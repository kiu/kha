$fn = 60;

t = 4;

wbox = 336;

d1 = 3.6;

dm = 68;

w = t + d1 / 2 + dm + d1 / 2 + t;
l = d1 + 4;

depth = 60;

cube ([wbox / 2, 8, t]);

cube ([20, t, 12]);
translate([wbox/2 - 20, 0, 0]) cube ([20, t, 12]);

translate([wbox/2 - w/2 + t, t + depth, 0]) difference() {
	  cube ([w, l, t]);
	  
	  // mounting holes
	  translate([w/2 - dm/2, l/2, 0]) cylinder(h = t * 2, d = d1);
	  translate([w/2 + dm/2, l/2, 0]) cylinder(h = t * 2, d = d1);
}

translate([wbox/2 - 8/2 + t, 0, 0]) cube([8, t + depth, t]);


