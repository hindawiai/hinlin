<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SIGNAL32_H
#घोषणा __ASM_SIGNAL32_H

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>

काष्ठा compat_sigcontext अणु
	/* We always set these two fields to 0 */
	compat_uदीर्घ_t			trap_no;
	compat_uदीर्घ_t			error_code;

	compat_uदीर्घ_t			oldmask;
	compat_uदीर्घ_t			arm_r0;
	compat_uदीर्घ_t			arm_r1;
	compat_uदीर्घ_t			arm_r2;
	compat_uदीर्घ_t			arm_r3;
	compat_uदीर्घ_t			arm_r4;
	compat_uदीर्घ_t			arm_r5;
	compat_uदीर्घ_t			arm_r6;
	compat_uदीर्घ_t			arm_r7;
	compat_uदीर्घ_t			arm_r8;
	compat_uदीर्घ_t			arm_r9;
	compat_uदीर्घ_t			arm_r10;
	compat_uदीर्घ_t			arm_fp;
	compat_uदीर्घ_t			arm_ip;
	compat_uदीर्घ_t			arm_sp;
	compat_uदीर्घ_t			arm_lr;
	compat_uदीर्घ_t			arm_pc;
	compat_uदीर्घ_t			arm_cpsr;
	compat_uदीर्घ_t			fault_address;
पूर्ण;

काष्ठा compat_ucontext अणु
	compat_uदीर्घ_t			uc_flags;
	compat_uptr_t			uc_link;
	compat_stack_t			uc_stack;
	काष्ठा compat_sigcontext	uc_mcontext;
	compat_sigset_t			uc_sigmask;
	पूर्णांक 				__unused[32 - (माप(compat_sigset_t) / माप(पूर्णांक))];
	compat_uदीर्घ_t			uc_regspace[128] __attribute__((__aligned__(8)));
पूर्ण;

काष्ठा compat_sigframe अणु
	काष्ठा compat_ucontext	uc;
	compat_uदीर्घ_t		retcode[2];
पूर्ण;

काष्ठा compat_rt_sigframe अणु
	काष्ठा compat_siginfo info;
	काष्ठा compat_sigframe sig;
पूर्ण;

पूर्णांक compat_setup_frame(पूर्णांक usig, काष्ठा kसंकेत *ksig, sigset_t *set,
		       काष्ठा pt_regs *regs);
पूर्णांक compat_setup_rt_frame(पूर्णांक usig, काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs);

व्योम compat_setup_restart_syscall(काष्ठा pt_regs *regs);
#अन्यथा

अटल अंतरभूत पूर्णांक compat_setup_frame(पूर्णांक usid, काष्ठा kसंकेत *ksig,
				     sigset_t *set, काष्ठा pt_regs *regs)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक compat_setup_rt_frame(पूर्णांक usig, काष्ठा kसंकेत *ksig, sigset_t *set,
					काष्ठा pt_regs *regs)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम compat_setup_restart_syscall(काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */
#पूर्ण_अगर /* __ASM_SIGNAL32_H */
