<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_AVERAGE_H
#घोषणा _LINUX_AVERAGE_H

#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/log2.h>

/*
 * Exponentially weighted moving average (EWMA)
 *
 * This implements a fixed-precision EWMA algorithm, with both the
 * precision and fall-off coefficient determined at compile-समय
 * and built पूर्णांकo the generated helper funtions.
 *
 * The first argument to the macro is the name that will be used
 * क्रम the काष्ठा and helper functions.
 *
 * The second argument, the precision, expresses how many bits are
 * used क्रम the fractional part of the fixed-precision values.
 *
 * The third argument, the weight reciprocal, determines how the
 * new values will be weighed vs. the old state, new values will
 * get weight 1/weight_rcp and old values 1-1/weight_rcp. Note
 * that this parameter must be a घातer of two क्रम efficiency.
 */

#घोषणा DECLARE_EWMA(name, _precision, _weight_rcp)			\
	काष्ठा ewma_##name अणु						\
		अचिन्हित दीर्घ पूर्णांकernal;					\
	पूर्ण;								\
	अटल अंतरभूत व्योम ewma_##name##_init(काष्ठा ewma_##name *e)	\
	अणु								\
		BUILD_BUG_ON(!__builtin_स्थिरant_p(_precision));	\
		BUILD_BUG_ON(!__builtin_स्थिरant_p(_weight_rcp));	\
		/*							\
		 * Even अगर you want to feed it just 0/1 you should have	\
		 * some bits क्रम the non-fractional part...		\
		 */							\
		BUILD_BUG_ON((_precision) > 30);			\
		BUILD_BUG_ON_NOT_POWER_OF_2(_weight_rcp);		\
		e->पूर्णांकernal = 0;					\
	पूर्ण								\
	अटल अंतरभूत अचिन्हित दीर्घ					\
	ewma_##name##_पढ़ो(काष्ठा ewma_##name *e)			\
	अणु								\
		BUILD_BUG_ON(!__builtin_स्थिरant_p(_precision));	\
		BUILD_BUG_ON(!__builtin_स्थिरant_p(_weight_rcp));	\
		BUILD_BUG_ON((_precision) > 30);			\
		BUILD_BUG_ON_NOT_POWER_OF_2(_weight_rcp);		\
		वापस e->पूर्णांकernal >> (_precision);			\
	पूर्ण								\
	अटल अंतरभूत व्योम ewma_##name##_add(काष्ठा ewma_##name *e,	\
					     अचिन्हित दीर्घ val)		\
	अणु								\
		अचिन्हित दीर्घ पूर्णांकernal = READ_ONCE(e->पूर्णांकernal);	\
		अचिन्हित दीर्घ weight_rcp = ilog2(_weight_rcp);		\
		अचिन्हित दीर्घ precision = _precision;			\
									\
		BUILD_BUG_ON(!__builtin_स्थिरant_p(_precision));	\
		BUILD_BUG_ON(!__builtin_स्थिरant_p(_weight_rcp));	\
		BUILD_BUG_ON((_precision) > 30);			\
		BUILD_BUG_ON_NOT_POWER_OF_2(_weight_rcp);		\
									\
		WRITE_ONCE(e->पूर्णांकernal, पूर्णांकernal ?			\
			(((पूर्णांकernal << weight_rcp) - पूर्णांकernal) +	\
				(val << precision)) >> weight_rcp :	\
			(val << precision));				\
	पूर्ण

#पूर्ण_अगर /* _LINUX_AVERAGE_H */
