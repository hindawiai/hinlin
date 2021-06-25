<शैली गुरु>
/*
 * include/यंत्र-xtensa/atomic.h
 *
 * Atomic operations that C can't guarantee us.  Useful क्रम resource counting..
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2008 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_ATOMIC_H
#घोषणा _XTENSA_ATOMIC_H

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

/*
 * This Xtensa implementation assumes that the right mechanism
 * क्रम exclusion is क्रम locking पूर्णांकerrupts to level EXCM_LEVEL.
 *
 * Locking पूर्णांकerrupts looks like this:
 *
 *    rsil a15, TOPLEVEL
 *    <code>
 *    wsr  a15, PS
 *    rsync
 *
 * Note that a15 is used here because the रेजिस्टर allocation
 * करोne by the compiler is not guaranteed and a winकरोw overflow
 * may not occur between the rsil and wsr inकाष्ठाions. By using
 * a15 in the rsil, the machine is guaranteed to be in a state
 * where no रेजिस्टर reference will cause an overflow.
 */

/**
 * atomic_पढ़ो - पढ़ो atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically पढ़ोs the value of @v.
 */
#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)

/**
 * atomic_set - set atomic variable
 * @v: poपूर्णांकer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
#घोषणा atomic_set(v,i)		WRITE_ONCE((v)->counter, (i))

#अगर XCHAL_HAVE_EXCLUSIVE
#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32ex   %[tmp], %[addr]\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			"       s32ex   %[result], %[addr]\n"		\
			"       getex   %[result]\n"			\
			"       beqz    %[result], 1b\n"		\
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp)	\
			: [i] "a" (i), [addr] "a" (v)			\
			: "memory"					\
			);						\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32ex   %[tmp], %[addr]\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			"       s32ex   %[result], %[addr]\n"		\
			"       getex   %[result]\n"			\
			"       beqz    %[result], 1b\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp)	\
			: [i] "a" (i), [addr] "a" (v)			\
			: "memory"					\
			);						\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32ex   %[tmp], %[addr]\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			"       s32ex   %[result], %[addr]\n"		\
			"       getex   %[result]\n"			\
			"       beqz    %[result], 1b\n"		\
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp)	\
			: [i] "a" (i), [addr] "a" (v)			\
			: "memory"					\
			);						\
									\
	वापस पंचांगp;							\
पूर्ण

#या_अगर XCHAL_HAVE_S32C1I
#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t * v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32i    %[tmp], %[mem]\n"		\
			"       wsr     %[tmp], scompare1\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			"       s32c1i  %[result], %[mem]\n"		\
			"       bne     %[result], %[tmp], 1b\n"	\
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "memory"					\
			);						\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t * v)		\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32i    %[tmp], %[mem]\n"		\
			"       wsr     %[tmp], scompare1\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			"       s32c1i  %[result], %[mem]\n"		\
			"       bne     %[result], %[tmp], 1b\n"	\
			"       " #op " %[result], %[result], %[i]\n"	\
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "memory"					\
			);						\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t * v)		\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32i    %[tmp], %[mem]\n"		\
			"       wsr     %[tmp], scompare1\n"		\
			"       " #op " %[result], %[tmp], %[i]\n"	\
			"       s32c1i  %[result], %[mem]\n"		\
			"       bne     %[result], %[tmp], 1b\n"	\
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "memory"					\
			);						\
									\
	वापस result;							\
पूर्ण

#अन्यथा /* XCHAL_HAVE_S32C1I */

#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t * v)			\
अणु									\
	अचिन्हित पूर्णांक vval;						\
									\
	__यंत्र__ __अस्थिर__(						\
			"       rsil    a15, "__stringअगरy(TOPLEVEL)"\n"	\
			"       l32i    %[result], %[mem]\n"		\
			"       " #op " %[result], %[result], %[i]\n"	\
			"       s32i    %[result], %[mem]\n"		\
			"       wsr     a15, ps\n"			\
			"       rsync\n"				\
			: [result] "=&a" (vval), [mem] "+m" (*v)	\
			: [i] "a" (i)					\
			: "a15", "memory"				\
			);						\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t * v)		\
अणु									\
	अचिन्हित पूर्णांक vval;						\
									\
	__यंत्र__ __अस्थिर__(						\
			"       rsil    a15,"__stringअगरy(TOPLEVEL)"\n"	\
			"       l32i    %[result], %[mem]\n"		\
			"       " #op " %[result], %[result], %[i]\n"	\
			"       s32i    %[result], %[mem]\n"		\
			"       wsr     a15, ps\n"			\
			"       rsync\n"				\
			: [result] "=&a" (vval), [mem] "+m" (*v)	\
			: [i] "a" (i)					\
			: "a15", "memory"				\
			);						\
									\
	वापस vval;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t * v)		\
अणु									\
	अचिन्हित पूर्णांक पंचांगp, vval;						\
									\
	__यंत्र__ __अस्थिर__(						\
			"       rsil    a15,"__stringअगरy(TOPLEVEL)"\n"	\
			"       l32i    %[result], %[mem]\n"		\
			"       " #op " %[tmp], %[result], %[i]\n"	\
			"       s32i    %[tmp], %[mem]\n"		\
			"       wsr     a15, ps\n"			\
			"       rsync\n"				\
			: [result] "=&a" (vval), [पंचांगp] "=&a" (पंचांगp),	\
			  [mem] "+m" (*v)				\
			: [i] "a" (i)					\
			: "a15", "memory"				\
			);						\
									\
	वापस vval;							\
पूर्ण

#पूर्ण_अगर /* XCHAL_HAVE_S32C1I */

#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op) ATOMIC_OP_RETURN(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(or)
ATOMIC_OPS(xor)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#घोषणा atomic_cmpxchg(v, o, n) ((पूर्णांक)cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#पूर्ण_अगर /* _XTENSA_ATOMIC_H */
