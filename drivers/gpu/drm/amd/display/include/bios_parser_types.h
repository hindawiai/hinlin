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

#अगर_अघोषित __DAL_BIOS_PARSER_TYPES_H__

#घोषणा __DAL_BIOS_PARSER_TYPES_H__

#समावेश "dm_services.h"
#समावेश "include/signal_types.h"
#समावेश "include/grph_object_ctrl_defs.h"
#समावेश "include/gpio_types.h"
#समावेश "include/link_service_types.h"

/* TODO: include संकेत_types.h and हटाओ this क्रमागत */
क्रमागत as_संकेत_type अणु
	AS_SIGNAL_TYPE_NONE = 0L, /* no संकेत */
	AS_SIGNAL_TYPE_DVI,
	AS_SIGNAL_TYPE_HDMI,
	AS_SIGNAL_TYPE_LVDS,
	AS_SIGNAL_TYPE_DISPLAY_PORT,
	AS_SIGNAL_TYPE_GPU_PLL,
	AS_SIGNAL_TYPE_XGMI,
	AS_SIGNAL_TYPE_UNKNOWN
पूर्ण;

क्रमागत bp_result अणु
	BP_RESULT_OK = 0, /* There was no error */
	BP_RESULT_BADINPUT, /*Bad input parameter */
	BP_RESULT_BADBIOSTABLE, /* Bad BIOS table */
	BP_RESULT_UNSUPPORTED, /* BIOS Table is not supported */
	BP_RESULT_NORECORD, /* Record can't be found */
	BP_RESULT_FAILURE
पूर्ण;

क्रमागत bp_encoder_control_action अणु
	/* direct VBIOS translation! Just to simplअगरy the translation */
	ENCODER_CONTROL_DISABLE = 0,
	ENCODER_CONTROL_ENABLE,
	ENCODER_CONTROL_SETUP,
	ENCODER_CONTROL_INIT
पूर्ण;

क्रमागत bp_transmitter_control_action अणु
	/* direct VBIOS translation! Just to simplअगरy the translation */
	TRANSMITTER_CONTROL_DISABLE = 0,
	TRANSMITTER_CONTROL_ENABLE,
	TRANSMITTER_CONTROL_BACKLIGHT_OFF,
	TRANSMITTER_CONTROL_BACKLIGHT_ON,
	TRANSMITTER_CONTROL_BACKLIGHT_BRIGHTNESS,
	TRANSMITTER_CONTROL_LCD_SETF_TEST_START,
	TRANSMITTER_CONTROL_LCD_SELF_TEST_STOP,
	TRANSMITTER_CONTROL_INIT,
	TRANSMITTER_CONTROL_DEACTIVATE,
	TRANSMITTER_CONTROL_ACTIAVATE,
	TRANSMITTER_CONTROL_SETUP,
	TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS,
	/* ATOM_TRANSMITTER_ACTION_POWER_ON. This action is क्रम eDP only
	 * (घातer up the panel)
	 */
	TRANSMITTER_CONTROL_POWER_ON,
	/* ATOM_TRANSMITTER_ACTION_POWER_OFF. This action is क्रम eDP only
	 * (घातer करोwn the panel)
	 */
	TRANSMITTER_CONTROL_POWER_OFF
पूर्ण;

क्रमागत bp_बाह्यal_encoder_control_action अणु
	EXTERNAL_ENCODER_CONTROL_DISABLE = 0,
	EXTERNAL_ENCODER_CONTROL_ENABLE = 1,
	EXTERNAL_ENCODER_CONTROL_INIT = 0x7,
	EXTERNAL_ENCODER_CONTROL_SETUP = 0xf,
	EXTERNAL_ENCODER_CONTROL_UNBLANK = 0x10,
	EXTERNAL_ENCODER_CONTROL_BLANK = 0x11,
पूर्ण;

क्रमागत bp_pipe_control_action अणु
	ASIC_PIPE_DISABLE = 0,
	ASIC_PIPE_ENABLE,
	ASIC_PIPE_INIT
पूर्ण;

क्रमागत bp_lvपंचांगa_control_action अणु
	LVTMA_CONTROL_LCD_BLOFF = 2,
	LVTMA_CONTROL_LCD_BLON = 3,
	LVTMA_CONTROL_POWER_ON = 12,
	LVTMA_CONTROL_POWER_OFF = 13
पूर्ण;

काष्ठा bp_encoder_control अणु
	क्रमागत bp_encoder_control_action action;
	क्रमागत engine_id engine_id;
	क्रमागत transmitter transmitter;
	क्रमागत संकेत_type संकेत;
	क्रमागत dc_lane_count lanes_number;
	क्रमागत dc_color_depth color_depth;
	bool enable_dp_audio;
	uपूर्णांक32_t pixel_घड़ी; /* khz */
पूर्ण;

काष्ठा bp_बाह्यal_encoder_control अणु
	क्रमागत bp_बाह्यal_encoder_control_action action;
	क्रमागत engine_id engine_id;
	क्रमागत dc_link_rate link_rate;
	क्रमागत dc_lane_count lanes_number;
	क्रमागत संकेत_type संकेत;
	क्रमागत dc_color_depth color_depth;
	bool coherent;
	काष्ठा graphics_object_id encoder_id;
	काष्ठा graphics_object_id connector_obj_id;
	uपूर्णांक32_t pixel_घड़ी; /* in KHz */
पूर्ण;

काष्ठा bp_crtc_source_select अणु
	क्रमागत engine_id engine_id;
	क्रमागत controller_id controller_id;
	/* from GPU Tx aka asic_संकेत */
	क्रमागत संकेत_type संकेत;
	/* sink_संकेत may dअगरfer from asicSignal अगर Translator encoder */
	क्रमागत संकेत_type sink_संकेत;
	क्रमागत display_output_bit_depth display_output_bit_depth;
	bool enable_dp_audio;
पूर्ण;

काष्ठा bp_transmitter_control अणु
	क्रमागत bp_transmitter_control_action action;
	क्रमागत engine_id engine_id;
	क्रमागत transmitter transmitter; /* PhyId */
	क्रमागत dc_lane_count lanes_number;
	क्रमागत घड़ी_source_id pll_id; /* needed क्रम DCE 4.0 */
	क्रमागत संकेत_type संकेत;
	क्रमागत dc_color_depth color_depth; /* not used क्रम DCE6.0 */
	क्रमागत hpd_source_id hpd_sel; /* ucHPDSel, used क्रम DCe6.0 */
	काष्ठा graphics_object_id connector_obj_id;
	/* symClock; in 10kHz, pixel घड़ी, in HDMI deep color mode, it should
	 * be pixel घड़ी * deep_color_ratio (in KHz)
	 */
	uपूर्णांक32_t pixel_घड़ी;
	uपूर्णांक32_t lane_select;
	uपूर्णांक32_t lane_settings;
	bool coherent;
	bool multi_path;
	bool single_pll_mode;
पूर्ण;

काष्ठा bp_hw_crtc_timing_parameters अणु
	क्रमागत controller_id controller_id;
	/* horizontal part */
	uपूर्णांक32_t h_total;
	uपूर्णांक32_t h_addressable;
	uपूर्णांक32_t h_overscan_left;
	uपूर्णांक32_t h_overscan_right;
	uपूर्णांक32_t h_sync_start;
	uपूर्णांक32_t h_sync_width;

	/* vertical part */
	uपूर्णांक32_t v_total;
	uपूर्णांक32_t v_addressable;
	uपूर्णांक32_t v_overscan_top;
	uपूर्णांक32_t v_overscan_bottom;
	uपूर्णांक32_t v_sync_start;
	uपूर्णांक32_t v_sync_width;

	काष्ठा timing_flags अणु
		uपूर्णांक32_t INTERLACE:1;
		uपूर्णांक32_t PIXEL_REPETITION:4;
		uपूर्णांक32_t HSYNC_POSITIVE_POLARITY:1;
		uपूर्णांक32_t VSYNC_POSITIVE_POLARITY:1;
		uपूर्णांक32_t HORZ_COUNT_BY_TWO:1;
	पूर्ण flags;
पूर्ण;

काष्ठा bp_adjust_pixel_घड़ी_parameters अणु
	/* Input: Signal Type - to be converted to Encoder mode */
	क्रमागत संकेत_type संकेत_type;
	/* Input: Encoder object id */
	काष्ठा graphics_object_id encoder_object_id;
	/* Input: Pixel Clock (requested Pixel घड़ी based on Video timing
	 * standard used) in KHz
	 */
	uपूर्णांक32_t pixel_घड़ी;
	/* Output: Adjusted Pixel Clock (after VBIOS exec table) in KHz */
	uपूर्णांक32_t adjusted_pixel_घड़ी;
	/* Output: If non-zero, this refDiv value should be used to calculate
	 * other ppll params */
	uपूर्णांक32_t reference_भागider;
	/* Output: If non-zero, this postDiv value should be used to calculate
	 * other ppll params */
	uपूर्णांक32_t pixel_घड़ी_post_भागider;
	/* Input: Enable spपढ़ो spectrum */
	bool ss_enable;
पूर्ण;

काष्ठा bp_pixel_घड़ी_parameters अणु
	क्रमागत controller_id controller_id; /* (Which CRTC uses this PLL) */
	क्रमागत घड़ी_source_id pll_id; /* Clock Source Id */
	/* संकेत_type -> Encoder Mode - needed by VBIOS Exec table */
	क्रमागत संकेत_type संकेत_type;
	/* Adjusted Pixel Clock (after VBIOS exec table)
	 * that becomes Target Pixel Clock (100 Hz units) */
	uपूर्णांक32_t target_pixel_घड़ी_100hz;
	/* Calculated Reference भागider of Display PLL */
	uपूर्णांक32_t reference_भागider;
	/* Calculated Feedback भागider of Display PLL */
	uपूर्णांक32_t feedback_भागider;
	/* Calculated Fractional Feedback भागider of Display PLL */
	uपूर्णांक32_t fractional_feedback_भागider;
	/* Calculated Pixel Clock Post भागider of Display PLL */
	uपूर्णांक32_t pixel_घड़ी_post_भागider;
	काष्ठा graphics_object_id encoder_object_id; /* Encoder object id */
	/* VBIOS वापसs a fixed display घड़ी when DFS-bypass feature
	 * is enabled (KHz) */
	uपूर्णांक32_t dfs_bypass_display_घड़ी;
	/* color depth to support HDMI deep color */
	क्रमागत transmitter_color_depth color_depth;

	काष्ठा program_pixel_घड़ी_flags अणु
		uपूर्णांक32_t FORCE_PROGRAMMING_OF_PLL:1;
		/* Use Engine Clock as source क्रम Display Clock when
		 * programming PLL */
		uपूर्णांक32_t USE_E_CLOCK_AS_SOURCE_FOR_D_CLOCK:1;
		/* Use बाह्यal reference घड़ी (refDivSrc क्रम PLL) */
		uपूर्णांक32_t SET_EXTERNAL_REF_DIV_SRC:1;
		/* Use DFS bypass क्रम Display घड़ी. */
		uपूर्णांक32_t SET_DISPCLK_DFS_BYPASS:1;
		/* Force program PHY PLL only */
		uपूर्णांक32_t PROGRAM_PHY_PLL_ONLY:1;
		/* Support क्रम YUV420 */
		uपूर्णांक32_t SUPPORT_YUV_420:1;
		/* Use XTALIN reference घड़ी source */
		uपूर्णांक32_t SET_XTALIN_REF_SRC:1;
		/* Use GENLK reference घड़ी source */
		uपूर्णांक32_t SET_GENLOCK_REF_DIV_SRC:1;
	पूर्ण flags;
पूर्ण;

क्रमागत bp_dce_घड़ी_प्रकारype अणु
	DCECLOCK_TYPE_DISPLAY_CLOCK = 0,
	DCECLOCK_TYPE_DPREFCLK      = 1
पूर्ण;

/* DCE Clock Parameters काष्ठाure क्रम SetDceClock Exec command table */
काष्ठा bp_set_dce_घड़ी_parameters अणु
	क्रमागत घड़ी_source_id pll_id; /* Clock Source Id */
	/* Display घड़ी or DPREFCLK value */
	uपूर्णांक32_t target_घड़ी_frequency;
	/* Clock to set: =0: DISPCLK  =1: DPREFCLK  =2: PIXCLK */
	क्रमागत bp_dce_घड़ी_प्रकारype घड़ी_प्रकारype;

	काष्ठा set_dce_घड़ी_flags अणु
		uपूर्णांक32_t USE_GENERICA_AS_SOURCE_FOR_DPREFCLK:1;
		/* Use XTALIN reference घड़ी source */
		uपूर्णांक32_t USE_XTALIN_AS_SOURCE_FOR_DPREFCLK:1;
		/* Use PCIE reference घड़ी source */
		uपूर्णांक32_t USE_PCIE_AS_SOURCE_FOR_DPREFCLK:1;
		/* Use GENLK reference घड़ी source */
		uपूर्णांक32_t USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK:1;
	पूर्ण flags;
पूर्ण;

काष्ठा spपढ़ो_spectrum_flags अणु
	/* 1 = Center Spपढ़ो; 0 = करोwn spपढ़ो */
	uपूर्णांक32_t CENTER_SPREAD:1;
	/* 1 = बाह्यal; 0 = पूर्णांकernal */
	uपूर्णांक32_t EXTERNAL_SS:1;
	/* 1 = delta-sigma type parameter; 0 = ver1 */
	uपूर्णांक32_t DS_TYPE:1;
पूर्ण;

काष्ठा bp_spपढ़ो_spectrum_parameters अणु
	क्रमागत घड़ी_source_id pll_id;
	uपूर्णांक32_t percentage;
	uपूर्णांक32_t ds_frac_amount;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t step;
			uपूर्णांक32_t delay;
			uपूर्णांक32_t range; /* In Hz unit */
		पूर्ण ver1;
		काष्ठा अणु
			uपूर्णांक32_t feedback_amount;
			uपूर्णांक32_t nfrac_amount;
			uपूर्णांक32_t ds_frac_size;
		पूर्ण ds;
	पूर्ण;

	काष्ठा spपढ़ो_spectrum_flags flags;
पूर्ण;

काष्ठा bp_disp_connector_caps_info अणु
	uपूर्णांक32_t INTERNAL_DISPLAY    : 1;
	uपूर्णांक32_t INTERNAL_DISPLAY_BL : 1;
पूर्ण;

काष्ठा bp_encoder_cap_info अणु
	uपूर्णांक32_t DP_HBR2_CAP:1;
	uपूर्णांक32_t DP_HBR2_EN:1;
	uपूर्णांक32_t DP_HBR3_EN:1;
	uपूर्णांक32_t HDMI_6GB_EN:1;
	uपूर्णांक32_t DP_IS_USB_C:1;
	uपूर्णांक32_t RESERVED:27;
पूर्ण;

काष्ठा bp_soc_bb_info अणु
	uपूर्णांक32_t dram_घड़ी_change_latency_100ns;
	uपूर्णांक32_t dram_sr_निकास_latency_100ns;
	uपूर्णांक32_t dram_sr_enter_निकास_latency_100ns;
पूर्ण;

#पूर्ण_अगर /*__DAL_BIOS_PARSER_TYPES_H__ */
