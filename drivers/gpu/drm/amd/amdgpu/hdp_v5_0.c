<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
 */
#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "hdp_v5_0.h"

#समावेश "hdp/hdp_5_0_0_offset.h"
#समावेश "hdp/hdp_5_0_0_sh_mask.h"
#समावेश <uapi/linux/kfd_ioctl.h>

अटल व्योम hdp_v5_0_flush_hdp(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg)
		WREG32_NO_KIQ((adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL) >> 2, 0);
	अन्यथा
		amdgpu_ring_emit_wreg(ring, (adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL) >> 2, 0);
पूर्ण

अटल व्योम hdp_v5_0_invalidate_hdp(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32_SOC15_NO_KIQ(HDP, 0, mmHDP_READ_CACHE_INVALIDATE, 1);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, SOC15_REG_OFFSET(
					HDP, 0, mmHDP_READ_CACHE_INVALIDATE), 1);
	पूर्ण
पूर्ण

अटल व्योम hdp_v5_0_update_mem_घातer_gating(काष्ठा amdgpu_device *adev,
					  bool enable)
अणु
	uपूर्णांक32_t hdp_clk_cntl, hdp_clk_cntl1;
	uपूर्णांक32_t hdp_mem_pwr_cntl;

	अगर (!(adev->cg_flags & (AMD_CG_SUPPORT_HDP_LS |
				AMD_CG_SUPPORT_HDP_DS |
				AMD_CG_SUPPORT_HDP_SD)))
		वापस;

	hdp_clk_cntl = hdp_clk_cntl1 = RREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL);
	hdp_mem_pwr_cntl = RREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL);

	/* Beक्रमe करोing घड़ी/घातer mode चयन,
	 * क्रमced on IPH & RC घड़ी */
	hdp_clk_cntl = REG_SET_FIELD(hdp_clk_cntl, HDP_CLK_CNTL,
				     IPH_MEM_CLK_SOFT_OVERRIDE, 1);
	hdp_clk_cntl = REG_SET_FIELD(hdp_clk_cntl, HDP_CLK_CNTL,
				     RC_MEM_CLK_SOFT_OVERRIDE, 1);
	WREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL, hdp_clk_cntl);

	/* HDP 5.0 करोesn't support dynamic घातer mode चयन,
	 * disable घड़ी and घातer gating beक्रमe any changing */
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_CTRL_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_LS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_DS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_SD_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_CTRL_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_LS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_DS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_SD_EN, 0);
	WREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL, hdp_mem_pwr_cntl);

	/* only one घड़ी gating mode (LS/DS/SD) can be enabled */
	अगर (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS) अणु
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_LS_EN, enable);
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_LS_EN, enable);
	पूर्ण अन्यथा अगर (adev->cg_flags & AMD_CG_SUPPORT_HDP_DS) अणु
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_DS_EN, enable);
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_DS_EN, enable);
	पूर्ण अन्यथा अगर (adev->cg_flags & AMD_CG_SUPPORT_HDP_SD) अणु
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_SD_EN, enable);
		/* RC should not use shut करोwn mode, fallback to ds */
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_DS_EN, enable);
	पूर्ण

	/* confirmed that IPH_MEM_POWER_CTRL_EN and RC_MEM_POWER_CTRL_EN have to
	 * be set क्रम SRAM LS/DS/SD */
	अगर (adev->cg_flags & (AMD_CG_SUPPORT_HDP_LS | AMD_CG_SUPPORT_HDP_DS |
			      AMD_CG_SUPPORT_HDP_SD)) अणु
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_CTRL_EN, 1);
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_CTRL_EN, 1);
	पूर्ण

	WREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL, hdp_mem_pwr_cntl);

	/* restore IPH & RC घड़ी override after घड़ी/घातer mode changing */
	WREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL, hdp_clk_cntl1);
पूर्ण

अटल व्योम hdp_v5_0_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						      bool enable)
अणु
	uपूर्णांक32_t hdp_clk_cntl;

	अगर (!(adev->cg_flags & AMD_CG_SUPPORT_HDP_MGCG))
		वापस;

	hdp_clk_cntl = RREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL);

	अगर (enable) अणु
		hdp_clk_cntl &=
			~(uपूर्णांक32_t)
			(HDP_CLK_CNTL__IPH_MEM_CLK_SOFT_OVERRIDE_MASK |
			 HDP_CLK_CNTL__RC_MEM_CLK_SOFT_OVERRIDE_MASK |
			 HDP_CLK_CNTL__DBUS_CLK_SOFT_OVERRIDE_MASK |
			 HDP_CLK_CNTL__DYN_CLK_SOFT_OVERRIDE_MASK |
			 HDP_CLK_CNTL__XDP_REG_CLK_SOFT_OVERRIDE_MASK |
			 HDP_CLK_CNTL__HDP_REG_CLK_SOFT_OVERRIDE_MASK);
	पूर्ण अन्यथा अणु
		hdp_clk_cntl |= HDP_CLK_CNTL__IPH_MEM_CLK_SOFT_OVERRIDE_MASK |
			HDP_CLK_CNTL__RC_MEM_CLK_SOFT_OVERRIDE_MASK |
			HDP_CLK_CNTL__DBUS_CLK_SOFT_OVERRIDE_MASK |
			HDP_CLK_CNTL__DYN_CLK_SOFT_OVERRIDE_MASK |
			HDP_CLK_CNTL__XDP_REG_CLK_SOFT_OVERRIDE_MASK |
			HDP_CLK_CNTL__HDP_REG_CLK_SOFT_OVERRIDE_MASK;
	पूर्ण

	WREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL, hdp_clk_cntl);
पूर्ण

अटल व्योम hdp_v5_0_update_घड़ी_gating(काष्ठा amdgpu_device *adev,
					      bool enable)
अणु
	hdp_v5_0_update_mem_घातer_gating(adev, enable);
	hdp_v5_0_update_medium_grain_घड़ी_gating(adev, enable);
पूर्ण

अटल व्योम hdp_v5_0_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					    u32 *flags)
अणु
	uपूर्णांक32_t पंचांगp;

	/* AMD_CG_SUPPORT_HDP_MGCG */
	पंचांगp = RREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL);
	अगर (!(पंचांगp & (HDP_CLK_CNTL__IPH_MEM_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__RC_MEM_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__DBUS_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__DYN_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__XDP_REG_CLK_SOFT_OVERRIDE_MASK |
		     HDP_CLK_CNTL__HDP_REG_CLK_SOFT_OVERRIDE_MASK)))
		*flags |= AMD_CG_SUPPORT_HDP_MGCG;

	/* AMD_CG_SUPPORT_HDP_LS/DS/SD */
	पंचांगp = RREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL);
	अगर (पंचांगp & HDP_MEM_POWER_CTRL__IPH_MEM_POWER_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_LS;
	अन्यथा अगर (पंचांगp & HDP_MEM_POWER_CTRL__IPH_MEM_POWER_DS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_DS;
	अन्यथा अगर (पंचांगp & HDP_MEM_POWER_CTRL__IPH_MEM_POWER_SD_EN_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_SD;
पूर्ण

अटल व्योम hdp_v5_0_init_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_SOC15(HDP, 0, mmHDP_MISC_CNTL);
	पंचांगp |= HDP_MISC_CNTL__FLUSH_INVALIDATE_CACHE_MASK;
	WREG32_SOC15(HDP, 0, mmHDP_MISC_CNTL, पंचांगp);
पूर्ण

स्थिर काष्ठा amdgpu_hdp_funcs hdp_v5_0_funcs = अणु
	.flush_hdp = hdp_v5_0_flush_hdp,
	.invalidate_hdp = hdp_v5_0_invalidate_hdp,
	.update_घड़ी_gating = hdp_v5_0_update_घड़ी_gating,
	.get_घड़ी_gating_state = hdp_v5_0_get_घड़ीgating_state,
	.init_रेजिस्टरs = hdp_v5_0_init_रेजिस्टरs,
पूर्ण;
