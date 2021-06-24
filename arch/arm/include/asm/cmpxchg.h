<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_CMPXCHG_H
#घोषणा __ASM_ARM_CMPXCHG_H

#समावेश <linux/irqflags.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/barrier.h>

#अगर defined(CONFIG_CPU_SA1100) || defined(CONFIG_CPU_SA110)
/*
 * On the StrongARM, "swp" is terminally broken since it bypasses the
 * cache totally.  This means that the cache becomes inconsistent, and,
 * since we use normal loads/stores as well, this is really bad.
 * Typically, this causes oopsen in filp_बंद, but could have other,
 * more disastrous effects.  There are two work-arounds:
 *  1. Disable पूर्णांकerrupts and emulate the atomic swap
 *  2. Clean the cache, perक्रमm atomic swap, flush the cache
 *
 * We choose (1) since its the "easiest" to achieve here and is not
 * dependent on the processor type.
 *
 * NOTE that this solution won't work on an SMP प्रणाली, so explcitly
 * क्रमbid it here.
 */
#घोषणा swp_is_buggy
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, अस्थिर व्योम *ptr, पूर्णांक size)
अणु
	बाह्य व्योम __bad_xchg(अस्थिर व्योम *, पूर्णांक);
	अचिन्हित दीर्घ ret;
#अगर_घोषित swp_is_buggy
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर
#अगर __LINUX_ARM_ARCH__ >= 6
	अचिन्हित पूर्णांक पंचांगp;
#पूर्ण_अगर

	prefetchw((स्थिर व्योम *)ptr);

	चयन (size) अणु
#अगर __LINUX_ARM_ARCH__ >= 6
#अगर_अघोषित CONFIG_CPU_V6 /* MIN ARCH >= V6K */
	हाल 1:
		यंत्र अस्थिर("@	__xchg1\n"
		"1:	ldrexb	%0, [%3]\n"
		"	strexb	%1, %2, [%3]\n"
		"	teq	%1, #0\n"
		"	bne	1b"
			: "=&r" (ret), "=&r" (पंचांगp)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		अवरोध;
	हाल 2:
		यंत्र अस्थिर("@	__xchg2\n"
		"1:	ldrexh	%0, [%3]\n"
		"	strexh	%1, %2, [%3]\n"
		"	teq	%1, #0\n"
		"	bne	1b"
			: "=&r" (ret), "=&r" (पंचांगp)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		अवरोध;
#पूर्ण_अगर
	हाल 4:
		यंत्र अस्थिर("@	__xchg4\n"
		"1:	ldrex	%0, [%3]\n"
		"	strex	%1, %2, [%3]\n"
		"	teq	%1, #0\n"
		"	bne	1b"
			: "=&r" (ret), "=&r" (पंचांगp)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		अवरोध;
#या_अगर defined(swp_is_buggy)
#अगर_घोषित CONFIG_SMP
#त्रुटि SMP is not supported on this platक्रमm
#पूर्ण_अगर
	हाल 1:
		raw_local_irq_save(flags);
		ret = *(अस्थिर अचिन्हित अक्षर *)ptr;
		*(अस्थिर अचिन्हित अक्षर *)ptr = x;
		raw_local_irq_restore(flags);
		अवरोध;

	हाल 4:
		raw_local_irq_save(flags);
		ret = *(अस्थिर अचिन्हित दीर्घ *)ptr;
		*(अस्थिर अचिन्हित दीर्घ *)ptr = x;
		raw_local_irq_restore(flags);
		अवरोध;
#अन्यथा
	हाल 1:
		यंत्र अस्थिर("@	__xchg1\n"
		"	swpb	%0, %1, [%2]"
			: "=&r" (ret)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		अवरोध;
	हाल 4:
		यंत्र अस्थिर("@	__xchg4\n"
		"	swp	%0, %1, [%2]"
			: "=&r" (ret)
			: "r" (x), "r" (ptr)
			: "memory", "cc");
		अवरोध;
#पूर्ण_अगर
	शेष:
		/* Cause a link-समय error, the xchg() size is not supported */
		__bad_xchg(ptr, size), ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा xchg_relaxed(ptr, x) (अणु						\
	(__typeof__(*(ptr)))__xchg((अचिन्हित दीर्घ)(x), (ptr),		\
				   माप(*(ptr)));			\
पूर्ण)

#समावेश <यंत्र-generic/cmpxchg-local.h>

#अगर __LINUX_ARM_ARCH__ < 6
/* min ARCH < ARMv6 */

#अगर_घोषित CONFIG_SMP
#त्रुटि "SMP is not supported on this platform"
#पूर्ण_अगर

#घोषणा xchg xchg_relaxed

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#घोषणा cmpxchg_local(ptr, o, n) (अणु					\
	(__typeof(*ptr))__cmpxchg_local_generic((ptr),			\
					        (अचिन्हित दीर्घ)(o),	\
					        (अचिन्हित दीर्घ)(n),	\
					        माप(*(ptr)));	\
पूर्ण)

#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))

#समावेश <यंत्र-generic/cmpxchg.h>

#अन्यथा	/* min ARCH >= ARMv6 */

बाह्य व्योम __bad_cmpxchg(अस्थिर व्योम *ptr, पूर्णांक size);

/*
 * cmpxchg only support 32-bits opeअक्रमs on ARMv6.
 */

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old,
				      अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	अचिन्हित दीर्घ oldval, res;

	prefetchw((स्थिर व्योम *)ptr);

	चयन (size) अणु
#अगर_अघोषित CONFIG_CPU_V6	/* min ARCH >= ARMv6K */
	हाल 1:
		करो अणु
			यंत्र अस्थिर("@ __cmpxchg1\n"
			"	ldrexb	%1, [%2]\n"
			"	mov	%0, #0\n"
			"	teq	%1, %3\n"
			"	strexbeq %0, %4, [%2]\n"
				: "=&r" (res), "=&r" (oldval)
				: "r" (ptr), "Ir" (old), "r" (new)
				: "memory", "cc");
		पूर्ण जबतक (res);
		अवरोध;
	हाल 2:
		करो अणु
			यंत्र अस्थिर("@ __cmpxchg1\n"
			"	ldrexh	%1, [%2]\n"
			"	mov	%0, #0\n"
			"	teq	%1, %3\n"
			"	strexheq %0, %4, [%2]\n"
				: "=&r" (res), "=&r" (oldval)
				: "r" (ptr), "Ir" (old), "r" (new)
				: "memory", "cc");
		पूर्ण जबतक (res);
		अवरोध;
#पूर्ण_अगर
	हाल 4:
		करो अणु
			यंत्र अस्थिर("@ __cmpxchg4\n"
			"	ldrex	%1, [%2]\n"
			"	mov	%0, #0\n"
			"	teq	%1, %3\n"
			"	strexeq %0, %4, [%2]\n"
				: "=&r" (res), "=&r" (oldval)
				: "r" (ptr), "Ir" (old), "r" (new)
				: "memory", "cc");
		पूर्ण जबतक (res);
		अवरोध;
	शेष:
		__bad_cmpxchg(ptr, size);
		oldval = 0;
	पूर्ण

	वापस oldval;
पूर्ण

#घोषणा cmpxchg_relaxed(ptr,o,n) (अणु					\
	(__typeof__(*(ptr)))__cmpxchg((ptr),				\
				      (अचिन्हित दीर्घ)(o),		\
				      (अचिन्हित दीर्घ)(n),		\
				      माप(*(ptr)));			\
पूर्ण)

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_local(अस्थिर व्योम *ptr,
					    अचिन्हित दीर्घ old,
					    अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	अचिन्हित दीर्घ ret;

	चयन (size) अणु
#अगर_घोषित CONFIG_CPU_V6	/* min ARCH == ARMv6 */
	हाल 1:
	हाल 2:
		ret = __cmpxchg_local_generic(ptr, old, new, size);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = __cmpxchg(ptr, old, new, size);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा cmpxchg_local(ptr, o, n) (अणु					\
	(__typeof(*ptr))__cmpxchg_local((ptr),				\
				        (अचिन्हित दीर्घ)(o),		\
				        (अचिन्हित दीर्घ)(n),		\
				        माप(*(ptr)));		\
पूर्ण)

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ __cmpxchg64(अचिन्हित दीर्घ दीर्घ *ptr,
					     अचिन्हित दीर्घ दीर्घ old,
					     अचिन्हित दीर्घ दीर्घ new)
अणु
	अचिन्हित दीर्घ दीर्घ oldval;
	अचिन्हित दीर्घ res;

	prefetchw(ptr);

	__यंत्र__ __अस्थिर__(
"1:	ldrexd		%1, %H1, [%3]\n"
"	teq		%1, %4\n"
"	teqeq		%H1, %H4\n"
"	bne		2f\n"
"	strexd		%0, %5, %H5, [%3]\n"
"	teq		%0, #0\n"
"	bne		1b\n"
"2:"
	: "=&r" (res), "=&r" (oldval), "+Qo" (*ptr)
	: "r" (ptr), "r" (old), "r" (new)
	: "cc");

	वापस oldval;
पूर्ण

#घोषणा cmpxchg64_relaxed(ptr, o, n) (अणु					\
	(__typeof__(*(ptr)))__cmpxchg64((ptr),				\
					(अचिन्हित दीर्घ दीर्घ)(o),	\
					(अचिन्हित दीर्घ दीर्घ)(n));	\
पूर्ण)

#घोषणा cmpxchg64_local(ptr, o, n) cmpxchg64_relaxed((ptr), (o), (n))

#पूर्ण_अगर	/* __LINUX_ARM_ARCH__ >= 6 */

#पूर्ण_अगर /* __ASM_ARM_CMPXCHG_H */
