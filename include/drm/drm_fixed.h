<शैली गुरु>
/*
 * Copyright 2009 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Christian Kथघnig
 */
#अगर_अघोषित DRM_FIXED_H
#घोषणा DRM_FIXED_H

#समावेश <linux/math64.h>

प्रकार जोड़ dfixed अणु
	u32 full;
पूर्ण fixed20_12;


#घोषणा dfixed_स्थिर(A) (u32)(((A) << 12))/*  + ((B + 0.000122)*4096)) */
#घोषणा dfixed_स्थिर_half(A) (u32)(((A) << 12) + 2048)
#घोषणा dfixed_स्थिर_666(A) (u32)(((A) << 12) + 2731)
#घोषणा dfixed_स्थिर_8(A) (u32)(((A) << 12) + 3277)
#घोषणा dfixed_mul(A, B) ((u64)((u64)(A).full * (B).full + 2048) >> 12)
#घोषणा dfixed_init(A) अणु .full = dfixed_स्थिर((A)) पूर्ण
#घोषणा dfixed_init_half(A) अणु .full = dfixed_स्थिर_half((A)) पूर्ण
#घोषणा dfixed_trunc(A) ((A).full >> 12)
#घोषणा dfixed_frac(A) ((A).full & ((1 << 12) - 1))

अटल अंतरभूत u32 dfixed_न्यूनमान(fixed20_12 A)
अणु
	u32 non_frac = dfixed_trunc(A);

	वापस dfixed_स्थिर(non_frac);
पूर्ण

अटल अंतरभूत u32 dfixed_उच्चमान(fixed20_12 A)
अणु
	u32 non_frac = dfixed_trunc(A);

	अगर (A.full > dfixed_स्थिर(non_frac))
		वापस dfixed_स्थिर(non_frac + 1);
	अन्यथा
		वापस dfixed_स्थिर(non_frac);
पूर्ण

अटल अंतरभूत u32 dfixed_भाग(fixed20_12 A, fixed20_12 B)
अणु
	u64 पंचांगp = ((u64)A.full << 13);

	करो_भाग(पंचांगp, B.full);
	पंचांगp += 1;
	पंचांगp /= 2;
	वापस lower_32_bits(पंचांगp);
पूर्ण

#घोषणा DRM_FIXED_POINT		32
#घोषणा DRM_FIXED_ONE		(1ULL << DRM_FIXED_POINT)
#घोषणा DRM_FIXED_DECIMAL_MASK	(DRM_FIXED_ONE - 1)
#घोषणा DRM_FIXED_DIGITS_MASK	(~DRM_FIXED_DECIMAL_MASK)
#घोषणा DRM_FIXED_EPSILON	1LL
#घोषणा DRM_FIXED_ALMOST_ONE	(DRM_FIXED_ONE - DRM_FIXED_EPSILON)

अटल अंतरभूत s64 drm_पूर्णांक2fixp(पूर्णांक a)
अणु
	वापस ((s64)a) << DRM_FIXED_POINT;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fixp2पूर्णांक(s64 a)
अणु
	वापस ((s64)a) >> DRM_FIXED_POINT;
पूर्ण

अटल अंतरभूत पूर्णांक drm_fixp2पूर्णांक_उच्चमान(s64 a)
अणु
	अगर (a > 0)
		वापस drm_fixp2पूर्णांक(a + DRM_FIXED_ALMOST_ONE);
	अन्यथा
		वापस drm_fixp2पूर्णांक(a - DRM_FIXED_ALMOST_ONE);
पूर्ण

अटल अंतरभूत अचिन्हित drm_fixp_msbset(s64 a)
अणु
	अचिन्हित shअगरt, sign = (a >> 63) & 1;

	क्रम (shअगरt = 62; shअगरt > 0; --shअगरt)
		अगर (((a >> shअगरt) & 1) != sign)
			वापस shअगरt;

	वापस 0;
पूर्ण

अटल अंतरभूत s64 drm_fixp_mul(s64 a, s64 b)
अणु
	अचिन्हित shअगरt = drm_fixp_msbset(a) + drm_fixp_msbset(b);
	s64 result;

	अगर (shअगरt > 61) अणु
		shअगरt = shअगरt - 61;
		a >>= (shअगरt >> 1) + (shअगरt & 1);
		b >>= shअगरt >> 1;
	पूर्ण अन्यथा
		shअगरt = 0;

	result = a * b;

	अगर (shअगरt > DRM_FIXED_POINT)
		वापस result << (shअगरt - DRM_FIXED_POINT);

	अगर (shअगरt < DRM_FIXED_POINT)
		वापस result >> (DRM_FIXED_POINT - shअगरt);

	वापस result;
पूर्ण

अटल अंतरभूत s64 drm_fixp_भाग(s64 a, s64 b)
अणु
	अचिन्हित shअगरt = 62 - drm_fixp_msbset(a);
	s64 result;

	a <<= shअगरt;

	अगर (shअगरt < DRM_FIXED_POINT)
		b >>= (DRM_FIXED_POINT - shअगरt);

	result = भाग64_s64(a, b);

	अगर (shअगरt > DRM_FIXED_POINT)
		वापस result >> (shअगरt - DRM_FIXED_POINT);

	वापस result;
पूर्ण

अटल अंतरभूत s64 drm_fixp_from_fraction(s64 a, s64 b)
अणु
	s64 res;
	bool a_neg = a < 0;
	bool b_neg = b < 0;
	u64 a_असल = a_neg ? -a : a;
	u64 b_असल = b_neg ? -b : b;
	u64 rem;

	/* determine पूर्णांकeger part */
	u64 res_असल  = भाग64_u64_rem(a_असल, b_असल, &rem);

	/* determine fractional part */
	अणु
		u32 i = DRM_FIXED_POINT;

		करो अणु
			rem <<= 1;
			res_असल <<= 1;
			अगर (rem >= b_असल) अणु
				res_असल |= 1;
				rem -= b_असल;
			पूर्ण
		पूर्ण जबतक (--i != 0);
	पूर्ण

	/* round up LSB */
	अणु
		u64 summand = (rem << 1) >= b_असल;

		res_असल += summand;
	पूर्ण

	res = (s64) res_असल;
	अगर (a_neg ^ b_neg)
		res = -res;
	वापस res;
पूर्ण

अटल अंतरभूत s64 drm_fixp_exp(s64 x)
अणु
	s64 tolerance = भाग64_s64(DRM_FIXED_ONE, 1000000);
	s64 sum = DRM_FIXED_ONE, term, y = x;
	u64 count = 1;

	अगर (x < 0)
		y = -1 * x;

	term = y;

	जबतक (term >= tolerance) अणु
		sum = sum + term;
		count = count + 1;
		term = drm_fixp_mul(term, भाग64_s64(y, count));
	पूर्ण

	अगर (x < 0)
		sum = drm_fixp_भाग(DRM_FIXED_ONE, sum);

	वापस sum;
पूर्ण

#पूर्ण_अगर
