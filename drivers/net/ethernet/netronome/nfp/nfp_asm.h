<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2016-2018 Netronome Systems, Inc. */

#अगर_अघोषित __NFP_ASM_H__
#घोषणा __NFP_ASM_H__ 1

#समावेश <linux/bitfield.h>
#समावेश <linux/bug.h>
#समावेश <linux/types.h>

#घोषणा REG_NONE	0
#घोषणा REG_WIDTH	4

#घोषणा RE_REG_NO_DST	0x020
#घोषणा RE_REG_IMM	0x020
#घोषणा RE_REG_IMM_encode(x)					\
	(RE_REG_IMM | ((x) & 0x1f) | (((x) & 0x60) << 1))
#घोषणा RE_REG_IMM_MAX	 0x07fULL
#घोषणा RE_REG_LM	0x050
#घोषणा RE_REG_LM_IDX	0x008
#घोषणा RE_REG_LM_IDX_MAX	0x7
#घोषणा RE_REG_XFR	0x080

#घोषणा UR_REG_XFR	0x180
#घोषणा UR_REG_LM	0x200
#घोषणा UR_REG_LM_IDX	0x020
#घोषणा UR_REG_LM_POST_MOD	0x010
#घोषणा UR_REG_LM_POST_MOD_DEC	0x001
#घोषणा UR_REG_LM_IDX_MAX	0xf
#घोषणा UR_REG_NN	0x280
#घोषणा UR_REG_NO_DST	0x300
#घोषणा UR_REG_IMM	UR_REG_NO_DST
#घोषणा UR_REG_IMM_encode(x) (UR_REG_IMM | (x))
#घोषणा UR_REG_IMM_MAX	 0x0ffULL

#घोषणा OP_BR_BASE		0x0d800000020ULL
#घोषणा OP_BR_BASE_MASK		0x0f8000c3ce0ULL
#घोषणा OP_BR_MASK		0x0000000001fULL
#घोषणा OP_BR_EV_PIP		0x00000000300ULL
#घोषणा OP_BR_CSS		0x0000003c000ULL
#घोषणा OP_BR_DEFBR		0x00000300000ULL
#घोषणा OP_BR_ADDR_LO		0x007ffc00000ULL
#घोषणा OP_BR_ADDR_HI		0x10000000000ULL

#घोषणा OP_BR_BIT_BASE		0x0d000000000ULL
#घोषणा OP_BR_BIT_BASE_MASK	0x0f800080300ULL
#घोषणा OP_BR_BIT_A_SRC		0x000000000ffULL
#घोषणा OP_BR_BIT_B_SRC		0x0000003fc00ULL
#घोषणा OP_BR_BIT_BV		0x00000040000ULL
#घोषणा OP_BR_BIT_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_BR_BIT_DEFBR		OP_BR_DEFBR
#घोषणा OP_BR_BIT_ADDR_LO	OP_BR_ADDR_LO
#घोषणा OP_BR_BIT_ADDR_HI	OP_BR_ADDR_HI

#घोषणा OP_BR_ALU_BASE		0x0e800000000ULL
#घोषणा OP_BR_ALU_BASE_MASK	0x0ff80000000ULL
#घोषणा OP_BR_ALU_A_SRC		0x000000003ffULL
#घोषणा OP_BR_ALU_B_SRC		0x000000ffc00ULL
#घोषणा OP_BR_ALU_DEFBR		0x00000300000ULL
#घोषणा OP_BR_ALU_IMM_HI	0x0007fc00000ULL
#घोषणा OP_BR_ALU_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_BR_ALU_DST_LMEXTN	0x80000000000ULL

अटल अंतरभूत bool nfp_is_br(u64 insn)
अणु
	वापस (insn & OP_BR_BASE_MASK) == OP_BR_BASE ||
	       (insn & OP_BR_BIT_BASE_MASK) == OP_BR_BIT_BASE;
पूर्ण

क्रमागत br_mask अणु
	BR_BEQ = 0x00,
	BR_BNE = 0x01,
	BR_BMI = 0x02,
	BR_BHS = 0x04,
	BR_BCC = 0x05,
	BR_BLO = 0x05,
	BR_BGE = 0x08,
	BR_BLT = 0x09,
	BR_UNC = 0x18,
पूर्ण;

क्रमागत br_ev_pip अणु
	BR_EV_PIP_UNCOND = 0,
	BR_EV_PIP_COND = 1,
पूर्ण;

क्रमागत br_ctx_संकेत_state अणु
	BR_CSS_NONE = 2,
पूर्ण;

u16 br_get_offset(u64 instr);
व्योम br_set_offset(u64 *instr, u16 offset);
व्योम br_add_offset(u64 *instr, u16 offset);

#घोषणा OP_BBYTE_BASE		0x0c800000000ULL
#घोषणा OP_BB_A_SRC		0x000000000ffULL
#घोषणा OP_BB_BYTE		0x00000000300ULL
#घोषणा OP_BB_B_SRC		0x0000003fc00ULL
#घोषणा OP_BB_I8		0x00000040000ULL
#घोषणा OP_BB_EQ		0x00000080000ULL
#घोषणा OP_BB_DEFBR		0x00000300000ULL
#घोषणा OP_BB_ADDR_LO		0x007ffc00000ULL
#घोषणा OP_BB_ADDR_HI		0x10000000000ULL
#घोषणा OP_BB_SRC_LMEXTN	0x40000000000ULL

#घोषणा OP_BALU_BASE		0x0e800000000ULL
#घोषणा OP_BA_A_SRC		0x000000003ffULL
#घोषणा OP_BA_B_SRC		0x000000ffc00ULL
#घोषणा OP_BA_DEFBR		0x00000300000ULL
#घोषणा OP_BA_ADDR_HI		0x0007fc00000ULL

#घोषणा OP_IMMED_A_SRC		0x000000003ffULL
#घोषणा OP_IMMED_B_SRC		0x000000ffc00ULL
#घोषणा OP_IMMED_IMM		0x0000ff00000ULL
#घोषणा OP_IMMED_WIDTH		0x00060000000ULL
#घोषणा OP_IMMED_INV		0x00080000000ULL
#घोषणा OP_IMMED_SHIFT		0x00600000000ULL
#घोषणा OP_IMMED_BASE		0x0f000000000ULL
#घोषणा OP_IMMED_WR_AB		0x20000000000ULL
#घोषणा OP_IMMED_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_IMMED_DST_LMEXTN	0x80000000000ULL

क्रमागत immed_width अणु
	IMMED_WIDTH_ALL = 0,
	IMMED_WIDTH_BYTE = 1,
	IMMED_WIDTH_WORD = 2,
पूर्ण;

क्रमागत immed_shअगरt अणु
	IMMED_SHIFT_0B = 0,
	IMMED_SHIFT_1B = 1,
	IMMED_SHIFT_2B = 2,
पूर्ण;

u16 immed_get_value(u64 instr);
व्योम immed_set_value(u64 *instr, u16 immed);
व्योम immed_add_value(u64 *instr, u16 offset);

#घोषणा OP_SHF_BASE		0x08000000000ULL
#घोषणा OP_SHF_A_SRC		0x000000000ffULL
#घोषणा OP_SHF_SC		0x00000000300ULL
#घोषणा OP_SHF_B_SRC		0x0000003fc00ULL
#घोषणा OP_SHF_I8		0x00000040000ULL
#घोषणा OP_SHF_SW		0x00000080000ULL
#घोषणा OP_SHF_DST		0x0000ff00000ULL
#घोषणा OP_SHF_SHIFT		0x001f0000000ULL
#घोषणा OP_SHF_OP		0x00e00000000ULL
#घोषणा OP_SHF_DST_AB		0x01000000000ULL
#घोषणा OP_SHF_WR_AB		0x20000000000ULL
#घोषणा OP_SHF_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_SHF_DST_LMEXTN	0x80000000000ULL

क्रमागत shf_op अणु
	SHF_OP_NONE = 0,
	SHF_OP_AND = 2,
	SHF_OP_OR = 5,
	SHF_OP_ASHR = 6,
पूर्ण;

क्रमागत shf_sc अणु
	SHF_SC_R_ROT = 0,
	SHF_SC_NONE = SHF_SC_R_ROT,
	SHF_SC_R_SHF = 1,
	SHF_SC_L_SHF = 2,
	SHF_SC_R_DSHF = 3,
पूर्ण;

#घोषणा OP_ALU_A_SRC		0x000000003ffULL
#घोषणा OP_ALU_B_SRC		0x000000ffc00ULL
#घोषणा OP_ALU_DST		0x0003ff00000ULL
#घोषणा OP_ALU_SW		0x00040000000ULL
#घोषणा OP_ALU_OP		0x00f80000000ULL
#घोषणा OP_ALU_DST_AB		0x01000000000ULL
#घोषणा OP_ALU_BASE		0x0a000000000ULL
#घोषणा OP_ALU_WR_AB		0x20000000000ULL
#घोषणा OP_ALU_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_ALU_DST_LMEXTN	0x80000000000ULL

क्रमागत alu_op अणु
	ALU_OP_NONE		= 0x00,
	ALU_OP_ADD		= 0x01,
	ALU_OP_NOT		= 0x04,
	ALU_OP_ADD_2B		= 0x05,
	ALU_OP_AND		= 0x08,
	ALU_OP_AND_NOT_A	= 0x0c,
	ALU_OP_SUB_C		= 0x0d,
	ALU_OP_AND_NOT_B	= 0x10,
	ALU_OP_ADD_C		= 0x11,
	ALU_OP_OR		= 0x14,
	ALU_OP_SUB		= 0x15,
	ALU_OP_XOR		= 0x18,
पूर्ण;

क्रमागत alu_dst_ab अणु
	ALU_DST_A = 0,
	ALU_DST_B = 1,
पूर्ण;

#घोषणा OP_LDF_BASE		0x0c000000000ULL
#घोषणा OP_LDF_A_SRC		0x000000000ffULL
#घोषणा OP_LDF_SC		0x00000000300ULL
#घोषणा OP_LDF_B_SRC		0x0000003fc00ULL
#घोषणा OP_LDF_I8		0x00000040000ULL
#घोषणा OP_LDF_SW		0x00000080000ULL
#घोषणा OP_LDF_ZF		0x00000100000ULL
#घोषणा OP_LDF_BMASK		0x0000f000000ULL
#घोषणा OP_LDF_SHF		0x001f0000000ULL
#घोषणा OP_LDF_WR_AB		0x20000000000ULL
#घोषणा OP_LDF_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_LDF_DST_LMEXTN	0x80000000000ULL

#घोषणा OP_CMD_A_SRC		0x000000000ffULL
#घोषणा OP_CMD_CTX		0x00000000300ULL
#घोषणा OP_CMD_B_SRC		0x0000003fc00ULL
#घोषणा OP_CMD_TOKEN		0x000000c0000ULL
#घोषणा OP_CMD_XFER		0x00001f00000ULL
#घोषणा OP_CMD_CNT		0x0000e000000ULL
#घोषणा OP_CMD_SIG		0x000f0000000ULL
#घोषणा OP_CMD_TGT_CMD		0x07f00000000ULL
#घोषणा OP_CMD_INसूची		0x20000000000ULL
#घोषणा OP_CMD_MODE	       0x1c0000000000ULL

काष्ठा cmd_tgt_act अणु
	u8 token;
	u8 tgt_cmd;
पूर्ण;

क्रमागत cmd_tgt_map अणु
	CMD_TGT_READ8,
	CMD_TGT_WRITE8_SWAP,
	CMD_TGT_WRITE32_SWAP,
	CMD_TGT_READ32,
	CMD_TGT_READ32_LE,
	CMD_TGT_READ32_SWAP,
	CMD_TGT_READ_LE,
	CMD_TGT_READ_SWAP_LE,
	CMD_TGT_ADD,
	CMD_TGT_ADD_IMM,
	__CMD_TGT_MAP_SIZE,
पूर्ण;

बाह्य स्थिर काष्ठा cmd_tgt_act cmd_tgt_act[__CMD_TGT_MAP_SIZE];

क्रमागत cmd_mode अणु
	CMD_MODE_40b_AB	= 0,
	CMD_MODE_40b_BA	= 1,
	CMD_MODE_32b	= 4,
पूर्ण;

क्रमागत cmd_ctx_swap अणु
	CMD_CTX_SWAP = 0,
	CMD_CTX_SWAP_DEFER1 = 1,
	CMD_CTX_SWAP_DEFER2 = 2,
	CMD_CTX_NO_SWAP = 3,
पूर्ण;

#घोषणा CMD_OVE_DATA	GENMASK(5, 3)
#घोषणा CMD_OVE_LEN	BIT(7)
#घोषणा CMD_OV_LEN	GENMASK(12, 8)

#घोषणा OP_LCSR_BASE		0x0fc00000000ULL
#घोषणा OP_LCSR_A_SRC		0x000000003ffULL
#घोषणा OP_LCSR_B_SRC		0x000000ffc00ULL
#घोषणा OP_LCSR_WRITE		0x00000200000ULL
#घोषणा OP_LCSR_ADDR		0x001ffc00000ULL
#घोषणा OP_LCSR_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_LCSR_DST_LMEXTN	0x80000000000ULL

क्रमागत lcsr_wr_src अणु
	LCSR_WR_AREG,
	LCSR_WR_BREG,
	LCSR_WR_IMM,
पूर्ण;

#घोषणा OP_CARB_BASE		0x0e000000000ULL
#घोषणा OP_CARB_OR		0x00000010000ULL

#घोषणा NFP_CSR_CTX_PTR		0x20
#घोषणा NFP_CSR_ACT_LM_ADDR0	0x64
#घोषणा NFP_CSR_ACT_LM_ADDR1	0x6c
#घोषणा NFP_CSR_ACT_LM_ADDR2	0x94
#घोषणा NFP_CSR_ACT_LM_ADDR3	0x9c
#घोषणा NFP_CSR_PSEUDO_RND_NUM	0x148

/* Software रेजिस्टर representation, independent of opeअक्रम type */
#घोषणा NN_REG_TYPE	GENMASK(31, 24)
#घोषणा NN_REG_LM_IDX	GENMASK(23, 22)
#घोषणा NN_REG_LM_IDX_HI	BIT(23)
#घोषणा NN_REG_LM_IDX_LO	BIT(22)
#घोषणा NN_REG_LM_MOD	GENMASK(21, 20)
#घोषणा NN_REG_VAL	GENMASK(7, 0)

क्रमागत nfp_bpf_reg_type अणु
	NN_REG_GPR_A =	BIT(0),
	NN_REG_GPR_B =	BIT(1),
	NN_REG_GPR_BOTH = NN_REG_GPR_A | NN_REG_GPR_B,
	NN_REG_NNR =	BIT(2),
	NN_REG_XFER =	BIT(3),
	NN_REG_IMM =	BIT(4),
	NN_REG_NONE =	BIT(5),
	NN_REG_LMEM =	BIT(6),
पूर्ण;

क्रमागत nfp_bpf_lm_mode अणु
	NN_LM_MOD_NONE = 0,
	NN_LM_MOD_INC,
	NN_LM_MOD_DEC,
पूर्ण;

#घोषणा reg_both(x)	__enc_swreg((x), NN_REG_GPR_BOTH)
#घोषणा reg_a(x)	__enc_swreg((x), NN_REG_GPR_A)
#घोषणा reg_b(x)	__enc_swreg((x), NN_REG_GPR_B)
#घोषणा reg_nnr(x)	__enc_swreg((x), NN_REG_NNR)
#घोषणा reg_xfer(x)	__enc_swreg((x), NN_REG_XFER)
#घोषणा reg_imm(x)	__enc_swreg((x), NN_REG_IMM)
#घोषणा reg_none()	__enc_swreg(0, NN_REG_NONE)
#घोषणा reg_lm(x, off)	__enc_swreg_lm((x), NN_LM_MOD_NONE, (off))
#घोषणा reg_lm_inc(x)	__enc_swreg_lm((x), NN_LM_MOD_INC, 0)
#घोषणा reg_lm_dec(x)	__enc_swreg_lm((x), NN_LM_MOD_DEC, 0)
#घोषणा __reg_lm(x, mod, off)	__enc_swreg_lm((x), (mod), (off))

प्रकार __u32 __bitwise swreg;

अटल अंतरभूत swreg __enc_swreg(u16 id, u8 type)
अणु
	वापस (__क्रमce swreg)(id | FIELD_PREP(NN_REG_TYPE, type));
पूर्ण

अटल अंतरभूत swreg __enc_swreg_lm(u8 id, क्रमागत nfp_bpf_lm_mode mode, u8 off)
अणु
	WARN_ON(id > 3 || (off && mode != NN_LM_MOD_NONE));

	वापस (__क्रमce swreg)(FIELD_PREP(NN_REG_TYPE, NN_REG_LMEM) |
			       FIELD_PREP(NN_REG_LM_IDX, id) |
			       FIELD_PREP(NN_REG_LM_MOD, mode) |
			       off);
पूर्ण

अटल अंतरभूत u32 swreg_raw(swreg reg)
अणु
	वापस (__क्रमce u32)reg;
पूर्ण

अटल अंतरभूत क्रमागत nfp_bpf_reg_type swreg_type(swreg reg)
अणु
	वापस FIELD_GET(NN_REG_TYPE, swreg_raw(reg));
पूर्ण

अटल अंतरभूत u16 swreg_value(swreg reg)
अणु
	वापस FIELD_GET(NN_REG_VAL, swreg_raw(reg));
पूर्ण

अटल अंतरभूत bool swreg_lm_idx(swreg reg)
अणु
	वापस FIELD_GET(NN_REG_LM_IDX_LO, swreg_raw(reg));
पूर्ण

अटल अंतरभूत bool swreg_lmextn(swreg reg)
अणु
	वापस FIELD_GET(NN_REG_LM_IDX_HI, swreg_raw(reg));
पूर्ण

अटल अंतरभूत क्रमागत nfp_bpf_lm_mode swreg_lm_mode(swreg reg)
अणु
	वापस FIELD_GET(NN_REG_LM_MOD, swreg_raw(reg));
पूर्ण

काष्ठा nfp_insn_ur_regs अणु
	क्रमागत alu_dst_ab dst_ab;
	u16 dst;
	u16 areg, breg;
	bool swap;
	bool wr_both;
	bool dst_lmextn;
	bool src_lmextn;
पूर्ण;

काष्ठा nfp_insn_re_regs अणु
	क्रमागत alu_dst_ab dst_ab;
	u8 dst;
	u8 areg, breg;
	bool swap;
	bool wr_both;
	bool i8;
	bool dst_lmextn;
	bool src_lmextn;
पूर्ण;

पूर्णांक swreg_to_unrestricted(swreg dst, swreg lreg, swreg rreg,
			  काष्ठा nfp_insn_ur_regs *reg);
पूर्णांक swreg_to_restricted(swreg dst, swreg lreg, swreg rreg,
			काष्ठा nfp_insn_re_regs *reg, bool has_imm8);

#घोषणा NFP_USTORE_PREFETCH_WINDOW	8

पूर्णांक nfp_ustore_check_valid_no_ecc(u64 insn);
u64 nfp_ustore_calc_ecc_insn(u64 insn);

#घोषणा NFP_IND_ME_REFL_WR_SIG_INIT	3
#घोषणा NFP_IND_ME_CTX_PTR_BASE_MASK	GENMASK(9, 0)
#घोषणा NFP_IND_NUM_CONTEXTS		8

अटल अंतरभूत u32 nfp_get_ind_csr_ctx_ptr_offs(u32 पढ़ो_offset)
अणु
	वापस (पढ़ो_offset & ~NFP_IND_ME_CTX_PTR_BASE_MASK) | NFP_CSR_CTX_PTR;
पूर्ण

क्रमागत mul_type अणु
	MUL_TYPE_START		= 0x00,
	MUL_TYPE_STEP_24x8	= 0x01,
	MUL_TYPE_STEP_16x16	= 0x02,
	MUL_TYPE_STEP_32x32	= 0x03,
पूर्ण;

क्रमागत mul_step अणु
	MUL_STEP_1		= 0x00,
	MUL_STEP_NONE		= MUL_STEP_1,
	MUL_STEP_2		= 0x01,
	MUL_STEP_3		= 0x02,
	MUL_STEP_4		= 0x03,
	MUL_LAST		= 0x04,
	MUL_LAST_2		= 0x05,
पूर्ण;

#घोषणा OP_MUL_BASE		0x0f800000000ULL
#घोषणा OP_MUL_A_SRC		0x000000003ffULL
#घोषणा OP_MUL_B_SRC		0x000000ffc00ULL
#घोषणा OP_MUL_STEP		0x00000700000ULL
#घोषणा OP_MUL_DST_AB		0x00000800000ULL
#घोषणा OP_MUL_SW		0x00040000000ULL
#घोषणा OP_MUL_TYPE		0x00180000000ULL
#घोषणा OP_MUL_WR_AB		0x20000000000ULL
#घोषणा OP_MUL_SRC_LMEXTN	0x40000000000ULL
#घोषणा OP_MUL_DST_LMEXTN	0x80000000000ULL

#पूर्ण_अगर
