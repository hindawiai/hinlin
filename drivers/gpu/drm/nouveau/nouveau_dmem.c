<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "nouveau_dmem.h"
#समावेश "nouveau_drv.h"
#समावेश "nouveau_chan.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_mem.h"
#समावेश "nouveau_bo.h"
#समावेश "nouveau_svm.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/object.h>
#समावेश <nvअगर/push906f.h>
#समावेश <nvअगर/अगर000c.h>
#समावेश <nvअगर/अगर500b.h>
#समावेश <nvअगर/अगर900b.h>
#समावेश <nvअगर/अगर000c.h>

#समावेश <nvhw/class/cla0b5.h>

#समावेश <linux/sched/mm.h>
#समावेश <linux/hmm.h>

/*
 * FIXME: this is ugly right now we are using TTM to allocate vram and we pin
 * it in vram जबतक in use. We likely want to overhaul memory management क्रम
 * nouveau to be more page like (not necessarily with प्रणाली page size but a
 * bigger page size) at lowest level and have some shim layer on top that would
 * provide the same functionality as TTM.
 */
#घोषणा DMEM_CHUNK_SIZE (2UL << 20)
#घोषणा DMEM_CHUNK_NPAGES (DMEM_CHUNK_SIZE >> PAGE_SHIFT)

क्रमागत nouveau_aper अणु
	NOUVEAU_APER_VIRT,
	NOUVEAU_APER_VRAM,
	NOUVEAU_APER_HOST,
पूर्ण;

प्रकार पूर्णांक (*nouveau_migrate_copy_t)(काष्ठा nouveau_drm *drm, u64 npages,
				      क्रमागत nouveau_aper, u64 dst_addr,
				      क्रमागत nouveau_aper, u64 src_addr);
प्रकार पूर्णांक (*nouveau_clear_page_t)(काष्ठा nouveau_drm *drm, u32 length,
				      क्रमागत nouveau_aper, u64 dst_addr);

काष्ठा nouveau_dmem_chunk अणु
	काष्ठा list_head list;
	काष्ठा nouveau_bo *bo;
	काष्ठा nouveau_drm *drm;
	अचिन्हित दीर्घ सुस्मृतिated;
	काष्ठा dev_pagemap pagemap;
पूर्ण;

काष्ठा nouveau_dmem_migrate अणु
	nouveau_migrate_copy_t copy_func;
	nouveau_clear_page_t clear_func;
	काष्ठा nouveau_channel *chan;
पूर्ण;

काष्ठा nouveau_dmem अणु
	काष्ठा nouveau_drm *drm;
	काष्ठा nouveau_dmem_migrate migrate;
	काष्ठा list_head chunks;
	काष्ठा mutex mutex;
	काष्ठा page *मुक्त_pages;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा nouveau_dmem_chunk *nouveau_page_to_chunk(काष्ठा page *page)
अणु
	वापस container_of(page->pgmap, काष्ठा nouveau_dmem_chunk, pagemap);
पूर्ण

अटल काष्ठा nouveau_drm *page_to_drm(काष्ठा page *page)
अणु
	काष्ठा nouveau_dmem_chunk *chunk = nouveau_page_to_chunk(page);

	वापस chunk->drm;
पूर्ण

अचिन्हित दीर्घ nouveau_dmem_page_addr(काष्ठा page *page)
अणु
	काष्ठा nouveau_dmem_chunk *chunk = nouveau_page_to_chunk(page);
	अचिन्हित दीर्घ off = (page_to_pfn(page) << PAGE_SHIFT) -
				chunk->pagemap.range.start;

	वापस chunk->bo->offset + off;
पूर्ण

अटल व्योम nouveau_dmem_page_मुक्त(काष्ठा page *page)
अणु
	काष्ठा nouveau_dmem_chunk *chunk = nouveau_page_to_chunk(page);
	काष्ठा nouveau_dmem *dmem = chunk->drm->dmem;

	spin_lock(&dmem->lock);
	page->zone_device_data = dmem->मुक्त_pages;
	dmem->मुक्त_pages = page;

	WARN_ON(!chunk->सुस्मृतिated);
	chunk->सुस्मृतिated--;
	/*
	 * FIXME when chunk->सुस्मृतिated reach 0 we should add the chunk to
	 * a reclaim list so that it can be मुक्तd in हाल of memory pressure.
	 */
	spin_unlock(&dmem->lock);
पूर्ण

अटल व्योम nouveau_dmem_fence_करोne(काष्ठा nouveau_fence **fence)
अणु
	अगर (fence) अणु
		nouveau_fence_रुको(*fence, true, false);
		nouveau_fence_unref(fence);
	पूर्ण अन्यथा अणु
		/*
		 * FIXME रुको क्रम channel to be IDLE beक्रमe calling finalizing
		 * the hmem object.
		 */
	पूर्ण
पूर्ण

अटल vm_fault_t nouveau_dmem_fault_copy_one(काष्ठा nouveau_drm *drm,
		काष्ठा vm_fault *vmf, काष्ठा migrate_vma *args,
		dma_addr_t *dma_addr)
अणु
	काष्ठा device *dev = drm->dev->dev;
	काष्ठा page *dpage, *spage;
	काष्ठा nouveau_svmm *svmm;

	spage = migrate_pfn_to_page(args->src[0]);
	अगर (!spage || !(args->src[0] & MIGRATE_PFN_MIGRATE))
		वापस 0;

	dpage = alloc_page_vma(GFP_HIGHUSER, vmf->vma, vmf->address);
	अगर (!dpage)
		वापस VM_FAULT_SIGBUS;
	lock_page(dpage);

	*dma_addr = dma_map_page(dev, dpage, 0, PAGE_SIZE, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, *dma_addr))
		जाओ error_मुक्त_page;

	svmm = spage->zone_device_data;
	mutex_lock(&svmm->mutex);
	nouveau_svmm_invalidate(svmm, args->start, args->end);
	अगर (drm->dmem->migrate.copy_func(drm, 1, NOUVEAU_APER_HOST, *dma_addr,
			NOUVEAU_APER_VRAM, nouveau_dmem_page_addr(spage)))
		जाओ error_dma_unmap;
	mutex_unlock(&svmm->mutex);

	args->dst[0] = migrate_pfn(page_to_pfn(dpage)) | MIGRATE_PFN_LOCKED;
	वापस 0;

error_dma_unmap:
	mutex_unlock(&svmm->mutex);
	dma_unmap_page(dev, *dma_addr, PAGE_SIZE, DMA_BIसूचीECTIONAL);
error_मुक्त_page:
	__मुक्त_page(dpage);
	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल vm_fault_t nouveau_dmem_migrate_to_ram(काष्ठा vm_fault *vmf)
अणु
	काष्ठा nouveau_drm *drm = page_to_drm(vmf->page);
	काष्ठा nouveau_dmem *dmem = drm->dmem;
	काष्ठा nouveau_fence *fence;
	अचिन्हित दीर्घ src = 0, dst = 0;
	dma_addr_t dma_addr = 0;
	vm_fault_t ret;
	काष्ठा migrate_vma args = अणु
		.vma		= vmf->vma,
		.start		= vmf->address,
		.end		= vmf->address + PAGE_SIZE,
		.src		= &src,
		.dst		= &dst,
		.pgmap_owner	= drm->dev,
		.flags		= MIGRATE_VMA_SELECT_DEVICE_PRIVATE,
	पूर्ण;

	/*
	 * FIXME what we really want is to find some heuristic to migrate more
	 * than just one page on CPU fault. When such fault happens it is very
	 * likely that more surrounding page will CPU fault too.
	 */
	अगर (migrate_vma_setup(&args) < 0)
		वापस VM_FAULT_SIGBUS;
	अगर (!args.cpages)
		वापस 0;

	ret = nouveau_dmem_fault_copy_one(drm, vmf, &args, &dma_addr);
	अगर (ret || dst == 0)
		जाओ करोne;

	nouveau_fence_new(dmem->migrate.chan, false, &fence);
	migrate_vma_pages(&args);
	nouveau_dmem_fence_करोne(&fence);
	dma_unmap_page(drm->dev->dev, dma_addr, PAGE_SIZE, DMA_BIसूचीECTIONAL);
करोne:
	migrate_vma_finalize(&args);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pagemap_ops nouveau_dmem_pagemap_ops = अणु
	.page_मुक्त		= nouveau_dmem_page_मुक्त,
	.migrate_to_ram		= nouveau_dmem_migrate_to_ram,
पूर्ण;

अटल पूर्णांक
nouveau_dmem_chunk_alloc(काष्ठा nouveau_drm *drm, काष्ठा page **ppage)
अणु
	काष्ठा nouveau_dmem_chunk *chunk;
	काष्ठा resource *res;
	काष्ठा page *page;
	व्योम *ptr;
	अचिन्हित दीर्घ i, pfn_first;
	पूर्णांक ret;

	chunk = kzalloc(माप(*chunk), GFP_KERNEL);
	अगर (chunk == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Allocate unused physical address space क्रम device निजी pages. */
	res = request_मुक्त_mem_region(&iomem_resource, DMEM_CHUNK_SIZE,
				      "nouveau_dmem");
	अगर (IS_ERR(res)) अणु
		ret = PTR_ERR(res);
		जाओ out_मुक्त;
	पूर्ण

	chunk->drm = drm;
	chunk->pagemap.type = MEMORY_DEVICE_PRIVATE;
	chunk->pagemap.range.start = res->start;
	chunk->pagemap.range.end = res->end;
	chunk->pagemap.nr_range = 1;
	chunk->pagemap.ops = &nouveau_dmem_pagemap_ops;
	chunk->pagemap.owner = drm->dev;

	ret = nouveau_bo_new(&drm->client, DMEM_CHUNK_SIZE, 0,
			     NOUVEAU_GEM_DOMAIN_VRAM, 0, 0, शून्य, शून्य,
			     &chunk->bo);
	अगर (ret)
		जाओ out_release;

	ret = nouveau_bo_pin(chunk->bo, NOUVEAU_GEM_DOMAIN_VRAM, false);
	अगर (ret)
		जाओ out_bo_मुक्त;

	ptr = memremap_pages(&chunk->pagemap, numa_node_id());
	अगर (IS_ERR(ptr)) अणु
		ret = PTR_ERR(ptr);
		जाओ out_bo_unpin;
	पूर्ण

	mutex_lock(&drm->dmem->mutex);
	list_add(&chunk->list, &drm->dmem->chunks);
	mutex_unlock(&drm->dmem->mutex);

	pfn_first = chunk->pagemap.range.start >> PAGE_SHIFT;
	page = pfn_to_page(pfn_first);
	spin_lock(&drm->dmem->lock);
	क्रम (i = 0; i < DMEM_CHUNK_NPAGES - 1; ++i, ++page) अणु
		page->zone_device_data = drm->dmem->मुक्त_pages;
		drm->dmem->मुक्त_pages = page;
	पूर्ण
	*ppage = page;
	chunk->सुस्मृतिated++;
	spin_unlock(&drm->dmem->lock);

	NV_INFO(drm, "DMEM: registered %ldMB of device memory\n",
		DMEM_CHUNK_SIZE >> 20);

	वापस 0;

out_bo_unpin:
	nouveau_bo_unpin(chunk->bo);
out_bo_मुक्त:
	nouveau_bo_ref(शून्य, &chunk->bo);
out_release:
	release_mem_region(chunk->pagemap.range.start, range_len(&chunk->pagemap.range));
out_मुक्त:
	kमुक्त(chunk);
out:
	वापस ret;
पूर्ण

अटल काष्ठा page *
nouveau_dmem_page_alloc_locked(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_dmem_chunk *chunk;
	काष्ठा page *page = शून्य;
	पूर्णांक ret;

	spin_lock(&drm->dmem->lock);
	अगर (drm->dmem->मुक्त_pages) अणु
		page = drm->dmem->मुक्त_pages;
		drm->dmem->मुक्त_pages = page->zone_device_data;
		chunk = nouveau_page_to_chunk(page);
		chunk->सुस्मृतिated++;
		spin_unlock(&drm->dmem->lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&drm->dmem->lock);
		ret = nouveau_dmem_chunk_alloc(drm, &page);
		अगर (ret)
			वापस शून्य;
	पूर्ण

	get_page(page);
	lock_page(page);
	वापस page;
पूर्ण

अटल व्योम
nouveau_dmem_page_मुक्त_locked(काष्ठा nouveau_drm *drm, काष्ठा page *page)
अणु
	unlock_page(page);
	put_page(page);
पूर्ण

व्योम
nouveau_dmem_resume(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_dmem_chunk *chunk;
	पूर्णांक ret;

	अगर (drm->dmem == शून्य)
		वापस;

	mutex_lock(&drm->dmem->mutex);
	list_क्रम_each_entry(chunk, &drm->dmem->chunks, list) अणु
		ret = nouveau_bo_pin(chunk->bo, NOUVEAU_GEM_DOMAIN_VRAM, false);
		/* FIXME handle pin failure */
		WARN_ON(ret);
	पूर्ण
	mutex_unlock(&drm->dmem->mutex);
पूर्ण

व्योम
nouveau_dmem_suspend(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_dmem_chunk *chunk;

	अगर (drm->dmem == शून्य)
		वापस;

	mutex_lock(&drm->dmem->mutex);
	list_क्रम_each_entry(chunk, &drm->dmem->chunks, list)
		nouveau_bo_unpin(chunk->bo);
	mutex_unlock(&drm->dmem->mutex);
पूर्ण

व्योम
nouveau_dmem_fini(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_dmem_chunk *chunk, *पंचांगp;

	अगर (drm->dmem == शून्य)
		वापस;

	mutex_lock(&drm->dmem->mutex);

	list_क्रम_each_entry_safe(chunk, पंचांगp, &drm->dmem->chunks, list) अणु
		nouveau_bo_unpin(chunk->bo);
		nouveau_bo_ref(शून्य, &chunk->bo);
		list_del(&chunk->list);
		memunmap_pages(&chunk->pagemap);
		release_mem_region(chunk->pagemap.range.start,
				   range_len(&chunk->pagemap.range));
		kमुक्त(chunk);
	पूर्ण

	mutex_unlock(&drm->dmem->mutex);
पूर्ण

अटल पूर्णांक
nvc0b5_migrate_copy(काष्ठा nouveau_drm *drm, u64 npages,
		    क्रमागत nouveau_aper dst_aper, u64 dst_addr,
		    क्रमागत nouveau_aper src_aper, u64 src_addr)
अणु
	काष्ठा nvअगर_push *push = drm->dmem->migrate.chan->chan.push;
	u32 launch_dma = 0;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 13);
	अगर (ret)
		वापस ret;

	अगर (src_aper != NOUVEAU_APER_VIRT) अणु
		चयन (src_aper) अणु
		हाल NOUVEAU_APER_VRAM:
			PUSH_IMMD(push, NVA0B5, SET_SRC_PHYS_MODE,
				  NVDEF(NVA0B5, SET_SRC_PHYS_MODE, TARGET, LOCAL_FB));
			अवरोध;
		हाल NOUVEAU_APER_HOST:
			PUSH_IMMD(push, NVA0B5, SET_SRC_PHYS_MODE,
				  NVDEF(NVA0B5, SET_SRC_PHYS_MODE, TARGET, COHERENT_SYSMEM));
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		launch_dma |= NVDEF(NVA0B5, LAUNCH_DMA, SRC_TYPE, PHYSICAL);
	पूर्ण

	अगर (dst_aper != NOUVEAU_APER_VIRT) अणु
		चयन (dst_aper) अणु
		हाल NOUVEAU_APER_VRAM:
			PUSH_IMMD(push, NVA0B5, SET_DST_PHYS_MODE,
				  NVDEF(NVA0B5, SET_DST_PHYS_MODE, TARGET, LOCAL_FB));
			अवरोध;
		हाल NOUVEAU_APER_HOST:
			PUSH_IMMD(push, NVA0B5, SET_DST_PHYS_MODE,
				  NVDEF(NVA0B5, SET_DST_PHYS_MODE, TARGET, COHERENT_SYSMEM));
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		launch_dma |= NVDEF(NVA0B5, LAUNCH_DMA, DST_TYPE, PHYSICAL);
	पूर्ण

	PUSH_MTHD(push, NVA0B5, OFFSET_IN_UPPER,
		  NVVAL(NVA0B5, OFFSET_IN_UPPER, UPPER, upper_32_bits(src_addr)),

				OFFSET_IN_LOWER, lower_32_bits(src_addr),

				OFFSET_OUT_UPPER,
		  NVVAL(NVA0B5, OFFSET_OUT_UPPER, UPPER, upper_32_bits(dst_addr)),

				OFFSET_OUT_LOWER, lower_32_bits(dst_addr),
				PITCH_IN, PAGE_SIZE,
				PITCH_OUT, PAGE_SIZE,
				LINE_LENGTH_IN, PAGE_SIZE,
				LINE_COUNT, npages);

	PUSH_MTHD(push, NVA0B5, LAUNCH_DMA, launch_dma |
		  NVDEF(NVA0B5, LAUNCH_DMA, DATA_TRANSFER_TYPE, NON_PIPELINED) |
		  NVDEF(NVA0B5, LAUNCH_DMA, FLUSH_ENABLE, TRUE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, SEMAPHORE_TYPE, NONE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, INTERRUPT_TYPE, NONE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, SRC_MEMORY_LAYOUT, PITCH) |
		  NVDEF(NVA0B5, LAUNCH_DMA, DST_MEMORY_LAYOUT, PITCH) |
		  NVDEF(NVA0B5, LAUNCH_DMA, MULTI_LINE_ENABLE, TRUE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, REMAP_ENABLE, FALSE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, BYPASS_L2, USE_PTE_SETTING));
	वापस 0;
पूर्ण

अटल पूर्णांक
nvc0b5_migrate_clear(काष्ठा nouveau_drm *drm, u32 length,
		     क्रमागत nouveau_aper dst_aper, u64 dst_addr)
अणु
	काष्ठा nvअगर_push *push = drm->dmem->migrate.chan->chan.push;
	u32 launch_dma = 0;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 12);
	अगर (ret)
		वापस ret;

	चयन (dst_aper) अणु
	हाल NOUVEAU_APER_VRAM:
		PUSH_IMMD(push, NVA0B5, SET_DST_PHYS_MODE,
			  NVDEF(NVA0B5, SET_DST_PHYS_MODE, TARGET, LOCAL_FB));
		अवरोध;
	हाल NOUVEAU_APER_HOST:
		PUSH_IMMD(push, NVA0B5, SET_DST_PHYS_MODE,
			  NVDEF(NVA0B5, SET_DST_PHYS_MODE, TARGET, COHERENT_SYSMEM));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	launch_dma |= NVDEF(NVA0B5, LAUNCH_DMA, DST_TYPE, PHYSICAL);

	PUSH_MTHD(push, NVA0B5, SET_REMAP_CONST_A, 0,
				SET_REMAP_CONST_B, 0,

				SET_REMAP_COMPONENTS,
		  NVDEF(NVA0B5, SET_REMAP_COMPONENTS, DST_X, CONST_A) |
		  NVDEF(NVA0B5, SET_REMAP_COMPONENTS, DST_Y, CONST_B) |
		  NVDEF(NVA0B5, SET_REMAP_COMPONENTS, COMPONENT_SIZE, FOUR) |
		  NVDEF(NVA0B5, SET_REMAP_COMPONENTS, NUM_DST_COMPONENTS, TWO));

	PUSH_MTHD(push, NVA0B5, OFFSET_OUT_UPPER,
		  NVVAL(NVA0B5, OFFSET_OUT_UPPER, UPPER, upper_32_bits(dst_addr)),

				OFFSET_OUT_LOWER, lower_32_bits(dst_addr));

	PUSH_MTHD(push, NVA0B5, LINE_LENGTH_IN, length >> 3);

	PUSH_MTHD(push, NVA0B5, LAUNCH_DMA, launch_dma |
		  NVDEF(NVA0B5, LAUNCH_DMA, DATA_TRANSFER_TYPE, NON_PIPELINED) |
		  NVDEF(NVA0B5, LAUNCH_DMA, FLUSH_ENABLE, TRUE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, SEMAPHORE_TYPE, NONE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, INTERRUPT_TYPE, NONE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, SRC_MEMORY_LAYOUT, PITCH) |
		  NVDEF(NVA0B5, LAUNCH_DMA, DST_MEMORY_LAYOUT, PITCH) |
		  NVDEF(NVA0B5, LAUNCH_DMA, MULTI_LINE_ENABLE, FALSE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, REMAP_ENABLE, TRUE) |
		  NVDEF(NVA0B5, LAUNCH_DMA, BYPASS_L2, USE_PTE_SETTING));
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_dmem_migrate_init(काष्ठा nouveau_drm *drm)
अणु
	चयन (drm->tपंचांग.copy.oclass) अणु
	हाल PASCAL_DMA_COPY_A:
	हाल PASCAL_DMA_COPY_B:
	हाल  VOLTA_DMA_COPY_A:
	हाल TURING_DMA_COPY_A:
		drm->dmem->migrate.copy_func = nvc0b5_migrate_copy;
		drm->dmem->migrate.clear_func = nvc0b5_migrate_clear;
		drm->dmem->migrate.chan = drm->tपंचांग.chan;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENODEV;
पूर्ण

व्योम
nouveau_dmem_init(काष्ठा nouveau_drm *drm)
अणु
	पूर्णांक ret;

	/* This only make sense on PASCAL or newer */
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_PASCAL)
		वापस;

	अगर (!(drm->dmem = kzalloc(माप(*drm->dmem), GFP_KERNEL)))
		वापस;

	drm->dmem->drm = drm;
	mutex_init(&drm->dmem->mutex);
	INIT_LIST_HEAD(&drm->dmem->chunks);
	mutex_init(&drm->dmem->mutex);
	spin_lock_init(&drm->dmem->lock);

	/* Initialize migration dma helpers beक्रमe रेजिस्टरing memory */
	ret = nouveau_dmem_migrate_init(drm);
	अगर (ret) अणु
		kमुक्त(drm->dmem);
		drm->dmem = शून्य;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ nouveau_dmem_migrate_copy_one(काष्ठा nouveau_drm *drm,
		काष्ठा nouveau_svmm *svmm, अचिन्हित दीर्घ src,
		dma_addr_t *dma_addr, u64 *pfn)
अणु
	काष्ठा device *dev = drm->dev->dev;
	काष्ठा page *dpage, *spage;
	अचिन्हित दीर्घ paddr;

	spage = migrate_pfn_to_page(src);
	अगर (!(src & MIGRATE_PFN_MIGRATE))
		जाओ out;

	dpage = nouveau_dmem_page_alloc_locked(drm);
	अगर (!dpage)
		जाओ out;

	paddr = nouveau_dmem_page_addr(dpage);
	अगर (spage) अणु
		*dma_addr = dma_map_page(dev, spage, 0, page_size(spage),
					 DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(dev, *dma_addr))
			जाओ out_मुक्त_page;
		अगर (drm->dmem->migrate.copy_func(drm, 1,
			NOUVEAU_APER_VRAM, paddr, NOUVEAU_APER_HOST, *dma_addr))
			जाओ out_dma_unmap;
	पूर्ण अन्यथा अणु
		*dma_addr = DMA_MAPPING_ERROR;
		अगर (drm->dmem->migrate.clear_func(drm, page_size(dpage),
			NOUVEAU_APER_VRAM, paddr))
			जाओ out_मुक्त_page;
	पूर्ण

	dpage->zone_device_data = svmm;
	*pfn = NVIF_VMM_PFNMAP_V0_V | NVIF_VMM_PFNMAP_V0_VRAM |
		((paddr >> PAGE_SHIFT) << NVIF_VMM_PFNMAP_V0_ADDR_SHIFT);
	अगर (src & MIGRATE_PFN_WRITE)
		*pfn |= NVIF_VMM_PFNMAP_V0_W;
	वापस migrate_pfn(page_to_pfn(dpage)) | MIGRATE_PFN_LOCKED;

out_dma_unmap:
	dma_unmap_page(dev, *dma_addr, PAGE_SIZE, DMA_BIसूचीECTIONAL);
out_मुक्त_page:
	nouveau_dmem_page_मुक्त_locked(drm, dpage);
out:
	*pfn = NVIF_VMM_PFNMAP_V0_NONE;
	वापस 0;
पूर्ण

अटल व्योम nouveau_dmem_migrate_chunk(काष्ठा nouveau_drm *drm,
		काष्ठा nouveau_svmm *svmm, काष्ठा migrate_vma *args,
		dma_addr_t *dma_addrs, u64 *pfns)
अणु
	काष्ठा nouveau_fence *fence;
	अचिन्हित दीर्घ addr = args->start, nr_dma = 0, i;

	क्रम (i = 0; addr < args->end; i++) अणु
		args->dst[i] = nouveau_dmem_migrate_copy_one(drm, svmm,
				args->src[i], dma_addrs + nr_dma, pfns + i);
		अगर (!dma_mapping_error(drm->dev->dev, dma_addrs[nr_dma]))
			nr_dma++;
		addr += PAGE_SIZE;
	पूर्ण

	nouveau_fence_new(drm->dmem->migrate.chan, false, &fence);
	migrate_vma_pages(args);
	nouveau_dmem_fence_करोne(&fence);
	nouveau_pfns_map(svmm, args->vma->vm_mm, args->start, pfns, i);

	जबतक (nr_dma--) अणु
		dma_unmap_page(drm->dev->dev, dma_addrs[nr_dma], PAGE_SIZE,
				DMA_BIसूचीECTIONAL);
	पूर्ण
	migrate_vma_finalize(args);
पूर्ण

पूर्णांक
nouveau_dmem_migrate_vma(काष्ठा nouveau_drm *drm,
			 काष्ठा nouveau_svmm *svmm,
			 काष्ठा vm_area_काष्ठा *vma,
			 अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ npages = (end - start) >> PAGE_SHIFT;
	अचिन्हित दीर्घ max = min(SG_MAX_SINGLE_ALLOC, npages);
	dma_addr_t *dma_addrs;
	काष्ठा migrate_vma args = अणु
		.vma		= vma,
		.start		= start,
		.pgmap_owner	= drm->dev,
		.flags		= MIGRATE_VMA_SELECT_SYSTEM,
	पूर्ण;
	अचिन्हित दीर्घ i;
	u64 *pfns;
	पूर्णांक ret = -ENOMEM;

	अगर (drm->dmem == शून्य)
		वापस -ENODEV;

	args.src = kसुस्मृति(max, माप(*args.src), GFP_KERNEL);
	अगर (!args.src)
		जाओ out;
	args.dst = kसुस्मृति(max, माप(*args.dst), GFP_KERNEL);
	अगर (!args.dst)
		जाओ out_मुक्त_src;

	dma_addrs = kदो_स्मृति_array(max, माप(*dma_addrs), GFP_KERNEL);
	अगर (!dma_addrs)
		जाओ out_मुक्त_dst;

	pfns = nouveau_pfns_alloc(max);
	अगर (!pfns)
		जाओ out_मुक्त_dma;

	क्रम (i = 0; i < npages; i += max) अणु
		args.end = start + (max << PAGE_SHIFT);
		ret = migrate_vma_setup(&args);
		अगर (ret)
			जाओ out_मुक्त_pfns;

		अगर (args.cpages)
			nouveau_dmem_migrate_chunk(drm, svmm, &args, dma_addrs,
						   pfns);
		args.start = args.end;
	पूर्ण

	ret = 0;
out_मुक्त_pfns:
	nouveau_pfns_मुक्त(pfns);
out_मुक्त_dma:
	kमुक्त(dma_addrs);
out_मुक्त_dst:
	kमुक्त(args.dst);
out_मुक्त_src:
	kमुक्त(args.src);
out:
	वापस ret;
पूर्ण
