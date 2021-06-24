<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ACRN_H
#घोषणा _ASM_X86_ACRN_H

/*
 * This CPUID वापसs feature biपंचांगaps in EAX.
 * Guest VM uses this to detect the appropriate feature bit.
 */
#घोषणा	ACRN_CPUID_FEATURES		0x40000001
/* Bit 0 indicates whether guest VM is privileged */
#घोषणा	ACRN_FEATURE_PRIVILEGED_VM	BIT(0)

व्योम acrn_setup_पूर्णांकr_handler(व्योम (*handler)(व्योम));
व्योम acrn_हटाओ_पूर्णांकr_handler(व्योम);

अटल अंतरभूत u32 acrn_cpuid_base(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस hypervisor_cpuid_base("ACRNACRNACRN", 0);

	वापस 0;
पूर्ण

/*
 * Hypercalls क्रम ACRN
 *
 * - VMCALL inकाष्ठाion is used to implement ACRN hypercalls.
 * - ACRN hypercall ABI:
 *   - Hypercall number is passed in R8 रेजिस्टर.
 *   - Up to 2 arguments are passed in RDI, RSI.
 *   - Return value will be placed in RAX.
 *
 * Because GCC करोesn't support R8 रेजिस्टर as direct रेजिस्टर स्थिरraपूर्णांकs, use
 * supported स्थिरraपूर्णांक as input with a explicit MOV to R8 in beginning of यंत्र.
 */
अटल अंतरभूत दीर्घ acrn_hypercall0(अचिन्हित दीर्घ hcall_id)
अणु
	दीर्घ result;

	यंत्र अस्थिर("movl %1, %%r8d\n\t"
		     "vmcall\n\t"
		     : "=a" (result)
		     : "g" (hcall_id)
		     : "r8", "memory");

	वापस result;
पूर्ण

अटल अंतरभूत दीर्घ acrn_hypercall1(अचिन्हित दीर्घ hcall_id,
				   अचिन्हित दीर्घ param1)
अणु
	दीर्घ result;

	यंत्र अस्थिर("movl %1, %%r8d\n\t"
		     "vmcall\n\t"
		     : "=a" (result)
		     : "g" (hcall_id), "D" (param1)
		     : "r8", "memory");

	वापस result;
पूर्ण

अटल अंतरभूत दीर्घ acrn_hypercall2(अचिन्हित दीर्घ hcall_id,
				   अचिन्हित दीर्घ param1,
				   अचिन्हित दीर्घ param2)
अणु
	दीर्घ result;

	यंत्र अस्थिर("movl %1, %%r8d\n\t"
		     "vmcall\n\t"
		     : "=a" (result)
		     : "g" (hcall_id), "D" (param1), "S" (param2)
		     : "r8", "memory");

	वापस result;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_ACRN_H */
