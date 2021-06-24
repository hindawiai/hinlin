<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MINMAX_H
#घोषणा _LINUX_MINMAX_H

#समावेश <linux/स्थिर.h>

/*
 * min()/max()/clamp() macros must accomplish three things:
 *
 * - aव्योम multiple evaluations of the arguments (so side-effects like
 *   "x++" happen only once) when non-स्थिरant.
 * - perक्रमm strict type-checking (to generate warnings instead of
 *   nasty runसमय surprises). See the "unnecessary" poपूर्णांकer comparison
 *   in __typecheck().
 * - retain result as a स्थिरant expressions when called with only
 *   स्थिरant expressions (to aव्योम tripping VLA warnings in stack
 *   allocation usage).
 */
#घोषणा __typecheck(x, y) \
	(!!(माप((typeof(x) *)1 == (typeof(y) *)1)))

#घोषणा __no_side_effects(x, y) \
		(__is_स्थिरexpr(x) && __is_स्थिरexpr(y))

#घोषणा __safe_cmp(x, y) \
		(__typecheck(x, y) && __no_side_effects(x, y))

#घोषणा __cmp(x, y, op)	((x) op (y) ? (x) : (y))

#घोषणा __cmp_once(x, y, unique_x, unique_y, op) (अणु	\
		typeof(x) unique_x = (x);		\
		typeof(y) unique_y = (y);		\
		__cmp(unique_x, unique_y, op); पूर्ण)

#घोषणा __careful_cmp(x, y, op) \
	__builtin_choose_expr(__safe_cmp(x, y), \
		__cmp(x, y, op), \
		__cmp_once(x, y, __UNIQUE_ID(__x), __UNIQUE_ID(__y), op))

/**
 * min - वापस minimum of two values of the same or compatible types
 * @x: first value
 * @y: second value
 */
#घोषणा min(x, y)	__careful_cmp(x, y, <)

/**
 * max - वापस maximum of two values of the same or compatible types
 * @x: first value
 * @y: second value
 */
#घोषणा max(x, y)	__careful_cmp(x, y, >)

/**
 * min3 - वापस minimum of three values
 * @x: first value
 * @y: second value
 * @z: third value
 */
#घोषणा min3(x, y, z) min((typeof(x))min(x, y), z)

/**
 * max3 - वापस maximum of three values
 * @x: first value
 * @y: second value
 * @z: third value
 */
#घोषणा max3(x, y, z) max((typeof(x))max(x, y), z)

/**
 * min_not_zero - वापस the minimum that is _not_ zero, unless both are zero
 * @x: value1
 * @y: value2
 */
#घोषणा min_not_zero(x, y) (अणु			\
	typeof(x) __x = (x);			\
	typeof(y) __y = (y);			\
	__x == 0 ? __y : ((__y == 0) ? __x : min(__x, __y)); पूर्ण)

/**
 * clamp - वापस a value clamped to a given range with strict typechecking
 * @val: current value
 * @lo: lowest allowable value
 * @hi: highest allowable value
 *
 * This macro करोes strict typechecking of @lo/@hi to make sure they are of the
 * same type as @val.  See the unnecessary poपूर्णांकer comparisons.
 */
#घोषणा clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)

/*
 * ..and अगर you can't take the strict
 * types, you can specअगरy one yourself.
 *
 * Or not use min/max/clamp at all, of course.
 */

/**
 * min_t - वापस minimum of two values, using the specअगरied type
 * @type: data type to use
 * @x: first value
 * @y: second value
 */
#घोषणा min_t(type, x, y)	__careful_cmp((type)(x), (type)(y), <)

/**
 * max_t - वापस maximum of two values, using the specअगरied type
 * @type: data type to use
 * @x: first value
 * @y: second value
 */
#घोषणा max_t(type, x, y)	__careful_cmp((type)(x), (type)(y), >)

/**
 * clamp_t - वापस a value clamped to a given range using a given type
 * @type: the type of variable to use
 * @val: current value
 * @lo: minimum allowable value
 * @hi: maximum allowable value
 *
 * This macro करोes no typechecking and uses temporary variables of type
 * @type to make all the comparisons.
 */
#घोषणा clamp_t(type, val, lo, hi) min_t(type, max_t(type, val, lo), hi)

/**
 * clamp_val - वापस a value clamped to a given range using val's type
 * @val: current value
 * @lo: minimum allowable value
 * @hi: maximum allowable value
 *
 * This macro करोes no typechecking and uses temporary variables of whatever
 * type the input argument @val is.  This is useful when @val is an अचिन्हित
 * type and @lo and @hi are literals that will otherwise be asचिन्हित a चिन्हित
 * पूर्णांकeger type.
 */
#घोषणा clamp_val(val, lo, hi) clamp_t(typeof(val), val, lo, hi)

/**
 * swap - swap values of @a and @b
 * @a: first value
 * @b: second value
 */
#घोषणा swap(a, b) \
	करो अणु typeof(a) __पंचांगp = (a); (a) = (b); (b) = __पंचांगp; पूर्ण जबतक (0)

#पूर्ण_अगर	/* _LINUX_MINMAX_H */
