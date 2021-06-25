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

#समावेश "dce_i2c.h"
#समावेश "dce_i2c_sw.h"
#समावेश "include/gpio_service_interface.h"
#घोषणा SCL false
#घोषणा SDA true

व्योम dce_i2c_sw_स्थिरruct(
	काष्ठा dce_i2c_sw *dce_i2c_sw,
	काष्ठा dc_context *ctx)
अणु
	dce_i2c_sw->ctx = ctx;
पूर्ण

अटल अंतरभूत bool पढ़ो_bit_from_ddc(
	काष्ठा ddc *ddc,
	bool data_nor_घड़ी)
अणु
	uपूर्णांक32_t value = 0;

	अगर (data_nor_घड़ी)
		dal_gpio_get_value(ddc->pin_data, &value);
	अन्यथा
		dal_gpio_get_value(ddc->pin_घड़ी, &value);

	वापस (value != 0);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_bit_to_ddc(
	काष्ठा ddc *ddc,
	bool data_nor_घड़ी,
	bool bit)
अणु
	uपूर्णांक32_t value = bit ? 1 : 0;

	अगर (data_nor_घड़ी)
		dal_gpio_set_value(ddc->pin_data, value);
	अन्यथा
		dal_gpio_set_value(ddc->pin_घड़ी, value);
पूर्ण

अटल व्योम release_engine_dce_sw(
	काष्ठा resource_pool *pool,
	काष्ठा dce_i2c_sw *dce_i2c_sw)
अणु
	dal_ddc_बंद(dce_i2c_sw->ddc);
	dce_i2c_sw->ddc = शून्य;
पूर्ण

अटल bool रुको_क्रम_scl_high_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc,
	uपूर्णांक16_t घड़ी_delay_भाग_4)
अणु
	uपूर्णांक32_t scl_retry = 0;
	uपूर्णांक32_t scl_retry_max = I2C_SW_TIMEOUT_DELAY / घड़ी_delay_भाग_4;

	udelay(घड़ी_delay_भाग_4);

	करो अणु
		अगर (पढ़ो_bit_from_ddc(ddc, SCL))
			वापस true;

		udelay(घड़ी_delay_भाग_4);

		++scl_retry;
	पूर्ण जबतक (scl_retry <= scl_retry_max);

	वापस false;
पूर्ण
अटल bool ग_लिखो_byte_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc_handle,
	uपूर्णांक16_t घड़ी_delay_भाग_4,
	uपूर्णांक8_t byte)
अणु
	पूर्णांक32_t shअगरt = 7;
	bool ack;

	/* bits are transmitted serially, starting from MSB */

	करो अणु
		udelay(घड़ी_delay_भाग_4);

		ग_लिखो_bit_to_ddc(ddc_handle, SDA, (byte >> shअगरt) & 1);

		udelay(घड़ी_delay_भाग_4);

		ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

		अगर (!रुको_क्रम_scl_high_sw(ctx, ddc_handle, घड़ी_delay_भाग_4))
			वापस false;

		ग_लिखो_bit_to_ddc(ddc_handle, SCL, false);

		--shअगरt;
	पूर्ण जबतक (shअगरt >= 0);

	/* The display sends ACK by preventing the SDA from going high
	 * after the SCL pulse we use to send our last data bit.
	 * If the SDA goes high after that bit, it's a NACK
	 */

	udelay(घड़ी_delay_भाग_4);

	ग_लिखो_bit_to_ddc(ddc_handle, SDA, true);

	udelay(घड़ी_delay_भाग_4);

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

	अगर (!रुको_क्रम_scl_high_sw(ctx, ddc_handle, घड़ी_delay_भाग_4))
		वापस false;

	/* पढ़ो ACK bit */

	ack = !पढ़ो_bit_from_ddc(ddc_handle, SDA);

	udelay(घड़ी_delay_भाग_4 << 1);

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, false);

	udelay(घड़ी_delay_भाग_4 << 1);

	वापस ack;
पूर्ण

अटल bool पढ़ो_byte_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc_handle,
	uपूर्णांक16_t घड़ी_delay_भाग_4,
	uपूर्णांक8_t *byte,
	bool more)
अणु
	पूर्णांक32_t shअगरt = 7;

	uपूर्णांक8_t data = 0;

	/* The data bits are पढ़ो from MSB to LSB;
	 * bit is पढ़ो जबतक SCL is high
	 */

	करो अणु
		ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

		अगर (!रुको_क्रम_scl_high_sw(ctx, ddc_handle, घड़ी_delay_भाग_4))
			वापस false;

		अगर (पढ़ो_bit_from_ddc(ddc_handle, SDA))
			data |= (1 << shअगरt);

		ग_लिखो_bit_to_ddc(ddc_handle, SCL, false);

		udelay(घड़ी_delay_भाग_4 << 1);

		--shअगरt;
	पूर्ण जबतक (shअगरt >= 0);

	/* पढ़ो only whole byte */

	*byte = data;

	udelay(घड़ी_delay_भाग_4);

	/* send the acknowledge bit:
	 * SDA low means ACK, SDA high means NACK
	 */

	ग_लिखो_bit_to_ddc(ddc_handle, SDA, !more);

	udelay(घड़ी_delay_भाग_4);

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

	अगर (!रुको_क्रम_scl_high_sw(ctx, ddc_handle, घड़ी_delay_भाग_4))
		वापस false;

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, false);

	udelay(घड़ी_delay_भाग_4);

	ग_लिखो_bit_to_ddc(ddc_handle, SDA, true);

	udelay(घड़ी_delay_भाग_4);

	वापस true;
पूर्ण
अटल bool stop_sync_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc_handle,
	uपूर्णांक16_t घड़ी_delay_भाग_4)
अणु
	uपूर्णांक32_t retry = 0;

	/* The I2C communications stop संकेत is:
	 * the SDA going high from low, जबतक the SCL is high.
	 */

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, false);

	udelay(घड़ी_delay_भाग_4);

	ग_लिखो_bit_to_ddc(ddc_handle, SDA, false);

	udelay(घड़ी_delay_भाग_4);

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

	अगर (!रुको_क्रम_scl_high_sw(ctx, ddc_handle, घड़ी_delay_भाग_4))
		वापस false;

	ग_लिखो_bit_to_ddc(ddc_handle, SDA, true);

	करो अणु
		udelay(घड़ी_delay_भाग_4);

		अगर (पढ़ो_bit_from_ddc(ddc_handle, SDA))
			वापस true;

		++retry;
	पूर्ण जबतक (retry <= 2);

	वापस false;
पूर्ण
अटल bool i2c_ग_लिखो_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc_handle,
	uपूर्णांक16_t घड़ी_delay_भाग_4,
	uपूर्णांक8_t address,
	uपूर्णांक32_t length,
	स्थिर uपूर्णांक8_t *data)
अणु
	uपूर्णांक32_t i = 0;

	अगर (!ग_लिखो_byte_sw(ctx, ddc_handle, घड़ी_delay_भाग_4, address))
		वापस false;

	जबतक (i < length) अणु
		अगर (!ग_लिखो_byte_sw(ctx, ddc_handle, घड़ी_delay_भाग_4, data[i]))
			वापस false;
		++i;
	पूर्ण

	वापस true;
पूर्ण

अटल bool i2c_पढ़ो_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc_handle,
	uपूर्णांक16_t घड़ी_delay_भाग_4,
	uपूर्णांक8_t address,
	uपूर्णांक32_t length,
	uपूर्णांक8_t *data)
अणु
	uपूर्णांक32_t i = 0;

	अगर (!ग_लिखो_byte_sw(ctx, ddc_handle, घड़ी_delay_भाग_4, address))
		वापस false;

	जबतक (i < length) अणु
		अगर (!पढ़ो_byte_sw(ctx, ddc_handle, घड़ी_delay_भाग_4, data + i,
			i < length - 1))
			वापस false;
		++i;
	पूर्ण

	वापस true;
पूर्ण



अटल bool start_sync_sw(
	काष्ठा dc_context *ctx,
	काष्ठा ddc *ddc_handle,
	uपूर्णांक16_t घड़ी_delay_भाग_4)
अणु
	uपूर्णांक32_t retry = 0;

	/* The I2C communications start संकेत is:
	 * the SDA going low from high, जबतक the SCL is high.
	 */

	ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

	udelay(घड़ी_delay_भाग_4);

	करो अणु
		ग_लिखो_bit_to_ddc(ddc_handle, SDA, true);

		अगर (!पढ़ो_bit_from_ddc(ddc_handle, SDA)) अणु
			++retry;
			जारी;
		पूर्ण

		udelay(घड़ी_delay_भाग_4);

		ग_लिखो_bit_to_ddc(ddc_handle, SCL, true);

		अगर (!रुको_क्रम_scl_high_sw(ctx, ddc_handle, घड़ी_delay_भाग_4))
			अवरोध;

		ग_लिखो_bit_to_ddc(ddc_handle, SDA, false);

		udelay(घड़ी_delay_भाग_4);

		ग_लिखो_bit_to_ddc(ddc_handle, SCL, false);

		udelay(घड़ी_delay_भाग_4);

		वापस true;
	पूर्ण जबतक (retry <= I2C_SW_RETRIES);

	वापस false;
पूर्ण

अटल व्योम dce_i2c_sw_engine_set_speed(
	काष्ठा dce_i2c_sw *engine,
	uपूर्णांक32_t speed)
अणु
	ASSERT(speed);

	engine->speed = speed ? speed : DCE_I2C_DEFAULT_I2C_SW_SPEED;

	engine->घड़ी_delay = 1000 / engine->speed;

	अगर (engine->घड़ी_delay < 12)
		engine->घड़ी_delay = 12;
पूर्ण

अटल bool dce_i2c_sw_engine_acquire_engine(
	काष्ठा dce_i2c_sw *engine,
	काष्ठा ddc *ddc)
अणु
	क्रमागत gpio_result result;

	result = dal_ddc_खोलो(ddc, GPIO_MODE_FAST_OUTPUT,
		GPIO_DDC_CONFIG_TYPE_MODE_I2C);

	अगर (result != GPIO_RESULT_OK)
		वापस false;

	engine->ddc = ddc;

	वापस true;
पूर्ण
bool dce_i2c_engine_acquire_sw(
	काष्ठा dce_i2c_sw *dce_i2c_sw,
	काष्ठा ddc *ddc_handle)
अणु
	uपूर्णांक32_t counter = 0;
	bool result;

	करो अणु

		result = dce_i2c_sw_engine_acquire_engine(
				dce_i2c_sw, ddc_handle);

		अगर (result)
			अवरोध;

		/* i2c_engine is busy by VBios, lets रुको and retry */

		udelay(10);

		++counter;
	पूर्ण जबतक (counter < 2);

	वापस result;
पूर्ण




अटल व्योम dce_i2c_sw_engine_submit_channel_request(
	काष्ठा dce_i2c_sw *engine,
	काष्ठा i2c_request_transaction_data *req)
अणु
	काष्ठा ddc *ddc = engine->ddc;
	uपूर्णांक16_t घड़ी_delay_भाग_4 = engine->घड़ी_delay >> 2;

	/* send sync (start / repeated start) */

	bool result = start_sync_sw(engine->ctx, ddc, घड़ी_delay_भाग_4);

	/* process payload */

	अगर (result) अणु
		चयन (req->action) अणु
		हाल DCE_I2C_TRANSACTION_ACTION_I2C_WRITE:
		हाल DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT:
			result = i2c_ग_लिखो_sw(engine->ctx, ddc, घड़ी_delay_भाग_4,
				req->address, req->length, req->data);
		अवरोध;
		हाल DCE_I2C_TRANSACTION_ACTION_I2C_READ:
		हाल DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT:
			result = i2c_पढ़ो_sw(engine->ctx, ddc, घड़ी_delay_भाग_4,
				req->address, req->length, req->data);
		अवरोध;
		शेष:
			result = false;
		अवरोध;
		पूर्ण
	पूर्ण

	/* send stop अगर not 'mot' or operation failed */

	अगर (!result ||
		(req->action == DCE_I2C_TRANSACTION_ACTION_I2C_WRITE) ||
		(req->action == DCE_I2C_TRANSACTION_ACTION_I2C_READ))
		अगर (!stop_sync_sw(engine->ctx, ddc, घड़ी_delay_भाग_4))
			result = false;

	req->status = result ?
		I2C_CHANNEL_OPERATION_SUCCEEDED :
		I2C_CHANNEL_OPERATION_FAILED;
पूर्ण

अटल bool dce_i2c_sw_engine_submit_payload(
	काष्ठा dce_i2c_sw *engine,
	काष्ठा i2c_payload *payload,
	bool middle_of_transaction)
अणु
	काष्ठा i2c_request_transaction_data request;

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

	dce_i2c_sw_engine_submit_channel_request(engine, &request);

	अगर ((request.status == I2C_CHANNEL_OPERATION_ENGINE_BUSY) ||
		(request.status == I2C_CHANNEL_OPERATION_FAILED))
		वापस false;

	वापस true;
पूर्ण
bool dce_i2c_submit_command_sw(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc,
	काष्ठा i2c_command *cmd,
	काष्ठा dce_i2c_sw *dce_i2c_sw)
अणु
	uपूर्णांक8_t index_of_payload = 0;
	bool result;

	dce_i2c_sw_engine_set_speed(dce_i2c_sw, cmd->speed);

	result = true;

	जबतक (index_of_payload < cmd->number_of_payloads) अणु
		bool mot = (index_of_payload != cmd->number_of_payloads - 1);

		काष्ठा i2c_payload *payload = cmd->payloads + index_of_payload;

		अगर (!dce_i2c_sw_engine_submit_payload(
			dce_i2c_sw, payload, mot)) अणु
			result = false;
			अवरोध;
		पूर्ण

		++index_of_payload;
	पूर्ण

	release_engine_dce_sw(pool, dce_i2c_sw);

	वापस result;
पूर्ण
