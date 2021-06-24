<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  poly_atan.c                                                              |
 |                                                                           |
 | Compute the arctan of a FPU_REG, using a polynomial approximation.        |
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
#समावेश "status_w.h"
#समावेश "control_w.h"
#समावेश "poly.h"

#घोषणा	HIPOWERon	6	/* odd poly, negative terms */
अटल स्थिर अचिन्हित दीर्घ दीर्घ oddnegterms[HIPOWERon] = अणु
	0x0000000000000000LL,	/* Dummy (not क्रम - 1.0) */
	0x015328437f756467LL,
	0x0005dda27b73dec6LL,
	0x0000226bf2bfb91aLL,
	0x000000ccc439c5f7LL,
	0x0000000355438407LL
पूर्ण;

#घोषणा	HIPOWERop	6	/* odd poly, positive terms */
अटल स्थिर अचिन्हित दीर्घ दीर्घ oddplterms[HIPOWERop] = अणु
/*  0xaaaaaaaaaaaaaaabLL,  transferred to fixedpterm[] */
	0x0db55a71875c9ac2LL,
	0x0029fce2d67880b0LL,
	0x0000dfd3908b4596LL,
	0x00000550fd61dab4LL,
	0x0000001c9422b3f9LL,
	0x000000003e3301e1LL
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ दीर्घ denomterm = 0xebd9b842c5c53a0eLL;

अटल स्थिर Xsig fixedpterm = MK_XSIG(0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa);

अटल स्थिर Xsig pi_signअगर = MK_XSIG(0xc90fdaa2, 0x2168c234, 0xc4c6628b);

/*--- poly_atan() -----------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
व्योम poly_atan(FPU_REG *st0_ptr, u_अक्षर st0_tag,
	       FPU_REG *st1_ptr, u_अक्षर st1_tag)
अणु
	u_अक्षर transक्रमmed, inverted, sign1, sign2;
	पूर्णांक exponent;
	दीर्घ पूर्णांक dummy_exp;
	Xsig accumulator, Numer, Denom, accumulatore, argSignअगर, argSq, argSqSq;
	u_अक्षर tag;

	sign1 = माला_लोign(st0_ptr);
	sign2 = माला_लोign(st1_ptr);
	अगर (st0_tag == TAG_Valid) अणु
		exponent = exponent(st0_ptr);
	पूर्ण अन्यथा अणु
		/* This gives non-compatible stack contents... */
		FPU_to_exp16(st0_ptr, st0_ptr);
		exponent = exponent16(st0_ptr);
	पूर्ण
	अगर (st1_tag == TAG_Valid) अणु
		exponent -= exponent(st1_ptr);
	पूर्ण अन्यथा अणु
		/* This gives non-compatible stack contents... */
		FPU_to_exp16(st1_ptr, st1_ptr);
		exponent -= exponent16(st1_ptr);
	पूर्ण

	अगर ((exponent < 0) || ((exponent == 0) &&
			       ((st0_ptr->sigh < st1_ptr->sigh) ||
				((st0_ptr->sigh == st1_ptr->sigh) &&
				 (st0_ptr->sigl < st1_ptr->sigl))))) अणु
		inverted = 1;
		Numer.lsw = Denom.lsw = 0;
		XSIG_LL(Numer) = signअगरicand(st0_ptr);
		XSIG_LL(Denom) = signअगरicand(st1_ptr);
	पूर्ण अन्यथा अणु
		inverted = 0;
		exponent = -exponent;
		Numer.lsw = Denom.lsw = 0;
		XSIG_LL(Numer) = signअगरicand(st1_ptr);
		XSIG_LL(Denom) = signअगरicand(st0_ptr);
	पूर्ण
	भाग_Xsig(&Numer, &Denom, &argSignअगर);
	exponent += norm_Xsig(&argSignअगर);

	अगर ((exponent >= -1)
	    || ((exponent == -2) && (argSignअगर.msw > 0xd413ccd0))) अणु
		/* The argument is greater than वर्ग_मूल(2)-1 (=0.414213562...) */
		/* Convert the argument by an identity क्रम atan */
		transक्रमmed = 1;

		अगर (exponent >= 0) अणु
#अगर_घोषित PARANOID
			अगर (!((exponent == 0) &&
			      (argSignअगर.lsw == 0) && (argSignअगर.midw == 0) &&
			      (argSignअगर.msw == 0x80000000))) अणु
				EXCEPTION(EX_INTERNAL | 0x104);	/* There must be a logic error */
				वापस;
			पूर्ण
#पूर्ण_अगर /* PARANOID */
			argSignअगर.msw = 0;	/* Make the transक्रमmed arg -> 0.0 */
		पूर्ण अन्यथा अणु
			Numer.lsw = Denom.lsw = argSignअगर.lsw;
			XSIG_LL(Numer) = XSIG_LL(Denom) = XSIG_LL(argSignअगर);

			अगर (exponent < -1)
				shr_Xsig(&Numer, -1 - exponent);
			negate_Xsig(&Numer);

			shr_Xsig(&Denom, -exponent);
			Denom.msw |= 0x80000000;

			भाग_Xsig(&Numer, &Denom, &argSignअगर);

			exponent = -1 + norm_Xsig(&argSignअगर);
		पूर्ण
	पूर्ण अन्यथा अणु
		transक्रमmed = 0;
	पूर्ण

	argSq.lsw = argSignअगर.lsw;
	argSq.midw = argSignअगर.midw;
	argSq.msw = argSignअगर.msw;
	mul_Xsig_Xsig(&argSq, &argSq);

	argSqSq.lsw = argSq.lsw;
	argSqSq.midw = argSq.midw;
	argSqSq.msw = argSq.msw;
	mul_Xsig_Xsig(&argSqSq, &argSqSq);

	accumulatore.lsw = argSq.lsw;
	XSIG_LL(accumulatore) = XSIG_LL(argSq);

	shr_Xsig(&argSq, 2 * (-1 - exponent - 1));
	shr_Xsig(&argSqSq, 4 * (-1 - exponent - 1));

	/* Now have argSq etc with binary poपूर्णांक at the left
	   .1xxxxxxxx */

	/* Do the basic fixed poपूर्णांक polynomial evaluation */
	accumulator.msw = accumulator.midw = accumulator.lsw = 0;
	polynomial_Xsig(&accumulator, &XSIG_LL(argSqSq),
			oddplterms, HIPOWERop - 1);
	mul64_Xsig(&accumulator, &XSIG_LL(argSq));
	negate_Xsig(&accumulator);
	polynomial_Xsig(&accumulator, &XSIG_LL(argSqSq), oddnegterms,
			HIPOWERon - 1);
	negate_Xsig(&accumulator);
	add_two_Xsig(&accumulator, &fixedpterm, &dummy_exp);

	mul64_Xsig(&accumulatore, &denomterm);
	shr_Xsig(&accumulatore, 1 + 2 * (-1 - exponent));
	accumulatore.msw |= 0x80000000;

	भाग_Xsig(&accumulator, &accumulatore, &accumulator);

	mul_Xsig_Xsig(&accumulator, &argSignअगर);
	mul_Xsig_Xsig(&accumulator, &argSq);

	shr_Xsig(&accumulator, 3);
	negate_Xsig(&accumulator);
	add_Xsig_Xsig(&accumulator, &argSignअगर);

	अगर (transक्रमmed) अणु
		/* compute pi/4 - accumulator */
		shr_Xsig(&accumulator, -1 - exponent);
		negate_Xsig(&accumulator);
		add_Xsig_Xsig(&accumulator, &pi_signअगर);
		exponent = -1;
	पूर्ण

	अगर (inverted) अणु
		/* compute pi/2 - accumulator */
		shr_Xsig(&accumulator, -exponent);
		negate_Xsig(&accumulator);
		add_Xsig_Xsig(&accumulator, &pi_signअगर);
		exponent = 0;
	पूर्ण

	अगर (sign1) अणु
		/* compute pi - accumulator */
		shr_Xsig(&accumulator, 1 - exponent);
		negate_Xsig(&accumulator);
		add_Xsig_Xsig(&accumulator, &pi_signअगर);
		exponent = 1;
	पूर्ण

	exponent += round_Xsig(&accumulator);

	signअगरicand(st1_ptr) = XSIG_LL(accumulator);
	setexponent16(st1_ptr, exponent);

	tag = FPU_round(st1_ptr, 1, 0, FULL_PRECISION, sign2);
	FPU_settagi(1, tag);

	set_precision_flag_up();	/* We करो not really know अगर up or करोwn,
					   use this as the शेष. */

पूर्ण
