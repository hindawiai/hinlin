<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MATH_H
#घोषणा _LINUX_MATH_H

#समावेश <यंत्र/भाग64.h>
#समावेश <uapi/linux/kernel.h>

/*
 * This looks more complex than it should be. But we need to
 * get the type क्रम the ~ right in round_करोwn (it needs to be
 * as wide as the result!), and we want to evaluate the macro
 * arguments just once each.
 */
#घोषणा __round_mask(x, y) ((__typeof__(x))((y)-1))

/**
 * round_up - round up to next specअगरied घातer of 2
 * @x: the value to round
 * @y: multiple to round up to (must be a घातer of 2)
 *
 * Rounds @x up to next multiple of @y (which must be a घातer of 2).
 * To perक्रमm arbitrary rounding up, use roundup() below.
 */
#घोषणा round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)

/**
 * round_करोwn - round करोwn to next specअगरied घातer of 2
 * @x: the value to round
 * @y: multiple to round करोwn to (must be a घातer of 2)
 *
 * Rounds @x करोwn to next multiple of @y (which must be a घातer of 2).
 * To perक्रमm arbitrary rounding करोwn, use roundकरोwn() below.
 */
#घोषणा round_करोwn(x, y) ((x) & ~__round_mask(x, y))

#घोषणा DIV_ROUND_UP __KERNEL_DIV_ROUND_UP

#घोषणा DIV_ROUND_DOWN_ULL(ll, d) \
	(अणु अचिन्हित दीर्घ दीर्घ _पंचांगp = (ll); करो_भाग(_पंचांगp, d); _पंचांगp; पूर्ण)

#घोषणा DIV_ROUND_UP_ULL(ll, d) \
	DIV_ROUND_DOWN_ULL((अचिन्हित दीर्घ दीर्घ)(ll) + (d) - 1, (d))

#अगर BITS_PER_LONG == 32
# define DIV_ROUND_UP_SECTOR_T(ll,d) DIV_ROUND_UP_ULL(ll, d)
#अन्यथा
# define DIV_ROUND_UP_SECTOR_T(ll,d) DIV_ROUND_UP(ll,d)
#पूर्ण_अगर

/**
 * roundup - round up to the next specअगरied multiple
 * @x: the value to up
 * @y: multiple to round up to
 *
 * Rounds @x up to next multiple of @y. If @y will always be a घातer
 * of 2, consider using the faster round_up().
 */
#घोषणा roundup(x, y) (					\
अणु							\
	typeof(y) __y = y;				\
	(((x) + (__y - 1)) / __y) * __y;		\
पूर्ण							\
)
/**
 * roundकरोwn - round करोwn to next specअगरied multiple
 * @x: the value to round
 * @y: multiple to round करोwn to
 *
 * Rounds @x करोwn to next multiple of @y. If @y will always be a घातer
 * of 2, consider using the faster round_करोwn().
 */
#घोषणा roundकरोwn(x, y) (				\
अणु							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
पूर्ण							\
)

/*
 * Divide positive or negative भागidend by positive or negative भागisor
 * and round to बंदst पूर्णांकeger. Result is undefined क्रम negative
 * भागisors अगर the भागidend variable type is अचिन्हित and क्रम negative
 * भागidends अगर the भागisor variable type is अचिन्हित.
 */
#घोषणा DIV_ROUND_CLOSEST(x, भागisor)(			\
अणु							\
	typeof(x) __x = x;				\
	typeof(भागisor) __d = भागisor;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(भागisor))-1) > 0 ||			\
	 (((__x) > 0) == ((__d) > 0))) ?		\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
पूर्ण							\
)
/*
 * Same as above but क्रम u64 भागidends. भागisor must be a 32-bit
 * number.
 */
#घोषणा DIV_ROUND_CLOSEST_ULL(x, भागisor)(		\
अणु							\
	typeof(भागisor) __d = भागisor;			\
	अचिन्हित दीर्घ दीर्घ _पंचांगp = (x) + (__d) / 2;	\
	करो_भाग(_पंचांगp, __d);				\
	_पंचांगp;						\
पूर्ण							\
)

/*
 * Multiplies an पूर्णांकeger by a fraction, जबतक aव्योमing unnecessary
 * overflow or loss of precision.
 */
#घोषणा mult_frac(x, numer, denom)(			\
अणु							\
	typeof(x) quot = (x) / (denom);			\
	typeof(x) rem  = (x) % (denom);			\
	(quot * (numer)) + ((rem * (numer)) / (denom));	\
पूर्ण							\
)

#घोषणा sector_भाग(a, b) करो_भाग(a, b)

/**
 * असल - वापस असलolute value of an argument
 * @x: the value.  If it is अचिन्हित type, it is converted to चिन्हित type first.
 *     अक्षर is treated as अगर it was चिन्हित (regardless of whether it really is)
 *     but the macro's वापस type is preserved as अक्षर.
 *
 * Return: an असलolute value of x.
 */
#घोषणा असल(x)	__असल_choose_expr(x, दीर्घ दीर्घ,				\
		__असल_choose_expr(x, दीर्घ,				\
		__असल_choose_expr(x, पूर्णांक,				\
		__असल_choose_expr(x, लघु,				\
		__असल_choose_expr(x, अक्षर,				\
		__builtin_choose_expr(					\
			__builtin_types_compatible_p(typeof(x), अक्षर),	\
			(अक्षर)(अणु चिन्हित अक्षर __x = (x); __x<0?-__x:__x; पूर्ण), \
			((व्योम)0)))))))

#घोषणा __असल_choose_expr(x, type, other) __builtin_choose_expr(	\
	__builtin_types_compatible_p(typeof(x),   चिन्हित type) ||	\
	__builtin_types_compatible_p(typeof(x), अचिन्हित type),		\
	(अणु चिन्हित type __x = (x); __x < 0 ? -__x : __x; पूर्ण), other)

/**
 * reciprocal_scale - "scale" a value पूर्णांकo range [0, ep_ro)
 * @val: value
 * @ep_ro: right खोलो पूर्णांकerval endpoपूर्णांक
 *
 * Perक्रमm a "reciprocal multiplication" in order to "scale" a value पूर्णांकo
 * range [0, @ep_ro), where the upper पूर्णांकerval endpoपूर्णांक is right-खोलो.
 * This is useful, e.g. क्रम accessing a index of an array containing
 * @ep_ro elements, क्रम example. Think of it as sort of modulus, only that
 * the result isn't that of modulo. ;) Note that अगर initial input is a
 * small value, then result will वापस 0.
 *
 * Return: a result based on @val in पूर्णांकerval [0, @ep_ro).
 */
अटल अंतरभूत u32 reciprocal_scale(u32 val, u32 ep_ro)
अणु
	वापस (u32)(((u64) val * ep_ro) >> 32);
पूर्ण

u64 पूर्णांक_घात(u64 base, अचिन्हित पूर्णांक exp);
अचिन्हित दीर्घ पूर्णांक_वर्ग_मूल(अचिन्हित दीर्घ);

#अगर BITS_PER_LONG < 64
u32 पूर्णांक_वर्ग_मूल64(u64 x);
#अन्यथा
अटल अंतरभूत u32 पूर्णांक_वर्ग_मूल64(u64 x)
अणु
	वापस (u32)पूर्णांक_वर्ग_मूल(x);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_MATH_H */
