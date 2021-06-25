<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999, 2011
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 */

#अगर_अघोषित __ASM_CMPXCHG_H
#घोषणा __ASM_CMPXCHG_H

#समावेश <linux/mmdebug.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>

व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

अटल __always_अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x,
					    अचिन्हित दीर्घ address, पूर्णांक size)
अणु
	अचिन्हित दीर्घ old;
	पूर्णांक shअगरt;

	चयन (size) अणु
	हाल 1:
		shअगरt = (3 ^ (address & 3)) << 3;
		address ^= address & 3;
		यंत्र अस्थिर(
			"       l       %0,%1\n"
			"0:     lr      0,%0\n"
			"       nr      0,%3\n"
			"       or      0,%2\n"
			"       cs      %0,0,%1\n"
			"       jl      0b\n"
			: "=&d" (old), "+Q" (*(पूर्णांक *) address)
			: "d" ((x & 0xff) << shअगरt), "d" (~(0xff << shअगरt))
			: "memory", "cc", "0");
		वापस old >> shअगरt;
	हाल 2:
		shअगरt = (2 ^ (address & 2)) << 3;
		address ^= address & 2;
		यंत्र अस्थिर(
			"       l       %0,%1\n"
			"0:     lr      0,%0\n"
			"       nr      0,%3\n"
			"       or      0,%2\n"
			"       cs      %0,0,%1\n"
			"       jl      0b\n"
			: "=&d" (old), "+Q" (*(पूर्णांक *) address)
			: "d" ((x & 0xffff) << shअगरt), "d" (~(0xffff << shअगरt))
			: "memory", "cc", "0");
		वापस old >> shअगरt;
	हाल 4:
		यंत्र अस्थिर(
			"       l       %0,%1\n"
			"0:     cs      %0,%2,%1\n"
			"       jl      0b\n"
			: "=&d" (old), "+Q" (*(पूर्णांक *) address)
			: "d" (x)
			: "memory", "cc");
		वापस old;
	हाल 8:
		यंत्र अस्थिर(
			"       lg      %0,%1\n"
			"0:     csg     %0,%2,%1\n"
			"       jl      0b\n"
			: "=&d" (old), "+QS" (*(दीर्घ *) address)
			: "d" (x)
			: "memory", "cc");
		वापस old;
	पूर्ण
	__xchg_called_with_bad_poपूर्णांकer();
	वापस x;
पूर्ण

#घोषणा arch_xchg(ptr, x)						\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
									\
	__ret = (__typeof__(*(ptr)))					\
		__xchg((अचिन्हित दीर्घ)(x), (अचिन्हित दीर्घ)(ptr),	\
		       माप(*(ptr)));					\
	__ret;								\
पूर्ण)

व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

अटल __always_अंतरभूत अचिन्हित दीर्घ __cmpxchg(अचिन्हित दीर्घ address,
					       अचिन्हित दीर्घ old,
					       अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	अचिन्हित दीर्घ prev, पंचांगp;
	पूर्णांक shअगरt;

	चयन (size) अणु
	हाल 1:
		shअगरt = (3 ^ (address & 3)) << 3;
		address ^= address & 3;
		यंत्र अस्थिर(
			"       l       %0,%2\n"
			"0:     nr      %0,%5\n"
			"       lr      %1,%0\n"
			"       or      %0,%3\n"
			"       or      %1,%4\n"
			"       cs      %0,%1,%2\n"
			"       jnl     1f\n"
			"       xr      %1,%0\n"
			"       nr      %1,%5\n"
			"       jnz     0b\n"
			"1:"
			: "=&d" (prev), "=&d" (पंचांगp), "+Q" (*(पूर्णांक *) address)
			: "d" ((old & 0xff) << shअगरt),
			  "d" ((new & 0xff) << shअगरt),
			  "d" (~(0xff << shअगरt))
			: "memory", "cc");
		वापस prev >> shअगरt;
	हाल 2:
		shअगरt = (2 ^ (address & 2)) << 3;
		address ^= address & 2;
		यंत्र अस्थिर(
			"       l       %0,%2\n"
			"0:     nr      %0,%5\n"
			"       lr      %1,%0\n"
			"       or      %0,%3\n"
			"       or      %1,%4\n"
			"       cs      %0,%1,%2\n"
			"       jnl     1f\n"
			"       xr      %1,%0\n"
			"       nr      %1,%5\n"
			"       jnz     0b\n"
			"1:"
			: "=&d" (prev), "=&d" (पंचांगp), "+Q" (*(पूर्णांक *) address)
			: "d" ((old & 0xffff) << shअगरt),
			  "d" ((new & 0xffff) << shअगरt),
			  "d" (~(0xffff << shअगरt))
			: "memory", "cc");
		वापस prev >> shअगरt;
	हाल 4:
		यंत्र अस्थिर(
			"       cs      %0,%3,%1\n"
			: "=&d" (prev), "+Q" (*(पूर्णांक *) address)
			: "0" (old), "d" (new)
			: "memory", "cc");
		वापस prev;
	हाल 8:
		यंत्र अस्थिर(
			"       csg     %0,%3,%1\n"
			: "=&d" (prev), "+QS" (*(दीर्घ *) address)
			: "0" (old), "d" (new)
			: "memory", "cc");
		वापस prev;
	पूर्ण
	__cmpxchg_called_with_bad_poपूर्णांकer();
	वापस old;
पूर्ण

#घोषणा arch_cmpxchg(ptr, o, n)						\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
									\
	__ret = (__typeof__(*(ptr)))					\
		__cmpxchg((अचिन्हित दीर्घ)(ptr), (अचिन्हित दीर्घ)(o),	\
			  (अचिन्हित दीर्घ)(n), माप(*(ptr)));		\
	__ret;								\
पूर्ण)

#घोषणा arch_cmpxchg64		arch_cmpxchg
#घोषणा arch_cmpxchg_local	arch_cmpxchg
#घोषणा arch_cmpxchg64_local	arch_cmpxchg

#घोषणा प्रणाली_has_cmpxchg_द्विगुन()	1

#घोषणा __cmpxchg_द्विगुन(p1, p2, o1, o2, n1, n2)			\
(अणु									\
	रेजिस्टर __typeof__(*(p1)) __old1 यंत्र("2") = (o1);		\
	रेजिस्टर __typeof__(*(p2)) __old2 यंत्र("3") = (o2);		\
	रेजिस्टर __typeof__(*(p1)) __new1 यंत्र("4") = (n1);		\
	रेजिस्टर __typeof__(*(p2)) __new2 यंत्र("5") = (n2);		\
	पूर्णांक cc;								\
	यंत्र अस्थिर(							\
		"	cdsg	%[old],%[new],%[ptr]\n"			\
		"	ipm	%[cc]\n"				\
		"	srl	%[cc],28"				\
		: [cc] "=d" (cc), [old] "+d" (__old1), "+d" (__old2)	\
		: [new] "d" (__new1), "d" (__new2),			\
		  [ptr] "Q" (*(p1)), "Q" (*(p2))			\
		: "memory", "cc");					\
	!cc;								\
पूर्ण)

#घोषणा arch_cmpxchg_द्विगुन(p1, p2, o1, o2, n1, n2)			\
(अणु									\
	__typeof__(p1) __p1 = (p1);					\
	__typeof__(p2) __p2 = (p2);					\
	BUILD_BUG_ON(माप(*(p1)) != माप(दीर्घ));			\
	BUILD_BUG_ON(माप(*(p2)) != माप(दीर्घ));			\
	VM_BUG_ON((अचिन्हित दीर्घ)((__p1) + 1) != (अचिन्हित दीर्घ)(__p2));\
	__cmpxchg_द्विगुन(__p1, __p2, o1, o2, n1, n2);			\
पूर्ण)

#पूर्ण_अगर /* __ASM_CMPXCHG_H */
