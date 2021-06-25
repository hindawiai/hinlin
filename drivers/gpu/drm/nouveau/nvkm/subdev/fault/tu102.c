<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश <subdev/mc.h>
#समावेश <subdev/mmu.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

अटल व्योम
tu102_fault_buffer_पूर्णांकr(काष्ठा nvkm_fault_buffer *buffer, bool enable)
अणु
	/*XXX: Earlier versions of RM touched the old regs on Turing,
	 *     which करोn't appear to actually work anymore, but newer
	 *     versions of RM करोn't appear to touch anything at all..
	 */
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;

	nvkm_mc_पूर्णांकr_mask(device, NVKM_SUBDEV_FAULT, 0, enable);
पूर्ण

अटल व्योम
tu102_fault_buffer_fini(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 foff = buffer->id * 0x20;

	/* Disable the fault पूर्णांकerrupts */
	nvkm_wr32(device, 0xb81408, 0x1);
	nvkm_wr32(device, 0xb81410, 0x10);

	nvkm_mask(device, 0xb83010 + foff, 0x80000000, 0x00000000);
पूर्ण

अटल व्योम
tu102_fault_buffer_init(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 foff = buffer->id * 0x20;

	/* Enable the fault पूर्णांकerrupts */
	nvkm_wr32(device, 0xb81208, 0x1);
	nvkm_wr32(device, 0xb81210, 0x10);

	nvkm_mask(device, 0xb83010 + foff, 0xc0000000, 0x40000000);
	nvkm_wr32(device, 0xb83004 + foff, upper_32_bits(buffer->addr));
	nvkm_wr32(device, 0xb83000 + foff, lower_32_bits(buffer->addr));
	nvkm_mask(device, 0xb83010 + foff, 0x80000000, 0x80000000);
पूर्ण

अटल व्योम
tu102_fault_buffer_info(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 foff = buffer->id * 0x20;

	nvkm_mask(device, 0xb83010 + foff, 0x40000000, 0x40000000);

	buffer->entries = nvkm_rd32(device, 0xb83010 + foff) & 0x000fffff;
	buffer->get = 0xb83008 + foff;
	buffer->put = 0xb8300c + foff;
पूर्ण

अटल व्योम
tu102_fault_पूर्णांकr_fault(काष्ठा nvkm_fault *fault)
अणु
	काष्ठा nvkm_subdev *subdev = &fault->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fault_data info;
	स्थिर u32 addrlo = nvkm_rd32(device, 0xb83080);
	स्थिर u32 addrhi = nvkm_rd32(device, 0xb83084);
	स्थिर u32  info0 = nvkm_rd32(device, 0xb83088);
	स्थिर u32 insthi = nvkm_rd32(device, 0xb8308c);
	स्थिर u32  info1 = nvkm_rd32(device, 0xb83090);

	info.addr = ((u64)addrhi << 32) | addrlo;
	info.inst = ((u64)insthi << 32) | (info0 & 0xfffff000);
	info.समय = 0;
	info.engine = (info0 & 0x000000ff);
	info.valid  = (info1 & 0x80000000) >> 31;
	info.gpc    = (info1 & 0x1f000000) >> 24;
	info.hub    = (info1 & 0x00100000) >> 20;
	info.access = (info1 & 0x000f0000) >> 16;
	info.client = (info1 & 0x00007f00) >> 8;
	info.reason = (info1 & 0x0000001f);

	nvkm_fअगरo_fault(device->fअगरo, &info);
पूर्ण

अटल व्योम
tu102_fault_पूर्णांकr(काष्ठा nvkm_fault *fault)
अणु
	काष्ठा nvkm_subdev *subdev = &fault->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0xb83094);

	अगर (stat & 0x80000000) अणु
		tu102_fault_पूर्णांकr_fault(fault);
		nvkm_wr32(device, 0xb83094, 0x80000000);
		stat &= ~0x80000000;
	पूर्ण

	अगर (stat & 0x00000200) अणु
		/* Clear the associated पूर्णांकerrupt flag */
		nvkm_wr32(device, 0xb81010, 0x10);

		अगर (fault->buffer[0]) अणु
			nvkm_event_send(&fault->event, 1, 0, शून्य, 0);
			stat &= ~0x00000200;
		पूर्ण
	पूर्ण

	/* Replayable MMU fault */
	अगर (stat & 0x00000100) अणु
		/* Clear the associated पूर्णांकerrupt flag */
		nvkm_wr32(device, 0xb81008, 0x1);

		अगर (fault->buffer[1]) अणु
			nvkm_event_send(&fault->event, 1, 1, शून्य, 0);
			stat &= ~0x00000100;
		पूर्ण
	पूर्ण

	अगर (stat) अणु
		nvkm_debug(subdev, "intr %08x\n", stat);
	पूर्ण
पूर्ण

अटल व्योम
tu102_fault_fini(काष्ठा nvkm_fault *fault)
अणु
	nvkm_notअगरy_put(&fault->nrpfb);
	अगर (fault->buffer[0])
		fault->func->buffer.fini(fault->buffer[0]);
	/*XXX: disable priv faults */
पूर्ण

अटल व्योम
tu102_fault_init(काष्ठा nvkm_fault *fault)
अणु
	/*XXX: enable priv faults */
	fault->func->buffer.init(fault->buffer[0]);
	nvkm_notअगरy_get(&fault->nrpfb);
पूर्ण

अटल स्थिर काष्ठा nvkm_fault_func
tu102_fault = अणु
	.oneinit = gv100_fault_oneinit,
	.init = tu102_fault_init,
	.fini = tu102_fault_fini,
	.पूर्णांकr = tu102_fault_पूर्णांकr,
	.buffer.nr = 2,
	.buffer.entry_size = 32,
	.buffer.info = tu102_fault_buffer_info,
	.buffer.pin = gp100_fault_buffer_pin,
	.buffer.init = tu102_fault_buffer_init,
	.buffer.fini = tu102_fault_buffer_fini,
	.buffer.पूर्णांकr = tu102_fault_buffer_पूर्णांकr,
	.user = अणु अणु 0, 0, VOLTA_FAULT_BUFFER_A पूर्ण, 1 पूर्ण,
पूर्ण;

पूर्णांक
tu102_fault_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_fault **pfault)
अणु
	वापस nvkm_fault_new_(&tu102_fault, device, type, inst, pfault);
पूर्ण
