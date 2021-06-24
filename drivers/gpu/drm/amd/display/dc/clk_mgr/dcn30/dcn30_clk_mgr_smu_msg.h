<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DAL_DC_DCN30_CLK_MGR_SMU_MSG_H_
#घोषणा DAL_DC_DCN30_CLK_MGR_SMU_MSG_H_

#समावेश "core_types.h"

#घोषणा SMU11_DRIVER_IF_VERSION 0x1F

प्रकार क्रमागत अणु
	PPCLK_GFXCLK = 0,
	PPCLK_SOCCLK,
	PPCLK_UCLK,
	PPCLK_FCLK,
	PPCLK_DCLK_0,
	PPCLK_VCLK_0,
	PPCLK_DCLK_1,
	PPCLK_VCLK_1,
	PPCLK_DCEFCLK,
	PPCLK_DISPCLK,
	PPCLK_PIXCLK,
	PPCLK_PHYCLK,
	PPCLK_DTBCLK,
	PPCLK_COUNT,
पूर्ण PPCLK_e;

प्रकार काष्ठा अणु
	uपूर्णांक16_t MinClock; // This is either DCEFCLK or SOCCLK (in MHz)
	uपूर्णांक16_t MaxClock; // This is either DCEFCLK or SOCCLK (in MHz)
	uपूर्णांक16_t MinUclk;
	uपूर्णांक16_t MaxUclk;

	uपूर्णांक8_t  WmSetting;
	uपूर्णांक8_t  Flags;
	uपूर्णांक8_t  Padding[2];

पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
	WM_SOCCLK = 0,
	WM_DCEFCLK,
	WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार क्रमागत अणु
	WATERMARKS_CLOCK_RANGE = 0,
	WATERMARKS_DUMMY_PSTATE,
	WATERMARKS_MALL,
	WATERMARKS_COUNT,
पूर्ण WATERMARKS_FLAGS_e;

प्रकार काष्ठा अणु
	// Watermarks
	WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];
पूर्ण Watermarks_t;

प्रकार काष्ठा अणु
	Watermarks_t Watermarks;

	uपूर्णांक32_t     MmHubPadding[8]; // SMU पूर्णांकernal use
पूर्ण WatermarksExternal_t;

#घोषणा TABLE_WATERMARKS 1

काष्ठा clk_mgr_पूर्णांकernal;

bool         dcn30_smu_test_message(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t input);
bool         dcn30_smu_get_smu_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक *version);
bool         dcn30_smu_check_driver_अगर_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
bool         dcn30_smu_check_msg_header_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
व्योम         dcn30_smu_set_dram_addr_high(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_high);
व्योम         dcn30_smu_set_dram_addr_low(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_low);
व्योम         dcn30_smu_transfer_wm_table_smu_2_dram(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
व्योम         dcn30_smu_transfer_wm_table_dram_2_smu(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
अचिन्हित पूर्णांक dcn30_smu_set_hard_min_by_freq(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, uपूर्णांक16_t freq_mhz);
अचिन्हित पूर्णांक dcn30_smu_set_hard_max_by_freq(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, uपूर्णांक16_t freq_mhz);
अचिन्हित पूर्णांक dcn30_smu_get_dpm_freq_by_index(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, uपूर्णांक8_t dpm_level);
अचिन्हित पूर्णांक dcn30_smu_get_dc_mode_max_dpm_freq(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk);
व्योम         dcn30_smu_set_min_deep_sleep_dcef_clk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t freq_mhz);
व्योम         dcn30_smu_set_num_of_displays(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t num_displays);
व्योम         dcn30_smu_set_display_refresh_from_mall(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable, uपूर्णांक8_t cache_समयr_delay, uपूर्णांक8_t cache_समयr_scale);
व्योम         dcn30_smu_set_बाह्यal_client_df_cstate_allow(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable);
व्योम         dcn30_smu_set_pme_workaround(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);

#पूर्ण_अगर /* DAL_DC_DCN30_CLK_MGR_SMU_MSG_H_ */
