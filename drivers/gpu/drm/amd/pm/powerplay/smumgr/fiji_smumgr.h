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
#अगर_अघोषित _FIJI_SMUMANAGER_H_
#घोषणा _FIJI_SMUMANAGER_H_

#समावेश "smu73_discrete.h"
#समावेश <pp_endian.h>
#समावेश "smu7_smumgr.h"


काष्ठा fiji_pt_शेषs अणु
	uपूर्णांक8_t   SviLoadLineEn;
	uपूर्णांक8_t   SviLoadLineVddC;
	uपूर्णांक8_t   TDC_VDDC_ThrottleReleaseLimitPerc;
	uपूर्णांक8_t   TDC_MAWt;
	uपूर्णांक8_t   TdcWaterfallCtl;
	uपूर्णांक8_t   DTEAmbientTempBase;
पूर्ण;

काष्ठा fiji_smumgr अणु
	काष्ठा smu7_smumgr                   smu7_data;
	काष्ठा SMU73_Discrete_DpmTable       smc_state_table;
	काष्ठा SMU73_Discrete_Ulv            ulv_setting;
	काष्ठा SMU73_Discrete_PmFuses  घातer_tune_table;
	स्थिर काष्ठा fiji_pt_शेषs  *घातer_tune_शेषs;
पूर्ण;

#पूर्ण_अगर

