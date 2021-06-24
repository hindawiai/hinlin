<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_RT_SIGFRAME_H
#घोषणा _ASM_PARISC_RT_SIGFRAME_H

#घोषणा SIGRETURN_TRAMP 4
#घोषणा SIGRESTARTBLOCK_TRAMP 5 
#घोषणा TRAMP_SIZE (SIGRETURN_TRAMP + SIGRESTARTBLOCK_TRAMP)

काष्ठा rt_sigframe अणु
	/* XXX: Must match trampoline size in arch/parisc/kernel/संकेत.c 
	        Secondary to that it must protect the ERESTART_RESTARTBLOCK
		trampoline we left on the stack (we were bad and didn't 
		change sp so we could run really fast.) */
	अचिन्हित पूर्णांक tramp[TRAMP_SIZE];
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;

#घोषणा	SIGFRAME		128
#घोषणा FUNCTIONCALLFRAME	96
#घोषणा PARISC_RT_SIGFRAME_SIZE					\
	(((माप(काष्ठा rt_sigframe) + FUNCTIONCALLFRAME) + SIGFRAME) & -SIGFRAME)

#पूर्ण_अगर
