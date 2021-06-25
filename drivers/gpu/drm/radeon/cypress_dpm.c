<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश <linux/pci.h>

#समावेश "atom.h"
#समावेश "cypress_dpm.h"
#समावेश "evergreen.h"
#समावेश "evergreend.h"
#समावेश "r600_dpm.h"
#समावेश "rv770.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"

#घोषणा SMC_RAM_END 0x8000

#घोषणा MC_CG_ARB_FREQ_F0           0x0a
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा MC_CG_ARB_FREQ_F2           0x0c
#घोषणा MC_CG_ARB_FREQ_F3           0x0d

#घोषणा MC_CG_SEQ_DRAMCONF_S0       0x05
#घोषणा MC_CG_SEQ_DRAMCONF_S1       0x06
#घोषणा MC_CG_SEQ_YCLK_SUSPEND      0x04
#घोषणा MC_CG_SEQ_YCLK_RESUME       0x0a

अटल व्योम cypress_enable_bअगर_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
						 bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp, bअगर;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर (enable) अणु
		अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
		    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु
			अगर (!pi->boot_in_gen2) अणु
				bअगर = RREG32(CG_BIF_REQ_AND_RSP) & ~CG_CLIENT_REQ_MASK;
				bअगर |= CG_CLIENT_REQ(0xd);
				WREG32(CG_BIF_REQ_AND_RSP, bअगर);

				पंचांगp &= ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
				पंचांगp |= LC_HW_VOLTAGE_IF_CONTROL(1);
				पंचांगp |= LC_GEN2_EN_STRAP;

				पंचांगp |= LC_CLR_FAILED_SPD_CHANGE_CNT;
				WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
				udelay(10);
				पंचांगp &= ~LC_CLR_FAILED_SPD_CHANGE_CNT;
				WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!pi->boot_in_gen2) अणु
			पंचांगp &= ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
			पंचांगp &= ~LC_GEN2_EN_STRAP;
		पूर्ण
		अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) ||
		    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2))
			WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम cypress_enable_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					     bool enable)
अणु
	cypress_enable_bअगर_dynamic_pcie_gen2(rdev, enable);

	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, ENABLE_GEN2PCIE, ~ENABLE_GEN2PCIE);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~ENABLE_GEN2PCIE);
पूर्ण

#अगर 0
अटल पूर्णांक cypress_enter_ulp_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (pi->gfx_घड़ी_gating) अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);

		RREG32(GB_ADDR_CONFIG);
	पूर्ण

	WREG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_SwitchToMinimumPower),
		 ~HOST_SMC_MSG_MASK);

	udelay(7000);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम cypress_gfx_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
					    bool enable)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (enable) अणु
		अगर (eg_pi->light_sleep) अणु
			WREG32(GRBM_GFX_INDEX, 0xC0000000);

			WREG32_CG(CG_CGLS_TILE_0, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_1, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_2, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_3, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_4, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_5, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_6, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_7, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_8, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_9, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_10, 0xFFFFFFFF);
			WREG32_CG(CG_CGLS_TILE_11, 0xFFFFFFFF);

			WREG32_P(SCLK_PWRMGT_CNTL, DYN_LIGHT_SLEEP_EN, ~DYN_LIGHT_SLEEP_EN);
		पूर्ण
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	पूर्ण अन्यथा अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);
		RREG32(GB_ADDR_CONFIG);

		अगर (eg_pi->light_sleep) अणु
			WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_LIGHT_SLEEP_EN);

			WREG32(GRBM_GFX_INDEX, 0xC0000000);

			WREG32_CG(CG_CGLS_TILE_0, 0);
			WREG32_CG(CG_CGLS_TILE_1, 0);
			WREG32_CG(CG_CGLS_TILE_2, 0);
			WREG32_CG(CG_CGLS_TILE_3, 0);
			WREG32_CG(CG_CGLS_TILE_4, 0);
			WREG32_CG(CG_CGLS_TILE_5, 0);
			WREG32_CG(CG_CGLS_TILE_6, 0);
			WREG32_CG(CG_CGLS_TILE_7, 0);
			WREG32_CG(CG_CGLS_TILE_8, 0);
			WREG32_CG(CG_CGLS_TILE_9, 0);
			WREG32_CG(CG_CGLS_TILE_10, 0);
			WREG32_CG(CG_CGLS_TILE_11, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cypress_mg_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
					   bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (enable) अणु
		u32 cgts_sm_ctrl_reg;

		अगर (rdev->family == CHIP_CEDAR)
			cgts_sm_ctrl_reg = CEDAR_MGCGCGTSSMCTRL_DFLT;
		अन्यथा अगर (rdev->family == CHIP_REDWOOD)
			cgts_sm_ctrl_reg = REDWOOD_MGCGCGTSSMCTRL_DFLT;
		अन्यथा
			cgts_sm_ctrl_reg = CYPRESS_MGCGCGTSSMCTRL_DFLT;

		WREG32(GRBM_GFX_INDEX, 0xC0000000);

		WREG32_CG(CG_CGTT_LOCAL_0, CYPRESS_MGCGTTLOCAL0_DFLT);
		WREG32_CG(CG_CGTT_LOCAL_1, CYPRESS_MGCGTTLOCAL1_DFLT & 0xFFFFCFFF);
		WREG32_CG(CG_CGTT_LOCAL_2, CYPRESS_MGCGTTLOCAL2_DFLT);
		WREG32_CG(CG_CGTT_LOCAL_3, CYPRESS_MGCGTTLOCAL3_DFLT);

		अगर (pi->mgcgtssm)
			WREG32(CGTS_SM_CTRL_REG, cgts_sm_ctrl_reg);

		अगर (eg_pi->mcls) अणु
			WREG32_P(MC_CITF_MISC_RD_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_CITF_MISC_WR_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_CITF_MISC_VM_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_HUB_MISC_HUB_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_HUB_MISC_VM_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_HUB_MISC_SIP_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_XPB_CLK_GAT, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(VM_L2_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(GRBM_GFX_INDEX, 0xC0000000);

		WREG32_CG(CG_CGTT_LOCAL_0, 0xFFFFFFFF);
		WREG32_CG(CG_CGTT_LOCAL_1, 0xFFFFFFFF);
		WREG32_CG(CG_CGTT_LOCAL_2, 0xFFFFFFFF);
		WREG32_CG(CG_CGTT_LOCAL_3, 0xFFFFFFFF);

		अगर (pi->mgcgtssm)
			WREG32(CGTS_SM_CTRL_REG, 0x81f44bc0);
	पूर्ण
पूर्ण

व्योम cypress_enable_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
				    bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (enable) अणु
		अगर (pi->sclk_ss)
			WREG32_P(GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, ~DYN_SPREAD_SPECTRUM_EN);

		अगर (pi->mclk_ss)
			WREG32_P(MPLL_CNTL_MODE, SS_SSEN, ~SS_SSEN);
	पूर्ण अन्यथा अणु
		WREG32_P(CG_SPLL_SPREAD_SPECTRUM, 0, ~SSEN);
		WREG32_P(GENERAL_PWRMGT, 0, ~DYN_SPREAD_SPECTRUM_EN);
		WREG32_P(MPLL_CNTL_MODE, 0, ~SS_SSEN);
		WREG32_P(MPLL_CNTL_MODE, 0, ~SS_DSMODE_EN);
	पूर्ण
पूर्ण

व्योम cypress_start_dpm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(GENERAL_PWRMGT, GLOBAL_PWRMGT_EN, ~GLOBAL_PWRMGT_EN);
पूर्ण

व्योम cypress_enable_sclk_control(काष्ठा radeon_device *rdev,
				 bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~SCLK_PWRMGT_OFF);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, SCLK_PWRMGT_OFF, ~SCLK_PWRMGT_OFF);
पूर्ण

व्योम cypress_enable_mclk_control(काष्ठा radeon_device *rdev,
				 bool enable)
अणु
	अगर (enable)
		WREG32_P(MCLK_PWRMGT_CNTL, 0, ~MPLL_PWRMGT_OFF);
	अन्यथा
		WREG32_P(MCLK_PWRMGT_CNTL, MPLL_PWRMGT_OFF, ~MPLL_PWRMGT_OFF);
पूर्ण

पूर्णांक cypress_notअगरy_smc_display_change(काष्ठा radeon_device *rdev,
				      bool has_display)
अणु
	PPSMC_Msg msg = has_display ?
		(PPSMC_Msg)PPSMC_MSG_HasDisplay : (PPSMC_Msg)PPSMC_MSG_NoDisplay;

	अगर (rv770_send_msg_to_smc(rdev, msg) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम cypress_program_response_बार(काष्ठा radeon_device *rdev)
अणु
	u32 reference_घड़ी;
	u32 mclk_चयन_limit;

	reference_घड़ी = radeon_get_xclk(rdev);
	mclk_चयन_limit = (460 * reference_घड़ी) / 100;

	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_mclk_चयन_lim,
				      mclk_चयन_limit);

	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_mvdd_chg_समय, 1);

	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_mc_block_delay, 0xAA);

	rv770_program_response_बार(rdev);

	अगर (ASIC_IS_LOMBOK(rdev))
		rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
					      RV770_SMC_SOFT_REGISTER_is_asic_lombok, 1);

पूर्ण

अटल पूर्णांक cypress_pcie_perक्रमmance_request(काष्ठा radeon_device *rdev,
					    u8 perf_req, bool advertise)
अणु
#अगर defined(CONFIG_ACPI)
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
#पूर्ण_अगर
	u32 पंचांगp;

	udelay(10);
	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर ((perf_req == PCIE_PERF_REQ_PECI_GEN1) && (पंचांगp & LC_CURRENT_DATA_RATE))
		वापस 0;

#अगर defined(CONFIG_ACPI)
	अगर ((perf_req == PCIE_PERF_REQ_PECI_GEN1) ||
	    (perf_req == PCIE_PERF_REQ_PECI_GEN2)) अणु
		eg_pi->pcie_perक्रमmance_request_रेजिस्टरed = true;
		वापस radeon_acpi_pcie_perक्रमmance_request(rdev, perf_req, advertise);
	पूर्ण अन्यथा अगर ((perf_req == PCIE_PERF_REQ_REMOVE_REGISTRY) &&
		   eg_pi->pcie_perक्रमmance_request_रेजिस्टरed) अणु
		eg_pi->pcie_perक्रमmance_request_रेजिस्टरed = false;
		वापस radeon_acpi_pcie_perक्रमmance_request(rdev, perf_req, advertise);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम cypress_advertise_gen2_capability(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp;

#अगर defined(CONFIG_ACPI)
	radeon_acpi_pcie_notअगरy_device_पढ़ोy(rdev);
#पूर्ण_अगर

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);

	अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2))
		pi->pcie_gen2 = true;
	अन्यथा
		pi->pcie_gen2 = false;

	अगर (!pi->pcie_gen2)
		cypress_pcie_perक्रमmance_request(rdev, PCIE_PERF_REQ_PECI_GEN2, true);

पूर्ण

अटल क्रमागत radeon_pcie_gen cypress_get_maximum_link_speed(काष्ठा radeon_ps *radeon_state)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);

	अगर (state->high.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
		वापस 1;
	वापस 0;
पूर्ण

व्योम cypress_notअगरy_link_speed_change_after_state_change(काष्ठा radeon_device *rdev,
							 काष्ठा radeon_ps *radeon_new_state,
							 काष्ठा radeon_ps *radeon_current_state)
अणु
	क्रमागत radeon_pcie_gen pcie_link_speed_target =
		cypress_get_maximum_link_speed(radeon_new_state);
	क्रमागत radeon_pcie_gen pcie_link_speed_current =
		cypress_get_maximum_link_speed(radeon_current_state);
	u8 request;

	अगर (pcie_link_speed_target < pcie_link_speed_current) अणु
		अगर (pcie_link_speed_target == RADEON_PCIE_GEN1)
			request = PCIE_PERF_REQ_PECI_GEN1;
		अन्यथा अगर (pcie_link_speed_target == RADEON_PCIE_GEN2)
			request = PCIE_PERF_REQ_PECI_GEN2;
		अन्यथा
			request = PCIE_PERF_REQ_PECI_GEN3;

		cypress_pcie_perक्रमmance_request(rdev, request, false);
	पूर्ण
पूर्ण

व्योम cypress_notअगरy_link_speed_change_beक्रमe_state_change(काष्ठा radeon_device *rdev,
							  काष्ठा radeon_ps *radeon_new_state,
							  काष्ठा radeon_ps *radeon_current_state)
अणु
	क्रमागत radeon_pcie_gen pcie_link_speed_target =
		cypress_get_maximum_link_speed(radeon_new_state);
	क्रमागत radeon_pcie_gen pcie_link_speed_current =
		cypress_get_maximum_link_speed(radeon_current_state);
	u8 request;

	अगर (pcie_link_speed_target > pcie_link_speed_current) अणु
		अगर (pcie_link_speed_target == RADEON_PCIE_GEN1)
			request = PCIE_PERF_REQ_PECI_GEN1;
		अन्यथा अगर (pcie_link_speed_target == RADEON_PCIE_GEN2)
			request = PCIE_PERF_REQ_PECI_GEN2;
		अन्यथा
			request = PCIE_PERF_REQ_PECI_GEN3;

		cypress_pcie_perक्रमmance_request(rdev, request, false);
	पूर्ण
पूर्ण

अटल पूर्णांक cypress_populate_voltage_value(काष्ठा radeon_device *rdev,
					  काष्ठा atom_voltage_table *table,
					  u16 value, RV770_SMC_VOLTAGE_VALUE *voltage)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (value <= table->entries[i].value) अणु
			voltage->index = (u8)i;
			voltage->value = cpu_to_be16(table->entries[i].value);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == table->count)
		वापस -EINVAL;

	वापस 0;
पूर्ण

u8 cypress_get_strobe_mode_settings(काष्ठा radeon_device *rdev, u32 mclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u8 result = 0;
	bool strobe_mode = false;

	अगर (pi->mem_gddr5) अणु
		अगर (mclk <= pi->mclk_strobe_mode_threshold)
			strobe_mode = true;
		result = cypress_get_mclk_frequency_ratio(rdev, mclk, strobe_mode);

		अगर (strobe_mode)
			result |= SMC_STROBE_ENABLE;
	पूर्ण

	वापस result;
पूर्ण

u32 cypress_map_clkf_to_ibias(काष्ठा radeon_device *rdev, u32 clkf)
अणु
	u32 ref_clk = rdev->घड़ी.mpll.reference_freq;
	u32 vco = clkf * ref_clk;

	/* 100 Mhz ref clk */
	अगर (ref_clk == 10000) अणु
		अगर (vco > 500000)
			वापस 0xC6;
		अगर (vco > 400000)
			वापस 0x9D;
		अगर (vco > 330000)
			वापस 0x6C;
		अगर (vco > 250000)
			वापस 0x2B;
		अगर (vco >  160000)
			वापस 0x5B;
		अगर (vco > 120000)
			वापस 0x0A;
		वापस 0x4B;
	पूर्ण

	/* 27 Mhz ref clk */
	अगर (vco > 250000)
		वापस 0x8B;
	अगर (vco > 200000)
		वापस 0xCC;
	अगर (vco > 150000)
		वापस 0x9B;
	वापस 0x6B;
पूर्ण

अटल पूर्णांक cypress_populate_mclk_value(काष्ठा radeon_device *rdev,
				       u32 engine_घड़ी, u32 memory_घड़ी,
				       RV7XX_SMC_MCLK_VALUE *mclk,
				       bool strobe_mode, bool dll_state_on)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	u32 mpll_ad_func_cntl =
		pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 =
		pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl =
		pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 =
		pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl =
		pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl =
		pi->clk_regs.rv770.dll_cntl;
	u32 mpll_ss1 = pi->clk_regs.rv770.mpll_ss1;
	u32 mpll_ss2 = pi->clk_regs.rv770.mpll_ss2;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 ibias;
	u32 dll_speed;
	पूर्णांक ret;
	u32 mc_seq_misc7;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     memory_घड़ी, strobe_mode, &भागiders);
	अगर (ret)
		वापस ret;

	अगर (!strobe_mode) अणु
		mc_seq_misc7 = RREG32(MC_SEQ_MISC7);

		अगर(mc_seq_misc7 & 0x8000000)
			भागiders.post_भाग = 1;
	पूर्ण

	ibias = cypress_map_clkf_to_ibias(rdev, भागiders.whole_fb_भाग);

	mpll_ad_func_cntl &= ~(CLKR_MASK |
			       YCLK_POST_DIV_MASK |
			       CLKF_MASK |
			       CLKFRAC_MASK |
			       IBIAS_MASK);
	mpll_ad_func_cntl |= CLKR(भागiders.ref_भाग);
	mpll_ad_func_cntl |= YCLK_POST_DIV(भागiders.post_भाग);
	mpll_ad_func_cntl |= CLKF(भागiders.whole_fb_भाग);
	mpll_ad_func_cntl |= CLKFRAC(भागiders.frac_fb_भाग);
	mpll_ad_func_cntl |= IBIAS(ibias);

	अगर (भागiders.vco_mode)
		mpll_ad_func_cntl_2 |= VCO_MODE;
	अन्यथा
		mpll_ad_func_cntl_2 &= ~VCO_MODE;

	अगर (pi->mem_gddr5) अणु
		mpll_dq_func_cntl &= ~(CLKR_MASK |
				       YCLK_POST_DIV_MASK |
				       CLKF_MASK |
				       CLKFRAC_MASK |
				       IBIAS_MASK);
		mpll_dq_func_cntl |= CLKR(भागiders.ref_भाग);
		mpll_dq_func_cntl |= YCLK_POST_DIV(भागiders.post_भाग);
		mpll_dq_func_cntl |= CLKF(भागiders.whole_fb_भाग);
		mpll_dq_func_cntl |= CLKFRAC(भागiders.frac_fb_भाग);
		mpll_dq_func_cntl |= IBIAS(ibias);

		अगर (strobe_mode)
			mpll_dq_func_cntl &= ~PDNB;
		अन्यथा
			mpll_dq_func_cntl |= PDNB;

		अगर (भागiders.vco_mode)
			mpll_dq_func_cntl_2 |= VCO_MODE;
		अन्यथा
			mpll_dq_func_cntl_2 &= ~VCO_MODE;
	पूर्ण

	अगर (pi->mclk_ss) अणु
		काष्ठा radeon_atom_ss ss;
		u32 vco_freq = memory_घड़ी * भागiders.post_भाग;

		अगर (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_MEMORY_SS, vco_freq)) अणु
			u32 reference_घड़ी = rdev->घड़ी.mpll.reference_freq;
			u32 decoded_ref = rv740_get_decoded_reference_भागider(भागiders.ref_भाग);
			u32 clk_s = reference_घड़ी * 5 / (decoded_ref * ss.rate);
			u32 clk_v = ss.percentage *
				(0x4000 * भागiders.whole_fb_भाग + 0x800 * भागiders.frac_fb_भाग) / (clk_s * 625);

			mpll_ss1 &= ~CLKV_MASK;
			mpll_ss1 |= CLKV(clk_v);

			mpll_ss2 &= ~CLKS_MASK;
			mpll_ss2 |= CLKS(clk_s);
		पूर्ण
	पूर्ण

	dll_speed = rv740_get_dll_speed(pi->mem_gddr5,
					memory_घड़ी);

	mclk_pwrmgt_cntl &= ~DLL_SPEED_MASK;
	mclk_pwrmgt_cntl |= DLL_SPEED(dll_speed);
	अगर (dll_state_on)
		mclk_pwrmgt_cntl |= (MRDCKA0_PDNB |
				     MRDCKA1_PDNB |
				     MRDCKB0_PDNB |
				     MRDCKB1_PDNB |
				     MRDCKC0_PDNB |
				     MRDCKC1_PDNB |
				     MRDCKD0_PDNB |
				     MRDCKD1_PDNB);
	अन्यथा
		mclk_pwrmgt_cntl &= ~(MRDCKA0_PDNB |
				      MRDCKA1_PDNB |
				      MRDCKB0_PDNB |
				      MRDCKB1_PDNB |
				      MRDCKC0_PDNB |
				      MRDCKC1_PDNB |
				      MRDCKD0_PDNB |
				      MRDCKD1_PDNB);

	mclk->mclk770.mclk_value = cpu_to_be32(memory_घड़ी);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);
	mclk->mclk770.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);
	mclk->mclk770.vMPLL_SS = cpu_to_be32(mpll_ss1);
	mclk->mclk770.vMPLL_SS2 = cpu_to_be32(mpll_ss2);

	वापस 0;
पूर्ण

u8 cypress_get_mclk_frequency_ratio(काष्ठा radeon_device *rdev,
				    u32 memory_घड़ी, bool strobe_mode)
अणु
	u8 mc_para_index;

	अगर (rdev->family >= CHIP_BARTS) अणु
		अगर (strobe_mode) अणु
			अगर (memory_घड़ी < 10000)
				mc_para_index = 0x00;
			अन्यथा अगर (memory_घड़ी > 47500)
				mc_para_index = 0x0f;
			अन्यथा
				mc_para_index = (u8)((memory_घड़ी - 10000) / 2500);
		पूर्ण अन्यथा अणु
			अगर (memory_घड़ी < 65000)
				mc_para_index = 0x00;
			अन्यथा अगर (memory_घड़ी > 135000)
				mc_para_index = 0x0f;
			अन्यथा
				mc_para_index = (u8)((memory_घड़ी - 60000) / 5000);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (strobe_mode) अणु
			अगर (memory_घड़ी < 10000)
				mc_para_index = 0x00;
			अन्यथा अगर (memory_घड़ी > 47500)
				mc_para_index = 0x0f;
			अन्यथा
				mc_para_index = (u8)((memory_घड़ी - 10000) / 2500);
		पूर्ण अन्यथा अणु
			अगर (memory_घड़ी < 40000)
				mc_para_index = 0x00;
			अन्यथा अगर (memory_घड़ी > 115000)
				mc_para_index = 0x0f;
			अन्यथा
				mc_para_index = (u8)((memory_घड़ी - 40000) / 5000);
		पूर्ण
	पूर्ण
	वापस mc_para_index;
पूर्ण

अटल पूर्णांक cypress_populate_mvdd_value(काष्ठा radeon_device *rdev,
				       u32 mclk,
				       RV770_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	अगर (!pi->mvdd_control) अणु
		voltage->index = eg_pi->mvdd_high_index;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
		वापस 0;
	पूर्ण

	अगर (mclk <= pi->mvdd_split_frequency) अणु
		voltage->index = eg_pi->mvdd_low_index;
		voltage->value = cpu_to_be16(MVDD_LOW_VALUE);
	पूर्ण अन्यथा अणु
		voltage->index = eg_pi->mvdd_high_index;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cypress_convert_घातer_level_to_smc(काष्ठा radeon_device *rdev,
				       काष्ठा rv7xx_pl *pl,
				       RV770_SMC_HW_PERFORMANCE_LEVEL *level,
				       u8 watermark_level)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	पूर्णांक ret;
	bool dll_state_on;

	level->gen2PCIE = pi->pcie_gen2 ?
		((pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0) : 0;
	level->gen2XSP  = (pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0;
	level->backbias = (pl->flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? 1 : 0;
	level->displayWatermark = watermark_level;

	ret = rv740_populate_sclk_value(rdev, pl->sclk, &level->sclk);
	अगर (ret)
		वापस ret;

	level->mcFlags =  0;
	अगर (pi->mclk_stutter_mode_threshold &&
	    (pl->mclk <= pi->mclk_stutter_mode_threshold) &&
	    !eg_pi->uvd_enabled) अणु
		level->mcFlags |= SMC_MC_STUTTER_EN;
		अगर (eg_pi->sclk_deep_sleep)
			level->stateFlags |= PPSMC_STATEFLAG_AUTO_PULSE_SKIP;
		अन्यथा
			level->stateFlags &= ~PPSMC_STATEFLAG_AUTO_PULSE_SKIP;
	पूर्ण

	अगर (pi->mem_gddr5) अणु
		अगर (pl->mclk > pi->mclk_edc_enable_threshold)
			level->mcFlags |= SMC_MC_EDC_RD_FLAG;

		अगर (pl->mclk > eg_pi->mclk_edc_wr_enable_threshold)
			level->mcFlags |= SMC_MC_EDC_WR_FLAG;

		level->strobeMode = cypress_get_strobe_mode_settings(rdev, pl->mclk);

		अगर (level->strobeMode & SMC_STROBE_ENABLE) अणु
			अगर (cypress_get_mclk_frequency_ratio(rdev, pl->mclk, true) >=
			    ((RREG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dll_state_on = ((RREG32(MC_SEQ_MISC5) >> 1) & 0x1) ? true : false;
			अन्यथा
				dll_state_on = ((RREG32(MC_SEQ_MISC6) >> 1) & 0x1) ? true : false;
		पूर्ण अन्यथा
			dll_state_on = eg_pi->dll_शेष_on;

		ret = cypress_populate_mclk_value(rdev,
						  pl->sclk,
						  pl->mclk,
						  &level->mclk,
						  (level->strobeMode & SMC_STROBE_ENABLE) != 0,
						  dll_state_on);
	पूर्ण अन्यथा अणु
		ret = cypress_populate_mclk_value(rdev,
						  pl->sclk,
						  pl->mclk,
						  &level->mclk,
						  true,
						  true);
	पूर्ण
	अगर (ret)
		वापस ret;

	ret = cypress_populate_voltage_value(rdev,
					     &eg_pi->vddc_voltage_table,
					     pl->vddc,
					     &level->vddc);
	अगर (ret)
		वापस ret;

	अगर (eg_pi->vddci_control) अणु
		ret = cypress_populate_voltage_value(rdev,
						     &eg_pi->vddci_voltage_table,
						     pl->vddci,
						     &level->vddci);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = cypress_populate_mvdd_value(rdev, pl->mclk, &level->mvdd);

	वापस ret;
पूर्ण

अटल पूर्णांक cypress_convert_घातer_state_to_smc(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *radeon_state,
					      RV770_SMC_SWSTATE *smc_state)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	पूर्णांक ret;

	अगर (!(radeon_state->caps & ATOM_PPLIB_DISALLOW_ON_DC))
		smc_state->flags |= PPSMC_SWSTATE_FLAG_DC;

	ret = cypress_convert_घातer_level_to_smc(rdev,
						 &state->low,
						 &smc_state->levels[0],
						 PPSMC_DISPLAY_WATERMARK_LOW);
	अगर (ret)
		वापस ret;

	ret = cypress_convert_घातer_level_to_smc(rdev,
						 &state->medium,
						 &smc_state->levels[1],
						 PPSMC_DISPLAY_WATERMARK_LOW);
	अगर (ret)
		वापस ret;

	ret = cypress_convert_घातer_level_to_smc(rdev,
						 &state->high,
						 &smc_state->levels[2],
						 PPSMC_DISPLAY_WATERMARK_HIGH);
	अगर (ret)
		वापस ret;

	smc_state->levels[0].arbValue = MC_CG_ARB_FREQ_F1;
	smc_state->levels[1].arbValue = MC_CG_ARB_FREQ_F2;
	smc_state->levels[2].arbValue = MC_CG_ARB_FREQ_F3;

	अगर (eg_pi->dynamic_ac_timing) अणु
		smc_state->levels[0].ACIndex = 2;
		smc_state->levels[1].ACIndex = 3;
		smc_state->levels[2].ACIndex = 4;
	पूर्ण अन्यथा अणु
		smc_state->levels[0].ACIndex = 0;
		smc_state->levels[1].ACIndex = 0;
		smc_state->levels[2].ACIndex = 0;
	पूर्ण

	rv770_populate_smc_sp(rdev, radeon_state, smc_state);

	वापस rv770_populate_smc_t(rdev, radeon_state, smc_state);
पूर्ण

अटल व्योम cypress_convert_mc_रेजिस्टरs(काष्ठा evergreen_mc_reg_entry *entry,
					 SMC_Evergreen_MCRegisterSet *data,
					 u32 num_entries, u32 valid_flag)
अणु
	u32 i, j;

	क्रम (i = 0, j = 0; j < num_entries; j++) अणु
		अगर (valid_flag & (1 << j)) अणु
			data->value[i] = cpu_to_be32(entry->mc_data[j]);
			i++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cypress_convert_mc_reg_table_entry_to_smc(काष्ठा radeon_device *rdev,
						      काष्ठा rv7xx_pl *pl,
						      SMC_Evergreen_MCRegisterSet *mc_reg_table_data)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 i = 0;

	क्रम (i = 0; i < eg_pi->mc_reg_table.num_entries; i++) अणु
		अगर (pl->mclk <=
		    eg_pi->mc_reg_table.mc_reg_table_entry[i].mclk_max)
			अवरोध;
	पूर्ण

	अगर ((i == eg_pi->mc_reg_table.num_entries) && (i > 0))
		--i;

	cypress_convert_mc_रेजिस्टरs(&eg_pi->mc_reg_table.mc_reg_table_entry[i],
				     mc_reg_table_data,
				     eg_pi->mc_reg_table.last,
				     eg_pi->mc_reg_table.valid_flag);
पूर्ण

अटल व्योम cypress_convert_mc_reg_table_to_smc(काष्ठा radeon_device *rdev,
						काष्ठा radeon_ps *radeon_state,
						SMC_Evergreen_MCRegisters *mc_reg_table)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);

	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &state->low,
						  &mc_reg_table->data[2]);
	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &state->medium,
						  &mc_reg_table->data[3]);
	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &state->high,
						  &mc_reg_table->data[4]);
पूर्ण

पूर्णांक cypress_upload_sw_state(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ps *radeon_new_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u16 address = pi->state_table_start +
		दुरत्व(RV770_SMC_STATETABLE, driverState);
	RV770_SMC_SWSTATE state = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = cypress_convert_घातer_state_to_smc(rdev, radeon_new_state, &state);
	अगर (ret)
		वापस ret;

	वापस rv770_copy_bytes_to_smc(rdev, address, (u8 *)&state,
				    माप(RV770_SMC_SWSTATE),
				    pi->sram_end);
पूर्ण

पूर्णांक cypress_upload_mc_reg_table(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ps *radeon_new_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	SMC_Evergreen_MCRegisters mc_reg_table = अणु 0 पूर्ण;
	u16 address;

	cypress_convert_mc_reg_table_to_smc(rdev, radeon_new_state, &mc_reg_table);

	address = eg_pi->mc_reg_table_start +
		(u16)दुरत्व(SMC_Evergreen_MCRegisters, data[2]);

	वापस rv770_copy_bytes_to_smc(rdev, address,
				       (u8 *)&mc_reg_table.data[2],
				       माप(SMC_Evergreen_MCRegisterSet) * 3,
				       pi->sram_end);
पूर्ण

u32 cypress_calculate_burst_समय(काष्ठा radeon_device *rdev,
				 u32 engine_घड़ी, u32 memory_घड़ी)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 multiplier = pi->mem_gddr5 ? 1 : 2;
	u32 result = (4 * multiplier * engine_घड़ी) / (memory_घड़ी / 2);
	u32 burst_समय;

	अगर (result <= 4)
		burst_समय = 0;
	अन्यथा अगर (result < 8)
		burst_समय = result - 4;
	अन्यथा अणु
		burst_समय = result / 2 ;
		अगर (burst_समय > 18)
			burst_समय = 18;
	पूर्ण

	वापस burst_समय;
पूर्ण

व्योम cypress_program_memory_timing_parameters(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *radeon_new_state)
अणु
	काष्ठा rv7xx_ps *new_state = rv770_get_ps(radeon_new_state);
	u32 mc_arb_burst_समय = RREG32(MC_ARB_BURST_TIME);

	mc_arb_burst_समय &= ~(STATE1_MASK | STATE2_MASK | STATE3_MASK);

	mc_arb_burst_समय |= STATE1(cypress_calculate_burst_समय(rdev,
								 new_state->low.sclk,
								 new_state->low.mclk));
	mc_arb_burst_समय |= STATE2(cypress_calculate_burst_समय(rdev,
								 new_state->medium.sclk,
								 new_state->medium.mclk));
	mc_arb_burst_समय |= STATE3(cypress_calculate_burst_समय(rdev,
								 new_state->high.sclk,
								 new_state->high.mclk));

	rv730_program_memory_timing_parameters(rdev, radeon_new_state);

	WREG32(MC_ARB_BURST_TIME, mc_arb_burst_समय);
पूर्ण

अटल व्योम cypress_populate_mc_reg_addresses(काष्ठा radeon_device *rdev,
					      SMC_Evergreen_MCRegisters *mc_reg_table)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 i, j;

	क्रम (i = 0, j = 0; j < eg_pi->mc_reg_table.last; j++) अणु
		अगर (eg_pi->mc_reg_table.valid_flag & (1 << j)) अणु
			mc_reg_table->address[i].s0 =
				cpu_to_be16(eg_pi->mc_reg_table.mc_reg_address[j].s0);
			mc_reg_table->address[i].s1 =
				cpu_to_be16(eg_pi->mc_reg_table.mc_reg_address[j].s1);
			i++;
		पूर्ण
	पूर्ण

	mc_reg_table->last = (u8)i;
पूर्ण

अटल व्योम cypress_set_mc_reg_address_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 i = 0;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RAS_TIMING_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RAS_TIMING >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_CAS_TIMING_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_CAS_TIMING >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC_TIMING_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC_TIMING >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC_TIMING2_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC_TIMING2 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RD_CTL_D0_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RD_CTL_D0 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RD_CTL_D1_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RD_CTL_D1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_WR_CTL_D0_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_WR_CTL_D0 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_WR_CTL_D1_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_WR_CTL_D1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_PMG_CMD_EMRS_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_PMG_CMD_EMRS >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_PMG_CMD_MRS_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_PMG_CMD_MRS >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_PMG_CMD_MRS1_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_PMG_CMD_MRS1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC1 >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RESERVE_M >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RESERVE_M >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC3 >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC3 >> 2;
	i++;

	eg_pi->mc_reg_table.last = (u8)i;
पूर्ण

अटल व्योम cypress_retrieve_ac_timing_क्रम_one_entry(काष्ठा radeon_device *rdev,
						     काष्ठा evergreen_mc_reg_entry *entry)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 i;

	क्रम (i = 0; i < eg_pi->mc_reg_table.last; i++)
		entry->mc_data[i] =
			RREG32(eg_pi->mc_reg_table.mc_reg_address[i].s1 << 2);

पूर्ण

अटल व्योम cypress_retrieve_ac_timing_क्रम_all_ranges(काष्ठा radeon_device *rdev,
						      काष्ठा atom_memory_घड़ी_range_table *range_table)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 i, j;

	क्रम (i = 0; i < range_table->num_entries; i++) अणु
		eg_pi->mc_reg_table.mc_reg_table_entry[i].mclk_max =
			range_table->mclk[i];
		radeon_atom_set_ac_timing(rdev, range_table->mclk[i]);
		cypress_retrieve_ac_timing_क्रम_one_entry(rdev,
							 &eg_pi->mc_reg_table.mc_reg_table_entry[i]);
	पूर्ण

	eg_pi->mc_reg_table.num_entries = range_table->num_entries;
	eg_pi->mc_reg_table.valid_flag = 0;

	क्रम (i = 0; i < eg_pi->mc_reg_table.last; i++) अणु
		क्रम (j = 1; j < range_table->num_entries; j++) अणु
			अगर (eg_pi->mc_reg_table.mc_reg_table_entry[j-1].mc_data[i] !=
			    eg_pi->mc_reg_table.mc_reg_table_entry[j].mc_data[i]) अणु
				eg_pi->mc_reg_table.valid_flag |= (1 << i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cypress_initialize_mc_reg_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u8 module_index = rv770_get_memory_module_index(rdev);
	काष्ठा atom_memory_घड़ी_range_table range_table = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = radeon_atom_get_mclk_range_table(rdev,
					       pi->mem_gddr5,
					       module_index, &range_table);
	अगर (ret)
		वापस ret;

	cypress_retrieve_ac_timing_क्रम_all_ranges(rdev, &range_table);

	वापस 0;
पूर्ण

अटल व्योम cypress_रुको_क्रम_mc_sequencer(काष्ठा radeon_device *rdev, u8 value)
अणु
	u32 i, j;
	u32 channels = 2;

	अगर ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK))
		channels = 4;
	अन्यथा अगर (rdev->family == CHIP_CEDAR)
		channels = 1;

	क्रम (i = 0; i < channels; i++) अणु
		अगर ((rdev->family == CHIP_CYPRESS) ||
		    (rdev->family == CHIP_HEMLOCK)) अणु
			WREG32_P(MC_CONFIG_MCD, MC_RD_ENABLE_MCD(i), ~MC_RD_ENABLE_MCD_MASK);
			WREG32_P(MC_CG_CONFIG_MCD, MC_RD_ENABLE_MCD(i), ~MC_RD_ENABLE_MCD_MASK);
		पूर्ण अन्यथा अणु
			WREG32_P(MC_CONFIG, MC_RD_ENABLE(i), ~MC_RD_ENABLE_MASK);
			WREG32_P(MC_CG_CONFIG, MC_RD_ENABLE(i), ~MC_RD_ENABLE_MASK);
		पूर्ण
		क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
			अगर (((RREG32(MC_SEQ_CG) & CG_SEQ_RESP_MASK) >> CG_SEQ_RESP_SHIFT) == value)
				अवरोध;
			udelay(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cypress_क्रमce_mc_use_s1(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_ps *radeon_boot_state)
अणु
	काष्ठा rv7xx_ps *boot_state = rv770_get_ps(radeon_boot_state);
	u32 strobe_mode;
	u32 mc_seq_cg;
	पूर्णांक i;

	अगर (RREG32(MC_SEQ_STATUS_M) & PMG_PWRSTATE)
		वापस;

	radeon_atom_set_ac_timing(rdev, boot_state->low.mclk);
	radeon_mc_रुको_क्रम_idle(rdev);

	अगर ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK)) अणु
		WREG32(MC_CONFIG_MCD, 0xf);
		WREG32(MC_CG_CONFIG_MCD, 0xf);
	पूर्ण अन्यथा अणु
		WREG32(MC_CONFIG, 0xf);
		WREG32(MC_CG_CONFIG, 0xf);
	पूर्ण

	क्रम (i = 0; i < rdev->num_crtc; i++)
		radeon_रुको_क्रम_vblank(rdev, i);

	WREG32(MC_SEQ_CG, MC_CG_SEQ_YCLK_SUSPEND);
	cypress_रुको_क्रम_mc_sequencer(rdev, MC_CG_SEQ_YCLK_SUSPEND);

	strobe_mode = cypress_get_strobe_mode_settings(rdev,
						       boot_state->low.mclk);

	mc_seq_cg = CG_SEQ_REQ(MC_CG_SEQ_DRAMCONF_S1);
	mc_seq_cg |= SEQ_CG_RESP(strobe_mode);
	WREG32(MC_SEQ_CG, mc_seq_cg);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(MC_SEQ_STATUS_M) & PMG_PWRSTATE)
			अवरोध;
		udelay(1);
	पूर्ण

	mc_seq_cg &= ~CG_SEQ_REQ_MASK;
	mc_seq_cg |= CG_SEQ_REQ(MC_CG_SEQ_YCLK_RESUME);
	WREG32(MC_SEQ_CG, mc_seq_cg);

	cypress_रुको_क्रम_mc_sequencer(rdev, MC_CG_SEQ_YCLK_RESUME);
पूर्ण

अटल व्योम cypress_copy_ac_timing_from_s1_to_s0(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 value;
	u32 i;

	क्रम (i = 0; i < eg_pi->mc_reg_table.last; i++) अणु
		value = RREG32(eg_pi->mc_reg_table.mc_reg_address[i].s1 << 2);
		WREG32(eg_pi->mc_reg_table.mc_reg_address[i].s0 << 2, value);
	पूर्ण
पूर्ण

अटल व्योम cypress_क्रमce_mc_use_s0(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_ps *radeon_boot_state)
अणु
	काष्ठा rv7xx_ps *boot_state = rv770_get_ps(radeon_boot_state);
	u32 strobe_mode;
	u32 mc_seq_cg;
	पूर्णांक i;

	cypress_copy_ac_timing_from_s1_to_s0(rdev);
	radeon_mc_रुको_क्रम_idle(rdev);

	अगर ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK)) अणु
		WREG32(MC_CONFIG_MCD, 0xf);
		WREG32(MC_CG_CONFIG_MCD, 0xf);
	पूर्ण अन्यथा अणु
		WREG32(MC_CONFIG, 0xf);
		WREG32(MC_CG_CONFIG, 0xf);
	पूर्ण

	क्रम (i = 0; i < rdev->num_crtc; i++)
		radeon_रुको_क्रम_vblank(rdev, i);

	WREG32(MC_SEQ_CG, MC_CG_SEQ_YCLK_SUSPEND);
	cypress_रुको_क्रम_mc_sequencer(rdev, MC_CG_SEQ_YCLK_SUSPEND);

	strobe_mode = cypress_get_strobe_mode_settings(rdev,
						       boot_state->low.mclk);

	mc_seq_cg = CG_SEQ_REQ(MC_CG_SEQ_DRAMCONF_S0);
	mc_seq_cg |= SEQ_CG_RESP(strobe_mode);
	WREG32(MC_SEQ_CG, mc_seq_cg);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (!(RREG32(MC_SEQ_STATUS_M) & PMG_PWRSTATE))
			अवरोध;
		udelay(1);
	पूर्ण

	mc_seq_cg &= ~CG_SEQ_REQ_MASK;
	mc_seq_cg |= CG_SEQ_REQ(MC_CG_SEQ_YCLK_RESUME);
	WREG32(MC_SEQ_CG, mc_seq_cg);

	cypress_रुको_क्रम_mc_sequencer(rdev, MC_CG_SEQ_YCLK_RESUME);
पूर्ण

अटल पूर्णांक cypress_populate_initial_mvdd_value(काष्ठा radeon_device *rdev,
					       RV770_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	voltage->index = eg_pi->mvdd_high_index;
	voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);

	वापस 0;
पूर्ण

पूर्णांक cypress_populate_smc_initial_state(काष्ठा radeon_device *rdev,
				       काष्ठा radeon_ps *radeon_initial_state,
				       RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_ps *initial_state = rv770_get_ps(radeon_initial_state);
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 a_t;

	table->initialState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ad_func_cntl);
	table->initialState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ad_func_cntl_2);
	table->initialState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mpll_dq_func_cntl);
	table->initialState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_dq_func_cntl_2);
	table->initialState.levels[0].mclk.mclk770.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mclk_pwrmgt_cntl);
	table->initialState.levels[0].mclk.mclk770.vDLL_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.dll_cntl);

	table->initialState.levels[0].mclk.mclk770.vMPLL_SS =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ss1);
	table->initialState.levels[0].mclk.mclk770.vMPLL_SS2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ss2);

	table->initialState.levels[0].mclk.mclk770.mclk_value =
		cpu_to_be32(initial_state->low.mclk);

	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl_2);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl_3);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM_2 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum_2);

	table->initialState.levels[0].sclk.sclk_value =
		cpu_to_be32(initial_state->low.sclk);

	table->initialState.levels[0].arbValue = MC_CG_ARB_FREQ_F0;

	table->initialState.levels[0].ACIndex = 0;

	cypress_populate_voltage_value(rdev,
				       &eg_pi->vddc_voltage_table,
				       initial_state->low.vddc,
				       &table->initialState.levels[0].vddc);

	अगर (eg_pi->vddci_control)
		cypress_populate_voltage_value(rdev,
					       &eg_pi->vddci_voltage_table,
					       initial_state->low.vddci,
					       &table->initialState.levels[0].vddci);

	cypress_populate_initial_mvdd_value(rdev,
					    &table->initialState.levels[0].mvdd);

	a_t = CG_R(0xffff) | CG_L(0);
	table->initialState.levels[0].aT = cpu_to_be32(a_t);

	table->initialState.levels[0].bSP = cpu_to_be32(pi->dsp);


	अगर (pi->boot_in_gen2)
		table->initialState.levels[0].gen2PCIE = 1;
	अन्यथा
		table->initialState.levels[0].gen2PCIE = 0;
	अगर (initial_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
		table->initialState.levels[0].gen2XSP = 1;
	अन्यथा
		table->initialState.levels[0].gen2XSP = 0;

	अगर (pi->mem_gddr5) अणु
		table->initialState.levels[0].strobeMode =
			cypress_get_strobe_mode_settings(rdev,
							 initial_state->low.mclk);

		अगर (initial_state->low.mclk > pi->mclk_edc_enable_threshold)
			table->initialState.levels[0].mcFlags = SMC_MC_EDC_RD_FLAG | SMC_MC_EDC_WR_FLAG;
		अन्यथा
			table->initialState.levels[0].mcFlags =  0;
	पूर्ण

	table->initialState.levels[1] = table->initialState.levels[0];
	table->initialState.levels[2] = table->initialState.levels[0];

	table->initialState.flags |= PPSMC_SWSTATE_FLAG_DC;

	वापस 0;
पूर्ण

पूर्णांक cypress_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
				    RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 mpll_ad_func_cntl =
		pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 =
		pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl =
		pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 =
		pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 spll_func_cntl =
		pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 =
		pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 =
		pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 mclk_pwrmgt_cntl =
		pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl =
		pi->clk_regs.rv770.dll_cntl;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	अगर (pi->acpi_vddc) अणु
		cypress_populate_voltage_value(rdev,
					       &eg_pi->vddc_voltage_table,
					       pi->acpi_vddc,
					       &table->ACPIState.levels[0].vddc);
		अगर (pi->pcie_gen2) अणु
			अगर (pi->acpi_pcie_gen2)
				table->ACPIState.levels[0].gen2PCIE = 1;
			अन्यथा
				table->ACPIState.levels[0].gen2PCIE = 0;
		पूर्ण अन्यथा
			table->ACPIState.levels[0].gen2PCIE = 0;
		अगर (pi->acpi_pcie_gen2)
			table->ACPIState.levels[0].gen2XSP = 1;
		अन्यथा
			table->ACPIState.levels[0].gen2XSP = 0;
	पूर्ण अन्यथा अणु
		cypress_populate_voltage_value(rdev,
					       &eg_pi->vddc_voltage_table,
					       pi->min_vddc_in_table,
					       &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE = 0;
	पूर्ण

	अगर (eg_pi->acpi_vddci) अणु
		अगर (eg_pi->vddci_control) अणु
			cypress_populate_voltage_value(rdev,
						       &eg_pi->vddci_voltage_table,
						       eg_pi->acpi_vddci,
						       &table->ACPIState.levels[0].vddci);
		पूर्ण
	पूर्ण

	mpll_ad_func_cntl &= ~PDNB;

	mpll_ad_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN;

	अगर (pi->mem_gddr5)
		mpll_dq_func_cntl &= ~PDNB;
	mpll_dq_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN | BYPASS;

	mclk_pwrmgt_cntl |= (MRDCKA0_RESET |
			     MRDCKA1_RESET |
			     MRDCKB0_RESET |
			     MRDCKB1_RESET |
			     MRDCKC0_RESET |
			     MRDCKC1_RESET |
			     MRDCKD0_RESET |
			     MRDCKD1_RESET);

	mclk_pwrmgt_cntl &= ~(MRDCKA0_PDNB |
			      MRDCKA1_PDNB |
			      MRDCKB0_PDNB |
			      MRDCKB1_PDNB |
			      MRDCKC0_PDNB |
			      MRDCKC1_PDNB |
			      MRDCKD0_PDNB |
			      MRDCKD1_PDNB);

	dll_cntl |= (MRDCKA0_BYPASS |
		     MRDCKA1_BYPASS |
		     MRDCKB0_BYPASS |
		     MRDCKB1_BYPASS |
		     MRDCKC0_BYPASS |
		     MRDCKC1_BYPASS |
		     MRDCKD0_BYPASS |
		     MRDCKD1_BYPASS);

	/* evergreen only */
	अगर (rdev->family <= CHIP_HEMLOCK)
		spll_func_cntl |= SPLL_RESET | SPLL_SLEEP | SPLL_BYPASS_EN;

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(mpll_ad_func_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL_2 =
		cpu_to_be32(mpll_ad_func_cntl_2);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(mpll_dq_func_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL_2 =
		cpu_to_be32(mpll_dq_func_cntl_2);
	table->ACPIState.levels[0].mclk.mclk770.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);

	table->ACPIState.levels[0].mclk.mclk770.mclk_value = 0;

	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(spll_func_cntl);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(spll_func_cntl_3);

	table->ACPIState.levels[0].sclk.sclk_value = 0;

	cypress_populate_mvdd_value(rdev, 0, &table->ACPIState.levels[0].mvdd);

	अगर (eg_pi->dynamic_ac_timing)
		table->ACPIState.levels[0].ACIndex = 1;

	table->ACPIState.levels[1] = table->ACPIState.levels[0];
	table->ACPIState.levels[2] = table->ACPIState.levels[0];

	वापस 0;
पूर्ण

अटल व्योम cypress_trim_voltage_table_to_fit_state_table(काष्ठा radeon_device *rdev,
							  काष्ठा atom_voltage_table *voltage_table)
अणु
	अचिन्हित पूर्णांक i, dअगरf;

	अगर (voltage_table->count <= MAX_NO_VREG_STEPS)
		वापस;

	dअगरf = voltage_table->count - MAX_NO_VREG_STEPS;

	क्रम (i= 0; i < MAX_NO_VREG_STEPS; i++)
		voltage_table->entries[i] = voltage_table->entries[i + dअगरf];

	voltage_table->count = MAX_NO_VREG_STEPS;
पूर्ण

पूर्णांक cypress_स्थिरruct_voltage_tables(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	पूर्णांक ret;

	ret = radeon_atom_get_voltage_table(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0,
					    &eg_pi->vddc_voltage_table);
	अगर (ret)
		वापस ret;

	अगर (eg_pi->vddc_voltage_table.count > MAX_NO_VREG_STEPS)
		cypress_trim_voltage_table_to_fit_state_table(rdev,
							      &eg_pi->vddc_voltage_table);

	अगर (eg_pi->vddci_control) अणु
		ret = radeon_atom_get_voltage_table(rdev, SET_VOLTAGE_TYPE_ASIC_VDDCI, 0,
						    &eg_pi->vddci_voltage_table);
		अगर (ret)
			वापस ret;

		अगर (eg_pi->vddci_voltage_table.count > MAX_NO_VREG_STEPS)
			cypress_trim_voltage_table_to_fit_state_table(rdev,
								      &eg_pi->vddci_voltage_table);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cypress_populate_smc_voltage_table(काष्ठा radeon_device *rdev,
					       काष्ठा atom_voltage_table *voltage_table,
					       RV770_SMC_STATETABLE *table)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < voltage_table->count; i++) अणु
		table->highSMIO[i] = 0;
		table->lowSMIO[i] |= cpu_to_be32(voltage_table->entries[i].smio_low);
	पूर्ण
पूर्ण

पूर्णांक cypress_populate_smc_voltage_tables(काष्ठा radeon_device *rdev,
					RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	अचिन्हित अक्षर i;

	अगर (eg_pi->vddc_voltage_table.count) अणु
		cypress_populate_smc_voltage_table(rdev,
						   &eg_pi->vddc_voltage_table,
						   table);

		table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_VDDC] = 0;
		table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_VDDC] =
			cpu_to_be32(eg_pi->vddc_voltage_table.mask_low);

		क्रम (i = 0; i < eg_pi->vddc_voltage_table.count; i++) अणु
			अगर (pi->max_vddc_in_table <=
			    eg_pi->vddc_voltage_table.entries[i].value) अणु
				table->maxVDDCIndexInPPTable = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (eg_pi->vddci_voltage_table.count) अणु
		cypress_populate_smc_voltage_table(rdev,
						   &eg_pi->vddci_voltage_table,
						   table);

		table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_VDDCI] = 0;
		table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_VDDCI] =
			cpu_to_be32(eg_pi->vddci_voltage_table.mask_low);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 cypress_get_mclk_split_poपूर्णांक(काष्ठा atom_memory_info *memory_info)
अणु
	अगर ((memory_info->mem_type == MEM_TYPE_GDDR3) ||
	    (memory_info->mem_type == MEM_TYPE_DDR3))
		वापस 30000;

	वापस 0;
पूर्ण

पूर्णांक cypress_get_mvdd_configuration(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u8 module_index;
	काष्ठा atom_memory_info memory_info;
	u32 पंचांगp = RREG32(GENERAL_PWRMGT);

	अगर (!(पंचांगp & BACKBIAS_PAD_EN)) अणु
		eg_pi->mvdd_high_index = 0;
		eg_pi->mvdd_low_index = 1;
		pi->mvdd_control = false;
		वापस 0;
	पूर्ण

	अगर (पंचांगp & BACKBIAS_VALUE)
		eg_pi->mvdd_high_index = 1;
	अन्यथा
		eg_pi->mvdd_high_index = 0;

	eg_pi->mvdd_low_index =
		(eg_pi->mvdd_high_index == 0) ? 1 : 0;

	module_index = rv770_get_memory_module_index(rdev);

	अगर (radeon_atom_get_memory_info(rdev, module_index, &memory_info)) अणु
		pi->mvdd_control = false;
		वापस 0;
	पूर्ण

	pi->mvdd_split_frequency =
		cypress_get_mclk_split_poपूर्णांक(&memory_info);

	अगर (pi->mvdd_split_frequency == 0) अणु
		pi->mvdd_control = false;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cypress_init_smc_table(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *radeon_boot_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	RV770_SMC_STATETABLE *table = &pi->smc_statetable;
	पूर्णांक ret;

	स_रखो(table, 0, माप(RV770_SMC_STATETABLE));

	cypress_populate_smc_voltage_tables(rdev, table);

	चयन (rdev->pm.पूर्णांक_thermal_type) अणु
	हाल THERMAL_TYPE_EVERGREEN:
	हाल THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_INTERNAL;
		अवरोध;
	हाल THERMAL_TYPE_NONE:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_NONE;
		अवरोध;
	शेष:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL;
		अवरोध;
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_REGULATOR_HOT;

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (pi->mem_gddr5)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	ret = cypress_populate_smc_initial_state(rdev, radeon_boot_state, table);
	अगर (ret)
		वापस ret;

	ret = cypress_populate_smc_acpi_state(rdev, table);
	अगर (ret)
		वापस ret;

	table->driverState = table->initialState;

	वापस rv770_copy_bytes_to_smc(rdev,
				       pi->state_table_start,
				       (u8 *)table, माप(RV770_SMC_STATETABLE),
				       pi->sram_end);
पूर्ण

पूर्णांक cypress_populate_mc_reg_table(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *radeon_boot_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_ps *boot_state = rv770_get_ps(radeon_boot_state);
	SMC_Evergreen_MCRegisters mc_reg_table = अणु 0 पूर्ण;

	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_seq_index, 1);

	cypress_populate_mc_reg_addresses(rdev, &mc_reg_table);

	cypress_convert_mc_reg_table_entry_to_smc(rdev,
						  &boot_state->low,
						  &mc_reg_table.data[0]);

	cypress_convert_mc_रेजिस्टरs(&eg_pi->mc_reg_table.mc_reg_table_entry[0],
				     &mc_reg_table.data[1], eg_pi->mc_reg_table.last,
				     eg_pi->mc_reg_table.valid_flag);

	cypress_convert_mc_reg_table_to_smc(rdev, radeon_boot_state, &mc_reg_table);

	वापस rv770_copy_bytes_to_smc(rdev, eg_pi->mc_reg_table_start,
				       (u8 *)&mc_reg_table, माप(SMC_Evergreen_MCRegisters),
				       pi->sram_end);
पूर्ण

पूर्णांक cypress_get_table_locations(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	u32 पंचांगp;
	पूर्णांक ret;

	ret = rv770_पढ़ो_smc_sram_dword(rdev,
					EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION +
					EVERGREEN_SMC_FIRMWARE_HEADER_stateTable,
					&पंचांगp, pi->sram_end);
	अगर (ret)
		वापस ret;

	pi->state_table_start = (u16)पंचांगp;

	ret = rv770_पढ़ो_smc_sram_dword(rdev,
					EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION +
					EVERGREEN_SMC_FIRMWARE_HEADER_softRegisters,
					&पंचांगp, pi->sram_end);
	अगर (ret)
		वापस ret;

	pi->soft_regs_start = (u16)पंचांगp;

	ret = rv770_पढ़ो_smc_sram_dword(rdev,
					EVERGREEN_SMC_FIRMWARE_HEADER_LOCATION +
					EVERGREEN_SMC_FIRMWARE_HEADER_mcRegisterTable,
					&पंचांगp, pi->sram_end);
	अगर (ret)
		वापस ret;

	eg_pi->mc_reg_table_start = (u16)पंचांगp;

	वापस 0;
पूर्ण

व्योम cypress_enable_display_gap(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32(CG_DISPLAY_GAP_CNTL);

	पंचांगp &= ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	पंचांगp |= (DISP1_GAP(R600_PM_DISPLAY_GAP_IGNORE) |
		DISP2_GAP(R600_PM_DISPLAY_GAP_IGNORE));

	पंचांगp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	पंचांगp |= (DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_VBLANK) |
		DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE));
	WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);
पूर्ण

अटल व्योम cypress_program_display_gap(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp, pipe;
	पूर्णांक i;

	पंचांगp = RREG32(CG_DISPLAY_GAP_CNTL) & ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	अगर (rdev->pm.dpm.new_active_crtc_count > 0)
		पंचांगp |= DISP1_GAP(R600_PM_DISPLAY_GAP_VBLANK_OR_WM);
	अन्यथा
		पंचांगp |= DISP1_GAP(R600_PM_DISPLAY_GAP_IGNORE);

	अगर (rdev->pm.dpm.new_active_crtc_count > 1)
		पंचांगp |= DISP2_GAP(R600_PM_DISPLAY_GAP_VBLANK_OR_WM);
	अन्यथा
		पंचांगp |= DISP2_GAP(R600_PM_DISPLAY_GAP_IGNORE);

	WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);

	पंचांगp = RREG32(DCCG_DISP_SLOW_SELECT_REG);
	pipe = (पंचांगp & DCCG_DISP1_SLOW_SELECT_MASK) >> DCCG_DISP1_SLOW_SELECT_SHIFT;

	अगर ((rdev->pm.dpm.new_active_crtc_count > 0) &&
	    (!(rdev->pm.dpm.new_active_crtcs & (1 << pipe)))) अणु
		/* find the first active crtc */
		क्रम (i = 0; i < rdev->num_crtc; i++) अणु
			अगर (rdev->pm.dpm.new_active_crtcs & (1 << i))
				अवरोध;
		पूर्ण
		अगर (i == rdev->num_crtc)
			pipe = 0;
		अन्यथा
			pipe = i;

		पंचांगp &= ~DCCG_DISP1_SLOW_SELECT_MASK;
		पंचांगp |= DCCG_DISP1_SLOW_SELECT(pipe);
		WREG32(DCCG_DISP_SLOW_SELECT_REG, पंचांगp);
	पूर्ण

	cypress_notअगरy_smc_display_change(rdev, rdev->pm.dpm.new_active_crtc_count > 0);
पूर्ण

व्योम cypress_dpm_setup_asic(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);

	rv740_पढ़ो_घड़ी_रेजिस्टरs(rdev);
	rv770_पढ़ो_voltage_smio_रेजिस्टरs(rdev);
	rv770_get_max_vddc(rdev);
	rv770_get_memory_type(rdev);

	अगर (eg_pi->pcie_perक्रमmance_request)
		eg_pi->pcie_perक्रमmance_request_रेजिस्टरed = false;

	अगर (eg_pi->pcie_perक्रमmance_request)
		cypress_advertise_gen2_capability(rdev);

	rv770_get_pcie_gen2_status(rdev);

	rv770_enable_acpi_pm(rdev);
पूर्ण

पूर्णांक cypress_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	पूर्णांक ret;

	अगर (pi->gfx_घड़ी_gating)
		rv770_restore_cgcg(rdev);

	अगर (rv770_dpm_enabled(rdev))
		वापस -EINVAL;

	अगर (pi->voltage_control) अणु
		rv770_enable_voltage_control(rdev, true);
		ret = cypress_स्थिरruct_voltage_tables(rdev);
		अगर (ret) अणु
			DRM_ERROR("cypress_construct_voltage_tables failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pi->mvdd_control) अणु
		ret = cypress_get_mvdd_configuration(rdev);
		अगर (ret) अणु
			DRM_ERROR("cypress_get_mvdd_configuration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (eg_pi->dynamic_ac_timing) अणु
		cypress_set_mc_reg_address_table(rdev);
		cypress_क्रमce_mc_use_s0(rdev, boot_ps);
		ret = cypress_initialize_mc_reg_table(rdev);
		अगर (ret)
			eg_pi->dynamic_ac_timing = false;
		cypress_क्रमce_mc_use_s1(rdev, boot_ps);
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv770_enable_backbias(rdev, true);

	अगर (pi->dynamic_ss)
		cypress_enable_spपढ़ो_spectrum(rdev, true);

	अगर (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, true);

	rv770_setup_bsp(rdev);
	rv770_program_git(rdev);
	rv770_program_tp(rdev);
	rv770_program_tpp(rdev);
	rv770_program_sstp(rdev);
	rv770_program_engine_speed_parameters(rdev);
	cypress_enable_display_gap(rdev);
	rv770_program_vc(rdev);

	अगर (pi->dynamic_pcie_gen2)
		cypress_enable_dynamic_pcie_gen2(rdev, true);

	ret = rv770_upload_firmware(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_upload_firmware failed\n");
		वापस ret;
	पूर्ण

	ret = cypress_get_table_locations(rdev);
	अगर (ret) अणु
		DRM_ERROR("cypress_get_table_locations failed\n");
		वापस ret;
	पूर्ण
	ret = cypress_init_smc_table(rdev, boot_ps);
	अगर (ret) अणु
		DRM_ERROR("cypress_init_smc_table failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = cypress_populate_mc_reg_table(rdev, boot_ps);
		अगर (ret) अणु
			DRM_ERROR("cypress_populate_mc_reg_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	cypress_program_response_बार(rdev);

	r7xx_start_smc(rdev);

	ret = cypress_notअगरy_smc_display_change(rdev, false);
	अगर (ret) अणु
		DRM_ERROR("cypress_notify_smc_display_change failed\n");
		वापस ret;
	पूर्ण
	cypress_enable_sclk_control(rdev, true);

	अगर (eg_pi->memory_transition)
		cypress_enable_mclk_control(rdev, true);

	cypress_start_dpm(rdev);

	अगर (pi->gfx_घड़ी_gating)
		cypress_gfx_घड़ी_gating_enable(rdev, true);

	अगर (pi->mg_घड़ी_gating)
		cypress_mg_घड़ी_gating_enable(rdev, true);

	rv770_enable_स्वतः_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	वापस 0;
पूर्ण

व्योम cypress_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	अगर (!rv770_dpm_enabled(rdev))
		वापस;

	rv770_clear_vc(rdev);

	अगर (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, false);

	अगर (pi->dynamic_pcie_gen2)
		cypress_enable_dynamic_pcie_gen2(rdev, false);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण

	अगर (pi->gfx_घड़ी_gating)
		cypress_gfx_घड़ी_gating_enable(rdev, false);

	अगर (pi->mg_घड़ी_gating)
		cypress_mg_घड़ी_gating_enable(rdev, false);

	rv770_stop_dpm(rdev);
	r7xx_stop_smc(rdev);

	cypress_enable_spपढ़ो_spectrum(rdev, false);

	अगर (eg_pi->dynamic_ac_timing)
		cypress_क्रमce_mc_use_s1(rdev, boot_ps);

	rv770_reset_smio_status(rdev);
पूर्ण

पूर्णांक cypress_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	पूर्णांक ret;

	ret = rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_restrict_performance_levels_before_switch failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->pcie_perक्रमmance_request)
		cypress_notअगरy_link_speed_change_beक्रमe_state_change(rdev, new_ps, old_ps);

	rv770_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);
	ret = rv770_halt_smc(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_halt_smc failed\n");
		वापस ret;
	पूर्ण
	ret = cypress_upload_sw_state(rdev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("cypress_upload_sw_state failed\n");
		वापस ret;
	पूर्ण
	अगर (eg_pi->dynamic_ac_timing) अणु
		ret = cypress_upload_mc_reg_table(rdev, new_ps);
		अगर (ret) अणु
			DRM_ERROR("cypress_upload_mc_reg_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	cypress_program_memory_timing_parameters(rdev, new_ps);

	ret = rv770_resume_smc(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_resume_smc failed\n");
		वापस ret;
	पूर्ण
	ret = rv770_set_sw_state(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_set_sw_state failed\n");
		वापस ret;
	पूर्ण
	rv770_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);

	अगर (eg_pi->pcie_perक्रमmance_request)
		cypress_notअगरy_link_speed_change_after_state_change(rdev, new_ps, old_ps);

	वापस 0;
पूर्ण

#अगर 0
व्योम cypress_dpm_reset_asic(काष्ठा radeon_device *rdev)
अणु
	rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(rdev);
	rv770_set_boot_state(rdev);
पूर्ण
#पूर्ण_अगर

व्योम cypress_dpm_display_configuration_changed(काष्ठा radeon_device *rdev)
अणु
	cypress_program_display_gap(rdev);
पूर्ण

पूर्णांक cypress_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi;
	काष्ठा evergreen_घातer_info *eg_pi;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	eg_pi = kzalloc(माप(काष्ठा evergreen_घातer_info), GFP_KERNEL);
	अगर (eg_pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = eg_pi;
	pi = &eg_pi->rv7xx;

	rv770_get_max_vddc(rdev);

	eg_pi->ulv.supported = false;
	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = rv7xx_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	अगर (rdev->pm.dpm.voltage_response_समय == 0)
		rdev->pm.dpm.voltage_response_समय = R600_VOLTAGERESPONSETIME_DFLT;
	अगर (rdev->pm.dpm.backbias_response_समय == 0)
		rdev->pm.dpm.backbias_response_समय = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &भागiders);
	अगर (ret)
		pi->ref_भाग = भागiders.ref_भाग + 1;
	अन्यथा
		pi->ref_भाग = R600_REFERENCEDIVIDER_DFLT;

	pi->mclk_strobe_mode_threshold = 40000;
	pi->mclk_edc_enable_threshold = 40000;
	eg_pi->mclk_edc_wr_enable_threshold = 40000;

	pi->rlp = RV770_RLP_DFLT;
	pi->rmp = RV770_RMP_DFLT;
	pi->lhp = RV770_LHP_DFLT;
	pi->lmp = RV770_LMP_DFLT;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_MVDDC, 0);

	eg_pi->vddci_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDCI, 0);

	rv770_get_engine_memory_ss(rdev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = CYPRESS_HASI_DFLT;
	pi->vrc = CYPRESS_VRC_DFLT;

	pi->घातer_gating = false;

	अगर ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK))
		pi->gfx_घड़ी_gating = false;
	अन्यथा
		pi->gfx_घड़ी_gating = true;

	pi->mg_घड़ी_gating = true;
	pi->mgcgtssm = true;
	eg_pi->ls_घड़ी_gating = false;
	eg_pi->sclk_deep_sleep = false;

	pi->dynamic_pcie_gen2 = true;

	अगर (rdev->pm.पूर्णांक_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	अन्यथा
		pi->thermal_protection = false;

	pi->display_gap = true;

	अगर (rdev->flags & RADEON_IS_MOBILITY)
		pi->dcodt = true;
	अन्यथा
		pi->dcodt = false;

	pi->ulps = true;

	eg_pi->dynamic_ac_timing = true;
	eg_pi->abm = true;
	eg_pi->mcls = true;
	eg_pi->light_sleep = true;
	eg_pi->memory_transition = true;
#अगर defined(CONFIG_ACPI)
	eg_pi->pcie_perक्रमmance_request =
		radeon_acpi_is_pcie_perक्रमmance_request_supported(rdev);
#अन्यथा
	eg_pi->pcie_perक्रमmance_request = false;
#पूर्ण_अगर

	अगर ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK) ||
	    (rdev->family == CHIP_JUNIPER))
		eg_pi->dll_शेष_on = true;
	अन्यथा
		eg_pi->dll_शेष_on = false;

	eg_pi->sclk_deep_sleep = false;
	pi->mclk_stutter_mode_threshold = 0;

	pi->sram_end = SMC_RAM_END;

	वापस 0;
पूर्ण

व्योम cypress_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
पूर्ण

bool cypress_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 vblank_समय = r600_dpm_get_vblank_समय(rdev);
	/* we never hit the non-gddr5 limit so disable it */
	u32 चयन_limit = pi->mem_gddr5 ? 450 : 0;

	अगर (vblank_समय < चयन_limit)
		वापस true;
	अन्यथा
		वापस false;

पूर्ण
