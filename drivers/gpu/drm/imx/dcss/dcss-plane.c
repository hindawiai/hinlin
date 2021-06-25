<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>

#समावेश "dcss-dev.h"
#समावेश "dcss-kms.h"

अटल स्थिर u32 dcss_common_क्रमmats[] = अणु
	/* RGB */
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_RGBX1010102,
	DRM_FORMAT_BGRX1010102,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_RGBA1010102,
	DRM_FORMAT_BGRA1010102,
पूर्ण;

अटल स्थिर u64 dcss_video_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल स्थिर u64 dcss_graphics_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_VIVANTE_TILED,
	DRM_FORMAT_MOD_VIVANTE_SUPER_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल अंतरभूत काष्ठा dcss_plane *to_dcss_plane(काष्ठा drm_plane *p)
अणु
	वापस container_of(p, काष्ठा dcss_plane, base);
पूर्ण

अटल अंतरभूत bool dcss_plane_fb_is_linear(स्थिर काष्ठा drm_framebuffer *fb)
अणु
	वापस ((fb->flags & DRM_MODE_FB_MODIFIERS) == 0) ||
	       ((fb->flags & DRM_MODE_FB_MODIFIERS) != 0 &&
		fb->modअगरier == DRM_FORMAT_MOD_LINEAR);
पूर्ण

अटल व्योम dcss_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा dcss_plane *dcss_plane = container_of(plane, काष्ठा dcss_plane,
						     base);

	drm_plane_cleanup(plane);
	kमुक्त(dcss_plane);
पूर्ण

अटल bool dcss_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					    u32 क्रमmat,
					    u64 modअगरier)
अणु
	चयन (plane->type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
		चयन (क्रमmat) अणु
		हाल DRM_FORMAT_ARGB8888:
		हाल DRM_FORMAT_XRGB8888:
		हाल DRM_FORMAT_ARGB2101010:
			वापस modअगरier == DRM_FORMAT_MOD_LINEAR ||
			       modअगरier == DRM_FORMAT_MOD_VIVANTE_TILED ||
			       modअगरier == DRM_FORMAT_MOD_VIVANTE_SUPER_TILED;
		शेष:
			वापस modअगरier == DRM_FORMAT_MOD_LINEAR;
		पूर्ण
		अवरोध;
	हाल DRM_PLANE_TYPE_OVERLAY:
		वापस modअगरier == DRM_FORMAT_MOD_LINEAR;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs dcss_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= dcss_plane_destroy,
	.reset			= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
	.क्रमmat_mod_supported	= dcss_plane_क्रमmat_mod_supported,
पूर्ण;

अटल bool dcss_plane_can_rotate(स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				  bool mod_present, u64 modअगरier,
				  अचिन्हित पूर्णांक rotation)
अणु
	bool linear_क्रमmat = !mod_present || modअगरier == DRM_FORMAT_MOD_LINEAR;
	u32 supported_rotation = DRM_MODE_ROTATE_0;

	अगर (!क्रमmat->is_yuv && linear_क्रमmat)
		supported_rotation = DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
				     DRM_MODE_REFLECT_MASK;
	अन्यथा अगर (!क्रमmat->is_yuv &&
		 (modअगरier == DRM_FORMAT_MOD_VIVANTE_TILED ||
		  modअगरier == DRM_FORMAT_MOD_VIVANTE_SUPER_TILED))
		supported_rotation = DRM_MODE_ROTATE_MASK |
				     DRM_MODE_REFLECT_MASK;
	अन्यथा अगर (क्रमmat->is_yuv && linear_क्रमmat &&
		 (क्रमmat->क्रमmat == DRM_FORMAT_NV12 ||
		  क्रमmat->क्रमmat == DRM_FORMAT_NV21))
		supported_rotation = DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
				     DRM_MODE_REFLECT_MASK;

	वापस !!(rotation & supported_rotation);
पूर्ण

अटल bool dcss_plane_is_source_size_allowed(u16 src_w, u16 src_h, u32 pix_fmt)
अणु
	अगर (src_w < 64 &&
	    (pix_fmt == DRM_FORMAT_NV12 || pix_fmt == DRM_FORMAT_NV21))
		वापस false;
	अन्यथा अगर (src_w < 32 &&
		 (pix_fmt == DRM_FORMAT_UYVY || pix_fmt == DRM_FORMAT_VYUY ||
		  pix_fmt == DRM_FORMAT_YUYV || pix_fmt == DRM_FORMAT_YVYU))
		वापस false;

	वापस src_w >= 16 && src_h >= 8;
पूर्ण

अटल पूर्णांक dcss_plane_atomic_check(काष्ठा drm_plane *plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा dcss_plane *dcss_plane = to_dcss_plane(plane);
	काष्ठा dcss_dev *dcss = plane->dev->dev_निजी;
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	bool is_primary_plane = plane->type == DRM_PLANE_TYPE_PRIMARY;
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक hdisplay, vdisplay;
	पूर्णांक min, max;
	पूर्णांक ret;

	अगर (!fb || !new_plane_state->crtc)
		वापस 0;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	WARN_ON(!cma_obj);

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							new_plane_state->crtc);

	hdisplay = crtc_state->adjusted_mode.hdisplay;
	vdisplay = crtc_state->adjusted_mode.vdisplay;

	अगर (!dcss_plane_is_source_size_allowed(new_plane_state->src_w >> 16,
					       new_plane_state->src_h >> 16,
					       fb->क्रमmat->क्रमmat)) अणु
		DRM_DEBUG_KMS("Source plane size is not allowed!\n");
		वापस -EINVAL;
	पूर्ण

	dcss_scaler_get_min_max_ratios(dcss->scaler, dcss_plane->ch_num,
				       &min, &max);

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  min, max, !is_primary_plane,
						  false);
	अगर (ret)
		वापस ret;

	अगर (!new_plane_state->visible)
		वापस 0;

	अगर (!dcss_plane_can_rotate(fb->क्रमmat,
				   !!(fb->flags & DRM_MODE_FB_MODIFIERS),
				   fb->modअगरier,
				   new_plane_state->rotation)) अणु
		DRM_DEBUG_KMS("requested rotation is not allowed!\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((new_plane_state->crtc_x < 0 || new_plane_state->crtc_y < 0 ||
	     new_plane_state->crtc_x + new_plane_state->crtc_w > hdisplay ||
	     new_plane_state->crtc_y + new_plane_state->crtc_h > vdisplay) &&
	    !dcss_plane_fb_is_linear(fb)) अणु
		DRM_DEBUG_KMS("requested cropping operation is not allowed!\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((fb->flags & DRM_MODE_FB_MODIFIERS) &&
	    !plane->funcs->क्रमmat_mod_supported(plane,
				fb->क्रमmat->क्रमmat,
				fb->modअगरier)) अणु
		DRM_DEBUG_KMS("Invalid modifier: %llx", fb->modअगरier);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dcss_plane_atomic_set_base(काष्ठा dcss_plane *dcss_plane)
अणु
	काष्ठा drm_plane *plane = &dcss_plane->base;
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा dcss_dev *dcss = plane->dev->dev_निजी;
	काष्ठा drm_framebuffer *fb = state->fb;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	काष्ठा drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	अचिन्हित दीर्घ p1_ba = 0, p2_ba = 0;

	अगर (!क्रमmat->is_yuv ||
	    क्रमmat->क्रमmat == DRM_FORMAT_NV12 ||
	    क्रमmat->क्रमmat == DRM_FORMAT_NV21)
		p1_ba = cma_obj->paddr + fb->offsets[0] +
			fb->pitches[0] * (state->src.y1 >> 16) +
			क्रमmat->अक्षर_per_block[0] * (state->src.x1 >> 16);
	अन्यथा अगर (क्रमmat->क्रमmat == DRM_FORMAT_UYVY ||
		 क्रमmat->क्रमmat == DRM_FORMAT_VYUY ||
		 क्रमmat->क्रमmat == DRM_FORMAT_YUYV ||
		 क्रमmat->क्रमmat == DRM_FORMAT_YVYU)
		p1_ba = cma_obj->paddr + fb->offsets[0] +
			fb->pitches[0] * (state->src.y1 >> 16) +
			2 * क्रमmat->अक्षर_per_block[0] * (state->src.x1 >> 17);

	अगर (क्रमmat->क्रमmat == DRM_FORMAT_NV12 ||
	    क्रमmat->क्रमmat == DRM_FORMAT_NV21)
		p2_ba = cma_obj->paddr + fb->offsets[1] +
			(((fb->pitches[1] >> 1) * (state->src.y1 >> 17) +
			(state->src.x1 >> 17)) << 1);

	dcss_dpr_addr_set(dcss->dpr, dcss_plane->ch_num, p1_ba, p2_ba,
			  fb->pitches[0]);
पूर्ण

अटल bool dcss_plane_needs_setup(काष्ठा drm_plane_state *state,
				   काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_framebuffer *old_fb = old_state->fb;

	वापस state->crtc_x != old_state->crtc_x ||
	       state->crtc_y != old_state->crtc_y ||
	       state->crtc_w != old_state->crtc_w ||
	       state->crtc_h != old_state->crtc_h ||
	       state->src_x  != old_state->src_x  ||
	       state->src_y  != old_state->src_y  ||
	       state->src_w  != old_state->src_w  ||
	       state->src_h  != old_state->src_h  ||
	       fb->क्रमmat->क्रमmat != old_fb->क्रमmat->क्रमmat ||
	       fb->modअगरier  != old_fb->modअगरier ||
	       state->rotation != old_state->rotation ||
	       state->scaling_filter != old_state->scaling_filter;
पूर्ण

अटल व्योम dcss_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा dcss_plane *dcss_plane = to_dcss_plane(plane);
	काष्ठा dcss_dev *dcss = plane->dev->dev_निजी;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_crtc_state *crtc_state;
	bool modअगरiers_present;
	u32 src_w, src_h, dst_w, dst_h;
	काष्ठा drm_rect src, dst;
	bool enable = true;
	bool is_rotation_90_or_270;

	अगर (!fb || !new_state->crtc || !new_state->visible)
		वापस;

	crtc_state = new_state->crtc->state;
	modअगरiers_present = !!(fb->flags & DRM_MODE_FB_MODIFIERS);

	अगर (old_state->fb && !drm_atomic_crtc_needs_modeset(crtc_state) &&
	    !dcss_plane_needs_setup(new_state, old_state)) अणु
		dcss_plane_atomic_set_base(dcss_plane);
		वापस;
	पूर्ण

	src = plane->state->src;
	dst = plane->state->dst;

	/*
	 * The width and height after clipping.
	 */
	src_w = drm_rect_width(&src) >> 16;
	src_h = drm_rect_height(&src) >> 16;
	dst_w = drm_rect_width(&dst);
	dst_h = drm_rect_height(&dst);

	अगर (plane->type == DRM_PLANE_TYPE_OVERLAY &&
	    modअगरiers_present && fb->modअगरier == DRM_FORMAT_MOD_LINEAR)
		modअगरiers_present = false;

	dcss_dpr_क्रमmat_set(dcss->dpr, dcss_plane->ch_num,
			    new_state->fb->क्रमmat,
			    modअगरiers_present ? fb->modअगरier :
						DRM_FORMAT_MOD_LINEAR);
	dcss_dpr_set_res(dcss->dpr, dcss_plane->ch_num, src_w, src_h);
	dcss_dpr_set_rotation(dcss->dpr, dcss_plane->ch_num,
			      new_state->rotation);

	dcss_plane_atomic_set_base(dcss_plane);

	is_rotation_90_or_270 = new_state->rotation & (DRM_MODE_ROTATE_90 |
						   DRM_MODE_ROTATE_270);

	dcss_scaler_set_filter(dcss->scaler, dcss_plane->ch_num,
			       new_state->scaling_filter);

	dcss_scaler_setup(dcss->scaler, dcss_plane->ch_num,
			  new_state->fb->क्रमmat,
			  is_rotation_90_or_270 ? src_h : src_w,
			  is_rotation_90_or_270 ? src_w : src_h,
			  dst_w, dst_h,
			  drm_mode_vrefresh(&crtc_state->mode));

	dcss_dtg_plane_pos_set(dcss->dtg, dcss_plane->ch_num,
			       dst.x1, dst.y1, dst_w, dst_h);
	dcss_dtg_plane_alpha_set(dcss->dtg, dcss_plane->ch_num,
				 fb->क्रमmat, new_state->alpha >> 8);

	अगर (!dcss_plane->ch_num && (new_state->alpha >> 8) == 0)
		enable = false;

	dcss_dpr_enable(dcss->dpr, dcss_plane->ch_num, enable);
	dcss_scaler_ch_enable(dcss->scaler, dcss_plane->ch_num, enable);

	अगर (!enable)
		dcss_dtg_plane_pos_set(dcss->dtg, dcss_plane->ch_num,
				       0, 0, 0, 0);

	dcss_dtg_ch_enable(dcss->dtg, dcss_plane->ch_num, enable);
पूर्ण

अटल व्योम dcss_plane_atomic_disable(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा dcss_plane *dcss_plane = to_dcss_plane(plane);
	काष्ठा dcss_dev *dcss = plane->dev->dev_निजी;

	dcss_dpr_enable(dcss->dpr, dcss_plane->ch_num, false);
	dcss_scaler_ch_enable(dcss->scaler, dcss_plane->ch_num, false);
	dcss_dtg_plane_pos_set(dcss->dtg, dcss_plane->ch_num, 0, 0, 0, 0);
	dcss_dtg_ch_enable(dcss->dtg, dcss_plane->ch_num, false);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs dcss_plane_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = dcss_plane_atomic_check,
	.atomic_update = dcss_plane_atomic_update,
	.atomic_disable = dcss_plane_atomic_disable,
पूर्ण;

काष्ठा dcss_plane *dcss_plane_init(काष्ठा drm_device *drm,
				   अचिन्हित पूर्णांक possible_crtcs,
				   क्रमागत drm_plane_type type,
				   अचिन्हित पूर्णांक zpos)
अणु
	काष्ठा dcss_plane *dcss_plane;
	स्थिर u64 *क्रमmat_modअगरiers = dcss_video_क्रमmat_modअगरiers;
	पूर्णांक ret;

	अगर (zpos > 2)
		वापस ERR_PTR(-EINVAL);

	dcss_plane = kzalloc(माप(*dcss_plane), GFP_KERNEL);
	अगर (!dcss_plane) अणु
		DRM_ERROR("failed to allocate plane\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (type == DRM_PLANE_TYPE_PRIMARY)
		क्रमmat_modअगरiers = dcss_graphics_क्रमmat_modअगरiers;

	ret = drm_universal_plane_init(drm, &dcss_plane->base, possible_crtcs,
				       &dcss_plane_funcs, dcss_common_क्रमmats,
				       ARRAY_SIZE(dcss_common_क्रमmats),
				       क्रमmat_modअगरiers, type, शून्य);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize plane\n");
		kमुक्त(dcss_plane);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_plane_helper_add(&dcss_plane->base, &dcss_plane_helper_funcs);

	ret = drm_plane_create_zpos_immutable_property(&dcss_plane->base, zpos);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_plane_create_scaling_filter_property(&dcss_plane->base,
					BIT(DRM_SCALING_FILTER_DEFAULT) |
					BIT(DRM_SCALING_FILTER_NEAREST_NEIGHBOR));

	drm_plane_create_rotation_property(&dcss_plane->base,
					   DRM_MODE_ROTATE_0,
					   DRM_MODE_ROTATE_0   |
					   DRM_MODE_ROTATE_90  |
					   DRM_MODE_ROTATE_180 |
					   DRM_MODE_ROTATE_270 |
					   DRM_MODE_REFLECT_X  |
					   DRM_MODE_REFLECT_Y);

	dcss_plane->ch_num = zpos;

	वापस dcss_plane;
पूर्ण
