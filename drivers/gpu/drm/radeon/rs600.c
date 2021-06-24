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
/* RS600 / Radeon X1250/X1270 पूर्णांकegrated GPU
 *
 * This file gather function specअगरic to RS600 which is the IGP of
 * the X1250/X1270 family supporting पूर्णांकel CPU (जबतक RS690/RS740
 * is the X1250/X1270 supporting AMD CPU). The display engine are
 * the avivo one, bios is an atombios, 3D block are the one of the
 * R4XX family. The GART is dअगरferent from the RS400 one and is very
 * बंद to the one of the R600 family (R600 likely being an evolution
 * of the RS600 GART block).
 */

#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_vblank.h>

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "rs600_reg_safe.h"
#समावेश "rs600d.h"

अटल व्योम rs600_gpu_init(काष्ठा radeon_device *rdev);
पूर्णांक rs600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

अटल स्थिर u32 crtc_offsets[2] =
अणु
	0,
	AVIVO_D2CRTC_H_TOTAL - AVIVO_D1CRTC_H_TOTAL
पूर्ण;

अटल bool avivo_is_in_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अगर (RREG32(AVIVO_D1CRTC_STATUS + crtc_offsets[crtc]) & AVIVO_D1CRTC_V_BLANK)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool avivo_is_counter_moving(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	u32 pos1, pos2;

	pos1 = RREG32(AVIVO_D1CRTC_STATUS_POSITION + crtc_offsets[crtc]);
	pos2 = RREG32(AVIVO_D1CRTC_STATUS_POSITION + crtc_offsets[crtc]);

	अगर (pos1 != pos2)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * avivo_रुको_क्रम_vblank - vblank रुको asic callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc: crtc to रुको क्रम vblank on
 *
 * Wait क्रम vblank on the requested crtc (r5xx-r7xx).
 */
व्योम avivo_रुको_क्रम_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अचिन्हित i = 0;

	अगर (crtc >= rdev->num_crtc)
		वापस;

	अगर (!(RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[crtc]) & AVIVO_CRTC_EN))
		वापस;

	/* depending on when we hit vblank, we may be बंद to active; अगर so,
	 * रुको क्रम another frame.
	 */
	जबतक (avivo_is_in_vblank(rdev, crtc)) अणु
		अगर (i++ % 100 == 0) अणु
			अगर (!avivo_is_counter_moving(rdev, crtc))
				अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!avivo_is_in_vblank(rdev, crtc)) अणु
		अगर (i++ % 100 == 0) अणु
			अगर (!avivo_is_counter_moving(rdev, crtc))
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rs600_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc_id, u64 crtc_base, bool async)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	u32 पंचांगp = RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset);
	पूर्णांक i;

	/* Lock the graphics update lock */
	पंचांगp |= AVIVO_D1GRPH_UPDATE_LOCK;
	WREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset, पंचांगp);

	/* update the scanout addresses */
	WREG32(AVIVO_D1GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset,
	       async ? AVIVO_D1GRPH_SURFACE_UPDATE_H_RETRACE_EN : 0);
	WREG32(AVIVO_D1GRPH_SECONDARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)crtc_base);
	WREG32(AVIVO_D1GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)crtc_base);

	/* Wait क्रम update_pending to go high. */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset) & AVIVO_D1GRPH_SURFACE_UPDATE_PENDING)
			अवरोध;
		udelay(1);
	पूर्ण
	DRM_DEBUG("Update pending now high. Unlocking vupdate_lock.\n");

	/* Unlock the lock, so द्विगुन-buffering can take place inside vblank */
	पंचांगp &= ~AVIVO_D1GRPH_UPDATE_LOCK;
	WREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset, पंचांगp);
पूर्ण

bool rs600_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc_id)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];

	/* Return current update_pending status: */
	वापस !!(RREG32(AVIVO_D1GRPH_UPDATE + radeon_crtc->crtc_offset) &
		AVIVO_D1GRPH_SURFACE_UPDATE_PENDING);
पूर्ण

व्योम avivo_program_fmt(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
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

	अगर (bpc == 0)
		वापस;

	चयन (bpc) अणु
	हाल 6:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= AVIVO_TMDS_BIT_DEPTH_CONTROL_SPATIAL_DITHER_EN;
		अन्यथा
			पंचांगp |= AVIVO_TMDS_BIT_DEPTH_CONTROL_TRUNCATE_EN;
		अवरोध;
	हाल 8:
		अगर (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			पंचांगp |= (AVIVO_TMDS_BIT_DEPTH_CONTROL_SPATIAL_DITHER_EN |
				AVIVO_TMDS_BIT_DEPTH_CONTROL_SPATIAL_DITHER_DEPTH);
		अन्यथा
			पंचांगp |= (AVIVO_TMDS_BIT_DEPTH_CONTROL_TRUNCATE_EN |
				AVIVO_TMDS_BIT_DEPTH_CONTROL_TRUNCATE_DEPTH);
		अवरोध;
	हाल 10:
	शेष:
		/* not needed */
		अवरोध;
	पूर्ण

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
		WREG32(AVIVO_TMDSA_BIT_DEPTH_CONTROL, पंचांगp);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		WREG32(AVIVO_LVTMA_BIT_DEPTH_CONTROL, पंचांगp);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		WREG32(AVIVO_DVOA_BIT_DEPTH_CONTROL, पंचांगp);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
		WREG32(AVIVO_DDIA_BIT_DEPTH_CONTROL, पंचांगp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rs600_pm_misc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक requested_index = rdev->pm.requested_घातer_state_index;
	काष्ठा radeon_घातer_state *ps = &rdev->pm.घातer_state[requested_index];
	काष्ठा radeon_voltage *voltage = &ps->घड़ी_info[0].voltage;
	u32 पंचांगp, dyn_pwrmgt_sclk_length, dyn_sclk_vol_cntl;
	u32 hdp_dyn_cntl, /*mc_host_dyn_cntl,*/ dyn_backbias_cntl;

	अगर ((voltage->type == VOLTAGE_GPIO) && (voltage->gpio.valid)) अणु
		अगर (ps->misc & ATOM_PM_MISCINFO_VOLTAGE_DROP_SUPPORT) अणु
			पंचांगp = RREG32(voltage->gpio.reg);
			अगर (voltage->active_high)
				पंचांगp |= voltage->gpio.mask;
			अन्यथा
				पंचांगp &= ~(voltage->gpio.mask);
			WREG32(voltage->gpio.reg, पंचांगp);
			अगर (voltage->delay)
				udelay(voltage->delay);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(voltage->gpio.reg);
			अगर (voltage->active_high)
				पंचांगp &= ~voltage->gpio.mask;
			अन्यथा
				पंचांगp |= voltage->gpio.mask;
			WREG32(voltage->gpio.reg, पंचांगp);
			अगर (voltage->delay)
				udelay(voltage->delay);
		पूर्ण
	पूर्ण अन्यथा अगर (voltage->type == VOLTAGE_VDDC)
		radeon_atom_set_voltage(rdev, voltage->vddc_id, SET_VOLTAGE_TYPE_ASIC_VDDC);

	dyn_pwrmgt_sclk_length = RREG32_PLL(DYN_PWRMGT_SCLK_LENGTH);
	dyn_pwrmgt_sclk_length &= ~REDUCED_POWER_SCLK_HILEN(0xf);
	dyn_pwrmgt_sclk_length &= ~REDUCED_POWER_SCLK_LOLEN(0xf);
	अगर (ps->misc & ATOM_PM_MISCINFO_ASIC_REDUCED_SPEED_SCLK_EN) अणु
		अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_CLOCK_DIVIDER_BY_2) अणु
			dyn_pwrmgt_sclk_length |= REDUCED_POWER_SCLK_HILEN(2);
			dyn_pwrmgt_sclk_length |= REDUCED_POWER_SCLK_LOLEN(2);
		पूर्ण अन्यथा अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_CLOCK_DIVIDER_BY_4) अणु
			dyn_pwrmgt_sclk_length |= REDUCED_POWER_SCLK_HILEN(4);
			dyn_pwrmgt_sclk_length |= REDUCED_POWER_SCLK_LOLEN(4);
		पूर्ण
	पूर्ण अन्यथा अणु
		dyn_pwrmgt_sclk_length |= REDUCED_POWER_SCLK_HILEN(1);
		dyn_pwrmgt_sclk_length |= REDUCED_POWER_SCLK_LOLEN(1);
	पूर्ण
	WREG32_PLL(DYN_PWRMGT_SCLK_LENGTH, dyn_pwrmgt_sclk_length);

	dyn_sclk_vol_cntl = RREG32_PLL(DYN_SCLK_VOL_CNTL);
	अगर (ps->misc & ATOM_PM_MISCINFO_ASIC_DYNAMIC_VOLTAGE_EN) अणु
		dyn_sclk_vol_cntl |= IO_CG_VOLTAGE_DROP;
		अगर (voltage->delay) अणु
			dyn_sclk_vol_cntl |= VOLTAGE_DROP_SYNC;
			dyn_sclk_vol_cntl |= VOLTAGE_DELAY_SEL(voltage->delay);
		पूर्ण अन्यथा
			dyn_sclk_vol_cntl &= ~VOLTAGE_DROP_SYNC;
	पूर्ण अन्यथा
		dyn_sclk_vol_cntl &= ~IO_CG_VOLTAGE_DROP;
	WREG32_PLL(DYN_SCLK_VOL_CNTL, dyn_sclk_vol_cntl);

	hdp_dyn_cntl = RREG32_PLL(HDP_DYN_CNTL);
	अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_HDP_BLOCK_EN)
		hdp_dyn_cntl &= ~HDP_FORCEON;
	अन्यथा
		hdp_dyn_cntl |= HDP_FORCEON;
	WREG32_PLL(HDP_DYN_CNTL, hdp_dyn_cntl);
#अगर 0
	/* mc_host_dyn seems to cause hangs from समय to समय */
	mc_host_dyn_cntl = RREG32_PLL(MC_HOST_DYN_CNTL);
	अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_MC_HOST_BLOCK_EN)
		mc_host_dyn_cntl &= ~MC_HOST_FORCEON;
	अन्यथा
		mc_host_dyn_cntl |= MC_HOST_FORCEON;
	WREG32_PLL(MC_HOST_DYN_CNTL, mc_host_dyn_cntl);
#पूर्ण_अगर
	dyn_backbias_cntl = RREG32_PLL(DYN_BACKBIAS_CNTL);
	अगर (ps->misc & ATOM_PM_MISCINFO2_DYNAMIC_BACK_BIAS_EN)
		dyn_backbias_cntl |= IO_CG_BACKBIAS_EN;
	अन्यथा
		dyn_backbias_cntl &= ~IO_CG_BACKBIAS_EN;
	WREG32_PLL(DYN_BACKBIAS_CNTL, dyn_backbias_cntl);

	/* set pcie lanes */
	अगर ((rdev->flags & RADEON_IS_PCIE) &&
	    !(rdev->flags & RADEON_IS_IGP) &&
	    rdev->asic->pm.set_pcie_lanes &&
	    (ps->pcie_lanes !=
	     rdev->pm.घातer_state[rdev->pm.current_घातer_state_index].pcie_lanes)) अणु
		radeon_set_pcie_lanes(rdev,
				      ps->pcie_lanes);
		DRM_DEBUG("Setting: p: %d\n", ps->pcie_lanes);
	पूर्ण
पूर्ण

व्योम rs600_pm_prepare(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 पंचांगp;

	/* disable any active CRTCs */
	list_क्रम_each_entry(crtc, &ddev->mode_config.crtc_list, head) अणु
		radeon_crtc = to_radeon_crtc(crtc);
		अगर (radeon_crtc->enabled) अणु
			पंचांगp = RREG32(AVIVO_D1CRTC_CONTROL + radeon_crtc->crtc_offset);
			पंचांगp |= AVIVO_CRTC_DISP_READ_REQUEST_DISABLE;
			WREG32(AVIVO_D1CRTC_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rs600_pm_finish(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 पंचांगp;

	/* enable any active CRTCs */
	list_क्रम_each_entry(crtc, &ddev->mode_config.crtc_list, head) अणु
		radeon_crtc = to_radeon_crtc(crtc);
		अगर (radeon_crtc->enabled) अणु
			पंचांगp = RREG32(AVIVO_D1CRTC_CONTROL + radeon_crtc->crtc_offset);
			पंचांगp &= ~AVIVO_CRTC_DISP_READ_REQUEST_DISABLE;
			WREG32(AVIVO_D1CRTC_CONTROL + radeon_crtc->crtc_offset, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

/* hpd क्रम digital panel detect/disconnect */
bool rs600_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd)
अणु
	u32 पंचांगp;
	bool connected = false;

	चयन (hpd) अणु
	हाल RADEON_HPD_1:
		पंचांगp = RREG32(R_007D04_DC_HOT_PLUG_DETECT1_INT_STATUS);
		अगर (G_007D04_DC_HOT_PLUG_DETECT1_SENSE(पंचांगp))
			connected = true;
		अवरोध;
	हाल RADEON_HPD_2:
		पंचांगp = RREG32(R_007D14_DC_HOT_PLUG_DETECT2_INT_STATUS);
		अगर (G_007D14_DC_HOT_PLUG_DETECT2_SENSE(पंचांगp))
			connected = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस connected;
पूर्ण

व्योम rs600_hpd_set_polarity(काष्ठा radeon_device *rdev,
			    क्रमागत radeon_hpd_id hpd)
अणु
	u32 पंचांगp;
	bool connected = rs600_hpd_sense(rdev, hpd);

	चयन (hpd) अणु
	हाल RADEON_HPD_1:
		पंचांगp = RREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL);
		अगर (connected)
			पंचांगp &= ~S_007D08_DC_HOT_PLUG_DETECT1_INT_POLARITY(1);
		अन्यथा
			पंचांगp |= S_007D08_DC_HOT_PLUG_DETECT1_INT_POLARITY(1);
		WREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL, पंचांगp);
		अवरोध;
	हाल RADEON_HPD_2:
		पंचांगp = RREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL);
		अगर (connected)
			पंचांगp &= ~S_007D18_DC_HOT_PLUG_DETECT2_INT_POLARITY(1);
		अन्यथा
			पंचांगp |= S_007D18_DC_HOT_PLUG_DETECT2_INT_POLARITY(1);
		WREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL, पंचांगp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rs600_hpd_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित enable = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		चयन (radeon_connector->hpd.hpd) अणु
		हाल RADEON_HPD_1:
			WREG32(R_007D00_DC_HOT_PLUG_DETECT1_CONTROL,
			       S_007D00_DC_HOT_PLUG_DETECT1_EN(1));
			अवरोध;
		हाल RADEON_HPD_2:
			WREG32(R_007D10_DC_HOT_PLUG_DETECT2_CONTROL,
			       S_007D10_DC_HOT_PLUG_DETECT2_EN(1));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			enable |= 1 << radeon_connector->hpd.hpd;
		radeon_hpd_set_polarity(rdev, radeon_connector->hpd.hpd);
	पूर्ण
	radeon_irq_kms_enable_hpd(rdev, enable);
पूर्ण

व्योम rs600_hpd_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित disable = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		चयन (radeon_connector->hpd.hpd) अणु
		हाल RADEON_HPD_1:
			WREG32(R_007D00_DC_HOT_PLUG_DETECT1_CONTROL,
			       S_007D00_DC_HOT_PLUG_DETECT1_EN(0));
			अवरोध;
		हाल RADEON_HPD_2:
			WREG32(R_007D10_DC_HOT_PLUG_DETECT2_CONTROL,
			       S_007D10_DC_HOT_PLUG_DETECT2_EN(0));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			disable |= 1 << radeon_connector->hpd.hpd;
	पूर्ण
	radeon_irq_kms_disable_hpd(rdev, disable);
पूर्ण

पूर्णांक rs600_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	काष्ठा rv515_mc_save save;
	u32 status, पंचांगp;
	पूर्णांक ret = 0;

	status = RREG32(R_000E40_RBBM_STATUS);
	अगर (!G_000E40_GUI_ACTIVE(status)) अणु
		वापस 0;
	पूर्ण
	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* stop CP */
	WREG32(RADEON_CP_CSQ_CNTL, 0);
	पंचांगp = RREG32(RADEON_CP_RB_CNTL);
	WREG32(RADEON_CP_RB_CNTL, पंचांगp | RADEON_RB_RPTR_WR_ENA);
	WREG32(RADEON_CP_RB_RPTR_WR, 0);
	WREG32(RADEON_CP_RB_WPTR, 0);
	WREG32(RADEON_CP_RB_CNTL, पंचांगp);
	pci_save_state(rdev->pdev);
	/* disable bus mastering */
	pci_clear_master(rdev->pdev);
	mdelay(1);
	/* reset GA+VAP */
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_VAP(1) |
					S_0000F0_SOFT_RESET_GA(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* reset CP */
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_CP(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* reset MC */
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_MC(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* restore PCI & busmastering */
	pci_restore_state(rdev->pdev);
	/* Check अगर GPU is idle */
	अगर (G_000E40_GA_BUSY(status) || G_000E40_VAP_BUSY(status)) अणु
		dev_err(rdev->dev, "failed to reset GPU\n");
		ret = -1;
	पूर्ण अन्यथा
		dev_info(rdev->dev, "GPU reset succeed\n");
	rv515_mc_resume(rdev, &save);
	वापस ret;
पूर्ण

/*
 * GART.
 */
व्योम rs600_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32_MC(R_000100_MC_PT0_CNTL);
	पंचांगp &= C_000100_INVALIDATE_ALL_L1_TLBS & C_000100_INVALIDATE_L2_CACHE;
	WREG32_MC(R_000100_MC_PT0_CNTL, पंचांगp);

	पंचांगp = RREG32_MC(R_000100_MC_PT0_CNTL);
	पंचांगp |= S_000100_INVALIDATE_ALL_L1_TLBS(1) | S_000100_INVALIDATE_L2_CACHE(1);
	WREG32_MC(R_000100_MC_PT0_CNTL, पंचांगp);

	पंचांगp = RREG32_MC(R_000100_MC_PT0_CNTL);
	पंचांगp &= C_000100_INVALIDATE_ALL_L1_TLBS & C_000100_INVALIDATE_L2_CACHE;
	WREG32_MC(R_000100_MC_PT0_CNTL, पंचांगp);
	पंचांगp = RREG32_MC(R_000100_MC_PT0_CNTL);
पूर्ण

अटल पूर्णांक rs600_gart_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.robj) अणु
		WARN(1, "RS600 GART already initialized\n");
		वापस 0;
	पूर्ण
	/* Initialize common gart काष्ठाure */
	r = radeon_gart_init(rdev);
	अगर (r) अणु
		वापस r;
	पूर्ण
	rdev->gart.table_size = rdev->gart.num_gpu_pages * 8;
	वापस radeon_gart_table_vram_alloc(rdev);
पूर्ण

अटल पूर्णांक rs600_gart_enable(काष्ठा radeon_device *rdev)
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
	/* Enable bus master */
	पंचांगp = RREG32(RADEON_BUS_CNTL) & ~RS600_BUS_MASTER_DIS;
	WREG32(RADEON_BUS_CNTL, पंचांगp);
	/* FIXME: setup शेष page */
	WREG32_MC(R_000100_MC_PT0_CNTL,
		  (S_000100_EFFECTIVE_L2_CACHE_SIZE(6) |
		   S_000100_EFFECTIVE_L2_QUEUE_SIZE(6)));

	क्रम (i = 0; i < 19; i++) अणु
		WREG32_MC(R_00016C_MC_PT0_CLIENT0_CNTL + i,
			  S_00016C_ENABLE_TRANSLATION_MODE_OVERRIDE(1) |
			  S_00016C_SYSTEM_ACCESS_MODE_MASK(
				  V_00016C_SYSTEM_ACCESS_MODE_NOT_IN_SYS) |
			  S_00016C_SYSTEM_APERTURE_UNMAPPED_ACCESS(
				  V_00016C_SYSTEM_APERTURE_UNMAPPED_PASSTHROUGH) |
			  S_00016C_EFFECTIVE_L1_CACHE_SIZE(3) |
			  S_00016C_ENABLE_FRAGMENT_PROCESSING(1) |
			  S_00016C_EFFECTIVE_L1_QUEUE_SIZE(3));
	पूर्ण
	/* enable first context */
	WREG32_MC(R_000102_MC_PT0_CONTEXT0_CNTL,
		  S_000102_ENABLE_PAGE_TABLE(1) |
		  S_000102_PAGE_TABLE_DEPTH(V_000102_PAGE_TABLE_FLAT));

	/* disable all other contexts */
	क्रम (i = 1; i < 8; i++)
		WREG32_MC(R_000102_MC_PT0_CONTEXT0_CNTL + i, 0);

	/* setup the page table */
	WREG32_MC(R_00012C_MC_PT0_CONTEXT0_FLAT_BASE_ADDR,
		  rdev->gart.table_addr);
	WREG32_MC(R_00013C_MC_PT0_CONTEXT0_FLAT_START_ADDR, rdev->mc.gtt_start);
	WREG32_MC(R_00014C_MC_PT0_CONTEXT0_FLAT_END_ADDR, rdev->mc.gtt_end);
	WREG32_MC(R_00011C_MC_PT0_CONTEXT0_DEFAULT_READ_ADDR, 0);

	/* System context maps to VRAM space */
	WREG32_MC(R_000112_MC_PT0_SYSTEM_APERTURE_LOW_ADDR, rdev->mc.vram_start);
	WREG32_MC(R_000114_MC_PT0_SYSTEM_APERTURE_HIGH_ADDR, rdev->mc.vram_end);

	/* enable page tables */
	पंचांगp = RREG32_MC(R_000100_MC_PT0_CNTL);
	WREG32_MC(R_000100_MC_PT0_CNTL, (पंचांगp | S_000100_ENABLE_PT(1)));
	पंचांगp = RREG32_MC(R_000009_MC_CNTL1);
	WREG32_MC(R_000009_MC_CNTL1, (पंचांगp | S_000009_ENABLE_PAGE_TABLES(1)));
	rs600_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल व्योम rs600_gart_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	/* FIXME: disable out of gart access */
	WREG32_MC(R_000100_MC_PT0_CNTL, 0);
	पंचांगp = RREG32_MC(R_000009_MC_CNTL1);
	WREG32_MC(R_000009_MC_CNTL1, पंचांगp & C_000009_ENABLE_PAGE_TABLES);
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

अटल व्योम rs600_gart_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_gart_fini(rdev);
	rs600_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
पूर्ण

uपूर्णांक64_t rs600_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags)
अणु
	addr = addr & 0xFFFFFFFFFFFFF000ULL;
	addr |= R600_PTE_SYSTEM;
	अगर (flags & RADEON_GART_PAGE_VALID)
		addr |= R600_PTE_VALID;
	अगर (flags & RADEON_GART_PAGE_READ)
		addr |= R600_PTE_READABLE;
	अगर (flags & RADEON_GART_PAGE_WRITE)
		addr |= R600_PTE_WRITEABLE;
	अगर (flags & RADEON_GART_PAGE_SNOOP)
		addr |= R600_PTE_SNOOPED;
	वापस addr;
पूर्ण

व्योम rs600_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			 uपूर्णांक64_t entry)
अणु
	व्योम __iomem *ptr = (व्योम *)rdev->gart.ptr;
	ग_लिखोq(entry, ptr + (i * 8));
पूर्ण

पूर्णांक rs600_irq_set(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp = 0;
	uपूर्णांक32_t mode_पूर्णांक = 0;
	u32 hpd1 = RREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL) &
		~S_007D08_DC_HOT_PLUG_DETECT1_INT_EN(1);
	u32 hpd2 = RREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL) &
		~S_007D18_DC_HOT_PLUG_DETECT2_INT_EN(1);
	u32 hdmi0;
	अगर (ASIC_IS_DCE2(rdev))
		hdmi0 = RREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL) &
			~S_007408_HDMI0_AZ_FORMAT_WTRIG_MASK(1);
	अन्यथा
		hdmi0 = 0;

	अगर (!rdev->irq.installed) अणु
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		WREG32(R_000040_GEN_INT_CNTL, 0);
		वापस -EINVAL;
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
		पंचांगp |= S_000040_SW_INT_EN(1);
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[0] ||
	    atomic_पढ़ो(&rdev->irq.pflip[0])) अणु
		mode_पूर्णांक |= S_006540_D1MODE_VBLANK_INT_MASK(1);
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[1] ||
	    atomic_पढ़ो(&rdev->irq.pflip[1])) अणु
		mode_पूर्णांक |= S_006540_D2MODE_VBLANK_INT_MASK(1);
	पूर्ण
	अगर (rdev->irq.hpd[0]) अणु
		hpd1 |= S_007D08_DC_HOT_PLUG_DETECT1_INT_EN(1);
	पूर्ण
	अगर (rdev->irq.hpd[1]) अणु
		hpd2 |= S_007D18_DC_HOT_PLUG_DETECT2_INT_EN(1);
	पूर्ण
	अगर (rdev->irq.afmt[0]) अणु
		hdmi0 |= S_007408_HDMI0_AZ_FORMAT_WTRIG_MASK(1);
	पूर्ण
	WREG32(R_000040_GEN_INT_CNTL, पंचांगp);
	WREG32(R_006540_DxMODE_INT_MASK, mode_पूर्णांक);
	WREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL, hpd1);
	WREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL, hpd2);
	अगर (ASIC_IS_DCE2(rdev))
		WREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL, hdmi0);

	/* posting पढ़ो */
	RREG32(R_000040_GEN_INT_CNTL);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 rs600_irq_ack(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t irqs = RREG32(R_000044_GEN_INT_STATUS);
	uपूर्णांक32_t irq_mask = S_000044_SW_INT(1);
	u32 पंचांगp;

	अगर (G_000044_DISPLAY_INT_STAT(irqs)) अणु
		rdev->irq.stat_regs.r500.disp_पूर्णांक = RREG32(R_007EDC_DISP_INTERRUPT_STATUS);
		अगर (G_007EDC_LB_D1_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			WREG32(R_006534_D1MODE_VBLANK_STATUS,
				S_006534_D1MODE_VBLANK_ACK(1));
		पूर्ण
		अगर (G_007EDC_LB_D2_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			WREG32(R_006D34_D2MODE_VBLANK_STATUS,
				S_006D34_D2MODE_VBLANK_ACK(1));
		पूर्ण
		अगर (G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			पंचांगp = RREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL);
			पंचांगp |= S_007D08_DC_HOT_PLUG_DETECT1_INT_ACK(1);
			WREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL, पंचांगp);
		पूर्ण
		अगर (G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			पंचांगp = RREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL);
			पंचांगp |= S_007D18_DC_HOT_PLUG_DETECT2_INT_ACK(1);
			WREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL, पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		rdev->irq.stat_regs.r500.disp_पूर्णांक = 0;
	पूर्ण

	अगर (ASIC_IS_DCE2(rdev)) अणु
		rdev->irq.stat_regs.r500.hdmi0_status = RREG32(R_007404_HDMI0_STATUS) &
			S_007404_HDMI0_AZ_FORMAT_WTRIG(1);
		अगर (G_007404_HDMI0_AZ_FORMAT_WTRIG(rdev->irq.stat_regs.r500.hdmi0_status)) अणु
			पंचांगp = RREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL);
			पंचांगp |= S_007408_HDMI0_AZ_FORMAT_WTRIG_ACK(1);
			WREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL, पंचांगp);
		पूर्ण
	पूर्ण अन्यथा
		rdev->irq.stat_regs.r500.hdmi0_status = 0;

	अगर (irqs) अणु
		WREG32(R_000044_GEN_INT_STATUS, irqs);
	पूर्ण
	वापस irqs & irq_mask;
पूर्ण

व्योम rs600_irq_disable(काष्ठा radeon_device *rdev)
अणु
	u32 hdmi0 = RREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL) &
		~S_007408_HDMI0_AZ_FORMAT_WTRIG_MASK(1);
	WREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL, hdmi0);
	WREG32(R_000040_GEN_INT_CNTL, 0);
	WREG32(R_006540_DxMODE_INT_MASK, 0);
	/* Wait and acknowledge irq */
	mdelay(1);
	rs600_irq_ack(rdev);
पूर्ण

पूर्णांक rs600_irq_process(काष्ठा radeon_device *rdev)
अणु
	u32 status, msi_rearm;
	bool queue_hotplug = false;
	bool queue_hdmi = false;

	status = rs600_irq_ack(rdev);
	अगर (!status &&
	    !rdev->irq.stat_regs.r500.disp_पूर्णांक &&
	    !rdev->irq.stat_regs.r500.hdmi0_status) अणु
		वापस IRQ_NONE;
	पूर्ण
	जबतक (status ||
	       rdev->irq.stat_regs.r500.disp_पूर्णांक ||
	       rdev->irq.stat_regs.r500.hdmi0_status) अणु
		/* SW पूर्णांकerrupt */
		अगर (G_000044_SW_INT(status)) अणु
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
		पूर्ण
		/* Vertical blank पूर्णांकerrupts */
		अगर (G_007EDC_LB_D1_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			अगर (rdev->irq.crtc_vblank_पूर्णांक[0]) अणु
				drm_handle_vblank(rdev->ddev, 0);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			पूर्ण
			अगर (atomic_पढ़ो(&rdev->irq.pflip[0]))
				radeon_crtc_handle_vblank(rdev, 0);
		पूर्ण
		अगर (G_007EDC_LB_D2_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			अगर (rdev->irq.crtc_vblank_पूर्णांक[1]) अणु
				drm_handle_vblank(rdev->ddev, 1);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			पूर्ण
			अगर (atomic_पढ़ो(&rdev->irq.pflip[1]))
				radeon_crtc_handle_vblank(rdev, 1);
		पूर्ण
		अगर (G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			queue_hotplug = true;
			DRM_DEBUG("HPD1\n");
		पूर्ण
		अगर (G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT(rdev->irq.stat_regs.r500.disp_पूर्णांक)) अणु
			queue_hotplug = true;
			DRM_DEBUG("HPD2\n");
		पूर्ण
		अगर (G_007404_HDMI0_AZ_FORMAT_WTRIG(rdev->irq.stat_regs.r500.hdmi0_status)) अणु
			queue_hdmi = true;
			DRM_DEBUG("HDMI0\n");
		पूर्ण
		status = rs600_irq_ack(rdev);
	पूर्ण
	अगर (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	अगर (queue_hdmi)
		schedule_work(&rdev->audio_work);
	अगर (rdev->msi_enabled) अणु
		चयन (rdev->family) अणु
		हाल CHIP_RS600:
		हाल CHIP_RS690:
		हाल CHIP_RS740:
			msi_rearm = RREG32(RADEON_BUS_CNTL) & ~RS600_MSI_REARM;
			WREG32(RADEON_BUS_CNTL, msi_rearm);
			WREG32(RADEON_BUS_CNTL, msi_rearm | RS600_MSI_REARM);
			अवरोध;
		शेष:
			WREG32(RADEON_MSI_REARM_EN, RV370_MSI_REARM_EN);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

u32 rs600_get_vblank_counter(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अगर (crtc == 0)
		वापस RREG32(R_0060A4_D1CRTC_STATUS_FRAME_COUNT);
	अन्यथा
		वापस RREG32(R_0068A4_D2CRTC_STATUS_FRAME_COUNT);
पूर्ण

पूर्णांक rs600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (G_000000_MC_IDLE(RREG32_MC(R_000000_MC_STATUS)))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम rs600_gpu_init(काष्ठा radeon_device *rdev)
अणु
	r420_pipes_init(rdev);
	/* Wait क्रम mc idle */
	अगर (rs600_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");
पूर्ण

अटल व्योम rs600_mc_init(काष्ठा radeon_device *rdev)
अणु
	u64 base;

	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	rdev->mc.vram_is_ddr = true;
	rdev->mc.vram_width = 128;
	rdev->mc.real_vram_size = RREG32(RADEON_CONFIG_MEMSIZE);
	rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	rdev->mc.igp_sideport_enabled = radeon_atombios_sideport_present(rdev);
	base = RREG32_MC(R_000004_MC_FB_LOCATION);
	base = G_000004_MC_FB_START(base) << 16;
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = 0;
	radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण

व्योम rs600_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_display_mode *mode0 = शून्य;
	काष्ठा drm_display_mode *mode1 = शून्य;
	u32 d1mode_priority_a_cnt, d2mode_priority_a_cnt;
	/* FIXME: implement full support */

	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	radeon_update_display_priority(rdev);

	अगर (rdev->mode_info.crtcs[0]->base.enabled)
		mode0 = &rdev->mode_info.crtcs[0]->base.mode;
	अगर (rdev->mode_info.crtcs[1]->base.enabled)
		mode1 = &rdev->mode_info.crtcs[1]->base.mode;

	rs690_line_buffer_adjust(rdev, mode0, mode1);

	अगर (rdev->disp_priority == 2) अणु
		d1mode_priority_a_cnt = RREG32(R_006548_D1MODE_PRIORITY_A_CNT);
		d2mode_priority_a_cnt = RREG32(R_006D48_D2MODE_PRIORITY_A_CNT);
		d1mode_priority_a_cnt |= S_006548_D1MODE_PRIORITY_A_ALWAYS_ON(1);
		d2mode_priority_a_cnt |= S_006D48_D2MODE_PRIORITY_A_ALWAYS_ON(1);
		WREG32(R_006548_D1MODE_PRIORITY_A_CNT, d1mode_priority_a_cnt);
		WREG32(R_00654C_D1MODE_PRIORITY_B_CNT, d1mode_priority_a_cnt);
		WREG32(R_006D48_D2MODE_PRIORITY_A_CNT, d2mode_priority_a_cnt);
		WREG32(R_006D4C_D2MODE_PRIORITY_B_CNT, d2mode_priority_a_cnt);
	पूर्ण
पूर्ण

uपूर्णांक32_t rs600_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_000070_MC_IND_INDEX, S_000070_MC_IND_ADDR(reg) |
		S_000070_MC_IND_CITF_ARB0(1));
	r = RREG32(R_000074_MC_IND_DATA);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
	वापस r;
पूर्ण

व्योम rs600_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_000070_MC_IND_INDEX, S_000070_MC_IND_ADDR(reg) |
		S_000070_MC_IND_CITF_ARB0(1) | S_000070_MC_IND_WR_EN(1));
	WREG32(R_000074_MC_IND_DATA, v);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
पूर्ण

व्योम rs600_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	rdev->config.r300.reg_safe_bm = rs600_reg_safe_bm;
	rdev->config.r300.reg_safe_bm_size = ARRAY_SIZE(rs600_reg_safe_bm);
पूर्ण

अटल व्योम rs600_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;

	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);

	/* Wait क्रम mc idle */
	अगर (rs600_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");

	/* FIXME: What करोes AGP means क्रम such chipset ? */
	WREG32_MC(R_000005_MC_AGP_LOCATION, 0x0FFFFFFF);
	WREG32_MC(R_000006_AGP_BASE, 0);
	WREG32_MC(R_000007_AGP_BASE_2, 0);
	/* Program MC */
	WREG32_MC(R_000004_MC_FB_LOCATION,
			S_000004_MC_FB_START(rdev->mc.vram_start >> 16) |
			S_000004_MC_FB_TOP(rdev->mc.vram_end >> 16));
	WREG32(R_000134_HDP_FB_LOCATION,
		S_000134_HDP_FB_START(rdev->mc.vram_start >> 16));

	rv515_mc_resume(rdev, &save);
पूर्ण

अटल पूर्णांक rs600_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	rs600_mc_program(rdev);
	/* Resume घड़ी */
	rv515_घड़ी_startup(rdev);
	/* Initialize GPU configuration (# pipes, ...) */
	rs600_gpu_init(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	r = rs600_gart_enable(rdev);
	अगर (r)
		वापस r;

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	/* Enable IRQ */
	अगर (!rdev->irq.installed) अणु
		r = radeon_irq_kms_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	rs600_irq_set(rdev);
	rdev->config.r300.hdp_cntl = RREG32(RADEON_HOST_PATH_CNTL);
	/* 1M ring buffer */
	r = r100_cp_init(rdev, 1024 * 1024);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_audio_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing audio\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rs600_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	rs600_gart_disable(rdev);
	/* Resume घड़ी beक्रमe करोing reset */
	rv515_घड़ी_startup(rdev);
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* post */
	atom_asic_init(rdev->mode_info.atom_context);
	/* Resume घड़ी after posting */
	rv515_घड़ी_startup(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = rs600_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक rs600_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	rs600_irq_disable(rdev);
	rs600_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम rs600_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	radeon_audio_fini(rdev);
	r100_cp_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_gem_fini(rdev);
	rs600_gart_fini(rdev);
	radeon_irq_kms_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

पूर्णांक rs600_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Disable VGA */
	rv515_vga_render_disable(rdev);
	/* Initialize scratch रेजिस्टरs */
	radeon_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* restore some रेजिस्टर to sane शेषs */
	r100_restore_sanity(rdev);
	/* BIOS */
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	अगर (rdev->is_atom_bios) अणु
		r = radeon_atombios_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		dev_err(rdev->dev, "Expecting atombios for RS600 GPU\n");
		वापस -EINVAL;
	पूर्ण
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev,
			"GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* check अगर cards are posted or not */
	अगर (radeon_boot_test_post_card(rdev) == false)
		वापस -EINVAL;

	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* initialize memory controller */
	rs600_mc_init(rdev);
	r100_debugfs_rbbm_init(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;
	r = rs600_gart_init(rdev);
	अगर (r)
		वापस r;
	rs600_set_safe_रेजिस्टरs(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = rs600_startup(rdev);
	अगर (r) अणु
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		rs600_gart_fini(rdev);
		radeon_irq_kms_fini(rdev);
		rdev->accel_working = false;
	पूर्ण
	वापस 0;
पूर्ण
