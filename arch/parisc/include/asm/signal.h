<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_SIGNAL_H
#घोषणा _ASM_PARISC_SIGNAL_H

#समावेश <uapi/यंत्र/संकेत.स>

#घोषणा _NSIG		64
/* bits-per-word, where word apparently means 'long' not 'int' */
#घोषणा _NSIG_BPW	BITS_PER_LONG
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

# अगरndef __ASSEMBLY__

/* Most things should be clean enough to redefine this at will, अगर care
   is taken to make libc match.  */

प्रकार अचिन्हित दीर्घ old_sigset_t;		/* at least 32 bits */

प्रकार काष्ठा अणु
	/* next_संकेत() assumes this is a दीर्घ - no choice */
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

#समावेश <यंत्र/sigcontext.h>

#पूर्ण_अगर /* !__ASSEMBLY */
#पूर्ण_अगर /* _ASM_PARISC_SIGNAL_H */
