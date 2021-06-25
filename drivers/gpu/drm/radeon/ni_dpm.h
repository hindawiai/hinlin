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
#अगर_अघोषित __NI_DPM_H__
#घोषणा __NI_DPM_H__

#समावेश "cypress_dpm.h"
#समावेश "btc_dpm.h"
#समावेश "nislands_smc.h"

काष्ठा ni_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_func_cntl_4;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2;
	u32 mpll_ss1;
	u32 mpll_ss2;
पूर्ण;

काष्ठा ni_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा ni_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा ni_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMC_NIslands_MCRegisterAddress mc_reg_address[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

#घोषणा NISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT 2

क्रमागत ni_dc_cac_level
अणु
	NISLANDS_DCCAC_LEVEL_0 = 0,
	NISLANDS_DCCAC_LEVEL_1,
	NISLANDS_DCCAC_LEVEL_2,
	NISLANDS_DCCAC_LEVEL_3,
	NISLANDS_DCCAC_LEVEL_4,
	NISLANDS_DCCAC_LEVEL_5,
	NISLANDS_DCCAC_LEVEL_6,
	NISLANDS_DCCAC_LEVEL_7,
	NISLANDS_DCCAC_MAX_LEVELS
पूर्ण;

काष्ठा ni_leakage_coeffients
अणु
	u32 at;
	u32 bt;
	u32 av;
	u32 bv;
	s32 t_slope;
	s32 t_पूर्णांकercept;
	u32 t_ref;
पूर्ण;

काष्ठा ni_cac_data
अणु
	काष्ठा ni_leakage_coeffients leakage_coefficients;
	u32 i_leakage;
	s32 leakage_minimum_temperature;
	u32 pwr_स्थिर;
	u32 dc_cac_value;
	u32 bअगर_cac_value;
	u32 lkge_pwr;
	u8 mc_wr_weight;
	u8 mc_rd_weight;
	u8 allow_ovrflw;
	u8 num_win_tdp;
	u8 l2num_win_tdp;
	u8 lts_truncate_n;
पूर्ण;

काष्ठा ni_cac_weights
अणु
	u32 weight_tcp_sig0;
	u32 weight_tcp_sig1;
	u32 weight_ta_sig;
	u32 weight_tcc_en0;
	u32 weight_tcc_en1;
	u32 weight_tcc_en2;
	u32 weight_cb_en0;
	u32 weight_cb_en1;
	u32 weight_cb_en2;
	u32 weight_cb_en3;
	u32 weight_db_sig0;
	u32 weight_db_sig1;
	u32 weight_db_sig2;
	u32 weight_db_sig3;
	u32 weight_sxm_sig0;
	u32 weight_sxm_sig1;
	u32 weight_sxm_sig2;
	u32 weight_sxs_sig0;
	u32 weight_sxs_sig1;
	u32 weight_xbr_0;
	u32 weight_xbr_1;
	u32 weight_xbr_2;
	u32 weight_spi_sig0;
	u32 weight_spi_sig1;
	u32 weight_spi_sig2;
	u32 weight_spi_sig3;
	u32 weight_spi_sig4;
	u32 weight_spi_sig5;
	u32 weight_lds_sig0;
	u32 weight_lds_sig1;
	u32 weight_sc;
	u32 weight_bअगर;
	u32 weight_cp;
	u32 weight_pa_sig0;
	u32 weight_pa_sig1;
	u32 weight_vgt_sig0;
	u32 weight_vgt_sig1;
	u32 weight_vgt_sig2;
	u32 weight_dc_sig0;
	u32 weight_dc_sig1;
	u32 weight_dc_sig2;
	u32 weight_dc_sig3;
	u32 weight_uvd_sig0;
	u32 weight_uvd_sig1;
	u32 weight_spare0;
	u32 weight_spare1;
	u32 weight_sq_vsp;
	u32 weight_sq_vsp0;
	u32 weight_sq_gpr;
	u32 ovr_mode_spare_0;
	u32 ovr_val_spare_0;
	u32 ovr_mode_spare_1;
	u32 ovr_val_spare_1;
	u32 vsp;
	u32 vsp0;
	u32 gpr;
	u8 mc_पढ़ो_weight;
	u8 mc_ग_लिखो_weight;
	u32 tid_cnt;
	u32 tid_unit;
	u32 l2_lta_winकरोw_size;
	u32 lts_truncate;
	u32 dc_cac[NISLANDS_DCCAC_MAX_LEVELS];
	u32 pcie_cac[SMC_NISLANDS_BIF_LUT_NUM_OF_ENTRIES];
	bool enable_घातer_containment_by_शेष;
पूर्ण;

काष्ठा ni_ps अणु
	u16 perक्रमmance_level_count;
	bool dc_compatible;
	काष्ठा rv7xx_pl perक्रमmance_levels[NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
पूर्ण;

काष्ठा ni_घातer_info अणु
	/* must be first! */
	काष्ठा evergreen_घातer_info eg;
	काष्ठा ni_घड़ी_रेजिस्टरs घड़ी_रेजिस्टरs;
	काष्ठा ni_mc_reg_table mc_reg_table;
	u32 mclk_rtt_mode_threshold;
	/* flags */
	bool use_घातer_boost_limit;
	bool support_cac_दीर्घ_term_average;
	bool cac_enabled;
	bool cac_configuration_required;
	bool driver_calculate_cac_leakage;
	bool pc_enabled;
	bool enable_घातer_containment;
	bool enable_cac;
	bool enable_sq_ramping;
	/* smc offsets */
	u16 arb_table_start;
	u16 fan_table_start;
	u16 cac_table_start;
	u16 spll_table_start;
	/* CAC stuff */
	काष्ठा ni_cac_data cac_data;
	u32 dc_cac_table[NISLANDS_DCCAC_MAX_LEVELS];
	स्थिर काष्ठा ni_cac_weights *cac_weights;
	u8 lta_winकरोw_size;
	u8 lts_truncate;
	काष्ठा ni_ps current_ps;
	काष्ठा ni_ps requested_ps;
	/* scratch काष्ठाs */
	SMC_NIslands_MCRegisters smc_mc_reg_table;
	NISLANDS_SMC_STATETABLE smc_statetable;
पूर्ण;

#घोषणा NISLANDS_INITIAL_STATE_ARB_INDEX    0
#घोषणा NISLANDS_ACPI_STATE_ARB_INDEX       1
#घोषणा NISLANDS_ULV_STATE_ARB_INDEX        2
#घोषणा NISLANDS_DRIVER_STATE_ARB_INDEX     3

#घोषणा NISLANDS_DPM2_MAX_PULSE_SKIP        256

#घोषणा NISLANDS_DPM2_NEAR_TDP_DEC          10
#घोषणा NISLANDS_DPM2_ABOVE_SAFE_INC        5
#घोषणा NISLANDS_DPM2_BELOW_SAFE_INC        20

#घोषणा NISLANDS_DPM2_TDP_SAFE_LIMIT_PERCENT            80

#घोषणा NISLANDS_DPM2_MAXPS_PERCENT_H                   90
#घोषणा NISLANDS_DPM2_MAXPS_PERCENT_M                   0

#घोषणा NISLANDS_DPM2_SQ_RAMP_MAX_POWER                 0x3FFF
#घोषणा NISLANDS_DPM2_SQ_RAMP_MIN_POWER                 0x12
#घोषणा NISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA           0x15
#घोषणा NISLANDS_DPM2_SQ_RAMP_STI_SIZE                  0x1E
#घोषणा NISLANDS_DPM2_SQ_RAMP_LTI_RATIO                 0xF

पूर्णांक ni_copy_and_चयन_arb_sets(काष्ठा radeon_device *rdev,
				u32 arb_freq_src, u32 arb_freq_dest);
व्योम ni_update_current_ps(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ps *rps);
व्योम ni_update_requested_ps(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ps *rps);

व्योम ni_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
					   काष्ठा radeon_ps *new_ps,
					   काष्ठा radeon_ps *old_ps);
व्योम ni_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_ps *new_ps,
					  काष्ठा radeon_ps *old_ps);

bool ni_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev);

काष्ठा ni_घातer_info *ni_get_pi(काष्ठा radeon_device *rdev);
काष्ठा ni_ps *ni_get_ps(काष्ठा radeon_ps *rps);

#पूर्ण_अगर
