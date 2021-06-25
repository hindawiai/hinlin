<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_add_sub.c                                                            |
 |                                                                           |
 | Functions to add or subtract two रेजिस्टरs and put the result in a third. |
 |                                                                           |
 | Copyright (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 |  For each function, the destination may be any FPU_REG, including one of  |
 | the source FPU_REGs.                                                      |
 |  Each function वापसs 0 अगर the answer is o.k., otherwise a non-zero      |
 | value is वापसed, indicating either an exception condition or an         |
 | पूर्णांकernal error.                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "fpu_emu.h"
#समावेश "control_w.h"
#समावेश "fpu_system.h"

अटल
पूर्णांक add_sub_specials(FPU_REG स्थिर *a, u_अक्षर taga, u_अक्षर signa,
		     FPU_REG स्थिर *b, u_अक्षर tagb, u_अक्षर signb,
		     FPU_REG * dest, पूर्णांक deststnr, पूर्णांक control_w);

/*
  Operates on st(0) and st(n), or on st(0) and temporary data.
  The destination must be one of the source st(x).
  */
पूर्णांक FPU_add(FPU_REG स्थिर *b, u_अक्षर tagb, पूर्णांक deststnr, पूर्णांक control_w)
अणु
	FPU_REG *a = &st(0);
	FPU_REG *dest = &st(deststnr);
	u_अक्षर signb = माला_लोign(b);
	u_अक्षर taga = FPU_gettag0();
	u_अक्षर signa = माला_लोign(a);
	u_अक्षर saved_sign = माला_लोign(dest);
	पूर्णांक dअगरf, tag, expa, expb;

	अगर (!(taga | tagb)) अणु
		expa = exponent(a);
		expb = exponent(b);

	      valid_add:
		/* Both रेजिस्टरs are valid */
		अगर (!(signa ^ signb)) अणु
			/* signs are the same */
			tag =
			    FPU_u_add(a, b, dest, control_w, signa, expa, expb);
		पूर्ण अन्यथा अणु
			/* The signs are dअगरferent, so करो a subtraction */
			dअगरf = expa - expb;
			अगर (!dअगरf) अणु
				dअगरf = a->sigh - b->sigh;	/* This works only अगर the ms bits
								   are identical. */
				अगर (!dअगरf) अणु
					dअगरf = a->sigl > b->sigl;
					अगर (!dअगरf)
						dअगरf = -(a->sigl < b->sigl);
				पूर्ण
			पूर्ण

			अगर (dअगरf > 0) अणु
				tag =
				    FPU_u_sub(a, b, dest, control_w, signa,
					      expa, expb);
			पूर्ण अन्यथा अगर (dअगरf < 0) अणु
				tag =
				    FPU_u_sub(b, a, dest, control_w, signb,
					      expb, expa);
			पूर्ण अन्यथा अणु
				FPU_copy_to_regi(&CONST_Z, TAG_Zero, deststnr);
				/* sign depends upon rounding mode */
				setsign(dest, ((control_w & CW_RC) != RC_DOWN)
					? SIGN_POS : SIGN_NEG);
				वापस TAG_Zero;
			पूर्ण
		पूर्ण

		अगर (tag < 0) अणु
			setsign(dest, saved_sign);
			वापस tag;
		पूर्ण
		FPU_settagi(deststnr, tag);
		वापस tag;
	पूर्ण

	अगर (taga == TAG_Special)
		taga = FPU_Special(a);
	अगर (tagb == TAG_Special)
		tagb = FPU_Special(b);

	अगर (((taga == TAG_Valid) && (tagb == TW_Denormal))
	    || ((taga == TW_Denormal) && (tagb == TAG_Valid))
	    || ((taga == TW_Denormal) && (tagb == TW_Denormal))) अणु
		FPU_REG x, y;

		अगर (denormal_opeअक्रम() < 0)
			वापस FPU_Exception;

		FPU_to_exp16(a, &x);
		FPU_to_exp16(b, &y);
		a = &x;
		b = &y;
		expa = exponent16(a);
		expb = exponent16(b);
		जाओ valid_add;
	पूर्ण

	अगर ((taga == TW_NaN) || (tagb == TW_NaN)) अणु
		अगर (deststnr == 0)
			वापस real_2op_NaN(b, tagb, deststnr, a);
		अन्यथा
			वापस real_2op_NaN(a, taga, deststnr, a);
	पूर्ण

	वापस add_sub_specials(a, taga, signa, b, tagb, signb,
				dest, deststnr, control_w);
पूर्ण

/* Subtract b from a.  (a-b) -> dest */
पूर्णांक FPU_sub(पूर्णांक flags, पूर्णांक rm, पूर्णांक control_w)
अणु
	FPU_REG स्थिर *a, *b;
	FPU_REG *dest;
	u_अक्षर taga, tagb, signa, signb, saved_sign, sign;
	पूर्णांक dअगरf, tag = 0, expa, expb, deststnr;

	a = &st(0);
	taga = FPU_gettag0();

	deststnr = 0;
	अगर (flags & LOADED) अणु
		b = (FPU_REG *) rm;
		tagb = flags & 0x0f;
	पूर्ण अन्यथा अणु
		b = &st(rm);
		tagb = FPU_gettagi(rm);

		अगर (flags & DEST_RM)
			deststnr = rm;
	पूर्ण

	signa = माला_लोign(a);
	signb = माला_लोign(b);

	अगर (flags & REV) अणु
		signa ^= SIGN_NEG;
		signb ^= SIGN_NEG;
	पूर्ण

	dest = &st(deststnr);
	saved_sign = माला_लोign(dest);

	अगर (!(taga | tagb)) अणु
		expa = exponent(a);
		expb = exponent(b);

	      valid_subtract:
		/* Both रेजिस्टरs are valid */

		dअगरf = expa - expb;

		अगर (!dअगरf) अणु
			dअगरf = a->sigh - b->sigh;	/* Works only अगर ms bits are identical */
			अगर (!dअगरf) अणु
				dअगरf = a->sigl > b->sigl;
				अगर (!dअगरf)
					dअगरf = -(a->sigl < b->sigl);
			पूर्ण
		पूर्ण

		चयन ((((पूर्णांक)signa) * 2 + signb) / SIGN_NEG) अणु
		हाल 0:	/* P - P */
		हाल 3:	/* N - N */
			अगर (dअगरf > 0) अणु
				/* |a| > |b| */
				tag =
				    FPU_u_sub(a, b, dest, control_w, signa,
					      expa, expb);
			पूर्ण अन्यथा अगर (dअगरf == 0) अणु
				FPU_copy_to_regi(&CONST_Z, TAG_Zero, deststnr);

				/* sign depends upon rounding mode */
				setsign(dest, ((control_w & CW_RC) != RC_DOWN)
					? SIGN_POS : SIGN_NEG);
				वापस TAG_Zero;
			पूर्ण अन्यथा अणु
				sign = signa ^ SIGN_NEG;
				tag =
				    FPU_u_sub(b, a, dest, control_w, sign, expb,
					      expa);
			पूर्ण
			अवरोध;
		हाल 1:	/* P - N */
			tag =
			    FPU_u_add(a, b, dest, control_w, SIGN_POS, expa,
				      expb);
			अवरोध;
		हाल 2:	/* N - P */
			tag =
			    FPU_u_add(a, b, dest, control_w, SIGN_NEG, expa,
				      expb);
			अवरोध;
#अगर_घोषित PARANOID
		शेष:
			EXCEPTION(EX_INTERNAL | 0x111);
			वापस -1;
#पूर्ण_अगर
		पूर्ण
		अगर (tag < 0) अणु
			setsign(dest, saved_sign);
			वापस tag;
		पूर्ण
		FPU_settagi(deststnr, tag);
		वापस tag;
	पूर्ण

	अगर (taga == TAG_Special)
		taga = FPU_Special(a);
	अगर (tagb == TAG_Special)
		tagb = FPU_Special(b);

	अगर (((taga == TAG_Valid) && (tagb == TW_Denormal))
	    || ((taga == TW_Denormal) && (tagb == TAG_Valid))
	    || ((taga == TW_Denormal) && (tagb == TW_Denormal))) अणु
		FPU_REG x, y;

		अगर (denormal_opeअक्रम() < 0)
			वापस FPU_Exception;

		FPU_to_exp16(a, &x);
		FPU_to_exp16(b, &y);
		a = &x;
		b = &y;
		expa = exponent16(a);
		expb = exponent16(b);

		जाओ valid_subtract;
	पूर्ण

	अगर ((taga == TW_NaN) || (tagb == TW_NaN)) अणु
		FPU_REG स्थिर *d1, *d2;
		अगर (flags & REV) अणु
			d1 = b;
			d2 = a;
		पूर्ण अन्यथा अणु
			d1 = a;
			d2 = b;
		पूर्ण
		अगर (flags & LOADED)
			वापस real_2op_NaN(b, tagb, deststnr, d1);
		अगर (flags & DEST_RM)
			वापस real_2op_NaN(a, taga, deststnr, d2);
		अन्यथा
			वापस real_2op_NaN(b, tagb, deststnr, d2);
	पूर्ण

	वापस add_sub_specials(a, taga, signa, b, tagb, signb ^ SIGN_NEG,
				dest, deststnr, control_w);
पूर्ण

अटल
पूर्णांक add_sub_specials(FPU_REG स्थिर *a, u_अक्षर taga, u_अक्षर signa,
		     FPU_REG स्थिर *b, u_अक्षर tagb, u_अक्षर signb,
		     FPU_REG * dest, पूर्णांक deststnr, पूर्णांक control_w)
अणु
	अगर (((taga == TW_Denormal) || (tagb == TW_Denormal))
	    && (denormal_opeअक्रम() < 0))
		वापस FPU_Exception;

	अगर (taga == TAG_Zero) अणु
		अगर (tagb == TAG_Zero) अणु
			/* Both are zero, result will be zero. */
			u_अक्षर dअगरferent_signs = signa ^ signb;

			FPU_copy_to_regi(a, TAG_Zero, deststnr);
			अगर (dअगरferent_signs) अणु
				/* Signs are dअगरferent. */
				/* Sign of answer depends upon rounding mode. */
				setsign(dest, ((control_w & CW_RC) != RC_DOWN)
					? SIGN_POS : SIGN_NEG);
			पूर्ण अन्यथा
				setsign(dest, signa);	/* signa may dअगरfer from the sign of a. */
			वापस TAG_Zero;
		पूर्ण अन्यथा अणु
			reg_copy(b, dest);
			अगर ((tagb == TW_Denormal) && (b->sigh & 0x80000000)) अणु
				/* A pseuकरोDenormal, convert it. */
				addexponent(dest, 1);
				tagb = TAG_Valid;
			पूर्ण अन्यथा अगर (tagb > TAG_Empty)
				tagb = TAG_Special;
			setsign(dest, signb);	/* signb may dअगरfer from the sign of b. */
			FPU_settagi(deststnr, tagb);
			वापस tagb;
		पूर्ण
	पूर्ण अन्यथा अगर (tagb == TAG_Zero) अणु
		reg_copy(a, dest);
		अगर ((taga == TW_Denormal) && (a->sigh & 0x80000000)) अणु
			/* A pseuकरोDenormal */
			addexponent(dest, 1);
			taga = TAG_Valid;
		पूर्ण अन्यथा अगर (taga > TAG_Empty)
			taga = TAG_Special;
		setsign(dest, signa);	/* signa may dअगरfer from the sign of a. */
		FPU_settagi(deststnr, taga);
		वापस taga;
	पूर्ण अन्यथा अगर (taga == TW_Infinity) अणु
		अगर ((tagb != TW_Infinity) || (signa == signb)) अणु
			FPU_copy_to_regi(a, TAG_Special, deststnr);
			setsign(dest, signa);	/* signa may dअगरfer from the sign of a. */
			वापस taga;
		पूर्ण
		/* Infinity-Infinity is undefined. */
		वापस arith_invalid(deststnr);
	पूर्ण अन्यथा अगर (tagb == TW_Infinity) अणु
		FPU_copy_to_regi(b, TAG_Special, deststnr);
		setsign(dest, signb);	/* signb may dअगरfer from the sign of b. */
		वापस tagb;
	पूर्ण
#अगर_घोषित PARANOID
	EXCEPTION(EX_INTERNAL | 0x101);
#पूर्ण_अगर

	वापस FPU_Exception;
पूर्ण
