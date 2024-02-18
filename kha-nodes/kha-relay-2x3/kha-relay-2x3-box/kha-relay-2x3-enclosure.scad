$fn = $preview?6:60;

pcb_height = 1.6;

base_thick = 4;
wall_thick = 3;
lip_thick = 1;

standoff_height = 4;

mount_dia_inner = 3.4;
mount_dia_head = 6.6;
mount_dia_outer = mount_dia_inner + 4;

sep = 55;

outer_width = wall_thick + 1.5 + 46 + 1.5 + wall_thick;
outer_length = wall_thick + 1.5 + 194 + 1.5 + wall_thick;

outer_height = base_thick + standoff_height + pcb_height + sep + pcb_height;

pcb_mount_width1 = 8.5;
pcb_mount_width2 = outer_width - pcb_mount_width1;
pcb_mount_length1 = 8.5;
pcb_mount_length2 = outer_length - pcb_mount_length1;

// -------------------------------------------------------

module mount_wall(x) {
    translate([x, outer_width - wall_thick, outer_height - 20]) {
        rotate([-90, 0, 0]) cylinder(h = wall_thick, d = 9);
        translate([-5/2, 0, 0]) cube([5, wall_thick, 10]);
        translate([0, 0, 10]) rotate([-90, 0, 0]) cylinder(h = wall_thick, d = 5);
    }
}

module mount_socket_pwr(x) {
	  translate([x, 0, base_thick + standoff_height + pcb_height + sep/2]) {
			//translate([-25, 3, -25]) cube([50, outer_width - 6, 50]);
			
			rotate([-90, 0, 0]) {
			cylinder(h = wall_thick, d = 44);
			translate([-19, -19, 0]) cylinder(h = wall_thick, d = 4.7);
			translate([-19,  19, 0]) cylinder(h = wall_thick, d = 4.7);
			translate([ 19, -19, 0]) cylinder(h = wall_thick, d = 4.7);
			translate([ 19,  19, 0]) cylinder(h = wall_thick, d = 4.7);
			}
	  }
}

module pcb_mount(x, y) {
	  translate([x, y, base_thick]) {
			difference() {
				  cylinder(h = standoff_height, d = mount_dia_outer);
				  cylinder(h = standoff_height, d = mount_dia_inner);
			}
	  }
}

module pcb_mount_diff(x, y) {
	  translate([x, y, 0]) {
			cylinder(h = base_thick, d = mount_dia_inner);
			cylinder(h = 1.5, d = mount_dia_head);
	  }
}

module base() {
	  difference() {
			cube ([outer_length, outer_width, outer_height]);

			// Sockets
			offset = -54/2 + 60.5;
			mount_socket_pwr(offset + (54 / 2) + (54 * 0));
			mount_socket_pwr(offset + (54 / 2) + (54 * 1));
			mount_socket_pwr(offset + (54 / 2) + (54 * 2));

			// Inner
			translate([wall_thick, wall_thick, base_thick]) cube([outer_length - 2 * wall_thick, outer_width - 2 * wall_thick, outer_height - base_thick]);

			// Lip
			translate([lip_thick, lip_thick, outer_height - pcb_height]) cube([outer_length - 2 * lip_thick, outer_width - 2 * lip_thick, pcb_height]);

			// PCB Mount
			pcb_mount_diff(pcb_mount_length1, pcb_mount_width1);
			pcb_mount_diff(pcb_mount_length2, pcb_mount_width1);
			pcb_mount_diff(pcb_mount_length1, pcb_mount_width2);
			pcb_mount_diff(pcb_mount_length2, pcb_mount_width2);

			// PWR Input
			translate([0, outer_width/2, base_thick + 10 + 4]) rotate([0, 90, 0]) cylinder(h = wall_thick, d = 16);

			// Data Input
			translate([0, outer_width/2, base_thick + 10 + 16/2 + 8 + 28/2]) {
                rotate([0, 90, 0]) cylinder(h = wall_thick, d = 24);
                translate([0, -24/2, 19/2]) rotate([0, 90, 0]) cylinder(h = wall_thick, d = 3.4);
                translate([0, 24/2, -19/2]) rotate([0, 90, 0]) cylinder(h = wall_thick, d = 3.4);
            }
            
            mount_wall(outer_length/2 - 50);
            mount_wall(outer_length/2 + 50);
	}
}

// -------------------------------------------------------

base();

pcb_mount(pcb_mount_length1, pcb_mount_width1);
pcb_mount(pcb_mount_length2, pcb_mount_width1);
pcb_mount(pcb_mount_length1, pcb_mount_width2);
pcb_mount(pcb_mount_length2, pcb_mount_width2);

// -------------------------------------------------------
