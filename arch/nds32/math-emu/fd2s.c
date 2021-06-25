<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/द्विगुन.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/soft-fp.h>
व्योम fd2s(व्योम *ft, व्योम *fa)
अणु
	FP_DECL_D(A);
	FP_DECL_S(R);
	FP_DECL_EX;

	FP_UNPACK_DP(A, fa);

	FP_CONV(S, D, 1, 2, R, A);

	FP_PACK_SP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
पूर्ण
