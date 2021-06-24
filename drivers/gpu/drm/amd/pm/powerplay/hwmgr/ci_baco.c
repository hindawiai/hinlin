<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
#समावेश "ci_baco.h"

#समावेश "gmc/gmc_7_1_d.h"
#समावेश "gmc/gmc_7_1_sh_mask.h"

#समावेश "bif/bif_4_1_d.h"
#समावेश "bif/bif_4_1_sh_mask.h"

#समावेश "dce/dce_8_0_d.h"
#समावेश "dce/dce_8_0_sh_mask.h"

#समावेश "smu/smu_7_0_1_d.h"
#समावेश "smu/smu_7_0_1_sh_mask.h"

#समावेश "gca/gfx_7_2_d.h"
#समावेश "gca/gfx_7_2_sh_mask.h"

अटल स्थिर काष्ठा baco_cmd_entry gpio_tbl[] =
अणु
	अणु CMD_WRITE, mmGPIOPAD_EN, 0, 0, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGPIOPAD_PD_EN, 0, 0, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGPIOPAD_PU_EN, 0, 0, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGPIOPAD_MASK, 0, 0, 0, 0xff77ffff पूर्ण,
	अणु CMD_WRITE, mmDC_GPIO_DVODATA_EN, 0, 0, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmDC_GPIO_DVODATA_MASK, 0, 0, 0, 0xffffffff पूर्ण,
	अणु CMD_WRITE, mmDC_GPIO_GENERIC_EN, 0, 0, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmDC_GPIO_GENERIC_MASK, 0, 0, 0, 0x03333333 पूर्ण,
	अणु CMD_WRITE, mmDC_GPIO_SYNCA_EN, 0, 0, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmDC_GPIO_SYNCA_MASK, 0, 0, 0, 0x00001111 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry enable_fb_req_rej_tbl[] =
अणु
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0300024 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x1, 0x0, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmBIF_FB_EN, 0, 0, 0, 0x0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry use_bclk_tbl[] =
अणु
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL__SPLL_BYPASS_EN_MASK, CG_SPLL_FUNC_CNTL__SPLL_BYPASS_EN__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL_2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_BYPASS_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_BYPASS_CHG__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_STATUS पूर्ण,
	अणु CMD_WAITFOR, mmGCK_SMC_IND_DATA, CG_SPLL_STATUS__SPLL_CHG_STATUS_MASK, 0, 0xffffffff, 0x2 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL_2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_BYPASS_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_BYPASS_CHG__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_STATUS पूर्ण,
	अणु CMD_WAITFOR, mmGCK_SMC_IND_DATA, CG_SPLL_STATUS__SPLL_CHG_STATUS_MASK, 0, 0xffffffff, 0x2 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL_2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500170 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x4000000, 0x1a, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPLL_BYPASSCLK_SEL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT, 0, 0x2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMPLL_CNTL_MODE, MPLL_CNTL_MODE__MPLL_SW_सूची_CONTROL_MASK, MPLL_CNTL_MODE__MPLL_SW_सूची_CONTROL__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMPLL_CNTL_MODE, MPLL_CNTL_MODE__MPLL_MCLK_SEL_MASK, MPLL_CNTL_MODE__MPLL_MCLK_SEL__SHIFT, 0, 0x0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry turn_off_plls_tbl[] =
अणु
	अणु CMD_READMODIFYWRITE, mmDISPPLL_BG_CNTL, DISPPLL_BG_CNTL__DISPPLL_BG_PDN_MASK, DISPPLL_BG_CNTL__DISPPLL_BG_PDN__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_CLKPIN_CNTL_DC पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_CLKPIN_CNTL_DC__OSC_EN_MASK, CG_CLKPIN_CNTL_DC__OSC_EN__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_CLKPIN_CNTL_DC__XTALIN_SEL_MASK, CG_CLKPIN_CNTL_DC__XTALIN_SEL__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmPLL_CNTL, PLL_CNTL__PLL_RESET_MASK, PLL_CNTL__PLL_RESET__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmPLL_CNTL, PLL_CNTL__PLL_POWER_DOWN_MASK, PLL_CNTL__PLL_POWER_DOWN__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmPLL_CNTL, PLL_CNTL__PLL_BYPASS_CAL_MASK, PLL_CNTL__PLL_BYPASS_CAL__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL__SPLL_RESET_MASK, CG_SPLL_FUNC_CNTL__SPLL_RESET__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL__SPLL_PWRON_MASK, CG_SPLL_FUNC_CNTL__SPLL_PWRON__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500170 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x2000000, 0x19, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x8000000, 0x1b, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMPLL_CNTL_MODE, MPLL_CNTL_MODE__GLOBAL_MPLL_RESET_MASK, MPLL_CNTL_MODE__GLOBAL_MPLL_RESET__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmMPLL_CONTROL, 0, 0, 0, 0x00000006 पूर्ण,
	अणु CMD_WRITE, mmMC_IO_RXCNTL_DPHY0_D0, 0, 0, 0, 0x00007740 पूर्ण,
	अणु CMD_WRITE, mmMC_IO_RXCNTL_DPHY0_D1, 0, 0, 0, 0x00007740 पूर्ण,
	अणु CMD_WRITE, mmMC_IO_RXCNTL_DPHY1_D0, 0, 0, 0, 0x00007740 पूर्ण,
	अणु CMD_WRITE, mmMC_IO_RXCNTL_DPHY1_D1, 0, 0, 0, 0x00007740 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMCLK_PWRMGT_CNTL, MCLK_PWRMGT_CNTL__MRDCK0_PDNB_MASK, MCLK_PWRMGT_CNTL__MRDCK0_PDNB__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMCLK_PWRMGT_CNTL, MCLK_PWRMGT_CNTL__MRDCK1_PDNB_MASK, MCLK_PWRMGT_CNTL__MRDCK1_PDNB__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMC_SEQ_CNTL_2, MC_SEQ_CNTL_2__DRST_PU_MASK, MC_SEQ_CNTL_2__DRST_PU__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmMC_SEQ_CNTL_2, MC_SEQ_CNTL_2__DRST_PD_MASK, MC_SEQ_CNTL_2__DRST_PD__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_CLKPIN_CNTL_2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN_MASK, CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPLL_BYPASSCLK_SEL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT, 0, 0x4 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMISC_CLK_CTRL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL_MASK, MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL__SHIFT, 0, 0x2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MISC_CLK_CTRL__ZCLK_SEL_MASK, MISC_CLK_CTRL__ZCLK_SEL__SHIFT, 0, 0x2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MISC_CLK_CTRL__DFT_SMS_PG_CLK_SEL_MASK, MISC_CLK_CTRL__DFT_SMS_PG_CLK_SEL__SHIFT, 0, 0x2 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixTHM_CLK_CNTL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, THM_CLK_CNTL__CMON_CLK_SEL_MASK, THM_CLK_CNTL__CMON_CLK_SEL__SHIFT, 0, 0x2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, THM_CLK_CNTL__TMON_CLK_SEL_MASK, THM_CLK_CNTL__TMON_CLK_SEL__SHIFT, 0, 0x2 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry enter_baco_tbl[] =
अणु
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_EN_MASK, BACO_CNTL__BACO_EN__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_BCLK_OFF_MASK, BACO_CNTL__BACO_BCLK_OFF__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR,         mmBACO_CNTL, BACO_CNTL__BACO_BCLK_OFF_MASK, 0, 5, 0x02 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ISO_DIS_MASK, BACO_CNTL__BACO_ISO_DIS__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR,         mmBACO_CNTL, BACO_CNTL__BACO_ISO_DIS_MASK, 0, 5,  0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ANA_ISO_DIS_MASK, BACO_CNTL__BACO_ANA_ISO_DIS__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR,         mmBACO_CNTL, BACO_CNTL__BACO_ANA_ISO_DIS_MASK, 0, 5, 0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_POWER_OFF_MASK, BACO_CNTL__BACO_POWER_OFF__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR,         mmBACO_CNTL, BACO_CNTL__BACO_POWER_OFF_MASK, 0, 5, 0x08 पूर्ण,
	अणु CMD_WAITFOR,         mmBACO_CNTL, BACO_CNTL__BACO_MODE_MASK, 0, 0xffffffff, 0x40 पूर्ण
पूर्ण;

#घोषणा BACO_CNTL__PWRGOOD_MASK  BACO_CNTL__PWRGOOD_GPIO_MASK+BACO_CNTL__PWRGOOD_MEM_MASK+BACO_CNTL__PWRGOOD_DVO_MASK

अटल स्थिर काष्ठा baco_cmd_entry निकास_baco_tbl[] =
अणु
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_RESET_EN_MASK, BACO_CNTL__BACO_RESET_EN__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_BCLK_OFF_MASK,           BACO_CNTL__BACO_BCLK_OFF__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_POWER_OFF_MASK,          BACO_CNTL__BACO_POWER_OFF__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_DELAY_MS, 0, 0, 0, 20, 0 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__PWRGOOD_BF_MASK, 0, 0xffffffff, 0x200 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ISO_DIS_MASK, BACO_CNTL__BACO_ISO_DIS__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__PWRGOOD_MASK, 0, 5, 0x1c00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ANA_ISO_DIS_MASK, BACO_CNTL__BACO_ANA_ISO_DIS__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_RESET_EN_MASK, BACO_CNTL__BACO_RESET_EN__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__RCU_BIF_CONFIG_DONE_MASK, 0, 5, 0x100 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_EN_MASK, BACO_CNTL__BACO_EN__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_MODE_MASK, 0, 0xffffffff, 0x00 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry clean_baco_tbl[] =
अणु
	अणु CMD_WRITE, mmBIOS_SCRATCH_6, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_7, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmCP_PFP_UCODE_ADDR, 0, 0, 0, 0 पूर्ण
पूर्ण;

पूर्णांक ci_baco_set_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE state)
अणु
	क्रमागत BACO_STATE cur_state;

	smu7_baco_get_state(hwmgr, &cur_state);

	अगर (cur_state == state)
		/* aisc alपढ़ोy in the target state */
		वापस 0;

	अगर (state == BACO_STATE_IN) अणु
		baco_program_रेजिस्टरs(hwmgr, gpio_tbl, ARRAY_SIZE(gpio_tbl));
		baco_program_रेजिस्टरs(hwmgr, enable_fb_req_rej_tbl,
				       ARRAY_SIZE(enable_fb_req_rej_tbl));
		baco_program_रेजिस्टरs(hwmgr, use_bclk_tbl, ARRAY_SIZE(use_bclk_tbl));
		baco_program_रेजिस्टरs(hwmgr, turn_off_plls_tbl,
				       ARRAY_SIZE(turn_off_plls_tbl));
		अगर (baco_program_रेजिस्टरs(hwmgr, enter_baco_tbl,
					   ARRAY_SIZE(enter_baco_tbl)))
			वापस 0;

	पूर्ण अन्यथा अगर (state == BACO_STATE_OUT) अणु
		/* HW requires at least 20ms between regulator off and on */
		msleep(20);
		/* Execute Hardware BACO निकास sequence */
		अगर (baco_program_रेजिस्टरs(hwmgr, निकास_baco_tbl,
					   ARRAY_SIZE(निकास_baco_tbl))) अणु
			अगर (baco_program_रेजिस्टरs(hwmgr, clean_baco_tbl,
						   ARRAY_SIZE(clean_baco_tbl)))
				वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
