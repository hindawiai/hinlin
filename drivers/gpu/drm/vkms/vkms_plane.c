<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/dma-buf-map.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>

#समावेश "vkms_drv.h"

अटल स्थिर u32 vkms_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर u32 vkms_cursor_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल काष्ठा drm_plane_state *
vkms_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा vkms_plane_state *vkms_state;
	काष्ठा vkms_composer *composer;

	vkms_state = kzalloc(माप(*vkms_state), GFP_KERNEL);
	अगर (!vkms_state)
		वापस शून्य;

	composer = kzalloc(माप(*composer), GFP_KERNEL);
	अगर (!composer) अणु
		DRM_DEBUG_KMS("Couldn't allocate composer\n");
		kमुक्त(vkms_state);
		वापस शून्य;
	पूर्ण

	vkms_state->composer = composer;

	__drm_atomic_helper_plane_duplicate_state(plane,
						  &vkms_state->base);

	वापस &vkms_state->base;
पूर्ण

अटल व्योम vkms_plane_destroy_state(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा vkms_plane_state *vkms_state = to_vkms_plane_state(old_state);
	काष्ठा drm_crtc *crtc = vkms_state->base.crtc;

	अगर (crtc) अणु
		/* dropping the reference we acquired in
		 * vkms_primary_plane_update()
		 */
		अगर (drm_framebuffer_पढ़ो_refcount(&vkms_state->composer->fb))
			drm_framebuffer_put(&vkms_state->composer->fb);
	पूर्ण

	kमुक्त(vkms_state->composer);
	vkms_state->composer = शून्य;

	__drm_atomic_helper_plane_destroy_state(old_state);
	kमुक्त(vkms_state);
पूर्ण

अटल व्योम vkms_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा vkms_plane_state *vkms_state;

	अगर (plane->state)
		vkms_plane_destroy_state(plane, plane->state);

	vkms_state = kzalloc(माप(*vkms_state), GFP_KERNEL);
	अगर (!vkms_state) अणु
		DRM_ERROR("Cannot allocate vkms_plane_state\n");
		वापस;
	पूर्ण

	plane->state = &vkms_state->base;
	plane->state->plane = plane;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs vkms_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= drm_plane_cleanup,
	.reset			= vkms_plane_reset,
	.atomic_duplicate_state = vkms_plane_duplicate_state,
	.atomic_destroy_state	= vkms_plane_destroy_state,
पूर्ण;

अटल व्योम vkms_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा vkms_plane_state *vkms_plane_state;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा vkms_composer *composer;

	अगर (!new_state->crtc || !fb)
		वापस;

	vkms_plane_state = to_vkms_plane_state(new_state);

	composer = vkms_plane_state->composer;
	स_नकल(&composer->src, &new_state->src, माप(काष्ठा drm_rect));
	स_नकल(&composer->dst, &new_state->dst, माप(काष्ठा drm_rect));
	स_नकल(&composer->fb, fb, माप(काष्ठा drm_framebuffer));
	drm_framebuffer_get(&composer->fb);
	composer->offset = fb->offsets[0];
	composer->pitch = fb->pitches[0];
	composer->cpp = fb->क्रमmat->cpp[0];
पूर्ण

अटल पूर्णांक vkms_plane_atomic_check(काष्ठा drm_plane *plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc_state *crtc_state;
	bool can_position = false;
	पूर्णांक ret;

	अगर (!new_plane_state->fb || WARN_ON(!new_plane_state->crtc))
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state,
					       new_plane_state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
		can_position = true;

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  can_position, true);
	अगर (ret != 0)
		वापस ret;

	/* क्रम now primary plane must be visible and full screen */
	अगर (!new_plane_state->visible && !can_position)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vkms_prepare_fb(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	अगर (!state->fb)
		वापस 0;

	gem_obj = drm_gem_fb_get_obj(state->fb, 0);
	ret = drm_gem_shmem_vmap(gem_obj, &map);
	अगर (ret)
		DRM_ERROR("vmap failed: %d\n", ret);

	वापस drm_gem_plane_helper_prepare_fb(plane, state);
पूर्ण

अटल व्योम vkms_cleanup_fb(काष्ठा drm_plane *plane,
			    काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा drm_gem_shmem_object *shmem_obj;
	काष्ठा dma_buf_map map;

	अगर (!old_state->fb)
		वापस;

	gem_obj = drm_gem_fb_get_obj(old_state->fb, 0);
	shmem_obj = to_drm_gem_shmem_obj(drm_gem_fb_get_obj(old_state->fb, 0));
	dma_buf_map_set_vaddr(&map, shmem_obj->vaddr);
	drm_gem_shmem_vunmap(gem_obj, &map);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs vkms_primary_helper_funcs = अणु
	.atomic_update		= vkms_plane_atomic_update,
	.atomic_check		= vkms_plane_atomic_check,
	.prepare_fb		= vkms_prepare_fb,
	.cleanup_fb		= vkms_cleanup_fb,
पूर्ण;

काष्ठा drm_plane *vkms_plane_init(काष्ठा vkms_device *vkmsdev,
				  क्रमागत drm_plane_type type, पूर्णांक index)
अणु
	काष्ठा drm_device *dev = &vkmsdev->drm;
	स्थिर काष्ठा drm_plane_helper_funcs *funcs;
	काष्ठा drm_plane *plane;
	स्थिर u32 *क्रमmats;
	पूर्णांक ret, nक्रमmats;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	अगर (type == DRM_PLANE_TYPE_CURSOR) अणु
		क्रमmats = vkms_cursor_क्रमmats;
		nक्रमmats = ARRAY_SIZE(vkms_cursor_क्रमmats);
		funcs = &vkms_primary_helper_funcs;
	पूर्ण अन्यथा अणु
		क्रमmats = vkms_क्रमmats;
		nक्रमmats = ARRAY_SIZE(vkms_क्रमmats);
		funcs = &vkms_primary_helper_funcs;
	पूर्ण

	ret = drm_universal_plane_init(dev, plane, 1 << index,
				       &vkms_plane_funcs,
				       क्रमmats, nक्रमmats,
				       शून्य, type, शून्य);
	अगर (ret) अणु
		kमुक्त(plane);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_plane_helper_add(plane, funcs);

	वापस plane;
पूर्ण
