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
#समावेश <core/gpuobj.h>
#समावेश <core/engine.h>

#समावेश <subdev/insपंचांगem.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/mmu.h>

/* fast-path, where backend is able to provide direct poपूर्णांकer to memory */
अटल u32
nvkm_gpuobj_rd32_fast(काष्ठा nvkm_gpuobj *gpuobj, u32 offset)
अणु
	वापस ioपढ़ो32_native(gpuobj->map + offset);
पूर्ण

अटल व्योम
nvkm_gpuobj_wr32_fast(काष्ठा nvkm_gpuobj *gpuobj, u32 offset, u32 data)
अणु
	ioग_लिखो32_native(data, gpuobj->map + offset);
पूर्ण

/* accessor functions क्रम gpuobjs allocated directly from insपंचांगem */
अटल पूर्णांक
nvkm_gpuobj_heap_map(काष्ठा nvkm_gpuobj *gpuobj, u64 offset,
		     काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma,
		     व्योम *argv, u32 argc)
अणु
	वापस nvkm_memory_map(gpuobj->memory, offset, vmm, vma, argv, argc);
पूर्ण

अटल u32
nvkm_gpuobj_heap_rd32(काष्ठा nvkm_gpuobj *gpuobj, u32 offset)
अणु
	वापस nvkm_ro32(gpuobj->memory, offset);
पूर्ण

अटल व्योम
nvkm_gpuobj_heap_wr32(काष्ठा nvkm_gpuobj *gpuobj, u32 offset, u32 data)
अणु
	nvkm_wo32(gpuobj->memory, offset, data);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpuobj_func nvkm_gpuobj_heap;
अटल व्योम
nvkm_gpuobj_heap_release(काष्ठा nvkm_gpuobj *gpuobj)
अणु
	gpuobj->func = &nvkm_gpuobj_heap;
	nvkm_करोne(gpuobj->memory);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpuobj_func
nvkm_gpuobj_heap_fast = अणु
	.release = nvkm_gpuobj_heap_release,
	.rd32 = nvkm_gpuobj_rd32_fast,
	.wr32 = nvkm_gpuobj_wr32_fast,
	.map = nvkm_gpuobj_heap_map,
पूर्ण;

अटल स्थिर काष्ठा nvkm_gpuobj_func
nvkm_gpuobj_heap_slow = अणु
	.release = nvkm_gpuobj_heap_release,
	.rd32 = nvkm_gpuobj_heap_rd32,
	.wr32 = nvkm_gpuobj_heap_wr32,
	.map = nvkm_gpuobj_heap_map,
पूर्ण;

अटल व्योम *
nvkm_gpuobj_heap_acquire(काष्ठा nvkm_gpuobj *gpuobj)
अणु
	gpuobj->map = nvkm_kmap(gpuobj->memory);
	अगर (likely(gpuobj->map))
		gpuobj->func = &nvkm_gpuobj_heap_fast;
	अन्यथा
		gpuobj->func = &nvkm_gpuobj_heap_slow;
	वापस gpuobj->map;
पूर्ण

अटल स्थिर काष्ठा nvkm_gpuobj_func
nvkm_gpuobj_heap = अणु
	.acquire = nvkm_gpuobj_heap_acquire,
	.map = nvkm_gpuobj_heap_map,
पूर्ण;

/* accessor functions क्रम gpuobjs sub-allocated from a parent gpuobj */
अटल पूर्णांक
nvkm_gpuobj_map(काष्ठा nvkm_gpuobj *gpuobj, u64 offset,
		काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vma *vma,
		व्योम *argv, u32 argc)
अणु
	वापस nvkm_memory_map(gpuobj->parent, gpuobj->node->offset + offset,
			       vmm, vma, argv, argc);
पूर्ण

अटल u32
nvkm_gpuobj_rd32(काष्ठा nvkm_gpuobj *gpuobj, u32 offset)
अणु
	वापस nvkm_ro32(gpuobj->parent, gpuobj->node->offset + offset);
पूर्ण

अटल व्योम
nvkm_gpuobj_wr32(काष्ठा nvkm_gpuobj *gpuobj, u32 offset, u32 data)
अणु
	nvkm_wo32(gpuobj->parent, gpuobj->node->offset + offset, data);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpuobj_func nvkm_gpuobj_func;
अटल व्योम
nvkm_gpuobj_release(काष्ठा nvkm_gpuobj *gpuobj)
अणु
	gpuobj->func = &nvkm_gpuobj_func;
	nvkm_करोne(gpuobj->parent);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpuobj_func
nvkm_gpuobj_fast = अणु
	.release = nvkm_gpuobj_release,
	.rd32 = nvkm_gpuobj_rd32_fast,
	.wr32 = nvkm_gpuobj_wr32_fast,
	.map = nvkm_gpuobj_map,
पूर्ण;

अटल स्थिर काष्ठा nvkm_gpuobj_func
nvkm_gpuobj_slow = अणु
	.release = nvkm_gpuobj_release,
	.rd32 = nvkm_gpuobj_rd32,
	.wr32 = nvkm_gpuobj_wr32,
	.map = nvkm_gpuobj_map,
पूर्ण;

अटल व्योम *
nvkm_gpuobj_acquire(काष्ठा nvkm_gpuobj *gpuobj)
अणु
	gpuobj->map = nvkm_kmap(gpuobj->parent);
	अगर (likely(gpuobj->map)) अणु
		gpuobj->map  = (u8 *)gpuobj->map + gpuobj->node->offset;
		gpuobj->func = &nvkm_gpuobj_fast;
	पूर्ण अन्यथा अणु
		gpuobj->func = &nvkm_gpuobj_slow;
	पूर्ण
	वापस gpuobj->map;
पूर्ण

अटल स्थिर काष्ठा nvkm_gpuobj_func
nvkm_gpuobj_func = अणु
	.acquire = nvkm_gpuobj_acquire,
	.map = nvkm_gpuobj_map,
पूर्ण;

अटल पूर्णांक
nvkm_gpuobj_ctor(काष्ठा nvkm_device *device, u32 size, पूर्णांक align, bool zero,
		 काष्ठा nvkm_gpuobj *parent, काष्ठा nvkm_gpuobj *gpuobj)
अणु
	u32 offset;
	पूर्णांक ret;

	अगर (parent) अणु
		अगर (align >= 0) अणु
			ret = nvkm_mm_head(&parent->heap, 0, 1, size, size,
					   max(align, 1), &gpuobj->node);
		पूर्ण अन्यथा अणु
			ret = nvkm_mm_tail(&parent->heap, 0, 1, size, size,
					   -align, &gpuobj->node);
		पूर्ण
		अगर (ret)
			वापस ret;

		gpuobj->parent = parent;
		gpuobj->func = &nvkm_gpuobj_func;
		gpuobj->addr = parent->addr + gpuobj->node->offset;
		gpuobj->size = gpuobj->node->length;

		अगर (zero) अणु
			nvkm_kmap(gpuobj);
			क्रम (offset = 0; offset < gpuobj->size; offset += 4)
				nvkm_wo32(gpuobj, offset, 0x00000000);
			nvkm_करोne(gpuobj);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, size,
				      असल(align), zero, &gpuobj->memory);
		अगर (ret)
			वापस ret;

		gpuobj->func = &nvkm_gpuobj_heap;
		gpuobj->addr = nvkm_memory_addr(gpuobj->memory);
		gpuobj->size = nvkm_memory_size(gpuobj->memory);
	पूर्ण

	वापस nvkm_mm_init(&gpuobj->heap, 0, 0, gpuobj->size, 1);
पूर्ण

व्योम
nvkm_gpuobj_del(काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nvkm_gpuobj *gpuobj = *pgpuobj;
	अगर (gpuobj) अणु
		अगर (gpuobj->parent)
			nvkm_mm_मुक्त(&gpuobj->parent->heap, &gpuobj->node);
		nvkm_mm_fini(&gpuobj->heap);
		nvkm_memory_unref(&gpuobj->memory);
		kमुक्त(*pgpuobj);
		*pgpuobj = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_gpuobj_new(काष्ठा nvkm_device *device, u32 size, पूर्णांक align, bool zero,
		काष्ठा nvkm_gpuobj *parent, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nvkm_gpuobj *gpuobj;
	पूर्णांक ret;

	अगर (!(gpuobj = *pgpuobj = kzalloc(माप(*gpuobj), GFP_KERNEL)))
		वापस -ENOMEM;

	ret = nvkm_gpuobj_ctor(device, size, align, zero, parent, gpuobj);
	अगर (ret)
		nvkm_gpuobj_del(pgpuobj);
	वापस ret;
पूर्ण

/* the below is basically only here to support sharing the paged dma object
 * क्रम PCI(E)GART on <=nv4x chipsets, and should *not* be expected to work
 * anywhere अन्यथा.
 */

पूर्णांक
nvkm_gpuobj_wrap(काष्ठा nvkm_memory *memory, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	अगर (!(*pgpuobj = kzalloc(माप(**pgpuobj), GFP_KERNEL)))
		वापस -ENOMEM;

	(*pgpuobj)->addr = nvkm_memory_addr(memory);
	(*pgpuobj)->size = nvkm_memory_size(memory);
	वापस 0;
पूर्ण

व्योम
nvkm_gpuobj_स_नकल_to(काष्ठा nvkm_gpuobj *dst, u32 dstoffset, व्योम *src,
		      u32 length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length; i += 4)
		nvkm_wo32(dst, dstoffset + i, *(u32 *)(src + i));
पूर्ण

व्योम
nvkm_gpuobj_स_नकल_from(व्योम *dst, काष्ठा nvkm_gpuobj *src, u32 srcoffset,
			u32 length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length; i += 4)
		((u32 *)src)[i / 4] = nvkm_ro32(src, srcoffset + i);
पूर्ण
