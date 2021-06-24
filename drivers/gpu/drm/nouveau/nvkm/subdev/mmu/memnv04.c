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
#समावेश "mem.h"

#समावेश <core/memory.h>
#समावेश <subdev/fb.h>

#समावेश <nvअगर/अगर000b.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
nv04_mem_map(काष्ठा nvkm_mmu *mmu, काष्ठा nvkm_memory *memory, व्योम *argv,
	     u32 argc, u64 *paddr, u64 *psize, काष्ठा nvkm_vma **pvma)
अणु
	जोड़ अणु
		काष्ठा nv04_mem_map_vn vn;
	पूर्ण *args = argv;
	काष्ठा nvkm_device *device = mmu->subdev.device;
	स्थिर u64 addr = nvkm_memory_addr(memory);
	पूर्णांक ret = -ENOSYS;

	अगर ((ret = nvअगर_unvers(ret, &argv, &argc, args->vn)))
		वापस ret;

	*paddr = device->func->resource_addr(device, 1) + addr;
	*psize = nvkm_memory_size(memory);
	*pvma = ERR_PTR(-ENODEV);
	वापस 0;
पूर्ण

पूर्णांक
nv04_mem_new(काष्ठा nvkm_mmu *mmu, पूर्णांक type, u8 page, u64 size,
	     व्योम *argv, u32 argc, काष्ठा nvkm_memory **pmemory)
अणु
	जोड़ अणु
		काष्ठा nv04_mem_vn vn;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;

	अगर ((ret = nvअगर_unvers(ret, &argv, &argc, args->vn)))
		वापस ret;

	अगर (mmu->type[type].type & NVKM_MEM_MAPPABLE)
		type = NVKM_RAM_MM_NORMAL;
	अन्यथा
		type = NVKM_RAM_MM_NOMAP;

	वापस nvkm_ram_get(mmu->subdev.device, type, 0x01, page,
			    size, true, false, pmemory);
पूर्ण
