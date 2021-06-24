<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */
#अगर_अघोषित __ASM_OPENRISC_PTRACE_H
#घोषणा __ASM_OPENRISC_PTRACE_H


#समावेश <यंत्र/spr_defs.h>
#समावेश <uapi/यंत्र/ptrace.h>

/*
 * Make kernel PTrace/रेजिस्टर काष्ठाures opaque to userspace... userspace can
 * access thपढ़ो state via the regset mechanism.  This allows us a bit of
 * flexibility in how we order the रेजिस्टरs on the stack, permitting some
 * optimizations like packing call-clobbered रेजिस्टरs together so that
 * they share a cacheline (not करोne yet, though... future optimization).
 */

#अगर_अघोषित __ASSEMBLY__
/*
 * This काष्ठा describes how the रेजिस्टरs are laid out on the kernel stack
 * during a syscall or other kernel entry.
 *
 * This काष्ठाure should always be cacheline aligned on the stack.
 * FIXME: I करोn't think that's the हाल right now.  The alignment is
 * taken care of अन्यथाwhere... head.S, process.c, etc.
 */

काष्ठा pt_regs अणु
	जोड़ अणु
		काष्ठा अणु
			/* Named रेजिस्टरs */
			दीर्घ  sr;	/* Stored in place of r0 */
			दीर्घ  sp;	/* r1 */
		पूर्ण;
		काष्ठा अणु
			/* Old style */
			दीर्घ offset[2];
			दीर्घ gprs[30];
		पूर्ण;
		काष्ठा अणु
			/* New style */
			दीर्घ gpr[32];
		पूर्ण;
	पूर्ण;
	दीर्घ  pc;
	/* For restarting प्रणाली calls:
	 * Set to syscall number क्रम syscall exceptions,
	 * -1 क्रम all other exceptions.
	 */
	दीर्घ  orig_gpr11;	/* For restarting प्रणाली calls */
	दीर्घ dummy;		/* Cheap alignment fix */
	दीर्घ dummy2;		/* Cheap alignment fix */
पूर्ण;

/* TODO: Rename this to REDZONE because that's what it is */
#घोषणा STACK_FRAME_OVERHEAD  128  /* size of minimum stack frame */

#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	((regs)->pc)
#घोषणा user_mode(regs)			(((regs)->sr & SPR_SR_SM) == 0)
#घोषणा user_stack_poपूर्णांकer(regs)	((अचिन्हित दीर्घ)(regs)->sp)
#घोषणा profile_pc(regs)		inकाष्ठाion_poपूर्णांकer(regs)

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->gpr[11];
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Offsets used by 'ptrace' प्रणाली call पूर्णांकerface.
 */
#घोषणा PT_SR         0
#घोषणा PT_SP         4
#घोषणा PT_GPR2       8
#घोषणा PT_GPR3       12
#घोषणा PT_GPR4       16
#घोषणा PT_GPR5       20
#घोषणा PT_GPR6       24
#घोषणा PT_GPR7       28
#घोषणा PT_GPR8       32
#घोषणा PT_GPR9       36
#घोषणा PT_GPR10      40
#घोषणा PT_GPR11      44
#घोषणा PT_GPR12      48
#घोषणा PT_GPR13      52
#घोषणा PT_GPR14      56
#घोषणा PT_GPR15      60
#घोषणा PT_GPR16      64
#घोषणा PT_GPR17      68
#घोषणा PT_GPR18      72
#घोषणा PT_GPR19      76
#घोषणा PT_GPR20      80
#घोषणा PT_GPR21      84
#घोषणा PT_GPR22      88
#घोषणा PT_GPR23      92
#घोषणा PT_GPR24      96
#घोषणा PT_GPR25      100
#घोषणा PT_GPR26      104
#घोषणा PT_GPR27      108
#घोषणा PT_GPR28      112
#घोषणा PT_GPR29      116
#घोषणा PT_GPR30      120
#घोषणा PT_GPR31      124
#घोषणा PT_PC	      128
#घोषणा PT_ORIG_GPR11 132
#घोषणा PT_SYSCALLNO  136

#पूर्ण_अगर /* __ASM_OPENRISC_PTRACE_H */
