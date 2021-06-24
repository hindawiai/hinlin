<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2019 VMware, Inc., Palo Alto, CA., USA
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
#समावेश "vmwgfx_drv.h"

/*
 * Dअगरferent methods क्रम tracking dirty:
 * VMW_BO_सूचीTY_PAGETABLE - Scan the pagetable क्रम hardware dirty bits
 * VMW_BO_सूचीTY_MKWRITE - Write-protect page table entries and record ग_लिखो-
 * accesses in the VM mkग_लिखो() callback
 */
क्रमागत vmw_bo_dirty_method अणु
	VMW_BO_सूचीTY_PAGETABLE,
	VMW_BO_सूचीTY_MKWRITE,
पूर्ण;

/*
 * No dirtied pages at scan trigger a transition to the _MKWRITE method,
 * similarly a certain percentage of dirty pages trigger a transition to
 * the _PAGETABLE method. How many triggers should we रुको क्रम beक्रमe
 * changing method?
 */
#घोषणा VMW_सूचीTY_NUM_CHANGE_TRIGGERS 2

/* Percentage to trigger a transition to the _PAGETABLE method */
#घोषणा VMW_सूचीTY_PERCENTAGE 10

/**
 * काष्ठा vmw_bo_dirty - Dirty inक्रमmation क्रम buffer objects
 * @start: First currently dirty bit
 * @end: Last currently dirty bit + 1
 * @method: The currently used dirty method
 * @change_count: Number of consecutive method change triggers
 * @ref_count: Reference count क्रम this काष्ठाure
 * @biपंचांगap_size: The size of the biपंचांगap in bits. Typically equal to the
 * nuber of pages in the bo.
 * @size: The accounting size क्रम this काष्ठा.
 * @biपंचांगap: A biपंचांगap where each bit represents a page. A set bit means a
 * dirty page.
 */
काष्ठा vmw_bo_dirty अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	क्रमागत vmw_bo_dirty_method method;
	अचिन्हित पूर्णांक change_count;
	अचिन्हित पूर्णांक ref_count;
	अचिन्हित दीर्घ biपंचांगap_size;
	माप_प्रकार size;
	अचिन्हित दीर्घ biपंचांगap[];
पूर्ण;

/**
 * vmw_bo_dirty_scan_pagetable - Perक्रमm a pagetable scan क्रम dirty bits
 * @vbo: The buffer object to scan
 *
 * Scans the pagetable क्रम dirty bits. Clear those bits and modअगरy the
 * dirty काष्ठाure with the results. This function may change the
 * dirty-tracking method.
 */
अटल व्योम vmw_bo_dirty_scan_pagetable(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;
	pgoff_t offset = drm_vma_node_start(&vbo->base.base.vma_node);
	काष्ठा address_space *mapping = vbo->base.bdev->dev_mapping;
	pgoff_t num_marked;

	num_marked = clean_record_shared_mapping_range
		(mapping,
		 offset, dirty->biपंचांगap_size,
		 offset, &dirty->biपंचांगap[0],
		 &dirty->start, &dirty->end);
	अगर (num_marked == 0)
		dirty->change_count++;
	अन्यथा
		dirty->change_count = 0;

	अगर (dirty->change_count > VMW_सूचीTY_NUM_CHANGE_TRIGGERS) अणु
		dirty->change_count = 0;
		dirty->method = VMW_BO_सूचीTY_MKWRITE;
		wp_shared_mapping_range(mapping,
					offset, dirty->biपंचांगap_size);
		clean_record_shared_mapping_range(mapping,
						  offset, dirty->biपंचांगap_size,
						  offset, &dirty->biपंचांगap[0],
						  &dirty->start, &dirty->end);
	पूर्ण
पूर्ण

/**
 * vmw_bo_dirty_scan_mkग_लिखो - Reset the mkग_लिखो dirty-tracking method
 * @vbo: The buffer object to scan
 *
 * Write-protect pages written to so that consecutive ग_लिखो accesses will
 * trigger a call to mkग_लिखो.
 *
 * This function may change the dirty-tracking method.
 */
अटल व्योम vmw_bo_dirty_scan_mkग_लिखो(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;
	अचिन्हित दीर्घ offset = drm_vma_node_start(&vbo->base.base.vma_node);
	काष्ठा address_space *mapping = vbo->base.bdev->dev_mapping;
	pgoff_t num_marked;

	अगर (dirty->end <= dirty->start)
		वापस;

	num_marked = wp_shared_mapping_range(vbo->base.bdev->dev_mapping,
					dirty->start + offset,
					dirty->end - dirty->start);

	अगर (100UL * num_marked / dirty->biपंचांगap_size >
	    VMW_सूचीTY_PERCENTAGE) अणु
		dirty->change_count++;
	पूर्ण अन्यथा अणु
		dirty->change_count = 0;
	पूर्ण

	अगर (dirty->change_count > VMW_सूचीTY_NUM_CHANGE_TRIGGERS) अणु
		pgoff_t start = 0;
		pgoff_t end = dirty->biपंचांगap_size;

		dirty->method = VMW_BO_सूचीTY_PAGETABLE;
		clean_record_shared_mapping_range(mapping, offset, end, offset,
						  &dirty->biपंचांगap[0],
						  &start, &end);
		biपंचांगap_clear(&dirty->biपंचांगap[0], 0, dirty->biपंचांगap_size);
		अगर (dirty->start < dirty->end)
			biपंचांगap_set(&dirty->biपंचांगap[0], dirty->start,
				   dirty->end - dirty->start);
		dirty->change_count = 0;
	पूर्ण
पूर्ण

/**
 * vmw_bo_dirty_scan - Scan क्रम dirty pages and add them to the dirty
 * tracking काष्ठाure
 * @vbo: The buffer object to scan
 *
 * This function may change the dirty tracking method.
 */
व्योम vmw_bo_dirty_scan(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;

	अगर (dirty->method == VMW_BO_सूचीTY_PAGETABLE)
		vmw_bo_dirty_scan_pagetable(vbo);
	अन्यथा
		vmw_bo_dirty_scan_mkग_लिखो(vbo);
पूर्ण

/**
 * vmw_bo_dirty_pre_unmap - ग_लिखो-protect and pick up dirty pages beक्रमe
 * an unmap_mapping_range operation.
 * @vbo: The buffer object,
 * @start: First page of the range within the buffer object.
 * @end: Last page of the range within the buffer object + 1.
 *
 * If we're using the _PAGETABLE scan method, we may leak dirty pages
 * when calling unmap_mapping_range(). This function makes sure we pick
 * up all dirty pages.
 */
अटल व्योम vmw_bo_dirty_pre_unmap(काष्ठा vmw_buffer_object *vbo,
				   pgoff_t start, pgoff_t end)
अणु
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;
	अचिन्हित दीर्घ offset = drm_vma_node_start(&vbo->base.base.vma_node);
	काष्ठा address_space *mapping = vbo->base.bdev->dev_mapping;

	अगर (dirty->method != VMW_BO_सूचीTY_PAGETABLE || start >= end)
		वापस;

	wp_shared_mapping_range(mapping, start + offset, end - start);
	clean_record_shared_mapping_range(mapping, start + offset,
					  end - start, offset,
					  &dirty->biपंचांगap[0], &dirty->start,
					  &dirty->end);
पूर्ण

/**
 * vmw_bo_dirty_unmap - Clear all ptes poपूर्णांकing to a range within a bo
 * @vbo: The buffer object,
 * @start: First page of the range within the buffer object.
 * @end: Last page of the range within the buffer object + 1.
 *
 * This is similar to tपंचांग_bo_unmap_भव() except it takes a subrange.
 */
व्योम vmw_bo_dirty_unmap(काष्ठा vmw_buffer_object *vbo,
			pgoff_t start, pgoff_t end)
अणु
	अचिन्हित दीर्घ offset = drm_vma_node_start(&vbo->base.base.vma_node);
	काष्ठा address_space *mapping = vbo->base.bdev->dev_mapping;

	vmw_bo_dirty_pre_unmap(vbo, start, end);
	unmap_shared_mapping_range(mapping, (offset + start) << PAGE_SHIFT,
				   (loff_t) (end - start) << PAGE_SHIFT);
पूर्ण

/**
 * vmw_bo_dirty_add - Add a dirty-tracking user to a buffer object
 * @vbo: The buffer object
 *
 * This function रेजिस्टरs a dirty-tracking user to a buffer object.
 * A user can be क्रम example a resource or a vma in a special user-space
 * mapping.
 *
 * Return: Zero on success, -ENOMEM on memory allocation failure.
 */
पूर्णांक vmw_bo_dirty_add(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;
	pgoff_t num_pages = vbo->base.mem.num_pages;
	माप_प्रकार size, acc_size;
	पूर्णांक ret;
	अटल काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;

	अगर (dirty) अणु
		dirty->ref_count++;
		वापस 0;
	पूर्ण

	size = माप(*dirty) + BITS_TO_LONGS(num_pages) * माप(दीर्घ);
	acc_size = tपंचांग_round_pot(size);
	ret = tपंचांग_mem_global_alloc(&tपंचांग_mem_glob, acc_size, &ctx);
	अगर (ret) अणु
		VMW_DEBUG_USER("Out of graphics memory for buffer object "
			       "dirty tracker.\n");
		वापस ret;
	पूर्ण
	dirty = kvzalloc(size, GFP_KERNEL);
	अगर (!dirty) अणु
		ret = -ENOMEM;
		जाओ out_no_dirty;
	पूर्ण

	dirty->size = acc_size;
	dirty->biपंचांगap_size = num_pages;
	dirty->start = dirty->biपंचांगap_size;
	dirty->end = 0;
	dirty->ref_count = 1;
	अगर (num_pages < PAGE_SIZE / माप(pte_t)) अणु
		dirty->method = VMW_BO_सूचीTY_PAGETABLE;
	पूर्ण अन्यथा अणु
		काष्ठा address_space *mapping = vbo->base.bdev->dev_mapping;
		pgoff_t offset = drm_vma_node_start(&vbo->base.base.vma_node);

		dirty->method = VMW_BO_सूचीTY_MKWRITE;

		/* Write-protect and then pick up alपढ़ोy dirty bits */
		wp_shared_mapping_range(mapping, offset, num_pages);
		clean_record_shared_mapping_range(mapping, offset, num_pages,
						  offset,
						  &dirty->biपंचांगap[0],
						  &dirty->start, &dirty->end);
	पूर्ण

	vbo->dirty = dirty;

	वापस 0;

out_no_dirty:
	tपंचांग_mem_global_मुक्त(&tपंचांग_mem_glob, acc_size);
	वापस ret;
पूर्ण

/**
 * vmw_bo_dirty_release - Release a dirty-tracking user from a buffer object
 * @vbo: The buffer object
 *
 * This function releases a dirty-tracking user from a buffer object.
 * If the reference count reaches zero, then the dirty-tracking object is
 * मुक्तd and the poपूर्णांकer to it cleared.
 *
 * Return: Zero on success, -ENOMEM on memory allocation failure.
 */
व्योम vmw_bo_dirty_release(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;

	अगर (dirty && --dirty->ref_count == 0) अणु
		माप_प्रकार acc_size = dirty->size;

		kvमुक्त(dirty);
		tपंचांग_mem_global_मुक्त(&tपंचांग_mem_glob, acc_size);
		vbo->dirty = शून्य;
	पूर्ण
पूर्ण

/**
 * vmw_bo_dirty_transfer_to_res - Pick up a resource's dirty region from
 * its backing mob.
 * @res: The resource
 *
 * This function will pick up all dirty ranges affecting the resource from
 * it's backup mob, and call vmw_resource_dirty_update() once क्रम each
 * range. The transferred ranges will be cleared from the backing mob's
 * dirty tracking.
 */
व्योम vmw_bo_dirty_transfer_to_res(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_buffer_object *vbo = res->backup;
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;
	pgoff_t start, cur, end;
	अचिन्हित दीर्घ res_start = res->backup_offset;
	अचिन्हित दीर्घ res_end = res->backup_offset + res->backup_size;

	WARN_ON_ONCE(res_start & ~PAGE_MASK);
	res_start >>= PAGE_SHIFT;
	res_end = DIV_ROUND_UP(res_end, PAGE_SIZE);

	अगर (res_start >= dirty->end || res_end <= dirty->start)
		वापस;

	cur = max(res_start, dirty->start);
	res_end = max(res_end, dirty->end);
	जबतक (cur < res_end) अणु
		अचिन्हित दीर्घ num;

		start = find_next_bit(&dirty->biपंचांगap[0], res_end, cur);
		अगर (start >= res_end)
			अवरोध;

		end = find_next_zero_bit(&dirty->biपंचांगap[0], res_end, start + 1);
		cur = end + 1;
		num = end - start;
		biपंचांगap_clear(&dirty->biपंचांगap[0], start, num);
		vmw_resource_dirty_update(res, start, end);
	पूर्ण

	अगर (res_start <= dirty->start && res_end > dirty->start)
		dirty->start = res_end;
	अगर (res_start < dirty->end && res_end >= dirty->end)
		dirty->end = res_start;
पूर्ण

/**
 * vmw_bo_dirty_clear_res - Clear a resource's dirty region from
 * its backing mob.
 * @res: The resource
 *
 * This function will clear all dirty ranges affecting the resource from
 * it's backup mob's dirty tracking.
 */
व्योम vmw_bo_dirty_clear_res(काष्ठा vmw_resource *res)
अणु
	अचिन्हित दीर्घ res_start = res->backup_offset;
	अचिन्हित दीर्घ res_end = res->backup_offset + res->backup_size;
	काष्ठा vmw_buffer_object *vbo = res->backup;
	काष्ठा vmw_bo_dirty *dirty = vbo->dirty;

	res_start >>= PAGE_SHIFT;
	res_end = DIV_ROUND_UP(res_end, PAGE_SIZE);

	अगर (res_start >= dirty->end || res_end <= dirty->start)
		वापस;

	res_start = max(res_start, dirty->start);
	res_end = min(res_end, dirty->end);
	biपंचांगap_clear(&dirty->biपंचांगap[0], res_start, res_end - res_start);

	अगर (res_start <= dirty->start && res_end > dirty->start)
		dirty->start = res_end;
	अगर (res_start < dirty->end && res_end >= dirty->end)
		dirty->end = res_start;
पूर्ण

vm_fault_t vmw_bo_vm_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा tपंचांग_buffer_object *bo = (काष्ठा tपंचांग_buffer_object *)
	    vma->vm_निजी_data;
	vm_fault_t ret;
	अचिन्हित दीर्घ page_offset;
	अचिन्हित पूर्णांक save_flags;
	काष्ठा vmw_buffer_object *vbo =
		container_of(bo, typeof(*vbo), base);

	/*
	 * mkग_लिखो() करोesn't handle the VM_FAULT_RETRY वापस value correctly.
	 * So make sure the TTM helpers are aware.
	 */
	save_flags = vmf->flags;
	vmf->flags &= ~FAULT_FLAG_ALLOW_RETRY;
	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	vmf->flags = save_flags;
	अगर (ret)
		वापस ret;

	page_offset = vmf->pgoff - drm_vma_node_start(&bo->base.vma_node);
	अगर (unlikely(page_offset >= bo->mem.num_pages)) अणु
		ret = VM_FAULT_SIGBUS;
		जाओ out_unlock;
	पूर्ण

	अगर (vbo->dirty && vbo->dirty->method == VMW_BO_सूचीTY_MKWRITE &&
	    !test_bit(page_offset, &vbo->dirty->biपंचांगap[0])) अणु
		काष्ठा vmw_bo_dirty *dirty = vbo->dirty;

		__set_bit(page_offset, &dirty->biपंचांगap[0]);
		dirty->start = min(dirty->start, page_offset);
		dirty->end = max(dirty->end, page_offset + 1);
	पूर्ण

out_unlock:
	dma_resv_unlock(bo->base.resv);
	वापस ret;
पूर्ण

vm_fault_t vmw_bo_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा tपंचांग_buffer_object *bo = (काष्ठा tपंचांग_buffer_object *)
	    vma->vm_निजी_data;
	काष्ठा vmw_buffer_object *vbo =
		container_of(bo, काष्ठा vmw_buffer_object, base);
	pgoff_t num_prefault;
	pgprot_t prot;
	vm_fault_t ret;

	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	अगर (ret)
		वापस ret;

	num_prefault = (vma->vm_flags & VM_RAND_READ) ? 1 :
		TTM_BO_VM_NUM_PREFAULT;

	अगर (vbo->dirty) अणु
		pgoff_t allowed_prefault;
		अचिन्हित दीर्घ page_offset;

		page_offset = vmf->pgoff -
			drm_vma_node_start(&bo->base.vma_node);
		अगर (page_offset >= bo->mem.num_pages ||
		    vmw_resources_clean(vbo, page_offset,
					page_offset + PAGE_SIZE,
					&allowed_prefault)) अणु
			ret = VM_FAULT_SIGBUS;
			जाओ out_unlock;
		पूर्ण

		num_prefault = min(num_prefault, allowed_prefault);
	पूर्ण

	/*
	 * If we करोn't track dirty using the MKWRITE method, make sure
	 * sure the page protection is ग_लिखो-enabled so we करोn't get
	 * a lot of unnecessary ग_लिखो faults.
	 */
	अगर (vbo->dirty && vbo->dirty->method == VMW_BO_सूचीTY_MKWRITE)
		prot = vm_get_page_prot(vma->vm_flags & ~VM_SHARED);
	अन्यथा
		prot = vm_get_page_prot(vma->vm_flags);

	ret = tपंचांग_bo_vm_fault_reserved(vmf, prot, num_prefault, 1);
	अगर (ret == VM_FAULT_RETRY && !(vmf->flags & FAULT_FLAG_RETRY_NOWAIT))
		वापस ret;

out_unlock:
	dma_resv_unlock(bo->base.resv);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
vm_fault_t vmw_bo_vm_huge_fault(काष्ठा vm_fault *vmf,
				क्रमागत page_entry_size pe_size)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा tपंचांग_buffer_object *bo = (काष्ठा tपंचांग_buffer_object *)
	    vma->vm_निजी_data;
	काष्ठा vmw_buffer_object *vbo =
		container_of(bo, काष्ठा vmw_buffer_object, base);
	pgprot_t prot;
	vm_fault_t ret;
	pgoff_t fault_page_size;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;

	चयन (pe_size) अणु
	हाल PE_SIZE_PMD:
		fault_page_size = HPAGE_PMD_SIZE >> PAGE_SHIFT;
		अवरोध;
#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
	हाल PE_SIZE_PUD:
		fault_page_size = HPAGE_PUD_SIZE >> PAGE_SHIFT;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
		वापस VM_FAULT_FALLBACK;
	पूर्ण

	/* Always करो ग_लिखो dirty-tracking and COW on PTE level. */
	अगर (ग_लिखो && (READ_ONCE(vbo->dirty) || is_cow_mapping(vma->vm_flags)))
		वापस VM_FAULT_FALLBACK;

	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	अगर (ret)
		वापस ret;

	अगर (vbo->dirty) अणु
		pgoff_t allowed_prefault;
		अचिन्हित दीर्घ page_offset;

		page_offset = vmf->pgoff -
			drm_vma_node_start(&bo->base.vma_node);
		अगर (page_offset >= bo->mem.num_pages ||
		    vmw_resources_clean(vbo, page_offset,
					page_offset + PAGE_SIZE,
					&allowed_prefault)) अणु
			ret = VM_FAULT_SIGBUS;
			जाओ out_unlock;
		पूर्ण

		/*
		 * Write protect, so we get a new fault on ग_लिखो, and can
		 * split.
		 */
		prot = vm_get_page_prot(vma->vm_flags & ~VM_SHARED);
	पूर्ण अन्यथा अणु
		prot = vm_get_page_prot(vma->vm_flags);
	पूर्ण

	ret = tपंचांग_bo_vm_fault_reserved(vmf, prot, 1, fault_page_size);
	अगर (ret == VM_FAULT_RETRY && !(vmf->flags & FAULT_FLAG_RETRY_NOWAIT))
		वापस ret;

out_unlock:
	dma_resv_unlock(bo->base.resv);

	वापस ret;
पूर्ण
#पूर्ण_अगर
