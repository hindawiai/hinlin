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

#अगर_अघोषित __DAL_AUX_ENGINE_H__
#घोषणा __DAL_AUX_ENGINE_H__

#समावेश "dc_ddc_types.h"
#समावेश "include/i2caux_interface.h"

क्रमागत aux_वापस_code_type;

क्रमागत i2caux_transaction_operation अणु
	I2CAUX_TRANSACTION_READ,
	I2CAUX_TRANSACTION_WRITE
पूर्ण;

क्रमागत i2caux_transaction_address_space अणु
	I2CAUX_TRANSACTION_ADDRESS_SPACE_I2C = 1,
	I2CAUX_TRANSACTION_ADDRESS_SPACE_DPCD
पूर्ण;

काष्ठा i2caux_transaction_payload अणु
	क्रमागत i2caux_transaction_address_space address_space;
	uपूर्णांक32_t address;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;
पूर्ण;

क्रमागत i2caux_transaction_status अणु
	I2CAUX_TRANSACTION_STATUS_UNKNOWN = (-1L),
	I2CAUX_TRANSACTION_STATUS_SUCCEEDED,
	I2CAUX_TRANSACTION_STATUS_FAILED_CHANNEL_BUSY,
	I2CAUX_TRANSACTION_STATUS_FAILED_TIMEOUT,
	I2CAUX_TRANSACTION_STATUS_FAILED_PROTOCOL_ERROR,
	I2CAUX_TRANSACTION_STATUS_FAILED_NACK,
	I2CAUX_TRANSACTION_STATUS_FAILED_INCOMPLETE,
	I2CAUX_TRANSACTION_STATUS_FAILED_OPERATION,
	I2CAUX_TRANSACTION_STATUS_FAILED_INVALID_OPERATION,
	I2CAUX_TRANSACTION_STATUS_FAILED_BUFFER_OVERFLOW,
	I2CAUX_TRANSACTION_STATUS_FAILED_HPD_DISCON
पूर्ण;

काष्ठा i2caux_transaction_request अणु
	क्रमागत i2caux_transaction_operation operation;
	काष्ठा i2caux_transaction_payload payload;
	क्रमागत i2caux_transaction_status status;
पूर्ण;

क्रमागत i2caux_engine_type अणु
	I2CAUX_ENGINE_TYPE_UNKNOWN = (-1L),
	I2CAUX_ENGINE_TYPE_AUX,
	I2CAUX_ENGINE_TYPE_I2C_DDC_HW,
	I2CAUX_ENGINE_TYPE_I2C_GENERIC_HW,
	I2CAUX_ENGINE_TYPE_I2C_SW
पूर्ण;

क्रमागत i2c_शेष_speed अणु
	I2CAUX_DEFAULT_I2C_HW_SPEED = 50,
	I2CAUX_DEFAULT_I2C_SW_SPEED = 50
पूर्ण;

जोड़ aux_config;

काष्ठा aux_engine अणु
	uपूर्णांक32_t inst;
	काष्ठा ddc *ddc;
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा aux_engine_funcs *funcs;
	/* following values are expressed in milliseconds */
	uपूर्णांक32_t delay;
	uपूर्णांक32_t max_defer_ग_लिखो_retry;
	bool acquire_reset;
पूर्ण;

काष्ठा पढ़ो_command_context अणु
	uपूर्णांक8_t *buffer;
	uपूर्णांक32_t current_पढ़ो_length;
	uपूर्णांक32_t offset;
	क्रमागत i2caux_transaction_status status;

	काष्ठा aux_request_transaction_data request;
	काष्ठा aux_reply_transaction_data reply;

	uपूर्णांक8_t वापसed_byte;

	uपूर्णांक32_t समयd_out_retry_aux;
	uपूर्णांक32_t invalid_reply_retry_aux;
	uपूर्णांक32_t defer_retry_aux;
	uपूर्णांक32_t defer_retry_i2c;
	uपूर्णांक32_t invalid_reply_retry_aux_on_ack;

	bool transaction_complete;
	bool operation_succeeded;
पूर्ण;

काष्ठा ग_लिखो_command_context अणु
	bool mot;

	uपूर्णांक8_t *buffer;
	uपूर्णांक32_t current_ग_लिखो_length;
	क्रमागत i2caux_transaction_status status;

	काष्ठा aux_request_transaction_data request;
	काष्ठा aux_reply_transaction_data reply;

	uपूर्णांक8_t वापसed_byte;

	uपूर्णांक32_t समयd_out_retry_aux;
	uपूर्णांक32_t invalid_reply_retry_aux;
	uपूर्णांक32_t defer_retry_aux;
	uपूर्णांक32_t defer_retry_i2c;
	uपूर्णांक32_t max_defer_retry;
	uपूर्णांक32_t ack_m_retry;

	uपूर्णांक8_t reply_data[DEFAULT_AUX_MAX_DATA_SIZE];

	bool transaction_complete;
	bool operation_succeeded;
पूर्ण;


काष्ठा aux_engine_funcs अणु
	bool (*configure_समयout)(
		काष्ठा ddc_service *ddc,
		uपूर्णांक32_t समयout);
	व्योम (*destroy)(
		काष्ठा aux_engine **ptr);
	bool (*acquire_engine)(
		काष्ठा aux_engine *engine);
	व्योम (*configure)(
		काष्ठा aux_engine *engine,
		जोड़ aux_config cfg);
	व्योम (*submit_channel_request)(
		काष्ठा aux_engine *engine,
		काष्ठा aux_request_transaction_data *request);
	व्योम (*process_channel_reply)(
		काष्ठा aux_engine *engine,
		काष्ठा aux_reply_transaction_data *reply);
	पूर्णांक (*पढ़ो_channel_reply)(
		काष्ठा aux_engine *engine,
		uपूर्णांक32_t size,
		uपूर्णांक8_t *buffer,
		uपूर्णांक8_t *reply_result,
		uपूर्णांक32_t *sw_status);
	क्रमागत aux_वापस_code_type (*get_channel_status)(
		काष्ठा aux_engine *engine,
		uपूर्णांक8_t *वापसed_bytes);
	bool (*is_engine_available)(काष्ठा aux_engine *engine);
	क्रमागत i2caux_engine_type (*get_engine_type)(
		स्थिर काष्ठा aux_engine *engine);
	bool (*acquire)(
		काष्ठा aux_engine *engine,
		काष्ठा ddc *ddc);
	bool (*submit_request)(
		काष्ठा aux_engine *engine,
		काष्ठा i2caux_transaction_request *request,
		bool middle_of_transaction);
	व्योम (*release_engine)(
		काष्ठा aux_engine *engine);
	व्योम (*destroy_engine)(
		काष्ठा aux_engine **engine);
पूर्ण;
#पूर्ण_अगर
