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
#घोषणा gf119_dmaobj(p) container_of((p), काष्ठा gf119_dmaobj, base)
#समावेश "user.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>

#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/unpack.h>

काष्ठा gf119_dmaobj अणु
	काष्ठा nvkm_dmaobj base;
	u32 flags0;
पूर्ण;

अटल पूर्णांक
gf119_dmaobj_bind(काष्ठा nvkm_dmaobj *base, काष्ठा nvkm_gpuobj *parent,
		  पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा gf119_dmaobj *dmaobj = gf119_dmaobj(base);
	काष्ठा nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	पूर्णांक ret;

	ret = nvkm_gpuobj_new(device, 24, align, false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0);
		nvkm_wo32(*pgpuobj, 0x04, dmaobj->base.start >> 8);
		nvkm_wo32(*pgpuobj, 0x08, dmaobj->base.limit >> 8);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x14, 0x00000000);
		nvkm_करोne(*pgpuobj);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_dmaobj_func
gf119_dmaobj_func = अणु
	.bind = gf119_dmaobj_bind,
पूर्ण;

पूर्णांक
gf119_dmaobj_new(काष्ठा nvkm_dma *dma, स्थिर काष्ठा nvkm_oclass *oclass,
		 व्योम *data, u32 size, काष्ठा nvkm_dmaobj **pdmaobj)
अणु
	जोड़ अणु
		काष्ठा gf119_dma_v0 v0;
	पूर्ण *args;
	काष्ठा nvkm_object *parent = oclass->parent;
	काष्ठा gf119_dmaobj *dmaobj;
	u32 kind, page;
	पूर्णांक ret;

	अगर (!(dmaobj = kzalloc(माप(*dmaobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pdmaobj = &dmaobj->base;

	ret = nvkm_dmaobj_ctor(&gf119_dmaobj_func, dma, oclass,
			       &data, &size, &dmaobj->base);
	अगर (ret)
		वापस ret;

	ret  = -ENOSYS;
	args = data;

	nvअगर_ioctl(parent, "create gf119 dma size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent,
			   "create gf100 dma vers %d page %d kind %02x\n",
			   args->v0.version, args->v0.page, args->v0.kind);
		kind = args->v0.kind;
		page = args->v0.page;
	पूर्ण अन्यथा
	अगर (size == 0) अणु
		अगर (dmaobj->base.target != NV_MEM_TARGET_VM) अणु
			kind = GF119_DMA_V0_KIND_PITCH;
			page = GF119_DMA_V0_PAGE_SP;
		पूर्ण अन्यथा अणु
			kind = GF119_DMA_V0_KIND_VM;
			page = GF119_DMA_V0_PAGE_LP;
		पूर्ण
	पूर्ण अन्यथा
		वापस ret;

	अगर (page > 1)
		वापस -EINVAL;
	dmaobj->flags0 = (kind << 20) | (page << 6);

	चयन (dmaobj->base.target) अणु
	हाल NV_MEM_TARGET_VRAM:
		dmaobj->flags0 |= 0x00000009;
		अवरोध;
	हाल NV_MEM_TARGET_VM:
	हाल NV_MEM_TARGET_PCI:
	हाल NV_MEM_TARGET_PCI_NOSNOOP:
		/* XXX: करोn't currently know how to स्थिरruct a real one
		 *      of these.  we only use them to represent pushbufs
		 *      on these chipsets, and the classes that use them
		 *      deal with the target themselves.
		 */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
