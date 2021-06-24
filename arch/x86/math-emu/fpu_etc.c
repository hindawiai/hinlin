<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  fpu_etc.c                                                                |
 |                                                                           |
 | Implement a few FPU inकाष्ठाions.                                         |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@suburbia.net             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "fpu_emu.h"
#समावेश "status_w.h"
#समावेश "reg_constant.h"

अटल व्योम fchs(FPU_REG *st0_ptr, u_अक्षर st0tag)
अणु
	अगर (st0tag ^ TAG_Empty) अणु
		signbyte(st0_ptr) ^= SIGN_NEG;
		clear_C1();
	पूर्ण अन्यथा
		FPU_stack_underflow();
पूर्ण

अटल व्योम भ_असल(FPU_REG *st0_ptr, u_अक्षर st0tag)
अणु
	अगर (st0tag ^ TAG_Empty) अणु
		setpositive(st0_ptr);
		clear_C1();
	पूर्ण अन्यथा
		FPU_stack_underflow();
पूर्ण

अटल व्योम ftst_(FPU_REG *st0_ptr, u_अक्षर st0tag)
अणु
	चयन (st0tag) अणु
	हाल TAG_Zero:
		setcc(SW_C3);
		अवरोध;
	हाल TAG_Valid:
		अगर (माला_लोign(st0_ptr) == SIGN_POS)
			setcc(0);
		अन्यथा
			setcc(SW_C0);
		अवरोध;
	हाल TAG_Special:
		चयन (FPU_Special(st0_ptr)) अणु
		हाल TW_Denormal:
			अगर (माला_लोign(st0_ptr) == SIGN_POS)
				setcc(0);
			अन्यथा
				setcc(SW_C0);
			अगर (denormal_opeअक्रम() < 0) अणु
#अगर_घोषित PECULIAR_486
				/* This is weird! */
				अगर (माला_लोign(st0_ptr) == SIGN_POS)
					setcc(SW_C3);
#पूर्ण_अगर /* PECULIAR_486 */
				वापस;
			पूर्ण
			अवरोध;
		हाल TW_NaN:
			setcc(SW_C0 | SW_C2 | SW_C3);	/* Opeअक्रम is not comparable */
			EXCEPTION(EX_Invalid);
			अवरोध;
		हाल TW_Infinity:
			अगर (माला_लोign(st0_ptr) == SIGN_POS)
				setcc(0);
			अन्यथा
				setcc(SW_C0);
			अवरोध;
		शेष:
			setcc(SW_C0 | SW_C2 | SW_C3);	/* Opeअक्रम is not comparable */
			EXCEPTION(EX_INTERNAL | 0x14);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल TAG_Empty:
		setcc(SW_C0 | SW_C2 | SW_C3);
		EXCEPTION(EX_StackUnder);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fxam(FPU_REG *st0_ptr, u_अक्षर st0tag)
अणु
	पूर्णांक c = 0;
	चयन (st0tag) अणु
	हाल TAG_Empty:
		c = SW_C3 | SW_C0;
		अवरोध;
	हाल TAG_Zero:
		c = SW_C3;
		अवरोध;
	हाल TAG_Valid:
		c = SW_C2;
		अवरोध;
	हाल TAG_Special:
		चयन (FPU_Special(st0_ptr)) अणु
		हाल TW_Denormal:
			c = SW_C2 | SW_C3;	/* Denormal */
			अवरोध;
		हाल TW_NaN:
			/* We also use NaN क्रम unsupported types. */
			अगर ((st0_ptr->sigh & 0x80000000)
			    && (exponent(st0_ptr) == EXP_OVER))
				c = SW_C0;
			अवरोध;
		हाल TW_Infinity:
			c = SW_C2 | SW_C0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (माला_लोign(st0_ptr) == SIGN_NEG)
		c |= SW_C1;
	setcc(c);
पूर्ण

अटल FUNC_ST0 स्थिर fp_etc_table[] = अणु
	fchs, भ_असल, (FUNC_ST0) FPU_illegal, (FUNC_ST0) FPU_illegal,
	ftst_, fxam, (FUNC_ST0) FPU_illegal, (FUNC_ST0) FPU_illegal
पूर्ण;

व्योम FPU_etc(व्योम)
अणु
	(fp_etc_table[FPU_rm]) (&st(0), FPU_gettag0());
पूर्ण
