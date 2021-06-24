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
#समावेश "dm_helpers.h"
#समावेश "gpio_service_interface.h"
#समावेश "include/ddc_service_types.h"
#समावेश "include/grph_object_id.h"
#समावेश "include/dpcd_defs.h"
#समावेश "include/logger_interface.h"
#समावेश "include/vector.h"
#समावेश "core_types.h"
#समावेश "dc_link_ddc.h"
#समावेश "dce/dce_aux.h"
#समावेश "dmub/inc/dmub_cmd.h"

#घोषणा DC_LOGGER_INIT(logger)

अटल स्थिर uपूर्णांक8_t DP_VGA_DONGLE_BRANCH_DEV_NAME[] = "DpVga";
/* DP to Dual link DVI converter */
अटल स्थिर uपूर्णांक8_t DP_DVI_CONVERTER_ID_4[] = "m2DVIa";
अटल स्थिर uपूर्णांक8_t DP_DVI_CONVERTER_ID_5[] = "3393N2";

#घोषणा AUX_POWER_UP_WA_DELAY 500
#घोषणा I2C_OVER_AUX_DEFER_WA_DELAY 70
#घोषणा DPVGA_DONGLE_AUX_DEFER_WA_DELAY 40
#घोषणा I2C_OVER_AUX_DEFER_WA_DELAY_1MS 1

/* CV smart करोngle slave address क्रम retrieving supported HDTV modes*/
#घोषणा CV_SMART_DONGLE_ADDRESS 0x20
/* DVI-HDMI करोngle slave address क्रम retrieving करोngle signature*/
#घोषणा DVI_HDMI_DONGLE_ADDRESS 0x68
काष्ठा dvi_hdmi_करोngle_signature_data अणु
	पूर्णांक8_t venकरोr[3];/* "AMD" */
	uपूर्णांक8_t version[2];
	uपूर्णांक8_t size;
	पूर्णांक8_t id[11];/* "6140063500G"*/
पूर्ण;
/* DP-HDMI करोngle slave address क्रम retrieving करोngle signature*/
#घोषणा DP_HDMI_DONGLE_ADDRESS 0x40
अटल स्थिर uपूर्णांक8_t dp_hdmi_करोngle_signature_str[] = "DP-HDMI ADAPTOR";
#घोषणा DP_HDMI_DONGLE_SIGNATURE_EOT 0x04

काष्ठा dp_hdmi_करोngle_signature_data अणु
	पूर्णांक8_t id[15];/* "DP-HDMI ADAPTOR"*/
	uपूर्णांक8_t eot;/* end of transmition '\x4' */
पूर्ण;

/* SCDC Address defines (HDMI 2.0)*/
#घोषणा HDMI_SCDC_WRITE_UPDATE_0_ARRAY 3
#घोषणा HDMI_SCDC_ADDRESS  0x54
#घोषणा HDMI_SCDC_SINK_VERSION 0x01
#घोषणा HDMI_SCDC_SOURCE_VERSION 0x02
#घोषणा HDMI_SCDC_UPDATE_0 0x10
#घोषणा HDMI_SCDC_TMDS_CONFIG 0x20
#घोषणा HDMI_SCDC_SCRAMBLER_STATUS 0x21
#घोषणा HDMI_SCDC_CONFIG_0 0x30
#घोषणा HDMI_SCDC_STATUS_FLAGS 0x40
#घोषणा HDMI_SCDC_ERR_DETECT 0x50
#घोषणा HDMI_SCDC_TEST_CONFIG 0xC0

जोड़ hdmi_scdc_update_पढ़ो_data अणु
	uपूर्णांक8_t byte[2];
	काष्ठा अणु
		uपूर्णांक8_t STATUS_UPDATE:1;
		uपूर्णांक8_t CED_UPDATE:1;
		uपूर्णांक8_t RR_TEST:1;
		uपूर्णांक8_t RESERVED:5;
		uपूर्णांक8_t RESERVED2:8;
	पूर्ण fields;
पूर्ण;

जोड़ hdmi_scdc_status_flags_data अणु
	uपूर्णांक8_t byte[2];
	काष्ठा अणु
		uपूर्णांक8_t CLOCK_DETECTED:1;
		uपूर्णांक8_t CH0_LOCKED:1;
		uपूर्णांक8_t CH1_LOCKED:1;
		uपूर्णांक8_t CH2_LOCKED:1;
		uपूर्णांक8_t RESERVED:4;
		uपूर्णांक8_t RESERVED2:8;
		uपूर्णांक8_t RESERVED3:8;

	पूर्ण fields;
पूर्ण;

जोड़ hdmi_scdc_ced_data अणु
	uपूर्णांक8_t byte[7];
	काष्ठा अणु
		uपूर्णांक8_t CH0_8LOW:8;
		uपूर्णांक8_t CH0_7HIGH:7;
		uपूर्णांक8_t CH0_VALID:1;
		uपूर्णांक8_t CH1_8LOW:8;
		uपूर्णांक8_t CH1_7HIGH:7;
		uपूर्णांक8_t CH1_VALID:1;
		uपूर्णांक8_t CH2_8LOW:8;
		uपूर्णांक8_t CH2_7HIGH:7;
		uपूर्णांक8_t CH2_VALID:1;
		uपूर्णांक8_t CHECKSUM:8;
		uपूर्णांक8_t RESERVED:8;
		uपूर्णांक8_t RESERVED2:8;
		uपूर्णांक8_t RESERVED3:8;
		uपूर्णांक8_t RESERVED4:4;
	पूर्ण fields;
पूर्ण;

काष्ठा i2c_payloads अणु
	काष्ठा vector payloads;
पूर्ण;

काष्ठा aux_payloads अणु
	काष्ठा vector payloads;
पूर्ण;

अटल bool dal_ddc_i2c_payloads_create(
		काष्ठा dc_context *ctx,
		काष्ठा i2c_payloads *payloads,
		uपूर्णांक32_t count)
अणु
	अगर (dal_vector_स्थिरruct(
		&payloads->payloads, ctx, count, माप(काष्ठा i2c_payload)))
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा i2c_payload *dal_ddc_i2c_payloads_get(काष्ठा i2c_payloads *p)
अणु
	वापस (काष्ठा i2c_payload *)p->payloads.container;
पूर्ण

अटल uपूर्णांक32_t dal_ddc_i2c_payloads_get_count(काष्ठा i2c_payloads *p)
अणु
	वापस p->payloads.count;
पूर्ण

#घोषणा DDC_MIN(a, b) (((a) < (b)) ? (a) : (b))

व्योम dal_ddc_i2c_payloads_add(
	काष्ठा i2c_payloads *payloads,
	uपूर्णांक32_t address,
	uपूर्णांक32_t len,
	uपूर्णांक8_t *data,
	bool ग_लिखो)
अणु
	uपूर्णांक32_t payload_size = EDID_SEGMENT_SIZE;
	uपूर्णांक32_t pos;

	क्रम (pos = 0; pos < len; pos += payload_size) अणु
		काष्ठा i2c_payload payload = अणु
			.ग_लिखो = ग_लिखो,
			.address = address,
			.length = DDC_MIN(payload_size, len - pos),
			.data = data + pos पूर्ण;
		dal_vector_append(&payloads->payloads, &payload);
	पूर्ण

पूर्ण

अटल व्योम ddc_service_स्थिरruct(
	काष्ठा ddc_service *ddc_service,
	काष्ठा ddc_service_init_data *init_data)
अणु
	क्रमागत connector_id connector_id =
		dal_graphics_object_id_get_connector_id(init_data->id);

	काष्ठा gpio_service *gpio_service = init_data->ctx->gpio_service;
	काष्ठा graphics_object_i2c_info i2c_info;
	काष्ठा gpio_ddc_hw_info hw_info;
	काष्ठा dc_bios *dcb = init_data->ctx->dc_bios;

	ddc_service->link = init_data->link;
	ddc_service->ctx = init_data->ctx;

	अगर (BP_RESULT_OK != dcb->funcs->get_i2c_info(dcb, init_data->id, &i2c_info)) अणु
		ddc_service->ddc_pin = शून्य;
	पूर्ण अन्यथा अणु
		DC_LOGGER_INIT(ddc_service->ctx->logger);
		DC_LOG_DC("BIOS object table - i2c_line: %d", i2c_info.i2c_line);
		DC_LOG_DC("BIOS object table - i2c_engine_id: %d", i2c_info.i2c_engine_id);

		hw_info.ddc_channel = i2c_info.i2c_line;
		अगर (ddc_service->link != शून्य)
			hw_info.hw_supported = i2c_info.i2c_hw_assist;
		अन्यथा
			hw_info.hw_supported = false;

		ddc_service->ddc_pin = dal_gpio_create_ddc(
			gpio_service,
			i2c_info.gpio_info.clk_a_रेजिस्टर_index,
			1 << i2c_info.gpio_info.clk_a_shअगरt,
			&hw_info);
	पूर्ण

	ddc_service->flags.EDID_QUERY_DONE_ONCE = false;
	ddc_service->flags.FORCE_READ_REPEATED_START = false;
	ddc_service->flags.EDID_STRESS_READ = false;

	ddc_service->flags.IS_INTERNAL_DISPLAY =
		connector_id == CONNECTOR_ID_EDP ||
		connector_id == CONNECTOR_ID_LVDS;

	ddc_service->wa.raw = 0;
पूर्ण

काष्ठा ddc_service *dal_ddc_service_create(
	काष्ठा ddc_service_init_data *init_data)
अणु
	काष्ठा ddc_service *ddc_service;

	ddc_service = kzalloc(माप(काष्ठा ddc_service), GFP_KERNEL);

	अगर (!ddc_service)
		वापस शून्य;

	ddc_service_स्थिरruct(ddc_service, init_data);
	वापस ddc_service;
पूर्ण

अटल व्योम ddc_service_deकाष्ठा(काष्ठा ddc_service *ddc)
अणु
	अगर (ddc->ddc_pin)
		dal_gpio_destroy_ddc(&ddc->ddc_pin);
पूर्ण

व्योम dal_ddc_service_destroy(काष्ठा ddc_service **ddc)
अणु
	अगर (!ddc || !*ddc) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण
	ddc_service_deकाष्ठा(*ddc);
	kमुक्त(*ddc);
	*ddc = शून्य;
पूर्ण

क्रमागत ddc_service_type dal_ddc_service_get_type(काष्ठा ddc_service *ddc)
अणु
	वापस DDC_SERVICE_TYPE_CONNECTOR;
पूर्ण

व्योम dal_ddc_service_set_transaction_type(
	काष्ठा ddc_service *ddc,
	क्रमागत ddc_transaction_type type)
अणु
	ddc->transaction_type = type;
पूर्ण

bool dal_ddc_service_is_in_aux_transaction_mode(काष्ठा ddc_service *ddc)
अणु
	चयन (ddc->transaction_type) अणु
	हाल DDC_TRANSACTION_TYPE_I2C_OVER_AUX:
	हाल DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER:
	हाल DDC_TRANSACTION_TYPE_I2C_OVER_AUX_RETRY_DEFER:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

व्योम ddc_service_set_करोngle_type(काष्ठा ddc_service *ddc,
		क्रमागत display_करोngle_type करोngle_type)
अणु
	ddc->करोngle_type = करोngle_type;
पूर्ण

अटल uपूर्णांक32_t defer_delay_converter_wa(
	काष्ठा ddc_service *ddc,
	uपूर्णांक32_t defer_delay)
अणु
	काष्ठा dc_link *link = ddc->link;

	अगर (link->dpcd_caps.करोngle_type == DISPLAY_DONGLE_DP_VGA_CONVERTER &&
		link->dpcd_caps.branch_dev_id == DP_BRANCH_DEVICE_ID_0080E1 &&
		!स_भेद(link->dpcd_caps.branch_dev_name,
		    DP_VGA_DONGLE_BRANCH_DEV_NAME,
			माप(link->dpcd_caps.branch_dev_name)))

		वापस defer_delay > DPVGA_DONGLE_AUX_DEFER_WA_DELAY ?
			defer_delay : DPVGA_DONGLE_AUX_DEFER_WA_DELAY;

	अगर (link->dpcd_caps.branch_dev_id == DP_BRANCH_DEVICE_ID_0080E1 &&
	    !स_भेद(link->dpcd_caps.branch_dev_name,
		    DP_DVI_CONVERTER_ID_4,
		    माप(link->dpcd_caps.branch_dev_name)))
		वापस defer_delay > I2C_OVER_AUX_DEFER_WA_DELAY ?
			defer_delay : I2C_OVER_AUX_DEFER_WA_DELAY;
	अगर (link->dpcd_caps.branch_dev_id == DP_BRANCH_DEVICE_ID_006037 &&
	    !स_भेद(link->dpcd_caps.branch_dev_name,
		    DP_DVI_CONVERTER_ID_5,
		    माप(link->dpcd_caps.branch_dev_name)))
		वापस defer_delay > I2C_OVER_AUX_DEFER_WA_DELAY_1MS ?
			I2C_OVER_AUX_DEFER_WA_DELAY_1MS : defer_delay;

	वापस defer_delay;
पूर्ण

#घोषणा DP_TRANSLATOR_DELAY 5

uपूर्णांक32_t get_defer_delay(काष्ठा ddc_service *ddc)
अणु
	uपूर्णांक32_t defer_delay = 0;

	चयन (ddc->transaction_type) अणु
	हाल DDC_TRANSACTION_TYPE_I2C_OVER_AUX:
		अगर ((DISPLAY_DONGLE_DP_VGA_CONVERTER == ddc->करोngle_type) ||
			(DISPLAY_DONGLE_DP_DVI_CONVERTER == ddc->करोngle_type) ||
			(DISPLAY_DONGLE_DP_HDMI_CONVERTER ==
				ddc->करोngle_type)) अणु

			defer_delay = DP_TRANSLATOR_DELAY;

			defer_delay =
				defer_delay_converter_wa(ddc, defer_delay);

		पूर्ण अन्यथा /*sink has a delay dअगरferent from an Active Converter*/
			defer_delay = 0;
		अवरोध;
	हाल DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER:
		defer_delay = DP_TRANSLATOR_DELAY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस defer_delay;
पूर्ण

अटल bool i2c_पढ़ो(
	काष्ठा ddc_service *ddc,
	uपूर्णांक32_t address,
	uपूर्णांक8_t *buffer,
	uपूर्णांक32_t len)
अणु
	uपूर्णांक8_t offs_data = 0;
	काष्ठा i2c_payload payloads[2] = अणु
		अणु
		.ग_लिखो = true,
		.address = address,
		.length = 1,
		.data = &offs_data पूर्ण,
		अणु
		.ग_लिखो = false,
		.address = address,
		.length = len,
		.data = buffer पूर्ण पूर्ण;

	काष्ठा i2c_command command = अणु
		.payloads = payloads,
		.number_of_payloads = 2,
		.engine = DDC_I2C_COMMAND_ENGINE,
		.speed = ddc->ctx->dc->caps.i2c_speed_in_khz पूर्ण;

	वापस dm_helpers_submit_i2c(
			ddc->ctx,
			ddc->link,
			&command);
पूर्ण

व्योम dal_ddc_service_i2c_query_dp_dual_mode_adaptor(
	काष्ठा ddc_service *ddc,
	काष्ठा display_sink_capability *sink_cap)
अणु
	uपूर्णांक8_t i;
	bool is_valid_hdmi_signature;
	क्रमागत display_करोngle_type *करोngle = &sink_cap->करोngle_type;
	uपूर्णांक8_t type2_करोngle_buf[DP_ADAPTOR_TYPE2_SIZE];
	bool is_type2_करोngle = false;
	पूर्णांक retry_count = 2;
	काष्ठा dp_hdmi_करोngle_signature_data *करोngle_signature;

	/* Assume we have no valid DP passive करोngle connected */
	*करोngle = DISPLAY_DONGLE_NONE;
	sink_cap->max_hdmi_pixel_घड़ी = DP_ADAPTOR_HDMI_SAFE_MAX_TMDS_CLK;

	/* Read DP-HDMI करोngle I2c (no response पूर्णांकerpreted as DP-DVI करोngle)*/
	अगर (!i2c_पढ़ो(
		ddc,
		DP_HDMI_DONGLE_ADDRESS,
		type2_करोngle_buf,
		माप(type2_करोngle_buf))) अणु
		/* Passive HDMI करोngles can someबार fail here without retrying*/
		जबतक (retry_count > 0) अणु
			अगर (i2c_पढ़ो(ddc,
				DP_HDMI_DONGLE_ADDRESS,
				type2_करोngle_buf,
				माप(type2_करोngle_buf)))
				अवरोध;
			retry_count--;
		पूर्ण
		अगर (retry_count == 0) अणु
			*करोngle = DISPLAY_DONGLE_DP_DVI_DONGLE;
			sink_cap->max_hdmi_pixel_घड़ी = DP_ADAPTOR_DVI_MAX_TMDS_CLK;

			CONN_DATA_DETECT(ddc->link, type2_करोngle_buf, माप(type2_करोngle_buf),
					"DP-DVI passive dongle %dMhz: ",
					DP_ADAPTOR_DVI_MAX_TMDS_CLK / 1000);
			वापस;
		पूर्ण
	पूर्ण

	/* Check अगर Type 2 करोngle.*/
	अगर (type2_करोngle_buf[DP_ADAPTOR_TYPE2_REG_ID] == DP_ADAPTOR_TYPE2_ID)
		is_type2_करोngle = true;

	करोngle_signature =
		(काष्ठा dp_hdmi_करोngle_signature_data *)type2_करोngle_buf;

	is_valid_hdmi_signature = true;

	/* Check EOT */
	अगर (करोngle_signature->eot != DP_HDMI_DONGLE_SIGNATURE_EOT) अणु
		is_valid_hdmi_signature = false;
	पूर्ण

	/* Check signature */
	क्रम (i = 0; i < माप(करोngle_signature->id); ++i) अणु
		/* If its not the right signature,
		 * skip mismatch in subversion byte.*/
		अगर (करोngle_signature->id[i] !=
			dp_hdmi_करोngle_signature_str[i] && i != 3) अणु

			अगर (is_type2_करोngle) अणु
				is_valid_hdmi_signature = false;
				अवरोध;
			पूर्ण

		पूर्ण
	पूर्ण

	अगर (is_type2_करोngle) अणु
		uपूर्णांक32_t max_पंचांगds_clk =
			type2_करोngle_buf[DP_ADAPTOR_TYPE2_REG_MAX_TMDS_CLK];

		max_पंचांगds_clk = max_पंचांगds_clk * 2 + max_पंचांगds_clk / 2;

		अगर (0 == max_पंचांगds_clk ||
				max_पंचांगds_clk < DP_ADAPTOR_TYPE2_MIN_TMDS_CLK ||
				max_पंचांगds_clk > DP_ADAPTOR_TYPE2_MAX_TMDS_CLK) अणु
			*करोngle = DISPLAY_DONGLE_DP_DVI_DONGLE;

			CONN_DATA_DETECT(ddc->link, type2_करोngle_buf,
					माप(type2_करोngle_buf),
					"DP-DVI passive dongle %dMhz: ",
					DP_ADAPTOR_DVI_MAX_TMDS_CLK / 1000);
		पूर्ण अन्यथा अणु
			अगर (is_valid_hdmi_signature == true) अणु
				*करोngle = DISPLAY_DONGLE_DP_HDMI_DONGLE;

				CONN_DATA_DETECT(ddc->link, type2_करोngle_buf,
						माप(type2_करोngle_buf),
						"Type 2 DP-HDMI passive dongle %dMhz: ",
						max_पंचांगds_clk);
			पूर्ण अन्यथा अणु
				*करोngle = DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE;

				CONN_DATA_DETECT(ddc->link, type2_करोngle_buf,
						माप(type2_करोngle_buf),
						"Type 2 DP-HDMI passive dongle (no signature) %dMhz: ",
						max_पंचांगds_clk);

			पूर्ण

			/* Multiply by 1000 to convert to kHz. */
			sink_cap->max_hdmi_pixel_घड़ी =
				max_पंचांगds_clk * 1000;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (is_valid_hdmi_signature == true) अणु
			*करोngle = DISPLAY_DONGLE_DP_HDMI_DONGLE;

			CONN_DATA_DETECT(ddc->link, type2_करोngle_buf,
					माप(type2_करोngle_buf),
					"Type 1 DP-HDMI passive dongle %dMhz: ",
					sink_cap->max_hdmi_pixel_घड़ी / 1000);
		पूर्ण अन्यथा अणु
			*करोngle = DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE;

			CONN_DATA_DETECT(ddc->link, type2_करोngle_buf,
					माप(type2_करोngle_buf),
					"Type 1 DP-HDMI passive dongle (no signature) %dMhz: ",
					sink_cap->max_hdmi_pixel_घड़ी / 1000);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

क्रमागत अणु
	DP_SINK_CAP_SIZE =
		DP_EDP_CONFIGURATION_CAP - DP_DPCD_REV + 1
पूर्ण;

bool dal_ddc_service_query_ddc_data(
	काष्ठा ddc_service *ddc,
	uपूर्णांक32_t address,
	uपूर्णांक8_t *ग_लिखो_buf,
	uपूर्णांक32_t ग_लिखो_size,
	uपूर्णांक8_t *पढ़ो_buf,
	uपूर्णांक32_t पढ़ो_size)
अणु
	bool success = true;
	uपूर्णांक32_t payload_size =
		dal_ddc_service_is_in_aux_transaction_mode(ddc) ?
			DEFAULT_AUX_MAX_DATA_SIZE : EDID_SEGMENT_SIZE;

	uपूर्णांक32_t ग_लिखो_payloads =
		(ग_लिखो_size + payload_size - 1) / payload_size;

	uपूर्णांक32_t पढ़ो_payloads =
		(पढ़ो_size + payload_size - 1) / payload_size;

	uपूर्णांक32_t payloads_num = ग_लिखो_payloads + पढ़ो_payloads;


	अगर (ग_लिखो_size > EDID_SEGMENT_SIZE || पढ़ो_size > EDID_SEGMENT_SIZE)
		वापस false;

	अगर (!payloads_num)
		वापस false;

	/*TODO: len of payload data क्रम i2c and aux is uपूर्णांक8!!!!,
	 *  but we want to पढ़ो 256 over i2c!!!!*/
	अगर (dal_ddc_service_is_in_aux_transaction_mode(ddc)) अणु
		काष्ठा aux_payload payload;

		payload.i2c_over_aux = true;
		payload.address = address;
		payload.reply = शून्य;
		payload.defer_delay = get_defer_delay(ddc);

		अगर (ग_लिखो_size != 0) अणु
			payload.ग_लिखो = true;
			/* should not set mot (middle of transaction) to 0
			 * अगर there are pending पढ़ो payloads
			 */
			payload.mot = !(पढ़ो_size == 0);
			payload.length = ग_लिखो_size;
			payload.data = ग_लिखो_buf;

			success = dal_ddc_submit_aux_command(ddc, &payload);
		पूर्ण

		अगर (पढ़ो_size != 0 && success) अणु
			payload.ग_लिखो = false;
			/* should set mot (middle of transaction) to 0
			 * since it is the last payload to send
			 */
			payload.mot = false;
			payload.length = पढ़ो_size;
			payload.data = पढ़ो_buf;

			success = dal_ddc_submit_aux_command(ddc, &payload);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा i2c_command command = अणु0पूर्ण;
		काष्ठा i2c_payloads payloads;

		अगर (!dal_ddc_i2c_payloads_create(ddc->ctx, &payloads, payloads_num))
			वापस false;

		command.payloads = dal_ddc_i2c_payloads_get(&payloads);
		command.number_of_payloads = 0;
		command.engine = DDC_I2C_COMMAND_ENGINE;
		command.speed = ddc->ctx->dc->caps.i2c_speed_in_khz;

		dal_ddc_i2c_payloads_add(
			&payloads, address, ग_लिखो_size, ग_लिखो_buf, true);

		dal_ddc_i2c_payloads_add(
			&payloads, address, पढ़ो_size, पढ़ो_buf, false);

		command.number_of_payloads =
			dal_ddc_i2c_payloads_get_count(&payloads);

		success = dm_helpers_submit_i2c(
				ddc->ctx,
				ddc->link,
				&command);

		dal_vector_deकाष्ठा(&payloads.payloads);
	पूर्ण

	वापस success;
पूर्ण

bool dal_ddc_submit_aux_command(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload)
अणु
	uपूर्णांक32_t retrieved = 0;
	bool ret = false;

	अगर (!ddc)
		वापस false;

	अगर (!payload)
		वापस false;

	करो अणु
		काष्ठा aux_payload current_payload;
		bool is_end_of_payload = (retrieved + DEFAULT_AUX_MAX_DATA_SIZE) >=
			payload->length;

		current_payload.address = payload->address;
		current_payload.data = &payload->data[retrieved];
		current_payload.defer_delay = payload->defer_delay;
		current_payload.i2c_over_aux = payload->i2c_over_aux;
		current_payload.length = is_end_of_payload ?
			payload->length - retrieved : DEFAULT_AUX_MAX_DATA_SIZE;
		/* set mot (middle of transaction) to false
		 * अगर it is the last payload
		 */
		current_payload.mot = is_end_of_payload ? payload->mot:true;
		current_payload.reply = payload->reply;
		current_payload.ग_लिखो = payload->ग_लिखो;

		ret = dc_link_aux_transfer_with_retries(ddc, &current_payload);

		retrieved += current_payload.length;
	पूर्ण जबतक (retrieved < payload->length && ret == true);

	वापस ret;
पूर्ण

/* dc_link_aux_transfer_raw() - Attempt to transfer
 * the given aux payload.  This function करोes not perक्रमm
 * retries or handle error states.  The reply is वापसed
 * in the payload->reply and the result through
 * *operation_result.  Returns the number of bytes transferred,
 * or -1 on a failure.
 */
पूर्णांक dc_link_aux_transfer_raw(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload,
		क्रमागत aux_वापस_code_type *operation_result)
अणु
	वापस dce_aux_transfer_raw(ddc, payload, operation_result);
पूर्ण

/* dc_link_aux_transfer_with_retries() - Attempt to submit an
 * aux payload, retrying on समयouts, defers, and busy states
 * as outlined in the DP spec.  Returns true अगर the request
 * was successful.
 *
 * Unless you want to implement your own retry semantics, this
 * is probably the one you want.
 */
bool dc_link_aux_transfer_with_retries(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload)
अणु
	वापस dce_aux_transfer_with_retries(ddc, payload);
पूर्ण


bool dc_link_aux_try_to_configure_समयout(काष्ठा ddc_service *ddc,
		uपूर्णांक32_t समयout)
अणु
	bool result = false;
	काष्ठा ddc *ddc_pin = ddc->ddc_pin;

	अगर (ddc->ctx->dc->res_pool->engines[ddc_pin->pin_data->en]->funcs->configure_समयout) अणु
		ddc->ctx->dc->res_pool->engines[ddc_pin->pin_data->en]->funcs->configure_समयout(ddc, समयout);
		result = true;
	पूर्ण
	वापस result;
पूर्ण

/*test only function*/
व्योम dal_ddc_service_set_ddc_pin(
	काष्ठा ddc_service *ddc_service,
	काष्ठा ddc *ddc)
अणु
	ddc_service->ddc_pin = ddc;
पूर्ण

काष्ठा ddc *dal_ddc_service_get_ddc_pin(काष्ठा ddc_service *ddc_service)
अणु
	वापस ddc_service->ddc_pin;
पूर्ण

व्योम dal_ddc_service_ग_लिखो_scdc_data(काष्ठा ddc_service *ddc_service,
		uपूर्णांक32_t pix_clk,
		bool lte_340_scramble)
अणु
	bool over_340_mhz = pix_clk > 340000 ? 1 : 0;
	uपूर्णांक8_t slave_address = HDMI_SCDC_ADDRESS;
	uपूर्णांक8_t offset = HDMI_SCDC_SINK_VERSION;
	uपूर्णांक8_t sink_version = 0;
	uपूर्णांक8_t ग_लिखो_buffer[2] = अणु0पूर्ण;
	/*Lower than 340 Scramble bit from SCDC caps*/

	अगर (ddc_service->link->local_sink &&
		ddc_service->link->local_sink->edid_caps.panel_patch.skip_scdc_overग_लिखो)
		वापस;

	dal_ddc_service_query_ddc_data(ddc_service, slave_address, &offset,
			माप(offset), &sink_version, माप(sink_version));
	अगर (sink_version == 1) अणु
		/*Source Version = 1*/
		ग_लिखो_buffer[0] = HDMI_SCDC_SOURCE_VERSION;
		ग_लिखो_buffer[1] = 1;
		dal_ddc_service_query_ddc_data(ddc_service, slave_address,
				ग_लिखो_buffer, माप(ग_लिखो_buffer), शून्य, 0);
		/*Read Request from SCDC caps*/
	पूर्ण
	ग_लिखो_buffer[0] = HDMI_SCDC_TMDS_CONFIG;

	अगर (over_340_mhz) अणु
		ग_लिखो_buffer[1] = 3;
	पूर्ण अन्यथा अगर (lte_340_scramble) अणु
		ग_लिखो_buffer[1] = 1;
	पूर्ण अन्यथा अणु
		ग_लिखो_buffer[1] = 0;
	पूर्ण
	dal_ddc_service_query_ddc_data(ddc_service, slave_address, ग_लिखो_buffer,
			माप(ग_लिखो_buffer), शून्य, 0);
पूर्ण

व्योम dal_ddc_service_पढ़ो_scdc_data(काष्ठा ddc_service *ddc_service)
अणु
	uपूर्णांक8_t slave_address = HDMI_SCDC_ADDRESS;
	uपूर्णांक8_t offset = HDMI_SCDC_TMDS_CONFIG;
	uपूर्णांक8_t पंचांगds_config = 0;

	अगर (ddc_service->link->local_sink &&
		ddc_service->link->local_sink->edid_caps.panel_patch.skip_scdc_overग_लिखो)
		वापस;

	dal_ddc_service_query_ddc_data(ddc_service, slave_address, &offset,
			माप(offset), &पंचांगds_config, माप(पंचांगds_config));
	अगर (पंचांगds_config & 0x1) अणु
		जोड़ hdmi_scdc_status_flags_data status_data = अणु अणु0पूर्ण पूर्ण;
		uपूर्णांक8_t scramble_status = 0;

		offset = HDMI_SCDC_SCRAMBLER_STATUS;
		dal_ddc_service_query_ddc_data(ddc_service, slave_address,
				&offset, माप(offset), &scramble_status,
				माप(scramble_status));
		offset = HDMI_SCDC_STATUS_FLAGS;
		dal_ddc_service_query_ddc_data(ddc_service, slave_address,
				&offset, माप(offset), status_data.byte,
				माप(status_data.byte));
	पूर्ण
पूर्ण

