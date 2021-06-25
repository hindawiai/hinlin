<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  fpu_trig.c                                                               |
 |                                                                           |
 | Implementation of the FPU "transcendental" functions.                     |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997,1999                                    |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@melbpc.org.au            |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "fpu_emu.h"
#समावेश "status_w.h"
#समावेश "control_w.h"
#समावेश "reg_constant.h"

अटल व्योम rem_kernel(अचिन्हित दीर्घ दीर्घ st0, अचिन्हित दीर्घ दीर्घ *y,
		       अचिन्हित दीर्घ दीर्घ st1, अचिन्हित दीर्घ दीर्घ q, पूर्णांक n);

#घोषणा BETTER_THAN_486

#घोषणा FCOS  4

/* Used only by fptan, fsin, fcos, and fsincos. */
/* This routine produces very accurate results, similar to
   using a value of pi with more than 128 bits precision. */
/* Limited measurements show no results worse than 64 bit precision
   except क्रम the results क्रम arguments बंद to 2^63, where the
   precision of the result someबार degrades to about 63.9 bits */
अटल पूर्णांक trig_arg(FPU_REG *st0_ptr, पूर्णांक even)
अणु
	FPU_REG पंचांगp;
	u_अक्षर पंचांगptag;
	अचिन्हित दीर्घ दीर्घ q;
	पूर्णांक old_cw = control_word, saved_status = partial_status;
	पूर्णांक tag, st0_tag = TAG_Valid;

	अगर (exponent(st0_ptr) >= 63) अणु
		partial_status |= SW_C2;	/* Reduction incomplete. */
		वापस -1;
	पूर्ण

	control_word &= ~CW_RC;
	control_word |= RC_CHOP;

	setpositive(st0_ptr);
	tag = FPU_u_भाग(st0_ptr, &CONST_PI2, &पंचांगp, PR_64_BITS | RC_CHOP | 0x3f,
			SIGN_POS);

	FPU_round_to_पूर्णांक(&पंचांगp, tag);	/* Fortunately, this can't overflow
					   to 2^64 */
	q = signअगरicand(&पंचांगp);
	अगर (q) अणु
		rem_kernel(signअगरicand(st0_ptr),
			   &signअगरicand(&पंचांगp),
			   signअगरicand(&CONST_PI2),
			   q, exponent(st0_ptr) - exponent(&CONST_PI2));
		setexponent16(&पंचांगp, exponent(&CONST_PI2));
		st0_tag = FPU_normalize(&पंचांगp);
		FPU_copy_to_reg0(&पंचांगp, st0_tag);
	पूर्ण

	अगर ((even && !(q & 1)) || (!even && (q & 1))) अणु
		st0_tag =
		    FPU_sub(REV | LOADED | TAG_Valid, (पूर्णांक)&CONST_PI2,
			    FULL_PRECISION);

#अगर_घोषित BETTER_THAN_486
		/* So far, the results are exact but based upon a 64 bit
		   precision approximation to pi/2. The technique used
		   now is equivalent to using an approximation to pi/2 which
		   is accurate to about 128 bits. */
		अगर ((exponent(st0_ptr) <= exponent(&CONST_PI2extra) + 64)
		    || (q > 1)) अणु
			/* This code gives the effect of having pi/2 to better than
			   128 bits precision. */

			signअगरicand(&पंचांगp) = q + 1;
			setexponent16(&पंचांगp, 63);
			FPU_normalize(&पंचांगp);
			पंचांगptag =
			    FPU_u_mul(&CONST_PI2extra, &पंचांगp, &पंचांगp,
				      FULL_PRECISION, SIGN_POS,
				      exponent(&CONST_PI2extra) +
				      exponent(&पंचांगp));
			setsign(&पंचांगp, माला_लोign(&CONST_PI2extra));
			st0_tag = FPU_add(&पंचांगp, पंचांगptag, 0, FULL_PRECISION);
			अगर (signnegative(st0_ptr)) अणु
				/* CONST_PI2extra is negative, so the result of the addition
				   can be negative. This means that the argument is actually
				   in a dअगरferent quadrant. The correction is always < pi/2,
				   so it can't overflow पूर्णांकo yet another quadrant. */
				setpositive(st0_ptr);
				q++;
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* BETTER_THAN_486 */
	पूर्ण
#अगर_घोषित BETTER_THAN_486
	अन्यथा अणु
		/* So far, the results are exact but based upon a 64 bit
		   precision approximation to pi/2. The technique used
		   now is equivalent to using an approximation to pi/2 which
		   is accurate to about 128 bits. */
		अगर (((q > 0)
		     && (exponent(st0_ptr) <= exponent(&CONST_PI2extra) + 64))
		    || (q > 1)) अणु
			/* This code gives the effect of having p/2 to better than
			   128 bits precision. */

			signअगरicand(&पंचांगp) = q;
			setexponent16(&पंचांगp, 63);
			FPU_normalize(&पंचांगp);	/* This must वापस TAG_Valid */
			पंचांगptag =
			    FPU_u_mul(&CONST_PI2extra, &पंचांगp, &पंचांगp,
				      FULL_PRECISION, SIGN_POS,
				      exponent(&CONST_PI2extra) +
				      exponent(&पंचांगp));
			setsign(&पंचांगp, माला_लोign(&CONST_PI2extra));
			st0_tag = FPU_sub(LOADED | (पंचांगptag & 0x0f), (पूर्णांक)&पंचांगp,
					  FULL_PRECISION);
			अगर ((exponent(st0_ptr) == exponent(&CONST_PI2)) &&
			    ((st0_ptr->sigh > CONST_PI2.sigh)
			     || ((st0_ptr->sigh == CONST_PI2.sigh)
				 && (st0_ptr->sigl > CONST_PI2.sigl)))) अणु
				/* CONST_PI2extra is negative, so the result of the
				   subtraction can be larger than pi/2. This means
				   that the argument is actually in a dअगरferent quadrant.
				   The correction is always < pi/2, so it can't overflow
				   पूर्णांकo yet another quadrant. */
				st0_tag =
				    FPU_sub(REV | LOADED | TAG_Valid,
					    (पूर्णांक)&CONST_PI2, FULL_PRECISION);
				q++;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* BETTER_THAN_486 */

	FPU_settag0(st0_tag);
	control_word = old_cw;
	partial_status = saved_status & ~SW_C2;	/* Reduction complete. */

	वापस (q & 3) | even;
पूर्ण

/* Convert a दीर्घ to रेजिस्टर */
अटल व्योम convert_l2reg(दीर्घ स्थिर *arg, पूर्णांक deststnr)
अणु
	पूर्णांक tag;
	दीर्घ num = *arg;
	u_अक्षर sign;
	FPU_REG *dest = &st(deststnr);

	अगर (num == 0) अणु
		FPU_copy_to_regi(&CONST_Z, TAG_Zero, deststnr);
		वापस;
	पूर्ण

	अगर (num > 0) अणु
		sign = SIGN_POS;
	पूर्ण अन्यथा अणु
		num = -num;
		sign = SIGN_NEG;
	पूर्ण

	dest->sigh = num;
	dest->sigl = 0;
	setexponent16(dest, 31);
	tag = FPU_normalize(dest);
	FPU_settagi(deststnr, tag);
	setsign(dest, sign);
	वापस;
पूर्ण

अटल व्योम single_arg_error(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	अगर (st0_tag == TAG_Empty)
		FPU_stack_underflow();	/* Puts a QNaN in st(0) */
	अन्यथा अगर (st0_tag == TW_NaN)
		real_1op_NaN(st0_ptr);	/* वापस with a NaN in st(0) */
#अगर_घोषित PARANOID
	अन्यथा
		EXCEPTION(EX_INTERNAL | 0x0112);
#पूर्ण_अगर /* PARANOID */
पूर्ण

अटल व्योम single_arg_2_error(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	पूर्णांक isNaN;

	चयन (st0_tag) अणु
	हाल TW_NaN:
		isNaN = (exponent(st0_ptr) == EXP_OVER)
		    && (st0_ptr->sigh & 0x80000000);
		अगर (isNaN && !(st0_ptr->sigh & 0x40000000)) अणु	/* Signaling ? */
			EXCEPTION(EX_Invalid);
			अगर (control_word & CW_Invalid) अणु
				/* The masked response */
				/* Convert to a QNaN */
				st0_ptr->sigh |= 0x40000000;
				push();
				FPU_copy_to_reg0(st0_ptr, TAG_Special);
			पूर्ण
		पूर्ण अन्यथा अगर (isNaN) अणु
			/* A QNaN */
			push();
			FPU_copy_to_reg0(st0_ptr, TAG_Special);
		पूर्ण अन्यथा अणु
			/* pseuकरोNaN or other unsupported */
			EXCEPTION(EX_Invalid);
			अगर (control_word & CW_Invalid) अणु
				/* The masked response */
				FPU_copy_to_reg0(&CONST_QNaN, TAG_Special);
				push();
				FPU_copy_to_reg0(&CONST_QNaN, TAG_Special);
			पूर्ण
		पूर्ण
		अवरोध;		/* वापस with a NaN in st(0) */
#अगर_घोषित PARANOID
	शेष:
		EXCEPTION(EX_INTERNAL | 0x0112);
#पूर्ण_अगर /* PARANOID */
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------*/

अटल व्योम f2xm1(FPU_REG *st0_ptr, u_अक्षर tag)
अणु
	FPU_REG a;

	clear_C1();

	अगर (tag == TAG_Valid) अणु
		/* For an 80486 FPU, the result is undefined अगर the arg is >= 1.0 */
		अगर (exponent(st0_ptr) < 0) अणु
		      denormal_arg:

			FPU_to_exp16(st0_ptr, &a);

			/* poly_2xm1(x) requires 0 < st(0) < 1. */
			poly_2xm1(माला_लोign(st0_ptr), &a, st0_ptr);
		पूर्ण
		set_precision_flag_up();	/* 80486 appears to always करो this */
		वापस;
	पूर्ण

	अगर (tag == TAG_Zero)
		वापस;

	अगर (tag == TAG_Special)
		tag = FPU_Special(st0_ptr);

	चयन (tag) अणु
	हाल TW_Denormal:
		अगर (denormal_opeअक्रम() < 0)
			वापस;
		जाओ denormal_arg;
	हाल TW_Infinity:
		अगर (signnegative(st0_ptr)) अणु
			/* -infinity gives -1 (p16-10) */
			FPU_copy_to_reg0(&CONST_1, TAG_Valid);
			setnegative(st0_ptr);
		पूर्ण
		वापस;
	शेष:
		single_arg_error(st0_ptr, tag);
	पूर्ण
पूर्ण

अटल व्योम fptan(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	FPU_REG *st_new_ptr;
	पूर्णांक q;
	u_अक्षर arg_sign = माला_लोign(st0_ptr);

	/* Stack underflow has higher priority */
	अगर (st0_tag == TAG_Empty) अणु
		FPU_stack_underflow();	/* Puts a QNaN in st(0) */
		अगर (control_word & CW_Invalid) अणु
			st_new_ptr = &st(-1);
			push();
			FPU_stack_underflow();	/* Puts a QNaN in the new st(0) */
		पूर्ण
		वापस;
	पूर्ण

	अगर (STACK_OVERFLOW) अणु
		FPU_stack_overflow();
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Valid) अणु
		अगर (exponent(st0_ptr) > -40) अणु
			अगर ((q = trig_arg(st0_ptr, 0)) == -1) अणु
				/* Opeअक्रम is out of range */
				वापस;
			पूर्ण

			poly_tan(st0_ptr);
			setsign(st0_ptr, (q & 1) ^ (arg_sign != 0));
			set_precision_flag_up();	/* We करो not really know अगर up or करोwn */
		पूर्ण अन्यथा अणु
			/* For a small arg, the result == the argument */
			/* Underflow may happen */

		      denormal_arg:

			FPU_to_exp16(st0_ptr, st0_ptr);

			st0_tag =
			    FPU_round(st0_ptr, 1, 0, FULL_PRECISION, arg_sign);
			FPU_settag0(st0_tag);
		पूर्ण
		push();
		FPU_copy_to_reg0(&CONST_1, TAG_Valid);
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Zero) अणु
		push();
		FPU_copy_to_reg0(&CONST_1, TAG_Valid);
		setcc(0);
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	अगर (st0_tag == TW_Denormal) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस;

		जाओ denormal_arg;
	पूर्ण

	अगर (st0_tag == TW_Infinity) अणु
		/* The 80486 treats infinity as an invalid opeअक्रम */
		अगर (arith_invalid(0) >= 0) अणु
			st_new_ptr = &st(-1);
			push();
			arith_invalid(0);
		पूर्ण
		वापस;
	पूर्ण

	single_arg_2_error(st0_ptr, st0_tag);
पूर्ण

अटल व्योम fxtract(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	FPU_REG *st_new_ptr;
	u_अक्षर sign;
	रेजिस्टर FPU_REG *st1_ptr = st0_ptr;	/* anticipate */

	अगर (STACK_OVERFLOW) अणु
		FPU_stack_overflow();
		वापस;
	पूर्ण

	clear_C1();

	अगर (st0_tag == TAG_Valid) अणु
		दीर्घ e;

		push();
		sign = माला_लोign(st1_ptr);
		reg_copy(st1_ptr, st_new_ptr);
		setexponent16(st_new_ptr, exponent(st_new_ptr));

	      denormal_arg:

		e = exponent16(st_new_ptr);
		convert_l2reg(&e, 1);
		setexponentpos(st_new_ptr, 0);
		setsign(st_new_ptr, sign);
		FPU_settag0(TAG_Valid);	/* Needed अगर arg was a denormal */
		वापस;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		sign = माला_लोign(st0_ptr);

		अगर (FPU_भागide_by_zero(0, SIGN_NEG) < 0)
			वापस;

		push();
		FPU_copy_to_reg0(&CONST_Z, TAG_Zero);
		setsign(st_new_ptr, sign);
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	अगर (st0_tag == TW_Denormal) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस;

		push();
		sign = माला_लोign(st1_ptr);
		FPU_to_exp16(st1_ptr, st_new_ptr);
		जाओ denormal_arg;
	पूर्ण अन्यथा अगर (st0_tag == TW_Infinity) अणु
		sign = माला_लोign(st0_ptr);
		setpositive(st0_ptr);
		push();
		FPU_copy_to_reg0(&CONST_INF, TAG_Special);
		setsign(st_new_ptr, sign);
		वापस;
	पूर्ण अन्यथा अगर (st0_tag == TW_NaN) अणु
		अगर (real_1op_NaN(st0_ptr) < 0)
			वापस;

		push();
		FPU_copy_to_reg0(st0_ptr, TAG_Special);
		वापस;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Empty) अणु
		/* Is this the correct behaviour? */
		अगर (control_word & EX_Invalid) अणु
			FPU_stack_underflow();
			push();
			FPU_stack_underflow();
		पूर्ण अन्यथा
			EXCEPTION(EX_StackUnder);
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा
		EXCEPTION(EX_INTERNAL | 0x119);
#पूर्ण_अगर /* PARANOID */
पूर्ण

अटल व्योम fdecstp(व्योम)
अणु
	clear_C1();
	top--;
पूर्ण

अटल व्योम fincstp(व्योम)
अणु
	clear_C1();
	top++;
पूर्ण

अटल व्योम fवर्ग_मूल_(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	पूर्णांक expon;

	clear_C1();

	अगर (st0_tag == TAG_Valid) अणु
		u_अक्षर tag;

		अगर (signnegative(st0_ptr)) अणु
			arith_invalid(0);	/* वर्ग_मूल(negative) is invalid */
			वापस;
		पूर्ण

		/* make st(0) in  [1.0 .. 4.0) */
		expon = exponent(st0_ptr);

	      denormal_arg:

		setexponent16(st0_ptr, (expon & 1));

		/* Do the computation, the sign of the result will be positive. */
		tag = wm_वर्ग_मूल(st0_ptr, 0, 0, control_word, SIGN_POS);
		addexponent(st0_ptr, expon >> 1);
		FPU_settag0(tag);
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Zero)
		वापस;

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	अगर (st0_tag == TW_Infinity) अणु
		अगर (signnegative(st0_ptr))
			arith_invalid(0);	/* वर्ग_मूल(-Infinity) is invalid */
		वापस;
	पूर्ण अन्यथा अगर (st0_tag == TW_Denormal) अणु
		अगर (signnegative(st0_ptr)) अणु
			arith_invalid(0);	/* वर्ग_मूल(negative) is invalid */
			वापस;
		पूर्ण

		अगर (denormal_opeअक्रम() < 0)
			वापस;

		FPU_to_exp16(st0_ptr, st0_ptr);

		expon = exponent16(st0_ptr);

		जाओ denormal_arg;
	पूर्ण

	single_arg_error(st0_ptr, st0_tag);

पूर्ण

अटल व्योम frndपूर्णांक_(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	पूर्णांक flags, tag;

	अगर (st0_tag == TAG_Valid) अणु
		u_अक्षर sign;

	      denormal_arg:

		sign = माला_लोign(st0_ptr);

		अगर (exponent(st0_ptr) > 63)
			वापस;

		अगर (st0_tag == TW_Denormal) अणु
			अगर (denormal_opeअक्रम() < 0)
				वापस;
		पूर्ण

		/* Fortunately, this can't overflow to 2^64 */
		अगर ((flags = FPU_round_to_पूर्णांक(st0_ptr, st0_tag)))
			set_precision_flag(flags);

		setexponent16(st0_ptr, 63);
		tag = FPU_normalize(st0_ptr);
		setsign(st0_ptr, sign);
		FPU_settag0(tag);
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Zero)
		वापस;

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	अगर (st0_tag == TW_Denormal)
		जाओ denormal_arg;
	अन्यथा अगर (st0_tag == TW_Infinity)
		वापस;
	अन्यथा
		single_arg_error(st0_ptr, st0_tag);
पूर्ण

अटल पूर्णांक f_sin(FPU_REG *st0_ptr, u_अक्षर tag)
अणु
	u_अक्षर arg_sign = माला_लोign(st0_ptr);

	अगर (tag == TAG_Valid) अणु
		पूर्णांक q;

		अगर (exponent(st0_ptr) > -40) अणु
			अगर ((q = trig_arg(st0_ptr, 0)) == -1) अणु
				/* Opeअक्रम is out of range */
				वापस 1;
			पूर्ण

			poly_sine(st0_ptr);

			अगर (q & 2)
				changesign(st0_ptr);

			setsign(st0_ptr, माला_लोign(st0_ptr) ^ arg_sign);

			/* We करो not really know अगर up or करोwn */
			set_precision_flag_up();
			वापस 0;
		पूर्ण अन्यथा अणु
			/* For a small arg, the result == the argument */
			set_precision_flag_up();	/* Must be up. */
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (tag == TAG_Zero) अणु
		setcc(0);
		वापस 0;
	पूर्ण

	अगर (tag == TAG_Special)
		tag = FPU_Special(st0_ptr);

	अगर (tag == TW_Denormal) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस 1;

		/* For a small arg, the result == the argument */
		/* Underflow may happen */
		FPU_to_exp16(st0_ptr, st0_ptr);

		tag = FPU_round(st0_ptr, 1, 0, FULL_PRECISION, arg_sign);

		FPU_settag0(tag);

		वापस 0;
	पूर्ण अन्यथा अगर (tag == TW_Infinity) अणु
		/* The 80486 treats infinity as an invalid opeअक्रम */
		arith_invalid(0);
		वापस 1;
	पूर्ण अन्यथा अणु
		single_arg_error(st0_ptr, tag);
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम fsin(FPU_REG *st0_ptr, u_अक्षर tag)
अणु
	f_sin(st0_ptr, tag);
पूर्ण

अटल पूर्णांक f_cos(FPU_REG *st0_ptr, u_अक्षर tag)
अणु
	u_अक्षर st0_sign;

	st0_sign = माला_लोign(st0_ptr);

	अगर (tag == TAG_Valid) अणु
		पूर्णांक q;

		अगर (exponent(st0_ptr) > -40) अणु
			अगर ((exponent(st0_ptr) < 0)
			    || ((exponent(st0_ptr) == 0)
				&& (signअगरicand(st0_ptr) <=
				    0xc90fdaa22168c234LL))) अणु
				poly_cos(st0_ptr);

				/* We करो not really know अगर up or करोwn */
				set_precision_flag_करोwn();

				वापस 0;
			पूर्ण अन्यथा अगर ((q = trig_arg(st0_ptr, FCOS)) != -1) अणु
				poly_sine(st0_ptr);

				अगर ((q + 1) & 2)
					changesign(st0_ptr);

				/* We करो not really know अगर up or करोwn */
				set_precision_flag_करोwn();

				वापस 0;
			पूर्ण अन्यथा अणु
				/* Opeअक्रम is out of range */
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
		      denormal_arg:

			setcc(0);
			FPU_copy_to_reg0(&CONST_1, TAG_Valid);
#अगर_घोषित PECULIAR_486
			set_precision_flag_करोwn();	/* 80486 appears to करो this. */
#अन्यथा
			set_precision_flag_up();	/* Must be up. */
#पूर्ण_अगर /* PECULIAR_486 */
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (tag == TAG_Zero) अणु
		FPU_copy_to_reg0(&CONST_1, TAG_Valid);
		setcc(0);
		वापस 0;
	पूर्ण

	अगर (tag == TAG_Special)
		tag = FPU_Special(st0_ptr);

	अगर (tag == TW_Denormal) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस 1;

		जाओ denormal_arg;
	पूर्ण अन्यथा अगर (tag == TW_Infinity) अणु
		/* The 80486 treats infinity as an invalid opeअक्रम */
		arith_invalid(0);
		वापस 1;
	पूर्ण अन्यथा अणु
		single_arg_error(st0_ptr, tag);	/* requires st0_ptr == &st(0) */
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम fcos(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	f_cos(st0_ptr, st0_tag);
पूर्ण

अटल व्योम fsincos(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	FPU_REG *st_new_ptr;
	FPU_REG arg;
	u_अक्षर tag;

	/* Stack underflow has higher priority */
	अगर (st0_tag == TAG_Empty) अणु
		FPU_stack_underflow();	/* Puts a QNaN in st(0) */
		अगर (control_word & CW_Invalid) अणु
			st_new_ptr = &st(-1);
			push();
			FPU_stack_underflow();	/* Puts a QNaN in the new st(0) */
		पूर्ण
		वापस;
	पूर्ण

	अगर (STACK_OVERFLOW) अणु
		FPU_stack_overflow();
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		tag = FPU_Special(st0_ptr);
	अन्यथा
		tag = st0_tag;

	अगर (tag == TW_NaN) अणु
		single_arg_2_error(st0_ptr, TW_NaN);
		वापस;
	पूर्ण अन्यथा अगर (tag == TW_Infinity) अणु
		/* The 80486 treats infinity as an invalid opeअक्रम */
		अगर (arith_invalid(0) >= 0) अणु
			/* Masked response */
			push();
			arith_invalid(0);
		पूर्ण
		वापस;
	पूर्ण

	reg_copy(st0_ptr, &arg);
	अगर (!f_sin(st0_ptr, st0_tag)) अणु
		push();
		FPU_copy_to_reg0(&arg, st0_tag);
		f_cos(&st(0), st0_tag);
	पूर्ण अन्यथा अणु
		/* An error, so restore st(0) */
		FPU_copy_to_reg0(&arg, st0_tag);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------*/
/* The following all require two arguments: st(0) and st(1) */

/* A lean, mean kernel क्रम the fprem inकाष्ठाions. This relies upon
   the भागision and rounding to an पूर्णांकeger in करो_fprem giving an
   exact result. Because of this, rem_kernel() needs to deal only with
   the least signअगरicant 64 bits, the more signअगरicant bits of the
   result must be zero.
 */
अटल व्योम rem_kernel(अचिन्हित दीर्घ दीर्घ st0, अचिन्हित दीर्घ दीर्घ *y,
		       अचिन्हित दीर्घ दीर्घ st1, अचिन्हित दीर्घ दीर्घ q, पूर्णांक n)
अणु
	पूर्णांक dummy;
	अचिन्हित दीर्घ दीर्घ x;

	x = st0 << n;

	/* Do the required multiplication and subtraction in the one operation */

	/* lsw x -= lsw st1 * lsw q */
	यंत्र अस्थिर ("mull %4; subl %%eax,%0; sbbl %%edx,%1":"=m"
		      (((अचिन्हित *)&x)[0]), "=m"(((अचिन्हित *)&x)[1]),
		      "=a"(dummy)
		      :"2"(((अचिन्हित *)&st1)[0]), "m"(((अचिन्हित *)&q)[0])
		      :"%dx");
	/* msw x -= msw st1 * lsw q */
	यंत्र अस्थिर ("mull %3; subl %%eax,%0":"=m" (((अचिन्हित *)&x)[1]),
		      "=a"(dummy)
		      :"1"(((अचिन्हित *)&st1)[1]), "m"(((अचिन्हित *)&q)[0])
		      :"%dx");
	/* msw x -= lsw st1 * msw q */
	यंत्र अस्थिर ("mull %3; subl %%eax,%0":"=m" (((अचिन्हित *)&x)[1]),
		      "=a"(dummy)
		      :"1"(((अचिन्हित *)&st1)[0]), "m"(((अचिन्हित *)&q)[1])
		      :"%dx");

	*y = x;
पूर्ण

/* Reमुख्यder of st(0) / st(1) */
/* This routine produces exact results, i.e. there is never any
   rounding or truncation, etc of the result. */
अटल व्योम करो_fprem(FPU_REG *st0_ptr, u_अक्षर st0_tag, पूर्णांक round)
अणु
	FPU_REG *st1_ptr = &st(1);
	u_अक्षर st1_tag = FPU_gettagi(1);

	अगर (!((st0_tag ^ TAG_Valid) | (st1_tag ^ TAG_Valid))) अणु
		FPU_REG पंचांगp, st0, st1;
		u_अक्षर st0_sign, st1_sign;
		u_अक्षर पंचांगptag;
		पूर्णांक tag;
		पूर्णांक old_cw;
		पूर्णांक expdअगर;
		दीर्घ दीर्घ q;
		अचिन्हित लघु saved_status;
		पूर्णांक cc;

	      fprem_valid:
		/* Convert रेजिस्टरs क्रम पूर्णांकernal use. */
		st0_sign = FPU_to_exp16(st0_ptr, &st0);
		st1_sign = FPU_to_exp16(st1_ptr, &st1);
		expdअगर = exponent16(&st0) - exponent16(&st1);

		old_cw = control_word;
		cc = 0;

		/* We want the status following the denorm tests, but करोn't want
		   the status changed by the arithmetic operations. */
		saved_status = partial_status;
		control_word &= ~CW_RC;
		control_word |= RC_CHOP;

		अगर (expdअगर < 64) अणु
			/* This should be the most common हाल */

			अगर (expdअगर > -2) अणु
				u_अक्षर sign = st0_sign ^ st1_sign;
				tag = FPU_u_भाग(&st0, &st1, &पंचांगp,
						PR_64_BITS | RC_CHOP | 0x3f,
						sign);
				setsign(&पंचांगp, sign);

				अगर (exponent(&पंचांगp) >= 0) अणु
					FPU_round_to_पूर्णांक(&पंचांगp, tag);	/* Fortunately, this can't
									   overflow to 2^64 */
					q = signअगरicand(&पंचांगp);

					rem_kernel(signअगरicand(&st0),
						   &signअगरicand(&पंचांगp),
						   signअगरicand(&st1),
						   q, expdअगर);

					setexponent16(&पंचांगp, exponent16(&st1));
				पूर्ण अन्यथा अणु
					reg_copy(&st0, &पंचांगp);
					q = 0;
				पूर्ण

				अगर ((round == RC_RND)
				    && (पंचांगp.sigh & 0xc0000000)) अणु
					/* We may need to subtract st(1) once more,
					   to get a result <= 1/2 of st(1). */
					अचिन्हित दीर्घ दीर्घ x;
					expdअगर =
					    exponent16(&st1) - exponent16(&पंचांगp);
					अगर (expdअगर <= 1) अणु
						अगर (expdअगर == 0)
							x = signअगरicand(&st1) -
							    signअगरicand(&पंचांगp);
						अन्यथा	/* expdअगर is 1 */
							x = (signअगरicand(&st1)
							     << 1) -
							    signअगरicand(&पंचांगp);
						अगर ((x < signअगरicand(&पंचांगp)) ||
						    /* or equi-distant (from 0 & st(1)) and q is odd */
						    ((x == signअगरicand(&पंचांगp))
						     && (q & 1))) अणु
							st0_sign = !st0_sign;
							signअगरicand(&पंचांगp) = x;
							q++;
						पूर्ण
					पूर्ण
				पूर्ण

				अगर (q & 4)
					cc |= SW_C0;
				अगर (q & 2)
					cc |= SW_C3;
				अगर (q & 1)
					cc |= SW_C1;
			पूर्ण अन्यथा अणु
				control_word = old_cw;
				setcc(0);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* There is a large exponent dअगरference ( >= 64 ) */
			/* To make much sense, the code in this section should
			   be करोne at high precision. */
			पूर्णांक exp_1, N;
			u_अक्षर sign;

			/* prevent overflow here */
			/* N is 'a number between 32 and 63' (p26-113) */
			reg_copy(&st0, &पंचांगp);
			पंचांगptag = st0_tag;
			N = (expdअगर & 0x0000001f) + 32;	/* This choice gives results
							   identical to an AMD 486 */
			setexponent16(&पंचांगp, N);
			exp_1 = exponent16(&st1);
			setexponent16(&st1, 0);
			expdअगर -= N;

			sign = माला_लोign(&पंचांगp) ^ st1_sign;
			tag =
			    FPU_u_भाग(&पंचांगp, &st1, &पंचांगp,
				      PR_64_BITS | RC_CHOP | 0x3f, sign);
			setsign(&पंचांगp, sign);

			FPU_round_to_पूर्णांक(&पंचांगp, tag);	/* Fortunately, this can't
							   overflow to 2^64 */

			rem_kernel(signअगरicand(&st0),
				   &signअगरicand(&पंचांगp),
				   signअगरicand(&st1),
				   signअगरicand(&पंचांगp), exponent(&पंचांगp)
			    );
			setexponent16(&पंचांगp, exp_1 + expdअगर);

			/* It is possible क्रम the operation to be complete here.
			   What करोes the IEEE standard say? The Intel 80486 manual
			   implies that the operation will never be completed at this
			   poपूर्णांक, and the behaviour of a real 80486 confirms this.
			 */
			अगर (!(पंचांगp.sigh | पंचांगp.sigl)) अणु
				/* The result is zero */
				control_word = old_cw;
				partial_status = saved_status;
				FPU_copy_to_reg0(&CONST_Z, TAG_Zero);
				setsign(&st0, st0_sign);
#अगर_घोषित PECULIAR_486
				setcc(SW_C2);
#अन्यथा
				setcc(0);
#पूर्ण_अगर /* PECULIAR_486 */
				वापस;
			पूर्ण
			cc = SW_C2;
		पूर्ण

		control_word = old_cw;
		partial_status = saved_status;
		tag = FPU_normalize_nuo(&पंचांगp);
		reg_copy(&पंचांगp, st0_ptr);

		/* The only condition to be looked क्रम is underflow,
		   and it can occur here only अगर underflow is unmasked. */
		अगर ((exponent16(&पंचांगp) <= EXP_UNDER) && (tag != TAG_Zero)
		    && !(control_word & CW_Underflow)) अणु
			setcc(cc);
			tag = arith_underflow(st0_ptr);
			setsign(st0_ptr, st0_sign);
			FPU_settag0(tag);
			वापस;
		पूर्ण अन्यथा अगर ((exponent16(&पंचांगp) > EXP_UNDER) || (tag == TAG_Zero)) अणु
			stdexp(st0_ptr);
			setsign(st0_ptr, st0_sign);
		पूर्ण अन्यथा अणु
			tag =
			    FPU_round(st0_ptr, 0, 0, FULL_PRECISION, st0_sign);
		पूर्ण
		FPU_settag0(tag);
		setcc(cc);

		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);
	अगर (st1_tag == TAG_Special)
		st1_tag = FPU_Special(st1_ptr);

	अगर (((st0_tag == TAG_Valid) && (st1_tag == TW_Denormal))
	    || ((st0_tag == TW_Denormal) && (st1_tag == TAG_Valid))
	    || ((st0_tag == TW_Denormal) && (st1_tag == TW_Denormal))) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस;
		जाओ fprem_valid;
	पूर्ण अन्यथा अगर ((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty)) अणु
		FPU_stack_underflow();
		वापस;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		अगर (st1_tag == TAG_Valid) अणु
			setcc(0);
			वापस;
		पूर्ण अन्यथा अगर (st1_tag == TW_Denormal) अणु
			अगर (denormal_opeअक्रम() < 0)
				वापस;
			setcc(0);
			वापस;
		पूर्ण अन्यथा अगर (st1_tag == TAG_Zero) अणु
			arith_invalid(0);
			वापस;
		पूर्ण /* fprem(?,0) always invalid */
		अन्यथा अगर (st1_tag == TW_Infinity) अणु
			setcc(0);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर ((st0_tag == TAG_Valid) || (st0_tag == TW_Denormal)) अणु
		अगर (st1_tag == TAG_Zero) अणु
			arith_invalid(0);	/* fprem(Valid,Zero) is invalid */
			वापस;
		पूर्ण अन्यथा अगर (st1_tag != TW_NaN) अणु
			अगर (((st0_tag == TW_Denormal)
			     || (st1_tag == TW_Denormal))
			    && (denormal_opeअक्रम() < 0))
				वापस;

			अगर (st1_tag == TW_Infinity) अणु
				/* fprem(Valid,Infinity) is o.k. */
				setcc(0);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TW_Infinity) अणु
		अगर (st1_tag != TW_NaN) अणु
			arith_invalid(0);	/* fprem(Infinity,?) is invalid */
			वापस;
		पूर्ण
	पूर्ण

	/* One of the रेजिस्टरs must contain a NaN अगर we got here. */

#अगर_घोषित PARANOID
	अगर ((st0_tag != TW_NaN) && (st1_tag != TW_NaN))
		EXCEPTION(EX_INTERNAL | 0x118);
#पूर्ण_अगर /* PARANOID */

	real_2op_NaN(st1_ptr, st1_tag, 0, st1_ptr);

पूर्ण

/* ST(1) <- ST(1) * log ST;  pop ST */
अटल व्योम fyl2x(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	FPU_REG *st1_ptr = &st(1), exponent;
	u_अक्षर st1_tag = FPU_gettagi(1);
	u_अक्षर sign;
	पूर्णांक e, tag;

	clear_C1();

	अगर ((st0_tag == TAG_Valid) && (st1_tag == TAG_Valid)) अणु
	      both_valid:
		/* Both regs are Valid or Denormal */
		अगर (signpositive(st0_ptr)) अणु
			अगर (st0_tag == TW_Denormal)
				FPU_to_exp16(st0_ptr, st0_ptr);
			अन्यथा
				/* Convert st(0) क्रम पूर्णांकernal use. */
				setexponent16(st0_ptr, exponent(st0_ptr));

			अगर ((st0_ptr->sigh == 0x80000000)
			    && (st0_ptr->sigl == 0)) अणु
				/* Special हाल. The result can be precise. */
				u_अक्षर esign;
				e = exponent16(st0_ptr);
				अगर (e >= 0) अणु
					exponent.sigh = e;
					esign = SIGN_POS;
				पूर्ण अन्यथा अणु
					exponent.sigh = -e;
					esign = SIGN_NEG;
				पूर्ण
				exponent.sigl = 0;
				setexponent16(&exponent, 31);
				tag = FPU_normalize_nuo(&exponent);
				stdexp(&exponent);
				setsign(&exponent, esign);
				tag =
				    FPU_mul(&exponent, tag, 1, FULL_PRECISION);
				अगर (tag >= 0)
					FPU_settagi(1, tag);
			पूर्ण अन्यथा अणु
				/* The usual हाल */
				sign = माला_लोign(st1_ptr);
				अगर (st1_tag == TW_Denormal)
					FPU_to_exp16(st1_ptr, st1_ptr);
				अन्यथा
					/* Convert st(1) क्रम पूर्णांकernal use. */
					setexponent16(st1_ptr,
						      exponent(st1_ptr));
				poly_l2(st0_ptr, st1_ptr, sign);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* negative */
			अगर (arith_invalid(1) < 0)
				वापस;
		पूर्ण

		FPU_pop();

		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);
	अगर (st1_tag == TAG_Special)
		st1_tag = FPU_Special(st1_ptr);

	अगर ((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty)) अणु
		FPU_stack_underflow_pop(1);
		वापस;
	पूर्ण अन्यथा अगर ((st0_tag <= TW_Denormal) && (st1_tag <= TW_Denormal)) अणु
		अगर (st0_tag == TAG_Zero) अणु
			अगर (st1_tag == TAG_Zero) अणु
				/* Both args zero is invalid */
				अगर (arith_invalid(1) < 0)
					वापस;
			पूर्ण अन्यथा अणु
				u_अक्षर sign;
				sign = माला_लोign(st1_ptr) ^ SIGN_NEG;
				अगर (FPU_भागide_by_zero(1, sign) < 0)
					वापस;

				setsign(st1_ptr, sign);
			पूर्ण
		पूर्ण अन्यथा अगर (st1_tag == TAG_Zero) अणु
			/* st(1) contains zero, st(0) valid <> 0 */
			/* Zero is the valid answer */
			sign = माला_लोign(st1_ptr);

			अगर (signnegative(st0_ptr)) अणु
				/* log(negative) */
				अगर (arith_invalid(1) < 0)
					वापस;
			पूर्ण अन्यथा अगर ((st0_tag == TW_Denormal)
				   && (denormal_opeअक्रम() < 0))
				वापस;
			अन्यथा अणु
				अगर (exponent(st0_ptr) < 0)
					sign ^= SIGN_NEG;

				FPU_copy_to_reg1(&CONST_Z, TAG_Zero);
				setsign(st1_ptr, sign);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* One or both opeअक्रमs are denormals. */
			अगर (denormal_opeअक्रम() < 0)
				वापस;
			जाओ both_valid;
		पूर्ण
	पूर्ण अन्यथा अगर ((st0_tag == TW_NaN) || (st1_tag == TW_NaN)) अणु
		अगर (real_2op_NaN(st0_ptr, st0_tag, 1, st0_ptr) < 0)
			वापस;
	पूर्ण
	/* One or both arg must be an infinity */
	अन्यथा अगर (st0_tag == TW_Infinity) अणु
		अगर ((signnegative(st0_ptr)) || (st1_tag == TAG_Zero)) अणु
			/* log(-infinity) or 0*log(infinity) */
			अगर (arith_invalid(1) < 0)
				वापस;
		पूर्ण अन्यथा अणु
			u_अक्षर sign = माला_लोign(st1_ptr);

			अगर ((st1_tag == TW_Denormal)
			    && (denormal_opeअक्रम() < 0))
				वापस;

			FPU_copy_to_reg1(&CONST_INF, TAG_Special);
			setsign(st1_ptr, sign);
		पूर्ण
	पूर्ण
	/* st(1) must be infinity here */
	अन्यथा अगर (((st0_tag == TAG_Valid) || (st0_tag == TW_Denormal))
		 && (signpositive(st0_ptr))) अणु
		अगर (exponent(st0_ptr) >= 0) अणु
			अगर ((exponent(st0_ptr) == 0) &&
			    (st0_ptr->sigh == 0x80000000) &&
			    (st0_ptr->sigl == 0)) अणु
				/* st(0) holds 1.0 */
				/* infinity*log(1) */
				अगर (arith_invalid(1) < 0)
					वापस;
			पूर्ण
			/* अन्यथा st(0) is positive and > 1.0 */
		पूर्ण अन्यथा अणु
			/* st(0) is positive and < 1.0 */

			अगर ((st0_tag == TW_Denormal)
			    && (denormal_opeअक्रम() < 0))
				वापस;

			changesign(st1_ptr);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* st(0) must be zero or negative */
		अगर (st0_tag == TAG_Zero) अणु
			/* This should be invalid, but a real 80486 is happy with it. */

#अगर_अघोषित PECULIAR_486
			sign = माला_लोign(st1_ptr);
			अगर (FPU_भागide_by_zero(1, sign) < 0)
				वापस;
#पूर्ण_अगर /* PECULIAR_486 */

			changesign(st1_ptr);
		पूर्ण अन्यथा अगर (arith_invalid(1) < 0)	/* log(negative) */
			वापस;
	पूर्ण

	FPU_pop();
पूर्ण

अटल व्योम fpatan(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	FPU_REG *st1_ptr = &st(1);
	u_अक्षर st1_tag = FPU_gettagi(1);
	पूर्णांक tag;

	clear_C1();
	अगर (!((st0_tag ^ TAG_Valid) | (st1_tag ^ TAG_Valid))) अणु
	      valid_atan:

		poly_atan(st0_ptr, st0_tag, st1_ptr, st1_tag);

		FPU_pop();

		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);
	अगर (st1_tag == TAG_Special)
		st1_tag = FPU_Special(st1_ptr);

	अगर (((st0_tag == TAG_Valid) && (st1_tag == TW_Denormal))
	    || ((st0_tag == TW_Denormal) && (st1_tag == TAG_Valid))
	    || ((st0_tag == TW_Denormal) && (st1_tag == TW_Denormal))) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस;

		जाओ valid_atan;
	पूर्ण अन्यथा अगर ((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty)) अणु
		FPU_stack_underflow_pop(1);
		वापस;
	पूर्ण अन्यथा अगर ((st0_tag == TW_NaN) || (st1_tag == TW_NaN)) अणु
		अगर (real_2op_NaN(st0_ptr, st0_tag, 1, st0_ptr) >= 0)
			FPU_pop();
		वापस;
	पूर्ण अन्यथा अगर ((st0_tag == TW_Infinity) || (st1_tag == TW_Infinity)) अणु
		u_अक्षर sign = माला_लोign(st1_ptr);
		अगर (st0_tag == TW_Infinity) अणु
			अगर (st1_tag == TW_Infinity) अणु
				अगर (signpositive(st0_ptr)) अणु
					FPU_copy_to_reg1(&CONST_PI4, TAG_Valid);
				पूर्ण अन्यथा अणु
					setpositive(st1_ptr);
					tag =
					    FPU_u_add(&CONST_PI4, &CONST_PI2,
						      st1_ptr, FULL_PRECISION,
						      SIGN_POS,
						      exponent(&CONST_PI4),
						      exponent(&CONST_PI2));
					अगर (tag >= 0)
						FPU_settagi(1, tag);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर ((st1_tag == TW_Denormal)
				    && (denormal_opeअक्रम() < 0))
					वापस;

				अगर (signpositive(st0_ptr)) अणु
					FPU_copy_to_reg1(&CONST_Z, TAG_Zero);
					setsign(st1_ptr, sign);	/* An 80486 preserves the sign */
					FPU_pop();
					वापस;
				पूर्ण अन्यथा अणु
					FPU_copy_to_reg1(&CONST_PI, TAG_Valid);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* st(1) is infinity, st(0) not infinity */
			अगर ((st0_tag == TW_Denormal)
			    && (denormal_opeअक्रम() < 0))
				वापस;

			FPU_copy_to_reg1(&CONST_PI2, TAG_Valid);
		पूर्ण
		setsign(st1_ptr, sign);
	पूर्ण अन्यथा अगर (st1_tag == TAG_Zero) अणु
		/* st(0) must be valid or zero */
		u_अक्षर sign = माला_लोign(st1_ptr);

		अगर ((st0_tag == TW_Denormal) && (denormal_opeअक्रम() < 0))
			वापस;

		अगर (signpositive(st0_ptr)) अणु
			/* An 80486 preserves the sign */
			FPU_pop();
			वापस;
		पूर्ण

		FPU_copy_to_reg1(&CONST_PI, TAG_Valid);
		setsign(st1_ptr, sign);
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		/* st(1) must be TAG_Valid here */
		u_अक्षर sign = माला_लोign(st1_ptr);

		अगर ((st1_tag == TW_Denormal) && (denormal_opeअक्रम() < 0))
			वापस;

		FPU_copy_to_reg1(&CONST_PI2, TAG_Valid);
		setsign(st1_ptr, sign);
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा
		EXCEPTION(EX_INTERNAL | 0x125);
#पूर्ण_अगर /* PARANOID */

	FPU_pop();
	set_precision_flag_up();	/* We करो not really know अगर up or करोwn */
पूर्ण

अटल व्योम fprem(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	करो_fprem(st0_ptr, st0_tag, RC_CHOP);
पूर्ण

अटल व्योम fprem1(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	करो_fprem(st0_ptr, st0_tag, RC_RND);
पूर्ण

अटल व्योम fyl2xp1(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	u_अक्षर sign, sign1;
	FPU_REG *st1_ptr = &st(1), a, b;
	u_अक्षर st1_tag = FPU_gettagi(1);

	clear_C1();
	अगर (!((st0_tag ^ TAG_Valid) | (st1_tag ^ TAG_Valid))) अणु
	      valid_yl2xp1:

		sign = माला_लोign(st0_ptr);
		sign1 = माला_लोign(st1_ptr);

		FPU_to_exp16(st0_ptr, &a);
		FPU_to_exp16(st1_ptr, &b);

		अगर (poly_l2p1(sign, sign1, &a, &b, st1_ptr))
			वापस;

		FPU_pop();
		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);
	अगर (st1_tag == TAG_Special)
		st1_tag = FPU_Special(st1_ptr);

	अगर (((st0_tag == TAG_Valid) && (st1_tag == TW_Denormal))
	    || ((st0_tag == TW_Denormal) && (st1_tag == TAG_Valid))
	    || ((st0_tag == TW_Denormal) && (st1_tag == TW_Denormal))) अणु
		अगर (denormal_opeअक्रम() < 0)
			वापस;

		जाओ valid_yl2xp1;
	पूर्ण अन्यथा अगर ((st0_tag == TAG_Empty) | (st1_tag == TAG_Empty)) अणु
		FPU_stack_underflow_pop(1);
		वापस;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		चयन (st1_tag) अणु
		हाल TW_Denormal:
			अगर (denormal_opeअक्रम() < 0)
				वापस;
			fallthrough;
		हाल TAG_Zero:
		हाल TAG_Valid:
			setsign(st0_ptr, माला_लोign(st0_ptr) ^ माला_लोign(st1_ptr));
			FPU_copy_to_reg1(st0_ptr, st0_tag);
			अवरोध;

		हाल TW_Infinity:
			/* Infinity*log(1) */
			अगर (arith_invalid(1) < 0)
				वापस;
			अवरोध;

		हाल TW_NaN:
			अगर (real_2op_NaN(st0_ptr, st0_tag, 1, st0_ptr) < 0)
				वापस;
			अवरोध;

		शेष:
#अगर_घोषित PARANOID
			EXCEPTION(EX_INTERNAL | 0x116);
			वापस;
#पूर्ण_अगर /* PARANOID */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर ((st0_tag == TAG_Valid) || (st0_tag == TW_Denormal)) अणु
		चयन (st1_tag) अणु
		हाल TAG_Zero:
			अगर (signnegative(st0_ptr)) अणु
				अगर (exponent(st0_ptr) >= 0) अणु
					/* st(0) holds <= -1.0 */
#अगर_घोषित PECULIAR_486		/* Stupid 80486 करोesn't worry about log(negative). */
					changesign(st1_ptr);
#अन्यथा
					अगर (arith_invalid(1) < 0)
						वापस;
#पूर्ण_अगर /* PECULIAR_486 */
				पूर्ण अन्यथा अगर ((st0_tag == TW_Denormal)
					   && (denormal_opeअक्रम() < 0))
					वापस;
				अन्यथा
					changesign(st1_ptr);
			पूर्ण अन्यथा अगर ((st0_tag == TW_Denormal)
				   && (denormal_opeअक्रम() < 0))
				वापस;
			अवरोध;

		हाल TW_Infinity:
			अगर (signnegative(st0_ptr)) अणु
				अगर ((exponent(st0_ptr) >= 0) &&
				    !((st0_ptr->sigh == 0x80000000) &&
				      (st0_ptr->sigl == 0))) अणु
					/* st(0) holds < -1.0 */
#अगर_घोषित PECULIAR_486		/* Stupid 80486 करोesn't worry about log(negative). */
					changesign(st1_ptr);
#अन्यथा
					अगर (arith_invalid(1) < 0)
						वापस;
#पूर्ण_अगर /* PECULIAR_486 */
				पूर्ण अन्यथा अगर ((st0_tag == TW_Denormal)
					   && (denormal_opeअक्रम() < 0))
					वापस;
				अन्यथा
					changesign(st1_ptr);
			पूर्ण अन्यथा अगर ((st0_tag == TW_Denormal)
				   && (denormal_opeअक्रम() < 0))
				वापस;
			अवरोध;

		हाल TW_NaN:
			अगर (real_2op_NaN(st0_ptr, st0_tag, 1, st0_ptr) < 0)
				वापस;
		पूर्ण

	पूर्ण अन्यथा अगर (st0_tag == TW_NaN) अणु
		अगर (real_2op_NaN(st0_ptr, st0_tag, 1, st0_ptr) < 0)
			वापस;
	पूर्ण अन्यथा अगर (st0_tag == TW_Infinity) अणु
		अगर (st1_tag == TW_NaN) अणु
			अगर (real_2op_NaN(st0_ptr, st0_tag, 1, st0_ptr) < 0)
				वापस;
		पूर्ण अन्यथा अगर (signnegative(st0_ptr)) अणु
#अगर_अघोषित PECULIAR_486
			/* This should have higher priority than denormals, but... */
			अगर (arith_invalid(1) < 0)	/* log(-infinity) */
				वापस;
#पूर्ण_अगर /* PECULIAR_486 */
			अगर ((st1_tag == TW_Denormal)
			    && (denormal_opeअक्रम() < 0))
				वापस;
#अगर_घोषित PECULIAR_486
			/* Denormal opeअक्रमs actually get higher priority */
			अगर (arith_invalid(1) < 0)	/* log(-infinity) */
				वापस;
#पूर्ण_अगर /* PECULIAR_486 */
		पूर्ण अन्यथा अगर (st1_tag == TAG_Zero) अणु
			/* log(infinity) */
			अगर (arith_invalid(1) < 0)
				वापस;
		पूर्ण

		/* st(1) must be valid here. */

		अन्यथा अगर ((st1_tag == TW_Denormal) && (denormal_opeअक्रम() < 0))
			वापस;

		/* The Manual says that log(Infinity) is invalid, but a real
		   80486 sensibly says that it is o.k. */
		अन्यथा अणु
			u_अक्षर sign = माला_लोign(st1_ptr);
			FPU_copy_to_reg1(&CONST_INF, TAG_Special);
			setsign(st1_ptr, sign);
		पूर्ण
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा अणु
		EXCEPTION(EX_INTERNAL | 0x117);
		वापस;
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	FPU_pop();
	वापस;

पूर्ण

अटल व्योम fscale(FPU_REG *st0_ptr, u_अक्षर st0_tag)
अणु
	FPU_REG *st1_ptr = &st(1);
	u_अक्षर st1_tag = FPU_gettagi(1);
	पूर्णांक old_cw = control_word;
	u_अक्षर sign = माला_लोign(st0_ptr);

	clear_C1();
	अगर (!((st0_tag ^ TAG_Valid) | (st1_tag ^ TAG_Valid))) अणु
		दीर्घ scale;
		FPU_REG पंचांगp;

		/* Convert रेजिस्टर क्रम पूर्णांकernal use. */
		setexponent16(st0_ptr, exponent(st0_ptr));

	      valid_scale:

		अगर (exponent(st1_ptr) > 30) अणु
			/* 2^31 is far too large, would require 2^(2^30) or 2^(-2^30) */

			अगर (signpositive(st1_ptr)) अणु
				EXCEPTION(EX_Overflow);
				FPU_copy_to_reg0(&CONST_INF, TAG_Special);
			पूर्ण अन्यथा अणु
				EXCEPTION(EX_Underflow);
				FPU_copy_to_reg0(&CONST_Z, TAG_Zero);
			पूर्ण
			setsign(st0_ptr, sign);
			वापस;
		पूर्ण

		control_word &= ~CW_RC;
		control_word |= RC_CHOP;
		reg_copy(st1_ptr, &पंचांगp);
		FPU_round_to_पूर्णांक(&पंचांगp, st1_tag);	/* This can never overflow here */
		control_word = old_cw;
		scale = signnegative(st1_ptr) ? -पंचांगp.sigl : पंचांगp.sigl;
		scale += exponent16(st0_ptr);

		setexponent16(st0_ptr, scale);

		/* Use FPU_round() to properly detect under/overflow etc */
		FPU_round(st0_ptr, 0, 0, control_word, sign);

		वापस;
	पूर्ण

	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);
	अगर (st1_tag == TAG_Special)
		st1_tag = FPU_Special(st1_ptr);

	अगर ((st0_tag == TAG_Valid) || (st0_tag == TW_Denormal)) अणु
		चयन (st1_tag) अणु
		हाल TAG_Valid:
			/* st(0) must be a denormal */
			अगर ((st0_tag == TW_Denormal)
			    && (denormal_opeअक्रम() < 0))
				वापस;

			FPU_to_exp16(st0_ptr, st0_ptr);	/* Will not be left on stack */
			जाओ valid_scale;

		हाल TAG_Zero:
			अगर (st0_tag == TW_Denormal)
				denormal_opeअक्रम();
			वापस;

		हाल TW_Denormal:
			denormal_opeअक्रम();
			वापस;

		हाल TW_Infinity:
			अगर ((st0_tag == TW_Denormal)
			    && (denormal_opeअक्रम() < 0))
				वापस;

			अगर (signpositive(st1_ptr))
				FPU_copy_to_reg0(&CONST_INF, TAG_Special);
			अन्यथा
				FPU_copy_to_reg0(&CONST_Z, TAG_Zero);
			setsign(st0_ptr, sign);
			वापस;

		हाल TW_NaN:
			real_2op_NaN(st1_ptr, st1_tag, 0, st0_ptr);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		चयन (st1_tag) अणु
		हाल TAG_Valid:
		हाल TAG_Zero:
			वापस;

		हाल TW_Denormal:
			denormal_opeअक्रम();
			वापस;

		हाल TW_Infinity:
			अगर (signpositive(st1_ptr))
				arith_invalid(0);	/* Zero scaled by +Infinity */
			वापस;

		हाल TW_NaN:
			real_2op_NaN(st1_ptr, st1_tag, 0, st0_ptr);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TW_Infinity) अणु
		चयन (st1_tag) अणु
		हाल TAG_Valid:
		हाल TAG_Zero:
			वापस;

		हाल TW_Denormal:
			denormal_opeअक्रम();
			वापस;

		हाल TW_Infinity:
			अगर (signnegative(st1_ptr))
				arith_invalid(0);	/* Infinity scaled by -Infinity */
			वापस;

		हाल TW_NaN:
			real_2op_NaN(st1_ptr, st1_tag, 0, st0_ptr);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TW_NaN) अणु
		अगर (st1_tag != TAG_Empty) अणु
			real_2op_NaN(st1_ptr, st1_tag, 0, st0_ptr);
			वापस;
		पूर्ण
	पूर्ण
#अगर_घोषित PARANOID
	अगर (!((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty))) अणु
		EXCEPTION(EX_INTERNAL | 0x115);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* At least one of st(0), st(1) must be empty */
	FPU_stack_underflow();

पूर्ण

/*---------------------------------------------------------------------------*/

अटल FUNC_ST0 स्थिर trig_table_a[] = अणु
	f2xm1, fyl2x, fptan, fpatan,
	fxtract, fprem1, (FUNC_ST0) fdecstp, (FUNC_ST0) fincstp
पूर्ण;

व्योम FPU_triga(व्योम)
अणु
	(trig_table_a[FPU_rm]) (&st(0), FPU_gettag0());
पूर्ण

अटल FUNC_ST0 स्थिर trig_table_b[] = अणु
	fprem, fyl2xp1, fवर्ग_मूल_, fsincos, frndपूर्णांक_, fscale, fsin, fcos
पूर्ण;

व्योम FPU_trigb(व्योम)
अणु
	(trig_table_b[FPU_rm]) (&st(0), FPU_gettag0());
पूर्ण
