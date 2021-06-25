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
#समावेश "vmm.h"

#समावेश <nvअगर/अगर000d.h>
#समावेश <nvअगर/unpack.h>

अटल अंतरभूत व्योम
nv04_vmm_pgt_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	u32 data = addr | 0x00000003; /* PRESENT, RW. */
	जबतक (ptes--) अणु
		VMM_WO032(pt, vmm, 8 + ptei++ * 4, data);
		data += 0x00001000;
	पूर्ण
पूर्ण

अटल व्योम
nv04_vmm_pgt_sgl(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_SGL(vmm, pt, ptei, ptes, map, nv04_vmm_pgt_pte);
पूर्ण

अटल व्योम
nv04_vmm_pgt_dma(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
#अगर PAGE_SHIFT == 12
	nvkm_kmap(pt->memory);
	जबतक (ptes--)
		VMM_WO032(pt, vmm, 8 + (ptei++ * 4), *map->dma++ | 0x00000003);
	nvkm_करोne(pt->memory);
#अन्यथा
	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, nv04_vmm_pgt_pte);
#पूर्ण_अगर
पूर्ण

अटल व्योम
nv04_vmm_pgt_unmap(काष्ठा nvkm_vmm *vmm,
		   काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	VMM_FO032(pt, vmm, 8 + (ptei * 4), 0, ptes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
nv04_vmm_desc_pgt = अणु
	.unmap = nv04_vmm_pgt_unmap,
	.dma = nv04_vmm_pgt_dma,
	.sgl = nv04_vmm_pgt_sgl,
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
nv04_vmm_desc_12[] = अणु
	अणु PGT, 15, 4, 0x1000, &nv04_vmm_desc_pgt पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
nv04_vmm_valid(काष्ठा nvkm_vmm *vmm, व्योम *argv, u32 argc,
	       काष्ठा nvkm_vmm_map *map)
अणु
	जोड़ अणु
		काष्ठा nv04_vmm_map_vn vn;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	अगर ((ret = nvअगर_unvers(ret, &argv, &argc, args->vn)))
		VMM_DEBUG(vmm, "args");
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
nv04_vmm = अणु
	.valid = nv04_vmm_valid,
	.page = अणु
		अणु 12, &nv04_vmm_desc_12[0], NVKM_VMM_PAGE_HOST पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv04_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *func, काष्ठा nvkm_mmu *mmu,
	      u32 pd_header, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	जोड़ अणु
		काष्ठा nv04_vmm_vn vn;
	पूर्ण *args = argv;
	पूर्णांक ret;

	ret = nvkm_vmm_new_(func, mmu, pd_header, managed, addr, size,
			    key, name, pvmm);
	अगर (ret)
		वापस ret;

	वापस nvअगर_unvers(-ENOSYS, &argv, &argc, args->vn);
पूर्ण

पूर्णांक
nv04_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	     व्योम *argv, u32 argc, काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	     काष्ठा nvkm_vmm **pvmm)
अणु
	काष्ठा nvkm_memory *mem;
	काष्ठा nvkm_vmm *vmm;
	पूर्णांक ret;

	ret = nv04_vmm_new_(&nv04_vmm, mmu, 8, managed, addr, size,
			    argv, argc, key, name, &vmm);
	*pvmm = vmm;
	अगर (ret)
		वापस ret;

	mem = vmm->pd->pt[0]->memory;
	nvkm_kmap(mem);
	nvkm_wo32(mem, 0x00000, 0x0002103d); /* PCI, RW, PT, !LN */
	nvkm_wo32(mem, 0x00004, vmm->limit - 1);
	nvkm_करोne(mem);
	वापस 0;
पूर्ण
