pcb_w = 50;
pcb_l = 53;
pcb_standoff_spacing = 23;
    
include <../nodes-enclosures-common.scad>

module complete() {
    difference() {
        union() {
            difference() {
                box();
                wall_mount(30, 11);
                ident();
                socket(14);
                eavr(-3);
                terminal(14.75, -22.525, 20, 7);
                terminal(-18.25, -16, 14, 18);
            }
            standoffs_vert(pcb_standoff_spacing);
        }
        standoffs_vert_holes(pcb_standoff_spacing);
    }
}

slice_top();
//slice_bottom();
