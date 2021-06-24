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

#अगर_अघोषित __DAL_DDC_SERVICE_H__
#घोषणा __DAL_DDC_SERVICE_H__

#समावेश "include/ddc_service_types.h"
#समावेश "include/i2caux_interface.h"

#घोषणा EDID_SEGMENT_SIZE 256

/* Address range from 0x00 to 0x1F.*/
#घोषणा DP_ADAPTOR_TYPE2_SIZE 0x20
#घोषणा DP_ADAPTOR_TYPE2_REG_ID 0x10
#घोषणा DP_ADAPTOR_TYPE2_REG_MAX_TMDS_CLK 0x1D
/* Identअगरies adaptor as Dual-mode adaptor */
#घोषणा DP_ADAPTOR_TYPE2_ID 0xA0
/* MHz*/
#घोषणा DP_ADAPTOR_TYPE2_MAX_TMDS_CLK 600
/* MHz*/
#घोषणा DP_ADAPTOR_TYPE2_MIN_TMDS_CLK 25
/* kHZ*/
#घोषणा DP_ADAPTOR_DVI_MAX_TMDS_CLK 165000
/* kHZ*/
#घोषणा DP_ADAPTOR_HDMI_SAFE_MAX_TMDS_CLK 165000

#घोषणा DDC_I2C_COMMAND_ENGINE I2C_COMMAND_ENGINE_SW

काष्ठा ddc_service;
काष्ठा graphics_object_id;
क्रमागत ddc_result;
काष्ठा av_sync_data;
काष्ठा dp_receiver_id_info;

काष्ठा i2c_payloads;
काष्ठा aux_payloads;
क्रमागत aux_वापस_code_type;

व्योम dal_ddc_i2c_payloads_add(
		काष्ठा i2c_payloads *payloads,
		uपूर्णांक32_t address,
		uपूर्णांक32_t len,
		uपूर्णांक8_t *data,
		bool ग_लिखो);

काष्ठा ddc_service_init_data अणु
	काष्ठा graphics_object_id id;
	काष्ठा dc_context *ctx;
	काष्ठा dc_link *link;
पूर्ण;

काष्ठा ddc_service *dal_ddc_service_create(
		काष्ठा ddc_service_init_data *ddc_init_data);

व्योम dal_ddc_service_destroy(काष्ठा ddc_service **ddc);

क्रमागत ddc_service_type dal_ddc_service_get_type(काष्ठा ddc_service *ddc);

व्योम dal_ddc_service_set_transaction_type(
		काष्ठा ddc_service *ddc,
		क्रमागत ddc_transaction_type type);

bool dal_ddc_service_is_in_aux_transaction_mode(काष्ठा ddc_service *ddc);

व्योम dal_ddc_service_i2c_query_dp_dual_mode_adaptor(
		काष्ठा ddc_service *ddc,
		काष्ठा display_sink_capability *sink_cap);

bool dal_ddc_service_query_ddc_data(
		काष्ठा ddc_service *ddc,
		uपूर्णांक32_t address,
		uपूर्णांक8_t *ग_लिखो_buf,
		uपूर्णांक32_t ग_लिखो_size,
		uपूर्णांक8_t *पढ़ो_buf,
		uपूर्णांक32_t पढ़ो_size);

bool dal_ddc_submit_aux_command(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload);

पूर्णांक dc_link_aux_transfer_raw(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload,
		क्रमागत aux_वापस_code_type *operation_result);

bool dc_link_aux_transfer_with_retries(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload);

bool dc_link_aux_try_to_configure_समयout(काष्ठा ddc_service *ddc,
		uपूर्णांक32_t समयout);

व्योम dal_ddc_service_ग_लिखो_scdc_data(
		काष्ठा ddc_service *ddc_service,
		uपूर्णांक32_t pix_clk,
		bool lte_340_scramble);

व्योम dal_ddc_service_पढ़ो_scdc_data(
		काष्ठा ddc_service *ddc_service);

व्योम ddc_service_set_करोngle_type(काष्ठा ddc_service *ddc,
		क्रमागत display_करोngle_type करोngle_type);

व्योम dal_ddc_service_set_ddc_pin(
		काष्ठा ddc_service *ddc_service,
		काष्ठा ddc *ddc);

काष्ठा ddc *dal_ddc_service_get_ddc_pin(काष्ठा ddc_service *ddc_service);

uपूर्णांक32_t get_defer_delay(काष्ठा ddc_service *ddc);

#पूर्ण_अगर /* __DAL_DDC_SERVICE_H__ */

