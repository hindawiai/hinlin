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
#समावेश "dce_i2c.h"
#समावेश "reg_helper.h"

bool dce_i2c_submit_command(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc,
	काष्ठा i2c_command *cmd)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw;
	काष्ठा dce_i2c_sw dce_i2c_sw = अणु0पूर्ण;

	अगर (!ddc) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!cmd) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	dce_i2c_hw = acquire_i2c_hw_engine(pool, ddc);

	अगर (dce_i2c_hw)
		वापस dce_i2c_submit_command_hw(pool, ddc, cmd, dce_i2c_hw);

	dce_i2c_sw.ctx = ddc->ctx;
	अगर (dce_i2c_engine_acquire_sw(&dce_i2c_sw, ddc)) अणु
		वापस dce_i2c_submit_command_sw(pool, ddc, cmd, &dce_i2c_sw);
	पूर्ण

	वापस false;
पूर्ण
