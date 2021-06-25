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
#समावेश "dm_services_types.h"

#समावेश "virtual_link_encoder.h"

अटल bool भव_link_encoder_validate_output_with_stream(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_stream_state *stream) अणु वापस true; पूर्ण

अटल व्योम भव_link_encoder_hw_init(काष्ठा link_encoder *enc) अणुपूर्ण

अटल व्योम भव_link_encoder_setup(
	काष्ठा link_encoder *enc,
	क्रमागत संकेत_type संकेत) अणुपूर्ण

अटल व्योम भव_link_encoder_enable_पंचांगds_output(
	काष्ठा link_encoder *enc,
	क्रमागत घड़ी_source_id घड़ी_source,
	क्रमागत dc_color_depth color_depth,
	क्रमागत संकेत_type संकेत,
	uपूर्णांक32_t pixel_घड़ी) अणुपूर्ण

अटल व्योम भव_link_encoder_enable_dp_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source) अणुपूर्ण

अटल व्योम भव_link_encoder_enable_dp_mst_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source) अणुपूर्ण

अटल व्योम भव_link_encoder_disable_output(
	काष्ठा link_encoder *link_enc,
	क्रमागत संकेत_type संकेत) अणुपूर्ण

अटल व्योम भव_link_encoder_dp_set_lane_settings(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा link_training_settings *link_settings) अणुपूर्ण

अटल व्योम भव_link_encoder_dp_set_phy_pattern(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा encoder_set_dp_phy_pattern_param *param) अणुपूर्ण

अटल व्योम भव_link_encoder_update_mst_stream_allocation_table(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा link_mst_stream_allocation_table *table) अणुपूर्ण

अटल व्योम भव_link_encoder_connect_dig_be_to_fe(
	काष्ठा link_encoder *enc,
	क्रमागत engine_id engine,
	bool connect) अणुपूर्ण

अटल व्योम भव_link_encoder_destroy(काष्ठा link_encoder **enc)
अणु
	kमुक्त(*enc);
	*enc = शून्य;
पूर्ण

अटल व्योम भव_link_encoder_get_max_link_cap(काष्ठा link_encoder *enc,
		काष्ठा dc_link_settings *link_settings)
अणु
	/* Set Default link settings */
	काष्ठा dc_link_settings max_link_cap = अणुLANE_COUNT_FOUR, LINK_RATE_HIGH,
				LINK_SPREAD_05_DOWNSPREAD_30KHZ, false, 0पूर्ण;
	*link_settings = max_link_cap;
पूर्ण

अटल स्थिर काष्ठा link_encoder_funcs भव_lnk_enc_funcs = अणु
	.validate_output_with_stream =
		भव_link_encoder_validate_output_with_stream,
	.hw_init = भव_link_encoder_hw_init,
	.setup = भव_link_encoder_setup,
	.enable_पंचांगds_output = भव_link_encoder_enable_पंचांगds_output,
	.enable_dp_output = भव_link_encoder_enable_dp_output,
	.enable_dp_mst_output = भव_link_encoder_enable_dp_mst_output,
	.disable_output = भव_link_encoder_disable_output,
	.get_max_link_cap = भव_link_encoder_get_max_link_cap,
	.dp_set_lane_settings = भव_link_encoder_dp_set_lane_settings,
	.dp_set_phy_pattern = भव_link_encoder_dp_set_phy_pattern,
	.update_mst_stream_allocation_table =
		भव_link_encoder_update_mst_stream_allocation_table,
	.connect_dig_be_to_fe = भव_link_encoder_connect_dig_be_to_fe,
	.destroy = भव_link_encoder_destroy
पूर्ण;

bool भव_link_encoder_स्थिरruct(
	काष्ठा link_encoder *enc, स्थिर काष्ठा encoder_init_data *init_data)
अणु
	enc->funcs = &भव_lnk_enc_funcs;
	enc->ctx = init_data->ctx;
	enc->id = init_data->encoder;

	enc->hpd_source = init_data->hpd_source;
	enc->connector = init_data->connector;

	enc->transmitter = init_data->transmitter;

	enc->output_संकेतs = SIGNAL_TYPE_VIRTUAL;

	enc->preferred_engine = ENGINE_ID_VIRTUAL;

	वापस true;
पूर्ण


