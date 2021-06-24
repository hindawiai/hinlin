<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
/*
 * stream_encoder.h
 *
 */

#अगर_अघोषित STREAM_ENCODER_H_
#घोषणा STREAM_ENCODER_H_

#समावेश "audio_types.h"
#समावेश "hw_shared.h"

काष्ठा dc_bios;
काष्ठा dc_context;
काष्ठा dc_crtc_timing;

क्रमागत dp_pixel_encoding_type अणु
	DP_PIXEL_ENCODING_TYPE_RGB444		= 0x00000000,
	DP_PIXEL_ENCODING_TYPE_YCBCR422		= 0x00000001,
	DP_PIXEL_ENCODING_TYPE_YCBCR444		= 0x00000002,
	DP_PIXEL_ENCODING_TYPE_RGB_WIDE_GAMUT	= 0x00000003,
	DP_PIXEL_ENCODING_TYPE_Y_ONLY		= 0x00000004,
	DP_PIXEL_ENCODING_TYPE_YCBCR420		= 0x00000005
पूर्ण;

क्रमागत dp_component_depth अणु
	DP_COMPONENT_PIXEL_DEPTH_6BPC		= 0x00000000,
	DP_COMPONENT_PIXEL_DEPTH_8BPC		= 0x00000001,
	DP_COMPONENT_PIXEL_DEPTH_10BPC		= 0x00000002,
	DP_COMPONENT_PIXEL_DEPTH_12BPC		= 0x00000003,
	DP_COMPONENT_PIXEL_DEPTH_16BPC		= 0x00000004
पूर्ण;

काष्ठा audio_घड़ी_info अणु
	/* pixel घड़ी frequency*/
	uपूर्णांक32_t pixel_घड़ी_in_10khz;
	/* N - 32KHz audio */
	uपूर्णांक32_t n_32khz;
	/* CTS - 32KHz audio*/
	uपूर्णांक32_t cts_32khz;
	uपूर्णांक32_t n_44khz;
	uपूर्णांक32_t cts_44khz;
	uपूर्णांक32_t n_48khz;
	uपूर्णांक32_t cts_48khz;
पूर्ण;

क्रमागत dynamic_metadata_mode अणु
	dmdata_dp,
	dmdata_hdmi,
	dmdata_करोlby_vision
पूर्ण;

काष्ठा encoder_info_frame अणु
	/* auxiliary video inक्रमmation */
	काष्ठा dc_info_packet avi;
	काष्ठा dc_info_packet gamut;
	काष्ठा dc_info_packet venकरोr;
	काष्ठा dc_info_packet hfvsअगर;
	/* source product description */
	काष्ठा dc_info_packet spd;
	/* video stream configuration */
	काष्ठा dc_info_packet vsc;
	/* HDR Static MetaData */
	काष्ठा dc_info_packet hdrsmd;
पूर्ण;

काष्ठा encoder_unblank_param अणु
	काष्ठा dc_link_settings link_settings;
	काष्ठा dc_crtc_timing timing;
	पूर्णांक opp_cnt;
पूर्ण;

काष्ठा encoder_set_dp_phy_pattern_param अणु
	क्रमागत dp_test_pattern dp_phy_pattern;
	स्थिर uपूर्णांक8_t *custom_pattern;
	uपूर्णांक32_t custom_pattern_size;
	क्रमागत dp_panel_mode dp_panel_mode;
पूर्ण;

काष्ठा stream_encoder अणु
	स्थिर काष्ठा stream_encoder_funcs *funcs;
	काष्ठा dc_context *ctx;
	काष्ठा dc_bios *bp;
	क्रमागत engine_id id;
	uपूर्णांक32_t stream_enc_inst;
	काष्ठा vpg *vpg;
	काष्ठा afmt *afmt;
पूर्ण;

काष्ठा enc_state अणु
	uपूर्णांक32_t dsc_mode;  // DISABLED  0; 1 or 2 indicate enabled state.
	uपूर्णांक32_t dsc_slice_width;
	uपूर्णांक32_t sec_gsp_pps_line_num;
	uपूर्णांक32_t vbid6_line_reference;
	uपूर्णांक32_t vbid6_line_num;
	uपूर्णांक32_t sec_gsp_pps_enable;
	uपूर्णांक32_t sec_stream_enable;
पूर्ण;

काष्ठा stream_encoder_funcs अणु
	व्योम (*dp_set_stream_attribute)(
		काष्ठा stream_encoder *enc,
		काष्ठा dc_crtc_timing *crtc_timing,
		क्रमागत dc_color_space output_color_space,
		bool use_vsc_sdp_क्रम_colorimetry,
		uपूर्णांक32_t enable_sdp_splitting);

	व्योम (*hdmi_set_stream_attribute)(
		काष्ठा stream_encoder *enc,
		काष्ठा dc_crtc_timing *crtc_timing,
		पूर्णांक actual_pix_clk_khz,
		bool enable_audio);

	व्योम (*dvi_set_stream_attribute)(
		काष्ठा stream_encoder *enc,
		काष्ठा dc_crtc_timing *crtc_timing,
		bool is_dual_link);

	व्योम (*lvds_set_stream_attribute)(
		काष्ठा stream_encoder *enc,
		काष्ठा dc_crtc_timing *crtc_timing);

	व्योम (*set_throttled_vcp_size)(
		काष्ठा stream_encoder *enc,
		काष्ठा fixed31_32 avg_समय_slots_per_mtp);

	व्योम (*update_hdmi_info_packets)(
		काष्ठा stream_encoder *enc,
		स्थिर काष्ठा encoder_info_frame *info_frame);

	व्योम (*stop_hdmi_info_packets)(
		काष्ठा stream_encoder *enc);

	व्योम (*update_dp_info_packets)(
		काष्ठा stream_encoder *enc,
		स्थिर काष्ठा encoder_info_frame *info_frame);

	व्योम (*send_immediate_sdp_message)(
				काष्ठा stream_encoder *enc,
				स्थिर uपूर्णांक8_t *custom_sdp_message,
				अचिन्हित पूर्णांक sdp_message_size);

	व्योम (*stop_dp_info_packets)(
		काष्ठा stream_encoder *enc);

	व्योम (*dp_blank)(
		काष्ठा stream_encoder *enc);

	व्योम (*dp_unblank)(
		काष्ठा stream_encoder *enc,
		स्थिर काष्ठा encoder_unblank_param *param);

	व्योम (*audio_mute_control)(
		काष्ठा stream_encoder *enc, bool mute);

	व्योम (*dp_audio_setup)(
		काष्ठा stream_encoder *enc,
		अचिन्हित पूर्णांक az_inst,
		काष्ठा audio_info *info);

	व्योम (*dp_audio_enable) (
			काष्ठा stream_encoder *enc);

	व्योम (*dp_audio_disable) (
			काष्ठा stream_encoder *enc);

	व्योम (*hdmi_audio_setup)(
		काष्ठा stream_encoder *enc,
		अचिन्हित पूर्णांक az_inst,
		काष्ठा audio_info *info,
		काष्ठा audio_crtc_info *audio_crtc_info);

	व्योम (*hdmi_audio_disable) (
			काष्ठा stream_encoder *enc);

	व्योम (*setup_stereo_sync) (
			काष्ठा stream_encoder *enc,
			पूर्णांक tg_inst,
			bool enable);

	व्योम (*set_avmute)(
		काष्ठा stream_encoder *enc, bool enable);

	व्योम (*dig_connect_to_otg)(
		काष्ठा stream_encoder *enc,
		पूर्णांक tg_inst);

	व्योम (*hdmi_reset_stream_attribute)(
		काष्ठा stream_encoder *enc);

	अचिन्हित पूर्णांक (*dig_source_otg)(
		काष्ठा stream_encoder *enc);

	bool (*dp_get_pixel_क्रमmat)(
		काष्ठा stream_encoder *enc,
		क्रमागत dc_pixel_encoding *encoding,
		क्रमागत dc_color_depth *depth);

	व्योम (*enc_पढ़ो_state)(काष्ठा stream_encoder *enc, काष्ठा enc_state *s);

	व्योम (*dp_set_dsc_config)(
			काष्ठा stream_encoder *enc,
			क्रमागत optc_dsc_mode dsc_mode,
			uपूर्णांक32_t dsc_bytes_per_pixel,
			uपूर्णांक32_t dsc_slice_width);

	व्योम (*dp_set_dsc_pps_info_packet)(काष्ठा stream_encoder *enc,
				bool enable,
				uपूर्णांक8_t *dsc_packed_pps);

	व्योम (*set_dynamic_metadata)(काष्ठा stream_encoder *enc,
			bool enable,
			uपूर्णांक32_t hubp_requestor_id,
			क्रमागत dynamic_metadata_mode dmdata_mode);

	व्योम (*dp_set_odm_combine)(
		काष्ठा stream_encoder *enc,
		bool odm_combine);
पूर्ण;

#पूर्ण_अगर /* STREAM_ENCODER_H_ */
