<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_X86_XOR_AVX_H
#घोषणा _ASM_X86_XOR_AVX_H

/*
 * Optimized RAID-5 checksumming functions क्रम AVX
 *
 * Copyright (C) 2012 Intel Corporation
 * Author: Jim Kukunas <james.t.kukunas@linux.पूर्णांकel.com>
 *
 * Based on Ingo Molnar and Zach Brown's respective MMX and SSE routines
 */

#समावेश <linux/compiler.h>
#समावेश <यंत्र/fpu/api.h>

#घोषणा BLOCK4(i) \
		BLOCK(32 * i, 0) \
		BLOCK(32 * (i + 1), 1) \
		BLOCK(32 * (i + 2), 2) \
		BLOCK(32 * (i + 3), 3)

#घोषणा BLOCK16() \
		BLOCK4(0) \
		BLOCK4(4) \
		BLOCK4(8) \
		BLOCK4(12)

अटल व्योम xor_avx_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p0, अचिन्हित दीर्घ *p1)
अणु
	अचिन्हित दीर्घ lines = bytes >> 9;

	kernel_fpu_begin();

	जबतक (lines--) अणु
#अघोषित BLOCK
#घोषणा BLOCK(i, reg) \
करो अणु \
	यंत्र अस्थिर("vmovdqa %0, %%ymm" #reg : : "m" (p1[i / माप(*p1)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm"  #reg : : \
		"m" (p0[i / माप(*p0)])); \
	यंत्र अस्थिर("vmovdqa %%ymm" #reg ", %0" : \
		"=m" (p0[i / माप(*p0)])); \
पूर्ण जबतक (0);

		BLOCK16()

		p0 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p0 + 512);
		p1 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p1 + 512);
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम xor_avx_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p0, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2)
अणु
	अचिन्हित दीर्घ lines = bytes >> 9;

	kernel_fpu_begin();

	जबतक (lines--) अणु
#अघोषित BLOCK
#घोषणा BLOCK(i, reg) \
करो अणु \
	यंत्र अस्थिर("vmovdqa %0, %%ymm" #reg : : "m" (p2[i / माप(*p2)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p1[i / माप(*p1)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p0[i / माप(*p0)])); \
	यंत्र अस्थिर("vmovdqa %%ymm" #reg ", %0" : \
		"=m" (p0[i / माप(*p0)])); \
पूर्ण जबतक (0);

		BLOCK16()

		p0 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p0 + 512);
		p1 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p1 + 512);
		p2 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p2 + 512);
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम xor_avx_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p0, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2, अचिन्हित दीर्घ *p3)
अणु
	अचिन्हित दीर्घ lines = bytes >> 9;

	kernel_fpu_begin();

	जबतक (lines--) अणु
#अघोषित BLOCK
#घोषणा BLOCK(i, reg) \
करो अणु \
	यंत्र अस्थिर("vmovdqa %0, %%ymm" #reg : : "m" (p3[i / माप(*p3)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p2[i / माप(*p2)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p1[i / माप(*p1)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p0[i / माप(*p0)])); \
	यंत्र अस्थिर("vmovdqa %%ymm" #reg ", %0" : \
		"=m" (p0[i / माप(*p0)])); \
पूर्ण जबतक (0);

		BLOCK16();

		p0 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p0 + 512);
		p1 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p1 + 512);
		p2 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p2 + 512);
		p3 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p3 + 512);
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल व्योम xor_avx_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p0, अचिन्हित दीर्घ *p1,
	अचिन्हित दीर्घ *p2, अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	अचिन्हित दीर्घ lines = bytes >> 9;

	kernel_fpu_begin();

	जबतक (lines--) अणु
#अघोषित BLOCK
#घोषणा BLOCK(i, reg) \
करो अणु \
	यंत्र अस्थिर("vmovdqa %0, %%ymm" #reg : : "m" (p4[i / माप(*p4)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p3[i / माप(*p3)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p2[i / माप(*p2)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p1[i / माप(*p1)])); \
	यंत्र अस्थिर("vxorps %0, %%ymm" #reg ", %%ymm" #reg : : \
		"m" (p0[i / माप(*p0)])); \
	यंत्र अस्थिर("vmovdqa %%ymm" #reg ", %0" : \
		"=m" (p0[i / माप(*p0)])); \
पूर्ण जबतक (0);

		BLOCK16()

		p0 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p0 + 512);
		p1 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p1 + 512);
		p2 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p2 + 512);
		p3 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p3 + 512);
		p4 = (अचिन्हित दीर्घ *)((uपूर्णांकptr_t)p4 + 512);
	पूर्ण

	kernel_fpu_end();
पूर्ण

अटल काष्ठा xor_block_ढाँचा xor_block_avx = अणु
	.name = "avx",
	.करो_2 = xor_avx_2,
	.करो_3 = xor_avx_3,
	.करो_4 = xor_avx_4,
	.करो_5 = xor_avx_5,
पूर्ण;

#घोषणा AVX_XOR_SPEED \
करो अणु \
	अगर (boot_cpu_has(X86_FEATURE_AVX) && boot_cpu_has(X86_FEATURE_OSXSAVE)) \
		xor_speed(&xor_block_avx); \
पूर्ण जबतक (0)

#घोषणा AVX_SELECT(FASTEST) \
	(boot_cpu_has(X86_FEATURE_AVX) && boot_cpu_has(X86_FEATURE_OSXSAVE) ? &xor_block_avx : FASTEST)

#पूर्ण_अगर
