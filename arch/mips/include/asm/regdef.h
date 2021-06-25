<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1985 MIPS Computer Systems, Inc.
 * Copyright (C) 1994, 95, 99, 2003 by Ralf Baechle
 * Copyright (C) 1990 - 1992, 1999 Silicon Graphics, Inc.
 * Copyright (C) 2011 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित _ASM_REGDEF_H
#घोषणा _ASM_REGDEF_H

#समावेश <यंत्र/sgidefs.h>

#अगर _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * Symbolic रेजिस्टर names क्रम 32 bit ABI
 */
#घोषणा zero	$0	/* wired zero */
#घोषणा AT	$1	/* assembler temp  - upperहाल because of ".set at" */
#घोषणा v0	$2	/* वापस value */
#घोषणा v1	$3
#घोषणा a0	$4	/* argument रेजिस्टरs */
#घोषणा a1	$5
#घोषणा a2	$6
#घोषणा a3	$7
#घोषणा t0	$8	/* caller saved */
#घोषणा t1	$9
#घोषणा t2	$10
#घोषणा t3	$11
#घोषणा t4	$12
#घोषणा ta0	$12
#घोषणा t5	$13
#घोषणा ta1	$13
#घोषणा t6	$14
#घोषणा ta2	$14
#घोषणा t7	$15
#घोषणा ta3	$15
#घोषणा s0	$16	/* callee saved */
#घोषणा s1	$17
#घोषणा s2	$18
#घोषणा s3	$19
#घोषणा s4	$20
#घोषणा s5	$21
#घोषणा s6	$22
#घोषणा s7	$23
#घोषणा t8	$24	/* caller saved */
#घोषणा t9	$25
#घोषणा jp	$25	/* PIC jump रेजिस्टर */
#घोषणा k0	$26	/* kernel scratch */
#घोषणा k1	$27
#घोषणा gp	$28	/* global poपूर्णांकer */
#घोषणा sp	$29	/* stack poपूर्णांकer */
#घोषणा fp	$30	/* frame poपूर्णांकer */
#घोषणा s8	$30	/* same like fp! */
#घोषणा ra	$31	/* वापस address */

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#घोषणा zero	$0	/* wired zero */
#घोषणा AT	$at	/* assembler temp - upperहाल because of ".set at" */
#घोषणा v0	$2	/* वापस value - caller saved */
#घोषणा v1	$3
#घोषणा a0	$4	/* argument रेजिस्टरs */
#घोषणा a1	$5
#घोषणा a2	$6
#घोषणा a3	$7
#घोषणा a4	$8	/* arg reg 64 bit; caller saved in 32 bit */
#घोषणा ta0	$8
#घोषणा a5	$9
#घोषणा ta1	$9
#घोषणा a6	$10
#घोषणा ta2	$10
#घोषणा a7	$11
#घोषणा ta3	$11
#घोषणा t0	$12	/* caller saved */
#घोषणा t1	$13
#घोषणा t2	$14
#घोषणा t3	$15
#घोषणा s0	$16	/* callee saved */
#घोषणा s1	$17
#घोषणा s2	$18
#घोषणा s3	$19
#घोषणा s4	$20
#घोषणा s5	$21
#घोषणा s6	$22
#घोषणा s7	$23
#घोषणा t8	$24	/* caller saved */
#घोषणा t9	$25	/* callee address क्रम PIC/temp */
#घोषणा jp	$25	/* PIC jump रेजिस्टर */
#घोषणा k0	$26	/* kernel temporary */
#घोषणा k1	$27
#घोषणा gp	$28	/* global poपूर्णांकer - caller saved क्रम PIC */
#घोषणा sp	$29	/* stack poपूर्णांकer */
#घोषणा fp	$30	/* frame poपूर्णांकer */
#घोषणा s8	$30	/* callee saved */
#घोषणा ra	$31	/* वापस address */

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#पूर्ण_अगर /* _ASM_REGDEF_H */
