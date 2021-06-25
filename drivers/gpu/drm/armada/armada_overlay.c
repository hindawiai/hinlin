<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 *  Rewritten from the करोvefb driver, and Armada510 manuals.
 */

#समावेश <drm/armada_drm.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"
#समावेश "armada_fb.h"
#समावेश "armada_gem.h"
#समावेश "armada_hw.h"
#समावेश "armada_ioctlP.h"
#समावेश "armada_plane.h"
#समावेश "armada_trace.h"

#घोषणा DEFAULT_BRIGHTNESS	0
#घोषणा DEFAULT_CONTRAST	0x4000
#घोषणा DEFAULT_SATURATION	0x4000
#घोषणा DEFAULT_ENCODING	DRM_COLOR_YCBCR_BT601

काष्ठा armada_overlay_state अणु
	काष्ठा armada_plane_state base;
	u32 colorkey_yr;
	u32 colorkey_ug;
	u32 colorkey_vb;
	u32 colorkey_mode;
	u32 colorkey_enable;
	s16 brightness;
	u16 contrast;
	u16 saturation;
पूर्ण;
#घोषणा drm_to_overlay_state(s) \
	container_of(s, काष्ठा armada_overlay_state, base.base)

अटल अंतरभूत u32 armada_spu_contrast(काष्ठा drm_plane_state *state)
अणु
	वापस drm_to_overlay_state(state)->brightness << 16 |
	       drm_to_overlay_state(state)->contrast;
पूर्ण

अटल अंतरभूत u32 armada_spu_saturation(काष्ठा drm_plane_state *state)
अणु
	/* Docs say 15:0, but it seems to actually be 31:16 on Armada 510 */
	वापस drm_to_overlay_state(state)->saturation << 16;
पूर्ण

अटल अंतरभूत u32 armada_csc(काष्ठा drm_plane_state *state)
अणु
	/*
	 * The CFG_CSC_RGB_* settings control the output of the colour space
	 * converter, setting the range of output values it produces.  Since
	 * we will be blending with the full-range graphics, we need to
	 * produce full-range RGB output from the conversion.
	 */
	वापस CFG_CSC_RGB_COMPUTER |
	       (state->color_encoding == DRM_COLOR_YCBCR_BT709 ?
			CFG_CSC_YUV_CCIR709 : CFG_CSC_YUV_CCIR601);
पूर्ण

/* === Plane support === */
अटल व्योम armada_drm_overlay_plane_atomic_update(काष्ठा drm_plane *plane,
	काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा armada_crtc *dcrtc;
	काष्ठा armada_regs *regs;
	अचिन्हित पूर्णांक idx;
	u32 cfg, cfg_mask, val;

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
	अगर (!old_state->visible && new_state->visible)
		armada_reg_queue_mod(regs, idx,
				     0, CFG_PDWN16x66 | CFG_PDWN32x66,
				     LCD_SPU_SRAM_PARA1);
	val = armada_src_hw(new_state);
	अगर (armada_src_hw(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_DMA_HPXL_VLN);
	val = armada_dst_yx(new_state);
	अगर (armada_dst_yx(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_DMA_OVSA_HPXL_VLN);
	val = armada_dst_hw(new_state);
	अगर (armada_dst_hw(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_DZM_HPXL_VLN);
	/* FIXME: overlay on an पूर्णांकerlaced display */
	अगर (old_state->src.x1 != new_state->src.x1 ||
	    old_state->src.y1 != new_state->src.y1 ||
	    old_state->fb != new_state->fb ||
	    new_state->crtc->state->mode_changed) अणु
		स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
		u16 src_x;

		armada_reg_queue_set(regs, idx, armada_addr(new_state, 0, 0),
				     LCD_SPU_DMA_START_ADDR_Y0);
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 0, 1),
				     LCD_SPU_DMA_START_ADDR_U0);
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 0, 2),
				     LCD_SPU_DMA_START_ADDR_V0);
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 1, 0),
				     LCD_SPU_DMA_START_ADDR_Y1);
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 1, 1),
				     LCD_SPU_DMA_START_ADDR_U1);
		armada_reg_queue_set(regs, idx, armada_addr(new_state, 1, 2),
				     LCD_SPU_DMA_START_ADDR_V1);

		val = armada_pitch(new_state, 0) << 16 | armada_pitch(new_state,
								      0);
		armada_reg_queue_set(regs, idx, val, LCD_SPU_DMA_PITCH_YC);
		val = armada_pitch(new_state, 1) << 16 | armada_pitch(new_state,
								      2);
		armada_reg_queue_set(regs, idx, val, LCD_SPU_DMA_PITCH_UV);

		cfg = CFG_DMA_FMT(drm_fb_to_armada_fb(new_state->fb)->fmt) |
		      CFG_DMA_MOD(drm_fb_to_armada_fb(new_state->fb)->mod) |
		      CFG_CBSH_ENA;
		अगर (new_state->visible)
			cfg |= CFG_DMA_ENA;

		/*
		 * Shअगरting a YUV packed क्रमmat image by one pixel causes the
		 * U/V planes to swap.  Compensate क्रम it by also toggling
		 * the UV swap.
		 */
		क्रमmat = new_state->fb->क्रमmat;
		src_x = new_state->src.x1 >> 16;
		अगर (क्रमmat->num_planes == 1 && src_x & (क्रमmat->hsub - 1))
			cfg ^= CFG_DMA_MOD(CFG_SWAPUV);
		अगर (to_armada_plane_state(new_state)->पूर्णांकerlace)
			cfg |= CFG_DMA_FTOGGLE;
		cfg_mask = CFG_CBSH_ENA | CFG_DMAFORMAT |
			   CFG_DMA_MOD(CFG_SWAPRB | CFG_SWAPUV |
				       CFG_SWAPYU | CFG_YUV2RGB) |
			   CFG_DMA_FTOGGLE | CFG_DMA_TSTMODE |
			   CFG_DMA_ENA;
	पूर्ण अन्यथा अगर (old_state->visible != new_state->visible) अणु
		cfg = new_state->visible ? CFG_DMA_ENA : 0;
		cfg_mask = CFG_DMA_ENA;
	पूर्ण अन्यथा अणु
		cfg = cfg_mask = 0;
	पूर्ण
	अगर (drm_rect_width(&old_state->src) != drm_rect_width(&new_state->src) ||
	    drm_rect_width(&old_state->dst) != drm_rect_width(&new_state->dst)) अणु
		cfg_mask |= CFG_DMA_HSMOOTH;
		अगर (drm_rect_width(&new_state->src) >> 16 !=
		    drm_rect_width(&new_state->dst))
			cfg |= CFG_DMA_HSMOOTH;
	पूर्ण

	अगर (cfg_mask)
		armada_reg_queue_mod(regs, idx, cfg, cfg_mask,
				     LCD_SPU_DMA_CTRL0);

	val = armada_spu_contrast(new_state);
	अगर ((!old_state->visible && new_state->visible) ||
	    armada_spu_contrast(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_CONTRAST);
	val = armada_spu_saturation(new_state);
	अगर ((!old_state->visible && new_state->visible) ||
	    armada_spu_saturation(old_state) != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_SATURATION);
	अगर (!old_state->visible && new_state->visible)
		armada_reg_queue_set(regs, idx, 0x00002000, LCD_SPU_CBSH_HUE);
	val = armada_csc(new_state);
	अगर ((!old_state->visible && new_state->visible) ||
	    armada_csc(old_state) != val)
		armada_reg_queue_mod(regs, idx, val, CFG_CSC_MASK,
				     LCD_SPU_IOPAD_CONTROL);
	val = drm_to_overlay_state(new_state)->colorkey_yr;
	अगर ((!old_state->visible && new_state->visible) ||
	    drm_to_overlay_state(old_state)->colorkey_yr != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_COLORKEY_Y);
	val = drm_to_overlay_state(new_state)->colorkey_ug;
	अगर ((!old_state->visible && new_state->visible) ||
	    drm_to_overlay_state(old_state)->colorkey_ug != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_COLORKEY_U);
	val = drm_to_overlay_state(new_state)->colorkey_vb;
	अगर ((!old_state->visible && new_state->visible) ||
	    drm_to_overlay_state(old_state)->colorkey_vb != val)
		armada_reg_queue_set(regs, idx, val, LCD_SPU_COLORKEY_V);
	val = drm_to_overlay_state(new_state)->colorkey_mode;
	अगर ((!old_state->visible && new_state->visible) ||
	    drm_to_overlay_state(old_state)->colorkey_mode != val)
		armada_reg_queue_mod(regs, idx, val, CFG_CKMODE_MASK |
				     CFG_ALPHAM_MASK | CFG_ALPHA_MASK,
				     LCD_SPU_DMA_CTRL1);
	val = drm_to_overlay_state(new_state)->colorkey_enable;
	अगर (((!old_state->visible && new_state->visible) ||
	     drm_to_overlay_state(old_state)->colorkey_enable != val) &&
	    dcrtc->variant->has_spu_adv_reg)
		armada_reg_queue_mod(regs, idx, val, ADV_GRACOLORKEY |
				     ADV_VIDCOLORKEY, LCD_SPU_ADV_REG);

	dcrtc->regs_idx += idx;
पूर्ण

अटल व्योम armada_drm_overlay_plane_atomic_disable(काष्ठा drm_plane *plane,
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

	/* Disable plane and घातer करोwn the YUV FIFOs */
	armada_reg_queue_mod(regs, idx, 0, CFG_DMA_ENA, LCD_SPU_DMA_CTRL0);
	armada_reg_queue_mod(regs, idx, CFG_PDWN16x66 | CFG_PDWN32x66, 0,
			     LCD_SPU_SRAM_PARA1);

	dcrtc->regs_idx += idx;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs armada_overlay_plane_helper_funcs = अणु
	.prepare_fb	= armada_drm_plane_prepare_fb,
	.cleanup_fb	= armada_drm_plane_cleanup_fb,
	.atomic_check	= armada_drm_plane_atomic_check,
	.atomic_update	= armada_drm_overlay_plane_atomic_update,
	.atomic_disable	= armada_drm_overlay_plane_atomic_disable,
पूर्ण;

अटल पूर्णांक
armada_overlay_plane_update(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
	काष्ठा drm_framebuffer *fb,
	पूर्णांक crtc_x, पूर्णांक crtc_y, अचिन्हित crtc_w, अचिन्हित crtc_h,
	uपूर्णांक32_t src_x, uपूर्णांक32_t src_y, uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
	काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_plane_state *plane_state;
	पूर्णांक ret = 0;

	trace_armada_ovl_plane_update(plane, crtc, fb,
				 crtc_x, crtc_y, crtc_w, crtc_h,
				 src_x, src_y, src_w, src_h);

	state = drm_atomic_state_alloc(plane->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;
	plane_state = drm_atomic_get_plane_state(state, plane);
	अगर (IS_ERR(plane_state)) अणु
		ret = PTR_ERR(plane_state);
		जाओ fail;
	पूर्ण

	ret = drm_atomic_set_crtc_क्रम_plane(plane_state, crtc);
	अगर (ret != 0)
		जाओ fail;

	drm_atomic_set_fb_क्रम_plane(plane_state, fb);
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_h = crtc_h;
	plane_state->crtc_w = crtc_w;
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_h = src_h;
	plane_state->src_w = src_w;

	ret = drm_atomic_nonblocking_commit(state);
fail:
	drm_atomic_state_put(state);
	वापस ret;
पूर्ण

अटल व्योम armada_ovl_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);
	kमुक्त(plane);
पूर्ण

अटल व्योम armada_overlay_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा armada_overlay_state *state;

	अगर (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);
	kमुक्त(plane->state);
	plane->state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state) अणु
		state->colorkey_yr = 0xfefefe00;
		state->colorkey_ug = 0x01010100;
		state->colorkey_vb = 0x01010100;
		state->colorkey_mode = CFG_CKMODE(CKMODE_RGB) |
				       CFG_ALPHAM_GRA | CFG_ALPHA(0);
		state->colorkey_enable = ADV_GRACOLORKEY;
		state->brightness = DEFAULT_BRIGHTNESS;
		state->contrast = DEFAULT_CONTRAST;
		state->saturation = DEFAULT_SATURATION;
		__drm_atomic_helper_plane_reset(plane, &state->base.base);
		state->base.base.color_encoding = DEFAULT_ENCODING;
		state->base.base.color_range = DRM_COLOR_YCBCR_LIMITED_RANGE;
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
armada_overlay_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा armada_overlay_state *state;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	state = kmemdup(plane->state, माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_plane_duplicate_state(plane,
							  &state->base.base);
	वापस &state->base.base;
पूर्ण

अटल पूर्णांक armada_overlay_set_property(काष्ठा drm_plane *plane,
	काष्ठा drm_plane_state *state, काष्ठा drm_property *property,
	uपूर्णांक64_t val)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(plane->dev);

#घोषणा K2R(val) (((val) >> 0) & 0xff)
#घोषणा K2G(val) (((val) >> 8) & 0xff)
#घोषणा K2B(val) (((val) >> 16) & 0xff)
	अगर (property == priv->colorkey_prop) अणु
#घोषणा CCC(v) ((v) << 24 | (v) << 16 | (v) << 8)
		drm_to_overlay_state(state)->colorkey_yr = CCC(K2R(val));
		drm_to_overlay_state(state)->colorkey_ug = CCC(K2G(val));
		drm_to_overlay_state(state)->colorkey_vb = CCC(K2B(val));
#अघोषित CCC
	पूर्ण अन्यथा अगर (property == priv->colorkey_min_prop) अणु
		drm_to_overlay_state(state)->colorkey_yr &= ~0x00ff0000;
		drm_to_overlay_state(state)->colorkey_yr |= K2R(val) << 16;
		drm_to_overlay_state(state)->colorkey_ug &= ~0x00ff0000;
		drm_to_overlay_state(state)->colorkey_ug |= K2G(val) << 16;
		drm_to_overlay_state(state)->colorkey_vb &= ~0x00ff0000;
		drm_to_overlay_state(state)->colorkey_vb |= K2B(val) << 16;
	पूर्ण अन्यथा अगर (property == priv->colorkey_max_prop) अणु
		drm_to_overlay_state(state)->colorkey_yr &= ~0xff000000;
		drm_to_overlay_state(state)->colorkey_yr |= K2R(val) << 24;
		drm_to_overlay_state(state)->colorkey_ug &= ~0xff000000;
		drm_to_overlay_state(state)->colorkey_ug |= K2G(val) << 24;
		drm_to_overlay_state(state)->colorkey_vb &= ~0xff000000;
		drm_to_overlay_state(state)->colorkey_vb |= K2B(val) << 24;
	पूर्ण अन्यथा अगर (property == priv->colorkey_val_prop) अणु
		drm_to_overlay_state(state)->colorkey_yr &= ~0x0000ff00;
		drm_to_overlay_state(state)->colorkey_yr |= K2R(val) << 8;
		drm_to_overlay_state(state)->colorkey_ug &= ~0x0000ff00;
		drm_to_overlay_state(state)->colorkey_ug |= K2G(val) << 8;
		drm_to_overlay_state(state)->colorkey_vb &= ~0x0000ff00;
		drm_to_overlay_state(state)->colorkey_vb |= K2B(val) << 8;
	पूर्ण अन्यथा अगर (property == priv->colorkey_alpha_prop) अणु
		drm_to_overlay_state(state)->colorkey_yr &= ~0x000000ff;
		drm_to_overlay_state(state)->colorkey_yr |= K2R(val);
		drm_to_overlay_state(state)->colorkey_ug &= ~0x000000ff;
		drm_to_overlay_state(state)->colorkey_ug |= K2G(val);
		drm_to_overlay_state(state)->colorkey_vb &= ~0x000000ff;
		drm_to_overlay_state(state)->colorkey_vb |= K2B(val);
	पूर्ण अन्यथा अगर (property == priv->colorkey_mode_prop) अणु
		अगर (val == CKMODE_DISABLE) अणु
			drm_to_overlay_state(state)->colorkey_mode =
				CFG_CKMODE(CKMODE_DISABLE) |
				CFG_ALPHAM_CFG | CFG_ALPHA(255);
			drm_to_overlay_state(state)->colorkey_enable = 0;
		पूर्ण अन्यथा अणु
			drm_to_overlay_state(state)->colorkey_mode =
				CFG_CKMODE(val) |
				CFG_ALPHAM_GRA | CFG_ALPHA(0);
			drm_to_overlay_state(state)->colorkey_enable =
				ADV_GRACOLORKEY;
		पूर्ण
	पूर्ण अन्यथा अगर (property == priv->brightness_prop) अणु
		drm_to_overlay_state(state)->brightness = val - 256;
	पूर्ण अन्यथा अगर (property == priv->contrast_prop) अणु
		drm_to_overlay_state(state)->contrast = val;
	पूर्ण अन्यथा अगर (property == priv->saturation_prop) अणु
		drm_to_overlay_state(state)->saturation = val;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक armada_overlay_get_property(काष्ठा drm_plane *plane,
	स्थिर काष्ठा drm_plane_state *state, काष्ठा drm_property *property,
	uपूर्णांक64_t *val)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(plane->dev);

#घोषणा C2K(c,s)	(((c) >> (s)) & 0xff)
#घोषणा R2BGR(r,g,b,s)	(C2K(r,s) << 0 | C2K(g,s) << 8 | C2K(b,s) << 16)
	अगर (property == priv->colorkey_prop) अणु
		/* Do best-efक्रमts here क्रम this property */
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 16);
		/* If min != max, or min != val, error out */
		अगर (*val != R2BGR(drm_to_overlay_state(state)->colorkey_yr,
				  drm_to_overlay_state(state)->colorkey_ug,
				  drm_to_overlay_state(state)->colorkey_vb, 24) ||
		    *val != R2BGR(drm_to_overlay_state(state)->colorkey_yr,
				  drm_to_overlay_state(state)->colorkey_ug,
				  drm_to_overlay_state(state)->colorkey_vb, 8))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (property == priv->colorkey_min_prop) अणु
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 16);
	पूर्ण अन्यथा अगर (property == priv->colorkey_max_prop) अणु
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 24);
	पूर्ण अन्यथा अगर (property == priv->colorkey_val_prop) अणु
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 8);
	पूर्ण अन्यथा अगर (property == priv->colorkey_alpha_prop) अणु
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 0);
	पूर्ण अन्यथा अगर (property == priv->colorkey_mode_prop) अणु
		*val = (drm_to_overlay_state(state)->colorkey_mode &
			CFG_CKMODE_MASK) >> ffs(CFG_CKMODE_MASK);
	पूर्ण अन्यथा अगर (property == priv->brightness_prop) अणु
		*val = drm_to_overlay_state(state)->brightness + 256;
	पूर्ण अन्यथा अगर (property == priv->contrast_prop) अणु
		*val = drm_to_overlay_state(state)->contrast;
	पूर्ण अन्यथा अगर (property == priv->saturation_prop) अणु
		*val = drm_to_overlay_state(state)->saturation;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs armada_ovl_plane_funcs = अणु
	.update_plane	= armada_overlay_plane_update,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= armada_ovl_plane_destroy,
	.reset		= armada_overlay_reset,
	.atomic_duplicate_state = armada_overlay_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.atomic_set_property = armada_overlay_set_property,
	.atomic_get_property = armada_overlay_get_property,
पूर्ण;

अटल स्थिर uपूर्णांक32_t armada_ovl_क्रमmats[] = अणु
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YVU422,
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

अटल स्थिर काष्ठा drm_prop_क्रमागत_list armada_drm_colorkey_क्रमागत_list[] = अणु
	अणु CKMODE_DISABLE, "disabled" पूर्ण,
	अणु CKMODE_Y,       "Y component" पूर्ण,
	अणु CKMODE_U,       "U component" पूर्ण,
	अणु CKMODE_V,       "V component" पूर्ण,
	अणु CKMODE_RGB,     "RGB" पूर्ण,
	अणु CKMODE_R,       "R component" पूर्ण,
	अणु CKMODE_G,       "G component" पूर्ण,
	अणु CKMODE_B,       "B component" पूर्ण,
पूर्ण;

अटल पूर्णांक armada_overlay_create_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(dev);

	अगर (priv->colorkey_prop)
		वापस 0;

	priv->colorkey_prop = drm_property_create_range(dev, 0,
				"colorkey", 0, 0xffffff);
	priv->colorkey_min_prop = drm_property_create_range(dev, 0,
				"colorkey_min", 0, 0xffffff);
	priv->colorkey_max_prop = drm_property_create_range(dev, 0,
				"colorkey_max", 0, 0xffffff);
	priv->colorkey_val_prop = drm_property_create_range(dev, 0,
				"colorkey_val", 0, 0xffffff);
	priv->colorkey_alpha_prop = drm_property_create_range(dev, 0,
				"colorkey_alpha", 0, 0xffffff);
	priv->colorkey_mode_prop = drm_property_create_क्रमागत(dev, 0,
				"colorkey_mode",
				armada_drm_colorkey_क्रमागत_list,
				ARRAY_SIZE(armada_drm_colorkey_क्रमागत_list));
	priv->brightness_prop = drm_property_create_range(dev, 0,
				"brightness", 0, 256 + 255);
	priv->contrast_prop = drm_property_create_range(dev, 0,
				"contrast", 0, 0x7fff);
	priv->saturation_prop = drm_property_create_range(dev, 0,
				"saturation", 0, 0x7fff);

	अगर (!priv->colorkey_prop)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक armada_overlay_plane_create(काष्ठा drm_device *dev, अचिन्हित दीर्घ crtcs)
अणु
	काष्ठा armada_निजी *priv = drm_to_armada_dev(dev);
	काष्ठा drm_mode_object *mobj;
	काष्ठा drm_plane *overlay;
	पूर्णांक ret;

	ret = armada_overlay_create_properties(dev);
	अगर (ret)
		वापस ret;

	overlay = kzalloc(माप(*overlay), GFP_KERNEL);
	अगर (!overlay)
		वापस -ENOMEM;

	drm_plane_helper_add(overlay, &armada_overlay_plane_helper_funcs);

	ret = drm_universal_plane_init(dev, overlay, crtcs,
				       &armada_ovl_plane_funcs,
				       armada_ovl_क्रमmats,
				       ARRAY_SIZE(armada_ovl_क्रमmats),
				       शून्य,
				       DRM_PLANE_TYPE_OVERLAY, शून्य);
	अगर (ret) अणु
		kमुक्त(overlay);
		वापस ret;
	पूर्ण

	mobj = &overlay->base;
	drm_object_attach_property(mobj, priv->colorkey_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_min_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_max_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_val_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_alpha_prop,
				   0x000000);
	drm_object_attach_property(mobj, priv->colorkey_mode_prop,
				   CKMODE_RGB);
	drm_object_attach_property(mobj, priv->brightness_prop,
				   256 + DEFAULT_BRIGHTNESS);
	drm_object_attach_property(mobj, priv->contrast_prop,
				   DEFAULT_CONTRAST);
	drm_object_attach_property(mobj, priv->saturation_prop,
				   DEFAULT_SATURATION);

	ret = drm_plane_create_color_properties(overlay,
						BIT(DRM_COLOR_YCBCR_BT601) |
						BIT(DRM_COLOR_YCBCR_BT709),
						BIT(DRM_COLOR_YCBCR_LIMITED_RANGE),
						DEFAULT_ENCODING,
						DRM_COLOR_YCBCR_LIMITED_RANGE);

	वापस ret;
पूर्ण
