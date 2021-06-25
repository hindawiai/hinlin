<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>

पूर्णांक
fctiw(u32 *frD, व्योम *frB)
अणु
	FP_DECL_D(B);
	FP_DECL_EX;
	अचिन्हित पूर्णांक r;

	FP_UNPACK_DP(B, frB);
	FP_TO_INT_D(r, B, 32, 1);
	frD[1] = r;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: D %p, B %p: ", __func__, frD, frB);
	dump_द्विगुन(frD);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण
