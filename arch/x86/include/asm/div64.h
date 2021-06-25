<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_DIV64_H
#घोषणा _ASM_X86_DIV64_H

#अगर_घोषित CONFIG_X86_32

#समावेश <linux/types.h>
#समावेश <linux/log2.h>

/*
 * करो_भाग() is NOT a C function. It wants to वापस
 * two values (the quotient and the reमुख्यder), but
 * since that करोesn't work very well in C, what it
 * करोes is:
 *
 * - modअगरies the 64-bit भागidend _in_place_
 * - वापसs the 32-bit reमुख्यder
 *
 * This ends up being the most efficient "calling
 * convention" on x86.
 */
#घोषणा करो_भाग(n, base)						\
(अणु								\
	अचिन्हित दीर्घ __upper, __low, __high, __mod, __base;	\
	__base = (base);					\
	अगर (__builtin_स्थिरant_p(__base) && is_घातer_of_2(__base)) अणु \
		__mod = n & (__base - 1);			\
		n >>= ilog2(__base);				\
	पूर्ण अन्यथा अणु						\
		यंत्र("" : "=a" (__low), "=d" (__high) : "A" (n));\
		__upper = __high;				\
		अगर (__high) अणु					\
			__upper = __high % (__base);		\
			__high = __high / (__base);		\
		पूर्ण						\
		यंत्र("divl %2" : "=a" (__low), "=d" (__mod)	\
			: "rm" (__base), "0" (__low), "1" (__upper));	\
		यंत्र("" : "=A" (n) : "a" (__low), "d" (__high));	\
	पूर्ण							\
	__mod;							\
पूर्ण)

अटल अंतरभूत u64 भाग_u64_rem(u64 भागidend, u32 भागisor, u32 *reमुख्यder)
अणु
	जोड़ अणु
		u64 v64;
		u32 v32[2];
	पूर्ण d = अणु भागidend पूर्ण;
	u32 upper;

	upper = d.v32[1];
	d.v32[1] = 0;
	अगर (upper >= भागisor) अणु
		d.v32[1] = upper / भागisor;
		upper %= भागisor;
	पूर्ण
	यंत्र ("divl %2" : "=a" (d.v32[0]), "=d" (*reमुख्यder) :
		"rm" (भागisor), "0" (d.v32[0]), "1" (upper));
	वापस d.v64;
पूर्ण
#घोषणा भाग_u64_rem	भाग_u64_rem

अटल अंतरभूत u64 mul_u32_u32(u32 a, u32 b)
अणु
	u32 high, low;

	यंत्र ("mull %[b]" : "=a" (low), "=d" (high)
			 : [a] "a" (a), [b] "rm" (b) );

	वापस low | ((u64)high) << 32;
पूर्ण
#घोषणा mul_u32_u32 mul_u32_u32

#अन्यथा
# include <यंत्र-generic/भाग64.h>

/*
 * Will generate an #DE when the result करोesn't fit u64, could fix with an
 * __ex_table[] entry when it becomes an issue.
 */
अटल अंतरभूत u64 mul_u64_u64_भाग_u64(u64 a, u64 mul, u64 भाग)
अणु
	u64 q;

	यंत्र ("mulq %2; divq %3" : "=a" (q)
				: "a" (a), "rm" (mul), "rm" (भाग)
				: "rdx");

	वापस q;
पूर्ण
#घोषणा mul_u64_u64_भाग_u64 mul_u64_u64_भाग_u64

अटल अंतरभूत u64 mul_u64_u32_भाग(u64 a, u32 mul, u32 भाग)
अणु
	वापस mul_u64_u64_भाग_u64(a, mul, भाग);
पूर्ण
#घोषणा mul_u64_u32_भाग	mul_u64_u32_भाग

#पूर्ण_अगर /* CONFIG_X86_32 */

#पूर्ण_अगर /* _ASM_X86_DIV64_H */
