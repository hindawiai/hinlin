<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "virtgpu_drv.h"

अटल स्थिर uपूर्णांक32_t virtio_gpu_क्रमmats[] = अणु
	DRM_FORMAT_HOST_XRGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक32_t virtio_gpu_cursor_क्रमmats[] = अणु
	DRM_FORMAT_HOST_ARGB8888,
पूर्ण;

uपूर्णांक32_t virtio_gpu_translate_क्रमmat(uपूर्णांक32_t drm_fourcc)
अणु
	uपूर्णांक32_t क्रमmat;

	चयन (drm_fourcc) अणु
	हाल DRM_FORMAT_XRGB8888:
		क्रमmat = VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		क्रमmat = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
		अवरोध;
	हाल DRM_FORMAT_BGRX8888:
		क्रमmat = VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM;
		अवरोध;
	हाल DRM_FORMAT_BGRA8888:
		क्रमmat = VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM;
		अवरोध;
	शेष:
		/*
		 * This should not happen, we handle everything listed
		 * in virtio_gpu_क्रमmats[].
		 */
		क्रमmat = 0;
		अवरोध;
	पूर्ण
	WARN_ON(क्रमmat == 0);
	वापस क्रमmat;
पूर्ण

अटल व्योम virtio_gpu_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);
	kमुक्त(plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs virtio_gpu_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= virtio_gpu_plane_destroy,
	.reset			= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल पूर्णांक virtio_gpu_plane_atomic_check(काष्ठा drm_plane *plane,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	bool is_cursor = plane->type == DRM_PLANE_TYPE_CURSOR;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	अगर (!new_plane_state->fb || WARN_ON(!new_plane_state->crtc))
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state,
					       new_plane_state->crtc);
	अगर (IS_ERR(crtc_state))
                वापस PTR_ERR(crtc_state);

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  is_cursor, true);
	वापस ret;
पूर्ण

अटल व्योम virtio_gpu_update_dumb_bo(काष्ठा virtio_gpu_device *vgdev,
				      काष्ठा drm_plane_state *state,
				      काष्ठा drm_rect *rect)
अणु
	काष्ठा virtio_gpu_object *bo =
		gem_to_virtio_gpu_obj(state->fb->obj[0]);
	काष्ठा virtio_gpu_object_array *objs;
	uपूर्णांक32_t w = rect->x2 - rect->x1;
	uपूर्णांक32_t h = rect->y2 - rect->y1;
	uपूर्णांक32_t x = rect->x1;
	uपूर्णांक32_t y = rect->y1;
	uपूर्णांक32_t off = x * state->fb->क्रमmat->cpp[0] +
		y * state->fb->pitches[0];

	objs = virtio_gpu_array_alloc(1);
	अगर (!objs)
		वापस;
	virtio_gpu_array_add_obj(objs, &bo->base.base);

	virtio_gpu_cmd_transfer_to_host_2d(vgdev, off, w, h, x, y,
					   objs, शून्य);
पूर्ण

अटल व्योम virtio_gpu_primary_plane_update(काष्ठा drm_plane *plane,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_output *output = शून्य;
	काष्ठा virtio_gpu_object *bo;
	काष्ठा drm_rect rect;

	अगर (plane->state->crtc)
		output = drm_crtc_to_virtio_gpu_output(plane->state->crtc);
	अगर (old_state->crtc)
		output = drm_crtc_to_virtio_gpu_output(old_state->crtc);
	अगर (WARN_ON(!output))
		वापस;

	अगर (!plane->state->fb || !output->crtc.state->active) अणु
		DRM_DEBUG("nofb\n");
		virtio_gpu_cmd_set_scanout(vgdev, output->index, 0,
					   plane->state->src_w >> 16,
					   plane->state->src_h >> 16,
					   0, 0);
		virtio_gpu_notअगरy(vgdev);
		वापस;
	पूर्ण

	अगर (!drm_atomic_helper_damage_merged(old_state, plane->state, &rect))
		वापस;

	bo = gem_to_virtio_gpu_obj(plane->state->fb->obj[0]);
	अगर (bo->dumb)
		virtio_gpu_update_dumb_bo(vgdev, plane->state, &rect);

	अगर (plane->state->fb != old_state->fb ||
	    plane->state->src_w != old_state->src_w ||
	    plane->state->src_h != old_state->src_h ||
	    plane->state->src_x != old_state->src_x ||
	    plane->state->src_y != old_state->src_y ||
	    output->needs_modeset) अणु
		output->needs_modeset = false;
		DRM_DEBUG("handle 0x%x, crtc %dx%d+%d+%d, src %dx%d+%d+%d\n",
			  bo->hw_res_handle,
			  plane->state->crtc_w, plane->state->crtc_h,
			  plane->state->crtc_x, plane->state->crtc_y,
			  plane->state->src_w >> 16,
			  plane->state->src_h >> 16,
			  plane->state->src_x >> 16,
			  plane->state->src_y >> 16);

		अगर (bo->host3d_blob || bo->guest_blob) अणु
			virtio_gpu_cmd_set_scanout_blob
						(vgdev, output->index, bo,
						 plane->state->fb,
						 plane->state->src_w >> 16,
						 plane->state->src_h >> 16,
						 plane->state->src_x >> 16,
						 plane->state->src_y >> 16);
		पूर्ण अन्यथा अणु
			virtio_gpu_cmd_set_scanout(vgdev, output->index,
						   bo->hw_res_handle,
						   plane->state->src_w >> 16,
						   plane->state->src_h >> 16,
						   plane->state->src_x >> 16,
						   plane->state->src_y >> 16);
		पूर्ण
	पूर्ण

	virtio_gpu_cmd_resource_flush(vgdev, bo->hw_res_handle,
				      rect.x1,
				      rect.y1,
				      rect.x2 - rect.x1,
				      rect.y2 - rect.y1);
	virtio_gpu_notअगरy(vgdev);
पूर्ण

अटल पूर्णांक virtio_gpu_cursor_prepare_fb(काष्ठा drm_plane *plane,
					काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_framebuffer *vgfb;
	काष्ठा virtio_gpu_object *bo;

	अगर (!new_state->fb)
		वापस 0;

	vgfb = to_virtio_gpu_framebuffer(new_state->fb);
	bo = gem_to_virtio_gpu_obj(vgfb->base.obj[0]);
	अगर (bo && bo->dumb && (plane->state->fb != new_state->fb)) अणु
		vgfb->fence = virtio_gpu_fence_alloc(vgdev);
		अगर (!vgfb->fence)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम virtio_gpu_cursor_cleanup_fb(काष्ठा drm_plane *plane,
					 काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा virtio_gpu_framebuffer *vgfb;

	अगर (!plane->state->fb)
		वापस;

	vgfb = to_virtio_gpu_framebuffer(plane->state->fb);
	अगर (vgfb->fence) अणु
		dma_fence_put(&vgfb->fence->f);
		vgfb->fence = शून्य;
	पूर्ण
पूर्ण

अटल व्योम virtio_gpu_cursor_plane_update(काष्ठा drm_plane *plane,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_output *output = शून्य;
	काष्ठा virtio_gpu_framebuffer *vgfb;
	काष्ठा virtio_gpu_object *bo = शून्य;
	uपूर्णांक32_t handle;

	अगर (plane->state->crtc)
		output = drm_crtc_to_virtio_gpu_output(plane->state->crtc);
	अगर (old_state->crtc)
		output = drm_crtc_to_virtio_gpu_output(old_state->crtc);
	अगर (WARN_ON(!output))
		वापस;

	अगर (plane->state->fb) अणु
		vgfb = to_virtio_gpu_framebuffer(plane->state->fb);
		bo = gem_to_virtio_gpu_obj(vgfb->base.obj[0]);
		handle = bo->hw_res_handle;
	पूर्ण अन्यथा अणु
		handle = 0;
	पूर्ण

	अगर (bo && bo->dumb && (plane->state->fb != old_state->fb)) अणु
		/* new cursor -- update & रुको */
		काष्ठा virtio_gpu_object_array *objs;

		objs = virtio_gpu_array_alloc(1);
		अगर (!objs)
			वापस;
		virtio_gpu_array_add_obj(objs, vgfb->base.obj[0]);
		virtio_gpu_array_lock_resv(objs);
		virtio_gpu_cmd_transfer_to_host_2d
			(vgdev, 0,
			 plane->state->crtc_w,
			 plane->state->crtc_h,
			 0, 0, objs, vgfb->fence);
		virtio_gpu_notअगरy(vgdev);
		dma_fence_रुको(&vgfb->fence->f, true);
		dma_fence_put(&vgfb->fence->f);
		vgfb->fence = शून्य;
	पूर्ण

	अगर (plane->state->fb != old_state->fb) अणु
		DRM_DEBUG("update, handle %d, pos +%d+%d, hot %d,%d\n", handle,
			  plane->state->crtc_x,
			  plane->state->crtc_y,
			  plane->state->fb ? plane->state->fb->hot_x : 0,
			  plane->state->fb ? plane->state->fb->hot_y : 0);
		output->cursor.hdr.type =
			cpu_to_le32(VIRTIO_GPU_CMD_UPDATE_CURSOR);
		output->cursor.resource_id = cpu_to_le32(handle);
		अगर (plane->state->fb) अणु
			output->cursor.hot_x =
				cpu_to_le32(plane->state->fb->hot_x);
			output->cursor.hot_y =
				cpu_to_le32(plane->state->fb->hot_y);
		पूर्ण अन्यथा अणु
			output->cursor.hot_x = cpu_to_le32(0);
			output->cursor.hot_y = cpu_to_le32(0);
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_DEBUG("move +%d+%d\n",
			  plane->state->crtc_x,
			  plane->state->crtc_y);
		output->cursor.hdr.type =
			cpu_to_le32(VIRTIO_GPU_CMD_MOVE_CURSOR);
	पूर्ण
	output->cursor.pos.x = cpu_to_le32(plane->state->crtc_x);
	output->cursor.pos.y = cpu_to_le32(plane->state->crtc_y);
	virtio_gpu_cursor_ping(vgdev, output);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs virtio_gpu_primary_helper_funcs = अणु
	.atomic_check		= virtio_gpu_plane_atomic_check,
	.atomic_update		= virtio_gpu_primary_plane_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs virtio_gpu_cursor_helper_funcs = अणु
	.prepare_fb		= virtio_gpu_cursor_prepare_fb,
	.cleanup_fb		= virtio_gpu_cursor_cleanup_fb,
	.atomic_check		= virtio_gpu_plane_atomic_check,
	.atomic_update		= virtio_gpu_cursor_plane_update,
पूर्ण;

काष्ठा drm_plane *virtio_gpu_plane_init(काष्ठा virtio_gpu_device *vgdev,
					क्रमागत drm_plane_type type,
					पूर्णांक index)
अणु
	काष्ठा drm_device *dev = vgdev->ddev;
	स्थिर काष्ठा drm_plane_helper_funcs *funcs;
	काष्ठा drm_plane *plane;
	स्थिर uपूर्णांक32_t *क्रमmats;
	पूर्णांक ret, nक्रमmats;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	अगर (type == DRM_PLANE_TYPE_CURSOR) अणु
		क्रमmats = virtio_gpu_cursor_क्रमmats;
		nक्रमmats = ARRAY_SIZE(virtio_gpu_cursor_क्रमmats);
		funcs = &virtio_gpu_cursor_helper_funcs;
	पूर्ण अन्यथा अणु
		क्रमmats = virtio_gpu_क्रमmats;
		nक्रमmats = ARRAY_SIZE(virtio_gpu_क्रमmats);
		funcs = &virtio_gpu_primary_helper_funcs;
	पूर्ण
	ret = drm_universal_plane_init(dev, plane, 1 << index,
				       &virtio_gpu_plane_funcs,
				       क्रमmats, nक्रमmats,
				       शून्य, type, शून्य);
	अगर (ret)
		जाओ err_plane_init;

	drm_plane_helper_add(plane, funcs);
	वापस plane;

err_plane_init:
	kमुक्त(plane);
	वापस ERR_PTR(ret);
पूर्ण
