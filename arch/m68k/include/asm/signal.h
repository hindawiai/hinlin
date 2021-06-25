<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_SIGNAL_H
#घोषणा _M68K_SIGNAL_H

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

#अगर_अघोषित CONFIG_CPU_HAS_NO_BITFIELDS
#घोषणा __HAVE_ARCH_SIG_BITOPS

अटल अंतरभूत व्योम sigaddset(sigset_t *set, पूर्णांक _sig)
अणु
	यंत्र ("bfset %0{%1,#1}"
		: "+o" (*set)
		: "id" ((_sig - 1) ^ 31)
		: "cc");
पूर्ण

अटल अंतरभूत व्योम sigdअन्यथाt(sigset_t *set, पूर्णांक _sig)
अणु
	यंत्र ("bfclr %0{%1,#1}"
		: "+o" (*set)
		: "id" ((_sig - 1) ^ 31)
		: "cc");
पूर्ण

अटल अंतरभूत पूर्णांक __स्थिर_sigismember(sigset_t *set, पूर्णांक _sig)
अणु
	अचिन्हित दीर्घ sig = _sig - 1;
	वापस 1 & (set->sig[sig / _NSIG_BPW] >> (sig % _NSIG_BPW));
पूर्ण

अटल अंतरभूत पूर्णांक __gen_sigismember(sigset_t *set, पूर्णांक _sig)
अणु
	पूर्णांक ret;
	यंत्र ("bfextu %1{%2,#1},%0"
		: "=d" (ret)
		: "o" (*set), "id" ((_sig-1) ^ 31)
		: "cc");
	वापस ret;
पूर्ण

#घोषणा sigismember(set,sig)			\
	(__builtin_स्थिरant_p(sig) ?		\
	 __स्थिर_sigismember(set,sig) :		\
	 __gen_sigismember(set,sig))

#पूर्ण_अगर /* !CONFIG_CPU_HAS_NO_BITFIELDS */

#पूर्ण_अगर /* _M68K_SIGNAL_H */
