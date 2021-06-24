<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_UCONTEXT_H
#घोषणा __ASM_GENERIC_UCONTEXT_H

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	stack_t		  uc_stack;
	काष्ठा sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

#पूर्ण_अगर /* __ASM_GENERIC_UCONTEXT_H */
