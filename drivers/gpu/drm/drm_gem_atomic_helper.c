<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/dma-resv.h>

#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "drm_internal.h"

/**
 * DOC: overview
 *
 * The GEM atomic helpers library implements generic atomic-commit
 * functions क्रम drivers that use GEM objects. Currently, it provides
 * synchronization helpers, and plane state and framebuffer BO mappings
 * क्रम planes with shaकरोw buffers.
 *
 * Beक्रमe scanout, a plane's framebuffer needs to be synchronized with
 * possible ग_लिखोrs that draw पूर्णांकo the framebuffer. All drivers should
 * call drm_gem_plane_helper_prepare_fb() from their implementation of
 * काष्ठा &drm_plane_helper.prepare_fb . It sets the plane's fence from
 * the framebuffer so that the DRM core can synchronize access स्वतःmatically.
 *
 * drm_gem_plane_helper_prepare_fb() can also be used directly as
 * implementation of prepare_fb. For drivers based on
 * काष्ठा drm_simple_display_pipe, drm_gem_simple_display_pipe_prepare_fb()
 * provides equivalent functionality.
 *
 * .. code-block:: c
 *
 *	#समावेश <drm/drm_gem_atomic_helper.h>
 *
 *	काष्ठा drm_plane_helper_funcs driver_plane_helper_funcs = अणु
 *		...,
 *		. prepare_fb = drm_gem_plane_helper_prepare_fb,
 *	पूर्ण;
 *
 *	काष्ठा drm_simple_display_pipe_funcs driver_pipe_funcs = अणु
 *		...,
 *		. prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
 *	पूर्ण;
 *
 * A driver using a shaकरोw buffer copies the content of the shaकरोw buffers
 * पूर्णांकo the HW's framebuffer memory during an atomic update. This requires
 * a mapping of the shaकरोw buffer पूर्णांकo kernel address space. The mappings
 * cannot be established by commit-tail functions, such as atomic_update,
 * as this would violate locking rules around dma_buf_vmap().
 *
 * The helpers क्रम shaकरोw-buffered planes establish and release mappings,
 * and provide काष्ठा drm_shaकरोw_plane_state, which stores the plane's mapping
 * क्रम commit-tail functons.
 *
 * Shaकरोw-buffered planes can easily be enabled by using the provided macros
 * %DRM_GEM_SHADOW_PLANE_FUNCS and %DRM_GEM_SHADOW_PLANE_HELPER_FUNCS.
 * These macros set up the plane and plane-helper callbacks to poपूर्णांक to the
 * shaकरोw-buffer helpers.
 *
 * .. code-block:: c
 *
 *	#समावेश <drm/drm_gem_atomic_helper.h>
 *
 *	काष्ठा drm_plane_funcs driver_plane_funcs = अणु
 *		...,
 *		DRM_GEM_SHADOW_PLANE_FUNCS,
 *	पूर्ण;
 *
 *	काष्ठा drm_plane_helper_funcs driver_plane_helper_funcs = अणु
 *		...,
 *		DRM_GEM_SHADOW_PLANE_HELPER_FUNCS,
 *	पूर्ण;
 *
 * In the driver's atomic-update function, shaकरोw-buffer mappings are available
 * from the plane state. Use to_drm_shaकरोw_plane_state() to upcast from
 * काष्ठा drm_plane_state.
 *
 * .. code-block:: c
 *
 *	व्योम driver_plane_atomic_update(काष्ठा drm_plane *plane,
 *					काष्ठा drm_plane_state *old_plane_state)
 *	अणु
 *		काष्ठा drm_plane_state *plane_state = plane->state;
 *		काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state =
 *			to_drm_shaकरोw_plane_state(plane_state);
 *
 *		// access shaकरोw buffer via shaकरोw_plane_state->map
 *	पूर्ण
 *
 * A mapping address क्रम each of the framebuffer's buffer object is stored in
 * काष्ठा &drm_shaकरोw_plane_state.map. The mappings are valid जबतक the state
 * is being used.
 *
 * Drivers that use काष्ठा drm_simple_display_pipe can use
 * %DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS to initialize the rsp
 * callbacks. Access to shaकरोw-buffer mappings is similar to regular
 * atomic_update.
 *
 * .. code-block:: c
 *
 *	काष्ठा drm_simple_display_pipe_funcs driver_pipe_funcs = अणु
 *		...,
 *		DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS,
 *	पूर्ण;
 *
 *	व्योम driver_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
 *				काष्ठा drm_crtc_state *crtc_state,
 *				काष्ठा drm_plane_state *plane_state)
 *	अणु
 *		काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state =
 *			to_drm_shaकरोw_plane_state(plane_state);
 *
 *		// access shaकरोw buffer via shaकरोw_plane_state->map
 *	पूर्ण
 */

/*
 * Plane Helpers
 */

/**
 * drm_gem_plane_helper_prepare_fb() - Prepare a GEM backed framebuffer
 * @plane: Plane
 * @state: Plane state the fence will be attached to
 *
 * This function extracts the exclusive fence from &drm_gem_object.resv and
 * attaches it to plane state क्रम the atomic helper to रुको on. This is
 * necessary to correctly implement implicit synchronization क्रम any buffers
 * shared as a काष्ठा &dma_buf. This function can be used as the
 * &drm_plane_helper_funcs.prepare_fb callback.
 *
 * There is no need क्रम &drm_plane_helper_funcs.cleanup_fb hook क्रम simple
 * GEM based framebuffer drivers which have their buffers always pinned in
 * memory.
 *
 * See drm_atomic_set_fence_क्रम_plane() क्रम a discussion of implicit and
 * explicit fencing in atomic modeset updates.
 */
पूर्णांक drm_gem_plane_helper_prepare_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_gem_object *obj;
	काष्ठा dma_fence *fence;

	अगर (!state->fb)
		वापस 0;

	obj = drm_gem_fb_get_obj(state->fb, 0);
	fence = dma_resv_get_excl_rcu(obj->resv);
	drm_atomic_set_fence_क्रम_plane(state, fence);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_plane_helper_prepare_fb);

/**
 * drm_gem_simple_display_pipe_prepare_fb - prepare_fb helper क्रम &drm_simple_display_pipe
 * @pipe: Simple display pipe
 * @plane_state: Plane state
 *
 * This function uses drm_gem_plane_helper_prepare_fb() to extract the exclusive fence
 * from &drm_gem_object.resv and attaches it to plane state क्रम the atomic
 * helper to रुको on. This is necessary to correctly implement implicit
 * synchronization क्रम any buffers shared as a काष्ठा &dma_buf. Drivers can use
 * this as their &drm_simple_display_pipe_funcs.prepare_fb callback.
 *
 * See drm_atomic_set_fence_क्रम_plane() क्रम a discussion of implicit and
 * explicit fencing in atomic modeset updates.
 */
पूर्णांक drm_gem_simple_display_pipe_prepare_fb(काष्ठा drm_simple_display_pipe *pipe,
					   काष्ठा drm_plane_state *plane_state)
अणु
	वापस drm_gem_plane_helper_prepare_fb(&pipe->plane, plane_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_simple_display_pipe_prepare_fb);

/*
 * Shaकरोw-buffered Planes
 */

/**
 * drm_gem_duplicate_shaकरोw_plane_state - duplicates shaकरोw-buffered plane state
 * @plane: the plane
 *
 * This function implements काष्ठा &drm_plane_funcs.atomic_duplicate_state क्रम
 * shaकरोw-buffered planes. It assumes the existing state to be of type
 * काष्ठा drm_shaकरोw_plane_state and it allocates the new state to be of this
 * type.
 *
 * The function करोes not duplicate existing mappings of the shaकरोw buffers.
 * Mappings are मुख्यtained during the atomic commit by the plane's prepare_fb
 * and cleanup_fb helpers. See drm_gem_prepare_shaकरोw_fb() and drm_gem_cleanup_shaकरोw_fb()
 * क्रम corresponding helpers.
 *
 * Returns:
 * A poपूर्णांकer to a new plane state on success, or शून्य otherwise.
 */
काष्ठा drm_plane_state *
drm_gem_duplicate_shaकरोw_plane_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *plane_state = plane->state;
	काष्ठा drm_shaकरोw_plane_state *new_shaकरोw_plane_state;

	अगर (!plane_state)
		वापस शून्य;

	new_shaकरोw_plane_state = kzalloc(माप(*new_shaकरोw_plane_state), GFP_KERNEL);
	अगर (!new_shaकरोw_plane_state)
		वापस शून्य;
	__drm_atomic_helper_plane_duplicate_state(plane, &new_shaकरोw_plane_state->base);

	वापस &new_shaकरोw_plane_state->base;
पूर्ण
EXPORT_SYMBOL(drm_gem_duplicate_shaकरोw_plane_state);

/**
 * drm_gem_destroy_shaकरोw_plane_state - deletes shaकरोw-buffered plane state
 * @plane: the plane
 * @plane_state: the plane state of type काष्ठा drm_shaकरोw_plane_state
 *
 * This function implements काष्ठा &drm_plane_funcs.atomic_destroy_state
 * क्रम shaकरोw-buffered planes. It expects that mappings of shaकरोw buffers
 * have been released alपढ़ोy.
 */
व्योम drm_gem_destroy_shaकरोw_plane_state(काष्ठा drm_plane *plane,
					काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state =
		to_drm_shaकरोw_plane_state(plane_state);

	__drm_atomic_helper_plane_destroy_state(&shaकरोw_plane_state->base);
	kमुक्त(shaकरोw_plane_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_destroy_shaकरोw_plane_state);

/**
 * drm_gem_reset_shaकरोw_plane - resets a shaकरोw-buffered plane
 * @plane: the plane
 *
 * This function implements काष्ठा &drm_plane_funcs.reset_plane क्रम
 * shaकरोw-buffered planes. It assumes the current plane state to be
 * of type काष्ठा drm_shaकरोw_plane and it allocates the new state of
 * this type.
 */
व्योम drm_gem_reset_shaकरोw_plane(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state;

	अगर (plane->state) अणु
		drm_gem_destroy_shaकरोw_plane_state(plane, plane->state);
		plane->state = शून्य; /* must be set to शून्य here */
	पूर्ण

	shaकरोw_plane_state = kzalloc(माप(*shaकरोw_plane_state), GFP_KERNEL);
	अगर (!shaकरोw_plane_state)
		वापस;
	__drm_atomic_helper_plane_reset(plane, &shaकरोw_plane_state->base);
पूर्ण
EXPORT_SYMBOL(drm_gem_reset_shaकरोw_plane);

/**
 * drm_gem_prepare_shaकरोw_fb - prepares shaकरोw framebuffers
 * @plane: the plane
 * @plane_state: the plane state of type काष्ठा drm_shaकरोw_plane_state
 *
 * This function implements काष्ठा &drm_plane_helper_funcs.prepare_fb. It
 * maps all buffer objects of the plane's framebuffer पूर्णांकo kernel address
 * space and stores them in &काष्ठा drm_shaकरोw_plane_state.map. The
 * framebuffer will be synchronized as part of the atomic commit.
 *
 * See drm_gem_cleanup_shaकरोw_fb() क्रम cleanup.
 *
 * Returns:
 * 0 on success, or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drm_gem_prepare_shaकरोw_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(plane_state);
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा drm_gem_object *obj;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;
	माप_प्रकार i;

	अगर (!fb)
		वापस 0;

	ret = drm_gem_plane_helper_prepare_fb(plane, plane_state);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(shaकरोw_plane_state->map); ++i) अणु
		obj = drm_gem_fb_get_obj(fb, i);
		अगर (!obj)
			जारी;
		ret = drm_gem_vmap(obj, &map);
		अगर (ret)
			जाओ err_drm_gem_vunmap;
		shaकरोw_plane_state->map[i] = map;
	पूर्ण

	वापस 0;

err_drm_gem_vunmap:
	जबतक (i) अणु
		--i;
		obj = drm_gem_fb_get_obj(fb, i);
		अगर (!obj)
			जारी;
		drm_gem_vunmap(obj, &shaकरोw_plane_state->map[i]);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_prepare_shaकरोw_fb);

/**
 * drm_gem_cleanup_shaकरोw_fb - releases shaकरोw framebuffers
 * @plane: the plane
 * @plane_state: the plane state of type काष्ठा drm_shaकरोw_plane_state
 *
 * This function implements काष्ठा &drm_plane_helper_funcs.cleanup_fb.
 * This function unmaps all buffer objects of the plane's framebuffer.
 *
 * See drm_gem_prepare_shaकरोw_fb() क्रम more inक्रमamtion.
 */
व्योम drm_gem_cleanup_shaकरोw_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(plane_state);
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	माप_प्रकार i = ARRAY_SIZE(shaकरोw_plane_state->map);
	काष्ठा drm_gem_object *obj;

	अगर (!fb)
		वापस;

	जबतक (i) अणु
		--i;
		obj = drm_gem_fb_get_obj(fb, i);
		अगर (!obj)
			जारी;
		drm_gem_vunmap(obj, &shaकरोw_plane_state->map[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_gem_cleanup_shaकरोw_fb);

/**
 * drm_gem_simple_kms_prepare_shaकरोw_fb - prepares shaकरोw framebuffers
 * @pipe: the simple display pipe
 * @plane_state: the plane state of type काष्ठा drm_shaकरोw_plane_state
 *
 * This function implements काष्ठा drm_simple_display_funcs.prepare_fb. It
 * maps all buffer objects of the plane's framebuffer पूर्णांकo kernel address
 * space and stores them in काष्ठा drm_shaकरोw_plane_state.map. The
 * framebuffer will be synchronized as part of the atomic commit.
 *
 * See drm_gem_simple_kms_cleanup_shaकरोw_fb() क्रम cleanup.
 *
 * Returns:
 * 0 on success, or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drm_gem_simple_kms_prepare_shaकरोw_fb(काष्ठा drm_simple_display_pipe *pipe,
					 काष्ठा drm_plane_state *plane_state)
अणु
	वापस drm_gem_prepare_shaकरोw_fb(&pipe->plane, plane_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_simple_kms_prepare_shaकरोw_fb);

/**
 * drm_gem_simple_kms_cleanup_shaकरोw_fb - releases shaकरोw framebuffers
 * @pipe: the simple display pipe
 * @plane_state: the plane state of type काष्ठा drm_shaकरोw_plane_state
 *
 * This function implements काष्ठा drm_simple_display_funcs.cleanup_fb.
 * This function unmaps all buffer objects of the plane's framebuffer.
 *
 * See drm_gem_simple_kms_prepare_shaकरोw_fb().
 */
व्योम drm_gem_simple_kms_cleanup_shaकरोw_fb(काष्ठा drm_simple_display_pipe *pipe,
					  काष्ठा drm_plane_state *plane_state)
अणु
	drm_gem_cleanup_shaकरोw_fb(&pipe->plane, plane_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_simple_kms_cleanup_shaकरोw_fb);

/**
 * drm_gem_simple_kms_reset_shaकरोw_plane - resets a shaकरोw-buffered plane
 * @pipe: the simple display pipe
 *
 * This function implements काष्ठा drm_simple_display_funcs.reset_plane
 * क्रम shaकरोw-buffered planes.
 */
व्योम drm_gem_simple_kms_reset_shaकरोw_plane(काष्ठा drm_simple_display_pipe *pipe)
अणु
	drm_gem_reset_shaकरोw_plane(&pipe->plane);
पूर्ण
EXPORT_SYMBOL(drm_gem_simple_kms_reset_shaकरोw_plane);

/**
 * drm_gem_simple_kms_duplicate_shaकरोw_plane_state - duplicates shaकरोw-buffered plane state
 * @pipe: the simple display pipe
 *
 * This function implements काष्ठा drm_simple_display_funcs.duplicate_plane_state
 * क्रम shaकरोw-buffered planes. It करोes not duplicate existing mappings of the shaकरोw
 * buffers. Mappings are मुख्यtained during the atomic commit by the plane's prepare_fb
 * and cleanup_fb helpers.
 *
 * Returns:
 * A poपूर्णांकer to a new plane state on success, or शून्य otherwise.
 */
काष्ठा drm_plane_state *
drm_gem_simple_kms_duplicate_shaकरोw_plane_state(काष्ठा drm_simple_display_pipe *pipe)
अणु
	वापस drm_gem_duplicate_shaकरोw_plane_state(&pipe->plane);
पूर्ण
EXPORT_SYMBOL(drm_gem_simple_kms_duplicate_shaकरोw_plane_state);

/**
 * drm_gem_simple_kms_destroy_shaकरोw_plane_state - resets shaकरोw-buffered plane state
 * @pipe: the simple display pipe
 * @plane_state: the plane state of type काष्ठा drm_shaकरोw_plane_state
 *
 * This function implements काष्ठा drm_simple_display_funcs.destroy_plane_state
 * क्रम shaकरोw-buffered planes. It expects that mappings of shaकरोw buffers
 * have been released alपढ़ोy.
 */
व्योम drm_gem_simple_kms_destroy_shaकरोw_plane_state(काष्ठा drm_simple_display_pipe *pipe,
						   काष्ठा drm_plane_state *plane_state)
अणु
	drm_gem_destroy_shaकरोw_plane_state(&pipe->plane, plane_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_simple_kms_destroy_shaकरोw_plane_state);
