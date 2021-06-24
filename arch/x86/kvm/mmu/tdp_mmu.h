<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित __KVM_X86_MMU_TDP_MMU_H
#घोषणा __KVM_X86_MMU_TDP_MMU_H

#समावेश <linux/kvm_host.h>

hpa_t kvm_tdp_mmu_get_vcpu_root_hpa(काष्ठा kvm_vcpu *vcpu);

__must_check अटल अंतरभूत bool kvm_tdp_mmu_get_root(काष्ठा kvm *kvm,
						     काष्ठा kvm_mmu_page *root)
अणु
	अगर (root->role.invalid)
		वापस false;

	वापस refcount_inc_not_zero(&root->tdp_mmu_root_count);
पूर्ण

व्योम kvm_tdp_mmu_put_root(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *root,
			  bool shared);

bool __kvm_tdp_mmu_zap_gfn_range(काष्ठा kvm *kvm, पूर्णांक as_id, gfn_t start,
				 gfn_t end, bool can_yield, bool flush,
				 bool shared);
अटल अंतरभूत bool kvm_tdp_mmu_zap_gfn_range(काष्ठा kvm *kvm, पूर्णांक as_id,
					     gfn_t start, gfn_t end, bool flush,
					     bool shared)
अणु
	वापस __kvm_tdp_mmu_zap_gfn_range(kvm, as_id, start, end, true, flush,
					   shared);
पूर्ण
अटल अंतरभूत bool kvm_tdp_mmu_zap_sp(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp)
अणु
	gfn_t end = sp->gfn + KVM_PAGES_PER_HPAGE(sp->role.level);

	/*
	 * Don't allow yielding, as the caller may have a flush pending.  Note,
	 * अगर mmu_lock is held क्रम ग_लिखो, zapping will never yield in this हाल,
	 * but explicitly disallow it क्रम safety.  The TDP MMU करोes not yield
	 * until it has made क्रमward progress (steps sideways), and when zapping
	 * a single shaकरोw page that it's guaranteed to see (thus the mmu_lock
	 * requirement), its "step sideways" will always step beyond the bounds
	 * of the shaकरोw page's gfn range and stop iterating beक्रमe yielding.
	 */
	lockdep_निश्चित_held_ग_लिखो(&kvm->mmu_lock);
	वापस __kvm_tdp_mmu_zap_gfn_range(kvm, kvm_mmu_page_as_id(sp),
					   sp->gfn, end, false, false, false);
पूर्ण

व्योम kvm_tdp_mmu_zap_all(काष्ठा kvm *kvm);
व्योम kvm_tdp_mmu_invalidate_all_roots(काष्ठा kvm *kvm);
व्योम kvm_tdp_mmu_zap_invalidated_roots(काष्ठा kvm *kvm);

पूर्णांक kvm_tdp_mmu_map(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, u32 error_code,
		    पूर्णांक map_writable, पूर्णांक max_level, kvm_pfn_t pfn,
		    bool prefault);

bool kvm_tdp_mmu_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range,
				 bool flush);
bool kvm_tdp_mmu_age_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
bool kvm_tdp_mmu_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
bool kvm_tdp_mmu_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);

bool kvm_tdp_mmu_wrprot_slot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot,
			     पूर्णांक min_level);
bool kvm_tdp_mmu_clear_dirty_slot(काष्ठा kvm *kvm,
				  काष्ठा kvm_memory_slot *slot);
व्योम kvm_tdp_mmu_clear_dirty_pt_masked(काष्ठा kvm *kvm,
				       काष्ठा kvm_memory_slot *slot,
				       gfn_t gfn, अचिन्हित दीर्घ mask,
				       bool wrprot);
bool kvm_tdp_mmu_zap_collapsible_sptes(काष्ठा kvm *kvm,
				       स्थिर काष्ठा kvm_memory_slot *slot,
				       bool flush);

bool kvm_tdp_mmu_ग_लिखो_protect_gfn(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot, gfn_t gfn);

पूर्णांक kvm_tdp_mmu_get_walk(काष्ठा kvm_vcpu *vcpu, u64 addr, u64 *sptes,
			 पूर्णांक *root_level);

#अगर_घोषित CONFIG_X86_64
व्योम kvm_mmu_init_tdp_mmu(काष्ठा kvm *kvm);
व्योम kvm_mmu_uninit_tdp_mmu(काष्ठा kvm *kvm);
अटल अंतरभूत bool is_tdp_mmu_enabled(काष्ठा kvm *kvm) अणु वापस kvm->arch.tdp_mmu_enabled; पूर्ण
अटल अंतरभूत bool is_tdp_mmu_page(काष्ठा kvm_mmu_page *sp) अणु वापस sp->tdp_mmu_page; पूर्ण
#अन्यथा
अटल अंतरभूत व्योम kvm_mmu_init_tdp_mmu(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_mmu_uninit_tdp_mmu(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत bool is_tdp_mmu_enabled(काष्ठा kvm *kvm) अणु वापस false; पूर्ण
अटल अंतरभूत bool is_tdp_mmu_page(काष्ठा kvm_mmu_page *sp) अणु वापस false; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool is_tdp_mmu_root(काष्ठा kvm *kvm, hpa_t hpa)
अणु
	काष्ठा kvm_mmu_page *sp;

	अगर (!is_tdp_mmu_enabled(kvm))
		वापस false;
	अगर (WARN_ON(!VALID_PAGE(hpa)))
		वापस false;

	sp = to_shaकरोw_page(hpa);
	अगर (WARN_ON(!sp))
		वापस false;

	वापस is_tdp_mmu_page(sp) && sp->root_count;
पूर्ण

#पूर्ण_अगर /* __KVM_X86_MMU_TDP_MMU_H */
