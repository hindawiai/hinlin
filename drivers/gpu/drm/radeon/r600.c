<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "avivod.h"
#समावेश "evergreen.h"
#समावेश "r600.h"
#समावेश "r600d.h"
#समावेश "rv770.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "radeon_mode.h"
#समावेश "radeon_ucode.h"

/* Firmware Names */
MODULE_FIRMWARE("radeon/R600_pfp.bin");
MODULE_FIRMWARE("radeon/R600_me.bin");
MODULE_FIRMWARE("radeon/RV610_pfp.bin");
MODULE_FIRMWARE("radeon/RV610_me.bin");
MODULE_FIRMWARE("radeon/RV630_pfp.bin");
MODULE_FIRMWARE("radeon/RV630_me.bin");
MODULE_FIRMWARE("radeon/RV620_pfp.bin");
MODULE_FIRMWARE("radeon/RV620_me.bin");
MODULE_FIRMWARE("radeon/RV635_pfp.bin");
MODULE_FIRMWARE("radeon/RV635_me.bin");
MODULE_FIRMWARE("radeon/RV670_pfp.bin");
MODULE_FIRMWARE("radeon/RV670_me.bin");
MODULE_FIRMWARE("radeon/RS780_pfp.bin");
MODULE_FIRMWARE("radeon/RS780_me.bin");
MODULE_FIRMWARE("radeon/RV770_pfp.bin");
MODULE_FIRMWARE("radeon/RV770_me.bin");
MODULE_FIRMWARE("radeon/RV770_smc.bin");
MODULE_FIRMWARE("radeon/RV730_pfp.bin");
MODULE_FIRMWARE("radeon/RV730_me.bin");
MODULE_FIRMWARE("radeon/RV730_smc.bin");
MODULE_FIRMWARE("radeon/RV740_smc.bin");
MODULE_FIRMWARE("radeon/RV710_pfp.bin");
MODULE_FIRMWARE("radeon/RV710_me.bin");
MODULE_FIRMWARE("radeon/RV710_smc.bin");
MODULE_FIRMWARE("radeon/R600_rlc.bin");
MODULE_FIRMWARE("radeon/R700_rlc.bin");
MODULE_FIRMWARE("radeon/CEDAR_pfp.bin");
MODULE_FIRMWARE("radeon/CEDAR_me.bin");
MODULE_FIRMWARE("radeon/CEDAR_rlc.bin");
MODULE_FIRMWARE("radeon/CEDAR_smc.bin");
MODULE_FIRMWARE("radeon/REDWOOD_pfp.bin");
MODULE_FIRMWARE("radeon/REDWOOD_me.bin");
MODULE_FIRMWARE("radeon/REDWOOD_rlc.bin");
MODULE_FIRMWARE("radeon/REDWOOD_smc.bin");
MODULE_FIRMWARE("radeon/JUNIPER_pfp.bin");
MODULE_FIRMWARE("radeon/JUNIPER_me.bin");
MODULE_FIRMWARE("radeon/JUNIPER_rlc.bin");
MODULE_FIRMWARE("radeon/JUNIPER_smc.bin");
MODULE_FIRMWARE("radeon/CYPRESS_pfp.bin");
MODULE_FIRMWARE("radeon/CYPRESS_me.bin");
MODULE_FIRMWARE("radeon/CYPRESS_rlc.bin");
MODULE_FIRMWARE("radeon/CYPRESS_smc.bin");
MODULE_FIRMWARE("radeon/PALM_pfp.bin");
MODULE_FIRMWARE("radeon/PALM_me.bin");
MODULE_FIRMWARE("radeon/SUMO_rlc.bin");
MODULE_FIRMWARE("radeon/SUMO_pfp.bin");
MODULE_FIRMWARE("radeon/SUMO_me.bin");
MODULE_FIRMWARE("radeon/SUMO2_pfp.bin");
MODULE_FIRMWARE("radeon/SUMO2_me.bin");

अटल स्थिर u32 crtc_offsets[2] =
अणु
	0,
	AVIVO_D2CRTC_H_TOTAL - AVIVO_D1CRTC_H_TOTAL
पूर्ण;

अटल व्योम r600_debugfs_mc_info_init(काष्ठा radeon_device *rdev);

/* r600,rv610,rv630,rv620,rv635,rv670 */
पूर्णांक r600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
अटल व्योम r600_gpu_init(काष्ठा radeon_device *rdev);
व्योम r600_fini(काष्ठा radeon_device *rdev);
व्योम r600_irq_disable(काष्ठा radeon_device *rdev);
अटल व्योम r600_pcie_gen2_enable(काष्ठा radeon_device *rdev);

/*
 * Indirect रेजिस्टरs accessor
 */
u32 r600_rcu_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->rcu_idx_lock, flags);
	WREG32(R600_RCU_INDEX, ((reg) & 0x1fff));
	r = RREG32(R600_RCU_DATA);
	spin_unlock_irqrestore(&rdev->rcu_idx_lock, flags);
	वापस r;
पूर्ण

व्योम r600_rcu_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->rcu_idx_lock, flags);
	WREG32(R600_RCU_INDEX, ((reg) & 0x1fff));
	WREG32(R600_RCU_DATA, (v));
	spin_unlock_irqrestore(&rdev->rcu_idx_lock, flags);
पूर्ण

u32 r600_uvd_ctx_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->uvd_idx_lock, flags);
	WREG32(R600_UVD_CTX_INDEX, ((reg) & 0x1ff));
	r = RREG32(R600_UVD_CTX_DATA);
	spin_unlock_irqrestore(&rdev->uvd_idx_lock, flags);
	वापस r;
पूर्ण

व्योम r600_uvd_ctx_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->uvd_idx_lock, flags);
	WREG32(R600_UVD_CTX_INDEX, ((reg) & 0x1ff));
	WREG32(R600_UVD_CTX_DATA, (v));
	spin_unlock_irqrestore(&rdev->uvd_idx_lock, flags);
पूर्ण

/**
 * r600_get_allowed_info_रेजिस्टर - fetch the रेजिस्टर क्रम the info ioctl
 *
 * @rdev: radeon_device poपूर्णांकer
 * @reg: रेजिस्टर offset in bytes
 * @val: रेजिस्टर value
 *
 * Returns 0 क्रम success or -EINVAL क्रम an invalid रेजिस्टर
 *
 */
पूर्णांक r600_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				   u32 reg, u32 *val)
अणु
	चयन (reg) अणु
	हाल GRBM_STATUS:
	हाल GRBM_STATUS2:
	हाल R_000E50_SRBM_STATUS:
	हाल DMA_STATUS_REG:
	हाल UVD_STATUS:
		*val = RREG32(reg);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * r600_get_xclk - get the xclk
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Returns the reference घड़ी used by the gfx engine
 * (r6xx, IGPs, APUs).
 */
u32 r600_get_xclk(काष्ठा radeon_device *rdev)
अणु
	वापस rdev->घड़ी.spll.reference_freq;
पूर्ण

पूर्णांक r600_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk)
अणु
	अचिन्हित fb_भाग = 0, ref_भाग, vclk_भाग = 0, dclk_भाग = 0;
	पूर्णांक r;

	/* bypass vclk and dclk with bclk */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 VCLK_SRC_SEL(1) | DCLK_SRC_SEL(1),
		 ~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	/* निश्चित BYPASS_EN, deनिश्चित UPLL_RESET, UPLL_SLEEP and UPLL_CTLREQ */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_BYPASS_EN_MASK, ~(
		 UPLL_RESET_MASK | UPLL_SLEEP_MASK | UPLL_CTLREQ_MASK));

	अगर (rdev->family >= CHIP_RS780)
		WREG32_P(GFX_MACRO_BYPASS_CNTL, UPLL_BYPASS_CNTL,
			 ~UPLL_BYPASS_CNTL);

	अगर (!vclk || !dclk) अणु
		/* keep the Bypass mode, put PLL to sleep */
		WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_SLEEP_MASK, ~UPLL_SLEEP_MASK);
		वापस 0;
	पूर्ण

	अगर (rdev->घड़ी.spll.reference_freq == 10000)
		ref_भाग = 34;
	अन्यथा
		ref_भाग = 4;

	r = radeon_uvd_calc_upll_भागiders(rdev, vclk, dclk, 50000, 160000,
					  ref_भाग + 1, 0xFFF, 2, 30, ~0,
					  &fb_भाग, &vclk_भाग, &dclk_भाग);
	अगर (r)
		वापस r;

	अगर (rdev->family >= CHIP_RV670 && rdev->family < CHIP_RS780)
		fb_भाग >>= 1;
	अन्यथा
		fb_भाग |= 1;

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* निश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_RESET_MASK, ~UPLL_RESET_MASK);

	/* For RS780 we have to choose ref clk */
	अगर (rdev->family >= CHIP_RS780)
		WREG32_P(CG_UPLL_FUNC_CNTL, UPLL_REFCLK_SRC_SEL_MASK,
			 ~UPLL_REFCLK_SRC_SEL_MASK);

	/* set the required fb, ref and post भागder values */
	WREG32_P(CG_UPLL_FUNC_CNTL,
		 UPLL_FB_DIV(fb_भाग) |
		 UPLL_REF_DIV(ref_भाग),
		 ~(UPLL_FB_DIV_MASK | UPLL_REF_DIV_MASK));
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 UPLL_SW_HILEN(vclk_भाग >> 1) |
		 UPLL_SW_LOLEN((vclk_भाग >> 1) + (vclk_भाग & 1)) |
		 UPLL_SW_HILEN2(dclk_भाग >> 1) |
		 UPLL_SW_LOLEN2((dclk_भाग >> 1) + (dclk_भाग & 1)) |
		 UPLL_DIVEN_MASK | UPLL_DIVEN2_MASK,
		 ~UPLL_SW_MASK);

	/* give the PLL some समय to settle */
	mdelay(15);

	/* deनिश्चित PLL_RESET */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_RESET_MASK);

	mdelay(15);

	/* deनिश्चित BYPASS EN */
	WREG32_P(CG_UPLL_FUNC_CNTL, 0, ~UPLL_BYPASS_EN_MASK);

	अगर (rdev->family >= CHIP_RS780)
		WREG32_P(GFX_MACRO_BYPASS_CNTL, 0, ~UPLL_BYPASS_CNTL);

	r = radeon_uvd_send_upll_ctlreq(rdev, CG_UPLL_FUNC_CNTL);
	अगर (r)
		वापस r;

	/* चयन VCLK and DCLK selection */
	WREG32_P(CG_UPLL_FUNC_CNTL_2,
		 VCLK_SRC_SEL(2) | DCLK_SRC_SEL(2),
		 ~(VCLK_SRC_SEL_MASK | DCLK_SRC_SEL_MASK));

	mdelay(100);

	वापस 0;
पूर्ण

व्योम dce3_program_fmt(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	पूर्णांक bpc = 0;
	u32 पंचांगp = 0;
	क्रमागत radeon_connector_dither dither = RADEON_FMT_DITHER_DISABLE;

	अगर (connector) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		bpc = radeon_get_monitor_bpc(connector);
		dither = radeon_connector->dither;
	पूर्ण

	/* LVDS FMT is set up by atom */
	अगर (radeon_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		वापस;

	/* not needed क्रम analog */
	अगर ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1) ||
	    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2))
		वापस;

	अगर (bpc == 0)
		वापस;

	चयन (bpc) अणु
	हाल 6:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= FMT_SPATIAL_DITHER_EN;
		अन्यथा
			पंचांगp |= FMT_TRUNCATE_EN;
		अवरोध;
	हाल 8:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (FMT_SPATIAL_DITHER_EN | FMT_SPATIAL_DITHER_DEPTH);
		अन्यथा
			पंचांगp |= (FMT_TRUNCATE_EN | FMT_TRUNCATE_DEPTH);
		अवरोध;
	हाल 10:
	शेष:
		/* not needed */
		अवरोध;
	पूर्ण

	WREG32(FMT_BIT_DEPTH_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
पूर्ण

/* get temperature in millidegrees */
पूर्णांक rv6xx_get_temp(काष्ठा radeon_device *rdev)
अणु
	u32 temp = (RREG32(CG_THERMAL_STATUS) & ASIC_T_MASK) >>
		ASIC_T_SHIFT;
	पूर्णांक actual_temp = temp & 0xff;

	अगर (temp & 0x100)
		actual_temp -= 256;

	वापस actual_temp * 1000;
पूर्ण

व्योम r600_pm_get_dynpm_state(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	rdev->pm.dynpm_can_upघड़ी = true;
	rdev->pm.dynpm_can_करोwnघड़ी = true;

	/* घातer state array is low to high, शेष is first */
	अगर ((rdev->flags & RADEON_IS_IGP) || (rdev->family == CHIP_R600)) अणु
		पूर्णांक min_घातer_state_index = 0;

		अगर (rdev->pm.num_घातer_states > 2)
			min_घातer_state_index = 1;

		चयन (rdev->pm.dynpm_planned_action) अणु
		हाल DYNPM_ACTION_MINIMUM:
			rdev->pm.requested_घातer_state_index = min_घातer_state_index;
			rdev->pm.requested_घड़ी_mode_index = 0;
			rdev->pm.dynpm_can_करोwnघड़ी = false;
			अवरोध;
		हाल DYNPM_ACTION_DOWNCLOCK:
			अगर (rdev->pm.current_घातer_state_index == min_घातer_state_index) अणु
				rdev->pm.requested_घातer_state_index = rdev->pm.current_घातer_state_index;
				rdev->pm.dynpm_can_करोwnघड़ी = false;
			पूर्ण अन्यथा अणु
				अगर (rdev->pm.active_crtc_count > 1) अणु
					क्रम (i = 0; i < rdev->pm.num_घातer_states; i++) अणु
						अगर (rdev->pm.घातer_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
							जारी;
						अन्यथा अगर (i >= rdev->pm.current_घातer_state_index) अणु
							rdev->pm.requested_घातer_state_index =
								rdev->pm.current_घातer_state_index;
							अवरोध;
						पूर्ण अन्यथा अणु
							rdev->pm.requested_घातer_state_index = i;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (rdev->pm.current_घातer_state_index == 0)
						rdev->pm.requested_घातer_state_index =
							rdev->pm.num_घातer_states - 1;
					अन्यथा
						rdev->pm.requested_घातer_state_index =
							rdev->pm.current_घातer_state_index - 1;
				पूर्ण
			पूर्ण
			rdev->pm.requested_घड़ी_mode_index = 0;
			/* करोn't use the घातer state अगर crtcs are active and no display flag is set */
			अगर ((rdev->pm.active_crtc_count > 0) &&
			    (rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
			     घड़ी_info[rdev->pm.requested_घड़ी_mode_index].flags &
			     RADEON_PM_MODE_NO_DISPLAY)) अणु
				rdev->pm.requested_घातer_state_index++;
			पूर्ण
			अवरोध;
		हाल DYNPM_ACTION_UPCLOCK:
			अगर (rdev->pm.current_घातer_state_index == (rdev->pm.num_घातer_states - 1)) अणु
				rdev->pm.requested_घातer_state_index = rdev->pm.current_घातer_state_index;
				rdev->pm.dynpm_can_upघड़ी = false;
			पूर्ण अन्यथा अणु
				अगर (rdev->pm.active_crtc_count > 1) अणु
					क्रम (i = (rdev->pm.num_घातer_states - 1); i >= 0; i--) अणु
						अगर (rdev->pm.घातer_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
							जारी;
						अन्यथा अगर (i <= rdev->pm.current_घातer_state_index) अणु
							rdev->pm.requested_घातer_state_index =
								rdev->pm.current_घातer_state_index;
							अवरोध;
						पूर्ण अन्यथा अणु
							rdev->pm.requested_घातer_state_index = i;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण अन्यथा
					rdev->pm.requested_घातer_state_index =
						rdev->pm.current_घातer_state_index + 1;
			पूर्ण
			rdev->pm.requested_घड़ी_mode_index = 0;
			अवरोध;
		हाल DYNPM_ACTION_DEFAULT:
			rdev->pm.requested_घातer_state_index = rdev->pm.शेष_घातer_state_index;
			rdev->pm.requested_घड़ी_mode_index = 0;
			rdev->pm.dynpm_can_upघड़ी = false;
			अवरोध;
		हाल DYNPM_ACTION_NONE:
		शेष:
			DRM_ERROR("Requested mode for not defined action\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* XXX select a घातer state based on AC/DC, single/dualhead, etc. */
		/* क्रम now just select the first घातer state and चयन between घड़ी modes */
		/* घातer state array is low to high, शेष is first (0) */
		अगर (rdev->pm.active_crtc_count > 1) अणु
			rdev->pm.requested_घातer_state_index = -1;
			/* start at 1 as we करोn't want the शेष mode */
			क्रम (i = 1; i < rdev->pm.num_घातer_states; i++) अणु
				अगर (rdev->pm.घातer_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
					जारी;
				अन्यथा अगर ((rdev->pm.घातer_state[i].type == POWER_STATE_TYPE_PERFORMANCE) ||
					 (rdev->pm.घातer_state[i].type == POWER_STATE_TYPE_BATTERY)) अणु
					rdev->pm.requested_घातer_state_index = i;
					अवरोध;
				पूर्ण
			पूर्ण
			/* अगर nothing selected, grab the शेष state. */
			अगर (rdev->pm.requested_घातer_state_index == -1)
				rdev->pm.requested_घातer_state_index = 0;
		पूर्ण अन्यथा
			rdev->pm.requested_घातer_state_index = 1;

		चयन (rdev->pm.dynpm_planned_action) अणु
		हाल DYNPM_ACTION_MINIMUM:
			rdev->pm.requested_घड़ी_mode_index = 0;
			rdev->pm.dynpm_can_करोwnघड़ी = false;
			अवरोध;
		हाल DYNPM_ACTION_DOWNCLOCK:
			अगर (rdev->pm.requested_घातer_state_index == rdev->pm.current_घातer_state_index) अणु
				अगर (rdev->pm.current_घड़ी_mode_index == 0) अणु
					rdev->pm.requested_घड़ी_mode_index = 0;
					rdev->pm.dynpm_can_करोwnघड़ी = false;
				पूर्ण अन्यथा
					rdev->pm.requested_घड़ी_mode_index =
						rdev->pm.current_घड़ी_mode_index - 1;
			पूर्ण अन्यथा अणु
				rdev->pm.requested_घड़ी_mode_index = 0;
				rdev->pm.dynpm_can_करोwnघड़ी = false;
			पूर्ण
			/* करोn't use the घातer state अगर crtcs are active and no display flag is set */
			अगर ((rdev->pm.active_crtc_count > 0) &&
			    (rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
			     घड़ी_info[rdev->pm.requested_घड़ी_mode_index].flags &
			     RADEON_PM_MODE_NO_DISPLAY)) अणु
				rdev->pm.requested_घड़ी_mode_index++;
			पूर्ण
			अवरोध;
		हाल DYNPM_ACTION_UPCLOCK:
			अगर (rdev->pm.requested_घातer_state_index == rdev->pm.current_घातer_state_index) अणु
				अगर (rdev->pm.current_घड़ी_mode_index ==
				    (rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].num_घड़ी_modes - 1)) अणु
					rdev->pm.requested_घड़ी_mode_index = rdev->pm.current_घड़ी_mode_index;
					rdev->pm.dynpm_can_upघड़ी = false;
				पूर्ण अन्यथा
					rdev->pm.requested_घड़ी_mode_index =
						rdev->pm.current_घड़ी_mode_index + 1;
			पूर्ण अन्यथा अणु
				rdev->pm.requested_घड़ी_mode_index =
					rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].num_घड़ी_modes - 1;
				rdev->pm.dynpm_can_upघड़ी = false;
			पूर्ण
			अवरोध;
		हाल DYNPM_ACTION_DEFAULT:
			rdev->pm.requested_घातer_state_index = rdev->pm.शेष_घातer_state_index;
			rdev->pm.requested_घड़ी_mode_index = 0;
			rdev->pm.dynpm_can_upघड़ी = false;
			अवरोध;
		हाल DYNPM_ACTION_NONE:
		शेष:
			DRM_ERROR("Requested mode for not defined action\n");
			वापस;
		पूर्ण
	पूर्ण

	DRM_DEBUG_DRIVER("Requested: e: %d m: %d p: %d\n",
		  rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
		  घड़ी_info[rdev->pm.requested_घड़ी_mode_index].sclk,
		  rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
		  घड़ी_info[rdev->pm.requested_घड़ी_mode_index].mclk,
		  rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
		  pcie_lanes);
पूर्ण

व्योम rs780_pm_init_profile(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.num_घातer_states == 2) अणु
		/* शेष */
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 0;
		/* low sh */
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* low mh */
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	पूर्ण अन्यथा अगर (rdev->pm.num_घातer_states == 3) अणु
		/* शेष */
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 0;
		/* low sh */
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* low mh */
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = 1;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	पूर्ण अन्यथा अणु
		/* शेष */
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 0;
		/* low sh */
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = 3;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* low mh */
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = 2;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = 3;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	पूर्ण
पूर्ण

व्योम r600_pm_init_profile(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक idx;

	अगर (rdev->family == CHIP_R600) अणु
		/* XXX */
		/* शेष */
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 0;
		/* low sh */
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* low mh */
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	पूर्ण अन्यथा अणु
		अगर (rdev->pm.num_घातer_states < 4) अणु
			/* शेष */
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 2;
			/* low sh */
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = 1;
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = 1;
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
			/* mid sh */
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = 1;
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = 1;
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 1;
			/* high sh */
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = 1;
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = 1;
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 2;
			/* low mh */
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = 2;
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = 2;
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
			/* low mh */
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = 2;
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = 2;
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 1;
			/* high mh */
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = 2;
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = 2;
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 2;
		पूर्ण अन्यथा अणु
			/* शेष */
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 2;
			/* low sh */
			अगर (rdev->flags & RADEON_IS_MOBILITY)
				idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_BATTERY, 0);
			अन्यथा
				idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
			/* mid sh */
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 1;
			/* high sh */
			idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 0);
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 2;
			/* low mh */
			अगर (rdev->flags & RADEON_IS_MOBILITY)
				idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_BATTERY, 1);
			अन्यथा
				idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 1);
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
			/* mid mh */
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 1;
			/* high mh */
			idx = radeon_pm_get_type_index(rdev, POWER_STATE_TYPE_PERFORMANCE, 1);
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = idx;
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
			rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 2;
		पूर्ण
	पूर्ण
पूर्ण

व्योम r600_pm_misc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक req_ps_idx = rdev->pm.requested_घातer_state_index;
	पूर्णांक req_cm_idx = rdev->pm.requested_घड़ी_mode_index;
	काष्ठा radeon_घातer_state *ps = &rdev->pm.घातer_state[req_ps_idx];
	काष्ठा radeon_voltage *voltage = &ps->घड़ी_info[req_cm_idx].voltage;

	अगर ((voltage->type == VOLTAGE_SW) && voltage->voltage) अणु
		/* 0xff01 is a flag rather then an actual voltage */
		अगर (voltage->voltage == 0xff01)
			वापस;
		अगर (voltage->voltage != rdev->pm.current_vddc) अणु
			radeon_atom_set_voltage(rdev, voltage->voltage, SET_VOLTAGE_TYPE_ASIC_VDDC);
			rdev->pm.current_vddc = voltage->voltage;
			DRM_DEBUG_DRIVER("Setting: v: %d\n", voltage->voltage);
		पूर्ण
	पूर्ण
पूर्ण

bool r600_gui_idle(काष्ठा radeon_device *rdev)
अणु
	अगर (RREG32(GRBM_STATUS) & GUI_ACTIVE)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

/* hpd क्रम digital panel detect/disconnect */
bool r600_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd)
अणु
	bool connected = false;

	अगर (ASIC_IS_DCE3(rdev)) अणु
		चयन (hpd) अणु
		हाल RADEON_HPD_1:
			अगर (RREG32(DC_HPD1_INT_STATUS) & DC_HPDx_SENSE)
				connected = true;
			अवरोध;
		हाल RADEON_HPD_2:
			अगर (RREG32(DC_HPD2_INT_STATUS) & DC_HPDx_SENSE)
				connected = true;
			अवरोध;
		हाल RADEON_HPD_3:
			अगर (RREG32(DC_HPD3_INT_STATUS) & DC_HPDx_SENSE)
				connected = true;
			अवरोध;
		हाल RADEON_HPD_4:
			अगर (RREG32(DC_HPD4_INT_STATUS) & DC_HPDx_SENSE)
				connected = true;
			अवरोध;
			/* DCE 3.2 */
		हाल RADEON_HPD_5:
			अगर (RREG32(DC_HPD5_INT_STATUS) & DC_HPDx_SENSE)
				connected = true;
			अवरोध;
		हाल RADEON_HPD_6:
			अगर (RREG32(DC_HPD6_INT_STATUS) & DC_HPDx_SENSE)
				connected = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (hpd) अणु
		हाल RADEON_HPD_1:
			अगर (RREG32(DC_HOT_PLUG_DETECT1_INT_STATUS) & DC_HOT_PLUG_DETECTx_SENSE)
				connected = true;
			अवरोध;
		हाल RADEON_HPD_2:
			अगर (RREG32(DC_HOT_PLUG_DETECT2_INT_STATUS) & DC_HOT_PLUG_DETECTx_SENSE)
				connected = true;
			अवरोध;
		हाल RADEON_HPD_3:
			अगर (RREG32(DC_HOT_PLUG_DETECT3_INT_STATUS) & DC_HOT_PLUG_DETECTx_SENSE)
				connected = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस connected;
पूर्ण

व्योम r600_hpd_set_polarity(काष्ठा radeon_device *rdev,
			   क्रमागत radeon_hpd_id hpd)
अणु
	u32 पंचांगp;
	bool connected = r600_hpd_sense(rdev, hpd);

	अगर (ASIC_IS_DCE3(rdev)) अणु
		चयन (hpd) अणु
		हाल RADEON_HPD_1:
			पंचांगp = RREG32(DC_HPD1_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HPDx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD1_INT_CONTROL, पंचांगp);
			अवरोध;
		हाल RADEON_HPD_2:
			पंचांगp = RREG32(DC_HPD2_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HPDx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD2_INT_CONTROL, पंचांगp);
			अवरोध;
		हाल RADEON_HPD_3:
			पंचांगp = RREG32(DC_HPD3_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HPDx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD3_INT_CONTROL, पंचांगp);
			अवरोध;
		हाल RADEON_HPD_4:
			पंचांगp = RREG32(DC_HPD4_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HPDx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD4_INT_CONTROL, पंचांगp);
			अवरोध;
		हाल RADEON_HPD_5:
			पंचांगp = RREG32(DC_HPD5_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HPDx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD5_INT_CONTROL, पंचांगp);
			अवरोध;
			/* DCE 3.2 */
		हाल RADEON_HPD_6:
			पंचांगp = RREG32(DC_HPD6_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HPDx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD6_INT_CONTROL, पंचांगp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (hpd) अणु
		हाल RADEON_HPD_1:
			पंचांगp = RREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HOT_PLUG_DETECTx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HOT_PLUG_DETECTx_INT_POLARITY;
			WREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL, पंचांगp);
			अवरोध;
		हाल RADEON_HPD_2:
			पंचांगp = RREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HOT_PLUG_DETECTx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HOT_PLUG_DETECTx_INT_POLARITY;
			WREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL, पंचांगp);
			अवरोध;
		हाल RADEON_HPD_3:
			पंचांगp = RREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL);
			अगर (connected)
				पंचांगp &= ~DC_HOT_PLUG_DETECTx_INT_POLARITY;
			अन्यथा
				पंचांगp |= DC_HOT_PLUG_DETECTx_INT_POLARITY;
			WREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL, पंचांगp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम r600_hpd_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित enable = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP ||
		    connector->connector_type == DRM_MODE_CONNECTOR_LVDS) अणु
			/* करोn't try to enable hpd on eDP or LVDS aव्योम अवरोधing the
			 * aux dp channel on imac and help (but not completely fix)
			 * https://bugzilla.redhat.com/show_bug.cgi?id=726143
			 */
			जारी;
		पूर्ण
		अगर (ASIC_IS_DCE3(rdev)) अणु
			u32 पंचांगp = DC_HPDx_CONNECTION_TIMER(0x9c4) | DC_HPDx_RX_INT_TIMER(0xfa);
			अगर (ASIC_IS_DCE32(rdev))
				पंचांगp |= DC_HPDx_EN;

			चयन (radeon_connector->hpd.hpd) अणु
			हाल RADEON_HPD_1:
				WREG32(DC_HPD1_CONTROL, पंचांगp);
				अवरोध;
			हाल RADEON_HPD_2:
				WREG32(DC_HPD2_CONTROL, पंचांगp);
				अवरोध;
			हाल RADEON_HPD_3:
				WREG32(DC_HPD3_CONTROL, पंचांगp);
				अवरोध;
			हाल RADEON_HPD_4:
				WREG32(DC_HPD4_CONTROL, पंचांगp);
				अवरोध;
				/* DCE 3.2 */
			हाल RADEON_HPD_5:
				WREG32(DC_HPD5_CONTROL, पंचांगp);
				अवरोध;
			हाल RADEON_HPD_6:
				WREG32(DC_HPD6_CONTROL, पंचांगp);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (radeon_connector->hpd.hpd) अणु
			हाल RADEON_HPD_1:
				WREG32(DC_HOT_PLUG_DETECT1_CONTROL, DC_HOT_PLUG_DETECTx_EN);
				अवरोध;
			हाल RADEON_HPD_2:
				WREG32(DC_HOT_PLUG_DETECT2_CONTROL, DC_HOT_PLUG_DETECTx_EN);
				अवरोध;
			हाल RADEON_HPD_3:
				WREG32(DC_HOT_PLUG_DETECT3_CONTROL, DC_HOT_PLUG_DETECTx_EN);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			enable |= 1 << radeon_connector->hpd.hpd;
		radeon_hpd_set_polarity(rdev, radeon_connector->hpd.hpd);
	पूर्ण
	radeon_irq_kms_enable_hpd(rdev, enable);
पूर्ण

व्योम r600_hpd_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित disable = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		अगर (ASIC_IS_DCE3(rdev)) अणु
			चयन (radeon_connector->hpd.hpd) अणु
			हाल RADEON_HPD_1:
				WREG32(DC_HPD1_CONTROL, 0);
				अवरोध;
			हाल RADEON_HPD_2:
				WREG32(DC_HPD2_CONTROL, 0);
				अवरोध;
			हाल RADEON_HPD_3:
				WREG32(DC_HPD3_CONTROL, 0);
				अवरोध;
			हाल RADEON_HPD_4:
				WREG32(DC_HPD4_CONTROL, 0);
				अवरोध;
				/* DCE 3.2 */
			हाल RADEON_HPD_5:
				WREG32(DC_HPD5_CONTROL, 0);
				अवरोध;
			हाल RADEON_HPD_6:
				WREG32(DC_HPD6_CONTROL, 0);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (radeon_connector->hpd.hpd) अणु
			हाल RADEON_HPD_1:
				WREG32(DC_HOT_PLUG_DETECT1_CONTROL, 0);
				अवरोध;
			हाल RADEON_HPD_2:
				WREG32(DC_HOT_PLUG_DETECT2_CONTROL, 0);
				अवरोध;
			हाल RADEON_HPD_3:
				WREG32(DC_HOT_PLUG_DETECT3_CONTROL, 0);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			disable |= 1 << radeon_connector->hpd.hpd;
	पूर्ण
	radeon_irq_kms_disable_hpd(rdev, disable);
पूर्ण

/*
 * R600 PCIE GART
 */
व्योम r600_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	u32 पंचांगp;

	/* flush hdp cache so updates hit vram */
	अगर ((rdev->family >= CHIP_RV770) && (rdev->family <= CHIP_RV740) &&
	    !(rdev->flags & RADEON_IS_AGP)) अणु
		व्योम __iomem *ptr = (व्योम *)rdev->gart.ptr;

		/* r7xx hw bug.  ग_लिखो to HDP_DEBUG1 followed by fb पढ़ो
		 * rather than ग_लिखो to HDP_REG_COHERENCY_FLUSH_CNTL
		 * This seems to cause problems on some AGP cards. Just use the old
		 * method क्रम them.
		 */
		WREG32(HDP_DEBUG1, 0);
		पढ़ोl((व्योम __iomem *)ptr);
	पूर्ण अन्यथा
		WREG32(R_005480_HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);

	WREG32(VM_CONTEXT0_INVALIDATION_LOW_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_INVALIDATION_HIGH_ADDR, (rdev->mc.gtt_end - 1) >> 12);
	WREG32(VM_CONTEXT0_REQUEST_RESPONSE, REQUEST_TYPE(1));
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(VM_CONTEXT0_REQUEST_RESPONSE);
		पंचांगp = (पंचांगp & RESPONSE_TYPE_MASK) >> RESPONSE_TYPE_SHIFT;
		अगर (पंचांगp == 2) अणु
			pr_warn("[drm] r600 flush TLB failed\n");
			वापस;
		पूर्ण
		अगर (पंचांगp) अणु
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण
पूर्ण

पूर्णांक r600_pcie_gart_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.robj) अणु
		WARN(1, "R600 PCIE GART already initialized\n");
		वापस 0;
	पूर्ण
	/* Initialize common gart काष्ठाure */
	r = radeon_gart_init(rdev);
	अगर (r)
		वापस r;
	rdev->gart.table_size = rdev->gart.num_gpu_pages * 8;
	वापस radeon_gart_table_vram_alloc(rdev);
पूर्ण

अटल पूर्णांक r600_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक r, i;

	अगर (rdev->gart.robj == शून्य) अणु
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_gart_table_vram_pin(rdev);
	अगर (r)
		वापस r;

	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE | ENABLE_L2_FRAGMENT_PROCESSING |
				ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT_0(0) | BANK_SELECT_1(1));
	/* Setup TLB control */
	पंचांगp = ENABLE_L1_TLB | ENABLE_L1_FRAGMENT_PROCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5) |
		ENABLE_WAIT_L2_QUERY;
	WREG32(MC_VM_L1_TLB_MCB_RD_SYS_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_SYS_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_HDP_CNTL, पंचांगp | ENABLE_L1_STRICT_ORDERING);
	WREG32(MC_VM_L1_TLB_MCB_WR_HDP_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_RD_A_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_WR_A_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_RD_B_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_WR_B_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_GFX_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_GFX_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_PDMA_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_PDMA_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_UVD_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_UVD_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_SEM_CNTL, पंचांगp | ENABLE_SEMAPHORE_MODE);
	WREG32(MC_VM_L1_TLB_MCB_WR_SEM_CNTL, पंचांगp | ENABLE_SEMAPHORE_MODE);
	WREG32(VM_CONTEXT0_PAGE_TABLE_START_ADDR, rdev->mc.gtt_start >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_END_ADDR, rdev->mc.gtt_end >> 12);
	WREG32(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR, rdev->gart.table_addr >> 12);
	WREG32(VM_CONTEXT0_CNTL, ENABLE_CONTEXT | PAGE_TABLE_DEPTH(0) |
				RANGE_PROTECTION_FAULT_ENABLE_DEFAULT);
	WREG32(VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR,
			(u32)(rdev->dummy_page.addr >> 12));
	क्रम (i = 1; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);

	r600_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल व्योम r600_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	/* Disable all tables */
	क्रम (i = 0; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);

	/* Disable L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL3, BANK_SELECT_0(0) | BANK_SELECT_1(1));
	/* Setup L1 TLB control */
	पंचांगp = EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5) |
		ENABLE_WAIT_L2_QUERY;
	WREG32(MC_VM_L1_TLB_MCD_RD_A_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_WR_A_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_RD_B_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_WR_B_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_GFX_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_GFX_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_PDMA_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_PDMA_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_SEM_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_SEM_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_SYS_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_SYS_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_HDP_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_HDP_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_UVD_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_UVD_CNTL, पंचांगp);
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

अटल व्योम r600_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_gart_fini(rdev);
	r600_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
पूर्ण

अटल व्योम r600_agp_enable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	/* Setup L2 cache */
	WREG32(VM_L2_CNTL, ENABLE_L2_CACHE | ENABLE_L2_FRAGMENT_PROCESSING |
				ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE |
				EFFECTIVE_L2_QUEUE_SIZE(7));
	WREG32(VM_L2_CNTL2, 0);
	WREG32(VM_L2_CNTL3, BANK_SELECT_0(0) | BANK_SELECT_1(1));
	/* Setup TLB control */
	पंचांगp = ENABLE_L1_TLB | ENABLE_L1_FRAGMENT_PROCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		EFFECTIVE_L1_TLB_SIZE(5) | EFFECTIVE_L1_QUEUE_SIZE(5) |
		ENABLE_WAIT_L2_QUERY;
	WREG32(MC_VM_L1_TLB_MCB_RD_SYS_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_SYS_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_HDP_CNTL, पंचांगp | ENABLE_L1_STRICT_ORDERING);
	WREG32(MC_VM_L1_TLB_MCB_WR_HDP_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_RD_A_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_WR_A_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_RD_B_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCD_WR_B_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_GFX_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_GFX_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_PDMA_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_WR_PDMA_CNTL, पंचांगp);
	WREG32(MC_VM_L1_TLB_MCB_RD_SEM_CNTL, पंचांगp | ENABLE_SEMAPHORE_MODE);
	WREG32(MC_VM_L1_TLB_MCB_WR_SEM_CNTL, पंचांगp | ENABLE_SEMAPHORE_MODE);
	क्रम (i = 0; i < 7; i++)
		WREG32(VM_CONTEXT0_CNTL + (i * 4), 0);
पूर्ण

पूर्णांक r600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	u32 पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(R_000E50_SRBM_STATUS) & 0x3F00;
		अगर (!पंचांगp)
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

uपूर्णांक32_t rs780_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_0028F8_MC_INDEX, S_0028F8_MC_IND_ADDR(reg));
	r = RREG32(R_0028FC_MC_DATA);
	WREG32(R_0028F8_MC_INDEX, ~C_0028F8_MC_IND_ADDR);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
	वापस r;
पूर्ण

व्योम rs780_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_0028F8_MC_INDEX, S_0028F8_MC_IND_ADDR(reg) |
		S_0028F8_MC_IND_WR_EN(1));
	WREG32(R_0028FC_MC_DATA, v);
	WREG32(R_0028F8_MC_INDEX, 0x7F);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
पूर्ण

अटल व्योम r600_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;
	u32 पंचांगp;
	पूर्णांक i, j;

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x18) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	पूर्ण
	WREG32(HDP_REG_COHERENCY_FLUSH_CNTL, 0);

	rv515_mc_stop(rdev, &save);
	अगर (r600_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	/* Lockout access through VGA aperture (करोesn't exist beक्रमe R600) */
	WREG32(VGA_HDP_CONTROL, VGA_MEMORY_DISABLE);
	/* Update configuration */
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		अगर (rdev->mc.vram_start < rdev->mc.gtt_start) अणु
			/* VRAM beक्रमe AGP */
			WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
				rdev->mc.vram_start >> 12);
			WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
				rdev->mc.gtt_end >> 12);
		पूर्ण अन्यथा अणु
			/* VRAM after AGP */
			WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
				rdev->mc.gtt_start >> 12);
			WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
				rdev->mc.vram_end >> 12);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(MC_VM_SYSTEM_APERTURE_LOW_ADDR, rdev->mc.vram_start >> 12);
		WREG32(MC_VM_SYSTEM_APERTURE_HIGH_ADDR, rdev->mc.vram_end >> 12);
	पूर्ण
	WREG32(MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR, rdev->vram_scratch.gpu_addr >> 12);
	पंचांगp = ((rdev->mc.vram_end >> 24) & 0xFFFF) << 16;
	पंचांगp |= ((rdev->mc.vram_start >> 24) & 0xFFFF);
	WREG32(MC_VM_FB_LOCATION, पंचांगp);
	WREG32(HDP_NONSURFACE_BASE, (rdev->mc.vram_start >> 8));
	WREG32(HDP_NONSURFACE_INFO, (2 << 7));
	WREG32(HDP_NONSURFACE_SIZE, 0x3FFFFFFF);
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		WREG32(MC_VM_AGP_TOP, rdev->mc.gtt_end >> 22);
		WREG32(MC_VM_AGP_BOT, rdev->mc.gtt_start >> 22);
		WREG32(MC_VM_AGP_BASE, rdev->mc.agp_base >> 22);
	पूर्ण अन्यथा अणु
		WREG32(MC_VM_AGP_BASE, 0);
		WREG32(MC_VM_AGP_TOP, 0x0FFFFFFF);
		WREG32(MC_VM_AGP_BOT, 0x0FFFFFFF);
	पूर्ण
	अगर (r600_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण
	rv515_mc_resume(rdev, &save);
	/* we need to own VRAM, so turn off the VGA renderer here
	 * to stop it overwriting our objects */
	rv515_vga_render_disable(rdev);
पूर्ण

/**
 * r600_vram_gtt_location - try to find VRAM & GTT location
 * @rdev: radeon device काष्ठाure holding all necessary inक्रमmations
 * @mc: memory controller काष्ठाure holding memory inक्रमmations
 *
 * Function will place try to place VRAM at same place as in CPU (PCI)
 * address space as some GPU seems to have issue when we reprogram at
 * dअगरferent address space.
 *
 * If there is not enough space to fit the unvisible VRAM after the
 * aperture then we limit the VRAM size to the aperture.
 *
 * If we are using AGP then place VRAM adjacent to AGP aperture are we need
 * them to be in one from GPU poपूर्णांक of view so that we can program GPU to
 * catch access outside them (weird GPU policy see ??).
 *
 * This function will never fails, worst हाल are limiting VRAM or GTT.
 *
 * Note: GTT start, end, size should be initialized beक्रमe calling this
 * function on AGP platक्रमm.
 */
अटल व्योम r600_vram_gtt_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc)
अणु
	u64 size_bf, size_af;

	अगर (mc->mc_vram_size > 0xE0000000) अणु
		/* leave room क्रम at least 512M GTT */
		dev_warn(rdev->dev, "limiting VRAM\n");
		mc->real_vram_size = 0xE0000000;
		mc->mc_vram_size = 0xE0000000;
	पूर्ण
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		size_bf = mc->gtt_start;
		size_af = mc->mc_mask - mc->gtt_end;
		अगर (size_bf > size_af) अणु
			अगर (mc->mc_vram_size > size_bf) अणु
				dev_warn(rdev->dev, "limiting VRAM\n");
				mc->real_vram_size = size_bf;
				mc->mc_vram_size = size_bf;
			पूर्ण
			mc->vram_start = mc->gtt_start - mc->mc_vram_size;
		पूर्ण अन्यथा अणु
			अगर (mc->mc_vram_size > size_af) अणु
				dev_warn(rdev->dev, "limiting VRAM\n");
				mc->real_vram_size = size_af;
				mc->mc_vram_size = size_af;
			पूर्ण
			mc->vram_start = mc->gtt_end + 1;
		पूर्ण
		mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
		dev_info(rdev->dev, "VRAM: %lluM 0x%08llX - 0x%08llX (%lluM used)\n",
				mc->mc_vram_size >> 20, mc->vram_start,
				mc->vram_end, mc->real_vram_size >> 20);
	पूर्ण अन्यथा अणु
		u64 base = 0;
		अगर (rdev->flags & RADEON_IS_IGP) अणु
			base = RREG32(MC_VM_FB_LOCATION) & 0xFFFF;
			base <<= 24;
		पूर्ण
		radeon_vram_location(rdev, &rdev->mc, base);
		rdev->mc.gtt_base_align = 0;
		radeon_gtt_location(rdev, mc);
	पूर्ण
पूर्ण

अटल पूर्णांक r600_mc_init(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक chansize, numchan;
	uपूर्णांक32_t h_addr, l_addr;
	अचिन्हित दीर्घ दीर्घ k8_addr;

	/* Get VRAM inक्रमmations */
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32(RAMCFG);
	अगर (पंचांगp & CHANSIZE_OVERRIDE) अणु
		chansize = 16;
	पूर्ण अन्यथा अगर (पंचांगp & CHANSIZE_MASK) अणु
		chansize = 64;
	पूर्ण अन्यथा अणु
		chansize = 32;
	पूर्ण
	पंचांगp = RREG32(CHMAP);
	चयन ((पंचांगp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) अणु
	हाल 0:
	शेष:
		numchan = 1;
		अवरोध;
	हाल 1:
		numchan = 2;
		अवरोध;
	हाल 2:
		numchan = 4;
		अवरोध;
	हाल 3:
		numchan = 8;
		अवरोध;
	पूर्ण
	rdev->mc.vram_width = numchan * chansize;
	/* Could aper size report 0 ? */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	/* Setup GPU memory space */
	rdev->mc.mc_vram_size = RREG32(CONFIG_MEMSIZE);
	rdev->mc.real_vram_size = RREG32(CONFIG_MEMSIZE);
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	r600_vram_gtt_location(rdev, &rdev->mc);

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		rs690_pm_info(rdev);
		rdev->mc.igp_sideport_enabled = radeon_atombios_sideport_present(rdev);

		अगर (rdev->family == CHIP_RS780 || rdev->family == CHIP_RS880) अणु
			/* Use K8 direct mapping क्रम fast fb access. */
			rdev->fastfb_working = false;
			h_addr = G_000012_K8_ADDR_EXT(RREG32_MC(R_000012_MC_MISC_UMA_CNTL));
			l_addr = RREG32_MC(R_000011_K8_FB_LOCATION);
			k8_addr = ((अचिन्हित दीर्घ दीर्घ)h_addr) << 32 | l_addr;
#अगर defined(CONFIG_X86_32) && !defined(CONFIG_X86_PAE)
			अगर (k8_addr + rdev->mc.visible_vram_size < 0x100000000ULL)
#पूर्ण_अगर
			अणु
				/* FastFB shall be used with UMA memory. Here it is simply disabled when sideport
		 		* memory is present.
		 		*/
				अगर (rdev->mc.igp_sideport_enabled == false && radeon_fastfb == 1) अणु
					DRM_INFO("Direct mapping: aper base at 0x%llx, replaced by direct mapping base 0x%llx.\n",
						(अचिन्हित दीर्घ दीर्घ)rdev->mc.aper_base, k8_addr);
					rdev->mc.aper_base = (resource_माप_प्रकार)k8_addr;
					rdev->fastfb_working = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	radeon_update_bandwidth_info(rdev);
	वापस 0;
पूर्ण

पूर्णांक r600_vram_scratch_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->vram_scratch.robj == शून्य) अणु
		r = radeon_bo_create(rdev, RADEON_GPU_PAGE_SIZE,
				     PAGE_SIZE, true, RADEON_GEM_DOMAIN_VRAM,
				     0, शून्य, शून्य, &rdev->vram_scratch.robj);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण

	r = radeon_bo_reserve(rdev->vram_scratch.robj, false);
	अगर (unlikely(r != 0))
		वापस r;
	r = radeon_bo_pin(rdev->vram_scratch.robj,
			  RADEON_GEM_DOMAIN_VRAM, &rdev->vram_scratch.gpu_addr);
	अगर (r) अणु
		radeon_bo_unreserve(rdev->vram_scratch.robj);
		वापस r;
	पूर्ण
	r = radeon_bo_kmap(rdev->vram_scratch.robj,
				(व्योम **)&rdev->vram_scratch.ptr);
	अगर (r)
		radeon_bo_unpin(rdev->vram_scratch.robj);
	radeon_bo_unreserve(rdev->vram_scratch.robj);

	वापस r;
पूर्ण

व्योम r600_vram_scratch_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->vram_scratch.robj == शून्य) अणु
		वापस;
	पूर्ण
	r = radeon_bo_reserve(rdev->vram_scratch.robj, false);
	अगर (likely(r == 0)) अणु
		radeon_bo_kunmap(rdev->vram_scratch.robj);
		radeon_bo_unpin(rdev->vram_scratch.robj);
		radeon_bo_unreserve(rdev->vram_scratch.robj);
	पूर्ण
	radeon_bo_unref(&rdev->vram_scratch.robj);
पूर्ण

व्योम r600_set_bios_scratch_engine_hung(काष्ठा radeon_device *rdev, bool hung)
अणु
	u32 पंचांगp = RREG32(R600_BIOS_3_SCRATCH);

	अगर (hung)
		पंचांगp |= ATOM_S3_ASIC_GUI_ENGINE_HUNG;
	अन्यथा
		पंचांगp &= ~ATOM_S3_ASIC_GUI_ENGINE_HUNG;

	WREG32(R600_BIOS_3_SCRATCH, पंचांगp);
पूर्ण

अटल व्योम r600_prपूर्णांक_gpu_status_regs(काष्ठा radeon_device *rdev)
अणु
	dev_info(rdev->dev, "  R_008010_GRBM_STATUS      = 0x%08X\n",
		 RREG32(R_008010_GRBM_STATUS));
	dev_info(rdev->dev, "  R_008014_GRBM_STATUS2     = 0x%08X\n",
		 RREG32(R_008014_GRBM_STATUS2));
	dev_info(rdev->dev, "  R_000E50_SRBM_STATUS      = 0x%08X\n",
		 RREG32(R_000E50_SRBM_STATUS));
	dev_info(rdev->dev, "  R_008674_CP_STALLED_STAT1 = 0x%08X\n",
		 RREG32(CP_STALLED_STAT1));
	dev_info(rdev->dev, "  R_008678_CP_STALLED_STAT2 = 0x%08X\n",
		 RREG32(CP_STALLED_STAT2));
	dev_info(rdev->dev, "  R_00867C_CP_BUSY_STAT     = 0x%08X\n",
		 RREG32(CP_BUSY_STAT));
	dev_info(rdev->dev, "  R_008680_CP_STAT          = 0x%08X\n",
		 RREG32(CP_STAT));
	dev_info(rdev->dev, "  R_00D034_DMA_STATUS_REG   = 0x%08X\n",
		RREG32(DMA_STATUS_REG));
पूर्ण

अटल bool r600_is_display_hung(काष्ठा radeon_device *rdev)
अणु
	u32 crtc_hung = 0;
	u32 crtc_status[2];
	u32 i, j, पंचांगp;

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]) & AVIVO_CRTC_EN) अणु
			crtc_status[i] = RREG32(AVIVO_D1CRTC_STATUS_HV_COUNT + crtc_offsets[i]);
			crtc_hung |= (1 << i);
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < 10; j++) अणु
		क्रम (i = 0; i < rdev->num_crtc; i++) अणु
			अगर (crtc_hung & (1 << i)) अणु
				पंचांगp = RREG32(AVIVO_D1CRTC_STATUS_HV_COUNT + crtc_offsets[i]);
				अगर (पंचांगp != crtc_status[i])
					crtc_hung &= ~(1 << i);
			पूर्ण
		पूर्ण
		अगर (crtc_hung == 0)
			वापस false;
		udelay(100);
	पूर्ण

	वापस true;
पूर्ण

u32 r600_gpu_check_soft_reset(काष्ठा radeon_device *rdev)
अणु
	u32 reset_mask = 0;
	u32 पंचांगp;

	/* GRBM_STATUS */
	पंचांगp = RREG32(R_008010_GRBM_STATUS);
	अगर (rdev->family >= CHIP_RV770) अणु
		अगर (G_008010_PA_BUSY(पंचांगp) | G_008010_SC_BUSY(पंचांगp) |
		    G_008010_SH_BUSY(पंचांगp) | G_008010_SX_BUSY(पंचांगp) |
		    G_008010_TA_BUSY(पंचांगp) | G_008010_VGT_BUSY(पंचांगp) |
		    G_008010_DB03_BUSY(पंचांगp) | G_008010_CB03_BUSY(पंचांगp) |
		    G_008010_SPI03_BUSY(पंचांगp) | G_008010_VGT_BUSY_NO_DMA(पंचांगp))
			reset_mask |= RADEON_RESET_GFX;
	पूर्ण अन्यथा अणु
		अगर (G_008010_PA_BUSY(पंचांगp) | G_008010_SC_BUSY(पंचांगp) |
		    G_008010_SH_BUSY(पंचांगp) | G_008010_SX_BUSY(पंचांगp) |
		    G_008010_TA03_BUSY(पंचांगp) | G_008010_VGT_BUSY(पंचांगp) |
		    G_008010_DB03_BUSY(पंचांगp) | G_008010_CB03_BUSY(पंचांगp) |
		    G_008010_SPI03_BUSY(पंचांगp) | G_008010_VGT_BUSY_NO_DMA(पंचांगp))
			reset_mask |= RADEON_RESET_GFX;
	पूर्ण

	अगर (G_008010_CF_RQ_PENDING(पंचांगp) | G_008010_PF_RQ_PENDING(पंचांगp) |
	    G_008010_CP_BUSY(पंचांगp) | G_008010_CP_COHERENCY_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_CP;

	अगर (G_008010_GRBM_EE_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_GRBM | RADEON_RESET_GFX | RADEON_RESET_CP;

	/* DMA_STATUS_REG */
	पंचांगp = RREG32(DMA_STATUS_REG);
	अगर (!(पंचांगp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* SRBM_STATUS */
	पंचांगp = RREG32(R_000E50_SRBM_STATUS);
	अगर (G_000E50_RLC_RQ_PENDING(पंचांगp) | G_000E50_RLC_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_RLC;

	अगर (G_000E50_IH_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_IH;

	अगर (G_000E50_SEM_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_SEM;

	अगर (G_000E50_GRBM_RQ_PENDING(पंचांगp))
		reset_mask |= RADEON_RESET_GRBM;

	अगर (G_000E50_VMC_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_VMC;

	अगर (G_000E50_MCB_BUSY(पंचांगp) | G_000E50_MCDZ_BUSY(पंचांगp) |
	    G_000E50_MCDY_BUSY(पंचांगp) | G_000E50_MCDX_BUSY(पंचांगp) |
	    G_000E50_MCDW_BUSY(पंचांगp))
		reset_mask |= RADEON_RESET_MC;

	अगर (r600_is_display_hung(rdev))
		reset_mask |= RADEON_RESET_DISPLAY;

	/* Skip MC reset as it's mostly likely not hung, just busy */
	अगर (reset_mask & RADEON_RESET_MC) अणु
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	पूर्ण

	वापस reset_mask;
पूर्ण

अटल व्योम r600_gpu_soft_reset(काष्ठा radeon_device *rdev, u32 reset_mask)
अणु
	काष्ठा rv515_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 पंचांगp;

	अगर (reset_mask == 0)
		वापस;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	r600_prपूर्णांक_gpu_status_regs(rdev);

	/* Disable CP parsing/prefetching */
	अगर (rdev->family >= CHIP_RV770)
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1) | S_0086D8_CP_PFP_HALT(1));
	अन्यथा
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1));

	/* disable the RLC */
	WREG32(RLC_CNTL, 0);

	अगर (reset_mask & RADEON_RESET_DMA) अणु
		/* Disable DMA */
		पंचांगp = RREG32(DMA_RB_CNTL);
		पंचांगp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL, पंचांगp);
	पूर्ण

	mdelay(50);

	rv515_mc_stop(rdev, &save);
	अगर (r600_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	अगर (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE)) अणु
		अगर (rdev->family >= CHIP_RV770)
			grbm_soft_reset |= S_008020_SOFT_RESET_DB(1) |
				S_008020_SOFT_RESET_CB(1) |
				S_008020_SOFT_RESET_PA(1) |
				S_008020_SOFT_RESET_SC(1) |
				S_008020_SOFT_RESET_SPI(1) |
				S_008020_SOFT_RESET_SX(1) |
				S_008020_SOFT_RESET_SH(1) |
				S_008020_SOFT_RESET_TC(1) |
				S_008020_SOFT_RESET_TA(1) |
				S_008020_SOFT_RESET_VC(1) |
				S_008020_SOFT_RESET_VGT(1);
		अन्यथा
			grbm_soft_reset |= S_008020_SOFT_RESET_CR(1) |
				S_008020_SOFT_RESET_DB(1) |
				S_008020_SOFT_RESET_CB(1) |
				S_008020_SOFT_RESET_PA(1) |
				S_008020_SOFT_RESET_SC(1) |
				S_008020_SOFT_RESET_SMX(1) |
				S_008020_SOFT_RESET_SPI(1) |
				S_008020_SOFT_RESET_SX(1) |
				S_008020_SOFT_RESET_SH(1) |
				S_008020_SOFT_RESET_TC(1) |
				S_008020_SOFT_RESET_TA(1) |
				S_008020_SOFT_RESET_VC(1) |
				S_008020_SOFT_RESET_VGT(1);
	पूर्ण

	अगर (reset_mask & RADEON_RESET_CP) अणु
		grbm_soft_reset |= S_008020_SOFT_RESET_CP(1) |
			S_008020_SOFT_RESET_VGT(1);

		srbm_soft_reset |= S_000E60_SOFT_RESET_GRBM(1);
	पूर्ण

	अगर (reset_mask & RADEON_RESET_DMA) अणु
		अगर (rdev->family >= CHIP_RV770)
			srbm_soft_reset |= RV770_SOFT_RESET_DMA;
		अन्यथा
			srbm_soft_reset |= SOFT_RESET_DMA;
	पूर्ण

	अगर (reset_mask & RADEON_RESET_RLC)
		srbm_soft_reset |= S_000E60_SOFT_RESET_RLC(1);

	अगर (reset_mask & RADEON_RESET_SEM)
		srbm_soft_reset |= S_000E60_SOFT_RESET_SEM(1);

	अगर (reset_mask & RADEON_RESET_IH)
		srbm_soft_reset |= S_000E60_SOFT_RESET_IH(1);

	अगर (reset_mask & RADEON_RESET_GRBM)
		srbm_soft_reset |= S_000E60_SOFT_RESET_GRBM(1);

	अगर (!(rdev->flags & RADEON_IS_IGP)) अणु
		अगर (reset_mask & RADEON_RESET_MC)
			srbm_soft_reset |= S_000E60_SOFT_RESET_MC(1);
	पूर्ण

	अगर (reset_mask & RADEON_RESET_VMC)
		srbm_soft_reset |= S_000E60_SOFT_RESET_VMC(1);

	अगर (grbm_soft_reset) अणु
		पंचांगp = RREG32(R_008020_GRBM_SOFT_RESET);
		पंचांगp |= grbm_soft_reset;
		dev_info(rdev->dev, "R_008020_GRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(R_008020_GRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(R_008020_GRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~grbm_soft_reset;
		WREG32(R_008020_GRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(R_008020_GRBM_SOFT_RESET);
	पूर्ण

	अगर (srbm_soft_reset) अणु
		पंचांगp = RREG32(SRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(rdev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(SRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(SRBM_SOFT_RESET);
	पूर्ण

	/* Wait a little क्रम things to settle करोwn */
	mdelay(1);

	rv515_mc_resume(rdev, &save);
	udelay(50);

	r600_prपूर्णांक_gpu_status_regs(rdev);
पूर्ण

अटल व्योम r600_gpu_pci_config_reset(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;
	u32 पंचांगp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* Disable CP parsing/prefetching */
	अगर (rdev->family >= CHIP_RV770)
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1) | S_0086D8_CP_PFP_HALT(1));
	अन्यथा
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1));

	/* disable the RLC */
	WREG32(RLC_CNTL, 0);

	/* Disable DMA */
	पंचांगp = RREG32(DMA_RB_CNTL);
	पंचांगp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL, पंचांगp);

	mdelay(50);

	/* set mclk/sclk to bypass */
	अगर (rdev->family >= CHIP_RV770)
		rv770_set_clk_bypass_mode(rdev);
	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* disable mem access */
	rv515_mc_stop(rdev, &save);
	अगर (r600_mc_रुको_क्रम_idle(rdev)) अणु
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	पूर्ण

	/* BIF reset workaround.  Not sure अगर this is needed on 6xx */
	पंचांगp = RREG32(BUS_CNTL);
	पंचांगp |= VGA_COHE_SPEC_TIMER_DIS;
	WREG32(BUS_CNTL, पंचांगp);

	पंचांगp = RREG32(BIF_SCRATCH0);

	/* reset */
	radeon_pci_config_reset(rdev);
	mdelay(1);

	/* BIF reset workaround.  Not sure अगर this is needed on 6xx */
	पंचांगp = SOFT_RESET_BIF;
	WREG32(SRBM_SOFT_RESET, पंचांगp);
	mdelay(1);
	WREG32(SRBM_SOFT_RESET, 0);

	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

पूर्णांक r600_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	u32 reset_mask;

	अगर (hard) अणु
		r600_gpu_pci_config_reset(rdev);
		वापस 0;
	पूर्ण

	reset_mask = r600_gpu_check_soft_reset(rdev);

	अगर (reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, true);

	/* try soft reset */
	r600_gpu_soft_reset(rdev, reset_mask);

	reset_mask = r600_gpu_check_soft_reset(rdev);

	/* try pci config reset */
	अगर (reset_mask && radeon_hard_reset)
		r600_gpu_pci_config_reset(rdev);

	reset_mask = r600_gpu_check_soft_reset(rdev);

	अगर (!reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, false);

	वापस 0;
पूर्ण

/**
 * r600_gfx_is_lockup - Check अगर the GFX engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the GFX engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool r600_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = r600_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & (RADEON_RESET_GFX |
			    RADEON_RESET_COMPUTE |
			    RADEON_RESET_CP))) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

u32 r6xx_remap_render_backend(काष्ठा radeon_device *rdev,
			      u32 tiling_pipe_num,
			      u32 max_rb_num,
			      u32 total_max_rb_num,
			      u32 disabled_rb_mask)
अणु
	u32 rendering_pipe_num, rb_num_width, req_rb_num;
	u32 pipe_rb_ratio, pipe_rb_reमुख्य, पंचांगp;
	u32 data = 0, mask = 1 << (max_rb_num - 1);
	अचिन्हित i, j;

	/* mask out the RBs that करोn't exist on that asic */
	पंचांगp = disabled_rb_mask | ((0xff << max_rb_num) & 0xff);
	/* make sure at least one RB is available */
	अगर ((पंचांगp & 0xff) != 0xff)
		disabled_rb_mask = पंचांगp;

	rendering_pipe_num = 1 << tiling_pipe_num;
	req_rb_num = total_max_rb_num - r600_count_pipe_bits(disabled_rb_mask);
	BUG_ON(rendering_pipe_num < req_rb_num);

	pipe_rb_ratio = rendering_pipe_num / req_rb_num;
	pipe_rb_reमुख्य = rendering_pipe_num - pipe_rb_ratio * req_rb_num;

	अगर (rdev->family <= CHIP_RV740) अणु
		/* r6xx/r7xx */
		rb_num_width = 2;
	पूर्ण अन्यथा अणु
		/* eg+ */
		rb_num_width = 4;
	पूर्ण

	क्रम (i = 0; i < max_rb_num; i++) अणु
		अगर (!(mask & disabled_rb_mask)) अणु
			क्रम (j = 0; j < pipe_rb_ratio; j++) अणु
				data <<= rb_num_width;
				data |= max_rb_num - i - 1;
			पूर्ण
			अगर (pipe_rb_reमुख्य) अणु
				data <<= rb_num_width;
				data |= max_rb_num - i - 1;
				pipe_rb_reमुख्य--;
			पूर्ण
		पूर्ण
		mask >>= 1;
	पूर्ण

	वापस data;
पूर्ण

पूर्णांक r600_count_pipe_bits(uपूर्णांक32_t val)
अणु
	वापस hweight32(val);
पूर्ण

अटल व्योम r600_gpu_init(काष्ठा radeon_device *rdev)
अणु
	u32 tiling_config;
	u32 ramcfg;
	u32 cc_gc_shader_pipe_config;
	u32 पंचांगp;
	पूर्णांक i, j;
	u32 sq_config;
	u32 sq_gpr_resource_mgmt_1 = 0;
	u32 sq_gpr_resource_mgmt_2 = 0;
	u32 sq_thपढ़ो_resource_mgmt = 0;
	u32 sq_stack_resource_mgmt_1 = 0;
	u32 sq_stack_resource_mgmt_2 = 0;
	u32 disabled_rb_mask;

	rdev->config.r600.tiling_group_size = 256;
	चयन (rdev->family) अणु
	हाल CHIP_R600:
		rdev->config.r600.max_pipes = 4;
		rdev->config.r600.max_tile_pipes = 8;
		rdev->config.r600.max_simds = 4;
		rdev->config.r600.max_backends = 4;
		rdev->config.r600.max_gprs = 256;
		rdev->config.r600.max_thपढ़ोs = 192;
		rdev->config.r600.max_stack_entries = 256;
		rdev->config.r600.max_hw_contexts = 8;
		rdev->config.r600.max_gs_thपढ़ोs = 16;
		rdev->config.r600.sx_max_export_size = 128;
		rdev->config.r600.sx_max_export_pos_size = 16;
		rdev->config.r600.sx_max_export_smx_size = 128;
		rdev->config.r600.sq_num_cf_insts = 2;
		अवरोध;
	हाल CHIP_RV630:
	हाल CHIP_RV635:
		rdev->config.r600.max_pipes = 2;
		rdev->config.r600.max_tile_pipes = 2;
		rdev->config.r600.max_simds = 3;
		rdev->config.r600.max_backends = 1;
		rdev->config.r600.max_gprs = 128;
		rdev->config.r600.max_thपढ़ोs = 192;
		rdev->config.r600.max_stack_entries = 128;
		rdev->config.r600.max_hw_contexts = 8;
		rdev->config.r600.max_gs_thपढ़ोs = 4;
		rdev->config.r600.sx_max_export_size = 128;
		rdev->config.r600.sx_max_export_pos_size = 16;
		rdev->config.r600.sx_max_export_smx_size = 128;
		rdev->config.r600.sq_num_cf_insts = 2;
		अवरोध;
	हाल CHIP_RV610:
	हाल CHIP_RV620:
	हाल CHIP_RS780:
	हाल CHIP_RS880:
		rdev->config.r600.max_pipes = 1;
		rdev->config.r600.max_tile_pipes = 1;
		rdev->config.r600.max_simds = 2;
		rdev->config.r600.max_backends = 1;
		rdev->config.r600.max_gprs = 128;
		rdev->config.r600.max_thपढ़ोs = 192;
		rdev->config.r600.max_stack_entries = 128;
		rdev->config.r600.max_hw_contexts = 4;
		rdev->config.r600.max_gs_thपढ़ोs = 4;
		rdev->config.r600.sx_max_export_size = 128;
		rdev->config.r600.sx_max_export_pos_size = 16;
		rdev->config.r600.sx_max_export_smx_size = 128;
		rdev->config.r600.sq_num_cf_insts = 1;
		अवरोध;
	हाल CHIP_RV670:
		rdev->config.r600.max_pipes = 4;
		rdev->config.r600.max_tile_pipes = 4;
		rdev->config.r600.max_simds = 4;
		rdev->config.r600.max_backends = 4;
		rdev->config.r600.max_gprs = 192;
		rdev->config.r600.max_thपढ़ोs = 192;
		rdev->config.r600.max_stack_entries = 256;
		rdev->config.r600.max_hw_contexts = 8;
		rdev->config.r600.max_gs_thपढ़ोs = 16;
		rdev->config.r600.sx_max_export_size = 128;
		rdev->config.r600.sx_max_export_pos_size = 16;
		rdev->config.r600.sx_max_export_smx_size = 128;
		rdev->config.r600.sq_num_cf_insts = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Initialize HDP */
	क्रम (i = 0, j = 0; i < 32; i++, j += 0x18) अणु
		WREG32((0x2c14 + j), 0x00000000);
		WREG32((0x2c18 + j), 0x00000000);
		WREG32((0x2c1c + j), 0x00000000);
		WREG32((0x2c20 + j), 0x00000000);
		WREG32((0x2c24 + j), 0x00000000);
	पूर्ण

	WREG32(GRBM_CNTL, GRBM_READ_TIMEOUT(0xff));

	/* Setup tiling */
	tiling_config = 0;
	ramcfg = RREG32(RAMCFG);
	चयन (rdev->config.r600.max_tile_pipes) अणु
	हाल 1:
		tiling_config |= PIPE_TILING(0);
		अवरोध;
	हाल 2:
		tiling_config |= PIPE_TILING(1);
		अवरोध;
	हाल 4:
		tiling_config |= PIPE_TILING(2);
		अवरोध;
	हाल 8:
		tiling_config |= PIPE_TILING(3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rdev->config.r600.tiling_npipes = rdev->config.r600.max_tile_pipes;
	rdev->config.r600.tiling_nbanks = 4 << ((ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT);
	tiling_config |= BANK_TILING((ramcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT);
	tiling_config |= GROUP_SIZE((ramcfg & BURSTLENGTH_MASK) >> BURSTLENGTH_SHIFT);

	पंचांगp = (ramcfg & NOOFROWS_MASK) >> NOOFROWS_SHIFT;
	अगर (पंचांगp > 3) अणु
		tiling_config |= ROW_TILING(3);
		tiling_config |= SAMPLE_SPLIT(3);
	पूर्ण अन्यथा अणु
		tiling_config |= ROW_TILING(पंचांगp);
		tiling_config |= SAMPLE_SPLIT(पंचांगp);
	पूर्ण
	tiling_config |= BANK_SWAPS(1);

	cc_gc_shader_pipe_config = RREG32(CC_GC_SHADER_PIPE_CONFIG) & 0x00ffff00;
	पंचांगp = rdev->config.r600.max_simds -
		r600_count_pipe_bits((cc_gc_shader_pipe_config >> 16) & R6XX_MAX_SIMDS_MASK);
	rdev->config.r600.active_simds = पंचांगp;

	disabled_rb_mask = (RREG32(CC_RB_BACKEND_DISABLE) >> 16) & R6XX_MAX_BACKENDS_MASK;
	पंचांगp = 0;
	क्रम (i = 0; i < rdev->config.r600.max_backends; i++)
		पंचांगp |= (1 << i);
	/* अगर all the backends are disabled, fix it up here */
	अगर ((disabled_rb_mask & पंचांगp) == पंचांगp) अणु
		क्रम (i = 0; i < rdev->config.r600.max_backends; i++)
			disabled_rb_mask &= ~(1 << i);
	पूर्ण
	पंचांगp = (tiling_config & PIPE_TILING__MASK) >> PIPE_TILING__SHIFT;
	पंचांगp = r6xx_remap_render_backend(rdev, पंचांगp, rdev->config.r600.max_backends,
					R6XX_MAX_BACKENDS, disabled_rb_mask);
	tiling_config |= पंचांगp << 16;
	rdev->config.r600.backend_map = पंचांगp;

	rdev->config.r600.tile_config = tiling_config;
	WREG32(GB_TILING_CONFIG, tiling_config);
	WREG32(DCP_TILING_CONFIG, tiling_config & 0xffff);
	WREG32(HDP_TILING_CONFIG, tiling_config & 0xffff);
	WREG32(DMA_TILING_CONFIG, tiling_config & 0xffff);

	पंचांगp = R6XX_MAX_PIPES - r600_count_pipe_bits((cc_gc_shader_pipe_config & INACTIVE_QD_PIPES_MASK) >> 8);
	WREG32(VGT_OUT_DEALLOC_CNTL, (पंचांगp * 4) & DEALLOC_DIST_MASK);
	WREG32(VGT_VERTEX_REUSE_BLOCK_CNTL, ((पंचांगp * 4) - 2) & VTX_REUSE_DEPTH_MASK);

	/* Setup some CP states */
	WREG32(CP_QUEUE_THRESHOLDS, (ROQ_IB1_START(0x16) | ROQ_IB2_START(0x2b)));
	WREG32(CP_MEQ_THRESHOLDS, (MEQ_END(0x40) | ROQ_END(0x40)));

	WREG32(TA_CNTL_AUX, (DISABLE_CUBE_ANISO | SYNC_GRADIENT |
			     SYNC_WALKER | SYNC_ALIGNER));
	/* Setup various GPU states */
	अगर (rdev->family == CHIP_RV670)
		WREG32(ARB_GDEC_RD_CNTL, 0x00000021);

	पंचांगp = RREG32(SX_DEBUG_1);
	पंचांगp |= SMX_EVENT_RELEASE;
	अगर ((rdev->family > CHIP_R600))
		पंचांगp |= ENABLE_NEW_SMX_ADDRESS;
	WREG32(SX_DEBUG_1, पंचांगp);

	अगर (((rdev->family) == CHIP_R600) ||
	    ((rdev->family) == CHIP_RV630) ||
	    ((rdev->family) == CHIP_RV610) ||
	    ((rdev->family) == CHIP_RV620) ||
	    ((rdev->family) == CHIP_RS780) ||
	    ((rdev->family) == CHIP_RS880)) अणु
		WREG32(DB_DEBUG, PREZ_MUST_WAIT_FOR_POSTZ_DONE);
	पूर्ण अन्यथा अणु
		WREG32(DB_DEBUG, 0);
	पूर्ण
	WREG32(DB_WATERMARKS, (DEPTH_FREE(4) | DEPTH_CACHELINE_FREE(16) |
			       DEPTH_FLUSH(16) | DEPTH_PENDING_FREE(4)));

	WREG32(PA_SC_MULTI_CHIP_CNTL, 0);
	WREG32(VGT_NUM_INSTANCES, 0);

	WREG32(SPI_CONFIG_CNTL, GPR_WRITE_PRIORITY(0));
	WREG32(SPI_CONFIG_CNTL_1, VTX_DONE_DELAY(0));

	पंचांगp = RREG32(SQ_MS_FIFO_SIZES);
	अगर (((rdev->family) == CHIP_RV610) ||
	    ((rdev->family) == CHIP_RV620) ||
	    ((rdev->family) == CHIP_RS780) ||
	    ((rdev->family) == CHIP_RS880)) अणु
		पंचांगp = (CACHE_FIFO_SIZE(0xa) |
		       FETCH_FIFO_HIWATER(0xa) |
		       DONE_FIFO_HIWATER(0xe0) |
		       ALU_UPDATE_FIFO_HIWATER(0x8));
	पूर्ण अन्यथा अगर (((rdev->family) == CHIP_R600) ||
		   ((rdev->family) == CHIP_RV630)) अणु
		पंचांगp &= ~DONE_FIFO_HIWATER(0xff);
		पंचांगp |= DONE_FIFO_HIWATER(0x4);
	पूर्ण
	WREG32(SQ_MS_FIFO_SIZES, पंचांगp);

	/* SQ_CONFIG, SQ_GPR_RESOURCE_MGMT, SQ_THREAD_RESOURCE_MGMT, SQ_STACK_RESOURCE_MGMT
	 * should be adjusted as needed by the 2D/3D drivers.  This just sets शेष values
	 */
	sq_config = RREG32(SQ_CONFIG);
	sq_config &= ~(PS_PRIO(3) |
		       VS_PRIO(3) |
		       GS_PRIO(3) |
		       ES_PRIO(3));
	sq_config |= (DX9_CONSTS |
		      VC_ENABLE |
		      PS_PRIO(0) |
		      VS_PRIO(1) |
		      GS_PRIO(2) |
		      ES_PRIO(3));

	अगर ((rdev->family) == CHIP_R600) अणु
		sq_gpr_resource_mgmt_1 = (NUM_PS_GPRS(124) |
					  NUM_VS_GPRS(124) |
					  NUM_CLAUSE_TEMP_GPRS(4));
		sq_gpr_resource_mgmt_2 = (NUM_GS_GPRS(0) |
					  NUM_ES_GPRS(0));
		sq_thपढ़ो_resource_mgmt = (NUM_PS_THREADS(136) |
					   NUM_VS_THREADS(48) |
					   NUM_GS_THREADS(4) |
					   NUM_ES_THREADS(4));
		sq_stack_resource_mgmt_1 = (NUM_PS_STACK_ENTRIES(128) |
					    NUM_VS_STACK_ENTRIES(128));
		sq_stack_resource_mgmt_2 = (NUM_GS_STACK_ENTRIES(0) |
					    NUM_ES_STACK_ENTRIES(0));
	पूर्ण अन्यथा अगर (((rdev->family) == CHIP_RV610) ||
		   ((rdev->family) == CHIP_RV620) ||
		   ((rdev->family) == CHIP_RS780) ||
		   ((rdev->family) == CHIP_RS880)) अणु
		/* no vertex cache */
		sq_config &= ~VC_ENABLE;

		sq_gpr_resource_mgmt_1 = (NUM_PS_GPRS(44) |
					  NUM_VS_GPRS(44) |
					  NUM_CLAUSE_TEMP_GPRS(2));
		sq_gpr_resource_mgmt_2 = (NUM_GS_GPRS(17) |
					  NUM_ES_GPRS(17));
		sq_thपढ़ो_resource_mgmt = (NUM_PS_THREADS(79) |
					   NUM_VS_THREADS(78) |
					   NUM_GS_THREADS(4) |
					   NUM_ES_THREADS(31));
		sq_stack_resource_mgmt_1 = (NUM_PS_STACK_ENTRIES(40) |
					    NUM_VS_STACK_ENTRIES(40));
		sq_stack_resource_mgmt_2 = (NUM_GS_STACK_ENTRIES(32) |
					    NUM_ES_STACK_ENTRIES(16));
	पूर्ण अन्यथा अगर (((rdev->family) == CHIP_RV630) ||
		   ((rdev->family) == CHIP_RV635)) अणु
		sq_gpr_resource_mgmt_1 = (NUM_PS_GPRS(44) |
					  NUM_VS_GPRS(44) |
					  NUM_CLAUSE_TEMP_GPRS(2));
		sq_gpr_resource_mgmt_2 = (NUM_GS_GPRS(18) |
					  NUM_ES_GPRS(18));
		sq_thपढ़ो_resource_mgmt = (NUM_PS_THREADS(79) |
					   NUM_VS_THREADS(78) |
					   NUM_GS_THREADS(4) |
					   NUM_ES_THREADS(31));
		sq_stack_resource_mgmt_1 = (NUM_PS_STACK_ENTRIES(40) |
					    NUM_VS_STACK_ENTRIES(40));
		sq_stack_resource_mgmt_2 = (NUM_GS_STACK_ENTRIES(32) |
					    NUM_ES_STACK_ENTRIES(16));
	पूर्ण अन्यथा अगर ((rdev->family) == CHIP_RV670) अणु
		sq_gpr_resource_mgmt_1 = (NUM_PS_GPRS(44) |
					  NUM_VS_GPRS(44) |
					  NUM_CLAUSE_TEMP_GPRS(2));
		sq_gpr_resource_mgmt_2 = (NUM_GS_GPRS(17) |
					  NUM_ES_GPRS(17));
		sq_thपढ़ो_resource_mgmt = (NUM_PS_THREADS(79) |
					   NUM_VS_THREADS(78) |
					   NUM_GS_THREADS(4) |
					   NUM_ES_THREADS(31));
		sq_stack_resource_mgmt_1 = (NUM_PS_STACK_ENTRIES(64) |
					    NUM_VS_STACK_ENTRIES(64));
		sq_stack_resource_mgmt_2 = (NUM_GS_STACK_ENTRIES(64) |
					    NUM_ES_STACK_ENTRIES(64));
	पूर्ण

	WREG32(SQ_CONFIG, sq_config);
	WREG32(SQ_GPR_RESOURCE_MGMT_1,  sq_gpr_resource_mgmt_1);
	WREG32(SQ_GPR_RESOURCE_MGMT_2,  sq_gpr_resource_mgmt_2);
	WREG32(SQ_THREAD_RESOURCE_MGMT, sq_thपढ़ो_resource_mgmt);
	WREG32(SQ_STACK_RESOURCE_MGMT_1, sq_stack_resource_mgmt_1);
	WREG32(SQ_STACK_RESOURCE_MGMT_2, sq_stack_resource_mgmt_2);

	अगर (((rdev->family) == CHIP_RV610) ||
	    ((rdev->family) == CHIP_RV620) ||
	    ((rdev->family) == CHIP_RS780) ||
	    ((rdev->family) == CHIP_RS880)) अणु
		WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(TC_ONLY));
	पूर्ण अन्यथा अणु
		WREG32(VGT_CACHE_INVALIDATION, CACHE_INVALIDATION(VC_AND_TC));
	पूर्ण

	/* More शेष values. 2D/3D driver should adjust as needed */
	WREG32(PA_SC_AA_SAMPLE_LOCS_2S, (S0_X(0xc) | S0_Y(0x4) |
					 S1_X(0x4) | S1_Y(0xc)));
	WREG32(PA_SC_AA_SAMPLE_LOCS_4S, (S0_X(0xe) | S0_Y(0xe) |
					 S1_X(0x2) | S1_Y(0x2) |
					 S2_X(0xa) | S2_Y(0x6) |
					 S3_X(0x6) | S3_Y(0xa)));
	WREG32(PA_SC_AA_SAMPLE_LOCS_8S_WD0, (S0_X(0xe) | S0_Y(0xb) |
					     S1_X(0x4) | S1_Y(0xc) |
					     S2_X(0x1) | S2_Y(0x6) |
					     S3_X(0xa) | S3_Y(0xe)));
	WREG32(PA_SC_AA_SAMPLE_LOCS_8S_WD1, (S4_X(0x6) | S4_Y(0x1) |
					     S5_X(0x0) | S5_Y(0x0) |
					     S6_X(0xb) | S6_Y(0x4) |
					     S7_X(0x7) | S7_Y(0x8)));

	WREG32(VGT_STRMOUT_EN, 0);
	पंचांगp = rdev->config.r600.max_pipes * 16;
	चयन (rdev->family) अणु
	हाल CHIP_RV610:
	हाल CHIP_RV620:
	हाल CHIP_RS780:
	हाल CHIP_RS880:
		पंचांगp += 32;
		अवरोध;
	हाल CHIP_RV670:
		पंचांगp += 128;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (पंचांगp > 256) अणु
		पंचांगp = 256;
	पूर्ण
	WREG32(VGT_ES_PER_GS, 128);
	WREG32(VGT_GS_PER_ES, पंचांगp);
	WREG32(VGT_GS_PER_VS, 2);
	WREG32(VGT_GS_VERTEX_REUSE, 16);

	/* more शेष values. 2D/3D driver should adjust as needed */
	WREG32(PA_SC_LINE_STIPPLE_STATE, 0);
	WREG32(VGT_STRMOUT_EN, 0);
	WREG32(SX_MISC, 0);
	WREG32(PA_SC_MODE_CNTL, 0);
	WREG32(PA_SC_AA_CONFIG, 0);
	WREG32(PA_SC_LINE_STIPPLE, 0);
	WREG32(SPI_INPUT_Z, 0);
	WREG32(SPI_PS_IN_CONTROL_0, NUM_INTERP(2));
	WREG32(CB_COLOR7_FRAG, 0);

	/* Clear render buffer base addresses */
	WREG32(CB_COLOR0_BASE, 0);
	WREG32(CB_COLOR1_BASE, 0);
	WREG32(CB_COLOR2_BASE, 0);
	WREG32(CB_COLOR3_BASE, 0);
	WREG32(CB_COLOR4_BASE, 0);
	WREG32(CB_COLOR5_BASE, 0);
	WREG32(CB_COLOR6_BASE, 0);
	WREG32(CB_COLOR7_BASE, 0);
	WREG32(CB_COLOR7_FRAG, 0);

	चयन (rdev->family) अणु
	हाल CHIP_RV610:
	हाल CHIP_RV620:
	हाल CHIP_RS780:
	हाल CHIP_RS880:
		पंचांगp = TC_L2_SIZE(8);
		अवरोध;
	हाल CHIP_RV630:
	हाल CHIP_RV635:
		पंचांगp = TC_L2_SIZE(4);
		अवरोध;
	हाल CHIP_R600:
		पंचांगp = TC_L2_SIZE(0) | L2_DISABLE_LATE_HIT;
		अवरोध;
	शेष:
		पंचांगp = TC_L2_SIZE(0);
		अवरोध;
	पूर्ण
	WREG32(TC_CNTL, पंचांगp);

	पंचांगp = RREG32(HDP_HOST_PATH_CNTL);
	WREG32(HDP_HOST_PATH_CNTL, पंचांगp);

	पंचांगp = RREG32(ARB_POP);
	पंचांगp |= ENABLE_TC128;
	WREG32(ARB_POP, पंचांगp);

	WREG32(PA_SC_MULTI_CHIP_CNTL, 0);
	WREG32(PA_CL_ENHANCE, (CLIP_VTX_REORDER_ENA |
			       NUM_CLIP_SEQ(3)));
	WREG32(PA_SC_ENHANCE, FORCE_EOV_MAX_CLK_CNT(4095));
	WREG32(VC_ENHANCE, 0);
पूर्ण


/*
 * Indirect रेजिस्टरs accessor
 */
u32 r600_pciep_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->pciep_idx_lock, flags);
	WREG32(PCIE_PORT_INDEX, ((reg) & 0xff));
	(व्योम)RREG32(PCIE_PORT_INDEX);
	r = RREG32(PCIE_PORT_DATA);
	spin_unlock_irqrestore(&rdev->pciep_idx_lock, flags);
	वापस r;
पूर्ण

व्योम r600_pciep_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->pciep_idx_lock, flags);
	WREG32(PCIE_PORT_INDEX, ((reg) & 0xff));
	(व्योम)RREG32(PCIE_PORT_INDEX);
	WREG32(PCIE_PORT_DATA, (v));
	(व्योम)RREG32(PCIE_PORT_DATA);
	spin_unlock_irqrestore(&rdev->pciep_idx_lock, flags);
पूर्ण

/*
 * CP & Ring
 */
व्योम r600_cp_stop(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
	WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1));
	WREG32(SCRATCH_UMSK, 0);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
पूर्ण

पूर्णांक r600_init_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर अक्षर *chip_name;
	स्थिर अक्षर *rlc_chip_name;
	स्थिर अक्षर *smc_chip_name = "RV770";
	माप_प्रकार pfp_req_size, me_req_size, rlc_req_size, smc_req_size = 0;
	अक्षर fw_name[30];
	पूर्णांक err;

	DRM_DEBUG("\n");

	चयन (rdev->family) अणु
	हाल CHIP_R600:
		chip_name = "R600";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RV610:
		chip_name = "RV610";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RV630:
		chip_name = "RV630";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RV620:
		chip_name = "RV620";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RV635:
		chip_name = "RV635";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RV670:
		chip_name = "RV670";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RS780:
	हाल CHIP_RS880:
		chip_name = "RS780";
		rlc_chip_name = "R600";
		अवरोध;
	हाल CHIP_RV770:
		chip_name = "RV770";
		rlc_chip_name = "R700";
		smc_chip_name = "RV770";
		smc_req_size = ALIGN(RV770_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_RV730:
		chip_name = "RV730";
		rlc_chip_name = "R700";
		smc_chip_name = "RV730";
		smc_req_size = ALIGN(RV730_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_RV710:
		chip_name = "RV710";
		rlc_chip_name = "R700";
		smc_chip_name = "RV710";
		smc_req_size = ALIGN(RV710_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_RV740:
		chip_name = "RV730";
		rlc_chip_name = "R700";
		smc_chip_name = "RV740";
		smc_req_size = ALIGN(RV740_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_CEDAR:
		chip_name = "CEDAR";
		rlc_chip_name = "CEDAR";
		smc_chip_name = "CEDAR";
		smc_req_size = ALIGN(CEDAR_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_REDWOOD:
		chip_name = "REDWOOD";
		rlc_chip_name = "REDWOOD";
		smc_chip_name = "REDWOOD";
		smc_req_size = ALIGN(REDWOOD_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_JUNIPER:
		chip_name = "JUNIPER";
		rlc_chip_name = "JUNIPER";
		smc_chip_name = "JUNIPER";
		smc_req_size = ALIGN(JUNIPER_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		chip_name = "CYPRESS";
		rlc_chip_name = "CYPRESS";
		smc_chip_name = "CYPRESS";
		smc_req_size = ALIGN(CYPRESS_SMC_UCODE_SIZE, 4);
		अवरोध;
	हाल CHIP_PALM:
		chip_name = "PALM";
		rlc_chip_name = "SUMO";
		अवरोध;
	हाल CHIP_SUMO:
		chip_name = "SUMO";
		rlc_chip_name = "SUMO";
		अवरोध;
	हाल CHIP_SUMO2:
		chip_name = "SUMO2";
		rlc_chip_name = "SUMO";
		अवरोध;
	शेष: BUG();
	पूर्ण

	अगर (rdev->family >= CHIP_CEDAR) अणु
		pfp_req_size = EVERGREEN_PFP_UCODE_SIZE * 4;
		me_req_size = EVERGREEN_PM4_UCODE_SIZE * 4;
		rlc_req_size = EVERGREEN_RLC_UCODE_SIZE * 4;
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_RV770) अणु
		pfp_req_size = R700_PFP_UCODE_SIZE * 4;
		me_req_size = R700_PM4_UCODE_SIZE * 4;
		rlc_req_size = R700_RLC_UCODE_SIZE * 4;
	पूर्ण अन्यथा अणु
		pfp_req_size = R600_PFP_UCODE_SIZE * 4;
		me_req_size = R600_PM4_UCODE_SIZE * 12;
		rlc_req_size = R600_RLC_UCODE_SIZE * 4;
	पूर्ण

	DRM_INFO("Loading %s Microcode\n", chip_name);

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_pfp.bin", chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	अगर (err)
		जाओ out;
	अगर (rdev->pfp_fw->size != pfp_req_size) अणु
		pr_err("r600_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->pfp_fw->size, fw_name);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_me.bin", chip_name);
	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	अगर (err)
		जाओ out;
	अगर (rdev->me_fw->size != me_req_size) अणु
		pr_err("r600_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->me_fw->size, fw_name);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "radeon/%s_rlc.bin", rlc_chip_name);
	err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
	अगर (err)
		जाओ out;
	अगर (rdev->rlc_fw->size != rlc_req_size) अणु
		pr_err("r600_rlc: Bogus length %zu in firmware \"%s\"\n",
		       rdev->rlc_fw->size, fw_name);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((rdev->family >= CHIP_RV770) && (rdev->family <= CHIP_HEMLOCK)) अणु
		snम_लिखो(fw_name, माप(fw_name), "radeon/%s_smc.bin", smc_chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		अगर (err) अणु
			pr_err("smc: error loading firmware \"%s\"\n", fw_name);
			release_firmware(rdev->smc_fw);
			rdev->smc_fw = शून्य;
			err = 0;
		पूर्ण अन्यथा अगर (rdev->smc_fw->size != smc_req_size) अणु
			pr_err("smc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->smc_fw->size, fw_name);
			err = -EINVAL;
		पूर्ण
	पूर्ण

out:
	अगर (err) अणु
		अगर (err != -EINVAL)
			pr_err("r600_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = शून्य;
		release_firmware(rdev->me_fw);
		rdev->me_fw = शून्य;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = शून्य;
		release_firmware(rdev->smc_fw);
		rdev->smc_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

u32 r600_gfx_get_rptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring)
अणु
	u32 rptr;

	अगर (rdev->wb.enabled)
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	अन्यथा
		rptr = RREG32(R600_CP_RB_RPTR);

	वापस rptr;
पूर्ण

u32 r600_gfx_get_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring)
अणु
	वापस RREG32(R600_CP_RB_WPTR);
पूर्ण

व्योम r600_gfx_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	WREG32(R600_CP_RB_WPTR, ring->wptr);
	(व्योम)RREG32(R600_CP_RB_WPTR);
पूर्ण

अटल पूर्णांक r600_cp_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data;
	पूर्णांक i;

	अगर (!rdev->me_fw || !rdev->pfp_fw)
		वापस -EINVAL;

	r600_cp_stop(rdev);

	WREG32(CP_RB_CNTL,
#अगर_घोषित __BIG_ENDIAN
	       BUF_SWAP_32BIT |
#पूर्ण_अगर
	       RB_NO_UPDATE | RB_BLKSZ(15) | RB_BUFSZ(3));

	/* Reset cp */
	WREG32(GRBM_SOFT_RESET, SOFT_RESET_CP);
	RREG32(GRBM_SOFT_RESET);
	mdelay(15);
	WREG32(GRBM_SOFT_RESET, 0);

	WREG32(CP_ME_RAM_WADDR, 0);

	fw_data = (स्थिर __be32 *)rdev->me_fw->data;
	WREG32(CP_ME_RAM_WADDR, 0);
	क्रम (i = 0; i < R600_PM4_UCODE_SIZE * 3; i++)
		WREG32(CP_ME_RAM_DATA,
		       be32_to_cpup(fw_data++));

	fw_data = (स्थिर __be32 *)rdev->pfp_fw->data;
	WREG32(CP_PFP_UCODE_ADDR, 0);
	क्रम (i = 0; i < R600_PFP_UCODE_SIZE; i++)
		WREG32(CP_PFP_UCODE_DATA,
		       be32_to_cpup(fw_data++));

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	वापस 0;
पूर्ण

पूर्णांक r600_cp_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	पूर्णांक r;
	uपूर्णांक32_t cp_me;

	r = radeon_ring_lock(rdev, ring, 7);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_ME_INITIALIZE, 5));
	radeon_ring_ग_लिखो(ring, 0x1);
	अगर (rdev->family >= CHIP_RV770) अणु
		radeon_ring_ग_लिखो(ring, 0x0);
		radeon_ring_ग_लिखो(ring, rdev->config.rv770.max_hw_contexts - 1);
	पूर्ण अन्यथा अणु
		radeon_ring_ग_लिखो(ring, 0x3);
		radeon_ring_ग_लिखो(ring, rdev->config.r600.max_hw_contexts - 1);
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3_ME_INITIALIZE_DEVICE_ID(1));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_unlock_commit(rdev, ring, false);

	cp_me = 0xff;
	WREG32(R_0086D8_CP_ME_CNTL, cp_me);
	वापस 0;
पूर्ण

पूर्णांक r600_cp_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	u32 पंचांगp;
	u32 rb_bufsz;
	पूर्णांक r;

	/* Reset cp */
	WREG32(GRBM_SOFT_RESET, SOFT_RESET_CP);
	RREG32(GRBM_SOFT_RESET);
	mdelay(15);
	WREG32(GRBM_SOFT_RESET, 0);

	/* Set ring buffer size */
	rb_bufsz = order_base_2(ring->ring_size / 8);
	पंचांगp = (order_base_2(RADEON_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(CP_RB_CNTL, पंचांगp);
	WREG32(CP_SEM_WAIT_TIMER, 0x0);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(CP_RB_WPTR_DELAY, 0);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(CP_RB_CNTL, पंचांगp | RB_RPTR_WR_ENA);
	WREG32(CP_RB_RPTR_WR, 0);
	ring->wptr = 0;
	WREG32(CP_RB_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(CP_RB_RPTR_ADDR,
	       ((rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFFFFFFFC));
	WREG32(CP_RB_RPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) & 0xFF);
	WREG32(SCRATCH_ADDR, ((rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET) >> 8) & 0xFFFFFFFF);

	अगर (rdev->wb.enabled)
		WREG32(SCRATCH_UMSK, 0xff);
	अन्यथा अणु
		पंचांगp |= RB_NO_UPDATE;
		WREG32(SCRATCH_UMSK, 0);
	पूर्ण

	mdelay(1);
	WREG32(CP_RB_CNTL, पंचांगp);

	WREG32(CP_RB_BASE, ring->gpu_addr >> 8);
	WREG32(CP_DEBUG, (1 << 27) | (1 << 28));

	r600_cp_start(rdev);
	ring->पढ़ोy = true;
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, ring);
	अगर (r) अणु
		ring->पढ़ोy = false;
		वापस r;
	पूर्ण

	अगर (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	वापस 0;
पूर्ण

व्योम r600_ring_init(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring, अचिन्हित ring_size)
अणु
	u32 rb_bufsz;
	पूर्णांक r;

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 8);
	ring_size = (1 << (rb_bufsz + 1)) * 4;
	ring->ring_size = ring_size;
	ring->align_mask = 16 - 1;

	अगर (radeon_ring_supports_scratch_reg(rdev, ring)) अणु
		r = radeon_scratch_get(rdev, &ring->rptr_save_reg);
		अगर (r) अणु
			DRM_ERROR("failed to get scratch reg for rptr save (%d).\n", r);
			ring->rptr_save_reg = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम r600_cp_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r600_cp_stop(rdev);
	radeon_ring_fini(rdev, ring);
	radeon_scratch_मुक्त(rdev, ring->rptr_save_reg);
पूर्ण

/*
 * GPU scratch रेजिस्टरs helpers function.
 */
व्योम r600_scratch_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	rdev->scratch.num_reg = 7;
	rdev->scratch.reg_base = SCRATCH_REG0;
	क्रम (i = 0; i < rdev->scratch.num_reg; i++) अणु
		rdev->scratch.मुक्त[i] = true;
		rdev->scratch.reg[i] = rdev->scratch.reg_base + (i * 4);
	पूर्ण
पूर्ण

पूर्णांक r600_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	uपूर्णांक32_t scratch;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	r = radeon_scratch_get(rdev, &scratch);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to get scratch reg (%d).\n", r);
		वापस r;
	पूर्ण
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ring_lock(rdev, ring, 3);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring %d (%d).\n", ring->idx, r);
		radeon_scratch_मुक्त(rdev, scratch);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
	radeon_ring_ग_लिखो(ring, ((scratch - PACKET3_SET_CONFIG_REG_OFFSET) >> 2));
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(scratch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test on %d succeeded in %d usecs\n", ring->idx, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring %d test failed (scratch(0x%04X)=0x%08X)\n",
			  ring->idx, scratch, पंचांगp);
		r = -EINVAL;
	पूर्ण
	radeon_scratch_मुक्त(rdev, scratch);
	वापस r;
पूर्ण

/*
 * CP fences/semaphores
 */

व्योम r600_fence_ring_emit(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u32 cp_coher_cntl = PACKET3_TC_ACTION_ENA | PACKET3_VC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	अगर (rdev->family >= CHIP_RV770)
		cp_coher_cntl |= PACKET3_FULL_CACHE_ENA;

	अगर (rdev->wb.use_event) अणु
		u64 addr = rdev->fence_drv[fence->ring].gpu_addr;
		/* flush पढ़ो cache over gart */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
		radeon_ring_ग_लिखो(ring, cp_coher_cntl);
		radeon_ring_ग_लिखो(ring, 0xFFFFFFFF);
		radeon_ring_ग_लिखो(ring, 0);
		radeon_ring_ग_लिखो(ring, 10); /* poll पूर्णांकerval */
		/* EVENT_WRITE_EOP - flush caches, send पूर्णांक */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
		radeon_ring_ग_लिखो(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_EVENT_TS) | EVENT_INDEX(5));
		radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
		radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff) | DATA_SEL(1) | INT_SEL(2));
		radeon_ring_ग_लिखो(ring, fence->seq);
		radeon_ring_ग_लिखो(ring, 0);
	पूर्ण अन्यथा अणु
		/* flush पढ़ो cache over gart */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
		radeon_ring_ग_लिखो(ring, cp_coher_cntl);
		radeon_ring_ग_लिखो(ring, 0xFFFFFFFF);
		radeon_ring_ग_लिखो(ring, 0);
		radeon_ring_ग_लिखो(ring, 10); /* poll पूर्णांकerval */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
		radeon_ring_ग_लिखो(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_EVENT) | EVENT_INDEX(0));
		/* रुको क्रम 3D idle clean */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_ग_लिखो(ring, (WAIT_UNTIL - PACKET3_SET_CONFIG_REG_OFFSET) >> 2);
		radeon_ring_ग_लिखो(ring, WAIT_3D_IDLE_bit | WAIT_3D_IDLECLEAN_bit);
		/* Emit fence sequence & fire IRQ */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_ग_लिखो(ring, ((rdev->fence_drv[fence->ring].scratch_reg - PACKET3_SET_CONFIG_REG_OFFSET) >> 2));
		radeon_ring_ग_लिखो(ring, fence->seq);
		/* CP_INTERRUPT packet 3 no दीर्घer exists, use packet 0 */
		radeon_ring_ग_लिखो(ring, PACKET0(CP_INT_STATUS, 0));
		radeon_ring_ग_लिखो(ring, RB_INT_STAT);
	पूर्ण
पूर्ण

/**
 * r600_semaphore_ring_emit - emit a semaphore on the CP ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring buffer object
 * @semaphore: radeon semaphore object
 * @emit_रुको: Is this a sempahore रुको?
 *
 * Emits a semaphore संकेत/रुको packet to the CP ring and prevents the PFP
 * from running ahead of semaphore रुकोs.
 */
bool r600_semaphore_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ring *ring,
			      काष्ठा radeon_semaphore *semaphore,
			      bool emit_रुको)
अणु
	uपूर्णांक64_t addr = semaphore->gpu_addr;
	अचिन्हित sel = emit_रुको ? PACKET3_SEM_SEL_WAIT : PACKET3_SEM_SEL_SIGNAL;

	अगर (rdev->family < CHIP_CAYMAN)
		sel |= PACKET3_SEM_WAIT_ON_SIGNAL;

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_MEM_SEMAPHORE, 1));
	radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff) | sel);

	/* PFP_SYNC_ME packet only exists on 7xx+, only enable it on eg+ */
	अगर (emit_रुको && (rdev->family >= CHIP_CEDAR)) अणु
		/* Prevent the PFP from running ahead of the semaphore रुको */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		radeon_ring_ग_लिखो(ring, 0x0);
	पूर्ण

	वापस true;
पूर्ण

/**
 * r600_copy_cpdma - copy pages using the CP DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @num_gpu_pages: number of GPU pages to xfer
 * @resv: DMA reservation object to manage fences
 *
 * Copy GPU paging using the CP DMA engine (r6xx+).
 * Used by the radeon tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
काष्ठा radeon_fence *r600_copy_cpdma(काष्ठा radeon_device *rdev,
				     uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				     अचिन्हित num_gpu_pages,
				     काष्ठा dma_resv *resv)
अणु
	काष्ठा radeon_fence *fence;
	काष्ठा radeon_sync sync;
	पूर्णांक ring_index = rdev->asic->copy.blit_ring_index;
	काष्ठा radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_bytes, cur_size_in_bytes, पंचांगp;
	पूर्णांक i, num_loops;
	पूर्णांक r = 0;

	radeon_sync_create(&sync);

	size_in_bytes = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT);
	num_loops = DIV_ROUND_UP(size_in_bytes, 0x1fffff);
	r = radeon_ring_lock(rdev, ring, num_loops * 6 + 24);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
	radeon_ring_ग_लिखो(ring, (WAIT_UNTIL - PACKET3_SET_CONFIG_REG_OFFSET) >> 2);
	radeon_ring_ग_लिखो(ring, WAIT_3D_IDLE_bit);
	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size_in_bytes = size_in_bytes;
		अगर (cur_size_in_bytes > 0x1fffff)
			cur_size_in_bytes = 0x1fffff;
		size_in_bytes -= cur_size_in_bytes;
		पंचांगp = upper_32_bits(src_offset) & 0xff;
		अगर (size_in_bytes == 0)
			पंचांगp |= PACKET3_CP_DMA_CP_SYNC;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_CP_DMA, 4));
		radeon_ring_ग_लिखो(ring, lower_32_bits(src_offset));
		radeon_ring_ग_लिखो(ring, पंचांगp);
		radeon_ring_ग_लिखो(ring, lower_32_bits(dst_offset));
		radeon_ring_ग_लिखो(ring, upper_32_bits(dst_offset) & 0xff);
		radeon_ring_ग_लिखो(ring, cur_size_in_bytes);
		src_offset += cur_size_in_bytes;
		dst_offset += cur_size_in_bytes;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
	radeon_ring_ग_लिखो(ring, (WAIT_UNTIL - PACKET3_SET_CONFIG_REG_OFFSET) >> 2);
	radeon_ring_ग_लिखो(ring, WAIT_CP_DMA_IDLE_bit);

	r = radeon_fence_emit(rdev, &fence, ring->idx);
	अगर (r) अणु
		radeon_ring_unlock_unकरो(rdev, ring);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_ring_unlock_commit(rdev, ring, false);
	radeon_sync_मुक्त(rdev, &sync, fence);

	वापस fence;
पूर्ण

पूर्णांक r600_set_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg,
			 uपूर्णांक32_t tiling_flags, uपूर्णांक32_t pitch,
			 uपूर्णांक32_t offset, uपूर्णांक32_t obj_size)
अणु
	/* FIXME: implement */
	वापस 0;
पूर्ण

व्योम r600_clear_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg)
अणु
	/* FIXME: implement */
पूर्ण

अटल व्योम r600_uvd_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = radeon_uvd_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD (%d) init.\n", r);
		/*
		 * At this poपूर्णांक rdev->uvd.vcpu_bo is शून्य which trickles करोwn
		 * to early fails uvd_v1_0_resume() and thus nothing happens
		 * there. So it is poपूर्णांकless to try to go through that code
		 * hence why we disable uvd here.
		 */
		rdev->has_uvd = false;
		वापस;
	पूर्ण
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX], 4096);
पूर्ण

अटल व्योम r600_uvd_start(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->has_uvd)
		वापस;

	r = uvd_v1_0_resume(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed UVD resume (%d).\n", r);
		जाओ error;
	पूर्ण
	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_UVD_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD fences (%d).\n", r);
		जाओ error;
	पूर्ण
	वापस;

error:
	rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size = 0;
पूर्ण

अटल व्योम r600_uvd_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	अगर (!rdev->has_uvd || !rdev->ring[R600_RING_TYPE_UVD_INDEX].ring_size)
		वापस;

	ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, 0, PACKET0(UVD_NO_OP, 0));
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD ring (%d).\n", r);
		वापस;
	पूर्ण
	r = uvd_v1_0_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing UVD (%d).\n", r);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक r600_startup(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	पूर्णांक r;

	/* enable pcie gen2 link */
	r600_pcie_gen2_enable(rdev);

	/* scratch needs to be initialized beक्रमe MC */
	r = r600_vram_scratch_init(rdev);
	अगर (r)
		वापस r;

	r600_mc_program(rdev);

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		r600_agp_enable(rdev);
	पूर्ण अन्यथा अणु
		r = r600_pcie_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	r600_gpu_init(rdev);

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	r600_uvd_start(rdev);

	/* Enable IRQ */
	अगर (!rdev->irq.installed) अणु
		r = radeon_irq_kms_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	r = r600_irq_init(rdev);
	अगर (r) अणु
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		वापस r;
	पूर्ण
	r600_irq_set(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r)
		वापस r;

	r = r600_cp_load_microcode(rdev);
	अगर (r)
		वापस r;
	r = r600_cp_resume(rdev);
	अगर (r)
		वापस r;

	r600_uvd_resume(rdev);

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_audio_init(rdev);
	अगर (r) अणु
		DRM_ERROR("radeon: audio init failed\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम r600_vga_set_state(काष्ठा radeon_device *rdev, bool state)
अणु
	uपूर्णांक32_t temp;

	temp = RREG32(CONFIG_CNTL);
	अगर (!state) अणु
		temp &= ~(1<<0);
		temp |= (1<<1);
	पूर्ण अन्यथा अणु
		temp &= ~(1<<1);
	पूर्ण
	WREG32(CONFIG_CNTL, temp);
पूर्ण

पूर्णांक r600_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Do not reset GPU beक्रमe posting, on r600 hw unlike on r500 hw,
	 * posting will perक्रमm necessary task to bring back GPU पूर्णांकo good
	 * shape.
	 */
	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = r600_startup(rdev);
	अगर (r) अणु
		DRM_ERROR("r600 startup failed on resume\n");
		rdev->accel_working = false;
		वापस r;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक r600_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	r600_cp_stop(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_suspend(rdev);
	पूर्ण
	r600_irq_suspend(rdev);
	radeon_wb_disable(rdev);
	r600_pcie_gart_disable(rdev);

	वापस 0;
पूर्ण

/* Plan is to move initialization in that function and use
 * helper function so that radeon_device_init pretty much
 * करो nothing more than calling asic specअगरic function. This
 * should also allow to हटाओ a bunch of callback function
 * like vram_info.
 */
पूर्णांक r600_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	r600_debugfs_mc_info_init(rdev);
	/* Read BIOS */
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	/* Must be an ATOMBIOS */
	अगर (!rdev->is_atom_bios) अणु
		dev_err(rdev->dev, "Expecting atombios for R600 GPU\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_atombios_init(rdev);
	अगर (r)
		वापस r;
	/* Post card अगर necessary */
	अगर (!radeon_card_posted(rdev)) अणु
		अगर (!rdev->bios) अणु
			dev_err(rdev->dev, "Card not posted and no BIOS - ignoring\n");
			वापस -EINVAL;
		पूर्ण
		DRM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(rdev->mode_info.atom_context);
	पूर्ण
	/* Initialize scratch रेजिस्टरs */
	r600_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		r = radeon_agp_init(rdev);
		अगर (r)
			radeon_agp_disable(rdev);
	पूर्ण
	r = r600_mc_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;

	अगर (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw) अणु
		r = r600_init_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].ring_obj = शून्य;
	r600_ring_init(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX], 1024 * 1024);

	r600_uvd_init(rdev);

	rdev->ih.ring_obj = शून्य;
	r600_ih_ring_init(rdev, 64 * 1024);

	r = r600_pcie_gart_init(rdev);
	अगर (r)
		वापस r;

	rdev->accel_working = true;
	r = r600_startup(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "disabling GPU acceleration\n");
		r600_cp_fini(rdev);
		r600_irq_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		r600_pcie_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण

	वापस 0;
पूर्ण

व्योम r600_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	radeon_audio_fini(rdev);
	r600_cp_fini(rdev);
	r600_irq_fini(rdev);
	अगर (rdev->has_uvd) अणु
		uvd_v1_0_fini(rdev);
		radeon_uvd_fini(rdev);
	पूर्ण
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_irq_kms_fini(rdev);
	r600_pcie_gart_fini(rdev);
	r600_vram_scratch_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_gem_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण


/*
 * CS stuff
 */
व्योम r600_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	u32 next_rptr;

	अगर (ring->rptr_save_reg) अणु
		next_rptr = ring->wptr + 3 + 4;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_ग_लिखो(ring, ((ring->rptr_save_reg -
					 PACKET3_SET_CONFIG_REG_OFFSET) >> 2));
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण अन्यथा अगर (rdev->wb.enabled) अणु
		next_rptr = ring->wptr + 5 + 4;
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_MEM_WRITE, 3));
		radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, (upper_32_bits(ring->next_rptr_gpu_addr) & 0xff) | (1 << 18));
		radeon_ring_ग_लिखो(ring, next_rptr);
		radeon_ring_ग_लिखो(ring, 0);
	पूर्ण

	radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_INसूचीECT_BUFFER, 2));
	radeon_ring_ग_लिखो(ring,
#अगर_घोषित __BIG_ENDIAN
			  (2 << 0) |
#पूर्ण_अगर
			  (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr) & 0xFF);
	radeon_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

पूर्णांक r600_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	काष्ठा radeon_ib ib;
	uपूर्णांक32_t scratch;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	r = radeon_scratch_get(rdev, &scratch);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get scratch reg (%d).\n", r);
		वापस r;
	पूर्ण
	WREG32(scratch, 0xCAFEDEAD);
	r = radeon_ib_get(rdev, ring->idx, &ib, शून्य, 256);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		जाओ मुक्त_scratch;
	पूर्ण
	ib.ptr[0] = PACKET3(PACKET3_SET_CONFIG_REG, 1);
	ib.ptr[1] = ((scratch - PACKET3_SET_CONFIG_REG_OFFSET) >> 2);
	ib.ptr[2] = 0xDEADBEEF;
	ib.length_dw = 3;
	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		जाओ मुक्त_ib;
	पूर्ण
	r = radeon_fence_रुको_समयout(ib.fence, false, usecs_to_jअगरfies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	अगर (r < 0) अणु
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		जाओ मुक्त_ib;
	पूर्ण अन्यथा अगर (r == 0) अणु
		DRM_ERROR("radeon: fence wait timed out.\n");
		r = -ETIMEDOUT;
		जाओ मुक्त_ib;
	पूर्ण
	r = 0;
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(scratch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ib test on ring %d succeeded in %u usecs\n", ib.fence->ring, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ib test failed (scratch(0x%04X)=0x%08X)\n",
			  scratch, पंचांगp);
		r = -EINVAL;
	पूर्ण
मुक्त_ib:
	radeon_ib_मुक्त(rdev, &ib);
मुक्त_scratch:
	radeon_scratch_मुक्त(rdev, scratch);
	वापस r;
पूर्ण

/*
 * Interrupts
 *
 * Interrupts use a ring buffer on r6xx/r7xx hardware.  It works pretty
 * the same as the CP ring buffer, but in reverse.  Rather than the CPU
 * writing to the ring and the GPU consuming, the GPU ग_लिखोs to the ring
 * and host consumes.  As the host irq handler processes पूर्णांकerrupts, it
 * increments the rptr.  When the rptr catches up with the wptr, all the
 * current पूर्णांकerrupts have been processed.
 */

व्योम r600_ih_ring_init(काष्ठा radeon_device *rdev, अचिन्हित ring_size)
अणु
	u32 rb_bufsz;

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 4);
	ring_size = (1 << rb_bufsz) * 4;
	rdev->ih.ring_size = ring_size;
	rdev->ih.ptr_mask = rdev->ih.ring_size - 1;
	rdev->ih.rptr = 0;
पूर्ण

पूर्णांक r600_ih_ring_alloc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Allocate ring buffer */
	अगर (rdev->ih.ring_obj == शून्य) अणु
		r = radeon_bo_create(rdev, rdev->ih.ring_size,
				     PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, 0,
				     शून्य, शून्य, &rdev->ih.ring_obj);
		अगर (r) अणु
			DRM_ERROR("radeon: failed to create ih ring buffer (%d).\n", r);
			वापस r;
		पूर्ण
		r = radeon_bo_reserve(rdev->ih.ring_obj, false);
		अगर (unlikely(r != 0))
			वापस r;
		r = radeon_bo_pin(rdev->ih.ring_obj,
				  RADEON_GEM_DOMAIN_GTT,
				  &rdev->ih.gpu_addr);
		अगर (r) अणु
			radeon_bo_unreserve(rdev->ih.ring_obj);
			DRM_ERROR("radeon: failed to pin ih ring buffer (%d).\n", r);
			वापस r;
		पूर्ण
		r = radeon_bo_kmap(rdev->ih.ring_obj,
				   (व्योम **)&rdev->ih.ring);
		radeon_bo_unreserve(rdev->ih.ring_obj);
		अगर (r) अणु
			DRM_ERROR("radeon: failed to map ih ring buffer (%d).\n", r);
			वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम r600_ih_ring_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;
	अगर (rdev->ih.ring_obj) अणु
		r = radeon_bo_reserve(rdev->ih.ring_obj, false);
		अगर (likely(r == 0)) अणु
			radeon_bo_kunmap(rdev->ih.ring_obj);
			radeon_bo_unpin(rdev->ih.ring_obj);
			radeon_bo_unreserve(rdev->ih.ring_obj);
		पूर्ण
		radeon_bo_unref(&rdev->ih.ring_obj);
		rdev->ih.ring = शून्य;
		rdev->ih.ring_obj = शून्य;
	पूर्ण
पूर्ण

व्योम r600_rlc_stop(काष्ठा radeon_device *rdev)
अणु

	अगर ((rdev->family >= CHIP_RV770) &&
	    (rdev->family <= CHIP_RV740)) अणु
		/* r7xx asics need to soft reset RLC beक्रमe halting */
		WREG32(SRBM_SOFT_RESET, SOFT_RESET_RLC);
		RREG32(SRBM_SOFT_RESET);
		mdelay(15);
		WREG32(SRBM_SOFT_RESET, 0);
		RREG32(SRBM_SOFT_RESET);
	पूर्ण

	WREG32(RLC_CNTL, 0);
पूर्ण

अटल व्योम r600_rlc_start(काष्ठा radeon_device *rdev)
अणु
	WREG32(RLC_CNTL, RLC_ENABLE);
पूर्ण

अटल पूर्णांक r600_rlc_resume(काष्ठा radeon_device *rdev)
अणु
	u32 i;
	स्थिर __be32 *fw_data;

	अगर (!rdev->rlc_fw)
		वापस -EINVAL;

	r600_rlc_stop(rdev);

	WREG32(RLC_HB_CNTL, 0);

	WREG32(RLC_HB_BASE, 0);
	WREG32(RLC_HB_RPTR, 0);
	WREG32(RLC_HB_WPTR, 0);
	WREG32(RLC_HB_WPTR_LSB_ADDR, 0);
	WREG32(RLC_HB_WPTR_MSB_ADDR, 0);
	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	fw_data = (स्थिर __be32 *)rdev->rlc_fw->data;
	अगर (rdev->family >= CHIP_RV770) अणु
		क्रम (i = 0; i < R700_RLC_UCODE_SIZE; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < R600_RLC_UCODE_SIZE; i++) अणु
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		पूर्ण
	पूर्ण
	WREG32(RLC_UCODE_ADDR, 0);

	r600_rlc_start(rdev);

	वापस 0;
पूर्ण

अटल व्योम r600_enable_पूर्णांकerrupts(काष्ठा radeon_device *rdev)
अणु
	u32 ih_cntl = RREG32(IH_CNTL);
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);

	ih_cntl |= ENABLE_INTR;
	ih_rb_cntl |= IH_RB_ENABLE;
	WREG32(IH_CNTL, ih_cntl);
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	rdev->ih.enabled = true;
पूर्ण

व्योम r600_disable_पूर्णांकerrupts(काष्ठा radeon_device *rdev)
अणु
	u32 ih_rb_cntl = RREG32(IH_RB_CNTL);
	u32 ih_cntl = RREG32(IH_CNTL);

	ih_rb_cntl &= ~IH_RB_ENABLE;
	ih_cntl &= ~ENABLE_INTR;
	WREG32(IH_RB_CNTL, ih_rb_cntl);
	WREG32(IH_CNTL, ih_cntl);
	/* set rptr, wptr to 0 */
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);
	rdev->ih.enabled = false;
	rdev->ih.rptr = 0;
पूर्ण

अटल व्योम r600_disable_पूर्णांकerrupt_state(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	WREG32(CP_INT_CNTL, CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	पंचांगp = RREG32(DMA_CNTL) & ~TRAP_ENABLE;
	WREG32(DMA_CNTL, पंचांगp);
	WREG32(GRBM_INT_CNTL, 0);
	WREG32(DxMODE_INT_MASK, 0);
	WREG32(D1GRPH_INTERRUPT_CONTROL, 0);
	WREG32(D2GRPH_INTERRUPT_CONTROL, 0);
	अगर (ASIC_IS_DCE3(rdev)) अणु
		WREG32(DCE3_DACA_AUTODETECT_INT_CONTROL, 0);
		WREG32(DCE3_DACB_AUTODETECT_INT_CONTROL, 0);
		पंचांगp = RREG32(DC_HPD1_INT_CONTROL) & DC_HPDx_INT_POLARITY;
		WREG32(DC_HPD1_INT_CONTROL, पंचांगp);
		पंचांगp = RREG32(DC_HPD2_INT_CONTROL) & DC_HPDx_INT_POLARITY;
		WREG32(DC_HPD2_INT_CONTROL, पंचांगp);
		पंचांगp = RREG32(DC_HPD3_INT_CONTROL) & DC_HPDx_INT_POLARITY;
		WREG32(DC_HPD3_INT_CONTROL, पंचांगp);
		पंचांगp = RREG32(DC_HPD4_INT_CONTROL) & DC_HPDx_INT_POLARITY;
		WREG32(DC_HPD4_INT_CONTROL, पंचांगp);
		अगर (ASIC_IS_DCE32(rdev)) अणु
			पंचांगp = RREG32(DC_HPD5_INT_CONTROL) & DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD5_INT_CONTROL, पंचांगp);
			पंचांगp = RREG32(DC_HPD6_INT_CONTROL) & DC_HPDx_INT_POLARITY;
			WREG32(DC_HPD6_INT_CONTROL, पंचांगp);
			पंचांगp = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0, पंचांगp);
			पंचांगp = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(HDMI0_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
			WREG32(HDMI0_AUDIO_PACKET_CONTROL, पंचांगp);
			पंचांगp = RREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
			WREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL, पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(DACA_AUTODETECT_INT_CONTROL, 0);
		WREG32(DACB_AUTODETECT_INT_CONTROL, 0);
		पंचांगp = RREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL) & DC_HOT_PLUG_DETECTx_INT_POLARITY;
		WREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL, पंचांगp);
		पंचांगp = RREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL) & DC_HOT_PLUG_DETECTx_INT_POLARITY;
		WREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL, पंचांगp);
		पंचांगp = RREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL) & DC_HOT_PLUG_DETECTx_INT_POLARITY;
		WREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL, पंचांगp);
		पंचांगp = RREG32(HDMI0_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
		WREG32(HDMI0_AUDIO_PACKET_CONTROL, पंचांगp);
		पंचांगp = RREG32(HDMI1_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
		WREG32(HDMI1_AUDIO_PACKET_CONTROL, पंचांगp);
	पूर्ण
पूर्ण

पूर्णांक r600_irq_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rb_bufsz;
	u32 पूर्णांकerrupt_cntl, ih_cntl, ih_rb_cntl;

	/* allocate ring */
	ret = r600_ih_ring_alloc(rdev);
	अगर (ret)
		वापस ret;

	/* disable irqs */
	r600_disable_पूर्णांकerrupts(rdev);

	/* init rlc */
	अगर (rdev->family >= CHIP_CEDAR)
		ret = evergreen_rlc_resume(rdev);
	अन्यथा
		ret = r600_rlc_resume(rdev);
	अगर (ret) अणु
		r600_ih_ring_fini(rdev);
		वापस ret;
	पूर्ण

	/* setup पूर्णांकerrupt control */
	/* set dummy पढ़ो address to dummy page address */
	WREG32(INTERRUPT_CNTL2, rdev->dummy_page.addr >> 8);
	पूर्णांकerrupt_cntl = RREG32(INTERRUPT_CNTL);
	/* IH_DUMMY_RD_OVERRIDE=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * IH_DUMMY_RD_OVERRIDE=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl &= ~IH_DUMMY_RD_OVERRIDE;
	/* IH_REQ_NONSNOOP_EN=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl &= ~IH_REQ_NONSNOOP_EN;
	WREG32(INTERRUPT_CNTL, पूर्णांकerrupt_cntl);

	WREG32(IH_RB_BASE, rdev->ih.gpu_addr >> 8);
	rb_bufsz = order_base_2(rdev->ih.ring_size / 4);

	ih_rb_cntl = (IH_WPTR_OVERFLOW_ENABLE |
		      IH_WPTR_OVERFLOW_CLEAR |
		      (rb_bufsz << 1));

	अगर (rdev->wb.enabled)
		ih_rb_cntl |= IH_WPTR_WRITEBACK_ENABLE;

	/* set the ग_लिखोback address whether it's enabled or not */
	WREG32(IH_RB_WPTR_ADDR_LO, (rdev->wb.gpu_addr + R600_WB_IH_WPTR_OFFSET) & 0xFFFFFFFC);
	WREG32(IH_RB_WPTR_ADDR_HI, upper_32_bits(rdev->wb.gpu_addr + R600_WB_IH_WPTR_OFFSET) & 0xFF);

	WREG32(IH_RB_CNTL, ih_rb_cntl);

	/* set rptr, wptr to 0 */
	WREG32(IH_RB_RPTR, 0);
	WREG32(IH_RB_WPTR, 0);

	/* Default settings क्रम IH_CNTL (disabled at first) */
	ih_cntl = MC_WRREQ_CREDIT(0x10) | MC_WR_CLEAN_CNT(0x10);
	/* RPTR_REARM only works अगर msi's are enabled */
	अगर (rdev->msi_enabled)
		ih_cntl |= RPTR_REARM;
	WREG32(IH_CNTL, ih_cntl);

	/* क्रमce the active पूर्णांकerrupt state to all disabled */
	अगर (rdev->family >= CHIP_CEDAR)
		evergreen_disable_पूर्णांकerrupt_state(rdev);
	अन्यथा
		r600_disable_पूर्णांकerrupt_state(rdev);

	/* at this poपूर्णांक everything should be setup correctly to enable master */
	pci_set_master(rdev->pdev);

	/* enable irqs */
	r600_enable_पूर्णांकerrupts(rdev);

	वापस ret;
पूर्ण

व्योम r600_irq_suspend(काष्ठा radeon_device *rdev)
अणु
	r600_irq_disable(rdev);
	r600_rlc_stop(rdev);
पूर्ण

व्योम r600_irq_fini(काष्ठा radeon_device *rdev)
अणु
	r600_irq_suspend(rdev);
	r600_ih_ring_fini(rdev);
पूर्ण

पूर्णांक r600_irq_set(काष्ठा radeon_device *rdev)
अणु
	u32 cp_पूर्णांक_cntl = CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE;
	u32 mode_पूर्णांक = 0;
	u32 hpd1, hpd2, hpd3, hpd4 = 0, hpd5 = 0, hpd6 = 0;
	u32 grbm_पूर्णांक_cntl = 0;
	u32 hdmi0, hdmi1;
	u32 dma_cntl;
	u32 thermal_पूर्णांक = 0;

	अगर (!rdev->irq.installed) अणु
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		वापस -EINVAL;
	पूर्ण
	/* करोn't enable anything अगर the ih is disabled */
	अगर (!rdev->ih.enabled) अणु
		r600_disable_पूर्णांकerrupts(rdev);
		/* क्रमce the active पूर्णांकerrupt state to all disabled */
		r600_disable_पूर्णांकerrupt_state(rdev);
		वापस 0;
	पूर्ण

	अगर (ASIC_IS_DCE3(rdev)) अणु
		hpd1 = RREG32(DC_HPD1_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd2 = RREG32(DC_HPD2_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd3 = RREG32(DC_HPD3_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd4 = RREG32(DC_HPD4_INT_CONTROL) & ~DC_HPDx_INT_EN;
		अगर (ASIC_IS_DCE32(rdev)) अणु
			hpd5 = RREG32(DC_HPD5_INT_CONTROL) & ~DC_HPDx_INT_EN;
			hpd6 = RREG32(DC_HPD6_INT_CONTROL) & ~DC_HPDx_INT_EN;
			hdmi0 = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
			hdmi1 = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
		पूर्ण अन्यथा अणु
			hdmi0 = RREG32(HDMI0_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
			hdmi1 = RREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
		पूर्ण
	पूर्ण अन्यथा अणु
		hpd1 = RREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd2 = RREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd3 = RREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hdmi0 = RREG32(HDMI0_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
		hdmi1 = RREG32(HDMI1_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
	पूर्ण

	dma_cntl = RREG32(DMA_CNTL) & ~TRAP_ENABLE;

	अगर ((rdev->family > CHIP_R600) && (rdev->family < CHIP_RV770)) अणु
		thermal_पूर्णांक = RREG32(CG_THERMAL_INT) &
			~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_RV770) अणु
		thermal_पूर्णांक = RREG32(RV770_CG_THERMAL_INT) &
			~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);
	पूर्ण
	अगर (rdev->irq.dpm_thermal) अणु
		DRM_DEBUG("dpm thermal\n");
		thermal_पूर्णांक |= THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW;
	पूर्ण

	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
		DRM_DEBUG("r600_irq_set: sw int\n");
		cp_पूर्णांक_cntl |= RB_INT_ENABLE;
		cp_पूर्णांक_cntl |= TIME_STAMP_INT_ENABLE;
	पूर्ण

	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[R600_RING_TYPE_DMA_INDEX])) अणु
		DRM_DEBUG("r600_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	पूर्ण

	अगर (rdev->irq.crtc_vblank_पूर्णांक[0] ||
	    atomic_पढ़ो(&rdev->irq.pflip[0])) अणु
		DRM_DEBUG("r600_irq_set: vblank 0\n");
		mode_पूर्णांक |= D1MODE_VBLANK_INT_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[1] ||
	    atomic_पढ़ो(&rdev->irq.pflip[1])) अणु
		DRM_DEBUG("r600_irq_set: vblank 1\n");
		mode_पूर्णांक |= D2MODE_VBLANK_INT_MASK;
	पूर्ण
	अगर (rdev->irq.hpd[0]) अणु
		DRM_DEBUG("r600_irq_set: hpd 1\n");
		hpd1 |= DC_HPDx_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[1]) अणु
		DRM_DEBUG("r600_irq_set: hpd 2\n");
		hpd2 |= DC_HPDx_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[2]) अणु
		DRM_DEBUG("r600_irq_set: hpd 3\n");
		hpd3 |= DC_HPDx_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[3]) अणु
		DRM_DEBUG("r600_irq_set: hpd 4\n");
		hpd4 |= DC_HPDx_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[4]) अणु
		DRM_DEBUG("r600_irq_set: hpd 5\n");
		hpd5 |= DC_HPDx_INT_EN;
	पूर्ण
	अगर (rdev->irq.hpd[5]) अणु
		DRM_DEBUG("r600_irq_set: hpd 6\n");
		hpd6 |= DC_HPDx_INT_EN;
	पूर्ण
	अगर (rdev->irq.afmt[0]) अणु
		DRM_DEBUG("r600_irq_set: hdmi 0\n");
		hdmi0 |= HDMI0_AZ_FORMAT_WTRIG_MASK;
	पूर्ण
	अगर (rdev->irq.afmt[1]) अणु
		DRM_DEBUG("r600_irq_set: hdmi 0\n");
		hdmi1 |= HDMI0_AZ_FORMAT_WTRIG_MASK;
	पूर्ण

	WREG32(CP_INT_CNTL, cp_पूर्णांक_cntl);
	WREG32(DMA_CNTL, dma_cntl);
	WREG32(DxMODE_INT_MASK, mode_पूर्णांक);
	WREG32(D1GRPH_INTERRUPT_CONTROL, DxGRPH_PFLIP_INT_MASK);
	WREG32(D2GRPH_INTERRUPT_CONTROL, DxGRPH_PFLIP_INT_MASK);
	WREG32(GRBM_INT_CNTL, grbm_पूर्णांक_cntl);
	अगर (ASIC_IS_DCE3(rdev)) अणु
		WREG32(DC_HPD1_INT_CONTROL, hpd1);
		WREG32(DC_HPD2_INT_CONTROL, hpd2);
		WREG32(DC_HPD3_INT_CONTROL, hpd3);
		WREG32(DC_HPD4_INT_CONTROL, hpd4);
		अगर (ASIC_IS_DCE32(rdev)) अणु
			WREG32(DC_HPD5_INT_CONTROL, hpd5);
			WREG32(DC_HPD6_INT_CONTROL, hpd6);
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0, hdmi0);
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1, hdmi1);
		पूर्ण अन्यथा अणु
			WREG32(HDMI0_AUDIO_PACKET_CONTROL, hdmi0);
			WREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL, hdmi1);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL, hpd1);
		WREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL, hpd2);
		WREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL, hpd3);
		WREG32(HDMI0_AUDIO_PACKET_CONTROL, hdmi0);
		WREG32(HDMI1_AUDIO_PACKET_CONTROL, hdmi1);
	पूर्ण
	अगर ((rdev->family > CHIP_R600) && (rdev->family < CHIP_RV770)) अणु
		WREG32(CG_THERMAL_INT, thermal_पूर्णांक);
	पूर्ण अन्यथा अगर (rdev->family >= CHIP_RV770) अणु
		WREG32(RV770_CG_THERMAL_INT, thermal_पूर्णांक);
	पूर्ण

	/* posting पढ़ो */
	RREG32(R_000E50_SRBM_STATUS);

	वापस 0;
पूर्ण

अटल व्योम r600_irq_ack(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	अगर (ASIC_IS_DCE3(rdev)) अणु
		rdev->irq.stat_regs.r600.disp_पूर्णांक = RREG32(DCE3_DISP_INTERRUPT_STATUS);
		rdev->irq.stat_regs.r600.disp_पूर्णांक_cont = RREG32(DCE3_DISP_INTERRUPT_STATUS_CONTINUE);
		rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 = RREG32(DCE3_DISP_INTERRUPT_STATUS_CONTINUE2);
		अगर (ASIC_IS_DCE32(rdev)) अणु
			rdev->irq.stat_regs.r600.hdmi0_status = RREG32(AFMT_STATUS + DCE3_HDMI_OFFSET0);
			rdev->irq.stat_regs.r600.hdmi1_status = RREG32(AFMT_STATUS + DCE3_HDMI_OFFSET1);
		पूर्ण अन्यथा अणु
			rdev->irq.stat_regs.r600.hdmi0_status = RREG32(HDMI0_STATUS);
			rdev->irq.stat_regs.r600.hdmi1_status = RREG32(DCE3_HDMI1_STATUS);
		पूर्ण
	पूर्ण अन्यथा अणु
		rdev->irq.stat_regs.r600.disp_पूर्णांक = RREG32(DISP_INTERRUPT_STATUS);
		rdev->irq.stat_regs.r600.disp_पूर्णांक_cont = RREG32(DISP_INTERRUPT_STATUS_CONTINUE);
		rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 = 0;
		rdev->irq.stat_regs.r600.hdmi0_status = RREG32(HDMI0_STATUS);
		rdev->irq.stat_regs.r600.hdmi1_status = RREG32(HDMI1_STATUS);
	पूर्ण
	rdev->irq.stat_regs.r600.d1grph_पूर्णांक = RREG32(D1GRPH_INTERRUPT_STATUS);
	rdev->irq.stat_regs.r600.d2grph_पूर्णांक = RREG32(D2GRPH_INTERRUPT_STATUS);

	अगर (rdev->irq.stat_regs.r600.d1grph_पूर्णांक & DxGRPH_PFLIP_INT_OCCURRED)
		WREG32(D1GRPH_INTERRUPT_STATUS, DxGRPH_PFLIP_INT_CLEAR);
	अगर (rdev->irq.stat_regs.r600.d2grph_पूर्णांक & DxGRPH_PFLIP_INT_OCCURRED)
		WREG32(D2GRPH_INTERRUPT_STATUS, DxGRPH_PFLIP_INT_CLEAR);
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D1_VBLANK_INTERRUPT)
		WREG32(D1MODE_VBLANK_STATUS, DxMODE_VBLANK_ACK);
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D1_VLINE_INTERRUPT)
		WREG32(D1MODE_VLINE_STATUS, DxMODE_VLINE_ACK);
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D2_VBLANK_INTERRUPT)
		WREG32(D2MODE_VBLANK_STATUS, DxMODE_VBLANK_ACK);
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D2_VLINE_INTERRUPT)
		WREG32(D2MODE_VLINE_STATUS, DxMODE_VLINE_ACK);
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक & DC_HPD1_INTERRUPT) अणु
		अगर (ASIC_IS_DCE3(rdev)) अणु
			पंचांगp = RREG32(DC_HPD1_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HPD1_INT_CONTROL, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL, पंचांगp);
		पूर्ण
	पूर्ण
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक & DC_HPD2_INTERRUPT) अणु
		अगर (ASIC_IS_DCE3(rdev)) अणु
			पंचांगp = RREG32(DC_HPD2_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HPD2_INT_CONTROL, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL, पंचांगp);
		पूर्ण
	पूर्ण
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक_cont & DC_HPD3_INTERRUPT) अणु
		अगर (ASIC_IS_DCE3(rdev)) अणु
			पंचांगp = RREG32(DC_HPD3_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HPD3_INT_CONTROL, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL, पंचांगp);
		पूर्ण
	पूर्ण
	अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक_cont & DC_HPD4_INTERRUPT) अणु
		पंचांगp = RREG32(DC_HPD4_INT_CONTROL);
		पंचांगp |= DC_HPDx_INT_ACK;
		WREG32(DC_HPD4_INT_CONTROL, पंचांगp);
	पूर्ण
	अगर (ASIC_IS_DCE32(rdev)) अणु
		अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 & DC_HPD5_INTERRUPT) अणु
			पंचांगp = RREG32(DC_HPD5_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HPD5_INT_CONTROL, पंचांगp);
		पूर्ण
		अगर (rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 & DC_HPD6_INTERRUPT) अणु
			पंचांगp = RREG32(DC_HPD6_INT_CONTROL);
			पंचांगp |= DC_HPDx_INT_ACK;
			WREG32(DC_HPD6_INT_CONTROL, पंचांगp);
		पूर्ण
		अगर (rdev->irq.stat_regs.r600.hdmi0_status & AFMT_AZ_FORMAT_WTRIG) अणु
			पंचांगp = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0);
			पंचांगp |= AFMT_AZ_FORMAT_WTRIG_ACK;
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0, पंचांगp);
		पूर्ण
		अगर (rdev->irq.stat_regs.r600.hdmi1_status & AFMT_AZ_FORMAT_WTRIG) अणु
			पंचांगp = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1);
			पंचांगp |= AFMT_AZ_FORMAT_WTRIG_ACK;
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1, पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rdev->irq.stat_regs.r600.hdmi0_status & HDMI0_AZ_FORMAT_WTRIG) अणु
			पंचांगp = RREG32(HDMI0_AUDIO_PACKET_CONTROL);
			पंचांगp |= HDMI0_AZ_FORMAT_WTRIG_ACK;
			WREG32(HDMI0_AUDIO_PACKET_CONTROL, पंचांगp);
		पूर्ण
		अगर (rdev->irq.stat_regs.r600.hdmi1_status & HDMI0_AZ_FORMAT_WTRIG) अणु
			अगर (ASIC_IS_DCE3(rdev)) अणु
				पंचांगp = RREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL);
				पंचांगp |= HDMI0_AZ_FORMAT_WTRIG_ACK;
				WREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL, पंचांगp);
			पूर्ण अन्यथा अणु
				पंचांगp = RREG32(HDMI1_AUDIO_PACKET_CONTROL);
				पंचांगp |= HDMI0_AZ_FORMAT_WTRIG_ACK;
				WREG32(HDMI1_AUDIO_PACKET_CONTROL, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम r600_irq_disable(काष्ठा radeon_device *rdev)
अणु
	r600_disable_पूर्णांकerrupts(rdev);
	/* Wait and acknowledge irq */
	mdelay(1);
	r600_irq_ack(rdev);
	r600_disable_पूर्णांकerrupt_state(rdev);
पूर्ण

अटल u32 r600_get_ih_wptr(काष्ठा radeon_device *rdev)
अणु
	u32 wptr, पंचांगp;

	अगर (rdev->wb.enabled)
		wptr = le32_to_cpu(rdev->wb.wb[R600_WB_IH_WPTR_OFFSET/4]);
	अन्यथा
		wptr = RREG32(IH_RB_WPTR);

	अगर (wptr & RB_OVERFLOW) अणु
		wptr &= ~RB_OVERFLOW;
		/* When a ring buffer overflow happen start parsing पूर्णांकerrupt
		 * from the last not overwritten vector (wptr + 16). Hopefully
		 * this should allow us to catchup.
		 */
		dev_warn(rdev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptr, rdev->ih.rptr, (wptr + 16) & rdev->ih.ptr_mask);
		rdev->ih.rptr = (wptr + 16) & rdev->ih.ptr_mask;
		पंचांगp = RREG32(IH_RB_CNTL);
		पंचांगp |= IH_WPTR_OVERFLOW_CLEAR;
		WREG32(IH_RB_CNTL, पंचांगp);
	पूर्ण
	वापस (wptr & rdev->ih.ptr_mask);
पूर्ण

/*        r600 IV Ring
 * Each IV ring entry is 128 bits:
 * [7:0]    - पूर्णांकerrupt source id
 * [31:8]   - reserved
 * [59:32]  - पूर्णांकerrupt source data
 * [127:60]  - reserved
 *
 * The basic पूर्णांकerrupt vector entries
 * are decoded as follows:
 * src_id  src_data  description
 *      1         0  D1 Vblank
 *      1         1  D1 Vline
 *      5         0  D2 Vblank
 *      5         1  D2 Vline
 *     19         0  FP Hot plug detection A
 *     19         1  FP Hot plug detection B
 *     19         2  DAC A स्वतः-detection
 *     19         3  DAC B स्वतः-detection
 *     21         4  HDMI block A
 *     21         5  HDMI block B
 *    176         -  CP_INT RB
 *    177         -  CP_INT IB1
 *    178         -  CP_INT IB2
 *    181         -  EOP Interrupt
 *    233         -  GUI Idle
 *
 * Note, these are based on r600 and may need to be
 * adjusted or added to on newer asics
 */

पूर्णांक r600_irq_process(काष्ठा radeon_device *rdev)
अणु
	u32 wptr;
	u32 rptr;
	u32 src_id, src_data;
	u32 ring_index;
	bool queue_hotplug = false;
	bool queue_hdmi = false;
	bool queue_thermal = false;

	अगर (!rdev->ih.enabled || rdev->shutकरोwn)
		वापस IRQ_NONE;

	/* No MSIs, need a dummy पढ़ो to flush PCI DMAs */
	अगर (!rdev->msi_enabled)
		RREG32(IH_RB_WPTR);

	wptr = r600_get_ih_wptr(rdev);

restart_ih:
	/* is somebody अन्यथा alपढ़ोy processing irqs? */
	अगर (atomic_xchg(&rdev->ih.lock, 1))
		वापस IRQ_NONE;

	rptr = rdev->ih.rptr;
	DRM_DEBUG("r600_irq_process start: rptr %d, wptr %d\n", rptr, wptr);

	/* Order पढ़ोing of wptr vs. पढ़ोing of IH ring data */
	rmb();

	/* display पूर्णांकerrupts */
	r600_irq_ack(rdev);

	जबतक (rptr != wptr) अणु
		/* wptr/rptr are in bytes! */
		ring_index = rptr / 4;
		src_id = le32_to_cpu(rdev->ih.ring[ring_index]) & 0xff;
		src_data = le32_to_cpu(rdev->ih.ring[ring_index + 1]) & 0xfffffff;

		चयन (src_id) अणु
		हाल 1: /* D1 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D1 vblank */
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D1_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: D1 vblank - IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[0]) अणु
					drm_handle_vblank(rdev->ddev, 0);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[0]))
					radeon_crtc_handle_vblank(rdev, 0);
				rdev->irq.stat_regs.r600.disp_पूर्णांक &= ~LB_D1_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D1 vblank\n");

				अवरोध;
			हाल 1: /* D1 vline */
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D1_VLINE_INTERRUPT))
				    DRM_DEBUG("IH: D1 vline - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक &= ~LB_D1_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D1 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 5: /* D2 vblank/vline */
			चयन (src_data) अणु
			हाल 0: /* D2 vblank */
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D2_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: D2 vblank - IH event w/o asserted irq bit?\n");

				अगर (rdev->irq.crtc_vblank_पूर्णांक[1]) अणु
					drm_handle_vblank(rdev->ddev, 1);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				पूर्ण
				अगर (atomic_पढ़ो(&rdev->irq.pflip[1]))
					radeon_crtc_handle_vblank(rdev, 1);
				rdev->irq.stat_regs.r600.disp_पूर्णांक &= ~LB_D2_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D2 vblank\n");

				अवरोध;
			हाल 1: /* D1 vline */
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक & LB_D2_VLINE_INTERRUPT))
					DRM_DEBUG("IH: D2 vline - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक &= ~LB_D2_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D2 vline\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 9: /* D1 pflip */
			DRM_DEBUG("IH: D1 flip\n");
			अगर (radeon_use_pflipirq > 0)
				radeon_crtc_handle_flip(rdev, 0);
			अवरोध;
		हाल 11: /* D2 pflip */
			DRM_DEBUG("IH: D2 flip\n");
			अगर (radeon_use_pflipirq > 0)
				radeon_crtc_handle_flip(rdev, 1);
			अवरोध;
		हाल 19: /* HPD/DAC hotplug */
			चयन (src_data) अणु
			हाल 0:
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक & DC_HPD1_INTERRUPT))
					DRM_DEBUG("IH: HPD1 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक &= ~DC_HPD1_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD1\n");
				अवरोध;
			हाल 1:
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक & DC_HPD2_INTERRUPT))
					DRM_DEBUG("IH: HPD2 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक &= ~DC_HPD2_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD2\n");
				अवरोध;
			हाल 4:
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक_cont & DC_HPD3_INTERRUPT))
					DRM_DEBUG("IH: HPD3 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक_cont &= ~DC_HPD3_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD3\n");
				अवरोध;
			हाल 5:
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक_cont & DC_HPD4_INTERRUPT))
					DRM_DEBUG("IH: HPD4 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक_cont &= ~DC_HPD4_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD4\n");
				अवरोध;
			हाल 10:
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 & DC_HPD5_INTERRUPT))
					DRM_DEBUG("IH: HPD5 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 &= ~DC_HPD5_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD5\n");
				अवरोध;
			हाल 12:
				अगर (!(rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 & DC_HPD6_INTERRUPT))
					DRM_DEBUG("IH: HPD6 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.disp_पूर्णांक_cont2 &= ~DC_HPD6_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD6\n");

				अवरोध;
			शेष:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 21: /* hdmi */
			चयन (src_data) अणु
			हाल 4:
				अगर (!(rdev->irq.stat_regs.r600.hdmi0_status & HDMI0_AZ_FORMAT_WTRIG))
					DRM_DEBUG("IH: HDMI0 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.hdmi0_status &= ~HDMI0_AZ_FORMAT_WTRIG;
				queue_hdmi = true;
				DRM_DEBUG("IH: HDMI0\n");

				अवरोध;
			हाल 5:
				अगर (!(rdev->irq.stat_regs.r600.hdmi1_status & HDMI0_AZ_FORMAT_WTRIG))
					DRM_DEBUG("IH: HDMI1 - IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.r600.hdmi1_status &= ~HDMI0_AZ_FORMAT_WTRIG;
				queue_hdmi = true;
				DRM_DEBUG("IH: HDMI1\n");

				अवरोध;
			शेष:
				DRM_ERROR("Unhandled interrupt: %d %d\n", src_id, src_data);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 124: /* UVD */
			DRM_DEBUG("IH: UVD int: 0x%08x\n", src_data);
			radeon_fence_process(rdev, R600_RING_TYPE_UVD_INDEX);
			अवरोध;
		हाल 176: /* CP_INT in ring buffer */
		हाल 177: /* CP_INT in IB1 */
		हाल 178: /* CP_INT in IB2 */
			DRM_DEBUG("IH: CP int: 0x%08x\n", src_data);
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			अवरोध;
		हाल 181: /* CP EOP event */
			DRM_DEBUG("IH: CP EOP\n");
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			अवरोध;
		हाल 224: /* DMA trap event */
			DRM_DEBUG("IH: DMA trap\n");
			radeon_fence_process(rdev, R600_RING_TYPE_DMA_INDEX);
			अवरोध;
		हाल 230: /* thermal low to high */
			DRM_DEBUG("IH: thermal low to high\n");
			rdev->pm.dpm.thermal.high_to_low = false;
			queue_thermal = true;
			अवरोध;
		हाल 231: /* thermal high to low */
			DRM_DEBUG("IH: thermal high to low\n");
			rdev->pm.dpm.thermal.high_to_low = true;
			queue_thermal = true;
			अवरोध;
		हाल 233: /* GUI IDLE */
			DRM_DEBUG("IH: GUI idle\n");
			अवरोध;
		शेष:
			DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
			अवरोध;
		पूर्ण

		/* wptr/rptr are in bytes! */
		rptr += 16;
		rptr &= rdev->ih.ptr_mask;
		WREG32(IH_RB_RPTR, rptr);
	पूर्ण
	अगर (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	अगर (queue_hdmi)
		schedule_work(&rdev->audio_work);
	अगर (queue_thermal && rdev->pm.dpm_enabled)
		schedule_work(&rdev->pm.dpm.thermal.work);
	rdev->ih.rptr = rptr;
	atomic_set(&rdev->ih.lock, 0);

	/* make sure wptr hasn't changed जबतक processing */
	wptr = r600_get_ih_wptr(rdev);
	अगर (wptr != rptr)
		जाओ restart_ih;

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक r600_debugfs_mc_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;

	DREG32_SYS(m, rdev, R_000E50_SRBM_STATUS);
	DREG32_SYS(m, rdev, VM_L2_STATUS);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(r600_debugfs_mc_info);
#पूर्ण_अगर

अटल व्योम r600_debugfs_mc_info_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("r600_mc_info", 0444, root, rdev,
			    &r600_debugfs_mc_info_fops);

#पूर्ण_अगर
पूर्ण

/**
 * r600_mmio_hdp_flush - flush Host Data Path cache via MMIO
 * @rdev: radeon device काष्ठाure
 *
 * Some R6XX/R7XX करोn't seem to take पूर्णांकo account HDP flushes perक्रमmed
 * through the ring buffer. This leads to corruption in rendering, see
 * http://bugzilla.kernel.org/show_bug.cgi?id=15186 . To aव्योम this, we
 * directly perक्रमm the HDP flush by writing the रेजिस्टर through MMIO.
 */
व्योम r600_mmio_hdp_flush(काष्ठा radeon_device *rdev)
अणु
	/* r7xx hw bug.  ग_लिखो to HDP_DEBUG1 followed by fb पढ़ो
	 * rather than ग_लिखो to HDP_REG_COHERENCY_FLUSH_CNTL.
	 * This seems to cause problems on some AGP cards. Just use the old
	 * method क्रम them.
	 */
	अगर ((rdev->family >= CHIP_RV770) && (rdev->family <= CHIP_RV740) &&
	    rdev->vram_scratch.ptr && !(rdev->flags & RADEON_IS_AGP)) अणु
		व्योम __iomem *ptr = (व्योम *)rdev->vram_scratch.ptr;

		WREG32(HDP_DEBUG1, 0);
		पढ़ोl((व्योम __iomem *)ptr);
	पूर्ण अन्यथा
		WREG32(R_005480_HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);
पूर्ण

व्योम r600_set_pcie_lanes(काष्ठा radeon_device *rdev, पूर्णांक lanes)
अणु
	u32 link_width_cntl, mask;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	/* x2 cards have a special sequence */
	अगर (ASIC_IS_X2(rdev))
		वापस;

	radeon_gui_idle(rdev);

	चयन (lanes) अणु
	हाल 0:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X0;
		अवरोध;
	हाल 1:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X1;
		अवरोध;
	हाल 2:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X2;
		अवरोध;
	हाल 4:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X4;
		अवरोध;
	हाल 8:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X8;
		अवरोध;
	हाल 12:
		/* not actually supported */
		mask = RADEON_PCIE_LC_LINK_WIDTH_X12;
		अवरोध;
	हाल 16:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X16;
		अवरोध;
	शेष:
		DRM_ERROR("invalid pcie lane request: %d\n", lanes);
		वापस;
	पूर्ण

	link_width_cntl = RREG32_PCIE_PORT(RADEON_PCIE_LC_LINK_WIDTH_CNTL);
	link_width_cntl &= ~RADEON_PCIE_LC_LINK_WIDTH_MASK;
	link_width_cntl |= mask << RADEON_PCIE_LC_LINK_WIDTH_SHIFT;
	link_width_cntl |= (RADEON_PCIE_LC_RECONFIG_NOW |
			    R600_PCIE_LC_RECONFIG_ARC_MISSING_ESCAPE);

	WREG32_PCIE_PORT(RADEON_PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
पूर्ण

पूर्णांक r600_get_pcie_lanes(काष्ठा radeon_device *rdev)
अणु
	u32 link_width_cntl;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस 0;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस 0;

	/* x2 cards have a special sequence */
	अगर (ASIC_IS_X2(rdev))
		वापस 0;

	radeon_gui_idle(rdev);

	link_width_cntl = RREG32_PCIE_PORT(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

	चयन ((link_width_cntl & RADEON_PCIE_LC_LINK_WIDTH_RD_MASK) >> RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT) अणु
	हाल RADEON_PCIE_LC_LINK_WIDTH_X1:
		वापस 1;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X2:
		वापस 2;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X4:
		वापस 4;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X8:
		वापस 8;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X12:
		/* not actually supported */
		वापस 12;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X0:
	हाल RADEON_PCIE_LC_LINK_WIDTH_X16:
	शेष:
		वापस 16;
	पूर्ण
पूर्ण

अटल व्योम r600_pcie_gen2_enable(काष्ठा radeon_device *rdev)
अणु
	u32 link_width_cntl, lanes, speed_cntl, training_cntl, पंचांगp;
	u16 link_cntl2;

	अगर (radeon_pcie_gen2 == 0)
		वापस;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	/* x2 cards have a special sequence */
	अगर (ASIC_IS_X2(rdev))
		वापस;

	/* only RV6xx+ chips are supported */
	अगर (rdev->family <= CHIP_R600)
		वापस;

	अगर ((rdev->pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT) &&
		(rdev->pdev->bus->max_bus_speed != PCIE_SPEED_8_0GT))
		वापस;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर (speed_cntl & LC_CURRENT_DATA_RATE) अणु
		DRM_INFO("PCIE gen 2 link speeds already enabled\n");
		वापस;
	पूर्ण

	DRM_INFO("enabling PCIE gen 2 link speeds, disable with radeon.pcie_gen2=0\n");

	/* 55 nm r6xx asics */
	अगर ((rdev->family == CHIP_RV670) ||
	    (rdev->family == CHIP_RV620) ||
	    (rdev->family == CHIP_RV635)) अणु
		/* advertise upconfig capability */
		link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
		link_width_cntl &= ~LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
		link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
		अगर (link_width_cntl & LC_RENEGOTIATION_SUPPORT) अणु
			lanes = (link_width_cntl & LC_LINK_WIDTH_RD_MASK) >> LC_LINK_WIDTH_RD_SHIFT;
			link_width_cntl &= ~(LC_LINK_WIDTH_MASK |
					     LC_RECONFIG_ARC_MISSING_ESCAPE);
			link_width_cntl |= lanes | LC_RECONFIG_NOW | LC_RENEGOTIATE_EN;
			WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
		पूर्ण अन्यथा अणु
			link_width_cntl |= LC_UPCONFIGURE_DIS;
			WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
		पूर्ण
	पूर्ण

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर ((speed_cntl & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (speed_cntl & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु

		/* 55 nm r6xx asics */
		अगर ((rdev->family == CHIP_RV670) ||
		    (rdev->family == CHIP_RV620) ||
		    (rdev->family == CHIP_RV635)) अणु
			WREG32(MM_CFGREGS_CNTL, 0x8);
			link_cntl2 = RREG32(0x4088);
			WREG32(MM_CFGREGS_CNTL, 0);
			/* not supported yet */
			अगर (link_cntl2 & SELECTABLE_DEEMPHASIS)
				वापस;
		पूर्ण

		speed_cntl &= ~LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK;
		speed_cntl |= (0x3 << LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_SHIFT);
		speed_cntl &= ~LC_VOLTAGE_TIMER_SEL_MASK;
		speed_cntl &= ~LC_FORCE_DIS_HW_SPEED_CHANGE;
		speed_cntl |= LC_FORCE_EN_HW_SPEED_CHANGE;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

		पंचांगp = RREG32(0x541c);
		WREG32(0x541c, पंचांगp | 0x8);
		WREG32(MM_CFGREGS_CNTL, MM_WR_TO_CFG_EN);
		link_cntl2 = RREG16(0x4088);
		link_cntl2 &= ~TARGET_LINK_SPEED_MASK;
		link_cntl2 |= 0x2;
		WREG16(0x4088, link_cntl2);
		WREG32(MM_CFGREGS_CNTL, 0);

		अगर ((rdev->family == CHIP_RV670) ||
		    (rdev->family == CHIP_RV620) ||
		    (rdev->family == CHIP_RV635)) अणु
			training_cntl = RREG32_PCIE_PORT(PCIE_LC_TRAINING_CNTL);
			training_cntl &= ~LC_POINT_7_PLUS_EN;
			WREG32_PCIE_PORT(PCIE_LC_TRAINING_CNTL, training_cntl);
		पूर्ण अन्यथा अणु
			speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
			speed_cntl &= ~LC_TARGET_LINK_SPEED_OVERRIDE_EN;
			WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);
		पूर्ण

		speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
		speed_cntl |= LC_GEN2_EN_STRAP;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, speed_cntl);

	पूर्ण अन्यथा अणु
		link_width_cntl = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
		/* XXX: only disable it अगर gen1 bridge venकरोr == 0x111d or 0x1106 */
		अगर (1)
			link_width_cntl |= LC_UPCONFIGURE_DIS;
		अन्यथा
			link_width_cntl &= ~LC_UPCONFIGURE_DIS;
		WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	पूर्ण
पूर्ण

/**
 * r600_get_gpu_घड़ी_counter - वापस GPU घड़ी counter snapshot
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Fetches a GPU घड़ी counter snapshot (R6xx-cayman).
 * Returns the 64 bit घड़ी counter snapshot.
 */
uपूर्णांक64_t r600_get_gpu_घड़ी_counter(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t घड़ी;

	mutex_lock(&rdev->gpu_घड़ी_mutex);
	WREG32(RLC_CAPTURE_GPU_CLOCK_COUNT, 1);
	घड़ी = (uपूर्णांक64_t)RREG32(RLC_GPU_CLOCK_COUNT_LSB) |
		((uपूर्णांक64_t)RREG32(RLC_GPU_CLOCK_COUNT_MSB) << 32ULL);
	mutex_unlock(&rdev->gpu_घड़ी_mutex);
	वापस घड़ी;
पूर्ण
