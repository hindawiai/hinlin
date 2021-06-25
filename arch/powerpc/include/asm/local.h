<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_POWERPC_LOCAL_H
#घोषणा _ARCH_POWERPC_LOCAL_H

#अगर_घोषित CONFIG_PPC_BOOK3S_64

#समावेश <linux/percpu.h>
#समावेश <linux/atomic.h>
#समावेश <linux/irqflags.h>

#समावेश <यंत्र/hw_irq.h>

प्रकार काष्ठा
अणु
	दीर्घ v;
पूर्ण local_t;

#घोषणा LOCAL_INIT(i)	अणु (i) पूर्ण

अटल __अंतरभूत__ दीर्घ local_पढ़ो(स्थिर local_t *l)
अणु
	वापस READ_ONCE(l->v);
पूर्ण

अटल __अंतरभूत__ व्योम local_set(local_t *l, दीर्घ i)
अणु
	WRITE_ONCE(l->v, i);
पूर्ण

#घोषणा LOCAL_OP(op, c_op)						\
अटल __अंतरभूत__ व्योम local_##op(दीर्घ i, local_t *l)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	घातerpc_local_irq_pmu_save(flags);				\
	l->v c_op i;						\
	घातerpc_local_irq_pmu_restore(flags);				\
पूर्ण

#घोषणा LOCAL_OP_RETURN(op, c_op)					\
अटल __अंतरभूत__ दीर्घ local_##op##_वापस(दीर्घ a, local_t *l)		\
अणु									\
	दीर्घ t;								\
	अचिन्हित दीर्घ flags;						\
									\
	घातerpc_local_irq_pmu_save(flags);				\
	t = (l->v c_op a);						\
	घातerpc_local_irq_pmu_restore(flags);				\
									\
	वापस t;							\
पूर्ण

#घोषणा LOCAL_OPS(op, c_op)		\
	LOCAL_OP(op, c_op)		\
	LOCAL_OP_RETURN(op, c_op)

LOCAL_OPS(add, +=)
LOCAL_OPS(sub, -=)

#घोषणा local_add_negative(a, l)	(local_add_वापस((a), (l)) < 0)
#घोषणा local_inc_वापस(l)		local_add_वापस(1LL, l)
#घोषणा local_inc(l)			local_inc_वापस(l)

/*
 * local_inc_and_test - increment and test
 * @l: poपूर्णांकer of type local_t
 *
 * Atomically increments @l by 1
 * and वापसs true अगर the result is zero, or false क्रम all
 * other हालs.
 */
#घोषणा local_inc_and_test(l)		(local_inc_वापस(l) == 0)

#घोषणा local_dec_वापस(l)		local_sub_वापस(1LL, l)
#घोषणा local_dec(l)			local_dec_वापस(l)
#घोषणा local_sub_and_test(a, l)	(local_sub_वापस((a), (l)) == 0)
#घोषणा local_dec_and_test(l)		(local_dec_वापस((l)) == 0)

अटल __अंतरभूत__ दीर्घ local_cmpxchg(local_t *l, दीर्घ o, दीर्घ n)
अणु
	दीर्घ t;
	अचिन्हित दीर्घ flags;

	घातerpc_local_irq_pmu_save(flags);
	t = l->v;
	अगर (t == o)
		l->v = n;
	घातerpc_local_irq_pmu_restore(flags);

	वापस t;
पूर्ण

अटल __अंतरभूत__ दीर्घ local_xchg(local_t *l, दीर्घ n)
अणु
	दीर्घ t;
	अचिन्हित दीर्घ flags;

	घातerpc_local_irq_pmu_save(flags);
	t = l->v;
	l->v = n;
	घातerpc_local_irq_pmu_restore(flags);

	वापस t;
पूर्ण

/**
 * local_add_unless - add unless the number is a given value
 * @l: poपूर्णांकer of type local_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @l, so दीर्घ as it was not @u.
 * Returns non-zero अगर @l was not @u, and zero otherwise.
 */
अटल __अंतरभूत__ पूर्णांक local_add_unless(local_t *l, दीर्घ a, दीर्घ u)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	घातerpc_local_irq_pmu_save(flags);
	अगर (l->v != u) अणु
		l->v += a;
		ret = 1;
	पूर्ण
	घातerpc_local_irq_pmu_restore(flags);

	वापस ret;
पूर्ण

#घोषणा local_inc_not_zero(l)		local_add_unless((l), 1, 0)

/* Use these क्रम per-cpu local_t variables: on some archs they are
 * much more efficient than these naive implementations.  Note they take
 * a variable, not an address.
 */

#घोषणा __local_inc(l)		((l)->v++)
#घोषणा __local_dec(l)		((l)->v++)
#घोषणा __local_add(i,l)	((l)->v+=(i))
#घोषणा __local_sub(i,l)	((l)->v-=(i))

#अन्यथा /* CONFIG_PPC64 */

#समावेश <यंत्र-generic/local.h>

#पूर्ण_अगर /* CONFIG_PPC64 */

#पूर्ण_अगर /* _ARCH_POWERPC_LOCAL_H */
