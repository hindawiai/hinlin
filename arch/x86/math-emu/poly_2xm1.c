<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  poly_2xm1.c                                                              |
 |                                                                           |
 | Function to compute 2^x-1 by a polynomial approximation.                  |
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

#घोषणा	HIPOWER	11
अटल स्थिर अचिन्हित दीर्घ दीर्घ lterms[HIPOWER] = अणु
	0x0000000000000000LL,	/* This term करोne separately as 12 bytes */
	0xf5fdeffc162c7543LL,
	0x1c6b08d704a0bfa6LL,
	0x0276556df749cc21LL,
	0x002bb0ffcf14f6b8LL,
	0x0002861225ef751cLL,
	0x00001ffcbfcd5422LL,
	0x00000162c005d5f1LL,
	0x0000000da96ccb1bLL,
	0x0000000078d1b897LL,
	0x000000000422b029LL
पूर्ण;

अटल स्थिर Xsig hiterm = MK_XSIG(0xb17217f7, 0xd1cf79ab, 0xc8a39194);

/* Four slices: 0.0 : 0.25 : 0.50 : 0.75 : 1.0,
   These numbers are 2^(1/4), 2^(1/2), and 2^(3/4)
 */
अटल स्थिर Xsig shअगरtterm0 = MK_XSIG(0, 0, 0);
अटल स्थिर Xsig shअगरtterm1 = MK_XSIG(0x9837f051, 0x8db8a96f, 0x46ad2318);
अटल स्थिर Xsig shअगरtterm2 = MK_XSIG(0xb504f333, 0xf9de6484, 0x597d89b3);
अटल स्थिर Xsig shअगरtterm3 = MK_XSIG(0xd744fcca, 0xd69d6af4, 0x39a68bb9);

अटल स्थिर Xsig *shअगरtterm[] = अणु &shअगरtterm0, &shअगरtterm1,
	&shअगरtterm2, &shअगरtterm3
पूर्ण;

/*--- poly_2xm1() -----------------------------------------------------------+
 | Requires st(0) which is TAG_Valid and < 1.                                |
 +---------------------------------------------------------------------------*/
पूर्णांक poly_2xm1(u_अक्षर sign, FPU_REG *arg, FPU_REG *result)
अणु
	दीर्घ पूर्णांक exponent, shअगरt;
	अचिन्हित दीर्घ दीर्घ Xll;
	Xsig accumulator, Denom, argSignअगर;
	u_अक्षर tag;

	exponent = exponent16(arg);

#अगर_घोषित PARANOID
	अगर (exponent >= 0) अणु	/* Don't want a |number| >= 1.0 */
		/* Number negative, too large, or not Valid. */
		EXCEPTION(EX_INTERNAL | 0x127);
		वापस 1;
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	argSignअगर.lsw = 0;
	XSIG_LL(argSignअगर) = Xll = signअगरicand(arg);

	अगर (exponent == -1) अणु
		shअगरt = (argSignअगर.msw & 0x40000000) ? 3 : 2;
		/* subtract 0.5 or 0.75 */
		exponent -= 2;
		XSIG_LL(argSignअगर) <<= 2;
		Xll <<= 2;
	पूर्ण अन्यथा अगर (exponent == -2) अणु
		shअगरt = 1;
		/* subtract 0.25 */
		exponent--;
		XSIG_LL(argSignअगर) <<= 1;
		Xll <<= 1;
	पूर्ण अन्यथा
		shअगरt = 0;

	अगर (exponent < -2) अणु
		/* Shअगरt the argument right by the required places. */
		अगर (FPU_shrx(&Xll, -2 - exponent) >= 0x80000000U)
			Xll++;	/* round up */
	पूर्ण

	accumulator.lsw = accumulator.midw = accumulator.msw = 0;
	polynomial_Xsig(&accumulator, &Xll, lterms, HIPOWER - 1);
	mul_Xsig_Xsig(&accumulator, &argSignअगर);
	shr_Xsig(&accumulator, 3);

	mul_Xsig_Xsig(&argSignअगर, &hiterm);	/* The leading term */
	add_two_Xsig(&accumulator, &argSignअगर, &exponent);

	अगर (shअगरt) अणु
		/* The argument is large, use the identity:
		   f(x+a) = f(a) * (f(x) + 1) - 1;
		 */
		shr_Xsig(&accumulator, -exponent);
		accumulator.msw |= 0x80000000;	/* add 1.0 */
		mul_Xsig_Xsig(&accumulator, shअगरtterm[shअगरt]);
		accumulator.msw &= 0x3fffffff;	/* subtract 1.0 */
		exponent = 1;
	पूर्ण

	अगर (sign != SIGN_POS) अणु
		/* The argument is negative, use the identity:
		   f(-x) = -f(x) / (1 + f(x))
		 */
		Denom.lsw = accumulator.lsw;
		XSIG_LL(Denom) = XSIG_LL(accumulator);
		अगर (exponent < 0)
			shr_Xsig(&Denom, -exponent);
		अन्यथा अगर (exponent > 0) अणु
			/* exponent must be 1 here */
			XSIG_LL(Denom) <<= 1;
			अगर (Denom.lsw & 0x80000000)
				XSIG_LL(Denom) |= 1;
			(Denom.lsw) <<= 1;
		पूर्ण
		Denom.msw |= 0x80000000;	/* add 1.0 */
		भाग_Xsig(&accumulator, &Denom, &accumulator);
	पूर्ण

	/* Convert to 64 bit चिन्हित-compatible */
	exponent += round_Xsig(&accumulator);

	result = &st(0);
	signअगरicand(result) = XSIG_LL(accumulator);
	setexponent16(result, exponent);

	tag = FPU_round(result, 1, 0, FULL_PRECISION, sign);

	setsign(result, sign);
	FPU_settag0(tag);

	वापस 0;

पूर्ण
