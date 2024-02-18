$fn = 60;

dia = 3.6;
h = dia + 2;
il = 14;
ol = 1;
w = ol * 2 + 1;

l = il + 2 * h;

module clip() {
	  difference() {
			cube ([w, l, h]);
			translate([0, l/2-il/2,0]) cube ([ol, il, h]);
			translate([0, h/2, h/2]) rotate([0, 90, 0]) cylinder(h = w, d = dia);
			translate([0, l-h/2, h/2]) rotate([0, 90, 0]) cylinder(h = w, d = dia);
	  }
}

translate([0, 0, 0]) clip();
translate([w*2, 0, 0]) clip();
translate([w*4, 0, 0]) clip();
translate([w*6, 0, 0]) clip();
translate([w*8, 0, 0]) clip();
