<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __ATOMBIOS_I2C_H__
#घोषणा __ATOMBIOS_I2C_H__

पूर्णांक amdgpu_atombios_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
		      काष्ठा i2c_msg *msgs, पूर्णांक num);
u32 amdgpu_atombios_i2c_func(काष्ठा i2c_adapter *adap);
व्योम amdgpu_atombios_i2c_channel_trans(काष्ठा amdgpu_device* adev,
		u8 slave_addr, u8 line_number, u8 offset, u8 data);

#पूर्ण_अगर
