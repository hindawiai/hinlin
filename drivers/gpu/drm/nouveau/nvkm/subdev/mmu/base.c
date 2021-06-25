<शैली गुरु>
/*
 * Copyright 2010 Red Hat Inc.
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
 *
 * Authors: Ben Skeggs
 */
#समावेश "ummu.h"
#समावेश "vmm.h"

#समावेश <subdev/bar.h>
#समावेश <subdev/fb.h>

#समावेश <nvअगर/अगर500d.h>
#समावेश <nvअगर/अगर900d.h>

काष्ठा nvkm_mmu_ptp अणु
	काष्ठा nvkm_mmu_pt *pt;
	काष्ठा list_head head;
	u8  shअगरt;
	u16 mask;
	u16 मुक्त;
पूर्ण;

अटल व्योम
nvkm_mmu_ptp_put(काष्ठा nvkm_mmu *mmu, bool क्रमce, काष्ठा nvkm_mmu_pt *pt)
अणु
	स्थिर पूर्णांक slot = pt->base >> pt->ptp->shअगरt;
	काष्ठा nvkm_mmu_ptp *ptp = pt->ptp;

	/* If there were no मुक्त slots in the parent allocation beक्रमe,
	 * there will be now, so वापस PTP to the cache.
	 */
	अगर (!ptp->मुक्त)
		list_add(&ptp->head, &mmu->ptp.list);
	ptp->मुक्त |= BIT(slot);

	/* If there's no more sub-allocations, destroy PTP. */
	अगर (ptp->मुक्त == ptp->mask) अणु
		nvkm_mmu_ptc_put(mmu, क्रमce, &ptp->pt);
		list_del(&ptp->head);
		kमुक्त(ptp);
	पूर्ण

	kमुक्त(pt);
पूर्ण

अटल काष्ठा nvkm_mmu_pt *
nvkm_mmu_ptp_get(काष्ठा nvkm_mmu *mmu, u32 size, bool zero)
अणु
	काष्ठा nvkm_mmu_pt *pt;
	काष्ठा nvkm_mmu_ptp *ptp;
	पूर्णांक slot;

	अगर (!(pt = kzalloc(माप(*pt), GFP_KERNEL)))
		वापस शून्य;

	ptp = list_first_entry_or_null(&mmu->ptp.list, typeof(*ptp), head);
	अगर (!ptp) अणु
		/* Need to allocate a new parent to sub-allocate from. */
		अगर (!(ptp = kदो_स्मृति(माप(*ptp), GFP_KERNEL))) अणु
			kमुक्त(pt);
			वापस शून्य;
		पूर्ण

		ptp->pt = nvkm_mmu_ptc_get(mmu, 0x1000, 0x1000, false);
		अगर (!ptp->pt) अणु
			kमुक्त(ptp);
			kमुक्त(pt);
			वापस शून्य;
		पूर्ण

		ptp->shअगरt = order_base_2(size);
		slot = nvkm_memory_size(ptp->pt->memory) >> ptp->shअगरt;
		ptp->mask = (1 << slot) - 1;
		ptp->मुक्त = ptp->mask;
		list_add(&ptp->head, &mmu->ptp.list);
	पूर्ण
	pt->ptp = ptp;
	pt->sub = true;

	/* Sub-allocate from parent object, removing PTP from cache
	 * अगर there's no more मुक्त slots left.
	 */
	slot = __ffs(ptp->मुक्त);
	ptp->मुक्त &= ~BIT(slot);
	अगर (!ptp->मुक्त)
		list_del(&ptp->head);

	pt->memory = pt->ptp->pt->memory;
	pt->base = slot << ptp->shअगरt;
	pt->addr = pt->ptp->pt->addr + pt->base;
	वापस pt;
पूर्ण

काष्ठा nvkm_mmu_ptc अणु
	काष्ठा list_head head;
	काष्ठा list_head item;
	u32 size;
	u32 refs;
पूर्ण;

अटल अंतरभूत काष्ठा nvkm_mmu_ptc *
nvkm_mmu_ptc_find(काष्ठा nvkm_mmu *mmu, u32 size)
अणु
	काष्ठा nvkm_mmu_ptc *ptc;

	list_क्रम_each_entry(ptc, &mmu->ptc.list, head) अणु
		अगर (ptc->size == size)
			वापस ptc;
	पूर्ण

	ptc = kदो_स्मृति(माप(*ptc), GFP_KERNEL);
	अगर (ptc) अणु
		INIT_LIST_HEAD(&ptc->item);
		ptc->size = size;
		ptc->refs = 0;
		list_add(&ptc->head, &mmu->ptc.list);
	पूर्ण

	वापस ptc;
पूर्ण

व्योम
nvkm_mmu_ptc_put(काष्ठा nvkm_mmu *mmu, bool क्रमce, काष्ठा nvkm_mmu_pt **ppt)
अणु
	काष्ठा nvkm_mmu_pt *pt = *ppt;
	अगर (pt) अणु
		/* Handle sub-allocated page tables. */
		अगर (pt->sub) अणु
			mutex_lock(&mmu->ptp.mutex);
			nvkm_mmu_ptp_put(mmu, क्रमce, pt);
			mutex_unlock(&mmu->ptp.mutex);
			वापस;
		पूर्ण

		/* Either cache or मुक्त the object. */
		mutex_lock(&mmu->ptc.mutex);
		अगर (pt->ptc->refs < 8 /* Heuristic. */ && !क्रमce) अणु
			list_add_tail(&pt->head, &pt->ptc->item);
			pt->ptc->refs++;
		पूर्ण अन्यथा अणु
			nvkm_memory_unref(&pt->memory);
			kमुक्त(pt);
		पूर्ण
		mutex_unlock(&mmu->ptc.mutex);
	पूर्ण
पूर्ण

काष्ठा nvkm_mmu_pt *
nvkm_mmu_ptc_get(काष्ठा nvkm_mmu *mmu, u32 size, u32 align, bool zero)
अणु
	काष्ठा nvkm_mmu_ptc *ptc;
	काष्ठा nvkm_mmu_pt *pt;
	पूर्णांक ret;

	/* Sub-allocated page table (ie. GP100 LPT). */
	अगर (align < 0x1000) अणु
		mutex_lock(&mmu->ptp.mutex);
		pt = nvkm_mmu_ptp_get(mmu, align, zero);
		mutex_unlock(&mmu->ptp.mutex);
		वापस pt;
	पूर्ण

	/* Lookup cache क्रम this page table size. */
	mutex_lock(&mmu->ptc.mutex);
	ptc = nvkm_mmu_ptc_find(mmu, size);
	अगर (!ptc) अणु
		mutex_unlock(&mmu->ptc.mutex);
		वापस शून्य;
	पूर्ण

	/* If there's a मुक्त PT in the cache, reuse it. */
	pt = list_first_entry_or_null(&ptc->item, typeof(*pt), head);
	अगर (pt) अणु
		अगर (zero)
			nvkm_fo64(pt->memory, 0, 0, size >> 3);
		list_del(&pt->head);
		ptc->refs--;
		mutex_unlock(&mmu->ptc.mutex);
		वापस pt;
	पूर्ण
	mutex_unlock(&mmu->ptc.mutex);

	/* No such luck, we need to allocate. */
	अगर (!(pt = kदो_स्मृति(माप(*pt), GFP_KERNEL)))
		वापस शून्य;
	pt->ptc = ptc;
	pt->sub = false;

	ret = nvkm_memory_new(mmu->subdev.device, NVKM_MEM_TARGET_INST,
			      size, align, zero, &pt->memory);
	अगर (ret) अणु
		kमुक्त(pt);
		वापस शून्य;
	पूर्ण

	pt->base = 0;
	pt->addr = nvkm_memory_addr(pt->memory);
	वापस pt;
पूर्ण

व्योम
nvkm_mmu_ptc_dump(काष्ठा nvkm_mmu *mmu)
अणु
	काष्ठा nvkm_mmu_ptc *ptc;
	list_क्रम_each_entry(ptc, &mmu->ptc.list, head) अणु
		काष्ठा nvkm_mmu_pt *pt, *tt;
		list_क्रम_each_entry_safe(pt, tt, &ptc->item, head) अणु
			nvkm_memory_unref(&pt->memory);
			list_del(&pt->head);
			kमुक्त(pt);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nvkm_mmu_ptc_fini(काष्ठा nvkm_mmu *mmu)
अणु
	काष्ठा nvkm_mmu_ptc *ptc, *ptct;

	list_क्रम_each_entry_safe(ptc, ptct, &mmu->ptc.list, head) अणु
		WARN_ON(!list_empty(&ptc->item));
		list_del(&ptc->head);
		kमुक्त(ptc);
	पूर्ण
पूर्ण

अटल व्योम
nvkm_mmu_ptc_init(काष्ठा nvkm_mmu *mmu)
अणु
	mutex_init(&mmu->ptc.mutex);
	INIT_LIST_HEAD(&mmu->ptc.list);
	mutex_init(&mmu->ptp.mutex);
	INIT_LIST_HEAD(&mmu->ptp.list);
पूर्ण

अटल व्योम
nvkm_mmu_type(काष्ठा nvkm_mmu *mmu, पूर्णांक heap, u8 type)
अणु
	अगर (heap >= 0 && !WARN_ON(mmu->type_nr == ARRAY_SIZE(mmu->type))) अणु
		mmu->type[mmu->type_nr].type = type | mmu->heap[heap].type;
		mmu->type[mmu->type_nr].heap = heap;
		mmu->type_nr++;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_mmu_heap(काष्ठा nvkm_mmu *mmu, u8 type, u64 size)
अणु
	अगर (size) अणु
		अगर (!WARN_ON(mmu->heap_nr == ARRAY_SIZE(mmu->heap))) अणु
			mmu->heap[mmu->heap_nr].type = type;
			mmu->heap[mmu->heap_nr].size = size;
			वापस mmu->heap_nr++;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम
nvkm_mmu_host(काष्ठा nvkm_mmu *mmu)
अणु
	काष्ठा nvkm_device *device = mmu->subdev.device;
	u8 type = NVKM_MEM_KIND * !!mmu->func->kind_sys;
	पूर्णांक heap;

	/* Non-mappable प्रणाली memory. */
	heap = nvkm_mmu_heap(mmu, NVKM_MEM_HOST, ~0ULL);
	nvkm_mmu_type(mmu, heap, type);

	/* Non-coherent, cached, प्रणाली memory.
	 *
	 * Block-linear mappings of प्रणाली memory must be करोne through
	 * BAR1, and cannot be supported on प्रणालीs where we're unable
	 * to map BAR1 with ग_लिखो-combining.
	 */
	type |= NVKM_MEM_MAPPABLE;
	अगर (!device->bar || device->bar->iomap_uncached)
		nvkm_mmu_type(mmu, heap, type & ~NVKM_MEM_KIND);
	अन्यथा
		nvkm_mmu_type(mmu, heap, type);

	/* Coherent, cached, प्रणाली memory.
	 *
	 * Unsupported on प्रणालीs that aren't able to support snooped
	 * mappings, and also क्रम block-linear mappings which must be
	 * करोne through BAR1.
	 */
	type |= NVKM_MEM_COHERENT;
	अगर (device->func->cpu_coherent)
		nvkm_mmu_type(mmu, heap, type & ~NVKM_MEM_KIND);

	/* Uncached प्रणाली memory. */
	nvkm_mmu_type(mmu, heap, type |= NVKM_MEM_UNCACHED);
पूर्ण

अटल व्योम
nvkm_mmu_vram(काष्ठा nvkm_mmu *mmu)
अणु
	काष्ठा nvkm_device *device = mmu->subdev.device;
	काष्ठा nvkm_mm *mm = &device->fb->ram->vram;
	स्थिर u64 sizeN = nvkm_mm_heap_size(mm, NVKM_RAM_MM_NORMAL);
	स्थिर u64 sizeU = nvkm_mm_heap_size(mm, NVKM_RAM_MM_NOMAP);
	स्थिर u64 sizeM = nvkm_mm_heap_size(mm, NVKM_RAM_MM_MIXED);
	u8 type = NVKM_MEM_KIND * !!mmu->func->kind;
	u8 heap = NVKM_MEM_VRAM;
	पूर्णांक heapM, heapN, heapU;

	/* Mixed-memory करोesn't support compression or display. */
	heapM = nvkm_mmu_heap(mmu, heap, sizeM << NVKM_RAM_MM_SHIFT);

	heap |= NVKM_MEM_COMP;
	heap |= NVKM_MEM_DISP;
	heapN = nvkm_mmu_heap(mmu, heap, sizeN << NVKM_RAM_MM_SHIFT);
	heapU = nvkm_mmu_heap(mmu, heap, sizeU << NVKM_RAM_MM_SHIFT);

	/* Add non-mappable VRAM types first so that they're preferred
	 * over anything अन्यथा.  Mixed-memory will be slower than other
	 * heaps, it's prioritised last.
	 */
	nvkm_mmu_type(mmu, heapU, type);
	nvkm_mmu_type(mmu, heapN, type);
	nvkm_mmu_type(mmu, heapM, type);

	/* Add host memory types next, under the assumption that users
	 * wanting mappable memory want to use them as staging buffers
	 * or the like.
	 */
	nvkm_mmu_host(mmu);

	/* Mappable VRAM types go last, as they're basically the worst
	 * possible type to ask क्रम unless there's no other choice.
	 */
	अगर (device->bar) अणु
		/* Write-combined BAR1 access. */
		type |= NVKM_MEM_MAPPABLE;
		अगर (!device->bar->iomap_uncached) अणु
			nvkm_mmu_type(mmu, heapN, type);
			nvkm_mmu_type(mmu, heapM, type);
		पूर्ण

		/* Uncached BAR1 access. */
		type |= NVKM_MEM_COHERENT;
		type |= NVKM_MEM_UNCACHED;
		nvkm_mmu_type(mmu, heapN, type);
		nvkm_mmu_type(mmu, heapM, type);
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_mmu_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_mmu *mmu = nvkm_mmu(subdev);

	/* Determine available memory types. */
	अगर (mmu->subdev.device->fb && mmu->subdev.device->fb->ram)
		nvkm_mmu_vram(mmu);
	अन्यथा
		nvkm_mmu_host(mmu);

	अगर (mmu->func->vmm.global) अणु
		पूर्णांक ret = nvkm_vmm_new(subdev->device, 0, 0, शून्य, 0, शून्य,
				       "gart", &mmu->vmm);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_mmu_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_mmu *mmu = nvkm_mmu(subdev);
	अगर (mmu->func->init)
		mmu->func->init(mmu);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_mmu_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_mmu *mmu = nvkm_mmu(subdev);

	nvkm_vmm_unref(&mmu->vmm);

	nvkm_mmu_ptc_fini(mmu);
	mutex_destroy(&mmu->mutex);
	वापस mmu;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_mmu = अणु
	.dtor = nvkm_mmu_dtor,
	.oneinit = nvkm_mmu_oneinit,
	.init = nvkm_mmu_init,
पूर्ण;

व्योम
nvkm_mmu_ctor(स्थिर काष्ठा nvkm_mmu_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mmu *mmu)
अणु
	nvkm_subdev_ctor(&nvkm_mmu, device, type, inst, &mmu->subdev);
	mmu->func = func;
	mmu->dma_bits = func->dma_bits;
	nvkm_mmu_ptc_init(mmu);
	mutex_init(&mmu->mutex);
	mmu->user.ctor = nvkm_ummu_new;
	mmu->user.base = func->mmu.user;
पूर्ण

पूर्णांक
nvkm_mmu_new_(स्थिर काष्ठा nvkm_mmu_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mmu **pmmu)
अणु
	अगर (!(*pmmu = kzalloc(माप(**pmmu), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_mmu_ctor(func, device, type, inst, *pmmu);
	वापस 0;
पूर्ण
