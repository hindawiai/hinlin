<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_ENTRY_H
#घोषणा __ASM_CSKY_ENTRY_H

#समावेश <यंत्र/setup.h>
#समावेश <abi/regdef.h>

#घोषणा LSAVE_PC	8
#घोषणा LSAVE_PSR	12
#घोषणा LSAVE_A0	24
#घोषणा LSAVE_A1	28
#घोषणा LSAVE_A2	32
#घोषणा LSAVE_A3	36
#घोषणा LSAVE_A4	40
#घोषणा LSAVE_A5	44

#घोषणा KSPTOUSP
#घोषणा USPTOKSP

#घोषणा usp cr<14, 1>

.macro SAVE_ALL epc_inc
	subi    sp, 152
	stw	tls, (sp, 0)
	stw	lr, (sp, 4)

	RD_MEH	lr
	WR_MEH	lr

	mfcr	lr, epc
	movi	tls, \epc_inc
	add	lr, tls
	stw	lr, (sp, 8)

	mfcr	lr, epsr
	stw	lr, (sp, 12)
	btsti   lr, 31
	bf      1f
	addi    lr, sp, 152
	br	2f
1:
	mfcr	lr, usp
2:
	stw	lr, (sp, 16)

	stw     a0, (sp, 20)
	stw     a0, (sp, 24)
	stw     a1, (sp, 28)
	stw     a2, (sp, 32)
	stw     a3, (sp, 36)

	addi	sp, 40
	sपंचांग	r4-r13, (sp)

	addi    sp, 40
	sपंचांग     r16-r30, (sp)
#अगर_घोषित CONFIG_CPU_HAS_HILO
	mfhi	lr
	stw	lr, (sp, 60)
	mflo	lr
	stw	lr, (sp, 64)
	mfcr	lr, cr14
	stw	lr, (sp, 68)
#पूर्ण_अगर
	subi	sp, 80
.endm

.macro	RESTORE_ALL
	ldw	tls, (sp, 0)
	ldw	lr, (sp, 4)
	ldw	a0, (sp, 8)
	mtcr	a0, epc
	ldw	a0, (sp, 12)
	mtcr	a0, epsr
	btsti   a0, 31
	ldw	a0, (sp, 16)
	mtcr	a0, usp
	mtcr	a0, ss0

#अगर_घोषित CONFIG_CPU_HAS_HILO
	ldw	a0, (sp, 140)
	mthi	a0
	ldw	a0, (sp, 144)
	mtlo	a0
	ldw	a0, (sp, 148)
	mtcr	a0, cr14
#पूर्ण_अगर

	ldw     a0, (sp, 24)
	ldw     a1, (sp, 28)
	ldw     a2, (sp, 32)
	ldw     a3, (sp, 36)

	addi	sp, 40
	ldm	r4-r13, (sp)
	addi    sp, 40
	ldm     r16-r30, (sp)
	addi    sp, 72
	bf	1f
	mfcr	sp, ss0
1:
	rte
.endm

.macro SAVE_REGS_FTRACE
	subi    sp, 152
	stw	tls, (sp, 0)
	stw	lr, (sp, 4)

	mfcr	lr, psr
	stw	lr, (sp, 12)

	addi    lr, sp, 152
	stw	lr, (sp, 16)

	stw     a0, (sp, 20)
	stw     a0, (sp, 24)
	stw     a1, (sp, 28)
	stw     a2, (sp, 32)
	stw     a3, (sp, 36)

	addi	sp, 40
	sपंचांग	r4-r13, (sp)

	addi    sp, 40
	sपंचांग     r16-r30, (sp)
#अगर_घोषित CONFIG_CPU_HAS_HILO
	mfhi	lr
	stw	lr, (sp, 60)
	mflo	lr
	stw	lr, (sp, 64)
	mfcr	lr, cr14
	stw	lr, (sp, 68)
#पूर्ण_अगर
	subi	sp, 80
.endm

.macro	RESTORE_REGS_FTRACE
	ldw	tls, (sp, 0)

#अगर_घोषित CONFIG_CPU_HAS_HILO
	ldw	a0, (sp, 140)
	mthi	a0
	ldw	a0, (sp, 144)
	mtlo	a0
	ldw	a0, (sp, 148)
	mtcr	a0, cr14
#पूर्ण_अगर

	ldw     a0, (sp, 24)
	ldw     a1, (sp, 28)
	ldw     a2, (sp, 32)
	ldw     a3, (sp, 36)

	addi	sp, 40
	ldm	r4-r13, (sp)
	addi    sp, 40
	ldm     r16-r30, (sp)
	addi    sp, 72
.endm

.macro SAVE_SWITCH_STACK
	subi    sp, 64
	sपंचांग	r4-r11, (sp)
	stw	lr,  (sp, 32)
	stw	r16, (sp, 36)
	stw	r17, (sp, 40)
	stw	r26, (sp, 44)
	stw	r27, (sp, 48)
	stw	r28, (sp, 52)
	stw	r29, (sp, 56)
	stw	r30, (sp, 60)
#अगर_घोषित CONFIG_CPU_HAS_HILO
	subi	sp, 16
	mfhi	lr
	stw	lr, (sp, 0)
	mflo	lr
	stw	lr, (sp, 4)
	mfcr	lr, cr14
	stw	lr, (sp, 8)
#पूर्ण_अगर
.endm

.macro RESTORE_SWITCH_STACK
#अगर_घोषित CONFIG_CPU_HAS_HILO
	ldw	lr, (sp, 0)
	mthi	lr
	ldw	lr, (sp, 4)
	mtlo	lr
	ldw	lr, (sp, 8)
	mtcr	lr, cr14
	addi	sp, 16
#पूर्ण_अगर
	ldm	r4-r11, (sp)
	ldw	lr,  (sp, 32)
	ldw	r16, (sp, 36)
	ldw	r17, (sp, 40)
	ldw	r26, (sp, 44)
	ldw	r27, (sp, 48)
	ldw	r28, (sp, 52)
	ldw	r29, (sp, 56)
	ldw	r30, (sp, 60)
	addi	sp, 64
.endm

/* MMU रेजिस्टरs चालकs. */
.macro RD_MIR rx
	mfcr	\लx, cr<0, 15>
.endm

.macro RD_MEH rx
	mfcr	\लx, cr<4, 15>
.endm

.macro RD_MCIR rx
	mfcr	\लx, cr<8, 15>
.endm

.macro RD_PGDR rx
	mfcr	\लx, cr<29, 15>
.endm

.macro RD_PGDR_K rx
	mfcr	\लx, cr<28, 15>
.endm

.macro WR_MEH rx
	mtcr	\लx, cr<4, 15>
.endm

.macro WR_MCIR rx
	mtcr	\लx, cr<8, 15>
.endm

#अगर_घोषित CONFIG_PAGE_OFFSET_80000000
#घोषणा MSA_SET cr<30, 15>
#घोषणा MSA_CLR cr<31, 15>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_OFFSET_A0000000
#घोषणा MSA_SET cr<31, 15>
#घोषणा MSA_CLR cr<30, 15>
#पूर्ण_अगर

.macro SETUP_MMU
	/* Init psr and enable ee */
	lrw	r6, DEFAULT_PSR_VALUE
	mtcr    r6, psr
	psrset  ee

	/* Invalid I/Dcache BTB BHT */
	movi	r6, 7
	lsli	r6, 16
	addi	r6, (1<<4) | 3
	mtcr	r6, cr17

	/* Invalid all TLB */
	bgeni   r6, 26
	mtcr	r6, cr<8, 15> /* Set MCIR */

	/* Check MMU on/off */
	mfcr	r6, cr18
	btsti	r6, 0
	bt	1f

	/* MMU off: setup mapping tlb entry */
	movi	r6, 0
	mtcr	r6, cr<6, 15> /* Set MPR with 4K page size */

	grs	r6, 1f /* Get current pa by PC */
	bmaski  r7, (PAGE_SHIFT + 1) /* r7 = 0x1fff */
	andn    r6, r7
	mtcr	r6, cr<4, 15> /* Set MEH */

	mov	r8, r6
	movi    r7, 0x00000006
	or      r8, r7
	mtcr	r8, cr<2, 15> /* Set MEL0 */
	movi    r7, 0x00001006
	or      r8, r7
	mtcr	r8, cr<3, 15> /* Set MEL1 */

	bgeni   r8, 28
	mtcr	r8, cr<8, 15> /* Set MCIR to ग_लिखो TLB */

	br	2f
1:
	/*
	 * MMU on: use origin MSA value from bootloader
	 *
	 * cr<30/31, 15> MSA रेजिस्टर क्रमmat:
	 * 31 - 29 | 28 - 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
	 *   BA     Reserved  SH  WA  B   SO SEC  C   D   V
	 */
	mfcr	r6, MSA_SET /* Get MSA */
2:
	lsri	r6, 29
	lsli	r6, 29
	addi	r6, 0x1ce
	mtcr	r6, MSA_SET /* Set MSA */

	movi    r6, 0
	mtcr	r6, MSA_CLR /* Clr MSA */

	/* enable MMU */
	mfcr    r6, cr18
	bseti	r6, 0
	mtcr    r6, cr18

	jmpi	3f /* jump to va */
3:
.endm
#पूर्ण_अगर /* __ASM_CSKY_ENTRY_H */
