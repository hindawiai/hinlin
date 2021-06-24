<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2019 Andes Technology Corporation
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>

व्योम fd2si(व्योम *ft, व्योम *fa)
अणु
	पूर्णांक r;

	FP_DECL_D(A);
	FP_DECL_EX;

	FP_UNPACK_DP(A, fa);

	अगर (A_c == FP_CLS_INF) अणु
		*(पूर्णांक *)ft = (A_s == 0) ? 0x7fffffff : 0x80000000;
		__FPU_FPCSR |= FP_EX_INVALID;
	पूर्ण अन्यथा अगर (A_c == FP_CLS_न_अंक) अणु
		*(पूर्णांक *)ft = 0xffffffff;
		__FPU_FPCSR |= FP_EX_INVALID;
	पूर्ण अन्यथा अणु
		FP_TO_INT_ROUND_D(r, A, 32, 1);
		__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
		*(पूर्णांक *)ft = r;
	पूर्ण

पूर्ण
