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
fवर्ग_मूलs(व्योम *frD, व्योम *frB)
अणु
	FP_DECL_D(B);
	FP_DECL_D(R);
	FP_DECL_EX;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %p %p %p %p\n", __func__, frD, frB);
#पूर्ण_अगर

	FP_UNPACK_DP(B, frB);

#अगर_घोषित DEBUG
	prपूर्णांकk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
#पूर्ण_अगर

	अगर (B_s && B_c != FP_CLS_ZERO)
		FP_SET_EXCEPTION(EFLAG_VXSQRT);
	अगर (B_c == FP_CLS_न_अंक)
		FP_SET_EXCEPTION(EFLAG_VXSन_अंक);

	FP_SQRT_D(R, B);

#अगर_घोषित DEBUG
	prपूर्णांकk("R: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#पूर्ण_अगर

	__FP_PACK_DS(frD, R);

	वापस FP_CUR_EXCEPTIONS;
पूर्ण
