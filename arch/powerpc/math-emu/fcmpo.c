<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>

पूर्णांक
fcmpo(u32 *ccr, पूर्णांक crfD, व्योम *frA, व्योम *frB)
अणु
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_EX;
	पूर्णांक code[4] = अणु (1 << 3), (1 << 1), (1 << 2), (1 << 0) पूर्ण;
	दीर्घ cmp;

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %p (%08x) %d %p %p\n", __func__, ccr, *ccr, crfD, frA, frB);
#पूर्ण_अगर

	FP_UNPACK_DP(A, frA);
	FP_UNPACK_DP(B, frB);

#अगर_घोषित DEBUG
	prपूर्णांकk("A: %ld %lu %lu %ld (%ld)\n", A_s, A_f1, A_f0, A_e, A_c);
	prपूर्णांकk("B: %ld %lu %lu %ld (%ld)\n", B_s, B_f1, B_f0, B_e, B_c);
#पूर्ण_अगर

	अगर (A_c == FP_CLS_न_अंक || B_c == FP_CLS_न_अंक)
		FP_SET_EXCEPTION(EFLAG_VXVC);

	FP_CMP_D(cmp, A, B, 2);
	cmp = code[(cmp + 1) & 3];

	__FPU_FPSCR &= ~(0x1f000);
	__FPU_FPSCR |= (cmp << 12);

	*ccr &= ~(15 << ((7 - crfD) << 2));
	*ccr |= (cmp << ((7 - crfD) << 2));

#अगर_घोषित DEBUG
	prपूर्णांकk("CR: %08x\n", *ccr);
#पूर्ण_अगर

	वापस FP_CUR_EXCEPTIONS;
पूर्ण
