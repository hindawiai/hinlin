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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "virtual_stream_encoder.h"

अटल व्योम भव_stream_encoder_dp_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	क्रमागत dc_color_space output_color_space,
	bool use_vsc_sdp_क्रम_colorimetry,
	uपूर्णांक32_t enable_sdp_splitting) अणुपूर्ण

अटल व्योम भव_stream_encoder_hdmi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	पूर्णांक actual_pix_clk_khz,
	bool enable_audio) अणुपूर्ण

अटल व्योम भव_stream_encoder_dvi_set_stream_attribute(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_crtc_timing *crtc_timing,
	bool is_dual_link) अणुपूर्ण

अटल व्योम भव_stream_encoder_set_throttled_vcp_size(
	काष्ठा stream_encoder *enc,
	काष्ठा fixed31_32 avg_समय_slots_per_mtp)
अणुपूर्ण

अटल व्योम भव_stream_encoder_update_hdmi_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame) अणुपूर्ण

अटल व्योम भव_stream_encoder_stop_hdmi_info_packets(
	काष्ठा stream_encoder *enc) अणुपूर्ण

अटल व्योम भव_stream_encoder_set_avmute(
	काष्ठा stream_encoder *enc,
	bool enable) अणुपूर्ण
अटल व्योम भव_stream_encoder_update_dp_info_packets(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_info_frame *info_frame) अणुपूर्ण

अटल व्योम भव_stream_encoder_stop_dp_info_packets(
	काष्ठा stream_encoder *enc) अणुपूर्ण

अटल व्योम भव_stream_encoder_dp_blank(
	काष्ठा stream_encoder *enc) अणुपूर्ण

अटल व्योम भव_stream_encoder_dp_unblank(
	काष्ठा stream_encoder *enc,
	स्थिर काष्ठा encoder_unblank_param *param) अणुपूर्ण

अटल व्योम भव_audio_mute_control(
	काष्ठा stream_encoder *enc,
	bool mute) अणुपूर्ण

अटल व्योम भव_stream_encoder_reset_hdmi_stream_attribute(
		काष्ठा stream_encoder *enc)
अणुपूर्ण

अटल व्योम भव_enc_dp_set_odm_combine(
	काष्ठा stream_encoder *enc,
	bool odm_combine)
अणुपूर्ण

अटल व्योम भव_dig_connect_to_otg(
		काष्ठा stream_encoder *enc,
		पूर्णांक tg_inst)
अणुपूर्ण

अटल व्योम भव_setup_stereo_sync(
			काष्ठा stream_encoder *enc,
			पूर्णांक tg_inst,
			bool enable)
अणुपूर्ण

अटल व्योम भव_stream_encoder_set_dsc_pps_info_packet(
		काष्ठा stream_encoder *enc,
		bool enable,
		uपूर्णांक8_t *dsc_packed_pps)
अणुपूर्ण

अटल स्थिर काष्ठा stream_encoder_funcs भव_str_enc_funcs = अणु
	.dp_set_odm_combine =
		भव_enc_dp_set_odm_combine,
	.dp_set_stream_attribute =
		भव_stream_encoder_dp_set_stream_attribute,
	.hdmi_set_stream_attribute =
		भव_stream_encoder_hdmi_set_stream_attribute,
	.dvi_set_stream_attribute =
		भव_stream_encoder_dvi_set_stream_attribute,
	.set_throttled_vcp_size =
		भव_stream_encoder_set_throttled_vcp_size,
	.update_hdmi_info_packets =
		भव_stream_encoder_update_hdmi_info_packets,
	.stop_hdmi_info_packets =
		भव_stream_encoder_stop_hdmi_info_packets,
	.update_dp_info_packets =
		भव_stream_encoder_update_dp_info_packets,
	.stop_dp_info_packets =
		भव_stream_encoder_stop_dp_info_packets,
	.dp_blank =
		भव_stream_encoder_dp_blank,
	.dp_unblank =
		भव_stream_encoder_dp_unblank,

	.audio_mute_control = भव_audio_mute_control,
	.set_avmute = भव_stream_encoder_set_avmute,
	.hdmi_reset_stream_attribute = भव_stream_encoder_reset_hdmi_stream_attribute,
	.dig_connect_to_otg = भव_dig_connect_to_otg,
	.setup_stereo_sync = भव_setup_stereo_sync,
	.dp_set_dsc_pps_info_packet = भव_stream_encoder_set_dsc_pps_info_packet,
पूर्ण;

bool भव_stream_encoder_स्थिरruct(
	काष्ठा stream_encoder *enc,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bp)
अणु
	अगर (!enc)
		वापस false;
	अगर (!bp)
		वापस false;

	enc->funcs = &भव_str_enc_funcs;
	enc->ctx = ctx;
	enc->id = ENGINE_ID_VIRTUAL;
	enc->bp = bp;

	वापस true;
पूर्ण

काष्ठा stream_encoder *भव_stream_encoder_create(
	काष्ठा dc_context *ctx, काष्ठा dc_bios *bp)
अणु
	काष्ठा stream_encoder *enc = kzalloc(माप(*enc), GFP_KERNEL);

	अगर (!enc)
		वापस शून्य;

	अगर (भव_stream_encoder_स्थिरruct(enc, ctx, bp))
		वापस enc;

	BREAK_TO_DEBUGGER();
	kमुक्त(enc);
	वापस शून्य;
पूर्ण

