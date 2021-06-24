<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Save/restore भग्नing poपूर्णांक context क्रम संकेत handlers.
 *
 * Copyright (C) 1999, 2000  Kaz Kojima & Niibe Yutaka
 *
 * FIXME! These routines can be optimized in big endian हाल.
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/traps.h>

/* The PR (precision) bit in the FP Status Register must be clear when
 * an frchg inकाष्ठाion is executed, otherwise the inकाष्ठाion is undefined.
 * Executing frchg with PR set causes a trap on some SH4 implementations.
 */

#घोषणा FPSCR_RCHG 0x00000000


/*
 * Save FPU रेजिस्टरs onto task काष्ठाure.
 */
व्योम save_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ dummy;

	enable_fpu();
	यंत्र अस्थिर("sts.l	fpul, @-%0\n\t"
		     "sts.l	fpscr, @-%0\n\t"
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
		     "lds	%3, fpscr\n\t"
		     : "=r" (dummy)
		     : "0" ((अक्षर *)(&tsk->thपढ़ो.xstate->hardfpu.status)),
		       "r" (FPSCR_RCHG),
		       "r" (FPSCR_INIT)
		     : "memory");

	disable_fpu();
पूर्ण

व्योम restore_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ dummy;

	enable_fpu();
	यंत्र अस्थिर("fmov.s	@%0+, fr0\n\t"
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
		     "lds.l	@%0+, fpscr\n\t"
		     "lds.l	@%0+, fpul\n\t"
		     : "=r" (dummy)
		     : "0" (tsk->thपढ़ो.xstate), "r" (FPSCR_RCHG)
		     : "memory");
	disable_fpu();
पूर्ण

/*
 *	Emulate arithmetic ops on denormalized number क्रम some FPU insns.
 */

/* denormalized भग्न * भग्न */
अटल पूर्णांक denormal_mulf(पूर्णांक hx, पूर्णांक hy)
अणु
	अचिन्हित पूर्णांक ix, iy;
	अचिन्हित दीर्घ दीर्घ m, n;
	पूर्णांक exp, w;

	ix = hx & 0x7fffffff;
	iy = hy & 0x7fffffff;
	अगर (iy < 0x00800000 || ix == 0)
		वापस ((hx ^ hy) & 0x80000000);

	exp = (iy & 0x7f800000) >> 23;
	ix &= 0x007fffff;
	iy = (iy & 0x007fffff) | 0x00800000;
	m = (अचिन्हित दीर्घ दीर्घ)ix * iy;
	n = m;
	w = -1;
	जबतक (n) अणु n >>= 1; w++; पूर्ण

	/* FIXME: use guard bits */
	exp += w - 126 - 46;
	अगर (exp > 0)
		ix = ((पूर्णांक) (m >> (w - 23)) & 0x007fffff) | (exp << 23);
	अन्यथा अगर (exp + 22 >= 0)
		ix = (पूर्णांक) (m >> (w - 22 - exp)) & 0x007fffff;
	अन्यथा
		ix = 0;

	ix |= (hx ^ hy) & 0x80000000;
	वापस ix;
पूर्ण

/* denormalized द्विगुन * द्विगुन */
अटल व्योम mult64(अचिन्हित दीर्घ दीर्घ x, अचिन्हित दीर्घ दीर्घ y,
		अचिन्हित दीर्घ दीर्घ *highp, अचिन्हित दीर्घ दीर्घ *lowp)
अणु
	अचिन्हित दीर्घ दीर्घ sub0, sub1, sub2, sub3;
	अचिन्हित दीर्घ दीर्घ high, low;

	sub0 = (x >> 32) * (अचिन्हित दीर्घ) (y >> 32);
	sub1 = (x & 0xffffffffLL) * (अचिन्हित दीर्घ) (y >> 32);
	sub2 = (x >> 32) * (अचिन्हित दीर्घ) (y & 0xffffffffLL);
	sub3 = (x & 0xffffffffLL) * (अचिन्हित दीर्घ) (y & 0xffffffffLL);
	low = sub3;
	high = 0LL;
	sub3 += (sub1 << 32);
	अगर (low > sub3)
		high++;
	low = sub3;
	sub3 += (sub2 << 32);
	अगर (low > sub3)
		high++;
	low = sub3;
	high += (sub1 >> 32) + (sub2 >> 32);
	high += sub0;
	*lowp = low;
	*highp = high;
पूर्ण

अटल अंतरभूत दीर्घ दीर्घ rshअगरt64(अचिन्हित दीर्घ दीर्घ mh,
		अचिन्हित दीर्घ दीर्घ ml, पूर्णांक n)
अणु
	अगर (n >= 64)
		वापस mh >> (n - 64);
	वापस (mh << (64 - n)) | (ml >> n);
पूर्ण

अटल दीर्घ दीर्घ denormal_muld(दीर्घ दीर्घ hx, दीर्घ दीर्घ hy)
अणु
	अचिन्हित दीर्घ दीर्घ ix, iy;
	अचिन्हित दीर्घ दीर्घ mh, ml, nh, nl;
	पूर्णांक exp, w;

	ix = hx & 0x7fffffffffffffffLL;
	iy = hy & 0x7fffffffffffffffLL;
	अगर (iy < 0x0010000000000000LL || ix == 0)
		वापस ((hx ^ hy) & 0x8000000000000000LL);

	exp = (iy & 0x7ff0000000000000LL) >> 52;
	ix &= 0x000fffffffffffffLL;
	iy = (iy & 0x000fffffffffffffLL) | 0x0010000000000000LL;
	mult64(ix, iy, &mh, &ml);
	nh = mh;
	nl = ml;
	w = -1;
	अगर (nh) अणु
		जबतक (nh) अणु nh >>= 1; w++;पूर्ण
		w += 64;
	पूर्ण अन्यथा
		जबतक (nl) अणु nl >>= 1; w++;पूर्ण

	/* FIXME: use guard bits */
	exp += w - 1022 - 52 * 2;
	अगर (exp > 0)
		ix = (rshअगरt64(mh, ml, w - 52) & 0x000fffffffffffffLL)
			| ((दीर्घ दीर्घ)exp << 52);
	अन्यथा अगर (exp + 51 >= 0)
		ix = rshअगरt64(mh, ml, w - 51 - exp) & 0x000fffffffffffffLL;
	अन्यथा
		ix = 0;

	ix |= (hx ^ hy) & 0x8000000000000000LL;
	वापस ix;
पूर्ण

/* ix - iy where iy: denormal and ix, iy >= 0 */
अटल पूर्णांक denormal_subf1(अचिन्हित पूर्णांक ix, अचिन्हित पूर्णांक iy)
अणु
	पूर्णांक frac;
	पूर्णांक exp;

	अगर (ix < 0x00800000)
		वापस ix - iy;

	exp = (ix & 0x7f800000) >> 23;
	अगर (exp - 1 > 31)
		वापस ix;
	iy >>= exp - 1;
	अगर (iy == 0)
		वापस ix;

	frac = (ix & 0x007fffff) | 0x00800000;
	frac -= iy;
	जबतक (frac < 0x00800000) अणु
		अगर (--exp == 0)
			वापस frac;
		frac <<= 1;
	पूर्ण

	वापस (exp << 23) | (frac & 0x007fffff);
पूर्ण

/* ix + iy where iy: denormal and ix, iy >= 0 */
अटल पूर्णांक denormal_addf1(अचिन्हित पूर्णांक ix, अचिन्हित पूर्णांक iy)
अणु
	पूर्णांक frac;
	पूर्णांक exp;

	अगर (ix < 0x00800000)
		वापस ix + iy;

	exp = (ix & 0x7f800000) >> 23;
	अगर (exp - 1 > 31)
		वापस ix;
	iy >>= exp - 1;
	अगर (iy == 0)
	  वापस ix;

	frac = (ix & 0x007fffff) | 0x00800000;
	frac += iy;
	अगर (frac >= 0x01000000) अणु
		frac >>= 1;
		++exp;
	पूर्ण

	वापस (exp << 23) | (frac & 0x007fffff);
पूर्ण

अटल पूर्णांक denormal_addf(पूर्णांक hx, पूर्णांक hy)
अणु
	अचिन्हित पूर्णांक ix, iy;
	पूर्णांक sign;

	अगर ((hx ^ hy) & 0x80000000) अणु
		sign = hx & 0x80000000;
		ix = hx & 0x7fffffff;
		iy = hy & 0x7fffffff;
		अगर (iy < 0x00800000) अणु
			ix = denormal_subf1(ix, iy);
			अगर ((पूर्णांक) ix < 0) अणु
				ix = -ix;
				sign ^= 0x80000000;
			पूर्ण
		पूर्ण अन्यथा अणु
			ix = denormal_subf1(iy, ix);
			sign ^= 0x80000000;
		पूर्ण
	पूर्ण अन्यथा अणु
		sign = hx & 0x80000000;
		ix = hx & 0x7fffffff;
		iy = hy & 0x7fffffff;
		अगर (iy < 0x00800000)
			ix = denormal_addf1(ix, iy);
		अन्यथा
			ix = denormal_addf1(iy, ix);
	पूर्ण

	वापस sign | ix;
पूर्ण

/* ix - iy where iy: denormal and ix, iy >= 0 */
अटल दीर्घ दीर्घ denormal_subd1(अचिन्हित दीर्घ दीर्घ ix, अचिन्हित दीर्घ दीर्घ iy)
अणु
	दीर्घ दीर्घ frac;
	पूर्णांक exp;

	अगर (ix < 0x0010000000000000LL)
		वापस ix - iy;

	exp = (ix & 0x7ff0000000000000LL) >> 52;
	अगर (exp - 1 > 63)
		वापस ix;
	iy >>= exp - 1;
	अगर (iy == 0)
		वापस ix;

	frac = (ix & 0x000fffffffffffffLL) | 0x0010000000000000LL;
	frac -= iy;
	जबतक (frac < 0x0010000000000000LL) अणु
		अगर (--exp == 0)
			वापस frac;
		frac <<= 1;
	पूर्ण

	वापस ((दीर्घ दीर्घ)exp << 52) | (frac & 0x000fffffffffffffLL);
पूर्ण

/* ix + iy where iy: denormal and ix, iy >= 0 */
अटल दीर्घ दीर्घ denormal_addd1(अचिन्हित दीर्घ दीर्घ ix, अचिन्हित दीर्घ दीर्घ iy)
अणु
	दीर्घ दीर्घ frac;
	दीर्घ दीर्घ exp;

	अगर (ix < 0x0010000000000000LL)
		वापस ix + iy;

	exp = (ix & 0x7ff0000000000000LL) >> 52;
	अगर (exp - 1 > 63)
		वापस ix;
	iy >>= exp - 1;
	अगर (iy == 0)
	  वापस ix;

	frac = (ix & 0x000fffffffffffffLL) | 0x0010000000000000LL;
	frac += iy;
	अगर (frac >= 0x0020000000000000LL) अणु
		frac >>= 1;
		++exp;
	पूर्ण

	वापस (exp << 52) | (frac & 0x000fffffffffffffLL);
पूर्ण

अटल दीर्घ दीर्घ denormal_addd(दीर्घ दीर्घ hx, दीर्घ दीर्घ hy)
अणु
	अचिन्हित दीर्घ दीर्घ ix, iy;
	दीर्घ दीर्घ sign;

	अगर ((hx ^ hy) & 0x8000000000000000LL) अणु
		sign = hx & 0x8000000000000000LL;
		ix = hx & 0x7fffffffffffffffLL;
		iy = hy & 0x7fffffffffffffffLL;
		अगर (iy < 0x0010000000000000LL) अणु
			ix = denormal_subd1(ix, iy);
			अगर ((पूर्णांक) ix < 0) अणु
				ix = -ix;
				sign ^= 0x8000000000000000LL;
			पूर्ण
		पूर्ण अन्यथा अणु
			ix = denormal_subd1(iy, ix);
			sign ^= 0x8000000000000000LL;
		पूर्ण
	पूर्ण अन्यथा अणु
		sign = hx & 0x8000000000000000LL;
		ix = hx & 0x7fffffffffffffffLL;
		iy = hy & 0x7fffffffffffffffLL;
		अगर (iy < 0x0010000000000000LL)
			ix = denormal_addd1(ix, iy);
		अन्यथा
			ix = denormal_addd1(iy, ix);
	पूर्ण

	वापस sign | ix;
पूर्ण

/**
 *	denormal_to_द्विगुन - Given denormalized भग्न number,
 *	                     store द्विगुन भग्न
 *
 *	@fpu: Poपूर्णांकer to sh_fpu_hard काष्ठाure
 *	@n: Index to FP रेजिस्टर
 */
अटल व्योम
denormal_to_द्विगुन (काष्ठा sh_fpu_hard_काष्ठा *fpu, पूर्णांक n)
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
		fpu->fp_regs[n+1] = dl;
	पूर्ण
पूर्ण

/**
 *	ieee_fpe_handler - Handle denormalized number exception
 *
 *	@regs: Poपूर्णांकer to रेजिस्टर काष्ठाure
 *
 *	Returns 1 when it's handled (should not cause exception).
 */
अटल पूर्णांक
ieee_fpe_handler (काष्ठा pt_regs *regs)
अणु
	अचिन्हित लघु insn = *(अचिन्हित लघु *) regs->pc;
	अचिन्हित लघु finsn;
	अचिन्हित दीर्घ nextpc;
	पूर्णांक nib[4] = अणु
		(insn >> 12) & 0xf,
		(insn >> 8) & 0xf,
		(insn >> 4) & 0xf,
		insn & 0xfपूर्ण;

	अगर (nib[0] == 0xb ||
	    (nib[0] == 0x4 && nib[2] == 0x0 && nib[3] == 0xb)) /* bsr & jsr */
		regs->pr = regs->pc + 4;
	अगर (nib[0] == 0xa || nib[0] == 0xb) अणु /* bra & bsr */
		nextpc = regs->pc + 4 + ((लघु) ((insn & 0xfff) << 4) >> 3);
		finsn = *(अचिन्हित लघु *) (regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x8 && nib[1] == 0xd) अणु /* bt/s */
		अगर (regs->sr & 1)
			nextpc = regs->pc + 4 + ((अक्षर) (insn & 0xff) << 1);
		अन्यथा
			nextpc = regs->pc + 4;
		finsn = *(अचिन्हित लघु *) (regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x8 && nib[1] == 0xf) अणु /* bf/s */
		अगर (regs->sr & 1)
			nextpc = regs->pc + 4;
		अन्यथा
			nextpc = regs->pc + 4 + ((अक्षर) (insn & 0xff) << 1);
		finsn = *(अचिन्हित लघु *) (regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x4 && nib[3] == 0xb &&
		 (nib[2] == 0x0 || nib[2] == 0x2)) अणु /* jmp & jsr */
		nextpc = regs->regs[nib[1]];
		finsn = *(अचिन्हित लघु *) (regs->pc + 2);
	पूर्ण अन्यथा अगर (nib[0] == 0x0 && nib[3] == 0x3 &&
		 (nib[2] == 0x0 || nib[2] == 0x2)) अणु /* braf & bsrf */
		nextpc = regs->pc + 4 + regs->regs[nib[1]];
		finsn = *(अचिन्हित लघु *) (regs->pc + 2);
	पूर्ण अन्यथा अगर (insn == 0x000b) अणु /* rts */
		nextpc = regs->pr;
		finsn = *(अचिन्हित लघु *) (regs->pc + 2);
	पूर्ण अन्यथा अणु
		nextpc = regs->pc + 2;
		finsn = insn;
	पूर्ण

#घोषणा FPSCR_FPU_ERROR (1 << 17)

	अगर ((finsn & 0xf1ff) == 0xf0ad) अणु /* fcnvsd */
		काष्ठा task_काष्ठा *tsk = current;

		अगर ((tsk->thपढ़ो.xstate->hardfpu.fpscr & FPSCR_FPU_ERROR)) अणु
			/* FPU error */
			denormal_to_द्विगुन (&tsk->thपढ़ो.xstate->hardfpu,
					    (finsn >> 8) & 0xf);
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण अन्यथा अगर ((finsn & 0xf00f) == 0xf002) अणु /* fmul */
		काष्ठा task_काष्ठा *tsk = current;
		पूर्णांक fpscr;
		पूर्णांक n, m, prec;
		अचिन्हित पूर्णांक hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thपढ़ो.xstate->hardfpu.fp_regs[n];
		hy = tsk->thपढ़ो.xstate->hardfpu.fp_regs[m];
		fpscr = tsk->thपढ़ो.xstate->hardfpu.fpscr;
		prec = fpscr & (1 << 19);

		अगर ((fpscr & FPSCR_FPU_ERROR)
		     && (prec && ((hx & 0x7fffffff) < 0x00100000
				   || (hy & 0x7fffffff) < 0x00100000))) अणु
			दीर्घ दीर्घ llx, lly;

			/* FPU error because of denormal */
			llx = ((दीर्घ दीर्घ) hx << 32)
			       | tsk->thपढ़ो.xstate->hardfpu.fp_regs[n+1];
			lly = ((दीर्घ दीर्घ) hy << 32)
			       | tsk->thपढ़ो.xstate->hardfpu.fp_regs[m+1];
			अगर ((hx & 0x7fffffff) >= 0x00100000)
				llx = denormal_muld(lly, llx);
			अन्यथा
				llx = denormal_muld(llx, lly);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = llx >> 32;
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n+1] = llx & 0xffffffff;
		पूर्ण अन्यथा अगर ((fpscr & FPSCR_FPU_ERROR)
		     && (!prec && ((hx & 0x7fffffff) < 0x00800000
				   || (hy & 0x7fffffff) < 0x00800000))) अणु
			/* FPU error because of denormal */
			अगर ((hx & 0x7fffffff) >= 0x00800000)
				hx = denormal_mulf(hy, hx);
			अन्यथा
				hx = denormal_mulf(hx, hy);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = hx;
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण अन्यथा अगर ((finsn & 0xf00e) == 0xf000) अणु /* fadd, fsub */
		काष्ठा task_काष्ठा *tsk = current;
		पूर्णांक fpscr;
		पूर्णांक n, m, prec;
		अचिन्हित पूर्णांक hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thपढ़ो.xstate->hardfpu.fp_regs[n];
		hy = tsk->thपढ़ो.xstate->hardfpu.fp_regs[m];
		fpscr = tsk->thपढ़ो.xstate->hardfpu.fpscr;
		prec = fpscr & (1 << 19);

		अगर ((fpscr & FPSCR_FPU_ERROR)
		     && (prec && ((hx & 0x7fffffff) < 0x00100000
				   || (hy & 0x7fffffff) < 0x00100000))) अणु
			दीर्घ दीर्घ llx, lly;

			/* FPU error because of denormal */
			llx = ((दीर्घ दीर्घ) hx << 32)
			       | tsk->thपढ़ो.xstate->hardfpu.fp_regs[n+1];
			lly = ((दीर्घ दीर्घ) hy << 32)
			       | tsk->thपढ़ो.xstate->hardfpu.fp_regs[m+1];
			अगर ((finsn & 0xf00f) == 0xf000)
				llx = denormal_addd(llx, lly);
			अन्यथा
				llx = denormal_addd(llx, lly ^ (1LL << 63));
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = llx >> 32;
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n+1] = llx & 0xffffffff;
		पूर्ण अन्यथा अगर ((fpscr & FPSCR_FPU_ERROR)
		     && (!prec && ((hx & 0x7fffffff) < 0x00800000
				   || (hy & 0x7fffffff) < 0x00800000))) अणु
			/* FPU error because of denormal */
			अगर ((finsn & 0xf00f) == 0xf000)
				hx = denormal_addf(hx, hy);
			अन्यथा
				hx = denormal_addf(hx, hy ^ 0x80000000);
			tsk->thपढ़ो.xstate->hardfpu.fp_regs[n] = hx;
		पूर्ण अन्यथा
			वापस 0;

		regs->pc = nextpc;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

BUILD_TRAP_HANDLER(fpu_error)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	TRAP_HANDLER_DECL;

	__unlazy_fpu(tsk, regs);
	अगर (ieee_fpe_handler(regs)) अणु
		tsk->thपढ़ो.xstate->hardfpu.fpscr &=
			~(FPSCR_CAUSE_MASK | FPSCR_FLAG_MASK);
		grab_fpu(regs);
		restore_fpu(tsk);
		task_thपढ़ो_info(tsk)->status |= TS_USEDFPU;
		वापस;
	पूर्ण

	क्रमce_sig(संक_भ_त्रुटि);
पूर्ण
