<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_UCONTEXT_H
#घोषणा _ASM_IA64_UCONTEXT_H

काष्ठा ucontext अणु
	काष्ठा sigcontext uc_mcontext;
पूर्ण;

#घोषणा uc_link		uc_mcontext.sc_gr[0]	/* wrong type; nobody cares */
#घोषणा uc_sigmask	uc_mcontext.sc_sigmask
#घोषणा uc_stack	uc_mcontext.sc_stack

#पूर्ण_अगर /* _ASM_IA64_UCONTEXT_H */
