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

#समावेश <core/client.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/ltc.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/gr.h>

#समावेश <nvअगर/अगरc00d.h>
#समावेश <nvअगर/unpack.h>

अटल व्योम
gp100_vmm_pfn_unmap(काष्ठा nvkm_vmm *vmm,
		    काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	काष्ठा device *dev = vmm->mmu->subdev.device->dev;
	dma_addr_t addr;

	nvkm_kmap(pt->memory);
	जबतक (ptes--) अणु
		u32 datalo = nvkm_ro32(pt->memory, pt->base + ptei * 8 + 0);
		u32 datahi = nvkm_ro32(pt->memory, pt->base + ptei * 8 + 4);
		u64 data   = (u64)datahi << 32 | datalo;
		अगर ((data & (3ULL << 1)) != 0) अणु
			addr = (data >> 8) << 12;
			dma_unmap_page(dev, addr, PAGE_SIZE, DMA_BIसूचीECTIONAL);
		पूर्ण
		ptei++;
	पूर्ण
	nvkm_करोne(pt->memory);
पूर्ण

अटल bool
gp100_vmm_pfn_clear(काष्ठा nvkm_vmm *vmm,
		    काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	bool dma = false;
	nvkm_kmap(pt->memory);
	जबतक (ptes--) अणु
		u32 datalo = nvkm_ro32(pt->memory, pt->base + ptei * 8 + 0);
		u32 datahi = nvkm_ro32(pt->memory, pt->base + ptei * 8 + 4);
		u64 data   = (u64)datahi << 32 | datalo;
		अगर ((data & BIT_ULL(0)) && (data & (3ULL << 1)) != 0) अणु
			VMM_WO064(pt, vmm, ptei * 8, data & ~BIT_ULL(0));
			dma = true;
		पूर्ण
		ptei++;
	पूर्ण
	nvkm_करोne(pt->memory);
	वापस dma;
पूर्ण

अटल व्योम
gp100_vmm_pgt_pfn(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	काष्ठा device *dev = vmm->mmu->subdev.device->dev;
	dma_addr_t addr;

	nvkm_kmap(pt->memory);
	क्रम (; ptes; ptes--, map->pfn++) अणु
		u64 data = 0;

		अगर (!(*map->pfn & NVKM_VMM_PFN_V))
			जारी;

		अगर (!(*map->pfn & NVKM_VMM_PFN_W))
			data |= BIT_ULL(6); /* RO. */

		अगर (!(*map->pfn & NVKM_VMM_PFN_VRAM)) अणु
			addr = *map->pfn >> NVKM_VMM_PFN_ADDR_SHIFT;
			addr = dma_map_page(dev, pfn_to_page(addr), 0,
					    PAGE_SIZE, DMA_BIसूचीECTIONAL);
			अगर (!WARN_ON(dma_mapping_error(dev, addr))) अणु
				data |= addr >> 4;
				data |= 2ULL << 1; /* SYSTEM_COHERENT_MEMORY. */
				data |= BIT_ULL(3); /* VOL. */
				data |= BIT_ULL(0); /* VALID. */
			पूर्ण
		पूर्ण अन्यथा अणु
			data |= (*map->pfn & NVKM_VMM_PFN_ADDR) >> 4;
			data |= BIT_ULL(0); /* VALID. */
		पूर्ण

		VMM_WO064(pt, vmm, ptei++ * 8, data);
	पूर्ण
	nvkm_करोne(pt->memory);
पूर्ण

अटल अंतरभूत व्योम
gp100_vmm_pgt_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	u64 data = (addr >> 4) | map->type;

	map->type += ptes * map->ctag;

	जबतक (ptes--) अणु
		VMM_WO064(pt, vmm, ptei++ * 8, data);
		data += map->next;
	पूर्ण
पूर्ण

अटल व्योम
gp100_vmm_pgt_sgl(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_SGL(vmm, pt, ptei, ptes, map, gp100_vmm_pgt_pte);
पूर्ण

अटल व्योम
gp100_vmm_pgt_dma(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	अगर (map->page->shअगरt == PAGE_SHIFT) अणु
		VMM_SPAM(vmm, "DMAA %08x %08x PTE(s)", ptei, ptes);
		nvkm_kmap(pt->memory);
		जबतक (ptes--) अणु
			स्थिर u64 data = (*map->dma++ >> 4) | map->type;
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			map->type += map->ctag;
		पूर्ण
		nvkm_करोne(pt->memory);
		वापस;
	पूर्ण

	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, gp100_vmm_pgt_pte);
पूर्ण

अटल व्योम
gp100_vmm_pgt_mem(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_MEM(vmm, pt, ptei, ptes, map, gp100_vmm_pgt_pte);
पूर्ण

अटल व्योम
gp100_vmm_pgt_sparse(काष्ठा nvkm_vmm *vmm,
		     काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	/* VALID_FALSE + VOL tells the MMU to treat the PTE as sparse. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_ULL(3) /* VOL. */, ptes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gp100_vmm_desc_spt = अणु
	.unmap = gf100_vmm_pgt_unmap,
	.sparse = gp100_vmm_pgt_sparse,
	.mem = gp100_vmm_pgt_mem,
	.dma = gp100_vmm_pgt_dma,
	.sgl = gp100_vmm_pgt_sgl,
	.pfn = gp100_vmm_pgt_pfn,
	.pfn_clear = gp100_vmm_pfn_clear,
	.pfn_unmap = gp100_vmm_pfn_unmap,
पूर्ण;

अटल व्योम
gp100_vmm_lpt_invalid(काष्ठा nvkm_vmm *vmm,
		      काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	/* VALID_FALSE + PRIV tells the MMU to ignore corresponding SPTEs. */
	VMM_FO064(pt, vmm, ptei * 8, BIT_ULL(5) /* PRIV. */, ptes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gp100_vmm_desc_lpt = अणु
	.invalid = gp100_vmm_lpt_invalid,
	.unmap = gf100_vmm_pgt_unmap,
	.sparse = gp100_vmm_pgt_sparse,
	.mem = gp100_vmm_pgt_mem,
पूर्ण;

अटल अंतरभूत व्योम
gp100_vmm_pd0_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	u64 data = (addr >> 4) | map->type;

	map->type += ptes * map->ctag;

	जबतक (ptes--) अणु
		VMM_WO128(pt, vmm, ptei++ * 0x10, data, 0ULL);
		data += map->next;
	पूर्ण
पूर्ण

अटल व्योम
gp100_vmm_pd0_mem(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_MEM(vmm, pt, ptei, ptes, map, gp100_vmm_pd0_pte);
पूर्ण

अटल अंतरभूत bool
gp100_vmm_pde(काष्ठा nvkm_mmu_pt *pt, u64 *data)
अणु
	चयन (nvkm_memory_target(pt->memory)) अणु
	हाल NVKM_MEM_TARGET_VRAM: *data |= 1ULL << 1; अवरोध;
	हाल NVKM_MEM_TARGET_HOST: *data |= 2ULL << 1;
		*data |= BIT_ULL(3); /* VOL. */
		अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: *data |= 3ULL << 1; अवरोध;
	शेष:
		WARN_ON(1);
		वापस false;
	पूर्ण
	*data |= pt->addr >> 4;
	वापस true;
पूर्ण

अटल व्योम
gp100_vmm_pd0_pde(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vmm_pt *pgd, u32 pdei)
अणु
	काष्ठा nvkm_vmm_pt *pgt = pgd->pde[pdei];
	काष्ठा nvkm_mmu_pt *pd = pgd->pt[0];
	u64 data[2] = अणुपूर्ण;

	अगर (pgt->pt[0] && !gp100_vmm_pde(pgt->pt[0], &data[0]))
		वापस;
	अगर (pgt->pt[1] && !gp100_vmm_pde(pgt->pt[1], &data[1]))
		वापस;

	nvkm_kmap(pd->memory);
	VMM_WO128(pd, vmm, pdei * 0x10, data[0], data[1]);
	nvkm_करोne(pd->memory);
पूर्ण

अटल व्योम
gp100_vmm_pd0_sparse(काष्ठा nvkm_vmm *vmm,
		     काष्ठा nvkm_mmu_pt *pt, u32 pdei, u32 pdes)
अणु
	/* VALID_FALSE + VOL_BIG tells the MMU to treat the PDE as sparse. */
	VMM_FO128(pt, vmm, pdei * 0x10, BIT_ULL(3) /* VOL_BIG. */, 0ULL, pdes);
पूर्ण

अटल व्योम
gp100_vmm_pd0_unmap(काष्ठा nvkm_vmm *vmm,
		    काष्ठा nvkm_mmu_pt *pt, u32 pdei, u32 pdes)
अणु
	VMM_FO128(pt, vmm, pdei * 0x10, 0ULL, 0ULL, pdes);
पूर्ण

अटल व्योम
gp100_vmm_pd0_pfn_unmap(काष्ठा nvkm_vmm *vmm,
			काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	काष्ठा device *dev = vmm->mmu->subdev.device->dev;
	dma_addr_t addr;

	nvkm_kmap(pt->memory);
	जबतक (ptes--) अणु
		u32 datalo = nvkm_ro32(pt->memory, pt->base + ptei * 16 + 0);
		u32 datahi = nvkm_ro32(pt->memory, pt->base + ptei * 16 + 4);
		u64 data   = (u64)datahi << 32 | datalo;

		अगर ((data & (3ULL << 1)) != 0) अणु
			addr = (data >> 8) << 12;
			dma_unmap_page(dev, addr, 1UL << 21, DMA_BIसूचीECTIONAL);
		पूर्ण
		ptei++;
	पूर्ण
	nvkm_करोne(pt->memory);
पूर्ण

अटल bool
gp100_vmm_pd0_pfn_clear(काष्ठा nvkm_vmm *vmm,
			काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	bool dma = false;

	nvkm_kmap(pt->memory);
	जबतक (ptes--) अणु
		u32 datalo = nvkm_ro32(pt->memory, pt->base + ptei * 16 + 0);
		u32 datahi = nvkm_ro32(pt->memory, pt->base + ptei * 16 + 4);
		u64 data   = (u64)datahi << 32 | datalo;

		अगर ((data & BIT_ULL(0)) && (data & (3ULL << 1)) != 0) अणु
			VMM_WO064(pt, vmm, ptei * 16, data & ~BIT_ULL(0));
			dma = true;
		पूर्ण
		ptei++;
	पूर्ण
	nvkm_करोne(pt->memory);
	वापस dma;
पूर्ण

अटल व्योम
gp100_vmm_pd0_pfn(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	काष्ठा device *dev = vmm->mmu->subdev.device->dev;
	dma_addr_t addr;

	nvkm_kmap(pt->memory);
	क्रम (; ptes; ptes--, map->pfn++) अणु
		u64 data = 0;

		अगर (!(*map->pfn & NVKM_VMM_PFN_V))
			जारी;

		अगर (!(*map->pfn & NVKM_VMM_PFN_W))
			data |= BIT_ULL(6); /* RO. */

		अगर (!(*map->pfn & NVKM_VMM_PFN_VRAM)) अणु
			addr = *map->pfn >> NVKM_VMM_PFN_ADDR_SHIFT;
			addr = dma_map_page(dev, pfn_to_page(addr), 0,
					    1UL << 21, DMA_BIसूचीECTIONAL);
			अगर (!WARN_ON(dma_mapping_error(dev, addr))) अणु
				data |= addr >> 4;
				data |= 2ULL << 1; /* SYSTEM_COHERENT_MEMORY. */
				data |= BIT_ULL(3); /* VOL. */
				data |= BIT_ULL(0); /* VALID. */
			पूर्ण
		पूर्ण अन्यथा अणु
			data |= (*map->pfn & NVKM_VMM_PFN_ADDR) >> 4;
			data |= BIT_ULL(0); /* VALID. */
		पूर्ण

		VMM_WO064(pt, vmm, ptei++ * 16, data);
	पूर्ण
	nvkm_करोne(pt->memory);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gp100_vmm_desc_pd0 = अणु
	.unmap = gp100_vmm_pd0_unmap,
	.sparse = gp100_vmm_pd0_sparse,
	.pde = gp100_vmm_pd0_pde,
	.mem = gp100_vmm_pd0_mem,
	.pfn = gp100_vmm_pd0_pfn,
	.pfn_clear = gp100_vmm_pd0_pfn_clear,
	.pfn_unmap = gp100_vmm_pd0_pfn_unmap,
पूर्ण;

अटल व्योम
gp100_vmm_pd1_pde(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vmm_pt *pgd, u32 pdei)
अणु
	काष्ठा nvkm_vmm_pt *pgt = pgd->pde[pdei];
	काष्ठा nvkm_mmu_pt *pd = pgd->pt[0];
	u64 data = 0;

	अगर (!gp100_vmm_pde(pgt->pt[0], &data))
		वापस;

	nvkm_kmap(pd->memory);
	VMM_WO064(pd, vmm, pdei * 8, data);
	nvkm_करोne(pd->memory);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
gp100_vmm_desc_pd1 = अणु
	.unmap = gf100_vmm_pgt_unmap,
	.sparse = gp100_vmm_pgt_sparse,
	.pde = gp100_vmm_pd1_pde,
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
gp100_vmm_desc_16[] = अणु
	अणु LPT, 5,  8, 0x0100, &gp100_vmm_desc_lpt पूर्ण,
	अणु PGD, 8, 16, 0x1000, &gp100_vmm_desc_pd0 पूर्ण,
	अणु PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 पूर्ण,
	अणु PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 पूर्ण,
	अणु PGD, 2,  8, 0x1000, &gp100_vmm_desc_pd1 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
gp100_vmm_desc_12[] = अणु
	अणु SPT, 9,  8, 0x1000, &gp100_vmm_desc_spt पूर्ण,
	अणु PGD, 8, 16, 0x1000, &gp100_vmm_desc_pd0 पूर्ण,
	अणु PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 पूर्ण,
	अणु PGD, 9,  8, 0x1000, &gp100_vmm_desc_pd1 पूर्ण,
	अणु PGD, 2,  8, 0x1000, &gp100_vmm_desc_pd1 पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp100_vmm_valid(काष्ठा nvkm_vmm *vmm, व्योम *argv, u32 argc,
		काष्ठा nvkm_vmm_map *map)
अणु
	स्थिर क्रमागत nvkm_memory_target target = nvkm_memory_target(map->memory);
	स्थिर काष्ठा nvkm_vmm_page *page = map->page;
	जोड़ अणु
		काष्ठा gp100_vmm_map_vn vn;
		काष्ठा gp100_vmm_map_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	काष्ठा nvkm_memory *memory = map->memory;
	u8  kind, kind_inv, priv, ro, vol;
	पूर्णांक kindn, aper, ret = -ENOSYS;
	स्थिर u8 *kindm;

	map->next = (1ULL << page->shअगरt) >> 4;
	map->type = 0;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		vol  = !!args->v0.vol;
		ro   = !!args->v0.ro;
		priv = !!args->v0.priv;
		kind =   args->v0.kind;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		vol  = target == NVKM_MEM_TARGET_HOST;
		ro   = 0;
		priv = 0;
		kind = 0x00;
	पूर्ण अन्यथा अणु
		VMM_DEBUG(vmm, "args");
		वापस ret;
	पूर्ण

	aper = vmm->func->aper(target);
	अगर (WARN_ON(aper < 0))
		वापस aper;

	kindm = vmm->mmu->func->kind(vmm->mmu, &kindn, &kind_inv);
	अगर (kind >= kindn || kindm[kind] == kind_inv) अणु
		VMM_DEBUG(vmm, "kind %02x", kind);
		वापस -EINVAL;
	पूर्ण

	अगर (kindm[kind] != kind) अणु
		u64 tags = nvkm_memory_size(memory) >> 16;
		अगर (aper != 0 || !(page->type & NVKM_VMM_PAGE_COMP)) अणु
			VMM_DEBUG(vmm, "comp %d %02x", aper, page->type);
			वापस -EINVAL;
		पूर्ण

		ret = nvkm_memory_tags_get(memory, device, tags,
					   nvkm_ltc_tags_clear,
					   &map->tags);
		अगर (ret) अणु
			VMM_DEBUG(vmm, "comp %d", ret);
			वापस ret;
		पूर्ण

		अगर (map->tags->mn) अणु
			tags = map->tags->mn->offset + (map->offset >> 16);
			map->ctag |= ((1ULL << page->shअगरt) >> 16) << 36;
			map->type |= tags << 36;
			map->next |= map->ctag;
		पूर्ण अन्यथा अणु
			kind = kindm[kind];
		पूर्ण
	पूर्ण

	map->type |= BIT(0);
	map->type |= (u64)aper << 1;
	map->type |= (u64) vol << 3;
	map->type |= (u64)priv << 5;
	map->type |= (u64)  ro << 6;
	map->type |= (u64)kind << 56;
	वापस 0;
पूर्ण

अटल पूर्णांक
gp100_vmm_fault_cancel(काष्ठा nvkm_vmm *vmm, व्योम *argv, u32 argc)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	जोड़ अणु
		काष्ठा gp100_vmm_fault_cancel_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	u32 inst, aper;

	अगर ((ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false)))
		वापस ret;

	/* Translate MaxwellFaultBufferA instance poपूर्णांकer to the same
	 * क्रमmat as the NV_GR_FECS_CURRENT_CTX रेजिस्टर.
	 */
	aper = (args->v0.inst >> 8) & 3;
	args->v0.inst >>= 12;
	args->v0.inst |= aper << 28;
	args->v0.inst |= 0x80000000;

	अगर (!WARN_ON(nvkm_gr_ctxsw_छोड़ो(device))) अणु
		अगर ((inst = nvkm_gr_ctxsw_inst(device)) == args->v0.inst) अणु
			gf100_vmm_invalidate(vmm, 0x0000001b
					     /* CANCEL_TARGETED. */ |
					     (args->v0.hub    << 20) |
					     (args->v0.gpc    << 15) |
					     (args->v0.client << 9));
		पूर्ण
		WARN_ON(nvkm_gr_ctxsw_resume(device));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gp100_vmm_fault_replay(काष्ठा nvkm_vmm *vmm, व्योम *argv, u32 argc)
अणु
	जोड़ अणु
		काष्ठा gp100_vmm_fault_replay_vn vn;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		gf100_vmm_invalidate(vmm, 0x0000000b); /* REPLAY_GLOBAL. */
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
gp100_vmm_mthd(काष्ठा nvkm_vmm *vmm,
	       काष्ठा nvkm_client *client, u32 mthd, व्योम *argv, u32 argc)
अणु
	अगर (client->super) अणु
		चयन (mthd) अणु
		हाल GP100_VMM_VN_FAULT_REPLAY:
			वापस gp100_vmm_fault_replay(vmm, argv, argc);
		हाल GP100_VMM_VN_FAULT_CANCEL:
			वापस gp100_vmm_fault_cancel(vmm, argv, argc);
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

व्योम
gp100_vmm_invalidate_pdb(काष्ठा nvkm_vmm *vmm, u64 addr)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	nvkm_wr32(device, 0x100cb8, lower_32_bits(addr));
	nvkm_wr32(device, 0x100cec, upper_32_bits(addr));
पूर्ण

व्योम
gp100_vmm_flush(काष्ठा nvkm_vmm *vmm, पूर्णांक depth)
अणु
	u32 type = (5 /* CACHE_LEVEL_UP_TO_PDE3 */ - depth) << 24;
	अगर (atomic_पढ़ो(&vmm->engref[NVKM_SUBDEV_BAR]))
		type |= 0x00000004; /* HUB_ONLY */
	type |= 0x00000001; /* PAGE_ALL */
	gf100_vmm_invalidate(vmm, type);
पूर्ण

पूर्णांक
gp100_vmm_join(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	u64 base = BIT_ULL(10) /* VER2 */ | BIT_ULL(11) /* 64KiB */;
	अगर (vmm->replay) अणु
		base |= BIT_ULL(4); /* FAULT_REPLAY_TEX */
		base |= BIT_ULL(5); /* FAULT_REPLAY_GCC */
	पूर्ण
	वापस gf100_vmm_join_(vmm, inst, base);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
gp100_vmm = अणु
	.join = gp100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gp100_vmm_valid,
	.flush = gp100_vmm_flush,
	.mthd = gp100_vmm_mthd,
	.invalidate_pdb = gp100_vmm_invalidate_pdb,
	.page = अणु
		अणु 47, &gp100_vmm_desc_16[4], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 38, &gp100_vmm_desc_16[3], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 29, &gp100_vmm_desc_16[2], NVKM_VMM_PAGE_Sxxx पूर्ण,
		अणु 21, &gp100_vmm_desc_16[1], NVKM_VMM_PAGE_SVxC पूर्ण,
		अणु 16, &gp100_vmm_desc_16[0], NVKM_VMM_PAGE_SVxC पूर्ण,
		अणु 12, &gp100_vmm_desc_12[0], NVKM_VMM_PAGE_SVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gp100_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *func,
	       काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	       व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	       स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	जोड़ अणु
		काष्ठा gp100_vmm_vn vn;
		काष्ठा gp100_vmm_v0 v0;
	पूर्ण *args = argv;
	पूर्णांक ret = -ENOSYS;
	bool replay;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		replay = args->v0.fault_replay != 0;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		replay = false;
	पूर्ण अन्यथा
		वापस ret;

	ret = nvkm_vmm_new_(func, mmu, 0, managed, addr, size, key, name, pvmm);
	अगर (ret)
		वापस ret;

	(*pvmm)->replay = replay;
	वापस 0;
पूर्ण

पूर्णांक
gp100_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gp100_vmm_new_(&gp100_vmm, mmu, managed, addr, size,
			      argv, argc, key, name, pvmm);
पूर्ण
