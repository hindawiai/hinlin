<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
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

#समावेश <linux/delay.h>

#समावेश "dc_bios_types.h"
#समावेश "dcn10_stream_encoder.h"
#समावेश "reg_helper.h"
#समावेश "hw_shared.h"

#घोषणा DC_LOGGER \
		enc1->base.ctx->logger


#घोषणा REG(reg)\
	(enc1->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	enc1->se_shअगरt->field_name, enc1->se_mask->field_name

#घोषणा VBI_LINE_0 0
#घोषणा DP_BLANK_MAX_RETRY 20
#घोषणा HDMI_CLOCK_CHANNEL_RATE_MORE_340M 340000


क्रमागत अणु
	DP_MST_UPDATE_MAX_RETRY = 50
पूर्ण;

#घोषणा CTX \
	enc1->base.ctx

व्योम enc1_update_generic_info_packet(
	काष्ठा dcn10_stream_encoder *enc1,
	uपूर्णांक32_t packet_index,
	स्थिर काष्ठा dc_info_packet *info_packet)
अणु
	uपूर्णांक32_t regval;
	/* TODOFPGA Figure out a proper number क्रम max_retries polling क्रम lock
	 * use 50 क्रम now.
	 */
	uपूर्णांक32_t max_retries = 50;

	/*we need turn on घड़ी beक्रमe programming AFMT block*/
	REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

	अगर (packet_index >= 8)
		ASSERT(0);

	/* poll dig_update_lock is not locked -> asic पूर्णांकernal संकेत
	 * assume otg master lock will unlock it
	 */
/*		REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_LOCK_STATUS,
			0, 10, max_retries);*/

	/* check अगर HW पढ़ोing GSP memory */
	REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT,
			0, 10, max_retries);

	/* HW करोes is not पढ़ोing GSP memory not पढ़ोing too दीर्घ ->
	 * something wrong. clear GPS memory access and notअगरy?
	 * hw SW is writing to GSP memory
	 */
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT_CLR, 1);

	/* choose which generic packet to use */
	regval = REG_READ(AFMT_VBI_PACKET_CONTROL);
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL,
			AFMT_GENERIC_INDEX, packet_index);

	/* ग_लिखो generic packet header
	 * (4th byte is क्रम GENERIC0 only)
	 */
	REG_SET_4(AFMT_GENERIC_HDR, 0,
			AFMT_GENERIC_HB0, info_packet->hb0,
			AFMT_GENERIC_HB1, info_packet->hb1,
			AFMT_GENERIC_HB2, info_packet->hb2,
			AFMT_GENERIC_HB3, info_packet->hb3);

	/* ग_लिखो generic packet contents
	 * (we never use last 4 bytes)
	 * there are 8 (0-7) mmDIG0_AFMT_GENERIC0_x रेजिस्टरs
	 */
	अणु
		स्थिर uपूर्णांक32_t *content =
			(स्थिर uपूर्णांक32_t *) &info_packet->sb[0];

		REG_WRITE(AFMT_GENERIC_0, *content++);
		REG_WRITE(AFMT_GENERIC_1, *content++);
		REG_WRITE(AFMT_GENERIC_2, *content++);
		REG_WRITE(AFMT_GENERIC_3, *content++);
		REG_WRITE(AFMT_GENERIC_4, *content++);
		REG_WRITE(AFMT_GENERIC_5, *content++);
		REG_WRITE(AFMT_GENERIC_6, *content++);
		REG_WRITE(AFMT_GENERIC_7, *content);
	पूर्ण

	चयन (packet_index) अणु
	हाल 0:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC0_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 1:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC1_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 2:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC2_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 3:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC3_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 4:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC4_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 5:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC5_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 6:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC6_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 7:
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
				AFMT_GENERIC7_IMMEDIATE_UPDATE, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enc1_update_hdmi_info_packet(
	काष्ठा dcn10_stream_encoder *enc1,
	uपूर्णांक32_t packet_index,
	स्थिर काष्ठा dc_info_packet *info_packet)
अणु
	uपूर्णांक32_t cont, send, line;

	अगर (info_packet->valid) अणु
		enc1_update_generic_info_packet(
			enc1,
			packet_index,
			info_packet);

		/* enable transmission of packet(s) -
		 * packet transmission begins on the next frame
		 */
		cont = 1;
		/* send packet(s) every frame */
		send = 1;
		/* select line number to send packets on */
		line = 2;
	पूर्ण अन्यथा अणु
		cont = 0;
		send = 0;
		line = 0;
	पूर्ण

	/* choose which generic packet control to use */
	चयन (packet_index) अणु
	हाल 0:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC0_CONT, cont,
				HDMI_GENERIC0_SEND, send,
				HDMI_GENERIC0_LINE, line);
		अवरोध;
	हाल 1:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC1_CONT, cont,
				HDMI_GENERIC1_SEND, send,
				HDMI_GENERIC1_LINE, line);
		अवरोध;
	हाल 2:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL1,
				HDMI_GENERIC0_CONT, cont,
				HDMI_GENERIC0_SEND, send,
				HDMI_GENERIC0_LINE, line);
		अवरोध;
	हाल 3:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL1,
				HDMI_GENERIC1_CONT, cont,
				HDMI_GENERIC1_SEND, send,
				HDMI_GENERIC1_LINE, line);
		अवरोध;
	हाल 4:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL2,
				HDMI_GENERIC0_CONT, cont,
				HDMI_GENERIC0_SEND, send,
				HDMI_GENERIC0_LINE, line);
		अवरोध;
	हाल 5:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL2,
				HDMI_GENERIC1_CONT, cont,
				HDMI_GENERIC1_SEND, send,
				HDMI_GENERIC1_LINE, line);
		अवरोध;
	हाल 6:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL3,
				HDMI_GENERIC0_CONT, cont,
				HDMI_GENERIC0_SEND, send,
				HDMI_GENERIC0_LINE, line);
		अवरोध;
	हाल 7:
		REG_UPDATE_3(HDMI_GENERIC_PACKET_CONTROL3,
				HDMI_GENERIC1_CONT, cont,
				HDMI_GENERIC1_SEND, send,
				HDMI_GENERIC1_LINE, line);
		अवरोध;
	शेष:
		/* invalid HW packet index */
		DC_LOG_WARNING(
			"Invalid HW packet index: %s()\n",
			__func__);
		वापस;
	पूर्ण
पूर्ण

/* setup stream encoder in dp mode */
व्योम enc1_stream_encoder_dp_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	क्रमागत dc_color_space output_color_space,
	bool use_vsc_sdp_क्रम_colorimetry,
	uपूर्णांक32_t enable_sdp_splitting)
अणु
	uपूर्णांक32_t h_active_start;
	uपूर्णांक32_t v_active_start;
	uपूर्णांक32_t misc0 = 0;
	uपूर्णांक32_t misc1 = 0;
	uपूर्णांक32_t h_blank;
	uपूर्णांक32_t h_back_porch;
	uपूर्णांक8_t synchronous_घड़ी = 0; /* asynchronous mode */
	uपूर्णांक8_t colorimetry_bpc;
	uपूर्णांक8_t dynamic_range_rgb = 0; /*full range*/
	uपूर्णांक8_t dynamic_range_ycbcr = 1; /*bt709*/
	uपूर्णांक8_t dp_pixel_encoding = 0;
	uपूर्णांक8_t dp_component_depth = 0;

	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	काष्ठा dc_crtc_timing hw_crtc_timing = *crtc_timing;

	अगर (hw_crtc_timing.flags.INTERLACE) अणु
		/*the input timing is in VESA spec क्रमmat with Interlace flag =1*/
		hw_crtc_timing.v_total /= 2;
		hw_crtc_timing.v_border_top /= 2;
		hw_crtc_timing.v_addressable /= 2;
		hw_crtc_timing.v_border_bottom /= 2;
		hw_crtc_timing.v_front_porch /= 2;
		hw_crtc_timing.v_sync_width /= 2;
	पूर्ण


	/* set pixel encoding */
	चयन (hw_crtc_timing.pixel_encoding) अणु
	हाल PIXEL_ENCODING_YCBCR422:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_YCBCR422;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR444:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_YCBCR444;

		अगर (hw_crtc_timing.flags.Y_ONLY)
			अगर (hw_crtc_timing.display_color_depth != COLOR_DEPTH_666)
				/* HW testing only, no use हाल yet.
				 * Color depth of Y-only could be
				 * 8, 10, 12, 16 bits
				 */
				dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_Y_ONLY;

		/* Note: DP_MSA_MISC1 bit 7 is the indicator
		 * of Y-only mode.
		 * This bit is set in HW अगर रेजिस्टर
		 * DP_PIXEL_ENCODING is programmed to 0x4
		 */
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_YCBCR420;
		अवरोध;
	शेष:
		dp_pixel_encoding = DP_PIXEL_ENCODING_TYPE_RGB444;
		अवरोध;
	पूर्ण

	misc1 = REG_READ(DP_MSA_MISC);
	/* For YCbCr420 and BT2020 Colorimetry Formats, VSC SDP shall be used.
	 * When MISC1, bit 6, is Set to 1, a Source device uses a VSC SDP to indicate the
	 * Pixel Encoding/Colorimetry Format and that a Sink device shall ignore MISC1, bit 7,
	 * and MISC0, bits 7:1 (MISC1, bit 7, and MISC0, bits 7:1, become "don't care").
	 */
	अगर (use_vsc_sdp_क्रम_colorimetry)
		misc1 = misc1 | 0x40;
	अन्यथा
		misc1 = misc1 & ~0x40;

	/* set color depth */
	चयन (hw_crtc_timing.display_color_depth) अणु
	हाल COLOR_DEPTH_666:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_6BPC;
		अवरोध;
	हाल COLOR_DEPTH_888:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_8BPC;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_10BPC;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_12BPC;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_16BPC;
		अवरोध;
	शेष:
		dp_component_depth = DP_COMPONENT_PIXEL_DEPTH_6BPC;
		अवरोध;
	पूर्ण

	/* Set DP pixel encoding and component depth */
	REG_UPDATE_2(DP_PIXEL_FORMAT,
			DP_PIXEL_ENCODING, dp_pixel_encoding,
			DP_COMPONENT_DEPTH, dp_component_depth);

	/* set dynamic range and YCbCr range */

	चयन (hw_crtc_timing.display_color_depth) अणु
	हाल COLOR_DEPTH_666:
		colorimetry_bpc = 0;
		अवरोध;
	हाल COLOR_DEPTH_888:
		colorimetry_bpc = 1;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		colorimetry_bpc = 2;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		colorimetry_bpc = 3;
		अवरोध;
	शेष:
		colorimetry_bpc = 0;
		अवरोध;
	पूर्ण

	misc0 = misc0 | synchronous_घड़ी;
	misc0 = colorimetry_bpc << 5;

	चयन (output_color_space) अणु
	हाल COLOR_SPACE_SRGB:
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_rgb = 0; /*full range*/
		अवरोध;
	हाल COLOR_SPACE_SRGB_LIMITED:
		misc0 = misc0 | 0x8; /* bit3=1 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_rgb = 1; /*limited range*/
		अवरोध;
	हाल COLOR_SPACE_YCBCR601:
	हाल COLOR_SPACE_YCBCR601_LIMITED:
		misc0 = misc0 | 0x8; /* bit3=1, bit4=0 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_ycbcr = 0; /*bt601*/
		अगर (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
			misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
		अन्यथा अगर (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR444)
			misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
		अवरोध;
	हाल COLOR_SPACE_YCBCR709:
	हाल COLOR_SPACE_YCBCR709_LIMITED:
		misc0 = misc0 | 0x18; /* bit3=1, bit4=1 */
		misc1 = misc1 & ~0x80; /* bit7 = 0*/
		dynamic_range_ycbcr = 1; /*bt709*/
		अगर (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
			misc0 = misc0 | 0x2; /* bit2=0, bit1=1 */
		अन्यथा अगर (hw_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR444)
			misc0 = misc0 | 0x4; /* bit2=1, bit1=0 */
		अवरोध;
	हाल COLOR_SPACE_2020_RGB_LIMITEDRANGE:
		dynamic_range_rgb = 1; /*limited range*/
		अवरोध;
	हाल COLOR_SPACE_2020_RGB_FULLRANGE:
	हाल COLOR_SPACE_2020_YCBCR:
	हाल COLOR_SPACE_XR_RGB:
	हाल COLOR_SPACE_MSREF_SCRGB:
	हाल COLOR_SPACE_ADOBERGB:
	हाल COLOR_SPACE_DCIP3:
	हाल COLOR_SPACE_XV_YCC_709:
	हाल COLOR_SPACE_XV_YCC_601:
	हाल COLOR_SPACE_DISPLAYNATIVE:
	हाल COLOR_SPACE_DOLBYVISION:
	हाल COLOR_SPACE_APPCTRL:
	हाल COLOR_SPACE_CUSTOMPOINTS:
	हाल COLOR_SPACE_UNKNOWN:
	हाल COLOR_SPACE_YCBCR709_BLACK:
		/* करो nothing */
		अवरोध;
	पूर्ण

	REG_SET(DP_MSA_COLORIMETRY, 0, DP_MSA_MISC0, misc0);
	REG_WRITE(DP_MSA_MISC, misc1);   /* MSA_MISC1 */

	/* dcn new रेजिस्टर
	 * dc_crtc_timing is vesa dmt काष्ठा. data from edid
	 */
	REG_SET_2(DP_MSA_TIMING_PARAM1, 0,
			DP_MSA_HTOTAL, hw_crtc_timing.h_total,
			DP_MSA_VTOTAL, hw_crtc_timing.v_total);

	/* calculate from vesa timing parameters
	 * h_active_start related to leading edge of sync
	 */

	h_blank = hw_crtc_timing.h_total - hw_crtc_timing.h_border_left -
			hw_crtc_timing.h_addressable - hw_crtc_timing.h_border_right;

	h_back_porch = h_blank - hw_crtc_timing.h_front_porch -
			hw_crtc_timing.h_sync_width;

	/* start at beginning of left border */
	h_active_start = hw_crtc_timing.h_sync_width + h_back_porch;


	v_active_start = hw_crtc_timing.v_total - hw_crtc_timing.v_border_top -
			hw_crtc_timing.v_addressable - hw_crtc_timing.v_border_bottom -
			hw_crtc_timing.v_front_porch;


	/* start at beginning of left border */
	REG_SET_2(DP_MSA_TIMING_PARAM2, 0,
		DP_MSA_HSTART, h_active_start,
		DP_MSA_VSTART, v_active_start);

	REG_SET_4(DP_MSA_TIMING_PARAM3, 0,
			DP_MSA_HSYNCWIDTH,
			hw_crtc_timing.h_sync_width,
			DP_MSA_HSYNCPOLARITY,
			!hw_crtc_timing.flags.HSYNC_POSITIVE_POLARITY,
			DP_MSA_VSYNCWIDTH,
			hw_crtc_timing.v_sync_width,
			DP_MSA_VSYNCPOLARITY,
			!hw_crtc_timing.flags.VSYNC_POSITIVE_POLARITY);

	/* HWDITH include border or overscan */
	REG_SET_2(DP_MSA_TIMING_PARAM4, 0,
		DP_MSA_HWIDTH, hw_crtc_timing.h_border_left +
		hw_crtc_timing.h_addressable + hw_crtc_timing.h_border_right,
		DP_MSA_VHEIGHT, hw_crtc_timing.v_border_top +
		hw_crtc_timing.v_addressable + hw_crtc_timing.v_border_bottom);
पूर्ण

व्योम enc1_stream_encoder_set_stream_attribute_helper(
		काष्ठा dcn10_stream_encoder *enc1,
		काष्ठा dc_crtc_timing *crtc_timing)
अणु
	चयन (crtc_timing->pixel_encoding) अणु
	हाल PIXEL_ENCODING_YCBCR422:
		REG_UPDATE(DIG_FE_CNTL, TMDS_PIXEL_ENCODING, 1);
		अवरोध;
	शेष:
		REG_UPDATE(DIG_FE_CNTL, TMDS_PIXEL_ENCODING, 0);
		अवरोध;
	पूर्ण
	REG_UPDATE(DIG_FE_CNTL, TMDS_COLOR_FORMAT, 0);
पूर्ण

/* setup stream encoder in hdmi mode */
व्योम enc1_stream_encoder_hdmi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	पूर्णांक actual_pix_clk_khz,
	bool enable_audio)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	काष्ठा bp_encoder_control cntl = अणु0पूर्ण;

	cntl.action = ENCODER_CONTROL_SETUP;
	cntl.engine_id = enc1->base.id;
	cntl.संकेत = SIGNAL_TYPE_HDMI_TYPE_A;
	cntl.enable_dp_audio = enable_audio;
	cntl.pixel_घड़ी = actual_pix_clk_khz;
	cntl.lanes_number = LANE_COUNT_FOUR;

	अगर (enc1->base.bp->funcs->encoder_control(
			enc1->base.bp, &cntl) != BP_RESULT_OK)
		वापस;

	enc1_stream_encoder_set_stream_attribute_helper(enc1, crtc_timing);

	/* setup HDMI engine */
	REG_UPDATE_6(HDMI_CONTROL,
		HDMI_PACKET_GEN_VERSION, 1,
		HDMI_KEEPOUT_MODE, 1,
		HDMI_DEEP_COLOR_ENABLE, 0,
		HDMI_DATA_SCRAMBLE_EN, 0,
		HDMI_NO_EXTRA_शून्य_PACKET_FILLED, 1,
		HDMI_CLOCK_CHANNEL_RATE, 0);


	चयन (crtc_timing->display_color_depth) अणु
	हाल COLOR_DEPTH_888:
		REG_UPDATE(HDMI_CONTROL, HDMI_DEEP_COLOR_DEPTH, 0);
		अवरोध;
	हाल COLOR_DEPTH_101010:
		अगर (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 1,
					HDMI_DEEP_COLOR_ENABLE, 0);
		पूर्ण अन्यथा अणु
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 1,
					HDMI_DEEP_COLOR_ENABLE, 1);
			पूर्ण
		अवरोध;
	हाल COLOR_DEPTH_121212:
		अगर (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 2,
					HDMI_DEEP_COLOR_ENABLE, 0);
		पूर्ण अन्यथा अणु
			REG_UPDATE_2(HDMI_CONTROL,
					HDMI_DEEP_COLOR_DEPTH, 2,
					HDMI_DEEP_COLOR_ENABLE, 1);
			पूर्ण
		अवरोध;
	हाल COLOR_DEPTH_161616:
		REG_UPDATE_2(HDMI_CONTROL,
				HDMI_DEEP_COLOR_DEPTH, 3,
				HDMI_DEEP_COLOR_ENABLE, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (actual_pix_clk_khz >= HDMI_CLOCK_CHANNEL_RATE_MORE_340M) अणु
		/* enable HDMI data scrambler
		 * HDMI_CLOCK_CHANNEL_RATE_MORE_340M
		 * Clock channel frequency is 1/4 of अक्षरacter rate.
		 */
		REG_UPDATE_2(HDMI_CONTROL,
			HDMI_DATA_SCRAMBLE_EN, 1,
			HDMI_CLOCK_CHANNEL_RATE, 1);
	पूर्ण अन्यथा अगर (crtc_timing->flags.LTE_340MCSC_SCRAMBLE) अणु

		/* TODO: New feature क्रम DCE11, still need to implement */

		/* enable HDMI data scrambler
		 * HDMI_CLOCK_CHANNEL_FREQ_EQUAL_TO_CHAR_RATE
		 * Clock channel frequency is the same
		 * as अक्षरacter rate
		 */
		REG_UPDATE_2(HDMI_CONTROL,
			HDMI_DATA_SCRAMBLE_EN, 1,
			HDMI_CLOCK_CHANNEL_RATE, 0);
	पूर्ण


	REG_UPDATE_3(HDMI_VBI_PACKET_CONTROL,
		HDMI_GC_CONT, 1,
		HDMI_GC_SEND, 1,
		HDMI_शून्य_SEND, 1);

	/* following beदीर्घs to audio */
	REG_UPDATE(HDMI_INFOFRAME_CONTROL0, HDMI_AUDIO_INFO_SEND, 1);

	REG_UPDATE(AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, 1);

	REG_UPDATE(HDMI_INFOFRAME_CONTROL1, HDMI_AUDIO_INFO_LINE,
				VBI_LINE_0 + 2);

	REG_UPDATE(HDMI_GC, HDMI_GC_AVMUTE, 0);
पूर्ण

/* setup stream encoder in dvi mode */
व्योम enc1_stream_encoder_dvi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	bool is_dual_link)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	काष्ठा bp_encoder_control cntl = अणु0पूर्ण;

	cntl.action = ENCODER_CONTROL_SETUP;
	cntl.engine_id = enc1->base.id;
	cntl.संकेत = is_dual_link ?
			SIGNAL_TYPE_DVI_DUAL_LINK : SIGNAL_TYPE_DVI_SINGLE_LINK;
	cntl.enable_dp_audio = false;
	cntl.pixel_घड़ी = crtc_timing->pix_clk_100hz / 10;
	cntl.lanes_number = (is_dual_link) ? LANE_COUNT_EIGHT : LANE_COUNT_FOUR;

	अगर (enc1->base.bp->funcs->encoder_control(
			enc1->base.bp, &cntl) != BP_RESULT_OK)
		वापस;

	ASSERT(crtc_timing->pixel_encoding == PIXEL_ENCODING_RGB);
	ASSERT(crtc_timing->display_color_depth == COLOR_DEPTH_888);
	enc1_stream_encoder_set_stream_attribute_helper(enc1, crtc_timing);
पूर्ण

व्योम enc1_stream_encoder_set_throttled_vcp_size(
	काष्ठा stream_encoder *enc,
	काष्ठा fixed31_32 avg_समय_slots_per_mtp)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t x = dc_fixpt_न्यूनमान(
		avg_समय_slots_per_mtp);
	uपूर्णांक32_t y = dc_fixpt_उच्चमान(
		dc_fixpt_shl(
			dc_fixpt_sub_पूर्णांक(
				avg_समय_slots_per_mtp,
				x),
			26));

	REG_SET_2(DP_MSE_RATE_CNTL, 0,
		DP_MSE_RATE_X, x,
		DP_MSE_RATE_Y, y);

	/* रुको क्रम update to be completed on the link */
	/* i.e. DP_MSE_RATE_UPDATE_PENDING field (पढ़ो only) */
	/* is reset to 0 (not pending) */
	REG_WAIT(DP_MSE_RATE_UPDATE, DP_MSE_RATE_UPDATE_PENDING,
			0,
			10, DP_MST_UPDATE_MAX_RETRY);
पूर्ण

अटल व्योम enc1_stream_encoder_update_hdmi_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* क्रम bring up, disable dp द्विगुन  TODO */
	REG_UPDATE(HDMI_DB_CONTROL, HDMI_DB_DISABLE, 1);

	enc1_update_hdmi_info_packet(enc1, 0, &info_frame->avi);
	enc1_update_hdmi_info_packet(enc1, 1, &info_frame->venकरोr);
	enc1_update_hdmi_info_packet(enc1, 2, &info_frame->gamut);
	enc1_update_hdmi_info_packet(enc1, 3, &info_frame->spd);
	enc1_update_hdmi_info_packet(enc1, 4, &info_frame->hdrsmd);
पूर्ण

अटल व्योम enc1_stream_encoder_stop_hdmi_info_packets(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* stop generic packets 0 & 1 on HDMI */
	REG_SET_6(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC1_CONT, 0,
		HDMI_GENERIC1_LINE, 0,
		HDMI_GENERIC1_SEND, 0,
		HDMI_GENERIC0_CONT, 0,
		HDMI_GENERIC0_LINE, 0,
		HDMI_GENERIC0_SEND, 0);

	/* stop generic packets 2 & 3 on HDMI */
	REG_SET_6(HDMI_GENERIC_PACKET_CONTROL1, 0,
		HDMI_GENERIC0_CONT, 0,
		HDMI_GENERIC0_LINE, 0,
		HDMI_GENERIC0_SEND, 0,
		HDMI_GENERIC1_CONT, 0,
		HDMI_GENERIC1_LINE, 0,
		HDMI_GENERIC1_SEND, 0);

	/* stop generic packets 2 & 3 on HDMI */
	REG_SET_6(HDMI_GENERIC_PACKET_CONTROL2, 0,
		HDMI_GENERIC0_CONT, 0,
		HDMI_GENERIC0_LINE, 0,
		HDMI_GENERIC0_SEND, 0,
		HDMI_GENERIC1_CONT, 0,
		HDMI_GENERIC1_LINE, 0,
		HDMI_GENERIC1_SEND, 0);

	REG_SET_6(HDMI_GENERIC_PACKET_CONTROL3, 0,
		HDMI_GENERIC0_CONT, 0,
		HDMI_GENERIC0_LINE, 0,
		HDMI_GENERIC0_SEND, 0,
		HDMI_GENERIC1_CONT, 0,
		HDMI_GENERIC1_LINE, 0,
		HDMI_GENERIC1_SEND, 0);
पूर्ण

व्योम enc1_stream_encoder_update_dp_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t value = 0;

	अगर (info_frame->vsc.valid)
		enc1_update_generic_info_packet(
					enc1,
					0,  /* packetIndex */
					&info_frame->vsc);

	अगर (info_frame->spd.valid)
		enc1_update_generic_info_packet(
				enc1,
				2,  /* packetIndex */
				&info_frame->spd);

	अगर (info_frame->hdrsmd.valid)
		enc1_update_generic_info_packet(
				enc1,
				3,  /* packetIndex */
				&info_frame->hdrsmd);

	/* packetIndex 4 is used क्रम send immediate sdp message, and please
	 * use other packetIndex (such as 5,6) क्रम other info packet
	 */

	/* enable/disable transmission of packet(s).
	 * If enabled, packet transmission begins on the next frame
	 */
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_GSP0_ENABLE, info_frame->vsc.valid);
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_GSP2_ENABLE, info_frame->spd.valid);
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_GSP3_ENABLE, info_frame->hdrsmd.valid);

	/* This bit is the master enable bit.
	 * When enabling secondary stream engine,
	 * this master bit must also be set.
	 * This रेजिस्टर shared with audio info frame.
	 * Thereक्रमe we need to enable master bit
	 * अगर at least on of the fields is not 0
	 */
	value = REG_READ(DP_SEC_CNTL);
	अगर (value)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
पूर्ण

व्योम enc1_stream_encoder_send_immediate_sdp_message(
	काष्ठा stream_encoder *enc,
	स्थिर uपूर्णांक8_t *custom_sdp_message,
	अचिन्हित पूर्णांक sdp_message_size)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t value = 0;

	/* TODOFPGA Figure out a proper number क्रम max_retries polling क्रम lock
	 * use 50 क्रम now.
	 */
	uपूर्णांक32_t max_retries = 50;

	/* check अगर GSP4 is transmitted */
	REG_WAIT(DP_SEC_CNTL2, DP_SEC_GSP4_SEND_PENDING,
		0, 10, max_retries);

	/* disable GSP4 transmitting */
	REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP4_SEND, 0);

	/* transmit GSP4 at the earliest समय in a frame */
	REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP4_SEND_ANY_LINE, 1);

	/*we need turn on घड़ी beक्रमe programming AFMT block*/
	REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

	/* check अगर HW पढ़ोing GSP memory */
	REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT,
			0, 10, max_retries);

	/* HW करोes is not पढ़ोing GSP memory not पढ़ोing too दीर्घ ->
	 * something wrong. clear GPS memory access and notअगरy?
	 * hw SW is writing to GSP memory
	 */
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT_CLR, 1);

	/* use generic packet 4 क्रम immediate sdp message */
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL,
			AFMT_GENERIC_INDEX, 4);

	/* ग_लिखो generic packet header
	 * (4th byte is क्रम GENERIC0 only)
	 */
	REG_SET_4(AFMT_GENERIC_HDR, 0,
			AFMT_GENERIC_HB0, custom_sdp_message[0],
			AFMT_GENERIC_HB1, custom_sdp_message[1],
			AFMT_GENERIC_HB2, custom_sdp_message[2],
			AFMT_GENERIC_HB3, custom_sdp_message[3]);

	/* ग_लिखो generic packet contents
	 * (we never use last 4 bytes)
	 * there are 8 (0-7) mmDIG0_AFMT_GENERIC0_x रेजिस्टरs
	 */
	अणु
		स्थिर uपूर्णांक32_t *content =
			(स्थिर uपूर्णांक32_t *) &custom_sdp_message[4];

		REG_WRITE(AFMT_GENERIC_0, *content++);
		REG_WRITE(AFMT_GENERIC_1, *content++);
		REG_WRITE(AFMT_GENERIC_2, *content++);
		REG_WRITE(AFMT_GENERIC_3, *content++);
		REG_WRITE(AFMT_GENERIC_4, *content++);
		REG_WRITE(AFMT_GENERIC_5, *content++);
		REG_WRITE(AFMT_GENERIC_6, *content++);
		REG_WRITE(AFMT_GENERIC_7, *content);
	पूर्ण

	/* check whether GENERIC4 रेजिस्टरs द्विगुन buffer update in immediate mode
	 * is pending
	 */
	REG_WAIT(AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC4_IMMEDIATE_UPDATE_PENDING,
			0, 10, max_retries);

	/* atomically update द्विगुन-buffered GENERIC4 रेजिस्टरs in immediate mode
	 * (update immediately)
	 */
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL1,
			AFMT_GENERIC4_IMMEDIATE_UPDATE, 1);

	/* enable GSP4 transmitting */
	REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP4_SEND, 1);

	/* This bit is the master enable bit.
	 * When enabling secondary stream engine,
	 * this master bit must also be set.
	 * This रेजिस्टर shared with audio info frame.
	 * Thereक्रमe we need to enable master bit
	 * अगर at least on of the fields is not 0
	 */
	value = REG_READ(DP_SEC_CNTL);
	अगर (value)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
पूर्ण

व्योम enc1_stream_encoder_stop_dp_info_packets(
	काष्ठा stream_encoder *enc)
अणु
	/* stop generic packets on DP */
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t value = 0;

	REG_SET_10(DP_SEC_CNTL, 0,
		DP_SEC_GSP0_ENABLE, 0,
		DP_SEC_GSP1_ENABLE, 0,
		DP_SEC_GSP2_ENABLE, 0,
		DP_SEC_GSP3_ENABLE, 0,
		DP_SEC_GSP4_ENABLE, 0,
		DP_SEC_GSP5_ENABLE, 0,
		DP_SEC_GSP6_ENABLE, 0,
		DP_SEC_GSP7_ENABLE, 0,
		DP_SEC_MPG_ENABLE, 0,
		DP_SEC_STREAM_ENABLE, 0);

	/* this रेजिस्टर shared with audio info frame.
	 * thereक्रमe we need to keep master enabled
	 * अगर at least one of the fields is not 0 */
	value = REG_READ(DP_SEC_CNTL);
	अगर (value)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);

पूर्ण

व्योम enc1_stream_encoder_dp_blank(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t  reg1 = 0;
	uपूर्णांक32_t max_retries = DP_BLANK_MAX_RETRY * 10;

	/* Note: For CZ, we are changing driver शेष to disable
	 * stream deferred to next VBLANK. If results are positive, we
	 * will make the same change to all DCE versions. There are a
	 * handful of panels that cannot handle disable stream at
	 * HBLANK and will result in a white line flash across the
	 * screen on stream disable.
	 */
	REG_GET(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, &reg1);
	अगर ((reg1 & 0x1) == 0)
		/*stream not enabled*/
		वापस;
	/* Specअगरy the video stream disable poपूर्णांक
	 * (2 = start of the next vertical blank)
	 */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_DIS_DEFER, 2);
	/* Larger delay to रुको until VBLANK - use max retry of
	 * 10us*10200=102ms. This covers 100.0ms of minimum 10 Hz mode +
	 * a little more because we may not trust delay accuracy.
	 */
	max_retries = DP_BLANK_MAX_RETRY * 501;

	/* disable DP stream */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, 0);

	/* the encoder stops sending the video stream
	 * at the start of the vertical blanking.
	 * Poll क्रम DP_VID_STREAM_STATUS == 0
	 */

	REG_WAIT(DP_VID_STREAM_CNTL, DP_VID_STREAM_STATUS,
			0,
			10, max_retries);

	/* Tell the DP encoder to ignore timing from CRTC, must be करोne after
	 * the polling. If we set DP_STEER_FIFO_RESET beक्रमe DP stream blank is
	 * complete, stream status will be stuck in video stream enabled state,
	 * i.e. DP_VID_STREAM_STATUS stuck at 1.
	 */

	REG_UPDATE(DP_STEER_FIFO, DP_STEER_FIFO_RESET, true);
पूर्ण

/* output video stream to link encoder */
व्योम enc1_stream_encoder_dp_unblank(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_unblank_param *param)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (param->link_settings.link_rate != LINK_RATE_UNKNOWN) अणु
		uपूर्णांक32_t n_vid = 0x8000;
		uपूर्णांक32_t m_vid;
		uपूर्णांक32_t n_multiply = 0;
		uपूर्णांक64_t m_vid_l = n_vid;

		/* YCbCr 4:2:0 : Computed VID_M will be 2X the input rate */
		अगर (param->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
			/*this param->pixel_clk_khz is half of 444 rate क्रम 420 alपढ़ोy*/
			n_multiply = 1;
		पूर्ण
		/* M / N = Fstream / Flink
		 * m_vid / n_vid = pixel rate / link rate
		 */

		m_vid_l *= param->timing.pix_clk_100hz / 10;
		m_vid_l = भाग_u64(m_vid_l,
			param->link_settings.link_rate
				* LINK_RATE_REF_FREQ_IN_KHZ);

		m_vid = (uपूर्णांक32_t) m_vid_l;

		/* enable स्वतः measurement */

		REG_UPDATE(DP_VID_TIMING, DP_VID_M_N_GEN_EN, 0);

		/* स्वतः measurement need 1 full 0x8000 symbol cycle to kick in,
		 * thereक्रमe program initial value क्रम Mvid and Nvid
		 */

		REG_UPDATE(DP_VID_N, DP_VID_N, n_vid);

		REG_UPDATE(DP_VID_M, DP_VID_M, m_vid);

		REG_UPDATE_2(DP_VID_TIMING,
				DP_VID_M_N_GEN_EN, 1,
				DP_VID_N_MUL, n_multiply);
	पूर्ण

	/* set DIG_START to 0x1 to resync FIFO */

	REG_UPDATE(DIG_FE_CNTL, DIG_START, 1);

	/* चयन DP encoder to CRTC data */

	REG_UPDATE(DP_STEER_FIFO, DP_STEER_FIFO_RESET, 0);

	/* रुको 100us क्रम DIG/DP logic to prime
	 * (i.e. a few video lines)
	 */
	udelay(100);

	/* the hardware would start sending video at the start of the next DP
	 * frame (i.e. rising edge of the vblank).
	 * NOTE: We used to program DP_VID_STREAM_DIS_DEFER = 2 here, but this
	 * रेजिस्टर has no effect on enable transition! HW always guarantees
	 * VID_STREAM enable at start of next frame, and this is not
	 * programmable
	 */

	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, true);
पूर्ण

व्योम enc1_stream_encoder_set_avmute(
	काष्ठा stream_encoder *enc,
	bool enable)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	अचिन्हित पूर्णांक value = enable ? 1 : 0;

	REG_UPDATE(HDMI_GC, HDMI_GC_AVMUTE, value);
पूर्ण

व्योम enc1_reset_hdmi_stream_attribute(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_UPDATE_5(HDMI_CONTROL,
		HDMI_PACKET_GEN_VERSION, 1,
		HDMI_KEEPOUT_MODE, 1,
		HDMI_DEEP_COLOR_ENABLE, 0,
		HDMI_DATA_SCRAMBLE_EN, 0,
		HDMI_CLOCK_CHANNEL_RATE, 0);
पूर्ण


#घोषणा DP_SEC_AUD_N__DP_SEC_AUD_N__DEFAULT 0x8000
#घोषणा DP_SEC_TIMESTAMP__DP_SEC_TIMESTAMP_MODE__AUTO_CALC 1

#समावेश "include/audio_types.h"


/* 25.2MHz/1.001*/
/* 25.2MHz/1.001*/
/* 25.2MHz*/
/* 27MHz */
/* 27MHz*1.001*/
/* 27MHz*1.001*/
/* 54MHz*/
/* 54MHz*1.001*/
/* 74.25MHz/1.001*/
/* 74.25MHz*/
/* 148.5MHz/1.001*/
/* 148.5MHz*/

अटल स्थिर काष्ठा audio_घड़ी_info audio_घड़ी_info_table[16] = अणु
	अणु2517, 4576, 28125, 7007, 31250, 6864, 28125पूर्ण,
	अणु2518, 4576, 28125, 7007, 31250, 6864, 28125पूर्ण,
	अणु2520, 4096, 25200, 6272, 28000, 6144, 25200पूर्ण,
	अणु2700, 4096, 27000, 6272, 30000, 6144, 27000पूर्ण,
	अणु2702, 4096, 27027, 6272, 30030, 6144, 27027पूर्ण,
	अणु2703, 4096, 27027, 6272, 30030, 6144, 27027पूर्ण,
	अणु5400, 4096, 54000, 6272, 60000, 6144, 54000पूर्ण,
	अणु5405, 4096, 54054, 6272, 60060, 6144, 54054पूर्ण,
	अणु7417, 11648, 210937, 17836, 234375, 11648, 140625पूर्ण,
	अणु7425, 4096, 74250, 6272, 82500, 6144, 74250पूर्ण,
	अणु14835, 11648, 421875, 8918, 234375, 5824, 140625पूर्ण,
	अणु14850, 4096, 148500, 6272, 165000, 6144, 148500पूर्ण,
	अणु29670, 5824, 421875, 4459, 234375, 5824, 281250पूर्ण,
	अणु29700, 3072, 222750, 4704, 247500, 5120, 247500पूर्ण,
	अणु59340, 5824, 843750, 8918, 937500, 5824, 562500पूर्ण,
	अणु59400, 3072, 445500, 9408, 990000, 6144, 594000पूर्ण
पूर्ण;

अटल स्थिर काष्ठा audio_घड़ी_info audio_घड़ी_info_table_36bpc[14] = अणु
	अणु2517,  9152,  84375,  7007,  48875,  9152,  56250पूर्ण,
	अणु2518,  9152,  84375,  7007,  48875,  9152,  56250पूर्ण,
	अणु2520,  4096,  37800,  6272,  42000,  6144,  37800पूर्ण,
	अणु2700,  4096,  40500,  6272,  45000,  6144,  40500पूर्ण,
	अणु2702,  8192,  81081,  6272,  45045,  8192,  54054पूर्ण,
	अणु2703,  8192,  81081,  6272,  45045,  8192,  54054पूर्ण,
	अणु5400,  4096,  81000,  6272,  90000,  6144,  81000पूर्ण,
	अणु5405,  4096,  81081,  6272,  90090,  6144,  81081पूर्ण,
	अणु7417, 11648, 316406, 17836, 351562, 11648, 210937पूर्ण,
	अणु7425, 4096, 111375,  6272, 123750,  6144, 111375पूर्ण,
	अणु14835, 11648, 632812, 17836, 703125, 11648, 421875पूर्ण,
	अणु14850, 4096, 222750,  6272, 247500,  6144, 222750पूर्ण,
	अणु29670, 5824, 632812,  8918, 703125,  5824, 421875पूर्ण,
	अणु29700, 4096, 445500,  4704, 371250,  5120, 371250पूर्ण
पूर्ण;

अटल स्थिर काष्ठा audio_घड़ी_info audio_घड़ी_info_table_48bpc[14] = अणु
	अणु2517,  4576,  56250,  7007,  62500,  6864,  56250पूर्ण,
	अणु2518,  4576,  56250,  7007,  62500,  6864,  56250पूर्ण,
	अणु2520,  4096,  50400,  6272,  56000,  6144,  50400पूर्ण,
	अणु2700,  4096,  54000,  6272,  60000,  6144,  54000पूर्ण,
	अणु2702,  4096,  54054,  6267,  60060,  8192,  54054पूर्ण,
	अणु2703,  4096,  54054,  6272,  60060,  8192,  54054पूर्ण,
	अणु5400,  4096, 108000,  6272, 120000,  6144, 108000पूर्ण,
	अणु5405,  4096, 108108,  6272, 120120,  6144, 108108पूर्ण,
	अणु7417, 11648, 421875, 17836, 468750, 11648, 281250पूर्ण,
	अणु7425,  4096, 148500,  6272, 165000,  6144, 148500पूर्ण,
	अणु14835, 11648, 843750,  8918, 468750, 11648, 281250पूर्ण,
	अणु14850, 4096, 297000,  6272, 330000,  6144, 297000पूर्ण,
	अणु29670, 5824, 843750,  4459, 468750,  5824, 562500पूर्ण,
	अणु29700, 3072, 445500,  4704, 495000,  5120, 495000पूर्ण


पूर्ण;

अटल जोड़ audio_cea_channels speakers_to_channels(
	काष्ठा audio_speaker_flags speaker_flags)
अणु
	जोड़ audio_cea_channels cea_channels = अणु0पूर्ण;

	/* these are one to one */
	cea_channels.channels.FL = speaker_flags.FL_FR;
	cea_channels.channels.FR = speaker_flags.FL_FR;
	cea_channels.channels.LFE = speaker_flags.LFE;
	cea_channels.channels.FC = speaker_flags.FC;

	/* अगर Rear Left and Right exist move RC speaker to channel 7
	 * otherwise to channel 5
	 */
	अगर (speaker_flags.RL_RR) अणु
		cea_channels.channels.RL_RC = speaker_flags.RL_RR;
		cea_channels.channels.RR = speaker_flags.RL_RR;
		cea_channels.channels.RC_RLC_FLC = speaker_flags.RC;
	पूर्ण अन्यथा अणु
		cea_channels.channels.RL_RC = speaker_flags.RC;
	पूर्ण

	/* FRONT Left Right Center and REAR Left Right Center are exclusive */
	अगर (speaker_flags.FLC_FRC) अणु
		cea_channels.channels.RC_RLC_FLC = speaker_flags.FLC_FRC;
		cea_channels.channels.RRC_FRC = speaker_flags.FLC_FRC;
	पूर्ण अन्यथा अणु
		cea_channels.channels.RC_RLC_FLC = speaker_flags.RLC_RRC;
		cea_channels.channels.RRC_FRC = speaker_flags.RLC_RRC;
	पूर्ण

	वापस cea_channels;
पूर्ण

व्योम get_audio_घड़ी_info(
	क्रमागत dc_color_depth color_depth,
	uपूर्णांक32_t crtc_pixel_घड़ी_100Hz,
	uपूर्णांक32_t actual_pixel_घड़ी_100Hz,
	काष्ठा audio_घड़ी_info *audio_घड़ी_info)
अणु
	स्थिर काष्ठा audio_घड़ी_info *घड़ी_info;
	uपूर्णांक32_t index;
	uपूर्णांक32_t crtc_pixel_घड़ी_in_10khz = crtc_pixel_घड़ी_100Hz / 100;
	uपूर्णांक32_t audio_array_size;

	चयन (color_depth) अणु
	हाल COLOR_DEPTH_161616:
		घड़ी_info = audio_घड़ी_info_table_48bpc;
		audio_array_size = ARRAY_SIZE(
				audio_घड़ी_info_table_48bpc);
		अवरोध;
	हाल COLOR_DEPTH_121212:
		घड़ी_info = audio_घड़ी_info_table_36bpc;
		audio_array_size = ARRAY_SIZE(
				audio_घड़ी_info_table_36bpc);
		अवरोध;
	शेष:
		घड़ी_info = audio_घड़ी_info_table;
		audio_array_size = ARRAY_SIZE(
				audio_घड़ी_info_table);
		अवरोध;
	पूर्ण

	अगर (घड़ी_info != शून्य) अणु
		/* search क्रम exact pixel घड़ी in table */
		क्रम (index = 0; index < audio_array_size; index++) अणु
			अगर (घड़ी_info[index].pixel_घड़ी_in_10khz >
				crtc_pixel_घड़ी_in_10khz)
				अवरोध;  /* not match */
			अन्यथा अगर (घड़ी_info[index].pixel_घड़ी_in_10khz ==
					crtc_pixel_घड़ी_in_10khz) अणु
				/* match found */
				*audio_घड़ी_info = घड़ी_info[index];
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* not found */
	अगर (actual_pixel_घड़ी_100Hz == 0)
		actual_pixel_घड़ी_100Hz = crtc_pixel_घड़ी_100Hz;

	/* See HDMI spec  the table entry under
	 *  pixel घड़ी of "Other". */
	audio_घड़ी_info->pixel_घड़ी_in_10khz =
			actual_pixel_घड़ी_100Hz / 100;
	audio_घड़ी_info->cts_32khz = actual_pixel_घड़ी_100Hz / 10;
	audio_घड़ी_info->cts_44khz = actual_pixel_घड़ी_100Hz / 10;
	audio_घड़ी_info->cts_48khz = actual_pixel_घड़ी_100Hz / 10;

	audio_घड़ी_info->n_32khz = 4096;
	audio_घड़ी_info->n_44khz = 6272;
	audio_घड़ी_info->n_48khz = 6144;
पूर्ण

अटल व्योम enc1_se_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *audio_info)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	uपूर्णांक32_t channels = 0;

	ASSERT(audio_info);
	अगर (audio_info == शून्य)
		/* This should not happen.it करोes so we करोn't get BSOD*/
		वापस;

	channels = speakers_to_channels(audio_info->flags.speaker_flags).all;

	/* setup the audio stream source select (audio -> dig mapping) */
	REG_SET(AFMT_AUDIO_SRC_CONTROL, 0, AFMT_AUDIO_SRC_SELECT, az_inst);

	/* Channel allocation */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_CHANNEL_ENABLE, channels);
पूर्ण

अटल व्योम enc1_se_setup_hdmi_audio(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा audio_crtc_info *crtc_info)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	काष्ठा audio_घड़ी_info audio_घड़ी_info = अणु0पूर्ण;

	/* HDMI_AUDIO_PACKET_CONTROL */
	REG_UPDATE(HDMI_AUDIO_PACKET_CONTROL,
			HDMI_AUDIO_DELAY_EN, 1);

	/* AFMT_AUDIO_PACKET_CONTROL */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, 1);

	/* AFMT_AUDIO_PACKET_CONTROL2 */
	REG_UPDATE_2(AFMT_AUDIO_PACKET_CONTROL2,
			AFMT_AUDIO_LAYOUT_OVRD, 0,
			AFMT_60958_OSF_OVRD, 0);

	/* HDMI_ACR_PACKET_CONTROL */
	REG_UPDATE_3(HDMI_ACR_PACKET_CONTROL,
			HDMI_ACR_AUTO_SEND, 1,
			HDMI_ACR_SOURCE, 0,
			HDMI_ACR_AUDIO_PRIORITY, 0);

	/* Program audio घड़ी sample/regeneration parameters */
	get_audio_घड़ी_info(crtc_info->color_depth,
			     crtc_info->requested_pixel_घड़ी_100Hz,
			     crtc_info->calculated_pixel_घड़ी_100Hz,
			     &audio_घड़ी_info);
	DC_LOG_HW_AUDIO(
			"\n%s:Input::requested_pixel_clock_100Hz = %d"	\
			"calculated_pixel_clock_100Hz = %d \n", __func__,	\
			crtc_info->requested_pixel_घड़ी_100Hz,		\
			crtc_info->calculated_pixel_घड़ी_100Hz);

	/* HDMI_ACR_32_0__HDMI_ACR_CTS_32_MASK */
	REG_UPDATE(HDMI_ACR_32_0, HDMI_ACR_CTS_32, audio_घड़ी_info.cts_32khz);

	/* HDMI_ACR_32_1__HDMI_ACR_N_32_MASK */
	REG_UPDATE(HDMI_ACR_32_1, HDMI_ACR_N_32, audio_घड़ी_info.n_32khz);

	/* HDMI_ACR_44_0__HDMI_ACR_CTS_44_MASK */
	REG_UPDATE(HDMI_ACR_44_0, HDMI_ACR_CTS_44, audio_घड़ी_info.cts_44khz);

	/* HDMI_ACR_44_1__HDMI_ACR_N_44_MASK */
	REG_UPDATE(HDMI_ACR_44_1, HDMI_ACR_N_44, audio_घड़ी_info.n_44khz);

	/* HDMI_ACR_48_0__HDMI_ACR_CTS_48_MASK */
	REG_UPDATE(HDMI_ACR_48_0, HDMI_ACR_CTS_48, audio_घड़ी_info.cts_48khz);

	/* HDMI_ACR_48_1__HDMI_ACR_N_48_MASK */
	REG_UPDATE(HDMI_ACR_48_1, HDMI_ACR_N_48, audio_घड़ी_info.n_48khz);

	/* Video driver cannot know in advance which sample rate will
	 * be used by HD Audio driver
	 * HDMI_ACR_PACKET_CONTROL__HDMI_ACR_N_MULTIPLE field is
	 * programmed below in पूर्णांकerruppt callback
	 */

	/* AFMT_60958_0__AFMT_60958_CS_CHANNEL_NUMBER_L_MASK &
	 * AFMT_60958_0__AFMT_60958_CS_CLOCK_ACCURACY_MASK
	 */
	REG_UPDATE_2(AFMT_60958_0,
			AFMT_60958_CS_CHANNEL_NUMBER_L, 1,
			AFMT_60958_CS_CLOCK_ACCURACY, 0);

	/* AFMT_60958_1 AFMT_60958_CS_CHALNNEL_NUMBER_R */
	REG_UPDATE(AFMT_60958_1, AFMT_60958_CS_CHANNEL_NUMBER_R, 2);

	/* AFMT_60958_2 now keep this settings until
	 * Programming guide comes out
	 */
	REG_UPDATE_6(AFMT_60958_2,
			AFMT_60958_CS_CHANNEL_NUMBER_2, 3,
			AFMT_60958_CS_CHANNEL_NUMBER_3, 4,
			AFMT_60958_CS_CHANNEL_NUMBER_4, 5,
			AFMT_60958_CS_CHANNEL_NUMBER_5, 6,
			AFMT_60958_CS_CHANNEL_NUMBER_6, 7,
			AFMT_60958_CS_CHANNEL_NUMBER_7, 8);
पूर्ण

अटल व्योम enc1_se_setup_dp_audio(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* --- DP Audio packet configurations --- */

	/* ATP Configuration */
	REG_SET(DP_SEC_AUD_N, 0,
			DP_SEC_AUD_N, DP_SEC_AUD_N__DP_SEC_AUD_N__DEFAULT);

	/* Async/स्वतः-calc बारtamp mode */
	REG_SET(DP_SEC_TIMESTAMP, 0, DP_SEC_TIMESTAMP_MODE,
			DP_SEC_TIMESTAMP__DP_SEC_TIMESTAMP_MODE__AUTO_CALC);

	/* --- The following are the रेजिस्टरs
	 *  copied from the SetupHDMI ---
	 */

	/* AFMT_AUDIO_PACKET_CONTROL */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, 1);

	/* AFMT_AUDIO_PACKET_CONTROL2 */
	/* Program the ATP and AIP next */
	REG_UPDATE_2(AFMT_AUDIO_PACKET_CONTROL2,
			AFMT_AUDIO_LAYOUT_OVRD, 0,
			AFMT_60958_OSF_OVRD, 0);

	/* AFMT_INFOFRAME_CONTROL0 */
	REG_UPDATE(AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, 1);

	/* AFMT_60958_0__AFMT_60958_CS_CLOCK_ACCURACY_MASK */
	REG_UPDATE(AFMT_60958_0, AFMT_60958_CS_CLOCK_ACCURACY, 0);
पूर्ण

व्योम enc1_se_enable_audio_घड़ी(
	काष्ठा stream_encoder *enc,
	bool enable)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (REG(AFMT_CNTL) == 0)
		वापस;   /* DCE8/10 करोes not have this रेजिस्टर */

	REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, !!enable);

	/* रुको क्रम AFMT घड़ी to turn on,
	 * expectation: this should complete in 1-2 पढ़ोs
	 *
	 * REG_WAIT(AFMT_CNTL, AFMT_AUDIO_CLOCK_ON, !!enable, 1, 10);
	 *
	 * TODO: रुको क्रम घड़ी_on करोes not work well. May need HW
	 * program sequence. But audio seems work normally even without रुको
	 * क्रम घड़ी_on status change
	 */
पूर्ण

व्योम enc1_se_enable_dp_audio(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* Enable Audio packets */
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_ASP_ENABLE, 1);

	/* Program the ATP and AIP next */
	REG_UPDATE_2(DP_SEC_CNTL,
			DP_SEC_ATP_ENABLE, 1,
			DP_SEC_AIP_ENABLE, 1);

	/* Program STREAM_ENABLE after all the other enables. */
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
पूर्ण

अटल व्योम enc1_se_disable_dp_audio(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t value = 0;

	/* Disable Audio packets */
	REG_UPDATE_5(DP_SEC_CNTL,
			DP_SEC_ASP_ENABLE, 0,
			DP_SEC_ATP_ENABLE, 0,
			DP_SEC_AIP_ENABLE, 0,
			DP_SEC_ACM_ENABLE, 0,
			DP_SEC_STREAM_ENABLE, 0);

	/* This रेजिस्टर shared with encoder info frame. Thereक्रमe we need to
	 * keep master enabled अगर at least on of the fields is not 0
	 */
	value = REG_READ(DP_SEC_CNTL);
	अगर (value != 0)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);

पूर्ण

व्योम enc1_se_audio_mute_control(
	काष्ठा stream_encoder *enc,
	bool mute)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_AUDIO_SAMPLE_SEND, !mute);
पूर्ण

व्योम enc1_se_dp_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *info)
अणु
	enc1_se_audio_setup(enc, az_inst, info);
पूर्ण

व्योम enc1_se_dp_audio_enable(
	काष्ठा stream_encoder *enc)
अणु
	enc1_se_enable_audio_घड़ी(enc, true);
	enc1_se_setup_dp_audio(enc);
	enc1_se_enable_dp_audio(enc);
पूर्ण

व्योम enc1_se_dp_audio_disable(
	काष्ठा stream_encoder *enc)
अणु
	enc1_se_disable_dp_audio(enc);
	enc1_se_enable_audio_घड़ी(enc, false);
पूर्ण

व्योम enc1_se_hdmi_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *info,
	काष्ठा audio_crtc_info *audio_crtc_info)
अणु
	enc1_se_enable_audio_घड़ी(enc, true);
	enc1_se_setup_hdmi_audio(enc, audio_crtc_info);
	enc1_se_audio_setup(enc, az_inst, info);
पूर्ण

व्योम enc1_se_hdmi_audio_disable(
	काष्ठा stream_encoder *enc)
अणु
	enc1_se_enable_audio_घड़ी(enc, false);
पूर्ण


व्योम enc1_setup_stereo_sync(
	काष्ठा stream_encoder *enc,
	पूर्णांक tg_inst, bool enable)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	REG_UPDATE(DIG_FE_CNTL, DIG_STEREOSYNC_SELECT, tg_inst);
	REG_UPDATE(DIG_FE_CNTL, DIG_STEREOSYNC_GATE_EN, !enable);
पूर्ण

व्योम enc1_dig_connect_to_otg(
	काष्ठा stream_encoder *enc,
	पूर्णांक tg_inst)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_UPDATE(DIG_FE_CNTL, DIG_SOURCE_SELECT, tg_inst);
पूर्ण

अचिन्हित पूर्णांक enc1_dig_source_otg(
	काष्ठा stream_encoder *enc)
अणु
	uपूर्णांक32_t tg_inst = 0;
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_GET(DIG_FE_CNTL, DIG_SOURCE_SELECT, &tg_inst);

	वापस tg_inst;
पूर्ण

bool enc1_stream_encoder_dp_get_pixel_क्रमmat(
	काष्ठा stream_encoder *enc,
	क्रमागत dc_pixel_encoding *encoding,
	क्रमागत dc_color_depth *depth)
अणु
	uपूर्णांक32_t hw_encoding = 0;
	uपूर्णांक32_t hw_depth = 0;
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (enc == शून्य ||
		encoding == शून्य ||
		depth == शून्य)
		वापस false;

	REG_GET_2(DP_PIXEL_FORMAT,
		DP_PIXEL_ENCODING, &hw_encoding,
		DP_COMPONENT_DEPTH, &hw_depth);

	चयन (hw_depth) अणु
	हाल DP_COMPONENT_PIXEL_DEPTH_6BPC:
		*depth = COLOR_DEPTH_666;
		अवरोध;
	हाल DP_COMPONENT_PIXEL_DEPTH_8BPC:
		*depth = COLOR_DEPTH_888;
		अवरोध;
	हाल DP_COMPONENT_PIXEL_DEPTH_10BPC:
		*depth = COLOR_DEPTH_101010;
		अवरोध;
	हाल DP_COMPONENT_PIXEL_DEPTH_12BPC:
		*depth = COLOR_DEPTH_121212;
		अवरोध;
	हाल DP_COMPONENT_PIXEL_DEPTH_16BPC:
		*depth = COLOR_DEPTH_161616;
		अवरोध;
	शेष:
		*depth = COLOR_DEPTH_UNDEFINED;
		अवरोध;
	पूर्ण

	चयन (hw_encoding) अणु
	हाल DP_PIXEL_ENCODING_TYPE_RGB444:
		*encoding = PIXEL_ENCODING_RGB;
		अवरोध;
	हाल DP_PIXEL_ENCODING_TYPE_YCBCR422:
		*encoding = PIXEL_ENCODING_YCBCR422;
		अवरोध;
	हाल DP_PIXEL_ENCODING_TYPE_YCBCR444:
	हाल DP_PIXEL_ENCODING_TYPE_Y_ONLY:
		*encoding = PIXEL_ENCODING_YCBCR444;
		अवरोध;
	हाल DP_PIXEL_ENCODING_TYPE_YCBCR420:
		*encoding = PIXEL_ENCODING_YCBCR420;
		अवरोध;
	शेष:
		*encoding = PIXEL_ENCODING_UNDEFINED;
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

अटल स्थिर काष्ठा stream_encoder_funcs dcn10_str_enc_funcs = अणु
	.dp_set_stream_attribute =
		enc1_stream_encoder_dp_set_stream_attribute,
	.hdmi_set_stream_attribute =
		enc1_stream_encoder_hdmi_set_stream_attribute,
	.dvi_set_stream_attribute =
		enc1_stream_encoder_dvi_set_stream_attribute,
	.set_throttled_vcp_size =
		enc1_stream_encoder_set_throttled_vcp_size,
	.update_hdmi_info_packets =
		enc1_stream_encoder_update_hdmi_info_packets,
	.stop_hdmi_info_packets =
		enc1_stream_encoder_stop_hdmi_info_packets,
	.update_dp_info_packets =
		enc1_stream_encoder_update_dp_info_packets,
	.send_immediate_sdp_message =
		enc1_stream_encoder_send_immediate_sdp_message,
	.stop_dp_info_packets =
		enc1_stream_encoder_stop_dp_info_packets,
	.dp_blank =
		enc1_stream_encoder_dp_blank,
	.dp_unblank =
		enc1_stream_encoder_dp_unblank,
	.audio_mute_control = enc1_se_audio_mute_control,

	.dp_audio_setup = enc1_se_dp_audio_setup,
	.dp_audio_enable = enc1_se_dp_audio_enable,
	.dp_audio_disable = enc1_se_dp_audio_disable,

	.hdmi_audio_setup = enc1_se_hdmi_audio_setup,
	.hdmi_audio_disable = enc1_se_hdmi_audio_disable,
	.setup_stereo_sync  = enc1_setup_stereo_sync,
	.set_avmute = enc1_stream_encoder_set_avmute,
	.dig_connect_to_otg  = enc1_dig_connect_to_otg,
	.hdmi_reset_stream_attribute = enc1_reset_hdmi_stream_attribute,
	.dig_source_otg = enc1_dig_source_otg,

	.dp_get_pixel_क्रमmat  = enc1_stream_encoder_dp_get_pixel_क्रमmat,
पूर्ण;

व्योम dcn10_stream_encoder_स्थिरruct(
	काष्ठा dcn10_stream_encoder *enc1,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bp,
	क्रमागत engine_id eng_id,
	स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_stream_encoder_shअगरt *se_shअगरt,
	स्थिर काष्ठा dcn10_stream_encoder_mask *se_mask)
अणु
	enc1->base.funcs = &dcn10_str_enc_funcs;
	enc1->base.ctx = ctx;
	enc1->base.id = eng_id;
	enc1->base.bp = bp;
	enc1->regs = regs;
	enc1->se_shअगरt = se_shअगरt;
	enc1->se_mask = se_mask;
	enc1->base.stream_enc_inst = eng_id - ENGINE_ID_DIGA;
पूर्ण

