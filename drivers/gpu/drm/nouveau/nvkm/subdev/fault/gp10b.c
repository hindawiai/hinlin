<शैली गुरु>
/*
 * Copyright (c) 2019 NVIDIA Corporation.
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
 */

#समावेश "priv.h"

#समावेश <core/memory.h>

#समावेश <nvअगर/class.h>

u64
gp10b_fault_buffer_pin(काष्ठा nvkm_fault_buffer *buffer)
अणु
	वापस nvkm_memory_addr(buffer->mem);
पूर्ण

अटल स्थिर काष्ठा nvkm_fault_func
gp10b_fault = अणु
	.पूर्णांकr = gp100_fault_पूर्णांकr,
	.buffer.nr = 1,
	.buffer.entry_size = 32,
	.buffer.info = gp100_fault_buffer_info,
	.buffer.pin = gp10b_fault_buffer_pin,
	.buffer.init = gp100_fault_buffer_init,
	.buffer.fini = gp100_fault_buffer_fini,
	.buffer.पूर्णांकr = gp100_fault_buffer_पूर्णांकr,
	.user = अणु अणु 0, 0, MAXWELL_FAULT_BUFFER_A पूर्ण, 0 पूर्ण,
पूर्ण;

पूर्णांक
gp10b_fault_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_fault **pfault)
अणु
	वापस nvkm_fault_new_(&gp10b_fault, device, type, inst, pfault);
पूर्ण
