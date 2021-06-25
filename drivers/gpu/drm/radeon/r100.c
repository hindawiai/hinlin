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
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "r100_reg_safe.h"
#समावेश "r100d.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_reg.h"
#समावेश "rn50_reg_safe.h"
#समावेश "rs100d.h"
#समावेश "rv200d.h"
#समावेश "rv250d.h"

/* Firmware Names */
#घोषणा FIRMWARE_R100		"radeon/R100_cp.bin"
#घोषणा FIRMWARE_R200		"radeon/R200_cp.bin"
#घोषणा FIRMWARE_R300		"radeon/R300_cp.bin"
#घोषणा FIRMWARE_R420		"radeon/R420_cp.bin"
#घोषणा FIRMWARE_RS690		"radeon/RS690_cp.bin"
#घोषणा FIRMWARE_RS600		"radeon/RS600_cp.bin"
#घोषणा FIRMWARE_R520		"radeon/R520_cp.bin"

MODULE_FIRMWARE(FIRMWARE_R100);
MODULE_FIRMWARE(FIRMWARE_R200);
MODULE_FIRMWARE(FIRMWARE_R300);
MODULE_FIRMWARE(FIRMWARE_R420);
MODULE_FIRMWARE(FIRMWARE_RS690);
MODULE_FIRMWARE(FIRMWARE_RS600);
MODULE_FIRMWARE(FIRMWARE_R520);

#समावेश "r100_track.h"

/* This files gather functions specअगरics to:
 * r100,rv100,rs100,rv200,rs200,r200,rv250,rs300,rv280
 * and others in some हालs.
 */

अटल bool r100_is_in_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अगर (crtc == 0) अणु
		अगर (RREG32(RADEON_CRTC_STATUS) & RADEON_CRTC_VBLANK_CUR)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (RREG32(RADEON_CRTC2_STATUS) & RADEON_CRTC2_VBLANK_CUR)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
पूर्ण

अटल bool r100_is_counter_moving(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	u32 vline1, vline2;

	अगर (crtc == 0) अणु
		vline1 = (RREG32(RADEON_CRTC_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
		vline2 = (RREG32(RADEON_CRTC_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
	पूर्ण अन्यथा अणु
		vline1 = (RREG32(RADEON_CRTC2_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
		vline2 = (RREG32(RADEON_CRTC2_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
	पूर्ण
	अगर (vline1 != vline2)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * r100_रुको_क्रम_vblank - vblank रुको asic callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc: crtc to रुको क्रम vblank on
 *
 * Wait क्रम vblank on the requested crtc (r1xx-r4xx).
 */
व्योम r100_रुको_क्रम_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अचिन्हित i = 0;

	अगर (crtc >= rdev->num_crtc)
		वापस;

	अगर (crtc == 0) अणु
		अगर (!(RREG32(RADEON_CRTC_GEN_CNTL) & RADEON_CRTC_EN))
			वापस;
	पूर्ण अन्यथा अणु
		अगर (!(RREG32(RADEON_CRTC2_GEN_CNTL) & RADEON_CRTC2_EN))
			वापस;
	पूर्ण

	/* depending on when we hit vblank, we may be बंद to active; अगर so,
	 * रुको क्रम another frame.
	 */
	जबतक (r100_is_in_vblank(rdev, crtc)) अणु
		अगर (i++ % 100 == 0) अणु
			अगर (!r100_is_counter_moving(rdev, crtc))
				अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!r100_is_in_vblank(rdev, crtc)) अणु
		अगर (i++ % 100 == 0) अणु
			अगर (!r100_is_counter_moving(rdev, crtc))
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * r100_page_flip - pageflip callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc_id: crtc to cleanup pageflip on
 * @crtc_base: new address of the crtc (GPU MC address)
 * @async: asynchronous flip
 *
 * Does the actual pageflip (r1xx-r4xx).
 * During vblank we take the crtc lock and रुको क्रम the update_pending
 * bit to go high, when it करोes, we release the lock, and allow the
 * द्विगुन buffered update to take place.
 */
व्योम r100_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc_id, u64 crtc_base, bool async)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	u32 पंचांगp = ((u32)crtc_base) | RADEON_CRTC_OFFSET__OFFSET_LOCK;
	पूर्णांक i;

	/* Lock the graphics update lock */
	/* update the scanout addresses */
	WREG32(RADEON_CRTC_OFFSET + radeon_crtc->crtc_offset, पंचांगp);

	/* Wait क्रम update_pending to go high. */
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(RADEON_CRTC_OFFSET + radeon_crtc->crtc_offset) & RADEON_CRTC_OFFSET__GUI_TRIG_OFFSET)
			अवरोध;
		udelay(1);
	पूर्ण
	DRM_DEBUG("Update pending now high. Unlocking vupdate_lock.\n");

	/* Unlock the lock, so द्विगुन-buffering can take place inside vblank */
	पंचांगp &= ~RADEON_CRTC_OFFSET__OFFSET_LOCK;
	WREG32(RADEON_CRTC_OFFSET + radeon_crtc->crtc_offset, पंचांगp);

पूर्ण

/**
 * r100_page_flip_pending - check अगर page flip is still pending
 *
 * @rdev: radeon_device poपूर्णांकer
 * @crtc_id: crtc to check
 *
 * Check अगर the last pagefilp is still pending (r1xx-r4xx).
 * Returns the current update pending status.
 */
bool r100_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc_id)
अणु
	काष्ठा radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];

	/* Return current update_pending status: */
	वापस !!(RREG32(RADEON_CRTC_OFFSET + radeon_crtc->crtc_offset) &
		RADEON_CRTC_OFFSET__GUI_TRIG_OFFSET);
पूर्ण

/**
 * r100_pm_get_dynpm_state - look up dynpm घातer state callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Look up the optimal घातer state based on the
 * current state of the GPU (r1xx-r5xx).
 * Used क्रम dynpm only.
 */
व्योम r100_pm_get_dynpm_state(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	rdev->pm.dynpm_can_upघड़ी = true;
	rdev->pm.dynpm_can_करोwnघड़ी = true;

	चयन (rdev->pm.dynpm_planned_action) अणु
	हाल DYNPM_ACTION_MINIMUM:
		rdev->pm.requested_घातer_state_index = 0;
		rdev->pm.dynpm_can_करोwnघड़ी = false;
		अवरोध;
	हाल DYNPM_ACTION_DOWNCLOCK:
		अगर (rdev->pm.current_घातer_state_index == 0) अणु
			rdev->pm.requested_घातer_state_index = rdev->pm.current_घातer_state_index;
			rdev->pm.dynpm_can_करोwnघड़ी = false;
		पूर्ण अन्यथा अणु
			अगर (rdev->pm.active_crtc_count > 1) अणु
				क्रम (i = 0; i < rdev->pm.num_घातer_states; i++) अणु
					अगर (rdev->pm.घातer_state[i].flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
						जारी;
					अन्यथा अगर (i >= rdev->pm.current_घातer_state_index) अणु
						rdev->pm.requested_घातer_state_index = rdev->pm.current_घातer_state_index;
						अवरोध;
					पूर्ण अन्यथा अणु
						rdev->pm.requested_घातer_state_index = i;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा
				rdev->pm.requested_घातer_state_index =
					rdev->pm.current_घातer_state_index - 1;
		पूर्ण
		/* करोn't use the घातer state अगर crtcs are active and no display flag is set */
		अगर ((rdev->pm.active_crtc_count > 0) &&
		    (rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].घड़ी_info[0].flags &
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
						rdev->pm.requested_घातer_state_index = rdev->pm.current_घातer_state_index;
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
		अवरोध;
	हाल DYNPM_ACTION_DEFAULT:
		rdev->pm.requested_घातer_state_index = rdev->pm.शेष_घातer_state_index;
		rdev->pm.dynpm_can_upघड़ी = false;
		अवरोध;
	हाल DYNPM_ACTION_NONE:
	शेष:
		DRM_ERROR("Requested mode for not defined action\n");
		वापस;
	पूर्ण
	/* only one घड़ी mode per घातer state */
	rdev->pm.requested_घड़ी_mode_index = 0;

	DRM_DEBUG_DRIVER("Requested: e: %d m: %d p: %d\n",
		  rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
		  घड़ी_info[rdev->pm.requested_घड़ी_mode_index].sclk,
		  rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
		  घड़ी_info[rdev->pm.requested_घड़ी_mode_index].mclk,
		  rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
		  pcie_lanes);
पूर्ण

/**
 * r100_pm_init_profile - Initialize घातer profiles callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initialize the घातer states used in profile mode
 * (r1xx-r3xx).
 * Used क्रम profile mode only.
 */
व्योम r100_pm_init_profile(काष्ठा radeon_device *rdev)
अणु
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
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 0;
	/* low mh */
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
	/* mid mh */
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;
	/* high mh */
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 0;
पूर्ण

/**
 * r100_pm_misc - set additional pm hw parameters callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set non-घड़ी parameters associated with a घातer state
 * (voltage, pcie lanes, etc.) (r1xx-r4xx).
 */
व्योम r100_pm_misc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक requested_index = rdev->pm.requested_घातer_state_index;
	काष्ठा radeon_घातer_state *ps = &rdev->pm.घातer_state[requested_index];
	काष्ठा radeon_voltage *voltage = &ps->घड़ी_info[0].voltage;
	u32 पंचांगp, sclk_cntl, sclk_cntl2, sclk_more_cntl;

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
	पूर्ण

	sclk_cntl = RREG32_PLL(SCLK_CNTL);
	sclk_cntl2 = RREG32_PLL(SCLK_CNTL2);
	sclk_cntl2 &= ~REDUCED_SPEED_SCLK_SEL(3);
	sclk_more_cntl = RREG32_PLL(SCLK_MORE_CNTL);
	sclk_more_cntl &= ~VOLTAGE_DELAY_SEL(3);
	अगर (ps->misc & ATOM_PM_MISCINFO_ASIC_REDUCED_SPEED_SCLK_EN) अणु
		sclk_more_cntl |= REDUCED_SPEED_SCLK_EN;
		अगर (ps->misc & ATOM_PM_MISCINFO_DYN_CLK_3D_IDLE)
			sclk_cntl2 |= REDUCED_SPEED_SCLK_MODE;
		अन्यथा
			sclk_cntl2 &= ~REDUCED_SPEED_SCLK_MODE;
		अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_CLOCK_DIVIDER_BY_2)
			sclk_cntl2 |= REDUCED_SPEED_SCLK_SEL(0);
		अन्यथा अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_CLOCK_DIVIDER_BY_4)
			sclk_cntl2 |= REDUCED_SPEED_SCLK_SEL(2);
	पूर्ण अन्यथा
		sclk_more_cntl &= ~REDUCED_SPEED_SCLK_EN;

	अगर (ps->misc & ATOM_PM_MISCINFO_ASIC_DYNAMIC_VOLTAGE_EN) अणु
		sclk_more_cntl |= IO_CG_VOLTAGE_DROP;
		अगर (voltage->delay) अणु
			sclk_more_cntl |= VOLTAGE_DROP_SYNC;
			चयन (voltage->delay) अणु
			हाल 33:
				sclk_more_cntl |= VOLTAGE_DELAY_SEL(0);
				अवरोध;
			हाल 66:
				sclk_more_cntl |= VOLTAGE_DELAY_SEL(1);
				अवरोध;
			हाल 99:
				sclk_more_cntl |= VOLTAGE_DELAY_SEL(2);
				अवरोध;
			हाल 132:
				sclk_more_cntl |= VOLTAGE_DELAY_SEL(3);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			sclk_more_cntl &= ~VOLTAGE_DROP_SYNC;
	पूर्ण अन्यथा
		sclk_more_cntl &= ~IO_CG_VOLTAGE_DROP;

	अगर (ps->misc & ATOM_PM_MISCINFO_DYNAMIC_HDP_BLOCK_EN)
		sclk_cntl &= ~FORCE_HDP;
	अन्यथा
		sclk_cntl |= FORCE_HDP;

	WREG32_PLL(SCLK_CNTL, sclk_cntl);
	WREG32_PLL(SCLK_CNTL2, sclk_cntl2);
	WREG32_PLL(SCLK_MORE_CNTL, sclk_more_cntl);

	/* set pcie lanes */
	अगर ((rdev->flags & RADEON_IS_PCIE) &&
	    !(rdev->flags & RADEON_IS_IGP) &&
	    rdev->asic->pm.set_pcie_lanes &&
	    (ps->pcie_lanes !=
	     rdev->pm.घातer_state[rdev->pm.current_घातer_state_index].pcie_lanes)) अणु
		radeon_set_pcie_lanes(rdev,
				      ps->pcie_lanes);
		DRM_DEBUG_DRIVER("Setting: p: %d\n", ps->pcie_lanes);
	पूर्ण
पूर्ण

/**
 * r100_pm_prepare - pre-घातer state change callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Prepare क्रम a घातer state change (r1xx-r4xx).
 */
व्योम r100_pm_prepare(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 पंचांगp;

	/* disable any active CRTCs */
	list_क्रम_each_entry(crtc, &ddev->mode_config.crtc_list, head) अणु
		radeon_crtc = to_radeon_crtc(crtc);
		अगर (radeon_crtc->enabled) अणु
			अगर (radeon_crtc->crtc_id) अणु
				पंचांगp = RREG32(RADEON_CRTC2_GEN_CNTL);
				पंचांगp |= RADEON_CRTC2_DISP_REQ_EN_B;
				WREG32(RADEON_CRTC2_GEN_CNTL, पंचांगp);
			पूर्ण अन्यथा अणु
				पंचांगp = RREG32(RADEON_CRTC_GEN_CNTL);
				पंचांगp |= RADEON_CRTC_DISP_REQ_EN_B;
				WREG32(RADEON_CRTC_GEN_CNTL, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * r100_pm_finish - post-घातer state change callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Clean up after a घातer state change (r1xx-r4xx).
 */
व्योम r100_pm_finish(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 पंचांगp;

	/* enable any active CRTCs */
	list_क्रम_each_entry(crtc, &ddev->mode_config.crtc_list, head) अणु
		radeon_crtc = to_radeon_crtc(crtc);
		अगर (radeon_crtc->enabled) अणु
			अगर (radeon_crtc->crtc_id) अणु
				पंचांगp = RREG32(RADEON_CRTC2_GEN_CNTL);
				पंचांगp &= ~RADEON_CRTC2_DISP_REQ_EN_B;
				WREG32(RADEON_CRTC2_GEN_CNTL, पंचांगp);
			पूर्ण अन्यथा अणु
				पंचांगp = RREG32(RADEON_CRTC_GEN_CNTL);
				पंचांगp &= ~RADEON_CRTC_DISP_REQ_EN_B;
				WREG32(RADEON_CRTC_GEN_CNTL, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * r100_gui_idle - gui idle callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Check of the GUI (2D/3D engines) are idle (r1xx-r5xx).
 * Returns true अगर idle, false अगर not.
 */
bool r100_gui_idle(काष्ठा radeon_device *rdev)
अणु
	अगर (RREG32(RADEON_RBBM_STATUS) & RADEON_RBBM_ACTIVE)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

/* hpd क्रम digital panel detect/disconnect */
/**
 * r100_hpd_sense - hpd sense callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @hpd: hpd (hotplug detect) pin
 *
 * Checks अगर a digital monitor is connected (r1xx-r4xx).
 * Returns true अगर connected, false अगर not connected.
 */
bool r100_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd)
अणु
	bool connected = false;

	चयन (hpd) अणु
	हाल RADEON_HPD_1:
		अगर (RREG32(RADEON_FP_GEN_CNTL) & RADEON_FP_DETECT_SENSE)
			connected = true;
		अवरोध;
	हाल RADEON_HPD_2:
		अगर (RREG32(RADEON_FP2_GEN_CNTL) & RADEON_FP2_DETECT_SENSE)
			connected = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस connected;
पूर्ण

/**
 * r100_hpd_set_polarity - hpd set polarity callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @hpd: hpd (hotplug detect) pin
 *
 * Set the polarity of the hpd pin (r1xx-r4xx).
 */
व्योम r100_hpd_set_polarity(काष्ठा radeon_device *rdev,
			   क्रमागत radeon_hpd_id hpd)
अणु
	u32 पंचांगp;
	bool connected = r100_hpd_sense(rdev, hpd);

	चयन (hpd) अणु
	हाल RADEON_HPD_1:
		पंचांगp = RREG32(RADEON_FP_GEN_CNTL);
		अगर (connected)
			पंचांगp &= ~RADEON_FP_DETECT_INT_POL;
		अन्यथा
			पंचांगp |= RADEON_FP_DETECT_INT_POL;
		WREG32(RADEON_FP_GEN_CNTL, पंचांगp);
		अवरोध;
	हाल RADEON_HPD_2:
		पंचांगp = RREG32(RADEON_FP2_GEN_CNTL);
		अगर (connected)
			पंचांगp &= ~RADEON_FP2_DETECT_INT_POL;
		अन्यथा
			पंचांगp |= RADEON_FP2_DETECT_INT_POL;
		WREG32(RADEON_FP2_GEN_CNTL, पंचांगp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * r100_hpd_init - hpd setup callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Setup the hpd pins used by the card (r1xx-r4xx).
 * Set the polarity, and enable the hpd पूर्णांकerrupts.
 */
व्योम r100_hpd_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित enable = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			enable |= 1 << radeon_connector->hpd.hpd;
		radeon_hpd_set_polarity(rdev, radeon_connector->hpd.hpd);
	पूर्ण
	radeon_irq_kms_enable_hpd(rdev, enable);
पूर्ण

/**
 * r100_hpd_fini - hpd tear करोwn callback.
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the hpd pins used by the card (r1xx-r4xx).
 * Disable the hpd पूर्णांकerrupts.
 */
व्योम r100_hpd_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	अचिन्हित disable = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		अगर (radeon_connector->hpd.hpd != RADEON_HPD_NONE)
			disable |= 1 << radeon_connector->hpd.hpd;
	पूर्ण
	radeon_irq_kms_disable_hpd(rdev, disable);
पूर्ण

/*
 * PCI GART
 */
व्योम r100_pci_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	/* TODO: can we करो somethings here ? */
	/* It seems hw only cache one entry so we should discard this
	 * entry otherwise अगर first GPU GART पढ़ो hit this entry it
	 * could end up in wrong address. */
पूर्ण

पूर्णांक r100_pci_gart_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.ptr) अणु
		WARN(1, "R100 PCI GART already initialized\n");
		वापस 0;
	पूर्ण
	/* Initialize common gart काष्ठाure */
	r = radeon_gart_init(rdev);
	अगर (r)
		वापस r;
	rdev->gart.table_size = rdev->gart.num_gpu_pages * 4;
	rdev->asic->gart.tlb_flush = &r100_pci_gart_tlb_flush;
	rdev->asic->gart.get_page_entry = &r100_pci_gart_get_page_entry;
	rdev->asic->gart.set_page = &r100_pci_gart_set_page;
	वापस radeon_gart_table_ram_alloc(rdev);
पूर्ण

पूर्णांक r100_pci_gart_enable(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* discard memory request outside of configured range */
	पंचांगp = RREG32(RADEON_AIC_CNTL) | RADEON_DIS_OUT_OF_PCI_GART_ACCESS;
	WREG32(RADEON_AIC_CNTL, पंचांगp);
	/* set address range क्रम PCI address translate */
	WREG32(RADEON_AIC_LO_ADDR, rdev->mc.gtt_start);
	WREG32(RADEON_AIC_HI_ADDR, rdev->mc.gtt_end);
	/* set PCI GART page-table base address */
	WREG32(RADEON_AIC_PT_BASE, rdev->gart.table_addr);
	पंचांगp = RREG32(RADEON_AIC_CNTL) | RADEON_PCIGART_TRANSLATE_EN;
	WREG32(RADEON_AIC_CNTL, पंचांगp);
	r100_pci_gart_tlb_flush(rdev);
	DRM_INFO("PCI GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

व्योम r100_pci_gart_disable(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* discard memory request outside of configured range */
	पंचांगp = RREG32(RADEON_AIC_CNTL) | RADEON_DIS_OUT_OF_PCI_GART_ACCESS;
	WREG32(RADEON_AIC_CNTL, पंचांगp & ~RADEON_PCIGART_TRANSLATE_EN);
	WREG32(RADEON_AIC_LO_ADDR, 0);
	WREG32(RADEON_AIC_HI_ADDR, 0);
पूर्ण

uपूर्णांक64_t r100_pci_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags)
अणु
	वापस addr;
पूर्ण

व्योम r100_pci_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			    uपूर्णांक64_t entry)
अणु
	u32 *gtt = rdev->gart.ptr;
	gtt[i] = cpu_to_le32(lower_32_bits(entry));
पूर्ण

व्योम r100_pci_gart_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_gart_fini(rdev);
	r100_pci_gart_disable(rdev);
	radeon_gart_table_ram_मुक्त(rdev);
पूर्ण

पूर्णांक r100_irq_set(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp = 0;

	अगर (!rdev->irq.installed) अणु
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		WREG32(R_000040_GEN_INT_CNTL, 0);
		वापस -EINVAL;
	पूर्ण
	अगर (atomic_पढ़ो(&rdev->irq.ring_पूर्णांक[RADEON_RING_TYPE_GFX_INDEX])) अणु
		पंचांगp |= RADEON_SW_INT_ENABLE;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[0] ||
	    atomic_पढ़ो(&rdev->irq.pflip[0])) अणु
		पंचांगp |= RADEON_CRTC_VBLANK_MASK;
	पूर्ण
	अगर (rdev->irq.crtc_vblank_पूर्णांक[1] ||
	    atomic_पढ़ो(&rdev->irq.pflip[1])) अणु
		पंचांगp |= RADEON_CRTC2_VBLANK_MASK;
	पूर्ण
	अगर (rdev->irq.hpd[0]) अणु
		पंचांगp |= RADEON_FP_DETECT_MASK;
	पूर्ण
	अगर (rdev->irq.hpd[1]) अणु
		पंचांगp |= RADEON_FP2_DETECT_MASK;
	पूर्ण
	WREG32(RADEON_GEN_INT_CNTL, पंचांगp);

	/* पढ़ो back to post the ग_लिखो */
	RREG32(RADEON_GEN_INT_CNTL);

	वापस 0;
पूर्ण

व्योम r100_irq_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	WREG32(R_000040_GEN_INT_CNTL, 0);
	/* Wait and acknowledge irq */
	mdelay(1);
	पंचांगp = RREG32(R_000044_GEN_INT_STATUS);
	WREG32(R_000044_GEN_INT_STATUS, पंचांगp);
पूर्ण

अटल uपूर्णांक32_t r100_irq_ack(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t irqs = RREG32(RADEON_GEN_INT_STATUS);
	uपूर्णांक32_t irq_mask = RADEON_SW_INT_TEST |
		RADEON_CRTC_VBLANK_STAT | RADEON_CRTC2_VBLANK_STAT |
		RADEON_FP_DETECT_STAT | RADEON_FP2_DETECT_STAT;

	अगर (irqs) अणु
		WREG32(RADEON_GEN_INT_STATUS, irqs);
	पूर्ण
	वापस irqs & irq_mask;
पूर्ण

पूर्णांक r100_irq_process(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t status, msi_rearm;
	bool queue_hotplug = false;

	status = r100_irq_ack(rdev);
	अगर (!status) अणु
		वापस IRQ_NONE;
	पूर्ण
	अगर (rdev->shutकरोwn) अणु
		वापस IRQ_NONE;
	पूर्ण
	जबतक (status) अणु
		/* SW पूर्णांकerrupt */
		अगर (status & RADEON_SW_INT_TEST) अणु
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
		पूर्ण
		/* Vertical blank पूर्णांकerrupts */
		अगर (status & RADEON_CRTC_VBLANK_STAT) अणु
			अगर (rdev->irq.crtc_vblank_पूर्णांक[0]) अणु
				drm_handle_vblank(rdev->ddev, 0);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			पूर्ण
			अगर (atomic_पढ़ो(&rdev->irq.pflip[0]))
				radeon_crtc_handle_vblank(rdev, 0);
		पूर्ण
		अगर (status & RADEON_CRTC2_VBLANK_STAT) अणु
			अगर (rdev->irq.crtc_vblank_पूर्णांक[1]) अणु
				drm_handle_vblank(rdev->ddev, 1);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			पूर्ण
			अगर (atomic_पढ़ो(&rdev->irq.pflip[1]))
				radeon_crtc_handle_vblank(rdev, 1);
		पूर्ण
		अगर (status & RADEON_FP_DETECT_STAT) अणु
			queue_hotplug = true;
			DRM_DEBUG("HPD1\n");
		पूर्ण
		अगर (status & RADEON_FP2_DETECT_STAT) अणु
			queue_hotplug = true;
			DRM_DEBUG("HPD2\n");
		पूर्ण
		status = r100_irq_ack(rdev);
	पूर्ण
	अगर (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	अगर (rdev->msi_enabled) अणु
		चयन (rdev->family) अणु
		हाल CHIP_RS400:
		हाल CHIP_RS480:
			msi_rearm = RREG32(RADEON_AIC_CNTL) & ~RS400_MSI_REARM;
			WREG32(RADEON_AIC_CNTL, msi_rearm);
			WREG32(RADEON_AIC_CNTL, msi_rearm | RS400_MSI_REARM);
			अवरोध;
		शेष:
			WREG32(RADEON_MSI_REARM_EN, RV370_MSI_REARM_EN);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

u32 r100_get_vblank_counter(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अगर (crtc == 0)
		वापस RREG32(RADEON_CRTC_CRNT_FRAME);
	अन्यथा
		वापस RREG32(RADEON_CRTC2_CRNT_FRAME);
पूर्ण

/**
 * r100_ring_hdp_flush - flush Host Data Path via the ring buffer
 * @rdev: radeon device काष्ठाure
 * @ring: ring buffer काष्ठा क्रम emitting packets
 */
अटल व्योम r100_ring_hdp_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_HOST_PATH_CNTL, 0));
	radeon_ring_ग_लिखो(ring, rdev->config.r100.hdp_cntl |
				RADEON_HDP_READ_BUFFER_INVALIDATE);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_HOST_PATH_CNTL, 0));
	radeon_ring_ग_लिखो(ring, rdev->config.r100.hdp_cntl);
पूर्ण

/* Who ever call radeon_fence_emit should call ring_lock and ask
 * क्रम enough space (today caller are ib schedule and buffer move) */
व्योम r100_fence_ring_emit(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];

	/* We have to make sure that caches are flushed beक्रमe
	 * CPU might पढ़ो something from VRAM. */
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, RADEON_RB3D_DC_FLUSH_ALL);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_RB3D_ZCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, RADEON_RB3D_ZC_FLUSH_ALL);
	/* Wait until IDLE & CLEAN */
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring, RADEON_WAIT_2D_IDLECLEAN | RADEON_WAIT_3D_IDLECLEAN);
	r100_ring_hdp_flush(rdev, ring);
	/* Emit fence sequence & fire IRQ */
	radeon_ring_ग_लिखो(ring, PACKET0(rdev->fence_drv[fence->ring].scratch_reg, 0));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_GEN_INT_STATUS, 0));
	radeon_ring_ग_लिखो(ring, RADEON_SW_INT_FIRE);
पूर्ण

bool r100_semaphore_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ring *ring,
			      काष्ठा radeon_semaphore *semaphore,
			      bool emit_रुको)
अणु
	/* Unused on older asics, since we करोn't have semaphores or multiple rings */
	BUG();
	वापस false;
पूर्ण

काष्ठा radeon_fence *r100_copy_blit(काष्ठा radeon_device *rdev,
				    uपूर्णांक64_t src_offset,
				    uपूर्णांक64_t dst_offset,
				    अचिन्हित num_gpu_pages,
				    काष्ठा dma_resv *resv)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	काष्ठा radeon_fence *fence;
	uपूर्णांक32_t cur_pages;
	uपूर्णांक32_t stride_bytes = RADEON_GPU_PAGE_SIZE;
	uपूर्णांक32_t pitch;
	uपूर्णांक32_t stride_pixels;
	अचिन्हित ndw;
	पूर्णांक num_loops;
	पूर्णांक r = 0;

	/* radeon limited to 16k stride */
	stride_bytes &= 0x3fff;
	/* radeon pitch is /64 */
	pitch = stride_bytes / 64;
	stride_pixels = stride_bytes / 4;
	num_loops = DIV_ROUND_UP(num_gpu_pages, 8191);

	/* Ask क्रम enough room क्रम blit + flush + fence */
	ndw = 64 + (10 * num_loops);
	r = radeon_ring_lock(rdev, ring, ndw);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d) asking for %u dw.\n", r, ndw);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	जबतक (num_gpu_pages > 0) अणु
		cur_pages = num_gpu_pages;
		अगर (cur_pages > 8191) अणु
			cur_pages = 8191;
		पूर्ण
		num_gpu_pages -= cur_pages;

		/* pages are in Y direction - height
		   page width in X direction - width */
		radeon_ring_ग_लिखो(ring, PACKET3(PACKET3_BITBLT_MULTI, 8));
		radeon_ring_ग_लिखो(ring,
				  RADEON_GMC_SRC_PITCH_OFFSET_CNTL |
				  RADEON_GMC_DST_PITCH_OFFSET_CNTL |
				  RADEON_GMC_SRC_CLIPPING |
				  RADEON_GMC_DST_CLIPPING |
				  RADEON_GMC_BRUSH_NONE |
				  (RADEON_COLOR_FORMAT_ARGB8888 << 8) |
				  RADEON_GMC_SRC_DATATYPE_COLOR |
				  RADEON_ROP3_S |
				  RADEON_DP_SRC_SOURCE_MEMORY |
				  RADEON_GMC_CLR_CMP_CNTL_DIS |
				  RADEON_GMC_WR_MSK_DIS);
		radeon_ring_ग_लिखो(ring, (pitch << 22) | (src_offset >> 10));
		radeon_ring_ग_लिखो(ring, (pitch << 22) | (dst_offset >> 10));
		radeon_ring_ग_लिखो(ring, (0x1fff) | (0x1fff << 16));
		radeon_ring_ग_लिखो(ring, 0);
		radeon_ring_ग_लिखो(ring, (0x1fff) | (0x1fff << 16));
		radeon_ring_ग_लिखो(ring, num_gpu_pages);
		radeon_ring_ग_लिखो(ring, num_gpu_pages);
		radeon_ring_ग_लिखो(ring, cur_pages | (stride_pixels << 16));
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, RADEON_RB2D_DC_FLUSH_ALL);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring,
			  RADEON_WAIT_2D_IDLECLEAN |
			  RADEON_WAIT_HOST_IDLECLEAN |
			  RADEON_WAIT_DMA_GUI_IDLE);
	r = radeon_fence_emit(rdev, &fence, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		radeon_ring_unlock_unकरो(rdev, ring);
		वापस ERR_PTR(r);
	पूर्ण
	radeon_ring_unlock_commit(rdev, ring, false);
	वापस fence;
पूर्ण

अटल पूर्णांक r100_cp_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	u32 पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(R_000E40_RBBM_STATUS);
		अगर (!G_000E40_CP_CMDSTRM_BUSY(पंचांगp)) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

व्योम r100_ring_start(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	पूर्णांक r;

	r = radeon_ring_lock(rdev, ring, 2);
	अगर (r) अणु
		वापस;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_ISYNC_CNTL, 0));
	radeon_ring_ग_लिखो(ring,
			  RADEON_ISYNC_ANY2D_IDLE3D |
			  RADEON_ISYNC_ANY3D_IDLE2D |
			  RADEON_ISYNC_WAIT_IDLEGUI |
			  RADEON_ISYNC_CPSCRATCH_IDLEGUI);
	radeon_ring_unlock_commit(rdev, ring, false);
पूर्ण


/* Load the microcode क्रम the CP */
अटल पूर्णांक r100_cp_init_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर अक्षर *fw_name = शून्य;
	पूर्णांक err;

	DRM_DEBUG_KMS("\n");

	अगर ((rdev->family == CHIP_R100) || (rdev->family == CHIP_RV100) ||
	    (rdev->family == CHIP_RV200) || (rdev->family == CHIP_RS100) ||
	    (rdev->family == CHIP_RS200)) अणु
		DRM_INFO("Loading R100 Microcode\n");
		fw_name = FIRMWARE_R100;
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_R200) ||
		   (rdev->family == CHIP_RV250) ||
		   (rdev->family == CHIP_RV280) ||
		   (rdev->family == CHIP_RS300)) अणु
		DRM_INFO("Loading R200 Microcode\n");
		fw_name = FIRMWARE_R200;
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_R300) ||
		   (rdev->family == CHIP_R350) ||
		   (rdev->family == CHIP_RV350) ||
		   (rdev->family == CHIP_RV380) ||
		   (rdev->family == CHIP_RS400) ||
		   (rdev->family == CHIP_RS480)) अणु
		DRM_INFO("Loading R300 Microcode\n");
		fw_name = FIRMWARE_R300;
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_R420) ||
		   (rdev->family == CHIP_R423) ||
		   (rdev->family == CHIP_RV410)) अणु
		DRM_INFO("Loading R400 Microcode\n");
		fw_name = FIRMWARE_R420;
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_RS690) ||
		   (rdev->family == CHIP_RS740)) अणु
		DRM_INFO("Loading RS690/RS740 Microcode\n");
		fw_name = FIRMWARE_RS690;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_RS600) अणु
		DRM_INFO("Loading RS600 Microcode\n");
		fw_name = FIRMWARE_RS600;
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_RV515) ||
		   (rdev->family == CHIP_R520) ||
		   (rdev->family == CHIP_RV530) ||
		   (rdev->family == CHIP_R580) ||
		   (rdev->family == CHIP_RV560) ||
		   (rdev->family == CHIP_RV570)) अणु
		DRM_INFO("Loading R500 Microcode\n");
		fw_name = FIRMWARE_R520;
	पूर्ण

	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	अगर (err) अणु
		pr_err("radeon_cp: Failed to load firmware \"%s\"\n", fw_name);
	पूर्ण अन्यथा अगर (rdev->me_fw->size % 8) अणु
		pr_err("radeon_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->me_fw->size, fw_name);
		err = -EINVAL;
		release_firmware(rdev->me_fw);
		rdev->me_fw = शून्य;
	पूर्ण
	वापस err;
पूर्ण

u32 r100_gfx_get_rptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring)
अणु
	u32 rptr;

	अगर (rdev->wb.enabled)
		rptr = le32_to_cpu(rdev->wb.wb[ring->rptr_offs/4]);
	अन्यथा
		rptr = RREG32(RADEON_CP_RB_RPTR);

	वापस rptr;
पूर्ण

u32 r100_gfx_get_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring)
अणु
	वापस RREG32(RADEON_CP_RB_WPTR);
पूर्ण

व्योम r100_gfx_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	WREG32(RADEON_CP_RB_WPTR, ring->wptr);
	(व्योम)RREG32(RADEON_CP_RB_WPTR);
पूर्ण

अटल व्योम r100_cp_load_microcode(काष्ठा radeon_device *rdev)
अणु
	स्थिर __be32 *fw_data;
	पूर्णांक i, size;

	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण

	अगर (rdev->me_fw) अणु
		size = rdev->me_fw->size / 4;
		fw_data = (स्थिर __be32 *)&rdev->me_fw->data[0];
		WREG32(RADEON_CP_ME_RAM_ADDR, 0);
		क्रम (i = 0; i < size; i += 2) अणु
			WREG32(RADEON_CP_ME_RAM_DATAH,
			       be32_to_cpup(&fw_data[i]));
			WREG32(RADEON_CP_ME_RAM_DATAL,
			       be32_to_cpup(&fw_data[i + 1]));
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक r100_cp_init(काष्ठा radeon_device *rdev, अचिन्हित ring_size)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	अचिन्हित rb_bufsz;
	अचिन्हित rb_blksz;
	अचिन्हित max_fetch;
	अचिन्हित pre_ग_लिखो_समयr;
	अचिन्हित pre_ग_लिखो_limit;
	अचिन्हित indirect2_start;
	अचिन्हित indirect1_start;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;

	r100_debugfs_cp_init(rdev);
	अगर (!rdev->me_fw) अणु
		r = r100_cp_init_microcode(rdev);
		अगर (r) अणु
			DRM_ERROR("Failed to load firmware!\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 8);
	ring_size = (1 << (rb_bufsz + 1)) * 4;
	r100_cp_load_microcode(rdev);
	r = radeon_ring_init(rdev, ring, ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	अगर (r) अणु
		वापस r;
	पूर्ण
	/* Each समय the cp पढ़ो 1024 bytes (16 dword/quadword) update
	 * the rptr copy in प्रणाली ram */
	rb_blksz = 9;
	/* cp will पढ़ो 128bytes at a समय (4 dwords) */
	max_fetch = 1;
	ring->align_mask = 16 - 1;
	/* Write to CP_RB_WPTR will be delayed क्रम pre_ग_लिखो_समयr घड़ीs */
	pre_ग_लिखो_समयr = 64;
	/* Force CP_RB_WPTR ग_लिखो अगर written more than one समय beक्रमe the
	 * delay expire
	 */
	pre_ग_लिखो_limit = 0;
	/* Setup the cp cache like this (cache size is 96 dwords) :
	 *	RING		0  to 15
	 *	INसूचीECT1	16 to 79
	 *	INसूचीECT2	80 to 95
	 * So ring cache size is 16dwords (> (2 * max_fetch = 2 * 4dwords))
	 *    indirect1 cache size is 64dwords (> (2 * max_fetch = 2 * 4dwords))
	 *    indirect2 cache size is 16dwords (> (2 * max_fetch = 2 * 4dwords))
	 * Idea being that most of the gpu cmd will be through indirect1 buffer
	 * so it माला_लो the bigger cache.
	 */
	indirect2_start = 80;
	indirect1_start = 16;
	/* cp setup */
	WREG32(0x718, pre_ग_लिखो_समयr | (pre_ग_लिखो_limit << 28));
	पंचांगp = (REG_SET(RADEON_RB_BUFSZ, rb_bufsz) |
	       REG_SET(RADEON_RB_BLKSZ, rb_blksz) |
	       REG_SET(RADEON_MAX_FETCH, max_fetch));
#अगर_घोषित __BIG_ENDIAN
	पंचांगp |= RADEON_BUF_SWAP_32BIT;
#पूर्ण_अगर
	WREG32(RADEON_CP_RB_CNTL, पंचांगp | RADEON_RB_NO_UPDATE);

	/* Set ring address */
	DRM_INFO("radeon: ring at 0x%016lX\n", (अचिन्हित दीर्घ)ring->gpu_addr);
	WREG32(RADEON_CP_RB_BASE, ring->gpu_addr);
	/* Force पढ़ो & ग_लिखो ptr to 0 */
	WREG32(RADEON_CP_RB_CNTL, पंचांगp | RADEON_RB_RPTR_WR_ENA | RADEON_RB_NO_UPDATE);
	WREG32(RADEON_CP_RB_RPTR_WR, 0);
	ring->wptr = 0;
	WREG32(RADEON_CP_RB_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(R_00070C_CP_RB_RPTR_ADDR,
		S_00070C_RB_RPTR_ADDR((rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) >> 2));
	WREG32(R_000774_SCRATCH_ADDR, rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET);

	अगर (rdev->wb.enabled)
		WREG32(R_000770_SCRATCH_UMSK, 0xff);
	अन्यथा अणु
		पंचांगp |= RADEON_RB_NO_UPDATE;
		WREG32(R_000770_SCRATCH_UMSK, 0);
	पूर्ण

	WREG32(RADEON_CP_RB_CNTL, पंचांगp);
	udelay(10);
	/* Set cp mode to bus mastering & enable cp*/
	WREG32(RADEON_CP_CSQ_MODE,
	       REG_SET(RADEON_INसूचीECT2_START, indirect2_start) |
	       REG_SET(RADEON_INसूचीECT1_START, indirect1_start));
	WREG32(RADEON_CP_RB_WPTR_DELAY, 0);
	WREG32(RADEON_CP_CSQ_MODE, 0x00004D4D);
	WREG32(RADEON_CP_CSQ_CNTL, RADEON_CSQ_PRIBM_INDBM);

	/* at this poपूर्णांक everything should be setup correctly to enable master */
	pci_set_master(rdev->pdev);

	radeon_ring_start(rdev, RADEON_RING_TYPE_GFX_INDEX, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, ring);
	अगर (r) अणु
		DRM_ERROR("radeon: cp isn't working (%d).\n", r);
		वापस r;
	पूर्ण
	ring->पढ़ोy = true;
	radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	अगर (!ring->rptr_save_reg /* not resuming from suspend */
	    && radeon_ring_supports_scratch_reg(rdev, ring)) अणु
		r = radeon_scratch_get(rdev, &ring->rptr_save_reg);
		अगर (r) अणु
			DRM_ERROR("failed to get scratch reg for rptr save (%d).\n", r);
			ring->rptr_save_reg = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम r100_cp_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (r100_cp_रुको_क्रम_idle(rdev)) अणु
		DRM_ERROR("Wait for CP idle timeout, shutting down CP.\n");
	पूर्ण
	/* Disable ring */
	r100_cp_disable(rdev);
	radeon_scratch_मुक्त(rdev, rdev->ring[RADEON_RING_TYPE_GFX_INDEX].rptr_save_reg);
	radeon_ring_fini(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	DRM_INFO("radeon: cp finalized\n");
पूर्ण

व्योम r100_cp_disable(काष्ठा radeon_device *rdev)
अणु
	/* Disable ring */
	radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
	WREG32(RADEON_CP_CSQ_MODE, 0);
	WREG32(RADEON_CP_CSQ_CNTL, 0);
	WREG32(R_000770_SCRATCH_UMSK, 0);
	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण
पूर्ण

/*
 * CS functions
 */
पूर्णांक r100_reloc_pitch_offset(काष्ठा radeon_cs_parser *p,
			    काष्ठा radeon_cs_packet *pkt,
			    अचिन्हित idx,
			    अचिन्हित reg)
अणु
	पूर्णांक r;
	u32 tile_flags = 0;
	u32 पंचांगp;
	काष्ठा radeon_bo_list *reloc;
	u32 value;

	r = radeon_cs_packet_next_reloc(p, &reloc, 0);
	अगर (r) अणु
		DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
			  idx, reg);
		radeon_cs_dump_packet(p, pkt);
		वापस r;
	पूर्ण

	value = radeon_get_ib_value(p, idx);
	पंचांगp = value & 0x003fffff;
	पंचांगp += (((u32)reloc->gpu_offset) >> 10);

	अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
		अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
			tile_flags |= RADEON_DST_TILE_MACRO;
		अगर (reloc->tiling_flags & RADEON_TILING_MICRO) अणु
			अगर (reg == RADEON_SRC_PITCH_OFFSET) अणु
				DRM_ERROR("Cannot src blit from microtiled surface\n");
				radeon_cs_dump_packet(p, pkt);
				वापस -EINVAL;
			पूर्ण
			tile_flags |= RADEON_DST_TILE_MICRO;
		पूर्ण

		पंचांगp |= tile_flags;
		p->ib.ptr[idx] = (value & 0x3fc00000) | पंचांगp;
	पूर्ण अन्यथा
		p->ib.ptr[idx] = (value & 0xffc00000) | पंचांगp;
	वापस 0;
पूर्ण

पूर्णांक r100_packet3_load_vbpntr(काष्ठा radeon_cs_parser *p,
			     काष्ठा radeon_cs_packet *pkt,
			     पूर्णांक idx)
अणु
	अचिन्हित c, i;
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r100_cs_track *track;
	पूर्णांक r = 0;
	अस्थिर uपूर्णांक32_t *ib;
	u32 idx_value;

	ib = p->ib.ptr;
	track = (काष्ठा r100_cs_track *)p->track;
	c = radeon_get_ib_value(p, idx++) & 0x1F;
	अगर (c > 16) अणु
	    DRM_ERROR("Only 16 vertex buffers are allowed %d\n",
		      pkt->opcode);
	    radeon_cs_dump_packet(p, pkt);
	    वापस -EINVAL;
	पूर्ण
	track->num_arrays = c;
	क्रम (i = 0; i < (c - 1); i+=2, idx+=3) अणु
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for packet3 %d\n",
				  pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		idx_value = radeon_get_ib_value(p, idx);
		ib[idx+1] = radeon_get_ib_value(p, idx + 1) + ((u32)reloc->gpu_offset);

		track->arrays[i + 0].esize = idx_value >> 8;
		track->arrays[i + 0].robj = reloc->robj;
		track->arrays[i + 0].esize &= 0x7F;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for packet3 %d\n",
				  pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx+2] = radeon_get_ib_value(p, idx + 2) + ((u32)reloc->gpu_offset);
		track->arrays[i + 1].robj = reloc->robj;
		track->arrays[i + 1].esize = idx_value >> 24;
		track->arrays[i + 1].esize &= 0x7F;
	पूर्ण
	अगर (c & 1) अणु
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for packet3 %d\n",
					  pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		idx_value = radeon_get_ib_value(p, idx);
		ib[idx+1] = radeon_get_ib_value(p, idx + 1) + ((u32)reloc->gpu_offset);
		track->arrays[i + 0].robj = reloc->robj;
		track->arrays[i + 0].esize = idx_value >> 8;
		track->arrays[i + 0].esize &= 0x7F;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक r100_cs_parse_packet0(काष्ठा radeon_cs_parser *p,
			  काष्ठा radeon_cs_packet *pkt,
			  स्थिर अचिन्हित *auth, अचिन्हित n,
			  radeon_packet0_check_t check)
अणु
	अचिन्हित reg;
	अचिन्हित i, j, m;
	अचिन्हित idx;
	पूर्णांक r;

	idx = pkt->idx + 1;
	reg = pkt->reg;
	/* Check that रेजिस्टर fall पूर्णांकo रेजिस्टर range
	 * determined by the number of entry (n) in the
	 * safe रेजिस्टर biपंचांगap.
	 */
	अगर (pkt->one_reg_wr) अणु
		अगर ((reg >> 7) > n) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (((reg + (pkt->count << 2)) >> 7) > n) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= pkt->count; i++, idx++) अणु
		j = (reg >> 7);
		m = 1 << ((reg >> 2) & 31);
		अगर (auth[j] & m) अणु
			r = check(p, pkt, idx, reg);
			अगर (r) अणु
				वापस r;
			पूर्ण
		पूर्ण
		अगर (pkt->one_reg_wr) अणु
			अगर (!(auth[j] & m)) अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			reg += 4;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * r100_cs_packet_next_vline() - parse userspace VLINE packet
 * @p:		parser काष्ठाure holding parsing context.
 *
 * Userspace sends a special sequence क्रम VLINE रुकोs.
 * PACKET0 - VLINE_START_END + value
 * PACKET0 - WAIT_UNTIL +_value
 * RELOC (P3) - crtc_id in reloc.
 *
 * This function parses this and relocates the VLINE START END
 * and WAIT UNTIL packets to the correct crtc.
 * It also detects a चयनed off crtc and nulls out the
 * रुको in that हाल.
 */
पूर्णांक r100_cs_packet_parse_vline(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	काष्ठा radeon_cs_packet p3reloc, रुकोreloc;
	पूर्णांक crtc_id;
	पूर्णांक r;
	uपूर्णांक32_t header, h_idx, reg;
	अस्थिर uपूर्णांक32_t *ib;

	ib = p->ib.ptr;

	/* parse the रुको until */
	r = radeon_cs_packet_parse(p, &रुकोreloc, p->idx);
	अगर (r)
		वापस r;

	/* check its a रुको until and only 1 count */
	अगर (रुकोreloc.reg != RADEON_WAIT_UNTIL ||
	    रुकोreloc.count != 0) अणु
		DRM_ERROR("vline wait had illegal wait until segment\n");
		वापस -EINVAL;
	पूर्ण

	अगर (radeon_get_ib_value(p, रुकोreloc.idx + 1) != RADEON_WAIT_CRTC_VLINE) अणु
		DRM_ERROR("vline wait had illegal wait until\n");
		वापस -EINVAL;
	पूर्ण

	/* jump over the NOP */
	r = radeon_cs_packet_parse(p, &p3reloc, p->idx + रुकोreloc.count + 2);
	अगर (r)
		वापस r;

	h_idx = p->idx - 2;
	p->idx += रुकोreloc.count + 2;
	p->idx += p3reloc.count + 2;

	header = radeon_get_ib_value(p, h_idx);
	crtc_id = radeon_get_ib_value(p, h_idx + 5);
	reg = R100_CP_PACKET0_GET_REG(header);
	crtc = drm_crtc_find(p->rdev->ddev, p->filp, crtc_id);
	अगर (!crtc) अणु
		DRM_ERROR("cannot find crtc %d\n", crtc_id);
		वापस -ENOENT;
	पूर्ण
	radeon_crtc = to_radeon_crtc(crtc);
	crtc_id = radeon_crtc->crtc_id;

	अगर (!crtc->enabled) अणु
		/* अगर the CRTC isn't enabled - we need to nop out the रुको until */
		ib[h_idx + 2] = PACKET2(0);
		ib[h_idx + 3] = PACKET2(0);
	पूर्ण अन्यथा अगर (crtc_id == 1) अणु
		चयन (reg) अणु
		हाल AVIVO_D1MODE_VLINE_START_END:
			header &= ~R300_CP_PACKET0_REG_MASK;
			header |= AVIVO_D2MODE_VLINE_START_END >> 2;
			अवरोध;
		हाल RADEON_CRTC_GUI_TRIG_VLINE:
			header &= ~R300_CP_PACKET0_REG_MASK;
			header |= RADEON_CRTC2_GUI_TRIG_VLINE >> 2;
			अवरोध;
		शेष:
			DRM_ERROR("unknown crtc reloc\n");
			वापस -EINVAL;
		पूर्ण
		ib[h_idx] = header;
		ib[h_idx + 3] |= RADEON_ENG_DISPLAY_SELECT_CRTC1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r100_get_vtx_size(uपूर्णांक32_t vtx_fmt)
अणु
	पूर्णांक vtx_size;
	vtx_size = 2;
	/* ordered according to bits in spec */
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_W0)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_FPCOLOR)
		vtx_size += 3;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_FPALPHA)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_PKCOLOR)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_FPSPEC)
		vtx_size += 3;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_FPFOG)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_PKSPEC)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_ST0)
		vtx_size += 2;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_ST1)
		vtx_size += 2;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_Q1)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_ST2)
		vtx_size += 2;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_Q2)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_ST3)
		vtx_size += 2;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_Q3)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_Q0)
		vtx_size++;
	/* blend weight */
	अगर (vtx_fmt & (0x7 << 15))
		vtx_size += (vtx_fmt >> 15) & 0x7;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_N0)
		vtx_size += 3;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_XY1)
		vtx_size += 2;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_Z1)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_W1)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_N1)
		vtx_size++;
	अगर (vtx_fmt & RADEON_SE_VTX_FMT_Z)
		vtx_size++;
	वापस vtx_size;
पूर्ण

अटल पूर्णांक r100_packet0_check(काष्ठा radeon_cs_parser *p,
			      काष्ठा radeon_cs_packet *pkt,
			      अचिन्हित idx, अचिन्हित reg)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r100_cs_track *track;
	अस्थिर uपूर्णांक32_t *ib;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;
	पूर्णांक i, face;
	u32 tile_flags = 0;
	u32 idx_value;

	ib = p->ib.ptr;
	track = (काष्ठा r100_cs_track *)p->track;

	idx_value = radeon_get_ib_value(p, idx);

	चयन (reg) अणु
	हाल RADEON_CRTC_GUI_TRIG_VLINE:
		r = r100_cs_packet_parse_vline(p);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		अवरोध;
		/* FIXME: only allow PACKET3 blit? easier to check क्रम out of
		 * range access */
	हाल RADEON_DST_PITCH_OFFSET:
	हाल RADEON_SRC_PITCH_OFFSET:
		r = r100_reloc_pitch_offset(p, pkt, idx, reg);
		अगर (r)
			वापस r;
		अवरोध;
	हाल RADEON_RB3D_DEPTHOFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->zb.robj = reloc->robj;
		track->zb.offset = idx_value;
		track->zb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल RADEON_RB3D_COLOROFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->cb[0].robj = reloc->robj;
		track->cb[0].offset = idx_value;
		track->cb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल RADEON_PP_TXOFFSET_0:
	हाल RADEON_PP_TXOFFSET_1:
	हाल RADEON_PP_TXOFFSET_2:
		i = (reg - RADEON_PP_TXOFFSET_0) / 24;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= RADEON_TXO_MACRO_TILE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= RADEON_TXO_MICRO_TILE_X2;

			पंचांगp = idx_value & ~(0x7 << 2);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp + ((u32)reloc->gpu_offset);
		पूर्ण अन्यथा
			ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[i].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_CUBIC_OFFSET_T0_0:
	हाल RADEON_PP_CUBIC_OFFSET_T0_1:
	हाल RADEON_PP_CUBIC_OFFSET_T0_2:
	हाल RADEON_PP_CUBIC_OFFSET_T0_3:
	हाल RADEON_PP_CUBIC_OFFSET_T0_4:
		i = (reg - RADEON_PP_CUBIC_OFFSET_T0_0) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->textures[0].cube_info[i].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[0].cube_info[i].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_CUBIC_OFFSET_T1_0:
	हाल RADEON_PP_CUBIC_OFFSET_T1_1:
	हाल RADEON_PP_CUBIC_OFFSET_T1_2:
	हाल RADEON_PP_CUBIC_OFFSET_T1_3:
	हाल RADEON_PP_CUBIC_OFFSET_T1_4:
		i = (reg - RADEON_PP_CUBIC_OFFSET_T1_0) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->textures[1].cube_info[i].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[1].cube_info[i].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_CUBIC_OFFSET_T2_0:
	हाल RADEON_PP_CUBIC_OFFSET_T2_1:
	हाल RADEON_PP_CUBIC_OFFSET_T2_2:
	हाल RADEON_PP_CUBIC_OFFSET_T2_3:
	हाल RADEON_PP_CUBIC_OFFSET_T2_4:
		i = (reg - RADEON_PP_CUBIC_OFFSET_T2_0) / 4;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->textures[2].cube_info[i].offset = idx_value;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		track->textures[2].cube_info[i].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_RE_WIDTH_HEIGHT:
		track->maxy = ((idx_value >> 16) & 0x7FF);
		track->cb_dirty = true;
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_COLORPITCH:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= RADEON_COLOR_TILE_ENABLE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= RADEON_COLOR_MICROTILE_ENABLE;

			पंचांगp = idx_value & ~(0x7 << 16);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp;
		पूर्ण अन्यथा
			ib[idx] = idx_value;

		track->cb[0].pitch = idx_value & RADEON_COLORPITCH_MASK;
		track->cb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_DEPTHPITCH:
		track->zb.pitch = idx_value & RADEON_DEPTHPITCH_MASK;
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_CNTL:
		चयन ((idx_value >> RADEON_RB3D_COLOR_FORMAT_SHIFT) & 0x1f) अणु
		हाल 7:
		हाल 8:
		हाल 9:
		हाल 11:
		हाल 12:
			track->cb[0].cpp = 1;
			अवरोध;
		हाल 3:
		हाल 4:
		हाल 15:
			track->cb[0].cpp = 2;
			अवरोध;
		हाल 6:
			track->cb[0].cpp = 4;
			अवरोध;
		शेष:
			DRM_ERROR("Invalid color buffer format (%d) !\n",
				  ((idx_value >> RADEON_RB3D_COLOR_FORMAT_SHIFT) & 0x1f));
			वापस -EINVAL;
		पूर्ण
		track->z_enabled = !!(idx_value & RADEON_Z_ENABLE);
		track->cb_dirty = true;
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_ZSTENCILCNTL:
		चयन (idx_value & 0xf) अणु
		हाल 0:
			track->zb.cpp = 2;
			अवरोध;
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 9:
		हाल 11:
			track->zb.cpp = 4;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		track->zb_dirty = true;
		अवरोध;
	हाल RADEON_RB3D_ZPASS_ADDR:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल RADEON_PP_CNTL:
		अणु
			uपूर्णांक32_t temp = idx_value >> 4;
			क्रम (i = 0; i < track->num_texture; i++)
				track->textures[i].enabled = !!(temp & (1 << i));
			track->tex_dirty = true;
		पूर्ण
		अवरोध;
	हाल RADEON_SE_VF_CNTL:
		track->vap_vf_cntl = idx_value;
		अवरोध;
	हाल RADEON_SE_VTX_FMT:
		track->vtx_size = r100_get_vtx_size(idx_value);
		अवरोध;
	हाल RADEON_PP_TEX_SIZE_0:
	हाल RADEON_PP_TEX_SIZE_1:
	हाल RADEON_PP_TEX_SIZE_2:
		i = (reg - RADEON_PP_TEX_SIZE_0) / 8;
		track->textures[i].width = (idx_value & RADEON_TEX_USIZE_MASK) + 1;
		track->textures[i].height = ((idx_value & RADEON_TEX_VSIZE_MASK) >> RADEON_TEX_VSIZE_SHIFT) + 1;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_TEX_PITCH_0:
	हाल RADEON_PP_TEX_PITCH_1:
	हाल RADEON_PP_TEX_PITCH_2:
		i = (reg - RADEON_PP_TEX_PITCH_0) / 8;
		track->textures[i].pitch = idx_value + 32;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_TXFILTER_0:
	हाल RADEON_PP_TXFILTER_1:
	हाल RADEON_PP_TXFILTER_2:
		i = (reg - RADEON_PP_TXFILTER_0) / 24;
		track->textures[i].num_levels = ((idx_value & RADEON_MAX_MIP_LEVEL_MASK)
						 >> RADEON_MAX_MIP_LEVEL_SHIFT);
		पंचांगp = (idx_value >> 23) & 0x7;
		अगर (पंचांगp == 2 || पंचांगp == 6)
			track->textures[i].roundup_w = false;
		पंचांगp = (idx_value >> 27) & 0x7;
		अगर (पंचांगp == 2 || पंचांगp == 6)
			track->textures[i].roundup_h = false;
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_TXFORMAT_0:
	हाल RADEON_PP_TXFORMAT_1:
	हाल RADEON_PP_TXFORMAT_2:
		i = (reg - RADEON_PP_TXFORMAT_0) / 24;
		अगर (idx_value & RADEON_TXFORMAT_NON_POWER2) अणु
			track->textures[i].use_pitch = true;
		पूर्ण अन्यथा अणु
			track->textures[i].use_pitch = false;
			track->textures[i].width = 1 << ((idx_value & RADEON_TXFORMAT_WIDTH_MASK) >> RADEON_TXFORMAT_WIDTH_SHIFT);
			track->textures[i].height = 1 << ((idx_value & RADEON_TXFORMAT_HEIGHT_MASK) >> RADEON_TXFORMAT_HEIGHT_SHIFT);
		पूर्ण
		अगर (idx_value & RADEON_TXFORMAT_CUBIC_MAP_ENABLE)
			track->textures[i].tex_coord_type = 2;
		चयन ((idx_value & RADEON_TXFORMAT_FORMAT_MASK)) अणु
		हाल RADEON_TXFORMAT_I8:
		हाल RADEON_TXFORMAT_RGB332:
		हाल RADEON_TXFORMAT_Y8:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल RADEON_TXFORMAT_AI88:
		हाल RADEON_TXFORMAT_ARGB1555:
		हाल RADEON_TXFORMAT_RGB565:
		हाल RADEON_TXFORMAT_ARGB4444:
		हाल RADEON_TXFORMAT_VYUY422:
		हाल RADEON_TXFORMAT_YVYU422:
		हाल RADEON_TXFORMAT_SHADOW16:
		हाल RADEON_TXFORMAT_LDUDV655:
		हाल RADEON_TXFORMAT_DUDV88:
			track->textures[i].cpp = 2;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल RADEON_TXFORMAT_ARGB8888:
		हाल RADEON_TXFORMAT_RGBA8888:
		हाल RADEON_TXFORMAT_SHADOW32:
		हाल RADEON_TXFORMAT_LDUDUV8888:
			track->textures[i].cpp = 4;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल RADEON_TXFORMAT_DXT1:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_DXT1;
			अवरोध;
		हाल RADEON_TXFORMAT_DXT23:
		हाल RADEON_TXFORMAT_DXT45:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_DXT35;
			अवरोध;
		पूर्ण
		track->textures[i].cube_info[4].width = 1 << ((idx_value >> 16) & 0xf);
		track->textures[i].cube_info[4].height = 1 << ((idx_value >> 20) & 0xf);
		track->tex_dirty = true;
		अवरोध;
	हाल RADEON_PP_CUBIC_FACES_0:
	हाल RADEON_PP_CUBIC_FACES_1:
	हाल RADEON_PP_CUBIC_FACES_2:
		पंचांगp = idx_value;
		i = (reg - RADEON_PP_CUBIC_FACES_0) / 4;
		क्रम (face = 0; face < 4; face++) अणु
			track->textures[i].cube_info[face].width = 1 << ((पंचांगp >> (face * 8)) & 0xf);
			track->textures[i].cube_info[face].height = 1 << ((पंचांगp >> ((face * 8) + 4)) & 0xf);
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	शेष:
		pr_err("Forbidden register 0x%04X in cs at %d\n", reg, idx);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r100_cs_track_check_pkt3_indx_buffer(काष्ठा radeon_cs_parser *p,
					 काष्ठा radeon_cs_packet *pkt,
					 काष्ठा radeon_bo *robj)
अणु
	अचिन्हित idx;
	u32 value;
	idx = pkt->idx + 1;
	value = radeon_get_ib_value(p, idx + 2);
	अगर ((value + 1) > radeon_bo_size(robj)) अणु
		DRM_ERROR("[drm] Buffer too small for PACKET3 INDX_BUFFER "
			  "(need %u have %lu) !\n",
			  value + 1,
			  radeon_bo_size(robj));
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r100_packet3_check(काष्ठा radeon_cs_parser *p,
			      काष्ठा radeon_cs_packet *pkt)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r100_cs_track *track;
	अचिन्हित idx;
	अस्थिर uपूर्णांक32_t *ib;
	पूर्णांक r;

	ib = p->ib.ptr;
	idx = pkt->idx + 1;
	track = (काष्ठा r100_cs_track *)p->track;
	चयन (pkt->opcode) अणु
	हाल PACKET3_3D_LOAD_VBPNTR:
		r = r100_packet3_load_vbpntr(p, pkt, idx);
		अगर (r)
			वापस r;
		अवरोध;
	हाल PACKET3_INDX_BUFFER:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for packet3 %d\n", pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx+1] = radeon_get_ib_value(p, idx+1) + ((u32)reloc->gpu_offset);
		r = r100_cs_track_check_pkt3_indx_buffer(p, pkt, reloc->robj);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल 0x23:
		/* 3D_RNDR_GEN_INDX_PRIM on r100/r200 */
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for packet3 %d\n", pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx] = radeon_get_ib_value(p, idx) + ((u32)reloc->gpu_offset);
		track->num_arrays = 1;
		track->vtx_size = r100_get_vtx_size(radeon_get_ib_value(p, idx + 2));

		track->arrays[0].robj = reloc->robj;
		track->arrays[0].esize = track->vtx_size;

		track->max_indx = radeon_get_ib_value(p, idx+1);

		track->vap_vf_cntl = radeon_get_ib_value(p, idx+3);
		track->immd_dwords = pkt->count - 1;
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
	हाल PACKET3_3D_DRAW_IMMD:
		अगर (((radeon_get_ib_value(p, idx + 1) >> 4) & 0x3) != 3) अणु
			DRM_ERROR("PRIM_WALK must be 3 for IMMD draw\n");
			वापस -EINVAL;
		पूर्ण
		track->vtx_size = r100_get_vtx_size(radeon_get_ib_value(p, idx + 0));
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		track->immd_dwords = pkt->count - 1;
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
		/* triggers drawing using in-packet vertex data */
	हाल PACKET3_3D_DRAW_IMMD_2:
		अगर (((radeon_get_ib_value(p, idx) >> 4) & 0x3) != 3) अणु
			DRM_ERROR("PRIM_WALK must be 3 for IMMD draw\n");
			वापस -EINVAL;
		पूर्ण
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		track->immd_dwords = pkt->count;
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
		/* triggers drawing using in-packet vertex data */
	हाल PACKET3_3D_DRAW_VBUF_2:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
		/* triggers drawing of vertex buffers setup अन्यथाwhere */
	हाल PACKET3_3D_DRAW_INDX_2:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
		/* triggers drawing using indices to vertex buffer */
	हाल PACKET3_3D_DRAW_VBUF:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
		/* triggers drawing of vertex buffers setup अन्यथाwhere */
	हाल PACKET3_3D_DRAW_INDX:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r)
			वापस r;
		अवरोध;
		/* triggers drawing using indices to vertex buffer */
	हाल PACKET3_3D_CLEAR_HIZ:
	हाल PACKET3_3D_CLEAR_ZMASK:
		अगर (p->rdev->hyperz_filp != p->filp)
			वापस -EINVAL;
		अवरोध;
	हाल PACKET3_NOP:
		अवरोध;
	शेष:
		DRM_ERROR("Packet3 opcode %x not supported\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r100_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_packet pkt;
	काष्ठा r100_cs_track *track;
	पूर्णांक r;

	track = kzalloc(माप(*track), GFP_KERNEL);
	अगर (!track)
		वापस -ENOMEM;
	r100_cs_track_clear(p->rdev, track);
	p->track = track;
	करो अणु
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		अगर (r) अणु
			वापस r;
		पूर्ण
		p->idx += pkt.count + 2;
		चयन (pkt.type) अणु
		हाल RADEON_PACKET_TYPE0:
			अगर (p->rdev->family >= CHIP_R200)
				r = r100_cs_parse_packet0(p, &pkt,
					p->rdev->config.r100.reg_safe_bm,
					p->rdev->config.r100.reg_safe_bm_size,
					&r200_packet0_check);
			अन्यथा
				r = r100_cs_parse_packet0(p, &pkt,
					p->rdev->config.r100.reg_safe_bm,
					p->rdev->config.r100.reg_safe_bm_size,
					&r100_packet0_check);
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			अवरोध;
		हाल RADEON_PACKET_TYPE3:
			r = r100_packet3_check(p, &pkt);
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d !\n",
				  pkt.type);
			वापस -EINVAL;
		पूर्ण
		अगर (r)
			वापस r;
	पूर्ण जबतक (p->idx < p->chunk_ib->length_dw);
	वापस 0;
पूर्ण

अटल व्योम r100_cs_track_texture_prपूर्णांक(काष्ठा r100_cs_track_texture *t)
अणु
	DRM_ERROR("pitch                      %d\n", t->pitch);
	DRM_ERROR("use_pitch                  %d\n", t->use_pitch);
	DRM_ERROR("width                      %d\n", t->width);
	DRM_ERROR("width_11                   %d\n", t->width_11);
	DRM_ERROR("height                     %d\n", t->height);
	DRM_ERROR("height_11                  %d\n", t->height_11);
	DRM_ERROR("num levels                 %d\n", t->num_levels);
	DRM_ERROR("depth                      %d\n", t->txdepth);
	DRM_ERROR("bpp                        %d\n", t->cpp);
	DRM_ERROR("coordinate type            %d\n", t->tex_coord_type);
	DRM_ERROR("width round to power of 2  %d\n", t->roundup_w);
	DRM_ERROR("height round to power of 2 %d\n", t->roundup_h);
	DRM_ERROR("compress format            %d\n", t->compress_क्रमmat);
पूर्ण

अटल पूर्णांक r100_track_compress_size(पूर्णांक compress_क्रमmat, पूर्णांक w, पूर्णांक h)
अणु
	पूर्णांक block_width, block_height, block_bytes;
	पूर्णांक wblocks, hblocks;
	पूर्णांक min_wblocks;
	पूर्णांक sz;

	block_width = 4;
	block_height = 4;

	चयन (compress_क्रमmat) अणु
	हाल R100_TRACK_COMP_DXT1:
		block_bytes = 8;
		min_wblocks = 4;
		अवरोध;
	शेष:
	हाल R100_TRACK_COMP_DXT35:
		block_bytes = 16;
		min_wblocks = 2;
		अवरोध;
	पूर्ण

	hblocks = (h + block_height - 1) / block_height;
	wblocks = (w + block_width - 1) / block_width;
	अगर (wblocks < min_wblocks)
		wblocks = min_wblocks;
	sz = wblocks * hblocks * block_bytes;
	वापस sz;
पूर्ण

अटल पूर्णांक r100_cs_track_cube(काष्ठा radeon_device *rdev,
			      काष्ठा r100_cs_track *track, अचिन्हित idx)
अणु
	अचिन्हित face, w, h;
	काष्ठा radeon_bo *cube_robj;
	अचिन्हित दीर्घ size;
	अचिन्हित compress_क्रमmat = track->textures[idx].compress_क्रमmat;

	क्रम (face = 0; face < 5; face++) अणु
		cube_robj = track->textures[idx].cube_info[face].robj;
		w = track->textures[idx].cube_info[face].width;
		h = track->textures[idx].cube_info[face].height;

		अगर (compress_क्रमmat) अणु
			size = r100_track_compress_size(compress_क्रमmat, w, h);
		पूर्ण अन्यथा
			size = w * h;
		size *= track->textures[idx].cpp;

		size += track->textures[idx].cube_info[face].offset;

		अगर (size > radeon_bo_size(cube_robj)) अणु
			DRM_ERROR("Cube texture offset greater than object size %lu %lu\n",
				  size, radeon_bo_size(cube_robj));
			r100_cs_track_texture_prपूर्णांक(&track->textures[idx]);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r100_cs_track_texture_check(काष्ठा radeon_device *rdev,
				       काष्ठा r100_cs_track *track)
अणु
	काष्ठा radeon_bo *robj;
	अचिन्हित दीर्घ size;
	अचिन्हित u, i, w, h, d;
	पूर्णांक ret;

	क्रम (u = 0; u < track->num_texture; u++) अणु
		अगर (!track->textures[u].enabled)
			जारी;
		अगर (track->textures[u].lookup_disable)
			जारी;
		robj = track->textures[u].robj;
		अगर (robj == शून्य) अणु
			DRM_ERROR("No texture bound to unit %u\n", u);
			वापस -EINVAL;
		पूर्ण
		size = 0;
		क्रम (i = 0; i <= track->textures[u].num_levels; i++) अणु
			अगर (track->textures[u].use_pitch) अणु
				अगर (rdev->family < CHIP_R300)
					w = (track->textures[u].pitch / track->textures[u].cpp) / (1 << i);
				अन्यथा
					w = track->textures[u].pitch / (1 << i);
			पूर्ण अन्यथा अणु
				w = track->textures[u].width;
				अगर (rdev->family >= CHIP_RV515)
					w |= track->textures[u].width_11;
				w = w / (1 << i);
				अगर (track->textures[u].roundup_w)
					w = roundup_घात_of_two(w);
			पूर्ण
			h = track->textures[u].height;
			अगर (rdev->family >= CHIP_RV515)
				h |= track->textures[u].height_11;
			h = h / (1 << i);
			अगर (track->textures[u].roundup_h)
				h = roundup_घात_of_two(h);
			अगर (track->textures[u].tex_coord_type == 1) अणु
				d = (1 << track->textures[u].txdepth) / (1 << i);
				अगर (!d)
					d = 1;
			पूर्ण अन्यथा अणु
				d = 1;
			पूर्ण
			अगर (track->textures[u].compress_क्रमmat) अणु

				size += r100_track_compress_size(track->textures[u].compress_क्रमmat, w, h) * d;
				/* compressed textures are block based */
			पूर्ण अन्यथा
				size += w * h * d;
		पूर्ण
		size *= track->textures[u].cpp;

		चयन (track->textures[u].tex_coord_type) अणु
		हाल 0:
		हाल 1:
			अवरोध;
		हाल 2:
			अगर (track->separate_cube) अणु
				ret = r100_cs_track_cube(rdev, track, u);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा
				size *= 6;
			अवरोध;
		शेष:
			DRM_ERROR("Invalid texture coordinate type %u for unit "
				  "%u\n", track->textures[u].tex_coord_type, u);
			वापस -EINVAL;
		पूर्ण
		अगर (size > radeon_bo_size(robj)) अणु
			DRM_ERROR("Texture of unit %u needs %lu bytes but is "
				  "%lu\n", u, size, radeon_bo_size(robj));
			r100_cs_track_texture_prपूर्णांक(&track->textures[u]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r100_cs_track_check(काष्ठा radeon_device *rdev, काष्ठा r100_cs_track *track)
अणु
	अचिन्हित i;
	अचिन्हित दीर्घ size;
	अचिन्हित prim_walk;
	अचिन्हित nverts;
	अचिन्हित num_cb = track->cb_dirty ? track->num_cb : 0;

	अगर (num_cb && !track->zb_cb_clear && !track->color_channel_mask &&
	    !track->blend_पढ़ो_enable)
		num_cb = 0;

	क्रम (i = 0; i < num_cb; i++) अणु
		अगर (track->cb[i].robj == शून्य) अणु
			DRM_ERROR("[drm] No buffer for color buffer %d !\n", i);
			वापस -EINVAL;
		पूर्ण
		size = track->cb[i].pitch * track->cb[i].cpp * track->maxy;
		size += track->cb[i].offset;
		अगर (size > radeon_bo_size(track->cb[i].robj)) अणु
			DRM_ERROR("[drm] Buffer too small for color buffer %d "
				  "(need %lu have %lu) !\n", i, size,
				  radeon_bo_size(track->cb[i].robj));
			DRM_ERROR("[drm] color buffer %d (%u %u %u %u)\n",
				  i, track->cb[i].pitch, track->cb[i].cpp,
				  track->cb[i].offset, track->maxy);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	track->cb_dirty = false;

	अगर (track->zb_dirty && track->z_enabled) अणु
		अगर (track->zb.robj == शून्य) अणु
			DRM_ERROR("[drm] No buffer for z buffer !\n");
			वापस -EINVAL;
		पूर्ण
		size = track->zb.pitch * track->zb.cpp * track->maxy;
		size += track->zb.offset;
		अगर (size > radeon_bo_size(track->zb.robj)) अणु
			DRM_ERROR("[drm] Buffer too small for z buffer "
				  "(need %lu have %lu) !\n", size,
				  radeon_bo_size(track->zb.robj));
			DRM_ERROR("[drm] zbuffer (%u %u %u %u)\n",
				  track->zb.pitch, track->zb.cpp,
				  track->zb.offset, track->maxy);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	track->zb_dirty = false;

	अगर (track->aa_dirty && track->aaresolve) अणु
		अगर (track->aa.robj == शून्य) अणु
			DRM_ERROR("[drm] No buffer for AA resolve buffer %d !\n", i);
			वापस -EINVAL;
		पूर्ण
		/* I believe the क्रमmat comes from colorbuffer0. */
		size = track->aa.pitch * track->cb[0].cpp * track->maxy;
		size += track->aa.offset;
		अगर (size > radeon_bo_size(track->aa.robj)) अणु
			DRM_ERROR("[drm] Buffer too small for AA resolve buffer %d "
				  "(need %lu have %lu) !\n", i, size,
				  radeon_bo_size(track->aa.robj));
			DRM_ERROR("[drm] AA resolve buffer %d (%u %u %u %u)\n",
				  i, track->aa.pitch, track->cb[0].cpp,
				  track->aa.offset, track->maxy);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	track->aa_dirty = false;

	prim_walk = (track->vap_vf_cntl >> 4) & 0x3;
	अगर (track->vap_vf_cntl & (1 << 14)) अणु
		nverts = track->vap_alt_nverts;
	पूर्ण अन्यथा अणु
		nverts = (track->vap_vf_cntl >> 16) & 0xFFFF;
	पूर्ण
	चयन (prim_walk) अणु
	हाल 1:
		क्रम (i = 0; i < track->num_arrays; i++) अणु
			size = track->arrays[i].esize * track->max_indx * 4;
			अगर (track->arrays[i].robj == शून्य) अणु
				DRM_ERROR("(PW %u) Vertex array %u no buffer "
					  "bound\n", prim_walk, i);
				वापस -EINVAL;
			पूर्ण
			अगर (size > radeon_bo_size(track->arrays[i].robj)) अणु
				dev_err(rdev->dev, "(PW %u) Vertex array %u "
					"need %lu dwords have %lu dwords\n",
					prim_walk, i, size >> 2,
					radeon_bo_size(track->arrays[i].robj)
					>> 2);
				DRM_ERROR("Max indices %u\n", track->max_indx);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 2:
		क्रम (i = 0; i < track->num_arrays; i++) अणु
			size = track->arrays[i].esize * (nverts - 1) * 4;
			अगर (track->arrays[i].robj == शून्य) अणु
				DRM_ERROR("(PW %u) Vertex array %u no buffer "
					  "bound\n", prim_walk, i);
				वापस -EINVAL;
			पूर्ण
			अगर (size > radeon_bo_size(track->arrays[i].robj)) अणु
				dev_err(rdev->dev, "(PW %u) Vertex array %u "
					"need %lu dwords have %lu dwords\n",
					prim_walk, i, size >> 2,
					radeon_bo_size(track->arrays[i].robj)
					>> 2);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 3:
		size = track->vtx_size * nverts;
		अगर (size != track->immd_dwords) अणु
			DRM_ERROR("IMMD draw %u dwors but needs %lu dwords\n",
				  track->immd_dwords, size);
			DRM_ERROR("VAP_VF_CNTL.NUM_VERTICES %u, VTX_SIZE %u\n",
				  nverts, track->vtx_size);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("[drm] Invalid primitive walk %d for VAP_VF_CNTL\n",
			  prim_walk);
		वापस -EINVAL;
	पूर्ण

	अगर (track->tex_dirty) अणु
		track->tex_dirty = false;
		वापस r100_cs_track_texture_check(rdev, track);
	पूर्ण
	वापस 0;
पूर्ण

व्योम r100_cs_track_clear(काष्ठा radeon_device *rdev, काष्ठा r100_cs_track *track)
अणु
	अचिन्हित i, face;

	track->cb_dirty = true;
	track->zb_dirty = true;
	track->tex_dirty = true;
	track->aa_dirty = true;

	अगर (rdev->family < CHIP_R300) अणु
		track->num_cb = 1;
		अगर (rdev->family <= CHIP_RS200)
			track->num_texture = 3;
		अन्यथा
			track->num_texture = 6;
		track->maxy = 2048;
		track->separate_cube = true;
	पूर्ण अन्यथा अणु
		track->num_cb = 4;
		track->num_texture = 16;
		track->maxy = 4096;
		track->separate_cube = false;
		track->aaresolve = false;
		track->aa.robj = शून्य;
	पूर्ण

	क्रम (i = 0; i < track->num_cb; i++) अणु
		track->cb[i].robj = शून्य;
		track->cb[i].pitch = 8192;
		track->cb[i].cpp = 16;
		track->cb[i].offset = 0;
	पूर्ण
	track->z_enabled = true;
	track->zb.robj = शून्य;
	track->zb.pitch = 8192;
	track->zb.cpp = 4;
	track->zb.offset = 0;
	track->vtx_size = 0x7F;
	track->immd_dwords = 0xFFFFFFFFUL;
	track->num_arrays = 11;
	track->max_indx = 0x00FFFFFFUL;
	क्रम (i = 0; i < track->num_arrays; i++) अणु
		track->arrays[i].robj = शून्य;
		track->arrays[i].esize = 0x7F;
	पूर्ण
	क्रम (i = 0; i < track->num_texture; i++) अणु
		track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
		track->textures[i].pitch = 16536;
		track->textures[i].width = 16536;
		track->textures[i].height = 16536;
		track->textures[i].width_11 = 1 << 11;
		track->textures[i].height_11 = 1 << 11;
		track->textures[i].num_levels = 12;
		अगर (rdev->family <= CHIP_RS200) अणु
			track->textures[i].tex_coord_type = 0;
			track->textures[i].txdepth = 0;
		पूर्ण अन्यथा अणु
			track->textures[i].txdepth = 16;
			track->textures[i].tex_coord_type = 1;
		पूर्ण
		track->textures[i].cpp = 64;
		track->textures[i].robj = शून्य;
		/* CS IB emission code makes sure texture unit are disabled */
		track->textures[i].enabled = false;
		track->textures[i].lookup_disable = false;
		track->textures[i].roundup_w = true;
		track->textures[i].roundup_h = true;
		अगर (track->separate_cube)
			क्रम (face = 0; face < 5; face++) अणु
				track->textures[i].cube_info[face].robj = शून्य;
				track->textures[i].cube_info[face].width = 16536;
				track->textures[i].cube_info[face].height = 16536;
				track->textures[i].cube_info[face].offset = 0;
			पूर्ण
	पूर्ण
पूर्ण

/*
 * Global GPU functions
 */
अटल व्योम r100_errata(काष्ठा radeon_device *rdev)
अणु
	rdev->pll_errata = 0;

	अगर (rdev->family == CHIP_RV200 || rdev->family == CHIP_RS200) अणु
		rdev->pll_errata |= CHIP_ERRATA_PLL_DUMMYREADS;
	पूर्ण

	अगर (rdev->family == CHIP_RV100 ||
	    rdev->family == CHIP_RS100 ||
	    rdev->family == CHIP_RS200) अणु
		rdev->pll_errata |= CHIP_ERRATA_PLL_DELAY;
	पूर्ण
पूर्ण

अटल पूर्णांक r100_rbbm_fअगरo_रुको_क्रम_entry(काष्ठा radeon_device *rdev, अचिन्हित n)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(RADEON_RBBM_STATUS) & RADEON_RBBM_FIFOCNT_MASK;
		अगर (पंचांगp >= n) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक r100_gui_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	अगर (r100_rbbm_fअगरo_रुको_क्रम_entry(rdev, 64)) अणु
		pr_warn("radeon: wait for empty RBBM fifo failed! Bad things might happen.\n");
	पूर्ण
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(RADEON_RBBM_STATUS);
		अगर (!(पंचांगp & RADEON_RBBM_ACTIVE)) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक r100_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(RADEON_MC_STATUS);
		अगर (पंचांगp & RADEON_MC_IDLE) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

bool r100_gpu_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 rbbm_status;

	rbbm_status = RREG32(R_000E40_RBBM_STATUS);
	अगर (!G_000E40_GUI_ACTIVE(rbbm_status)) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

/* required on r1xx, r2xx, r300, r(v)350, r420/r481, rs400/rs480 */
व्योम r100_enable_bm(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;
	/* Enable bus mastering */
	पंचांगp = RREG32(RADEON_BUS_CNTL) & ~RADEON_BUS_MASTER_DIS;
	WREG32(RADEON_BUS_CNTL, पंचांगp);
पूर्ण

व्योम r100_bm_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	/* disable bus mastering */
	पंचांगp = RREG32(R_000030_BUS_CNTL);
	WREG32(R_000030_BUS_CNTL, (पंचांगp & 0xFFFFFFFF) | 0x00000044);
	mdelay(1);
	WREG32(R_000030_BUS_CNTL, (पंचांगp & 0xFFFFFFFF) | 0x00000042);
	mdelay(1);
	WREG32(R_000030_BUS_CNTL, (पंचांगp & 0xFFFFFFFF) | 0x00000040);
	पंचांगp = RREG32(RADEON_BUS_CNTL);
	mdelay(1);
	pci_clear_master(rdev->pdev);
	mdelay(1);
पूर्ण

पूर्णांक r100_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	काष्ठा r100_mc_save save;
	u32 status, पंचांगp;
	पूर्णांक ret = 0;

	status = RREG32(R_000E40_RBBM_STATUS);
	अगर (!G_000E40_GUI_ACTIVE(status)) अणु
		वापस 0;
	पूर्ण
	r100_mc_stop(rdev, &save);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* stop CP */
	WREG32(RADEON_CP_CSQ_CNTL, 0);
	पंचांगp = RREG32(RADEON_CP_RB_CNTL);
	WREG32(RADEON_CP_RB_CNTL, पंचांगp | RADEON_RB_RPTR_WR_ENA);
	WREG32(RADEON_CP_RB_RPTR_WR, 0);
	WREG32(RADEON_CP_RB_WPTR, 0);
	WREG32(RADEON_CP_RB_CNTL, पंचांगp);
	/* save PCI state */
	pci_save_state(rdev->pdev);
	/* disable bus mastering */
	r100_bm_disable(rdev);
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_SE(1) |
					S_0000F0_SOFT_RESET_RE(1) |
					S_0000F0_SOFT_RESET_PP(1) |
					S_0000F0_SOFT_RESET_RB(1));
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
	/* restore PCI & busmastering */
	pci_restore_state(rdev->pdev);
	r100_enable_bm(rdev);
	/* Check अगर GPU is idle */
	अगर (G_000E40_SE_BUSY(status) || G_000E40_RE_BUSY(status) ||
		G_000E40_TAM_BUSY(status) || G_000E40_PB_BUSY(status)) अणु
		dev_err(rdev->dev, "failed to reset GPU\n");
		ret = -1;
	पूर्ण अन्यथा
		dev_info(rdev->dev, "GPU reset succeed\n");
	r100_mc_resume(rdev, &save);
	वापस ret;
पूर्ण

व्योम r100_set_common_regs(काष्ठा radeon_device *rdev)
अणु
	bool क्रमce_dac2 = false;
	u32 पंचांगp;

	/* set these so they करोn't पूर्णांकerfere with anything */
	WREG32(RADEON_OV0_SCALE_CNTL, 0);
	WREG32(RADEON_SUBPIC_CNTL, 0);
	WREG32(RADEON_VIPH_CONTROL, 0);
	WREG32(RADEON_I2C_CNTL_1, 0);
	WREG32(RADEON_DVI_I2C_CNTL_1, 0);
	WREG32(RADEON_CAP0_TRIG_CNTL, 0);
	WREG32(RADEON_CAP1_TRIG_CNTL, 0);

	/* always set up dac2 on rn50 and some rv100 as lots
	 * of servers seem to wire it up to a VGA port but
	 * करोn't report it in the bios connector
	 * table.
	 */
	चयन (rdev->pdev->device) अणु
		/* RN50 */
	हाल 0x515e:
	हाल 0x5969:
		क्रमce_dac2 = true;
		अवरोध;
		/* RV100*/
	हाल 0x5159:
	हाल 0x515a:
		/* DELL triple head servers */
		अगर ((rdev->pdev->subप्रणाली_venकरोr == 0x1028 /* DELL */) &&
		    ((rdev->pdev->subप्रणाली_device == 0x016c) ||
		     (rdev->pdev->subप्रणाली_device == 0x016d) ||
		     (rdev->pdev->subप्रणाली_device == 0x016e) ||
		     (rdev->pdev->subप्रणाली_device == 0x016f) ||
		     (rdev->pdev->subप्रणाली_device == 0x0170) ||
		     (rdev->pdev->subप्रणाली_device == 0x017d) ||
		     (rdev->pdev->subप्रणाली_device == 0x017e) ||
		     (rdev->pdev->subप्रणाली_device == 0x0183) ||
		     (rdev->pdev->subप्रणाली_device == 0x018a) ||
		     (rdev->pdev->subप्रणाली_device == 0x019a)))
			क्रमce_dac2 = true;
		अवरोध;
	पूर्ण

	अगर (क्रमce_dac2) अणु
		u32 disp_hw_debug = RREG32(RADEON_DISP_HW_DEBUG);
		u32 tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
		u32 dac2_cntl = RREG32(RADEON_DAC_CNTL2);

		/* For CRT on DAC2, करोn't turn it on if BIOS didn't
		   enable it, even it's detected.
		*/

		/* क्रमce it to crtc0 */
		dac2_cntl &= ~RADEON_DAC2_DAC_CLK_SEL;
		dac2_cntl |= RADEON_DAC2_DAC2_CLK_SEL;
		disp_hw_debug |= RADEON_CRT2_DISP1_SEL;

		/* set up the TV DAC */
		tv_dac_cntl &= ~(RADEON_TV_DAC_PEDESTAL |
				 RADEON_TV_DAC_STD_MASK |
				 RADEON_TV_DAC_RDACPD |
				 RADEON_TV_DAC_GDACPD |
				 RADEON_TV_DAC_BDACPD |
				 RADEON_TV_DAC_BGADJ_MASK |
				 RADEON_TV_DAC_DACADJ_MASK);
		tv_dac_cntl |= (RADEON_TV_DAC_NBLANK |
				RADEON_TV_DAC_NHOLD |
				RADEON_TV_DAC_STD_PS2 |
				(0x58 << 16));

		WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
		WREG32(RADEON_DISP_HW_DEBUG, disp_hw_debug);
		WREG32(RADEON_DAC_CNTL2, dac2_cntl);
	पूर्ण

	/* चयन PM block to ACPI mode */
	पंचांगp = RREG32_PLL(RADEON_PLL_PWRMGT_CNTL);
	पंचांगp &= ~RADEON_PM_MODE_SEL;
	WREG32_PLL(RADEON_PLL_PWRMGT_CNTL, पंचांगp);

पूर्ण

/*
 * VRAM info
 */
अटल व्योम r100_vram_get_type(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	rdev->mc.vram_is_ddr = false;
	अगर (rdev->flags & RADEON_IS_IGP)
		rdev->mc.vram_is_ddr = true;
	अन्यथा अगर (RREG32(RADEON_MEM_SDRAM_MODE_REG) & RADEON_MEM_CFG_TYPE_DDR)
		rdev->mc.vram_is_ddr = true;
	अगर ((rdev->family == CHIP_RV100) ||
	    (rdev->family == CHIP_RS100) ||
	    (rdev->family == CHIP_RS200)) अणु
		पंचांगp = RREG32(RADEON_MEM_CNTL);
		अगर (पंचांगp & RV100_HALF_MODE) अणु
			rdev->mc.vram_width = 32;
		पूर्ण अन्यथा अणु
			rdev->mc.vram_width = 64;
		पूर्ण
		अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
			rdev->mc.vram_width /= 4;
			rdev->mc.vram_is_ddr = true;
		पूर्ण
	पूर्ण अन्यथा अगर (rdev->family <= CHIP_RV280) अणु
		पंचांगp = RREG32(RADEON_MEM_CNTL);
		अगर (पंचांगp & RADEON_MEM_NUM_CHANNELS_MASK) अणु
			rdev->mc.vram_width = 128;
		पूर्ण अन्यथा अणु
			rdev->mc.vram_width = 64;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* newer IGPs */
		rdev->mc.vram_width = 128;
	पूर्ण
पूर्ण

अटल u32 r100_get_accessible_vram(काष्ठा radeon_device *rdev)
अणु
	u32 aper_size;
	u8 byte;

	aper_size = RREG32(RADEON_CONFIG_APER_SIZE);

	/* Set HDP_APER_CNTL only on cards that are known not to be broken,
	 * that is has the 2nd generation multअगरunction PCI पूर्णांकerface
	 */
	अगर (rdev->family == CHIP_RV280 ||
	    rdev->family >= CHIP_RV350) अणु
		WREG32_P(RADEON_HOST_PATH_CNTL, RADEON_HDP_APER_CNTL,
		       ~RADEON_HDP_APER_CNTL);
		DRM_INFO("Generation 2 PCI interface, using max accessible memory\n");
		वापस aper_size * 2;
	पूर्ण

	/* Older cards have all sorts of funny issues to deal with. First
	 * check अगर it's a multअगरunction card by पढ़ोing the PCI config
	 * header type... Limit those to one aperture size
	 */
	pci_पढ़ो_config_byte(rdev->pdev, 0xe, &byte);
	अगर (byte & 0x80) अणु
		DRM_INFO("Generation 1 PCI interface in multifunction mode\n");
		DRM_INFO("Limiting VRAM to one aperture\n");
		वापस aper_size;
	पूर्ण

	/* Single function older card. We पढ़ो HDP_APER_CNTL to see how the BIOS
	 * have set it up. We करोn't write this as it's broken on some ASICs but
	 * we expect the BIOS to have करोne the right thing (might be too optimistic...)
	 */
	अगर (RREG32(RADEON_HOST_PATH_CNTL) & RADEON_HDP_APER_CNTL)
		वापस aper_size * 2;
	वापस aper_size;
पूर्ण

व्योम r100_vram_init_sizes(काष्ठा radeon_device *rdev)
अणु
	u64 config_aper_size;

	/* work out accessible VRAM */
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	rdev->mc.visible_vram_size = r100_get_accessible_vram(rdev);
	/* FIXME we करोn't use the second aperture yet when we could use it */
	अगर (rdev->mc.visible_vram_size > rdev->mc.aper_size)
		rdev->mc.visible_vram_size = rdev->mc.aper_size;
	config_aper_size = RREG32(RADEON_CONFIG_APER_SIZE);
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		uपूर्णांक32_t tom;
		/* पढ़ो NB_TOM to get the amount of ram stolen क्रम the GPU */
		tom = RREG32(RADEON_NB_TOM);
		rdev->mc.real_vram_size = (((tom >> 16) - (tom & 0xffff) + 1) << 16);
		WREG32(RADEON_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
		rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	पूर्ण अन्यथा अणु
		rdev->mc.real_vram_size = RREG32(RADEON_CONFIG_MEMSIZE);
		/* Some production boards of m6 will report 0
		 * अगर it's 8 MB
		 */
		अगर (rdev->mc.real_vram_size == 0) अणु
			rdev->mc.real_vram_size = 8192 * 1024;
			WREG32(RADEON_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
		पूर्ण
		/* Fix क्रम RN50, M6, M7 with 8/16/32(??) MBs of VRAM -
		 * Novell bug 204882 + aदीर्घ with lots of ubuntu ones
		 */
		अगर (rdev->mc.aper_size > config_aper_size)
			config_aper_size = rdev->mc.aper_size;

		अगर (config_aper_size > rdev->mc.real_vram_size)
			rdev->mc.mc_vram_size = config_aper_size;
		अन्यथा
			rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	पूर्ण
पूर्ण

व्योम r100_vga_set_state(काष्ठा radeon_device *rdev, bool state)
अणु
	uपूर्णांक32_t temp;

	temp = RREG32(RADEON_CONFIG_CNTL);
	अगर (!state) अणु
		temp &= ~RADEON_CFG_VGA_RAM_EN;
		temp |= RADEON_CFG_VGA_IO_DIS;
	पूर्ण अन्यथा अणु
		temp &= ~RADEON_CFG_VGA_IO_DIS;
	पूर्ण
	WREG32(RADEON_CONFIG_CNTL, temp);
पूर्ण

अटल व्योम r100_mc_init(काष्ठा radeon_device *rdev)
अणु
	u64 base;

	r100_vram_get_type(rdev);
	r100_vram_init_sizes(rdev);
	base = rdev->mc.aper_base;
	अगर (rdev->flags & RADEON_IS_IGP)
		base = (RREG32(RADEON_NB_TOM) & 0xffff) << 16;
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = 0;
	अगर (!(rdev->flags & RADEON_IS_AGP))
		radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण


/*
 * Indirect रेजिस्टरs accessor
 */
व्योम r100_pll_errata_after_index(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pll_errata & CHIP_ERRATA_PLL_DUMMYREADS) अणु
		(व्योम)RREG32(RADEON_CLOCK_CNTL_DATA);
		(व्योम)RREG32(RADEON_CRTC_GEN_CNTL);
	पूर्ण
पूर्ण

अटल व्योम r100_pll_errata_after_data(काष्ठा radeon_device *rdev)
अणु
	/* This workarounds is necessary on RV100, RS100 and RS200 chips
	 * or the chip could hang on a subsequent access
	 */
	अगर (rdev->pll_errata & CHIP_ERRATA_PLL_DELAY) अणु
		mdelay(5);
	पूर्ण

	/* This function is required to workaround a hardware bug in some (all?)
	 * revisions of the R300.  This workaround should be called after every
	 * CLOCK_CNTL_INDEX रेजिस्टर access.  If not, रेजिस्टर पढ़ोs afterward
	 * may not be correct.
	 */
	अगर (rdev->pll_errata & CHIP_ERRATA_R300_CG) अणु
		uपूर्णांक32_t save, पंचांगp;

		save = RREG32(RADEON_CLOCK_CNTL_INDEX);
		पंचांगp = save & ~(0x3f | RADEON_PLL_WR_EN);
		WREG32(RADEON_CLOCK_CNTL_INDEX, पंचांगp);
		पंचांगp = RREG32(RADEON_CLOCK_CNTL_DATA);
		WREG32(RADEON_CLOCK_CNTL_INDEX, save);
	पूर्ण
पूर्ण

uपूर्णांक32_t r100_pll_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t data;

	spin_lock_irqsave(&rdev->pll_idx_lock, flags);
	WREG8(RADEON_CLOCK_CNTL_INDEX, reg & 0x3f);
	r100_pll_errata_after_index(rdev);
	data = RREG32(RADEON_CLOCK_CNTL_DATA);
	r100_pll_errata_after_data(rdev);
	spin_unlock_irqrestore(&rdev->pll_idx_lock, flags);
	वापस data;
पूर्ण

व्योम r100_pll_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->pll_idx_lock, flags);
	WREG8(RADEON_CLOCK_CNTL_INDEX, ((reg & 0x3f) | RADEON_PLL_WR_EN));
	r100_pll_errata_after_index(rdev);
	WREG32(RADEON_CLOCK_CNTL_DATA, v);
	r100_pll_errata_after_data(rdev);
	spin_unlock_irqrestore(&rdev->pll_idx_lock, flags);
पूर्ण

अटल व्योम r100_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	अगर (ASIC_IS_RN50(rdev)) अणु
		rdev->config.r100.reg_safe_bm = rn50_reg_safe_bm;
		rdev->config.r100.reg_safe_bm_size = ARRAY_SIZE(rn50_reg_safe_bm);
	पूर्ण अन्यथा अगर (rdev->family < CHIP_R200) अणु
		rdev->config.r100.reg_safe_bm = r100_reg_safe_bm;
		rdev->config.r100.reg_safe_bm_size = ARRAY_SIZE(r100_reg_safe_bm);
	पूर्ण अन्यथा अणु
		r200_set_safe_रेजिस्टरs(rdev);
	पूर्ण
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक r100_debugfs_rbbm_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t reg, value;
	अचिन्हित i;

	seq_म_लिखो(m, "RBBM_STATUS 0x%08x\n", RREG32(RADEON_RBBM_STATUS));
	seq_म_लिखो(m, "RBBM_CMDFIFO_STAT 0x%08x\n", RREG32(0xE7C));
	seq_म_लिखो(m, "CP_STAT 0x%08x\n", RREG32(RADEON_CP_STAT));
	क्रम (i = 0; i < 64; i++) अणु
		WREG32(RADEON_RBBM_CMDFIFO_ADDR, i | 0x100);
		reg = (RREG32(RADEON_RBBM_CMDFIFO_DATA) - 1) >> 2;
		WREG32(RADEON_RBBM_CMDFIFO_ADDR, i);
		value = RREG32(RADEON_RBBM_CMDFIFO_DATA);
		seq_म_लिखो(m, "[0x%03X] 0x%04X=0x%08X\n", i, reg, value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r100_debugfs_cp_ring_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	uपूर्णांक32_t rdp, wdp;
	अचिन्हित count, i, j;

	radeon_ring_मुक्त_size(rdev, ring);
	rdp = RREG32(RADEON_CP_RB_RPTR);
	wdp = RREG32(RADEON_CP_RB_WPTR);
	count = (rdp + ring->ring_size - wdp) & ring->ptr_mask;
	seq_म_लिखो(m, "CP_STAT 0x%08x\n", RREG32(RADEON_CP_STAT));
	seq_म_लिखो(m, "CP_RB_WPTR 0x%08x\n", wdp);
	seq_म_लिखो(m, "CP_RB_RPTR 0x%08x\n", rdp);
	seq_म_लिखो(m, "%u free dwords in ring\n", ring->ring_मुक्त_dw);
	seq_म_लिखो(m, "%u dwords in ring\n", count);
	अगर (ring->पढ़ोy) अणु
		क्रम (j = 0; j <= count; j++) अणु
			i = (rdp + j) & ring->ptr_mask;
			seq_म_लिखो(m, "r[%04d]=0x%08x\n", i, ring->ring[i]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक r100_debugfs_cp_csq_fअगरo_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t csq_stat, csq2_stat, पंचांगp;
	अचिन्हित r_rptr, r_wptr, ib1_rptr, ib1_wptr, ib2_rptr, ib2_wptr;
	अचिन्हित i;

	seq_म_लिखो(m, "CP_STAT 0x%08x\n", RREG32(RADEON_CP_STAT));
	seq_म_लिखो(m, "CP_CSQ_MODE 0x%08x\n", RREG32(RADEON_CP_CSQ_MODE));
	csq_stat = RREG32(RADEON_CP_CSQ_STAT);
	csq2_stat = RREG32(RADEON_CP_CSQ2_STAT);
	r_rptr = (csq_stat >> 0) & 0x3ff;
	r_wptr = (csq_stat >> 10) & 0x3ff;
	ib1_rptr = (csq_stat >> 20) & 0x3ff;
	ib1_wptr = (csq2_stat >> 0) & 0x3ff;
	ib2_rptr = (csq2_stat >> 10) & 0x3ff;
	ib2_wptr = (csq2_stat >> 20) & 0x3ff;
	seq_म_लिखो(m, "CP_CSQ_STAT 0x%08x\n", csq_stat);
	seq_म_लिखो(m, "CP_CSQ2_STAT 0x%08x\n", csq2_stat);
	seq_म_लिखो(m, "Ring rptr %u\n", r_rptr);
	seq_म_लिखो(m, "Ring wptr %u\n", r_wptr);
	seq_म_लिखो(m, "Indirect1 rptr %u\n", ib1_rptr);
	seq_म_लिखो(m, "Indirect1 wptr %u\n", ib1_wptr);
	seq_म_लिखो(m, "Indirect2 rptr %u\n", ib2_rptr);
	seq_म_लिखो(m, "Indirect2 wptr %u\n", ib2_wptr);
	/* FIXME: 0, 128, 640 depends on fअगरo setup see cp_init_kms
	 * 128 = indirect1_start * 8 & 640 = indirect2_start * 8 */
	seq_म_लिखो(m, "Ring fifo:\n");
	क्रम (i = 0; i < 256; i++) अणु
		WREG32(RADEON_CP_CSQ_ADDR, i << 2);
		पंचांगp = RREG32(RADEON_CP_CSQ_DATA);
		seq_म_लिखो(m, "rfifo[%04d]=0x%08X\n", i, पंचांगp);
	पूर्ण
	seq_म_लिखो(m, "Indirect1 fifo:\n");
	क्रम (i = 256; i <= 512; i++) अणु
		WREG32(RADEON_CP_CSQ_ADDR, i << 2);
		पंचांगp = RREG32(RADEON_CP_CSQ_DATA);
		seq_म_लिखो(m, "ib1fifo[%04d]=0x%08X\n", i, पंचांगp);
	पूर्ण
	seq_म_लिखो(m, "Indirect2 fifo:\n");
	क्रम (i = 640; i < ib1_wptr; i++) अणु
		WREG32(RADEON_CP_CSQ_ADDR, i << 2);
		पंचांगp = RREG32(RADEON_CP_CSQ_DATA);
		seq_म_लिखो(m, "ib2fifo[%04d]=0x%08X\n", i, पंचांगp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r100_debugfs_mc_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32(RADEON_CONFIG_MEMSIZE);
	seq_म_लिखो(m, "CONFIG_MEMSIZE 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_MC_FB_LOCATION);
	seq_म_लिखो(m, "MC_FB_LOCATION 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_BUS_CNTL);
	seq_म_लिखो(m, "BUS_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_MC_AGP_LOCATION);
	seq_म_लिखो(m, "MC_AGP_LOCATION 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_AGP_BASE);
	seq_म_लिखो(m, "AGP_BASE 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_HOST_PATH_CNTL);
	seq_म_लिखो(m, "HOST_PATH_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(0x01D0);
	seq_म_लिखो(m, "AIC_CTRL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_AIC_LO_ADDR);
	seq_म_लिखो(m, "AIC_LO_ADDR 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_AIC_HI_ADDR);
	seq_म_लिखो(m, "AIC_HI_ADDR 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(0x01E4);
	seq_म_लिखो(m, "AIC_TLB_ADDR 0x%08x\n", पंचांगp);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(r100_debugfs_rbbm_info);
DEFINE_SHOW_ATTRIBUTE(r100_debugfs_cp_ring_info);
DEFINE_SHOW_ATTRIBUTE(r100_debugfs_cp_csq_fअगरo);
DEFINE_SHOW_ATTRIBUTE(r100_debugfs_mc_info);

#पूर्ण_अगर

व्योम  r100_debugfs_rbbm_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("r100_rbbm_info", 0444, root, rdev,
			    &r100_debugfs_rbbm_info_fops);
#पूर्ण_अगर
पूर्ण

व्योम r100_debugfs_cp_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("r100_cp_ring_info", 0444, root, rdev,
			    &r100_debugfs_cp_ring_info_fops);
	debugfs_create_file("r100_cp_csq_fifo", 0444, root, rdev,
			    &r100_debugfs_cp_csq_fअगरo_fops);
#पूर्ण_अगर
पूर्ण

व्योम  r100_debugfs_mc_info_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("r100_mc_info", 0444, root, rdev,
			    &r100_debugfs_mc_info_fops);
#पूर्ण_अगर
पूर्ण

पूर्णांक r100_set_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg,
			 uपूर्णांक32_t tiling_flags, uपूर्णांक32_t pitch,
			 uपूर्णांक32_t offset, uपूर्णांक32_t obj_size)
अणु
	पूर्णांक surf_index = reg * 16;
	पूर्णांक flags = 0;

	अगर (rdev->family <= CHIP_RS200) अणु
		अगर ((tiling_flags & (RADEON_TILING_MACRO|RADEON_TILING_MICRO))
				 == (RADEON_TILING_MACRO|RADEON_TILING_MICRO))
			flags |= RADEON_SURF_TILE_COLOR_BOTH;
		अगर (tiling_flags & RADEON_TILING_MACRO)
			flags |= RADEON_SURF_TILE_COLOR_MACRO;
		/* setting pitch to 0 disables tiling */
		अगर ((tiling_flags & (RADEON_TILING_MACRO|RADEON_TILING_MICRO))
				== 0)
			pitch = 0;
	पूर्ण अन्यथा अगर (rdev->family <= CHIP_RV280) अणु
		अगर (tiling_flags & (RADEON_TILING_MACRO))
			flags |= R200_SURF_TILE_COLOR_MACRO;
		अगर (tiling_flags & RADEON_TILING_MICRO)
			flags |= R200_SURF_TILE_COLOR_MICRO;
	पूर्ण अन्यथा अणु
		अगर (tiling_flags & RADEON_TILING_MACRO)
			flags |= R300_SURF_TILE_MACRO;
		अगर (tiling_flags & RADEON_TILING_MICRO)
			flags |= R300_SURF_TILE_MICRO;
	पूर्ण

	अगर (tiling_flags & RADEON_TILING_SWAP_16BIT)
		flags |= RADEON_SURF_AP0_SWP_16BPP | RADEON_SURF_AP1_SWP_16BPP;
	अगर (tiling_flags & RADEON_TILING_SWAP_32BIT)
		flags |= RADEON_SURF_AP0_SWP_32BPP | RADEON_SURF_AP1_SWP_32BPP;

	/* r100/r200 भागide by 16 */
	अगर (rdev->family < CHIP_R300)
		flags |= pitch / 16;
	अन्यथा
		flags |= pitch / 8;


	DRM_DEBUG_KMS("writing surface %d %d %x %x\n", reg, flags, offset, offset+obj_size-1);
	WREG32(RADEON_SURFACE0_INFO + surf_index, flags);
	WREG32(RADEON_SURFACE0_LOWER_BOUND + surf_index, offset);
	WREG32(RADEON_SURFACE0_UPPER_BOUND + surf_index, offset + obj_size - 1);
	वापस 0;
पूर्ण

व्योम r100_clear_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg)
अणु
	पूर्णांक surf_index = reg * 16;
	WREG32(RADEON_SURFACE0_INFO + surf_index, 0);
पूर्ण

व्योम r100_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	fixed20_12 trcd_ff, trp_ff, tras_ff, trbs_ff, tcas_ff;
	fixed20_12 sclk_ff, mclk_ff, sclk_eff_ff, sclk_delay_ff;
	fixed20_12 peak_disp_bw, mem_bw, pix_clk, pix_clk2, temp_ff;
	fixed20_12 crit_poपूर्णांक_ff = अणु0पूर्ण;
	uपूर्णांक32_t temp, data, mem_trcd, mem_trp, mem_tras;
	fixed20_12 memtcas_ff[8] = अणु
		dfixed_init(1),
		dfixed_init(2),
		dfixed_init(3),
		dfixed_init(0),
		dfixed_init_half(1),
		dfixed_init_half(2),
		dfixed_init(0),
	पूर्ण;
	fixed20_12 memtcas_rs480_ff[8] = अणु
		dfixed_init(0),
		dfixed_init(1),
		dfixed_init(2),
		dfixed_init(3),
		dfixed_init(0),
		dfixed_init_half(1),
		dfixed_init_half(2),
		dfixed_init_half(3),
	पूर्ण;
	fixed20_12 memtcas2_ff[8] = अणु
		dfixed_init(0),
		dfixed_init(1),
		dfixed_init(2),
		dfixed_init(3),
		dfixed_init(4),
		dfixed_init(5),
		dfixed_init(6),
		dfixed_init(7),
	पूर्ण;
	fixed20_12 memtrbs[8] = अणु
		dfixed_init(1),
		dfixed_init_half(1),
		dfixed_init(2),
		dfixed_init_half(2),
		dfixed_init(3),
		dfixed_init_half(3),
		dfixed_init(4),
		dfixed_init_half(4)
	पूर्ण;
	fixed20_12 memtrbs_r4xx[8] = अणु
		dfixed_init(4),
		dfixed_init(5),
		dfixed_init(6),
		dfixed_init(7),
		dfixed_init(8),
		dfixed_init(9),
		dfixed_init(10),
		dfixed_init(11)
	पूर्ण;
	fixed20_12 min_mem_eff;
	fixed20_12 mc_latency_sclk, mc_latency_mclk, k1;
	fixed20_12 cur_latency_mclk, cur_latency_sclk;
	fixed20_12 disp_latency, disp_latency_overhead, disp_drain_rate = अणु0पूर्ण,
		disp_drain_rate2, पढ़ो_वापस_rate;
	fixed20_12 समय_disp1_drop_priority;
	पूर्णांक c;
	पूर्णांक cur_size = 16;       /* in octawords */
	पूर्णांक critical_poपूर्णांक = 0, critical_poपूर्णांक2;
/* 	uपूर्णांक32_t पढ़ो_वापस_rate, समय_disp1_drop_priority; */
	पूर्णांक stop_req, max_stop_req;
	काष्ठा drm_display_mode *mode1 = शून्य;
	काष्ठा drm_display_mode *mode2 = शून्य;
	uपूर्णांक32_t pixel_bytes1 = 0;
	uपूर्णांक32_t pixel_bytes2 = 0;

	/* Guess line buffer size to be 8192 pixels */
	u32 lb_size = 8192;

	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	radeon_update_display_priority(rdev);

	अगर (rdev->mode_info.crtcs[0]->base.enabled) अणु
		स्थिर काष्ठा drm_framebuffer *fb =
			rdev->mode_info.crtcs[0]->base.primary->fb;

		mode1 = &rdev->mode_info.crtcs[0]->base.mode;
		pixel_bytes1 = fb->क्रमmat->cpp[0];
	पूर्ण
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		अगर (rdev->mode_info.crtcs[1]->base.enabled) अणु
			स्थिर काष्ठा drm_framebuffer *fb =
				rdev->mode_info.crtcs[1]->base.primary->fb;

			mode2 = &rdev->mode_info.crtcs[1]->base.mode;
			pixel_bytes2 = fb->क्रमmat->cpp[0];
		पूर्ण
	पूर्ण

	min_mem_eff.full = dfixed_स्थिर_8(0);
	/* get modes */
	अगर ((rdev->disp_priority == 2) && ASIC_IS_R300(rdev)) अणु
		uपूर्णांक32_t mc_init_misc_lat_समयr = RREG32(R300_MC_INIT_MISC_LAT_TIMER);
		mc_init_misc_lat_समयr &= ~(R300_MC_DISP1R_INIT_LAT_MASK << R300_MC_DISP1R_INIT_LAT_SHIFT);
		mc_init_misc_lat_समयr &= ~(R300_MC_DISP0R_INIT_LAT_MASK << R300_MC_DISP0R_INIT_LAT_SHIFT);
		/* check crtc enables */
		अगर (mode2)
			mc_init_misc_lat_समयr |= (1 << R300_MC_DISP1R_INIT_LAT_SHIFT);
		अगर (mode1)
			mc_init_misc_lat_समयr |= (1 << R300_MC_DISP0R_INIT_LAT_SHIFT);
		WREG32(R300_MC_INIT_MISC_LAT_TIMER, mc_init_misc_lat_समयr);
	पूर्ण

	/*
	 * determine is there is enough bw क्रम current mode
	 */
	sclk_ff = rdev->pm.sclk;
	mclk_ff = rdev->pm.mclk;

	temp = (rdev->mc.vram_width / 8) * (rdev->mc.vram_is_ddr ? 2 : 1);
	temp_ff.full = dfixed_स्थिर(temp);
	mem_bw.full = dfixed_mul(mclk_ff, temp_ff);

	pix_clk.full = 0;
	pix_clk2.full = 0;
	peak_disp_bw.full = 0;
	अगर (mode1) अणु
		temp_ff.full = dfixed_स्थिर(1000);
		pix_clk.full = dfixed_स्थिर(mode1->घड़ी); /* convert to fixed poपूर्णांक */
		pix_clk.full = dfixed_भाग(pix_clk, temp_ff);
		temp_ff.full = dfixed_स्थिर(pixel_bytes1);
		peak_disp_bw.full += dfixed_mul(pix_clk, temp_ff);
	पूर्ण
	अगर (mode2) अणु
		temp_ff.full = dfixed_स्थिर(1000);
		pix_clk2.full = dfixed_स्थिर(mode2->घड़ी); /* convert to fixed poपूर्णांक */
		pix_clk2.full = dfixed_भाग(pix_clk2, temp_ff);
		temp_ff.full = dfixed_स्थिर(pixel_bytes2);
		peak_disp_bw.full += dfixed_mul(pix_clk2, temp_ff);
	पूर्ण

	mem_bw.full = dfixed_mul(mem_bw, min_mem_eff);
	अगर (peak_disp_bw.full >= mem_bw.full) अणु
		DRM_ERROR("You may not have enough display bandwidth for current mode\n"
			  "If you have flickering problem, try to lower resolution, refresh rate, or color depth\n");
	पूर्ण

	/*  Get values from the EXT_MEM_CNTL रेजिस्टर...converting its contents. */
	temp = RREG32(RADEON_MEM_TIMING_CNTL);
	अगर ((rdev->family == CHIP_RV100) || (rdev->flags & RADEON_IS_IGP)) अणु /* RV100, M6, IGPs */
		mem_trcd = ((temp >> 2) & 0x3) + 1;
		mem_trp  = ((temp & 0x3)) + 1;
		mem_tras = ((temp & 0x70) >> 4) + 1;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_R300 ||
		   rdev->family == CHIP_R350) अणु /* r300, r350 */
		mem_trcd = (temp & 0x7) + 1;
		mem_trp = ((temp >> 8) & 0x7) + 1;
		mem_tras = ((temp >> 11) & 0xf) + 4;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_RV350 ||
		   rdev->family == CHIP_RV380) अणु
		/* rv3x0 */
		mem_trcd = (temp & 0x7) + 3;
		mem_trp = ((temp >> 8) & 0x7) + 3;
		mem_tras = ((temp >> 11) & 0xf) + 6;
	पूर्ण अन्यथा अगर (rdev->family == CHIP_R420 ||
		   rdev->family == CHIP_R423 ||
		   rdev->family == CHIP_RV410) अणु
		/* r4xx */
		mem_trcd = (temp & 0xf) + 3;
		अगर (mem_trcd > 15)
			mem_trcd = 15;
		mem_trp = ((temp >> 8) & 0xf) + 3;
		अगर (mem_trp > 15)
			mem_trp = 15;
		mem_tras = ((temp >> 12) & 0x1f) + 6;
		अगर (mem_tras > 31)
			mem_tras = 31;
	पूर्ण अन्यथा अणु /* RV200, R200 */
		mem_trcd = (temp & 0x7) + 1;
		mem_trp = ((temp >> 8) & 0x7) + 1;
		mem_tras = ((temp >> 12) & 0xf) + 4;
	पूर्ण
	/* convert to FF */
	trcd_ff.full = dfixed_स्थिर(mem_trcd);
	trp_ff.full = dfixed_स्थिर(mem_trp);
	tras_ff.full = dfixed_स्थिर(mem_tras);

	/* Get values from the MEM_SDRAM_MODE_REG रेजिस्टर...converting its */
	temp = RREG32(RADEON_MEM_SDRAM_MODE_REG);
	data = (temp & (7 << 20)) >> 20;
	अगर ((rdev->family == CHIP_RV100) || rdev->flags & RADEON_IS_IGP) अणु
		अगर (rdev->family == CHIP_RS480) /* करोn't think rs400 */
			tcas_ff = memtcas_rs480_ff[data];
		अन्यथा
			tcas_ff = memtcas_ff[data];
	पूर्ण अन्यथा
		tcas_ff = memtcas2_ff[data];

	अगर (rdev->family == CHIP_RS400 ||
	    rdev->family == CHIP_RS480) अणु
		/* extra cas latency stored in bits 23-25 0-4 घड़ीs */
		data = (temp >> 23) & 0x7;
		अगर (data < 5)
			tcas_ff.full += dfixed_स्थिर(data);
	पूर्ण

	अगर (ASIC_IS_R300(rdev) && !(rdev->flags & RADEON_IS_IGP)) अणु
		/* on the R300, Tcas is included in Trbs.
		 */
		temp = RREG32(RADEON_MEM_CNTL);
		data = (R300_MEM_NUM_CHANNELS_MASK & temp);
		अगर (data == 1) अणु
			अगर (R300_MEM_USE_CD_CH_ONLY & temp) अणु
				temp = RREG32(R300_MC_IND_INDEX);
				temp &= ~R300_MC_IND_ADDR_MASK;
				temp |= R300_MC_READ_CNTL_CD_mcind;
				WREG32(R300_MC_IND_INDEX, temp);
				temp = RREG32(R300_MC_IND_DATA);
				data = (R300_MEM_RBS_POSITION_C_MASK & temp);
			पूर्ण अन्यथा अणु
				temp = RREG32(R300_MC_READ_CNTL_AB);
				data = (R300_MEM_RBS_POSITION_A_MASK & temp);
			पूर्ण
		पूर्ण अन्यथा अणु
			temp = RREG32(R300_MC_READ_CNTL_AB);
			data = (R300_MEM_RBS_POSITION_A_MASK & temp);
		पूर्ण
		अगर (rdev->family == CHIP_RV410 ||
		    rdev->family == CHIP_R420 ||
		    rdev->family == CHIP_R423)
			trbs_ff = memtrbs_r4xx[data];
		अन्यथा
			trbs_ff = memtrbs[data];
		tcas_ff.full += trbs_ff.full;
	पूर्ण

	sclk_eff_ff.full = sclk_ff.full;

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		fixed20_12 agpmode_ff;
		agpmode_ff.full = dfixed_स्थिर(radeon_agpmode);
		temp_ff.full = dfixed_स्थिर_666(16);
		sclk_eff_ff.full -= dfixed_mul(agpmode_ff, temp_ff);
	पूर्ण
	/* TODO PCIE lanes may affect this - agpmode == 16?? */

	अगर (ASIC_IS_R300(rdev)) अणु
		sclk_delay_ff.full = dfixed_स्थिर(250);
	पूर्ण अन्यथा अणु
		अगर ((rdev->family == CHIP_RV100) ||
		    rdev->flags & RADEON_IS_IGP) अणु
			अगर (rdev->mc.vram_is_ddr)
				sclk_delay_ff.full = dfixed_स्थिर(41);
			अन्यथा
				sclk_delay_ff.full = dfixed_स्थिर(33);
		पूर्ण अन्यथा अणु
			अगर (rdev->mc.vram_width == 128)
				sclk_delay_ff.full = dfixed_स्थिर(57);
			अन्यथा
				sclk_delay_ff.full = dfixed_स्थिर(41);
		पूर्ण
	पूर्ण

	mc_latency_sclk.full = dfixed_भाग(sclk_delay_ff, sclk_eff_ff);

	अगर (rdev->mc.vram_is_ddr) अणु
		अगर (rdev->mc.vram_width == 32) अणु
			k1.full = dfixed_स्थिर(40);
			c  = 3;
		पूर्ण अन्यथा अणु
			k1.full = dfixed_स्थिर(20);
			c  = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		k1.full = dfixed_स्थिर(40);
		c  = 3;
	पूर्ण

	temp_ff.full = dfixed_स्थिर(2);
	mc_latency_mclk.full = dfixed_mul(trcd_ff, temp_ff);
	temp_ff.full = dfixed_स्थिर(c);
	mc_latency_mclk.full += dfixed_mul(tcas_ff, temp_ff);
	temp_ff.full = dfixed_स्थिर(4);
	mc_latency_mclk.full += dfixed_mul(tras_ff, temp_ff);
	mc_latency_mclk.full += dfixed_mul(trp_ff, temp_ff);
	mc_latency_mclk.full += k1.full;

	mc_latency_mclk.full = dfixed_भाग(mc_latency_mclk, mclk_ff);
	mc_latency_mclk.full += dfixed_भाग(temp_ff, sclk_eff_ff);

	/*
	  HW cursor समय assuming worst हाल of full size colour cursor.
	*/
	temp_ff.full = dfixed_स्थिर((2 * (cur_size - (rdev->mc.vram_is_ddr + 1))));
	temp_ff.full += trcd_ff.full;
	अगर (temp_ff.full < tras_ff.full)
		temp_ff.full = tras_ff.full;
	cur_latency_mclk.full = dfixed_भाग(temp_ff, mclk_ff);

	temp_ff.full = dfixed_स्थिर(cur_size);
	cur_latency_sclk.full = dfixed_भाग(temp_ff, sclk_eff_ff);
	/*
	  Find the total latency क्रम the display data.
	*/
	disp_latency_overhead.full = dfixed_स्थिर(8);
	disp_latency_overhead.full = dfixed_भाग(disp_latency_overhead, sclk_ff);
	mc_latency_mclk.full += disp_latency_overhead.full + cur_latency_mclk.full;
	mc_latency_sclk.full += disp_latency_overhead.full + cur_latency_sclk.full;

	अगर (mc_latency_mclk.full > mc_latency_sclk.full)
		disp_latency.full = mc_latency_mclk.full;
	अन्यथा
		disp_latency.full = mc_latency_sclk.full;

	/* setup Max GRPH_STOP_REQ शेष value */
	अगर (ASIC_IS_RV100(rdev))
		max_stop_req = 0x5c;
	अन्यथा
		max_stop_req = 0x7c;

	अगर (mode1) अणु
		/*  CRTC1
		    Set GRPH_BUFFER_CNTL रेजिस्टर using h/w defined optimal values.
		    GRPH_STOP_REQ <= MIN[ 0x7C, (CRTC_H_DISP + 1) * (bit depth) / 0x10 ]
		*/
		stop_req = mode1->hdisplay * pixel_bytes1 / 16;

		अगर (stop_req > max_stop_req)
			stop_req = max_stop_req;

		/*
		  Find the drain rate of the display buffer.
		*/
		temp_ff.full = dfixed_स्थिर((16/pixel_bytes1));
		disp_drain_rate.full = dfixed_भाग(pix_clk, temp_ff);

		/*
		  Find the critical poपूर्णांक of the display buffer.
		*/
		crit_poपूर्णांक_ff.full = dfixed_mul(disp_drain_rate, disp_latency);
		crit_poपूर्णांक_ff.full += dfixed_स्थिर_half(0);

		critical_poपूर्णांक = dfixed_trunc(crit_poपूर्णांक_ff);

		अगर (rdev->disp_priority == 2) अणु
			critical_poपूर्णांक = 0;
		पूर्ण

		/*
		  The critical poपूर्णांक should never be above max_stop_req-4.  Setting
		  GRPH_CRITICAL_CNTL = 0 will thus क्रमce high priority all the समय.
		*/
		अगर (max_stop_req - critical_poपूर्णांक < 4)
			critical_poपूर्णांक = 0;

		अगर (critical_poपूर्णांक == 0 && mode2 && rdev->family == CHIP_R300) अणु
			/* some R300 cards have problem with this set to 0, when CRTC2 is enabled.*/
			critical_poपूर्णांक = 0x10;
		पूर्ण

		temp = RREG32(RADEON_GRPH_BUFFER_CNTL);
		temp &= ~(RADEON_GRPH_STOP_REQ_MASK);
		temp |= (stop_req << RADEON_GRPH_STOP_REQ_SHIFT);
		temp &= ~(RADEON_GRPH_START_REQ_MASK);
		अगर ((rdev->family == CHIP_R350) &&
		    (stop_req > 0x15)) अणु
			stop_req -= 0x10;
		पूर्ण
		temp |= (stop_req << RADEON_GRPH_START_REQ_SHIFT);
		temp |= RADEON_GRPH_BUFFER_SIZE;
		temp &= ~(RADEON_GRPH_CRITICAL_CNTL   |
			  RADEON_GRPH_CRITICAL_AT_SOF |
			  RADEON_GRPH_STOP_CNTL);
		/*
		  Write the result पूर्णांकo the रेजिस्टर.
		*/
		WREG32(RADEON_GRPH_BUFFER_CNTL, ((temp & ~RADEON_GRPH_CRITICAL_POINT_MASK) |
						       (critical_poपूर्णांक << RADEON_GRPH_CRITICAL_POINT_SHIFT)));

#अगर 0
		अगर ((rdev->family == CHIP_RS400) ||
		    (rdev->family == CHIP_RS480)) अणु
			/* attempt to program RS400 disp regs correctly ??? */
			temp = RREG32(RS400_DISP1_REG_CNTL);
			temp &= ~(RS400_DISP1_START_REQ_LEVEL_MASK |
				  RS400_DISP1_STOP_REQ_LEVEL_MASK);
			WREG32(RS400_DISP1_REQ_CNTL1, (temp |
						       (critical_poपूर्णांक << RS400_DISP1_START_REQ_LEVEL_SHIFT) |
						       (critical_poपूर्णांक << RS400_DISP1_STOP_REQ_LEVEL_SHIFT)));
			temp = RREG32(RS400_DMIF_MEM_CNTL1);
			temp &= ~(RS400_DISP1_CRITICAL_POINT_START_MASK |
				  RS400_DISP1_CRITICAL_POINT_STOP_MASK);
			WREG32(RS400_DMIF_MEM_CNTL1, (temp |
						      (critical_poपूर्णांक << RS400_DISP1_CRITICAL_POINT_START_SHIFT) |
						      (critical_poपूर्णांक << RS400_DISP1_CRITICAL_POINT_STOP_SHIFT)));
		पूर्ण
#पूर्ण_अगर

		DRM_DEBUG_KMS("GRPH_BUFFER_CNTL from to %x\n",
			  /* 	  (अचिन्हित पूर्णांक)info->SavedReg->grph_buffer_cntl, */
			  (अचिन्हित पूर्णांक)RREG32(RADEON_GRPH_BUFFER_CNTL));
	पूर्ण

	अगर (mode2) अणु
		u32 grph2_cntl;
		stop_req = mode2->hdisplay * pixel_bytes2 / 16;

		अगर (stop_req > max_stop_req)
			stop_req = max_stop_req;

		/*
		  Find the drain rate of the display buffer.
		*/
		temp_ff.full = dfixed_स्थिर((16/pixel_bytes2));
		disp_drain_rate2.full = dfixed_भाग(pix_clk2, temp_ff);

		grph2_cntl = RREG32(RADEON_GRPH2_BUFFER_CNTL);
		grph2_cntl &= ~(RADEON_GRPH_STOP_REQ_MASK);
		grph2_cntl |= (stop_req << RADEON_GRPH_STOP_REQ_SHIFT);
		grph2_cntl &= ~(RADEON_GRPH_START_REQ_MASK);
		अगर ((rdev->family == CHIP_R350) &&
		    (stop_req > 0x15)) अणु
			stop_req -= 0x10;
		पूर्ण
		grph2_cntl |= (stop_req << RADEON_GRPH_START_REQ_SHIFT);
		grph2_cntl |= RADEON_GRPH_BUFFER_SIZE;
		grph2_cntl &= ~(RADEON_GRPH_CRITICAL_CNTL   |
			  RADEON_GRPH_CRITICAL_AT_SOF |
			  RADEON_GRPH_STOP_CNTL);

		अगर ((rdev->family == CHIP_RS100) ||
		    (rdev->family == CHIP_RS200))
			critical_poपूर्णांक2 = 0;
		अन्यथा अणु
			temp = (rdev->mc.vram_width * rdev->mc.vram_is_ddr + 1)/128;
			temp_ff.full = dfixed_स्थिर(temp);
			temp_ff.full = dfixed_mul(mclk_ff, temp_ff);
			अगर (sclk_ff.full < temp_ff.full)
				temp_ff.full = sclk_ff.full;

			पढ़ो_वापस_rate.full = temp_ff.full;

			अगर (mode1) अणु
				temp_ff.full = पढ़ो_वापस_rate.full - disp_drain_rate.full;
				समय_disp1_drop_priority.full = dfixed_भाग(crit_poपूर्णांक_ff, temp_ff);
			पूर्ण अन्यथा अणु
				समय_disp1_drop_priority.full = 0;
			पूर्ण
			crit_poपूर्णांक_ff.full = disp_latency.full + समय_disp1_drop_priority.full + disp_latency.full;
			crit_poपूर्णांक_ff.full = dfixed_mul(crit_poपूर्णांक_ff, disp_drain_rate2);
			crit_poपूर्णांक_ff.full += dfixed_स्थिर_half(0);

			critical_poपूर्णांक2 = dfixed_trunc(crit_poपूर्णांक_ff);

			अगर (rdev->disp_priority == 2) अणु
				critical_poपूर्णांक2 = 0;
			पूर्ण

			अगर (max_stop_req - critical_poपूर्णांक2 < 4)
				critical_poपूर्णांक2 = 0;

		पूर्ण

		अगर (critical_poपूर्णांक2 == 0 && rdev->family == CHIP_R300) अणु
			/* some R300 cards have problem with this set to 0 */
			critical_poपूर्णांक2 = 0x10;
		पूर्ण

		WREG32(RADEON_GRPH2_BUFFER_CNTL, ((grph2_cntl & ~RADEON_GRPH_CRITICAL_POINT_MASK) |
						  (critical_poपूर्णांक2 << RADEON_GRPH_CRITICAL_POINT_SHIFT)));

		अगर ((rdev->family == CHIP_RS400) ||
		    (rdev->family == CHIP_RS480)) अणु
#अगर 0
			/* attempt to program RS400 disp2 regs correctly ??? */
			temp = RREG32(RS400_DISP2_REQ_CNTL1);
			temp &= ~(RS400_DISP2_START_REQ_LEVEL_MASK |
				  RS400_DISP2_STOP_REQ_LEVEL_MASK);
			WREG32(RS400_DISP2_REQ_CNTL1, (temp |
						       (critical_poपूर्णांक2 << RS400_DISP1_START_REQ_LEVEL_SHIFT) |
						       (critical_poपूर्णांक2 << RS400_DISP1_STOP_REQ_LEVEL_SHIFT)));
			temp = RREG32(RS400_DISP2_REQ_CNTL2);
			temp &= ~(RS400_DISP2_CRITICAL_POINT_START_MASK |
				  RS400_DISP2_CRITICAL_POINT_STOP_MASK);
			WREG32(RS400_DISP2_REQ_CNTL2, (temp |
						       (critical_poपूर्णांक2 << RS400_DISP2_CRITICAL_POINT_START_SHIFT) |
						       (critical_poपूर्णांक2 << RS400_DISP2_CRITICAL_POINT_STOP_SHIFT)));
#पूर्ण_अगर
			WREG32(RS400_DISP2_REQ_CNTL1, 0x105DC1CC);
			WREG32(RS400_DISP2_REQ_CNTL2, 0x2749D000);
			WREG32(RS400_DMIF_MEM_CNTL1,  0x29CA71DC);
			WREG32(RS400_DISP1_REQ_CNTL1, 0x28FBC3AC);
		पूर्ण

		DRM_DEBUG_KMS("GRPH2_BUFFER_CNTL from to %x\n",
			  (अचिन्हित पूर्णांक)RREG32(RADEON_GRPH2_BUFFER_CNTL));
	पूर्ण

	/* Save number of lines the linebuffer leads beक्रमe the scanout */
	अगर (mode1)
	    rdev->mode_info.crtcs[0]->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode1->crtc_hdisplay);

	अगर (mode2)
	    rdev->mode_info.crtcs[1]->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode2->crtc_hdisplay);
पूर्ण

पूर्णांक r100_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
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
	r = radeon_ring_lock(rdev, ring, 2);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring (%d).\n", r);
		radeon_scratch_मुक्त(rdev, scratch);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(scratch, 0));
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(scratch);
		अगर (पंचांगp == 0xDEADBEEF) अणु
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test succeeded in %d usecs\n", i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring test failed (scratch(0x%04X)=0x%08X)\n",
			  scratch, पंचांगp);
		r = -EINVAL;
	पूर्ण
	radeon_scratch_मुक्त(rdev, scratch);
	वापस r;
पूर्ण

व्योम r100_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];

	अगर (ring->rptr_save_reg) अणु
		u32 next_rptr = ring->wptr + 2 + 3;
		radeon_ring_ग_लिखो(ring, PACKET0(ring->rptr_save_reg, 0));
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण

	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_CP_IB_BASE, 1));
	radeon_ring_ग_लिखो(ring, ib->gpu_addr);
	radeon_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

पूर्णांक r100_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
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
	r = radeon_ib_get(rdev, RADEON_RING_TYPE_GFX_INDEX, &ib, शून्य, 256);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		जाओ मुक्त_scratch;
	पूर्ण
	ib.ptr[0] = PACKET0(scratch, 0);
	ib.ptr[1] = 0xDEADBEEF;
	ib.ptr[2] = PACKET2(0);
	ib.ptr[3] = PACKET2(0);
	ib.ptr[4] = PACKET2(0);
	ib.ptr[5] = PACKET2(0);
	ib.ptr[6] = PACKET2(0);
	ib.ptr[7] = PACKET2(0);
	ib.length_dw = 8;
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
		अगर (पंचांगp == 0xDEADBEEF) अणु
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ib test succeeded in %u usecs\n", i);
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

व्योम r100_mc_stop(काष्ठा radeon_device *rdev, काष्ठा r100_mc_save *save)
अणु
	/* Shutकरोwn CP we shouldn't need to करो that but better be safe than
	 * sorry
	 */
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].पढ़ोy = false;
	WREG32(R_000740_CP_CSQ_CNTL, 0);

	/* Save few CRTC रेजिस्टरs */
	save->GENMO_WT = RREG8(R_0003C2_GENMO_WT);
	save->CRTC_EXT_CNTL = RREG32(R_000054_CRTC_EXT_CNTL);
	save->CRTC_GEN_CNTL = RREG32(R_000050_CRTC_GEN_CNTL);
	save->CUR_OFFSET = RREG32(R_000260_CUR_OFFSET);
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		save->CRTC2_GEN_CNTL = RREG32(R_0003F8_CRTC2_GEN_CNTL);
		save->CUR2_OFFSET = RREG32(R_000360_CUR2_OFFSET);
	पूर्ण

	/* Disable VGA aperture access */
	WREG8(R_0003C2_GENMO_WT, C_0003C2_VGA_RAM_EN & save->GENMO_WT);
	/* Disable cursor, overlay, crtc */
	WREG32(R_000260_CUR_OFFSET, save->CUR_OFFSET | S_000260_CUR_LOCK(1));
	WREG32(R_000054_CRTC_EXT_CNTL, save->CRTC_EXT_CNTL |
					S_000054_CRTC_DISPLAY_DIS(1));
	WREG32(R_000050_CRTC_GEN_CNTL,
			(C_000050_CRTC_CUR_EN & save->CRTC_GEN_CNTL) |
			S_000050_CRTC_DISP_REQ_EN_B(1));
	WREG32(R_000420_OV0_SCALE_CNTL,
		C_000420_OV0_OVERLAY_EN & RREG32(R_000420_OV0_SCALE_CNTL));
	WREG32(R_000260_CUR_OFFSET, C_000260_CUR_LOCK & save->CUR_OFFSET);
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		WREG32(R_000360_CUR2_OFFSET, save->CUR2_OFFSET |
						S_000360_CUR2_LOCK(1));
		WREG32(R_0003F8_CRTC2_GEN_CNTL,
			(C_0003F8_CRTC2_CUR_EN & save->CRTC2_GEN_CNTL) |
			S_0003F8_CRTC2_DISPLAY_DIS(1) |
			S_0003F8_CRTC2_DISP_REQ_EN_B(1));
		WREG32(R_000360_CUR2_OFFSET,
			C_000360_CUR2_LOCK & save->CUR2_OFFSET);
	पूर्ण
पूर्ण

व्योम r100_mc_resume(काष्ठा radeon_device *rdev, काष्ठा r100_mc_save *save)
अणु
	/* Update base address क्रम crtc */
	WREG32(R_00023C_DISPLAY_BASE_ADDR, rdev->mc.vram_start);
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		WREG32(R_00033C_CRTC2_DISPLAY_BASE_ADDR, rdev->mc.vram_start);
	पूर्ण
	/* Restore CRTC रेजिस्टरs */
	WREG8(R_0003C2_GENMO_WT, save->GENMO_WT);
	WREG32(R_000054_CRTC_EXT_CNTL, save->CRTC_EXT_CNTL);
	WREG32(R_000050_CRTC_GEN_CNTL, save->CRTC_GEN_CNTL);
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		WREG32(R_0003F8_CRTC2_GEN_CNTL, save->CRTC2_GEN_CNTL);
	पूर्ण
पूर्ण

व्योम r100_vga_render_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG8(R_0003C2_GENMO_WT);
	WREG8(R_0003C2_GENMO_WT, C_0003C2_VGA_RAM_EN & पंचांगp);
पूर्ण

अटल व्योम r100_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा r100_mc_save save;

	/* Stops all mc clients */
	r100_mc_stop(rdev, &save);
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		WREG32(R_00014C_MC_AGP_LOCATION,
			S_00014C_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_00014C_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32(R_000170_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		अगर (rdev->family > CHIP_RV200)
			WREG32(R_00015C_AGP_BASE_2,
				upper_32_bits(rdev->mc.agp_base) & 0xff);
	पूर्ण अन्यथा अणु
		WREG32(R_00014C_MC_AGP_LOCATION, 0x0FFFFFFF);
		WREG32(R_000170_AGP_BASE, 0);
		अगर (rdev->family > CHIP_RV200)
			WREG32(R_00015C_AGP_BASE_2, 0);
	पूर्ण
	/* Wait क्रम mc idle */
	अगर (r100_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "Wait for MC idle timeout.\n");
	/* Program MC, should be a 32bits limited address space */
	WREG32(R_000148_MC_FB_LOCATION,
		S_000148_MC_FB_START(rdev->mc.vram_start >> 16) |
		S_000148_MC_FB_TOP(rdev->mc.vram_end >> 16));
	r100_mc_resume(rdev, &save);
पूर्ण

अटल व्योम r100_घड़ी_startup(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	अगर (radeon_dynclks != -1 && radeon_dynclks)
		radeon_legacy_set_घड़ी_gating(rdev, 1);
	/* We need to क्रमce on some of the block */
	पंचांगp = RREG32_PLL(R_00000D_SCLK_CNTL);
	पंचांगp |= S_00000D_FORCE_CP(1) | S_00000D_FORCE_VIP(1);
	अगर ((rdev->family == CHIP_RV250) || (rdev->family == CHIP_RV280))
		पंचांगp |= S_00000D_FORCE_DISP1(1) | S_00000D_FORCE_DISP2(1);
	WREG32_PLL(R_00000D_SCLK_CNTL, पंचांगp);
पूर्ण

अटल पूर्णांक r100_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* set common regs */
	r100_set_common_regs(rdev);
	/* program mc */
	r100_mc_program(rdev);
	/* Resume घड़ी */
	r100_घड़ी_startup(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	r100_enable_bm(rdev);
	अगर (rdev->flags & RADEON_IS_PCI) अणु
		r = r100_pci_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण

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

	r100_irq_set(rdev);
	rdev->config.r100.hdp_cntl = RREG32(RADEON_HOST_PATH_CNTL);
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

	वापस 0;
पूर्ण

पूर्णांक r100_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	/* Resume घड़ी beक्रमe करोing reset */
	r100_घड़ी_startup(rdev);
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* post */
	radeon_combios_asic_init(rdev->ddev);
	/* Resume घड़ी after posting */
	r100_घड़ी_startup(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = r100_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक r100_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	r100_irq_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम r100_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	r100_cp_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_gem_fini(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_irq_kms_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

/*
 * Due to how kexec works, it can leave the hw fully initialised when it
 * boots the new kernel. However करोing our init sequence with the CP and
 * WB stuff setup causes GPU hangs on the RN50 at least. So at startup
 * करो some quick sanity checks and restore sane values to aव्योम this
 * problem.
 */
व्योम r100_restore_sanity(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(RADEON_CP_CSQ_CNTL);
	अगर (पंचांगp) अणु
		WREG32(RADEON_CP_CSQ_CNTL, 0);
	पूर्ण
	पंचांगp = RREG32(RADEON_CP_RB_CNTL);
	अगर (पंचांगp) अणु
		WREG32(RADEON_CP_RB_CNTL, 0);
	पूर्ण
	पंचांगp = RREG32(RADEON_SCRATCH_UMSK);
	अगर (पंचांगp) अणु
		WREG32(RADEON_SCRATCH_UMSK, 0);
	पूर्ण
पूर्ण

पूर्णांक r100_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Register debugfs file specअगरic to this group of asics */
	r100_debugfs_mc_info_init(rdev);
	/* Disable VGA */
	r100_vga_render_disable(rdev);
	/* Initialize scratch रेजिस्टरs */
	radeon_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* sanity check some रेजिस्टर to aव्योम hangs like after kexec */
	r100_restore_sanity(rdev);
	/* TODO: disable VGA need to use VGA request */
	/* BIOS*/
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	अगर (rdev->is_atom_bios) अणु
		dev_err(rdev->dev, "Expecting combios for RS400/RS480 GPU\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		r = radeon_combios_init(rdev);
		अगर (r)
			वापस r;
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
	/* Set asic errata */
	r100_errata(rdev);
	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* initialize AGP */
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		r = radeon_agp_init(rdev);
		अगर (r) अणु
			radeon_agp_disable(rdev);
		पूर्ण
	पूर्ण
	/* initialize VRAM */
	r100_mc_init(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;
	अगर (rdev->flags & RADEON_IS_PCI) अणु
		r = r100_pci_gart_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	r100_set_safe_रेजिस्टरs(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r100_startup(rdev);
	अगर (r) अणु
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		अगर (rdev->flags & RADEON_IS_PCI)
			r100_pci_gart_fini(rdev);
		rdev->accel_working = false;
	पूर्ण
	वापस 0;
पूर्ण

uपूर्णांक32_t r100_mm_rreg_slow(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t ret;

	spin_lock_irqsave(&rdev->mmio_idx_lock, flags);
	ग_लिखोl(reg, ((व्योम __iomem *)rdev->rmmio) + RADEON_MM_INDEX);
	ret = पढ़ोl(((व्योम __iomem *)rdev->rmmio) + RADEON_MM_DATA);
	spin_unlock_irqrestore(&rdev->mmio_idx_lock, flags);
	वापस ret;
पूर्ण

व्योम r100_mm_wreg_slow(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mmio_idx_lock, flags);
	ग_लिखोl(reg, ((व्योम __iomem *)rdev->rmmio) + RADEON_MM_INDEX);
	ग_लिखोl(v, ((व्योम __iomem *)rdev->rmmio) + RADEON_MM_DATA);
	spin_unlock_irqrestore(&rdev->mmio_idx_lock, flags);
पूर्ण

u32 r100_io_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अगर (reg < rdev->rio_mem_size)
		वापस ioपढ़ो32(rdev->rio_mem + reg);
	अन्यथा अणु
		ioग_लिखो32(reg, rdev->rio_mem + RADEON_MM_INDEX);
		वापस ioपढ़ो32(rdev->rio_mem + RADEON_MM_DATA);
	पूर्ण
पूर्ण

व्योम r100_io_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अगर (reg < rdev->rio_mem_size)
		ioग_लिखो32(v, rdev->rio_mem + reg);
	अन्यथा अणु
		ioग_लिखो32(reg, rdev->rio_mem + RADEON_MM_INDEX);
		ioग_लिखो32(v, rdev->rio_mem + RADEON_MM_DATA);
	पूर्ण
पूर्ण
