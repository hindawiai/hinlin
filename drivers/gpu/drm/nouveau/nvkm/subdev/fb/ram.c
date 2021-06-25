<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#घोषणा nvkm_vram(p) container_of((p), काष्ठा nvkm_vram, memory)
#समावेश "ram.h"

#समावेश <core/memory.h>
#समावेश <subdev/mmu.h>

काष्ठा nvkm_vram अणु
	काष्ठा nvkm_memory memory;
	काष्ठा nvkm_ram *ram;
	u8 page;
	काष्ठा nvkm_mm_node *mn;
पूर्ण;

अटल पूर्णांक
nvkm_vram_map(काष्ठा nvkm_memory *memory, u64 offset, काष्ठा nvkm_vmm *vmm,
	      काष्ठा nvkm_vma *vma, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_vram *vram = nvkm_vram(memory);
	काष्ठा nvkm_vmm_map map = अणु
		.memory = &vram->memory,
		.offset = offset,
		.mem = vram->mn,
	पूर्ण;

	वापस nvkm_vmm_map(vmm, vma, argv, argc, &map);
पूर्ण

अटल u64
nvkm_vram_size(काष्ठा nvkm_memory *memory)
अणु
	वापस (u64)nvkm_mm_size(nvkm_vram(memory)->mn) << NVKM_RAM_MM_SHIFT;
पूर्ण

अटल u64
nvkm_vram_addr(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nvkm_vram *vram = nvkm_vram(memory);
	अगर (!nvkm_mm_contiguous(vram->mn))
		वापस ~0ULL;
	वापस (u64)nvkm_mm_addr(vram->mn) << NVKM_RAM_MM_SHIFT;
पूर्ण

अटल u8
nvkm_vram_page(काष्ठा nvkm_memory *memory)
अणु
	वापस nvkm_vram(memory)->page;
पूर्ण

अटल क्रमागत nvkm_memory_target
nvkm_vram_target(काष्ठा nvkm_memory *memory)
अणु
	वापस NVKM_MEM_TARGET_VRAM;
पूर्ण

अटल व्योम *
nvkm_vram_dtor(काष्ठा nvkm_memory *memory)
अणु
	काष्ठा nvkm_vram *vram = nvkm_vram(memory);
	काष्ठा nvkm_mm_node *next = vram->mn;
	काष्ठा nvkm_mm_node *node;
	mutex_lock(&vram->ram->mutex);
	जबतक ((node = next)) अणु
		next = node->next;
		nvkm_mm_मुक्त(&vram->ram->vram, &node);
	पूर्ण
	mutex_unlock(&vram->ram->mutex);
	वापस vram;
पूर्ण

अटल स्थिर काष्ठा nvkm_memory_func
nvkm_vram = अणु
	.dtor = nvkm_vram_dtor,
	.target = nvkm_vram_target,
	.page = nvkm_vram_page,
	.addr = nvkm_vram_addr,
	.size = nvkm_vram_size,
	.map = nvkm_vram_map,
पूर्ण;

पूर्णांक
nvkm_ram_get(काष्ठा nvkm_device *device, u8 heap, u8 type, u8 rpage, u64 size,
	     bool contig, bool back, काष्ठा nvkm_memory **pmemory)
अणु
	काष्ठा nvkm_ram *ram;
	काष्ठा nvkm_mm *mm;
	काष्ठा nvkm_mm_node **node, *r;
	काष्ठा nvkm_vram *vram;
	u8   page = max(rpage, (u8)NVKM_RAM_MM_SHIFT);
	u32 align = (1 << page) >> NVKM_RAM_MM_SHIFT;
	u32   max = ALIGN(size, 1 << page) >> NVKM_RAM_MM_SHIFT;
	u32   min = contig ? max : align;
	पूर्णांक ret;

	अगर (!device->fb || !(ram = device->fb->ram))
		वापस -ENODEV;
	ram = device->fb->ram;
	mm = &ram->vram;

	अगर (!(vram = kzalloc(माप(*vram), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_memory_ctor(&nvkm_vram, &vram->memory);
	vram->ram = ram;
	vram->page = page;
	*pmemory = &vram->memory;

	mutex_lock(&ram->mutex);
	node = &vram->mn;
	करो अणु
		अगर (back)
			ret = nvkm_mm_tail(mm, heap, type, max, min, align, &r);
		अन्यथा
			ret = nvkm_mm_head(mm, heap, type, max, min, align, &r);
		अगर (ret) अणु
			mutex_unlock(&ram->mutex);
			nvkm_memory_unref(pmemory);
			वापस ret;
		पूर्ण

		*node = r;
		node = &r->next;
		max -= r->length;
	पूर्ण जबतक (max);
	mutex_unlock(&ram->mutex);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_ram_init(काष्ठा nvkm_ram *ram)
अणु
	अगर (ram->func->init)
		वापस ram->func->init(ram);
	वापस 0;
पूर्ण

व्योम
nvkm_ram_del(काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_ram *ram = *pram;
	अगर (ram && !WARN_ON(!ram->func)) अणु
		अगर (ram->func->dtor)
			*pram = ram->func->dtor(ram);
		nvkm_mm_fini(&ram->vram);
		mutex_destroy(&ram->mutex);
		kमुक्त(*pram);
		*pram = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_ram_ctor(स्थिर काष्ठा nvkm_ram_func *func, काष्ठा nvkm_fb *fb,
	      क्रमागत nvkm_ram_type type, u64 size, काष्ठा nvkm_ram *ram)
अणु
	अटल स्थिर अक्षर *name[] = अणु
		[NVKM_RAM_TYPE_UNKNOWN] = "of unknown memory type",
		[NVKM_RAM_TYPE_STOLEN ] = "stolen system memory",
		[NVKM_RAM_TYPE_SGRAM  ] = "SGRAM",
		[NVKM_RAM_TYPE_SDRAM  ] = "SDRAM",
		[NVKM_RAM_TYPE_DDR1   ] = "DDR1",
		[NVKM_RAM_TYPE_DDR2   ] = "DDR2",
		[NVKM_RAM_TYPE_DDR3   ] = "DDR3",
		[NVKM_RAM_TYPE_GDDR2  ] = "GDDR2",
		[NVKM_RAM_TYPE_GDDR3  ] = "GDDR3",
		[NVKM_RAM_TYPE_GDDR4  ] = "GDDR4",
		[NVKM_RAM_TYPE_GDDR5  ] = "GDDR5",
		[NVKM_RAM_TYPE_GDDR5X ] = "GDDR5X",
		[NVKM_RAM_TYPE_GDDR6  ] = "GDDR6",
		[NVKM_RAM_TYPE_HBM2   ] = "HBM2",
	पूर्ण;
	काष्ठा nvkm_subdev *subdev = &fb->subdev;
	पूर्णांक ret;

	nvkm_info(subdev, "%d MiB %s\n", (पूर्णांक)(size >> 20), name[type]);
	ram->func = func;
	ram->fb = fb;
	ram->type = type;
	ram->size = size;
	mutex_init(&ram->mutex);

	अगर (!nvkm_mm_initialised(&ram->vram)) अणु
		ret = nvkm_mm_init(&ram->vram, NVKM_RAM_MM_NORMAL, 0,
				   size >> NVKM_RAM_MM_SHIFT, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nvkm_ram_new_(स्थिर काष्ठा nvkm_ram_func *func, काष्ठा nvkm_fb *fb,
	      क्रमागत nvkm_ram_type type, u64 size, काष्ठा nvkm_ram **pram)
अणु
	अगर (!(*pram = kzalloc(माप(**pram), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_ram_ctor(func, fb, type, size, *pram);
पूर्ण
