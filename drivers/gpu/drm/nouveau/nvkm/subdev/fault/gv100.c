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
#समावेश <subdev/mmu.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

अटल व्योम
gv100_fault_buffer_process(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	काष्ठा nvkm_memory *mem = buffer->mem;
	u32 get = nvkm_rd32(device, buffer->get);
	u32 put = nvkm_rd32(device, buffer->put);
	अगर (put == get)
		वापस;

	nvkm_kmap(mem);
	जबतक (get != put) अणु
		स्थिर u32   base = get * buffer->fault->func->buffer.entry_size;
		स्थिर u32 instlo = nvkm_ro32(mem, base + 0x00);
		स्थिर u32 insthi = nvkm_ro32(mem, base + 0x04);
		स्थिर u32 addrlo = nvkm_ro32(mem, base + 0x08);
		स्थिर u32 addrhi = nvkm_ro32(mem, base + 0x0c);
		स्थिर u32 समयlo = nvkm_ro32(mem, base + 0x10);
		स्थिर u32 समयhi = nvkm_ro32(mem, base + 0x14);
		स्थिर u32  info0 = nvkm_ro32(mem, base + 0x18);
		स्थिर u32  info1 = nvkm_ro32(mem, base + 0x1c);
		काष्ठा nvkm_fault_data info;

		अगर (++get == buffer->entries)
			get = 0;
		nvkm_wr32(device, buffer->get, get);

		info.addr   = ((u64)addrhi << 32) | addrlo;
		info.inst   = ((u64)insthi << 32) | instlo;
		info.समय   = ((u64)समयhi << 32) | समयlo;
		info.engine = (info0 & 0x000000ff);
		info.valid  = (info1 & 0x80000000) >> 31;
		info.gpc    = (info1 & 0x1f000000) >> 24;
		info.hub    = (info1 & 0x00100000) >> 20;
		info.access = (info1 & 0x000f0000) >> 16;
		info.client = (info1 & 0x00007f00) >> 8;
		info.reason = (info1 & 0x0000001f);

		nvkm_fअगरo_fault(device->fअगरo, &info);
	पूर्ण
	nvkm_करोne(mem);
पूर्ण

अटल व्योम
gv100_fault_buffer_पूर्णांकr(काष्ठा nvkm_fault_buffer *buffer, bool enable)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 पूर्णांकr = buffer->id ? 0x08000000 : 0x20000000;
	अगर (enable)
		nvkm_mask(device, 0x100a2c, पूर्णांकr, पूर्णांकr);
	अन्यथा
		nvkm_mask(device, 0x100a34, पूर्णांकr, पूर्णांकr);
पूर्ण

अटल व्योम
gv100_fault_buffer_fini(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 foff = buffer->id * 0x14;
	nvkm_mask(device, 0x100e34 + foff, 0x80000000, 0x00000000);
पूर्ण

अटल व्योम
gv100_fault_buffer_init(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 foff = buffer->id * 0x14;

	nvkm_mask(device, 0x100e34 + foff, 0xc0000000, 0x40000000);
	nvkm_wr32(device, 0x100e28 + foff, upper_32_bits(buffer->addr));
	nvkm_wr32(device, 0x100e24 + foff, lower_32_bits(buffer->addr));
	nvkm_mask(device, 0x100e34 + foff, 0x80000000, 0x80000000);
पूर्ण

अटल व्योम
gv100_fault_buffer_info(काष्ठा nvkm_fault_buffer *buffer)
अणु
	काष्ठा nvkm_device *device = buffer->fault->subdev.device;
	स्थिर u32 foff = buffer->id * 0x14;

	nvkm_mask(device, 0x100e34 + foff, 0x40000000, 0x40000000);

	buffer->entries = nvkm_rd32(device, 0x100e34 + foff) & 0x000fffff;
	buffer->get = 0x100e2c + foff;
	buffer->put = 0x100e30 + foff;
पूर्ण

अटल पूर्णांक
gv100_fault_ntfy_nrpfb(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_fault *fault = container_of(notअगरy, typeof(*fault), nrpfb);
	gv100_fault_buffer_process(fault->buffer[0]);
	वापस NVKM_NOTIFY_KEEP;
पूर्ण

अटल व्योम
gv100_fault_पूर्णांकr_fault(काष्ठा nvkm_fault *fault)
अणु
	काष्ठा nvkm_subdev *subdev = &fault->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fault_data info;
	स्थिर u32 addrlo = nvkm_rd32(device, 0x100e4c);
	स्थिर u32 addrhi = nvkm_rd32(device, 0x100e50);
	स्थिर u32  info0 = nvkm_rd32(device, 0x100e54);
	स्थिर u32 insthi = nvkm_rd32(device, 0x100e58);
	स्थिर u32  info1 = nvkm_rd32(device, 0x100e5c);

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
gv100_fault_पूर्णांकr(काष्ठा nvkm_fault *fault)
अणु
	काष्ठा nvkm_subdev *subdev = &fault->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x100a20);

	अगर (stat & 0x80000000) अणु
		gv100_fault_पूर्णांकr_fault(fault);
		nvkm_wr32(device, 0x100e60, 0x80000000);
		stat &= ~0x80000000;
	पूर्ण

	अगर (stat & 0x20000000) अणु
		अगर (fault->buffer[0]) अणु
			nvkm_event_send(&fault->event, 1, 0, शून्य, 0);
			stat &= ~0x20000000;
		पूर्ण
	पूर्ण

	अगर (stat & 0x08000000) अणु
		अगर (fault->buffer[1]) अणु
			nvkm_event_send(&fault->event, 1, 1, शून्य, 0);
			stat &= ~0x08000000;
		पूर्ण
	पूर्ण

	अगर (stat) अणु
		nvkm_debug(subdev, "intr %08x\n", stat);
	पूर्ण
पूर्ण

अटल व्योम
gv100_fault_fini(काष्ठा nvkm_fault *fault)
अणु
	nvkm_notअगरy_put(&fault->nrpfb);
	अगर (fault->buffer[0])
		fault->func->buffer.fini(fault->buffer[0]);
	nvkm_mask(fault->subdev.device, 0x100a34, 0x80000000, 0x80000000);
पूर्ण

अटल व्योम
gv100_fault_init(काष्ठा nvkm_fault *fault)
अणु
	nvkm_mask(fault->subdev.device, 0x100a2c, 0x80000000, 0x80000000);
	fault->func->buffer.init(fault->buffer[0]);
	nvkm_notअगरy_get(&fault->nrpfb);
पूर्ण

पूर्णांक
gv100_fault_oneinit(काष्ठा nvkm_fault *fault)
अणु
	वापस nvkm_notअगरy_init(&fault->buffer[0]->object, &fault->event,
				gv100_fault_ntfy_nrpfb, true, शून्य, 0, 0,
				&fault->nrpfb);
पूर्ण

अटल स्थिर काष्ठा nvkm_fault_func
gv100_fault = अणु
	.oneinit = gv100_fault_oneinit,
	.init = gv100_fault_init,
	.fini = gv100_fault_fini,
	.पूर्णांकr = gv100_fault_पूर्णांकr,
	.buffer.nr = 2,
	.buffer.entry_size = 32,
	.buffer.info = gv100_fault_buffer_info,
	.buffer.pin = gp100_fault_buffer_pin,
	.buffer.init = gv100_fault_buffer_init,
	.buffer.fini = gv100_fault_buffer_fini,
	.buffer.पूर्णांकr = gv100_fault_buffer_पूर्णांकr,
	/*TODO: Figure out how to expose non-replayable fault buffer, which,
	 *      क्रम some reason, is where recoverable CE faults appear...
	 *
	 * 	It's a bit tricky, as both NVKM and SVM will need access to
	 * 	the non-replayable fault buffer.
	 */
	.user = अणु अणु 0, 0, VOLTA_FAULT_BUFFER_A पूर्ण, 1 पूर्ण,
पूर्ण;

पूर्णांक
gv100_fault_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_fault **pfault)
अणु
	वापस nvkm_fault_new_(&gv100_fault, device, type, inst, pfault);
पूर्ण
