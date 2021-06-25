<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sparc/math-emu/math.c
 *
 * Copyright (C) 1998 Peter Maydell (pmaydell@chiark.greenend.org.uk)
 * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1999 David S. Miller (davem@redhat.com)
 *
 * This is a good place to start अगर you're trying to understand the
 * emulation code, because it's pretty simple. What we करो is
 * essentially analyse the inकाष्ठाion to work out what the operation
 * is and which रेजिस्टरs are involved. We then execute the appropriate
 * FXXXX function. [The भग्नing poपूर्णांक queue पूर्णांकroduces a minor wrinkle;
 * see below...]
 * The fxxxxx.c files each emulate a single insn. They look relatively
 * simple because the complनिकासy is hidden away in an unholy tangle
 * of preprocessor macros.
 *
 * The first layer of macros is single.h, द्विगुन.h, quad.h. Generally
 * these files define macros क्रम working with भग्नing poपूर्णांक numbers
 * of the three IEEE क्रमmats. FP_ADD_D(R,A,B) is क्रम adding द्विगुनs,
 * क्रम instance. These macros are usually defined as calls to more
 * generic macros (in this हाल _FP_ADD(D,2,R,X,Y) where the number
 * of machine words required to store the given IEEE क्रमmat is passed
 * as a parameter. [द्विगुन.h and co check the number of bits in a word
 * and define FP_ADD_D & co appropriately].
 * The generic macros are defined in op-common.h. This is where all
 * the grotty stuff like handling NaNs is coded. To handle the possible
 * word sizes macros in op-common.h use macros like _FP_FRAC_SLL_##wc()
 * where wc is the 'number of machine words' parameter (here 2).
 * These are defined in the third layer of macros: op-1.h, op-2.h
 * and op-4.h. These handle operations on भग्नing poपूर्णांक numbers composed
 * of 1,2 and 4 machine words respectively. [For example, on sparc64
 * द्विगुनs are one machine word so macros in द्विगुन.h eventually use
 * स्थिरructs in op-1.h, but on sparc32 they use op-2.h definitions.]
 * soft-fp.h is on the same level as op-common.h, and defines some
 * macros which are independent of both word size and FP क्रमmat.
 * Finally, sfp-machine.h is the machine dependent part of the
 * code: it defines the word size and what type a word is. It also
 * defines how _FP_MUL_MEAT_t() maps to _FP_MUL_MEAT_n_* : op-n.h
 * provide several possible flavours of multiply algorithm, most
 * of which require that you supply some क्रमm of यंत्र or C primitive to
 * करो the actual multiply. (such यंत्र primitives should be defined
 * in sfp-machine.h too). uभागmodti4.c is the same sort of thing.
 *
 * There may be some errors here because I'm working from a
 * SPARC architecture manual V9, and what I really want is V8...
 * Also, the insns which can generate exceptions seem to be a
 * greater subset of the FPops than क्रम V9 (क्रम example, FCMPED
 * has to be emulated on V8). So I think I'm going to have
 * to emulate them all just to be on the safe side...
 *
 * Emulation routines originate from soft-fp package, which is
 * part of glibc and has appropriate copyrights in it (allegedly).
 *
 * NB: on sparc पूर्णांक == दीर्घ == 4 bytes, दीर्घ दीर्घ == 8 bytes.
 * Most bits of the kernel seem to go क्रम दीर्घ rather than पूर्णांक,
 * so we follow that practice...
 */

/* TODO:
 * fpsave() saves the FP queue but fpload() करोesn't reload it.
 * Thereक्रमe when we context चयन or change FPU ownership
 * we have to check to see अगर the queue had anything in it and
 * emulate it अगर it did. This is going to be a pain.
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

#समावेश "sfp-util_32.h"
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/द्विगुन.h>
#समावेश <math-emu/quad.h>

#घोषणा FLOATFUNC(x) बाह्य पूर्णांक x(व्योम *,व्योम *,व्योम *)

/* The Vn labels indicate what version of the SPARC architecture gas thinks
 * each insn is. This is from the binutils source :->
 */
/* quadword inकाष्ठाions */
#घोषणा FSQRTQ	0x02b		/* v8 */
#घोषणा FADDQ	0x043		/* v8 */
#घोषणा FSUBQ	0x047		/* v8 */
#घोषणा FMULQ	0x04b		/* v8 */
#घोषणा FDIVQ	0x04f		/* v8 */
#घोषणा FDMULQ	0x06e		/* v8 */
#घोषणा FQTOS	0x0c7		/* v8 */
#घोषणा FQTOD	0x0cb		/* v8 */
#घोषणा FITOQ	0x0cc		/* v8 */
#घोषणा FSTOQ	0x0cd		/* v8 */
#घोषणा FDTOQ	0x0ce		/* v8 */
#घोषणा FQTOI	0x0d3		/* v8 */
#घोषणा FCMPQ	0x053		/* v8 */
#घोषणा FCMPEQ	0x057		/* v8 */
/* single/द्विगुन inकाष्ठाions (subnormal): should all work */
#घोषणा FSQRTS	0x029		/* v7 */
#घोषणा FSQRTD	0x02a		/* v7 */
#घोषणा FADDS	0x041		/* v6 */
#घोषणा FADDD	0x042		/* v6 */
#घोषणा FSUBS	0x045		/* v6 */
#घोषणा FSUBD	0x046		/* v6 */
#घोषणा FMULS	0x049		/* v6 */
#घोषणा FMULD	0x04a		/* v6 */
#घोषणा FDIVS	0x04d		/* v6 */
#घोषणा FDIVD	0x04e		/* v6 */
#घोषणा FSMULD	0x069		/* v6 */
#घोषणा FDTOS	0x0c6		/* v6 */
#घोषणा FSTOD	0x0c9		/* v6 */
#घोषणा FSTOI	0x0d1		/* v6 */
#घोषणा FDTOI	0x0d2		/* v6 */
#घोषणा FABSS	0x009		/* v6 */
#घोषणा FCMPS	0x051		/* v6 */
#घोषणा FCMPES	0x055		/* v6 */
#घोषणा FCMPD	0x052		/* v6 */
#घोषणा FCMPED	0x056		/* v6 */
#घोषणा FMOVS	0x001		/* v6 */
#घोषणा FNEGS	0x005		/* v6 */
#घोषणा FITOS	0x0c4		/* v6 */
#घोषणा FITOD	0x0c8		/* v6 */

#घोषणा FSR_TEM_SHIFT	23UL
#घोषणा FSR_TEM_MASK	(0x1fUL << FSR_TEM_SHIFT)
#घोषणा FSR_AEXC_SHIFT	5UL
#घोषणा FSR_AEXC_MASK	(0x1fUL << FSR_AEXC_SHIFT)
#घोषणा FSR_CEXC_SHIFT	0UL
#घोषणा FSR_CEXC_MASK	(0x1fUL << FSR_CEXC_SHIFT)

अटल पूर्णांक करो_one_mathemu(u32 insn, अचिन्हित दीर्घ *fsr, अचिन्हित दीर्घ *fregs);

/* Unlike the Sparc64 version (which has a काष्ठा fpustate), we
 * pass the taskकाष्ठा corresponding to the task which currently owns the
 * FPU. This is partly because we करोn't have the fpustate काष्ठा and
 * partly because the task owning the FPU isn't always current (as is
 * the हाल क्रम the Sparc64 port). This is probably SMP-related...
 * This function वापसs 1 अगर all queued insns were emulated successfully.
 * The test क्रम unimplemented FPop in kernel mode has been moved पूर्णांकo
 * kernel/traps.c क्रम simplicity.
 */
पूर्णांक करो_mathemu(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *fpt)
अणु
	/* regs->pc isn't necessarily the PC at which the offending insn is sitting.
	 * The FPU मुख्यtains a queue of FPops which cause traps.
	 * When it hits an inकाष्ठाion that requires that the trapped op succeeded
	 * (usually because it पढ़ोs a reg. that the trapped op wrote) then it
	 * causes this exception. We need to emulate all the insns on the queue
	 * and then allow the op to proceed.
	 * This code should also handle the हाल where the trap was precise,
	 * in which हाल the queue length is zero and regs->pc poपूर्णांकs at the
	 * single FPop to be emulated. (this हाल is untested, though :->)
	 * You'll need this हाल अगर you want to be able to emulate all FPops
	 * because the FPU either करोesn't exist or has been software-disabled.
	 * [The UltraSPARC makes FP a precise trap; this isn't as stupid as it
	 * might sound because the Ultra करोes funky things with a superscalar
	 * architecture.]
	 */

	/* You wouldn't believe how often I typed 'ftp' when I meant 'fpt' :-> */

	पूर्णांक i;
	पूर्णांक retcode = 0;                               /* assume all succeed */
	अचिन्हित दीर्घ insn;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

#अगर_घोषित DEBUG_MATHEMU
	prपूर्णांकk("In do_mathemu()... pc is %08lx\n", regs->pc);
	prपूर्णांकk("fpqdepth is %ld\n", fpt->thपढ़ो.fpqdepth);
	क्रम (i = 0; i < fpt->thपढ़ो.fpqdepth; i++)
		prपूर्णांकk("%d: %08lx at %08lx\n", i, fpt->thपढ़ो.fpqueue[i].insn,
		       (अचिन्हित दीर्घ)fpt->thपढ़ो.fpqueue[i].insn_addr);
#पूर्ण_अगर

	अगर (fpt->thपढ़ो.fpqdepth == 0) अणु                   /* no queue, guilty insn is at regs->pc */
#अगर_घोषित DEBUG_MATHEMU
		prपूर्णांकk("precise trap at %08lx\n", regs->pc);
#पूर्ण_अगर
		अगर (!get_user(insn, (u32 __user *) regs->pc)) अणु
			retcode = करो_one_mathemu(insn, &fpt->thपढ़ो.fsr, fpt->thपढ़ो.भग्न_regs);
			अगर (retcode) अणु
				/* in this हाल we need to fix up PC & nPC */
				regs->pc = regs->npc;
				regs->npc += 4;
			पूर्ण
		पूर्ण
		वापस retcode;
	पूर्ण

	/* Normal हाल: need to empty the queue... */
	क्रम (i = 0; i < fpt->thपढ़ो.fpqdepth; i++) अणु
		retcode = करो_one_mathemu(fpt->thपढ़ो.fpqueue[i].insn, &(fpt->thपढ़ो.fsr), fpt->thपढ़ो.भग्न_regs);
		अगर (!retcode)                               /* insn failed, no poपूर्णांक करोing any more */
			अवरोध;
	पूर्ण
	/* Now empty the queue and clear the queue_not_empty flag */
	अगर (retcode)
		fpt->thपढ़ो.fsr &= ~(0x3000 | FSR_CEXC_MASK);
	अन्यथा
		fpt->thपढ़ो.fsr &= ~0x3000;
	fpt->thपढ़ो.fpqdepth = 0;

	वापस retcode;
पूर्ण

/* All routines वापसing an exception to उठाओ should detect
 * such exceptions _beक्रमe_ rounding to be consistent with
 * the behavior of the hardware in the implemented हालs
 * (and thus with the recommendations in the V9 architecture
 * manual).
 *
 * We वापस 0 अगर a संक_भ_त्रुटि should be sent, 1 otherwise.
 */
अटल अंतरभूत पूर्णांक record_exception(अचिन्हित दीर्घ *pfsr, पूर्णांक eflag)
अणु
	अचिन्हित दीर्घ fsr = *pfsr;
	पूर्णांक would_trap;

	/* Determine अगर this exception would have generated a trap. */
	would_trap = (fsr & ((दीर्घ)eflag << FSR_TEM_SHIFT)) != 0UL;

	/* If trapping, we only want to संकेत one bit. */
	अगर (would_trap != 0) अणु
		eflag &= ((fsr & FSR_TEM_MASK) >> FSR_TEM_SHIFT);
		अगर ((eflag & (eflag - 1)) != 0) अणु
			अगर (eflag & FP_EX_INVALID)
				eflag = FP_EX_INVALID;
			अन्यथा अगर (eflag & FP_EX_OVERFLOW)
				eflag = FP_EX_OVERFLOW;
			अन्यथा अगर (eflag & FP_EX_UNDERFLOW)
				eflag = FP_EX_UNDERFLOW;
			अन्यथा अगर (eflag & FP_EX_DIVZERO)
				eflag = FP_EX_DIVZERO;
			अन्यथा अगर (eflag & FP_EX_INEXACT)
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
	अगर (would_trap == 0)
		fsr |= ((दीर्घ)eflag << FSR_AEXC_SHIFT);

	/* If trapping, indicate fault trap type IEEE. */
	अगर (would_trap != 0)
		fsr |= (1UL << 14);

	*pfsr = fsr;

	वापस (would_trap ? 0 : 1);
पूर्ण

प्रकार जोड़ अणु
	u32 s;
	u64 d;
	u64 q[2];
पूर्ण *argp;

अटल पूर्णांक करो_one_mathemu(u32 insn, अचिन्हित दीर्घ *pfsr, अचिन्हित दीर्घ *fregs)
अणु
	/* Emulate the given insn, updating fsr and fregs appropriately. */
	पूर्णांक type = 0;
	/* r is rd, b is rs2 and a is rs1. The *u arg tells
	   whether the argument should be packed/unpacked (0 - करो not unpack/pack, 1 - unpack/pack)
	   non-u args tells the size of the argument (0 - no argument, 1 - single, 2 - द्विगुन, 3 - quad */
#घोषणा TYPE(dummy, r, ru, b, bu, a, au) type = (au << 2) | (a << 0) | (bu << 5) | (b << 3) | (ru << 8) | (r << 6)
	पूर्णांक freg;
	argp rs1 = शून्य, rs2 = शून्य, rd = शून्य;
	FP_DECL_EX;
	FP_DECL_S(SA); FP_DECL_S(SB); FP_DECL_S(SR);
	FP_DECL_D(DA); FP_DECL_D(DB); FP_DECL_D(DR);
	FP_DECL_Q(QA); FP_DECL_Q(QB); FP_DECL_Q(QR);
	पूर्णांक IR;
	दीर्घ fsr;

#अगर_घोषित DEBUG_MATHEMU
	prपूर्णांकk("In do_mathemu(), emulating %08lx\n", insn);
#पूर्ण_अगर

	अगर ((insn & 0xc1f80000) == 0x81a00000)	/* FPOP1 */ अणु
		चयन ((insn >> 5) & 0x1ff) अणु
		हाल FSQRTQ: TYPE(3,3,1,3,1,0,0); अवरोध;
		हाल FADDQ:
		हाल FSUBQ:
		हाल FMULQ:
		हाल FDIVQ: TYPE(3,3,1,3,1,3,1); अवरोध;
		हाल FDMULQ: TYPE(3,3,1,2,1,2,1); अवरोध;
		हाल FQTOS: TYPE(3,1,1,3,1,0,0); अवरोध;
		हाल FQTOD: TYPE(3,2,1,3,1,0,0); अवरोध;
		हाल FITOQ: TYPE(3,3,1,1,0,0,0); अवरोध;
		हाल FSTOQ: TYPE(3,3,1,1,1,0,0); अवरोध;
		हाल FDTOQ: TYPE(3,3,1,2,1,0,0); अवरोध;
		हाल FQTOI: TYPE(3,1,0,3,1,0,0); अवरोध;
		हाल FSQRTS: TYPE(2,1,1,1,1,0,0); अवरोध;
		हाल FSQRTD: TYPE(2,2,1,2,1,0,0); अवरोध;
		हाल FADDD:
		हाल FSUBD:
		हाल FMULD:
		हाल FDIVD: TYPE(2,2,1,2,1,2,1); अवरोध;
		हाल FADDS:
		हाल FSUBS:
		हाल FMULS:
		हाल FDIVS: TYPE(2,1,1,1,1,1,1); अवरोध;
		हाल FSMULD: TYPE(2,2,1,1,1,1,1); अवरोध;
		हाल FDTOS: TYPE(2,1,1,2,1,0,0); अवरोध;
		हाल FSTOD: TYPE(2,2,1,1,1,0,0); अवरोध;
		हाल FSTOI: TYPE(2,1,0,1,1,0,0); अवरोध;
		हाल FDTOI: TYPE(2,1,0,2,1,0,0); अवरोध;
		हाल FITOS: TYPE(2,1,1,1,0,0,0); अवरोध;
		हाल FITOD: TYPE(2,2,1,1,0,0,0); अवरोध;
		हाल FMOVS:
		हाल FABSS:
		हाल FNEGS: TYPE(2,1,0,1,0,0,0); अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर ((insn & 0xc1f80000) == 0x81a80000)	/* FPOP2 */ अणु
		चयन ((insn >> 5) & 0x1ff) अणु
		हाल FCMPS: TYPE(3,0,0,1,1,1,1); अवरोध;
		हाल FCMPES: TYPE(3,0,0,1,1,1,1); अवरोध;
		हाल FCMPD: TYPE(3,0,0,2,1,2,1); अवरोध;
		हाल FCMPED: TYPE(3,0,0,2,1,2,1); अवरोध;
		हाल FCMPQ: TYPE(3,0,0,3,1,3,1); अवरोध;
		हाल FCMPEQ: TYPE(3,0,0,3,1,3,1); अवरोध;
		पूर्ण
	पूर्ण

	अगर (!type) अणु	/* oops, didn't recognise that FPop */
#अगर_घोषित DEBUG_MATHEMU
		prपूर्णांकk("attempt to emulate unrecognised FPop!\n");
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	/* Decode the रेजिस्टरs to be used */
	freg = (*pfsr >> 14) & 0xf;

	*pfsr &= ~0x1c000;				/* clear the traptype bits */
	
	freg = ((insn >> 14) & 0x1f);
	चयन (type & 0x3) अणु				/* is rs1 single, द्विगुन or quad? */
	हाल 3:
		अगर (freg & 3) अणु				/* quadwords must have bits 4&5 of the */
							/* encoded reg. number set to zero. */
			*pfsr |= (6 << 14);
			वापस 0;			/* simulate invalid_fp_रेजिस्टर exception */
		पूर्ण
		fallthrough;
	हाल 2:
		अगर (freg & 1) अणु				/* द्विगुनwords must have bit 5 zeroed */
			*pfsr |= (6 << 14);
			वापस 0;
		पूर्ण
	पूर्ण
	rs1 = (argp)&fregs[freg];
	चयन (type & 0x7) अणु
	हाल 7: FP_UNPACK_QP (QA, rs1); अवरोध;
	हाल 6: FP_UNPACK_DP (DA, rs1); अवरोध;
	हाल 5: FP_UNPACK_SP (SA, rs1); अवरोध;
	पूर्ण
	freg = (insn & 0x1f);
	चयन ((type >> 3) & 0x3) अणु			/* same again क्रम rs2 */
	हाल 3:
		अगर (freg & 3) अणु				/* quadwords must have bits 4&5 of the */
							/* encoded reg. number set to zero. */
			*pfsr |= (6 << 14);
			वापस 0;			/* simulate invalid_fp_रेजिस्टर exception */
		पूर्ण
		fallthrough;
	हाल 2:
		अगर (freg & 1) अणु				/* द्विगुनwords must have bit 5 zeroed */
			*pfsr |= (6 << 14);
			वापस 0;
		पूर्ण
	पूर्ण
	rs2 = (argp)&fregs[freg];
	चयन ((type >> 3) & 0x7) अणु
	हाल 7: FP_UNPACK_QP (QB, rs2); अवरोध;
	हाल 6: FP_UNPACK_DP (DB, rs2); अवरोध;
	हाल 5: FP_UNPACK_SP (SB, rs2); अवरोध;
	पूर्ण
	freg = ((insn >> 25) & 0x1f);
	चयन ((type >> 6) & 0x3) अणु			/* and finally rd. This one's a bit dअगरferent */
	हाल 0:						/* dest is fcc. (this must be FCMPQ or FCMPEQ) */
		अगर (freg) अणु				/* V8 has only one set of condition codes, so */
							/* anything but 0 in the rd field is an error */
			*pfsr |= (6 << 14);		/* (should probably flag as invalid opcode */
			वापस 0;			/* but संक_भ_त्रुटि will करो :-> ) */
		पूर्ण
		अवरोध;
	हाल 3:
		अगर (freg & 3) अणु				/* quadwords must have bits 4&5 of the */
							/* encoded reg. number set to zero. */
			*pfsr |= (6 << 14);
			वापस 0;			/* simulate invalid_fp_रेजिस्टर exception */
		पूर्ण
		fallthrough;
	हाल 2:
		अगर (freg & 1) अणु				/* द्विगुनwords must have bit 5 zeroed */
			*pfsr |= (6 << 14);
			वापस 0;
		पूर्ण
		fallthrough;
	हाल 1:
		rd = (व्योम *)&fregs[freg];
		अवरोध;
	पूर्ण
#अगर_घोषित DEBUG_MATHEMU
	prपूर्णांकk("executing insn...\n");
#पूर्ण_अगर
	/* करो the Right Thing */
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
	हाल FSMULD: FP_CONV (D, S, 2, 1, DA, SA);
		     FP_CONV (D, S, 2, 1, DB, SB);
	हाल FMULD: FP_MUL_D (DR, DA, DB); अवरोध;
	हाल FDMULQ: FP_CONV (Q, D, 4, 2, QA, DA);
		     FP_CONV (Q, D, 4, 2, QB, DB);
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
	हाल FMOVS: rd->s = rs2->s; अवरोध;
	हाल FABSS: rd->s = rs2->s & 0x7fffffff; अवरोध;
	हाल FNEGS: rd->s = rs2->s ^ 0x80000000; अवरोध;
	/* भग्न to पूर्णांक */
	हाल FSTOI: FP_TO_INT_S (IR, SB, 32, 1); अवरोध;
	हाल FDTOI: FP_TO_INT_D (IR, DB, 32, 1); अवरोध;
	हाल FQTOI: FP_TO_INT_Q (IR, QB, 32, 1); अवरोध;
	/* पूर्णांक to भग्न */
	हाल FITOS: IR = rs2->s; FP_FROM_INT_S (SR, IR, 32, पूर्णांक); अवरोध;
	हाल FITOD: IR = rs2->s; FP_FROM_INT_D (DR, IR, 32, पूर्णांक); अवरोध;
	हाल FITOQ: IR = rs2->s; FP_FROM_INT_Q (QR, IR, 32, पूर्णांक); अवरोध;
	/* भग्न to भग्न */
	हाल FSTOD: FP_CONV (D, S, 2, 1, DR, SB); अवरोध;
	हाल FSTOQ: FP_CONV (Q, S, 4, 1, QR, SB); अवरोध;
	हाल FDTOQ: FP_CONV (Q, D, 4, 2, QR, DB); अवरोध;
	हाल FDTOS: FP_CONV (S, D, 1, 2, SR, DB); अवरोध;
	हाल FQTOS: FP_CONV (S, Q, 1, 4, SR, QB); अवरोध;
	हाल FQTOD: FP_CONV (D, Q, 2, 4, DR, QB); अवरोध;
	/* comparison */
	हाल FCMPS:
	हाल FCMPES:
		FP_CMP_S(IR, SB, SA, 3);
		अगर (IR == 3 &&
		    (((insn >> 5) & 0x1ff) == FCMPES ||
		     FP_ISSIGन_अंक_S(SA) ||
		     FP_ISSIGन_अंक_S(SB)))
			FP_SET_EXCEPTION (FP_EX_INVALID);
		अवरोध;
	हाल FCMPD:
	हाल FCMPED:
		FP_CMP_D(IR, DB, DA, 3);
		अगर (IR == 3 &&
		    (((insn >> 5) & 0x1ff) == FCMPED ||
		     FP_ISSIGन_अंक_D(DA) ||
		     FP_ISSIGन_अंक_D(DB)))
			FP_SET_EXCEPTION (FP_EX_INVALID);
		अवरोध;
	हाल FCMPQ:
	हाल FCMPEQ:
		FP_CMP_Q(IR, QB, QA, 3);
		अगर (IR == 3 &&
		    (((insn >> 5) & 0x1ff) == FCMPEQ ||
		     FP_ISSIGन_अंक_Q(QA) ||
		     FP_ISSIGन_अंक_Q(QB)))
			FP_SET_EXCEPTION (FP_EX_INVALID);
	पूर्ण
	अगर (!FP_INHIBIT_RESULTS) अणु
		चयन ((type >> 6) & 0x7) अणु
		हाल 0: fsr = *pfsr;
			अगर (IR == -1) IR = 2;
			/* fcc is always fcc0 */
			fsr &= ~0xc00; fsr |= (IR << 10);
			*pfsr = fsr;
			अवरोध;
		हाल 1: rd->s = IR; अवरोध;
		हाल 5: FP_PACK_SP (rd, SR); अवरोध;
		हाल 6: FP_PACK_DP (rd, DR); अवरोध;
		हाल 7: FP_PACK_QP (rd, QR); अवरोध;
		पूर्ण
	पूर्ण
	अगर (_fex == 0)
		वापस 1;				/* success! */
	वापस record_exception(pfsr, _fex);
पूर्ण
