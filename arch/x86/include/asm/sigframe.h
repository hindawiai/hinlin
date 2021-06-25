<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SIGFRAME_H
#घोषणा _ASM_X86_SIGFRAME_H

#समावेश <uapi/यंत्र/sigcontext.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/compat.h>

#अगर_घोषित CONFIG_X86_32
#घोषणा sigframe_ia32		sigframe
#घोषणा rt_sigframe_ia32	rt_sigframe
#घोषणा ucontext_ia32		ucontext
#अन्यथा /* !CONFIG_X86_32 */

#अगर_घोषित CONFIG_IA32_EMULATION
#समावेश <यंत्र/ia32.h>
#पूर्ण_अगर /* CONFIG_IA32_EMULATION */

#पूर्ण_अगर /* CONFIG_X86_32 */

#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
काष्ठा sigframe_ia32 अणु
	u32 pretcode;
	पूर्णांक sig;
	काष्ठा sigcontext_32 sc;
	/*
	 * fpstate is unused. fpstate is moved/allocated after
	 * retcode[] below. This movement allows to have the FP state and the
	 * future state extensions (xsave) stay together.
	 * And at the same समय retaining the unused fpstate, prevents changing
	 * the offset of extramask[] in the sigframe and thus prevent any
	 * legacy application accessing/modअगरying it.
	 */
	काष्ठा _fpstate_32 fpstate_unused;
	अचिन्हित पूर्णांक extramask[1];
	अक्षर retcode[8];
	/* fp state follows here */
पूर्ण;

काष्ठा rt_sigframe_ia32 अणु
	u32 pretcode;
	पूर्णांक sig;
	u32 pinfo;
	u32 puc;
#अगर_घोषित CONFIG_IA32_EMULATION
	compat_siginfo_t info;
#अन्यथा /* !CONFIG_IA32_EMULATION */
	काष्ठा siginfo info;
#पूर्ण_अगर /* CONFIG_IA32_EMULATION */
	काष्ठा ucontext_ia32 uc;
	अक्षर retcode[8];
	/* fp state follows here */
पूर्ण;
#पूर्ण_अगर /* defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION) */

#अगर_घोषित CONFIG_X86_64

काष्ठा rt_sigframe अणु
	अक्षर __user *pretcode;
	काष्ठा ucontext uc;
	काष्ठा siginfo info;
	/* fp state follows here */
पूर्ण;

#अगर_घोषित CONFIG_X86_X32_ABI

काष्ठा ucontext_x32 अणु
	अचिन्हित पूर्णांक	  uc_flags;
	अचिन्हित पूर्णांक 	  uc_link;
	compat_stack_t	  uc_stack;
	अचिन्हित पूर्णांक	  uc__pad0;     /* needed क्रम alignment */
	काष्ठा sigcontext uc_mcontext;  /* the 64-bit sigcontext type */
	compat_sigset_t	  uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

काष्ठा rt_sigframe_x32 अणु
	u64 pretcode;
	काष्ठा ucontext_x32 uc;
	compat_siginfo_t info;
	/* fp state follows here */
पूर्ण;

#पूर्ण_अगर /* CONFIG_X86_X32_ABI */

#पूर्ण_अगर /* CONFIG_X86_64 */

#पूर्ण_अगर /* _ASM_X86_SIGFRAME_H */
