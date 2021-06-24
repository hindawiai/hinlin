<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  fs/userfaultfd.c
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *  Copyright (C) 2008-2009 Red Hat, Inc.
 *  Copyright (C) 2015  Red Hat, Inc.
 *
 *  Some part derived from fs/eventfd.c (anon inode setup) and
 *  mm/ksm.c (mm hashing).
 */

#समावेश <linux/list.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/file.h>
#समावेश <linux/bug.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/security.h>
#समावेश <linux/hugetlb.h>

पूर्णांक sysctl_unprivileged_userfaultfd __पढ़ो_mostly;

अटल काष्ठा kmem_cache *userfaultfd_ctx_cachep __पढ़ो_mostly;

क्रमागत userfaultfd_state अणु
	UFFD_STATE_WAIT_API,
	UFFD_STATE_RUNNING,
पूर्ण;

/*
 * Start with fault_pending_wqh and fault_wqh so they're more likely
 * to be in the same cacheline.
 *
 * Locking order:
 *	fd_wqh.lock
 *		fault_pending_wqh.lock
 *			fault_wqh.lock
 *		event_wqh.lock
 *
 * To aव्योम deadlocks, IRQs must be disabled when taking any of the above locks,
 * since fd_wqh.lock is taken by aio_poll() जबतक it's holding a lock that's
 * also taken in IRQ context.
 */
काष्ठा userfaultfd_ctx अणु
	/* रुकोqueue head क्रम the pending (i.e. not पढ़ो) userfaults */
	रुको_queue_head_t fault_pending_wqh;
	/* रुकोqueue head क्रम the userfaults */
	रुको_queue_head_t fault_wqh;
	/* रुकोqueue head क्रम the pseuकरो fd to wakeup poll/पढ़ो */
	रुको_queue_head_t fd_wqh;
	/* रुकोqueue head क्रम events */
	रुको_queue_head_t event_wqh;
	/* a refile sequence रक्षित by fault_pending_wqh lock */
	seqcount_spinlock_t refile_seq;
	/* pseuकरो fd refcounting */
	refcount_t refcount;
	/* userfaultfd syscall flags */
	अचिन्हित पूर्णांक flags;
	/* features requested from the userspace */
	अचिन्हित पूर्णांक features;
	/* state machine */
	क्रमागत userfaultfd_state state;
	/* released */
	bool released;
	/* memory mappings are changing because of non-cooperative event */
	bool mmap_changing;
	/* mm with one ore more vmas attached to this userfaultfd_ctx */
	काष्ठा mm_काष्ठा *mm;
पूर्ण;

काष्ठा userfaultfd_विभाजन_ctx अणु
	काष्ठा userfaultfd_ctx *orig;
	काष्ठा userfaultfd_ctx *new;
	काष्ठा list_head list;
पूर्ण;

काष्ठा userfaultfd_unmap_ctx अणु
	काष्ठा userfaultfd_ctx *ctx;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	काष्ठा list_head list;
पूर्ण;

काष्ठा userfaultfd_रुको_queue अणु
	काष्ठा uffd_msg msg;
	रुको_queue_entry_t wq;
	काष्ठा userfaultfd_ctx *ctx;
	bool waken;
पूर्ण;

काष्ठा userfaultfd_wake_range अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ len;
पूर्ण;

अटल पूर्णांक userfaultfd_wake_function(रुको_queue_entry_t *wq, अचिन्हित mode,
				     पूर्णांक wake_flags, व्योम *key)
अणु
	काष्ठा userfaultfd_wake_range *range = key;
	पूर्णांक ret;
	काष्ठा userfaultfd_रुको_queue *uwq;
	अचिन्हित दीर्घ start, len;

	uwq = container_of(wq, काष्ठा userfaultfd_रुको_queue, wq);
	ret = 0;
	/* len == 0 means wake all */
	start = range->start;
	len = range->len;
	अगर (len && (start > uwq->msg.arg.pagefault.address ||
		    start + len <= uwq->msg.arg.pagefault.address))
		जाओ out;
	WRITE_ONCE(uwq->waken, true);
	/*
	 * The Program-Order guarantees provided by the scheduler
	 * ensure uwq->waken is visible beक्रमe the task is woken.
	 */
	ret = wake_up_state(wq->निजी, mode);
	अगर (ret) अणु
		/*
		 * Wake only once, स्वतःहटाओ behavior.
		 *
		 * After the effect of list_del_init is visible to the other
		 * CPUs, the रुकोqueue may disappear from under us, see the
		 * !list_empty_careful() in handle_userfault().
		 *
		 * try_to_wake_up() has an implicit smp_mb(), and the
		 * wq->निजी is पढ़ो beक्रमe calling the बाह्य function
		 * "wake_up_state" (which in turns calls try_to_wake_up).
		 */
		list_del_init(&wq->entry);
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 * userfaultfd_ctx_get - Acquires a reference to the पूर्णांकernal userfaultfd
 * context.
 * @ctx: [in] Poपूर्णांकer to the userfaultfd context.
 */
अटल व्योम userfaultfd_ctx_get(काष्ठा userfaultfd_ctx *ctx)
अणु
	refcount_inc(&ctx->refcount);
पूर्ण

/**
 * userfaultfd_ctx_put - Releases a reference to the पूर्णांकernal userfaultfd
 * context.
 * @ctx: [in] Poपूर्णांकer to userfaultfd context.
 *
 * The userfaultfd context reference must have been previously acquired either
 * with userfaultfd_ctx_get() or userfaultfd_ctx_fdget().
 */
अटल व्योम userfaultfd_ctx_put(काष्ठा userfaultfd_ctx *ctx)
अणु
	अगर (refcount_dec_and_test(&ctx->refcount)) अणु
		VM_BUG_ON(spin_is_locked(&ctx->fault_pending_wqh.lock));
		VM_BUG_ON(रुकोqueue_active(&ctx->fault_pending_wqh));
		VM_BUG_ON(spin_is_locked(&ctx->fault_wqh.lock));
		VM_BUG_ON(रुकोqueue_active(&ctx->fault_wqh));
		VM_BUG_ON(spin_is_locked(&ctx->event_wqh.lock));
		VM_BUG_ON(रुकोqueue_active(&ctx->event_wqh));
		VM_BUG_ON(spin_is_locked(&ctx->fd_wqh.lock));
		VM_BUG_ON(रुकोqueue_active(&ctx->fd_wqh));
		mmdrop(ctx->mm);
		kmem_cache_मुक्त(userfaultfd_ctx_cachep, ctx);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम msg_init(काष्ठा uffd_msg *msg)
अणु
	BUILD_BUG_ON(माप(काष्ठा uffd_msg) != 32);
	/*
	 * Must use स_रखो to zero out the paddings or kernel data is
	 * leaked to userland.
	 */
	स_रखो(msg, 0, माप(काष्ठा uffd_msg));
पूर्ण

अटल अंतरभूत काष्ठा uffd_msg userfault_msg(अचिन्हित दीर्घ address,
					    अचिन्हित पूर्णांक flags,
					    अचिन्हित दीर्घ reason,
					    अचिन्हित पूर्णांक features)
अणु
	काष्ठा uffd_msg msg;
	msg_init(&msg);
	msg.event = UFFD_EVENT_PAGEFAULT;
	msg.arg.pagefault.address = address;
	/*
	 * These flags indicate why the userfault occurred:
	 * - UFFD_PAGEFAULT_FLAG_WP indicates a ग_लिखो protect fault.
	 * - UFFD_PAGEFAULT_FLAG_MINOR indicates a minor fault.
	 * - Neither of these flags being set indicates a MISSING fault.
	 *
	 * Separately, UFFD_PAGEFAULT_FLAG_WRITE indicates it was a ग_लिखो
	 * fault. Otherwise, it was a पढ़ो fault.
	 */
	अगर (flags & FAULT_FLAG_WRITE)
		msg.arg.pagefault.flags |= UFFD_PAGEFAULT_FLAG_WRITE;
	अगर (reason & VM_UFFD_WP)
		msg.arg.pagefault.flags |= UFFD_PAGEFAULT_FLAG_WP;
	अगर (reason & VM_UFFD_MINOR)
		msg.arg.pagefault.flags |= UFFD_PAGEFAULT_FLAG_MINOR;
	अगर (features & UFFD_FEATURE_THREAD_ID)
		msg.arg.pagefault.feat.ptid = task_pid_vnr(current);
	वापस msg;
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
/*
 * Same functionality as userfaultfd_must_रुको below with modअगरications क्रम
 * hugepmd ranges.
 */
अटल अंतरभूत bool userfaultfd_huge_must_रुको(काष्ठा userfaultfd_ctx *ctx,
					 काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address,
					 अचिन्हित दीर्घ flags,
					 अचिन्हित दीर्घ reason)
अणु
	काष्ठा mm_काष्ठा *mm = ctx->mm;
	pte_t *ptep, pte;
	bool ret = true;

	mmap_निश्चित_locked(mm);

	ptep = huge_pte_offset(mm, address, vma_mmu_pagesize(vma));

	अगर (!ptep)
		जाओ out;

	ret = false;
	pte = huge_ptep_get(ptep);

	/*
	 * Lockless access: we're in a wait_event so it's ok अगर it
	 * changes under us.
	 */
	अगर (huge_pte_none(pte))
		ret = true;
	अगर (!huge_pte_ग_लिखो(pte) && (reason & VM_UFFD_WP))
		ret = true;
out:
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत bool userfaultfd_huge_must_रुको(काष्ठा userfaultfd_ctx *ctx,
					 काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address,
					 अचिन्हित दीर्घ flags,
					 अचिन्हित दीर्घ reason)
अणु
	वापस false;	/* should never get here */
पूर्ण
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

/*
 * Verअगरy the pagetables are still not ok after having reigstered पूर्णांकo
 * the fault_pending_wqh to aव्योम userland having to UFFDIO_WAKE any
 * userfault that has alपढ़ोy been resolved, अगर userfaultfd_पढ़ो and
 * UFFDIO_COPY|ZEROPAGE are being run simultaneously on two dअगरferent
 * thपढ़ोs.
 */
अटल अंतरभूत bool userfaultfd_must_रुको(काष्ठा userfaultfd_ctx *ctx,
					 अचिन्हित दीर्घ address,
					 अचिन्हित दीर्घ flags,
					 अचिन्हित दीर्घ reason)
अणु
	काष्ठा mm_काष्ठा *mm = ctx->mm;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd, _pmd;
	pte_t *pte;
	bool ret = true;

	mmap_निश्चित_locked(mm);

	pgd = pgd_offset(mm, address);
	अगर (!pgd_present(*pgd))
		जाओ out;
	p4d = p4d_offset(pgd, address);
	अगर (!p4d_present(*p4d))
		जाओ out;
	pud = pud_offset(p4d, address);
	अगर (!pud_present(*pud))
		जाओ out;
	pmd = pmd_offset(pud, address);
	/*
	 * READ_ONCE must function as a barrier with narrower scope
	 * and it must be equivalent to:
	 *	_pmd = *pmd; barrier();
	 *
	 * This is to deal with the instability (as in
	 * pmd_trans_unstable) of the pmd.
	 */
	_pmd = READ_ONCE(*pmd);
	अगर (pmd_none(_pmd))
		जाओ out;

	ret = false;
	अगर (!pmd_present(_pmd))
		जाओ out;

	अगर (pmd_trans_huge(_pmd)) अणु
		अगर (!pmd_ग_लिखो(_pmd) && (reason & VM_UFFD_WP))
			ret = true;
		जाओ out;
	पूर्ण

	/*
	 * the pmd is stable (as in !pmd_trans_unstable) so we can re-पढ़ो it
	 * and use the standard pte_offset_map() instead of parsing _pmd.
	 */
	pte = pte_offset_map(pmd, address);
	/*
	 * Lockless access: we're in a wait_event so it's ok अगर it
	 * changes under us.
	 */
	अगर (pte_none(*pte))
		ret = true;
	अगर (!pte_ग_लिखो(*pte) && (reason & VM_UFFD_WP))
		ret = true;
	pte_unmap(pte);

out:
	वापस ret;
पूर्ण

अटल अंतरभूत दीर्घ userfaultfd_get_blocking_state(अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & FAULT_FLAG_INTERRUPTIBLE)
		वापस TASK_INTERRUPTIBLE;

	अगर (flags & FAULT_FLAG_KILLABLE)
		वापस TASK_KILLABLE;

	वापस TASK_UNINTERRUPTIBLE;
पूर्ण

/*
 * The locking rules involved in वापसing VM_FAULT_RETRY depending on
 * FAULT_FLAG_ALLOW_RETRY, FAULT_FLAG_RETRY_NOWAIT and
 * FAULT_FLAG_KILLABLE are not straightक्रमward. The "Caution"
 * recommendation in __lock_page_or_retry is not an understatement.
 *
 * If FAULT_FLAG_ALLOW_RETRY is set, the mmap_lock must be released
 * beक्रमe वापसing VM_FAULT_RETRY only अगर FAULT_FLAG_RETRY_NOWAIT is
 * not set.
 *
 * If FAULT_FLAG_ALLOW_RETRY is set but FAULT_FLAG_KILLABLE is not
 * set, VM_FAULT_RETRY can still be वापसed अगर and only अगर there are
 * fatal_संकेत_pending()s, and the mmap_lock must be released beक्रमe
 * वापसing it.
 */
vm_fault_t handle_userfault(काष्ठा vm_fault *vmf, अचिन्हित दीर्घ reason)
अणु
	काष्ठा mm_काष्ठा *mm = vmf->vma->vm_mm;
	काष्ठा userfaultfd_ctx *ctx;
	काष्ठा userfaultfd_रुको_queue uwq;
	vm_fault_t ret = VM_FAULT_SIGBUS;
	bool must_रुको;
	दीर्घ blocking_state;

	/*
	 * We करोn't करो userfault handling क्रम the final child pid update.
	 *
	 * We also करोn't करो userfault handling during
	 * coredumping. hugetlbfs has the special
	 * follow_hugetlb_page() to skip missing pages in the
	 * FOLL_DUMP हाल, anon memory also checks क्रम FOLL_DUMP with
	 * the no_page_table() helper in follow_page_mask(), but the
	 * shmem_vm_ops->fault method is invoked even during
	 * coredumping without mmap_lock and it ends up here.
	 */
	अगर (current->flags & (PF_EXITING|PF_DUMPCORE))
		जाओ out;

	/*
	 * Coredumping runs without mmap_lock so we can only check that
	 * the mmap_lock is held, अगर PF_DUMPCORE was not set.
	 */
	mmap_निश्चित_locked(mm);

	ctx = vmf->vma->vm_userfaultfd_ctx.ctx;
	अगर (!ctx)
		जाओ out;

	BUG_ON(ctx->mm != mm);

	/* Any unrecognized flag is a bug. */
	VM_BUG_ON(reason & ~__VM_UFFD_FLAGS);
	/* 0 or > 1 flags set is a bug; we expect exactly 1. */
	VM_BUG_ON(!reason || (reason & (reason - 1)));

	अगर (ctx->features & UFFD_FEATURE_SIGBUS)
		जाओ out;
	अगर ((vmf->flags & FAULT_FLAG_USER) == 0 &&
	    ctx->flags & UFFD_USER_MODE_ONLY) अणु
		prपूर्णांकk_once(KERN_WARNING "uffd: Set unprivileged_userfaultfd "
			"sysctl knob to 1 if kernel faults must be handled "
			"without obtaining CAP_SYS_PTRACE capability\n");
		जाओ out;
	पूर्ण

	/*
	 * If it's already released don't get it. This aव्योमs to loop
	 * in __get_user_pages अगर userfaultfd_release रुकोs on the
	 * caller of handle_userfault to release the mmap_lock.
	 */
	अगर (unlikely(READ_ONCE(ctx->released))) अणु
		/*
		 * Don't वापस VM_FAULT_SIGBUS in this हाल, so a non
		 * cooperative manager can बंद the uffd after the
		 * last UFFDIO_COPY, without risking to trigger an
		 * involuntary SIGBUS अगर the process was starting the
		 * userfaultfd जबतक the userfaultfd was still armed
		 * (but after the last UFFDIO_COPY). If the uffd
		 * wasn't alपढ़ोy बंदd when the userfault reached
		 * this poपूर्णांक, that would normally be solved by
		 * userfaultfd_must_रुको वापसing 'false'.
		 *
		 * If we were to वापस VM_FAULT_SIGBUS here, the non
		 * cooperative manager would be instead क्रमced to
		 * always call UFFDIO_UNREGISTER beक्रमe it can safely
		 * बंद the uffd.
		 */
		ret = VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण

	/*
	 * Check that we can वापस VM_FAULT_RETRY.
	 *
	 * NOTE: it should become possible to वापस VM_FAULT_RETRY
	 * even अगर FAULT_FLAG_TRIED is set without leading to gup()
	 * -EBUSY failures, अगर the userfaultfd is to be extended क्रम
	 * VM_UFFD_WP tracking and we पूर्णांकend to arm the userfault
	 * without first stopping userland access to the memory. For
	 * VM_UFFD_MISSING userfaults this is enough क्रम now.
	 */
	अगर (unlikely(!(vmf->flags & FAULT_FLAG_ALLOW_RETRY))) अणु
		/*
		 * Validate the invariant that noरुको must allow retry
		 * to be sure not to वापस SIGBUS erroneously on
		 * noरुको invocations.
		 */
		BUG_ON(vmf->flags & FAULT_FLAG_RETRY_NOWAIT);
#अगर_घोषित CONFIG_DEBUG_VM
		अगर (prपूर्णांकk_ratelimit()) अणु
			prपूर्णांकk(KERN_WARNING
			       "FAULT_FLAG_ALLOW_RETRY missing %x\n",
			       vmf->flags);
			dump_stack();
		पूर्ण
#पूर्ण_अगर
		जाओ out;
	पूर्ण

	/*
	 * Handle noरुको, not much to करो other than tell it to retry
	 * and रुको.
	 */
	ret = VM_FAULT_RETRY;
	अगर (vmf->flags & FAULT_FLAG_RETRY_NOWAIT)
		जाओ out;

	/* take the reference beक्रमe dropping the mmap_lock */
	userfaultfd_ctx_get(ctx);

	init_रुकोqueue_func_entry(&uwq.wq, userfaultfd_wake_function);
	uwq.wq.निजी = current;
	uwq.msg = userfault_msg(vmf->address, vmf->flags, reason,
			ctx->features);
	uwq.ctx = ctx;
	uwq.waken = false;

	blocking_state = userfaultfd_get_blocking_state(vmf->flags);

	spin_lock_irq(&ctx->fault_pending_wqh.lock);
	/*
	 * After the __add_रुको_queue the uwq is visible to userland
	 * through poll/पढ़ो().
	 */
	__add_रुको_queue(&ctx->fault_pending_wqh, &uwq.wq);
	/*
	 * The smp_mb() after __set_current_state prevents the पढ़ोs
	 * following the spin_unlock to happen beक्रमe the list_add in
	 * __add_रुको_queue.
	 */
	set_current_state(blocking_state);
	spin_unlock_irq(&ctx->fault_pending_wqh.lock);

	अगर (!is_vm_hugetlb_page(vmf->vma))
		must_रुको = userfaultfd_must_रुको(ctx, vmf->address, vmf->flags,
						  reason);
	अन्यथा
		must_रुको = userfaultfd_huge_must_रुको(ctx, vmf->vma,
						       vmf->address,
						       vmf->flags, reason);
	mmap_पढ़ो_unlock(mm);

	अगर (likely(must_रुको && !READ_ONCE(ctx->released))) अणु
		wake_up_poll(&ctx->fd_wqh, EPOLLIN);
		schedule();
	पूर्ण

	__set_current_state(TASK_RUNNING);

	/*
	 * Here we race with the list_del; list_add in
	 * userfaultfd_ctx_पढ़ो(), however because we करोn't ever run
	 * list_del_init() to refile across the two lists, the prev
	 * and next poपूर्णांकers will never poपूर्णांक to self. list_add also
	 * would never let any of the two poपूर्णांकers to poपूर्णांक to
	 * self. So list_empty_careful won't risk to see both poपूर्णांकers
	 * poपूर्णांकing to self at any समय during the list refile. The
	 * only हाल where list_del_init() is called is the full
	 * removal in the wake function and there we करोn't re-list_add
	 * and it's fine not to block on the spinlock. The uwq on this
	 * kernel stack can be released after the list_del_init.
	 */
	अगर (!list_empty_careful(&uwq.wq.entry)) अणु
		spin_lock_irq(&ctx->fault_pending_wqh.lock);
		/*
		 * No need of list_del_init(), the uwq on the stack
		 * will be मुक्तd लघुly anyway.
		 */
		list_del(&uwq.wq.entry);
		spin_unlock_irq(&ctx->fault_pending_wqh.lock);
	पूर्ण

	/*
	 * ctx may go away after this अगर the userfault pseuकरो fd is
	 * alपढ़ोy released.
	 */
	userfaultfd_ctx_put(ctx);

out:
	वापस ret;
पूर्ण

अटल व्योम userfaultfd_event_रुको_completion(काष्ठा userfaultfd_ctx *ctx,
					      काष्ठा userfaultfd_रुको_queue *ewq)
अणु
	काष्ठा userfaultfd_ctx *release_new_ctx;

	अगर (WARN_ON_ONCE(current->flags & PF_EXITING))
		जाओ out;

	ewq->ctx = ctx;
	init_रुकोqueue_entry(&ewq->wq, current);
	release_new_ctx = शून्य;

	spin_lock_irq(&ctx->event_wqh.lock);
	/*
	 * After the __add_रुको_queue the uwq is visible to userland
	 * through poll/पढ़ो().
	 */
	__add_रुको_queue(&ctx->event_wqh, &ewq->wq);
	क्रम (;;) अणु
		set_current_state(TASK_KILLABLE);
		अगर (ewq->msg.event == 0)
			अवरोध;
		अगर (READ_ONCE(ctx->released) ||
		    fatal_संकेत_pending(current)) अणु
			/*
			 * &ewq->wq may be queued in विभाजन_event, but
			 * __हटाओ_रुको_queue ignores the head
			 * parameter. It would be a problem अगर it
			 * didn't.
			 */
			__हटाओ_रुको_queue(&ctx->event_wqh, &ewq->wq);
			अगर (ewq->msg.event == UFFD_EVENT_FORK) अणु
				काष्ठा userfaultfd_ctx *new;

				new = (काष्ठा userfaultfd_ctx *)
					(अचिन्हित दीर्घ)
					ewq->msg.arg.reserved.reserved1;
				release_new_ctx = new;
			पूर्ण
			अवरोध;
		पूर्ण

		spin_unlock_irq(&ctx->event_wqh.lock);

		wake_up_poll(&ctx->fd_wqh, EPOLLIN);
		schedule();

		spin_lock_irq(&ctx->event_wqh.lock);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	spin_unlock_irq(&ctx->event_wqh.lock);

	अगर (release_new_ctx) अणु
		काष्ठा vm_area_काष्ठा *vma;
		काष्ठा mm_काष्ठा *mm = release_new_ctx->mm;

		/* the various vma->vm_userfaultfd_ctx still poपूर्णांकs to it */
		mmap_ग_लिखो_lock(mm);
		क्रम (vma = mm->mmap; vma; vma = vma->vm_next)
			अगर (vma->vm_userfaultfd_ctx.ctx == release_new_ctx) अणु
				vma->vm_userfaultfd_ctx = शून्य_VM_UFFD_CTX;
				vma->vm_flags &= ~__VM_UFFD_FLAGS;
			पूर्ण
		mmap_ग_लिखो_unlock(mm);

		userfaultfd_ctx_put(release_new_ctx);
	पूर्ण

	/*
	 * ctx may go away after this अगर the userfault pseuकरो fd is
	 * alपढ़ोy released.
	 */
out:
	WRITE_ONCE(ctx->mmap_changing, false);
	userfaultfd_ctx_put(ctx);
पूर्ण

अटल व्योम userfaultfd_event_complete(काष्ठा userfaultfd_ctx *ctx,
				       काष्ठा userfaultfd_रुको_queue *ewq)
अणु
	ewq->msg.event = 0;
	wake_up_locked(&ctx->event_wqh);
	__हटाओ_रुको_queue(&ctx->event_wqh, &ewq->wq);
पूर्ण

पूर्णांक dup_userfaultfd(काष्ठा vm_area_काष्ठा *vma, काष्ठा list_head *fcs)
अणु
	काष्ठा userfaultfd_ctx *ctx = शून्य, *octx;
	काष्ठा userfaultfd_विभाजन_ctx *fctx;

	octx = vma->vm_userfaultfd_ctx.ctx;
	अगर (!octx || !(octx->features & UFFD_FEATURE_EVENT_FORK)) अणु
		vma->vm_userfaultfd_ctx = शून्य_VM_UFFD_CTX;
		vma->vm_flags &= ~__VM_UFFD_FLAGS;
		वापस 0;
	पूर्ण

	list_क्रम_each_entry(fctx, fcs, list)
		अगर (fctx->orig == octx) अणु
			ctx = fctx->new;
			अवरोध;
		पूर्ण

	अगर (!ctx) अणु
		fctx = kदो_स्मृति(माप(*fctx), GFP_KERNEL);
		अगर (!fctx)
			वापस -ENOMEM;

		ctx = kmem_cache_alloc(userfaultfd_ctx_cachep, GFP_KERNEL);
		अगर (!ctx) अणु
			kमुक्त(fctx);
			वापस -ENOMEM;
		पूर्ण

		refcount_set(&ctx->refcount, 1);
		ctx->flags = octx->flags;
		ctx->state = UFFD_STATE_RUNNING;
		ctx->features = octx->features;
		ctx->released = false;
		ctx->mmap_changing = false;
		ctx->mm = vma->vm_mm;
		mmgrab(ctx->mm);

		userfaultfd_ctx_get(octx);
		WRITE_ONCE(octx->mmap_changing, true);
		fctx->orig = octx;
		fctx->new = ctx;
		list_add_tail(&fctx->list, fcs);
	पूर्ण

	vma->vm_userfaultfd_ctx.ctx = ctx;
	वापस 0;
पूर्ण

अटल व्योम dup_fctx(काष्ठा userfaultfd_विभाजन_ctx *fctx)
अणु
	काष्ठा userfaultfd_ctx *ctx = fctx->orig;
	काष्ठा userfaultfd_रुको_queue ewq;

	msg_init(&ewq.msg);

	ewq.msg.event = UFFD_EVENT_FORK;
	ewq.msg.arg.reserved.reserved1 = (अचिन्हित दीर्घ)fctx->new;

	userfaultfd_event_रुको_completion(ctx, &ewq);
पूर्ण

व्योम dup_userfaultfd_complete(काष्ठा list_head *fcs)
अणु
	काष्ठा userfaultfd_विभाजन_ctx *fctx, *n;

	list_क्रम_each_entry_safe(fctx, n, fcs, list) अणु
		dup_fctx(fctx);
		list_del(&fctx->list);
		kमुक्त(fctx);
	पूर्ण
पूर्ण

व्योम mremap_userfaultfd_prep(काष्ठा vm_area_काष्ठा *vma,
			     काष्ठा vm_userfaultfd_ctx *vm_ctx)
अणु
	काष्ठा userfaultfd_ctx *ctx;

	ctx = vma->vm_userfaultfd_ctx.ctx;

	अगर (!ctx)
		वापस;

	अगर (ctx->features & UFFD_FEATURE_EVENT_REMAP) अणु
		vm_ctx->ctx = ctx;
		userfaultfd_ctx_get(ctx);
		WRITE_ONCE(ctx->mmap_changing, true);
	पूर्ण अन्यथा अणु
		/* Drop uffd context अगर remap feature not enabled */
		vma->vm_userfaultfd_ctx = शून्य_VM_UFFD_CTX;
		vma->vm_flags &= ~__VM_UFFD_FLAGS;
	पूर्ण
पूर्ण

व्योम mremap_userfaultfd_complete(काष्ठा vm_userfaultfd_ctx *vm_ctx,
				 अचिन्हित दीर्घ from, अचिन्हित दीर्घ to,
				 अचिन्हित दीर्घ len)
अणु
	काष्ठा userfaultfd_ctx *ctx = vm_ctx->ctx;
	काष्ठा userfaultfd_रुको_queue ewq;

	अगर (!ctx)
		वापस;

	अगर (to & ~PAGE_MASK) अणु
		userfaultfd_ctx_put(ctx);
		वापस;
	पूर्ण

	msg_init(&ewq.msg);

	ewq.msg.event = UFFD_EVENT_REMAP;
	ewq.msg.arg.remap.from = from;
	ewq.msg.arg.remap.to = to;
	ewq.msg.arg.remap.len = len;

	userfaultfd_event_रुको_completion(ctx, &ewq);
पूर्ण

bool userfaultfd_हटाओ(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा userfaultfd_ctx *ctx;
	काष्ठा userfaultfd_रुको_queue ewq;

	ctx = vma->vm_userfaultfd_ctx.ctx;
	अगर (!ctx || !(ctx->features & UFFD_FEATURE_EVENT_REMOVE))
		वापस true;

	userfaultfd_ctx_get(ctx);
	WRITE_ONCE(ctx->mmap_changing, true);
	mmap_पढ़ो_unlock(mm);

	msg_init(&ewq.msg);

	ewq.msg.event = UFFD_EVENT_REMOVE;
	ewq.msg.arg.हटाओ.start = start;
	ewq.msg.arg.हटाओ.end = end;

	userfaultfd_event_रुको_completion(ctx, &ewq);

	वापस false;
पूर्ण

अटल bool has_unmap_ctx(काष्ठा userfaultfd_ctx *ctx, काष्ठा list_head *unmaps,
			  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा userfaultfd_unmap_ctx *unmap_ctx;

	list_क्रम_each_entry(unmap_ctx, unmaps, list)
		अगर (unmap_ctx->ctx == ctx && unmap_ctx->start == start &&
		    unmap_ctx->end == end)
			वापस true;

	वापस false;
पूर्ण

पूर्णांक userfaultfd_unmap_prep(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			   काष्ठा list_head *unmaps)
अणु
	क्रम ( ; vma && vma->vm_start < end; vma = vma->vm_next) अणु
		काष्ठा userfaultfd_unmap_ctx *unmap_ctx;
		काष्ठा userfaultfd_ctx *ctx = vma->vm_userfaultfd_ctx.ctx;

		अगर (!ctx || !(ctx->features & UFFD_FEATURE_EVENT_UNMAP) ||
		    has_unmap_ctx(ctx, unmaps, start, end))
			जारी;

		unmap_ctx = kzalloc(माप(*unmap_ctx), GFP_KERNEL);
		अगर (!unmap_ctx)
			वापस -ENOMEM;

		userfaultfd_ctx_get(ctx);
		WRITE_ONCE(ctx->mmap_changing, true);
		unmap_ctx->ctx = ctx;
		unmap_ctx->start = start;
		unmap_ctx->end = end;
		list_add_tail(&unmap_ctx->list, unmaps);
	पूर्ण

	वापस 0;
पूर्ण

व्योम userfaultfd_unmap_complete(काष्ठा mm_काष्ठा *mm, काष्ठा list_head *uf)
अणु
	काष्ठा userfaultfd_unmap_ctx *ctx, *n;
	काष्ठा userfaultfd_रुको_queue ewq;

	list_क्रम_each_entry_safe(ctx, n, uf, list) अणु
		msg_init(&ewq.msg);

		ewq.msg.event = UFFD_EVENT_UNMAP;
		ewq.msg.arg.हटाओ.start = ctx->start;
		ewq.msg.arg.हटाओ.end = ctx->end;

		userfaultfd_event_रुको_completion(ctx->ctx, &ewq);

		list_del(&ctx->list);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

अटल पूर्णांक userfaultfd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा userfaultfd_ctx *ctx = file->निजी_data;
	काष्ठा mm_काष्ठा *mm = ctx->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	/* len == 0 means wake all */
	काष्ठा userfaultfd_wake_range range = अणु .len = 0, पूर्ण;
	अचिन्हित दीर्घ new_flags;

	WRITE_ONCE(ctx->released, true);

	अगर (!mmget_not_zero(mm))
		जाओ wakeup;

	/*
	 * Flush page faults out of all CPUs. NOTE: all page faults
	 * must be retried without वापसing VM_FAULT_SIGBUS अगर
	 * userfaultfd_ctx_get() succeeds but vma->vma_userfault_ctx
	 * changes जबतक handle_userfault released the mmap_lock. So
	 * it's critical that released is set to true (above), beक्रमe
	 * taking the mmap_lock क्रम writing.
	 */
	mmap_ग_लिखो_lock(mm);
	prev = शून्य;
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		cond_resched();
		BUG_ON(!!vma->vm_userfaultfd_ctx.ctx ^
		       !!(vma->vm_flags & __VM_UFFD_FLAGS));
		अगर (vma->vm_userfaultfd_ctx.ctx != ctx) अणु
			prev = vma;
			जारी;
		पूर्ण
		new_flags = vma->vm_flags & ~__VM_UFFD_FLAGS;
		prev = vma_merge(mm, prev, vma->vm_start, vma->vm_end,
				 new_flags, vma->anon_vma,
				 vma->vm_file, vma->vm_pgoff,
				 vma_policy(vma),
				 शून्य_VM_UFFD_CTX);
		अगर (prev)
			vma = prev;
		अन्यथा
			prev = vma;
		vma->vm_flags = new_flags;
		vma->vm_userfaultfd_ctx = शून्य_VM_UFFD_CTX;
	पूर्ण
	mmap_ग_लिखो_unlock(mm);
	mmput(mm);
wakeup:
	/*
	 * After no new page faults can रुको on this fault_*wqh, flush
	 * the last page faults that may have been alपढ़ोy रुकोing on
	 * the fault_*wqh.
	 */
	spin_lock_irq(&ctx->fault_pending_wqh.lock);
	__wake_up_locked_key(&ctx->fault_pending_wqh, TASK_NORMAL, &range);
	__wake_up(&ctx->fault_wqh, TASK_NORMAL, 1, &range);
	spin_unlock_irq(&ctx->fault_pending_wqh.lock);

	/* Flush pending events that may still रुको on event_wqh */
	wake_up_all(&ctx->event_wqh);

	wake_up_poll(&ctx->fd_wqh, EPOLLHUP);
	userfaultfd_ctx_put(ctx);
	वापस 0;
पूर्ण

/* fault_pending_wqh.lock must be hold by the caller */
अटल अंतरभूत काष्ठा userfaultfd_रुको_queue *find_userfault_in(
		रुको_queue_head_t *wqh)
अणु
	रुको_queue_entry_t *wq;
	काष्ठा userfaultfd_रुको_queue *uwq;

	lockdep_निश्चित_held(&wqh->lock);

	uwq = शून्य;
	अगर (!रुकोqueue_active(wqh))
		जाओ out;
	/* walk in reverse to provide FIFO behavior to पढ़ो userfaults */
	wq = list_last_entry(&wqh->head, typeof(*wq), entry);
	uwq = container_of(wq, काष्ठा userfaultfd_रुको_queue, wq);
out:
	वापस uwq;
पूर्ण

अटल अंतरभूत काष्ठा userfaultfd_रुको_queue *find_userfault(
		काष्ठा userfaultfd_ctx *ctx)
अणु
	वापस find_userfault_in(&ctx->fault_pending_wqh);
पूर्ण

अटल अंतरभूत काष्ठा userfaultfd_रुको_queue *find_userfault_evt(
		काष्ठा userfaultfd_ctx *ctx)
अणु
	वापस find_userfault_in(&ctx->event_wqh);
पूर्ण

अटल __poll_t userfaultfd_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा userfaultfd_ctx *ctx = file->निजी_data;
	__poll_t ret;

	poll_रुको(file, &ctx->fd_wqh, रुको);

	चयन (ctx->state) अणु
	हाल UFFD_STATE_WAIT_API:
		वापस EPOLLERR;
	हाल UFFD_STATE_RUNNING:
		/*
		 * poll() never guarantees that पढ़ो won't block.
		 * userfaults can be waken beक्रमe they're पढ़ो().
		 */
		अगर (unlikely(!(file->f_flags & O_NONBLOCK)))
			वापस EPOLLERR;
		/*
		 * lockless access to see अगर there are pending faults
		 * __pollरुको last action is the add_रुको_queue but
		 * the spin_unlock would allow the रुकोqueue_active to
		 * pass above the actual list_add inside
		 * add_रुको_queue critical section. So use a full
		 * memory barrier to serialize the list_add ग_लिखो of
		 * add_रुको_queue() with the रुकोqueue_active पढ़ो
		 * below.
		 */
		ret = 0;
		smp_mb();
		अगर (रुकोqueue_active(&ctx->fault_pending_wqh))
			ret = EPOLLIN;
		अन्यथा अगर (रुकोqueue_active(&ctx->event_wqh))
			ret = EPOLLIN;

		वापस ret;
	शेष:
		WARN_ON_ONCE(1);
		वापस EPOLLERR;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations userfaultfd_fops;

अटल पूर्णांक resolve_userfault_विभाजन(काष्ठा userfaultfd_ctx *new,
				  काष्ठा inode *inode,
				  काष्ठा uffd_msg *msg)
अणु
	पूर्णांक fd;

	fd = anon_inode_getfd_secure("[userfaultfd]", &userfaultfd_fops, new,
			O_RDWR | (new->flags & UFFD_SHARED_FCNTL_FLAGS), inode);
	अगर (fd < 0)
		वापस fd;

	msg->arg.reserved.reserved1 = 0;
	msg->arg.विभाजन.ufd = fd;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार userfaultfd_ctx_पढ़ो(काष्ठा userfaultfd_ctx *ctx, पूर्णांक no_रुको,
				    काष्ठा uffd_msg *msg, काष्ठा inode *inode)
अणु
	sमाप_प्रकार ret;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा userfaultfd_रुको_queue *uwq;
	/*
	 * Handling विभाजन event requires sleeping operations, so
	 * we drop the event_wqh lock, then करो these ops, then
	 * lock it back and wake up the रुकोer. While the lock is
	 * dropped the ewq may go away so we keep track of it
	 * carefully.
	 */
	LIST_HEAD(विभाजन_event);
	काष्ठा userfaultfd_ctx *विभाजन_nctx = शून्य;

	/* always take the fd_wqh lock beक्रमe the fault_pending_wqh lock */
	spin_lock_irq(&ctx->fd_wqh.lock);
	__add_रुको_queue(&ctx->fd_wqh, &रुको);
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock(&ctx->fault_pending_wqh.lock);
		uwq = find_userfault(ctx);
		अगर (uwq) अणु
			/*
			 * Use a seqcount to repeat the lockless check
			 * in wake_userfault() to aव्योम missing
			 * wakeups because during the refile both
			 * रुकोqueue could become empty अगर this is the
			 * only userfault.
			 */
			ग_लिखो_seqcount_begin(&ctx->refile_seq);

			/*
			 * The fault_pending_wqh.lock prevents the uwq
			 * to disappear from under us.
			 *
			 * Refile this userfault from
			 * fault_pending_wqh to fault_wqh, it's not
			 * pending anymore after we पढ़ो it.
			 *
			 * Use list_del() by hand (as
			 * userfaultfd_wake_function also uses
			 * list_del_init() by hand) to be sure nobody
			 * changes __हटाओ_रुको_queue() to use
			 * list_del_init() in turn अवरोधing the
			 * !list_empty_careful() check in
			 * handle_userfault(). The uwq->wq.head list
			 * must never be empty at any समय during the
			 * refile, or the रुकोqueue could disappear
			 * from under us. The "wait_queue_head_t"
			 * parameter of __हटाओ_रुको_queue() is unused
			 * anyway.
			 */
			list_del(&uwq->wq.entry);
			add_रुको_queue(&ctx->fault_wqh, &uwq->wq);

			ग_लिखो_seqcount_end(&ctx->refile_seq);

			/* careful to always initialize msg अगर ret == 0 */
			*msg = uwq->msg;
			spin_unlock(&ctx->fault_pending_wqh.lock);
			ret = 0;
			अवरोध;
		पूर्ण
		spin_unlock(&ctx->fault_pending_wqh.lock);

		spin_lock(&ctx->event_wqh.lock);
		uwq = find_userfault_evt(ctx);
		अगर (uwq) अणु
			*msg = uwq->msg;

			अगर (uwq->msg.event == UFFD_EVENT_FORK) अणु
				विभाजन_nctx = (काष्ठा userfaultfd_ctx *)
					(अचिन्हित दीर्घ)
					uwq->msg.arg.reserved.reserved1;
				list_move(&uwq->wq.entry, &विभाजन_event);
				/*
				 * विभाजन_nctx can be मुक्तd as soon as
				 * we drop the lock, unless we take a
				 * reference on it.
				 */
				userfaultfd_ctx_get(विभाजन_nctx);
				spin_unlock(&ctx->event_wqh.lock);
				ret = 0;
				अवरोध;
			पूर्ण

			userfaultfd_event_complete(ctx, uwq);
			spin_unlock(&ctx->event_wqh.lock);
			ret = 0;
			अवरोध;
		पूर्ण
		spin_unlock(&ctx->event_wqh.lock);

		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (no_रुको) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		spin_unlock_irq(&ctx->fd_wqh.lock);
		schedule();
		spin_lock_irq(&ctx->fd_wqh.lock);
	पूर्ण
	__हटाओ_रुको_queue(&ctx->fd_wqh, &रुको);
	__set_current_state(TASK_RUNNING);
	spin_unlock_irq(&ctx->fd_wqh.lock);

	अगर (!ret && msg->event == UFFD_EVENT_FORK) अणु
		ret = resolve_userfault_विभाजन(विभाजन_nctx, inode, msg);
		spin_lock_irq(&ctx->event_wqh.lock);
		अगर (!list_empty(&विभाजन_event)) अणु
			/*
			 * The विभाजन thपढ़ो didn't पात, so we can
			 * drop the temporary refcount.
			 */
			userfaultfd_ctx_put(विभाजन_nctx);

			uwq = list_first_entry(&विभाजन_event,
					       typeof(*uwq),
					       wq.entry);
			/*
			 * If विभाजन_event list wasn't empty and in turn
			 * the event wasn't alपढ़ोy released by विभाजन
			 * (the event is allocated on विभाजन kernel
			 * stack), put the event back to its place in
			 * the event_wq. विभाजन_event head will be मुक्तd
			 * as soon as we वापस so the event cannot
			 * stay queued there no matter the current
			 * "ret" value.
			 */
			list_del(&uwq->wq.entry);
			__add_रुको_queue(&ctx->event_wqh, &uwq->wq);

			/*
			 * Leave the event in the रुकोqueue and report
			 * error to userland अगर we failed to resolve
			 * the userfault विभाजन.
			 */
			अगर (likely(!ret))
				userfaultfd_event_complete(ctx, uwq);
		पूर्ण अन्यथा अणु
			/*
			 * Here the विभाजन thपढ़ो पातed and the
			 * refcount from the विभाजन thपढ़ो on विभाजन_nctx
			 * has alपढ़ोy been released. We still hold
			 * the reference we took beक्रमe releasing the
			 * lock above. If resolve_userfault_विभाजन
			 * failed we've to drop it because the
			 * विभाजन_nctx has to be मुक्तd in such हाल. If
			 * it succeeded we'll hold it because the new
			 * uffd references it.
			 */
			अगर (ret)
				userfaultfd_ctx_put(विभाजन_nctx);
		पूर्ण
		spin_unlock_irq(&ctx->event_wqh.lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार userfaultfd_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा userfaultfd_ctx *ctx = file->निजी_data;
	sमाप_प्रकार _ret, ret = 0;
	काष्ठा uffd_msg msg;
	पूर्णांक no_रुको = file->f_flags & O_NONBLOCK;
	काष्ठा inode *inode = file_inode(file);

	अगर (ctx->state == UFFD_STATE_WAIT_API)
		वापस -EINVAL;

	क्रम (;;) अणु
		अगर (count < माप(msg))
			वापस ret ? ret : -EINVAL;
		_ret = userfaultfd_ctx_पढ़ो(ctx, no_रुको, &msg, inode);
		अगर (_ret < 0)
			वापस ret ? ret : _ret;
		अगर (copy_to_user((__u64 __user *) buf, &msg, माप(msg)))
			वापस ret ? ret : -EFAULT;
		ret += माप(msg);
		buf += माप(msg);
		count -= माप(msg);
		/*
		 * Allow to पढ़ो more than one fault at समय but only
		 * block अगर रुकोing क्रम the very first one.
		 */
		no_रुको = O_NONBLOCK;
	पूर्ण
पूर्ण

अटल व्योम __wake_userfault(काष्ठा userfaultfd_ctx *ctx,
			     काष्ठा userfaultfd_wake_range *range)
अणु
	spin_lock_irq(&ctx->fault_pending_wqh.lock);
	/* wake all in the range and स्वतःहटाओ */
	अगर (रुकोqueue_active(&ctx->fault_pending_wqh))
		__wake_up_locked_key(&ctx->fault_pending_wqh, TASK_NORMAL,
				     range);
	अगर (रुकोqueue_active(&ctx->fault_wqh))
		__wake_up(&ctx->fault_wqh, TASK_NORMAL, 1, range);
	spin_unlock_irq(&ctx->fault_pending_wqh.lock);
पूर्ण

अटल __always_अंतरभूत व्योम wake_userfault(काष्ठा userfaultfd_ctx *ctx,
					   काष्ठा userfaultfd_wake_range *range)
अणु
	अचिन्हित seq;
	bool need_wakeup;

	/*
	 * To be sure रुकोqueue_active() is not reordered by the CPU
	 * beक्रमe the pagetable update, use an explicit SMP memory
	 * barrier here. PT lock release or mmap_पढ़ो_unlock(mm) still
	 * have release semantics that can allow the
	 * रुकोqueue_active() to be reordered beक्रमe the pte update.
	 */
	smp_mb();

	/*
	 * Use रुकोqueue_active because it's very frequent to
	 * change the address space atomically even अगर there are no
	 * userfaults yet. So we take the spinlock only when we're
	 * sure we've userfaults to wake.
	 */
	करो अणु
		seq = पढ़ो_seqcount_begin(&ctx->refile_seq);
		need_wakeup = रुकोqueue_active(&ctx->fault_pending_wqh) ||
			रुकोqueue_active(&ctx->fault_wqh);
		cond_resched();
	पूर्ण जबतक (पढ़ो_seqcount_retry(&ctx->refile_seq, seq));
	अगर (need_wakeup)
		__wake_userfault(ctx, range);
पूर्ण

अटल __always_अंतरभूत पूर्णांक validate_range(काष्ठा mm_काष्ठा *mm,
					  __u64 *start, __u64 len)
अणु
	__u64 task_size = mm->task_size;

	*start = untagged_addr(*start);

	अगर (*start & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (len & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (!len)
		वापस -EINVAL;
	अगर (*start < mmap_min_addr)
		वापस -EINVAL;
	अगर (*start >= task_size)
		वापस -EINVAL;
	अगर (len > task_size - *start)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत bool vma_can_userfault(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ vm_flags)
अणु
	/* FIXME: add WP support to hugetlbfs and shmem */
	अगर (vm_flags & VM_UFFD_WP) अणु
		अगर (is_vm_hugetlb_page(vma) || vma_is_shmem(vma))
			वापस false;
	पूर्ण

	अगर (vm_flags & VM_UFFD_MINOR) अणु
		/* FIXME: Add minor fault पूर्णांकerception क्रम shmem. */
		अगर (!is_vm_hugetlb_page(vma))
			वापस false;
	पूर्ण

	वापस vma_is_anonymous(vma) || is_vm_hugetlb_page(vma) ||
	       vma_is_shmem(vma);
पूर्ण

अटल पूर्णांक userfaultfd_रेजिस्टर(काष्ठा userfaultfd_ctx *ctx,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा mm_काष्ठा *mm = ctx->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev, *cur;
	पूर्णांक ret;
	काष्ठा uffdio_रेजिस्टर uffdio_रेजिस्टर;
	काष्ठा uffdio_रेजिस्टर __user *user_uffdio_रेजिस्टर;
	अचिन्हित दीर्घ vm_flags, new_flags;
	bool found;
	bool basic_ioctls;
	अचिन्हित दीर्घ start, end, vma_end;

	user_uffdio_रेजिस्टर = (काष्ठा uffdio_रेजिस्टर __user *) arg;

	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_रेजिस्टर, user_uffdio_रेजिस्टर,
			   माप(uffdio_रेजिस्टर)-माप(__u64)))
		जाओ out;

	ret = -EINVAL;
	अगर (!uffdio_रेजिस्टर.mode)
		जाओ out;
	अगर (uffdio_रेजिस्टर.mode & ~UFFD_API_REGISTER_MODES)
		जाओ out;
	vm_flags = 0;
	अगर (uffdio_रेजिस्टर.mode & UFFDIO_REGISTER_MODE_MISSING)
		vm_flags |= VM_UFFD_MISSING;
	अगर (uffdio_रेजिस्टर.mode & UFFDIO_REGISTER_MODE_WP)
		vm_flags |= VM_UFFD_WP;
	अगर (uffdio_रेजिस्टर.mode & UFFDIO_REGISTER_MODE_MINOR) अणु
#अगर_अघोषित CONFIG_HAVE_ARCH_USERFAULTFD_MINOR
		जाओ out;
#पूर्ण_अगर
		vm_flags |= VM_UFFD_MINOR;
	पूर्ण

	ret = validate_range(mm, &uffdio_रेजिस्टर.range.start,
			     uffdio_रेजिस्टर.range.len);
	अगर (ret)
		जाओ out;

	start = uffdio_रेजिस्टर.range.start;
	end = start + uffdio_रेजिस्टर.range.len;

	ret = -ENOMEM;
	अगर (!mmget_not_zero(mm))
		जाओ out;

	mmap_ग_लिखो_lock(mm);
	vma = find_vma_prev(mm, start, &prev);
	अगर (!vma)
		जाओ out_unlock;

	/* check that there's at least one vma in the range */
	ret = -EINVAL;
	अगर (vma->vm_start >= end)
		जाओ out_unlock;

	/*
	 * If the first vma contains huge pages, make sure start address
	 * is aligned to huge page size.
	 */
	अगर (is_vm_hugetlb_page(vma)) अणु
		अचिन्हित दीर्घ vma_hpagesize = vma_kernel_pagesize(vma);

		अगर (start & (vma_hpagesize - 1))
			जाओ out_unlock;
	पूर्ण

	/*
	 * Search क्रम not compatible vmas.
	 */
	found = false;
	basic_ioctls = false;
	क्रम (cur = vma; cur && cur->vm_start < end; cur = cur->vm_next) अणु
		cond_resched();

		BUG_ON(!!cur->vm_userfaultfd_ctx.ctx ^
		       !!(cur->vm_flags & __VM_UFFD_FLAGS));

		/* check not compatible vmas */
		ret = -EINVAL;
		अगर (!vma_can_userfault(cur, vm_flags))
			जाओ out_unlock;

		/*
		 * UFFDIO_COPY will fill file holes even without
		 * PROT_WRITE. This check enक्रमces that अगर this is a
		 * MAP_SHARED, the process has ग_लिखो permission to the backing
		 * file. If VM_MAYWRITE is set it also enक्रमces that on a
		 * MAP_SHARED vma: there is no F_WRITE_SEAL and no further
		 * F_WRITE_SEAL can be taken until the vma is destroyed.
		 */
		ret = -EPERM;
		अगर (unlikely(!(cur->vm_flags & VM_MAYWRITE)))
			जाओ out_unlock;

		/*
		 * If this vma contains ending address, and huge pages
		 * check alignment.
		 */
		अगर (is_vm_hugetlb_page(cur) && end <= cur->vm_end &&
		    end > cur->vm_start) अणु
			अचिन्हित दीर्घ vma_hpagesize = vma_kernel_pagesize(cur);

			ret = -EINVAL;

			अगर (end & (vma_hpagesize - 1))
				जाओ out_unlock;
		पूर्ण
		अगर ((vm_flags & VM_UFFD_WP) && !(cur->vm_flags & VM_MAYWRITE))
			जाओ out_unlock;

		/*
		 * Check that this vma isn't alपढ़ोy owned by a
		 * dअगरferent userfaultfd. We can't allow more than one
		 * userfaultfd to own a single vma simultaneously or we
		 * wouldn't know which one to deliver the userfaults to.
		 */
		ret = -EBUSY;
		अगर (cur->vm_userfaultfd_ctx.ctx &&
		    cur->vm_userfaultfd_ctx.ctx != ctx)
			जाओ out_unlock;

		/*
		 * Note vmas containing huge pages
		 */
		अगर (is_vm_hugetlb_page(cur))
			basic_ioctls = true;

		found = true;
	पूर्ण
	BUG_ON(!found);

	अगर (vma->vm_start < start)
		prev = vma;

	ret = 0;
	करो अणु
		cond_resched();

		BUG_ON(!vma_can_userfault(vma, vm_flags));
		BUG_ON(vma->vm_userfaultfd_ctx.ctx &&
		       vma->vm_userfaultfd_ctx.ctx != ctx);
		WARN_ON(!(vma->vm_flags & VM_MAYWRITE));

		/*
		 * Nothing to करो: this vma is alपढ़ोy रेजिस्टरed पूर्णांकo this
		 * userfaultfd and with the right tracking mode too.
		 */
		अगर (vma->vm_userfaultfd_ctx.ctx == ctx &&
		    (vma->vm_flags & vm_flags) == vm_flags)
			जाओ skip;

		अगर (vma->vm_start > start)
			start = vma->vm_start;
		vma_end = min(end, vma->vm_end);

		new_flags = (vma->vm_flags & ~__VM_UFFD_FLAGS) | vm_flags;
		prev = vma_merge(mm, prev, start, vma_end, new_flags,
				 vma->anon_vma, vma->vm_file, vma->vm_pgoff,
				 vma_policy(vma),
				 ((काष्ठा vm_userfaultfd_ctx)अणु ctx पूर्ण));
		अगर (prev) अणु
			vma = prev;
			जाओ next;
		पूर्ण
		अगर (vma->vm_start < start) अणु
			ret = split_vma(mm, vma, start, 1);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (vma->vm_end > end) अणु
			ret = split_vma(mm, vma, end, 0);
			अगर (ret)
				अवरोध;
		पूर्ण
	next:
		/*
		 * In the vma_merge() successful mprotect-like हाल 8:
		 * the next vma was merged पूर्णांकo the current one and
		 * the current one has not been updated yet.
		 */
		vma->vm_flags = new_flags;
		vma->vm_userfaultfd_ctx.ctx = ctx;

		अगर (is_vm_hugetlb_page(vma) && uffd_disable_huge_pmd_share(vma))
			hugetlb_unshare_all_pmds(vma);

	skip:
		prev = vma;
		start = vma->vm_end;
		vma = vma->vm_next;
	पूर्ण जबतक (vma && vma->vm_start < end);
out_unlock:
	mmap_ग_लिखो_unlock(mm);
	mmput(mm);
	अगर (!ret) अणु
		__u64 ioctls_out;

		ioctls_out = basic_ioctls ? UFFD_API_RANGE_IOCTLS_BASIC :
		    UFFD_API_RANGE_IOCTLS;

		/*
		 * Declare the WP ioctl only अगर the WP mode is
		 * specअगरied and all checks passed with the range
		 */
		अगर (!(uffdio_रेजिस्टर.mode & UFFDIO_REGISTER_MODE_WP))
			ioctls_out &= ~((__u64)1 << _UFFDIO_WRITEPROTECT);

		/* CONTINUE ioctl is only supported क्रम MINOR ranges. */
		अगर (!(uffdio_रेजिस्टर.mode & UFFDIO_REGISTER_MODE_MINOR))
			ioctls_out &= ~((__u64)1 << _UFFDIO_CONTINUE);

		/*
		 * Now that we scanned all vmas we can alपढ़ोy tell
		 * userland which ioctls methods are guaranteed to
		 * succeed on this range.
		 */
		अगर (put_user(ioctls_out, &user_uffdio_रेजिस्टर->ioctls))
			ret = -EFAULT;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक userfaultfd_unरेजिस्टर(काष्ठा userfaultfd_ctx *ctx,
				  अचिन्हित दीर्घ arg)
अणु
	काष्ठा mm_काष्ठा *mm = ctx->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev, *cur;
	पूर्णांक ret;
	काष्ठा uffdio_range uffdio_unरेजिस्टर;
	अचिन्हित दीर्घ new_flags;
	bool found;
	अचिन्हित दीर्घ start, end, vma_end;
	स्थिर व्योम __user *buf = (व्योम __user *)arg;

	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_unरेजिस्टर, buf, माप(uffdio_unरेजिस्टर)))
		जाओ out;

	ret = validate_range(mm, &uffdio_unरेजिस्टर.start,
			     uffdio_unरेजिस्टर.len);
	अगर (ret)
		जाओ out;

	start = uffdio_unरेजिस्टर.start;
	end = start + uffdio_unरेजिस्टर.len;

	ret = -ENOMEM;
	अगर (!mmget_not_zero(mm))
		जाओ out;

	mmap_ग_लिखो_lock(mm);
	vma = find_vma_prev(mm, start, &prev);
	अगर (!vma)
		जाओ out_unlock;

	/* check that there's at least one vma in the range */
	ret = -EINVAL;
	अगर (vma->vm_start >= end)
		जाओ out_unlock;

	/*
	 * If the first vma contains huge pages, make sure start address
	 * is aligned to huge page size.
	 */
	अगर (is_vm_hugetlb_page(vma)) अणु
		अचिन्हित दीर्घ vma_hpagesize = vma_kernel_pagesize(vma);

		अगर (start & (vma_hpagesize - 1))
			जाओ out_unlock;
	पूर्ण

	/*
	 * Search क्रम not compatible vmas.
	 */
	found = false;
	ret = -EINVAL;
	क्रम (cur = vma; cur && cur->vm_start < end; cur = cur->vm_next) अणु
		cond_resched();

		BUG_ON(!!cur->vm_userfaultfd_ctx.ctx ^
		       !!(cur->vm_flags & __VM_UFFD_FLAGS));

		/*
		 * Check not compatible vmas, not strictly required
		 * here as not compatible vmas cannot have an
		 * userfaultfd_ctx रेजिस्टरed on them, but this
		 * provides क्रम more strict behavior to notice
		 * unregistration errors.
		 */
		अगर (!vma_can_userfault(cur, cur->vm_flags))
			जाओ out_unlock;

		found = true;
	पूर्ण
	BUG_ON(!found);

	अगर (vma->vm_start < start)
		prev = vma;

	ret = 0;
	करो अणु
		cond_resched();

		BUG_ON(!vma_can_userfault(vma, vma->vm_flags));

		/*
		 * Nothing to करो: this vma is alपढ़ोy रेजिस्टरed पूर्णांकo this
		 * userfaultfd and with the right tracking mode too.
		 */
		अगर (!vma->vm_userfaultfd_ctx.ctx)
			जाओ skip;

		WARN_ON(!(vma->vm_flags & VM_MAYWRITE));

		अगर (vma->vm_start > start)
			start = vma->vm_start;
		vma_end = min(end, vma->vm_end);

		अगर (userfaultfd_missing(vma)) अणु
			/*
			 * Wake any concurrent pending userfault जबतक
			 * we unरेजिस्टर, so they will not hang
			 * permanently and it aव्योमs userland to call
			 * UFFDIO_WAKE explicitly.
			 */
			काष्ठा userfaultfd_wake_range range;
			range.start = start;
			range.len = vma_end - start;
			wake_userfault(vma->vm_userfaultfd_ctx.ctx, &range);
		पूर्ण

		new_flags = vma->vm_flags & ~__VM_UFFD_FLAGS;
		prev = vma_merge(mm, prev, start, vma_end, new_flags,
				 vma->anon_vma, vma->vm_file, vma->vm_pgoff,
				 vma_policy(vma),
				 शून्य_VM_UFFD_CTX);
		अगर (prev) अणु
			vma = prev;
			जाओ next;
		पूर्ण
		अगर (vma->vm_start < start) अणु
			ret = split_vma(mm, vma, start, 1);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (vma->vm_end > end) अणु
			ret = split_vma(mm, vma, end, 0);
			अगर (ret)
				अवरोध;
		पूर्ण
	next:
		/*
		 * In the vma_merge() successful mprotect-like हाल 8:
		 * the next vma was merged पूर्णांकo the current one and
		 * the current one has not been updated yet.
		 */
		vma->vm_flags = new_flags;
		vma->vm_userfaultfd_ctx = शून्य_VM_UFFD_CTX;

	skip:
		prev = vma;
		start = vma->vm_end;
		vma = vma->vm_next;
	पूर्ण जबतक (vma && vma->vm_start < end);
out_unlock:
	mmap_ग_लिखो_unlock(mm);
	mmput(mm);
out:
	वापस ret;
पूर्ण

/*
 * userfaultfd_wake may be used in combination with the
 * UFFDIO_*_MODE_DONTWAKE to wakeup userfaults in batches.
 */
अटल पूर्णांक userfaultfd_wake(काष्ठा userfaultfd_ctx *ctx,
			    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा uffdio_range uffdio_wake;
	काष्ठा userfaultfd_wake_range range;
	स्थिर व्योम __user *buf = (व्योम __user *)arg;

	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_wake, buf, माप(uffdio_wake)))
		जाओ out;

	ret = validate_range(ctx->mm, &uffdio_wake.start, uffdio_wake.len);
	अगर (ret)
		जाओ out;

	range.start = uffdio_wake.start;
	range.len = uffdio_wake.len;

	/*
	 * len == 0 means wake all and we करोn't want to wake all here,
	 * so check it again to be sure.
	 */
	VM_BUG_ON(!range.len);

	wake_userfault(ctx, &range);
	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक userfaultfd_copy(काष्ठा userfaultfd_ctx *ctx,
			    अचिन्हित दीर्घ arg)
अणु
	__s64 ret;
	काष्ठा uffdio_copy uffdio_copy;
	काष्ठा uffdio_copy __user *user_uffdio_copy;
	काष्ठा userfaultfd_wake_range range;

	user_uffdio_copy = (काष्ठा uffdio_copy __user *) arg;

	ret = -EAGAIN;
	अगर (READ_ONCE(ctx->mmap_changing))
		जाओ out;

	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_copy, user_uffdio_copy,
			   /* करोn't copy "copy" last field */
			   माप(uffdio_copy)-माप(__s64)))
		जाओ out;

	ret = validate_range(ctx->mm, &uffdio_copy.dst, uffdio_copy.len);
	अगर (ret)
		जाओ out;
	/*
	 * द्विगुन check क्रम wraparound just in हाल. copy_from_user()
	 * will later check uffdio_copy.src + uffdio_copy.len to fit
	 * in the userland range.
	 */
	ret = -EINVAL;
	अगर (uffdio_copy.src + uffdio_copy.len <= uffdio_copy.src)
		जाओ out;
	अगर (uffdio_copy.mode & ~(UFFDIO_COPY_MODE_DONTWAKE|UFFDIO_COPY_MODE_WP))
		जाओ out;
	अगर (mmget_not_zero(ctx->mm)) अणु
		ret = mcopy_atomic(ctx->mm, uffdio_copy.dst, uffdio_copy.src,
				   uffdio_copy.len, &ctx->mmap_changing,
				   uffdio_copy.mode);
		mmput(ctx->mm);
	पूर्ण अन्यथा अणु
		वापस -ESRCH;
	पूर्ण
	अगर (unlikely(put_user(ret, &user_uffdio_copy->copy)))
		वापस -EFAULT;
	अगर (ret < 0)
		जाओ out;
	BUG_ON(!ret);
	/* len == 0 would wake all */
	range.len = ret;
	अगर (!(uffdio_copy.mode & UFFDIO_COPY_MODE_DONTWAKE)) अणु
		range.start = uffdio_copy.dst;
		wake_userfault(ctx, &range);
	पूर्ण
	ret = range.len == uffdio_copy.len ? 0 : -EAGAIN;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक userfaultfd_zeropage(काष्ठा userfaultfd_ctx *ctx,
				अचिन्हित दीर्घ arg)
अणु
	__s64 ret;
	काष्ठा uffdio_zeropage uffdio_zeropage;
	काष्ठा uffdio_zeropage __user *user_uffdio_zeropage;
	काष्ठा userfaultfd_wake_range range;

	user_uffdio_zeropage = (काष्ठा uffdio_zeropage __user *) arg;

	ret = -EAGAIN;
	अगर (READ_ONCE(ctx->mmap_changing))
		जाओ out;

	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_zeropage, user_uffdio_zeropage,
			   /* करोn't copy "zeropage" last field */
			   माप(uffdio_zeropage)-माप(__s64)))
		जाओ out;

	ret = validate_range(ctx->mm, &uffdio_zeropage.range.start,
			     uffdio_zeropage.range.len);
	अगर (ret)
		जाओ out;
	ret = -EINVAL;
	अगर (uffdio_zeropage.mode & ~UFFDIO_ZEROPAGE_MODE_DONTWAKE)
		जाओ out;

	अगर (mmget_not_zero(ctx->mm)) अणु
		ret = mfill_zeropage(ctx->mm, uffdio_zeropage.range.start,
				     uffdio_zeropage.range.len,
				     &ctx->mmap_changing);
		mmput(ctx->mm);
	पूर्ण अन्यथा अणु
		वापस -ESRCH;
	पूर्ण
	अगर (unlikely(put_user(ret, &user_uffdio_zeropage->zeropage)))
		वापस -EFAULT;
	अगर (ret < 0)
		जाओ out;
	/* len == 0 would wake all */
	BUG_ON(!ret);
	range.len = ret;
	अगर (!(uffdio_zeropage.mode & UFFDIO_ZEROPAGE_MODE_DONTWAKE)) अणु
		range.start = uffdio_zeropage.range.start;
		wake_userfault(ctx, &range);
	पूर्ण
	ret = range.len == uffdio_zeropage.range.len ? 0 : -EAGAIN;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक userfaultfd_ग_लिखोprotect(काष्ठा userfaultfd_ctx *ctx,
				    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा uffdio_ग_लिखोprotect uffdio_wp;
	काष्ठा uffdio_ग_लिखोprotect __user *user_uffdio_wp;
	काष्ठा userfaultfd_wake_range range;
	bool mode_wp, mode_करोntwake;

	अगर (READ_ONCE(ctx->mmap_changing))
		वापस -EAGAIN;

	user_uffdio_wp = (काष्ठा uffdio_ग_लिखोprotect __user *) arg;

	अगर (copy_from_user(&uffdio_wp, user_uffdio_wp,
			   माप(काष्ठा uffdio_ग_लिखोprotect)))
		वापस -EFAULT;

	ret = validate_range(ctx->mm, &uffdio_wp.range.start,
			     uffdio_wp.range.len);
	अगर (ret)
		वापस ret;

	अगर (uffdio_wp.mode & ~(UFFDIO_WRITEPROTECT_MODE_DONTWAKE |
			       UFFDIO_WRITEPROTECT_MODE_WP))
		वापस -EINVAL;

	mode_wp = uffdio_wp.mode & UFFDIO_WRITEPROTECT_MODE_WP;
	mode_करोntwake = uffdio_wp.mode & UFFDIO_WRITEPROTECT_MODE_DONTWAKE;

	अगर (mode_wp && mode_करोntwake)
		वापस -EINVAL;

	ret = mग_लिखोprotect_range(ctx->mm, uffdio_wp.range.start,
				  uffdio_wp.range.len, mode_wp,
				  &ctx->mmap_changing);
	अगर (ret)
		वापस ret;

	अगर (!mode_wp && !mode_करोntwake) अणु
		range.start = uffdio_wp.range.start;
		range.len = uffdio_wp.range.len;
		wake_userfault(ctx, &range);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक userfaultfd_जारी(काष्ठा userfaultfd_ctx *ctx, अचिन्हित दीर्घ arg)
अणु
	__s64 ret;
	काष्ठा uffdio_जारी uffdio_जारी;
	काष्ठा uffdio_जारी __user *user_uffdio_जारी;
	काष्ठा userfaultfd_wake_range range;

	user_uffdio_जारी = (काष्ठा uffdio_जारी __user *)arg;

	ret = -EAGAIN;
	अगर (READ_ONCE(ctx->mmap_changing))
		जाओ out;

	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_जारी, user_uffdio_जारी,
			   /* करोn't copy the output fields */
			   माप(uffdio_जारी) - (माप(__s64))))
		जाओ out;

	ret = validate_range(ctx->mm, &uffdio_जारी.range.start,
			     uffdio_जारी.range.len);
	अगर (ret)
		जाओ out;

	ret = -EINVAL;
	/* द्विगुन check क्रम wraparound just in हाल. */
	अगर (uffdio_जारी.range.start + uffdio_जारी.range.len <=
	    uffdio_जारी.range.start) अणु
		जाओ out;
	पूर्ण
	अगर (uffdio_जारी.mode & ~UFFDIO_CONTINUE_MODE_DONTWAKE)
		जाओ out;

	अगर (mmget_not_zero(ctx->mm)) अणु
		ret = mcopy_जारी(ctx->mm, uffdio_जारी.range.start,
				     uffdio_जारी.range.len,
				     &ctx->mmap_changing);
		mmput(ctx->mm);
	पूर्ण अन्यथा अणु
		वापस -ESRCH;
	पूर्ण

	अगर (unlikely(put_user(ret, &user_uffdio_जारी->mapped)))
		वापस -EFAULT;
	अगर (ret < 0)
		जाओ out;

	/* len == 0 would wake all */
	BUG_ON(!ret);
	range.len = ret;
	अगर (!(uffdio_जारी.mode & UFFDIO_CONTINUE_MODE_DONTWAKE)) अणु
		range.start = uffdio_जारी.range.start;
		wake_userfault(ctx, &range);
	पूर्ण
	ret = range.len == uffdio_जारी.range.len ? 0 : -EAGAIN;

out:
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक uffd_ctx_features(__u64 user_features)
अणु
	/*
	 * For the current set of features the bits just coincide
	 */
	वापस (अचिन्हित पूर्णांक)user_features;
पूर्ण

/*
 * userland asks क्रम a certain API version and we वापस which bits
 * and ioctl commands are implemented in this kernel क्रम such API
 * version or -EINVAL अगर unknown.
 */
अटल पूर्णांक userfaultfd_api(काष्ठा userfaultfd_ctx *ctx,
			   अचिन्हित दीर्घ arg)
अणु
	काष्ठा uffdio_api uffdio_api;
	व्योम __user *buf = (व्योम __user *)arg;
	पूर्णांक ret;
	__u64 features;

	ret = -EINVAL;
	अगर (ctx->state != UFFD_STATE_WAIT_API)
		जाओ out;
	ret = -EFAULT;
	अगर (copy_from_user(&uffdio_api, buf, माप(uffdio_api)))
		जाओ out;
	features = uffdio_api.features;
	ret = -EINVAL;
	अगर (uffdio_api.api != UFFD_API || (features & ~UFFD_API_FEATURES))
		जाओ err_out;
	ret = -EPERM;
	अगर ((features & UFFD_FEATURE_EVENT_FORK) && !capable(CAP_SYS_PTRACE))
		जाओ err_out;
	/* report all available features and ioctls to userland */
	uffdio_api.features = UFFD_API_FEATURES;
#अगर_अघोषित CONFIG_HAVE_ARCH_USERFAULTFD_MINOR
	uffdio_api.features &= ~UFFD_FEATURE_MINOR_HUGETLBFS;
#पूर्ण_अगर
	uffdio_api.ioctls = UFFD_API_IOCTLS;
	ret = -EFAULT;
	अगर (copy_to_user(buf, &uffdio_api, माप(uffdio_api)))
		जाओ out;
	ctx->state = UFFD_STATE_RUNNING;
	/* only enable the requested features क्रम this uffd context */
	ctx->features = uffd_ctx_features(features);
	ret = 0;
out:
	वापस ret;
err_out:
	स_रखो(&uffdio_api, 0, माप(uffdio_api));
	अगर (copy_to_user(buf, &uffdio_api, माप(uffdio_api)))
		ret = -EFAULT;
	जाओ out;
पूर्ण

अटल दीर्घ userfaultfd_ioctl(काष्ठा file *file, अचिन्हित cmd,
			      अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा userfaultfd_ctx *ctx = file->निजी_data;

	अगर (cmd != UFFDIO_API && ctx->state == UFFD_STATE_WAIT_API)
		वापस -EINVAL;

	चयन(cmd) अणु
	हाल UFFDIO_API:
		ret = userfaultfd_api(ctx, arg);
		अवरोध;
	हाल UFFDIO_REGISTER:
		ret = userfaultfd_रेजिस्टर(ctx, arg);
		अवरोध;
	हाल UFFDIO_UNREGISTER:
		ret = userfaultfd_unरेजिस्टर(ctx, arg);
		अवरोध;
	हाल UFFDIO_WAKE:
		ret = userfaultfd_wake(ctx, arg);
		अवरोध;
	हाल UFFDIO_COPY:
		ret = userfaultfd_copy(ctx, arg);
		अवरोध;
	हाल UFFDIO_ZEROPAGE:
		ret = userfaultfd_zeropage(ctx, arg);
		अवरोध;
	हाल UFFDIO_WRITEPROTECT:
		ret = userfaultfd_ग_लिखोprotect(ctx, arg);
		अवरोध;
	हाल UFFDIO_CONTINUE:
		ret = userfaultfd_जारी(ctx, arg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम userfaultfd_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा userfaultfd_ctx *ctx = f->निजी_data;
	रुको_queue_entry_t *wq;
	अचिन्हित दीर्घ pending = 0, total = 0;

	spin_lock_irq(&ctx->fault_pending_wqh.lock);
	list_क्रम_each_entry(wq, &ctx->fault_pending_wqh.head, entry) अणु
		pending++;
		total++;
	पूर्ण
	list_क्रम_each_entry(wq, &ctx->fault_wqh.head, entry) अणु
		total++;
	पूर्ण
	spin_unlock_irq(&ctx->fault_pending_wqh.lock);

	/*
	 * If more protocols will be added, there will be all shown
	 * separated by a space. Like this:
	 *	protocols: aa:... bb:...
	 */
	seq_म_लिखो(m, "pending:\t%lu\ntotal:\t%lu\nAPI:\t%Lx:%x:%Lx\n",
		   pending, total, UFFD_API, ctx->features,
		   UFFD_API_IOCTLS|UFFD_API_RANGE_IOCTLS);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations userfaultfd_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= userfaultfd_show_fdinfo,
#पूर्ण_अगर
	.release	= userfaultfd_release,
	.poll		= userfaultfd_poll,
	.पढ़ो		= userfaultfd_पढ़ो,
	.unlocked_ioctl = userfaultfd_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

अटल व्योम init_once_userfaultfd_ctx(व्योम *mem)
अणु
	काष्ठा userfaultfd_ctx *ctx = (काष्ठा userfaultfd_ctx *) mem;

	init_रुकोqueue_head(&ctx->fault_pending_wqh);
	init_रुकोqueue_head(&ctx->fault_wqh);
	init_रुकोqueue_head(&ctx->event_wqh);
	init_रुकोqueue_head(&ctx->fd_wqh);
	seqcount_spinlock_init(&ctx->refile_seq, &ctx->fault_pending_wqh.lock);
पूर्ण

SYSCALL_DEFINE1(userfaultfd, पूर्णांक, flags)
अणु
	काष्ठा userfaultfd_ctx *ctx;
	पूर्णांक fd;

	अगर (!sysctl_unprivileged_userfaultfd &&
	    (flags & UFFD_USER_MODE_ONLY) == 0 &&
	    !capable(CAP_SYS_PTRACE)) अणु
		prपूर्णांकk_once(KERN_WARNING "uffd: Set unprivileged_userfaultfd "
			"sysctl knob to 1 if kernel faults must be handled "
			"without obtaining CAP_SYS_PTRACE capability\n");
		वापस -EPERM;
	पूर्ण

	BUG_ON(!current->mm);

	/* Check the UFFD_* स्थिरants क्रम consistency.  */
	BUILD_BUG_ON(UFFD_USER_MODE_ONLY & UFFD_SHARED_FCNTL_FLAGS);
	BUILD_BUG_ON(UFFD_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(UFFD_NONBLOCK != O_NONBLOCK);

	अगर (flags & ~(UFFD_SHARED_FCNTL_FLAGS | UFFD_USER_MODE_ONLY))
		वापस -EINVAL;

	ctx = kmem_cache_alloc(userfaultfd_ctx_cachep, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	refcount_set(&ctx->refcount, 1);
	ctx->flags = flags;
	ctx->features = 0;
	ctx->state = UFFD_STATE_WAIT_API;
	ctx->released = false;
	ctx->mmap_changing = false;
	ctx->mm = current->mm;
	/* prevent the mm काष्ठा to be मुक्तd */
	mmgrab(ctx->mm);

	fd = anon_inode_getfd_secure("[userfaultfd]", &userfaultfd_fops, ctx,
			O_RDWR | (flags & UFFD_SHARED_FCNTL_FLAGS), शून्य);
	अगर (fd < 0) अणु
		mmdrop(ctx->mm);
		kmem_cache_मुक्त(userfaultfd_ctx_cachep, ctx);
	पूर्ण
	वापस fd;
पूर्ण

अटल पूर्णांक __init userfaultfd_init(व्योम)
अणु
	userfaultfd_ctx_cachep = kmem_cache_create("userfaultfd_ctx_cache",
						माप(काष्ठा userfaultfd_ctx),
						0,
						SLAB_HWCACHE_ALIGN|SLAB_PANIC,
						init_once_userfaultfd_ctx);
	वापस 0;
पूर्ण
__initcall(userfaultfd_init);
