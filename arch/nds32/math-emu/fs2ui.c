<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2019 Andes Technology Corporation
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>

व्योम fs2ui(व्योम *ft, व्योम *fa)
अणु
	अचिन्हित पूर्णांक r;

	FP_DECL_S(A);
	FP_DECL_EX;

	FP_UNPACK_SP(A, fa);

	अगर (A_c == FP_CLS_INF) अणु
		*(अचिन्हित पूर्णांक *)ft = (A_s == 0) ? 0xffffffff : 0x00000000;
		__FPU_FPCSR |= FP_EX_INVALID;
	पूर्ण अन्यथा अगर (A_c == FP_CLS_न_अंक) अणु
		*(अचिन्हित पूर्णांक *)ft = 0xffffffff;
		__FPU_FPCSR |= FP_EX_INVALID;
	पूर्ण अन्यथा अणु
		FP_TO_INT_ROUND_S(r, A, 32, 0);
		__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
		*(अचिन्हित पूर्णांक *)ft = r;
	पूर्ण
पूर्ण
