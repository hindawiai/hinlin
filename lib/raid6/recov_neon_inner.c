<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Intel Corporation
 * Copyright (C) 2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <arm_neon.h>

#अगर_घोषित CONFIG_ARM
/*
 * AArch32 करोes not provide this पूर्णांकrinsic natively because it करोes not
 * implement the underlying inकाष्ठाion. AArch32 only provides a 64-bit
 * wide vtbl.8 inकाष्ठाion, so use that instead.
 */
अटल uपूर्णांक8x16_t vqtbl1q_u8(uपूर्णांक8x16_t a, uपूर्णांक8x16_t b)
अणु
	जोड़ अणु
		uपूर्णांक8x16_t	val;
		uपूर्णांक8x8x2_t	pair;
	पूर्ण __a = अणु a पूर्ण;

	वापस vcombine_u8(vtbl2_u8(__a.pair, vget_low_u8(b)),
			   vtbl2_u8(__a.pair, vget_high_u8(b)));
पूर्ण
#पूर्ण_अगर

व्योम __raid6_2data_recov_neon(पूर्णांक bytes, uपूर्णांक8_t *p, uपूर्णांक8_t *q, uपूर्णांक8_t *dp,
			      uपूर्णांक8_t *dq, स्थिर uपूर्णांक8_t *pbmul,
			      स्थिर uपूर्णांक8_t *qmul)
अणु
	uपूर्णांक8x16_t pm0 = vld1q_u8(pbmul);
	uपूर्णांक8x16_t pm1 = vld1q_u8(pbmul + 16);
	uपूर्णांक8x16_t qm0 = vld1q_u8(qmul);
	uपूर्णांक8x16_t qm1 = vld1q_u8(qmul + 16);
	uपूर्णांक8x16_t x0f = vdupq_n_u8(0x0f);

	/*
	 * जबतक ( bytes-- ) अणु
	 *	uपूर्णांक8_t px, qx, db;
	 *
	 *	px    = *p ^ *dp;
	 *	qx    = qmul[*q ^ *dq];
	 *	*dq++ = db = pbmul[px] ^ qx;
	 *	*dp++ = db ^ px;
	 *	p++; q++;
	 * पूर्ण
	 */

	जबतक (bytes) अणु
		uपूर्णांक8x16_t vx, vy, px, qx, db;

		px = veorq_u8(vld1q_u8(p), vld1q_u8(dp));
		vx = veorq_u8(vld1q_u8(q), vld1q_u8(dq));

		vy = vshrq_n_u8(vx, 4);
		vx = vqtbl1q_u8(qm0, vandq_u8(vx, x0f));
		vy = vqtbl1q_u8(qm1, vy);
		qx = veorq_u8(vx, vy);

		vy = vshrq_n_u8(px, 4);
		vx = vqtbl1q_u8(pm0, vandq_u8(px, x0f));
		vy = vqtbl1q_u8(pm1, vy);
		vx = veorq_u8(vx, vy);
		db = veorq_u8(vx, qx);

		vst1q_u8(dq, db);
		vst1q_u8(dp, veorq_u8(db, px));

		bytes -= 16;
		p += 16;
		q += 16;
		dp += 16;
		dq += 16;
	पूर्ण
पूर्ण

व्योम __raid6_datap_recov_neon(पूर्णांक bytes, uपूर्णांक8_t *p, uपूर्णांक8_t *q, uपूर्णांक8_t *dq,
			      स्थिर uपूर्णांक8_t *qmul)
अणु
	uपूर्णांक8x16_t qm0 = vld1q_u8(qmul);
	uपूर्णांक8x16_t qm1 = vld1q_u8(qmul + 16);
	uपूर्णांक8x16_t x0f = vdupq_n_u8(0x0f);

	/*
	 * जबतक (bytes--) अणु
	 *	*p++ ^= *dq = qmul[*q ^ *dq];
	 *	q++; dq++;
	 * पूर्ण
	 */

	जबतक (bytes) अणु
		uपूर्णांक8x16_t vx, vy;

		vx = veorq_u8(vld1q_u8(q), vld1q_u8(dq));

		vy = vshrq_n_u8(vx, 4);
		vx = vqtbl1q_u8(qm0, vandq_u8(vx, x0f));
		vy = vqtbl1q_u8(qm1, vy);
		vx = veorq_u8(vx, vy);
		vy = veorq_u8(vx, vld1q_u8(p));

		vst1q_u8(dq, vx);
		vst1q_u8(p, vy);

		bytes -= 16;
		p += 16;
		q += 16;
		dq += 16;
	पूर्ण
पूर्ण
