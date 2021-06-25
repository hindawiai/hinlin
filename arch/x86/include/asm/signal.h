<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SIGNAL_H
#घोषणा _ASM_X86_SIGNAL_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/linkage.h>

/* Most things should be clean enough to redefine this at will, अगर care
   is taken to make libc match.  */

#घोषणा _NSIG		64

#अगर_घोषित __i386__
# define _NSIG_BPW	32
#अन्यथा
# define _NSIG_BPW	64
#पूर्ण_अगर

#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

प्रकार अचिन्हित दीर्घ old_sigset_t;		/* at least 32 bits */

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

/* non-uapi in-kernel SA_FLAGS क्रम those indicates ABI क्रम a संकेत frame */
#घोषणा SA_IA32_ABI	0x02000000u
#घोषणा SA_X32_ABI	0x01000000u

#अगर_अघोषित CONFIG_COMPAT
प्रकार sigset_t compat_sigset_t;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#समावेश <uapi/यंत्र/संकेत.स>
#अगर_अघोषित __ASSEMBLY__

#घोषणा __ARCH_HAS_SA_RESTORER

#समावेश <यंत्र/यंत्र.h>
#समावेश <uapi/यंत्र/sigcontext.h>

#अगर_घोषित __i386__

#घोषणा __HAVE_ARCH_SIG_BITOPS

#घोषणा sigaddset(set,sig)		    \
	(__builtin_स्थिरant_p(sig)	    \
	 ? __स्थिर_sigaddset((set), (sig))  \
	 : __gen_sigaddset((set), (sig)))

अटल अंतरभूत व्योम __gen_sigaddset(sigset_t *set, पूर्णांक _sig)
अणु
	यंत्र("btsl %1,%0" : "+m"(*set) : "Ir"(_sig - 1) : "cc");
पूर्ण

अटल अंतरभूत व्योम __स्थिर_sigaddset(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	set->sig[sig / _NSIG_BPW] |= 1 << (sig % _NSIG_BPW);
पूर्ण

#घोषणा sigdअन्यथाt(set, sig)		    \
	(__builtin_स्थिरant_p(sig)	    \
	 ? __स्थिर_sigdअन्यथाt((set), (sig))  \
	 : __gen_sigdअन्यथाt((set), (sig)))


अटल अंतरभूत व्योम __gen_sigdअन्यथाt(sigset_t *set, पूर्णांक _sig)
अणु
	यंत्र("btrl %1,%0" : "+m"(*set) : "Ir"(_sig - 1) : "cc");
पूर्ण

अटल अंतरभूत व्योम __स्थिर_sigdअन्यथाt(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	set->sig[sig / _NSIG_BPW] &= ~(1 << (sig % _NSIG_BPW));
पूर्ण

अटल अंतरभूत पूर्णांक __स्थिर_sigismember(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	वापस 1 & (set->sig[sig / _NSIG_BPW] >> (sig % _NSIG_BPW));
पूर्ण

अटल अंतरभूत पूर्णांक __gen_sigismember(sigset_t *set, पूर्णांक _sig)
अणु
	bool ret;
	यंत्र("btl %2,%1" CC_SET(c)
	    : CC_OUT(c) (ret) : "m"(*set), "Ir"(_sig-1));
	वापस ret;
पूर्ण

#घोषणा sigismember(set, sig)			\
	(__builtin_स्थिरant_p(sig)		\
	 ? __स्थिर_sigismember((set), (sig))	\
	 : __gen_sigismember((set), (sig)))

काष्ठा pt_regs;

#अन्यथा /* __i386__ */

#अघोषित __HAVE_ARCH_SIG_BITOPS

#पूर्ण_अगर /* !__i386__ */

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_SIGNAL_H */
