<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TYPECHECK_H_INCLUDED
#घोषणा TYPECHECK_H_INCLUDED

/*
 * Check at compile समय that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 */
#घोषणा typecheck(type,x) \
(अणु	type __dummy; \
	typeof(x) __dummy2; \
	(व्योम)(&__dummy == &__dummy2); \
	1; \
पूर्ण)

/*
 * Check at compile समय that 'function' is a certain type, or is a poपूर्णांकer
 * to that type (needs to use प्रकार क्रम the function type.)
 */
#घोषणा typecheck_fn(type,function) \
(अणु	typeof(type) __पंचांगp = function; \
	(व्योम)__पंचांगp; \
पूर्ण)

#पूर्ण_अगर		/* TYPECHECK_H_INCLUDED */
