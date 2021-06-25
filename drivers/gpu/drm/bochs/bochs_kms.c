<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/moduleparam.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "bochs.h"

अटल पूर्णांक defx = 1024;
अटल पूर्णांक defy = 768;

module_param(defx, पूर्णांक, 0444);
module_param(defy, पूर्णांक, 0444);
MODULE_PARM_DESC(defx, "default x resolution");
MODULE_PARM_DESC(defy, "default y resolution");

/* ---------------------------------------------------------------------- */

अटल स्थिर uपूर्णांक32_t bochs_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_BGRX8888,
पूर्ण;

अटल व्योम bochs_plane_update(काष्ठा bochs_device *bochs,
			       काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_gem_vram_object *gbo;
	s64 gpu_addr;

	अगर (!state->fb || !bochs->stride)
		वापस;

	gbo = drm_gem_vram_of_gem(state->fb->obj[0]);
	gpu_addr = drm_gem_vram_offset(gbo);
	अगर (WARN_ON_ONCE(gpu_addr < 0))
		वापस; /* Bug: we didn't pin the BO to VRAM in prepare_fb. */

	bochs_hw_setbase(bochs,
			 state->crtc_x,
			 state->crtc_y,
			 state->fb->pitches[0],
			 state->fb->offsets[0] + gpu_addr);
	bochs_hw_setक्रमmat(bochs, state->fb->क्रमmat);
पूर्ण

अटल व्योम bochs_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
			      काष्ठा drm_crtc_state *crtc_state,
			      काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा bochs_device *bochs = pipe->crtc.dev->dev_निजी;

	bochs_hw_seपंचांगode(bochs, &crtc_state->mode);
	bochs_plane_update(bochs, plane_state);
पूर्ण

अटल व्योम bochs_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
			      काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा bochs_device *bochs = pipe->crtc.dev->dev_निजी;

	bochs_plane_update(bochs, pipe->plane.state);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs bochs_pipe_funcs = अणु
	.enable	    = bochs_pipe_enable,
	.update	    = bochs_pipe_update,
	.prepare_fb = drm_gem_vram_simple_display_pipe_prepare_fb,
	.cleanup_fb = drm_gem_vram_simple_display_pipe_cleanup_fb,
पूर्ण;

अटल पूर्णांक bochs_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा bochs_device *bochs =
		container_of(connector, काष्ठा bochs_device, connector);
	पूर्णांक count = 0;

	अगर (bochs->edid)
		count = drm_add_edid_modes(connector, bochs->edid);

	अगर (!count) अणु
		count = drm_add_modes_noedid(connector, 8192, 8192);
		drm_set_preferred_mode(connector, defx, defy);
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs bochs_connector_connector_helper_funcs = अणु
	.get_modes = bochs_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs bochs_connector_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम bochs_connector_init(काष्ठा drm_device *dev)
अणु
	काष्ठा bochs_device *bochs = dev->dev_निजी;
	काष्ठा drm_connector *connector = &bochs->connector;

	drm_connector_init(dev, connector, &bochs_connector_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	drm_connector_helper_add(connector,
				 &bochs_connector_connector_helper_funcs);

	bochs_hw_load_edid(bochs);
	अगर (bochs->edid) अणु
		DRM_INFO("Found EDID data blob.\n");
		drm_connector_attach_edid_property(connector);
		drm_connector_update_edid_property(connector, bochs->edid);
	पूर्ण
पूर्ण

अटल काष्ठा drm_framebuffer *
bochs_gem_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	अगर (mode_cmd->pixel_क्रमmat != DRM_FORMAT_XRGB8888 &&
	    mode_cmd->pixel_क्रमmat != DRM_FORMAT_BGRX8888)
		वापस ERR_PTR(-EINVAL);

	वापस drm_gem_fb_create(dev, file, mode_cmd);
पूर्ण

स्थिर काष्ठा drm_mode_config_funcs bochs_mode_funcs = अणु
	.fb_create = bochs_gem_fb_create,
	.mode_valid = drm_vram_helper_mode_valid,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

पूर्णांक bochs_kms_init(काष्ठा bochs_device *bochs)
अणु
	पूर्णांक ret;

	ret = drmm_mode_config_init(bochs->dev);
	अगर (ret)
		वापस ret;

	bochs->dev->mode_config.max_width = 8192;
	bochs->dev->mode_config.max_height = 8192;

	bochs->dev->mode_config.fb_base = bochs->fb_base;
	bochs->dev->mode_config.preferred_depth = 24;
	bochs->dev->mode_config.prefer_shaकरोw = 0;
	bochs->dev->mode_config.prefer_shaकरोw_fbdev = 1;
	bochs->dev->mode_config.quirk_addfb_prefer_host_byte_order = true;

	bochs->dev->mode_config.funcs = &bochs_mode_funcs;

	bochs_connector_init(bochs->dev);
	drm_simple_display_pipe_init(bochs->dev,
				     &bochs->pipe,
				     &bochs_pipe_funcs,
				     bochs_क्रमmats,
				     ARRAY_SIZE(bochs_क्रमmats),
				     शून्य,
				     &bochs->connector);

	drm_mode_config_reset(bochs->dev);

	वापस 0;
पूर्ण
