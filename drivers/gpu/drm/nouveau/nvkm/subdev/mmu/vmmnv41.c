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

#समावेश <subdev/समयr.h>

अटल व्योम
nv41_vmm_pgt_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	u32 data = (addr >> 7) | 0x00000001; /* VALID. */
	जबतक (ptes--) अणु
		VMM_WO032(pt, vmm, ptei++ * 4, data);
		data += 0x00000020;
	पूर्ण
पूर्ण

अटल व्योम
nv41_vmm_pgt_sgl(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_SGL(vmm, pt, ptei, ptes, map, nv41_vmm_pgt_pte);
पूर्ण

अटल व्योम
nv41_vmm_pgt_dma(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
#अगर PAGE_SHIFT == 12
	nvkm_kmap(pt->memory);
	जबतक (ptes--) अणु
		स्थिर u32 data = (*map->dma++ >> 7) | 0x00000001;
		VMM_WO032(pt, vmm, ptei++ * 4, data);
	पूर्ण
	nvkm_करोne(pt->memory);
#अन्यथा
	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, nv41_vmm_pgt_pte);
#पूर्ण_अगर
पूर्ण

अटल व्योम
nv41_vmm_pgt_unmap(काष्ठा nvkm_vmm *vmm,
		   काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	VMM_FO032(pt, vmm, ptei * 4, 0, ptes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
nv41_vmm_desc_pgt = अणु
	.unmap = nv41_vmm_pgt_unmap,
	.dma = nv41_vmm_pgt_dma,
	.sgl = nv41_vmm_pgt_sgl,
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
nv41_vmm_desc_12[] = अणु
	अणु PGT, 17, 4, 0x1000, &nv41_vmm_desc_pgt पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv41_vmm_flush(काष्ठा nvkm_vmm *vmm, पूर्णांक level)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;

	mutex_lock(&vmm->mmu->mutex);
	nvkm_wr32(device, 0x100810, 0x00000022);
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x100810) & 0x00000020)
			अवरोध;
	);
	nvkm_wr32(device, 0x100810, 0x00000000);
	mutex_unlock(&vmm->mmu->mutex);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
nv41_vmm = अणु
	.valid = nv04_vmm_valid,
	.flush = nv41_vmm_flush,
	.page = अणु
		अणु 12, &nv41_vmm_desc_12[0], NVKM_VMM_PAGE_HOST पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv41_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	     व्योम *argv, u32 argc, काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	     काष्ठा nvkm_vmm **pvmm)
अणु
	वापस nv04_vmm_new_(&nv41_vmm, mmu, 0, managed, addr, size,
			     argv, argc, key, name, pvmm);
पूर्ण
