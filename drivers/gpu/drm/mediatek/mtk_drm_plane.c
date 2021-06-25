<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: CK Hu <ck.hu@mediatek.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "mtk_drm_crtc.h"
#समावेश "mtk_drm_ddp_comp.h"
#समावेश "mtk_drm_drv.h"
#समावेश "mtk_drm_gem.h"
#समावेश "mtk_drm_plane.h"

अटल स्थिर u32 क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
पूर्ण;

अटल व्योम mtk_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा mtk_plane_state *state;

	अगर (plane->state) अणु
		__drm_atomic_helper_plane_destroy_state(plane->state);

		state = to_mtk_plane_state(plane->state);
		स_रखो(state, 0, माप(*state));
	पूर्ण अन्यथा अणु
		state = kzalloc(माप(*state), GFP_KERNEL);
		अगर (!state)
			वापस;
		plane->state = &state->base;
	पूर्ण

	state->base.plane = plane;
	state->pending.क्रमmat = DRM_FORMAT_RGB565;
पूर्ण

अटल काष्ठा drm_plane_state *mtk_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा mtk_plane_state *old_state = to_mtk_plane_state(plane->state);
	काष्ठा mtk_plane_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &state->base);

	WARN_ON(state->base.plane != plane);

	state->pending = old_state->pending;

	वापस &state->base;
पूर्ण

अटल व्योम mtk_drm_plane_destroy_state(काष्ठा drm_plane *plane,
					काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(to_mtk_plane_state(state));
पूर्ण

अटल पूर्णांक mtk_plane_atomic_async_check(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	अगर (plane != new_plane_state->crtc->cursor)
		वापस -EINVAL;

	अगर (!plane->state)
		वापस -EINVAL;

	अगर (!plane->state->fb)
		वापस -EINVAL;

	ret = mtk_drm_crtc_plane_check(new_plane_state->crtc, plane,
				       to_mtk_plane_state(new_plane_state));
	अगर (ret)
		वापस ret;

	अगर (state)
		crtc_state = drm_atomic_get_existing_crtc_state(state,
								new_plane_state->crtc);
	अन्यथा /* Special हाल क्रम asynchronous cursor updates. */
		crtc_state = new_plane_state->crtc->state;

	वापस drm_atomic_helper_check_plane_state(plane->state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   true, true);
पूर्ण

अटल व्योम mtk_plane_atomic_async_update(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा mtk_plane_state *new_plane_state = to_mtk_plane_state(plane->state);

	plane->state->crtc_x = new_state->crtc_x;
	plane->state->crtc_y = new_state->crtc_y;
	plane->state->crtc_h = new_state->crtc_h;
	plane->state->crtc_w = new_state->crtc_w;
	plane->state->src_x = new_state->src_x;
	plane->state->src_y = new_state->src_y;
	plane->state->src_h = new_state->src_h;
	plane->state->src_w = new_state->src_w;
	swap(plane->state->fb, new_state->fb);
	new_plane_state->pending.async_dirty = true;

	mtk_drm_crtc_async_update(new_state->crtc, plane, state);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs mtk_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = mtk_plane_reset,
	.atomic_duplicate_state = mtk_plane_duplicate_state,
	.atomic_destroy_state = mtk_drm_plane_destroy_state,
पूर्ण;

अटल पूर्णांक mtk_plane_atomic_check(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	अगर (!fb)
		वापस 0;

	अगर (WARN_ON(!new_plane_state->crtc))
		वापस 0;

	ret = mtk_drm_crtc_plane_check(new_plane_state->crtc, plane,
				       to_mtk_plane_state(new_plane_state));
	अगर (ret)
		वापस ret;

	crtc_state = drm_atomic_get_crtc_state(state,
					       new_plane_state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	वापस drm_atomic_helper_check_plane_state(new_plane_state,
						   crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   true, true);
पूर्ण

अटल व्योम mtk_plane_atomic_disable(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा mtk_plane_state *mtk_plane_state = to_mtk_plane_state(new_state);
	mtk_plane_state->pending.enable = false;
	wmb(); /* Make sure the above parameter is set beक्रमe update */
	mtk_plane_state->pending.dirty = true;
पूर्ण

अटल व्योम mtk_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा mtk_plane_state *mtk_plane_state = to_mtk_plane_state(new_state);
	काष्ठा drm_crtc *crtc = new_state->crtc;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_gem_object *gem;
	काष्ठा mtk_drm_gem_obj *mtk_gem;
	अचिन्हित पूर्णांक pitch, क्रमmat;
	dma_addr_t addr;

	अगर (!crtc || WARN_ON(!fb))
		वापस;

	अगर (!new_state->visible) अणु
		mtk_plane_atomic_disable(plane, state);
		वापस;
	पूर्ण

	gem = fb->obj[0];
	mtk_gem = to_mtk_gem_obj(gem);
	addr = mtk_gem->dma_addr;
	pitch = fb->pitches[0];
	क्रमmat = fb->क्रमmat->क्रमmat;

	addr += (new_state->src.x1 >> 16) * fb->क्रमmat->cpp[0];
	addr += (new_state->src.y1 >> 16) * pitch;

	mtk_plane_state->pending.enable = true;
	mtk_plane_state->pending.pitch = pitch;
	mtk_plane_state->pending.क्रमmat = क्रमmat;
	mtk_plane_state->pending.addr = addr;
	mtk_plane_state->pending.x = new_state->dst.x1;
	mtk_plane_state->pending.y = new_state->dst.y1;
	mtk_plane_state->pending.width = drm_rect_width(&new_state->dst);
	mtk_plane_state->pending.height = drm_rect_height(&new_state->dst);
	mtk_plane_state->pending.rotation = new_state->rotation;
	wmb(); /* Make sure the above parameters are set beक्रमe update */
	mtk_plane_state->pending.dirty = true;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs mtk_plane_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = mtk_plane_atomic_check,
	.atomic_update = mtk_plane_atomic_update,
	.atomic_disable = mtk_plane_atomic_disable,
	.atomic_async_update = mtk_plane_atomic_async_update,
	.atomic_async_check = mtk_plane_atomic_async_check,
पूर्ण;

पूर्णांक mtk_plane_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
		   अचिन्हित दीर्घ possible_crtcs, क्रमागत drm_plane_type type,
		   अचिन्हित पूर्णांक supported_rotations)
अणु
	पूर्णांक err;

	err = drm_universal_plane_init(dev, plane, possible_crtcs,
				       &mtk_plane_funcs, क्रमmats,
				       ARRAY_SIZE(क्रमmats), शून्य, type, शून्य);
	अगर (err) अणु
		DRM_ERROR("failed to initialize plane\n");
		वापस err;
	पूर्ण

	अगर (supported_rotations & ~DRM_MODE_ROTATE_0) अणु
		err = drm_plane_create_rotation_property(plane,
							 DRM_MODE_ROTATE_0,
							 supported_rotations);
		अगर (err)
			DRM_INFO("Create rotation property failed\n");
	पूर्ण

	drm_plane_helper_add(plane, &mtk_plane_helper_funcs);

	वापस 0;
पूर्ण
