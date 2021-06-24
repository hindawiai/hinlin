<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Noralf Trथचnnes
 */

#अगर_अघोषित __LINUX_DRM_SIMPLE_KMS_HELPER_H
#घोषणा __LINUX_DRM_SIMPLE_KMS_HELPER_H

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_plane.h>

काष्ठा drm_simple_display_pipe;

/**
 * काष्ठा drm_simple_display_pipe_funcs - helper operations क्रम a simple
 *                                        display pipeline
 */
काष्ठा drm_simple_display_pipe_funcs अणु
	/**
	 * @mode_valid:
	 *
	 * This callback is used to check अगर a specअगरic mode is valid in the
	 * crtc used in this simple display pipe. This should be implemented
	 * अगर the display pipe has some sort of restriction in the modes
	 * it can display. For example, a given display pipe may be responsible
	 * to set a घड़ी value. If the घड़ी can not produce all the values
	 * क्रम the available modes then this callback can be used to restrict
	 * the number of modes to only the ones that can be displayed. Another
	 * reason can be bandwidth mitigation: the memory port on the display
	 * controller can have bandwidth limitations not allowing pixel data
	 * to be fetched at any rate.
	 *
	 * This hook is used by the probe helpers to filter the mode list in
	 * drm_helper_probe_single_connector_modes(), and it is used by the
	 * atomic helpers to validate modes supplied by userspace in
	 * drm_atomic_helper_check_modeset().
	 *
	 * This function is optional.
	 *
	 * NOTE:
	 *
	 * Since this function is both called from the check phase of an atomic
	 * commit, and the mode validation in the probe paths it is not allowed
	 * to look at anything अन्यथा but the passed-in mode, and validate it
	 * against configuration-invariant hardware स्थिरraपूर्णांकs.
	 *
	 * RETURNS:
	 *
	 * drm_mode_status Enum
	 */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा drm_simple_display_pipe *pipe,
					   स्थिर काष्ठा drm_display_mode *mode);

	/**
	 * @enable:
	 *
	 * This function should be used to enable the pipeline.
	 * It is called when the underlying crtc is enabled.
	 * This hook is optional.
	 */
	व्योम (*enable)(काष्ठा drm_simple_display_pipe *pipe,
		       काष्ठा drm_crtc_state *crtc_state,
		       काष्ठा drm_plane_state *plane_state);
	/**
	 * @disable:
	 *
	 * This function should be used to disable the pipeline.
	 * It is called when the underlying crtc is disabled.
	 * This hook is optional.
	 */
	व्योम (*disable)(काष्ठा drm_simple_display_pipe *pipe);

	/**
	 * @check:
	 *
	 * This function is called in the check phase of an atomic update,
	 * specअगरically when the underlying plane is checked.
	 * The simple display pipeline helpers alपढ़ोy check that the plane is
	 * not scaled, fills the entire visible area and is always enabled
	 * when the crtc is also enabled.
	 * This hook is optional.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the state or the transition can't be
	 * supported, -ENOMEM on memory allocation failure and -EDEADLK अगर an
	 * attempt to obtain another state object ran पूर्णांकo a &drm_modeset_lock
	 * deadlock.
	 */
	पूर्णांक (*check)(काष्ठा drm_simple_display_pipe *pipe,
		     काष्ठा drm_plane_state *plane_state,
		     काष्ठा drm_crtc_state *crtc_state);
	/**
	 * @update:
	 *
	 * This function is called when the underlying plane state is updated.
	 * This hook is optional.
	 *
	 * This is the function drivers should submit the
	 * &drm_pending_vblank_event from. Using either
	 * drm_crtc_arm_vblank_event(), when the driver supports vblank
	 * पूर्णांकerrupt handling, or drm_crtc_send_vblank_event() क्रम more
	 * complex हाल. In हाल the hardware lacks vblank support entirely,
	 * drivers can set &काष्ठा drm_crtc_state.no_vblank in
	 * &काष्ठा drm_simple_display_pipe_funcs.check and let DRM's
	 * atomic helper fake a vblank event.
	 */
	व्योम (*update)(काष्ठा drm_simple_display_pipe *pipe,
		       काष्ठा drm_plane_state *old_plane_state);

	/**
	 * @prepare_fb:
	 *
	 * Optional, called by &drm_plane_helper_funcs.prepare_fb.  Please पढ़ो
	 * the करोcumentation क्रम the &drm_plane_helper_funcs.prepare_fb hook क्रम
	 * more details.
	 *
	 * Drivers which always have their buffers pinned should use
	 * drm_gem_simple_display_pipe_prepare_fb() क्रम this hook.
	 */
	पूर्णांक (*prepare_fb)(काष्ठा drm_simple_display_pipe *pipe,
			  काष्ठा drm_plane_state *plane_state);

	/**
	 * @cleanup_fb:
	 *
	 * Optional, called by &drm_plane_helper_funcs.cleanup_fb.  Please पढ़ो
	 * the करोcumentation क्रम the &drm_plane_helper_funcs.cleanup_fb hook क्रम
	 * more details.
	 */
	व्योम (*cleanup_fb)(काष्ठा drm_simple_display_pipe *pipe,
			   काष्ठा drm_plane_state *plane_state);

	/**
	 * @enable_vblank:
	 *
	 * Optional, called by &drm_crtc_funcs.enable_vblank. Please पढ़ो
	 * the करोcumentation क्रम the &drm_crtc_funcs.enable_vblank hook क्रम
	 * more details.
	 */
	पूर्णांक (*enable_vblank)(काष्ठा drm_simple_display_pipe *pipe);

	/**
	 * @disable_vblank:
	 *
	 * Optional, called by &drm_crtc_funcs.disable_vblank. Please पढ़ो
	 * the करोcumentation क्रम the &drm_crtc_funcs.disable_vblank hook क्रम
	 * more details.
	 */
	व्योम (*disable_vblank)(काष्ठा drm_simple_display_pipe *pipe);

	/**
	 * @reset_plane:
	 *
	 * Optional, called by &drm_plane_funcs.reset. Please पढ़ो the
	 * करोcumentation क्रम the &drm_plane_funcs.reset hook क्रम more details.
	 */
	व्योम (*reset_plane)(काष्ठा drm_simple_display_pipe *pipe);

	/**
	 * @duplicate_plane_state:
	 *
	 * Optional, called by &drm_plane_funcs.atomic_duplicate_state.  Please
	 * पढ़ो the करोcumentation क्रम the &drm_plane_funcs.atomic_duplicate_state
	 * hook क्रम more details.
	 */
	काष्ठा drm_plane_state * (*duplicate_plane_state)(काष्ठा drm_simple_display_pipe *pipe);

	/**
	 * @destroy_plane_state:
	 *
	 * Optional, called by &drm_plane_funcs.atomic_destroy_state.  Please
	 * पढ़ो the करोcumentation क्रम the &drm_plane_funcs.atomic_destroy_state
	 * hook क्रम more details.
	 */
	व्योम (*destroy_plane_state)(काष्ठा drm_simple_display_pipe *pipe,
				    काष्ठा drm_plane_state *plane_state);
पूर्ण;

/**
 * काष्ठा drm_simple_display_pipe - simple display pipeline
 * @crtc: CRTC control काष्ठाure
 * @plane: Plane control काष्ठाure
 * @encoder: Encoder control काष्ठाure
 * @connector: Connector control काष्ठाure
 * @funcs: Pipeline control functions (optional)
 *
 * Simple display pipeline with plane, crtc and encoder collapsed पूर्णांकo one
 * entity. It should be initialized by calling drm_simple_display_pipe_init().
 */
काष्ठा drm_simple_display_pipe अणु
	काष्ठा drm_crtc crtc;
	काष्ठा drm_plane plane;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_connector *connector;

	स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs;
पूर्ण;

पूर्णांक drm_simple_display_pipe_attach_bridge(काष्ठा drm_simple_display_pipe *pipe,
					  काष्ठा drm_bridge *bridge);

पूर्णांक drm_simple_display_pipe_init(काष्ठा drm_device *dev,
			काष्ठा drm_simple_display_pipe *pipe,
			स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs,
			स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
			स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
			काष्ठा drm_connector *connector);

पूर्णांक drm_simple_encoder_init(काष्ठा drm_device *dev,
			    काष्ठा drm_encoder *encoder,
			    पूर्णांक encoder_type);

व्योम *__drmm_simple_encoder_alloc(काष्ठा drm_device *dev, माप_प्रकार size,
				  माप_प्रकार offset, पूर्णांक encoder_type);

/**
 * drmm_simple_encoder_alloc - Allocate and initialize an encoder with basic
 *                             functionality.
 * @dev: drm device
 * @type: the type of the काष्ठा which contains काष्ठा &drm_encoder
 * @member: the name of the &drm_encoder within @type.
 * @encoder_type: user visible type of the encoder
 *
 * Allocates and initializes an encoder that has no further functionality.
 * Settings क्रम possible CRTC and clones are left to their initial values.
 * Cleanup is स्वतःmatically handled through रेजिस्टरing drm_encoder_cleanup()
 * with drmm_add_action().
 *
 * Returns:
 * Poपूर्णांकer to new encoder, or ERR_PTR on failure.
 */
#घोषणा drmm_simple_encoder_alloc(dev, type, member, encoder_type) \
	((type *)__drmm_simple_encoder_alloc(dev, माप(type), \
					     दुरत्व(type, member), \
					     encoder_type))

#पूर्ण_अगर /* __LINUX_DRM_SIMPLE_KMS_HELPER_H */
