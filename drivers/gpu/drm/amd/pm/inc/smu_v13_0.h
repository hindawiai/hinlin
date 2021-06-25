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
 */
#अगर_अघोषित __SMU_V13_0_H__
#घोषणा __SMU_V13_0_H__

#समावेश "amdgpu_smu.h"

#घोषणा SMU13_DRIVER_IF_VERSION_INV 0xFFFFFFFF
#घोषणा SMU13_DRIVER_IF_VERSION_ALDE 0x6

/* MP Apertures */
#घोषणा MP0_Public			0x03800000
#घोषणा MP0_SRAM			0x03900000
#घोषणा MP1_Public			0x03b00000
#घोषणा MP1_SRAM			0x03c00004

/* address block */
#घोषणा smnMP1_FIRMWARE_FLAGS		0x3010024
#घोषणा smnMP0_FW_INTF			0x30101c0
#घोषणा smnMP1_PUB_CTRL			0x3010b14

#घोषणा TEMP_RANGE_MIN			(0)
#घोषणा TEMP_RANGE_MAX			(80 * 1000)

#घोषणा SMU13_TOOL_SIZE			0x19000

#घोषणा MAX_DPM_LEVELS 16
#घोषणा MAX_PCIE_CONF 2

#घोषणा CTF_OFFSET_EDGE			5
#घोषणा CTF_OFFSET_HOTSPOT		5
#घोषणा CTF_OFFSET_MEM			5

अटल स्थिर काष्ठा smu_temperature_range smu13_thermal_policy[] =
अणु
	अणु-273150,  99000, 99000, -273150, 99000, 99000, -273150, 99000, 99000पूर्ण,
	अणु 120000, 120000, 120000, 120000, 120000, 120000, 120000, 120000, 120000पूर्ण,
पूर्ण;

काष्ठा smu_13_0_max_sustainable_घड़ीs अणु
	uपूर्णांक32_t display_घड़ी;
	uपूर्णांक32_t phy_घड़ी;
	uपूर्णांक32_t pixel_घड़ी;
	uपूर्णांक32_t uघड़ी;
	uपूर्णांक32_t dcef_घड़ी;
	uपूर्णांक32_t soc_घड़ी;
पूर्ण;

काष्ठा smu_13_0_dpm_clk_level अणु
	bool				enabled;
	uपूर्णांक32_t			value;
पूर्ण;

काष्ठा smu_13_0_dpm_table अणु
	uपूर्णांक32_t			min;        /* MHz */
	uपूर्णांक32_t			max;        /* MHz */
	uपूर्णांक32_t			count;
	काष्ठा smu_13_0_dpm_clk_level	dpm_levels[MAX_DPM_LEVELS];
पूर्ण;

काष्ठा smu_13_0_pcie_table अणु
	uपूर्णांक8_t  pcie_gen[MAX_PCIE_CONF];
	uपूर्णांक8_t  pcie_lane[MAX_PCIE_CONF];
पूर्ण;

काष्ठा smu_13_0_dpm_tables अणु
	काष्ठा smu_13_0_dpm_table        soc_table;
	काष्ठा smu_13_0_dpm_table        gfx_table;
	काष्ठा smu_13_0_dpm_table        uclk_table;
	काष्ठा smu_13_0_dpm_table        eclk_table;
	काष्ठा smu_13_0_dpm_table        vclk_table;
	काष्ठा smu_13_0_dpm_table        dclk_table;
	काष्ठा smu_13_0_dpm_table        dcef_table;
	काष्ठा smu_13_0_dpm_table        pixel_table;
	काष्ठा smu_13_0_dpm_table        display_table;
	काष्ठा smu_13_0_dpm_table        phy_table;
	काष्ठा smu_13_0_dpm_table        fclk_table;
	काष्ठा smu_13_0_pcie_table       pcie_table;
पूर्ण;

काष्ठा smu_13_0_dpm_context अणु
	काष्ठा smu_13_0_dpm_tables  dpm_tables;
	uपूर्णांक32_t                    workload_policy_mask;
	uपूर्णांक32_t                    dcef_min_ds_clk;
पूर्ण;

क्रमागत smu_13_0_घातer_state अणु
	SMU_13_0_POWER_STATE__D0 = 0,
	SMU_13_0_POWER_STATE__D1,
	SMU_13_0_POWER_STATE__D3, /* Sleep*/
	SMU_13_0_POWER_STATE__D4, /* Hibernate*/
	SMU_13_0_POWER_STATE__D5, /* Power off*/
पूर्ण;

काष्ठा smu_13_0_घातer_context अणु
	uपूर्णांक32_t	घातer_source;
	uपूर्णांक8_t		in_घातer_limit_boost_mode;
	क्रमागत smu_13_0_घातer_state घातer_state;
पूर्ण;

क्रमागत smu_v13_0_baco_seq अणु
	BACO_SEQ_BACO = 0,
	BACO_SEQ_MSR,
	BACO_SEQ_BAMACO,
	BACO_SEQ_ULPS,
	BACO_SEQ_COUNT,
पूर्ण;

#अगर defined(SWSMU_CODE_LAYER_L2) || defined(SWSMU_CODE_LAYER_L3)

पूर्णांक smu_v13_0_init_microcode(काष्ठा smu_context *smu);

व्योम smu_v13_0_fini_microcode(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_load_microcode(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_init_smc_tables(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_fini_smc_tables(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_init_घातer(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_fini_घातer(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_check_fw_status(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_setup_pptable(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_vbios_bootup_values(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_check_fw_version(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_set_driver_table_location(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_set_tool_table_location(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_notअगरy_memory_pool_location(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_प्रणाली_features_control(काष्ठा smu_context *smu,
				      bool en);

पूर्णांक smu_v13_0_init_display_count(काष्ठा smu_context *smu, uपूर्णांक32_t count);

पूर्णांक smu_v13_0_set_allowed_mask(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_notअगरy_display_change(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_current_घातer_limit(काष्ठा smu_context *smu,
				      uपूर्णांक32_t *घातer_limit);

पूर्णांक smu_v13_0_set_घातer_limit(काष्ठा smu_context *smu, uपूर्णांक32_t n);

पूर्णांक smu_v13_0_init_max_sustainable_घड़ीs(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_enable_thermal_alert(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_disable_thermal_alert(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_gfx_vdd(काष्ठा smu_context *smu, uपूर्णांक32_t *value);

पूर्णांक smu_v13_0_set_min_deep_sleep_dcefclk(काष्ठा smu_context *smu, uपूर्णांक32_t clk);

पूर्णांक
smu_v13_0_display_घड़ी_voltage_request(काष्ठा smu_context *smu,
					काष्ठा pp_display_घड़ी_request
					*घड़ी_req);

uपूर्णांक32_t
smu_v13_0_get_fan_control_mode(काष्ठा smu_context *smu);

पूर्णांक
smu_v13_0_set_fan_control_mode(काष्ठा smu_context *smu,
			       uपूर्णांक32_t mode);

पूर्णांक
smu_v13_0_set_fan_speed_percent(काष्ठा smu_context *smu, uपूर्णांक32_t speed);

पूर्णांक smu_v13_0_set_fan_speed_rpm(काष्ठा smu_context *smu,
				uपूर्णांक32_t speed);

पूर्णांक smu_v13_0_set_xgmi_pstate(काष्ठा smu_context *smu,
			      uपूर्णांक32_t pstate);

पूर्णांक smu_v13_0_gfx_off_control(काष्ठा smu_context *smu, bool enable);

पूर्णांक smu_v13_0_रेजिस्टर_irq_handler(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_set_azalia_d3_pme(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_max_sustainable_घड़ीs_by_dc(काष्ठा smu_context *smu,
					       काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs);

bool smu_v13_0_baco_is_support(काष्ठा smu_context *smu);

क्रमागत smu_baco_state smu_v13_0_baco_get_state(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_baco_set_state(काष्ठा smu_context *smu, क्रमागत smu_baco_state state);

पूर्णांक smu_v13_0_baco_enter(काष्ठा smu_context *smu);
पूर्णांक smu_v13_0_baco_निकास(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_mode1_reset(काष्ठा smu_context *smu);
पूर्णांक smu_v13_0_mode2_reset(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_dpm_ultimate_freq(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
				    uपूर्णांक32_t *min, uपूर्णांक32_t *max);

पूर्णांक smu_v13_0_set_soft_freq_limited_range(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
					  uपूर्णांक32_t min, uपूर्णांक32_t max);

पूर्णांक smu_v13_0_set_hard_freq_limited_range(काष्ठा smu_context *smu,
					  क्रमागत smu_clk_type clk_type,
					  uपूर्णांक32_t min,
					  uपूर्णांक32_t max);

पूर्णांक smu_v13_0_set_perक्रमmance_level(काष्ठा smu_context *smu,
				    क्रमागत amd_dpm_क्रमced_level level);

पूर्णांक smu_v13_0_set_घातer_source(काष्ठा smu_context *smu,
			       क्रमागत smu_घातer_src_type घातer_src);

पूर्णांक smu_v13_0_get_dpm_freq_by_index(काष्ठा smu_context *smu,
				    क्रमागत smu_clk_type clk_type,
				    uपूर्णांक16_t level,
				    uपूर्णांक32_t *value);

पूर्णांक smu_v13_0_get_dpm_level_count(काष्ठा smu_context *smu,
				  क्रमागत smu_clk_type clk_type,
				  uपूर्णांक32_t *value);

पूर्णांक smu_v13_0_set_single_dpm_table(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type,
				   काष्ठा smu_13_0_dpm_table *single_dpm_table);

पूर्णांक smu_v13_0_get_dpm_level_range(काष्ठा smu_context *smu,
				  क्रमागत smu_clk_type clk_type,
				  uपूर्णांक32_t *min_value,
				  uपूर्णांक32_t *max_value);

पूर्णांक smu_v13_0_get_current_pcie_link_width_level(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_current_pcie_link_width(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_current_pcie_link_speed_level(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_get_current_pcie_link_speed(काष्ठा smu_context *smu);

पूर्णांक smu_v13_0_gfx_ulv_control(काष्ठा smu_context *smu,
			      bool enablement);

पूर्णांक smu_v13_0_रुको_क्रम_event(काष्ठा smu_context *smu, क्रमागत smu_event_type event,
			     uपूर्णांक64_t event_arg);

#पूर्ण_अगर
#पूर्ण_अगर
