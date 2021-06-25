<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_DIV64_H
#घोषणा _ASM_GENERIC_DIV64_H
/*
 * Copyright (C) 2003 Bernarकरो Innocenti <bernie@develer.com>
 * Based on क्रमmer यंत्र-ppc/भाग64.h and यंत्र-m68knommu/भाग64.h
 *
 * Optimization क्रम स्थिरant भागisors on 32-bit machines:
 * Copyright (C) 2006-2015 Nicolas Pitre
 *
 * The semantics of करो_भाग() is, in C++ notation, observing that the name
 * is a function-like macro and the n parameter has the semantics of a C++
 * reference:
 *
 * uपूर्णांक32_t करो_भाग(uपूर्णांक64_t &n, uपूर्णांक32_t base)
 * अणु
 * 	uपूर्णांक32_t reमुख्यder = n % base;
 * 	n = n / base;
 * 	वापस reमुख्यder;
 * पूर्ण
 *
 * NOTE: macro parameter n is evaluated multiple बार,
 *       beware of side effects!
 */

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

#अगर BITS_PER_LONG == 64

/**
 * करो_भाग - वापसs 2 values: calculate reमुख्यder and update new भागidend
 * @n: uपूर्णांक64_t भागidend (will be updated)
 * @base: uपूर्णांक32_t भागisor
 *
 * Summary:
 * ``uपूर्णांक32_t reमुख्यder = n % base;``
 * ``n = n / base;``
 *
 * Return: (uपूर्णांक32_t)reमुख्यder
 *
 * NOTE: macro parameter @n is evaluated multiple बार,
 * beware of side effects!
 */
# define करो_भाग(n,base) (अणु					\
	uपूर्णांक32_t __base = (base);				\
	uपूर्णांक32_t __rem;						\
	__rem = ((uपूर्णांक64_t)(n)) % __base;			\
	(n) = ((uपूर्णांक64_t)(n)) / __base;				\
	__rem;							\
 पूर्ण)

#या_अगर BITS_PER_LONG == 32

#समावेश <linux/log2.h>

/*
 * If the भागisor happens to be स्थिरant, we determine the appropriate
 * inverse at compile समय to turn the भागision पूर्णांकo a few अंतरभूत
 * multiplications which ought to be much faster. And yet only अगर compiling
 * with a sufficiently recent gcc version to perक्रमm proper 64-bit स्थिरant
 * propagation.
 *
 * (It is unक्रमtunate that gcc करोesn't perक्रमm all this पूर्णांकernally.)
 */

#अगर_अघोषित __भाग64_स्थिर32_is_OK
#घोषणा __भाग64_स्थिर32_is_OK (__GNUC__ >= 4)
#पूर्ण_अगर

#घोषणा __भाग64_स्थिर32(n, ___b)					\
(अणु									\
	/*								\
	 * Multiplication by reciprocal of b: n / b = n * (p / b) / p	\
	 *								\
	 * We rely on the fact that most of this code माला_लो optimized	\
	 * away at compile समय due to स्थिरant propagation and only	\
	 * a few multiplication inकाष्ठाions should reमुख्य.		\
	 * Hence this monstrous macro (अटल अंतरभूत करोesn't always	\
	 * करो the trick here).						\
	 */								\
	uपूर्णांक64_t ___res, ___x, ___t, ___m, ___n = (n);			\
	uपूर्णांक32_t ___p, ___bias;						\
									\
	/* determine MSB of b */					\
	___p = 1 << ilog2(___b);					\
									\
	/* compute m = ((p << 64) + b - 1) / b */			\
	___m = (~0ULL / ___b) * ___p;					\
	___m += (((~0ULL % ___b + 1) * ___p) + ___b - 1) / ___b;	\
									\
	/* one less than the भागidend with highest result */		\
	___x = ~0ULL / ___b * ___b - 1;					\
									\
	/* test our ___m with res = m * x / (p << 64) */		\
	___res = ((___m & 0xffffffff) * (___x & 0xffffffff)) >> 32;	\
	___t = ___res += (___m & 0xffffffff) * (___x >> 32);		\
	___res += (___x & 0xffffffff) * (___m >> 32);			\
	___t = (___res < ___t) ? (1ULL << 32) : 0;			\
	___res = (___res >> 32) + ___t;					\
	___res += (___m >> 32) * (___x >> 32);				\
	___res /= ___p;							\
									\
	/* Now sanitize and optimize what we've got. */			\
	अगर (~0ULL % (___b / (___b & -___b)) == 0) अणु			\
		/* special हाल, can be simplअगरied to ... */		\
		___n /= (___b & -___b);					\
		___m = ~0ULL / (___b / (___b & -___b));			\
		___p = 1;						\
		___bias = 1;						\
	पूर्ण अन्यथा अगर (___res != ___x / ___b) अणु				\
		/*							\
		 * We can't get away without a bias to compensate	\
		 * क्रम bit truncation errors.  To aव्योम it we'd need an	\
		 * additional bit to represent m which would overflow	\
		 * a 64-bit variable.					\
		 *							\
		 * Instead we करो m = p / b and n / b = (n * m + m) / p.	\
		 */							\
		___bias = 1;						\
		/* Compute m = (p << 64) / b */				\
		___m = (~0ULL / ___b) * ___p;				\
		___m += ((~0ULL % ___b + 1) * ___p) / ___b;		\
	पूर्ण अन्यथा अणु							\
		/*							\
		 * Reduce m / p, and try to clear bit 31 of m when	\
		 * possible, otherwise that'll need extra overflow	\
		 * handling later.					\
		 */							\
		uपूर्णांक32_t ___bits = -(___m & -___m);			\
		___bits |= ___m >> 32;					\
		___bits = (~___bits) << 1;				\
		/*							\
		 * If ___bits == 0 then setting bit 31 is  unaव्योमable.	\
		 * Simply apply the maximum possible reduction in that	\
		 * हाल. Otherwise the MSB of ___bits indicates the	\
		 * best reduction we should apply.			\
		 */							\
		अगर (!___bits) अणु						\
			___p /= (___m & -___m);				\
			___m /= (___m & -___m);				\
		पूर्ण अन्यथा अणु						\
			___p >>= ilog2(___bits);			\
			___m >>= ilog2(___bits);			\
		पूर्ण							\
		/* No bias needed. */					\
		___bias = 0;						\
	पूर्ण								\
									\
	/*								\
	 * Now we have a combination of 2 conditions:			\
	 *								\
	 * 1) whether or not we need to apply a bias, and		\
	 *								\
	 * 2) whether or not there might be an overflow in the cross	\
	 *    product determined by (___m & ((1 << 63) | (1 << 31))).	\
	 *								\
	 * Select the best way to करो (m_bias + m * n) / (1 << 64).	\
	 * From now on there will be actual runसमय code generated.	\
	 */								\
	___res = __arch_xprod_64(___m, ___n, ___bias);			\
									\
	___res /= ___p;							\
पूर्ण)

#अगर_अघोषित __arch_xprod_64
/*
 * Default C implementation क्रम __arch_xprod_64()
 *
 * Prototype: uपूर्णांक64_t __arch_xprod_64(स्थिर uपूर्णांक64_t m, uपूर्णांक64_t n, bool bias)
 * Semantic:  retval = ((bias ? m : 0) + m * n) >> 64
 *
 * The product is a 128-bit value, scaled करोwn to 64 bits.
 * Assuming स्थिरant propagation to optimize away unused conditional code.
 * Architectures may provide their own optimized assembly implementation.
 */
अटल अंतरभूत uपूर्णांक64_t __arch_xprod_64(स्थिर uपूर्णांक64_t m, uपूर्णांक64_t n, bool bias)
अणु
	uपूर्णांक32_t m_lo = m;
	uपूर्णांक32_t m_hi = m >> 32;
	uपूर्णांक32_t n_lo = n;
	uपूर्णांक32_t n_hi = n >> 32;
	uपूर्णांक64_t res;
	uपूर्णांक32_t res_lo, res_hi, पंचांगp;

	अगर (!bias) अणु
		res = ((uपूर्णांक64_t)m_lo * n_lo) >> 32;
	पूर्ण अन्यथा अगर (!(m & ((1ULL << 63) | (1ULL << 31)))) अणु
		/* there can't be any overflow here */
		res = (m + (uपूर्णांक64_t)m_lo * n_lo) >> 32;
	पूर्ण अन्यथा अणु
		res = m + (uपूर्णांक64_t)m_lo * n_lo;
		res_lo = res >> 32;
		res_hi = (res_lo < m_hi);
		res = res_lo | ((uपूर्णांक64_t)res_hi << 32);
	पूर्ण

	अगर (!(m & ((1ULL << 63) | (1ULL << 31)))) अणु
		/* there can't be any overflow here */
		res += (uपूर्णांक64_t)m_lo * n_hi;
		res += (uपूर्णांक64_t)m_hi * n_lo;
		res >>= 32;
	पूर्ण अन्यथा अणु
		res += (uपूर्णांक64_t)m_lo * n_hi;
		पंचांगp = res >> 32;
		res += (uपूर्णांक64_t)m_hi * n_lo;
		res_lo = res >> 32;
		res_hi = (res_lo < पंचांगp);
		res = res_lo | ((uपूर्णांक64_t)res_hi << 32);
	पूर्ण

	res += (uपूर्णांक64_t)m_hi * n_hi;

	वापस res;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __भाग64_32
बाह्य uपूर्णांक32_t __भाग64_32(uपूर्णांक64_t *भागidend, uपूर्णांक32_t भागisor);
#पूर्ण_अगर

/* The unnecessary poपूर्णांकer compare is there
 * to check क्रम type safety (n must be 64bit)
 */
# define करो_भाग(n,base) (अणु				\
	uपूर्णांक32_t __base = (base);			\
	uपूर्णांक32_t __rem;					\
	(व्योम)(((typeof((n)) *)0) == ((uपूर्णांक64_t *)0));	\
	अगर (__builtin_स्थिरant_p(__base) &&		\
	    is_घातer_of_2(__base)) अणु			\
		__rem = (n) & (__base - 1);		\
		(n) >>= ilog2(__base);			\
	पूर्ण अन्यथा अगर (__भाग64_स्थिर32_is_OK &&		\
		   __builtin_स्थिरant_p(__base) &&	\
		   __base != 0) अणु			\
		uपूर्णांक32_t __res_lo, __n_lo = (n);	\
		(n) = __भाग64_स्थिर32(n, __base);	\
		/* the reमुख्यder can be computed with 32-bit regs */ \
		__res_lo = (n);				\
		__rem = __n_lo - __res_lo * __base;	\
	पूर्ण अन्यथा अगर (likely(((n) >> 32) == 0)) अणु		\
		__rem = (uपूर्णांक32_t)(n) % __base;		\
		(n) = (uपूर्णांक32_t)(n) / __base;		\
	पूर्ण अन्यथा 						\
		__rem = __भाग64_32(&(n), __base);	\
	__rem;						\
 पूर्ण)

#अन्यथा /* BITS_PER_LONG == ?? */

# error करो_भाग() करोes not yet support the C64

#पूर्ण_अगर /* BITS_PER_LONG */

#पूर्ण_अगर /* _ASM_GENERIC_DIV64_H */
