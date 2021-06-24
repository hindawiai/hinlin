<शैली गुरु>
/*
 * mm/rmap.c - physical to भव reverse mappings
 *
 * Copyright 2001, Rik van Riel <riel@conectiva.com.br>
 * Released under the General Public License (GPL).
 *
 * Simple, low overhead reverse mapping scheme.
 * Please try to keep this thing as modular as possible.
 *
 * Provides methods क्रम unmapping each kind of mapped page:
 * the anon methods track anonymous pages, and
 * the file methods track pages beदीर्घing to an inode.
 *
 * Original design by Rik van Riel <riel@conectiva.com.br> 2001
 * File methods by Dave McCracken <dmccr@us.ibm.com> 2003, 2004
 * Anonymous methods by Andrea Arcangeli <andrea@suse.de> 2004
 * Contributions by Hugh Dickins 2003, 2004
 */

/*
 * Lock ordering in mm:
 *
 * inode->i_mutex	(जबतक writing or truncating, not पढ़ोing or faulting)
 *   mm->mmap_lock
 *     page->flags PG_locked (lock_page)   * (see huegtlbfs below)
 *       hugetlbfs_i_mmap_rwsem_key (in huge_pmd_share)
 *         mapping->i_mmap_rwsem
 *           hugetlb_fault_mutex (hugetlbfs specअगरic page fault mutex)
 *           anon_vma->rwsem
 *             mm->page_table_lock or pte_lock
 *               swap_lock (in swap_duplicate, swap_info_get)
 *                 mmlist_lock (in mmput, drain_mmlist and others)
 *                 mapping->निजी_lock (in __set_page_dirty_buffers)
 *                   lock_page_memcg move_lock (in __set_page_dirty_buffers)
 *                     i_pages lock (widely used)
 *                       lruvec->lru_lock (in lock_page_lruvec_irq)
 *                 inode->i_lock (in set_page_dirty's __mark_inode_dirty)
 *                 bdi.wb->list_lock (in set_page_dirty's __mark_inode_dirty)
 *                   sb_lock (within inode_lock in fs/fs-ग_लिखोback.c)
 *                   i_pages lock (widely used, in set_page_dirty,
 *                             in arch-dependent flush_dcache_mmap_lock,
 *                             within bdi.wb->list_lock in __sync_single_inode)
 *
 * anon_vma->rwsem,mapping->i_mutex      (memory_failure, collect_procs_anon)
 *   ->tasklist_lock
 *     pte map lock
 *
 * * hugetlbfs PageHuge() pages take locks in this order:
 *         mapping->i_mmap_rwsem
 *           hugetlb_fault_mutex (hugetlbfs specअगरic page fault mutex)
 *             page->flags PG_locked (lock_page)
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/ksm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/migrate.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/huge_mm.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/memremap.h>
#समावेश <linux/userfaultfd_k.h>

#समावेश <यंत्र/tlbflush.h>

#समावेश <trace/events/tlb.h>

#समावेश "internal.h"

अटल काष्ठा kmem_cache *anon_vma_cachep;
अटल काष्ठा kmem_cache *anon_vma_chain_cachep;

अटल अंतरभूत काष्ठा anon_vma *anon_vma_alloc(व्योम)
अणु
	काष्ठा anon_vma *anon_vma;

	anon_vma = kmem_cache_alloc(anon_vma_cachep, GFP_KERNEL);
	अगर (anon_vma) अणु
		atomic_set(&anon_vma->refcount, 1);
		anon_vma->degree = 1;	/* Reference क्रम first vma */
		anon_vma->parent = anon_vma;
		/*
		 * Initialise the anon_vma root to poपूर्णांक to itself. If called
		 * from विभाजन, the root will be reset to the parents anon_vma.
		 */
		anon_vma->root = anon_vma;
	पूर्ण

	वापस anon_vma;
पूर्ण

अटल अंतरभूत व्योम anon_vma_मुक्त(काष्ठा anon_vma *anon_vma)
अणु
	VM_BUG_ON(atomic_पढ़ो(&anon_vma->refcount));

	/*
	 * Synchronize against page_lock_anon_vma_पढ़ो() such that
	 * we can safely hold the lock without the anon_vma getting
	 * मुक्तd.
	 *
	 * Relies on the full mb implied by the atomic_dec_and_test() from
	 * put_anon_vma() against the acquire barrier implied by
	 * करोwn_पढ़ो_trylock() from page_lock_anon_vma_पढ़ो(). This orders:
	 *
	 * page_lock_anon_vma_पढ़ो()	VS	put_anon_vma()
	 *   करोwn_पढ़ो_trylock()		  atomic_dec_and_test()
	 *   LOCK				  MB
	 *   atomic_पढ़ो()			  rwsem_is_locked()
	 *
	 * LOCK should suffice since the actual taking of the lock must
	 * happen _beक्रमe_ what follows.
	 */
	might_sleep();
	अगर (rwsem_is_locked(&anon_vma->root->rwsem)) अणु
		anon_vma_lock_ग_लिखो(anon_vma);
		anon_vma_unlock_ग_लिखो(anon_vma);
	पूर्ण

	kmem_cache_मुक्त(anon_vma_cachep, anon_vma);
पूर्ण

अटल अंतरभूत काष्ठा anon_vma_chain *anon_vma_chain_alloc(gfp_t gfp)
अणु
	वापस kmem_cache_alloc(anon_vma_chain_cachep, gfp);
पूर्ण

अटल व्योम anon_vma_chain_मुक्त(काष्ठा anon_vma_chain *anon_vma_chain)
अणु
	kmem_cache_मुक्त(anon_vma_chain_cachep, anon_vma_chain);
पूर्ण

अटल व्योम anon_vma_chain_link(काष्ठा vm_area_काष्ठा *vma,
				काष्ठा anon_vma_chain *avc,
				काष्ठा anon_vma *anon_vma)
अणु
	avc->vma = vma;
	avc->anon_vma = anon_vma;
	list_add(&avc->same_vma, &vma->anon_vma_chain);
	anon_vma_पूर्णांकerval_tree_insert(avc, &anon_vma->rb_root);
पूर्ण

/**
 * __anon_vma_prepare - attach an anon_vma to a memory region
 * @vma: the memory region in question
 *
 * This makes sure the memory mapping described by 'vma' has
 * an 'anon_vma' attached to it, so that we can associate the
 * anonymous pages mapped पूर्णांकo it with that anon_vma.
 *
 * The common हाल will be that we alपढ़ोy have one, which
 * is handled अंतरभूत by anon_vma_prepare(). But अगर
 * not we either need to find an adjacent mapping that we
 * can re-use the anon_vma from (very common when the only
 * reason क्रम splitting a vma has been mprotect()), or we
 * allocate a new one.
 *
 * Anon-vma allocations are very subtle, because we may have
 * optimistically looked up an anon_vma in page_lock_anon_vma_पढ़ो()
 * and that may actually touch the rwsem even in the newly
 * allocated vma (it depends on RCU to make sure that the
 * anon_vma isn't actually destroyed).
 *
 * As a result, we need to करो proper anon_vma locking even
 * क्रम the new allocation. At the same समय, we करो not want
 * to करो any locking क्रम the common हाल of alपढ़ोy having
 * an anon_vma.
 *
 * This must be called with the mmap_lock held क्रम पढ़ोing.
 */
पूर्णांक __anon_vma_prepare(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा anon_vma *anon_vma, *allocated;
	काष्ठा anon_vma_chain *avc;

	might_sleep();

	avc = anon_vma_chain_alloc(GFP_KERNEL);
	अगर (!avc)
		जाओ out_enomem;

	anon_vma = find_mergeable_anon_vma(vma);
	allocated = शून्य;
	अगर (!anon_vma) अणु
		anon_vma = anon_vma_alloc();
		अगर (unlikely(!anon_vma))
			जाओ out_enomem_मुक्त_avc;
		allocated = anon_vma;
	पूर्ण

	anon_vma_lock_ग_लिखो(anon_vma);
	/* page_table_lock to protect against thपढ़ोs */
	spin_lock(&mm->page_table_lock);
	अगर (likely(!vma->anon_vma)) अणु
		vma->anon_vma = anon_vma;
		anon_vma_chain_link(vma, avc, anon_vma);
		/* vma reference or self-parent link क्रम new root */
		anon_vma->degree++;
		allocated = शून्य;
		avc = शून्य;
	पूर्ण
	spin_unlock(&mm->page_table_lock);
	anon_vma_unlock_ग_लिखो(anon_vma);

	अगर (unlikely(allocated))
		put_anon_vma(allocated);
	अगर (unlikely(avc))
		anon_vma_chain_मुक्त(avc);

	वापस 0;

 out_enomem_मुक्त_avc:
	anon_vma_chain_मुक्त(avc);
 out_enomem:
	वापस -ENOMEM;
पूर्ण

/*
 * This is a useful helper function क्रम locking the anon_vma root as
 * we traverse the vma->anon_vma_chain, looping over anon_vma's that
 * have the same vma.
 *
 * Such anon_vma's should have the same root, so you'd expect to see
 * just a single mutex_lock क्रम the whole traversal.
 */
अटल अंतरभूत काष्ठा anon_vma *lock_anon_vma_root(काष्ठा anon_vma *root, काष्ठा anon_vma *anon_vma)
अणु
	काष्ठा anon_vma *new_root = anon_vma->root;
	अगर (new_root != root) अणु
		अगर (WARN_ON_ONCE(root))
			up_ग_लिखो(&root->rwsem);
		root = new_root;
		करोwn_ग_लिखो(&root->rwsem);
	पूर्ण
	वापस root;
पूर्ण

अटल अंतरभूत व्योम unlock_anon_vma_root(काष्ठा anon_vma *root)
अणु
	अगर (root)
		up_ग_लिखो(&root->rwsem);
पूर्ण

/*
 * Attach the anon_vmas from src to dst.
 * Returns 0 on success, -ENOMEM on failure.
 *
 * anon_vma_clone() is called by __vma_adjust(), __split_vma(), copy_vma() and
 * anon_vma_विभाजन(). The first three want an exact copy of src, जबतक the last
 * one, anon_vma_विभाजन(), may try to reuse an existing anon_vma to prevent
 * endless growth of anon_vma. Since dst->anon_vma is set to शून्य beक्रमe call,
 * we can identअगरy this हाल by checking (!dst->anon_vma && src->anon_vma).
 *
 * If (!dst->anon_vma && src->anon_vma) is true, this function tries to find
 * and reuse existing anon_vma which has no vmas and only one child anon_vma.
 * This prevents degradation of anon_vma hierarchy to endless linear chain in
 * हाल of स्थिरantly विभाजनing task. On the other hand, an anon_vma with more
 * than one child isn't reused even अगर there was no alive vma, thus rmap
 * walker has a good chance of aव्योमing scanning the whole hierarchy when it
 * searches where page is mapped.
 */
पूर्णांक anon_vma_clone(काष्ठा vm_area_काष्ठा *dst, काष्ठा vm_area_काष्ठा *src)
अणु
	काष्ठा anon_vma_chain *avc, *pavc;
	काष्ठा anon_vma *root = शून्य;

	list_क्रम_each_entry_reverse(pavc, &src->anon_vma_chain, same_vma) अणु
		काष्ठा anon_vma *anon_vma;

		avc = anon_vma_chain_alloc(GFP_NOWAIT | __GFP_NOWARN);
		अगर (unlikely(!avc)) अणु
			unlock_anon_vma_root(root);
			root = शून्य;
			avc = anon_vma_chain_alloc(GFP_KERNEL);
			अगर (!avc)
				जाओ enomem_failure;
		पूर्ण
		anon_vma = pavc->anon_vma;
		root = lock_anon_vma_root(root, anon_vma);
		anon_vma_chain_link(dst, avc, anon_vma);

		/*
		 * Reuse existing anon_vma अगर its degree lower than two,
		 * that means it has no vma and only one anon_vma child.
		 *
		 * Do not chose parent anon_vma, otherwise first child
		 * will always reuse it. Root anon_vma is never reused:
		 * it has self-parent reference and at least one child.
		 */
		अगर (!dst->anon_vma && src->anon_vma &&
		    anon_vma != src->anon_vma && anon_vma->degree < 2)
			dst->anon_vma = anon_vma;
	पूर्ण
	अगर (dst->anon_vma)
		dst->anon_vma->degree++;
	unlock_anon_vma_root(root);
	वापस 0;

 enomem_failure:
	/*
	 * dst->anon_vma is dropped here otherwise its degree can be incorrectly
	 * decremented in unlink_anon_vmas().
	 * We can safely करो this because callers of anon_vma_clone() करोn't care
	 * about dst->anon_vma अगर anon_vma_clone() failed.
	 */
	dst->anon_vma = शून्य;
	unlink_anon_vmas(dst);
	वापस -ENOMEM;
पूर्ण

/*
 * Attach vma to its own anon_vma, as well as to the anon_vmas that
 * the corresponding VMA in the parent process is attached to.
 * Returns 0 on success, non-zero on failure.
 */
पूर्णांक anon_vma_विभाजन(काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_area_काष्ठा *pvma)
अणु
	काष्ठा anon_vma_chain *avc;
	काष्ठा anon_vma *anon_vma;
	पूर्णांक error;

	/* Don't bother अगर the parent process has no anon_vma here. */
	अगर (!pvma->anon_vma)
		वापस 0;

	/* Drop inherited anon_vma, we'll reuse existing or allocate new. */
	vma->anon_vma = शून्य;

	/*
	 * First, attach the new VMA to the parent VMA's anon_vmas,
	 * so rmap can find non-COWed pages in child processes.
	 */
	error = anon_vma_clone(vma, pvma);
	अगर (error)
		वापस error;

	/* An existing anon_vma has been reused, all करोne then. */
	अगर (vma->anon_vma)
		वापस 0;

	/* Then add our own anon_vma. */
	anon_vma = anon_vma_alloc();
	अगर (!anon_vma)
		जाओ out_error;
	avc = anon_vma_chain_alloc(GFP_KERNEL);
	अगर (!avc)
		जाओ out_error_मुक्त_anon_vma;

	/*
	 * The root anon_vma's rwsem is the lock actually used when we
	 * lock any of the anon_vmas in this anon_vma tree.
	 */
	anon_vma->root = pvma->anon_vma->root;
	anon_vma->parent = pvma->anon_vma;
	/*
	 * With refcounts, an anon_vma can stay around दीर्घer than the
	 * process it beदीर्घs to. The root anon_vma needs to be pinned until
	 * this anon_vma is मुक्तd, because the lock lives in the root.
	 */
	get_anon_vma(anon_vma->root);
	/* Mark this anon_vma as the one where our new (COWed) pages go. */
	vma->anon_vma = anon_vma;
	anon_vma_lock_ग_लिखो(anon_vma);
	anon_vma_chain_link(vma, avc, anon_vma);
	anon_vma->parent->degree++;
	anon_vma_unlock_ग_लिखो(anon_vma);

	वापस 0;

 out_error_मुक्त_anon_vma:
	put_anon_vma(anon_vma);
 out_error:
	unlink_anon_vmas(vma);
	वापस -ENOMEM;
पूर्ण

व्योम unlink_anon_vmas(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा anon_vma_chain *avc, *next;
	काष्ठा anon_vma *root = शून्य;

	/*
	 * Unlink each anon_vma chained to the VMA.  This list is ordered
	 * from newest to oldest, ensuring the root anon_vma माला_लो मुक्तd last.
	 */
	list_क्रम_each_entry_safe(avc, next, &vma->anon_vma_chain, same_vma) अणु
		काष्ठा anon_vma *anon_vma = avc->anon_vma;

		root = lock_anon_vma_root(root, anon_vma);
		anon_vma_पूर्णांकerval_tree_हटाओ(avc, &anon_vma->rb_root);

		/*
		 * Leave empty anon_vmas on the list - we'll need
		 * to मुक्त them outside the lock.
		 */
		अगर (RB_EMPTY_ROOT(&anon_vma->rb_root.rb_root)) अणु
			anon_vma->parent->degree--;
			जारी;
		पूर्ण

		list_del(&avc->same_vma);
		anon_vma_chain_मुक्त(avc);
	पूर्ण
	अगर (vma->anon_vma) अणु
		vma->anon_vma->degree--;

		/*
		 * vma would still be needed after unlink, and anon_vma will be prepared
		 * when handle fault.
		 */
		vma->anon_vma = शून्य;
	पूर्ण
	unlock_anon_vma_root(root);

	/*
	 * Iterate the list once more, it now only contains empty and unlinked
	 * anon_vmas, destroy them. Could not करो beक्रमe due to __put_anon_vma()
	 * needing to ग_लिखो-acquire the anon_vma->root->rwsem.
	 */
	list_क्रम_each_entry_safe(avc, next, &vma->anon_vma_chain, same_vma) अणु
		काष्ठा anon_vma *anon_vma = avc->anon_vma;

		VM_WARN_ON(anon_vma->degree);
		put_anon_vma(anon_vma);

		list_del(&avc->same_vma);
		anon_vma_chain_मुक्त(avc);
	पूर्ण
पूर्ण

अटल व्योम anon_vma_ctor(व्योम *data)
अणु
	काष्ठा anon_vma *anon_vma = data;

	init_rwsem(&anon_vma->rwsem);
	atomic_set(&anon_vma->refcount, 0);
	anon_vma->rb_root = RB_ROOT_CACHED;
पूर्ण

व्योम __init anon_vma_init(व्योम)
अणु
	anon_vma_cachep = kmem_cache_create("anon_vma", माप(काष्ठा anon_vma),
			0, SLAB_TYPESAFE_BY_RCU|SLAB_PANIC|SLAB_ACCOUNT,
			anon_vma_ctor);
	anon_vma_chain_cachep = KMEM_CACHE(anon_vma_chain,
			SLAB_PANIC|SLAB_ACCOUNT);
पूर्ण

/*
 * Getting a lock on a stable anon_vma from a page off the LRU is tricky!
 *
 * Since there is no serialization what so ever against page_हटाओ_rmap()
 * the best this function can करो is वापस a refcount increased anon_vma
 * that might have been relevant to this page.
 *
 * The page might have been remapped to a dअगरferent anon_vma or the anon_vma
 * वापसed may alपढ़ोy be मुक्तd (and even reused).
 *
 * In हाल it was remapped to a dअगरferent anon_vma, the new anon_vma will be a
 * child of the old anon_vma, and the anon_vma lअगरeसमय rules will thereक्रमe
 * ensure that any anon_vma obtained from the page will still be valid क्रम as
 * दीर्घ as we observe page_mapped() [ hence all those page_mapped() tests ].
 *
 * All users of this function must be very careful when walking the anon_vma
 * chain and verअगरy that the page in question is indeed mapped in it
 * [ something equivalent to page_mapped_in_vma() ].
 *
 * Since anon_vma's slab is SLAB_TYPESAFE_BY_RCU and we know from
 * page_हटाओ_rmap() that the anon_vma poपूर्णांकer from page->mapping is valid
 * अगर there is a mapcount, we can dereference the anon_vma after observing
 * those.
 */
काष्ठा anon_vma *page_get_anon_vma(काष्ठा page *page)
अणु
	काष्ठा anon_vma *anon_vma = शून्य;
	अचिन्हित दीर्घ anon_mapping;

	rcu_पढ़ो_lock();
	anon_mapping = (अचिन्हित दीर्घ)READ_ONCE(page->mapping);
	अगर ((anon_mapping & PAGE_MAPPING_FLAGS) != PAGE_MAPPING_ANON)
		जाओ out;
	अगर (!page_mapped(page))
		जाओ out;

	anon_vma = (काष्ठा anon_vma *) (anon_mapping - PAGE_MAPPING_ANON);
	अगर (!atomic_inc_not_zero(&anon_vma->refcount)) अणु
		anon_vma = शून्य;
		जाओ out;
	पूर्ण

	/*
	 * If this page is still mapped, then its anon_vma cannot have been
	 * मुक्तd.  But अगर it has been unmapped, we have no security against the
	 * anon_vma काष्ठाure being मुक्तd and reused (क्रम another anon_vma:
	 * SLAB_TYPESAFE_BY_RCU guarantees that - so the atomic_inc_not_zero()
	 * above cannot corrupt).
	 */
	अगर (!page_mapped(page)) अणु
		rcu_पढ़ो_unlock();
		put_anon_vma(anon_vma);
		वापस शून्य;
	पूर्ण
out:
	rcu_पढ़ो_unlock();

	वापस anon_vma;
पूर्ण

/*
 * Similar to page_get_anon_vma() except it locks the anon_vma.
 *
 * Its a little more complex as it tries to keep the fast path to a single
 * atomic op -- the trylock. If we fail the trylock, we fall back to getting a
 * reference like with page_get_anon_vma() and then block on the mutex.
 */
काष्ठा anon_vma *page_lock_anon_vma_पढ़ो(काष्ठा page *page)
अणु
	काष्ठा anon_vma *anon_vma = शून्य;
	काष्ठा anon_vma *root_anon_vma;
	अचिन्हित दीर्घ anon_mapping;

	rcu_पढ़ो_lock();
	anon_mapping = (अचिन्हित दीर्घ)READ_ONCE(page->mapping);
	अगर ((anon_mapping & PAGE_MAPPING_FLAGS) != PAGE_MAPPING_ANON)
		जाओ out;
	अगर (!page_mapped(page))
		जाओ out;

	anon_vma = (काष्ठा anon_vma *) (anon_mapping - PAGE_MAPPING_ANON);
	root_anon_vma = READ_ONCE(anon_vma->root);
	अगर (करोwn_पढ़ो_trylock(&root_anon_vma->rwsem)) अणु
		/*
		 * If the page is still mapped, then this anon_vma is still
		 * its anon_vma, and holding the mutex ensures that it will
		 * not go away, see anon_vma_मुक्त().
		 */
		अगर (!page_mapped(page)) अणु
			up_पढ़ो(&root_anon_vma->rwsem);
			anon_vma = शून्य;
		पूर्ण
		जाओ out;
	पूर्ण

	/* trylock failed, we got to sleep */
	अगर (!atomic_inc_not_zero(&anon_vma->refcount)) अणु
		anon_vma = शून्य;
		जाओ out;
	पूर्ण

	अगर (!page_mapped(page)) अणु
		rcu_पढ़ो_unlock();
		put_anon_vma(anon_vma);
		वापस शून्य;
	पूर्ण

	/* we pinned the anon_vma, its safe to sleep */
	rcu_पढ़ो_unlock();
	anon_vma_lock_पढ़ो(anon_vma);

	अगर (atomic_dec_and_test(&anon_vma->refcount)) अणु
		/*
		 * Oops, we held the last refcount, release the lock
		 * and bail -- can't simply use put_anon_vma() because
		 * we'll deadlock on the anon_vma_lock_ग_लिखो() recursion.
		 */
		anon_vma_unlock_पढ़ो(anon_vma);
		__put_anon_vma(anon_vma);
		anon_vma = शून्य;
	पूर्ण

	वापस anon_vma;

out:
	rcu_पढ़ो_unlock();
	वापस anon_vma;
पूर्ण

व्योम page_unlock_anon_vma_पढ़ो(काष्ठा anon_vma *anon_vma)
अणु
	anon_vma_unlock_पढ़ो(anon_vma);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH
/*
 * Flush TLB entries क्रम recently unmapped pages from remote CPUs. It is
 * important अगर a PTE was dirty when it was unmapped that it's flushed
 * beक्रमe any IO is initiated on the page to prevent lost ग_लिखोs. Similarly,
 * it must be flushed beक्रमe मुक्तing to prevent data leakage.
 */
व्योम try_to_unmap_flush(व्योम)
अणु
	काष्ठा tlbflush_unmap_batch *tlb_ubc = &current->tlb_ubc;

	अगर (!tlb_ubc->flush_required)
		वापस;

	arch_tlbbatch_flush(&tlb_ubc->arch);
	tlb_ubc->flush_required = false;
	tlb_ubc->writable = false;
पूर्ण

/* Flush अगरf there are potentially writable TLB entries that can race with IO */
व्योम try_to_unmap_flush_dirty(व्योम)
अणु
	काष्ठा tlbflush_unmap_batch *tlb_ubc = &current->tlb_ubc;

	अगर (tlb_ubc->writable)
		try_to_unmap_flush();
पूर्ण

अटल व्योम set_tlb_ubc_flush_pending(काष्ठा mm_काष्ठा *mm, bool writable)
अणु
	काष्ठा tlbflush_unmap_batch *tlb_ubc = &current->tlb_ubc;

	arch_tlbbatch_add_mm(&tlb_ubc->arch, mm);
	tlb_ubc->flush_required = true;

	/*
	 * Ensure compiler करोes not re-order the setting of tlb_flush_batched
	 * beक्रमe the PTE is cleared.
	 */
	barrier();
	mm->tlb_flush_batched = true;

	/*
	 * If the PTE was dirty then it's best to assume it's writable. The
	 * caller must use try_to_unmap_flush_dirty() or try_to_unmap_flush()
	 * beक्रमe the page is queued क्रम IO.
	 */
	अगर (writable)
		tlb_ubc->writable = true;
पूर्ण

/*
 * Returns true अगर the TLB flush should be deferred to the end of a batch of
 * unmap operations to reduce IPIs.
 */
अटल bool should_defer_flush(काष्ठा mm_काष्ठा *mm, क्रमागत ttu_flags flags)
अणु
	bool should_defer = false;

	अगर (!(flags & TTU_BATCH_FLUSH))
		वापस false;

	/* If remote CPUs need to be flushed then defer batch the flush */
	अगर (cpumask_any_but(mm_cpumask(mm), get_cpu()) < nr_cpu_ids)
		should_defer = true;
	put_cpu();

	वापस should_defer;
पूर्ण

/*
 * Reclaim unmaps pages under the PTL but करो not flush the TLB prior to
 * releasing the PTL अगर TLB flushes are batched. It's possible क्रम a parallel
 * operation such as mprotect or munmap to race between reclaim unmapping
 * the page and flushing the page. If this race occurs, it potentially allows
 * access to data via a stale TLB entry. Tracking all mm's that have TLB
 * batching in flight would be expensive during reclaim so instead track
 * whether TLB batching occurred in the past and अगर so then करो a flush here
 * अगर required. This will cost one additional flush per reclaim cycle paid
 * by the first operation at risk such as mprotect and mumap.
 *
 * This must be called under the PTL so that an access to tlb_flush_batched
 * that is potentially a "reclaim vs mprotect/munmap/etc" race will synchronise
 * via the PTL.
 */
व्योम flush_tlb_batched_pending(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (data_race(mm->tlb_flush_batched)) अणु
		flush_tlb_mm(mm);

		/*
		 * Do not allow the compiler to re-order the clearing of
		 * tlb_flush_batched beक्रमe the tlb is flushed.
		 */
		barrier();
		mm->tlb_flush_batched = false;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम set_tlb_ubc_flush_pending(काष्ठा mm_काष्ठा *mm, bool writable)
अणु
पूर्ण

अटल bool should_defer_flush(काष्ठा mm_काष्ठा *mm, क्रमागत ttu_flags flags)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH */

/*
 * At what user भव address is page expected in vma?
 * Caller should check the page is actually part of the vma.
 */
अचिन्हित दीर्घ page_address_in_vma(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (PageAnon(page)) अणु
		काष्ठा anon_vma *page__anon_vma = page_anon_vma(page);
		/*
		 * Note: swapoff's unuse_vma() is more efficient with this
		 * check, and needs it to match anon_vma when KSM is active.
		 */
		अगर (!vma->anon_vma || !page__anon_vma ||
		    vma->anon_vma->root != page__anon_vma->root)
			वापस -EFAULT;
	पूर्ण अन्यथा अगर (!vma->vm_file) अणु
		वापस -EFAULT;
	पूर्ण अन्यथा अगर (vma->vm_file->f_mapping != compound_head(page)->mapping) अणु
		वापस -EFAULT;
	पूर्ण

	वापस vma_address(page, vma);
पूर्ण

pmd_t *mm_find_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd = शून्य;
	pmd_t pmde;

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
	 * Some THP functions use the sequence pmdp_huge_clear_flush(), set_pmd_at()
	 * without holding anon_vma lock क्रम ग_लिखो.  So when looking क्रम a
	 * genuine pmde (in which to find pte), test present and !THP together.
	 */
	pmde = *pmd;
	barrier();
	अगर (!pmd_present(pmde) || pmd_trans_huge(pmde))
		pmd = शून्य;
out:
	वापस pmd;
पूर्ण

काष्ठा page_referenced_arg अणु
	पूर्णांक mapcount;
	पूर्णांक referenced;
	अचिन्हित दीर्घ vm_flags;
	काष्ठा mem_cgroup *memcg;
पूर्ण;
/*
 * arg: page_referenced_arg will be passed
 */
अटल bool page_referenced_one(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ address, व्योम *arg)
अणु
	काष्ठा page_referenced_arg *pra = arg;
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = page,
		.vma = vma,
		.address = address,
	पूर्ण;
	पूर्णांक referenced = 0;

	जबतक (page_vma_mapped_walk(&pvmw)) अणु
		address = pvmw.address;

		अगर (vma->vm_flags & VM_LOCKED) अणु
			page_vma_mapped_walk_करोne(&pvmw);
			pra->vm_flags |= VM_LOCKED;
			वापस false; /* To अवरोध the loop */
		पूर्ण

		अगर (pvmw.pte) अणु
			अगर (ptep_clear_flush_young_notअगरy(vma, address,
						pvmw.pte)) अणु
				/*
				 * Don't treat a reference through
				 * a sequentially पढ़ो mapping as such.
				 * If the page has been used in another mapping,
				 * we will catch it; अगर this other mapping is
				 * alपढ़ोy gone, the unmap path will have set
				 * PG_referenced or activated the page.
				 */
				अगर (likely(!(vma->vm_flags & VM_SEQ_READ)))
					referenced++;
			पूर्ण
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) अणु
			अगर (pmdp_clear_flush_young_notअगरy(vma, address,
						pvmw.pmd))
				referenced++;
		पूर्ण अन्यथा अणु
			/* unexpected pmd-mapped page? */
			WARN_ON_ONCE(1);
		पूर्ण

		pra->mapcount--;
	पूर्ण

	अगर (referenced)
		clear_page_idle(page);
	अगर (test_and_clear_page_young(page))
		referenced++;

	अगर (referenced) अणु
		pra->referenced++;
		pra->vm_flags |= vma->vm_flags;
	पूर्ण

	अगर (!pra->mapcount)
		वापस false; /* To अवरोध the loop */

	वापस true;
पूर्ण

अटल bool invalid_page_referenced_vma(काष्ठा vm_area_काष्ठा *vma, व्योम *arg)
अणु
	काष्ठा page_referenced_arg *pra = arg;
	काष्ठा mem_cgroup *memcg = pra->memcg;

	अगर (!mm_match_cgroup(vma->vm_mm, memcg))
		वापस true;

	वापस false;
पूर्ण

/**
 * page_referenced - test अगर the page was referenced
 * @page: the page to test
 * @is_locked: caller holds lock on the page
 * @memcg: target memory cgroup
 * @vm_flags: collect encountered vma->vm_flags who actually referenced the page
 *
 * Quick test_and_clear_referenced क्रम all mappings to a page,
 * वापसs the number of ptes which referenced the page.
 */
पूर्णांक page_referenced(काष्ठा page *page,
		    पूर्णांक is_locked,
		    काष्ठा mem_cgroup *memcg,
		    अचिन्हित दीर्घ *vm_flags)
अणु
	पूर्णांक we_locked = 0;
	काष्ठा page_referenced_arg pra = अणु
		.mapcount = total_mapcount(page),
		.memcg = memcg,
	पूर्ण;
	काष्ठा rmap_walk_control rwc = अणु
		.rmap_one = page_referenced_one,
		.arg = (व्योम *)&pra,
		.anon_lock = page_lock_anon_vma_पढ़ो,
	पूर्ण;

	*vm_flags = 0;
	अगर (!pra.mapcount)
		वापस 0;

	अगर (!page_rmapping(page))
		वापस 0;

	अगर (!is_locked && (!PageAnon(page) || PageKsm(page))) अणु
		we_locked = trylock_page(page);
		अगर (!we_locked)
			वापस 1;
	पूर्ण

	/*
	 * If we are reclaiming on behalf of a cgroup, skip
	 * counting on behalf of references from dअगरferent
	 * cgroups
	 */
	अगर (memcg) अणु
		rwc.invalid_vma = invalid_page_referenced_vma;
	पूर्ण

	rmap_walk(page, &rwc);
	*vm_flags = pra.vm_flags;

	अगर (we_locked)
		unlock_page(page);

	वापस pra.referenced;
पूर्ण

अटल bool page_mkclean_one(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ address, व्योम *arg)
अणु
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = page,
		.vma = vma,
		.address = address,
		.flags = PVMW_SYNC,
	पूर्ण;
	काष्ठा mmu_notअगरier_range range;
	पूर्णांक *cleaned = arg;

	/*
	 * We have to assume the worse हाल ie pmd क्रम invalidation. Note that
	 * the page can not be मुक्त from this function.
	 */
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_PROTECTION_PAGE,
				0, vma, vma->vm_mm, address,
				vma_address_end(page, vma));
	mmu_notअगरier_invalidate_range_start(&range);

	जबतक (page_vma_mapped_walk(&pvmw)) अणु
		पूर्णांक ret = 0;

		address = pvmw.address;
		अगर (pvmw.pte) अणु
			pte_t entry;
			pte_t *pte = pvmw.pte;

			अगर (!pte_dirty(*pte) && !pte_ग_लिखो(*pte))
				जारी;

			flush_cache_page(vma, address, pte_pfn(*pte));
			entry = ptep_clear_flush(vma, address, pte);
			entry = pte_wrprotect(entry);
			entry = pte_mkclean(entry);
			set_pte_at(vma->vm_mm, address, pte, entry);
			ret = 1;
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
			pmd_t *pmd = pvmw.pmd;
			pmd_t entry;

			अगर (!pmd_dirty(*pmd) && !pmd_ग_लिखो(*pmd))
				जारी;

			flush_cache_page(vma, address, page_to_pfn(page));
			entry = pmdp_invalidate(vma, address, pmd);
			entry = pmd_wrprotect(entry);
			entry = pmd_mkclean(entry);
			set_pmd_at(vma->vm_mm, address, pmd, entry);
			ret = 1;
#अन्यथा
			/* unexpected pmd-mapped page? */
			WARN_ON_ONCE(1);
#पूर्ण_अगर
		पूर्ण

		/*
		 * No need to call mmu_notअगरier_invalidate_range() as we are
		 * करोwngrading page table protection not changing it to poपूर्णांक
		 * to a new page.
		 *
		 * See Documentation/vm/mmu_notअगरier.rst
		 */
		अगर (ret)
			(*cleaned)++;
	पूर्ण

	mmu_notअगरier_invalidate_range_end(&range);

	वापस true;
पूर्ण

अटल bool invalid_mkclean_vma(काष्ठा vm_area_काष्ठा *vma, व्योम *arg)
अणु
	अगर (vma->vm_flags & VM_SHARED)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक page_mkclean(काष्ठा page *page)
अणु
	पूर्णांक cleaned = 0;
	काष्ठा address_space *mapping;
	काष्ठा rmap_walk_control rwc = अणु
		.arg = (व्योम *)&cleaned,
		.rmap_one = page_mkclean_one,
		.invalid_vma = invalid_mkclean_vma,
	पूर्ण;

	BUG_ON(!PageLocked(page));

	अगर (!page_mapped(page))
		वापस 0;

	mapping = page_mapping(page);
	अगर (!mapping)
		वापस 0;

	rmap_walk(page, &rwc);

	वापस cleaned;
पूर्ण
EXPORT_SYMBOL_GPL(page_mkclean);

/**
 * page_move_anon_rmap - move a page to our anon_vma
 * @page:	the page to move to our anon_vma
 * @vma:	the vma the page beदीर्घs to
 *
 * When a page beदीर्घs exclusively to one process after a COW event,
 * that page can be moved पूर्णांकo the anon_vma that beदीर्घs to just that
 * process, so the rmap code will not search the parent or sibling
 * processes.
 */
व्योम page_move_anon_rmap(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा anon_vma *anon_vma = vma->anon_vma;

	page = compound_head(page);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_VMA(!anon_vma, vma);

	anon_vma = (व्योम *) anon_vma + PAGE_MAPPING_ANON;
	/*
	 * Ensure that anon_vma and the PAGE_MAPPING_ANON bit are written
	 * simultaneously, so a concurrent पढ़ोer (eg page_referenced()'s
	 * PageAnon()) will not see one without the other.
	 */
	WRITE_ONCE(page->mapping, (काष्ठा address_space *) anon_vma);
पूर्ण

/**
 * __page_set_anon_rmap - set up new anonymous rmap
 * @page:	Page or Hugepage to add to rmap
 * @vma:	VM area to add page to.
 * @address:	User भव address of the mapping	
 * @exclusive:	the page is exclusively owned by the current process
 */
अटल व्योम __page_set_anon_rmap(काष्ठा page *page,
	काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, पूर्णांक exclusive)
अणु
	काष्ठा anon_vma *anon_vma = vma->anon_vma;

	BUG_ON(!anon_vma);

	अगर (PageAnon(page))
		वापस;

	/*
	 * If the page isn't exclusively mapped पूर्णांकo this vma,
	 * we must use the _oldest_ possible anon_vma क्रम the
	 * page mapping!
	 */
	अगर (!exclusive)
		anon_vma = anon_vma->root;

	/*
	 * page_idle करोes a lockless/optimistic rmap scan on page->mapping.
	 * Make sure the compiler करोesn't split the stores of anon_vma and
	 * the PAGE_MAPPING_ANON type identअगरier, otherwise the rmap code
	 * could mistake the mapping क्रम a काष्ठा address_space and crash.
	 */
	anon_vma = (व्योम *) anon_vma + PAGE_MAPPING_ANON;
	WRITE_ONCE(page->mapping, (काष्ठा address_space *) anon_vma);
	page->index = linear_page_index(vma, address);
पूर्ण

/**
 * __page_check_anon_rmap - sanity check anonymous rmap addition
 * @page:	the page to add the mapping to
 * @vma:	the vm area in which the mapping is added
 * @address:	the user भव address mapped
 */
अटल व्योम __page_check_anon_rmap(काष्ठा page *page,
	काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	/*
	 * The page's anon-rmap details (mapping and index) are guaranteed to
	 * be set up correctly at this poपूर्णांक.
	 *
	 * We have exclusion against page_add_anon_rmap because the caller
	 * always holds the page locked.
	 *
	 * We have exclusion against page_add_new_anon_rmap because those pages
	 * are initially only visible via the pagetables, and the pte is locked
	 * over the call to page_add_new_anon_rmap.
	 */
	VM_BUG_ON_PAGE(page_anon_vma(page)->root != vma->anon_vma->root, page);
	VM_BUG_ON_PAGE(page_to_pgoff(page) != linear_page_index(vma, address),
		       page);
पूर्ण

/**
 * page_add_anon_rmap - add pte mapping to an anonymous page
 * @page:	the page to add the mapping to
 * @vma:	the vm area in which the mapping is added
 * @address:	the user भव address mapped
 * @compound:	अक्षरge the page as compound or small page
 *
 * The caller needs to hold the pte lock, and the page must be locked in
 * the anon_vma हाल: to serialize mapping,index checking after setting,
 * and to ensure that PageAnon is not being upgraded racily to PageKsm
 * (but PageKsm is never करोwngraded to PageAnon).
 */
व्योम page_add_anon_rmap(काष्ठा page *page,
	काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, bool compound)
अणु
	करो_page_add_anon_rmap(page, vma, address, compound ? RMAP_COMPOUND : 0);
पूर्ण

/*
 * Special version of the above क्रम करो_swap_page, which often runs
 * पूर्णांकo pages that are exclusively owned by the current process.
 * Everybody अन्यथा should जारी to use page_add_anon_rmap above.
 */
व्योम करो_page_add_anon_rmap(काष्ठा page *page,
	काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, पूर्णांक flags)
अणु
	bool compound = flags & RMAP_COMPOUND;
	bool first;

	अगर (unlikely(PageKsm(page)))
		lock_page_memcg(page);
	अन्यथा
		VM_BUG_ON_PAGE(!PageLocked(page), page);

	अगर (compound) अणु
		atomic_t *mapcount;
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		VM_BUG_ON_PAGE(!PageTransHuge(page), page);
		mapcount = compound_mapcount_ptr(page);
		first = atomic_inc_and_test(mapcount);
	पूर्ण अन्यथा अणु
		first = atomic_inc_and_test(&page->_mapcount);
	पूर्ण

	अगर (first) अणु
		पूर्णांक nr = compound ? thp_nr_pages(page) : 1;
		/*
		 * We use the irq-unsafe __अणुinc|modपूर्ण_zone_page_stat because
		 * these counters are not modअगरied in पूर्णांकerrupt context, and
		 * pte lock(a spinlock) is held, which implies preemption
		 * disabled.
		 */
		अगर (compound)
			__mod_lruvec_page_state(page, NR_ANON_THPS, nr);
		__mod_lruvec_page_state(page, NR_ANON_MAPPED, nr);
	पूर्ण

	अगर (unlikely(PageKsm(page))) अणु
		unlock_page_memcg(page);
		वापस;
	पूर्ण

	/* address might be in next vma when migration races vma_adjust */
	अगर (first)
		__page_set_anon_rmap(page, vma, address,
				flags & RMAP_EXCLUSIVE);
	अन्यथा
		__page_check_anon_rmap(page, vma, address);
पूर्ण

/**
 * page_add_new_anon_rmap - add pte mapping to a new anonymous page
 * @page:	the page to add the mapping to
 * @vma:	the vm area in which the mapping is added
 * @address:	the user भव address mapped
 * @compound:	अक्षरge the page as compound or small page
 *
 * Same as page_add_anon_rmap but must only be called on *new* pages.
 * This means the inc-and-test can be bypassed.
 * Page करोes not have to be locked.
 */
व्योम page_add_new_anon_rmap(काष्ठा page *page,
	काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, bool compound)
अणु
	पूर्णांक nr = compound ? thp_nr_pages(page) : 1;

	VM_BUG_ON_VMA(address < vma->vm_start || address >= vma->vm_end, vma);
	__SetPageSwapBacked(page);
	अगर (compound) अणु
		VM_BUG_ON_PAGE(!PageTransHuge(page), page);
		/* increment count (starts at -1) */
		atomic_set(compound_mapcount_ptr(page), 0);
		अगर (hpage_pincount_available(page))
			atomic_set(compound_pincount_ptr(page), 0);

		__mod_lruvec_page_state(page, NR_ANON_THPS, nr);
	पूर्ण अन्यथा अणु
		/* Anon THP always mapped first with PMD */
		VM_BUG_ON_PAGE(PageTransCompound(page), page);
		/* increment count (starts at -1) */
		atomic_set(&page->_mapcount, 0);
	पूर्ण
	__mod_lruvec_page_state(page, NR_ANON_MAPPED, nr);
	__page_set_anon_rmap(page, vma, address, 1);
पूर्ण

/**
 * page_add_file_rmap - add pte mapping to a file page
 * @page: the page to add the mapping to
 * @compound: अक्षरge the page as compound or small page
 *
 * The caller needs to hold the pte lock.
 */
व्योम page_add_file_rmap(काष्ठा page *page, bool compound)
अणु
	पूर्णांक i, nr = 1;

	VM_BUG_ON_PAGE(compound && !PageTransHuge(page), page);
	lock_page_memcg(page);
	अगर (compound && PageTransHuge(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		क्रम (i = 0, nr = 0; i < nr_pages; i++) अणु
			अगर (atomic_inc_and_test(&page[i]._mapcount))
				nr++;
		पूर्ण
		अगर (!atomic_inc_and_test(compound_mapcount_ptr(page)))
			जाओ out;
		अगर (PageSwapBacked(page))
			__mod_lruvec_page_state(page, NR_SHMEM_PMDMAPPED,
						nr_pages);
		अन्यथा
			__mod_lruvec_page_state(page, NR_खाता_PMDMAPPED,
						nr_pages);
	पूर्ण अन्यथा अणु
		अगर (PageTransCompound(page) && page_mapping(page)) अणु
			VM_WARN_ON_ONCE(!PageLocked(page));

			SetPageDoubleMap(compound_head(page));
			अगर (PageMlocked(page))
				clear_page_mlock(compound_head(page));
		पूर्ण
		अगर (!atomic_inc_and_test(&page->_mapcount))
			जाओ out;
	पूर्ण
	__mod_lruvec_page_state(page, NR_खाता_MAPPED, nr);
out:
	unlock_page_memcg(page);
पूर्ण

अटल व्योम page_हटाओ_file_rmap(काष्ठा page *page, bool compound)
अणु
	पूर्णांक i, nr = 1;

	VM_BUG_ON_PAGE(compound && !PageHead(page), page);

	/* Hugepages are not counted in NR_खाता_MAPPED क्रम now. */
	अगर (unlikely(PageHuge(page))) अणु
		/* hugetlb pages are always mapped with pmds */
		atomic_dec(compound_mapcount_ptr(page));
		वापस;
	पूर्ण

	/* page still mapped by someone अन्यथा? */
	अगर (compound && PageTransHuge(page)) अणु
		पूर्णांक nr_pages = thp_nr_pages(page);

		क्रम (i = 0, nr = 0; i < nr_pages; i++) अणु
			अगर (atomic_add_negative(-1, &page[i]._mapcount))
				nr++;
		पूर्ण
		अगर (!atomic_add_negative(-1, compound_mapcount_ptr(page)))
			वापस;
		अगर (PageSwapBacked(page))
			__mod_lruvec_page_state(page, NR_SHMEM_PMDMAPPED,
						-nr_pages);
		अन्यथा
			__mod_lruvec_page_state(page, NR_खाता_PMDMAPPED,
						-nr_pages);
	पूर्ण अन्यथा अणु
		अगर (!atomic_add_negative(-1, &page->_mapcount))
			वापस;
	पूर्ण

	/*
	 * We use the irq-unsafe __अणुinc|modपूर्ण_lruvec_page_state because
	 * these counters are not modअगरied in पूर्णांकerrupt context, and
	 * pte lock(a spinlock) is held, which implies preemption disabled.
	 */
	__mod_lruvec_page_state(page, NR_खाता_MAPPED, -nr);

	अगर (unlikely(PageMlocked(page)))
		clear_page_mlock(page);
पूर्ण

अटल व्योम page_हटाओ_anon_compound_rmap(काष्ठा page *page)
अणु
	पूर्णांक i, nr;

	अगर (!atomic_add_negative(-1, compound_mapcount_ptr(page)))
		वापस;

	/* Hugepages are not counted in NR_ANON_PAGES क्रम now. */
	अगर (unlikely(PageHuge(page)))
		वापस;

	अगर (!IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE))
		वापस;

	__mod_lruvec_page_state(page, NR_ANON_THPS, -thp_nr_pages(page));

	अगर (TestClearPageDoubleMap(page)) अणु
		/*
		 * Subpages can be mapped with PTEs too. Check how many of
		 * them are still mapped.
		 */
		क्रम (i = 0, nr = 0; i < thp_nr_pages(page); i++) अणु
			अगर (atomic_add_negative(-1, &page[i]._mapcount))
				nr++;
		पूर्ण

		/*
		 * Queue the page क्रम deferred split अगर at least one small
		 * page of the compound page is unmapped, but at least one
		 * small page is still mapped.
		 */
		अगर (nr && nr < thp_nr_pages(page))
			deferred_split_huge_page(page);
	पूर्ण अन्यथा अणु
		nr = thp_nr_pages(page);
	पूर्ण

	अगर (unlikely(PageMlocked(page)))
		clear_page_mlock(page);

	अगर (nr)
		__mod_lruvec_page_state(page, NR_ANON_MAPPED, -nr);
पूर्ण

/**
 * page_हटाओ_rmap - take करोwn pte mapping from a page
 * @page:	page to हटाओ mapping from
 * @compound:	unअक्षरge the page as compound or small page
 *
 * The caller needs to hold the pte lock.
 */
व्योम page_हटाओ_rmap(काष्ठा page *page, bool compound)
अणु
	lock_page_memcg(page);

	अगर (!PageAnon(page)) अणु
		page_हटाओ_file_rmap(page, compound);
		जाओ out;
	पूर्ण

	अगर (compound) अणु
		page_हटाओ_anon_compound_rmap(page);
		जाओ out;
	पूर्ण

	/* page still mapped by someone अन्यथा? */
	अगर (!atomic_add_negative(-1, &page->_mapcount))
		जाओ out;

	/*
	 * We use the irq-unsafe __अणुinc|modपूर्ण_zone_page_stat because
	 * these counters are not modअगरied in पूर्णांकerrupt context, and
	 * pte lock(a spinlock) is held, which implies preemption disabled.
	 */
	__dec_lruvec_page_state(page, NR_ANON_MAPPED);

	अगर (unlikely(PageMlocked(page)))
		clear_page_mlock(page);

	अगर (PageTransCompound(page))
		deferred_split_huge_page(compound_head(page));

	/*
	 * It would be tidy to reset the PageAnon mapping here,
	 * but that might overग_लिखो a racing page_add_anon_rmap
	 * which increments mapcount after us but sets mapping
	 * beक्रमe us: so leave the reset to मुक्त_unref_page,
	 * and remember that it's only reliable जबतक mapped.
	 * Leaving it set also helps swapoff to reinstate ptes
	 * faster क्रम those pages still in swapcache.
	 */
out:
	unlock_page_memcg(page);
पूर्ण

/*
 * @arg: क्रमागत ttu_flags will be passed to this argument
 */
अटल bool try_to_unmap_one(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ address, व्योम *arg)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = page,
		.vma = vma,
		.address = address,
	पूर्ण;
	pte_t pteval;
	काष्ठा page *subpage;
	bool ret = true;
	काष्ठा mmu_notअगरier_range range;
	क्रमागत ttu_flags flags = (क्रमागत ttu_flags)(दीर्घ)arg;

	/*
	 * When racing against e.g. zap_pte_range() on another cpu,
	 * in between its ptep_get_and_clear_full() and page_हटाओ_rmap(),
	 * try_to_unmap() may वापस false when it is about to become true,
	 * अगर page table locking is skipped: use TTU_SYNC to रुको क्रम that.
	 */
	अगर (flags & TTU_SYNC)
		pvmw.flags = PVMW_SYNC;

	/* munlock has nothing to gain from examining un-locked vmas */
	अगर ((flags & TTU_MUNLOCK) && !(vma->vm_flags & VM_LOCKED))
		वापस true;

	अगर (IS_ENABLED(CONFIG_MIGRATION) && (flags & TTU_MIGRATION) &&
	    is_zone_device_page(page) && !is_device_निजी_page(page))
		वापस true;

	अगर (flags & TTU_SPLIT_HUGE_PMD) अणु
		split_huge_pmd_address(vma, address,
				flags & TTU_SPLIT_FREEZE, page);
	पूर्ण

	/*
	 * For THP, we have to assume the worse हाल ie pmd क्रम invalidation.
	 * For hugetlb, it could be much worse अगर we need to करो pud
	 * invalidation in the हाल of pmd sharing.
	 *
	 * Note that the page can not be मुक्त in this function as call of
	 * try_to_unmap() must hold a reference on the page.
	 */
	range.end = PageKsm(page) ?
			address + PAGE_SIZE : vma_address_end(page, vma);
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address, range.end);
	अगर (PageHuge(page)) अणु
		/*
		 * If sharing is possible, start and end will be adjusted
		 * accordingly.
		 */
		adjust_range_अगर_pmd_sharing_possible(vma, &range.start,
						     &range.end);
	पूर्ण
	mmu_notअगरier_invalidate_range_start(&range);

	जबतक (page_vma_mapped_walk(&pvmw)) अणु
#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
		/* PMD-mapped THP migration entry */
		अगर (!pvmw.pte && (flags & TTU_MIGRATION)) अणु
			VM_BUG_ON_PAGE(PageHuge(page) || !PageTransCompound(page), page);

			set_pmd_migration_entry(&pvmw, page);
			जारी;
		पूर्ण
#पूर्ण_अगर

		/*
		 * If the page is mlock()d, we cannot swap it out.
		 * If it's recently referenced (perhaps page_referenced
		 * skipped over this mm) then we should reactivate it.
		 */
		अगर (!(flags & TTU_IGNORE_MLOCK)) अणु
			अगर (vma->vm_flags & VM_LOCKED) अणु
				/* PTE-mapped THP are never mlocked */
				अगर (!PageTransCompound(page)) अणु
					/*
					 * Holding pte lock, we करो *not* need
					 * mmap_lock here
					 */
					mlock_vma_page(page);
				पूर्ण
				ret = false;
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण
			अगर (flags & TTU_MUNLOCK)
				जारी;
		पूर्ण

		/* Unexpected PMD-mapped THP? */
		VM_BUG_ON_PAGE(!pvmw.pte, page);

		subpage = page - page_to_pfn(page) + pte_pfn(*pvmw.pte);
		address = pvmw.address;

		अगर (PageHuge(page) && !PageAnon(page)) अणु
			/*
			 * To call huge_pmd_unshare, i_mmap_rwsem must be
			 * held in ग_लिखो mode.  Caller needs to explicitly
			 * करो this outside rmap routines.
			 */
			VM_BUG_ON(!(flags & TTU_RMAP_LOCKED));
			अगर (huge_pmd_unshare(mm, vma, &address, pvmw.pte)) अणु
				/*
				 * huge_pmd_unshare unmapped an entire PMD
				 * page.  There is no way of knowing exactly
				 * which PMDs may be cached क्रम this mm, so
				 * we must flush them all.  start/end were
				 * alपढ़ोy adjusted above to cover this range.
				 */
				flush_cache_range(vma, range.start, range.end);
				flush_tlb_range(vma, range.start, range.end);
				mmu_notअगरier_invalidate_range(mm, range.start,
							      range.end);

				/*
				 * The ref count of the PMD page was dropped
				 * which is part of the way map counting
				 * is करोne क्रम shared PMDs.  Return 'true'
				 * here.  When there is no other sharing,
				 * huge_pmd_unshare वापसs false and we will
				 * unmap the actual page and drop map count
				 * to zero.
				 */
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (IS_ENABLED(CONFIG_MIGRATION) &&
		    (flags & TTU_MIGRATION) &&
		    is_zone_device_page(page)) अणु
			swp_entry_t entry;
			pte_t swp_pte;

			pteval = ptep_get_and_clear(mm, pvmw.address, pvmw.pte);

			/*
			 * Store the pfn of the page in a special migration
			 * pte. करो_swap_page() will रुको until the migration
			 * pte is हटाओd and then restart fault handling.
			 */
			entry = make_migration_entry(page, 0);
			swp_pte = swp_entry_to_pte(entry);

			/*
			 * pteval maps a zone device page and is thereक्रमe
			 * a swap pte.
			 */
			अगर (pte_swp_soft_dirty(pteval))
				swp_pte = pte_swp_mksoft_dirty(swp_pte);
			अगर (pte_swp_uffd_wp(pteval))
				swp_pte = pte_swp_mkuffd_wp(swp_pte);
			set_pte_at(mm, pvmw.address, pvmw.pte, swp_pte);
			/*
			 * No need to invalidate here it will synchronize on
			 * against the special swap migration pte.
			 *
			 * The assignment to subpage above was computed from a
			 * swap PTE which results in an invalid poपूर्णांकer.
			 * Since only PAGE_SIZE pages can currently be
			 * migrated, just set it to page. This will need to be
			 * changed when hugepage migrations to device निजी
			 * memory are supported.
			 */
			subpage = page;
			जाओ discard;
		पूर्ण

		/* Nuke the page table entry. */
		flush_cache_page(vma, address, pte_pfn(*pvmw.pte));
		अगर (should_defer_flush(mm, flags)) अणु
			/*
			 * We clear the PTE but करो not flush so potentially
			 * a remote CPU could still be writing to the page.
			 * If the entry was previously clean then the
			 * architecture must guarantee that a clear->dirty
			 * transition on a cached TLB entry is written through
			 * and traps अगर the PTE is unmapped.
			 */
			pteval = ptep_get_and_clear(mm, address, pvmw.pte);

			set_tlb_ubc_flush_pending(mm, pte_dirty(pteval));
		पूर्ण अन्यथा अणु
			pteval = ptep_clear_flush(vma, address, pvmw.pte);
		पूर्ण

		/* Move the dirty bit to the page. Now the pte is gone. */
		अगर (pte_dirty(pteval))
			set_page_dirty(page);

		/* Update high watermark beक्रमe we lower rss */
		update_hiwater_rss(mm);

		अगर (PageHWPoison(page) && !(flags & TTU_IGNORE_HWPOISON)) अणु
			pteval = swp_entry_to_pte(make_hwpoison_entry(subpage));
			अगर (PageHuge(page)) अणु
				hugetlb_count_sub(compound_nr(page), mm);
				set_huge_swap_pte_at(mm, address,
						     pvmw.pte, pteval,
						     vma_mmu_pagesize(vma));
			पूर्ण अन्यथा अणु
				dec_mm_counter(mm, mm_counter(page));
				set_pte_at(mm, address, pvmw.pte, pteval);
			पूर्ण

		पूर्ण अन्यथा अगर (pte_unused(pteval) && !userfaultfd_armed(vma)) अणु
			/*
			 * The guest indicated that the page content is of no
			 * पूर्णांकerest anymore. Simply discard the pte, vmscan
			 * will take care of the rest.
			 * A future reference will then fault in a new zero
			 * page. When userfaultfd is active, we must not drop
			 * this page though, as its मुख्य user (postcopy
			 * migration) will not expect userfaults on alपढ़ोy
			 * copied pages.
			 */
			dec_mm_counter(mm, mm_counter(page));
			/* We have to invalidate as we cleared the pte */
			mmu_notअगरier_invalidate_range(mm, address,
						      address + PAGE_SIZE);
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_MIGRATION) &&
				(flags & (TTU_MIGRATION|TTU_SPLIT_FREEZE))) अणु
			swp_entry_t entry;
			pte_t swp_pte;

			अगर (arch_unmap_one(mm, vma, address, pteval) < 0) अणु
				set_pte_at(mm, address, pvmw.pte, pteval);
				ret = false;
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण

			/*
			 * Store the pfn of the page in a special migration
			 * pte. करो_swap_page() will रुको until the migration
			 * pte is हटाओd and then restart fault handling.
			 */
			entry = make_migration_entry(subpage,
					pte_ग_लिखो(pteval));
			swp_pte = swp_entry_to_pte(entry);
			अगर (pte_soft_dirty(pteval))
				swp_pte = pte_swp_mksoft_dirty(swp_pte);
			अगर (pte_uffd_wp(pteval))
				swp_pte = pte_swp_mkuffd_wp(swp_pte);
			set_pte_at(mm, address, pvmw.pte, swp_pte);
			/*
			 * No need to invalidate here it will synchronize on
			 * against the special swap migration pte.
			 */
		पूर्ण अन्यथा अगर (PageAnon(page)) अणु
			swp_entry_t entry = अणु .val = page_निजी(subpage) पूर्ण;
			pte_t swp_pte;
			/*
			 * Store the swap location in the pte.
			 * See handle_pte_fault() ...
			 */
			अगर (unlikely(PageSwapBacked(page) != PageSwapCache(page))) अणु
				WARN_ON_ONCE(1);
				ret = false;
				/* We have to invalidate as we cleared the pte */
				mmu_notअगरier_invalidate_range(mm, address,
							address + PAGE_SIZE);
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण

			/* MADV_FREE page check */
			अगर (!PageSwapBacked(page)) अणु
				अगर (!PageDirty(page)) अणु
					/* Invalidate as we cleared the pte */
					mmu_notअगरier_invalidate_range(mm,
						address, address + PAGE_SIZE);
					dec_mm_counter(mm, MM_ANONPAGES);
					जाओ discard;
				पूर्ण

				/*
				 * If the page was redirtied, it cannot be
				 * discarded. Remap the page to page table.
				 */
				set_pte_at(mm, address, pvmw.pte, pteval);
				SetPageSwapBacked(page);
				ret = false;
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण

			अगर (swap_duplicate(entry) < 0) अणु
				set_pte_at(mm, address, pvmw.pte, pteval);
				ret = false;
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण
			अगर (arch_unmap_one(mm, vma, address, pteval) < 0) अणु
				set_pte_at(mm, address, pvmw.pte, pteval);
				ret = false;
				page_vma_mapped_walk_करोne(&pvmw);
				अवरोध;
			पूर्ण
			अगर (list_empty(&mm->mmlist)) अणु
				spin_lock(&mmlist_lock);
				अगर (list_empty(&mm->mmlist))
					list_add(&mm->mmlist, &init_mm.mmlist);
				spin_unlock(&mmlist_lock);
			पूर्ण
			dec_mm_counter(mm, MM_ANONPAGES);
			inc_mm_counter(mm, MM_SWAPENTS);
			swp_pte = swp_entry_to_pte(entry);
			अगर (pte_soft_dirty(pteval))
				swp_pte = pte_swp_mksoft_dirty(swp_pte);
			अगर (pte_uffd_wp(pteval))
				swp_pte = pte_swp_mkuffd_wp(swp_pte);
			set_pte_at(mm, address, pvmw.pte, swp_pte);
			/* Invalidate as we cleared the pte */
			mmu_notअगरier_invalidate_range(mm, address,
						      address + PAGE_SIZE);
		पूर्ण अन्यथा अणु
			/*
			 * This is a locked file-backed page, thus it cannot
			 * be हटाओd from the page cache and replaced by a new
			 * page beक्रमe mmu_notअगरier_invalidate_range_end, so no
			 * concurrent thपढ़ो might update its page table to
			 * poपूर्णांक at new page जबतक a device still is using this
			 * page.
			 *
			 * See Documentation/vm/mmu_notअगरier.rst
			 */
			dec_mm_counter(mm, mm_counter_file(page));
		पूर्ण
discard:
		/*
		 * No need to call mmu_notअगरier_invalidate_range() it has be
		 * करोne above क्रम all हालs requiring it to happen under page
		 * table lock beक्रमe mmu_notअगरier_invalidate_range_end()
		 *
		 * See Documentation/vm/mmu_notअगरier.rst
		 */
		page_हटाओ_rmap(subpage, PageHuge(page));
		put_page(page);
	पूर्ण

	mmu_notअगरier_invalidate_range_end(&range);

	वापस ret;
पूर्ण

अटल bool invalid_migration_vma(काष्ठा vm_area_काष्ठा *vma, व्योम *arg)
अणु
	वापस vma_is_temporary_stack(vma);
पूर्ण

अटल पूर्णांक page_not_mapped(काष्ठा page *page)
अणु
	वापस !page_mapped(page);
पूर्ण

/**
 * try_to_unmap - try to हटाओ all page table mappings to a page
 * @page: the page to get unmapped
 * @flags: action and flags
 *
 * Tries to हटाओ all the page table entries which are mapping this
 * page, used in the pageout path.  Caller must hold the page lock.
 *
 * If unmap is successful, वापस true. Otherwise, false.
 */
bool try_to_unmap(काष्ठा page *page, क्रमागत ttu_flags flags)
अणु
	काष्ठा rmap_walk_control rwc = अणु
		.rmap_one = try_to_unmap_one,
		.arg = (व्योम *)flags,
		.करोne = page_not_mapped,
		.anon_lock = page_lock_anon_vma_पढ़ो,
	पूर्ण;

	/*
	 * During exec, a temporary VMA is setup and later moved.
	 * The VMA is moved under the anon_vma lock but not the
	 * page tables leading to a race where migration cannot
	 * find the migration ptes. Rather than increasing the
	 * locking requirements of exec(), migration skips
	 * temporary VMAs until after exec() completes.
	 */
	अगर ((flags & (TTU_MIGRATION|TTU_SPLIT_FREEZE))
	    && !PageKsm(page) && PageAnon(page))
		rwc.invalid_vma = invalid_migration_vma;

	अगर (flags & TTU_RMAP_LOCKED)
		rmap_walk_locked(page, &rwc);
	अन्यथा
		rmap_walk(page, &rwc);

	/*
	 * When racing against e.g. zap_pte_range() on another cpu,
	 * in between its ptep_get_and_clear_full() and page_हटाओ_rmap(),
	 * try_to_unmap() may वापस false when it is about to become true,
	 * अगर page table locking is skipped: use TTU_SYNC to रुको क्रम that.
	 */
	वापस !page_mapcount(page);
पूर्ण

/**
 * try_to_munlock - try to munlock a page
 * @page: the page to be munlocked
 *
 * Called from munlock code.  Checks all of the VMAs mapping the page
 * to make sure nobody अन्यथा has this page mlocked. The page will be
 * वापसed with PG_mlocked cleared अगर no other vmas have it mlocked.
 */

व्योम try_to_munlock(काष्ठा page *page)
अणु
	काष्ठा rmap_walk_control rwc = अणु
		.rmap_one = try_to_unmap_one,
		.arg = (व्योम *)TTU_MUNLOCK,
		.करोne = page_not_mapped,
		.anon_lock = page_lock_anon_vma_पढ़ो,

	पूर्ण;

	VM_BUG_ON_PAGE(!PageLocked(page) || PageLRU(page), page);
	VM_BUG_ON_PAGE(PageCompound(page) && PageDoubleMap(page), page);

	rmap_walk(page, &rwc);
पूर्ण

व्योम __put_anon_vma(काष्ठा anon_vma *anon_vma)
अणु
	काष्ठा anon_vma *root = anon_vma->root;

	anon_vma_मुक्त(anon_vma);
	अगर (root != anon_vma && atomic_dec_and_test(&root->refcount))
		anon_vma_मुक्त(root);
पूर्ण

अटल काष्ठा anon_vma *rmap_walk_anon_lock(काष्ठा page *page,
					काष्ठा rmap_walk_control *rwc)
अणु
	काष्ठा anon_vma *anon_vma;

	अगर (rwc->anon_lock)
		वापस rwc->anon_lock(page);

	/*
	 * Note: हटाओ_migration_ptes() cannot use page_lock_anon_vma_पढ़ो()
	 * because that depends on page_mapped(); but not all its usages
	 * are holding mmap_lock. Users without mmap_lock are required to
	 * take a reference count to prevent the anon_vma disappearing
	 */
	anon_vma = page_anon_vma(page);
	अगर (!anon_vma)
		वापस शून्य;

	anon_vma_lock_पढ़ो(anon_vma);
	वापस anon_vma;
पूर्ण

/*
 * rmap_walk_anon - करो something to anonymous page using the object-based
 * rmap method
 * @page: the page to be handled
 * @rwc: control variable according to each walk type
 *
 * Find all the mappings of a page using the mapping poपूर्णांकer and the vma chains
 * contained in the anon_vma काष्ठा it poपूर्णांकs to.
 *
 * When called from try_to_munlock(), the mmap_lock of the mm containing the vma
 * where the page was found will be held क्रम ग_लिखो.  So, we won't recheck
 * vm_flags क्रम that VMA.  That should be OK, because that vma shouldn't be
 * LOCKED.
 */
अटल व्योम rmap_walk_anon(काष्ठा page *page, काष्ठा rmap_walk_control *rwc,
		bool locked)
अणु
	काष्ठा anon_vma *anon_vma;
	pgoff_t pgoff_start, pgoff_end;
	काष्ठा anon_vma_chain *avc;

	अगर (locked) अणु
		anon_vma = page_anon_vma(page);
		/* anon_vma disappear under us? */
		VM_BUG_ON_PAGE(!anon_vma, page);
	पूर्ण अन्यथा अणु
		anon_vma = rmap_walk_anon_lock(page, rwc);
	पूर्ण
	अगर (!anon_vma)
		वापस;

	pgoff_start = page_to_pgoff(page);
	pgoff_end = pgoff_start + thp_nr_pages(page) - 1;
	anon_vma_पूर्णांकerval_tree_क्रमeach(avc, &anon_vma->rb_root,
			pgoff_start, pgoff_end) अणु
		काष्ठा vm_area_काष्ठा *vma = avc->vma;
		अचिन्हित दीर्घ address = vma_address(page, vma);

		VM_BUG_ON_VMA(address == -EFAULT, vma);
		cond_resched();

		अगर (rwc->invalid_vma && rwc->invalid_vma(vma, rwc->arg))
			जारी;

		अगर (!rwc->rmap_one(page, vma, address, rwc->arg))
			अवरोध;
		अगर (rwc->करोne && rwc->करोne(page))
			अवरोध;
	पूर्ण

	अगर (!locked)
		anon_vma_unlock_पढ़ो(anon_vma);
पूर्ण

/*
 * rmap_walk_file - करो something to file page using the object-based rmap method
 * @page: the page to be handled
 * @rwc: control variable according to each walk type
 *
 * Find all the mappings of a page using the mapping poपूर्णांकer and the vma chains
 * contained in the address_space काष्ठा it poपूर्णांकs to.
 *
 * When called from try_to_munlock(), the mmap_lock of the mm containing the vma
 * where the page was found will be held क्रम ग_लिखो.  So, we won't recheck
 * vm_flags क्रम that VMA.  That should be OK, because that vma shouldn't be
 * LOCKED.
 */
अटल व्योम rmap_walk_file(काष्ठा page *page, काष्ठा rmap_walk_control *rwc,
		bool locked)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	pgoff_t pgoff_start, pgoff_end;
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * The page lock not only makes sure that page->mapping cannot
	 * suddenly be शून्यअगरied by truncation, it makes sure that the
	 * काष्ठाure at mapping cannot be मुक्तd and reused yet,
	 * so we can safely take mapping->i_mmap_rwsem.
	 */
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	अगर (!mapping)
		वापस;

	pgoff_start = page_to_pgoff(page);
	pgoff_end = pgoff_start + thp_nr_pages(page) - 1;
	अगर (!locked)
		i_mmap_lock_पढ़ो(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(vma, &mapping->i_mmap,
			pgoff_start, pgoff_end) अणु
		अचिन्हित दीर्घ address = vma_address(page, vma);

		VM_BUG_ON_VMA(address == -EFAULT, vma);
		cond_resched();

		अगर (rwc->invalid_vma && rwc->invalid_vma(vma, rwc->arg))
			जारी;

		अगर (!rwc->rmap_one(page, vma, address, rwc->arg))
			जाओ करोne;
		अगर (rwc->करोne && rwc->करोne(page))
			जाओ करोne;
	पूर्ण

करोne:
	अगर (!locked)
		i_mmap_unlock_पढ़ो(mapping);
पूर्ण

व्योम rmap_walk(काष्ठा page *page, काष्ठा rmap_walk_control *rwc)
अणु
	अगर (unlikely(PageKsm(page)))
		rmap_walk_ksm(page, rwc);
	अन्यथा अगर (PageAnon(page))
		rmap_walk_anon(page, rwc, false);
	अन्यथा
		rmap_walk_file(page, rwc, false);
पूर्ण

/* Like rmap_walk, but caller holds relevant rmap lock */
व्योम rmap_walk_locked(काष्ठा page *page, काष्ठा rmap_walk_control *rwc)
अणु
	/* no ksm support क्रम now */
	VM_BUG_ON_PAGE(PageKsm(page), page);
	अगर (PageAnon(page))
		rmap_walk_anon(page, rwc, true);
	अन्यथा
		rmap_walk_file(page, rwc, true);
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
/*
 * The following two functions are क्रम anonymous (निजी mapped) hugepages.
 * Unlike common anonymous pages, anonymous hugepages have no accounting code
 * and no lru code, because we handle hugepages dअगरferently from common pages.
 */
व्योम hugepage_add_anon_rmap(काष्ठा page *page,
			    काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	काष्ठा anon_vma *anon_vma = vma->anon_vma;
	पूर्णांक first;

	BUG_ON(!PageLocked(page));
	BUG_ON(!anon_vma);
	/* address might be in next vma when migration races vma_adjust */
	first = atomic_inc_and_test(compound_mapcount_ptr(page));
	अगर (first)
		__page_set_anon_rmap(page, vma, address, 0);
पूर्ण

व्योम hugepage_add_new_anon_rmap(काष्ठा page *page,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	BUG_ON(address < vma->vm_start || address >= vma->vm_end);
	atomic_set(compound_mapcount_ptr(page), 0);
	अगर (hpage_pincount_available(page))
		atomic_set(compound_pincount_ptr(page), 0);

	__page_set_anon_rmap(page, vma, address, 1);
पूर्ण
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */
