<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  fpu_arith.c                                                              |
 |                                                                           |
 | Code to implement the FPU रेजिस्टर/रेजिस्टर arithmetic inकाष्ठाions       |
 |                                                                           |
 | Copyright (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "fpu_system.h"
#समावेश "fpu_emu.h"
#समावेश "control_w.h"
#समावेश "status_w.h"

व्योम fadd__(व्योम)
अणु
	/* fadd st,st(i) */
	पूर्णांक i = FPU_rm;
	clear_C1();
	FPU_add(&st(i), FPU_gettagi(i), 0, control_word);
पूर्ण

व्योम fmul__(व्योम)
अणु
	/* fmul st,st(i) */
	पूर्णांक i = FPU_rm;
	clear_C1();
	FPU_mul(&st(i), FPU_gettagi(i), 0, control_word);
पूर्ण

व्योम fsub__(व्योम)
अणु
	/* fsub st,st(i) */
	clear_C1();
	FPU_sub(0, FPU_rm, control_word);
पूर्ण

व्योम fsubr_(व्योम)
अणु
	/* fsubr st,st(i) */
	clear_C1();
	FPU_sub(REV, FPU_rm, control_word);
पूर्ण

व्योम fभाग__(व्योम)
अणु
	/* fभाग st,st(i) */
	clear_C1();
	FPU_भाग(0, FPU_rm, control_word);
पूर्ण

व्योम fभागr_(व्योम)
अणु
	/* fभागr st,st(i) */
	clear_C1();
	FPU_भाग(REV, FPU_rm, control_word);
पूर्ण

व्योम fadd_i(व्योम)
अणु
	/* fadd st(i),st */
	पूर्णांक i = FPU_rm;
	clear_C1();
	FPU_add(&st(i), FPU_gettagi(i), i, control_word);
पूर्ण

व्योम fmul_i(व्योम)
अणु
	/* fmul st(i),st */
	clear_C1();
	FPU_mul(&st(0), FPU_gettag0(), FPU_rm, control_word);
पूर्ण

व्योम fsubri(व्योम)
अणु
	/* fsubr st(i),st */
	clear_C1();
	FPU_sub(DEST_RM, FPU_rm, control_word);
पूर्ण

व्योम fsub_i(व्योम)
अणु
	/* fsub st(i),st */
	clear_C1();
	FPU_sub(REV | DEST_RM, FPU_rm, control_word);
पूर्ण

व्योम fभागri(व्योम)
अणु
	/* fभागr st(i),st */
	clear_C1();
	FPU_भाग(DEST_RM, FPU_rm, control_word);
पूर्ण

व्योम fभाग_i(व्योम)
अणु
	/* fभाग st(i),st */
	clear_C1();
	FPU_भाग(REV | DEST_RM, FPU_rm, control_word);
पूर्ण

व्योम faddp_(व्योम)
अणु
	/* faddp st(i),st */
	पूर्णांक i = FPU_rm;
	clear_C1();
	अगर (FPU_add(&st(i), FPU_gettagi(i), i, control_word) >= 0)
		FPU_pop();
पूर्ण

व्योम fmulp_(व्योम)
अणु
	/* fmulp st(i),st */
	clear_C1();
	अगर (FPU_mul(&st(0), FPU_gettag0(), FPU_rm, control_word) >= 0)
		FPU_pop();
पूर्ण

व्योम fsubrp(व्योम)
अणु
	/* fsubrp st(i),st */
	clear_C1();
	अगर (FPU_sub(DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
पूर्ण

व्योम fsubp_(व्योम)
अणु
	/* fsubp st(i),st */
	clear_C1();
	अगर (FPU_sub(REV | DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
पूर्ण

व्योम fभागrp(व्योम)
अणु
	/* fभागrp st(i),st */
	clear_C1();
	अगर (FPU_भाग(DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
पूर्ण

व्योम fभागp_(व्योम)
अणु
	/* fभागp st(i),st */
	clear_C1();
	अगर (FPU_भाग(REV | DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
पूर्ण
