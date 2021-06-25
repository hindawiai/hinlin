<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _POLARIS10_SMUMANAGER_H
#घोषणा _POLARIS10_SMUMANAGER_H


#समावेश <pp_endian.h>
#समावेश "smu74.h"
#समावेश "smu74_discrete.h"
#समावेश "smu7_smumgr.h"

#घोषणा SMC_RAM_END 0x40000

काष्ठा polaris10_pt_शेषs अणु
	uपूर्णांक8_t   SviLoadLineEn;
	uपूर्णांक8_t   SviLoadLineVddC;
	uपूर्णांक8_t   TDC_VDDC_ThrottleReleaseLimitPerc;
	uपूर्णांक8_t   TDC_MAWt;
	uपूर्णांक8_t   TdcWaterfallCtl;
	uपूर्णांक8_t   DTEAmbientTempBase;

	uपूर्णांक32_t  DisplayCac;
	uपूर्णांक32_t  BAPM_TEMP_GRADIENT;
	uपूर्णांक16_t  BAPMTI_R[SMU74_DTE_ITERATIONS * SMU74_DTE_SOURCES * SMU74_DTE_SINKS];
	uपूर्णांक16_t  BAPMTI_RC[SMU74_DTE_ITERATIONS * SMU74_DTE_SOURCES * SMU74_DTE_SINKS];
पूर्ण;

काष्ठा polaris10_range_table अणु
	uपूर्णांक32_t trans_lower_frequency; /* in 10khz */
	uपूर्णांक32_t trans_upper_frequency;
पूर्ण;

काष्ठा polaris10_smumgr अणु
	काष्ठा smu7_smumgr smu7_data;
	uपूर्णांक8_t रक्षित_mode;
	SMU74_Discrete_DpmTable              smc_state_table;
	काष्ठा SMU74_Discrete_Ulv            ulv_setting;
	काष्ठा SMU74_Discrete_PmFuses  घातer_tune_table;
	काष्ठा polaris10_range_table                range_table[NUM_SCLK_RANGE];
	स्थिर काष्ठा polaris10_pt_शेषs       *घातer_tune_शेषs;
	uपूर्णांक32_t               bअगर_sclk_table[SMU74_MAX_LEVELS_LINK];
	pp_atomctrl_mc_reg_table             mc_reg_table;
पूर्ण;


#पूर्ण_अगर
