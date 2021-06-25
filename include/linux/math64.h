<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MATH64_H
#घोषणा _LINUX_MATH64_H

#समावेश <linux/types.h>
#समावेश <vdso/math64.h>
#समावेश <यंत्र/भाग64.h>

#अगर BITS_PER_LONG == 64

#घोषणा भाग64_दीर्घ(x, y) भाग64_s64((x), (y))
#घोषणा भाग64_ul(x, y)   भाग64_u64((x), (y))

/**
 * भाग_u64_rem - अचिन्हित 64bit भागide with 32bit भागisor with reमुख्यder
 * @भागidend: अचिन्हित 64bit भागidend
 * @भागisor: अचिन्हित 32bit भागisor
 * @reमुख्यder: poपूर्णांकer to अचिन्हित 32bit reमुख्यder
 *
 * Return: sets ``*reमुख्यder``, then वापसs भागidend / भागisor
 *
 * This is commonly provided by 32bit archs to provide an optimized 64bit
 * भागide.
 */
अटल अंतरभूत u64 भाग_u64_rem(u64 भागidend, u32 भागisor, u32 *reमुख्यder)
अणु
	*reमुख्यder = भागidend % भागisor;
	वापस भागidend / भागisor;
पूर्ण

/*
 * भाग_s64_rem - चिन्हित 64bit भागide with 32bit भागisor with reमुख्यder
 * @भागidend: चिन्हित 64bit भागidend
 * @भागisor: चिन्हित 32bit भागisor
 * @reमुख्यder: poपूर्णांकer to चिन्हित 32bit reमुख्यder
 *
 * Return: sets ``*reमुख्यder``, then वापसs भागidend / भागisor
 */
अटल अंतरभूत s64 भाग_s64_rem(s64 भागidend, s32 भागisor, s32 *reमुख्यder)
अणु
	*reमुख्यder = भागidend % भागisor;
	वापस भागidend / भागisor;
पूर्ण

/*
 * भाग64_u64_rem - अचिन्हित 64bit भागide with 64bit भागisor and reमुख्यder
 * @भागidend: अचिन्हित 64bit भागidend
 * @भागisor: अचिन्हित 64bit भागisor
 * @reमुख्यder: poपूर्णांकer to अचिन्हित 64bit reमुख्यder
 *
 * Return: sets ``*reमुख्यder``, then वापसs भागidend / भागisor
 */
अटल अंतरभूत u64 भाग64_u64_rem(u64 भागidend, u64 भागisor, u64 *reमुख्यder)
अणु
	*reमुख्यder = भागidend % भागisor;
	वापस भागidend / भागisor;
पूर्ण

/*
 * भाग64_u64 - अचिन्हित 64bit भागide with 64bit भागisor
 * @भागidend: अचिन्हित 64bit भागidend
 * @भागisor: अचिन्हित 64bit भागisor
 *
 * Return: भागidend / भागisor
 */
अटल अंतरभूत u64 भाग64_u64(u64 भागidend, u64 भागisor)
अणु
	वापस भागidend / भागisor;
पूर्ण

/*
 * भाग64_s64 - चिन्हित 64bit भागide with 64bit भागisor
 * @भागidend: चिन्हित 64bit भागidend
 * @भागisor: चिन्हित 64bit भागisor
 *
 * Return: भागidend / भागisor
 */
अटल अंतरभूत s64 भाग64_s64(s64 भागidend, s64 भागisor)
अणु
	वापस भागidend / भागisor;
पूर्ण

#या_अगर BITS_PER_LONG == 32

#घोषणा भाग64_दीर्घ(x, y) भाग_s64((x), (y))
#घोषणा भाग64_ul(x, y)   भाग_u64((x), (y))

#अगर_अघोषित भाग_u64_rem
अटल अंतरभूत u64 भाग_u64_rem(u64 भागidend, u32 भागisor, u32 *reमुख्यder)
अणु
	*reमुख्यder = करो_भाग(भागidend, भागisor);
	वापस भागidend;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित भाग_s64_rem
बाह्य s64 भाग_s64_rem(s64 भागidend, s32 भागisor, s32 *reमुख्यder);
#पूर्ण_अगर

#अगर_अघोषित भाग64_u64_rem
बाह्य u64 भाग64_u64_rem(u64 भागidend, u64 भागisor, u64 *reमुख्यder);
#पूर्ण_अगर

#अगर_अघोषित भाग64_u64
बाह्य u64 भाग64_u64(u64 भागidend, u64 भागisor);
#पूर्ण_अगर

#अगर_अघोषित भाग64_s64
बाह्य s64 भाग64_s64(s64 भागidend, s64 भागisor);
#पूर्ण_अगर

#पूर्ण_अगर /* BITS_PER_LONG */

/**
 * भाग_u64 - अचिन्हित 64bit भागide with 32bit भागisor
 * @भागidend: अचिन्हित 64bit भागidend
 * @भागisor: अचिन्हित 32bit भागisor
 *
 * This is the most common 64bit भागide and should be used अगर possible,
 * as many 32bit archs can optimize this variant better than a full 64bit
 * भागide.
 */
#अगर_अघोषित भाग_u64
अटल अंतरभूत u64 भाग_u64(u64 भागidend, u32 भागisor)
अणु
	u32 reमुख्यder;
	वापस भाग_u64_rem(भागidend, भागisor, &reमुख्यder);
पूर्ण
#पूर्ण_अगर

/**
 * भाग_s64 - चिन्हित 64bit भागide with 32bit भागisor
 * @भागidend: चिन्हित 64bit भागidend
 * @भागisor: चिन्हित 32bit भागisor
 */
#अगर_अघोषित भाग_s64
अटल अंतरभूत s64 भाग_s64(s64 भागidend, s32 भागisor)
अणु
	s32 reमुख्यder;
	वापस भाग_s64_rem(भागidend, भागisor, &reमुख्यder);
पूर्ण
#पूर्ण_अगर

u32 iter_भाग_u64_rem(u64 भागidend, u32 भागisor, u64 *reमुख्यder);

#अगर_अघोषित mul_u32_u32
/*
 * Many a GCC version messes this up and generates a 64x64 mult :-(
 */
अटल अंतरभूत u64 mul_u32_u32(u32 a, u32 b)
अणु
	वापस (u64)a * b;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_SUPPORTS_INT128) && defined(__SIZखातापूर्ण_INT128__)

#अगर_अघोषित mul_u64_u32_shr
अटल अंतरभूत u64 mul_u64_u32_shr(u64 a, u32 mul, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (u64)(((अचिन्हित __पूर्णांक128)a * mul) >> shअगरt);
पूर्ण
#पूर्ण_अगर /* mul_u64_u32_shr */

#अगर_अघोषित mul_u64_u64_shr
अटल अंतरभूत u64 mul_u64_u64_shr(u64 a, u64 mul, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (u64)(((अचिन्हित __पूर्णांक128)a * mul) >> shअगरt);
पूर्ण
#पूर्ण_अगर /* mul_u64_u64_shr */

#अन्यथा

#अगर_अघोषित mul_u64_u32_shr
अटल अंतरभूत u64 mul_u64_u32_shr(u64 a, u32 mul, अचिन्हित पूर्णांक shअगरt)
अणु
	u32 ah, al;
	u64 ret;

	al = a;
	ah = a >> 32;

	ret = mul_u32_u32(al, mul) >> shअगरt;
	अगर (ah)
		ret += mul_u32_u32(ah, mul) << (32 - shअगरt);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* mul_u64_u32_shr */

#अगर_अघोषित mul_u64_u64_shr
अटल अंतरभूत u64 mul_u64_u64_shr(u64 a, u64 b, अचिन्हित पूर्णांक shअगरt)
अणु
	जोड़ अणु
		u64 ll;
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			u32 high, low;
#अन्यथा
			u32 low, high;
#पूर्ण_अगर
		पूर्ण l;
	पूर्ण rl, rm, rn, rh, a0, b0;
	u64 c;

	a0.ll = a;
	b0.ll = b;

	rl.ll = mul_u32_u32(a0.l.low, b0.l.low);
	rm.ll = mul_u32_u32(a0.l.low, b0.l.high);
	rn.ll = mul_u32_u32(a0.l.high, b0.l.low);
	rh.ll = mul_u32_u32(a0.l.high, b0.l.high);

	/*
	 * Each of these lines computes a 64-bit पूर्णांकermediate result पूर्णांकo "c",
	 * starting at bits 32-95.  The low 32-bits go पूर्णांकo the result of the
	 * multiplication, the high 32-bits are carried पूर्णांकo the next step.
	 */
	rl.l.high = c = (u64)rl.l.high + rm.l.low + rn.l.low;
	rh.l.low = c = (c >> 32) + rm.l.high + rn.l.high + rh.l.low;
	rh.l.high = (c >> 32) + rh.l.high;

	/*
	 * The 128-bit result of the multiplication is in rl.ll and rh.ll,
	 * shअगरt it right and throw away the high part of the result.
	 */
	अगर (shअगरt == 0)
		वापस rl.ll;
	अगर (shअगरt < 64)
		वापस (rl.ll >> shअगरt) | (rh.ll << (64 - shअगरt));
	वापस rh.ll >> (shअगरt & 63);
पूर्ण
#पूर्ण_अगर /* mul_u64_u64_shr */

#पूर्ण_अगर

#अगर_अघोषित mul_u64_u32_भाग
अटल अंतरभूत u64 mul_u64_u32_भाग(u64 a, u32 mul, u32 भागisor)
अणु
	जोड़ अणु
		u64 ll;
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			u32 high, low;
#अन्यथा
			u32 low, high;
#पूर्ण_अगर
		पूर्ण l;
	पूर्ण u, rl, rh;

	u.ll = a;
	rl.ll = mul_u32_u32(u.l.low, mul);
	rh.ll = mul_u32_u32(u.l.high, mul) + rl.l.high;

	/* Bits 32-63 of the result will be in rh.l.low. */
	rl.l.high = करो_भाग(rh.ll, भागisor);

	/* Bits 0-31 of the result will be in rl.l.low.	*/
	करो_भाग(rl.ll, भागisor);

	rl.l.high = rh.l.low;
	वापस rl.ll;
पूर्ण
#पूर्ण_अगर /* mul_u64_u32_भाग */

u64 mul_u64_u64_भाग_u64(u64 a, u64 mul, u64 भाग);

#घोषणा DIV64_U64_ROUND_UP(ll, d)	\
	(अणु u64 _पंचांगp = (d); भाग64_u64((ll) + _पंचांगp - 1, _पंचांगp); पूर्ण)

/**
 * DIV64_U64_ROUND_CLOSEST - अचिन्हित 64bit भागide with 64bit भागisor rounded to nearest पूर्णांकeger
 * @भागidend: अचिन्हित 64bit भागidend
 * @भागisor: अचिन्हित 64bit भागisor
 *
 * Divide अचिन्हित 64bit भागidend by अचिन्हित 64bit भागisor
 * and round to बंदst पूर्णांकeger.
 *
 * Return: भागidend / भागisor rounded to nearest पूर्णांकeger
 */
#घोषणा DIV64_U64_ROUND_CLOSEST(भागidend, भागisor)	\
	(अणु u64 _पंचांगp = (भागisor); भाग64_u64((भागidend) + _पंचांगp / 2, _पंचांगp); पूर्ण)

/*
 * DIV_S64_ROUND_CLOSEST - चिन्हित 64bit भागide with 32bit भागisor rounded to nearest पूर्णांकeger
 * @भागidend: चिन्हित 64bit भागidend
 * @भागisor: चिन्हित 32bit भागisor
 *
 * Divide चिन्हित 64bit भागidend by चिन्हित 32bit भागisor
 * and round to बंदst पूर्णांकeger.
 *
 * Return: भागidend / भागisor rounded to nearest पूर्णांकeger
 */
#घोषणा DIV_S64_ROUND_CLOSEST(भागidend, भागisor)(	\
अणु							\
	s64 __x = (भागidend);				\
	s32 __d = (भागisor);				\
	((__x > 0) == (__d > 0)) ?			\
		भाग_s64((__x + (__d / 2)), __d) :	\
		भाग_s64((__x - (__d / 2)), __d);	\
पूर्ण							\
)
#पूर्ण_अगर /* _LINUX_MATH64_H */
