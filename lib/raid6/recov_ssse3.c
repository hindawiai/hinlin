<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Intel Corporation
 */

#समावेश <linux/raid/pq.h>
#समावेश "x86.h"

अटल पूर्णांक raid6_has_ssse3(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_XMM) &&
		boot_cpu_has(X86_FEATURE_XMM2) &&
		boot_cpu_has(X86_FEATURE_SSSE3);
पूर्ण

अटल व्योम raid6_2data_recov_ssse3(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		पूर्णांक failb, व्योम **ptrs)
अणु
	u8 *p, *q, *dp, *dq;
	स्थिर u8 *pbmul;	/* P multiplier table क्रम B data */
	स्थिर u8 *qmul;		/* Q multiplier table (क्रम both) */
	अटल स्थिर u8 __aligned(16) x0f[16] = अणु
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0fपूर्ण;

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

	यंत्र अस्थिर("movdqa %0,%%xmm7" : : "m" (x0f[0]));

#अगर_घोषित CONFIG_X86_64
	यंत्र अस्थिर("movdqa %0,%%xmm6" : : "m" (qmul[0]));
	यंत्र अस्थिर("movdqa %0,%%xmm14" : : "m" (pbmul[0]));
	यंत्र अस्थिर("movdqa %0,%%xmm15" : : "m" (pbmul[16]));
#पूर्ण_अगर

	/* Now करो it... */
	जबतक (bytes) अणु
#अगर_घोषित CONFIG_X86_64
		/* xmm6, xmm14, xmm15 */

		यंत्र अस्थिर("movdqa %0,%%xmm1" : : "m" (q[0]));
		यंत्र अस्थिर("movdqa %0,%%xmm9" : : "m" (q[16]));
		यंत्र अस्थिर("movdqa %0,%%xmm0" : : "m" (p[0]));
		यंत्र अस्थिर("movdqa %0,%%xmm8" : : "m" (p[16]));
		यंत्र अस्थिर("pxor   %0,%%xmm1" : : "m" (dq[0]));
		यंत्र अस्थिर("pxor   %0,%%xmm9" : : "m" (dq[16]));
		यंत्र अस्थिर("pxor   %0,%%xmm0" : : "m" (dp[0]));
		यंत्र अस्थिर("pxor   %0,%%xmm8" : : "m" (dp[16]));

		/* xmm0/8 = px */

		यंत्र अस्थिर("movdqa %xmm6,%xmm4");
		यंत्र अस्थिर("movdqa %0,%%xmm5" : : "m" (qmul[16]));
		यंत्र अस्थिर("movdqa %xmm6,%xmm12");
		यंत्र अस्थिर("movdqa %xmm5,%xmm13");
		यंत्र अस्थिर("movdqa %xmm1,%xmm3");
		यंत्र अस्थिर("movdqa %xmm9,%xmm11");
		यंत्र अस्थिर("movdqa %xmm0,%xmm2"); /* xmm2/10 = px */
		यंत्र अस्थिर("movdqa %xmm8,%xmm10");
		यंत्र अस्थिर("psraw  $4,%xmm1");
		यंत्र अस्थिर("psraw  $4,%xmm9");
		यंत्र अस्थिर("pand   %xmm7,%xmm3");
		यंत्र अस्थिर("pand   %xmm7,%xmm11");
		यंत्र अस्थिर("pand   %xmm7,%xmm1");
		यंत्र अस्थिर("pand   %xmm7,%xmm9");
		यंत्र अस्थिर("pshufb %xmm3,%xmm4");
		यंत्र अस्थिर("pshufb %xmm11,%xmm12");
		यंत्र अस्थिर("pshufb %xmm1,%xmm5");
		यंत्र अस्थिर("pshufb %xmm9,%xmm13");
		यंत्र अस्थिर("pxor   %xmm4,%xmm5");
		यंत्र अस्थिर("pxor   %xmm12,%xmm13");

		/* xmm5/13 = qx */

		यंत्र अस्थिर("movdqa %xmm14,%xmm4");
		यंत्र अस्थिर("movdqa %xmm15,%xmm1");
		यंत्र अस्थिर("movdqa %xmm14,%xmm12");
		यंत्र अस्थिर("movdqa %xmm15,%xmm9");
		यंत्र अस्थिर("movdqa %xmm2,%xmm3");
		यंत्र अस्थिर("movdqa %xmm10,%xmm11");
		यंत्र अस्थिर("psraw  $4,%xmm2");
		यंत्र अस्थिर("psraw  $4,%xmm10");
		यंत्र अस्थिर("pand   %xmm7,%xmm3");
		यंत्र अस्थिर("pand   %xmm7,%xmm11");
		यंत्र अस्थिर("pand   %xmm7,%xmm2");
		यंत्र अस्थिर("pand   %xmm7,%xmm10");
		यंत्र अस्थिर("pshufb %xmm3,%xmm4");
		यंत्र अस्थिर("pshufb %xmm11,%xmm12");
		यंत्र अस्थिर("pshufb %xmm2,%xmm1");
		यंत्र अस्थिर("pshufb %xmm10,%xmm9");
		यंत्र अस्थिर("pxor   %xmm4,%xmm1");
		यंत्र अस्थिर("pxor   %xmm12,%xmm9");

		/* xmm1/9 = pbmul[px] */
		यंत्र अस्थिर("pxor   %xmm5,%xmm1");
		यंत्र अस्थिर("pxor   %xmm13,%xmm9");
		/* xmm1/9 = db = DQ */
		यंत्र अस्थिर("movdqa %%xmm1,%0" : "=m" (dq[0]));
		यंत्र अस्थिर("movdqa %%xmm9,%0" : "=m" (dq[16]));

		यंत्र अस्थिर("pxor   %xmm1,%xmm0");
		यंत्र अस्थिर("pxor   %xmm9,%xmm8");
		यंत्र अस्थिर("movdqa %%xmm0,%0" : "=m" (dp[0]));
		यंत्र अस्थिर("movdqa %%xmm8,%0" : "=m" (dp[16]));

		bytes -= 32;
		p += 32;
		q += 32;
		dp += 32;
		dq += 32;
#अन्यथा
		यंत्र अस्थिर("movdqa %0,%%xmm1" : : "m" (*q));
		यंत्र अस्थिर("movdqa %0,%%xmm0" : : "m" (*p));
		यंत्र अस्थिर("pxor   %0,%%xmm1" : : "m" (*dq));
		यंत्र अस्थिर("pxor   %0,%%xmm0" : : "m" (*dp));

		/* 1 = dq ^ q
		 * 0 = dp ^ p
		 */
		यंत्र अस्थिर("movdqa %0,%%xmm4" : : "m" (qmul[0]));
		यंत्र अस्थिर("movdqa %0,%%xmm5" : : "m" (qmul[16]));

		यंत्र अस्थिर("movdqa %xmm1,%xmm3");
		यंत्र अस्थिर("psraw  $4,%xmm1");
		यंत्र अस्थिर("pand   %xmm7,%xmm3");
		यंत्र अस्थिर("pand   %xmm7,%xmm1");
		यंत्र अस्थिर("pshufb %xmm3,%xmm4");
		यंत्र अस्थिर("pshufb %xmm1,%xmm5");
		यंत्र अस्थिर("pxor   %xmm4,%xmm5");

		यंत्र अस्थिर("movdqa %xmm0,%xmm2"); /* xmm2 = px */

		/* xmm5 = qx */

		यंत्र अस्थिर("movdqa %0,%%xmm4" : : "m" (pbmul[0]));
		यंत्र अस्थिर("movdqa %0,%%xmm1" : : "m" (pbmul[16]));
		यंत्र अस्थिर("movdqa %xmm2,%xmm3");
		यंत्र अस्थिर("psraw  $4,%xmm2");
		यंत्र अस्थिर("pand   %xmm7,%xmm3");
		यंत्र अस्थिर("pand   %xmm7,%xmm2");
		यंत्र अस्थिर("pshufb %xmm3,%xmm4");
		यंत्र अस्थिर("pshufb %xmm2,%xmm1");
		यंत्र अस्थिर("pxor   %xmm4,%xmm1");

		/* xmm1 = pbmul[px] */
		यंत्र अस्थिर("pxor   %xmm5,%xmm1");
		/* xmm1 = db = DQ */
		यंत्र अस्थिर("movdqa %%xmm1,%0" : "=m" (*dq));

		यंत्र अस्थिर("pxor   %xmm1,%xmm0");
		यंत्र अस्थिर("movdqa %%xmm0,%0" : "=m" (*dp));

		bytes -= 16;
		p += 16;
		q += 16;
		dp += 16;
		dq += 16;
#पूर्ण_अगर
	पूर्ण

	kernel_fpu_end();
पूर्ण


अटल व्योम raid6_datap_recov_ssse3(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		व्योम **ptrs)
अणु
	u8 *p, *q, *dq;
	स्थिर u8 *qmul;		/* Q multiplier table */
	अटल स्थिर u8 __aligned(16) x0f[16] = अणु
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0fपूर्ण;

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

	यंत्र अस्थिर("movdqa %0, %%xmm7" : : "m" (x0f[0]));

	जबतक (bytes) अणु
#अगर_घोषित CONFIG_X86_64
		यंत्र अस्थिर("movdqa %0, %%xmm3" : : "m" (dq[0]));
		यंत्र अस्थिर("movdqa %0, %%xmm4" : : "m" (dq[16]));
		यंत्र अस्थिर("pxor %0, %%xmm3" : : "m" (q[0]));
		यंत्र अस्थिर("movdqa %0, %%xmm0" : : "m" (qmul[0]));

		/* xmm3 = q[0] ^ dq[0] */

		यंत्र अस्थिर("pxor %0, %%xmm4" : : "m" (q[16]));
		यंत्र अस्थिर("movdqa %0, %%xmm1" : : "m" (qmul[16]));

		/* xmm4 = q[16] ^ dq[16] */

		यंत्र अस्थिर("movdqa %xmm3, %xmm6");
		यंत्र अस्थिर("movdqa %xmm4, %xmm8");

		/* xmm4 = xmm8 = q[16] ^ dq[16] */

		यंत्र अस्थिर("psraw $4, %xmm3");
		यंत्र अस्थिर("pand %xmm7, %xmm6");
		यंत्र अस्थिर("pand %xmm7, %xmm3");
		यंत्र अस्थिर("pshufb %xmm6, %xmm0");
		यंत्र अस्थिर("pshufb %xmm3, %xmm1");
		यंत्र अस्थिर("movdqa %0, %%xmm10" : : "m" (qmul[0]));
		यंत्र अस्थिर("pxor %xmm0, %xmm1");
		यंत्र अस्थिर("movdqa %0, %%xmm11" : : "m" (qmul[16]));

		/* xmm1 = qmul[q[0] ^ dq[0]] */

		यंत्र अस्थिर("psraw $4, %xmm4");
		यंत्र अस्थिर("pand %xmm7, %xmm8");
		यंत्र अस्थिर("pand %xmm7, %xmm4");
		यंत्र अस्थिर("pshufb %xmm8, %xmm10");
		यंत्र अस्थिर("pshufb %xmm4, %xmm11");
		यंत्र अस्थिर("movdqa %0, %%xmm2" : : "m" (p[0]));
		यंत्र अस्थिर("pxor %xmm10, %xmm11");
		यंत्र अस्थिर("movdqa %0, %%xmm12" : : "m" (p[16]));

		/* xmm11 = qmul[q[16] ^ dq[16]] */

		यंत्र अस्थिर("pxor %xmm1, %xmm2");

		/* xmm2 = p[0] ^ qmul[q[0] ^ dq[0]] */

		यंत्र अस्थिर("pxor %xmm11, %xmm12");

		/* xmm12 = p[16] ^ qmul[q[16] ^ dq[16]] */

		यंत्र अस्थिर("movdqa %%xmm1, %0" : "=m" (dq[0]));
		यंत्र अस्थिर("movdqa %%xmm11, %0" : "=m" (dq[16]));

		यंत्र अस्थिर("movdqa %%xmm2, %0" : "=m" (p[0]));
		यंत्र अस्थिर("movdqa %%xmm12, %0" : "=m" (p[16]));

		bytes -= 32;
		p += 32;
		q += 32;
		dq += 32;

#अन्यथा
		यंत्र अस्थिर("movdqa %0, %%xmm3" : : "m" (dq[0]));
		यंत्र अस्थिर("movdqa %0, %%xmm0" : : "m" (qmul[0]));
		यंत्र अस्थिर("pxor %0, %%xmm3" : : "m" (q[0]));
		यंत्र अस्थिर("movdqa %0, %%xmm1" : : "m" (qmul[16]));

		/* xmm3 = *q ^ *dq */

		यंत्र अस्थिर("movdqa %xmm3, %xmm6");
		यंत्र अस्थिर("movdqa %0, %%xmm2" : : "m" (p[0]));
		यंत्र अस्थिर("psraw $4, %xmm3");
		यंत्र अस्थिर("pand %xmm7, %xmm6");
		यंत्र अस्थिर("pand %xmm7, %xmm3");
		यंत्र अस्थिर("pshufb %xmm6, %xmm0");
		यंत्र अस्थिर("pshufb %xmm3, %xmm1");
		यंत्र अस्थिर("pxor %xmm0, %xmm1");

		/* xmm1 = qmul[*q ^ *dq */

		यंत्र अस्थिर("pxor %xmm1, %xmm2");

		/* xmm2 = *p ^ qmul[*q ^ *dq] */

		यंत्र अस्थिर("movdqa %%xmm1, %0" : "=m" (dq[0]));
		यंत्र अस्थिर("movdqa %%xmm2, %0" : "=m" (p[0]));

		bytes -= 16;
		p += 16;
		q += 16;
		dq += 16;
#पूर्ण_अगर
	पूर्ण

	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_recov_calls raid6_recov_ssse3 = अणु
	.data2 = raid6_2data_recov_ssse3,
	.datap = raid6_datap_recov_ssse3,
	.valid = raid6_has_ssse3,
#अगर_घोषित CONFIG_X86_64
	.name = "ssse3x2",
#अन्यथा
	.name = "ssse3x1",
#पूर्ण_अगर
	.priority = 1,
पूर्ण;
