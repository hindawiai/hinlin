<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_UCONTEXT_H
#घोषणा _ASM_POWERPC_UCONTEXT_H

#अगर_घोषित __घातerpc64__
#समावेश <यंत्र/sigcontext.h>
#अन्यथा
#समावेश <यंत्र/elf.h>
#पूर्ण_अगर
#समावेश <यंत्र/संकेत.स>

#अगर_अघोषित __घातerpc64__
काष्ठा mcontext अणु
	elf_gregset_t	mc_gregs;
	elf_fpregset_t	mc_fregs;
	अचिन्हित दीर्घ	mc_pad[2];
	elf_vrregset_t	mc_vregs __attribute__((__aligned__(16)));
पूर्ण;
#पूर्ण_अगर

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	uc_flags;
	काष्ठा ucontext __user *uc_link;
	stack_t		uc_stack;
#अगर_अघोषित __घातerpc64__
	पूर्णांक		uc_pad[7];
	काष्ठा mcontext	__user *uc_regs;/* poपूर्णांकs to uc_mcontext field */
#पूर्ण_अगर
	sigset_t	uc_sigmask;
	/* glibc has 1024-bit संकेत masks, ours are 64-bit */
#अगर_घोषित __घातerpc64__
	sigset_t	__unused[15];	/* Allow क्रम uc_sigmask growth */
	काष्ठा sigcontext uc_mcontext;	/* last क्रम extensibility */
#अन्यथा
	पूर्णांक		uc_maskext[30];
	पूर्णांक		uc_pad2[3];
	काष्ठा mcontext	uc_mcontext;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* _ASM_POWERPC_UCONTEXT_H */
