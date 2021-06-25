<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_ld_str.c                                                             |
 |                                                                           |
 | All of the functions which transfer data between user memory and FPU_REGs.|
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1996,1997                                    |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The file contains code which accesses user memory.                     |
 |    Emulator अटल data may change when user memory is accessed, due to   |
 |    other processes using the emulator जबतक swapping is in progress.      |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_emu.h"

#समावेश <linux/uaccess.h>

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "reg_constant.h"
#समावेश "control_w.h"
#समावेश "status_w.h"

#घोषणा DOUBLE_Emax 1023	/* largest valid exponent */
#घोषणा DOUBLE_Ebias 1023
#घोषणा DOUBLE_Emin (-1022)	/* smallest valid exponent */

#घोषणा SINGLE_Emax 127		/* largest valid exponent */
#घोषणा SINGLE_Ebias 127
#घोषणा SINGLE_Emin (-126)	/* smallest valid exponent */

अटल u_अक्षर normalize_no_excep(FPU_REG *r, पूर्णांक exp, पूर्णांक sign)
अणु
	u_अक्षर tag;

	setexponent16(r, exp);

	tag = FPU_normalize_nuo(r);
	stdexp(r);
	अगर (sign)
		setnegative(r);

	वापस tag;
पूर्ण

पूर्णांक FPU_tagof(FPU_REG *ptr)
अणु
	पूर्णांक exp;

	exp = exponent16(ptr) & 0x7fff;
	अगर (exp == 0) अणु
		अगर (!(ptr->sigh | ptr->sigl)) अणु
			वापस TAG_Zero;
		पूर्ण
		/* The number is a de-normal or pseuकरोdenormal. */
		वापस TAG_Special;
	पूर्ण

	अगर (exp == 0x7fff) अणु
		/* Is an Infinity, a NaN, or an unsupported data type. */
		वापस TAG_Special;
	पूर्ण

	अगर (!(ptr->sigh & 0x80000000)) अणु
		/* Unsupported data type. */
		/* Valid numbers have the ms bit set to 1. */
		/* Unnormal. */
		वापस TAG_Special;
	पूर्ण

	वापस TAG_Valid;
पूर्ण

/* Get a दीर्घ द्विगुन from user memory */
पूर्णांक FPU_load_extended(दीर्घ द्विगुन __user *s, पूर्णांक stnr)
अणु
	FPU_REG *sti_ptr = &st(stnr);

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(s, 10);
	FPU_copy_from_user(sti_ptr, s, 10);
	RE_ENTRANT_CHECK_ON;

	वापस FPU_tagof(sti_ptr);
पूर्ण

/* Get a द्विगुन from user memory */
पूर्णांक FPU_load_द्विगुन(द्विगुन __user *dभग्न, FPU_REG *loaded_data)
अणु
	पूर्णांक exp, tag, negative;
	अचिन्हित m64, l64;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(dभग्न, 8);
	FPU_get_user(m64, 1 + (अचिन्हित दीर्घ __user *)dभग्न);
	FPU_get_user(l64, (अचिन्हित दीर्घ __user *)dभग्न);
	RE_ENTRANT_CHECK_ON;

	negative = (m64 & 0x80000000) ? SIGN_Negative : SIGN_Positive;
	exp = ((m64 & 0x7ff00000) >> 20) - DOUBLE_Ebias + EXTENDED_Ebias;
	m64 &= 0xfffff;
	अगर (exp > DOUBLE_Emax + EXTENDED_Ebias) अणु
		/* Infinity or NaN */
		अगर ((m64 == 0) && (l64 == 0)) अणु
			/* +- infinity */
			loaded_data->sigh = 0x80000000;
			loaded_data->sigl = 0x00000000;
			exp = EXP_Infinity + EXTENDED_Ebias;
			tag = TAG_Special;
		पूर्ण अन्यथा अणु
			/* Must be a संकेतing or quiet NaN */
			exp = EXP_NaN + EXTENDED_Ebias;
			loaded_data->sigh = (m64 << 11) | 0x80000000;
			loaded_data->sigh |= l64 >> 21;
			loaded_data->sigl = l64 << 11;
			tag = TAG_Special;	/* The calling function must look क्रम NaNs */
		पूर्ण
	पूर्ण अन्यथा अगर (exp < DOUBLE_Emin + EXTENDED_Ebias) अणु
		/* Zero or de-normal */
		अगर ((m64 == 0) && (l64 == 0)) अणु
			/* Zero */
			reg_copy(&CONST_Z, loaded_data);
			exp = 0;
			tag = TAG_Zero;
		पूर्ण अन्यथा अणु
			/* De-normal */
			loaded_data->sigh = m64 << 11;
			loaded_data->sigh |= l64 >> 21;
			loaded_data->sigl = l64 << 11;

			वापस normalize_no_excep(loaded_data, DOUBLE_Emin,
						  negative)
			    | (denormal_opeअक्रम() < 0 ? FPU_Exception : 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		loaded_data->sigh = (m64 << 11) | 0x80000000;
		loaded_data->sigh |= l64 >> 21;
		loaded_data->sigl = l64 << 11;

		tag = TAG_Valid;
	पूर्ण

	setexponent16(loaded_data, exp | negative);

	वापस tag;
पूर्ण

/* Get a भग्न from user memory */
पूर्णांक FPU_load_single(भग्न __user *single, FPU_REG *loaded_data)
अणु
	अचिन्हित m32;
	पूर्णांक exp, tag, negative;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(single, 4);
	FPU_get_user(m32, (अचिन्हित दीर्घ __user *)single);
	RE_ENTRANT_CHECK_ON;

	negative = (m32 & 0x80000000) ? SIGN_Negative : SIGN_Positive;

	अगर (!(m32 & 0x7fffffff)) अणु
		/* Zero */
		reg_copy(&CONST_Z, loaded_data);
		addexponent(loaded_data, negative);
		वापस TAG_Zero;
	पूर्ण
	exp = ((m32 & 0x7f800000) >> 23) - SINGLE_Ebias + EXTENDED_Ebias;
	m32 = (m32 & 0x7fffff) << 8;
	अगर (exp < SINGLE_Emin + EXTENDED_Ebias) अणु
		/* De-normals */
		loaded_data->sigh = m32;
		loaded_data->sigl = 0;

		वापस normalize_no_excep(loaded_data, SINGLE_Emin, negative)
		    | (denormal_opeअक्रम() < 0 ? FPU_Exception : 0);
	पूर्ण अन्यथा अगर (exp > SINGLE_Emax + EXTENDED_Ebias) अणु
		/* Infinity or NaN */
		अगर (m32 == 0) अणु
			/* +- infinity */
			loaded_data->sigh = 0x80000000;
			loaded_data->sigl = 0x00000000;
			exp = EXP_Infinity + EXTENDED_Ebias;
			tag = TAG_Special;
		पूर्ण अन्यथा अणु
			/* Must be a संकेतing or quiet NaN */
			exp = EXP_NaN + EXTENDED_Ebias;
			loaded_data->sigh = m32 | 0x80000000;
			loaded_data->sigl = 0;
			tag = TAG_Special;	/* The calling function must look क्रम NaNs */
		पूर्ण
	पूर्ण अन्यथा अणु
		loaded_data->sigh = m32 | 0x80000000;
		loaded_data->sigl = 0;
		tag = TAG_Valid;
	पूर्ण

	setexponent16(loaded_data, exp | negative);	/* Set the sign. */

	वापस tag;
पूर्ण

/* Get a दीर्घ दीर्घ from user memory */
पूर्णांक FPU_load_पूर्णांक64(दीर्घ दीर्घ __user *_s)
अणु
	दीर्घ दीर्घ s;
	पूर्णांक sign;
	FPU_REG *st0_ptr = &st(0);

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(_s, 8);
	अगर (copy_from_user(&s, _s, 8))
		FPU_पात;
	RE_ENTRANT_CHECK_ON;

	अगर (s == 0) अणु
		reg_copy(&CONST_Z, st0_ptr);
		वापस TAG_Zero;
	पूर्ण

	अगर (s > 0)
		sign = SIGN_Positive;
	अन्यथा अणु
		s = -s;
		sign = SIGN_Negative;
	पूर्ण

	signअगरicand(st0_ptr) = s;

	वापस normalize_no_excep(st0_ptr, 63, sign);
पूर्ण

/* Get a दीर्घ from user memory */
पूर्णांक FPU_load_पूर्णांक32(दीर्घ __user *_s, FPU_REG *loaded_data)
अणु
	दीर्घ s;
	पूर्णांक negative;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(_s, 4);
	FPU_get_user(s, _s);
	RE_ENTRANT_CHECK_ON;

	अगर (s == 0) अणु
		reg_copy(&CONST_Z, loaded_data);
		वापस TAG_Zero;
	पूर्ण

	अगर (s > 0)
		negative = SIGN_Positive;
	अन्यथा अणु
		s = -s;
		negative = SIGN_Negative;
	पूर्ण

	loaded_data->sigh = s;
	loaded_data->sigl = 0;

	वापस normalize_no_excep(loaded_data, 31, negative);
पूर्ण

/* Get a लघु from user memory */
पूर्णांक FPU_load_पूर्णांक16(लघु __user *_s, FPU_REG *loaded_data)
अणु
	पूर्णांक s, negative;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(_s, 2);
	/* Cast as लघु to get the sign extended. */
	FPU_get_user(s, _s);
	RE_ENTRANT_CHECK_ON;

	अगर (s == 0) अणु
		reg_copy(&CONST_Z, loaded_data);
		वापस TAG_Zero;
	पूर्ण

	अगर (s > 0)
		negative = SIGN_Positive;
	अन्यथा अणु
		s = -s;
		negative = SIGN_Negative;
	पूर्ण

	loaded_data->sigh = s << 16;
	loaded_data->sigl = 0;

	वापस normalize_no_excep(loaded_data, 15, negative);
पूर्ण

/* Get a packed bcd array from user memory */
पूर्णांक FPU_load_bcd(u_अक्षर __user *s)
अणु
	FPU_REG *st0_ptr = &st(0);
	पूर्णांक pos;
	u_अक्षर bcd;
	दीर्घ दीर्घ l = 0;
	पूर्णांक sign;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(s, 10);
	RE_ENTRANT_CHECK_ON;
	क्रम (pos = 8; pos >= 0; pos--) अणु
		l *= 10;
		RE_ENTRANT_CHECK_OFF;
		FPU_get_user(bcd, s + pos);
		RE_ENTRANT_CHECK_ON;
		l += bcd >> 4;
		l *= 10;
		l += bcd & 0x0f;
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	FPU_get_user(sign, s + 9);
	sign = sign & 0x80 ? SIGN_Negative : SIGN_Positive;
	RE_ENTRANT_CHECK_ON;

	अगर (l == 0) अणु
		reg_copy(&CONST_Z, st0_ptr);
		addexponent(st0_ptr, sign);	/* Set the sign. */
		वापस TAG_Zero;
	पूर्ण अन्यथा अणु
		signअगरicand(st0_ptr) = l;
		वापस normalize_no_excep(st0_ptr, 63, sign);
	पूर्ण
पूर्ण

/*===========================================================================*/

/* Put a दीर्घ द्विगुन पूर्णांकo user memory */
पूर्णांक FPU_store_extended(FPU_REG *st0_ptr, u_अक्षर st0_tag,
		       दीर्घ द्विगुन __user * d)
अणु
	/*
	   The only exception उठाओd by an attempt to store to an
	   extended क्रमmat is the Invalid Stack exception, i.e.
	   attempting to store from an empty रेजिस्टर.
	 */

	अगर (st0_tag != TAG_Empty) अणु
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(d, 10);

		FPU_put_user(st0_ptr->sigl, (अचिन्हित दीर्घ __user *)d);
		FPU_put_user(st0_ptr->sigh,
			     (अचिन्हित दीर्घ __user *)((u_अक्षर __user *) d + 4));
		FPU_put_user(exponent16(st0_ptr),
			     (अचिन्हित लघु __user *)((u_अक्षर __user *) d +
						       8));
		RE_ENTRANT_CHECK_ON;

		वापस 1;
	पूर्ण

	/* Empty रेजिस्टर (stack underflow) */
	EXCEPTION(EX_StackUnder);
	अगर (control_word & CW_Invalid) अणु
		/* The masked response */
		/* Put out the QNaN indefinite */
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(d, 10);
		FPU_put_user(0, (अचिन्हित दीर्घ __user *)d);
		FPU_put_user(0xc0000000, 1 + (अचिन्हित दीर्घ __user *)d);
		FPU_put_user(0xffff, 4 + (लघु __user *)d);
		RE_ENTRANT_CHECK_ON;
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;

पूर्ण

/* Put a द्विगुन पूर्णांकo user memory */
पूर्णांक FPU_store_द्विगुन(FPU_REG *st0_ptr, u_अक्षर st0_tag, द्विगुन __user *dभग्न)
अणु
	अचिन्हित दीर्घ l[2];
	अचिन्हित दीर्घ increment = 0;	/* aव्योम gcc warnings */
	पूर्णांक precision_loss;
	पूर्णांक exp;
	FPU_REG पंचांगp;

	l[0] = 0;
	l[1] = 0;
	अगर (st0_tag == TAG_Valid) अणु
		reg_copy(st0_ptr, &पंचांगp);
		exp = exponent(&पंचांगp);

		अगर (exp < DOUBLE_Emin) अणु	/* It may be a denormal */
			addexponent(&पंचांगp, -DOUBLE_Emin + 52);	/* largest exp to be 51 */
denormal_arg:
			अगर ((precision_loss = FPU_round_to_पूर्णांक(&पंचांगp, st0_tag))) अणु
#अगर_घोषित PECULIAR_486
				/* Did it round to a non-denormal ? */
				/* This behaviour might be regarded as peculiar, it appears
				   that the 80486 rounds to the dest precision, then
				   converts to decide underflow. */
				अगर (!
				    ((पंचांगp.sigh == 0x00100000) && (पंचांगp.sigl == 0)
				     && (st0_ptr->sigl & 0x000007ff)))
#पूर्ण_अगर /* PECULIAR_486 */
				अणु
					EXCEPTION(EX_Underflow);
					/* This is a special हाल: see sec 16.2.5.1 of
					   the 80486 book */
					अगर (!(control_word & CW_Underflow))
						वापस 0;
				पूर्ण
				EXCEPTION(precision_loss);
				अगर (!(control_word & CW_Precision))
					वापस 0;
			पूर्ण
			l[0] = पंचांगp.sigl;
			l[1] = पंचांगp.sigh;
		पूर्ण अन्यथा अणु
			अगर (पंचांगp.sigl & 0x000007ff) अणु
				precision_loss = 1;
				चयन (control_word & CW_RC) अणु
				हाल RC_RND:
					/* Rounding can get a little messy.. */
					increment = ((पंचांगp.sigl & 0x7ff) > 0x400) |	/* nearest */
					    ((पंचांगp.sigl & 0xc00) == 0xc00);	/* odd -> even */
					अवरोध;
				हाल RC_DOWN:	/* towards -infinity */
					increment =
					    signpositive(&पंचांगp) ? 0 : पंचांगp.
					    sigl & 0x7ff;
					अवरोध;
				हाल RC_UP:	/* towards +infinity */
					increment =
					    signpositive(&पंचांगp) ? पंचांगp.
					    sigl & 0x7ff : 0;
					अवरोध;
				हाल RC_CHOP:
					increment = 0;
					अवरोध;
				पूर्ण

				/* Truncate the mantissa */
				पंचांगp.sigl &= 0xfffff800;

				अगर (increment) अणु
					अगर (पंचांगp.sigl >= 0xfffff800) अणु
						/* the sigl part overflows */
						अगर (पंचांगp.sigh == 0xffffffff) अणु
							/* The sigh part overflows */
							पंचांगp.sigh = 0x80000000;
							exp++;
							अगर (exp >= EXP_OVER)
								जाओ overflow;
						पूर्ण अन्यथा अणु
							पंचांगp.sigh++;
						पूर्ण
						पंचांगp.sigl = 0x00000000;
					पूर्ण अन्यथा अणु
						/* We only need to increment sigl */
						पंचांगp.sigl += 0x00000800;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा
				precision_loss = 0;

			l[0] = (पंचांगp.sigl >> 11) | (पंचांगp.sigh << 21);
			l[1] = ((पंचांगp.sigh >> 11) & 0xfffff);

			अगर (exp > DOUBLE_Emax) अणु
			      overflow:
				EXCEPTION(EX_Overflow);
				अगर (!(control_word & CW_Overflow))
					वापस 0;
				set_precision_flag_up();
				अगर (!(control_word & CW_Precision))
					वापस 0;

				/* This is a special हाल: see sec 16.2.5.1 of the 80486 book */
				/* Overflow to infinity */
				l[1] = 0x7ff00000;	/* Set to + INF */
			पूर्ण अन्यथा अणु
				अगर (precision_loss) अणु
					अगर (increment)
						set_precision_flag_up();
					अन्यथा
						set_precision_flag_करोwn();
				पूर्ण
				/* Add the exponent */
				l[1] |= (((exp + DOUBLE_Ebias) & 0x7ff) << 20);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		/* Number is zero */
	पूर्ण अन्यथा अगर (st0_tag == TAG_Special) अणु
		st0_tag = FPU_Special(st0_ptr);
		अगर (st0_tag == TW_Denormal) अणु
			/* A denormal will always underflow. */
#अगर_अघोषित PECULIAR_486
			/* An 80486 is supposed to be able to generate
			   a denormal exception here, but... */
			/* Underflow has priority. */
			अगर (control_word & CW_Underflow)
				denormal_opeअक्रम();
#पूर्ण_अगर /* PECULIAR_486 */
			reg_copy(st0_ptr, &पंचांगp);
			जाओ denormal_arg;
		पूर्ण अन्यथा अगर (st0_tag == TW_Infinity) अणु
			l[1] = 0x7ff00000;
		पूर्ण अन्यथा अगर (st0_tag == TW_NaN) अणु
			/* Is it really a NaN ? */
			अगर ((exponent(st0_ptr) == EXP_OVER)
			    && (st0_ptr->sigh & 0x80000000)) अणु
				/* See अगर we can get a valid NaN from the FPU_REG */
				l[0] =
				    (st0_ptr->sigl >> 11) | (st0_ptr->
							     sigh << 21);
				l[1] = ((st0_ptr->sigh >> 11) & 0xfffff);
				अगर (!(st0_ptr->sigh & 0x40000000)) अणु
					/* It is a संकेतling NaN */
					EXCEPTION(EX_Invalid);
					अगर (!(control_word & CW_Invalid))
						वापस 0;
					l[1] |= (0x40000000 >> 11);
				पूर्ण
				l[1] |= 0x7ff00000;
			पूर्ण अन्यथा अणु
				/* It is an unsupported data type */
				EXCEPTION(EX_Invalid);
				अगर (!(control_word & CW_Invalid))
					वापस 0;
				l[1] = 0xfff80000;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TAG_Empty) अणु
		/* Empty रेजिस्टर (stack underflow) */
		EXCEPTION(EX_StackUnder);
		अगर (control_word & CW_Invalid) अणु
			/* The masked response */
			/* Put out the QNaN indefinite */
			RE_ENTRANT_CHECK_OFF;
			FPU_access_ok(dभग्न, 8);
			FPU_put_user(0, (अचिन्हित दीर्घ __user *)dभग्न);
			FPU_put_user(0xfff80000,
				     1 + (अचिन्हित दीर्घ __user *)dभग्न);
			RE_ENTRANT_CHECK_ON;
			वापस 1;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	अगर (माला_लोign(st0_ptr))
		l[1] |= 0x80000000;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(dभग्न, 8);
	FPU_put_user(l[0], (अचिन्हित दीर्घ __user *)dभग्न);
	FPU_put_user(l[1], 1 + (अचिन्हित दीर्घ __user *)dभग्न);
	RE_ENTRANT_CHECK_ON;

	वापस 1;
पूर्ण

/* Put a भग्न पूर्णांकo user memory */
पूर्णांक FPU_store_single(FPU_REG *st0_ptr, u_अक्षर st0_tag, भग्न __user *single)
अणु
	दीर्घ templ = 0;
	अचिन्हित दीर्घ increment = 0;	/* aव्योम gcc warnings */
	पूर्णांक precision_loss;
	पूर्णांक exp;
	FPU_REG पंचांगp;

	अगर (st0_tag == TAG_Valid) अणु

		reg_copy(st0_ptr, &पंचांगp);
		exp = exponent(&पंचांगp);

		अगर (exp < SINGLE_Emin) अणु
			addexponent(&पंचांगp, -SINGLE_Emin + 23);	/* largest exp to be 22 */

		      denormal_arg:

			अगर ((precision_loss = FPU_round_to_पूर्णांक(&पंचांगp, st0_tag))) अणु
#अगर_घोषित PECULIAR_486
				/* Did it round to a non-denormal ? */
				/* This behaviour might be regarded as peculiar, it appears
				   that the 80486 rounds to the dest precision, then
				   converts to decide underflow. */
				अगर (!((पंचांगp.sigl == 0x00800000) &&
				      ((st0_ptr->sigh & 0x000000ff)
				       || st0_ptr->sigl)))
#पूर्ण_अगर /* PECULIAR_486 */
				अणु
					EXCEPTION(EX_Underflow);
					/* This is a special हाल: see sec 16.2.5.1 of
					   the 80486 book */
					अगर (!(control_word & CW_Underflow))
						वापस 0;
				पूर्ण
				EXCEPTION(precision_loss);
				अगर (!(control_word & CW_Precision))
					वापस 0;
			पूर्ण
			templ = पंचांगp.sigl;
		पूर्ण अन्यथा अणु
			अगर (पंचांगp.sigl | (पंचांगp.sigh & 0x000000ff)) अणु
				अचिन्हित दीर्घ sigh = पंचांगp.sigh;
				अचिन्हित दीर्घ sigl = पंचांगp.sigl;

				precision_loss = 1;
				चयन (control_word & CW_RC) अणु
				हाल RC_RND:
					increment = ((sigh & 0xff) > 0x80)	/* more than half */
					    ||(((sigh & 0xff) == 0x80) && sigl)	/* more than half */
					    ||((sigh & 0x180) == 0x180);	/* round to even */
					अवरोध;
				हाल RC_DOWN:	/* towards -infinity */
					increment = signpositive(&पंचांगp)
					    ? 0 : (sigl | (sigh & 0xff));
					अवरोध;
				हाल RC_UP:	/* towards +infinity */
					increment = signpositive(&पंचांगp)
					    ? (sigl | (sigh & 0xff)) : 0;
					अवरोध;
				हाल RC_CHOP:
					increment = 0;
					अवरोध;
				पूर्ण

				/* Truncate part of the mantissa */
				पंचांगp.sigl = 0;

				अगर (increment) अणु
					अगर (sigh >= 0xffffff00) अणु
						/* The sigh part overflows */
						पंचांगp.sigh = 0x80000000;
						exp++;
						अगर (exp >= EXP_OVER)
							जाओ overflow;
					पूर्ण अन्यथा अणु
						पंचांगp.sigh &= 0xffffff00;
						पंचांगp.sigh += 0x100;
					पूर्ण
				पूर्ण अन्यथा अणु
					पंचांगp.sigh &= 0xffffff00;	/* Finish the truncation */
				पूर्ण
			पूर्ण अन्यथा
				precision_loss = 0;

			templ = (पंचांगp.sigh >> 8) & 0x007fffff;

			अगर (exp > SINGLE_Emax) अणु
			      overflow:
				EXCEPTION(EX_Overflow);
				अगर (!(control_word & CW_Overflow))
					वापस 0;
				set_precision_flag_up();
				अगर (!(control_word & CW_Precision))
					वापस 0;

				/* This is a special हाल: see sec 16.2.5.1 of the 80486 book. */
				/* Masked response is overflow to infinity. */
				templ = 0x7f800000;
			पूर्ण अन्यथा अणु
				अगर (precision_loss) अणु
					अगर (increment)
						set_precision_flag_up();
					अन्यथा
						set_precision_flag_करोwn();
				पूर्ण
				/* Add the exponent */
				templ |= ((exp + SINGLE_Ebias) & 0xff) << 23;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (st0_tag == TAG_Zero) अणु
		templ = 0;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Special) अणु
		st0_tag = FPU_Special(st0_ptr);
		अगर (st0_tag == TW_Denormal) अणु
			reg_copy(st0_ptr, &पंचांगp);

			/* A denormal will always underflow. */
#अगर_अघोषित PECULIAR_486
			/* An 80486 is supposed to be able to generate
			   a denormal exception here, but... */
			/* Underflow has priority. */
			अगर (control_word & CW_Underflow)
				denormal_opeअक्रम();
#पूर्ण_अगर /* PECULIAR_486 */
			जाओ denormal_arg;
		पूर्ण अन्यथा अगर (st0_tag == TW_Infinity) अणु
			templ = 0x7f800000;
		पूर्ण अन्यथा अगर (st0_tag == TW_NaN) अणु
			/* Is it really a NaN ? */
			अगर ((exponent(st0_ptr) == EXP_OVER)
			    && (st0_ptr->sigh & 0x80000000)) अणु
				/* See अगर we can get a valid NaN from the FPU_REG */
				templ = st0_ptr->sigh >> 8;
				अगर (!(st0_ptr->sigh & 0x40000000)) अणु
					/* It is a संकेतling NaN */
					EXCEPTION(EX_Invalid);
					अगर (!(control_word & CW_Invalid))
						वापस 0;
					templ |= (0x40000000 >> 8);
				पूर्ण
				templ |= 0x7f800000;
			पूर्ण अन्यथा अणु
				/* It is an unsupported data type */
				EXCEPTION(EX_Invalid);
				अगर (!(control_word & CW_Invalid))
					वापस 0;
				templ = 0xffc00000;
			पूर्ण
		पूर्ण
#अगर_घोषित PARANOID
		अन्यथा अणु
			EXCEPTION(EX_INTERNAL | 0x164);
			वापस 0;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (st0_tag == TAG_Empty) अणु
		/* Empty रेजिस्टर (stack underflow) */
		EXCEPTION(EX_StackUnder);
		अगर (control_word & EX_Invalid) अणु
			/* The masked response */
			/* Put out the QNaN indefinite */
			RE_ENTRANT_CHECK_OFF;
			FPU_access_ok(single, 4);
			FPU_put_user(0xffc00000,
				     (अचिन्हित दीर्घ __user *)single);
			RE_ENTRANT_CHECK_ON;
			वापस 1;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
#अगर_घोषित PARANOID
	अन्यथा अणु
		EXCEPTION(EX_INTERNAL | 0x163);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (माला_लोign(st0_ptr))
		templ |= 0x80000000;

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(single, 4);
	FPU_put_user(templ, (अचिन्हित दीर्घ __user *)single);
	RE_ENTRANT_CHECK_ON;

	वापस 1;
पूर्ण

/* Put a दीर्घ दीर्घ पूर्णांकo user memory */
पूर्णांक FPU_store_पूर्णांक64(FPU_REG *st0_ptr, u_अक्षर st0_tag, दीर्घ दीर्घ __user *d)
अणु
	FPU_REG t;
	दीर्घ दीर्घ tll;
	पूर्णांक precision_loss;

	अगर (st0_tag == TAG_Empty) अणु
		/* Empty रेजिस्टर (stack underflow) */
		EXCEPTION(EX_StackUnder);
		जाओ invalid_opeअक्रम;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Special) अणु
		st0_tag = FPU_Special(st0_ptr);
		अगर ((st0_tag == TW_Infinity) || (st0_tag == TW_NaN)) अणु
			EXCEPTION(EX_Invalid);
			जाओ invalid_opeअक्रम;
		पूर्ण
	पूर्ण

	reg_copy(st0_ptr, &t);
	precision_loss = FPU_round_to_पूर्णांक(&t, st0_tag);
	((दीर्घ *)&tll)[0] = t.sigl;
	((दीर्घ *)&tll)[1] = t.sigh;
	अगर ((precision_loss == 1) ||
	    ((t.sigh & 0x80000000) &&
	     !((t.sigh == 0x80000000) && (t.sigl == 0) && signnegative(&t)))) अणु
		EXCEPTION(EX_Invalid);
		/* This is a special हाल: see sec 16.2.5.1 of the 80486 book */
	      invalid_opeअक्रम:
		अगर (control_word & EX_Invalid) अणु
			/* Produce something like QNaN "indefinite" */
			tll = 0x8000000000000000LL;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (precision_loss)
			set_precision_flag(precision_loss);
		अगर (signnegative(&t))
			tll = -tll;
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(d, 8);
	अगर (copy_to_user(d, &tll, 8))
		FPU_पात;
	RE_ENTRANT_CHECK_ON;

	वापस 1;
पूर्ण

/* Put a दीर्घ पूर्णांकo user memory */
पूर्णांक FPU_store_पूर्णांक32(FPU_REG *st0_ptr, u_अक्षर st0_tag, दीर्घ __user *d)
अणु
	FPU_REG t;
	पूर्णांक precision_loss;

	अगर (st0_tag == TAG_Empty) अणु
		/* Empty रेजिस्टर (stack underflow) */
		EXCEPTION(EX_StackUnder);
		जाओ invalid_opeअक्रम;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Special) अणु
		st0_tag = FPU_Special(st0_ptr);
		अगर ((st0_tag == TW_Infinity) || (st0_tag == TW_NaN)) अणु
			EXCEPTION(EX_Invalid);
			जाओ invalid_opeअक्रम;
		पूर्ण
	पूर्ण

	reg_copy(st0_ptr, &t);
	precision_loss = FPU_round_to_पूर्णांक(&t, st0_tag);
	अगर (t.sigh ||
	    ((t.sigl & 0x80000000) &&
	     !((t.sigl == 0x80000000) && signnegative(&t)))) अणु
		EXCEPTION(EX_Invalid);
		/* This is a special हाल: see sec 16.2.5.1 of the 80486 book */
	      invalid_opeअक्रम:
		अगर (control_word & EX_Invalid) अणु
			/* Produce something like QNaN "indefinite" */
			t.sigl = 0x80000000;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (precision_loss)
			set_precision_flag(precision_loss);
		अगर (signnegative(&t))
			t.sigl = -(दीर्घ)t.sigl;
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(d, 4);
	FPU_put_user(t.sigl, (अचिन्हित दीर्घ __user *)d);
	RE_ENTRANT_CHECK_ON;

	वापस 1;
पूर्ण

/* Put a लघु पूर्णांकo user memory */
पूर्णांक FPU_store_पूर्णांक16(FPU_REG *st0_ptr, u_अक्षर st0_tag, लघु __user *d)
अणु
	FPU_REG t;
	पूर्णांक precision_loss;

	अगर (st0_tag == TAG_Empty) अणु
		/* Empty रेजिस्टर (stack underflow) */
		EXCEPTION(EX_StackUnder);
		जाओ invalid_opeअक्रम;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Special) अणु
		st0_tag = FPU_Special(st0_ptr);
		अगर ((st0_tag == TW_Infinity) || (st0_tag == TW_NaN)) अणु
			EXCEPTION(EX_Invalid);
			जाओ invalid_opeअक्रम;
		पूर्ण
	पूर्ण

	reg_copy(st0_ptr, &t);
	precision_loss = FPU_round_to_पूर्णांक(&t, st0_tag);
	अगर (t.sigh ||
	    ((t.sigl & 0xffff8000) &&
	     !((t.sigl == 0x8000) && signnegative(&t)))) अणु
		EXCEPTION(EX_Invalid);
		/* This is a special हाल: see sec 16.2.5.1 of the 80486 book */
	      invalid_opeअक्रम:
		अगर (control_word & EX_Invalid) अणु
			/* Produce something like QNaN "indefinite" */
			t.sigl = 0x8000;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (precision_loss)
			set_precision_flag(precision_loss);
		अगर (signnegative(&t))
			t.sigl = -t.sigl;
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(d, 2);
	FPU_put_user((लघु)t.sigl, d);
	RE_ENTRANT_CHECK_ON;

	वापस 1;
पूर्ण

/* Put a packed bcd array पूर्णांकo user memory */
पूर्णांक FPU_store_bcd(FPU_REG *st0_ptr, u_अक्षर st0_tag, u_अक्षर __user *d)
अणु
	FPU_REG t;
	अचिन्हित दीर्घ दीर्घ ll;
	u_अक्षर b;
	पूर्णांक i, precision_loss;
	u_अक्षर sign = (माला_लोign(st0_ptr) == SIGN_NEG) ? 0x80 : 0;

	अगर (st0_tag == TAG_Empty) अणु
		/* Empty रेजिस्टर (stack underflow) */
		EXCEPTION(EX_StackUnder);
		जाओ invalid_opeअक्रम;
	पूर्ण अन्यथा अगर (st0_tag == TAG_Special) अणु
		st0_tag = FPU_Special(st0_ptr);
		अगर ((st0_tag == TW_Infinity) || (st0_tag == TW_NaN)) अणु
			EXCEPTION(EX_Invalid);
			जाओ invalid_opeअक्रम;
		पूर्ण
	पूर्ण

	reg_copy(st0_ptr, &t);
	precision_loss = FPU_round_to_पूर्णांक(&t, st0_tag);
	ll = signअगरicand(&t);

	/* Check क्रम overflow, by comparing with 999999999999999999 decimal. */
	अगर ((t.sigh > 0x0de0b6b3) ||
	    ((t.sigh == 0x0de0b6b3) && (t.sigl > 0xa763ffff))) अणु
		EXCEPTION(EX_Invalid);
		/* This is a special हाल: see sec 16.2.5.1 of the 80486 book */
	      invalid_opeअक्रम:
		अगर (control_word & CW_Invalid) अणु
			/* Produce the QNaN "indefinite" */
			RE_ENTRANT_CHECK_OFF;
			FPU_access_ok(d, 10);
			क्रम (i = 0; i < 7; i++)
				FPU_put_user(0, d + i);	/* These bytes "undefined" */
			FPU_put_user(0xc0, d + 7);	/* This byte "undefined" */
			FPU_put_user(0xff, d + 8);
			FPU_put_user(0xff, d + 9);
			RE_ENTRANT_CHECK_ON;
			वापस 1;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (precision_loss) अणु
		/* Precision loss करोesn't stop the data transfer */
		set_precision_flag(precision_loss);
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(d, 10);
	RE_ENTRANT_CHECK_ON;
	क्रम (i = 0; i < 9; i++) अणु
		b = FPU_भाग_small(&ll, 10);
		b |= (FPU_भाग_small(&ll, 10)) << 4;
		RE_ENTRANT_CHECK_OFF;
		FPU_put_user(b, d + i);
		RE_ENTRANT_CHECK_ON;
	पूर्ण
	RE_ENTRANT_CHECK_OFF;
	FPU_put_user(sign, d + 9);
	RE_ENTRANT_CHECK_ON;

	वापस 1;
पूर्ण

/*===========================================================================*/

/* r माला_लो mangled such that sig is पूर्णांक, sign: 
   it is NOT normalized */
/* The वापस value (in eax) is zero अगर the result is exact,
   अगर bits are changed due to rounding, truncation, etc, then
   a non-zero value is वापसed */
/* Overflow is संकेतed by a non-zero वापस value (in eax).
   In the हाल of overflow, the वापसed signअगरicand always has the
   largest possible value */
पूर्णांक FPU_round_to_पूर्णांक(FPU_REG *r, u_अक्षर tag)
अणु
	u_अक्षर very_big;
	अचिन्हित eax;

	अगर (tag == TAG_Zero) अणु
		/* Make sure that zero is वापसed */
		signअगरicand(r) = 0;
		वापस 0;	/* o.k. */
	पूर्ण

	अगर (exponent(r) > 63) अणु
		r->sigl = r->sigh = ~0;	/* The largest representable number */
		वापस 1;	/* overflow */
	पूर्ण

	eax = FPU_shrxs(&r->sigl, 63 - exponent(r));
	very_big = !(~(r->sigh) | ~(r->sigl));	/* test क्रम 0xfff...fff */
#घोषणा	half_or_more	(eax & 0x80000000)
#घोषणा	frac_part	(eax)
#घोषणा more_than_half  ((eax & 0x80000001) == 0x80000001)
	चयन (control_word & CW_RC) अणु
	हाल RC_RND:
		अगर (more_than_half	/* nearest */
		    || (half_or_more && (r->sigl & 1))) अणु	/* odd -> even */
			अगर (very_big)
				वापस 1;	/* overflow */
			signअगरicand(r)++;
			वापस PRECISION_LOST_UP;
		पूर्ण
		अवरोध;
	हाल RC_DOWN:
		अगर (frac_part && माला_लोign(r)) अणु
			अगर (very_big)
				वापस 1;	/* overflow */
			signअगरicand(r)++;
			वापस PRECISION_LOST_UP;
		पूर्ण
		अवरोध;
	हाल RC_UP:
		अगर (frac_part && !माला_लोign(r)) अणु
			अगर (very_big)
				वापस 1;	/* overflow */
			signअगरicand(r)++;
			वापस PRECISION_LOST_UP;
		पूर्ण
		अवरोध;
	हाल RC_CHOP:
		अवरोध;
	पूर्ण

	वापस eax ? PRECISION_LOST_DOWN : 0;

पूर्ण

/*===========================================================================*/

u_अक्षर __user *fldenv(fpu_addr_modes addr_modes, u_अक्षर __user *s)
अणु
	अचिन्हित लघु tag_word = 0;
	u_अक्षर tag;
	पूर्णांक i;

	अगर ((addr_modes.शेष_mode == VM86) ||
	    ((addr_modes.शेष_mode == PM16)
	     ^ (addr_modes.override.opeअक्रम_size == OP_SIZE_PREFIX))) अणु
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(s, 0x0e);
		FPU_get_user(control_word, (अचिन्हित लघु __user *)s);
		FPU_get_user(partial_status, (अचिन्हित लघु __user *)(s + 2));
		FPU_get_user(tag_word, (अचिन्हित लघु __user *)(s + 4));
		FPU_get_user(inकाष्ठाion_address.offset,
			     (अचिन्हित लघु __user *)(s + 6));
		FPU_get_user(inकाष्ठाion_address.selector,
			     (अचिन्हित लघु __user *)(s + 8));
		FPU_get_user(opeअक्रम_address.offset,
			     (अचिन्हित लघु __user *)(s + 0x0a));
		FPU_get_user(opeअक्रम_address.selector,
			     (अचिन्हित लघु __user *)(s + 0x0c));
		RE_ENTRANT_CHECK_ON;
		s += 0x0e;
		अगर (addr_modes.शेष_mode == VM86) अणु
			inकाष्ठाion_address.offset
			    += (inकाष्ठाion_address.selector & 0xf000) << 4;
			opeअक्रम_address.offset +=
			    (opeअक्रम_address.selector & 0xf000) << 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(s, 0x1c);
		FPU_get_user(control_word, (अचिन्हित लघु __user *)s);
		FPU_get_user(partial_status, (अचिन्हित लघु __user *)(s + 4));
		FPU_get_user(tag_word, (अचिन्हित लघु __user *)(s + 8));
		FPU_get_user(inकाष्ठाion_address.offset,
			     (अचिन्हित दीर्घ __user *)(s + 0x0c));
		FPU_get_user(inकाष्ठाion_address.selector,
			     (अचिन्हित लघु __user *)(s + 0x10));
		FPU_get_user(inकाष्ठाion_address.opcode,
			     (अचिन्हित लघु __user *)(s + 0x12));
		FPU_get_user(opeअक्रम_address.offset,
			     (अचिन्हित दीर्घ __user *)(s + 0x14));
		FPU_get_user(opeअक्रम_address.selector,
			     (अचिन्हित दीर्घ __user *)(s + 0x18));
		RE_ENTRANT_CHECK_ON;
		s += 0x1c;
	पूर्ण

#अगर_घोषित PECULIAR_486
	control_word &= ~0xe080;
#पूर्ण_अगर /* PECULIAR_486 */

	top = (partial_status >> SW_Top_Shअगरt) & 7;

	अगर (partial_status & ~control_word & CW_Exceptions)
		partial_status |= (SW_Summary | SW_Backward);
	अन्यथा
		partial_status &= ~(SW_Summary | SW_Backward);

	क्रम (i = 0; i < 8; i++) अणु
		tag = tag_word & 3;
		tag_word >>= 2;

		अगर (tag == TAG_Empty)
			/* New tag is empty.  Accept it */
			FPU_settag(i, TAG_Empty);
		अन्यथा अगर (FPU_gettag(i) == TAG_Empty) अणु
			/* Old tag is empty and new tag is not empty.  New tag is determined
			   by old reg contents */
			अगर (exponent(&fpu_रेजिस्टर(i)) == -EXTENDED_Ebias) अणु
				अगर (!
				    (fpu_रेजिस्टर(i).sigl | fpu_रेजिस्टर(i).
				     sigh))
					FPU_settag(i, TAG_Zero);
				अन्यथा
					FPU_settag(i, TAG_Special);
			पूर्ण अन्यथा अगर (exponent(&fpu_रेजिस्टर(i)) ==
				   0x7fff - EXTENDED_Ebias) अणु
				FPU_settag(i, TAG_Special);
			पूर्ण अन्यथा अगर (fpu_रेजिस्टर(i).sigh & 0x80000000)
				FPU_settag(i, TAG_Valid);
			अन्यथा
				FPU_settag(i, TAG_Special);	/* An Un-normal */
		पूर्ण
		/* Else old tag is not empty and new tag is not empty.  Old tag
		   reमुख्यs correct */
	पूर्ण

	वापस s;
पूर्ण

व्योम frstor(fpu_addr_modes addr_modes, u_अक्षर __user *data_address)
अणु
	पूर्णांक i, regnr;
	u_अक्षर __user *s = fldenv(addr_modes, data_address);
	पूर्णांक offset = (top & 7) * 10, other = 80 - offset;

	/* Copy all रेजिस्टरs in stack order. */
	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(s, 80);
	FPU_copy_from_user(रेजिस्टर_base + offset, s, other);
	अगर (offset)
		FPU_copy_from_user(रेजिस्टर_base, s + other, offset);
	RE_ENTRANT_CHECK_ON;

	क्रम (i = 0; i < 8; i++) अणु
		regnr = (i + top) & 7;
		अगर (FPU_gettag(regnr) != TAG_Empty)
			/* The loaded data over-rides all other हालs. */
			FPU_settag(regnr, FPU_tagof(&st(i)));
	पूर्ण

पूर्ण

u_अक्षर __user *fstenv(fpu_addr_modes addr_modes, u_अक्षर __user *d)
अणु
	अगर ((addr_modes.शेष_mode == VM86) ||
	    ((addr_modes.शेष_mode == PM16)
	     ^ (addr_modes.override.opeअक्रम_size == OP_SIZE_PREFIX))) अणु
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(d, 14);
#अगर_घोषित PECULIAR_486
		FPU_put_user(control_word & ~0xe080, (अचिन्हित दीर्घ __user *)d);
#अन्यथा
		FPU_put_user(control_word, (अचिन्हित लघु __user *)d);
#पूर्ण_अगर /* PECULIAR_486 */
		FPU_put_user(status_word(), (अचिन्हित लघु __user *)(d + 2));
		FPU_put_user(fpu_tag_word, (अचिन्हित लघु __user *)(d + 4));
		FPU_put_user(inकाष्ठाion_address.offset,
			     (अचिन्हित लघु __user *)(d + 6));
		FPU_put_user(opeअक्रम_address.offset,
			     (अचिन्हित लघु __user *)(d + 0x0a));
		अगर (addr_modes.शेष_mode == VM86) अणु
			FPU_put_user((inकाष्ठाion_address.
				      offset & 0xf0000) >> 4,
				     (अचिन्हित लघु __user *)(d + 8));
			FPU_put_user((opeअक्रम_address.offset & 0xf0000) >> 4,
				     (अचिन्हित लघु __user *)(d + 0x0c));
		पूर्ण अन्यथा अणु
			FPU_put_user(inकाष्ठाion_address.selector,
				     (अचिन्हित लघु __user *)(d + 8));
			FPU_put_user(opeअक्रम_address.selector,
				     (अचिन्हित लघु __user *)(d + 0x0c));
		पूर्ण
		RE_ENTRANT_CHECK_ON;
		d += 0x0e;
	पूर्ण अन्यथा अणु
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(d, 7 * 4);
#अगर_घोषित PECULIAR_486
		control_word &= ~0xe080;
		/* An 80486 sets nearly all of the reserved bits to 1. */
		control_word |= 0xffff0040;
		partial_status = status_word() | 0xffff0000;
		fpu_tag_word |= 0xffff0000;
		I387->soft.fcs &= ~0xf8000000;
		I387->soft.fos |= 0xffff0000;
#पूर्ण_अगर /* PECULIAR_486 */
		अगर (__copy_to_user(d, &control_word, 7 * 4))
			FPU_पात;
		RE_ENTRANT_CHECK_ON;
		d += 0x1c;
	पूर्ण

	control_word |= CW_Exceptions;
	partial_status &= ~(SW_Summary | SW_Backward);

	वापस d;
पूर्ण

व्योम fsave(fpu_addr_modes addr_modes, u_अक्षर __user *data_address)
अणु
	u_अक्षर __user *d;
	पूर्णांक offset = (top & 7) * 10, other = 80 - offset;

	d = fstenv(addr_modes, data_address);

	RE_ENTRANT_CHECK_OFF;
	FPU_access_ok(d, 80);

	/* Copy all रेजिस्टरs in stack order. */
	अगर (__copy_to_user(d, रेजिस्टर_base + offset, other))
		FPU_पात;
	अगर (offset)
		अगर (__copy_to_user(d + other, रेजिस्टर_base, offset))
			FPU_पात;
	RE_ENTRANT_CHECK_ON;

	finit();
पूर्ण

/*===========================================================================*/
