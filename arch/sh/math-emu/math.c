<शैली गुरु>
/*
 * arch/sh/math-emu/math.c
 *
 * Copyright (C) 2006 Takashi YOSHII <takasi-y@ops.dti.ne.jp>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/perf_event.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>

#समावेश "sfp-util.h"
#समावेश <math-emu/soft-fp.h>
#समावेश <math-emu/single.h>
#समावेश <math-emu/द्विगुन.h>

#घोषणा	FPUL		(fregs->fpul)
#घोषणा FPSCR		(fregs->fpscr)
#घोषणा FPSCR_RM	(FPSCR&3)
#घोषणा FPSCR_DN	((FPSCR>>18)&1)
#घोषणा FPSCR_PR	((FPSCR>>19)&1)
#घोषणा FPSCR_SZ	((FPSCR>>20)&1)
#घोषणा FPSCR_FR	((FPSCR>>21)&1)
#घोषणा FPSCR_MASK	0x003fffffUL

#घोषणा BANK(n)	(n^(FPSCR_FR?16:0))
#घोषणा FR	((अचिन्हित दीर्घ*)(fregs->fp_regs))
#घोषणा FR0	(FR[BANK(0)])
#घोषणा FRn	(FR[BANK(n)])
#घोषणा FRm	(FR[BANK(m)])
#घोषणा DR	((अचिन्हित दीर्घ दीर्घ*)(fregs->fp_regs))
#घोषणा DRn	(DR[BANK(n)/2])
#घोषणा DRm	(DR[BANK(m)/2])

#घोषणा XREG(n)	(n^16)
#घोषणा XFn	(FR[BANK(XREG(n))])
#घोषणा XFm	(FR[BANK(XREG(m))])
#घोषणा XDn	(DR[BANK(XREG(n))/2])
#घोषणा XDm	(DR[BANK(XREG(m))/2])

#घोषणा R0	(regs->regs[0])
#घोषणा Rn	(regs->regs[n])
#घोषणा Rm	(regs->regs[m])

#घोषणा WRITE(d,a)	(अणुअगर(put_user(d, (typeof (d)*)a)) वापस -EFAULT;पूर्ण)
#घोषणा READ(d,a)	(अणुअगर(get_user(d, (typeof (d)*)a)) वापस -EFAULT;पूर्ण)

#घोषणा PACK_S(r,f)	FP_PACK_SP(&r,f)
#घोषणा UNPACK_S(f,r)	FP_UNPACK_SP(f,&r)
#घोषणा PACK_D(r,f) \
	अणुu32 t[2]; FP_PACK_DP(t,f); ((u32*)&r)[0]=t[1]; ((u32*)&r)[1]=t[0];पूर्ण
#घोषणा UNPACK_D(f,r) \
	अणुu32 t[2]; t[0]=((u32*)&r)[1]; t[1]=((u32*)&r)[0]; FP_UNPACK_DP(f,t);पूर्ण

// 2 args inकाष्ठाions.
#घोषणा BOTH_PRmn(op,x) \
	FP_DECL_EX; अगर(FPSCR_PR) op(D,x,DRm,DRn); अन्यथा op(S,x,FRm,FRn);

#घोषणा CMP_X(SZ,R,M,N) करोअणु \
	FP_DECL_##SZ(Fm); FP_DECL_##SZ(Fn); \
	UNPACK_##SZ(Fm, M); UNPACK_##SZ(Fn, N); \
	FP_CMP_##SZ(R, Fn, Fm, 2); पूर्णजबतक(0)
#घोषणा EQ_X(SZ,R,M,N) करोअणु \
	FP_DECL_##SZ(Fm); FP_DECL_##SZ(Fn); \
	UNPACK_##SZ(Fm, M); UNPACK_##SZ(Fn, N); \
	FP_CMP_EQ_##SZ(R, Fn, Fm); पूर्णजबतक(0)
#घोषणा CMP(OP) (अणु पूर्णांक r; BOTH_PRmn(OP##_X,r); r; पूर्ण)

अटल पूर्णांक
fcmp_gt(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	अगर (CMP(CMP) > 0)
		regs->sr |= 1;
	अन्यथा
		regs->sr &= ~1;

	वापस 0;
पूर्ण

अटल पूर्णांक
fcmp_eq(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	अगर (CMP(CMP /*EQ*/) == 0)
		regs->sr |= 1;
	अन्यथा
		regs->sr &= ~1;
	वापस 0;
पूर्ण

#घोषणा ARITH_X(SZ,OP,M,N) करोअणु \
	FP_DECL_##SZ(Fm); FP_DECL_##SZ(Fn); FP_DECL_##SZ(Fr); \
	UNPACK_##SZ(Fm, M); UNPACK_##SZ(Fn, N); \
	FP_##OP##_##SZ(Fr, Fn, Fm); \
	PACK_##SZ(N, Fr); पूर्णजबतक(0)

अटल पूर्णांक
fadd(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	BOTH_PRmn(ARITH_X, ADD);
	वापस 0;
पूर्ण

अटल पूर्णांक
fsub(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	BOTH_PRmn(ARITH_X, SUB);
	वापस 0;
पूर्ण

अटल पूर्णांक
fmul(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	BOTH_PRmn(ARITH_X, MUL);
	वापस 0;
पूर्ण

अटल पूर्णांक
fभाग(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	BOTH_PRmn(ARITH_X, DIV);
	वापस 0;
पूर्ण

अटल पूर्णांक
fmac(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	FP_DECL_EX;
	FP_DECL_S(Fr);
	FP_DECL_S(Ft);
	FP_DECL_S(F0);
	FP_DECL_S(Fm);
	FP_DECL_S(Fn);
	UNPACK_S(F0, FR0);
	UNPACK_S(Fm, FRm);
	UNPACK_S(Fn, FRn);
	FP_MUL_S(Ft, Fm, F0);
	FP_ADD_S(Fr, Fn, Ft);
	PACK_S(FRn, Fr);
	वापस 0;
पूर्ण

// to process fmov's extension (odd n क्रम DR access XD).
#घोषणा FMOV_EXT(x) अगर(x&1) x+=16-1

अटल पूर्णांक
fmov_idx_reg(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(n);
		READ(FRn, Rm + R0 + 4);
		n++;
		READ(FRn, Rm + R0);
	पूर्ण अन्यथा अणु
		READ(FRn, Rm + R0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fmov_mem_reg(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(n);
		READ(FRn, Rm + 4);
		n++;
		READ(FRn, Rm);
	पूर्ण अन्यथा अणु
		READ(FRn, Rm);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fmov_inc_reg(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(n);
		READ(FRn, Rm + 4);
		n++;
		READ(FRn, Rm);
		Rm += 8;
	पूर्ण अन्यथा अणु
		READ(FRn, Rm);
		Rm += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fmov_reg_idx(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(m);
		WRITE(FRm, Rn + R0 + 4);
		m++;
		WRITE(FRm, Rn + R0);
	पूर्ण अन्यथा अणु
		WRITE(FRm, Rn + R0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fmov_reg_mem(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(m);
		WRITE(FRm, Rn + 4);
		m++;
		WRITE(FRm, Rn);
	पूर्ण अन्यथा अणु
		WRITE(FRm, Rn);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fmov_reg_dec(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(m);
		Rn -= 8;
		WRITE(FRm, Rn + 4);
		m++;
		WRITE(FRm, Rn);
	पूर्ण अन्यथा अणु
		Rn -= 4;
		WRITE(FRm, Rn);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fmov_reg_reg(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m,
	     पूर्णांक n)
अणु
	अगर (FPSCR_SZ) अणु
		FMOV_EXT(m);
		FMOV_EXT(n);
		DRn = DRm;
	पूर्ण अन्यथा अणु
		FRn = FRm;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fnop_mn(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक m, पूर्णांक n)
अणु
	वापस -EINVAL;
पूर्ण

// 1 arg inकाष्ठाions.
#घोषणा NOTYETn(i) अटल पूर्णांक i(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n) \
	अणु prपूर्णांकk( #i " not yet done.\n"); वापस 0; पूर्ण

NOTYETn(ftrv)
NOTYETn(fवर्ग_मूल)
NOTYETn(fipr)
NOTYETn(fsca)
NOTYETn(fsrra)

#घोषणा EMU_FLOAT_X(SZ,N) करो अणु \
	FP_DECL_##SZ(Fn); \
	FP_FROM_INT_##SZ(Fn, FPUL, 32, पूर्णांक); \
	PACK_##SZ(N, Fn); पूर्णजबतक(0)
अटल पूर्णांक fभग्न(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FP_DECL_EX;

	अगर (FPSCR_PR)
		EMU_FLOAT_X(D, DRn);
	अन्यथा
		EMU_FLOAT_X(S, FRn);

	वापस 0;
पूर्ण

#घोषणा EMU_FTRC_X(SZ,N) करो अणु \
	FP_DECL_##SZ(Fn); \
	UNPACK_##SZ(Fn, N); \
	FP_TO_INT_##SZ(FPUL, Fn, 32, 1); पूर्णजबतक(0)
अटल पूर्णांक ftrc(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FP_DECL_EX;

	अगर (FPSCR_PR)
		EMU_FTRC_X(D, DRn);
	अन्यथा
		EMU_FTRC_X(S, FRn);

	वापस 0;
पूर्ण

अटल पूर्णांक fcnvsd(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FP_DECL_EX;
	FP_DECL_S(Fn);
	FP_DECL_D(Fr);
	UNPACK_S(Fn, FPUL);
	FP_CONV(D, S, 2, 1, Fr, Fn);
	PACK_D(DRn, Fr);
	वापस 0;
पूर्ण

अटल पूर्णांक fcnvds(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FP_DECL_EX;
	FP_DECL_D(Fn);
	FP_DECL_S(Fr);
	UNPACK_D(Fn, DRn);
	FP_CONV(S, D, 1, 2, Fr, Fn);
	PACK_S(FPUL, Fr);
	वापस 0;
पूर्ण

अटल पूर्णांक fxchg(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक flag)
अणु
	FPSCR ^= flag;
	वापस 0;
पूर्ण

अटल पूर्णांक fsts(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FRn = FPUL;
	वापस 0;
पूर्ण

अटल पूर्णांक flds(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FPUL = FRn;
	वापस 0;
पूर्ण

अटल पूर्णांक fneg(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FRn ^= (1 << (_FP_W_TYPE_SIZE - 1));
	वापस 0;
पूर्ण

अटल पूर्णांक भ_असल(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FRn &= ~(1 << (_FP_W_TYPE_SIZE - 1));
	वापस 0;
पूर्ण

अटल पूर्णांक fld0(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FRn = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक fld1(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	FRn = (_FP_EXPBIAS_S << (_FP_FRACBITS_S - 1));
	वापस 0;
पूर्ण

अटल पूर्णांक fnop_n(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक n)
अणु
	वापस -EINVAL;
पूर्ण

/// Inकाष्ठाion decoders.

अटल पूर्णांक id_fxfd(काष्ठा sh_fpu_soft_काष्ठा *, पूर्णांक);
अटल पूर्णांक id_fnxd(काष्ठा sh_fpu_soft_काष्ठा *, काष्ठा pt_regs *, पूर्णांक, पूर्णांक);

अटल पूर्णांक (*fnxd[])(काष्ठा sh_fpu_soft_काष्ठा *, पूर्णांक) = अणु
	fsts, flds, fभग्न, ftrc, fneg, भ_असल, fवर्ग_मूल, fsrra,
	fld0, fld1, fcnvsd, fcnvds, fnop_n, fnop_n, fipr, id_fxfd
पूर्ण;

अटल पूर्णांक (*fnmx[])(काष्ठा sh_fpu_soft_काष्ठा *, काष्ठा pt_regs *, पूर्णांक, पूर्णांक) = अणु
	fadd, fsub, fmul, fभाग, fcmp_eq, fcmp_gt, fmov_idx_reg, fmov_reg_idx,
	fmov_mem_reg, fmov_inc_reg, fmov_reg_mem, fmov_reg_dec,
	fmov_reg_reg, id_fnxd, fmac, fnop_mnपूर्ण;

अटल पूर्णांक id_fxfd(काष्ठा sh_fpu_soft_काष्ठा *fregs, पूर्णांक x)
अणु
	स्थिर पूर्णांक flag[] = अणु FPSCR_SZ, FPSCR_PR, FPSCR_FR, 0 पूर्ण;
	चयन (x & 3) अणु
	हाल 3:
		fxchg(fregs, flag[x >> 2]);
		अवरोध;
	हाल 1:
		ftrv(fregs, x - 1);
		अवरोध;
	शेष:
		fsca(fregs, x);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
id_fnxd(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, पूर्णांक x, पूर्णांक n)
अणु
	वापस (fnxd[x])(fregs, n);
पूर्ण

अटल पूर्णांक
id_fnmx(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, u16 code)
अणु
	पूर्णांक n = (code >> 8) & 0xf, m = (code >> 4) & 0xf, x = code & 0xf;
	वापस (fnmx[x])(fregs, regs, m, n);
पूर्ण

अटल पूर्णांक
id_sys(काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs, u16 code)
अणु
	पूर्णांक n = ((code >> 8) & 0xf);
	अचिन्हित दीर्घ *reg = (code & 0x0010) ? &FPUL : &FPSCR;

	चयन (code & 0xf0ff) अणु
	हाल 0x005a:
	हाल 0x006a:
		Rn = *reg;
		अवरोध;
	हाल 0x405a:
	हाल 0x406a:
		*reg = Rn;
		अवरोध;
	हाल 0x4052:
	हाल 0x4062:
		Rn -= 4;
		WRITE(*reg, Rn);
		अवरोध;
	हाल 0x4056:
	हाल 0x4066:
		READ(*reg, Rn);
		Rn += 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fpu_emulate(u16 code, काष्ठा sh_fpu_soft_काष्ठा *fregs, काष्ठा pt_regs *regs)
अणु
	अगर ((code & 0xf000) == 0xf000)
		वापस id_fnmx(fregs, regs, code);
	अन्यथा
		वापस id_sys(fregs, regs, code);
पूर्ण

/**
 *	denormal_to_द्विगुन - Given denormalized भग्न number,
 *	                     store द्विगुन भग्न
 *
 *	@fpu: Poपूर्णांकer to sh_fpu_soft काष्ठाure
 *	@n: Index to FP रेजिस्टर
 */
अटल व्योम denormal_to_द्विगुन(काष्ठा sh_fpu_soft_काष्ठा *fpu, पूर्णांक n)
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
अटल पूर्णांक ieee_fpe_handler(काष्ठा pt_regs *regs)
अणु
	अचिन्हित लघु insn = *(अचिन्हित लघु *)regs->pc;
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

	अगर ((finsn & 0xf1ff) == 0xf0ad) अणु /* fcnvsd */
		काष्ठा task_काष्ठा *tsk = current;

		अगर ((tsk->thपढ़ो.xstate->softfpu.fpscr & (1 << 17))) अणु
			/* FPU error */
			denormal_to_द्विगुन (&tsk->thपढ़ो.xstate->softfpu,
					    (finsn >> 8) & 0xf);
			tsk->thपढ़ो.xstate->softfpu.fpscr &=
				~(FPSCR_CAUSE_MASK | FPSCR_FLAG_MASK);
			task_thपढ़ो_info(tsk)->status |= TS_USEDFPU;
		पूर्ण अन्यथा अणु
			क्रमce_sig_fault(संक_भ_त्रुटि, FPE_FLTINV,
					(व्योम __user *)regs->pc);
		पूर्ण

		regs->pc = nextpc;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fpu_init - Initialize FPU रेजिस्टरs
 * @fpu: Poपूर्णांकer to software emulated FPU रेजिस्टरs.
 */
अटल व्योम fpu_init(काष्ठा sh_fpu_soft_काष्ठा *fpu)
अणु
	पूर्णांक i;

	fpu->fpscr = FPSCR_INIT;
	fpu->fpul = 0;

	क्रम (i = 0; i < 16; i++) अणु
		fpu->fp_regs[i] = 0;
		fpu->xfp_regs[i]= 0;
	पूर्ण
पूर्ण

/**
 * करो_fpu_inst - Handle reserved inकाष्ठाions क्रम FPU emulation
 * @inst: inकाष्ठाion code.
 * @regs: रेजिस्टरs on stack.
 */
पूर्णांक करो_fpu_inst(अचिन्हित लघु inst, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा sh_fpu_soft_काष्ठा *fpu = &(tsk->thपढ़ो.xstate->softfpu);

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

	अगर (!(task_thपढ़ो_info(tsk)->status & TS_USEDFPU)) अणु
		/* initialize once. */
		fpu_init(fpu);
		task_thपढ़ो_info(tsk)->status |= TS_USEDFPU;
	पूर्ण

	वापस fpu_emulate(inst, fpu, regs);
पूर्ण
