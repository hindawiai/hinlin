<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 *
 */

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "amdgpu_atombios.h"
#समावेश "atombios_i2c.h"

#घोषणा TARGET_HW_I2C_CLOCK 50

/* these are a limitation of ProcessI2cChannelTransaction not the hw */
#घोषणा ATOM_MAX_HW_I2C_WRITE 3
#घोषणा ATOM_MAX_HW_I2C_READ  255

अटल पूर्णांक amdgpu_atombios_i2c_process_i2c_ch(काष्ठा amdgpu_i2c_chan *chan,
				       u8 slave_addr, u8 flags,
				       u8 *buf, u8 num)
अणु
	काष्ठा drm_device *dev = chan->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	PROCESS_I2C_CHANNEL_TRANSACTION_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ProcessI2cChannelTransaction);
	अचिन्हित अक्षर *base;
	u16 out = cpu_to_le16(0);
	पूर्णांक r = 0;

	स_रखो(&args, 0, माप(args));

	mutex_lock(&chan->mutex);

	base = (अचिन्हित अक्षर *)adev->mode_info.atom_context->scratch;

	अगर (flags & HW_I2C_WRITE) अणु
		अगर (num > ATOM_MAX_HW_I2C_WRITE) अणु
			DRM_ERROR("hw i2c: tried to write too many bytes (%d vs 3)\n", num);
			r = -EINVAL;
			जाओ करोne;
		पूर्ण
		अगर (buf == शून्य)
			args.ucRegIndex = 0;
		अन्यथा
			args.ucRegIndex = buf[0];
		अगर (num)
			num--;
		अगर (num) अणु
			अगर (buf) अणु
				स_नकल(&out, &buf[1], num);
			पूर्ण अन्यथा अणु
				DRM_ERROR("hw i2c: missing buf with num > 1\n");
				r = -EINVAL;
				जाओ करोne;
			पूर्ण
		पूर्ण
		args.lpI2CDataOut = cpu_to_le16(out);
	पूर्ण अन्यथा अणु
		args.ucRegIndex = 0;
		args.lpI2CDataOut = 0;
	पूर्ण

	args.ucFlag = flags;
	args.ucI2CSpeed = TARGET_HW_I2C_CLOCK;
	args.ucTransBytes = num;
	args.ucSlaveAddr = slave_addr << 1;
	args.ucLineNumber = chan->rec.i2c_id;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	/* error */
	अगर (args.ucStatus != HW_ASSISTED_I2C_STATUS_SUCCESS) अणु
		DRM_DEBUG_KMS("hw_i2c error\n");
		r = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (!(flags & HW_I2C_WRITE))
		amdgpu_atombios_copy_swap(buf, base, num, false);

करोne:
	mutex_unlock(&chan->mutex);

	वापस r;
पूर्ण

पूर्णांक amdgpu_atombios_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
		      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा i2c_msg *p;
	पूर्णांक i, reमुख्यing, current_count, buffer_offset, max_bytes, ret;
	u8 flags;

	/* check क्रम bus probe */
	p = &msgs[0];
	अगर ((num == 1) && (p->len == 0)) अणु
		ret = amdgpu_atombios_i2c_process_i2c_ch(i2c,
						  p->addr, HW_I2C_WRITE,
						  शून्य, 0);
		अगर (ret)
			वापस ret;
		अन्यथा
			वापस num;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		p = &msgs[i];
		reमुख्यing = p->len;
		buffer_offset = 0;
		/* max_bytes are a limitation of ProcessI2cChannelTransaction not the hw */
		अगर (p->flags & I2C_M_RD) अणु
			max_bytes = ATOM_MAX_HW_I2C_READ;
			flags = HW_I2C_READ;
		पूर्ण अन्यथा अणु
			max_bytes = ATOM_MAX_HW_I2C_WRITE;
			flags = HW_I2C_WRITE;
		पूर्ण
		जबतक (reमुख्यing) अणु
			अगर (reमुख्यing > max_bytes)
				current_count = max_bytes;
			अन्यथा
				current_count = reमुख्यing;
			ret = amdgpu_atombios_i2c_process_i2c_ch(i2c,
							  p->addr, flags,
							  &p->buf[buffer_offset], current_count);
			अगर (ret)
				वापस ret;
			reमुख्यing -= current_count;
			buffer_offset += current_count;
		पूर्ण
	पूर्ण

	वापस num;
पूर्ण

u32 amdgpu_atombios_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

व्योम amdgpu_atombios_i2c_channel_trans(काष्ठा amdgpu_device *adev, u8 slave_addr, u8 line_number, u8 offset, u8 data)
अणु
	PROCESS_I2C_CHANNEL_TRANSACTION_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ProcessI2cChannelTransaction);

	args.ucRegIndex = offset;
	args.lpI2CDataOut = data;
	args.ucFlag = 1;
	args.ucI2CSpeed = TARGET_HW_I2C_CLOCK;
	args.ucTransBytes = 1;
	args.ucSlaveAddr = slave_addr;
	args.ucLineNumber = line_number;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण
