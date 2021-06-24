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
#समावेश "dcn20_stream_encoder.h"
#समावेश "reg_helper.h"
#समावेश "hw_shared.h"

#घोषणा DC_LOGGER \
		enc1->base.ctx->logger


#घोषणा REG(reg)\
	(enc1->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	enc1->se_shअगरt->field_name, enc1->se_mask->field_name


#घोषणा CTX \
	enc1->base.ctx


अटल व्योम enc2_update_hdmi_info_packet(
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
	शेष:
		/* invalid HW packet index */
		DC_LOG_WARNING(
			"Invalid HW packet index: %s()\n",
			__func__);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम enc2_stream_encoder_update_hdmi_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* क्रम bring up, disable dp द्विगुन  TODO */
	REG_UPDATE(HDMI_DB_CONTROL, HDMI_DB_DISABLE, 1);

	/*Always add mandatory packets first followed by optional ones*/
	enc2_update_hdmi_info_packet(enc1, 0, &info_frame->avi);
	enc2_update_hdmi_info_packet(enc1, 1, &info_frame->hfvsअगर);
	enc2_update_hdmi_info_packet(enc1, 2, &info_frame->gamut);
	enc2_update_hdmi_info_packet(enc1, 3, &info_frame->venकरोr);
	enc2_update_hdmi_info_packet(enc1, 4, &info_frame->spd);
	enc2_update_hdmi_info_packet(enc1, 5, &info_frame->hdrsmd);
पूर्ण

अटल व्योम enc2_stream_encoder_stop_hdmi_info_packets(
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
पूर्ण


/* Update GSP7 SDP 128 byte दीर्घ */
अटल व्योम enc2_update_gsp7_128_info_packet(
	काष्ठा dcn10_stream_encoder *enc1,
	स्थिर काष्ठा dc_info_packet_128 *info_packet)
अणु
	uपूर्णांक32_t i;

	/* TODOFPGA Figure out a proper number क्रम max_retries polling क्रम lock
	 * use 50 क्रम now.
	 */
	uपूर्णांक32_t max_retries = 50;
	स्थिर uपूर्णांक32_t *content = (स्थिर uपूर्णांक32_t *) &info_packet->sb[0];

	ASSERT(info_packet->hb1  == DC_DP_INFOFRAME_TYPE_PPS);

	/* Configure क्रम PPS packet size (128 bytes) */
	REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP7_PPS, 1);

	/* We need turn on घड़ी beक्रमe programming AFMT block*/
	REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

	/* Poll dig_update_lock is not locked -> asic पूर्णांकernal संकेत
	 * assumes otg master lock will unlock it
	 */
	/*REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_LOCK_STATUS, 0, 10, max_retries);*/

	/* Wait क्रम HW/SW GSP memory access conflict to go away */
	REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT,
			0, 10, max_retries);

	/* Clear HW/SW memory access conflict flag */
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT_CLR, 1);

	/* ग_लिखो generic packet header */
	REG_UPDATE(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_INDEX, 7);
	REG_SET_4(AFMT_GENERIC_HDR, 0,
			AFMT_GENERIC_HB0, info_packet->hb0,
			AFMT_GENERIC_HB1, info_packet->hb1,
			AFMT_GENERIC_HB2, info_packet->hb2,
			AFMT_GENERIC_HB3, info_packet->hb3);

	/* Write generic packet content 128 bytes दीर्घ. Four sets are used (indexes 7
	 * through 10) to fit 128 bytes.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		uपूर्णांक32_t packet_index = 7 + i;
		REG_UPDATE(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_INDEX, packet_index);

		REG_WRITE(AFMT_GENERIC_0, *content++);
		REG_WRITE(AFMT_GENERIC_1, *content++);
		REG_WRITE(AFMT_GENERIC_2, *content++);
		REG_WRITE(AFMT_GENERIC_3, *content++);
		REG_WRITE(AFMT_GENERIC_4, *content++);
		REG_WRITE(AFMT_GENERIC_5, *content++);
		REG_WRITE(AFMT_GENERIC_6, *content++);
		REG_WRITE(AFMT_GENERIC_7, *content++);
	पूर्ण

	REG_UPDATE(AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC7_FRAME_UPDATE, 1);
पूर्ण

/* Set DSC-related configuration.
 *   dsc_mode: 0 disables DSC, other values enable DSC in specअगरied क्रमmat
 *   sc_bytes_per_pixel: Bytes per pixel in u3.28 क्रमmat
 *   dsc_slice_width: Slice width in pixels
 */
अटल व्योम enc2_dp_set_dsc_config(काष्ठा stream_encoder *enc,
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


अटल व्योम enc2_dp_set_dsc_pps_info_packet(काष्ठा stream_encoder *enc,
					bool enable,
					uपूर्णांक8_t *dsc_packed_pps)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (enable) अणु
		काष्ठा dc_info_packet_128 pps_sdp;

		ASSERT(dsc_packed_pps);

		/* Load PPS पूर्णांकo infoframe (SDP) रेजिस्टरs */
		pps_sdp.valid = true;
		pps_sdp.hb0 = 0;
		pps_sdp.hb1 = DC_DP_INFOFRAME_TYPE_PPS;
		pps_sdp.hb2 = 127;
		pps_sdp.hb3 = 0;
		स_नकल(&pps_sdp.sb[0], dsc_packed_pps, माप(pps_sdp.sb));
		enc2_update_gsp7_128_info_packet(enc1, &pps_sdp);

		/* Enable Generic Stream Packet 7 (GSP) transmission */
		//REG_UPDATE(DP_SEC_CNTL,
		//	DP_SEC_GSP7_ENABLE, 1);

		/* SW should make sure VBID[6] update line number is bigger
		 * than PPS transmit line number
		 */
		REG_UPDATE(DP_SEC_CNTL6,
				DP_SEC_GSP7_LINE_NUM, 2);
		REG_UPDATE_2(DP_MSA_VBID_MISC,
				DP_VBID6_LINE_REFERENCE, 0,
				DP_VBID6_LINE_NUM, 3);

		/* Send PPS data at the line number specअगरied above.
		 * DP spec requires PPS to be sent only when it changes, however since
		 * decoder has to be able to handle its change on every frame, we're
		 * sending it always (i.e. on every frame) to reduce the chance it'd be
		 * missed by decoder. If it turns out required to send PPS only when it
		 * changes, we can use DP_SEC_GSP7_SEND रेजिस्टर.
		 */
		REG_UPDATE_2(DP_SEC_CNTL,
			DP_SEC_GSP7_ENABLE, 1,
			DP_SEC_STREAM_ENABLE, 1);
	पूर्ण अन्यथा अणु
		/* Disable Generic Stream Packet 7 (GSP) transmission */
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_GSP7_ENABLE, 0);
		REG_UPDATE(DP_SEC_CNTL2, DP_SEC_GSP7_PPS, 0);
	पूर्ण
पूर्ण


/* this function पढ़ो dsc related रेजिस्टर fields to be logged later in dcn10_log_hw_state
 * पूर्णांकo a dcn_dsc_state काष्ठा.
 */
अटल व्योम enc2_पढ़ो_state(काष्ठा stream_encoder *enc, काष्ठा enc_state *s)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	//अगर dsc is enabled, जारी to पढ़ो
	REG_GET(DP_DSC_CNTL, DP_DSC_MODE, &s->dsc_mode);
	अगर (s->dsc_mode) अणु
		REG_GET(DP_DSC_CNTL, DP_DSC_SLICE_WIDTH, &s->dsc_slice_width);
		REG_GET(DP_SEC_CNTL6, DP_SEC_GSP7_LINE_NUM, &s->sec_gsp_pps_line_num);

		REG_GET(DP_MSA_VBID_MISC, DP_VBID6_LINE_REFERENCE, &s->vbid6_line_reference);
		REG_GET(DP_MSA_VBID_MISC, DP_VBID6_LINE_NUM, &s->vbid6_line_num);

		REG_GET(DP_SEC_CNTL, DP_SEC_GSP7_ENABLE, &s->sec_gsp_pps_enable);
		REG_GET(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, &s->sec_stream_enable);
	पूर्ण
पूर्ण

/* Set Dynamic Metadata-configuration.
 *   enable_dme:         TRUE: enables Dynamic Metadata Enfine, FALSE: disables DME
 *   hubp_requestor_id:  HUBP physical instance that is the source of dynamic metadata
 *                       only needs to be set when enable_dme is TRUE
 *   dmdata_mode:        dynamic metadata packet type: DP, HDMI, or Dolby Vision
 *
 *   Ensure the OTG master update lock is set when changing DME configuration.
 */
व्योम enc2_set_dynamic_metadata(काष्ठा stream_encoder *enc,
		bool enable_dme,
		uपूर्णांक32_t hubp_requestor_id,
		क्रमागत dynamic_metadata_mode dmdata_mode)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	अगर (enable_dme) अणु
		REG_UPDATE_2(DME_CONTROL,
				METADATA_HUBP_REQUESTOR_ID, hubp_requestor_id,
				METADATA_STREAM_TYPE, (dmdata_mode == dmdata_करोlby_vision) ? 1 : 0);

		/* Use शेष line reference DP_SOF क्रम bringup.
		 * Should use OTG_SOF क्रम DRR हालs
		 */
		अगर (dmdata_mode == dmdata_dp)
			REG_UPDATE_3(DP_SEC_METADATA_TRANSMISSION,
					DP_SEC_METADATA_PACKET_ENABLE, 1,
					DP_SEC_METADATA_PACKET_LINE_REFERENCE, 0,
					DP_SEC_METADATA_PACKET_LINE, 20);
		अन्यथा अणु
			REG_UPDATE_3(HDMI_METADATA_PACKET_CONTROL,
					HDMI_METADATA_PACKET_ENABLE, 1,
					HDMI_METADATA_PACKET_LINE_REFERENCE, 0,
					HDMI_METADATA_PACKET_LINE, 2);

			अगर (dmdata_mode == dmdata_करोlby_vision)
				REG_UPDATE(DIG_FE_CNTL,
						DOLBY_VISION_EN, 1);
		पूर्ण

		REG_UPDATE(DME_CONTROL,
				METADATA_ENGINE_EN, 1);
	पूर्ण अन्यथा अणु
		REG_UPDATE(DME_CONTROL,
				METADATA_ENGINE_EN, 0);

		अगर (dmdata_mode == dmdata_dp)
			REG_UPDATE(DP_SEC_METADATA_TRANSMISSION,
					DP_SEC_METADATA_PACKET_ENABLE, 0);
		अन्यथा अणु
			REG_UPDATE(HDMI_METADATA_PACKET_CONTROL,
					HDMI_METADATA_PACKET_ENABLE, 0);
			REG_UPDATE(DIG_FE_CNTL,
					DOLBY_VISION_EN, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम enc2_stream_encoder_update_dp_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uपूर्णांक32_t dmdata_packet_enabled = 0;

	enc1_stream_encoder_update_dp_info_packets(enc, info_frame);

	/* check अगर dynamic metadata packet transmission is enabled */
	REG_GET(DP_SEC_METADATA_TRANSMISSION,
			DP_SEC_METADATA_PACKET_ENABLE, &dmdata_packet_enabled);

	अगर (dmdata_packet_enabled)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
पूर्ण

अटल bool is_two_pixels_per_contaपूर्णांकer(स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	bool two_pix = timing->pixel_encoding == PIXEL_ENCODING_YCBCR420;

	two_pix = two_pix || (timing->flags.DSC && timing->pixel_encoding == PIXEL_ENCODING_YCBCR422
			&& !timing->dsc_cfg.ycbcr422_simple);
	वापस two_pix;
पूर्ण

व्योम enc2_stream_encoder_dp_unblank(
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
		अगर (is_two_pixels_per_contaपूर्णांकer(&param->timing) || param->opp_cnt > 1) अणु
			/*this logic should be the same in get_pixel_घड़ी_parameters() */
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

	/* make sure stream is disabled beक्रमe resetting steer fअगरo */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, false);
	REG_WAIT(DP_VID_STREAM_CNTL, DP_VID_STREAM_STATUS, 0, 10, 5000);

	/* set DIG_START to 0x1 to reset FIFO */
	REG_UPDATE(DIG_FE_CNTL, DIG_START, 1);
	udelay(1);

	/* ग_लिखो 0 to take the FIFO out of reset */

	REG_UPDATE(DIG_FE_CNTL, DIG_START, 0);

	/* चयन DP encoder to CRTC data, but reset it the fअगरo first. It may happen
	 * that it overflows during mode transition, and someबार करोesn't recover.
	 */
	REG_UPDATE(DP_STEER_FIFO, DP_STEER_FIFO_RESET, 1);
	udelay(10);

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

अटल व्योम enc2_dp_set_odm_combine(
	काष्ठा stream_encoder *enc,
	bool odm_combine)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	REG_UPDATE(DP_PIXEL_FORMAT, DP_PIXEL_COMBINE, odm_combine);
पूर्ण

व्योम enc2_stream_encoder_dp_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	क्रमागत dc_color_space output_color_space,
	bool use_vsc_sdp_क्रम_colorimetry,
	uपूर्णांक32_t enable_sdp_splitting)
अणु
	काष्ठा dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	enc1_stream_encoder_dp_set_stream_attribute(enc,
			crtc_timing,
			output_color_space,
			use_vsc_sdp_क्रम_colorimetry,
			enable_sdp_splitting);

	REG_UPDATE(DP_SEC_FRAMING4,
		DP_SST_SDP_SPLITTING, enable_sdp_splitting);
पूर्ण

अटल स्थिर काष्ठा stream_encoder_funcs dcn20_str_enc_funcs = अणु
	.dp_set_odm_combine =
		enc2_dp_set_odm_combine,
	.dp_set_stream_attribute =
		enc2_stream_encoder_dp_set_stream_attribute,
	.hdmi_set_stream_attribute =
		enc1_stream_encoder_hdmi_set_stream_attribute,
	.dvi_set_stream_attribute =
		enc1_stream_encoder_dvi_set_stream_attribute,
	.set_throttled_vcp_size =
		enc1_stream_encoder_set_throttled_vcp_size,
	.update_hdmi_info_packets =
		enc2_stream_encoder_update_hdmi_info_packets,
	.stop_hdmi_info_packets =
		enc2_stream_encoder_stop_hdmi_info_packets,
	.update_dp_info_packets =
		enc2_stream_encoder_update_dp_info_packets,
	.send_immediate_sdp_message =
		enc1_stream_encoder_send_immediate_sdp_message,
	.stop_dp_info_packets =
		enc1_stream_encoder_stop_dp_info_packets,
	.dp_blank =
		enc1_stream_encoder_dp_blank,
	.dp_unblank =
		enc2_stream_encoder_dp_unblank,
	.audio_mute_control = enc1_se_audio_mute_control,

	.dp_audio_setup = enc1_se_dp_audio_setup,
	.dp_audio_enable = enc1_se_dp_audio_enable,
	.dp_audio_disable = enc1_se_dp_audio_disable,

	.hdmi_audio_setup = enc1_se_hdmi_audio_setup,
	.hdmi_audio_disable = enc1_se_hdmi_audio_disable,
	.setup_stereo_sync  = enc1_setup_stereo_sync,
	.set_avmute = enc1_stream_encoder_set_avmute,
	.dig_connect_to_otg  = enc1_dig_connect_to_otg,
	.dig_source_otg = enc1_dig_source_otg,

	.dp_get_pixel_क्रमmat =
		enc1_stream_encoder_dp_get_pixel_क्रमmat,

	.enc_पढ़ो_state = enc2_पढ़ो_state,
	.dp_set_dsc_config = enc2_dp_set_dsc_config,
	.dp_set_dsc_pps_info_packet = enc2_dp_set_dsc_pps_info_packet,
	.set_dynamic_metadata = enc2_set_dynamic_metadata,
	.hdmi_reset_stream_attribute = enc1_reset_hdmi_stream_attribute,
पूर्ण;

व्योम dcn20_stream_encoder_स्थिरruct(
	काष्ठा dcn10_stream_encoder *enc1,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bp,
	क्रमागत engine_id eng_id,
	स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_stream_encoder_shअगरt *se_shअगरt,
	स्थिर काष्ठा dcn10_stream_encoder_mask *se_mask)
अणु
	enc1->base.funcs = &dcn20_str_enc_funcs;
	enc1->base.ctx = ctx;
	enc1->base.id = eng_id;
	enc1->base.bp = bp;
	enc1->regs = regs;
	enc1->se_shअगरt = se_shअगरt;
	enc1->se_mask = se_mask;
	enc1->base.stream_enc_inst = eng_id - ENGINE_ID_DIGA;
पूर्ण

