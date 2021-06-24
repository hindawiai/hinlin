<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र/assembler.h>
#समावेश <यंत्र/unwind.h>

#अगर __LINUX_ARM_ARCH__ >= 6
	.macro	bitop, name, instr
ENTRY(	\नame		)
UNWIND(	.fnstart	)
	ands	ip, r1, #3
	strbne	r1, [ip]		@ निश्चित word-aligned
	mov	r2, #1
	and	r3, r0, #31		@ Get bit offset
	mov	r0, r0, lsr #5
	add	r1, r1, r0, lsl #2	@ Get word offset
#अगर __LINUX_ARM_ARCH__ >= 7 && defined(CONFIG_SMP)
	.arch_extension	mp
	ALT_SMP(W(pldw)	[r1])
	ALT_UP(W(nop))
#पूर्ण_अगर
	mov	r3, r2, lsl r3
1:	ldrex	r2, [r1]
	\instr	r2, r2, r3
	strex	r0, r2, [r1]
	cmp	r0, #0
	bne	1b
	bx	lr
UNWIND(	.fnend		)
ENDPROC(\नame		)
	.endm

	.macro	testop, name, instr, store
ENTRY(	\नame		)
UNWIND(	.fnstart	)
	ands	ip, r1, #3
	strbne	r1, [ip]		@ निश्चित word-aligned
	mov	r2, #1
	and	r3, r0, #31		@ Get bit offset
	mov	r0, r0, lsr #5
	add	r1, r1, r0, lsl #2	@ Get word offset
	mov	r3, r2, lsl r3		@ create mask
	smp_dmb
#अगर __LINUX_ARM_ARCH__ >= 7 && defined(CONFIG_SMP)
	.arch_extension	mp
	ALT_SMP(W(pldw)	[r1])
	ALT_UP(W(nop))
#पूर्ण_अगर
1:	ldrex	r2, [r1]
	ands	r0, r2, r3		@ save old value of bit
	\instr	r2, r2, r3		@ toggle bit
	strex	ip, r2, [r1]
	cmp	ip, #0
	bne	1b
	smp_dmb
	cmp	r0, #0
	movne	r0, #1
2:	bx	lr
UNWIND(	.fnend		)
ENDPROC(\नame		)
	.endm
#अन्यथा
	.macro	bitop, name, instr
ENTRY(	\नame		)
UNWIND(	.fnstart	)
	ands	ip, r1, #3
	strbne	r1, [ip]		@ निश्चित word-aligned
	and	r2, r0, #31
	mov	r0, r0, lsr #5
	mov	r3, #1
	mov	r3, r3, lsl r2
	save_and_disable_irqs ip
	ldr	r2, [r1, r0, lsl #2]
	\instr	r2, r2, r3
	str	r2, [r1, r0, lsl #2]
	restore_irqs ip
	ret	lr
UNWIND(	.fnend		)
ENDPROC(\नame		)
	.endm

/**
 * testop - implement a test_and_xxx_bit operation.
 * @instr: operational inकाष्ठाion
 * @store: store inकाष्ठाion
 *
 * Note: we can trivially conditionalise the store inकाष्ठाion
 * to aव्योम dirtying the data cache.
 */
	.macro	testop, name, instr, store
ENTRY(	\नame		)
UNWIND(	.fnstart	)
	ands	ip, r1, #3
	strbne	r1, [ip]		@ निश्चित word-aligned
	and	r3, r0, #31
	mov	r0, r0, lsr #5
	save_and_disable_irqs ip
	ldr	r2, [r1, r0, lsl #2]!
	mov	r0, #1
	tst	r2, r0, lsl r3
	\instr	r2, r2, r0, lsl r3
	\store	r2, [r1]
	moveq	r0, #0
	restore_irqs ip
	ret	lr
UNWIND(	.fnend		)
ENDPROC(\नame		)
	.endm
#पूर्ण_अगर
