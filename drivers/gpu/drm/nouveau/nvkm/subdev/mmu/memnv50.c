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
#समावेश <subdev/bar.h>
#समावेश <subdev/fb.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर500b.h>
#समावेश <nvअगर/अगर500d.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
nv50_mem_map(काष्ठा nvkm_mmu *mmu, काष्ठा nvkm_memory *memory, व्योम *argv,
	     u32 argc, u64 *paddr, u64 *psize, काष्ठा nvkm_vma **pvma)
अणु
	काष्ठा nv50_vmm_map_v0 uvmm = अणुपूर्ण;
	जोड़ अणु
		काष्ठा nv50_mem_map_vn vn;
		काष्ठा nv50_mem_map_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_device *device = mmu->subdev.device;
	काष्ठा nvkm_vmm *bar = nvkm_bar_bar1_vmm(device);
	u64 size = nvkm_memory_size(memory);
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		uvmm.ro   = args->v0.ro;
		uvmm.kind = args->v0.kind;
		uvmm.comp = args->v0.comp;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
	पूर्ण अन्यथा
		वापस ret;

	ret = nvkm_vmm_get(bar, 12, size, pvma);
	अगर (ret)
		वापस ret;

	*paddr = device->func->resource_addr(device, 1) + (*pvma)->addr;
	*psize = (*pvma)->size;
	वापस nvkm_memory_map(memory, 0, bar, *pvma, &uvmm, माप(uvmm));
पूर्ण

पूर्णांक
nv50_mem_new(काष्ठा nvkm_mmu *mmu, पूर्णांक type, u8 page, u64 size,
	     व्योम *argv, u32 argc, काष्ठा nvkm_memory **pmemory)
अणु
	जोड़ अणु
		काष्ठा nv50_mem_vn vn;
		काष्ठा nv50_mem_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	bool contig;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		type   = args->v0.bankswz ? 0x02 : 0x01;
		contig = args->v0.contig;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		type   = 0x01;
		contig = false;
	पूर्ण अन्यथा
		वापस -ENOSYS;

	वापस nvkm_ram_get(mmu->subdev.device, NVKM_RAM_MM_NORMAL, type,
			    page, size, contig, false, pmemory);
पूर्ण
