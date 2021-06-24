<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASMAXP_UCONTEXT_H
#घोषणा _ASMAXP_UCONTEXT_H

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	old_sigset_t	  uc_osf_sigmask;
	stack_t		  uc_stack;
	काष्ठा sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

#पूर्ण_अगर /* !_ASMAXP_UCONTEXT_H */
