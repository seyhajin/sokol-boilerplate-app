#include <stdio.h>

#define SOKOL_IMPL
#define SOKOL_GLCORE33 //SOKOL_GLES2, SOKOL_GLES3, SOKOL_D3D11, SOKOL_METAL, SOKOL_DUMMY_BACKEND
#include <sokol/sokol_app.h>
#include <sokol/sokol_gfx.h>

static sg_pass_action pass_action;

void init(void) {
	sg_setup(&(sg_desc) {
        .gl_force_gles2 = true,
        .mtl_device = sapp_metal_get_device(),
        .mtl_renderpass_descriptor_cb = sapp_metal_get_renderpass_descriptor,
        .mtl_drawable_cb = sapp_metal_get_drawable,
        .d3d11_device = sapp_d3d11_get_device(),
        .d3d11_device_context = sapp_d3d11_get_device_context(),
        .d3d11_render_target_view_cb = sapp_d3d11_get_render_target_view,
        .d3d11_depth_stencil_view_cb = sapp_d3d11_get_depth_stencil_view
    });

    pass_action = (sg_pass_action) {
        .colors[0] = { .action=SG_ACTION_CLEAR, .val={1.0f, 0.0f, 0.0f, 1.0f} }
    };
}

void frame(void) {
	float g = pass_action.colors[0].val[1] + 0.01f;
    pass_action.colors[0].val[1] = (g > 1.0f) ? 0.0f : g;
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());

    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
	sg_shutdown();
}

//=========================================
// Main entry
//=========================================
sapp_desc sokol_main(int argc, char* argv[]) {
	return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .width = 400,
        .height = 300,
        .gl_force_gles2 = true,
        .window_title = "sokol app",
    };
}