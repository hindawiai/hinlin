<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TOOLS_ASM_GENERIC_ATOMIC_H
#घोषणा __TOOLS_ASM_GENERIC_ATOMIC_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 *
 * Excerpts obtained from the Linux kernel sources.
 */

#घोषणा ATOMIC_INIT(i)	अणु (i) पूर्ण

/**
 * atomic_पढ़ो - पढ़ो atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically पढ़ोs the value of @v.
 */
अटल अंतरभूत पूर्णांक atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	वापस READ_ONCE((v)->counter);
पूर्ण

/**
 * atomic_set - set atomic variable
 * @v: poपूर्णांकer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
अटल अंतरभूत व्योम atomic_set(atomic_t *v, पूर्णांक i)
अणु
        v->counter = i;
पूर्ण

/**
 * atomic_inc - increment atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically increments @v by 1.
 */
अटल अंतरभूत व्योम atomic_inc(atomic_t *v)
अणु
	__sync_add_and_fetch(&v->counter, 1);
पूर्ण

/**
 * atomic_dec_and_test - decrement and test
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically decrements @v by 1 and
 * वापसs true अगर the result is 0, or false क्रम all other
 * हालs.
 */
अटल अंतरभूत पूर्णांक atomic_dec_and_test(atomic_t *v)
अणु
	वापस __sync_sub_and_fetch(&v->counter, 1) == 0;
पूर्ण

#घोषणा cmpxchg(ptr, oldval, newval) \
	__sync_val_compare_and_swap(ptr, oldval, newval)

अटल अंतरभूत पूर्णांक atomic_cmpxchg(atomic_t *v, पूर्णांक oldval, पूर्णांक newval)
अणु
	वापस cmpxchg(&(v)->counter, oldval, newval);
पूर्ण

#पूर्ण_अगर /* __TOOLS_ASM_GENERIC_ATOMIC_H */
