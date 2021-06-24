<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Ralf Baechle
 */
#अगर_अघोषित _ASM_ASMMACRO_H
#घोषणा _ASM_ASMMACRO_H

#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/msa.h>

#अगर_घोषित CONFIG_32BIT
#समावेश <यंत्र/यंत्रmacro-32.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
#समावेश <यंत्र/यंत्रmacro-64.h>
#पूर्ण_अगर

/* preprocessor replaces the fp in ".set fp=64" with $30 otherwise */
#अघोषित fp

/*
 * Helper macros क्रम generating raw inकाष्ठाion encodings.
 */
#अगर_घोषित CONFIG_CPU_MICROMIPS
	.macro	insn32_अगर_mm enc
	.insn
	.hword ((\enc) >> 16)
	.hword ((\enc) & 0xffff)
	.endm

	.macro	insn_अगर_mips enc
	.endm
#अन्यथा
	.macro	insn32_अगर_mm enc
	.endm

	.macro	insn_अगर_mips enc
	.insn
	.word (\enc)
	.endm
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_HAS_DIEI
	.macro	local_irq_enable reg=t0
	ei
	irq_enable_hazard
	.endm

	.macro	local_irq_disable reg=t0
	di
	irq_disable_hazard
	.endm
#अन्यथा /* !CONFIG_CPU_MIPSR2 && !CONFIG_CPU_MIPSR5 && !CONFIG_CPU_MIPSR6 */
	.macro	local_irq_enable reg=t0
	mfc0	\लeg, CP0_STATUS
	ori	\लeg, \लeg, 1
	mtc0	\लeg, CP0_STATUS
	irq_enable_hazard
	.endm

	.macro	local_irq_disable reg=t0
#अगर_घोषित CONFIG_PREEMPTION
	lw      \लeg, TI_PRE_COUNT($28)
	addi    \लeg, \लeg, 1
	sw      \लeg, TI_PRE_COUNT($28)
#पूर्ण_अगर
	mfc0	\लeg, CP0_STATUS
	ori	\लeg, \लeg, 1
	xori	\लeg, \लeg, 1
	mtc0	\लeg, CP0_STATUS
	irq_disable_hazard
#अगर_घोषित CONFIG_PREEMPTION
	lw      \लeg, TI_PRE_COUNT($28)
	addi    \लeg, \लeg, -1
	sw      \लeg, TI_PRE_COUNT($28)
#पूर्ण_अगर
	.endm
#पूर्ण_अगर  /* !CONFIG_CPU_MIPSR2 && !CONFIG_CPU_MIPSR5 && !CONFIG_CPU_MIPSR6 */

	.macro	fpu_save_16even thपढ़ो पंचांगp=t0
	.set	push
	SET_HARDFLOAT
	cfc1	\टmp, fcr31
	sdc1	$f0,  THREAD_FPR0(\टhपढ़ो)
	sdc1	$f2,  THREAD_FPR2(\टhपढ़ो)
	sdc1	$f4,  THREAD_FPR4(\टhपढ़ो)
	sdc1	$f6,  THREAD_FPR6(\टhपढ़ो)
	sdc1	$f8,  THREAD_FPR8(\टhपढ़ो)
	sdc1	$f10, THREAD_FPR10(\टhपढ़ो)
	sdc1	$f12, THREAD_FPR12(\टhपढ़ो)
	sdc1	$f14, THREAD_FPR14(\टhपढ़ो)
	sdc1	$f16, THREAD_FPR16(\टhपढ़ो)
	sdc1	$f18, THREAD_FPR18(\टhपढ़ो)
	sdc1	$f20, THREAD_FPR20(\टhपढ़ो)
	sdc1	$f22, THREAD_FPR22(\टhपढ़ो)
	sdc1	$f24, THREAD_FPR24(\टhपढ़ो)
	sdc1	$f26, THREAD_FPR26(\टhपढ़ो)
	sdc1	$f28, THREAD_FPR28(\टhपढ़ो)
	sdc1	$f30, THREAD_FPR30(\टhपढ़ो)
	sw	\टmp, THREAD_FCR31(\टhपढ़ो)
	.set	pop
	.endm

	.macro	fpu_save_16odd thपढ़ो
	.set	push
	.set	mips64r2
	.set	fp=64
	SET_HARDFLOAT
	sdc1	$f1,  THREAD_FPR1(\टhपढ़ो)
	sdc1	$f3,  THREAD_FPR3(\टhपढ़ो)
	sdc1	$f5,  THREAD_FPR5(\टhपढ़ो)
	sdc1	$f7,  THREAD_FPR7(\टhपढ़ो)
	sdc1	$f9,  THREAD_FPR9(\टhपढ़ो)
	sdc1	$f11, THREAD_FPR11(\टhपढ़ो)
	sdc1	$f13, THREAD_FPR13(\टhपढ़ो)
	sdc1	$f15, THREAD_FPR15(\टhपढ़ो)
	sdc1	$f17, THREAD_FPR17(\टhपढ़ो)
	sdc1	$f19, THREAD_FPR19(\टhपढ़ो)
	sdc1	$f21, THREAD_FPR21(\टhपढ़ो)
	sdc1	$f23, THREAD_FPR23(\टhपढ़ो)
	sdc1	$f25, THREAD_FPR25(\टhपढ़ो)
	sdc1	$f27, THREAD_FPR27(\टhपढ़ो)
	sdc1	$f29, THREAD_FPR29(\टhपढ़ो)
	sdc1	$f31, THREAD_FPR31(\टhपढ़ो)
	.set	pop
	.endm

	.macro	fpu_save_द्विगुन thपढ़ो status पंचांगp
#अगर defined(CONFIG_64BIT) || defined(CONFIG_CPU_MIPSR2) || \
    defined(CONFIG_CPU_MIPSR5) || defined(CONFIG_CPU_MIPSR6)
	sll	\टmp, \status, 5
	bgez	\टmp, 10f
	fpu_save_16odd \टhपढ़ो
10:
#पूर्ण_अगर
	fpu_save_16even \टhपढ़ो \टmp
	.endm

	.macro	fpu_restore_16even thपढ़ो पंचांगp=t0
	.set	push
	SET_HARDFLOAT
	lw	\टmp, THREAD_FCR31(\टhपढ़ो)
	ldc1	$f0,  THREAD_FPR0(\टhपढ़ो)
	ldc1	$f2,  THREAD_FPR2(\टhपढ़ो)
	ldc1	$f4,  THREAD_FPR4(\टhपढ़ो)
	ldc1	$f6,  THREAD_FPR6(\टhपढ़ो)
	ldc1	$f8,  THREAD_FPR8(\टhपढ़ो)
	ldc1	$f10, THREAD_FPR10(\टhपढ़ो)
	ldc1	$f12, THREAD_FPR12(\टhपढ़ो)
	ldc1	$f14, THREAD_FPR14(\टhपढ़ो)
	ldc1	$f16, THREAD_FPR16(\टhपढ़ो)
	ldc1	$f18, THREAD_FPR18(\टhपढ़ो)
	ldc1	$f20, THREAD_FPR20(\टhपढ़ो)
	ldc1	$f22, THREAD_FPR22(\टhपढ़ो)
	ldc1	$f24, THREAD_FPR24(\टhपढ़ो)
	ldc1	$f26, THREAD_FPR26(\टhपढ़ो)
	ldc1	$f28, THREAD_FPR28(\टhपढ़ो)
	ldc1	$f30, THREAD_FPR30(\टhपढ़ो)
	ctc1	\टmp, fcr31
	.set	pop
	.endm

	.macro	fpu_restore_16odd thपढ़ो
	.set	push
	.set	mips64r2
	.set	fp=64
	SET_HARDFLOAT
	ldc1	$f1,  THREAD_FPR1(\टhपढ़ो)
	ldc1	$f3,  THREAD_FPR3(\टhपढ़ो)
	ldc1	$f5,  THREAD_FPR5(\टhपढ़ो)
	ldc1	$f7,  THREAD_FPR7(\टhपढ़ो)
	ldc1	$f9,  THREAD_FPR9(\टhपढ़ो)
	ldc1	$f11, THREAD_FPR11(\टhपढ़ो)
	ldc1	$f13, THREAD_FPR13(\टhपढ़ो)
	ldc1	$f15, THREAD_FPR15(\टhपढ़ो)
	ldc1	$f17, THREAD_FPR17(\टhपढ़ो)
	ldc1	$f19, THREAD_FPR19(\टhपढ़ो)
	ldc1	$f21, THREAD_FPR21(\टhपढ़ो)
	ldc1	$f23, THREAD_FPR23(\टhपढ़ो)
	ldc1	$f25, THREAD_FPR25(\टhपढ़ो)
	ldc1	$f27, THREAD_FPR27(\टhपढ़ो)
	ldc1	$f29, THREAD_FPR29(\टhपढ़ो)
	ldc1	$f31, THREAD_FPR31(\टhपढ़ो)
	.set	pop
	.endm

	.macro	fpu_restore_द्विगुन thपढ़ो status पंचांगp
#अगर defined(CONFIG_64BIT) || defined(CONFIG_CPU_MIPSR2) || \
    defined(CONFIG_CPU_MIPSR5) || defined(CONFIG_CPU_MIPSR6)
	sll	\टmp, \status, 5
	bgez	\टmp, 10f				# 16 रेजिस्टर mode?

	fpu_restore_16odd \टhपढ़ो
10:
#पूर्ण_अगर
	fpu_restore_16even \टhपढ़ो \टmp
	.endm

#अगर defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_CPU_MIPSR5) || \
    defined(CONFIG_CPU_MIPSR6)
	.macro	_EXT	rd, rs, p, s
	ext	\लd, \लs, \p, \s
	.endm
#अन्यथा /* !CONFIG_CPU_MIPSR2 && !CONFIG_CPU_MIPSR5 && !CONFIG_CPU_MIPSR6 */
	.macro	_EXT	rd, rs, p, s
	srl	\लd, \लs, \p
	andi	\लd, \लd, (1 << \s) - 1
	.endm
#पूर्ण_अगर /* !CONFIG_CPU_MIPSR2 && !CONFIG_CPU_MIPSR5 && !CONFIG_CPU_MIPSR6 */

/*
 * Temporary until all gas have MT ASE support
 */
	.macro	DMT	reg=0
	.word	0x41600bc1 | (\लeg << 16)
	.endm

	.macro	EMT	reg=0
	.word	0x41600be1 | (\लeg << 16)
	.endm

	.macro	DVPE	reg=0
	.word	0x41600001 | (\लeg << 16)
	.endm

	.macro	EVPE	reg=0
	.word	0x41600021 | (\लeg << 16)
	.endm

	.macro	MFTR	rt=0, rd=0, u=0, sel=0
	 .word	0x41000000 | (\लt << 16) | (\लd << 11) | (\u << 5) | (\sel)
	.endm

	.macro	MTTR	rt=0, rd=0, u=0, sel=0
	 .word	0x41800000 | (\लt << 16) | (\लd << 11) | (\u << 5) | (\sel)
	.endm

#अगर_घोषित TOOLCHAIN_SUPPORTS_MSA
	.macro	_cfcmsa	rd, cs
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	cfcmsa	\लd, $\cs
	.set	pop
	.endm

	.macro	_ctcmsa	cd, rs
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	ctcmsa	$\cd, \लs
	.set	pop
	.endm

	.macro	ld_b	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	ld.b	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	ld_h	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	ld.h	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	ld_w	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	ld.w	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	ld_d	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	ld.d	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	st_b	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	st.b	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	st_h	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	st.h	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	st_w	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	st.w	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	st_d	wd, off, base
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	st.d	$w\wd, \off(\मase)
	.set	pop
	.endm

	.macro	copy_s_w	ws, n
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	copy_s.w $1, $w\ws[\न]
	.set	pop
	.endm

	.macro	copy_s_d	ws, n
	.set	push
	.set	mips64r2
	.set	fp=64
	.set	msa
	copy_s.d $1, $w\ws[\न]
	.set	pop
	.endm

	.macro	insert_w	wd, n
	.set	push
	.set	mips32r2
	.set	fp=64
	.set	msa
	insert.w $w\wd[\न], $1
	.set	pop
	.endm

	.macro	insert_d	wd, n
	.set	push
	.set	mips64r2
	.set	fp=64
	.set	msa
	insert.d $w\wd[\न], $1
	.set	pop
	.endm
#अन्यथा

	/*
	 * Temporary until all toolchains in use include MSA support.
	 */
	.macro	_cfcmsa	rd, cs
	.set	push
	.set	noat
	SET_HARDFLOAT
	insn_अगर_mips 0x787e0059 | (\cs << 11)
	insn32_अगर_mm 0x587e0056 | (\cs << 11)
	move	\लd, $1
	.set	pop
	.endm

	.macro	_ctcmsa	cd, rs
	.set	push
	.set	noat
	SET_HARDFLOAT
	move	$1, \लs
	insn_अगर_mips 0x783e0819 | (\cd << 6)
	insn32_अगर_mm 0x583e0816 | (\cd << 6)
	.set	pop
	.endm

	.macro	ld_b	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000820 | (\wd << 6)
	insn32_अगर_mm 0x58000807 | (\wd << 6)
	.set	pop
	.endm

	.macro	ld_h	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000821 | (\wd << 6)
	insn32_अगर_mm 0x58000817 | (\wd << 6)
	.set	pop
	.endm

	.macro	ld_w	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000822 | (\wd << 6)
	insn32_अगर_mm 0x58000827 | (\wd << 6)
	.set	pop
	.endm

	.macro	ld_d	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000823 | (\wd << 6)
	insn32_अगर_mm 0x58000837 | (\wd << 6)
	.set	pop
	.endm

	.macro	st_b	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000824 | (\wd << 6)
	insn32_अगर_mm 0x5800080f | (\wd << 6)
	.set	pop
	.endm

	.macro	st_h	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000825 | (\wd << 6)
	insn32_अगर_mm 0x5800081f | (\wd << 6)
	.set	pop
	.endm

	.macro	st_w	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000826 | (\wd << 6)
	insn32_अगर_mm 0x5800082f | (\wd << 6)
	.set	pop
	.endm

	.macro	st_d	wd, off, base
	.set	push
	.set	noat
	SET_HARDFLOAT
	PTR_ADDU $1, \मase, \off
	insn_अगर_mips 0x78000827 | (\wd << 6)
	insn32_अगर_mm 0x5800083f | (\wd << 6)
	.set	pop
	.endm

	.macro	copy_s_w	ws, n
	.set	push
	.set	noat
	SET_HARDFLOAT
	insn_अगर_mips 0x78b00059 | (\न << 16) | (\ws << 11)
	insn32_अगर_mm 0x58b00056 | (\न << 16) | (\ws << 11)
	.set	pop
	.endm

	.macro	copy_s_d	ws, n
	.set	push
	.set	noat
	SET_HARDFLOAT
	insn_अगर_mips 0x78b80059 | (\न << 16) | (\ws << 11)
	insn32_अगर_mm 0x58b80056 | (\न << 16) | (\ws << 11)
	.set	pop
	.endm

	.macro	insert_w	wd, n
	.set	push
	.set	noat
	SET_HARDFLOAT
	insn_अगर_mips 0x79300819 | (\न << 16) | (\wd << 6)
	insn32_अगर_mm 0x59300816 | (\न << 16) | (\wd << 6)
	.set	pop
	.endm

	.macro	insert_d	wd, n
	.set	push
	.set	noat
	SET_HARDFLOAT
	insn_अगर_mips 0x79380819 | (\न << 16) | (\wd << 6)
	insn32_अगर_mm 0x59380816 | (\न << 16) | (\wd << 6)
	.set	pop
	.endm
#पूर्ण_अगर

#अगर_घोषित TOOLCHAIN_SUPPORTS_MSA
#घोषणा FPR_BASE_OFFS	THREAD_FPR0
#घोषणा FPR_BASE	$1
#अन्यथा
#घोषणा FPR_BASE_OFFS	0
#घोषणा FPR_BASE	\टhपढ़ो
#पूर्ण_अगर

	.macro	msa_save_all	thपढ़ो
	.set	push
	.set	noat
#अगर_घोषित TOOLCHAIN_SUPPORTS_MSA
	PTR_ADDU FPR_BASE, \टhपढ़ो, FPR_BASE_OFFS
#पूर्ण_अगर
	st_d	 0, THREAD_FPR0  - FPR_BASE_OFFS, FPR_BASE
	st_d	 1, THREAD_FPR1  - FPR_BASE_OFFS, FPR_BASE
	st_d	 2, THREAD_FPR2  - FPR_BASE_OFFS, FPR_BASE
	st_d	 3, THREAD_FPR3  - FPR_BASE_OFFS, FPR_BASE
	st_d	 4, THREAD_FPR4  - FPR_BASE_OFFS, FPR_BASE
	st_d	 5, THREAD_FPR5  - FPR_BASE_OFFS, FPR_BASE
	st_d	 6, THREAD_FPR6  - FPR_BASE_OFFS, FPR_BASE
	st_d	 7, THREAD_FPR7  - FPR_BASE_OFFS, FPR_BASE
	st_d	 8, THREAD_FPR8  - FPR_BASE_OFFS, FPR_BASE
	st_d	 9, THREAD_FPR9  - FPR_BASE_OFFS, FPR_BASE
	st_d	10, THREAD_FPR10 - FPR_BASE_OFFS, FPR_BASE
	st_d	11, THREAD_FPR11 - FPR_BASE_OFFS, FPR_BASE
	st_d	12, THREAD_FPR12 - FPR_BASE_OFFS, FPR_BASE
	st_d	13, THREAD_FPR13 - FPR_BASE_OFFS, FPR_BASE
	st_d	14, THREAD_FPR14 - FPR_BASE_OFFS, FPR_BASE
	st_d	15, THREAD_FPR15 - FPR_BASE_OFFS, FPR_BASE
	st_d	16, THREAD_FPR16 - FPR_BASE_OFFS, FPR_BASE
	st_d	17, THREAD_FPR17 - FPR_BASE_OFFS, FPR_BASE
	st_d	18, THREAD_FPR18 - FPR_BASE_OFFS, FPR_BASE
	st_d	19, THREAD_FPR19 - FPR_BASE_OFFS, FPR_BASE
	st_d	20, THREAD_FPR20 - FPR_BASE_OFFS, FPR_BASE
	st_d	21, THREAD_FPR21 - FPR_BASE_OFFS, FPR_BASE
	st_d	22, THREAD_FPR22 - FPR_BASE_OFFS, FPR_BASE
	st_d	23, THREAD_FPR23 - FPR_BASE_OFFS, FPR_BASE
	st_d	24, THREAD_FPR24 - FPR_BASE_OFFS, FPR_BASE
	st_d	25, THREAD_FPR25 - FPR_BASE_OFFS, FPR_BASE
	st_d	26, THREAD_FPR26 - FPR_BASE_OFFS, FPR_BASE
	st_d	27, THREAD_FPR27 - FPR_BASE_OFFS, FPR_BASE
	st_d	28, THREAD_FPR28 - FPR_BASE_OFFS, FPR_BASE
	st_d	29, THREAD_FPR29 - FPR_BASE_OFFS, FPR_BASE
	st_d	30, THREAD_FPR30 - FPR_BASE_OFFS, FPR_BASE
	st_d	31, THREAD_FPR31 - FPR_BASE_OFFS, FPR_BASE
	SET_HARDFLOAT
	_cfcmsa	$1, MSA_CSR
	sw	$1, THREAD_MSA_CSR(\टhपढ़ो)
	.set	pop
	.endm

	.macro	msa_restore_all	thपढ़ो
	.set	push
	.set	noat
	SET_HARDFLOAT
	lw	$1, THREAD_MSA_CSR(\टhपढ़ो)
	_ctcmsa	MSA_CSR, $1
#अगर_घोषित TOOLCHAIN_SUPPORTS_MSA
	PTR_ADDU FPR_BASE, \टhपढ़ो, FPR_BASE_OFFS
#पूर्ण_अगर
	ld_d	 0, THREAD_FPR0  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 1, THREAD_FPR1  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 2, THREAD_FPR2  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 3, THREAD_FPR3  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 4, THREAD_FPR4  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 5, THREAD_FPR5  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 6, THREAD_FPR6  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 7, THREAD_FPR7  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 8, THREAD_FPR8  - FPR_BASE_OFFS, FPR_BASE
	ld_d	 9, THREAD_FPR9  - FPR_BASE_OFFS, FPR_BASE
	ld_d	10, THREAD_FPR10 - FPR_BASE_OFFS, FPR_BASE
	ld_d	11, THREAD_FPR11 - FPR_BASE_OFFS, FPR_BASE
	ld_d	12, THREAD_FPR12 - FPR_BASE_OFFS, FPR_BASE
	ld_d	13, THREAD_FPR13 - FPR_BASE_OFFS, FPR_BASE
	ld_d	14, THREAD_FPR14 - FPR_BASE_OFFS, FPR_BASE
	ld_d	15, THREAD_FPR15 - FPR_BASE_OFFS, FPR_BASE
	ld_d	16, THREAD_FPR16 - FPR_BASE_OFFS, FPR_BASE
	ld_d	17, THREAD_FPR17 - FPR_BASE_OFFS, FPR_BASE
	ld_d	18, THREAD_FPR18 - FPR_BASE_OFFS, FPR_BASE
	ld_d	19, THREAD_FPR19 - FPR_BASE_OFFS, FPR_BASE
	ld_d	20, THREAD_FPR20 - FPR_BASE_OFFS, FPR_BASE
	ld_d	21, THREAD_FPR21 - FPR_BASE_OFFS, FPR_BASE
	ld_d	22, THREAD_FPR22 - FPR_BASE_OFFS, FPR_BASE
	ld_d	23, THREAD_FPR23 - FPR_BASE_OFFS, FPR_BASE
	ld_d	24, THREAD_FPR24 - FPR_BASE_OFFS, FPR_BASE
	ld_d	25, THREAD_FPR25 - FPR_BASE_OFFS, FPR_BASE
	ld_d	26, THREAD_FPR26 - FPR_BASE_OFFS, FPR_BASE
	ld_d	27, THREAD_FPR27 - FPR_BASE_OFFS, FPR_BASE
	ld_d	28, THREAD_FPR28 - FPR_BASE_OFFS, FPR_BASE
	ld_d	29, THREAD_FPR29 - FPR_BASE_OFFS, FPR_BASE
	ld_d	30, THREAD_FPR30 - FPR_BASE_OFFS, FPR_BASE
	ld_d	31, THREAD_FPR31 - FPR_BASE_OFFS, FPR_BASE
	.set pop
	.endm

#अघोषित FPR_BASE_OFFS
#अघोषित FPR_BASE

	.macro	msa_init_upper wd
#अगर_घोषित CONFIG_64BIT
	insert_d \wd, 1
#अन्यथा
	insert_w \wd, 2
	insert_w \wd, 3
#पूर्ण_अगर
	.endm

	.macro	msa_init_all_upper
	.set	push
	.set	noat
	SET_HARDFLOAT
	not	$1, zero
	msa_init_upper	0
	msa_init_upper	1
	msa_init_upper	2
	msa_init_upper	3
	msa_init_upper	4
	msa_init_upper	5
	msa_init_upper	6
	msa_init_upper	7
	msa_init_upper	8
	msa_init_upper	9
	msa_init_upper	10
	msa_init_upper	11
	msa_init_upper	12
	msa_init_upper	13
	msa_init_upper	14
	msa_init_upper	15
	msa_init_upper	16
	msa_init_upper	17
	msa_init_upper	18
	msa_init_upper	19
	msa_init_upper	20
	msa_init_upper	21
	msa_init_upper	22
	msa_init_upper	23
	msa_init_upper	24
	msa_init_upper	25
	msa_init_upper	26
	msa_init_upper	27
	msa_init_upper	28
	msa_init_upper	29
	msa_init_upper	30
	msa_init_upper	31
	.set	pop
	.endm

#पूर्ण_अगर /* _ASM_ASMMACRO_H */
