<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2014 Endless Mobile
 *
 * Written by:
 *     Jasper St. Pierre <jstpierre@mecheye.net>
 */

#समावेश <linux/bitfield.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "meson_plane.h"
#समावेश "meson_registers.h"
#समावेश "meson_viu.h"
#समावेश "meson_osd_afbcd.h"

/* OSD_SCI_WH_M1 */
#घोषणा SCI_WH_M1_W(w)			FIELD_PREP(GENMASK(28, 16), w)
#घोषणा SCI_WH_M1_H(h)			FIELD_PREP(GENMASK(12, 0), h)

/* OSD_SCO_H_START_END */
/* OSD_SCO_V_START_END */
#घोषणा SCO_HV_START(start)		FIELD_PREP(GENMASK(27, 16), start)
#घोषणा SCO_HV_END(end)			FIELD_PREP(GENMASK(11, 0), end)

/* OSD_SC_CTRL0 */
#घोषणा SC_CTRL0_PATH_EN		BIT(3)
#घोषणा SC_CTRL0_SEL_OSD1		BIT(2)

/* OSD_VSC_CTRL0 */
#घोषणा VSC_BANK_LEN(value)		FIELD_PREP(GENMASK(2, 0), value)
#घोषणा VSC_TOP_INI_RCV_NUM(value)	FIELD_PREP(GENMASK(6, 3), value)
#घोषणा VSC_TOP_RPT_L0_NUM(value)	FIELD_PREP(GENMASK(9, 8), value)
#घोषणा VSC_BOT_INI_RCV_NUM(value)	FIELD_PREP(GENMASK(14, 11), value)
#घोषणा VSC_BOT_RPT_L0_NUM(value)	FIELD_PREP(GENMASK(17, 16), value)
#घोषणा VSC_PROG_INTERLACE		BIT(23)
#घोषणा VSC_VERTICAL_SCALER_EN		BIT(24)

/* OSD_VSC_INI_PHASE */
#घोषणा VSC_INI_PHASE_BOT(bottom)	FIELD_PREP(GENMASK(31, 16), bottom)
#घोषणा VSC_INI_PHASE_TOP(top)		FIELD_PREP(GENMASK(15, 0), top)

/* OSD_HSC_CTRL0 */
#घोषणा HSC_BANK_LENGTH(value)		FIELD_PREP(GENMASK(2, 0), value)
#घोषणा HSC_INI_RCV_NUM0(value)		FIELD_PREP(GENMASK(6, 3), value)
#घोषणा HSC_RPT_P0_NUM0(value)		FIELD_PREP(GENMASK(9, 8), value)
#घोषणा HSC_HORIZ_SCALER_EN		BIT(22)

/* VPP_OSD_VSC_PHASE_STEP */
/* VPP_OSD_HSC_PHASE_STEP */
#घोषणा SC_PHASE_STEP(value)		FIELD_PREP(GENMASK(27, 0), value)

काष्ठा meson_plane अणु
	काष्ठा drm_plane base;
	काष्ठा meson_drm *priv;
	bool enabled;
पूर्ण;
#घोषणा to_meson_plane(x) container_of(x, काष्ठा meson_plane, base)

#घोषणा FRAC_16_16(mult, भाग)    (((mult) << 16) / (भाग))

अटल पूर्णांक meson_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!new_plane_state->crtc)
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state,
					       new_plane_state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	/*
	 * Only allow :
	 * - Upscaling up to 5x, vertical and horizontal
	 * - Final coordinates must match crtc size
	 */
	वापस drm_atomic_helper_check_plane_state(new_plane_state,
						   crtc_state,
						   FRAC_16_16(1, 5),
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, true);
पूर्ण

#घोषणा MESON_MOD_AFBC_VALID_BITS (AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |	\
				   AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |	\
				   AFBC_FORMAT_MOD_YTR |		\
				   AFBC_FORMAT_MOD_SPARSE |		\
				   AFBC_FORMAT_MOD_SPLIT)

/* Takes a fixed 16.16 number and converts it to पूर्णांकeger. */
अटल अंतरभूत पूर्णांक64_t fixed16_to_पूर्णांक(पूर्णांक64_t value)
अणु
	वापस value >> 16;
पूर्ण

अटल u32 meson_g12a_afbcd_line_stride(काष्ठा meson_drm *priv)
अणु
	u32 line_stride = 0;

	चयन (priv->afbcd.क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
		line_stride = ((priv->viu.osd1_width << 4) + 127) >> 7;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		line_stride = ((priv->viu.osd1_width << 5) + 127) >> 7;
		अवरोध;
	पूर्ण

	वापस ((line_stride + 1) >> 1) << 1;
पूर्ण

अटल व्योम meson_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_plane *meson_plane = to_meson_plane(plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_rect dest = drm_plane_state_dest(new_state);
	काष्ठा meson_drm *priv = meson_plane->priv;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_gem_cma_object *gem;
	अचिन्हित दीर्घ flags;
	पूर्णांक vsc_ini_rcv_num, vsc_ini_rpt_p0_num;
	पूर्णांक vsc_bot_rcv_num, vsc_bot_rpt_p0_num;
	पूर्णांक hsc_ini_rcv_num, hsc_ini_rpt_p0_num;
	पूर्णांक hf_phase_step, vf_phase_step;
	पूर्णांक src_w, src_h, dst_w, dst_h;
	पूर्णांक bot_ini_phase;
	पूर्णांक hf_bank_len;
	पूर्णांक vf_bank_len;
	u8 canvas_id_osd1;

	/*
	 * Update Coordinates
	 * Update Formats
	 * Update Buffer
	 * Enable Plane
	 */
	spin_lock_irqsave(&priv->drm->event_lock, flags);

	/* Check अगर AFBC decoder is required क्रम this buffer */
	अगर ((meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
	     meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) &&
	    fb->modअगरier & DRM_FORMAT_MOD_ARM_AFBC(MESON_MOD_AFBC_VALID_BITS))
		priv->viu.osd1_afbcd = true;
	अन्यथा
		priv->viu.osd1_afbcd = false;

	/* Enable OSD and BLK0, set max global alpha */
	priv->viu.osd1_ctrl_stat = OSD_ENABLE |
				   (0xFF << OSD_GLOBAL_ALPHA_SHIFT) |
				   OSD_BLK0_ENABLE;

	priv->viu.osd1_ctrl_stat2 = पढ़ोl(priv->io_base +
					  _REG(VIU_OSD1_CTRL_STAT2));

	canvas_id_osd1 = priv->canvas_id_osd1;

	/* Set up BLK0 to poपूर्णांक to the right canvas */
	priv->viu.osd1_blk0_cfg[0] = canvas_id_osd1 << OSD_CANVAS_SEL;

	अगर (priv->viu.osd1_afbcd) अणु
		अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
			/* This is the पूर्णांकernal decoding memory address */
			priv->viu.osd1_blk1_cfg4 = MESON_G12A_AFBCD_OUT_ADDR;
			priv->viu.osd1_blk0_cfg[0] |= OSD_ENDIANNESS_BE;
			priv->viu.osd1_ctrl_stat2 |= OSD_PENDING_STAT_CLEAN;
			priv->viu.osd1_ctrl_stat |= VIU_OSD1_CFG_SYN_EN;
		पूर्ण

		अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM)) अणु
			priv->viu.osd1_blk0_cfg[0] |= OSD_ENDIANNESS_LE;
			priv->viu.osd1_ctrl_stat2 |= OSD_DPATH_MALI_AFBCD;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->viu.osd1_blk0_cfg[0] |= OSD_ENDIANNESS_LE;

		अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM))
			priv->viu.osd1_ctrl_stat2 &= ~OSD_DPATH_MALI_AFBCD;
	पूर्ण

	/* On GXBB, Use the old non-HDR RGB2YUV converter */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		priv->viu.osd1_blk0_cfg[0] |= OSD_OUTPUT_COLOR_RGB;

	अगर (priv->viu.osd1_afbcd &&
	    meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		priv->viu.osd1_blk0_cfg[0] |= OSD_MALI_SRC_EN |
			priv->afbcd.ops->fmt_to_blk_mode(fb->modअगरier,
							  fb->क्रमmat->क्रमmat);
	पूर्ण अन्यथा अणु
		चयन (fb->क्रमmat->क्रमmat) अणु
		हाल DRM_FORMAT_XRGB8888:
		हाल DRM_FORMAT_ARGB8888:
			priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_32 |
						OSD_COLOR_MATRIX_32_ARGB;
			अवरोध;
		हाल DRM_FORMAT_XBGR8888:
		हाल DRM_FORMAT_ABGR8888:
			priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_32 |
						OSD_COLOR_MATRIX_32_ABGR;
			अवरोध;
		हाल DRM_FORMAT_RGB888:
			priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_24 |
						OSD_COLOR_MATRIX_24_RGB;
			अवरोध;
		हाल DRM_FORMAT_RGB565:
			priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_16 |
						OSD_COLOR_MATRIX_16_RGB565;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
		/* For XRGB, replace the pixel's alpha by 0xFF */
		priv->viu.osd1_ctrl_stat2 |= OSD_REPLACE_EN;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
		/* For ARGB, use the pixel's alpha */
		priv->viu.osd1_ctrl_stat2 &= ~OSD_REPLACE_EN;
		अवरोध;
	पूर्ण

	/* Default scaler parameters */
	vsc_bot_rcv_num = 0;
	vsc_bot_rpt_p0_num = 0;
	hf_bank_len = 4;
	vf_bank_len = 4;

	अगर (new_state->crtc->mode.flags & DRM_MODE_FLAG_INTERLACE) अणु
		vsc_bot_rcv_num = 6;
		vsc_bot_rpt_p0_num = 2;
	पूर्ण

	hsc_ini_rcv_num = hf_bank_len;
	vsc_ini_rcv_num = vf_bank_len;
	hsc_ini_rpt_p0_num = (hf_bank_len / 2) - 1;
	vsc_ini_rpt_p0_num = (vf_bank_len / 2) - 1;

	src_w = fixed16_to_पूर्णांक(new_state->src_w);
	src_h = fixed16_to_पूर्णांक(new_state->src_h);
	dst_w = new_state->crtc_w;
	dst_h = new_state->crtc_h;

	/*
	 * When the output is पूर्णांकerlaced, the OSD must चयन between
	 * each field using the INTERLACE_SEL_ODD (0) of VIU_OSD1_BLK0_CFG_W0
	 * at each vsync.
	 * But the vertical scaler can provide such funtionnality अगर
	 * is configured क्रम 2:1 scaling with पूर्णांकerlace options enabled.
	 */
	अगर (new_state->crtc->mode.flags & DRM_MODE_FLAG_INTERLACE) अणु
		dest.y1 /= 2;
		dest.y2 /= 2;
		dst_h /= 2;
	पूर्ण

	hf_phase_step = ((src_w << 18) / dst_w) << 6;
	vf_phase_step = (src_h << 20) / dst_h;

	अगर (new_state->crtc->mode.flags & DRM_MODE_FLAG_INTERLACE)
		bot_ini_phase = ((vf_phase_step / 2) >> 4);
	अन्यथा
		bot_ini_phase = 0;

	vf_phase_step = (vf_phase_step << 4);

	/* In पूर्णांकerlaced mode, scaler is always active */
	अगर (src_h != dst_h || src_w != dst_w) अणु
		priv->viu.osd_sc_i_wh_m1 = SCI_WH_M1_W(src_w - 1) |
					   SCI_WH_M1_H(src_h - 1);
		priv->viu.osd_sc_o_h_start_end = SCO_HV_START(dest.x1) |
						 SCO_HV_END(dest.x2 - 1);
		priv->viu.osd_sc_o_v_start_end = SCO_HV_START(dest.y1) |
						 SCO_HV_END(dest.y2 - 1);
		/* Enable OSD Scaler */
		priv->viu.osd_sc_ctrl0 = SC_CTRL0_PATH_EN | SC_CTRL0_SEL_OSD1;
	पूर्ण अन्यथा अणु
		priv->viu.osd_sc_i_wh_m1 = 0;
		priv->viu.osd_sc_o_h_start_end = 0;
		priv->viu.osd_sc_o_v_start_end = 0;
		priv->viu.osd_sc_ctrl0 = 0;
	पूर्ण

	/* In पूर्णांकerlaced mode, vertical scaler is always active */
	अगर (src_h != dst_h) अणु
		priv->viu.osd_sc_v_ctrl0 =
					VSC_BANK_LEN(vf_bank_len) |
					VSC_TOP_INI_RCV_NUM(vsc_ini_rcv_num) |
					VSC_TOP_RPT_L0_NUM(vsc_ini_rpt_p0_num) |
					VSC_VERTICAL_SCALER_EN;

		अगर (new_state->crtc->mode.flags & DRM_MODE_FLAG_INTERLACE)
			priv->viu.osd_sc_v_ctrl0 |=
					VSC_BOT_INI_RCV_NUM(vsc_bot_rcv_num) |
					VSC_BOT_RPT_L0_NUM(vsc_bot_rpt_p0_num) |
					VSC_PROG_INTERLACE;

		priv->viu.osd_sc_v_phase_step = SC_PHASE_STEP(vf_phase_step);
		priv->viu.osd_sc_v_ini_phase = VSC_INI_PHASE_BOT(bot_ini_phase);
	पूर्ण अन्यथा अणु
		priv->viu.osd_sc_v_ctrl0 = 0;
		priv->viu.osd_sc_v_phase_step = 0;
		priv->viu.osd_sc_v_ini_phase = 0;
	पूर्ण

	/* Horizontal scaler is only used अगर width करोes not match */
	अगर (src_w != dst_w) अणु
		priv->viu.osd_sc_h_ctrl0 =
					HSC_BANK_LENGTH(hf_bank_len) |
					HSC_INI_RCV_NUM0(hsc_ini_rcv_num) |
					HSC_RPT_P0_NUM0(hsc_ini_rpt_p0_num) |
					HSC_HORIZ_SCALER_EN;
		priv->viu.osd_sc_h_phase_step = SC_PHASE_STEP(hf_phase_step);
		priv->viu.osd_sc_h_ini_phase = 0;
	पूर्ण अन्यथा अणु
		priv->viu.osd_sc_h_ctrl0 = 0;
		priv->viu.osd_sc_h_phase_step = 0;
		priv->viu.osd_sc_h_ini_phase = 0;
	पूर्ण

	/*
	 * The क्रमmat of these रेजिस्टरs is (x2 << 16 | x1),
	 * where x2 is exclusive.
	 * e.g. +30x1920 would be (1919 << 16) | 30
	 */
	priv->viu.osd1_blk0_cfg[1] =
				((fixed16_to_पूर्णांक(new_state->src.x2) - 1) << 16) |
				fixed16_to_पूर्णांक(new_state->src.x1);
	priv->viu.osd1_blk0_cfg[2] =
				((fixed16_to_पूर्णांक(new_state->src.y2) - 1) << 16) |
				fixed16_to_पूर्णांक(new_state->src.y1);
	priv->viu.osd1_blk0_cfg[3] = ((dest.x2 - 1) << 16) | dest.x1;
	priv->viu.osd1_blk0_cfg[4] = ((dest.y2 - 1) << 16) | dest.y1;

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		priv->viu.osd_blend_din0_scope_h = ((dest.x2 - 1) << 16) | dest.x1;
		priv->viu.osd_blend_din0_scope_v = ((dest.y2 - 1) << 16) | dest.y1;
		priv->viu.osb_blend0_size = dst_h << 16 | dst_w;
		priv->viu.osb_blend1_size = dst_h << 16 | dst_w;
	पूर्ण

	/* Update Canvas with buffer address */
	gem = drm_fb_cma_get_gem_obj(fb, 0);

	priv->viu.osd1_addr = gem->paddr;
	priv->viu.osd1_stride = fb->pitches[0];
	priv->viu.osd1_height = fb->height;
	priv->viu.osd1_width = fb->width;

	अगर (priv->viu.osd1_afbcd) अणु
		priv->afbcd.modअगरier = fb->modअगरier;
		priv->afbcd.क्रमmat = fb->क्रमmat->क्रमmat;

		/* Calculate decoder ग_लिखो stride */
		अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
			priv->viu.osd1_blk2_cfg4 =
				meson_g12a_afbcd_line_stride(priv);
	पूर्ण

	अगर (!meson_plane->enabled) अणु
		/* Reset OSD1 beक्रमe enabling it on GXL+ SoCs */
		अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		    meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
			meson_viu_osd1_reset(priv);

		meson_plane->enabled = true;
	पूर्ण

	priv->viu.osd1_enabled = true;

	spin_unlock_irqrestore(&priv->drm->event_lock, flags);
पूर्ण

अटल व्योम meson_plane_atomic_disable(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_plane *meson_plane = to_meson_plane(plane);
	काष्ठा meson_drm *priv = meson_plane->priv;

	अगर (priv->afbcd.ops) अणु
		priv->afbcd.ops->reset(priv);
		priv->afbcd.ops->disable(priv);
	पूर्ण

	/* Disable OSD1 */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		ग_लिखोl_bits_relaxed(VIU_OSD1_POSTBLD_SRC_OSD1, 0,
				    priv->io_base + _REG(OSD1_BLEND_SRC_CTRL));
	अन्यथा
		ग_लिखोl_bits_relaxed(VPP_OSD1_POSTBLEND, 0,
				    priv->io_base + _REG(VPP_MISC));

	meson_plane->enabled = false;
	priv->viu.osd1_enabled = false;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs meson_plane_helper_funcs = अणु
	.atomic_check	= meson_plane_atomic_check,
	.atomic_disable	= meson_plane_atomic_disable,
	.atomic_update	= meson_plane_atomic_update,
	.prepare_fb	= drm_gem_plane_helper_prepare_fb,
पूर्ण;

अटल bool meson_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					     u32 क्रमmat, u64 modअगरier)
अणु
	काष्ठा meson_plane *meson_plane = to_meson_plane(plane);
	काष्ठा meson_drm *priv = meson_plane->priv;
	पूर्णांक i;

	अगर (modअगरier == DRM_FORMAT_MOD_INVALID)
		वापस false;

	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस true;

	अगर (!meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) &&
	    !meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		वापस false;

	अगर (modअगरier & ~DRM_FORMAT_MOD_ARM_AFBC(MESON_MOD_AFBC_VALID_BITS))
		वापस false;

	क्रम (i = 0 ; i < plane->modअगरier_count ; ++i)
		अगर (plane->modअगरiers[i] == modअगरier)
			अवरोध;

	अगर (i == plane->modअगरier_count) अणु
		DRM_DEBUG_KMS("Unsupported modifier\n");
		वापस false;
	पूर्ण

	अगर (priv->afbcd.ops && priv->afbcd.ops->supported_fmt)
		वापस priv->afbcd.ops->supported_fmt(modअगरier, क्रमmat);

	DRM_DEBUG_KMS("AFBC Unsupported\n");
	वापस false;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs meson_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= drm_plane_cleanup,
	.reset			= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
	.क्रमmat_mod_supported   = meson_plane_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर uपूर्णांक32_t supported_drm_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGB565,
पूर्ण;

अटल स्थिर uपूर्णांक64_t क्रमmat_modअगरiers_afbc_gxm[] = अणु
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |
				AFBC_FORMAT_MOD_SPARSE |
				AFBC_FORMAT_MOD_YTR),
	/* SPLIT mandates SPARSE, RGB modes mandates YTR */
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |
				AFBC_FORMAT_MOD_YTR |
				AFBC_FORMAT_MOD_SPARSE |
				AFBC_FORMAT_MOD_SPLIT),
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल स्थिर uपूर्णांक64_t क्रमmat_modअगरiers_afbc_g12a[] = अणु
	/*
	 * - TOFIX Support AFBC modअगरiers क्रम YUV क्रमmats (16x16 + TILED)
	 * - SPLIT is mandatory क्रम perक्रमmances reasons when in 16x16
	 *   block size
	 * - 32x8 block size + SPLIT is mandatory with 4K frame size
	 *   क्रम perक्रमmances reasons
	 */
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |
				AFBC_FORMAT_MOD_SPARSE |
				AFBC_FORMAT_MOD_SPLIT),
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 |
				AFBC_FORMAT_MOD_YTR |
				AFBC_FORMAT_MOD_SPARSE |
				AFBC_FORMAT_MOD_SPLIT),
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |
				AFBC_FORMAT_MOD_SPARSE),
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |
				AFBC_FORMAT_MOD_YTR |
				AFBC_FORMAT_MOD_SPARSE),
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |
				AFBC_FORMAT_MOD_SPARSE |
				AFBC_FORMAT_MOD_SPLIT),
	DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 |
				AFBC_FORMAT_MOD_YTR |
				AFBC_FORMAT_MOD_SPARSE |
				AFBC_FORMAT_MOD_SPLIT),
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल स्थिर uपूर्णांक64_t क्रमmat_modअगरiers_शेष[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

पूर्णांक meson_plane_create(काष्ठा meson_drm *priv)
अणु
	काष्ठा meson_plane *meson_plane;
	काष्ठा drm_plane *plane;
	स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers = क्रमmat_modअगरiers_शेष;

	meson_plane = devm_kzalloc(priv->drm->dev, माप(*meson_plane),
				   GFP_KERNEL);
	अगर (!meson_plane)
		वापस -ENOMEM;

	meson_plane->priv = priv;
	plane = &meson_plane->base;

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM))
		क्रमmat_modअगरiers = क्रमmat_modअगरiers_afbc_gxm;
	अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		क्रमmat_modअगरiers = क्रमmat_modअगरiers_afbc_g12a;

	drm_universal_plane_init(priv->drm, plane, 0xFF,
				 &meson_plane_funcs,
				 supported_drm_क्रमmats,
				 ARRAY_SIZE(supported_drm_क्रमmats),
				 क्रमmat_modअगरiers,
				 DRM_PLANE_TYPE_PRIMARY, "meson_primary_plane");

	drm_plane_helper_add(plane, &meson_plane_helper_funcs);

	/* For now, OSD Primary plane is always on the front */
	drm_plane_create_zpos_immutable_property(plane, 1);

	priv->primary_plane = plane;

	वापस 0;
पूर्ण
