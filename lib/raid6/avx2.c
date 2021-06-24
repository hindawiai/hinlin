<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 2012 Intel Corporation
 *   Author: Yuanhan Liu <yuanhan.liu@linux.पूर्णांकel.com>
 *
 *   Based on sse2.c: Copyright 2002 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * AVX2 implementation of RAID-6 syndrome functions
 *
 */

#समावेश <linux/raid/pq.h>
#समावेश "x86.h"

अटल स्थिर काष्ठा raid6_avx2_स्थिरants अणु
	u64 x1d[4];
पूर्ण raid6_avx2_स्थिरants __aligned(32) = अणु
	अणु 0x1d1d1d1d1d1d1d1dULL, 0x1d1d1d1d1d1d1d1dULL,
	  0x1d1d1d1d1d1d1d1dULL, 0x1d1d1d1d1d1d1d1dULL,पूर्ण,
पूर्ण;

अटल पूर्णांक raid6_have_avx2(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_AVX2) && boot_cpu_has(X86_FEATURE_AVX);
पूर्ण

/*
 * Plain AVX2 implementation
 */
अटल व्योम raid6_avx21_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("vmovdqa %0,%%ymm0" : : "m" (raid6_avx2_स्थिरants.x1d[0]));
	यंत्र अस्थिर("vpxor %ymm3,%ymm3,%ymm3");	/* Zero temp */

	क्रम (d = 0; d < bytes; d += 32) अणु
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0][d]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm2" : : "m" (dptr[z0][d]));/* P[0] */
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0-1][d]));
		यंत्र अस्थिर("vmovdqa %ymm2,%ymm4");/* Q[0] */
		यंत्र अस्थिर("vmovdqa %0,%%ymm6" : : "m" (dptr[z0-1][d]));
		क्रम (z = z0-2; z >= 0; z--) अणु
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm3,%ymm5");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm6,%ymm2,%ymm2");
			यंत्र अस्थिर("vpxor %ymm6,%ymm4,%ymm4");
			यंत्र अस्थिर("vmovdqa %0,%%ymm6" : : "m" (dptr[z][d]));
		पूर्ण
		यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm3,%ymm5");
		यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
		यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
		यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
		यंत्र अस्थिर("vpxor %ymm6,%ymm2,%ymm2");
		यंत्र अस्थिर("vpxor %ymm6,%ymm4,%ymm4");

		यंत्र अस्थिर("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("vpxor %ymm2,%ymm2,%ymm2");
		यंत्र अस्थिर("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("vpxor %ymm4,%ymm4,%ymm4");
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_avx21_xor_syndrome(पूर्णांक disks, पूर्णांक start, पूर्णांक stop,
				     माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = stop;		/* P/Q right side optimization */
	p = dptr[disks-2];	/* XOR parity */
	q = dptr[disks-1];	/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("vmovdqa %0,%%ymm0" : : "m" (raid6_avx2_स्थिरants.x1d[0]));

	क्रम (d = 0 ; d < bytes ; d += 32) अणु
		यंत्र अस्थिर("vmovdqa %0,%%ymm4" :: "m" (dptr[z0][d]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm2" : : "m" (p[d]));
		यंत्र अस्थिर("vpxor %ymm4,%ymm2,%ymm2");
		/* P/Q data pages */
		क्रम (z = z0-1 ; z >= start ; z--) अणु
			यंत्र अस्थिर("vpxor %ymm5,%ymm5,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm5,%ymm5");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vmovdqa %0,%%ymm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("vpxor %ymm5,%ymm2,%ymm2");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
		पूर्ण
		/* P/Q left side optimization */
		क्रम (z = start-1 ; z >= 0 ; z--) अणु
			यंत्र अस्थिर("vpxor %ymm5,%ymm5,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm5,%ymm5");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
		पूर्ण
		यंत्र अस्थिर("vpxor %0,%%ymm4,%%ymm4" : : "m" (q[d]));
		/* Don't use movntdq क्रम r/w memory area < cache line */
		यंत्र अस्थिर("vmovdqa %%ymm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("vmovdqa %%ymm2,%0" : "=m" (p[d]));
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_avx2x1 = अणु
	raid6_avx21_gen_syndrome,
	raid6_avx21_xor_syndrome,
	raid6_have_avx2,
	"avx2x1",
	1			/* Has cache hपूर्णांकs */
पूर्ण;

/*
 * Unrolled-by-2 AVX2 implementation
 */
अटल व्योम raid6_avx22_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("vmovdqa %0,%%ymm0" : : "m" (raid6_avx2_स्थिरants.x1d[0]));
	यंत्र अस्थिर("vpxor %ymm1,%ymm1,%ymm1"); /* Zero temp */

	/* We unअगरormly assume a single prefetch covers at least 32 bytes */
	क्रम (d = 0; d < bytes; d += 64) अणु
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0][d]));
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0][d+32]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm2" : : "m" (dptr[z0][d]));/* P[0] */
		यंत्र अस्थिर("vmovdqa %0,%%ymm3" : : "m" (dptr[z0][d+32]));/* P[1] */
		यंत्र अस्थिर("vmovdqa %ymm2,%ymm4"); /* Q[0] */
		यंत्र अस्थिर("vmovdqa %ymm3,%ymm6"); /* Q[1] */
		क्रम (z = z0-1; z >= 0; z--) अणु
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d+32]));
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm1,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm6,%ymm1,%ymm7");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpaddb %ymm6,%ymm6,%ymm6");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpand %ymm0,%ymm7,%ymm7");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vmovdqa %0,%%ymm5" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm7" : : "m" (dptr[z][d+32]));
			यंत्र अस्थिर("vpxor %ymm5,%ymm2,%ymm2");
			यंत्र अस्थिर("vpxor %ymm7,%ymm3,%ymm3");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
		पूर्ण
		यंत्र अस्थिर("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("vmovntdq %%ymm3,%0" : "=m" (p[d+32]));
		यंत्र अस्थिर("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("vmovntdq %%ymm6,%0" : "=m" (q[d+32]));
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_avx22_xor_syndrome(पूर्णांक disks, पूर्णांक start, पूर्णांक stop,
				     माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = stop;		/* P/Q right side optimization */
	p = dptr[disks-2];	/* XOR parity */
	q = dptr[disks-1];	/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("vmovdqa %0,%%ymm0" : : "m" (raid6_avx2_स्थिरants.x1d[0]));

	क्रम (d = 0 ; d < bytes ; d += 64) अणु
		यंत्र अस्थिर("vmovdqa %0,%%ymm4" :: "m" (dptr[z0][d]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm6" :: "m" (dptr[z0][d+32]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm2" : : "m" (p[d]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm3" : : "m" (p[d+32]));
		यंत्र अस्थिर("vpxor %ymm4,%ymm2,%ymm2");
		यंत्र अस्थिर("vpxor %ymm6,%ymm3,%ymm3");
		/* P/Q data pages */
		क्रम (z = z0-1 ; z >= start ; z--) अणु
			यंत्र अस्थिर("vpxor %ymm5,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm7,%ymm7,%ymm7");
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm5,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm6,%ymm7,%ymm7");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpaddb %ymm6,%ymm6,%ymm6");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpand %ymm0,%ymm7,%ymm7");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vmovdqa %0,%%ymm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm7"
				     :: "m" (dptr[z][d+32]));
			यंत्र अस्थिर("vpxor %ymm5,%ymm2,%ymm2");
			यंत्र अस्थिर("vpxor %ymm7,%ymm3,%ymm3");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
		पूर्ण
		/* P/Q left side optimization */
		क्रम (z = start-1 ; z >= 0 ; z--) अणु
			यंत्र अस्थिर("vpxor %ymm5,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm7,%ymm7,%ymm7");
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm5,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm6,%ymm7,%ymm7");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpaddb %ymm6,%ymm6,%ymm6");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpand %ymm0,%ymm7,%ymm7");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
		पूर्ण
		यंत्र अस्थिर("vpxor %0,%%ymm4,%%ymm4" : : "m" (q[d]));
		यंत्र अस्थिर("vpxor %0,%%ymm6,%%ymm6" : : "m" (q[d+32]));
		/* Don't use movntdq क्रम r/w memory area < cache line */
		यंत्र अस्थिर("vmovdqa %%ymm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("vmovdqa %%ymm6,%0" : "=m" (q[d+32]));
		यंत्र अस्थिर("vmovdqa %%ymm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("vmovdqa %%ymm3,%0" : "=m" (p[d+32]));
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_avx2x2 = अणु
	raid6_avx22_gen_syndrome,
	raid6_avx22_xor_syndrome,
	raid6_have_avx2,
	"avx2x2",
	1			/* Has cache hपूर्णांकs */
पूर्ण;

#अगर_घोषित CONFIG_X86_64

/*
 * Unrolled-by-4 AVX2 implementation
 */
अटल व्योम raid6_avx24_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("vmovdqa %0,%%ymm0" : : "m" (raid6_avx2_स्थिरants.x1d[0]));
	यंत्र अस्थिर("vpxor %ymm1,%ymm1,%ymm1");	/* Zero temp */
	यंत्र अस्थिर("vpxor %ymm2,%ymm2,%ymm2");	/* P[0] */
	यंत्र अस्थिर("vpxor %ymm3,%ymm3,%ymm3");	/* P[1] */
	यंत्र अस्थिर("vpxor %ymm4,%ymm4,%ymm4");	/* Q[0] */
	यंत्र अस्थिर("vpxor %ymm6,%ymm6,%ymm6");	/* Q[1] */
	यंत्र अस्थिर("vpxor %ymm10,%ymm10,%ymm10");	/* P[2] */
	यंत्र अस्थिर("vpxor %ymm11,%ymm11,%ymm11");	/* P[3] */
	यंत्र अस्थिर("vpxor %ymm12,%ymm12,%ymm12");	/* Q[2] */
	यंत्र अस्थिर("vpxor %ymm14,%ymm14,%ymm14");	/* Q[3] */

	क्रम (d = 0; d < bytes; d += 128) अणु
		क्रम (z = z0; z >= 0; z--) अणु
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d+32]));
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d+64]));
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d+96]));
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm1,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm6,%ymm1,%ymm7");
			यंत्र अस्थिर("vpcmpgtb %ymm12,%ymm1,%ymm13");
			यंत्र अस्थिर("vpcmpgtb %ymm14,%ymm1,%ymm15");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpaddb %ymm6,%ymm6,%ymm6");
			यंत्र अस्थिर("vpaddb %ymm12,%ymm12,%ymm12");
			यंत्र अस्थिर("vpaddb %ymm14,%ymm14,%ymm14");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpand %ymm0,%ymm7,%ymm7");
			यंत्र अस्थिर("vpand %ymm0,%ymm13,%ymm13");
			यंत्र अस्थिर("vpand %ymm0,%ymm15,%ymm15");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vpxor %ymm13,%ymm12,%ymm12");
			यंत्र अस्थिर("vpxor %ymm15,%ymm14,%ymm14");
			यंत्र अस्थिर("vmovdqa %0,%%ymm5" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm7" : : "m" (dptr[z][d+32]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm13" : : "m" (dptr[z][d+64]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm15" : : "m" (dptr[z][d+96]));
			यंत्र अस्थिर("vpxor %ymm5,%ymm2,%ymm2");
			यंत्र अस्थिर("vpxor %ymm7,%ymm3,%ymm3");
			यंत्र अस्थिर("vpxor %ymm13,%ymm10,%ymm10");
			यंत्र अस्थिर("vpxor %ymm15,%ymm11,%ymm11");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vpxor %ymm13,%ymm12,%ymm12");
			यंत्र अस्थिर("vpxor %ymm15,%ymm14,%ymm14");
		पूर्ण
		यंत्र अस्थिर("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("vpxor %ymm2,%ymm2,%ymm2");
		यंत्र अस्थिर("vmovntdq %%ymm3,%0" : "=m" (p[d+32]));
		यंत्र अस्थिर("vpxor %ymm3,%ymm3,%ymm3");
		यंत्र अस्थिर("vmovntdq %%ymm10,%0" : "=m" (p[d+64]));
		यंत्र अस्थिर("vpxor %ymm10,%ymm10,%ymm10");
		यंत्र अस्थिर("vmovntdq %%ymm11,%0" : "=m" (p[d+96]));
		यंत्र अस्थिर("vpxor %ymm11,%ymm11,%ymm11");
		यंत्र अस्थिर("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("vpxor %ymm4,%ymm4,%ymm4");
		यंत्र अस्थिर("vmovntdq %%ymm6,%0" : "=m" (q[d+32]));
		यंत्र अस्थिर("vpxor %ymm6,%ymm6,%ymm6");
		यंत्र अस्थिर("vmovntdq %%ymm12,%0" : "=m" (q[d+64]));
		यंत्र अस्थिर("vpxor %ymm12,%ymm12,%ymm12");
		यंत्र अस्थिर("vmovntdq %%ymm14,%0" : "=m" (q[d+96]));
		यंत्र अस्थिर("vpxor %ymm14,%ymm14,%ymm14");
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_avx24_xor_syndrome(पूर्णांक disks, पूर्णांक start, पूर्णांक stop,
				     माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = stop;		/* P/Q right side optimization */
	p = dptr[disks-2];	/* XOR parity */
	q = dptr[disks-1];	/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("vmovdqa %0,%%ymm0" :: "m" (raid6_avx2_स्थिरants.x1d[0]));

	क्रम (d = 0 ; d < bytes ; d += 128) अणु
		यंत्र अस्थिर("vmovdqa %0,%%ymm4" :: "m" (dptr[z0][d]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm6" :: "m" (dptr[z0][d+32]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm12" :: "m" (dptr[z0][d+64]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm14" :: "m" (dptr[z0][d+96]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm2" : : "m" (p[d]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm3" : : "m" (p[d+32]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm10" : : "m" (p[d+64]));
		यंत्र अस्थिर("vmovdqa %0,%%ymm11" : : "m" (p[d+96]));
		यंत्र अस्थिर("vpxor %ymm4,%ymm2,%ymm2");
		यंत्र अस्थिर("vpxor %ymm6,%ymm3,%ymm3");
		यंत्र अस्थिर("vpxor %ymm12,%ymm10,%ymm10");
		यंत्र अस्थिर("vpxor %ymm14,%ymm11,%ymm11");
		/* P/Q data pages */
		क्रम (z = z0-1 ; z >= start ; z--) अणु
			यंत्र अस्थिर("prefetchnta %0" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("prefetchnta %0" :: "m" (dptr[z][d+64]));
			यंत्र अस्थिर("vpxor %ymm5,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm7,%ymm7,%ymm7");
			यंत्र अस्थिर("vpxor %ymm13,%ymm13,%ymm13");
			यंत्र अस्थिर("vpxor %ymm15,%ymm15,%ymm15");
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm5,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm6,%ymm7,%ymm7");
			यंत्र अस्थिर("vpcmpgtb %ymm12,%ymm13,%ymm13");
			यंत्र अस्थिर("vpcmpgtb %ymm14,%ymm15,%ymm15");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpaddb %ymm6,%ymm6,%ymm6");
			यंत्र अस्थिर("vpaddb %ymm12,%ymm12,%ymm12");
			यंत्र अस्थिर("vpaddb %ymm14,%ymm14,%ymm14");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpand %ymm0,%ymm7,%ymm7");
			यंत्र अस्थिर("vpand %ymm0,%ymm13,%ymm13");
			यंत्र अस्थिर("vpand %ymm0,%ymm15,%ymm15");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vpxor %ymm13,%ymm12,%ymm12");
			यंत्र अस्थिर("vpxor %ymm15,%ymm14,%ymm14");
			यंत्र अस्थिर("vmovdqa %0,%%ymm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm7"
				     :: "m" (dptr[z][d+32]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm13"
				     :: "m" (dptr[z][d+64]));
			यंत्र अस्थिर("vmovdqa %0,%%ymm15"
				     :: "m" (dptr[z][d+96]));
			यंत्र अस्थिर("vpxor %ymm5,%ymm2,%ymm2");
			यंत्र अस्थिर("vpxor %ymm7,%ymm3,%ymm3");
			यंत्र अस्थिर("vpxor %ymm13,%ymm10,%ymm10");
			यंत्र अस्थिर("vpxor %ymm15,%ymm11,%ymm11");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vpxor %ymm13,%ymm12,%ymm12");
			यंत्र अस्थिर("vpxor %ymm15,%ymm14,%ymm14");
		पूर्ण
		यंत्र अस्थिर("prefetchnta %0" :: "m" (q[d]));
		यंत्र अस्थिर("prefetchnta %0" :: "m" (q[d+64]));
		/* P/Q left side optimization */
		क्रम (z = start-1 ; z >= 0 ; z--) अणु
			यंत्र अस्थिर("vpxor %ymm5,%ymm5,%ymm5");
			यंत्र अस्थिर("vpxor %ymm7,%ymm7,%ymm7");
			यंत्र अस्थिर("vpxor %ymm13,%ymm13,%ymm13");
			यंत्र अस्थिर("vpxor %ymm15,%ymm15,%ymm15");
			यंत्र अस्थिर("vpcmpgtb %ymm4,%ymm5,%ymm5");
			यंत्र अस्थिर("vpcmpgtb %ymm6,%ymm7,%ymm7");
			यंत्र अस्थिर("vpcmpgtb %ymm12,%ymm13,%ymm13");
			यंत्र अस्थिर("vpcmpgtb %ymm14,%ymm15,%ymm15");
			यंत्र अस्थिर("vpaddb %ymm4,%ymm4,%ymm4");
			यंत्र अस्थिर("vpaddb %ymm6,%ymm6,%ymm6");
			यंत्र अस्थिर("vpaddb %ymm12,%ymm12,%ymm12");
			यंत्र अस्थिर("vpaddb %ymm14,%ymm14,%ymm14");
			यंत्र अस्थिर("vpand %ymm0,%ymm5,%ymm5");
			यंत्र अस्थिर("vpand %ymm0,%ymm7,%ymm7");
			यंत्र अस्थिर("vpand %ymm0,%ymm13,%ymm13");
			यंत्र अस्थिर("vpand %ymm0,%ymm15,%ymm15");
			यंत्र अस्थिर("vpxor %ymm5,%ymm4,%ymm4");
			यंत्र अस्थिर("vpxor %ymm7,%ymm6,%ymm6");
			यंत्र अस्थिर("vpxor %ymm13,%ymm12,%ymm12");
			यंत्र अस्थिर("vpxor %ymm15,%ymm14,%ymm14");
		पूर्ण
		यंत्र अस्थिर("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("vmovntdq %%ymm3,%0" : "=m" (p[d+32]));
		यंत्र अस्थिर("vmovntdq %%ymm10,%0" : "=m" (p[d+64]));
		यंत्र अस्थिर("vmovntdq %%ymm11,%0" : "=m" (p[d+96]));
		यंत्र अस्थिर("vpxor %0,%%ymm4,%%ymm4" : : "m" (q[d]));
		यंत्र अस्थिर("vpxor %0,%%ymm6,%%ymm6" : : "m" (q[d+32]));
		यंत्र अस्थिर("vpxor %0,%%ymm12,%%ymm12" : : "m" (q[d+64]));
		यंत्र अस्थिर("vpxor %0,%%ymm14,%%ymm14" : : "m" (q[d+96]));
		यंत्र अस्थिर("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("vmovntdq %%ymm6,%0" : "=m" (q[d+32]));
		यंत्र अस्थिर("vmovntdq %%ymm12,%0" : "=m" (q[d+64]));
		यंत्र अस्थिर("vmovntdq %%ymm14,%0" : "=m" (q[d+96]));
	पूर्ण
	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_avx2x4 = अणु
	raid6_avx24_gen_syndrome,
	raid6_avx24_xor_syndrome,
	raid6_have_avx2,
	"avx2x4",
	1			/* Has cache hपूर्णांकs */
पूर्ण;
#पूर्ण_अगर
