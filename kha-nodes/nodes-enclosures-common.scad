$fn = $preview?6:60;

t = 3;

pcb_spacing = 1;
pcb_standoff = 5;

h = pcb_standoff + 1.6 + 14;
outer_w = t + pcb_spacing + pcb_w + pcb_spacing + t;
outer_l = t + pcb_spacing + pcb_l + pcb_spacing + t;
outer_h = t + h + t;   

cut = t + pcb_standoff + 2;
lip = 2;

module box() {
	difference() {
        cube([outer_w, outer_l, outer_h]);
        translate([t, t, t]) cube([pcb_spacing + pcb_w + pcb_spacing, pcb_spacing + pcb_l + pcb_spacing, h]);
    }
}

module standoffs_vert(spacing) {
	translate([outer_w / 2, outer_l/2, 0]) { 
            translate([0, 11, t]) {
				cylinder(h = pcb_standoff, d = 8);
				translate([0, -spacing, 0]) cylinder(h = pcb_standoff, d = 8);
			}
	}
}

module standoffs_vert_holes(spacing) {
	translate([outer_w / 2, outer_l/2, 0]) { 
            translate([0, 11, 0]) {
				cylinder(h = outer_h, d = 3.4);
				cylinder(h = 5.4, d = 6.4, $fn=6);
				translate([0, -spacing, 0]) {
					cylinder(h = outer_h, d = 3.4);
					cylinder(h = 5.4, d = 6.4, $fn=6);
				}
			}
	}
}

module standoffs_horiz(offset, spacing) {
	translate([outer_w / 2, outer_l/2 + offset, t]) { 
            translate([-spacing/2, 0, 0]) cylinder(h = pcb_standoff, d = 8);
			translate([+spacing/2, 0, 0]) cylinder(h = pcb_standoff, d = 8);
	}
}

module standoffs_horiz_holes(offset, spacing) {
	translate([outer_w / 2, outer_l/2 + offset, 0]) { 
		translate([-spacing/2, 0, 0]) cylinder(h = outer_h, d = 3.4);
		translate([-spacing/2, 0, 0]) cylinder(h = 5.4, d = 6.4, $fn=6);
		
		translate([+spacing/2, 0, 0]) cylinder(h = outer_h, d = 3.4);
		translate([+spacing/2, 0, 0]) cylinder(h = 5.4, d = 6.4, $fn=6);
	}
}

module wall_mount(spacing, y) {
	translate([outer_w / 2, outer_l/2, 0]) { 
            translate([0, y, 0]) {                            
				translate([-spacing/2, 0, 0]) {
					cylinder(h = t, d = 4.4);
					translate([spacing, 0, 0]) cylinder(h = t, d = 4.4);
				}
            }
        }
}

module socket(y) {
    translate([outer_w / 2, outer_l/2, 0]) { 
        translate([-outer_w/2, -17/2 + y, t + pcb_standoff + 1.6 + 12/2 - 14/2]) cube([outer_w, 17, 14]);
    }
}

module socket_center() {
    translate([outer_w / 2 - 17/2, outer_l - t, t + pcb_standoff + 1.6 + 12/2 - 14/2]) cube([17, t, 14]);
}

module eavr(x) {
    translate([outer_w / 2, 0, 0]) { 
       translate([-15/2 + x, 0, t + pcb_standoff + 1.6/2 - 10/2]) cube([15, t , 10]);
    }
}

module usb(x) {
    translate([outer_w / 2, 0, 0]) { 
        translate([-11/2 + x, 0, t + pcb_standoff + 1.6 + 3/2 - 9/2]) cube([11, t, 9]);
    }
}

module ident () {
    translate([outer_w / 2, outer_l/2, 0]) { 
        translate([-10/2 - 9.5, -19/2 - 5, 0]) cube([10, 19, t]);
    }
}

module jumper1(offset_x, offset_y) {
    translate([outer_w / 2 + offset_x, outer_l/2 + offset_y, outer_h-t]) { 
        translate([-8/2, -5/2, 0]) cube([8, 5, t]);
    }
}

module jumper3(offset_x, offset_y) {
    translate([outer_w / 2 + offset_x, outer_l/2 + offset_y, outer_h-t]) { 
        translate([-8/2, -10/2, 0]) cube([8, 10, t]);
    }
}

module idc(x) {
    translate([outer_w / 2, outer_l/2, 0]) { 
        translate([-22/2 + x, -12/2 - 20, outer_h - t]) cube([22, 12, t]);
    }
}
module terminal(x, y, w, l) {       
    translate([outer_w / 2 -w/2 + x, outer_l/2 -l/2 + y, t + pcb_standoff + 1.6]) cube([w, l, outer_h]);    
}

module terminal_front(x, y, w, l) {
    l2 = outer_l / 2 - y + l/2;    
    translate([outer_w / 2 -w/2 + x, 0, t + pcb_standoff + 1.6]) cube([w, l2, outer_h]);    
}

module slice_bottom() {
	translate([0, outer_w + 5, 0]) difference() {
		complete();
		translate([0, 0, cut + lip]) cube([outer_w, outer_l, outer_h]);
		
		s = (t/2) - 0.1;
		translate([s, s, cut]) cube([outer_w - s * 2, outer_l - s * 2, outer_h]);
	}
}

module slice_top() {
	translate([outer_w, 0, outer_h]) rotate([0, 180, 0]) difference() {	
		complete();
		translate([0, 0, 0]) cube([outer_w, outer_l, cut]);
		
		s = (t/2) + 0.1;
		translate([0, 0, 0]) cube([s, outer_l, cut + lip]);
		translate([outer_w - s, 0, 0]) cube([s, outer_l, cut + lip]);
		translate([0, 0, 0]) cube([outer_w, s, cut + lip]);
		translate([0, outer_l - s, 0]) cube([outer_w, s, cut + lip]);
	}
}
