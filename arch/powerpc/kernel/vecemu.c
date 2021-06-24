<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Routines to emulate some Altivec/VMX inकाष्ठाions, specअगरically
 * those that can trap when given denormalized opeअक्रमs in Java mode.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/inst.h>

/* Functions in vector.S */
बाह्य व्योम vaddfp(vector128 *dst, vector128 *a, vector128 *b);
बाह्य व्योम vsubfp(vector128 *dst, vector128 *a, vector128 *b);
बाह्य व्योम vmaddfp(vector128 *dst, vector128 *a, vector128 *b, vector128 *c);
बाह्य व्योम vnmsubfp(vector128 *dst, vector128 *a, vector128 *b, vector128 *c);
बाह्य व्योम vrefp(vector128 *dst, vector128 *src);
बाह्य व्योम vrवर्ग_मूलefp(vector128 *dst, vector128 *src);
बाह्य व्योम vexptep(vector128 *dst, vector128 *src);

अटल अचिन्हित पूर्णांक exp2s[8] = अणु
	0x800000,
	0x8b95c2,
	0x9837f0,
	0xa5fed7,
	0xb504f3,
	0xc5672a,
	0xd744fd,
	0xeac0c7
पूर्ण;

/*
 * Computes an estimate of 2^x.  The `s' argument is the 32-bit
 * single-precision भग्नing-poपूर्णांक representation of x.
 */
अटल अचिन्हित पूर्णांक eexp2(अचिन्हित पूर्णांक s)
अणु
	पूर्णांक exp, pwr;
	अचिन्हित पूर्णांक mant, frac;

	/* extract exponent field from input */
	exp = ((s >> 23) & 0xff) - 127;
	अगर (exp > 7) अणु
		/* check क्रम NaN input */
		अगर (exp == 128 && (s & 0x7fffff) != 0)
			वापस s | 0x400000;	/* वापस QNaN */
		/* 2^-big = 0, 2^+big = +Inf */
		वापस (s & 0x80000000)? 0: 0x7f800000;	/* 0 or +Inf */
	पूर्ण
	अगर (exp < -23)
		वापस 0x3f800000;	/* 1.0 */

	/* convert to fixed poपूर्णांक पूर्णांकeger in 9.23 representation */
	pwr = (s & 0x7fffff) | 0x800000;
	अगर (exp > 0)
		pwr <<= exp;
	अन्यथा
		pwr >>= -exp;
	अगर (s & 0x80000000)
		pwr = -pwr;

	/* extract पूर्णांकeger part, which becomes exponent part of result */
	exp = (pwr >> 23) + 126;
	अगर (exp >= 254)
		वापस 0x7f800000;
	अगर (exp < -23)
		वापस 0;

	/* table lookup on top 3 bits of fraction to get mantissa */
	mant = exp2s[(pwr >> 20) & 7];

	/* linear पूर्णांकerpolation using reमुख्यing 20 bits of fraction */
	यंत्र("mulhwu %0,%1,%2" : "=r" (frac)
	    : "r" (pwr << 12), "r" (0x172b83ff));
	यंत्र("mulhwu %0,%1,%2" : "=r" (frac) : "r" (frac), "r" (mant));
	mant += frac;

	अगर (exp >= 0)
		वापस mant + (exp << 23);

	/* denormalized result */
	exp = -exp;
	mant += 1 << (exp - 1);
	वापस mant >> exp;
पूर्ण

/*
 * Computes an estimate of log_2(x).  The `s' argument is the 32-bit
 * single-precision भग्नing-poपूर्णांक representation of x.
 */
अटल अचिन्हित पूर्णांक elog2(अचिन्हित पूर्णांक s)
अणु
	पूर्णांक exp, mant, lz, frac;

	exp = s & 0x7f800000;
	mant = s & 0x7fffff;
	अगर (exp == 0x7f800000) अणु	/* Inf or NaN */
		अगर (mant != 0)
			s |= 0x400000;	/* turn NaN पूर्णांकo QNaN */
		वापस s;
	पूर्ण
	अगर ((exp | mant) == 0)		/* +0 or -0 */
		वापस 0xff800000;	/* वापस -Inf */

	अगर (exp == 0) अणु
		/* denormalized */
		यंत्र("cntlzw %0,%1" : "=r" (lz) : "r" (mant));
		mant <<= lz - 8;
		exp = (-118 - lz) << 23;
	पूर्ण अन्यथा अणु
		mant |= 0x800000;
		exp -= 127 << 23;
	पूर्ण

	अगर (mant >= 0xb504f3) अणु				/* 2^0.5 * 2^23 */
		exp |= 0x400000;			/* 0.5 * 2^23 */
		यंत्र("mulhwu %0,%1,%2" : "=r" (mant)
		    : "r" (mant), "r" (0xb504f334));	/* 2^-0.5 * 2^32 */
	पूर्ण
	अगर (mant >= 0x9837f0) अणु				/* 2^0.25 * 2^23 */
		exp |= 0x200000;			/* 0.25 * 2^23 */
		यंत्र("mulhwu %0,%1,%2" : "=r" (mant)
		    : "r" (mant), "r" (0xd744fccb));	/* 2^-0.25 * 2^32 */
	पूर्ण
	अगर (mant >= 0x8b95c2) अणु				/* 2^0.125 * 2^23 */
		exp |= 0x100000;			/* 0.125 * 2^23 */
		यंत्र("mulhwu %0,%1,%2" : "=r" (mant)
		    : "r" (mant), "r" (0xeac0c6e8));	/* 2^-0.125 * 2^32 */
	पूर्ण
	अगर (mant > 0x800000) अणु				/* 1.0 * 2^23 */
		/* calculate (mant - 1) * 1.381097463 */
		/* 1.381097463 == 0.125 / (2^0.125 - 1) */
		यंत्र("mulhwu %0,%1,%2" : "=r" (frac)
		    : "r" ((mant - 0x800000) << 1), "r" (0xb0c7cd3a));
		exp += frac;
	पूर्ण
	s = exp & 0x80000000;
	अगर (exp != 0) अणु
		अगर (s)
			exp = -exp;
		यंत्र("cntlzw %0,%1" : "=r" (lz) : "r" (exp));
		lz = 8 - lz;
		अगर (lz > 0)
			exp >>= lz;
		अन्यथा अगर (lz < 0)
			exp <<= -lz;
		s += ((lz + 126) << 23) + exp;
	पूर्ण
	वापस s;
पूर्ण

#घोषणा VSCR_SAT	1

अटल पूर्णांक ctsxs(अचिन्हित पूर्णांक x, पूर्णांक scale, अचिन्हित पूर्णांक *vscrp)
अणु
	पूर्णांक exp, mant;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	अगर (exp == 255 && mant != 0)
		वापस 0;		/* NaN -> 0 */
	exp = exp - 127 + scale;
	अगर (exp < 0)
		वापस 0;		/* round towards zero */
	अगर (exp >= 31) अणु
		/* saturate, unless the result would be -2^31 */
		अगर (x + (scale << 23) != 0xcf000000)
			*vscrp |= VSCR_SAT;
		वापस (x & 0x80000000)? 0x80000000: 0x7fffffff;
	पूर्ण
	mant |= 0x800000;
	mant = (mant << 7) >> (30 - exp);
	वापस (x & 0x80000000)? -mant: mant;
पूर्ण

अटल अचिन्हित पूर्णांक ctuxs(अचिन्हित पूर्णांक x, पूर्णांक scale, अचिन्हित पूर्णांक *vscrp)
अणु
	पूर्णांक exp;
	अचिन्हित पूर्णांक mant;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	अगर (exp == 255 && mant != 0)
		वापस 0;		/* NaN -> 0 */
	exp = exp - 127 + scale;
	अगर (exp < 0)
		वापस 0;		/* round towards zero */
	अगर (x & 0x80000000) अणु
		/* negative => saturate to 0 */
		*vscrp |= VSCR_SAT;
		वापस 0;
	पूर्ण
	अगर (exp >= 32) अणु
		/* saturate */
		*vscrp |= VSCR_SAT;
		वापस 0xffffffff;
	पूर्ण
	mant |= 0x800000;
	mant = (mant << 8) >> (31 - exp);
	वापस mant;
पूर्ण

/* Round to भग्नing पूर्णांकeger, towards 0 */
अटल अचिन्हित पूर्णांक rfiz(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक exp;

	exp = ((x >> 23) & 0xff) - 127;
	अगर (exp == 128 && (x & 0x7fffff) != 0)
		वापस x | 0x400000;	/* NaN -> make it a QNaN */
	अगर (exp >= 23)
		वापस x;		/* it's an पूर्णांकeger alपढ़ोy (or Inf) */
	अगर (exp < 0)
		वापस x & 0x80000000;	/* |x| < 1.0 rounds to 0 */
	वापस x & ~(0x7fffff >> exp);
पूर्ण

/* Round to भग्नing पूर्णांकeger, towards +/- Inf */
अटल अचिन्हित पूर्णांक rfii(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक exp, mask;

	exp = ((x >> 23) & 0xff) - 127;
	अगर (exp == 128 && (x & 0x7fffff) != 0)
		वापस x | 0x400000;	/* NaN -> make it a QNaN */
	अगर (exp >= 23)
		वापस x;		/* it's an पूर्णांकeger alपढ़ोy (or Inf) */
	अगर ((x & 0x7fffffff) == 0)
		वापस x;		/* +/-0 -> +/-0 */
	अगर (exp < 0)
		/* 0 < |x| < 1.0 rounds to +/- 1.0 */
		वापस (x & 0x80000000) | 0x3f800000;
	mask = 0x7fffff >> exp;
	/* mantissa overflows पूर्णांकo exponent - that's OK,
	   it can't overflow पूर्णांकo the sign bit */
	वापस (x + mask) & ~mask;
पूर्ण

/* Round to भग्नing पूर्णांकeger, to nearest */
अटल अचिन्हित पूर्णांक rfin(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक exp, half;

	exp = ((x >> 23) & 0xff) - 127;
	अगर (exp == 128 && (x & 0x7fffff) != 0)
		वापस x | 0x400000;	/* NaN -> make it a QNaN */
	अगर (exp >= 23)
		वापस x;		/* it's an पूर्णांकeger alपढ़ोy (or Inf) */
	अगर (exp < -1)
		वापस x & 0x80000000;	/* |x| < 0.5 -> +/-0 */
	अगर (exp == -1)
		/* 0.5 <= |x| < 1.0 rounds to +/- 1.0 */
		वापस (x & 0x80000000) | 0x3f800000;
	half = 0x400000 >> exp;
	/* add 0.5 to the magnitude and chop off the fraction bits */
	वापस (x + half) & ~(0x7fffff >> exp);
पूर्ण

पूर्णांक emulate_altivec(काष्ठा pt_regs *regs)
अणु
	काष्ठा ppc_inst instr;
	अचिन्हित पूर्णांक i, word;
	अचिन्हित पूर्णांक va, vb, vc, vd;
	vector128 *vrs;

	अगर (get_user_instr(instr, (व्योम __user *)regs->nip))
		वापस -EFAULT;

	word = ppc_inst_val(instr);
	अगर (ppc_inst_primary_opcode(instr) != 4)
		वापस -EINVAL;		/* not an altivec inकाष्ठाion */
	vd = (word >> 21) & 0x1f;
	va = (word >> 16) & 0x1f;
	vb = (word >> 11) & 0x1f;
	vc = (word >> 6) & 0x1f;

	vrs = current->thपढ़ो.vr_state.vr;
	चयन (word & 0x3f) अणु
	हाल 10:
		चयन (vc) अणु
		हाल 0:	/* vaddfp */
			vaddfp(&vrs[vd], &vrs[va], &vrs[vb]);
			अवरोध;
		हाल 1:	/* vsubfp */
			vsubfp(&vrs[vd], &vrs[va], &vrs[vb]);
			अवरोध;
		हाल 4:	/* vrefp */
			vrefp(&vrs[vd], &vrs[vb]);
			अवरोध;
		हाल 5:	/* vrवर्ग_मूलefp */
			vrवर्ग_मूलefp(&vrs[vd], &vrs[vb]);
			अवरोध;
		हाल 6:	/* vexptefp */
			क्रम (i = 0; i < 4; ++i)
				vrs[vd].u[i] = eexp2(vrs[vb].u[i]);
			अवरोध;
		हाल 7:	/* vlogefp */
			क्रम (i = 0; i < 4; ++i)
				vrs[vd].u[i] = elog2(vrs[vb].u[i]);
			अवरोध;
		हाल 8:		/* vrfin */
			क्रम (i = 0; i < 4; ++i)
				vrs[vd].u[i] = rfin(vrs[vb].u[i]);
			अवरोध;
		हाल 9:		/* vrfiz */
			क्रम (i = 0; i < 4; ++i)
				vrs[vd].u[i] = rfiz(vrs[vb].u[i]);
			अवरोध;
		हाल 10:	/* vrfip */
			क्रम (i = 0; i < 4; ++i) अणु
				u32 x = vrs[vb].u[i];
				x = (x & 0x80000000)? rfiz(x): rfii(x);
				vrs[vd].u[i] = x;
			पूर्ण
			अवरोध;
		हाल 11:	/* vrfim */
			क्रम (i = 0; i < 4; ++i) अणु
				u32 x = vrs[vb].u[i];
				x = (x & 0x80000000)? rfii(x): rfiz(x);
				vrs[vd].u[i] = x;
			पूर्ण
			अवरोध;
		हाल 14:	/* vctuxs */
			क्रम (i = 0; i < 4; ++i)
				vrs[vd].u[i] = ctuxs(vrs[vb].u[i], va,
					&current->thपढ़ो.vr_state.vscr.u[3]);
			अवरोध;
		हाल 15:	/* vctsxs */
			क्रम (i = 0; i < 4; ++i)
				vrs[vd].u[i] = ctsxs(vrs[vb].u[i], va,
					&current->thपढ़ो.vr_state.vscr.u[3]);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 46:	/* vmaddfp */
		vmaddfp(&vrs[vd], &vrs[va], &vrs[vb], &vrs[vc]);
		अवरोध;
	हाल 47:	/* vnmsubfp */
		vnmsubfp(&vrs[vd], &vrs[va], &vrs[vb], &vrs[vc]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
