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
#अगर_अघोषित DC_DDC_TYPES_H_
#घोषणा DC_DDC_TYPES_H_

क्रमागत aux_transaction_type अणु
	AUX_TRANSACTION_TYPE_DP,
	AUX_TRANSACTION_TYPE_I2C
पूर्ण;


क्रमागत i2caux_transaction_action अणु
	I2CAUX_TRANSACTION_ACTION_I2C_WRITE = 0x00,
	I2CAUX_TRANSACTION_ACTION_I2C_READ = 0x10,
	I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST = 0x20,

	I2CAUX_TRANSACTION_ACTION_I2C_WRITE_MOT = 0x40,
	I2CAUX_TRANSACTION_ACTION_I2C_READ_MOT = 0x50,
	I2CAUX_TRANSACTION_ACTION_I2C_STATUS_REQUEST_MOT = 0x60,

	I2CAUX_TRANSACTION_ACTION_DP_WRITE = 0x80,
	I2CAUX_TRANSACTION_ACTION_DP_READ = 0x90
पूर्ण;

काष्ठा aux_request_transaction_data अणु
	क्रमागत aux_transaction_type type;
	क्रमागत i2caux_transaction_action action;
	/* 20-bit AUX channel transaction address */
	uपूर्णांक32_t address;
	/* delay, in 100-microsecond units */
	uपूर्णांक8_t delay;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;
पूर्ण;

क्रमागत aux_transaction_reply अणु
	AUX_TRANSACTION_REPLY_AUX_ACK = 0x00,
	AUX_TRANSACTION_REPLY_AUX_NACK = 0x01,
	AUX_TRANSACTION_REPLY_AUX_DEFER = 0x02,
	AUX_TRANSACTION_REPLY_I2C_OVER_AUX_NACK = 0x04,
	AUX_TRANSACTION_REPLY_I2C_OVER_AUX_DEFER = 0x08,

	AUX_TRANSACTION_REPLY_I2C_ACK = 0x00,
	AUX_TRANSACTION_REPLY_I2C_NACK = 0x10,
	AUX_TRANSACTION_REPLY_I2C_DEFER = 0x20,

	AUX_TRANSACTION_REPLY_HPD_DISCON = 0x40,

	AUX_TRANSACTION_REPLY_INVALID = 0xFF
पूर्ण;

काष्ठा aux_reply_transaction_data अणु
	क्रमागत aux_transaction_reply status;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;
पूर्ण;

काष्ठा i2c_payload अणु
	bool ग_लिखो;
	uपूर्णांक8_t address;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;
पूर्ण;

क्रमागत i2c_command_engine अणु
	I2C_COMMAND_ENGINE_DEFAULT,
	I2C_COMMAND_ENGINE_SW,
	I2C_COMMAND_ENGINE_HW
पूर्ण;

काष्ठा i2c_command अणु
	काष्ठा i2c_payload *payloads;
	uपूर्णांक8_t number_of_payloads;

	क्रमागत i2c_command_engine engine;

	/* expressed in KHz
	 * zero means "use default value" */
	uपूर्णांक32_t speed;
पूर्ण;

काष्ठा gpio_ddc_hw_info अणु
	bool hw_supported;
	uपूर्णांक32_t ddc_channel;
पूर्ण;

काष्ठा ddc अणु
	काष्ठा gpio *pin_data;
	काष्ठा gpio *pin_घड़ी;
	काष्ठा gpio_ddc_hw_info hw_info;
	काष्ठा dc_context *ctx;
पूर्ण;

जोड़ ddc_wa अणु
	काष्ठा अणु
		uपूर्णांक32_t DP_SKIP_POWER_OFF:1;
		uपूर्णांक32_t DP_AUX_POWER_UP_WA_DELAY:1;
	पूर्ण bits;
	uपूर्णांक32_t raw;
पूर्ण;

काष्ठा ddc_flags अणु
	uपूर्णांक8_t EDID_QUERY_DONE_ONCE:1;
	uपूर्णांक8_t IS_INTERNAL_DISPLAY:1;
	uपूर्णांक8_t FORCE_READ_REPEATED_START:1;
	uपूर्णांक8_t EDID_STRESS_READ:1;

पूर्ण;

क्रमागत ddc_transaction_type अणु
	DDC_TRANSACTION_TYPE_NONE = 0,
	DDC_TRANSACTION_TYPE_I2C,
	DDC_TRANSACTION_TYPE_I2C_OVER_AUX,
	DDC_TRANSACTION_TYPE_I2C_OVER_AUX_WITH_DEFER,
	DDC_TRANSACTION_TYPE_I2C_OVER_AUX_RETRY_DEFER
पूर्ण;

क्रमागत display_करोngle_type अणु
	DISPLAY_DONGLE_NONE = 0,
	/* Active converter types*/
	DISPLAY_DONGLE_DP_VGA_CONVERTER,
	DISPLAY_DONGLE_DP_DVI_CONVERTER,
	DISPLAY_DONGLE_DP_HDMI_CONVERTER,
	/* DP-HDMI/DVI passive करोngles (Type 1 and Type 2)*/
	DISPLAY_DONGLE_DP_DVI_DONGLE,
	DISPLAY_DONGLE_DP_HDMI_DONGLE,
	/* Other types of करोngle*/
	DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE,
पूर्ण;

काष्ठा ddc_service अणु
	काष्ठा ddc *ddc_pin;
	काष्ठा ddc_flags flags;
	जोड़ ddc_wa wa;
	क्रमागत ddc_transaction_type transaction_type;
	क्रमागत display_करोngle_type करोngle_type;
	काष्ठा dc_context *ctx;
	काष्ठा dc_link *link;

	uपूर्णांक32_t address;
	uपूर्णांक32_t edid_buf_len;
	uपूर्णांक8_t edid_buf[DC_MAX_EDID_BUFFER_SIZE];
पूर्ण;

#पूर्ण_अगर /* DC_DDC_TYPES_H_ */
