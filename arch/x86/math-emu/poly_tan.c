<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  poly_tan.c                                                               |
 |                                                                           |
 | Compute the tan of a FPU_REG, using a polynomial approximation.           |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997,1999                                    |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@melbpc.org.au            |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "fpu_emu.h"
#समावेश "fpu_system.h"
#समावेश "control_w.h"
#समावेश "poly.h"

#घोषणा	HiPOWERop	3	/* odd poly, positive terms */
अटल स्थिर अचिन्हित दीर्घ दीर्घ oddplterm[HiPOWERop] = अणु
	0x0000000000000000LL,
	0x0051a1cf08fca228LL,
	0x0000000071284ff7LL
पूर्ण;

#घोषणा	HiPOWERon	2	/* odd poly, negative terms */
अटल स्थिर अचिन्हित दीर्घ दीर्घ oddnegterm[HiPOWERon] = अणु
	0x1291a9a184244e80LL,
	0x0000583245819c21LL
पूर्ण;

#घोषणा	HiPOWERep	2	/* even poly, positive terms */
अटल स्थिर अचिन्हित दीर्घ दीर्घ evenplterm[HiPOWERep] = अणु
	0x0e848884b539e888LL,
	0x00003c7f18b887daLL
पूर्ण;

#घोषणा	HiPOWERen	2	/* even poly, negative terms */
अटल स्थिर अचिन्हित दीर्घ दीर्घ evennegterm[HiPOWERen] = अणु
	0xf1f0200fd51569ccLL,
	0x003afb46105c4432LL
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ दीर्घ twothirds = 0xaaaaaaaaaaaaaaabLL;

/*--- poly_tan() ------------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
व्योम poly_tan(FPU_REG *st0_ptr)
अणु
	दीर्घ पूर्णांक exponent;
	पूर्णांक invert;
	Xsig argSq, argSqSq, accumulatoro, accumulatore, accum,
	    argSignअगर, fix_up;
	अचिन्हित दीर्घ adj;

	exponent = exponent(st0_ptr);

#अगर_घोषित PARANOID
	अगर (signnegative(st0_ptr)) अणु	/* Can't hack a number < 0.0 */
		arith_invalid(0);
		वापस;
	पूर्ण			/* Need a positive number */
#पूर्ण_अगर /* PARANOID */

	/* Split the problem पूर्णांकo two करोमुख्यs, smaller and larger than pi/4 */
	अगर ((exponent == 0)
	    || ((exponent == -1) && (st0_ptr->sigh > 0xc90fdaa2))) अणु
		/* The argument is greater than (approx) pi/4 */
		invert = 1;
		accum.lsw = 0;
		XSIG_LL(accum) = signअगरicand(st0_ptr);

		अगर (exponent == 0) अणु
			/* The argument is >= 1.0 */
			/* Put the binary poपूर्णांक at the left. */
			XSIG_LL(accum) <<= 1;
		पूर्ण
		/* pi/2 in hex is: 1.921fb54442d18469 898CC51701B839A2 52049C1 */
		XSIG_LL(accum) = 0x921fb54442d18469LL - XSIG_LL(accum);
		/* This is a special हाल which arises due to rounding. */
		अगर (XSIG_LL(accum) == 0xffffffffffffffffLL) अणु
			FPU_settag0(TAG_Valid);
			signअगरicand(st0_ptr) = 0x8a51e04daabda360LL;
			setexponent16(st0_ptr,
				      (0x41 + EXTENDED_Ebias) | SIGN_Negative);
			वापस;
		पूर्ण

		argSignअगर.lsw = accum.lsw;
		XSIG_LL(argSignअगर) = XSIG_LL(accum);
		exponent = -1 + norm_Xsig(&argSignअगर);
	पूर्ण अन्यथा अणु
		invert = 0;
		argSignअगर.lsw = 0;
		XSIG_LL(accum) = XSIG_LL(argSignअगर) = signअगरicand(st0_ptr);

		अगर (exponent < -1) अणु
			/* shअगरt the argument right by the required places */
			अगर (FPU_shrx(&XSIG_LL(accum), -1 - exponent) >=
			    0x80000000U)
				XSIG_LL(accum)++;	/* round up */
		पूर्ण
	पूर्ण

	XSIG_LL(argSq) = XSIG_LL(accum);
	argSq.lsw = accum.lsw;
	mul_Xsig_Xsig(&argSq, &argSq);
	XSIG_LL(argSqSq) = XSIG_LL(argSq);
	argSqSq.lsw = argSq.lsw;
	mul_Xsig_Xsig(&argSqSq, &argSqSq);

	/* Compute the negative terms क्रम the numerator polynomial */
	accumulatoro.msw = accumulatoro.midw = accumulatoro.lsw = 0;
	polynomial_Xsig(&accumulatoro, &XSIG_LL(argSqSq), oddnegterm,
			HiPOWERon - 1);
	mul_Xsig_Xsig(&accumulatoro, &argSq);
	negate_Xsig(&accumulatoro);
	/* Add the positive terms */
	polynomial_Xsig(&accumulatoro, &XSIG_LL(argSqSq), oddplterm,
			HiPOWERop - 1);

	/* Compute the positive terms क्रम the denominator polynomial */
	accumulatore.msw = accumulatore.midw = accumulatore.lsw = 0;
	polynomial_Xsig(&accumulatore, &XSIG_LL(argSqSq), evenplterm,
			HiPOWERep - 1);
	mul_Xsig_Xsig(&accumulatore, &argSq);
	negate_Xsig(&accumulatore);
	/* Add the negative terms */
	polynomial_Xsig(&accumulatore, &XSIG_LL(argSqSq), evennegterm,
			HiPOWERen - 1);
	/* Multiply by arg^2 */
	mul64_Xsig(&accumulatore, &XSIG_LL(argSignअगर));
	mul64_Xsig(&accumulatore, &XSIG_LL(argSignअगर));
	/* de-normalize and भागide by 2 */
	shr_Xsig(&accumulatore, -2 * (1 + exponent) + 1);
	negate_Xsig(&accumulatore);	/* This करोes 1 - accumulator */

	/* Now find the ratio. */
	अगर (accumulatore.msw == 0) अणु
		/* accumulatoro must contain 1.0 here, (actually, 0) but it
		   really करोesn't matter what value we use because it will
		   have negligible effect in later calculations
		 */
		XSIG_LL(accum) = 0x8000000000000000LL;
		accum.lsw = 0;
	पूर्ण अन्यथा अणु
		भाग_Xsig(&accumulatoro, &accumulatore, &accum);
	पूर्ण

	/* Multiply by 1/3 * arg^3 */
	mul64_Xsig(&accum, &XSIG_LL(argSignअगर));
	mul64_Xsig(&accum, &XSIG_LL(argSignअगर));
	mul64_Xsig(&accum, &XSIG_LL(argSignअगर));
	mul64_Xsig(&accum, &twothirds);
	shr_Xsig(&accum, -2 * (exponent + 1));

	/* tan(arg) = arg + accum */
	add_two_Xsig(&accum, &argSignअगर, &exponent);

	अगर (invert) अणु
		/* We now have the value of tan(pi_2 - arg) where pi_2 is an
		   approximation क्रम pi/2
		 */
		/* The next step is to fix the answer to compensate क्रम the
		   error due to the approximation used क्रम pi/2
		 */

		/* This is (approx) delta, the error in our approx क्रम pi/2
		   (see above). It has an exponent of -65
		 */
		XSIG_LL(fix_up) = 0x898cc51701b839a2LL;
		fix_up.lsw = 0;

		अगर (exponent == 0)
			adj = 0xffffffff;	/* We want approx 1.0 here, but
						   this is बंद enough. */
		अन्यथा अगर (exponent > -30) अणु
			adj = accum.msw >> -(exponent + 1);	/* tan */
			adj = mul_32_32(adj, adj);	/* tan^2 */
		पूर्ण अन्यथा
			adj = 0;
		adj = mul_32_32(0x898cc517, adj);	/* delta * tan^2 */

		fix_up.msw += adj;
		अगर (!(fix_up.msw & 0x80000000)) अणु	/* did fix_up overflow ? */
			/* Yes, we need to add an msb */
			shr_Xsig(&fix_up, 1);
			fix_up.msw |= 0x80000000;
			shr_Xsig(&fix_up, 64 + exponent);
		पूर्ण अन्यथा
			shr_Xsig(&fix_up, 65 + exponent);

		add_two_Xsig(&accum, &fix_up, &exponent);

		/* accum now contains tan(pi/2 - arg).
		   Use tan(arg) = 1.0 / tan(pi/2 - arg)
		 */
		accumulatoro.lsw = accumulatoro.midw = 0;
		accumulatoro.msw = 0x80000000;
		भाग_Xsig(&accumulatoro, &accum, &accum);
		exponent = -exponent - 1;
	पूर्ण

	/* Transfer the result */
	round_Xsig(&accum);
	FPU_settag0(TAG_Valid);
	signअगरicand(st0_ptr) = XSIG_LL(accum);
	setexponent16(st0_ptr, exponent + EXTENDED_Ebias);	/* Result is positive. */

पूर्ण
