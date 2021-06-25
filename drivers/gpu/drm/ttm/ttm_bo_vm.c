<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

#घोषणा pr_fmt(fmt) "[TTM] " fmt

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <drm/drm_vma_manager.h>
#समावेश <linux/mm.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mem_encrypt.h>

अटल vm_fault_t tपंचांग_bo_vm_fault_idle(काष्ठा tपंचांग_buffer_object *bo,
				काष्ठा vm_fault *vmf)
अणु
	vm_fault_t ret = 0;
	पूर्णांक err = 0;

	अगर (likely(!bo->moving))
		जाओ out_unlock;

	/*
	 * Quick non-stalling check क्रम idle.
	 */
	अगर (dma_fence_is_संकेतed(bo->moving))
		जाओ out_clear;

	/*
	 * If possible, aव्योम रुकोing क्रम GPU with mmap_lock
	 * held.  We only करो this अगर the fault allows retry and this
	 * is the first attempt.
	 */
	अगर (fault_flag_allow_retry_first(vmf->flags)) अणु
		ret = VM_FAULT_RETRY;
		अगर (vmf->flags & FAULT_FLAG_RETRY_NOWAIT)
			जाओ out_unlock;

		tपंचांग_bo_get(bo);
		mmap_पढ़ो_unlock(vmf->vma->vm_mm);
		(व्योम) dma_fence_रुको(bo->moving, true);
		dma_resv_unlock(bo->base.resv);
		tपंचांग_bo_put(bo);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Ordinary रुको.
	 */
	err = dma_fence_रुको(bo->moving, true);
	अगर (unlikely(err != 0)) अणु
		ret = (err != -ERESTARTSYS) ? VM_FAULT_SIGBUS :
			VM_FAULT_NOPAGE;
		जाओ out_unlock;
	पूर्ण

out_clear:
	dma_fence_put(bo->moving);
	bo->moving = शून्य;

out_unlock:
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ tपंचांग_bo_io_mem_pfn(काष्ठा tपंचांग_buffer_object *bo,
				       अचिन्हित दीर्घ page_offset)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;

	अगर (bdev->funcs->io_mem_pfn)
		वापस bdev->funcs->io_mem_pfn(bo, page_offset);

	वापस (bo->mem.bus.offset >> PAGE_SHIFT) + page_offset;
पूर्ण

/**
 * tपंचांग_bo_vm_reserve - Reserve a buffer object in a retryable vm callback
 * @bo: The buffer object
 * @vmf: The fault काष्ठाure handed to the callback
 *
 * vm callbacks like fault() and *_mkग_लिखो() allow क्रम the mm_sem to be dropped
 * during दीर्घ रुकोs, and after the रुको the callback will be restarted. This
 * is to allow other thपढ़ोs using the same भव memory space concurrent
 * access to map(), unmap() completely unrelated buffer objects. TTM buffer
 * object reservations someबार रुको क्रम GPU and should thereक्रमe be
 * considered दीर्घ रुकोs. This function reserves the buffer object पूर्णांकerruptibly
 * taking this पूर्णांकo account. Starvation is aव्योमed by the vm प्रणाली not
 * allowing too many repeated restarts.
 * This function is पूर्णांकended to be used in customized fault() and _mkग_लिखो()
 * handlers.
 *
 * Return:
 *    0 on success and the bo was reserved.
 *    VM_FAULT_RETRY अगर blocking रुको.
 *    VM_FAULT_NOPAGE अगर blocking रुको and retrying was not allowed.
 */
vm_fault_t tपंचांग_bo_vm_reserve(काष्ठा tपंचांग_buffer_object *bo,
			     काष्ठा vm_fault *vmf)
अणु
	/*
	 * Work around locking order reversal in fault / nopfn
	 * between mmap_lock and bo_reserve: Perक्रमm a trylock operation
	 * क्रम reserve, and अगर it fails, retry the fault after रुकोing
	 * क्रम the buffer to become unreserved.
	 */
	अगर (unlikely(!dma_resv_trylock(bo->base.resv))) अणु
		/*
		 * If the fault allows retry and this is the first
		 * fault attempt, we try to release the mmap_lock
		 * beक्रमe रुकोing
		 */
		अगर (fault_flag_allow_retry_first(vmf->flags)) अणु
			अगर (!(vmf->flags & FAULT_FLAG_RETRY_NOWAIT)) अणु
				tपंचांग_bo_get(bo);
				mmap_पढ़ो_unlock(vmf->vma->vm_mm);
				अगर (!dma_resv_lock_पूर्णांकerruptible(bo->base.resv,
								 शून्य))
					dma_resv_unlock(bo->base.resv);
				tपंचांग_bo_put(bo);
			पूर्ण

			वापस VM_FAULT_RETRY;
		पूर्ण

		अगर (dma_resv_lock_पूर्णांकerruptible(bo->base.resv, शून्य))
			वापस VM_FAULT_NOPAGE;
	पूर्ण

	/*
	 * Refuse to fault imported pages. This should be handled
	 * (अगर at all) by redirecting mmap to the exporter.
	 */
	अगर (bo->tपंचांग && (bo->tपंचांग->page_flags & TTM_PAGE_FLAG_SG)) अणु
		dma_resv_unlock(bo->base.resv);
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vm_reserve);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/**
 * tपंचांग_bo_vm_insert_huge - Insert a pfn क्रम PUD or PMD faults
 * @vmf: Fault data
 * @bo: The buffer object
 * @page_offset: Page offset from bo start
 * @fault_page_size: The size of the fault in pages.
 * @pgprot: The page protections.
 * Does additional checking whether it's possible to insert a PUD or PMD
 * pfn and perक्रमms the insertion.
 *
 * Return: VM_FAULT_NOPAGE on successful insertion, VM_FAULT_FALLBACK अगर
 * a huge fault was not possible, or on insertion error.
 */
अटल vm_fault_t tपंचांग_bo_vm_insert_huge(काष्ठा vm_fault *vmf,
					काष्ठा tपंचांग_buffer_object *bo,
					pgoff_t page_offset,
					pgoff_t fault_page_size,
					pgprot_t pgprot)
अणु
	pgoff_t i;
	vm_fault_t ret;
	अचिन्हित दीर्घ pfn;
	pfn_t pfnt;
	काष्ठा tपंचांग_tt *tपंचांग = bo->tपंचांग;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;

	/* Fault should not cross bo boundary. */
	page_offset &= ~(fault_page_size - 1);
	अगर (page_offset + fault_page_size > bo->mem.num_pages)
		जाओ out_fallback;

	अगर (bo->mem.bus.is_iomem)
		pfn = tपंचांग_bo_io_mem_pfn(bo, page_offset);
	अन्यथा
		pfn = page_to_pfn(tपंचांग->pages[page_offset]);

	/* pfn must be fault_page_size aligned. */
	अगर ((pfn & (fault_page_size - 1)) != 0)
		जाओ out_fallback;

	/* Check that memory is contiguous. */
	अगर (!bo->mem.bus.is_iomem) अणु
		क्रम (i = 1; i < fault_page_size; ++i) अणु
			अगर (page_to_pfn(tपंचांग->pages[page_offset + i]) != pfn + i)
				जाओ out_fallback;
		पूर्ण
	पूर्ण अन्यथा अगर (bo->bdev->funcs->io_mem_pfn) अणु
		क्रम (i = 1; i < fault_page_size; ++i) अणु
			अगर (tपंचांग_bo_io_mem_pfn(bo, page_offset + i) != pfn + i)
				जाओ out_fallback;
		पूर्ण
	पूर्ण

	pfnt = __pfn_to_pfn_t(pfn, PFN_DEV);
	अगर (fault_page_size == (HPAGE_PMD_SIZE >> PAGE_SHIFT))
		ret = vmf_insert_pfn_pmd_prot(vmf, pfnt, pgprot, ग_लिखो);
#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
	अन्यथा अगर (fault_page_size == (HPAGE_PUD_SIZE >> PAGE_SHIFT))
		ret = vmf_insert_pfn_pud_prot(vmf, pfnt, pgprot, ग_लिखो);
#पूर्ण_अगर
	अन्यथा
		WARN_ON_ONCE(ret = VM_FAULT_FALLBACK);

	अगर (ret != VM_FAULT_NOPAGE)
		जाओ out_fallback;

	वापस VM_FAULT_NOPAGE;
out_fallback:
	count_vm_event(THP_FAULT_FALLBACK);
	वापस VM_FAULT_FALLBACK;
पूर्ण
#अन्यथा
अटल vm_fault_t tपंचांग_bo_vm_insert_huge(काष्ठा vm_fault *vmf,
					काष्ठा tपंचांग_buffer_object *bo,
					pgoff_t page_offset,
					pgoff_t fault_page_size,
					pgprot_t pgprot)
अणु
	वापस VM_FAULT_FALLBACK;
पूर्ण
#पूर्ण_अगर

/**
 * tपंचांग_bo_vm_fault_reserved - TTM fault helper
 * @vmf: The काष्ठा vm_fault given as argument to the fault callback
 * @prot: The page protection to be used क्रम this memory area.
 * @num_prefault: Maximum number of prefault pages. The caller may want to
 * specअगरy this based on madvice settings and the size of the GPU object
 * backed by the memory.
 * @fault_page_size: The size of the fault in pages.
 *
 * This function inserts one or more page table entries poपूर्णांकing to the
 * memory backing the buffer object, and then वापसs a वापस code
 * inकाष्ठाing the caller to retry the page access.
 *
 * Return:
 *   VM_FAULT_NOPAGE on success or pending संकेत
 *   VM_FAULT_SIGBUS on unspecअगरied error
 *   VM_FAULT_OOM on out-of-memory
 *   VM_FAULT_RETRY अगर retryable रुको
 */
vm_fault_t tपंचांग_bo_vm_fault_reserved(काष्ठा vm_fault *vmf,
				    pgprot_t prot,
				    pgoff_t num_prefault,
				    pgoff_t fault_page_size)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा tपंचांग_buffer_object *bo = vma->vm_निजी_data;
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	अचिन्हित दीर्घ page_offset;
	अचिन्हित दीर्घ page_last;
	अचिन्हित दीर्घ pfn;
	काष्ठा tपंचांग_tt *tपंचांग = शून्य;
	काष्ठा page *page;
	पूर्णांक err;
	pgoff_t i;
	vm_fault_t ret = VM_FAULT_NOPAGE;
	अचिन्हित दीर्घ address = vmf->address;

	/*
	 * Wait क्रम buffer data in transit, due to a pipelined
	 * move.
	 */
	ret = tपंचांग_bo_vm_fault_idle(bo, vmf);
	अगर (unlikely(ret != 0))
		वापस ret;

	err = tपंचांग_mem_io_reserve(bdev, &bo->mem);
	अगर (unlikely(err != 0))
		वापस VM_FAULT_SIGBUS;

	page_offset = ((address - vma->vm_start) >> PAGE_SHIFT) +
		vma->vm_pgoff - drm_vma_node_start(&bo->base.vma_node);
	page_last = vma_pages(vma) + vma->vm_pgoff -
		drm_vma_node_start(&bo->base.vma_node);

	अगर (unlikely(page_offset >= bo->mem.num_pages))
		वापस VM_FAULT_SIGBUS;

	prot = tपंचांग_io_prot(bo, &bo->mem, prot);
	अगर (!bo->mem.bus.is_iomem) अणु
		काष्ठा tपंचांग_operation_ctx ctx = अणु
			.पूर्णांकerruptible = false,
			.no_रुको_gpu = false,
			.क्रमce_alloc = true
		पूर्ण;

		tपंचांग = bo->tपंचांग;
		अगर (tपंचांग_tt_populate(bdev, bo->tपंचांग, &ctx))
			वापस VM_FAULT_OOM;
	पूर्ण अन्यथा अणु
		/* Iomem should not be marked encrypted */
		prot = pgprot_decrypted(prot);
	पूर्ण

	/* We करोn't prefault on huge faults. Yet. */
	अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) && fault_page_size != 1)
		वापस tपंचांग_bo_vm_insert_huge(vmf, bo, page_offset,
					     fault_page_size, prot);

	/*
	 * Speculatively prefault a number of pages. Only error on
	 * first page.
	 */
	क्रम (i = 0; i < num_prefault; ++i) अणु
		अगर (bo->mem.bus.is_iomem) अणु
			pfn = tपंचांग_bo_io_mem_pfn(bo, page_offset);
		पूर्ण अन्यथा अणु
			page = tपंचांग->pages[page_offset];
			अगर (unlikely(!page && i == 0)) अणु
				वापस VM_FAULT_OOM;
			पूर्ण अन्यथा अगर (unlikely(!page)) अणु
				अवरोध;
			पूर्ण
			page->index = drm_vma_node_start(&bo->base.vma_node) +
				page_offset;
			pfn = page_to_pfn(page);
		पूर्ण

		/*
		 * Note that the value of @prot at this poपूर्णांक may dअगरfer from
		 * the value of @vma->vm_page_prot in the caching- and
		 * encryption bits. This is because the exact location of the
		 * data may not be known at mmap() समय and may also change
		 * at arbitrary बार जबतक the data is mmap'ed.
		 * See vmf_insert_mixed_prot() क्रम a discussion.
		 */
		अगर (vma->vm_flags & VM_MIXEDMAP)
			ret = vmf_insert_mixed_prot(vma, address,
						    __pfn_to_pfn_t(pfn, PFN_DEV),
						    prot);
		अन्यथा
			ret = vmf_insert_pfn_prot(vma, address, pfn, prot);

		/* Never error on prefaulted PTEs */
		अगर (unlikely((ret & VM_FAULT_ERROR))) अणु
			अगर (i == 0)
				वापस VM_FAULT_NOPAGE;
			अन्यथा
				अवरोध;
		पूर्ण

		address += PAGE_SIZE;
		अगर (unlikely(++page_offset >= page_last))
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vm_fault_reserved);

vm_fault_t tपंचांग_bo_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	pgprot_t prot;
	काष्ठा tपंचांग_buffer_object *bo = vma->vm_निजी_data;
	vm_fault_t ret;

	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	अगर (ret)
		वापस ret;

	prot = vma->vm_page_prot;
	ret = tपंचांग_bo_vm_fault_reserved(vmf, prot, TTM_BO_VM_NUM_PREFAULT, 1);
	अगर (ret == VM_FAULT_RETRY && !(vmf->flags & FAULT_FLAG_RETRY_NOWAIT))
		वापस ret;

	dma_resv_unlock(bo->base.resv);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vm_fault);

व्योम tपंचांग_bo_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tपंचांग_buffer_object *bo = vma->vm_निजी_data;

	WARN_ON(bo->bdev->dev_mapping != vma->vm_file->f_mapping);

	tपंचांग_bo_get(bo);
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vm_खोलो);

व्योम tपंचांग_bo_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tपंचांग_buffer_object *bo = vma->vm_निजी_data;

	tपंचांग_bo_put(bo);
	vma->vm_निजी_data = शून्य;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vm_बंद);

अटल पूर्णांक tपंचांग_bo_vm_access_kmap(काष्ठा tपंचांग_buffer_object *bo,
				 अचिन्हित दीर्घ offset,
				 uपूर्णांक8_t *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ page = offset >> PAGE_SHIFT;
	अचिन्हित दीर्घ bytes_left = len;
	पूर्णांक ret;

	/* Copy a page at a समय, that way no extra भव address
	 * mapping is needed
	 */
	offset -= page << PAGE_SHIFT;
	करो अणु
		अचिन्हित दीर्घ bytes = min(bytes_left, PAGE_SIZE - offset);
		काष्ठा tपंचांग_bo_kmap_obj map;
		व्योम *ptr;
		bool is_iomem;

		ret = tपंचांग_bo_kmap(bo, page, 1, &map);
		अगर (ret)
			वापस ret;

		ptr = (uपूर्णांक8_t *)tपंचांग_kmap_obj_भव(&map, &is_iomem) + offset;
		WARN_ON_ONCE(is_iomem);
		अगर (ग_लिखो)
			स_नकल(ptr, buf, bytes);
		अन्यथा
			स_नकल(buf, ptr, bytes);
		tपंचांग_bo_kunmap(&map);

		page++;
		buf += bytes;
		bytes_left -= bytes;
		offset = 0;
	पूर्ण जबतक (bytes_left);

	वापस len;
पूर्ण

पूर्णांक tपंचांग_bo_vm_access(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		     व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	काष्ठा tपंचांग_buffer_object *bo = vma->vm_निजी_data;
	अचिन्हित दीर्घ offset = (addr) - vma->vm_start +
		((vma->vm_pgoff - drm_vma_node_start(&bo->base.vma_node))
		 << PAGE_SHIFT);
	पूर्णांक ret;

	अगर (len < 1 || (offset + len) >> PAGE_SHIFT > bo->mem.num_pages)
		वापस -EIO;

	ret = tपंचांग_bo_reserve(bo, true, false, शून्य);
	अगर (ret)
		वापस ret;

	चयन (bo->mem.mem_type) अणु
	हाल TTM_PL_SYSTEM:
		अगर (unlikely(bo->tपंचांग->page_flags & TTM_PAGE_FLAG_SWAPPED)) अणु
			ret = tपंचांग_tt_swapin(bo->tपंचांग);
			अगर (unlikely(ret != 0))
				वापस ret;
		पूर्ण
		fallthrough;
	हाल TTM_PL_TT:
		ret = tपंचांग_bo_vm_access_kmap(bo, offset, buf, len, ग_लिखो);
		अवरोध;
	शेष:
		अगर (bo->bdev->funcs->access_memory)
			ret = bo->bdev->funcs->access_memory(
				bo, offset, buf, len, ग_लिखो);
		अन्यथा
			ret = -EIO;
	पूर्ण

	tपंचांग_bo_unreserve(bo);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vm_access);

अटल स्थिर काष्ठा vm_operations_काष्ठा tपंचांग_bo_vm_ops = अणु
	.fault = tपंचांग_bo_vm_fault,
	.खोलो = tपंचांग_bo_vm_खोलो,
	.बंद = tपंचांग_bo_vm_बंद,
	.access = tपंचांग_bo_vm_access,
पूर्ण;

अटल काष्ठा tपंचांग_buffer_object *tपंचांग_bo_vm_lookup(काष्ठा tपंचांग_device *bdev,
						  अचिन्हित दीर्घ offset,
						  अचिन्हित दीर्घ pages)
अणु
	काष्ठा drm_vma_offset_node *node;
	काष्ठा tपंचांग_buffer_object *bo = शून्य;

	drm_vma_offset_lock_lookup(bdev->vma_manager);

	node = drm_vma_offset_lookup_locked(bdev->vma_manager, offset, pages);
	अगर (likely(node)) अणु
		bo = container_of(node, काष्ठा tपंचांग_buffer_object,
				  base.vma_node);
		bo = tपंचांग_bo_get_unless_zero(bo);
	पूर्ण

	drm_vma_offset_unlock_lookup(bdev->vma_manager);

	अगर (!bo)
		pr_err("Could not find buffer object to map\n");

	वापस bo;
पूर्ण

अटल व्योम tपंचांग_bo_mmap_vma_setup(काष्ठा tपंचांग_buffer_object *bo, काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_ops = &tपंचांग_bo_vm_ops;

	/*
	 * Note: We're transferring the bo reference to
	 * vma->vm_निजी_data here.
	 */

	vma->vm_निजी_data = bo;

	/*
	 * We'd like to use VM_PFNMAP on shared mappings, where
	 * (vma->vm_flags & VM_SHARED) != 0, क्रम perक्रमmance reasons,
	 * but क्रम some reason VM_PFNMAP + x86 PAT + ग_लिखो-combine is very
	 * bad क्रम perक्रमmance. Until that has been sorted out, use
	 * VM_MIXEDMAP on all mappings. See मुक्तdesktop.org bug #75719
	 */
	vma->vm_flags |= VM_MIXEDMAP;
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
पूर्ण

पूर्णांक tपंचांग_bo_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma,
		काष्ठा tपंचांग_device *bdev)
अणु
	काष्ठा tपंचांग_buffer_object *bo;
	पूर्णांक ret;

	अगर (unlikely(vma->vm_pgoff < DRM_खाता_PAGE_OFFSET_START))
		वापस -EINVAL;

	bo = tपंचांग_bo_vm_lookup(bdev, vma->vm_pgoff, vma_pages(vma));
	अगर (unlikely(!bo))
		वापस -EINVAL;

	अगर (unlikely(!bo->bdev->funcs->verअगरy_access)) अणु
		ret = -EPERM;
		जाओ out_unref;
	पूर्ण
	ret = bo->bdev->funcs->verअगरy_access(bo, filp);
	अगर (unlikely(ret != 0))
		जाओ out_unref;

	tपंचांग_bo_mmap_vma_setup(bo, vma);
	वापस 0;
out_unref:
	tपंचांग_bo_put(bo);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_mmap);

पूर्णांक tपंचांग_bo_mmap_obj(काष्ठा vm_area_काष्ठा *vma, काष्ठा tपंचांग_buffer_object *bo)
अणु
	tपंचांग_bo_get(bo);
	tपंचांग_bo_mmap_vma_setup(bo, vma);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_mmap_obj);
