<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/assembler.h
 *
 *  Copyright (C) 1996-2000 Russell King
 *
 *  This file contains arm architecture specअगरic defines
 *  क्रम the dअगरferent processors.
 *
 *  Do not include any C declarations in this file - it is included by
 *  assembler source.
 */
#अगर_अघोषित __ASM_ASSEMBLER_H__
#घोषणा __ASM_ASSEMBLER_H__

#अगर_अघोषित __ASSEMBLY__
#त्रुटि "Only include this from assembly code"
#पूर्ण_अगर

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/opcodes-virt.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/uaccess-यंत्र.h>

#घोषणा IOMEM(x)	(x)

/*
 * Endian independent macros क्रम shअगरting bytes within रेजिस्टरs.
 */
#अगर_अघोषित __ARMEB__
#घोषणा lspull          lsr
#घोषणा lspush          lsl
#घोषणा get_byte_0      lsl #0
#घोषणा get_byte_1	lsr #8
#घोषणा get_byte_2	lsr #16
#घोषणा get_byte_3	lsr #24
#घोषणा put_byte_0      lsl #0
#घोषणा put_byte_1	lsl #8
#घोषणा put_byte_2	lsl #16
#घोषणा put_byte_3	lsl #24
#अन्यथा
#घोषणा lspull          lsl
#घोषणा lspush          lsr
#घोषणा get_byte_0	lsr #24
#घोषणा get_byte_1	lsr #16
#घोषणा get_byte_2	lsr #8
#घोषणा get_byte_3      lsl #0
#घोषणा put_byte_0	lsl #24
#घोषणा put_byte_1	lsl #16
#घोषणा put_byte_2	lsl #8
#घोषणा put_byte_3      lsl #0
#पूर्ण_अगर

/* Select code क्रम any configuration running in BE8 mode */
#अगर_घोषित CONFIG_CPU_ENDIAN_BE8
#घोषणा ARM_BE8(code...) code
#अन्यथा
#घोषणा ARM_BE8(code...)
#पूर्ण_अगर

/*
 * Data preload क्रम architectures that support it
 */
#अगर __LINUX_ARM_ARCH__ >= 5
#घोषणा PLD(code...)	code
#अन्यथा
#घोषणा PLD(code...)
#पूर्ण_अगर

/*
 * This can be used to enable code to cacheline align the destination
 * poपूर्णांकer when bulk writing to memory.  Experiments on StrongARM and
 * XScale didn't show this a worthजबतक thing to करो when the cache is not
 * set to ग_लिखो-allocate (this would need further testing on XScale when WA
 * is used).
 *
 * On Feroceon there is much to gain however, regardless of cache mode.
 */
#अगर_घोषित CONFIG_CPU_FEROCEON
#घोषणा CALGN(code...) code
#अन्यथा
#घोषणा CALGN(code...)
#पूर्ण_अगर

#घोषणा IMM12_MASK 0xfff

/*
 * Enable and disable पूर्णांकerrupts
 */
#अगर __LINUX_ARM_ARCH__ >= 6
	.macro	disable_irq_notrace
	cpsid	i
	.endm

	.macro	enable_irq_notrace
	cpsie	i
	.endm
#अन्यथा
	.macro	disable_irq_notrace
	msr	cpsr_c, #PSR_I_BIT | SVC_MODE
	.endm

	.macro	enable_irq_notrace
	msr	cpsr_c, #SVC_MODE
	.endm
#पूर्ण_अगर

	.macro यंत्र_trace_hardirqs_off, save=1
#अगर defined(CONFIG_TRACE_IRQFLAGS)
	.अगर \save
	sपंचांगdb   sp!, अणुr0-r3, ip, lrपूर्ण
	.endअगर
	bl	trace_hardirqs_off
	.अगर \save
	ldmia	sp!, अणुr0-r3, ip, lrपूर्ण
	.endअगर
#पूर्ण_अगर
	.endm

	.macro यंत्र_trace_hardirqs_on, cond=al, save=1
#अगर defined(CONFIG_TRACE_IRQFLAGS)
	/*
	 * actually the रेजिस्टरs should be pushed and pop'd conditionally, but
	 * after bl the flags are certainly clobbered
	 */
	.अगर \save
	sपंचांगdb   sp!, अणुr0-r3, ip, lrपूर्ण
	.endअगर
	bl\cond	trace_hardirqs_on
	.अगर \save
	ldmia	sp!, अणुr0-r3, ip, lrपूर्ण
	.endअगर
#पूर्ण_अगर
	.endm

	.macro disable_irq, save=1
	disable_irq_notrace
	यंत्र_trace_hardirqs_off \save
	.endm

	.macro enable_irq
	यंत्र_trace_hardirqs_on
	enable_irq_notrace
	.endm
/*
 * Save the current IRQ state and disable IRQs.  Note that this macro
 * assumes FIQs are enabled, and that the processor is in SVC mode.
 */
	.macro	save_and_disable_irqs, oldcpsr
#अगर_घोषित CONFIG_CPU_V7M
	mrs	\oldcpsr, primask
#अन्यथा
	mrs	\oldcpsr, cpsr
#पूर्ण_अगर
	disable_irq
	.endm

	.macro	save_and_disable_irqs_notrace, oldcpsr
#अगर_घोषित CONFIG_CPU_V7M
	mrs	\oldcpsr, primask
#अन्यथा
	mrs	\oldcpsr, cpsr
#पूर्ण_अगर
	disable_irq_notrace
	.endm

/*
 * Restore पूर्णांकerrupt state previously stored in a रेजिस्टर.  We करोn't
 * guarantee that this will preserve the flags.
 */
	.macro	restore_irqs_notrace, oldcpsr
#अगर_घोषित CONFIG_CPU_V7M
	msr	primask, \oldcpsr
#अन्यथा
	msr	cpsr_c, \oldcpsr
#पूर्ण_अगर
	.endm

	.macro restore_irqs, oldcpsr
	tst	\oldcpsr, #PSR_I_BIT
	यंत्र_trace_hardirqs_on cond=eq
	restore_irqs_notrace \oldcpsr
	.endm

/*
 * Assembly version of "adr rd, BSYM(sym)".  This should only be used to
 * reference local symbols in the same assembly file which are to be
 * resolved by the assembler.  Other usage is undefined.
 */
	.irp	c,,eq,ne,cs,cc,mi,pl,vs,vc,hi,ls,ge,lt,gt,le,hs,lo
	.macro	badr\c, rd, sym
#अगर_घोषित CONFIG_THUMB2_KERNEL
	adr\c	\लd, \sym + 1
#अन्यथा
	adr\c	\लd, \sym
#पूर्ण_अगर
	.endm
	.endr

/*
 * Get current thपढ़ो_info.
 */
	.macro	get_thपढ़ो_info, rd
 ARM(	mov	\लd, sp, lsr #THREAD_SIZE_ORDER + PAGE_SHIFT	)
 THUMB(	mov	\लd, sp			)
 THUMB(	lsr	\लd, \लd, #THREAD_SIZE_ORDER + PAGE_SHIFT	)
	mov	\लd, \लd, lsl #THREAD_SIZE_ORDER + PAGE_SHIFT
	.endm

/*
 * Increment/decrement the preempt count.
 */
#अगर_घोषित CONFIG_PREEMPT_COUNT
	.macro	inc_preempt_count, ti, पंचांगp
	ldr	\टmp, [\टi, #TI_PREEMPT]	@ get preempt count
	add	\टmp, \टmp, #1			@ increment it
	str	\टmp, [\टi, #TI_PREEMPT]
	.endm

	.macro	dec_preempt_count, ti, पंचांगp
	ldr	\टmp, [\टi, #TI_PREEMPT]	@ get preempt count
	sub	\टmp, \टmp, #1			@ decrement it
	str	\टmp, [\टi, #TI_PREEMPT]
	.endm

	.macro	dec_preempt_count_ti, ti, पंचांगp
	get_thपढ़ो_info \टi
	dec_preempt_count \टi, \टmp
	.endm
#अन्यथा
	.macro	inc_preempt_count, ti, पंचांगp
	.endm

	.macro	dec_preempt_count, ti, पंचांगp
	.endm

	.macro	dec_preempt_count_ti, ti, पंचांगp
	.endm
#पूर्ण_अगर

#घोषणा USERL(l, x...)				\
9999:	x;					\
	.pushsection __ex_table,"a";		\
	.align	3;				\
	.दीर्घ	9999b,l;			\
	.popsection

#घोषणा USER(x...)	USERL(9001f, x)

#अगर_घोषित CONFIG_SMP
#घोषणा ALT_SMP(instr...)					\
9998:	instr
/*
 * Note: अगर you get assembler errors from ALT_UP() when building with
 * CONFIG_THUMB2_KERNEL, you almost certainly need to use
 * ALT_SMP( W(instr) ... )
 */
#घोषणा ALT_UP(instr...)					\
	.pushsection ".alt.smp.init", "a"			;\
	.दीर्घ	9998b - .					;\
9997:	instr							;\
	.अगर . - 9997b == 2					;\
		nop						;\
	.endअगर							;\
	.अगर . - 9997b != 4					;\
		.error "ALT_UP() content must assemble to exactly 4 bytes";\
	.endअगर							;\
	.popsection
#घोषणा ALT_UP_B(label)					\
	.pushsection ".alt.smp.init", "a"			;\
	.दीर्घ	9998b - .					;\
	W(b)	. + (label - 9998b)					;\
	.popsection
#अन्यथा
#घोषणा ALT_SMP(instr...)
#घोषणा ALT_UP(instr...) instr
#घोषणा ALT_UP_B(label) b label
#पूर्ण_अगर

/*
 * Inकाष्ठाion barrier
 */
	.macro	instr_sync
#अगर __LINUX_ARM_ARCH__ >= 7
	isb
#या_अगर __LINUX_ARM_ARCH__ == 6
	mcr	p15, 0, r0, c7, c5, 4
#पूर्ण_अगर
	.endm

/*
 * SMP data memory barrier
 */
	.macro	smp_dmb mode
#अगर_घोषित CONFIG_SMP
#अगर __LINUX_ARM_ARCH__ >= 7
	.अगरeqs "\mode","arm"
	ALT_SMP(dmb	ish)
	.अन्यथा
	ALT_SMP(W(dmb)	ish)
	.endअगर
#या_अगर __LINUX_ARM_ARCH__ == 6
	ALT_SMP(mcr	p15, 0, r0, c7, c10, 5)	@ dmb
#अन्यथा
#त्रुटि Incompatible SMP platक्रमm
#पूर्ण_अगर
	.अगरeqs "\mode","arm"
	ALT_UP(nop)
	.अन्यथा
	ALT_UP(W(nop))
	.endअगर
#पूर्ण_अगर
	.endm

#अगर defined(CONFIG_CPU_V7M)
	/*
	 * seपंचांगode is used to निश्चित to be in svc mode during boot. For v7-M
	 * this is करोne in __v7m_setup, so seपंचांगode can be empty here.
	 */
	.macro	seपंचांगode, mode, reg
	.endm
#या_अगर defined(CONFIG_THUMB2_KERNEL)
	.macro	seपंचांगode, mode, reg
	mov	\लeg, #\mode
	msr	cpsr_c, \लeg
	.endm
#अन्यथा
	.macro	seपंचांगode, mode, reg
	msr	cpsr_c, #\mode
	.endm
#पूर्ण_अगर

/*
 * Helper macro to enter SVC mode cleanly and mask पूर्णांकerrupts. reg is
 * a scratch रेजिस्टर क्रम the macro to overग_लिखो.
 *
 * This macro is पूर्णांकended क्रम क्रमcing the CPU पूर्णांकo SVC mode at boot समय.
 * you cannot वापस to the original mode.
 */
.macro safe_svcmode_maskall reg:req
#अगर __LINUX_ARM_ARCH__ >= 6 && !defined(CONFIG_CPU_V7M)
	mrs	\लeg , cpsr
	eor	\लeg, \लeg, #HYP_MODE
	tst	\लeg, #MODE_MASK
	bic	\लeg , \लeg , #MODE_MASK
	orr	\लeg , \लeg , #PSR_I_BIT | PSR_F_BIT | SVC_MODE
THUMB(	orr	\लeg , \लeg , #PSR_T_BIT	)
	bne	1f
	orr	\लeg, \लeg, #PSR_A_BIT
	badr	lr, 2f
	msr	spsr_cxsf, \लeg
	__MSR_ELR_HYP(14)
	__ERET
1:	msr	cpsr_c, \लeg
2:
#अन्यथा
/*
 * workaround क्रम possibly broken pre-v6 hardware
 * (akita, Sharp Zaurus C-1000, PXA270-based)
 */
	seपंचांगode	PSR_F_BIT | PSR_I_BIT | SVC_MODE, \लeg
#पूर्ण_अगर
.endm

/*
 * STRT/LDRT access macros with ARM and Thumb-2 variants
 */
#अगर_घोषित CONFIG_THUMB2_KERNEL

	.macro	usraccoff, instr, reg, ptr, inc, off, cond, पात, t=TUSER()
9999:
	.अगर	\inc == 1
	\instr\()b\ट\cond\().w \लeg, [\ptr, #\off]
	.अन्यथाअगर	\inc == 4
	\instr\ट\cond\().w \लeg, [\ptr, #\off]
	.अन्यथा
	.error	"Unsupported inc macro argument"
	.endअगर

	.pushsection __ex_table,"a"
	.align	3
	.दीर्घ	9999b, \चbort
	.popsection
	.endm

	.macro	usracc, instr, reg, ptr, inc, cond, rept, पात
	@ explicit IT inकाष्ठाion needed because of the label
	@ पूर्णांकroduced by the USER macro
	.अगरnc	\cond,al
	.अगर	\लept == 1
	itt	\cond
	.अन्यथाअगर	\लept == 2
	ittt	\cond
	.अन्यथा
	.error	"Unsupported rept macro argument"
	.endअगर
	.endअगर

	@ Slightly optimised to aव्योम incrementing the poपूर्णांकer twice
	usraccoff \instr, \लeg, \ptr, \inc, 0, \cond, \चbort
	.अगर	\लept == 2
	usraccoff \instr, \लeg, \ptr, \inc, \inc, \cond, \चbort
	.endअगर

	add\cond \ptr, #\लept * \inc
	.endm

#अन्यथा	/* !CONFIG_THUMB2_KERNEL */

	.macro	usracc, instr, reg, ptr, inc, cond, rept, पात, t=TUSER()
	.rept	\लept
9999:
	.अगर	\inc == 1
	\instr\()b\ट\cond \लeg, [\ptr], #\inc
	.अन्यथाअगर	\inc == 4
	\instr\ट\cond \लeg, [\ptr], #\inc
	.अन्यथा
	.error	"Unsupported inc macro argument"
	.endअगर

	.pushsection __ex_table,"a"
	.align	3
	.दीर्घ	9999b, \चbort
	.popsection
	.endr
	.endm

#पूर्ण_अगर	/* CONFIG_THUMB2_KERNEL */

	.macro	strusr, reg, ptr, inc, cond=al, rept=1, पात=9001f
	usracc	str, \लeg, \ptr, \inc, \cond, \लept, \चbort
	.endm

	.macro	ldrusr, reg, ptr, inc, cond=al, rept=1, पात=9001f
	usracc	ldr, \लeg, \ptr, \inc, \cond, \लept, \चbort
	.endm

/* Utility macro क्रम declaring string literals */
	.macro	string name:req, string
	.type \नame , #object
\नame:
	.asciz "\string"
	.size \नame , . - \नame
	.endm

	.irp	c,,eq,ne,cs,cc,mi,pl,vs,vc,hi,ls,ge,lt,gt,le,hs,lo
	.macro	ret\c, reg
#अगर __LINUX_ARM_ARCH__ < 6
	mov\c	pc, \लeg
#अन्यथा
	.अगरeqs	"\reg", "lr"
	bx\c	\लeg
	.अन्यथा
	mov\c	pc, \लeg
	.endअगर
#पूर्ण_अगर
	.endm
	.endr

	.macro	ret.w, reg
	ret	\लeg
#अगर_घोषित CONFIG_THUMB2_KERNEL
	nop
#पूर्ण_अगर
	.endm

	.macro	bug, msg, line
#अगर_घोषित CONFIG_THUMB2_KERNEL
1:	.inst	0xde02
#अन्यथा
1:	.inst	0xe7f001f2
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
	.pushsection .rodata.str, "aMS", %progbits, 1
2:	.asciz	"\msg"
	.popsection
	.pushsection __bug_table, "aw"
	.align	2
	.word	1b, 2b
	.hword	\line
	.popsection
#पूर्ण_अगर
	.endm

#अगर_घोषित CONFIG_KPROBES
#घोषणा _ASM_NOKPROBE(entry)				\
	.pushsection "_kprobe_blacklist", "aw" ;	\
	.balign 4 ;					\
	.दीर्घ entry;					\
	.popsection
#अन्यथा
#घोषणा _ASM_NOKPROBE(entry)
#पूर्ण_अगर

	.macro		__adldst_l, op, reg, sym, पंचांगp, c
	.अगर		__LINUX_ARM_ARCH__ < 7
	ldr\c		\टmp, .La\@
	.subsection	1
	.align		2
.La\@:	.दीर्घ		\sym - .Lpc\@
	.previous
	.अन्यथा
	.अगरnb		\c
 THUMB(	ittt		\c			)
	.endअगर
	movw\c		\टmp, #:lower16:\sym - .Lpc\@
	movt\c		\टmp, #:upper16:\sym - .Lpc\@
	.endअगर

#अगर_अघोषित CONFIG_THUMB2_KERNEL
	.set		.Lpc\@, . + 8			// PC bias
	.अगरc		\op, add
	add\c		\लeg, \टmp, pc
	.अन्यथा
	\op\c		\लeg, [pc, \टmp]
	.endअगर
#अन्यथा
.Lb\@:	add\c		\टmp, \टmp, pc
	/*
	 * In Thumb-2 builds, the PC bias depends on whether we are currently
	 * emitting पूर्णांकo a .arm or a .thumb section. The size of the add opcode
	 * above will be 2 bytes when emitting in Thumb mode and 4 bytes when
	 * emitting in ARM mode, so let's use this to account क्रम the bias.
	 */
	.set		.Lpc\@, . + (. - .Lb\@)

	.अगरnc		\op, add
	\op\c		\लeg, [\टmp]
	.endअगर
#पूर्ण_अगर
	.endm

	/*
	 * mov_l - move a स्थिरant value or [relocated] address पूर्णांकo a रेजिस्टर
	 */
	.macro		mov_l, dst:req, imm:req
	.अगर		__LINUX_ARM_ARCH__ < 7
	ldr		\dst, =\imm
	.अन्यथा
	movw		\dst, #:lower16:\imm
	movt		\dst, #:upper16:\imm
	.endअगर
	.endm

	/*
	 * adr_l - adr pseuकरो-op with unlimited range
	 *
	 * @dst: destination रेजिस्टर
	 * @sym: name of the symbol
	 * @cond: conditional opcode suffix
	 */
	.macro		adr_l, dst:req, sym:req, cond
	__adldst_l	add, \dst, \sym, \dst, \cond
	.endm

	/*
	 * ldr_l - ldr <literal> pseuकरो-op with unlimited range
	 *
	 * @dst: destination रेजिस्टर
	 * @sym: name of the symbol
	 * @cond: conditional opcode suffix
	 */
	.macro		ldr_l, dst:req, sym:req, cond
	__adldst_l	ldr, \dst, \sym, \dst, \cond
	.endm

	/*
	 * str_l - str <literal> pseuकरो-op with unlimited range
	 *
	 * @src: source रेजिस्टर
	 * @sym: name of the symbol
	 * @पंचांगp: mandatory scratch रेजिस्टर
	 * @cond: conditional opcode suffix
	 */
	.macro		str_l, src:req, sym:req, पंचांगp:req, cond
	__adldst_l	str, \src, \sym, \टmp, \cond
	.endm

	/*
	 * rev_l - byte-swap a 32-bit value
	 *
	 * @val: source/destination रेजिस्टर
	 * @पंचांगp: scratch रेजिस्टर
	 */
	.macro		rev_l, val:req, पंचांगp:req
	.अगर		__LINUX_ARM_ARCH__ < 6
	eor		\टmp, \खal, \खal, ror #16
	bic		\टmp, \टmp, #0x00ff0000
	mov		\खal, \खal, ror #8
	eor		\खal, \खal, \टmp, lsr #8
	.अन्यथा
	rev		\खal, \खal
	.endअगर
	.endm

#पूर्ण_अगर /* __ASM_ASSEMBLER_H__ */
