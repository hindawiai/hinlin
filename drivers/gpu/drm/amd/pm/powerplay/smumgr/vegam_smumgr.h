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

#अगर_अघोषित _VEGAM_SMUMANAGER_H
#घोषणा _VEGAM_SMUMANAGER_H


#समावेश <pp_endian.h>
#समावेश "smu75_discrete.h"
#समावेश "smu7_smumgr.h"

#घोषणा SMC_RAM_END 0x40000

#घोषणा DPMTuning_Uphyst_Shअगरt    0
#घोषणा DPMTuning_Downhyst_Shअगरt  8
#घोषणा DPMTuning_Activity_Shअगरt  16

#घोषणा GraphicsDPMTuning_VEGAM    0x001e6400
#घोषणा MemoryDPMTuning_VEGAM      0x000f3c0a
#घोषणा SclkDPMTuning_VEGAM        0x002d000a
#घोषणा MclkDPMTuning_VEGAM        0x001f100a


काष्ठा vegam_pt_शेषs अणु
	uपूर्णांक8_t   SviLoadLineEn;
	uपूर्णांक8_t   SviLoadLineVddC;
	uपूर्णांक8_t   TDC_VDDC_ThrottleReleaseLimitPerc;
	uपूर्णांक8_t   TDC_MAWt;
	uपूर्णांक8_t   TdcWaterfallCtl;
	uपूर्णांक8_t   DTEAmbientTempBase;

	uपूर्णांक32_t  DisplayCac;
	uपूर्णांक32_t  BAPM_TEMP_GRADIENT;
	uपूर्णांक16_t  BAPMTI_R[SMU75_DTE_ITERATIONS * SMU75_DTE_SOURCES * SMU75_DTE_SINKS];
	uपूर्णांक16_t  BAPMTI_RC[SMU75_DTE_ITERATIONS * SMU75_DTE_SOURCES * SMU75_DTE_SINKS];
पूर्ण;

काष्ठा vegam_range_table अणु
	uपूर्णांक32_t trans_lower_frequency; /* in 10khz */
	uपूर्णांक32_t trans_upper_frequency;
पूर्ण;

काष्ठा vegam_smumgr अणु
	काष्ठा smu7_smumgr smu7_data;
	uपूर्णांक8_t रक्षित_mode;
	SMU75_Discrete_DpmTable              smc_state_table;
	काष्ठा SMU75_Discrete_Ulv            ulv_setting;
	काष्ठा SMU75_Discrete_PmFuses  घातer_tune_table;
	काष्ठा vegam_range_table                range_table[NUM_SCLK_RANGE];
	स्थिर काष्ठा vegam_pt_शेषs       *घातer_tune_शेषs;
	uपूर्णांक32_t               bअगर_sclk_table[SMU75_MAX_LEVELS_LINK];
पूर्ण;


#पूर्ण_अगर
