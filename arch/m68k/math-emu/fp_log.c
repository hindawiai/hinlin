<शैली गुरु>
/*

  fp_trig.c: भग्नing-poपूर्णांक math routines क्रम the Linux-m68k
  भग्नing poपूर्णांक emulator.

  Copyright (c) 1998-1999 David Huggins-Daines / Roman Zippel.

  I hereby give permission, मुक्त of अक्षरge, to copy, modअगरy, and
  redistribute this software, in source or binary क्रमm, provided that
  the above copyright notice and the following disclaimer are included
  in all such copies.

  THIS SOFTWARE IS PROVIDED "AS IS", WITH ABSOLUTELY NO WARRANTY, REAL
  OR IMPLIED.

*/

#समावेश "fp_emu.h"

अटल स्थिर काष्ठा fp_ext fp_one =
अणु
	.exp = 0x3fff,
पूर्ण;

बाह्य काष्ठा fp_ext *fp_fadd(काष्ठा fp_ext *dest, स्थिर काष्ठा fp_ext *src);
बाह्य काष्ठा fp_ext *fp_fभाग(काष्ठा fp_ext *dest, स्थिर काष्ठा fp_ext *src);

काष्ठा fp_ext *
fp_fवर्ग_मूल(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	काष्ठा fp_ext पंचांगp, src2;
	पूर्णांक i, exp;

	dprपूर्णांक(PINSTR, "fsqrt\n");

	fp_monadic_check(dest, src);

	अगर (IS_ZERO(dest))
		वापस dest;

	अगर (dest->sign) अणु
		fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_INF(dest))
		वापस dest;

	/*
	 *		 वर्ग_मूल(m) * 2^(p)	, अगर e = 2*p
	 * वर्ग_मूल(m*2^e) =
	 *		 वर्ग_मूल(2*m) * 2^(p)	, अगर e = 2*p + 1
	 *
	 * So we use the last bit of the exponent to decide whether to
	 * use the m or 2*m.
	 *
	 * Since only the fractional part of the mantissa is stored and
	 * the पूर्णांकeger part is assumed to be one, we place a 1 or 2 पूर्णांकo
	 * the fixed poपूर्णांक representation.
	 */
	exp = dest->exp;
	dest->exp = 0x3FFF;
	अगर (!(exp & 1))		/* lowest bit of exponent is set */
		dest->exp++;
	fp_copy_ext(&src2, dest);

	/*
	 * The taylor row around a क्रम वर्ग_मूल(x) is:
	 *	वर्ग_मूल(x) = वर्ग_मूल(a) + 1/(2*वर्ग_मूल(a))*(x-a) + R
	 * With a=1 this gives:
	 *	वर्ग_मूल(x) = 1 + 1/2*(x-1)
	 *		= 1/2*(1+x)
	 */
	fp_fadd(dest, &fp_one);
	dest->exp--;		/* * 1/2 */

	/*
	 * We now apply the newton rule to the function
	 *	f(x) := x^2 - r
	 * which has a null poपूर्णांक on x = वर्ग_मूल(r).
	 *
	 * It gives:
	 *	x' := x - f(x)/f'(x)
	 *	    = x - (x^2 -r)/(2*x)
	 *	    = x - (x - r/x)/2
	 *          = (2*x - x + r/x)/2
	 *	    = (x + r/x)/2
	 */
	क्रम (i = 0; i < 9; i++) अणु
		fp_copy_ext(&पंचांगp, &src2);

		fp_fभाग(&पंचांगp, dest);
		fp_fadd(dest, &पंचांगp);
		dest->exp--;
	पूर्ण

	dest->exp += (exp - 0x3FFF) / 2;

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fetoxm1(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("fetoxm1\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fetox(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("fetox\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_ftwotox(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("ftwotox\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_ftentox(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("ftentox\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_flogn(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("flogn\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_flognp1(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("flognp1\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_flog10(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("flog10\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_flog2(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	uprपूर्णांक("flog2\n");

	fp_monadic_check(dest, src);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fgetexp(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fgetexp\n");

	fp_monadic_check(dest, src);

	अगर (IS_INF(dest)) अणु
		fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_ZERO(dest))
		वापस dest;

	fp_conv_दीर्घ2ext(dest, (पूर्णांक)dest->exp - 0x3FFF);

	fp_normalize_ext(dest);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fgeपंचांगan(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fgetman\n");

	fp_monadic_check(dest, src);

	अगर (IS_ZERO(dest))
		वापस dest;

	अगर (IS_INF(dest))
		वापस dest;

	dest->exp = 0x3FFF;

	वापस dest;
पूर्ण

