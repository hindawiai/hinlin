<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_HASH_H
#घोषणा _ASM_HASH_H

/*
 * Fortunately, most people who want to run Linux on Microblaze enable
 * both multiplier and barrel shअगरter, but omitting them is technically
 * a supported configuration.
 *
 * With just a barrel shअगरter, we can implement an efficient स्थिरant
 * multiply using shअगरts and adds.  GCC can find a 9-step solution, but
 * this 6-step solution was found by Yevgen Voronenko's implementation
 * of the Hcub algorithm at http://spiral.ece.cmu.edu/mcm/gen.hपंचांगl.
 *
 * That software is really not deचिन्हित क्रम a single multiplier this large,
 * but अगर you run it enough बार with dअगरferent seeds, it'll find several
 * 6-shअगरt, 6-add sequences क्रम computing x * 0x61C88647.  They are all
 *	c = (x << 19) + x;
 *	a = (x <<  9) + c;
 *	b = (x << 23) + a;
 *	वापस (a<<11) + (b<<6) + (c<<3) - b;
 * with variations on the order of the final add.
 *
 * Without even a shअगरter, it's hopless; any hash function will suck.
 */

#अगर CONFIG_XILINX_MICROBLAZE0_USE_HW_MUL == 0

#घोषणा HAVE_ARCH__HASH_32 1

/* Multiply by GOLDEN_RATIO_32 = 0x61C88647 */
अटल अंतरभूत u32 __attribute_स्थिर__ __hash_32(u32 a)
अणु
#अगर CONFIG_XILINX_MICROBLAZE0_USE_BARREL
	अचिन्हित पूर्णांक b, c;

	/* Phase 1: Compute three पूर्णांकermediate values */
	b =  a << 23;
	c = (a << 19) + a;
	a = (a <<  9) + c;
	b += a;

	/* Phase 2: Compute (a << 11) + (b << 6) + (c << 3) - b */
	a <<= 5;
	a += b;		/* (a << 5) + b */
	a <<= 3;
	a += c;		/* (a << 8) + (b << 3) + c */
	a <<= 3;
	वापस a - b;	/* (a << 11) + (b << 6) + (c << 3) - b */
#अन्यथा
	/*
	 * "This is really going to hurt."
	 *
	 * Without a barrel shअगरter, left shअगरts are implemented as
	 * repeated additions, and the best we can करो is an optimal
	 * addition-subtraction chain.  This one is not known to be
	 * optimal, but at 37 steps, it's decent क्रम a 31-bit multiplier.
	 *
	 * Question: given its size (37*4 = 148 bytes per instance),
	 * and slowness, is this worth having अंतरभूत?
	 */
	अचिन्हित पूर्णांक b, c, d;

	b = a << 4;	/* 4    */
	c = b << 1;	/* 1  5 */
	b += a;		/* 1  6 */
	c += b;		/* 1  7 */
	c <<= 3;	/* 3 10 */
	c -= a;		/* 1 11 */
	d = c << 7;	/* 7 18 */
	d += b;		/* 1 19 */
	d <<= 8;	/* 8 27 */
	d += a;		/* 1 28 */
	d <<= 1;	/* 1 29 */
	d += b;		/* 1 30 */
	d <<= 6;	/* 6 36 */
	वापस d + c;	/* 1 37 total inकाष्ठाions*/
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* !CONFIG_XILINX_MICROBLAZE0_USE_HW_MUL */
#पूर्ण_अगर /* _ASM_HASH_H */
