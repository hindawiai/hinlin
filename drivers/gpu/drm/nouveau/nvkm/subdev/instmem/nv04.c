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
#घोषणा nv04_insपंचांगem(p) container_of((p), काष्ठा nv04_insपंचांगem, base)
#समावेश "priv.h"

#समावेश <core/ramht.h>

काष्ठा nv04_insपंचांगem अणु
	काष्ठा nvkm_insपंचांगem base;
	काष्ठा nvkm_mm heap;
पूर्ण;

/******************************************************************************
 * insपंचांगem object implementation
 *****************************************************************************/
#घोषणा nv04_instobj(p) container_of((p), काष्ठा nv04_instobj, base.memory)

काष्ठा nv04_instobj अणु
	काष्ठा nvkm_instobj base;
	काष्ठा nv04_insपंचांगem *imem;
	काष्ठा nvkm_mm_node *node;
पूर्ण;

अटल व्योम
nv04_instobj_wr32(काष्ठा nvkm_memory *memory, u64 offset, u32 data)
अणु
	काष्ठा nv04_instobj *iobj = nv04_instobj(memory);
	काष्ठा nvkm_device *device = iobj->imem->base.subdev.device;
	nvkm_wr32(device, 0x700000 + iobj->node->offset + offset, data);
पूर्ण

अटल u32
nv04_instobj_rd32(काष्ठा nvkm_memory *memory, u64 offset)
अणु
	काष्ठा nv04_instobj *iobj = nv04_instobj(memory);
	काष्ठा nvkm_device *device = iobj->imem->base.subdev.device;
	वापस nvkm_rd32(device, 0x700000 + iobj->node->offset + offset);
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_ptrs
nv04_instobj_ptrs = अणु
	.rd32 = nv04_instobj_rd32,
	.wr32 = nv04_instobj_wr32,
पूर्ण;

अटल व्योम
nv04_instobj_release(काष्ठा nvkm_memory *memory)
अणु
पूर्ण

अटल व्योम __iomem *
nv04_instobj_acquire(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv04_instobj *iobj = nv04_instobj(memory);
	काष्ठा nvkm_device *device = iobj->imem->base.subdev.device;
	वापस device->pri + 0x700000 + iobj->node->offset;
पूर्ण

अटल u64
nv04_instobj_size(काष्ठा nvkm_memory *memory)
अणु
	वापस nv04_instobj(memory)->node->length;
पूर्ण

अटल u64
nv04_instobj_addr(काष्ठा nvkm_memory *memory)
अणु
	वापस nv04_instobj(memory)->node->offset;
पूर्ण

अटल क्रमागत nvkm_memory_target
nv04_instobj_target(काष्ठा nvkm_memory *memory)
अणु
	वापस NVKM_MEM_TARGET_INST;
पूर्ण

अटल व्योम *
nv04_instobj_dtor(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv04_instobj *iobj = nv04_instobj(memory);
	mutex_lock(&iobj->imem->base.mutex);
	nvkm_mm_मुक्त(&iobj->imem->heap, &iobj->node);
	mutex_unlock(&iobj->imem->base.mutex);
	nvkm_instobj_dtor(&iobj->imem->base, &iobj->base);
	वापस iobj;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
nv04_instobj_func = अणु
	.dtor = nv04_instobj_dtor,
	.target = nv04_instobj_target,
	.size = nv04_instobj_size,
	.addr = nv04_instobj_addr,
	.acquire = nv04_instobj_acquire,
	.release = nv04_instobj_release,
पूर्ण;

अटल पूर्णांक
nv04_instobj_new(काष्ठा nvkm_insपंचांगem *base, u32 size, u32 align, bool zero,
		 काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nv04_insपंचांगem *imem = nv04_insपंचांगem(base);
	काष्ठा nv04_instobj *iobj;
	पूर्णांक ret;

	अगर (!(iobj = kzalloc(माप(*iobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pmemory = &iobj->base.memory;

	nvkm_instobj_ctor(&nv04_instobj_func, &imem->base, &iobj->base);
	iobj->base.memory.ptrs = &nv04_instobj_ptrs;
	iobj->imem = imem;

	mutex_lock(&imem->base.mutex);
	ret = nvkm_mm_head(&imem->heap, 0, 1, size, size, align ? align : 1, &iobj->node);
	mutex_unlock(&imem->base.mutex);
	वापस ret;
पूर्ण

/******************************************************************************
 * insपंचांगem subdev implementation
 *****************************************************************************/

अटल u32
nv04_insपंचांगem_rd32(काष्ठा nvkm_insपंचांगem *imem, u32 addr)
अणु
	वापस nvkm_rd32(imem->subdev.device, 0x700000 + addr);
पूर्ण

अटल व्योम
nv04_insपंचांगem_wr32(काष्ठा nvkm_insपंचांगem *imem, u32 addr, u32 data)
अणु
	nvkm_wr32(imem->subdev.device, 0x700000 + addr, data);
पूर्ण

अटल पूर्णांक
nv04_insपंचांगem_oneinit(काष्ठा nvkm_insपंचांगem *base)
अणु
	काष्ठा nv04_insपंचांगem *imem = nv04_insपंचांगem(base);
	काष्ठा nvkm_device *device = imem->base.subdev.device;
	पूर्णांक ret;

	/* PRAMIN aperture maps over the end of VRAM, reserve it */
	imem->base.reserved = 512 * 1024;

	ret = nvkm_mm_init(&imem->heap, 0, 0, imem->base.reserved, 1);
	अगर (ret)
		वापस ret;

	/* 0x00000-0x10000: reserve क्रम probable vbios image */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x10000, 0, false,
			      &imem->base.vbios);
	अगर (ret)
		वापस ret;

	/* 0x10000-0x18000: reserve क्रम RAMHT */
	ret = nvkm_ramht_new(device, 0x08000, 0, शून्य, &imem->base.ramht);
	अगर (ret)
		वापस ret;

	/* 0x18000-0x18800: reserve क्रम RAMFC (enough क्रम 32 nv30 channels) */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x00800, 0, true,
			      &imem->base.ramfc);
	अगर (ret)
		वापस ret;

	/* 0x18800-0x18a00: reserve क्रम RAMRO */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x00200, 0, false,
			      &imem->base.ramro);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम *
nv04_insपंचांगem_dtor(काष्ठा nvkm_insपंचांगem *base)
अणु
	काष्ठा nv04_insपंचांगem *imem = nv04_insपंचांगem(base);
	nvkm_memory_unref(&imem->base.ramfc);
	nvkm_memory_unref(&imem->base.ramro);
	nvkm_ramht_del(&imem->base.ramht);
	nvkm_memory_unref(&imem->base.vbios);
	nvkm_mm_fini(&imem->heap);
	वापस imem;
पूर्ण

अटल स्थिर काष्ठा nvkm_insपंचांगem_func
nv04_insपंचांगem = अणु
	.dtor = nv04_insपंचांगem_dtor,
	.oneinit = nv04_insपंचांगem_oneinit,
	.rd32 = nv04_insपंचांगem_rd32,
	.wr32 = nv04_insपंचांगem_wr32,
	.memory_new = nv04_instobj_new,
	.zero = false,
पूर्ण;

पूर्णांक
nv04_insपंचांगem_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_insपंचांगem **pimem)
अणु
	काष्ठा nv04_insपंचांगem *imem;

	अगर (!(imem = kzalloc(माप(*imem), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_insपंचांगem_ctor(&nv04_insपंचांगem, device, type, inst, &imem->base);
	*pimem = &imem->base;
	वापस 0;
पूर्ण
