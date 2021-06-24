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
#अगर_अघोषित __TRINITY_DPM_H__
#घोषणा __TRINITY_DPM_H__

#समावेश "sumo_dpm.h"

#घोषणा TRINITY_SIZखातापूर्ण_DPM_STATE_TABLE (SMU_SCLK_DPM_STATE_1_CNTL_0 - SMU_SCLK_DPM_STATE_0_CNTL_0)

काष्ठा trinity_pl अणु
	u32 sclk;
	u8 vddc_index;
	u8 ds_भागider_index;
	u8 ss_भागider_index;
	u8 allow_gnb_slow;
	u8 क्रमce_nbp_state;
	u8 display_wm;
	u8 vce_wm;
पूर्ण;

#घोषणा TRINITY_POWERSTATE_FLAGS_NBPS_FORCEHIGH  (1 << 0)
#घोषणा TRINITY_POWERSTATE_FLAGS_NBPS_LOCKTOHIGH (1 << 1)
#घोषणा TRINITY_POWERSTATE_FLAGS_NBPS_LOCKTOLOW  (1 << 2)

#घोषणा TRINITY_POWERSTATE_FLAGS_BAPM_DISABLE    (1 << 0)

काष्ठा trinity_ps अणु
	u32 num_levels;
	काष्ठा trinity_pl levels[SUMO_MAX_HARDWARE_POWERLEVELS];

	u32 nbps_flags;
	u32 bapm_flags;

	u8 Dpm0PgNbPsLo;
	u8 Dpm0PgNbPsHi;
	u8 DpmXNbPsLo;
	u8 DpmXNbPsHi;

	u32 vclk_low_भागider;
	u32 vclk_high_भागider;
	u32 dclk_low_भागider;
	u32 dclk_high_भागider;
पूर्ण;

#घोषणा TRINITY_NUM_NBPSTATES   4

काष्ठा trinity_uvd_घड़ी_प्रकारable_entry
अणु
	u32 vclk;
	u32 dclk;
	u8 vclk_did;
	u8 dclk_did;
	u8 rsv[2];
पूर्ण;

काष्ठा trinity_sys_info अणु
	u32 bootup_uma_clk;
	u32 bootup_sclk;
	u32 min_sclk;
	u32 dentist_vco_freq;
	u32 nb_dpm_enable;
	u32 nbp_mclk[TRINITY_NUM_NBPSTATES];
	u32 nbp_nclk[TRINITY_NUM_NBPSTATES];
	u16 nbp_voltage_index[TRINITY_NUM_NBPSTATES];
	u16 bootup_nb_voltage_index;
	u8 htc_पंचांगp_lmt;
	u8 htc_hyst_lmt;
	काष्ठा sumo_sclk_voltage_mapping_table sclk_voltage_mapping_table;
	काष्ठा sumo_vid_mapping_table vid_mapping_table;
	u32 uma_channel_number;
	काष्ठा trinity_uvd_घड़ी_प्रकारable_entry uvd_घड़ी_प्रकारable_entries[4];
पूर्ण;

काष्ठा trinity_घातer_info अणु
	u32 at[SUMO_MAX_HARDWARE_POWERLEVELS];
	u32 dpm_पूर्णांकerval;
	u32 thermal_स्वतः_throttling;
	काष्ठा trinity_sys_info sys_info;
	काष्ठा trinity_pl boot_pl;
	u32 min_sclk_did;
	bool enable_nbps_policy;
	bool voltage_drop_in_dce;
	bool override_dynamic_mgpg;
	bool enable_gfx_घड़ी_gating;
	bool enable_gfx_घातer_gating;
	bool enable_mg_घड़ी_gating;
	bool enable_gfx_dynamic_mgpg;
	bool enable_स्वतः_thermal_throttling;
	bool enable_dpm;
	bool enable_sclk_ds;
	bool enable_bapm;
	bool uvd_dpm;
	काष्ठा radeon_ps current_rps;
	काष्ठा trinity_ps current_ps;
	काष्ठा radeon_ps requested_rps;
	काष्ठा trinity_ps requested_ps;
पूर्ण;

#घोषणा TRINITY_AT_DFLT            30

/* trinity_smc.c */
पूर्णांक trinity_dpm_bapm_enable(काष्ठा radeon_device *rdev, bool enable);
पूर्णांक trinity_dpm_config(काष्ठा radeon_device *rdev, bool enable);
पूर्णांक trinity_uvd_dpm_config(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dpm_क्रमce_state(काष्ठा radeon_device *rdev, u32 n);
पूर्णांक trinity_dpm_n_levels_disabled(काष्ठा radeon_device *rdev, u32 n);
पूर्णांक trinity_dpm_no_क्रमced_level(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dce_enable_voltage_adjusपंचांगent(काष्ठा radeon_device *rdev,
					  bool enable);
पूर्णांक trinity_gfx_dynamic_mgpg_config(काष्ठा radeon_device *rdev);
व्योम trinity_acquire_mutex(काष्ठा radeon_device *rdev);
व्योम trinity_release_mutex(काष्ठा radeon_device *rdev);

#पूर्ण_अगर
