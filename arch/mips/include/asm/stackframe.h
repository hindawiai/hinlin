<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 99, 2001 Ralf Baechle
 * Copyright (C) 1994, 1995, 1996 Paul M. Antoine.
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2007  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_STACKFRAME_H
#घोषणा _ASM_STACKFRAME_H

#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/यंत्रmacro.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/thपढ़ो_info.h>

/* Make the addition of cfi info a little easier. */
	.macro cfi_rel_offset reg offset=0 करोcfi=0
	.अगर \करोcfi
	.cfi_rel_offset \लeg, \offset
	.endअगर
	.endm

	.macro cfi_st reg offset=0 करोcfi=0
	LONG_S	\लeg, \offset(sp)
	cfi_rel_offset \लeg, \offset, \करोcfi
	.endm

	.macro cfi_restore reg offset=0 करोcfi=0
	.अगर \करोcfi
	.cfi_restore \लeg
	.endअगर
	.endm

	.macro cfi_ld reg offset=0 करोcfi=0
	LONG_L	\लeg, \offset(sp)
	cfi_restore \लeg \offset \करोcfi
	.endm

#अगर defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
#घोषणा STATMASK 0x3f
#अन्यथा
#घोषणा STATMASK 0x1f
#पूर्ण_अगर

		.macro	SAVE_AT करोcfi=0
		.set	push
		.set	noat
		cfi_st	$1, PT_R1, \करोcfi
		.set	pop
		.endm

		.macro	SAVE_TEMP करोcfi=0
#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
		mflhxu	v1
		LONG_S	v1, PT_LO(sp)
		mflhxu	v1
		LONG_S	v1, PT_HI(sp)
		mflhxu	v1
		LONG_S	v1, PT_ACX(sp)
#या_अगर !defined(CONFIG_CPU_MIPSR6)
		mfhi	v1
#पूर्ण_अगर
#अगर_घोषित CONFIG_32BIT
		cfi_st	$8, PT_R8, \करोcfi
		cfi_st	$9, PT_R9, \करोcfi
#पूर्ण_अगर
		cfi_st	$10, PT_R10, \करोcfi
		cfi_st	$11, PT_R11, \करोcfi
		cfi_st	$12, PT_R12, \करोcfi
#अगर !defined(CONFIG_CPU_HAS_SMARTMIPS) && !defined(CONFIG_CPU_MIPSR6)
		LONG_S	v1, PT_HI(sp)
		mflo	v1
#पूर्ण_अगर
		cfi_st	$13, PT_R13, \करोcfi
		cfi_st	$14, PT_R14, \करोcfi
		cfi_st	$15, PT_R15, \करोcfi
		cfi_st	$24, PT_R24, \करोcfi
#अगर !defined(CONFIG_CPU_HAS_SMARTMIPS) && !defined(CONFIG_CPU_MIPSR6)
		LONG_S	v1, PT_LO(sp)
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
		/*
		 * The Octeon multiplier state is affected by general
		 * multiply inकाष्ठाions. It must be saved beक्रमe and
		 * kernel code might corrupt it
		 */
		jal     octeon_mult_save
#पूर्ण_अगर
		.endm

		.macro	SAVE_STATIC करोcfi=0
		cfi_st	$16, PT_R16, \करोcfi
		cfi_st	$17, PT_R17, \करोcfi
		cfi_st	$18, PT_R18, \करोcfi
		cfi_st	$19, PT_R19, \करोcfi
		cfi_st	$20, PT_R20, \करोcfi
		cfi_st	$21, PT_R21, \करोcfi
		cfi_st	$22, PT_R22, \करोcfi
		cfi_st	$23, PT_R23, \करोcfi
		cfi_st	$30, PT_R30, \करोcfi
		.endm

/*
 * get_saved_sp वापसs the SP क्रम the current CPU by looking in the
 * kernelsp array क्रम it.  If tosp is set, it stores the current sp in
 * k0 and loads the new value in sp.  If not, it clobbers k0 and
 * stores the new value in k1, leaving sp unaffected.
 */
#अगर_घोषित CONFIG_SMP

		/* SMP variation */
		.macro	get_saved_sp करोcfi=0 tosp=0
		ASM_CPUID_MFC0	k0, ASM_SMP_CPUID_REG
#अगर defined(CONFIG_32BIT) || defined(KBUILD_64BIT_SYM32)
		lui	k1, %hi(kernelsp)
#अन्यथा
		lui	k1, %highest(kernelsp)
		daddiu	k1, %higher(kernelsp)
		dsll	k1, 16
		daddiu	k1, %hi(kernelsp)
		dsll	k1, 16
#पूर्ण_अगर
		LONG_SRL	k0, SMP_CPUID_PTRSHIFT
		LONG_ADDU	k1, k0
		.अगर \टosp
		move	k0, sp
		.अगर \करोcfi
		.cfi_रेजिस्टर sp, k0
		.endअगर
		LONG_L	sp, %lo(kernelsp)(k1)
		.अन्यथा
		LONG_L	k1, %lo(kernelsp)(k1)
		.endअगर
		.endm

		.macro	set_saved_sp stackp temp temp2
		ASM_CPUID_MFC0	\टemp, ASM_SMP_CPUID_REG
		LONG_SRL	\टemp, SMP_CPUID_PTRSHIFT
		LONG_S	\stackp, kernelsp(\टemp)
		.endm
#अन्यथा /* !CONFIG_SMP */
		/* Uniprocessor variation */
		.macro	get_saved_sp करोcfi=0 tosp=0
#अगर_घोषित CONFIG_CPU_JUMP_WORKAROUNDS
		/*
		 * Clear BTB (branch target buffer), क्रमbid RAS (वापस address
		 * stack) to workaround the Out-of-order Issue in Loongson2F
		 * via its diagnostic रेजिस्टर.
		 */
		move	k0, ra
		jal	1f
		 nop
1:		jal	1f
		 nop
1:		jal	1f
		 nop
1:		jal	1f
		 nop
1:		move	ra, k0
		li	k0, 3
		mtc0	k0, $22
#पूर्ण_अगर /* CONFIG_CPU_JUMP_WORKAROUNDS */
#अगर defined(CONFIG_32BIT) || defined(KBUILD_64BIT_SYM32)
		lui	k1, %hi(kernelsp)
#अन्यथा
		lui	k1, %highest(kernelsp)
		daddiu	k1, %higher(kernelsp)
		dsll	k1, k1, 16
		daddiu	k1, %hi(kernelsp)
		dsll	k1, k1, 16
#पूर्ण_अगर
		.अगर \टosp
		move	k0, sp
		.अगर \करोcfi
		.cfi_रेजिस्टर sp, k0
		.endअगर
		LONG_L	sp, %lo(kernelsp)(k1)
		.अन्यथा
		LONG_L	k1, %lo(kernelsp)(k1)
		.endअगर
		.endm

		.macro	set_saved_sp stackp temp temp2
		LONG_S	\stackp, kernelsp
		.endm
#पूर्ण_अगर

		.macro	SAVE_SOME करोcfi=0
		.set	push
		.set	noat
		.set	reorder
		mfc0	k0, CP0_STATUS
		sll	k0, 3		/* extract cu0 bit */
		.set	noreorder
		bltz	k0, 8f
		 move	k0, sp
		.अगर \करोcfi
		.cfi_रेजिस्टर sp, k0
		.endअगर
#अगर_घोषित CONFIG_EVA
		/*
		 * Flush पूर्णांकerAptiv's Return Prediction Stack (RPS) by writing
		 * EntryHi. Toggling Config7.RPS is slower and less portable.
		 *
		 * The RPS isn't स्वतःmatically flushed when exceptions are
		 * taken, which can result in kernel mode speculative accesses
		 * to user addresses अगर the RPS mispredicts. That's harmless
		 * when user and kernel share the same address space, but with
		 * EVA the same user segments may be unmapped to kernel mode,
		 * even containing sensitive MMIO regions or invalid memory.
		 *
		 * This can happen when the kernel sets the वापस address to
		 * ret_from_* and jr's to the exception handler, which looks
		 * more like a tail call than a function call. If nested calls
		 * करोn't evict the last user address in the RPS, it will
		 * mispredict the वापस and fetch from a user controlled
		 * address पूर्णांकo the icache.
		 *
		 * More recent EVA-capable cores with MAAR to restrict
		 * speculative accesses aren't affected.
		 */
		MFC0	k0, CP0_ENTRYHI
		MTC0	k0, CP0_ENTRYHI
#पूर्ण_अगर
		.set	reorder
		/* Called from user mode, new stack. */
		get_saved_sp करोcfi=\करोcfi tosp=1
8:
#अगर_घोषित CONFIG_CPU_DADDI_WORKAROUNDS
		.set	at=k1
#पूर्ण_अगर
		PTR_SUBU sp, PT_SIZE
#अगर_घोषित CONFIG_CPU_DADDI_WORKAROUNDS
		.set	noat
#पूर्ण_अगर
		.अगर \करोcfi
		.cfi_def_cfa sp,0
		.endअगर
		cfi_st	k0, PT_R29, \करोcfi
		cfi_rel_offset  sp, PT_R29, \करोcfi
		cfi_st	v1, PT_R3, \करोcfi
		/*
		 * You might think that you करोn't need to save $0,
		 * but the FPU emulator and gdb remote debug stub
		 * need it to operate correctly
		 */
		LONG_S	$0, PT_R0(sp)
		mfc0	v1, CP0_STATUS
		cfi_st	v0, PT_R2, \करोcfi
		LONG_S	v1, PT_STATUS(sp)
		cfi_st	$4, PT_R4, \करोcfi
		mfc0	v1, CP0_CAUSE
		cfi_st	$5, PT_R5, \करोcfi
		LONG_S	v1, PT_CAUSE(sp)
		cfi_st	$6, PT_R6, \करोcfi
		cfi_st	ra, PT_R31, \करोcfi
		MFC0	ra, CP0_EPC
		cfi_st	$7, PT_R7, \करोcfi
#अगर_घोषित CONFIG_64BIT
		cfi_st	$8, PT_R8, \करोcfi
		cfi_st	$9, PT_R9, \करोcfi
#पूर्ण_अगर
		LONG_S	ra, PT_EPC(sp)
		.अगर \करोcfi
		.cfi_rel_offset ra, PT_EPC
		.endअगर
		cfi_st	$25, PT_R25, \करोcfi
		cfi_st	$28, PT_R28, \करोcfi

		/* Set thपढ़ो_info अगर we're coming from user mode */
		mfc0	k0, CP0_STATUS
		sll	k0, 3		/* extract cu0 bit */
		bltz	k0, 9f

		ori	$28, sp, _THREAD_MASK
		xori	$28, _THREAD_MASK
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
		.set    mips64
		pref    0, 0($28)       /* Prefetch the current poपूर्णांकer */
#पूर्ण_अगर
9:
		.set	pop
		.endm

		.macro	SAVE_ALL करोcfi=0
		SAVE_SOME \करोcfi
		SAVE_AT \करोcfi
		SAVE_TEMP \करोcfi
		SAVE_STATIC \करोcfi
		.endm

		.macro	RESTORE_AT करोcfi=0
		.set	push
		.set	noat
		cfi_ld	$1, PT_R1, \करोcfi
		.set	pop
		.endm

		.macro	RESTORE_TEMP करोcfi=0
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
		/* Restore the Octeon multiplier state */
		jal	octeon_mult_restore
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
		LONG_L	$24, PT_ACX(sp)
		mtlhx	$24
		LONG_L	$24, PT_HI(sp)
		mtlhx	$24
		LONG_L	$24, PT_LO(sp)
		mtlhx	$24
#या_अगर !defined(CONFIG_CPU_MIPSR6)
		LONG_L	$24, PT_LO(sp)
		mtlo	$24
		LONG_L	$24, PT_HI(sp)
		mthi	$24
#पूर्ण_अगर
#अगर_घोषित CONFIG_32BIT
		cfi_ld	$8, PT_R8, \करोcfi
		cfi_ld	$9, PT_R9, \करोcfi
#पूर्ण_अगर
		cfi_ld	$10, PT_R10, \करोcfi
		cfi_ld	$11, PT_R11, \करोcfi
		cfi_ld	$12, PT_R12, \करोcfi
		cfi_ld	$13, PT_R13, \करोcfi
		cfi_ld	$14, PT_R14, \करोcfi
		cfi_ld	$15, PT_R15, \करोcfi
		cfi_ld	$24, PT_R24, \करोcfi
		.endm

		.macro	RESTORE_STATIC करोcfi=0
		cfi_ld	$16, PT_R16, \करोcfi
		cfi_ld	$17, PT_R17, \करोcfi
		cfi_ld	$18, PT_R18, \करोcfi
		cfi_ld	$19, PT_R19, \करोcfi
		cfi_ld	$20, PT_R20, \करोcfi
		cfi_ld	$21, PT_R21, \करोcfi
		cfi_ld	$22, PT_R22, \करोcfi
		cfi_ld	$23, PT_R23, \करोcfi
		cfi_ld	$30, PT_R30, \करोcfi
		.endm

		.macro	RESTORE_SP करोcfi=0
		cfi_ld	sp, PT_R29, \करोcfi
		.endm

#अगर defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)

		.macro	RESTORE_SOME करोcfi=0
		.set	push
		.set	reorder
		.set	noat
		mfc0	a0, CP0_STATUS
		li	v1, ST0_CU1 | ST0_IM
		ori	a0, STATMASK
		xori	a0, STATMASK
		mtc0	a0, CP0_STATUS
		and	a0, v1
		LONG_L	v0, PT_STATUS(sp)
		nor	v1, $0, v1
		and	v0, v1
		or	v0, a0
		mtc0	v0, CP0_STATUS
		cfi_ld	$31, PT_R31, \करोcfi
		cfi_ld	$28, PT_R28, \करोcfi
		cfi_ld	$25, PT_R25, \करोcfi
		cfi_ld	$7,  PT_R7, \करोcfi
		cfi_ld	$6,  PT_R6, \करोcfi
		cfi_ld	$5,  PT_R5, \करोcfi
		cfi_ld	$4,  PT_R4, \करोcfi
		cfi_ld	$3,  PT_R3, \करोcfi
		cfi_ld	$2,  PT_R2, \करोcfi
		.set	pop
		.endm

		.macro	RESTORE_SP_AND_RET करोcfi=0
		.set	push
		.set	noreorder
		LONG_L	k0, PT_EPC(sp)
		RESTORE_SP \करोcfi
		jr	k0
		 rfe
		.set	pop
		.endm

#अन्यथा
		.macro	RESTORE_SOME करोcfi=0
		.set	push
		.set	reorder
		.set	noat
		mfc0	a0, CP0_STATUS
		ori	a0, STATMASK
		xori	a0, STATMASK
		mtc0	a0, CP0_STATUS
		li	v1, ST0_CU1 | ST0_FR | ST0_IM
		and	a0, v1
		LONG_L	v0, PT_STATUS(sp)
		nor	v1, $0, v1
		and	v0, v1
		or	v0, a0
		mtc0	v0, CP0_STATUS
		LONG_L	v1, PT_EPC(sp)
		MTC0	v1, CP0_EPC
		cfi_ld	$31, PT_R31, \करोcfi
		cfi_ld	$28, PT_R28, \करोcfi
		cfi_ld	$25, PT_R25, \करोcfi
#अगर_घोषित CONFIG_64BIT
		cfi_ld	$8, PT_R8, \करोcfi
		cfi_ld	$9, PT_R9, \करोcfi
#पूर्ण_अगर
		cfi_ld	$7,  PT_R7, \करोcfi
		cfi_ld	$6,  PT_R6, \करोcfi
		cfi_ld	$5,  PT_R5, \करोcfi
		cfi_ld	$4,  PT_R4, \करोcfi
		cfi_ld	$3,  PT_R3, \करोcfi
		cfi_ld	$2,  PT_R2, \करोcfi
		.set	pop
		.endm

		.macro	RESTORE_SP_AND_RET करोcfi=0
		RESTORE_SP \करोcfi
#अगर defined(CONFIG_CPU_MIPSR5) || defined(CONFIG_CPU_MIPSR6)
		eretnc
#अन्यथा
		.set	push
		.set	arch=r4000
		eret
		.set	pop
#पूर्ण_अगर
		.endm

#पूर्ण_अगर

		.macro	RESTORE_ALL करोcfi=0
		RESTORE_TEMP \करोcfi
		RESTORE_STATIC \करोcfi
		RESTORE_AT \करोcfi
		RESTORE_SOME \करोcfi
		RESTORE_SP \करोcfi
		.endm

/*
 * Move to kernel mode and disable पूर्णांकerrupts.
 * Set cp0 enable bit as sign that we're running on the kernel stack
 */
		.macro	CLI
		mfc0	t0, CP0_STATUS
		li	t1, ST0_KERNEL_CUMASK | STATMASK
		or	t0, t1
		xori	t0, STATMASK
		mtc0	t0, CP0_STATUS
		irq_disable_hazard
		.endm

/*
 * Move to kernel mode and enable पूर्णांकerrupts.
 * Set cp0 enable bit as sign that we're running on the kernel stack
 */
		.macro	STI
		mfc0	t0, CP0_STATUS
		li	t1, ST0_KERNEL_CUMASK | STATMASK
		or	t0, t1
		xori	t0, STATMASK & ~1
		mtc0	t0, CP0_STATUS
		irq_enable_hazard
		.endm

/*
 * Just move to kernel mode and leave पूर्णांकerrupts as they are.  Note
 * क्रम the R3000 this means copying the previous enable from IEp.
 * Set cp0 enable bit as sign that we're running on the kernel stack
 */
		.macro	KMODE
		mfc0	t0, CP0_STATUS
		li	t1, ST0_KERNEL_CUMASK | (STATMASK & ~1)
#अगर defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
		andi	t2, t0, ST0_IEP
		srl	t2, 2
		or	t0, t2
#पूर्ण_अगर
		or	t0, t1
		xori	t0, STATMASK & ~1
		mtc0	t0, CP0_STATUS
		irq_disable_hazard
		.endm

#पूर्ण_अगर /* _ASM_STACKFRAME_H */
