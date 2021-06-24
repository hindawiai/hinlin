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

#अगर_अघोषित _SMU8_HWMGR_H_
#घोषणा _SMU8_HWMGR_H_

#समावेश "cgs_common.h"
#समावेश "ppatomctrl.h"

#घोषणा SMU8_NUM_NBPSTATES               4
#घोषणा SMU8_NUM_NBPMEMORYCLOCK          2
#घोषणा MAX_DISPLAY_CLOCK_LEVEL        8
#घोषणा SMU8_MAX_HARDWARE_POWERLEVELS    8
#घोषणा SMU8_VOTINGRIGHTSCLIENTS_DFLT0   0x3FFFC102
#घोषणा SMU8_MIN_DEEP_SLEEP_SCLK         800

/* Carrizo device IDs */
#घोषणा DEVICE_ID_CZ_9870             0x9870
#घोषणा DEVICE_ID_CZ_9874             0x9874
#घोषणा DEVICE_ID_CZ_9875             0x9875
#घोषणा DEVICE_ID_CZ_9876             0x9876
#घोषणा DEVICE_ID_CZ_9877             0x9877

काष्ठा smu8_dpm_entry अणु
	uपूर्णांक32_t soft_min_clk;
	uपूर्णांक32_t hard_min_clk;
	uपूर्णांक32_t soft_max_clk;
	uपूर्णांक32_t hard_max_clk;
पूर्ण;

काष्ठा smu8_sys_info अणु
	uपूर्णांक32_t bootup_uma_घड़ी;
	uपूर्णांक32_t bootup_engine_घड़ी;
	uपूर्णांक32_t dentist_vco_freq;
	uपूर्णांक32_t nb_dpm_enable;
	uपूर्णांक32_t nbp_memory_घड़ी[SMU8_NUM_NBPMEMORYCLOCK];
	uपूर्णांक32_t nbp_n_घड़ी[SMU8_NUM_NBPSTATES];
	uपूर्णांक16_t nbp_voltage_index[SMU8_NUM_NBPSTATES];
	uपूर्णांक32_t display_घड़ी[MAX_DISPLAY_CLOCK_LEVEL];
	uपूर्णांक16_t bootup_nb_voltage_index;
	uपूर्णांक8_t htc_पंचांगp_lmt;
	uपूर्णांक8_t htc_hyst_lmt;
	uपूर्णांक32_t प्रणाली_config;
	uपूर्णांक32_t uma_channel_number;
पूर्ण;

#घोषणा MAX_DISPLAYPHY_IDS			0x8
#घोषणा DISPLAYPHY_LANEMASK			0xF
#घोषणा UNKNOWN_TRANSMITTER_PHY_ID		(-1)

#घोषणा DISPLAYPHY_PHYID_SHIFT			24
#घोषणा DISPLAYPHY_LANESELECT_SHIFT		16

#घोषणा DISPLAYPHY_RX_SELECT			0x1
#घोषणा DISPLAYPHY_TX_SELECT			0x2
#घोषणा DISPLAYPHY_CORE_SELECT			0x4

#घोषणा DDI_POWERGATING_ARG(phyID, lanemask, rx, tx, core) \
		(((uपूर्णांक32_t)(phyID))<<DISPLAYPHY_PHYID_SHIFT | \
		((uपूर्णांक32_t)(lanemask))<<DISPLAYPHY_LANESELECT_SHIFT | \
		((rx) ? DISPLAYPHY_RX_SELECT : 0) | \
		((tx) ? DISPLAYPHY_TX_SELECT : 0) | \
		((core) ? DISPLAYPHY_CORE_SELECT : 0))

काष्ठा smu8_display_phy_info_entry अणु
	uपूर्णांक8_t phy_present;
	uपूर्णांक8_t active_lane_mapping;
	uपूर्णांक8_t display_config_type;
	uपूर्णांक8_t active_number_of_lanes;
पूर्ण;

#घोषणा SMU8_MAX_DISPLAYPHY_IDS			10

काष्ठा smu8_display_phy_info अणु
	bool display_phy_access_initialized;
	काष्ठा smu8_display_phy_info_entry entries[SMU8_MAX_DISPLAYPHY_IDS];
पूर्ण;

काष्ठा smu8_घातer_level अणु
	uपूर्णांक32_t engineClock;
	uपूर्णांक8_t vddcIndex;
	uपूर्णांक8_t dsDividerIndex;
	uपूर्णांक8_t ssDividerIndex;
	uपूर्णांक8_t allowGnbSlow;
	uपूर्णांक8_t क्रमceNBPstate;
	uपूर्णांक8_t display_wm;
	uपूर्णांक8_t vce_wm;
	uपूर्णांक8_t numSIMDToPowerDown;
	uपूर्णांक8_t hysteresis_up;
	uपूर्णांक8_t rsv[3];
पूर्ण;

काष्ठा smu8_uvd_घड़ीs अणु
	uपूर्णांक32_t vclk;
	uपूर्णांक32_t dclk;
	uपूर्णांक32_t vclk_low_भागider;
	uपूर्णांक32_t vclk_high_भागider;
	uपूर्णांक32_t dclk_low_भागider;
	uपूर्णांक32_t dclk_high_भागider;
पूर्ण;

क्रमागत smu8_pstate_previous_action अणु
	DO_NOTHING = 1,
	FORCE_HIGH,
	CANCEL_FORCE_HIGH
पूर्ण;

काष्ठा pp_disable_nb_ps_flags अणु
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

काष्ठा smu8_घातer_state अणु
	अचिन्हित पूर्णांक magic;
	uपूर्णांक32_t level;
	काष्ठा smu8_uvd_घड़ीs uvd_घड़ीs;
	uपूर्णांक32_t evclk;
	uपूर्णांक32_t ecclk;
	uपूर्णांक32_t samclk;
	uपूर्णांक32_t acpclk;
	bool need_dfs_bypass;
	uपूर्णांक32_t nbps_flags;
	uपूर्णांक32_t bapm_flags;
	uपूर्णांक8_t dpm_0_pg_nb_ps_low;
	uपूर्णांक8_t dpm_0_pg_nb_ps_high;
	uपूर्णांक8_t dpm_x_nb_ps_low;
	uपूर्णांक8_t dpm_x_nb_ps_high;
	क्रमागत smu8_pstate_previous_action action;
	काष्ठा smu8_घातer_level levels[SMU8_MAX_HARDWARE_POWERLEVELS];
	काष्ठा pp_disable_nb_ps_flags disable_nb_ps_flag;
पूर्ण;

#घोषणा DPMFlags_SCLK_Enabled			0x00000001
#घोषणा DPMFlags_UVD_Enabled			0x00000002
#घोषणा DPMFlags_VCE_Enabled			0x00000004
#घोषणा DPMFlags_ACP_Enabled			0x00000008
#घोषणा DPMFlags_ForceHighestValid		0x40000000
#घोषणा DPMFlags_Debug				0x80000000

#घोषणा SMU_EnabledFeatureScoreboard_AcpDpmOn   0x00000001 /* bit 0 */
#घोषणा SMU_EnabledFeatureScoreboard_UvdDpmOn   0x00800000 /* bit 23 */
#घोषणा SMU_EnabledFeatureScoreboard_VceDpmOn   0x01000000 /* bit 24 */

काष्ठा cc6_settings अणु
	bool cc6_setting_changed;
	bool nb_pstate_चयन_disable;/* controls NB PState चयन */
	bool cpu_cc6_disable; /* controls CPU CState चयन ( on or off) */
	bool cpu_pstate_disable;
	uपूर्णांक32_t cpu_pstate_separation_समय;
पूर्ण;

काष्ठा smu8_hwmgr अणु
	uपूर्णांक32_t dpm_पूर्णांकerval;

	uपूर्णांक32_t voltage_drop_threshold;

	uपूर्णांक32_t voting_rights_clients;

	uपूर्णांक32_t disable_driver_thermal_policy;

	uपूर्णांक32_t अटल_screen_threshold;

	uपूर्णांक32_t gfx_घातer_gating_threshold;

	uपूर्णांक32_t activity_hysteresis;
	uपूर्णांक32_t bootup_sclk_भागider;
	uपूर्णांक32_t gfx_ramp_step;
	uपूर्णांक32_t gfx_ramp_delay; /* in micro-seconds */

	uपूर्णांक32_t thermal_स्वतः_throttling_treshold;

	काष्ठा smu8_sys_info sys_info;

	काष्ठा smu8_घातer_level boot_घातer_level;
	काष्ठा smu8_घातer_state *smu8_current_ps;
	काष्ठा smu8_घातer_state *smu8_requested_ps;

	uपूर्णांक32_t mgcg_cgtt_local0;
	uपूर्णांक32_t mgcg_cgtt_local1;

	uपूर्णांक32_t tdr_घड़ी; /* in 10khz unit */

	uपूर्णांक32_t ddi_घातer_gating_disabled;
	uपूर्णांक32_t disable_gfx_घातer_gating_in_uvd;
	uपूर्णांक32_t disable_nb_ps3_in_battery;

	uपूर्णांक32_t lock_nb_ps_in_uvd_play_back;

	काष्ठा smu8_display_phy_info display_phy_info;
	uपूर्णांक32_t vce_slow_sclk_threshold; /* शेष 200mhz */
	uपूर्णांक32_t dce_slow_sclk_threshold; /* शेष 300mhz */
	uपूर्णांक32_t min_sclk_did;  /* minimum sclk भागider */

	bool disp_clk_bypass;
	bool disp_clk_bypass_pending;
	uपूर्णांक32_t bapm_enabled;
	uपूर्णांक32_t घड़ी_slow_करोwn_freq;
	uपूर्णांक32_t skip_घड़ी_slow_करोwn;
	uपूर्णांक32_t enable_nb_ps_policy;
	uपूर्णांक32_t voltage_drop_in_dce_घातer_gating;
	uपूर्णांक32_t uvd_dpm_पूर्णांकerval;
	uपूर्णांक32_t override_dynamic_mgpg;
	uपूर्णांक32_t lclk_deep_enabled;

	uपूर्णांक32_t uvd_perक्रमmance;

	bool video_start;
	bool battery_state;
	uपूर्णांक32_t lowest_valid;
	uपूर्णांक32_t highest_valid;
	uपूर्णांक32_t high_voltage_threshold;
	uपूर्णांक32_t is_nb_dpm_enabled;
	काष्ठा cc6_settings cc6_settings;
	uपूर्णांक32_t is_voltage_island_enabled;

	bool pgacpinit;

	uपूर्णांक8_t disp_config;

	/* PowerTune */
	uपूर्णांक32_t घातer_containment_features;
	bool cac_enabled;
	bool disable_uvd_घातer_tune_feature;
	bool enable_ba_pm_feature;
	bool enable_tdc_limit_feature;

	uपूर्णांक32_t sram_end;
	uपूर्णांक32_t dpm_table_start;
	uपूर्णांक32_t soft_regs_start;

	uपूर्णांक8_t uvd_level_count;
	uपूर्णांक8_t vce_level_count;

	uपूर्णांक8_t acp_level_count;
	uपूर्णांक8_t samu_level_count;
	uपूर्णांक32_t fps_high_threshold;
	uपूर्णांक32_t fps_low_threshold;

	uपूर्णांक32_t dpm_flags;
	काष्ठा smu8_dpm_entry sclk_dpm;
	काष्ठा smu8_dpm_entry uvd_dpm;
	काष्ठा smu8_dpm_entry vce_dpm;
	काष्ठा smu8_dpm_entry acp_dpm;

	uपूर्णांक8_t uvd_boot_level;
	uपूर्णांक8_t vce_boot_level;
	uपूर्णांक8_t acp_boot_level;
	uपूर्णांक8_t samu_boot_level;
	uपूर्णांक8_t uvd_पूर्णांकerval;
	uपूर्णांक8_t vce_पूर्णांकerval;
	uपूर्णांक8_t acp_पूर्णांकerval;
	uपूर्णांक8_t samu_पूर्णांकerval;

	uपूर्णांक8_t graphics_पूर्णांकerval;
	uपूर्णांक8_t graphics_therm_throttle_enable;
	uपूर्णांक8_t graphics_voltage_change_enable;

	uपूर्णांक8_t graphics_clk_slow_enable;
	uपूर्णांक8_t graphics_clk_slow_भागider;

	uपूर्णांक32_t display_cac;
	uपूर्णांक32_t low_sclk_पूर्णांकerrupt_threshold;

	uपूर्णांक32_t dram_log_addr_h;
	uपूर्णांक32_t dram_log_addr_l;
	uपूर्णांक32_t dram_log_phy_addr_h;
	uपूर्णांक32_t dram_log_phy_addr_l;
	uपूर्णांक32_t dram_log_buff_size;

	bool uvd_घातer_gated;
	bool vce_घातer_gated;
	bool samu_घातer_gated;
	bool acp_घातer_gated;
	bool acp_घातer_up_no_dsp;
	uपूर्णांक32_t active_process_mask;

	uपूर्णांक32_t max_sclk_level;
	uपूर्णांक32_t num_of_clk_entries;
पूर्ण;

#पूर्ण_अगर /* _SMU8_HWMGR_H_ */
