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
#घोषणा gv100_dmaobj(p) container_of((p), काष्ठा gv100_dmaobj, base)
#समावेश "user.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>

#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/unpack.h>

काष्ठा gv100_dmaobj अणु
	काष्ठा nvkm_dmaobj base;
	u32 flags0;
पूर्ण;

अटल पूर्णांक
gv100_dmaobj_bind(काष्ठा nvkm_dmaobj *base, काष्ठा nvkm_gpuobj *parent,
		  पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा gv100_dmaobj *dmaobj = gv100_dmaobj(base);
	काष्ठा nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	u64 start = dmaobj->base.start >> 8;
	u64 limit = dmaobj->base.limit >> 8;
	पूर्णांक ret;

	ret = nvkm_gpuobj_new(device, 24, align, false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->flags0);
		nvkm_wo32(*pgpuobj, 0x04, lower_32_bits(start));
		nvkm_wo32(*pgpuobj, 0x08, upper_32_bits(start));
		nvkm_wo32(*pgpuobj, 0x0c, lower_32_bits(limit));
		nvkm_wo32(*pgpuobj, 0x10, upper_32_bits(limit));
		nvkm_करोne(*pgpuobj);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_dmaobj_func
gv100_dmaobj_func = अणु
	.bind = gv100_dmaobj_bind,
पूर्ण;

पूर्णांक
gv100_dmaobj_new(काष्ठा nvkm_dma *dma, स्थिर काष्ठा nvkm_oclass *oclass,
		 व्योम *data, u32 size, काष्ठा nvkm_dmaobj **pdmaobj)
अणु
	जोड़ अणु
		काष्ठा gf119_dma_v0 v0;
	पूर्ण *args;
	काष्ठा nvkm_object *parent = oclass->parent;
	काष्ठा gv100_dmaobj *dmaobj;
	u32 kind, page;
	पूर्णांक ret;

	अगर (!(dmaobj = kzalloc(माप(*dmaobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pdmaobj = &dmaobj->base;

	ret = nvkm_dmaobj_ctor(&gv100_dmaobj_func, dma, oclass,
			       &data, &size, &dmaobj->base);
	अगर (ret)
		वापस ret;

	ret  = -ENOSYS;
	args = data;

	nvअगर_ioctl(parent, "create gv100 dma size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent,
			   "create gv100 dma vers %d page %d kind %02x\n",
			   args->v0.version, args->v0.page, args->v0.kind);
		kind = args->v0.kind != 0;
		page = args->v0.page != 0;
	पूर्ण अन्यथा
	अगर (size == 0) अणु
		kind = 0;
		page = GF119_DMA_V0_PAGE_SP;
	पूर्ण अन्यथा
		वापस ret;

	अगर (kind)
		dmaobj->flags0 |= 0x00100000;
	अगर (page)
		dmaobj->flags0 |= 0x00000040;
	dmaobj->flags0 |= 0x00000004; /* rw */

	चयन (dmaobj->base.target) अणु
	हाल NV_MEM_TARGET_VRAM       : dmaobj->flags0 |= 0x00000001; अवरोध;
	हाल NV_MEM_TARGET_PCI        : dmaobj->flags0 |= 0x00000002; अवरोध;
	हाल NV_MEM_TARGET_PCI_NOSNOOP: dmaobj->flags0 |= 0x00000003; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
