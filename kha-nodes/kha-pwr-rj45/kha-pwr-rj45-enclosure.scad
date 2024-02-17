pcb_w = 70;
pcb_l = 30;
pcb_standoff_offset = 2;
pcb_standoff_spacing = 28;
    
include <../nodes-enclosures-common.scad>

module complete() {
    difference() {
        union() {
            difference() {
                box();
                wall_mount(30, 11);
                socket(-4);
                socket_center();
                jumper3(-12, -9);
                jumper3(12, -9);
                jumper1(21, 10);
            }
            standoffs_horiz(pcb_standoff_offset, pcb_standoff_spacing);
        }
        standoffs_horiz_holes(pcb_standoff_offset, pcb_standoff_spacing);
    }
}

slice_top();
slice_bottom();
