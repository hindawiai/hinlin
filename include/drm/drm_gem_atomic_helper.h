<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अगर_अघोषित __DRM_GEM_ATOMIC_HELPER_H__
#घोषणा __DRM_GEM_ATOMIC_HELPER_H__

#समावेश <linux/dma-buf-map.h>

#समावेश <drm/drm_plane.h>

काष्ठा drm_simple_display_pipe;

/*
 * Plane Helpers
 */

पूर्णांक drm_gem_plane_helper_prepare_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *state);
पूर्णांक drm_gem_simple_display_pipe_prepare_fb(काष्ठा drm_simple_display_pipe *pipe,
					   काष्ठा drm_plane_state *plane_state);

/*
 * Helpers क्रम planes with shaकरोw buffers
 */

/**
 * काष्ठा drm_shaकरोw_plane_state - plane state क्रम planes with shaकरोw buffers
 *
 * For planes that use a shaकरोw buffer, काष्ठा drm_shaकरोw_plane_state
 * provides the regular plane state plus mappings of the shaकरोw buffer
 * पूर्णांकo kernel address space.
 */
काष्ठा drm_shaकरोw_plane_state अणु
	/** @base: plane state */
	काष्ठा drm_plane_state base;

	/* Transitional state - करो not export or duplicate */

	/**
	 * @map: Mappings of the plane's framebuffer BOs in to kernel address space
	 *
	 * The memory mappings stored in map should be established in the plane's
	 * prepare_fb callback and हटाओd in the cleanup_fb callback.
	 */
	काष्ठा dma_buf_map map[4];
पूर्ण;

/**
 * to_drm_shaकरोw_plane_state - upcasts from काष्ठा drm_plane_state
 * @state: the plane state
 */
अटल अंतरभूत काष्ठा drm_shaकरोw_plane_state *
to_drm_shaकरोw_plane_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा drm_shaकरोw_plane_state, base);
पूर्ण

व्योम drm_gem_reset_shaकरोw_plane(काष्ठा drm_plane *plane);
काष्ठा drm_plane_state *drm_gem_duplicate_shaकरोw_plane_state(काष्ठा drm_plane *plane);
व्योम drm_gem_destroy_shaकरोw_plane_state(काष्ठा drm_plane *plane,
					काष्ठा drm_plane_state *plane_state);

/**
 * DRM_GEM_SHADOW_PLANE_FUNCS -
 *	Initializes काष्ठा drm_plane_funcs क्रम shaकरोw-buffered planes
 *
 * Drivers may use GEM BOs as shaकरोw buffers over the framebuffer memory. This
 * macro initializes काष्ठा drm_plane_funcs to use the rsp helper functions.
 */
#घोषणा DRM_GEM_SHADOW_PLANE_FUNCS \
	.reset = drm_gem_reset_shaकरोw_plane, \
	.atomic_duplicate_state = drm_gem_duplicate_shaकरोw_plane_state, \
	.atomic_destroy_state = drm_gem_destroy_shaकरोw_plane_state

पूर्णांक drm_gem_prepare_shaकरोw_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *plane_state);
व्योम drm_gem_cleanup_shaकरोw_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *plane_state);

/**
 * DRM_GEM_SHADOW_PLANE_HELPER_FUNCS -
 *	Initializes काष्ठा drm_plane_helper_funcs क्रम shaकरोw-buffered planes
 *
 * Drivers may use GEM BOs as shaकरोw buffers over the framebuffer memory. This
 * macro initializes काष्ठा drm_plane_helper_funcs to use the rsp helper
 * functions.
 */
#घोषणा DRM_GEM_SHADOW_PLANE_HELPER_FUNCS \
	.prepare_fb = drm_gem_prepare_shaकरोw_fb, \
	.cleanup_fb = drm_gem_cleanup_shaकरोw_fb

पूर्णांक drm_gem_simple_kms_prepare_shaकरोw_fb(काष्ठा drm_simple_display_pipe *pipe,
					 काष्ठा drm_plane_state *plane_state);
व्योम drm_gem_simple_kms_cleanup_shaकरोw_fb(काष्ठा drm_simple_display_pipe *pipe,
					  काष्ठा drm_plane_state *plane_state);
व्योम drm_gem_simple_kms_reset_shaकरोw_plane(काष्ठा drm_simple_display_pipe *pipe);
काष्ठा drm_plane_state *
drm_gem_simple_kms_duplicate_shaकरोw_plane_state(काष्ठा drm_simple_display_pipe *pipe);
व्योम drm_gem_simple_kms_destroy_shaकरोw_plane_state(काष्ठा drm_simple_display_pipe *pipe,
						   काष्ठा drm_plane_state *plane_state);

/**
 * DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS -
 *	Initializes काष्ठा drm_simple_display_pipe_funcs क्रम shaकरोw-buffered planes
 *
 * Drivers may use GEM BOs as shaकरोw buffers over the framebuffer memory. This
 * macro initializes काष्ठा drm_simple_display_pipe_funcs to use the rsp helper
 * functions.
 */
#घोषणा DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS \
	.prepare_fb = drm_gem_simple_kms_prepare_shaकरोw_fb, \
	.cleanup_fb = drm_gem_simple_kms_cleanup_shaकरोw_fb, \
	.reset_plane = drm_gem_simple_kms_reset_shaकरोw_plane, \
	.duplicate_plane_state = drm_gem_simple_kms_duplicate_shaकरोw_plane_state, \
	.destroy_plane_state = drm_gem_simple_kms_destroy_shaकरोw_plane_state

#पूर्ण_अगर /* __DRM_GEM_ATOMIC_HELPER_H__ */
