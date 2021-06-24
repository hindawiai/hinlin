<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 64-bit atomic xchg() and cmpxchg() definitions.
 *
 * Copyright (C) 1996, 1997, 2000 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित __ARCH_SPARC64_CMPXCHG__
#घोषणा __ARCH_SPARC64_CMPXCHG__

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32(अस्थिर पूर्णांक *m, पूर्णांक old, पूर्णांक new)
अणु
	__यंत्र__ __अस्थिर__("cas [%2], %3, %0"
			     : "=&r" (new)
			     : "0" (new), "r" (m), "r" (old)
			     : "memory");

	वापस new;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg32(__अस्थिर__ अचिन्हित पूर्णांक *m, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	__यंत्र__ __अस्थिर__(
"	mov		%0, %1\n"
"1:	lduw		[%4], %2\n"
"	cas		[%4], %2, %0\n"
"	cmp		%2, %0\n"
"	bne,a,pn	%%icc, 1b\n"
"	 mov		%1, %0\n"
	: "=&r" (val), "=&r" (पंचांगp1), "=&r" (पंचांगp2)
	: "0" (val), "r" (m)
	: "cc", "memory");
	वापस val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg64(__अस्थिर__ अचिन्हित दीर्घ *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	__यंत्र__ __अस्थिर__(
"	mov		%0, %1\n"
"1:	ldx		[%4], %2\n"
"	casx		[%4], %2, %0\n"
"	cmp		%2, %0\n"
"	bne,a,pn	%%xcc, 1b\n"
"	 mov		%1, %0\n"
	: "=&r" (val), "=&r" (पंचांगp1), "=&r" (पंचांगp2)
	: "0" (val), "r" (m)
	: "cc", "memory");
	वापस val;
पूर्ण

#घोषणा xchg(ptr,x)							\
(अणु	__typeof__(*(ptr)) __ret;					\
	__ret = (__typeof__(*(ptr)))					\
		__xchg((अचिन्हित दीर्घ)(x), (ptr), माप(*(ptr)));	\
	__ret;								\
पूर्ण)

व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

/*
 * Use 4 byte cas inकाष्ठाion to achieve 2 byte xchg. Main logic
 * here is to get the bit shअगरt of the byte we are पूर्णांकerested in.
 * The XOR is handy क्रम reversing the bits क्रम big-endian byte order.
 */
अटल अंतरभूत अचिन्हित दीर्घ
xchg16(__अस्थिर__ अचिन्हित लघु *m, अचिन्हित लघु val)
अणु
	अचिन्हित दीर्घ maddr = (अचिन्हित दीर्घ)m;
	पूर्णांक bit_shअगरt = (((अचिन्हित दीर्घ)m & 2) ^ 2) << 3;
	अचिन्हित पूर्णांक mask = 0xffff << bit_shअगरt;
	अचिन्हित पूर्णांक *ptr = (अचिन्हित पूर्णांक  *) (maddr & ~2);
	अचिन्हित पूर्णांक old32, new32, load32;

	/* Read the old value */
	load32 = *ptr;

	करो अणु
		old32 = load32;
		new32 = (load32 & (~mask)) | val << bit_shअगरt;
		load32 = __cmpxchg_u32(ptr, old32, new32);
	पूर्ण जबतक (load32 != old32);

	वापस (load32 & mask) >> bit_shअगरt;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, __अस्थिर__ व्योम * ptr,
				       पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 2:
		वापस xchg16(ptr, x);
	हाल 4:
		वापस xchg32(ptr, x);
	हाल 8:
		वापस xchg64(ptr, x);
	पूर्ण
	__xchg_called_with_bad_poपूर्णांकer();
	वापस x;
पूर्ण

/*
 * Atomic compare and exchange.  Compare OLD with MEM, अगर identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */

#समावेश <यंत्र-generic/cmpxchg-local.h>


अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u64(अस्थिर दीर्घ *m, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	__यंत्र__ __अस्थिर__("casx [%2], %3, %0"
			     : "=&r" (new)
			     : "0" (new), "r" (m), "r" (old)
			     : "memory");

	वापस new;
पूर्ण

/*
 * Use 4 byte cas inकाष्ठाion to achieve 1 byte cmpxchg. Main logic
 * here is to get the bit shअगरt of the byte we are पूर्णांकerested in.
 * The XOR is handy क्रम reversing the bits क्रम big-endian byte order
 */
अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u8(अस्थिर अचिन्हित अक्षर *m, अचिन्हित अक्षर old, अचिन्हित अक्षर new)
अणु
	अचिन्हित दीर्घ maddr = (अचिन्हित दीर्घ)m;
	पूर्णांक bit_shअगरt = (((अचिन्हित दीर्घ)m & 3) ^ 3) << 3;
	अचिन्हित पूर्णांक mask = 0xff << bit_shअगरt;
	अचिन्हित पूर्णांक *ptr = (अचिन्हित पूर्णांक *) (maddr & ~3);
	अचिन्हित पूर्णांक old32, new32, load;
	अचिन्हित पूर्णांक load32 = *ptr;

	करो अणु
		new32 = (load32 & ~mask) | (new << bit_shअगरt);
		old32 = (load32 & ~mask) | (old << bit_shअगरt);
		load32 = __cmpxchg_u32(ptr, old32, new32);
		अगर (load32 == old32)
			वापस old;
		load = (load32 & mask) >> bit_shअगरt;
	पूर्ण जबतक (load == old);

	वापस load;
पूर्ण

/* This function करोesn't exist, so you'll get a linker error
   अगर something tries to करो an invalid cmpxchg().  */
व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
		हाल 1:
			वापस __cmpxchg_u8(ptr, old, new);
		हाल 4:
			वापस __cmpxchg_u32(ptr, old, new);
		हाल 8:
			वापस __cmpxchg_u64(ptr, old, new);
	पूर्ण
	__cmpxchg_called_with_bad_poपूर्णांकer();
	वापस old;
पूर्ण

#घोषणा cmpxchg(ptr,o,n)						 \
  (अणु									 \
     __typeof__(*(ptr)) _o_ = (o);					 \
     __typeof__(*(ptr)) _n_ = (n);					 \
     (__typeof__(*(ptr))) __cmpxchg((ptr), (अचिन्हित दीर्घ)_o_,		 \
				    (अचिन्हित दीर्घ)_n_, माप(*(ptr))); \
  पूर्ण)

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_local(अस्थिर व्योम *ptr,
				      अचिन्हित दीर्घ old,
				      अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 4:
	हाल 8:	वापस __cmpxchg(ptr, old, new, size);
	शेष:
		वापस __cmpxchg_local_generic(ptr, old, new, size);
	पूर्ण

	वापस old;
पूर्ण

#घोषणा cmpxchg_local(ptr, o, n)				  	\
	((__typeof__(*(ptr)))__cmpxchg_local((ptr), (अचिन्हित दीर्घ)(o),	\
			(अचिन्हित दीर्घ)(n), माप(*(ptr))))
#घोषणा cmpxchg64_local(ptr, o, n)					\
  (अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_local((ptr), (o), (n));					\
  पूर्ण)
#घोषणा cmpxchg64(ptr, o, n)	cmpxchg64_local((ptr), (o), (n))

#पूर्ण_अगर /* __ARCH_SPARC64_CMPXCHG__ */
