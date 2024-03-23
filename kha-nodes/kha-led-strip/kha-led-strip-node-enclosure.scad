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
                eavr(13);
                terminal(-17.5, -14.5, 15, 24);
            }
            standoffs_vert(pcb_standoff_spacing);
        }
        standoffs_vert_holes(pcb_standoff_spacing);
    }
}

slice_top();
slice_bottom();
