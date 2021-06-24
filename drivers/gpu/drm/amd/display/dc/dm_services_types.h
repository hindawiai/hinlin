<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DM_SERVICES_TYPES_H__
#घोषणा __DM_SERVICES_TYPES_H__

#समावेश "os_types.h"
#समावेश "dc_types.h"

काष्ठा pp_smu_funcs;

काष्ठा dm_pp_घड़ी_range अणु
	पूर्णांक min_khz;
	पूर्णांक max_khz;
पूर्ण;

क्रमागत dm_pp_घड़ीs_state अणु
	DM_PP_CLOCKS_STATE_INVALID,
	DM_PP_CLOCKS_STATE_ULTRA_LOW,
	DM_PP_CLOCKS_STATE_LOW,
	DM_PP_CLOCKS_STATE_NOMINAL,
	DM_PP_CLOCKS_STATE_PERFORMANCE,

	/* Starting from DCE11, Max 8 levels of DPM state supported. */
	DM_PP_CLOCKS_DPM_STATE_LEVEL_INVALID = DM_PP_CLOCKS_STATE_INVALID,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_0,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_1,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_2,
	/* to be backward compatible */
	DM_PP_CLOCKS_DPM_STATE_LEVEL_3,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_4,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_5,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_6,
	DM_PP_CLOCKS_DPM_STATE_LEVEL_7,

	DM_PP_CLOCKS_MAX_STATES
पूर्ण;

काष्ठा dm_pp_gpu_घड़ी_range अणु
	क्रमागत dm_pp_घड़ीs_state घड़ी_state;
	काष्ठा dm_pp_घड़ी_range sclk;
	काष्ठा dm_pp_घड़ी_range mclk;
	काष्ठा dm_pp_घड़ी_range eclk;
	काष्ठा dm_pp_घड़ी_range dclk;
पूर्ण;

क्रमागत dm_pp_घड़ी_प्रकारype अणु
	DM_PP_CLOCK_TYPE_DISPLAY_CLK = 1,
	DM_PP_CLOCK_TYPE_ENGINE_CLK, /* System घड़ी */
	DM_PP_CLOCK_TYPE_MEMORY_CLK,
	DM_PP_CLOCK_TYPE_DCFCLK,
	DM_PP_CLOCK_TYPE_DCEFCLK,
	DM_PP_CLOCK_TYPE_SOCCLK,
	DM_PP_CLOCK_TYPE_PIXELCLK,
	DM_PP_CLOCK_TYPE_DISPLAYPHYCLK,
	DM_PP_CLOCK_TYPE_DPPCLK,
	DM_PP_CLOCK_TYPE_FCLK,
पूर्ण;

#घोषणा DC_DECODE_PP_CLOCK_TYPE(clk_type) \
	(clk_type) == DM_PP_CLOCK_TYPE_DISPLAY_CLK ? "Display" : \
	(clk_type) == DM_PP_CLOCK_TYPE_ENGINE_CLK ? "Engine" : \
	(clk_type) == DM_PP_CLOCK_TYPE_MEMORY_CLK ? "Memory" : \
	(clk_type) == DM_PP_CLOCK_TYPE_DCFCLK ? "DCF" : \
	(clk_type) == DM_PP_CLOCK_TYPE_DCEFCLK ? "DCEF" : \
	(clk_type) == DM_PP_CLOCK_TYPE_SOCCLK ? "SoC" : \
	(clk_type) == DM_PP_CLOCK_TYPE_PIXELCLK ? "Pixel" : \
	(clk_type) == DM_PP_CLOCK_TYPE_DISPLAYPHYCLK ? "Display PHY" : \
	(clk_type) == DM_PP_CLOCK_TYPE_DPPCLK ? "DPP" : \
	(clk_type) == DM_PP_CLOCK_TYPE_FCLK ? "F" : \
	"Invalid"

#घोषणा DM_PP_MAX_CLOCK_LEVELS 16

काष्ठा dm_pp_घड़ी_levels अणु
	uपूर्णांक32_t num_levels;
	uपूर्णांक32_t घड़ीs_in_khz[DM_PP_MAX_CLOCK_LEVELS];
पूर्ण;

काष्ठा dm_pp_घड़ी_with_latency अणु
	uपूर्णांक32_t घड़ीs_in_khz;
	uपूर्णांक32_t latency_in_us;
पूर्ण;

काष्ठा dm_pp_घड़ी_levels_with_latency अणु
	uपूर्णांक32_t num_levels;
	काष्ठा dm_pp_घड़ी_with_latency data[DM_PP_MAX_CLOCK_LEVELS];
पूर्ण;

काष्ठा dm_pp_घड़ी_with_voltage अणु
	uपूर्णांक32_t घड़ीs_in_khz;
	uपूर्णांक32_t voltage_in_mv;
पूर्ण;

काष्ठा dm_pp_घड़ी_levels_with_voltage अणु
	uपूर्णांक32_t num_levels;
	काष्ठा dm_pp_घड़ी_with_voltage data[DM_PP_MAX_CLOCK_LEVELS];
पूर्ण;

काष्ठा dm_pp_single_disp_config अणु
	क्रमागत संकेत_type संकेत;
	uपूर्णांक8_t transmitter;
	uपूर्णांक8_t ddi_channel_mapping;
	uपूर्णांक8_t pipe_idx;
	uपूर्णांक32_t src_height;
	uपूर्णांक32_t src_width;
	uपूर्णांक32_t v_refresh;
	uपूर्णांक32_t sym_घड़ी; /* HDMI only */
	काष्ठा dc_link_settings link_settings; /* DP only */
पूर्ण;

#घोषणा MAX_WM_SETS 4

क्रमागत dm_pp_wm_set_id अणु
	WM_SET_A = 0,
	WM_SET_B,
	WM_SET_C,
	WM_SET_D,
	WM_SET_INVALID = 0xffff,
पूर्ण;

काष्ठा dm_pp_घड़ी_range_क्रम_wm_set अणु
	क्रमागत dm_pp_wm_set_id wm_set_id;
	uपूर्णांक32_t wm_min_eng_clk_in_khz;
	uपूर्णांक32_t wm_max_eng_clk_in_khz;
	uपूर्णांक32_t wm_min_mem_clk_in_khz;
	uपूर्णांक32_t wm_max_mem_clk_in_khz;
पूर्ण;

काष्ठा dm_pp_wm_sets_with_घड़ी_ranges अणु
	uपूर्णांक32_t num_wm_sets;
	काष्ठा dm_pp_घड़ी_range_क्रम_wm_set wm_clk_ranges[MAX_WM_SETS];
पूर्ण;

काष्ठा dm_pp_घड़ी_range_क्रम_dmअगर_wm_set_soc15 अणु
	क्रमागत dm_pp_wm_set_id wm_set_id;
	uपूर्णांक32_t wm_min_dcfclk_clk_in_khz;
	uपूर्णांक32_t wm_max_dcfclk_clk_in_khz;
	uपूर्णांक32_t wm_min_mem_clk_in_khz;
	uपूर्णांक32_t wm_max_mem_clk_in_khz;
पूर्ण;

काष्ठा dm_pp_घड़ी_range_क्रम_mcअगर_wm_set_soc15 अणु
	क्रमागत dm_pp_wm_set_id wm_set_id;
	uपूर्णांक32_t wm_min_socclk_clk_in_khz;
	uपूर्णांक32_t wm_max_socclk_clk_in_khz;
	uपूर्णांक32_t wm_min_mem_clk_in_khz;
	uपूर्णांक32_t wm_max_mem_clk_in_khz;
पूर्ण;

काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 अणु
	uपूर्णांक32_t num_wm_dmअगर_sets;
	uपूर्णांक32_t num_wm_mcअगर_sets;
	काष्ठा dm_pp_घड़ी_range_क्रम_dmअगर_wm_set_soc15
		wm_dmअगर_घड़ीs_ranges[MAX_WM_SETS];
	काष्ठा dm_pp_घड़ी_range_क्रम_mcअगर_wm_set_soc15
		wm_mcअगर_घड़ीs_ranges[MAX_WM_SETS];
पूर्ण;

#घोषणा MAX_DISPLAY_CONFIGS 6

काष्ठा dm_pp_display_configuration अणु
	bool nb_pstate_चयन_disable;/* controls NB PState चयन */
	bool cpu_cc6_disable; /* controls CPU CState चयन ( on or off) */
	bool cpu_pstate_disable;
	uपूर्णांक32_t cpu_pstate_separation_समय;

	uपूर्णांक32_t min_memory_घड़ी_khz;
	uपूर्णांक32_t min_engine_घड़ी_khz;
	uपूर्णांक32_t min_engine_घड़ी_deep_sleep_khz;

	uपूर्णांक32_t avail_mclk_चयन_समय_us;
	uपूर्णांक32_t avail_mclk_चयन_समय_in_disp_active_us;
	uपूर्णांक32_t min_dcfघड़ी_khz;
	uपूर्णांक32_t min_dcfc_deep_sleep_घड़ी_khz;

	uपूर्णांक32_t disp_clk_khz;

	bool all_displays_in_sync;

	uपूर्णांक8_t display_count;
	काष्ठा dm_pp_single_disp_config disp_configs[MAX_DISPLAY_CONFIGS];

	/*Controller Index of primary display - used in MCLK SMC चयनing hang
	 * SW Workaround*/
	uपूर्णांक8_t crtc_index;
	/*htotal*1000/pixelclk - used in MCLK SMC चयनing hang SW Workaround*/
	uपूर्णांक32_t line_समय_in_us;
पूर्ण;

काष्ठा dm_bl_data_poपूर्णांक अणु
		/* Brightness level in percentage */
		uपूर्णांक8_t luminance;
		/* Brightness level as effective value in range 0-255,
		 * corresponding to above percentage
		 */
		uपूर्णांक8_t संकेत_level;
पूर्ण;

/* Total size of the काष्ठाure should not exceed 256 bytes */
#घोषणा BL_DATA_POINTS 99
काष्ठा dm_acpi_atअगर_backlight_caps अणु
	uपूर्णांक16_t size; /* Bytes 0-1 (2 bytes) */
	uपूर्णांक16_t flags; /* Byted 2-3 (2 bytes) */
	uपूर्णांक8_t  error_code; /* Byte 4 */
	uपूर्णांक8_t  ac_level_percentage; /* Byte 5 */
	uपूर्णांक8_t  dc_level_percentage; /* Byte 6 */
	uपूर्णांक8_t  min_input_संकेत; /* Byte 7 */
	uपूर्णांक8_t  max_input_संकेत; /* Byte 8 */
	uपूर्णांक8_t  num_data_poपूर्णांकs; /* Byte 9 */
	काष्ठा dm_bl_data_poपूर्णांक data_poपूर्णांकs[BL_DATA_POINTS]; /* Bytes 10-207 (198 bytes)*/
पूर्ण;

क्रमागत dm_acpi_display_type अणु
	AcpiDisplayType_LCD1 = 0,
	AcpiDisplayType_CRT1 = 1,
	AcpiDisplayType_DFP1 = 3,
	AcpiDisplayType_CRT2 = 4,
	AcpiDisplayType_LCD2 = 5,
	AcpiDisplayType_DFP2 = 7,
	AcpiDisplayType_DFP3 = 9,
	AcpiDisplayType_DFP4 = 10,
	AcpiDisplayType_DFP5 = 11,
	AcpiDisplayType_DFP6 = 12
पूर्ण;

काष्ठा dm_pp_घातer_level_change_request अणु
	क्रमागत dm_pp_घड़ीs_state घातer_level;
पूर्ण;

काष्ठा dm_pp_घड़ी_क्रम_voltage_req अणु
	क्रमागत dm_pp_घड़ी_प्रकारype clk_type;
	uपूर्णांक32_t घड़ीs_in_khz;
पूर्ण;

काष्ठा dm_pp_अटल_घड़ी_info अणु
	uपूर्णांक32_t max_sclk_khz;
	uपूर्णांक32_t max_mclk_khz;

	/* max possible display block घड़ीs state */
	क्रमागत dm_pp_घड़ीs_state max_घड़ीs_state;
पूर्ण;

काष्ठा dtn_min_clk_info अणु
	uपूर्णांक32_t disp_clk_khz;
	uपूर्णांक32_t min_engine_घड़ी_khz;
	uपूर्णांक32_t min_memory_घड़ी_khz;
पूर्ण;

#पूर्ण_अगर
