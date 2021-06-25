<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_XOR_H
#घोषणा _ASM_X86_XOR_H

/*
 * Optimized RAID-5 checksumming functions क्रम SSE.
 */

/*
 * Cache aव्योमing checksumming functions utilizing KNI inकाष्ठाions
 * Copyright (C) 1999 Zach Brown (with obvious credit due Ingo)
 */

/*
 * Based on
 * High-speed RAID5 checksumming functions utilizing SSE inकाष्ठाions.
 * Copyright (C) 1998 Ingo Molnar.
 */

/*
 * x86-64 changes / gcc fixes from Andi Kleen.
 * Copyright 2002 Andi Kleen, SuSE Lअसल.
 *
 * This hasn't been optimized क्रम the hammer yet, but there are likely
 * no advantages to be gotten from x86-64 here anyways.
 */

#समावेश <यंत्र/fpu/api.h>

#अगर_घोषित CONFIG_X86_32
/* reduce रेजिस्टर pressure */
# define XOR_CONSTANT_CONSTRAINT "i"
#अन्यथा
# define XOR_CONSTANT_CONSTRAINT "re"
#पूर्ण_अगर

#घोषणा OFFS(x)		"16*("#x")"
#घोषणा PF_OFFS(x)	"256+16*("#x")"
#घोषणा PF0(x)		"	prefetchnta "PF_OFFS(x)"(%[p1])		;\n"
#घोषणा LD(x, y)	"	movaps "OFFS(x)"(%[p1]), %%xmm"#y"	;\n"
#घोषणा ST(x, y)	"	movaps %%xmm"#y", "OFFS(x)"(%[p1])	;\n"
#घोषणा PF1(x)		"	prefetchnta "PF_OFFS(x)"(%[p2])		;\n"
#घोषणा PF2(x)		"	prefetchnta "PF_OFFS(x)"(%[p3])		;\n"
#घोषणा PF3(x)		"	prefetchnta "PF_OFFS(x)"(%[p4])		;\n"
#घोषणा PF4(x)		"	prefetchnta "PF_OFFS(x)"(%[p5])		;\n"
#घोषणा XO1(x, y)	"	xorps "OFFS(x)"(%[p2]), %%xmm"#y"	;\n"
#घोषणा XO2(x, y)	"	xorps "OFFS(x)"(%[p3]), %%xmm"#y"	;\n"
#घोषणा XO3(x, y)	"	xorps "OFFS(x)"(%[p4]), %%xmm"#y"	;\n"
#घोषणा XO4(x, y)	"	xorps "OFFS(x)"(%[p5]), %%xmm"#y"	;\n"
#घोषणा NOP(x)

#घोषणा BLK64(pf, op, i)				\
		pf(i)					\
		op(i, 0)				\
			op(i + 1, 1)			\
				op(i + 2, 2)		\
					op(i + 3, 3)

अटल व्योम
xor_sse_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)					\
		LD(i, 0)				\
			LD(i + 1, 1)			\
		PF1(i)					\
				PF1(i + 2)		\
				LD(i + 2, 2)		\
					LD(i + 3, 3)	\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines),
	  [p1] "+r" (p1), [p2] "+r" (p2)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_2_pf64(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)			\
		BLK64(PF0, LD, i)	\
		BLK64(PF1, XO1, i)	\
		BLK64(NOP, ST, i)	\

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines),
	  [p1] "+r" (p1), [p2] "+r" (p2)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	  अचिन्हित दीर्घ *p3)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i) \
		PF1(i)					\
				PF1(i + 2)		\
		LD(i, 0)				\
			LD(i + 1, 1)			\
				LD(i + 2, 2)		\
					LD(i + 3, 3)	\
		PF2(i)					\
				PF2(i + 2)		\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		XO2(i, 0)				\
			XO2(i + 1, 1)			\
				XO2(i + 2, 2)		\
					XO2(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines),
	  [p1] "+r" (p1), [p2] "+r" (p2), [p3] "+r" (p3)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_3_pf64(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	       अचिन्हित दीर्घ *p3)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)			\
		BLK64(PF0, LD, i)	\
		BLK64(PF1, XO1, i)	\
		BLK64(PF2, XO2, i)	\
		BLK64(NOP, ST, i)	\

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines),
	  [p1] "+r" (p1), [p2] "+r" (p2), [p3] "+r" (p3)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	  अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i) \
		PF1(i)					\
				PF1(i + 2)		\
		LD(i, 0)				\
			LD(i + 1, 1)			\
				LD(i + 2, 2)		\
					LD(i + 3, 3)	\
		PF2(i)					\
				PF2(i + 2)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		PF3(i)					\
				PF3(i + 2)		\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO2(i, 0)				\
			XO2(i + 1, 1)			\
				XO2(i + 2, 2)		\
					XO2(i + 3, 3)	\
		XO3(i, 0)				\
			XO3(i + 1, 1)			\
				XO3(i + 2, 2)		\
					XO3(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines), [p1] "+r" (p1),
	  [p2] "+r" (p2), [p3] "+r" (p3), [p4] "+r" (p4)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_4_pf64(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	       अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)			\
		BLK64(PF0, LD, i)	\
		BLK64(PF1, XO1, i)	\
		BLK64(PF2, XO2, i)	\
		BLK64(PF3, XO3, i)	\
		BLK64(NOP, ST, i)	\

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines), [p1] "+r" (p1),
	  [p2] "+r" (p2), [p3] "+r" (p3), [p4] "+r" (p4)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	  अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i) \
		PF1(i)					\
				PF1(i + 2)		\
		LD(i, 0)				\
			LD(i + 1, 1)			\
				LD(i + 2, 2)		\
					LD(i + 3, 3)	\
		PF2(i)					\
				PF2(i + 2)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		PF3(i)					\
				PF3(i + 2)		\
		XO2(i, 0)				\
			XO2(i + 1, 1)			\
				XO2(i + 2, 2)		\
					XO2(i + 3, 3)	\
		PF4(i)					\
				PF4(i + 2)		\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO3(i, 0)				\
			XO3(i + 1, 1)			\
				XO3(i + 2, 2)		\
					XO3(i + 3, 3)	\
		XO4(i, 0)				\
			XO4(i + 1, 1)			\
				XO4(i + 2, 2)		\
					XO4(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       add %[inc], %[p5]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines), [p1] "+r" (p1), [p2] "+r" (p2),
	  [p3] "+r" (p3), [p4] "+r" (p4), [p5] "+r" (p5)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल व्योम
xor_sse_5_pf64(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	       अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	अचिन्हित दीर्घ lines = bytes >> 8;

	kernel_fpu_begin();

	यंत्र अस्थिर(
#अघोषित BLOCK
#घोषणा BLOCK(i)			\
		BLK64(PF0, LD, i)	\
		BLK64(PF1, XO1, i)	\
		BLK64(PF2, XO2, i)	\
		BLK64(PF3, XO3, i)	\
		BLK64(PF4, XO4, i)	\
		BLK64(NOP, ST, i)	\

	" .align 32			;\n"
	" 1:                            ;\n"

		BLOCK(0)
		BLOCK(4)
		BLOCK(8)
		BLOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       add %[inc], %[p5]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+r" (lines), [p1] "+r" (p1), [p2] "+r" (p2),
	  [p3] "+r" (p3), [p4] "+r" (p4), [p5] "+r" (p5)
	: [inc] XOR_CONSTANT_CONSTRAINT (256UL)
	: "memory");

	kernel_fpu_end();
पूर्ण

अटल काष्ठा xor_block_ढाँचा xor_block_sse_pf64 = अणु
	.name = "prefetch64-sse",
	.करो_2 = xor_sse_2_pf64,
	.करो_3 = xor_sse_3_pf64,
	.करो_4 = xor_sse_4_pf64,
	.करो_5 = xor_sse_5_pf64,
पूर्ण;

#अघोषित LD
#अघोषित XO1
#अघोषित XO2
#अघोषित XO3
#अघोषित XO4
#अघोषित ST
#अघोषित NOP
#अघोषित BLK64
#अघोषित BLOCK

#अघोषित XOR_CONSTANT_CONSTRAINT

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/xor_32.h>
#अन्यथा
# include <यंत्र/xor_64.h>
#पूर्ण_अगर

#घोषणा XOR_SELECT_TEMPLATE(FASTEST) \
	AVX_SELECT(FASTEST)

#पूर्ण_अगर /* _ASM_X86_XOR_H */
