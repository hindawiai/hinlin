<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_mul.c                                                                |
 |                                                                           |
 | Multiply one FPU_REG by another, put the result in a destination FPU_REG. |
 |                                                                           |
 | Copyright (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 | Returns the tag of the result अगर no exceptions or errors occurred.        |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | The destination may be any FPU_REG, including one of the source FPU_REGs. |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_emu.h"
#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "fpu_system.h"

/*
  Multiply two रेजिस्टरs to give a रेजिस्टर result.
  The sources are st(deststnr) and (b,tagb,signb).
  The destination is st(deststnr).
  */
/* This routine must be called with non-empty source रेजिस्टरs */
पूर्णांक FPU_mul(FPU_REG स्थिर *b, u_अक्षर tagb, पूर्णांक deststnr, पूर्णांक control_w)
अणु
	FPU_REG *a = &st(deststnr);
	FPU_REG *dest = a;
	u_अक्षर taga = FPU_gettagi(deststnr);
	u_अक्षर saved_sign = माला_लोign(dest);
	u_अक्षर sign = (माला_लोign(a) ^ माला_लोign(b));
	पूर्णांक tag;

	अगर (!(taga | tagb)) अणु
		/* Both regs Valid, this should be the most common हाल. */

		tag =
		    FPU_u_mul(a, b, dest, control_w, sign,
			      exponent(a) + exponent(b));
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
		tag = FPU_u_mul(&x, &y, dest, control_w, sign,
				exponent16(&x) + exponent16(&y));
		अगर (tag < 0) अणु
			setsign(dest, saved_sign);
			वापस tag;
		पूर्ण
		FPU_settagi(deststnr, tag);
		वापस tag;
	पूर्ण अन्यथा अगर ((taga <= TW_Denormal) && (tagb <= TW_Denormal)) अणु
		अगर (((tagb == TW_Denormal) || (taga == TW_Denormal))
		    && (denormal_opeअक्रम() < 0))
			वापस FPU_Exception;

		/* Must have either both arguments == zero, or
		   one valid and the other zero.
		   The result is thereक्रमe zero. */
		FPU_copy_to_regi(&CONST_Z, TAG_Zero, deststnr);
		/* The 80486 book says that the answer is +0, but a real
		   80486 behaves this way.
		   IEEE-754 apparently says it should be this way. */
		setsign(dest, sign);
		वापस TAG_Zero;
	पूर्ण
	/* Must have infinities, NaNs, etc */
	अन्यथा अगर ((taga == TW_NaN) || (tagb == TW_NaN)) अणु
		वापस real_2op_NaN(b, tagb, deststnr, &st(0));
	पूर्ण अन्यथा अगर (((taga == TW_Infinity) && (tagb == TAG_Zero))
		   || ((tagb == TW_Infinity) && (taga == TAG_Zero))) अणु
		वापस arith_invalid(deststnr);	/* Zero*Infinity is invalid */
	पूर्ण अन्यथा अगर (((taga == TW_Denormal) || (tagb == TW_Denormal))
		   && (denormal_opeअक्रम() < 0)) अणु
		वापस FPU_Exception;
	पूर्ण अन्यथा अगर (taga == TW_Infinity) अणु
		FPU_copy_to_regi(a, TAG_Special, deststnr);
		setsign(dest, sign);
		वापस TAG_Special;
	पूर्ण अन्यथा अगर (tagb == TW_Infinity) अणु
		FPU_copy_to_regi(b, TAG_Special, deststnr);
		setsign(dest, sign);
		वापस TAG_Special;
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा अणु
		EXCEPTION(EX_INTERNAL | 0x102);
		वापस FPU_Exception;
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	वापस 0;
पूर्ण
