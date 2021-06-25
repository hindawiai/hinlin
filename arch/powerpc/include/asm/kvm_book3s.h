<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright SUSE Linux Products GmbH 2009
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#अगर_अघोषित __ASM_KVM_BOOK3S_H__
#घोषणा __ASM_KVM_BOOK3S_H__

#समावेश <linux/types.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_book3s_यंत्र.h>

काष्ठा kvmppc_bat अणु
	u64 raw;
	u32 bepi;
	u32 bepi_mask;
	u32 brpn;
	u8 wimg;
	u8 pp;
	bool vs		: 1;
	bool vp		: 1;
पूर्ण;

काष्ठा kvmppc_sid_map अणु
	u64 guest_vsid;
	u64 guest_esid;
	u64 host_vsid;
	bool valid	: 1;
पूर्ण;

#घोषणा SID_MAP_BITS    9
#घोषणा SID_MAP_NUM     (1 << SID_MAP_BITS)
#घोषणा SID_MAP_MASK    (SID_MAP_NUM - 1)

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#घोषणा SID_CONTEXTS	1
#अन्यथा
#घोषणा SID_CONTEXTS	128
#घोषणा VSID_POOL_SIZE	(SID_CONTEXTS * 16)
#पूर्ण_अगर

काष्ठा hpte_cache अणु
	काष्ठा hlist_node list_pte;
	काष्ठा hlist_node list_pte_दीर्घ;
	काष्ठा hlist_node list_vpte;
	काष्ठा hlist_node list_vpte_दीर्घ;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा hlist_node list_vpte_64k;
#पूर्ण_अगर
	काष्ठा rcu_head rcu_head;
	u64 host_vpn;
	u64 pfn;
	uदीर्घ slot;
	काष्ठा kvmppc_pte pte;
	पूर्णांक pagesize;
पूर्ण;

/*
 * Struct क्रम a भव core.
 * Note: entry_निकास_map combines a biपंचांगap of thपढ़ोs that have entered
 * in the bottom 8 bits and a biपंचांगap of thपढ़ोs that have निकासed in the
 * next 8 bits.  This is so that we can atomically set the entry bit
 * अगरf the निकास map is 0 without taking a lock.
 */
काष्ठा kvmppc_vcore अणु
	पूर्णांक n_runnable;
	पूर्णांक num_thपढ़ोs;
	पूर्णांक entry_निकास_map;
	पूर्णांक napping_thपढ़ोs;
	पूर्णांक first_vcpuid;
	u16 pcpu;
	u16 last_cpu;
	u8 vcore_state;
	u8 in_guest;
	काष्ठा kvm_vcpu *runnable_thपढ़ोs[MAX_SMT_THREADS];
	काष्ठा list_head preempt_list;
	spinlock_t lock;
	काष्ठा rcuरुको रुको;
	spinlock_t stoltb_lock;	/* protects stolen_tb and preempt_tb */
	u64 stolen_tb;
	u64 preempt_tb;
	काष्ठा kvm_vcpu *runner;
	काष्ठा kvm *kvm;
	u64 tb_offset;		/* guest समयbase - host समयbase */
	u64 tb_offset_applied;	/* समयbase offset currently in क्रमce */
	uदीर्घ lpcr;
	u32 arch_compat;
	uदीर्घ pcr;
	uदीर्घ dpdes;		/* करोorbell state (POWER8) */
	uदीर्घ vtb;		/* भव समयbase */
	uदीर्घ conferring_thपढ़ोs;
	अचिन्हित पूर्णांक halt_poll_ns;
	atomic_t online_count;
पूर्ण;

काष्ठा kvmppc_vcpu_book3s अणु
	काष्ठा kvmppc_sid_map sid_map[SID_MAP_NUM];
	काष्ठा अणु
		u64 esid;
		u64 vsid;
	पूर्ण slb_shaकरोw[64];
	u8 slb_shaकरोw_max;
	काष्ठा kvmppc_bat ibat[8];
	काष्ठा kvmppc_bat dbat[8];
	u64 hid[6];
	u64 gqr[8];
	u64 sdr1;
	u64 hior;
	u64 msr_mask;
	u64 vtb;
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	u32 vsid_pool[VSID_POOL_SIZE];
	u32 vsid_next;
#अन्यथा
	u64 proto_vsid_first;
	u64 proto_vsid_max;
	u64 proto_vsid_next;
#पूर्ण_अगर
	पूर्णांक context_id[SID_CONTEXTS];

	bool hior_explicit;		/* HIOR is set by ioctl, not PVR */

	काष्ठा hlist_head hpte_hash_pte[HPTEG_HASH_NUM_PTE];
	काष्ठा hlist_head hpte_hash_pte_दीर्घ[HPTEG_HASH_NUM_PTE_LONG];
	काष्ठा hlist_head hpte_hash_vpte[HPTEG_HASH_NUM_VPTE];
	काष्ठा hlist_head hpte_hash_vpte_दीर्घ[HPTEG_HASH_NUM_VPTE_LONG];
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा hlist_head hpte_hash_vpte_64k[HPTEG_HASH_NUM_VPTE_64K];
#पूर्ण_अगर
	पूर्णांक hpte_cache_count;
	spinlock_t mmu_lock;
पूर्ण;

#घोषणा VSID_REAL	0x07ffffffffc00000ULL
#घोषणा VSID_BAT	0x07ffffffffb00000ULL
#घोषणा VSID_64K	0x0800000000000000ULL
#घोषणा VSID_1T		0x1000000000000000ULL
#घोषणा VSID_REAL_DR	0x2000000000000000ULL
#घोषणा VSID_REAL_IR	0x4000000000000000ULL
#घोषणा VSID_PR		0x8000000000000000ULL

बाह्य व्योम kvmppc_mmu_pte_flush(काष्ठा kvm_vcpu *vcpu, uदीर्घ ea, uदीर्घ ea_mask);
बाह्य व्योम kvmppc_mmu_pte_vflush(काष्ठा kvm_vcpu *vcpu, u64 vp, u64 vp_mask);
बाह्य व्योम kvmppc_mmu_pte_pflush(काष्ठा kvm_vcpu *vcpu, uदीर्घ pa_start, uदीर्घ pa_end);
बाह्य व्योम kvmppc_set_msr(काष्ठा kvm_vcpu *vcpu, u64 new_msr);
बाह्य व्योम kvmppc_mmu_book3s_64_init(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_mmu_book3s_32_init(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_mmu_book3s_hv_init(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_mmu_map_page(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *pte,
			       bool isग_लिखो);
बाह्य व्योम kvmppc_mmu_unmap_page(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *pte);
बाह्य पूर्णांक kvmppc_mmu_map_segment(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr);
बाह्य व्योम kvmppc_mmu_flush_segment(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr, uदीर्घ seg_size);
बाह्य व्योम kvmppc_mmu_flush_segments(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_book3s_hv_page_fault(काष्ठा kvm_vcpu *vcpu,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ status);
बाह्य दीर्घ kvmppc_hv_find_lock_hpte(काष्ठा kvm *kvm, gva_t eaddr,
			अचिन्हित दीर्घ slb_v, अचिन्हित दीर्घ valid);
बाह्य पूर्णांक kvmppc_hv_emulate_mmio(काष्ठा kvm_vcpu *vcpu,
			अचिन्हित दीर्घ gpa, gva_t ea, पूर्णांक is_store);

बाह्य व्योम kvmppc_mmu_hpte_cache_map(काष्ठा kvm_vcpu *vcpu, काष्ठा hpte_cache *pte);
बाह्य काष्ठा hpte_cache *kvmppc_mmu_hpte_cache_next(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_mmu_hpte_cache_मुक्त(काष्ठा hpte_cache *pte);
बाह्य व्योम kvmppc_mmu_hpte_destroy(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_mmu_hpte_init(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_mmu_invalidate_pte(काष्ठा kvm_vcpu *vcpu, काष्ठा hpte_cache *pte);
बाह्य पूर्णांक kvmppc_mmu_hpte_sysinit(व्योम);
बाह्य व्योम kvmppc_mmu_hpte_sysनिकास(व्योम);
बाह्य पूर्णांक kvmppc_mmu_hv_init(व्योम);
बाह्य पूर्णांक kvmppc_book3s_hcall_implemented(काष्ठा kvm *kvm, अचिन्हित दीर्घ hc);

बाह्य पूर्णांक kvmppc_book3s_radix_page_fault(काष्ठा kvm_vcpu *vcpu,
			अचिन्हित दीर्घ ea, अचिन्हित दीर्घ dsisr);
बाह्य अचिन्हित दीर्घ __kvmhv_copy_tofrom_guest_radix(पूर्णांक lpid, पूर्णांक pid,
					gva_t eaddr, व्योम *to, व्योम *from,
					अचिन्हित दीर्घ n);
बाह्य दीर्घ kvmhv_copy_from_guest_radix(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
					व्योम *to, अचिन्हित दीर्घ n);
बाह्य दीर्घ kvmhv_copy_to_guest_radix(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				      व्योम *from, अचिन्हित दीर्घ n);
बाह्य पूर्णांक kvmppc_mmu_walk_radix_tree(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				      काष्ठा kvmppc_pte *gpte, u64 root,
				      u64 *pte_ret_p);
बाह्य पूर्णांक kvmppc_mmu_radix_translate_table(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
			काष्ठा kvmppc_pte *gpte, u64 table,
			पूर्णांक table_index, u64 *pte_ret_p);
बाह्य पूर्णांक kvmppc_mmu_radix_xlate(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
			काष्ठा kvmppc_pte *gpte, bool data, bool isग_लिखो);
बाह्य व्योम kvmppc_radix_tlbie_page(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr,
				    अचिन्हित पूर्णांक pshअगरt, अचिन्हित पूर्णांक lpid);
बाह्य व्योम kvmppc_unmap_pte(काष्ठा kvm *kvm, pte_t *pte, अचिन्हित दीर्घ gpa,
			अचिन्हित पूर्णांक shअगरt,
			स्थिर काष्ठा kvm_memory_slot *memslot,
			अचिन्हित पूर्णांक lpid);
बाह्य bool kvmppc_hv_handle_set_rc(काष्ठा kvm *kvm, bool nested,
				    bool writing, अचिन्हित दीर्घ gpa,
				    अचिन्हित पूर्णांक lpid);
बाह्य पूर्णांक kvmppc_book3s_instantiate_page(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित दीर्घ gpa,
				काष्ठा kvm_memory_slot *memslot,
				bool writing, bool kvm_ro,
				pte_t *inserted_pte, अचिन्हित पूर्णांक *levelp);
बाह्य पूर्णांक kvmppc_init_vm_radix(काष्ठा kvm *kvm);
बाह्य व्योम kvmppc_मुक्त_radix(काष्ठा kvm *kvm);
बाह्य व्योम kvmppc_मुक्त_pgtable_radix(काष्ठा kvm *kvm, pgd_t *pgd,
				      अचिन्हित पूर्णांक lpid);
बाह्य पूर्णांक kvmppc_radix_init(व्योम);
बाह्य व्योम kvmppc_radix_निकास(व्योम);
बाह्य व्योम kvm_unmap_radix(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			    अचिन्हित दीर्घ gfn);
बाह्य bool kvm_age_radix(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			  अचिन्हित दीर्घ gfn);
बाह्य bool kvm_test_age_radix(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			       अचिन्हित दीर्घ gfn);
बाह्य दीर्घ kvmppc_hv_get_dirty_log_radix(काष्ठा kvm *kvm,
			काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ *map);
बाह्य व्योम kvmppc_radix_flush_memslot(काष्ठा kvm *kvm,
			स्थिर काष्ठा kvm_memory_slot *memslot);
बाह्य पूर्णांक kvmhv_get_rmmu_info(काष्ठा kvm *kvm, काष्ठा kvm_ppc_rmmu_info *info);

/* XXX हटाओ this export when load_last_inst() is generic */
बाह्य पूर्णांक kvmppc_ld(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, पूर्णांक size, व्योम *ptr, bool data);
बाह्य व्योम kvmppc_book3s_queue_irqprio(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक vec);
बाह्य व्योम kvmppc_book3s_dequeue_irqprio(काष्ठा kvm_vcpu *vcpu,
					  अचिन्हित पूर्णांक vec);
बाह्य व्योम kvmppc_inject_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 flags);
बाह्य व्योम kvmppc_trigger_fac_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac);
बाह्य व्योम kvmppc_set_bat(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_bat *bat,
			   bool upper, u32 val);
बाह्य व्योम kvmppc_giveup_ext(काष्ठा kvm_vcpu *vcpu, uदीर्घ msr);
बाह्य पूर्णांक kvmppc_emulate_paired_single(काष्ठा kvm_vcpu *vcpu);
बाह्य kvm_pfn_t kvmppc_gpa_to_pfn(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			bool writing, bool *writable);
बाह्य व्योम kvmppc_add_revmap_chain(काष्ठा kvm *kvm, काष्ठा revmap_entry *rev,
			अचिन्हित दीर्घ *rmap, दीर्घ pte_index, पूर्णांक realmode);
बाह्य व्योम kvmppc_update_dirty_map(स्थिर काष्ठा kvm_memory_slot *memslot,
			अचिन्हित दीर्घ gfn, अचिन्हित दीर्घ psize);
बाह्य व्योम kvmppc_invalidate_hpte(काष्ठा kvm *kvm, __be64 *hptep,
			अचिन्हित दीर्घ pte_index);
व्योम kvmppc_clear_ref_hpte(काष्ठा kvm *kvm, __be64 *hptep,
			अचिन्हित दीर्घ pte_index);
बाह्य व्योम *kvmppc_pin_guest_page(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ *nb_ret);
बाह्य व्योम kvmppc_unpin_guest_page(काष्ठा kvm *kvm, व्योम *addr,
			अचिन्हित दीर्घ gpa, bool dirty);
बाह्य दीर्घ kvmppc_करो_h_enter(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags,
			दीर्घ pte_index, अचिन्हित दीर्घ pteh, अचिन्हित दीर्घ ptel,
			pgd_t *pgdir, bool realmode, अचिन्हित दीर्घ *idx_ret);
बाह्य दीर्घ kvmppc_करो_h_हटाओ(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ pte_index, अचिन्हित दीर्घ avpn,
			अचिन्हित दीर्घ *hpret);
बाह्य दीर्घ kvmppc_hv_get_dirty_log_hpt(काष्ठा kvm *kvm,
			काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ *map);
बाह्य व्योम kvmppc_harvest_vpa_dirty(काष्ठा kvmppc_vpa *vpa,
			काष्ठा kvm_memory_slot *memslot,
			अचिन्हित दीर्घ *map);
बाह्य अचिन्हित दीर्घ kvmppc_filter_lpcr_hv(काष्ठा kvm *kvm,
			अचिन्हित दीर्घ lpcr);
बाह्य व्योम kvmppc_update_lpcr(काष्ठा kvm *kvm, अचिन्हित दीर्घ lpcr,
			अचिन्हित दीर्घ mask);
बाह्य व्योम kvmppc_set_fscr(काष्ठा kvm_vcpu *vcpu, u64 fscr);

बाह्य पूर्णांक kvmhv_p9_पंचांग_emulation_early(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmhv_p9_पंचांग_emulation(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmhv_emulate_पंचांग_rollback(काष्ठा kvm_vcpu *vcpu);

बाह्य व्योम kvmppc_entry_trampoline(व्योम);
बाह्य व्योम kvmppc_hv_entry_trampoline(व्योम);
बाह्य u32 kvmppc_alignment_dsisr(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक inst);
बाह्य uदीर्घ kvmppc_alignment_dar(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक inst);
बाह्य पूर्णांक kvmppc_h_pr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cmd);
बाह्य व्योम kvmppc_pr_init_शेष_hcalls(काष्ठा kvm *kvm);
बाह्य पूर्णांक kvmppc_hcall_impl_pr(अचिन्हित दीर्घ cmd);
बाह्य पूर्णांक kvmppc_hcall_impl_hv_realmode(अचिन्हित दीर्घ cmd);
बाह्य व्योम kvmppc_copy_to_svcpu(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_copy_from_svcpu(काष्ठा kvm_vcpu *vcpu);

दीर्घ kvmppc_पढ़ो_पूर्णांकr(व्योम);
व्योम kvmppc_bad_पूर्णांकerrupt(काष्ठा pt_regs *regs);
व्योम kvmhv_p9_set_lpcr(काष्ठा kvm_split_mode *sip);
व्योम kvmhv_p9_restore_lpcr(काष्ठा kvm_split_mode *sip);
व्योम kvmppc_set_msr_hv(काष्ठा kvm_vcpu *vcpu, u64 msr);
व्योम kvmppc_inject_पूर्णांकerrupt_hv(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 srr1_flags);

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
व्योम kvmppc_save_पंचांग_pr(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_restore_पंचांग_pr(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_save_पंचांग_sprs(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_restore_पंचांग_sprs(काष्ठा kvm_vcpu *vcpu);
#अन्यथा
अटल अंतरभूत व्योम kvmppc_save_पंचांग_pr(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_restore_पंचांग_pr(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_save_पंचांग_sprs(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_restore_पंचांग_sprs(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
#पूर्ण_अगर

दीर्घ kvmhv_nested_init(व्योम);
व्योम kvmhv_nested_निकास(व्योम);
व्योम kvmhv_vm_nested_init(काष्ठा kvm *kvm);
दीर्घ kvmhv_set_partition_table(काष्ठा kvm_vcpu *vcpu);
दीर्घ kvmhv_copy_tofrom_guest_nested(काष्ठा kvm_vcpu *vcpu);
व्योम kvmhv_set_ptbl_entry(अचिन्हित पूर्णांक lpid, u64 dw0, u64 dw1);
व्योम kvmhv_release_all_nested(काष्ठा kvm *kvm);
दीर्घ kvmhv_enter_nested_guest(काष्ठा kvm_vcpu *vcpu);
दीर्घ kvmhv_करो_nested_tlbie(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvmhv_run_single_vcpu(काष्ठा kvm_vcpu *vcpu,
			  u64 समय_limit, अचिन्हित दीर्घ lpcr);
व्योम kvmhv_save_hv_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा hv_guest_state *hr);
व्योम kvmhv_restore_hv_वापस_state(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा hv_guest_state *hr);
दीर्घ पूर्णांक kvmhv_nested_page_fault(काष्ठा kvm_vcpu *vcpu);

व्योम kvmppc_giveup_fac(काष्ठा kvm_vcpu *vcpu, uदीर्घ fac);

बाह्य पूर्णांक kvm_irq_bypass;

अटल अंतरभूत काष्ठा kvmppc_vcpu_book3s *to_book3s(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.book3s;
पूर्ण

/* Also add subarch specअगरic defines */

#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
#समावेश <यंत्र/kvm_book3s_32.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_64_HANDLER
#समावेश <यंत्र/kvm_book3s_64.h>
#पूर्ण_अगर

अटल अंतरभूत व्योम kvmppc_set_gpr(काष्ठा kvm_vcpu *vcpu, पूर्णांक num, uदीर्घ val)
अणु
	vcpu->arch.regs.gpr[num] = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_gpr(काष्ठा kvm_vcpu *vcpu, पूर्णांक num)
अणु
	वापस vcpu->arch.regs.gpr[num];
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_cr(काष्ठा kvm_vcpu *vcpu, u32 val)
अणु
	vcpu->arch.regs.ccr = val;
पूर्ण

अटल अंतरभूत u32 kvmppc_get_cr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.ccr;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_xer(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.xer = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_xer(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.xer;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_ctr(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.ctr = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_ctr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.ctr;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_lr(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.link = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_lr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.link;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_pc(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)
अणु
	vcpu->arch.regs.nip = val;
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_pc(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.regs.nip;
पूर्ण

अटल अंतरभूत u64 kvmppc_get_msr(काष्ठा kvm_vcpu *vcpu);
अटल अंतरभूत bool kvmppc_need_byteswap(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (kvmppc_get_msr(vcpu) & MSR_LE) != (MSR_KERNEL & MSR_LE);
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_fault_dar(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.fault_dar;
पूर्ण

अटल अंतरभूत bool is_kvmppc_resume_guest(पूर्णांक r)
अणु
	वापस (r == RESUME_GUEST || r == RESUME_GUEST_NV);
पूर्ण

अटल अंतरभूत bool is_kvmppc_hv_enabled(काष्ठा kvm *kvm);
अटल अंतरभूत bool kvmppc_supports_magic_page(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Only PR KVM supports the magic page */
	वापस !is_kvmppc_hv_enabled(vcpu->kvm);
पूर्ण

बाह्य पूर्णांक kvmppc_h_logical_ci_load(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_h_logical_ci_store(काष्ठा kvm_vcpu *vcpu);

/* Magic रेजिस्टर values loaded पूर्णांकo r3 and r4 beक्रमe the 'sc' assembly
 * inकाष्ठाion क्रम the OSI hypercalls */
#घोषणा OSI_SC_MAGIC_R3			0x113724FA
#घोषणा OSI_SC_MAGIC_R4			0x77810F9B

#घोषणा INS_DCBZ			0x7c0007ec
/* TO = 31 क्रम unconditional trap */
#घोषणा INS_TW				0x7fe00008

#घोषणा SPLIT_HACK_MASK			0xff000000
#घोषणा SPLIT_HACK_OFFS			0xfb000000

/*
 * This packs a VCPU ID from the [0..KVM_MAX_VCPU_ID) space करोwn to the
 * [0..KVM_MAX_VCPUS) space, using knowledge of the guest's core stride
 * (but not its actual thपढ़ोing mode, which is not available) to aव्योम
 * collisions.
 *
 * The implementation leaves VCPU IDs from the range [0..KVM_MAX_VCPUS) (block
 * 0) unchanged: अगर the guest is filling each VCORE completely then it will be
 * using consecutive IDs and it will fill the space without any packing.
 *
 * For higher VCPU IDs, the packed ID is based on the VCPU ID modulo
 * KVM_MAX_VCPUS (effectively masking off the top bits) and then an offset is
 * added to aव्योम collisions.
 *
 * VCPU IDs in the range [KVM_MAX_VCPUS..(KVM_MAX_VCPUS*2)) (block 1) are only
 * possible अगर the guest is leaving at least 1/2 of each VCORE empty, so IDs
 * can be safely packed पूर्णांकo the second half of each VCORE by adding an offset
 * of (stride / 2).
 *
 * Similarly, अगर VCPU IDs in the range [(KVM_MAX_VCPUS*2)..(KVM_MAX_VCPUS*4))
 * (blocks 2 and 3) are seen, the guest must be leaving at least 3/4 of each
 * VCORE empty so packed IDs can be offset by (stride / 4) and (stride * 3 / 4).
 *
 * Finally, VCPU IDs from blocks 5..7 will only be seen अगर the guest is using a
 * stride of 8 and 1 thपढ़ो per core so the reमुख्यing offsets of 1, 5, 3 and 7
 * must be मुक्त to use.
 *
 * (The offsets क्रम each block are stored in block_offsets[], indexed by the
 * block number अगर the stride is 8. For हालs where the guest's stride is less
 * than 8, we can re-use the block_offsets array by multiplying the block
 * number by (MAX_SMT_THREADS / stride) to reach the correct entry.)
 */
अटल अंतरभूत u32 kvmppc_pack_vcpu_id(काष्ठा kvm *kvm, u32 id)
अणु
	स्थिर पूर्णांक block_offsets[MAX_SMT_THREADS] = अणु0, 4, 2, 6, 1, 5, 3, 7पूर्ण;
	पूर्णांक stride = kvm->arch.emul_smt_mode;
	पूर्णांक block = (id / KVM_MAX_VCPUS) * (MAX_SMT_THREADS / stride);
	u32 packed_id;

	अगर (WARN_ONCE(block >= MAX_SMT_THREADS, "VCPU ID too large to pack"))
		वापस 0;
	packed_id = (id % KVM_MAX_VCPUS) + block_offsets[block];
	अगर (WARN_ONCE(packed_id >= KVM_MAX_VCPUS, "VCPU ID packing failed"))
		वापस 0;
	वापस packed_id;
पूर्ण

#पूर्ण_अगर /* __ASM_KVM_BOOK3S_H__ */
