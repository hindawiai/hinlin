<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * FP/SIMD state saving and restoring macros
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */

#समावेश <यंत्र/assembler.h>

.macro fpsimd_save state, पंचांगpnr
	stp	q0, q1, [\state, #16 * 0]
	stp	q2, q3, [\state, #16 * 2]
	stp	q4, q5, [\state, #16 * 4]
	stp	q6, q7, [\state, #16 * 6]
	stp	q8, q9, [\state, #16 * 8]
	stp	q10, q11, [\state, #16 * 10]
	stp	q12, q13, [\state, #16 * 12]
	stp	q14, q15, [\state, #16 * 14]
	stp	q16, q17, [\state, #16 * 16]
	stp	q18, q19, [\state, #16 * 18]
	stp	q20, q21, [\state, #16 * 20]
	stp	q22, q23, [\state, #16 * 22]
	stp	q24, q25, [\state, #16 * 24]
	stp	q26, q27, [\state, #16 * 26]
	stp	q28, q29, [\state, #16 * 28]
	stp	q30, q31, [\state, #16 * 30]!
	mrs	x\टmpnr, fpsr
	str	w\टmpnr, [\state, #16 * 2]
	mrs	x\टmpnr, fpcr
	str	w\टmpnr, [\state, #16 * 2 + 4]
.endm

.macro fpsimd_restore_fpcr state, पंचांगp
	/*
	 * Writes to fpcr may be self-synchronising, so aव्योम restoring
	 * the रेजिस्टर अगर it hasn't changed.
	 */
	mrs	\टmp, fpcr
	cmp	\टmp, \state
	b.eq	9999f
	msr	fpcr, \state
9999:
.endm

/* Clobbers \state */
.macro fpsimd_restore state, पंचांगpnr
	ldp	q0, q1, [\state, #16 * 0]
	ldp	q2, q3, [\state, #16 * 2]
	ldp	q4, q5, [\state, #16 * 4]
	ldp	q6, q7, [\state, #16 * 6]
	ldp	q8, q9, [\state, #16 * 8]
	ldp	q10, q11, [\state, #16 * 10]
	ldp	q12, q13, [\state, #16 * 12]
	ldp	q14, q15, [\state, #16 * 14]
	ldp	q16, q17, [\state, #16 * 16]
	ldp	q18, q19, [\state, #16 * 18]
	ldp	q20, q21, [\state, #16 * 20]
	ldp	q22, q23, [\state, #16 * 22]
	ldp	q24, q25, [\state, #16 * 24]
	ldp	q26, q27, [\state, #16 * 26]
	ldp	q28, q29, [\state, #16 * 28]
	ldp	q30, q31, [\state, #16 * 30]!
	ldr	w\टmpnr, [\state, #16 * 2]
	msr	fpsr, x\टmpnr
	ldr	w\टmpnr, [\state, #16 * 2 + 4]
	fpsimd_restore_fpcr x\टmpnr, \state
.endm

/* Sanity-check macros to help aव्योम encoding garbage inकाष्ठाions */

.macro _check_general_reg nr
	.अगर (\नr) < 0 || (\नr) > 30
		.error "Bad register number \nr."
	.endअगर
.endm

.macro _sve_check_zreg znr
	.अगर (\znr) < 0 || (\znr) > 31
		.error "Bad Scalable Vector Extension vector register number \znr."
	.endअगर
.endm

.macro _sve_check_preg pnr
	.अगर (\pnr) < 0 || (\pnr) > 15
		.error "Bad Scalable Vector Extension predicate register number \pnr."
	.endअगर
.endm

.macro _check_num n, min, max
	.अगर (\न) < (\min) || (\न) > (\max)
		.error "Number \n out of range [\min,\max]"
	.endअगर
.endm

/* SVE inकाष्ठाion encodings क्रम non-SVE-capable assemblers */

/* STR (vector): STR Z\नz, [X\नxbase, #\offset, MUL VL] */
.macro _sve_str_v nz, nxbase, offset=0
	_sve_check_zreg \नz
	_check_general_reg \नxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0xe5804000			\
		| (\नz)				\
		| ((\नxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* LDR (vector): LDR Z\नz, [X\नxbase, #\offset, MUL VL] */
.macro _sve_ldr_v nz, nxbase, offset=0
	_sve_check_zreg \नz
	_check_general_reg \नxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0x85804000			\
		| (\नz)				\
		| ((\नxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* STR (predicate): STR P\नp, [X\नxbase, #\offset, MUL VL] */
.macro _sve_str_p np, nxbase, offset=0
	_sve_check_preg \नp
	_check_general_reg \नxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0xe5800000			\
		| (\नp)				\
		| ((\नxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* LDR (predicate): LDR P\नp, [X\नxbase, #\offset, MUL VL] */
.macro _sve_ldr_p np, nxbase, offset=0
	_sve_check_preg \नp
	_check_general_reg \नxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0x85800000			\
		| (\नp)				\
		| ((\नxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* RDVL X\नx, #\imm */
.macro _sve_rdvl nx, imm
	_check_general_reg \नx
	_check_num (\imm), -0x20, 0x1f
	.inst	0x04bf5000			\
		| (\नx)				\
		| (((\imm) & 0x3f) << 5)
.endm

/* RDFFR (unpredicated): RDFFR P\नp.B */
.macro _sve_rdffr np
	_sve_check_preg \नp
	.inst	0x2519f000			\
		| (\नp)
.endm

/* WRFFR P\नp.B */
.macro _sve_wrffr np
	_sve_check_preg \नp
	.inst	0x25289000			\
		| ((\नp) << 5)
.endm

/* PFALSE P\नp.B */
.macro _sve_pfalse np
	_sve_check_preg \नp
	.inst	0x2518e400			\
		| (\नp)
.endm

.macro __क्रम from:req, to:req
	.अगर (\पrom) == (\टo)
		_क्रम__body %\पrom
	.अन्यथा
		__क्रम %\पrom, %((\पrom) + ((\टo) - (\पrom)) / 2)
		__क्रम %((\पrom) + ((\टo) - (\पrom)) / 2 + 1), %\टo
	.endअगर
.endm

.macro _क्रम var:req, from:req, to:req, insn:vararg
	.macro _क्रम__body \खar:req
		.noalपंचांगacro
		\insn
		.alपंचांगacro
	.endm

	.alपंचांगacro
	__क्रम \पrom, \टo
	.noalपंचांगacro

	.purgem _क्रम__body
.endm

/* Update ZCR_EL1.LEN with the new VQ */
.macro sve_load_vq xvqminus1, xपंचांगp, xपंचांगp2
		mrs_s		\षपंचांगp, SYS_ZCR_EL1
		bic		\षपंचांगp2, \षपंचांगp, ZCR_ELx_LEN_MASK
		orr		\षपंचांगp2, \षपंचांगp2, \षvqminus1
		cmp		\षपंचांगp2, \षपंचांगp
		b.eq		921f
		msr_s		SYS_ZCR_EL1, \षपंचांगp2	//self-synchronising
921:
.endm

/* Preserve the first 128-bits of Znz and zero the rest. */
.macro _sve_flush_z nz
	_sve_check_zreg \नz
	mov	v\नz\().16b, v\नz\().16b
.endm

.macro sve_flush
 _क्रम n, 0, 31, _sve_flush_z	\न
 _क्रम n, 0, 15, _sve_pfalse	\न
		_sve_wrffr	0
.endm

.macro sve_save nxbase, xpfpsr, nxपंचांगp
 _क्रम n, 0, 31,	_sve_str_v	\न, \नxbase, \न - 34
 _क्रम n, 0, 15,	_sve_str_p	\न, \नxbase, \न - 16
		_sve_rdffr	0
		_sve_str_p	0, \नxbase
		_sve_ldr_p	0, \नxbase, -16

		mrs		x\नxपंचांगp, fpsr
		str		w\नxपंचांगp, [\षpfpsr]
		mrs		x\नxपंचांगp, fpcr
		str		w\नxपंचांगp, [\षpfpsr, #4]
.endm

.macro __sve_load nxbase, xpfpsr, nxपंचांगp
 _क्रम n, 0, 31,	_sve_ldr_v	\न, \नxbase, \न - 34
		_sve_ldr_p	0, \नxbase
		_sve_wrffr	0
 _क्रम n, 0, 15,	_sve_ldr_p	\न, \नxbase, \न - 16

		ldr		w\नxपंचांगp, [\षpfpsr]
		msr		fpsr, x\नxपंचांगp
		ldr		w\नxपंचांगp, [\षpfpsr, #4]
		msr		fpcr, x\नxपंचांगp
.endm

.macro sve_load nxbase, xpfpsr, xvqminus1, nxपंचांगp, xपंचांगp2
		sve_load_vq	\षvqminus1, x\नxपंचांगp, \षपंचांगp2
		__sve_load	\नxbase, \षpfpsr, \नxपंचांगp
.endm
