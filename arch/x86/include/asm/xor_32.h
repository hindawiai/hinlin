<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_XOR_32_H
#घोषणा _ASM_X86_XOR_32_H

/*
 * Optimized RAID-5 checksumming functions क्रम MMX.
 */

/*
 * High-speed RAID5 checksumming functions utilizing MMX inकाष्ठाions.
 * Copyright (C) 1998 Ingo Molnar.
 */

#घोषणा LD(x, y)	"       movq   8*("#x")(%1), %%mm"#y"   ;\n"
#घोषणा ST(x, y)	"       movq %%mm"#y",   8*("#x")(%1)   ;\n"
#घोषणा XO1(x, y)	"       pxor   8*("#x")(%2), %%mm"#y"   ;\n"
#घोषणा XO2(x, y)	"       pxor   8*("#x")(%3), %%mm"#y"   ;\n"
#घोषणा XO3(x, y)	"       pxor   8*("#x")(%4), %%mm"#y"   ;\n"
#घोषणा XO4(x, y)	"       pxor   8*("#x")(%5), %%mm"#y"   ;\n"

#समावेश <यंत्र/fpu/api.h>

अटल व्योम
xor_pII_mmx_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	अचिन्हित दीर्घ lines = bytes >> 7;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)				\
	LD(i, 0)				\
		LD(i + 1, 1)			\
			LD(i + 2, 2)		\
				LD(i + 3, 3)	\
	XO1(i, 0)				\
	ST(i, 0)				\
		XO1(i+1, 1)			\
		ST(i+1, 1)			\
			XO1(i + 2, 2)		\
			ST(i + 2, 2)		\
				XO1(i + 3, 3)	\
				ST(i + 3, 3)

	" .align 32			;\n"
	" 1:                            ;\n"

	BLOCK(0)
	BLOCK(4)
	BLOCK(8)
	BLOCK(12)

	"       addl $128, %1         ;\n"
	"       addl $128, %2         ;\n"
	"       decl %0               ;\n"
	"       jnz 1b                ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2)
	:
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_pII_mmx_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	      अचिन्हित दीर्घ *p3)
अणु
	अचिन्हित दीर्घ lines = bytes >> 7;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)				\
	LD(i, 0)				\
		LD(i + 1, 1)			\
			LD(i + 2, 2)		\
				LD(i + 3, 3)	\
	XO1(i, 0)				\
		XO1(i + 1, 1)			\
			XO1(i + 2, 2)		\
				XO1(i + 3, 3)	\
	XO2(i, 0)				\
	ST(i, 0)				\
		XO2(i + 1, 1)			\
		ST(i + 1, 1)			\
			XO2(i + 2, 2)		\
			ST(i + 2, 2)		\
				XO2(i + 3, 3)	\
				ST(i + 3, 3)

	" .align 32			;\n"
	" 1:                            ;\n"

	BLOCK(0)
	BLOCK(4)
	BLOCK(8)
	BLOCK(12)

	"       addl $128, %1         ;\n"
	"       addl $128, %2         ;\n"
	"       addl $128, %3         ;\n"
	"       decl %0               ;\n"
	"       jnz 1b                ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2), "+r" (p3)
	:
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_pII_mmx_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	      अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	अचिन्हित दीर्घ lines = bytes >> 7;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)				\
	LD(i, 0)				\
		LD(i + 1, 1)			\
			LD(i + 2, 2)		\
				LD(i + 3, 3)	\
	XO1(i, 0)				\
		XO1(i + 1, 1)			\
			XO1(i + 2, 2)		\
				XO1(i + 3, 3)	\
	XO2(i, 0)				\
		XO2(i + 1, 1)			\
			XO2(i + 2, 2)		\
				XO2(i + 3, 3)	\
	XO3(i, 0)				\
	ST(i, 0)				\
		XO3(i + 1, 1)			\
		ST(i + 1, 1)			\
			XO3(i + 2, 2)		\
			ST(i + 2, 2)		\
				XO3(i + 3, 3)	\
				ST(i + 3, 3)

	" .align 32			;\n"
	" 1:                            ;\n"

	BLOCK(0)
	BLOCK(4)
	BLOCK(8)
	BLOCK(12)

	"       addl $128, %1         ;\n"
	"       addl $128, %2         ;\n"
	"       addl $128, %3         ;\n"
	"       addl $128, %4         ;\n"
	"       decl %0               ;\n"
	"       jnz 1b                ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2), "+r" (p3), "+r" (p4)
	:
	: "memory");

	kernel_fpu_end();
पूर्ण


अटल व्योम
xor_pII_mmx_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	      अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	अचिन्हित दीर्घ lines = bytes >> 7;

	kernel_fpu_begin();

	/* Make sure GCC क्रममाला_लो anything it knows about p4 or p5,
	   such that it won't pass to the यंत्र अस्थिर below a
	   रेजिस्टर that is shared with any other variable.  That's
	   because we modअगरy p4 and p5 there, but we can't mark them
	   as पढ़ो/ग_लिखो, otherwise we'd overflow the 10-यंत्र-opeअक्रमs
	   limit of GCC < 3.1.  */
	यंत्र("" : "+r" (p4), "+r" (p5));

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)				\
	LD(i, 0)				\
		LD(i + 1, 1)			\
			LD(i + 2, 2)		\
				LD(i + 3, 3)	\
	XO1(i, 0)				\
		XO1(i + 1, 1)			\
			XO1(i + 2, 2)		\
				XO1(i + 3, 3)	\
	XO2(i, 0)				\
		XO2(i + 1, 1)			\
			XO2(i + 2, 2)		\
				XO2(i + 3, 3)	\
	XO3(i, 0)				\
		XO3(i + 1, 1)			\
			XO3(i + 2, 2)		\
				XO3(i + 3, 3)	\
	XO4(i, 0)				\
	ST(i, 0)				\
		XO4(i + 1, 1)			\
		ST(i + 1, 1)			\
			XO4(i + 2, 2)		\
			ST(i + 2, 2)		\
				XO4(i + 3, 3)	\
				ST(i + 3, 3)

	" .align 32			;\n"
	" 1:                            ;\n"

	BLOCK(0)
	BLOCK(4)
	BLOCK(8)
	BLOCK(12)

	"       addl $128, %1         ;\n"
	"       addl $128, %2         ;\n"
	"       addl $128, %3         ;\n"
	"       addl $128, %4         ;\n"
	"       addl $128, %5         ;\n"
	"       decl %0               ;\n"
	"       jnz 1b                ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2), "+r" (p3)
	: "r" (p4), "r" (p5)
	: "memory");

	/* p4 and p5 were modअगरied, and now the variables are dead.
	   Clobber them just to be sure nobody करोes something stupid
	   like assuming they have some legal value.  */
	यंत्र("" : "=r" (p4), "=r" (p5));

	kernel_fpu_end();
पूर्ण

#अघोषित LD
#अघोषित XO1
#अघोषित XO2
#अघोषित XO3
#अघोषित XO4
#अघोषित ST
#अघोषित BLOCK

अटल व्योम
xor_p5_mmx_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	अचिन्हित दीर्घ lines = bytes >> 6;

	kernel_fpu_begin();

	यंत्र अस्थिर(
	" .align 32	             ;\n"
	" 1:                         ;\n"
	"       movq   (%1), %%mm0   ;\n"
	"       movq  8(%1), %%mm1   ;\n"
	"       pxor   (%2), %%mm0   ;\n"
	"       movq 16(%1), %%mm2   ;\n"
	"       movq %%mm0,   (%1)   ;\n"
	"       pxor  8(%2), %%mm1   ;\n"
	"       movq 24(%1), %%mm3   ;\n"
	"       movq %%mm1,  8(%1)   ;\n"
	"       pxor 16(%2), %%mm2   ;\n"
	"       movq 32(%1), %%mm4   ;\n"
	"       movq %%mm2, 16(%1)   ;\n"
	"       pxor 24(%2), %%mm3   ;\n"
	"       movq 40(%1), %%mm5   ;\n"
	"       movq %%mm3, 24(%1)   ;\n"
	"       pxor 32(%2), %%mm4   ;\n"
	"       movq 48(%1), %%mm6   ;\n"
	"       movq %%mm4, 32(%1)   ;\n"
	"       pxor 40(%2), %%mm5   ;\n"
	"       movq 56(%1), %%mm7   ;\n"
	"       movq %%mm5, 40(%1)   ;\n"
	"       pxor 48(%2), %%mm6   ;\n"
	"       pxor 56(%2), %%mm7   ;\n"
	"       movq %%mm6, 48(%1)   ;\n"
	"       movq %%mm7, 56(%1)   ;\n"

	"       addl $64, %1         ;\n"
	"       addl $64, %2         ;\n"
	"       decl %0              ;\n"
	"       jnz 1b               ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2)
	:
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_p5_mmx_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	     अचिन्हित दीर्घ *p3)
अणु
	अचिन्हित दीर्घ lines = bytes >> 6;

	kernel_fpu_begin();

	यंत्र अस्थिर(
	" .align 32,0x90             ;\n"
	" 1:                         ;\n"
	"       movq   (%1), %%mm0   ;\n"
	"       movq  8(%1), %%mm1   ;\n"
	"       pxor   (%2), %%mm0   ;\n"
	"       movq 16(%1), %%mm2   ;\n"
	"       pxor  8(%2), %%mm1   ;\n"
	"       pxor   (%3), %%mm0   ;\n"
	"       pxor 16(%2), %%mm2   ;\n"
	"       movq %%mm0,   (%1)   ;\n"
	"       pxor  8(%3), %%mm1   ;\n"
	"       pxor 16(%3), %%mm2   ;\n"
	"       movq 24(%1), %%mm3   ;\n"
	"       movq %%mm1,  8(%1)   ;\n"
	"       movq 32(%1), %%mm4   ;\n"
	"       movq 40(%1), %%mm5   ;\n"
	"       pxor 24(%2), %%mm3   ;\n"
	"       movq %%mm2, 16(%1)   ;\n"
	"       pxor 32(%2), %%mm4   ;\n"
	"       pxor 24(%3), %%mm3   ;\n"
	"       pxor 40(%2), %%mm5   ;\n"
	"       movq %%mm3, 24(%1)   ;\n"
	"       pxor 32(%3), %%mm4   ;\n"
	"       pxor 40(%3), %%mm5   ;\n"
	"       movq 48(%1), %%mm6   ;\n"
	"       movq %%mm4, 32(%1)   ;\n"
	"       movq 56(%1), %%mm7   ;\n"
	"       pxor 48(%2), %%mm6   ;\n"
	"       movq %%mm5, 40(%1)   ;\n"
	"       pxor 56(%2), %%mm7   ;\n"
	"       pxor 48(%3), %%mm6   ;\n"
	"       pxor 56(%3), %%mm7   ;\n"
	"       movq %%mm6, 48(%1)   ;\n"
	"       movq %%mm7, 56(%1)   ;\n"

	"       addl $64, %1         ;\n"
	"       addl $64, %2         ;\n"
	"       addl $64, %3         ;\n"
	"       decl %0              ;\n"
	"       jnz 1b               ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2), "+r" (p3)
	:
	: "memory" );

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_p5_mmx_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	     अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	अचिन्हित दीर्घ lines = bytes >> 6;

	kernel_fpu_begin();

	यंत्र अस्थिर(
	" .align 32,0x90             ;\n"
	" 1:                         ;\n"
	"       movq   (%1), %%mm0   ;\n"
	"       movq  8(%1), %%mm1   ;\n"
	"       pxor   (%2), %%mm0   ;\n"
	"       movq 16(%1), %%mm2   ;\n"
	"       pxor  8(%2), %%mm1   ;\n"
	"       pxor   (%3), %%mm0   ;\n"
	"       pxor 16(%2), %%mm2   ;\n"
	"       pxor  8(%3), %%mm1   ;\n"
	"       pxor   (%4), %%mm0   ;\n"
	"       movq 24(%1), %%mm3   ;\n"
	"       pxor 16(%3), %%mm2   ;\n"
	"       pxor  8(%4), %%mm1   ;\n"
	"       movq %%mm0,   (%1)   ;\n"
	"       movq 32(%1), %%mm4   ;\n"
	"       pxor 24(%2), %%mm3   ;\n"
	"       pxor 16(%4), %%mm2   ;\n"
	"       movq %%mm1,  8(%1)   ;\n"
	"       movq 40(%1), %%mm5   ;\n"
	"       pxor 32(%2), %%mm4   ;\n"
	"       pxor 24(%3), %%mm3   ;\n"
	"       movq %%mm2, 16(%1)   ;\n"
	"       pxor 40(%2), %%mm5   ;\n"
	"       pxor 32(%3), %%mm4   ;\n"
	"       pxor 24(%4), %%mm3   ;\n"
	"       movq %%mm3, 24(%1)   ;\n"
	"       movq 56(%1), %%mm7   ;\n"
	"       movq 48(%1), %%mm6   ;\n"
	"       pxor 40(%3), %%mm5   ;\n"
	"       pxor 32(%4), %%mm4   ;\n"
	"       pxor 48(%2), %%mm6   ;\n"
	"       movq %%mm4, 32(%1)   ;\n"
	"       pxor 56(%2), %%mm7   ;\n"
	"       pxor 40(%4), %%mm5   ;\n"
	"       pxor 48(%3), %%mm6   ;\n"
	"       pxor 56(%3), %%mm7   ;\n"
	"       movq %%mm5, 40(%1)   ;\n"
	"       pxor 48(%4), %%mm6   ;\n"
	"       pxor 56(%4), %%mm7   ;\n"
	"       movq %%mm6, 48(%1)   ;\n"
	"       movq %%mm7, 56(%1)   ;\n"

	"       addl $64, %1         ;\n"
	"       addl $64, %2         ;\n"
	"       addl $64, %3         ;\n"
	"       addl $64, %4         ;\n"
	"       decl %0              ;\n"
	"       jnz 1b               ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2), "+r" (p3), "+r" (p4)
	:
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_p5_mmx_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	     अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	अचिन्हित दीर्घ lines = bytes >> 6;

	kernel_fpu_begin();

	/* Make sure GCC क्रममाला_लो anything it knows about p4 or p5,
	   such that it won't pass to the यंत्र अस्थिर below a
	   रेजिस्टर that is shared with any other variable.  That's
	   because we modअगरy p4 and p5 there, but we can't mark them
	   as पढ़ो/ग_लिखो, otherwise we'd overflow the 10-यंत्र-opeअक्रमs
	   limit of GCC < 3.1.  */
	यंत्र("" : "+r" (p4), "+r" (p5));

	यंत्र अस्थिर(
	" .align 32,0x90             ;\n"
	" 1:                         ;\n"
	"       movq   (%1), %%mm0   ;\n"
	"       movq  8(%1), %%mm1   ;\n"
	"       pxor   (%2), %%mm0   ;\n"
	"       pxor  8(%2), %%mm1   ;\n"
	"       movq 16(%1), %%mm2   ;\n"
	"       pxor   (%3), %%mm0   ;\n"
	"       pxor  8(%3), %%mm1   ;\n"
	"       pxor 16(%2), %%mm2   ;\n"
	"       pxor   (%4), %%mm0   ;\n"
	"       pxor  8(%4), %%mm1   ;\n"
	"       pxor 16(%3), %%mm2   ;\n"
	"       movq 24(%1), %%mm3   ;\n"
	"       pxor   (%5), %%mm0   ;\n"
	"       pxor  8(%5), %%mm1   ;\n"
	"       movq %%mm0,   (%1)   ;\n"
	"       pxor 16(%4), %%mm2   ;\n"
	"       pxor 24(%2), %%mm3   ;\n"
	"       movq %%mm1,  8(%1)   ;\n"
	"       pxor 16(%5), %%mm2   ;\n"
	"       pxor 24(%3), %%mm3   ;\n"
	"       movq 32(%1), %%mm4   ;\n"
	"       movq %%mm2, 16(%1)   ;\n"
	"       pxor 24(%4), %%mm3   ;\n"
	"       pxor 32(%2), %%mm4   ;\n"
	"       movq 40(%1), %%mm5   ;\n"
	"       pxor 24(%5), %%mm3   ;\n"
	"       pxor 32(%3), %%mm4   ;\n"
	"       pxor 40(%2), %%mm5   ;\n"
	"       movq %%mm3, 24(%1)   ;\n"
	"       pxor 32(%4), %%mm4   ;\n"
	"       pxor 40(%3), %%mm5   ;\n"
	"       movq 48(%1), %%mm6   ;\n"
	"       movq 56(%1), %%mm7   ;\n"
	"       pxor 32(%5), %%mm4   ;\n"
	"       pxor 40(%4), %%mm5   ;\n"
	"       pxor 48(%2), %%mm6   ;\n"
	"       pxor 56(%2), %%mm7   ;\n"
	"       movq %%mm4, 32(%1)   ;\n"
	"       pxor 48(%3), %%mm6   ;\n"
	"       pxor 56(%3), %%mm7   ;\n"
	"       pxor 40(%5), %%mm5   ;\n"
	"       pxor 48(%4), %%mm6   ;\n"
	"       pxor 56(%4), %%mm7   ;\n"
	"       movq %%mm5, 40(%1)   ;\n"
	"       pxor 48(%5), %%mm6   ;\n"
	"       pxor 56(%5), %%mm7   ;\n"
	"       movq %%mm6, 48(%1)   ;\n"
	"       movq %%mm7, 56(%1)   ;\n"

	"       addl $64, %1         ;\n"
	"       addl $64, %2         ;\n"
	"       addl $64, %3         ;\n"
	"       addl $64, %4         ;\n"
	"       addl $64, %5         ;\n"
	"       decl %0              ;\n"
	"       jnz 1b               ;\n"
	: "+r" (lines),
	  "+r" (p1), "+r" (p2), "+r" (p3)
	: "r" (p4), "r" (p5)
	: "memory");

	/* p4 and p5 were modअगरied, and now the variables are dead.
	   Clobber them just to be sure nobody करोes something stupid
	   like assuming they have some legal value.  */
	यंत्र("" : "=r" (p4), "=r" (p5));

	kernel_fpu_end();
पूर्ण

अटल काष्ठा xor_block_ढाँचा xor_block_pII_mmx = अणु
	.name = "pII_mmx",
	.करो_2 = xor_pII_mmx_2,
	.करो_3 = xor_pII_mmx_3,
	.करो_4 = xor_pII_mmx_4,
	.करो_5 = xor_pII_mmx_5,
पूर्ण;

अटल काष्ठा xor_block_ढाँचा xor_block_p5_mmx = अणु
	.name = "p5_mmx",
	.करो_2 = xor_p5_mmx_2,
	.करो_3 = xor_p5_mmx_3,
	.करो_4 = xor_p5_mmx_4,
	.करो_5 = xor_p5_mmx_5,
पूर्ण;

अटल काष्ठा xor_block_ढाँचा xor_block_pIII_sse = अणु
	.name = "pIII_sse",
	.करो_2 = xor_sse_2,
	.करो_3 = xor_sse_3,
	.करो_4 = xor_sse_4,
	.करो_5 = xor_sse_5,
पूर्ण;

/* Also try the AVX routines */
#समावेश <यंत्र/xor_avx.h>

/* Also try the generic routines.  */
#समावेश <यंत्र-generic/xor.h>

/* We क्रमce the use of the SSE xor block because it can ग_लिखो around L2.
   We may also be able to load पूर्णांकo the L1 only depending on how the cpu
   deals with a load to a line that is being prefetched.  */
#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES				\
करो अणु							\
	AVX_XOR_SPEED;					\
	अगर (boot_cpu_has(X86_FEATURE_XMM)) अणु				\
		xor_speed(&xor_block_pIII_sse);		\
		xor_speed(&xor_block_sse_pf64);		\
	पूर्ण अन्यथा अगर (boot_cpu_has(X86_FEATURE_MMX)) अणु	\
		xor_speed(&xor_block_pII_mmx);		\
		xor_speed(&xor_block_p5_mmx);		\
	पूर्ण अन्यथा अणु					\
		xor_speed(&xor_block_8regs);		\
		xor_speed(&xor_block_8regs_p);		\
		xor_speed(&xor_block_32regs);		\
		xor_speed(&xor_block_32regs_p);		\
	पूर्ण						\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_X86_XOR_32_H */
