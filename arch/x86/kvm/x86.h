<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_X86_KVM_X86_H
#घोषणा ARCH_X86_KVM_X86_H

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/pvघड़ी.h>
#समावेश "kvm_cache_regs.h"
#समावेश "kvm_emulate.h"

अटल __always_अंतरभूत व्योम kvm_guest_enter_irqoff(व्योम)
अणु
	/*
	 * VMENTER enables पूर्णांकerrupts (host state), but the kernel state is
	 * पूर्णांकerrupts disabled when this is invoked. Also tell RCU about
	 * it. This is the same logic as क्रम निकास_to_user_mode().
	 *
	 * This ensures that e.g. latency analysis on the host observes
	 * guest mode as पूर्णांकerrupt enabled.
	 *
	 * guest_enter_irqoff() inक्रमms context tracking about the
	 * transition to guest mode and अगर enabled adjusts RCU state
	 * accordingly.
	 */
	instrumentation_begin();
	trace_hardirqs_on_prepare();
	lockdep_hardirqs_on_prepare(CALLER_ADDR0);
	instrumentation_end();

	guest_enter_irqoff();
	lockdep_hardirqs_on(CALLER_ADDR0);
पूर्ण

अटल __always_अंतरभूत व्योम kvm_guest_निकास_irqoff(व्योम)
अणु
	/*
	 * VMEXIT disables पूर्णांकerrupts (host state), but tracing and lockdep
	 * have them in state 'on' as recorded beक्रमe entering guest mode.
	 * Same as enter_from_user_mode().
	 *
	 * context_tracking_guest_निकास() restores host context and reinstates
	 * RCU अगर enabled and required.
	 *
	 * This needs to be करोne immediately after VM-Exit, beक्रमe any code
	 * that might contain tracepoपूर्णांकs or call out to the greater world,
	 * e.g. beक्रमe x86_spec_ctrl_restore_host().
	 */
	lockdep_hardirqs_off(CALLER_ADDR0);
	context_tracking_guest_निकास();

	instrumentation_begin();
	trace_hardirqs_off_finish();
	instrumentation_end();
पूर्ण

#घोषणा KVM_NESTED_VMENTER_CONSISTENCY_CHECK(consistency_check)		\
(अणु									\
	bool failed = (consistency_check);				\
	अगर (failed)							\
		trace_kvm_nested_vmenter_failed(#consistency_check, 0);	\
	failed;								\
पूर्ण)

#घोषणा KVM_DEFAULT_PLE_GAP		128
#घोषणा KVM_VMX_DEFAULT_PLE_WINDOW	4096
#घोषणा KVM_DEFAULT_PLE_WINDOW_GROW	2
#घोषणा KVM_DEFAULT_PLE_WINDOW_SHRINK	0
#घोषणा KVM_VMX_DEFAULT_PLE_WINDOW_MAX	अच_पूर्णांक_उच्च
#घोषणा KVM_SVM_DEFAULT_PLE_WINDOW_MAX	अच_लघु_उच्च
#घोषणा KVM_SVM_DEFAULT_PLE_WINDOW	3000

अटल अंतरभूत अचिन्हित पूर्णांक __grow_ple_winकरोw(अचिन्हित पूर्णांक val,
		अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक modअगरier, अचिन्हित पूर्णांक max)
अणु
	u64 ret = val;

	अगर (modअगरier < 1)
		वापस base;

	अगर (modअगरier < base)
		ret *= modअगरier;
	अन्यथा
		ret += modअगरier;

	वापस min(ret, (u64)max);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __shrink_ple_winकरोw(अचिन्हित पूर्णांक val,
		अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक modअगरier, अचिन्हित पूर्णांक min)
अणु
	अगर (modअगरier < 1)
		वापस base;

	अगर (modअगरier < base)
		val /= modअगरier;
	अन्यथा
		val -= modअगरier;

	वापस max(val, min);
पूर्ण

#घोषणा MSR_IA32_CR_PAT_DEFAULT  0x0007040600070406ULL

पूर्णांक kvm_check_nested_events(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत व्योम kvm_clear_exception_queue(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.exception.pending = false;
	vcpu->arch.exception.injected = false;
पूर्ण

अटल अंतरभूत व्योम kvm_queue_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, u8 vector,
	bool soft)
अणु
	vcpu->arch.पूर्णांकerrupt.injected = true;
	vcpu->arch.पूर्णांकerrupt.soft = soft;
	vcpu->arch.पूर्णांकerrupt.nr = vector;
पूर्ण

अटल अंतरभूत व्योम kvm_clear_पूर्णांकerrupt_queue(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.पूर्णांकerrupt.injected = false;
पूर्ण

अटल अंतरभूत bool kvm_event_needs_reinjection(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.exception.injected || vcpu->arch.पूर्णांकerrupt.injected ||
		vcpu->arch.nmi_injected;
पूर्ण

अटल अंतरभूत bool kvm_exception_is_soft(अचिन्हित पूर्णांक nr)
अणु
	वापस (nr == BP_VECTOR) || (nr == OF_VECTOR);
पूर्ण

अटल अंतरभूत bool is_proपंचांगode(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr0_bits(vcpu, X86_CR0_PE);
पूर्ण

अटल अंतरभूत पूर्णांक is_दीर्घ_mode(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस vcpu->arch.efer & EFER_LMA;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool is_64_bit_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक cs_db, cs_l;

	अगर (!is_दीर्घ_mode(vcpu))
		वापस false;
	अटल_call(kvm_x86_get_cs_db_l_bits)(vcpu, &cs_db, &cs_l);
	वापस cs_l;
पूर्ण

अटल अंतरभूत bool is_la57_mode(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस (vcpu->arch.efer & EFER_LMA) &&
		 kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_LA57);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool x86_exception_has_error_code(अचिन्हित पूर्णांक vector)
अणु
	अटल u32 exception_has_error_code = BIT(DF_VECTOR) | BIT(TS_VECTOR) |
			BIT(NP_VECTOR) | BIT(SS_VECTOR) | BIT(GP_VECTOR) |
			BIT(PF_VECTOR) | BIT(AC_VECTOR);

	वापस (1U << vector) & exception_has_error_code;
पूर्ण

अटल अंतरभूत bool mmu_is_nested(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.walk_mmu == &vcpu->arch.nested_mmu;
पूर्ण

अटल अंतरभूत व्योम kvm_vcpu_flush_tlb_current(काष्ठा kvm_vcpu *vcpu)
अणु
	++vcpu->stat.tlb_flush;
	अटल_call(kvm_x86_tlb_flush_current)(vcpu);
पूर्ण

अटल अंतरभूत पूर्णांक is_pae(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PAE);
पूर्ण

अटल अंतरभूत पूर्णांक is_pse(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PSE);
पूर्ण

अटल अंतरभूत पूर्णांक is_paging(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस likely(kvm_पढ़ो_cr0_bits(vcpu, X86_CR0_PG));
पूर्ण

अटल अंतरभूत bool is_pae_paging(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !is_दीर्घ_mode(vcpu) && is_pae(vcpu) && is_paging(vcpu);
पूर्ण

अटल अंतरभूत u8 vcpu_virt_addr_bits(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_LA57) ? 57 : 48;
पूर्ण

अटल अंतरभूत u64 get_canonical(u64 la, u8 vaddr_bits)
अणु
	वापस ((पूर्णांक64_t)la << (64 - vaddr_bits)) >> (64 - vaddr_bits);
पूर्ण

अटल अंतरभूत bool is_noncanonical_address(u64 la, काष्ठा kvm_vcpu *vcpu)
अणु
	वापस get_canonical(la, vcpu_virt_addr_bits(vcpu)) != la;
पूर्ण

अटल अंतरभूत व्योम vcpu_cache_mmio_info(काष्ठा kvm_vcpu *vcpu,
					gva_t gva, gfn_t gfn, अचिन्हित access)
अणु
	u64 gen = kvm_memslots(vcpu->kvm)->generation;

	अगर (unlikely(gen & KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS))
		वापस;

	/*
	 * If this is a shaकरोw nested page table, the "GVA" is
	 * actually a nGPA.
	 */
	vcpu->arch.mmio_gva = mmu_is_nested(vcpu) ? 0 : gva & PAGE_MASK;
	vcpu->arch.mmio_access = access;
	vcpu->arch.mmio_gfn = gfn;
	vcpu->arch.mmio_gen = gen;
पूर्ण

अटल अंतरभूत bool vcpu_match_mmio_gen(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.mmio_gen == kvm_memslots(vcpu->kvm)->generation;
पूर्ण

/*
 * Clear the mmio cache info क्रम the given gva. If gva is MMIO_GVA_ANY, we
 * clear all mmio cache info.
 */
#घोषणा MMIO_GVA_ANY (~(gva_t)0)

अटल अंतरभूत व्योम vcpu_clear_mmio_info(काष्ठा kvm_vcpu *vcpu, gva_t gva)
अणु
	अगर (gva != MMIO_GVA_ANY && vcpu->arch.mmio_gva != (gva & PAGE_MASK))
		वापस;

	vcpu->arch.mmio_gva = 0;
पूर्ण

अटल अंतरभूत bool vcpu_match_mmio_gva(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva)
अणु
	अगर (vcpu_match_mmio_gen(vcpu) && vcpu->arch.mmio_gva &&
	      vcpu->arch.mmio_gva == (gva & PAGE_MASK))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool vcpu_match_mmio_gpa(काष्ठा kvm_vcpu *vcpu, gpa_t gpa)
अणु
	अगर (vcpu_match_mmio_gen(vcpu) && vcpu->arch.mmio_gfn &&
	      vcpu->arch.mmio_gfn == gpa >> PAGE_SHIFT)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_रेजिस्टर_पढ़ो(काष्ठा kvm_vcpu *vcpu, पूर्णांक reg)
अणु
	अचिन्हित दीर्घ val = kvm_रेजिस्टर_पढ़ो_raw(vcpu, reg);

	वापस is_64_bit_mode(vcpu) ? val : (u32)val;
पूर्ण

अटल अंतरभूत व्योम kvm_रेजिस्टर_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				       पूर्णांक reg, अचिन्हित दीर्घ val)
अणु
	अगर (!is_64_bit_mode(vcpu))
		val = (u32)val;
	वापस kvm_रेजिस्टर_ग_लिखो_raw(vcpu, reg, val);
पूर्ण

अटल अंतरभूत bool kvm_check_has_quirk(काष्ठा kvm *kvm, u64 quirk)
अणु
	वापस !(kvm->arch.disabled_quirks & quirk);
पूर्ण

अटल अंतरभूत bool kvm_vcpu_latch_init(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस is_smm(vcpu) || अटल_call(kvm_x86_apic_init_संकेत_blocked)(vcpu);
पूर्ण

व्योम kvm_ग_लिखो_wall_घड़ी(काष्ठा kvm *kvm, gpa_t wall_घड़ी, पूर्णांक sec_hi_ofs);
व्योम kvm_inject_realmode_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, पूर्णांक irq, पूर्णांक inc_eip);

u64 get_kvmघड़ी_ns(काष्ठा kvm *kvm);

पूर्णांक kvm_पढ़ो_guest_virt(काष्ठा kvm_vcpu *vcpu,
	gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
	काष्ठा x86_exception *exception);

पूर्णांक kvm_ग_लिखो_guest_virt_प्रणाली(काष्ठा kvm_vcpu *vcpu,
	gva_t addr, व्योम *val, अचिन्हित पूर्णांक bytes,
	काष्ठा x86_exception *exception);

पूर्णांक handle_ud(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_deliver_exception_payload(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_vcpu_mtrr_init(काष्ठा kvm_vcpu *vcpu);
u8 kvm_mtrr_get_guest_memory_type(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
bool kvm_mtrr_valid(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data);
पूर्णांक kvm_mtrr_set_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data);
पूर्णांक kvm_mtrr_get_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata);
bool kvm_mtrr_check_gfn_range_consistency(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
					  पूर्णांक page_num);
bool kvm_vector_hashing_enabled(व्योम);
व्योम kvm_fixup_and_inject_pf_error(काष्ठा kvm_vcpu *vcpu, gva_t gva, u16 error_code);
पूर्णांक x86_decode_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, पूर्णांक emulation_type,
				    व्योम *insn, पूर्णांक insn_len);
पूर्णांक x86_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa,
			    पूर्णांक emulation_type, व्योम *insn, पूर्णांक insn_len);
fastpath_t handle_fastpath_set_msr_irqoff(काष्ठा kvm_vcpu *vcpu);

बाह्य u64 host_xcr0;
बाह्य u64 supported_xcr0;
बाह्य u64 host_xss;
बाह्य u64 supported_xss;

अटल अंतरभूत bool kvm_mpx_supported(व्योम)
अणु
	वापस (supported_xcr0 & (XFEATURE_MASK_BNDREGS | XFEATURE_MASK_BNDCSR))
		== (XFEATURE_MASK_BNDREGS | XFEATURE_MASK_BNDCSR);
पूर्ण

बाह्य अचिन्हित पूर्णांक min_समयr_period_us;

बाह्य bool enable_vmware_backकरोor;

बाह्य पूर्णांक pi_inject_समयr;

बाह्य काष्ठा अटल_key kvm_no_apic_vcpu;

बाह्य bool report_ignored_msrs;

अटल अंतरभूत u64 nsec_to_cycles(काष्ठा kvm_vcpu *vcpu, u64 nsec)
अणु
	वापस pvघड़ी_scale_delta(nsec, vcpu->arch.भव_tsc_mult,
				   vcpu->arch.भव_tsc_shअगरt);
पूर्ण

/* Same "calling convention" as करो_भाग:
 * - भागide (n << 32) by base
 * - put result in n
 * - वापस reमुख्यder
 */
#घोषणा करो_shl32_भाग32(n, base)					\
	(अणु							\
	    u32 __quot, __rem;					\
	    यंत्र("divl %2" : "=a" (__quot), "=d" (__rem)		\
			: "rm" (base), "0" (0), "1" ((u32) n));	\
	    n = __quot;						\
	    __rem;						\
	 पूर्ण)

अटल अंतरभूत bool kvm_mरुको_in_guest(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.mरुको_in_guest;
पूर्ण

अटल अंतरभूत bool kvm_hlt_in_guest(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.hlt_in_guest;
पूर्ण

अटल अंतरभूत bool kvm_छोड़ो_in_guest(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.छोड़ो_in_guest;
पूर्ण

अटल अंतरभूत bool kvm_cstate_in_guest(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.cstate_in_guest;
पूर्ण

DECLARE_PER_CPU(काष्ठा kvm_vcpu *, current_vcpu);

अटल अंतरभूत व्योम kvm_beक्रमe_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	__this_cpu_ग_लिखो(current_vcpu, vcpu);
पूर्ण

अटल अंतरभूत व्योम kvm_after_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	__this_cpu_ग_लिखो(current_vcpu, शून्य);
पूर्ण


अटल अंतरभूत bool kvm_pat_valid(u64 data)
अणु
	अगर (data & 0xF8F8F8F8F8F8F8F8ull)
		वापस false;
	/* 0, 1, 4, 5, 6, 7 are valid values.  */
	वापस (data | ((data & 0x0202020202020202ull) << 1)) == data;
पूर्ण

अटल अंतरभूत bool kvm_dr7_valid(u64 data)
अणु
	/* Bits [63:32] are reserved */
	वापस !(data >> 32);
पूर्ण
अटल अंतरभूत bool kvm_dr6_valid(u64 data)
अणु
	/* Bits [63:32] are reserved */
	वापस !(data >> 32);
पूर्ण

/*
 * Trigger machine check on the host. We assume all the MSRs are alपढ़ोy set up
 * by the CPU and that we still run on the same CPU as the MCE occurred on.
 * We pass a fake environment to the machine check handler because we want
 * the guest to be always treated like user space, no matter what context
 * it used पूर्णांकernally.
 */
अटल अंतरभूत व्योम kvm_machine_check(व्योम)
अणु
#अगर defined(CONFIG_X86_MCE)
	काष्ठा pt_regs regs = अणु
		.cs = 3, /* Fake ring 3 no matter what the guest ran on */
		.flags = X86_EFLAGS_IF,
	पूर्ण;

	करो_machine_check(&regs);
#पूर्ण_अगर
पूर्ण

व्योम kvm_load_guest_xsave_state(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_load_host_xsave_state(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_spec_ctrl_test_value(u64 value);
bool kvm_is_valid_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4);
पूर्णांक kvm_handle_memory_failure(काष्ठा kvm_vcpu *vcpu, पूर्णांक r,
			      काष्ठा x86_exception *e);
पूर्णांक kvm_handle_invpcid(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ type, gva_t gva);
bool kvm_msr_allowed(काष्ठा kvm_vcpu *vcpu, u32 index, u32 type);

/*
 * Internal error codes that are used to indicate that MSR emulation encountered
 * an error that should result in #GP in the guest, unless userspace
 * handles it.
 */
#घोषणा  KVM_MSR_RET_INVALID	2	/* in-kernel MSR emulation #GP condition */
#घोषणा  KVM_MSR_RET_FILTERED	3	/* #GP due to userspace MSR filter */

#घोषणा __cr4_reserved_bits(__cpu_has, __c)             \
(अणु                                                      \
	u64 __reserved_bits = CR4_RESERVED_BITS;        \
                                                        \
	अगर (!__cpu_has(__c, X86_FEATURE_XSAVE))         \
		__reserved_bits |= X86_CR4_OSXSAVE;     \
	अगर (!__cpu_has(__c, X86_FEATURE_SMEP))          \
		__reserved_bits |= X86_CR4_SMEP;        \
	अगर (!__cpu_has(__c, X86_FEATURE_SMAP))          \
		__reserved_bits |= X86_CR4_SMAP;        \
	अगर (!__cpu_has(__c, X86_FEATURE_FSGSBASE))      \
		__reserved_bits |= X86_CR4_FSGSBASE;    \
	अगर (!__cpu_has(__c, X86_FEATURE_PKU))           \
		__reserved_bits |= X86_CR4_PKE;         \
	अगर (!__cpu_has(__c, X86_FEATURE_LA57))          \
		__reserved_bits |= X86_CR4_LA57;        \
	अगर (!__cpu_has(__c, X86_FEATURE_UMIP))          \
		__reserved_bits |= X86_CR4_UMIP;        \
	अगर (!__cpu_has(__c, X86_FEATURE_VMX))           \
		__reserved_bits |= X86_CR4_VMXE;        \
	अगर (!__cpu_has(__c, X86_FEATURE_PCID))          \
		__reserved_bits |= X86_CR4_PCIDE;       \
	__reserved_bits;                                \
पूर्ण)

पूर्णांक kvm_sev_es_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gpa_t src, अचिन्हित पूर्णांक bytes,
			  व्योम *dst);
पूर्णांक kvm_sev_es_mmio_पढ़ो(काष्ठा kvm_vcpu *vcpu, gpa_t src, अचिन्हित पूर्णांक bytes,
			 व्योम *dst);
पूर्णांक kvm_sev_es_string_io(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक size,
			 अचिन्हित पूर्णांक port, व्योम *data,  अचिन्हित पूर्णांक count,
			 पूर्णांक in);

#पूर्ण_अगर
