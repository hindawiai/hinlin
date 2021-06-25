<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Modअगरied 1998-2001, 2003
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 *
 * Unक्रमtunately, this file is being included by bits/संकेत.स in
 * glibc-2.x.  Hence the #अगर_घोषित __KERNEL__ ugliness.
 */
#अगर_अघोषित _ASM_IA64_SIGNAL_H
#घोषणा _ASM_IA64_SIGNAL_H

#समावेश <uapi/यंत्र/संकेत.स>


#घोषणा _NSIG		64
#घोषणा _NSIG_BPW	64
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

# अगरndef __ASSEMBLY__

/* Most things should be clean enough to redefine this at will, अगर care
   is taken to make libc match.  */

प्रकार अचिन्हित दीर्घ old_sigset_t;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

#  include <यंत्र/sigcontext.h>

# endअगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_IA64_SIGNAL_H */
