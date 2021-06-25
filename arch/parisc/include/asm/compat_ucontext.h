<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_COMPAT_UCONTEXT_H
#घोषणा _ASM_PARISC_COMPAT_UCONTEXT_H

#समावेश <linux/compat.h>

/* 32-bit ucontext as seen from an 64-bit kernel */
काष्ठा compat_ucontext अणु
	compat_uपूर्णांक_t uc_flags;
	compat_uptr_t uc_link;
	compat_stack_t uc_stack;	/* काष्ठा compat_sigaltstack (12 bytes)*/	
	/* FIXME: Pad out to get uc_mcontext to start at an 8-byte aligned boundary */
	compat_uपूर्णांक_t pad[1];
	काष्ठा compat_sigcontext uc_mcontext;
	compat_sigset_t uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

#पूर्ण_अगर /* !_ASM_PARISC_COMPAT_UCONTEXT_H */
