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

#अगर_अघोषित __DCE_I2C_SW_H__
#घोषणा __DCE_I2C_SW_H__

क्रमागत अणु
	DCE_I2C_DEFAULT_I2C_SW_SPEED = 50,
	I2C_SW_RETRIES = 10,
	I2C_SW_TIMEOUT_DELAY = 3000,
पूर्ण;

काष्ठा dce_i2c_sw अणु
	काष्ठा ddc *ddc;
	काष्ठा dc_context *ctx;
	uपूर्णांक32_t घड़ी_delay;
	uपूर्णांक32_t speed;
पूर्ण;

व्योम dce_i2c_sw_स्थिरruct(
	काष्ठा dce_i2c_sw *dce_i2c_sw,
	काष्ठा dc_context *ctx);

bool dce_i2c_submit_command_sw(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc,
	काष्ठा i2c_command *cmd,
	काष्ठा dce_i2c_sw *dce_i2c_sw);

bool dce_i2c_engine_acquire_sw(
	काष्ठा dce_i2c_sw *dce_i2c_sw,
	काष्ठा ddc *ddc_handle);

#पूर्ण_अगर

