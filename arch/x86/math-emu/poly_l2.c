<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  poly_l2.c                                                                |
 |                                                                           |
 | Compute the base 2 log of a FPU_REG, using a polynomial approximation.    |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "fpu_emu.h"
#समावेश "fpu_system.h"
#समावेश "control_w.h"
#समावेश "poly.h"

अटल व्योम log2_kernel(FPU_REG स्थिर *arg, u_अक्षर argsign,
			Xsig * accum_result, दीर्घ पूर्णांक *expon);

/*--- poly_l2() -------------------------------------------------------------+
 |   Base 2 logarithm by a polynomial approximation.                         |
 +---------------------------------------------------------------------------*/
व्योम poly_l2(FPU_REG *st0_ptr, FPU_REG *st1_ptr, u_अक्षर st1_sign)
अणु
	दीर्घ पूर्णांक exponent, expon, expon_expon;
	Xsig accumulator, expon_accum, yaccum;
	u_अक्षर sign, argsign;
	FPU_REG x;
	पूर्णांक tag;

	exponent = exponent16(st0_ptr);

	/* From st0_ptr, make a number > वर्ग_मूल(2)/2 and < वर्ग_मूल(2) */
	अगर (st0_ptr->sigh > (अचिन्हित)0xb504f334) अणु
		/* Treat as  वर्ग_मूल(2)/2 < st0_ptr < 1 */
		signअगरicand(&x) = -signअगरicand(st0_ptr);
		setexponent16(&x, -1);
		exponent++;
		argsign = SIGN_NEG;
	पूर्ण अन्यथा अणु
		/* Treat as  1 <= st0_ptr < वर्ग_मूल(2) */
		x.sigh = st0_ptr->sigh - 0x80000000;
		x.sigl = st0_ptr->sigl;
		setexponent16(&x, 0);
		argsign = SIGN_POS;
	पूर्ण
	tag = FPU_normalize_nuo(&x);

	अगर (tag == TAG_Zero) अणु
		expon = 0;
		accumulator.msw = accumulator.midw = accumulator.lsw = 0;
	पूर्ण अन्यथा अणु
		log2_kernel(&x, argsign, &accumulator, &expon);
	पूर्ण

	अगर (exponent < 0) अणु
		sign = SIGN_NEG;
		exponent = -exponent;
	पूर्ण अन्यथा
		sign = SIGN_POS;
	expon_accum.msw = exponent;
	expon_accum.midw = expon_accum.lsw = 0;
	अगर (exponent) अणु
		expon_expon = 31 + norm_Xsig(&expon_accum);
		shr_Xsig(&accumulator, expon_expon - expon);

		अगर (sign ^ argsign)
			negate_Xsig(&accumulator);
		add_Xsig_Xsig(&accumulator, &expon_accum);
	पूर्ण अन्यथा अणु
		expon_expon = expon;
		sign = argsign;
	पूर्ण

	yaccum.lsw = 0;
	XSIG_LL(yaccum) = signअगरicand(st1_ptr);
	mul_Xsig_Xsig(&accumulator, &yaccum);

	expon_expon += round_Xsig(&accumulator);

	अगर (accumulator.msw == 0) अणु
		FPU_copy_to_reg1(&CONST_Z, TAG_Zero);
		वापस;
	पूर्ण

	signअगरicand(st1_ptr) = XSIG_LL(accumulator);
	setexponent16(st1_ptr, expon_expon + exponent16(st1_ptr) + 1);

	tag = FPU_round(st1_ptr, 1, 0, FULL_PRECISION, sign ^ st1_sign);
	FPU_settagi(1, tag);

	set_precision_flag_up();	/* 80486 appears to always करो this */

	वापस;

पूर्ण

/*--- poly_l2p1() -----------------------------------------------------------+
 |   Base 2 logarithm by a polynomial approximation.                         |
 |   log2(x+1)                                                               |
 +---------------------------------------------------------------------------*/
पूर्णांक poly_l2p1(u_अक्षर sign0, u_अक्षर sign1,
	      FPU_REG * st0_ptr, FPU_REG * st1_ptr, FPU_REG * dest)
अणु
	u_अक्षर tag;
	दीर्घ पूर्णांक exponent;
	Xsig accumulator, yaccum;

	अगर (exponent16(st0_ptr) < 0) अणु
		log2_kernel(st0_ptr, sign0, &accumulator, &exponent);

		yaccum.lsw = 0;
		XSIG_LL(yaccum) = signअगरicand(st1_ptr);
		mul_Xsig_Xsig(&accumulator, &yaccum);

		exponent += round_Xsig(&accumulator);

		exponent += exponent16(st1_ptr) + 1;
		अगर (exponent < EXP_WAY_UNDER)
			exponent = EXP_WAY_UNDER;

		signअगरicand(dest) = XSIG_LL(accumulator);
		setexponent16(dest, exponent);

		tag = FPU_round(dest, 1, 0, FULL_PRECISION, sign0 ^ sign1);
		FPU_settagi(1, tag);

		अगर (tag == TAG_Valid)
			set_precision_flag_up();	/* 80486 appears to always करो this */
	पूर्ण अन्यथा अणु
		/* The magnitude of st0_ptr is far too large. */

		अगर (sign0 != SIGN_POS) अणु
			/* Trying to get the log of a negative number. */
#अगर_घोषित PECULIAR_486		/* Stupid 80486 करोesn't worry about log(negative). */
			changesign(st1_ptr);
#अन्यथा
			अगर (arith_invalid(1) < 0)
				वापस 1;
#पूर्ण_अगर /* PECULIAR_486 */
		पूर्ण

		/* 80486 appears to करो this */
		अगर (sign0 == SIGN_NEG)
			set_precision_flag_करोwn();
		अन्यथा
			set_precision_flag_up();
	पूर्ण

	अगर (exponent(dest) <= EXP_UNDER)
		EXCEPTION(EX_Underflow);

	वापस 0;

पूर्ण

#अघोषित HIPOWER
#घोषणा	HIPOWER	10
अटल स्थिर अचिन्हित दीर्घ दीर्घ logterms[HIPOWER] = अणु
	0x2a8eca5705fc2ef0LL,
	0xf6384ee1d01febceLL,
	0x093bb62877cdf642LL,
	0x006985d8a9ec439bLL,
	0x0005212c4f55a9c8LL,
	0x00004326a16927f0LL,
	0x0000038d1d80a0e7LL,
	0x0000003141cc80c6LL,
	0x00000002b1668c9fLL,
	0x000000002c7a46aaLL
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ leadterm = 0xb8000000;

/*--- log2_kernel() ---------------------------------------------------------+
 |   Base 2 logarithm by a polynomial approximation.                         |
 |   log2(x+1)                                                               |
 +---------------------------------------------------------------------------*/
अटल व्योम log2_kernel(FPU_REG स्थिर *arg, u_अक्षर argsign, Xsig *accum_result,
			दीर्घ पूर्णांक *expon)
अणु
	दीर्घ पूर्णांक exponent, adj;
	अचिन्हित दीर्घ दीर्घ Xsq;
	Xsig accumulator, Numer, Denom, argSignअगर, arg_signअगर;

	exponent = exponent16(arg);
	Numer.lsw = Denom.lsw = 0;
	XSIG_LL(Numer) = XSIG_LL(Denom) = signअगरicand(arg);
	अगर (argsign == SIGN_POS) अणु
		shr_Xsig(&Denom, 2 - (1 + exponent));
		Denom.msw |= 0x80000000;
		भाग_Xsig(&Numer, &Denom, &argSignअगर);
	पूर्ण अन्यथा अणु
		shr_Xsig(&Denom, 1 - (1 + exponent));
		negate_Xsig(&Denom);
		अगर (Denom.msw & 0x80000000) अणु
			भाग_Xsig(&Numer, &Denom, &argSignअगर);
			exponent++;
		पूर्ण अन्यथा अणु
			/* Denom must be 1.0 */
			argSignअगर.lsw = Numer.lsw;
			argSignअगर.midw = Numer.midw;
			argSignअगर.msw = Numer.msw;
		पूर्ण
	पूर्ण

#अगर_अघोषित PECULIAR_486
	/* Should check here that  |local_arg|  is within the valid range */
	अगर (exponent >= -2) अणु
		अगर ((exponent > -2) || (argSignअगर.msw > (अचिन्हित)0xafb0ccc0)) अणु
			/* The argument is too large */
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* PECULIAR_486 */

	arg_signअगर.lsw = argSignअगर.lsw;
	XSIG_LL(arg_signअगर) = XSIG_LL(argSignअगर);
	adj = norm_Xsig(&argSignअगर);
	accumulator.lsw = argSignअगर.lsw;
	XSIG_LL(accumulator) = XSIG_LL(argSignअगर);
	mul_Xsig_Xsig(&accumulator, &accumulator);
	shr_Xsig(&accumulator, 2 * (-1 - (1 + exponent + adj)));
	Xsq = XSIG_LL(accumulator);
	अगर (accumulator.lsw & 0x80000000)
		Xsq++;

	accumulator.msw = accumulator.midw = accumulator.lsw = 0;
	/* Do the basic fixed poपूर्णांक polynomial evaluation */
	polynomial_Xsig(&accumulator, &Xsq, logterms, HIPOWER - 1);

	mul_Xsig_Xsig(&accumulator, &argSignअगर);
	shr_Xsig(&accumulator, 6 - adj);

	mul32_Xsig(&arg_signअगर, leadterm);
	add_two_Xsig(&accumulator, &arg_signअगर, &exponent);

	*expon = exponent + 1;
	accum_result->lsw = accumulator.lsw;
	accum_result->midw = accumulator.midw;
	accum_result->msw = accumulator.msw;

पूर्ण
