<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Macro used to simplअगरy coding multi-line assembler.
 * Some of the bit test macro can simplअगरy करोwn to one line
 * depending on the mask value.
 *
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * All rights reserved.
 */
#अगर_अघोषित _ASM_NIOS2_ASMMACROS_H
#घोषणा _ASM_NIOS2_ASMMACROS_H
/*
 * ANDs reg2 with mask and places the result in reg1.
 *
 * You cannnot use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro ANDI32	reg1, reg2, mask
.अगर \mask & 0xffff
	.अगर \mask & 0xffff0000
		movhi	\लeg1, %hi(\mask)
		movui	\लeg1, %lo(\mask)
		and	\लeg1, \लeg1, \लeg2
	.अन्यथा
		andi	\लeg1, \लeg2, %lo(\mask)
	.endअगर
.अन्यथा
	andhi	\लeg1, \लeg2, %hi(\mask)
.endअगर
.endm

/*
 * ORs reg2 with mask and places the result in reg1.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro ORI32	reg1, reg2, mask
.अगर \mask & 0xffff
	.अगर \mask & 0xffff0000
		orhi	\लeg1, \लeg2, %hi(\mask)
		ori	\लeg1, \लeg2, %lo(\mask)
	.अन्यथा
		ori	\लeg1, \लeg2, %lo(\mask)
	.endअगर
.अन्यथा
	orhi	\लeg1, \लeg2, %hi(\mask)
.endअगर
.endm

/*
 * XORs reg2 with mask and places the result in reg1.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro XORI32	reg1, reg2, mask
.अगर \mask & 0xffff
	.अगर \mask & 0xffff0000
		xorhi	\लeg1, \लeg2, %hi(\mask)
		xori	\लeg1, \लeg1, %lo(\mask)
	.अन्यथा
		xori	\लeg1, \लeg2, %lo(\mask)
	.endअगर
.अन्यथा
	xorhi	\लeg1, \लeg2, %hi(\mask)
.endअगर
.endm

/*
 * This is a support macro क्रम BTBZ & BTBNZ.  It checks
 * the bit to make sure it is valid 32 value.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BT	reg1, reg2, bit
.अगर \मit > 31
	.err
.अन्यथा
	.अगर \मit < 16
		andi	\लeg1, \लeg2, (1 << \मit)
	.अन्यथा
		andhi	\लeg1, \लeg2, (1 << (\मit - 16))
	.endअगर
.endअगर
.endm

/*
 * Tests the bit in reg2 and branches to label अगर the
 * bit is zero.  The result of the bit test is stored in reg1.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTBZ	reg1, reg2, bit, label
	BT	\लeg1, \लeg2, \मit
	beq	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and branches to label अगर the
 * bit is non-zero.  The result of the bit test is stored in reg1.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTBNZ	reg1, reg2, bit, label
	BT	\लeg1, \लeg2, \मit
	bne	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and then compliments the bit in reg2.
 * The result of the bit test is stored in reg1.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTC	reg1, reg2, bit
.अगर \मit > 31
	.err
.अन्यथा
	.अगर \मit < 16
		andi	\लeg1, \लeg2, (1 << \मit)
		xori	\लeg2, \लeg2, (1 << \मit)
	.अन्यथा
		andhi	\लeg1, \लeg2, (1 << (\मit - 16))
		xorhi	\लeg2, \लeg2, (1 << (\मit - 16))
	.endअगर
.endअगर
.endm

/*
 * Tests the bit in reg2 and then sets the bit in reg2.
 * The result of the bit test is stored in reg1.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTS	reg1, reg2, bit
.अगर \मit > 31
	.err
.अन्यथा
	.अगर \मit < 16
		andi	\लeg1, \लeg2, (1 << \मit)
		ori	\लeg2, \लeg2, (1 << \मit)
	.अन्यथा
		andhi	\लeg1, \लeg2, (1 << (\मit - 16))
		orhi	\लeg2, \लeg2, (1 << (\मit - 16))
	.endअगर
.endअगर
.endm

/*
 * Tests the bit in reg2 and then resets the bit in reg2.
 * The result of the bit test is stored in reg1.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTR	reg1, reg2, bit
.अगर \मit > 31
	.err
.अन्यथा
	.अगर \मit < 16
		andi	\लeg1, \लeg2, (1 << \मit)
		andi	\लeg2, \लeg2, %lo(~(1 << \मit))
	.अन्यथा
		andhi	\लeg1, \लeg2, (1 << (\मit - 16))
		andhi	\लeg2, \लeg2, %lo(~(1 << (\मit - 16)))
	.endअगर
.endअगर
.endm

/*
 * Tests the bit in reg2 and then compliments the bit in reg2.
 * The result of the bit test is stored in reg1.  If the
 * original bit was zero it branches to label.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTCBZ	reg1, reg2, bit, label
	BTC	\लeg1, \लeg2, \मit
	beq	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and then compliments the bit in reg2.
 * The result of the bit test is stored in reg1.  If the
 * original bit was non-zero it branches to label.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTCBNZ	reg1, reg2, bit, label
	BTC	\लeg1, \लeg2, \मit
	bne	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and then sets the bit in reg2.
 * The result of the bit test is stored in reg1.  If the
 * original bit was zero it branches to label.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTSBZ	reg1, reg2, bit, label
	BTS	\लeg1, \लeg2, \मit
	beq	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and then sets the bit in reg2.
 * The result of the bit test is stored in reg1.  If the
 * original bit was non-zero it branches to label.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTSBNZ	reg1, reg2, bit, label
	BTS	\लeg1, \लeg2, \मit
	bne	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and then resets the bit in reg2.
 * The result of the bit test is stored in reg1.  If the
 * original bit was zero it branches to label.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTRBZ	reg1, reg2, bit, label
	BTR	\लeg1, \लeg2, \मit
	bne	\लeg1, r0, \label
.endm

/*
 * Tests the bit in reg2 and then resets the bit in reg2.
 * The result of the bit test is stored in reg1.  If the
 * original bit was non-zero it branches to label.
 *
 * It is NOT safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro BTRBNZ	reg1, reg2, bit, label
	BTR	\लeg1, \लeg2, \मit
	bne	\लeg1, r0, \label
.endm

/*
 * Tests the bits in mask against reg2 stores the result in reg1.
 * If the all the bits in the mask are zero it branches to label.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro TSTBZ	reg1, reg2, mask, label
	ANDI32	\लeg1, \लeg2, \mask
	beq	\लeg1, r0, \label
.endm

/*
 * Tests the bits in mask against reg2 stores the result in reg1.
 * If the any of the bits in the mask are 1 it branches to label.
 *
 * It is safe to use the same रेजिस्टर क्रम reg1 & reg2.
 */

.macro TSTBNZ	reg1, reg2, mask, label
	ANDI32	\लeg1, \लeg2, \mask
	bne	\लeg1, r0, \label
.endm

/*
 * Pushes reg onto the stack.
 */

.macro PUSH	reg
	addi	sp, sp, -4
	stw	\लeg, 0(sp)
.endm

/*
 * Pops the top of the stack पूर्णांकo reg.
 */

.macro POP	reg
	ldw	\लeg, 0(sp)
	addi	sp, sp, 4
.endm


#पूर्ण_अगर /* _ASM_NIOS2_ASMMACROS_H */
