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
 */
#अगर_अघोषित _VEGA10_POWERTUNE_H_
#घोषणा _VEGA10_POWERTUNE_H_

क्रमागत vega10_pt_config_reg_type अणु
	VEGA10_CONFIGREG_MMR = 0,
	VEGA10_CONFIGREG_SMC_IND,
	VEGA10_CONFIGREG_DIDT_IND,
	VEGA10_CONFIGREG_CACHE,
	VEGA10_CONFIGREG_MAX
पूर्ण;

क्रमागत vega10_didt_config_reg_type अणु
	VEGA10_CONFIGREG_DIDT = 0,
	VEGA10_CONFIGREG_GCCAC,
	VEGA10_CONFIGREG_SECAC
पूर्ण;

/* PowerContainment Features */
#घोषणा POWERCONTAINMENT_FEATURE_DTE             0x00000001
#घोषणा POWERCONTAINMENT_FEATURE_TDCLimit        0x00000002
#घोषणा POWERCONTAINMENT_FEATURE_PkgPwrLimit     0x00000004

काष्ठा vega10_pt_config_reg अणु
	uपूर्णांक32_t                           offset;
	uपूर्णांक32_t                           mask;
	uपूर्णांक32_t                           shअगरt;
	uपूर्णांक32_t                           value;
	क्रमागत vega10_pt_config_reg_type       type;
पूर्ण;

काष्ठा vega10_didt_config_reg अणु
	uपूर्णांक32_t		offset;
	uपूर्णांक32_t		mask;
	uपूर्णांक32_t		shअगरt;
	uपूर्णांक32_t		value;
पूर्ण;

काष्ठा vega10_pt_शेषs अणु
    uपूर्णांक8_t   SviLoadLineEn;
    uपूर्णांक8_t   SviLoadLineVddC;
    uपूर्णांक8_t   TDC_VDDC_ThrottleReleaseLimitPerc;
    uपूर्णांक8_t   TDC_MAWt;
    uपूर्णांक8_t   TdcWaterfallCtl;
    uपूर्णांक8_t   DTEAmbientTempBase;
पूर्ण;

व्योम vega10_initialize_घातer_tune_शेषs(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_populate_bapm_parameters_in_dpm_table(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_populate_pm_fuses(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_enable_smc_cac(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_enable_घातer_containment(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_set_घातer_limit(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t n);
पूर्णांक vega10_घातer_control_set_level(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_disable_घातer_containment(काष्ठा pp_hwmgr *hwmgr);

पूर्णांक vega10_enable_didt_config(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक vega10_disable_didt_config(काष्ठा pp_hwmgr *hwmgr);

#पूर्ण_अगर  /* _VEGA10_POWERTUNE_H_ */

