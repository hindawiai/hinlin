<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __SUMO_DPM_H__
#घोषणा __SUMO_DPM_H__

#समावेश "atom.h"
#समावेश "radeon.h"

#घोषणा SUMO_MAX_HARDWARE_POWERLEVELS 5
#घोषणा SUMO_PM_NUMBER_OF_TC 15

काष्ठा sumo_pl अणु
	u32 sclk;
	u32 vddc_index;
	u32 ds_भागider_index;
	u32 ss_भागider_index;
	u32 allow_gnb_slow;
	u32 sclk_dpm_tdp_limit;
पूर्ण;

/* used क्रम the flags field */
#घोषणा SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE (1 << 0)
#घोषणा SUMO_POWERSTATE_FLAGS_BOOST_STATE       (1 << 1)

काष्ठा sumo_ps अणु
	काष्ठा sumo_pl levels[SUMO_MAX_HARDWARE_POWERLEVELS];
	u32 num_levels;
	/* flags */
	u32 flags;
पूर्ण;

#घोषणा NUMBER_OF_M3ARB_PARAM_SETS 10
#घोषणा SUMO_MAX_NUMBER_VOLTAGES    4

काष्ठा sumo_disp_घड़ी_voltage_mapping_table अणु
	u32 num_max_voltage_levels;
	u32 display_घड़ी_frequency[SUMO_MAX_NUMBER_VOLTAGES];
पूर्ण;

काष्ठा sumo_vid_mapping_entry अणु
	u16 vid_2bit;
	u16 vid_7bit;
पूर्ण;

काष्ठा sumo_vid_mapping_table अणु
	u32 num_entries;
	काष्ठा sumo_vid_mapping_entry entries[SUMO_MAX_NUMBER_VOLTAGES];
पूर्ण;

काष्ठा sumo_sclk_voltage_mapping_entry अणु
	u32 sclk_frequency;
	u16 vid_2bit;
	u16 rsv;
पूर्ण;

काष्ठा sumo_sclk_voltage_mapping_table अणु
	u32 num_max_dpm_entries;
	काष्ठा sumo_sclk_voltage_mapping_entry entries[SUMO_MAX_HARDWARE_POWERLEVELS];
पूर्ण;

काष्ठा sumo_sys_info अणु
	u32 bootup_sclk;
	u32 min_sclk;
	u32 bootup_uma_clk;
	u16 bootup_nb_voltage_index;
	u8 htc_पंचांगp_lmt;
	u8 htc_hyst_lmt;
	काष्ठा sumo_sclk_voltage_mapping_table sclk_voltage_mapping_table;
	काष्ठा sumo_disp_घड़ी_voltage_mapping_table disp_clk_voltage_mapping_table;
	काष्ठा sumo_vid_mapping_table vid_mapping_table;
	u32 csr_m3_arb_cntl_शेष[NUMBER_OF_M3ARB_PARAM_SETS];
	u32 csr_m3_arb_cntl_uvd[NUMBER_OF_M3ARB_PARAM_SETS];
	u32 csr_m3_arb_cntl_fs3d[NUMBER_OF_M3ARB_PARAM_SETS];
	u32 sclk_dpm_boost_margin;
	u32 sclk_dpm_throttle_margin;
	u32 sclk_dpm_tdp_limit_pg;
	u32 gnb_tdp_limit;
	u32 sclk_dpm_tdp_limit_boost;
	u32 boost_sclk;
	u32 boost_vid_2bit;
	bool enable_boost;
पूर्ण;

काष्ठा sumo_घातer_info अणु
	u32 asi;
	u32 pasi;
	u32 bsp;
	u32 bsu;
	u32 pbsp;
	u32 pbsu;
	u32 dsp;
	u32 psp;
	u32 thermal_स्वतः_throttling;
	u32 uvd_m3_arbiter;
	u32 fw_version;
	काष्ठा sumo_sys_info sys_info;
	काष्ठा sumo_pl acpi_pl;
	काष्ठा sumo_pl boot_pl;
	काष्ठा sumo_pl boost_pl;
	bool disable_gfx_घातer_gating_in_uvd;
	bool driver_nbps_policy_disable;
	bool enable_alt_vddnb;
	bool enable_dynamic_m3_arbiter;
	bool enable_gfx_घड़ी_gating;
	bool enable_gfx_घातer_gating;
	bool enable_mg_घड़ी_gating;
	bool enable_sclk_ds;
	bool enable_स्वतः_thermal_throttling;
	bool enable_dynamic_patch_ps;
	bool enable_dpm;
	bool enable_boost;
	काष्ठा radeon_ps current_rps;
	काष्ठा sumo_ps current_ps;
	काष्ठा radeon_ps requested_rps;
	काष्ठा sumo_ps requested_ps;
पूर्ण;

#घोषणा SUMO_UTC_DFLT_00                     0x48
#घोषणा SUMO_UTC_DFLT_01                     0x44
#घोषणा SUMO_UTC_DFLT_02                     0x44
#घोषणा SUMO_UTC_DFLT_03                     0x44
#घोषणा SUMO_UTC_DFLT_04                     0x44
#घोषणा SUMO_UTC_DFLT_05                     0x44
#घोषणा SUMO_UTC_DFLT_06                     0x44
#घोषणा SUMO_UTC_DFLT_07                     0x44
#घोषणा SUMO_UTC_DFLT_08                     0x44
#घोषणा SUMO_UTC_DFLT_09                     0x44
#घोषणा SUMO_UTC_DFLT_10                     0x44
#घोषणा SUMO_UTC_DFLT_11                     0x44
#घोषणा SUMO_UTC_DFLT_12                     0x44
#घोषणा SUMO_UTC_DFLT_13                     0x44
#घोषणा SUMO_UTC_DFLT_14                     0x44

#घोषणा SUMO_DTC_DFLT_00                     0x48
#घोषणा SUMO_DTC_DFLT_01                     0x44
#घोषणा SUMO_DTC_DFLT_02                     0x44
#घोषणा SUMO_DTC_DFLT_03                     0x44
#घोषणा SUMO_DTC_DFLT_04                     0x44
#घोषणा SUMO_DTC_DFLT_05                     0x44
#घोषणा SUMO_DTC_DFLT_06                     0x44
#घोषणा SUMO_DTC_DFLT_07                     0x44
#घोषणा SUMO_DTC_DFLT_08                     0x44
#घोषणा SUMO_DTC_DFLT_09                     0x44
#घोषणा SUMO_DTC_DFLT_10                     0x44
#घोषणा SUMO_DTC_DFLT_11                     0x44
#घोषणा SUMO_DTC_DFLT_12                     0x44
#घोषणा SUMO_DTC_DFLT_13                     0x44
#घोषणा SUMO_DTC_DFLT_14                     0x44

#घोषणा SUMO_AH_DFLT               5

#घोषणा SUMO_R_DFLT0               70
#घोषणा SUMO_R_DFLT1               70
#घोषणा SUMO_R_DFLT2               70
#घोषणा SUMO_R_DFLT3               70
#घोषणा SUMO_R_DFLT4               100

#घोषणा SUMO_L_DFLT0               0
#घोषणा SUMO_L_DFLT1               20
#घोषणा SUMO_L_DFLT2               20
#घोषणा SUMO_L_DFLT3               20
#घोषणा SUMO_L_DFLT4               20
#घोषणा SUMO_VRC_DFLT              0x30033
#घोषणा SUMO_MGCGTTLOCAL0_DFLT     0
#घोषणा SUMO_MGCGTTLOCAL1_DFLT     0
#घोषणा SUMO_GICST_DFLT            19
#घोषणा SUMO_SST_DFLT              8
#घोषणा SUMO_VOLTAGEDROPT_DFLT     1
#घोषणा SUMO_GFXPOWERGATINGT_DFLT  100

/* sumo_dpm.c */
व्योम sumo_gfx_घड़ीgating_initialize(काष्ठा radeon_device *rdev);
व्योम sumo_program_vc(काष्ठा radeon_device *rdev, u32 vrc);
व्योम sumo_clear_vc(काष्ठा radeon_device *rdev);
व्योम sumo_program_sstp(काष्ठा radeon_device *rdev);
व्योम sumo_take_smu_control(काष्ठा radeon_device *rdev, bool enable);
व्योम sumo_स्थिरruct_sclk_voltage_mapping_table(काष्ठा radeon_device *rdev,
					       काष्ठा sumo_sclk_voltage_mapping_table *sclk_voltage_mapping_table,
					       ATOM_AVAILABLE_SCLK_LIST *table);
व्योम sumo_स्थिरruct_vid_mapping_table(काष्ठा radeon_device *rdev,
				      काष्ठा sumo_vid_mapping_table *vid_mapping_table,
				      ATOM_AVAILABLE_SCLK_LIST *table);
u32 sumo_convert_vid2_to_vid7(काष्ठा radeon_device *rdev,
			      काष्ठा sumo_vid_mapping_table *vid_mapping_table,
			      u32 vid_2bit);
u32 sumo_get_sleep_भागider_from_id(u32 id);
u32 sumo_get_sleep_भागider_id_from_घड़ी(काष्ठा radeon_device *rdev,
					 u32 sclk,
					 u32 min_sclk_in_sr);
काष्ठा sumo_घातer_info *sumo_get_pi(काष्ठा radeon_device *rdev);

/* sumo_smc.c */
व्योम sumo_initialize_m3_arb(काष्ठा radeon_device *rdev);
व्योम sumo_smu_pg_init(काष्ठा radeon_device *rdev);
व्योम sumo_set_tdp_limit(काष्ठा radeon_device *rdev, u32 index, u32 tdp_limit);
व्योम sumo_smu_notअगरy_alt_vddnb_change(काष्ठा radeon_device *rdev,
				      bool घातersaving, bool क्रमce_nbps1);
व्योम sumo_boost_state_enable(काष्ठा radeon_device *rdev, bool enable);
व्योम sumo_enable_boost_समयr(काष्ठा radeon_device *rdev);
u32 sumo_get_running_fw_version(काष्ठा radeon_device *rdev);

#पूर्ण_अगर
