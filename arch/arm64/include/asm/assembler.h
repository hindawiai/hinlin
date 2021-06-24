<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/assembler.h, arch/arm/mm/proc-macros.S
 *
 * Copyright (C) 1996-2000 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASSEMBLY__
#त्रुटि "Only include this from assembly code"
#पूर्ण_अगर

#अगर_अघोषित __ASM_ASSEMBLER_H
#घोषणा __ASM_ASSEMBLER_H

#समावेश <यंत्र-generic/export.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/यंत्र-bug.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/thपढ़ो_info.h>

	/*
	 * Provide a wxN alias क्रम each wN रेजिस्टर so what we can paste a xN
	 * reference after a 'w' to obtain the 32-bit version.
	 */
	.irp	n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
	wx\न	.req	w\न
	.endr

	.macro save_and_disable_daअगर, flags
	mrs	\पlags, daअगर
	msr	daअगरset, #0xf
	.endm

	.macro disable_daअगर
	msr	daअगरset, #0xf
	.endm

	.macro enable_daअगर
	msr	daअगरclr, #0xf
	.endm

	.macro	restore_daअगर, flags:req
	msr	daअगर, \पlags
	.endm

	/* IRQ/FIQ are the lowest priority flags, unconditionally unmask the rest. */
	.macro enable_da
	msr	daअगरclr, #(8 | 4)
	.endm

/*
 * Save/restore पूर्णांकerrupts.
 */
	.macro	save_and_disable_irq, flags
	mrs	\पlags, daअगर
	msr	daअगरset, #3
	.endm

	.macro	restore_irq, flags
	msr	daअगर, \पlags
	.endm

	.macro	enable_dbg
	msr	daअगरclr, #8
	.endm

	.macro	disable_step_tsk, flgs, पंचांगp
	tbz	\पlgs, #TIF_SINGLESTEP, 9990f
	mrs	\टmp, mdscr_el1
	bic	\टmp, \टmp, #DBG_MDSCR_SS
	msr	mdscr_el1, \टmp
	isb	// Synchronise with enable_dbg
9990:
	.endm

	/* call with daअगर masked */
	.macro	enable_step_tsk, flgs, पंचांगp
	tbz	\पlgs, #TIF_SINGLESTEP, 9990f
	mrs	\टmp, mdscr_el1
	orr	\टmp, \टmp, #DBG_MDSCR_SS
	msr	mdscr_el1, \टmp
9990:
	.endm

/*
 * RAS Error Synchronization barrier
 */
	.macro  esb
#अगर_घोषित CONFIG_ARM64_RAS_EXTN
	hपूर्णांक    #16
#अन्यथा
	nop
#पूर्ण_अगर
	.endm

/*
 * Value prediction barrier
 */
	.macro	csdb
	hपूर्णांक	#20
	.endm

/*
 * Speculation barrier
 */
	.macro	sb
alternative_अगर_not ARM64_HAS_SB
	dsb	nsh
	isb
alternative_अन्यथा
	SB_BARRIER_INSN
	nop
alternative_endअगर
	.endm

/*
 * NOP sequence
 */
	.macro	nops, num
	.rept	\नum
	nop
	.endr
	.endm

/*
 * Emit an entry पूर्णांकo the exception table
 */
	.macro		_यंत्र_extable, from, to
	.pushsection	__ex_table, "a"
	.align		3
	.दीर्घ		(\पrom - .), (\टo - .)
	.popsection
	.endm

#घोषणा USER(l, x...)				\
9999:	x;					\
	_यंत्र_extable	9999b, l

/*
 * Register aliases.
 */
lr	.req	x30		// link रेजिस्टर

/*
 * Vector entry
 */
	 .macro	ventry	label
	.align	7
	b	\label
	.endm

/*
 * Select code when configured क्रम BE.
 */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा CPU_BE(code...) code
#अन्यथा
#घोषणा CPU_BE(code...)
#पूर्ण_अगर

/*
 * Select code when configured क्रम LE.
 */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा CPU_LE(code...)
#अन्यथा
#घोषणा CPU_LE(code...) code
#पूर्ण_अगर

/*
 * Define a macro that स्थिरructs a 64-bit value by concatenating two
 * 32-bit रेजिस्टरs. Note that on big endian प्रणालीs the order of the
 * रेजिस्टरs is swapped.
 */
#अगर_अघोषित CONFIG_CPU_BIG_ENDIAN
	.macro	regs_to_64, rd, lbits, hbits
#अन्यथा
	.macro	regs_to_64, rd, hbits, lbits
#पूर्ण_अगर
	orr	\लd, \lbits, \hbits, lsl #32
	.endm

/*
 * Pseuकरो-ops क्रम PC-relative adr/ldr/str <reg>, <symbol> where
 * <symbol> is within the range +/- 4 GB of the PC.
 */
	/*
	 * @dst: destination रेजिस्टर (64 bit wide)
	 * @sym: name of the symbol
	 */
	.macro	adr_l, dst, sym
	adrp	\dst, \sym
	add	\dst, \dst, :lo12:\sym
	.endm

	/*
	 * @dst: destination रेजिस्टर (32 or 64 bit wide)
	 * @sym: name of the symbol
	 * @पंचांगp: optional 64-bit scratch रेजिस्टर to be used अगर <dst> is a
	 *       32-bit wide रेजिस्टर, in which हाल it cannot be used to hold
	 *       the address
	 */
	.macro	ldr_l, dst, sym, पंचांगp=
	.अगरb	\टmp
	adrp	\dst, \sym
	ldr	\dst, [\dst, :lo12:\sym]
	.अन्यथा
	adrp	\टmp, \sym
	ldr	\dst, [\टmp, :lo12:\sym]
	.endअगर
	.endm

	/*
	 * @src: source रेजिस्टर (32 or 64 bit wide)
	 * @sym: name of the symbol
	 * @पंचांगp: mandatory 64-bit scratch रेजिस्टर to calculate the address
	 *       जबतक <src> needs to be preserved.
	 */
	.macro	str_l, src, sym, पंचांगp
	adrp	\टmp, \sym
	str	\src, [\टmp, :lo12:\sym]
	.endm

	/*
	 * @dst: destination रेजिस्टर
	 */
#अगर defined(__KVM_NVHE_HYPERVISOR__) || defined(__KVM_VHE_HYPERVISOR__)
	.macro	this_cpu_offset, dst
	mrs	\dst, tpidr_el2
	.endm
#अन्यथा
	.macro	this_cpu_offset, dst
alternative_अगर_not ARM64_HAS_VIRT_HOST_EXTN
	mrs	\dst, tpidr_el1
alternative_अन्यथा
	mrs	\dst, tpidr_el2
alternative_endअगर
	.endm
#पूर्ण_अगर

	/*
	 * @dst: Result of per_cpu(sym, smp_processor_id()) (can be SP)
	 * @sym: The name of the per-cpu variable
	 * @पंचांगp: scratch रेजिस्टर
	 */
	.macro adr_this_cpu, dst, sym, पंचांगp
	adrp	\टmp, \sym
	add	\dst, \टmp, #:lo12:\sym
	this_cpu_offset \टmp
	add	\dst, \dst, \टmp
	.endm

	/*
	 * @dst: Result of READ_ONCE(per_cpu(sym, smp_processor_id()))
	 * @sym: The name of the per-cpu variable
	 * @पंचांगp: scratch रेजिस्टर
	 */
	.macro ldr_this_cpu dst, sym, पंचांगp
	adr_l	\dst, \sym
	this_cpu_offset \टmp
	ldr	\dst, [\dst, \टmp]
	.endm

/*
 * vma_vm_mm - get mm poपूर्णांकer from vma poपूर्णांकer (vma->vm_mm)
 */
	.macro	vma_vm_mm, rd, rn
	ldr	\लd, [\लn, #VMA_VM_MM]
	.endm

/*
 * पढ़ो_ctr - पढ़ो CTR_EL0. If the प्रणाली has mismatched रेजिस्टर fields,
 * provide the प्रणाली wide safe value from arm64_ftr_reg_ctrel0.sys_val
 */
	.macro	पढ़ो_ctr, reg
#अगर_अघोषित __KVM_NVHE_HYPERVISOR__
alternative_अगर_not ARM64_MISMATCHED_CACHE_TYPE
	mrs	\लeg, ctr_el0			// पढ़ो CTR
	nop
alternative_अन्यथा
	ldr_l	\लeg, arm64_ftr_reg_ctrel0 + ARM64_FTR_SYSVAL
alternative_endअगर
#अन्यथा
alternative_अगर_not ARM64_KVM_PROTECTED_MODE
	ASM_BUG()
alternative_अन्यथा_nop_endअगर
alternative_cb kvm_compute_final_ctr_el0
	movz	\लeg, #0
	movk	\लeg, #0, lsl #16
	movk	\लeg, #0, lsl #32
	movk	\लeg, #0, lsl #48
alternative_cb_end
#पूर्ण_अगर
	.endm


/*
 * raw_dcache_line_size - get the minimum D-cache line size on this CPU
 * from the CTR रेजिस्टर.
 */
	.macro	raw_dcache_line_size, reg, पंचांगp
	mrs	\टmp, ctr_el0			// पढ़ो CTR
	ubfm	\टmp, \टmp, #16, #19		// cache line size encoding
	mov	\लeg, #4			// bytes per word
	lsl	\लeg, \लeg, \टmp		// actual cache line size
	.endm

/*
 * dcache_line_size - get the safe D-cache line size across all CPUs
 */
	.macro	dcache_line_size, reg, पंचांगp
	पढ़ो_ctr	\टmp
	ubfm		\टmp, \टmp, #16, #19	// cache line size encoding
	mov		\लeg, #4		// bytes per word
	lsl		\लeg, \लeg, \टmp	// actual cache line size
	.endm

/*
 * raw_icache_line_size - get the minimum I-cache line size on this CPU
 * from the CTR रेजिस्टर.
 */
	.macro	raw_icache_line_size, reg, पंचांगp
	mrs	\टmp, ctr_el0			// पढ़ो CTR
	and	\टmp, \टmp, #0xf		// cache line size encoding
	mov	\लeg, #4			// bytes per word
	lsl	\लeg, \लeg, \टmp		// actual cache line size
	.endm

/*
 * icache_line_size - get the safe I-cache line size across all CPUs
 */
	.macro	icache_line_size, reg, पंचांगp
	पढ़ो_ctr	\टmp
	and		\टmp, \टmp, #0xf	// cache line size encoding
	mov		\लeg, #4		// bytes per word
	lsl		\लeg, \लeg, \टmp	// actual cache line size
	.endm

/*
 * tcr_set_t0sz - update TCR.T0SZ so that we can load the ID map
 */
	.macro	tcr_set_t0sz, valreg, t0sz
	bfi	\खalreg, \ट0sz, #TCR_T0SZ_OFFSET, #TCR_TxSZ_WIDTH
	.endm

/*
 * tcr_set_t1sz - update TCR.T1SZ
 */
	.macro	tcr_set_t1sz, valreg, t1sz
	bfi	\खalreg, \ट1sz, #TCR_T1SZ_OFFSET, #TCR_TxSZ_WIDTH
	.endm

/*
 * tcr_compute_pa_size - set TCR.(I)PS to the highest supported
 * ID_AA64MMFR0_EL1.PARange value
 *
 *	tcr:		रेजिस्टर with the TCR_ELx value to be updated
 *	pos:		IPS or PS bitfield position
 *	पंचांगpअणु0,1पूर्ण:	temporary रेजिस्टरs
 */
	.macro	tcr_compute_pa_size, tcr, pos, पंचांगp0, पंचांगp1
	mrs	\टmp0, ID_AA64MMFR0_EL1
	// Narrow PARange to fit the PS field in TCR_ELx
	ubfx	\टmp0, \टmp0, #ID_AA64MMFR0_PARANGE_SHIFT, #3
	mov	\टmp1, #ID_AA64MMFR0_PARANGE_MAX
	cmp	\टmp0, \टmp1
	csel	\टmp0, \टmp1, \टmp0, hi
	bfi	\टcr, \टmp0, \pos, #3
	.endm

/*
 * Macro to perक्रमm a data cache मुख्यtenance क्रम the पूर्णांकerval
 * [kaddr, kaddr + size)
 *
 * 	op:		operation passed to dc inकाष्ठाion
 * 	करोमुख्य:		करोमुख्य used in dsb instruciton
 * 	kaddr:		starting भव address of the region
 * 	size:		size of the region
 * 	Corrupts:	kaddr, size, पंचांगp1, पंचांगp2
 */
	.macro __dcache_op_workaround_clean_cache, op, kaddr
alternative_अगर_not ARM64_WORKAROUND_CLEAN_CACHE
	dc	\op, \kaddr
alternative_अन्यथा
	dc	civac, \kaddr
alternative_endअगर
	.endm

	.macro dcache_by_line_op op, करोमुख्य, kaddr, size, पंचांगp1, पंचांगp2
	dcache_line_size \टmp1, \टmp2
	add	\size, \kaddr, \size
	sub	\टmp2, \टmp1, #1
	bic	\kaddr, \kaddr, \टmp2
9998:
	.अगरc	\op, cvau
	__dcache_op_workaround_clean_cache \op, \kaddr
	.अन्यथा
	.अगरc	\op, cvac
	__dcache_op_workaround_clean_cache \op, \kaddr
	.अन्यथा
	.अगरc	\op, cvap
	sys	3, c7, c12, 1, \kaddr	// dc cvap
	.अन्यथा
	.अगरc	\op, cvadp
	sys	3, c7, c13, 1, \kaddr	// dc cvadp
	.अन्यथा
	dc	\op, \kaddr
	.endअगर
	.endअगर
	.endअगर
	.endअगर
	add	\kaddr, \kaddr, \टmp1
	cmp	\kaddr, \size
	b.lo	9998b
	dsb	\करोमुख्य
	.endm

/*
 * Macro to perक्रमm an inकाष्ठाion cache मुख्यtenance क्रम the पूर्णांकerval
 * [start, end)
 *
 * 	start, end:	भव addresses describing the region
 *	label:		A label to branch to on user fault.
 * 	Corrupts:	पंचांगp1, पंचांगp2
 */
	.macro invalidate_icache_by_line start, end, पंचांगp1, पंचांगp2, label
	icache_line_size \टmp1, \टmp2
	sub	\टmp2, \टmp1, #1
	bic	\टmp2, \start, \टmp2
9997:
USER(\label, ic	ivau, \टmp2)			// invalidate I line PoU
	add	\टmp2, \टmp2, \टmp1
	cmp	\टmp2, \end
	b.lo	9997b
	dsb	ish
	isb
	.endm

/*
 * reset_pmuserenr_el0 - reset PMUSERENR_EL0 अगर PMUv3 present
 */
	.macro	reset_pmuserenr_el0, पंचांगpreg
	mrs	\टmpreg, id_aa64dfr0_el1
	sbfx	\टmpreg, \टmpreg, #ID_AA64DFR0_PMUVER_SHIFT, #4
	cmp	\टmpreg, #1			// Skip अगर no PMU present
	b.lt	9000f
	msr	pmuserenr_el0, xzr		// Disable PMU access from EL0
9000:
	.endm

/*
 * reset_amuserenr_el0 - reset AMUSERENR_EL0 अगर AMUv1 present
 */
	.macro	reset_amuserenr_el0, पंचांगpreg
	mrs	\टmpreg, id_aa64pfr0_el1	// Check ID_AA64PFR0_EL1
	ubfx	\टmpreg, \टmpreg, #ID_AA64PFR0_AMU_SHIFT, #4
	cbz	\टmpreg, .Lskip_\@		// Skip अगर no AMU present
	msr_s	SYS_AMUSERENR_EL0, xzr		// Disable AMU access from EL0
.Lskip_\@:
	.endm
/*
 * copy_page - copy src to dest using temp रेजिस्टरs t1-t8
 */
	.macro copy_page dest:req src:req t1:req t2:req t3:req t4:req t5:req t6:req t7:req t8:req
9998:	ldp	\ट1, \ट2, [\src]
	ldp	\ट3, \ट4, [\src, #16]
	ldp	\ट5, \ट6, [\src, #32]
	ldp	\ट7, \ट8, [\src, #48]
	add	\src, \src, #64
	stnp	\ट1, \ट2, [\dest]
	stnp	\ट3, \ट4, [\dest, #16]
	stnp	\ट5, \ट6, [\dest, #32]
	stnp	\ट7, \ट8, [\dest, #48]
	add	\dest, \dest, #64
	tst	\src, #(PAGE_SIZE - 1)
	b.ne	9998b
	.endm

/*
 * Annotate a function as being unsuitable क्रम kprobes.
 */
#अगर_घोषित CONFIG_KPROBES
#घोषणा NOKPROBE(x)				\
	.pushsection "_kprobe_blacklist", "aw";	\
	.quad	x;				\
	.popsection;
#अन्यथा
#घोषणा NOKPROBE(x)
#पूर्ण_अगर

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
#घोषणा EXPORT_SYMBOL_NOKASAN(name)
#अन्यथा
#घोषणा EXPORT_SYMBOL_NOKASAN(name)	EXPORT_SYMBOL(name)
#पूर्ण_अगर

	/*
	 * Emit a 64-bit असलolute little endian symbol reference in a way that
	 * ensures that it will be resolved at build समय, even when building a
	 * PIE binary. This requires cooperation from the linker script, which
	 * must emit the lo32/hi32 halves inभागidually.
	 */
	.macro	le64sym, sym
	.दीर्घ	\sym\()_lo32
	.दीर्घ	\sym\()_hi32
	.endm

	/*
	 * mov_q - move an immediate स्थिरant पूर्णांकo a 64-bit रेजिस्टर using
	 *         between 2 and 4 movz/movk inकाष्ठाions (depending on the
	 *         magnitude and sign of the opeअक्रम)
	 */
	.macro	mov_q, reg, val
	.अगर (((\खal) >> 31) == 0 || ((\खal) >> 31) == 0x1ffffffff)
	movz	\लeg, :असल_g1_s:\खal
	.अन्यथा
	.अगर (((\खal) >> 47) == 0 || ((\खal) >> 47) == 0x1ffff)
	movz	\लeg, :असल_g2_s:\खal
	.अन्यथा
	movz	\लeg, :असल_g3:\खal
	movk	\लeg, :असल_g2_nc:\खal
	.endअगर
	movk	\लeg, :असल_g1_nc:\खal
	.endअगर
	movk	\लeg, :असल_g0_nc:\खal
	.endm

/*
 * Return the current task_काष्ठा.
 */
	.macro	get_current_task, rd
	mrs	\लd, sp_el0
	.endm

/*
 * Offset ttbr1 to allow क्रम 48-bit kernel VAs set with 52-bit PTRS_PER_PGD.
 * orr is used as it can cover the immediate value (and is idempotent).
 * In future this may be nop'ed out when dealing with 52-bit kernel VAs.
 * 	ttbr: Value of ttbr to set, modअगरied.
 */
	.macro	offset_ttbr1, ttbr, पंचांगp
#अगर_घोषित CONFIG_ARM64_VA_BITS_52
	mrs_s	\टmp, SYS_ID_AA64MMFR2_EL1
	and	\टmp, \टmp, #(0xf << ID_AA64MMFR2_LVA_SHIFT)
	cbnz	\टmp, .Lskipoffs_\@
	orr	\टtbr, \टtbr, #TTBR1_BADDR_4852_OFFSET
.Lskipoffs_\@ :
#पूर्ण_अगर
	.endm

/*
 * Perक्रमm the reverse of offset_ttbr1.
 * bic is used as it can cover the immediate value and, in future, won't need
 * to be nop'ed out when dealing with 52-bit kernel VAs.
 */
	.macro	restore_ttbr1, ttbr
#अगर_घोषित CONFIG_ARM64_VA_BITS_52
	bic	\टtbr, \टtbr, #TTBR1_BADDR_4852_OFFSET
#पूर्ण_अगर
	.endm

/*
 * Arrange a physical address in a TTBR रेजिस्टर, taking care of 52-bit
 * addresses.
 *
 * 	phys:	physical address, preserved
 * 	ttbr:	वापसs the TTBR value
 */
	.macro	phys_to_ttbr, ttbr, phys
#अगर_घोषित CONFIG_ARM64_PA_BITS_52
	orr	\टtbr, \phys, \phys, lsr #46
	and	\टtbr, \टtbr, #TTBR_BADDR_MASK_52
#अन्यथा
	mov	\टtbr, \phys
#पूर्ण_अगर
	.endm

	.macro	phys_to_pte, pte, phys
#अगर_घोषित CONFIG_ARM64_PA_BITS_52
	/*
	 * We assume \phys is 64K aligned and this is guaranteed by only
	 * supporting this configuration with 64K pages.
	 */
	orr	\pte, \phys, \phys, lsr #36
	and	\pte, \pte, #PTE_ADDR_MASK
#अन्यथा
	mov	\pte, \phys
#पूर्ण_अगर
	.endm

	.macro	pte_to_phys, phys, pte
#अगर_घोषित CONFIG_ARM64_PA_BITS_52
	ubfiz	\phys, \pte, #(48 - 16 - 12), #16
	bfxil	\phys, \pte, #16, #32
	lsl	\phys, \phys, #16
#अन्यथा
	and	\phys, \pte, #PTE_ADDR_MASK
#पूर्ण_अगर
	.endm

/*
 * tcr_clear_errata_bits - Clear TCR bits that trigger an errata on this CPU.
 */
	.macro	tcr_clear_errata_bits, tcr, पंचांगp1, पंचांगp2
#अगर_घोषित CONFIG_FUJITSU_ERRATUM_010001
	mrs	\टmp1, midr_el1

	mov_q	\टmp2, MIDR_FUJITSU_ERRATUM_010001_MASK
	and	\टmp1, \टmp1, \टmp2
	mov_q	\टmp2, MIDR_FUJITSU_ERRATUM_010001
	cmp	\टmp1, \टmp2
	b.ne	10f

	mov_q	\टmp2, TCR_CLEAR_FUJITSU_ERRATUM_010001
	bic	\टcr, \टcr, \टmp2
10:
#पूर्ण_अगर /* CONFIG_FUJITSU_ERRATUM_010001 */
	.endm

/**
 * Errata workaround prior to disable MMU. Insert an ISB immediately prior
 * to executing the MSR that will change SCTLR_ELn[M] from a value of 1 to 0.
 */
	.macro pre_disable_mmu_workaround
#अगर_घोषित CONFIG_QCOM_FALKOR_ERRATUM_E1041
	isb
#पूर्ण_अगर
	.endm

	/*
	 * frame_push - Push @regcount callee saved रेजिस्टरs to the stack,
	 *              starting at x19, as well as x29/x30, and set x29 to
	 *              the new value of sp. Add @extra bytes of stack space
	 *              क्रम locals.
	 */
	.macro		frame_push, regcount:req, extra
	__frame		st, \लegcount, \extra
	.endm

	/*
	 * frame_pop  - Pop the callee saved रेजिस्टरs from the stack that were
	 *              pushed in the most recent call to frame_push, as well
	 *              as x29/x30 and any extra stack space that may have been
	 *              allocated.
	 */
	.macro		frame_pop
	__frame		ld
	.endm

	.macro		__frame_regs, reg1, reg2, op, num
	.अगर		.Lframe_regcount == \नum
	\op\()r		\लeg1, [sp, #(\नum + 1) * 8]
	.अन्यथाअगर		.Lframe_regcount > \नum
	\op\()p		\लeg1, \लeg2, [sp, #(\नum + 1) * 8]
	.endअगर
	.endm

	.macro		__frame, op, regcount, extra=0
	.अगरc		\op, st
	.अगर		(\लegcount) < 0 || (\लegcount) > 10
	.error		"regcount should be in the range [0 ... 10]"
	.endअगर
	.अगर		((\extra) % 16) != 0
	.error		"extra should be a multiple of 16 bytes"
	.endअगर
	.अगरdef		.Lframe_regcount
	.अगर		.Lframe_regcount != -1
	.error		"frame_push/frame_pop may not be nested"
	.endअगर
	.endअगर
	.set		.Lframe_regcount, \लegcount
	.set		.Lframe_extra, \extra
	.set		.Lframe_local_offset, ((\लegcount + 3) / 2) * 16
	stp		x29, x30, [sp, #-.Lframe_local_offset - .Lframe_extra]!
	mov		x29, sp
	.endअगर

	__frame_regs	x19, x20, \op, 1
	__frame_regs	x21, x22, \op, 3
	__frame_regs	x23, x24, \op, 5
	__frame_regs	x25, x26, \op, 7
	__frame_regs	x27, x28, \op, 9

	.अगरc		\op, ld
	.अगर		.Lframe_regcount == -1
	.error		"frame_push/frame_pop may not be nested"
	.endअगर
	ldp		x29, x30, [sp], #.Lframe_local_offset + .Lframe_extra
	.set		.Lframe_regcount, -1
	.endअगर
	.endm

/*
 * Set SCTLR_ELx to the @reg value, and invalidate the local icache
 * in the process. This is called when setting the MMU on.
 */
.macro set_sctlr, sreg, reg
	msr	\sreg, \लeg
	isb
	/*
	 * Invalidate the local I-cache so that any inकाष्ठाions fetched
	 * speculatively from the PoC are discarded, since they may have
	 * been dynamically patched at the PoU.
	 */
	ic	iallu
	dsb	nsh
	isb
.endm

.macro set_sctlr_el1, reg
	set_sctlr sctlr_el1, \लeg
.endm

.macro set_sctlr_el2, reg
	set_sctlr sctlr_el2, \लeg
.endm

	/*
	 * Check whether preempt/bh-disabled यंत्र code should yield as soon as
	 * it is able. This is the हाल अगर we are currently running in task
	 * context, and either a softirq is pending, or the TIF_NEED_RESCHED
	 * flag is set and re-enabling preemption a single समय would result in
	 * a preempt count of zero. (Note that the TIF_NEED_RESCHED flag is
	 * stored negated in the top word of the thपढ़ो_info::preempt_count
	 * field)
	 */
	.macro		cond_yield, lbl:req, पंचांगp:req, पंचांगp2:req
	get_current_task \टmp
	ldr		\टmp, [\टmp, #TSK_TI_PREEMPT]
	/*
	 * If we are serving a softirq, there is no poपूर्णांक in yielding: the
	 * softirq will not be preempted no matter what we करो, so we should
	 * run to completion as quickly as we can.
	 */
	tbnz		\टmp, #SOFTIRQ_SHIFT, .Lnoyield_\@
#अगर_घोषित CONFIG_PREEMPTION
	sub		\टmp, \टmp, #PREEMPT_DISABLE_OFFSET
	cbz		\टmp, \lbl
#पूर्ण_अगर
	adr_l		\टmp, irq_stat + IRQ_CPUSTAT_SOFTIRQ_PENDING
	this_cpu_offset	\टmp2
	ldr		w\टmp, [\टmp, \टmp2]
	cbnz		w\टmp, \lbl	// yield on pending softirq in task context
.Lnoyield_\@:
	.endm

/*
 * This macro emits a program property note section identअगरying
 * architecture features which require special handling, मुख्यly क्रम
 * use in assembly files included in the VDSO.
 */

#घोषणा NT_GNU_PROPERTY_TYPE_0  5
#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_AND      0xc0000000

#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_BTI      (1U << 0)
#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_PAC      (1U << 1)

#अगर_घोषित CONFIG_ARM64_BTI_KERNEL
#घोषणा GNU_PROPERTY_AARCH64_FEATURE_1_DEFAULT		\
		((GNU_PROPERTY_AARCH64_FEATURE_1_BTI |	\
		  GNU_PROPERTY_AARCH64_FEATURE_1_PAC))
#पूर्ण_अगर

#अगर_घोषित GNU_PROPERTY_AARCH64_FEATURE_1_DEFAULT
.macro emit_aarch64_feature_1_and, feat=GNU_PROPERTY_AARCH64_FEATURE_1_DEFAULT
	.pushsection .note.gnu.property, "a"
	.align  3
	.दीर्घ   2f - 1f
	.दीर्घ   6f - 3f
	.दीर्घ   NT_GNU_PROPERTY_TYPE_0
1:      .string "GNU"
2:
	.align  3
3:      .दीर्घ   GNU_PROPERTY_AARCH64_FEATURE_1_AND
	.दीर्घ   5f - 4f
4:
	/*
	 * This is described with an array of अक्षर in the Linux API
	 * spec but the text and all other usage (including binutils,
	 * clang and GCC) treat this as a 32 bit value so no swizzling
	 * is required क्रम big endian.
	 */
	.दीर्घ   \पeat
5:
	.align  3
6:
	.popsection
.endm

#अन्यथा
.macro emit_aarch64_feature_1_and, feat=0
.endm

#पूर्ण_अगर /* GNU_PROPERTY_AARCH64_FEATURE_1_DEFAULT */

#पूर्ण_अगर	/* __ASM_ASSEMBLER_H */
