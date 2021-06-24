<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2016-2017 INRIA and Microsoft Corporation.
 * Copyright (C) 2018-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is a machine-generated क्रमmally verअगरied implementation of Curve25519
 * ECDH from: <https://github.com/mitls/hacl-star>. Though originally machine
 * generated, it has been tweaked to be suitable क्रम use in the kernel. It is
 * optimized क्रम 64-bit machines that can efficiently work with 128-bit
 * पूर्णांकeger types.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/curve25519.h>
#समावेश <linux/माला.स>

प्रकार __uपूर्णांक128_t u128;

अटल __always_अंतरभूत u64 u64_eq_mask(u64 a, u64 b)
अणु
	u64 x = a ^ b;
	u64 minus_x = ~x + (u64)1U;
	u64 x_or_minus_x = x | minus_x;
	u64 xnx = x_or_minus_x >> (u32)63U;
	u64 c = xnx - (u64)1U;
	वापस c;
पूर्ण

अटल __always_अंतरभूत u64 u64_gte_mask(u64 a, u64 b)
अणु
	u64 x = a;
	u64 y = b;
	u64 x_xor_y = x ^ y;
	u64 x_sub_y = x - y;
	u64 x_sub_y_xor_y = x_sub_y ^ y;
	u64 q = x_xor_y | x_sub_y_xor_y;
	u64 x_xor_q = x ^ q;
	u64 x_xor_q_ = x_xor_q >> (u32)63U;
	u64 c = x_xor_q_ - (u64)1U;
	वापस c;
पूर्ण

अटल __always_अंतरभूत व्योम modulo_carry_top(u64 *b)
अणु
	u64 b4 = b[4];
	u64 b0 = b[0];
	u64 b4_ = b4 & 0x7ffffffffffffLLU;
	u64 b0_ = b0 + 19 * (b4 >> 51);
	b[4] = b4_;
	b[0] = b0_;
पूर्ण

अटल __always_अंतरभूत व्योम fproduct_copy_from_wide_(u64 *output, u128 *input)
अणु
	अणु
		u128 xi = input[0];
		output[0] = ((u64)(xi));
	पूर्ण
	अणु
		u128 xi = input[1];
		output[1] = ((u64)(xi));
	पूर्ण
	अणु
		u128 xi = input[2];
		output[2] = ((u64)(xi));
	पूर्ण
	अणु
		u128 xi = input[3];
		output[3] = ((u64)(xi));
	पूर्ण
	अणु
		u128 xi = input[4];
		output[4] = ((u64)(xi));
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम
fproduct_sum_scalar_multiplication_(u128 *output, u64 *input, u64 s)
अणु
	output[0] += (u128)input[0] * s;
	output[1] += (u128)input[1] * s;
	output[2] += (u128)input[2] * s;
	output[3] += (u128)input[3] * s;
	output[4] += (u128)input[4] * s;
पूर्ण

अटल __always_अंतरभूत व्योम fproduct_carry_wide_(u128 *पंचांगp)
अणु
	अणु
		u32 ctr = 0;
		u128 tctr = पंचांगp[ctr];
		u128 tctrp1 = पंचांगp[ctr + 1];
		u64 r0 = ((u64)(tctr)) & 0x7ffffffffffffLLU;
		u128 c = ((tctr) >> (51));
		पंचांगp[ctr] = ((u128)(r0));
		पंचांगp[ctr + 1] = ((tctrp1) + (c));
	पूर्ण
	अणु
		u32 ctr = 1;
		u128 tctr = पंचांगp[ctr];
		u128 tctrp1 = पंचांगp[ctr + 1];
		u64 r0 = ((u64)(tctr)) & 0x7ffffffffffffLLU;
		u128 c = ((tctr) >> (51));
		पंचांगp[ctr] = ((u128)(r0));
		पंचांगp[ctr + 1] = ((tctrp1) + (c));
	पूर्ण

	अणु
		u32 ctr = 2;
		u128 tctr = पंचांगp[ctr];
		u128 tctrp1 = पंचांगp[ctr + 1];
		u64 r0 = ((u64)(tctr)) & 0x7ffffffffffffLLU;
		u128 c = ((tctr) >> (51));
		पंचांगp[ctr] = ((u128)(r0));
		पंचांगp[ctr + 1] = ((tctrp1) + (c));
	पूर्ण
	अणु
		u32 ctr = 3;
		u128 tctr = पंचांगp[ctr];
		u128 tctrp1 = पंचांगp[ctr + 1];
		u64 r0 = ((u64)(tctr)) & 0x7ffffffffffffLLU;
		u128 c = ((tctr) >> (51));
		पंचांगp[ctr] = ((u128)(r0));
		पंचांगp[ctr + 1] = ((tctrp1) + (c));
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम fmul_shअगरt_reduce(u64 *output)
अणु
	u64 पंचांगp = output[4];
	u64 b0;
	अणु
		u32 ctr = 5 - 0 - 1;
		u64 z = output[ctr - 1];
		output[ctr] = z;
	पूर्ण
	अणु
		u32 ctr = 5 - 1 - 1;
		u64 z = output[ctr - 1];
		output[ctr] = z;
	पूर्ण
	अणु
		u32 ctr = 5 - 2 - 1;
		u64 z = output[ctr - 1];
		output[ctr] = z;
	पूर्ण
	अणु
		u32 ctr = 5 - 3 - 1;
		u64 z = output[ctr - 1];
		output[ctr] = z;
	पूर्ण
	output[0] = पंचांगp;
	b0 = output[0];
	output[0] = 19 * b0;
पूर्ण

अटल __always_अंतरभूत व्योम fmul_mul_shअगरt_reduce_(u128 *output, u64 *input,
						   u64 *input21)
अणु
	u32 i;
	u64 input2i;
	अणु
		u64 input2i = input21[0];
		fproduct_sum_scalar_multiplication_(output, input, input2i);
		fmul_shअगरt_reduce(input);
	पूर्ण
	अणु
		u64 input2i = input21[1];
		fproduct_sum_scalar_multiplication_(output, input, input2i);
		fmul_shअगरt_reduce(input);
	पूर्ण
	अणु
		u64 input2i = input21[2];
		fproduct_sum_scalar_multiplication_(output, input, input2i);
		fmul_shअगरt_reduce(input);
	पूर्ण
	अणु
		u64 input2i = input21[3];
		fproduct_sum_scalar_multiplication_(output, input, input2i);
		fmul_shअगरt_reduce(input);
	पूर्ण
	i = 4;
	input2i = input21[i];
	fproduct_sum_scalar_multiplication_(output, input, input2i);
पूर्ण

अटल __always_अंतरभूत व्योम fmul_fmul(u64 *output, u64 *input, u64 *input21)
अणु
	u64 पंचांगp[5] = अणु input[0], input[1], input[2], input[3], input[4] पूर्ण;
	अणु
		u128 b4;
		u128 b0;
		u128 b4_;
		u128 b0_;
		u64 i0;
		u64 i1;
		u64 i0_;
		u64 i1_;
		u128 t[5] = अणु 0 पूर्ण;
		fmul_mul_shअगरt_reduce_(t, पंचांगp, input21);
		fproduct_carry_wide_(t);
		b4 = t[4];
		b0 = t[0];
		b4_ = ((b4) & (((u128)(0x7ffffffffffffLLU))));
		b0_ = ((b0) + (((u128)(19) * (((u64)(((b4) >> (51))))))));
		t[4] = b4_;
		t[0] = b0_;
		fproduct_copy_from_wide_(output, t);
		i0 = output[0];
		i1 = output[1];
		i0_ = i0 & 0x7ffffffffffffLLU;
		i1_ = i1 + (i0 >> 51);
		output[0] = i0_;
		output[1] = i1_;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम fsquare_fsquare__(u128 *पंचांगp, u64 *output)
अणु
	u64 r0 = output[0];
	u64 r1 = output[1];
	u64 r2 = output[2];
	u64 r3 = output[3];
	u64 r4 = output[4];
	u64 d0 = r0 * 2;
	u64 d1 = r1 * 2;
	u64 d2 = r2 * 2 * 19;
	u64 d419 = r4 * 19;
	u64 d4 = d419 * 2;
	u128 s0 = ((((((u128)(r0) * (r0))) + (((u128)(d4) * (r1))))) +
		   (((u128)(d2) * (r3))));
	u128 s1 = ((((((u128)(d0) * (r1))) + (((u128)(d4) * (r2))))) +
		   (((u128)(r3 * 19) * (r3))));
	u128 s2 = ((((((u128)(d0) * (r2))) + (((u128)(r1) * (r1))))) +
		   (((u128)(d4) * (r3))));
	u128 s3 = ((((((u128)(d0) * (r3))) + (((u128)(d1) * (r2))))) +
		   (((u128)(r4) * (d419))));
	u128 s4 = ((((((u128)(d0) * (r4))) + (((u128)(d1) * (r3))))) +
		   (((u128)(r2) * (r2))));
	पंचांगp[0] = s0;
	पंचांगp[1] = s1;
	पंचांगp[2] = s2;
	पंचांगp[3] = s3;
	पंचांगp[4] = s4;
पूर्ण

अटल __always_अंतरभूत व्योम fsquare_fsquare_(u128 *पंचांगp, u64 *output)
अणु
	u128 b4;
	u128 b0;
	u128 b4_;
	u128 b0_;
	u64 i0;
	u64 i1;
	u64 i0_;
	u64 i1_;
	fsquare_fsquare__(पंचांगp, output);
	fproduct_carry_wide_(पंचांगp);
	b4 = पंचांगp[4];
	b0 = पंचांगp[0];
	b4_ = ((b4) & (((u128)(0x7ffffffffffffLLU))));
	b0_ = ((b0) + (((u128)(19) * (((u64)(((b4) >> (51))))))));
	पंचांगp[4] = b4_;
	पंचांगp[0] = b0_;
	fproduct_copy_from_wide_(output, पंचांगp);
	i0 = output[0];
	i1 = output[1];
	i0_ = i0 & 0x7ffffffffffffLLU;
	i1_ = i1 + (i0 >> 51);
	output[0] = i0_;
	output[1] = i1_;
पूर्ण

अटल __always_अंतरभूत व्योम fsquare_fsquare_बार_(u64 *output, u128 *पंचांगp,
						   u32 count1)
अणु
	u32 i;
	fsquare_fsquare_(पंचांगp, output);
	क्रम (i = 1; i < count1; ++i)
		fsquare_fsquare_(पंचांगp, output);
पूर्ण

अटल __always_अंतरभूत व्योम fsquare_fsquare_बार(u64 *output, u64 *input,
						  u32 count1)
अणु
	u128 t[5];
	स_नकल(output, input, 5 * माप(*input));
	fsquare_fsquare_बार_(output, t, count1);
पूर्ण

अटल __always_अंतरभूत व्योम fsquare_fsquare_बार_inplace(u64 *output,
							  u32 count1)
अणु
	u128 t[5];
	fsquare_fsquare_बार_(output, t, count1);
पूर्ण

अटल __always_अंतरभूत व्योम crecip_crecip(u64 *out, u64 *z)
अणु
	u64 buf[20] = अणु 0 पूर्ण;
	u64 *a0 = buf;
	u64 *t00 = buf + 5;
	u64 *b0 = buf + 10;
	u64 *t01;
	u64 *b1;
	u64 *c0;
	u64 *a;
	u64 *t0;
	u64 *b;
	u64 *c;
	fsquare_fsquare_बार(a0, z, 1);
	fsquare_fsquare_बार(t00, a0, 2);
	fmul_fmul(b0, t00, z);
	fmul_fmul(a0, b0, a0);
	fsquare_fsquare_बार(t00, a0, 1);
	fmul_fmul(b0, t00, b0);
	fsquare_fsquare_बार(t00, b0, 5);
	t01 = buf + 5;
	b1 = buf + 10;
	c0 = buf + 15;
	fmul_fmul(b1, t01, b1);
	fsquare_fsquare_बार(t01, b1, 10);
	fmul_fmul(c0, t01, b1);
	fsquare_fsquare_बार(t01, c0, 20);
	fmul_fmul(t01, t01, c0);
	fsquare_fsquare_बार_inplace(t01, 10);
	fmul_fmul(b1, t01, b1);
	fsquare_fsquare_बार(t01, b1, 50);
	a = buf;
	t0 = buf + 5;
	b = buf + 10;
	c = buf + 15;
	fmul_fmul(c, t0, b);
	fsquare_fsquare_बार(t0, c, 100);
	fmul_fmul(t0, t0, c);
	fsquare_fsquare_बार_inplace(t0, 50);
	fmul_fmul(t0, t0, b);
	fsquare_fsquare_बार_inplace(t0, 5);
	fmul_fmul(out, t0, a);
पूर्ण

अटल __always_अंतरभूत व्योम fsum(u64 *a, u64 *b)
अणु
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
	a[4] += b[4];
पूर्ण

अटल __always_अंतरभूत व्योम fdअगरference(u64 *a, u64 *b)
अणु
	u64 पंचांगp[5] = अणु 0 पूर्ण;
	u64 b0;
	u64 b1;
	u64 b2;
	u64 b3;
	u64 b4;
	स_नकल(पंचांगp, b, 5 * माप(*b));
	b0 = पंचांगp[0];
	b1 = पंचांगp[1];
	b2 = पंचांगp[2];
	b3 = पंचांगp[3];
	b4 = पंचांगp[4];
	पंचांगp[0] = b0 + 0x3fffffffffff68LLU;
	पंचांगp[1] = b1 + 0x3ffffffffffff8LLU;
	पंचांगp[2] = b2 + 0x3ffffffffffff8LLU;
	पंचांगp[3] = b3 + 0x3ffffffffffff8LLU;
	पंचांगp[4] = b4 + 0x3ffffffffffff8LLU;
	अणु
		u64 xi = a[0];
		u64 yi = पंचांगp[0];
		a[0] = yi - xi;
	पूर्ण
	अणु
		u64 xi = a[1];
		u64 yi = पंचांगp[1];
		a[1] = yi - xi;
	पूर्ण
	अणु
		u64 xi = a[2];
		u64 yi = पंचांगp[2];
		a[2] = yi - xi;
	पूर्ण
	अणु
		u64 xi = a[3];
		u64 yi = पंचांगp[3];
		a[3] = yi - xi;
	पूर्ण
	अणु
		u64 xi = a[4];
		u64 yi = पंचांगp[4];
		a[4] = yi - xi;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम fscalar(u64 *output, u64 *b, u64 s)
अणु
	u128 पंचांगp[5];
	u128 b4;
	u128 b0;
	u128 b4_;
	u128 b0_;
	अणु
		u64 xi = b[0];
		पंचांगp[0] = ((u128)(xi) * (s));
	पूर्ण
	अणु
		u64 xi = b[1];
		पंचांगp[1] = ((u128)(xi) * (s));
	पूर्ण
	अणु
		u64 xi = b[2];
		पंचांगp[2] = ((u128)(xi) * (s));
	पूर्ण
	अणु
		u64 xi = b[3];
		पंचांगp[3] = ((u128)(xi) * (s));
	पूर्ण
	अणु
		u64 xi = b[4];
		पंचांगp[4] = ((u128)(xi) * (s));
	पूर्ण
	fproduct_carry_wide_(पंचांगp);
	b4 = पंचांगp[4];
	b0 = पंचांगp[0];
	b4_ = ((b4) & (((u128)(0x7ffffffffffffLLU))));
	b0_ = ((b0) + (((u128)(19) * (((u64)(((b4) >> (51))))))));
	पंचांगp[4] = b4_;
	पंचांगp[0] = b0_;
	fproduct_copy_from_wide_(output, पंचांगp);
पूर्ण

अटल __always_अंतरभूत व्योम fmul(u64 *output, u64 *a, u64 *b)
अणु
	fmul_fmul(output, a, b);
पूर्ण

अटल __always_अंतरभूत व्योम crecip(u64 *output, u64 *input)
अणु
	crecip_crecip(output, input);
पूर्ण

अटल __always_अंतरभूत व्योम poपूर्णांक_swap_conditional_step(u64 *a, u64 *b,
							u64 swap1, u32 ctr)
अणु
	u32 i = ctr - 1;
	u64 ai = a[i];
	u64 bi = b[i];
	u64 x = swap1 & (ai ^ bi);
	u64 ai1 = ai ^ x;
	u64 bi1 = bi ^ x;
	a[i] = ai1;
	b[i] = bi1;
पूर्ण

अटल __always_अंतरभूत व्योम poपूर्णांक_swap_conditional5(u64 *a, u64 *b, u64 swap1)
अणु
	poपूर्णांक_swap_conditional_step(a, b, swap1, 5);
	poपूर्णांक_swap_conditional_step(a, b, swap1, 4);
	poपूर्णांक_swap_conditional_step(a, b, swap1, 3);
	poपूर्णांक_swap_conditional_step(a, b, swap1, 2);
	poपूर्णांक_swap_conditional_step(a, b, swap1, 1);
पूर्ण

अटल __always_अंतरभूत व्योम poपूर्णांक_swap_conditional(u64 *a, u64 *b, u64 iswap)
अणु
	u64 swap1 = 0 - iswap;
	poपूर्णांक_swap_conditional5(a, b, swap1);
	poपूर्णांक_swap_conditional5(a + 5, b + 5, swap1);
पूर्ण

अटल __always_अंतरभूत व्योम poपूर्णांक_copy(u64 *output, u64 *input)
अणु
	स_नकल(output, input, 5 * माप(*input));
	स_नकल(output + 5, input + 5, 5 * माप(*input));
पूर्ण

अटल __always_अंतरभूत व्योम addandद्विगुन_fmonty(u64 *pp, u64 *ppq, u64 *p,
						u64 *pq, u64 *qmqp)
अणु
	u64 *qx = qmqp;
	u64 *x2 = pp;
	u64 *z2 = pp + 5;
	u64 *x3 = ppq;
	u64 *z3 = ppq + 5;
	u64 *x = p;
	u64 *z = p + 5;
	u64 *xprime = pq;
	u64 *zprime = pq + 5;
	u64 buf[40] = अणु 0 पूर्ण;
	u64 *origx = buf;
	u64 *origxprime0 = buf + 5;
	u64 *xxprime0;
	u64 *zzprime0;
	u64 *origxprime;
	xxprime0 = buf + 25;
	zzprime0 = buf + 30;
	स_नकल(origx, x, 5 * माप(*x));
	fsum(x, z);
	fdअगरference(z, origx);
	स_नकल(origxprime0, xprime, 5 * माप(*xprime));
	fsum(xprime, zprime);
	fdअगरference(zprime, origxprime0);
	fmul(xxprime0, xprime, z);
	fmul(zzprime0, x, zprime);
	origxprime = buf + 5;
	अणु
		u64 *xx0;
		u64 *zz0;
		u64 *xxprime;
		u64 *zzprime;
		u64 *zzzprime;
		xx0 = buf + 15;
		zz0 = buf + 20;
		xxprime = buf + 25;
		zzprime = buf + 30;
		zzzprime = buf + 35;
		स_नकल(origxprime, xxprime, 5 * माप(*xxprime));
		fsum(xxprime, zzprime);
		fdअगरference(zzprime, origxprime);
		fsquare_fsquare_बार(x3, xxprime, 1);
		fsquare_fsquare_बार(zzzprime, zzprime, 1);
		fmul(z3, zzzprime, qx);
		fsquare_fsquare_बार(xx0, x, 1);
		fsquare_fsquare_बार(zz0, z, 1);
		अणु
			u64 *zzz;
			u64 *xx;
			u64 *zz;
			u64 scalar;
			zzz = buf + 10;
			xx = buf + 15;
			zz = buf + 20;
			fmul(x2, xx, zz);
			fdअगरference(zz, xx);
			scalar = 121665;
			fscalar(zzz, zz, scalar);
			fsum(zzz, xx);
			fmul(z2, zzz, zz);
		पूर्ण
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम
ladder_smallloop_cmult_small_loop_step(u64 *nq, u64 *nqpq, u64 *nq2, u64 *nqpq2,
				       u64 *q, u8 byt)
अणु
	u64 bit0 = (u64)(byt >> 7);
	u64 bit;
	poपूर्णांक_swap_conditional(nq, nqpq, bit0);
	addandद्विगुन_fmonty(nq2, nqpq2, nq, nqpq, q);
	bit = (u64)(byt >> 7);
	poपूर्णांक_swap_conditional(nq2, nqpq2, bit);
पूर्ण

अटल __always_अंतरभूत व्योम
ladder_smallloop_cmult_small_loop_द्विगुन_step(u64 *nq, u64 *nqpq, u64 *nq2,
					      u64 *nqpq2, u64 *q, u8 byt)
अणु
	u8 byt1;
	ladder_smallloop_cmult_small_loop_step(nq, nqpq, nq2, nqpq2, q, byt);
	byt1 = byt << 1;
	ladder_smallloop_cmult_small_loop_step(nq2, nqpq2, nq, nqpq, q, byt1);
पूर्ण

अटल __always_अंतरभूत व्योम
ladder_smallloop_cmult_small_loop(u64 *nq, u64 *nqpq, u64 *nq2, u64 *nqpq2,
				  u64 *q, u8 byt, u32 i)
अणु
	जबतक (i--) अणु
		ladder_smallloop_cmult_small_loop_द्विगुन_step(nq, nqpq, nq2,
							      nqpq2, q, byt);
		byt <<= 2;
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम ladder_bigloop_cmult_big_loop(u8 *n1, u64 *nq,
							  u64 *nqpq, u64 *nq2,
							  u64 *nqpq2, u64 *q,
							  u32 i)
अणु
	जबतक (i--) अणु
		u8 byte = n1[i];
		ladder_smallloop_cmult_small_loop(nq, nqpq, nq2, nqpq2, q,
						  byte, 4);
	पूर्ण
पूर्ण

अटल व्योम ladder_cmult(u64 *result, u8 *n1, u64 *q)
अणु
	u64 poपूर्णांक_buf[40] = अणु 0 पूर्ण;
	u64 *nq = poपूर्णांक_buf;
	u64 *nqpq = poपूर्णांक_buf + 10;
	u64 *nq2 = poपूर्णांक_buf + 20;
	u64 *nqpq2 = poपूर्णांक_buf + 30;
	poपूर्णांक_copy(nqpq, q);
	nq[0] = 1;
	ladder_bigloop_cmult_big_loop(n1, nq, nqpq, nq2, nqpq2, q, 32);
	poपूर्णांक_copy(result, nq);
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fexpand(u64 *output, स्थिर u8 *input)
अणु
	स्थिर u8 *x00 = input + 6;
	स्थिर u8 *x01 = input + 12;
	स्थिर u8 *x02 = input + 19;
	स्थिर u8 *x0 = input + 24;
	u64 i0, i1, i2, i3, i4, output0, output1, output2, output3, output4;
	i0 = get_unaligned_le64(input);
	i1 = get_unaligned_le64(x00);
	i2 = get_unaligned_le64(x01);
	i3 = get_unaligned_le64(x02);
	i4 = get_unaligned_le64(x0);
	output0 = i0 & 0x7ffffffffffffLLU;
	output1 = i1 >> 3 & 0x7ffffffffffffLLU;
	output2 = i2 >> 6 & 0x7ffffffffffffLLU;
	output3 = i3 >> 1 & 0x7ffffffffffffLLU;
	output4 = i4 >> 12 & 0x7ffffffffffffLLU;
	output[0] = output0;
	output[1] = output1;
	output[2] = output2;
	output[3] = output3;
	output[4] = output4;
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract_first_carry_pass(u64 *input)
अणु
	u64 t0 = input[0];
	u64 t1 = input[1];
	u64 t2 = input[2];
	u64 t3 = input[3];
	u64 t4 = input[4];
	u64 t1_ = t1 + (t0 >> 51);
	u64 t0_ = t0 & 0x7ffffffffffffLLU;
	u64 t2_ = t2 + (t1_ >> 51);
	u64 t1__ = t1_ & 0x7ffffffffffffLLU;
	u64 t3_ = t3 + (t2_ >> 51);
	u64 t2__ = t2_ & 0x7ffffffffffffLLU;
	u64 t4_ = t4 + (t3_ >> 51);
	u64 t3__ = t3_ & 0x7ffffffffffffLLU;
	input[0] = t0_;
	input[1] = t1__;
	input[2] = t2__;
	input[3] = t3__;
	input[4] = t4_;
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract_first_carry_full(u64 *input)
अणु
	क्रमmat_fcontract_first_carry_pass(input);
	modulo_carry_top(input);
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract_second_carry_pass(u64 *input)
अणु
	u64 t0 = input[0];
	u64 t1 = input[1];
	u64 t2 = input[2];
	u64 t3 = input[3];
	u64 t4 = input[4];
	u64 t1_ = t1 + (t0 >> 51);
	u64 t0_ = t0 & 0x7ffffffffffffLLU;
	u64 t2_ = t2 + (t1_ >> 51);
	u64 t1__ = t1_ & 0x7ffffffffffffLLU;
	u64 t3_ = t3 + (t2_ >> 51);
	u64 t2__ = t2_ & 0x7ffffffffffffLLU;
	u64 t4_ = t4 + (t3_ >> 51);
	u64 t3__ = t3_ & 0x7ffffffffffffLLU;
	input[0] = t0_;
	input[1] = t1__;
	input[2] = t2__;
	input[3] = t3__;
	input[4] = t4_;
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract_second_carry_full(u64 *input)
अणु
	u64 i0;
	u64 i1;
	u64 i0_;
	u64 i1_;
	क्रमmat_fcontract_second_carry_pass(input);
	modulo_carry_top(input);
	i0 = input[0];
	i1 = input[1];
	i0_ = i0 & 0x7ffffffffffffLLU;
	i1_ = i1 + (i0 >> 51);
	input[0] = i0_;
	input[1] = i1_;
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract_trim(u64 *input)
अणु
	u64 a0 = input[0];
	u64 a1 = input[1];
	u64 a2 = input[2];
	u64 a3 = input[3];
	u64 a4 = input[4];
	u64 mask0 = u64_gte_mask(a0, 0x7ffffffffffedLLU);
	u64 mask1 = u64_eq_mask(a1, 0x7ffffffffffffLLU);
	u64 mask2 = u64_eq_mask(a2, 0x7ffffffffffffLLU);
	u64 mask3 = u64_eq_mask(a3, 0x7ffffffffffffLLU);
	u64 mask4 = u64_eq_mask(a4, 0x7ffffffffffffLLU);
	u64 mask = (((mask0 & mask1) & mask2) & mask3) & mask4;
	u64 a0_ = a0 - (0x7ffffffffffedLLU & mask);
	u64 a1_ = a1 - (0x7ffffffffffffLLU & mask);
	u64 a2_ = a2 - (0x7ffffffffffffLLU & mask);
	u64 a3_ = a3 - (0x7ffffffffffffLLU & mask);
	u64 a4_ = a4 - (0x7ffffffffffffLLU & mask);
	input[0] = a0_;
	input[1] = a1_;
	input[2] = a2_;
	input[3] = a3_;
	input[4] = a4_;
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract_store(u8 *output, u64 *input)
अणु
	u64 t0 = input[0];
	u64 t1 = input[1];
	u64 t2 = input[2];
	u64 t3 = input[3];
	u64 t4 = input[4];
	u64 o0 = t1 << 51 | t0;
	u64 o1 = t2 << 38 | t1 >> 13;
	u64 o2 = t3 << 25 | t2 >> 26;
	u64 o3 = t4 << 12 | t3 >> 39;
	u8 *b0 = output;
	u8 *b1 = output + 8;
	u8 *b2 = output + 16;
	u8 *b3 = output + 24;
	put_unaligned_le64(o0, b0);
	put_unaligned_le64(o1, b1);
	put_unaligned_le64(o2, b2);
	put_unaligned_le64(o3, b3);
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_fcontract(u8 *output, u64 *input)
अणु
	क्रमmat_fcontract_first_carry_full(input);
	क्रमmat_fcontract_second_carry_full(input);
	क्रमmat_fcontract_trim(input);
	क्रमmat_fcontract_store(output, input);
पूर्ण

अटल __always_अंतरभूत व्योम क्रमmat_scalar_of_poपूर्णांक(u8 *scalar, u64 *poपूर्णांक)
अणु
	u64 *x = poपूर्णांक;
	u64 *z = poपूर्णांक + 5;
	u64 buf[10] __aligned(32) = अणु 0 पूर्ण;
	u64 *zmone = buf;
	u64 *sc = buf + 5;
	crecip(zmone, z);
	fmul(sc, x, zmone);
	क्रमmat_fcontract(scalar, sc);
पूर्ण

व्योम curve25519_generic(u8 myखुला[CURVE25519_KEY_SIZE],
			स्थिर u8 secret[CURVE25519_KEY_SIZE],
			स्थिर u8 basepoपूर्णांक[CURVE25519_KEY_SIZE])
अणु
	u64 buf0[10] __aligned(32) = अणु 0 पूर्ण;
	u64 *x0 = buf0;
	u64 *z = buf0 + 5;
	u64 *q;
	क्रमmat_fexpand(x0, basepoपूर्णांक);
	z[0] = 1;
	q = buf0;
	अणु
		u8 e[32] __aligned(32) = अणु 0 पूर्ण;
		u8 *scalar;
		स_नकल(e, secret, 32);
		curve25519_clamp_secret(e);
		scalar = e;
		अणु
			u64 buf[15] = अणु 0 पूर्ण;
			u64 *nq = buf;
			u64 *x = nq;
			x[0] = 1;
			ladder_cmult(nq, scalar, q);
			क्रमmat_scalar_of_poपूर्णांक(myखुला, nq);
			memzero_explicit(buf, माप(buf));
		पूर्ण
		memzero_explicit(e, माप(e));
	पूर्ण
	memzero_explicit(buf0, माप(buf0));
पूर्ण
