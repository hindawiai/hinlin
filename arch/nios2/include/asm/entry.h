<शैली गुरु>
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_ENTRY_H
#घोषणा _ASM_NIOS2_ENTRY_H

#अगर_घोषित __ASSEMBLY__

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/यंत्र-offsets.h>

/*
 * Standard Nios2 पूर्णांकerrupt entry and निकास macros.
 * Must be called with पूर्णांकerrupts disabled.
 */
.macro SAVE_ALL
	rdctl	r24, estatus
	andi	r24, r24, ESTATUS_EU
	beq	r24, r0, 1f /* In supervisor mode, alपढ़ोy on kernel stack */

	movia	r24, _current_thपढ़ो	/* Switch to current kernel stack */
	ldw	r24, 0(r24)		/* using the thपढ़ो_info */
	addi	r24, r24, THREAD_SIZE-PT_REGS_SIZE
	stw	sp, PT_SP(r24)		/* Save user stack beक्रमe changing */
	mov	sp, r24
	br	2f

1 :	mov	r24, sp
	addi	sp, sp, -PT_REGS_SIZE	/* Backup the kernel stack poपूर्णांकer */
	stw	r24, PT_SP(sp)
2 :	stw	r1, PT_R1(sp)
	stw	r2, PT_R2(sp)
	stw	r3, PT_R3(sp)
	stw	r4, PT_R4(sp)
	stw	r5, PT_R5(sp)
	stw	r6, PT_R6(sp)
	stw	r7, PT_R7(sp)
	stw	r8, PT_R8(sp)
	stw	r9, PT_R9(sp)
	stw	r10, PT_R10(sp)
	stw	r11, PT_R11(sp)
	stw	r12, PT_R12(sp)
	stw	r13, PT_R13(sp)
	stw	r14, PT_R14(sp)
	stw	r15, PT_R15(sp)
	stw	r2, PT_ORIG_R2(sp)
	stw	r7, PT_ORIG_R7(sp)

	stw	ra, PT_RA(sp)
	stw	fp, PT_FP(sp)
	stw	gp, PT_GP(sp)
	rdctl	r24, estatus
	stw	r24, PT_ESTATUS(sp)
	stw	ea, PT_EA(sp)
.endm

.macro RESTORE_ALL
	ldw	r1, PT_R1(sp)		/* Restore रेजिस्टरs */
	ldw	r2, PT_R2(sp)
	ldw	r3, PT_R3(sp)
	ldw	r4, PT_R4(sp)
	ldw	r5, PT_R5(sp)
	ldw	r6, PT_R6(sp)
	ldw	r7, PT_R7(sp)
	ldw	r8, PT_R8(sp)
	ldw	r9, PT_R9(sp)
	ldw	r10, PT_R10(sp)
	ldw	r11, PT_R11(sp)
	ldw	r12, PT_R12(sp)
	ldw	r13, PT_R13(sp)
	ldw	r14, PT_R14(sp)
	ldw	r15, PT_R15(sp)
	ldw	ra, PT_RA(sp)
	ldw	fp, PT_FP(sp)
	ldw	gp, PT_GP(sp)
	ldw	r24, PT_ESTATUS(sp)
	wrctl	estatus, r24
	ldw	ea, PT_EA(sp)
	ldw	sp, PT_SP(sp)		/* Restore sp last */
.endm

.macro	SAVE_SWITCH_STACK
	addi	sp, sp, -SWITCH_STACK_SIZE
	stw	r16, SW_R16(sp)
	stw	r17, SW_R17(sp)
	stw	r18, SW_R18(sp)
	stw	r19, SW_R19(sp)
	stw	r20, SW_R20(sp)
	stw	r21, SW_R21(sp)
	stw	r22, SW_R22(sp)
	stw	r23, SW_R23(sp)
	stw	fp, SW_FP(sp)
	stw	gp, SW_GP(sp)
	stw	ra, SW_RA(sp)
.endm

.macro	RESTORE_SWITCH_STACK
	ldw	r16, SW_R16(sp)
	ldw	r17, SW_R17(sp)
	ldw	r18, SW_R18(sp)
	ldw	r19, SW_R19(sp)
	ldw	r20, SW_R20(sp)
	ldw	r21, SW_R21(sp)
	ldw	r22, SW_R22(sp)
	ldw	r23, SW_R23(sp)
	ldw	fp, SW_FP(sp)
	ldw	gp, SW_GP(sp)
	ldw	ra, SW_RA(sp)
	addi	sp, sp, SWITCH_STACK_SIZE
.endm

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_NIOS2_ENTRY_H */
