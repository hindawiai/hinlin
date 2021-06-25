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
nv44_vmm_pgt_fill(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  dma_addr_t *list, u32 ptei, u32 ptes)
अणु
	u32 pteo = (ptei << 2) & ~0x0000000f;
	u32 पंचांगp[4];

	पंचांगp[0] = nvkm_ro32(pt->memory, pteo + 0x0);
	पंचांगp[1] = nvkm_ro32(pt->memory, pteo + 0x4);
	पंचांगp[2] = nvkm_ro32(pt->memory, pteo + 0x8);
	पंचांगp[3] = nvkm_ro32(pt->memory, pteo + 0xc);

	जबतक (ptes--) अणु
		u32 addr = (list ? *list++ : vmm->null) >> 12;
		चयन (ptei++ & 0x3) अणु
		हाल 0:
			पंचांगp[0] &= ~0x07ffffff;
			पंचांगp[0] |= addr;
			अवरोध;
		हाल 1:
			पंचांगp[0] &= ~0xf8000000;
			पंचांगp[0] |= addr << 27;
			पंचांगp[1] &= ~0x003fffff;
			पंचांगp[1] |= addr >> 5;
			अवरोध;
		हाल 2:
			पंचांगp[1] &= ~0xffc00000;
			पंचांगp[1] |= addr << 22;
			पंचांगp[2] &= ~0x0001ffff;
			पंचांगp[2] |= addr >> 10;
			अवरोध;
		हाल 3:
			पंचांगp[2] &= ~0xfffe0000;
			पंचांगp[2] |= addr << 17;
			पंचांगp[3] &= ~0x00000fff;
			पंचांगp[3] |= addr >> 15;
			अवरोध;
		पूर्ण
	पूर्ण

	VMM_WO032(pt, vmm, pteo + 0x0, पंचांगp[0]);
	VMM_WO032(pt, vmm, pteo + 0x4, पंचांगp[1]);
	VMM_WO032(pt, vmm, pteo + 0x8, पंचांगp[2]);
	VMM_WO032(pt, vmm, pteo + 0xc, पंचांगp[3] | 0x40000000);
पूर्ण

अटल व्योम
nv44_vmm_pgt_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	dma_addr_t पंचांगp[4], i;

	अगर (ptei & 3) अणु
		स्थिर u32 pten = min(ptes, 4 - (ptei & 3));
		क्रम (i = 0; i < pten; i++, addr += 0x1000)
			पंचांगp[i] = addr;
		nv44_vmm_pgt_fill(vmm, pt, पंचांगp, ptei, pten);
		ptei += pten;
		ptes -= pten;
	पूर्ण

	जबतक (ptes >= 4) अणु
		क्रम (i = 0; i < 4; i++, addr += 0x1000)
			पंचांगp[i] = addr >> 12;
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[0] >>  0 | पंचांगp[1] << 27);
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[1] >>  5 | पंचांगp[2] << 22);
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[2] >> 10 | पंचांगp[3] << 17);
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[3] >> 15 | 0x40000000);
		ptes -= 4;
	पूर्ण

	अगर (ptes) अणु
		क्रम (i = 0; i < ptes; i++, addr += 0x1000)
			पंचांगp[i] = addr;
		nv44_vmm_pgt_fill(vmm, pt, पंचांगp, ptei, ptes);
	पूर्ण
पूर्ण

अटल व्योम
nv44_vmm_pgt_sgl(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_SGL(vmm, pt, ptei, ptes, map, nv44_vmm_pgt_pte);
पूर्ण

अटल व्योम
nv44_vmm_pgt_dma(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
#अगर PAGE_SHIFT == 12
	nvkm_kmap(pt->memory);
	अगर (ptei & 3) अणु
		स्थिर u32 pten = min(ptes, 4 - (ptei & 3));
		nv44_vmm_pgt_fill(vmm, pt, map->dma, ptei, pten);
		ptei += pten;
		ptes -= pten;
		map->dma += pten;
	पूर्ण

	जबतक (ptes >= 4) अणु
		u32 पंचांगp[4], i;
		क्रम (i = 0; i < 4; i++)
			पंचांगp[i] = *map->dma++ >> 12;
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[0] >>  0 | पंचांगp[1] << 27);
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[1] >>  5 | पंचांगp[2] << 22);
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[2] >> 10 | पंचांगp[3] << 17);
		VMM_WO032(pt, vmm, ptei++ * 4, पंचांगp[3] >> 15 | 0x40000000);
		ptes -= 4;
	पूर्ण

	अगर (ptes) अणु
		nv44_vmm_pgt_fill(vmm, pt, map->dma, ptei, ptes);
		map->dma += ptes;
	पूर्ण
	nvkm_करोne(pt->memory);
#अन्यथा
	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, nv44_vmm_pgt_pte);
#पूर्ण_अगर
पूर्ण

अटल व्योम
nv44_vmm_pgt_unmap(काष्ठा nvkm_vmm *vmm,
		   काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	nvkm_kmap(pt->memory);
	अगर (ptei & 3) अणु
		स्थिर u32 pten = min(ptes, 4 - (ptei & 3));
		nv44_vmm_pgt_fill(vmm, pt, शून्य, ptei, pten);
		ptei += pten;
		ptes -= pten;
	पूर्ण

	जबतक (ptes > 4) अणु
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		VMM_WO032(pt, vmm, ptei++ * 4, 0x00000000);
		ptes -= 4;
	पूर्ण

	अगर (ptes)
		nv44_vmm_pgt_fill(vmm, pt, शून्य, ptei, ptes);
	nvkm_करोne(pt->memory);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
nv44_vmm_desc_pgt = अणु
	.unmap = nv44_vmm_pgt_unmap,
	.dma = nv44_vmm_pgt_dma,
	.sgl = nv44_vmm_pgt_sgl,
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
nv44_vmm_desc_12[] = अणु
	अणु PGT, 17, 4, 0x80000, &nv44_vmm_desc_pgt पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv44_vmm_flush(काष्ठा nvkm_vmm *vmm, पूर्णांक level)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	nvkm_wr32(device, 0x100814, vmm->limit - 4096);
	nvkm_wr32(device, 0x100808, 0x000000020);
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x100808) & 0x00000001)
			अवरोध;
	);
	nvkm_wr32(device, 0x100808, 0x00000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
nv44_vmm = अणु
	.valid = nv04_vmm_valid,
	.flush = nv44_vmm_flush,
	.page = अणु
		अणु 12, &nv44_vmm_desc_12[0], NVKM_VMM_PAGE_HOST पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv44_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	     व्योम *argv, u32 argc, काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	     काष्ठा nvkm_vmm **pvmm)
अणु
	काष्ठा nvkm_subdev *subdev = &mmu->subdev;
	काष्ठा nvkm_vmm *vmm;
	पूर्णांक ret;

	ret = nv04_vmm_new_(&nv44_vmm, mmu, 0, managed, addr, size,
			    argv, argc, key, name, &vmm);
	*pvmm = vmm;
	अगर (ret)
		वापस ret;

	vmm->nullp = dma_alloc_coherent(subdev->device->dev, 16 * 1024,
					&vmm->null, GFP_KERNEL);
	अगर (!vmm->nullp) अणु
		nvkm_warn(subdev, "unable to allocate dummy pages\n");
		vmm->null = 0;
	पूर्ण

	वापस 0;
पूर्ण
