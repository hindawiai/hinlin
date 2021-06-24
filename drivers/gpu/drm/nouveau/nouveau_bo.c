<शैली गुरु>
/*
 * Copyright 2007 Dave Airlied
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Authors: Dave Airlied <airlied@linux.ie>
 *	    Ben Skeggs   <darktama@iinet.net.au>
 *	    Jeremy Kolb  <jkolb@bअक्रमeis.edu>
 */

#समावेश <linux/dma-mapping.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_chan.h"
#समावेश "nouveau_fence.h"

#समावेश "nouveau_bo.h"
#समावेश "nouveau_ttm.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_mem.h"
#समावेश "nouveau_vmm.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर500b.h>
#समावेश <nvअगर/अगर900b.h>

अटल पूर्णांक nouveau_tपंचांग_tt_bind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग,
			       काष्ठा tपंचांग_resource *reg);
अटल व्योम nouveau_tपंचांग_tt_unbind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);

/*
 * NV10-NV40 tiling helpers
 */

अटल व्योम
nv10_bo_update_tile_region(काष्ठा drm_device *dev, काष्ठा nouveau_drm_tile *reg,
			   u32 addr, u32 size, u32 pitch, u32 flags)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	पूर्णांक i = reg - drm->tile.reg;
	काष्ठा nvkm_fb *fb = nvxx_fb(&drm->client.device);
	काष्ठा nvkm_fb_tile *tile = &fb->tile.region[i];

	nouveau_fence_unref(&reg->fence);

	अगर (tile->pitch)
		nvkm_fb_tile_fini(fb, i, tile);

	अगर (pitch)
		nvkm_fb_tile_init(fb, i, addr, size, pitch, flags, tile);

	nvkm_fb_tile_prog(fb, i, tile);
पूर्ण

अटल काष्ठा nouveau_drm_tile *
nv10_bo_get_tile_region(काष्ठा drm_device *dev, पूर्णांक i)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_drm_tile *tile = &drm->tile.reg[i];

	spin_lock(&drm->tile.lock);

	अगर (!tile->used &&
	    (!tile->fence || nouveau_fence_करोne(tile->fence)))
		tile->used = true;
	अन्यथा
		tile = शून्य;

	spin_unlock(&drm->tile.lock);
	वापस tile;
पूर्ण

अटल व्योम
nv10_bo_put_tile_region(काष्ठा drm_device *dev, काष्ठा nouveau_drm_tile *tile,
			काष्ठा dma_fence *fence)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (tile) अणु
		spin_lock(&drm->tile.lock);
		tile->fence = (काष्ठा nouveau_fence *)dma_fence_get(fence);
		tile->used = false;
		spin_unlock(&drm->tile.lock);
	पूर्ण
पूर्ण

अटल काष्ठा nouveau_drm_tile *
nv10_bo_set_tiling(काष्ठा drm_device *dev, u32 addr,
		   u32 size, u32 pitch, u32 zeta)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_fb *fb = nvxx_fb(&drm->client.device);
	काष्ठा nouveau_drm_tile *tile, *found = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < fb->tile.regions; i++) अणु
		tile = nv10_bo_get_tile_region(dev, i);

		अगर (pitch && !found) अणु
			found = tile;
			जारी;

		पूर्ण अन्यथा अगर (tile && fb->tile.region[i].pitch) अणु
			/* Kill an unused tile region. */
			nv10_bo_update_tile_region(dev, tile, 0, 0, 0, 0);
		पूर्ण

		nv10_bo_put_tile_region(dev, tile, शून्य);
	पूर्ण

	अगर (found)
		nv10_bo_update_tile_region(dev, found, addr, size, pitch, zeta);
	वापस found;
पूर्ण

अटल व्योम
nouveau_bo_del_tपंचांग(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);

	WARN_ON(nvbo->bo.pin_count > 0);
	nouveau_bo_del_io_reserve_lru(bo);
	nv10_bo_put_tile_region(dev, nvbo->tile, शून्य);

	/*
	 * If nouveau_bo_new() allocated this buffer, the GEM object was never
	 * initialized, so करोn't attempt to release it.
	 */
	अगर (bo->base.dev)
		drm_gem_object_release(&bo->base);

	kमुक्त(nvbo);
पूर्ण

अटल अंतरभूत u64
roundup_64(u64 x, u32 y)
अणु
	x += y - 1;
	करो_भाग(x, y);
	वापस x * y;
पूर्ण

अटल व्योम
nouveau_bo_fixup_align(काष्ठा nouveau_bo *nvbo, पूर्णांक *align, u64 *size)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा nvअगर_device *device = &drm->client.device;

	अगर (device->info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		अगर (nvbo->mode) अणु
			अगर (device->info.chipset >= 0x40) अणु
				*align = 65536;
				*size = roundup_64(*size, 64 * nvbo->mode);

			पूर्ण अन्यथा अगर (device->info.chipset >= 0x30) अणु
				*align = 32768;
				*size = roundup_64(*size, 64 * nvbo->mode);

			पूर्ण अन्यथा अगर (device->info.chipset >= 0x20) अणु
				*align = 16384;
				*size = roundup_64(*size, 64 * nvbo->mode);

			पूर्ण अन्यथा अगर (device->info.chipset >= 0x10) अणु
				*align = 16384;
				*size = roundup_64(*size, 32 * nvbo->mode);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		*size = roundup_64(*size, (1 << nvbo->page));
		*align = max((1 <<  nvbo->page), *align);
	पूर्ण

	*size = roundup_64(*size, PAGE_SIZE);
पूर्ण

काष्ठा nouveau_bo *
nouveau_bo_alloc(काष्ठा nouveau_cli *cli, u64 *size, पूर्णांक *align, u32 करोमुख्य,
		 u32 tile_mode, u32 tile_flags)
अणु
	काष्ठा nouveau_drm *drm = cli->drm;
	काष्ठा nouveau_bo *nvbo;
	काष्ठा nvअगर_mmu *mmu = &cli->mmu;
	काष्ठा nvअगर_vmm *vmm = cli->svm.cli ? &cli->svm.vmm : &cli->vmm.vmm;
	पूर्णांक i, pi = -1;

	अगर (!*size) अणु
		NV_WARN(drm, "skipped size %016llx\n", *size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	nvbo = kzalloc(माप(काष्ठा nouveau_bo), GFP_KERNEL);
	अगर (!nvbo)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&nvbo->head);
	INIT_LIST_HEAD(&nvbo->entry);
	INIT_LIST_HEAD(&nvbo->vma_list);
	nvbo->bo.bdev = &drm->tपंचांग.bdev;

	/* This is confusing, and करोesn't actually mean we want an uncached
	 * mapping, but is what NOUVEAU_GEM_DOMAIN_COHERENT माला_लो translated
	 * पूर्णांकo in nouveau_gem_new().
	 */
	अगर (करोमुख्य & NOUVEAU_GEM_DOMAIN_COHERENT) अणु
		/* Determine अगर we can get a cache-coherent map, क्रमcing
		 * uncached mapping अगर we can't.
		 */
		अगर (!nouveau_drm_use_coherent_gpu_mapping(drm))
			nvbo->क्रमce_coherent = true;
	पूर्ण

	अगर (cli->device.info.family >= NV_DEVICE_INFO_V0_FERMI) अणु
		nvbo->kind = (tile_flags & 0x0000ff00) >> 8;
		अगर (!nvअगर_mmu_kind_valid(mmu, nvbo->kind)) अणु
			kमुक्त(nvbo);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		nvbo->comp = mmu->kind[nvbo->kind] != nvbo->kind;
	पूर्ण अन्यथा
	अगर (cli->device.info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		nvbo->kind = (tile_flags & 0x00007f00) >> 8;
		nvbo->comp = (tile_flags & 0x00030000) >> 16;
		अगर (!nvअगर_mmu_kind_valid(mmu, nvbo->kind)) अणु
			kमुक्त(nvbo);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		nvbo->zeta = (tile_flags & 0x00000007);
	पूर्ण
	nvbo->mode = tile_mode;
	nvbo->contig = !(tile_flags & NOUVEAU_GEM_TILE_NONCONTIG);

	/* Determine the desirable target GPU page size क्रम the buffer. */
	क्रम (i = 0; i < vmm->page_nr; i++) अणु
		/* Because we cannot currently allow VMM maps to fail
		 * during buffer migration, we need to determine page
		 * size क्रम the buffer up-front, and pre-allocate its
		 * page tables.
		 *
		 * Skip page sizes that can't support needed करोमुख्यs.
		 */
		अगर (cli->device.info.family > NV_DEVICE_INFO_V0_CURIE &&
		    (करोमुख्य & NOUVEAU_GEM_DOMAIN_VRAM) && !vmm->page[i].vram)
			जारी;
		अगर ((करोमुख्य & NOUVEAU_GEM_DOMAIN_GART) &&
		    (!vmm->page[i].host || vmm->page[i].shअगरt > PAGE_SHIFT))
			जारी;

		/* Select this page size अगर it's the first that supports
		 * the potential memory करोमुख्यs, or when it's compatible
		 * with the requested compression settings.
		 */
		अगर (pi < 0 || !nvbo->comp || vmm->page[i].comp)
			pi = i;

		/* Stop once the buffer is larger than the current page size. */
		अगर (*size >= 1ULL << vmm->page[i].shअगरt)
			अवरोध;
	पूर्ण

	अगर (WARN_ON(pi < 0))
		वापस ERR_PTR(-EINVAL);

	/* Disable compression अगर suitable settings couldn't be found. */
	अगर (nvbo->comp && !vmm->page[pi].comp) अणु
		अगर (mmu->object.oclass >= NVIF_CLASS_MMU_GF100)
			nvbo->kind = mmu->kind[nvbo->kind];
		nvbo->comp = 0;
	पूर्ण
	nvbo->page = vmm->page[pi].shअगरt;

	nouveau_bo_fixup_align(nvbo, align, size);

	वापस nvbo;
पूर्ण

पूर्णांक
nouveau_bo_init(काष्ठा nouveau_bo *nvbo, u64 size, पूर्णांक align, u32 करोमुख्य,
		काष्ठा sg_table *sg, काष्ठा dma_resv *robj)
अणु
	पूर्णांक type = sg ? tपंचांग_bo_type_sg : tपंचांग_bo_type_device;
	पूर्णांक ret;

	nvbo->bo.mem.num_pages = size >> PAGE_SHIFT;
	nouveau_bo_placement_set(nvbo, करोमुख्य, 0);
	INIT_LIST_HEAD(&nvbo->io_reserve_lru);

	ret = tपंचांग_bo_init(nvbo->bo.bdev, &nvbo->bo, size, type,
			  &nvbo->placement, align >> PAGE_SHIFT, false, sg,
			  robj, nouveau_bo_del_tपंचांग);
	अगर (ret) अणु
		/* tपंचांग will call nouveau_bo_del_tपंचांग अगर it fails.. */
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nouveau_bo_new(काष्ठा nouveau_cli *cli, u64 size, पूर्णांक align,
	       uपूर्णांक32_t करोमुख्य, uपूर्णांक32_t tile_mode, uपूर्णांक32_t tile_flags,
	       काष्ठा sg_table *sg, काष्ठा dma_resv *robj,
	       काष्ठा nouveau_bo **pnvbo)
अणु
	काष्ठा nouveau_bo *nvbo;
	पूर्णांक ret;

	nvbo = nouveau_bo_alloc(cli, &size, &align, करोमुख्य, tile_mode,
				tile_flags);
	अगर (IS_ERR(nvbo))
		वापस PTR_ERR(nvbo);

	ret = nouveau_bo_init(nvbo, size, align, करोमुख्य, sg, robj);
	अगर (ret)
		वापस ret;

	*pnvbo = nvbo;
	वापस 0;
पूर्ण

अटल व्योम
set_placement_list(काष्ठा tपंचांग_place *pl, अचिन्हित *n, uपूर्णांक32_t करोमुख्य)
अणु
	*n = 0;

	अगर (करोमुख्य & NOUVEAU_GEM_DOMAIN_VRAM) अणु
		pl[*n].mem_type = TTM_PL_VRAM;
		pl[*n].flags = 0;
		(*n)++;
	पूर्ण
	अगर (करोमुख्य & NOUVEAU_GEM_DOMAIN_GART) अणु
		pl[*n].mem_type = TTM_PL_TT;
		pl[*n].flags = 0;
		(*n)++;
	पूर्ण
	अगर (करोमुख्य & NOUVEAU_GEM_DOMAIN_CPU) अणु
		pl[*n].mem_type = TTM_PL_SYSTEM;
		pl[(*n)++].flags = 0;
	पूर्ण
पूर्ण

अटल व्योम
set_placement_range(काष्ठा nouveau_bo *nvbo, uपूर्णांक32_t करोमुख्य)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	u32 vram_pages = drm->client.device.info.ram_size >> PAGE_SHIFT;
	अचिन्हित i, fpfn, lpfn;

	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CELSIUS &&
	    nvbo->mode && (करोमुख्य & NOUVEAU_GEM_DOMAIN_VRAM) &&
	    nvbo->bo.mem.num_pages < vram_pages / 4) अणु
		/*
		 * Make sure that the color and depth buffers are handled
		 * by independent memory controller units. Up to a 9x
		 * speed up when alpha-blending and depth-test are enabled
		 * at the same समय.
		 */
		अगर (nvbo->zeta) अणु
			fpfn = vram_pages / 2;
			lpfn = ~0;
		पूर्ण अन्यथा अणु
			fpfn = 0;
			lpfn = vram_pages / 2;
		पूर्ण
		क्रम (i = 0; i < nvbo->placement.num_placement; ++i) अणु
			nvbo->placements[i].fpfn = fpfn;
			nvbo->placements[i].lpfn = lpfn;
		पूर्ण
		क्रम (i = 0; i < nvbo->placement.num_busy_placement; ++i) अणु
			nvbo->busy_placements[i].fpfn = fpfn;
			nvbo->busy_placements[i].lpfn = lpfn;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nouveau_bo_placement_set(काष्ठा nouveau_bo *nvbo, uपूर्णांक32_t करोमुख्य,
			 uपूर्णांक32_t busy)
अणु
	काष्ठा tपंचांग_placement *pl = &nvbo->placement;

	pl->placement = nvbo->placements;
	set_placement_list(nvbo->placements, &pl->num_placement, करोमुख्य);

	pl->busy_placement = nvbo->busy_placements;
	set_placement_list(nvbo->busy_placements, &pl->num_busy_placement,
			   करोमुख्य | busy);

	set_placement_range(nvbo, करोमुख्य);
पूर्ण

पूर्णांक
nouveau_bo_pin(काष्ठा nouveau_bo *nvbo, uपूर्णांक32_t करोमुख्य, bool contig)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा tपंचांग_buffer_object *bo = &nvbo->bo;
	bool क्रमce = false, evict = false;
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(bo, false, false, शून्य);
	अगर (ret)
		वापस ret;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    करोमुख्य == NOUVEAU_GEM_DOMAIN_VRAM && contig) अणु
		अगर (!nvbo->contig) अणु
			nvbo->contig = true;
			क्रमce = true;
			evict = true;
		पूर्ण
	पूर्ण

	अगर (nvbo->bo.pin_count) अणु
		bool error = evict;

		चयन (bo->mem.mem_type) अणु
		हाल TTM_PL_VRAM:
			error |= !(करोमुख्य & NOUVEAU_GEM_DOMAIN_VRAM);
			अवरोध;
		हाल TTM_PL_TT:
			error |= !(करोमुख्य & NOUVEAU_GEM_DOMAIN_GART);
		शेष:
			अवरोध;
		पूर्ण

		अगर (error) अणु
			NV_ERROR(drm, "bo %p pinned elsewhere: "
				      "0x%08x vs 0x%08x\n", bo,
				 bo->mem.mem_type, करोमुख्य);
			ret = -EBUSY;
		पूर्ण
		tपंचांग_bo_pin(&nvbo->bo);
		जाओ out;
	पूर्ण

	अगर (evict) अणु
		nouveau_bo_placement_set(nvbo, NOUVEAU_GEM_DOMAIN_GART, 0);
		ret = nouveau_bo_validate(nvbo, false, false);
		अगर (ret)
			जाओ out;
	पूर्ण

	nouveau_bo_placement_set(nvbo, करोमुख्य, 0);
	ret = nouveau_bo_validate(nvbo, false, false);
	अगर (ret)
		जाओ out;

	tपंचांग_bo_pin(&nvbo->bo);

	चयन (bo->mem.mem_type) अणु
	हाल TTM_PL_VRAM:
		drm->gem.vram_available -= bo->base.size;
		अवरोध;
	हाल TTM_PL_TT:
		drm->gem.gart_available -= bo->base.size;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	अगर (क्रमce && ret)
		nvbo->contig = false;
	tपंचांग_bo_unreserve(bo);
	वापस ret;
पूर्ण

पूर्णांक
nouveau_bo_unpin(काष्ठा nouveau_bo *nvbo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा tपंचांग_buffer_object *bo = &nvbo->bo;
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(bo, false, false, शून्य);
	अगर (ret)
		वापस ret;

	tपंचांग_bo_unpin(&nvbo->bo);
	अगर (!nvbo->bo.pin_count) अणु
		चयन (bo->mem.mem_type) अणु
		हाल TTM_PL_VRAM:
			drm->gem.vram_available += bo->base.size;
			अवरोध;
		हाल TTM_PL_TT:
			drm->gem.gart_available += bo->base.size;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	tपंचांग_bo_unreserve(bo);
	वापस 0;
पूर्ण

पूर्णांक
nouveau_bo_map(काष्ठा nouveau_bo *nvbo)
अणु
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(&nvbo->bo, false, false, शून्य);
	अगर (ret)
		वापस ret;

	ret = tपंचांग_bo_kmap(&nvbo->bo, 0, nvbo->bo.mem.num_pages, &nvbo->kmap);

	tपंचांग_bo_unreserve(&nvbo->bo);
	वापस ret;
पूर्ण

व्योम
nouveau_bo_unmap(काष्ठा nouveau_bo *nvbo)
अणु
	अगर (!nvbo)
		वापस;

	tपंचांग_bo_kunmap(&nvbo->kmap);
पूर्ण

व्योम
nouveau_bo_sync_क्रम_device(काष्ठा nouveau_bo *nvbo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा tपंचांग_tt *tपंचांग_dma = (काष्ठा tपंचांग_tt *)nvbo->bo.tपंचांग;
	पूर्णांक i, j;

	अगर (!tपंचांग_dma)
		वापस;
	अगर (!tपंचांग_dma->pages) अणु
		NV_DEBUG(drm, "ttm_dma 0x%p: pages NULL\n", tपंचांग_dma);
		वापस;
	पूर्ण

	/* Don't waste समय looping अगर the object is coherent */
	अगर (nvbo->क्रमce_coherent)
		वापस;

	i = 0;
	जबतक (i < tपंचांग_dma->num_pages) अणु
		काष्ठा page *p = tपंचांग_dma->pages[i];
		माप_प्रकार num_pages = 1;

		क्रम (j = i + 1; j < tपंचांग_dma->num_pages; ++j) अणु
			अगर (++p != tपंचांग_dma->pages[j])
				अवरोध;

			++num_pages;
		पूर्ण
		dma_sync_single_क्रम_device(drm->dev->dev,
					   tपंचांग_dma->dma_address[i],
					   num_pages * PAGE_SIZE, DMA_TO_DEVICE);
		i += num_pages;
	पूर्ण
पूर्ण

व्योम
nouveau_bo_sync_क्रम_cpu(काष्ठा nouveau_bo *nvbo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	काष्ठा tपंचांग_tt *tपंचांग_dma = (काष्ठा tपंचांग_tt *)nvbo->bo.tपंचांग;
	पूर्णांक i, j;

	अगर (!tपंचांग_dma)
		वापस;
	अगर (!tपंचांग_dma->pages) अणु
		NV_DEBUG(drm, "ttm_dma 0x%p: pages NULL\n", tपंचांग_dma);
		वापस;
	पूर्ण

	/* Don't waste समय looping अगर the object is coherent */
	अगर (nvbo->क्रमce_coherent)
		वापस;

	i = 0;
	जबतक (i < tपंचांग_dma->num_pages) अणु
		काष्ठा page *p = tपंचांग_dma->pages[i];
		माप_प्रकार num_pages = 1;

		क्रम (j = i + 1; j < tपंचांग_dma->num_pages; ++j) अणु
			अगर (++p != tपंचांग_dma->pages[j])
				अवरोध;

			++num_pages;
		पूर्ण

		dma_sync_single_क्रम_cpu(drm->dev->dev, tपंचांग_dma->dma_address[i],
					num_pages * PAGE_SIZE, DMA_FROM_DEVICE);
		i += num_pages;
	पूर्ण
पूर्ण

व्योम nouveau_bo_add_io_reserve_lru(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);

	mutex_lock(&drm->tपंचांग.io_reserve_mutex);
	list_move_tail(&nvbo->io_reserve_lru, &drm->tपंचांग.io_reserve_lru);
	mutex_unlock(&drm->tपंचांग.io_reserve_mutex);
पूर्ण

व्योम nouveau_bo_del_io_reserve_lru(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);

	mutex_lock(&drm->tपंचांग.io_reserve_mutex);
	list_del_init(&nvbo->io_reserve_lru);
	mutex_unlock(&drm->tपंचांग.io_reserve_mutex);
पूर्ण

पूर्णांक
nouveau_bo_validate(काष्ठा nouveau_bo *nvbo, bool पूर्णांकerruptible,
		    bool no_रुको_gpu)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु पूर्णांकerruptible, no_रुको_gpu पूर्ण;
	पूर्णांक ret;

	ret = tपंचांग_bo_validate(&nvbo->bo, &nvbo->placement, &ctx);
	अगर (ret)
		वापस ret;

	nouveau_bo_sync_क्रम_device(nvbo);

	वापस 0;
पूर्ण

व्योम
nouveau_bo_wr16(काष्ठा nouveau_bo *nvbo, अचिन्हित index, u16 val)
अणु
	bool is_iomem;
	u16 *mem = tपंचांग_kmap_obj_भव(&nvbo->kmap, &is_iomem);

	mem += index;

	अगर (is_iomem)
		ioग_लिखो16_native(val, (व्योम __क्रमce __iomem *)mem);
	अन्यथा
		*mem = val;
पूर्ण

u32
nouveau_bo_rd32(काष्ठा nouveau_bo *nvbo, अचिन्हित index)
अणु
	bool is_iomem;
	u32 *mem = tपंचांग_kmap_obj_भव(&nvbo->kmap, &is_iomem);

	mem += index;

	अगर (is_iomem)
		वापस ioपढ़ो32_native((व्योम __क्रमce __iomem *)mem);
	अन्यथा
		वापस *mem;
पूर्ण

व्योम
nouveau_bo_wr32(काष्ठा nouveau_bo *nvbo, अचिन्हित index, u32 val)
अणु
	bool is_iomem;
	u32 *mem = tपंचांग_kmap_obj_भव(&nvbo->kmap, &is_iomem);

	mem += index;

	अगर (is_iomem)
		ioग_लिखो32_native(val, (व्योम __क्रमce __iomem *)mem);
	अन्यथा
		*mem = val;
पूर्ण

अटल काष्ठा tपंचांग_tt *
nouveau_tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo, uपूर्णांक32_t page_flags)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);

	अगर (drm->agp.bridge) अणु
		वापस tपंचांग_agp_tt_create(bo, drm->agp.bridge, page_flags);
	पूर्ण
#पूर्ण_अगर

	वापस nouveau_sgdma_create_tपंचांग(bo, page_flags);
पूर्ण

अटल पूर्णांक
nouveau_tपंचांग_tt_bind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग,
		    काष्ठा tपंचांग_resource *reg)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा nouveau_drm *drm = nouveau_bdev(bdev);
#पूर्ण_अगर
	अगर (!reg)
		वापस -EINVAL;
#अगर IS_ENABLED(CONFIG_AGP)
	अगर (drm->agp.bridge)
		वापस tपंचांग_agp_bind(tपंचांग, reg);
#पूर्ण_अगर
	वापस nouveau_sgdma_bind(bdev, tपंचांग, reg);
पूर्ण

अटल व्योम
nouveau_tपंचांग_tt_unbind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा nouveau_drm *drm = nouveau_bdev(bdev);

	अगर (drm->agp.bridge) अणु
		tपंचांग_agp_unbind(tपंचांग);
		वापस;
	पूर्ण
#पूर्ण_अगर
	nouveau_sgdma_unbind(bdev, tपंचांग);
पूर्ण

अटल व्योम
nouveau_bo_evict_flags(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_placement *pl)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);

	चयन (bo->mem.mem_type) अणु
	हाल TTM_PL_VRAM:
		nouveau_bo_placement_set(nvbo, NOUVEAU_GEM_DOMAIN_GART,
					 NOUVEAU_GEM_DOMAIN_CPU);
		अवरोध;
	शेष:
		nouveau_bo_placement_set(nvbo, NOUVEAU_GEM_DOMAIN_CPU, 0);
		अवरोध;
	पूर्ण

	*pl = nvbo->placement;
पूर्ण

अटल पूर्णांक
nouveau_bo_move_prep(काष्ठा nouveau_drm *drm, काष्ठा tपंचांग_buffer_object *bo,
		     काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_mem *old_mem = nouveau_mem(&bo->mem);
	काष्ठा nouveau_mem *new_mem = nouveau_mem(reg);
	काष्ठा nvअगर_vmm *vmm = &drm->client.vmm.vmm;
	पूर्णांक ret;

	ret = nvअगर_vmm_get(vmm, LAZY, false, old_mem->mem.page, 0,
			   old_mem->mem.size, &old_mem->vma[0]);
	अगर (ret)
		वापस ret;

	ret = nvअगर_vmm_get(vmm, LAZY, false, new_mem->mem.page, 0,
			   new_mem->mem.size, &old_mem->vma[1]);
	अगर (ret)
		जाओ करोne;

	ret = nouveau_mem_map(old_mem, vmm, &old_mem->vma[0]);
	अगर (ret)
		जाओ करोne;

	ret = nouveau_mem_map(new_mem, vmm, &old_mem->vma[1]);
करोne:
	अगर (ret) अणु
		nvअगर_vmm_put(vmm, &old_mem->vma[1]);
		nvअगर_vmm_put(vmm, &old_mem->vma[0]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_bo_move_m2mf(काष्ठा tपंचांग_buffer_object *bo, पूर्णांक evict,
		     काष्ठा tपंचांग_operation_ctx *ctx,
		     काष्ठा tपंचांग_resource *new_reg)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_channel *chan = drm->tपंचांग.chan;
	काष्ठा nouveau_cli *cli = (व्योम *)chan->user.client;
	काष्ठा nouveau_fence *fence;
	पूर्णांक ret;

	/* create temporary vmas क्रम the transfer and attach them to the
	 * old nvkm_mem node, these will get cleaned up after tपंचांग has
	 * destroyed the tपंचांग_resource
	 */
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nouveau_bo_move_prep(drm, bo, new_reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (drm_drv_uses_atomic_modeset(drm->dev))
		mutex_lock(&cli->mutex);
	अन्यथा
		mutex_lock_nested(&cli->mutex, SINGLE_DEPTH_NESTING);
	ret = nouveau_fence_sync(nouveau_bo(bo), chan, true, ctx->पूर्णांकerruptible);
	अगर (ret == 0) अणु
		ret = drm->tपंचांग.move(chan, bo, &bo->mem, new_reg);
		अगर (ret == 0) अणु
			ret = nouveau_fence_new(chan, false, &fence);
			अगर (ret == 0) अणु
				ret = tपंचांग_bo_move_accel_cleanup(bo,
								&fence->base,
								evict, false,
								new_reg);
				nouveau_fence_unref(&fence);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&cli->mutex);
	वापस ret;
पूर्ण

व्योम
nouveau_bo_move_init(काष्ठा nouveau_drm *drm)
अणु
	अटल स्थिर काष्ठा _method_table अणु
		स्थिर अक्षर *name;
		पूर्णांक engine;
		s32 oclass;
		पूर्णांक (*exec)(काष्ठा nouveau_channel *,
			    काष्ठा tपंचांग_buffer_object *,
			    काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_resource *);
		पूर्णांक (*init)(काष्ठा nouveau_channel *, u32 handle);
	पूर्ण _methods[] = अणु
		अणु  "COPY", 4, 0xc5b5, nve0_bo_move_copy, nve0_bo_move_init पूर्ण,
		अणु  "GRCE", 0, 0xc5b5, nve0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु  "COPY", 4, 0xc3b5, nve0_bo_move_copy, nve0_bo_move_init पूर्ण,
		अणु  "GRCE", 0, 0xc3b5, nve0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु  "COPY", 4, 0xc1b5, nve0_bo_move_copy, nve0_bo_move_init पूर्ण,
		अणु  "GRCE", 0, 0xc1b5, nve0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु  "COPY", 4, 0xc0b5, nve0_bo_move_copy, nve0_bo_move_init पूर्ण,
		अणु  "GRCE", 0, 0xc0b5, nve0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु  "COPY", 4, 0xb0b5, nve0_bo_move_copy, nve0_bo_move_init पूर्ण,
		अणु  "GRCE", 0, 0xb0b5, nve0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु  "COPY", 4, 0xa0b5, nve0_bo_move_copy, nve0_bo_move_init पूर्ण,
		अणु  "GRCE", 0, 0xa0b5, nve0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु "COPY1", 5, 0x90b8, nvc0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु "COPY0", 4, 0x90b5, nvc0_bo_move_copy, nvc0_bo_move_init पूर्ण,
		अणु  "COPY", 0, 0x85b5, nva3_bo_move_copy, nv50_bo_move_init पूर्ण,
		अणु "CRYPT", 0, 0x74c1, nv84_bo_move_exec, nv50_bo_move_init पूर्ण,
		अणु  "M2MF", 0, 0x9039, nvc0_bo_move_m2mf, nvc0_bo_move_init पूर्ण,
		अणु  "M2MF", 0, 0x5039, nv50_bo_move_m2mf, nv50_bo_move_init पूर्ण,
		अणु  "M2MF", 0, 0x0039, nv04_bo_move_m2mf, nv04_bo_move_init पूर्ण,
		अणुपूर्ण,
	पूर्ण;
	स्थिर काष्ठा _method_table *mthd = _methods;
	स्थिर अक्षर *name = "CPU";
	पूर्णांक ret;

	करो अणु
		काष्ठा nouveau_channel *chan;

		अगर (mthd->engine)
			chan = drm->cechan;
		अन्यथा
			chan = drm->channel;
		अगर (chan == शून्य)
			जारी;

		ret = nvअगर_object_ctor(&chan->user, "ttmBoMove",
				       mthd->oclass | (mthd->engine << 16),
				       mthd->oclass, शून्य, 0,
				       &drm->tपंचांग.copy);
		अगर (ret == 0) अणु
			ret = mthd->init(chan, drm->tपंचांग.copy.handle);
			अगर (ret) अणु
				nvअगर_object_dtor(&drm->tपंचांग.copy);
				जारी;
			पूर्ण

			drm->tपंचांग.move = mthd->exec;
			drm->tपंचांग.chan = chan;
			name = mthd->name;
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((++mthd)->exec);

	NV_INFO(drm, "MM: using %s for buffer copies\n", name);
पूर्ण

अटल व्योम nouveau_bo_move_ntfy(काष्ठा tपंचांग_buffer_object *bo,
				 काष्ठा tपंचांग_resource *new_reg)
अणु
	काष्ठा nouveau_mem *mem = new_reg ? nouveau_mem(new_reg) : शून्य;
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा nouveau_vma *vma;

	/* tपंचांग can now (stupidly) pass the driver bos it didn't create... */
	अगर (bo->destroy != nouveau_bo_del_tपंचांग)
		वापस;

	nouveau_bo_del_io_reserve_lru(bo);

	अगर (mem && new_reg->mem_type != TTM_PL_SYSTEM &&
	    mem->mem.page == nvbo->page) अणु
		list_क्रम_each_entry(vma, &nvbo->vma_list, head) अणु
			nouveau_vma_map(vma, mem);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(vma, &nvbo->vma_list, head) अणु
			WARN_ON(tपंचांग_bo_रुको(bo, false, false));
			nouveau_vma_unmap(vma);
		पूर्ण
	पूर्ण

	अगर (new_reg) अणु
		अगर (new_reg->mm_node)
			nvbo->offset = (new_reg->start << PAGE_SHIFT);
		अन्यथा
			nvbo->offset = 0;
	पूर्ण

पूर्ण

अटल पूर्णांक
nouveau_bo_vm_bind(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_resource *new_reg,
		   काष्ठा nouveau_drm_tile **new_tile)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	u64 offset = new_reg->start << PAGE_SHIFT;

	*new_tile = शून्य;
	अगर (new_reg->mem_type != TTM_PL_VRAM)
		वापस 0;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) अणु
		*new_tile = nv10_bo_set_tiling(dev, offset, bo->base.size,
					       nvbo->mode, nvbo->zeta);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nouveau_bo_vm_cleanup(काष्ठा tपंचांग_buffer_object *bo,
		      काष्ठा nouveau_drm_tile *new_tile,
		      काष्ठा nouveau_drm_tile **old_tile)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा dma_fence *fence = dma_resv_get_excl(bo->base.resv);

	nv10_bo_put_tile_region(dev, *old_tile, fence);
	*old_tile = new_tile;
पूर्ण

अटल पूर्णांक
nouveau_bo_move(काष्ठा tपंचांग_buffer_object *bo, bool evict,
		काष्ठा tपंचांग_operation_ctx *ctx,
		काष्ठा tपंचांग_resource *new_reg,
		काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा tपंचांग_resource *old_reg = &bo->mem;
	काष्ठा nouveau_drm_tile *new_tile = शून्य;
	पूर्णांक ret = 0;


	अगर (new_reg->mem_type == TTM_PL_TT) अणु
		ret = nouveau_tपंचांग_tt_bind(bo->bdev, bo->tपंचांग, new_reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	nouveau_bo_move_ntfy(bo, new_reg);
	ret = tपंचांग_bo_रुको_ctx(bo, ctx);
	अगर (ret)
		जाओ out_ntfy;

	अगर (nvbo->bo.pin_count)
		NV_WARN(drm, "Moving pinned object %p!\n", nvbo);

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nouveau_bo_vm_bind(bo, new_reg, &new_tile);
		अगर (ret)
			जाओ out_ntfy;
	पूर्ण

	/* Fake bo copy. */
	अगर (old_reg->mem_type == TTM_PL_SYSTEM && !bo->tपंचांग) अणु
		tपंचांग_bo_move_null(bo, new_reg);
		जाओ out;
	पूर्ण

	अगर (old_reg->mem_type == TTM_PL_SYSTEM &&
	    new_reg->mem_type == TTM_PL_TT) अणु
		tपंचांग_bo_move_null(bo, new_reg);
		जाओ out;
	पूर्ण

	अगर (old_reg->mem_type == TTM_PL_TT &&
	    new_reg->mem_type == TTM_PL_SYSTEM) अणु
		nouveau_tपंचांग_tt_unbind(bo->bdev, bo->tपंचांग);
		tपंचांग_resource_मुक्त(bo, &bo->mem);
		tपंचांग_bo_assign_mem(bo, new_reg);
		जाओ out;
	पूर्ण

	/* Hardware assisted copy. */
	अगर (drm->tपंचांग.move) अणु
		अगर ((old_reg->mem_type == TTM_PL_SYSTEM &&
		     new_reg->mem_type == TTM_PL_VRAM) ||
		    (old_reg->mem_type == TTM_PL_VRAM &&
		     new_reg->mem_type == TTM_PL_SYSTEM)) अणु
			hop->fpfn = 0;
			hop->lpfn = 0;
			hop->mem_type = TTM_PL_TT;
			hop->flags = 0;
			वापस -EMULTIHOP;
		पूर्ण
		ret = nouveau_bo_move_m2mf(bo, evict, ctx,
					   new_reg);
	पूर्ण अन्यथा
		ret = -ENODEV;

	अगर (ret) अणु
		/* Fallback to software copy. */
		ret = tपंचांग_bo_move_स_नकल(bo, ctx, new_reg);
	पूर्ण

out:
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		अगर (ret)
			nouveau_bo_vm_cleanup(bo, शून्य, &new_tile);
		अन्यथा
			nouveau_bo_vm_cleanup(bo, new_tile, &nvbo->tile);
	पूर्ण
out_ntfy:
	अगर (ret) अणु
		nouveau_bo_move_ntfy(bo, &bo->mem);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_bo_verअगरy_access(काष्ठा tपंचांग_buffer_object *bo, काष्ठा file *filp)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);

	वापस drm_vma_node_verअगरy_access(&nvbo->bo.base.vma_node,
					  filp->निजी_data);
पूर्ण

अटल व्योम
nouveau_tपंचांग_io_mem_मुक्त_locked(काष्ठा nouveau_drm *drm,
			       काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(reg);

	अगर (drm->client.mem->oclass >= NVIF_CLASS_MEM_NV50) अणु
		चयन (reg->mem_type) अणु
		हाल TTM_PL_TT:
			अगर (mem->kind)
				nvअगर_object_unmap_handle(&mem->mem.object);
			अवरोध;
		हाल TTM_PL_VRAM:
			nvअगर_object_unmap_handle(&mem->mem.object);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
nouveau_tपंचांग_io_mem_reserve(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bdev);
	काष्ठा nvkm_device *device = nvxx_device(&drm->client.device);
	काष्ठा nouveau_mem *mem = nouveau_mem(reg);
	काष्ठा nvअगर_mmu *mmu = &drm->client.mmu;
	पूर्णांक ret;

	mutex_lock(&drm->tपंचांग.io_reserve_mutex);
retry:
	चयन (reg->mem_type) अणु
	हाल TTM_PL_SYSTEM:
		/* System memory */
		ret = 0;
		जाओ out;
	हाल TTM_PL_TT:
#अगर IS_ENABLED(CONFIG_AGP)
		अगर (drm->agp.bridge) अणु
			reg->bus.offset = (reg->start << PAGE_SHIFT) +
				drm->agp.base;
			reg->bus.is_iomem = !drm->agp.cma;
			reg->bus.caching = tपंचांग_ग_लिखो_combined;
		पूर्ण
#पूर्ण_अगर
		अगर (drm->client.mem->oclass < NVIF_CLASS_MEM_NV50 ||
		    !mem->kind) अणु
			/* untiled */
			ret = 0;
			अवरोध;
		पूर्ण
		fallthrough;	/* tiled memory */
	हाल TTM_PL_VRAM:
		reg->bus.offset = (reg->start << PAGE_SHIFT) +
			device->func->resource_addr(device, 1);
		reg->bus.is_iomem = true;

		/* Some BARs करो not support being ioremapped WC */
		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA &&
		    mmu->type[drm->tपंचांग.type_vram].type & NVIF_MEM_UNCACHED)
			reg->bus.caching = tपंचांग_uncached;
		अन्यथा
			reg->bus.caching = tपंचांग_ग_लिखो_combined;

		अगर (drm->client.mem->oclass >= NVIF_CLASS_MEM_NV50) अणु
			जोड़ अणु
				काष्ठा nv50_mem_map_v0 nv50;
				काष्ठा gf100_mem_map_v0 gf100;
			पूर्ण args;
			u64 handle, length;
			u32 argc = 0;

			चयन (mem->mem.object.oclass) अणु
			हाल NVIF_CLASS_MEM_NV50:
				args.nv50.version = 0;
				args.nv50.ro = 0;
				args.nv50.kind = mem->kind;
				args.nv50.comp = mem->comp;
				argc = माप(args.nv50);
				अवरोध;
			हाल NVIF_CLASS_MEM_GF100:
				args.gf100.version = 0;
				args.gf100.ro = 0;
				args.gf100.kind = mem->kind;
				argc = माप(args.gf100);
				अवरोध;
			शेष:
				WARN_ON(1);
				अवरोध;
			पूर्ण

			ret = nvअगर_object_map_handle(&mem->mem.object,
						     &args, argc,
						     &handle, &length);
			अगर (ret != 1) अणु
				अगर (WARN_ON(ret == 0))
					ret = -EINVAL;
				जाओ out;
			पूर्ण

			reg->bus.offset = handle;
		पूर्ण
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	अगर (ret == -ENOSPC) अणु
		काष्ठा nouveau_bo *nvbo;

		nvbo = list_first_entry_or_null(&drm->tपंचांग.io_reserve_lru,
						typeof(*nvbo),
						io_reserve_lru);
		अगर (nvbo) अणु
			list_del_init(&nvbo->io_reserve_lru);
			drm_vma_node_unmap(&nvbo->bo.base.vma_node,
					   bdev->dev_mapping);
			nouveau_tपंचांग_io_mem_मुक्त_locked(drm, &nvbo->bo.mem);
			जाओ retry;
		पूर्ण

	पूर्ण
	mutex_unlock(&drm->tपंचांग.io_reserve_mutex);
	वापस ret;
पूर्ण

अटल व्योम
nouveau_tपंचांग_io_mem_मुक्त(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_resource *reg)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bdev);

	mutex_lock(&drm->tपंचांग.io_reserve_mutex);
	nouveau_tपंचांग_io_mem_मुक्त_locked(drm, reg);
	mutex_unlock(&drm->tपंचांग.io_reserve_mutex);
पूर्ण

vm_fault_t nouveau_tपंचांग_fault_reserve_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा nouveau_drm *drm = nouveau_bdev(bo->bdev);
	काष्ठा nouveau_bo *nvbo = nouveau_bo(bo);
	काष्ठा nvkm_device *device = nvxx_device(&drm->client.device);
	u32 mappable = device->func->resource_size(device, 1) >> PAGE_SHIFT;
	पूर्णांक i, ret;

	/* as दीर्घ as the bo isn't in vram, and isn't tiled, we've got
	 * nothing to करो here.
	 */
	अगर (bo->mem.mem_type != TTM_PL_VRAM) अणु
		अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA ||
		    !nvbo->kind)
			वापस 0;

		अगर (bo->mem.mem_type != TTM_PL_SYSTEM)
			वापस 0;

		nouveau_bo_placement_set(nvbo, NOUVEAU_GEM_DOMAIN_GART, 0);

	पूर्ण अन्यथा अणु
		/* make sure bo is in mappable vram */
		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA ||
		    bo->mem.start + bo->mem.num_pages < mappable)
			वापस 0;

		क्रम (i = 0; i < nvbo->placement.num_placement; ++i) अणु
			nvbo->placements[i].fpfn = 0;
			nvbo->placements[i].lpfn = mappable;
		पूर्ण

		क्रम (i = 0; i < nvbo->placement.num_busy_placement; ++i) अणु
			nvbo->busy_placements[i].fpfn = 0;
			nvbo->busy_placements[i].lpfn = mappable;
		पूर्ण

		nouveau_bo_placement_set(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, 0);
	पूर्ण

	ret = nouveau_bo_validate(nvbo, false, false);
	अगर (unlikely(ret == -EBUSY || ret == -ERESTARTSYS))
		वापस VM_FAULT_NOPAGE;
	अन्यथा अगर (unlikely(ret))
		वापस VM_FAULT_SIGBUS;

	tपंचांग_bo_move_to_lru_tail_unlocked(bo);
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_tपंचांग_tt_populate(काष्ठा tपंचांग_device *bdev,
			काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा tपंचांग_tt *tपंचांग_dma = (व्योम *)tपंचांग;
	काष्ठा nouveau_drm *drm;
	काष्ठा device *dev;
	bool slave = !!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG);

	अगर (tपंचांग_tt_is_populated(tपंचांग))
		वापस 0;

	अगर (slave && tपंचांग->sg) अणु
		drm_prime_sg_to_dma_addr_array(tपंचांग->sg, tपंचांग_dma->dma_address,
					       tपंचांग->num_pages);
		वापस 0;
	पूर्ण

	drm = nouveau_bdev(bdev);
	dev = drm->dev->dev;

	वापस tपंचांग_pool_alloc(&drm->tपंचांग.bdev.pool, tपंचांग, ctx);
पूर्ण

अटल व्योम
nouveau_tपंचांग_tt_unpopulate(काष्ठा tपंचांग_device *bdev,
			  काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा nouveau_drm *drm;
	काष्ठा device *dev;
	bool slave = !!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG);

	अगर (slave)
		वापस;

	drm = nouveau_bdev(bdev);
	dev = drm->dev->dev;

	वापस tपंचांग_pool_मुक्त(&drm->tपंचांग.bdev.pool, tपंचांग);
पूर्ण

अटल व्योम
nouveau_tपंचांग_tt_destroy(काष्ठा tपंचांग_device *bdev,
		       काष्ठा tपंचांग_tt *tपंचांग)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा nouveau_drm *drm = nouveau_bdev(bdev);
	अगर (drm->agp.bridge) अणु
		tपंचांग_agp_unbind(tपंचांग);
		tपंचांग_tt_destroy_common(bdev, tपंचांग);
		tपंचांग_agp_destroy(tपंचांग);
		वापस;
	पूर्ण
#पूर्ण_अगर
	nouveau_sgdma_destroy(bdev, tपंचांग);
पूर्ण

व्योम
nouveau_bo_fence(काष्ठा nouveau_bo *nvbo, काष्ठा nouveau_fence *fence, bool exclusive)
अणु
	काष्ठा dma_resv *resv = nvbo->bo.base.resv;

	अगर (exclusive)
		dma_resv_add_excl_fence(resv, &fence->base);
	अन्यथा अगर (fence)
		dma_resv_add_shared_fence(resv, &fence->base);
पूर्ण

अटल व्योम
nouveau_bo_delete_mem_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	nouveau_bo_move_ntfy(bo, शून्य);
पूर्ण

काष्ठा tपंचांग_device_funcs nouveau_bo_driver = अणु
	.tपंचांग_tt_create = &nouveau_tपंचांग_tt_create,
	.tपंचांग_tt_populate = &nouveau_tपंचांग_tt_populate,
	.tपंचांग_tt_unpopulate = &nouveau_tपंचांग_tt_unpopulate,
	.tपंचांग_tt_destroy = &nouveau_tपंचांग_tt_destroy,
	.eviction_valuable = tपंचांग_bo_eviction_valuable,
	.evict_flags = nouveau_bo_evict_flags,
	.delete_mem_notअगरy = nouveau_bo_delete_mem_notअगरy,
	.move = nouveau_bo_move,
	.verअगरy_access = nouveau_bo_verअगरy_access,
	.io_mem_reserve = &nouveau_tपंचांग_io_mem_reserve,
	.io_mem_मुक्त = &nouveau_tपंचांग_io_mem_मुक्त,
पूर्ण;
