<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 SiFive
 */

#समावेश <linux/bits.h>

/* The bit field of immediate value in I-type inकाष्ठाion */
#घोषणा I_IMM_SIGN_OPOFF	31
#घोषणा I_IMM_11_0_OPOFF	20
#घोषणा I_IMM_SIGN_OFF		12
#घोषणा I_IMM_11_0_OFF		0
#घोषणा I_IMM_11_0_MASK		GENMASK(11, 0)

/* The bit field of immediate value in J-type inकाष्ठाion */
#घोषणा J_IMM_SIGN_OPOFF	31
#घोषणा J_IMM_10_1_OPOFF	21
#घोषणा J_IMM_11_OPOFF		20
#घोषणा J_IMM_19_12_OPOFF	12
#घोषणा J_IMM_SIGN_OFF		20
#घोषणा J_IMM_10_1_OFF		1
#घोषणा J_IMM_11_OFF		11
#घोषणा J_IMM_19_12_OFF		12
#घोषणा J_IMM_10_1_MASK		GENMASK(9, 0)
#घोषणा J_IMM_11_MASK		GENMASK(0, 0)
#घोषणा J_IMM_19_12_MASK	GENMASK(7, 0)

/* The bit field of immediate value in B-type inकाष्ठाion */
#घोषणा B_IMM_SIGN_OPOFF	31
#घोषणा B_IMM_10_5_OPOFF	25
#घोषणा B_IMM_4_1_OPOFF		8
#घोषणा B_IMM_11_OPOFF		7
#घोषणा B_IMM_SIGN_OFF		12
#घोषणा B_IMM_10_5_OFF		5
#घोषणा B_IMM_4_1_OFF		1
#घोषणा B_IMM_11_OFF		11
#घोषणा B_IMM_10_5_MASK		GENMASK(5, 0)
#घोषणा B_IMM_4_1_MASK		GENMASK(3, 0)
#घोषणा B_IMM_11_MASK		GENMASK(0, 0)

/* The रेजिस्टर offset in RVG inकाष्ठाion */
#घोषणा RVG_RS1_OPOFF		15
#घोषणा RVG_RS2_OPOFF		20
#घोषणा RVG_RD_OPOFF		7

/* The bit field of immediate value in RVC J inकाष्ठाion */
#घोषणा RVC_J_IMM_SIGN_OPOFF	12
#घोषणा RVC_J_IMM_4_OPOFF	11
#घोषणा RVC_J_IMM_9_8_OPOFF	9
#घोषणा RVC_J_IMM_10_OPOFF	8
#घोषणा RVC_J_IMM_6_OPOFF	7
#घोषणा RVC_J_IMM_7_OPOFF	6
#घोषणा RVC_J_IMM_3_1_OPOFF	3
#घोषणा RVC_J_IMM_5_OPOFF	2
#घोषणा RVC_J_IMM_SIGN_OFF	11
#घोषणा RVC_J_IMM_4_OFF		4
#घोषणा RVC_J_IMM_9_8_OFF	8
#घोषणा RVC_J_IMM_10_OFF	10
#घोषणा RVC_J_IMM_6_OFF		6
#घोषणा RVC_J_IMM_7_OFF		7
#घोषणा RVC_J_IMM_3_1_OFF	1
#घोषणा RVC_J_IMM_5_OFF		5
#घोषणा RVC_J_IMM_4_MASK	GENMASK(0, 0)
#घोषणा RVC_J_IMM_9_8_MASK	GENMASK(1, 0)
#घोषणा RVC_J_IMM_10_MASK	GENMASK(0, 0)
#घोषणा RVC_J_IMM_6_MASK	GENMASK(0, 0)
#घोषणा RVC_J_IMM_7_MASK	GENMASK(0, 0)
#घोषणा RVC_J_IMM_3_1_MASK	GENMASK(2, 0)
#घोषणा RVC_J_IMM_5_MASK	GENMASK(0, 0)

/* The bit field of immediate value in RVC B inकाष्ठाion */
#घोषणा RVC_B_IMM_SIGN_OPOFF	12
#घोषणा RVC_B_IMM_4_3_OPOFF	10
#घोषणा RVC_B_IMM_7_6_OPOFF	5
#घोषणा RVC_B_IMM_2_1_OPOFF	3
#घोषणा RVC_B_IMM_5_OPOFF	2
#घोषणा RVC_B_IMM_SIGN_OFF	8
#घोषणा RVC_B_IMM_4_3_OFF	3
#घोषणा RVC_B_IMM_7_6_OFF	6
#घोषणा RVC_B_IMM_2_1_OFF	1
#घोषणा RVC_B_IMM_5_OFF		5
#घोषणा RVC_B_IMM_4_3_MASK	GENMASK(1, 0)
#घोषणा RVC_B_IMM_7_6_MASK	GENMASK(1, 0)
#घोषणा RVC_B_IMM_2_1_MASK	GENMASK(1, 0)
#घोषणा RVC_B_IMM_5_MASK	GENMASK(0, 0)

/* The रेजिस्टर offset in RVC op=C0 inकाष्ठाion */
#घोषणा RVC_C0_RS1_OPOFF	7
#घोषणा RVC_C0_RS2_OPOFF	2
#घोषणा RVC_C0_RD_OPOFF		2

/* The रेजिस्टर offset in RVC op=C1 inकाष्ठाion */
#घोषणा RVC_C1_RS1_OPOFF	7
#घोषणा RVC_C1_RS2_OPOFF	2
#घोषणा RVC_C1_RD_OPOFF		7

/* The रेजिस्टर offset in RVC op=C2 inकाष्ठाion */
#घोषणा RVC_C2_RS1_OPOFF	7
#घोषणा RVC_C2_RS2_OPOFF	2
#घोषणा RVC_C2_RD_OPOFF		7

/* parts of opcode क्रम RVG*/
#घोषणा OPCODE_BRANCH		0x63
#घोषणा OPCODE_JALR		0x67
#घोषणा OPCODE_JAL		0x6f
#घोषणा OPCODE_SYSTEM		0x73

/* parts of opcode क्रम RVC*/
#घोषणा OPCODE_C_0		0x0
#घोषणा OPCODE_C_1		0x1
#घोषणा OPCODE_C_2		0x2

/* parts of funct3 code क्रम I, M, A extension*/
#घोषणा FUNCT3_JALR		0x0
#घोषणा FUNCT3_BEQ		0x0
#घोषणा FUNCT3_BNE		0x1000
#घोषणा FUNCT3_BLT		0x4000
#घोषणा FUNCT3_BGE		0x5000
#घोषणा FUNCT3_BLTU		0x6000
#घोषणा FUNCT3_BGEU		0x7000

/* parts of funct3 code क्रम C extension*/
#घोषणा FUNCT3_C_BEQZ		0xc000
#घोषणा FUNCT3_C_BNEZ		0xe000
#घोषणा FUNCT3_C_J		0xa000
#घोषणा FUNCT3_C_JAL		0x2000
#घोषणा FUNCT4_C_JR		0x8000
#घोषणा FUNCT4_C_JALR		0xf000

#घोषणा FUNCT12_SRET		0x10200000

#घोषणा MATCH_JALR		(FUNCT3_JALR | OPCODE_JALR)
#घोषणा MATCH_JAL		(OPCODE_JAL)
#घोषणा MATCH_BEQ		(FUNCT3_BEQ | OPCODE_BRANCH)
#घोषणा MATCH_BNE		(FUNCT3_BNE | OPCODE_BRANCH)
#घोषणा MATCH_BLT		(FUNCT3_BLT | OPCODE_BRANCH)
#घोषणा MATCH_BGE		(FUNCT3_BGE | OPCODE_BRANCH)
#घोषणा MATCH_BLTU		(FUNCT3_BLTU | OPCODE_BRANCH)
#घोषणा MATCH_BGEU		(FUNCT3_BGEU | OPCODE_BRANCH)
#घोषणा MATCH_SRET		(FUNCT12_SRET | OPCODE_SYSTEM)
#घोषणा MATCH_C_BEQZ		(FUNCT3_C_BEQZ | OPCODE_C_1)
#घोषणा MATCH_C_BNEZ		(FUNCT3_C_BNEZ | OPCODE_C_1)
#घोषणा MATCH_C_J		(FUNCT3_C_J | OPCODE_C_1)
#घोषणा MATCH_C_JAL		(FUNCT3_C_JAL | OPCODE_C_1)
#घोषणा MATCH_C_JR		(FUNCT4_C_JR | OPCODE_C_2)
#घोषणा MATCH_C_JALR		(FUNCT4_C_JALR | OPCODE_C_2)

#घोषणा MASK_JALR		0x707f
#घोषणा MASK_JAL		0x7f
#घोषणा MASK_C_JALR		0xf07f
#घोषणा MASK_C_JR		0xf07f
#घोषणा MASK_C_JAL		0xe003
#घोषणा MASK_C_J		0xe003
#घोषणा MASK_BEQ		0x707f
#घोषणा MASK_BNE		0x707f
#घोषणा MASK_BLT		0x707f
#घोषणा MASK_BGE		0x707f
#घोषणा MASK_BLTU		0x707f
#घोषणा MASK_BGEU		0x707f
#घोषणा MASK_C_BEQZ		0xe003
#घोषणा MASK_C_BNEZ		0xe003
#घोषणा MASK_SRET		0xffffffff

#घोषणा __INSN_LENGTH_MASK	_UL(0x3)
#घोषणा __INSN_LENGTH_GE_32	_UL(0x3)
#घोषणा __INSN_OPCODE_MASK	_UL(0x7F)
#घोषणा __INSN_BRANCH_OPCODE	_UL(OPCODE_BRANCH)

/* Define a series of is_XXX_insn functions to check अगर the value INSN
 * is an instance of inकाष्ठाion XXX.
 */
#घोषणा DECLARE_INSN(INSN_NAME, INSN_MATCH, INSN_MASK) \
अटल अंतरभूत bool is_ ## INSN_NAME ## _insn(दीर्घ insn) \
अणु \
	वापस (insn & (INSN_MASK)) == (INSN_MATCH); \
पूर्ण

#घोषणा RV_IMM_SIGN(x) (-(((x) >> 31) & 1))
#घोषणा RVC_IMM_SIGN(x) (-(((x) >> 12) & 1))
#घोषणा RV_X(X, s, mask)  (((X) >> (s)) & (mask))
#घोषणा RVC_X(X, s, mask) RV_X(X, s, mask)

#घोषणा EXTRACT_JTYPE_IMM(x) \
	(अणुtypeof(x) x_ = (x); \
	(RV_X(x_, J_IMM_10_1_OPOFF, J_IMM_10_1_MASK) << J_IMM_10_1_OFF) | \
	(RV_X(x_, J_IMM_11_OPOFF, J_IMM_11_MASK) << J_IMM_11_OFF) | \
	(RV_X(x_, J_IMM_19_12_OPOFF, J_IMM_19_12_MASK) << J_IMM_19_12_OFF) | \
	(RV_IMM_SIGN(x_) << J_IMM_SIGN_OFF); पूर्ण)

#घोषणा EXTRACT_ITYPE_IMM(x) \
	(अणुtypeof(x) x_ = (x); \
	(RV_X(x_, I_IMM_11_0_OPOFF, I_IMM_11_0_MASK)) | \
	(RV_IMM_SIGN(x_) << I_IMM_SIGN_OFF); पूर्ण)

#घोषणा EXTRACT_BTYPE_IMM(x) \
	(अणुtypeof(x) x_ = (x); \
	(RV_X(x_, B_IMM_4_1_OPOFF, B_IMM_4_1_MASK) << B_IMM_4_1_OFF) | \
	(RV_X(x_, B_IMM_10_5_OPOFF, B_IMM_10_5_MASK) << B_IMM_10_5_OFF) | \
	(RV_X(x_, B_IMM_11_OPOFF, B_IMM_11_MASK) << B_IMM_11_OFF) | \
	(RV_IMM_SIGN(x_) << B_IMM_SIGN_OFF); पूर्ण)

#घोषणा EXTRACT_RVC_J_IMM(x) \
	(अणुtypeof(x) x_ = (x); \
	(RVC_X(x_, RVC_J_IMM_3_1_OPOFF, RVC_J_IMM_3_1_MASK) << RVC_J_IMM_3_1_OFF) | \
	(RVC_X(x_, RVC_J_IMM_4_OPOFF, RVC_J_IMM_4_MASK) << RVC_J_IMM_4_OFF) | \
	(RVC_X(x_, RVC_J_IMM_5_OPOFF, RVC_J_IMM_5_MASK) << RVC_J_IMM_5_OFF) | \
	(RVC_X(x_, RVC_J_IMM_6_OPOFF, RVC_J_IMM_6_MASK) << RVC_J_IMM_6_OFF) | \
	(RVC_X(x_, RVC_J_IMM_7_OPOFF, RVC_J_IMM_7_MASK) << RVC_J_IMM_7_OFF) | \
	(RVC_X(x_, RVC_J_IMM_9_8_OPOFF, RVC_J_IMM_9_8_MASK) << RVC_J_IMM_9_8_OFF) | \
	(RVC_X(x_, RVC_J_IMM_10_OPOFF, RVC_J_IMM_10_MASK) << RVC_J_IMM_10_OFF) | \
	(RVC_IMM_SIGN(x_) << RVC_J_IMM_SIGN_OFF); पूर्ण)

#घोषणा EXTRACT_RVC_B_IMM(x) \
	(अणुtypeof(x) x_ = (x); \
	(RVC_X(x_, RVC_B_IMM_2_1_OPOFF, RVC_B_IMM_2_1_MASK) << RVC_B_IMM_2_1_OFF) | \
	(RVC_X(x_, RVC_B_IMM_4_3_OPOFF, RVC_B_IMM_4_3_MASK) << RVC_B_IMM_4_3_OFF) | \
	(RVC_X(x_, RVC_B_IMM_5_OPOFF, RVC_B_IMM_5_MASK) << RVC_B_IMM_5_OFF) | \
	(RVC_X(x_, RVC_B_IMM_7_6_OPOFF, RVC_B_IMM_7_6_MASK) << RVC_B_IMM_7_6_OFF) | \
	(RVC_IMM_SIGN(x_) << RVC_B_IMM_SIGN_OFF); पूर्ण)
