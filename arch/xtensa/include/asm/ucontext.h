<शैली गुरु>
/*
 * include/यंत्र-xtensa/ucontext.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_UCONTEXT_H
#घोषणा _XTENSA_UCONTEXT_H

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	stack_t		  uc_stack;
	काष्ठा sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask last क्रम extensibility */
पूर्ण;

#पूर्ण_अगर /* _XTENSA_UCONTEXT_H */
