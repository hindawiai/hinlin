<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
व्योम fnegs(व्योम *ft, व्योम *fa)
अणु
	FP_DECL_S(A);
	FP_DECL_S(R);
	FP_DECL_EX;

	FP_UNPACK_SP(A, fa);

	FP_NEG_S(R, A);

	FP_PACK_SP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;
पूर्ण
