<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Intel Corporation
 *
 * Author: Gayatri Kammela <gayatri.kammela@पूर्णांकel.com>
 * Author: Megha Dey <megha.dey@linux.पूर्णांकel.com>
 */

#अगर_घोषित CONFIG_AS_AVX512

#समावेश <linux/raid/pq.h>
#समावेश "x86.h"

अटल पूर्णांक raid6_has_avx512(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_AVX2) &&
		boot_cpu_has(X86_FEATURE_AVX) &&
		boot_cpu_has(X86_FEATURE_AVX512F) &&
		boot_cpu_has(X86_FEATURE_AVX512BW) &&
		boot_cpu_has(X86_FEATURE_AVX512VL) &&
		boot_cpu_has(X86_FEATURE_AVX512DQ);
पूर्ण

अटल व्योम raid6_2data_recov_avx512(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
				     पूर्णांक failb, व्योम **ptrs)
अणु
	u8 *p, *q, *dp, *dq;
	स्थिर u8 *pbmul;	/* P multiplier table क्रम B data */
	स्थिर u8 *qmul;		/* Q multiplier table (क्रम both) */
	स्थिर u8 x0f = 0x0f;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/*
	 * Compute syndrome with zero क्रम the missing data pages
	 * Use the dead data pages as temporary storage क्रम
	 * delta p and delta q
	 */

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

	/* zmm0 = x0f[16] */
	यंत्र अस्थिर("vpbroadcastb %0, %%zmm7" : : "m" (x0f));

	जबतक (bytes) अणु
#अगर_घोषित CONFIG_X86_64
		यंत्र अस्थिर("vmovdqa64 %0, %%zmm1\n\t"
			     "vmovdqa64 %1, %%zmm9\n\t"
			     "vmovdqa64 %2, %%zmm0\n\t"
			     "vmovdqa64 %3, %%zmm8\n\t"
			     "vpxorq %4, %%zmm1, %%zmm1\n\t"
			     "vpxorq %5, %%zmm9, %%zmm9\n\t"
			     "vpxorq %6, %%zmm0, %%zmm0\n\t"
			     "vpxorq %7, %%zmm8, %%zmm8"
			     :
			     : "m" (q[0]), "m" (q[64]), "m" (p[0]),
			       "m" (p[64]), "m" (dq[0]), "m" (dq[64]),
			       "m" (dp[0]), "m" (dp[64]));

		/*
		 * 1 = dq[0]  ^ q[0]
		 * 9 = dq[64] ^ q[64]
		 * 0 = dp[0]  ^ p[0]
		 * 8 = dp[64] ^ p[64]
		 */

		यंत्र अस्थिर("vbroadcasti64x2 %0, %%zmm4\n\t"
			     "vbroadcasti64x2 %1, %%zmm5"
			     :
			     : "m" (qmul[0]), "m" (qmul[16]));

		यंत्र अस्थिर("vpsraw $4, %%zmm1, %%zmm3\n\t"
			     "vpsraw $4, %%zmm9, %%zmm12\n\t"
			     "vpandq %%zmm7, %%zmm1, %%zmm1\n\t"
			     "vpandq %%zmm7, %%zmm9, %%zmm9\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm12, %%zmm12\n\t"
			     "vpshufb %%zmm9, %%zmm4, %%zmm14\n\t"
			     "vpshufb %%zmm1, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm12, %%zmm5, %%zmm15\n\t"
			     "vpshufb %%zmm3, %%zmm5, %%zmm5\n\t"
			     "vpxorq %%zmm14, %%zmm15, %%zmm15\n\t"
			     "vpxorq %%zmm4, %%zmm5, %%zmm5"
			     :
			     : );

		/*
		 * 5 = qx[0]
		 * 15 = qx[64]
		 */

		यंत्र अस्थिर("vbroadcasti64x2 %0, %%zmm4\n\t"
			     "vbroadcasti64x2 %1, %%zmm1\n\t"
			     "vpsraw $4, %%zmm0, %%zmm2\n\t"
			     "vpsraw $4, %%zmm8, %%zmm6\n\t"
			     "vpandq %%zmm7, %%zmm0, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm8, %%zmm14\n\t"
			     "vpandq %%zmm7, %%zmm2, %%zmm2\n\t"
			     "vpandq %%zmm7, %%zmm6, %%zmm6\n\t"
			     "vpshufb %%zmm14, %%zmm4, %%zmm12\n\t"
			     "vpshufb %%zmm3, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm6, %%zmm1, %%zmm13\n\t"
			     "vpshufb %%zmm2, %%zmm1, %%zmm1\n\t"
			     "vpxorq %%zmm4, %%zmm1, %%zmm1\n\t"
			     "vpxorq %%zmm12, %%zmm13, %%zmm13"
			     :
			     : "m" (pbmul[0]), "m" (pbmul[16]));

		/*
		 * 1  = pbmul[px[0]]
		 * 13 = pbmul[px[64]]
		 */
		यंत्र अस्थिर("vpxorq %%zmm5, %%zmm1, %%zmm1\n\t"
			     "vpxorq %%zmm15, %%zmm13, %%zmm13"
			     :
			     : );

		/*
		 * 1 = db = DQ
		 * 13 = db[64] = DQ[64]
		 */
		यंत्र अस्थिर("vmovdqa64 %%zmm1, %0\n\t"
			     "vmovdqa64 %%zmm13,%1\n\t"
			     "vpxorq %%zmm1, %%zmm0, %%zmm0\n\t"
			     "vpxorq %%zmm13, %%zmm8, %%zmm8"
			     :
			     : "m" (dq[0]), "m" (dq[64]));

		यंत्र अस्थिर("vmovdqa64 %%zmm0, %0\n\t"
			     "vmovdqa64 %%zmm8, %1"
			     :
			     : "m" (dp[0]), "m" (dp[64]));

		bytes -= 128;
		p += 128;
		q += 128;
		dp += 128;
		dq += 128;
#अन्यथा
		यंत्र अस्थिर("vmovdqa64 %0, %%zmm1\n\t"
			     "vmovdqa64 %1, %%zmm0\n\t"
			     "vpxorq %2, %%zmm1, %%zmm1\n\t"
			     "vpxorq %3, %%zmm0, %%zmm0"
			     :
			     : "m" (*q), "m" (*p), "m"(*dq), "m" (*dp));

		/* 1 = dq ^ q;  0 = dp ^ p */

		यंत्र अस्थिर("vbroadcasti64x2 %0, %%zmm4\n\t"
			     "vbroadcasti64x2 %1, %%zmm5"
			     :
			     : "m" (qmul[0]), "m" (qmul[16]));

		/*
		 * 1 = dq ^ q
		 * 3 = dq ^ p >> 4
		 */
		यंत्र अस्थिर("vpsraw $4, %%zmm1, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm1, %%zmm1\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpshufb %%zmm1, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm3, %%zmm5, %%zmm5\n\t"
			     "vpxorq %%zmm4, %%zmm5, %%zmm5"
			     :
			     : );

		/* 5 = qx */

		यंत्र अस्थिर("vbroadcasti64x2 %0, %%zmm4\n\t"
			     "vbroadcasti64x2 %1, %%zmm1"
			     :
			     : "m" (pbmul[0]), "m" (pbmul[16]));

		यंत्र अस्थिर("vpsraw $4, %%zmm0, %%zmm2\n\t"
			     "vpandq %%zmm7, %%zmm0, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm2, %%zmm2\n\t"
			     "vpshufb %%zmm3, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm2, %%zmm1, %%zmm1\n\t"
			     "vpxorq %%zmm4, %%zmm1, %%zmm1"
			     :
			     : );

		/* 1 = pbmul[px] */
		यंत्र अस्थिर("vpxorq %%zmm5, %%zmm1, %%zmm1\n\t"
			     /* 1 = db = DQ */
			     "vmovdqa64 %%zmm1, %0\n\t"
			     :
			     : "m" (dq[0]));

		यंत्र अस्थिर("vpxorq %%zmm1, %%zmm0, %%zmm0\n\t"
			     "vmovdqa64 %%zmm0, %0"
			     :
			     : "m" (dp[0]));

		bytes -= 64;
		p += 64;
		q += 64;
		dp += 64;
		dq += 64;
#पूर्ण_अगर
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_datap_recov_avx512(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
				     व्योम **ptrs)
अणु
	u8 *p, *q, *dq;
	स्थिर u8 *qmul;		/* Q multiplier table */
	स्थिर u8 x0f = 0x0f;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/*
	 * Compute syndrome with zero क्रम the missing data page
	 * Use the dead data page as temporary storage क्रम delta q
	 */

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

	यंत्र अस्थिर("vpbroadcastb %0, %%zmm7" : : "m" (x0f));

	जबतक (bytes) अणु
#अगर_घोषित CONFIG_X86_64
		यंत्र अस्थिर("vmovdqa64 %0, %%zmm3\n\t"
			     "vmovdqa64 %1, %%zmm8\n\t"
			     "vpxorq %2, %%zmm3, %%zmm3\n\t"
			     "vpxorq %3, %%zmm8, %%zmm8"
			     :
			     : "m" (dq[0]), "m" (dq[64]), "m" (q[0]),
			       "m" (q[64]));

		/*
		 * 3 = q[0] ^ dq[0]
		 * 8 = q[64] ^ dq[64]
		 */
		यंत्र अस्थिर("vbroadcasti64x2 %0, %%zmm0\n\t"
			     "vmovapd %%zmm0, %%zmm13\n\t"
			     "vbroadcasti64x2 %1, %%zmm1\n\t"
			     "vmovapd %%zmm1, %%zmm14"
			     :
			     : "m" (qmul[0]), "m" (qmul[16]));

		यंत्र अस्थिर("vpsraw $4, %%zmm3, %%zmm6\n\t"
			     "vpsraw $4, %%zmm8, %%zmm12\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm8, %%zmm8\n\t"
			     "vpandq %%zmm7, %%zmm6, %%zmm6\n\t"
			     "vpandq %%zmm7, %%zmm12, %%zmm12\n\t"
			     "vpshufb %%zmm3, %%zmm0, %%zmm0\n\t"
			     "vpshufb %%zmm8, %%zmm13, %%zmm13\n\t"
			     "vpshufb %%zmm6, %%zmm1, %%zmm1\n\t"
			     "vpshufb %%zmm12, %%zmm14, %%zmm14\n\t"
			     "vpxorq %%zmm0, %%zmm1, %%zmm1\n\t"
			     "vpxorq %%zmm13, %%zmm14, %%zmm14"
			     :
			     : );

		/*
		 * 1  = qmul[q[0]  ^ dq[0]]
		 * 14 = qmul[q[64] ^ dq[64]]
		 */
		यंत्र अस्थिर("vmovdqa64 %0, %%zmm2\n\t"
			     "vmovdqa64 %1, %%zmm12\n\t"
			     "vpxorq %%zmm1, %%zmm2, %%zmm2\n\t"
			     "vpxorq %%zmm14, %%zmm12, %%zmm12"
			     :
			     : "m" (p[0]), "m" (p[64]));

		/*
		 * 2  = p[0]  ^ qmul[q[0]  ^ dq[0]]
		 * 12 = p[64] ^ qmul[q[64] ^ dq[64]]
		 */

		यंत्र अस्थिर("vmovdqa64 %%zmm1, %0\n\t"
			     "vmovdqa64 %%zmm14, %1\n\t"
			     "vmovdqa64 %%zmm2, %2\n\t"
			     "vmovdqa64 %%zmm12,%3"
			     :
			     : "m" (dq[0]), "m" (dq[64]), "m" (p[0]),
			       "m" (p[64]));

		bytes -= 128;
		p += 128;
		q += 128;
		dq += 128;
#अन्यथा
		यंत्र अस्थिर("vmovdqa64 %0, %%zmm3\n\t"
			     "vpxorq %1, %%zmm3, %%zmm3"
			     :
			     : "m" (dq[0]), "m" (q[0]));

		/* 3 = q ^ dq */

		यंत्र अस्थिर("vbroadcasti64x2 %0, %%zmm0\n\t"
			     "vbroadcasti64x2 %1, %%zmm1"
			     :
			     : "m" (qmul[0]), "m" (qmul[16]));

		यंत्र अस्थिर("vpsraw $4, %%zmm3, %%zmm6\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm6, %%zmm6\n\t"
			     "vpshufb %%zmm3, %%zmm0, %%zmm0\n\t"
			     "vpshufb %%zmm6, %%zmm1, %%zmm1\n\t"
			     "vpxorq %%zmm0, %%zmm1, %%zmm1"
			     :
			     : );

		/* 1 = qmul[q ^ dq] */

		यंत्र अस्थिर("vmovdqa64 %0, %%zmm2\n\t"
			     "vpxorq %%zmm1, %%zmm2, %%zmm2"
			     :
			     : "m" (p[0]));

		/* 2 = p ^ qmul[q ^ dq] */

		यंत्र अस्थिर("vmovdqa64 %%zmm1, %0\n\t"
			     "vmovdqa64 %%zmm2, %1"
			     :
			     : "m" (dq[0]), "m" (p[0]));

		bytes -= 64;
		p += 64;
		q += 64;
		dq += 64;
#पूर्ण_अगर
	पूर्ण

	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_recov_calls raid6_recov_avx512 = अणु
	.data2 = raid6_2data_recov_avx512,
	.datap = raid6_datap_recov_avx512,
	.valid = raid6_has_avx512,
#अगर_घोषित CONFIG_X86_64
	.name = "avx512x2",
#अन्यथा
	.name = "avx512x1",
#पूर्ण_अगर
	.priority = 3,
पूर्ण;

#अन्यथा
#warning "your version of binutils lacks AVX512 support"
#पूर्ण_अगर
