<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Atomic operations क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_ATOMIC_H
#घोषणा _ASM_ATOMIC_H

#समावेश <linux/types.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

/*  Normal ग_लिखोs in our arch करोn't clear lock reservations  */

अटल अंतरभूत व्योम atomic_set(atomic_t *v, पूर्णांक new)
अणु
	यंत्र अस्थिर(
		"1:	r6 = memw_locked(%0);\n"
		"	memw_locked(%0,p0) = %1;\n"
		"	if (!P0) jump 1b;\n"
		:
		: "r" (&v->counter), "r" (new)
		: "memory", "p0", "r6"
	);
पूर्ण

#घोषणा atomic_set_release(v, i)	atomic_set((v), (i))

/**
 * atomic_पढ़ो - पढ़ोs a word, atomically
 * @v: poपूर्णांकer to atomic value
 *
 * Assumes all word पढ़ोs on our architecture are atomic.
 */
#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)

/**
 * atomic_xchg - atomic
 * @v: poपूर्णांकer to memory to change
 * @new: new value (technically passed in a रेजिस्टर -- see xchg)
 */
#घोषणा atomic_xchg(v, new)	(xchg(&((v)->counter), (new)))


/**
 * atomic_cmpxchg - atomic compare-and-exchange values
 * @v: poपूर्णांकer to value to change
 * @old:  desired old value to match
 * @new:  new value to put in
 *
 * Parameters are then poपूर्णांकer, value-in-रेजिस्टर, value-in-रेजिस्टर,
 * and the output is the old value.
 *
 * Apparently this is complicated क्रम archs that करोn't support
 * the memw_locked like we करो (or it's broken or whatever).
 *
 * Kind of the lynchpin of the rest of the generically defined routines.
 * Remember V2 had that bug with करोtnew predicate set by memw_locked.
 *
 * "old" is "expected" old val, __oldval is actual old value
 */
अटल अंतरभूत पूर्णांक atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक __oldval;

	यंत्र अस्थिर(
		"1:	%0 = memw_locked(%1);\n"
		"	{ P0 = cmp.eq(%0,%2);\n"
		"	  if (!P0.new) jump:nt 2f; }\n"
		"	memw_locked(%1,P0) = %3;\n"
		"	if (!P0) jump 1b;\n"
		"2:\n"
		: "=&r" (__oldval)
		: "r" (&v->counter), "r" (old), "r" (new)
		: "memory", "p0"
	);

	वापस __oldval;
पूर्ण

#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक output;							\
									\
	__यंत्र__ __अस्थिर__ (						\
		"1:	%0 = memw_locked(%1);\n"			\
		"	%0 = "#op "(%0,%2);\n"				\
		"	memw_locked(%1,P3)=%0;\n"			\
		"	if (!P3) jump 1b;\n"				\
		: "=&r" (output)					\
		: "r" (&v->counter), "r" (i)				\
		: "memory", "p3"					\
	);								\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	पूर्णांक output;							\
									\
	__यंत्र__ __अस्थिर__ (						\
		"1:	%0 = memw_locked(%1);\n"			\
		"	%0 = "#op "(%0,%2);\n"				\
		"	memw_locked(%1,P3)=%0;\n"			\
		"	if (!P3) jump 1b;\n"				\
		: "=&r" (output)					\
		: "r" (&v->counter), "r" (i)				\
		: "memory", "p3"					\
	);								\
	वापस output;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक output, val;						\
									\
	__यंत्र__ __अस्थिर__ (						\
		"1:	%0 = memw_locked(%2);\n"			\
		"	%1 = "#op "(%0,%3);\n"				\
		"	memw_locked(%2,P3)=%1;\n"			\
		"	if (!P3) jump 1b;\n"				\
		: "=&r" (output), "=&r" (val)				\
		: "r" (&v->counter), "r" (i)				\
		: "memory", "p3"					\
	);								\
	वापस output;							\
पूर्ण

#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_OP_RETURN(op) ATOMIC_FETCH_OP(op)

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

/**
 * atomic_fetch_add_unless - add unless the number is a given value
 * @v: poपूर्णांकer to value
 * @a: amount to add
 * @u: unless value is equal to u
 *
 * Returns old value.
 *
 */

अटल अंतरभूत पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक __oldval;
	रेजिस्टर पूर्णांक पंचांगp;

	यंत्र अस्थिर(
		"1:	%0 = memw_locked(%2);"
		"	{"
		"		p3 = cmp.eq(%0, %4);"
		"		if (p3.new) jump:nt 2f;"
		"		%1 = add(%0, %3);"
		"	}"
		"	memw_locked(%2, p3) = %1;"
		"	{"
		"		if (!p3) jump 1b;"
		"	}"
		"2:"
		: "=&r" (__oldval), "=&r" (पंचांगp)
		: "r" (v), "r" (a), "r" (u)
		: "memory", "p3"
	);
	वापस __oldval;
पूर्ण
#घोषणा atomic_fetch_add_unless atomic_fetch_add_unless

#पूर्ण_अगर
