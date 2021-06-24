<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HEAD_32_H__
#घोषणा __HEAD_32_H__

#समावेश <यंत्र/ptrace.h>	/* क्रम STACK_FRAME_REGS_MARKER */

/*
 * Exception entry code.  This code runs with address translation
 * turned off, i.e. using physical addresses.
 * We assume sprg3 has the physical address of the current
 * task's thपढ़ो_काष्ठा.
 */
.macro EXCEPTION_PROLOG		trapno name handle_dar_dsisr=0
	EXCEPTION_PROLOG_0	handle_dar_dsisr=\handle_dar_dsisr
	EXCEPTION_PROLOG_1
	EXCEPTION_PROLOG_2	\टrapno \नame handle_dar_dsisr=\handle_dar_dsisr
.endm

.macro EXCEPTION_PROLOG_0 handle_dar_dsisr=0
	mtspr	SPRN_SPRG_SCRATCH0,r10
	mtspr	SPRN_SPRG_SCRATCH1,r11
	mfspr	r10, SPRN_SPRG_THREAD
	.अगर	\handle_dar_dsisr
#अगर_घोषित CONFIG_40x
	mfspr	r11, SPRN_DEAR
#अन्यथा
	mfspr	r11, SPRN_DAR
#पूर्ण_अगर
	stw	r11, DAR(r10)
#अगर_घोषित CONFIG_40x
	mfspr	r11, SPRN_ESR
#अन्यथा
	mfspr	r11, SPRN_DSISR
#पूर्ण_अगर
	stw	r11, DSISR(r10)
	.endअगर
	mfspr	r11, SPRN_SRR0
	stw	r11, SRR0(r10)
	mfspr	r11, SPRN_SRR1		/* check whether user or kernel */
	stw	r11, SRR1(r10)
	mfcr	r10
	andi.	r11, r11, MSR_PR
.endm

.macro EXCEPTION_PROLOG_1
	mtspr	SPRN_SPRG_SCRATCH2,r1
	subi	r1, r1, INT_FRAME_SIZE		/* use r1 अगर kernel */
	beq	1f
	mfspr	r1,SPRN_SPRG_THREAD
	lwz	r1,TASK_STACK-THREAD(r1)
	addi	r1, r1, THREAD_SIZE - INT_FRAME_SIZE
1:
#अगर_घोषित CONFIG_VMAP_STACK
	mtcrf	0x3f, r1
	bt	32 - THREAD_ALIGN_SHIFT, vmap_stack_overflow
#पूर्ण_अगर
.endm

.macro EXCEPTION_PROLOG_2 trapno name handle_dar_dsisr=0
#अगर_घोषित CONFIG_PPC_8xx
	.अगर	\handle_dar_dsisr
	li	r11, RPN_PATTERN
	mtspr	SPRN_DAR, r11	/* Tag DAR, to be used in DTLB Error */
	.endअगर
#पूर्ण_अगर
	LOAD_REG_IMMEDIATE(r11, MSR_KERNEL & ~MSR_RI) /* re-enable MMU */
	mtspr	SPRN_SRR1, r11
	lis	r11, 1f@h
	ori	r11, r11, 1f@l
	mtspr	SPRN_SRR0, r11
	mfspr	r11, SPRN_SPRG_SCRATCH2
	rfi

	.text
\नame\()_virt:
1:
	stw	r11,GPR1(r1)
	stw	r11,0(r1)
	mr	r11, r1
	stw	r10,_CCR(r11)		/* save रेजिस्टरs */
	stw	r12,GPR12(r11)
	stw	r9,GPR9(r11)
	mfspr	r10,SPRN_SPRG_SCRATCH0
	mfspr	r12,SPRN_SPRG_SCRATCH1
	stw	r10,GPR10(r11)
	stw	r12,GPR11(r11)
	mflr	r10
	stw	r10,_LINK(r11)
	mfspr	r12, SPRN_SPRG_THREAD
	tovirt(r12, r12)
	.अगर	\handle_dar_dsisr
	lwz	r10, DAR(r12)
	stw	r10, _DAR(r11)
	lwz	r10, DSISR(r12)
	stw	r10, _DSISR(r11)
	.endअगर
	lwz	r9, SRR1(r12)
	lwz	r12, SRR0(r12)
#अगर_घोषित CONFIG_40x
	rlwinm	r9,r9,0,14,12		/* clear MSR_WE (necessary?) */
#या_अगर defined(CONFIG_PPC_8xx)
	mtspr	SPRN_EID, r2		/* Set MSR_RI */
#अन्यथा
	li	r10, MSR_KERNEL		/* can take exceptions */
	mपंचांगsr	r10			/* (except क्रम mach check in rtas) */
#पूर्ण_अगर
	COMMON_EXCEPTION_PROLOG_END \टrapno
_ASM_NOKPROBE_SYMBOL(\नame\()_virt)
.endm

.macro COMMON_EXCEPTION_PROLOG_END trapno
	stw	r0,GPR0(r1)
	lis	r10,STACK_FRAME_REGS_MARKER@ha /* exception frame marker */
	addi	r10,r10,STACK_FRAME_REGS_MARKER@l
	stw	r10,8(r1)
	li	r10, \टrapno
	stw	r10,_TRAP(r1)
	SAVE_4GPRS(3, r1)
	SAVE_2GPRS(7, r1)
	SAVE_NVGPRS(r1)
	stw	r2,GPR2(r1)
	stw	r12,_NIP(r1)
	stw	r9,_MSR(r1)
	mfctr	r10
	mfspr	r2,SPRN_SPRG_THREAD
	stw	r10,_CTR(r1)
	tovirt(r2, r2)
	mfspr	r10,SPRN_XER
	addi	r2, r2, -THREAD
	stw	r10,_XER(r1)
	addi	r3,r1,STACK_FRAME_OVERHEAD
.endm

.macro prepare_transfer_to_handler
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	andi.	r12,r9,MSR_PR
	bne	777f
	bl	prepare_transfer_to_handler
777:
#पूर्ण_अगर
.endm

.macro SYSCALL_ENTRY trapno
	mfspr	r9, SPRN_SRR1
	mfspr	r10, SPRN_SRR0
	LOAD_REG_IMMEDIATE(r11, MSR_KERNEL)		/* can take exceptions */
	lis	r12, 1f@h
	ori	r12, r12, 1f@l
	mtspr	SPRN_SRR1, r11
	mtspr	SPRN_SRR0, r12
	mfspr	r12,SPRN_SPRG_THREAD
	mr	r11, r1
	lwz	r1,TASK_STACK-THREAD(r12)
	tovirt(r12, r12)
	addi	r1, r1, THREAD_SIZE - INT_FRAME_SIZE
	rfi
1:
	stw	r11,GPR1(r1)
	stw	r11,0(r1)
	mr	r11, r1
	stw	r10,_NIP(r11)
	mflr	r10
	stw	r10, _LINK(r11)
	mfcr	r10
	rlwinm	r10,r10,0,4,2	/* Clear SO bit in CR */
	stw	r10,_CCR(r11)		/* save रेजिस्टरs */
#अगर_घोषित CONFIG_40x
	rlwinm	r9,r9,0,14,12		/* clear MSR_WE (necessary?) */
#पूर्ण_अगर
	lis	r10,STACK_FRAME_REGS_MARKER@ha /* exception frame marker */
	stw	r2,GPR2(r11)
	addi	r10,r10,STACK_FRAME_REGS_MARKER@l
	stw	r9,_MSR(r11)
	li	r2, \टrapno
	stw	r10,8(r11)
	stw	r2,_TRAP(r11)
	SAVE_GPR(0, r11)
	SAVE_4GPRS(3, r11)
	SAVE_2GPRS(7, r11)
	addi	r2,r12,-THREAD
	b	transfer_to_syscall		/* jump to handler */
.endm

/*
 * Note: code which follows this uses cr0.eq (set अगर from kernel),
 * r11, r12 (SRR0), and r9 (SRR1).
 *
 * Note2: once we have set r1 we are in a position to take exceptions
 * again, and we could thus set MSR:RI at that poपूर्णांक.
 */

/*
 * Exception vectors.
 */
#अगर_घोषित CONFIG_PPC_BOOK3S
#घोषणा	START_EXCEPTION(n, label)		\
	__HEAD;					\
	. = n;					\
	DO_KVM n;				\
label:

#अन्यथा
#घोषणा	START_EXCEPTION(n, label)		\
	__HEAD;					\
	. = n;					\
label:

#पूर्ण_अगर

#घोषणा EXCEPTION(n, label, hdlr)		\
	START_EXCEPTION(n, label)		\
	EXCEPTION_PROLOG n label;		\
	prepare_transfer_to_handler;		\
	bl	hdlr;				\
	b	पूर्णांकerrupt_वापस

.macro vmap_stack_overflow_exception
	__HEAD
vmap_stack_overflow:
#अगर_घोषित CONFIG_SMP
	mfspr	r1, SPRN_SPRG_THREAD
	lwz	r1, TASK_CPU - THREAD(r1)
	slwi	r1, r1, 3
	addis	r1, r1, emergency_ctx@ha
#अन्यथा
	lis	r1, emergency_ctx@ha
#पूर्ण_अगर
	lwz	r1, emergency_ctx@l(r1)
	addi	r1, r1, THREAD_SIZE - INT_FRAME_SIZE
	EXCEPTION_PROLOG_2 0 vmap_stack_overflow
	prepare_transfer_to_handler
	bl	stack_overflow_exception
	b	पूर्णांकerrupt_वापस
.endm

#पूर्ण_अगर /* __HEAD_32_H__ */
