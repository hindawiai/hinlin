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
#समावेश "user.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/insपंचांगem.h>

#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/unpack.h>

अटल स्थिर काष्ठा nvkm_object_func nvkm_dmaobj_func;
काष्ठा nvkm_dmaobj *
nvkm_dmaobj_search(काष्ठा nvkm_client *client, u64 handle)
अणु
	काष्ठा nvkm_object *object;

	object = nvkm_object_search(client, handle, &nvkm_dmaobj_func);
	अगर (IS_ERR(object))
		वापस (व्योम *)object;

	वापस nvkm_dmaobj(object);
पूर्ण

अटल पूर्णांक
nvkm_dmaobj_bind(काष्ठा nvkm_object *base, काष्ठा nvkm_gpuobj *gpuobj,
		 पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nvkm_dmaobj *dmaobj = nvkm_dmaobj(base);
	वापस dmaobj->func->bind(dmaobj, gpuobj, align, pgpuobj);
पूर्ण

अटल व्योम *
nvkm_dmaobj_dtor(काष्ठा nvkm_object *base)
अणु
	वापस nvkm_dmaobj(base);
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_dmaobj_func = अणु
	.dtor = nvkm_dmaobj_dtor,
	.bind = nvkm_dmaobj_bind,
पूर्ण;

पूर्णांक
nvkm_dmaobj_ctor(स्थिर काष्ठा nvkm_dmaobj_func *func, काष्ठा nvkm_dma *dma,
		 स्थिर काष्ठा nvkm_oclass *oclass, व्योम **pdata, u32 *psize,
		 काष्ठा nvkm_dmaobj *dmaobj)
अणु
	जोड़ अणु
		काष्ठा nv_dma_v0 v0;
	पूर्ण *args = *pdata;
	काष्ठा nvkm_device *device = dma->engine.subdev.device;
	काष्ठा nvkm_client *client = oclass->client;
	काष्ठा nvkm_object *parent = oclass->parent;
	काष्ठा nvkm_insपंचांगem *insपंचांगem = device->imem;
	काष्ठा nvkm_fb *fb = device->fb;
	व्योम *data = *pdata;
	u32 size = *psize;
	पूर्णांक ret = -ENOSYS;

	nvkm_object_ctor(&nvkm_dmaobj_func, oclass, &dmaobj->object);
	dmaobj->func = func;
	dmaobj->dma = dma;

	nvअगर_ioctl(parent, "create dma size %d\n", *psize);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(parent, "create dma vers %d target %d access %d "
				   "start %016llx limit %016llx\n",
			   args->v0.version, args->v0.target, args->v0.access,
			   args->v0.start, args->v0.limit);
		dmaobj->target = args->v0.target;
		dmaobj->access = args->v0.access;
		dmaobj->start  = args->v0.start;
		dmaobj->limit  = args->v0.limit;
	पूर्ण अन्यथा
		वापस ret;

	*pdata = data;
	*psize = size;

	अगर (dmaobj->start > dmaobj->limit)
		वापस -EINVAL;

	चयन (dmaobj->target) अणु
	हाल NV_DMA_V0_TARGET_VM:
		dmaobj->target = NV_MEM_TARGET_VM;
		अवरोध;
	हाल NV_DMA_V0_TARGET_VRAM:
		अगर (!client->super) अणु
			अगर (dmaobj->limit >= fb->ram->size - insपंचांगem->reserved)
				वापस -EACCES;
			अगर (device->card_type >= NV_50)
				वापस -EACCES;
		पूर्ण
		dmaobj->target = NV_MEM_TARGET_VRAM;
		अवरोध;
	हाल NV_DMA_V0_TARGET_PCI:
		अगर (!client->super)
			वापस -EACCES;
		dmaobj->target = NV_MEM_TARGET_PCI;
		अवरोध;
	हाल NV_DMA_V0_TARGET_PCI_US:
	हाल NV_DMA_V0_TARGET_AGP:
		अगर (!client->super)
			वापस -EACCES;
		dmaobj->target = NV_MEM_TARGET_PCI_NOSNOOP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (dmaobj->access) अणु
	हाल NV_DMA_V0_ACCESS_VM:
		dmaobj->access = NV_MEM_ACCESS_VM;
		अवरोध;
	हाल NV_DMA_V0_ACCESS_RD:
		dmaobj->access = NV_MEM_ACCESS_RO;
		अवरोध;
	हाल NV_DMA_V0_ACCESS_WR:
		dmaobj->access = NV_MEM_ACCESS_WO;
		अवरोध;
	हाल NV_DMA_V0_ACCESS_RDWR:
		dmaobj->access = NV_MEM_ACCESS_RW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
