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


#समावेश <linux/sync_file.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

व्योम __drm_crtc_commit_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा drm_crtc_commit *commit =
		container_of(kref, काष्ठा drm_crtc_commit, ref);

	kमुक्त(commit);
पूर्ण
EXPORT_SYMBOL(__drm_crtc_commit_मुक्त);

/**
 * drm_crtc_commit_रुको - Waits क्रम a commit to complete
 * @commit: &drm_crtc_commit to रुको क्रम
 *
 * Waits क्रम a given &drm_crtc_commit to be programmed पूर्णांकo the
 * hardware and flipped to.
 *
 * Returns:
 *
 * 0 on success, a negative error code otherwise.
 */
पूर्णांक drm_crtc_commit_रुको(काष्ठा drm_crtc_commit *commit)
अणु
	अचिन्हित दीर्घ समयout = 10 * HZ;
	पूर्णांक ret;

	अगर (!commit)
		वापस 0;

	ret = रुको_क्रम_completion_समयout(&commit->hw_करोne, समयout);
	अगर (!ret) अणु
		DRM_ERROR("hw_done timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/*
	 * Currently no support क्रम overwriting flips, hence
	 * stall क्रम previous one to execute completely.
	 */
	ret = रुको_क्रम_completion_समयout(&commit->flip_करोne, समयout);
	अगर (!ret) अणु
		DRM_ERROR("flip_done timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_crtc_commit_रुको);

/**
 * drm_atomic_state_शेष_release -
 * release memory initialized by drm_atomic_state_init
 * @state: atomic state
 *
 * Free all the memory allocated by drm_atomic_state_init.
 * This should only be used by drivers which are still subclassing
 * &drm_atomic_state and haven't चयनed to &drm_निजी_state yet.
 */
व्योम drm_atomic_state_शेष_release(काष्ठा drm_atomic_state *state)
अणु
	kमुक्त(state->connectors);
	kमुक्त(state->crtcs);
	kमुक्त(state->planes);
	kमुक्त(state->निजी_objs);
पूर्ण
EXPORT_SYMBOL(drm_atomic_state_शेष_release);

/**
 * drm_atomic_state_init - init new atomic state
 * @dev: DRM device
 * @state: atomic state
 *
 * Default implementation क्रम filling in a new atomic state.
 * This should only be used by drivers which are still subclassing
 * &drm_atomic_state and haven't चयनed to &drm_निजी_state yet.
 */
पूर्णांक
drm_atomic_state_init(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *state)
अणु
	kref_init(&state->ref);

	/* TODO legacy paths should maybe करो a better job about
	 * setting this appropriately?
	 */
	state->allow_modeset = true;

	state->crtcs = kसुस्मृति(dev->mode_config.num_crtc,
			       माप(*state->crtcs), GFP_KERNEL);
	अगर (!state->crtcs)
		जाओ fail;
	state->planes = kसुस्मृति(dev->mode_config.num_total_plane,
				माप(*state->planes), GFP_KERNEL);
	अगर (!state->planes)
		जाओ fail;

	state->dev = dev;

	DRM_DEBUG_ATOMIC("Allocated atomic state %p\n", state);

	वापस 0;
fail:
	drm_atomic_state_शेष_release(state);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(drm_atomic_state_init);

/**
 * drm_atomic_state_alloc - allocate atomic state
 * @dev: DRM device
 *
 * This allocates an empty atomic state to track updates.
 */
काष्ठा drm_atomic_state *
drm_atomic_state_alloc(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;

	अगर (!config->funcs->atomic_state_alloc) अणु
		काष्ठा drm_atomic_state *state;

		state = kzalloc(माप(*state), GFP_KERNEL);
		अगर (!state)
			वापस शून्य;
		अगर (drm_atomic_state_init(dev, state) < 0) अणु
			kमुक्त(state);
			वापस शून्य;
		पूर्ण
		वापस state;
	पूर्ण

	वापस config->funcs->atomic_state_alloc(dev);
पूर्ण
EXPORT_SYMBOL(drm_atomic_state_alloc);

/**
 * drm_atomic_state_शेष_clear - clear base atomic state
 * @state: atomic state
 *
 * Default implementation क्रम clearing atomic state.
 * This should only be used by drivers which are still subclassing
 * &drm_atomic_state and haven't चयनed to &drm_निजी_state yet.
 */
व्योम drm_atomic_state_शेष_clear(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;
	पूर्णांक i;

	DRM_DEBUG_ATOMIC("Clearing atomic state %p\n", state);

	क्रम (i = 0; i < state->num_connector; i++) अणु
		काष्ठा drm_connector *connector = state->connectors[i].ptr;

		अगर (!connector)
			जारी;

		connector->funcs->atomic_destroy_state(connector,
						       state->connectors[i].state);
		state->connectors[i].ptr = शून्य;
		state->connectors[i].state = शून्य;
		state->connectors[i].old_state = शून्य;
		state->connectors[i].new_state = शून्य;
		drm_connector_put(connector);
	पूर्ण

	क्रम (i = 0; i < config->num_crtc; i++) अणु
		काष्ठा drm_crtc *crtc = state->crtcs[i].ptr;

		अगर (!crtc)
			जारी;

		crtc->funcs->atomic_destroy_state(crtc,
						  state->crtcs[i].state);

		state->crtcs[i].ptr = शून्य;
		state->crtcs[i].state = शून्य;
		state->crtcs[i].old_state = शून्य;
		state->crtcs[i].new_state = शून्य;

		अगर (state->crtcs[i].commit) अणु
			drm_crtc_commit_put(state->crtcs[i].commit);
			state->crtcs[i].commit = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < config->num_total_plane; i++) अणु
		काष्ठा drm_plane *plane = state->planes[i].ptr;

		अगर (!plane)
			जारी;

		plane->funcs->atomic_destroy_state(plane,
						   state->planes[i].state);
		state->planes[i].ptr = शून्य;
		state->planes[i].state = शून्य;
		state->planes[i].old_state = शून्य;
		state->planes[i].new_state = शून्य;
	पूर्ण

	क्रम (i = 0; i < state->num_निजी_objs; i++) अणु
		काष्ठा drm_निजी_obj *obj = state->निजी_objs[i].ptr;

		obj->funcs->atomic_destroy_state(obj,
						 state->निजी_objs[i].state);
		state->निजी_objs[i].ptr = शून्य;
		state->निजी_objs[i].state = शून्य;
		state->निजी_objs[i].old_state = शून्य;
		state->निजी_objs[i].new_state = शून्य;
	पूर्ण
	state->num_निजी_objs = 0;

	अगर (state->fake_commit) अणु
		drm_crtc_commit_put(state->fake_commit);
		state->fake_commit = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_state_शेष_clear);

/**
 * drm_atomic_state_clear - clear state object
 * @state: atomic state
 *
 * When the w/w mutex algorithm detects a deadlock we need to back off and drop
 * all locks. So someone अन्यथा could sneak in and change the current modeset
 * configuration. Which means that all the state assembled in @state is no
 * दीर्घer an atomic update to the current state, but to some arbitrary earlier
 * state. Which could अवरोध assumptions the driver's
 * &drm_mode_config_funcs.atomic_check likely relies on.
 *
 * Hence we must clear all cached state and completely start over, using this
 * function.
 */
व्योम drm_atomic_state_clear(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;

	अगर (config->funcs->atomic_state_clear)
		config->funcs->atomic_state_clear(state);
	अन्यथा
		drm_atomic_state_शेष_clear(state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_state_clear);

/**
 * __drm_atomic_state_मुक्त - मुक्त all memory क्रम an atomic state
 * @ref: This atomic state to deallocate
 *
 * This मुक्तs all memory associated with an atomic state, including all the
 * per-object state क्रम planes, CRTCs and connectors.
 */
व्योम __drm_atomic_state_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा drm_atomic_state *state = container_of(ref, typeof(*state), ref);
	काष्ठा drm_mode_config *config = &state->dev->mode_config;

	drm_atomic_state_clear(state);

	DRM_DEBUG_ATOMIC("Freeing atomic state %p\n", state);

	अगर (config->funcs->atomic_state_मुक्त) अणु
		config->funcs->atomic_state_मुक्त(state);
	पूर्ण अन्यथा अणु
		drm_atomic_state_शेष_release(state);
		kमुक्त(state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__drm_atomic_state_मुक्त);

/**
 * drm_atomic_get_crtc_state - get CRTC state
 * @state: global atomic state object
 * @crtc: CRTC to get state object क्रम
 *
 * This function वापसs the CRTC state क्रम the given CRTC, allocating it अगर
 * needed. It will also grab the relevant CRTC lock to make sure that the state
 * is consistent.
 *
 * WARNING: Drivers may only add new CRTC states to a @state अगर
 * drm_atomic_state.allow_modeset is set, or अगर it's a driver-पूर्णांकernal commit
 * not created by userspace through an IOCTL call.
 *
 * Returns:
 *
 * Either the allocated state or the error code encoded पूर्णांकo the poपूर्णांकer. When
 * the error is EDEADLK then the w/w mutex code has detected a deadlock and the
 * entire atomic sequence must be restarted. All other errors are fatal.
 */
काष्ठा drm_crtc_state *
drm_atomic_get_crtc_state(काष्ठा drm_atomic_state *state,
			  काष्ठा drm_crtc *crtc)
अणु
	पूर्णांक ret, index = drm_crtc_index(crtc);
	काष्ठा drm_crtc_state *crtc_state;

	WARN_ON(!state->acquire_ctx);

	crtc_state = drm_atomic_get_existing_crtc_state(state, crtc);
	अगर (crtc_state)
		वापस crtc_state;

	ret = drm_modeset_lock(&crtc->mutex, state->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	crtc_state = crtc->funcs->atomic_duplicate_state(crtc);
	अगर (!crtc_state)
		वापस ERR_PTR(-ENOMEM);

	state->crtcs[index].state = crtc_state;
	state->crtcs[index].old_state = crtc->state;
	state->crtcs[index].new_state = crtc_state;
	state->crtcs[index].ptr = crtc;
	crtc_state->state = state;

	DRM_DEBUG_ATOMIC("Added [CRTC:%d:%s] %p state to %p\n",
			 crtc->base.id, crtc->name, crtc_state, state);

	वापस crtc_state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_crtc_state);

अटल पूर्णांक drm_atomic_crtc_check(स्थिर काष्ठा drm_crtc_state *old_crtc_state,
				 स्थिर काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_crtc *crtc = new_crtc_state->crtc;

	/* NOTE: we explicitly करोn't enक्रमce स्थिरraपूर्णांकs such as primary
	 * layer covering entire screen, since that is something we want
	 * to allow (on hw that supports it).  For hw that करोes not, it
	 * should be checked in driver's crtc->atomic_check() vfunc.
	 *
	 * TODO: Add generic modeset state checks once we support those.
	 */

	अगर (new_crtc_state->active && !new_crtc_state->enable) अणु
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] active without enabled\n",
				 crtc->base.id, crtc->name);
		वापस -EINVAL;
	पूर्ण

	/* The state->enable vs. state->mode_blob checks can be WARN_ON,
	 * as this is a kernel-पूर्णांकernal detail that userspace should never
	 * be able to trigger. */
	अगर (drm_core_check_feature(crtc->dev, DRIVER_ATOMIC) &&
	    WARN_ON(new_crtc_state->enable && !new_crtc_state->mode_blob)) अणु
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] enabled without mode blob\n",
				 crtc->base.id, crtc->name);
		वापस -EINVAL;
	पूर्ण

	अगर (drm_core_check_feature(crtc->dev, DRIVER_ATOMIC) &&
	    WARN_ON(!new_crtc_state->enable && new_crtc_state->mode_blob)) अणु
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] disabled with mode blob\n",
				 crtc->base.id, crtc->name);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Reject event generation क्रम when a CRTC is off and stays off.
	 * It wouldn't be hard to implement this, but userspace has a track
	 * record of happily burning through 100% cpu (or worse, crash) when the
	 * display pipe is suspended. To aव्योम all that fun just reject updates
	 * that ask क्रम events since likely that indicates a bug in the
	 * compositor's drawing loop. This is consistent with the vblank IOCTL
	 * and legacy page_flip IOCTL which also reject service on a disabled
	 * pipe.
	 */
	अगर (new_crtc_state->event &&
	    !new_crtc_state->active && !old_crtc_state->active) अणु
		DRM_DEBUG_ATOMIC("[CRTC:%d:%s] requesting event but off\n",
				 crtc->base.id, crtc->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम drm_atomic_crtc_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
		स्थिर काष्ठा drm_crtc_state *state)
अणु
	काष्ठा drm_crtc *crtc = state->crtc;

	drm_म_लिखो(p, "crtc[%u]: %s\n", crtc->base.id, crtc->name);
	drm_म_लिखो(p, "\tenable=%d\n", state->enable);
	drm_म_लिखो(p, "\tactive=%d\n", state->active);
	drm_म_लिखो(p, "\tself_refresh_active=%d\n", state->self_refresh_active);
	drm_म_लिखो(p, "\tplanes_changed=%d\n", state->planes_changed);
	drm_म_लिखो(p, "\tmode_changed=%d\n", state->mode_changed);
	drm_म_लिखो(p, "\tactive_changed=%d\n", state->active_changed);
	drm_म_लिखो(p, "\tconnectors_changed=%d\n", state->connectors_changed);
	drm_म_लिखो(p, "\tcolor_mgmt_changed=%d\n", state->color_mgmt_changed);
	drm_म_लिखो(p, "\tplane_mask=%x\n", state->plane_mask);
	drm_म_लिखो(p, "\tconnector_mask=%x\n", state->connector_mask);
	drm_म_लिखो(p, "\tencoder_mask=%x\n", state->encoder_mask);
	drm_म_लिखो(p, "\tmode: " DRM_MODE_FMT "\n", DRM_MODE_ARG(&state->mode));

	अगर (crtc->funcs->atomic_prपूर्णांक_state)
		crtc->funcs->atomic_prपूर्णांक_state(p, state);
पूर्ण

अटल पूर्णांक drm_atomic_connector_check(काष्ठा drm_connector *connector,
		काष्ठा drm_connector_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_ग_लिखोback_job *ग_लिखोback_job = state->ग_लिखोback_job;
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;

	state->max_bpc = info->bpc ? info->bpc : 8;
	अगर (connector->max_bpc_property)
		state->max_bpc = min(state->max_bpc, state->max_requested_bpc);

	अगर ((connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK) || !ग_लिखोback_job)
		वापस 0;

	अगर (ग_लिखोback_job->fb && !state->crtc) अणु
		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] framebuffer without CRTC\n",
				 connector->base.id, connector->name);
		वापस -EINVAL;
	पूर्ण

	अगर (state->crtc)
		crtc_state = drm_atomic_get_existing_crtc_state(state->state,
								state->crtc);

	अगर (ग_लिखोback_job->fb && !crtc_state->active) अणु
		DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] has framebuffer, but [CRTC:%d] is off\n",
				 connector->base.id, connector->name,
				 state->crtc->base.id);
		वापस -EINVAL;
	पूर्ण

	अगर (!ग_लिखोback_job->fb) अणु
		अगर (ग_लिखोback_job->out_fence) अणु
			DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] requesting out-fence without framebuffer\n",
					 connector->base.id, connector->name);
			वापस -EINVAL;
		पूर्ण

		drm_ग_लिखोback_cleanup_job(ग_लिखोback_job);
		state->ग_लिखोback_job = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_atomic_get_plane_state - get plane state
 * @state: global atomic state object
 * @plane: plane to get state object क्रम
 *
 * This function वापसs the plane state क्रम the given plane, allocating it अगर
 * needed. It will also grab the relevant plane lock to make sure that the state
 * is consistent.
 *
 * Returns:
 *
 * Either the allocated state or the error code encoded पूर्णांकo the poपूर्णांकer. When
 * the error is EDEADLK then the w/w mutex code has detected a deadlock and the
 * entire atomic sequence must be restarted. All other errors are fatal.
 */
काष्ठा drm_plane_state *
drm_atomic_get_plane_state(काष्ठा drm_atomic_state *state,
			  काष्ठा drm_plane *plane)
अणु
	पूर्णांक ret, index = drm_plane_index(plane);
	काष्ठा drm_plane_state *plane_state;

	WARN_ON(!state->acquire_ctx);

	/* the legacy poपूर्णांकers should never be set */
	WARN_ON(plane->fb);
	WARN_ON(plane->old_fb);
	WARN_ON(plane->crtc);

	plane_state = drm_atomic_get_existing_plane_state(state, plane);
	अगर (plane_state)
		वापस plane_state;

	ret = drm_modeset_lock(&plane->mutex, state->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	plane_state = plane->funcs->atomic_duplicate_state(plane);
	अगर (!plane_state)
		वापस ERR_PTR(-ENOMEM);

	state->planes[index].state = plane_state;
	state->planes[index].ptr = plane;
	state->planes[index].old_state = plane->state;
	state->planes[index].new_state = plane_state;
	plane_state->state = state;

	DRM_DEBUG_ATOMIC("Added [PLANE:%d:%s] %p state to %p\n",
			 plane->base.id, plane->name, plane_state, state);

	अगर (plane_state->crtc) अणु
		काष्ठा drm_crtc_state *crtc_state;

		crtc_state = drm_atomic_get_crtc_state(state,
						       plane_state->crtc);
		अगर (IS_ERR(crtc_state))
			वापस ERR_CAST(crtc_state);
	पूर्ण

	वापस plane_state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_plane_state);

अटल bool
plane_चयनing_crtc(स्थिर काष्ठा drm_plane_state *old_plane_state,
		     स्थिर काष्ठा drm_plane_state *new_plane_state)
अणु
	अगर (!old_plane_state->crtc || !new_plane_state->crtc)
		वापस false;

	अगर (old_plane_state->crtc == new_plane_state->crtc)
		वापस false;

	/* This could be refined, but currently there's no helper or driver code
	 * to implement direct चयनing of active planes nor userspace to take
	 * advantage of more direct plane चयनing without the पूर्णांकermediate
	 * full OFF state.
	 */
	वापस true;
पूर्ण

/**
 * drm_atomic_plane_check - check plane state
 * @old_plane_state: old plane state to check
 * @new_plane_state: new plane state to check
 *
 * Provides core sanity checks क्रम plane state.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
अटल पूर्णांक drm_atomic_plane_check(स्थिर काष्ठा drm_plane_state *old_plane_state,
				  स्थिर काष्ठा drm_plane_state *new_plane_state)
अणु
	काष्ठा drm_plane *plane = new_plane_state->plane;
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	स्थिर काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	अचिन्हित पूर्णांक fb_width, fb_height;
	काष्ठा drm_mode_rect *clips;
	uपूर्णांक32_t num_clips;
	पूर्णांक ret;

	/* either *both* CRTC and FB must be set, or neither */
	अगर (crtc && !fb) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] CRTC set but no FB\n",
				 plane->base.id, plane->name);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (fb && !crtc) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] FB set but no CRTC\n",
				 plane->base.id, plane->name);
		वापस -EINVAL;
	पूर्ण

	/* अगर disabled, we करोn't care about the rest of the state: */
	अगर (!crtc)
		वापस 0;

	/* Check whether this plane is usable on this CRTC */
	अगर (!(plane->possible_crtcs & drm_crtc_mask(crtc))) अणु
		DRM_DEBUG_ATOMIC("Invalid [CRTC:%d:%s] for [PLANE:%d:%s]\n",
				 crtc->base.id, crtc->name,
				 plane->base.id, plane->name);
		वापस -EINVAL;
	पूर्ण

	/* Check whether this plane supports the fb pixel क्रमmat. */
	ret = drm_plane_check_pixel_क्रमmat(plane, fb->क्रमmat->क्रमmat,
					   fb->modअगरier);
	अगर (ret) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid pixel format %p4cc, modifier 0x%llx\n",
				 plane->base.id, plane->name,
				 &fb->क्रमmat->क्रमmat, fb->modअगरier);
		वापस ret;
	पूर्ण

	/* Give drivers some help against पूर्णांकeger overflows */
	अगर (new_plane_state->crtc_w > पूर्णांक_उच्च ||
	    new_plane_state->crtc_x > पूर्णांक_उच्च - (पूर्णांक32_t) new_plane_state->crtc_w ||
	    new_plane_state->crtc_h > पूर्णांक_उच्च ||
	    new_plane_state->crtc_y > पूर्णांक_उच्च - (पूर्णांक32_t) new_plane_state->crtc_h) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid CRTC coordinates %ux%u+%d+%d\n",
				 plane->base.id, plane->name,
				 new_plane_state->crtc_w, new_plane_state->crtc_h,
				 new_plane_state->crtc_x, new_plane_state->crtc_y);
		वापस -दुस्फल;
	पूर्ण

	fb_width = fb->width << 16;
	fb_height = fb->height << 16;

	/* Make sure source coordinates are inside the fb. */
	अगर (new_plane_state->src_w > fb_width ||
	    new_plane_state->src_x > fb_width - new_plane_state->src_w ||
	    new_plane_state->src_h > fb_height ||
	    new_plane_state->src_y > fb_height - new_plane_state->src_h) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid source coordinates "
				 "%u.%06ux%u.%06u+%u.%06u+%u.%06u (fb %ux%u)\n",
				 plane->base.id, plane->name,
				 new_plane_state->src_w >> 16,
				 ((new_plane_state->src_w & 0xffff) * 15625) >> 10,
				 new_plane_state->src_h >> 16,
				 ((new_plane_state->src_h & 0xffff) * 15625) >> 10,
				 new_plane_state->src_x >> 16,
				 ((new_plane_state->src_x & 0xffff) * 15625) >> 10,
				 new_plane_state->src_y >> 16,
				 ((new_plane_state->src_y & 0xffff) * 15625) >> 10,
				 fb->width, fb->height);
		वापस -ENOSPC;
	पूर्ण

	clips = drm_plane_get_damage_clips(new_plane_state);
	num_clips = drm_plane_get_damage_clips_count(new_plane_state);

	/* Make sure damage clips are valid and inside the fb. */
	जबतक (num_clips > 0) अणु
		अगर (clips->x1 >= clips->x2 ||
		    clips->y1 >= clips->y2 ||
		    clips->x1 < 0 ||
		    clips->y1 < 0 ||
		    clips->x2 > fb_width ||
		    clips->y2 > fb_height) अणु
			DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid damage clip %d %d %d %d\n",
					 plane->base.id, plane->name, clips->x1,
					 clips->y1, clips->x2, clips->y2);
			वापस -EINVAL;
		पूर्ण
		clips++;
		num_clips--;
	पूर्ण

	अगर (plane_चयनing_crtc(old_plane_state, new_plane_state)) अणु
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] switching CRTC directly\n",
				 plane->base.id, plane->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम drm_atomic_plane_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
		स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_plane *plane = state->plane;
	काष्ठा drm_rect src  = drm_plane_state_src(state);
	काष्ठा drm_rect dest = drm_plane_state_dest(state);

	drm_म_लिखो(p, "plane[%u]: %s\n", plane->base.id, plane->name);
	drm_म_लिखो(p, "\tcrtc=%s\n", state->crtc ? state->crtc->name : "(null)");
	drm_म_लिखो(p, "\tfb=%u\n", state->fb ? state->fb->base.id : 0);
	अगर (state->fb)
		drm_framebuffer_prपूर्णांक_info(p, 2, state->fb);
	drm_म_लिखो(p, "\tcrtc-pos=" DRM_RECT_FMT "\n", DRM_RECT_ARG(&dest));
	drm_म_लिखो(p, "\tsrc-pos=" DRM_RECT_FP_FMT "\n", DRM_RECT_FP_ARG(&src));
	drm_म_लिखो(p, "\trotation=%x\n", state->rotation);
	drm_म_लिखो(p, "\tnormalized-zpos=%x\n", state->normalized_zpos);
	drm_म_लिखो(p, "\tcolor-encoding=%s\n",
		   drm_get_color_encoding_name(state->color_encoding));
	drm_म_लिखो(p, "\tcolor-range=%s\n",
		   drm_get_color_range_name(state->color_range));

	अगर (plane->funcs->atomic_prपूर्णांक_state)
		plane->funcs->atomic_prपूर्णांक_state(p, state);
पूर्ण

/**
 * DOC: handling driver निजी state
 *
 * Very often the DRM objects exposed to userspace in the atomic modeset api
 * (&drm_connector, &drm_crtc and &drm_plane) करो not map neatly to the
 * underlying hardware. Especially क्रम any kind of shared resources (e.g. shared
 * घड़ीs, scaler units, bandwidth and fअगरo limits shared among a group of
 * planes or CRTCs, and so on) it makes sense to model these as independent
 * objects. Drivers then need to करो similar state tracking and commit ordering क्रम
 * such निजी (since not exposed to userpace) objects as the atomic core and
 * helpers alपढ़ोy provide क्रम connectors, planes and CRTCs.
 *
 * To make this easier on drivers the atomic core provides some support to track
 * driver निजी state objects using काष्ठा &drm_निजी_obj, with the
 * associated state काष्ठा &drm_निजी_state.
 *
 * Similar to userspace-exposed objects, निजी state काष्ठाures can be
 * acquired by calling drm_atomic_get_निजी_obj_state(). This also takes care
 * of locking, hence drivers should not have a need to call drm_modeset_lock()
 * directly. Sequence of the actual hardware state commit is not handled,
 * drivers might need to keep track of काष्ठा drm_crtc_commit within subclassed
 * काष्ठाure of &drm_निजी_state as necessary, e.g. similar to
 * &drm_plane_state.commit. See also &drm_atomic_state.fake_commit.
 *
 * All निजी state काष्ठाures contained in a &drm_atomic_state update can be
 * iterated using क्रम_each_oldnew_निजी_obj_in_state(),
 * क्रम_each_new_निजी_obj_in_state() and क्रम_each_old_निजी_obj_in_state().
 * Drivers are recommended to wrap these क्रम each type of driver निजी state
 * object they have, filtering on &drm_निजी_obj.funcs using क्रम_each_अगर(), at
 * least अगर they want to iterate over all objects of a given type.
 *
 * An earlier way to handle driver निजी state was by subclassing काष्ठा
 * &drm_atomic_state. But since that encourages non-standard ways to implement
 * the check/commit split atomic requires (by using e.g. "check and rollback or
 * commit instead" of "duplicate state, check, then either commit or release
 * duplicated state) it is deprecated in favour of using &drm_निजी_state.
 */

/**
 * drm_atomic_निजी_obj_init - initialize निजी object
 * @dev: DRM device this object will be attached to
 * @obj: निजी object
 * @state: initial निजी object state
 * @funcs: poपूर्णांकer to the काष्ठा of function poपूर्णांकers that identअगरy the object
 * type
 *
 * Initialize the निजी object, which can be embedded पूर्णांकo any
 * driver निजी object that needs its own atomic state.
 */
व्योम
drm_atomic_निजी_obj_init(काष्ठा drm_device *dev,
			    काष्ठा drm_निजी_obj *obj,
			    काष्ठा drm_निजी_state *state,
			    स्थिर काष्ठा drm_निजी_state_funcs *funcs)
अणु
	स_रखो(obj, 0, माप(*obj));

	drm_modeset_lock_init(&obj->lock);

	obj->state = state;
	obj->funcs = funcs;
	list_add_tail(&obj->head, &dev->mode_config.privobj_list);
पूर्ण
EXPORT_SYMBOL(drm_atomic_निजी_obj_init);

/**
 * drm_atomic_निजी_obj_fini - finalize निजी object
 * @obj: निजी object
 *
 * Finalize the निजी object.
 */
व्योम
drm_atomic_निजी_obj_fini(काष्ठा drm_निजी_obj *obj)
अणु
	list_del(&obj->head);
	obj->funcs->atomic_destroy_state(obj, obj->state);
	drm_modeset_lock_fini(&obj->lock);
पूर्ण
EXPORT_SYMBOL(drm_atomic_निजी_obj_fini);

/**
 * drm_atomic_get_निजी_obj_state - get निजी object state
 * @state: global atomic state
 * @obj: निजी object to get the state क्रम
 *
 * This function वापसs the निजी object state क्रम the given निजी object,
 * allocating the state अगर needed. It will also grab the relevant निजी
 * object lock to make sure that the state is consistent.
 *
 * RETURNS:
 *
 * Either the allocated state or the error code encoded पूर्णांकo a poपूर्णांकer.
 */
काष्ठा drm_निजी_state *
drm_atomic_get_निजी_obj_state(काष्ठा drm_atomic_state *state,
				 काष्ठा drm_निजी_obj *obj)
अणु
	पूर्णांक index, num_objs, i, ret;
	माप_प्रकार size;
	काष्ठा __drm_निजी_objs_state *arr;
	काष्ठा drm_निजी_state *obj_state;

	क्रम (i = 0; i < state->num_निजी_objs; i++)
		अगर (obj == state->निजी_objs[i].ptr)
			वापस state->निजी_objs[i].state;

	ret = drm_modeset_lock(&obj->lock, state->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	num_objs = state->num_निजी_objs + 1;
	size = माप(*state->निजी_objs) * num_objs;
	arr = kपुनः_स्मृति(state->निजी_objs, size, GFP_KERNEL);
	अगर (!arr)
		वापस ERR_PTR(-ENOMEM);

	state->निजी_objs = arr;
	index = state->num_निजी_objs;
	स_रखो(&state->निजी_objs[index], 0, माप(*state->निजी_objs));

	obj_state = obj->funcs->atomic_duplicate_state(obj);
	अगर (!obj_state)
		वापस ERR_PTR(-ENOMEM);

	state->निजी_objs[index].state = obj_state;
	state->निजी_objs[index].old_state = obj->state;
	state->निजी_objs[index].new_state = obj_state;
	state->निजी_objs[index].ptr = obj;
	obj_state->state = state;

	state->num_निजी_objs = num_objs;

	DRM_DEBUG_ATOMIC("Added new private object %p state %p to %p\n",
			 obj, obj_state, state);

	वापस obj_state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_निजी_obj_state);

/**
 * drm_atomic_get_old_निजी_obj_state
 * @state: global atomic state object
 * @obj: निजी_obj to grab
 *
 * This function वापसs the old निजी object state क्रम the given निजी_obj,
 * or शून्य अगर the निजी_obj is not part of the global atomic state.
 */
काष्ठा drm_निजी_state *
drm_atomic_get_old_निजी_obj_state(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_निजी_obj *obj)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < state->num_निजी_objs; i++)
		अगर (obj == state->निजी_objs[i].ptr)
			वापस state->निजी_objs[i].old_state;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_old_निजी_obj_state);

/**
 * drm_atomic_get_new_निजी_obj_state
 * @state: global atomic state object
 * @obj: निजी_obj to grab
 *
 * This function वापसs the new निजी object state क्रम the given निजी_obj,
 * or शून्य अगर the निजी_obj is not part of the global atomic state.
 */
काष्ठा drm_निजी_state *
drm_atomic_get_new_निजी_obj_state(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_निजी_obj *obj)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < state->num_निजी_objs; i++)
		अगर (obj == state->निजी_objs[i].ptr)
			वापस state->निजी_objs[i].new_state;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_new_निजी_obj_state);

/**
 * drm_atomic_get_old_connector_क्रम_encoder - Get old connector क्रम an encoder
 * @state: Atomic state
 * @encoder: The encoder to fetch the connector state क्रम
 *
 * This function finds and वापसs the connector that was connected to @encoder
 * as specअगरied by the @state.
 *
 * If there is no connector in @state which previously had @encoder connected to
 * it, this function will वापस शून्य. While this may seem like an invalid use
 * हाल, it is someबार useful to dअगरferentiate commits which had no prior
 * connectors attached to @encoder vs ones that did (and to inspect their
 * state). This is especially true in enable hooks because the pipeline has
 * changed.
 *
 * Returns: The old connector connected to @encoder, or शून्य अगर the encoder is
 * not connected.
 */
काष्ठा drm_connector *
drm_atomic_get_old_connector_क्रम_encoder(काष्ठा drm_atomic_state *state,
					 काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *connector;
	अचिन्हित पूर्णांक i;

	क्रम_each_old_connector_in_state(state, connector, conn_state, i) अणु
		अगर (conn_state->best_encoder == encoder)
			वापस connector;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_old_connector_क्रम_encoder);

/**
 * drm_atomic_get_new_connector_क्रम_encoder - Get new connector क्रम an encoder
 * @state: Atomic state
 * @encoder: The encoder to fetch the connector state क्रम
 *
 * This function finds and वापसs the connector that will be connected to
 * @encoder as specअगरied by the @state.
 *
 * If there is no connector in @state which will have @encoder connected to it,
 * this function will वापस शून्य. While this may seem like an invalid use हाल,
 * it is someबार useful to dअगरferentiate commits which have no connectors
 * attached to @encoder vs ones that करो (and to inspect their state). This is
 * especially true in disable hooks because the pipeline will change.
 *
 * Returns: The new connector connected to @encoder, or शून्य अगर the encoder is
 * not connected.
 */
काष्ठा drm_connector *
drm_atomic_get_new_connector_क्रम_encoder(काष्ठा drm_atomic_state *state,
					 काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *connector;
	अचिन्हित पूर्णांक i;

	क्रम_each_new_connector_in_state(state, connector, conn_state, i) अणु
		अगर (conn_state->best_encoder == encoder)
			वापस connector;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_new_connector_क्रम_encoder);

/**
 * drm_atomic_get_connector_state - get connector state
 * @state: global atomic state object
 * @connector: connector to get state object क्रम
 *
 * This function वापसs the connector state क्रम the given connector,
 * allocating it अगर needed. It will also grab the relevant connector lock to
 * make sure that the state is consistent.
 *
 * Returns:
 *
 * Either the allocated state or the error code encoded पूर्णांकo the poपूर्णांकer. When
 * the error is EDEADLK then the w/w mutex code has detected a deadlock and the
 * entire atomic sequence must be restarted. All other errors are fatal.
 */
काष्ठा drm_connector_state *
drm_atomic_get_connector_state(काष्ठा drm_atomic_state *state,
			  काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret, index;
	काष्ठा drm_mode_config *config = &connector->dev->mode_config;
	काष्ठा drm_connector_state *connector_state;

	WARN_ON(!state->acquire_ctx);

	ret = drm_modeset_lock(&config->connection_mutex, state->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	index = drm_connector_index(connector);

	अगर (index >= state->num_connector) अणु
		काष्ठा __drm_connnectors_state *c;
		पूर्णांक alloc = max(index + 1, config->num_connector);

		c = kपुनः_स्मृति_array(state->connectors, alloc,
				   माप(*state->connectors), GFP_KERNEL);
		अगर (!c)
			वापस ERR_PTR(-ENOMEM);

		state->connectors = c;
		स_रखो(&state->connectors[state->num_connector], 0,
		       माप(*state->connectors) * (alloc - state->num_connector));

		state->num_connector = alloc;
	पूर्ण

	अगर (state->connectors[index].state)
		वापस state->connectors[index].state;

	connector_state = connector->funcs->atomic_duplicate_state(connector);
	अगर (!connector_state)
		वापस ERR_PTR(-ENOMEM);

	drm_connector_get(connector);
	state->connectors[index].state = connector_state;
	state->connectors[index].old_state = connector->state;
	state->connectors[index].new_state = connector_state;
	state->connectors[index].ptr = connector;
	connector_state->state = state;

	DRM_DEBUG_ATOMIC("Added [CONNECTOR:%d:%s] %p state to %p\n",
			 connector->base.id, connector->name,
			 connector_state, state);

	अगर (connector_state->crtc) अणु
		काष्ठा drm_crtc_state *crtc_state;

		crtc_state = drm_atomic_get_crtc_state(state,
						       connector_state->crtc);
		अगर (IS_ERR(crtc_state))
			वापस ERR_CAST(crtc_state);
	पूर्ण

	वापस connector_state;
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_connector_state);

अटल व्योम drm_atomic_connector_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
		स्थिर काष्ठा drm_connector_state *state)
अणु
	काष्ठा drm_connector *connector = state->connector;

	drm_म_लिखो(p, "connector[%u]: %s\n", connector->base.id, connector->name);
	drm_म_लिखो(p, "\tcrtc=%s\n", state->crtc ? state->crtc->name : "(null)");
	drm_म_लिखो(p, "\tself_refresh_aware=%d\n", state->self_refresh_aware);

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_WRITEBACK)
		अगर (state->ग_लिखोback_job && state->ग_लिखोback_job->fb)
			drm_म_लिखो(p, "\tfb=%d\n", state->ग_लिखोback_job->fb->base.id);

	अगर (connector->funcs->atomic_prपूर्णांक_state)
		connector->funcs->atomic_prपूर्णांक_state(p, state);
पूर्ण

/**
 * drm_atomic_get_bridge_state - get bridge state
 * @state: global atomic state object
 * @bridge: bridge to get state object क्रम
 *
 * This function वापसs the bridge state क्रम the given bridge, allocating it
 * अगर needed. It will also grab the relevant bridge lock to make sure that the
 * state is consistent.
 *
 * Returns:
 *
 * Either the allocated state or the error code encoded पूर्णांकo the poपूर्णांकer. When
 * the error is EDEADLK then the w/w mutex code has detected a deadlock and the
 * entire atomic sequence must be restarted.
 */
काष्ठा drm_bridge_state *
drm_atomic_get_bridge_state(काष्ठा drm_atomic_state *state,
			    काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_निजी_state *obj_state;

	obj_state = drm_atomic_get_निजी_obj_state(state, &bridge->base);
	अगर (IS_ERR(obj_state))
		वापस ERR_CAST(obj_state);

	वापस drm_priv_to_bridge_state(obj_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_bridge_state);

/**
 * drm_atomic_get_old_bridge_state - get old bridge state, अगर it exists
 * @state: global atomic state object
 * @bridge: bridge to grab
 *
 * This function वापसs the old bridge state क्रम the given bridge, or शून्य अगर
 * the bridge is not part of the global atomic state.
 */
काष्ठा drm_bridge_state *
drm_atomic_get_old_bridge_state(काष्ठा drm_atomic_state *state,
				काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_निजी_state *obj_state;

	obj_state = drm_atomic_get_old_निजी_obj_state(state, &bridge->base);
	अगर (!obj_state)
		वापस शून्य;

	वापस drm_priv_to_bridge_state(obj_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_old_bridge_state);

/**
 * drm_atomic_get_new_bridge_state - get new bridge state, अगर it exists
 * @state: global atomic state object
 * @bridge: bridge to grab
 *
 * This function वापसs the new bridge state क्रम the given bridge, or शून्य अगर
 * the bridge is not part of the global atomic state.
 */
काष्ठा drm_bridge_state *
drm_atomic_get_new_bridge_state(काष्ठा drm_atomic_state *state,
				काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_निजी_state *obj_state;

	obj_state = drm_atomic_get_new_निजी_obj_state(state, &bridge->base);
	अगर (!obj_state)
		वापस शून्य;

	वापस drm_priv_to_bridge_state(obj_state);
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_new_bridge_state);

/**
 * drm_atomic_add_encoder_bridges - add bridges attached to an encoder
 * @state: atomic state
 * @encoder: DRM encoder
 *
 * This function adds all bridges attached to @encoder. This is needed to add
 * bridge states to @state and make them available when
 * &drm_bridge_funcs.atomic_check(), &drm_bridge_funcs.atomic_pre_enable(),
 * &drm_bridge_funcs.atomic_enable(),
 * &drm_bridge_funcs.atomic_disable_post_disable() are called.
 *
 * Returns:
 * 0 on success or can fail with -EDEADLK or -ENOMEM. When the error is EDEADLK
 * then the w/w mutex code has detected a deadlock and the entire atomic
 * sequence must be restarted. All other errors are fatal.
 */
पूर्णांक
drm_atomic_add_encoder_bridges(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_bridge_state *bridge_state;
	काष्ठा drm_bridge *bridge;

	अगर (!encoder)
		वापस 0;

	DRM_DEBUG_ATOMIC("Adding all bridges for [encoder:%d:%s] to %p\n",
			 encoder->base.id, encoder->name, state);

	drm_क्रम_each_bridge_in_chain(encoder, bridge) अणु
		/* Skip bridges that करोn't implement the atomic state hooks. */
		अगर (!bridge->funcs->atomic_duplicate_state)
			जारी;

		bridge_state = drm_atomic_get_bridge_state(state, bridge);
		अगर (IS_ERR(bridge_state))
			वापस PTR_ERR(bridge_state);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_add_encoder_bridges);

/**
 * drm_atomic_add_affected_connectors - add connectors क्रम CRTC
 * @state: atomic state
 * @crtc: DRM CRTC
 *
 * This function walks the current configuration and adds all connectors
 * currently using @crtc to the atomic configuration @state. Note that this
 * function must acquire the connection mutex. This can potentially cause
 * unneeded serialization अगर the update is just क्रम the planes on one CRTC. Hence
 * drivers and helpers should only call this when really needed (e.g. when a
 * full modeset needs to happen due to some change).
 *
 * Returns:
 * 0 on success or can fail with -EDEADLK or -ENOMEM. When the error is EDEADLK
 * then the w/w mutex code has detected a deadlock and the entire atomic
 * sequence must be restarted. All other errors are fatal.
 */
पूर्णांक
drm_atomic_add_affected_connectors(काष्ठा drm_atomic_state *state,
				   काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_mode_config *config = &state->dev->mode_config;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	ret = drm_modeset_lock(&config->connection_mutex, state->acquire_ctx);
	अगर (ret)
		वापस ret;

	DRM_DEBUG_ATOMIC("Adding all current connectors for [CRTC:%d:%s] to %p\n",
			 crtc->base.id, crtc->name, state);

	/*
	 * Changed connectors are alपढ़ोy in @state, so only need to look
	 * at the connector_mask in crtc_state.
	 */
	drm_connector_list_iter_begin(state->dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (!(crtc_state->connector_mask & drm_connector_mask(connector)))
			जारी;

		conn_state = drm_atomic_get_connector_state(state, connector);
		अगर (IS_ERR(conn_state)) अणु
			drm_connector_list_iter_end(&conn_iter);
			वापस PTR_ERR(conn_state);
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_add_affected_connectors);

/**
 * drm_atomic_add_affected_planes - add planes क्रम CRTC
 * @state: atomic state
 * @crtc: DRM CRTC
 *
 * This function walks the current configuration and adds all planes
 * currently used by @crtc to the atomic configuration @state. This is useful
 * when an atomic commit also needs to check all currently enabled plane on
 * @crtc, e.g. when changing the mode. It's also useful when re-enabling a CRTC
 * to aव्योम special code to क्रमce-enable all planes.
 *
 * Since acquiring a plane state will always also acquire the w/w mutex of the
 * current CRTC क्रम that plane (अगर there is any) adding all the plane states क्रम
 * a CRTC will not reduce parallelism of atomic updates.
 *
 * Returns:
 * 0 on success or can fail with -EDEADLK or -ENOMEM. When the error is EDEADLK
 * then the w/w mutex code has detected a deadlock and the entire atomic
 * sequence must be restarted. All other errors are fatal.
 */
पूर्णांक
drm_atomic_add_affected_planes(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_crtc *crtc)
अणु
	स्थिर काष्ठा drm_crtc_state *old_crtc_state =
		drm_atomic_get_old_crtc_state(state, crtc);
	काष्ठा drm_plane *plane;

	WARN_ON(!drm_atomic_get_new_crtc_state(state, crtc));

	DRM_DEBUG_ATOMIC("Adding all current planes for [CRTC:%d:%s] to %p\n",
			 crtc->base.id, crtc->name, state);

	drm_क्रम_each_plane_mask(plane, state->dev, old_crtc_state->plane_mask) अणु
		काष्ठा drm_plane_state *plane_state =
			drm_atomic_get_plane_state(state, plane);

		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_add_affected_planes);

/**
 * drm_atomic_check_only - check whether a given config would work
 * @state: atomic configuration to check
 *
 * Note that this function can वापस -EDEADLK अगर the driver needed to acquire
 * more locks but encountered a deadlock. The caller must then करो the usual w/w
 * backoff dance and restart. All other errors are fatal.
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_atomic_check_only(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state;
	काष्ठा drm_plane_state *new_plane_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *conn_state;
	अचिन्हित requested_crtc = 0;
	अचिन्हित affected_crtc = 0;
	पूर्णांक i, ret = 0;

	DRM_DEBUG_ATOMIC("checking %p\n", state);

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i)
		requested_crtc |= drm_crtc_mask(crtc);

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		ret = drm_atomic_plane_check(old_plane_state, new_plane_state);
		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("[PLANE:%d:%s] atomic core check failed\n",
					 plane->base.id, plane->name);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		ret = drm_atomic_crtc_check(old_crtc_state, new_crtc_state);
		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("[CRTC:%d:%s] atomic core check failed\n",
					 crtc->base.id, crtc->name);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_new_connector_in_state(state, conn, conn_state, i) अणु
		ret = drm_atomic_connector_check(conn, conn_state);
		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] atomic core check failed\n",
					 conn->base.id, conn->name);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (config->funcs->atomic_check) अणु
		ret = config->funcs->atomic_check(state->dev, state);

		अगर (ret) अणु
			DRM_DEBUG_ATOMIC("atomic driver check for %p failed: %d\n",
					 state, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!state->allow_modeset) अणु
		क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
			अगर (drm_atomic_crtc_needs_modeset(new_crtc_state)) अणु
				DRM_DEBUG_ATOMIC("[CRTC:%d:%s] requires full modeset\n",
						 crtc->base.id, crtc->name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i)
		affected_crtc |= drm_crtc_mask(crtc);

	/*
	 * For commits that allow modesets drivers can add other CRTCs to the
	 * atomic commit, e.g. when they need to पुनः_स्मृतिate global resources.
	 * This can cause spurious EBUSY, which robs compositors of a very
	 * effective sanity check क्रम their drawing loop. Thereक्रम only allow
	 * drivers to add unrelated CRTC states क्रम modeset commits.
	 *
	 * FIXME: Should add affected_crtc mask to the ATOMIC IOCTL as an output
	 * so compositors know what's going on.
	 */
	अगर (affected_crtc != requested_crtc) अणु
		DRM_DEBUG_ATOMIC("driver added CRTC to commit: requested 0x%x, affected 0x%0x\n",
				 requested_crtc, affected_crtc);
		WARN(!state->allow_modeset, "adding CRTC not allowed without modesets: requested 0x%x, affected 0x%0x\n",
		     requested_crtc, affected_crtc);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_check_only);

/**
 * drm_atomic_commit - commit configuration atomically
 * @state: atomic configuration to check
 *
 * Note that this function can वापस -EDEADLK अगर the driver needed to acquire
 * more locks but encountered a deadlock. The caller must then करो the usual w/w
 * backoff dance and restart. All other errors are fatal.
 *
 * This function will take its own reference on @state.
 * Callers should always release their reference with drm_atomic_state_put().
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_atomic_commit(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_mode_config *config = &state->dev->mode_config;
	पूर्णांक ret;

	ret = drm_atomic_check_only(state);
	अगर (ret)
		वापस ret;

	DRM_DEBUG_ATOMIC("committing %p\n", state);

	वापस config->funcs->atomic_commit(state->dev, state, false);
पूर्ण
EXPORT_SYMBOL(drm_atomic_commit);

/**
 * drm_atomic_nonblocking_commit - atomic nonblocking commit
 * @state: atomic configuration to check
 *
 * Note that this function can वापस -EDEADLK अगर the driver needed to acquire
 * more locks but encountered a deadlock. The caller must then करो the usual w/w
 * backoff dance and restart. All other errors are fatal.
 *
 * This function will take its own reference on @state.
 * Callers should always release their reference with drm_atomic_state_put().
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_atomic_nonblocking_commit(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_mode_config *config = &state->dev->mode_config;
	पूर्णांक ret;

	ret = drm_atomic_check_only(state);
	अगर (ret)
		वापस ret;

	DRM_DEBUG_ATOMIC("committing %p nonblocking\n", state);

	वापस config->funcs->atomic_commit(state->dev, state, true);
पूर्ण
EXPORT_SYMBOL(drm_atomic_nonblocking_commit);

/* just used from drm-client and atomic-helper: */
पूर्णांक __drm_atomic_helper_disable_plane(काष्ठा drm_plane *plane,
				      काष्ठा drm_plane_state *plane_state)
अणु
	पूर्णांक ret;

	ret = drm_atomic_set_crtc_क्रम_plane(plane_state, शून्य);
	अगर (ret != 0)
		वापस ret;

	drm_atomic_set_fb_क्रम_plane(plane_state, शून्य);
	plane_state->crtc_x = 0;
	plane_state->crtc_y = 0;
	plane_state->crtc_w = 0;
	plane_state->crtc_h = 0;
	plane_state->src_x = 0;
	plane_state->src_y = 0;
	plane_state->src_w = 0;
	plane_state->src_h = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_disable_plane);

अटल पूर्णांक update_output_state(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_mode_set *set)
अणु
	काष्ठा drm_device *dev = set->crtc->dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	पूर्णांक ret, i;

	ret = drm_modeset_lock(&dev->mode_config.connection_mutex,
			       state->acquire_ctx);
	अगर (ret)
		वापस ret;

	/* First disable all connectors on the target crtc. */
	ret = drm_atomic_add_affected_connectors(state, set->crtc);
	अगर (ret)
		वापस ret;

	क्रम_each_new_connector_in_state(state, connector, new_conn_state, i) अणु
		अगर (new_conn_state->crtc == set->crtc) अणु
			ret = drm_atomic_set_crtc_क्रम_connector(new_conn_state,
								शून्य);
			अगर (ret)
				वापस ret;

			/* Make sure legacy setCrtc always re-trains */
			new_conn_state->link_status = DRM_LINK_STATUS_GOOD;
		पूर्ण
	पूर्ण

	/* Then set all connectors from set->connectors on the target crtc */
	क्रम (i = 0; i < set->num_connectors; i++) अणु
		new_conn_state = drm_atomic_get_connector_state(state,
								set->connectors[i]);
		अगर (IS_ERR(new_conn_state))
			वापस PTR_ERR(new_conn_state);

		ret = drm_atomic_set_crtc_क्रम_connector(new_conn_state,
							set->crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		/*
		 * Don't update ->enable क्रम the CRTC in the set_config request,
		 * since a mismatch would indicate a bug in the upper layers.
		 * The actual modeset code later on will catch any
		 * inconsistencies here.
		 */
		अगर (crtc == set->crtc)
			जारी;

		अगर (!new_crtc_state->connector_mask) अणु
			ret = drm_atomic_set_mode_prop_क्रम_crtc(new_crtc_state,
								शून्य);
			अगर (ret < 0)
				वापस ret;

			new_crtc_state->active = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* just used from drm-client and atomic-helper: */
पूर्णांक __drm_atomic_helper_set_config(काष्ठा drm_mode_set *set,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_plane_state *primary_state;
	काष्ठा drm_crtc *crtc = set->crtc;
	पूर्णांक hdisplay, vdisplay;
	पूर्णांक ret;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	primary_state = drm_atomic_get_plane_state(state, crtc->primary);
	अगर (IS_ERR(primary_state))
		वापस PTR_ERR(primary_state);

	अगर (!set->mode) अणु
		WARN_ON(set->fb);
		WARN_ON(set->num_connectors);

		ret = drm_atomic_set_mode_क्रम_crtc(crtc_state, शून्य);
		अगर (ret != 0)
			वापस ret;

		crtc_state->active = false;

		ret = drm_atomic_set_crtc_क्रम_plane(primary_state, शून्य);
		अगर (ret != 0)
			वापस ret;

		drm_atomic_set_fb_क्रम_plane(primary_state, शून्य);

		जाओ commit;
	पूर्ण

	WARN_ON(!set->fb);
	WARN_ON(!set->num_connectors);

	ret = drm_atomic_set_mode_क्रम_crtc(crtc_state, set->mode);
	अगर (ret != 0)
		वापस ret;

	crtc_state->active = true;

	ret = drm_atomic_set_crtc_क्रम_plane(primary_state, crtc);
	अगर (ret != 0)
		वापस ret;

	drm_mode_get_hv_timing(set->mode, &hdisplay, &vdisplay);

	drm_atomic_set_fb_क्रम_plane(primary_state, set->fb);
	primary_state->crtc_x = 0;
	primary_state->crtc_y = 0;
	primary_state->crtc_w = hdisplay;
	primary_state->crtc_h = vdisplay;
	primary_state->src_x = set->x << 16;
	primary_state->src_y = set->y << 16;
	अगर (drm_rotation_90_or_270(primary_state->rotation)) अणु
		primary_state->src_w = vdisplay << 16;
		primary_state->src_h = hdisplay << 16;
	पूर्ण अन्यथा अणु
		primary_state->src_w = hdisplay << 16;
		primary_state->src_h = vdisplay << 16;
	पूर्ण

commit:
	ret = update_output_state(state, set);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__drm_atomic_helper_set_config);

व्योम drm_atomic_prपूर्णांक_state(स्थिर काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(state->dev->dev);
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *plane_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *connector_state;
	पूर्णांक i;

	DRM_DEBUG_ATOMIC("checking %p\n", state);

	क्रम_each_new_plane_in_state(state, plane, plane_state, i)
		drm_atomic_plane_prपूर्णांक_state(&p, plane_state);

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i)
		drm_atomic_crtc_prपूर्णांक_state(&p, crtc_state);

	क्रम_each_new_connector_in_state(state, connector, connector_state, i)
		drm_atomic_connector_prपूर्णांक_state(&p, connector_state);
पूर्ण

अटल व्योम __drm_state_dump(काष्ठा drm_device *dev, काष्ठा drm_prपूर्णांकer *p,
			     bool take_locks)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	अगर (!drm_drv_uses_atomic_modeset(dev))
		वापस;

	list_क्रम_each_entry(plane, &config->plane_list, head) अणु
		अगर (take_locks)
			drm_modeset_lock(&plane->mutex, शून्य);
		drm_atomic_plane_prपूर्णांक_state(p, plane->state);
		अगर (take_locks)
			drm_modeset_unlock(&plane->mutex);
	पूर्ण

	list_क्रम_each_entry(crtc, &config->crtc_list, head) अणु
		अगर (take_locks)
			drm_modeset_lock(&crtc->mutex, शून्य);
		drm_atomic_crtc_prपूर्णांक_state(p, crtc->state);
		अगर (take_locks)
			drm_modeset_unlock(&crtc->mutex);
	पूर्ण

	drm_connector_list_iter_begin(dev, &conn_iter);
	अगर (take_locks)
		drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		drm_atomic_connector_prपूर्णांक_state(p, connector->state);
	अगर (take_locks)
		drm_modeset_unlock(&dev->mode_config.connection_mutex);
	drm_connector_list_iter_end(&conn_iter);
पूर्ण

/**
 * drm_state_dump - dump entire device atomic state
 * @dev: the drm device
 * @p: where to prपूर्णांक the state to
 *
 * Just क्रम debugging.  Drivers might want an option to dump state
 * to dmesg in हाल of error irq's.  (Hपूर्णांक, you probably want to
 * ratelimit this!)
 *
 * The caller must wrap this drm_modeset_lock_all_ctx() and
 * drm_modeset_drop_locks(). If this is called from error irq handler, it should
 * not be enabled by शेष - अगर you are debugging errors you might
 * not care that this is racey, but calling this without all modeset locks held
 * is inherently unsafe.
 */
व्योम drm_state_dump(काष्ठा drm_device *dev, काष्ठा drm_prपूर्णांकer *p)
अणु
	__drm_state_dump(dev, p, false);
पूर्ण
EXPORT_SYMBOL(drm_state_dump);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक drm_state_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	__drm_state_dump(dev, &p, true);

	वापस 0;
पूर्ण

/* any use in debugfs files to dump inभागidual planes/crtc/etc? */
अटल स्थिर काष्ठा drm_info_list drm_atomic_debugfs_list[] = अणु
	अणु"state", drm_state_info, 0पूर्ण,
पूर्ण;

व्योम drm_atomic_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(drm_atomic_debugfs_list,
				 ARRAY_SIZE(drm_atomic_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर
