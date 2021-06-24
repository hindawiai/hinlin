<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* multi_arith.h: multi-precision पूर्णांकeger arithmetic functions, needed
   to करो extended-precision भग्नing poपूर्णांक.

   (c) 1998 David Huggins-Daines.

   Somewhat based on arch/alpha/math-emu/ieee-math.c, which is (c)
   David Mosberger-Tang.

 */

/* Note:

   These are not general multi-precision math routines.  Rather, they
   implement the subset of पूर्णांकeger arithmetic that we need in order to
   multiply, भागide, and normalize 128-bit अचिन्हित mantissae.  */

#अगर_अघोषित MULTI_ARITH_H
#घोषणा MULTI_ARITH_H

अटल अंतरभूत व्योम fp_denormalize(काष्ठा fp_ext *reg, अचिन्हित पूर्णांक cnt)
अणु
	reg->exp += cnt;

	चयन (cnt) अणु
	हाल 0 ... 8:
		reg->lowmant = reg->mant.m32[1] << (8 - cnt);
		reg->mant.m32[1] = (reg->mant.m32[1] >> cnt) |
				   (reg->mant.m32[0] << (32 - cnt));
		reg->mant.m32[0] = reg->mant.m32[0] >> cnt;
		अवरोध;
	हाल 9 ... 32:
		reg->lowmant = reg->mant.m32[1] >> (cnt - 8);
		अगर (reg->mant.m32[1] << (40 - cnt))
			reg->lowmant |= 1;
		reg->mant.m32[1] = (reg->mant.m32[1] >> cnt) |
				   (reg->mant.m32[0] << (32 - cnt));
		reg->mant.m32[0] = reg->mant.m32[0] >> cnt;
		अवरोध;
	हाल 33 ... 39:
		यंत्र अस्थिर ("bfextu %1{%2,#8},%0" : "=d" (reg->lowmant)
			: "m" (reg->mant.m32[0]), "d" (64 - cnt));
		अगर (reg->mant.m32[1] << (40 - cnt))
			reg->lowmant |= 1;
		reg->mant.m32[1] = reg->mant.m32[0] >> (cnt - 32);
		reg->mant.m32[0] = 0;
		अवरोध;
	हाल 40 ... 71:
		reg->lowmant = reg->mant.m32[0] >> (cnt - 40);
		अगर ((reg->mant.m32[0] << (72 - cnt)) || reg->mant.m32[1])
			reg->lowmant |= 1;
		reg->mant.m32[1] = reg->mant.m32[0] >> (cnt - 32);
		reg->mant.m32[0] = 0;
		अवरोध;
	शेष:
		reg->lowmant = reg->mant.m32[0] || reg->mant.m32[1];
		reg->mant.m32[0] = 0;
		reg->mant.m32[1] = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक fp_overnormalize(काष्ठा fp_ext *reg)
अणु
	पूर्णांक shअगरt;

	अगर (reg->mant.m32[0]) अणु
		यंत्र ("bfffo %1{#0,#32},%0" : "=d" (shअगरt) : "dm" (reg->mant.m32[0]));
		reg->mant.m32[0] = (reg->mant.m32[0] << shअगरt) | (reg->mant.m32[1] >> (32 - shअगरt));
		reg->mant.m32[1] = (reg->mant.m32[1] << shअगरt);
	पूर्ण अन्यथा अणु
		यंत्र ("bfffo %1{#0,#32},%0" : "=d" (shअगरt) : "dm" (reg->mant.m32[1]));
		reg->mant.m32[0] = (reg->mant.m32[1] << shअगरt);
		reg->mant.m32[1] = 0;
		shअगरt += 32;
	पूर्ण

	वापस shअगरt;
पूर्ण

अटल अंतरभूत पूर्णांक fp_addmant(काष्ठा fp_ext *dest, काष्ठा fp_ext *src)
अणु
	पूर्णांक carry;

	/* we assume here, gcc only insert move and a clr instr */
	यंत्र अस्थिर ("add.b %1,%0" : "=d,g" (dest->lowmant)
		: "g,d" (src->lowmant), "0,0" (dest->lowmant));
	यंत्र अस्थिर ("addx.l %1,%0" : "=d" (dest->mant.m32[1])
		: "d" (src->mant.m32[1]), "0" (dest->mant.m32[1]));
	यंत्र अस्थिर ("addx.l %1,%0" : "=d" (dest->mant.m32[0])
		: "d" (src->mant.m32[0]), "0" (dest->mant.m32[0]));
	यंत्र अस्थिर ("addx.l %0,%0" : "=d" (carry) : "0" (0));

	वापस carry;
पूर्ण

अटल अंतरभूत पूर्णांक fp_addcarry(काष्ठा fp_ext *reg)
अणु
	अगर (++reg->exp == 0x7fff) अणु
		अगर (reg->mant.m64)
			fp_set_sr(FPSR_EXC_INEX2);
		reg->mant.m64 = 0;
		fp_set_sr(FPSR_EXC_OVFL);
		वापस 0;
	पूर्ण
	reg->lowmant = (reg->mant.m32[1] << 7) | (reg->lowmant ? 1 : 0);
	reg->mant.m32[1] = (reg->mant.m32[1] >> 1) |
			   (reg->mant.m32[0] << 31);
	reg->mant.m32[0] = (reg->mant.m32[0] >> 1) | 0x80000000;

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम fp_submant(काष्ठा fp_ext *dest, काष्ठा fp_ext *src1,
			      काष्ठा fp_ext *src2)
अणु
	/* we assume here, gcc only insert move and a clr instr */
	यंत्र अस्थिर ("sub.b %1,%0" : "=d,g" (dest->lowmant)
		: "g,d" (src2->lowmant), "0,0" (src1->lowmant));
	यंत्र अस्थिर ("subx.l %1,%0" : "=d" (dest->mant.m32[1])
		: "d" (src2->mant.m32[1]), "0" (src1->mant.m32[1]));
	यंत्र अस्थिर ("subx.l %1,%0" : "=d" (dest->mant.m32[0])
		: "d" (src2->mant.m32[0]), "0" (src1->mant.m32[0]));
पूर्ण

#घोषणा fp_mul64(desth, destl, src1, src2) (अणु				\
	यंत्र ("mulu.l %2,%1:%0" : "=d" (destl), "=d" (desth)		\
		: "dm" (src1), "0" (src2));				\
पूर्ण)
#घोषणा fp_भाग64(quot, rem, srch, srcl, भाग)				\
	यंत्र ("divu.l %2,%1:%0" : "=d" (quot), "=d" (rem)		\
		: "dm" (भाग), "1" (srch), "0" (srcl))
#घोषणा fp_add64(dest1, dest2, src1, src2) (अणु				\
	यंत्र ("add.l %1,%0" : "=d,dm" (dest2)				\
		: "dm,d" (src2), "0,0" (dest2));			\
	यंत्र ("addx.l %1,%0" : "=d" (dest1)				\
		: "d" (src1), "0" (dest1));				\
पूर्ण)
#घोषणा fp_addx96(dest, src) (अणु						\
	/* we assume here, gcc only insert move and a clr instr */	\
	यंत्र अस्थिर ("add.l %1,%0" : "=d,g" (dest->m32[2])		\
		: "g,d" (temp.m32[1]), "0,0" (dest->m32[2]));		\
	यंत्र अस्थिर ("addx.l %1,%0" : "=d" (dest->m32[1])		\
		: "d" (temp.m32[0]), "0" (dest->m32[1]));		\
	यंत्र अस्थिर ("addx.l %1,%0" : "=d" (dest->m32[0])		\
		: "d" (0), "0" (dest->m32[0]));				\
पूर्ण)
#घोषणा fp_sub64(dest, src) (अणु						\
	यंत्र ("sub.l %1,%0" : "=d,dm" (dest.m32[1])			\
		: "dm,d" (src.m32[1]), "0,0" (dest.m32[1]));		\
	यंत्र ("subx.l %1,%0" : "=d" (dest.m32[0])			\
		: "d" (src.m32[0]), "0" (dest.m32[0]));			\
पूर्ण)
#घोषणा fp_sub96c(dest, srch, srcm, srcl) (अणु				\
	अक्षर carry;							\
	यंत्र ("sub.l %1,%0" : "=d,dm" (dest.m32[2])			\
		: "dm,d" (srcl), "0,0" (dest.m32[2]));			\
	यंत्र ("subx.l %1,%0" : "=d" (dest.m32[1])			\
		: "d" (srcm), "0" (dest.m32[1]));			\
	यंत्र ("subx.l %2,%1; scs %0" : "=d" (carry), "=d" (dest.m32[0])	\
		: "d" (srch), "1" (dest.m32[0]));			\
	carry;								\
पूर्ण)

अटल अंतरभूत व्योम fp_multiplymant(जोड़ fp_mant128 *dest, काष्ठा fp_ext *src1,
				   काष्ठा fp_ext *src2)
अणु
	जोड़ fp_mant64 temp;

	fp_mul64(dest->m32[0], dest->m32[1], src1->mant.m32[0], src2->mant.m32[0]);
	fp_mul64(dest->m32[2], dest->m32[3], src1->mant.m32[1], src2->mant.m32[1]);

	fp_mul64(temp.m32[0], temp.m32[1], src1->mant.m32[0], src2->mant.m32[1]);
	fp_addx96(dest, temp);

	fp_mul64(temp.m32[0], temp.m32[1], src1->mant.m32[1], src2->mant.m32[0]);
	fp_addx96(dest, temp);
पूर्ण

अटल अंतरभूत व्योम fp_भागidemant(जोड़ fp_mant128 *dest, काष्ठा fp_ext *src,
				 काष्ठा fp_ext *भाग)
अणु
	जोड़ fp_mant128 पंचांगp;
	जोड़ fp_mant64 पंचांगp64;
	अचिन्हित दीर्घ *mantp = dest->m32;
	अचिन्हित दीर्घ fix, rem, first, dummy;
	पूर्णांक i;

	/* the algorithm below requires dest to be smaller than भाग,
	   but both have the high bit set */
	अगर (src->mant.m64 >= भाग->mant.m64) अणु
		fp_sub64(src->mant, भाग->mant);
		*mantp = 1;
	पूर्ण अन्यथा
		*mantp = 0;
	mantp++;

	/* basic idea behind this algorithm: we can't भागide two 64bit numbers
	   (AB/CD) directly, but we can calculate AB/C0, but this means this
	   quotient is off by C0/CD, so we have to multiply the first result
	   to fix the result, after that we have nearly the correct result
	   and only a few corrections are needed. */

	/* C0/CD can be precalculated, but it's an 64bit भागision again, but
	   we can make it a bit easier, by भागiding first through C so we get
	   10/1D and now only a single shअगरt and the value fits पूर्णांकo 32bit. */
	fix = 0x80000000;
	dummy = भाग->mant.m32[1] / भाग->mant.m32[0] + 1;
	dummy = (dummy >> 1) | fix;
	fp_भाग64(fix, dummy, fix, 0, dummy);
	fix--;

	क्रम (i = 0; i < 3; i++, mantp++) अणु
		अगर (src->mant.m32[0] == भाग->mant.m32[0]) अणु
			fp_भाग64(first, rem, 0, src->mant.m32[1], भाग->mant.m32[0]);

			fp_mul64(*mantp, dummy, first, fix);
			*mantp += fix;
		पूर्ण अन्यथा अणु
			fp_भाग64(first, rem, src->mant.m32[0], src->mant.m32[1], भाग->mant.m32[0]);

			fp_mul64(*mantp, dummy, first, fix);
		पूर्ण

		fp_mul64(पंचांगp.m32[0], पंचांगp.m32[1], भाग->mant.m32[0], first - *mantp);
		fp_add64(पंचांगp.m32[0], पंचांगp.m32[1], 0, rem);
		पंचांगp.m32[2] = 0;

		fp_mul64(पंचांगp64.m32[0], पंचांगp64.m32[1], *mantp, भाग->mant.m32[1]);
		fp_sub96c(पंचांगp, 0, पंचांगp64.m32[0], पंचांगp64.m32[1]);

		src->mant.m32[0] = पंचांगp.m32[1];
		src->mant.m32[1] = पंचांगp.m32[2];

		जबतक (!fp_sub96c(पंचांगp, 0, भाग->mant.m32[0], भाग->mant.m32[1])) अणु
			src->mant.m32[0] = पंचांगp.m32[1];
			src->mant.m32[1] = पंचांगp.m32[2];
			*mantp += 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fp_puपंचांगant128(काष्ठा fp_ext *dest, जोड़ fp_mant128 *src,
				 पूर्णांक shअगरt)
अणु
	अचिन्हित दीर्घ पंचांगp;

	चयन (shअगरt) अणु
	हाल 0:
		dest->mant.m64 = src->m64[0];
		dest->lowmant = src->m32[2] >> 24;
		अगर (src->m32[3] || (src->m32[2] << 8))
			dest->lowmant |= 1;
		अवरोध;
	हाल 1:
		यंत्र अस्थिर ("lsl.l #1,%0"
			: "=d" (पंचांगp) : "0" (src->m32[2]));
		यंत्र अस्थिर ("roxl.l #1,%0"
			: "=d" (dest->mant.m32[1]) : "0" (src->m32[1]));
		यंत्र अस्थिर ("roxl.l #1,%0"
			: "=d" (dest->mant.m32[0]) : "0" (src->m32[0]));
		dest->lowmant = पंचांगp >> 24;
		अगर (src->m32[3] || (पंचांगp << 8))
			dest->lowmant |= 1;
		अवरोध;
	हाल 31:
		यंत्र अस्थिर ("lsr.l #1,%1; roxr.l #1,%0"
			: "=d" (dest->mant.m32[0])
			: "d" (src->m32[0]), "0" (src->m32[1]));
		यंत्र अस्थिर ("roxr.l #1,%0"
			: "=d" (dest->mant.m32[1]) : "0" (src->m32[2]));
		यंत्र अस्थिर ("roxr.l #1,%0"
			: "=d" (पंचांगp) : "0" (src->m32[3]));
		dest->lowmant = पंचांगp >> 24;
		अगर (src->m32[3] << 7)
			dest->lowmant |= 1;
		अवरोध;
	हाल 32:
		dest->mant.m32[0] = src->m32[1];
		dest->mant.m32[1] = src->m32[2];
		dest->lowmant = src->m32[3] >> 24;
		अगर (src->m32[3] << 8)
			dest->lowmant |= 1;
		अवरोध;
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* MULTI_ARITH_H */
