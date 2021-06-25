<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2016-2018 Netronome Systems, Inc. */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "nfp_asm.h"

स्थिर काष्ठा cmd_tgt_act cmd_tgt_act[__CMD_TGT_MAP_SIZE] = अणु
	[CMD_TGT_WRITE8_SWAP] =		अणु 0x02, 0x42 पूर्ण,
	[CMD_TGT_WRITE32_SWAP] =	अणु 0x02, 0x5f पूर्ण,
	[CMD_TGT_READ8] =		अणु 0x01, 0x43 पूर्ण,
	[CMD_TGT_READ32] =		अणु 0x00, 0x5c पूर्ण,
	[CMD_TGT_READ32_LE] =		अणु 0x01, 0x5c पूर्ण,
	[CMD_TGT_READ32_SWAP] =		अणु 0x02, 0x5c पूर्ण,
	[CMD_TGT_READ_LE] =		अणु 0x01, 0x40 पूर्ण,
	[CMD_TGT_READ_SWAP_LE] =	अणु 0x03, 0x40 पूर्ण,
	[CMD_TGT_ADD] =			अणु 0x00, 0x47 पूर्ण,
	[CMD_TGT_ADD_IMM] =		अणु 0x02, 0x47 पूर्ण,
पूर्ण;

अटल bool unreg_is_imm(u16 reg)
अणु
	वापस (reg & UR_REG_IMM) == UR_REG_IMM;
पूर्ण

u16 br_get_offset(u64 instr)
अणु
	u16 addr_lo, addr_hi;

	addr_lo = FIELD_GET(OP_BR_ADDR_LO, instr);
	addr_hi = FIELD_GET(OP_BR_ADDR_HI, instr);

	वापस (addr_hi * ((OP_BR_ADDR_LO >> __bf_shf(OP_BR_ADDR_LO)) + 1)) |
		addr_lo;
पूर्ण

व्योम br_set_offset(u64 *instr, u16 offset)
अणु
	u16 addr_lo, addr_hi;

	addr_lo = offset & (OP_BR_ADDR_LO >> __bf_shf(OP_BR_ADDR_LO));
	addr_hi = offset != addr_lo;
	*instr &= ~(OP_BR_ADDR_HI | OP_BR_ADDR_LO);
	*instr |= FIELD_PREP(OP_BR_ADDR_HI, addr_hi);
	*instr |= FIELD_PREP(OP_BR_ADDR_LO, addr_lo);
पूर्ण

व्योम br_add_offset(u64 *instr, u16 offset)
अणु
	u16 addr;

	addr = br_get_offset(*instr);
	br_set_offset(instr, addr + offset);
पूर्ण

अटल bool immed_can_modअगरy(u64 instr)
अणु
	अगर (FIELD_GET(OP_IMMED_INV, instr) ||
	    FIELD_GET(OP_IMMED_SHIFT, instr) ||
	    FIELD_GET(OP_IMMED_WIDTH, instr) != IMMED_WIDTH_ALL) अणु
		pr_err("Can't decode/encode immed!\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

u16 immed_get_value(u64 instr)
अणु
	u16 reg;

	अगर (!immed_can_modअगरy(instr))
		वापस 0;

	reg = FIELD_GET(OP_IMMED_A_SRC, instr);
	अगर (!unreg_is_imm(reg))
		reg = FIELD_GET(OP_IMMED_B_SRC, instr);

	वापस (reg & 0xff) | FIELD_GET(OP_IMMED_IMM, instr) << 8;
पूर्ण

व्योम immed_set_value(u64 *instr, u16 immed)
अणु
	अगर (!immed_can_modअगरy(*instr))
		वापस;

	अगर (unreg_is_imm(FIELD_GET(OP_IMMED_A_SRC, *instr))) अणु
		*instr &= ~FIELD_PREP(OP_IMMED_A_SRC, 0xff);
		*instr |= FIELD_PREP(OP_IMMED_A_SRC, immed & 0xff);
	पूर्ण अन्यथा अणु
		*instr &= ~FIELD_PREP(OP_IMMED_B_SRC, 0xff);
		*instr |= FIELD_PREP(OP_IMMED_B_SRC, immed & 0xff);
	पूर्ण

	*instr &= ~OP_IMMED_IMM;
	*instr |= FIELD_PREP(OP_IMMED_IMM, immed >> 8);
पूर्ण

व्योम immed_add_value(u64 *instr, u16 offset)
अणु
	u16 val;

	अगर (!immed_can_modअगरy(*instr))
		वापस;

	val = immed_get_value(*instr);
	immed_set_value(instr, val + offset);
पूर्ण

अटल u16 nfp_swreg_to_unreg(swreg reg, bool is_dst)
अणु
	bool lm_id, lm_dec = false;
	u16 val = swreg_value(reg);

	चयन (swreg_type(reg)) अणु
	हाल NN_REG_GPR_A:
	हाल NN_REG_GPR_B:
	हाल NN_REG_GPR_BOTH:
		वापस val;
	हाल NN_REG_NNR:
		वापस UR_REG_NN | val;
	हाल NN_REG_XFER:
		वापस UR_REG_XFR | val;
	हाल NN_REG_LMEM:
		lm_id = swreg_lm_idx(reg);

		चयन (swreg_lm_mode(reg)) अणु
		हाल NN_LM_MOD_NONE:
			अगर (val & ~UR_REG_LM_IDX_MAX) अणु
				pr_err("LM offset too large\n");
				वापस 0;
			पूर्ण
			वापस UR_REG_LM | FIELD_PREP(UR_REG_LM_IDX, lm_id) |
				val;
		हाल NN_LM_MOD_DEC:
			lm_dec = true;
			fallthrough;
		हाल NN_LM_MOD_INC:
			अगर (val) अणु
				pr_err("LM offset in inc/dev mode\n");
				वापस 0;
			पूर्ण
			वापस UR_REG_LM | UR_REG_LM_POST_MOD |
				FIELD_PREP(UR_REG_LM_IDX, lm_id) |
				FIELD_PREP(UR_REG_LM_POST_MOD_DEC, lm_dec);
		शेष:
			pr_err("bad LM mode for unrestricted operands %d\n",
			       swreg_lm_mode(reg));
			वापस 0;
		पूर्ण
	हाल NN_REG_IMM:
		अगर (val & ~0xff) अणु
			pr_err("immediate too large\n");
			वापस 0;
		पूर्ण
		वापस UR_REG_IMM_encode(val);
	हाल NN_REG_NONE:
		वापस is_dst ? UR_REG_NO_DST : REG_NONE;
	पूर्ण

	pr_err("unrecognized reg encoding %08x\n", reg);
	वापस 0;
पूर्ण

पूर्णांक swreg_to_unrestricted(swreg dst, swreg lreg, swreg rreg,
			  काष्ठा nfp_insn_ur_regs *reg)
अणु
	स_रखो(reg, 0, माप(*reg));

	/* Decode destination */
	अगर (swreg_type(dst) == NN_REG_IMM)
		वापस -EFAULT;

	अगर (swreg_type(dst) == NN_REG_GPR_B)
		reg->dst_ab = ALU_DST_B;
	अगर (swreg_type(dst) == NN_REG_GPR_BOTH)
		reg->wr_both = true;
	reg->dst = nfp_swreg_to_unreg(dst, true);

	/* Decode source opeअक्रमs */
	अगर (swreg_type(lreg) == swreg_type(rreg) &&
	    swreg_type(lreg) != NN_REG_NONE)
		वापस -EFAULT;

	अगर (swreg_type(lreg) == NN_REG_GPR_B ||
	    swreg_type(rreg) == NN_REG_GPR_A) अणु
		reg->areg = nfp_swreg_to_unreg(rreg, false);
		reg->breg = nfp_swreg_to_unreg(lreg, false);
		reg->swap = true;
	पूर्ण अन्यथा अणु
		reg->areg = nfp_swreg_to_unreg(lreg, false);
		reg->breg = nfp_swreg_to_unreg(rreg, false);
	पूर्ण

	reg->dst_lmextn = swreg_lmextn(dst);
	reg->src_lmextn = swreg_lmextn(lreg) | swreg_lmextn(rreg);

	वापस 0;
पूर्ण

अटल u16 nfp_swreg_to_rereg(swreg reg, bool is_dst, bool has_imm8, bool *i8)
अणु
	u16 val = swreg_value(reg);
	bool lm_id;

	चयन (swreg_type(reg)) अणु
	हाल NN_REG_GPR_A:
	हाल NN_REG_GPR_B:
	हाल NN_REG_GPR_BOTH:
		वापस val;
	हाल NN_REG_XFER:
		वापस RE_REG_XFR | val;
	हाल NN_REG_LMEM:
		lm_id = swreg_lm_idx(reg);

		अगर (swreg_lm_mode(reg) != NN_LM_MOD_NONE) अणु
			pr_err("bad LM mode for restricted operands %d\n",
			       swreg_lm_mode(reg));
			वापस 0;
		पूर्ण

		अगर (val & ~RE_REG_LM_IDX_MAX) अणु
			pr_err("LM offset too large\n");
			वापस 0;
		पूर्ण

		वापस RE_REG_LM | FIELD_PREP(RE_REG_LM_IDX, lm_id) | val;
	हाल NN_REG_IMM:
		अगर (val & ~(0x7f | has_imm8 << 7)) अणु
			pr_err("immediate too large\n");
			वापस 0;
		पूर्ण
		*i8 = val & 0x80;
		वापस RE_REG_IMM_encode(val & 0x7f);
	हाल NN_REG_NONE:
		वापस is_dst ? RE_REG_NO_DST : REG_NONE;
	हाल NN_REG_NNR:
		pr_err("NNRs used with restricted encoding\n");
		वापस 0;
	पूर्ण

	pr_err("unrecognized reg encoding\n");
	वापस 0;
पूर्ण

पूर्णांक swreg_to_restricted(swreg dst, swreg lreg, swreg rreg,
			काष्ठा nfp_insn_re_regs *reg, bool has_imm8)
अणु
	स_रखो(reg, 0, माप(*reg));

	/* Decode destination */
	अगर (swreg_type(dst) == NN_REG_IMM)
		वापस -EFAULT;

	अगर (swreg_type(dst) == NN_REG_GPR_B)
		reg->dst_ab = ALU_DST_B;
	अगर (swreg_type(dst) == NN_REG_GPR_BOTH)
		reg->wr_both = true;
	reg->dst = nfp_swreg_to_rereg(dst, true, false, शून्य);

	/* Decode source opeअक्रमs */
	अगर (swreg_type(lreg) == swreg_type(rreg) &&
	    swreg_type(lreg) != NN_REG_NONE)
		वापस -EFAULT;

	अगर (swreg_type(lreg) == NN_REG_GPR_B ||
	    swreg_type(rreg) == NN_REG_GPR_A) अणु
		reg->areg = nfp_swreg_to_rereg(rreg, false, has_imm8, &reg->i8);
		reg->breg = nfp_swreg_to_rereg(lreg, false, has_imm8, &reg->i8);
		reg->swap = true;
	पूर्ण अन्यथा अणु
		reg->areg = nfp_swreg_to_rereg(lreg, false, has_imm8, &reg->i8);
		reg->breg = nfp_swreg_to_rereg(rreg, false, has_imm8, &reg->i8);
	पूर्ण

	reg->dst_lmextn = swreg_lmextn(dst);
	reg->src_lmextn = swreg_lmextn(lreg) | swreg_lmextn(rreg);

	वापस 0;
पूर्ण

#घोषणा NFP_USTORE_ECC_POLY_WORDS		7
#घोषणा NFP_USTORE_OP_BITS			45

अटल स्थिर u64 nfp_ustore_ecc_polynomials[NFP_USTORE_ECC_POLY_WORDS] = अणु
	0x0ff800007fffULL,
	0x11f801ff801fULL,
	0x1e387e0781e1ULL,
	0x17cb8e388e22ULL,
	0x1af5b2c93244ULL,
	0x1f56d5525488ULL,
	0x0daf69a46910ULL,
पूर्ण;

अटल bool parity(u64 value)
अणु
	वापस hweight64(value) & 1;
पूर्ण

पूर्णांक nfp_ustore_check_valid_no_ecc(u64 insn)
अणु
	अगर (insn & ~GENMASK_ULL(NFP_USTORE_OP_BITS, 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण

u64 nfp_ustore_calc_ecc_insn(u64 insn)
अणु
	u8 ecc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NFP_USTORE_ECC_POLY_WORDS; i++)
		ecc |= parity(nfp_ustore_ecc_polynomials[i] & insn) << i;

	वापस insn | (u64)ecc << NFP_USTORE_OP_BITS;
पूर्ण
