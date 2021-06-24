<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/lib/xor-neon.c
 *
 * Authors: Jackie Liu <liuyun01@kylinos.cn>
 * Copyright (C) 2018,Tianjin KYLIN Inक्रमmation Technology Co., Ltd.
 */

#समावेश <linux/raid/xor.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/neon-पूर्णांकrinsics.h>

व्योम xor_arm64_neon_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2)
अणु
	uपूर्णांक64_t *dp1 = (uपूर्णांक64_t *)p1;
	uपूर्णांक64_t *dp2 = (uपूर्णांक64_t *)p2;

	रेजिस्टर uपूर्णांक64x2_t v0, v1, v2, v3;
	दीर्घ lines = bytes / (माप(uपूर्णांक64x2_t) * 4);

	करो अणु
		/* p1 ^= p2 */
		v0 = veorq_u64(vld1q_u64(dp1 +  0), vld1q_u64(dp2 +  0));
		v1 = veorq_u64(vld1q_u64(dp1 +  2), vld1q_u64(dp2 +  2));
		v2 = veorq_u64(vld1q_u64(dp1 +  4), vld1q_u64(dp2 +  4));
		v3 = veorq_u64(vld1q_u64(dp1 +  6), vld1q_u64(dp2 +  6));

		/* store */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

व्योम xor_arm64_neon_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2, अचिन्हित दीर्घ *p3)
अणु
	uपूर्णांक64_t *dp1 = (uपूर्णांक64_t *)p1;
	uपूर्णांक64_t *dp2 = (uपूर्णांक64_t *)p2;
	uपूर्णांक64_t *dp3 = (uपूर्णांक64_t *)p3;

	रेजिस्टर uपूर्णांक64x2_t v0, v1, v2, v3;
	दीर्घ lines = bytes / (माप(uपूर्णांक64x2_t) * 4);

	करो अणु
		/* p1 ^= p2 */
		v0 = veorq_u64(vld1q_u64(dp1 +  0), vld1q_u64(dp2 +  0));
		v1 = veorq_u64(vld1q_u64(dp1 +  2), vld1q_u64(dp2 +  2));
		v2 = veorq_u64(vld1q_u64(dp1 +  4), vld1q_u64(dp2 +  4));
		v3 = veorq_u64(vld1q_u64(dp1 +  6), vld1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veorq_u64(v0, vld1q_u64(dp3 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp3 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp3 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp3 +  6));

		/* store */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

व्योम xor_arm64_neon_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2, अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	uपूर्णांक64_t *dp1 = (uपूर्णांक64_t *)p1;
	uपूर्णांक64_t *dp2 = (uपूर्णांक64_t *)p2;
	uपूर्णांक64_t *dp3 = (uपूर्णांक64_t *)p3;
	uपूर्णांक64_t *dp4 = (uपूर्णांक64_t *)p4;

	रेजिस्टर uपूर्णांक64x2_t v0, v1, v2, v3;
	दीर्घ lines = bytes / (माप(uपूर्णांक64x2_t) * 4);

	करो अणु
		/* p1 ^= p2 */
		v0 = veorq_u64(vld1q_u64(dp1 +  0), vld1q_u64(dp2 +  0));
		v1 = veorq_u64(vld1q_u64(dp1 +  2), vld1q_u64(dp2 +  2));
		v2 = veorq_u64(vld1q_u64(dp1 +  4), vld1q_u64(dp2 +  4));
		v3 = veorq_u64(vld1q_u64(dp1 +  6), vld1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veorq_u64(v0, vld1q_u64(dp3 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp3 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp3 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp3 +  6));

		/* p1 ^= p4 */
		v0 = veorq_u64(v0, vld1q_u64(dp4 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp4 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp4 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp4 +  6));

		/* store */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
		dp4 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

व्योम xor_arm64_neon_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2, अचिन्हित दीर्घ *p3,
	अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	uपूर्णांक64_t *dp1 = (uपूर्णांक64_t *)p1;
	uपूर्णांक64_t *dp2 = (uपूर्णांक64_t *)p2;
	uपूर्णांक64_t *dp3 = (uपूर्णांक64_t *)p3;
	uपूर्णांक64_t *dp4 = (uपूर्णांक64_t *)p4;
	uपूर्णांक64_t *dp5 = (uपूर्णांक64_t *)p5;

	रेजिस्टर uपूर्णांक64x2_t v0, v1, v2, v3;
	दीर्घ lines = bytes / (माप(uपूर्णांक64x2_t) * 4);

	करो अणु
		/* p1 ^= p2 */
		v0 = veorq_u64(vld1q_u64(dp1 +  0), vld1q_u64(dp2 +  0));
		v1 = veorq_u64(vld1q_u64(dp1 +  2), vld1q_u64(dp2 +  2));
		v2 = veorq_u64(vld1q_u64(dp1 +  4), vld1q_u64(dp2 +  4));
		v3 = veorq_u64(vld1q_u64(dp1 +  6), vld1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veorq_u64(v0, vld1q_u64(dp3 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp3 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp3 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp3 +  6));

		/* p1 ^= p4 */
		v0 = veorq_u64(v0, vld1q_u64(dp4 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp4 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp4 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp4 +  6));

		/* p1 ^= p5 */
		v0 = veorq_u64(v0, vld1q_u64(dp5 +  0));
		v1 = veorq_u64(v1, vld1q_u64(dp5 +  2));
		v2 = veorq_u64(v2, vld1q_u64(dp5 +  4));
		v3 = veorq_u64(v3, vld1q_u64(dp5 +  6));

		/* store */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
		dp4 += 8;
		dp5 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

काष्ठा xor_block_ढाँचा स्थिर xor_block_inner_neon = अणु
	.name	= "__inner_neon__",
	.करो_2	= xor_arm64_neon_2,
	.करो_3	= xor_arm64_neon_3,
	.करो_4	= xor_arm64_neon_4,
	.करो_5	= xor_arm64_neon_5,
पूर्ण;
EXPORT_SYMBOL(xor_block_inner_neon);

MODULE_AUTHOR("Jackie Liu <liuyun01@kylinos.cn>");
MODULE_DESCRIPTION("ARMv8 XOR Extensions");
MODULE_LICENSE("GPL");
