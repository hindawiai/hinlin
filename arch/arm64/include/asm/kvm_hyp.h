<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM64_KVM_HYP_H__
#घोषणा __ARM64_KVM_HYP_H__

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/sysreg.h>

DECLARE_PER_CPU(काष्ठा kvm_cpu_context, kvm_hyp_ctxt);
DECLARE_PER_CPU(अचिन्हित दीर्घ, kvm_hyp_vector);
DECLARE_PER_CPU(काष्ठा kvm_nvhe_init_params, kvm_init_params);

#घोषणा पढ़ो_sysreg_elx(r,nvh,vh)					\
	(अणु								\
		u64 reg;						\
		यंत्र अस्थिर(ALTERNATIVE(__mrs_s("%0", r##nvh),	\
					 __mrs_s("%0", r##vh),		\
					 ARM64_HAS_VIRT_HOST_EXTN)	\
			     : "=r" (reg));				\
		reg;							\
	पूर्ण)

#घोषणा ग_लिखो_sysreg_elx(v,r,nvh,vh)					\
	करो अणु								\
		u64 __val = (u64)(v);					\
		यंत्र अस्थिर(ALTERNATIVE(__msr_s(r##nvh, "%x0"),	\
					 __msr_s(r##vh, "%x0"),		\
					 ARM64_HAS_VIRT_HOST_EXTN)	\
					 : : "rZ" (__val));		\
	पूर्ण जबतक (0)

/*
 * Unअगरied accessors क्रम रेजिस्टरs that have a dअगरferent encoding
 * between VHE and non-VHE. They must be specअगरied without their "ELx"
 * encoding, but with the SYS_ prefix, as defined in यंत्र/sysreg.h.
 */

#घोषणा पढ़ो_sysreg_el0(r)	पढ़ो_sysreg_elx(r, _EL0, _EL02)
#घोषणा ग_लिखो_sysreg_el0(v,r)	ग_लिखो_sysreg_elx(v, r, _EL0, _EL02)
#घोषणा पढ़ो_sysreg_el1(r)	पढ़ो_sysreg_elx(r, _EL1, _EL12)
#घोषणा ग_लिखो_sysreg_el1(v,r)	ग_लिखो_sysreg_elx(v, r, _EL1, _EL12)
#घोषणा पढ़ो_sysreg_el2(r)	पढ़ो_sysreg_elx(r, _EL2, _EL1)
#घोषणा ग_लिखो_sysreg_el2(v,r)	ग_लिखो_sysreg_elx(v, r, _EL2, _EL1)

/*
 * Without an __arch_swab32(), we fall back to ___स्थिरant_swab32(), but the
 * अटल अंतरभूत can allow the compiler to out-of-line this. KVM always wants
 * the macro version as its always अंतरभूतd.
 */
#घोषणा __kvm_swab32(x)	___स्थिरant_swab32(x)

पूर्णांक __vgic_v2_perक्रमm_cpuअगर_access(काष्ठा kvm_vcpu *vcpu);

व्योम __vgic_v3_save_state(काष्ठा vgic_v3_cpu_अगर *cpu_अगर);
व्योम __vgic_v3_restore_state(काष्ठा vgic_v3_cpu_अगर *cpu_अगर);
व्योम __vgic_v3_activate_traps(काष्ठा vgic_v3_cpu_अगर *cpu_अगर);
व्योम __vgic_v3_deactivate_traps(काष्ठा vgic_v3_cpu_अगर *cpu_अगर);
व्योम __vgic_v3_save_aprs(काष्ठा vgic_v3_cpu_अगर *cpu_अगर);
व्योम __vgic_v3_restore_aprs(काष्ठा vgic_v3_cpu_अगर *cpu_अगर);
पूर्णांक __vgic_v3_perक्रमm_cpuअगर_access(काष्ठा kvm_vcpu *vcpu);

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
व्योम __समयr_enable_traps(काष्ठा kvm_vcpu *vcpu);
व्योम __समयr_disable_traps(काष्ठा kvm_vcpu *vcpu);
#पूर्ण_अगर

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
व्योम __sysreg_save_state_nvhe(काष्ठा kvm_cpu_context *ctxt);
व्योम __sysreg_restore_state_nvhe(काष्ठा kvm_cpu_context *ctxt);
#अन्यथा
व्योम sysreg_save_host_state_vhe(काष्ठा kvm_cpu_context *ctxt);
व्योम sysreg_restore_host_state_vhe(काष्ठा kvm_cpu_context *ctxt);
व्योम sysreg_save_guest_state_vhe(काष्ठा kvm_cpu_context *ctxt);
व्योम sysreg_restore_guest_state_vhe(काष्ठा kvm_cpu_context *ctxt);
#पूर्ण_अगर

व्योम __debug_चयन_to_guest(काष्ठा kvm_vcpu *vcpu);
व्योम __debug_चयन_to_host(काष्ठा kvm_vcpu *vcpu);

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
व्योम __debug_save_host_buffers_nvhe(काष्ठा kvm_vcpu *vcpu);
व्योम __debug_restore_host_buffers_nvhe(काष्ठा kvm_vcpu *vcpu);
#पूर्ण_अगर

व्योम __fpsimd_save_state(काष्ठा user_fpsimd_state *fp_regs);
व्योम __fpsimd_restore_state(काष्ठा user_fpsimd_state *fp_regs);
व्योम __sve_save_state(व्योम *sve_pffr, u32 *fpsr);
व्योम __sve_restore_state(व्योम *sve_pffr, u32 *fpsr);

#अगर_अघोषित __KVM_NVHE_HYPERVISOR__
व्योम activate_traps_vhe_load(काष्ठा kvm_vcpu *vcpu);
व्योम deactivate_traps_vhe_put(व्योम);
#पूर्ण_अगर

u64 __guest_enter(काष्ठा kvm_vcpu *vcpu);

bool kvm_host_psci_handler(काष्ठा kvm_cpu_context *host_ctxt);

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
व्योम __noवापस __hyp_करो_panic(काष्ठा kvm_cpu_context *host_ctxt, u64 spsr,
			       u64 elr, u64 par);
#पूर्ण_अगर

#अगर_घोषित __KVM_NVHE_HYPERVISOR__
व्योम __pkvm_init_चयन_pgd(phys_addr_t phys, अचिन्हित दीर्घ size,
			    phys_addr_t pgd, व्योम *sp, व्योम *cont_fn);
पूर्णांक __pkvm_init(phys_addr_t phys, अचिन्हित दीर्घ size, अचिन्हित दीर्घ nr_cpus,
		अचिन्हित दीर्घ *per_cpu_base, u32 hyp_va_bits);
व्योम __noवापस __host_enter(काष्ठा kvm_cpu_context *host_ctxt);
#पूर्ण_अगर

बाह्य u64 kvm_nvhe_sym(id_aa64mmfr0_el1_sys_val);
बाह्य u64 kvm_nvhe_sym(id_aa64mmfr1_el1_sys_val);

#पूर्ण_अगर /* __ARM64_KVM_HYP_H__ */
