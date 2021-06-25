<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_भागide.c                                                             |
 |                                                                           |
 | Divide one FPU_REG by another and put the result in a destination FPU_REG.|
 |                                                                           |
 | Copyright (C) 1996                                                        |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |    Return value is the tag of the answer, or-ed with FPU_Exception अगर     |
 |    one was उठाओd, or -1 on पूर्णांकernal error.                               |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | The destination may be any FPU_REG, including one of the source FPU_REGs. |
 +---------------------------------------------------------------------------*/

#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "fpu_emu.h"
#समावेश "fpu_system.h"

/*
  Divide one रेजिस्टर by another and put the result पूर्णांकo a third रेजिस्टर.
  */
पूर्णांक FPU_भाग(पूर्णांक flags, पूर्णांक rm, पूर्णांक control_w)
अणु
	FPU_REG x, y;
	FPU_REG स्थिर *a, *b, *st0_ptr, *st_ptr;
	FPU_REG *dest;
	u_अक्षर taga, tagb, signa, signb, sign, saved_sign;
	पूर्णांक tag, deststnr;

	अगर (flags & DEST_RM)
		deststnr = rm;
	अन्यथा
		deststnr = 0;

	अगर (flags & REV) अणु
		b = &st(0);
		st0_ptr = b;
		tagb = FPU_gettag0();
		अगर (flags & LOADED) अणु
			a = (FPU_REG *) rm;
			taga = flags & 0x0f;
		पूर्ण अन्यथा अणु
			a = &st(rm);
			st_ptr = a;
			taga = FPU_gettagi(rm);
		पूर्ण
	पूर्ण अन्यथा अणु
		a = &st(0);
		st0_ptr = a;
		taga = FPU_gettag0();
		अगर (flags & LOADED) अणु
			b = (FPU_REG *) rm;
			tagb = flags & 0x0f;
		पूर्ण अन्यथा अणु
			b = &st(rm);
			st_ptr = b;
			tagb = FPU_gettagi(rm);
		पूर्ण
	पूर्ण

	signa = माला_लोign(a);
	signb = माला_लोign(b);

	sign = signa ^ signb;

	dest = &st(deststnr);
	saved_sign = माला_लोign(dest);

	अगर (!(taga | tagb)) अणु
		/* Both regs Valid, this should be the most common हाल. */
		reg_copy(a, &x);
		reg_copy(b, &y);
		setpositive(&x);
		setpositive(&y);
		tag = FPU_u_भाग(&x, &y, dest, control_w, sign);

		अगर (tag < 0)
			वापस tag;

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
		अगर (denormal_opeअक्रम() < 0)
			वापस FPU_Exception;

		FPU_to_exp16(a, &x);
		FPU_to_exp16(b, &y);
		tag = FPU_u_भाग(&x, &y, dest, control_w, sign);
		अगर (tag < 0)
			वापस tag;

		FPU_settagi(deststnr, tag);
		वापस tag;
	पूर्ण अन्यथा अगर ((taga <= TW_Denormal) && (tagb <= TW_Denormal)) अणु
		अगर (tagb != TAG_Zero) अणु
			/* Want to find Zero/Valid */
			अगर (tagb == TW_Denormal) अणु
				अगर (denormal_opeअक्रम() < 0)
					वापस FPU_Exception;
			पूर्ण

			/* The result is zero. */
			FPU_copy_to_regi(&CONST_Z, TAG_Zero, deststnr);
			setsign(dest, sign);
			वापस TAG_Zero;
		पूर्ण
		/* We have an exception condition, either 0/0 or Valid/Zero. */
		अगर (taga == TAG_Zero) अणु
			/* 0/0 */
			वापस arith_invalid(deststnr);
		पूर्ण
		/* Valid/Zero */
		वापस FPU_भागide_by_zero(deststnr, sign);
	पूर्ण
	/* Must have infinities, NaNs, etc */
	अन्यथा अगर ((taga == TW_NaN) || (tagb == TW_NaN)) अणु
		अगर (flags & LOADED)
			वापस real_2op_NaN((FPU_REG *) rm, flags & 0x0f, 0,
					    st0_ptr);

		अगर (flags & DEST_RM) अणु
			पूर्णांक tag;
			tag = FPU_gettag0();
			अगर (tag == TAG_Special)
				tag = FPU_Special(st0_ptr);
			वापस real_2op_NaN(st0_ptr, tag, rm,
					    (flags & REV) ? st0_ptr : &st(rm));
		पूर्ण अन्यथा अणु
			पूर्णांक tag;
			tag = FPU_gettagi(rm);
			अगर (tag == TAG_Special)
				tag = FPU_Special(&st(rm));
			वापस real_2op_NaN(&st(rm), tag, 0,
					    (flags & REV) ? st0_ptr : &st(rm));
		पूर्ण
	पूर्ण अन्यथा अगर (taga == TW_Infinity) अणु
		अगर (tagb == TW_Infinity) अणु
			/* infinity/infinity */
			वापस arith_invalid(deststnr);
		पूर्ण अन्यथा अणु
			/* tagb must be Valid or Zero */
			अगर ((tagb == TW_Denormal) && (denormal_opeअक्रम() < 0))
				वापस FPU_Exception;

			/* Infinity भागided by Zero or Valid करोes
			   not उठाओ and exception, but वापसs Infinity */
			FPU_copy_to_regi(a, TAG_Special, deststnr);
			setsign(dest, sign);
			वापस taga;
		पूर्ण
	पूर्ण अन्यथा अगर (tagb == TW_Infinity) अणु
		अगर ((taga == TW_Denormal) && (denormal_opeअक्रम() < 0))
			वापस FPU_Exception;

		/* The result is zero. */
		FPU_copy_to_regi(&CONST_Z, TAG_Zero, deststnr);
		setsign(dest, sign);
		वापस TAG_Zero;
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा अणु
		EXCEPTION(EX_INTERNAL | 0x102);
		वापस FPU_Exception;
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	वापस 0;
पूर्ण
