<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#घोषणा nv04_dmaobj(p) container_of((p), काष्ठा nv04_dmaobj, base)
#समावेश "user.h"

#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mmu/vmm.h>

#समावेश <nvअगर/class.h>

काष्ठा nv04_dmaobj अणु
	काष्ठा nvkm_dmaobj base;
	bool clone;
	u32 flags0;
	u32 flags2;
पूर्ण;

अटल पूर्णांक
nv04_dmaobj_bind(काष्ठा nvkm_dmaobj *base, काष्ठा nvkm_gpuobj *parent,
		 पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nv04_dmaobj *dmaobj = nv04_dmaobj(base);
	काष्ठा nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	u64 offset = dmaobj->base.start & 0xfffff000;
	u64 adjust = dmaobj->base.start & 0x00000fff;
	u32 length = dmaobj->base.limit - dmaobj->base.start;
	पूर्णांक ret;

	अगर (dmaobj->clone) अणु
		काष्ठा nvkm_memory *pgt =
			device->mmu->vmm->pd->pt[0]->memory;
		अगर (!dmaobj->base.start)
			वापस nvkm_gpuobj_wrap(pgt, pgpuobj);
		nvkm_kmap(pgt);
		offset  = nvkm_ro32(pgt, 8 + (offset >> 10));
		offset &= 0xfffff000;
		nvkm_करोne(pgt);
	पूर्ण

	ret = nvkm_gpuobj_new(device, 16, align, false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0 | (adjust << 20));
		nvkm_wo32(*pgpuobj, 0x04, length);
		nvkm_wo32(*pgpuobj, 0x08, dmaobj->flags2 | offset);
		nvkm_wo32(*pgpuobj, 0x0c, dmaobj->flags2 | offset);
		nvkm_करोne(*pgpuobj);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_dmaobj_func
nv04_dmaobj_func = अणु
	.bind = nv04_dmaobj_bind,
पूर्ण;

पूर्णांक
nv04_dmaobj_new(काष्ठा nvkm_dma *dma, स्थिर काष्ठा nvkm_oclass *oclass,
		व्योम *data, u32 size, काष्ठा nvkm_dmaobj **pdmaobj)
अणु
	काष्ठा nvkm_device *device = dma->engine.subdev.device;
	काष्ठा nv04_dmaobj *dmaobj;
	पूर्णांक ret;

	अगर (!(dmaobj = kzalloc(माप(*dmaobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pdmaobj = &dmaobj->base;

	ret = nvkm_dmaobj_ctor(&nv04_dmaobj_func, dma, oclass,
			       &data, &size, &dmaobj->base);
	अगर (ret)
		वापस ret;

	अगर (dmaobj->base.target == NV_MEM_TARGET_VM) अणु
		अगर (device->mmu->func == &nv04_mmu)
			dmaobj->clone = true;
		dmaobj->base.target = NV_MEM_TARGET_PCI;
		dmaobj->base.access = NV_MEM_ACCESS_RW;
	पूर्ण

	dmaobj->flags0 = oclass->base.oclass;
	चयन (dmaobj->base.target) अणु
	हाल NV_MEM_TARGET_VRAM:
		dmaobj->flags0 |= 0x00003000;
		अवरोध;
	हाल NV_MEM_TARGET_PCI:
		dmaobj->flags0 |= 0x00023000;
		अवरोध;
	हाल NV_MEM_TARGET_PCI_NOSNOOP:
		dmaobj->flags0 |= 0x00033000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dmaobj->base.access) अणु
	हाल NV_MEM_ACCESS_RO:
		dmaobj->flags0 |= 0x00004000;
		अवरोध;
	हाल NV_MEM_ACCESS_WO:
		dmaobj->flags0 |= 0x00008000;
		fallthrough;
	हाल NV_MEM_ACCESS_RW:
		dmaobj->flags2 |= 0x00000002;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
