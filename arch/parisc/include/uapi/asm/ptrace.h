<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* written by Philipp Rumpf, Copyright (C) 1999 SuSE GmbH Nuernberg
** Copyright (C) 2000 Grant Grundler, Hewlett-Packard
*/
#अगर_अघोषित _UAPI_PARISC_PTRACE_H
#घोषणा _UAPI_PARISC_PTRACE_H


#समावेश <linux/types.h>

/* This काष्ठा defines the way the रेजिस्टरs are stored on the 
 * stack during a प्रणाली call.
 *
 * N.B. gdb/strace care about the size and offsets within this
 * काष्ठाure. If you change things, you may अवरोध object compatibility
 * क्रम those applications.
 *
 * Please करो NOT use this काष्ठाure क्रम future programs, but use
 * user_regs_काष्ठा (see below) instead.
 *
 * It can be accessed through PTRACE_PEEKUSR/PTRACE_POKEUSR only.
 */

काष्ठा pt_regs अणु
	अचिन्हित दीर्घ gr[32];	/* PSW is in gr[0] */
	__u64 fr[32];
	अचिन्हित दीर्घ sr[ 8];
	अचिन्हित दीर्घ iasq[2];
	अचिन्हित दीर्घ iaoq[2];
	अचिन्हित दीर्घ cr27;
	अचिन्हित दीर्घ pad0;     /* available क्रम other uses */
	अचिन्हित दीर्घ orig_r28;
	अचिन्हित दीर्घ ksp;
	अचिन्हित दीर्घ kpc;
	अचिन्हित दीर्घ sar;	/* CR11 */
	अचिन्हित दीर्घ iir;	/* CR19 */
	अचिन्हित दीर्घ isr;	/* CR20 */
	अचिन्हित दीर्घ ior;	/* CR21 */
	अचिन्हित दीर्घ ipsw;	/* CR22 */
पूर्ण;

/**
 * काष्ठा user_regs_काष्ठा - User general purpose रेजिस्टरs
 *
 * This is the user-visible general purpose रेजिस्टर state काष्ठाure
 * which is used to define the elf_gregset_t.
 *
 * It can be accessed through PTRACE_GETREGSET with NT_PRSTATUS
 * and through PTRACE_GETREGS.
 */
काष्ठा user_regs_काष्ठा अणु
	अचिन्हित दीर्घ gr[32];	/* PSW is in gr[0] */
	अचिन्हित दीर्घ sr[8];
	अचिन्हित दीर्घ iaoq[2];
	अचिन्हित दीर्घ iasq[2];
	अचिन्हित दीर्घ sar;	/* CR11 */
	अचिन्हित दीर्घ iir;	/* CR19 */
	अचिन्हित दीर्घ isr;	/* CR20 */
	अचिन्हित दीर्घ ior;	/* CR21 */
	अचिन्हित दीर्घ ipsw;	/* CR22 */
	अचिन्हित दीर्घ cr0;
	अचिन्हित दीर्घ cr24, cr25, cr26, cr27, cr28, cr29, cr30, cr31;
	अचिन्हित दीर्घ cr8, cr9, cr12, cr13, cr10, cr15;
	अचिन्हित दीर्घ _pad[80-64];	/* pad to ELF_NGREG (80) */
पूर्ण;

/**
 * काष्ठा user_fp_काष्ठा - User भग्नing poपूर्णांक रेजिस्टरs
 *
 * This is the user-visible भग्नing poपूर्णांक रेजिस्टर state काष्ठाure.
 * It uses the same layout and size as elf_fpregset_t.
 *
 * It can be accessed through PTRACE_GETREGSET with NT_PRFPREG
 * and through PTRACE_GETFPREGS.
 */
काष्ठा user_fp_काष्ठा अणु
	__u64 fr[32];
पूर्ण;


/*
 * The numbers chosen here are somewhat arbitrary but असलolutely MUST
 * not overlap with any of the number asचिन्हित in <linux/ptrace.h>.
 *
 * These ones are taken from IA-64 on the assumption that theirs are
 * the most correct (and we also want to support PTRACE_SINGLEBLOCK
 * since we have taken branch traps too)
 */
#घोषणा PTRACE_SINGLEBLOCK	12	/* resume execution until next branch */

#घोषणा PTRACE_GETREGS		18
#घोषणा PTRACE_SETREGS		19
#घोषणा PTRACE_GETFPREGS	14
#घोषणा PTRACE_SETFPREGS	15

#पूर्ण_अगर /* _UAPI_PARISC_PTRACE_H */
