<शैली गुरु>
/*
 * Copyright (C) 2014 Red Hat
 * Copyright (C) 2014 Intel Corp.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Daniel Vetter <daniel.vetter@ffwll.ch>
 */

#अगर_अघोषित DRM_ATOMIC_HELPER_H_
#घोषणा DRM_ATOMIC_HELPER_H_

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_util.h>

काष्ठा drm_atomic_state;
काष्ठा drm_निजी_obj;
काष्ठा drm_निजी_state;

पूर्णांक drm_atomic_helper_check_modeset(काष्ठा drm_device *dev,
				काष्ठा drm_atomic_state *state);
पूर्णांक drm_atomic_helper_check_plane_state(काष्ठा drm_plane_state *plane_state,
					स्थिर काष्ठा drm_crtc_state *crtc_state,
					पूर्णांक min_scale,
					पूर्णांक max_scale,
					bool can_position,
					bool can_update_disabled);
पूर्णांक drm_atomic_helper_check_planes(काष्ठा drm_device *dev,
			       काष्ठा drm_atomic_state *state);
पूर्णांक drm_atomic_helper_check(काष्ठा drm_device *dev,
			    काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_commit_tail(काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_commit_tail_rpm(काष्ठा drm_atomic_state *state);
पूर्णांक drm_atomic_helper_commit(काष्ठा drm_device *dev,
			     काष्ठा drm_atomic_state *state,
			     bool nonblock);
पूर्णांक drm_atomic_helper_async_check(काष्ठा drm_device *dev,
				  काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_async_commit(काष्ठा drm_device *dev,
				    काष्ठा drm_atomic_state *state);

पूर्णांक drm_atomic_helper_रुको_क्रम_fences(काष्ठा drm_device *dev,
					काष्ठा drm_atomic_state *state,
					bool pre_swap);

व्योम drm_atomic_helper_रुको_क्रम_vblanks(काष्ठा drm_device *dev,
					काष्ठा drm_atomic_state *old_state);

व्योम drm_atomic_helper_रुको_क्रम_flip_करोne(काष्ठा drm_device *dev,
					  काष्ठा drm_atomic_state *old_state);

व्योम
drm_atomic_helper_update_legacy_modeset_state(काष्ठा drm_device *dev,
					      काष्ठा drm_atomic_state *old_state);

व्योम
drm_atomic_helper_calc_बारtamping_स्थिरants(काष्ठा drm_atomic_state *state);

व्योम drm_atomic_helper_commit_modeset_disables(काष्ठा drm_device *dev,
					       काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_commit_modeset_enables(काष्ठा drm_device *dev,
					  काष्ठा drm_atomic_state *old_state);

पूर्णांक drm_atomic_helper_prepare_planes(काष्ठा drm_device *dev,
				     काष्ठा drm_atomic_state *state);

#घोषणा DRM_PLANE_COMMIT_ACTIVE_ONLY			BIT(0)
#घोषणा DRM_PLANE_COMMIT_NO_DISABLE_AFTER_MODESET	BIT(1)

व्योम drm_atomic_helper_commit_planes(काष्ठा drm_device *dev,
				     काष्ठा drm_atomic_state *state,
				     uपूर्णांक32_t flags);
व्योम drm_atomic_helper_cleanup_planes(काष्ठा drm_device *dev,
				      काष्ठा drm_atomic_state *old_state);
व्योम drm_atomic_helper_commit_planes_on_crtc(काष्ठा drm_crtc_state *old_crtc_state);
व्योम
drm_atomic_helper_disable_planes_on_crtc(काष्ठा drm_crtc_state *old_crtc_state,
					 bool atomic);

पूर्णांक __must_check drm_atomic_helper_swap_state(काष्ठा drm_atomic_state *state,
					      bool stall);

/* nonblocking commit helpers */
पूर्णांक drm_atomic_helper_setup_commit(काष्ठा drm_atomic_state *state,
				   bool nonblock);
व्योम drm_atomic_helper_रुको_क्रम_dependencies(काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_fake_vblank(काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_commit_hw_करोne(काष्ठा drm_atomic_state *state);
व्योम drm_atomic_helper_commit_cleanup_करोne(काष्ठा drm_atomic_state *state);

/* implementations क्रम legacy पूर्णांकerfaces */
पूर्णांक drm_atomic_helper_update_plane(काष्ठा drm_plane *plane,
				   काष्ठा drm_crtc *crtc,
				   काष्ठा drm_framebuffer *fb,
				   पूर्णांक crtc_x, पूर्णांक crtc_y,
				   अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
				   uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
				   uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
				   काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक drm_atomic_helper_disable_plane(काष्ठा drm_plane *plane,
				    काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक drm_atomic_helper_set_config(काष्ठा drm_mode_set *set,
				 काष्ठा drm_modeset_acquire_ctx *ctx);

पूर्णांक drm_atomic_helper_disable_all(काष्ठा drm_device *dev,
				  काष्ठा drm_modeset_acquire_ctx *ctx);
व्योम drm_atomic_helper_shutकरोwn(काष्ठा drm_device *dev);
काष्ठा drm_atomic_state *
drm_atomic_helper_duplicate_state(काष्ठा drm_device *dev,
				  काष्ठा drm_modeset_acquire_ctx *ctx);
काष्ठा drm_atomic_state *drm_atomic_helper_suspend(काष्ठा drm_device *dev);
पूर्णांक drm_atomic_helper_commit_duplicated_state(काष्ठा drm_atomic_state *state,
					      काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक drm_atomic_helper_resume(काष्ठा drm_device *dev,
			     काष्ठा drm_atomic_state *state);

पूर्णांक drm_atomic_helper_page_flip(काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				काष्ठा drm_pending_vblank_event *event,
				uपूर्णांक32_t flags,
				काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक drm_atomic_helper_page_flip_target(
				काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				काष्ठा drm_pending_vblank_event *event,
				uपूर्णांक32_t flags,
				uपूर्णांक32_t target,
				काष्ठा drm_modeset_acquire_ctx *ctx);

/**
 * drm_atomic_crtc_क्रम_each_plane - iterate over planes currently attached to CRTC
 * @plane: the loop cursor
 * @crtc:  the CRTC whose planes are iterated
 *
 * This iterates over the current state, useful (क्रम example) when applying
 * atomic state after it has been checked and swapped.  To iterate over the
 * planes which *will* be attached (more useful in code called from
 * &drm_mode_config_funcs.atomic_check) see
 * drm_atomic_crtc_state_क्रम_each_plane().
 */
#घोषणा drm_atomic_crtc_क्रम_each_plane(plane, crtc) \
	drm_क्रम_each_plane_mask(plane, (crtc)->dev, (crtc)->state->plane_mask)

/**
 * drm_atomic_crtc_state_क्रम_each_plane - iterate over attached planes in new state
 * @plane: the loop cursor
 * @crtc_state: the incoming CRTC state
 *
 * Similar to drm_crtc_क्रम_each_plane(), but iterates the planes that will be
 * attached अगर the specअगरied state is applied.  Useful during क्रम example
 * in code called from &drm_mode_config_funcs.atomic_check operations, to
 * validate the incoming state.
 */
#घोषणा drm_atomic_crtc_state_क्रम_each_plane(plane, crtc_state) \
	drm_क्रम_each_plane_mask(plane, (crtc_state)->state->dev, (crtc_state)->plane_mask)

/**
 * drm_atomic_crtc_state_क्रम_each_plane_state - iterate over attached planes in new state
 * @plane: the loop cursor
 * @plane_state: loop cursor क्रम the plane's state, must be स्थिर
 * @crtc_state: the incoming CRTC state
 *
 * Similar to drm_crtc_क्रम_each_plane(), but iterates the planes that will be
 * attached अगर the specअगरied state is applied.  Useful during क्रम example
 * in code called from &drm_mode_config_funcs.atomic_check operations, to
 * validate the incoming state.
 *
 * Compared to just drm_atomic_crtc_state_क्रम_each_plane() this also fills in a
 * स्थिर plane_state. This is useful when a driver just wants to peek at other
 * active planes on this CRTC, but करोes not need to change it.
 */
#घोषणा drm_atomic_crtc_state_क्रम_each_plane_state(plane, plane_state, crtc_state) \
	drm_क्रम_each_plane_mask(plane, (crtc_state)->state->dev, (crtc_state)->plane_mask) \
		क्रम_each_अगर ((plane_state = \
			      __drm_atomic_get_current_plane_state((crtc_state)->state, \
								   plane)))

/**
 * drm_atomic_plane_disabling - check whether a plane is being disabled
 * @old_plane_state: old atomic plane state
 * @new_plane_state: new atomic plane state
 *
 * Checks the atomic state of a plane to determine whether it's being disabled
 * or not. This also WARNs अगर it detects an invalid state (both CRTC and FB
 * need to either both be शून्य or both be non-शून्य).
 *
 * RETURNS:
 * True अगर the plane is being disabled, false otherwise.
 */
अटल अंतरभूत bool
drm_atomic_plane_disabling(काष्ठा drm_plane_state *old_plane_state,
			   काष्ठा drm_plane_state *new_plane_state)
अणु
	/*
	 * When disabling a plane, CRTC and FB should always be शून्य together.
	 * Anything अन्यथा should be considered a bug in the atomic core, so we
	 * gently warn about it.
	 */
	WARN_ON((new_plane_state->crtc == शून्य && new_plane_state->fb != शून्य) ||
		(new_plane_state->crtc != शून्य && new_plane_state->fb == शून्य));

	वापस old_plane_state->crtc && !new_plane_state->crtc;
पूर्ण

u32 *
drm_atomic_helper_bridge_propagate_bus_fmt(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					u32 output_fmt,
					अचिन्हित पूर्णांक *num_input_fmts);

#पूर्ण_अगर /* DRM_ATOMIC_HELPER_H_ */
