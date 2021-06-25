<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित DAL_DC_RN_CLK_MGR_VBIOS_SMU_H_
#घोषणा DAL_DC_RN_CLK_MGR_VBIOS_SMU_H_

पूर्णांक rn_vbios_smu_get_smu_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
पूर्णांक rn_vbios_smu_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dispclk_khz);
पूर्णांक rn_vbios_smu_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
पूर्णांक rn_vbios_smu_set_hard_min_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dcfclk_khz);
पूर्णांक rn_vbios_smu_set_min_deep_sleep_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_min_ds_dcfclk_khz);
व्योम rn_vbios_smu_set_phyclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_phyclk_khz);
पूर्णांक rn_vbios_smu_set_dppclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dpp_khz);
व्योम rn_vbios_smu_set_dcn_low_घातer_state(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक display_count);
व्योम rn_vbios_smu_enable_48mhz_पंचांगdp_refclk_pwrdwn(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable);
व्योम rn_vbios_smu_enable_pme_wa(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
पूर्णांक rn_vbios_smu_is_periodic_retraining_disabled(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);

#पूर्ण_अगर /* DAL_DC_DCN10_RV1_CLK_MGR_VBIOS_SMU_H_ */
