<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Author: Huang Rui <ray.huang@amd.com>
 *
 */

#अगर_अघोषित _ICELAND_SMUMGR_H_
#घोषणा _ICELAND_SMUMGR_H_


#समावेश "smu7_smumgr.h"
#समावेश "pp_endian.h"
#समावेश "smu71_discrete.h"

काष्ठा iceland_pt_शेषs अणु
	uपूर्णांक8_t   svi_load_line_en;
	uपूर्णांक8_t   svi_load_line_vddc;
	uपूर्णांक8_t   tdc_vddc_throttle_release_limit_perc;
	uपूर्णांक8_t   tdc_mawt;
	uपूर्णांक8_t   tdc_waterfall_ctl;
	uपूर्णांक8_t   dte_ambient_temp_base;
	uपूर्णांक32_t  display_cac;
	uपूर्णांक32_t  bapm_temp_gradient;
	uपूर्णांक16_t  bapmti_r[SMU71_DTE_ITERATIONS * SMU71_DTE_SOURCES * SMU71_DTE_SINKS];
	uपूर्णांक16_t  bapmti_rc[SMU71_DTE_ITERATIONS * SMU71_DTE_SOURCES * SMU71_DTE_SINKS];
पूर्ण;

काष्ठा iceland_mc_reg_entry अणु
	uपूर्णांक32_t mclk_max;
	uपूर्णांक32_t mc_data[SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा iceland_mc_reg_table अणु
	uपूर्णांक8_t   last;               /* number of रेजिस्टरs*/
	uपूर्णांक8_t   num_entries;        /* number of entries in mc_reg_table_entry used*/
	uपूर्णांक16_t  validflag;          /* indicate the corresponding रेजिस्टर is valid or not. 1: valid, 0: invalid. bit0->address[0], bit1->address[1], etc.*/
	काष्ठा iceland_mc_reg_entry    mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMU71_Discrete_MCRegisterAddress mc_reg_address[SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा iceland_smumgr अणु
	काष्ठा smu7_smumgr smu7_data;
	काष्ठा SMU71_Discrete_DpmTable       smc_state_table;
	काष्ठा SMU71_Discrete_PmFuses  घातer_tune_table;
	काष्ठा SMU71_Discrete_Ulv            ulv_setting;
	स्थिर काष्ठा iceland_pt_शेषs  *घातer_tune_शेषs;
	SMU71_Discrete_MCRegisters      mc_regs;
	काष्ठा iceland_mc_reg_table mc_reg_table;
पूर्ण;

#पूर्ण_अगर
