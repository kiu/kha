$fn = 60;

t = 6;

rack_w = 27.8;
rack_l = 132.5;

rack_c_w = 2.5;
rack_c_l = 1.4;

rack_h_distance = 88;
rack_h_offset_w = 12.15;
rack_h_offset_l = 22.25;
rack_h_dia = 7;

shelf_l = 17;
shelf_d = 14;
shelf_h_dia = 4.6;

module main_left() {
difference() {
    cube([rack_w, t, rack_l]);
    translate([rack_w - rack_c_w, 0, 0]) cube([rack_c_w, t, rack_c_l]);
    translate([rack_w - rack_c_w, 0, rack_l - rack_c_l]) cube([rack_c_w, t, rack_c_l]);
    translate([rack_w - rack_h_offset_w, 0, rack_h_offset_l]) {
        rotate([-90, 0, 0]) cylinder(h = t, d = rack_h_dia);
        translate([-12.4 / 2, 0, -8.4 / 2]) cube([12.4, 2, 8.4]);
        translate([0, 0, rack_h_distance]) {
            rotate([-90, 0, 0]) cylinder(h = t, d = rack_h_dia);
            translate([-12.4 / 2, 0, -8.4 / 2]) cube([12.4, 2, 8.4]);
        }
    }
}

translate([0, 0, -shelf_l]) {		
    cube([rack_w, t, shelf_l]);
}

translate([0, 0, -shelf_l - t]) {
    difference() {
        cube([rack_w, t + shelf_d, t]);
        translate([rack_w / 2, t + shelf_d / 2, 0]) cylinder(h = t, d = shelf_h_dia);
        translate([rack_w / 2, t + shelf_d / 2, 0]) cylinder(h = 2, d = shelf_h_dia * 2);
    }
}
}

module main_right() {
difference() {
    cube([rack_w, t, rack_l]);
    translate([0, 0, 0]) cube([rack_c_w, t, rack_c_l]);
    translate([0, 0, rack_l - rack_c_l]) cube([rack_c_w, t, rack_c_l]);
    translate([rack_h_offset_w, 0, rack_h_offset_l]) {
        rotate([-90, 0, 0]) cylinder(h = t, d = rack_h_dia);
        translate([-12.4 / 2, 0, -8.4 / 2]) cube([12.4, 2, 8.4]);
        translate([0, 0, rack_h_distance]) {
            rotate([-90, 0, 0]) cylinder(h = t, d = rack_h_dia);
            translate([-12.4 / 2, 0, -8.4 / 2]) cube([12.4, 2, 8.4]);
        }
    }
}

translate([0, 0, -shelf_l]) {		
    cube([rack_w, t, shelf_l]);
}

translate([0, 0, -shelf_l - t]) {
    difference() {
        cube([rack_w, t + shelf_d, t]);
        translate([rack_w / 2, t + shelf_d / 2, 0]) cylinder(h = t, d = shelf_h_dia);
        translate([rack_w / 2, t + shelf_d / 2, 0]) cylinder(h = 2, d = shelf_h_dia * 2);
    }
}
}

translate([-20, 0, 0]) main_left();
translate([ 20, 0, 0]) main_right();