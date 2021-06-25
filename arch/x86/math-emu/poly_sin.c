<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  poly_sin.c                                                               |
 |                                                                           |
 |  Computation of an approximation of the sin function and the cosine       |
 |  function by a polynomial.                                                |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997,1999                                    |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@melbpc.org.au                             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "fpu_emu.h"
#समावेश "fpu_system.h"
#समावेश "control_w.h"
#समावेश "poly.h"

#घोषणा	N_COEFF_P	4
#घोषणा	N_COEFF_N	4

अटल स्थिर अचिन्हित दीर्घ दीर्घ pos_terms_l[N_COEFF_P] = अणु
	0xaaaaaaaaaaaaaaabLL,
	0x00d00d00d00cf906LL,
	0x000006b99159a8bbLL,
	0x000000000d7392e6LL
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ दीर्घ neg_terms_l[N_COEFF_N] = अणु
	0x2222222222222167LL,
	0x0002e3bc74aab624LL,
	0x0000000b09229062LL,
	0x00000000000c7973LL
पूर्ण;

#घोषणा	N_COEFF_PH	4
#घोषणा	N_COEFF_NH	4
अटल स्थिर अचिन्हित दीर्घ दीर्घ pos_terms_h[N_COEFF_PH] = अणु
	0x0000000000000000LL,
	0x05b05b05b05b0406LL,
	0x000049f93edd91a9LL,
	0x00000000c9c9ed62LL
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ दीर्घ neg_terms_h[N_COEFF_NH] = अणु
	0xaaaaaaaaaaaaaa98LL,
	0x001a01a01a019064LL,
	0x0000008f76c68a77LL,
	0x0000000000d58f5eLL
पूर्ण;

/*--- poly_sine() -----------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
व्योम poly_sine(FPU_REG *st0_ptr)
अणु
	पूर्णांक exponent, echange;
	Xsig accumulator, argSqrd, argTo4;
	अचिन्हित दीर्घ fix_up, adj;
	अचिन्हित दीर्घ दीर्घ fixed_arg;
	FPU_REG result;

	exponent = exponent(st0_ptr);

	accumulator.lsw = accumulator.midw = accumulator.msw = 0;

	/* Split पूर्णांकo two ranges, क्रम arguments below and above 1.0 */
	/* The boundary between upper and lower is approx 0.88309101259 */
	अगर ((exponent < -1)
	    || ((exponent == -1) && (st0_ptr->sigh <= 0xe21240aa))) अणु
		/* The argument is <= 0.88309101259 */

		argSqrd.msw = st0_ptr->sigh;
		argSqrd.midw = st0_ptr->sigl;
		argSqrd.lsw = 0;
		mul64_Xsig(&argSqrd, &signअगरicand(st0_ptr));
		shr_Xsig(&argSqrd, 2 * (-1 - exponent));
		argTo4.msw = argSqrd.msw;
		argTo4.midw = argSqrd.midw;
		argTo4.lsw = argSqrd.lsw;
		mul_Xsig_Xsig(&argTo4, &argTo4);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), neg_terms_l,
				N_COEFF_N - 1);
		mul_Xsig_Xsig(&accumulator, &argSqrd);
		negate_Xsig(&accumulator);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), pos_terms_l,
				N_COEFF_P - 1);

		shr_Xsig(&accumulator, 2);	/* Divide by four */
		accumulator.msw |= 0x80000000;	/* Add 1.0 */

		mul64_Xsig(&accumulator, &signअगरicand(st0_ptr));
		mul64_Xsig(&accumulator, &signअगरicand(st0_ptr));
		mul64_Xsig(&accumulator, &signअगरicand(st0_ptr));

		/* Divide by four, FPU_REG compatible, etc */
		exponent = 3 * exponent;

		/* The minimum exponent dअगरference is 3 */
		shr_Xsig(&accumulator, exponent(st0_ptr) - exponent);

		negate_Xsig(&accumulator);
		XSIG_LL(accumulator) += signअगरicand(st0_ptr);

		echange = round_Xsig(&accumulator);

		setexponentpos(&result, exponent(st0_ptr) + echange);
	पूर्ण अन्यथा अणु
		/* The argument is > 0.88309101259 */
		/* We use sin(st(0)) = cos(pi/2-st(0)) */

		fixed_arg = signअगरicand(st0_ptr);

		अगर (exponent == 0) अणु
			/* The argument is >= 1.0 */

			/* Put the binary poपूर्णांक at the left. */
			fixed_arg <<= 1;
		पूर्ण
		/* pi/2 in hex is: 1.921fb54442d18469 898CC51701B839A2 52049C1 */
		fixed_arg = 0x921fb54442d18469LL - fixed_arg;
		/* There is a special हाल which arises due to rounding, to fix here. */
		अगर (fixed_arg == 0xffffffffffffffffLL)
			fixed_arg = 0;

		XSIG_LL(argSqrd) = fixed_arg;
		argSqrd.lsw = 0;
		mul64_Xsig(&argSqrd, &fixed_arg);

		XSIG_LL(argTo4) = XSIG_LL(argSqrd);
		argTo4.lsw = argSqrd.lsw;
		mul_Xsig_Xsig(&argTo4, &argTo4);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), neg_terms_h,
				N_COEFF_NH - 1);
		mul_Xsig_Xsig(&accumulator, &argSqrd);
		negate_Xsig(&accumulator);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), pos_terms_h,
				N_COEFF_PH - 1);
		negate_Xsig(&accumulator);

		mul64_Xsig(&accumulator, &fixed_arg);
		mul64_Xsig(&accumulator, &fixed_arg);

		shr_Xsig(&accumulator, 3);
		negate_Xsig(&accumulator);

		add_Xsig_Xsig(&accumulator, &argSqrd);

		shr_Xsig(&accumulator, 1);

		accumulator.lsw |= 1;	/* A zero accumulator here would cause problems */
		negate_Xsig(&accumulator);

		/* The basic computation is complete. Now fix the answer to
		   compensate क्रम the error due to the approximation used क्रम
		   pi/2
		 */

		/* This has an exponent of -65 */
		fix_up = 0x898cc517;
		/* The fix-up needs to be improved क्रम larger args */
		अगर (argSqrd.msw & 0xffc00000) अणु
			/* Get about 32 bit precision in these: */
			fix_up -= mul_32_32(0x898cc517, argSqrd.msw) / 6;
		पूर्ण
		fix_up = mul_32_32(fix_up, LL_MSW(fixed_arg));

		adj = accumulator.lsw;	/* temp save */
		accumulator.lsw -= fix_up;
		अगर (accumulator.lsw > adj)
			XSIG_LL(accumulator)--;

		echange = round_Xsig(&accumulator);

		setexponentpos(&result, echange - 1);
	पूर्ण

	signअगरicand(&result) = XSIG_LL(accumulator);
	setsign(&result, माला_लोign(st0_ptr));
	FPU_copy_to_reg0(&result, TAG_Valid);

#अगर_घोषित PARANOID
	अगर ((exponent(&result) >= 0)
	    && (signअगरicand(&result) > 0x8000000000000000LL)) अणु
		EXCEPTION(EX_INTERNAL | 0x150);
	पूर्ण
#पूर्ण_अगर /* PARANOID */

पूर्ण

/*--- poly_cos() ------------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
व्योम poly_cos(FPU_REG *st0_ptr)
अणु
	FPU_REG result;
	दीर्घ पूर्णांक exponent, exp2, echange;
	Xsig accumulator, argSqrd, fix_up, argTo4;
	अचिन्हित दीर्घ दीर्घ fixed_arg;

#अगर_घोषित PARANOID
	अगर ((exponent(st0_ptr) > 0)
	    || ((exponent(st0_ptr) == 0)
		&& (signअगरicand(st0_ptr) > 0xc90fdaa22168c234LL))) अणु
		EXCEPTION(EX_Invalid);
		FPU_copy_to_reg0(&CONST_QNaN, TAG_Special);
		वापस;
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	exponent = exponent(st0_ptr);

	accumulator.lsw = accumulator.midw = accumulator.msw = 0;

	अगर ((exponent < -1)
	    || ((exponent == -1) && (st0_ptr->sigh <= 0xb00d6f54))) अणु
		/* arg is < 0.687705 */

		argSqrd.msw = st0_ptr->sigh;
		argSqrd.midw = st0_ptr->sigl;
		argSqrd.lsw = 0;
		mul64_Xsig(&argSqrd, &signअगरicand(st0_ptr));

		अगर (exponent < -1) अणु
			/* shअगरt the argument right by the required places */
			shr_Xsig(&argSqrd, 2 * (-1 - exponent));
		पूर्ण

		argTo4.msw = argSqrd.msw;
		argTo4.midw = argSqrd.midw;
		argTo4.lsw = argSqrd.lsw;
		mul_Xsig_Xsig(&argTo4, &argTo4);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), neg_terms_h,
				N_COEFF_NH - 1);
		mul_Xsig_Xsig(&accumulator, &argSqrd);
		negate_Xsig(&accumulator);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), pos_terms_h,
				N_COEFF_PH - 1);
		negate_Xsig(&accumulator);

		mul64_Xsig(&accumulator, &signअगरicand(st0_ptr));
		mul64_Xsig(&accumulator, &signअगरicand(st0_ptr));
		shr_Xsig(&accumulator, -2 * (1 + exponent));

		shr_Xsig(&accumulator, 3);
		negate_Xsig(&accumulator);

		add_Xsig_Xsig(&accumulator, &argSqrd);

		shr_Xsig(&accumulator, 1);

		/* It करोesn't matter अगर accumulator is all zero here, the
		   following code will work ok */
		negate_Xsig(&accumulator);

		अगर (accumulator.lsw & 0x80000000)
			XSIG_LL(accumulator)++;
		अगर (accumulator.msw == 0) अणु
			/* The result is 1.0 */
			FPU_copy_to_reg0(&CONST_1, TAG_Valid);
			वापस;
		पूर्ण अन्यथा अणु
			signअगरicand(&result) = XSIG_LL(accumulator);

			/* will be a valid positive nr with expon = -1 */
			setexponentpos(&result, -1);
		पूर्ण
	पूर्ण अन्यथा अणु
		fixed_arg = signअगरicand(st0_ptr);

		अगर (exponent == 0) अणु
			/* The argument is >= 1.0 */

			/* Put the binary poपूर्णांक at the left. */
			fixed_arg <<= 1;
		पूर्ण
		/* pi/2 in hex is: 1.921fb54442d18469 898CC51701B839A2 52049C1 */
		fixed_arg = 0x921fb54442d18469LL - fixed_arg;
		/* There is a special हाल which arises due to rounding, to fix here. */
		अगर (fixed_arg == 0xffffffffffffffffLL)
			fixed_arg = 0;

		exponent = -1;
		exp2 = -1;

		/* A shअगरt is needed here only क्रम a narrow range of arguments,
		   i.e. क्रम fixed_arg approx 2^-32, but we pick up more... */
		अगर (!(LL_MSW(fixed_arg) & 0xffff0000)) अणु
			fixed_arg <<= 16;
			exponent -= 16;
			exp2 -= 16;
		पूर्ण

		XSIG_LL(argSqrd) = fixed_arg;
		argSqrd.lsw = 0;
		mul64_Xsig(&argSqrd, &fixed_arg);

		अगर (exponent < -1) अणु
			/* shअगरt the argument right by the required places */
			shr_Xsig(&argSqrd, 2 * (-1 - exponent));
		पूर्ण

		argTo4.msw = argSqrd.msw;
		argTo4.midw = argSqrd.midw;
		argTo4.lsw = argSqrd.lsw;
		mul_Xsig_Xsig(&argTo4, &argTo4);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), neg_terms_l,
				N_COEFF_N - 1);
		mul_Xsig_Xsig(&accumulator, &argSqrd);
		negate_Xsig(&accumulator);

		polynomial_Xsig(&accumulator, &XSIG_LL(argTo4), pos_terms_l,
				N_COEFF_P - 1);

		shr_Xsig(&accumulator, 2);	/* Divide by four */
		accumulator.msw |= 0x80000000;	/* Add 1.0 */

		mul64_Xsig(&accumulator, &fixed_arg);
		mul64_Xsig(&accumulator, &fixed_arg);
		mul64_Xsig(&accumulator, &fixed_arg);

		/* Divide by four, FPU_REG compatible, etc */
		exponent = 3 * exponent;

		/* The minimum exponent dअगरference is 3 */
		shr_Xsig(&accumulator, exp2 - exponent);

		negate_Xsig(&accumulator);
		XSIG_LL(accumulator) += fixed_arg;

		/* The basic computation is complete. Now fix the answer to
		   compensate क्रम the error due to the approximation used क्रम
		   pi/2
		 */

		/* This has an exponent of -65 */
		XSIG_LL(fix_up) = 0x898cc51701b839a2ll;
		fix_up.lsw = 0;

		/* The fix-up needs to be improved क्रम larger args */
		अगर (argSqrd.msw & 0xffc00000) अणु
			/* Get about 32 bit precision in these: */
			fix_up.msw -= mul_32_32(0x898cc517, argSqrd.msw) / 2;
			fix_up.msw += mul_32_32(0x898cc517, argTo4.msw) / 24;
		पूर्ण

		exp2 += norm_Xsig(&accumulator);
		shr_Xsig(&accumulator, 1);	/* Prevent overflow */
		exp2++;
		shr_Xsig(&fix_up, 65 + exp2);

		add_Xsig_Xsig(&accumulator, &fix_up);

		echange = round_Xsig(&accumulator);

		setexponentpos(&result, exp2 + echange);
		signअगरicand(&result) = XSIG_LL(accumulator);
	पूर्ण

	FPU_copy_to_reg0(&result, TAG_Valid);

#अगर_घोषित PARANOID
	अगर ((exponent(&result) >= 0)
	    && (signअगरicand(&result) > 0x8000000000000000LL)) अणु
		EXCEPTION(EX_INTERNAL | 0x151);
	पूर्ण
#पूर्ण_अगर /* PARANOID */

पूर्ण
