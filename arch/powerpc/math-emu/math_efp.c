<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/math-emu/math_efp.c
 *
 * Copyright (C) 2006-2008, 2010 Freescale Semiconductor, Inc.
 *
 * Author: Ebony Zhu,	<ebony.zhu@मुक्तscale.com>
 *         Yu Liu,	<yu.liu@मुक्तscale.com>
 *
 * Derived from arch/alpha/math-emu/math.c
 *              arch/घातerpc/math-emu/math.c
 *
 * Description:
 * This file is the exception handler to make E500 SPE inकाष्ठाions
 * fully comply with IEEE-754 भग्नing poपूर्णांक standard.
 */

#समावेश <linux/types.h>
#समावेश <linux/prctl.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/reg.h>

#घोषणा FP_EX_BOOKE_E500_SPE
#समावेश <यंत्र/sfp-machine.h>

#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/द्विगुन.h>

#घोषणा EFAPU		0x4

#घोषणा VCT		0x4
#घोषणा SPFP		0x6
#घोषणा DPFP		0x7

#घोषणा EFSADD		0x2c0
#घोषणा EFSSUB		0x2c1
#घोषणा EFSABS		0x2c4
#घोषणा EFSNABS		0x2c5
#घोषणा EFSNEG		0x2c6
#घोषणा EFSMUL		0x2c8
#घोषणा EFSDIV		0x2c9
#घोषणा EFSCMPGT	0x2cc
#घोषणा EFSCMPLT	0x2cd
#घोषणा EFSCMPEQ	0x2ce
#घोषणा EFSCFD		0x2cf
#घोषणा EFSCFSI		0x2d1
#घोषणा EFSCTUI		0x2d4
#घोषणा EFSCTSI		0x2d5
#घोषणा EFSCTUF		0x2d6
#घोषणा EFSCTSF		0x2d7
#घोषणा EFSCTUIZ	0x2d8
#घोषणा EFSCTSIZ	0x2da

#घोषणा EVFSADD		0x280
#घोषणा EVFSSUB		0x281
#घोषणा EVFSABS		0x284
#घोषणा EVFSNABS	0x285
#घोषणा EVFSNEG		0x286
#घोषणा EVFSMUL		0x288
#घोषणा EVFSDIV		0x289
#घोषणा EVFSCMPGT	0x28c
#घोषणा EVFSCMPLT	0x28d
#घोषणा EVFSCMPEQ	0x28e
#घोषणा EVFSCTUI	0x294
#घोषणा EVFSCTSI	0x295
#घोषणा EVFSCTUF	0x296
#घोषणा EVFSCTSF	0x297
#घोषणा EVFSCTUIZ	0x298
#घोषणा EVFSCTSIZ	0x29a

#घोषणा EFDADD		0x2e0
#घोषणा EFDSUB		0x2e1
#घोषणा EFDABS		0x2e4
#घोषणा EFDNABS		0x2e5
#घोषणा EFDNEG		0x2e6
#घोषणा EFDMUL		0x2e8
#घोषणा EFDDIV		0x2e9
#घोषणा EFDCTUIDZ	0x2ea
#घोषणा EFDCTSIDZ	0x2eb
#घोषणा EFDCMPGT	0x2ec
#घोषणा EFDCMPLT	0x2ed
#घोषणा EFDCMPEQ	0x2ee
#घोषणा EFDCFS		0x2ef
#घोषणा EFDCTUI		0x2f4
#घोषणा EFDCTSI		0x2f5
#घोषणा EFDCTUF		0x2f6
#घोषणा EFDCTSF		0x2f7
#घोषणा EFDCTUIZ	0x2f8
#घोषणा EFDCTSIZ	0x2fa

#घोषणा AB	2
#घोषणा XA	3
#घोषणा XB	4
#घोषणा XCR	5
#घोषणा NOTYPE	0

#घोषणा SIGN_BIT_S	(1UL << 31)
#घोषणा SIGN_BIT_D	(1ULL << 63)
#घोषणा FP_EX_MASK	(FP_EX_INEXACT | FP_EX_INVALID | FP_EX_DIVZERO | \
			FP_EX_UNDERFLOW | FP_EX_OVERFLOW)

अटल पूर्णांक have_e500_cpu_a005_erratum;

जोड़ dw_जोड़ अणु
	u64 dp[1];
	u32 wp[2];
पूर्ण;

अटल अचिन्हित दीर्घ insn_type(अचिन्हित दीर्घ speinsn)
अणु
	अचिन्हित दीर्घ ret = NOTYPE;

	चयन (speinsn & 0x7ff) अणु
	हाल EFSABS:	ret = XA;	अवरोध;
	हाल EFSADD:	ret = AB;	अवरोध;
	हाल EFSCFD:	ret = XB;	अवरोध;
	हाल EFSCMPEQ:	ret = XCR;	अवरोध;
	हाल EFSCMPGT:	ret = XCR;	अवरोध;
	हाल EFSCMPLT:	ret = XCR;	अवरोध;
	हाल EFSCTSF:	ret = XB;	अवरोध;
	हाल EFSCTSI:	ret = XB;	अवरोध;
	हाल EFSCTSIZ:	ret = XB;	अवरोध;
	हाल EFSCTUF:	ret = XB;	अवरोध;
	हाल EFSCTUI:	ret = XB;	अवरोध;
	हाल EFSCTUIZ:	ret = XB;	अवरोध;
	हाल EFSDIV:	ret = AB;	अवरोध;
	हाल EFSMUL:	ret = AB;	अवरोध;
	हाल EFSNABS:	ret = XA;	अवरोध;
	हाल EFSNEG:	ret = XA;	अवरोध;
	हाल EFSSUB:	ret = AB;	अवरोध;
	हाल EFSCFSI:	ret = XB;	अवरोध;

	हाल EVFSABS:	ret = XA;	अवरोध;
	हाल EVFSADD:	ret = AB;	अवरोध;
	हाल EVFSCMPEQ:	ret = XCR;	अवरोध;
	हाल EVFSCMPGT:	ret = XCR;	अवरोध;
	हाल EVFSCMPLT:	ret = XCR;	अवरोध;
	हाल EVFSCTSF:	ret = XB;	अवरोध;
	हाल EVFSCTSI:	ret = XB;	अवरोध;
	हाल EVFSCTSIZ:	ret = XB;	अवरोध;
	हाल EVFSCTUF:	ret = XB;	अवरोध;
	हाल EVFSCTUI:	ret = XB;	अवरोध;
	हाल EVFSCTUIZ:	ret = XB;	अवरोध;
	हाल EVFSDIV:	ret = AB;	अवरोध;
	हाल EVFSMUL:	ret = AB;	अवरोध;
	हाल EVFSNABS:	ret = XA;	अवरोध;
	हाल EVFSNEG:	ret = XA;	अवरोध;
	हाल EVFSSUB:	ret = AB;	अवरोध;

	हाल EFDABS:	ret = XA;	अवरोध;
	हाल EFDADD:	ret = AB;	अवरोध;
	हाल EFDCFS:	ret = XB;	अवरोध;
	हाल EFDCMPEQ:	ret = XCR;	अवरोध;
	हाल EFDCMPGT:	ret = XCR;	अवरोध;
	हाल EFDCMPLT:	ret = XCR;	अवरोध;
	हाल EFDCTSF:	ret = XB;	अवरोध;
	हाल EFDCTSI:	ret = XB;	अवरोध;
	हाल EFDCTSIDZ:	ret = XB;	अवरोध;
	हाल EFDCTSIZ:	ret = XB;	अवरोध;
	हाल EFDCTUF:	ret = XB;	अवरोध;
	हाल EFDCTUI:	ret = XB;	अवरोध;
	हाल EFDCTUIDZ:	ret = XB;	अवरोध;
	हाल EFDCTUIZ:	ret = XB;	अवरोध;
	हाल EFDDIV:	ret = AB;	अवरोध;
	हाल EFDMUL:	ret = AB;	अवरोध;
	हाल EFDNABS:	ret = XA;	अवरोध;
	हाल EFDNEG:	ret = XA;	अवरोध;
	हाल EFDSUB:	ret = AB;	अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक करो_spe_mathemu(काष्ठा pt_regs *regs)
अणु
	FP_DECL_EX;
	पूर्णांक IR, cmp;

	अचिन्हित दीर्घ type, func, fc, fa, fb, src, speinsn;
	जोड़ dw_जोड़ vc, va, vb;

	अगर (get_user(speinsn, (अचिन्हित पूर्णांक __user *) regs->nip))
		वापस -EFAULT;
	अगर ((speinsn >> 26) != EFAPU)
		वापस -EINVAL;         /* not an spe inकाष्ठाion */

	type = insn_type(speinsn);
	अगर (type == NOTYPE)
		जाओ illegal;

	func = speinsn & 0x7ff;
	fc = (speinsn >> 21) & 0x1f;
	fa = (speinsn >> 16) & 0x1f;
	fb = (speinsn >> 11) & 0x1f;
	src = (speinsn >> 5) & 0x7;

	vc.wp[0] = current->thपढ़ो.evr[fc];
	vc.wp[1] = regs->gpr[fc];
	va.wp[0] = current->thपढ़ो.evr[fa];
	va.wp[1] = regs->gpr[fa];
	vb.wp[0] = current->thपढ़ो.evr[fb];
	vb.wp[1] = regs->gpr[fb];

	__FPU_FPSCR = mfspr(SPRN_SPEFSCR);

	pr_debug("speinsn:%08lx spefscr:%08lx\n", speinsn, __FPU_FPSCR);
	pr_debug("vc: %08x  %08x\n", vc.wp[0], vc.wp[1]);
	pr_debug("va: %08x  %08x\n", va.wp[0], va.wp[1]);
	pr_debug("vb: %08x  %08x\n", vb.wp[0], vb.wp[1]);

	चयन (src) अणु
	हाल SPFP: अणु
		FP_DECL_S(SA); FP_DECL_S(SB); FP_DECL_S(SR);

		चयन (type) अणु
		हाल AB:
		हाल XCR:
			FP_UNPACK_SP(SA, va.wp + 1);
		हाल XB:
			FP_UNPACK_SP(SB, vb.wp + 1);
			अवरोध;
		हाल XA:
			FP_UNPACK_SP(SA, va.wp + 1);
			अवरोध;
		पूर्ण

		pr_debug("SA: %ld %08lx %ld (%ld)\n", SA_s, SA_f, SA_e, SA_c);
		pr_debug("SB: %ld %08lx %ld (%ld)\n", SB_s, SB_f, SB_e, SB_c);

		चयन (func) अणु
		हाल EFSABS:
			vc.wp[1] = va.wp[1] & ~SIGN_BIT_S;
			जाओ update_regs;

		हाल EFSNABS:
			vc.wp[1] = va.wp[1] | SIGN_BIT_S;
			जाओ update_regs;

		हाल EFSNEG:
			vc.wp[1] = va.wp[1] ^ SIGN_BIT_S;
			जाओ update_regs;

		हाल EFSADD:
			FP_ADD_S(SR, SA, SB);
			जाओ pack_s;

		हाल EFSSUB:
			FP_SUB_S(SR, SA, SB);
			जाओ pack_s;

		हाल EFSMUL:
			FP_MUL_S(SR, SA, SB);
			जाओ pack_s;

		हाल EFSDIV:
			FP_DIV_S(SR, SA, SB);
			जाओ pack_s;

		हाल EFSCMPEQ:
			cmp = 0;
			जाओ cmp_s;

		हाल EFSCMPGT:
			cmp = 1;
			जाओ cmp_s;

		हाल EFSCMPLT:
			cmp = -1;
			जाओ cmp_s;

		हाल EFSCTSF:
		हाल EFSCTUF:
			अगर (SB_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				SB_e += (func == EFSCTSF ? 31 : 32);
				FP_TO_INT_ROUND_S(vc.wp[1], SB, 32,
						(func == EFSCTSF));
			पूर्ण
			जाओ update_regs;

		हाल EFSCFD: अणु
			FP_DECL_D(DB);
			FP_CLEAR_EXCEPTIONS;
			FP_UNPACK_DP(DB, vb.dp);

			pr_debug("DB: %ld %08lx %08lx %ld (%ld)\n",
					DB_s, DB_f1, DB_f0, DB_e, DB_c);

			FP_CONV(S, D, 1, 2, SR, DB);
			जाओ pack_s;
		पूर्ण

		हाल EFSCTSI:
		हाल EFSCTUI:
			अगर (SB_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_ROUND_S(vc.wp[1], SB, 32,
						((func & 0x3) != 0));
			पूर्ण
			जाओ update_regs;

		हाल EFSCTSIZ:
		हाल EFSCTUIZ:
			अगर (SB_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_S(vc.wp[1], SB, 32,
						((func & 0x3) != 0));
			पूर्ण
			जाओ update_regs;

		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

pack_s:
		pr_debug("SR: %ld %08lx %ld (%ld)\n", SR_s, SR_f, SR_e, SR_c);

		FP_PACK_SP(vc.wp + 1, SR);
		जाओ update_regs;

cmp_s:
		FP_CMP_S(IR, SA, SB, 3);
		अगर (IR == 3 && (FP_ISSIGन_अंक_S(SA) || FP_ISSIGन_अंक_S(SB)))
			FP_SET_EXCEPTION(FP_EX_INVALID);
		अगर (IR == cmp) अणु
			IR = 0x4;
		पूर्ण अन्यथा अणु
			IR = 0;
		पूर्ण
		जाओ update_ccr;
	पूर्ण

	हाल DPFP: अणु
		FP_DECL_D(DA); FP_DECL_D(DB); FP_DECL_D(DR);

		चयन (type) अणु
		हाल AB:
		हाल XCR:
			FP_UNPACK_DP(DA, va.dp);
		हाल XB:
			FP_UNPACK_DP(DB, vb.dp);
			अवरोध;
		हाल XA:
			FP_UNPACK_DP(DA, va.dp);
			अवरोध;
		पूर्ण

		pr_debug("DA: %ld %08lx %08lx %ld (%ld)\n",
				DA_s, DA_f1, DA_f0, DA_e, DA_c);
		pr_debug("DB: %ld %08lx %08lx %ld (%ld)\n",
				DB_s, DB_f1, DB_f0, DB_e, DB_c);

		चयन (func) अणु
		हाल EFDABS:
			vc.dp[0] = va.dp[0] & ~SIGN_BIT_D;
			जाओ update_regs;

		हाल EFDNABS:
			vc.dp[0] = va.dp[0] | SIGN_BIT_D;
			जाओ update_regs;

		हाल EFDNEG:
			vc.dp[0] = va.dp[0] ^ SIGN_BIT_D;
			जाओ update_regs;

		हाल EFDADD:
			FP_ADD_D(DR, DA, DB);
			जाओ pack_d;

		हाल EFDSUB:
			FP_SUB_D(DR, DA, DB);
			जाओ pack_d;

		हाल EFDMUL:
			FP_MUL_D(DR, DA, DB);
			जाओ pack_d;

		हाल EFDDIV:
			FP_DIV_D(DR, DA, DB);
			जाओ pack_d;

		हाल EFDCMPEQ:
			cmp = 0;
			जाओ cmp_d;

		हाल EFDCMPGT:
			cmp = 1;
			जाओ cmp_d;

		हाल EFDCMPLT:
			cmp = -1;
			जाओ cmp_d;

		हाल EFDCTSF:
		हाल EFDCTUF:
			अगर (DB_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				DB_e += (func == EFDCTSF ? 31 : 32);
				FP_TO_INT_ROUND_D(vc.wp[1], DB, 32,
						(func == EFDCTSF));
			पूर्ण
			जाओ update_regs;

		हाल EFDCFS: अणु
			FP_DECL_S(SB);
			FP_CLEAR_EXCEPTIONS;
			FP_UNPACK_SP(SB, vb.wp + 1);

			pr_debug("SB: %ld %08lx %ld (%ld)\n",
					SB_s, SB_f, SB_e, SB_c);

			FP_CONV(D, S, 2, 1, DR, SB);
			जाओ pack_d;
		पूर्ण

		हाल EFDCTUIDZ:
		हाल EFDCTSIDZ:
			अगर (DB_c == FP_CLS_न_अंक) अणु
				vc.dp[0] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_D(vc.dp[0], DB, 64,
						((func & 0x1) == 0));
			पूर्ण
			जाओ update_regs;

		हाल EFDCTUI:
		हाल EFDCTSI:
			अगर (DB_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_ROUND_D(vc.wp[1], DB, 32,
						((func & 0x3) != 0));
			पूर्ण
			जाओ update_regs;

		हाल EFDCTUIZ:
		हाल EFDCTSIZ:
			अगर (DB_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_D(vc.wp[1], DB, 32,
						((func & 0x3) != 0));
			पूर्ण
			जाओ update_regs;

		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

pack_d:
		pr_debug("DR: %ld %08lx %08lx %ld (%ld)\n",
				DR_s, DR_f1, DR_f0, DR_e, DR_c);

		FP_PACK_DP(vc.dp, DR);
		जाओ update_regs;

cmp_d:
		FP_CMP_D(IR, DA, DB, 3);
		अगर (IR == 3 && (FP_ISSIGन_अंक_D(DA) || FP_ISSIGन_अंक_D(DB)))
			FP_SET_EXCEPTION(FP_EX_INVALID);
		अगर (IR == cmp) अणु
			IR = 0x4;
		पूर्ण अन्यथा अणु
			IR = 0;
		पूर्ण
		जाओ update_ccr;

	पूर्ण

	हाल VCT: अणु
		FP_DECL_S(SA0); FP_DECL_S(SB0); FP_DECL_S(SR0);
		FP_DECL_S(SA1); FP_DECL_S(SB1); FP_DECL_S(SR1);
		पूर्णांक IR0, IR1;

		चयन (type) अणु
		हाल AB:
		हाल XCR:
			FP_UNPACK_SP(SA0, va.wp);
			FP_UNPACK_SP(SA1, va.wp + 1);
		हाल XB:
			FP_UNPACK_SP(SB0, vb.wp);
			FP_UNPACK_SP(SB1, vb.wp + 1);
			अवरोध;
		हाल XA:
			FP_UNPACK_SP(SA0, va.wp);
			FP_UNPACK_SP(SA1, va.wp + 1);
			अवरोध;
		पूर्ण

		pr_debug("SA0: %ld %08lx %ld (%ld)\n",
				SA0_s, SA0_f, SA0_e, SA0_c);
		pr_debug("SA1: %ld %08lx %ld (%ld)\n",
				SA1_s, SA1_f, SA1_e, SA1_c);
		pr_debug("SB0: %ld %08lx %ld (%ld)\n",
				SB0_s, SB0_f, SB0_e, SB0_c);
		pr_debug("SB1: %ld %08lx %ld (%ld)\n",
				SB1_s, SB1_f, SB1_e, SB1_c);

		चयन (func) अणु
		हाल EVFSABS:
			vc.wp[0] = va.wp[0] & ~SIGN_BIT_S;
			vc.wp[1] = va.wp[1] & ~SIGN_BIT_S;
			जाओ update_regs;

		हाल EVFSNABS:
			vc.wp[0] = va.wp[0] | SIGN_BIT_S;
			vc.wp[1] = va.wp[1] | SIGN_BIT_S;
			जाओ update_regs;

		हाल EVFSNEG:
			vc.wp[0] = va.wp[0] ^ SIGN_BIT_S;
			vc.wp[1] = va.wp[1] ^ SIGN_BIT_S;
			जाओ update_regs;

		हाल EVFSADD:
			FP_ADD_S(SR0, SA0, SB0);
			FP_ADD_S(SR1, SA1, SB1);
			जाओ pack_vs;

		हाल EVFSSUB:
			FP_SUB_S(SR0, SA0, SB0);
			FP_SUB_S(SR1, SA1, SB1);
			जाओ pack_vs;

		हाल EVFSMUL:
			FP_MUL_S(SR0, SA0, SB0);
			FP_MUL_S(SR1, SA1, SB1);
			जाओ pack_vs;

		हाल EVFSDIV:
			FP_DIV_S(SR0, SA0, SB0);
			FP_DIV_S(SR1, SA1, SB1);
			जाओ pack_vs;

		हाल EVFSCMPEQ:
			cmp = 0;
			जाओ cmp_vs;

		हाल EVFSCMPGT:
			cmp = 1;
			जाओ cmp_vs;

		हाल EVFSCMPLT:
			cmp = -1;
			जाओ cmp_vs;

		हाल EVFSCTUF:
		हाल EVFSCTSF:
			अगर (SB0_c == FP_CLS_न_अंक) अणु
				vc.wp[0] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				SB0_e += (func == EVFSCTSF ? 31 : 32);
				FP_TO_INT_ROUND_S(vc.wp[0], SB0, 32,
						(func == EVFSCTSF));
			पूर्ण
			अगर (SB1_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				SB1_e += (func == EVFSCTSF ? 31 : 32);
				FP_TO_INT_ROUND_S(vc.wp[1], SB1, 32,
						(func == EVFSCTSF));
			पूर्ण
			जाओ update_regs;

		हाल EVFSCTUI:
		हाल EVFSCTSI:
			अगर (SB0_c == FP_CLS_न_अंक) अणु
				vc.wp[0] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_ROUND_S(vc.wp[0], SB0, 32,
						((func & 0x3) != 0));
			पूर्ण
			अगर (SB1_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_ROUND_S(vc.wp[1], SB1, 32,
						((func & 0x3) != 0));
			पूर्ण
			जाओ update_regs;

		हाल EVFSCTUIZ:
		हाल EVFSCTSIZ:
			अगर (SB0_c == FP_CLS_न_अंक) अणु
				vc.wp[0] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_S(vc.wp[0], SB0, 32,
						((func & 0x3) != 0));
			पूर्ण
			अगर (SB1_c == FP_CLS_न_अंक) अणु
				vc.wp[1] = 0;
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण अन्यथा अणु
				FP_TO_INT_S(vc.wp[1], SB1, 32,
						((func & 0x3) != 0));
			पूर्ण
			जाओ update_regs;

		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

pack_vs:
		pr_debug("SR0: %ld %08lx %ld (%ld)\n",
				SR0_s, SR0_f, SR0_e, SR0_c);
		pr_debug("SR1: %ld %08lx %ld (%ld)\n",
				SR1_s, SR1_f, SR1_e, SR1_c);

		FP_PACK_SP(vc.wp, SR0);
		FP_PACK_SP(vc.wp + 1, SR1);
		जाओ update_regs;

cmp_vs:
		अणु
			पूर्णांक ch, cl;

			FP_CMP_S(IR0, SA0, SB0, 3);
			FP_CMP_S(IR1, SA1, SB1, 3);
			अगर (IR0 == 3 && (FP_ISSIGन_अंक_S(SA0) || FP_ISSIGन_अंक_S(SB0)))
				FP_SET_EXCEPTION(FP_EX_INVALID);
			अगर (IR1 == 3 && (FP_ISSIGन_अंक_S(SA1) || FP_ISSIGन_अंक_S(SB1)))
				FP_SET_EXCEPTION(FP_EX_INVALID);
			ch = (IR0 == cmp) ? 1 : 0;
			cl = (IR1 == cmp) ? 1 : 0;
			IR = (ch << 3) | (cl << 2) | ((ch | cl) << 1) |
				((ch & cl) << 0);
			जाओ update_ccr;
		पूर्ण
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

update_ccr:
	regs->ccr &= ~(15 << ((7 - ((speinsn >> 23) & 0x7)) << 2));
	regs->ccr |= (IR << ((7 - ((speinsn >> 23) & 0x7)) << 2));

update_regs:
	/*
	 * If the "invalid" exception sticky bit was set by the
	 * processor क्रम non-finite input, but was not set beक्रमe the
	 * inकाष्ठाion being emulated, clear it.  Likewise क्रम the
	 * "underflow" bit, which may have been set by the processor
	 * क्रम exact underflow, not just inexact underflow when the
	 * flag should be set क्रम IEEE 754 semantics.  Other sticky
	 * exceptions will only be set by the processor when they are
	 * correct according to IEEE 754 semantics, and we must not
	 * clear sticky bits that were alपढ़ोy set beक्रमe the emulated
	 * inकाष्ठाion as they represent the user-visible sticky
	 * exception status.  "inexact" traps to kernel are not
	 * required क्रम IEEE semantics and are not enabled by शेष,
	 * so the "inexact" sticky bit may have been set by a previous
	 * inकाष्ठाion without the kernel being aware of it.
	 */
	__FPU_FPSCR
	  &= ~(FP_EX_INVALID | FP_EX_UNDERFLOW) | current->thपढ़ो.spefscr_last;
	__FPU_FPSCR |= (FP_CUR_EXCEPTIONS & FP_EX_MASK);
	mtspr(SPRN_SPEFSCR, __FPU_FPSCR);
	current->thपढ़ो.spefscr_last = __FPU_FPSCR;

	current->thपढ़ो.evr[fc] = vc.wp[0];
	regs->gpr[fc] = vc.wp[1];

	pr_debug("ccr = %08lx\n", regs->ccr);
	pr_debug("cur exceptions = %08x spefscr = %08lx\n",
			FP_CUR_EXCEPTIONS, __FPU_FPSCR);
	pr_debug("vc: %08x  %08x\n", vc.wp[0], vc.wp[1]);
	pr_debug("va: %08x  %08x\n", va.wp[0], va.wp[1]);
	pr_debug("vb: %08x  %08x\n", vb.wp[0], vb.wp[1]);

	अगर (current->thपढ़ो.fpexc_mode & PR_FP_EXC_SW_ENABLE) अणु
		अगर ((FP_CUR_EXCEPTIONS & FP_EX_DIVZERO)
		    && (current->thपढ़ो.fpexc_mode & PR_FP_EXC_DIV))
			वापस 1;
		अगर ((FP_CUR_EXCEPTIONS & FP_EX_OVERFLOW)
		    && (current->thपढ़ो.fpexc_mode & PR_FP_EXC_OVF))
			वापस 1;
		अगर ((FP_CUR_EXCEPTIONS & FP_EX_UNDERFLOW)
		    && (current->thपढ़ो.fpexc_mode & PR_FP_EXC_UND))
			वापस 1;
		अगर ((FP_CUR_EXCEPTIONS & FP_EX_INEXACT)
		    && (current->thपढ़ो.fpexc_mode & PR_FP_EXC_RES))
			वापस 1;
		अगर ((FP_CUR_EXCEPTIONS & FP_EX_INVALID)
		    && (current->thपढ़ो.fpexc_mode & PR_FP_EXC_INV))
			वापस 1;
	पूर्ण
	वापस 0;

illegal:
	अगर (have_e500_cpu_a005_erratum) अणु
		/* according to e500 cpu a005 erratum, reissue efp inst */
		regs->nip -= 4;
		pr_debug("re-issue efp inst: %08lx\n", speinsn);
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "\nOoops! IEEE-754 compliance handler encountered un-supported instruction.\ninst code: %08lx\n", speinsn);
	वापस -ENOSYS;
पूर्ण

पूर्णांक speround_handler(काष्ठा pt_regs *regs)
अणु
	जोड़ dw_जोड़ fgpr;
	पूर्णांक s_lo, s_hi;
	पूर्णांक lo_inexact, hi_inexact;
	पूर्णांक fp_result;
	अचिन्हित दीर्घ speinsn, type, fb, fc, fptype, func;

	अगर (get_user(speinsn, (अचिन्हित पूर्णांक __user *) regs->nip))
		वापस -EFAULT;
	अगर ((speinsn >> 26) != 4)
		वापस -EINVAL;         /* not an spe inकाष्ठाion */

	func = speinsn & 0x7ff;
	type = insn_type(func);
	अगर (type == XCR) वापस -ENOSYS;

	__FPU_FPSCR = mfspr(SPRN_SPEFSCR);
	pr_debug("speinsn:%08lx spefscr:%08lx\n", speinsn, __FPU_FPSCR);

	fptype = (speinsn >> 5) & 0x7;

	/* No need to round अगर the result is exact */
	lo_inexact = __FPU_FPSCR & (SPEFSCR_FG | SPEFSCR_FX);
	hi_inexact = __FPU_FPSCR & (SPEFSCR_FGH | SPEFSCR_FXH);
	अगर (!(lo_inexact || (hi_inexact && fptype == VCT)))
		वापस 0;

	fc = (speinsn >> 21) & 0x1f;
	s_lo = regs->gpr[fc] & SIGN_BIT_S;
	s_hi = current->thपढ़ो.evr[fc] & SIGN_BIT_S;
	fgpr.wp[0] = current->thपढ़ो.evr[fc];
	fgpr.wp[1] = regs->gpr[fc];

	fb = (speinsn >> 11) & 0x1f;
	चयन (func) अणु
	हाल EFSCTUIZ:
	हाल EFSCTSIZ:
	हाल EVFSCTUIZ:
	हाल EVFSCTSIZ:
	हाल EFDCTUIDZ:
	हाल EFDCTSIDZ:
	हाल EFDCTUIZ:
	हाल EFDCTSIZ:
		/*
		 * These inकाष्ठाions always round to zero,
		 * independent of the rounding mode.
		 */
		वापस 0;

	हाल EFSCTUI:
	हाल EFSCTUF:
	हाल EVFSCTUI:
	हाल EVFSCTUF:
	हाल EFDCTUI:
	हाल EFDCTUF:
		fp_result = 0;
		s_lo = 0;
		s_hi = 0;
		अवरोध;

	हाल EFSCTSI:
	हाल EFSCTSF:
		fp_result = 0;
		/* Recover the sign of a zero result अगर possible.  */
		अगर (fgpr.wp[1] == 0)
			s_lo = regs->gpr[fb] & SIGN_BIT_S;
		अवरोध;

	हाल EVFSCTSI:
	हाल EVFSCTSF:
		fp_result = 0;
		/* Recover the sign of a zero result अगर possible.  */
		अगर (fgpr.wp[1] == 0)
			s_lo = regs->gpr[fb] & SIGN_BIT_S;
		अगर (fgpr.wp[0] == 0)
			s_hi = current->thपढ़ो.evr[fb] & SIGN_BIT_S;
		अवरोध;

	हाल EFDCTSI:
	हाल EFDCTSF:
		fp_result = 0;
		s_hi = s_lo;
		/* Recover the sign of a zero result अगर possible.  */
		अगर (fgpr.wp[1] == 0)
			s_hi = current->thपढ़ो.evr[fb] & SIGN_BIT_S;
		अवरोध;

	शेष:
		fp_result = 1;
		अवरोध;
	पूर्ण

	pr_debug("round fgpr: %08x  %08x\n", fgpr.wp[0], fgpr.wp[1]);

	चयन (fptype) अणु
	/* Since SPE inकाष्ठाions on E500 core can handle round to nearest
	 * and round toward zero with IEEE-754 complied, we just need
	 * to handle round toward +Inf and round toward -Inf by software.
	 */
	हाल SPFP:
		अगर ((FP_ROUNDMODE) == FP_RND_PINF) अणु
			अगर (!s_lo) fgpr.wp[1]++; /* Z > 0, choose Z1 */
		पूर्ण अन्यथा अणु /* round to -Inf */
			अगर (s_lo) अणु
				अगर (fp_result)
					fgpr.wp[1]++; /* Z < 0, choose Z2 */
				अन्यथा
					fgpr.wp[1]--; /* Z < 0, choose Z2 */
			पूर्ण
		पूर्ण
		अवरोध;

	हाल DPFP:
		अगर (FP_ROUNDMODE == FP_RND_PINF) अणु
			अगर (!s_hi) अणु
				अगर (fp_result)
					fgpr.dp[0]++; /* Z > 0, choose Z1 */
				अन्यथा
					fgpr.wp[1]++; /* Z > 0, choose Z1 */
			पूर्ण
		पूर्ण अन्यथा अणु /* round to -Inf */
			अगर (s_hi) अणु
				अगर (fp_result)
					fgpr.dp[0]++; /* Z < 0, choose Z2 */
				अन्यथा
					fgpr.wp[1]--; /* Z < 0, choose Z2 */
			पूर्ण
		पूर्ण
		अवरोध;

	हाल VCT:
		अगर (FP_ROUNDMODE == FP_RND_PINF) अणु
			अगर (lo_inexact && !s_lo)
				fgpr.wp[1]++; /* Z_low > 0, choose Z1 */
			अगर (hi_inexact && !s_hi)
				fgpr.wp[0]++; /* Z_high word > 0, choose Z1 */
		पूर्ण अन्यथा अणु /* round to -Inf */
			अगर (lo_inexact && s_lo) अणु
				अगर (fp_result)
					fgpr.wp[1]++; /* Z_low < 0, choose Z2 */
				अन्यथा
					fgpr.wp[1]--; /* Z_low < 0, choose Z2 */
			पूर्ण
			अगर (hi_inexact && s_hi) अणु
				अगर (fp_result)
					fgpr.wp[0]++; /* Z_high < 0, choose Z2 */
				अन्यथा
					fgpr.wp[0]--; /* Z_high < 0, choose Z2 */
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	current->thपढ़ो.evr[fc] = fgpr.wp[0];
	regs->gpr[fc] = fgpr.wp[1];

	pr_debug("  to fgpr: %08x  %08x\n", fgpr.wp[0], fgpr.wp[1]);

	अगर (current->thपढ़ो.fpexc_mode & PR_FP_EXC_SW_ENABLE)
		वापस (current->thपढ़ो.fpexc_mode & PR_FP_EXC_RES) ? 1 : 0;
	वापस 0;
पूर्ण

पूर्णांक __init spe_mathemu_init(व्योम)
अणु
	u32 pvr, maj, min;

	pvr = mfspr(SPRN_PVR);

	अगर ((PVR_VER(pvr) == PVR_VER_E500V1) ||
	    (PVR_VER(pvr) == PVR_VER_E500V2)) अणु
		maj = PVR_MAJ(pvr);
		min = PVR_MIN(pvr);

		/*
		 * E500 revision below 1.1, 2.3, 3.1, 4.1, 5.1
		 * need cpu a005 errata workaround
		 */
		चयन (maj) अणु
		हाल 1:
			अगर (min < 1)
				have_e500_cpu_a005_erratum = 1;
			अवरोध;
		हाल 2:
			अगर (min < 3)
				have_e500_cpu_a005_erratum = 1;
			अवरोध;
		हाल 3:
		हाल 4:
		हाल 5:
			अगर (min < 1)
				have_e500_cpu_a005_erratum = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

module_init(spe_mathemu_init);
