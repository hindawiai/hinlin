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
 * Authors: AMD
 *
 */

#अगर_अघोषित DC_DP_TYPES_H
#घोषणा DC_DP_TYPES_H

#समावेश "os_types.h"

क्रमागत dc_lane_count अणु
	LANE_COUNT_UNKNOWN = 0,
	LANE_COUNT_ONE = 1,
	LANE_COUNT_TWO = 2,
	LANE_COUNT_FOUR = 4,
	LANE_COUNT_EIGHT = 8,
	LANE_COUNT_DP_MAX = LANE_COUNT_FOUR
पूर्ण;

/* This is actually a reference घड़ी (27MHz) multiplier
 * 162MBps bandwidth क्रम 1.62GHz like rate,
 * 270MBps क्रम 2.70GHz,
 * 324MBps क्रम 3.24Ghz,
 * 540MBps क्रम 5.40GHz
 * 810MBps क्रम 8.10GHz
 */
क्रमागत dc_link_rate अणु
	LINK_RATE_UNKNOWN = 0,
	LINK_RATE_LOW = 0x06,		// Rate_1 (RBR)	- 1.62 Gbps/Lane
	LINK_RATE_RATE_2 = 0x08,	// Rate_2		- 2.16 Gbps/Lane
	LINK_RATE_RATE_3 = 0x09,	// Rate_3		- 2.43 Gbps/Lane
	LINK_RATE_HIGH = 0x0A,		// Rate_4 (HBR)	- 2.70 Gbps/Lane
	LINK_RATE_RBR2 = 0x0C,		// Rate_5 (RBR2)- 3.24 Gbps/Lane
	LINK_RATE_RATE_6 = 0x10,	// Rate_6		- 4.32 Gbps/Lane
	LINK_RATE_HIGH2 = 0x14,		// Rate_7 (HBR2)- 5.40 Gbps/Lane
	LINK_RATE_HIGH3 = 0x1E		// Rate_8 (HBR3)- 8.10 Gbps/Lane
पूर्ण;

क्रमागत dc_link_spपढ़ो अणु
	LINK_SPREAD_DISABLED = 0x00,
	/* 0.5 % करोwnspपढ़ो 30 kHz */
	LINK_SPREAD_05_DOWNSPREAD_30KHZ = 0x10,
	/* 0.5 % करोwnspपढ़ो 33 kHz */
	LINK_SPREAD_05_DOWNSPREAD_33KHZ = 0x11
पूर्ण;

क्रमागत dc_voltage_swing अणु
	VOLTAGE_SWING_LEVEL0 = 0,	/* direct HW translation! */
	VOLTAGE_SWING_LEVEL1,
	VOLTAGE_SWING_LEVEL2,
	VOLTAGE_SWING_LEVEL3,
	VOLTAGE_SWING_MAX_LEVEL = VOLTAGE_SWING_LEVEL3
पूर्ण;

क्रमागत dc_pre_emphasis अणु
	PRE_EMPHASIS_DISABLED = 0,	/* direct HW translation! */
	PRE_EMPHASIS_LEVEL1,
	PRE_EMPHASIS_LEVEL2,
	PRE_EMPHASIS_LEVEL3,
	PRE_EMPHASIS_MAX_LEVEL = PRE_EMPHASIS_LEVEL3
पूर्ण;
/* Post Cursor 2 is optional क्रम transmitter
 * and it applies only to the मुख्य link operating at HBR2
 */
क्रमागत dc_post_cursor2 अणु
	POST_CURSOR2_DISABLED = 0,	/* direct HW translation! */
	POST_CURSOR2_LEVEL1,
	POST_CURSOR2_LEVEL2,
	POST_CURSOR2_LEVEL3,
	POST_CURSOR2_MAX_LEVEL = POST_CURSOR2_LEVEL3,
पूर्ण;

क्रमागत dc_dp_training_pattern अणु
	DP_TRAINING_PATTERN_SEQUENCE_1 = 0,
	DP_TRAINING_PATTERN_SEQUENCE_2,
	DP_TRAINING_PATTERN_SEQUENCE_3,
	DP_TRAINING_PATTERN_SEQUENCE_4,
पूर्ण;

काष्ठा dc_link_settings अणु
	क्रमागत dc_lane_count lane_count;
	क्रमागत dc_link_rate link_rate;
	क्रमागत dc_link_spपढ़ो link_spपढ़ो;
	bool use_link_rate_set;
	uपूर्णांक8_t link_rate_set;
पूर्ण;

काष्ठा dc_lane_settings अणु
	क्रमागत dc_voltage_swing VOLTAGE_SWING;
	क्रमागत dc_pre_emphasis PRE_EMPHASIS;
	क्रमागत dc_post_cursor2 POST_CURSOR2;
पूर्ण;

काष्ठा dc_link_training_settings अणु
	काष्ठा dc_link_settings link;
	काष्ठा dc_lane_settings lane_settings[LANE_COUNT_DP_MAX];
पूर्ण;

काष्ठा dc_link_training_overrides अणु
	क्रमागत dc_voltage_swing *voltage_swing;
	क्रमागत dc_pre_emphasis *pre_emphasis;
	क्रमागत dc_post_cursor2 *post_cursor2;

	uपूर्णांक16_t *cr_pattern_समय;
	uपूर्णांक16_t *eq_pattern_समय;
	क्रमागत dc_dp_training_pattern *pattern_क्रम_cr;
	क्रमागत dc_dp_training_pattern *pattern_क्रम_eq;

	क्रमागत dc_link_spपढ़ो *करोwnspपढ़ो;
	bool *alternate_scrambler_reset;
	bool *enhanced_framing;
	bool *mst_enable;
	bool *fec_enable;
पूर्ण;

जोड़ dpcd_rev अणु
	काष्ठा अणु
		uपूर्णांक8_t MINOR:4;
		uपूर्णांक8_t MAJOR:4;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ max_lane_count अणु
	काष्ठा अणु
		uपूर्णांक8_t MAX_LANE_COUNT:5;
		uपूर्णांक8_t POST_LT_ADJ_REQ_SUPPORTED:1;
		uपूर्णांक8_t TPS3_SUPPORTED:1;
		uपूर्णांक8_t ENHANCED_FRAME_CAP:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ max_करोwn_spपढ़ो अणु
	काष्ठा अणु
		uपूर्णांक8_t MAX_DOWN_SPREAD:1;
		uपूर्णांक8_t RESERVED:5;
		uपूर्णांक8_t NO_AUX_HANDSHAKE_LINK_TRAINING:1;
		uपूर्णांक8_t TPS4_SUPPORTED:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ msपंचांग_cap अणु
	काष्ठा अणु
		uपूर्णांक8_t MST_CAP:1;
		uपूर्णांक8_t RESERVED:7;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ lane_count_set अणु
	काष्ठा अणु
		uपूर्णांक8_t LANE_COUNT_SET:5;
		uपूर्णांक8_t POST_LT_ADJ_REQ_GRANTED:1;
		uपूर्णांक8_t RESERVED:1;
		uपूर्णांक8_t ENHANCED_FRAMING:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ lane_status अणु
	काष्ठा अणु
		uपूर्णांक8_t CR_DONE_0:1;
		uपूर्णांक8_t CHANNEL_EQ_DONE_0:1;
		uपूर्णांक8_t SYMBOL_LOCKED_0:1;
		uपूर्णांक8_t RESERVED0:1;
		uपूर्णांक8_t CR_DONE_1:1;
		uपूर्णांक8_t CHANNEL_EQ_DONE_1:1;
		uपूर्णांक8_t SYMBOL_LOCKED_1:1;
		uपूर्णांक8_t RESERVED_1:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ device_service_irq अणु
	काष्ठा अणु
		uपूर्णांक8_t REMOTE_CONTROL_CMD_PENDING:1;
		uपूर्णांक8_t AUTOMATED_TEST:1;
		uपूर्णांक8_t CP_IRQ:1;
		uपूर्णांक8_t MCCS_IRQ:1;
		uपूर्णांक8_t DOWN_REP_MSG_RDY:1;
		uपूर्णांक8_t UP_REQ_MSG_RDY:1;
		uपूर्णांक8_t SINK_SPECIFIC:1;
		uपूर्णांक8_t reserved:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ sink_count अणु
	काष्ठा अणु
		uपूर्णांक8_t SINK_COUNT:6;
		uपूर्णांक8_t CPREADY:1;
		uपूर्णांक8_t RESERVED:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ lane_align_status_updated अणु
	काष्ठा अणु
		uपूर्णांक8_t INTERLANE_ALIGN_DONE:1;
		uपूर्णांक8_t POST_LT_ADJ_REQ_IN_PROGRESS:1;
		uपूर्णांक8_t RESERVED:4;
		uपूर्णांक8_t DOWNSTREAM_PORT_STATUS_CHANGED:1;
		uपूर्णांक8_t LINK_STATUS_UPDATED:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ lane_adjust अणु
	काष्ठा अणु
		uपूर्णांक8_t VOLTAGE_SWING_LANE:2;
		uपूर्णांक8_t PRE_EMPHASIS_LANE:2;
		uपूर्णांक8_t RESERVED:4;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dpcd_training_pattern अणु
	काष्ठा अणु
		uपूर्णांक8_t TRAINING_PATTERN_SET:4;
		uपूर्णांक8_t RECOVERED_CLOCK_OUT_EN:1;
		uपूर्णांक8_t SCRAMBLING_DISABLE:1;
		uपूर्णांक8_t SYMBOL_ERROR_COUNT_SEL:2;
	पूर्ण v1_4;
	काष्ठा अणु
		uपूर्णांक8_t TRAINING_PATTERN_SET:2;
		uपूर्णांक8_t LINK_QUAL_PATTERN_SET:2;
		uपूर्णांक8_t RESERVED:4;
	पूर्ण v1_3;
	uपूर्णांक8_t raw;
पूर्ण;

/* Training Lane is used to configure करोwnstream DP device's voltage swing
and pre-emphasis levels*/
/* The DPCD addresses are from 0x103 to 0x106*/
जोड़ dpcd_training_lane अणु
	काष्ठा अणु
		uपूर्णांक8_t VOLTAGE_SWING_SET:2;
		uपूर्णांक8_t MAX_SWING_REACHED:1;
		uपूर्णांक8_t PRE_EMPHASIS_SET:2;
		uपूर्णांक8_t MAX_PRE_EMPHASIS_REACHED:1;
		uपूर्णांक8_t RESERVED:2;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/* TMDS-converter related */
जोड़ dwnstream_port_caps_byte0 अणु
	काष्ठा अणु
		uपूर्णांक8_t DWN_STRM_PORTX_TYPE:3;
		uपूर्णांक8_t DWN_STRM_PORTX_HPD:1;
		uपूर्णांक8_t RESERVERD:4;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/* these are the detailed types stored at DWN_STRM_PORTX_CAP (00080h)*/
क्रमागत dpcd_करोwnstream_port_detailed_type अणु
	DOWN_STREAM_DETAILED_DP = 0,
	DOWN_STREAM_DETAILED_VGA,
	DOWN_STREAM_DETAILED_DVI,
	DOWN_STREAM_DETAILED_HDMI,
	DOWN_STREAM_DETAILED_NONDDC,/* has no EDID (TV,CV)*/
	DOWN_STREAM_DETAILED_DP_PLUS_PLUS
पूर्ण;

जोड़ dwnstream_port_caps_byte2 अणु
	काष्ठा अणु
		uपूर्णांक8_t MAX_BITS_PER_COLOR_COMPONENT:2;
		uपूर्णांक8_t RESERVED:6;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dp_करोwnstream_port_present अणु
	uपूर्णांक8_t byte;
	काष्ठा अणु
		uपूर्णांक8_t PORT_PRESENT:1;
		uपूर्णांक8_t PORT_TYPE:2;
		uपूर्णांक8_t FMT_CONVERSION:1;
		uपूर्णांक8_t DETAILED_CAPS:1;
		uपूर्णांक8_t RESERVED:3;
	पूर्ण fields;
पूर्ण;

जोड़ dwnstream_port_caps_byte3_dvi अणु
	काष्ठा अणु
		uपूर्णांक8_t RESERVED1:1;
		uपूर्णांक8_t DUAL_LINK:1;
		uपूर्णांक8_t HIGH_COLOR_DEPTH:1;
		uपूर्णांक8_t RESERVED2:5;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dwnstream_port_caps_byte3_hdmi अणु
	काष्ठा अणु
		uपूर्णांक8_t FRAME_SEQ_TO_FRAME_PACK:1;
		uपूर्णांक8_t YCrCr422_PASS_THROUGH:1;
		uपूर्णांक8_t YCrCr420_PASS_THROUGH:1;
		uपूर्णांक8_t YCrCr422_CONVERSION:1;
		uपूर्णांक8_t YCrCr420_CONVERSION:1;
		uपूर्णांक8_t RESERVED:3;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/*4-byte काष्ठाure क्रम detailed capabilities of a करोwn-stream port
(DP-to-TMDS converter).*/
जोड़ dwnstream_portxcaps अणु
	काष्ठा अणु
		जोड़ dwnstream_port_caps_byte0 byte0;
		अचिन्हित अक्षर max_TMDS_घड़ी;   //byte1
		जोड़ dwnstream_port_caps_byte2 byte2;

		जोड़ अणु
			जोड़ dwnstream_port_caps_byte3_dvi byteDVI;
			जोड़ dwnstream_port_caps_byte3_hdmi byteHDMI;
		पूर्ण byte3;
	पूर्ण bytes;

	अचिन्हित अक्षर raw[4];
पूर्ण;

जोड़ करोwnstream_port अणु
	काष्ठा अणु
		अचिन्हित अक्षर   present:1;
		अचिन्हित अक्षर   type:2;
		अचिन्हित अक्षर   क्रमmat_conv:1;
		अचिन्हित अक्षर   detailed_caps:1;
		अचिन्हित अक्षर   reserved:3;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;


जोड़ sink_status अणु
	काष्ठा अणु
		uपूर्णांक8_t RX_PORT0_STATUS:1;
		uपूर्णांक8_t RX_PORT1_STATUS:1;
		uपूर्णांक8_t RESERVED:6;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/*6-byte काष्ठाure corresponding to 6 रेजिस्टरs (200h-205h)
पढ़ो during handling of HPD-IRQ*/
जोड़ hpd_irq_data अणु
	काष्ठा अणु
		जोड़ sink_count sink_cnt;/* 200h */
		जोड़ device_service_irq device_service_irq;/* 201h */
		जोड़ lane_status lane01_status;/* 202h */
		जोड़ lane_status lane23_status;/* 203h */
		जोड़ lane_align_status_updated lane_status_updated;/* 204h */
		जोड़ sink_status sink_status;
	पूर्ण bytes;
	uपूर्णांक8_t raw[6];
पूर्ण;

जोड़ करोwn_stream_port_count अणु
	काष्ठा अणु
		uपूर्णांक8_t DOWN_STR_PORT_COUNT:4;
		uपूर्णांक8_t RESERVED:2; /*Bits 5:4 = RESERVED. Read all 0s.*/
		/*Bit 6 = MSA_TIMING_PAR_IGNORED
		0 = Sink device requires the MSA timing parameters
		1 = Sink device is capable of rendering incoming video
		 stream without MSA timing parameters*/
		uपूर्णांक8_t IGNORE_MSA_TIMING_PARAM:1;
		/*Bit 7 = OUI Support
		0 = OUI not supported
		1 = OUI supported
		(OUI and Device Identअगरication mandatory क्रम DP 1.2)*/
		uपूर्णांक8_t OUI_SUPPORT:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ करोwn_spपढ़ो_ctrl अणु
	काष्ठा अणु
		uपूर्णांक8_t RESERVED1:4;/* Bit 3:0 = RESERVED. Read all 0s*/
	/* Bits 4 = SPREAD_AMP. Spपढ़ोing amplitude
	0 = Main link संकेत is not करोwnspपढ़ो
	1 = Main link संकेत is करोwnspपढ़ो <= 0.5%
	with frequency in the range of 30kHz ~ 33kHz*/
		uपूर्णांक8_t SPREAD_AMP:1;
		uपूर्णांक8_t RESERVED2:2;/*Bit 6:5 = RESERVED. Read all 0s*/
	/*Bit 7 = MSA_TIMING_PAR_IGNORE_EN
	0 = Source device will send valid data क्रम the MSA Timing Params
	1 = Source device may send invalid data क्रम these MSA Timing Params*/
		uपूर्णांक8_t IGNORE_MSA_TIMING_PARAM:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dpcd_edp_config अणु
	काष्ठा अणु
		uपूर्णांक8_t PANEL_MODE_EDP:1;
		uपूर्णांक8_t FRAMING_CHANGE_ENABLE:1;
		uपूर्णांक8_t RESERVED:5;
		uपूर्णांक8_t PANEL_SELF_TEST_ENABLE:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

काष्ठा dp_device_venकरोr_id अणु
	uपूर्णांक8_t ieee_oui[3];/*24-bit IEEE OUI*/
	uपूर्णांक8_t ieee_device_id[6];/*usually 6-byte ASCII name*/
पूर्ण;

काष्ठा dp_sink_hw_fw_revision अणु
	uपूर्णांक8_t ieee_hw_rev;
	uपूर्णांक8_t ieee_fw_rev[2];
पूर्ण;

काष्ठा dpcd_venकरोr_signature अणु
	bool is_valid;

	जोड़ dpcd_ieee_venकरोr_signature अणु
		काष्ठा अणु
			uपूर्णांक8_t ieee_oui[3];/*24-bit IEEE OUI*/
			uपूर्णांक8_t ieee_device_id[6];/*usually 6-byte ASCII name*/
			uपूर्णांक8_t ieee_hw_rev;
			uपूर्णांक8_t ieee_fw_rev[2];
		पूर्ण;
		uपूर्णांक8_t raw[12];
	पूर्ण data;
पूर्ण;

काष्ठा dpcd_amd_signature अणु
	uपूर्णांक8_t AMD_IEEE_TxSignature_byte1;
	uपूर्णांक8_t AMD_IEEE_TxSignature_byte2;
	uपूर्णांक8_t AMD_IEEE_TxSignature_byte3;
पूर्ण;

काष्ठा dpcd_amd_device_id अणु
	uपूर्णांक8_t device_id_byte1;
	uपूर्णांक8_t device_id_byte2;
	uपूर्णांक8_t zero[4];
	uपूर्णांक8_t dce_version;
	uपूर्णांक8_t dal_version_byte1;
	uपूर्णांक8_t dal_version_byte2;
पूर्ण;

काष्ठा dpcd_source_backlight_set अणु
	काष्ठा  अणु
		uपूर्णांक8_t byte0;
		uपूर्णांक8_t byte1;
		uपूर्णांक8_t byte2;
		uपूर्णांक8_t byte3;
	पूर्ण backlight_level_millinits;

	काष्ठा  अणु
		uपूर्णांक8_t byte0;
		uपूर्णांक8_t byte1;
	पूर्ण backlight_transition_समय_ms;
पूर्ण;

जोड़ dpcd_source_backlight_get अणु
	काष्ठा अणु
		uपूर्णांक32_t backlight_millinits_peak; /* 326h */
		uपूर्णांक32_t backlight_millinits_avg; /* 32Ah */
	पूर्ण bytes;
	uपूर्णांक8_t raw[8];
पूर्ण;

/*DPCD रेजिस्टर of DP receiver capability field bits-*/
जोड़ edp_configuration_cap अणु
	काष्ठा अणु
		uपूर्णांक8_t ALT_SCRAMBLER_RESET:1;
		uपूर्णांक8_t FRAMING_CHANGE:1;
		uपूर्णांक8_t RESERVED:1;
		uपूर्णांक8_t DPCD_DISPLAY_CONTROL_CAPABLE:1;
		uपूर्णांक8_t RESERVED2:4;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dprx_feature अणु
	काष्ठा अणु
		uपूर्णांक8_t GTC_CAP:1;                             // bit 0: DP 1.3+
		uपूर्णांक8_t SST_SPLIT_SDP_CAP:1;                   // bit 1: DP 1.4
		uपूर्णांक8_t AV_SYNC_CAP:1;                         // bit 2: DP 1.3+
		uपूर्णांक8_t VSC_SDP_COLORIMETRY_SUPPORTED:1;       // bit 3: DP 1.3+
		uपूर्णांक8_t VSC_EXT_VESA_SDP_SUPPORTED:1;          // bit 4: DP 1.4
		uपूर्णांक8_t VSC_EXT_VESA_SDP_CHAINING_SUPPORTED:1; // bit 5: DP 1.4
		uपूर्णांक8_t VSC_EXT_CEA_SDP_SUPPORTED:1;           // bit 6: DP 1.4
		uपूर्णांक8_t VSC_EXT_CEA_SDP_CHAINING_SUPPORTED:1;  // bit 7: DP 1.4
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ training_aux_rd_पूर्णांकerval अणु
	काष्ठा अणु
		uपूर्णांक8_t TRAINIG_AUX_RD_INTERVAL:7;
		uपूर्णांक8_t EXT_RECEIVER_CAP_FIELD_PRESENT:1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/* Automated test काष्ठाures */
जोड़ test_request अणु
	काष्ठा अणु
	uपूर्णांक8_t LINK_TRAINING                :1;
	uपूर्णांक8_t LINK_TEST_PATTRN             :1;
	uपूर्णांक8_t EDID_READ                    :1;
	uपूर्णांक8_t PHY_TEST_PATTERN             :1;
	uपूर्णांक8_t RESERVED                     :1;
	uपूर्णांक8_t AUDIO_TEST_PATTERN           :1;
	uपूर्णांक8_t TEST_AUDIO_DISABLED_VIDEO    :1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ test_response अणु
	काष्ठा अणु
		uपूर्णांक8_t ACK         :1;
		uपूर्णांक8_t NO_ACK      :1;
		uपूर्णांक8_t EDID_CHECKSUM_WRITE:1;
		uपूर्णांक8_t RESERVED    :5;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ phy_test_pattern अणु
	काष्ठा अणु
		/* DpcdPhyTestPatterns. This field is 2 bits क्रम DP1.1
		 * and 3 bits क्रम DP1.2.
		 */
		uपूर्णांक8_t PATTERN     :3;
		/* BY speci, bit7:2 is 0 क्रम DP1.1. */
		uपूर्णांक8_t RESERVED    :5;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/* States of Compliance Test Specअगरication (CTS DP1.2). */
जोड़ compliance_test_state अणु
	काष्ठा अणु
		अचिन्हित अक्षर STEREO_3D_RUNNING        : 1;
		अचिन्हित अक्षर RESERVED                 : 7;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

जोड़ link_test_pattern अणु
	काष्ठा अणु
		/* dpcd_link_test_patterns */
		अचिन्हित अक्षर PATTERN :2;
		अचिन्हित अक्षर RESERVED:6;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

जोड़ test_misc अणु
	काष्ठा dpcd_test_misc_bits अणु
		अचिन्हित अक्षर SYNC_CLOCK  :1;
		/* dpcd_test_color_क्रमmat */
		अचिन्हित अक्षर CLR_FORMAT  :2;
		/* dpcd_test_dyn_range */
		अचिन्हित अक्षर DYN_RANGE   :1;
		अचिन्हित अक्षर YCBCR_COEFS :1;
		/* dpcd_test_bit_depth */
		अचिन्हित अक्षर BPC         :3;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

जोड़ audio_test_mode अणु
	काष्ठा अणु
		अचिन्हित अक्षर sampling_rate   :4;
		अचिन्हित अक्षर channel_count   :4;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

जोड़ audio_test_pattern_period अणु
	काष्ठा अणु
		अचिन्हित अक्षर pattern_period   :4;
		अचिन्हित अक्षर reserved         :4;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

काष्ठा audio_test_pattern_type अणु
	अचिन्हित अक्षर value;
पूर्ण;

काष्ठा dp_audio_test_data_flags अणु
	uपूर्णांक8_t test_requested  :1;
	uपूर्णांक8_t disable_video   :1;
पूर्ण;

काष्ठा dp_audio_test_data अणु

	काष्ठा dp_audio_test_data_flags flags;
	uपूर्णांक8_t sampling_rate;
	uपूर्णांक8_t channel_count;
	uपूर्णांक8_t pattern_type;
	uपूर्णांक8_t pattern_period[8];
पूर्ण;

/* FEC capability DPCD रेजिस्टर field bits-*/
जोड़ dpcd_fec_capability अणु
	काष्ठा अणु
		uपूर्णांक8_t FEC_CAPABLE:1;
		uपूर्णांक8_t UNCORRECTED_BLOCK_ERROR_COUNT_CAPABLE:1;
		uपूर्णांक8_t CORRECTED_BLOCK_ERROR_COUNT_CAPABLE:1;
		uपूर्णांक8_t BIT_ERROR_COUNT_CAPABLE:1;
		uपूर्णांक8_t RESERVED:4;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

/* DSC capability DPCD रेजिस्टर field bits-*/
काष्ठा dpcd_dsc_support अणु
	uपूर्णांक8_t DSC_SUPPORT		:1;
	uपूर्णांक8_t DSC_PASSTHROUGH_SUPPORT	:1;
	uपूर्णांक8_t RESERVED		:6;
पूर्ण;

काष्ठा dpcd_dsc_algorithm_revision अणु
	uपूर्णांक8_t DSC_VERSION_MAJOR	:4;
	uपूर्णांक8_t DSC_VERSION_MINOR	:4;
पूर्ण;

काष्ठा dpcd_dsc_rc_buffer_block_size अणु
	uपूर्णांक8_t RC_BLOCK_BUFFER_SIZE	:2;
	uपूर्णांक8_t RESERVED		:6;
पूर्ण;

काष्ठा dpcd_dsc_slice_capability1 अणु
	uपूर्णांक8_t ONE_SLICE_PER_DP_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t TWO_SLICES_PER_DP_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t RESERVED				:1;
	uपूर्णांक8_t FOUR_SLICES_PER_DP_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t SIX_SLICES_PER_DP_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t EIGHT_SLICES_PER_DP_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t TEN_SLICES_PER_DP_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t TWELVE_SLICES_PER_DP_DSC_SINK_DEVICE	:1;
पूर्ण;

काष्ठा dpcd_dsc_line_buffer_bit_depth अणु
	uपूर्णांक8_t LINE_BUFFER_BIT_DEPTH	:4;
	uपूर्णांक8_t RESERVED		:4;
पूर्ण;

काष्ठा dpcd_dsc_block_prediction_support अणु
	uपूर्णांक8_t BLOCK_PREDICTION_SUPPORT:1;
	uपूर्णांक8_t RESERVED		:7;
पूर्ण;

काष्ठा dpcd_maximum_bits_per_pixel_supported_by_the_decompressor अणु
	uपूर्णांक8_t MAXIMUM_BITS_PER_PIXEL_SUPPORTED_BY_THE_DECOMPRESSOR_LOW	:7;
	uपूर्णांक8_t MAXIMUM_BITS_PER_PIXEL_SUPPORTED_BY_THE_DECOMPRESSOR_HIGH	:7;
	uपूर्णांक8_t RESERVED							:2;
पूर्ण;

काष्ठा dpcd_dsc_decoder_color_क्रमmat_capabilities अणु
	uपूर्णांक8_t RGB_SUPPORT			:1;
	uपूर्णांक8_t Y_CB_CR_444_SUPPORT		:1;
	uपूर्णांक8_t Y_CB_CR_SIMPLE_422_SUPPORT	:1;
	uपूर्णांक8_t Y_CB_CR_NATIVE_422_SUPPORT	:1;
	uपूर्णांक8_t Y_CB_CR_NATIVE_420_SUPPORT	:1;
	uपूर्णांक8_t RESERVED			:3;
पूर्ण;

काष्ठा dpcd_dsc_decoder_color_depth_capabilities अणु
	uपूर्णांक8_t RESERVED0			:1;
	uपूर्णांक8_t EIGHT_BITS_PER_COLOR_SUPPORT	:1;
	uपूर्णांक8_t TEN_BITS_PER_COLOR_SUPPORT	:1;
	uपूर्णांक8_t TWELVE_BITS_PER_COLOR_SUPPORT	:1;
	uपूर्णांक8_t RESERVED1			:4;
पूर्ण;

काष्ठा dpcd_peak_dsc_throughput_dsc_sink अणु
	uपूर्णांक8_t THROUGHPUT_MODE_0:4;
	uपूर्णांक8_t THROUGHPUT_MODE_1:4;
पूर्ण;

काष्ठा dpcd_dsc_slice_capabilities_2 अणु
	uपूर्णांक8_t SIXTEEN_SLICES_PER_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t TWENTY_SLICES_PER_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t TWENTYFOUR_SLICES_PER_DSC_SINK_DEVICE	:1;
	uपूर्णांक8_t RESERVED				:5;
पूर्ण;

काष्ठा dpcd_bits_per_pixel_incrementअणु
	uपूर्णांक8_t INCREMENT_OF_BITS_PER_PIXEL_SUPPORTED	:3;
	uपूर्णांक8_t RESERVED				:5;
पूर्ण;
जोड़ dpcd_dsc_basic_capabilities अणु
	काष्ठा अणु
		काष्ठा dpcd_dsc_support dsc_support;
		काष्ठा dpcd_dsc_algorithm_revision dsc_algorithm_revision;
		काष्ठा dpcd_dsc_rc_buffer_block_size dsc_rc_buffer_block_size;
		uपूर्णांक8_t dsc_rc_buffer_size;
		काष्ठा dpcd_dsc_slice_capability1 dsc_slice_capabilities_1;
		काष्ठा dpcd_dsc_line_buffer_bit_depth dsc_line_buffer_bit_depth;
		काष्ठा dpcd_dsc_block_prediction_support dsc_block_prediction_support;
		काष्ठा dpcd_maximum_bits_per_pixel_supported_by_the_decompressor maximum_bits_per_pixel_supported_by_the_decompressor;
		काष्ठा dpcd_dsc_decoder_color_क्रमmat_capabilities dsc_decoder_color_क्रमmat_capabilities;
		काष्ठा dpcd_dsc_decoder_color_depth_capabilities dsc_decoder_color_depth_capabilities;
		काष्ठा dpcd_peak_dsc_throughput_dsc_sink peak_dsc_throughput_dsc_sink;
		uपूर्णांक8_t dsc_maximum_slice_width;
		काष्ठा dpcd_dsc_slice_capabilities_2 dsc_slice_capabilities_2;
		uपूर्णांक8_t reserved;
		काष्ठा dpcd_bits_per_pixel_increment bits_per_pixel_increment;
	पूर्ण fields;
	uपूर्णांक8_t raw[16];
पूर्ण;

जोड़ dpcd_dsc_branch_decoder_capabilities अणु
	काष्ठा अणु
		uपूर्णांक8_t BRANCH_OVERALL_THROUGHPUT_0;
		uपूर्णांक8_t BRANCH_OVERALL_THROUGHPUT_1;
		uपूर्णांक8_t BRANCH_MAX_LINE_WIDTH;
	पूर्ण fields;
	uपूर्णांक8_t raw[3];
पूर्ण;

काष्ठा dpcd_dsc_capabilities अणु
	जोड़ dpcd_dsc_basic_capabilities dsc_basic_caps;
	जोड़ dpcd_dsc_branch_decoder_capabilities dsc_branch_decoder_caps;
पूर्ण;

/* These parameters are from PSR capabilities reported by Sink DPCD */
काष्ठा psr_caps अणु
	अचिन्हित अक्षर psr_version;
	अचिन्हित पूर्णांक psr_rfb_setup_समय;
	bool psr_निकास_link_training_required;
पूर्ण;

#पूर्ण_अगर /* DC_DP_TYPES_H */
