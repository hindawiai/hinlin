<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ASM__VIRT_H
#घोषणा __ASM__VIRT_H

/*
 * The arm64 hcall implementation uses x0 to specअगरy the hcall
 * number. A value less than HVC_STUB_HCALL_NR indicates a special
 * hcall, such as set vector. Any other value is handled in a
 * hypervisor specअगरic way.
 *
 * The hypercall is allowed to clobber any of the caller-saved
 * रेजिस्टरs (x0-x18), so it is advisable to use it through the
 * indirection of a function call (as implemented in hyp-stub.S).
 */

/*
 * HVC_SET_VECTORS - Set the value of the vbar_el2 रेजिस्टर.
 *
 * @x1: Physical address of the new vector table.
 */
#घोषणा HVC_SET_VECTORS 0

/*
 * HVC_SOFT_RESTART - CPU soft reset, used by the cpu_soft_restart routine.
 */
#घोषणा HVC_SOFT_RESTART 1

/*
 * HVC_RESET_VECTORS - Restore the vectors to the original HYP stubs
 */
#घोषणा HVC_RESET_VECTORS 2

/*
 * HVC_VHE_RESTART - Upgrade the CPU from EL1 to EL2, अगर possible
 */
#घोषणा HVC_VHE_RESTART	3

/* Max number of HYP stub hypercalls */
#घोषणा HVC_STUB_HCALL_NR 4

/* Error वापसed when an invalid stub number is passed पूर्णांकo x0 */
#घोषणा HVC_STUB_ERR	0xbadca11

#घोषणा BOOT_CPU_MODE_EL1	(0xe11)
#घोषणा BOOT_CPU_MODE_EL2	(0xe12)

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/cpufeature.h>

/*
 * __boot_cpu_mode records what mode CPUs were booted in.
 * A correctly-implemented bootloader must start all CPUs in the same mode:
 * In this हाल, both 32bit halves of __boot_cpu_mode will contain the
 * same value (either 0 अगर booted in EL1, BOOT_CPU_MODE_EL2 अगर booted in EL2).
 *
 * Should the bootloader fail to करो this, the two values will be dअगरferent.
 * This allows the kernel to flag an error when the secondaries have come up.
 */
बाह्य u32 __boot_cpu_mode[2];

व्योम __hyp_set_vectors(phys_addr_t phys_vector_base);
व्योम __hyp_reset_vectors(व्योम);

DECLARE_STATIC_KEY_FALSE(kvm_रक्षित_mode_initialized);

/* Reports the availability of HYP mode */
अटल अंतरभूत bool is_hyp_mode_available(व्योम)
अणु
	/*
	 * If KVM रक्षित mode is initialized, all CPUs must have been booted
	 * in EL2. Aव्योम checking __boot_cpu_mode as CPUs now come up in EL1.
	 */
	अगर (IS_ENABLED(CONFIG_KVM) &&
	    अटल_branch_likely(&kvm_रक्षित_mode_initialized))
		वापस true;

	वापस (__boot_cpu_mode[0] == BOOT_CPU_MODE_EL2 &&
		__boot_cpu_mode[1] == BOOT_CPU_MODE_EL2);
पूर्ण

/* Check अगर the bootloader has booted CPUs in dअगरferent modes */
अटल अंतरभूत bool is_hyp_mode_mismatched(व्योम)
अणु
	/*
	 * If KVM रक्षित mode is initialized, all CPUs must have been booted
	 * in EL2. Aव्योम checking __boot_cpu_mode as CPUs now come up in EL1.
	 */
	अगर (IS_ENABLED(CONFIG_KVM) &&
	    अटल_branch_likely(&kvm_रक्षित_mode_initialized))
		वापस false;

	वापस __boot_cpu_mode[0] != __boot_cpu_mode[1];
पूर्ण

अटल अंतरभूत bool is_kernel_in_hyp_mode(व्योम)
अणु
	वापस पढ़ो_sysreg(CurrentEL) == CurrentEL_EL2;
पूर्ण

अटल __always_अंतरभूत bool has_vhe(व्योम)
अणु
	/*
	 * Code only run in VHE/NVHE hyp context can assume VHE is present or
	 * असलent. Otherwise fall back to caps.
	 */
	अगर (is_vhe_hyp_code())
		वापस true;
	अन्यथा अगर (is_nvhe_hyp_code())
		वापस false;
	अन्यथा
		वापस cpus_have_final_cap(ARM64_HAS_VIRT_HOST_EXTN);
पूर्ण

अटल __always_अंतरभूत bool is_रक्षित_kvm_enabled(व्योम)
अणु
	अगर (is_vhe_hyp_code())
		वापस false;
	अन्यथा
		वापस cpus_have_final_cap(ARM64_KVM_PROTECTED_MODE);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* ! __ASM__VIRT_H */
