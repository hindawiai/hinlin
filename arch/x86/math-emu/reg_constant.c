<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_स्थिरant.c                                                           |
 |                                                                           |
 | All of the स्थिरant FPU_REGs                                              |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                     W. Metzenthen, 22 Parker St, Ormond, Vic 3163,        |
 |                     Australia.  E-mail   billm@suburbia.net               |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_system.h"
#समावेश "fpu_emu.h"
#समावेश "status_w.h"
#समावेश "reg_constant.h"
#समावेश "control_w.h"

#घोषणा MAKE_REG(s, e, l, h) अणु l, h, \
		(u16)((EXTENDED_Ebias+(e)) | ((SIGN_##s != 0)*0x8000)) पूर्ण

FPU_REG स्थिर CONST_1 = MAKE_REG(POS, 0, 0x00000000, 0x80000000);
#अगर 0
FPU_REG स्थिर CONST_2 = MAKE_REG(POS, 1, 0x00000000, 0x80000000);
FPU_REG स्थिर CONST_HALF = MAKE_REG(POS, -1, 0x00000000, 0x80000000);
#पूर्ण_अगर /*  0  */
अटल FPU_REG स्थिर CONST_L2T = MAKE_REG(POS, 1, 0xcd1b8afe, 0xd49a784b);
अटल FPU_REG स्थिर CONST_L2E = MAKE_REG(POS, 0, 0x5c17f0bc, 0xb8aa3b29);
FPU_REG स्थिर CONST_PI = MAKE_REG(POS, 1, 0x2168c235, 0xc90fdaa2);
FPU_REG स्थिर CONST_PI2 = MAKE_REG(POS, 0, 0x2168c235, 0xc90fdaa2);
FPU_REG स्थिर CONST_PI4 = MAKE_REG(POS, -1, 0x2168c235, 0xc90fdaa2);
अटल FPU_REG स्थिर CONST_LG2 = MAKE_REG(POS, -2, 0xfbcff799, 0x9a209a84);
अटल FPU_REG स्थिर CONST_LN2 = MAKE_REG(POS, -1, 0xd1cf79ac, 0xb17217f7);

/* Extra bits to take pi/2 to more than 128 bits precision. */
FPU_REG स्थिर CONST_PI2extra = MAKE_REG(NEG, -66,
					0xfc8f8cbb, 0xece675d1);

/* Only the sign (and tag) is used in पूर्णांकernal zeroes */
FPU_REG स्थिर CONST_Z = MAKE_REG(POS, EXP_UNDER, 0x0, 0x0);

/* Only the sign and signअगरicand (and tag) are used in पूर्णांकernal NaNs */
/* The 80486 never generates one of these
FPU_REG स्थिर CONST_Sन_अंक = MAKE_REG(POS, EXP_OVER, 0x00000001, 0x80000000);
 */
/* This is the real indefinite QNaN */
FPU_REG स्थिर CONST_QNaN = MAKE_REG(NEG, EXP_OVER, 0x00000000, 0xC0000000);

/* Only the sign (and tag) is used in पूर्णांकernal infinities */
FPU_REG स्थिर CONST_INF = MAKE_REG(POS, EXP_OVER, 0x00000000, 0x80000000);

अटल व्योम fld_स्थिर(FPU_REG स्थिर * c, पूर्णांक adj, u_अक्षर tag)
अणु
	FPU_REG *st_new_ptr;

	अगर (STACK_OVERFLOW) अणु
		FPU_stack_overflow();
		वापस;
	पूर्ण
	push();
	reg_copy(c, st_new_ptr);
	st_new_ptr->sigl += adj;	/* For all our fldxxx स्थिरants, we करोn't need to
					   borrow or carry. */
	FPU_settag0(tag);
	clear_C1();
पूर्ण

/* A fast way to find out whether x is one of RC_DOWN or RC_CHOP
   (and not one of RC_RND or RC_UP).
   */
#घोषणा DOWN_OR_CHOP(x)  (x & RC_DOWN)

अटल व्योम fld1(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_1, 0, TAG_Valid);
पूर्ण

अटल व्योम fldl2t(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_L2T, (rc == RC_UP) ? 1 : 0, TAG_Valid);
पूर्ण

अटल व्योम fldl2e(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_L2E, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
पूर्ण

अटल व्योम fldpi(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_PI, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
पूर्ण

अटल व्योम fldlg2(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_LG2, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
पूर्ण

अटल व्योम fldln2(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_LN2, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
पूर्ण

अटल व्योम fldz(पूर्णांक rc)
अणु
	fld_स्थिर(&CONST_Z, 0, TAG_Zero);
पूर्ण

प्रकार व्योम (*FUNC_RC) (पूर्णांक);

अटल FUNC_RC स्थिरants_table[] = अणु
	fld1, fldl2t, fldl2e, fldpi, fldlg2, fldln2, fldz, (FUNC_RC) FPU_illegal
पूर्ण;

व्योम fस्थिर(व्योम)
अणु
	(स्थिरants_table[FPU_rm]) (control_word & CW_RC);
पूर्ण
