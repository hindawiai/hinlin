<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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


#समावेश "dc_bios_types.h"
#समावेश "dcn30_dio_stream_encoder.h"
#समावेश "reg_helper.h"
#समावेश "hw_shared.h"
#समावेश "core_types.h"
#समावेश <linux/delay.h>


#घोषणा DC_LOGGER \
		enc1->base.ctx->logger


#घोषणा REG(reg)\
	(enc1->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	enc1->se_shअगरt->field_name, enc1->se_mask->field_name

#घोषणा VBI_LINE_0 0
#घोषणा HDMI_CLOCK_CHANNEL_RATE_MORE_340M 340000

#घोषणा CTX \
	enc1->base.ctx


व्योम convert_dc_info_packet_to_128(
	स्थिर काष्ठा dc_info_packet *info_packet,
	काष्ठा dc_info_packet_128 *info_packet_128)
अणु
	अचिन्हित पूर्णांक i;

	info_packet_128->hb0 = info_packet->hb0;
	info_packet_128->hb1 = info_packet->hb1;
	info_packet_128->hb2 = info_packet->hb2;
	info_packet_128->hb3 = info_packet->hb3;

	क्रम (i = 0; i < 32; i++) अणु
		info_packet_128->sb[i] = info_packet->sb[i];
	पूर्ण

पूर्ण
अटल व्योम enc3_update_hdmi_info_packet(
	काष्ठा dcn10_stream_encoder *enc1,
	uपूर्णांक32_t packet_index,
	स्थिर काष्ठा dc_info_packet *info_packet)
अणु
	uपूर्णांक32_t cont, send, line;

	अगर (info_packet->valid) अणु
		enc1->base.vpg->funcs->update_generic_info_packet(
				enc1->base.vpg,
				packet_index,
				info_packet);

		/* enable transmission of packet(s) -
		 * packet transmission begins on the next frame */
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

	/* DP_SEC_GSP[x]_LINE_REFERENCE - keep शेष value REFER_TO_DP_SOF */

	/* choose which generic packet control to use */
	चयन (packet_index) अणु
	हाल 0:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC0_CONT, cont,
				HDMI_GENERIC0_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL1,
				HDMI_GENERIC0_LINE, line);
		अवरोध;
	हाल 1:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC1_CONT, cont,
				HDMI_GENERIC1_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL1,
				HDMI_GENERIC1_LINE, line);
		अवरोध;
	हाल 2:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC2_CONT, cont,
				HDMI_GENERIC2_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL2,
				HDMI_GENERIC2_LINE, line);
		अवरोध;
	हाल 3:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC3_CONT, cont,
				HDMI_GENERIC3_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL2,
				HDMI_GENERIC3_LINE, line);
		अवरोध;
	हाल 4:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC4_CONT, cont,
				HDMI_GENERIC4_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL3,
				HDMI_GENERIC4_LINE, line);
		अवरोध;
	हाल 5:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC5_CONT, cont,
				HDMI_GENERIC5_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL3,
				HDMI_GENERIC5_LINE, line);
		अवरोध;
	हाल 6:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC6_CONT, cont,
				HDMI_GENERIC6_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL4,
				HDMI_GENERIC6_LINE, line);
		अवरोध;
	हाल 7:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL0,
				HDMI_GENERIC7_CONT, cont,
				HDMI_GENERIC7_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL4,
				HDMI_GENERIC7_LINE, line);
		अवरोध;
	हाल 8:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC8_CONT, cont,
				HDMI_GENERIC8_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL7,
				HDMI_GENERIC8_LINE, line);
		अवरोध;
	हाल 9:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC9_CONT, cont,
				HDMI_GENERIC9_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL7,
				HDMI_GENERIC9_LINE, line);
		अवरोध;
	हाल 10:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC10_CONT, cont,
				HDMI_GENERIC10_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL8,
				HDMI_GENERIC10_LINE, line);
		अवरोध;
	हाल 11:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC11_CONT, cont,
				HDMI_GENERIC11_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL8,
				HDMI_GENERIC11_LINE, line);
		अवरोध;
	हाल 12:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC12_CONT, cont,
				HDMI_GENERIC12_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL9,
				HDMI_GENERIC12_LINE, line);
		अवरोध;
	हाल 13:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC13_CONT, cont,
				HDMI_GENERIC13_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL9,
				HDMI_GENERIC13_LINE, line);
		अवरोध;
	हाल 14:
		REG_UPDATE_2(HDMI_GENERIC_PACKET_CONTROL6,
				HDMI_GENERIC14_CONT, cont,
				HDMI_GENERIC14_SEND, send);
		REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL10,
				HDMI_GENERIC14_LINE, line);
		अवरोध;
	शेष:
		/* invalid HW packet index */
		DC_LOG_WARNING(
			"Invalid HW packet index: %s()\n",
			__func__);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम enc3_stream_encoder_update_hdmi_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* क्रम bring up, disable dp द्विगुन  TODO */
	REG_UPDATE(HDMI_DB_CONTROL, HDMI_DB_DISABLE, 1);
	REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

	/*Always add mandatory packets first followed by optional ones*/
	enc3_update_hdmi_info_packet(enc1, 0, &info_frame->avi);
	enc3_update_hdmi_info_packet(enc1, 5, &info_frame->hfvsअगर);
	enc3_update_hdmi_info_packet(enc1, 2, &info_frame->gamut);
	enc3_update_hdmi_info_packet(enc1, 1, &info_frame->venकरोr);
	enc3_update_hdmi_info_packet(enc1, 3, &info_frame->spd);
	enc3_update_hdmi_info_packet(enc1, 4, &info_frame->hdrsmd);
पूर्ण

अटल व्योम enc3_stream_encoder_stop_hdmi_info_packets(
	काष्ठा stream_encoder *enc)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* stop generic packets 0,1 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC0_CONT, 0,
		HDMI_GENERIC0_SEND, 0,
		HDMI_GENERIC1_CONT, 0,
		HDMI_GENERIC1_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL1, 0,
		HDMI_GENERIC0_LINE, 0,
		HDMI_GENERIC1_LINE, 0);

	/* stop generic packets 2,3 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC2_CONT, 0,
		HDMI_GENERIC2_SEND, 0,
		HDMI_GENERIC3_CONT, 0,
		HDMI_GENERIC3_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL2, 0,
		HDMI_GENERIC2_LINE, 0,
		HDMI_GENERIC3_LINE, 0);

	/* stop generic packets 4,5 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC4_CONT, 0,
		HDMI_GENERIC4_SEND, 0,
		HDMI_GENERIC5_CONT, 0,
		HDMI_GENERIC5_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL3, 0,
		HDMI_GENERIC4_LINE, 0,
		HDMI_GENERIC5_LINE, 0);

	/* stop generic packets 6,7 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC6_CONT, 0,
		HDMI_GENERIC6_SEND, 0,
		HDMI_GENERIC7_CONT, 0,
		HDMI_GENERIC7_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL4, 0,
		HDMI_GENERIC6_LINE, 0,
		HDMI_GENERIC7_LINE, 0);

	/* stop generic packets 8,9 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL6, 0,
		HDMI_GENERIC8_CONT, 0,
		HDMI_GENERIC8_SEND, 0,
		HDMI_GENERIC9_CONT, 0,
		HDMI_GENERIC9_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL7, 0,
		HDMI_GENERIC8_LINE, 0,
		HDMI_GENERIC9_LINE, 0);

	/* stop generic packets 10,11 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL6, 0,
		HDMI_GENERIC10_CONT, 0,
		HDMI_GENERIC10_SEND, 0,
		HDMI_GENERIC11_CONT, 0,
		HDMI_GENERIC11_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL8, 0,
		HDMI_GENERIC10_LINE, 0,
		HDMI_GENERIC11_LINE, 0);

	/* stop generic packets 12,13 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL6, 0,
		HDMI_GENERIC12_CONT, 0,
		HDMI_GENERIC12_SEND, 0,
		HDMI_GENERIC13_CONT, 0,
		HDMI_GENERIC13_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL9, 0,
		HDMI_GENERIC12_LINE, 0,
		HDMI_GENERIC13_LINE, 0);

	/* stop generic packet 14 on HDMI */
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL6, 0,
		HDMI_GENERIC14_CONT, 0,
		HDMI_GENERIC14_SEND, 0);
	REG_UPDATE(HDMI_GENERIC_PACKET_CONTROL10,
		HDMI_GENERIC14_LINE, 0);
पूर्ण

/* Set DSC-related configuration.
 *   dsc_mode: 0 disables DSC, other values enable DSC in specअगरied क्रमmat
 *   sc_bytes_per_pixel: Bytes per pixel in u3.28 क्रमmat
 *   dsc_slice_width: Slice width in pixels
 */
अटल व्योम enc3_dp_set_dsc_config(काष्ठा stream_encoder *enc,
					क्रमागत optc_dsc_mode dsc_mode,
					uपूर्णांक32_t dsc_bytes_per_pixel,
					uपूर्णांक32_t dsc_slice_width)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_UPDATE_2(DP_DSC_CNTL,
			DP_DSC_MODE, dsc_mode,
			DP_DSC_SLICE_WIDTH, dsc_slice_width);

	REG_SET(DP_DSC_BYTES_PER_PIXEL, 0,
		DP_DSC_BYTES_PER_PIXEL, dsc_bytes_per_pixel);
पूर्ण


अटल व्योम enc3_dp_set_dsc_pps_info_packet(काष्ठा stream_encoder *enc,
					bool enable,
					uपूर्णांक8_t *dsc_packed_pps)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (enable) अणु
		काष्ठा dc_info_packet pps_sdp;
		पूर्णांक i;

		/* Configure क्रम PPS packet size (128 bytes) */
		REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP11_PPS, 1);

		/* We need turn on घड़ी beक्रमe programming AFMT block
		 *
		 * TODO: We may not need this here anymore since update_generic_info_packet
		 * no दीर्घer touches AFMT
		 */
		REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

		/* Load PPS पूर्णांकo infoframe (SDP) रेजिस्टरs */
		pps_sdp.valid = true;
		pps_sdp.hb0 = 0;
		pps_sdp.hb1 = DC_DP_INFOFRAME_TYPE_PPS;
		pps_sdp.hb2 = 127;
		pps_sdp.hb3 = 0;

		क्रम (i = 0; i < 4; i++) अणु
			स_नकल(pps_sdp.sb, &dsc_packed_pps[i * 32], 32);
			enc1->base.vpg->funcs->update_generic_info_packet(
							enc1->base.vpg,
							11 + i,
							&pps_sdp);
		पूर्ण

		/* SW should make sure VBID[6] update line number is bigger
		 * than PPS transmit line number
		 */
		REG_UPDATE(DP_GSP11_CNTL,
				DP_SEC_GSP11_LINE_NUM, 2);
		REG_UPDATE_2(DP_MSA_VBID_MISC,
				DP_VBID6_LINE_REFERENCE, 0,
				DP_VBID6_LINE_NUM, 3);

		/* Send PPS data at the line number specअगरied above.
		 * DP spec requires PPS to be sent only when it changes, however since
		 * decoder has to be able to handle its change on every frame, we're
		 * sending it always (i.e. on every frame) to reduce the chance it'd be
		 * missed by decoder. If it turns out required to send PPS only when it
		 * changes, we can use DP_SEC_GSP11_SEND रेजिस्टर.
		 */
		REG_UPDATE(DP_GSP11_CNTL,
			DP_SEC_GSP11_ENABLE, 1);
		REG_UPDATE(DP_SEC_CNTL,
			DP_SEC_STREAM_ENABLE, 1);
	पूर्ण अन्यथा अणु
		/* Disable Generic Stream Packet 11 (GSP) transmission */
		REG_UPDATE(DP_GSP11_CNTL, DP_SEC_GSP11_ENABLE, 0);
		REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP11_PPS, 0);
	पूर्ण
पूर्ण


/* this function पढ़ो dsc related रेजिस्टर fields to be logged later in dcn10_log_hw_state
 * पूर्णांकo a dcn_dsc_state काष्ठा.
 */
अटल व्योम enc3_पढ़ो_state(काष्ठा stream_encoder *enc, काष्ठा enc_state *s)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	//अगर dsc is enabled, जारी to पढ़ो
	REG_GET(DP_DSC_CNTL, DP_DSC_MODE, &s->dsc_mode);
	अगर (s->dsc_mode) अणु
		REG_GET(DP_DSC_CNTL, DP_DSC_SLICE_WIDTH, &s->dsc_slice_width);
		REG_GET(DP_GSP11_CNTL, DP_SEC_GSP11_LINE_NUM, &s->sec_gsp_pps_line_num);

		REG_GET(DP_MSA_VBID_MISC, DP_VBID6_LINE_REFERENCE, &s->vbid6_line_reference);
		REG_GET(DP_MSA_VBID_MISC, DP_VBID6_LINE_NUM, &s->vbid6_line_num);

		REG_GET(DP_GSP11_CNTL, DP_SEC_GSP11_ENABLE, &s->sec_gsp_pps_enable);
		REG_GET(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, &s->sec_stream_enable);
	पूर्ण
पूर्ण

अटल व्योम enc3_stream_encoder_update_dp_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t dmdata_packet_enabled = 0;

	अगर (info_frame->vsc.valid) अणु
		enc->vpg->funcs->update_generic_info_packet(
				enc->vpg,
				0,  /* packetIndex */
				&info_frame->vsc);
	पूर्ण
	अगर (info_frame->spd.valid) अणु
		enc->vpg->funcs->update_generic_info_packet(
				enc->vpg,
				2,  /* packetIndex */
				&info_frame->spd);
	पूर्ण
	अगर (info_frame->hdrsmd.valid) अणु
		enc->vpg->funcs->update_generic_info_packet(
				enc->vpg,
				3,  /* packetIndex */
				&info_frame->hdrsmd);
	पूर्ण
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

	/* check अगर dynamic metadata packet transmission is enabled */
	REG_GET(DP_SEC_METADATA_TRANSMISSION,
			DP_SEC_METADATA_PACKET_ENABLE, &dmdata_packet_enabled);

	अगर (dmdata_packet_enabled)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
पूर्ण

अटल व्योम enc3_dp_set_odm_combine(
	काष्ठा stream_encoder *enc,
	bool odm_combine)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_COMBINE, odm_combine);
पूर्ण

/* setup stream encoder in dvi mode */
व्योम enc3_stream_encoder_dvi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	bool is_dual_link)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (!enc->ctx->dc->debug.aव्योम_vbios_exec_table) अणु
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

	पूर्ण अन्यथा अणु

		//Set pattern क्रम घड़ी channel, शेष vlue 0x63 करोes not work
		REG_UPDATE(DIG_CLOCK_PATTERN, DIG_CLOCK_PATTERN, 0x1F);

		//DIG_BE_TMDS_DVI_MODE : TMDS-DVI mode is alपढ़ोy set in link_encoder_setup

		//DIG_SOURCE_SELECT is alपढ़ोy set in dig_connect_to_otg

		/* set DIG_START to 0x1 to reset FIFO */
		REG_UPDATE(DIG_FE_CNTL, DIG_START, 1);
		udelay(1);

		/* ग_लिखो 0 to take the FIFO out of reset */
		REG_UPDATE(DIG_FE_CNTL, DIG_START, 0);
		udelay(1);
	पूर्ण

	ASSERT(crtc_timing->pixel_encoding == PIXEL_ENCODING_RGB);
	ASSERT(crtc_timing->display_color_depth == COLOR_DEPTH_888);
	enc1_stream_encoder_set_stream_attribute_helper(enc1, crtc_timing);
पूर्ण

/* setup stream encoder in hdmi mode */
अटल व्योम enc3_stream_encoder_hdmi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	पूर्णांक actual_pix_clk_khz,
	bool enable_audio)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (!enc->ctx->dc->debug.aव्योम_vbios_exec_table) अणु
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

	पूर्ण अन्यथा अणु

		//Set pattern क्रम घड़ी channel, शेष vlue 0x63 करोes not work
		REG_UPDATE(DIG_CLOCK_PATTERN, DIG_CLOCK_PATTERN, 0x1F);

		//DIG_BE_TMDS_HDMI_MODE : TMDS-HDMI mode is alपढ़ोy set in link_encoder_setup

		//DIG_SOURCE_SELECT is alपढ़ोy set in dig_connect_to_otg

		/* set DIG_START to 0x1 to reset FIFO */
		REG_UPDATE(DIG_FE_CNTL, DIG_START, 1);
		udelay(1);

		/* ग_लिखो 0 to take the FIFO out of reset */
		REG_UPDATE(DIG_FE_CNTL, DIG_START, 0);
		udelay(1);
	पूर्ण

	/* Configure pixel encoding */
	enc1_stream_encoder_set_stream_attribute_helper(enc1, crtc_timing);

	/* setup HDMI engine */
	REG_UPDATE_6(HDMI_CONTROL,
		HDMI_PACKET_GEN_VERSION, 1,
		HDMI_KEEPOUT_MODE, 1,
		HDMI_DEEP_COLOR_ENABLE, 0,
		HDMI_DATA_SCRAMBLE_EN, 0,
		HDMI_NO_EXTRA_शून्य_PACKET_FILLED, 1,
		HDMI_CLOCK_CHANNEL_RATE, 0);

	/* Configure color depth */
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


	/* Enable transmission of General Control packet on every frame */
	REG_UPDATE_3(HDMI_VBI_PACKET_CONTROL,
		HDMI_GC_CONT, 1,
		HDMI_GC_SEND, 1,
		HDMI_शून्य_SEND, 1);

	/* following beदीर्घs to audio */
	/* Enable Audio InfoFrame packet transmission. */
	REG_UPDATE(HDMI_INFOFRAME_CONTROL0, HDMI_AUDIO_INFO_SEND, 1);

	/* update द्विगुन-buffered AUDIO_INFO रेजिस्टरs immediately */
	ASSERT (enc->afmt);
	enc->afmt->funcs->audio_info_immediate_update(enc->afmt);

	/* Select line number on which to send Audio InfoFrame packets */
	REG_UPDATE(HDMI_INFOFRAME_CONTROL1, HDMI_AUDIO_INFO_LINE,
				VBI_LINE_0 + 2);

	/* set HDMI GC AVMUTE */
	REG_UPDATE(HDMI_GC, HDMI_GC_AVMUTE, 0);
पूर्ण

अटल व्योम enc3_audio_mute_control(
	काष्ठा stream_encoder *enc,
	bool mute)
अणु
	ASSERT (enc->afmt);
	enc->afmt->funcs->audio_mute_control(enc->afmt, mute);
पूर्ण

अटल व्योम enc3_se_dp_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *info)
अणु
	ASSERT (enc->afmt);
	enc->afmt->funcs->se_audio_setup(enc->afmt, az_inst, info);
पूर्ण

#घोषणा DP_SEC_AUD_N__DP_SEC_AUD_N__DEFAULT 0x8000
#घोषणा DP_SEC_TIMESTAMP__DP_SEC_TIMESTAMP_MODE__AUTO_CALC 1

अटल व्योम enc3_se_setup_dp_audio(
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

	ASSERT (enc->afmt);
	enc->afmt->funcs->setup_dp_audio(enc->afmt);
पूर्ण

अटल व्योम enc3_se_dp_audio_enable(
	काष्ठा stream_encoder *enc)
अणु
	enc1_se_enable_audio_घड़ी(enc, true);
	enc3_se_setup_dp_audio(enc);
	enc1_se_enable_dp_audio(enc);
पूर्ण

अटल व्योम enc3_se_setup_hdmi_audio(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा audio_crtc_info *crtc_info)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	काष्ठा audio_घड़ी_info audio_घड़ी_info = अणु0पूर्ण;

	/* Setup audio in AFMT - program AFMT block associated with DIO */
	ASSERT (enc->afmt);
	enc->afmt->funcs->setup_hdmi_audio(enc->afmt);

	/* HDMI_AUDIO_PACKET_CONTROL */
	REG_UPDATE(HDMI_AUDIO_PACKET_CONTROL,
			HDMI_AUDIO_DELAY_EN, 1);

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
पूर्ण

अटल व्योम enc3_se_hdmi_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *info,
	काष्ठा audio_crtc_info *audio_crtc_info)
अणु
	enc1_se_enable_audio_घड़ी(enc, true);
	enc3_se_setup_hdmi_audio(enc, audio_crtc_info);
	ASSERT (enc->afmt);
	enc->afmt->funcs->se_audio_setup(enc->afmt, az_inst, info);
पूर्ण


अटल स्थिर काष्ठा stream_encoder_funcs dcn30_str_enc_funcs = अणु
	.dp_set_odm_combine =
		enc3_dp_set_odm_combine,
	.dp_set_stream_attribute =
		enc2_stream_encoder_dp_set_stream_attribute,
	.hdmi_set_stream_attribute =
		enc3_stream_encoder_hdmi_set_stream_attribute,
	.dvi_set_stream_attribute =
		enc3_stream_encoder_dvi_set_stream_attribute,
	.set_throttled_vcp_size =
		enc1_stream_encoder_set_throttled_vcp_size,
	.update_hdmi_info_packets =
		enc3_stream_encoder_update_hdmi_info_packets,
	.stop_hdmi_info_packets =
		enc3_stream_encoder_stop_hdmi_info_packets,
	.update_dp_info_packets =
		enc3_stream_encoder_update_dp_info_packets,
	.stop_dp_info_packets =
		enc1_stream_encoder_stop_dp_info_packets,
	.dp_blank =
		enc1_stream_encoder_dp_blank,
	.dp_unblank =
		enc2_stream_encoder_dp_unblank,
	.audio_mute_control = enc3_audio_mute_control,

	.dp_audio_setup = enc3_se_dp_audio_setup,
	.dp_audio_enable = enc3_se_dp_audio_enable,
	.dp_audio_disable = enc1_se_dp_audio_disable,

	.hdmi_audio_setup = enc3_se_hdmi_audio_setup,
	.hdmi_audio_disable = enc1_se_hdmi_audio_disable,
	.setup_stereo_sync  = enc1_setup_stereo_sync,
	.set_avmute = enc1_stream_encoder_set_avmute,
	.dig_connect_to_otg = enc1_dig_connect_to_otg,
	.dig_source_otg = enc1_dig_source_otg,

	.dp_get_pixel_क्रमmat  = enc1_stream_encoder_dp_get_pixel_क्रमmat,

	.enc_पढ़ो_state = enc3_पढ़ो_state,
	.dp_set_dsc_config = enc3_dp_set_dsc_config,
	.dp_set_dsc_pps_info_packet = enc3_dp_set_dsc_pps_info_packet,
	.set_dynamic_metadata = enc2_set_dynamic_metadata,
	.hdmi_reset_stream_attribute = enc1_reset_hdmi_stream_attribute,
पूर्ण;

व्योम dcn30_dio_stream_encoder_स्थिरruct(
	काष्ठा dcn10_stream_encoder *enc1,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bp,
	क्रमागत engine_id eng_id,
	काष्ठा vpg *vpg,
	काष्ठा afmt *afmt,
	स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_stream_encoder_shअगरt *se_shअगरt,
	स्थिर काष्ठा dcn10_stream_encoder_mask *se_mask)
अणु
	enc1->base.funcs = &dcn30_str_enc_funcs;
	enc1->base.ctx = ctx;
	enc1->base.id = eng_id;
	enc1->base.bp = bp;
	enc1->base.vpg = vpg;
	enc1->base.afmt = afmt;
	enc1->regs = regs;
	enc1->se_shअगरt = se_shअगरt;
	enc1->se_mask = se_mask;
	enc1->base.stream_enc_inst = vpg->inst;
पूर्ण

