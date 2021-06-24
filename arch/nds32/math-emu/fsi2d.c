<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2019 Andes Technology Corporation
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>

व्योम fsi2d(व्योम *ft, व्योम *fa)
अणु
	पूर्णांक a = *(पूर्णांक *)fa;

	FP_DECL_D(R);
	FP_DECL_EX;

	FP_FROM_INT_D(R, a, 32, पूर्णांक);

	FP_PACK_DP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;

पूर्ण
