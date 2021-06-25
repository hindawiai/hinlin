<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/द्विगुन.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/soft-fp.h>

व्योम fs2d(व्योम *ft, व्योम *fa)
अणु
	FP_DECL_S(A);
	FP_DECL_D(R);
	FP_DECL_EX;

	FP_UNPACK_SP(A, fa);

	FP_CONV(D, S, 2, 1, R, A);

	FP_PACK_DP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
पूर्ण
