<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <linux/file.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/sgx.h>
#समावेश "driver.h"
#समावेश "encl.h"
#समावेश "encls.h"

काष्ठा sgx_epc_section sgx_epc_sections[SGX_MAX_EPC_SECTIONS];
अटल पूर्णांक sgx_nr_epc_sections;
अटल काष्ठा task_काष्ठा *ksgxd_tsk;
अटल DECLARE_WAIT_QUEUE_HEAD(ksgxd_रुकोq);

/*
 * These variables are part of the state of the reclaimer, and must be accessed
 * with sgx_reclaimer_lock acquired.
 */
अटल LIST_HEAD(sgx_active_page_list);
अटल DEFINE_SPINLOCK(sgx_reclaimer_lock);

/* The मुक्त page list lock रक्षित variables prepend the lock. */
अटल अचिन्हित दीर्घ sgx_nr_मुक्त_pages;

/* Nodes with one or more EPC sections. */
अटल nodemask_t sgx_numa_mask;

/*
 * Array with one list_head क्रम each possible NUMA node.  Each
 * list contains all the sgx_epc_section's which are on that
 * node.
 */
अटल काष्ठा sgx_numa_node *sgx_numa_nodes;

अटल LIST_HEAD(sgx_dirty_page_list);

/*
 * Reset post-kexec EPC pages to the uninitialized state. The pages are हटाओd
 * from the input list, and made available क्रम the page allocator. SECS pages
 * prepending their children in the input list are left पूर्णांकact.
 */
अटल व्योम __sgx_sanitize_pages(काष्ठा list_head *dirty_page_list)
अणु
	काष्ठा sgx_epc_page *page;
	LIST_HEAD(dirty);
	पूर्णांक ret;

	/* dirty_page_list is thपढ़ो-local, no need क्रम a lock: */
	जबतक (!list_empty(dirty_page_list)) अणु
		अगर (kthपढ़ो_should_stop())
			वापस;

		page = list_first_entry(dirty_page_list, काष्ठा sgx_epc_page, list);

		ret = __eहटाओ(sgx_get_epc_virt_addr(page));
		अगर (!ret) अणु
			/*
			 * page is now sanitized.  Make it available via the SGX
			 * page allocator:
			 */
			list_del(&page->list);
			sgx_मुक्त_epc_page(page);
		पूर्ण अन्यथा अणु
			/* The page is not yet clean - move to the dirty list. */
			list_move_tail(&page->list, &dirty);
		पूर्ण

		cond_resched();
	पूर्ण

	list_splice(&dirty, dirty_page_list);
पूर्ण

अटल bool sgx_reclaimer_age(काष्ठा sgx_epc_page *epc_page)
अणु
	काष्ठा sgx_encl_page *page = epc_page->owner;
	काष्ठा sgx_encl *encl = page->encl;
	काष्ठा sgx_encl_mm *encl_mm;
	bool ret = true;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&encl->srcu);

	list_क्रम_each_entry_rcu(encl_mm, &encl->mm_list, list) अणु
		अगर (!mmget_not_zero(encl_mm->mm))
			जारी;

		mmap_पढ़ो_lock(encl_mm->mm);
		ret = !sgx_encl_test_and_clear_young(encl_mm->mm, page);
		mmap_पढ़ो_unlock(encl_mm->mm);

		mmput_async(encl_mm->mm);

		अगर (!ret)
			अवरोध;
	पूर्ण

	srcu_पढ़ो_unlock(&encl->srcu, idx);

	अगर (!ret)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम sgx_reclaimer_block(काष्ठा sgx_epc_page *epc_page)
अणु
	काष्ठा sgx_encl_page *page = epc_page->owner;
	अचिन्हित दीर्घ addr = page->desc & PAGE_MASK;
	काष्ठा sgx_encl *encl = page->encl;
	अचिन्हित दीर्घ mm_list_version;
	काष्ठा sgx_encl_mm *encl_mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक idx, ret;

	करो अणु
		mm_list_version = encl->mm_list_version;

		/* Pairs with smp_rmb() in sgx_encl_mm_add(). */
		smp_rmb();

		idx = srcu_पढ़ो_lock(&encl->srcu);

		list_क्रम_each_entry_rcu(encl_mm, &encl->mm_list, list) अणु
			अगर (!mmget_not_zero(encl_mm->mm))
				जारी;

			mmap_पढ़ो_lock(encl_mm->mm);

			ret = sgx_encl_find(encl_mm->mm, addr, &vma);
			अगर (!ret && encl == vma->vm_निजी_data)
				zap_vma_ptes(vma, addr, PAGE_SIZE);

			mmap_पढ़ो_unlock(encl_mm->mm);

			mmput_async(encl_mm->mm);
		पूर्ण

		srcu_पढ़ो_unlock(&encl->srcu, idx);
	पूर्ण जबतक (unlikely(encl->mm_list_version != mm_list_version));

	mutex_lock(&encl->lock);

	ret = __eblock(sgx_get_epc_virt_addr(epc_page));
	अगर (encls_failed(ret))
		ENCLS_WARN(ret, "EBLOCK");

	mutex_unlock(&encl->lock);
पूर्ण

अटल पूर्णांक __sgx_encl_ewb(काष्ठा sgx_epc_page *epc_page, व्योम *va_slot,
			  काष्ठा sgx_backing *backing)
अणु
	काष्ठा sgx_pageinfo pginfo;
	पूर्णांक ret;

	pginfo.addr = 0;
	pginfo.secs = 0;

	pginfo.contents = (अचिन्हित दीर्घ)kmap_atomic(backing->contents);
	pginfo.metadata = (अचिन्हित दीर्घ)kmap_atomic(backing->pcmd) +
			  backing->pcmd_offset;

	ret = __ewb(&pginfo, sgx_get_epc_virt_addr(epc_page), va_slot);

	kunmap_atomic((व्योम *)(अचिन्हित दीर्घ)(pginfo.metadata -
					      backing->pcmd_offset));
	kunmap_atomic((व्योम *)(अचिन्हित दीर्घ)pginfo.contents);

	वापस ret;
पूर्ण

अटल व्योम sgx_ipi_cb(व्योम *info)
अणु
पूर्ण

अटल स्थिर cpumask_t *sgx_encl_ewb_cpumask(काष्ठा sgx_encl *encl)
अणु
	cpumask_t *cpumask = &encl->cpumask;
	काष्ठा sgx_encl_mm *encl_mm;
	पूर्णांक idx;

	/*
	 * Can race with sgx_encl_mm_add(), but ETRACK has alपढ़ोy been
	 * executed, which means that the CPUs running in the new mm will enter
	 * पूर्णांकo the enclave with a fresh epoch.
	 */
	cpumask_clear(cpumask);

	idx = srcu_पढ़ो_lock(&encl->srcu);

	list_क्रम_each_entry_rcu(encl_mm, &encl->mm_list, list) अणु
		अगर (!mmget_not_zero(encl_mm->mm))
			जारी;

		cpumask_or(cpumask, cpumask, mm_cpumask(encl_mm->mm));

		mmput_async(encl_mm->mm);
	पूर्ण

	srcu_पढ़ो_unlock(&encl->srcu, idx);

	वापस cpumask;
पूर्ण

/*
 * Swap page to the regular memory transक्रमmed to the blocked state by using
 * EBLOCK, which means that it can no दीर्घer be referenced (no new TLB entries).
 *
 * The first trial just tries to ग_लिखो the page assuming that some other thपढ़ो
 * has reset the count क्रम thपढ़ोs inside the enclave by using ETRACK, and
 * previous thपढ़ो count has been zeroed out. The second trial calls ETRACK
 * beक्रमe EWB. If that fails we kick all the HW thपढ़ोs out, and then करो EWB,
 * which should be guaranteed the succeed.
 */
अटल व्योम sgx_encl_ewb(काष्ठा sgx_epc_page *epc_page,
			 काष्ठा sgx_backing *backing)
अणु
	काष्ठा sgx_encl_page *encl_page = epc_page->owner;
	काष्ठा sgx_encl *encl = encl_page->encl;
	काष्ठा sgx_va_page *va_page;
	अचिन्हित पूर्णांक va_offset;
	व्योम *va_slot;
	पूर्णांक ret;

	encl_page->desc &= ~SGX_ENCL_PAGE_BEING_RECLAIMED;

	va_page = list_first_entry(&encl->va_pages, काष्ठा sgx_va_page,
				   list);
	va_offset = sgx_alloc_va_slot(va_page);
	va_slot = sgx_get_epc_virt_addr(va_page->epc_page) + va_offset;
	अगर (sgx_va_page_full(va_page))
		list_move_tail(&va_page->list, &encl->va_pages);

	ret = __sgx_encl_ewb(epc_page, va_slot, backing);
	अगर (ret == SGX_NOT_TRACKED) अणु
		ret = __etrack(sgx_get_epc_virt_addr(encl->secs.epc_page));
		अगर (ret) अणु
			अगर (encls_failed(ret))
				ENCLS_WARN(ret, "ETRACK");
		पूर्ण

		ret = __sgx_encl_ewb(epc_page, va_slot, backing);
		अगर (ret == SGX_NOT_TRACKED) अणु
			/*
			 * Slow path, send IPIs to kick cpus out of the
			 * enclave.  Note, it's imperative that the cpu
			 * mask is generated *after* ETRACK, अन्यथा we'll
			 * miss cpus that entered the enclave between
			 * generating the mask and incrementing epoch.
			 */
			on_each_cpu_mask(sgx_encl_ewb_cpumask(encl),
					 sgx_ipi_cb, शून्य, 1);
			ret = __sgx_encl_ewb(epc_page, va_slot, backing);
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		अगर (encls_failed(ret))
			ENCLS_WARN(ret, "EWB");

		sgx_मुक्त_va_slot(va_page, va_offset);
	पूर्ण अन्यथा अणु
		encl_page->desc |= va_offset;
		encl_page->va_page = va_page;
	पूर्ण
पूर्ण

अटल व्योम sgx_reclaimer_ग_लिखो(काष्ठा sgx_epc_page *epc_page,
				काष्ठा sgx_backing *backing)
अणु
	काष्ठा sgx_encl_page *encl_page = epc_page->owner;
	काष्ठा sgx_encl *encl = encl_page->encl;
	काष्ठा sgx_backing secs_backing;
	पूर्णांक ret;

	mutex_lock(&encl->lock);

	sgx_encl_ewb(epc_page, backing);
	encl_page->epc_page = शून्य;
	encl->secs_child_cnt--;

	अगर (!encl->secs_child_cnt && test_bit(SGX_ENCL_INITIALIZED, &encl->flags)) अणु
		ret = sgx_encl_get_backing(encl, PFN_DOWN(encl->size),
					   &secs_backing);
		अगर (ret)
			जाओ out;

		sgx_encl_ewb(encl->secs.epc_page, &secs_backing);

		sgx_encl_मुक्त_epc_page(encl->secs.epc_page);
		encl->secs.epc_page = शून्य;

		sgx_encl_put_backing(&secs_backing, true);
	पूर्ण

out:
	mutex_unlock(&encl->lock);
पूर्ण

/*
 * Take a fixed number of pages from the head of the active page pool and
 * reclaim them to the enclave's निजी shmem files. Skip the pages, which have
 * been accessed since the last scan. Move those pages to the tail of active
 * page pool so that the pages get scanned in LRU like fashion.
 *
 * Batch process a chunk of pages (at the moment 16) in order to degrade amount
 * of IPI's and ETRACK's potentially required. sgx_encl_ewb() करोes degrade a bit
 * among the HW thपढ़ोs with three stage EWB pipeline (EWB, ETRACK + EWB and IPI
 * + EWB) but not sufficiently. Reclaiming one page at a समय would also be
 * problematic as it would increase the lock contention too much, which would
 * halt क्रमward progress.
 */
अटल व्योम sgx_reclaim_pages(व्योम)
अणु
	काष्ठा sgx_epc_page *chunk[SGX_NR_TO_SCAN];
	काष्ठा sgx_backing backing[SGX_NR_TO_SCAN];
	काष्ठा sgx_epc_section *section;
	काष्ठा sgx_encl_page *encl_page;
	काष्ठा sgx_epc_page *epc_page;
	काष्ठा sgx_numa_node *node;
	pgoff_t page_index;
	पूर्णांक cnt = 0;
	पूर्णांक ret;
	पूर्णांक i;

	spin_lock(&sgx_reclaimer_lock);
	क्रम (i = 0; i < SGX_NR_TO_SCAN; i++) अणु
		अगर (list_empty(&sgx_active_page_list))
			अवरोध;

		epc_page = list_first_entry(&sgx_active_page_list,
					    काष्ठा sgx_epc_page, list);
		list_del_init(&epc_page->list);
		encl_page = epc_page->owner;

		अगर (kref_get_unless_zero(&encl_page->encl->refcount) != 0)
			chunk[cnt++] = epc_page;
		अन्यथा
			/* The owner is मुक्तing the page. No need to add the
			 * page back to the list of reclaimable pages.
			 */
			epc_page->flags &= ~SGX_EPC_PAGE_RECLAIMER_TRACKED;
	पूर्ण
	spin_unlock(&sgx_reclaimer_lock);

	क्रम (i = 0; i < cnt; i++) अणु
		epc_page = chunk[i];
		encl_page = epc_page->owner;

		अगर (!sgx_reclaimer_age(epc_page))
			जाओ skip;

		page_index = PFN_DOWN(encl_page->desc - encl_page->encl->base);
		ret = sgx_encl_get_backing(encl_page->encl, page_index, &backing[i]);
		अगर (ret)
			जाओ skip;

		mutex_lock(&encl_page->encl->lock);
		encl_page->desc |= SGX_ENCL_PAGE_BEING_RECLAIMED;
		mutex_unlock(&encl_page->encl->lock);
		जारी;

skip:
		spin_lock(&sgx_reclaimer_lock);
		list_add_tail(&epc_page->list, &sgx_active_page_list);
		spin_unlock(&sgx_reclaimer_lock);

		kref_put(&encl_page->encl->refcount, sgx_encl_release);

		chunk[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		epc_page = chunk[i];
		अगर (epc_page)
			sgx_reclaimer_block(epc_page);
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		epc_page = chunk[i];
		अगर (!epc_page)
			जारी;

		encl_page = epc_page->owner;
		sgx_reclaimer_ग_लिखो(epc_page, &backing[i]);
		sgx_encl_put_backing(&backing[i], true);

		kref_put(&encl_page->encl->refcount, sgx_encl_release);
		epc_page->flags &= ~SGX_EPC_PAGE_RECLAIMER_TRACKED;

		section = &sgx_epc_sections[epc_page->section];
		node = section->node;

		spin_lock(&node->lock);
		list_add_tail(&epc_page->list, &node->मुक्त_page_list);
		sgx_nr_मुक्त_pages++;
		spin_unlock(&node->lock);
	पूर्ण
पूर्ण

अटल bool sgx_should_reclaim(अचिन्हित दीर्घ watermark)
अणु
	वापस sgx_nr_मुक्त_pages < watermark && !list_empty(&sgx_active_page_list);
पूर्ण

अटल पूर्णांक ksgxd(व्योम *p)
अणु
	set_मुक्तzable();

	/*
	 * Sanitize pages in order to recover from kexec(). The 2nd pass is
	 * required क्रम SECS pages, whose child pages blocked EREMOVE.
	 */
	__sgx_sanitize_pages(&sgx_dirty_page_list);
	__sgx_sanitize_pages(&sgx_dirty_page_list);

	/* sanity check: */
	WARN_ON(!list_empty(&sgx_dirty_page_list));

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (try_to_मुक्तze())
			जारी;

		रुको_event_मुक्तzable(ksgxd_रुकोq,
				     kthपढ़ो_should_stop() ||
				     sgx_should_reclaim(SGX_NR_HIGH_PAGES));

		अगर (sgx_should_reclaim(SGX_NR_HIGH_PAGES))
			sgx_reclaim_pages();

		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल bool __init sgx_page_reclaimer_init(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk;

	tsk = kthपढ़ो_run(ksgxd, शून्य, "ksgxd");
	अगर (IS_ERR(tsk))
		वापस false;

	ksgxd_tsk = tsk;

	वापस true;
पूर्ण

अटल काष्ठा sgx_epc_page *__sgx_alloc_epc_page_from_node(पूर्णांक nid)
अणु
	काष्ठा sgx_numa_node *node = &sgx_numa_nodes[nid];
	काष्ठा sgx_epc_page *page = शून्य;

	spin_lock(&node->lock);

	अगर (list_empty(&node->मुक्त_page_list)) अणु
		spin_unlock(&node->lock);
		वापस शून्य;
	पूर्ण

	page = list_first_entry(&node->मुक्त_page_list, काष्ठा sgx_epc_page, list);
	list_del_init(&page->list);
	sgx_nr_मुक्त_pages--;

	spin_unlock(&node->lock);

	वापस page;
पूर्ण

/**
 * __sgx_alloc_epc_page() - Allocate an EPC page
 *
 * Iterate through NUMA nodes and reserve ia मुक्त EPC page to the caller. Start
 * from the NUMA node, where the caller is executing.
 *
 * Return:
 * - an EPC page:	A borrowed EPC pages were available.
 * - शून्य:		Out of EPC pages.
 */
काष्ठा sgx_epc_page *__sgx_alloc_epc_page(व्योम)
अणु
	काष्ठा sgx_epc_page *page;
	पूर्णांक nid_of_current = numa_node_id();
	पूर्णांक nid = nid_of_current;

	अगर (node_isset(nid_of_current, sgx_numa_mask)) अणु
		page = __sgx_alloc_epc_page_from_node(nid_of_current);
		अगर (page)
			वापस page;
	पूर्ण

	/* Fall back to the non-local NUMA nodes: */
	जबतक (true) अणु
		nid = next_node_in(nid, sgx_numa_mask);
		अगर (nid == nid_of_current)
			अवरोध;

		page = __sgx_alloc_epc_page_from_node(nid);
		अगर (page)
			वापस page;
	पूर्ण

	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * sgx_mark_page_reclaimable() - Mark a page as reclaimable
 * @page:	EPC page
 *
 * Mark a page as reclaimable and add it to the active page list. Pages
 * are स्वतःmatically हटाओd from the active list when मुक्तd.
 */
व्योम sgx_mark_page_reclaimable(काष्ठा sgx_epc_page *page)
अणु
	spin_lock(&sgx_reclaimer_lock);
	page->flags |= SGX_EPC_PAGE_RECLAIMER_TRACKED;
	list_add_tail(&page->list, &sgx_active_page_list);
	spin_unlock(&sgx_reclaimer_lock);
पूर्ण

/**
 * sgx_unmark_page_reclaimable() - Remove a page from the reclaim list
 * @page:	EPC page
 *
 * Clear the reclaimable flag and हटाओ the page from the active page list.
 *
 * Return:
 *   0 on success,
 *   -EBUSY अगर the page is in the process of being reclaimed
 */
पूर्णांक sgx_unmark_page_reclaimable(काष्ठा sgx_epc_page *page)
अणु
	spin_lock(&sgx_reclaimer_lock);
	अगर (page->flags & SGX_EPC_PAGE_RECLAIMER_TRACKED) अणु
		/* The page is being reclaimed. */
		अगर (list_empty(&page->list)) अणु
			spin_unlock(&sgx_reclaimer_lock);
			वापस -EBUSY;
		पूर्ण

		list_del(&page->list);
		page->flags &= ~SGX_EPC_PAGE_RECLAIMER_TRACKED;
	पूर्ण
	spin_unlock(&sgx_reclaimer_lock);

	वापस 0;
पूर्ण

/**
 * sgx_alloc_epc_page() - Allocate an EPC page
 * @owner:	the owner of the EPC page
 * @reclaim:	reclaim pages अगर necessary
 *
 * Iterate through EPC sections and borrow a मुक्त EPC page to the caller. When a
 * page is no दीर्घer needed it must be released with sgx_मुक्त_epc_page(). If
 * @reclaim is set to true, directly reclaim pages when we are out of pages. No
 * mm's can be locked when @reclaim is set to true.
 *
 * Finally, wake up ksgxd when the number of pages goes below the watermark
 * beक्रमe वापसing back to the caller.
 *
 * Return:
 *   an EPC page,
 *   -त्रुटि_सं on error
 */
काष्ठा sgx_epc_page *sgx_alloc_epc_page(व्योम *owner, bool reclaim)
अणु
	काष्ठा sgx_epc_page *page;

	क्रम ( ; ; ) अणु
		page = __sgx_alloc_epc_page();
		अगर (!IS_ERR(page)) अणु
			page->owner = owner;
			अवरोध;
		पूर्ण

		अगर (list_empty(&sgx_active_page_list))
			वापस ERR_PTR(-ENOMEM);

		अगर (!reclaim) अणु
			page = ERR_PTR(-EBUSY);
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			page = ERR_PTR(-ERESTARTSYS);
			अवरोध;
		पूर्ण

		sgx_reclaim_pages();
		cond_resched();
	पूर्ण

	अगर (sgx_should_reclaim(SGX_NR_LOW_PAGES))
		wake_up(&ksgxd_रुकोq);

	वापस page;
पूर्ण

/**
 * sgx_मुक्त_epc_page() - Free an EPC page
 * @page:	an EPC page
 *
 * Put the EPC page back to the list of मुक्त pages. It's the caller's
 * responsibility to make sure that the page is in uninitialized state. In other
 * words, करो EREMOVE, EWB or whatever operation is necessary beक्रमe calling
 * this function.
 */
व्योम sgx_मुक्त_epc_page(काष्ठा sgx_epc_page *page)
अणु
	काष्ठा sgx_epc_section *section = &sgx_epc_sections[page->section];
	काष्ठा sgx_numa_node *node = section->node;

	spin_lock(&node->lock);

	list_add_tail(&page->list, &node->मुक्त_page_list);
	sgx_nr_मुक्त_pages++;

	spin_unlock(&node->lock);
पूर्ण

अटल bool __init sgx_setup_epc_section(u64 phys_addr, u64 size,
					 अचिन्हित दीर्घ index,
					 काष्ठा sgx_epc_section *section)
अणु
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	अचिन्हित दीर्घ i;

	section->virt_addr = memremap(phys_addr, size, MEMREMAP_WB);
	अगर (!section->virt_addr)
		वापस false;

	section->pages = vदो_स्मृति(nr_pages * माप(काष्ठा sgx_epc_page));
	अगर (!section->pages) अणु
		memunmap(section->virt_addr);
		वापस false;
	पूर्ण

	section->phys_addr = phys_addr;

	क्रम (i = 0; i < nr_pages; i++) अणु
		section->pages[i].section = index;
		section->pages[i].flags = 0;
		section->pages[i].owner = शून्य;
		list_add_tail(&section->pages[i].list, &sgx_dirty_page_list);
	पूर्ण

	वापस true;
पूर्ण

/**
 * A section metric is concatenated in a way that @low bits 12-31 define the
 * bits 12-31 of the metric and @high bits 0-19 define the bits 32-51 of the
 * metric.
 */
अटल अंतरभूत u64 __init sgx_calc_section_metric(u64 low, u64 high)
अणु
	वापस (low & GENMASK_ULL(31, 12)) +
	       ((high & GENMASK_ULL(19, 0)) << 32);
पूर्ण

अटल bool __init sgx_page_cache_init(व्योम)
अणु
	u32 eax, ebx, ecx, edx, type;
	u64 pa, size;
	पूर्णांक nid;
	पूर्णांक i;

	sgx_numa_nodes = kदो_स्मृति_array(num_possible_nodes(), माप(*sgx_numa_nodes), GFP_KERNEL);
	अगर (!sgx_numa_nodes)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(sgx_epc_sections); i++) अणु
		cpuid_count(SGX_CPUID, i + SGX_CPUID_EPC, &eax, &ebx, &ecx, &edx);

		type = eax & SGX_CPUID_EPC_MASK;
		अगर (type == SGX_CPUID_EPC_INVALID)
			अवरोध;

		अगर (type != SGX_CPUID_EPC_SECTION) अणु
			pr_err_once("Unknown EPC section type: %u\n", type);
			अवरोध;
		पूर्ण

		pa   = sgx_calc_section_metric(eax, ebx);
		size = sgx_calc_section_metric(ecx, edx);

		pr_info("EPC section 0x%llx-0x%llx\n", pa, pa + size - 1);

		अगर (!sgx_setup_epc_section(pa, size, i, &sgx_epc_sections[i])) अणु
			pr_err("No free memory for an EPC section\n");
			अवरोध;
		पूर्ण

		nid = numa_map_to_online_node(phys_to_target_node(pa));
		अगर (nid == NUMA_NO_NODE) अणु
			/* The physical address is alपढ़ोy prपूर्णांकed above. */
			pr_warn(FW_BUG "Unable to map EPC section to online node. Fallback to the NUMA node 0.\n");
			nid = 0;
		पूर्ण

		अगर (!node_isset(nid, sgx_numa_mask)) अणु
			spin_lock_init(&sgx_numa_nodes[nid].lock);
			INIT_LIST_HEAD(&sgx_numa_nodes[nid].मुक्त_page_list);
			node_set(nid, sgx_numa_mask);
		पूर्ण

		sgx_epc_sections[i].node =  &sgx_numa_nodes[nid];

		sgx_nr_epc_sections++;
	पूर्ण

	अगर (!sgx_nr_epc_sections) अणु
		pr_err("There are zero EPC sections.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Update the SGX_LEPUBKEYHASH MSRs to the values specअगरied by caller.
 * Bare-metal driver requires to update them to hash of enclave's signer
 * beक्रमe EINIT. KVM needs to update them to guest's भव MSR values
 * beक्रमe करोing EINIT from guest.
 */
व्योम sgx_update_lepubkeyhash(u64 *lepubkeyhash)
अणु
	पूर्णांक i;

	WARN_ON_ONCE(preemptible());

	क्रम (i = 0; i < 4; i++)
		wrmsrl(MSR_IA32_SGXLEPUBKEYHASH0 + i, lepubkeyhash[i]);
पूर्ण

स्थिर काष्ठा file_operations sgx_provision_fops = अणु
	.owner			= THIS_MODULE,
पूर्ण;

अटल काष्ठा miscdevice sgx_dev_provision = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "sgx_provision",
	.nodename = "sgx_provision",
	.fops = &sgx_provision_fops,
पूर्ण;

/**
 * sgx_set_attribute() - Update allowed attributes given file descriptor
 * @allowed_attributes:		Poपूर्णांकer to allowed enclave attributes
 * @attribute_fd:		File descriptor क्रम specअगरic attribute
 *
 * Append enclave attribute indicated by file descriptor to allowed
 * attributes. Currently only SGX_ATTR_PROVISIONKEY indicated by
 * /dev/sgx_provision is supported.
 *
 * Return:
 * -0:		SGX_ATTR_PROVISIONKEY is appended to allowed_attributes
 * -EINVAL:	Invalid, or not supported file descriptor
 */
पूर्णांक sgx_set_attribute(अचिन्हित दीर्घ *allowed_attributes,
		      अचिन्हित पूर्णांक attribute_fd)
अणु
	काष्ठा file *file;

	file = fget(attribute_fd);
	अगर (!file)
		वापस -EINVAL;

	अगर (file->f_op != &sgx_provision_fops) अणु
		fput(file);
		वापस -EINVAL;
	पूर्ण

	*allowed_attributes |= SGX_ATTR_PROVISIONKEY;

	fput(file);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sgx_set_attribute);

अटल पूर्णांक __init sgx_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!cpu_feature_enabled(X86_FEATURE_SGX))
		वापस -ENODEV;

	अगर (!sgx_page_cache_init())
		वापस -ENOMEM;

	अगर (!sgx_page_reclaimer_init()) अणु
		ret = -ENOMEM;
		जाओ err_page_cache;
	पूर्ण

	ret = misc_रेजिस्टर(&sgx_dev_provision);
	अगर (ret)
		जाओ err_kthपढ़ो;

	/*
	 * Always try to initialize the native *and* KVM drivers.
	 * The KVM driver is less picky than the native one and
	 * can function अगर the native one is not supported on the
	 * current प्रणाली or fails to initialize.
	 *
	 * Error out only अगर both fail to initialize.
	 */
	ret = sgx_drv_init();

	अगर (sgx_vepc_init() && ret)
		जाओ err_provision;

	वापस 0;

err_provision:
	misc_deरेजिस्टर(&sgx_dev_provision);

err_kthपढ़ो:
	kthपढ़ो_stop(ksgxd_tsk);

err_page_cache:
	क्रम (i = 0; i < sgx_nr_epc_sections; i++) अणु
		vमुक्त(sgx_epc_sections[i].pages);
		memunmap(sgx_epc_sections[i].virt_addr);
	पूर्ण

	वापस ret;
पूर्ण

device_initcall(sgx_init);
