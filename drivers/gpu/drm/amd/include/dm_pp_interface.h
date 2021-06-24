<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _DM_PP_INTERFACE_
#घोषणा _DM_PP_INTERFACE_

#समावेश "dm_services_types.h"

#घोषणा PP_MAX_CLOCK_LEVELS 16

क्रमागत amd_pp_display_config_typeअणु
	AMD_PP_DisplayConfigType_None = 0,
	AMD_PP_DisplayConfigType_DP54 ,
	AMD_PP_DisplayConfigType_DP432 ,
	AMD_PP_DisplayConfigType_DP324 ,
	AMD_PP_DisplayConfigType_DP27,
	AMD_PP_DisplayConfigType_DP243,
	AMD_PP_DisplayConfigType_DP216,
	AMD_PP_DisplayConfigType_DP162,
	AMD_PP_DisplayConfigType_HDMI6G ,
	AMD_PP_DisplayConfigType_HDMI297 ,
	AMD_PP_DisplayConfigType_HDMI162,
	AMD_PP_DisplayConfigType_LVDS,
	AMD_PP_DisplayConfigType_DVI,
	AMD_PP_DisplayConfigType_WIRELESS,
	AMD_PP_DisplayConfigType_VGA
पूर्ण;

काष्ठा single_display_configuration
अणु
	uपूर्णांक32_t controller_index;
	uपूर्णांक32_t controller_id;
	uपूर्णांक32_t संकेत_type;
	uपूर्णांक32_t display_state;
	/* phy id क्रम the primary पूर्णांकernal transmitter */
	uपूर्णांक8_t primary_transmitter_phyi_d;
	/* biपंचांगap with the active lanes */
	uपूर्णांक8_t primary_transmitter_active_lanemap;
	/* phy id क्रम the secondary पूर्णांकernal transmitter (क्रम dual-link dvi) */
	uपूर्णांक8_t secondary_transmitter_phy_id;
	/* biपंचांगap with the active lanes */
	uपूर्णांक8_t secondary_transmitter_active_lanemap;
	/* misc phy settings क्रम SMU. */
	uपूर्णांक32_t config_flags;
	uपूर्णांक32_t display_type;
	uपूर्णांक32_t view_resolution_cx;
	uपूर्णांक32_t view_resolution_cy;
	क्रमागत amd_pp_display_config_type displayconfigtype;
	uपूर्णांक32_t vertical_refresh; /* क्रम active display */
पूर्ण;

#घोषणा MAX_NUM_DISPLAY 32

काष्ठा amd_pp_display_configuration अणु
	bool nb_pstate_चयन_disable;/* controls NB PState चयन */
	bool cpu_cc6_disable; /* controls CPU CState चयन ( on or off) */
	bool cpu_pstate_disable;
	uपूर्णांक32_t cpu_pstate_separation_समय;

	uपूर्णांक32_t num_display;  /* total number of display*/
	uपूर्णांक32_t num_path_including_non_display;
	uपूर्णांक32_t crossfire_display_index;
	uपूर्णांक32_t min_mem_set_घड़ी;
	uपूर्णांक32_t min_core_set_घड़ी;
	/* unit 10KHz x bit*/
	uपूर्णांक32_t min_bus_bandwidth;
	/* minimum required stutter sclk, in 10khz uपूर्णांक32_t ulMinCoreSetClk;*/
	uपूर्णांक32_t min_core_set_घड़ी_in_sr;

	काष्ठा single_display_configuration displays[MAX_NUM_DISPLAY];

	uपूर्णांक32_t vrefresh; /* क्रम active display*/

	uपूर्णांक32_t min_vblank_समय; /* क्रम active display*/
	bool multi_monitor_in_sync;
	/* Controller Index of primary display - used in MCLK SMC चयनing hang
	 * SW Workaround*/
	uपूर्णांक32_t crtc_index;
	/* htotal*1000/pixelclk - used in MCLK SMC चयनing hang SW Workaround*/
	uपूर्णांक32_t line_समय_in_us;
	bool invalid_vblank_समय;

	uपूर्णांक32_t display_clk;
	/*
	 * क्रम given display configuration अगर multimonitormnsync == false then
	 * Memory घड़ी DPMS with this latency or below is allowed, DPMS with
	 * higher latency not allowed.
	 */
	uपूर्णांक32_t dce_tolerable_mclk_in_active_latency;
	uपूर्णांक32_t min_dcef_set_clk;
	uपूर्णांक32_t min_dcef_deep_sleep_set_clk;
पूर्ण;

काष्ठा amd_pp_simple_घड़ी_info अणु
	uपूर्णांक32_t	engine_max_घड़ी;
	uपूर्णांक32_t	memory_max_घड़ी;
	uपूर्णांक32_t	level;
पूर्ण;

क्रमागत PP_DAL_POWERLEVEL अणु
	PP_DAL_POWERLEVEL_INVALID = 0,
	PP_DAL_POWERLEVEL_ULTRALOW,
	PP_DAL_POWERLEVEL_LOW,
	PP_DAL_POWERLEVEL_NOMINAL,
	PP_DAL_POWERLEVEL_PERFORMANCE,

	PP_DAL_POWERLEVEL_0 = PP_DAL_POWERLEVEL_ULTRALOW,
	PP_DAL_POWERLEVEL_1 = PP_DAL_POWERLEVEL_LOW,
	PP_DAL_POWERLEVEL_2 = PP_DAL_POWERLEVEL_NOMINAL,
	PP_DAL_POWERLEVEL_3 = PP_DAL_POWERLEVEL_PERFORMANCE,
	PP_DAL_POWERLEVEL_4 = PP_DAL_POWERLEVEL_3+1,
	PP_DAL_POWERLEVEL_5 = PP_DAL_POWERLEVEL_4+1,
	PP_DAL_POWERLEVEL_6 = PP_DAL_POWERLEVEL_5+1,
	PP_DAL_POWERLEVEL_7 = PP_DAL_POWERLEVEL_6+1,
पूर्ण;

काष्ठा amd_pp_घड़ी_info अणु
	uपूर्णांक32_t min_engine_घड़ी;
	uपूर्णांक32_t max_engine_घड़ी;
	uपूर्णांक32_t min_memory_घड़ी;
	uपूर्णांक32_t max_memory_घड़ी;
	uपूर्णांक32_t min_bus_bandwidth;
	uपूर्णांक32_t max_bus_bandwidth;
	uपूर्णांक32_t max_engine_घड़ी_in_sr;
	uपूर्णांक32_t min_engine_घड़ी_in_sr;
	क्रमागत PP_DAL_POWERLEVEL max_घड़ीs_state;
पूर्ण;

क्रमागत amd_pp_घड़ी_प्रकारype अणु
	amd_pp_disp_घड़ी = 1,
	amd_pp_sys_घड़ी,
	amd_pp_mem_घड़ी,
	amd_pp_dcef_घड़ी,
	amd_pp_soc_घड़ी,
	amd_pp_pixel_घड़ी,
	amd_pp_phy_घड़ी,
	amd_pp_dcf_घड़ी,
	amd_pp_dpp_घड़ी,
	amd_pp_f_घड़ी = amd_pp_dcef_घड़ी,
पूर्ण;

#घोषणा MAX_NUM_CLOCKS 16

काष्ठा amd_pp_घड़ीs अणु
	uपूर्णांक32_t count;
	uपूर्णांक32_t घड़ी[MAX_NUM_CLOCKS];
	uपूर्णांक32_t latency[MAX_NUM_CLOCKS];
पूर्ण;

काष्ठा pp_घड़ी_with_latency अणु
	uपूर्णांक32_t घड़ीs_in_khz;
	uपूर्णांक32_t latency_in_us;
पूर्ण;

काष्ठा pp_घड़ी_levels_with_latency अणु
	uपूर्णांक32_t num_levels;
	काष्ठा pp_घड़ी_with_latency data[PP_MAX_CLOCK_LEVELS];
पूर्ण;

काष्ठा pp_घड़ी_with_voltage अणु
	uपूर्णांक32_t घड़ीs_in_khz;
	uपूर्णांक32_t voltage_in_mv;
पूर्ण;

काष्ठा pp_घड़ी_levels_with_voltage अणु
	uपूर्णांक32_t num_levels;
	काष्ठा pp_घड़ी_with_voltage data[PP_MAX_CLOCK_LEVELS];
पूर्ण;

काष्ठा pp_display_घड़ी_request अणु
	क्रमागत amd_pp_घड़ी_प्रकारype घड़ी_प्रकारype;
	uपूर्णांक32_t घड़ी_freq_in_khz;
पूर्ण;

#पूर्ण_अगर /* _DM_PP_INTERFACE_ */
