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

#अगर_अघोषित __DC_STREAM_ENCODER_DCN10_H__
#घोषणा __DC_STREAM_ENCODER_DCN10_H__

#समावेश "stream_encoder.h"

#घोषणा DCN10STRENC_FROM_STRENC(stream_encoder)\
	container_of(stream_encoder, काष्ठा dcn10_stream_encoder, base)

#घोषणा SE_COMMON_DCN_REG_LIST(id) \
	SRI(AFMT_CNTL, DIG, id), \
	SRI(AFMT_GENERIC_0, DIG, id), \
	SRI(AFMT_GENERIC_1, DIG, id), \
	SRI(AFMT_GENERIC_2, DIG, id), \
	SRI(AFMT_GENERIC_3, DIG, id), \
	SRI(AFMT_GENERIC_4, DIG, id), \
	SRI(AFMT_GENERIC_5, DIG, id), \
	SRI(AFMT_GENERIC_6, DIG, id), \
	SRI(AFMT_GENERIC_7, DIG, id), \
	SRI(AFMT_GENERIC_HDR, DIG, id), \
	SRI(AFMT_INFOFRAME_CONTROL0, DIG, id), \
	SRI(AFMT_VBI_PACKET_CONTROL, DIG, id), \
	SRI(AFMT_VBI_PACKET_CONTROL1, DIG, id), \
	SRI(AFMT_AUDIO_PACKET_CONTROL, DIG, id), \
	SRI(AFMT_AUDIO_PACKET_CONTROL2, DIG, id), \
	SRI(AFMT_AUDIO_SRC_CONTROL, DIG, id), \
	SRI(AFMT_60958_0, DIG, id), \
	SRI(AFMT_60958_1, DIG, id), \
	SRI(AFMT_60958_2, DIG, id), \
	SRI(DIG_FE_CNTL, DIG, id), \
	SRI(HDMI_CONTROL, DIG, id), \
	SRI(HDMI_DB_CONTROL, DIG, id), \
	SRI(HDMI_GC, DIG, id), \
	SRI(HDMI_GENERIC_PACKET_CONTROL0, DIG, id), \
	SRI(HDMI_GENERIC_PACKET_CONTROL1, DIG, id), \
	SRI(HDMI_GENERIC_PACKET_CONTROL2, DIG, id), \
	SRI(HDMI_GENERIC_PACKET_CONTROL3, DIG, id), \
	SRI(HDMI_INFOFRAME_CONTROL0, DIG, id), \
	SRI(HDMI_INFOFRAME_CONTROL1, DIG, id), \
	SRI(HDMI_VBI_PACKET_CONTROL, DIG, id), \
	SRI(HDMI_AUDIO_PACKET_CONTROL, DIG, id),\
	SRI(HDMI_ACR_PACKET_CONTROL, DIG, id),\
	SRI(HDMI_ACR_32_0, DIG, id),\
	SRI(HDMI_ACR_32_1, DIG, id),\
	SRI(HDMI_ACR_44_0, DIG, id),\
	SRI(HDMI_ACR_44_1, DIG, id),\
	SRI(HDMI_ACR_48_0, DIG, id),\
	SRI(HDMI_ACR_48_1, DIG, id),\
	SRI(DP_DB_CNTL, DP, id), \
	SRI(DP_MSA_MISC, DP, id), \
	SRI(DP_MSA_COLORIMETRY, DP, id), \
	SRI(DP_MSA_TIMING_PARAM1, DP, id), \
	SRI(DP_MSA_TIMING_PARAM2, DP, id), \
	SRI(DP_MSA_TIMING_PARAM3, DP, id), \
	SRI(DP_MSA_TIMING_PARAM4, DP, id), \
	SRI(DP_MSE_RATE_CNTL, DP, id), \
	SRI(DP_MSE_RATE_UPDATE, DP, id), \
	SRI(DP_PIXEL_FORMAT, DP, id), \
	SRI(DP_SEC_CNTL, DP, id), \
	SRI(DP_SEC_CNTL1, DP, id), \
	SRI(DP_SEC_CNTL2, DP, id), \
	SRI(DP_SEC_CNTL5, DP, id), \
	SRI(DP_SEC_CNTL6, DP, id), \
	SRI(DP_STEER_FIFO, DP, id), \
	SRI(DP_VID_M, DP, id), \
	SRI(DP_VID_N, DP, id), \
	SRI(DP_VID_STREAM_CNTL, DP, id), \
	SRI(DP_VID_TIMING, DP, id), \
	SRI(DP_SEC_AUD_N, DP, id), \
	SRI(DP_SEC_TIMESTAMP, DP, id), \
	SRI(DIG_CLOCK_PATTERN, DIG, id)

#घोषणा SE_DCN_REG_LIST(id)\
	SE_COMMON_DCN_REG_LIST(id)


काष्ठा dcn10_stream_enc_रेजिस्टरs अणु
	uपूर्णांक32_t AFMT_CNTL;
	uपूर्णांक32_t AFMT_AVI_INFO0;
	uपूर्णांक32_t AFMT_AVI_INFO1;
	uपूर्णांक32_t AFMT_AVI_INFO2;
	uपूर्णांक32_t AFMT_AVI_INFO3;
	uपूर्णांक32_t AFMT_GENERIC_0;
	uपूर्णांक32_t AFMT_GENERIC_1;
	uपूर्णांक32_t AFMT_GENERIC_2;
	uपूर्णांक32_t AFMT_GENERIC_3;
	uपूर्णांक32_t AFMT_GENERIC_4;
	uपूर्णांक32_t AFMT_GENERIC_5;
	uपूर्णांक32_t AFMT_GENERIC_6;
	uपूर्णांक32_t AFMT_GENERIC_7;
	uपूर्णांक32_t AFMT_GENERIC_HDR;
	uपूर्णांक32_t AFMT_INFOFRAME_CONTROL0;
	uपूर्णांक32_t AFMT_VBI_PACKET_CONTROL;
	uपूर्णांक32_t AFMT_VBI_PACKET_CONTROL1;
	uपूर्णांक32_t AFMT_AUDIO_PACKET_CONTROL;
	uपूर्णांक32_t AFMT_AUDIO_PACKET_CONTROL2;
	uपूर्णांक32_t AFMT_AUDIO_SRC_CONTROL;
	uपूर्णांक32_t AFMT_60958_0;
	uपूर्णांक32_t AFMT_60958_1;
	uपूर्णांक32_t AFMT_60958_2;
	uपूर्णांक32_t DIG_FE_CNTL;
	uपूर्णांक32_t DIG_FE_CNTL2;
	uपूर्णांक32_t DP_MSE_RATE_CNTL;
	uपूर्णांक32_t DP_MSE_RATE_UPDATE;
	uपूर्णांक32_t DP_PIXEL_FORMAT;
	uपूर्णांक32_t DP_SEC_CNTL;
	uपूर्णांक32_t DP_SEC_CNTL1;
	uपूर्णांक32_t DP_SEC_CNTL2;
	uपूर्णांक32_t DP_SEC_CNTL5;
	uपूर्णांक32_t DP_SEC_CNTL6;
	uपूर्णांक32_t DP_STEER_FIFO;
	uपूर्णांक32_t DP_VID_M;
	uपूर्णांक32_t DP_VID_N;
	uपूर्णांक32_t DP_VID_STREAM_CNTL;
	uपूर्णांक32_t DP_VID_TIMING;
	uपूर्णांक32_t DP_SEC_AUD_N;
	uपूर्णांक32_t DP_SEC_TIMESTAMP;
	uपूर्णांक32_t HDMI_CONTROL;
	uपूर्णांक32_t HDMI_GC;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL0;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL1;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL2;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL3;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL4;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL5;
	uपूर्णांक32_t HDMI_INFOFRAME_CONTROL0;
	uपूर्णांक32_t HDMI_INFOFRAME_CONTROL1;
	uपूर्णांक32_t HDMI_VBI_PACKET_CONTROL;
	uपूर्णांक32_t HDMI_AUDIO_PACKET_CONTROL;
	uपूर्णांक32_t HDMI_ACR_PACKET_CONTROL;
	uपूर्णांक32_t HDMI_ACR_32_0;
	uपूर्णांक32_t HDMI_ACR_32_1;
	uपूर्णांक32_t HDMI_ACR_44_0;
	uपूर्णांक32_t HDMI_ACR_44_1;
	uपूर्णांक32_t HDMI_ACR_48_0;
	uपूर्णांक32_t HDMI_ACR_48_1;
	uपूर्णांक32_t DP_DB_CNTL;
	uपूर्णांक32_t DP_MSA_MISC;
	uपूर्णांक32_t DP_MSA_VBID_MISC;
	uपूर्णांक32_t DP_MSA_COLORIMETRY;
	uपूर्णांक32_t DP_MSA_TIMING_PARAM1;
	uपूर्णांक32_t DP_MSA_TIMING_PARAM2;
	uपूर्णांक32_t DP_MSA_TIMING_PARAM3;
	uपूर्णांक32_t DP_MSA_TIMING_PARAM4;
	uपूर्णांक32_t HDMI_DB_CONTROL;
	uपूर्णांक32_t DP_DSC_CNTL;
	uपूर्णांक32_t DP_DSC_BYTES_PER_PIXEL;
	uपूर्णांक32_t DME_CONTROL;
	uपूर्णांक32_t DP_SEC_METADATA_TRANSMISSION;
	uपूर्णांक32_t HDMI_METADATA_PACKET_CONTROL;
	uपूर्णांक32_t DP_SEC_FRAMING4;
	uपूर्णांक32_t DP_GSP11_CNTL;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL6;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL7;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL8;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL9;
	uपूर्णांक32_t HDMI_GENERIC_PACKET_CONTROL10;
	uपूर्णांक32_t DIG_CLOCK_PATTERN;
पूर्ण;


#घोषणा SE_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा SE_COMMON_MASK_SH_LIST_SOC_BASE(mask_sh)\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_INDEX, mask_sh),\
	SE_SF(DIG0_AFMT_GENERIC_HDR, AFMT_GENERIC_HB0, mask_sh),\
	SE_SF(DIG0_AFMT_GENERIC_HDR, AFMT_GENERIC_HB1, mask_sh),\
	SE_SF(DIG0_AFMT_GENERIC_HDR, AFMT_GENERIC_HB2, mask_sh),\
	SE_SF(DIG0_AFMT_GENERIC_HDR, AFMT_GENERIC_HB3, mask_sh),\
	SE_SF(DP0_DP_PIXEL_FORMAT, DP_PIXEL_ENCODING, mask_sh),\
	SE_SF(DP0_DP_PIXEL_FORMAT, DP_COMPONENT_DEPTH, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_PACKET_GEN_VERSION, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_KEEPOUT_MODE, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_DEEP_COLOR_ENABLE, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_DEEP_COLOR_DEPTH, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_DATA_SCRAMBLE_EN, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_NO_EXTRA_शून्य_PACKET_FILLED, mask_sh),\
	SE_SF(DIG0_HDMI_VBI_PACKET_CONTROL, HDMI_GC_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_VBI_PACKET_CONTROL, HDMI_GC_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_VBI_PACKET_CONTROL, HDMI_शून्य_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_INFOFRAME_CONTROL0, HDMI_AUDIO_INFO_SEND, mask_sh),\
	SE_SF(DIG0_AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, mask_sh),\
	SE_SF(DIG0_HDMI_INFOFRAME_CONTROL1, HDMI_AUDIO_INFO_LINE, mask_sh),\
	SE_SF(DIG0_HDMI_GC, HDMI_GC_AVMUTE, mask_sh),\
	SE_SF(DP0_DP_MSE_RATE_CNTL, DP_MSE_RATE_X, mask_sh),\
	SE_SF(DP0_DP_MSE_RATE_CNTL, DP_MSE_RATE_Y, mask_sh),\
	SE_SF(DP0_DP_MSE_RATE_UPDATE, DP_MSE_RATE_UPDATE_PENDING, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP0_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP1_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP2_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP3_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_MPG_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL2, DP_SEC_GSP4_SEND, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL2, DP_SEC_GSP4_SEND_PENDING, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL4, DP_SEC_GSP4_LINE_NUM, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL2, DP_SEC_GSP4_SEND_ANY_LINE, mask_sh),\
	SE_SF(DP0_DP_VID_STREAM_CNTL, DP_VID_STREAM_DIS_DEFER, mask_sh),\
	SE_SF(DP0_DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, mask_sh),\
	SE_SF(DP0_DP_VID_STREAM_CNTL, DP_VID_STREAM_STATUS, mask_sh),\
	SE_SF(DP0_DP_STEER_FIFO, DP_STEER_FIFO_RESET, mask_sh),\
	SE_SF(DP0_DP_VID_TIMING, DP_VID_M_N_GEN_EN, mask_sh),\
	SE_SF(DP0_DP_VID_N, DP_VID_N, mask_sh),\
	SE_SF(DP0_DP_VID_M, DP_VID_M, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTL, DIG_START, mask_sh),\
	SE_SF(DIG0_AFMT_AUDIO_SRC_CONTROL, AFMT_AUDIO_SRC_SELECT, mask_sh),\
	SE_SF(DIG0_AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_CHANNEL_ENABLE, mask_sh),\
	SE_SF(DIG0_HDMI_AUDIO_PACKET_CONTROL, HDMI_AUDIO_PACKETS_PER_LINE, mask_sh),\
	SE_SF(DIG0_HDMI_AUDIO_PACKET_CONTROL, HDMI_AUDIO_DELAY_EN, mask_sh),\
	SE_SF(DIG0_AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_LAYOUT_OVRD, mask_sh),\
	SE_SF(DIG0_AFMT_AUDIO_PACKET_CONTROL2, AFMT_60958_OSF_OVRD, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_PACKET_CONTROL, HDMI_ACR_AUTO_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_PACKET_CONTROL, HDMI_ACR_SOURCE, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_PACKET_CONTROL, HDMI_ACR_AUDIO_PRIORITY, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_32_0, HDMI_ACR_CTS_32, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_32_1, HDMI_ACR_N_32, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_44_0, HDMI_ACR_CTS_44, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_44_1, HDMI_ACR_N_44, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_48_0, HDMI_ACR_CTS_48, mask_sh),\
	SE_SF(DIG0_HDMI_ACR_48_1, HDMI_ACR_N_48, mask_sh),\
	SE_SF(DIG0_AFMT_60958_0, AFMT_60958_CS_CHANNEL_NUMBER_L, mask_sh),\
	SE_SF(DIG0_AFMT_60958_0, AFMT_60958_CS_CLOCK_ACCURACY, mask_sh),\
	SE_SF(DIG0_AFMT_60958_1, AFMT_60958_CS_CHANNEL_NUMBER_R, mask_sh),\
	SE_SF(DIG0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_2, mask_sh),\
	SE_SF(DIG0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_3, mask_sh),\
	SE_SF(DIG0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_4, mask_sh),\
	SE_SF(DIG0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_5, mask_sh),\
	SE_SF(DIG0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_6, mask_sh),\
	SE_SF(DIG0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_7, mask_sh),\
	SE_SF(DP0_DP_SEC_AUD_N, DP_SEC_AUD_N, mask_sh),\
	SE_SF(DP0_DP_SEC_TIMESTAMP, DP_SEC_TIMESTAMP_MODE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_ASP_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_ATP_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_AIP_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_ACM_ENABLE, mask_sh),\
	SE_SF(DIG0_AFMT_AUDIO_PACKET_CONTROL, AFMT_AUDIO_SAMPLE_SEND, mask_sh),\
	SE_SF(DIG0_AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, mask_sh),\
	SE_SF(DIG0_HDMI_CONTROL, HDMI_CLOCK_CHANNEL_RATE, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTL, TMDS_PIXEL_ENCODING, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTL, TMDS_COLOR_FORMAT, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTL, DIG_STEREOSYNC_SELECT, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTL, DIG_STEREOSYNC_GATE_EN, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_LOCK_STATUS, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_CONFLICT_CLR, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC0_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC1_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC2_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC3_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC4_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC4_IMMEDIATE_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC5_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC6_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC7_FRAME_UPDATE_PENDING, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC0_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC1_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC2_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC3_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC4_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC0_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC1_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC2_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC3_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC4_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC5_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC6_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC7_IMMEDIATE_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC5_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC6_FRAME_UPDATE, mask_sh),\
	SE_SF(DIG0_AFMT_VBI_PACKET_CONTROL1, AFMT_GENERIC7_FRAME_UPDATE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP4_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP5_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP6_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL, DP_SEC_GSP7_ENABLE, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL2, DP_SEC_GSP7_PPS, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL2, DP_SEC_GSP7_SEND, mask_sh),\
	SE_SF(DP0_DP_SEC_CNTL6, DP_SEC_GSP7_LINE_NUM, mask_sh),\
	SE_SF(DP0_DP_DB_CNTL, DP_DB_DISABLE, mask_sh),\
	SE_SF(DP0_DP_MSA_COLORIMETRY, DP_MSA_MISC0, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM1, DP_MSA_HTOTAL, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM1, DP_MSA_VTOTAL, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM2, DP_MSA_HSTART, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM2, DP_MSA_VSTART, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM3, DP_MSA_HSYNCWIDTH, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM3, DP_MSA_HSYNCPOLARITY, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM3, DP_MSA_VSYNCWIDTH, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM3, DP_MSA_VSYNCPOLARITY, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM4, DP_MSA_HWIDTH, mask_sh),\
	SE_SF(DP0_DP_MSA_TIMING_PARAM4, DP_MSA_VHEIGHT, mask_sh),\
	SE_SF(DIG0_HDMI_DB_CONTROL, HDMI_DB_DISABLE, mask_sh),\
	SE_SF(DP0_DP_VID_TIMING, DP_VID_N_MUL, mask_sh),\
	SE_SF(DIG0_DIG_FE_CNTL, DIG_SOURCE_SELECT, mask_sh),\
	SE_SF(DIG0_DIG_CLOCK_PATTERN, DIG_CLOCK_PATTERN, mask_sh)

#घोषणा SE_COMMON_MASK_SH_LIST_SOC(mask_sh)\
	SE_COMMON_MASK_SH_LIST_SOC_BASE(mask_sh)

#घोषणा SE_COMMON_MASK_SH_LIST_DCN10(mask_sh)\
	SE_COMMON_MASK_SH_LIST_SOC(mask_sh),\
	SE_SF(DIG0_HDMI_GENERIC_PACKET_CONTROL0, HDMI_GENERIC0_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENERIC_PACKET_CONTROL0, HDMI_GENERIC0_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENERIC_PACKET_CONTROL0, HDMI_GENERIC0_LINE, mask_sh),\
	SE_SF(DIG0_HDMI_GENERIC_PACKET_CONTROL0, HDMI_GENERIC1_CONT, mask_sh),\
	SE_SF(DIG0_HDMI_GENERIC_PACKET_CONTROL0, HDMI_GENERIC1_SEND, mask_sh),\
	SE_SF(DIG0_HDMI_GENERIC_PACKET_CONTROL0, HDMI_GENERIC1_LINE, mask_sh)


#घोषणा SE_REG_FIELD_LIST_DCN1_0(type) \
	type AFMT_GENERIC_INDEX;\
	type AFMT_GENERIC_HB0;\
	type AFMT_GENERIC_HB1;\
	type AFMT_GENERIC_HB2;\
	type AFMT_GENERIC_HB3;\
	type AFMT_GENERIC_LOCK_STATUS;\
	type AFMT_GENERIC_CONFLICT;\
	type AFMT_GENERIC_CONFLICT_CLR;\
	type AFMT_GENERIC0_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC1_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC2_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC3_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC4_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC4_IMMEDIATE_UPDATE_PENDING;\
	type AFMT_GENERIC5_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC6_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC7_FRAME_UPDATE_PENDING;\
	type AFMT_GENERIC0_FRAME_UPDATE;\
	type AFMT_GENERIC1_FRAME_UPDATE;\
	type AFMT_GENERIC2_FRAME_UPDATE;\
	type AFMT_GENERIC3_FRAME_UPDATE;\
	type AFMT_GENERIC4_FRAME_UPDATE;\
	type AFMT_GENERIC0_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC1_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC2_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC3_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC4_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC5_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC6_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC7_IMMEDIATE_UPDATE;\
	type AFMT_GENERIC5_FRAME_UPDATE;\
	type AFMT_GENERIC6_FRAME_UPDATE;\
	type AFMT_GENERIC7_FRAME_UPDATE;\
	type HDMI_GENERIC0_CONT;\
	type HDMI_GENERIC0_SEND;\
	type HDMI_GENERIC0_LINE;\
	type HDMI_GENERIC1_CONT;\
	type HDMI_GENERIC1_SEND;\
	type HDMI_GENERIC1_LINE;\
	type HDMI_GENERIC2_CONT;\
	type HDMI_GENERIC2_SEND;\
	type HDMI_GENERIC2_LINE;\
	type HDMI_GENERIC3_CONT;\
	type HDMI_GENERIC3_SEND;\
	type HDMI_GENERIC3_LINE;\
	type HDMI_GENERIC4_CONT;\
	type HDMI_GENERIC4_SEND;\
	type HDMI_GENERIC4_LINE;\
	type HDMI_GENERIC5_CONT;\
	type HDMI_GENERIC5_SEND;\
	type HDMI_GENERIC5_LINE;\
	type HDMI_GENERIC6_CONT;\
	type HDMI_GENERIC6_SEND;\
	type HDMI_GENERIC6_LINE;\
	type HDMI_GENERIC7_CONT;\
	type HDMI_GENERIC7_SEND;\
	type HDMI_GENERIC7_LINE;\
	type DP_PIXEL_ENCODING;\
	type DP_COMPONENT_DEPTH;\
	type HDMI_PACKET_GEN_VERSION;\
	type HDMI_KEEPOUT_MODE;\
	type HDMI_DEEP_COLOR_ENABLE;\
	type HDMI_CLOCK_CHANNEL_RATE;\
	type HDMI_DEEP_COLOR_DEPTH;\
	type HDMI_GC_CONT;\
	type HDMI_GC_SEND;\
	type HDMI_शून्य_SEND;\
	type HDMI_DATA_SCRAMBLE_EN;\
	type HDMI_NO_EXTRA_शून्य_PACKET_FILLED;\
	type HDMI_AUDIO_INFO_SEND;\
	type AFMT_AUDIO_INFO_UPDATE;\
	type HDMI_AUDIO_INFO_LINE;\
	type HDMI_GC_AVMUTE;\
	type DP_MSE_RATE_X;\
	type DP_MSE_RATE_Y;\
	type DP_MSE_RATE_UPDATE_PENDING;\
	type DP_SEC_GSP0_ENABLE;\
	type DP_SEC_STREAM_ENABLE;\
	type DP_SEC_GSP1_ENABLE;\
	type DP_SEC_GSP2_ENABLE;\
	type DP_SEC_GSP3_ENABLE;\
	type DP_SEC_GSP4_ENABLE;\
	type DP_SEC_GSP5_ENABLE;\
	type DP_SEC_GSP5_LINE_NUM;\
	type DP_SEC_GSP5_LINE_REFERENCE;\
	type DP_SEC_GSP6_ENABLE;\
	type DP_SEC_GSP7_ENABLE;\
	type DP_SEC_GSP7_PPS;\
	type DP_SEC_GSP7_SEND;\
	type DP_SEC_GSP4_SEND;\
	type DP_SEC_GSP4_SEND_PENDING;\
	type DP_SEC_GSP4_LINE_NUM;\
	type DP_SEC_GSP4_SEND_ANY_LINE;\
	type DP_SEC_MPG_ENABLE;\
	type DP_VID_STREAM_DIS_DEFER;\
	type DP_VID_STREAM_ENABLE;\
	type DP_VID_STREAM_STATUS;\
	type DP_STEER_FIFO_RESET;\
	type DP_VID_M_N_GEN_EN;\
	type DP_VID_N;\
	type DP_VID_M;\
	type DIG_START;\
	type AFMT_AUDIO_SRC_SELECT;\
	type AFMT_AUDIO_CHANNEL_ENABLE;\
	type HDMI_AUDIO_PACKETS_PER_LINE;\
	type HDMI_AUDIO_DELAY_EN;\
	type AFMT_60958_CS_UPDATE;\
	type AFMT_AUDIO_LAYOUT_OVRD;\
	type AFMT_60958_OSF_OVRD;\
	type HDMI_ACR_AUTO_SEND;\
	type HDMI_ACR_SOURCE;\
	type HDMI_ACR_AUDIO_PRIORITY;\
	type HDMI_ACR_CTS_32;\
	type HDMI_ACR_N_32;\
	type HDMI_ACR_CTS_44;\
	type HDMI_ACR_N_44;\
	type HDMI_ACR_CTS_48;\
	type HDMI_ACR_N_48;\
	type AFMT_60958_CS_CHANNEL_NUMBER_L;\
	type AFMT_60958_CS_CLOCK_ACCURACY;\
	type AFMT_60958_CS_CHANNEL_NUMBER_R;\
	type AFMT_60958_CS_CHANNEL_NUMBER_2;\
	type AFMT_60958_CS_CHANNEL_NUMBER_3;\
	type AFMT_60958_CS_CHANNEL_NUMBER_4;\
	type AFMT_60958_CS_CHANNEL_NUMBER_5;\
	type AFMT_60958_CS_CHANNEL_NUMBER_6;\
	type AFMT_60958_CS_CHANNEL_NUMBER_7;\
	type DP_SEC_AUD_N;\
	type DP_SEC_TIMESTAMP_MODE;\
	type DP_SEC_ASP_ENABLE;\
	type DP_SEC_ATP_ENABLE;\
	type DP_SEC_AIP_ENABLE;\
	type DP_SEC_ACM_ENABLE;\
	type DP_SEC_GSP7_LINE_NUM;\
	type AFMT_AUDIO_SAMPLE_SEND;\
	type AFMT_AUDIO_CLOCK_EN;\
	type TMDS_PIXEL_ENCODING;\
	type TMDS_COLOR_FORMAT;\
	type DIG_STEREOSYNC_SELECT;\
	type DIG_STEREOSYNC_GATE_EN;\
	type DP_DB_DISABLE;\
	type DP_MSA_MISC0;\
	type DP_MSA_HTOTAL;\
	type DP_MSA_VTOTAL;\
	type DP_MSA_HSTART;\
	type DP_MSA_VSTART;\
	type DP_MSA_HSYNCWIDTH;\
	type DP_MSA_HSYNCPOLARITY;\
	type DP_MSA_VSYNCWIDTH;\
	type DP_MSA_VSYNCPOLARITY;\
	type DP_MSA_HWIDTH;\
	type DP_MSA_VHEIGHT;\
	type HDMI_DB_DISABLE;\
	type DP_VID_N_MUL;\
	type DP_VID_M_DOUBLE_VALUE_EN;\
	type DIG_SOURCE_SELECT;\
	type DIG_CLOCK_PATTERN

#घोषणा SE_REG_FIELD_LIST_DCN2_0(type) \
	type DP_DSC_MODE;\
	type DP_DSC_SLICE_WIDTH;\
	type DP_DSC_BYTES_PER_PIXEL;\
	type DP_VBID6_LINE_REFERENCE;\
	type DP_VBID6_LINE_NUM;\
	type METADATA_ENGINE_EN;\
	type METADATA_HUBP_REQUESTOR_ID;\
	type METADATA_STREAM_TYPE;\
	type DP_SEC_METADATA_PACKET_ENABLE;\
	type DP_SEC_METADATA_PACKET_LINE_REFERENCE;\
	type DP_SEC_METADATA_PACKET_LINE;\
	type HDMI_METADATA_PACKET_ENABLE;\
	type HDMI_METADATA_PACKET_LINE_REFERENCE;\
	type HDMI_METADATA_PACKET_LINE;\
	type DOLBY_VISION_EN;\
	type DP_PIXEL_COMBINE;\
	type DP_SST_SDP_SPLITTING

#घोषणा SE_REG_FIELD_LIST_DCN3_0(type) \
	type HDMI_GENERIC8_CONT;\
	type HDMI_GENERIC8_SEND;\
	type HDMI_GENERIC8_LINE;\
	type HDMI_GENERIC9_CONT;\
	type HDMI_GENERIC9_SEND;\
	type HDMI_GENERIC9_LINE;\
	type HDMI_GENERIC10_CONT;\
	type HDMI_GENERIC10_SEND;\
	type HDMI_GENERIC10_LINE;\
	type HDMI_GENERIC11_CONT;\
	type HDMI_GENERIC11_SEND;\
	type HDMI_GENERIC11_LINE;\
	type HDMI_GENERIC12_CONT;\
	type HDMI_GENERIC12_SEND;\
	type HDMI_GENERIC12_LINE;\
	type HDMI_GENERIC13_CONT;\
	type HDMI_GENERIC13_SEND;\
	type HDMI_GENERIC13_LINE;\
	type HDMI_GENERIC14_CONT;\
	type HDMI_GENERIC14_SEND;\
	type HDMI_GENERIC14_LINE;\
	type DP_SEC_GSP11_PPS;\
	type DP_SEC_GSP11_ENABLE;\
	type DP_SEC_GSP11_LINE_NUM

काष्ठा dcn10_stream_encoder_shअगरt अणु
	SE_REG_FIELD_LIST_DCN1_0(uपूर्णांक8_t);
	SE_REG_FIELD_LIST_DCN2_0(uपूर्णांक8_t);
	SE_REG_FIELD_LIST_DCN3_0(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn10_stream_encoder_mask अणु
	SE_REG_FIELD_LIST_DCN1_0(uपूर्णांक32_t);
	SE_REG_FIELD_LIST_DCN2_0(uपूर्णांक32_t);
	SE_REG_FIELD_LIST_DCN3_0(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn10_stream_encoder अणु
	काष्ठा stream_encoder base;
	स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn10_stream_encoder_shअगरt *se_shअगरt;
	स्थिर काष्ठा dcn10_stream_encoder_mask *se_mask;
पूर्ण;

व्योम dcn10_stream_encoder_स्थिरruct(
	काष्ठा dcn10_stream_encoder *enc1,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bp,
	क्रमागत engine_id eng_id,
	स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_stream_encoder_shअगरt *se_shअगरt,
	स्थिर काष्ठा dcn10_stream_encoder_mask *se_mask);

व्योम enc1_update_generic_info_packet(
	काष्ठा dcn10_stream_encoder *enc1,
	uपूर्णांक32_t packet_index,
	स्थिर काष्ठा dc_info_packet *info_packet);

व्योम enc1_stream_encoder_dp_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	क्रमागत dc_color_space output_color_space,
	bool use_vsc_sdp_क्रम_colorimetry,
	uपूर्णांक32_t enable_sdp_splitting);

व्योम enc1_stream_encoder_hdmi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	पूर्णांक actual_pix_clk_khz,
	bool enable_audio);

व्योम enc1_stream_encoder_dvi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	bool is_dual_link);

व्योम enc1_stream_encoder_set_throttled_vcp_size(
	काष्ठा stream_encoder *enc,
	काष्ठा fixed31_32 avg_समय_slots_per_mtp);

व्योम enc1_stream_encoder_update_dp_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame);

व्योम enc1_stream_encoder_send_immediate_sdp_message(
	काष्ठा stream_encoder *enc,
	स्थिर uपूर्णांक8_t *custom_sdp_message,
				अचिन्हित पूर्णांक sdp_message_size);

व्योम enc1_stream_encoder_stop_dp_info_packets(
	काष्ठा stream_encoder *enc);

व्योम enc1_stream_encoder_dp_blank(
	काष्ठा stream_encoder *enc);

व्योम enc1_stream_encoder_dp_unblank(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_unblank_param *param);

व्योम enc1_setup_stereo_sync(
	काष्ठा stream_encoder *enc,
	पूर्णांक tg_inst, bool enable);

व्योम enc1_stream_encoder_set_avmute(
	काष्ठा stream_encoder *enc,
	bool enable);

व्योम enc1_se_audio_mute_control(
	काष्ठा stream_encoder *enc,
	bool mute);

व्योम enc1_se_dp_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *info);

व्योम enc1_se_dp_audio_enable(
	काष्ठा stream_encoder *enc);

व्योम enc1_se_dp_audio_disable(
	काष्ठा stream_encoder *enc);

व्योम enc1_se_hdmi_audio_setup(
	काष्ठा stream_encoder *enc,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *info,
	काष्ठा audio_crtc_info *audio_crtc_info);

व्योम enc1_se_hdmi_audio_disable(
	काष्ठा stream_encoder *enc);

व्योम enc1_dig_connect_to_otg(
	काष्ठा stream_encoder *enc,
	पूर्णांक tg_inst);

अचिन्हित पूर्णांक enc1_dig_source_otg(
	काष्ठा stream_encoder *enc);

व्योम enc1_stream_encoder_set_stream_attribute_helper(
	काष्ठा dcn10_stream_encoder *enc1,
	काष्ठा dc_crtc_timing *crtc_timing);

व्योम enc1_se_enable_audio_घड़ी(
	काष्ठा stream_encoder *enc,
	bool enable);

व्योम enc1_se_enable_dp_audio(
	काष्ठा stream_encoder *enc);

व्योम get_audio_घड़ी_info(
	क्रमागत dc_color_depth color_depth,
	uपूर्णांक32_t crtc_pixel_घड़ी_100Hz,
	uपूर्णांक32_t actual_pixel_घड़ी_100Hz,
	काष्ठा audio_घड़ी_info *audio_घड़ी_info);

व्योम enc1_reset_hdmi_stream_attribute(
	काष्ठा stream_encoder *enc);

bool enc1_stream_encoder_dp_get_pixel_क्रमmat(
	काष्ठा stream_encoder *enc,
	क्रमागत dc_pixel_encoding *encoding,
	क्रमागत dc_color_depth *depth);

#पूर्ण_अगर /* __DC_STREAM_ENCODER_DCN10_H__ */
