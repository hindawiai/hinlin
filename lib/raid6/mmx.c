<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2002 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * raid6/mmx.c
 *
 * MMX implementation of RAID-6 syndrome functions
 */

#अगर_घोषित CONFIG_X86_32

#समावेश <linux/raid/pq.h>
#समावेश "x86.h"

/* Shared with raid6/sse1.c */
स्थिर काष्ठा raid6_mmx_स्थिरants अणु
	u64 x1d;
पूर्ण raid6_mmx_स्थिरants = अणु
	0x1d1d1d1d1d1d1d1dULL,
पूर्ण;

अटल पूर्णांक raid6_have_mmx(व्योम)
अणु
	/* Not really "boot_cpu" but "all_cpus" */
	वापस boot_cpu_has(X86_FEATURE_MMX);
पूर्ण

/*
 * Plain MMX implementation
 */
अटल व्योम raid6_mmx1_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movq %0,%%mm0" : : "m" (raid6_mmx_स्थिरants.x1d));
	यंत्र अस्थिर("pxor %mm5,%mm5");	/* Zero temp */

	क्रम ( d = 0 ; d < bytes ; d += 8 ) अणु
		यंत्र अस्थिर("movq %0,%%mm2" : : "m" (dptr[z0][d])); /* P[0] */
		यंत्र अस्थिर("movq %mm2,%mm4");	/* Q[0] */
		क्रम ( z = z0-1 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("movq %0,%%mm6" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("pcmpgtb %mm4,%mm5");
			यंत्र अस्थिर("paddb %mm4,%mm4");
			यंत्र अस्थिर("pand %mm0,%mm5");
			यंत्र अस्थिर("pxor %mm5,%mm4");
			यंत्र अस्थिर("pxor %mm5,%mm5");
			यंत्र अस्थिर("pxor %mm6,%mm2");
			यंत्र अस्थिर("pxor %mm6,%mm4");
		पूर्ण
		यंत्र अस्थिर("movq %%mm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("pxor %mm2,%mm2");
		यंत्र अस्थिर("movq %%mm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("pxor %mm4,%mm4");
	पूर्ण

	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_mmxx1 = अणु
	raid6_mmx1_gen_syndrome,
	शून्य,			/* XOR not yet implemented */
	raid6_have_mmx,
	"mmxx1",
	0
पूर्ण;

/*
 * Unrolled-by-2 MMX implementation
 */
अटल व्योम raid6_mmx2_gen_syndrome(पूर्णांक disks, माप_प्रकार bytes, व्योम **ptrs)
अणु
	u8 **dptr = (u8 **)ptrs;
	u8 *p, *q;
	पूर्णांक d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptr[z0+1];		/* XOR parity */
	q = dptr[z0+2];		/* RS syndrome */

	kernel_fpu_begin();

	यंत्र अस्थिर("movq %0,%%mm0" : : "m" (raid6_mmx_स्थिरants.x1d));
	यंत्र अस्थिर("pxor %mm5,%mm5");	/* Zero temp */
	यंत्र अस्थिर("pxor %mm7,%mm7"); /* Zero temp */

	क्रम ( d = 0 ; d < bytes ; d += 16 ) अणु
		यंत्र अस्थिर("movq %0,%%mm2" : : "m" (dptr[z0][d])); /* P[0] */
		यंत्र अस्थिर("movq %0,%%mm3" : : "m" (dptr[z0][d+8]));
		यंत्र अस्थिर("movq %mm2,%mm4"); /* Q[0] */
		यंत्र अस्थिर("movq %mm3,%mm6"); /* Q[1] */
		क्रम ( z = z0-1 ; z >= 0 ; z-- ) अणु
			यंत्र अस्थिर("pcmpgtb %mm4,%mm5");
			यंत्र अस्थिर("pcmpgtb %mm6,%mm7");
			यंत्र अस्थिर("paddb %mm4,%mm4");
			यंत्र अस्थिर("paddb %mm6,%mm6");
			यंत्र अस्थिर("pand %mm0,%mm5");
			यंत्र अस्थिर("pand %mm0,%mm7");
			यंत्र अस्थिर("pxor %mm5,%mm4");
			यंत्र अस्थिर("pxor %mm7,%mm6");
			यंत्र अस्थिर("movq %0,%%mm5" : : "m" (dptr[z][d]));
			यंत्र अस्थिर("movq %0,%%mm7" : : "m" (dptr[z][d+8]));
			यंत्र अस्थिर("pxor %mm5,%mm2");
			यंत्र अस्थिर("pxor %mm7,%mm3");
			यंत्र अस्थिर("pxor %mm5,%mm4");
			यंत्र अस्थिर("pxor %mm7,%mm6");
			यंत्र अस्थिर("pxor %mm5,%mm5");
			यंत्र अस्थिर("pxor %mm7,%mm7");
		पूर्ण
		यंत्र अस्थिर("movq %%mm2,%0" : "=m" (p[d]));
		यंत्र अस्थिर("movq %%mm3,%0" : "=m" (p[d+8]));
		यंत्र अस्थिर("movq %%mm4,%0" : "=m" (q[d]));
		यंत्र अस्थिर("movq %%mm6,%0" : "=m" (q[d+8]));
	पूर्ण

	kernel_fpu_end();
पूर्ण

स्थिर काष्ठा raid6_calls raid6_mmxx2 = अणु
	raid6_mmx2_gen_syndrome,
	शून्य,			/* XOR not yet implemented */
	raid6_have_mmx,
	"mmxx2",
	0
पूर्ण;

#पूर्ण_अगर
