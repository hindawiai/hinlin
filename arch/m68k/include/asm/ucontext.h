<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_UCONTEXT_H
#घोषणा _M68K_UCONTEXT_H

प्रकार पूर्णांक greg_t;
#घोषणा NGREG 18
प्रकार greg_t gregset_t[NGREG];

प्रकार काष्ठा fpregset अणु
	पूर्णांक f_fpcntl[3];
	पूर्णांक f_fpregs[8*3];
पूर्ण fpregset_t;

काष्ठा mcontext अणु
	पूर्णांक version;
	gregset_t gregs;
	fpregset_t fpregs;
पूर्ण;

#घोषणा MCONTEXT_VERSION 2

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	stack_t		  uc_stack;
	काष्ठा mcontext	  uc_mcontext;
	अचिन्हित दीर्घ	  uc_filler[80];
	sigset_t	  uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

#पूर्ण_अगर
