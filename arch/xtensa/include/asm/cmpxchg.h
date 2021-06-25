<शैली गुरु>
/*
 * Atomic xchg and cmpxchg operations.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CMPXCHG_H
#घोषणा _XTENSA_CMPXCHG_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bits.h>
#समावेश <linux/stringअगरy.h>

/*
 * cmpxchg
 */

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32(अस्थिर पूर्णांक *p, पूर्णांक old, पूर्णांक new)
अणु
#अगर XCHAL_HAVE_EXCLUSIVE
	अचिन्हित दीर्घ पंचांगp, result;

	__यंत्र__ __अस्थिर__(
			"1:     l32ex   %[result], %[addr]\n"
			"       bne     %[result], %[cmp], 2f\n"
			"       mov     %[tmp], %[new]\n"
			"       s32ex   %[tmp], %[addr]\n"
			"       getex   %[tmp]\n"
			"       beqz    %[tmp], 1b\n"
			"2:\n"
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp)
			: [new] "a" (new), [addr] "a" (p), [cmp] "a" (old)
			: "memory"
			);

	वापस result;
#या_अगर XCHAL_HAVE_S32C1I
	__यंत्र__ __अस्थिर__(
			"       wsr     %[cmp], scompare1\n"
			"       s32c1i  %[new], %[mem]\n"
			: [new] "+a" (new), [mem] "+m" (*p)
			: [cmp] "a" (old)
			: "memory"
			);

	वापस new;
#अन्यथा
	__यंत्र__ __अस्थिर__(
			"       rsil    a15, "__stringअगरy(TOPLEVEL)"\n"
			"       l32i    %[old], %[mem]\n"
			"       bne     %[old], %[cmp], 1f\n"
			"       s32i    %[new], %[mem]\n"
			"1:\n"
			"       wsr     a15, ps\n"
			"       rsync\n"
			: [old] "=&a" (old), [mem] "+m" (*p)
			: [cmp] "a" (old), [new] "r" (new)
			: "a15", "memory");
	वापस old;
#पूर्ण_अगर
पूर्ण
/* This function करोesn't exist, so you'll get a linker error
 * अगर something tries to करो an invalid cmpxchg(). */

बाह्य व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

अटल __अंतरभूत__ अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 4:  वापस __cmpxchg_u32(ptr, old, new);
	शेष: __cmpxchg_called_with_bad_poपूर्णांकer();
		 वापस old;
	पूर्ण
पूर्ण

#घोषणा cmpxchg(ptr,o,n)						      \
	(अणु __typeof__(*(ptr)) _o_ = (o);				      \
	   __typeof__(*(ptr)) _n_ = (n);				      \
	   (__typeof__(*(ptr))) __cmpxchg((ptr), (अचिन्हित दीर्घ)_o_,	      \
	   			        (अचिन्हित दीर्घ)_n_, माप (*(ptr))); \
	पूर्ण)

#समावेश <यंत्र-generic/cmpxchg-local.h>

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_local(अस्थिर व्योम *ptr,
				      अचिन्हित दीर्घ old,
				      अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 4:
		वापस __cmpxchg_u32(ptr, old, new);
	शेष:
		वापस __cmpxchg_local_generic(ptr, old, new, size);
	पूर्ण

	वापस old;
पूर्ण

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#घोषणा cmpxchg_local(ptr, o, n)				  	       \
	((__typeof__(*(ptr)))__cmpxchg_local_generic((ptr), (अचिन्हित दीर्घ)(o),\
			(अचिन्हित दीर्घ)(n), माप(*(ptr))))
#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))
#घोषणा cmpxchg64(ptr, o, n)    cmpxchg64_local((ptr), (o), (n))

/*
 * xchg_u32
 *
 * Note that a15 is used here because the रेजिस्टर allocation
 * करोne by the compiler is not guaranteed and a winकरोw overflow
 * may not occur between the rsil and wsr inकाष्ठाions. By using
 * a15 in the rsil, the machine is guaranteed to be in a state
 * where no रेजिस्टर reference will cause an overflow.
 */

अटल अंतरभूत अचिन्हित दीर्घ xchg_u32(अस्थिर पूर्णांक * m, अचिन्हित दीर्घ val)
अणु
#अगर XCHAL_HAVE_EXCLUSIVE
	अचिन्हित दीर्घ पंचांगp, result;

	__यंत्र__ __अस्थिर__(
			"1:     l32ex   %[result], %[addr]\n"
			"       mov     %[tmp], %[val]\n"
			"       s32ex   %[tmp], %[addr]\n"
			"       getex   %[tmp]\n"
			"       beqz    %[tmp], 1b\n"
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp)
			: [val] "a" (val), [addr] "a" (m)
			: "memory"
			);

	वापस result;
#या_अगर XCHAL_HAVE_S32C1I
	अचिन्हित दीर्घ पंचांगp, result;
	__यंत्र__ __अस्थिर__(
			"1:     l32i    %[tmp], %[mem]\n"
			"       mov     %[result], %[val]\n"
			"       wsr     %[tmp], scompare1\n"
			"       s32c1i  %[result], %[mem]\n"
			"       bne     %[result], %[tmp], 1b\n"
			: [result] "=&a" (result), [पंचांगp] "=&a" (पंचांगp),
			  [mem] "+m" (*m)
			: [val] "a" (val)
			: "memory"
			);
	वापस result;
#अन्यथा
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__(
			"       rsil    a15, "__stringअगरy(TOPLEVEL)"\n"
			"       l32i    %[tmp], %[mem]\n"
			"       s32i    %[val], %[mem]\n"
			"       wsr     a15, ps\n"
			"       rsync\n"
			: [पंचांगp] "=&a" (पंचांगp), [mem] "+m" (*m)
			: [val] "a" (val)
			: "a15", "memory");
	वापस पंचांगp;
#पूर्ण_अगर
पूर्ण

#घोषणा xchg(ptr,x) \
	((__typeof__(*(ptr)))__xchg((अचिन्हित दीर्घ)(x),(ptr),माप(*(ptr))))

अटल अंतरभूत u32 xchg_small(अस्थिर व्योम *ptr, u32 x, पूर्णांक size)
अणु
	पूर्णांक off = (अचिन्हित दीर्घ)ptr % माप(u32);
	अस्थिर u32 *p = ptr - off;
#अगर_घोषित __BIG_ENDIAN
	पूर्णांक bitoff = (माप(u32) - size - off) * BITS_PER_BYTE;
#अन्यथा
	पूर्णांक bitoff = off * BITS_PER_BYTE;
#पूर्ण_अगर
	u32 biपंचांगask = ((0x1 << size * BITS_PER_BYTE) - 1) << bitoff;
	u32 oldv, newv;
	u32 ret;

	करो अणु
		oldv = READ_ONCE(*p);
		ret = (oldv & biपंचांगask) >> bitoff;
		newv = (oldv & ~biपंचांगask) | (x << bitoff);
	पूर्ण जबतक (__cmpxchg_u32(p, oldv, newv) != oldv);

	वापस ret;
पूर्ण

/*
 * This only works अगर the compiler isn't horribly bad at optimizing.
 * gcc-2.5.8 reportedly can't handle this, but I define that one to
 * be dead anyway.
 */

बाह्य व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

अटल __अंतरभूत__ अचिन्हित दीर्घ
__xchg(अचिन्हित दीर्घ x, अस्थिर व्योम * ptr, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस xchg_small(ptr, x, 1);
	हाल 2:
		वापस xchg_small(ptr, x, 2);
	हाल 4:
		वापस xchg_u32(ptr, x);
	शेष:
		__xchg_called_with_bad_poपूर्णांकer();
		वापस x;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _XTENSA_CMPXCHG_H */
