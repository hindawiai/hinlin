<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>

पूर्णांक
fsel(u32 *frD, व्योम *frA, u32 *frB, u32 *frC)
अणु
	FP_DECL_D(A);
	FP_DECL_EX;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %p %p %p %p\n", __func__, frD, frA, frB, frC);
#पूर्ण_अगर

	FP_UNPACK_DP(A, frA);

#अगर_घोषित DEBUG
	prपूर्णांकk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
	prपूर्णांकk("B: %08x %08x\n", frB[0], frB[1]);
	prपूर्णांकk("C: %08x %08x\n", frC[0], frC[1]);
#पूर्ण_अगर

	अगर (A_c == FP_CLS_न_अंक || (A_c != FP_CLS_ZERO && A_s)) अणु
		frD[0] = frB[0];
		frD[1] = frB[1];
	पूर्ण अन्यथा अणु
		frD[0] = frC[0];
		frD[1] = frC[1];
	पूर्ण

#अगर_घोषित DEBUG
	prपूर्णांकk("D: %08x.%08x\n", frD[0], frD[1]);
#पूर्ण_अगर

	वापस 0;
पूर्ण
