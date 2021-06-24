<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_SIGNAL_H
#घोषणा _H8300_SIGNAL_H

#समावेश <uapi/यंत्र/संकेत.स>

/* Most things should be clean enough to redefine this at will, अगर care
   is taken to make libc match.  */

#घोषणा _NSIG		64
#घोषणा _NSIG_BPW	32
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

प्रकार अचिन्हित दीर्घ old_sigset_t;		/* at least 32 bits */

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

#घोषणा __ARCH_HAS_SA_RESTORER
#समावेश <यंत्र/sigcontext.h>

#पूर्ण_अगर /* _H8300_SIGNAL_H */
