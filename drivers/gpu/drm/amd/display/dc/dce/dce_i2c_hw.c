<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश "resource.h"
#समावेश "dce_i2c.h"
#समावेश "dce_i2c_hw.h"
#समावेश "reg_helper.h"
#समावेश "include/gpio_service_interface.h"

#घोषणा CTX \
	dce_i2c_hw->ctx
#घोषणा REG(reg)\
	dce_i2c_hw->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dce_i2c_hw->shअगरts->field_name, dce_i2c_hw->masks->field_name

अटल व्योम execute_transaction(
	काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	REG_UPDATE_N(SETUP, 5,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DRIVE_EN), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CLK_DRIVE_EN), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DRIVE_SEL), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTRA_TRANSACTION_DELAY), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTRA_BYTE_DELAY), 0);


	REG_UPDATE_5(DC_I2C_CONTROL,
		     DC_I2C_SOFT_RESET, 0,
		     DC_I2C_SW_STATUS_RESET, 0,
		     DC_I2C_SEND_RESET, 0,
		     DC_I2C_GO, 0,
		     DC_I2C_TRANSACTION_COUNT, dce_i2c_hw->transaction_count - 1);

	/* start I2C transfer */
	REG_UPDATE(DC_I2C_CONTROL, DC_I2C_GO, 1);

	/* all transactions were executed and HW buffer became empty
	 * (even though it actually happens when status becomes DONE)
	 */
	dce_i2c_hw->transaction_count = 0;
	dce_i2c_hw->buffer_used_bytes = 0;
पूर्ण

अटल क्रमागत i2c_channel_operation_result get_channel_status(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	uपूर्णांक8_t *वापसed_bytes)
अणु
	uपूर्णांक32_t i2c_sw_status = 0;
	uपूर्णांक32_t value =
		REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
	अगर (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW)
		वापस I2C_CHANNEL_OPERATION_ENGINE_BUSY;
	अन्यथा अगर (value & dce_i2c_hw->masks->DC_I2C_SW_STOPPED_ON_NACK)
		वापस I2C_CHANNEL_OPERATION_NO_RESPONSE;
	अन्यथा अगर (value & dce_i2c_hw->masks->DC_I2C_SW_TIMEOUT)
		वापस I2C_CHANNEL_OPERATION_TIMEOUT;
	अन्यथा अगर (value & dce_i2c_hw->masks->DC_I2C_SW_ABORTED)
		वापस I2C_CHANNEL_OPERATION_FAILED;
	अन्यथा अगर (value & dce_i2c_hw->masks->DC_I2C_SW_DONE)
		वापस I2C_CHANNEL_OPERATION_SUCCEEDED;

	/*
	 * this is the हाल when HW used क्रम communication, I2C_SW_STATUS
	 * could be zero
	 */
	वापस I2C_CHANNEL_OPERATION_SUCCEEDED;
पूर्ण

अटल uपूर्णांक32_t get_hw_buffer_available_size(
	स्थिर काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	वापस dce_i2c_hw->buffer_size -
			dce_i2c_hw->buffer_used_bytes;
पूर्ण

अटल व्योम process_channel_reply(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा i2c_payload *reply)
अणु
	uपूर्णांक32_t length = reply->length;
	uपूर्णांक8_t *buffer = reply->data;

	REG_SET_3(DC_I2C_DATA, 0,
		 DC_I2C_INDEX, dce_i2c_hw->buffer_used_ग_लिखो,
		 DC_I2C_DATA_RW, 1,
		 DC_I2C_INDEX_WRITE, 1);

	जबतक (length) अणु
		/* after पढ़ोing the status,
		 * अगर the I2C operation executed successfully
		 * (i.e. DC_I2C_STATUS_DONE = 1) then the I2C controller
		 * should पढ़ो data bytes from I2C circular data buffer
		 */

		uपूर्णांक32_t i2c_data;

		REG_GET(DC_I2C_DATA, DC_I2C_DATA, &i2c_data);
		*buffer++ = i2c_data;

		--length;
	पूर्ण
पूर्ण

अटल bool is_engine_available(काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	अचिन्हित पूर्णांक arbitrate;
	अचिन्हित पूर्णांक i2c_hw_status;

	REG_GET(HW_STATUS, DC_I2C_DDC1_HW_STATUS, &i2c_hw_status);
	अगर (i2c_hw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_HW)
		वापस false;

	REG_GET(DC_I2C_ARBITRATION, DC_I2C_REG_RW_CNTL_STATUS, &arbitrate);
	अगर (arbitrate == DC_I2C_REG_RW_CNTL_STATUS_DMCU_ONLY)
		वापस false;

	वापस true;
पूर्ण

अटल bool is_hw_busy(काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	uपूर्णांक32_t i2c_sw_status = 0;

	REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
	अगर (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_IDLE)
		वापस false;

	अगर (is_engine_available(dce_i2c_hw))
		वापस false;

	वापस true;
पूर्ण

अटल bool process_transaction(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा i2c_request_transaction_data *request)
अणु
	uपूर्णांक32_t length = request->length;
	uपूर्णांक8_t *buffer = request->data;

	bool last_transaction = false;
	uपूर्णांक32_t value = 0;

	अगर (is_hw_busy(dce_i2c_hw)) अणु
		request->status = I2C_CHANNEL_OPERATION_ENGINE_BUSY;
		वापस false;
	पूर्ण

	last_transaction = ((dce_i2c_hw->transaction_count == 3) ||
			(request->action == DCE_I2C_TRANSACTION_ACTION_I2C_WRITE) ||
			(request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ));


	चयन (dce_i2c_hw->transaction_count) अणु
	हाल 0:
		REG_UPDATE_5(DC_I2C_TRANSACTION0,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		अवरोध;
	हाल 1:
		REG_UPDATE_5(DC_I2C_TRANSACTION1,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		अवरोध;
	हाल 2:
		REG_UPDATE_5(DC_I2C_TRANSACTION2,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		अवरोध;
	हाल 3:
		REG_UPDATE_5(DC_I2C_TRANSACTION3,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_START0, 1,
				 DC_I2C_RW0, 0 != (request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ),
				 DC_I2C_COUNT0, length,
				 DC_I2C_STOP0, last_transaction ? 1 : 0);
		अवरोध;
	शेष:
		/* TODO Warning ? */
		अवरोध;
	पूर्ण

	/* Write the I2C address and I2C data
	 * पूर्णांकo the hardware circular buffer, one byte per entry.
	 * As an example, the 7-bit I2C slave address क्रम CRT monitor
	 * क्रम पढ़ोing DDC/EDID inक्रमmation is 0b1010001.
	 * For an I2C send operation, the LSB must be programmed to 0;
	 * क्रम I2C receive operation, the LSB must be programmed to 1.
	 */
	अगर (dce_i2c_hw->transaction_count == 0) अणु
		value = REG_SET_4(DC_I2C_DATA, 0,
				  DC_I2C_DATA_RW, false,
				  DC_I2C_DATA, request->address,
				  DC_I2C_INDEX, 0,
				  DC_I2C_INDEX_WRITE, 1);
		dce_i2c_hw->buffer_used_ग_लिखो = 0;
	पूर्ण अन्यथा
		value = REG_SET_2(DC_I2C_DATA, 0,
			  DC_I2C_DATA_RW, false,
			  DC_I2C_DATA, request->address);

	dce_i2c_hw->buffer_used_ग_लिखो++;

	अगर (!(request->action & DCE_I2C_TRANSACTION_ACTION_I2C_READ)) अणु
		जबतक (length) अणु
			REG_SET_2(DC_I2C_DATA, value,
				  DC_I2C_INDEX_WRITE, 0,
				  DC_I2C_DATA, *buffer++);
			dce_i2c_hw->buffer_used_ग_लिखो++;
			--length;
		पूर्ण
	पूर्ण

	++dce_i2c_hw->transaction_count;
	dce_i2c_hw->buffer_used_bytes += length + 1;

	वापस last_transaction;
पूर्ण

अटल अंतरभूत व्योम reset_hw_engine(काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	REG_UPDATE_2(DC_I2C_CONTROL,
		     DC_I2C_SW_STATUS_RESET, 1,
		     DC_I2C_SW_STATUS_RESET, 1);
पूर्ण

अटल व्योम set_speed(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	uपूर्णांक32_t speed)
अणु
	uपूर्णांक32_t xtal_ref_भाग = 0;
	uपूर्णांक32_t prescale = 0;

	अगर (speed == 0)
		वापस;

	REG_GET(MICROSECOND_TIME_BASE_DIV, XTAL_REF_DIV, &xtal_ref_भाग);

	अगर (xtal_ref_भाग == 0)
		xtal_ref_भाग = 2;

	prescale = ((dce_i2c_hw->reference_frequency * 2) / xtal_ref_भाग) / speed;

	अगर (dce_i2c_hw->masks->DC_I2C_DDC1_START_STOP_TIMING_CNTL)
		REG_UPDATE_N(SPEED, 3,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE), prescale,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD), 2,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_START_STOP_TIMING_CNTL), speed > 50 ? 2:1);
	अन्यथा
		REG_UPDATE_N(SPEED, 2,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE), prescale,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD), 2);
पूर्ण

अटल bool setup_engine(
	काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	uपूर्णांक32_t i2c_setup_limit = I2C_SETUP_TIME_LIMIT_DCE;
	uपूर्णांक32_t  reset_length = 0;

        अगर (dce_i2c_hw->ctx->dc->debug.enable_mem_low_घातer.bits.i2c) अणु
	     अगर (dce_i2c_hw->regs->DIO_MEM_PWR_CTRL) अणु
		     REG_UPDATE(DIO_MEM_PWR_CTRL, I2C_LIGHT_SLEEP_FORCE, 0);
		     REG_WAIT(DIO_MEM_PWR_STATUS, I2C_MEM_PWR_STATE, 0, 0, 5);
		     पूर्ण
	     पूर्ण

	/* we have checked I2c not used by DMCU, set SW use I2C REQ to 1 to indicate SW using it*/
	REG_UPDATE(DC_I2C_ARBITRATION, DC_I2C_SW_USE_I2C_REG_REQ, 1);

	/* we have checked I2c not used by DMCU, set SW use I2C REQ to 1 to indicate SW using it*/
	REG_UPDATE(DC_I2C_ARBITRATION, DC_I2C_SW_USE_I2C_REG_REQ, 1);

	/*set SW requested I2c speed to शेष, अगर API calls in it will be override later*/
	set_speed(dce_i2c_hw, dce_i2c_hw->ctx->dc->caps.i2c_speed_in_khz);

	अगर (dce_i2c_hw->setup_limit != 0)
		i2c_setup_limit = dce_i2c_hw->setup_limit;

	/* Program pin select */
	REG_UPDATE_6(DC_I2C_CONTROL,
		     DC_I2C_GO, 0,
		     DC_I2C_SOFT_RESET, 0,
		     DC_I2C_SEND_RESET, 0,
		     DC_I2C_SW_STATUS_RESET, 1,
		     DC_I2C_TRANSACTION_COUNT, 0,
		     DC_I2C_DDC_SELECT, dce_i2c_hw->engine_id);

	/* Program समय limit */
	अगर (dce_i2c_hw->send_reset_length == 0) अणु
		/*pre-dcn*/
		REG_UPDATE_N(SETUP, 2,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_LIMIT), i2c_setup_limit,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABLE), 1);
	पूर्ण अन्यथा अणु
		reset_length = dce_i2c_hw->send_reset_length;
		REG_UPDATE_N(SETUP, 3,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_LIMIT), i2c_setup_limit,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_SEND_RESET_LENGTH), reset_length,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABLE), 1);
	पूर्ण
	/* Program HW priority
	 * set to High - पूर्णांकerrupt software I2C at any समय
	 * Enable restart of SW I2C that was पूर्णांकerrupted by HW
	 * disable queuing of software जबतक I2C is in use by HW
	 */
	REG_UPDATE(DC_I2C_ARBITRATION,
			DC_I2C_NO_QUEUED_SW_GO, 0);

	वापस true;
पूर्ण

अटल व्योम release_engine(
	काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	bool safe_to_reset;


	/* Reset HW engine */
	अणु
		uपूर्णांक32_t i2c_sw_status = 0;

		REG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
		/* अगर used by SW, safe to reset */
		safe_to_reset = (i2c_sw_status == 1);
	पूर्ण

	अगर (safe_to_reset)
		REG_UPDATE_2(DC_I2C_CONTROL,
			     DC_I2C_SOFT_RESET, 1,
			     DC_I2C_SW_STATUS_RESET, 1);
	अन्यथा
		REG_UPDATE(DC_I2C_CONTROL, DC_I2C_SW_STATUS_RESET, 1);
	/* HW I2c engine - घड़ी gating feature */
	अगर (!dce_i2c_hw->engine_keep_घातer_up_count)
		REG_UPDATE_N(SETUP, 1, FN(SETUP, DC_I2C_DDC1_ENABLE), 0);

	/*क्रम HW HDCP Ri polling failure w/a test*/
	set_speed(dce_i2c_hw, dce_i2c_hw->ctx->dc->caps.i2c_speed_in_khz_hdcp);
	/* Release I2C after reset, so HW or DMCU could use it */
	REG_UPDATE_2(DC_I2C_ARBITRATION, DC_I2C_SW_DONE_USING_I2C_REG, 1,
		DC_I2C_SW_USE_I2C_REG_REQ, 0);

	अगर (dce_i2c_hw->ctx->dc->debug.enable_mem_low_घातer.bits.i2c) अणु
		अगर (dce_i2c_hw->regs->DIO_MEM_PWR_CTRL)
			REG_UPDATE(DIO_MEM_PWR_CTRL, I2C_LIGHT_SLEEP_FORCE, 1);
	पूर्ण
पूर्ण

काष्ठा dce_i2c_hw *acquire_i2c_hw_engine(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc)
अणु
	uपूर्णांक32_t counter = 0;
	क्रमागत gpio_result result;
	काष्ठा dce_i2c_hw *dce_i2c_hw = शून्य;

	अगर (!ddc)
		वापस शून्य;

	अगर (ddc->hw_info.hw_supported) अणु
		क्रमागत gpio_ddc_line line = dal_ddc_get_line(ddc);

		अगर (line < pool->res_cap->num_ddc)
			dce_i2c_hw = pool->hw_i2cs[line];
	पूर्ण

	अगर (!dce_i2c_hw)
		वापस शून्य;

	अगर (pool->i2c_hw_buffer_in_use || !is_engine_available(dce_i2c_hw))
		वापस शून्य;

	करो अणु
		result = dal_ddc_खोलो(ddc, GPIO_MODE_HARDWARE,
			GPIO_DDC_CONFIG_TYPE_MODE_I2C);

		अगर (result == GPIO_RESULT_OK)
			अवरोध;

		/* i2c_engine is busy by VBios, lets रुको and retry */

		udelay(10);

		++counter;
	पूर्ण जबतक (counter < 2);

	अगर (result != GPIO_RESULT_OK)
		वापस शून्य;

	dce_i2c_hw->ddc = ddc;

	अगर (!setup_engine(dce_i2c_hw)) अणु
		release_engine(dce_i2c_hw);
		वापस शून्य;
	पूर्ण

	pool->i2c_hw_buffer_in_use = true;
	वापस dce_i2c_hw;
पूर्ण

अटल क्रमागत i2c_channel_operation_result dce_i2c_hw_engine_रुको_on_operation_result(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	uपूर्णांक32_t समयout,
	क्रमागत i2c_channel_operation_result expected_result)
अणु
	क्रमागत i2c_channel_operation_result result;
	uपूर्णांक32_t i = 0;

	अगर (!समयout)
		वापस I2C_CHANNEL_OPERATION_SUCCEEDED;

	करो अणु

		result = get_channel_status(
				dce_i2c_hw, शून्य);

		अगर (result != expected_result)
			अवरोध;

		udelay(1);

		++i;
	पूर्ण जबतक (i < समयout);
	वापस result;
पूर्ण

अटल व्योम submit_channel_request_hw(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा i2c_request_transaction_data *request)
अणु
	request->status = I2C_CHANNEL_OPERATION_SUCCEEDED;

	अगर (!process_transaction(dce_i2c_hw, request))
		वापस;

	अगर (is_hw_busy(dce_i2c_hw)) अणु
		request->status = I2C_CHANNEL_OPERATION_ENGINE_BUSY;
		वापस;
	पूर्ण
	reset_hw_engine(dce_i2c_hw);

	execute_transaction(dce_i2c_hw);


पूर्ण

अटल uपूर्णांक32_t get_transaction_समयout_hw(
	स्थिर काष्ठा dce_i2c_hw *dce_i2c_hw,
	uपूर्णांक32_t length,
	uपूर्णांक32_t speed)
अणु
	uपूर्णांक32_t period_समयout;
	uपूर्णांक32_t num_of_घड़ी_stretches;

	अगर (!speed)
		वापस 0;

	period_समयout = (1000 * TRANSACTION_TIMEOUT_IN_I2C_CLOCKS) / speed;

	num_of_घड़ी_stretches = 1 + (length << 3) + 1;
	num_of_घड़ी_stretches +=
		(dce_i2c_hw->buffer_used_bytes << 3) +
		(dce_i2c_hw->transaction_count << 1);

	वापस period_समयout * num_of_घड़ी_stretches;
पूर्ण

अटल bool dce_i2c_hw_engine_submit_payload(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा i2c_payload *payload,
	bool middle_of_transaction,
	uपूर्णांक32_t speed)
अणु

	काष्ठा i2c_request_transaction_data request;

	uपूर्णांक32_t transaction_समयout;

	क्रमागत i2c_channel_operation_result operation_result;

	bool result = false;

	/* We need following:
	 * transaction length will not exceed
	 * the number of मुक्त bytes in HW buffer (minus one क्रम address)
	 */

	अगर (payload->length >=
			get_hw_buffer_available_size(dce_i2c_hw)) अणु
		वापस false;
	पूर्ण

	अगर (!payload->ग_लिखो)
		request.action = middle_of_transaction ?
			DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT :
			DCE_I2C_TRANSACTION_ACTION_I2C_READ;
	अन्यथा
		request.action = middle_of_transaction ?
			DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT :
			DCE_I2C_TRANSACTION_ACTION_I2C_WRITE;


	request.address = (uपूर्णांक8_t) ((payload->address << 1) | !payload->ग_लिखो);
	request.length = payload->length;
	request.data = payload->data;

	/* obtain समयout value beक्रमe submitting request */

	transaction_समयout = get_transaction_समयout_hw(
		dce_i2c_hw, payload->length + 1, speed);

	submit_channel_request_hw(
		dce_i2c_hw, &request);

	अगर ((request.status == I2C_CHANNEL_OPERATION_FAILED) ||
		(request.status == I2C_CHANNEL_OPERATION_ENGINE_BUSY))
		वापस false;

	/* रुको until transaction proceed */

	operation_result = dce_i2c_hw_engine_रुको_on_operation_result(
		dce_i2c_hw,
		transaction_समयout,
		I2C_CHANNEL_OPERATION_ENGINE_BUSY);

	/* update transaction status */

	अगर (operation_result == I2C_CHANNEL_OPERATION_SUCCEEDED)
		result = true;

	अगर (result && (!payload->ग_लिखो))
		process_channel_reply(dce_i2c_hw, payload);

	वापस result;
पूर्ण

bool dce_i2c_submit_command_hw(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc,
	काष्ठा i2c_command *cmd,
	काष्ठा dce_i2c_hw *dce_i2c_hw)
अणु
	uपूर्णांक8_t index_of_payload = 0;
	bool result;

	set_speed(dce_i2c_hw, cmd->speed);

	result = true;

	जबतक (index_of_payload < cmd->number_of_payloads) अणु
		bool mot = (index_of_payload != cmd->number_of_payloads - 1);

		काष्ठा i2c_payload *payload = cmd->payloads + index_of_payload;

		अगर (!dce_i2c_hw_engine_submit_payload(
				dce_i2c_hw, payload, mot, cmd->speed)) अणु
			result = false;
			अवरोध;
		पूर्ण

		++index_of_payload;
	पूर्ण

	pool->i2c_hw_buffer_in_use = false;

	release_engine(dce_i2c_hw);
	dal_ddc_बंद(dce_i2c_hw->ddc);

	dce_i2c_hw->ddc = शून्य;

	वापस result;
पूर्ण

व्योम dce_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks)
अणु
	dce_i2c_hw->ctx = ctx;
	dce_i2c_hw->engine_id = engine_id;
	dce_i2c_hw->reference_frequency = (ctx->dc_bios->fw_info.pll_info.crystal_frequency) >> 1;
	dce_i2c_hw->regs = regs;
	dce_i2c_hw->shअगरts = shअगरts;
	dce_i2c_hw->masks = masks;
	dce_i2c_hw->buffer_used_bytes = 0;
	dce_i2c_hw->transaction_count = 0;
	dce_i2c_hw->engine_keep_घातer_up_count = 1;
	dce_i2c_hw->शेष_speed = DEFAULT_I2C_HW_SPEED;
	dce_i2c_hw->send_reset_length = 0;
	dce_i2c_hw->setup_limit = I2C_SETUP_TIME_LIMIT_DCE;
	dce_i2c_hw->buffer_size = I2C_HW_BUFFER_SIZE_DCE;
पूर्ण

व्योम dce100_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks)
अणु
	dce_i2c_hw_स्थिरruct(dce_i2c_hw,
			ctx,
			engine_id,
			regs,
			shअगरts,
			masks);
	dce_i2c_hw->buffer_size = I2C_HW_BUFFER_SIZE_DCE100;
पूर्ण

व्योम dce112_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks)
अणु
	dce100_i2c_hw_स्थिरruct(dce_i2c_hw,
			ctx,
			engine_id,
			regs,
			shअगरts,
			masks);
	dce_i2c_hw->शेष_speed = DEFAULT_I2C_HW_SPEED_100KHZ;
पूर्ण

व्योम dcn1_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks)
अणु
	dce112_i2c_hw_स्थिरruct(dce_i2c_hw,
			ctx,
			engine_id,
			regs,
			shअगरts,
			masks);
	dce_i2c_hw->setup_limit = I2C_SETUP_TIME_LIMIT_DCN;
पूर्ण

व्योम dcn2_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks)
अणु
	dcn1_i2c_hw_स्थिरruct(dce_i2c_hw,
			ctx,
			engine_id,
			regs,
			shअगरts,
			masks);
	dce_i2c_hw->send_reset_length = I2C_SEND_RESET_LENGTH_9;
	अगर (ctx->dc->debug.scl_reset_length10)
		dce_i2c_hw->send_reset_length = I2C_SEND_RESET_LENGTH_10;
पूर्ण
