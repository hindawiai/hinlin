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
#घोषणा nv40_insपंचांगem(p) container_of((p), काष्ठा nv40_insपंचांगem, base)
#समावेश "priv.h"

#समावेश <core/ramht.h>
#समावेश <engine/gr/nv40.h>

काष्ठा nv40_insपंचांगem अणु
	काष्ठा nvkm_insपंचांगem base;
	काष्ठा nvkm_mm heap;
	व्योम __iomem *iomem;
पूर्ण;

/******************************************************************************
 * insपंचांगem object implementation
 *****************************************************************************/
#घोषणा nv40_instobj(p) container_of((p), काष्ठा nv40_instobj, base.memory)

काष्ठा nv40_instobj अणु
	काष्ठा nvkm_instobj base;
	काष्ठा nv40_insपंचांगem *imem;
	काष्ठा nvkm_mm_node *node;
पूर्ण;

अटल व्योम
nv40_instobj_wr32(काष्ठा nvkm_memory *memory, u64 offset, u32 data)
अणु
	काष्ठा nv40_instobj *iobj = nv40_instobj(memory);
	ioग_लिखो32_native(data, iobj->imem->iomem + iobj->node->offset + offset);
पूर्ण

अटल u32
nv40_instobj_rd32(काष्ठा nvkm_memory *memory, u64 offset)
अणु
	काष्ठा nv40_instobj *iobj = nv40_instobj(memory);
	वापस ioपढ़ो32_native(iobj->imem->iomem + iobj->node->offset + offset);
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_ptrs
nv40_instobj_ptrs = अणु
	.rd32 = nv40_instobj_rd32,
	.wr32 = nv40_instobj_wr32,
पूर्ण;

अटल व्योम
nv40_instobj_release(काष्ठा nvkm_memory *memory)
अणु
	wmb();
पूर्ण

अटल व्योम __iomem *
nv40_instobj_acquire(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv40_instobj *iobj = nv40_instobj(memory);
	वापस iobj->imem->iomem + iobj->node->offset;
पूर्ण

अटल u64
nv40_instobj_size(काष्ठा nvkm_memory *memory)
अणु
	वापस nv40_instobj(memory)->node->length;
पूर्ण

अटल u64
nv40_instobj_addr(काष्ठा nvkm_memory *memory)
अणु
	वापस nv40_instobj(memory)->node->offset;
पूर्ण

अटल क्रमागत nvkm_memory_target
nv40_instobj_target(काष्ठा nvkm_memory *memory)
अणु
	वापस NVKM_MEM_TARGET_INST;
पूर्ण

अटल व्योम *
nv40_instobj_dtor(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nv40_instobj *iobj = nv40_instobj(memory);
	mutex_lock(&iobj->imem->base.mutex);
	nvkm_mm_मुक्त(&iobj->imem->heap, &iobj->node);
	mutex_unlock(&iobj->imem->base.mutex);
	nvkm_instobj_dtor(&iobj->imem->base, &iobj->base);
	वापस iobj;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
nv40_instobj_func = अणु
	.dtor = nv40_instobj_dtor,
	.target = nv40_instobj_target,
	.size = nv40_instobj_size,
	.addr = nv40_instobj_addr,
	.acquire = nv40_instobj_acquire,
	.release = nv40_instobj_release,
पूर्ण;

अटल पूर्णांक
nv40_instobj_new(काष्ठा nvkm_insपंचांगem *base, u32 size, u32 align, bool zero,
		 काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nv40_insपंचांगem *imem = nv40_insपंचांगem(base);
	काष्ठा nv40_instobj *iobj;
	पूर्णांक ret;

	अगर (!(iobj = kzalloc(माप(*iobj), GFP_KERNEL)))
		वापस -ENOMEM;
	*pmemory = &iobj->base.memory;

	nvkm_instobj_ctor(&nv40_instobj_func, &imem->base, &iobj->base);
	iobj->base.memory.ptrs = &nv40_instobj_ptrs;
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
nv40_insपंचांगem_rd32(काष्ठा nvkm_insपंचांगem *base, u32 addr)
अणु
	वापस ioपढ़ो32_native(nv40_insपंचांगem(base)->iomem + addr);
पूर्ण

अटल व्योम
nv40_insपंचांगem_wr32(काष्ठा nvkm_insपंचांगem *base, u32 addr, u32 data)
अणु
	ioग_लिखो32_native(data, nv40_insपंचांगem(base)->iomem + addr);
पूर्ण

अटल पूर्णांक
nv40_insपंचांगem_oneinit(काष्ठा nvkm_insपंचांगem *base)
अणु
	काष्ठा nv40_insपंचांगem *imem = nv40_insपंचांगem(base);
	काष्ठा nvkm_device *device = imem->base.subdev.device;
	पूर्णांक ret, vs;

	/* PRAMIN aperture maps over the end of vram, reserve enough space
	 * to fit graphics contexts क्रम every channel, the magics come
	 * from engine/gr/nv40.c
	 */
	vs = hweight8((nvkm_rd32(device, 0x001540) & 0x0000ff00) >> 8);
	अगर      (device->chipset == 0x40) imem->base.reserved = 0x6aa0 * vs;
	अन्यथा अगर (device->chipset  < 0x43) imem->base.reserved = 0x4f00 * vs;
	अन्यथा अगर (nv44_gr_class(device))   imem->base.reserved = 0x4980 * vs;
	अन्यथा				  imem->base.reserved = 0x4a40 * vs;
	imem->base.reserved += 16 * 1024;
	imem->base.reserved *= 32;		/* per-channel */
	imem->base.reserved += 512 * 1024;	/* pci(e)gart table */
	imem->base.reserved += 512 * 1024;	/* object storage */
	imem->base.reserved = round_up(imem->base.reserved, 4096);

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

	/* 0x18000-0x18200: reserve क्रम RAMRO
	 * 0x18200-0x20000: padding
	 */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x08000, 0, false,
			      &imem->base.ramro);
	अगर (ret)
		वापस ret;

	/* 0x20000-0x21000: reserve क्रम RAMFC
	 * 0x21000-0x40000: padding and some unknown crap
	 */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x20000, 0, true,
			      &imem->base.ramfc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम *
nv40_insपंचांगem_dtor(काष्ठा nvkm_insपंचांगem *base)
अणु
	काष्ठा nv40_insपंचांगem *imem = nv40_insपंचांगem(base);
	nvkm_memory_unref(&imem->base.ramfc);
	nvkm_memory_unref(&imem->base.ramro);
	nvkm_ramht_del(&imem->base.ramht);
	nvkm_memory_unref(&imem->base.vbios);
	nvkm_mm_fini(&imem->heap);
	अगर (imem->iomem)
		iounmap(imem->iomem);
	वापस imem;
पूर्ण

अटल स्थिर काष्ठा nvkm_insपंचांगem_func
nv40_insपंचांगem = अणु
	.dtor = nv40_insपंचांगem_dtor,
	.oneinit = nv40_insपंचांगem_oneinit,
	.rd32 = nv40_insपंचांगem_rd32,
	.wr32 = nv40_insपंचांगem_wr32,
	.memory_new = nv40_instobj_new,
	.zero = false,
पूर्ण;

पूर्णांक
nv40_insपंचांगem_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 काष्ठा nvkm_insपंचांगem **pimem)
अणु
	काष्ठा nv40_insपंचांगem *imem;
	पूर्णांक bar;

	अगर (!(imem = kzalloc(माप(*imem), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_insपंचांगem_ctor(&nv40_insपंचांगem, device, type, inst, &imem->base);
	*pimem = &imem->base;

	/* map bar */
	अगर (device->func->resource_size(device, 2))
		bar = 2;
	अन्यथा
		bar = 3;

	imem->iomem = ioremap_wc(device->func->resource_addr(device, bar),
				 device->func->resource_size(device, bar));
	अगर (!imem->iomem) अणु
		nvkm_error(&imem->base.subdev, "unable to map PRAMIN BAR\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
