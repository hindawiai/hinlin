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
#घोषणा nv50_dmaobj(p) container_of((p), काष्ठा nv50_dmaobj, base)
#समावेश "user.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>

#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/unpack.h>

काष्ठा nv50_dmaobj अणु
	काष्ठा nvkm_dmaobj base;
	u32 flags0;
	u32 flags5;
पूर्ण;

अटल पूर्णांक
nv50_dmaobj_bind(काष्ठा nvkm_dmaobj *base, काष्ठा nvkm_gpuobj *parent,
		 पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nv50_dmaobj *dmaobj = nv50_dmaobj(base);
	काष्ठा nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	पूर्णांक ret;

	ret = nvkm_gpuobj_new(device, 24, align, false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0);
		nvkm_wo32(*pgpuobj, 0x04, lower_32_bits(dmaobj->base.limit));
		nvkm_wo32(*pgpuobj, 0x08, lower_32_bits(dmaobj->base.start));
		nvkm_wo32(*pgpuobj, 0x0c, upper_32_bits(dmaobj->base.limit) << 24 |
					  upper_32_bits(dmaobj->base.start));
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x14, dmaobj->flags5);
		nvkm_करोne(*pgpuobj);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_dmaobj_func
nv50_dmaobj_func = अणु
	.bind = nv50_dmaobj_bind,
पूर्ण;

पूर्णांक
nv50_dmaobj_new(काष्ठा nvkm_dma *dma, स्थिर काष्ठा nvkm_oclass *oclass,
		व्योम *data, u32 size, काष्ठा nvkm_dmaobj **pdmaobj)
अणु
	जोड़ अणु
		काष्ठा nv50_dma_v0 v0;
	पूर्ण *args;
	काष्ठा nvkm_object *parent = oclass->parent;
	काष्ठा nv50_dmaobj *dmaobj;
	u32 user, part, comp, kind;
	पूर्णांक ret;

	अगर (!(dmaobj = kzalloc(माप(*dmaobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pdmaobj = &dmaobj->base;

	ret = nvkm_dmaobj_ctor(&nv50_dmaobj_func, dma, oclass,
			       &data, &size, &dmaobj->base);
	अगर (ret)
		वापस ret;

	ret  = -ENOSYS;
	args = data;

	nvअगर_ioctl(parent, "create nv50 dma size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create nv50 dma vers %d priv %d part %d "
				   "comp %d kind %02x\n", args->v0.version,
			   args->v0.priv, args->v0.part, args->v0.comp,
			   args->v0.kind);
		user = args->v0.priv;
		part = args->v0.part;
		comp = args->v0.comp;
		kind = args->v0.kind;
	पूर्ण अन्यथा
	अगर (size == 0) अणु
		अगर (dmaobj->base.target != NV_MEM_TARGET_VM) अणु
			user = NV50_DMA_V0_PRIV_US;
			part = NV50_DMA_V0_PART_256;
			comp = NV50_DMA_V0_COMP_NONE;
			kind = NV50_DMA_V0_KIND_PITCH;
		पूर्ण अन्यथा अणु
			user = NV50_DMA_V0_PRIV_VM;
			part = NV50_DMA_V0_PART_VM;
			comp = NV50_DMA_V0_COMP_VM;
			kind = NV50_DMA_V0_KIND_VM;
		पूर्ण
	पूर्ण अन्यथा
		वापस ret;

	अगर (user > 2 || part > 2 || comp > 3 || kind > 0x7f)
		वापस -EINVAL;
	dmaobj->flags0 = (comp << 29) | (kind << 22) | (user << 20) |
			 oclass->base.oclass;
	dmaobj->flags5 = (part << 16);

	चयन (dmaobj->base.target) अणु
	हाल NV_MEM_TARGET_VM:
		dmaobj->flags0 |= 0x00000000;
		अवरोध;
	हाल NV_MEM_TARGET_VRAM:
		dmaobj->flags0 |= 0x00010000;
		अवरोध;
	हाल NV_MEM_TARGET_PCI:
		dmaobj->flags0 |= 0x00020000;
		अवरोध;
	हाल NV_MEM_TARGET_PCI_NOSNOOP:
		dmaobj->flags0 |= 0x00030000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dmaobj->base.access) अणु
	हाल NV_MEM_ACCESS_VM:
		अवरोध;
	हाल NV_MEM_ACCESS_RO:
		dmaobj->flags0 |= 0x00040000;
		अवरोध;
	हाल NV_MEM_ACCESS_WO:
	हाल NV_MEM_ACCESS_RW:
		dmaobj->flags0 |= 0x00080000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
