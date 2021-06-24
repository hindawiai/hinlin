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
stfs(व्योम *frS, व्योम *ea)
अणु
	FP_DECL_D(A);
	FP_DECL_S(R);
	FP_DECL_EX;
	भग्न f;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: S %p, ea %p\n", __func__, frS, ea);
#पूर्ण_अगर

	FP_UNPACK_DP(A, frS);

#अगर_घोषित DEBUG
	prपूर्णांकk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
#पूर्ण_अगर

	FP_CONV(S, D, 1, 2, R, A);

#अगर_घोषित DEBUG
	prपूर्णांकk("R: %ld %lu %ld (%ld)\n", R_s, R_f, R_e, R_c);
#पूर्ण_अगर

	_FP_PACK_CANONICAL(S, 1, R);
	अगर (!FP_CUR_EXCEPTIONS || !__FPU_TRAP_P(FP_CUR_EXCEPTIONS)) अणु
		_FP_PACK_RAW_1_P(S, &f, R);
		अगर (copy_to_user(ea, &f, माप(भग्न)))
			वापस -EFAULT;
	पूर्ण

	वापस FP_CUR_EXCEPTIONS;
पूर्ण
