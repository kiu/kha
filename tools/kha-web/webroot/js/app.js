// kha-web status page: renders data/nodes.json, refreshes periodically.

const REFRESH_MS = 15000;
// the collector's export; ?mock shows the mock data instead
const DATA_URL = new URLSearchParams(location.search).has("mock") ? "data/mock.json" : "data/nodes.json";

// counters per direction: the frame count, then its error counters
const COUNTER_GROUPS = [
  { title: "Receive", total: "rx", errors: [
    ["rx_framing", "framing"], ["rx_overrun", "overrun"], ["rx_buffer_full", "buffer full"],
    ["rx_start_unescaped", "start unescaped"], ["rx_start_missing", "start missing"],
    ["rx_len", "length"], ["rx_crc", "crc"],
  ] },
  { title: "Transmit", total: "tx", errors: [["tx_len", "length"], ["tx_full", "queue full"]] },
];
const NOT_ERRORS = new Set(["rx", "tx"]);
const STATES = ["ok", "errors", "missing", "unknown"];

let data = null;
let fwReport = null;
let selected = location.hash.slice(1).toUpperCase() || null;

// helpers ---------------------------------------------------------------------

const el = (tag, cls, text) => {
  const e = document.createElement(tag);
  if (cls) e.className = cls;
  if (text !== undefined) e.textContent = text;
  return e;
};

// ages: live data is only exported on change, so its ages run against the clock; mock data against its
// snapshot time, so it reads the same however old the file is
const ref = () => (data.mock ? new Date(data.generated) : new Date());

function age(iso, from = ref()) {
  if (!iso) return "–";
  const s = Math.max(0, (from - new Date(iso)) / 1000);
  if (s < 90) return `${Math.round(s)} s`;
  if (s < 90 * 60) return `${Math.round(s / 60)} min`;
  if (s < 36 * 3600) return `${Math.round(s / 3600)} h`;
  return `${Math.floor(s / 86400)} d`;
}

function daysSince(iso) {
  if (!iso) return null;
  return Math.floor((ref() - new Date(iso)) / 86400000);
}

const clock = (iso) => new Date(iso).toLocaleTimeString([], { hour: "2-digit", minute: "2-digit", second: "2-digit" });
const dateTime = (iso) => new Date(iso).toLocaleString([], { dateStyle: "short", timeStyle: "short" });

// firmware versions are the build time as unix seconds
function versionDate(hex) {
  const d = new Date(parseInt(hex, 16) * 1000);
  return d.toLocaleString([], { dateStyle: "short", timeStyle: "short" });
}

const errorSum = (n) => Object.entries(n.stats || {}).reduce((sum, [k, v]) => sum + (NOT_ERRORS.has(k) ? 0 : v), 0);

// gateways carry a "log" key: their decode errors (array), or null when this server can't see their log
const isGateway = (n) => "log" in n;
const logErrors = (n) => (n.log || []).length;

// nodes never reboot in normal operation: a reboot within this window stands out
const RECENT_REBOOT_H = 24;
const rebootedRecently = (n) => n.last_up && (ref() - new Date(n.last_up)) / 3600000 < RECENT_REBOOT_H;
// the guru asks every known node once per interval. Nothing for longer than 1.5 intervals, without a
// failed request ("missing"), means nobody asked: not in the guru's known list, or nobody is polling
const seenStale = (n) => n.state !== "missing" && (ref() - new Date(n.last_seen)) / 1000 > 1.5 * data.guru_interval_s;
// most nodes stale at once is a data problem (guru not polling, gateway or collector silent), not theirs
const STALE_ALL_SHARE = 0.75;
let allStale = false;
const notPolled = (n) => !allStale && seenStale(n);

const typeLabel = (n) => n.type_name || `type ${n.type}`;
const inConfig = (n) => data.sections.some((s) => s.id === n.section);

// everything unusual about a node, for its tile (all marked yellow)
function oddities(n) {
  const out = [];
  if (!inConfig(n)) out.push("new");
  if (fwReport.odd.has(n.addr)) out.push("fw");
  if (!n.boot || !n.app) out.push("fw ?");
  if (notPolled(n)) out.push("not polled");
  const errs = errorSum(n) + logErrors(n);
  if (errs) out.push(`${errs} err`);
  return out;
}
const unusual = (n) => n.state !== "missing" && (rebootedRecently(n) || !n.last_up || oddities(n).length > 0);

// firmware: what most nodes of a board type run is the reference, everything else stands out
const fwKey = (fw) => (fw ? `${fw.version}/${fw.crc}` : null);

function variants(nodes, pick) {
  const map = new Map();
  for (const n of nodes) {
    const key = fwKey(pick(n));
    if (!key) continue;
    if (!map.has(key)) map.set(key, { fw: pick(n), nodes: [] });
    map.get(key).nodes.push(n);
  }
  return [...map.values()].sort((a, b) => b.nodes.length - a.nodes.length);
}

function firmwareReport() {
  const boot = variants(data.nodes, (n) => n.boot);
  const types = new Map();
  for (const n of data.nodes) {
    if (!types.has(n.type)) types.set(n.type, { type: n.type, name: n.type_name, nodes: [] });
    types.get(n.type).nodes.push(n);
  }
  const apps = [...types.values()].sort((a, b) => a.type.localeCompare(b.type))
    .map((t) => ({ ...t, variants: variants(t.nodes, (n) => n.app) }));
  // the most common variant is the reference; on a tie (e.g. two relay nodes, two versions) there is none
  const hasRef = (vs) => vs.length <= 1 || vs[0].nodes.length > vs[1].nodes.length;
  const odd = new Set(); // nodes whose boot or app differs from the reference
  const mark = (vs) => vs.slice(hasRef(vs) ? 1 : 0).forEach((v) => v.nodes.forEach((n) => odd.add(n.addr)));
  mark(boot);
  apps.forEach((t) => mark(t.variants));
  return { boot, apps, odd, hasRef };
}

// banner: no fresh data at all -------------------------------------------------

// The collector only exports when something changed, and every guru round changes something. So data
// older than 1.5 guru intervals (by this browser's clock) means nothing arrives: guru, gateway or
// collector. Inside the data, most nodes quiet together means the same from the bus side.
function renderBanner() {
  const box = document.getElementById("banner");
  // mock data is written once and would turn old while iterating on the page
  const snapshotOld = !data.mock && (Date.now() - new Date(data.generated)) / 1000 > 1.5 * data.guru_interval_s;
  const alive = data.nodes.filter((n) => n.state !== "missing");
  const stale = alive.filter(seenStale);
  allStale = snapshotOld || (alive.length > 0 && stale.length / alive.length >= STALE_ALL_SHARE);
  box.hidden = !allStale;
  if (!allStale) return;
  if (snapshotOld) {
    box.replaceChildren(el("strong", "", `No new data since ${dateTime(data.generated)} (${age(data.generated, new Date())} ago). `),
      document.createTextNode("Every guru round should change something: the guru isn't polling, or the gateway / "
        + "collector stopped delivering. The states below are as of then."));
    return;
  }
  const newest = alive.map((n) => n.last_seen).sort().pop();
  box.replaceChildren(el("strong", "", `No fresh data since ${clock(newest)} (${age(newest)} ago). `),
    document.createTextNode(`${stale.length} of ${alive.length} nodes went quiet together: the guru isn't polling, `
      + "or the gateway / collector stopped delivering. The states below are as of then."));
}

// summary ---------------------------------------------------------------------

function renderSummary() {
  const box = document.getElementById("summary");
  box.replaceChildren();
  for (const state of STATES) {
    const count = data.nodes.filter((n) => n.state === state).length;
    if (!count && state !== "ok") continue;
    const pill = el("span", `pill state-${state}`);
    pill.append(el("span", `dot state-${state}`), el("span", "count", count), document.createTextNode(state));
    box.append(pill);
  }
  const notes = [
    [data.nodes.filter(rebootedRecently).length, `rebooted < ${RECENT_REBOOT_H} h`],
    [fwReport.odd.size, "firmware differs"],
  ];
  for (const [count, text] of notes) {
    if (!count) continue;
    const pill = el("span", "pill state-errors");
    pill.append(el("span", "count", count), document.createTextNode(text));
    box.append(pill);
  }

  const snap = document.getElementById("snapshot");
  snap.replaceChildren(document.createTextNode(`data ${clock(data.generated)} · ${age(data.generated, new Date())} ago `));
  if (data.mock) snap.append(el("span", "badge-mock", "mock"));
}

// bus map ---------------------------------------------------------------------

function nodeButton(n) {
  const b = el("button", `node state-${n.state}${unusual(n) ? " unusual" : ""}${n.addr === selected ? " selected" : ""}`);
  b.type = "button";
  b.title = `${n.addr} ${n.name || "not in config"} (${typeLabel(n)})`;
  b.addEventListener("click", () => select(n.addr));

  const head = el("div", "node-head");
  const group = el("span", "node-group", `grp ${n.group}`);
  group.title = "group address";
  head.append(el("span", `dot state-${n.state}`), el("span", "node-addr", n.addr), group);
  const meta = el("div", "node-meta");
  if (n.state === "missing") {
    meta.append(el("span", "error", `missing ${age(n.missing_since)}`));
  } else {
    const days = daysSince(n.last_up);
    meta.append(el("span", rebootedRecently(n) ? "warn" : "",
      days === null ? "↻ ?" : days === 0 ? `↻ ${age(n.last_up)}` : `↻ ${days} d`));
    const flags = oddities(n);
    if (flags.length) meta.append(el("span", "warn", flags.join(" · ")));
  }
  b.append(head, el("div", "node-type", typeLabel(n)),
    el("div", `node-name${n.name ? "" : " faint"}`, n.name || "not in config"), meta);
  return b;
}

function renderBus() {
  const bus = document.getElementById("bus");
  bus.replaceChildren();
  // nodes the config doesn't know (new address): their own section at the end
  const unplaced = { id: null, label: "Not in config", nodes: data.nodes.filter((n) => !inConfig(n)) };
  for (const section of [...data.sections, unplaced]) {
    const nodes = section.nodes || data.nodes.filter((n) => n.section === section.id);
    if (!nodes.length) continue;
    const s = el("div", "bus-section");
    const row = el("div", "bus-section-nodes");
    row.append(...nodes.map(nodeButton));
    s.append(el("div", "bus-section-label", section.label), row);
    bus.append(s);
  }
}

// detail ----------------------------------------------------------------------

function kv(pairs) {
  const dl = el("dl", "kv");
  for (const [k, v] of pairs) {
    const dd = el("dd");
    if (v instanceof Node) dd.append(v); else dd.textContent = v;
    dl.append(el("dt", "", k), dd);
  }
  return dl;
}

function section(title, ...content) {
  const s = el("div", "detail-section");
  s.append(el("h3", "", title), ...content);
  return s;
}

function firmware(fw) {
  if (!fw) return el("span", "warn", "unknown (no UP / ident yet)");
  const span = el("span");
  span.append(el("span", "mono", fw.crc), document.createTextNode(` · built ${versionDate(fw.version)}`));
  return span;
}

// what the other nodes run, when this node isn't on the reference (most common) variant
function fwCompare(fw, vs) {
  if (!fw || vs.length <= 1) return null;
  const hasRef = fwReport.hasRef(vs);
  if (hasRef && fwKey(vs[0].fw) === fwKey(fw)) return null;
  const others = vs.filter((v) => fwKey(v.fw) !== fwKey(fw));
  const span = el("span", "warn");
  span.append(hasRef ? "others: " : "no majority, others: ");
  others.forEach((v, i) => {
    if (i) span.append("; ");
    span.append(el("span", "mono", v.fw.crc), ` · ${versionDate(v.fw.version)} `);
    span.append(v.nodes.length > 4 ? `(${v.nodes.length} nodes)` : nodeLinks(v.nodes));
  });
  return span;
}

function renderDetail() {
  const box = document.getElementById("detail");
  box.replaceChildren();
  const n = data.nodes.find((x) => x.addr === selected);
  if (!n) {
    box.append(el("h2", "card-title", "Node"), el("p", "empty", "Select a node on the bus map."));
    return;
  }

  const head = el("div", "detail-head");
  head.append(el("span", "detail-addr", n.addr),
    el("span", `detail-name${n.name ? "" : " faint"}`, n.name || "not in config"));
  const pill = el("span", `pill state-${n.state}`);
  pill.append(el("span", `dot state-${n.state}`), document.createTextNode(n.state));
  box.append(head, el("div", "detail-sub", `${typeLabel(n)} · rev ${n.rev} · group ${n.group}`), pill);
  if (!inConfig(n)) {
    box.append(el("p", "note warn", n.type_name
      ? "New address: not in the config yet (no name or place on the bus)."
      : `New address, and its board type ${n.type} isn't in the protocol's type list.`));
  }

  const days = daysSince(n.last_up);
  const big = el("div", `big-number${rebootedRecently(n) || days === null ? " warn" : ""}`);
  if (days === null) big.append(el("span", "value", "?"), el("span", "unit", "no reboot seen yet"));
  else big.append(el("span", "value", days), el("span", "unit", `days since reboot · ${dateTime(n.last_up)}`));
  const uptime = [big];
  if (rebootedRecently(n)) uptime.push(el("p", "note warn", `Rebooted within the last ${RECENT_REBOOT_H} h. Nodes don't reboot in normal operation.`));
  box.append(section("Uptime", ...uptime));

  const lastSeen = el("span", n.missing_since ? "error" : notPolled(n) ? "warn" : "", `${age(n.last_seen)} ago · ${clock(n.last_seen)}`);
  const status = section("Status", kv([
    ["last seen", lastSeen],
    ...(n.missing_since ? [["missing", el("span", "error", `${age(n.missing_since)} (since ${clock(n.missing_since)})`)]] : []),
    ["mode", n.mode],
    ["board type", `${n.type} ${n.type_name || "(unknown type)"}`],
  ]));
  if (notPolled(n)) {
    status.append(el("p", "note warn", "Not polled: no request went unanswered, but nothing heard for longer than "
      + "1.5 guru intervals. Probably not in the guru's known list (the guru button rescans)."));
  }
  box.append(status);

  const appVariants = fwReport.apps.find((t) => t.type === n.type).variants;
  const fwRows = [];
  for (const [label, fw, vs] of [["boot", n.boot, fwReport.boot], ["app", n.app, appVariants]]) {
    fwRows.push([label, firmware(fw)]);
    const cmp = fwCompare(fw, vs);
    if (cmp) fwRows.push(["", cmp]);
  }
  box.append(section("Firmware", kv(fwRows)));

  const counters = el("div", "counters");
  const fmt = (v) => (v === null || v === undefined ? "–" : v === 255 ? "FF+" : v); // saturate at FF; – = not reported (old stack)
  for (const group of COUNTER_GROUPS) {
    const g = el("div", "counter-group");
    const head = el("div", "counter-head");
    head.append(el("span", "counter-title", group.title),
      el("span", "counter-total", `${fmt(n.stats[group.total])} frames`));
    g.append(head);
    for (const [key, label] of group.errors) {
      const v = n.stats[key];
      const c = el("div", `counter${v > 0 ? " bad" : " zero"}`);
      c.append(el("span", "label", label), el("span", "value", fmt(v)));
      g.append(c);
    }
    counters.append(g);
  }
  box.append(section(`Counters · ${age(n.stats_at)} ago`, counters));

  if (isGateway(n)) box.append(gatewayLog(n));
}

// gateway: decode errors from its own log (only errors are published) ----------

function gatewayLog(n) {
  const title = `Decode errors · last ${data.log_window_h} h`;
  if (n.log === null) return section(title, el("p", "empty", "Not available: only the gateway attached to this server reports its log."));
  if (!n.log.length) return section(title, el("p", "empty", "None."));
  const t = el("table", "table");
  const hr = el("tr");
  for (const h of ["time", "age", "message"]) hr.append(el("th", "", h));
  t.append(hr);
  for (const line of n.log) {
    const tr = el("tr", "level-error");
    tr.append(el("td", "nowrap mono", clock(line.t)), el("td", "nowrap faint", age(line.t)), el("td", "text", line.text));
    t.append(tr);
  }
  return section(title, t);
}

// links to nodes ------------------------------------------------------------

function nodeLinks(nodes) {
  const span = el("span", "node-links");
  for (const n of nodes) {
    const a = el("a", "node-link mono", n.addr);
    a.href = `#${n.addr}`;
    a.title = n.name || "not in config";
    span.append(a);
  }
  return span;
}

// wiring ----------------------------------------------------------------------

// below this width the detail sits under the map (see app.css)
const narrow = matchMedia("(max-width: 1000px)");

function select(addr) {
  selected = addr;
  history.replaceState(null, "", `#${addr}`);
  renderBus();
  renderDetail();
  if (narrow.matches) document.getElementById("detail").scrollIntoView({ behavior: "smooth", block: "start" });
}

function render() {
  fwReport = firmwareReport();
  renderBanner();
  renderSummary();
  renderBus();
  renderDetail();
}

async function load() {
  try {
    data = await fetch(DATA_URL, { cache: "no-store" }).then((r) => r.json());
    render();
  } catch (e) {
    document.getElementById("snapshot").textContent = `no data: ${e.message}`;
  }
}

window.addEventListener("hashchange", () => {
  const addr = location.hash.slice(1).toUpperCase();
  if (addr && addr !== selected && data) select(addr);
});

load();
setInterval(load, REFRESH_MS);
