pcb_w = 50;
pcb_l = 50;
pcb_standoff_spacing = 24;
    
include <../nodes-enclosures-common.scad>

module complete() {
    difference() {
        union() {
            difference() {
                box(pcb_standoff_spacing);
                wall_mount(30, 11);
                ident();
                socket(14);
                eavr(17.5);
                usb(-16.5);
            }
            standoffs_vert(pcb_standoff_spacing);
        }
        standoffs_vert_holes(pcb_standoff_spacing);
    }
}

slice_top();
slice_bottom();
