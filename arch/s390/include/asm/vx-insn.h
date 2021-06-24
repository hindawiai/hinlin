<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Vector Inकाष्ठाions
 *
 * Assembler macros to generate .byte/.word code क्रम particular
 * vector inकाष्ठाions that are supported by recent binutils (>= 2.26) only.
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */

#अगर_अघोषित __ASM_S390_VX_INSN_H
#घोषणा __ASM_S390_VX_INSN_H

#अगर_घोषित __ASSEMBLY__


/* Macros to generate vector inकाष्ठाion byte code */

/* GR_NUM - Retrieve general-purpose रेजिस्टर number
 *
 * @opd:	Opeअक्रम to store रेजिस्टर number
 * @r64:	String designation रेजिस्टर in the क्रमmat "%rN"
 */
.macro	GR_NUM	opd gr
	\opd = 255
	.अगरc \gr,%r0
		\opd = 0
	.endअगर
	.अगरc \gr,%r1
		\opd = 1
	.endअगर
	.अगरc \gr,%r2
		\opd = 2
	.endअगर
	.अगरc \gr,%r3
		\opd = 3
	.endअगर
	.अगरc \gr,%r4
		\opd = 4
	.endअगर
	.अगरc \gr,%r5
		\opd = 5
	.endअगर
	.अगरc \gr,%r6
		\opd = 6
	.endअगर
	.अगरc \gr,%r7
		\opd = 7
	.endअगर
	.अगरc \gr,%r8
		\opd = 8
	.endअगर
	.अगरc \gr,%r9
		\opd = 9
	.endअगर
	.अगरc \gr,%r10
		\opd = 10
	.endअगर
	.अगरc \gr,%r11
		\opd = 11
	.endअगर
	.अगरc \gr,%r12
		\opd = 12
	.endअगर
	.अगरc \gr,%r13
		\opd = 13
	.endअगर
	.अगरc \gr,%r14
		\opd = 14
	.endअगर
	.अगरc \gr,%r15
		\opd = 15
	.endअगर
	.अगर \opd == 255
		\opd = \gr
	.endअगर
.endm

/* VX_NUM - Retrieve vector रेजिस्टर number
 *
 * @opd:	Opeअक्रम to store रेजिस्टर number
 * @vxr:	String designation रेजिस्टर in the क्रमmat "%vN"
 *
 * The vector रेजिस्टर number is used क्रम as input number to the
 * inकाष्ठाion and, as well as, to compute the RXB field of the
 * inकाष्ठाion.
 */
.macro	VX_NUM	opd vxr
	\opd = 255
	.अगरc \खxr,%v0
		\opd = 0
	.endअगर
	.अगरc \खxr,%v1
		\opd = 1
	.endअगर
	.अगरc \खxr,%v2
		\opd = 2
	.endअगर
	.अगरc \खxr,%v3
		\opd = 3
	.endअगर
	.अगरc \खxr,%v4
		\opd = 4
	.endअगर
	.अगरc \खxr,%v5
		\opd = 5
	.endअगर
	.अगरc \खxr,%v6
		\opd = 6
	.endअगर
	.अगरc \खxr,%v7
		\opd = 7
	.endअगर
	.अगरc \खxr,%v8
		\opd = 8
	.endअगर
	.अगरc \खxr,%v9
		\opd = 9
	.endअगर
	.अगरc \खxr,%v10
		\opd = 10
	.endअगर
	.अगरc \खxr,%v11
		\opd = 11
	.endअगर
	.अगरc \खxr,%v12
		\opd = 12
	.endअगर
	.अगरc \खxr,%v13
		\opd = 13
	.endअगर
	.अगरc \खxr,%v14
		\opd = 14
	.endअगर
	.अगरc \खxr,%v15
		\opd = 15
	.endअगर
	.अगरc \खxr,%v16
		\opd = 16
	.endअगर
	.अगरc \खxr,%v17
		\opd = 17
	.endअगर
	.अगरc \खxr,%v18
		\opd = 18
	.endअगर
	.अगरc \खxr,%v19
		\opd = 19
	.endअगर
	.अगरc \खxr,%v20
		\opd = 20
	.endअगर
	.अगरc \खxr,%v21
		\opd = 21
	.endअगर
	.अगरc \खxr,%v22
		\opd = 22
	.endअगर
	.अगरc \खxr,%v23
		\opd = 23
	.endअगर
	.अगरc \खxr,%v24
		\opd = 24
	.endअगर
	.अगरc \खxr,%v25
		\opd = 25
	.endअगर
	.अगरc \खxr,%v26
		\opd = 26
	.endअगर
	.अगरc \खxr,%v27
		\opd = 27
	.endअगर
	.अगरc \खxr,%v28
		\opd = 28
	.endअगर
	.अगरc \खxr,%v29
		\opd = 29
	.endअगर
	.अगरc \खxr,%v30
		\opd = 30
	.endअगर
	.अगरc \खxr,%v31
		\opd = 31
	.endअगर
	.अगर \opd == 255
		\opd = \खxr
	.endअगर
.endm

/* RXB - Compute most signअगरicant bit used vector रेजिस्टरs
 *
 * @rxb:	Opeअक्रम to store computed RXB value
 * @v1:		First vector रेजिस्टर designated opeअक्रम
 * @v2:		Second vector रेजिस्टर designated opeअक्रम
 * @v3:		Third vector रेजिस्टर designated opeअक्रम
 * @v4:		Fourth vector रेजिस्टर designated opeअक्रम
 */
.macro	RXB	rxb v1 v2=0 v3=0 v4=0
	\लxb = 0
	.अगर \ख1 & 0x10
		\लxb = \लxb | 0x08
	.endअगर
	.अगर \ख2 & 0x10
		\लxb = \लxb | 0x04
	.endअगर
	.अगर \ख3 & 0x10
		\लxb = \लxb | 0x02
	.endअगर
	.अगर \ख4 & 0x10
		\लxb = \लxb | 0x01
	.endअगर
.endm

/* MRXB - Generate Element Size Control and RXB value
 *
 * @m:		Element size control
 * @v1:		First vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 * @v2:		Second vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 * @v3:		Third vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 * @v4:		Fourth vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 */
.macro	MRXB	m v1 v2=0 v3=0 v4=0
	rxb = 0
	RXB	rxb, \ख1, \ख2, \ख3, \ख4
	.byte	(\m << 4) | rxb
.endm

/* MRXBOPC - Generate Element Size Control, RXB, and final Opcode fields
 *
 * @m:		Element size control
 * @opc:	Opcode
 * @v1:		First vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 * @v2:		Second vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 * @v3:		Third vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 * @v4:		Fourth vector रेजिस्टर designated opeअक्रम (क्रम RXB)
 */
.macro	MRXBOPC	m opc v1 v2=0 v3=0 v4=0
	MRXB	\m, \ख1, \ख2, \ख3, \ख4
	.byte	\opc
.endm

/* Vector support inकाष्ठाions */

/* VECTOR GENERATE BYTE MASK */
.macro	VGBM	vr imm2
	VX_NUM	v1, \खr
	.word	(0xE700 | ((v1&15) << 4))
	.word	\imm2
	MRXBOPC	0, 0x44, v1
.endm
.macro	VZERO	vxr
	VGBM	\खxr, 0
.endm
.macro	VONE	vxr
	VGBM	\खxr, 0xFFFF
.endm

/* VECTOR LOAD VR ELEMENT FROM GR */
.macro	VLVG	v, gr, disp, m
	VX_NUM	v1, \ख
	GR_NUM	b2, "%r0"
	GR_NUM	r3, \gr
	.word	0xE700 | ((v1&15) << 4) | r3
	.word	(b2 << 12) | (\disp)
	MRXBOPC	\m, 0x22, v1
.endm
.macro	VLVGB	v, gr, index, base
	VLVG	\ख, \gr, \index, \मase, 0
.endm
.macro	VLVGH	v, gr, index
	VLVG	\ख, \gr, \index, 1
.endm
.macro	VLVGF	v, gr, index
	VLVG	\ख, \gr, \index, 2
.endm
.macro	VLVGG	v, gr, index
	VLVG	\ख, \gr, \index, 3
.endm

/* VECTOR LOAD REGISTER */
.macro	VLR	v1, v2
	VX_NUM	v1, \ख1
	VX_NUM	v2, \ख2
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	0
	MRXBOPC	0, 0x56, v1, v2
.endm

/* VECTOR LOAD */
.macro	VL	v, disp, index="%r0", base
	VX_NUM	v1, \ख
	GR_NUM	x2, \index
	GR_NUM	b2, \मase
	.word	0xE700 | ((v1&15) << 4) | x2
	.word	(b2 << 12) | (\disp)
	MRXBOPC 0, 0x06, v1
.endm

/* VECTOR LOAD ELEMENT */
.macro	VLEx	vr1, disp, index="%r0", base, m3, opc
	VX_NUM	v1, \खr1
	GR_NUM	x2, \index
	GR_NUM	b2, \मase
	.word	0xE700 | ((v1&15) << 4) | x2
	.word	(b2 << 12) | (\disp)
	MRXBOPC	\m3, \opc, v1
.endm
.macro	VLEB	vr1, disp, index="%r0", base, m3
	VLEx	\खr1, \disp, \index, \मase, \m3, 0x00
.endm
.macro	VLEH	vr1, disp, index="%r0", base, m3
	VLEx	\खr1, \disp, \index, \मase, \m3, 0x01
.endm
.macro	VLEF	vr1, disp, index="%r0", base, m3
	VLEx	\खr1, \disp, \index, \मase, \m3, 0x03
.endm
.macro	VLEG	vr1, disp, index="%r0", base, m3
	VLEx	\खr1, \disp, \index, \मase, \m3, 0x02
.endm

/* VECTOR LOAD ELEMENT IMMEDIATE */
.macro	VLEIx	vr1, imm2, m3, opc
	VX_NUM	v1, \खr1
	.word	0xE700 | ((v1&15) << 4)
	.word	\imm2
	MRXBOPC	\m3, \opc, v1
.endm
.macro	VLEIB	vr1, imm2, index
	VLEIx	\खr1, \imm2, \index, 0x40
.endm
.macro	VLEIH	vr1, imm2, index
	VLEIx	\खr1, \imm2, \index, 0x41
.endm
.macro	VLEIF	vr1, imm2, index
	VLEIx	\खr1, \imm2, \index, 0x43
.endm
.macro	VLEIG	vr1, imm2, index
	VLEIx	\खr1, \imm2, \index, 0x42
.endm

/* VECTOR LOAD GR FROM VR ELEMENT */
.macro	VLGV	gr, vr, disp, base="%r0", m
	GR_NUM	r1, \gr
	GR_NUM	b2, \मase
	VX_NUM	v3, \खr
	.word	0xE700 | (r1 << 4) | (v3&15)
	.word	(b2 << 12) | (\disp)
	MRXBOPC	\m, 0x21, v3
.endm
.macro	VLGVB	gr, vr, disp, base="%r0"
	VLGV	\gr, \खr, \disp, \मase, 0
.endm
.macro	VLGVH	gr, vr, disp, base="%r0"
	VLGV	\gr, \खr, \disp, \मase, 1
.endm
.macro	VLGVF	gr, vr, disp, base="%r0"
	VLGV	\gr, \खr, \disp, \मase, 2
.endm
.macro	VLGVG	gr, vr, disp, base="%r0"
	VLGV	\gr, \खr, \disp, \मase, 3
.endm

/* VECTOR LOAD MULTIPLE */
.macro	VLM	vfrom, vto, disp, base, hपूर्णांक=3
	VX_NUM	v1, \खfrom
	VX_NUM	v3, \खto
	GR_NUM	b2, \मase	    /* Base रेजिस्टर */
	.word	0xE700 | ((v1&15) << 4) | (v3&15)
	.word	(b2 << 12) | (\disp)
	MRXBOPC	\hपूर्णांक, 0x36, v1, v3
.endm

/* VECTOR STORE MULTIPLE */
.macro	VSTM	vfrom, vto, disp, base, hपूर्णांक=3
	VX_NUM	v1, \खfrom
	VX_NUM	v3, \खto
	GR_NUM	b2, \मase	    /* Base रेजिस्टर */
	.word	0xE700 | ((v1&15) << 4) | (v3&15)
	.word	(b2 << 12) | (\disp)
	MRXBOPC	\hपूर्णांक, 0x3E, v1, v3
.endm

/* VECTOR PERMUTE */
.macro	VPERM	vr1, vr2, vr3, vr4
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	VX_NUM	v4, \खr4
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC	(v4&15), 0x8C, v1, v2, v3, v4
.endm

/* VECTOR UNPACK LOGICAL LOW */
.macro	VUPLL	vr1, vr2, m3
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	0x0000
	MRXBOPC	\m3, 0xD4, v1, v2
.endm
.macro	VUPLLB	vr1, vr2
	VUPLL	\खr1, \खr2, 0
.endm
.macro	VUPLLH	vr1, vr2
	VUPLL	\खr1, \खr2, 1
.endm
.macro	VUPLLF	vr1, vr2
	VUPLL	\खr1, \खr2, 2
.endm


/* Vector पूर्णांकeger inकाष्ठाions */

/* VECTOR AND */
.macro	VN	vr1, vr2, vr3
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC	0, 0x68, v1, v2, v3
.endm

/* VECTOR EXCLUSIVE OR */
.macro	VX	vr1, vr2, vr3
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC	0, 0x6D, v1, v2, v3
.endm

/* VECTOR GALOIS FIELD MULTIPLY SUM */
.macro	VGFM	vr1, vr2, vr3, m4
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC	\m4, 0xB4, v1, v2, v3
.endm
.macro	VGFMB	vr1, vr2, vr3
	VGFM	\खr1, \खr2, \खr3, 0
.endm
.macro	VGFMH	vr1, vr2, vr3
	VGFM	\खr1, \खr2, \खr3, 1
.endm
.macro	VGFMF	vr1, vr2, vr3
	VGFM	\खr1, \खr2, \खr3, 2
.endm
.macro	VGFMG	vr1, vr2, vr3
	VGFM	\खr1, \खr2, \खr3, 3
.endm

/* VECTOR GALOIS FIELD MULTIPLY SUM AND ACCUMULATE */
.macro	VGFMA	vr1, vr2, vr3, vr4, m5
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	VX_NUM	v4, \खr4
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12) | (\m5 << 8)
	MRXBOPC	(v4&15), 0xBC, v1, v2, v3, v4
.endm
.macro	VGFMAB	vr1, vr2, vr3, vr4
	VGFMA	\खr1, \खr2, \खr3, \खr4, 0
.endm
.macro	VGFMAH	vr1, vr2, vr3, vr4
	VGFMA	\खr1, \खr2, \खr3, \खr4, 1
.endm
.macro	VGFMAF	vr1, vr2, vr3, vr4
	VGFMA	\खr1, \खr2, \खr3, \खr4, 2
.endm
.macro	VGFMAG	vr1, vr2, vr3, vr4
	VGFMA	\खr1, \खr2, \खr3, \खr4, 3
.endm

/* VECTOR SHIFT RIGHT LOGICAL BY BYTE */
.macro	VSRLB	vr1, vr2, vr3
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC	0, 0x7D, v1, v2, v3
.endm

/* VECTOR REPLICATE IMMEDIATE */
.macro	VREPI	vr1, imm2, m3
	VX_NUM	v1, \खr1
	.word	0xE700 | ((v1&15) << 4)
	.word	\imm2
	MRXBOPC	\m3, 0x45, v1
.endm
.macro	VREPIB	vr1, imm2
	VREPI	\खr1, \imm2, 0
.endm
.macro	VREPIH	vr1, imm2
	VREPI	\खr1, \imm2, 1
.endm
.macro	VREPIF	vr1, imm2
	VREPI	\खr1, \imm2, 2
.endm
.macro	VREPIG	vr1, imm2
	VREP	\खr1, \imm2, 3
.endm

/* VECTOR ADD */
.macro	VA	vr1, vr2, vr3, m4
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC	\m4, 0xF3, v1, v2, v3
.endm
.macro	VAB	vr1, vr2, vr3
	VA	\खr1, \खr2, \खr3, 0
.endm
.macro	VAH	vr1, vr2, vr3
	VA	\खr1, \खr2, \खr3, 1
.endm
.macro	VAF	vr1, vr2, vr3
	VA	\खr1, \खr2, \खr3, 2
.endm
.macro	VAG	vr1, vr2, vr3
	VA	\खr1, \खr2, \खr3, 3
.endm
.macro	VAQ	vr1, vr2, vr3
	VA	\खr1, \खr2, \खr3, 4
.endm

/* VECTOR ELEMENT SHIFT RIGHT ARITHMETIC */
.macro	VESRAV	vr1, vr2, vr3, m4
	VX_NUM	v1, \खr1
	VX_NUM	v2, \खr2
	VX_NUM	v3, \खr3
	.word	0xE700 | ((v1&15) << 4) | (v2&15)
	.word	((v3&15) << 12)
	MRXBOPC \m4, 0x7A, v1, v2, v3
.endm

.macro	VESRAVB	vr1, vr2, vr3
	VESRAV	\खr1, \खr2, \खr3, 0
.endm
.macro	VESRAVH	vr1, vr2, vr3
	VESRAV	\खr1, \खr2, \खr3, 1
.endm
.macro	VESRAVF	vr1, vr2, vr3
	VESRAV	\खr1, \खr2, \खr3, 2
.endm
.macro	VESRAVG	vr1, vr2, vr3
	VESRAV	\खr1, \खr2, \खr3, 3
.endm

#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर	/* __ASM_S390_VX_INSN_H */
