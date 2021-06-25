<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __RV770_DPM_H__
#घोषणा __RV770_DPM_H__

#समावेश "radeon.h"
#समावेश "rv770_smc.h"

काष्ठा rv770_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 mpll_ss1;
	u32 mpll_ss2;
पूर्ण;

काष्ठा rv730_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 mpll_func_cntl;
	u32 mpll_func_cntl2;
	u32 mpll_func_cntl3;
	u32 mpll_ss;
	u32 mpll_ss2;
पूर्ण;

जोड़ r7xx_घड़ी_रेजिस्टरs अणु
	काष्ठा rv770_घड़ी_रेजिस्टरs rv770;
	काष्ठा rv730_घड़ी_रेजिस्टरs rv730;
पूर्ण;

काष्ठा vddc_table_entry अणु
	u16 vddc;
	u8 vddc_index;
	u8 high_smio;
	u32 low_smio;
पूर्ण;

#घोषणा MAX_NO_OF_MVDD_VALUES 2
#घोषणा MAX_NO_VREG_STEPS 32

काष्ठा rv7xx_घातer_info अणु
	/* flags */
	bool mem_gddr5;
	bool pcie_gen2;
	bool dynamic_pcie_gen2;
	bool acpi_pcie_gen2;
	bool boot_in_gen2;
	bool voltage_control; /* vddc */
	bool mvdd_control;
	bool sclk_ss;
	bool mclk_ss;
	bool dynamic_ss;
	bool gfx_घड़ी_gating;
	bool mg_घड़ी_gating;
	bool mgcgtssm;
	bool घातer_gating;
	bool thermal_protection;
	bool display_gap;
	bool dcodt;
	bool ulps;
	/* रेजिस्टरs */
	जोड़ r7xx_घड़ी_रेजिस्टरs clk_regs;
	u32 s0_vid_lower_smio_cntl;
	/* voltage */
	u32 vddc_mask_low;
	u32 mvdd_mask_low;
	u32 mvdd_split_frequency;
	u32 mvdd_low_smio[MAX_NO_OF_MVDD_VALUES];
	u16 max_vddc;
	u16 max_vddc_in_table;
	u16 min_vddc_in_table;
	काष्ठा vddc_table_entry vddc_table[MAX_NO_VREG_STEPS];
	u8 valid_vddc_entries;
	/* dc odt */
	u32 mclk_odt_threshold;
	u8 odt_value_0[2];
	u8 odt_value_1[2];
	/* stored values */
	u32 boot_sclk;
	u16 acpi_vddc;
	u32 ref_भाग;
	u32 active_स्वतः_throttle_sources;
	u32 mclk_stutter_mode_threshold;
	u32 mclk_strobe_mode_threshold;
	u32 mclk_edc_enable_threshold;
	u32 bsp;
	u32 bsu;
	u32 pbsp;
	u32 pbsu;
	u32 dsp;
	u32 psp;
	u32 asi;
	u32 pasi;
	u32 vrc;
	u32 restricted_levels;
	u32 rlp;
	u32 rmp;
	u32 lhp;
	u32 lmp;
	/* smc offsets */
	u16 state_table_start;
	u16 soft_regs_start;
	u16 sram_end;
	/* scratch काष्ठाs */
	RV770_SMC_STATETABLE smc_statetable;
पूर्ण;

काष्ठा rv7xx_pl अणु
	u32 sclk;
	u32 mclk;
	u16 vddc;
	u16 vddci; /* eg+ only */
	u32 flags;
	क्रमागत radeon_pcie_gen pcie_gen; /* si+ only */
पूर्ण;

काष्ठा rv7xx_ps अणु
	काष्ठा rv7xx_pl high;
	काष्ठा rv7xx_pl medium;
	काष्ठा rv7xx_pl low;
	bool dc_compatible;
पूर्ण;

#घोषणा RV770_RLP_DFLT                                10
#घोषणा RV770_RMP_DFLT                                25
#घोषणा RV770_LHP_DFLT                                25
#घोषणा RV770_LMP_DFLT                                10
#घोषणा RV770_VRC_DFLT                                0x003f
#घोषणा RV770_ASI_DFLT                                1000
#घोषणा RV770_HASI_DFLT                               200000
#घोषणा RV770_MGCGTTLOCAL0_DFLT                       0x00100000
#घोषणा RV7XX_MGCGTTLOCAL0_DFLT                       0
#घोषणा RV770_MGCGTTLOCAL1_DFLT                       0xFFFF0000
#घोषणा RV770_MGCGCGTSSMCTRL_DFLT                     0x55940000

#घोषणा MVDD_LOW_INDEX  0
#घोषणा MVDD_HIGH_INDEX 1

#घोषणा MVDD_LOW_VALUE  0
#घोषणा MVDD_HIGH_VALUE 0xffff

#घोषणा RV770_DEFAULT_VCLK_FREQ  53300 /* 10 khz */
#घोषणा RV770_DEFAULT_DCLK_FREQ  40000 /* 10 khz */

/* rv730/rv710 */
पूर्णांक rv730_populate_sclk_value(काष्ठा radeon_device *rdev,
			      u32 engine_घड़ी,
			      RV770_SMC_SCLK_VALUE *sclk);
पूर्णांक rv730_populate_mclk_value(काष्ठा radeon_device *rdev,
			      u32 engine_घड़ी, u32 memory_घड़ी,
			      LPRV7XX_SMC_MCLK_VALUE mclk);
व्योम rv730_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा radeon_device *rdev);
पूर्णांक rv730_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
				  RV770_SMC_STATETABLE *table);
पूर्णांक rv730_populate_smc_initial_state(काष्ठा radeon_device *rdev,
				     काष्ठा radeon_ps *radeon_initial_state,
				     RV770_SMC_STATETABLE *table);
व्योम rv730_program_memory_timing_parameters(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *radeon_state);
व्योम rv730_घातer_gating_enable(काष्ठा radeon_device *rdev,
			       bool enable);
व्योम rv730_start_dpm(काष्ठा radeon_device *rdev);
व्योम rv730_stop_dpm(काष्ठा radeon_device *rdev);
व्योम rv730_program_dcodt(काष्ठा radeon_device *rdev, bool use_dcodt);
व्योम rv730_get_odt_values(काष्ठा radeon_device *rdev);

/* rv740 */
पूर्णांक rv740_populate_sclk_value(काष्ठा radeon_device *rdev, u32 engine_घड़ी,
			      RV770_SMC_SCLK_VALUE *sclk);
पूर्णांक rv740_populate_mclk_value(काष्ठा radeon_device *rdev,
			      u32 engine_घड़ी, u32 memory_घड़ी,
			      RV7XX_SMC_MCLK_VALUE *mclk);
व्योम rv740_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा radeon_device *rdev);
पूर्णांक rv740_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
				  RV770_SMC_STATETABLE *table);
व्योम rv740_enable_mclk_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
				       bool enable);
u8 rv740_get_mclk_frequency_ratio(u32 memory_घड़ी);
u32 rv740_get_dll_speed(bool is_gddr5, u32 memory_घड़ी);
u32 rv740_get_decoded_reference_भागider(u32 encoded_ref);

/* rv770 */
u32 rv770_map_clkf_to_ibias(काष्ठा radeon_device *rdev, u32 clkf);
पूर्णांक rv770_populate_vddc_value(काष्ठा radeon_device *rdev, u16 vddc,
			      RV770_SMC_VOLTAGE_VALUE *voltage);
पूर्णांक rv770_populate_mvdd_value(काष्ठा radeon_device *rdev, u32 mclk,
			      RV770_SMC_VOLTAGE_VALUE *voltage);
u8 rv770_get_seq_value(काष्ठा radeon_device *rdev,
		       काष्ठा rv7xx_pl *pl);
पूर्णांक rv770_populate_initial_mvdd_value(काष्ठा radeon_device *rdev,
				      RV770_SMC_VOLTAGE_VALUE *voltage);
u32 rv770_calculate_memory_refresh_rate(काष्ठा radeon_device *rdev,
					u32 engine_घड़ी);
व्योम rv770_program_response_बार(काष्ठा radeon_device *rdev);
पूर्णांक rv770_populate_smc_sp(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ps *radeon_state,
			  RV770_SMC_SWSTATE *smc_state);
पूर्णांक rv770_populate_smc_t(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ps *radeon_state,
			 RV770_SMC_SWSTATE *smc_state);
व्योम rv770_पढ़ो_voltage_smio_रेजिस्टरs(काष्ठा radeon_device *rdev);
व्योम rv770_get_memory_type(काष्ठा radeon_device *rdev);
व्योम r7xx_start_smc(काष्ठा radeon_device *rdev);
u8 rv770_get_memory_module_index(काष्ठा radeon_device *rdev);
व्योम rv770_get_max_vddc(काष्ठा radeon_device *rdev);
व्योम rv770_get_pcie_gen2_status(काष्ठा radeon_device *rdev);
व्योम rv770_enable_acpi_pm(काष्ठा radeon_device *rdev);
व्योम rv770_restore_cgcg(काष्ठा radeon_device *rdev);
bool rv770_dpm_enabled(काष्ठा radeon_device *rdev);
व्योम rv770_enable_voltage_control(काष्ठा radeon_device *rdev,
				  bool enable);
व्योम rv770_enable_backbias(काष्ठा radeon_device *rdev,
			   bool enable);
व्योम rv770_enable_thermal_protection(काष्ठा radeon_device *rdev,
				     bool enable);
व्योम rv770_enable_स्वतः_throttle_source(काष्ठा radeon_device *rdev,
				       क्रमागत radeon_dpm_स्वतः_throttle_src source,
				       bool enable);
व्योम rv770_setup_bsp(काष्ठा radeon_device *rdev);
व्योम rv770_program_git(काष्ठा radeon_device *rdev);
व्योम rv770_program_tp(काष्ठा radeon_device *rdev);
व्योम rv770_program_tpp(काष्ठा radeon_device *rdev);
व्योम rv770_program_sstp(काष्ठा radeon_device *rdev);
व्योम rv770_program_engine_speed_parameters(काष्ठा radeon_device *rdev);
व्योम rv770_program_vc(काष्ठा radeon_device *rdev);
व्योम rv770_clear_vc(काष्ठा radeon_device *rdev);
पूर्णांक rv770_upload_firmware(काष्ठा radeon_device *rdev);
व्योम rv770_stop_dpm(काष्ठा radeon_device *rdev);
व्योम r7xx_stop_smc(काष्ठा radeon_device *rdev);
व्योम rv770_reset_smio_status(काष्ठा radeon_device *rdev);
पूर्णांक rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(काष्ठा radeon_device *rdev);
पूर्णांक rv770_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level);
पूर्णांक rv770_halt_smc(काष्ठा radeon_device *rdev);
पूर्णांक rv770_resume_smc(काष्ठा radeon_device *rdev);
पूर्णांक rv770_set_sw_state(काष्ठा radeon_device *rdev);
पूर्णांक rv770_set_boot_state(काष्ठा radeon_device *rdev);
पूर्णांक rv7xx_parse_घातer_table(काष्ठा radeon_device *rdev);
व्योम rv770_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *new_ps,
					      काष्ठा radeon_ps *old_ps);
व्योम rv770_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *new_ps,
					     काष्ठा radeon_ps *old_ps);
व्योम rv770_get_engine_memory_ss(काष्ठा radeon_device *rdev);

/* smc */
पूर्णांक rv770_ग_लिखो_smc_soft_रेजिस्टर(काष्ठा radeon_device *rdev,
				  u16 reg_offset, u32 value);

#पूर्ण_अगर
