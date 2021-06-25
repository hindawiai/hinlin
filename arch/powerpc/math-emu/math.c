<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1999  Eddie C. Dost  (ecd@atecom.com)
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/चयन_to.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/द्विगुन.h>

#घोषणा FLOATFUNC(x)	बाह्य पूर्णांक x(व्योम *, व्योम *, व्योम *, व्योम *)

/* The inकाष्ठाions list which may be not implemented by a hardware FPU */
FLOATFUNC(fre);
FLOATFUNC(frवर्ग_मूलes);
FLOATFUNC(fवर्ग_मूल);
FLOATFUNC(fवर्ग_मूलs);
FLOATFUNC(mtfsf);
FLOATFUNC(mtfsfi);

#अगर_घोषित CONFIG_MATH_EMULATION_HW_UNIMPLEMENTED
#अघोषित FLOATFUNC(x)
#घोषणा FLOATFUNC(x)	अटल अंतरभूत पूर्णांक x(व्योम *op1, व्योम *op2, व्योम *op3, \
						 व्योम *op4) अणु पूर्ण
#पूर्ण_अगर

FLOATFUNC(fadd);
FLOATFUNC(fadds);
FLOATFUNC(fभाग);
FLOATFUNC(fभागs);
FLOATFUNC(fmul);
FLOATFUNC(fmuls);
FLOATFUNC(fsub);
FLOATFUNC(fsubs);

FLOATFUNC(fmadd);
FLOATFUNC(fmadds);
FLOATFUNC(fmsub);
FLOATFUNC(fmsubs);
FLOATFUNC(fnmadd);
FLOATFUNC(fnmadds);
FLOATFUNC(fnmsub);
FLOATFUNC(fnmsubs);

FLOATFUNC(fctiw);
FLOATFUNC(fctiwz);
FLOATFUNC(frsp);

FLOATFUNC(fcmpo);
FLOATFUNC(fcmpu);

FLOATFUNC(mcrfs);
FLOATFUNC(mffs);
FLOATFUNC(mtfsb0);
FLOATFUNC(mtfsb1);

FLOATFUNC(lfd);
FLOATFUNC(lfs);

FLOATFUNC(stfd);
FLOATFUNC(stfs);
FLOATFUNC(stfiwx);

FLOATFUNC(भ_असल);
FLOATFUNC(fmr);
FLOATFUNC(fnअसल);
FLOATFUNC(fneg);

/* Optional */
FLOATFUNC(fres);
FLOATFUNC(frवर्ग_मूलe);
FLOATFUNC(fsel);


#घोषणा OP31		0x1f		/*   31 */
#घोषणा LFS		0x30		/*   48 */
#घोषणा LFSU		0x31		/*   49 */
#घोषणा LFD		0x32		/*   50 */
#घोषणा LFDU		0x33		/*   51 */
#घोषणा STFS		0x34		/*   52 */
#घोषणा STFSU		0x35		/*   53 */
#घोषणा STFD		0x36		/*   54 */
#घोषणा STFDU		0x37		/*   55 */
#घोषणा OP59		0x3b		/*   59 */
#घोषणा OP63		0x3f		/*   63 */

/* Opcode 31: */
/* X-Form: */
#घोषणा LFSX		0x217		/*  535 */
#घोषणा LFSUX		0x237		/*  567 */
#घोषणा LFDX		0x257		/*  599 */
#घोषणा LFDUX		0x277		/*  631 */
#घोषणा STFSX		0x297		/*  663 */
#घोषणा STFSUX		0x2b7		/*  695 */
#घोषणा STFDX		0x2d7		/*  727 */
#घोषणा STFDUX		0x2f7		/*  759 */
#घोषणा STFIWX		0x3d7		/*  983 */

/* Opcode 59: */
/* A-Form: */
#घोषणा FDIVS		0x012		/*   18 */
#घोषणा FSUBS		0x014		/*   20 */
#घोषणा FADDS		0x015		/*   21 */
#घोषणा FSQRTS		0x016		/*   22 */
#घोषणा FRES		0x018		/*   24 */
#घोषणा FMULS		0x019		/*   25 */
#घोषणा FRSQRTES	0x01a		/*   26 */
#घोषणा FMSUBS		0x01c		/*   28 */
#घोषणा FMADDS		0x01d		/*   29 */
#घोषणा FNMSUBS		0x01e		/*   30 */
#घोषणा FNMADDS		0x01f		/*   31 */

/* Opcode 63: */
/* A-Form: */
#घोषणा FDIV		0x012		/*   18 */
#घोषणा FSUB		0x014		/*   20 */
#घोषणा FADD		0x015		/*   21 */
#घोषणा FSQRT		0x016		/*   22 */
#घोषणा FSEL		0x017		/*   23 */
#घोषणा FRE		0x018		/*   24 */
#घोषणा FMUL		0x019		/*   25 */
#घोषणा FRSQRTE		0x01a		/*   26 */
#घोषणा FMSUB		0x01c		/*   28 */
#घोषणा FMADD		0x01d		/*   29 */
#घोषणा FNMSUB		0x01e		/*   30 */
#घोषणा FNMADD		0x01f		/*   31 */

/* X-Form: */
#घोषणा FCMPU		0x000		/*    0	*/
#घोषणा FRSP		0x00c		/*   12 */
#घोषणा FCTIW		0x00e		/*   14 */
#घोषणा FCTIWZ		0x00f		/*   15 */
#घोषणा FCMPO		0x020		/*   32 */
#घोषणा MTFSB1		0x026		/*   38 */
#घोषणा FNEG		0x028		/*   40 */
#घोषणा MCRFS		0x040		/*   64 */
#घोषणा MTFSB0		0x046		/*   70 */
#घोषणा FMR		0x048		/*   72 */
#घोषणा MTFSFI		0x086		/*  134 */
#घोषणा FNABS		0x088		/*  136 */
#घोषणा FABS		0x108		/*  264 */
#घोषणा MFFS		0x247		/*  583 */
#घोषणा MTFSF		0x2c7		/*  711 */


#घोषणा AB	2
#घोषणा AC	3
#घोषणा ABC	4
#घोषणा D	5
#घोषणा DU	6
#घोषणा X	7
#घोषणा XA	8
#घोषणा XB	9
#घोषणा XCR	11
#घोषणा XCRB	12
#घोषणा XCRI	13
#घोषणा XCRL	16
#घोषणा XE	14
#घोषणा XEU	15
#घोषणा XFLB	10

अटल पूर्णांक
record_exception(काष्ठा pt_regs *regs, पूर्णांक eflag)
अणु
	u32 fpscr;

	fpscr = __FPU_FPSCR;

	अगर (eflag) अणु
		fpscr |= FPSCR_FX;
		अगर (eflag & EFLAG_OVERFLOW)
			fpscr |= FPSCR_OX;
		अगर (eflag & EFLAG_UNDERFLOW)
			fpscr |= FPSCR_UX;
		अगर (eflag & EFLAG_DIVZERO)
			fpscr |= FPSCR_ZX;
		अगर (eflag & EFLAG_INEXACT)
			fpscr |= FPSCR_XX;
		अगर (eflag & EFLAG_INVALID)
			fpscr |= FPSCR_VX;
		अगर (eflag & EFLAG_VXSन_अंक)
			fpscr |= FPSCR_VXSन_अंक;
		अगर (eflag & EFLAG_VXISI)
			fpscr |= FPSCR_VXISI;
		अगर (eflag & EFLAG_VXIDI)
			fpscr |= FPSCR_VXIDI;
		अगर (eflag & EFLAG_VXZDZ)
			fpscr |= FPSCR_VXZDZ;
		अगर (eflag & EFLAG_VXIMZ)
			fpscr |= FPSCR_VXIMZ;
		अगर (eflag & EFLAG_VXVC)
			fpscr |= FPSCR_VXVC;
		अगर (eflag & EFLAG_VXSOFT)
			fpscr |= FPSCR_VXSOFT;
		अगर (eflag & EFLAG_VXSQRT)
			fpscr |= FPSCR_VXSQRT;
		अगर (eflag & EFLAG_VXCVI)
			fpscr |= FPSCR_VXCVI;
	पूर्ण

//	fpscr &= ~(FPSCR_VX);
	अगर (fpscr & (FPSCR_VXSन_अंक | FPSCR_VXISI | FPSCR_VXIDI |
		     FPSCR_VXZDZ | FPSCR_VXIMZ | FPSCR_VXVC |
		     FPSCR_VXSOFT | FPSCR_VXSQRT | FPSCR_VXCVI))
		fpscr |= FPSCR_VX;

	fpscr &= ~(FPSCR_FEX);
	अगर (((fpscr & FPSCR_VX) && (fpscr & FPSCR_VE)) ||
	    ((fpscr & FPSCR_OX) && (fpscr & FPSCR_OE)) ||
	    ((fpscr & FPSCR_UX) && (fpscr & FPSCR_UE)) ||
	    ((fpscr & FPSCR_ZX) && (fpscr & FPSCR_ZE)) ||
	    ((fpscr & FPSCR_XX) && (fpscr & FPSCR_XE)))
		fpscr |= FPSCR_FEX;

	__FPU_FPSCR = fpscr;

	वापस (fpscr & FPSCR_FEX) ? 1 : 0;
पूर्ण

पूर्णांक
करो_mathemu(काष्ठा pt_regs *regs)
अणु
	व्योम *op0 = शून्य, *op1 = शून्य, *op2 = शून्य, *op3 = शून्य;
	अचिन्हित दीर्घ pc = regs->nip;
	चिन्हित लघु sdisp;
	u32 insn = 0;
	पूर्णांक idx = 0;
	पूर्णांक (*func)(व्योम *, व्योम *, व्योम *, व्योम *);
	पूर्णांक type = 0;
	पूर्णांक eflag, trap;

	अगर (get_user(insn, (u32 __user *)pc))
		वापस -EFAULT;

	चयन (insn >> 26) अणु
	हाल LFS:	func = lfs;	type = D;	अवरोध;
	हाल LFSU:	func = lfs;	type = DU;	अवरोध;
	हाल LFD:	func = lfd;	type = D;	अवरोध;
	हाल LFDU:	func = lfd;	type = DU;	अवरोध;
	हाल STFS:	func = stfs;	type = D;	अवरोध;
	हाल STFSU:	func = stfs;	type = DU;	अवरोध;
	हाल STFD:	func = stfd;	type = D;	अवरोध;
	हाल STFDU:	func = stfd;	type = DU;	अवरोध;

	हाल OP31:
		चयन ((insn >> 1) & 0x3ff) अणु
		हाल LFSX:	func = lfs;	type = XE;	अवरोध;
		हाल LFSUX:	func = lfs;	type = XEU;	अवरोध;
		हाल LFDX:	func = lfd;	type = XE;	अवरोध;
		हाल LFDUX:	func = lfd;	type = XEU;	अवरोध;
		हाल STFSX:	func = stfs;	type = XE;	अवरोध;
		हाल STFSUX:	func = stfs;	type = XEU;	अवरोध;
		हाल STFDX:	func = stfd;	type = XE;	अवरोध;
		हाल STFDUX:	func = stfd;	type = XEU;	अवरोध;
		हाल STFIWX:	func = stfiwx;	type = XE;	अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल OP59:
		चयन ((insn >> 1) & 0x1f) अणु
		हाल FDIVS:	func = fभागs;	type = AB;	अवरोध;
		हाल FSUBS:	func = fsubs;	type = AB;	अवरोध;
		हाल FADDS:	func = fadds;	type = AB;	अवरोध;
		हाल FSQRTS:	func = fवर्ग_मूलs;	type = XB;	अवरोध;
		हाल FRES:	func = fres;	type = XB;	अवरोध;
		हाल FMULS:	func = fmuls;	type = AC;	अवरोध;
		हाल FRSQRTES:	func = frवर्ग_मूलes;type = XB;	अवरोध;
		हाल FMSUBS:	func = fmsubs;	type = ABC;	अवरोध;
		हाल FMADDS:	func = fmadds;	type = ABC;	अवरोध;
		हाल FNMSUBS:	func = fnmsubs;	type = ABC;	अवरोध;
		हाल FNMADDS:	func = fnmadds;	type = ABC;	अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	हाल OP63:
		अगर (insn & 0x20) अणु
			चयन ((insn >> 1) & 0x1f) अणु
			हाल FDIV:	func = fभाग;	type = AB;	अवरोध;
			हाल FSUB:	func = fsub;	type = AB;	अवरोध;
			हाल FADD:	func = fadd;	type = AB;	अवरोध;
			हाल FSQRT:	func = fवर्ग_मूल;	type = XB;	अवरोध;
			हाल FRE:	func = fre;	type = XB;	अवरोध;
			हाल FSEL:	func = fsel;	type = ABC;	अवरोध;
			हाल FMUL:	func = fmul;	type = AC;	अवरोध;
			हाल FRSQRTE:	func = frवर्ग_मूलe;	type = XB;	अवरोध;
			हाल FMSUB:	func = fmsub;	type = ABC;	अवरोध;
			हाल FMADD:	func = fmadd;	type = ABC;	अवरोध;
			हाल FNMSUB:	func = fnmsub;	type = ABC;	अवरोध;
			हाल FNMADD:	func = fnmadd;	type = ABC;	अवरोध;
			शेष:
				जाओ illegal;
			पूर्ण
			अवरोध;
		पूर्ण

		चयन ((insn >> 1) & 0x3ff) अणु
		हाल FCMPU:	func = fcmpu;	type = XCR;	अवरोध;
		हाल FRSP:	func = frsp;	type = XB;	अवरोध;
		हाल FCTIW:	func = fctiw;	type = XB;	अवरोध;
		हाल FCTIWZ:	func = fctiwz;	type = XB;	अवरोध;
		हाल FCMPO:	func = fcmpo;	type = XCR;	अवरोध;
		हाल MTFSB1:	func = mtfsb1;	type = XCRB;	अवरोध;
		हाल FNEG:	func = fneg;	type = XB;	अवरोध;
		हाल MCRFS:	func = mcrfs;	type = XCRL;	अवरोध;
		हाल MTFSB0:	func = mtfsb0;	type = XCRB;	अवरोध;
		हाल FMR:	func = fmr;	type = XB;	अवरोध;
		हाल MTFSFI:	func = mtfsfi;	type = XCRI;	अवरोध;
		हाल FNABS:	func = fnअसल;	type = XB;	अवरोध;
		हाल FABS:	func = भ_असल;	type = XB;	अवरोध;
		हाल MFFS:	func = mffs;	type = X;	अवरोध;
		हाल MTFSF:	func = mtfsf;	type = XFLB;	अवरोध;
		शेष:
			जाओ illegal;
		पूर्ण
		अवरोध;

	शेष:
		जाओ illegal;
	पूर्ण

	चयन (type) अणु
	हाल AB:
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 16) & 0x1f);
		op2 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 11) & 0x1f);
		अवरोध;

	हाल AC:
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 16) & 0x1f);
		op2 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >>  6) & 0x1f);
		अवरोध;

	हाल ABC:
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 16) & 0x1f);
		op2 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 11) & 0x1f);
		op3 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >>  6) & 0x1f);
		अवरोध;

	हाल D:
		idx = (insn >> 16) & 0x1f;
		sdisp = (insn & 0xffff);
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)((idx ? regs->gpr[idx] : 0) + sdisp);
		अवरोध;

	हाल DU:
		idx = (insn >> 16) & 0x1f;
		अगर (!idx)
			जाओ illegal;

		sdisp = (insn & 0xffff);
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)(regs->gpr[idx] + sdisp);
		अवरोध;

	हाल X:
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		अवरोध;

	हाल XA:
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 16) & 0x1f);
		अवरोध;

	हाल XB:
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 11) & 0x1f);
		अवरोध;

	हाल XE:
		idx = (insn >> 16) & 0x1f;
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)((idx ? regs->gpr[idx] : 0)
				+ regs->gpr[(insn >> 11) & 0x1f]);
		अवरोध;

	हाल XEU:
		idx = (insn >> 16) & 0x1f;
		अगर (!idx)
			जाओ illegal;
		op0 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 21) & 0x1f);
		op1 = (व्योम *)(regs->gpr[idx]
				+ regs->gpr[(insn >> 11) & 0x1f]);
		अवरोध;

	हाल XCR:
		op0 = (व्योम *)&regs->ccr;
		op1 = (व्योम *)((insn >> 23) & 0x7);
		op2 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 16) & 0x1f);
		op3 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 11) & 0x1f);
		अवरोध;

	हाल XCRL:
		op0 = (व्योम *)&regs->ccr;
		op1 = (व्योम *)((insn >> 23) & 0x7);
		op2 = (व्योम *)((insn >> 18) & 0x7);
		अवरोध;

	हाल XCRB:
		op0 = (व्योम *)((insn >> 21) & 0x1f);
		अवरोध;

	हाल XCRI:
		op0 = (व्योम *)((insn >> 23) & 0x7);
		op1 = (व्योम *)((insn >> 12) & 0xf);
		अवरोध;

	हाल XFLB:
		op0 = (व्योम *)((insn >> 17) & 0xff);
		op1 = (व्योम *)&current->thपढ़ो.TS_FPR((insn >> 11) & 0x1f);
		अवरोध;

	शेष:
		जाओ illegal;
	पूर्ण

	/*
	 * If we support a HW FPU, we need to ensure the FP state
	 * is flushed पूर्णांकo the thपढ़ो_काष्ठा beक्रमe attempting
	 * emulation
	 */
	flush_fp_to_thपढ़ो(current);

	eflag = func(op0, op1, op2, op3);

	अगर (insn & 1) अणु
		regs->ccr &= ~(0x0f000000);
		regs->ccr |= (__FPU_FPSCR >> 4) & 0x0f000000;
	पूर्ण

	trap = record_exception(regs, eflag);
	अगर (trap)
		वापस 1;

	चयन (type) अणु
	हाल DU:
	हाल XEU:
		regs->gpr[idx] = (अचिन्हित दीर्घ)op1;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	regs->nip += 4;
	वापस 0;

illegal:
	वापस -ENOSYS;
पूर्ण
