<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/signal.h"
 */
#अगर_अघोषित _ASMS390_SIGNAL_H
#घोषणा _ASMS390_SIGNAL_H

#समावेश <uapi/यंत्र/संकेत.स>

/* Most things should be clean enough to redefine this at will, अगर care
   is taken to make libc match.  */
#समावेश <यंत्र/sigcontext.h>
#घोषणा _NSIG           _SIGCONTEXT_NSIG
#घोषणा _NSIG_BPW       _SIGCONTEXT_NSIG_BPW
#घोषणा _NSIG_WORDS     _SIGCONTEXT_NSIG_WORDS

प्रकार अचिन्हित दीर्घ old_sigset_t;             /* at least 32 bits */

प्रकार काष्ठा अणु
        अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

#घोषणा __ARCH_HAS_SA_RESTORER
#पूर्ण_अगर
