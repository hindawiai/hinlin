<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2002 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * raid6/sse2.c
 *
 * SSE-2 implementation of RAID-6 syndrome functions
 *
 */

#समावेश <linux/raid/pq.h>
#समावेश "x86.h"

अटल स्थिर काष्ठा raid6_sse_स्थिरants अणु
	u64 x1d[2];
पूर्ण raid6_sse_स्थिरants  __attribute__((aligned(16))) = अणु
	अणु 0x1d1d1d1d1d1d1d1dULL, 0x1d1d1d1d1d1d1d1dULL पूर्ण,
पूर्ण;

अटल पूर्णांक raid6_have_sse2(व्योम)
अणु
	/* Not really boot_cpu but "all_cpus" */
	वापस boot_cpu_has(X86_FEATURE_MMX) &&
		boot_cpu_has(X86_FEATURE_FXSR) &&
		boot_cpu_has(X86_FEATURE_XMM) &&
		boot_cpu_has(X86_FEATURE_XMM2);
पूर्ण

/*
 * Plain SSE2 implementation
 */
अटल व्योम raid6_sse21_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movdqa %0,%%xmm0" : : "m" (raid6_sse_स्थिरants.x1d[0]));
	यंत्र अस्थिर("pxor %xmm5,%xmm5");	/* Zero temp */

	क्रम ( d = 0 ; d < bytes ; d += 16 ) अणु
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0][d]));
		यंत्र अस्थिर("movdqa %0,%%xmm2" : : "m" (dptr[z0][d])); /* P[0] */
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0-1][d]));
		यंत्र अस्थिर("movdqa %xmm2,%xmm4"); /* Q[0] */
		यंत्र अस्थिर("movdqa %0,%%xmm6" : : "m" (dptr[z0-1][d]));
		क्रम ( z = z0-2 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm6,%xmm2");
			यंत्र अस्थिर("pxor %xmm6,%xmm4");
			यंत्र अस्थिर("movdqa %0,%%xmm6" : : "m" (dptr[z][d]));
		पूर्ण
		यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
		यंत्र अस्थिर("paddb %xmm4,%xmm4");
		यंत्र अस्थिर("pand %xmm0,%xmm5");
		यंत्र अस्थिर("pxor %xmm5,%xmm4");
		यंत्र अस्थिर("pxor %xmm5,%xmm5");
		यंत्र अस्थिर("pxor %xmm6,%xmm2");
		यंत्र अस्थिर("pxor %xmm6,%xmm4");

		यंत्र अस्थिर("movntdq %%xmm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("pxor %xmm2,%xmm2");
		यंत्र अस्थिर("movntdq %%xmm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("pxor %xmm4,%xmm4");
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण


अटल व्योम raid6_sse21_xor_syndrome(पूर्णांक disks, पूर्णांक start, पूर्णांक stop,
				     माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = stop;		/* P/Q right side optimization */
	p = dptr[disks-2];	/* XOR parity */
	q = dptr[disks-1];	/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movdqa %0,%%xmm0" : : "m" (raid6_sse_स्थिरants.x1d[0]));

	क्रम ( d = 0 ; d < bytes ; d += 16 ) अणु
		यंत्र अस्थिर("movdqa %0,%%xmm4" :: "m" (dptr[z0][d]));
		यंत्र अस्थिर("movdqa %0,%%xmm2" : : "m" (p[d]));
		यंत्र अस्थिर("pxor %xmm4,%xmm2");
		/* P/Q data pages */
		क्रम ( z = z0-1 ; z >= start ; z-- ) अणु
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("movdqa %0,%%xmm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("pxor %xmm5,%xmm2");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
		पूर्ण
		/* P/Q left side optimization */
		क्रम ( z = start-1 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
		पूर्ण
		यंत्र अस्थिर("pxor %0,%%xmm4" : : "m" (q[d]));
		/* Don't use movntdq क्रम r/w memory area < cache line */
		यंत्र अस्थिर("movdqa %%xmm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("movdqa %%xmm2,%0" : "=m" (p[d]));
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_sse2x1 = अणु
	raid6_sse21_gen_syndrome,
	raid6_sse21_xor_syndrome,
	raid6_have_sse2,
	"sse2x1",
	1			/* Has cache hपूर्णांकs */
पूर्ण;

/*
 * Unrolled-by-2 SSE2 implementation
 */
अटल व्योम raid6_sse22_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movdqa %0,%%xmm0" : : "m" (raid6_sse_स्थिरants.x1d[0]));
	यंत्र अस्थिर("pxor %xmm5,%xmm5"); /* Zero temp */
	यंत्र अस्थिर("pxor %xmm7,%xmm7"); /* Zero temp */

	/* We unअगरormly assume a single prefetch covers at least 32 bytes */
	क्रम ( d = 0 ; d < bytes ; d += 32 ) अणु
		यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z0][d]));
		यंत्र अस्थिर("movdqa %0,%%xmm2" : : "m" (dptr[z0][d]));    /* P[0] */
		यंत्र अस्थिर("movdqa %0,%%xmm3" : : "m" (dptr[z0][d+16])); /* P[1] */
		यंत्र अस्थिर("movdqa %xmm2,%xmm4"); /* Q[0] */
		यंत्र अस्थिर("movdqa %xmm3,%xmm6"); /* Q[1] */
		क्रम ( z = z0-1 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("prefetchnta %0" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm6,%xmm7");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("paddb %xmm6,%xmm6");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pand %xmm0,%xmm7");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("movdqa %0,%%xmm5" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("movdqa %0,%%xmm7" : : "m" (dptr[z][d+16]));
			यंत्र अस्थिर("pxor %xmm5,%xmm2");
			यंत्र अस्थिर("pxor %xmm7,%xmm3");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm7,%xmm7");
		पूर्ण
		यंत्र अस्थिर("movntdq %%xmm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("movntdq %%xmm3,%0" : "=m" (p[d+16]));
		यंत्र अस्थिर("movntdq %%xmm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("movntdq %%xmm6,%0" : "=m" (q[d+16]));
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_sse22_xor_syndrome(पूर्णांक disks, पूर्णांक start, पूर्णांक stop,
				     माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = stop;		/* P/Q right side optimization */
	p = dptr[disks-2];	/* XOR parity */
	q = dptr[disks-1];	/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movdqa %0,%%xmm0" : : "m" (raid6_sse_स्थिरants.x1d[0]));

	क्रम ( d = 0 ; d < bytes ; d += 32 ) अणु
		यंत्र अस्थिर("movdqa %0,%%xmm4" :: "m" (dptr[z0][d]));
		यंत्र अस्थिर("movdqa %0,%%xmm6" :: "m" (dptr[z0][d+16]));
		यंत्र अस्थिर("movdqa %0,%%xmm2" : : "m" (p[d]));
		यंत्र अस्थिर("movdqa %0,%%xmm3" : : "m" (p[d+16]));
		यंत्र अस्थिर("pxor %xmm4,%xmm2");
		यंत्र अस्थिर("pxor %xmm6,%xmm3");
		/* P/Q data pages */
		क्रम ( z = z0-1 ; z >= start ; z-- ) अणु
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm7,%xmm7");
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm6,%xmm7");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("paddb %xmm6,%xmm6");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pand %xmm0,%xmm7");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("movdqa %0,%%xmm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("movdqa %0,%%xmm7" :: "m" (dptr[z][d+16]));
			यंत्र अस्थिर("pxor %xmm5,%xmm2");
			यंत्र अस्थिर("pxor %xmm7,%xmm3");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
		पूर्ण
		/* P/Q left side optimization */
		क्रम ( z = start-1 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm7,%xmm7");
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm6,%xmm7");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("paddb %xmm6,%xmm6");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pand %xmm0,%xmm7");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
		पूर्ण
		यंत्र अस्थिर("pxor %0,%%xmm4" : : "m" (q[d]));
		यंत्र अस्थिर("pxor %0,%%xmm6" : : "m" (q[d+16]));
		/* Don't use movntdq क्रम r/w memory area < cache line */
		यंत्र अस्थिर("movdqa %%xmm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("movdqa %%xmm6,%0" : "=m" (q[d+16]));
		यंत्र अस्थिर("movdqa %%xmm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("movdqa %%xmm3,%0" : "=m" (p[d+16]));
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_sse2x2 = अणु
	raid6_sse22_gen_syndrome,
	raid6_sse22_xor_syndrome,
	raid6_have_sse2,
	"sse2x2",
	1			/* Has cache hपूर्णांकs */
पूर्ण;

#अगर_घोषित CONFIG_X86_64

/*
 * Unrolled-by-4 SSE2 implementation
 */
अटल व्योम raid6_sse24_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movdqa %0,%%xmm0" :: "m" (raid6_sse_स्थिरants.x1d[0]));
	यंत्र अस्थिर("pxor %xmm2,%xmm2");	/* P[0] */
	यंत्र अस्थिर("pxor %xmm3,%xmm3");	/* P[1] */
	यंत्र अस्थिर("pxor %xmm4,%xmm4"); 	/* Q[0] */
	यंत्र अस्थिर("pxor %xmm5,%xmm5");	/* Zero temp */
	यंत्र अस्थिर("pxor %xmm6,%xmm6"); 	/* Q[1] */
	यंत्र अस्थिर("pxor %xmm7,%xmm7"); 	/* Zero temp */
	यंत्र अस्थिर("pxor %xmm10,%xmm10");	/* P[2] */
	यंत्र अस्थिर("pxor %xmm11,%xmm11");	/* P[3] */
	यंत्र अस्थिर("pxor %xmm12,%xmm12"); 	/* Q[2] */
	यंत्र अस्थिर("pxor %xmm13,%xmm13");	/* Zero temp */
	यंत्र अस्थिर("pxor %xmm14,%xmm14"); 	/* Q[3] */
	यंत्र अस्थिर("pxor %xmm15,%xmm15"); 	/* Zero temp */

	क्रम ( d = 0 ; d < bytes ; d += 64 ) अणु
		क्रम ( z = z0 ; z >= 0 ; z-- ) अणु
			/* The second prefetch seems to improve perक्रमmance... */
			यंत्र अस्थिर("prefetchnta %0" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("prefetchnta %0" :: "m" (dptr[z][d+32]));
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm6,%xmm7");
			यंत्र अस्थिर("pcmpgtb %xmm12,%xmm13");
			यंत्र अस्थिर("pcmpgtb %xmm14,%xmm15");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("paddb %xmm6,%xmm6");
			यंत्र अस्थिर("paddb %xmm12,%xmm12");
			यंत्र अस्थिर("paddb %xmm14,%xmm14");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pand %xmm0,%xmm7");
			यंत्र अस्थिर("pand %xmm0,%xmm13");
			यंत्र अस्थिर("pand %xmm0,%xmm15");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("pxor %xmm13,%xmm12");
			यंत्र अस्थिर("pxor %xmm15,%xmm14");
			यंत्र अस्थिर("movdqa %0,%%xmm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("movdqa %0,%%xmm7" :: "m" (dptr[z][d+16]));
			यंत्र अस्थिर("movdqa %0,%%xmm13" :: "m" (dptr[z][d+32]));
			यंत्र अस्थिर("movdqa %0,%%xmm15" :: "m" (dptr[z][d+48]));
			यंत्र अस्थिर("pxor %xmm5,%xmm2");
			यंत्र अस्थिर("pxor %xmm7,%xmm3");
			यंत्र अस्थिर("pxor %xmm13,%xmm10");
			यंत्र अस्थिर("pxor %xmm15,%xmm11");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("pxor %xmm13,%xmm12");
			यंत्र अस्थिर("pxor %xmm15,%xmm14");
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm7,%xmm7");
			यंत्र अस्थिर("pxor %xmm13,%xmm13");
			यंत्र अस्थिर("pxor %xmm15,%xmm15");
		पूर्ण
		यंत्र अस्थिर("movntdq %%xmm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("pxor %xmm2,%xmm2");
		यंत्र अस्थिर("movntdq %%xmm3,%0" : "=m" (p[d+16]));
		यंत्र अस्थिर("pxor %xmm3,%xmm3");
		यंत्र अस्थिर("movntdq %%xmm10,%0" : "=m" (p[d+32]));
		यंत्र अस्थिर("pxor %xmm10,%xmm10");
		यंत्र अस्थिर("movntdq %%xmm11,%0" : "=m" (p[d+48]));
		यंत्र अस्थिर("pxor %xmm11,%xmm11");
		यंत्र अस्थिर("movntdq %%xmm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("pxor %xmm4,%xmm4");
		यंत्र अस्थिर("movntdq %%xmm6,%0" : "=m" (q[d+16]));
		यंत्र अस्थिर("pxor %xmm6,%xmm6");
		यंत्र अस्थिर("movntdq %%xmm12,%0" : "=m" (q[d+32]));
		यंत्र अस्थिर("pxor %xmm12,%xmm12");
		यंत्र अस्थिर("movntdq %%xmm14,%0" : "=m" (q[d+48]));
		यंत्र अस्थिर("pxor %xmm14,%xmm14");
	पूर्ण

	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण

अटल व्योम raid6_sse24_xor_syndrome(पूर्णांक disks, पूर्णांक start, पूर्णांक stop,
				     माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = stop;		/* P/Q right side optimization */
	p = dptr[disks-2];	/* XOR parity */
	q = dptr[disks-1];	/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movdqa %0,%%xmm0" :: "m" (raid6_sse_स्थिरants.x1d[0]));

	क्रम ( d = 0 ; d < bytes ; d += 64 ) अणु
		यंत्र अस्थिर("movdqa %0,%%xmm4" :: "m" (dptr[z0][d]));
		यंत्र अस्थिर("movdqa %0,%%xmm6" :: "m" (dptr[z0][d+16]));
		यंत्र अस्थिर("movdqa %0,%%xmm12" :: "m" (dptr[z0][d+32]));
		यंत्र अस्थिर("movdqa %0,%%xmm14" :: "m" (dptr[z0][d+48]));
		यंत्र अस्थिर("movdqa %0,%%xmm2" : : "m" (p[d]));
		यंत्र अस्थिर("movdqa %0,%%xmm3" : : "m" (p[d+16]));
		यंत्र अस्थिर("movdqa %0,%%xmm10" : : "m" (p[d+32]));
		यंत्र अस्थिर("movdqa %0,%%xmm11" : : "m" (p[d+48]));
		यंत्र अस्थिर("pxor %xmm4,%xmm2");
		यंत्र अस्थिर("pxor %xmm6,%xmm3");
		यंत्र अस्थिर("pxor %xmm12,%xmm10");
		यंत्र अस्थिर("pxor %xmm14,%xmm11");
		/* P/Q data pages */
		क्रम ( z = z0-1 ; z >= start ; z-- ) अणु
			यंत्र अस्थिर("prefetchnta %0" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("prefetchnta %0" :: "m" (dptr[z][d+32]));
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm7,%xmm7");
			यंत्र अस्थिर("pxor %xmm13,%xmm13");
			यंत्र अस्थिर("pxor %xmm15,%xmm15");
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm6,%xmm7");
			यंत्र अस्थिर("pcmpgtb %xmm12,%xmm13");
			यंत्र अस्थिर("pcmpgtb %xmm14,%xmm15");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("paddb %xmm6,%xmm6");
			यंत्र अस्थिर("paddb %xmm12,%xmm12");
			यंत्र अस्थिर("paddb %xmm14,%xmm14");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pand %xmm0,%xmm7");
			यंत्र अस्थिर("pand %xmm0,%xmm13");
			यंत्र अस्थिर("pand %xmm0,%xmm15");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("pxor %xmm13,%xmm12");
			यंत्र अस्थिर("pxor %xmm15,%xmm14");
			यंत्र अस्थिर("movdqa %0,%%xmm5" :: "m" (dptr[z][d]));
			यंत्र अस्थिर("movdqa %0,%%xmm7" :: "m" (dptr[z][d+16]));
			यंत्र अस्थिर("movdqa %0,%%xmm13" :: "m" (dptr[z][d+32]));
			यंत्र अस्थिर("movdqa %0,%%xmm15" :: "m" (dptr[z][d+48]));
			यंत्र अस्थिर("pxor %xmm5,%xmm2");
			यंत्र अस्थिर("pxor %xmm7,%xmm3");
			यंत्र अस्थिर("pxor %xmm13,%xmm10");
			यंत्र अस्थिर("pxor %xmm15,%xmm11");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("pxor %xmm13,%xmm12");
			यंत्र अस्थिर("pxor %xmm15,%xmm14");
		पूर्ण
		यंत्र अस्थिर("prefetchnta %0" :: "m" (q[d]));
		यंत्र अस्थिर("prefetchnta %0" :: "m" (q[d+32]));
		/* P/Q left side optimization */
		क्रम ( z = start-1 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("pxor %xmm5,%xmm5");
			यंत्र अस्थिर("pxor %xmm7,%xmm7");
			यंत्र अस्थिर("pxor %xmm13,%xmm13");
			यंत्र अस्थिर("pxor %xmm15,%xmm15");
			यंत्र अस्थिर("pcmpgtb %xmm4,%xmm5");
			यंत्र अस्थिर("pcmpgtb %xmm6,%xmm7");
			यंत्र अस्थिर("pcmpgtb %xmm12,%xmm13");
			यंत्र अस्थिर("pcmpgtb %xmm14,%xmm15");
			यंत्र अस्थिर("paddb %xmm4,%xmm4");
			यंत्र अस्थिर("paddb %xmm6,%xmm6");
			यंत्र अस्थिर("paddb %xmm12,%xmm12");
			यंत्र अस्थिर("paddb %xmm14,%xmm14");
			यंत्र अस्थिर("pand %xmm0,%xmm5");
			यंत्र अस्थिर("pand %xmm0,%xmm7");
			यंत्र अस्थिर("pand %xmm0,%xmm13");
			यंत्र अस्थिर("pand %xmm0,%xmm15");
			यंत्र अस्थिर("pxor %xmm5,%xmm4");
			यंत्र अस्थिर("pxor %xmm7,%xmm6");
			यंत्र अस्थिर("pxor %xmm13,%xmm12");
			यंत्र अस्थिर("pxor %xmm15,%xmm14");
		पूर्ण
		यंत्र अस्थिर("movntdq %%xmm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("movntdq %%xmm3,%0" : "=m" (p[d+16]));
		यंत्र अस्थिर("movntdq %%xmm10,%0" : "=m" (p[d+32]));
		यंत्र अस्थिर("movntdq %%xmm11,%0" : "=m" (p[d+48]));
		यंत्र अस्थिर("pxor %0,%%xmm4" : : "m" (q[d]));
		यंत्र अस्थिर("pxor %0,%%xmm6" : : "m" (q[d+16]));
		यंत्र अस्थिर("pxor %0,%%xmm12" : : "m" (q[d+32]));
		यंत्र अस्थिर("pxor %0,%%xmm14" : : "m" (q[d+48]));
		यंत्र अस्थिर("movntdq %%xmm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("movntdq %%xmm6,%0" : "=m" (q[d+16]));
		यंत्र अस्थिर("movntdq %%xmm12,%0" : "=m" (q[d+32]));
		यंत्र अस्थिर("movntdq %%xmm14,%0" : "=m" (q[d+48]));
	पूर्ण
	यंत्र अस्थिर("sfence" : : : "memory");
	kernel_fpu_end();
पूर्ण


स्थिर काष्ठा raid6_calls raid6_sse2x4 = अणु
	raid6_sse24_gen_syndrome,
	raid6_sse24_xor_syndrome,
	raid6_have_sse2,
	"sse2x4",
	1			/* Has cache hपूर्णांकs */
पूर्ण;

#पूर्ण_अगर /* CONFIG_X86_64 */
