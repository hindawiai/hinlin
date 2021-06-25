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

#अगर_अघोषित SMU10_HWMGR_H
#घोषणा SMU10_HWMGR_H

#समावेश "hwmgr.h"
#समावेश "smu10_inc.h"
#समावेश "smu10_driver_if.h"
#समावेश "rv_ppsmc.h"


#घोषणा SMU10_MAX_HARDWARE_POWERLEVELS               8
#घोषणा SMU10_DYNCLK_NUMBER_OF_TREND_COEFFICIENTS   15

#घोषणा DPMFlags_SCLK_Enabled                     0x00000001
#घोषणा DPMFlags_UVD_Enabled                      0x00000002
#घोषणा DPMFlags_VCE_Enabled                      0x00000004
#घोषणा DPMFlags_ACP_Enabled                      0x00000008
#घोषणा DPMFlags_ForceHighestValid                0x40000000

/* Do not change the following, it is also defined in SMU8.h */
#घोषणा SMU_EnabledFeatureScoreboard_AcpDpmOn     0x00000001
#घोषणा SMU_EnabledFeatureScoreboard_SclkDpmOn    0x00200000
#घोषणा SMU_EnabledFeatureScoreboard_UvdDpmOn     0x01000000
#घोषणा SMU_EnabledFeatureScoreboard_VceDpmOn     0x02000000

#घोषणा SMU_PHYID_SHIFT      8

#घोषणा SMU10_PCIE_POWERGATING_TARGET_GFX            0
#घोषणा SMU10_PCIE_POWERGATING_TARGET_DDI            1
#घोषणा SMU10_PCIE_POWERGATING_TARGET_PLLCASCADE     2
#घोषणा SMU10_PCIE_POWERGATING_TARGET_PHY            3

क्रमागत VQ_TYPE अणु
	CLOCK_TYPE_DCLK = 0L,
	CLOCK_TYPE_ECLK,
	CLOCK_TYPE_SCLK,
	CLOCK_TYPE_CCLK,
	VQ_GFX_CU
पूर्ण;

#घोषणा SUSTAINABLE_SCLK_MASK  0x00ffffff
#घोषणा SUSTAINABLE_SCLK_SHIFT 0
#घोषणा SUSTAINABLE_CU_MASK    0xff000000
#घोषणा SUSTAINABLE_CU_SHIFT   24

काष्ठा smu10_dpm_entry अणु
	uपूर्णांक32_t soft_min_clk;
	uपूर्णांक32_t hard_min_clk;
	uपूर्णांक32_t soft_max_clk;
	uपूर्णांक32_t hard_max_clk;
पूर्ण;

काष्ठा smu10_घातer_level अणु
	uपूर्णांक32_t engine_घड़ी;
	uपूर्णांक8_t vddc_index;
	uपूर्णांक8_t ds_भागider_index;
	uपूर्णांक8_t ss_भागider_index;
	uपूर्णांक8_t allow_gnb_slow;
	uपूर्णांक8_t क्रमce_nbp_state;
	uपूर्णांक8_t display_wm;
	uपूर्णांक8_t vce_wm;
	uपूर्णांक8_t num_simd_to_घातerकरोwn;
	uपूर्णांक8_t hysteresis_up;
	uपूर्णांक8_t rsv[3];
पूर्ण;

/*used क्रम the nbpsFlags field in smu10_घातer state*/
#घोषणा SMU10_POWERSTATE_FLAGS_NBPS_FORCEHIGH (1<<0)
#घोषणा SMU10_POWERSTATE_FLAGS_NBPS_LOCKTOHIGH (1<<1)
#घोषणा SMU10_POWERSTATE_FLAGS_NBPS_LOCKTOLOW (1<<2)

#घोषणा SMU10_POWERSTATE_FLAGS_BAPM_DISABLE    (1<<0)

काष्ठा smu10_uvd_घड़ीs अणु
	uपूर्णांक32_t vclk;
	uपूर्णांक32_t dclk;
	uपूर्णांक32_t vclk_low_भागider;
	uपूर्णांक32_t vclk_high_भागider;
	uपूर्णांक32_t dclk_low_भागider;
	uपूर्णांक32_t dclk_high_भागider;
पूर्ण;

काष्ठा pp_disable_nbpslo_flags अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t entry : 1;
			uपूर्णांक32_t display : 1;
			uपूर्णांक32_t driver: 1;
			uपूर्णांक32_t vce : 1;
			uपूर्णांक32_t uvd : 1;
			uपूर्णांक32_t acp : 1;
			uपूर्णांक32_t reserved: 26;
		पूर्ण bits;
		uपूर्णांक32_t u32All;
	पूर्ण;
पूर्ण;


क्रमागत smu10_pstate_previous_action अणु
	DO_NOTHING = 1,
	FORCE_HIGH,
	CANCEL_FORCE_HIGH
पूर्ण;

काष्ठा smu10_घातer_state अणु
	अचिन्हित पूर्णांक magic;
	uपूर्णांक32_t level;
	काष्ठा smu10_uvd_घड़ीs uvd_घड़ीs;
	uपूर्णांक32_t evclk;
	uपूर्णांक32_t ecclk;
	uपूर्णांक32_t samclk;
	uपूर्णांक32_t acpclk;
	bool need_dfs_bypass;

	uपूर्णांक32_t nbps_flags;
	uपूर्णांक32_t bapm_flags;
	uपूर्णांक8_t dpm0_pg_nbps_low;
	uपूर्णांक8_t dpm0_pg_nbps_high;
	uपूर्णांक8_t dpm_x_nbps_low;
	uपूर्णांक8_t dpm_x_nbps_high;

	क्रमागत smu10_pstate_previous_action action;

	काष्ठा smu10_घातer_level levels[SMU10_MAX_HARDWARE_POWERLEVELS];
	काष्ठा pp_disable_nbpslo_flags nbpslo_flags;
पूर्ण;

#घोषणा SMU10_NUM_NBPSTATES        4
#घोषणा SMU10_NUM_NBPMEMORYCLOCK   2


काष्ठा smu10_display_phy_info_entry अणु
	uपूर्णांक8_t                   phy_present;
	uपूर्णांक8_t                   active_lane_mapping;
	uपूर्णांक8_t                   display_config_type;
	uपूर्णांक8_t                   active_num_of_lanes;
पूर्ण;

#घोषणा SMU10_MAX_DISPLAYPHY_IDS       10

काष्ठा smu10_display_phy_info अणु
	bool                         display_phy_access_initialized;
	काष्ठा smu10_display_phy_info_entry  entries[SMU10_MAX_DISPLAYPHY_IDS];
पूर्ण;

#घोषणा MAX_DISPLAY_CLOCK_LEVEL 8

काष्ठा smu10_प्रणाली_infoअणु
	uपूर्णांक8_t                      htc_पंचांगp_lmt;
	uपूर्णांक8_t                      htc_hyst_lmt;
पूर्ण;

#घोषणा MAX_REGULAR_DPM_NUMBER 8

काष्ठा smu10_mclk_latency_entries अणु
	uपूर्णांक32_t  frequency;
	uपूर्णांक32_t  latency;
पूर्ण;

काष्ठा smu10_mclk_latency_table अणु
	uपूर्णांक32_t  count;
	काष्ठा smu10_mclk_latency_entries  entries[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा smu10_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t clk;
	uपूर्णांक32_t vol;
पूर्ण;


काष्ठा smu10_voltage_dependency_table अणु
	uपूर्णांक32_t count;
	काष्ठा smu10_घड़ी_voltage_dependency_record entries[];
पूर्ण;

काष्ठा smu10_घड़ी_voltage_inक्रमmation अणु
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_dcefclk;
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_socclk;
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_fclk;
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_mclk;
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_dispclk;
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_dppclk;
	काष्ठा smu10_voltage_dependency_table    *vdd_dep_on_phyclk;
पूर्ण;

काष्ठा smu10_hwmgr अणु
	uपूर्णांक32_t disable_driver_thermal_policy;
	uपूर्णांक32_t thermal_स्वतः_throttling_treshold;
	काष्ठा smu10_प्रणाली_info sys_info;
	काष्ठा smu10_mclk_latency_table mclk_latency_table;

	uपूर्णांक32_t ddi_घातer_gating_disabled;

	काष्ठा smu10_display_phy_info_entry            display_phy_info;
	uपूर्णांक32_t dce_slow_sclk_threshold;

	bool disp_clk_bypass;
	bool disp_clk_bypass_pending;
	uपूर्णांक32_t bapm_enabled;

	bool video_start;
	bool battery_state;

	uपूर्णांक32_t is_nb_dpm_enabled;
	uपूर्णांक32_t is_voltage_island_enabled;
	uपूर्णांक32_t disable_smu_acp_s3_handshake;
	uपूर्णांक32_t disable_notअगरy_smu_vpu_recovery;
	bool                           in_vpu_recovery;
	bool pg_acp_init;
	uपूर्णांक8_t disp_config;

	/* PowerTune */
	uपूर्णांक32_t घातer_containment_features;
	bool cac_enabled;
	bool disable_uvd_घातer_tune_feature;
	bool enable_bapm_feature;
	bool enable_tdc_limit_feature;


	/* SMC SRAM Address of firmware header tables */
	uपूर्णांक32_t sram_end;
	uपूर्णांक32_t dpm_table_start;
	uपूर्णांक32_t soft_regs_start;

	/* start of SMU7_Fusion_DpmTable */

	uपूर्णांक8_t uvd_level_count;
	uपूर्णांक8_t vce_level_count;
	uपूर्णांक8_t acp_level_count;
	uपूर्णांक8_t samu_level_count;

	uपूर्णांक32_t fps_high_threshold;
	uपूर्णांक32_t fps_low_threshold;

	uपूर्णांक32_t dpm_flags;
	काष्ठा smu10_dpm_entry sclk_dpm;
	काष्ठा smu10_dpm_entry uvd_dpm;
	काष्ठा smu10_dpm_entry vce_dpm;
	काष्ठा smu10_dpm_entry acp_dpm;
	bool acp_घातer_up_no_dsp;

	uपूर्णांक32_t max_sclk_level;
	uपूर्णांक32_t num_of_clk_entries;

	/* CPU Power State */
	uपूर्णांक32_t                          separation_समय;
	bool                              cc6_disable;
	bool                              pstate_disable;
	bool                              cc6_setting_changed;

	uपूर्णांक32_t                             ulTotalActiveCUs;

	bool                           isp_tileA_घातer_gated;
	bool                           isp_tileB_घातer_gated;
	uपूर्णांक32_t                       isp_actual_hard_min_freq;
	uपूर्णांक32_t                       soc_actual_hard_min_freq;
	uपूर्णांक32_t                       dcf_actual_hard_min_freq;

	uपूर्णांक32_t                        f_actual_hard_min_freq;
	uपूर्णांक32_t                        fabric_actual_soft_min_freq;
	uपूर्णांक32_t                        vclk_soft_min;
	uपूर्णांक32_t                        dclk_soft_min;
	uपूर्णांक32_t                        gfx_actual_soft_min_freq;
	uपूर्णांक32_t                        gfx_actual_soft_max_freq;
	uपूर्णांक32_t                        gfx_min_freq_limit;
	uपूर्णांक32_t                        gfx_max_freq_limit; /* in 10Khz*/

	bool                           vcn_घातer_gated;
	bool                           vcn_dpg_mode;

	bool                           gfx_off_controled_by_driver;
	bool                           water_marks_exist;
	Watermarks_t                      water_marks_table;
	काष्ठा smu10_घड़ी_voltage_inक्रमmation   घड़ी_vol_info;
	DpmClocks_t                       घड़ी_प्रकारable;

	uपूर्णांक32_t active_process_mask;
	bool need_min_deep_sleep_dcefclk;
	uपूर्णांक32_t                             deep_sleep_dcefclk;
	uपूर्णांक32_t                             num_active_display;

	bool							fine_grain_enabled;
पूर्ण;

काष्ठा pp_hwmgr;

पूर्णांक smu10_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr);

/* UMD PState SMU10 Msg Parameters in MHz */
#घोषणा SMU10_UMD_PSTATE_GFXCLK                 700
#घोषणा SMU10_UMD_PSTATE_SOCCLK                 626
#घोषणा SMU10_UMD_PSTATE_FCLK                   933
#घोषणा SMU10_UMD_PSTATE_VCE                    0x03C00320
#घोषणा SMU10_UMD_PSTATE_PROखाता_VCE            0x02AD0229

#घोषणा SMU10_UMD_PSTATE_PEAK_SOCCLK            757
#घोषणा SMU10_UMD_PSTATE_PEAK_FCLK              1200

#घोषणा SMU10_UMD_PSTATE_MIN_FCLK               400
#घोषणा SMU10_UMD_PSTATE_MIN_SOCCLK             200
#घोषणा SMU10_UMD_PSTATE_MIN_VCE                0x0190012C

#पूर्ण_अगर
