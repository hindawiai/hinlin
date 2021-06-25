<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_HASH_H
#घोषणा _ASM_HASH_H

/*
 * HP-PA only implements पूर्णांकeger multiply in the FPU.  However, क्रम
 * पूर्णांकeger multiplies by स्थिरant, it has a number of shअगरt-and-add
 * (but no shअगरt-and-subtract, sigh!) inकाष्ठाions that a compiler
 * can synthesize a code sequence with.
 *
 * Unक्रमtunately, GCC isn't very efficient at using them.  For example
 * it uses three inकाष्ठाions क्रम "x *= 21" when only two are needed.
 * But we can find a sequence manually.
 */

#घोषणा HAVE_ARCH__HASH_32 1

/*
 * This is a multiply by GOLDEN_RATIO_32 = 0x61C88647 optimized क्रम the
 * PA7100 pairing rules.  This is an in-order 2-way superscalar processor.
 * Only one inकाष्ठाion in a pair may be a shअगरt (by more than 3 bits),
 * but other than that, simple ALU ops (including shअगरt-and-add by up
 * to 3 bits) may be paired arbitrarily.
 *
 * PA8xxx processors also dual-issue ALU inकाष्ठाions, although with
 * fewer स्थिरraपूर्णांकs, so this schedule is good क्रम them, too.
 *
 * This 6-step sequence was found by Yevgen Voronenko's implementation
 * of the Hcub algorithm at http://spiral.ece.cmu.edu/mcm/gen.hपंचांगl.
 */
अटल अंतरभूत u32 __attribute_स्थिर__ __hash_32(u32 x)
अणु
	u32 a, b, c;

	/*
	 * Phase 1: Compute  a = (x << 19) + x,
	 * b = (x << 9) + a, c = (x << 23) + b.
	 */
	a = x << 19;		/* Two shअगरts can't be paired */
	b = x << 9;	a += x;
	c = x << 23;	b += a;
			c += b;
	/* Phase 2: Return (b<<11) + (c<<6) + (a<<3) - c */
	b <<= 11;
	a += c << 3;	b -= c;
	वापस (a << 3) + b;
पूर्ण

#अगर BITS_PER_LONG == 64

#घोषणा HAVE_ARCH_HASH_64 1

/*
 * Finding a good shअगरt-and-add chain क्रम GOLDEN_RATIO_64 is tricky,
 * because available software क्रम the purpose chokes on स्थिरants this
 * large.  (It's mostly deचिन्हित क्रम compiling FIR filter coefficients
 * पूर्णांकo FPGAs.)
 *
 * However, Jason Thong poपूर्णांकed out a work-around.  The Hcub software
 * (http://spiral.ece.cmu.edu/mcm/gen.hपंचांगl) is deचिन्हित क्रम *multiple*
 * स्थिरant multiplication, and is good at finding shअगरt-and-add chains
 * which share common terms.
 *
 * Looking at 0x0x61C8864680B583EB in binary:
 * 0110000111001000100001100100011010000000101101011000001111101011
 *  \______________/    \__________/       \_______/     \________/
 *   \____________________________/         \____________________/
 * you can see the non-zero bits are भागided पूर्णांकo several well-separated
 * blocks.  Hcub can find algorithms क्रम those terms separately, which
 * can then be shअगरted and added together.
 *
 * Dividing the input पूर्णांकo 2, 3 or 4 blocks, Hcub can find solutions
 * with 10, 9 or 8 adds, respectively, making a total of 11 क्रम the
 * whole number.
 *
 * Using just two large blocks, 0xC3910C8D << 31 in the high bits,
 * and 0xB583EB in the low bits, produces as good an algorithm as any,
 * and with one more small shअगरt than alternatives.
 *
 * The high bits are a larger number and more work to compute, as well
 * as needing one extra cycle to shअगरt left 31 bits beक्रमe the final
 * addition, so they are the critical path क्रम scheduling.  The low bits
 * can fit पूर्णांकo the scheduling slots left over.
 */


/*
 * This _ASSIGN(dst, src) macro perक्रमms "dst = src", but prevents GCC
 * from inferring anything about the value asचिन्हित to "dest".
 *
 * This prevents it from mis-optimizing certain sequences.
 * In particular, gcc is annoyingly eager to combine consecutive shअगरts.
 * Given "x <<= 19; y += x; z += x << 1;", GCC will turn this पूर्णांकo
 * "y += x << 19; z += x << 20;" even though the latter sequence needs
 * an additional inकाष्ठाion and temporary रेजिस्टर.
 *
 * Because no actual assembly code is generated, this स्थिरruct is
 * usefully portable across all GCC platक्रमms, and so can be test-compiled
 * on non-PA प्रणालीs.
 *
 * In two places, additional unused input dependencies are added.  This
 * क्रमces GCC's scheduling so it करोes not rearrange inकाष्ठाions too much.
 * Because the PA-8xxx is out of order, I'm not sure how much this matters,
 * but why make it more dअगरficult क्रम the processor than necessary?
 */
#घोषणा _ASSIGN(dst, src, ...) यंत्र("" : "=r" (dst) : "0" (src), ##__VA_ARGS__)

/*
 * Multiply by GOLDEN_RATIO_64 = 0x0x61C8864680B583EB using a heavily
 * optimized shअगरt-and-add sequence.
 *
 * Without the final shअगरt, the multiply proper is 19 inकाष्ठाions,
 * 10 cycles and uses only 4 temporaries.  Whew!
 *
 * You are not expected to understand this.
 */
अटल __always_अंतरभूत u32 __attribute_स्थिर__
hash_64(u64 a, अचिन्हित पूर्णांक bits)
अणु
	u64 b, c, d;

	/*
	 * Encourage GCC to move a dynamic shअगरt to %sar early,
	 * thereby मुक्तing up an additional temporary रेजिस्टर.
	 */
	अगर (!__builtin_स्थिरant_p(bits))
		यंत्र("" : "=q" (bits) : "0" (64 - bits));
	अन्यथा
		bits = 64 - bits;

	_ASSIGN(b, a*5);	c = a << 13;
	b = (b << 2) + a;	_ASSIGN(d, a << 17);
	a = b + (a << 1);	c += d;
	d = a << 10;		_ASSIGN(a, a << 19);
	d = a - d;		_ASSIGN(a, a << 4, "X" (d));
	c += b;			a += b;
	d -= c;			c += a << 1;
	a += c << 3;		_ASSIGN(b, b << (7+31), "X" (c), "X" (d));
	a <<= 31;		b += d;
	a += b;
	वापस a >> bits;
पूर्ण
#अघोषित _ASSIGN	/* We're a widely-used header file, so don't litter! */

#पूर्ण_अगर /* BITS_PER_LONG == 64 */

#पूर्ण_अगर /* _ASM_HASH_H */
