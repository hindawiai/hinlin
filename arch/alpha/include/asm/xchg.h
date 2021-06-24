<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_CMPXCHG_H
#त्रुटि Do not include xchg.h directly!
#अन्यथा
/*
 * xchg/xchg_local and cmpxchg/cmpxchg_local share the same code
 * except that local version करो not have the expensive memory barrier.
 * So this file is included twice from यंत्र/cmpxchg.h.
 */

/*
 * Atomic exchange.
 * Since it can be used to implement critical sections
 * it must clobber "memory" (also क्रम पूर्णांकerrupts in UP).
 */

अटल अंतरभूत अचिन्हित दीर्घ
____xchg(_u8, अस्थिर अक्षर *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ ret, पंचांगp, addr64;

	__यंत्र__ __अस्थिर__(
	"	andnot	%4,7,%3\n"
	"	insbl	%1,%4,%1\n"
	"1:	ldq_l	%2,0(%3)\n"
	"	extbl	%2,%4,%0\n"
	"	mskbl	%2,%4,%2\n"
	"	or	%1,%2,%2\n"
	"	stq_c	%2,0(%3)\n"
	"	beq	%2,2f\n"
	".subsection 2\n"
	"2:	br	1b\n"
	".previous"
	: "=&r" (ret), "=&r" (val), "=&r" (पंचांगp), "=&r" (addr64)
	: "r" ((दीर्घ)m), "1" (val) : "memory");

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
____xchg(_u16, अस्थिर लघु *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ ret, पंचांगp, addr64;

	__यंत्र__ __अस्थिर__(
	"	andnot	%4,7,%3\n"
	"	inswl	%1,%4,%1\n"
	"1:	ldq_l	%2,0(%3)\n"
	"	extwl	%2,%4,%0\n"
	"	mskwl	%2,%4,%2\n"
	"	or	%1,%2,%2\n"
	"	stq_c	%2,0(%3)\n"
	"	beq	%2,2f\n"
	".subsection 2\n"
	"2:	br	1b\n"
	".previous"
	: "=&r" (ret), "=&r" (val), "=&r" (पंचांगp), "=&r" (addr64)
	: "r" ((दीर्घ)m), "1" (val) : "memory");

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
____xchg(_u32, अस्थिर पूर्णांक *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ dummy;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l %0,%4\n"
	"	bis $31,%3,%1\n"
	"	stl_c %1,%2\n"
	"	beq %1,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	: "=&r" (val), "=&r" (dummy), "=m" (*m)
	: "rI" (val), "m" (*m) : "memory");

	वापस val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
____xchg(_u64, अस्थिर दीर्घ *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ dummy;

	__यंत्र__ __अस्थिर__(
	"1:	ldq_l %0,%4\n"
	"	bis $31,%3,%1\n"
	"	stq_c %1,%2\n"
	"	beq %1,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	: "=&r" (val), "=&r" (dummy), "=m" (*m)
	: "rI" (val), "m" (*m) : "memory");

	वापस val;
पूर्ण

/* This function करोesn't exist, so you'll get a linker error
   अगर something tries to करो an invalid xchg().  */
बाह्य व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

अटल __always_अंतरभूत अचिन्हित दीर्घ
____xchg(, अस्थिर व्योम *ptr, अचिन्हित दीर्घ x, पूर्णांक size)
अणु
	चयन (size) अणु
		हाल 1:
			वापस ____xchg(_u8, ptr, x);
		हाल 2:
			वापस ____xchg(_u16, ptr, x);
		हाल 4:
			वापस ____xchg(_u32, ptr, x);
		हाल 8:
			वापस ____xchg(_u64, ptr, x);
	पूर्ण
	__xchg_called_with_bad_poपूर्णांकer();
	वापस x;
पूर्ण

/*
 * Atomic compare and exchange.  Compare OLD with MEM, अगर identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */

अटल अंतरभूत अचिन्हित दीर्घ
____cmpxchg(_u8, अस्थिर अक्षर *m, अचिन्हित अक्षर old, अचिन्हित अक्षर new)
अणु
	अचिन्हित दीर्घ prev, पंचांगp, cmp, addr64;

	__यंत्र__ __अस्थिर__(
	"	andnot	%5,7,%4\n"
	"	insbl	%1,%5,%1\n"
	"1:	ldq_l	%2,0(%4)\n"
	"	extbl	%2,%5,%0\n"
	"	cmpeq	%0,%6,%3\n"
	"	beq	%3,2f\n"
	"	mskbl	%2,%5,%2\n"
	"	or	%1,%2,%2\n"
	"	stq_c	%2,0(%4)\n"
	"	beq	%2,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br	1b\n"
	".previous"
	: "=&r" (prev), "=&r" (new), "=&r" (पंचांगp), "=&r" (cmp), "=&r" (addr64)
	: "r" ((दीर्घ)m), "Ir" (old), "1" (new) : "memory");

	वापस prev;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
____cmpxchg(_u16, अस्थिर लघु *m, अचिन्हित लघु old, अचिन्हित लघु new)
अणु
	अचिन्हित दीर्घ prev, पंचांगp, cmp, addr64;

	__यंत्र__ __अस्थिर__(
	"	andnot	%5,7,%4\n"
	"	inswl	%1,%5,%1\n"
	"1:	ldq_l	%2,0(%4)\n"
	"	extwl	%2,%5,%0\n"
	"	cmpeq	%0,%6,%3\n"
	"	beq	%3,2f\n"
	"	mskwl	%2,%5,%2\n"
	"	or	%1,%2,%2\n"
	"	stq_c	%2,0(%4)\n"
	"	beq	%2,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br	1b\n"
	".previous"
	: "=&r" (prev), "=&r" (new), "=&r" (पंचांगp), "=&r" (cmp), "=&r" (addr64)
	: "r" ((दीर्घ)m), "Ir" (old), "1" (new) : "memory");

	वापस prev;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
____cmpxchg(_u32, अस्थिर पूर्णांक *m, पूर्णांक old, पूर्णांक new)
अणु
	अचिन्हित दीर्घ prev, cmp;

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l %0,%5\n"
	"	cmpeq %0,%3,%1\n"
	"	beq %1,2f\n"
	"	mov %4,%1\n"
	"	stl_c %1,%2\n"
	"	beq %1,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br 1b\n"
	".previous"
	: "=&r"(prev), "=&r"(cmp), "=m"(*m)
	: "r"((दीर्घ) old), "r"(new), "m"(*m) : "memory");

	वापस prev;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
____cmpxchg(_u64, अस्थिर दीर्घ *m, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev, cmp;

	__यंत्र__ __अस्थिर__(
	"1:	ldq_l %0,%5\n"
	"	cmpeq %0,%3,%1\n"
	"	beq %1,2f\n"
	"	mov %4,%1\n"
	"	stq_c %1,%2\n"
	"	beq %1,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br 1b\n"
	".previous"
	: "=&r"(prev), "=&r"(cmp), "=m"(*m)
	: "r"((दीर्घ) old), "r"(new), "m"(*m) : "memory");

	वापस prev;
पूर्ण

/* This function करोesn't exist, so you'll get a linker error
   अगर something tries to करो an invalid cmpxchg().  */
बाह्य व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

अटल __always_अंतरभूत अचिन्हित दीर्घ
____cmpxchg(, अस्थिर व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new,
	      पूर्णांक size)
अणु
	चयन (size) अणु
		हाल 1:
			वापस ____cmpxchg(_u8, ptr, old, new);
		हाल 2:
			वापस ____cmpxchg(_u16, ptr, old, new);
		हाल 4:
			वापस ____cmpxchg(_u32, ptr, old, new);
		हाल 8:
			वापस ____cmpxchg(_u64, ptr, old, new);
	पूर्ण
	__cmpxchg_called_with_bad_poपूर्णांकer();
	वापस old;
पूर्ण

#पूर्ण_अगर
