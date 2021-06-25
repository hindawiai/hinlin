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

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "core_types.h"
#समावेश "dce_aux.h"
#समावेश "dce/dce_11_0_sh_mask.h"
#समावेश "dm_event_log.h"
#समावेश "dm_helpers.h"
#समावेश "dmub/inc/dmub_cmd.h"

#घोषणा CTX \
	aux110->base.ctx
#घोषणा REG(reg_name)\
	(aux110->regs->reg_name)

#घोषणा DC_LOGGER \
	engine->ctx->logger

#समावेश "reg_helper.h"

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	aux110->shअगरt->field_name, aux110->mask->field_name

#घोषणा FROM_AUX_ENGINE(ptr) \
	container_of((ptr), काष्ठा aux_engine_dce110, base)

#घोषणा FROM_ENGINE(ptr) \
	FROM_AUX_ENGINE(container_of((ptr), काष्ठा dce_aux, base))

#घोषणा FROM_AUX_ENGINE_ENGINE(ptr) \
	container_of((ptr), काष्ठा dce_aux, base)
क्रमागत अणु
	AUX_INVALID_REPLY_RETRY_COUNTER = 1,
	AUX_TIMED_OUT_RETRY_COUNTER = 2,
	AUX_DEFER_RETRY_COUNTER = 6
पूर्ण;

#घोषणा TIME_OUT_INCREMENT        1016
#घोषणा TIME_OUT_MULTIPLIER_8     8
#घोषणा TIME_OUT_MULTIPLIER_16    16
#घोषणा TIME_OUT_MULTIPLIER_32    32
#घोषणा TIME_OUT_MULTIPLIER_64    64
#घोषणा MAX_TIMEOUT_LENGTH        127
#घोषणा DEFAULT_AUX_ENGINE_MULT   0
#घोषणा DEFAULT_AUX_ENGINE_LENGTH 69

अटल व्योम release_engine(
	काष्ठा dce_aux *engine)
अणु
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);

	dal_ddc_बंद(engine->ddc);

	engine->ddc = शून्य;

	REG_UPDATE(AUX_ARB_CONTROL, AUX_SW_DONE_USING_AUX_REG, 1);
पूर्ण

#घोषणा SW_CAN_ACCESS_AUX 1
#घोषणा DMCU_CAN_ACCESS_AUX 2

अटल bool is_engine_available(
	काष्ठा dce_aux *engine)
अणु
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);

	uपूर्णांक32_t value = REG_READ(AUX_ARB_CONTROL);
	uपूर्णांक32_t field = get_reg_field_value(
			value,
			AUX_ARB_CONTROL,
			AUX_REG_RW_CNTL_STATUS);

	वापस (field != DMCU_CAN_ACCESS_AUX);
पूर्ण
अटल bool acquire_engine(
	काष्ठा dce_aux *engine)
अणु
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);

	uपूर्णांक32_t value = REG_READ(AUX_ARB_CONTROL);
	uपूर्णांक32_t field = get_reg_field_value(
			value,
			AUX_ARB_CONTROL,
			AUX_REG_RW_CNTL_STATUS);
	अगर (field == DMCU_CAN_ACCESS_AUX)
		वापस false;
	/* enable AUX beक्रमe request SW to access AUX */
	value = REG_READ(AUX_CONTROL);
	field = get_reg_field_value(value,
				AUX_CONTROL,
				AUX_EN);

	अगर (field == 0) अणु
		set_reg_field_value(
				value,
				1,
				AUX_CONTROL,
				AUX_EN);

		अगर (REG(AUX_RESET_MASK)) अणु
			/*DP_AUX block as part of the enable sequence*/
			set_reg_field_value(
				value,
				1,
				AUX_CONTROL,
				AUX_RESET);
		पूर्ण

		REG_WRITE(AUX_CONTROL, value);

		अगर (REG(AUX_RESET_MASK)) अणु
			/*poll HW to make sure reset it करोne*/

			REG_WAIT(AUX_CONTROL, AUX_RESET_DONE, 1,
					1, 11);

			set_reg_field_value(
				value,
				0,
				AUX_CONTROL,
				AUX_RESET);

			REG_WRITE(AUX_CONTROL, value);

			REG_WAIT(AUX_CONTROL, AUX_RESET_DONE, 0,
					1, 11);
		पूर्ण
	पूर्ण /*अगर (field)*/

	/* request SW to access AUX */
	REG_UPDATE(AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, 1);

	value = REG_READ(AUX_ARB_CONTROL);
	field = get_reg_field_value(
			value,
			AUX_ARB_CONTROL,
			AUX_REG_RW_CNTL_STATUS);

	वापस (field == SW_CAN_ACCESS_AUX);
पूर्ण

#घोषणा COMPOSE_AUX_SW_DATA_16_20(command, address) \
	((command) | ((0xF0000 & (address)) >> 16))

#घोषणा COMPOSE_AUX_SW_DATA_8_15(address) \
	((0xFF00 & (address)) >> 8)

#घोषणा COMPOSE_AUX_SW_DATA_0_7(address) \
	(0xFF & (address))

अटल व्योम submit_channel_request(
	काष्ठा dce_aux *engine,
	काष्ठा aux_request_transaction_data *request)
अणु
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);
	uपूर्णांक32_t value;
	uपूर्णांक32_t length;

	bool is_ग_लिखो =
		((request->type == AUX_TRANSACTION_TYPE_DP) &&
		 (request->action == I2CAUX_TRANSACTION_ACTION_DP_WRITE)) ||
		((request->type == AUX_TRANSACTION_TYPE_I2C) &&
		((request->action == I2CAUX_TRANSACTION_ACTION_I2C_WRITE) ||
		 (request->action == I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT)));
	अगर (REG(AUXN_IMPCAL)) अणु
		/* clear_aux_error */
		REG_UPDATE_SEQ_2(AUXN_IMPCAL,
				AUXN_CALOUT_ERROR_AK, 1,
				AUXN_CALOUT_ERROR_AK, 0);

		REG_UPDATE_SEQ_2(AUXP_IMPCAL,
				AUXP_CALOUT_ERROR_AK, 1,
				AUXP_CALOUT_ERROR_AK, 0);

		/* क्रमce_शेष_calibrate */
		REG_UPDATE_SEQ_2(AUXN_IMPCAL,
				AUXN_IMPCAL_ENABLE, 1,
				AUXN_IMPCAL_OVERRIDE_ENABLE, 0);

		/* bug? why AUXN update EN and OVERRIDE_EN 1 by 1 जबतक AUX P toggles OVERRIDE? */

		REG_UPDATE_SEQ_2(AUXP_IMPCAL,
				AUXP_IMPCAL_OVERRIDE_ENABLE, 1,
				AUXP_IMPCAL_OVERRIDE_ENABLE, 0);
	पूर्ण

	REG_UPDATE(AUX_INTERRUPT_CONTROL, AUX_SW_DONE_ACK, 1);

	REG_WAIT(AUX_SW_STATUS, AUX_SW_DONE, 0,
				10, aux110->polling_समयout_period/10);

	/* set the delay and the number of bytes to ग_लिखो */

	/* The length include
	 * the 4 bit header and the 20 bit address
	 * (that is 3 byte).
	 * If the requested length is non zero this means
	 * an addition byte specअगरying the length is required.
	 */

	length = request->length ? 4 : 3;
	अगर (is_ग_लिखो)
		length += request->length;

	REG_UPDATE_2(AUX_SW_CONTROL,
			AUX_SW_START_DELAY, request->delay,
			AUX_SW_WR_BYTES, length);

	/* program action and address and payload data (अगर 'is_write') */
	value = REG_UPDATE_4(AUX_SW_DATA,
			AUX_SW_INDEX, 0,
			AUX_SW_DATA_RW, 0,
			AUX_SW_AUTOINCREMENT_DISABLE, 1,
			AUX_SW_DATA, COMPOSE_AUX_SW_DATA_16_20(request->action, request->address));

	value = REG_SET_2(AUX_SW_DATA, value,
			AUX_SW_AUTOINCREMENT_DISABLE, 0,
			AUX_SW_DATA, COMPOSE_AUX_SW_DATA_8_15(request->address));

	value = REG_SET(AUX_SW_DATA, value,
			AUX_SW_DATA, COMPOSE_AUX_SW_DATA_0_7(request->address));

	अगर (request->length) अणु
		value = REG_SET(AUX_SW_DATA, value,
				AUX_SW_DATA, request->length - 1);
	पूर्ण

	अगर (is_ग_लिखो) अणु
		/* Load the HW buffer with the Data to be sent.
		 * This is relevant क्रम ग_लिखो operation.
		 * For पढ़ो, the data recived data will be
		 * processed in process_channel_reply().
		 */
		uपूर्णांक32_t i = 0;

		जबतक (i < request->length) अणु
			value = REG_SET(AUX_SW_DATA, value,
					AUX_SW_DATA, request->data[i]);

			++i;
		पूर्ण
	पूर्ण

	REG_UPDATE(AUX_SW_CONTROL, AUX_SW_GO, 1);
	EVENT_LOG_AUX_REQ(engine->ddc->pin_data->en, EVENT_LOG_AUX_ORIGIN_NATIVE,
					request->action, request->address, request->length, request->data);
पूर्ण

अटल पूर्णांक पढ़ो_channel_reply(काष्ठा dce_aux *engine, uपूर्णांक32_t size,
			      uपूर्णांक8_t *buffer, uपूर्णांक8_t *reply_result,
			      uपूर्णांक32_t *sw_status)
अणु
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);
	uपूर्णांक32_t bytes_replied;
	uपूर्णांक32_t reply_result_32;

	*sw_status = REG_GET(AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT,
			     &bytes_replied);

	/* In हाल HPD is LOW, निकास AUX transaction */
	अगर ((*sw_status & AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK))
		वापस -1;

	/* Need at least the status byte */
	अगर (!bytes_replied)
		वापस -1;

	REG_UPDATE_SEQ_3(AUX_SW_DATA,
			  AUX_SW_INDEX, 0,
			  AUX_SW_AUTOINCREMENT_DISABLE, 1,
			  AUX_SW_DATA_RW, 1);

	REG_GET(AUX_SW_DATA, AUX_SW_DATA, &reply_result_32);
	reply_result_32 = reply_result_32 >> 4;
	अगर (reply_result != शून्य)
		*reply_result = (uपूर्णांक8_t)reply_result_32;

	अगर (reply_result_32 == 0) अणु /* ACK */
		uपूर्णांक32_t i = 0;

		/* First byte was alपढ़ोy used to get the command status */
		--bytes_replied;

		/* Do not overflow buffer */
		अगर (bytes_replied > size)
			वापस -1;

		जबतक (i < bytes_replied) अणु
			uपूर्णांक32_t aux_sw_data_val;

			REG_GET(AUX_SW_DATA, AUX_SW_DATA, &aux_sw_data_val);
			buffer[i] = aux_sw_data_val;
			++i;
		पूर्ण

		वापस i;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत aux_वापस_code_type get_channel_status(
	काष्ठा dce_aux *engine,
	uपूर्णांक8_t *वापसed_bytes)
अणु
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);

	uपूर्णांक32_t value;

	अगर (वापसed_bytes == शून्य) अणु
		/*caller pass शून्य poपूर्णांकer*/
		ASSERT_CRITICAL(false);
		वापस AUX_RET_ERROR_UNKNOWN;
	पूर्ण
	*वापसed_bytes = 0;

	/* poll to make sure that SW_DONE is निश्चितed */
	REG_WAIT(AUX_SW_STATUS, AUX_SW_DONE, 1,
				10, aux110->polling_समयout_period/10);

	value = REG_READ(AUX_SW_STATUS);
	/* in हाल HPD is LOW, निकास AUX transaction */
	अगर ((value & AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK))
		वापस AUX_RET_ERROR_HPD_DISCON;

	/* Note that the following bits are set in 'status.bits'
	 * during CTS 4.2.1.2 (FW 3.3.1):
	 * AUX_SW_RX_MIN_COUNT_VIOL, AUX_SW_RX_INVALID_STOP,
	 * AUX_SW_RX_RECV_NO_DET, AUX_SW_RX_RECV_INVALID_H.
	 *
	 * AUX_SW_RX_MIN_COUNT_VIOL is an पूर्णांकernal,
	 * HW debugging bit and should be ignored.
	 */
	अगर (value & AUX_SW_STATUS__AUX_SW_DONE_MASK) अणु
		अगर ((value & AUX_SW_STATUS__AUX_SW_RX_TIMEOUT_STATE_MASK) ||
			(value & AUX_SW_STATUS__AUX_SW_RX_TIMEOUT_MASK))
			वापस AUX_RET_ERROR_TIMEOUT;

		अन्यथा अगर ((value & AUX_SW_STATUS__AUX_SW_RX_INVALID_STOP_MASK) ||
			(value & AUX_SW_STATUS__AUX_SW_RX_RECV_NO_DET_MASK) ||
			(value &
				AUX_SW_STATUS__AUX_SW_RX_RECV_INVALID_H_MASK) ||
			(value & AUX_SW_STATUS__AUX_SW_RX_RECV_INVALID_L_MASK))
			वापस AUX_RET_ERROR_INVALID_REPLY;

		*वापसed_bytes = get_reg_field_value(value,
				AUX_SW_STATUS,
				AUX_SW_REPLY_BYTE_COUNT);

		अगर (*वापसed_bytes == 0)
			वापस
			AUX_RET_ERROR_INVALID_REPLY;
		अन्यथा अणु
			*वापसed_bytes -= 1;
			वापस AUX_RET_SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*समय_elapsed >= aux_engine->समयout_period
		 *  AUX_SW_STATUS__AUX_SW_HPD_DISCON = at this poपूर्णांक
		 */
		ASSERT_CRITICAL(false);
		वापस AUX_RET_ERROR_TIMEOUT;
	पूर्ण
पूर्ण

अटल bool acquire(
	काष्ठा dce_aux *engine,
	काष्ठा ddc *ddc)
अणु
	क्रमागत gpio_result result;

	अगर ((engine == शून्य) || !is_engine_available(engine))
		वापस false;

	result = dal_ddc_खोलो(ddc, GPIO_MODE_HARDWARE,
		GPIO_DDC_CONFIG_TYPE_MODE_AUX);

	अगर (result != GPIO_RESULT_OK)
		वापस false;

	अगर (!acquire_engine(engine)) अणु
		dal_ddc_बंद(ddc);
		वापस false;
	पूर्ण

	engine->ddc = ddc;

	वापस true;
पूर्ण

व्योम dce110_engine_destroy(काष्ठा dce_aux **engine)
अणु

	काष्ठा aux_engine_dce110 *engine110 = FROM_AUX_ENGINE(*engine);

	kमुक्त(engine110);
	*engine = शून्य;

पूर्ण

अटल uपूर्णांक32_t dce_aux_configure_समयout(काष्ठा ddc_service *ddc,
		uपूर्णांक32_t समयout_in_us)
अणु
	uपूर्णांक32_t multiplier = 0;
	uपूर्णांक32_t length = 0;
	uपूर्णांक32_t prev_length = 0;
	uपूर्णांक32_t prev_mult = 0;
	uपूर्णांक32_t prev_समयout_val = 0;
	काष्ठा ddc *ddc_pin = ddc->ddc_pin;
	काष्ठा dce_aux *aux_engine = ddc->ctx->dc->res_pool->engines[ddc_pin->pin_data->en];
	काष्ठा aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(aux_engine);

	/* 1-Update polling समयout period */
	aux110->polling_समयout_period = समयout_in_us * SW_AUX_TIMEOUT_PERIOD_MULTIPLIER;

	/* 2-Update aux समयout period length and multiplier */
	अगर (समयout_in_us == 0) अणु
		multiplier = DEFAULT_AUX_ENGINE_MULT;
		length = DEFAULT_AUX_ENGINE_LENGTH;
	पूर्ण अन्यथा अगर (समयout_in_us <= TIME_OUT_INCREMENT) अणु
		multiplier = 0;
		length = समयout_in_us/TIME_OUT_MULTIPLIER_8;
		अगर (समयout_in_us % TIME_OUT_MULTIPLIER_8 != 0)
			length++;
	पूर्ण अन्यथा अगर (समयout_in_us <= 2 * TIME_OUT_INCREMENT) अणु
		multiplier = 1;
		length = समयout_in_us/TIME_OUT_MULTIPLIER_16;
		अगर (समयout_in_us % TIME_OUT_MULTIPLIER_16 != 0)
			length++;
	पूर्ण अन्यथा अगर (समयout_in_us <= 4 * TIME_OUT_INCREMENT) अणु
		multiplier = 2;
		length = समयout_in_us/TIME_OUT_MULTIPLIER_32;
		अगर (समयout_in_us % TIME_OUT_MULTIPLIER_32 != 0)
			length++;
	पूर्ण अन्यथा अगर (समयout_in_us > 4 * TIME_OUT_INCREMENT) अणु
		multiplier = 3;
		length = समयout_in_us/TIME_OUT_MULTIPLIER_64;
		अगर (समयout_in_us % TIME_OUT_MULTIPLIER_64 != 0)
			length++;
	पूर्ण

	length = (length < MAX_TIMEOUT_LENGTH) ? length : MAX_TIMEOUT_LENGTH;

	REG_GET_2(AUX_DPHY_RX_CONTROL1, AUX_RX_TIMEOUT_LEN, &prev_length, AUX_RX_TIMEOUT_LEN_MUL, &prev_mult);

	चयन (prev_mult) अणु
	हाल 0:
		prev_समयout_val = prev_length * TIME_OUT_MULTIPLIER_8;
		अवरोध;
	हाल 1:
		prev_समयout_val = prev_length * TIME_OUT_MULTIPLIER_16;
		अवरोध;
	हाल 2:
		prev_समयout_val = prev_length * TIME_OUT_MULTIPLIER_32;
		अवरोध;
	हाल 3:
		prev_समयout_val = prev_length * TIME_OUT_MULTIPLIER_64;
		अवरोध;
	शेष:
		prev_समयout_val = DEFAULT_AUX_ENGINE_LENGTH * TIME_OUT_MULTIPLIER_8;
		अवरोध;
	पूर्ण

	REG_UPDATE_SEQ_2(AUX_DPHY_RX_CONTROL1, AUX_RX_TIMEOUT_LEN, length, AUX_RX_TIMEOUT_LEN_MUL, multiplier);

	वापस prev_समयout_val;
पूर्ण

अटल काष्ठा dce_aux_funcs aux_functions = अणु
	.configure_समयout = शून्य,
	.destroy = शून्य,
पूर्ण;

काष्ठा dce_aux *dce110_aux_engine_स्थिरruct(काष्ठा aux_engine_dce110 *aux_engine110,
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t inst,
		uपूर्णांक32_t समयout_period,
		स्थिर काष्ठा dce110_aux_रेजिस्टरs *regs,
		स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask *mask,
		स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt *shअगरt,
		bool is_ext_aux_समयout_configurable)
अणु
	aux_engine110->base.ddc = शून्य;
	aux_engine110->base.ctx = ctx;
	aux_engine110->base.delay = 0;
	aux_engine110->base.max_defer_ग_लिखो_retry = 0;
	aux_engine110->base.inst = inst;
	aux_engine110->polling_समयout_period = समयout_period;
	aux_engine110->regs = regs;

	aux_engine110->mask = mask;
	aux_engine110->shअगरt = shअगरt;
	aux_engine110->base.funcs = &aux_functions;
	अगर (is_ext_aux_समयout_configurable)
		aux_engine110->base.funcs->configure_समयout = &dce_aux_configure_समयout;

	वापस &aux_engine110->base;
पूर्ण

अटल क्रमागत i2caux_transaction_action i2caux_action_from_payload(काष्ठा aux_payload *payload)
अणु
	अगर (payload->i2c_over_aux) अणु
		अगर (payload->ग_लिखो) अणु
			अगर (payload->mot)
				वापस I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT;
			वापस I2CAUX_TRANSACTION_ACTION_I2C_WRITE;
		पूर्ण
		अगर (payload->mot)
			वापस I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT;
		वापस I2CAUX_TRANSACTION_ACTION_I2C_READ;
	पूर्ण
	अगर (payload->ग_लिखो)
		वापस I2CAUX_TRANSACTION_ACTION_DP_WRITE;
	वापस I2CAUX_TRANSACTION_ACTION_DP_READ;
पूर्ण

पूर्णांक dce_aux_transfer_raw(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload,
		क्रमागत aux_वापस_code_type *operation_result)
अणु
	काष्ठा ddc *ddc_pin = ddc->ddc_pin;
	काष्ठा dce_aux *aux_engine;
	काष्ठा aux_request_transaction_data aux_req;
	काष्ठा aux_reply_transaction_data aux_rep;
	uपूर्णांक8_t वापसed_bytes = 0;
	पूर्णांक res = -1;
	uपूर्णांक32_t status;

	स_रखो(&aux_req, 0, माप(aux_req));
	स_रखो(&aux_rep, 0, माप(aux_rep));

	aux_engine = ddc->ctx->dc->res_pool->engines[ddc_pin->pin_data->en];
	अगर (!acquire(aux_engine, ddc_pin)) अणु
		*operation_result = AUX_RET_ERROR_ENGINE_ACQUIRE;
		वापस -1;
	पूर्ण

	अगर (payload->i2c_over_aux)
		aux_req.type = AUX_TRANSACTION_TYPE_I2C;
	अन्यथा
		aux_req.type = AUX_TRANSACTION_TYPE_DP;

	aux_req.action = i2caux_action_from_payload(payload);

	aux_req.address = payload->address;
	aux_req.delay = 0;
	aux_req.length = payload->length;
	aux_req.data = payload->data;

	submit_channel_request(aux_engine, &aux_req);
	*operation_result = get_channel_status(aux_engine, &वापसed_bytes);

	अगर (*operation_result == AUX_RET_SUCCESS) अणु
		पूर्णांक __maybe_unused bytes_replied = 0;

		bytes_replied = पढ़ो_channel_reply(aux_engine, payload->length,
					 payload->data, payload->reply,
					 &status);
		EVENT_LOG_AUX_REP(aux_engine->ddc->pin_data->en,
					EVENT_LOG_AUX_ORIGIN_NATIVE, *payload->reply,
					bytes_replied, payload->data);
		res = वापसed_bytes;
	पूर्ण अन्यथा अणु
		res = -1;
	पूर्ण

	release_engine(aux_engine);
	वापस res;
पूर्ण

#घोषणा AUX_MAX_RETRIES 7
#घोषणा AUX_MAX_DEFER_RETRIES 7
#घोषणा AUX_MAX_I2C_DEFER_RETRIES 7
#घोषणा AUX_MAX_INVALID_REPLY_RETRIES 2
#घोषणा AUX_MAX_TIMEOUT_RETRIES 3

bool dce_aux_transfer_with_retries(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *payload)
अणु
	पूर्णांक i, ret = 0;
	uपूर्णांक8_t reply;
	bool payload_reply = true;
	क्रमागत aux_वापस_code_type operation_result;
	bool retry_on_defer = false;

	पूर्णांक aux_ack_retries = 0,
		aux_defer_retries = 0,
		aux_i2c_defer_retries = 0,
		aux_समयout_retries = 0,
		aux_invalid_reply_retries = 0;

	अगर (!payload->reply) अणु
		payload_reply = false;
		payload->reply = &reply;
	पूर्ण

	क्रम (i = 0; i < AUX_MAX_RETRIES; i++) अणु
		ret = dce_aux_transfer_raw(ddc, payload, &operation_result);

		चयन (operation_result) अणु
		हाल AUX_RET_SUCCESS:
			aux_समयout_retries = 0;
			aux_invalid_reply_retries = 0;

			चयन (*payload->reply) अणु
			हाल AUX_TRANSACTION_REPLY_AUX_ACK:
				अगर (!payload->ग_लिखो && payload->length != ret) अणु
					अगर (++aux_ack_retries >= AUX_MAX_RETRIES)
						जाओ fail;
					अन्यथा
						udelay(300);
				पूर्ण अन्यथा
					वापस true;
			अवरोध;

			हाल AUX_TRANSACTION_REPLY_AUX_DEFER:
			हाल AUX_TRANSACTION_REPLY_I2C_OVER_AUX_DEFER:
				retry_on_defer = true;
				fallthrough;
			हाल AUX_TRANSACTION_REPLY_I2C_OVER_AUX_NACK:
				अगर (++aux_defer_retries >= AUX_MAX_DEFER_RETRIES) अणु
					जाओ fail;
				पूर्ण अन्यथा अणु
					अगर ((*payload->reply == AUX_TRANSACTION_REPLY_AUX_DEFER) ||
						(*payload->reply == AUX_TRANSACTION_REPLY_I2C_OVER_AUX_DEFER)) अणु
						अगर (payload->defer_delay > 1)
							msleep(payload->defer_delay);
						अन्यथा अगर (payload->defer_delay <= 1)
							udelay(payload->defer_delay * 1000);
					पूर्ण
				पूर्ण
				अवरोध;

			हाल AUX_TRANSACTION_REPLY_I2C_DEFER:
				aux_defer_retries = 0;
				अगर (++aux_i2c_defer_retries >= AUX_MAX_I2C_DEFER_RETRIES)
					जाओ fail;
				अवरोध;

			हाल AUX_TRANSACTION_REPLY_AUX_NACK:
			हाल AUX_TRANSACTION_REPLY_HPD_DISCON:
			शेष:
				जाओ fail;
			पूर्ण
			अवरोध;

		हाल AUX_RET_ERROR_INVALID_REPLY:
			अगर (++aux_invalid_reply_retries >= AUX_MAX_INVALID_REPLY_RETRIES)
				जाओ fail;
			अन्यथा
				udelay(400);
			अवरोध;

		हाल AUX_RET_ERROR_TIMEOUT:
			// Check whether a DEFER had occurred beक्रमe the समयout.
			// If so, treat समयout as a DEFER.
			अगर (retry_on_defer) अणु
				अगर (++aux_defer_retries >= AUX_MAX_DEFER_RETRIES)
					जाओ fail;
				अन्यथा अगर (payload->defer_delay > 0)
					msleep(payload->defer_delay);
			पूर्ण अन्यथा अणु
				अगर (++aux_समयout_retries >= AUX_MAX_TIMEOUT_RETRIES)
					जाओ fail;
				अन्यथा अणु
					/*
					 * DP 1.4, 2.8.2:  AUX Transaction Response/Reply Timeouts
					 * According to the DP spec there should be 3 retries total
					 * with a 400us रुको inbetween each. Hardware alपढ़ोy रुकोs
					 * क्रम 550us thereक्रमe no रुको is required here.
					 */
				पूर्ण
			पूर्ण
			अवरोध;

		हाल AUX_RET_ERROR_HPD_DISCON:
		हाल AUX_RET_ERROR_ENGINE_ACQUIRE:
		हाल AUX_RET_ERROR_UNKNOWN:
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण

fail:
	अगर (!payload_reply)
		payload->reply = शून्य;
	वापस false;
पूर्ण
