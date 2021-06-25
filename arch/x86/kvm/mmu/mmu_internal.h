<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_MMU_INTERNAL_H
#घोषणा __KVM_X86_MMU_INTERNAL_H

#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_host.h>

#अघोषित MMU_DEBUG

#अगर_घोषित MMU_DEBUG
बाह्य bool dbg;

#घोषणा pgprपूर्णांकk(x...) करो अणु अगर (dbg) prपूर्णांकk(x); पूर्ण जबतक (0)
#घोषणा rmap_prपूर्णांकk(fmt, args...) करो अणु अगर (dbg) prपूर्णांकk("%s: " fmt, __func__, ## args); पूर्ण जबतक (0)
#घोषणा MMU_WARN_ON(x) WARN_ON(x)
#अन्यथा
#घोषणा pgprपूर्णांकk(x...) करो अणु पूर्ण जबतक (0)
#घोषणा rmap_prपूर्णांकk(x...) करो अणु पूर्ण जबतक (0)
#घोषणा MMU_WARN_ON(x) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Unlike regular MMU roots, PAE "roots", a.k.a. PDPTEs/PDPTRs, have a PRESENT
 * bit, and thus are guaranteed to be non-zero when valid.  And, when a guest
 * PDPTR is !PRESENT, its corresponding PAE root cannot be set to INVALID_PAGE,
 * as the CPU would treat that as PRESENT PDPTR with reserved bits set.  Use
 * '0' instead of INVALID_PAGE to indicate an invalid PAE root.
 */
#घोषणा INVALID_PAE_ROOT	0
#घोषणा IS_VALID_PAE_ROOT(x)	(!!(x))

काष्ठा kvm_mmu_page अणु
	काष्ठा list_head link;
	काष्ठा hlist_node hash_link;
	काष्ठा list_head lpage_disallowed_link;

	bool unsync;
	u8 mmu_valid_gen;
	bool mmio_cached;
	bool lpage_disallowed; /* Can't be replaced by an equiv large page */

	/*
	 * The following two entries are used to key the shaकरोw page in the
	 * hash table.
	 */
	जोड़ kvm_mmu_page_role role;
	gfn_t gfn;

	u64 *spt;
	/* hold the gfn of each spte inside spt */
	gfn_t *gfns;
	/* Currently serving as active root */
	जोड़ अणु
		पूर्णांक root_count;
		refcount_t tdp_mmu_root_count;
	पूर्ण;
	अचिन्हित पूर्णांक unsync_children;
	काष्ठा kvm_rmap_head parent_ptes; /* rmap poपूर्णांकers to parent sptes */
	DECLARE_BITMAP(unsync_child_biपंचांगap, 512);

#अगर_घोषित CONFIG_X86_32
	/*
	 * Used out of the mmu-lock to aव्योम पढ़ोing spte values जबतक an
	 * update is in progress; see the comments in __get_spte_lockless().
	 */
	पूर्णांक clear_spte_count;
#पूर्ण_अगर

	/* Number of ग_लिखोs since the last समय traversal visited this page.  */
	atomic_t ग_लिखो_flooding_count;

#अगर_घोषित CONFIG_X86_64
	bool tdp_mmu_page;

	/* Used क्रम मुक्तing the page asynchronously अगर it is a TDP MMU page. */
	काष्ठा rcu_head rcu_head;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा kmem_cache *mmu_page_header_cache;

अटल अंतरभूत काष्ठा kvm_mmu_page *to_shaकरोw_page(hpa_t shaकरोw_page)
अणु
	काष्ठा page *page = pfn_to_page(shaकरोw_page >> PAGE_SHIFT);

	वापस (काष्ठा kvm_mmu_page *)page_निजी(page);
पूर्ण

अटल अंतरभूत काष्ठा kvm_mmu_page *sptep_to_sp(u64 *sptep)
अणु
	वापस to_shaकरोw_page(__pa(sptep));
पूर्ण

अटल अंतरभूत पूर्णांक kvm_mmu_role_as_id(जोड़ kvm_mmu_page_role role)
अणु
	वापस role.smm ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_mmu_page_as_id(काष्ठा kvm_mmu_page *sp)
अणु
	वापस kvm_mmu_role_as_id(sp->role);
पूर्ण

अटल अंतरभूत bool kvm_vcpu_ad_need_ग_लिखो_protect(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * When using the EPT page-modअगरication log, the GPAs in the CPU dirty
	 * log would come from L2 rather than L1.  Thereक्रमe, we need to rely
	 * on ग_लिखो protection to record dirty pages, which bypasses PML, since
	 * ग_लिखोs now result in a vmनिकास.  Note, the check on CPU dirty logging
	 * being enabled is mandatory as the bits used to denote WP-only SPTEs
	 * are reserved क्रम NPT w/ PAE (32-bit KVM).
	 */
	वापस vcpu->arch.mmu == &vcpu->arch.guest_mmu &&
	       kvm_x86_ops.cpu_dirty_log_size;
पूर्ण

bool is_nx_huge_page_enabled(व्योम);
bool mmu_need_ग_लिखो_protect(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
			    bool can_unsync);

व्योम kvm_mmu_gfn_disallow_lpage(काष्ठा kvm_memory_slot *slot, gfn_t gfn);
व्योम kvm_mmu_gfn_allow_lpage(काष्ठा kvm_memory_slot *slot, gfn_t gfn);
bool kvm_mmu_slot_gfn_ग_लिखो_protect(काष्ठा kvm *kvm,
				    काष्ठा kvm_memory_slot *slot, u64 gfn);
व्योम kvm_flush_remote_tlbs_with_address(काष्ठा kvm *kvm,
					u64 start_gfn, u64 pages);

/*
 * Return values of handle_mmio_page_fault, mmu.page_fault, and fast_page_fault().
 *
 * RET_PF_RETRY: let CPU fault again on the address.
 * RET_PF_EMULATE: mmio page fault, emulate the inकाष्ठाion directly.
 * RET_PF_INVALID: the spte is invalid, let the real page fault path update it.
 * RET_PF_FIXED: The faulting entry has been fixed.
 * RET_PF_SPURIOUS: The faulting entry was alपढ़ोy fixed, e.g. by another vCPU.
 */
क्रमागत अणु
	RET_PF_RETRY = 0,
	RET_PF_EMULATE,
	RET_PF_INVALID,
	RET_PF_FIXED,
	RET_PF_SPURIOUS,
पूर्ण;

/* Bits which may be वापसed by set_spte() */
#घोषणा SET_SPTE_WRITE_PROTECTED_PT	BIT(0)
#घोषणा SET_SPTE_NEED_REMOTE_TLB_FLUSH	BIT(1)
#घोषणा SET_SPTE_SPURIOUS		BIT(2)

पूर्णांक kvm_mmu_max_mapping_level(काष्ठा kvm *kvm,
			      स्थिर काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			      kvm_pfn_t pfn, पूर्णांक max_level);
पूर्णांक kvm_mmu_hugepage_adjust(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
			    पूर्णांक max_level, kvm_pfn_t *pfnp,
			    bool huge_page_disallowed, पूर्णांक *req_level);
व्योम disallowed_hugepage_adjust(u64 spte, gfn_t gfn, पूर्णांक cur_level,
				kvm_pfn_t *pfnp, पूर्णांक *goal_levelp);

bool is_nx_huge_page_enabled(व्योम);

व्योम *mmu_memory_cache_alloc(काष्ठा kvm_mmu_memory_cache *mc);

व्योम account_huge_nx_page(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp);
व्योम unaccount_huge_nx_page(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp);

#पूर्ण_अगर /* __KVM_X86_MMU_INTERNAL_H */
