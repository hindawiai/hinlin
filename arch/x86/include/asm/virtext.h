<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* CPU भवization extensions handling
 *
 * This should carry the code क्रम handling CPU भवization extensions
 * that needs to live in the kernel core.
 *
 * Author: Eduarकरो Habkost <ehabkost@redhat.com>
 *
 * Copyright (C) 2008, Red Hat Inc.
 *
 * Contains code from KVM, Copyright (C) 2006 Qumranet, Inc.
 */
#अगर_अघोषित _ASM_X86_VIRTEX_H
#घोषणा _ASM_X86_VIRTEX_H

#समावेश <यंत्र/processor.h>

#समावेश <यंत्र/vmx.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/tlbflush.h>

/*
 * VMX functions:
 */

अटल अंतरभूत पूर्णांक cpu_has_vmx(व्योम)
अणु
	अचिन्हित दीर्घ ecx = cpuid_ecx(1);
	वापस test_bit(5, &ecx); /* CPUID.1:ECX.VMX[bit 5] -> VT */
पूर्ण


/**
 * cpu_vmxoff() - Disable VMX on the current CPU
 *
 * Disable VMX and clear CR4.VMXE (even अगर VMXOFF faults)
 *
 * Note, VMXOFF causes a #UD अगर the CPU is !post-VMXON, but it's impossible to
 * atomically track post-VMXON state, e.g. this may be called in NMI context.
 * Eat all faults as all other faults on VMXOFF faults are mode related, i.e.
 * faults are guaranteed to be due to the !post-VMXON check unless the CPU is
 * magically in RM, VM86, compat mode, or at CPL>0.
 */
अटल अंतरभूत पूर्णांक cpu_vmxoff(व्योम)
अणु
	यंत्र_अस्थिर_जाओ("1: vmxoff\n\t"
			  _ASM_EXTABLE(1b, %l[fault])
			  ::: "cc", "memory" : fault);

	cr4_clear_bits(X86_CR4_VMXE);
	वापस 0;

fault:
	cr4_clear_bits(X86_CR4_VMXE);
	वापस -EIO;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_vmx_enabled(व्योम)
अणु
	वापस __पढ़ो_cr4() & X86_CR4_VMXE;
पूर्ण

/** Disable VMX अगर it is enabled on the current CPU
 *
 * You shouldn't call this अगर cpu_has_vmx() वापसs 0.
 */
अटल अंतरभूत व्योम __cpu_emergency_vmxoff(व्योम)
अणु
	अगर (cpu_vmx_enabled())
		cpu_vmxoff();
पूर्ण

/** Disable VMX अगर it is supported and enabled on the current CPU
 */
अटल अंतरभूत व्योम cpu_emergency_vmxoff(व्योम)
अणु
	अगर (cpu_has_vmx())
		__cpu_emergency_vmxoff();
पूर्ण




/*
 * SVM functions:
 */

/** Check अगर the CPU has SVM support
 *
 * You can use the 'msg' arg to get a message describing the problem,
 * अगर the function वापसs zero. Simply pass शून्य अगर you are not पूर्णांकerested
 * on the messages; gcc should take care of not generating code क्रम
 * the messages on this हाल.
 */
अटल अंतरभूत पूर्णांक cpu_has_svm(स्थिर अक्षर **msg)
अणु
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON) अणु
		अगर (msg)
			*msg = "not amd or hygon";
		वापस 0;
	पूर्ण

	अगर (boot_cpu_data.extended_cpuid_level < SVM_CPUID_FUNC) अणु
		अगर (msg)
			*msg = "can't execute cpuid_8000000a";
		वापस 0;
	पूर्ण

	अगर (!boot_cpu_has(X86_FEATURE_SVM)) अणु
		अगर (msg)
			*msg = "svm not available";
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण


/** Disable SVM on the current CPU
 *
 * You should call this only अगर cpu_has_svm() वापसed true.
 */
अटल अंतरभूत व्योम cpu_svm_disable(व्योम)
अणु
	uपूर्णांक64_t efer;

	wrmsrl(MSR_VM_HSAVE_PA, 0);
	rdmsrl(MSR_EFER, efer);
	wrmsrl(MSR_EFER, efer & ~EFER_SVME);
पूर्ण

/** Makes sure SVM is disabled, अगर it is supported on the CPU
 */
अटल अंतरभूत व्योम cpu_emergency_svm_disable(व्योम)
अणु
	अगर (cpu_has_svm(शून्य))
		cpu_svm_disable();
पूर्ण

#पूर्ण_अगर /* _ASM_X86_VIRTEX_H */
