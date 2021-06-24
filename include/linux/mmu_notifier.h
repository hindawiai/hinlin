<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MMU_NOTIFIER_H
#घोषणा _LINUX_MMU_NOTIFIER_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mmap_lock.h>
#समावेश <linux/srcu.h>
#समावेश <linux/पूर्णांकerval_tree.h>

काष्ठा mmu_notअगरier_subscriptions;
काष्ठा mmu_notअगरier;
काष्ठा mmu_notअगरier_range;
काष्ठा mmu_पूर्णांकerval_notअगरier;

/**
 * क्रमागत mmu_notअगरier_event - reason क्रम the mmu notअगरier callback
 * @MMU_NOTIFY_UNMAP: either munmap() that unmap the range or a mremap() that
 * move the range
 *
 * @MMU_NOTIFY_CLEAR: clear page table entry (many reasons क्रम this like
 * madvise() or replacing a page by another one, ...).
 *
 * @MMU_NOTIFY_PROTECTION_VMA: update is due to protection change क्रम the range
 * ie using the vma access permission (vm_page_prot) to update the whole range
 * is enough no need to inspect changes to the CPU page table (mprotect()
 * syscall)
 *
 * @MMU_NOTIFY_PROTECTION_PAGE: update is due to change in पढ़ो/ग_लिखो flag क्रम
 * pages in the range so to mirror those changes the user must inspect the CPU
 * page table (from the end callback).
 *
 * @MMU_NOTIFY_SOFT_सूचीTY: soft dirty accounting (still same page and same
 * access flags). User should soft dirty the page in the end callback to make
 * sure that anyone relying on soft dirtyness catch pages that might be written
 * through non CPU mappings.
 *
 * @MMU_NOTIFY_RELEASE: used during mmu_पूर्णांकerval_notअगरier invalidate to संकेत
 * that the mm refcount is zero and the range is no दीर्घer accessible.
 *
 * @MMU_NOTIFY_MIGRATE: used during migrate_vma_collect() invalidate to संकेत
 * a device driver to possibly ignore the invalidation अगर the
 * migrate_pgmap_owner field matches the driver's device निजी pgmap owner.
 */
क्रमागत mmu_notअगरier_event अणु
	MMU_NOTIFY_UNMAP = 0,
	MMU_NOTIFY_CLEAR,
	MMU_NOTIFY_PROTECTION_VMA,
	MMU_NOTIFY_PROTECTION_PAGE,
	MMU_NOTIFY_SOFT_सूचीTY,
	MMU_NOTIFY_RELEASE,
	MMU_NOTIFY_MIGRATE,
पूर्ण;

#घोषणा MMU_NOTIFIER_RANGE_BLOCKABLE (1 << 0)

काष्ठा mmu_notअगरier_ops अणु
	/*
	 * Called either by mmu_notअगरier_unरेजिस्टर or when the mm is
	 * being destroyed by निकास_mmap, always beक्रमe all pages are
	 * मुक्तd. This can run concurrently with other mmu notअगरier
	 * methods (the ones invoked outside the mm context) and it
	 * should tear करोwn all secondary mmu mappings and मुक्तze the
	 * secondary mmu. If this method isn't implemented you've to
	 * be sure that nothing could possibly ग_लिखो to the pages
	 * through the secondary mmu by the समय the last thपढ़ो with
	 * tsk->mm == mm निकासs.
	 *
	 * As side note: the pages मुक्तd after ->release वापसs could
	 * be immediately पुनः_स्मृतिated by the gart at an alias physical
	 * address with a dअगरferent cache model, so अगर ->release isn't
	 * implemented because all _software_ driven memory accesses
	 * through the secondary mmu are terminated by the समय the
	 * last thपढ़ो of this mm quits, you've also to be sure that
	 * speculative _hardware_ operations can't allocate dirty
	 * cachelines in the cpu that could not be snooped and made
	 * coherent with the other पढ़ो and ग_लिखो operations happening
	 * through the gart alias address, so leading to memory
	 * corruption.
	 */
	व्योम (*release)(काष्ठा mmu_notअगरier *subscription,
			काष्ठा mm_काष्ठा *mm);

	/*
	 * clear_flush_young is called after the VM is
	 * test-and-clearing the young/accessed bitflag in the
	 * pte. This way the VM will provide proper aging to the
	 * accesses to the page through the secondary MMUs and not
	 * only to the ones through the Linux pte.
	 * Start-end is necessary in हाल the secondary MMU is mapping the page
	 * at a smaller granularity than the primary MMU.
	 */
	पूर्णांक (*clear_flush_young)(काष्ठा mmu_notअगरier *subscription,
				 काष्ठा mm_काष्ठा *mm,
				 अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ end);

	/*
	 * clear_young is a lightweight version of clear_flush_young. Like the
	 * latter, it is supposed to test-and-clear the young/accessed bitflag
	 * in the secondary pte, but it may omit flushing the secondary tlb.
	 */
	पूर्णांक (*clear_young)(काष्ठा mmu_notअगरier *subscription,
			   काष्ठा mm_काष्ठा *mm,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end);

	/*
	 * test_young is called to check the young/accessed bitflag in
	 * the secondary pte. This is used to know अगर the page is
	 * frequently used without actually clearing the flag or tearing
	 * करोwn the secondary mapping on the page.
	 */
	पूर्णांक (*test_young)(काष्ठा mmu_notअगरier *subscription,
			  काष्ठा mm_काष्ठा *mm,
			  अचिन्हित दीर्घ address);

	/*
	 * change_pte is called in हालs that pte mapping to page is changed:
	 * क्रम example, when ksm remaps pte to poपूर्णांक to a new shared page.
	 */
	व्योम (*change_pte)(काष्ठा mmu_notअगरier *subscription,
			   काष्ठा mm_काष्ठा *mm,
			   अचिन्हित दीर्घ address,
			   pte_t pte);

	/*
	 * invalidate_range_start() and invalidate_range_end() must be
	 * paired and are called only when the mmap_lock and/or the
	 * locks protecting the reverse maps are held. If the subप्रणाली
	 * can't guarantee that no additional references are taken to
	 * the pages in the range, it has to implement the
	 * invalidate_range() notअगरier to हटाओ any references taken
	 * after invalidate_range_start().
	 *
	 * Invalidation of multiple concurrent ranges may be
	 * optionally permitted by the driver. Either way the
	 * establishment of sptes is क्रमbidden in the range passed to
	 * invalidate_range_begin/end क्रम the whole duration of the
	 * invalidate_range_begin/end critical section.
	 *
	 * invalidate_range_start() is called when all pages in the
	 * range are still mapped and have at least a refcount of one.
	 *
	 * invalidate_range_end() is called when all pages in the
	 * range have been unmapped and the pages have been मुक्तd by
	 * the VM.
	 *
	 * The VM will हटाओ the page table entries and potentially
	 * the page between invalidate_range_start() and
	 * invalidate_range_end(). If the page must not be मुक्तd
	 * because of pending I/O or other circumstances then the
	 * invalidate_range_start() callback (or the initial mapping
	 * by the driver) must make sure that the refcount is kept
	 * elevated.
	 *
	 * If the driver increases the refcount when the pages are
	 * initially mapped पूर्णांकo an address space then either
	 * invalidate_range_start() or invalidate_range_end() may
	 * decrease the refcount. If the refcount is decreased on
	 * invalidate_range_start() then the VM can मुक्त pages as page
	 * table entries are हटाओd.  If the refcount is only
	 * droppped on invalidate_range_end() then the driver itself
	 * will drop the last refcount but it must take care to flush
	 * any secondary tlb beक्रमe करोing the final मुक्त on the
	 * page. Pages will no दीर्घer be referenced by the linux
	 * address space but may still be referenced by sptes until
	 * the last refcount is dropped.
	 *
	 * If blockable argument is set to false then the callback cannot
	 * sleep and has to वापस with -EAGAIN अगर sleeping would be required.
	 * 0 should be वापसed otherwise. Please note that notअगरiers that can
	 * fail invalidate_range_start are not allowed to implement
	 * invalidate_range_end, as there is no mechanism क्रम inक्रमming the
	 * notअगरier that its start failed.
	 */
	पूर्णांक (*invalidate_range_start)(काष्ठा mmu_notअगरier *subscription,
				      स्थिर काष्ठा mmu_notअगरier_range *range);
	व्योम (*invalidate_range_end)(काष्ठा mmu_notअगरier *subscription,
				     स्थिर काष्ठा mmu_notअगरier_range *range);

	/*
	 * invalidate_range() is either called between
	 * invalidate_range_start() and invalidate_range_end() when the
	 * VM has to मुक्त pages that where unmapped, but beक्रमe the
	 * pages are actually मुक्तd, or outside of _start()/_end() when
	 * a (remote) TLB is necessary.
	 *
	 * If invalidate_range() is used to manage a non-CPU TLB with
	 * shared page-tables, it not necessary to implement the
	 * invalidate_range_start()/end() notअगरiers, as
	 * invalidate_range() alपढ़ो catches the poपूर्णांकs in समय when an
	 * बाह्यal TLB range needs to be flushed. For more in depth
	 * discussion on this see Documentation/vm/mmu_notअगरier.rst
	 *
	 * Note that this function might be called with just a sub-range
	 * of what was passed to invalidate_range_start()/end(), अगर
	 * called between those functions.
	 */
	व्योम (*invalidate_range)(काष्ठा mmu_notअगरier *subscription,
				 काष्ठा mm_काष्ठा *mm,
				 अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ end);

	/*
	 * These callbacks are used with the get/put पूर्णांकerface to manage the
	 * lअगरeसमय of the mmu_notअगरier memory. alloc_notअगरier() वापसs a new
	 * notअगरier क्रम use with the mm.
	 *
	 * मुक्त_notअगरier() is only called after the mmu_notअगरier has been
	 * fully put, calls to any ops callback are prevented and no ops
	 * callbacks are currently running. It is called from a SRCU callback
	 * and cannot sleep.
	 */
	काष्ठा mmu_notअगरier *(*alloc_notअगरier)(काष्ठा mm_काष्ठा *mm);
	व्योम (*मुक्त_notअगरier)(काष्ठा mmu_notअगरier *subscription);
पूर्ण;

/*
 * The notअगरier chains are रक्षित by mmap_lock and/or the reverse map
 * semaphores. Notअगरier chains are only changed when all reverse maps and
 * the mmap_lock locks are taken.
 *
 * Thereक्रमe notअगरier chains can only be traversed when either
 *
 * 1. mmap_lock is held.
 * 2. One of the reverse map locks is held (i_mmap_rwsem or anon_vma->rwsem).
 * 3. No other concurrent thपढ़ो can access the list (release)
 */
काष्ठा mmu_notअगरier अणु
	काष्ठा hlist_node hlist;
	स्थिर काष्ठा mmu_notअगरier_ops *ops;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा rcu_head rcu;
	अचिन्हित पूर्णांक users;
पूर्ण;

/**
 * काष्ठा mmu_पूर्णांकerval_notअगरier_ops
 * @invalidate: Upon वापस the caller must stop using any SPTEs within this
 *              range. This function can sleep. Return false only अगर sleeping
 *              was required but mmu_notअगरier_range_blockable(range) is false.
 */
काष्ठा mmu_पूर्णांकerval_notअगरier_ops अणु
	bool (*invalidate)(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
			   स्थिर काष्ठा mmu_notअगरier_range *range,
			   अचिन्हित दीर्घ cur_seq);
पूर्ण;

काष्ठा mmu_पूर्णांकerval_notअगरier अणु
	काष्ठा पूर्णांकerval_tree_node पूर्णांकerval_tree;
	स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा hlist_node deferred_item;
	अचिन्हित दीर्घ invalidate_seq;
पूर्ण;

#अगर_घोषित CONFIG_MMU_NOTIFIER

#अगर_घोषित CONFIG_LOCKDEP
बाह्य काष्ठा lockdep_map __mmu_notअगरier_invalidate_range_start_map;
#पूर्ण_अगर

काष्ठा mmu_notअगरier_range अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित flags;
	क्रमागत mmu_notअगरier_event event;
	व्योम *migrate_pgmap_owner;
पूर्ण;

अटल अंतरभूत पूर्णांक mm_has_notअगरiers(काष्ठा mm_काष्ठा *mm)
अणु
	वापस unlikely(mm->notअगरier_subscriptions);
पूर्ण

काष्ठा mmu_notअगरier *mmu_notअगरier_get_locked(स्थिर काष्ठा mmu_notअगरier_ops *ops,
					     काष्ठा mm_काष्ठा *mm);
अटल अंतरभूत काष्ठा mmu_notअगरier *
mmu_notअगरier_get(स्थिर काष्ठा mmu_notअगरier_ops *ops, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_notअगरier *ret;

	mmap_ग_लिखो_lock(mm);
	ret = mmu_notअगरier_get_locked(ops, mm);
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
व्योम mmu_notअगरier_put(काष्ठा mmu_notअगरier *subscription);
व्योम mmu_notअगरier_synchronize(व्योम);

बाह्य पूर्णांक mmu_notअगरier_रेजिस्टर(काष्ठा mmu_notअगरier *subscription,
				 काष्ठा mm_काष्ठा *mm);
बाह्य पूर्णांक __mmu_notअगरier_रेजिस्टर(काष्ठा mmu_notअगरier *subscription,
				   काष्ठा mm_काष्ठा *mm);
बाह्य व्योम mmu_notअगरier_unरेजिस्टर(काष्ठा mmu_notअगरier *subscription,
				    काष्ठा mm_काष्ठा *mm);

अचिन्हित दीर्घ
mmu_पूर्णांकerval_पढ़ो_begin(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub);
पूर्णांक mmu_पूर्णांकerval_notअगरier_insert(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
				 काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ length,
				 स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops);
पूर्णांक mmu_पूर्णांकerval_notअगरier_insert_locked(
	काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub, काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ length,
	स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops);
व्योम mmu_पूर्णांकerval_notअगरier_हटाओ(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub);

/**
 * mmu_पूर्णांकerval_set_seq - Save the invalidation sequence
 * @पूर्णांकerval_sub - The subscription passed to invalidate
 * @cur_seq - The cur_seq passed to the invalidate() callback
 *
 * This must be called unconditionally from the invalidate callback of a
 * काष्ठा mmu_पूर्णांकerval_notअगरier_ops under the same lock that is used to call
 * mmu_पूर्णांकerval_पढ़ो_retry(). It updates the sequence number क्रम later use by
 * mmu_पूर्णांकerval_पढ़ो_retry(). The provided cur_seq will always be odd.
 *
 * If the caller करोes not call mmu_पूर्णांकerval_पढ़ो_begin() or
 * mmu_पूर्णांकerval_पढ़ो_retry() then this call is not required.
 */
अटल अंतरभूत व्योम
mmu_पूर्णांकerval_set_seq(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
		     अचिन्हित दीर्घ cur_seq)
अणु
	WRITE_ONCE(पूर्णांकerval_sub->invalidate_seq, cur_seq);
पूर्ण

/**
 * mmu_पूर्णांकerval_पढ़ो_retry - End a पढ़ो side critical section against a VA range
 * पूर्णांकerval_sub: The subscription
 * seq: The वापस of the paired mmu_पूर्णांकerval_पढ़ो_begin()
 *
 * This MUST be called under a user provided lock that is also held
 * unconditionally by op->invalidate() when it calls mmu_पूर्णांकerval_set_seq().
 *
 * Each call should be paired with a single mmu_पूर्णांकerval_पढ़ो_begin() and
 * should be used to conclude the पढ़ो side.
 *
 * Returns true अगर an invalidation collided with this critical section, and
 * the caller should retry.
 */
अटल अंतरभूत bool
mmu_पूर्णांकerval_पढ़ो_retry(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
			अचिन्हित दीर्घ seq)
अणु
	वापस पूर्णांकerval_sub->invalidate_seq != seq;
पूर्ण

/**
 * mmu_पूर्णांकerval_check_retry - Test अगर a collision has occurred
 * पूर्णांकerval_sub: The subscription
 * seq: The वापस of the matching mmu_पूर्णांकerval_पढ़ो_begin()
 *
 * This can be used in the critical section between mmu_पूर्णांकerval_पढ़ो_begin()
 * and mmu_पूर्णांकerval_पढ़ो_retry().  A वापस of true indicates an invalidation
 * has collided with this critical region and a future
 * mmu_पूर्णांकerval_पढ़ो_retry() will वापस true.
 *
 * False is not reliable and only suggests a collision may not have
 * occured. It can be called many बार and करोes not have to hold the user
 * provided lock.
 *
 * This call can be used as part of loops and other expensive operations to
 * expedite a retry.
 */
अटल अंतरभूत bool
mmu_पूर्णांकerval_check_retry(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
			 अचिन्हित दीर्घ seq)
अणु
	/* Pairs with the WRITE_ONCE in mmu_पूर्णांकerval_set_seq() */
	वापस READ_ONCE(पूर्णांकerval_sub->invalidate_seq) != seq;
पूर्ण

बाह्य व्योम __mmu_notअगरier_subscriptions_destroy(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम __mmu_notअगरier_release(काष्ठा mm_काष्ठा *mm);
बाह्य पूर्णांक __mmu_notअगरier_clear_flush_young(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end);
बाह्य पूर्णांक __mmu_notअगरier_clear_young(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ start,
				      अचिन्हित दीर्घ end);
बाह्य पूर्णांक __mmu_notअगरier_test_young(काष्ठा mm_काष्ठा *mm,
				     अचिन्हित दीर्घ address);
बाह्य व्योम __mmu_notअगरier_change_pte(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pte_t pte);
बाह्य पूर्णांक __mmu_notअगरier_invalidate_range_start(काष्ठा mmu_notअगरier_range *r);
बाह्य व्योम __mmu_notअगरier_invalidate_range_end(काष्ठा mmu_notअगरier_range *r,
				  bool only_end);
बाह्य व्योम __mmu_notअगरier_invalidate_range(काष्ठा mm_काष्ठा *mm,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य bool
mmu_notअगरier_range_update_to_पढ़ो_only(स्थिर काष्ठा mmu_notअगरier_range *range);

अटल अंतरभूत bool
mmu_notअगरier_range_blockable(स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	वापस (range->flags & MMU_NOTIFIER_RANGE_BLOCKABLE);
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_release(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm_has_notअगरiers(mm))
		__mmu_notअगरier_release(mm);
पूर्ण

अटल अंतरभूत पूर्णांक mmu_notअगरier_clear_flush_young(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	अगर (mm_has_notअगरiers(mm))
		वापस __mmu_notअगरier_clear_flush_young(mm, start, end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmu_notअगरier_clear_young(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ start,
					   अचिन्हित दीर्घ end)
अणु
	अगर (mm_has_notअगरiers(mm))
		वापस __mmu_notअगरier_clear_young(mm, start, end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmu_notअगरier_test_young(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ address)
अणु
	अगर (mm_has_notअगरiers(mm))
		वापस __mmu_notअगरier_test_young(mm, address);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_change_pte(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ address, pte_t pte)
अणु
	अगर (mm_has_notअगरiers(mm))
		__mmu_notअगरier_change_pte(mm, address, pte);
पूर्ण

अटल अंतरभूत व्योम
mmu_notअगरier_invalidate_range_start(काष्ठा mmu_notअगरier_range *range)
अणु
	might_sleep();

	lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
	अगर (mm_has_notअगरiers(range->mm)) अणु
		range->flags |= MMU_NOTIFIER_RANGE_BLOCKABLE;
		__mmu_notअगरier_invalidate_range_start(range);
	पूर्ण
	lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
पूर्ण

अटल अंतरभूत पूर्णांक
mmu_notअगरier_invalidate_range_start_nonblock(काष्ठा mmu_notअगरier_range *range)
अणु
	पूर्णांक ret = 0;

	lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
	अगर (mm_has_notअगरiers(range->mm)) अणु
		range->flags &= ~MMU_NOTIFIER_RANGE_BLOCKABLE;
		ret = __mmu_notअगरier_invalidate_range_start(range);
	पूर्ण
	lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
mmu_notअगरier_invalidate_range_end(काष्ठा mmu_notअगरier_range *range)
अणु
	अगर (mmu_notअगरier_range_blockable(range))
		might_sleep();

	अगर (mm_has_notअगरiers(range->mm))
		__mmu_notअगरier_invalidate_range_end(range, false);
पूर्ण

अटल अंतरभूत व्योम
mmu_notअगरier_invalidate_range_only_end(काष्ठा mmu_notअगरier_range *range)
अणु
	अगर (mm_has_notअगरiers(range->mm))
		__mmu_notअगरier_invalidate_range_end(range, true);
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_invalidate_range(काष्ठा mm_काष्ठा *mm,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (mm_has_notअगरiers(mm))
		__mmu_notअगरier_invalidate_range(mm, start, end);
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_subscriptions_init(काष्ठा mm_काष्ठा *mm)
अणु
	mm->notअगरier_subscriptions = शून्य;
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_subscriptions_destroy(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm_has_notअगरiers(mm))
		__mmu_notअगरier_subscriptions_destroy(mm);
पूर्ण


अटल अंतरभूत व्योम mmu_notअगरier_range_init(काष्ठा mmu_notअगरier_range *range,
					   क्रमागत mmu_notअगरier_event event,
					   अचिन्हित flags,
					   काष्ठा vm_area_काष्ठा *vma,
					   काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ start,
					   अचिन्हित दीर्घ end)
अणु
	range->vma = vma;
	range->event = event;
	range->mm = mm;
	range->start = start;
	range->end = end;
	range->flags = flags;
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_range_init_migrate(
			काष्ठा mmu_notअगरier_range *range, अचिन्हित पूर्णांक flags,
			काष्ठा vm_area_काष्ठा *vma, काष्ठा mm_काष्ठा *mm,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, व्योम *pgmap)
अणु
	mmu_notअगरier_range_init(range, MMU_NOTIFY_MIGRATE, flags, vma, mm,
				start, end);
	range->migrate_pgmap_owner = pgmap;
पूर्ण

#घोषणा ptep_clear_flush_young_notअगरy(__vma, __address, __ptep)		\
(अणु									\
	पूर्णांक __young;							\
	काष्ठा vm_area_काष्ठा *___vma = __vma;				\
	अचिन्हित दीर्घ ___address = __address;				\
	__young = ptep_clear_flush_young(___vma, ___address, __ptep);	\
	__young |= mmu_notअगरier_clear_flush_young(___vma->vm_mm,	\
						  ___address,		\
						  ___address +		\
							PAGE_SIZE);	\
	__young;							\
पूर्ण)

#घोषणा pmdp_clear_flush_young_notअगरy(__vma, __address, __pmdp)		\
(अणु									\
	पूर्णांक __young;							\
	काष्ठा vm_area_काष्ठा *___vma = __vma;				\
	अचिन्हित दीर्घ ___address = __address;				\
	__young = pmdp_clear_flush_young(___vma, ___address, __pmdp);	\
	__young |= mmu_notअगरier_clear_flush_young(___vma->vm_mm,	\
						  ___address,		\
						  ___address +		\
							PMD_SIZE);	\
	__young;							\
पूर्ण)

#घोषणा ptep_clear_young_notअगरy(__vma, __address, __ptep)		\
(अणु									\
	पूर्णांक __young;							\
	काष्ठा vm_area_काष्ठा *___vma = __vma;				\
	अचिन्हित दीर्घ ___address = __address;				\
	__young = ptep_test_and_clear_young(___vma, ___address, __ptep);\
	__young |= mmu_notअगरier_clear_young(___vma->vm_mm, ___address,	\
					    ___address + PAGE_SIZE);	\
	__young;							\
पूर्ण)

#घोषणा pmdp_clear_young_notअगरy(__vma, __address, __pmdp)		\
(अणु									\
	पूर्णांक __young;							\
	काष्ठा vm_area_काष्ठा *___vma = __vma;				\
	अचिन्हित दीर्घ ___address = __address;				\
	__young = pmdp_test_and_clear_young(___vma, ___address, __pmdp);\
	__young |= mmu_notअगरier_clear_young(___vma->vm_mm, ___address,	\
					    ___address + PMD_SIZE);	\
	__young;							\
पूर्ण)

#घोषणा	ptep_clear_flush_notअगरy(__vma, __address, __ptep)		\
(अणु									\
	अचिन्हित दीर्घ ___addr = __address & PAGE_MASK;			\
	काष्ठा mm_काष्ठा *___mm = (__vma)->vm_mm;			\
	pte_t ___pte;							\
									\
	___pte = ptep_clear_flush(__vma, __address, __ptep);		\
	mmu_notअगरier_invalidate_range(___mm, ___addr,			\
					___addr + PAGE_SIZE);		\
									\
	___pte;								\
पूर्ण)

#घोषणा pmdp_huge_clear_flush_notअगरy(__vma, __haddr, __pmd)		\
(अणु									\
	अचिन्हित दीर्घ ___haddr = __haddr & HPAGE_PMD_MASK;		\
	काष्ठा mm_काष्ठा *___mm = (__vma)->vm_mm;			\
	pmd_t ___pmd;							\
									\
	___pmd = pmdp_huge_clear_flush(__vma, __haddr, __pmd);		\
	mmu_notअगरier_invalidate_range(___mm, ___haddr,			\
				      ___haddr + HPAGE_PMD_SIZE);	\
									\
	___pmd;								\
पूर्ण)

#घोषणा pudp_huge_clear_flush_notअगरy(__vma, __haddr, __pud)		\
(अणु									\
	अचिन्हित दीर्घ ___haddr = __haddr & HPAGE_PUD_MASK;		\
	काष्ठा mm_काष्ठा *___mm = (__vma)->vm_mm;			\
	pud_t ___pud;							\
									\
	___pud = pudp_huge_clear_flush(__vma, __haddr, __pud);		\
	mmu_notअगरier_invalidate_range(___mm, ___haddr,			\
				      ___haddr + HPAGE_PUD_SIZE);	\
									\
	___pud;								\
पूर्ण)

/*
 * set_pte_at_notअगरy() sets the pte _after_ running the notअगरier.
 * This is safe to start by updating the secondary MMUs, because the primary MMU
 * pte invalidate must have alपढ़ोy happened with a ptep_clear_flush() beक्रमe
 * set_pte_at_notअगरy() has been invoked.  Updating the secondary MMUs first is
 * required when we change both the protection of the mapping from पढ़ो-only to
 * पढ़ो-ग_लिखो and the pfn (like during copy on ग_लिखो page faults). Otherwise the
 * old page would reमुख्य mapped पढ़ोonly in the secondary MMUs after the new
 * page is alपढ़ोy writable by some CPU through the primary MMU.
 */
#घोषणा set_pte_at_notअगरy(__mm, __address, __ptep, __pte)		\
(अणु									\
	काष्ठा mm_काष्ठा *___mm = __mm;					\
	अचिन्हित दीर्घ ___address = __address;				\
	pte_t ___pte = __pte;						\
									\
	mmu_notअगरier_change_pte(___mm, ___address, ___pte);		\
	set_pte_at(___mm, ___address, __ptep, ___pte);			\
पूर्ण)

#अन्यथा /* CONFIG_MMU_NOTIFIER */

काष्ठा mmu_notअगरier_range अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

अटल अंतरभूत व्योम _mmu_notअगरier_range_init(काष्ठा mmu_notअगरier_range *range,
					    अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ end)
अणु
	range->start = start;
	range->end = end;
पूर्ण

#घोषणा mmu_notअगरier_range_init(range,event,flags,vma,mm,start,end)  \
	_mmu_notअगरier_range_init(range, start, end)
#घोषणा mmu_notअगरier_range_init_migrate(range, flags, vma, mm, start, end, \
					pgmap) \
	_mmu_notअगरier_range_init(range, start, end)

अटल अंतरभूत bool
mmu_notअगरier_range_blockable(स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक mm_has_notअगरiers(काष्ठा mm_काष्ठा *mm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_release(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mmu_notअगरier_clear_flush_young(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmu_notअगरier_test_young(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ address)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_change_pte(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ address, pte_t pte)
अणु
पूर्ण

अटल अंतरभूत व्योम
mmu_notअगरier_invalidate_range_start(काष्ठा mmu_notअगरier_range *range)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
mmu_notअगरier_invalidate_range_start_nonblock(काष्ठा mmu_notअगरier_range *range)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम mmu_notअगरier_invalidate_range_end(काष्ठा mmu_notअगरier_range *range)
अणु
पूर्ण

अटल अंतरभूत व्योम
mmu_notअगरier_invalidate_range_only_end(काष्ठा mmu_notअगरier_range *range)
अणु
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_invalidate_range(काष्ठा mm_काष्ठा *mm,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_subscriptions_init(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल अंतरभूत व्योम mmu_notअगरier_subscriptions_destroy(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

#घोषणा mmu_notअगरier_range_update_to_पढ़ो_only(r) false

#घोषणा ptep_clear_flush_young_notअगरy ptep_clear_flush_young
#घोषणा pmdp_clear_flush_young_notअगरy pmdp_clear_flush_young
#घोषणा ptep_clear_young_notअगरy ptep_test_and_clear_young
#घोषणा pmdp_clear_young_notअगरy pmdp_test_and_clear_young
#घोषणा	ptep_clear_flush_notअगरy ptep_clear_flush
#घोषणा pmdp_huge_clear_flush_notअगरy pmdp_huge_clear_flush
#घोषणा pudp_huge_clear_flush_notअगरy pudp_huge_clear_flush
#घोषणा set_pte_at_notअगरy set_pte_at

अटल अंतरभूत व्योम mmu_notअगरier_synchronize(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU_NOTIFIER */

#पूर्ण_अगर /* _LINUX_MMU_NOTIFIER_H */
