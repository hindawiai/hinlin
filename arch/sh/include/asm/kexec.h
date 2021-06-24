<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_KEXEC_H
#घोषणा __ASM_SH_KEXEC_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/माला.स>
#समावेश <linux/kernel.h>

/*
 * KEXEC_SOURCE_MEMORY_LIMIT maximum page get_मुक्त_page can वापस.
 * I.e. Maximum page that is mapped directly पूर्णांकo kernel memory,
 * and kmap is not required.
 *
 * Someone correct me अगर FIXADDR_START - PAGखातापूर्णFSET is not the correct
 * calculation क्रम the amount of memory directly mappable पूर्णांकo the
 * kernel memory space.
 */

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)
/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)
/* Maximum address we can use क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT TASK_SIZE

#घोषणा KEXEC_CONTROL_PAGE_SIZE	4096

/* The native architecture */
#घोषणा KEXEC_ARCH KEXEC_ARCH_SH

#अगर_घोषित CONFIG_KEXEC
/* arch/sh/kernel/machine_kexec.c */
व्योम reserve_crashkernel(व्योम);

अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
				    काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs)
		स_नकल(newregs, oldregs, माप(*newregs));
	अन्यथा अणु
		__यंत्र__ __अस्थिर__ ("mov r0, %0" : "=r" (newregs->regs[0]));
		__यंत्र__ __अस्थिर__ ("mov r1, %0" : "=r" (newregs->regs[1]));
		__यंत्र__ __अस्थिर__ ("mov r2, %0" : "=r" (newregs->regs[2]));
		__यंत्र__ __अस्थिर__ ("mov r3, %0" : "=r" (newregs->regs[3]));
		__यंत्र__ __अस्थिर__ ("mov r4, %0" : "=r" (newregs->regs[4]));
		__यंत्र__ __अस्थिर__ ("mov r5, %0" : "=r" (newregs->regs[5]));
		__यंत्र__ __अस्थिर__ ("mov r6, %0" : "=r" (newregs->regs[6]));
		__यंत्र__ __अस्थिर__ ("mov r7, %0" : "=r" (newregs->regs[7]));
		__यंत्र__ __अस्थिर__ ("mov r8, %0" : "=r" (newregs->regs[8]));
		__यंत्र__ __अस्थिर__ ("mov r9, %0" : "=r" (newregs->regs[9]));
		__यंत्र__ __अस्थिर__ ("mov r10, %0" : "=r" (newregs->regs[10]));
		__यंत्र__ __अस्थिर__ ("mov r11, %0" : "=r" (newregs->regs[11]));
		__यंत्र__ __अस्थिर__ ("mov r12, %0" : "=r" (newregs->regs[12]));
		__यंत्र__ __अस्थिर__ ("mov r13, %0" : "=r" (newregs->regs[13]));
		__यंत्र__ __अस्थिर__ ("mov r14, %0" : "=r" (newregs->regs[14]));
		__यंत्र__ __अस्थिर__ ("mov r15, %0" : "=r" (newregs->regs[15]));

		__यंत्र__ __अस्थिर__ ("sts pr, %0" : "=r" (newregs->pr));
		__यंत्र__ __अस्थिर__ ("sts macl, %0" : "=r" (newregs->macl));
		__यंत्र__ __अस्थिर__ ("sts mach, %0" : "=r" (newregs->mach));

		__यंत्र__ __अस्थिर__ ("stc gbr, %0" : "=r" (newregs->gbr));
		__यंत्र__ __अस्थिर__ ("stc sr, %0" : "=r" (newregs->sr));

		newregs->pc = _THIS_IP_;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम reserve_crashkernel(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC */

#पूर्ण_अगर /* __ASM_SH_KEXEC_H */
