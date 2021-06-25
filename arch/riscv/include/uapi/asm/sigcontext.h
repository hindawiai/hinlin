<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _UAPI_ASM_RISCV_SIGCONTEXT_H
#घोषणा _UAPI_ASM_RISCV_SIGCONTEXT_H

#समावेश <यंत्र/ptrace.h>

/*
 * Signal context काष्ठाure
 *
 * This contains the context saved beक्रमe a संकेत handler is invoked;
 * it is restored by sys_sigवापस / sys_rt_sigवापस.
 */
काष्ठा sigcontext अणु
	काष्ठा user_regs_काष्ठा sc_regs;
	जोड़ __riscv_fp_state sc_fpregs;
पूर्ण;

#पूर्ण_अगर /* _UAPI_ASM_RISCV_SIGCONTEXT_H */
