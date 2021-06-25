<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Save/restore भग्नing poपूर्णांक context क्रम संकेत handlers.
 *
 * Copyright (C) 1999, 2000  Kaz Kojima & Niibe Yutaka
 * Copyright (C) 2006  ST Microelectronics Ltd. (denorm support)
 *
 * FIXME! These routines have not been tested क्रम big endian हाल.
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/पन.स>
#समावेश <cpu/fpu.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/traps.h>

/* The PR (precision) bit in the FP Status Register must be clear when
 * an frchg inकाष्ठाion is executed, otherwise the inकाष्ठाion is undefined.
 * Executing frchg with PR set causes a trap on some SH4 implementations.
 */

#घोषणा FPSCR_RCHG 0x00000000
बाह्य अचिन्हित दीर्घ दीर्घ भग्न64_भाग(अचिन्हित दीर्घ दीर्घ a,
				      अचिन्हित दीर्घ दीर्घ b);
बाह्य अचिन्हित दीर्घ पूर्णांक भग्न32_भाग(अचिन्हित दीर्घ पूर्णांक a, अचिन्हित दीर्घ पूर्णांक b);
बाह्य अचिन्हित दीर्घ दीर्घ भग्न64_mul(अचिन्हित दीर्घ दीर्घ a,
				      अचिन्हित दीर्घ दीर्घ b);
बाह्य अचिन्हित दीर्घ पूर्णांक भग्न32_mul(अचिन्हित दीर्घ पूर्णांक a, अचिन्हित दीर्घ पूर्णांक b);
बाह्य अचिन्हित दीर्घ दीर्घ भग्न64_add(अचिन्हित दीर्घ दीर्घ a,
				      अचिन्हित दीर्घ दीर्घ b);
बाह्य अचिन्हित दीर्घ पूर्णांक भग्न32_add(अचिन्हित दीर्घ पूर्णांक a, अचिन्हित दीर्घ पूर्णांक b);
बाह्य अचिन्हित दीर्घ दीर्घ भग्न64_sub(अचिन्हित दीर्घ दीर्घ a,
				      अचिन्हित दीर्घ दीर्घ b);
बाह्य अचिन्हित दीर्घ पूर्णांक भग्न32_sub(अचिन्हित दीर्घ पूर्णांक a, अचिन्हित दीर्घ पूर्णांक b);
बाह्य अचिन्हित दीर्घ पूर्णांक भग्न64_to_भग्न32(अचिन्हित दीर्घ दीर्घ a);
अटल अचिन्हित पूर्णांक fpu_exception_flags;

/*
 * Save FPU रेजिस्टरs onto task काष्ठाure.
 */
व्योम save_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ dummy;

	enable_fpu();
	यंत्र अस्थिर ("sts.l	fpul, @-%0\n\t"
		      "sts.l	fpscr, @-%0\n\t"
		      "lds	%2, fpscr\n\t"
		      "frchg\n\t"
		      "fmov.s	fr15, @-%0\n\t"
		      "fmov.s	fr14, @-%0\n\t"
		      "fmov.s	fr13, @-%0\n\t"
		      "fmov.s	fr12, @-%0\n\t"
		      "fmov.s	fr11, @-%0\n\t"
		      "fmov.s	fr10, @-%0\n\t"
		      "fmov.s	fr9, @-%0\n\t"
		      "fmov.s	fr8, @-%0\n\t"
		      "fmov.s	fr7, @-%0\n\t"
		      "fmov.s	fr6, @-%0\n\t"
		      "fmov.s	fr5, @-%0\n\t"
		      "fmov.s	fr4, @-%0\n\t"
		      "fmov.s	fr3, @-%0\n\t"
		      "fmov.s	fr2, @-%0\n\t"
		      "fmov.s	fr1, @-%0\n\t"
		      "fmov.s	fr0, @-%0\n\t"
		      "frchg\n\t"
		      "fmov.s	fr15, @-%0\n\t"
		      "fmov.s	fr14, @-%0\n\t"
		      "fmov.s	fr13, @-%0\n\t"
		      "fmov.s	fr12, @-%0\n\t"
		      "fmov.s	fr11, @-%0\n\t"
		      "fmov.s	fr10, @-%0\n\t"
		      "fmov.s	fr9, @-%0\n\t"
		      "fmov.s	fr8, @-%0\n\t"
		      "fmov.s	fr7, @-%0\n\t"
		      "fmov.s	fr6, @-%0\n\t"
		      "fmov.s	fr5, @-%0\n\t"
		      "fmov.s	fr4, @-%0\n\t"
		      "fmov.s	fr3, @-%0\n\t"
		      "fmov.s	fr2, @-%0\n\t"
		      "fmov.s	fr1, @-%0\n\t"
		      "fmov.s	fr0, @-%0\n\t"
		      "lds	%3, fpscr\n\t":"=r" (dummy)
		      :"0"((अक्षर *)(&tsk->thपढ़ो.xstate->hardfpu.status)),
		      "r"(FPSCR_RCHG), "r"(FPSCR_INIT)
		      :"memory");

	disable_fpu();
पूर्ण

व्योम restore_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ dummy;

	enable_fpu();
	यंत्र अस्थिर ("lds	%2, fpscr\n\t"
		      "fmov.s	@%0+, fr0\n\t"
		      "fmov.s	@%0+, fr1\n\t"
		      "fmov.s	@%0+, fr2\n\t"
		      "fmov.s	@%0+, fr3\n\t"
		      "fmov.s	@%0+, fr4\n\t"
		      "fmov.s	@%0+, fr5\n\t"
		      "fmov.s	@%0+, fr6\n\t"
		      "fmov.s	@%0+, fr7\n\t"
		      "fmov.s	@%0+, fr8\n\t"
		      "fmov.s	@%0+, fr9\n\t"
		      "fmov.s	@%0+, fr10\n\t"
		      "fmov.s	@%0+, fr11\n\t"
		      "fmov.s	@%0+, fr12\n\t"
		      "fmov.s	@%0+, fr13\n\t"
		      "fmov.s	@%0+, fr14\n\t"
		      "fmov.s	@%0+, fr15\n\t"
		      "frchg\n\t"
		      "fmov.s	@%0+, fr0\n\t"
		      "fmov.s	@%0+, fr1\n\t"
		      "fmov.s	@%0+, fr2\n\t"
		      "fmov.s	@%0+, fr3\n\t"
		      "fmov.s	@%0+, fr4\n\t"
		      "fmov.s	@%0+, fr5\n\t"
		      "fmov.s	@%0+, fr6\n\t"
		      "fmov.s	@%0+, fr7\n\t"
		      "fmov.s	@%0+, fr8\n\t"
		      "fmov.s	@%0+, fr9\n\t"
		      "fmov.s	@%0+, fr10\n\t"
		      "fmov.s	@%0+, fr11\n\t"
		      "fmov.s	@%0+, fr12\n\t"
		      "fmov.s	@%0+, fr13\n\t"
		      "fmov.s	@%0+, fr14\n\t"
		      "fmov.s	@%0+, fr15\n\t"
		      "frchg\n\t"
		      "lds.l	@%0+, fpscr\n\t"
		      "lds.l	@%0+, fpul\n\t"
		      :"=r" (dummy)
		      :"0" (tsk->thपढ़ो.xstate), "r" (FPSCR_RCHG)
		      :"memory");
	disable_fpu();
पूर्ण

/**
 *      denormal_to_द्विगुन - Given denormalized भग्न number,
 *                           store द्विगुन भग्न
 *
 *      @fpu: Poपूर्णांकer to sh_fpu_hard काष्ठाure
 *      @n: Index to FP रेजिस्टर
 */
अटल व्योम denormal_to_द्विगुन(काष्ठा sh_fpu_hard_काष्ठा *fpu, पूर्णांक n)
अणु
	अचिन्हित दीर्घ du, dl;
	अचिन्हित दीर्घ x = fpu->fpul;
	पूर्णांक exp = 1023 - 126;

	अगर (x != 0 && (x & 0x7f800000) == 0) अणु
		du = (x & 0x80000000);
		जबतक ((x & 0x00800000) == 0) अणु
			x <<= 1;
			exp--;
		पूर्ण
		x &= 0x007fffff;
		du |= (exp << 20) | (x >> 3);
		dl = x << 29;

		fpu->fp_regs[n] = du;
		fpu->fp_regs[n + 1] = dl;
	पूर्ण
पूर्ण

/**
 *	ieee_fpe_handler - Handle denormalized number exception
 *
 *	@regs: Poपूर्णांकer to रेजिस्टर काष्ठाure
 *
 *	Returns 1 when it's handled (should not cause exception).
 */
अटल पूर्णांक ieee_fpe_handler(काष्ठा pt_regs *regs)
अणु
	अचिन्हित लघु insn = *(अचिन्हित लघु *)regs->pc;
	अचिन्हित लघु finsn;
	अचिन्हित दीर्घ nextpc;
	पूर्णांक nib[4] = अणु
		(insn >> 12) & 0xf,
		(insn >> 8) & 0xf,
		(insn >> 4) & 0xf,
		insn & 0xf
	पूर्ण;

	अगर (nib[0] == 0xb || (nib[0] == 0x4 && nib[2] == 0x0 && nib[3] == 0xb))
		regs->pr = regs->pc + 4;  /* bsr & jsr */

	अगर (nib[0] == 0xa || nib[0] == 0xb) अणु
		/* bra & bsr */
		nextpc = regs->pc + 4 + ((लघु)((insn & 0xfff) << 4) >> 3);
		finsn = *(अचिन्हित लघु *)(regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x8 && nib[1] == 0xd) अणु
		/* bt/s */
		अगर (regs->sr & 1)
			nextpc = regs->pc + 4 + ((अक्षर)(insn & 0xff) << 1);
		अन्यथा
			nextpc = regs->pc + 4;
		finsn = *(अचिन्हित लघु *)(regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x8 && nib[1] == 0xf) अणु
		/* bf/s */
		अगर (regs->sr & 1)
			nextpc = regs->pc + 4;
		अन्यथा
			nextpc = regs->pc + 4 + ((अक्षर)(insn & 0xff) << 1);
		finsn = *(अचिन्हित लघु *)(regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x4 && nib[3] == 0xb &&
		   (nib[2] == 0x0 || nib[2] == 0x2)) अणु
		/* jmp & jsr */
		nextpc = regs->regs[nib[1]];
		finsn = *(अचिन्हित लघु *)(regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x0 && nib[3] == 0x3 &&
		   (nib[2] == 0x0 || nib[2] == 0x2)) अणु
		/* braf & bsrf */
		nextpc = regs->pc + 4 + regs->regs[nib[1]];
		finsn = *(अचिन्हित लघु *)(regs->pc + 2);
	पूर्ण अन्यथा अगर (insn == 0x000b) अणु
		/* rts */
		nextpc = regs->pr;
		finsn = *(अचिन्हित लघु *)(regs->pc + 2);
	पूर्ण अन्यथा अणु
		nextpc = regs->pc + inकाष्ठाion_size(insn);
		finsn = insn;
	पूर्ण

	अगर ((finsn & 0xf1ff) == 0xf0ad) अणु
		/* fcnvsd */
		काष्ठा task_काष्ठा *tsk = current;

		अगर ((tsk->thपढ़ो.xstate->hardfpu.fpscr & FPSCR_CAUSE_ERROR))
			/* FPU error */
			denormal_to_द्विगुन(&tsk->thपढ़ो.xstate->hardfpu,
					   (finsn >> 8) & 0xf);
		अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण अन्यथा अगर ((finsn & 0xf00f) == 0xf002) अणु
		/* fmul */
		काष्ठा task_काष्ठा *tsk = current;
		पूर्णांक fpscr;
		पूर्णांक n, m, prec;
		अचिन्हित पूर्णांक hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thपढ़ो.xstate->hardfpu.fp_regs[n];
		hy = tsk->thपढ़ो.xstate->hardfpu.fp_regs[m];
		fpscr = tsk->thपढ़ो.xstate->hardfpu.fpscr;
		prec = fpscr & FPSCR_DBL_PRECISION;

		अगर ((fpscr & FPSCR_CAUSE_ERROR)
		    && (prec && ((hx & 0x7fffffff) < 0x00100000
				 || (hy & 0x7fffffff) < 0x00100000))) अणु
			दीर्घ दीर्घ llx, lly;

			/* FPU error because of denormal (द्विगुनs) */
			llx = ((दीर्घ दीर्घ)hx << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[n + 1];
			lly = ((दीर्घ दीर्घ)hy << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[m + 1];
			llx = भग्न64_mul(llx, lly);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = llx >> 32;
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n + 1] = llx & 0xffffffff;
		पूर्ण अन्यथा अगर ((fpscr & FPSCR_CAUSE_ERROR)
			   && (!prec && ((hx & 0x7fffffff) < 0x00800000
					 || (hy & 0x7fffffff) < 0x00800000))) अणु
			/* FPU error because of denormal (भग्नs) */
			hx = भग्न32_mul(hx, hy);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = hx;
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण अन्यथा अगर ((finsn & 0xf00e) == 0xf000) अणु
		/* fadd, fsub */
		काष्ठा task_काष्ठा *tsk = current;
		पूर्णांक fpscr;
		पूर्णांक n, m, prec;
		अचिन्हित पूर्णांक hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thपढ़ो.xstate->hardfpu.fp_regs[n];
		hy = tsk->thपढ़ो.xstate->hardfpu.fp_regs[m];
		fpscr = tsk->thपढ़ो.xstate->hardfpu.fpscr;
		prec = fpscr & FPSCR_DBL_PRECISION;

		अगर ((fpscr & FPSCR_CAUSE_ERROR)
		    && (prec && ((hx & 0x7fffffff) < 0x00100000
				 || (hy & 0x7fffffff) < 0x00100000))) अणु
			दीर्घ दीर्घ llx, lly;

			/* FPU error because of denormal (द्विगुनs) */
			llx = ((दीर्घ दीर्घ)hx << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[n + 1];
			lly = ((दीर्घ दीर्घ)hy << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[m + 1];
			अगर ((finsn & 0xf00f) == 0xf000)
				llx = भग्न64_add(llx, lly);
			अन्यथा
				llx = भग्न64_sub(llx, lly);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = llx >> 32;
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n + 1] = llx & 0xffffffff;
		पूर्ण अन्यथा अगर ((fpscr & FPSCR_CAUSE_ERROR)
			   && (!prec && ((hx & 0x7fffffff) < 0x00800000
					 || (hy & 0x7fffffff) < 0x00800000))) अणु
			/* FPU error because of denormal (भग्नs) */
			अगर ((finsn & 0xf00f) == 0xf000)
				hx = भग्न32_add(hx, hy);
			अन्यथा
				hx = भग्न32_sub(hx, hy);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = hx;
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण अन्यथा अगर ((finsn & 0xf003) == 0xf003) अणु
		/* fभाग */
		काष्ठा task_काष्ठा *tsk = current;
		पूर्णांक fpscr;
		पूर्णांक n, m, prec;
		अचिन्हित पूर्णांक hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thपढ़ो.xstate->hardfpu.fp_regs[n];
		hy = tsk->thपढ़ो.xstate->hardfpu.fp_regs[m];
		fpscr = tsk->thपढ़ो.xstate->hardfpu.fpscr;
		prec = fpscr & FPSCR_DBL_PRECISION;

		अगर ((fpscr & FPSCR_CAUSE_ERROR)
		    && (prec && ((hx & 0x7fffffff) < 0x00100000
				 || (hy & 0x7fffffff) < 0x00100000))) अणु
			दीर्घ दीर्घ llx, lly;

			/* FPU error because of denormal (द्विगुनs) */
			llx = ((दीर्घ दीर्घ)hx << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[n + 1];
			lly = ((दीर्घ दीर्घ)hy << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[m + 1];

			llx = भग्न64_भाग(llx, lly);

			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = llx >> 32;
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n + 1] = llx & 0xffffffff;
		पूर्ण अन्यथा अगर ((fpscr & FPSCR_CAUSE_ERROR)
			   && (!prec && ((hx & 0x7fffffff) < 0x00800000
					 || (hy & 0x7fffffff) < 0x00800000))) अणु
			/* FPU error because of denormal (भग्नs) */
			hx = भग्न32_भाग(hx, hy);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = hx;
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण अन्यथा अगर ((finsn & 0xf0bd) == 0xf0bd) अणु
		/* fcnvds - द्विगुन to single precision convert */
		काष्ठा task_काष्ठा *tsk = current;
		पूर्णांक m;
		अचिन्हित पूर्णांक hx;

		m = (finsn >> 8) & 0x7;
		hx = tsk->thपढ़ो.xstate->hardfpu.fp_regs[m];

		अगर ((tsk->thपढ़ो.xstate->hardfpu.fpscr & FPSCR_CAUSE_ERROR)
			&& ((hx & 0x7fffffff) < 0x00100000)) अणु
			/* subnormal द्विगुन to भग्न conversion */
			दीर्घ दीर्घ llx;

			llx = ((दीर्घ दीर्घ)tsk->thपढ़ो.xstate->hardfpu.fp_regs[m] << 32)
			    | tsk->thपढ़ो.xstate->hardfpu.fp_regs[m + 1];

			tsk->thपढ़ो.xstate->hardfpu.fpul = भग्न64_to_भग्न32(llx);
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम भग्न_उठाओ(अचिन्हित पूर्णांक flags)
अणु
	fpu_exception_flags |= flags;
पूर्ण

पूर्णांक भग्न_rounding_mode(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक roundingMode = FPSCR_ROUNDING_MODE(tsk->thपढ़ो.xstate->hardfpu.fpscr);
	वापस roundingMode;
पूर्ण

BUILD_TRAP_HANDLER(fpu_error)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	TRAP_HANDLER_DECL;

	__unlazy_fpu(tsk, regs);
	fpu_exception_flags = 0;
	अगर (ieee_fpe_handler(regs)) अणु
		tsk->thपढ़ो.xstate->hardfpu.fpscr &=
		    ~(FPSCR_CAUSE_MASK | FPSCR_FLAG_MASK);
		tsk->thपढ़ो.xstate->hardfpu.fpscr |= fpu_exception_flags;
		/* Set the FPSCR flag as well as cause bits - simply
		 * replicate the cause */
		tsk->thपढ़ो.xstate->hardfpu.fpscr |= (fpu_exception_flags >> 10);
		grab_fpu(regs);
		restore_fpu(tsk);
		task_thपढ़ो_info(tsk)->status |= TS_USEDFPU;
		अगर ((((tsk->thपढ़ो.xstate->hardfpu.fpscr & FPSCR_ENABLE_MASK) >> 7) &
		     (fpu_exception_flags >> 2)) == 0) अणु
			वापस;
		पूर्ण
	पूर्ण

	क्रमce_sig(संक_भ_त्रुटि);
पूर्ण
