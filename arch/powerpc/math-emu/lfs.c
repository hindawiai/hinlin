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
lfs(व्योम *frD, व्योम *ea)
अणु
	FP_DECL_D(R);
	FP_DECL_S(A);
	FP_DECL_EX;
	भग्न f;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: D %p, ea %p\n", __func__, frD, ea);
#पूर्ण_अगर

	अगर (copy_from_user(&f, ea, माप(भग्न)))
		वापस -EFAULT;

	FP_UNPACK_S(A, f);

#अगर_घोषित DEBUG
	prपूर्णांकk("A: %ld %lu %ld (%ld) [%08lx]\n", A_s, A_f, A_e, A_c,
	       *(अचिन्हित दीर्घ *)&f);
#पूर्ण_अगर

	FP_CONV(D, S, 2, 1, R, A);

#अगर_घोषित DEBUG
	prपूर्णांकk("R: %ld %lu %lu %ld (%ld)\n", R_s, R_f1, R_f0, R_e, R_c);
#पूर्ण_अगर

	अगर (R_c == FP_CLS_न_अंक) अणु
		R_e = _FP_EXPMAX_D;
		_FP_PACK_RAW_2_P(D, frD, R);
	पूर्ण अन्यथा अणु
		__FP_PACK_D(frD, R);
	पूर्ण

	वापस 0;
पूर्ण
