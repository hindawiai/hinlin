<शैली गुरु>
/*
 * Copyright 2017 Red Hat Inc.
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
#घोषणा nvkm_mem(p) container_of((p), काष्ठा nvkm_mem, memory)
#समावेश "mem.h"

#समावेश <core/memory.h>

#समावेश <nvअगर/अगर000a.h>
#समावेश <nvअगर/unpack.h>

काष्ठा nvkm_mem अणु
	काष्ठा nvkm_memory memory;
	क्रमागत nvkm_memory_target target;
	काष्ठा nvkm_mmu *mmu;
	u64 pages;
	काष्ठा page **mem;
	जोड़ अणु
		काष्ठा scatterlist *sgl;
		dma_addr_t *dma;
	पूर्ण;
पूर्ण;

अटल क्रमागत nvkm_memory_target
nvkm_mem_target(काष्ठा nvkm_memory *memory)
अणु
	वापस nvkm_mem(memory)->target;
पूर्ण

अटल u8
nvkm_mem_page(काष्ठा nvkm_memory *memory)
अणु
	वापस PAGE_SHIFT;
पूर्ण

अटल u64
nvkm_mem_addr(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nvkm_mem *mem = nvkm_mem(memory);
	अगर (mem->pages == 1 && mem->mem)
		वापस mem->dma[0];
	वापस ~0ULL;
पूर्ण

अटल u64
nvkm_mem_size(काष्ठा nvkm_memory *memory)
अणु
	वापस nvkm_mem(memory)->pages << PAGE_SHIFT;
पूर्ण

अटल पूर्णांक
nvkm_mem_map_dma(काष्ठा nvkm_memory *memory, u64 offset, काष्ठा nvkm_vmm *vmm,
		 काष्ठा nvkm_vma *vma, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_mem *mem = nvkm_mem(memory);
	काष्ठा nvkm_vmm_map map = अणु
		.memory = &mem->memory,
		.offset = offset,
		.dma = mem->dma,
	पूर्ण;
	वापस nvkm_vmm_map(vmm, vma, argv, argc, &map);
पूर्ण

अटल व्योम *
nvkm_mem_dtor(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nvkm_mem *mem = nvkm_mem(memory);
	अगर (mem->mem) अणु
		जबतक (mem->pages--) अणु
			dma_unmap_page(mem->mmu->subdev.device->dev,
				       mem->dma[mem->pages], PAGE_SIZE,
				       DMA_BIसूचीECTIONAL);
			__मुक्त_page(mem->mem[mem->pages]);
		पूर्ण
		kvमुक्त(mem->dma);
		kvमुक्त(mem->mem);
	पूर्ण
	वापस mem;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
nvkm_mem_dma = अणु
	.dtor = nvkm_mem_dtor,
	.target = nvkm_mem_target,
	.page = nvkm_mem_page,
	.addr = nvkm_mem_addr,
	.size = nvkm_mem_size,
	.map = nvkm_mem_map_dma,
पूर्ण;

अटल पूर्णांक
nvkm_mem_map_sgl(काष्ठा nvkm_memory *memory, u64 offset, काष्ठा nvkm_vmm *vmm,
		 काष्ठा nvkm_vma *vma, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_mem *mem = nvkm_mem(memory);
	काष्ठा nvkm_vmm_map map = अणु
		.memory = &mem->memory,
		.offset = offset,
		.sgl = mem->sgl,
	पूर्ण;
	वापस nvkm_vmm_map(vmm, vma, argv, argc, &map);
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
nvkm_mem_sgl = अणु
	.dtor = nvkm_mem_dtor,
	.target = nvkm_mem_target,
	.page = nvkm_mem_page,
	.addr = nvkm_mem_addr,
	.size = nvkm_mem_size,
	.map = nvkm_mem_map_sgl,
पूर्ण;

पूर्णांक
nvkm_mem_map_host(काष्ठा nvkm_memory *memory, व्योम **pmap)
अणु
	काष्ठा nvkm_mem *mem = nvkm_mem(memory);
	अगर (mem->mem) अणु
		*pmap = vmap(mem->mem, mem->pages, VM_MAP, PAGE_KERNEL);
		वापस *pmap ? 0 : -EFAULT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_mem_new_host(काष्ठा nvkm_mmu *mmu, पूर्णांक type, u8 page, u64 size,
		  व्योम *argv, u32 argc, काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा device *dev = mmu->subdev.device->dev;
	जोड़ अणु
		काष्ठा nvअगर_mem_ram_vn vn;
		काष्ठा nvअगर_mem_ram_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	क्रमागत nvkm_memory_target target;
	काष्ठा nvkm_mem *mem;
	gfp_t gfp = GFP_USER | __GFP_ZERO;

	अगर ( (mmu->type[type].type & NVKM_MEM_COHERENT) &&
	    !(mmu->type[type].type & NVKM_MEM_UNCACHED))
		target = NVKM_MEM_TARGET_HOST;
	अन्यथा
		target = NVKM_MEM_TARGET_NCOH;

	अगर (page != PAGE_SHIFT)
		वापस -EINVAL;

	अगर (!(mem = kzalloc(माप(*mem), GFP_KERNEL)))
		वापस -ENOMEM;
	mem->target = target;
	mem->mmu = mmu;
	*pmemory = &mem->memory;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		अगर (args->v0.dma) अणु
			nvkm_memory_ctor(&nvkm_mem_dma, &mem->memory);
			mem->dma = args->v0.dma;
		पूर्ण अन्यथा अणु
			nvkm_memory_ctor(&nvkm_mem_sgl, &mem->memory);
			mem->sgl = args->v0.sgl;
		पूर्ण

		अगर (!IS_ALIGNED(size, PAGE_SIZE))
			वापस -EINVAL;
		mem->pages = size >> PAGE_SHIFT;
		वापस 0;
	पूर्ण अन्यथा
	अगर ( (ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		kमुक्त(mem);
		वापस ret;
	पूर्ण

	nvkm_memory_ctor(&nvkm_mem_dma, &mem->memory);
	size = ALIGN(size, PAGE_SIZE) >> PAGE_SHIFT;

	अगर (!(mem->mem = kvदो_स्मृति_array(size, माप(*mem->mem), GFP_KERNEL)))
		वापस -ENOMEM;
	अगर (!(mem->dma = kvदो_स्मृति_array(size, माप(*mem->dma), GFP_KERNEL)))
		वापस -ENOMEM;

	अगर (mmu->dma_bits > 32)
		gfp |= GFP_HIGHUSER;
	अन्यथा
		gfp |= GFP_DMA32;

	क्रम (mem->pages = 0; size; size--, mem->pages++) अणु
		काष्ठा page *p = alloc_page(gfp);
		अगर (!p)
			वापस -ENOMEM;

		mem->dma[mem->pages] = dma_map_page(mmu->subdev.device->dev,
						    p, 0, PAGE_SIZE,
						    DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, mem->dma[mem->pages])) अणु
			__मुक्त_page(p);
			वापस -ENOMEM;
		पूर्ण

		mem->mem[mem->pages] = p;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvkm_mem_new_type(काष्ठा nvkm_mmu *mmu, पूर्णांक type, u8 page, u64 size,
		  व्योम *argv, u32 argc, काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nvkm_memory *memory = शून्य;
	पूर्णांक ret;

	अगर (mmu->type[type].type & NVKM_MEM_VRAM) अणु
		ret = mmu->func->mem.vram(mmu, type, page, size,
					  argv, argc, &memory);
	पूर्ण अन्यथा अणु
		ret = nvkm_mem_new_host(mmu, type, page, size,
					argv, argc, &memory);
	पूर्ण

	अगर (ret)
		nvkm_memory_unref(&memory);
	*pmemory = memory;
	वापस ret;
पूर्ण
