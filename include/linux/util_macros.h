<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HELPER_MACROS_H_
#घोषणा _LINUX_HELPER_MACROS_H_

#घोषणा __find_बंदst(x, a, as, op)					\
(अणु									\
	typeof(as) __fc_i, __fc_as = (as) - 1;				\
	typeof(x) __fc_x = (x);						\
	typeof(*a) स्थिर *__fc_a = (a);					\
	क्रम (__fc_i = 0; __fc_i < __fc_as; __fc_i++) अणु			\
		अगर (__fc_x op DIV_ROUND_CLOSEST(__fc_a[__fc_i] +	\
						__fc_a[__fc_i + 1], 2))	\
			अवरोध;						\
	पूर्ण								\
	(__fc_i);							\
पूर्ण)

/**
 * find_बंदst - locate the बंदst element in a sorted array
 * @x: The reference value.
 * @a: The array in which to look क्रम the बंदst element. Must be sorted
 *  in ascending order.
 * @as: Size of 'a'.
 *
 * Returns the index of the element बंदst to 'x'.
 */
#घोषणा find_बंदst(x, a, as) __find_बंदst(x, a, as, <=)

/**
 * find_बंदst_descending - locate the बंदst element in a sorted array
 * @x: The reference value.
 * @a: The array in which to look क्रम the बंदst element. Must be sorted
 *  in descending order.
 * @as: Size of 'a'.
 *
 * Similar to find_बंदst() but 'a' is expected to be sorted in descending
 * order.
 */
#घोषणा find_बंदst_descending(x, a, as) __find_बंदst(x, a, as, >=)

#पूर्ण_अगर
