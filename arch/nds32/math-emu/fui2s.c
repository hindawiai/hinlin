<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2019 Andes Technology Corporation
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>

व्योम fui2s(व्योम *ft, व्योम *fa)
अणु
	अचिन्हित पूर्णांक a = *(अचिन्हित पूर्णांक *)fa;

	FP_DECL_S(R);
	FP_DECL_EX;

	FP_FROM_INT_S(R, a, 32, पूर्णांक);

	FP_PACK_SP(ft, R);

	__FPU_FPCSR |= FP_CUR_EXCEPTIONS;

पूर्ण
