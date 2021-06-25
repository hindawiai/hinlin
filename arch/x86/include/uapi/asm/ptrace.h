<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_PTRACE_H
#घोषणा _UAPI_ASM_X86_PTRACE_H

#समावेश <linux/compiler.h>	/* For __user */
#समावेश <यंत्र/ptrace-abi.h>
#समावेश <यंत्र/processor-flags.h>


#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित __i386__
/* this काष्ठा defines the way the रेजिस्टरs are stored on the
   stack during a प्रणाली call. */

#अगर_अघोषित __KERNEL__

काष्ठा pt_regs अणु
	दीर्घ ebx;
	दीर्घ ecx;
	दीर्घ edx;
	दीर्घ esi;
	दीर्घ edi;
	दीर्घ ebp;
	दीर्घ eax;
	पूर्णांक  xds;
	पूर्णांक  xes;
	पूर्णांक  xfs;
	पूर्णांक  xgs;
	दीर्घ orig_eax;
	दीर्घ eip;
	पूर्णांक  xcs;
	दीर्घ eflags;
	दीर्घ esp;
	पूर्णांक  xss;
पूर्ण;

#पूर्ण_अगर /* __KERNEL__ */

#अन्यथा /* __i386__ */

#अगर_अघोषित __KERNEL__

काष्ठा pt_regs अणु
/*
 * C ABI says these regs are callee-preserved. They aren't saved on kernel entry
 * unless syscall needs a complete, fully filled "struct pt_regs".
 */
	अचिन्हित दीर्घ r15;
	अचिन्हित दीर्घ r14;
	अचिन्हित दीर्घ r13;
	अचिन्हित दीर्घ r12;
	अचिन्हित दीर्घ rbp;
	अचिन्हित दीर्घ rbx;
/* These regs are callee-clobbered. Always saved on kernel entry. */
	अचिन्हित दीर्घ r11;
	अचिन्हित दीर्घ r10;
	अचिन्हित दीर्घ r9;
	अचिन्हित दीर्घ r8;
	अचिन्हित दीर्घ rax;
	अचिन्हित दीर्घ rcx;
	अचिन्हित दीर्घ rdx;
	अचिन्हित दीर्घ rsi;
	अचिन्हित दीर्घ rdi;
/*
 * On syscall entry, this is syscall#. On CPU exception, this is error code.
 * On hw पूर्णांकerrupt, it's IRQ number:
 */
	अचिन्हित दीर्घ orig_rax;
/* Return frame क्रम iretq */
	अचिन्हित दीर्घ rip;
	अचिन्हित दीर्घ cs;
	अचिन्हित दीर्घ eflags;
	अचिन्हित दीर्घ rsp;
	अचिन्हित दीर्घ ss;
/* top of stack page */
पूर्ण;

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* !__i386__ */



#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_ASM_X86_PTRACE_H */
