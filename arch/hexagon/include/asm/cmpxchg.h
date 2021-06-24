<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * xchg/cmpxchg operations क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_CMPXCHG_H
#घोषणा _ASM_CMPXCHG_H

/*
 * __xchg - atomically exchange a रेजिस्टर and a memory location
 * @x: value to swap
 * @ptr: poपूर्णांकer to memory
 * @size:  size of the value
 *
 * Only 4 bytes supported currently.
 *
 * Note:  there was an errata क्रम V2 about .new's and memw_locked.
 *
 */
अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, अस्थिर व्योम *ptr,
				   पूर्णांक size)
अणु
	अचिन्हित दीर्घ retval;

	/*  Can't seem to use prपूर्णांकk or panic here, so just stop  */
	अगर (size != 4) करो अणु यंत्र अस्थिर("brkpt;\n"); पूर्ण जबतक (1);

	__यंत्र__ __अस्थिर__ (
	"1:	%0 = memw_locked(%1);\n"    /*  load पूर्णांकo retval */
	"	memw_locked(%1,P0) = %2;\n" /*  store पूर्णांकo memory */
	"	if (!P0) jump 1b;\n"
	: "=&r" (retval)
	: "r" (ptr), "r" (x)
	: "memory", "p0"
	);
	वापस retval;
पूर्ण

/*
 * Atomically swap the contents of a रेजिस्टर with memory.  Should be atomic
 * between multiple CPU's and within पूर्णांकerrupts on the same CPU.
 */
#घोषणा xchg(ptr, v) ((__typeof__(*(ptr)))__xchg((अचिन्हित दीर्घ)(v), (ptr), \
	माप(*(ptr))))

/*
 *  see rt-mutex-design.txt; cmpxchg supposedly checks अगर *ptr == A and swaps.
 *  looks just like atomic_cmpxchg on our arch currently with a bunch of
 *  variable casting.
 */

#घोषणा cmpxchg(ptr, old, new)					\
(अणु								\
	__typeof__(ptr) __ptr = (ptr);				\
	__typeof__(*(ptr)) __old = (old);			\
	__typeof__(*(ptr)) __new = (new);			\
	__typeof__(*(ptr)) __oldval = 0;			\
								\
	यंत्र अस्थिर(						\
		"1:	%0 = memw_locked(%1);\n"		\
		"	{ P0 = cmp.eq(%0,%2);\n"		\
		"	  if (!P0.new) jump:nt 2f; }\n"		\
		"	memw_locked(%1,p0) = %3;\n"		\
		"	if (!P0) jump 1b;\n"			\
		"2:\n"						\
		: "=&r" (__oldval)				\
		: "r" (__ptr), "r" (__old), "r" (__new)		\
		: "memory", "p0"				\
	);							\
	__oldval;						\
पूर्ण)

#पूर्ण_अगर /* _ASM_CMPXCHG_H */
