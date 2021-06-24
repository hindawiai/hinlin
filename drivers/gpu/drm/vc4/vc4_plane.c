<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Broadcom
 */

/**
 * DOC: VC4 plane module
 *
 * Each DRM plane is a layer of pixels being scanned out by the HVS.
 *
 * At atomic modeset check समय, we compute the HVS display element
 * state that would be necessary क्रम displaying the plane (giving us a
 * chance to figure out अगर a plane configuration is invalid), then at
 * atomic flush समय the CRTC will ask us to ग_लिखो our element state
 * पूर्णांकo the region of the HVS that it has allocated क्रम us.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "uapi/drm/vc4_drm.h"

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

अटल स्थिर काष्ठा hvs_क्रमmat अणु
	u32 drm; /* DRM_FORMAT_* */
	u32 hvs; /* HVS_FORMAT_* */
	u32 pixel_order;
	u32 pixel_order_hvs5;
पूर्ण hvs_क्रमmats[] = अणु
	अणु
		.drm = DRM_FORMAT_XRGB8888,
		.hvs = HVS_PIXEL_FORMAT_RGBA8888,
		.pixel_order = HVS_PIXEL_ORDER_ABGR,
		.pixel_order_hvs5 = HVS_PIXEL_ORDER_ARGB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_ARGB8888,
		.hvs = HVS_PIXEL_FORMAT_RGBA8888,
		.pixel_order = HVS_PIXEL_ORDER_ABGR,
		.pixel_order_hvs5 = HVS_PIXEL_ORDER_ARGB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_ABGR8888,
		.hvs = HVS_PIXEL_FORMAT_RGBA8888,
		.pixel_order = HVS_PIXEL_ORDER_ARGB,
		.pixel_order_hvs5 = HVS_PIXEL_ORDER_ABGR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_XBGR8888,
		.hvs = HVS_PIXEL_FORMAT_RGBA8888,
		.pixel_order = HVS_PIXEL_ORDER_ARGB,
		.pixel_order_hvs5 = HVS_PIXEL_ORDER_ABGR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_RGB565,
		.hvs = HVS_PIXEL_FORMAT_RGB565,
		.pixel_order = HVS_PIXEL_ORDER_XRGB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_BGR565,
		.hvs = HVS_PIXEL_FORMAT_RGB565,
		.pixel_order = HVS_PIXEL_ORDER_XBGR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_ARGB1555,
		.hvs = HVS_PIXEL_FORMAT_RGBA5551,
		.pixel_order = HVS_PIXEL_ORDER_ABGR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_XRGB1555,
		.hvs = HVS_PIXEL_FORMAT_RGBA5551,
		.pixel_order = HVS_PIXEL_ORDER_ABGR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_RGB888,
		.hvs = HVS_PIXEL_FORMAT_RGB888,
		.pixel_order = HVS_PIXEL_ORDER_XRGB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_BGR888,
		.hvs = HVS_PIXEL_FORMAT_RGB888,
		.pixel_order = HVS_PIXEL_ORDER_XBGR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_YUV422,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV422_3PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCBCR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_YVU422,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV422_3PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCRCB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_YUV420,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV420_3PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCBCR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_YVU420,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV420_3PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCRCB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_NV12,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV420_2PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCBCR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_NV21,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV420_2PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCRCB,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_NV16,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV422_2PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCBCR,
	पूर्ण,
	अणु
		.drm = DRM_FORMAT_NV61,
		.hvs = HVS_PIXEL_FORMAT_YCBCR_YUV422_2PLANE,
		.pixel_order = HVS_PIXEL_ORDER_XYCRCB,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hvs_क्रमmat *vc4_get_hvs_क्रमmat(u32 drm_क्रमmat)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < ARRAY_SIZE(hvs_क्रमmats); i++) अणु
		अगर (hvs_क्रमmats[i].drm == drm_क्रमmat)
			वापस &hvs_क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत vc4_scaling_mode vc4_get_scaling_mode(u32 src, u32 dst)
अणु
	अगर (dst == src)
		वापस VC4_SCALING_NONE;
	अगर (3 * dst >= 2 * src)
		वापस VC4_SCALING_PPF;
	अन्यथा
		वापस VC4_SCALING_TPZ;
पूर्ण

अटल bool plane_enabled(काष्ठा drm_plane_state *state)
अणु
	वापस state->fb && !WARN_ON(!state->crtc);
पूर्ण

अटल काष्ठा drm_plane_state *vc4_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा vc4_plane_state *vc4_state;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	vc4_state = kmemdup(plane->state, माप(*vc4_state), GFP_KERNEL);
	अगर (!vc4_state)
		वापस शून्य;

	स_रखो(&vc4_state->lbm, 0, माप(vc4_state->lbm));
	vc4_state->dlist_initialized = 0;

	__drm_atomic_helper_plane_duplicate_state(plane, &vc4_state->base);

	अगर (vc4_state->dlist) अणु
		vc4_state->dlist = kmemdup(vc4_state->dlist,
					   vc4_state->dlist_count * 4,
					   GFP_KERNEL);
		अगर (!vc4_state->dlist) अणु
			kमुक्त(vc4_state);
			वापस शून्य;
		पूर्ण
		vc4_state->dlist_size = vc4_state->dlist_count;
	पूर्ण

	वापस &vc4_state->base;
पूर्ण

अटल व्योम vc4_plane_destroy_state(काष्ठा drm_plane *plane,
				    काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(plane->dev);
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);

	अगर (drm_mm_node_allocated(&vc4_state->lbm)) अणु
		अचिन्हित दीर्घ irqflags;

		spin_lock_irqsave(&vc4->hvs->mm_lock, irqflags);
		drm_mm_हटाओ_node(&vc4_state->lbm);
		spin_unlock_irqrestore(&vc4->hvs->mm_lock, irqflags);
	पूर्ण

	kमुक्त(vc4_state->dlist);
	__drm_atomic_helper_plane_destroy_state(&vc4_state->base);
	kमुक्त(state);
पूर्ण

/* Called during init to allocate the plane's atomic state. */
अटल व्योम vc4_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा vc4_plane_state *vc4_state;

	WARN_ON(plane->state);

	vc4_state = kzalloc(माप(*vc4_state), GFP_KERNEL);
	अगर (!vc4_state)
		वापस;

	__drm_atomic_helper_plane_reset(plane, &vc4_state->base);
पूर्ण

अटल व्योम vc4_dlist_counter_increment(काष्ठा vc4_plane_state *vc4_state)
अणु
	अगर (vc4_state->dlist_count == vc4_state->dlist_size) अणु
		u32 new_size = max(4u, vc4_state->dlist_count * 2);
		u32 *new_dlist = kदो_स्मृति_array(new_size, 4, GFP_KERNEL);

		अगर (!new_dlist)
			वापस;
		स_नकल(new_dlist, vc4_state->dlist, vc4_state->dlist_count * 4);

		kमुक्त(vc4_state->dlist);
		vc4_state->dlist = new_dlist;
		vc4_state->dlist_size = new_size;
	पूर्ण

	vc4_state->dlist_count++;
पूर्ण

अटल व्योम vc4_dlist_ग_लिखो(काष्ठा vc4_plane_state *vc4_state, u32 val)
अणु
	अचिन्हित पूर्णांक idx = vc4_state->dlist_count;

	vc4_dlist_counter_increment(vc4_state);
	vc4_state->dlist[idx] = val;
पूर्ण

/* Returns the scl0/scl1 field based on whether the dimensions need to
 * be up/करोwn/non-scaled.
 *
 * This is a replication of a table from the spec.
 */
अटल u32 vc4_get_scl_field(काष्ठा drm_plane_state *state, पूर्णांक plane)
अणु
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);

	चयन (vc4_state->x_scaling[plane] << 2 | vc4_state->y_scaling[plane]) अणु
	हाल VC4_SCALING_PPF << 2 | VC4_SCALING_PPF:
		वापस SCALER_CTL0_SCL_H_PPF_V_PPF;
	हाल VC4_SCALING_TPZ << 2 | VC4_SCALING_PPF:
		वापस SCALER_CTL0_SCL_H_TPZ_V_PPF;
	हाल VC4_SCALING_PPF << 2 | VC4_SCALING_TPZ:
		वापस SCALER_CTL0_SCL_H_PPF_V_TPZ;
	हाल VC4_SCALING_TPZ << 2 | VC4_SCALING_TPZ:
		वापस SCALER_CTL0_SCL_H_TPZ_V_TPZ;
	हाल VC4_SCALING_PPF << 2 | VC4_SCALING_NONE:
		वापस SCALER_CTL0_SCL_H_PPF_V_NONE;
	हाल VC4_SCALING_NONE << 2 | VC4_SCALING_PPF:
		वापस SCALER_CTL0_SCL_H_NONE_V_PPF;
	हाल VC4_SCALING_NONE << 2 | VC4_SCALING_TPZ:
		वापस SCALER_CTL0_SCL_H_NONE_V_TPZ;
	हाल VC4_SCALING_TPZ << 2 | VC4_SCALING_NONE:
		वापस SCALER_CTL0_SCL_H_TPZ_V_NONE;
	शेष:
	हाल VC4_SCALING_NONE << 2 | VC4_SCALING_NONE:
		/* The unity हाल is independently handled by
		 * SCALER_CTL0_UNITY.
		 */
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_plane_margins_adj(काष्ठा drm_plane_state *pstate)
अणु
	काष्ठा vc4_plane_state *vc4_pstate = to_vc4_plane_state(pstate);
	अचिन्हित पूर्णांक left, right, top, bottom, adjhdisplay, adjvdisplay;
	काष्ठा drm_crtc_state *crtc_state;

	crtc_state = drm_atomic_get_new_crtc_state(pstate->state,
						   pstate->crtc);

	vc4_crtc_get_margins(crtc_state, &left, &right, &top, &bottom);
	अगर (!left && !right && !top && !bottom)
		वापस 0;

	अगर (left + right >= crtc_state->mode.hdisplay ||
	    top + bottom >= crtc_state->mode.vdisplay)
		वापस -EINVAL;

	adjhdisplay = crtc_state->mode.hdisplay - (left + right);
	vc4_pstate->crtc_x = DIV_ROUND_CLOSEST(vc4_pstate->crtc_x *
					       adjhdisplay,
					       crtc_state->mode.hdisplay);
	vc4_pstate->crtc_x += left;
	अगर (vc4_pstate->crtc_x > crtc_state->mode.hdisplay - left)
		vc4_pstate->crtc_x = crtc_state->mode.hdisplay - left;

	adjvdisplay = crtc_state->mode.vdisplay - (top + bottom);
	vc4_pstate->crtc_y = DIV_ROUND_CLOSEST(vc4_pstate->crtc_y *
					       adjvdisplay,
					       crtc_state->mode.vdisplay);
	vc4_pstate->crtc_y += top;
	अगर (vc4_pstate->crtc_y > crtc_state->mode.vdisplay - top)
		vc4_pstate->crtc_y = crtc_state->mode.vdisplay - top;

	vc4_pstate->crtc_w = DIV_ROUND_CLOSEST(vc4_pstate->crtc_w *
					       adjhdisplay,
					       crtc_state->mode.hdisplay);
	vc4_pstate->crtc_h = DIV_ROUND_CLOSEST(vc4_pstate->crtc_h *
					       adjvdisplay,
					       crtc_state->mode.vdisplay);

	अगर (!vc4_pstate->crtc_w || !vc4_pstate->crtc_h)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_plane_setup_clipping_and_scaling(काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *bo = drm_fb_cma_get_gem_obj(fb, 0);
	u32 subpixel_src_mask = (1 << 16) - 1;
	पूर्णांक num_planes = fb->क्रमmat->num_planes;
	काष्ठा drm_crtc_state *crtc_state;
	u32 h_subsample = fb->क्रमmat->hsub;
	u32 v_subsample = fb->क्रमmat->vsub;
	पूर्णांक i, ret;

	crtc_state = drm_atomic_get_existing_crtc_state(state->state,
							state->crtc);
	अगर (!crtc_state) अणु
		DRM_DEBUG_KMS("Invalid crtc state\n");
		वापस -EINVAL;
	पूर्ण

	ret = drm_atomic_helper_check_plane_state(state, crtc_state, 1,
						  पूर्णांक_उच्च, true, true);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num_planes; i++)
		vc4_state->offsets[i] = bo->paddr + fb->offsets[i];

	/* We करोn't support subpixel source positioning क्रम scaling. */
	अगर ((state->src.x1 & subpixel_src_mask) ||
	    (state->src.x2 & subpixel_src_mask) ||
	    (state->src.y1 & subpixel_src_mask) ||
	    (state->src.y2 & subpixel_src_mask)) अणु
		वापस -EINVAL;
	पूर्ण

	vc4_state->src_x = state->src.x1 >> 16;
	vc4_state->src_y = state->src.y1 >> 16;
	vc4_state->src_w[0] = (state->src.x2 - state->src.x1) >> 16;
	vc4_state->src_h[0] = (state->src.y2 - state->src.y1) >> 16;

	vc4_state->crtc_x = state->dst.x1;
	vc4_state->crtc_y = state->dst.y1;
	vc4_state->crtc_w = state->dst.x2 - state->dst.x1;
	vc4_state->crtc_h = state->dst.y2 - state->dst.y1;

	ret = vc4_plane_margins_adj(state);
	अगर (ret)
		वापस ret;

	vc4_state->x_scaling[0] = vc4_get_scaling_mode(vc4_state->src_w[0],
						       vc4_state->crtc_w);
	vc4_state->y_scaling[0] = vc4_get_scaling_mode(vc4_state->src_h[0],
						       vc4_state->crtc_h);

	vc4_state->is_unity = (vc4_state->x_scaling[0] == VC4_SCALING_NONE &&
			       vc4_state->y_scaling[0] == VC4_SCALING_NONE);

	अगर (num_planes > 1) अणु
		vc4_state->is_yuv = true;

		vc4_state->src_w[1] = vc4_state->src_w[0] / h_subsample;
		vc4_state->src_h[1] = vc4_state->src_h[0] / v_subsample;

		vc4_state->x_scaling[1] =
			vc4_get_scaling_mode(vc4_state->src_w[1],
					     vc4_state->crtc_w);
		vc4_state->y_scaling[1] =
			vc4_get_scaling_mode(vc4_state->src_h[1],
					     vc4_state->crtc_h);

		/* YUV conversion requires that horizontal scaling be enabled
		 * on the UV plane even अगर vc4_get_scaling_mode() वापसed
		 * VC4_SCALING_NONE (which can happen when the करोwn-scaling
		 * ratio is 0.5). Let's क्रमce it to VC4_SCALING_PPF in this
		 * हाल.
		 */
		अगर (vc4_state->x_scaling[1] == VC4_SCALING_NONE)
			vc4_state->x_scaling[1] = VC4_SCALING_PPF;
	पूर्ण अन्यथा अणु
		vc4_state->is_yuv = false;
		vc4_state->x_scaling[1] = VC4_SCALING_NONE;
		vc4_state->y_scaling[1] = VC4_SCALING_NONE;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vc4_ग_लिखो_tpz(काष्ठा vc4_plane_state *vc4_state, u32 src, u32 dst)
अणु
	u32 scale, recip;

	scale = (1 << 16) * src / dst;

	/* The specs note that जबतक the reciprocal would be defined
	 * as (1<<32)/scale, ~0 is बंद enough.
	 */
	recip = ~0 / scale;

	vc4_dlist_ग_लिखो(vc4_state,
			VC4_SET_FIELD(scale, SCALER_TPZ0_SCALE) |
			VC4_SET_FIELD(0, SCALER_TPZ0_IPHASE));
	vc4_dlist_ग_लिखो(vc4_state,
			VC4_SET_FIELD(recip, SCALER_TPZ1_RECIP));
पूर्ण

अटल व्योम vc4_ग_लिखो_ppf(काष्ठा vc4_plane_state *vc4_state, u32 src, u32 dst)
अणु
	u32 scale = (1 << 16) * src / dst;

	vc4_dlist_ग_लिखो(vc4_state,
			SCALER_PPF_AGC |
			VC4_SET_FIELD(scale, SCALER_PPF_SCALE) |
			VC4_SET_FIELD(0, SCALER_PPF_IPHASE));
पूर्ण

अटल u32 vc4_lbm_size(काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(state->plane->dev);
	u32 pix_per_line;
	u32 lbm;

	/* LBM is not needed when there's no vertical scaling. */
	अगर (vc4_state->y_scaling[0] == VC4_SCALING_NONE &&
	    vc4_state->y_scaling[1] == VC4_SCALING_NONE)
		वापस 0;

	/*
	 * This can be further optimized in the RGB/YUV444 हाल अगर the PPF
	 * decimation factor is between 0.5 and 1.0 by using crtc_w.
	 *
	 * It's not an issue though, since in that हाल since src_w[0] is going
	 * to be greater than or equal to crtc_w.
	 */
	अगर (vc4_state->x_scaling[0] == VC4_SCALING_TPZ)
		pix_per_line = vc4_state->crtc_w;
	अन्यथा
		pix_per_line = vc4_state->src_w[0];

	अगर (!vc4_state->is_yuv) अणु
		अगर (vc4_state->y_scaling[0] == VC4_SCALING_TPZ)
			lbm = pix_per_line * 8;
		अन्यथा अणु
			/* In special हालs, this multiplier might be 12. */
			lbm = pix_per_line * 16;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* There are हालs क्रम this going करोwn to a multiplier
		 * of 2, but according to the firmware source, the
		 * table in the करोcs is somewhat wrong.
		 */
		lbm = pix_per_line * 16;
	पूर्ण

	/* Align it to 64 or 128 (hvs5) bytes */
	lbm = roundup(lbm, vc4->hvs->hvs5 ? 128 : 64);

	/* Each "word" of the LBM memory contains 2 or 4 (hvs5) pixels */
	lbm /= vc4->hvs->hvs5 ? 4 : 2;

	वापस lbm;
पूर्ण

अटल व्योम vc4_ग_लिखो_scaling_parameters(काष्ठा drm_plane_state *state,
					 पूर्णांक channel)
अणु
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);

	/* Ch0 H-PPF Word 0: Scaling Parameters */
	अगर (vc4_state->x_scaling[channel] == VC4_SCALING_PPF) अणु
		vc4_ग_लिखो_ppf(vc4_state,
			      vc4_state->src_w[channel], vc4_state->crtc_w);
	पूर्ण

	/* Ch0 V-PPF Words 0-1: Scaling Parameters, Context */
	अगर (vc4_state->y_scaling[channel] == VC4_SCALING_PPF) अणु
		vc4_ग_लिखो_ppf(vc4_state,
			      vc4_state->src_h[channel], vc4_state->crtc_h);
		vc4_dlist_ग_लिखो(vc4_state, 0xc0c0c0c0);
	पूर्ण

	/* Ch0 H-TPZ Words 0-1: Scaling Parameters, Recip */
	अगर (vc4_state->x_scaling[channel] == VC4_SCALING_TPZ) अणु
		vc4_ग_लिखो_tpz(vc4_state,
			      vc4_state->src_w[channel], vc4_state->crtc_w);
	पूर्ण

	/* Ch0 V-TPZ Words 0-2: Scaling Parameters, Recip, Context */
	अगर (vc4_state->y_scaling[channel] == VC4_SCALING_TPZ) अणु
		vc4_ग_लिखो_tpz(vc4_state,
			      vc4_state->src_h[channel], vc4_state->crtc_h);
		vc4_dlist_ग_लिखो(vc4_state, 0xc0c0c0c0);
	पूर्ण
पूर्ण

अटल व्योम vc4_plane_calc_load(काष्ठा drm_plane_state *state)
अणु
	अचिन्हित पूर्णांक hvs_load_shअगरt, vrefresh, i;
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा vc4_plane_state *vc4_state;
	काष्ठा drm_crtc_state *crtc_state;
	अचिन्हित पूर्णांक vscale_factor;
	काष्ठा vc4_dev *vc4;

	vc4 = to_vc4_dev(state->plane->dev);
	अगर (!vc4->load_tracker_available)
		वापस;

	vc4_state = to_vc4_plane_state(state);
	crtc_state = drm_atomic_get_existing_crtc_state(state->state,
							state->crtc);
	vrefresh = drm_mode_vrefresh(&crtc_state->adjusted_mode);

	/* The HVS is able to process 2 pixels/cycle when scaling the source,
	 * 4 pixels/cycle otherwise.
	 * Alpha blending step seems to be pipelined and it's always operating
	 * at 4 pixels/cycle, so the limiting aspect here seems to be the
	 * scaler block.
	 * HVS load is expressed in clk-cycles/sec (AKA Hz).
	 */
	अगर (vc4_state->x_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->x_scaling[1] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[1] != VC4_SCALING_NONE)
		hvs_load_shअगरt = 1;
	अन्यथा
		hvs_load_shअगरt = 2;

	vc4_state->membus_load = 0;
	vc4_state->hvs_load = 0;
	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		/* Even अगर the bandwidth/plane required क्रम a single frame is
		 *
		 * vc4_state->src_w[i] * vc4_state->src_h[i] * cpp * vrefresh
		 *
		 * when करोwnscaling, we have to पढ़ो more pixels per line in
		 * the समय frame reserved क्रम a single line, so the bandwidth
		 * demand can be punctually higher. To account क्रम that, we
		 * calculate the करोwn-scaling factor and multiply the plane
		 * load by this number. We're likely over-estimating the पढ़ो
		 * demand, but that's better than under-estimating it.
		 */
		vscale_factor = DIV_ROUND_UP(vc4_state->src_h[i],
					     vc4_state->crtc_h);
		vc4_state->membus_load += vc4_state->src_w[i] *
					  vc4_state->src_h[i] * vscale_factor *
					  fb->क्रमmat->cpp[i];
		vc4_state->hvs_load += vc4_state->crtc_h * vc4_state->crtc_w;
	पूर्ण

	vc4_state->hvs_load *= vrefresh;
	vc4_state->hvs_load >>= hvs_load_shअगरt;
	vc4_state->membus_load *= vrefresh;
पूर्ण

अटल पूर्णांक vc4_plane_allocate_lbm(काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(state->plane->dev);
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	अचिन्हित दीर्घ irqflags;
	u32 lbm_size;

	lbm_size = vc4_lbm_size(state);
	अगर (!lbm_size)
		वापस 0;

	अगर (WARN_ON(!vc4_state->lbm_offset))
		वापस -EINVAL;

	/* Allocate the LBM memory that the HVS will use क्रम temporary
	 * storage due to our scaling/क्रमmat conversion.
	 */
	अगर (!drm_mm_node_allocated(&vc4_state->lbm)) अणु
		पूर्णांक ret;

		spin_lock_irqsave(&vc4->hvs->mm_lock, irqflags);
		ret = drm_mm_insert_node_generic(&vc4->hvs->lbm_mm,
						 &vc4_state->lbm,
						 lbm_size,
						 vc4->hvs->hvs5 ? 64 : 32,
						 0, 0);
		spin_unlock_irqrestore(&vc4->hvs->mm_lock, irqflags);

		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(lbm_size != vc4_state->lbm.size);
	पूर्ण

	vc4_state->dlist[vc4_state->lbm_offset] = vc4_state->lbm.start;

	वापस 0;
पूर्ण

/* Writes out a full display list क्रम an active plane to the plane's
 * निजी dlist state.
 */
अटल पूर्णांक vc4_plane_mode_set(काष्ठा drm_plane *plane,
			      काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(plane->dev);
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	काष्ठा drm_framebuffer *fb = state->fb;
	u32 ctl0_offset = vc4_state->dlist_count;
	स्थिर काष्ठा hvs_क्रमmat *क्रमmat = vc4_get_hvs_क्रमmat(fb->क्रमmat->क्रमmat);
	u64 base_क्रमmat_mod = fourcc_mod_broadcom_mod(fb->modअगरier);
	पूर्णांक num_planes = fb->क्रमmat->num_planes;
	u32 h_subsample = fb->क्रमmat->hsub;
	u32 v_subsample = fb->क्रमmat->vsub;
	bool mix_plane_alpha;
	bool covers_screen;
	u32 scl0, scl1, pitch0;
	u32 tiling, src_y;
	u32 hvs_क्रमmat = क्रमmat->hvs;
	अचिन्हित पूर्णांक rotation;
	पूर्णांक ret, i;

	अगर (vc4_state->dlist_initialized)
		वापस 0;

	ret = vc4_plane_setup_clipping_and_scaling(state);
	अगर (ret)
		वापस ret;

	/* SCL1 is used क्रम Cb/Cr scaling of planar क्रमmats.  For RGB
	 * and 4:4:4, scl1 should be set to scl0 so both channels of
	 * the scaler करो the same thing.  For YUV, the Y plane needs
	 * to be put in channel 1 and Cb/Cr in channel 0, so we swap
	 * the scl fields here.
	 */
	अगर (num_planes == 1) अणु
		scl0 = vc4_get_scl_field(state, 0);
		scl1 = scl0;
	पूर्ण अन्यथा अणु
		scl0 = vc4_get_scl_field(state, 1);
		scl1 = vc4_get_scl_field(state, 0);
	पूर्ण

	rotation = drm_rotation_simplअगरy(state->rotation,
					 DRM_MODE_ROTATE_0 |
					 DRM_MODE_REFLECT_X |
					 DRM_MODE_REFLECT_Y);

	/* We must poपूर्णांक to the last line when Y reflection is enabled. */
	src_y = vc4_state->src_y;
	अगर (rotation & DRM_MODE_REFLECT_Y)
		src_y += vc4_state->src_h[0] - 1;

	चयन (base_क्रमmat_mod) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
		tiling = SCALER_CTL0_TILING_LINEAR;
		pitch0 = VC4_SET_FIELD(fb->pitches[0], SCALER_SRC_PITCH);

		/* Adjust the base poपूर्णांकer to the first pixel to be scanned
		 * out.
		 */
		क्रम (i = 0; i < num_planes; i++) अणु
			vc4_state->offsets[i] += src_y /
						 (i ? v_subsample : 1) *
						 fb->pitches[i];

			vc4_state->offsets[i] += vc4_state->src_x /
						 (i ? h_subsample : 1) *
						 fb->क्रमmat->cpp[i];
		पूर्ण

		अवरोध;

	हाल DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED: अणु
		u32 tile_size_shअगरt = 12; /* T tiles are 4kb */
		/* Whole-tile offsets, mostly क्रम setting the pitch. */
		u32 tile_w_shअगरt = fb->क्रमmat->cpp[0] == 2 ? 6 : 5;
		u32 tile_h_shअगरt = 5; /* 16 and 32bpp are 32 pixels high */
		u32 tile_w_mask = (1 << tile_w_shअगरt) - 1;
		/* The height mask on 32-bit-per-pixel tiles is 63, i.e. twice
		 * the height (in pixels) of a 4k tile.
		 */
		u32 tile_h_mask = (2 << tile_h_shअगरt) - 1;
		/* For T-tiled, the FB pitch is "how many bytes from one row to
		 * the next, such that
		 *
		 *	pitch * tile_h == tile_size * tiles_per_row
		 */
		u32 tiles_w = fb->pitches[0] >> (tile_size_shअगरt - tile_h_shअगरt);
		u32 tiles_l = vc4_state->src_x >> tile_w_shअगरt;
		u32 tiles_r = tiles_w - tiles_l;
		u32 tiles_t = src_y >> tile_h_shअगरt;
		/* Intra-tile offsets, which modअगरy the base address (the
		 * SCALER_PITCH0_TILE_Y_OFFSET tells HVS how to walk from that
		 * base address).
		 */
		u32 tile_y = (src_y >> 4) & 1;
		u32 subtile_y = (src_y >> 2) & 3;
		u32 utile_y = src_y & 3;
		u32 x_off = vc4_state->src_x & tile_w_mask;
		u32 y_off = src_y & tile_h_mask;

		/* When Y reflection is requested we must set the
		 * SCALER_PITCH0_TILE_LINE_सूची flag to tell HVS that all lines
		 * after the initial one should be fetched in descending order,
		 * which makes sense since we start from the last line and go
		 * backward.
		 * Don't know why we need y_off = max_y_off - y_off, but it's
		 * definitely required (I guess it's also related to the "going
		 * backward" situation).
		 */
		अगर (rotation & DRM_MODE_REFLECT_Y) अणु
			y_off = tile_h_mask - y_off;
			pitch0 = SCALER_PITCH0_TILE_LINE_सूची;
		पूर्ण अन्यथा अणु
			pitch0 = 0;
		पूर्ण

		tiling = SCALER_CTL0_TILING_256B_OR_T;
		pitch0 |= (VC4_SET_FIELD(x_off, SCALER_PITCH0_SINK_PIX) |
			   VC4_SET_FIELD(y_off, SCALER_PITCH0_TILE_Y_OFFSET) |
			   VC4_SET_FIELD(tiles_l, SCALER_PITCH0_TILE_WIDTH_L) |
			   VC4_SET_FIELD(tiles_r, SCALER_PITCH0_TILE_WIDTH_R));
		vc4_state->offsets[0] += tiles_t * (tiles_w << tile_size_shअगरt);
		vc4_state->offsets[0] += subtile_y << 8;
		vc4_state->offsets[0] += utile_y << 4;

		/* Rows of tiles alternate left-to-right and right-to-left. */
		अगर (tiles_t & 1) अणु
			pitch0 |= SCALER_PITCH0_TILE_INITIAL_LINE_सूची;
			vc4_state->offsets[0] += (tiles_w - tiles_l) <<
						 tile_size_shअगरt;
			vc4_state->offsets[0] -= (1 + !tile_y) << 10;
		पूर्ण अन्यथा अणु
			vc4_state->offsets[0] += tiles_l << tile_size_shअगरt;
			vc4_state->offsets[0] += tile_y << 10;
		पूर्ण

		अवरोध;
	पूर्ण

	हाल DRM_FORMAT_MOD_BROADCOM_SAND64:
	हाल DRM_FORMAT_MOD_BROADCOM_SAND128:
	हाल DRM_FORMAT_MOD_BROADCOM_SAND256: अणु
		uपूर्णांक32_t param = fourcc_mod_broadcom_param(fb->modअगरier);
		u32 tile_w, tile, x_off, pix_per_tile;

		hvs_क्रमmat = HVS_PIXEL_FORMAT_H264;

		चयन (base_क्रमmat_mod) अणु
		हाल DRM_FORMAT_MOD_BROADCOM_SAND64:
			tiling = SCALER_CTL0_TILING_64B;
			tile_w = 64;
			अवरोध;
		हाल DRM_FORMAT_MOD_BROADCOM_SAND128:
			tiling = SCALER_CTL0_TILING_128B;
			tile_w = 128;
			अवरोध;
		हाल DRM_FORMAT_MOD_BROADCOM_SAND256:
			tiling = SCALER_CTL0_TILING_256B_OR_T;
			tile_w = 256;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (param > SCALER_TILE_HEIGHT_MASK) अणु
			DRM_DEBUG_KMS("SAND height too large (%d)\n", param);
			वापस -EINVAL;
		पूर्ण

		pix_per_tile = tile_w / fb->क्रमmat->cpp[0];
		tile = vc4_state->src_x / pix_per_tile;
		x_off = vc4_state->src_x % pix_per_tile;

		/* Adjust the base poपूर्णांकer to the first pixel to be scanned
		 * out.
		 */
		क्रम (i = 0; i < num_planes; i++) अणु
			vc4_state->offsets[i] += param * tile_w * tile;
			vc4_state->offsets[i] += src_y /
						 (i ? v_subsample : 1) *
						 tile_w;
			vc4_state->offsets[i] += x_off /
						 (i ? h_subsample : 1) *
						 fb->क्रमmat->cpp[i];
		पूर्ण

		pitch0 = VC4_SET_FIELD(param, SCALER_TILE_HEIGHT);
		अवरोध;
	पूर्ण

	शेष:
		DRM_DEBUG_KMS("Unsupported FB tiling flag 0x%16llx",
			      (दीर्घ दीर्घ)fb->modअगरier);
		वापस -EINVAL;
	पूर्ण

	/* Don't waste cycles mixing with plane alpha अगर the set alpha
	 * is opaque or there is no per-pixel alpha inक्रमmation.
	 * In any हाल we use the alpha property value as the fixed alpha.
	 */
	mix_plane_alpha = state->alpha != DRM_BLEND_ALPHA_OPAQUE &&
			  fb->क्रमmat->has_alpha;

	अगर (!vc4->hvs->hvs5) अणु
	/* Control word */
		vc4_dlist_ग_लिखो(vc4_state,
				SCALER_CTL0_VALID |
				(rotation & DRM_MODE_REFLECT_X ? SCALER_CTL0_HFLIP : 0) |
				(rotation & DRM_MODE_REFLECT_Y ? SCALER_CTL0_VFLIP : 0) |
				VC4_SET_FIELD(SCALER_CTL0_RGBA_EXPAND_ROUND, SCALER_CTL0_RGBA_EXPAND) |
				(क्रमmat->pixel_order << SCALER_CTL0_ORDER_SHIFT) |
				(hvs_क्रमmat << SCALER_CTL0_PIXEL_FORMAT_SHIFT) |
				VC4_SET_FIELD(tiling, SCALER_CTL0_TILING) |
				(vc4_state->is_unity ? SCALER_CTL0_UNITY : 0) |
				VC4_SET_FIELD(scl0, SCALER_CTL0_SCL0) |
				VC4_SET_FIELD(scl1, SCALER_CTL0_SCL1));

		/* Position Word 0: Image Positions and Alpha Value */
		vc4_state->pos0_offset = vc4_state->dlist_count;
		vc4_dlist_ग_लिखो(vc4_state,
				VC4_SET_FIELD(state->alpha >> 8, SCALER_POS0_FIXED_ALPHA) |
				VC4_SET_FIELD(vc4_state->crtc_x, SCALER_POS0_START_X) |
				VC4_SET_FIELD(vc4_state->crtc_y, SCALER_POS0_START_Y));

		/* Position Word 1: Scaled Image Dimensions. */
		अगर (!vc4_state->is_unity) अणु
			vc4_dlist_ग_लिखो(vc4_state,
					VC4_SET_FIELD(vc4_state->crtc_w,
						      SCALER_POS1_SCL_WIDTH) |
					VC4_SET_FIELD(vc4_state->crtc_h,
						      SCALER_POS1_SCL_HEIGHT));
		पूर्ण

		/* Position Word 2: Source Image Size, Alpha */
		vc4_state->pos2_offset = vc4_state->dlist_count;
		vc4_dlist_ग_लिखो(vc4_state,
				VC4_SET_FIELD(fb->क्रमmat->has_alpha ?
					      SCALER_POS2_ALPHA_MODE_PIPELINE :
					      SCALER_POS2_ALPHA_MODE_FIXED,
					      SCALER_POS2_ALPHA_MODE) |
				(mix_plane_alpha ? SCALER_POS2_ALPHA_MIX : 0) |
				(fb->क्रमmat->has_alpha ?
						SCALER_POS2_ALPHA_PREMULT : 0) |
				VC4_SET_FIELD(vc4_state->src_w[0],
					      SCALER_POS2_WIDTH) |
				VC4_SET_FIELD(vc4_state->src_h[0],
					      SCALER_POS2_HEIGHT));

		/* Position Word 3: Context.  Written by the HVS. */
		vc4_dlist_ग_लिखो(vc4_state, 0xc0c0c0c0);

	पूर्ण अन्यथा अणु
		u32 hvs_pixel_order = क्रमmat->pixel_order;

		अगर (क्रमmat->pixel_order_hvs5)
			hvs_pixel_order = क्रमmat->pixel_order_hvs5;

		/* Control word */
		vc4_dlist_ग_लिखो(vc4_state,
				SCALER_CTL0_VALID |
				(hvs_pixel_order << SCALER_CTL0_ORDER_SHIFT) |
				(hvs_क्रमmat << SCALER_CTL0_PIXEL_FORMAT_SHIFT) |
				VC4_SET_FIELD(tiling, SCALER_CTL0_TILING) |
				(vc4_state->is_unity ?
						SCALER5_CTL0_UNITY : 0) |
				VC4_SET_FIELD(scl0, SCALER_CTL0_SCL0) |
				VC4_SET_FIELD(scl1, SCALER_CTL0_SCL1) |
				SCALER5_CTL0_ALPHA_EXPAND |
				SCALER5_CTL0_RGB_EXPAND);

		/* Position Word 0: Image Positions and Alpha Value */
		vc4_state->pos0_offset = vc4_state->dlist_count;
		vc4_dlist_ग_लिखो(vc4_state,
				(rotation & DRM_MODE_REFLECT_Y ?
						SCALER5_POS0_VFLIP : 0) |
				VC4_SET_FIELD(vc4_state->crtc_x,
					      SCALER_POS0_START_X) |
				(rotation & DRM_MODE_REFLECT_X ?
					      SCALER5_POS0_HFLIP : 0) |
				VC4_SET_FIELD(vc4_state->crtc_y,
					      SCALER5_POS0_START_Y)
			       );

		/* Control Word 2 */
		vc4_dlist_ग_लिखो(vc4_state,
				VC4_SET_FIELD(state->alpha >> 4,
					      SCALER5_CTL2_ALPHA) |
				(fb->क्रमmat->has_alpha ?
					SCALER5_CTL2_ALPHA_PREMULT : 0) |
				(mix_plane_alpha ?
					SCALER5_CTL2_ALPHA_MIX : 0) |
				VC4_SET_FIELD(fb->क्रमmat->has_alpha ?
				      SCALER5_CTL2_ALPHA_MODE_PIPELINE :
				      SCALER5_CTL2_ALPHA_MODE_FIXED,
				      SCALER5_CTL2_ALPHA_MODE)
			       );

		/* Position Word 1: Scaled Image Dimensions. */
		अगर (!vc4_state->is_unity) अणु
			vc4_dlist_ग_लिखो(vc4_state,
					VC4_SET_FIELD(vc4_state->crtc_w,
						      SCALER5_POS1_SCL_WIDTH) |
					VC4_SET_FIELD(vc4_state->crtc_h,
						      SCALER5_POS1_SCL_HEIGHT));
		पूर्ण

		/* Position Word 2: Source Image Size */
		vc4_state->pos2_offset = vc4_state->dlist_count;
		vc4_dlist_ग_लिखो(vc4_state,
				VC4_SET_FIELD(vc4_state->src_w[0],
					      SCALER5_POS2_WIDTH) |
				VC4_SET_FIELD(vc4_state->src_h[0],
					      SCALER5_POS2_HEIGHT));

		/* Position Word 3: Context.  Written by the HVS. */
		vc4_dlist_ग_लिखो(vc4_state, 0xc0c0c0c0);
	पूर्ण


	/* Poपूर्णांकer Word 0/1/2: RGB / Y / Cb / Cr Poपूर्णांकers
	 *
	 * The poपूर्णांकers may be any byte address.
	 */
	vc4_state->ptr0_offset = vc4_state->dlist_count;
	क्रम (i = 0; i < num_planes; i++)
		vc4_dlist_ग_लिखो(vc4_state, vc4_state->offsets[i]);

	/* Poपूर्णांकer Context Word 0/1/2: Written by the HVS */
	क्रम (i = 0; i < num_planes; i++)
		vc4_dlist_ग_लिखो(vc4_state, 0xc0c0c0c0);

	/* Pitch word 0 */
	vc4_dlist_ग_लिखो(vc4_state, pitch0);

	/* Pitch word 1/2 */
	क्रम (i = 1; i < num_planes; i++) अणु
		अगर (hvs_क्रमmat != HVS_PIXEL_FORMAT_H264) अणु
			vc4_dlist_ग_लिखो(vc4_state,
					VC4_SET_FIELD(fb->pitches[i],
						      SCALER_SRC_PITCH));
		पूर्ण अन्यथा अणु
			vc4_dlist_ग_लिखो(vc4_state, pitch0);
		पूर्ण
	पूर्ण

	/* Colorspace conversion words */
	अगर (vc4_state->is_yuv) अणु
		vc4_dlist_ग_लिखो(vc4_state, SCALER_CSC0_ITR_R_601_5);
		vc4_dlist_ग_लिखो(vc4_state, SCALER_CSC1_ITR_R_601_5);
		vc4_dlist_ग_लिखो(vc4_state, SCALER_CSC2_ITR_R_601_5);
	पूर्ण

	vc4_state->lbm_offset = 0;

	अगर (vc4_state->x_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->x_scaling[1] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[1] != VC4_SCALING_NONE) अणु
		/* Reserve a slot क्रम the LBM Base Address. The real value will
		 * be set when calling vc4_plane_allocate_lbm().
		 */
		अगर (vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
		    vc4_state->y_scaling[1] != VC4_SCALING_NONE) अणु
			vc4_state->lbm_offset = vc4_state->dlist_count;
			vc4_dlist_counter_increment(vc4_state);
		पूर्ण

		अगर (num_planes > 1) अणु
			/* Emit Cb/Cr as channel 0 and Y as channel
			 * 1. This matches how we set up scl0/scl1
			 * above.
			 */
			vc4_ग_लिखो_scaling_parameters(state, 1);
		पूर्ण
		vc4_ग_लिखो_scaling_parameters(state, 0);

		/* If any PPF setup was करोne, then all the kernel
		 * poपूर्णांकers get uploaded.
		 */
		अगर (vc4_state->x_scaling[0] == VC4_SCALING_PPF ||
		    vc4_state->y_scaling[0] == VC4_SCALING_PPF ||
		    vc4_state->x_scaling[1] == VC4_SCALING_PPF ||
		    vc4_state->y_scaling[1] == VC4_SCALING_PPF) अणु
			u32 kernel = VC4_SET_FIELD(vc4->hvs->mitchell_netravali_filter.start,
						   SCALER_PPF_KERNEL_OFFSET);

			/* HPPF plane 0 */
			vc4_dlist_ग_लिखो(vc4_state, kernel);
			/* VPPF plane 0 */
			vc4_dlist_ग_लिखो(vc4_state, kernel);
			/* HPPF plane 1 */
			vc4_dlist_ग_लिखो(vc4_state, kernel);
			/* VPPF plane 1 */
			vc4_dlist_ग_लिखो(vc4_state, kernel);
		पूर्ण
	पूर्ण

	vc4_state->dlist[ctl0_offset] |=
		VC4_SET_FIELD(vc4_state->dlist_count, SCALER_CTL0_SIZE);

	/* crtc_* are alपढ़ोy clipped coordinates. */
	covers_screen = vc4_state->crtc_x == 0 && vc4_state->crtc_y == 0 &&
			vc4_state->crtc_w == state->crtc->mode.hdisplay &&
			vc4_state->crtc_h == state->crtc->mode.vdisplay;
	/* Background fill might be necessary when the plane has per-pixel
	 * alpha content or a non-opaque plane alpha and could blend from the
	 * background or करोes not cover the entire screen.
	 */
	vc4_state->needs_bg_fill = fb->क्रमmat->has_alpha || !covers_screen ||
				   state->alpha != DRM_BLEND_ALPHA_OPAQUE;

	/* Flag the dlist as initialized to aव्योम checking it twice in हाल
	 * the async update check alपढ़ोy called vc4_plane_mode_set() and
	 * decided to fallback to sync update because async update was not
	 * possible.
	 */
	vc4_state->dlist_initialized = 1;

	vc4_plane_calc_load(state);

	वापस 0;
पूर्ण

/* If a modeset involves changing the setup of a plane, the atomic
 * infraकाष्ठाure will call this to validate a proposed plane setup.
 * However, अगर a plane isn't getting updated, this (and the
 * corresponding vc4_plane_atomic_update) won't get called.  Thus, we
 * compute the dlist here and have all active plane dlists get updated
 * in the CRTC's flush.
 */
अटल पूर्णांक vc4_plane_atomic_check(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(new_plane_state);
	पूर्णांक ret;

	vc4_state->dlist_count = 0;

	अगर (!plane_enabled(new_plane_state))
		वापस 0;

	ret = vc4_plane_mode_set(plane, new_plane_state);
	अगर (ret)
		वापस ret;

	वापस vc4_plane_allocate_lbm(new_plane_state);
पूर्ण

अटल व्योम vc4_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	/* No contents here.  Since we करोn't know where in the CRTC's
	 * dlist we should be stored, our dlist is uploaded to the
	 * hardware with vc4_plane_ग_लिखो_dlist() at CRTC atomic_flush
	 * समय.
	 */
पूर्ण

u32 vc4_plane_ग_लिखो_dlist(काष्ठा drm_plane *plane, u32 __iomem *dlist)
अणु
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(plane->state);
	पूर्णांक i;

	vc4_state->hw_dlist = dlist;

	/* Can't स_नकल_toio() because it needs to be 32-bit ग_लिखोs. */
	क्रम (i = 0; i < vc4_state->dlist_count; i++)
		ग_लिखोl(vc4_state->dlist[i], &dlist[i]);

	वापस vc4_state->dlist_count;
पूर्ण

u32 vc4_plane_dlist_size(स्थिर काष्ठा drm_plane_state *state)
अणु
	स्थिर काष्ठा vc4_plane_state *vc4_state =
		container_of(state, typeof(*vc4_state), base);

	वापस vc4_state->dlist_count;
पूर्ण

/* Updates the plane to immediately (well, once the FIFO needs
 * refilling) scan out from at a new framebuffer.
 */
व्योम vc4_plane_async_set_fb(काष्ठा drm_plane *plane, काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा vc4_plane_state *vc4_state = to_vc4_plane_state(plane->state);
	काष्ठा drm_gem_cma_object *bo = drm_fb_cma_get_gem_obj(fb, 0);
	uपूर्णांक32_t addr;

	/* We're skipping the address adjusपंचांगent क्रम negative origin,
	 * because this is only called on the primary plane.
	 */
	WARN_ON_ONCE(plane->state->crtc_x < 0 || plane->state->crtc_y < 0);
	addr = bo->paddr + fb->offsets[0];

	/* Write the new address पूर्णांकo the hardware immediately.  The
	 * scanout will start from this address as soon as the FIFO
	 * needs to refill with pixels.
	 */
	ग_लिखोl(addr, &vc4_state->hw_dlist[vc4_state->ptr0_offset]);

	/* Also update the CPU-side dlist copy, so that any later
	 * atomic updates that करोn't करो a new modeset on our plane
	 * also use our updated address.
	 */
	vc4_state->dlist[vc4_state->ptr0_offset] = addr;
पूर्ण

अटल व्योम vc4_plane_atomic_async_update(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा vc4_plane_state *vc4_state, *new_vc4_state;

	swap(plane->state->fb, new_plane_state->fb);
	plane->state->crtc_x = new_plane_state->crtc_x;
	plane->state->crtc_y = new_plane_state->crtc_y;
	plane->state->crtc_w = new_plane_state->crtc_w;
	plane->state->crtc_h = new_plane_state->crtc_h;
	plane->state->src_x = new_plane_state->src_x;
	plane->state->src_y = new_plane_state->src_y;
	plane->state->src_w = new_plane_state->src_w;
	plane->state->src_h = new_plane_state->src_h;
	plane->state->alpha = new_plane_state->alpha;
	plane->state->pixel_blend_mode = new_plane_state->pixel_blend_mode;
	plane->state->rotation = new_plane_state->rotation;
	plane->state->zpos = new_plane_state->zpos;
	plane->state->normalized_zpos = new_plane_state->normalized_zpos;
	plane->state->color_encoding = new_plane_state->color_encoding;
	plane->state->color_range = new_plane_state->color_range;
	plane->state->src = new_plane_state->src;
	plane->state->dst = new_plane_state->dst;
	plane->state->visible = new_plane_state->visible;

	new_vc4_state = to_vc4_plane_state(new_plane_state);
	vc4_state = to_vc4_plane_state(plane->state);

	vc4_state->crtc_x = new_vc4_state->crtc_x;
	vc4_state->crtc_y = new_vc4_state->crtc_y;
	vc4_state->crtc_h = new_vc4_state->crtc_h;
	vc4_state->crtc_w = new_vc4_state->crtc_w;
	vc4_state->src_x = new_vc4_state->src_x;
	vc4_state->src_y = new_vc4_state->src_y;
	स_नकल(vc4_state->src_w, new_vc4_state->src_w,
	       माप(vc4_state->src_w));
	स_नकल(vc4_state->src_h, new_vc4_state->src_h,
	       माप(vc4_state->src_h));
	स_नकल(vc4_state->x_scaling, new_vc4_state->x_scaling,
	       माप(vc4_state->x_scaling));
	स_नकल(vc4_state->y_scaling, new_vc4_state->y_scaling,
	       माप(vc4_state->y_scaling));
	vc4_state->is_unity = new_vc4_state->is_unity;
	vc4_state->is_yuv = new_vc4_state->is_yuv;
	स_नकल(vc4_state->offsets, new_vc4_state->offsets,
	       माप(vc4_state->offsets));
	vc4_state->needs_bg_fill = new_vc4_state->needs_bg_fill;

	/* Update the current vc4_state pos0, pos2 and ptr0 dlist entries. */
	vc4_state->dlist[vc4_state->pos0_offset] =
		new_vc4_state->dlist[vc4_state->pos0_offset];
	vc4_state->dlist[vc4_state->pos2_offset] =
		new_vc4_state->dlist[vc4_state->pos2_offset];
	vc4_state->dlist[vc4_state->ptr0_offset] =
		new_vc4_state->dlist[vc4_state->ptr0_offset];

	/* Note that we can't just call vc4_plane_ग_लिखो_dlist()
	 * because that would smash the context data that the HVS is
	 * currently using.
	 */
	ग_लिखोl(vc4_state->dlist[vc4_state->pos0_offset],
	       &vc4_state->hw_dlist[vc4_state->pos0_offset]);
	ग_लिखोl(vc4_state->dlist[vc4_state->pos2_offset],
	       &vc4_state->hw_dlist[vc4_state->pos2_offset]);
	ग_लिखोl(vc4_state->dlist[vc4_state->ptr0_offset],
	       &vc4_state->hw_dlist[vc4_state->ptr0_offset]);
पूर्ण

अटल पूर्णांक vc4_plane_atomic_async_check(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा vc4_plane_state *old_vc4_state, *new_vc4_state;
	पूर्णांक ret;
	u32 i;

	ret = vc4_plane_mode_set(plane, new_plane_state);
	अगर (ret)
		वापस ret;

	old_vc4_state = to_vc4_plane_state(plane->state);
	new_vc4_state = to_vc4_plane_state(new_plane_state);
	अगर (old_vc4_state->dlist_count != new_vc4_state->dlist_count ||
	    old_vc4_state->pos0_offset != new_vc4_state->pos0_offset ||
	    old_vc4_state->pos2_offset != new_vc4_state->pos2_offset ||
	    old_vc4_state->ptr0_offset != new_vc4_state->ptr0_offset ||
	    vc4_lbm_size(plane->state) != vc4_lbm_size(new_plane_state))
		वापस -EINVAL;

	/* Only pos0, pos2 and ptr0 DWORDS can be updated in an async update
	 * अगर anything अन्यथा has changed, fallback to a sync update.
	 */
	क्रम (i = 0; i < new_vc4_state->dlist_count; i++) अणु
		अगर (i == new_vc4_state->pos0_offset ||
		    i == new_vc4_state->pos2_offset ||
		    i == new_vc4_state->ptr0_offset ||
		    (new_vc4_state->lbm_offset &&
		     i == new_vc4_state->lbm_offset))
			जारी;

		अगर (new_vc4_state->dlist[i] != old_vc4_state->dlist[i])
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_prepare_fb(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_bo *bo;
	पूर्णांक ret;

	अगर (!state->fb)
		वापस 0;

	bo = to_vc4_bo(&drm_fb_cma_get_gem_obj(state->fb, 0)->base);

	drm_gem_plane_helper_prepare_fb(plane, state);

	अगर (plane->state->fb == state->fb)
		वापस 0;

	ret = vc4_bo_inc_usecnt(bo);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम vc4_cleanup_fb(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *state)
अणु
	काष्ठा vc4_bo *bo;

	अगर (plane->state->fb == state->fb || !state->fb)
		वापस;

	bo = to_vc4_bo(&drm_fb_cma_get_gem_obj(state->fb, 0)->base);
	vc4_bo_dec_usecnt(bo);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs vc4_plane_helper_funcs = अणु
	.atomic_check = vc4_plane_atomic_check,
	.atomic_update = vc4_plane_atomic_update,
	.prepare_fb = vc4_prepare_fb,
	.cleanup_fb = vc4_cleanup_fb,
	.atomic_async_check = vc4_plane_atomic_async_check,
	.atomic_async_update = vc4_plane_atomic_async_update,
पूर्ण;

अटल bool vc4_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
				     uपूर्णांक32_t क्रमmat,
				     uपूर्णांक64_t modअगरier)
अणु
	/* Support T_TILING क्रम RGB क्रमmats only. */
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_BGR565:
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
		चयन (fourcc_mod_broadcom_mod(modअगरier)) अणु
		हाल DRM_FORMAT_MOD_LINEAR:
		हाल DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV21:
		चयन (fourcc_mod_broadcom_mod(modअगरier)) अणु
		हाल DRM_FORMAT_MOD_LINEAR:
		हाल DRM_FORMAT_MOD_BROADCOM_SAND64:
		हाल DRM_FORMAT_MOD_BROADCOM_SAND128:
		हाल DRM_FORMAT_MOD_BROADCOM_SAND256:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	हाल DRM_FORMAT_RGBX1010102:
	हाल DRM_FORMAT_BGRX1010102:
	हाल DRM_FORMAT_RGBA1010102:
	हाल DRM_FORMAT_BGRA1010102:
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV61:
	शेष:
		वापस (modअगरier == DRM_FORMAT_MOD_LINEAR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs vc4_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.set_property = शून्य,
	.reset = vc4_plane_reset,
	.atomic_duplicate_state = vc4_plane_duplicate_state,
	.atomic_destroy_state = vc4_plane_destroy_state,
	.क्रमmat_mod_supported = vc4_क्रमmat_mod_supported,
पूर्ण;

काष्ठा drm_plane *vc4_plane_init(काष्ठा drm_device *dev,
				 क्रमागत drm_plane_type type)
अणु
	काष्ठा drm_plane *plane = शून्य;
	काष्ठा vc4_plane *vc4_plane;
	u32 क्रमmats[ARRAY_SIZE(hvs_क्रमmats)];
	पूर्णांक ret = 0;
	अचिन्हित i;
	अटल स्थिर uपूर्णांक64_t modअगरiers[] = अणु
		DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED,
		DRM_FORMAT_MOD_BROADCOM_SAND128,
		DRM_FORMAT_MOD_BROADCOM_SAND64,
		DRM_FORMAT_MOD_BROADCOM_SAND256,
		DRM_FORMAT_MOD_LINEAR,
		DRM_FORMAT_MOD_INVALID
	पूर्ण;

	vc4_plane = devm_kzalloc(dev->dev, माप(*vc4_plane),
				 GFP_KERNEL);
	अगर (!vc4_plane)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < ARRAY_SIZE(hvs_क्रमmats); i++)
		क्रमmats[i] = hvs_क्रमmats[i].drm;

	plane = &vc4_plane->base;
	ret = drm_universal_plane_init(dev, plane, 0,
				       &vc4_plane_funcs,
				       क्रमmats, ARRAY_SIZE(क्रमmats),
				       modअगरiers, type, शून्य);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_plane_helper_add(plane, &vc4_plane_helper_funcs);

	drm_plane_create_alpha_property(plane);
	drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
					   DRM_MODE_ROTATE_0 |
					   DRM_MODE_ROTATE_180 |
					   DRM_MODE_REFLECT_X |
					   DRM_MODE_REFLECT_Y);

	वापस plane;
पूर्ण

पूर्णांक vc4_plane_create_additional_planes(काष्ठा drm_device *drm)
अणु
	काष्ठा drm_plane *cursor_plane;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i;

	/* Set up some arbitrary number of planes.  We're not limited
	 * by a set number of physical रेजिस्टरs, just the space in
	 * the HVS (16k) and how small an plane can be (28 bytes).
	 * However, each plane we set up takes up some memory, and
	 * increases the cost of looping over planes, which atomic
	 * modesetting करोes quite a bit.  As a result, we pick a
	 * modest number of planes to expose, that should hopefully
	 * still cover any sane useहाल.
	 */
	क्रम (i = 0; i < 16; i++) अणु
		काष्ठा drm_plane *plane =
			vc4_plane_init(drm, DRM_PLANE_TYPE_OVERLAY);

		अगर (IS_ERR(plane))
			जारी;

		plane->possible_crtcs =
			GENMASK(drm->mode_config.num_crtc - 1, 0);
	पूर्ण

	drm_क्रम_each_crtc(crtc, drm) अणु
		/* Set up the legacy cursor after overlay initialization,
		 * since we overlay planes on the CRTC in the order they were
		 * initialized.
		 */
		cursor_plane = vc4_plane_init(drm, DRM_PLANE_TYPE_CURSOR);
		अगर (!IS_ERR(cursor_plane)) अणु
			cursor_plane->possible_crtcs = drm_crtc_mask(crtc);
			crtc->cursor = cursor_plane;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
