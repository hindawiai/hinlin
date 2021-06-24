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
#समावेश <linux/soc/amlogic/meson-canvas.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "meson_crtc.h"
#समावेश "meson_plane.h"
#समावेश "meson_registers.h"
#समावेश "meson_venc.h"
#समावेश "meson_viu.h"
#समावेश "meson_rdma.h"
#समावेश "meson_vpp.h"
#समावेश "meson_osd_afbcd.h"

#घोषणा MESON_G12A_VIU_OFFSET	0x5ec0

/* CRTC definition */

काष्ठा meson_crtc अणु
	काष्ठा drm_crtc base;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा meson_drm *priv;
	व्योम (*enable_osd1)(काष्ठा meson_drm *priv);
	व्योम (*enable_vd1)(काष्ठा meson_drm *priv);
	व्योम (*enable_osd1_afbc)(काष्ठा meson_drm *priv);
	व्योम (*disable_osd1_afbc)(काष्ठा meson_drm *priv);
	अचिन्हित पूर्णांक viu_offset;
	bool vsync_क्रमced;
	bool vsync_disabled;
पूर्ण;
#घोषणा to_meson_crtc(x) container_of(x, काष्ठा meson_crtc, base)

/* CRTC */

अटल पूर्णांक meson_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा meson_drm *priv = meson_crtc->priv;

	meson_crtc->vsync_disabled = false;
	meson_venc_enable_vsync(priv);

	वापस 0;
पूर्ण

अटल व्योम meson_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा meson_drm *priv = meson_crtc->priv;

	अगर (!meson_crtc->vsync_क्रमced) अणु
		meson_crtc->vsync_disabled = true;
		meson_venc_disable_vsync(priv);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs meson_crtc_funcs = अणु
	.atomic_destroy_state	= drm_atomic_helper_crtc_destroy_state,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.destroy		= drm_crtc_cleanup,
	.page_flip		= drm_atomic_helper_page_flip,
	.reset			= drm_atomic_helper_crtc_reset,
	.set_config             = drm_atomic_helper_set_config,
	.enable_vblank		= meson_crtc_enable_vblank,
	.disable_vblank		= meson_crtc_disable_vblank,

पूर्ण;

अटल व्योम meson_g12a_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा drm_crtc_state *crtc_state = crtc->state;
	काष्ठा meson_drm *priv = meson_crtc->priv;

	DRM_DEBUG_DRIVER("\n");

	अगर (!crtc_state) अणु
		DRM_ERROR("Invalid crtc_state\n");
		वापस;
	पूर्ण

	/* VD1 Preblend vertical start/end */
	ग_लिखोl(FIELD_PREP(GENMASK(11, 0), 2303),
	       priv->io_base + _REG(VPP_PREBLEND_VD1_V_START_END));

	/* Setup Blender */
	ग_लिखोl(crtc_state->mode.hdisplay |
	       crtc_state->mode.vdisplay << 16,
	       priv->io_base + _REG(VPP_POSTBLEND_H_SIZE));

	ग_लिखोl_relaxed(0 << 16 |
			(crtc_state->mode.hdisplay - 1),
			priv->io_base + _REG(VPP_OSD1_BLD_H_SCOPE));
	ग_लिखोl_relaxed(0 << 16 |
			(crtc_state->mode.vdisplay - 1),
			priv->io_base + _REG(VPP_OSD1_BLD_V_SCOPE));
	ग_लिखोl_relaxed(crtc_state->mode.hdisplay << 16 |
			crtc_state->mode.vdisplay,
			priv->io_base + _REG(VPP_OUT_H_V_SIZE));

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम meson_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा drm_crtc_state *crtc_state = crtc->state;
	काष्ठा meson_drm *priv = meson_crtc->priv;

	DRM_DEBUG_DRIVER("\n");

	अगर (!crtc_state) अणु
		DRM_ERROR("Invalid crtc_state\n");
		वापस;
	पूर्ण

	/* Enable VPP Postblend */
	ग_लिखोl(crtc_state->mode.hdisplay,
	       priv->io_base + _REG(VPP_POSTBLEND_H_SIZE));

	/* VD1 Preblend vertical start/end */
	ग_लिखोl(FIELD_PREP(GENMASK(11, 0), 2303),
			priv->io_base + _REG(VPP_PREBLEND_VD1_V_START_END));

	ग_लिखोl_bits_relaxed(VPP_POSTBLEND_ENABLE, VPP_POSTBLEND_ENABLE,
			    priv->io_base + _REG(VPP_MISC));

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम meson_g12a_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा meson_drm *priv = meson_crtc->priv;

	DRM_DEBUG_DRIVER("\n");

	drm_crtc_vblank_off(crtc);

	priv->viu.osd1_enabled = false;
	priv->viu.osd1_commit = false;

	priv->viu.vd1_enabled = false;
	priv->viu.vd1_commit = false;

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम meson_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा meson_drm *priv = meson_crtc->priv;

	DRM_DEBUG_DRIVER("\n");

	drm_crtc_vblank_off(crtc);

	priv->viu.osd1_enabled = false;
	priv->viu.osd1_commit = false;

	priv->viu.vd1_enabled = false;
	priv->viu.vd1_commit = false;

	/* Disable VPP Postblend */
	ग_लिखोl_bits_relaxed(VPP_OSD1_POSTBLEND | VPP_VD1_POSTBLEND |
			    VPP_VD1_PREBLEND | VPP_POSTBLEND_ENABLE, 0,
			    priv->io_base + _REG(VPP_MISC));

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम meson_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	अचिन्हित दीर्घ flags;

	अगर (crtc->state->event) अणु
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&crtc->dev->event_lock, flags);
		meson_crtc->event = crtc->state->event;
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम meson_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(crtc);
	काष्ठा meson_drm *priv = meson_crtc->priv;

	priv->viu.osd1_commit = true;
	priv->viu.vd1_commit = true;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs meson_crtc_helper_funcs = अणु
	.atomic_begin	= meson_crtc_atomic_begin,
	.atomic_flush	= meson_crtc_atomic_flush,
	.atomic_enable	= meson_crtc_atomic_enable,
	.atomic_disable	= meson_crtc_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs meson_g12a_crtc_helper_funcs = अणु
	.atomic_begin	= meson_crtc_atomic_begin,
	.atomic_flush	= meson_crtc_atomic_flush,
	.atomic_enable	= meson_g12a_crtc_atomic_enable,
	.atomic_disable	= meson_g12a_crtc_atomic_disable,
पूर्ण;

अटल व्योम meson_crtc_enable_osd1(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_bits_relaxed(VPP_OSD1_POSTBLEND, VPP_OSD1_POSTBLEND,
			    priv->io_base + _REG(VPP_MISC));
पूर्ण

अटल व्योम meson_crtc_g12a_enable_osd1_afbc(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_relaxed(priv->viu.osd1_blk2_cfg4,
		       priv->io_base + _REG(VIU_OSD1_BLK2_CFG_W4));

	ग_लिखोl_bits_relaxed(OSD_MEM_LINEAR_ADDR, OSD_MEM_LINEAR_ADDR,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT));

	ग_लिखोl_relaxed(priv->viu.osd1_blk1_cfg4,
		       priv->io_base + _REG(VIU_OSD1_BLK1_CFG_W4));

	meson_viu_g12a_enable_osd1_afbc(priv);

	ग_लिखोl_bits_relaxed(OSD_MEM_LINEAR_ADDR, OSD_MEM_LINEAR_ADDR,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT));

	ग_लिखोl_bits_relaxed(OSD_MALI_SRC_EN, OSD_MALI_SRC_EN,
			    priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W0));
पूर्ण

अटल व्योम meson_g12a_crtc_enable_osd1(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_relaxed(priv->viu.osd_blend_din0_scope_h,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_DIN0_SCOPE_H));
	ग_लिखोl_relaxed(priv->viu.osd_blend_din0_scope_v,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_DIN0_SCOPE_V));
	ग_लिखोl_relaxed(priv->viu.osb_blend0_size,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_BLEND0_SIZE));
	ग_लिखोl_relaxed(priv->viu.osb_blend1_size,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_BLEND1_SIZE));
	ग_लिखोl_bits_relaxed(3 << 8, 3 << 8,
			    priv->io_base + _REG(OSD1_BLEND_SRC_CTRL));
पूर्ण

अटल व्योम meson_crtc_enable_vd1(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_bits_relaxed(VPP_VD1_PREBLEND | VPP_VD1_POSTBLEND |
			    VPP_COLOR_MNG_ENABLE,
			    VPP_VD1_PREBLEND | VPP_VD1_POSTBLEND |
			    VPP_COLOR_MNG_ENABLE,
			    priv->io_base + _REG(VPP_MISC));

	ग_लिखोl_bits_relaxed(VIU_CTRL0_AFBC_TO_VD1,
			    priv->viu.vd1_afbc ? VIU_CTRL0_AFBC_TO_VD1 : 0,
			    priv->io_base + _REG(VIU_MISC_CTRL0));
पूर्ण

अटल व्योम meson_g12a_crtc_enable_vd1(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_relaxed(VD_BLEND_PREBLD_SRC_VD1 |
		       VD_BLEND_PREBLD_PREMULT_EN |
		       VD_BLEND_POSTBLD_SRC_VD1 |
		       VD_BLEND_POSTBLD_PREMULT_EN,
		       priv->io_base + _REG(VD1_BLEND_SRC_CTRL));

	ग_लिखोl_relaxed(priv->viu.vd1_afbc ?
		       (VD1_AXI_SEL_AFBC | AFBC_VD1_SEL) : 0,
		       priv->io_base + _REG(VD1_AFBCD0_MISC_CTRL));
पूर्ण

व्योम meson_crtc_irq(काष्ठा meson_drm *priv)
अणु
	काष्ठा meson_crtc *meson_crtc = to_meson_crtc(priv->crtc);
	अचिन्हित दीर्घ flags;

	/* Update the OSD रेजिस्टरs */
	अगर (priv->viu.osd1_enabled && priv->viu.osd1_commit) अणु
		ग_लिखोl_relaxed(priv->viu.osd1_ctrl_stat,
				priv->io_base + _REG(VIU_OSD1_CTRL_STAT));
		ग_लिखोl_relaxed(priv->viu.osd1_ctrl_stat2,
				priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));
		ग_लिखोl_relaxed(priv->viu.osd1_blk0_cfg[0],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W0));
		ग_लिखोl_relaxed(priv->viu.osd1_blk0_cfg[1],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W1));
		ग_लिखोl_relaxed(priv->viu.osd1_blk0_cfg[2],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W2));
		ग_लिखोl_relaxed(priv->viu.osd1_blk0_cfg[3],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W3));
		ग_लिखोl_relaxed(priv->viu.osd1_blk0_cfg[4],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W4));

		अगर (priv->viu.osd1_afbcd) अणु
			अगर (meson_crtc->enable_osd1_afbc)
				meson_crtc->enable_osd1_afbc(priv);
		पूर्ण अन्यथा अणु
			अगर (meson_crtc->disable_osd1_afbc)
				meson_crtc->disable_osd1_afbc(priv);
			अगर (priv->afbcd.ops) अणु
				priv->afbcd.ops->reset(priv);
				priv->afbcd.ops->disable(priv);
			पूर्ण
			meson_crtc->vsync_क्रमced = false;
		पूर्ण

		ग_लिखोl_relaxed(priv->viu.osd_sc_ctrl0,
				priv->io_base + _REG(VPP_OSD_SC_CTRL0));
		ग_लिखोl_relaxed(priv->viu.osd_sc_i_wh_m1,
				priv->io_base + _REG(VPP_OSD_SCI_WH_M1));
		ग_लिखोl_relaxed(priv->viu.osd_sc_o_h_start_end,
				priv->io_base + _REG(VPP_OSD_SCO_H_START_END));
		ग_लिखोl_relaxed(priv->viu.osd_sc_o_v_start_end,
				priv->io_base + _REG(VPP_OSD_SCO_V_START_END));
		ग_लिखोl_relaxed(priv->viu.osd_sc_v_ini_phase,
				priv->io_base + _REG(VPP_OSD_VSC_INI_PHASE));
		ग_लिखोl_relaxed(priv->viu.osd_sc_v_phase_step,
				priv->io_base + _REG(VPP_OSD_VSC_PHASE_STEP));
		ग_लिखोl_relaxed(priv->viu.osd_sc_h_ini_phase,
				priv->io_base + _REG(VPP_OSD_HSC_INI_PHASE));
		ग_लिखोl_relaxed(priv->viu.osd_sc_h_phase_step,
				priv->io_base + _REG(VPP_OSD_HSC_PHASE_STEP));
		ग_लिखोl_relaxed(priv->viu.osd_sc_h_ctrl0,
				priv->io_base + _REG(VPP_OSD_HSC_CTRL0));
		ग_लिखोl_relaxed(priv->viu.osd_sc_v_ctrl0,
				priv->io_base + _REG(VPP_OSD_VSC_CTRL0));

		अगर (!priv->viu.osd1_afbcd)
			meson_canvas_config(priv->canvas, priv->canvas_id_osd1,
					    priv->viu.osd1_addr,
					    priv->viu.osd1_stride,
					    priv->viu.osd1_height,
					    MESON_CANVAS_WRAP_NONE,
					    MESON_CANVAS_BLKMODE_LINEAR, 0);

		/* Enable OSD1 */
		अगर (meson_crtc->enable_osd1)
			meson_crtc->enable_osd1(priv);

		अगर (priv->viu.osd1_afbcd) अणु
			priv->afbcd.ops->reset(priv);
			priv->afbcd.ops->setup(priv);
			priv->afbcd.ops->enable(priv);
			meson_crtc->vsync_क्रमced = true;
		पूर्ण

		priv->viu.osd1_commit = false;
	पूर्ण

	/* Update the VD1 रेजिस्टरs */
	अगर (priv->viu.vd1_enabled && priv->viu.vd1_commit) अणु

		अगर (priv->viu.vd1_afbc) अणु
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_head_addr,
				       priv->io_base +
				       _REG(AFBC_HEAD_BADDR));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_body_addr,
				       priv->io_base +
				       _REG(AFBC_BODY_BADDR));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_en,
				       priv->io_base +
				       _REG(AFBC_ENABLE));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_mode,
				       priv->io_base +
				       _REG(AFBC_MODE));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_size_in,
				       priv->io_base +
				       _REG(AFBC_SIZE_IN));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_dec_def_color,
				       priv->io_base +
				       _REG(AFBC_DEC_DEF_COLOR));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_conv_ctrl,
				       priv->io_base +
				       _REG(AFBC_CONV_CTRL));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_size_out,
				       priv->io_base +
				       _REG(AFBC_SIZE_OUT));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_vd_cfmt_ctrl,
				       priv->io_base +
				       _REG(AFBC_VD_CFMT_CTRL));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_vd_cfmt_w,
				       priv->io_base +
				       _REG(AFBC_VD_CFMT_W));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_mअगर_hor_scope,
				       priv->io_base +
				       _REG(AFBC_MIF_HOR_SCOPE));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_mअगर_ver_scope,
				       priv->io_base +
				       _REG(AFBC_MIF_VER_SCOPE));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_pixel_hor_scope,
				       priv->io_base+
				       _REG(AFBC_PIXEL_HOR_SCOPE));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_pixel_ver_scope,
				       priv->io_base +
				       _REG(AFBC_PIXEL_VER_SCOPE));
			ग_लिखोl_relaxed(priv->viu.vd1_afbc_vd_cfmt_h,
				       priv->io_base +
				       _REG(AFBC_VD_CFMT_H));
		पूर्ण अन्यथा अणु
			चयन (priv->viu.vd1_planes) अणु
			हाल 3:
				meson_canvas_config(priv->canvas,
						    priv->canvas_id_vd1_2,
						    priv->viu.vd1_addr2,
						    priv->viu.vd1_stride2,
						    priv->viu.vd1_height2,
						    MESON_CANVAS_WRAP_NONE,
						    MESON_CANVAS_BLKMODE_LINEAR,
						    MESON_CANVAS_ENDIAN_SWAP64);
				fallthrough;
			हाल 2:
				meson_canvas_config(priv->canvas,
						    priv->canvas_id_vd1_1,
						    priv->viu.vd1_addr1,
						    priv->viu.vd1_stride1,
						    priv->viu.vd1_height1,
						    MESON_CANVAS_WRAP_NONE,
						    MESON_CANVAS_BLKMODE_LINEAR,
						    MESON_CANVAS_ENDIAN_SWAP64);
				fallthrough;
			हाल 1:
				meson_canvas_config(priv->canvas,
						    priv->canvas_id_vd1_0,
						    priv->viu.vd1_addr0,
						    priv->viu.vd1_stride0,
						    priv->viu.vd1_height0,
						    MESON_CANVAS_WRAP_NONE,
						    MESON_CANVAS_BLKMODE_LINEAR,
						    MESON_CANVAS_ENDIAN_SWAP64);
			पूर्ण

			ग_लिखोl_relaxed(0, priv->io_base + _REG(AFBC_ENABLE));
		पूर्ण

		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_gen_reg,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_GEN_REG));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_gen_reg,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_GEN_REG));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_gen_reg2,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_GEN_REG2));
		ग_लिखोl_relaxed(priv->viu.viu_vd1_fmt_ctrl,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VIU_VD1_FMT_CTRL));
		ग_लिखोl_relaxed(priv->viu.viu_vd1_fmt_ctrl,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VIU_VD2_FMT_CTRL));
		ग_लिखोl_relaxed(priv->viu.viu_vd1_fmt_w,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VIU_VD1_FMT_W));
		ग_लिखोl_relaxed(priv->viu.viu_vd1_fmt_w,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VIU_VD2_FMT_W));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_canvas0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CANVAS0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_canvas0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CANVAS1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_canvas0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CANVAS0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_canvas0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CANVAS1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA_X0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA_X1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA_X0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA_X1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA_Y0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA_Y1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA_Y0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA_Y1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA_X0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA_X1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA_X0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_x0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA_X1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA_Y0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA_Y1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA_Y0));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma_y0,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA_Y1));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_repeat_loop,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_RPT_LOOP));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_repeat_loop,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_RPT_LOOP));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA0_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA0_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA1_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_luma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA1_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA0_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA0_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA1_RPT_PAT));
		ग_लिखोl_relaxed(priv->viu.vd1_अगर0_chroma0_rpt_pat,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA1_RPT_PAT));
		ग_लिखोl_relaxed(0, priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_LUMA_PSEL));
		ग_लिखोl_relaxed(0, priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_CHROMA_PSEL));
		ग_लिखोl_relaxed(0, priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_LUMA_PSEL));
		ग_लिखोl_relaxed(0, priv->io_base + meson_crtc->viu_offset +
				_REG(VD2_IF0_CHROMA_PSEL));
		ग_लिखोl_relaxed(priv->viu.vd1_range_map_y,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_RANGE_MAP_Y));
		ग_लिखोl_relaxed(priv->viu.vd1_range_map_cb,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_RANGE_MAP_CB));
		ग_लिखोl_relaxed(priv->viu.vd1_range_map_cr,
				priv->io_base + meson_crtc->viu_offset +
				_REG(VD1_IF0_RANGE_MAP_CR));
		ग_लिखोl_relaxed(VPP_VSC_BANK_LENGTH(4) |
			       VPP_HSC_BANK_LENGTH(4) |
			       VPP_SC_VD_EN_ENABLE |
			       VPP_SC_TOP_EN_ENABLE |
			       VPP_SC_HSC_EN_ENABLE |
			       VPP_SC_VSC_EN_ENABLE,
				priv->io_base + _REG(VPP_SC_MISC));
		ग_लिखोl_relaxed(priv->viu.vpp_pic_in_height,
				priv->io_base + _REG(VPP_PIC_IN_HEIGHT));
		ग_लिखोl_relaxed(priv->viu.vpp_postblend_vd1_h_start_end,
			priv->io_base + _REG(VPP_POSTBLEND_VD1_H_START_END));
		ग_लिखोl_relaxed(priv->viu.vpp_blend_vd2_h_start_end,
			priv->io_base + _REG(VPP_BLEND_VD2_H_START_END));
		ग_लिखोl_relaxed(priv->viu.vpp_postblend_vd1_v_start_end,
			priv->io_base + _REG(VPP_POSTBLEND_VD1_V_START_END));
		ग_लिखोl_relaxed(priv->viu.vpp_blend_vd2_v_start_end,
			priv->io_base + _REG(VPP_BLEND_VD2_V_START_END));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_region12_startp,
				priv->io_base + _REG(VPP_HSC_REGION12_STARTP));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_region34_startp,
				priv->io_base + _REG(VPP_HSC_REGION34_STARTP));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_region4_endp,
				priv->io_base + _REG(VPP_HSC_REGION4_ENDP));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_start_phase_step,
				priv->io_base + _REG(VPP_HSC_START_PHASE_STEP));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_region1_phase_slope,
			priv->io_base + _REG(VPP_HSC_REGION1_PHASE_SLOPE));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_region3_phase_slope,
			priv->io_base + _REG(VPP_HSC_REGION3_PHASE_SLOPE));
		ग_लिखोl_relaxed(priv->viu.vpp_line_in_length,
				priv->io_base + _REG(VPP_LINE_IN_LENGTH));
		ग_लिखोl_relaxed(priv->viu.vpp_preblend_h_size,
				priv->io_base + _REG(VPP_PREBLEND_H_SIZE));
		ग_लिखोl_relaxed(priv->viu.vpp_vsc_region12_startp,
				priv->io_base + _REG(VPP_VSC_REGION12_STARTP));
		ग_लिखोl_relaxed(priv->viu.vpp_vsc_region34_startp,
				priv->io_base + _REG(VPP_VSC_REGION34_STARTP));
		ग_लिखोl_relaxed(priv->viu.vpp_vsc_region4_endp,
				priv->io_base + _REG(VPP_VSC_REGION4_ENDP));
		ग_लिखोl_relaxed(priv->viu.vpp_vsc_start_phase_step,
				priv->io_base + _REG(VPP_VSC_START_PHASE_STEP));
		ग_लिखोl_relaxed(priv->viu.vpp_vsc_ini_phase,
				priv->io_base + _REG(VPP_VSC_INI_PHASE));
		ग_लिखोl_relaxed(priv->viu.vpp_vsc_phase_ctrl,
				priv->io_base + _REG(VPP_VSC_PHASE_CTRL));
		ग_लिखोl_relaxed(priv->viu.vpp_hsc_phase_ctrl,
				priv->io_base + _REG(VPP_HSC_PHASE_CTRL));
		ग_लिखोl_relaxed(0x42, priv->io_base + _REG(VPP_SCALE_COEF_IDX));

		/* Enable VD1 */
		अगर (meson_crtc->enable_vd1)
			meson_crtc->enable_vd1(priv);

		priv->viu.vd1_commit = false;
	पूर्ण

	अगर (meson_crtc->vsync_disabled)
		वापस;

	drm_crtc_handle_vblank(priv->crtc);

	spin_lock_irqsave(&priv->drm->event_lock, flags);
	अगर (meson_crtc->event) अणु
		drm_crtc_send_vblank_event(priv->crtc, meson_crtc->event);
		drm_crtc_vblank_put(priv->crtc);
		meson_crtc->event = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&priv->drm->event_lock, flags);
पूर्ण

पूर्णांक meson_crtc_create(काष्ठा meson_drm *priv)
अणु
	काष्ठा meson_crtc *meson_crtc;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	meson_crtc = devm_kzalloc(priv->drm->dev, माप(*meson_crtc),
				  GFP_KERNEL);
	अगर (!meson_crtc)
		वापस -ENOMEM;

	meson_crtc->priv = priv;
	crtc = &meson_crtc->base;
	ret = drm_crtc_init_with_planes(priv->drm, crtc,
					priv->primary_plane, शून्य,
					&meson_crtc_funcs, "meson_crtc");
	अगर (ret) अणु
		dev_err(priv->drm->dev, "Failed to init CRTC\n");
		वापस ret;
	पूर्ण

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		meson_crtc->enable_osd1 = meson_g12a_crtc_enable_osd1;
		meson_crtc->enable_vd1 = meson_g12a_crtc_enable_vd1;
		meson_crtc->viu_offset = MESON_G12A_VIU_OFFSET;
		meson_crtc->enable_osd1_afbc =
					meson_crtc_g12a_enable_osd1_afbc;
		meson_crtc->disable_osd1_afbc =
					meson_viu_g12a_disable_osd1_afbc;
		drm_crtc_helper_add(crtc, &meson_g12a_crtc_helper_funcs);
	पूर्ण अन्यथा अणु
		meson_crtc->enable_osd1 = meson_crtc_enable_osd1;
		meson_crtc->enable_vd1 = meson_crtc_enable_vd1;
		अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM)) अणु
			meson_crtc->enable_osd1_afbc =
					meson_viu_gxm_enable_osd1_afbc;
			meson_crtc->disable_osd1_afbc =
					meson_viu_gxm_disable_osd1_afbc;
		पूर्ण
		drm_crtc_helper_add(crtc, &meson_crtc_helper_funcs);
	पूर्ण

	priv->crtc = crtc;

	वापस 0;
पूर्ण
