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

#समावेश <subdev/fb.h>
#समावेश <subdev/ltc.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/अगर900d.h>
#समावेश <nvअगर/unpack.h>

अटल अंतरभूत व्योम
gf100_vmm_pgt_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	u64 base = (addr >> 8) | map->type;
	u64 data = base;

	अगर (map->ctag && !(map->next & (1ULL << 44))) अणु
		जबतक (ptes--) अणु
			data = base | ((map->ctag >> 1) << 44);
			अगर (!(map->ctag++ & 1))
				data |= BIT_ULL(60);

			VMM_WO064(pt, vmm, ptei++ * 8, data);
			base += map->next;
		पूर्ण
	पूर्ण अन्यथा अणु
		map->type += ptes * map->ctag;

		जबतक (ptes--) अणु
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			data += map->next;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
gf100_vmm_pgt_sgl(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_SGL(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
पूर्ण

व्योम
gf100_vmm_pgt_dma(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	अगर (map->page->shअगरt == PAGE_SHIFT) अणु
		VMM_SPAM(vmm, "DMAA %08x %08x PTE(s)", ptei, ptes);
		nvkm_kmap(pt->memory);
		जबतक (ptes--) अणु
			स्थिर u64 data = (*map->dma++ >> 8) | map->type;
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			map->type += map->ctag;
		पूर्ण
		nvkm_करोne(pt->memory);
		वापस;
	पूर्ण

	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
पूर्ण

व्योम
gf100_vmm_pgt_mem(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		  u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_MEM(vmm, pt, ptei, ptes, map, gf100_vmm_pgt_pte);
पूर्ण

व्योम
gf100_vmm_pgt_unmap(काष्ठा nvkm_vmm *vmm,
		    काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	VMM_FO064(pt, vmm, ptei * 8, 0ULL, ptes);
पूर्ण

स्थिर काष्ठा nvkm_vmm_desc_func
gf100_vmm_pgt = अणु
	.unmap = gf100_vmm_pgt_unmap,
	.mem = gf100_vmm_pgt_mem,
	.dma = gf100_vmm_pgt_dma,
	.sgl = gf100_vmm_pgt_sgl,
पूर्ण;

व्योम
gf100_vmm_pgd_pde(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vmm_pt *pgd, u32 pdei)
अणु
	काष्ठा nvkm_vmm_pt *pgt = pgd->pde[pdei];
	काष्ठा nvkm_mmu_pt *pd = pgd->pt[0];
	काष्ठा nvkm_mmu_pt *pt;
	u64 data = 0;

	अगर ((pt = pgt->pt[0])) अणु
		चयन (nvkm_memory_target(pt->memory)) अणु
		हाल NVKM_MEM_TARGET_VRAM: data |= 1ULL << 0; अवरोध;
		हाल NVKM_MEM_TARGET_HOST: data |= 2ULL << 0;
			data |= BIT_ULL(35); /* VOL */
			अवरोध;
		हाल NVKM_MEM_TARGET_NCOH: data |= 3ULL << 0; अवरोध;
		शेष:
			WARN_ON(1);
			वापस;
		पूर्ण
		data |= pt->addr >> 8;
	पूर्ण

	अगर ((pt = pgt->pt[1])) अणु
		चयन (nvkm_memory_target(pt->memory)) अणु
		हाल NVKM_MEM_TARGET_VRAM: data |= 1ULL << 32; अवरोध;
		हाल NVKM_MEM_TARGET_HOST: data |= 2ULL << 32;
			data |= BIT_ULL(34); /* VOL */
			अवरोध;
		हाल NVKM_MEM_TARGET_NCOH: data |= 3ULL << 32; अवरोध;
		शेष:
			WARN_ON(1);
			वापस;
		पूर्ण
		data |= pt->addr << 24;
	पूर्ण

	nvkm_kmap(pd->memory);
	VMM_WO064(pd, vmm, pdei * 8, data);
	nvkm_करोne(pd->memory);
पूर्ण

स्थिर काष्ठा nvkm_vmm_desc_func
gf100_vmm_pgd = अणु
	.unmap = gf100_vmm_pgt_unmap,
	.pde = gf100_vmm_pgd_pde,
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
gf100_vmm_desc_17_12[] = अणु
	अणु SPT, 15, 8, 0x1000, &gf100_vmm_pgt पूर्ण,
	अणु PGD, 13, 8, 0x1000, &gf100_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
gf100_vmm_desc_17_17[] = अणु
	अणु LPT, 10, 8, 0x1000, &gf100_vmm_pgt पूर्ण,
	अणु PGD, 13, 8, 0x1000, &gf100_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
gf100_vmm_desc_16_12[] = अणु
	अणु SPT, 14, 8, 0x1000, &gf100_vmm_pgt पूर्ण,
	अणु PGD, 14, 8, 0x1000, &gf100_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_desc
gf100_vmm_desc_16_16[] = अणु
	अणु LPT, 10, 8, 0x1000, &gf100_vmm_pgt पूर्ण,
	अणु PGD, 14, 8, 0x1000, &gf100_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gf100_vmm_invalidate_pdb(काष्ठा nvkm_vmm *vmm, u64 addr)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	nvkm_wr32(device, 0x100cb8, addr);
पूर्ण

व्योम
gf100_vmm_invalidate(काष्ठा nvkm_vmm *vmm, u32 type)
अणु
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	काष्ठा nvkm_mmu_pt *pd = vmm->pd->pt[0];
	u64 addr = 0;

	mutex_lock(&vmm->mmu->mutex);
	/* Looks like maybe a "free flush slots" counter, the
	 * faster you ग_लिखो to 0x100cbc to more it decreases.
	 */
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x100c80) & 0x00ff0000)
			अवरोध;
	);

	अगर (!(type & 0x00000002) /* ALL_PDB. */) अणु
		चयन (nvkm_memory_target(pd->memory)) अणु
		हाल NVKM_MEM_TARGET_VRAM: addr |= 0x00000000; अवरोध;
		हाल NVKM_MEM_TARGET_HOST: addr |= 0x00000002; अवरोध;
		हाल NVKM_MEM_TARGET_NCOH: addr |= 0x00000003; अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		addr |= (vmm->pd->pt[0]->addr >> 12) << 4;

		vmm->func->invalidate_pdb(vmm, addr);
	पूर्ण

	nvkm_wr32(device, 0x100cbc, 0x80000000 | type);

	/* Wait क्रम flush to be queued? */
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x100c80) & 0x00008000)
			अवरोध;
	);
	mutex_unlock(&vmm->mmu->mutex);
पूर्ण

व्योम
gf100_vmm_flush(काष्ठा nvkm_vmm *vmm, पूर्णांक depth)
अणु
	u32 type = 0x00000001; /* PAGE_ALL */
	अगर (atomic_पढ़ो(&vmm->engref[NVKM_SUBDEV_BAR]))
		type |= 0x00000004; /* HUB_ONLY */
	gf100_vmm_invalidate(vmm, type);
पूर्ण

पूर्णांक
gf100_vmm_valid(काष्ठा nvkm_vmm *vmm, व्योम *argv, u32 argc,
		काष्ठा nvkm_vmm_map *map)
अणु
	स्थिर क्रमागत nvkm_memory_target target = nvkm_memory_target(map->memory);
	स्थिर काष्ठा nvkm_vmm_page *page = map->page;
	स्थिर bool gm20x = page->desc->func->sparse != शून्य;
	जोड़ अणु
		काष्ठा gf100_vmm_map_vn vn;
		काष्ठा gf100_vmm_map_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	काष्ठा nvkm_memory *memory = map->memory;
	u8  kind, kind_inv, priv, ro, vol;
	पूर्णांक kindn, aper, ret = -ENOSYS;
	स्थिर u8 *kindm;

	map->next = (1 << page->shअगरt) >> 8;
	map->type = map->ctag = 0;

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
		u32 comp = (page->shअगरt == 16 && !gm20x) ? 16 : 17;
		u32 tags = ALIGN(nvkm_memory_size(memory), 1 << 17) >> comp;
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
			u64 tags = map->tags->mn->offset + (map->offset >> 17);
			अगर (page->shअगरt == 17 || !gm20x) अणु
				map->type |= tags << 44;
				map->ctag |= 1ULL << 44;
				map->next |= 1ULL << 44;
			पूर्ण अन्यथा अणु
				map->ctag |= tags << 1 | 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			kind = kindm[kind];
		पूर्ण
	पूर्ण

	map->type |= BIT(0);
	map->type |= (u64)priv << 1;
	map->type |= (u64)  ro << 2;
	map->type |= (u64) vol << 32;
	map->type |= (u64)aper << 33;
	map->type |= (u64)kind << 36;
	वापस 0;
पूर्ण

पूर्णांक
gf100_vmm_aper(क्रमागत nvkm_memory_target target)
अणु
	चयन (target) अणु
	हाल NVKM_MEM_TARGET_VRAM: वापस 0;
	हाल NVKM_MEM_TARGET_HOST: वापस 2;
	हाल NVKM_MEM_TARGET_NCOH: वापस 3;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम
gf100_vmm_part(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	nvkm_fo64(inst, 0x0200, 0x00000000, 2);
पूर्ण

पूर्णांक
gf100_vmm_join_(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst, u64 base)
अणु
	काष्ठा nvkm_mmu_pt *pd = vmm->pd->pt[0];

	चयन (nvkm_memory_target(pd->memory)) अणु
	हाल NVKM_MEM_TARGET_VRAM: base |= 0ULL << 0; अवरोध;
	हाल NVKM_MEM_TARGET_HOST: base |= 2ULL << 0;
		base |= BIT_ULL(2) /* VOL. */;
		अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: base |= 3ULL << 0; अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	base |= pd->addr;

	nvkm_kmap(inst);
	nvkm_wo64(inst, 0x0200, base);
	nvkm_wo64(inst, 0x0208, vmm->limit - 1);
	nvkm_करोne(inst);
	वापस 0;
पूर्ण

पूर्णांक
gf100_vmm_join(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	वापस gf100_vmm_join_(vmm, inst, 0);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
gf100_vmm_17 = अणु
	.join = gf100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gf100_vmm_valid,
	.flush = gf100_vmm_flush,
	.invalidate_pdb = gf100_vmm_invalidate_pdb,
	.page = अणु
		अणु 17, &gf100_vmm_desc_17_17[0], NVKM_VMM_PAGE_xVxC पूर्ण,
		अणु 12, &gf100_vmm_desc_17_12[0], NVKM_VMM_PAGE_xVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_vmm_func
gf100_vmm_16 = अणु
	.join = gf100_vmm_join,
	.part = gf100_vmm_part,
	.aper = gf100_vmm_aper,
	.valid = gf100_vmm_valid,
	.flush = gf100_vmm_flush,
	.invalidate_pdb = gf100_vmm_invalidate_pdb,
	.page = अणु
		अणु 16, &gf100_vmm_desc_16_16[0], NVKM_VMM_PAGE_xVxC पूर्ण,
		अणु 12, &gf100_vmm_desc_16_12[0], NVKM_VMM_PAGE_xVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gf100_vmm_new_(स्थिर काष्ठा nvkm_vmm_func *func_16,
	       स्थिर काष्ठा nvkm_vmm_func *func_17,
	       काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	       व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	       स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	चयन (mmu->subdev.device->fb->page) अणु
	हाल 16: वापस nv04_vmm_new_(func_16, mmu, 0, managed, addr, size,
				      argv, argc, key, name, pvmm);
	हाल 17: वापस nv04_vmm_new_(func_17, mmu, 0, managed, addr, size,
				      argv, argc, key, name, pvmm);
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक
gf100_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      व्योम *argv, u32 argc, काष्ठा lock_class_key *key,
	      स्थिर अक्षर *name, काष्ठा nvkm_vmm **pvmm)
अणु
	वापस gf100_vmm_new_(&gf100_vmm_16, &gf100_vmm_17, mmu, managed, addr,
			      size, argv, argc, key, name, pvmm);
पूर्ण
