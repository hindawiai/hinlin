<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation
#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/द्विगुन.h>
पूर्णांक fcmpd(व्योम *ft, व्योम *fa, व्योम *fb, पूर्णांक cmpop)
अणु
	FP_DECL_D(A);
	FP_DECL_D(B);
	FP_DECL_EX;
	दीर्घ cmp;

	FP_UNPACK_DP(A, fa);
	FP_UNPACK_DP(B, fb);

	FP_CMP_D(cmp, A, B, SF_CUN);
	cmp += 2;
	अगर (cmp == SF_CGT)
		*(दीर्घ *)ft = 0;
	अन्यथा
		*(दीर्घ *)ft = (cmp & cmpop) ? 1 : 0;

	वापस 0;
पूर्ण
