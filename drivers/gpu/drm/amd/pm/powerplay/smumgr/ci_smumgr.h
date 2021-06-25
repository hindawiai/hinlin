<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _CI_SMUMANAGER_H_
#घोषणा _CI_SMUMANAGER_H_

#घोषणा SMU__NUM_SCLK_DPM_STATE  8
#घोषणा SMU__NUM_MCLK_DPM_LEVELS 6
#घोषणा SMU__NUM_LCLK_DPM_LEVELS 8
#घोषणा SMU__NUM_PCIE_DPM_LEVELS 8

#समावेश "smu7_discrete.h"
#समावेश <pp_endian.h>
#समावेश "ppatomctrl.h"

काष्ठा ci_pt_शेषs अणु
	u8 svi_load_line_en;
	u8 svi_load_line_vddc;
	u8 tdc_vddc_throttle_release_limit_perc;
	u8 tdc_mawt;
	u8 tdc_waterfall_ctl;
	u8 dte_ambient_temp_base;
	u32 display_cac;
	u32 bapm_temp_gradient;
	u16 bapmti_r[SMU7_DTE_ITERATIONS * SMU7_DTE_SOURCES * SMU7_DTE_SINKS];
	u16 bapmti_rc[SMU7_DTE_ITERATIONS * SMU7_DTE_SOURCES * SMU7_DTE_SINKS];
पूर्ण;

काष्ठा ci_mc_reg_entry अणु
	uपूर्णांक32_t mclk_max;
	uपूर्णांक32_t mc_data[SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा ci_mc_reg_table अणु
	uपूर्णांक8_t   last;
	uपूर्णांक8_t   num_entries;
	uपूर्णांक16_t  validflag;
	काष्ठा ci_mc_reg_entry    mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMU7_Discrete_MCRegisterAddress mc_reg_address[SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा ci_smumgr अणु
	uपूर्णांक32_t                             soft_regs_start;
	uपूर्णांक32_t                             dpm_table_start;
	uपूर्णांक32_t                             mc_reg_table_start;
	uपूर्णांक32_t                             fan_table_start;
	uपूर्णांक32_t                             arb_table_start;
	uपूर्णांक32_t                             ulv_setting_starts;
	काष्ठा SMU7_Discrete_DpmTable       smc_state_table;
	काष्ठा SMU7_Discrete_PmFuses  घातer_tune_table;
	स्थिर काष्ठा ci_pt_शेषs  *घातer_tune_शेषs;
	SMU7_Discrete_MCRegisters      mc_regs;
	काष्ठा ci_mc_reg_table mc_reg_table;
पूर्ण;

#पूर्ण_अगर

