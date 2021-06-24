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
#समावेश <subdev/समयr.h>
#समावेश <engine/gr.h>

#समावेश <nvअगर/अगर500d.h>
#समावेश <nvअगर/unpack.h>

अटल अंतरभूत व्योम
nv50_vmm_pgt_pte(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map, u64 addr)
अणु
	u64 next = addr + map->type, data;
	u32 pten;
	पूर्णांक log2blk;

	map->type += ptes * map->ctag;

	जबतक (ptes) अणु
		क्रम (log2blk = 7; log2blk >= 0; log2blk--) अणु
			pten = 1 << log2blk;
			अगर (ptes >= pten && IS_ALIGNED(ptei, pten))
				अवरोध;
		पूर्ण

		data  = next | (log2blk << 7);
		next += pten * map->next;
		ptes -= pten;

		जबतक (pten--)
			VMM_WO064(pt, vmm, ptei++ * 8, data);
	पूर्ण
पूर्ण

अटल व्योम
nv50_vmm_pgt_sgl(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_SGL(vmm, pt, ptei, ptes, map, nv50_vmm_pgt_pte);
पूर्ण

अटल व्योम
nv50_vmm_pgt_dma(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	अगर (map->page->shअगरt == PAGE_SHIFT) अणु
		VMM_SPAM(vmm, "DMAA %08x %08x PTE(s)", ptei, ptes);
		nvkm_kmap(pt->memory);
		जबतक (ptes--) अणु
			स्थिर u64 data = *map->dma++ + map->type;
			VMM_WO064(pt, vmm, ptei++ * 8, data);
			map->type += map->ctag;
		पूर्ण
		nvkm_करोne(pt->memory);
		वापस;
	पूर्ण

	VMM_MAP_ITER_DMA(vmm, pt, ptei, ptes, map, nv50_vmm_pgt_pte);
पूर्ण

अटल व्योम
nv50_vmm_pgt_mem(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_mmu_pt *pt,
		 u32 ptei, u32 ptes, काष्ठा nvkm_vmm_map *map)
अणु
	VMM_MAP_ITER_MEM(vmm, pt, ptei, ptes, map, nv50_vmm_pgt_pte);
पूर्ण

अटल व्योम
nv50_vmm_pgt_unmap(काष्ठा nvkm_vmm *vmm,
		   काष्ठा nvkm_mmu_pt *pt, u32 ptei, u32 ptes)
अणु
	VMM_FO064(pt, vmm, ptei * 8, 0ULL, ptes);
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
nv50_vmm_pgt = अणु
	.unmap = nv50_vmm_pgt_unmap,
	.mem = nv50_vmm_pgt_mem,
	.dma = nv50_vmm_pgt_dma,
	.sgl = nv50_vmm_pgt_sgl,
पूर्ण;

अटल bool
nv50_vmm_pde(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vmm_pt *pgt, u64 *pdata)
अणु
	काष्ठा nvkm_mmu_pt *pt;
	u64 data = 0xdeadcafe00000000ULL;
	अगर (pgt && (pt = pgt->pt[0])) अणु
		चयन (pgt->page) अणु
		हाल 16: data = 0x00000001; अवरोध;
		हाल 12: data = 0x00000003;
			चयन (nvkm_memory_size(pt->memory)) अणु
			हाल 0x100000: data |= 0x00000000; अवरोध;
			हाल 0x040000: data |= 0x00000020; अवरोध;
			हाल 0x020000: data |= 0x00000040; अवरोध;
			हाल 0x010000: data |= 0x00000060; अवरोध;
			शेष:
				WARN_ON(1);
				वापस false;
			पूर्ण
			अवरोध;
		शेष:
			WARN_ON(1);
			वापस false;
		पूर्ण

		चयन (nvkm_memory_target(pt->memory)) अणु
		हाल NVKM_MEM_TARGET_VRAM: data |= 0x00000000; अवरोध;
		हाल NVKM_MEM_TARGET_HOST: data |= 0x00000008; अवरोध;
		हाल NVKM_MEM_TARGET_NCOH: data |= 0x0000000c; अवरोध;
		शेष:
			WARN_ON(1);
			वापस false;
		पूर्ण

		data |= pt->addr;
	पूर्ण
	*pdata = data;
	वापस true;
पूर्ण

अटल व्योम
nv50_vmm_pgd_pde(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_vmm_pt *pgd, u32 pdei)
अणु
	काष्ठा nvkm_vmm_join *join;
	u32 pdeo = vmm->mmu->func->vmm.pd_offset + (pdei * 8);
	u64 data;

	अगर (!nv50_vmm_pde(vmm, pgd->pde[pdei], &data))
		वापस;

	list_क्रम_each_entry(join, &vmm->join, head) अणु
		nvkm_kmap(join->inst);
		nvkm_wo64(join->inst, pdeo, data);
		nvkm_करोne(join->inst);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_desc_func
nv50_vmm_pgd = अणु
	.pde = nv50_vmm_pgd_pde,
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
nv50_vmm_desc_12[] = अणु
	अणु PGT, 17, 8, 0x1000, &nv50_vmm_pgt पूर्ण,
	अणु PGD, 11, 0, 0x0000, &nv50_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_vmm_desc
nv50_vmm_desc_16[] = अणु
	अणु PGT, 13, 8, 0x1000, &nv50_vmm_pgt पूर्ण,
	अणु PGD, 11, 0, 0x0000, &nv50_vmm_pgd पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
nv50_vmm_flush(काष्ठा nvkm_vmm *vmm, पूर्णांक level)
अणु
	काष्ठा nvkm_subdev *subdev = &vmm->mmu->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक i, id;

	mutex_lock(&vmm->mmu->mutex);
	क्रम (i = 0; i < NVKM_SUBDEV_NR; i++) अणु
		अगर (!atomic_पढ़ो(&vmm->engref[i]))
			जारी;

		/* unक्रमtunate hw bug workaround... */
		अगर (i == NVKM_ENGINE_GR && device->gr) अणु
			पूर्णांक ret = nvkm_gr_tlb_flush(device->gr);
			अगर (ret != -ENODEV)
				जारी;
		पूर्ण

		चयन (i) अणु
		हाल NVKM_ENGINE_GR    : id = 0x00; अवरोध;
		हाल NVKM_ENGINE_VP    :
		हाल NVKM_ENGINE_MSPDEC: id = 0x01; अवरोध;
		हाल NVKM_SUBDEV_BAR   : id = 0x06; अवरोध;
		हाल NVKM_ENGINE_MSPPP :
		हाल NVKM_ENGINE_MPEG  : id = 0x08; अवरोध;
		हाल NVKM_ENGINE_BSP   :
		हाल NVKM_ENGINE_MSVLD : id = 0x09; अवरोध;
		हाल NVKM_ENGINE_CIPHER:
		हाल NVKM_ENGINE_SEC   : id = 0x0a; अवरोध;
		हाल NVKM_ENGINE_CE    : id = 0x0d; अवरोध;
		शेष:
			जारी;
		पूर्ण

		nvkm_wr32(device, 0x100c80, (id << 16) | 1);
		अगर (nvkm_msec(device, 2000,
			अगर (!(nvkm_rd32(device, 0x100c80) & 0x00000001))
				अवरोध;
		) < 0)
			nvkm_error(subdev, "%s mmu invalidate timeout\n", nvkm_subdev_type[i]);
	पूर्ण
	mutex_unlock(&vmm->mmu->mutex);
पूर्ण

पूर्णांक
nv50_vmm_valid(काष्ठा nvkm_vmm *vmm, व्योम *argv, u32 argc,
	       काष्ठा nvkm_vmm_map *map)
अणु
	स्थिर काष्ठा nvkm_vmm_page *page = map->page;
	जोड़ अणु
		काष्ठा nv50_vmm_map_vn vn;
		काष्ठा nv50_vmm_map_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_device *device = vmm->mmu->subdev.device;
	काष्ठा nvkm_ram *ram = device->fb->ram;
	काष्ठा nvkm_memory *memory = map->memory;
	u8  aper, kind, kind_inv, comp, priv, ro;
	पूर्णांक kindn, ret = -ENOSYS;
	स्थिर u8 *kindm;

	map->type = map->ctag = 0;
	map->next = 1 << page->shअगरt;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		ro   = !!args->v0.ro;
		priv = !!args->v0.priv;
		kind = args->v0.kind & 0x7f;
		comp = args->v0.comp & 0x03;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unvers(ret, &argv, &argc, args->vn))) अणु
		ro   = 0;
		priv = 0;
		kind = 0x00;
		comp = 0;
	पूर्ण अन्यथा अणु
		VMM_DEBUG(vmm, "args");
		वापस ret;
	पूर्ण

	चयन (nvkm_memory_target(memory)) अणु
	हाल NVKM_MEM_TARGET_VRAM:
		अगर (ram->stolen) अणु
			map->type |= ram->stolen;
			aper = 3;
		पूर्ण अन्यथा अणु
			aper = 0;
		पूर्ण
		अवरोध;
	हाल NVKM_MEM_TARGET_HOST:
		aper = 2;
		अवरोध;
	हाल NVKM_MEM_TARGET_NCOH:
		aper = 3;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	kindm = vmm->mmu->func->kind(vmm->mmu, &kindn, &kind_inv);
	अगर (kind >= kindn || kindm[kind] == kind_inv) अणु
		VMM_DEBUG(vmm, "kind %02x", kind);
		वापस -EINVAL;
	पूर्ण

	अगर (map->mem && map->mem->type != kindm[kind]) अणु
		VMM_DEBUG(vmm, "kind %02x bankswz: %d %d", kind,
			  kindm[kind], map->mem->type);
		वापस -EINVAL;
	पूर्ण

	अगर (comp) अणु
		u32 tags = (nvkm_memory_size(memory) >> 16) * comp;
		अगर (aper != 0 || !(page->type & NVKM_VMM_PAGE_COMP)) अणु
			VMM_DEBUG(vmm, "comp %d %02x", aper, page->type);
			वापस -EINVAL;
		पूर्ण

		ret = nvkm_memory_tags_get(memory, device, tags, शून्य,
					   &map->tags);
		अगर (ret) अणु
			VMM_DEBUG(vmm, "comp %d", ret);
			वापस ret;
		पूर्ण

		अगर (map->tags->mn) अणु
			u32 tags = map->tags->mn->offset + (map->offset >> 16);
			map->ctag |= (u64)comp << 49;
			map->type |= (u64)comp << 47;
			map->type |= (u64)tags << 49;
			map->next |= map->ctag;
		पूर्ण
	पूर्ण

	map->type |= BIT(0); /* Valid. */
	map->type |= (u64)ro << 3;
	map->type |= (u64)aper << 4;
	map->type |= (u64)priv << 6;
	map->type |= (u64)kind << 40;
	वापस 0;
पूर्ण

व्योम
nv50_vmm_part(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	काष्ठा nvkm_vmm_join *join;

	list_क्रम_each_entry(join, &vmm->join, head) अणु
		अगर (join->inst == inst) अणु
			list_del(&join->head);
			kमुक्त(join);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
nv50_vmm_join(काष्ठा nvkm_vmm *vmm, काष्ठा nvkm_memory *inst)
अणु
	स्थिर u32 pd_offset = vmm->mmu->func->vmm.pd_offset;
	काष्ठा nvkm_vmm_join *join;
	पूर्णांक ret = 0;
	u64 data;
	u32 pdei;

	अगर (!(join = kदो_स्मृति(माप(*join), GFP_KERNEL)))
		वापस -ENOMEM;
	join->inst = inst;
	list_add_tail(&join->head, &vmm->join);

	nvkm_kmap(join->inst);
	क्रम (pdei = vmm->start >> 29; pdei <= (vmm->limit - 1) >> 29; pdei++) अणु
		अगर (!nv50_vmm_pde(vmm, vmm->pd->pde[pdei], &data)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		nvkm_wo64(join->inst, pd_offset + (pdei * 8), data);
	पूर्ण
	nvkm_करोne(join->inst);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_vmm_func
nv50_vmm = अणु
	.join = nv50_vmm_join,
	.part = nv50_vmm_part,
	.valid = nv50_vmm_valid,
	.flush = nv50_vmm_flush,
	.page_block = 1 << 29,
	.page = अणु
		अणु 16, &nv50_vmm_desc_16[0], NVKM_VMM_PAGE_xVxC पूर्ण,
		अणु 12, &nv50_vmm_desc_12[0], NVKM_VMM_PAGE_xVHx पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv50_vmm_new(काष्ठा nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	     व्योम *argv, u32 argc, काष्ठा lock_class_key *key, स्थिर अक्षर *name,
	     काष्ठा nvkm_vmm **pvmm)
अणु
	वापस nv04_vmm_new_(&nv50_vmm, mmu, 0, managed, addr, size,
			     argv, argc, key, name, pvmm);
पूर्ण
