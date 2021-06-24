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

#अगर_अघोषित DAL_DC_301_SMU_H_
#घोषणा DAL_DC_301_SMU_H_

#घोषणा SMU13_DRIVER_IF_VERSION 2

प्रकार काष्ठा अणु
	uपूर्णांक32_t fclk;
	uपूर्णांक32_t memclk;
	uपूर्णांक32_t voltage;
पूर्ण df_pstate_t;

प्रकार काष्ठा अणु
	uपूर्णांक32_t vclk;
	uपूर्णांक32_t dclk;
पूर्ण vcn_clk_t;

प्रकार क्रमागत अणु
	DSPCLK_DCFCLK = 0,
	DSPCLK_DISPCLK,
	DSPCLK_PIXCLK,
	DSPCLK_PHYCLK,
	DSPCLK_COUNT,
पूर्ण DSPCLK_e;

प्रकार काष्ठा अणु
	uपूर्णांक16_t Freq; // in MHz
	uपूर्णांक16_t Vid;  // min voltage in SVI2 VID
पूर्ण DisplayClockTable_t;

प्रकार काष्ठा अणु
	uपूर्णांक16_t MinClock; // This is either DCFCLK or SOCCLK (in MHz)
	uपूर्णांक16_t MaxClock; // This is either DCFCLK or SOCCLK (in MHz)
	uपूर्णांक16_t MinMclk;
	uपूर्णांक16_t MaxMclk;

	uपूर्णांक8_t  WmSetting;
	uपूर्णांक8_t  WmType;  // Used क्रम normal pstate change or memory retraining
	uपूर्णांक8_t  Padding[2];
पूर्ण WatermarkRowGeneric_t;


#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
	WM_SOCCLK = 0,
	WM_DCFCLK,
	WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार काष्ठा अणु
  // Watermarks
	WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];

	uपूर्णांक32_t     MmHubPadding[7]; // SMU पूर्णांकernal use
पूर्ण Watermarks_t;


#घोषणा TABLE_WATERMARKS         1
#घोषणा TABLE_DPMCLOCKS          4 // Called by Driver


#घोषणा VG_NUM_DCFCLK_DPM_LEVELS   7
#घोषणा VG_NUM_DISPCLK_DPM_LEVELS  7
#घोषणा VG_NUM_DPPCLK_DPM_LEVELS   7
#घोषणा VG_NUM_SOCCLK_DPM_LEVELS   7
#घोषणा VG_NUM_ISPICLK_DPM_LEVELS  7
#घोषणा VG_NUM_ISPXCLK_DPM_LEVELS  7
#घोषणा VG_NUM_VCN_DPM_LEVELS      5
#घोषणा VG_NUM_FCLK_DPM_LEVELS     4
#घोषणा VG_NUM_SOC_VOLTAGE_LEVELS  8

// copy from vgh/vangogh/pmfw_driver_अगर.h
काष्ठा vg_dpm_घड़ीs अणु
	uपूर्णांक32_t DcfClocks[VG_NUM_DCFCLK_DPM_LEVELS];
	uपूर्णांक32_t DispClocks[VG_NUM_DISPCLK_DPM_LEVELS];
	uपूर्णांक32_t DppClocks[VG_NUM_DPPCLK_DPM_LEVELS];
	uपूर्णांक32_t SocClocks[VG_NUM_SOCCLK_DPM_LEVELS];
	uपूर्णांक32_t IspiClocks[VG_NUM_ISPICLK_DPM_LEVELS];
	uपूर्णांक32_t IspxClocks[VG_NUM_ISPXCLK_DPM_LEVELS];
	vcn_clk_t VcnClocks[VG_NUM_VCN_DPM_LEVELS];

	uपूर्णांक32_t SocVoltage[VG_NUM_SOC_VOLTAGE_LEVELS];

	df_pstate_t DfPstateTable[VG_NUM_FCLK_DPM_LEVELS];

	uपूर्णांक32_t MinGfxClk;
	uपूर्णांक32_t MaxGfxClk;

	uपूर्णांक8_t NumDfPstatesEnabled;
	uपूर्णांक8_t NumDcfclkLevelsEnabled;
	uपूर्णांक8_t NumDispClkLevelsEnabled;  //applies to both dispclk and dppclk
	uपूर्णांक8_t NumSocClkLevelsEnabled;

	uपूर्णांक8_t IspClkLevelsEnabled;  //applies to both ispiclk and ispxclk
	uपूर्णांक8_t VcnClkLevelsEnabled;  //applies to both vclk/dclk
	uपूर्णांक8_t spare[2];
पूर्ण;

काष्ठा smu_dpm_clks अणु
	काष्ठा vg_dpm_घड़ीs *dpm_clks;
	जोड़ large_पूर्णांकeger mc_address;
पूर्ण;

काष्ठा watermarks अणु
  // Watermarks
	WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];

	uपूर्णांक32_t     MmHubPadding[7]; // SMU पूर्णांकernal use
पूर्ण;


काष्ठा display_idle_optimization अणु
	अचिन्हित पूर्णांक df_request_disabled : 1;
	अचिन्हित पूर्णांक phy_ref_clk_off     : 1;
	अचिन्हित पूर्णांक s0i2_rdy            : 1;
	अचिन्हित पूर्णांक reserved            : 29;
पूर्ण;

जोड़ display_idle_optimization_u अणु
	काष्ठा display_idle_optimization idle_info;
	uपूर्णांक32_t data;
पूर्ण;


पूर्णांक dcn301_smu_get_smu_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
पूर्णांक dcn301_smu_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dispclk_khz);
पूर्णांक dcn301_smu_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
पूर्णांक dcn301_smu_set_hard_min_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dcfclk_khz);
पूर्णांक dcn301_smu_set_min_deep_sleep_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_min_ds_dcfclk_khz);
पूर्णांक dcn301_smu_set_dppclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dpp_khz);
व्योम dcn301_smu_set_display_idle_optimization(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t idle_info);
व्योम dcn301_smu_enable_phy_refclk_pwrdwn(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable);
व्योम dcn301_smu_enable_pme_wa(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
व्योम dcn301_smu_set_dram_addr_high(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_high);
व्योम dcn301_smu_set_dram_addr_low(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_low);
व्योम dcn301_smu_transfer_dpm_table_smu_2_dram(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
व्योम dcn301_smu_transfer_wm_table_dram_2_smu(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);

#पूर्ण_अगर /* DAL_DC_301_SMU_H_ */
