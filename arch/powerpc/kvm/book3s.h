<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright IBM Corporation, 2013
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 */

#अगर_अघोषित __POWERPC_KVM_BOOK3S_H__
#घोषणा __POWERPC_KVM_BOOK3S_H__

बाह्य व्योम kvmppc_core_flush_memslot_hv(काष्ठा kvm *kvm,
					 काष्ठा kvm_memory_slot *memslot);
बाह्य bool kvm_unmap_gfn_range_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
बाह्य bool kvm_age_gfn_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
बाह्य bool kvm_test_age_gfn_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
बाह्य bool kvm_set_spte_gfn_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);

बाह्य पूर्णांक kvmppc_mmu_init_pr(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_mmu_destroy_pr(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_core_emulate_op_pr(काष्ठा kvm_vcpu *vcpu,
				     अचिन्हित पूर्णांक inst, पूर्णांक *advance);
बाह्य पूर्णांक kvmppc_core_emulate_mtspr_pr(काष्ठा kvm_vcpu *vcpu,
					पूर्णांक sprn, uदीर्घ spr_val);
बाह्य पूर्णांक kvmppc_core_emulate_mfspr_pr(काष्ठा kvm_vcpu *vcpu,
					पूर्णांक sprn, uदीर्घ *spr_val);
बाह्य पूर्णांक kvmppc_book3s_init_pr(व्योम);
बाह्य व्योम kvmppc_book3s_निकास_pr(व्योम);

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
बाह्य व्योम kvmppc_emulate_tपात(काष्ठा kvm_vcpu *vcpu, पूर्णांक ra_val);
#अन्यथा
अटल अंतरभूत व्योम kvmppc_emulate_tपात(काष्ठा kvm_vcpu *vcpu, पूर्णांक ra_val) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम kvmppc_set_msr_hv(काष्ठा kvm_vcpu *vcpu, u64 msr);
बाह्य व्योम kvmppc_inject_पूर्णांकerrupt_hv(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 srr1_flags);

#पूर्ण_अगर
