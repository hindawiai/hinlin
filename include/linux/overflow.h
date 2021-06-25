<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
#अगर_अघोषित __LINUX_OVERFLOW_H
#घोषणा __LINUX_OVERFLOW_H

#समावेश <linux/compiler.h>
#समावेश <linux/सीमा.स>

/*
 * In the fallback code below, we need to compute the minimum and
 * maximum values representable in a given type. These macros may also
 * be useful अन्यथाwhere, so we provide them outside the
 * COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW block.
 *
 * It would seem more obvious to करो something like
 *
 * #घोषणा type_min(T) (T)(is_चिन्हित_type(T) ? (T)1 << (8*माप(T)-1) : 0)
 * #घोषणा type_max(T) (T)(is_चिन्हित_type(T) ? ((T)1 << (8*माप(T)-1)) - 1 : ~(T)0)
 *
 * Unक्रमtunately, the middle expressions, strictly speaking, have
 * undefined behaviour, and at least some versions of gcc warn about
 * the type_max expression (but not अगर -fsanitize=undefined is in
 * effect; in that हाल, the warning is deferred to runसमय...).
 *
 * The slightly excessive casting in type_min is to make sure the
 * macros also produce sensible values क्रम the exotic type _Bool. [The
 * overflow checkers only almost work क्रम _Bool, but that's
 * a-feature-not-a-bug, since people shouldn't be करोing arithmetic on
 * _Bools. Besides, the gcc builtins करोn't allow _Bool* as third
 * argument.]
 *
 * Idea stolen from
 * https://mail-index.netbsd.org/tech-misc/2007/02/05/0000.hपंचांगl -
 * credit to Christian Biere.
 */
#घोषणा is_चिन्हित_type(type)       (((type)(-1)) < (type)1)
#घोषणा __type_half_max(type) ((type)1 << (8*माप(type) - 1 - is_चिन्हित_type(type)))
#घोषणा type_max(T) ((T)((__type_half_max(T) - 1) + __type_half_max(T)))
#घोषणा type_min(T) ((T)((T)-type_max(T)-(T)1))

/*
 * Aव्योमs triggering -Wtype-limits compilation warning,
 * जबतक using अचिन्हित data types to check a < 0.
 */
#घोषणा is_non_negative(a) ((a) > 0 || (a) == 0)
#घोषणा is_negative(a) (!(is_non_negative(a)))

/*
 * Allows क्रम effectively applying __must_check to a macro so we can have
 * both the type-agnostic benefits of the macros जबतक also being able to
 * enक्रमce that the वापस value is, in fact, checked.
 */
अटल अंतरभूत bool __must_check __must_check_overflow(bool overflow)
अणु
	वापस unlikely(overflow);
पूर्ण

#अगर_घोषित COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW
/*
 * For simplicity and code hygiene, the fallback code below insists on
 * a, b and *d having the same type (similar to the min() and max()
 * macros), whereas gcc's type-generic overflow checkers accept
 * dअगरferent types. Hence we करोn't just make check_add_overflow an
 * alias क्रम __builtin_add_overflow, but add type checks similar to
 * below.
 */
#घोषणा check_add_overflow(a, b, d) __must_check_overflow((अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	__builtin_add_overflow(__a, __b, __d);	\
पूर्ण))

#घोषणा check_sub_overflow(a, b, d) __must_check_overflow((अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	__builtin_sub_overflow(__a, __b, __d);	\
पूर्ण))

#घोषणा check_mul_overflow(a, b, d) __must_check_overflow((अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	__builtin_mul_overflow(__a, __b, __d);	\
पूर्ण))

#अन्यथा


/* Checking क्रम अचिन्हित overflow is relatively easy without causing UB. */
#घोषणा __अचिन्हित_add_overflow(a, b, d) (अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	*__d = __a + __b;			\
	*__d < __a;				\
पूर्ण)
#घोषणा __अचिन्हित_sub_overflow(a, b, d) (अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	*__d = __a - __b;			\
	__a < __b;				\
पूर्ण)
/*
 * If one of a or b is a compile-समय स्थिरant, this aव्योमs a भागision.
 */
#घोषणा __अचिन्हित_mul_overflow(a, b, d) (अणु		\
	typeof(a) __a = (a);				\
	typeof(b) __b = (b);				\
	typeof(d) __d = (d);				\
	(व्योम) (&__a == &__b);				\
	(व्योम) (&__a == __d);				\
	*__d = __a * __b;				\
	__builtin_स्थिरant_p(__b) ?			\
	  __b > 0 && __a > type_max(typeof(__a)) / __b : \
	  __a > 0 && __b > type_max(typeof(__b)) / __a;	 \
पूर्ण)

/*
 * For चिन्हित types, detecting overflow is much harder, especially अगर
 * we want to aव्योम UB. But the पूर्णांकerface of these macros is such that
 * we must provide a result in *d, and in fact we must produce the
 * result promised by gcc's builtins, which is simply the possibly
 * wrapped-around value. Fortunately, we can just क्रमmally करो the
 * operations in the widest relevant अचिन्हित type (u64) and then
 * truncate the result - gcc is smart enough to generate the same code
 * with and without the (u64) casts.
 */

/*
 * Adding two चिन्हित पूर्णांकegers can overflow only अगर they have the same
 * sign, and overflow has happened अगरf the result has the opposite
 * sign.
 */
#घोषणा __चिन्हित_add_overflow(a, b, d) (अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	*__d = (u64)__a + (u64)__b;		\
	(((~(__a ^ __b)) & (*__d ^ __a))	\
		& type_min(typeof(__a))) != 0;	\
पूर्ण)

/*
 * Subtraction is similar, except that overflow can now happen only
 * when the signs are opposite. In this हाल, overflow has happened अगर
 * the result has the opposite sign of a.
 */
#घोषणा __चिन्हित_sub_overflow(a, b, d) (अणु	\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	typeof(d) __d = (d);			\
	(व्योम) (&__a == &__b);			\
	(व्योम) (&__a == __d);			\
	*__d = (u64)__a - (u64)__b;		\
	((((__a ^ __b)) & (*__d ^ __a))		\
		& type_min(typeof(__a))) != 0;	\
पूर्ण)

/*
 * Signed multiplication is rather hard. gcc always follows C99, so
 * भागision is truncated towards 0. This means that we can ग_लिखो the
 * overflow check like this:
 *
 * (a > 0 && (b > MAX/a || b < MIN/a)) ||
 * (a < -1 && (b > MIN/a || b < MAX/a) ||
 * (a == -1 && b == MIN)
 *
 * The redundant casts of -1 are to silence an annoying -Wtype-limits
 * (included in -Wextra) warning: When the type is u8 or u16, the
 * __b_c_e in check_mul_overflow obviously selects
 * __अचिन्हित_mul_overflow, but unक्रमtunately gcc still parses this
 * code and warns about the limited range of __b.
 */

#घोषणा __चिन्हित_mul_overflow(a, b, d) (अणु				\
	typeof(a) __a = (a);						\
	typeof(b) __b = (b);						\
	typeof(d) __d = (d);						\
	typeof(a) __पंचांगax = type_max(typeof(a));				\
	typeof(a) __पंचांगin = type_min(typeof(a));				\
	(व्योम) (&__a == &__b);						\
	(व्योम) (&__a == __d);						\
	*__d = (u64)__a * (u64)__b;					\
	(__b > 0   && (__a > __पंचांगax/__b || __a < __पंचांगin/__b)) ||	\
	(__b < (typeof(__b))-1  && (__a > __पंचांगin/__b || __a < __पंचांगax/__b)) || \
	(__b == (typeof(__b))-1 && __a == __पंचांगin);			\
पूर्ण)


#घोषणा check_add_overflow(a, b, d)	__must_check_overflow(		\
	__builtin_choose_expr(is_चिन्हित_type(typeof(a)),		\
			__चिन्हित_add_overflow(a, b, d),			\
			__अचिन्हित_add_overflow(a, b, d)))

#घोषणा check_sub_overflow(a, b, d)	__must_check_overflow(		\
	__builtin_choose_expr(is_चिन्हित_type(typeof(a)),		\
			__चिन्हित_sub_overflow(a, b, d),			\
			__अचिन्हित_sub_overflow(a, b, d)))

#घोषणा check_mul_overflow(a, b, d)	__must_check_overflow(		\
	__builtin_choose_expr(is_चिन्हित_type(typeof(a)),		\
			__चिन्हित_mul_overflow(a, b, d),			\
			__अचिन्हित_mul_overflow(a, b, d)))

#पूर्ण_अगर /* COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW */

/** check_shl_overflow() - Calculate a left-shअगरted value and check overflow
 *
 * @a: Value to be shअगरted
 * @s: How many bits left to shअगरt
 * @d: Poपूर्णांकer to where to store the result
 *
 * Computes *@d = (@a << @s)
 *
 * Returns true अगर '*d' cannot hold the result or when 'a << s' doesn't
 * make sense. Example conditions:
 * - 'a << s' causes bits to be lost when stored in *d.
 * - 's' is garbage (e.g. negative) or so large that the result of
 *   'a << s' is guaranteed to be 0.
 * - 'a' is negative.
 * - 'a << s' sets the sign bit, if any, in '*d'.
 *
 * '*d' will hold the results of the attempted shअगरt, but is not
 * considered "safe for use" अगर true is वापसed.
 */
#घोषणा check_shl_overflow(a, s, d) __must_check_overflow((अणु		\
	typeof(a) _a = a;						\
	typeof(s) _s = s;						\
	typeof(d) _d = d;						\
	u64 _a_full = _a;						\
	अचिन्हित पूर्णांक _to_shअगरt =					\
		is_non_negative(_s) && _s < 8 * माप(*d) ? _s : 0;	\
	*_d = (_a_full << _to_shअगरt);					\
	(_to_shअगरt != _s || is_negative(*_d) || is_negative(_a) ||	\
	(*_d >> _to_shअगरt) != _a);					\
पूर्ण))

/**
 * array_size() - Calculate size of 2-dimensional array.
 *
 * @a: dimension one
 * @b: dimension two
 *
 * Calculates size of 2-dimensional array: @a * @b.
 *
 * Returns: number of bytes needed to represent the array or SIZE_MAX on
 * overflow.
 */
अटल अंतरभूत __must_check माप_प्रकार array_size(माप_प्रकार a, माप_प्रकार b)
अणु
	माप_प्रकार bytes;

	अगर (check_mul_overflow(a, b, &bytes))
		वापस SIZE_MAX;

	वापस bytes;
पूर्ण

/**
 * array3_size() - Calculate size of 3-dimensional array.
 *
 * @a: dimension one
 * @b: dimension two
 * @c: dimension three
 *
 * Calculates size of 3-dimensional array: @a * @b * @c.
 *
 * Returns: number of bytes needed to represent the array or SIZE_MAX on
 * overflow.
 */
अटल अंतरभूत __must_check माप_प्रकार array3_size(माप_प्रकार a, माप_प्रकार b, माप_प्रकार c)
अणु
	माप_प्रकार bytes;

	अगर (check_mul_overflow(a, b, &bytes))
		वापस SIZE_MAX;
	अगर (check_mul_overflow(bytes, c, &bytes))
		वापस SIZE_MAX;

	वापस bytes;
पूर्ण

/*
 * Compute a*b+c, वापसing SIZE_MAX on overflow. Internal helper क्रम
 * काष्ठा_size() below.
 */
अटल अंतरभूत __must_check माप_प्रकार __ab_c_size(माप_प्रकार a, माप_प्रकार b, माप_प्रकार c)
अणु
	माप_प्रकार bytes;

	अगर (check_mul_overflow(a, b, &bytes))
		वापस SIZE_MAX;
	अगर (check_add_overflow(bytes, c, &bytes))
		वापस SIZE_MAX;

	वापस bytes;
पूर्ण

/**
 * काष्ठा_size() - Calculate size of काष्ठाure with trailing array.
 * @p: Poपूर्णांकer to the काष्ठाure.
 * @member: Name of the array member.
 * @count: Number of elements in the array.
 *
 * Calculates size of memory needed क्रम काष्ठाure @p followed by an
 * array of @count number of @member elements.
 *
 * Return: number of bytes needed or SIZE_MAX on overflow.
 */
#घोषणा काष्ठा_size(p, member, count)					\
	__ab_c_size(count,						\
		    माप(*(p)->member) + __must_be_array((p)->member),\
		    माप(*(p)))

/**
 * flex_array_size() - Calculate size of a flexible array member
 *                     within an enclosing काष्ठाure.
 *
 * @p: Poपूर्णांकer to the काष्ठाure.
 * @member: Name of the flexible array member.
 * @count: Number of elements in the array.
 *
 * Calculates size of a flexible array of @count number of @member
 * elements, at the end of काष्ठाure @p.
 *
 * Return: number of bytes needed or SIZE_MAX on overflow.
 */
#घोषणा flex_array_size(p, member, count)				\
	array_size(count,						\
		    माप(*(p)->member) + __must_be_array((p)->member))

#पूर्ण_अगर /* __LINUX_OVERFLOW_H */
