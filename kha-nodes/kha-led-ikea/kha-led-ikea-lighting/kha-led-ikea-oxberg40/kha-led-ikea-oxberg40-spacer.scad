$fn = 60;

height = 2.0;
dia_inner = 3.4;
dia_outer = 5.8;

// -------------------------------------------------------

module spacer() {
	  difference() {
			cylinder(h = height, d = dia_outer);
			cylinder(h = height, d = dia_inner);
	  }
}

// -------------------------------------------------------

translate([  0,  0, 0])spacer();
translate([ 10,  0, 0])spacer();
translate([ 20,  0, 0])spacer();
translate([ 30,  0, 0])spacer();

translate([  0, 10, 0])spacer();
translate([ 10, 10, 0])spacer();
translate([ 20, 10, 0])spacer();
translate([ 30, 10, 0])spacer();

translate([  0, 20, 0])spacer();
translate([ 10, 20, 0])spacer();
translate([ 20, 20, 0])spacer();
translate([ 30, 20, 0])spacer();

translate([  0, 30, 0])spacer();
translate([ 10, 30, 0])spacer();
translate([ 20, 30, 0])spacer();
translate([ 30, 30, 0])spacer();
