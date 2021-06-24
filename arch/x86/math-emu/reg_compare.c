<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_compare.c                                                            |
 |                                                                           |
 | Compare two भग्नing poपूर्णांक रेजिस्टरs                                      |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | compare() is the core FPU_REG comparison function                         |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "fpu_emu.h"
#समावेश "control_w.h"
#समावेश "status_w.h"

अटल पूर्णांक compare(FPU_REG स्थिर *b, पूर्णांक tagb)
अणु
	पूर्णांक dअगरf, exp0, expb;
	u_अक्षर st0_tag;
	FPU_REG *st0_ptr;
	FPU_REG x, y;
	u_अक्षर st0_sign, signb = माला_लोign(b);

	st0_ptr = &st(0);
	st0_tag = FPU_gettag0();
	st0_sign = माला_लोign(st0_ptr);

	अगर (tagb == TAG_Special)
		tagb = FPU_Special(b);
	अगर (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	अगर (((st0_tag != TAG_Valid) && (st0_tag != TW_Denormal))
	    || ((tagb != TAG_Valid) && (tagb != TW_Denormal))) अणु
		अगर (st0_tag == TAG_Zero) अणु
			अगर (tagb == TAG_Zero)
				वापस COMP_A_eq_B;
			अगर (tagb == TAG_Valid)
				वापस ((signb ==
					 SIGN_POS) ? COMP_A_lt_B : COMP_A_gt_B);
			अगर (tagb == TW_Denormal)
				वापस ((signb ==
					 SIGN_POS) ? COMP_A_lt_B : COMP_A_gt_B)
				    | COMP_Denormal;
		पूर्ण अन्यथा अगर (tagb == TAG_Zero) अणु
			अगर (st0_tag == TAG_Valid)
				वापस ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B);
			अगर (st0_tag == TW_Denormal)
				वापस ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B)
				    | COMP_Denormal;
		पूर्ण

		अगर (st0_tag == TW_Infinity) अणु
			अगर ((tagb == TAG_Valid) || (tagb == TAG_Zero))
				वापस ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B);
			अन्यथा अगर (tagb == TW_Denormal)
				वापस ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B)
				    | COMP_Denormal;
			अन्यथा अगर (tagb == TW_Infinity) अणु
				/* The 80486 book says that infinities can be equal! */
				वापस (st0_sign == signb) ? COMP_A_eq_B :
				    ((st0_sign ==
				      SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B);
			पूर्ण
			/* Fall through to the NaN code */
		पूर्ण अन्यथा अगर (tagb == TW_Infinity) अणु
			अगर ((st0_tag == TAG_Valid) || (st0_tag == TAG_Zero))
				वापस ((signb ==
					 SIGN_POS) ? COMP_A_lt_B : COMP_A_gt_B);
			अगर (st0_tag == TW_Denormal)
				वापस ((signb ==
					 SIGN_POS) ? COMP_A_lt_B : COMP_A_gt_B)
				    | COMP_Denormal;
			/* Fall through to the NaN code */
		पूर्ण

		/* The only possibility now should be that one of the arguments
		   is a NaN */
		अगर ((st0_tag == TW_NaN) || (tagb == TW_NaN)) अणु
			पूर्णांक संकेतling = 0, unsupported = 0;
			अगर (st0_tag == TW_NaN) अणु
				संकेतling =
				    (st0_ptr->sigh & 0xc0000000) == 0x80000000;
				unsupported = !((exponent(st0_ptr) == EXP_OVER)
						&& (st0_ptr->
						    sigh & 0x80000000));
			पूर्ण
			अगर (tagb == TW_NaN) अणु
				संकेतling |=
				    (b->sigh & 0xc0000000) == 0x80000000;
				unsupported |= !((exponent(b) == EXP_OVER)
						 && (b->sigh & 0x80000000));
			पूर्ण
			अगर (संकेतling || unsupported)
				वापस COMP_No_Comp | COMP_SNaN | COMP_NaN;
			अन्यथा
				/* Neither is a संकेतing NaN */
				वापस COMP_No_Comp | COMP_NaN;
		पूर्ण

		EXCEPTION(EX_Invalid);
	पूर्ण

	अगर (st0_sign != signb) अणु
		वापस ((st0_sign == SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B)
		    | (((st0_tag == TW_Denormal) || (tagb == TW_Denormal)) ?
		       COMP_Denormal : 0);
	पूर्ण

	अगर ((st0_tag == TW_Denormal) || (tagb == TW_Denormal)) अणु
		FPU_to_exp16(st0_ptr, &x);
		FPU_to_exp16(b, &y);
		st0_ptr = &x;
		b = &y;
		exp0 = exponent16(st0_ptr);
		expb = exponent16(b);
	पूर्ण अन्यथा अणु
		exp0 = exponent(st0_ptr);
		expb = exponent(b);
	पूर्ण

#अगर_घोषित PARANOID
	अगर (!(st0_ptr->sigh & 0x80000000))
		EXCEPTION(EX_Invalid);
	अगर (!(b->sigh & 0x80000000))
		EXCEPTION(EX_Invalid);
#पूर्ण_अगर /* PARANOID */

	dअगरf = exp0 - expb;
	अगर (dअगरf == 0) अणु
		dअगरf = st0_ptr->sigh - b->sigh;	/* Works only अगर ms bits are
						   identical */
		अगर (dअगरf == 0) अणु
			dअगरf = st0_ptr->sigl > b->sigl;
			अगर (dअगरf == 0)
				dअगरf = -(st0_ptr->sigl < b->sigl);
		पूर्ण
	पूर्ण

	अगर (dअगरf > 0) अणु
		वापस ((st0_sign == SIGN_POS) ? COMP_A_gt_B : COMP_A_lt_B)
		    | (((st0_tag == TW_Denormal) || (tagb == TW_Denormal)) ?
		       COMP_Denormal : 0);
	पूर्ण
	अगर (dअगरf < 0) अणु
		वापस ((st0_sign == SIGN_POS) ? COMP_A_lt_B : COMP_A_gt_B)
		    | (((st0_tag == TW_Denormal) || (tagb == TW_Denormal)) ?
		       COMP_Denormal : 0);
	पूर्ण

	वापस COMP_A_eq_B
	    | (((st0_tag == TW_Denormal) || (tagb == TW_Denormal)) ?
	       COMP_Denormal : 0);

पूर्ण

/* This function requires that st(0) is not empty */
पूर्णांक FPU_compare_st_data(FPU_REG स्थिर *loaded_data, u_अक्षर loaded_tag)
अणु
	पूर्णांक f, c;

	c = compare(loaded_data, loaded_tag);

	अगर (c & COMP_NaN) अणु
		EXCEPTION(EX_Invalid);
		f = SW_C3 | SW_C2 | SW_C0;
	पूर्ण अन्यथा
		चयन (c & 7) अणु
		हाल COMP_A_lt_B:
			f = SW_C0;
			अवरोध;
		हाल COMP_A_eq_B:
			f = SW_C3;
			अवरोध;
		हाल COMP_A_gt_B:
			f = 0;
			अवरोध;
		हाल COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			अवरोध;
		शेष:
#अगर_घोषित PARANOID
			EXCEPTION(EX_INTERNAL | 0x121);
#पूर्ण_अगर /* PARANOID */
			f = SW_C3 | SW_C2 | SW_C0;
			अवरोध;
		पूर्ण
	setcc(f);
	अगर (c & COMP_Denormal) अणु
		वापस denormal_opeअक्रम() < 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compare_st_st(पूर्णांक nr)
अणु
	पूर्णांक f, c;
	FPU_REG *st_ptr;

	अगर (!NOT_EMPTY(0) || !NOT_EMPTY(nr)) अणु
		setcc(SW_C3 | SW_C2 | SW_C0);
		/* Stack fault */
		EXCEPTION(EX_StackUnder);
		वापस !(control_word & CW_Invalid);
	पूर्ण

	st_ptr = &st(nr);
	c = compare(st_ptr, FPU_gettagi(nr));
	अगर (c & COMP_NaN) अणु
		setcc(SW_C3 | SW_C2 | SW_C0);
		EXCEPTION(EX_Invalid);
		वापस !(control_word & CW_Invalid);
	पूर्ण अन्यथा
		चयन (c & 7) अणु
		हाल COMP_A_lt_B:
			f = SW_C0;
			अवरोध;
		हाल COMP_A_eq_B:
			f = SW_C3;
			अवरोध;
		हाल COMP_A_gt_B:
			f = 0;
			अवरोध;
		हाल COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			अवरोध;
		शेष:
#अगर_घोषित PARANOID
			EXCEPTION(EX_INTERNAL | 0x122);
#पूर्ण_अगर /* PARANOID */
			f = SW_C3 | SW_C2 | SW_C0;
			अवरोध;
		पूर्ण
	setcc(f);
	अगर (c & COMP_Denormal) अणु
		वापस denormal_opeअक्रम() < 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compare_i_st_st(पूर्णांक nr)
अणु
	पूर्णांक f, c;
	FPU_REG *st_ptr;

	अगर (!NOT_EMPTY(0) || !NOT_EMPTY(nr)) अणु
		FPU_EFLAGS |= (X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF);
		/* Stack fault */
		EXCEPTION(EX_StackUnder);
		वापस !(control_word & CW_Invalid);
	पूर्ण

	partial_status &= ~SW_C0;
	st_ptr = &st(nr);
	c = compare(st_ptr, FPU_gettagi(nr));
	अगर (c & COMP_NaN) अणु
		FPU_EFLAGS |= (X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF);
		EXCEPTION(EX_Invalid);
		वापस !(control_word & CW_Invalid);
	पूर्ण

	चयन (c & 7) अणु
	हाल COMP_A_lt_B:
		f = X86_EFLAGS_CF;
		अवरोध;
	हाल COMP_A_eq_B:
		f = X86_EFLAGS_ZF;
		अवरोध;
	हाल COMP_A_gt_B:
		f = 0;
		अवरोध;
	हाल COMP_No_Comp:
		f = X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF;
		अवरोध;
	शेष:
#अगर_घोषित PARANOID
		EXCEPTION(EX_INTERNAL | 0x122);
#पूर्ण_अगर /* PARANOID */
		f = 0;
		अवरोध;
	पूर्ण
	FPU_EFLAGS = (FPU_EFLAGS & ~(X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF)) | f;
	अगर (c & COMP_Denormal) अणु
		वापस denormal_opeअक्रम() < 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compare_u_st_st(पूर्णांक nr)
अणु
	पूर्णांक f = 0, c;
	FPU_REG *st_ptr;

	अगर (!NOT_EMPTY(0) || !NOT_EMPTY(nr)) अणु
		setcc(SW_C3 | SW_C2 | SW_C0);
		/* Stack fault */
		EXCEPTION(EX_StackUnder);
		वापस !(control_word & CW_Invalid);
	पूर्ण

	st_ptr = &st(nr);
	c = compare(st_ptr, FPU_gettagi(nr));
	अगर (c & COMP_NaN) अणु
		setcc(SW_C3 | SW_C2 | SW_C0);
		अगर (c & COMP_SNaN) अणु	/* This is the only dअगरference between
					   un-ordered and ordinary comparisons */
			EXCEPTION(EX_Invalid);
			वापस !(control_word & CW_Invalid);
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा
		चयन (c & 7) अणु
		हाल COMP_A_lt_B:
			f = SW_C0;
			अवरोध;
		हाल COMP_A_eq_B:
			f = SW_C3;
			अवरोध;
		हाल COMP_A_gt_B:
			f = 0;
			अवरोध;
		हाल COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			अवरोध;
#अगर_घोषित PARANOID
		शेष:
			EXCEPTION(EX_INTERNAL | 0x123);
			f = SW_C3 | SW_C2 | SW_C0;
			अवरोध;
#पूर्ण_अगर /* PARANOID */
		पूर्ण
	setcc(f);
	अगर (c & COMP_Denormal) अणु
		वापस denormal_opeअक्रम() < 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compare_ui_st_st(पूर्णांक nr)
अणु
	पूर्णांक f = 0, c;
	FPU_REG *st_ptr;

	अगर (!NOT_EMPTY(0) || !NOT_EMPTY(nr)) अणु
		FPU_EFLAGS |= (X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF);
		/* Stack fault */
		EXCEPTION(EX_StackUnder);
		वापस !(control_word & CW_Invalid);
	पूर्ण

	partial_status &= ~SW_C0;
	st_ptr = &st(nr);
	c = compare(st_ptr, FPU_gettagi(nr));
	अगर (c & COMP_NaN) अणु
		FPU_EFLAGS |= (X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF);
		अगर (c & COMP_SNaN) अणु	/* This is the only dअगरference between
					   un-ordered and ordinary comparisons */
			EXCEPTION(EX_Invalid);
			वापस !(control_word & CW_Invalid);
		पूर्ण
		वापस 0;
	पूर्ण

	चयन (c & 7) अणु
	हाल COMP_A_lt_B:
		f = X86_EFLAGS_CF;
		अवरोध;
	हाल COMP_A_eq_B:
		f = X86_EFLAGS_ZF;
		अवरोध;
	हाल COMP_A_gt_B:
		f = 0;
		अवरोध;
	हाल COMP_No_Comp:
		f = X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF;
		अवरोध;
#अगर_घोषित PARANOID
	शेष:
		EXCEPTION(EX_INTERNAL | 0x123);
		f = 0;
		अवरोध;
#पूर्ण_अगर /* PARANOID */
	पूर्ण
	FPU_EFLAGS = (FPU_EFLAGS & ~(X86_EFLAGS_ZF | X86_EFLAGS_PF | X86_EFLAGS_CF)) | f;
	अगर (c & COMP_Denormal) अणु
		वापस denormal_opeअक्रम() < 0;
	पूर्ण
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/

व्योम fcom_st(व्योम)
अणु
	/* fcom st(i) */
	compare_st_st(FPU_rm);
पूर्ण

व्योम fcompst(व्योम)
अणु
	/* fcomp st(i) */
	अगर (!compare_st_st(FPU_rm))
		FPU_pop();
पूर्ण

व्योम fcompp(व्योम)
अणु
	/* fcompp */
	अगर (FPU_rm != 1) अणु
		FPU_illegal();
		वापस;
	पूर्ण
	अगर (!compare_st_st(1))
		poppop();
पूर्ण

व्योम fucom_(व्योम)
अणु
	/* fucom st(i) */
	compare_u_st_st(FPU_rm);

पूर्ण

व्योम fucomp(व्योम)
अणु
	/* fucomp st(i) */
	अगर (!compare_u_st_st(FPU_rm))
		FPU_pop();
पूर्ण

व्योम fucompp(व्योम)
अणु
	/* fucompp */
	अगर (FPU_rm == 1) अणु
		अगर (!compare_u_st_st(1))
			poppop();
	पूर्ण अन्यथा
		FPU_illegal();
पूर्ण

/* P6+ compare-to-EFLAGS ops */

व्योम fcomi_(व्योम)
अणु
	/* fcomi st(i) */
	compare_i_st_st(FPU_rm);
पूर्ण

व्योम fcomip(व्योम)
अणु
	/* fcomip st(i) */
	अगर (!compare_i_st_st(FPU_rm))
		FPU_pop();
पूर्ण

व्योम fucomi_(व्योम)
अणु
	/* fucomi st(i) */
	compare_ui_st_st(FPU_rm);
पूर्ण

व्योम fucomip(व्योम)
अणु
	/* fucomip st(i) */
	अगर (!compare_ui_st_st(FPU_rm))
		FPU_pop();
पूर्ण
