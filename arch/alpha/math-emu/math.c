<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace.h>

#समावेश <linux/uaccess.h>

#समावेश "sfp-util.h"
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/द्विगुन.h>

#घोषणा	OPC_PAL		0x00
#घोषणा OPC_INTA	0x10
#घोषणा OPC_INTL	0x11
#घोषणा OPC_INTS	0x12
#घोषणा OPC_INTM	0x13
#घोषणा OPC_FLTC	0x14
#घोषणा OPC_FLTV	0x15
#घोषणा OPC_FLTI	0x16
#घोषणा OPC_FLTL	0x17
#घोषणा OPC_MISC	0x18
#घोषणा	OPC_JSR		0x1a

#घोषणा FOP_SRC_S	0
#घोषणा FOP_SRC_T	2
#घोषणा FOP_SRC_Q	3

#घोषणा FOP_FNC_ADDx	0
#घोषणा FOP_FNC_CVTQL	0
#घोषणा FOP_FNC_SUBx	1
#घोषणा FOP_FNC_MULx	2
#घोषणा FOP_FNC_DIVx	3
#घोषणा FOP_FNC_CMPxUN	4
#घोषणा FOP_FNC_CMPxEQ	5
#घोषणा FOP_FNC_CMPxLT	6
#घोषणा FOP_FNC_CMPxLE	7
#घोषणा FOP_FNC_SQRTx	11
#घोषणा FOP_FNC_CVTxS	12
#घोषणा FOP_FNC_CVTxT	14
#घोषणा FOP_FNC_CVTxQ	15

#घोषणा MISC_TRAPB	0x0000
#घोषणा MISC_EXCB	0x0400

बाह्य अचिन्हित दीर्घ alpha_पढ़ो_fp_reg (अचिन्हित दीर्घ reg);
बाह्य व्योम alpha_ग_लिखो_fp_reg (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val);
बाह्य अचिन्हित दीर्घ alpha_पढ़ो_fp_reg_s (अचिन्हित दीर्घ reg);
बाह्य व्योम alpha_ग_लिखो_fp_reg_s (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val);


#अगर_घोषित MODULE

MODULE_DESCRIPTION("FP Software completion module");
MODULE_LICENSE("GPL v2");

बाह्य दीर्घ (*alpha_fp_emul_imprecise)(काष्ठा pt_regs *, अचिन्हित दीर्घ);
बाह्य दीर्घ (*alpha_fp_emul) (अचिन्हित दीर्घ pc);

अटल दीर्घ (*save_emul_imprecise)(काष्ठा pt_regs *, अचिन्हित दीर्घ);
अटल दीर्घ (*save_emul) (अचिन्हित दीर्घ pc);

दीर्घ करो_alpha_fp_emul_imprecise(काष्ठा pt_regs *, अचिन्हित दीर्घ);
दीर्घ करो_alpha_fp_emul(अचिन्हित दीर्घ);

पूर्णांक init_module(व्योम)
अणु
	save_emul_imprecise = alpha_fp_emul_imprecise;
	save_emul = alpha_fp_emul;
	alpha_fp_emul_imprecise = करो_alpha_fp_emul_imprecise;
	alpha_fp_emul = करो_alpha_fp_emul;
	वापस 0;
पूर्ण

व्योम cleanup_module(व्योम)
अणु
	alpha_fp_emul_imprecise = save_emul_imprecise;
	alpha_fp_emul = save_emul;
पूर्ण

#अघोषित  alpha_fp_emul_imprecise
#घोषणा alpha_fp_emul_imprecise		करो_alpha_fp_emul_imprecise
#अघोषित  alpha_fp_emul
#घोषणा alpha_fp_emul			करो_alpha_fp_emul

#पूर्ण_अगर /* MODULE */


/*
 * Emulate the भग्नing poपूर्णांक inकाष्ठाion at address PC.  Returns -1 अगर the
 * inकाष्ठाion to be emulated is illegal (such as with the opDEC trap), अन्यथा
 * the SI_CODE क्रम a संक_भ_त्रुटि संकेत, अन्यथा 0 अगर everything's ok.
 *
 * Notice that the kernel करोes not and cannot use FP regs.  This is good
 * because it means that instead of saving/restoring all fp regs, we simply
 * stick the result of the operation पूर्णांकo the appropriate रेजिस्टर.
 */
दीर्घ
alpha_fp_emul (अचिन्हित दीर्घ pc)
अणु
	FP_DECL_EX;
	FP_DECL_S(SA); FP_DECL_S(SB); FP_DECL_S(SR);
	FP_DECL_D(DA); FP_DECL_D(DB); FP_DECL_D(DR);

	अचिन्हित दीर्घ fa, fb, fc, func, mode, src;
	अचिन्हित दीर्घ res, va, vb, vc, swcr, fpcr;
	__u32 insn;
	दीर्घ si_code;

	get_user(insn, (__u32 __user *)pc);
	fc     = (insn >>  0) & 0x1f;	/* destination रेजिस्टर */
	fb     = (insn >> 16) & 0x1f;
	fa     = (insn >> 21) & 0x1f;
	func   = (insn >>  5) & 0xf;
	src    = (insn >>  9) & 0x3;
	mode   = (insn >> 11) & 0x3;
	
	fpcr = rdfpcr();
	swcr = swcr_update_status(current_thपढ़ो_info()->ieee_state, fpcr);

	अगर (mode == 3) अणु
		/* Dynamic -- get rounding mode from fpcr.  */
		mode = (fpcr >> FPCR_DYN_SHIFT) & 3;
	पूर्ण

	चयन (src) अणु
	हाल FOP_SRC_S:
		va = alpha_पढ़ो_fp_reg_s(fa);
		vb = alpha_पढ़ो_fp_reg_s(fb);
		
		FP_UNPACK_SP(SA, &va);
		FP_UNPACK_SP(SB, &vb);

		चयन (func) अणु
		हाल FOP_FNC_SUBx:
			FP_SUB_S(SR, SA, SB);
			जाओ pack_s;

		हाल FOP_FNC_ADDx:
			FP_ADD_S(SR, SA, SB);
			जाओ pack_s;

		हाल FOP_FNC_MULx:
			FP_MUL_S(SR, SA, SB);
			जाओ pack_s;

		हाल FOP_FNC_DIVx:
			FP_DIV_S(SR, SA, SB);
			जाओ pack_s;

		हाल FOP_FNC_SQRTx:
			FP_SQRT_S(SR, SB);
			जाओ pack_s;
		पूर्ण
		जाओ bad_insn;

	हाल FOP_SRC_T:
		va = alpha_पढ़ो_fp_reg(fa);
		vb = alpha_पढ़ो_fp_reg(fb);

		अगर ((func & ~3) == FOP_FNC_CMPxUN) अणु
			FP_UNPACK_RAW_DP(DA, &va);
			FP_UNPACK_RAW_DP(DB, &vb);
			अगर (!DA_e && !_FP_FRAC_ZEROP_1(DA)) अणु
				FP_SET_EXCEPTION(FP_EX_DENORM);
				अगर (FP_DENORM_ZERO)
					_FP_FRAC_SET_1(DA, _FP_ZEROFRAC_1);
			पूर्ण
			अगर (!DB_e && !_FP_FRAC_ZEROP_1(DB)) अणु
				FP_SET_EXCEPTION(FP_EX_DENORM);
				अगर (FP_DENORM_ZERO)
					_FP_FRAC_SET_1(DB, _FP_ZEROFRAC_1);
			पूर्ण
			FP_CMP_D(res, DA, DB, 3);
			vc = 0x4000000000000000UL;
			/* CMPTEQ, CMPTUN करोn't trap on QNaN,
			   जबतक CMPTLT and CMPTLE करो */
			अगर (res == 3
			    && ((func & 3) >= 2
				|| FP_ISSIGन_अंक_D(DA)
				|| FP_ISSIGन_अंक_D(DB))) अणु
				FP_SET_EXCEPTION(FP_EX_INVALID);
			पूर्ण
			चयन (func) अणु
			हाल FOP_FNC_CMPxUN: अगर (res != 3) vc = 0; अवरोध;
			हाल FOP_FNC_CMPxEQ: अगर (res) vc = 0; अवरोध;
			हाल FOP_FNC_CMPxLT: अगर (res != -1) vc = 0; अवरोध;
			हाल FOP_FNC_CMPxLE: अगर ((दीर्घ)res > 0) vc = 0; अवरोध;
			पूर्ण
			जाओ करोne_d;
		पूर्ण

		FP_UNPACK_DP(DA, &va);
		FP_UNPACK_DP(DB, &vb);

		चयन (func) अणु
		हाल FOP_FNC_SUBx:
			FP_SUB_D(DR, DA, DB);
			जाओ pack_d;

		हाल FOP_FNC_ADDx:
			FP_ADD_D(DR, DA, DB);
			जाओ pack_d;

		हाल FOP_FNC_MULx:
			FP_MUL_D(DR, DA, DB);
			जाओ pack_d;

		हाल FOP_FNC_DIVx:
			FP_DIV_D(DR, DA, DB);
			जाओ pack_d;

		हाल FOP_FNC_SQRTx:
			FP_SQRT_D(DR, DB);
			जाओ pack_d;

		हाल FOP_FNC_CVTxS:
			/* It is irritating that DEC encoded CVTST with
			   SRC == T_भग्नing.  It is also पूर्णांकeresting that
			   the bit used to tell the two apart is /U... */
			अगर (insn & 0x2000) अणु
				FP_CONV(S,D,1,1,SR,DB);
				जाओ pack_s;
			पूर्ण अन्यथा अणु
				vb = alpha_पढ़ो_fp_reg_s(fb);
				FP_UNPACK_SP(SB, &vb);
				DR_c = DB_c;
				DR_s = DB_s;
				DR_e = DB_e + (1024 - 128);
				DR_f = SB_f << (52 - 23);
				जाओ pack_d;
			पूर्ण

		हाल FOP_FNC_CVTxQ:
			अगर (DB_c == FP_CLS_न_अंक
			    && (_FP_FRAC_HIGH_RAW_D(DB) & _FP_Qन_अंकBIT_D)) अणु
			  /* AAHB Table B-2 says QNaN should not trigger INV */
				vc = 0;
			पूर्ण अन्यथा
				FP_TO_INT_ROUND_D(vc, DB, 64, 2);
			जाओ करोne_d;
		पूर्ण
		जाओ bad_insn;

	हाल FOP_SRC_Q:
		vb = alpha_पढ़ो_fp_reg(fb);

		चयन (func) अणु
		हाल FOP_FNC_CVTQL:
			/* Notice: We can get here only due to an पूर्णांकeger
			   overflow.  Such overflows are reported as invalid
			   ops.  We वापस the result the hw would have
			   computed.  */
			vc = ((vb & 0xc0000000) << 32 |	/* sign and msb */
			      (vb & 0x3fffffff) << 29);	/* rest of the पूर्णांक */
			FP_SET_EXCEPTION (FP_EX_INVALID);
			जाओ करोne_d;

		हाल FOP_FNC_CVTxS:
			FP_FROM_INT_S(SR, ((दीर्घ)vb), 64, दीर्घ);
			जाओ pack_s;

		हाल FOP_FNC_CVTxT:
			FP_FROM_INT_D(DR, ((दीर्घ)vb), 64, दीर्घ);
			जाओ pack_d;
		पूर्ण
		जाओ bad_insn;
	पूर्ण
	जाओ bad_insn;

pack_s:
	FP_PACK_SP(&vc, SR);
	अगर ((_fex & FP_EX_UNDERFLOW) && (swcr & IEEE_MAP_UMZ))
		vc = 0;
	alpha_ग_लिखो_fp_reg_s(fc, vc);
	जाओ करोne;

pack_d:
	FP_PACK_DP(&vc, DR);
	अगर ((_fex & FP_EX_UNDERFLOW) && (swcr & IEEE_MAP_UMZ))
		vc = 0;
करोne_d:
	alpha_ग_लिखो_fp_reg(fc, vc);
	जाओ करोne;

	/*
	 * Take the appropriate action क्रम each possible
	 * भग्नing-poपूर्णांक result:
	 *
	 *	- Set the appropriate bits in the FPCR
	 *	- If the specअगरied exception is enabled in the FPCR,
	 *	  वापस.  The caller (entArith) will dispatch
	 *	  the appropriate संकेत to the translated program.
	 *
	 * In addition, properly track the exception state in software
	 * as described in the Alpha Architecture Handbook section 4.7.7.3.
	 */
करोne:
	अगर (_fex) अणु
		/* Record exceptions in software control word.  */
		swcr |= (_fex << IEEE_STATUS_TO_EXCSUM_SHIFT);
		current_thपढ़ो_info()->ieee_state
		  |= (_fex << IEEE_STATUS_TO_EXCSUM_SHIFT);

		/* Update hardware control रेजिस्टर.  */
		fpcr &= (~FPCR_MASK | FPCR_DYN_MASK);
		fpcr |= ieee_swcr_to_fpcr(swcr);
		wrfpcr(fpcr);

		/* Do we generate a संकेत?  */
		_fex = _fex & swcr & IEEE_TRAP_ENABLE_MASK;
		si_code = 0;
		अगर (_fex) अणु
			अगर (_fex & IEEE_TRAP_ENABLE_DNO) si_code = FPE_FLTUND;
			अगर (_fex & IEEE_TRAP_ENABLE_INE) si_code = FPE_FLTRES;
			अगर (_fex & IEEE_TRAP_ENABLE_UNF) si_code = FPE_FLTUND;
			अगर (_fex & IEEE_TRAP_ENABLE_OVF) si_code = FPE_FLTOVF;
			अगर (_fex & IEEE_TRAP_ENABLE_DZE) si_code = FPE_FLTDIV;
			अगर (_fex & IEEE_TRAP_ENABLE_INV) si_code = FPE_FLTINV;
		पूर्ण

		वापस si_code;
	पूर्ण

	/* We used to ग_लिखो the destination रेजिस्टर here, but DEC FORTRAN
	   requires that the result *always* be written... so we करो the ग_लिखो
	   immediately after the operations above.  */

	वापस 0;

bad_insn:
	prपूर्णांकk(KERN_ERR "alpha_fp_emul: Invalid FP insn %#x at %#lx\n",
	       insn, pc);
	वापस -1;
पूर्ण

दीर्घ
alpha_fp_emul_imprecise (काष्ठा pt_regs *regs, अचिन्हित दीर्घ ग_लिखो_mask)
अणु
	अचिन्हित दीर्घ trigger_pc = regs->pc - 4;
	अचिन्हित दीर्घ insn, opcode, rc, si_code = 0;

	/*
	 * Turn off the bits corresponding to रेजिस्टरs that are the
	 * target of inकाष्ठाions that set bits in the exception
	 * summary रेजिस्टर.  We have some slack करोing this because a
	 * रेजिस्टर that is the target of a trapping inकाष्ठाion can
	 * be written at most once in the trap shaकरोw.
	 *
	 * Branches, jumps, TRAPBs, EXCBs and calls to PALcode all
	 * bound the trap shaकरोw, so we need not look any further than
	 * up to the first occurrence of such an inकाष्ठाion.
	 */
	जबतक (ग_लिखो_mask) अणु
		get_user(insn, (__u32 __user *)(trigger_pc));
		opcode = insn >> 26;
		rc = insn & 0x1f;

		चयन (opcode) अणु
		      हाल OPC_PAL:
		      हाल OPC_JSR:
		      हाल 0x30 ... 0x3f:	/* branches */
			जाओ egress;

		      हाल OPC_MISC:
			चयन (insn & 0xffff) अणु
			      हाल MISC_TRAPB:
			      हाल MISC_EXCB:
				जाओ egress;

			      शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		      हाल OPC_INTA:
		      हाल OPC_INTL:
		      हाल OPC_INTS:
		      हाल OPC_INTM:
			ग_लिखो_mask &= ~(1UL << rc);
			अवरोध;

		      हाल OPC_FLTC:
		      हाल OPC_FLTV:
		      हाल OPC_FLTI:
		      हाल OPC_FLTL:
			ग_लिखो_mask &= ~(1UL << (rc + 32));
			अवरोध;
		पूर्ण
		अगर (!ग_लिखो_mask) अणु
			/* Re-execute insns in the trap-shaकरोw.  */
			regs->pc = trigger_pc + 4;
			si_code = alpha_fp_emul(trigger_pc);
			जाओ egress;
		पूर्ण
		trigger_pc -= 4;
	पूर्ण

egress:
	वापस si_code;
पूर्ण
