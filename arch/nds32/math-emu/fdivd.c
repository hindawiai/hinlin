<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>

व्योम fभागd(व्योम *ft, व्योम *fa, व्योम *fb)
अणु
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_D(R);
	FP_DECL_EX;

	FP_UNPACK_DP(A, fa);
	FP_UNPACK_DP(B, fb);

	अगर (B_c == FP_CLS_ZERO && A_c != FP_CLS_ZERO)
		FP_SET_EXCEPTION(FP_EX_DIVZERO);

	FP_DIV_D(R, A, B);

	FP_PACK_DP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
पूर्ण
