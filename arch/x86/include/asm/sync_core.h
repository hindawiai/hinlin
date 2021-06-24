<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SYNC_CORE_H
#घोषणा _ASM_X86_SYNC_CORE_H

#समावेश <linux/preempt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/special_insns.h>

#अगर_घोषित CONFIG_X86_32
अटल अंतरभूत व्योम iret_to_self(व्योम)
अणु
	यंत्र अस्थिर (
		"pushfl\n\t"
		"pushl %%cs\n\t"
		"pushl $1f\n\t"
		"iret\n\t"
		"1:"
		: ASM_CALL_CONSTRAINT : : "memory");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम iret_to_self(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	यंत्र अस्थिर (
		"mov %%ss, %0\n\t"
		"pushq %q0\n\t"
		"pushq %%rsp\n\t"
		"addq $8, (%%rsp)\n\t"
		"pushfq\n\t"
		"mov %%cs, %0\n\t"
		"pushq %q0\n\t"
		"pushq $1f\n\t"
		"iretq\n\t"
		"1:"
		: "=&r" (पंचांगp), ASM_CALL_CONSTRAINT : : "cc", "memory");
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */

/*
 * This function क्रमces the icache and prefetched inकाष्ठाion stream to
 * catch up with reality in two very specअगरic हालs:
 *
 *  a) Text was modअगरied using one भव address and is about to be executed
 *     from the same physical page at a dअगरferent भव address.
 *
 *  b) Text was modअगरied on a dअगरferent CPU, may subsequently be
 *     executed on this CPU, and you want to make sure the new version
 *     माला_लो executed.  This generally means you're calling this in an IPI.
 *
 * If you're calling this for a different reason, you're probably करोing
 * it wrong.
 *
 * Like all of Linux's memory ordering operations, this is a
 * compiler barrier as well.
 */
अटल अंतरभूत व्योम sync_core(व्योम)
अणु
	/*
	 * The SERIALIZE inकाष्ठाion is the most straightक्रमward way to
	 * करो this, but it is not universally available.
	 */
	अगर (अटल_cpu_has(X86_FEATURE_SERIALIZE)) अणु
		serialize();
		वापस;
	पूर्ण

	/*
	 * For all other processors, there are quite a few ways to करो this.
	 * IRET-to-self is nice because it works on every CPU, at any CPL
	 * (so it's compatible with paraभवization), and it never निकासs
	 * to a hypervisor.  The only करोwnsides are that it's a bit slow
	 * (it seems to be a bit more than 2x slower than the fastest
	 * options) and that it unmasks NMIs.  The "push %cs" is needed,
	 * because in paraभव environments __KERNEL_CS may not be a
	 * valid CS value when we करो IRET directly.
	 *
	 * In हाल NMI unmasking or perक्रमmance ever becomes a problem,
	 * the next best option appears to be MOV-to-CR2 and an
	 * unconditional jump.  That sequence also works on all CPUs,
	 * but it will fault at CPL3 (i.e. Xen PV).
	 *
	 * CPUID is the conventional way, but it's nasty: it doesn't
	 * exist on some 486-like CPUs, and it usually निकासs to a
	 * hypervisor.
	 */
	iret_to_self();
पूर्ण

/*
 * Ensure that a core serializing inकाष्ठाion is issued beक्रमe वापसing
 * to user-mode. x86 implements वापस to user-space through sysनिकास,
 * sysrel, and sysretq, which are not core serializing.
 */
अटल अंतरभूत व्योम sync_core_beक्रमe_usermode(व्योम)
अणु
	/* With PTI, we unconditionally serialize beक्रमe running user code. */
	अगर (अटल_cpu_has(X86_FEATURE_PTI))
		वापस;

	/*
	 * Even अगर we're in an पूर्णांकerrupt, we might reschedule beक्रमe वापसing,
	 * in which हाल we could चयन to a dअगरferent thपढ़ो in the same mm
	 * and वापस using SYSRET or SYSEXIT.  Instead of trying to keep
	 * track of our need to sync the core, just sync right away.
	 */
	sync_core();
पूर्ण

#पूर्ण_अगर /* _ASM_X86_SYNC_CORE_H */
