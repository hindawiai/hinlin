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

#अगर_अघोषित _VEGA12_HWMGR_H_
#घोषणा _VEGA12_HWMGR_H_

#समावेश "hwmgr.h"
#समावेश "vega12/smu9_driver_if.h"
#समावेश "ppatomfwctrl.h"

#घोषणा VEGA12_MAX_HARDWARE_POWERLEVELS 2

#घोषणा WaterMarksExist  1
#घोषणा WaterMarksLoaded 2

#घोषणा VG12_PSUEDO_NUM_GFXCLK_DPM_LEVELS   16
#घोषणा VG12_PSUEDO_NUM_SOCCLK_DPM_LEVELS   8
#घोषणा VG12_PSUEDO_NUM_DCEFCLK_DPM_LEVELS  8
#घोषणा VG12_PSUEDO_NUM_UCLK_DPM_LEVELS     4

क्रमागत
अणु
	GNLD_DPM_PREFETCHER = 0,
	GNLD_DPM_GFXCLK,
	GNLD_DPM_UCLK,
	GNLD_DPM_SOCCLK,
	GNLD_DPM_UVD,
	GNLD_DPM_VCE,
	GNLD_ULV,
	GNLD_DPM_MP0CLK,
	GNLD_DPM_LINK,
	GNLD_DPM_DCEFCLK,
	GNLD_DS_GFXCLK,
	GNLD_DS_SOCCLK,
	GNLD_DS_LCLK,
	GNLD_PPT,
	GNLD_TDC,
	GNLD_THERMAL,
	GNLD_GFX_PER_CU_CG,
	GNLD_RM,
	GNLD_DS_DCEFCLK,
	GNLD_ACDC,
	GNLD_VR0HOT,
	GNLD_VR1HOT,
	GNLD_FW_CTF,
	GNLD_LED_DISPLAY,
	GNLD_FAN_CONTROL,
	GNLD_DIDT,
	GNLD_GFXOFF,
	GNLD_CG,
	GNLD_ACG,

	GNLD_FEATURES_MAX
पूर्ण;


#घोषणा GNLD_DPM_MAX    (GNLD_DPM_DCEFCLK + 1)

#घोषणा SMC_DPM_FEATURES    0x30F

काष्ठा smu_features अणु
	bool supported;
	bool enabled;
	bool allowed;
	uपूर्णांक32_t smu_feature_id;
	uपूर्णांक64_t smu_feature_biपंचांगap;
पूर्ण;

काष्ठा vega12_dpm_level अणु
	bool		enabled;
	uपूर्णांक32_t	value;
	uपूर्णांक32_t	param1;
पूर्ण;

#घोषणा VEGA12_MAX_DEEPSLEEP_DIVIDER_ID 5
#घोषणा MAX_REGULAR_DPM_NUMBER 16
#घोषणा MAX_PCIE_CONF 2
#घोषणा VEGA12_MINIMUM_ENGINE_CLOCK 2500

काष्ठा vega12_dpm_state अणु
	uपूर्णांक32_t  soft_min_level;
	uपूर्णांक32_t  soft_max_level;
	uपूर्णांक32_t  hard_min_level;
	uपूर्णांक32_t  hard_max_level;
पूर्ण;

काष्ठा vega12_single_dpm_table अणु
	uपूर्णांक32_t		count;
	काष्ठा vega12_dpm_state	dpm_state;
	काष्ठा vega12_dpm_level	dpm_levels[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा vega12_odn_dpm_control अणु
	uपूर्णांक32_t	count;
	uपूर्णांक32_t	entries[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा vega12_pcie_table अणु
	uपूर्णांक16_t count;
	uपूर्णांक8_t  pcie_gen[MAX_PCIE_CONF];
	uपूर्णांक8_t  pcie_lane[MAX_PCIE_CONF];
	uपूर्णांक32_t lclk[MAX_PCIE_CONF];
पूर्ण;

काष्ठा vega12_dpm_table अणु
	काष्ठा vega12_single_dpm_table  soc_table;
	काष्ठा vega12_single_dpm_table  gfx_table;
	काष्ठा vega12_single_dpm_table  mem_table;
	काष्ठा vega12_single_dpm_table  eclk_table;
	काष्ठा vega12_single_dpm_table  vclk_table;
	काष्ठा vega12_single_dpm_table  dclk_table;
	काष्ठा vega12_single_dpm_table  dcef_table;
	काष्ठा vega12_single_dpm_table  pixel_table;
	काष्ठा vega12_single_dpm_table  display_table;
	काष्ठा vega12_single_dpm_table  phy_table;
	काष्ठा vega12_pcie_table        pcie_table;
पूर्ण;

#घोषणा VEGA12_MAX_LEAKAGE_COUNT  8
काष्ठा vega12_leakage_voltage अणु
	uपूर्णांक16_t  count;
	uपूर्णांक16_t  leakage_id[VEGA12_MAX_LEAKAGE_COUNT];
	uपूर्णांक16_t  actual_voltage[VEGA12_MAX_LEAKAGE_COUNT];
पूर्ण;

काष्ठा vega12_display_timing अणु
	uपूर्णांक32_t  min_घड़ी_in_sr;
	uपूर्णांक32_t  num_existing_displays;
पूर्ण;

काष्ठा vega12_dpmlevel_enable_mask अणु
	uपूर्णांक32_t  uvd_dpm_enable_mask;
	uपूर्णांक32_t  vce_dpm_enable_mask;
	uपूर्णांक32_t  samu_dpm_enable_mask;
	uपूर्णांक32_t  sclk_dpm_enable_mask;
	uपूर्णांक32_t  mclk_dpm_enable_mask;
पूर्ण;

काष्ठा vega12_vbios_boot_state अणु
	bool        bsoc_vddc_lock;
	uपूर्णांक8_t     uc_cooling_id;
	uपूर्णांक16_t    vddc;
	uपूर्णांक16_t    vddci;
	uपूर्णांक16_t    mvddc;
	uपूर्णांक16_t    vdd_gfx;
	uपूर्णांक32_t    gfx_घड़ी;
	uपूर्णांक32_t    mem_घड़ी;
	uपूर्णांक32_t    soc_घड़ी;
	uपूर्णांक32_t    dcef_घड़ी;
	uपूर्णांक32_t    eघड़ी;
	uपूर्णांक32_t    dघड़ी;
	uपूर्णांक32_t    vघड़ी;
पूर्ण;

#घोषणा DPMTABLE_OD_UPDATE_SCLK     0x00000001
#घोषणा DPMTABLE_OD_UPDATE_MCLK     0x00000002
#घोषणा DPMTABLE_UPDATE_SCLK        0x00000004
#घोषणा DPMTABLE_UPDATE_MCLK        0x00000008
#घोषणा DPMTABLE_OD_UPDATE_VDDC     0x00000010

काष्ठा vega12_smc_state_table अणु
	uपूर्णांक32_t        soc_boot_level;
	uपूर्णांक32_t        gfx_boot_level;
	uपूर्णांक32_t        dcef_boot_level;
	uपूर्णांक32_t        mem_boot_level;
	uपूर्णांक32_t        uvd_boot_level;
	uपूर्णांक32_t        vce_boot_level;
	uपूर्णांक32_t        gfx_max_level;
	uपूर्णांक32_t        mem_max_level;
	uपूर्णांक8_t         vr_hot_gpio;
	uपूर्णांक8_t         ac_dc_gpio;
	uपूर्णांक8_t         therm_out_gpio;
	uपूर्णांक8_t         therm_out_polarity;
	uपूर्णांक8_t         therm_out_mode;
	PPTable_t       pp_table;
	Watermarks_t    water_marks_table;
	AvfsDebugTable_t avfs_debug_table;
	AvfsFuseOverride_t avfs_fuse_override_table;
	SmuMetrics_t    smu_metrics;
	DriverSmuConfig_t driver_smu_config;
	DpmActivityMonitorCoeffInt_t dpm_activity_monitor_coeffपूर्णांक;
	OverDriveTable_t overdrive_table;
पूर्ण;

काष्ठा vega12_mclk_latency_entries अणु
	uपूर्णांक32_t  frequency;
	uपूर्णांक32_t  latency;
पूर्ण;

काष्ठा vega12_mclk_latency_table अणु
	uपूर्णांक32_t  count;
	काष्ठा vega12_mclk_latency_entries  entries[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा vega12_registry_data अणु
	uपूर्णांक64_t  disallowed_features;
	uपूर्णांक8_t   ac_dc_चयन_gpio_support;
	uपूर्णांक8_t   acg_loop_support;
	uपूर्णांक8_t   घड़ी_stretcher_support;
	uपूर्णांक8_t   db_ramping_support;
	uपूर्णांक8_t   didt_mode;
	uपूर्णांक8_t   didt_support;
	uपूर्णांक8_t   edc_didt_support;
	uपूर्णांक8_t   क्रमce_dpm_high;
	uपूर्णांक8_t   fuzzy_fan_control_support;
	uपूर्णांक8_t   mclk_dpm_key_disabled;
	uपूर्णांक8_t   od_state_in_dc_support;
	uपूर्णांक8_t   pcie_lane_override;
	uपूर्णांक8_t   pcie_speed_override;
	uपूर्णांक32_t  pcie_घड़ी_override;
	uपूर्णांक8_t   pcie_dpm_key_disabled;
	uपूर्णांक8_t   dcefclk_dpm_key_disabled;
	uपूर्णांक8_t   prefetcher_dpm_key_disabled;
	uपूर्णांक8_t   quick_transition_support;
	uपूर्णांक8_t   regulator_hot_gpio_support;
	uपूर्णांक8_t   master_deep_sleep_support;
	uपूर्णांक8_t   gfx_clk_deep_sleep_support;
	uपूर्णांक8_t   sclk_deep_sleep_support;
	uपूर्णांक8_t   lclk_deep_sleep_support;
	uपूर्णांक8_t   dce_fclk_deep_sleep_support;
	uपूर्णांक8_t   sclk_dpm_key_disabled;
	uपूर्णांक8_t   sclk_throttle_low_notअगरication;
	uपूर्णांक8_t   skip_baco_hardware;
	uपूर्णांक8_t   socclk_dpm_key_disabled;
	uपूर्णांक8_t   sq_ramping_support;
	uपूर्णांक8_t   tcp_ramping_support;
	uपूर्णांक8_t   td_ramping_support;
	uपूर्णांक8_t   dbr_ramping_support;
	uपूर्णांक8_t   gc_didt_support;
	uपूर्णांक8_t   psm_didt_support;
	uपूर्णांक8_t   thermal_support;
	uपूर्णांक8_t   fw_ctf_enabled;
	uपूर्णांक8_t   led_dpm_enabled;
	uपूर्णांक8_t   fan_control_support;
	uपूर्णांक8_t   ulv_support;
	uपूर्णांक8_t   odn_feature_enable;
	uपूर्णांक8_t   disable_water_mark;
	uपूर्णांक8_t   disable_workload_policy;
	uपूर्णांक32_t  क्रमce_workload_policy_mask;
	uपूर्णांक8_t   disable_3d_fs_detection;
	uपूर्णांक8_t   disable_pp_tuning;
	uपूर्णांक8_t   disable_xlpp_tuning;
	uपूर्णांक32_t  perf_ui_tuning_profile_turbo;
	uपूर्णांक32_t  perf_ui_tuning_profile_घातerSave;
	uपूर्णांक32_t  perf_ui_tuning_profile_xl;
	uपूर्णांक16_t  zrpm_stop_temp;
	uपूर्णांक16_t  zrpm_start_temp;
	uपूर्णांक32_t  stable_pstate_sclk_dpm_percentage;
	uपूर्णांक8_t   fps_support;
	uपूर्णांक8_t   vr0hot;
	uपूर्णांक8_t   vr1hot;
	uपूर्णांक8_t   disable_स्वतः_watपंचांगan;
	uपूर्णांक32_t  स्वतः_watपंचांगan_debug;
	uपूर्णांक32_t  स्वतः_watपंचांगan_sample_period;
	uपूर्णांक8_t   स्वतः_watपंचांगan_threshold;
	uपूर्णांक8_t   log_avfs_param;
	uपूर्णांक8_t   enable_enginess;
	uपूर्णांक8_t   custom_fan_support;
	uपूर्णांक8_t   disable_pcc_limit_control;
पूर्ण;

काष्ठा vega12_odn_घड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_record
		entries[MAX_REGULAR_DPM_NUMBER];
पूर्ण;

काष्ठा vega12_odn_dpm_table अणु
	काष्ठा vega12_odn_dpm_control		control_gfxclk_state;
	काष्ठा vega12_odn_dpm_control		control_memclk_state;
	काष्ठा phm_odn_घड़ी_levels		odn_core_घड़ी_dpm_levels;
	काष्ठा phm_odn_घड़ी_levels		odn_memory_घड़ी_dpm_levels;
	काष्ठा vega12_odn_घड़ी_voltage_dependency_table		vdd_dependency_on_sclk;
	काष्ठा vega12_odn_घड़ी_voltage_dependency_table		vdd_dependency_on_mclk;
	काष्ठा vega12_odn_घड़ी_voltage_dependency_table		vdd_dependency_on_socclk;
	uपूर्णांक32_t				odn_mclk_min_limit;
पूर्ण;

काष्ठा vega12_odn_fan_table अणु
	uपूर्णांक32_t	target_fan_speed;
	uपूर्णांक32_t	target_temperature;
	uपूर्णांक32_t	min_perक्रमmance_घड़ी;
	uपूर्णांक32_t	min_fan_limit;
	bool		क्रमce_fan_pwm;
पूर्ण;

काष्ठा vega12_घड़ी_range अणु
	uपूर्णांक32_t	ACMax;
	uपूर्णांक32_t	ACMin;
	uपूर्णांक32_t	DCMax;
पूर्ण;

काष्ठा vega12_hwmgr अणु
	काष्ठा vega12_dpm_table          dpm_table;
	काष्ठा vega12_dpm_table          golden_dpm_table;
	काष्ठा vega12_registry_data      registry_data;
	काष्ठा vega12_vbios_boot_state   vbios_boot_state;
	काष्ठा vega12_mclk_latency_table mclk_latency_table;

	काष्ठा vega12_leakage_voltage    vddc_leakage;

	uपूर्णांक32_t                           vddc_control;
	काष्ठा pp_atomfwctrl_voltage_table vddc_voltage_table;
	uपूर्णांक32_t                           mvdd_control;
	काष्ठा pp_atomfwctrl_voltage_table mvdd_voltage_table;
	uपूर्णांक32_t                           vddci_control;
	काष्ठा pp_atomfwctrl_voltage_table vddci_voltage_table;

	uपूर्णांक32_t                           active_स्वतः_throttle_sources;
	uपूर्णांक32_t                           water_marks_biपंचांगap;

	काष्ठा vega12_odn_dpm_table       odn_dpm_table;
	काष्ठा vega12_odn_fan_table       odn_fan_table;

	/* ---- General data ---- */
	uपूर्णांक8_t                           need_update_dpm_table;

	bool                           cac_enabled;
	bool                           battery_state;
	bool                           is_tlu_enabled;
	bool                           avfs_exist;

	uपूर्णांक32_t                       low_sclk_पूर्णांकerrupt_threshold;

	uपूर्णांक32_t                       total_active_cus;

	काष्ठा vega12_display_timing display_timing;

	/* ---- Vega12 Dyn Register Settings ---- */

	uपूर्णांक32_t                       debug_settings;
	uपूर्णांक32_t                       lowest_uclk_reserved_क्रम_ulv;
	uपूर्णांक32_t                       gfxclk_average_alpha;
	uपूर्णांक32_t                       socclk_average_alpha;
	uपूर्णांक32_t                       uclk_average_alpha;
	uपूर्णांक32_t                       gfx_activity_average_alpha;
	uपूर्णांक32_t                       display_voltage_mode;
	uपूर्णांक32_t                       dcef_clk_quad_eqn_a;
	uपूर्णांक32_t                       dcef_clk_quad_eqn_b;
	uपूर्णांक32_t                       dcef_clk_quad_eqn_c;
	uपूर्णांक32_t                       disp_clk_quad_eqn_a;
	uपूर्णांक32_t                       disp_clk_quad_eqn_b;
	uपूर्णांक32_t                       disp_clk_quad_eqn_c;
	uपूर्णांक32_t                       pixel_clk_quad_eqn_a;
	uपूर्णांक32_t                       pixel_clk_quad_eqn_b;
	uपूर्णांक32_t                       pixel_clk_quad_eqn_c;
	uपूर्णांक32_t                       phy_clk_quad_eqn_a;
	uपूर्णांक32_t                       phy_clk_quad_eqn_b;
	uपूर्णांक32_t                       phy_clk_quad_eqn_c;

	/* ---- Thermal Temperature Setting ---- */
	काष्ठा vega12_dpmlevel_enable_mask     dpm_level_enable_mask;

	/* ---- Power Gating States ---- */
	bool                           uvd_घातer_gated;
	bool                           vce_घातer_gated;
	bool                           samu_घातer_gated;
	bool                           need_दीर्घ_memory_training;

	/* Internal settings to apply the application घातer optimization parameters */
	bool                           apply_optimized_settings;
	uपूर्णांक32_t                       disable_dpm_mask;

	/* ---- Overdrive next setting ---- */
	uपूर्णांक32_t                       apply_overdrive_next_settings_mask;

	/* ---- Workload Mask ---- */
	uपूर्णांक32_t                       workload_mask;

	/* ---- SMU9 ---- */
	uपूर्णांक32_t                       smu_version;
	काष्ठा smu_features            smu_features[GNLD_FEATURES_MAX];
	काष्ठा vega12_smc_state_table  smc_state_table;

	काष्ठा vega12_घड़ी_range      clk_range[PPCLK_COUNT];

	/* ---- Gfxoff ---- */
	bool                           gfxoff_controlled_by_driver;

	अचिन्हित दीर्घ                  metrics_समय;
	SmuMetrics_t                   metrics_table;
	काष्ठा gpu_metrics_v1_0        gpu_metrics_table;
पूर्ण;

#घोषणा VEGA12_DPM2_NEAR_TDP_DEC                      10
#घोषणा VEGA12_DPM2_ABOVE_SAFE_INC                    5
#घोषणा VEGA12_DPM2_BELOW_SAFE_INC                    20

#घोषणा VEGA12_DPM2_LTA_WINDOW_SIZE                   7

#घोषणा VEGA12_DPM2_LTS_TRUNCATE                      0

#घोषणा VEGA12_DPM2_TDP_SAFE_LIMIT_PERCENT            80

#घोषणा VEGA12_DPM2_MAXPS_PERCENT_M                   90
#घोषणा VEGA12_DPM2_MAXPS_PERCENT_H                   90

#घोषणा VEGA12_DPM2_PWREFFICIENCYRATIO_MARGIN         50

#घोषणा VEGA12_DPM2_SQ_RAMP_MAX_POWER                 0x3FFF
#घोषणा VEGA12_DPM2_SQ_RAMP_MIN_POWER                 0x12
#घोषणा VEGA12_DPM2_SQ_RAMP_MAX_POWER_DELTA           0x15
#घोषणा VEGA12_DPM2_SQ_RAMP_SHORT_TERM_INTERVAL_SIZE  0x1E
#घोषणा VEGA12_DPM2_SQ_RAMP_LONG_TERM_INTERVAL_RATIO  0xF

#घोषणा VEGA12_VOLTAGE_CONTROL_NONE                   0x0
#घोषणा VEGA12_VOLTAGE_CONTROL_BY_GPIO                0x1
#घोषणा VEGA12_VOLTAGE_CONTROL_BY_SVID2               0x2
#घोषणा VEGA12_VOLTAGE_CONTROL_MERGED                 0x3
/* To convert to Q8.8 क्रमmat क्रम firmware */
#घोषणा VEGA12_Q88_FORMAT_CONVERSION_UNIT             256

#घोषणा VEGA12_UNUSED_GPIO_PIN       0x7F

#घोषणा VEGA12_THERM_OUT_MODE_DISABLE       0x0
#घोषणा VEGA12_THERM_OUT_MODE_THERM_ONLY    0x1
#घोषणा VEGA12_THERM_OUT_MODE_THERM_VRHOT   0x2

#घोषणा PPVEGA12_VEGA12DISPLAYVOLTAGEMODE_DFLT   0xffffffff
#घोषणा PPREGKEY_VEGA12QUADRATICEQUATION_DFLT    0xffffffff

#घोषणा PPVEGA12_VEGA12GFXCLKAVERAGEALPHA_DFLT       25 /* 10% * 255 = 25 */
#घोषणा PPVEGA12_VEGA12SOCCLKAVERAGEALPHA_DFLT       25 /* 10% * 255 = 25 */
#घोषणा PPVEGA12_VEGA12UCLKCLKAVERAGEALPHA_DFLT      25 /* 10% * 255 = 25 */
#घोषणा PPVEGA12_VEGA12GFXACTIVITYAVERAGEALPHA_DFLT  25 /* 10% * 255 = 25 */
#घोषणा PPVEGA12_VEGA12LOWESTUCLKRESERVEDFORULV_DFLT   0xffffffff
#घोषणा PPVEGA12_VEGA12DISPLAYVOLTAGEMODE_DFLT         0xffffffff
#घोषणा PPREGKEY_VEGA12QUADRATICEQUATION_DFLT          0xffffffff

#घोषणा VEGA12_UMD_PSTATE_GFXCLK_LEVEL         0x3
#घोषणा VEGA12_UMD_PSTATE_SOCCLK_LEVEL         0x3
#घोषणा VEGA12_UMD_PSTATE_MCLK_LEVEL           0x2
#घोषणा VEGA12_UMD_PSTATE_UVDCLK_LEVEL         0x3
#घोषणा VEGA12_UMD_PSTATE_VCEMCLK_LEVEL        0x3

पूर्णांक vega12_enable_disable_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable);

#पूर्ण_अगर /* _VEGA12_HWMGR_H_ */
