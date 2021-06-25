<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM_KVM_ASM_H__
#घोषणा __ARM_KVM_ASM_H__

#समावेश <यंत्र/hyp_image.h>
#समावेश <यंत्र/virt.h>

#घोषणा ARM_EXIT_WITH_SERROR_BIT  31
#घोषणा ARM_EXCEPTION_CODE(x)	  ((x) & ~(1U << ARM_EXIT_WITH_SERROR_BIT))
#घोषणा ARM_EXCEPTION_IS_TRAP(x)  (ARM_EXCEPTION_CODE((x)) == ARM_EXCEPTION_TRAP)
#घोषणा ARM_SERROR_PENDING(x)	  !!((x) & (1U << ARM_EXIT_WITH_SERROR_BIT))

#घोषणा ARM_EXCEPTION_IRQ	  0
#घोषणा ARM_EXCEPTION_EL1_SERROR  1
#घोषणा ARM_EXCEPTION_TRAP	  2
#घोषणा ARM_EXCEPTION_IL	  3
/* The hyp-stub will वापस this क्रम any kvm_call_hyp() call */
#घोषणा ARM_EXCEPTION_HYP_GONE	  HVC_STUB_ERR

#घोषणा kvm_arm_exception_type					\
	अणुARM_EXCEPTION_IRQ,		"IRQ"		पूर्ण,	\
	अणुARM_EXCEPTION_EL1_SERROR, 	"SERROR"	पूर्ण,	\
	अणुARM_EXCEPTION_TRAP, 		"TRAP"		पूर्ण,	\
	अणुARM_EXCEPTION_HYP_GONE,	"HYP_GONE"	पूर्ण

/*
 * Size of the HYP vectors preamble. kvm_patch_vector_branch() generates code
 * that jumps over this.
 */
#घोषणा KVM_VECTOR_PREAMBLE	(2 * AARCH64_INSN_SIZE)

#घोषणा KVM_HOST_SMCCC_ID(id)						\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_64,				\
			   ARM_SMCCC_OWNER_VENDOR_HYP,			\
			   (id))

#घोषणा KVM_HOST_SMCCC_FUNC(name) KVM_HOST_SMCCC_ID(__KVM_HOST_SMCCC_FUNC_##name)

#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_hyp_init			0
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_vcpu_run			1
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_flush_vm_context		2
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_tlb_flush_vmid_ipa		3
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_tlb_flush_vmid		4
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_flush_cpu_context		5
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_समयr_set_cntvoff		6
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_enable_ssbs			7
#घोषणा __KVM_HOST_SMCCC_FUNC___vgic_v3_get_gic_config		8
#घोषणा __KVM_HOST_SMCCC_FUNC___vgic_v3_पढ़ो_vmcr		9
#घोषणा __KVM_HOST_SMCCC_FUNC___vgic_v3_ग_लिखो_vmcr		10
#घोषणा __KVM_HOST_SMCCC_FUNC___vgic_v3_init_lrs		11
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_get_mdcr_el2		12
#घोषणा __KVM_HOST_SMCCC_FUNC___vgic_v3_save_aprs		13
#घोषणा __KVM_HOST_SMCCC_FUNC___vgic_v3_restore_aprs		14
#घोषणा __KVM_HOST_SMCCC_FUNC___pkvm_init			15
#घोषणा __KVM_HOST_SMCCC_FUNC___pkvm_create_mappings		16
#घोषणा __KVM_HOST_SMCCC_FUNC___pkvm_create_निजी_mapping	17
#घोषणा __KVM_HOST_SMCCC_FUNC___pkvm_cpu_set_vector		18
#घोषणा __KVM_HOST_SMCCC_FUNC___pkvm_prot_finalize		19
#घोषणा __KVM_HOST_SMCCC_FUNC___pkvm_mark_hyp			20
#घोषणा __KVM_HOST_SMCCC_FUNC___kvm_adjust_pc			21

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/mm.h>

#घोषणा DECLARE_KVM_VHE_SYM(sym)	बाह्य अक्षर sym[]
#घोषणा DECLARE_KVM_NVHE_SYM(sym)	बाह्य अक्षर kvm_nvhe_sym(sym)[]

/*
 * Define a pair of symbols sharing the same name but one defined in
 * VHE and the other in nVHE hyp implementations.
 */
#घोषणा DECLARE_KVM_HYP_SYM(sym)		\
	DECLARE_KVM_VHE_SYM(sym);		\
	DECLARE_KVM_NVHE_SYM(sym)

#घोषणा DECLARE_KVM_VHE_PER_CPU(type, sym)	\
	DECLARE_PER_CPU(type, sym)
#घोषणा DECLARE_KVM_NVHE_PER_CPU(type, sym)	\
	DECLARE_PER_CPU(type, kvm_nvhe_sym(sym))

#घोषणा DECLARE_KVM_HYP_PER_CPU(type, sym)	\
	DECLARE_KVM_VHE_PER_CPU(type, sym);	\
	DECLARE_KVM_NVHE_PER_CPU(type, sym)

/*
 * Compute poपूर्णांकer to a symbol defined in nVHE percpu region.
 * Returns शून्य अगर percpu memory has not been allocated yet.
 */
#घोषणा this_cpu_ptr_nvhe_sym(sym)	per_cpu_ptr_nvhe_sym(sym, smp_processor_id())
#घोषणा per_cpu_ptr_nvhe_sym(sym, cpu)						\
	(अणु									\
		अचिन्हित दीर्घ base, off;					\
		base = kvm_arm_hyp_percpu_base[cpu];				\
		off = (अचिन्हित दीर्घ)&CHOOSE_NVHE_SYM(sym) -			\
		      (अचिन्हित दीर्घ)&CHOOSE_NVHE_SYM(__per_cpu_start);		\
		base ? (typeof(CHOOSE_NVHE_SYM(sym))*)(base + off) : शून्य;	\
	पूर्ण)

#अगर defined(__KVM_NVHE_HYPERVISOR__)

#घोषणा CHOOSE_NVHE_SYM(sym)	sym
#घोषणा CHOOSE_HYP_SYM(sym)	CHOOSE_NVHE_SYM(sym)

/* The nVHE hypervisor shouldn't even try to access VHE symbols */
बाह्य व्योम *__nvhe_undefined_symbol;
#घोषणा CHOOSE_VHE_SYM(sym)		__nvhe_undefined_symbol
#घोषणा this_cpu_ptr_hyp_sym(sym)	(&__nvhe_undefined_symbol)
#घोषणा per_cpu_ptr_hyp_sym(sym, cpu)	(&__nvhe_undefined_symbol)

#या_अगर defined(__KVM_VHE_HYPERVISOR__)

#घोषणा CHOOSE_VHE_SYM(sym)	sym
#घोषणा CHOOSE_HYP_SYM(sym)	CHOOSE_VHE_SYM(sym)

/* The VHE hypervisor shouldn't even try to access nVHE symbols */
बाह्य व्योम *__vhe_undefined_symbol;
#घोषणा CHOOSE_NVHE_SYM(sym)		__vhe_undefined_symbol
#घोषणा this_cpu_ptr_hyp_sym(sym)	(&__vhe_undefined_symbol)
#घोषणा per_cpu_ptr_hyp_sym(sym, cpu)	(&__vhe_undefined_symbol)

#अन्यथा

/*
 * BIG FAT WARNINGS:
 *
 * - Don't be tempted to change the following is_kernel_in_hyp_mode()
 *   to has_vhe(). has_vhe() is implemented as a *final* capability,
 *   जबतक this is used early at boot समय, when the capabilities are
 *   not final yet....
 *
 * - Don't let the nVHE hypervisor have access to this, as it will
 *   pick the *wrong* symbol (yes, it runs at EL2...).
 */
#घोषणा CHOOSE_HYP_SYM(sym)		(is_kernel_in_hyp_mode()	\
					   ? CHOOSE_VHE_SYM(sym)	\
					   : CHOOSE_NVHE_SYM(sym))

#घोषणा this_cpu_ptr_hyp_sym(sym)	(is_kernel_in_hyp_mode()	\
					   ? this_cpu_ptr(&sym)		\
					   : this_cpu_ptr_nvhe_sym(sym))

#घोषणा per_cpu_ptr_hyp_sym(sym, cpu)	(is_kernel_in_hyp_mode()	\
					   ? per_cpu_ptr(&sym, cpu)	\
					   : per_cpu_ptr_nvhe_sym(sym, cpu))

#घोषणा CHOOSE_VHE_SYM(sym)	sym
#घोषणा CHOOSE_NVHE_SYM(sym)	kvm_nvhe_sym(sym)

#पूर्ण_अगर

काष्ठा kvm_nvhe_init_params अणु
	अचिन्हित दीर्घ mair_el2;
	अचिन्हित दीर्घ tcr_el2;
	अचिन्हित दीर्घ tpidr_el2;
	अचिन्हित दीर्घ stack_hyp_va;
	phys_addr_t pgd_pa;
	अचिन्हित दीर्घ hcr_el2;
	अचिन्हित दीर्घ vttbr;
	अचिन्हित दीर्घ vtcr;
पूर्ण;

/* Translate a kernel address @ptr पूर्णांकo its equivalent linear mapping */
#घोषणा kvm_ksym_ref(ptr)						\
	(अणु								\
		व्योम *val = (ptr);					\
		अगर (!is_kernel_in_hyp_mode())				\
			val = lm_alias((ptr));				\
		val;							\
	 पूर्ण)
#घोषणा kvm_ksym_ref_nvhe(sym)	kvm_ksym_ref(kvm_nvhe_sym(sym))

काष्ठा kvm;
काष्ठा kvm_vcpu;
काष्ठा kvm_s2_mmu;

DECLARE_KVM_NVHE_SYM(__kvm_hyp_init);
DECLARE_KVM_HYP_SYM(__kvm_hyp_vector);
#घोषणा __kvm_hyp_init		CHOOSE_NVHE_SYM(__kvm_hyp_init)
#घोषणा __kvm_hyp_vector	CHOOSE_HYP_SYM(__kvm_hyp_vector)

बाह्य अचिन्हित दीर्घ kvm_arm_hyp_percpu_base[NR_CPUS];
DECLARE_KVM_NVHE_SYM(__per_cpu_start);
DECLARE_KVM_NVHE_SYM(__per_cpu_end);

DECLARE_KVM_HYP_SYM(__bp_harden_hyp_vecs);
#घोषणा __bp_harden_hyp_vecs	CHOOSE_HYP_SYM(__bp_harden_hyp_vecs)

बाह्य व्योम __kvm_flush_vm_context(व्योम);
बाह्य व्योम __kvm_flush_cpu_context(काष्ठा kvm_s2_mmu *mmu);
बाह्य व्योम __kvm_tlb_flush_vmid_ipa(काष्ठा kvm_s2_mmu *mmu, phys_addr_t ipa,
				     पूर्णांक level);
बाह्य व्योम __kvm_tlb_flush_vmid(काष्ठा kvm_s2_mmu *mmu);

बाह्य व्योम __kvm_समयr_set_cntvoff(u64 cntvoff);

बाह्य पूर्णांक __kvm_vcpu_run(काष्ठा kvm_vcpu *vcpu);

बाह्य व्योम __kvm_adjust_pc(काष्ठा kvm_vcpu *vcpu);

बाह्य u64 __vgic_v3_get_gic_config(व्योम);
बाह्य u64 __vgic_v3_पढ़ो_vmcr(व्योम);
बाह्य व्योम __vgic_v3_ग_लिखो_vmcr(u32 vmcr);
बाह्य व्योम __vgic_v3_init_lrs(व्योम);

बाह्य u32 __kvm_get_mdcr_el2(व्योम);

#घोषणा __KVM_EXTABLE(from, to)						\
	"	.pushsection	__kvm_ex_table, \"a\"\n"		\
	"	.align		3\n"					\
	"	.long		(" #from " - .), (" #to " - .)\n"	\
	"	.popsection\n"


#घोषणा __kvm_at(at_op, addr)						\
( अणु 									\
	पूर्णांक __kvm_at_err = 0;						\
	u64 spsr, elr;							\
	यंत्र अस्थिर(							\
	"	mrs	%1, spsr_el2\n"					\
	"	mrs	%2, elr_el2\n"					\
	"1:	at	"at_op", %3\n"					\
	"	isb\n"							\
	"	b	9f\n"						\
	"2:	msr	spsr_el2, %1\n"					\
	"	msr	elr_el2, %2\n"					\
	"	mov	%w0, %4\n"					\
	"9:\n"								\
	__KVM_EXTABLE(1b, 2b)						\
	: "+r" (__kvm_at_err), "=&r" (spsr), "=&r" (elr)		\
	: "r" (addr), "i" (-EFAULT));					\
	__kvm_at_err;							\
पूर्ण )


#अन्यथा /* __ASSEMBLY__ */

.macro get_host_ctxt reg, पंचांगp
	adr_this_cpu \लeg, kvm_host_data, \टmp
	add	\लeg, \लeg, #HOST_DATA_CONTEXT
.endm

.macro get_vcpu_ptr vcpu, ctxt
	get_host_ctxt \ctxt, \खcpu
	ldr	\खcpu, [\ctxt, #HOST_CONTEXT_VCPU]
.endm

.macro get_loaded_vcpu vcpu, ctxt
	adr_this_cpu \ctxt, kvm_hyp_ctxt, \खcpu
	ldr	\खcpu, [\ctxt, #HOST_CONTEXT_VCPU]
.endm

.macro set_loaded_vcpu vcpu, ctxt, पंचांगp
	adr_this_cpu \ctxt, kvm_hyp_ctxt, \टmp
	str	\खcpu, [\ctxt, #HOST_CONTEXT_VCPU]
.endm

/*
 * KVM extable क्रम unexpected exceptions.
 * In the same क्रमmat _यंत्र_extable, but output to a dअगरferent section so that
 * it can be mapped to EL2. The KVM version is not sorted. The caller must
 * ensure:
 * x18 has the hypervisor value to allow any Shaकरोw-Call-Stack instrumented
 * code to ग_लिखो to it, and that SPSR_EL2 and ELR_EL2 are restored by the fixup.
 */
.macro	_kvm_extable, from, to
	.pushsection	__kvm_ex_table, "a"
	.align		3
	.दीर्घ		(\पrom - .), (\टo - .)
	.popsection
.endm

#घोषणा CPU_XREG_OFFSET(x)	(CPU_USER_PT_REGS + 8*x)
#घोषणा CPU_LR_OFFSET		CPU_XREG_OFFSET(30)
#घोषणा CPU_SP_EL0_OFFSET	(CPU_LR_OFFSET + 8)

/*
 * We treat x18 as callee-saved as the host may use it as a platक्रमm
 * रेजिस्टर (e.g. क्रम shaकरोw call stack).
 */
.macro save_callee_saved_regs ctxt
	str	x18,      [\ctxt, #CPU_XREG_OFFSET(18)]
	stp	x19, x20, [\ctxt, #CPU_XREG_OFFSET(19)]
	stp	x21, x22, [\ctxt, #CPU_XREG_OFFSET(21)]
	stp	x23, x24, [\ctxt, #CPU_XREG_OFFSET(23)]
	stp	x25, x26, [\ctxt, #CPU_XREG_OFFSET(25)]
	stp	x27, x28, [\ctxt, #CPU_XREG_OFFSET(27)]
	stp	x29, lr,  [\ctxt, #CPU_XREG_OFFSET(29)]
.endm

.macro restore_callee_saved_regs ctxt
	// We require \ctxt is not x18-x28
	ldr	x18,      [\ctxt, #CPU_XREG_OFFSET(18)]
	ldp	x19, x20, [\ctxt, #CPU_XREG_OFFSET(19)]
	ldp	x21, x22, [\ctxt, #CPU_XREG_OFFSET(21)]
	ldp	x23, x24, [\ctxt, #CPU_XREG_OFFSET(23)]
	ldp	x25, x26, [\ctxt, #CPU_XREG_OFFSET(25)]
	ldp	x27, x28, [\ctxt, #CPU_XREG_OFFSET(27)]
	ldp	x29, lr,  [\ctxt, #CPU_XREG_OFFSET(29)]
.endm

.macro save_sp_el0 ctxt, पंचांगp
	mrs	\टmp,	sp_el0
	str	\टmp,	[\ctxt, #CPU_SP_EL0_OFFSET]
.endm

.macro restore_sp_el0 ctxt, पंचांगp
	ldr	\टmp,	  [\ctxt, #CPU_SP_EL0_OFFSET]
	msr	sp_el0, \टmp
.endm

#पूर्ण_अगर

#पूर्ण_अगर /* __ARM_KVM_ASM_H__ */
