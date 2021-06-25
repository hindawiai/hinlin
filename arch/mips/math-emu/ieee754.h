<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 *
 *  Nov 7, 2000
 *  Modअगरication to allow पूर्णांकegration with Linux kernel
 *
 *  Kevin D. Kissell, kevink@mips.com and Carsten Langgard, carstenl@mips.com
 *  Copyright (C) 2000 MIPS Technologies, Inc. All rights reserved.
 */
#अगर_अघोषित __ARCH_MIPS_MATH_EMU_IEEE754_H
#घोषणा __ARCH_MIPS_MATH_EMU_IEEE754_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/bitfield.h>

जोड़ ieee754dp अणु
	काष्ठा अणु
		__BITFIELD_FIELD(अचिन्हित पूर्णांक sign:1,
		__BITFIELD_FIELD(अचिन्हित पूर्णांक bexp:11,
		__BITFIELD_FIELD(u64 mant:52,
		;)))
	पूर्ण;
	u64 bits;
पूर्ण;

जोड़ ieee754sp अणु
	काष्ठा अणु
		__BITFIELD_FIELD(अचिन्हित sign:1,
		__BITFIELD_FIELD(अचिन्हित bexp:8,
		__BITFIELD_FIELD(अचिन्हित mant:23,
		;)))
	पूर्ण;
	u32 bits;
पूर्ण;

/*
 * single precision (often aka भग्न)
*/
पूर्णांक ieee754sp_class(जोड़ ieee754sp x);

जोड़ ieee754sp ieee754sp_असल(जोड़ ieee754sp x);
जोड़ ieee754sp ieee754sp_neg(जोड़ ieee754sp x);

जोड़ ieee754sp ieee754sp_add(जोड़ ieee754sp x, जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_sub(जोड़ ieee754sp x, जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_mul(जोड़ ieee754sp x, जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_भाग(जोड़ ieee754sp x, जोड़ ieee754sp y);

जोड़ ieee754sp ieee754sp_fपूर्णांक(पूर्णांक x);
जोड़ ieee754sp ieee754sp_fदीर्घ(s64 x);
जोड़ ieee754sp ieee754sp_fdp(जोड़ ieee754dp x);
जोड़ ieee754sp ieee754sp_rपूर्णांक(जोड़ ieee754sp x);

पूर्णांक ieee754sp_tपूर्णांक(जोड़ ieee754sp x);
s64 ieee754sp_tदीर्घ(जोड़ ieee754sp x);

पूर्णांक ieee754sp_cmp(जोड़ ieee754sp x, जोड़ ieee754sp y, पूर्णांक cop, पूर्णांक sig);

जोड़ ieee754sp ieee754sp_वर्ग_मूल(जोड़ ieee754sp x);

जोड़ ieee754sp ieee754sp_maddf(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_msubf(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_madd(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_msub(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_nmadd(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_nmsub(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y);
पूर्णांक ieee754sp_2008class(जोड़ ieee754sp x);
जोड़ ieee754sp ieee754sp_fmin(जोड़ ieee754sp x, जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_fmina(जोड़ ieee754sp x, जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_fmax(जोड़ ieee754sp x, जोड़ ieee754sp y);
जोड़ ieee754sp ieee754sp_fmaxa(जोड़ ieee754sp x, जोड़ ieee754sp y);

/*
 * द्विगुन precision (often aka द्विगुन)
*/
पूर्णांक ieee754dp_class(जोड़ ieee754dp x);

जोड़ ieee754dp ieee754dp_add(जोड़ ieee754dp x, जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_sub(जोड़ ieee754dp x, जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_mul(जोड़ ieee754dp x, जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_भाग(जोड़ ieee754dp x, जोड़ ieee754dp y);

जोड़ ieee754dp ieee754dp_असल(जोड़ ieee754dp x);
जोड़ ieee754dp ieee754dp_neg(जोड़ ieee754dp x);

जोड़ ieee754dp ieee754dp_fपूर्णांक(पूर्णांक x);
जोड़ ieee754dp ieee754dp_fदीर्घ(s64 x);
जोड़ ieee754dp ieee754dp_fsp(जोड़ ieee754sp x);
जोड़ ieee754dp ieee754dp_rपूर्णांक(जोड़ ieee754dp x);

पूर्णांक ieee754dp_tपूर्णांक(जोड़ ieee754dp x);
s64 ieee754dp_tदीर्घ(जोड़ ieee754dp x);

पूर्णांक ieee754dp_cmp(जोड़ ieee754dp x, जोड़ ieee754dp y, पूर्णांक cop, पूर्णांक sig);

जोड़ ieee754dp ieee754dp_वर्ग_मूल(जोड़ ieee754dp x);

जोड़ ieee754dp ieee754dp_maddf(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_msubf(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_madd(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_msub(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_nmadd(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_nmsub(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y);
पूर्णांक ieee754dp_2008class(जोड़ ieee754dp x);
जोड़ ieee754dp ieee754dp_fmin(जोड़ ieee754dp x, जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_fmina(जोड़ ieee754dp x, जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_fmax(जोड़ ieee754dp x, जोड़ ieee754dp y);
जोड़ ieee754dp ieee754dp_fmaxa(जोड़ ieee754dp x, जोड़ ieee754dp y);


/* 5 types of भग्नing poपूर्णांक number
*/
क्रमागत अणु
	IEEE754_CLASS_NORM	= 0x00,
	IEEE754_CLASS_ZERO	= 0x01,
	IEEE754_CLASS_DNORM	= 0x02,
	IEEE754_CLASS_INF	= 0x03,
	IEEE754_CLASS_Sन_अंक	= 0x04,
	IEEE754_CLASS_Qन_अंक	= 0x05,
पूर्ण;

/* exception numbers */
#घोषणा IEEE754_INEXACT			0x01
#घोषणा IEEE754_UNDERFLOW		0x02
#घोषणा IEEE754_OVERFLOW		0x04
#घोषणा IEEE754_ZERO_DIVIDE		0x08
#घोषणा IEEE754_INVALID_OPERATION	0x10

/* cmp चालकs
*/
#घोषणा IEEE754_CLT	0x01
#घोषणा IEEE754_CEQ	0x02
#घोषणा IEEE754_CGT	0x04
#घोषणा IEEE754_CUN	0x08

/*
 * The control status रेजिस्टर
 */
काष्ठा _ieee754_csr अणु
	__BITFIELD_FIELD(अचिन्हित fcc:7,	/* condition[7:1] */
	__BITFIELD_FIELD(अचिन्हित nod:1,	/* set 1 क्रम no denormals */
	__BITFIELD_FIELD(अचिन्हित c:1,		/* condition[0] */
	__BITFIELD_FIELD(अचिन्हित pad0:3,
	__BITFIELD_FIELD(अचिन्हित असल2008:1,	/* IEEE 754-2008 ABS/NEG.fmt */
	__BITFIELD_FIELD(अचिन्हित nan2008:1,	/* IEEE 754-2008 NaN mode */
	__BITFIELD_FIELD(अचिन्हित cx:6,		/* exceptions this operation */
	__BITFIELD_FIELD(अचिन्हित mx:5,		/* exception enable  mask */
	__BITFIELD_FIELD(अचिन्हित sx:5,		/* exceptions total */
	__BITFIELD_FIELD(अचिन्हित rm:2,		/* current rounding mode */
	;))))))))))
पूर्ण;
#घोषणा ieee754_csr (*(काष्ठा _ieee754_csr *)(&current->thपढ़ो.fpu.fcr31))

अटल अंतरभूत अचिन्हित पूर्णांक ieee754_getrm(व्योम)
अणु
	वापस (ieee754_csr.rm);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ieee754_setrm(अचिन्हित पूर्णांक rm)
अणु
	वापस (ieee754_csr.rm = rm);
पूर्ण

/*
 * get current exceptions
 */
अटल अंतरभूत अचिन्हित पूर्णांक ieee754_अ_लोx(व्योम)
अणु
	वापस (ieee754_csr.cx);
पूर्ण

/* test क्रम current exception condition
 */
अटल अंतरभूत पूर्णांक ieee754_cxtest(अचिन्हित पूर्णांक n)
अणु
	वापस (ieee754_csr.cx & n);
पूर्ण

/*
 * get sticky exceptions
 */
अटल अंतरभूत अचिन्हित पूर्णांक ieee754_माला_लोx(व्योम)
अणु
	वापस (ieee754_csr.sx);
पूर्ण

/* clear sticky conditions
*/
अटल अंतरभूत अचिन्हित पूर्णांक ieee754_clrsx(व्योम)
अणु
	वापस (ieee754_csr.sx = 0);
पूर्ण

/* test क्रम sticky exception condition
 */
अटल अंतरभूत पूर्णांक ieee754_sxtest(अचिन्हित पूर्णांक n)
अणु
	वापस (ieee754_csr.sx & n);
पूर्ण

/* debugging */
जोड़ ieee754sp ieee754sp_dump(अक्षर *s, जोड़ ieee754sp x);
जोड़ ieee754dp ieee754dp_dump(अक्षर *s, जोड़ ieee754dp x);

#घोषणा IEEE754_SPCVAL_PZERO		0	/* +0.0 */
#घोषणा IEEE754_SPCVAL_NZERO		1	/* -0.0 */
#घोषणा IEEE754_SPCVAL_PONE		2	/* +1.0 */
#घोषणा IEEE754_SPCVAL_NONE		3	/* -1.0 */
#घोषणा IEEE754_SPCVAL_PTEN		4	/* +10.0 */
#घोषणा IEEE754_SPCVAL_NTEN		5	/* -10.0 */
#घोषणा IEEE754_SPCVAL_Pअनन्त	6	/* +inf */
#घोषणा IEEE754_SPCVAL_Nअनन्त	7	/* -inf */
#घोषणा IEEE754_SPCVAL_INDEF_LEG	8	/* legacy quiet NaN */
#घोषणा IEEE754_SPCVAL_INDEF_2008	9	/* IEEE 754-2008 quiet NaN */
#घोषणा IEEE754_SPCVAL_PMAX		10	/* +max norm */
#घोषणा IEEE754_SPCVAL_NMAX		11	/* -max norm */
#घोषणा IEEE754_SPCVAL_PMIN		12	/* +min norm */
#घोषणा IEEE754_SPCVAL_NMIN		13	/* -min norm */
#घोषणा IEEE754_SPCVAL_PMIND		14	/* +min denorm */
#घोषणा IEEE754_SPCVAL_NMIND		15	/* -min denorm */
#घोषणा IEEE754_SPCVAL_P1E31		16	/* + 1.0e31 */
#घोषणा IEEE754_SPCVAL_P1E63		17	/* + 1.0e63 */

बाह्य स्थिर जोड़ ieee754dp __ieee754dp_spcvals[];
बाह्य स्थिर जोड़ ieee754sp __ieee754sp_spcvals[];
#घोषणा ieee754dp_spcvals ((स्थिर जोड़ ieee754dp *)__ieee754dp_spcvals)
#घोषणा ieee754sp_spcvals ((स्थिर जोड़ ieee754sp *)__ieee754sp_spcvals)

/*
 * Return infinity with given sign
 */
#घोषणा ieee754dp_inf(sn)     (ieee754dp_spcvals[IEEE754_SPCVAL_Pअनन्त+(sn)])
#घोषणा ieee754dp_zero(sn)	(ieee754dp_spcvals[IEEE754_SPCVAL_PZERO+(sn)])
#घोषणा ieee754dp_one(sn)	(ieee754dp_spcvals[IEEE754_SPCVAL_PONE+(sn)])
#घोषणा ieee754dp_ten(sn)	(ieee754dp_spcvals[IEEE754_SPCVAL_PTEN+(sn)])
#घोषणा ieee754dp_indef()	(ieee754dp_spcvals[IEEE754_SPCVAL_INDEF_LEG + \
						   ieee754_csr.nan2008])
#घोषणा ieee754dp_max(sn)	(ieee754dp_spcvals[IEEE754_SPCVAL_PMAX+(sn)])
#घोषणा ieee754dp_min(sn)	(ieee754dp_spcvals[IEEE754_SPCVAL_PMIN+(sn)])
#घोषणा ieee754dp_mind(sn)	(ieee754dp_spcvals[IEEE754_SPCVAL_PMIND+(sn)])
#घोषणा ieee754dp_1e31()	(ieee754dp_spcvals[IEEE754_SPCVAL_P1E31])
#घोषणा ieee754dp_1e63()	(ieee754dp_spcvals[IEEE754_SPCVAL_P1E63])

#घोषणा ieee754sp_inf(sn)     (ieee754sp_spcvals[IEEE754_SPCVAL_Pअनन्त+(sn)])
#घोषणा ieee754sp_zero(sn)	(ieee754sp_spcvals[IEEE754_SPCVAL_PZERO+(sn)])
#घोषणा ieee754sp_one(sn)	(ieee754sp_spcvals[IEEE754_SPCVAL_PONE+(sn)])
#घोषणा ieee754sp_ten(sn)	(ieee754sp_spcvals[IEEE754_SPCVAL_PTEN+(sn)])
#घोषणा ieee754sp_indef()	(ieee754sp_spcvals[IEEE754_SPCVAL_INDEF_LEG + \
						   ieee754_csr.nan2008])
#घोषणा ieee754sp_max(sn)	(ieee754sp_spcvals[IEEE754_SPCVAL_PMAX+(sn)])
#घोषणा ieee754sp_min(sn)	(ieee754sp_spcvals[IEEE754_SPCVAL_PMIN+(sn)])
#घोषणा ieee754sp_mind(sn)	(ieee754sp_spcvals[IEEE754_SPCVAL_PMIND+(sn)])
#घोषणा ieee754sp_1e31()	(ieee754sp_spcvals[IEEE754_SPCVAL_P1E31])
#घोषणा ieee754sp_1e63()	(ieee754sp_spcvals[IEEE754_SPCVAL_P1E63])

/*
 * Indefinite पूर्णांकeger value
 */
अटल अंतरभूत पूर्णांक ieee754si_indef(व्योम)
अणु
	वापस ieee754_csr.nan2008 ? 0 : पूर्णांक_उच्च;
पूर्ण

अटल अंतरभूत s64 ieee754di_indef(व्योम)
अणु
	वापस ieee754_csr.nan2008 ? 0 : S64_MAX;
पूर्ण

/*
 * Overflow पूर्णांकeger value
 */
अटल अंतरभूत पूर्णांक ieee754si_overflow(पूर्णांक xs)
अणु
	वापस ieee754_csr.nan2008 && xs ? पूर्णांक_न्यून : पूर्णांक_उच्च;
पूर्ण

अटल अंतरभूत s64 ieee754di_overflow(पूर्णांक xs)
अणु
	वापस ieee754_csr.nan2008 && xs ? S64_MIN : S64_MAX;
पूर्ण

/* result types क्रम xctx.rt */
#घोषणा IEEE754_RT_SP	0
#घोषणा IEEE754_RT_DP	1
#घोषणा IEEE754_RT_XP	2
#घोषणा IEEE754_RT_SI	3
#घोषणा IEEE754_RT_DI	4

/* compat */
#घोषणा ieee754dp_fix(x)	ieee754dp_tपूर्णांक(x)
#घोषणा ieee754sp_fix(x)	ieee754sp_tपूर्णांक(x)

#पूर्ण_अगर /* __ARCH_MIPS_MATH_EMU_IEEE754_H */
