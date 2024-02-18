$fn = 60;

t = 3;
/*
wbox = 336;

d1 = 3.6;

dm = 68;

w = t + d1 / 2 + dm + d1 / 2 + t;
l = d1 + 4;

depth = 60;
*/

w = 26 + 4 + 4;


translate([-w, 0, 0]) {
	  difference() {
			cube ([w, 34, t]);
			translate([4,20 + 19 - 10,0]) cylinder(h = t, d = 3.4);
	  }
	  translate([4 + 4, 0, 0]) cube ([t, 24, t + 6]);
}

cube ([44, 20, t]);
translate([0, 20 - t, 0]) cube ([44, t, 16]);

/*
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
*/

