<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/ucontext.h"
 */

#अगर_अघोषित _ASM_S390_UCONTEXT_H
#घोषणा _ASM_S390_UCONTEXT_H

#घोषणा UC_GPRS_HIGH	1	/* uc_mcontext_ext has valid high gprs */
#घोषणा UC_VXRS		2	/* uc_mcontext_ext has valid vector regs */

/*
 * The काष्ठा ucontext_extended describes how the रेजिस्टरs are stored
 * on a rt संकेत frame. Please note that the काष्ठाure is not fixed,
 * अगर new CPU रेजिस्टरs are added to the user state the size of the
 * काष्ठा ucontext_extended will increase.
 */
काष्ठा ucontext_extended अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	stack_t		  uc_stack;
	_sigregs	  uc_mcontext;
	sigset_t	  uc_sigmask;
	/* Allow क्रम uc_sigmask growth.  Glibc uses a 1024-bit sigset_t.  */
	अचिन्हित अक्षर	  __unused[128 - माप(sigset_t)];
	_sigregs_ext	  uc_mcontext_ext;
पूर्ण;

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	stack_t		  uc_stack;
	_sigregs          uc_mcontext;
	sigset_t	  uc_sigmask;
	/* Allow क्रम uc_sigmask growth.  Glibc uses a 1024-bit sigset_t.  */
	अचिन्हित अक्षर	  __unused[128 - माप(sigset_t)];
पूर्ण;

#पूर्ण_अगर /* !_ASM_S390_UCONTEXT_H */
