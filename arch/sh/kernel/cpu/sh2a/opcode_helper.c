<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh2a/opcode_helper.c
 *
 * Helper क्रम the SH-2A 32-bit opcodes.
 *
 *  Copyright (C) 2007  Paul Mundt
 */
#समावेश <linux/kernel.h>

/*
 * Inकाष्ठाions on SH are generally fixed at 16-bits, however, SH-2A
 * पूर्णांकroduces some 32-bit inकाष्ठाions. Since there are no real
 * स्थिरraपूर्णांकs on their use (and they can be mixed and matched), we need
 * to check the inकाष्ठाion encoding to work out अगर it's a true 32-bit
 * inकाष्ठाion or not.
 *
 * Presently, 32-bit opcodes have only slight variations in what the
 * actual encoding looks like in the first-half of the inकाष्ठाion, which
 * makes it fairly straightक्रमward to dअगरferentiate from the 16-bit ones.
 *
 * First 16-bits of encoding		Used by
 *
 *	0011nnnnmmmm0001	mov.b, mov.w, mov.l, fmov.d,
 *				fmov.s, movu.b, movu.w
 *
 *	0011nnnn0iii1001        bclr.b, bld.b, bset.b, bst.b, band.b,
 *				bandnot.b, bldnot.b, bor.b, bornot.b,
 *				bxor.b
 *
 *	0000nnnniiii0000        movi20
 *	0000nnnniiii0001        movi20s
 */
अचिन्हित पूर्णांक inकाष्ठाion_size(अचिन्हित पूर्णांक insn)
अणु
	/* Look क्रम the common हालs */
	चयन ((insn & 0xf00f)) अणु
	हाल 0x0000:	/* movi20 */
	हाल 0x0001:	/* movi20s */
	हाल 0x3001:	/* 32-bit mov/fmov/movu variants */
		वापस 4;
	पूर्ण

	/* And the special हालs.. */
	चयन ((insn & 0xf08f)) अणु
	हाल 0x3009:	/* 32-bit b*.b bit operations */
		वापस 4;
	पूर्ण

	वापस 2;
पूर्ण
