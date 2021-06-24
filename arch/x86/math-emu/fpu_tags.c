<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  fpu_tags.c                                                               |
 |                                                                           |
 |  Set FPU रेजिस्टर tags.                                                   |
 |                                                                           |
 | Copyright (C) 1997                                                        |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_emu.h"
#समावेश "fpu_system.h"
#समावेश "exception.h"

व्योम FPU_pop(व्योम)
अणु
	fpu_tag_word |= 3 << ((top & 7) * 2);
	top++;
पूर्ण

पूर्णांक FPU_gettag0(व्योम)
अणु
	वापस (fpu_tag_word >> ((top & 7) * 2)) & 3;
पूर्ण

पूर्णांक FPU_gettagi(पूर्णांक stnr)
अणु
	वापस (fpu_tag_word >> (((top + stnr) & 7) * 2)) & 3;
पूर्ण

पूर्णांक FPU_gettag(पूर्णांक regnr)
अणु
	वापस (fpu_tag_word >> ((regnr & 7) * 2)) & 3;
पूर्ण

व्योम FPU_settag0(पूर्णांक tag)
अणु
	पूर्णांक regnr = top;
	regnr &= 7;
	fpu_tag_word &= ~(3 << (regnr * 2));
	fpu_tag_word |= (tag & 3) << (regnr * 2);
पूर्ण

व्योम FPU_settagi(पूर्णांक stnr, पूर्णांक tag)
अणु
	पूर्णांक regnr = stnr + top;
	regnr &= 7;
	fpu_tag_word &= ~(3 << (regnr * 2));
	fpu_tag_word |= (tag & 3) << (regnr * 2);
पूर्ण

व्योम FPU_settag(पूर्णांक regnr, पूर्णांक tag)
अणु
	regnr &= 7;
	fpu_tag_word &= ~(3 << (regnr * 2));
	fpu_tag_word |= (tag & 3) << (regnr * 2);
पूर्ण

पूर्णांक FPU_Special(FPU_REG स्थिर *ptr)
अणु
	पूर्णांक exp = exponent(ptr);

	अगर (exp == EXP_BIAS + EXP_UNDER)
		वापस TW_Denormal;
	अन्यथा अगर (exp != EXP_BIAS + EXP_OVER)
		वापस TW_NaN;
	अन्यथा अगर ((ptr->sigh == 0x80000000) && (ptr->sigl == 0))
		वापस TW_Infinity;
	वापस TW_NaN;
पूर्ण

पूर्णांक isNaN(FPU_REG स्थिर *ptr)
अणु
	वापस ((exponent(ptr) == EXP_BIAS + EXP_OVER)
		&& !((ptr->sigh == 0x80000000) && (ptr->sigl == 0)));
पूर्ण

पूर्णांक FPU_empty_i(पूर्णांक stnr)
अणु
	पूर्णांक regnr = (top + stnr) & 7;

	वापस ((fpu_tag_word >> (regnr * 2)) & 3) == TAG_Empty;
पूर्ण

पूर्णांक FPU_stackoverflow(FPU_REG ** st_new_ptr)
अणु
	*st_new_ptr = &st(-1);

	वापस ((fpu_tag_word >> (((top - 1) & 7) * 2)) & 3) != TAG_Empty;
पूर्ण

व्योम FPU_copy_to_regi(FPU_REG स्थिर *r, u_अक्षर tag, पूर्णांक stnr)
अणु
	reg_copy(r, &st(stnr));
	FPU_settagi(stnr, tag);
पूर्ण

व्योम FPU_copy_to_reg1(FPU_REG स्थिर *r, u_अक्षर tag)
अणु
	reg_copy(r, &st(1));
	FPU_settagi(1, tag);
पूर्ण

व्योम FPU_copy_to_reg0(FPU_REG स्थिर *r, u_अक्षर tag)
अणु
	पूर्णांक regnr = top;
	regnr &= 7;

	reg_copy(r, &st(0));

	fpu_tag_word &= ~(3 << (regnr * 2));
	fpu_tag_word |= (tag & 3) << (regnr * 2);
पूर्ण
