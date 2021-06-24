<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

   fp_arith.c: भग्नing-poपूर्णांक math routines क्रम the Linux-m68k
   भग्नing poपूर्णांक emulator.

   Copyright (c) 1998-1999 David Huggins-Daines.

   Somewhat based on the AlphaLinux भग्नing poपूर्णांक emulator, by David
   Mosberger-Tang.

 */

#समावेश "fp_emu.h"
#समावेश "multi_arith.h"
#समावेश "fp_arith.h"

स्थिर काष्ठा fp_ext fp_QNaN =
अणु
	.exp = 0x7fff,
	.mant = अणु .m64 = ~0 पूर्ण
पूर्ण;

स्थिर काष्ठा fp_ext fp_Inf =
अणु
	.exp = 0x7fff,
पूर्ण;

/* let's start with the easy ones */

काष्ठा fp_ext *
fp_भ_असल(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fabs\n");

	fp_monadic_check(dest, src);

	dest->sign = 0;

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fneg(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fneg\n");

	fp_monadic_check(dest, src);

	dest->sign = !dest->sign;

	वापस dest;
पूर्ण

/* Now, the slightly harder ones */

/* fp_fadd: Implements the kernel of the FADD, FSADD, FDADD, FSUB,
   FDSUB, and FCMP inकाष्ठाions. */

काष्ठा fp_ext *
fp_fadd(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	पूर्णांक dअगरf;

	dprपूर्णांक(PINSTR, "fadd\n");

	fp_dyadic_check(dest, src);

	अगर (IS_INF(dest)) अणु
		/* infinity - infinity == NaN */
		अगर (IS_INF(src) && (src->sign != dest->sign))
			fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_INF(src)) अणु
		fp_copy_ext(dest, src);
		वापस dest;
	पूर्ण

	अगर (IS_ZERO(dest)) अणु
		अगर (IS_ZERO(src)) अणु
			अगर (src->sign != dest->sign) अणु
				अगर (FPDATA->rnd == FPCR_ROUND_RM)
					dest->sign = 1;
				अन्यथा
					dest->sign = 0;
			पूर्ण
		पूर्ण अन्यथा
			fp_copy_ext(dest, src);
		वापस dest;
	पूर्ण

	dest->lowmant = src->lowmant = 0;

	अगर ((dअगरf = dest->exp - src->exp) > 0)
		fp_denormalize(src, dअगरf);
	अन्यथा अगर ((dअगरf = -dअगरf) > 0)
		fp_denormalize(dest, dअगरf);

	अगर (dest->sign == src->sign) अणु
		अगर (fp_addmant(dest, src))
			अगर (!fp_addcarry(dest))
				वापस dest;
	पूर्ण अन्यथा अणु
		अगर (dest->mant.m64 < src->mant.m64) अणु
			fp_submant(dest, src, dest);
			dest->sign = !dest->sign;
		पूर्ण अन्यथा
			fp_submant(dest, dest, src);
	पूर्ण

	वापस dest;
पूर्ण

/* fp_fsub: Implements the kernel of the FSUB, FSSUB, and FDSUB
   inकाष्ठाions.

   Remember that the arguments are in assembler-syntax order! */

काष्ठा fp_ext *
fp_fsub(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fsub ");

	src->sign = !src->sign;
	वापस fp_fadd(dest, src);
पूर्ण


काष्ठा fp_ext *
fp_fcmp(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fcmp ");

	FPDATA->temp[1] = *dest;
	src->sign = !src->sign;
	वापस fp_fadd(&FPDATA->temp[1], src);
पूर्ण

काष्ठा fp_ext *
fp_ftst(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "ftst\n");

	(व्योम)dest;

	वापस src;
पूर्ण

काष्ठा fp_ext *
fp_fmul(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	जोड़ fp_mant128 temp;
	पूर्णांक exp;

	dprपूर्णांक(PINSTR, "fmul\n");

	fp_dyadic_check(dest, src);

	/* calculate the correct sign now, as it's necessary क्रम infinities */
	dest->sign = src->sign ^ dest->sign;

	/* Handle infinities */
	अगर (IS_INF(dest)) अणु
		अगर (IS_ZERO(src))
			fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_INF(src)) अणु
		अगर (IS_ZERO(dest))
			fp_set_nan(dest);
		अन्यथा
			fp_copy_ext(dest, src);
		वापस dest;
	पूर्ण

	/* Of course, as we all know, zero * anything = zero.  You may
	   not have known that it might be a positive or negative
	   zero... */
	अगर (IS_ZERO(dest) || IS_ZERO(src)) अणु
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->lowmant = 0;

		वापस dest;
	पूर्ण

	exp = dest->exp + src->exp - 0x3ffe;

	/* shअगरt up the mantissa क्रम denormalized numbers,
	   so that the highest bit is set, this makes the
	   shअगरt of the result below easier */
	अगर ((दीर्घ)dest->mant.m32[0] >= 0)
		exp -= fp_overnormalize(dest);
	अगर ((दीर्घ)src->mant.m32[0] >= 0)
		exp -= fp_overnormalize(src);

	/* now, करो a 64-bit multiply with expansion */
	fp_multiplymant(&temp, dest, src);

	/* normalize it back to 64 bits and stuff it back पूर्णांकo the
	   destination काष्ठा */
	अगर ((दीर्घ)temp.m32[0] > 0) अणु
		exp--;
		fp_puपंचांगant128(dest, &temp, 1);
	पूर्ण अन्यथा
		fp_puपंचांगant128(dest, &temp, 0);

	अगर (exp >= 0x7fff) अणु
		fp_set_ovrflw(dest);
		वापस dest;
	पूर्ण
	dest->exp = exp;
	अगर (exp < 0) अणु
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -exp);
	पूर्ण

	वापस dest;
पूर्ण

/* fp_fभाग: Implements the "kernel" of the FDIV, FSDIV, FDDIV and
   FSGLDIV inकाष्ठाions.

   Note that the order of the opeअक्रमs is counter-पूर्णांकuitive: instead
   of src / dest, the result is actually dest / src. */

काष्ठा fp_ext *
fp_fभाग(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	जोड़ fp_mant128 temp;
	पूर्णांक exp;

	dprपूर्णांक(PINSTR, "fdiv\n");

	fp_dyadic_check(dest, src);

	/* calculate the correct sign now, as it's necessary क्रम infinities */
	dest->sign = src->sign ^ dest->sign;

	/* Handle infinities */
	अगर (IS_INF(dest)) अणु
		/* infinity / infinity = NaN (quiet, as always) */
		अगर (IS_INF(src))
			fp_set_nan(dest);
		/* infinity / anything अन्यथा = infinity (with approprate sign) */
		वापस dest;
	पूर्ण
	अगर (IS_INF(src)) अणु
		/* anything / infinity = zero (with appropriate sign) */
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->lowmant = 0;

		वापस dest;
	पूर्ण

	/* zeroes */
	अगर (IS_ZERO(dest)) अणु
		/* zero / zero = NaN */
		अगर (IS_ZERO(src))
			fp_set_nan(dest);
		/* zero / anything अन्यथा = zero */
		वापस dest;
	पूर्ण
	अगर (IS_ZERO(src)) अणु
		/* anything / zero = infinity (with appropriate sign) */
		fp_set_sr(FPSR_EXC_DZ);
		dest->exp = 0x7fff;
		dest->mant.m64 = 0;

		वापस dest;
	पूर्ण

	exp = dest->exp - src->exp + 0x3fff;

	/* shअगरt up the mantissa क्रम denormalized numbers,
	   so that the highest bit is set, this makes lots
	   of things below easier */
	अगर ((दीर्घ)dest->mant.m32[0] >= 0)
		exp -= fp_overnormalize(dest);
	अगर ((दीर्घ)src->mant.m32[0] >= 0)
		exp -= fp_overnormalize(src);

	/* now, करो the 64-bit भागide */
	fp_भागidemant(&temp, dest, src);

	/* normalize it back to 64 bits and stuff it back पूर्णांकo the
	   destination काष्ठा */
	अगर (!temp.m32[0]) अणु
		exp--;
		fp_puपंचांगant128(dest, &temp, 32);
	पूर्ण अन्यथा
		fp_puपंचांगant128(dest, &temp, 31);

	अगर (exp >= 0x7fff) अणु
		fp_set_ovrflw(dest);
		वापस dest;
	पूर्ण
	dest->exp = exp;
	अगर (exp < 0) अणु
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -exp);
	पूर्ण

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fsglmul(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	पूर्णांक exp;

	dprपूर्णांक(PINSTR, "fsglmul\n");

	fp_dyadic_check(dest, src);

	/* calculate the correct sign now, as it's necessary क्रम infinities */
	dest->sign = src->sign ^ dest->sign;

	/* Handle infinities */
	अगर (IS_INF(dest)) अणु
		अगर (IS_ZERO(src))
			fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_INF(src)) अणु
		अगर (IS_ZERO(dest))
			fp_set_nan(dest);
		अन्यथा
			fp_copy_ext(dest, src);
		वापस dest;
	पूर्ण

	/* Of course, as we all know, zero * anything = zero.  You may
	   not have known that it might be a positive or negative
	   zero... */
	अगर (IS_ZERO(dest) || IS_ZERO(src)) अणु
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->lowmant = 0;

		वापस dest;
	पूर्ण

	exp = dest->exp + src->exp - 0x3ffe;

	/* करो a 32-bit multiply */
	fp_mul64(dest->mant.m32[0], dest->mant.m32[1],
		 dest->mant.m32[0] & 0xffffff00,
		 src->mant.m32[0] & 0xffffff00);

	अगर (exp >= 0x7fff) अणु
		fp_set_ovrflw(dest);
		वापस dest;
	पूर्ण
	dest->exp = exp;
	अगर (exp < 0) अणु
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -exp);
	पूर्ण

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fsgद_भाग(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	पूर्णांक exp;
	अचिन्हित दीर्घ quot, rem;

	dprपूर्णांक(PINSTR, "fsgldiv\n");

	fp_dyadic_check(dest, src);

	/* calculate the correct sign now, as it's necessary क्रम infinities */
	dest->sign = src->sign ^ dest->sign;

	/* Handle infinities */
	अगर (IS_INF(dest)) अणु
		/* infinity / infinity = NaN (quiet, as always) */
		अगर (IS_INF(src))
			fp_set_nan(dest);
		/* infinity / anything अन्यथा = infinity (with approprate sign) */
		वापस dest;
	पूर्ण
	अगर (IS_INF(src)) अणु
		/* anything / infinity = zero (with appropriate sign) */
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->lowmant = 0;

		वापस dest;
	पूर्ण

	/* zeroes */
	अगर (IS_ZERO(dest)) अणु
		/* zero / zero = NaN */
		अगर (IS_ZERO(src))
			fp_set_nan(dest);
		/* zero / anything अन्यथा = zero */
		वापस dest;
	पूर्ण
	अगर (IS_ZERO(src)) अणु
		/* anything / zero = infinity (with appropriate sign) */
		fp_set_sr(FPSR_EXC_DZ);
		dest->exp = 0x7fff;
		dest->mant.m64 = 0;

		वापस dest;
	पूर्ण

	exp = dest->exp - src->exp + 0x3fff;

	dest->mant.m32[0] &= 0xffffff00;
	src->mant.m32[0] &= 0xffffff00;

	/* करो the 32-bit भागide */
	अगर (dest->mant.m32[0] >= src->mant.m32[0]) अणु
		fp_sub64(dest->mant, src->mant);
		fp_भाग64(quot, rem, dest->mant.m32[0], 0, src->mant.m32[0]);
		dest->mant.m32[0] = 0x80000000 | (quot >> 1);
		dest->mant.m32[1] = (quot & 1) | rem;	/* only क्रम rounding */
	पूर्ण अन्यथा अणु
		fp_भाग64(quot, rem, dest->mant.m32[0], 0, src->mant.m32[0]);
		dest->mant.m32[0] = quot;
		dest->mant.m32[1] = rem;		/* only क्रम rounding */
		exp--;
	पूर्ण

	अगर (exp >= 0x7fff) अणु
		fp_set_ovrflw(dest);
		वापस dest;
	पूर्ण
	dest->exp = exp;
	अगर (exp < 0) अणु
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -exp);
	पूर्ण

	वापस dest;
पूर्ण

/* fp_roundपूर्णांक: Internal rounding function क्रम use by several of these
   emulated inकाष्ठाions.

   This one rounds off the fractional part using the rounding mode
   specअगरied. */

अटल व्योम fp_roundपूर्णांक(काष्ठा fp_ext *dest, पूर्णांक mode)
अणु
	जोड़ fp_mant64 oldmant;
	अचिन्हित दीर्घ mask;

	अगर (!fp_normalize_ext(dest))
		वापस;

	/* infinities and zeroes */
	अगर (IS_INF(dest) || IS_ZERO(dest))
		वापस;

	/* first truncate the lower bits */
	oldmant = dest->mant;
	चयन (dest->exp) अणु
	हाल 0 ... 0x3ffe:
		dest->mant.m64 = 0;
		अवरोध;
	हाल 0x3fff ... 0x401e:
		dest->mant.m32[0] &= 0xffffffffU << (0x401e - dest->exp);
		dest->mant.m32[1] = 0;
		अगर (oldmant.m64 == dest->mant.m64)
			वापस;
		अवरोध;
	हाल 0x401f ... 0x403e:
		dest->mant.m32[1] &= 0xffffffffU << (0x403e - dest->exp);
		अगर (oldmant.m32[1] == dest->mant.m32[1])
			वापस;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	fp_set_sr(FPSR_EXC_INEX2);

	/* We might want to normalize upwards here... however, since
	   we know that this is only called on the output of fp_fभाग,
	   or with the input to fp_fपूर्णांक or fp_fपूर्णांकrz, and the inमाला_दो
	   to all these functions are either normal or denormalized
	   (no subnormals allowed!), there's really no need.

	   In the हाल of fp_fभाग, observe that 0x80000000 / 0xffff =
	   0xffff8000, and the same holds क्रम 128-bit / 64-bit. (i.e. the
	   smallest possible normal भागidend and the largest possible normal
	   भागisor will still produce a normal quotient, thereक्रमe, (normal
	   << 64) / normal is normal in all हालs) */

	चयन (mode) अणु
	हाल FPCR_ROUND_RN:
		चयन (dest->exp) अणु
		हाल 0 ... 0x3ffd:
			वापस;
		हाल 0x3ffe:
			/* As noted above, the input is always normal, so the
			   guard bit (bit 63) is always set.  thereक्रमe, the
			   only हाल in which we will NOT round to 1.0 is when
			   the input is exactly 0.5. */
			अगर (oldmant.m64 == (1ULL << 63))
				वापस;
			अवरोध;
		हाल 0x3fff ... 0x401d:
			mask = 1 << (0x401d - dest->exp);
			अगर (!(oldmant.m32[0] & mask))
				वापस;
			अगर (oldmant.m32[0] & (mask << 1))
				अवरोध;
			अगर (!(oldmant.m32[0] << (dest->exp - 0x3ffd)) &&
					!oldmant.m32[1])
				वापस;
			अवरोध;
		हाल 0x401e:
			अगर (oldmant.m32[1] & 0x80000000)
				वापस;
			अगर (oldmant.m32[0] & 1)
				अवरोध;
			अगर (!(oldmant.m32[1] << 1))
				वापस;
			अवरोध;
		हाल 0x401f ... 0x403d:
			mask = 1 << (0x403d - dest->exp);
			अगर (!(oldmant.m32[1] & mask))
				वापस;
			अगर (oldmant.m32[1] & (mask << 1))
				अवरोध;
			अगर (!(oldmant.m32[1] << (dest->exp - 0x401d)))
				वापस;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल FPCR_ROUND_RZ:
		वापस;
	शेष:
		अगर (dest->sign ^ (mode - FPCR_ROUND_RM))
			अवरोध;
		वापस;
	पूर्ण

	चयन (dest->exp) अणु
	हाल 0 ... 0x3ffe:
		dest->exp = 0x3fff;
		dest->mant.m64 = 1ULL << 63;
		अवरोध;
	हाल 0x3fff ... 0x401e:
		mask = 1 << (0x401e - dest->exp);
		अगर (dest->mant.m32[0] += mask)
			अवरोध;
		dest->mant.m32[0] = 0x80000000;
		dest->exp++;
		अवरोध;
	हाल 0x401f ... 0x403e:
		mask = 1 << (0x403e - dest->exp);
		अगर (dest->mant.m32[1] += mask)
			अवरोध;
		अगर (dest->mant.m32[0] += 1)
                        अवरोध;
		dest->mant.m32[0] = 0x80000000;
                dest->exp++;
		अवरोध;
	पूर्ण
पूर्ण

/* modrem_kernel: Implementation of the FREM and FMOD inकाष्ठाions
   (which are exactly the same, except क्रम the rounding used on the
   पूर्णांकermediate value) */

अटल काष्ठा fp_ext *
modrem_kernel(काष्ठा fp_ext *dest, काष्ठा fp_ext *src, पूर्णांक mode)
अणु
	काष्ठा fp_ext पंचांगp;

	fp_dyadic_check(dest, src);

	/* Infinities and zeros */
	अगर (IS_INF(dest) || IS_ZERO(src)) अणु
		fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_ZERO(dest) || IS_INF(src))
		वापस dest;

	/* FIXME: there is almost certainly a smarter way to करो this */
	fp_copy_ext(&पंचांगp, dest);
	fp_fभाग(&पंचांगp, src);		/* NOTE: src might be modअगरied */
	fp_roundपूर्णांक(&पंचांगp, mode);
	fp_fmul(&पंचांगp, src);
	fp_fsub(dest, &पंचांगp);

	/* set the quotient byte */
	fp_set_quotient((dest->mant.m64 & 0x7f) | (dest->sign << 7));
	वापस dest;
पूर्ण

/* fp_भ_शेष: Implements the kernel of the FMOD inकाष्ठाion.

   Again, the argument order is backwards.  The result, as defined in
   the Motorola manuals, is:

   भ_शेष(src,dest) = (dest - (src * न्यूनमान(dest / src))) */

काष्ठा fp_ext *
fp_भ_शेष(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fmod\n");
	वापस modrem_kernel(dest, src, FPCR_ROUND_RZ);
पूर्ण

/* fp_frem: Implements the kernel of the FREM inकाष्ठाion.

   frem(src,dest) = (dest - (src * round(dest / src)))
 */

काष्ठा fp_ext *
fp_frem(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "frem\n");
	वापस modrem_kernel(dest, src, FPCR_ROUND_RN);
पूर्ण

काष्ठा fp_ext *
fp_fपूर्णांक(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fint\n");

	fp_copy_ext(dest, src);

	fp_roundपूर्णांक(dest, FPDATA->rnd);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fपूर्णांकrz(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	dprपूर्णांक(PINSTR, "fintrz\n");

	fp_copy_ext(dest, src);

	fp_roundपूर्णांक(dest, FPCR_ROUND_RZ);

	वापस dest;
पूर्ण

काष्ठा fp_ext *
fp_fscale(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	पूर्णांक scale, oldround;

	dprपूर्णांक(PINSTR, "fscale\n");

	fp_dyadic_check(dest, src);

	/* Infinities */
	अगर (IS_INF(src)) अणु
		fp_set_nan(dest);
		वापस dest;
	पूर्ण
	अगर (IS_INF(dest))
		वापस dest;

	/* zeroes */
	अगर (IS_ZERO(src) || IS_ZERO(dest))
		वापस dest;

	/* Source exponent out of range */
	अगर (src->exp >= 0x400c) अणु
		fp_set_ovrflw(dest);
		वापस dest;
	पूर्ण

	/* src must be rounded with round to zero. */
	oldround = FPDATA->rnd;
	FPDATA->rnd = FPCR_ROUND_RZ;
	scale = fp_conv_ext2दीर्घ(src);
	FPDATA->rnd = oldround;

	/* new exponent */
	scale += dest->exp;

	अगर (scale >= 0x7fff) अणु
		fp_set_ovrflw(dest);
	पूर्ण अन्यथा अगर (scale <= 0) अणु
		fp_set_sr(FPSR_EXC_UNFL);
		fp_denormalize(dest, -scale);
	पूर्ण अन्यथा
		dest->exp = scale;

	वापस dest;
पूर्ण

