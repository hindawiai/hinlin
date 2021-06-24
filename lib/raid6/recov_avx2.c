<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Intel Corporation
 * Author: Jim Kukunas <james.t.kukunas@linux.पूर्णांकel.com>
 */

#समावेश <linux/raid/pq.h>
#समावेश "x86.h"

अटल पूर्णांक raid6_has_avx2(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_AVX2) &&
		boot_cpu_has(X86_FEATURE_AVX);
पूर्ण

अटल व्योम raid6_2data_recov_avx2(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		पूर्णांक failb, व्योम **ptrs)
अणु
	u8 *p, *q, *dp, *dq;
	स्थिर u8 *pbmul;	/* P multiplier table क्रम B data */
	स्थिर u8 *qmul;		/* Q multiplier table (क्रम both) */
	स्थिर u8 x0f = 0x0f;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/* Compute syndrome with zero क्रम the missing data pages
	   Use the dead data pages as temporary storage क्रम
	   delta p and delta q */
	dp = (u8 *)ptrs[faila];
	ptrs[faila] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks-2] = dp;
	dq = (u8 *)ptrs[failb];
	ptrs[failb] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks-1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore poपूर्णांकer table */
	ptrs[faila]   = dp;
	ptrs[failb]   = dq;
	ptrs[disks-2] = p;
	ptrs[disks-1] = q;

	/* Now, pick the proper data tables */
	pbmul = raid6_vgfmul[raid6_gfexi[failb-faila]];
	qmul  = raid6_vgfmul[raid6_gfinv[raid6_gfexp[faila] ^
		raid6_gfexp[failb]]];

	kernel_fpu_begin();

	/* ymm0 = x0f[16] */
	यंत्र अस्थिर("vpbroadcastb %0, %%ymm7" : : "m" (x0f));

	जबतक (bytes) अणु
#अगर_घोषित CONFIG_X86_64
		यंत्र अस्थिर("vmovdqa %0, %%ymm1" : : "m" (q[0]));
		यंत्र अस्थिर("vmovdqa %0, %%ymm9" : : "m" (q[32]));
		यंत्र अस्थिर("vmovdqa %0, %%ymm0" : : "m" (p[0]));
		यंत्र अस्थिर("vmovdqa %0, %%ymm8" : : "m" (p[32]));
		यंत्र अस्थिर("vpxor %0, %%ymm1, %%ymm1" : : "m" (dq[0]));
		यंत्र अस्थिर("vpxor %0, %%ymm9, %%ymm9" : : "m" (dq[32]));
		यंत्र अस्थिर("vpxor %0, %%ymm0, %%ymm0" : : "m" (dp[0]));
		यंत्र अस्थिर("vpxor %0, %%ymm8, %%ymm8" : : "m" (dp[32]));

		/*
		 * 1 = dq[0]  ^ q[0]
		 * 9 = dq[32] ^ q[32]
		 * 0 = dp[0]  ^ p[0]
		 * 8 = dp[32] ^ p[32]
		 */

		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm4" : : "m" (qmul[0]));
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm5" : : "m" (qmul[16]));

		यंत्र अस्थिर("vpsraw $4, %ymm1, %ymm3");
		यंत्र अस्थिर("vpsraw $4, %ymm9, %ymm12");
		यंत्र अस्थिर("vpand %ymm7, %ymm1, %ymm1");
		यंत्र अस्थिर("vpand %ymm7, %ymm9, %ymm9");
		यंत्र अस्थिर("vpand %ymm7, %ymm3, %ymm3");
		यंत्र अस्थिर("vpand %ymm7, %ymm12, %ymm12");
		यंत्र अस्थिर("vpshufb %ymm9, %ymm4, %ymm14");
		यंत्र अस्थिर("vpshufb %ymm1, %ymm4, %ymm4");
		यंत्र अस्थिर("vpshufb %ymm12, %ymm5, %ymm15");
		यंत्र अस्थिर("vpshufb %ymm3, %ymm5, %ymm5");
		यंत्र अस्थिर("vpxor %ymm14, %ymm15, %ymm15");
		यंत्र अस्थिर("vpxor %ymm4, %ymm5, %ymm5");

		/*
		 * 5 = qx[0]
		 * 15 = qx[32]
		 */

		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm4" : : "m" (pbmul[0]));
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm1" : : "m" (pbmul[16]));
		यंत्र अस्थिर("vpsraw $4, %ymm0, %ymm2");
		यंत्र अस्थिर("vpsraw $4, %ymm8, %ymm6");
		यंत्र अस्थिर("vpand %ymm7, %ymm0, %ymm3");
		यंत्र अस्थिर("vpand %ymm7, %ymm8, %ymm14");
		यंत्र अस्थिर("vpand %ymm7, %ymm2, %ymm2");
		यंत्र अस्थिर("vpand %ymm7, %ymm6, %ymm6");
		यंत्र अस्थिर("vpshufb %ymm14, %ymm4, %ymm12");
		यंत्र अस्थिर("vpshufb %ymm3, %ymm4, %ymm4");
		यंत्र अस्थिर("vpshufb %ymm6, %ymm1, %ymm13");
		यंत्र अस्थिर("vpshufb %ymm2, %ymm1, %ymm1");
		यंत्र अस्थिर("vpxor %ymm4, %ymm1, %ymm1");
		यंत्र अस्थिर("vpxor %ymm12, %ymm13, %ymm13");

		/*
		 * 1  = pbmul[px[0]]
		 * 13 = pbmul[px[32]]
		 */
		यंत्र अस्थिर("vpxor %ymm5, %ymm1, %ymm1");
		यंत्र अस्थिर("vpxor %ymm15, %ymm13, %ymm13");

		/*
		 * 1 = db = DQ
		 * 13 = db[32] = DQ[32]
		 */
		यंत्र अस्थिर("vmovdqa %%ymm1, %0" : "=m" (dq[0]));
		यंत्र अस्थिर("vmovdqa %%ymm13,%0" : "=m" (dq[32]));
		यंत्र अस्थिर("vpxor %ymm1, %ymm0, %ymm0");
		यंत्र अस्थिर("vpxor %ymm13, %ymm8, %ymm8");

		यंत्र अस्थिर("vmovdqa %%ymm0, %0" : "=m" (dp[0]));
		यंत्र अस्थिर("vmovdqa %%ymm8, %0" : "=m" (dp[32]));

		bytes -= 64;
		p += 64;
		q += 64;
		dp += 64;
		dq += 64;
#अन्यथा
		यंत्र अस्थिर("vmovdqa %0, %%ymm1" : : "m" (*q));
		यंत्र अस्थिर("vmovdqa %0, %%ymm0" : : "m" (*p));
		यंत्र अस्थिर("vpxor %0, %%ymm1, %%ymm1" : : "m" (*dq));
		यंत्र अस्थिर("vpxor %0, %%ymm0, %%ymm0" : : "m" (*dp));

		/* 1 = dq ^ q;  0 = dp ^ p */

		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm4" : : "m" (qmul[0]));
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm5" : : "m" (qmul[16]));

		/*
		 * 1 = dq ^ q
		 * 3 = dq ^ p >> 4
		 */
		यंत्र अस्थिर("vpsraw $4, %ymm1, %ymm3");
		यंत्र अस्थिर("vpand %ymm7, %ymm1, %ymm1");
		यंत्र अस्थिर("vpand %ymm7, %ymm3, %ymm3");
		यंत्र अस्थिर("vpshufb %ymm1, %ymm4, %ymm4");
		यंत्र अस्थिर("vpshufb %ymm3, %ymm5, %ymm5");
		यंत्र अस्थिर("vpxor %ymm4, %ymm5, %ymm5");

		/* 5 = qx */

		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm4" : : "m" (pbmul[0]));
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm1" : : "m" (pbmul[16]));

		यंत्र अस्थिर("vpsraw $4, %ymm0, %ymm2");
		यंत्र अस्थिर("vpand %ymm7, %ymm0, %ymm3");
		यंत्र अस्थिर("vpand %ymm7, %ymm2, %ymm2");
		यंत्र अस्थिर("vpshufb %ymm3, %ymm4, %ymm4");
		यंत्र अस्थिर("vpshufb %ymm2, %ymm1, %ymm1");
		यंत्र अस्थिर("vpxor %ymm4, %ymm1, %ymm1");

		/* 1 = pbmul[px] */
		यंत्र अस्थिर("vpxor %ymm5, %ymm1, %ymm1");
		/* 1 = db = DQ */
		यंत्र अस्थिर("vmovdqa %%ymm1, %0" : "=m" (dq[0]));

		यंत्र अस्थिर("vpxor %ymm1, %ymm0, %ymm0");
		यंत्र अस्थिर("vmovdqa %%ymm0, %0" : "=m" (dp[0]));

		bytes -= 32;
		p += 32;
		q += 32;
		dp += 32;
		dq += 32;
#पूर्ण_अगर
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_datap_recov_avx2(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		व्योम **ptrs)
अणु
	u8 *p, *q, *dq;
	स्थिर u8 *qmul;		/* Q multiplier table */
	स्थिर u8 x0f = 0x0f;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/* Compute syndrome with zero क्रम the missing data page
	   Use the dead data page as temporary storage क्रम delta q */
	dq = (u8 *)ptrs[faila];
	ptrs[faila] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks-1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore poपूर्णांकer table */
	ptrs[faila]   = dq;
	ptrs[disks-1] = q;

	/* Now, pick the proper data tables */
	qmul  = raid6_vgfmul[raid6_gfinv[raid6_gfexp[faila]]];

	kernel_fpu_begin();

	यंत्र अस्थिर("vpbroadcastb %0, %%ymm7" : : "m" (x0f));

	जबतक (bytes) अणु
#अगर_घोषित CONFIG_X86_64
		यंत्र अस्थिर("vmovdqa %0, %%ymm3" : : "m" (dq[0]));
		यंत्र अस्थिर("vmovdqa %0, %%ymm8" : : "m" (dq[32]));
		यंत्र अस्थिर("vpxor %0, %%ymm3, %%ymm3" : : "m" (q[0]));
		यंत्र अस्थिर("vpxor %0, %%ymm8, %%ymm8" : : "m" (q[32]));

		/*
		 * 3 = q[0] ^ dq[0]
		 * 8 = q[32] ^ dq[32]
		 */
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm0" : : "m" (qmul[0]));
		यंत्र अस्थिर("vmovapd %ymm0, %ymm13");
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm1" : : "m" (qmul[16]));
		यंत्र अस्थिर("vmovapd %ymm1, %ymm14");

		यंत्र अस्थिर("vpsraw $4, %ymm3, %ymm6");
		यंत्र अस्थिर("vpsraw $4, %ymm8, %ymm12");
		यंत्र अस्थिर("vpand %ymm7, %ymm3, %ymm3");
		यंत्र अस्थिर("vpand %ymm7, %ymm8, %ymm8");
		यंत्र अस्थिर("vpand %ymm7, %ymm6, %ymm6");
		यंत्र अस्थिर("vpand %ymm7, %ymm12, %ymm12");
		यंत्र अस्थिर("vpshufb %ymm3, %ymm0, %ymm0");
		यंत्र अस्थिर("vpshufb %ymm8, %ymm13, %ymm13");
		यंत्र अस्थिर("vpshufb %ymm6, %ymm1, %ymm1");
		यंत्र अस्थिर("vpshufb %ymm12, %ymm14, %ymm14");
		यंत्र अस्थिर("vpxor %ymm0, %ymm1, %ymm1");
		यंत्र अस्थिर("vpxor %ymm13, %ymm14, %ymm14");

		/*
		 * 1  = qmul[q[0]  ^ dq[0]]
		 * 14 = qmul[q[32] ^ dq[32]]
		 */
		यंत्र अस्थिर("vmovdqa %0, %%ymm2" : : "m" (p[0]));
		यंत्र अस्थिर("vmovdqa %0, %%ymm12" : : "m" (p[32]));
		यंत्र अस्थिर("vpxor %ymm1, %ymm2, %ymm2");
		यंत्र अस्थिर("vpxor %ymm14, %ymm12, %ymm12");

		/*
		 * 2  = p[0]  ^ qmul[q[0]  ^ dq[0]]
		 * 12 = p[32] ^ qmul[q[32] ^ dq[32]]
		 */

		यंत्र अस्थिर("vmovdqa %%ymm1, %0" : "=m" (dq[0]));
		यंत्र अस्थिर("vmovdqa %%ymm14, %0" : "=m" (dq[32]));
		यंत्र अस्थिर("vmovdqa %%ymm2, %0" : "=m" (p[0]));
		यंत्र अस्थिर("vmovdqa %%ymm12,%0" : "=m" (p[32]));

		bytes -= 64;
		p += 64;
		q += 64;
		dq += 64;
#अन्यथा
		यंत्र अस्थिर("vmovdqa %0, %%ymm3" : : "m" (dq[0]));
		यंत्र अस्थिर("vpxor %0, %%ymm3, %%ymm3" : : "m" (q[0]));

		/* 3 = q ^ dq */

		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm0" : : "m" (qmul[0]));
		यंत्र अस्थिर("vbroadcasti128 %0, %%ymm1" : : "m" (qmul[16]));

		यंत्र अस्थिर("vpsraw $4, %ymm3, %ymm6");
		यंत्र अस्थिर("vpand %ymm7, %ymm3, %ymm3");
		यंत्र अस्थिर("vpand %ymm7, %ymm6, %ymm6");
		यंत्र अस्थिर("vpshufb %ymm3, %ymm0, %ymm0");
		यंत्र अस्थिर("vpshufb %ymm6, %ymm1, %ymm1");
		यंत्र अस्थिर("vpxor %ymm0, %ymm1, %ymm1");

		/* 1 = qmul[q ^ dq] */

		यंत्र अस्थिर("vmovdqa %0, %%ymm2" : : "m" (p[0]));
		यंत्र अस्थिर("vpxor %ymm1, %ymm2, %ymm2");

		/* 2 = p ^ qmul[q ^ dq] */

		यंत्र अस्थिर("vmovdqa %%ymm1, %0" : "=m" (dq[0]));
		यंत्र अस्थिर("vmovdqa %%ymm2, %0" : "=m" (p[0]));

		bytes -= 32;
		p += 32;
		q += 32;
		dq += 32;
#पूर्ण_अगर
	पूर्ण

	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_recov_calls raid6_recov_avx2 = अणु
	.data2 = raid6_2data_recov_avx2,
	.datap = raid6_datap_recov_avx2,
	.valid = raid6_has_avx2,
#अगर_घोषित CONFIG_X86_64
	.name = "avx2x2",
#अन्यथा
	.name = "avx2x1",
#पूर्ण_अगर
	.priority = 2,
पूर्ण;
