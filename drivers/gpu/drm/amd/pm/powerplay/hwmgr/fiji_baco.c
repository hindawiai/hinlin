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
#समावेश "fiji_baco.h"

#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"

#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"

#समावेश "smu/smu_7_1_3_d.h"
#समावेश "smu/smu_7_1_3_sh_mask.h"


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
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_BYPASS_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_BYPASS_CHG__SHIFT, 0,  0x0 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG__SHIFT, 0,  0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_STATUS पूर्ण,
	अणु CMD_WAITFOR, mmGCK_SMC_IND_DATA, CG_SPLL_STATUS__SPLL_CHG_STATUS_MASK, 0, 0xffffffff, 0x2 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL_2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG_MASK, CG_SPLL_FUNC_CNTL_2__SPLL_CTLREQ_CHG__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500170 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x4000000, 0x1a, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPLL_BYPASSCLK_SEL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT, 0, 0x2 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry turn_off_plls_tbl[] =
अणु
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_SPLL_FUNC_CNTL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL__SPLL_RESET_MASK, CG_SPLL_FUNC_CNTL__SPLL_RESET__SHIFT, 0,     0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_SPLL_FUNC_CNTL__SPLL_PWRON_MASK, CG_SPLL_FUNC_CNTL__SPLL_PWRON__SHIFT, 0,     0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, 0xC0500170 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x2000000, 0x19, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, 0x8000000, 0x1b, 0, 0x0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry clk_req_b_tbl[] =
अणु
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_CLKPIN_CNTL_2 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN_MASK, CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMPLL_BYPASSCLK_SEL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK, MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT, 0, 0x4 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixMISC_CLK_CTRL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL_MASK, MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, MISC_CLK_CTRL__ZCLK_SEL_MASK, MISC_CLK_CTRL__ZCLK_SEL__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixCG_CLKPIN_CNTL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, CG_CLKPIN_CNTL__BCLK_AS_XCLK_MASK, CG_CLKPIN_CNTL__BCLK_AS_XCLK__SHIFT, 0, 0x0 पूर्ण,
	अणु CMD_WRITE, mmGCK_SMC_IND_INDEX, 0, 0, 0, ixTHM_CLK_CNTL पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, THM_CLK_CNTL__CMON_CLK_SEL_MASK, THM_CLK_CNTL__CMON_CLK_SEL__SHIFT, 0, 0x1 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmGCK_SMC_IND_DATA, THM_CLK_CNTL__TMON_CLK_SEL_MASK, THM_CLK_CNTL__TMON_CLK_SEL__SHIFT, 0, 0x1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry enter_baco_tbl[] =
अणु
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_EN_MASK, BACO_CNTL__BACO_EN__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_BIF_SCLK_SWITCH_MASK, BACO_CNTL__BACO_BIF_SCLK_SWITCH__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_BIF_SCLK_SWITCH_MASK, 0, 5, 0x40000 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_BCLK_OFF_MASK, BACO_CNTL__BACO_BCLK_OFF__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_BCLK_OFF_MASK, 0, 5, 0x02 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ISO_DIS_MASK, BACO_CNTL__BACO_ISO_DIS__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_ISO_DIS_MASK, 0, 5, 0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ANA_ISO_DIS_MASK, BACO_CNTL__BACO_ANA_ISO_DIS__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_ANA_ISO_DIS_MASK, 0, 5, 0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_POWER_OFF_MASK, BACO_CNTL__BACO_POWER_OFF__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_POWER_OFF_MASK, 0, 5, 0x08 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_MODE_MASK, 0, 0xffffffff, 0x40 पूर्ण
पूर्ण;

#घोषणा BACO_CNTL__PWRGOOD_MASK  BACO_CNTL__PWRGOOD_GPIO_MASK+BACO_CNTL__PWRGOOD_MEM_MASK+BACO_CNTL__PWRGOOD_DVO_MASK

अटल स्थिर काष्ठा baco_cmd_entry निकास_baco_tbl[] =
अणु
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_RESET_EN_MASK, BACO_CNTL__BACO_RESET_EN__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_BCLK_OFF_MASK, BACO_CNTL__BACO_BCLK_OFF__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_POWER_OFF_MASK, BACO_CNTL__BACO_POWER_OFF__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__PWRGOOD_BF_MASK, 0, 0xffffffff, 0x200 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ISO_DIS_MASK, BACO_CNTL__BACO_ISO_DIS__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__PWRGOOD_MASK, 0, 5, 0x1c00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_ANA_ISO_DIS_MASK, BACO_CNTL__BACO_ANA_ISO_DIS__SHIFT, 0, 0x01 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_BIF_SCLK_SWITCH_MASK, BACO_CNTL__BACO_BIF_SCLK_SWITCH__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_RESET_EN_MASK, BACO_CNTL__BACO_RESET_EN__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__RCU_BIF_CONFIG_DONE_MASK, 0, 5, 0x100 पूर्ण,
	अणु CMD_READMODIFYWRITE, mmBACO_CNTL, BACO_CNTL__BACO_EN_MASK, BACO_CNTL__BACO_EN__SHIFT, 0, 0x00 पूर्ण,
	अणु CMD_WAITFOR, mmBACO_CNTL, BACO_CNTL__BACO_MODE_MASK, 0, 0xffffffff, 0x00 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा baco_cmd_entry clean_baco_tbl[] =
अणु
	अणु CMD_WRITE, mmBIOS_SCRATCH_0, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_1, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_2, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_3, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_4, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_5, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_6, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_7, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_8, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_9, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_10, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_11, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_12, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_13, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_14, 0, 0, 0, 0 पूर्ण,
	अणु CMD_WRITE, mmBIOS_SCRATCH_15, 0, 0, 0, 0 पूर्ण
पूर्ण;

पूर्णांक fiji_baco_set_state(काष्ठा pp_hwmgr *hwmgr, क्रमागत BACO_STATE state)
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
		baco_program_रेजिस्टरs(hwmgr, clk_req_b_tbl, ARRAY_SIZE(clk_req_b_tbl));
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
