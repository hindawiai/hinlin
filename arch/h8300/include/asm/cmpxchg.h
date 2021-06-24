<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_H8300_CMPXCHG__
#घोषणा __ARCH_H8300_CMPXCHG__

#समावेश <linux/irqflags.h>

#घोषणा xchg(ptr, x) \
	((__typeof__(*(ptr)))__xchg((अचिन्हित दीर्घ)(x), (ptr), \
				    माप(*(ptr))))

काष्ठा __xchg_dummy अणु अचिन्हित दीर्घ a[100]; पूर्ण;
#घोषणा __xg(x) ((अस्थिर काष्ठा __xchg_dummy *)(x))

अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x,
				   अस्थिर व्योम *ptr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ पंचांगp, flags;

	local_irq_save(flags);

	चयन (size) अणु
	हाल 1:
		__यंत्र__ __अस्थिर__
			("mov.b %2,%0\n\t"
			 "mov.b %1,%2"
			 : "=&r" (पंचांगp) : "r" (x), "m" (*__xg(ptr)));
		अवरोध;
	हाल 2:
		__यंत्र__ __अस्थिर__
			("mov.w %2,%0\n\t"
			 "mov.w %1,%2"
			 : "=&r" (पंचांगp) : "r" (x), "m" (*__xg(ptr)));
		अवरोध;
	हाल 4:
		__यंत्र__ __अस्थिर__
			("mov.l %2,%0\n\t"
			 "mov.l %1,%2"
			 : "=&r" (पंचांगp) : "r" (x), "m" (*__xg(ptr)));
		अवरोध;
	शेष:
		पंचांगp = 0;
	पूर्ण
	local_irq_restore(flags);
	वापस पंचांगp;
पूर्ण

#समावेश <यंत्र-generic/cmpxchg-local.h>

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#घोषणा cmpxchg_local(ptr, o, n)					 \
	((__typeof__(*(ptr)))__cmpxchg_local_generic((ptr),		 \
						     (अचिन्हित दीर्घ)(o), \
						     (अचिन्हित दीर्घ)(n), \
						     माप(*(ptr))))
#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))

#अगर_अघोषित CONFIG_SMP
#समावेश <यंत्र-generic/cmpxchg.h>
#पूर्ण_अगर

#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#पूर्ण_अगर /* __ARCH_H8300_CMPXCHG__ */
