<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Noralf Trथचnnes
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

/**
 * DOC: overview
 *
 * This helper library provides helpers क्रम drivers क्रम simple display
 * hardware.
 *
 * drm_simple_display_pipe_init() initializes a simple display pipeline
 * which has only one full-screen scanout buffer feeding one output. The
 * pipeline is represented by &काष्ठा drm_simple_display_pipe and binds
 * together &drm_plane, &drm_crtc and &drm_encoder काष्ठाures पूर्णांकo one fixed
 * entity. Some flexibility क्रम code reuse is provided through a separately
 * allocated &drm_connector object and supporting optional &drm_bridge
 * encoder drivers.
 *
 * Many drivers require only a very simple encoder that fulfills the minimum
 * requirements of the display pipeline and करोes not add additional
 * functionality. The function drm_simple_encoder_init() provides an
 * implementation of such an encoder.
 */

अटल स्थिर काष्ठा drm_encoder_funcs drm_simple_encoder_funcs_cleanup = अणु
	.destroy = drm_encoder_cleanup,
पूर्ण;

/**
 * drm_simple_encoder_init - Initialize a pपुनः_स्मृतिated encoder with
 *                           basic functionality.
 * @dev: drm device
 * @encoder: the encoder to initialize
 * @encoder_type: user visible type of the encoder
 *
 * Initialises a pपुनः_स्मृतिated encoder that has no further functionality.
 * Settings क्रम possible CRTC and clones are left to their initial values.
 * The encoder will be cleaned up स्वतःmatically as part of the mode-setting
 * cleanup.
 *
 * The caller of drm_simple_encoder_init() is responsible क्रम मुक्तing
 * the encoder's memory after the encoder has been cleaned up. At the
 * moment this only works reliably अगर the encoder data काष्ठाure is
 * stored in the device काष्ठाure. Free the encoder's memory as part of
 * the device release function.
 *
 * Note: consider using drmm_simple_encoder_alloc() instead of
 * drm_simple_encoder_init() to let the DRM managed resource infraकाष्ठाure
 * take care of cleanup and deallocation.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_simple_encoder_init(काष्ठा drm_device *dev,
			    काष्ठा drm_encoder *encoder,
			    पूर्णांक encoder_type)
अणु
	वापस drm_encoder_init(dev, encoder,
				&drm_simple_encoder_funcs_cleanup,
				encoder_type, शून्य);
पूर्ण
EXPORT_SYMBOL(drm_simple_encoder_init);

व्योम *__drmm_simple_encoder_alloc(काष्ठा drm_device *dev, माप_प्रकार size,
				  माप_प्रकार offset, पूर्णांक encoder_type)
अणु
	वापस __drmm_encoder_alloc(dev, size, offset, शून्य, encoder_type,
				    शून्य);
पूर्ण
EXPORT_SYMBOL(__drmm_simple_encoder_alloc);

अटल क्रमागत drm_mode_status
drm_simple_kms_crtc_mode_valid(काष्ठा drm_crtc *crtc,
			       स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(crtc, काष्ठा drm_simple_display_pipe, crtc);
	अगर (!pipe->funcs || !pipe->funcs->mode_valid)
		/* Anything goes */
		वापस MODE_OK;

	वापस pipe->funcs->mode_valid(pipe, mode);
पूर्ण

अटल पूर्णांक drm_simple_kms_crtc_check(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	bool has_primary = crtc_state->plane_mask &
			   drm_plane_mask(crtc->primary);

	/* We always want to have an active plane with an active CRTC */
	अगर (has_primary != crtc_state->enable)
		वापस -EINVAL;

	वापस drm_atomic_add_affected_planes(state, crtc);
पूर्ण

अटल व्योम drm_simple_kms_crtc_enable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(crtc, काष्ठा drm_simple_display_pipe, crtc);
	अगर (!pipe->funcs || !pipe->funcs->enable)
		वापस;

	plane = &pipe->plane;
	pipe->funcs->enable(pipe, crtc->state, plane->state);
पूर्ण

अटल व्योम drm_simple_kms_crtc_disable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(crtc, काष्ठा drm_simple_display_pipe, crtc);
	अगर (!pipe->funcs || !pipe->funcs->disable)
		वापस;

	pipe->funcs->disable(pipe);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs drm_simple_kms_crtc_helper_funcs = अणु
	.mode_valid = drm_simple_kms_crtc_mode_valid,
	.atomic_check = drm_simple_kms_crtc_check,
	.atomic_enable = drm_simple_kms_crtc_enable,
	.atomic_disable = drm_simple_kms_crtc_disable,
पूर्ण;

अटल पूर्णांक drm_simple_kms_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(crtc, काष्ठा drm_simple_display_pipe, crtc);
	अगर (!pipe->funcs || !pipe->funcs->enable_vblank)
		वापस 0;

	वापस pipe->funcs->enable_vblank(pipe);
पूर्ण

अटल व्योम drm_simple_kms_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(crtc, काष्ठा drm_simple_display_pipe, crtc);
	अगर (!pipe->funcs || !pipe->funcs->disable_vblank)
		वापस;

	pipe->funcs->disable_vblank(pipe);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs drm_simple_kms_crtc_funcs = अणु
	.reset = drm_atomic_helper_crtc_reset,
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = drm_simple_kms_crtc_enable_vblank,
	.disable_vblank = drm_simple_kms_crtc_disable_vblank,
पूर्ण;

अटल पूर्णांक drm_simple_kms_plane_atomic_check(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *plane_state = drm_atomic_get_new_plane_state(state,
									     plane);
	काष्ठा drm_simple_display_pipe *pipe;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	crtc_state = drm_atomic_get_new_crtc_state(state,
						   &pipe->crtc);

	ret = drm_atomic_helper_check_plane_state(plane_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, true);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->visible)
		वापस 0;

	अगर (!pipe->funcs || !pipe->funcs->check)
		वापस 0;

	वापस pipe->funcs->check(pipe, plane_state, crtc_state);
पूर्ण

अटल व्योम drm_simple_kms_plane_atomic_update(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_pstate = drm_atomic_get_old_plane_state(state,
									    plane);
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	अगर (!pipe->funcs || !pipe->funcs->update)
		वापस;

	pipe->funcs->update(pipe, old_pstate);
पूर्ण

अटल पूर्णांक drm_simple_kms_plane_prepare_fb(काष्ठा drm_plane *plane,
					   काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	अगर (!pipe->funcs || !pipe->funcs->prepare_fb)
		वापस 0;

	वापस pipe->funcs->prepare_fb(pipe, state);
पूर्ण

अटल व्योम drm_simple_kms_plane_cleanup_fb(काष्ठा drm_plane *plane,
					    काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	अगर (!pipe->funcs || !pipe->funcs->cleanup_fb)
		वापस;

	pipe->funcs->cleanup_fb(pipe, state);
पूर्ण

अटल bool drm_simple_kms_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
						uपूर्णांक32_t क्रमmat,
						uपूर्णांक64_t modअगरier)
अणु
	वापस modअगरier == DRM_FORMAT_MOD_LINEAR;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs drm_simple_kms_plane_helper_funcs = अणु
	.prepare_fb = drm_simple_kms_plane_prepare_fb,
	.cleanup_fb = drm_simple_kms_plane_cleanup_fb,
	.atomic_check = drm_simple_kms_plane_atomic_check,
	.atomic_update = drm_simple_kms_plane_atomic_update,
पूर्ण;

अटल व्योम drm_simple_kms_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	अगर (!pipe->funcs || !pipe->funcs->reset_plane)
		वापस drm_atomic_helper_plane_reset(plane);

	वापस pipe->funcs->reset_plane(pipe);
पूर्ण

अटल काष्ठा drm_plane_state *drm_simple_kms_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	अगर (!pipe->funcs || !pipe->funcs->duplicate_plane_state)
		वापस drm_atomic_helper_plane_duplicate_state(plane);

	वापस pipe->funcs->duplicate_plane_state(pipe);
पूर्ण

अटल व्योम drm_simple_kms_plane_destroy_state(काष्ठा drm_plane *plane,
					       काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_simple_display_pipe *pipe;

	pipe = container_of(plane, काष्ठा drm_simple_display_pipe, plane);
	अगर (!pipe->funcs || !pipe->funcs->destroy_plane_state)
		drm_atomic_helper_plane_destroy_state(plane, state);
	अन्यथा
		pipe->funcs->destroy_plane_state(pipe, state);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs drm_simple_kms_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= drm_plane_cleanup,
	.reset			= drm_simple_kms_plane_reset,
	.atomic_duplicate_state	= drm_simple_kms_plane_duplicate_state,
	.atomic_destroy_state	= drm_simple_kms_plane_destroy_state,
	.क्रमmat_mod_supported   = drm_simple_kms_क्रमmat_mod_supported,
पूर्ण;

/**
 * drm_simple_display_pipe_attach_bridge - Attach a bridge to the display pipe
 * @pipe: simple display pipe object
 * @bridge: bridge to attach
 *
 * Makes it possible to still use the drm_simple_display_pipe helpers when
 * a DRM bridge has to be used.
 *
 * Note that you probably want to initialize the pipe by passing a शून्य
 * connector to drm_simple_display_pipe_init().
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक drm_simple_display_pipe_attach_bridge(काष्ठा drm_simple_display_pipe *pipe,
					  काष्ठा drm_bridge *bridge)
अणु
	वापस drm_bridge_attach(&pipe->encoder, bridge, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(drm_simple_display_pipe_attach_bridge);

/**
 * drm_simple_display_pipe_init - Initialize a simple display pipeline
 * @dev: DRM device
 * @pipe: simple display pipe object to initialize
 * @funcs: callbacks क्रम the display pipe (optional)
 * @क्रमmats: array of supported क्रमmats (DRM_FORMAT\_\*)
 * @क्रमmat_count: number of elements in @क्रमmats
 * @क्रमmat_modअगरiers: array of क्रमmats modअगरiers
 * @connector: connector to attach and रेजिस्टर (optional)
 *
 * Sets up a display pipeline which consist of a really simple
 * plane-crtc-encoder pipe.
 *
 * If a connector is supplied, the pipe will be coupled with the provided
 * connector. You may supply a शून्य connector when using drm bridges, that
 * handle connectors themselves (see drm_simple_display_pipe_attach_bridge()).
 *
 * Tearकरोwn of a simple display pipe is all handled स्वतःmatically by the drm
 * core through calling drm_mode_config_cleanup(). Drivers afterwards need to
 * release the memory क्रम the काष्ठाure themselves.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक drm_simple_display_pipe_init(काष्ठा drm_device *dev,
			काष्ठा drm_simple_display_pipe *pipe,
			स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs,
			स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
			स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
			काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder = &pipe->encoder;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	पूर्णांक ret;

	pipe->connector = connector;
	pipe->funcs = funcs;

	drm_plane_helper_add(plane, &drm_simple_kms_plane_helper_funcs);
	ret = drm_universal_plane_init(dev, plane, 0,
				       &drm_simple_kms_plane_funcs,
				       क्रमmats, क्रमmat_count,
				       क्रमmat_modअगरiers,
				       DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret)
		वापस ret;

	drm_crtc_helper_add(crtc, &drm_simple_kms_crtc_helper_funcs);
	ret = drm_crtc_init_with_planes(dev, crtc, plane, शून्य,
					&drm_simple_kms_crtc_funcs, शून्य);
	अगर (ret)
		वापस ret;

	encoder->possible_crtcs = drm_crtc_mask(crtc);
	ret = drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_NONE);
	अगर (ret || !connector)
		वापस ret;

	वापस drm_connector_attach_encoder(connector, encoder);
पूर्ण
EXPORT_SYMBOL(drm_simple_display_pipe_init);

MODULE_LICENSE("GPL");
