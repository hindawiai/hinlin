<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sparc64/math-emu/math.c
 *
 * Copyright (C) 1997,1999 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1999 David S. Miller (davem@redhat.com)
 *
 * Emulation routines originate from soft-fp package, which is part
 * of glibc and has appropriate copyrights in it.
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "sfp-util_64.h"
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/द्विगुन.h>
#समावेश <math-emu/quad.h>

/* QUAD - ftt == 3 */
#घोषणा FMOVQ	0x003
#घोषणा FNEGQ	0x007
#घोषणा FABSQ	0x00b
#घोषणा FSQRTQ	0x02b
#घोषणा FADDQ	0x043
#घोषणा FSUBQ	0x047
#घोषणा FMULQ	0x04b
#घोषणा FDIVQ	0x04f
#घोषणा FDMULQ	0x06e
#घोषणा FQTOX	0x083
#घोषणा FXTOQ	0x08c
#घोषणा FQTOS	0x0c7
#घोषणा FQTOD	0x0cb
#घोषणा FITOQ	0x0cc
#घोषणा FSTOQ	0x0cd
#घोषणा FDTOQ	0x0ce
#घोषणा FQTOI	0x0d3
/* SUBNORMAL - ftt == 2 */
#घोषणा FSQRTS	0x029
#घोषणा FSQRTD	0x02a
#घोषणा FADDS	0x041
#घोषणा FADDD	0x042
#घोषणा FSUBS	0x045
#घोषणा FSUBD	0x046
#घोषणा FMULS	0x049
#घोषणा FMULD	0x04a
#घोषणा FDIVS	0x04d
#घोषणा FDIVD	0x04e
#घोषणा FSMULD	0x069
#घोषणा FSTOX	0x081
#घोषणा FDTOX	0x082
#घोषणा FDTOS	0x0c6
#घोषणा FSTOD	0x0c9
#घोषणा FSTOI	0x0d1
#घोषणा FDTOI	0x0d2
#घोषणा FXTOS	0x084 /* Only Ultra-III generates this. */
#घोषणा FXTOD	0x088 /* Only Ultra-III generates this. */
#अगर 0	/* Optimized अंतरभूत in sparc64/kernel/entry.S */
#घोषणा FITOS	0x0c4 /* Only Ultra-III generates this. */
#पूर्ण_अगर
#घोषणा FITOD	0x0c8 /* Only Ultra-III generates this. */
/* FPOP2 */
#घोषणा FCMPQ	0x053
#घोषणा FCMPEQ	0x057
#घोषणा FMOVQ0	0x003
#घोषणा FMOVQ1	0x043
#घोषणा FMOVQ2	0x083
#घोषणा FMOVQ3	0x0c3
#घोषणा FMOVQI	0x103
#घोषणा FMOVQX	0x183
#घोषणा FMOVQZ	0x027
#घोषणा FMOVQLE	0x047
#घोषणा FMOVQLZ 0x067
#घोषणा FMOVQNZ	0x0a7
#घोषणा FMOVQGZ	0x0c7
#घोषणा FMOVQGE 0x0e7

#घोषणा FSR_TEM_SHIFT	23UL
#घोषणा FSR_TEM_MASK	(0x1fUL << FSR_TEM_SHIFT)
#घोषणा FSR_AEXC_SHIFT	5UL
#घोषणा FSR_AEXC_MASK	(0x1fUL << FSR_AEXC_SHIFT)
#घोषणा FSR_CEXC_SHIFT	0UL
#घोषणा FSR_CEXC_MASK	(0x1fUL << FSR_CEXC_SHIFT)

/* All routines वापसing an exception to उठाओ should detect
 * such exceptions _beक्रमe_ rounding to be consistent with
 * the behavior of the hardware in the implemented हालs
 * (and thus with the recommendations in the V9 architecture
 * manual).
 *
 * We वापस 0 अगर a संक_भ_त्रुटि should be sent, 1 otherwise.
 */
अटल अंतरभूत पूर्णांक record_exception(काष्ठा pt_regs *regs, पूर्णांक eflag)
अणु
	u64 fsr = current_thपढ़ो_info()->xfsr[0];
	पूर्णांक would_trap;

	/* Determine अगर this exception would have generated a trap. */
	would_trap = (fsr & ((दीर्घ)eflag << FSR_TEM_SHIFT)) != 0UL;

	/* If trapping, we only want to संकेत one bit. */
	अगर(would_trap != 0) अणु
		eflag &= ((fsr & FSR_TEM_MASK) >> FSR_TEM_SHIFT);
		अगर((eflag & (eflag - 1)) != 0) अणु
			अगर(eflag & FP_EX_INVALID)
				eflag = FP_EX_INVALID;
			अन्यथा अगर(eflag & FP_EX_OVERFLOW)
				eflag = FP_EX_OVERFLOW;
			अन्यथा अगर(eflag & FP_EX_UNDERFLOW)
				eflag = FP_EX_UNDERFLOW;
			अन्यथा अगर(eflag & FP_EX_DIVZERO)
				eflag = FP_EX_DIVZERO;
			अन्यथा अगर(eflag & FP_EX_INEXACT)
				eflag = FP_EX_INEXACT;
		पूर्ण
	पूर्ण

	/* Set CEXC, here is the rule:
	 *
	 *    In general all FPU ops will set one and only one
	 *    bit in the CEXC field, this is always the हाल
	 *    when the IEEE exception trap is enabled in TEM.
	 */
	fsr &= ~(FSR_CEXC_MASK);
	fsr |= ((दीर्घ)eflag << FSR_CEXC_SHIFT);

	/* Set the AEXC field, rule is:
	 *
	 *    If a trap would not be generated, the
	 *    CEXC just generated is OR'd पूर्णांकo the
	 *    existing value of AEXC.
	 */
	अगर(would_trap == 0)
		fsr |= ((दीर्घ)eflag << FSR_AEXC_SHIFT);

	/* If trapping, indicate fault trap type IEEE. */
	अगर(would_trap != 0)
		fsr |= (1UL << 14);

	current_thपढ़ो_info()->xfsr[0] = fsr;

	/* If we will not trap, advance the program counter over
	 * the inकाष्ठाion being handled.
	 */
	अगर(would_trap == 0) अणु
		regs->tpc = regs->tnpc;
		regs->tnpc += 4;
	पूर्ण

	वापस (would_trap ? 0 : 1);
पूर्ण

प्रकार जोड़ अणु
	u32 s;
	u64 d;
	u64 q[2];
पूर्ण *argp;

पूर्णांक करो_mathemu(काष्ठा pt_regs *regs, काष्ठा fpustate *f, bool illegal_insn_trap)
अणु
	अचिन्हित दीर्घ pc = regs->tpc;
	अचिन्हित दीर्घ tstate = regs->tstate;
	u32 insn = 0;
	पूर्णांक type = 0;
	/* ftt tells which ftt it may happen in, r is rd, b is rs2 and a is rs1. The *u arg tells
	   whether the argument should be packed/unpacked (0 - करो not unpack/pack, 1 - unpack/pack)
	   non-u args tells the size of the argument (0 - no argument, 1 - single, 2 - द्विगुन, 3 - quad */
#घोषणा TYPE(ftt, r, ru, b, bu, a, au) type = (au << 2) | (a << 0) | (bu << 5) | (b << 3) | (ru << 8) | (r << 6) | (ftt << 9)
	पूर्णांक freg;
	अटल u64 zero[2] = अणु 0L, 0L पूर्ण;
	पूर्णांक flags;
	FP_DECL_EX;
	FP_DECL_S(SA); FP_DECL_S(SB); FP_DECL_S(SR);
	FP_DECL_D(DA); FP_DECL_D(DB); FP_DECL_D(DR);
	FP_DECL_Q(QA); FP_DECL_Q(QB); FP_DECL_Q(QR);
	पूर्णांक IR;
	दीर्घ XR, xfsr;

	अगर (tstate & TSTATE_PRIV)
		die_अगर_kernel("unfinished/unimplemented FPop from kernel", regs);
	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);
	अगर (test_thपढ़ो_flag(TIF_32BIT))
		pc = (u32)pc;
	अगर (get_user(insn, (u32 __user *) pc) != -EFAULT) अणु
		अगर ((insn & 0xc1f80000) == 0x81a00000) /* FPOP1 */ अणु
			चयन ((insn >> 5) & 0x1ff) अणु
			/* QUAD - ftt == 3 */
			हाल FMOVQ:
			हाल FNEGQ:
			हाल FABSQ: TYPE(3,3,0,3,0,0,0); अवरोध;
			हाल FSQRTQ: TYPE(3,3,1,3,1,0,0); अवरोध;
			हाल FADDQ:
			हाल FSUBQ:
			हाल FMULQ:
			हाल FDIVQ: TYPE(3,3,1,3,1,3,1); अवरोध;
			हाल FDMULQ: TYPE(3,3,1,2,1,2,1); अवरोध;
			हाल FQTOX: TYPE(3,2,0,3,1,0,0); अवरोध;
			हाल FXTOQ: TYPE(3,3,1,2,0,0,0); अवरोध;
			हाल FQTOS: TYPE(3,1,1,3,1,0,0); अवरोध;
			हाल FQTOD: TYPE(3,2,1,3,1,0,0); अवरोध;
			हाल FITOQ: TYPE(3,3,1,1,0,0,0); अवरोध;
			हाल FSTOQ: TYPE(3,3,1,1,1,0,0); अवरोध;
			हाल FDTOQ: TYPE(3,3,1,2,1,0,0); अवरोध;
			हाल FQTOI: TYPE(3,1,0,3,1,0,0); अवरोध;

			/* We can get either unimplemented or unfinished
			 * क्रम these हालs.  Pre-Niagara प्रणालीs generate
			 * unfinished fpop क्रम SUBNORMAL हालs, and Niagara
			 * always gives unimplemented fpop क्रम fवर्ग_मूलअणुs,dपूर्ण.
			 */
			हाल FSQRTS: अणु
				अचिन्हित दीर्घ x = current_thपढ़ो_info()->xfsr[0];

				x = (x >> 14) & 0x7;
				TYPE(x,1,1,1,1,0,0);
				अवरोध;
			पूर्ण

			हाल FSQRTD: अणु
				अचिन्हित दीर्घ x = current_thपढ़ो_info()->xfsr[0];

				x = (x >> 14) & 0x7;
				TYPE(x,2,1,2,1,0,0);
				अवरोध;
			पूर्ण

			/* SUBNORMAL - ftt == 2 */
			हाल FADDD:
			हाल FSUBD:
			हाल FMULD:
			हाल FDIVD: TYPE(2,2,1,2,1,2,1); अवरोध;
			हाल FADDS:
			हाल FSUBS:
			हाल FMULS:
			हाल FDIVS: TYPE(2,1,1,1,1,1,1); अवरोध;
			हाल FSMULD: TYPE(2,2,1,1,1,1,1); अवरोध;
			हाल FSTOX: TYPE(2,2,0,1,1,0,0); अवरोध;
			हाल FDTOX: TYPE(2,2,0,2,1,0,0); अवरोध;
			हाल FDTOS: TYPE(2,1,1,2,1,0,0); अवरोध;
			हाल FSTOD: TYPE(2,2,1,1,1,0,0); अवरोध;
			हाल FSTOI: TYPE(2,1,0,1,1,0,0); अवरोध;
			हाल FDTOI: TYPE(2,1,0,2,1,0,0); अवरोध;

			/* Only Ultra-III generates these */
			हाल FXTOS: TYPE(2,1,1,2,0,0,0); अवरोध;
			हाल FXTOD: TYPE(2,2,1,2,0,0,0); अवरोध;
#अगर 0			/* Optimized अंतरभूत in sparc64/kernel/entry.S */
			हाल FITOS: TYPE(2,1,1,1,0,0,0); अवरोध;
#पूर्ण_अगर
			हाल FITOD: TYPE(2,2,1,1,0,0,0); अवरोध;
			पूर्ण
		पूर्ण
		अन्यथा अगर ((insn & 0xc1f80000) == 0x81a80000) /* FPOP2 */ अणु
			IR = 2;
			चयन ((insn >> 5) & 0x1ff) अणु
			हाल FCMPQ: TYPE(3,0,0,3,1,3,1); अवरोध;
			हाल FCMPEQ: TYPE(3,0,0,3,1,3,1); अवरोध;
			/* Now the conditional fmovq support */
			हाल FMOVQ0:
			हाल FMOVQ1:
			हाल FMOVQ2:
			हाल FMOVQ3:
				/* fmovq %fccX, %fY, %fZ */
				अगर (!((insn >> 11) & 3))
					XR = current_thपढ़ो_info()->xfsr[0] >> 10;
				अन्यथा
					XR = current_thपढ़ो_info()->xfsr[0] >> (30 + ((insn >> 10) & 0x6));
				XR &= 3;
				IR = 0;
				चयन ((insn >> 14) & 0x7) अणु
				/* हाल 0: IR = 0; अवरोध; */			/* Never */
				हाल 1: अगर (XR) IR = 1; अवरोध;			/* Not Equal */
				हाल 2: अगर (XR == 1 || XR == 2) IR = 1; अवरोध;	/* Less or Greater */
				हाल 3: अगर (XR & 1) IR = 1; अवरोध;		/* Unordered or Less */
				हाल 4: अगर (XR == 1) IR = 1; अवरोध;		/* Less */
				हाल 5: अगर (XR & 2) IR = 1; अवरोध;		/* Unordered or Greater */
				हाल 6: अगर (XR == 2) IR = 1; अवरोध;		/* Greater */
				हाल 7: अगर (XR == 3) IR = 1; अवरोध;		/* Unordered */
				पूर्ण
				अगर ((insn >> 14) & 8)
					IR ^= 1;
				अवरोध;
			हाल FMOVQI:
			हाल FMOVQX:
				/* fmovq %[ix]cc, %fY, %fZ */
				XR = regs->tstate >> 32;
				अगर ((insn >> 5) & 0x80)
					XR >>= 4;
				XR &= 0xf;
				IR = 0;
				freg = ((XR >> 2) ^ XR) & 2;
				चयन ((insn >> 14) & 0x7) अणु
				/* हाल 0: IR = 0; अवरोध; */			/* Never */
				हाल 1: अगर (XR & 4) IR = 1; अवरोध;		/* Equal */
				हाल 2: अगर ((XR & 4) || freg) IR = 1; अवरोध;	/* Less or Equal */
				हाल 3: अगर (freg) IR = 1; अवरोध;		/* Less */
				हाल 4: अगर (XR & 5) IR = 1; अवरोध;		/* Less or Equal Unचिन्हित */
				हाल 5: अगर (XR & 1) IR = 1; अवरोध;		/* Carry Set */
				हाल 6: अगर (XR & 8) IR = 1; अवरोध;		/* Negative */
				हाल 7: अगर (XR & 2) IR = 1; अवरोध;		/* Overflow Set */
				पूर्ण
				अगर ((insn >> 14) & 8)
					IR ^= 1;
				अवरोध;
			हाल FMOVQZ:
			हाल FMOVQLE:
			हाल FMOVQLZ:
			हाल FMOVQNZ:
			हाल FMOVQGZ:
			हाल FMOVQGE:
				freg = (insn >> 14) & 0x1f;
				अगर (!freg)
					XR = 0;
				अन्यथा अगर (freg < 16)
					XR = regs->u_regs[freg];
				अन्यथा अगर (!test_thपढ़ो_64bit_stack(regs->u_regs[UREG_FP])) अणु
					काष्ठा reg_winकरोw32 __user *win32;
					flushw_user ();
					win32 = (काष्ठा reg_winकरोw32 __user *)((अचिन्हित दीर्घ)((u32)regs->u_regs[UREG_FP]));
					get_user(XR, &win32->locals[freg - 16]);
				पूर्ण अन्यथा अणु
					काष्ठा reg_winकरोw __user *win;
					flushw_user ();
					win = (काष्ठा reg_winकरोw __user *)(regs->u_regs[UREG_FP] + STACK_BIAS);
					get_user(XR, &win->locals[freg - 16]);
				पूर्ण
				IR = 0;
				चयन ((insn >> 10) & 3) अणु
				हाल 1: अगर (!XR) IR = 1; अवरोध;			/* Register Zero */
				हाल 2: अगर (XR <= 0) IR = 1; अवरोध;		/* Register Less Than or Equal to Zero */
				हाल 3: अगर (XR < 0) IR = 1; अवरोध;		/* Register Less Than Zero */
				पूर्ण
				अगर ((insn >> 10) & 4)
					IR ^= 1;
				अवरोध;
			पूर्ण
			अगर (IR == 0) अणु
				/* The fmov test was false. Do a nop instead */
				current_thपढ़ो_info()->xfsr[0] &= ~(FSR_CEXC_MASK);
				regs->tpc = regs->tnpc;
				regs->tnpc += 4;
				वापस 1;
			पूर्ण अन्यथा अगर (IR == 1) अणु
				/* Change the inकाष्ठाion पूर्णांकo plain fmovq */
				insn = (insn & 0x3e00001f) | 0x81a00060;
				TYPE(3,3,0,3,0,0,0); 
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (type) अणु
		argp rs1 = शून्य, rs2 = शून्य, rd = शून्य;
		
		/* Starting with UltraSPARC-T2, the cpu करोes not set the FP Trap
		 * Type field in the %fsr to unimplemented_FPop.  Nor करोes it
		 * use the fp_exception_other trap.  Instead it संकेतs an
		 * illegal inकाष्ठाion and leaves the FP trap type field of
		 * the %fsr unchanged.
		 */
		अगर (!illegal_insn_trap) अणु
			पूर्णांक ftt = (current_thपढ़ो_info()->xfsr[0] >> 14) & 0x7;
			अगर (ftt != (type >> 9))
				जाओ err;
		पूर्ण
		current_thपढ़ो_info()->xfsr[0] &= ~0x1c000;
		freg = ((insn >> 14) & 0x1f);
		चयन (type & 0x3) अणु
		हाल 3: अगर (freg & 2) अणु
				current_thपढ़ो_info()->xfsr[0] |= (6 << 14) /* invalid_fp_रेजिस्टर */;
				जाओ err;
			पूर्ण
		हाल 2: freg = ((freg & 1) << 5) | (freg & 0x1e);
		हाल 1: rs1 = (argp)&f->regs[freg];
			flags = (freg < 32) ? FPRS_DL : FPRS_DU; 
			अगर (!(current_thपढ़ो_info()->fpsaved[0] & flags))
				rs1 = (argp)&zero;
			अवरोध;
		पूर्ण
		चयन (type & 0x7) अणु
		हाल 7: FP_UNPACK_QP (QA, rs1); अवरोध;
		हाल 6: FP_UNPACK_DP (DA, rs1); अवरोध;
		हाल 5: FP_UNPACK_SP (SA, rs1); अवरोध;
		पूर्ण
		freg = (insn & 0x1f);
		चयन ((type >> 3) & 0x3) अणु
		हाल 3: अगर (freg & 2) अणु
				current_thपढ़ो_info()->xfsr[0] |= (6 << 14) /* invalid_fp_रेजिस्टर */;
				जाओ err;
			पूर्ण
		हाल 2: freg = ((freg & 1) << 5) | (freg & 0x1e);
		हाल 1: rs2 = (argp)&f->regs[freg];
			flags = (freg < 32) ? FPRS_DL : FPRS_DU; 
			अगर (!(current_thपढ़ो_info()->fpsaved[0] & flags))
				rs2 = (argp)&zero;
			अवरोध;
		पूर्ण
		चयन ((type >> 3) & 0x7) अणु
		हाल 7: FP_UNPACK_QP (QB, rs2); अवरोध;
		हाल 6: FP_UNPACK_DP (DB, rs2); अवरोध;
		हाल 5: FP_UNPACK_SP (SB, rs2); अवरोध;
		पूर्ण
		freg = ((insn >> 25) & 0x1f);
		चयन ((type >> 6) & 0x3) अणु
		हाल 3: अगर (freg & 2) अणु
				current_thपढ़ो_info()->xfsr[0] |= (6 << 14) /* invalid_fp_रेजिस्टर */;
				जाओ err;
			पूर्ण
		हाल 2: freg = ((freg & 1) << 5) | (freg & 0x1e);
		हाल 1: rd = (argp)&f->regs[freg];
			flags = (freg < 32) ? FPRS_DL : FPRS_DU; 
			अगर (!(current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)) अणु
				current_thपढ़ो_info()->fpsaved[0] = FPRS_FEF;
				current_thपढ़ो_info()->gsr[0] = 0;
			पूर्ण
			अगर (!(current_thपढ़ो_info()->fpsaved[0] & flags)) अणु
				अगर (freg < 32)
					स_रखो(f->regs, 0, 32*माप(u32));
				अन्यथा
					स_रखो(f->regs+32, 0, 32*माप(u32));
			पूर्ण
			current_thपढ़ो_info()->fpsaved[0] |= flags;
			अवरोध;
		पूर्ण
		चयन ((insn >> 5) & 0x1ff) अणु
		/* + */
		हाल FADDS: FP_ADD_S (SR, SA, SB); अवरोध;
		हाल FADDD: FP_ADD_D (DR, DA, DB); अवरोध;
		हाल FADDQ: FP_ADD_Q (QR, QA, QB); अवरोध;
		/* - */
		हाल FSUBS: FP_SUB_S (SR, SA, SB); अवरोध;
		हाल FSUBD: FP_SUB_D (DR, DA, DB); अवरोध;
		हाल FSUBQ: FP_SUB_Q (QR, QA, QB); अवरोध;
		/* * */
		हाल FMULS: FP_MUL_S (SR, SA, SB); अवरोध;
		हाल FSMULD: FP_CONV (D, S, 1, 1, DA, SA);
			     FP_CONV (D, S, 1, 1, DB, SB);
		हाल FMULD: FP_MUL_D (DR, DA, DB); अवरोध;
		हाल FDMULQ: FP_CONV (Q, D, 2, 1, QA, DA);
			     FP_CONV (Q, D, 2, 1, QB, DB);
		हाल FMULQ: FP_MUL_Q (QR, QA, QB); अवरोध;
		/* / */
		हाल FDIVS: FP_DIV_S (SR, SA, SB); अवरोध;
		हाल FDIVD: FP_DIV_D (DR, DA, DB); अवरोध;
		हाल FDIVQ: FP_DIV_Q (QR, QA, QB); अवरोध;
		/* वर्ग_मूल */
		हाल FSQRTS: FP_SQRT_S (SR, SB); अवरोध;
		हाल FSQRTD: FP_SQRT_D (DR, DB); अवरोध;
		हाल FSQRTQ: FP_SQRT_Q (QR, QB); अवरोध;
		/* mov */
		हाल FMOVQ: rd->q[0] = rs2->q[0]; rd->q[1] = rs2->q[1]; अवरोध;
		हाल FABSQ: rd->q[0] = rs2->q[0] & 0x7fffffffffffffffUL; rd->q[1] = rs2->q[1]; अवरोध;
		हाल FNEGQ: rd->q[0] = rs2->q[0] ^ 0x8000000000000000UL; rd->q[1] = rs2->q[1]; अवरोध;
		/* भग्न to पूर्णांक */
		हाल FSTOI: FP_TO_INT_S (IR, SB, 32, 1); अवरोध;
		हाल FDTOI: FP_TO_INT_D (IR, DB, 32, 1); अवरोध;
		हाल FQTOI: FP_TO_INT_Q (IR, QB, 32, 1); अवरोध;
		हाल FSTOX: FP_TO_INT_S (XR, SB, 64, 1); अवरोध;
		हाल FDTOX: FP_TO_INT_D (XR, DB, 64, 1); अवरोध;
		हाल FQTOX: FP_TO_INT_Q (XR, QB, 64, 1); अवरोध;
		/* पूर्णांक to भग्न */
		हाल FITOQ: IR = rs2->s; FP_FROM_INT_Q (QR, IR, 32, पूर्णांक); अवरोध;
		हाल FXTOQ: XR = rs2->d; FP_FROM_INT_Q (QR, XR, 64, दीर्घ); अवरोध;
		/* Only Ultra-III generates these */
		हाल FXTOS: XR = rs2->d; FP_FROM_INT_S (SR, XR, 64, दीर्घ); अवरोध;
		हाल FXTOD: XR = rs2->d; FP_FROM_INT_D (DR, XR, 64, दीर्घ); अवरोध;
#अगर 0		/* Optimized अंतरभूत in sparc64/kernel/entry.S */
		हाल FITOS: IR = rs2->s; FP_FROM_INT_S (SR, IR, 32, पूर्णांक); अवरोध;
#पूर्ण_अगर
		हाल FITOD: IR = rs2->s; FP_FROM_INT_D (DR, IR, 32, पूर्णांक); अवरोध;
		/* भग्न to भग्न */
		हाल FSTOD: FP_CONV (D, S, 1, 1, DR, SB); अवरोध;
		हाल FSTOQ: FP_CONV (Q, S, 2, 1, QR, SB); अवरोध;
		हाल FDTOQ: FP_CONV (Q, D, 2, 1, QR, DB); अवरोध;
		हाल FDTOS: FP_CONV (S, D, 1, 1, SR, DB); अवरोध;
		हाल FQTOS: FP_CONV (S, Q, 1, 2, SR, QB); अवरोध;
		हाल FQTOD: FP_CONV (D, Q, 1, 2, DR, QB); अवरोध;
		/* comparison */
		हाल FCMPQ:
		हाल FCMPEQ:
			FP_CMP_Q(XR, QB, QA, 3);
			अगर (XR == 3 &&
			    (((insn >> 5) & 0x1ff) == FCMPEQ ||
			     FP_ISSIGन_अंक_Q(QA) ||
			     FP_ISSIGन_अंक_Q(QB)))
				FP_SET_EXCEPTION (FP_EX_INVALID);
		पूर्ण
		अगर (!FP_INHIBIT_RESULTS) अणु
			चयन ((type >> 6) & 0x7) अणु
			हाल 0: xfsr = current_thपढ़ो_info()->xfsr[0];
				अगर (XR == -1) XR = 2;
				चयन (freg & 3) अणु
				/* fcc0, 1, 2, 3 */
				हाल 0: xfsr &= ~0xc00; xfsr |= (XR << 10); अवरोध;
				हाल 1: xfsr &= ~0x300000000UL; xfsr |= (XR << 32); अवरोध;
				हाल 2: xfsr &= ~0xc00000000UL; xfsr |= (XR << 34); अवरोध;
				हाल 3: xfsr &= ~0x3000000000UL; xfsr |= (XR << 36); अवरोध;
				पूर्ण
				current_thपढ़ो_info()->xfsr[0] = xfsr;
				अवरोध;
			हाल 1: rd->s = IR; अवरोध;
			हाल 2: rd->d = XR; अवरोध;
			हाल 5: FP_PACK_SP (rd, SR); अवरोध;
			हाल 6: FP_PACK_DP (rd, DR); अवरोध;
			हाल 7: FP_PACK_QP (rd, QR); अवरोध;
			पूर्ण
		पूर्ण

		अगर(_fex != 0)
			वापस record_exception(regs, _fex);

		/* Success and no exceptions detected. */
		current_thपढ़ो_info()->xfsr[0] &= ~(FSR_CEXC_MASK);
		regs->tpc = regs->tnpc;
		regs->tnpc += 4;
		वापस 1;
	पूर्ण
err:	वापस 0;
पूर्ण
