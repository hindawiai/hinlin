<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* 
 *    Copyright (C) 2001 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2003 Carlos O'Donell <carlos at parisc-linux.org>
 */
#अगर_अघोषित _PARISC64_KERNEL_SIGNAL32_H
#घोषणा _PARISC64_KERNEL_SIGNAL32_H

#समावेश <linux/compat.h>

/* 32-bit ucontext as seen from an 64-bit kernel */
काष्ठा compat_ucontext अणु
        compat_uपूर्णांक_t uc_flags;
        compat_uptr_t uc_link;
        compat_stack_t uc_stack;        /* काष्ठा compat_sigaltstack (12 bytes)*/
        /* FIXME: Pad out to get uc_mcontext to start at an 8-byte aligned boundary */
        compat_uपूर्णांक_t pad[1];
        काष्ठा compat_sigcontext uc_mcontext;
        compat_sigset_t uc_sigmask;     /* mask last क्रम extensibility */
पूर्ण;

/* ELF32 संकेत handling */

/* In a deft move of uber-hackery, we decide to carry the top half of all
 * 64-bit रेजिस्टरs in a non-portable, non-ABI, hidden काष्ठाure.
 * Userspace can पढ़ो the hidden काष्ठाure अगर it *wants* but is never
 * guaranteed to be in the same place. In fact the uc_sigmask from the
 * ucontext_t काष्ठाure may push the hidden रेजिस्टर file करोwnards
 */
काष्ठा compat_regfile अणु
        /* Upper half of all the 64-bit रेजिस्टरs that were truncated
           on a copy to a 32-bit userspace */
        compat_पूर्णांक_t rf_gr[32];
        compat_पूर्णांक_t rf_iasq[2];
        compat_पूर्णांक_t rf_iaoq[2];
        compat_पूर्णांक_t rf_sar;
पूर्ण;

#घोषणा COMPAT_SIGRETURN_TRAMP 4
#घोषणा COMPAT_SIGRESTARTBLOCK_TRAMP 5
#घोषणा COMPAT_TRAMP_SIZE (COMPAT_SIGRETURN_TRAMP + \
				COMPAT_SIGRESTARTBLOCK_TRAMP)

काष्ठा compat_rt_sigframe अणु
        /* XXX: Must match trampoline size in arch/parisc/kernel/संकेत.c
                Secondary to that it must protect the ERESTART_RESTARTBLOCK
                trampoline we left on the stack (we were bad and didn't
                change sp so we could run really fast.) */
        compat_uपूर्णांक_t tramp[COMPAT_TRAMP_SIZE];
        compat_siginfo_t info;
        काष्ठा compat_ucontext uc;
        /* Hidden location of truncated रेजिस्टरs, *must* be last. */
        काष्ठा compat_regfile regs;
पूर्ण;

/*
 * The 32-bit ABI wants at least 48 bytes क्रम a function call frame:
 * 16 bytes क्रम arg0-arg3, and 32 bytes क्रम magic (the only part of
 * which Linux/parisc uses is sp-20 क्रम the saved वापस poपूर्णांकer...)
 * Then, the stack poपूर्णांकer must be rounded to a cache line (64 bytes).
 */
#घोषणा SIGFRAME32              64
#घोषणा FUNCTIONCALLFRAME32     48
#घोषणा PARISC_RT_SIGFRAME_SIZE32 (((माप(काष्ठा compat_rt_sigframe) + FUNCTIONCALLFRAME32) + SIGFRAME32) & -SIGFRAME32)

दीर्घ restore_sigcontext32(काष्ठा compat_sigcontext __user *sc, 
		काष्ठा compat_regfile __user *rf,
		काष्ठा pt_regs *regs);
दीर्घ setup_sigcontext32(काष्ठा compat_sigcontext __user *sc, 
		काष्ठा compat_regfile __user *rf,
		काष्ठा pt_regs *regs, पूर्णांक in_syscall);

#पूर्ण_अगर
