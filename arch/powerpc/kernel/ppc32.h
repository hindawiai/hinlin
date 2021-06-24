<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _PPC64_PPC32_H
#घोषणा _PPC64_PPC32_H

#समावेश <linux/compat.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/संकेत.स>

/*
 * Data types and macros क्रम providing 32b PowerPC support.
 */

/* These are here to support 32-bit syscalls on a 64-bit kernel. */

काष्ठा pt_regs32 अणु
	अचिन्हित पूर्णांक gpr[32];
	अचिन्हित पूर्णांक nip;
	अचिन्हित पूर्णांक msr;
	अचिन्हित पूर्णांक orig_gpr3;		/* Used क्रम restarting प्रणाली calls */
	अचिन्हित पूर्णांक ctr;
	अचिन्हित पूर्णांक link;
	अचिन्हित पूर्णांक xer;
	अचिन्हित पूर्णांक ccr;
	अचिन्हित पूर्णांक mq;		/* 601 only (not used at present) */
	अचिन्हित पूर्णांक trap;		/* Reason क्रम being here */
	अचिन्हित पूर्णांक dar;		/* Fault रेजिस्टरs */
	अचिन्हित पूर्णांक dsisr;
	अचिन्हित पूर्णांक result;		/* Result of a प्रणाली call */
पूर्ण;

काष्ठा sigcontext32 अणु
	अचिन्हित पूर्णांक	_unused[4];
	पूर्णांक		संकेत;
	compat_uptr_t	handler;
	अचिन्हित पूर्णांक	oldmask;
	compat_uptr_t	regs;  /* 4 byte poपूर्णांकer to the pt_regs32 काष्ठाure. */
पूर्ण;

काष्ठा mcontext32 अणु
	elf_gregset_t32		mc_gregs;
	elf_fpregset_t		mc_fregs;
	अचिन्हित पूर्णांक		mc_pad[2];
	elf_vrregset_t32	mc_vregs __attribute__((__aligned__(16)));
	elf_vsrreghalf_t32      mc_vsregs __attribute__((__aligned__(16)));
पूर्ण;

काष्ठा ucontext32 अणु 
	अचिन्हित पूर्णांक	  	uc_flags;
	अचिन्हित पूर्णांक 	  	uc_link;
	compat_stack_t	 	uc_stack;
	पूर्णांक		 	uc_pad[7];
	compat_uptr_t		uc_regs;	/* poपूर्णांकs to uc_mcontext field */
	compat_sigset_t	 	uc_sigmask;	/* mask last क्रम extensibility */
	/* glibc has 1024-bit संकेत masks, ours are 64-bit */
	पूर्णांक		 	uc_maskext[30];
	पूर्णांक		 	uc_pad2[3];
	काष्ठा mcontext32	uc_mcontext;
पूर्ण;

#पूर्ण_अगर  /* _PPC64_PPC32_H */
