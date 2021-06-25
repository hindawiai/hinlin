<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>
#समावेश <math-emu/single.h>

पूर्णांक
fभागs(व्योम *frD, व्योम *frA, व्योम *frB)
अणु
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_D(R);
	FP_DECL_EX;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %p %p %p\n", __func__, frD, frA, frB);
#पूर्ण_अगर

	FP_UNPACK_DP(A, frA);
	FP_UNPACK_DP(B, frB);

#अगर_घोषित DEBUG
	prपूर्णांकk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
	prपूर्णांकk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
#पूर्ण_अगर

	अगर (A_c == FP_CLS_ZERO && B_c == FP_CLS_ZERO) अणु
		FP_SET_EXCEPTION(EFLAG_VXZDZ);
#अगर_घोषित DEBUG
		prपूर्णांकk("%s: FPSCR_VXZDZ raised\n", __func__);
#पूर्ण_अगर
	पूर्ण
	अगर (A_c == FP_CLS_INF && B_c == FP_CLS_INF) अणु
		FP_SET_EXCEPTION(EFLAG_VXIDI);
#अगर_घोषित DEBUG
		prपूर्णांकk("%s: FPSCR_VXIDI raised\n", __func__);
#पूर्ण_अगर
	पूर्ण

	अगर (B_c == FP_CLS_ZERO && A_c != FP_CLS_ZERO) अणु
		FP_SET_EXCEPTION(EFLAG_DIVZERO);
		अगर (__FPU_TRAP_P(EFLAG_DIVZERO))
			वापस FP_CUR_EXCEPTIONS;
	पूर्ण

	FP_DIV_D(R, A, B);

#अगर_घोषित DEBUG
	prपूर्णांकk("D: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#पूर्ण_अगर

	__FP_PACK_DS(frD, R);

	वापस FP_CUR_EXCEPTIONS;
पूर्ण
