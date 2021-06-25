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
 * link_encoder.h
 *
 *  Created on: Oct 6, 2015
 *      Author: yonsun
 */

#अगर_अघोषित LINK_ENCODER_H_
#घोषणा LINK_ENCODER_H_

#समावेश "grph_object_defs.h"
#समावेश "signal_types.h"
#समावेश "dc_types.h"

काष्ठा dc_context;
काष्ठा encoder_set_dp_phy_pattern_param;
काष्ठा link_mst_stream_allocation_table;
काष्ठा dc_link_settings;
काष्ठा link_training_settings;
काष्ठा pipe_ctx;

काष्ठा encoder_init_data अणु
	क्रमागत channel_id channel;
	काष्ठा graphics_object_id connector;
	क्रमागत hpd_source_id hpd_source;
	/* TODO: in DAL2, here was poपूर्णांकer to EventManagerInterface */
	काष्ठा graphics_object_id encoder;
	काष्ठा dc_context *ctx;
	क्रमागत transmitter transmitter;
पूर्ण;

काष्ठा encoder_feature_support अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t IS_HBR2_CAPABLE:1;
			uपूर्णांक32_t IS_HBR3_CAPABLE:1;
			uपूर्णांक32_t IS_TPS3_CAPABLE:1;
			uपूर्णांक32_t IS_TPS4_CAPABLE:1;
			uपूर्णांक32_t HDMI_6GB_EN:1;
			uपूर्णांक32_t DP_IS_USB_C:1;
		पूर्ण bits;
		uपूर्णांक32_t raw;
	पूर्ण flags;

	क्रमागत dc_color_depth max_hdmi_deep_color;
	अचिन्हित पूर्णांक max_hdmi_pixel_घड़ी;
	bool hdmi_ycbcr420_supported;
	bool dp_ycbcr420_supported;
	bool fec_supported;
पूर्ण;

जोड़ dpcd_psr_configuration अणु
	काष्ठा अणु
		अचिन्हित अक्षर ENABLE                    : 1;
		अचिन्हित अक्षर TRANSMITTER_ACTIVE_IN_PSR : 1;
		अचिन्हित अक्षर CRC_VERIFICATION          : 1;
		अचिन्हित अक्षर FRAME_CAPTURE_INDICATION  : 1;
		/* For eDP 1.4, PSR v2*/
		अचिन्हित अक्षर LINE_CAPTURE_INDICATION   : 1;
		/* For eDP 1.4, PSR v2*/
		अचिन्हित अक्षर IRQ_HPD_WITH_CRC_ERROR    : 1;
		अचिन्हित अक्षर RESERVED                  : 2;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

जोड़ psr_error_status अणु
	काष्ठा अणु
		अचिन्हित अक्षर LINK_CRC_ERROR        :1;
		अचिन्हित अक्षर RFB_STORAGE_ERROR     :1;
		अचिन्हित अक्षर VSC_SDP_ERROR         :1;
		अचिन्हित अक्षर RESERVED              :5;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

जोड़ psr_sink_psr_status अणु
	काष्ठा अणु
	अचिन्हित अक्षर SINK_SELF_REFRESH_STATUS  :3;
	अचिन्हित अक्षर RESERVED                  :5;
	पूर्ण bits;
	अचिन्हित अक्षर raw;
पूर्ण;

काष्ठा link_encoder अणु
	स्थिर काष्ठा link_encoder_funcs *funcs;
	पूर्णांक32_t aux_channel_offset;
	काष्ठा dc_context *ctx;
	काष्ठा graphics_object_id id;
	काष्ठा graphics_object_id connector;
	uपूर्णांक32_t output_संकेतs;
	क्रमागत engine_id preferred_engine;
	काष्ठा encoder_feature_support features;
	क्रमागत transmitter transmitter;
	क्रमागत hpd_source_id hpd_source;
	bool usbc_combo_phy;
पूर्ण;

काष्ठा link_enc_state अणु

		uपूर्णांक32_t dphy_fec_en;
		uपूर्णांक32_t dphy_fec_पढ़ोy_shaकरोw;
		uपूर्णांक32_t dphy_fec_active_status;
		uपूर्णांक32_t dp_link_training_complete;

पूर्ण;

काष्ठा link_encoder_funcs अणु
	व्योम (*पढ़ो_state)(
			काष्ठा link_encoder *enc, काष्ठा link_enc_state *s);
	bool (*validate_output_with_stream)(
		काष्ठा link_encoder *enc, स्थिर काष्ठा dc_stream_state *stream);
	व्योम (*hw_init)(काष्ठा link_encoder *enc);
	व्योम (*setup)(काष्ठा link_encoder *enc,
		क्रमागत संकेत_type संकेत);
	व्योम (*enable_पंचांगds_output)(काष्ठा link_encoder *enc,
		क्रमागत घड़ी_source_id घड़ी_source,
		क्रमागत dc_color_depth color_depth,
		क्रमागत संकेत_type संकेत,
		uपूर्णांक32_t pixel_घड़ी);
	व्योम (*enable_dp_output)(काष्ठा link_encoder *enc,
		स्थिर काष्ठा dc_link_settings *link_settings,
		क्रमागत घड़ी_source_id घड़ी_source);
	व्योम (*enable_dp_mst_output)(काष्ठा link_encoder *enc,
		स्थिर काष्ठा dc_link_settings *link_settings,
		क्रमागत घड़ी_source_id घड़ी_source);
	व्योम (*enable_lvds_output)(काष्ठा link_encoder *enc,
		क्रमागत घड़ी_source_id घड़ी_source,
		uपूर्णांक32_t pixel_घड़ी);
	व्योम (*disable_output)(काष्ठा link_encoder *link_enc,
		क्रमागत संकेत_type संकेत);
	व्योम (*dp_set_lane_settings)(काष्ठा link_encoder *enc,
		स्थिर काष्ठा link_training_settings *link_settings);
	व्योम (*dp_set_phy_pattern)(काष्ठा link_encoder *enc,
		स्थिर काष्ठा encoder_set_dp_phy_pattern_param *para);
	व्योम (*update_mst_stream_allocation_table)(
		काष्ठा link_encoder *enc,
		स्थिर काष्ठा link_mst_stream_allocation_table *table);
	व्योम (*psr_program_dp_dphy_fast_training)(काष्ठा link_encoder *enc,
			bool निकास_link_training_required);
	व्योम (*psr_program_secondary_packet)(काष्ठा link_encoder *enc,
				अचिन्हित पूर्णांक sdp_transmit_line_num_deadline);
	व्योम (*connect_dig_be_to_fe)(काष्ठा link_encoder *enc,
		क्रमागत engine_id engine,
		bool connect);
	व्योम (*enable_hpd)(काष्ठा link_encoder *enc);
	व्योम (*disable_hpd)(काष्ठा link_encoder *enc);
	bool (*is_dig_enabled)(काष्ठा link_encoder *enc);
	अचिन्हित पूर्णांक (*get_dig_frontend)(काष्ठा link_encoder *enc);
	व्योम (*destroy)(काष्ठा link_encoder **enc);

	व्योम (*fec_set_enable)(काष्ठा link_encoder *enc,
		bool enable);

	व्योम (*fec_set_पढ़ोy)(काष्ठा link_encoder *enc,
		bool पढ़ोy);

	bool (*fec_is_active)(काष्ठा link_encoder *enc);
	bool (*is_in_alt_mode) (काष्ठा link_encoder *enc);

	व्योम (*get_max_link_cap)(काष्ठा link_encoder *enc,
		काष्ठा dc_link_settings *link_settings);

	क्रमागत संकेत_type (*get_dig_mode)(
		काष्ठा link_encoder *enc);
पूर्ण;

/*
 * Used to track assignments of links (display endpoपूर्णांकs) to link encoders.
 *
 * Entry in link_enc_assignments table in काष्ठा resource_context.
 * Entries only marked valid once encoder asचिन्हित to a link and invalidated once unasचिन्हित.
 * Uses engine ID as identअगरier since PHY ID not relevant क्रम USB4 DPIA endpoपूर्णांक.
 */
काष्ठा link_enc_assignment अणु
	bool valid;
	काष्ठा display_endpoपूर्णांक_id ep_id;
	क्रमागत engine_id eng_id;
पूर्ण;

#पूर्ण_अगर /* LINK_ENCODER_H_ */
