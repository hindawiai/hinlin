<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 *  Rewritten from the करोvefb driver, and Armada510 manuals.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"
#समावेश "armada_fb.h"
#समावेश "armada_gem.h"
#समावेश "armada_hw.h"
#समावेश "armada_plane.h"
#समावेश "armada_trace.h"

अटल स्थिर uपूर्णांक32_t armada_primary_क्रमmats[] = अणु
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_BGR565,
पूर्ण;

व्योम armada_drm_plane_calc(काष्ठा drm_plane_state *state, u32 addrs[2][3],
	u16 pitches[3], bool पूर्णांकerlaced)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	अचिन्हित पूर्णांक num_planes = क्रमmat->num_planes;
	अचिन्हित पूर्णांक x = state->src.x1 >> 16;
	अचिन्हित पूर्णांक y = state->src.y1 >> 16;
	u32 addr = drm_fb_obj(fb)->dev_addr;
	पूर्णांक i;

	DRM_DEBUG_KMS("pitch %u x %d y %d bpp %d\n",
		      fb->pitches[0], x, y, क्रमmat->cpp[0] * 8);

	अगर (num_planes > 3)
		num_planes = 3;

	addrs[0][0] = addr + fb->offsets[0] + y * fb->pitches[0] +
		      x * क्रमmat->cpp[0];
	pitches[0] = fb->pitches[0];

	y /= क्रमmat->vsub;
	x /= क्रमmat->hsub;

	क्रम (i = 1; i < num_planes; i++) अणु
		addrs[0][i] = addr + fb->offsets[i] + y * fb->pitches[i] +
			      x * क्रमmat->cpp[i];
		pitches[i] = fb->pitches[i];
	पूर्ण
	क्रम (; i < 3; i++) अणु
		addrs[0][i] = 0;
		pitches[i] = 0;
	पूर्ण
	अगर (पूर्णांकerlaced) अणु
		क्रम (i = 0; i < 3; i++) अणु
			addrs[1][i] = addrs[0][i] + pitches[i];
			pitches[i] *= 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 3; i++)
			addrs[1][i] = addrs[0][i];
	पूर्ण
पूर्ण

पूर्णांक armada_drm_plane_prepare_fb(काष्ठा drm_plane *plane,
	काष्ठा drm_plane_state *state)
अणु
	DRM_DEBUG_KMS("[PLANE:%d:%s] [FB:%d]\n",
		plane->base.id, plane->name,
		state->fb ? state->fb->base.id : 0);

	/*
	 * Take a reference on the new framebuffer - we want to
	 * hold on to it जबतक the hardware is displaying it.
	 */
	अगर (state->fb)
		drm_framebuffer_get(state->fb);
	वापस 0;
पूर्ण

व्योम armada_drm_plane_cleanup_fb(काष्ठा drm_plane *plane,
	काष्ठा drm_plane_state *old_state)
अणु
	DRM_DEBUG_KMS("[PLANE:%d:%s] [FB:%d]\n",
		plane->base.id, plane->name,
		old_state->fb ? old_state->fb->base.id : 0);

	अगर (old_state->fb)
		drm_framebuffer_put(old_state->fb);
पूर्ण

पूर्णांक armada_drm_plane_atomic_check(काष्ठा drm_plane *plane,
	काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा armada_plane_state *st = to_armada_plane_state(new_plane_state);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;
	bool पूर्णांकerlace;
	पूर्णांक ret;

	अगर (!new_plane_state->fb || WARN_ON(!new_plane_state->crtc)) अणु
		new_plane_state->visible = false;
		वापस 0;
	पूर्ण

	अगर (state)
		crtc_state = drm_atomic_get_existing_crtc_state(state,
								crtc);
	अन्यथा
		crtc_state = crtc->state;

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  0,
						  पूर्णांक_उच्च, true, false);
	अगर (ret)
		वापस ret;

	पूर्णांकerlace = crtc_state->adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE;
	अगर (पूर्णांकerlace) अणु
		अगर ((new_plane_state->dst.y1 | new_plane_state->dst.y2) & 1)
			वापस -EINVAL;
		st->src_hw = drm_rect_height(&new_plane_state->src) >> 17;
		st->dst_yx = new_plane_state->dst.y1 >> 1;
		st->dst_hw = drm_rect_height(&new_plane_state->dst) >> 1;
	पूर्ण अन्यथा अणु
		st->src_hw = drm_rect_height(&new_plane_state->src) >> 16;
		st->dst_yx = new_plane_state->dst.y1;
		st->dst_hw = drm_rect_height(&new_plane_state->dst);
	पूर्ण

	st->src_hw <<= 16;
	st->src_hw |= drm_rect_width(&new_plane_state->src) >> 16;
	st->dst_yx <<= 16;
	st->dst_yx |= new_plane_state->dst.x1 & 0x0000ffff;
	st->dst_hw <<= 16;
	st->dst_hw |= drm_rect_width(&new_plane_state->dst) & 0x0000ffff;

	armada_drm_plane_calc(new_plane_state, st->addrs, st->pitches,
			      पूर्णांकerlace);
	st->पूर्णांकerlace = पूर्णांकerlace;

	वापस 0;
पूर्ण

अटल व्योम armada_drm_primary_plane_atomic_update(काष्ठा drm_plane *plane,
	काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा armada_crtc *dcrtc;
	काष्ठा armada_regs *regs;
	u32 cfg, cfg_mask, val;
	अचिन्हित पूर्णांक idx;

	DRM_DEBUG_KMS("[PLANE:%d:%s]\n", plane->base.id, plane->name);

	अगर (!new_state->fb || WARN_ON(!new_state->crtc))
		वापस;

	DRM_DEBUG_KMS("[PLANE:%d:%s] is on [CRTC:%d:%s] with [FB:%d] visible %u->%u\n",
		plane->base.id, plane->name,
		new_state->crtc->base.id, new_state->crtc->name,
		new_state->fb->base.id,
		old_state->visible, new_state->visible);

	dcrtc = drm_to_armada_crtc(new_state->crtc);
	regs = dcrtc->regs + dcrtc->regs_idx;

	idx = 0;
	अगर (!old_state->visible && new_state->visible) अणु
		val = CFG_PDWN64x66;
		अगर (drm_fb_to_armada_fb(new_state->fb)->fmt > CFG_420)
			val |= CFG_PDWN256x24;
		armada_reg_queue_mod(regs, idx, 0, val, LCD_SPU_SRAM_PARA1);
	पूर्ण
	val = armada_src_hw(new_state);
	अगर (armada_src_hw(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_GRA_HPXL_VLN);
	val = armada_dst_yx(new_state);
	अगर (armada_dst_yx(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_GRA_OVSA_HPXL_VLN);
	val = armada_dst_hw(new_state);
	अगर (armada_dst_hw(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_GZM_HPXL_VLN);
	अगर (old_state->src.x1 != new_state->src.x1 ||
	    old_state->src.y1 != new_state->src.y1 ||
	    old_state->fb != new_state->fb ||
	    new_state->crtc->state->mode_changed) अणु
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 0, 0),
				     LCD_CFG_GRA_START_ADDR0);
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 1, 0),
				     LCD_CFG_GRA_START_ADDR1);
		armada_reg_queue_mod(regs, idx, armada_pitch(new_state, 0),
				     0xffff,
				     LCD_CFG_GRA_PITCH);
	पूर्ण
	अगर (old_state->fb != new_state->fb ||
	    new_state->crtc->state->mode_changed) अणु
		cfg = CFG_GRA_FMT(drm_fb_to_armada_fb(new_state->fb)->fmt) |
		      CFG_GRA_MOD(drm_fb_to_armada_fb(new_state->fb)->mod);
		अगर (drm_fb_to_armada_fb(new_state->fb)->fmt > CFG_420)
			cfg |= CFG_PALETTE_ENA;
		अगर (new_state->visible)
			cfg |= CFG_GRA_ENA;
		अगर (to_armada_plane_state(new_state)->पूर्णांकerlace)
			cfg |= CFG_GRA_FTOGGLE;
		cfg_mask = CFG_GRAFORMAT |
			   CFG_GRA_MOD(CFG_SWAPRB | CFG_SWAPUV |
				       CFG_SWAPYU | CFG_YUV2RGB) |
			   CFG_PALETTE_ENA | CFG_GRA_FTOGGLE |
			   CFG_GRA_ENA;
	पूर्ण अन्यथा अगर (old_state->visible != new_state->visible) अणु
		cfg = new_state->visible ? CFG_GRA_ENA : 0;
		cfg_mask = CFG_GRA_ENA;
	पूर्ण अन्यथा अणु
		cfg = cfg_mask = 0;
	पूर्ण
	अगर (drm_rect_width(&old_state->src) != drm_rect_width(&new_state->src) ||
	    drm_rect_width(&old_state->dst) != drm_rect_width(&new_state->dst)) अणु
		cfg_mask |= CFG_GRA_HSMOOTH;
		अगर (drm_rect_width(&new_state->src) >> 16 !=
		    drm_rect_width(&new_state->dst))
			cfg |= CFG_GRA_HSMOOTH;
	पूर्ण

	अगर (cfg_mask)
		armada_reg_queue_mod(regs, idx, cfg, cfg_mask,
				     LCD_SPU_DMA_CTRL0);

	dcrtc->regs_idx += idx;
पूर्ण

अटल व्योम armada_drm_primary_plane_atomic_disable(काष्ठा drm_plane *plane,
	काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा armada_crtc *dcrtc;
	काष्ठा armada_regs *regs;
	अचिन्हित पूर्णांक idx = 0;

	DRM_DEBUG_KMS("[PLANE:%d:%s]\n", plane->base.id, plane->name);

	अगर (!old_state->crtc)
		वापस;

	DRM_DEBUG_KMS("[PLANE:%d:%s] was on [CRTC:%d:%s] with [FB:%d]\n",
		plane->base.id, plane->name,
		old_state->crtc->base.id, old_state->crtc->name,
		old_state->fb->base.id);

	dcrtc = drm_to_armada_crtc(old_state->crtc);
	regs = dcrtc->regs + dcrtc->regs_idx;

	/* Disable plane and घातer करोwn most RAMs and FIFOs */
	armada_reg_queue_mod(regs, idx, 0, CFG_GRA_ENA, LCD_SPU_DMA_CTRL0);
	armada_reg_queue_mod(regs, idx, CFG_PDWN256x32 | CFG_PDWN256x24 |
			     CFG_PDWN32x32 | CFG_PDWN64x66,
			     0, LCD_SPU_SRAM_PARA1);

	dcrtc->regs_idx += idx;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs armada_primary_plane_helper_funcs = अणु
	.prepare_fb	= armada_drm_plane_prepare_fb,
	.cleanup_fb	= armada_drm_plane_cleanup_fb,
	.atomic_check	= armada_drm_plane_atomic_check,
	.atomic_update	= armada_drm_primary_plane_atomic_update,
	.atomic_disable	= armada_drm_primary_plane_atomic_disable,
पूर्ण;

व्योम armada_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा armada_plane_state *st;
	अगर (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);
	kमुक्त(plane->state);
	st = kzalloc(माप(*st), GFP_KERNEL);
	अगर (st)
		__drm_atomic_helper_plane_reset(plane, &st->base);
पूर्ण

काष्ठा drm_plane_state *armada_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा armada_plane_state *st;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	st = kmemdup(plane->state, माप(*st), GFP_KERNEL);
	अगर (st)
		__drm_atomic_helper_plane_duplicate_state(plane, &st->base);

	वापस &st->base;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs armada_primary_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_primary_helper_destroy,
	.reset		= armada_plane_reset,
	.atomic_duplicate_state = armada_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

पूर्णांक armada_drm_primary_plane_init(काष्ठा drm_device *drm,
	काष्ठा drm_plane *primary)
अणु
	पूर्णांक ret;

	drm_plane_helper_add(primary, &armada_primary_plane_helper_funcs);

	ret = drm_universal_plane_init(drm, primary, 0,
				       &armada_primary_plane_funcs,
				       armada_primary_क्रमmats,
				       ARRAY_SIZE(armada_primary_क्रमmats),
				       शून्य,
				       DRM_PLANE_TYPE_PRIMARY, शून्य);

	वापस ret;
पूर्ण
