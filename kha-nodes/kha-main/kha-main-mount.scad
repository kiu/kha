$fn = 60;

t = 4;

module main() {
    difference() {
        cube([20, t, 20 + t]);
        translate([20/2, 0, t + 20/2]) rotate([-90, 0, 0]) cylinder(h = t, d = 16);
    }
    difference() {
        cube([20, t + 50, t]);
        translate([20/2, t + 35, 0]) cylinder(h = t, d = 3.4);
        translate([20/2, t + 35, t - 1]) cylinder(h = t, d = 6.6);
        
        translate([20/2, t + 45, 0]) cylinder(h = t, d = 3.4);
        translate([20/2, t + 45, t - 1]) cylinder(h = t, d = 6.6);
    }
}

main();
