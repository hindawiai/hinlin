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
#अगर_अघोषित __CYPRESS_DPM_H__
#घोषणा __CYPRESS_DPM_H__

#समावेश "rv770_dpm.h"
#समावेश "evergreen_smc.h"

काष्ठा evergreen_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा evergreen_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा evergreen_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMC_Evergreen_MCRegisterAddress mc_reg_address[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा evergreen_ulv_param अणु
	bool supported;
	काष्ठा rv7xx_pl *pl;
पूर्ण;

काष्ठा evergreen_arb_रेजिस्टरs अणु
	u32 mc_arb_dram_timing;
	u32 mc_arb_dram_timing2;
	u32 mc_arb_rfsh_rate;
	u32 mc_arb_burst_समय;
पूर्ण;

काष्ठा at अणु
	u32 rlp;
	u32 rmp;
	u32 lhp;
	u32 lmp;
पूर्ण;

काष्ठा evergreen_घातer_info अणु
	/* must be first! */
	काष्ठा rv7xx_घातer_info rv7xx;
	/* flags */
	bool vddci_control;
	bool dynamic_ac_timing;
	bool abm;
	bool mcls;
	bool light_sleep;
	bool memory_transition;
	bool pcie_perक्रमmance_request;
	bool pcie_perक्रमmance_request_रेजिस्टरed;
	bool sclk_deep_sleep;
	bool dll_शेष_on;
	bool ls_घड़ी_gating;
	bool smu_uvd_hs;
	bool uvd_enabled;
	/* stored values */
	u16 acpi_vddci;
	u8 mvdd_high_index;
	u8 mvdd_low_index;
	u32 mclk_edc_wr_enable_threshold;
	काष्ठा evergreen_mc_reg_table mc_reg_table;
	काष्ठा atom_voltage_table vddc_voltage_table;
	काष्ठा atom_voltage_table vddci_voltage_table;
	काष्ठा evergreen_arb_रेजिस्टरs bootup_arb_रेजिस्टरs;
	काष्ठा evergreen_ulv_param ulv;
	काष्ठा at ats[2];
	/* smc offsets */
	u16 mc_reg_table_start;
	काष्ठा radeon_ps current_rps;
	काष्ठा rv7xx_ps current_ps;
	काष्ठा radeon_ps requested_rps;
	काष्ठा rv7xx_ps requested_ps;
पूर्ण;

#घोषणा CYPRESS_HASI_DFLT                               400000
#घोषणा CYPRESS_MGCGTTLOCAL0_DFLT                       0x00000000
#घोषणा CYPRESS_MGCGTTLOCAL1_DFLT                       0x00000000
#घोषणा CYPRESS_MGCGTTLOCAL2_DFLT                       0x00000000
#घोषणा CYPRESS_MGCGTTLOCAL3_DFLT                       0x00000000
#घोषणा CYPRESS_MGCGCGTSSMCTRL_DFLT                     0x81944bc0
#घोषणा REDWOOD_MGCGCGTSSMCTRL_DFLT                     0x6e944040
#घोषणा CEDAR_MGCGCGTSSMCTRL_DFLT                       0x46944040
#घोषणा CYPRESS_VRC_DFLT                                0xC00033

#घोषणा PCIE_PERF_REQ_REMOVE_REGISTRY   0
#घोषणा PCIE_PERF_REQ_FORCE_LOWPOWER    1
#घोषणा PCIE_PERF_REQ_PECI_GEN1         2
#घोषणा PCIE_PERF_REQ_PECI_GEN2         3
#घोषणा PCIE_PERF_REQ_PECI_GEN3         4

पूर्णांक cypress_convert_घातer_level_to_smc(काष्ठा radeon_device *rdev,
				       काष्ठा rv7xx_pl *pl,
				       RV770_SMC_HW_PERFORMANCE_LEVEL *level,
				       u8 watermark_level);
पूर्णांक cypress_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
				    RV770_SMC_STATETABLE *table);
पूर्णांक cypress_populate_smc_voltage_tables(काष्ठा radeon_device *rdev,
					RV770_SMC_STATETABLE *table);
पूर्णांक cypress_populate_smc_initial_state(काष्ठा radeon_device *rdev,
				       काष्ठा radeon_ps *radeon_initial_state,
				       RV770_SMC_STATETABLE *table);
u32 cypress_calculate_burst_समय(काष्ठा radeon_device *rdev,
				 u32 engine_घड़ी, u32 memory_घड़ी);
व्योम cypress_notअगरy_link_speed_change_beक्रमe_state_change(काष्ठा radeon_device *rdev,
							  काष्ठा radeon_ps *radeon_new_state,
							  काष्ठा radeon_ps *radeon_current_state);
पूर्णांक cypress_upload_sw_state(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ps *radeon_new_state);
पूर्णांक cypress_upload_mc_reg_table(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ps *radeon_new_state);
व्योम cypress_program_memory_timing_parameters(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *radeon_new_state);
व्योम cypress_notअगरy_link_speed_change_after_state_change(काष्ठा radeon_device *rdev,
							 काष्ठा radeon_ps *radeon_new_state,
							 काष्ठा radeon_ps *radeon_current_state);
पूर्णांक cypress_स्थिरruct_voltage_tables(काष्ठा radeon_device *rdev);
पूर्णांक cypress_get_mvdd_configuration(काष्ठा radeon_device *rdev);
व्योम cypress_enable_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
				    bool enable);
व्योम cypress_enable_display_gap(काष्ठा radeon_device *rdev);
पूर्णांक cypress_get_table_locations(काष्ठा radeon_device *rdev);
पूर्णांक cypress_populate_mc_reg_table(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ps *radeon_boot_state);
व्योम cypress_program_response_बार(काष्ठा radeon_device *rdev);
पूर्णांक cypress_notअगरy_smc_display_change(काष्ठा radeon_device *rdev,
				      bool has_display);
व्योम cypress_enable_sclk_control(काष्ठा radeon_device *rdev,
				 bool enable);
व्योम cypress_enable_mclk_control(काष्ठा radeon_device *rdev,
				 bool enable);
व्योम cypress_start_dpm(काष्ठा radeon_device *rdev);
व्योम cypress_advertise_gen2_capability(काष्ठा radeon_device *rdev);
u32 cypress_map_clkf_to_ibias(काष्ठा radeon_device *rdev, u32 clkf);
u8 cypress_get_mclk_frequency_ratio(काष्ठा radeon_device *rdev,
				    u32 memory_घड़ी, bool strobe_mode);
u8 cypress_get_strobe_mode_settings(काष्ठा radeon_device *rdev, u32 mclk);

#पूर्ण_अगर
