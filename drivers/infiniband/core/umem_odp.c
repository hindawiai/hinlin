<शैली गुरु>
/*
 * Copyright (c) 2014 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/pid.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/पूर्णांकerval_tree.h>
#समावेश <linux/hmm.h>
#समावेश <linux/pagemap.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_umem_odp.h>

#समावेश "uverbs.h"

अटल अंतरभूत पूर्णांक ib_init_umem_odp(काष्ठा ib_umem_odp *umem_odp,
				   स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	पूर्णांक ret;

	umem_odp->umem.is_odp = 1;
	mutex_init(&umem_odp->umem_mutex);

	अगर (!umem_odp->is_implicit_odp) अणु
		माप_प्रकार page_size = 1UL << umem_odp->page_shअगरt;
		अचिन्हित दीर्घ start;
		अचिन्हित दीर्घ end;
		माप_प्रकार ndmas, npfns;

		start = ALIGN_DOWN(umem_odp->umem.address, page_size);
		अगर (check_add_overflow(umem_odp->umem.address,
				       (अचिन्हित दीर्घ)umem_odp->umem.length,
				       &end))
			वापस -EOVERFLOW;
		end = ALIGN(end, page_size);
		अगर (unlikely(end < page_size))
			वापस -EOVERFLOW;

		ndmas = (end - start) >> umem_odp->page_shअगरt;
		अगर (!ndmas)
			वापस -EINVAL;

		npfns = (end - start) >> PAGE_SHIFT;
		umem_odp->pfn_list = kvसुस्मृति(
			npfns, माप(*umem_odp->pfn_list), GFP_KERNEL);
		अगर (!umem_odp->pfn_list)
			वापस -ENOMEM;

		umem_odp->dma_list = kvसुस्मृति(
			ndmas, माप(*umem_odp->dma_list), GFP_KERNEL);
		अगर (!umem_odp->dma_list) अणु
			ret = -ENOMEM;
			जाओ out_pfn_list;
		पूर्ण

		ret = mmu_पूर्णांकerval_notअगरier_insert(&umem_odp->notअगरier,
						   umem_odp->umem.owning_mm,
						   start, end - start, ops);
		अगर (ret)
			जाओ out_dma_list;
	पूर्ण

	वापस 0;

out_dma_list:
	kvमुक्त(umem_odp->dma_list);
out_pfn_list:
	kvमुक्त(umem_odp->pfn_list);
	वापस ret;
पूर्ण

/**
 * ib_umem_odp_alloc_implicit - Allocate a parent implicit ODP umem
 *
 * Implicit ODP umems करो not have a VA range and करो not have any page lists.
 * They exist only to hold the per_mm reference to help the driver create
 * children umems.
 *
 * @device: IB device to create UMEM
 * @access: ib_reg_mr access flags
 */
काष्ठा ib_umem_odp *ib_umem_odp_alloc_implicit(काष्ठा ib_device *device,
					       पूर्णांक access)
अणु
	काष्ठा ib_umem *umem;
	काष्ठा ib_umem_odp *umem_odp;
	पूर्णांक ret;

	अगर (access & IB_ACCESS_HUGETLB)
		वापस ERR_PTR(-EINVAL);

	umem_odp = kzalloc(माप(*umem_odp), GFP_KERNEL);
	अगर (!umem_odp)
		वापस ERR_PTR(-ENOMEM);
	umem = &umem_odp->umem;
	umem->ibdev = device;
	umem->writable = ib_access_writable(access);
	umem->owning_mm = current->mm;
	umem_odp->is_implicit_odp = 1;
	umem_odp->page_shअगरt = PAGE_SHIFT;

	umem_odp->tgid = get_task_pid(current->group_leader, PIDTYPE_PID);
	ret = ib_init_umem_odp(umem_odp, शून्य);
	अगर (ret) अणु
		put_pid(umem_odp->tgid);
		kमुक्त(umem_odp);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस umem_odp;
पूर्ण
EXPORT_SYMBOL(ib_umem_odp_alloc_implicit);

/**
 * ib_umem_odp_alloc_child - Allocate a child ODP umem under an implicit
 *                           parent ODP umem
 *
 * @root: The parent umem enclosing the child. This must be allocated using
 *        ib_alloc_implicit_odp_umem()
 * @addr: The starting userspace VA
 * @size: The length of the userspace VA
 * @ops: MMU पूर्णांकerval ops, currently only @invalidate
 */
काष्ठा ib_umem_odp *
ib_umem_odp_alloc_child(काष्ठा ib_umem_odp *root, अचिन्हित दीर्घ addr,
			माप_प्रकार size,
			स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	/*
	 * Caller must ensure that root cannot be मुक्तd during the call to
	 * ib_alloc_odp_umem.
	 */
	काष्ठा ib_umem_odp *odp_data;
	काष्ठा ib_umem *umem;
	पूर्णांक ret;

	अगर (WARN_ON(!root->is_implicit_odp))
		वापस ERR_PTR(-EINVAL);

	odp_data = kzalloc(माप(*odp_data), GFP_KERNEL);
	अगर (!odp_data)
		वापस ERR_PTR(-ENOMEM);
	umem = &odp_data->umem;
	umem->ibdev = root->umem.ibdev;
	umem->length     = size;
	umem->address    = addr;
	umem->writable   = root->umem.writable;
	umem->owning_mm  = root->umem.owning_mm;
	odp_data->page_shअगरt = PAGE_SHIFT;
	odp_data->notअगरier.ops = ops;

	/*
	 * A mmget must be held when रेजिस्टरing a notअगरier, the owming_mm only
	 * has a mm_grab at this poपूर्णांक.
	 */
	अगर (!mmget_not_zero(umem->owning_mm)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	odp_data->tgid = get_pid(root->tgid);
	ret = ib_init_umem_odp(odp_data, ops);
	अगर (ret)
		जाओ out_tgid;
	mmput(umem->owning_mm);
	वापस odp_data;

out_tgid:
	put_pid(odp_data->tgid);
	mmput(umem->owning_mm);
out_मुक्त:
	kमुक्त(odp_data);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(ib_umem_odp_alloc_child);

/**
 * ib_umem_odp_get - Create a umem_odp क्रम a userspace va
 *
 * @device: IB device काष्ठा to get UMEM
 * @addr: userspace भव address to start at
 * @size: length of region to pin
 * @access: IB_ACCESS_xxx flags क्रम memory being pinned
 * @ops: MMU पूर्णांकerval ops, currently only @invalidate
 *
 * The driver should use when the access flags indicate ODP memory. It aव्योमs
 * pinning, instead, stores the mm क्रम future page fault handling in
 * conjunction with MMU notअगरiers.
 */
काष्ठा ib_umem_odp *ib_umem_odp_get(काष्ठा ib_device *device,
				    अचिन्हित दीर्घ addr, माप_प्रकार size, पूर्णांक access,
				    स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	काष्ठा ib_umem_odp *umem_odp;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(!(access & IB_ACCESS_ON_DEMAND)))
		वापस ERR_PTR(-EINVAL);

	umem_odp = kzalloc(माप(काष्ठा ib_umem_odp), GFP_KERNEL);
	अगर (!umem_odp)
		वापस ERR_PTR(-ENOMEM);

	umem_odp->umem.ibdev = device;
	umem_odp->umem.length = size;
	umem_odp->umem.address = addr;
	umem_odp->umem.writable = ib_access_writable(access);
	umem_odp->umem.owning_mm = mm = current->mm;
	umem_odp->notअगरier.ops = ops;

	umem_odp->page_shअगरt = PAGE_SHIFT;
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (access & IB_ACCESS_HUGETLB)
		umem_odp->page_shअगरt = HPAGE_SHIFT;
#पूर्ण_अगर

	umem_odp->tgid = get_task_pid(current->group_leader, PIDTYPE_PID);
	ret = ib_init_umem_odp(umem_odp, ops);
	अगर (ret)
		जाओ err_put_pid;
	वापस umem_odp;

err_put_pid:
	put_pid(umem_odp->tgid);
	kमुक्त(umem_odp);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(ib_umem_odp_get);

व्योम ib_umem_odp_release(काष्ठा ib_umem_odp *umem_odp)
अणु
	/*
	 * Ensure that no more pages are mapped in the umem.
	 *
	 * It is the driver's responsibility to ensure, beक्रमe calling us,
	 * that the hardware will not attempt to access the MR any more.
	 */
	अगर (!umem_odp->is_implicit_odp) अणु
		mutex_lock(&umem_odp->umem_mutex);
		ib_umem_odp_unmap_dma_pages(umem_odp, ib_umem_start(umem_odp),
					    ib_umem_end(umem_odp));
		mutex_unlock(&umem_odp->umem_mutex);
		mmu_पूर्णांकerval_notअगरier_हटाओ(&umem_odp->notअगरier);
		kvमुक्त(umem_odp->dma_list);
		kvमुक्त(umem_odp->pfn_list);
	पूर्ण
	put_pid(umem_odp->tgid);
	kमुक्त(umem_odp);
पूर्ण
EXPORT_SYMBOL(ib_umem_odp_release);

/*
 * Map क्रम DMA and insert a single page पूर्णांकo the on-demand paging page tables.
 *
 * @umem: the umem to insert the page to.
 * @dma_index: index in the umem to add the dma to.
 * @page: the page काष्ठा to map and add.
 * @access_mask: access permissions needed क्रम this page.
 * @current_seq: sequence number क्रम synchronization with invalidations.
 *               the sequence number is taken from
 *               umem_odp->notअगरiers_seq.
 *
 * The function वापसs -EFAULT अगर the DMA mapping operation fails.
 *
 */
अटल पूर्णांक ib_umem_odp_map_dma_single_page(
		काष्ठा ib_umem_odp *umem_odp,
		अचिन्हित पूर्णांक dma_index,
		काष्ठा page *page,
		u64 access_mask)
अणु
	काष्ठा ib_device *dev = umem_odp->umem.ibdev;
	dma_addr_t *dma_addr = &umem_odp->dma_list[dma_index];

	अगर (*dma_addr) अणु
		/*
		 * If the page is alपढ़ोy dma mapped it means it went through
		 * a non-invalidating trasition, like पढ़ो-only to writable.
		 * Resync the flags.
		 */
		*dma_addr = (*dma_addr & ODP_DMA_ADDR_MASK) | access_mask;
		वापस 0;
	पूर्ण

	*dma_addr = ib_dma_map_page(dev, page, 0, 1 << umem_odp->page_shअगरt,
				    DMA_BIसूचीECTIONAL);
	अगर (ib_dma_mapping_error(dev, *dma_addr)) अणु
		*dma_addr = 0;
		वापस -EFAULT;
	पूर्ण
	umem_odp->npages++;
	*dma_addr |= access_mask;
	वापस 0;
पूर्ण

/**
 * ib_umem_odp_map_dma_and_lock - DMA map userspace memory in an ODP MR and lock it.
 *
 * Maps the range passed in the argument to DMA addresses.
 * The DMA addresses of the mapped pages is updated in umem_odp->dma_list.
 * Upon success the ODP MR will be locked to let caller complete its device
 * page table update.
 *
 * Returns the number of pages mapped in success, negative error code
 * क्रम failure.
 * @umem_odp: the umem to map and pin
 * @user_virt: the address from which we need to map.
 * @bcnt: the minimal number of bytes to pin and map. The mapping might be
 *        bigger due to alignment, and may also be smaller in हाल of an error
 *        pinning or mapping a page. The actual pages mapped is वापसed in
 *        the वापस value.
 * @access_mask: bit mask of the requested access permissions क्रम the given
 *               range.
 * @fault: is faulting required क्रम the given range
 */
पूर्णांक ib_umem_odp_map_dma_and_lock(काष्ठा ib_umem_odp *umem_odp, u64 user_virt,
				 u64 bcnt, u64 access_mask, bool fault)
			__acquires(&umem_odp->umem_mutex)
अणु
	काष्ठा task_काष्ठा *owning_process  = शून्य;
	काष्ठा mm_काष्ठा *owning_mm = umem_odp->umem.owning_mm;
	पूर्णांक pfn_index, dma_index, ret = 0, start_idx;
	अचिन्हित पूर्णांक page_shअगरt, hmm_order, pfn_start_idx;
	अचिन्हित दीर्घ num_pfns, current_seq;
	काष्ठा hmm_range range = अणुपूर्ण;
	अचिन्हित दीर्घ समयout;

	अगर (access_mask == 0)
		वापस -EINVAL;

	अगर (user_virt < ib_umem_start(umem_odp) ||
	    user_virt + bcnt > ib_umem_end(umem_odp))
		वापस -EFAULT;

	page_shअगरt = umem_odp->page_shअगरt;

	/*
	 * owning_process is allowed to be शून्य, this means somehow the mm is
	 * existing beyond the lअगरeसमय of the originating process.. Presumably
	 * mmget_not_zero will fail in this हाल.
	 */
	owning_process = get_pid_task(umem_odp->tgid, PIDTYPE_PID);
	अगर (!owning_process || !mmget_not_zero(owning_mm)) अणु
		ret = -EINVAL;
		जाओ out_put_task;
	पूर्ण

	range.notअगरier = &umem_odp->notअगरier;
	range.start = ALIGN_DOWN(user_virt, 1UL << page_shअगरt);
	range.end = ALIGN(user_virt + bcnt, 1UL << page_shअगरt);
	pfn_start_idx = (range.start - ib_umem_start(umem_odp)) >> PAGE_SHIFT;
	num_pfns = (range.end - range.start) >> PAGE_SHIFT;
	अगर (fault) अणु
		range.शेष_flags = HMM_PFN_REQ_FAULT;

		अगर (access_mask & ODP_WRITE_ALLOWED_BIT)
			range.शेष_flags |= HMM_PFN_REQ_WRITE;
	पूर्ण

	range.hmm_pfns = &(umem_odp->pfn_list[pfn_start_idx]);
	समयout = jअगरfies + msecs_to_jअगरfies(HMM_RANGE_DEFAULT_TIMEOUT);

retry:
	current_seq = range.notअगरier_seq =
		mmu_पूर्णांकerval_पढ़ो_begin(&umem_odp->notअगरier);

	mmap_पढ़ो_lock(owning_mm);
	ret = hmm_range_fault(&range);
	mmap_पढ़ो_unlock(owning_mm);
	अगर (unlikely(ret)) अणु
		अगर (ret == -EBUSY && !समय_after(jअगरfies, समयout))
			जाओ retry;
		जाओ out_put_mm;
	पूर्ण

	start_idx = (range.start - ib_umem_start(umem_odp)) >> page_shअगरt;
	dma_index = start_idx;

	mutex_lock(&umem_odp->umem_mutex);
	अगर (mmu_पूर्णांकerval_पढ़ो_retry(&umem_odp->notअगरier, current_seq)) अणु
		mutex_unlock(&umem_odp->umem_mutex);
		जाओ retry;
	पूर्ण

	क्रम (pfn_index = 0; pfn_index < num_pfns;
		pfn_index += 1 << (page_shअगरt - PAGE_SHIFT), dma_index++) अणु

		अगर (fault) अणु
			/*
			 * Since we asked क्रम hmm_range_fault() to populate
			 * pages it shouldn't वापस an error entry on success.
			 */
			WARN_ON(range.hmm_pfns[pfn_index] & HMM_PFN_ERROR);
			WARN_ON(!(range.hmm_pfns[pfn_index] & HMM_PFN_VALID));
		पूर्ण अन्यथा अणु
			अगर (!(range.hmm_pfns[pfn_index] & HMM_PFN_VALID)) अणु
				WARN_ON(umem_odp->dma_list[dma_index]);
				जारी;
			पूर्ण
			access_mask = ODP_READ_ALLOWED_BIT;
			अगर (range.hmm_pfns[pfn_index] & HMM_PFN_WRITE)
				access_mask |= ODP_WRITE_ALLOWED_BIT;
		पूर्ण

		hmm_order = hmm_pfn_to_map_order(range.hmm_pfns[pfn_index]);
		/* If a hugepage was detected and ODP wasn't set क्रम, the umem
		 * page_shअगरt will be used, the opposite हाल is an error.
		 */
		अगर (hmm_order + PAGE_SHIFT < page_shअगरt) अणु
			ret = -EINVAL;
			ibdev_dbg(umem_odp->umem.ibdev,
				  "%s: un-expected hmm_order %d, page_shift %d\n",
				  __func__, hmm_order, page_shअगरt);
			अवरोध;
		पूर्ण

		ret = ib_umem_odp_map_dma_single_page(
				umem_odp, dma_index, hmm_pfn_to_page(range.hmm_pfns[pfn_index]),
				access_mask);
		अगर (ret < 0) अणु
			ibdev_dbg(umem_odp->umem.ibdev,
				  "ib_umem_odp_map_dma_single_page failed with error %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण
	/* upon sucesss lock should stay on hold क्रम the callee */
	अगर (!ret)
		ret = dma_index - start_idx;
	अन्यथा
		mutex_unlock(&umem_odp->umem_mutex);

out_put_mm:
	mmput(owning_mm);
out_put_task:
	अगर (owning_process)
		put_task_काष्ठा(owning_process);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_umem_odp_map_dma_and_lock);

व्योम ib_umem_odp_unmap_dma_pages(काष्ठा ib_umem_odp *umem_odp, u64 virt,
				 u64 bound)
अणु
	dma_addr_t dma_addr;
	dma_addr_t dma;
	पूर्णांक idx;
	u64 addr;
	काष्ठा ib_device *dev = umem_odp->umem.ibdev;

	lockdep_निश्चित_held(&umem_odp->umem_mutex);

	virt = max_t(u64, virt, ib_umem_start(umem_odp));
	bound = min_t(u64, bound, ib_umem_end(umem_odp));
	क्रम (addr = virt; addr < bound; addr += BIT(umem_odp->page_shअगरt)) अणु
		idx = (addr - ib_umem_start(umem_odp)) >> umem_odp->page_shअगरt;
		dma = umem_odp->dma_list[idx];

		/* The access flags guaranteed a valid DMA address in हाल was शून्य */
		अगर (dma) अणु
			अचिन्हित दीर्घ pfn_idx = (addr - ib_umem_start(umem_odp)) >> PAGE_SHIFT;
			काष्ठा page *page = hmm_pfn_to_page(umem_odp->pfn_list[pfn_idx]);

			dma_addr = dma & ODP_DMA_ADDR_MASK;
			ib_dma_unmap_page(dev, dma_addr,
					  BIT(umem_odp->page_shअगरt),
					  DMA_BIसूचीECTIONAL);
			अगर (dma & ODP_WRITE_ALLOWED_BIT) अणु
				काष्ठा page *head_page = compound_head(page);
				/*
				 * set_page_dirty prefers being called with
				 * the page lock. However, MMU notअगरiers are
				 * called someबार with and someबार without
				 * the lock. We rely on the umem_mutex instead
				 * to prevent other mmu notअगरiers from
				 * continuing and allowing the page mapping to
				 * be हटाओd.
				 */
				set_page_dirty(head_page);
			पूर्ण
			umem_odp->dma_list[idx] = 0;
			umem_odp->npages--;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ib_umem_odp_unmap_dma_pages);
