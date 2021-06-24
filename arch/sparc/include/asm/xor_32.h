<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/यंत्र/xor.h
 *
 * Optimized RAID-5 checksumming functions क्रम 32-bit Sparc.
 */

/*
 * High speed xor_block operation क्रम RAID4/5 utilizing the
 * ldd/std SPARC inकाष्ठाions.
 *
 * Copyright (C) 1999 Jakub Jelinek (jj@ultra.linux.cz)
 */

अटल व्योम
sparc_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	पूर्णांक lines = bytes / (माप (दीर्घ)) / 8;

	करो अणु
		__यंत्र__ __अस्थिर__(
		  "ldd [%0 + 0x00], %%g2\n\t"
		  "ldd [%0 + 0x08], %%g4\n\t"
		  "ldd [%0 + 0x10], %%o0\n\t"
		  "ldd [%0 + 0x18], %%o2\n\t"
		  "ldd [%1 + 0x00], %%o4\n\t"
		  "ldd [%1 + 0x08], %%l0\n\t"
		  "ldd [%1 + 0x10], %%l2\n\t"
		  "ldd [%1 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "r" (p1), "r" (p2)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "l0", "l1", "l2", "l3", "l4", "l5");
		p1 += 8;
		p2 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

अटल व्योम
sparc_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	अचिन्हित दीर्घ *p3)
अणु
	पूर्णांक lines = bytes / (माप (दीर्घ)) / 8;

	करो अणु
		__यंत्र__ __अस्थिर__(
		  "ldd [%0 + 0x00], %%g2\n\t"
		  "ldd [%0 + 0x08], %%g4\n\t"
		  "ldd [%0 + 0x10], %%o0\n\t"
		  "ldd [%0 + 0x18], %%o2\n\t"
		  "ldd [%1 + 0x00], %%o4\n\t"
		  "ldd [%1 + 0x08], %%l0\n\t"
		  "ldd [%1 + 0x10], %%l2\n\t"
		  "ldd [%1 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "ldd [%2 + 0x00], %%o4\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "ldd [%2 + 0x08], %%l0\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "ldd [%2 + 0x10], %%l2\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "ldd [%2 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "r" (p1), "r" (p2), "r" (p3)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "l0", "l1", "l2", "l3", "l4", "l5");
		p1 += 8;
		p2 += 8;
		p3 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

अटल व्योम
sparc_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	पूर्णांक lines = bytes / (माप (दीर्घ)) / 8;

	करो अणु
		__यंत्र__ __अस्थिर__(
		  "ldd [%0 + 0x00], %%g2\n\t"
		  "ldd [%0 + 0x08], %%g4\n\t"
		  "ldd [%0 + 0x10], %%o0\n\t"
		  "ldd [%0 + 0x18], %%o2\n\t"
		  "ldd [%1 + 0x00], %%o4\n\t"
		  "ldd [%1 + 0x08], %%l0\n\t"
		  "ldd [%1 + 0x10], %%l2\n\t"
		  "ldd [%1 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "ldd [%2 + 0x00], %%o4\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "ldd [%2 + 0x08], %%l0\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "ldd [%2 + 0x10], %%l2\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "ldd [%2 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "ldd [%3 + 0x00], %%o4\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "ldd [%3 + 0x08], %%l0\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "ldd [%3 + 0x10], %%l2\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "ldd [%3 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "r" (p1), "r" (p2), "r" (p3), "r" (p4)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "l0", "l1", "l2", "l3", "l4", "l5");
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

अटल व्योम
sparc_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
	अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	पूर्णांक lines = bytes / (माप (दीर्घ)) / 8;

	करो अणु
		__यंत्र__ __अस्थिर__(
		  "ldd [%0 + 0x00], %%g2\n\t"
		  "ldd [%0 + 0x08], %%g4\n\t"
		  "ldd [%0 + 0x10], %%o0\n\t"
		  "ldd [%0 + 0x18], %%o2\n\t"
		  "ldd [%1 + 0x00], %%o4\n\t"
		  "ldd [%1 + 0x08], %%l0\n\t"
		  "ldd [%1 + 0x10], %%l2\n\t"
		  "ldd [%1 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "ldd [%2 + 0x00], %%o4\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "ldd [%2 + 0x08], %%l0\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "ldd [%2 + 0x10], %%l2\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "ldd [%2 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "ldd [%3 + 0x00], %%o4\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "ldd [%3 + 0x08], %%l0\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "ldd [%3 + 0x10], %%l2\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "ldd [%3 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "ldd [%4 + 0x00], %%o4\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "ldd [%4 + 0x08], %%l0\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "ldd [%4 + 0x10], %%l2\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "ldd [%4 + 0x18], %%l4\n\t"
		  "xor %%g2, %%o4, %%g2\n\t"
		  "xor %%g3, %%o5, %%g3\n\t"
		  "xor %%g4, %%l0, %%g4\n\t"
		  "xor %%g5, %%l1, %%g5\n\t"
		  "xor %%o0, %%l2, %%o0\n\t"
		  "xor %%o1, %%l3, %%o1\n\t"
		  "xor %%o2, %%l4, %%o2\n\t"
		  "xor %%o3, %%l5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "r" (p1), "r" (p2), "r" (p3), "r" (p4), "r" (p5)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "l0", "l1", "l2", "l3", "l4", "l5");
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
		p5 += 8;
	पूर्ण जबतक (--lines > 0);
पूर्ण

अटल काष्ठा xor_block_ढाँचा xor_block_SPARC = अणु
	.name	= "SPARC",
	.करो_2	= sparc_2,
	.करो_3	= sparc_3,
	.करो_4	= sparc_4,
	.करो_5	= sparc_5,
पूर्ण;

/* For grins, also test the generic routines.  */
#समावेश <यंत्र-generic/xor.h>

#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES				\
	करो अणु						\
		xor_speed(&xor_block_8regs);		\
		xor_speed(&xor_block_32regs);		\
		xor_speed(&xor_block_SPARC);		\
	पूर्ण जबतक (0)
