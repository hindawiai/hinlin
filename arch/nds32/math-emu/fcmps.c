<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation
#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
पूर्णांक fcmps(व्योम *ft, व्योम *fa, व्योम *fb, पूर्णांक cmpop)
अणु
	FP_DECL_S(A);
	FP_DECL_S(B);
	FP_DECL_EX;
	दीर्घ cmp;

	FP_UNPACK_SP(A, fa);
	FP_UNPACK_SP(B, fb);

	FP_CMP_S(cmp, A, B, SF_CUN);
	cmp += 2;
	अगर (cmp == SF_CGT)
		*(पूर्णांक *)ft = 0x0;
	अन्यथा
		*(पूर्णांक *)ft = (cmp & cmpop) ? 0x1 : 0x0;

	वापस 0;
पूर्ण
