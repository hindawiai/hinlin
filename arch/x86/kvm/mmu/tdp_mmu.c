<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "mmu.h"
#समावेश "mmu_internal.h"
#समावेश "mmutrace.h"
#समावेश "tdp_iter.h"
#समावेश "tdp_mmu.h"
#समावेश "spte.h"

#समावेश <यंत्र/cmpxchg.h>
#समावेश <trace/events/kvm.h>

अटल bool __पढ़ो_mostly tdp_mmu_enabled = false;
module_param_named(tdp_mmu, tdp_mmu_enabled, bool, 0644);

/* Initializes the TDP MMU क्रम the VM, अगर enabled. */
व्योम kvm_mmu_init_tdp_mmu(काष्ठा kvm *kvm)
अणु
	अगर (!tdp_enabled || !READ_ONCE(tdp_mmu_enabled))
		वापस;

	/* This should not be changed क्रम the lअगरeसमय of the VM. */
	kvm->arch.tdp_mmu_enabled = true;

	INIT_LIST_HEAD(&kvm->arch.tdp_mmu_roots);
	spin_lock_init(&kvm->arch.tdp_mmu_pages_lock);
	INIT_LIST_HEAD(&kvm->arch.tdp_mmu_pages);
पूर्ण

अटल __always_अंतरभूत व्योम kvm_lockdep_निश्चित_mmu_lock_held(काष्ठा kvm *kvm,
							     bool shared)
अणु
	अगर (shared)
		lockdep_निश्चित_held_पढ़ो(&kvm->mmu_lock);
	अन्यथा
		lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);
पूर्ण

व्योम kvm_mmu_uninit_tdp_mmu(काष्ठा kvm *kvm)
अणु
	अगर (!kvm->arch.tdp_mmu_enabled)
		वापस;

	WARN_ON(!list_empty(&kvm->arch.tdp_mmu_roots));

	/*
	 * Ensure that all the outstanding RCU callbacks to मुक्त shaकरोw pages
	 * can run beक्रमe the VM is torn करोwn.
	 */
	rcu_barrier();
पूर्ण

अटल bool zap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			  gfn_t start, gfn_t end, bool can_yield, bool flush,
			  bool shared);

अटल व्योम tdp_mmu_मुक्त_sp(काष्ठा kvm_mmu_page *sp)
अणु
	मुक्त_page((अचिन्हित दीर्घ)sp->spt);
	kmem_cache_मुक्त(mmu_page_header_cache, sp);
पूर्ण

/*
 * This is called through call_rcu in order to मुक्त TDP page table memory
 * safely with respect to other kernel thपढ़ोs that may be operating on
 * the memory.
 * By only accessing TDP MMU page table memory in an RCU पढ़ो critical
 * section, and मुक्तing it after a grace period, lockless access to that
 * memory won't use it after it is मुक्तd.
 */
अटल व्योम tdp_mmu_मुक्त_sp_rcu_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा kvm_mmu_page *sp = container_of(head, काष्ठा kvm_mmu_page,
					       rcu_head);

	tdp_mmu_मुक्त_sp(sp);
पूर्ण

व्योम kvm_tdp_mmu_put_root(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			  bool shared)
अणु
	gfn_t max_gfn = 1ULL << (shaकरोw_phys_bits - PAGE_SHIFT);

	kvm_lockdep_निश्चित_mmu_lock_held(kvm, shared);

	अगर (!refcount_dec_and_test(&root->tdp_mmu_root_count))
		वापस;

	WARN_ON(!root->tdp_mmu_page);

	spin_lock(&kvm->arch.tdp_mmu_pages_lock);
	list_del_rcu(&root->link);
	spin_unlock(&kvm->arch.tdp_mmu_pages_lock);

	zap_gfn_range(kvm, root, 0, max_gfn, false, false, shared);

	call_rcu(&root->rcu_head, tdp_mmu_मुक्त_sp_rcu_callback);
पूर्ण

/*
 * Finds the next valid root after root (or the first valid root अगर root
 * is शून्य), takes a reference on it, and वापसs that next root. If root
 * is not शून्य, this thपढ़ो should have alपढ़ोy taken a reference on it, and
 * that reference will be dropped. If no valid root is found, this
 * function will वापस शून्य.
 */
अटल काष्ठा kvm_mmu_page *tdp_mmu_next_root(काष्ठा kvm *kvm,
					      काष्ठा kvm_mmu_page *prev_root,
					      bool shared)
अणु
	काष्ठा kvm_mmu_page *next_root;

	rcu_पढ़ो_lock();

	अगर (prev_root)
		next_root = list_next_or_null_rcu(&kvm->arch.tdp_mmu_roots,
						  &prev_root->link,
						  typeof(*prev_root), link);
	अन्यथा
		next_root = list_first_or_null_rcu(&kvm->arch.tdp_mmu_roots,
						   typeof(*next_root), link);

	जबतक (next_root && !kvm_tdp_mmu_get_root(kvm, next_root))
		next_root = list_next_or_null_rcu(&kvm->arch.tdp_mmu_roots,
				&next_root->link, typeof(*next_root), link);

	rcu_पढ़ो_unlock();

	अगर (prev_root)
		kvm_tdp_mmu_put_root(kvm, prev_root, shared);

	वापस next_root;
पूर्ण

/*
 * Note: this iterator माला_लो and माला_दो references to the roots it iterates over.
 * This makes it safe to release the MMU lock and yield within the loop, but
 * अगर निकासing the loop early, the caller must drop the reference to the most
 * recent root. (Unless keeping a live reference is desirable.)
 *
 * If shared is set, this function is operating under the MMU lock in पढ़ो
 * mode. In the unlikely event that this thपढ़ो must मुक्त a root, the lock
 * will be temporarily dropped and reacquired in ग_लिखो mode.
 */
#घोषणा क्रम_each_tdp_mmu_root_yield_safe(_kvm, _root, _as_id, _shared)	\
	क्रम (_root = tdp_mmu_next_root(_kvm, शून्य, _shared);		\
	     _root;							\
	     _root = tdp_mmu_next_root(_kvm, _root, _shared))		\
		अगर (kvm_mmu_page_as_id(_root) != _as_id) अणु		\
		पूर्ण अन्यथा

#घोषणा क्रम_each_tdp_mmu_root(_kvm, _root, _as_id)				\
	list_क्रम_each_entry_rcu(_root, &_kvm->arch.tdp_mmu_roots, link,		\
				lockdep_is_held_type(&kvm->mmu_lock, 0) ||	\
				lockdep_is_held(&kvm->arch.tdp_mmu_pages_lock))	\
		अगर (kvm_mmu_page_as_id(_root) != _as_id) अणु		\
		पूर्ण अन्यथा

अटल जोड़ kvm_mmu_page_role page_role_क्रम_level(काष्ठा kvm_vcpu *vcpu,
						   पूर्णांक level)
अणु
	जोड़ kvm_mmu_page_role role;

	role = vcpu->arch.mmu->mmu_role.base;
	role.level = level;
	role.direct = true;
	role.gpte_is_8_bytes = true;
	role.access = ACC_ALL;

	वापस role;
पूर्ण

अटल काष्ठा kvm_mmu_page *alloc_tdp_mmu_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
					       पूर्णांक level)
अणु
	काष्ठा kvm_mmu_page *sp;

	sp = kvm_mmu_memory_cache_alloc(&vcpu->arch.mmu_page_header_cache);
	sp->spt = kvm_mmu_memory_cache_alloc(&vcpu->arch.mmu_shaकरोw_page_cache);
	set_page_निजी(virt_to_page(sp->spt), (अचिन्हित दीर्घ)sp);

	sp->role.word = page_role_क्रम_level(vcpu, level).word;
	sp->gfn = gfn;
	sp->tdp_mmu_page = true;

	trace_kvm_mmu_get_page(sp, true);

	वापस sp;
पूर्ण

hpa_t kvm_tdp_mmu_get_vcpu_root_hpa(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ kvm_mmu_page_role role;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_mmu_page *root;

	lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);

	role = page_role_क्रम_level(vcpu, vcpu->arch.mmu->shaकरोw_root_level);

	/* Check क्रम an existing root beक्रमe allocating a new one. */
	क्रम_each_tdp_mmu_root(kvm, root, kvm_mmu_role_as_id(role)) अणु
		अगर (root->role.word == role.word &&
		    kvm_tdp_mmu_get_root(kvm, root))
			जाओ out;
	पूर्ण

	root = alloc_tdp_mmu_page(vcpu, 0, vcpu->arch.mmu->shaकरोw_root_level);
	refcount_set(&root->tdp_mmu_root_count, 1);

	spin_lock(&kvm->arch.tdp_mmu_pages_lock);
	list_add_rcu(&root->link, &kvm->arch.tdp_mmu_roots);
	spin_unlock(&kvm->arch.tdp_mmu_pages_lock);

out:
	वापस __pa(root->spt);
पूर्ण

अटल व्योम handle_changed_spte(काष्ठा kvm *kvm, पूर्णांक as_id, gfn_t gfn,
				u64 old_spte, u64 new_spte, पूर्णांक level,
				bool shared);

अटल व्योम handle_changed_spte_acc_track(u64 old_spte, u64 new_spte, पूर्णांक level)
अणु
	अगर (!is_shaकरोw_present_pte(old_spte) || !is_last_spte(old_spte, level))
		वापस;

	अगर (is_accessed_spte(old_spte) &&
	    (!is_shaकरोw_present_pte(new_spte) || !is_accessed_spte(new_spte) ||
	     spte_to_pfn(old_spte) != spte_to_pfn(new_spte)))
		kvm_set_pfn_accessed(spte_to_pfn(old_spte));
पूर्ण

अटल व्योम handle_changed_spte_dirty_log(काष्ठा kvm *kvm, पूर्णांक as_id, gfn_t gfn,
					  u64 old_spte, u64 new_spte, पूर्णांक level)
अणु
	bool pfn_changed;
	काष्ठा kvm_memory_slot *slot;

	अगर (level > PG_LEVEL_4K)
		वापस;

	pfn_changed = spte_to_pfn(old_spte) != spte_to_pfn(new_spte);

	अगर ((!is_writable_pte(old_spte) || pfn_changed) &&
	    is_writable_pte(new_spte)) अणु
		slot = __gfn_to_memslot(__kvm_memslots(kvm, as_id), gfn);
		mark_page_dirty_in_slot(kvm, slot, gfn);
	पूर्ण
पूर्ण

/**
 * tdp_mmu_link_page - Add a new page to the list of pages used by the TDP MMU
 *
 * @kvm: kvm instance
 * @sp: the new page
 * @shared: This operation may not be running under the exclusive use of
 *	    the MMU lock and the operation must synchronize with other
 *	    thपढ़ोs that might be adding or removing pages.
 * @account_nx: This page replaces a NX large page and should be marked क्रम
 *		eventual reclaim.
 */
अटल व्योम tdp_mmu_link_page(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp,
			      bool shared, bool account_nx)
अणु
	अगर (shared)
		spin_lock(&kvm->arch.tdp_mmu_pages_lock);
	अन्यथा
		lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);

	list_add(&sp->link, &kvm->arch.tdp_mmu_pages);
	अगर (account_nx)
		account_huge_nx_page(kvm, sp);

	अगर (shared)
		spin_unlock(&kvm->arch.tdp_mmu_pages_lock);
पूर्ण

/**
 * tdp_mmu_unlink_page - Remove page from the list of pages used by the TDP MMU
 *
 * @kvm: kvm instance
 * @sp: the page to be हटाओd
 * @shared: This operation may not be running under the exclusive use of
 *	    the MMU lock and the operation must synchronize with other
 *	    thपढ़ोs that might be adding or removing pages.
 */
अटल व्योम tdp_mmu_unlink_page(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp,
				bool shared)
अणु
	अगर (shared)
		spin_lock(&kvm->arch.tdp_mmu_pages_lock);
	अन्यथा
		lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);

	list_del(&sp->link);
	अगर (sp->lpage_disallowed)
		unaccount_huge_nx_page(kvm, sp);

	अगर (shared)
		spin_unlock(&kvm->arch.tdp_mmu_pages_lock);
पूर्ण

/**
 * handle_हटाओd_tdp_mmu_page - handle a pt हटाओd from the TDP काष्ठाure
 *
 * @kvm: kvm instance
 * @pt: the page हटाओd from the paging काष्ठाure
 * @shared: This operation may not be running under the exclusive use
 *	    of the MMU lock and the operation must synchronize with other
 *	    thपढ़ोs that might be modअगरying SPTEs.
 *
 * Given a page table that has been हटाओd from the TDP paging काष्ठाure,
 * iterates through the page table to clear SPTEs and मुक्त child page tables.
 *
 * Note that pt is passed in as a tdp_ptep_t, but it करोes not need RCU
 * protection. Since this thपढ़ो हटाओd it from the paging काष्ठाure,
 * this thपढ़ो will be responsible क्रम ensuring the page is मुक्तd. Hence the
 * early rcu_dereferences in the function.
 */
अटल व्योम handle_हटाओd_tdp_mmu_page(काष्ठा kvm *kvm, tdp_ptep_t pt,
					bool shared)
अणु
	काष्ठा kvm_mmu_page *sp = sptep_to_sp(rcu_dereference(pt));
	पूर्णांक level = sp->role.level;
	gfn_t base_gfn = sp->gfn;
	u64 old_child_spte;
	u64 *sptep;
	gfn_t gfn;
	पूर्णांक i;

	trace_kvm_mmu_prepare_zap_page(sp);

	tdp_mmu_unlink_page(kvm, sp, shared);

	क्रम (i = 0; i < PT64_ENT_PER_PAGE; i++) अणु
		sptep = rcu_dereference(pt) + i;
		gfn = base_gfn + (i * KVM_PAGES_PER_HPAGE(level - 1));

		अगर (shared) अणु
			/*
			 * Set the SPTE to a nonpresent value that other
			 * thपढ़ोs will not overग_लिखो. If the SPTE was
			 * alपढ़ोy marked as हटाओd then another thपढ़ो
			 * handling a page fault could overग_लिखो it, so
			 * set the SPTE until it is set from some other
			 * value to the हटाओd SPTE value.
			 */
			क्रम (;;) अणु
				old_child_spte = xchg(sptep, REMOVED_SPTE);
				अगर (!is_हटाओd_spte(old_child_spte))
					अवरोध;
				cpu_relax();
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * If the SPTE is not MMU-present, there is no backing
			 * page associated with the SPTE and so no side effects
			 * that need to be recorded, and exclusive ownership of
			 * mmu_lock ensures the SPTE can't be made present.
			 * Note, zapping MMIO SPTEs is also unnecessary as they
			 * are guarded by the memslots generation, not by being
			 * unreachable.
			 */
			old_child_spte = READ_ONCE(*sptep);
			अगर (!is_shaकरोw_present_pte(old_child_spte))
				जारी;

			/*
			 * Marking the SPTE as a हटाओd SPTE is not
			 * strictly necessary here as the MMU lock will
			 * stop other thपढ़ोs from concurrently modअगरying
			 * this SPTE. Using the हटाओd SPTE value keeps
			 * the two branches consistent and simplअगरies
			 * the function.
			 */
			WRITE_ONCE(*sptep, REMOVED_SPTE);
		पूर्ण
		handle_changed_spte(kvm, kvm_mmu_page_as_id(sp), gfn,
				    old_child_spte, REMOVED_SPTE, level - 1,
				    shared);
	पूर्ण

	kvm_flush_remote_tlbs_with_address(kvm, gfn,
					   KVM_PAGES_PER_HPAGE(level));

	call_rcu(&sp->rcu_head, tdp_mmu_मुक्त_sp_rcu_callback);
पूर्ण

/**
 * __handle_changed_spte - handle bookkeeping associated with an SPTE change
 * @kvm: kvm instance
 * @as_id: the address space of the paging काष्ठाure the SPTE was a part of
 * @gfn: the base GFN that was mapped by the SPTE
 * @old_spte: The value of the SPTE beक्रमe the change
 * @new_spte: The value of the SPTE after the change
 * @level: the level of the PT the SPTE is part of in the paging काष्ठाure
 * @shared: This operation may not be running under the exclusive use of
 *	    the MMU lock and the operation must synchronize with other
 *	    thपढ़ोs that might be modअगरying SPTEs.
 *
 * Handle bookkeeping that might result from the modअगरication of a SPTE.
 * This function must be called क्रम all TDP SPTE modअगरications.
 */
अटल व्योम __handle_changed_spte(काष्ठा kvm *kvm, पूर्णांक as_id, gfn_t gfn,
				  u64 old_spte, u64 new_spte, पूर्णांक level,
				  bool shared)
अणु
	bool was_present = is_shaकरोw_present_pte(old_spte);
	bool is_present = is_shaकरोw_present_pte(new_spte);
	bool was_leaf = was_present && is_last_spte(old_spte, level);
	bool is_leaf = is_present && is_last_spte(new_spte, level);
	bool pfn_changed = spte_to_pfn(old_spte) != spte_to_pfn(new_spte);

	WARN_ON(level > PT64_ROOT_MAX_LEVEL);
	WARN_ON(level < PG_LEVEL_4K);
	WARN_ON(gfn & (KVM_PAGES_PER_HPAGE(level) - 1));

	/*
	 * If this warning were to trigger it would indicate that there was a
	 * missing MMU notअगरier or a race with some notअगरier handler.
	 * A present, leaf SPTE should never be directly replaced with another
	 * present leaf SPTE poपूर्णांकing to a dअगरferent PFN. A notअगरier handler
	 * should be zapping the SPTE beक्रमe the मुख्य MM's page table is
	 * changed, or the SPTE should be zeroed, and the TLBs flushed by the
	 * thपढ़ो beक्रमe replacement.
	 */
	अगर (was_leaf && is_leaf && pfn_changed) अणु
		pr_err("Invalid SPTE change: cannot replace a present leaf\n"
		       "SPTE with another present leaf SPTE mapping a\n"
		       "different PFN!\n"
		       "as_id: %d gfn: %llx old_spte: %llx new_spte: %llx level: %d",
		       as_id, gfn, old_spte, new_spte, level);

		/*
		 * Crash the host to prevent error propagation and guest data
		 * corruption.
		 */
		BUG();
	पूर्ण

	अगर (old_spte == new_spte)
		वापस;

	trace_kvm_tdp_mmu_spte_changed(as_id, gfn, level, old_spte, new_spte);

	अगर (is_large_pte(old_spte) != is_large_pte(new_spte)) अणु
		अगर (is_large_pte(old_spte))
			atomic64_sub(1, (atomic64_t*)&kvm->stat.lpages);
		अन्यथा
			atomic64_add(1, (atomic64_t*)&kvm->stat.lpages);
	पूर्ण

	/*
	 * The only बार a SPTE should be changed from a non-present to
	 * non-present state is when an MMIO entry is installed/modअगरied/
	 * हटाओd. In that हाल, there is nothing to करो here.
	 */
	अगर (!was_present && !is_present) अणु
		/*
		 * If this change करोes not involve a MMIO SPTE or हटाओd SPTE,
		 * it is unexpected. Log the change, though it should not
		 * impact the guest since both the क्रमmer and current SPTEs
		 * are nonpresent.
		 */
		अगर (WARN_ON(!is_mmio_spte(old_spte) &&
			    !is_mmio_spte(new_spte) &&
			    !is_हटाओd_spte(new_spte)))
			pr_err("Unexpected SPTE change! Nonpresent SPTEs\n"
			       "should not be replaced with another,\n"
			       "different nonpresent SPTE, unless one or both\n"
			       "are MMIO SPTEs, or the new SPTE is\n"
			       "a temporary removed SPTE.\n"
			       "as_id: %d gfn: %llx old_spte: %llx new_spte: %llx level: %d",
			       as_id, gfn, old_spte, new_spte, level);
		वापस;
	पूर्ण


	अगर (was_leaf && is_dirty_spte(old_spte) &&
	    (!is_present || !is_dirty_spte(new_spte) || pfn_changed))
		kvm_set_pfn_dirty(spte_to_pfn(old_spte));

	/*
	 * Recursively handle child PTs अगर the change हटाओd a subtree from
	 * the paging काष्ठाure.
	 */
	अगर (was_present && !was_leaf && (pfn_changed || !is_present))
		handle_हटाओd_tdp_mmu_page(kvm,
				spte_to_child_pt(old_spte, level), shared);
पूर्ण

अटल व्योम handle_changed_spte(काष्ठा kvm *kvm, पूर्णांक as_id, gfn_t gfn,
				u64 old_spte, u64 new_spte, पूर्णांक level,
				bool shared)
अणु
	__handle_changed_spte(kvm, as_id, gfn, old_spte, new_spte, level,
			      shared);
	handle_changed_spte_acc_track(old_spte, new_spte, level);
	handle_changed_spte_dirty_log(kvm, as_id, gfn, old_spte,
				      new_spte, level);
पूर्ण

/*
 * tdp_mmu_set_spte_atomic_no_dirty_log - Set a TDP MMU SPTE atomically
 * and handle the associated bookkeeping, but करो not mark the page dirty
 * in KVM's dirty biपंचांगaps.
 *
 * @kvm: kvm instance
 * @iter: a tdp_iter instance currently on the SPTE that should be set
 * @new_spte: The value the SPTE should be set to
 * Returns: true अगर the SPTE was set, false अगर it was not. If false is वापसed,
 *	    this function will have no side-effects.
 */
अटल अंतरभूत bool tdp_mmu_set_spte_atomic_no_dirty_log(काष्ठा kvm *kvm,
							काष्ठा tdp_iter *iter,
							u64 new_spte)
अणु
	lockdep_निश्चित_held_पढ़ो(&kvm->mmu_lock);

	/*
	 * Do not change हटाओd SPTEs. Only the thपढ़ो that froze the SPTE
	 * may modअगरy it.
	 */
	अगर (is_हटाओd_spte(iter->old_spte))
		वापस false;

	अगर (cmpxchg64(rcu_dereference(iter->sptep), iter->old_spte,
		      new_spte) != iter->old_spte)
		वापस false;

	__handle_changed_spte(kvm, iter->as_id, iter->gfn, iter->old_spte,
			      new_spte, iter->level, true);
	handle_changed_spte_acc_track(iter->old_spte, new_spte, iter->level);

	वापस true;
पूर्ण

अटल अंतरभूत bool tdp_mmu_set_spte_atomic(काष्ठा kvm *kvm,
					   काष्ठा tdp_iter *iter,
					   u64 new_spte)
अणु
	अगर (!tdp_mmu_set_spte_atomic_no_dirty_log(kvm, iter, new_spte))
		वापस false;

	handle_changed_spte_dirty_log(kvm, iter->as_id, iter->gfn,
				      iter->old_spte, new_spte, iter->level);
	वापस true;
पूर्ण

अटल अंतरभूत bool tdp_mmu_zap_spte_atomic(काष्ठा kvm *kvm,
					   काष्ठा tdp_iter *iter)
अणु
	/*
	 * Freeze the SPTE by setting it to a special,
	 * non-present value. This will stop other thपढ़ोs from
	 * immediately installing a present entry in its place
	 * beक्रमe the TLBs are flushed.
	 */
	अगर (!tdp_mmu_set_spte_atomic(kvm, iter, REMOVED_SPTE))
		वापस false;

	kvm_flush_remote_tlbs_with_address(kvm, iter->gfn,
					   KVM_PAGES_PER_HPAGE(iter->level));

	/*
	 * No other thपढ़ो can overग_लिखो the हटाओd SPTE as they
	 * must either रुको on the MMU lock or use
	 * tdp_mmu_set_spte_atomic which will not overग_लिखो the
	 * special हटाओd SPTE value. No bookkeeping is needed
	 * here since the SPTE is going from non-present
	 * to non-present.
	 */
	WRITE_ONCE(*rcu_dereference(iter->sptep), 0);

	वापस true;
पूर्ण


/*
 * __tdp_mmu_set_spte - Set a TDP MMU SPTE and handle the associated bookkeeping
 * @kvm: kvm instance
 * @iter: a tdp_iter instance currently on the SPTE that should be set
 * @new_spte: The value the SPTE should be set to
 * @record_acc_track: Notअगरy the MM subप्रणाली of changes to the accessed state
 *		      of the page. Should be set unless handling an MMU
 *		      notअगरier क्रम access tracking. Leaving record_acc_track
 *		      unset in that हाल prevents page accesses from being
 *		      द्विगुन counted.
 * @record_dirty_log: Record the page as dirty in the dirty biपंचांगap अगर
 *		      appropriate क्रम the change being made. Should be set
 *		      unless perक्रमming certain dirty logging operations.
 *		      Leaving record_dirty_log unset in that हाल prevents page
 *		      ग_लिखोs from being द्विगुन counted.
 */
अटल अंतरभूत व्योम __tdp_mmu_set_spte(काष्ठा kvm *kvm, काष्ठा tdp_iter *iter,
				      u64 new_spte, bool record_acc_track,
				      bool record_dirty_log)
अणु
	lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);

	/*
	 * No thपढ़ो should be using this function to set SPTEs to the
	 * temporary हटाओd SPTE value.
	 * If operating under the MMU lock in पढ़ो mode, tdp_mmu_set_spte_atomic
	 * should be used. If operating under the MMU lock in ग_लिखो mode, the
	 * use of the हटाओd SPTE should not be necessary.
	 */
	WARN_ON(is_हटाओd_spte(iter->old_spte));

	WRITE_ONCE(*rcu_dereference(iter->sptep), new_spte);

	__handle_changed_spte(kvm, iter->as_id, iter->gfn, iter->old_spte,
			      new_spte, iter->level, false);
	अगर (record_acc_track)
		handle_changed_spte_acc_track(iter->old_spte, new_spte,
					      iter->level);
	अगर (record_dirty_log)
		handle_changed_spte_dirty_log(kvm, iter->as_id, iter->gfn,
					      iter->old_spte, new_spte,
					      iter->level);
पूर्ण

अटल अंतरभूत व्योम tdp_mmu_set_spte(काष्ठा kvm *kvm, काष्ठा tdp_iter *iter,
				    u64 new_spte)
अणु
	__tdp_mmu_set_spte(kvm, iter, new_spte, true, true);
पूर्ण

अटल अंतरभूत व्योम tdp_mmu_set_spte_no_acc_track(काष्ठा kvm *kvm,
						 काष्ठा tdp_iter *iter,
						 u64 new_spte)
अणु
	__tdp_mmu_set_spte(kvm, iter, new_spte, false, true);
पूर्ण

अटल अंतरभूत व्योम tdp_mmu_set_spte_no_dirty_log(काष्ठा kvm *kvm,
						 काष्ठा tdp_iter *iter,
						 u64 new_spte)
अणु
	__tdp_mmu_set_spte(kvm, iter, new_spte, true, false);
पूर्ण

#घोषणा tdp_root_क्रम_each_pte(_iter, _root, _start, _end) \
	क्रम_each_tdp_pte(_iter, _root->spt, _root->role.level, _start, _end)

#घोषणा tdp_root_क्रम_each_leaf_pte(_iter, _root, _start, _end)	\
	tdp_root_क्रम_each_pte(_iter, _root, _start, _end)		\
		अगर (!is_shaकरोw_present_pte(_iter.old_spte) ||		\
		    !is_last_spte(_iter.old_spte, _iter.level))		\
			जारी;					\
		अन्यथा

#घोषणा tdp_mmu_क्रम_each_pte(_iter, _mmu, _start, _end)		\
	क्रम_each_tdp_pte(_iter, __va(_mmu->root_hpa),		\
			 _mmu->shaकरोw_root_level, _start, _end)

/*
 * Yield अगर the MMU lock is contended or this thपढ़ो needs to वापस control
 * to the scheduler.
 *
 * If this function should yield and flush is set, it will perक्रमm a remote
 * TLB flush beक्रमe yielding.
 *
 * If this function yields, it will also reset the tdp_iter's walk over the
 * paging काष्ठाure and the calling function should skip to the next
 * iteration to allow the iterator to जारी its traversal from the
 * paging काष्ठाure root.
 *
 * Return true अगर this function yielded and the iterator's traversal was reset.
 * Return false अगर a yield was not needed.
 */
अटल अंतरभूत bool tdp_mmu_iter_cond_resched(काष्ठा kvm *kvm,
					     काष्ठा tdp_iter *iter, bool flush,
					     bool shared)
अणु
	/* Ensure क्रमward progress has been made beक्रमe yielding. */
	अगर (iter->next_last_level_gfn == iter->yielded_gfn)
		वापस false;

	अगर (need_resched() || rwlock_needअवरोध(&kvm->mmu_lock)) अणु
		rcu_पढ़ो_unlock();

		अगर (flush)
			kvm_flush_remote_tlbs(kvm);

		अगर (shared)
			cond_resched_rwlock_पढ़ो(&kvm->mmu_lock);
		अन्यथा
			cond_resched_rwlock_ग_लिखो(&kvm->mmu_lock);

		rcu_पढ़ो_lock();

		WARN_ON(iter->gfn > iter->next_last_level_gfn);

		tdp_iter_restart(iter);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Tears करोwn the mappings क्रम the range of gfns, [start, end), and मुक्तs the
 * non-root pages mapping GFNs strictly within that range. Returns true अगर
 * SPTEs have been cleared and a TLB flush is needed beक्रमe releasing the
 * MMU lock.
 *
 * If can_yield is true, will release the MMU lock and reschedule अगर the
 * scheduler needs the CPU or there is contention on the MMU lock. If this
 * function cannot yield, it will not release the MMU lock or reschedule and
 * the caller must ensure it करोes not supply too large a GFN range, or the
 * operation can cause a soft lockup.
 *
 * If shared is true, this thपढ़ो holds the MMU lock in पढ़ो mode and must
 * account क्रम the possibility that other thपढ़ोs are modअगरying the paging
 * काष्ठाures concurrently. If shared is false, this thपढ़ो should hold the
 * MMU lock in ग_लिखो mode.
 */
अटल bool zap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			  gfn_t start, gfn_t end, bool can_yield, bool flush,
			  bool shared)
अणु
	काष्ठा tdp_iter iter;

	kvm_lockdep_निश्चित_mmu_lock_held(kvm, shared);

	rcu_पढ़ो_lock();

	tdp_root_क्रम_each_pte(iter, root, start, end) अणु
retry:
		अगर (can_yield &&
		    tdp_mmu_iter_cond_resched(kvm, &iter, flush, shared)) अणु
			flush = false;
			जारी;
		पूर्ण

		अगर (!is_shaकरोw_present_pte(iter.old_spte))
			जारी;

		/*
		 * If this is a non-last-level SPTE that covers a larger range
		 * than should be zapped, जारी, and zap the mappings at a
		 * lower level.
		 */
		अगर ((iter.gfn < start ||
		     iter.gfn + KVM_PAGES_PER_HPAGE(iter.level) > end) &&
		    !is_last_spte(iter.old_spte, iter.level))
			जारी;

		अगर (!shared) अणु
			tdp_mmu_set_spte(kvm, &iter, 0);
			flush = true;
		पूर्ण अन्यथा अगर (!tdp_mmu_zap_spte_atomic(kvm, &iter)) अणु
			/*
			 * The iter must explicitly re-पढ़ो the SPTE because
			 * the atomic cmpxchg failed.
			 */
			iter.old_spte = READ_ONCE(*rcu_dereference(iter.sptep));
			जाओ retry;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस flush;
पूर्ण

/*
 * Tears करोwn the mappings क्रम the range of gfns, [start, end), and मुक्तs the
 * non-root pages mapping GFNs strictly within that range. Returns true अगर
 * SPTEs have been cleared and a TLB flush is needed beक्रमe releasing the
 * MMU lock.
 *
 * If shared is true, this thपढ़ो holds the MMU lock in पढ़ो mode and must
 * account क्रम the possibility that other thपढ़ोs are modअगरying the paging
 * काष्ठाures concurrently. If shared is false, this thपढ़ो should hold the
 * MMU in ग_लिखो mode.
 */
bool __kvm_tdp_mmu_zap_gfn_range(काष्ठा kvm *kvm, पूर्णांक as_id, gfn_t start,
				 gfn_t end, bool can_yield, bool flush,
				 bool shared)
अणु
	काष्ठा kvm_mmu_page *root;

	क्रम_each_tdp_mmu_root_yield_safe(kvm, root, as_id, shared)
		flush = zap_gfn_range(kvm, root, start, end, can_yield, flush,
				      shared);

	वापस flush;
पूर्ण

व्योम kvm_tdp_mmu_zap_all(काष्ठा kvm *kvm)
अणु
	gfn_t max_gfn = 1ULL << (shaकरोw_phys_bits - PAGE_SHIFT);
	bool flush = false;
	पूर्णांक i;

	क्रम (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++)
		flush = kvm_tdp_mmu_zap_gfn_range(kvm, i, 0, max_gfn,
						  flush, false);

	अगर (flush)
		kvm_flush_remote_tlbs(kvm);
पूर्ण

अटल काष्ठा kvm_mmu_page *next_invalidated_root(काष्ठा kvm *kvm,
						  काष्ठा kvm_mmu_page *prev_root)
अणु
	काष्ठा kvm_mmu_page *next_root;

	अगर (prev_root)
		next_root = list_next_or_null_rcu(&kvm->arch.tdp_mmu_roots,
						  &prev_root->link,
						  typeof(*prev_root), link);
	अन्यथा
		next_root = list_first_or_null_rcu(&kvm->arch.tdp_mmu_roots,
						   typeof(*next_root), link);

	जबतक (next_root && !(next_root->role.invalid &&
			      refcount_पढ़ो(&next_root->tdp_mmu_root_count)))
		next_root = list_next_or_null_rcu(&kvm->arch.tdp_mmu_roots,
						  &next_root->link,
						  typeof(*next_root), link);

	वापस next_root;
पूर्ण

/*
 * Since kvm_tdp_mmu_zap_all_fast has acquired a reference to each
 * invalidated root, they will not be मुक्तd until this function drops the
 * reference. Beक्रमe dropping that reference, tear करोwn the paging
 * काष्ठाure so that whichever thपढ़ो करोes drop the last reference
 * only has to करो a trivial amount of work. Since the roots are invalid,
 * no new SPTEs should be created under them.
 */
व्योम kvm_tdp_mmu_zap_invalidated_roots(काष्ठा kvm *kvm)
अणु
	gfn_t max_gfn = 1ULL << (shaकरोw_phys_bits - PAGE_SHIFT);
	काष्ठा kvm_mmu_page *next_root;
	काष्ठा kvm_mmu_page *root;
	bool flush = false;

	lockdep_निश्चित_held_पढ़ो(&kvm->mmu_lock);

	rcu_पढ़ो_lock();

	root = next_invalidated_root(kvm, शून्य);

	जबतक (root) अणु
		next_root = next_invalidated_root(kvm, root);

		rcu_पढ़ो_unlock();

		flush = zap_gfn_range(kvm, root, 0, max_gfn, true, flush,
				      true);

		/*
		 * Put the reference acquired in
		 * kvm_tdp_mmu_invalidate_roots
		 */
		kvm_tdp_mmu_put_root(kvm, root, true);

		root = next_root;

		rcu_पढ़ो_lock();
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (flush)
		kvm_flush_remote_tlbs(kvm);
पूर्ण

/*
 * Mark each TDP MMU root as invalid so that other thपढ़ोs
 * will drop their references and allow the root count to
 * go to 0.
 *
 * Also take a reference on all roots so that this thपढ़ो
 * can करो the bulk of the work required to मुक्त the roots
 * once they are invalidated. Without this reference, a
 * vCPU thपढ़ो might drop the last reference to a root and
 * get stuck with tearing करोwn the entire paging काष्ठाure.
 *
 * Roots which have a zero refcount should be skipped as
 * they're alपढ़ोy being torn करोwn.
 * Alपढ़ोy invalid roots should be referenced again so that
 * they aren't मुक्तd beक्रमe kvm_tdp_mmu_zap_all_fast is
 * करोne with them.
 *
 * This has essentially the same effect क्रम the TDP MMU
 * as updating mmu_valid_gen करोes क्रम the shaकरोw MMU.
 */
व्योम kvm_tdp_mmu_invalidate_all_roots(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_mmu_page *root;

	lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);
	list_क्रम_each_entry(root, &kvm->arch.tdp_mmu_roots, link)
		अगर (refcount_inc_not_zero(&root->tdp_mmu_root_count))
			root->role.invalid = true;
पूर्ण

/*
 * Installs a last-level SPTE to handle a TDP page fault.
 * (NPT/EPT violation/misconfiguration)
 */
अटल पूर्णांक tdp_mmu_map_handle_target_level(काष्ठा kvm_vcpu *vcpu, पूर्णांक ग_लिखो,
					  पूर्णांक map_writable,
					  काष्ठा tdp_iter *iter,
					  kvm_pfn_t pfn, bool prefault)
अणु
	u64 new_spte;
	पूर्णांक ret = 0;
	पूर्णांक make_spte_ret = 0;

	अगर (unlikely(is_noslot_pfn(pfn)))
		new_spte = make_mmio_spte(vcpu, iter->gfn, ACC_ALL);
	अन्यथा
		make_spte_ret = make_spte(vcpu, ACC_ALL, iter->level, iter->gfn,
					 pfn, iter->old_spte, prefault, true,
					 map_writable, !shaकरोw_accessed_mask,
					 &new_spte);

	अगर (new_spte == iter->old_spte)
		ret = RET_PF_SPURIOUS;
	अन्यथा अगर (!tdp_mmu_set_spte_atomic(vcpu->kvm, iter, new_spte))
		वापस RET_PF_RETRY;

	/*
	 * If the page fault was caused by a ग_लिखो but the page is ग_लिखो
	 * रक्षित, emulation is needed. If the emulation was skipped,
	 * the vCPU would have the same fault again.
	 */
	अगर (make_spte_ret & SET_SPTE_WRITE_PROTECTED_PT) अणु
		अगर (ग_लिखो)
			ret = RET_PF_EMULATE;
		kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
	पूर्ण

	/* If a MMIO SPTE is installed, the MMIO will need to be emulated. */
	अगर (unlikely(is_mmio_spte(new_spte))) अणु
		trace_mark_mmio_spte(rcu_dereference(iter->sptep), iter->gfn,
				     new_spte);
		ret = RET_PF_EMULATE;
	पूर्ण अन्यथा अणु
		trace_kvm_mmu_set_spte(iter->level, iter->gfn,
				       rcu_dereference(iter->sptep));
	पूर्ण

	अगर (!prefault)
		vcpu->stat.pf_fixed++;

	वापस ret;
पूर्ण

/*
 * Handle a TDP page fault (NPT/EPT violation/misconfiguration) by installing
 * page tables and SPTEs to translate the faulting guest physical address.
 */
पूर्णांक kvm_tdp_mmu_map(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, u32 error_code,
		    पूर्णांक map_writable, पूर्णांक max_level, kvm_pfn_t pfn,
		    bool prefault)
अणु
	bool nx_huge_page_workaround_enabled = is_nx_huge_page_enabled();
	bool ग_लिखो = error_code & PFERR_WRITE_MASK;
	bool exec = error_code & PFERR_FETCH_MASK;
	bool huge_page_disallowed = exec && nx_huge_page_workaround_enabled;
	काष्ठा kvm_mmu *mmu = vcpu->arch.mmu;
	काष्ठा tdp_iter iter;
	काष्ठा kvm_mmu_page *sp;
	u64 *child_pt;
	u64 new_spte;
	पूर्णांक ret;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक level;
	पूर्णांक req_level;

	अगर (WARN_ON(!VALID_PAGE(vcpu->arch.mmu->root_hpa)))
		वापस RET_PF_RETRY;
	अगर (WARN_ON(!is_tdp_mmu_root(vcpu->kvm, vcpu->arch.mmu->root_hpa)))
		वापस RET_PF_RETRY;

	level = kvm_mmu_hugepage_adjust(vcpu, gfn, max_level, &pfn,
					huge_page_disallowed, &req_level);

	trace_kvm_mmu_spte_requested(gpa, level, pfn);

	rcu_पढ़ो_lock();

	tdp_mmu_क्रम_each_pte(iter, mmu, gfn, gfn + 1) अणु
		अगर (nx_huge_page_workaround_enabled)
			disallowed_hugepage_adjust(iter.old_spte, gfn,
						   iter.level, &pfn, &level);

		अगर (iter.level == level)
			अवरोध;

		/*
		 * If there is an SPTE mapping a large page at a higher level
		 * than the target, that SPTE must be cleared and replaced
		 * with a non-leaf SPTE.
		 */
		अगर (is_shaकरोw_present_pte(iter.old_spte) &&
		    is_large_pte(iter.old_spte)) अणु
			अगर (!tdp_mmu_zap_spte_atomic(vcpu->kvm, &iter))
				अवरोध;

			/*
			 * The iter must explicitly re-पढ़ो the spte here
			 * because the new value inक्रमms the !present
			 * path below.
			 */
			iter.old_spte = READ_ONCE(*rcu_dereference(iter.sptep));
		पूर्ण

		अगर (!is_shaकरोw_present_pte(iter.old_spte)) अणु
			/*
			 * If SPTE has been क्रमzen by another thपढ़ो, just
			 * give up and retry, aव्योमing unnecessary page table
			 * allocation and मुक्त.
			 */
			अगर (is_हटाओd_spte(iter.old_spte))
				अवरोध;

			sp = alloc_tdp_mmu_page(vcpu, iter.gfn, iter.level);
			child_pt = sp->spt;

			new_spte = make_nonleaf_spte(child_pt,
						     !shaकरोw_accessed_mask);

			अगर (tdp_mmu_set_spte_atomic(vcpu->kvm, &iter,
						    new_spte)) अणु
				tdp_mmu_link_page(vcpu->kvm, sp, true,
						  huge_page_disallowed &&
						  req_level >= iter.level);

				trace_kvm_mmu_get_page(sp, true);
			पूर्ण अन्यथा अणु
				tdp_mmu_मुक्त_sp(sp);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (iter.level != level) अणु
		rcu_पढ़ो_unlock();
		वापस RET_PF_RETRY;
	पूर्ण

	ret = tdp_mmu_map_handle_target_level(vcpu, ग_लिखो, map_writable, &iter,
					      pfn, prefault);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

bool kvm_tdp_mmu_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range,
				 bool flush)
अणु
	काष्ठा kvm_mmu_page *root;

	क्रम_each_tdp_mmu_root(kvm, root, range->slot->as_id)
		flush |= zap_gfn_range(kvm, root, range->start, range->end,
				       range->may_block, flush, false);

	वापस flush;
पूर्ण

प्रकार bool (*tdp_handler_t)(काष्ठा kvm *kvm, काष्ठा tdp_iter *iter,
			      काष्ठा kvm_gfn_range *range);

अटल __always_अंतरभूत bool kvm_tdp_mmu_handle_gfn(काष्ठा kvm *kvm,
						   काष्ठा kvm_gfn_range *range,
						   tdp_handler_t handler)
अणु
	काष्ठा kvm_mmu_page *root;
	काष्ठा tdp_iter iter;
	bool ret = false;

	rcu_पढ़ो_lock();

	/*
	 * Don't support rescheduling, none of the MMU notअगरiers that funnel
	 * पूर्णांकo this helper allow blocking; it'd be dead, wasteful code.
	 */
	क्रम_each_tdp_mmu_root(kvm, root, range->slot->as_id) अणु
		tdp_root_क्रम_each_leaf_pte(iter, root, range->start, range->end)
			ret |= handler(kvm, &iter, range);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/*
 * Mark the SPTEs range of GFNs [start, end) unaccessed and वापस non-zero
 * अगर any of the GFNs in the range have been accessed.
 */
अटल bool age_gfn_range(काष्ठा kvm *kvm, काष्ठा tdp_iter *iter,
			  काष्ठा kvm_gfn_range *range)
अणु
	u64 new_spte = 0;

	/* If we have a non-accessed entry we करोn't need to change the pte. */
	अगर (!is_accessed_spte(iter->old_spte))
		वापस false;

	new_spte = iter->old_spte;

	अगर (spte_ad_enabled(new_spte)) अणु
		new_spte &= ~shaकरोw_accessed_mask;
	पूर्ण अन्यथा अणु
		/*
		 * Capture the dirty status of the page, so that it करोesn't get
		 * lost when the SPTE is marked क्रम access tracking.
		 */
		अगर (is_writable_pte(new_spte))
			kvm_set_pfn_dirty(spte_to_pfn(new_spte));

		new_spte = mark_spte_क्रम_access_track(new_spte);
	पूर्ण

	tdp_mmu_set_spte_no_acc_track(kvm, iter, new_spte);

	वापस true;
पूर्ण

bool kvm_tdp_mmu_age_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm_tdp_mmu_handle_gfn(kvm, range, age_gfn_range);
पूर्ण

अटल bool test_age_gfn(काष्ठा kvm *kvm, काष्ठा tdp_iter *iter,
			 काष्ठा kvm_gfn_range *range)
अणु
	वापस is_accessed_spte(iter->old_spte);
पूर्ण

bool kvm_tdp_mmu_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm_tdp_mmu_handle_gfn(kvm, range, test_age_gfn);
पूर्ण

अटल bool set_spte_gfn(काष्ठा kvm *kvm, काष्ठा tdp_iter *iter,
			 काष्ठा kvm_gfn_range *range)
अणु
	u64 new_spte;

	/* Huge pages aren't expected to be modअगरied without first being zapped. */
	WARN_ON(pte_huge(range->pte) || range->start + 1 != range->end);

	अगर (iter->level != PG_LEVEL_4K ||
	    !is_shaकरोw_present_pte(iter->old_spte))
		वापस false;

	/*
	 * Note, when changing a पढ़ो-only SPTE, it's not strictly necessary to
	 * zero the SPTE beक्रमe setting the new PFN, but करोing so preserves the
	 * invariant that the PFN of a present * leaf SPTE can never change.
	 * See __handle_changed_spte().
	 */
	tdp_mmu_set_spte(kvm, iter, 0);

	अगर (!pte_ग_लिखो(range->pte)) अणु
		new_spte = kvm_mmu_changed_pte_notअगरier_make_spte(iter->old_spte,
								  pte_pfn(range->pte));

		tdp_mmu_set_spte(kvm, iter, new_spte);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Handle the changed_pte MMU notअगरier क्रम the TDP MMU.
 * data is a poपूर्णांकer to the new pte_t mapping the HVA specअगरied by the MMU
 * notअगरier.
 * Returns non-zero अगर a flush is needed beक्रमe releasing the MMU lock.
 */
bool kvm_tdp_mmu_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	bool flush = kvm_tdp_mmu_handle_gfn(kvm, range, set_spte_gfn);

	/* FIXME: वापस 'flush' instead of flushing here. */
	अगर (flush)
		kvm_flush_remote_tlbs_with_address(kvm, range->start, 1);

	वापस false;
पूर्ण

/*
 * Remove ग_लिखो access from all SPTEs at or above min_level that map GFNs
 * [start, end). Returns true अगर an SPTE has been changed and the TLBs need to
 * be flushed.
 */
अटल bool wrprot_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			     gfn_t start, gfn_t end, पूर्णांक min_level)
अणु
	काष्ठा tdp_iter iter;
	u64 new_spte;
	bool spte_set = false;

	rcu_पढ़ो_lock();

	BUG_ON(min_level > KVM_MAX_HUGEPAGE_LEVEL);

	क्रम_each_tdp_pte_min_level(iter, root->spt, root->role.level,
				   min_level, start, end) अणु
retry:
		अगर (tdp_mmu_iter_cond_resched(kvm, &iter, false, true))
			जारी;

		अगर (!is_shaकरोw_present_pte(iter.old_spte) ||
		    !is_last_spte(iter.old_spte, iter.level) ||
		    !(iter.old_spte & PT_WRITABLE_MASK))
			जारी;

		new_spte = iter.old_spte & ~PT_WRITABLE_MASK;

		अगर (!tdp_mmu_set_spte_atomic_no_dirty_log(kvm, &iter,
							  new_spte)) अणु
			/*
			 * The iter must explicitly re-पढ़ो the SPTE because
			 * the atomic cmpxchg failed.
			 */
			iter.old_spte = READ_ONCE(*rcu_dereference(iter.sptep));
			जाओ retry;
		पूर्ण
		spte_set = true;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस spte_set;
पूर्ण

/*
 * Remove ग_लिखो access from all the SPTEs mapping GFNs in the memslot. Will
 * only affect leaf SPTEs करोwn to min_level.
 * Returns true अगर an SPTE has been changed and the TLBs need to be flushed.
 */
bool kvm_tdp_mmu_wrprot_slot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot,
			     पूर्णांक min_level)
अणु
	काष्ठा kvm_mmu_page *root;
	bool spte_set = false;

	lockdep_निश्चित_held_पढ़ो(&kvm->mmu_lock);

	क्रम_each_tdp_mmu_root_yield_safe(kvm, root, slot->as_id, true)
		spte_set |= wrprot_gfn_range(kvm, root, slot->base_gfn,
			     slot->base_gfn + slot->npages, min_level);

	वापस spte_set;
पूर्ण

/*
 * Clear the dirty status of all the SPTEs mapping GFNs in the memslot. If
 * AD bits are enabled, this will involve clearing the dirty bit on each SPTE.
 * If AD bits are not enabled, this will require clearing the writable bit on
 * each SPTE. Returns true अगर an SPTE has been changed and the TLBs need to
 * be flushed.
 */
अटल bool clear_dirty_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			   gfn_t start, gfn_t end)
अणु
	काष्ठा tdp_iter iter;
	u64 new_spte;
	bool spte_set = false;

	rcu_पढ़ो_lock();

	tdp_root_क्रम_each_leaf_pte(iter, root, start, end) अणु
retry:
		अगर (tdp_mmu_iter_cond_resched(kvm, &iter, false, true))
			जारी;

		अगर (spte_ad_need_ग_लिखो_protect(iter.old_spte)) अणु
			अगर (is_writable_pte(iter.old_spte))
				new_spte = iter.old_spte & ~PT_WRITABLE_MASK;
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			अगर (iter.old_spte & shaकरोw_dirty_mask)
				new_spte = iter.old_spte & ~shaकरोw_dirty_mask;
			अन्यथा
				जारी;
		पूर्ण

		अगर (!tdp_mmu_set_spte_atomic_no_dirty_log(kvm, &iter,
							  new_spte)) अणु
			/*
			 * The iter must explicitly re-पढ़ो the SPTE because
			 * the atomic cmpxchg failed.
			 */
			iter.old_spte = READ_ONCE(*rcu_dereference(iter.sptep));
			जाओ retry;
		पूर्ण
		spte_set = true;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस spte_set;
पूर्ण

/*
 * Clear the dirty status of all the SPTEs mapping GFNs in the memslot. If
 * AD bits are enabled, this will involve clearing the dirty bit on each SPTE.
 * If AD bits are not enabled, this will require clearing the writable bit on
 * each SPTE. Returns true अगर an SPTE has been changed and the TLBs need to
 * be flushed.
 */
bool kvm_tdp_mmu_clear_dirty_slot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
	काष्ठा kvm_mmu_page *root;
	bool spte_set = false;

	lockdep_निश्चित_held_पढ़ो(&kvm->mmu_lock);

	क्रम_each_tdp_mmu_root_yield_safe(kvm, root, slot->as_id, true)
		spte_set |= clear_dirty_gfn_range(kvm, root, slot->base_gfn,
				slot->base_gfn + slot->npages);

	वापस spte_set;
पूर्ण

/*
 * Clears the dirty status of all the 4k SPTEs mapping GFNs क्रम which a bit is
 * set in mask, starting at gfn. The given memslot is expected to contain all
 * the GFNs represented by set bits in the mask. If AD bits are enabled,
 * clearing the dirty status will involve clearing the dirty bit on each SPTE
 * or, अगर AD bits are not enabled, clearing the writable bit on each SPTE.
 */
अटल व्योम clear_dirty_pt_masked(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
				  gfn_t gfn, अचिन्हित दीर्घ mask, bool wrprot)
अणु
	काष्ठा tdp_iter iter;
	u64 new_spte;

	rcu_पढ़ो_lock();

	tdp_root_क्रम_each_leaf_pte(iter, root, gfn + __ffs(mask),
				    gfn + BITS_PER_LONG) अणु
		अगर (!mask)
			अवरोध;

		अगर (iter.level > PG_LEVEL_4K ||
		    !(mask & (1UL << (iter.gfn - gfn))))
			जारी;

		mask &= ~(1UL << (iter.gfn - gfn));

		अगर (wrprot || spte_ad_need_ग_लिखो_protect(iter.old_spte)) अणु
			अगर (is_writable_pte(iter.old_spte))
				new_spte = iter.old_spte & ~PT_WRITABLE_MASK;
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			अगर (iter.old_spte & shaकरोw_dirty_mask)
				new_spte = iter.old_spte & ~shaकरोw_dirty_mask;
			अन्यथा
				जारी;
		पूर्ण

		tdp_mmu_set_spte_no_dirty_log(kvm, &iter, new_spte);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Clears the dirty status of all the 4k SPTEs mapping GFNs क्रम which a bit is
 * set in mask, starting at gfn. The given memslot is expected to contain all
 * the GFNs represented by set bits in the mask. If AD bits are enabled,
 * clearing the dirty status will involve clearing the dirty bit on each SPTE
 * or, अगर AD bits are not enabled, clearing the writable bit on each SPTE.
 */
व्योम kvm_tdp_mmu_clear_dirty_pt_masked(काष्ठा kvm *kvm,
				       काष्ठा kvm_memory_slot *slot,
				       gfn_t gfn, अचिन्हित दीर्घ mask,
				       bool wrprot)
अणु
	काष्ठा kvm_mmu_page *root;

	lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);
	क्रम_each_tdp_mmu_root(kvm, root, slot->as_id)
		clear_dirty_pt_masked(kvm, root, gfn, mask, wrprot);
पूर्ण

/*
 * Clear leaf entries which could be replaced by large mappings, क्रम
 * GFNs within the slot.
 */
अटल bool zap_collapsible_spte_range(काष्ठा kvm *kvm,
				       काष्ठा kvm_mmu_page *root,
				       स्थिर काष्ठा kvm_memory_slot *slot,
				       bool flush)
अणु
	gfn_t start = slot->base_gfn;
	gfn_t end = start + slot->npages;
	काष्ठा tdp_iter iter;
	kvm_pfn_t pfn;

	rcu_पढ़ो_lock();

	tdp_root_क्रम_each_pte(iter, root, start, end) अणु
retry:
		अगर (tdp_mmu_iter_cond_resched(kvm, &iter, flush, true)) अणु
			flush = false;
			जारी;
		पूर्ण

		अगर (!is_shaकरोw_present_pte(iter.old_spte) ||
		    !is_last_spte(iter.old_spte, iter.level))
			जारी;

		pfn = spte_to_pfn(iter.old_spte);
		अगर (kvm_is_reserved_pfn(pfn) ||
		    iter.level >= kvm_mmu_max_mapping_level(kvm, slot, iter.gfn,
							    pfn, PG_LEVEL_NUM))
			जारी;

		अगर (!tdp_mmu_zap_spte_atomic(kvm, &iter)) अणु
			/*
			 * The iter must explicitly re-पढ़ो the SPTE because
			 * the atomic cmpxchg failed.
			 */
			iter.old_spte = READ_ONCE(*rcu_dereference(iter.sptep));
			जाओ retry;
		पूर्ण
		flush = true;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस flush;
पूर्ण

/*
 * Clear non-leaf entries (and मुक्त associated page tables) which could
 * be replaced by large mappings, क्रम GFNs within the slot.
 */
bool kvm_tdp_mmu_zap_collapsible_sptes(काष्ठा kvm *kvm,
				       स्थिर काष्ठा kvm_memory_slot *slot,
				       bool flush)
अणु
	काष्ठा kvm_mmu_page *root;

	lockdep_निश्चित_held_पढ़ो(&kvm->mmu_lock);

	क्रम_each_tdp_mmu_root_yield_safe(kvm, root, slot->as_id, true)
		flush = zap_collapsible_spte_range(kvm, root, slot, flush);

	वापस flush;
पूर्ण

/*
 * Removes ग_लिखो access on the last level SPTE mapping this GFN and unsets the
 * MMU-writable bit to ensure future ग_लिखोs जारी to be पूर्णांकercepted.
 * Returns true अगर an SPTE was set and a TLB flush is needed.
 */
अटल bool ग_लिखो_protect_gfn(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			      gfn_t gfn)
अणु
	काष्ठा tdp_iter iter;
	u64 new_spte;
	bool spte_set = false;

	rcu_पढ़ो_lock();

	tdp_root_क्रम_each_leaf_pte(iter, root, gfn, gfn + 1) अणु
		अगर (!is_writable_pte(iter.old_spte))
			अवरोध;

		new_spte = iter.old_spte &
			~(PT_WRITABLE_MASK | shaकरोw_mmu_writable_mask);

		tdp_mmu_set_spte(kvm, &iter, new_spte);
		spte_set = true;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस spte_set;
पूर्ण

/*
 * Removes ग_लिखो access on the last level SPTE mapping this GFN and unsets the
 * MMU-writable bit to ensure future ग_लिखोs जारी to be पूर्णांकercepted.
 * Returns true अगर an SPTE was set and a TLB flush is needed.
 */
bool kvm_tdp_mmu_ग_लिखो_protect_gfn(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot, gfn_t gfn)
अणु
	काष्ठा kvm_mmu_page *root;
	bool spte_set = false;

	lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);
	क्रम_each_tdp_mmu_root(kvm, root, slot->as_id)
		spte_set |= ग_लिखो_protect_gfn(kvm, root, gfn);

	वापस spte_set;
पूर्ण

/*
 * Return the level of the lowest level SPTE added to sptes.
 * That SPTE may be non-present.
 */
पूर्णांक kvm_tdp_mmu_get_walk(काष्ठा kvm_vcpu *vcpu, u64 addr, u64 *sptes,
			 पूर्णांक *root_level)
अणु
	काष्ठा tdp_iter iter;
	काष्ठा kvm_mmu *mmu = vcpu->arch.mmu;
	gfn_t gfn = addr >> PAGE_SHIFT;
	पूर्णांक leaf = -1;

	*root_level = vcpu->arch.mmu->shaकरोw_root_level;

	rcu_पढ़ो_lock();

	tdp_mmu_क्रम_each_pte(iter, mmu, gfn, gfn + 1) अणु
		leaf = iter.level;
		sptes[leaf] = iter.old_spte;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस leaf;
पूर्ण
