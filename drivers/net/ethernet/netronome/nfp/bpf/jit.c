<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2016-2018 Netronome Systems, Inc. */

#घोषणा pr_fmt(fmt)	"NFP net bpf: " fmt

#समावेश <linux/bug.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/reciprocal_भाग.h>
#समावेश <linux/unistd.h>

#समावेश "main.h"
#समावेश "../nfp_asm.h"
#समावेश "../nfp_net_ctrl.h"

/* --- NFP prog --- */
/* Foreach "multiple" entries macros provide pos and next<n> poपूर्णांकers.
 * It's safe to modअगरy the next poपूर्णांकers (but not pos).
 */
#घोषणा nfp_क्रम_each_insn_walk2(nfp_prog, pos, next)			\
	क्रम (pos = list_first_entry(&(nfp_prog)->insns, typeof(*pos), l), \
	     next = list_next_entry(pos, l);			\
	     &(nfp_prog)->insns != &pos->l &&			\
	     &(nfp_prog)->insns != &next->l;			\
	     pos = nfp_meta_next(pos),				\
	     next = nfp_meta_next(pos))

#घोषणा nfp_क्रम_each_insn_walk3(nfp_prog, pos, next, next2)		\
	क्रम (pos = list_first_entry(&(nfp_prog)->insns, typeof(*pos), l), \
	     next = list_next_entry(pos, l),			\
	     next2 = list_next_entry(next, l);			\
	     &(nfp_prog)->insns != &pos->l &&			\
	     &(nfp_prog)->insns != &next->l &&			\
	     &(nfp_prog)->insns != &next2->l;			\
	     pos = nfp_meta_next(pos),				\
	     next = nfp_meta_next(pos),				\
	     next2 = nfp_meta_next(next))

अटल bool
nfp_meta_has_prev(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस meta->l.prev != &nfp_prog->insns;
पूर्ण

अटल व्योम nfp_prog_push(काष्ठा nfp_prog *nfp_prog, u64 insn)
अणु
	अगर (nfp_prog->__prog_alloc_len / माप(u64) == nfp_prog->prog_len) अणु
		pr_warn("instruction limit reached (%u NFP instructions)\n",
			nfp_prog->prog_len);
		nfp_prog->error = -ENOSPC;
		वापस;
	पूर्ण

	nfp_prog->prog[nfp_prog->prog_len] = insn;
	nfp_prog->prog_len++;
पूर्ण

अटल अचिन्हित पूर्णांक nfp_prog_current_offset(काष्ठा nfp_prog *nfp_prog)
अणु
	वापस nfp_prog->prog_len;
पूर्ण

अटल bool
nfp_prog_confirm_current_offset(काष्ठा nfp_prog *nfp_prog, अचिन्हित पूर्णांक off)
अणु
	/* If there is a recorded error we may have dropped inकाष्ठाions;
	 * that करोesn't have to be due to translator bug, and the translation
	 * will fail anyway, so just वापस OK.
	 */
	अगर (nfp_prog->error)
		वापस true;
	वापस !WARN_ON_ONCE(nfp_prog_current_offset(nfp_prog) != off);
पूर्ण

/* --- Emitters --- */
अटल व्योम
__emit_cmd(काष्ठा nfp_prog *nfp_prog, क्रमागत cmd_tgt_map op,
	   u8 mode, u8 xfer, u8 areg, u8 breg, u8 size, क्रमागत cmd_ctx_swap ctx,
	   bool indir)
अणु
	u64 insn;

	insn =	FIELD_PREP(OP_CMD_A_SRC, areg) |
		FIELD_PREP(OP_CMD_CTX, ctx) |
		FIELD_PREP(OP_CMD_B_SRC, breg) |
		FIELD_PREP(OP_CMD_TOKEN, cmd_tgt_act[op].token) |
		FIELD_PREP(OP_CMD_XFER, xfer) |
		FIELD_PREP(OP_CMD_CNT, size) |
		FIELD_PREP(OP_CMD_SIG, ctx != CMD_CTX_NO_SWAP) |
		FIELD_PREP(OP_CMD_TGT_CMD, cmd_tgt_act[op].tgt_cmd) |
		FIELD_PREP(OP_CMD_INसूची, indir) |
		FIELD_PREP(OP_CMD_MODE, mode);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_cmd_any(काष्ठा nfp_prog *nfp_prog, क्रमागत cmd_tgt_map op, u8 mode, u8 xfer,
	     swreg lreg, swreg rreg, u8 size, क्रमागत cmd_ctx_swap ctx, bool indir)
अणु
	काष्ठा nfp_insn_re_regs reg;
	पूर्णांक err;

	err = swreg_to_restricted(reg_none(), lreg, rreg, &reg, false);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण
	अगर (reg.swap) अणु
		pr_err("cmd can't swap arguments\n");
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण
	अगर (reg.dst_lmextn || reg.src_lmextn) अणु
		pr_err("cmd can't use LMextn\n");
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण

	__emit_cmd(nfp_prog, op, mode, xfer, reg.areg, reg.breg, size, ctx,
		   indir);
पूर्ण

अटल व्योम
emit_cmd(काष्ठा nfp_prog *nfp_prog, क्रमागत cmd_tgt_map op, u8 mode, u8 xfer,
	 swreg lreg, swreg rreg, u8 size, क्रमागत cmd_ctx_swap ctx)
अणु
	emit_cmd_any(nfp_prog, op, mode, xfer, lreg, rreg, size, ctx, false);
पूर्ण

अटल व्योम
emit_cmd_indir(काष्ठा nfp_prog *nfp_prog, क्रमागत cmd_tgt_map op, u8 mode, u8 xfer,
	       swreg lreg, swreg rreg, u8 size, क्रमागत cmd_ctx_swap ctx)
अणु
	emit_cmd_any(nfp_prog, op, mode, xfer, lreg, rreg, size, ctx, true);
पूर्ण

अटल व्योम
__emit_br(काष्ठा nfp_prog *nfp_prog, क्रमागत br_mask mask, क्रमागत br_ev_pip ev_pip,
	  क्रमागत br_ctx_संकेत_state css, u16 addr, u8 defer)
अणु
	u16 addr_lo, addr_hi;
	u64 insn;

	addr_lo = addr & (OP_BR_ADDR_LO >> __bf_shf(OP_BR_ADDR_LO));
	addr_hi = addr != addr_lo;

	insn = OP_BR_BASE |
		FIELD_PREP(OP_BR_MASK, mask) |
		FIELD_PREP(OP_BR_EV_PIP, ev_pip) |
		FIELD_PREP(OP_BR_CSS, css) |
		FIELD_PREP(OP_BR_DEFBR, defer) |
		FIELD_PREP(OP_BR_ADDR_LO, addr_lo) |
		FIELD_PREP(OP_BR_ADDR_HI, addr_hi);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_br_relo(काष्ठा nfp_prog *nfp_prog, क्रमागत br_mask mask, u16 addr, u8 defer,
	     क्रमागत nfp_relo_type relo)
अणु
	अगर (mask == BR_UNC && defer > 2) अणु
		pr_err("BUG: branch defer out of bounds %d\n", defer);
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण

	__emit_br(nfp_prog, mask,
		  mask != BR_UNC ? BR_EV_PIP_COND : BR_EV_PIP_UNCOND,
		  BR_CSS_NONE, addr, defer);

	nfp_prog->prog[nfp_prog->prog_len - 1] |=
		FIELD_PREP(OP_RELO_TYPE, relo);
पूर्ण

अटल व्योम
emit_br(काष्ठा nfp_prog *nfp_prog, क्रमागत br_mask mask, u16 addr, u8 defer)
अणु
	emit_br_relo(nfp_prog, mask, addr, defer, RELO_BR_REL);
पूर्ण

अटल व्योम
__emit_br_bit(काष्ठा nfp_prog *nfp_prog, u16 areg, u16 breg, u16 addr, u8 defer,
	      bool set, bool src_lmextn)
अणु
	u16 addr_lo, addr_hi;
	u64 insn;

	addr_lo = addr & (OP_BR_BIT_ADDR_LO >> __bf_shf(OP_BR_BIT_ADDR_LO));
	addr_hi = addr != addr_lo;

	insn = OP_BR_BIT_BASE |
		FIELD_PREP(OP_BR_BIT_A_SRC, areg) |
		FIELD_PREP(OP_BR_BIT_B_SRC, breg) |
		FIELD_PREP(OP_BR_BIT_BV, set) |
		FIELD_PREP(OP_BR_BIT_DEFBR, defer) |
		FIELD_PREP(OP_BR_BIT_ADDR_LO, addr_lo) |
		FIELD_PREP(OP_BR_BIT_ADDR_HI, addr_hi) |
		FIELD_PREP(OP_BR_BIT_SRC_LMEXTN, src_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_br_bit_relo(काष्ठा nfp_prog *nfp_prog, swreg src, u8 bit, u16 addr,
		 u8 defer, bool set, क्रमागत nfp_relo_type relo)
अणु
	काष्ठा nfp_insn_re_regs reg;
	पूर्णांक err;

	/* NOTE: The bit to test is specअगरied as an rotation amount, such that
	 *	 the bit to test will be placed on the MSB of the result when
	 *	 करोing a rotate right. For bit X, we need right rotate X + 1.
	 */
	bit += 1;

	err = swreg_to_restricted(reg_none(), src, reg_imm(bit), &reg, false);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_br_bit(nfp_prog, reg.areg, reg.breg, addr, defer, set,
		      reg.src_lmextn);

	nfp_prog->prog[nfp_prog->prog_len - 1] |=
		FIELD_PREP(OP_RELO_TYPE, relo);
पूर्ण

अटल व्योम
emit_br_bset(काष्ठा nfp_prog *nfp_prog, swreg src, u8 bit, u16 addr, u8 defer)
अणु
	emit_br_bit_relo(nfp_prog, src, bit, addr, defer, true, RELO_BR_REL);
पूर्ण

अटल व्योम
__emit_br_alu(काष्ठा nfp_prog *nfp_prog, u16 areg, u16 breg, u16 imm_hi,
	      u8 defer, bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	insn = OP_BR_ALU_BASE |
		FIELD_PREP(OP_BR_ALU_A_SRC, areg) |
		FIELD_PREP(OP_BR_ALU_B_SRC, breg) |
		FIELD_PREP(OP_BR_ALU_DEFBR, defer) |
		FIELD_PREP(OP_BR_ALU_IMM_HI, imm_hi) |
		FIELD_PREP(OP_BR_ALU_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_BR_ALU_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम emit_rtn(काष्ठा nfp_prog *nfp_prog, swreg base, u8 defer)
अणु
	काष्ठा nfp_insn_ur_regs reg;
	पूर्णांक err;

	err = swreg_to_unrestricted(reg_none(), base, reg_imm(0), &reg);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_br_alu(nfp_prog, reg.areg, reg.breg, 0, defer, reg.dst_lmextn,
		      reg.src_lmextn);
पूर्ण

अटल व्योम
__emit_immed(काष्ठा nfp_prog *nfp_prog, u16 areg, u16 breg, u16 imm_hi,
	     क्रमागत immed_width width, bool invert,
	     क्रमागत immed_shअगरt shअगरt, bool wr_both,
	     bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	insn = OP_IMMED_BASE |
		FIELD_PREP(OP_IMMED_A_SRC, areg) |
		FIELD_PREP(OP_IMMED_B_SRC, breg) |
		FIELD_PREP(OP_IMMED_IMM, imm_hi) |
		FIELD_PREP(OP_IMMED_WIDTH, width) |
		FIELD_PREP(OP_IMMED_INV, invert) |
		FIELD_PREP(OP_IMMED_SHIFT, shअगरt) |
		FIELD_PREP(OP_IMMED_WR_AB, wr_both) |
		FIELD_PREP(OP_IMMED_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_IMMED_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_immed(काष्ठा nfp_prog *nfp_prog, swreg dst, u16 imm,
	   क्रमागत immed_width width, bool invert, क्रमागत immed_shअगरt shअगरt)
अणु
	काष्ठा nfp_insn_ur_regs reg;
	पूर्णांक err;

	अगर (swreg_type(dst) == NN_REG_IMM) अणु
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण

	err = swreg_to_unrestricted(dst, dst, reg_imm(imm & 0xff), &reg);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	/* Use reg.dst when destination is No-Dest. */
	__emit_immed(nfp_prog,
		     swreg_type(dst) == NN_REG_NONE ? reg.dst : reg.areg,
		     reg.breg, imm >> 8, width, invert, shअगरt,
		     reg.wr_both, reg.dst_lmextn, reg.src_lmextn);
पूर्ण

अटल व्योम
__emit_shf(काष्ठा nfp_prog *nfp_prog, u16 dst, क्रमागत alu_dst_ab dst_ab,
	   क्रमागत shf_sc sc, u8 shअगरt,
	   u16 areg, क्रमागत shf_op op, u16 breg, bool i8, bool sw, bool wr_both,
	   bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	अगर (!FIELD_FIT(OP_SHF_SHIFT, shअगरt)) अणु
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण

	/* NFP shअगरt inकाष्ठाion has something special. If shअगरt direction is
	 * left then shअगरt amount of 1 to 31 is specअगरied as 32 minus the amount
	 * to shअगरt.
	 *
	 * But no need to करो this क्रम indirect shअगरt which has shअगरt amount be
	 * 0. Even after we करो this subtraction, shअगरt amount 0 will be turned
	 * पूर्णांकo 32 which will eventually be encoded the same as 0 because only
	 * low 5 bits are encoded, but shअगरt amount be 32 will fail the
	 * FIELD_PREP check करोne later on shअगरt mask (0x1f), due to 32 is out of
	 * mask range.
	 */
	अगर (sc == SHF_SC_L_SHF && shअगरt)
		shअगरt = 32 - shअगरt;

	insn = OP_SHF_BASE |
		FIELD_PREP(OP_SHF_A_SRC, areg) |
		FIELD_PREP(OP_SHF_SC, sc) |
		FIELD_PREP(OP_SHF_B_SRC, breg) |
		FIELD_PREP(OP_SHF_I8, i8) |
		FIELD_PREP(OP_SHF_SW, sw) |
		FIELD_PREP(OP_SHF_DST, dst) |
		FIELD_PREP(OP_SHF_SHIFT, shअगरt) |
		FIELD_PREP(OP_SHF_OP, op) |
		FIELD_PREP(OP_SHF_DST_AB, dst_ab) |
		FIELD_PREP(OP_SHF_WR_AB, wr_both) |
		FIELD_PREP(OP_SHF_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_SHF_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_shf(काष्ठा nfp_prog *nfp_prog, swreg dst,
	 swreg lreg, क्रमागत shf_op op, swreg rreg, क्रमागत shf_sc sc, u8 shअगरt)
अणु
	काष्ठा nfp_insn_re_regs reg;
	पूर्णांक err;

	err = swreg_to_restricted(dst, lreg, rreg, &reg, true);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_shf(nfp_prog, reg.dst, reg.dst_ab, sc, shअगरt,
		   reg.areg, op, reg.breg, reg.i8, reg.swap, reg.wr_both,
		   reg.dst_lmextn, reg.src_lmextn);
पूर्ण

अटल व्योम
emit_shf_indir(काष्ठा nfp_prog *nfp_prog, swreg dst,
	       swreg lreg, क्रमागत shf_op op, swreg rreg, क्रमागत shf_sc sc)
अणु
	अगर (sc == SHF_SC_R_ROT) अणु
		pr_err("indirect shift is not allowed on rotation\n");
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण

	emit_shf(nfp_prog, dst, lreg, op, rreg, sc, 0);
पूर्ण

अटल व्योम
__emit_alu(काष्ठा nfp_prog *nfp_prog, u16 dst, क्रमागत alu_dst_ab dst_ab,
	   u16 areg, क्रमागत alu_op op, u16 breg, bool swap, bool wr_both,
	   bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	insn = OP_ALU_BASE |
		FIELD_PREP(OP_ALU_A_SRC, areg) |
		FIELD_PREP(OP_ALU_B_SRC, breg) |
		FIELD_PREP(OP_ALU_DST, dst) |
		FIELD_PREP(OP_ALU_SW, swap) |
		FIELD_PREP(OP_ALU_OP, op) |
		FIELD_PREP(OP_ALU_DST_AB, dst_ab) |
		FIELD_PREP(OP_ALU_WR_AB, wr_both) |
		FIELD_PREP(OP_ALU_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_ALU_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_alu(काष्ठा nfp_prog *nfp_prog, swreg dst,
	 swreg lreg, क्रमागत alu_op op, swreg rreg)
अणु
	काष्ठा nfp_insn_ur_regs reg;
	पूर्णांक err;

	err = swreg_to_unrestricted(dst, lreg, rreg, &reg);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_alu(nfp_prog, reg.dst, reg.dst_ab,
		   reg.areg, op, reg.breg, reg.swap, reg.wr_both,
		   reg.dst_lmextn, reg.src_lmextn);
पूर्ण

अटल व्योम
__emit_mul(काष्ठा nfp_prog *nfp_prog, क्रमागत alu_dst_ab dst_ab, u16 areg,
	   क्रमागत mul_type type, क्रमागत mul_step step, u16 breg, bool swap,
	   bool wr_both, bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	insn = OP_MUL_BASE |
		FIELD_PREP(OP_MUL_A_SRC, areg) |
		FIELD_PREP(OP_MUL_B_SRC, breg) |
		FIELD_PREP(OP_MUL_STEP, step) |
		FIELD_PREP(OP_MUL_DST_AB, dst_ab) |
		FIELD_PREP(OP_MUL_SW, swap) |
		FIELD_PREP(OP_MUL_TYPE, type) |
		FIELD_PREP(OP_MUL_WR_AB, wr_both) |
		FIELD_PREP(OP_MUL_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_MUL_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_mul(काष्ठा nfp_prog *nfp_prog, swreg lreg, क्रमागत mul_type type,
	 क्रमागत mul_step step, swreg rreg)
अणु
	काष्ठा nfp_insn_ur_regs reg;
	u16 areg;
	पूर्णांक err;

	अगर (type == MUL_TYPE_START && step != MUL_STEP_NONE) अणु
		nfp_prog->error = -EINVAL;
		वापस;
	पूर्ण

	अगर (step == MUL_LAST || step == MUL_LAST_2) अणु
		/* When type is step and step Number is LAST or LAST2, left
		 * source is used as destination.
		 */
		err = swreg_to_unrestricted(lreg, reg_none(), rreg, &reg);
		areg = reg.dst;
	पूर्ण अन्यथा अणु
		err = swreg_to_unrestricted(reg_none(), lreg, rreg, &reg);
		areg = reg.areg;
	पूर्ण

	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_mul(nfp_prog, reg.dst_ab, areg, type, step, reg.breg, reg.swap,
		   reg.wr_both, reg.dst_lmextn, reg.src_lmextn);
पूर्ण

अटल व्योम
__emit_ld_field(काष्ठा nfp_prog *nfp_prog, क्रमागत shf_sc sc,
		u8 areg, u8 bmask, u8 breg, u8 shअगरt, bool imm8,
		bool zero, bool swap, bool wr_both,
		bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	insn = OP_LDF_BASE |
		FIELD_PREP(OP_LDF_A_SRC, areg) |
		FIELD_PREP(OP_LDF_SC, sc) |
		FIELD_PREP(OP_LDF_B_SRC, breg) |
		FIELD_PREP(OP_LDF_I8, imm8) |
		FIELD_PREP(OP_LDF_SW, swap) |
		FIELD_PREP(OP_LDF_ZF, zero) |
		FIELD_PREP(OP_LDF_BMASK, bmask) |
		FIELD_PREP(OP_LDF_SHF, shअगरt) |
		FIELD_PREP(OP_LDF_WR_AB, wr_both) |
		FIELD_PREP(OP_LDF_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_LDF_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम
emit_ld_field_any(काष्ठा nfp_prog *nfp_prog, swreg dst, u8 bmask, swreg src,
		  क्रमागत shf_sc sc, u8 shअगरt, bool zero)
अणु
	काष्ठा nfp_insn_re_regs reg;
	पूर्णांक err;

	/* Note: ld_field is special as it uses one of the src regs as dst */
	err = swreg_to_restricted(dst, dst, src, &reg, true);
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_ld_field(nfp_prog, sc, reg.areg, bmask, reg.breg, shअगरt,
			reg.i8, zero, reg.swap, reg.wr_both,
			reg.dst_lmextn, reg.src_lmextn);
पूर्ण

अटल व्योम
emit_ld_field(काष्ठा nfp_prog *nfp_prog, swreg dst, u8 bmask, swreg src,
	      क्रमागत shf_sc sc, u8 shअगरt)
अणु
	emit_ld_field_any(nfp_prog, dst, bmask, src, sc, shअगरt, false);
पूर्ण

अटल व्योम
__emit_lcsr(काष्ठा nfp_prog *nfp_prog, u16 areg, u16 breg, bool wr, u16 addr,
	    bool dst_lmextn, bool src_lmextn)
अणु
	u64 insn;

	insn = OP_LCSR_BASE |
		FIELD_PREP(OP_LCSR_A_SRC, areg) |
		FIELD_PREP(OP_LCSR_B_SRC, breg) |
		FIELD_PREP(OP_LCSR_WRITE, wr) |
		FIELD_PREP(OP_LCSR_ADDR, addr / 4) |
		FIELD_PREP(OP_LCSR_SRC_LMEXTN, src_lmextn) |
		FIELD_PREP(OP_LCSR_DST_LMEXTN, dst_lmextn);

	nfp_prog_push(nfp_prog, insn);
पूर्ण

अटल व्योम emit_csr_wr(काष्ठा nfp_prog *nfp_prog, swreg src, u16 addr)
अणु
	काष्ठा nfp_insn_ur_regs reg;
	पूर्णांक err;

	/* This inकाष्ठाion takes immeds instead of reg_none() क्रम the ignored
	 * opeअक्रम, but we can't encode 2 immeds in one instr with our normal
	 * swreg infra so अगर param is an immed, we encode as reg_none() and
	 * copy the immed to both opeअक्रमs.
	 */
	अगर (swreg_type(src) == NN_REG_IMM) अणु
		err = swreg_to_unrestricted(reg_none(), src, reg_none(), &reg);
		reg.breg = reg.areg;
	पूर्ण अन्यथा अणु
		err = swreg_to_unrestricted(reg_none(), src, reg_imm(0), &reg);
	पूर्ण
	अगर (err) अणु
		nfp_prog->error = err;
		वापस;
	पूर्ण

	__emit_lcsr(nfp_prog, reg.areg, reg.breg, true, addr,
		    false, reg.src_lmextn);
पूर्ण

/* CSR value is पढ़ो in following immed[gpr, 0] */
अटल व्योम __emit_csr_rd(काष्ठा nfp_prog *nfp_prog, u16 addr)
अणु
	__emit_lcsr(nfp_prog, 0, 0, false, addr, false, false);
पूर्ण

अटल व्योम emit_nop(काष्ठा nfp_prog *nfp_prog)
अणु
	__emit_immed(nfp_prog, UR_REG_IMM, UR_REG_IMM, 0, 0, 0, 0, 0, 0, 0);
पूर्ण

/* --- Wrappers --- */
अटल bool pack_immed(u32 imm, u16 *val, क्रमागत immed_shअगरt *shअगरt)
अणु
	अगर (!(imm & 0xffff0000)) अणु
		*val = imm;
		*shअगरt = IMMED_SHIFT_0B;
	पूर्ण अन्यथा अगर (!(imm & 0xff0000ff)) अणु
		*val = imm >> 8;
		*shअगरt = IMMED_SHIFT_1B;
	पूर्ण अन्यथा अगर (!(imm & 0x0000ffff)) अणु
		*val = imm >> 16;
		*shअगरt = IMMED_SHIFT_2B;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम wrp_immed(काष्ठा nfp_prog *nfp_prog, swreg dst, u32 imm)
अणु
	क्रमागत immed_shअगरt shअगरt;
	u16 val;

	अगर (pack_immed(imm, &val, &shअगरt)) अणु
		emit_immed(nfp_prog, dst, val, IMMED_WIDTH_ALL, false, shअगरt);
	पूर्ण अन्यथा अगर (pack_immed(~imm, &val, &shअगरt)) अणु
		emit_immed(nfp_prog, dst, val, IMMED_WIDTH_ALL, true, shअगरt);
	पूर्ण अन्यथा अणु
		emit_immed(nfp_prog, dst, imm & 0xffff, IMMED_WIDTH_ALL,
			   false, IMMED_SHIFT_0B);
		emit_immed(nfp_prog, dst, imm >> 16, IMMED_WIDTH_WORD,
			   false, IMMED_SHIFT_2B);
	पूर्ण
पूर्ण

अटल व्योम
wrp_zext(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta, u8 dst)
अणु
	अगर (meta->flags & FLAG_INSN_DO_ZEXT)
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
पूर्ण

अटल व्योम
wrp_immed_relo(काष्ठा nfp_prog *nfp_prog, swreg dst, u32 imm,
	       क्रमागत nfp_relo_type relo)
अणु
	अगर (imm > 0xffff) अणु
		pr_err("relocation of a large immediate!\n");
		nfp_prog->error = -EFAULT;
		वापस;
	पूर्ण
	emit_immed(nfp_prog, dst, imm, IMMED_WIDTH_ALL, false, IMMED_SHIFT_0B);

	nfp_prog->prog[nfp_prog->prog_len - 1] |=
		FIELD_PREP(OP_RELO_TYPE, relo);
पूर्ण

/* ur_load_imm_any() - encode immediate or use पंचांगp रेजिस्टर (unrestricted)
 * If the @imm is small enough encode it directly in opeअक्रम and वापस
 * otherwise load @imm to a spare रेजिस्टर and वापस its encoding.
 */
अटल swreg ur_load_imm_any(काष्ठा nfp_prog *nfp_prog, u32 imm, swreg पंचांगp_reg)
अणु
	अगर (FIELD_FIT(UR_REG_IMM_MAX, imm))
		वापस reg_imm(imm);

	wrp_immed(nfp_prog, पंचांगp_reg, imm);
	वापस पंचांगp_reg;
पूर्ण

/* re_load_imm_any() - encode immediate or use पंचांगp रेजिस्टर (restricted)
 * If the @imm is small enough encode it directly in opeअक्रम and वापस
 * otherwise load @imm to a spare रेजिस्टर and वापस its encoding.
 */
अटल swreg re_load_imm_any(काष्ठा nfp_prog *nfp_prog, u32 imm, swreg पंचांगp_reg)
अणु
	अगर (FIELD_FIT(RE_REG_IMM_MAX, imm))
		वापस reg_imm(imm);

	wrp_immed(nfp_prog, पंचांगp_reg, imm);
	वापस पंचांगp_reg;
पूर्ण

अटल व्योम wrp_nops(काष्ठा nfp_prog *nfp_prog, अचिन्हित पूर्णांक count)
अणु
	जबतक (count--)
		emit_nop(nfp_prog);
पूर्ण

अटल व्योम wrp_mov(काष्ठा nfp_prog *nfp_prog, swreg dst, swreg src)
अणु
	emit_alu(nfp_prog, dst, reg_none(), ALU_OP_NONE, src);
पूर्ण

अटल व्योम wrp_reg_mov(काष्ठा nfp_prog *nfp_prog, u16 dst, u16 src)
अणु
	wrp_mov(nfp_prog, reg_both(dst), reg_b(src));
पूर्ण

/* wrp_reg_subpart() - load @field_len bytes from @offset of @src, ग_लिखो the
 * result to @dst from low end.
 */
अटल व्योम
wrp_reg_subpart(काष्ठा nfp_prog *nfp_prog, swreg dst, swreg src, u8 field_len,
		u8 offset)
अणु
	क्रमागत shf_sc sc = offset ? SHF_SC_R_SHF : SHF_SC_NONE;
	u8 mask = (1 << field_len) - 1;

	emit_ld_field_any(nfp_prog, dst, mask, src, sc, offset * 8, true);
पूर्ण

/* wrp_reg_or_subpart() - load @field_len bytes from low end of @src, or the
 * result to @dst from offset, there is no change on the other bits of @dst.
 */
अटल व्योम
wrp_reg_or_subpart(काष्ठा nfp_prog *nfp_prog, swreg dst, swreg src,
		   u8 field_len, u8 offset)
अणु
	क्रमागत shf_sc sc = offset ? SHF_SC_L_SHF : SHF_SC_NONE;
	u8 mask = ((1 << field_len) - 1) << offset;

	emit_ld_field(nfp_prog, dst, mask, src, sc, 32 - offset * 8);
पूर्ण

अटल व्योम
addr40_offset(काष्ठा nfp_prog *nfp_prog, u8 src_gpr, swreg offset,
	      swreg *rega, swreg *regb)
अणु
	अगर (offset == reg_imm(0)) अणु
		*rega = reg_a(src_gpr);
		*regb = reg_b(src_gpr + 1);
		वापस;
	पूर्ण

	emit_alu(nfp_prog, imm_a(nfp_prog), reg_a(src_gpr), ALU_OP_ADD, offset);
	emit_alu(nfp_prog, imm_b(nfp_prog), reg_b(src_gpr + 1), ALU_OP_ADD_C,
		 reg_imm(0));
	*rega = imm_a(nfp_prog);
	*regb = imm_b(nfp_prog);
पूर्ण

/* NFP has Command Push Pull bus which supports bluk memory operations. */
अटल पूर्णांक nfp_cpp_स_नकल(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	bool descending_seq = meta->ldst_gather_len < 0;
	s16 len = असल(meta->ldst_gather_len);
	swreg src_base, off;
	bool src_40bit_addr;
	अचिन्हित पूर्णांक i;
	u8 xfer_num;

	off = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));
	src_40bit_addr = meta->ptr.type == PTR_TO_MAP_VALUE;
	src_base = reg_a(meta->insn.src_reg * 2);
	xfer_num = round_up(len, 4) / 4;

	अगर (src_40bit_addr)
		addr40_offset(nfp_prog, meta->insn.src_reg * 2, off, &src_base,
			      &off);

	/* Setup PREV_ALU fields to override memory पढ़ो length. */
	अगर (len > 32)
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 1));

	/* Memory पढ़ो from source addr पूर्णांकo transfer-in रेजिस्टरs. */
	emit_cmd_any(nfp_prog, CMD_TGT_READ32_SWAP,
		     src_40bit_addr ? CMD_MODE_40b_BA : CMD_MODE_32b, 0,
		     src_base, off, xfer_num - 1, CMD_CTX_SWAP, len > 32);

	/* Move from transfer-in to transfer-out. */
	क्रम (i = 0; i < xfer_num; i++)
		wrp_mov(nfp_prog, reg_xfer(i), reg_xfer(i));

	off = re_load_imm_any(nfp_prog, meta->paired_st->off, imm_b(nfp_prog));

	अगर (len <= 8) अणु
		/* Use single direct_ref ग_लिखो8. */
		emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
			 reg_a(meta->paired_st->dst_reg * 2), off, len - 1,
			 CMD_CTX_SWAP);
	पूर्ण अन्यथा अगर (len <= 32 && IS_ALIGNED(len, 4)) अणु
		/* Use single direct_ref ग_लिखो32. */
		emit_cmd(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			 reg_a(meta->paired_st->dst_reg * 2), off, xfer_num - 1,
			 CMD_CTX_SWAP);
	पूर्ण अन्यथा अगर (len <= 32) अणु
		/* Use single indirect_ref ग_लिखो8. */
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, len - 1));
		emit_cmd_indir(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
			       reg_a(meta->paired_st->dst_reg * 2), off,
			       len - 1, CMD_CTX_SWAP);
	पूर्ण अन्यथा अगर (IS_ALIGNED(len, 4)) अणु
		/* Use single indirect_ref ग_लिखो32. */
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 1));
		emit_cmd_indir(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			       reg_a(meta->paired_st->dst_reg * 2), off,
			       xfer_num - 1, CMD_CTX_SWAP);
	पूर्ण अन्यथा अगर (len <= 40) अणु
		/* Use one direct_ref ग_लिखो32 to ग_लिखो the first 32-bytes, then
		 * another direct_ref ग_लिखो8 to ग_लिखो the reमुख्यing bytes.
		 */
		emit_cmd(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			 reg_a(meta->paired_st->dst_reg * 2), off, 7,
			 CMD_CTX_SWAP);

		off = re_load_imm_any(nfp_prog, meta->paired_st->off + 32,
				      imm_b(nfp_prog));
		emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 8,
			 reg_a(meta->paired_st->dst_reg * 2), off, len - 33,
			 CMD_CTX_SWAP);
	पूर्ण अन्यथा अणु
		/* Use one indirect_ref ग_लिखो32 to ग_लिखो 4-bytes aligned length,
		 * then another direct_ref ग_लिखो8 to ग_लिखो the reमुख्यing bytes.
		 */
		u8 new_off;

		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 2));
		emit_cmd_indir(nfp_prog, CMD_TGT_WRITE32_SWAP, CMD_MODE_32b, 0,
			       reg_a(meta->paired_st->dst_reg * 2), off,
			       xfer_num - 2, CMD_CTX_SWAP);
		new_off = meta->paired_st->off + (xfer_num - 1) * 4;
		off = re_load_imm_any(nfp_prog, new_off, imm_b(nfp_prog));
		emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b,
			 xfer_num - 1, reg_a(meta->paired_st->dst_reg * 2), off,
			 (len & 0x3) - 1, CMD_CTX_SWAP);
	पूर्ण

	/* TODO: The following extra load is to make sure data flow be identical
	 *  beक्रमe and after we करो memory copy optimization.
	 *
	 *  The load destination रेजिस्टर is not guaranteed to be dead, so we
	 *  need to make sure it is loaded with the value the same as beक्रमe
	 *  this transक्रमmation.
	 *
	 *  These extra loads could be हटाओd once we have accurate रेजिस्टर
	 *  usage inक्रमmation.
	 */
	अगर (descending_seq)
		xfer_num = 0;
	अन्यथा अगर (BPF_SIZE(meta->insn.code) != BPF_DW)
		xfer_num = xfer_num - 1;
	अन्यथा
		xfer_num = xfer_num - 2;

	चयन (BPF_SIZE(meta->insn.code)) अणु
	हाल BPF_B:
		wrp_reg_subpart(nfp_prog, reg_both(meta->insn.dst_reg * 2),
				reg_xfer(xfer_num), 1,
				IS_ALIGNED(len, 4) ? 3 : (len & 3) - 1);
		अवरोध;
	हाल BPF_H:
		wrp_reg_subpart(nfp_prog, reg_both(meta->insn.dst_reg * 2),
				reg_xfer(xfer_num), 2, (len & 3) ^ 2);
		अवरोध;
	हाल BPF_W:
		wrp_mov(nfp_prog, reg_both(meta->insn.dst_reg * 2),
			reg_xfer(0));
		अवरोध;
	हाल BPF_DW:
		wrp_mov(nfp_prog, reg_both(meta->insn.dst_reg * 2),
			reg_xfer(xfer_num));
		wrp_mov(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1),
			reg_xfer(xfer_num + 1));
		अवरोध;
	पूर्ण

	अगर (BPF_SIZE(meta->insn.code) != BPF_DW)
		wrp_immed(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
data_ld(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta, swreg offset,
	u8 dst_gpr, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;
	u16 shअगरt, sz;

	/* We load the value from the address indicated in @offset and then
	 * shअगरt out the data we करोn't need.  Note: this is big endian!
	 */
	sz = max(size, 4);
	shअगरt = size < 4 ? 4 - size : 0;

	emit_cmd(nfp_prog, CMD_TGT_READ8, CMD_MODE_32b, 0,
		 pptr_reg(nfp_prog), offset, sz - 1, CMD_CTX_SWAP);

	i = 0;
	अगर (shअगरt)
		emit_shf(nfp_prog, reg_both(dst_gpr), reg_none(), SHF_OP_NONE,
			 reg_xfer(0), SHF_SC_R_SHF, shअगरt * 8);
	अन्यथा
		क्रम (; i * 4 < size; i++)
			wrp_mov(nfp_prog, reg_both(dst_gpr + i), reg_xfer(i));

	अगर (i < 2)
		wrp_zext(nfp_prog, meta, dst_gpr);

	वापस 0;
पूर्ण

अटल पूर्णांक
data_ld_host_order(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		   u8 dst_gpr, swreg lreg, swreg rreg, पूर्णांक size,
		   क्रमागत cmd_mode mode)
अणु
	अचिन्हित पूर्णांक i;
	u8 mask, sz;

	/* We load the value from the address indicated in rreg + lreg and then
	 * mask out the data we करोn't need.  Note: this is little endian!
	 */
	sz = max(size, 4);
	mask = size < 4 ? GENMASK(size - 1, 0) : 0;

	emit_cmd(nfp_prog, CMD_TGT_READ32_SWAP, mode, 0,
		 lreg, rreg, sz / 4 - 1, CMD_CTX_SWAP);

	i = 0;
	अगर (mask)
		emit_ld_field_any(nfp_prog, reg_both(dst_gpr), mask,
				  reg_xfer(0), SHF_SC_NONE, 0, true);
	अन्यथा
		क्रम (; i * 4 < size; i++)
			wrp_mov(nfp_prog, reg_both(dst_gpr + i), reg_xfer(i));

	अगर (i < 2)
		wrp_zext(nfp_prog, meta, dst_gpr);

	वापस 0;
पूर्ण

अटल पूर्णांक
data_ld_host_order_addr32(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
			  u8 src_gpr, swreg offset, u8 dst_gpr, u8 size)
अणु
	वापस data_ld_host_order(nfp_prog, meta, dst_gpr, reg_a(src_gpr),
				  offset, size, CMD_MODE_32b);
पूर्ण

अटल पूर्णांक
data_ld_host_order_addr40(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
			  u8 src_gpr, swreg offset, u8 dst_gpr, u8 size)
अणु
	swreg rega, regb;

	addr40_offset(nfp_prog, src_gpr, offset, &rega, &regb);

	वापस data_ld_host_order(nfp_prog, meta, dst_gpr, rega, regb,
				  size, CMD_MODE_40b_BA);
पूर्ण

अटल पूर्णांक
स्थिरruct_data_ind_ld(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		      u16 offset, u16 src, u8 size)
अणु
	swreg पंचांगp_reg;

	/* Calculate the true offset (src_reg + imm) */
	पंचांगp_reg = ur_load_imm_any(nfp_prog, offset, imm_b(nfp_prog));
	emit_alu(nfp_prog, imm_both(nfp_prog), reg_a(src), ALU_OP_ADD, पंचांगp_reg);

	/* Check packet length (size guaranteed to fit b/c it's u8) */
	emit_alu(nfp_prog, imm_a(nfp_prog),
		 imm_a(nfp_prog), ALU_OP_ADD, reg_imm(size));
	emit_alu(nfp_prog, reg_none(),
		 plen_reg(nfp_prog), ALU_OP_SUB, imm_a(nfp_prog));
	emit_br_relo(nfp_prog, BR_BLO, BR_OFF_RELO, 0, RELO_BR_GO_ABORT);

	/* Load data */
	वापस data_ld(nfp_prog, meta, imm_b(nfp_prog), 0, size);
पूर्ण

अटल पूर्णांक
स्थिरruct_data_ld(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		  u16 offset, u8 size)
अणु
	swreg पंचांगp_reg;

	/* Check packet length */
	पंचांगp_reg = ur_load_imm_any(nfp_prog, offset + size, imm_a(nfp_prog));
	emit_alu(nfp_prog, reg_none(), plen_reg(nfp_prog), ALU_OP_SUB, पंचांगp_reg);
	emit_br_relo(nfp_prog, BR_BLO, BR_OFF_RELO, 0, RELO_BR_GO_ABORT);

	/* Load data */
	पंचांगp_reg = re_load_imm_any(nfp_prog, offset, imm_b(nfp_prog));
	वापस data_ld(nfp_prog, meta, पंचांगp_reg, 0, size);
पूर्ण

अटल पूर्णांक
data_stx_host_order(काष्ठा nfp_prog *nfp_prog, u8 dst_gpr, swreg offset,
		    u8 src_gpr, u8 size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i * 4 < size; i++)
		wrp_mov(nfp_prog, reg_xfer(i), reg_a(src_gpr + i));

	emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
		 reg_a(dst_gpr), offset, size - 1, CMD_CTX_SWAP);

	वापस 0;
पूर्ण

अटल पूर्णांक
data_st_host_order(काष्ठा nfp_prog *nfp_prog, u8 dst_gpr, swreg offset,
		   u64 imm, u8 size)
अणु
	wrp_immed(nfp_prog, reg_xfer(0), imm);
	अगर (size == 8)
		wrp_immed(nfp_prog, reg_xfer(1), imm >> 32);

	emit_cmd(nfp_prog, CMD_TGT_WRITE8_SWAP, CMD_MODE_32b, 0,
		 reg_a(dst_gpr), offset, size - 1, CMD_CTX_SWAP);

	वापस 0;
पूर्ण

प्रकार पूर्णांक
(*lmem_step)(काष्ठा nfp_prog *nfp_prog, u8 gpr, u8 gpr_byte, s32 off,
	     अचिन्हित पूर्णांक size, bool first, bool new_gpr, bool last, bool lm3,
	     bool needs_inc);

अटल पूर्णांक
wrp_lmem_load(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 dst_byte, s32 off,
	      अचिन्हित पूर्णांक size, bool first, bool new_gpr, bool last, bool lm3,
	      bool needs_inc)
अणु
	bool should_inc = needs_inc && new_gpr && !last;
	u32 idx, src_byte;
	क्रमागत shf_sc sc;
	swreg reg;
	पूर्णांक shf;
	u8 mask;

	अगर (WARN_ON_ONCE(dst_byte + size > 4 || off % 4 + size > 4))
		वापस -EOPNOTSUPP;

	idx = off / 4;

	/* Move the entire word */
	अगर (size == 4) अणु
		wrp_mov(nfp_prog, reg_both(dst),
			should_inc ? reg_lm_inc(3) : reg_lm(lm3 ? 3 : 0, idx));
		वापस 0;
	पूर्ण

	अगर (WARN_ON_ONCE(lm3 && idx > RE_REG_LM_IDX_MAX))
		वापस -EOPNOTSUPP;

	src_byte = off % 4;

	mask = (1 << size) - 1;
	mask <<= dst_byte;

	अगर (WARN_ON_ONCE(mask > 0xf))
		वापस -EOPNOTSUPP;

	shf = असल(src_byte - dst_byte) * 8;
	अगर (src_byte == dst_byte) अणु
		sc = SHF_SC_NONE;
	पूर्ण अन्यथा अगर (src_byte < dst_byte) अणु
		shf = 32 - shf;
		sc = SHF_SC_L_SHF;
	पूर्ण अन्यथा अणु
		sc = SHF_SC_R_SHF;
	पूर्ण

	/* ld_field can address fewer indexes, अगर offset too large करो RMW.
	 * Because we RMV twice we waste 2 cycles on unaligned 8 byte ग_लिखोs.
	 */
	अगर (idx <= RE_REG_LM_IDX_MAX) अणु
		reg = reg_lm(lm3 ? 3 : 0, idx);
	पूर्ण अन्यथा अणु
		reg = imm_a(nfp_prog);
		/* If it's not the first part of the load and we start a new GPR
		 * that means we are loading a second part of the LMEM word पूर्णांकo
		 * a new GPR.  IOW we've alपढ़ोy looked that LMEM word and
		 * thereक्रमe it has been loaded पूर्णांकo imm_a().
		 */
		अगर (first || !new_gpr)
			wrp_mov(nfp_prog, reg, reg_lm(0, idx));
	पूर्ण

	emit_ld_field_any(nfp_prog, reg_both(dst), mask, reg, sc, shf, new_gpr);

	अगर (should_inc)
		wrp_mov(nfp_prog, reg_none(), reg_lm_inc(3));

	वापस 0;
पूर्ण

अटल पूर्णांक
wrp_lmem_store(काष्ठा nfp_prog *nfp_prog, u8 src, u8 src_byte, s32 off,
	       अचिन्हित पूर्णांक size, bool first, bool new_gpr, bool last, bool lm3,
	       bool needs_inc)
अणु
	bool should_inc = needs_inc && new_gpr && !last;
	u32 idx, dst_byte;
	क्रमागत shf_sc sc;
	swreg reg;
	पूर्णांक shf;
	u8 mask;

	अगर (WARN_ON_ONCE(src_byte + size > 4 || off % 4 + size > 4))
		वापस -EOPNOTSUPP;

	idx = off / 4;

	/* Move the entire word */
	अगर (size == 4) अणु
		wrp_mov(nfp_prog,
			should_inc ? reg_lm_inc(3) : reg_lm(lm3 ? 3 : 0, idx),
			reg_b(src));
		वापस 0;
	पूर्ण

	अगर (WARN_ON_ONCE(lm3 && idx > RE_REG_LM_IDX_MAX))
		वापस -EOPNOTSUPP;

	dst_byte = off % 4;

	mask = (1 << size) - 1;
	mask <<= dst_byte;

	अगर (WARN_ON_ONCE(mask > 0xf))
		वापस -EOPNOTSUPP;

	shf = असल(src_byte - dst_byte) * 8;
	अगर (src_byte == dst_byte) अणु
		sc = SHF_SC_NONE;
	पूर्ण अन्यथा अगर (src_byte < dst_byte) अणु
		shf = 32 - shf;
		sc = SHF_SC_L_SHF;
	पूर्ण अन्यथा अणु
		sc = SHF_SC_R_SHF;
	पूर्ण

	/* ld_field can address fewer indexes, अगर offset too large करो RMW.
	 * Because we RMV twice we waste 2 cycles on unaligned 8 byte ग_लिखोs.
	 */
	अगर (idx <= RE_REG_LM_IDX_MAX) अणु
		reg = reg_lm(lm3 ? 3 : 0, idx);
	पूर्ण अन्यथा अणु
		reg = imm_a(nfp_prog);
		/* Only first and last LMEM locations are going to need RMW,
		 * the middle location will be overwritten fully.
		 */
		अगर (first || last)
			wrp_mov(nfp_prog, reg, reg_lm(0, idx));
	पूर्ण

	emit_ld_field(nfp_prog, reg, mask, reg_b(src), sc, shf);

	अगर (new_gpr || last) अणु
		अगर (idx > RE_REG_LM_IDX_MAX)
			wrp_mov(nfp_prog, reg_lm(0, idx), reg);
		अगर (should_inc)
			wrp_mov(nfp_prog, reg_none(), reg_lm_inc(3));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mem_op_stack(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	     अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक ptr_off, u8 gpr, u8 ptr_gpr,
	     bool clr_gpr, lmem_step step)
अणु
	s32 off = nfp_prog->stack_frame_depth + meta->insn.off + ptr_off;
	bool first = true, narrow_ld, last;
	bool needs_inc = false;
	swreg stack_off_reg;
	u8 prev_gpr = 255;
	u32 gpr_byte = 0;
	bool lm3 = true;
	पूर्णांक ret;

	अगर (meta->ptr_not_स्थिर ||
	    meta->flags & FLAG_INSN_PTR_CALLER_STACK_FRAME) अणु
		/* Use of the last encountered ptr_off is OK, they all have
		 * the same alignment.  Depend on low bits of value being
		 * discarded when written to LMaddr रेजिस्टर.
		 */
		stack_off_reg = ur_load_imm_any(nfp_prog, meta->insn.off,
						stack_imm(nfp_prog));

		emit_alu(nfp_prog, imm_b(nfp_prog),
			 reg_a(ptr_gpr), ALU_OP_ADD, stack_off_reg);

		needs_inc = true;
	पूर्ण अन्यथा अगर (off + size <= 64) अणु
		/* We can reach bottom 64B with LMaddr0 */
		lm3 = false;
	पूर्ण अन्यथा अगर (round_करोwn(off, 32) == round_करोwn(off + size - 1, 32)) अणु
		/* We have to set up a new poपूर्णांकer.  If we know the offset
		 * and the entire access falls पूर्णांकo a single 32 byte aligned
		 * winकरोw we won't have to increment the LM poपूर्णांकer.
		 * The 32 byte alignment is imporant because offset is ORed in
		 * not added when करोing *l$indexN[off].
		 */
		stack_off_reg = ur_load_imm_any(nfp_prog, round_करोwn(off, 32),
						stack_imm(nfp_prog));
		emit_alu(nfp_prog, imm_b(nfp_prog),
			 stack_reg(nfp_prog), ALU_OP_ADD, stack_off_reg);

		off %= 32;
	पूर्ण अन्यथा अणु
		stack_off_reg = ur_load_imm_any(nfp_prog, round_करोwn(off, 4),
						stack_imm(nfp_prog));

		emit_alu(nfp_prog, imm_b(nfp_prog),
			 stack_reg(nfp_prog), ALU_OP_ADD, stack_off_reg);

		needs_inc = true;
	पूर्ण

	narrow_ld = clr_gpr && size < 8;

	अगर (lm3) अणु
		अचिन्हित पूर्णांक nop_cnt;

		emit_csr_wr(nfp_prog, imm_b(nfp_prog), NFP_CSR_ACT_LM_ADDR3);
		/* For size < 4 one slot will be filled by zeroing of upper,
		 * but be careful, that zeroing could be eliminated by zext
		 * optimization.
		 */
		nop_cnt = narrow_ld && meta->flags & FLAG_INSN_DO_ZEXT ? 2 : 3;
		wrp_nops(nfp_prog, nop_cnt);
	पूर्ण

	अगर (narrow_ld)
		wrp_zext(nfp_prog, meta, gpr);

	जबतक (size) अणु
		u32 slice_end;
		u8 slice_size;

		slice_size = min(size, 4 - gpr_byte);
		slice_end = min(off + slice_size, round_up(off + 1, 4));
		slice_size = slice_end - off;

		last = slice_size == size;

		अगर (needs_inc)
			off %= 4;

		ret = step(nfp_prog, gpr, gpr_byte, off, slice_size,
			   first, gpr != prev_gpr, last, lm3, needs_inc);
		अगर (ret)
			वापस ret;

		prev_gpr = gpr;
		first = false;

		gpr_byte += slice_size;
		अगर (gpr_byte >= 4) अणु
			gpr_byte -= 4;
			gpr++;
		पूर्ण

		size -= slice_size;
		off += slice_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
wrp_alu_imm(काष्ठा nfp_prog *nfp_prog, u8 dst, क्रमागत alu_op alu_op, u32 imm)
अणु
	swreg पंचांगp_reg;

	अगर (alu_op == ALU_OP_AND) अणु
		अगर (!imm)
			wrp_immed(nfp_prog, reg_both(dst), 0);
		अगर (!imm || !~imm)
			वापस;
	पूर्ण
	अगर (alu_op == ALU_OP_OR) अणु
		अगर (!~imm)
			wrp_immed(nfp_prog, reg_both(dst), ~0U);
		अगर (!imm || !~imm)
			वापस;
	पूर्ण
	अगर (alu_op == ALU_OP_XOR) अणु
		अगर (!~imm)
			emit_alu(nfp_prog, reg_both(dst), reg_none(),
				 ALU_OP_NOT, reg_b(dst));
		अगर (!imm || !~imm)
			वापस;
	पूर्ण

	पंचांगp_reg = ur_load_imm_any(nfp_prog, imm, imm_b(nfp_prog));
	emit_alu(nfp_prog, reg_both(dst), reg_a(dst), alu_op, पंचांगp_reg);
पूर्ण

अटल पूर्णांक
wrp_alu64_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	      क्रमागत alu_op alu_op, bool skip)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */

	अगर (skip) अणु
		meta->flags |= FLAG_INSN_SKIP_NOOP;
		वापस 0;
	पूर्ण

	wrp_alu_imm(nfp_prog, insn->dst_reg * 2, alu_op, imm & ~0U);
	wrp_alu_imm(nfp_prog, insn->dst_reg * 2 + 1, alu_op, imm >> 32);

	वापस 0;
पूर्ण

अटल पूर्णांक
wrp_alu64_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	      क्रमागत alu_op alu_op)
अणु
	u8 dst = meta->insn.dst_reg * 2, src = meta->insn.src_reg * 2;

	emit_alu(nfp_prog, reg_both(dst), reg_a(dst), alu_op, reg_b(src));
	emit_alu(nfp_prog, reg_both(dst + 1),
		 reg_a(dst + 1), alu_op, reg_b(src + 1));

	वापस 0;
पूर्ण

अटल पूर्णांक
wrp_alu32_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	      क्रमागत alu_op alu_op)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	wrp_alu_imm(nfp_prog, dst, alu_op, insn->imm);
	wrp_zext(nfp_prog, meta, dst);

	वापस 0;
पूर्ण

अटल पूर्णांक
wrp_alu32_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	      क्रमागत alu_op alu_op)
अणु
	u8 dst = meta->insn.dst_reg * 2, src = meta->insn.src_reg * 2;

	emit_alu(nfp_prog, reg_both(dst), reg_a(dst), alu_op, reg_b(src));
	wrp_zext(nfp_prog, meta, dst);

	वापस 0;
पूर्ण

अटल व्योम
wrp_test_reg_one(काष्ठा nfp_prog *nfp_prog, u8 dst, क्रमागत alu_op alu_op, u8 src,
		 क्रमागत br_mask br_mask, u16 off)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(dst), alu_op, reg_b(src));
	emit_br(nfp_prog, br_mask, off, 0);
पूर्ण

अटल पूर्णांक
wrp_test_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	     क्रमागत alu_op alu_op, क्रमागत br_mask br_mask)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	wrp_test_reg_one(nfp_prog, insn->dst_reg * 2, alu_op,
			 insn->src_reg * 2, br_mask, insn->off);
	अगर (is_mbpf_jmp64(meta))
		wrp_test_reg_one(nfp_prog, insn->dst_reg * 2 + 1, alu_op,
				 insn->src_reg * 2 + 1, br_mask, insn->off);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा jmp_code_map अणु
	क्रमागत br_mask br_mask;
	bool swap;
पूर्ण jmp_code_map[] = अणु
	[BPF_JGT >> 4]	= अणु BR_BLO, true पूर्ण,
	[BPF_JGE >> 4]	= अणु BR_BHS, false पूर्ण,
	[BPF_JLT >> 4]	= अणु BR_BLO, false पूर्ण,
	[BPF_JLE >> 4]	= अणु BR_BHS, true पूर्ण,
	[BPF_JSGT >> 4]	= अणु BR_BLT, true पूर्ण,
	[BPF_JSGE >> 4]	= अणु BR_BGE, false पूर्ण,
	[BPF_JSLT >> 4]	= अणु BR_BLT, false पूर्ण,
	[BPF_JSLE >> 4]	= अणु BR_BGE, true पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा jmp_code_map *nfp_jmp_code_get(काष्ठा nfp_insn_meta *meta)
अणु
	अचिन्हित पूर्णांक op;

	op = BPF_OP(meta->insn.code) >> 4;
	/* br_mask of 0 is BR_BEQ which we करोn't use in jump code table */
	अगर (WARN_ONCE(op >= ARRAY_SIZE(jmp_code_map) ||
		      !jmp_code_map[op].br_mask,
		      "no code found for jump instruction"))
		वापस शून्य;

	वापस &jmp_code_map[op];
पूर्ण

अटल पूर्णांक cmp_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */
	स्थिर काष्ठा jmp_code_map *code;
	क्रमागत alu_op alu_op, carry_op;
	u8 reg = insn->dst_reg * 2;
	swreg पंचांगp_reg;

	code = nfp_jmp_code_get(meta);
	अगर (!code)
		वापस -EINVAL;

	alu_op = meta->jump_neg_op ? ALU_OP_ADD : ALU_OP_SUB;
	carry_op = meta->jump_neg_op ? ALU_OP_ADD_C : ALU_OP_SUB_C;

	पंचांगp_reg = ur_load_imm_any(nfp_prog, imm & ~0U, imm_b(nfp_prog));
	अगर (!code->swap)
		emit_alu(nfp_prog, reg_none(), reg_a(reg), alu_op, पंचांगp_reg);
	अन्यथा
		emit_alu(nfp_prog, reg_none(), पंचांगp_reg, alu_op, reg_a(reg));

	अगर (is_mbpf_jmp64(meta)) अणु
		पंचांगp_reg = ur_load_imm_any(nfp_prog, imm >> 32, imm_b(nfp_prog));
		अगर (!code->swap)
			emit_alu(nfp_prog, reg_none(),
				 reg_a(reg + 1), carry_op, पंचांगp_reg);
		अन्यथा
			emit_alu(nfp_prog, reg_none(),
				 पंचांगp_reg, carry_op, reg_a(reg + 1));
	पूर्ण

	emit_br(nfp_prog, code->br_mask, insn->off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	स्थिर काष्ठा jmp_code_map *code;
	u8 areg, breg;

	code = nfp_jmp_code_get(meta);
	अगर (!code)
		वापस -EINVAL;

	areg = insn->dst_reg * 2;
	breg = insn->src_reg * 2;

	अगर (code->swap) अणु
		areg ^= breg;
		breg ^= areg;
		areg ^= breg;
	पूर्ण

	emit_alu(nfp_prog, reg_none(), reg_a(areg), ALU_OP_SUB, reg_b(breg));
	अगर (is_mbpf_jmp64(meta))
		emit_alu(nfp_prog, reg_none(),
			 reg_a(areg + 1), ALU_OP_SUB_C, reg_b(breg + 1));
	emit_br(nfp_prog, code->br_mask, insn->off, 0);

	वापस 0;
पूर्ण

अटल व्योम wrp_end32(काष्ठा nfp_prog *nfp_prog, swreg reg_in, u8 gpr_out)
अणु
	emit_ld_field(nfp_prog, reg_both(gpr_out), 0xf, reg_in,
		      SHF_SC_R_ROT, 8);
	emit_ld_field(nfp_prog, reg_both(gpr_out), 0x5, reg_a(gpr_out),
		      SHF_SC_R_ROT, 16);
पूर्ण

अटल व्योम
wrp_mul_u32(काष्ठा nfp_prog *nfp_prog, swreg dst_hi, swreg dst_lo, swreg lreg,
	    swreg rreg, bool gen_high_half)
अणु
	emit_mul(nfp_prog, lreg, MUL_TYPE_START, MUL_STEP_NONE, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_1, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_2, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_3, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_32x32, MUL_STEP_4, rreg);
	emit_mul(nfp_prog, dst_lo, MUL_TYPE_STEP_32x32, MUL_LAST, reg_none());
	अगर (gen_high_half)
		emit_mul(nfp_prog, dst_hi, MUL_TYPE_STEP_32x32, MUL_LAST_2,
			 reg_none());
	अन्यथा
		wrp_immed(nfp_prog, dst_hi, 0);
पूर्ण

अटल व्योम
wrp_mul_u16(काष्ठा nfp_prog *nfp_prog, swreg dst_hi, swreg dst_lo, swreg lreg,
	    swreg rreg)
अणु
	emit_mul(nfp_prog, lreg, MUL_TYPE_START, MUL_STEP_NONE, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_16x16, MUL_STEP_1, rreg);
	emit_mul(nfp_prog, lreg, MUL_TYPE_STEP_16x16, MUL_STEP_2, rreg);
	emit_mul(nfp_prog, dst_lo, MUL_TYPE_STEP_16x16, MUL_LAST, reg_none());
पूर्ण

अटल पूर्णांक
wrp_mul(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	bool gen_high_half, bool ropnd_from_reg)
अणु
	swreg multiplier, multiplicand, dst_hi, dst_lo;
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u32 lopnd_max, ropnd_max;
	u8 dst_reg;

	dst_reg = insn->dst_reg;
	multiplicand = reg_a(dst_reg * 2);
	dst_hi = reg_both(dst_reg * 2 + 1);
	dst_lo = reg_both(dst_reg * 2);
	lopnd_max = meta->umax_dst;
	अगर (ropnd_from_reg) अणु
		multiplier = reg_b(insn->src_reg * 2);
		ropnd_max = meta->umax_src;
	पूर्ण अन्यथा अणु
		u32 imm = insn->imm;

		multiplier = ur_load_imm_any(nfp_prog, imm, imm_b(nfp_prog));
		ropnd_max = imm;
	पूर्ण
	अगर (lopnd_max > U16_MAX || ropnd_max > U16_MAX)
		wrp_mul_u32(nfp_prog, dst_hi, dst_lo, multiplicand, multiplier,
			    gen_high_half);
	अन्यथा
		wrp_mul_u16(nfp_prog, dst_hi, dst_lo, multiplicand, multiplier);

	वापस 0;
पूर्ण

अटल पूर्णांक wrp_भाग_imm(काष्ठा nfp_prog *nfp_prog, u8 dst, u64 imm)
अणु
	swreg dst_both = reg_both(dst), dst_a = reg_a(dst), dst_b = reg_a(dst);
	काष्ठा reciprocal_value_adv rvalue;
	u8 pre_shअगरt, exp;
	swreg magic;

	अगर (imm > U32_MAX) अणु
		wrp_immed(nfp_prog, dst_both, 0);
		वापस 0;
	पूर्ण

	/* NOTE: because we are using "reciprocal_value_adv" which करोesn't
	 * support "divisor > (1u << 31)", we need to JIT separate NFP sequence
	 * to handle such हाल which actually equals to the result of अचिन्हित
	 * comparison "dst >= imm" which could be calculated using the following
	 * NFP sequence:
	 *
	 *  alu[--, dst, -, imm]
	 *  immed[imm, 0]
	 *  alu[dst, imm, +carry, 0]
	 *
	 */
	अगर (imm > 1U << 31) अणु
		swreg पंचांगp_b = ur_load_imm_any(nfp_prog, imm, imm_b(nfp_prog));

		emit_alu(nfp_prog, reg_none(), dst_a, ALU_OP_SUB, पंचांगp_b);
		wrp_immed(nfp_prog, imm_a(nfp_prog), 0);
		emit_alu(nfp_prog, dst_both, imm_a(nfp_prog), ALU_OP_ADD_C,
			 reg_imm(0));
		वापस 0;
	पूर्ण

	rvalue = reciprocal_value_adv(imm, 32);
	exp = rvalue.exp;
	अगर (rvalue.is_wide_m && !(imm & 1)) अणु
		pre_shअगरt = fls(imm & -imm) - 1;
		rvalue = reciprocal_value_adv(imm >> pre_shअगरt, 32 - pre_shअगरt);
	पूर्ण अन्यथा अणु
		pre_shअगरt = 0;
	पूर्ण
	magic = ur_load_imm_any(nfp_prog, rvalue.m, imm_b(nfp_prog));
	अगर (imm == 1U << exp) अणु
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE, dst_b,
			 SHF_SC_R_SHF, exp);
	पूर्ण अन्यथा अगर (rvalue.is_wide_m) अणु
		wrp_mul_u32(nfp_prog, imm_both(nfp_prog), reg_none(), dst_a,
			    magic, true);
		emit_alu(nfp_prog, dst_both, dst_a, ALU_OP_SUB,
			 imm_b(nfp_prog));
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE, dst_b,
			 SHF_SC_R_SHF, 1);
		emit_alu(nfp_prog, dst_both, dst_a, ALU_OP_ADD,
			 imm_b(nfp_prog));
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE, dst_b,
			 SHF_SC_R_SHF, rvalue.sh - 1);
	पूर्ण अन्यथा अणु
		अगर (pre_shअगरt)
			emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE,
				 dst_b, SHF_SC_R_SHF, pre_shअगरt);
		wrp_mul_u32(nfp_prog, dst_both, reg_none(), dst_a, magic, true);
		emit_shf(nfp_prog, dst_both, reg_none(), SHF_OP_NONE,
			 dst_b, SHF_SC_R_SHF, rvalue.sh);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adjust_head(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	swreg पंचांगp = imm_a(nfp_prog), पंचांगp_len = imm_b(nfp_prog);
	काष्ठा nfp_bpf_cap_adjust_head *adjust_head;
	u32 ret_einval, end;

	adjust_head = &nfp_prog->bpf->adjust_head;

	/* Optimized version - 5 vs 14 cycles */
	अगर (nfp_prog->adjust_head_location != अच_पूर्णांक_उच्च) अणु
		अगर (WARN_ON_ONCE(nfp_prog->adjust_head_location != meta->n))
			वापस -EINVAL;

		emit_alu(nfp_prog, pptr_reg(nfp_prog),
			 reg_a(2 * 2), ALU_OP_ADD, pptr_reg(nfp_prog));
		emit_alu(nfp_prog, plen_reg(nfp_prog),
			 plen_reg(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));
		emit_alu(nfp_prog, pv_len(nfp_prog),
			 pv_len(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));

		wrp_immed(nfp_prog, reg_both(0), 0);
		wrp_immed(nfp_prog, reg_both(1), 0);

		/* TODO: when adjust head is guaranteed to succeed we can
		 * also eliminate the following अगर (r0 == 0) branch.
		 */

		वापस 0;
	पूर्ण

	ret_einval = nfp_prog_current_offset(nfp_prog) + 14;
	end = ret_einval + 2;

	/* We need to use a temp because offset is just a part of the pkt ptr */
	emit_alu(nfp_prog, पंचांगp,
		 reg_a(2 * 2), ALU_OP_ADD_2B, pptr_reg(nfp_prog));

	/* Validate result will fit within FW datapath स्थिरraपूर्णांकs */
	emit_alu(nfp_prog, reg_none(),
		 पंचांगp, ALU_OP_SUB, reg_imm(adjust_head->off_min));
	emit_br(nfp_prog, BR_BLO, ret_einval, 0);
	emit_alu(nfp_prog, reg_none(),
		 reg_imm(adjust_head->off_max), ALU_OP_SUB, पंचांगp);
	emit_br(nfp_prog, BR_BLO, ret_einval, 0);

	/* Validate the length is at least ETH_HLEN */
	emit_alu(nfp_prog, पंचांगp_len,
		 plen_reg(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));
	emit_alu(nfp_prog, reg_none(),
		 पंचांगp_len, ALU_OP_SUB, reg_imm(ETH_HLEN));
	emit_br(nfp_prog, BR_BMI, ret_einval, 0);

	/* Load the ret code */
	wrp_immed(nfp_prog, reg_both(0), 0);
	wrp_immed(nfp_prog, reg_both(1), 0);

	/* Modअगरy the packet metadata */
	emit_ld_field(nfp_prog, pptr_reg(nfp_prog), 0x3, पंचांगp, SHF_SC_NONE, 0);

	/* Skip over the -EINVAL ret code (defer 2) */
	emit_br(nfp_prog, BR_UNC, end, 2);

	emit_alu(nfp_prog, plen_reg(nfp_prog),
		 plen_reg(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));
	emit_alu(nfp_prog, pv_len(nfp_prog),
		 pv_len(nfp_prog), ALU_OP_SUB, reg_a(2 * 2));

	/* वापस -EINVAL target */
	अगर (!nfp_prog_confirm_current_offset(nfp_prog, ret_einval))
		वापस -EINVAL;

	wrp_immed(nfp_prog, reg_both(0), -22);
	wrp_immed(nfp_prog, reg_both(1), ~0);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, end))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक adjust_tail(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	u32 ret_einval, end;
	swreg plen, delta;

	BUILD_BUG_ON(plen_reg(nfp_prog) != reg_b(STATIC_REG_PKT_LEN));

	plen = imm_a(nfp_prog);
	delta = reg_a(2 * 2);

	ret_einval = nfp_prog_current_offset(nfp_prog) + 9;
	end = nfp_prog_current_offset(nfp_prog) + 11;

	/* Calculate resulting length */
	emit_alu(nfp_prog, plen, plen_reg(nfp_prog), ALU_OP_ADD, delta);
	/* delta == 0 is not allowed by the kernel, add must overflow to make
	 * length smaller.
	 */
	emit_br(nfp_prog, BR_BCC, ret_einval, 0);

	/* अगर (new_len < 14) then -EINVAL */
	emit_alu(nfp_prog, reg_none(), plen, ALU_OP_SUB, reg_imm(ETH_HLEN));
	emit_br(nfp_prog, BR_BMI, ret_einval, 0);

	emit_alu(nfp_prog, plen_reg(nfp_prog),
		 plen_reg(nfp_prog), ALU_OP_ADD, delta);
	emit_alu(nfp_prog, pv_len(nfp_prog),
		 pv_len(nfp_prog), ALU_OP_ADD, delta);

	emit_br(nfp_prog, BR_UNC, end, 2);
	wrp_immed(nfp_prog, reg_both(0), 0);
	wrp_immed(nfp_prog, reg_both(1), 0);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, ret_einval))
		वापस -EINVAL;

	wrp_immed(nfp_prog, reg_both(0), -22);
	wrp_immed(nfp_prog, reg_both(1), ~0);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, end))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
map_call_stack_common(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	bool load_lm_ptr;
	u32 ret_tgt;
	s64 lm_off;

	/* We only have to reload LM0 अगर the key is not at start of stack */
	lm_off = nfp_prog->stack_frame_depth;
	lm_off += meta->arg2.reg.var_off.value + meta->arg2.reg.off;
	load_lm_ptr = meta->arg2.var_off || lm_off;

	/* Set LM0 to start of key */
	अगर (load_lm_ptr)
		emit_csr_wr(nfp_prog, reg_b(2 * 2), NFP_CSR_ACT_LM_ADDR0);
	अगर (meta->func_id == BPF_FUNC_map_update_elem)
		emit_csr_wr(nfp_prog, reg_b(3 * 2), NFP_CSR_ACT_LM_ADDR2);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO + meta->func_id,
		     2, RELO_BR_HELPER);
	ret_tgt = nfp_prog_current_offset(nfp_prog) + 2;

	/* Load map ID पूर्णांकo A0 */
	wrp_mov(nfp_prog, reg_a(0), reg_a(2));

	/* Load the वापस address पूर्णांकo B0 */
	wrp_immed_relo(nfp_prog, reg_b(0), ret_tgt, RELO_IMMED_REL);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, ret_tgt))
		वापस -EINVAL;

	/* Reset the LM0 poपूर्णांकer */
	अगर (!load_lm_ptr)
		वापस 0;

	emit_csr_wr(nfp_prog, stack_reg(nfp_prog), NFP_CSR_ACT_LM_ADDR0);
	wrp_nops(nfp_prog, 3);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_get_pअक्रमom_u32(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	__emit_csr_rd(nfp_prog, NFP_CSR_PSEUDO_RND_NUM);
	/* CSR value is पढ़ो in following immed[gpr, 0] */
	emit_immed(nfp_prog, reg_both(0), 0,
		   IMMED_WIDTH_ALL, false, IMMED_SHIFT_0B);
	emit_immed(nfp_prog, reg_both(1), 0,
		   IMMED_WIDTH_ALL, false, IMMED_SHIFT_0B);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_perf_event_output(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	swreg ptr_type;
	u32 ret_tgt;

	ptr_type = ur_load_imm_any(nfp_prog, meta->arg1.type, imm_a(nfp_prog));

	ret_tgt = nfp_prog_current_offset(nfp_prog) + 3;

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO + meta->func_id,
		     2, RELO_BR_HELPER);

	/* Load ptr type पूर्णांकo A1 */
	wrp_mov(nfp_prog, reg_a(1), ptr_type);

	/* Load the वापस address पूर्णांकo B0 */
	wrp_immed_relo(nfp_prog, reg_b(0), ret_tgt, RELO_IMMED_REL);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, ret_tgt))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_queue_select(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	u32 jmp_tgt;

	jmp_tgt = nfp_prog_current_offset(nfp_prog) + 5;

	/* Make sure the queue id fits पूर्णांकo FW field */
	emit_alu(nfp_prog, reg_none(), reg_a(meta->insn.src_reg * 2),
		 ALU_OP_AND_NOT_B, reg_imm(0xff));
	emit_br(nfp_prog, BR_BEQ, jmp_tgt, 2);

	/* Set the 'queue selected' bit and the queue value */
	emit_shf(nfp_prog, pv_qsel_set(nfp_prog),
		 pv_qsel_set(nfp_prog), SHF_OP_OR, reg_imm(1),
		 SHF_SC_L_SHF, PKT_VEL_QSEL_SET_BIT);
	emit_ld_field(nfp_prog,
		      pv_qsel_val(nfp_prog), 0x1, reg_b(meta->insn.src_reg * 2),
		      SHF_SC_NONE, 0);
	/* Delay slots end here, we will jump over next inकाष्ठाion अगर queue
	 * value fits पूर्णांकo the field.
	 */
	emit_ld_field(nfp_prog,
		      pv_qsel_val(nfp_prog), 0x1, reg_imm(NFP_NET_RXR_MAX),
		      SHF_SC_NONE, 0);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, jmp_tgt))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* --- Callbacks --- */
अटल पूर्णांक mov_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;
	u8 src = insn->src_reg * 2;

	अगर (insn->src_reg == BPF_REG_10) अणु
		swreg stack_depth_reg;

		stack_depth_reg = ur_load_imm_any(nfp_prog,
						  nfp_prog->stack_frame_depth,
						  stack_imm(nfp_prog));
		emit_alu(nfp_prog, reg_both(dst), stack_reg(nfp_prog),
			 ALU_OP_ADD, stack_depth_reg);
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
	पूर्ण अन्यथा अणु
		wrp_reg_mov(nfp_prog, dst, src);
		wrp_reg_mov(nfp_prog, dst + 1, src + 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mov_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	u64 imm = meta->insn.imm; /* sign extend */

	wrp_immed(nfp_prog, reg_both(meta->insn.dst_reg * 2), imm & ~0U);
	wrp_immed(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1), imm >> 32);

	वापस 0;
पूर्ण

अटल पूर्णांक xor_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu64_reg(nfp_prog, meta, ALU_OP_XOR);
पूर्ण

अटल पूर्णांक xor_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu64_imm(nfp_prog, meta, ALU_OP_XOR, !meta->insn.imm);
पूर्ण

अटल पूर्णांक and_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu64_reg(nfp_prog, meta, ALU_OP_AND);
पूर्ण

अटल पूर्णांक and_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu64_imm(nfp_prog, meta, ALU_OP_AND, !~meta->insn.imm);
पूर्ण

अटल पूर्णांक or_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu64_reg(nfp_prog, meta, ALU_OP_OR);
पूर्ण

अटल पूर्णांक or_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu64_imm(nfp_prog, meta, ALU_OP_OR, !meta->insn.imm);
पूर्ण

अटल पूर्णांक add_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2),
		 reg_a(insn->dst_reg * 2), ALU_OP_ADD,
		 reg_b(insn->src_reg * 2));
	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2 + 1),
		 reg_a(insn->dst_reg * 2 + 1), ALU_OP_ADD_C,
		 reg_b(insn->src_reg * 2 + 1));

	वापस 0;
पूर्ण

अटल पूर्णांक add_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */

	wrp_alu_imm(nfp_prog, insn->dst_reg * 2, ALU_OP_ADD, imm & ~0U);
	wrp_alu_imm(nfp_prog, insn->dst_reg * 2 + 1, ALU_OP_ADD_C, imm >> 32);

	वापस 0;
पूर्ण

अटल पूर्णांक sub_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2),
		 reg_a(insn->dst_reg * 2), ALU_OP_SUB,
		 reg_b(insn->src_reg * 2));
	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2 + 1),
		 reg_a(insn->dst_reg * 2 + 1), ALU_OP_SUB_C,
		 reg_b(insn->src_reg * 2 + 1));

	वापस 0;
पूर्ण

अटल पूर्णांक sub_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */

	wrp_alu_imm(nfp_prog, insn->dst_reg * 2, ALU_OP_SUB, imm & ~0U);
	wrp_alu_imm(nfp_prog, insn->dst_reg * 2 + 1, ALU_OP_SUB_C, imm >> 32);

	वापस 0;
पूर्ण

अटल पूर्णांक mul_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_mul(nfp_prog, meta, true, true);
पूर्ण

अटल पूर्णांक mul_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_mul(nfp_prog, meta, true, false);
पूर्ण

अटल पूर्णांक भाग_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	वापस wrp_भाग_imm(nfp_prog, insn->dst_reg * 2, insn->imm);
पूर्ण

अटल पूर्णांक भाग_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	/* NOTE: verअगरier hook has rejected हालs क्रम which verअगरier करोesn't
	 * know whether the source opeअक्रम is स्थिरant or not.
	 */
	वापस wrp_भाग_imm(nfp_prog, meta->insn.dst_reg * 2, meta->umin_src);
पूर्ण

अटल पूर्णांक neg_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2), reg_imm(0),
		 ALU_OP_SUB, reg_b(insn->dst_reg * 2));
	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2 + 1), reg_imm(0),
		 ALU_OP_SUB_C, reg_b(insn->dst_reg * 2 + 1));

	वापस 0;
पूर्ण

/* Pseuकरो code:
 *   अगर shअगरt_amt >= 32
 *     dst_high = dst_low << shअगरt_amt[4:0]
 *     dst_low = 0;
 *   अन्यथा
 *     dst_high = (dst_high, dst_low) >> (32 - shअगरt_amt)
 *     dst_low = dst_low << shअगरt_amt
 *
 * The indirect shअगरt will use the same logic at runसमय.
 */
अटल पूर्णांक __shl_imm64(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 shअगरt_amt)
अणु
	अगर (!shअगरt_amt)
		वापस 0;

	अगर (shअगरt_amt < 32) अणु
		emit_shf(nfp_prog, reg_both(dst + 1), reg_a(dst + 1),
			 SHF_OP_NONE, reg_b(dst), SHF_SC_R_DSHF,
			 32 - shअगरt_amt);
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_L_SHF, shअगरt_amt);
	पूर्ण अन्यथा अगर (shअगरt_amt == 32) अणु
		wrp_reg_mov(nfp_prog, dst + 1, dst);
		wrp_immed(nfp_prog, reg_both(dst), 0);
	पूर्ण अन्यथा अगर (shअगरt_amt > 32) अणु
		emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_L_SHF, shअगरt_amt - 32);
		wrp_immed(nfp_prog, reg_both(dst), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक shl_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	वापस __shl_imm64(nfp_prog, dst, insn->imm);
पूर्ण

अटल व्योम shl_reg64_lt32_high(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, imm_both(nfp_prog), reg_imm(32), ALU_OP_SUB,
		 reg_b(src));
	emit_alu(nfp_prog, reg_none(), imm_a(nfp_prog), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst + 1), reg_a(dst + 1), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_R_DSHF);
पूर्ण

/* NOTE: क्रम indirect left shअगरt, HIGH part should be calculated first. */
अटल व्योम shl_reg64_lt32_low(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_L_SHF);
पूर्ण

अटल व्योम shl_reg64_lt32(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	shl_reg64_lt32_high(nfp_prog, dst, src);
	shl_reg64_lt32_low(nfp_prog, dst, src);
पूर्ण

अटल व्योम shl_reg64_ge32(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_L_SHF);
	wrp_immed(nfp_prog, reg_both(dst), 0);
पूर्ण

अटल पूर्णांक shl_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	अगर (umin == umax)
		वापस __shl_imm64(nfp_prog, dst, umin);

	src = insn->src_reg * 2;
	अगर (umax < 32) अणु
		shl_reg64_lt32(nfp_prog, dst, src);
	पूर्ण अन्यथा अगर (umin >= 32) अणु
		shl_reg64_ge32(nfp_prog, dst, src);
	पूर्ण अन्यथा अणु
		/* Generate dअगरferent inकाष्ठाion sequences depending on runसमय
		 * value of shअगरt amount.
		 */
		u16 label_ge32, label_end;

		label_ge32 = nfp_prog_current_offset(nfp_prog) + 7;
		emit_br_bset(nfp_prog, reg_a(src), 5, label_ge32, 0);

		shl_reg64_lt32_high(nfp_prog, dst, src);
		label_end = nfp_prog_current_offset(nfp_prog) + 6;
		emit_br(nfp_prog, BR_UNC, label_end, 2);
		/* shl_reg64_lt32_low packed in delay slot. */
		shl_reg64_lt32_low(nfp_prog, dst, src);

		अगर (!nfp_prog_confirm_current_offset(nfp_prog, label_ge32))
			वापस -EINVAL;
		shl_reg64_ge32(nfp_prog, dst, src);

		अगर (!nfp_prog_confirm_current_offset(nfp_prog, label_end))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Pseuकरो code:
 *   अगर shअगरt_amt >= 32
 *     dst_high = 0;
 *     dst_low = dst_high >> shअगरt_amt[4:0]
 *   अन्यथा
 *     dst_high = dst_high >> shअगरt_amt
 *     dst_low = (dst_high, dst_low) >> shअगरt_amt
 *
 * The indirect shअगरt will use the same logic at runसमय.
 */
अटल पूर्णांक __shr_imm64(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 shअगरt_amt)
अणु
	अगर (!shअगरt_amt)
		वापस 0;

	अगर (shअगरt_amt < 32) अणु
		emit_shf(nfp_prog, reg_both(dst), reg_a(dst + 1), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_R_DSHF, shअगरt_amt);
		emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_NONE,
			 reg_b(dst + 1), SHF_SC_R_SHF, shअगरt_amt);
	पूर्ण अन्यथा अगर (shअगरt_amt == 32) अणु
		wrp_reg_mov(nfp_prog, dst, dst + 1);
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
	पूर्ण अन्यथा अगर (shअगरt_amt > 32) अणु
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
			 reg_b(dst + 1), SHF_SC_R_SHF, shअगरt_amt - 32);
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक shr_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	वापस __shr_imm64(nfp_prog, dst, insn->imm);
पूर्ण

/* NOTE: क्रम indirect right shअगरt, LOW part should be calculated first. */
अटल व्योम shr_reg64_lt32_high(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_NONE,
		       reg_b(dst + 1), SHF_SC_R_SHF);
पूर्ण

अटल व्योम shr_reg64_lt32_low(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_a(dst + 1), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_R_DSHF);
पूर्ण

अटल व्योम shr_reg64_lt32(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	shr_reg64_lt32_low(nfp_prog, dst, src);
	shr_reg64_lt32_high(nfp_prog, dst, src);
पूर्ण

अटल व्योम shr_reg64_ge32(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
		       reg_b(dst + 1), SHF_SC_R_SHF);
	wrp_immed(nfp_prog, reg_both(dst + 1), 0);
पूर्ण

अटल पूर्णांक shr_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	अगर (umin == umax)
		वापस __shr_imm64(nfp_prog, dst, umin);

	src = insn->src_reg * 2;
	अगर (umax < 32) अणु
		shr_reg64_lt32(nfp_prog, dst, src);
	पूर्ण अन्यथा अगर (umin >= 32) अणु
		shr_reg64_ge32(nfp_prog, dst, src);
	पूर्ण अन्यथा अणु
		/* Generate dअगरferent inकाष्ठाion sequences depending on runसमय
		 * value of shअगरt amount.
		 */
		u16 label_ge32, label_end;

		label_ge32 = nfp_prog_current_offset(nfp_prog) + 6;
		emit_br_bset(nfp_prog, reg_a(src), 5, label_ge32, 0);
		shr_reg64_lt32_low(nfp_prog, dst, src);
		label_end = nfp_prog_current_offset(nfp_prog) + 6;
		emit_br(nfp_prog, BR_UNC, label_end, 2);
		/* shr_reg64_lt32_high packed in delay slot. */
		shr_reg64_lt32_high(nfp_prog, dst, src);

		अगर (!nfp_prog_confirm_current_offset(nfp_prog, label_ge32))
			वापस -EINVAL;
		shr_reg64_ge32(nfp_prog, dst, src);

		अगर (!nfp_prog_confirm_current_offset(nfp_prog, label_end))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Code logic is the same as __shr_imm64 except ashr requires चिन्हितness bit
 * told through PREV_ALU result.
 */
अटल पूर्णांक __ashr_imm64(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 shअगरt_amt)
अणु
	अगर (!shअगरt_amt)
		वापस 0;

	अगर (shअगरt_amt < 32) अणु
		emit_shf(nfp_prog, reg_both(dst), reg_a(dst + 1), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_R_DSHF, shअगरt_amt);
		/* Set चिन्हितness bit. */
		emit_alu(nfp_prog, reg_none(), reg_a(dst + 1), ALU_OP_OR,
			 reg_imm(0));
		emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_ASHR,
			 reg_b(dst + 1), SHF_SC_R_SHF, shअगरt_amt);
	पूर्ण अन्यथा अगर (shअगरt_amt == 32) अणु
		/* NOTE: this also helps setting चिन्हितness bit. */
		wrp_reg_mov(nfp_prog, dst, dst + 1);
		emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_ASHR,
			 reg_b(dst + 1), SHF_SC_R_SHF, 31);
	पूर्ण अन्यथा अगर (shअगरt_amt > 32) अणु
		emit_alu(nfp_prog, reg_none(), reg_a(dst + 1), ALU_OP_OR,
			 reg_imm(0));
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_ASHR,
			 reg_b(dst + 1), SHF_SC_R_SHF, shअगरt_amt - 32);
		emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_ASHR,
			 reg_b(dst + 1), SHF_SC_R_SHF, 31);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ashr_imm64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	वापस __ashr_imm64(nfp_prog, dst, insn->imm);
पूर्ण

अटल व्योम ashr_reg64_lt32_high(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	/* NOTE: the first insn will set both indirect shअगरt amount (source A)
	 * and चिन्हितness bit (MSB of result).
	 */
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_b(dst + 1));
	emit_shf_indir(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_ASHR,
		       reg_b(dst + 1), SHF_SC_R_SHF);
पूर्ण

अटल व्योम ashr_reg64_lt32_low(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	/* NOTE: it is the same as logic shअगरt because we करोn't need to shअगरt in
	 * चिन्हितness bit when the shअगरt amount is less than 32.
	 */
	वापस shr_reg64_lt32_low(nfp_prog, dst, src);
पूर्ण

अटल व्योम ashr_reg64_lt32(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	ashr_reg64_lt32_low(nfp_prog, dst, src);
	ashr_reg64_lt32_high(nfp_prog, dst, src);
पूर्ण

अटल व्योम ashr_reg64_ge32(काष्ठा nfp_prog *nfp_prog, u8 dst, u8 src)
अणु
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_b(dst + 1));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_ASHR,
		       reg_b(dst + 1), SHF_SC_R_SHF);
	emit_shf(nfp_prog, reg_both(dst + 1), reg_none(), SHF_OP_ASHR,
		 reg_b(dst + 1), SHF_SC_R_SHF, 31);
पूर्ण

/* Like ashr_imm64, but need to use indirect shअगरt. */
अटल पूर्णांक ashr_reg64(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	अगर (umin == umax)
		वापस __ashr_imm64(nfp_prog, dst, umin);

	src = insn->src_reg * 2;
	अगर (umax < 32) अणु
		ashr_reg64_lt32(nfp_prog, dst, src);
	पूर्ण अन्यथा अगर (umin >= 32) अणु
		ashr_reg64_ge32(nfp_prog, dst, src);
	पूर्ण अन्यथा अणु
		u16 label_ge32, label_end;

		label_ge32 = nfp_prog_current_offset(nfp_prog) + 6;
		emit_br_bset(nfp_prog, reg_a(src), 5, label_ge32, 0);
		ashr_reg64_lt32_low(nfp_prog, dst, src);
		label_end = nfp_prog_current_offset(nfp_prog) + 6;
		emit_br(nfp_prog, BR_UNC, label_end, 2);
		/* ashr_reg64_lt32_high packed in delay slot. */
		ashr_reg64_lt32_high(nfp_prog, dst, src);

		अगर (!nfp_prog_confirm_current_offset(nfp_prog, label_ge32))
			वापस -EINVAL;
		ashr_reg64_ge32(nfp_prog, dst, src);

		अगर (!nfp_prog_confirm_current_offset(nfp_prog, label_end))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mov_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	wrp_reg_mov(nfp_prog, insn->dst_reg * 2,  insn->src_reg * 2);
	wrp_immed(nfp_prog, reg_both(insn->dst_reg * 2 + 1), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mov_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	wrp_immed(nfp_prog, reg_both(insn->dst_reg * 2), insn->imm);
	wrp_immed(nfp_prog, reg_both(insn->dst_reg * 2 + 1), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xor_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_reg(nfp_prog, meta, ALU_OP_XOR);
पूर्ण

अटल पूर्णांक xor_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_imm(nfp_prog, meta, ALU_OP_XOR);
पूर्ण

अटल पूर्णांक and_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_reg(nfp_prog, meta, ALU_OP_AND);
पूर्ण

अटल पूर्णांक and_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_imm(nfp_prog, meta, ALU_OP_AND);
पूर्ण

अटल पूर्णांक or_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_reg(nfp_prog, meta, ALU_OP_OR);
पूर्ण

अटल पूर्णांक or_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_imm(nfp_prog, meta, ALU_OP_OR);
पूर्ण

अटल पूर्णांक add_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_reg(nfp_prog, meta, ALU_OP_ADD);
पूर्ण

अटल पूर्णांक add_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_imm(nfp_prog, meta, ALU_OP_ADD);
पूर्ण

अटल पूर्णांक sub_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_reg(nfp_prog, meta, ALU_OP_SUB);
पूर्ण

अटल पूर्णांक sub_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_alu32_imm(nfp_prog, meta, ALU_OP_SUB);
पूर्ण

अटल पूर्णांक mul_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_mul(nfp_prog, meta, false, true);
पूर्ण

अटल पूर्णांक mul_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_mul(nfp_prog, meta, false, false);
पूर्ण

अटल पूर्णांक भाग_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस भाग_reg64(nfp_prog, meta);
पूर्ण

अटल पूर्णांक भाग_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस भाग_imm64(nfp_prog, meta);
पूर्ण

अटल पूर्णांक neg_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	u8 dst = meta->insn.dst_reg * 2;

	emit_alu(nfp_prog, reg_both(dst), reg_imm(0), ALU_OP_SUB, reg_b(dst));
	wrp_zext(nfp_prog, meta, dst);

	वापस 0;
पूर्ण

अटल पूर्णांक
__ashr_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta, u8 dst,
	   u8 shअगरt_amt)
अणु
	अगर (shअगरt_amt) अणु
		/* Set चिन्हितness bit (MSB of result). */
		emit_alu(nfp_prog, reg_none(), reg_a(dst), ALU_OP_OR,
			 reg_imm(0));
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_ASHR,
			 reg_b(dst), SHF_SC_R_SHF, shअगरt_amt);
	पूर्ण
	wrp_zext(nfp_prog, meta, dst);

	वापस 0;
पूर्ण

अटल पूर्णांक ashr_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	अगर (umin == umax)
		वापस __ashr_imm(nfp_prog, meta, dst, umin);

	src = insn->src_reg * 2;
	/* NOTE: the first insn will set both indirect shअगरt amount (source A)
	 * and चिन्हितness bit (MSB of result).
	 */
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_b(dst));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_ASHR,
		       reg_b(dst), SHF_SC_R_SHF);
	wrp_zext(nfp_prog, meta, dst);

	वापस 0;
पूर्ण

अटल पूर्णांक ashr_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	वापस __ashr_imm(nfp_prog, meta, dst, insn->imm);
पूर्ण

अटल पूर्णांक
__shr_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta, u8 dst,
	  u8 shअगरt_amt)
अणु
	अगर (shअगरt_amt)
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_R_SHF, shअगरt_amt);
	wrp_zext(nfp_prog, meta, dst);
	वापस 0;
पूर्ण

अटल पूर्णांक shr_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	वापस __shr_imm(nfp_prog, meta, dst, insn->imm);
पूर्ण

अटल पूर्णांक shr_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	अगर (umin == umax)
		वापस __shr_imm(nfp_prog, meta, dst, umin);

	src = insn->src_reg * 2;
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_R_SHF);
	wrp_zext(nfp_prog, meta, dst);
	वापस 0;
पूर्ण

अटल पूर्णांक
__shl_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta, u8 dst,
	  u8 shअगरt_amt)
अणु
	अगर (shअगरt_amt)
		emit_shf(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
			 reg_b(dst), SHF_SC_L_SHF, shअगरt_amt);
	wrp_zext(nfp_prog, meta, dst);
	वापस 0;
पूर्ण

अटल पूर्णांक shl_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	वापस __shl_imm(nfp_prog, meta, dst, insn->imm);
पूर्ण

अटल पूर्णांक shl_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	अगर (umin == umax)
		वापस __shl_imm(nfp_prog, meta, dst, umin);

	src = insn->src_reg * 2;
	shl_reg64_lt32_low(nfp_prog, dst, src);
	wrp_zext(nfp_prog, meta, dst);
	वापस 0;
पूर्ण

अटल पूर्णांक end_reg32(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u8 gpr = insn->dst_reg * 2;

	चयन (insn->imm) अणु
	हाल 16:
		emit_ld_field(nfp_prog, reg_both(gpr), 0x9, reg_b(gpr),
			      SHF_SC_R_ROT, 8);
		emit_ld_field(nfp_prog, reg_both(gpr), 0xe, reg_a(gpr),
			      SHF_SC_R_SHF, 16);

		wrp_immed(nfp_prog, reg_both(gpr + 1), 0);
		अवरोध;
	हाल 32:
		wrp_end32(nfp_prog, reg_a(gpr), gpr);
		wrp_immed(nfp_prog, reg_both(gpr + 1), 0);
		अवरोध;
	हाल 64:
		wrp_mov(nfp_prog, imm_a(nfp_prog), reg_b(gpr + 1));

		wrp_end32(nfp_prog, reg_a(gpr), gpr + 1);
		wrp_end32(nfp_prog, imm_a(nfp_prog), gpr);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imm_ld8_part2(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	काष्ठा nfp_insn_meta *prev = nfp_meta_prev(meta);
	u32 imm_lo, imm_hi;
	u8 dst;

	dst = prev->insn.dst_reg * 2;
	imm_lo = prev->insn.imm;
	imm_hi = meta->insn.imm;

	wrp_immed(nfp_prog, reg_both(dst), imm_lo);

	/* mov is always 1 insn, load imm may be two, so try to use mov */
	अगर (imm_hi == imm_lo)
		wrp_mov(nfp_prog, reg_both(dst + 1), reg_a(dst));
	अन्यथा
		wrp_immed(nfp_prog, reg_both(dst + 1), imm_hi);

	वापस 0;
पूर्ण

अटल पूर्णांक imm_ld8(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	meta->द्विगुन_cb = imm_ld8_part2;
	वापस 0;
पूर्ण

अटल पूर्णांक data_ld1(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस स्थिरruct_data_ld(nfp_prog, meta, meta->insn.imm, 1);
पूर्ण

अटल पूर्णांक data_ld2(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस स्थिरruct_data_ld(nfp_prog, meta, meta->insn.imm, 2);
पूर्ण

अटल पूर्णांक data_ld4(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस स्थिरruct_data_ld(nfp_prog, meta, meta->insn.imm, 4);
पूर्ण

अटल पूर्णांक data_ind_ld1(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस स्थिरruct_data_ind_ld(nfp_prog, meta, meta->insn.imm,
				     meta->insn.src_reg * 2, 1);
पूर्ण

अटल पूर्णांक data_ind_ld2(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस स्थिरruct_data_ind_ld(nfp_prog, meta, meta->insn.imm,
				     meta->insn.src_reg * 2, 2);
पूर्ण

अटल पूर्णांक data_ind_ld4(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस स्थिरruct_data_ind_ld(nfp_prog, meta, meta->insn.imm,
				     meta->insn.src_reg * 2, 4);
पूर्ण

अटल पूर्णांक
mem_ldx_stack(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	      अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक ptr_off)
अणु
	वापस mem_op_stack(nfp_prog, meta, size, ptr_off,
			    meta->insn.dst_reg * 2, meta->insn.src_reg * 2,
			    true, wrp_lmem_load);
पूर्ण

अटल पूर्णांक mem_ldx_skb(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		       u8 size)
अणु
	swreg dst = reg_both(meta->insn.dst_reg * 2);

	चयन (meta->insn.off) अणु
	हाल दुरत्व(काष्ठा __sk_buff, len):
		अगर (size != माप_field(काष्ठा __sk_buff, len))
			वापस -EOPNOTSUPP;
		wrp_mov(nfp_prog, dst, plen_reg(nfp_prog));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, data):
		अगर (size != माप_field(काष्ठा __sk_buff, data))
			वापस -EOPNOTSUPP;
		wrp_mov(nfp_prog, dst, pptr_reg(nfp_prog));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, data_end):
		अगर (size != माप_field(काष्ठा __sk_buff, data_end))
			वापस -EOPNOTSUPP;
		emit_alu(nfp_prog, dst,
			 plen_reg(nfp_prog), ALU_OP_ADD, pptr_reg(nfp_prog));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	wrp_immed(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mem_ldx_xdp(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		       u8 size)
अणु
	swreg dst = reg_both(meta->insn.dst_reg * 2);

	चयन (meta->insn.off) अणु
	हाल दुरत्व(काष्ठा xdp_md, data):
		अगर (size != माप_field(काष्ठा xdp_md, data))
			वापस -EOPNOTSUPP;
		wrp_mov(nfp_prog, dst, pptr_reg(nfp_prog));
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, data_end):
		अगर (size != माप_field(काष्ठा xdp_md, data_end))
			वापस -EOPNOTSUPP;
		emit_alu(nfp_prog, dst,
			 plen_reg(nfp_prog), ALU_OP_ADD, pptr_reg(nfp_prog));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	wrp_immed(nfp_prog, reg_both(meta->insn.dst_reg * 2 + 1), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
mem_ldx_data(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	     अचिन्हित पूर्णांक size)
अणु
	swreg पंचांगp_reg;

	पंचांगp_reg = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	वापस data_ld_host_order_addr32(nfp_prog, meta, meta->insn.src_reg * 2,
					 पंचांगp_reg, meta->insn.dst_reg * 2, size);
पूर्ण

अटल पूर्णांक
mem_ldx_emem(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	     अचिन्हित पूर्णांक size)
अणु
	swreg पंचांगp_reg;

	पंचांगp_reg = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	वापस data_ld_host_order_addr40(nfp_prog, meta, meta->insn.src_reg * 2,
					 पंचांगp_reg, meta->insn.dst_reg * 2, size);
पूर्ण

अटल व्योम
mem_ldx_data_init_pktcache(काष्ठा nfp_prog *nfp_prog,
			   काष्ठा nfp_insn_meta *meta)
अणु
	s16 range_start = meta->pkt_cache.range_start;
	s16 range_end = meta->pkt_cache.range_end;
	swreg src_base, off;
	u8 xfer_num, len;
	bool indir;

	off = re_load_imm_any(nfp_prog, range_start, imm_b(nfp_prog));
	src_base = reg_a(meta->insn.src_reg * 2);
	len = range_end - range_start;
	xfer_num = round_up(len, REG_WIDTH) / REG_WIDTH;

	indir = len > 8 * REG_WIDTH;
	/* Setup PREV_ALU क्रम indirect mode. */
	अगर (indir)
		wrp_immed(nfp_prog, reg_none(),
			  CMD_OVE_LEN | FIELD_PREP(CMD_OV_LEN, xfer_num - 1));

	/* Cache memory पूर्णांकo transfer-in रेजिस्टरs. */
	emit_cmd_any(nfp_prog, CMD_TGT_READ32_SWAP, CMD_MODE_32b, 0, src_base,
		     off, xfer_num - 1, CMD_CTX_SWAP, indir);
पूर्ण

अटल पूर्णांक
mem_ldx_data_from_pktcache_unaligned(काष्ठा nfp_prog *nfp_prog,
				     काष्ठा nfp_insn_meta *meta,
				     अचिन्हित पूर्णांक size)
अणु
	s16 range_start = meta->pkt_cache.range_start;
	s16 insn_off = meta->insn.off - range_start;
	swreg dst_lo, dst_hi, src_lo, src_mid;
	u8 dst_gpr = meta->insn.dst_reg * 2;
	u8 len_lo = size, len_mid = 0;
	u8 idx = insn_off / REG_WIDTH;
	u8 off = insn_off % REG_WIDTH;

	dst_hi = reg_both(dst_gpr + 1);
	dst_lo = reg_both(dst_gpr);
	src_lo = reg_xfer(idx);

	/* The पढ़ो length could involve as many as three रेजिस्टरs. */
	अगर (size > REG_WIDTH - off) अणु
		/* Calculate the part in the second रेजिस्टर. */
		len_lo = REG_WIDTH - off;
		len_mid = size - len_lo;

		/* Calculate the part in the third रेजिस्टर. */
		अगर (size > 2 * REG_WIDTH - off)
			len_mid = REG_WIDTH;
	पूर्ण

	wrp_reg_subpart(nfp_prog, dst_lo, src_lo, len_lo, off);

	अगर (!len_mid) अणु
		wrp_zext(nfp_prog, meta, dst_gpr);
		वापस 0;
	पूर्ण

	src_mid = reg_xfer(idx + 1);

	अगर (size <= REG_WIDTH) अणु
		wrp_reg_or_subpart(nfp_prog, dst_lo, src_mid, len_mid, len_lo);
		wrp_zext(nfp_prog, meta, dst_gpr);
	पूर्ण अन्यथा अणु
		swreg src_hi = reg_xfer(idx + 2);

		wrp_reg_or_subpart(nfp_prog, dst_lo, src_mid,
				   REG_WIDTH - len_lo, len_lo);
		wrp_reg_subpart(nfp_prog, dst_hi, src_mid, len_lo,
				REG_WIDTH - len_lo);
		wrp_reg_or_subpart(nfp_prog, dst_hi, src_hi, REG_WIDTH - len_lo,
				   len_lo);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mem_ldx_data_from_pktcache_aligned(काष्ठा nfp_prog *nfp_prog,
				   काष्ठा nfp_insn_meta *meta,
				   अचिन्हित पूर्णांक size)
अणु
	swreg dst_lo, dst_hi, src_lo;
	u8 dst_gpr, idx;

	idx = (meta->insn.off - meta->pkt_cache.range_start) / REG_WIDTH;
	dst_gpr = meta->insn.dst_reg * 2;
	dst_hi = reg_both(dst_gpr + 1);
	dst_lo = reg_both(dst_gpr);
	src_lo = reg_xfer(idx);

	अगर (size < REG_WIDTH) अणु
		wrp_reg_subpart(nfp_prog, dst_lo, src_lo, size, 0);
		wrp_zext(nfp_prog, meta, dst_gpr);
	पूर्ण अन्यथा अगर (size == REG_WIDTH) अणु
		wrp_mov(nfp_prog, dst_lo, src_lo);
		wrp_zext(nfp_prog, meta, dst_gpr);
	पूर्ण अन्यथा अणु
		swreg src_hi = reg_xfer(idx + 1);

		wrp_mov(nfp_prog, dst_lo, src_lo);
		wrp_mov(nfp_prog, dst_hi, src_hi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mem_ldx_data_from_pktcache(काष्ठा nfp_prog *nfp_prog,
			   काष्ठा nfp_insn_meta *meta, अचिन्हित पूर्णांक size)
अणु
	u8 off = meta->insn.off - meta->pkt_cache.range_start;

	अगर (IS_ALIGNED(off, REG_WIDTH))
		वापस mem_ldx_data_from_pktcache_aligned(nfp_prog, meta, size);

	वापस mem_ldx_data_from_pktcache_unaligned(nfp_prog, meta, size);
पूर्ण

अटल पूर्णांक
mem_ldx(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	अचिन्हित पूर्णांक size)
अणु
	अगर (meta->ldst_gather_len)
		वापस nfp_cpp_स_नकल(nfp_prog, meta);

	अगर (meta->ptr.type == PTR_TO_CTX) अणु
		अगर (nfp_prog->type == BPF_PROG_TYPE_XDP)
			वापस mem_ldx_xdp(nfp_prog, meta, size);
		अन्यथा
			वापस mem_ldx_skb(nfp_prog, meta, size);
	पूर्ण

	अगर (meta->ptr.type == PTR_TO_PACKET) अणु
		अगर (meta->pkt_cache.range_end) अणु
			अगर (meta->pkt_cache.करो_init)
				mem_ldx_data_init_pktcache(nfp_prog, meta);

			वापस mem_ldx_data_from_pktcache(nfp_prog, meta, size);
		पूर्ण अन्यथा अणु
			वापस mem_ldx_data(nfp_prog, meta, size);
		पूर्ण
	पूर्ण

	अगर (meta->ptr.type == PTR_TO_STACK)
		वापस mem_ldx_stack(nfp_prog, meta, size,
				     meta->ptr.off + meta->ptr.var_off.value);

	अगर (meta->ptr.type == PTR_TO_MAP_VALUE)
		वापस mem_ldx_emem(nfp_prog, meta, size);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mem_ldx1(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_ldx(nfp_prog, meta, 1);
पूर्ण

अटल पूर्णांक mem_ldx2(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_ldx(nfp_prog, meta, 2);
पूर्ण

अटल पूर्णांक mem_ldx4(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_ldx(nfp_prog, meta, 4);
पूर्ण

अटल पूर्णांक mem_ldx8(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_ldx(nfp_prog, meta, 8);
पूर्ण

अटल पूर्णांक
mem_st_data(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	    अचिन्हित पूर्णांक size)
अणु
	u64 imm = meta->insn.imm; /* sign extend */
	swreg off_reg;

	off_reg = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	वापस data_st_host_order(nfp_prog, meta->insn.dst_reg * 2, off_reg,
				  imm, size);
पूर्ण

अटल पूर्णांक mem_st(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		  अचिन्हित पूर्णांक size)
अणु
	अगर (meta->ptr.type == PTR_TO_PACKET)
		वापस mem_st_data(nfp_prog, meta, size);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mem_st1(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_st(nfp_prog, meta, 1);
पूर्ण

अटल पूर्णांक mem_st2(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_st(nfp_prog, meta, 2);
पूर्ण

अटल पूर्णांक mem_st4(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_st(nfp_prog, meta, 4);
पूर्ण

अटल पूर्णांक mem_st8(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_st(nfp_prog, meta, 8);
पूर्ण

अटल पूर्णांक
mem_stx_data(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	     अचिन्हित पूर्णांक size)
अणु
	swreg off_reg;

	off_reg = re_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	वापस data_stx_host_order(nfp_prog, meta->insn.dst_reg * 2, off_reg,
				   meta->insn.src_reg * 2, size);
पूर्ण

अटल पूर्णांक
mem_stx_stack(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	      अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक ptr_off)
अणु
	वापस mem_op_stack(nfp_prog, meta, size, ptr_off,
			    meta->insn.src_reg * 2, meta->insn.dst_reg * 2,
			    false, wrp_lmem_store);
पूर्ण

अटल पूर्णांक mem_stx_xdp(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	चयन (meta->insn.off) अणु
	हाल दुरत्व(काष्ठा xdp_md, rx_queue_index):
		वापस nfp_queue_select(nfp_prog, meta);
	पूर्ण

	WARN_ON_ONCE(1); /* verअगरier should have rejected bad accesses */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mem_stx(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
	अचिन्हित पूर्णांक size)
अणु
	अगर (meta->ptr.type == PTR_TO_PACKET)
		वापस mem_stx_data(nfp_prog, meta, size);

	अगर (meta->ptr.type == PTR_TO_STACK)
		वापस mem_stx_stack(nfp_prog, meta, size,
				     meta->ptr.off + meta->ptr.var_off.value);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mem_stx1(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_stx(nfp_prog, meta, 1);
पूर्ण

अटल पूर्णांक mem_stx2(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_stx(nfp_prog, meta, 2);
पूर्ण

अटल पूर्णांक mem_stx4(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अगर (meta->ptr.type == PTR_TO_CTX)
		अगर (nfp_prog->type == BPF_PROG_TYPE_XDP)
			वापस mem_stx_xdp(nfp_prog, meta);
	वापस mem_stx(nfp_prog, meta, 4);
पूर्ण

अटल पूर्णांक mem_stx8(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस mem_stx(nfp_prog, meta, 8);
पूर्ण

अटल पूर्णांक
mem_xadd(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta, bool is64)
अणु
	u8 dst_gpr = meta->insn.dst_reg * 2;
	u8 src_gpr = meta->insn.src_reg * 2;
	अचिन्हित पूर्णांक full_add, out;
	swreg addra, addrb, off;

	off = ur_load_imm_any(nfp_prog, meta->insn.off, imm_b(nfp_prog));

	/* We can fit 16 bits पूर्णांकo command immediate, अगर we know the immediate
	 * is guaranteed to either always or never fit पूर्णांकo 16 bit we only
	 * generate code to handle that particular हाल, otherwise generate
	 * code क्रम both.
	 */
	out = nfp_prog_current_offset(nfp_prog);
	full_add = nfp_prog_current_offset(nfp_prog);

	अगर (meta->insn.off) अणु
		out += 2;
		full_add += 2;
	पूर्ण
	अगर (meta->xadd_maybe_16bit) अणु
		out += 3;
		full_add += 3;
	पूर्ण
	अगर (meta->xadd_over_16bit)
		out += 2 + is64;
	अगर (meta->xadd_maybe_16bit && meta->xadd_over_16bit) अणु
		out += 5;
		full_add += 5;
	पूर्ण

	/* Generate the branch क्रम choosing add_imm vs add */
	अगर (meta->xadd_maybe_16bit && meta->xadd_over_16bit) अणु
		swreg max_imm = imm_a(nfp_prog);

		wrp_immed(nfp_prog, max_imm, 0xffff);
		emit_alu(nfp_prog, reg_none(),
			 max_imm, ALU_OP_SUB, reg_b(src_gpr));
		emit_alu(nfp_prog, reg_none(),
			 reg_imm(0), ALU_OP_SUB_C, reg_b(src_gpr + 1));
		emit_br(nfp_prog, BR_BLO, full_add, meta->insn.off ? 2 : 0);
		/* defer क्रम add */
	पूर्ण

	/* If insn has an offset add to the address */
	अगर (!meta->insn.off) अणु
		addra = reg_a(dst_gpr);
		addrb = reg_b(dst_gpr + 1);
	पूर्ण अन्यथा अणु
		emit_alu(nfp_prog, imma_a(nfp_prog),
			 reg_a(dst_gpr), ALU_OP_ADD, off);
		emit_alu(nfp_prog, imma_b(nfp_prog),
			 reg_a(dst_gpr + 1), ALU_OP_ADD_C, reg_imm(0));
		addra = imma_a(nfp_prog);
		addrb = imma_b(nfp_prog);
	पूर्ण

	/* Generate the add_imm अगर 16 bits are possible */
	अगर (meta->xadd_maybe_16bit) अणु
		swreg prev_alu = imm_a(nfp_prog);

		wrp_immed(nfp_prog, prev_alu,
			  FIELD_PREP(CMD_OVE_DATA, 2) |
			  CMD_OVE_LEN |
			  FIELD_PREP(CMD_OV_LEN, 0x8 | is64 << 2));
		wrp_reg_or_subpart(nfp_prog, prev_alu, reg_b(src_gpr), 2, 2);
		emit_cmd_indir(nfp_prog, CMD_TGT_ADD_IMM, CMD_MODE_40b_BA, 0,
			       addra, addrb, 0, CMD_CTX_NO_SWAP);

		अगर (meta->xadd_over_16bit)
			emit_br(nfp_prog, BR_UNC, out, 0);
	पूर्ण

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, full_add))
		वापस -EINVAL;

	/* Generate the add अगर 16 bits are not guaranteed */
	अगर (meta->xadd_over_16bit) अणु
		emit_cmd(nfp_prog, CMD_TGT_ADD, CMD_MODE_40b_BA, 0,
			 addra, addrb, is64 << 2,
			 is64 ? CMD_CTX_SWAP_DEFER2 : CMD_CTX_SWAP_DEFER1);

		wrp_mov(nfp_prog, reg_xfer(0), reg_a(src_gpr));
		अगर (is64)
			wrp_mov(nfp_prog, reg_xfer(1), reg_a(src_gpr + 1));
	पूर्ण

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, out))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mem_atomic4(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अगर (meta->insn.imm != BPF_ADD)
		वापस -EOPNOTSUPP;

	वापस mem_xadd(nfp_prog, meta, false);
पूर्ण

अटल पूर्णांक mem_atomic8(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अगर (meta->insn.imm != BPF_ADD)
		वापस -EOPNOTSUPP;

	वापस mem_xadd(nfp_prog, meta, true);
पूर्ण

अटल पूर्णांक jump(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	emit_br(nfp_prog, BR_UNC, meta->insn.off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jeq_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */
	swreg or1, or2, पंचांगp_reg;

	or1 = reg_a(insn->dst_reg * 2);
	or2 = reg_b(insn->dst_reg * 2 + 1);

	अगर (imm & ~0U) अणु
		पंचांगp_reg = ur_load_imm_any(nfp_prog, imm & ~0U, imm_b(nfp_prog));
		emit_alu(nfp_prog, imm_a(nfp_prog),
			 reg_a(insn->dst_reg * 2), ALU_OP_XOR, पंचांगp_reg);
		or1 = imm_a(nfp_prog);
	पूर्ण

	अगर (imm >> 32) अणु
		पंचांगp_reg = ur_load_imm_any(nfp_prog, imm >> 32, imm_b(nfp_prog));
		emit_alu(nfp_prog, imm_b(nfp_prog),
			 reg_a(insn->dst_reg * 2 + 1), ALU_OP_XOR, पंचांगp_reg);
		or2 = imm_b(nfp_prog);
	पूर्ण

	emit_alu(nfp_prog, reg_none(), or1, ALU_OP_OR, or2);
	emit_br(nfp_prog, BR_BEQ, insn->off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jeq32_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	swreg पंचांगp_reg;

	पंचांगp_reg = ur_load_imm_any(nfp_prog, insn->imm, imm_b(nfp_prog));
	emit_alu(nfp_prog, reg_none(),
		 reg_a(insn->dst_reg * 2), ALU_OP_XOR, पंचांगp_reg);
	emit_br(nfp_prog, BR_BEQ, insn->off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jset_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */
	u8 dst_gpr = insn->dst_reg * 2;
	swreg पंचांगp_reg;

	पंचांगp_reg = ur_load_imm_any(nfp_prog, imm & ~0U, imm_b(nfp_prog));
	emit_alu(nfp_prog, imm_b(nfp_prog),
		 reg_a(dst_gpr), ALU_OP_AND, पंचांगp_reg);
	/* Upper word of the mask can only be 0 or ~0 from sign extension,
	 * so either ignore it or OR the whole thing in.
	 */
	अगर (is_mbpf_jmp64(meta) && imm >> 32) अणु
		emit_alu(nfp_prog, reg_none(),
			 reg_a(dst_gpr + 1), ALU_OP_OR, imm_b(nfp_prog));
	पूर्ण
	emit_br(nfp_prog, BR_BNE, insn->off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jne_imm(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */
	bool is_jmp32 = is_mbpf_jmp32(meta);
	swreg पंचांगp_reg;

	अगर (!imm) अणु
		अगर (is_jmp32)
			emit_alu(nfp_prog, reg_none(), reg_none(), ALU_OP_NONE,
				 reg_b(insn->dst_reg * 2));
		अन्यथा
			emit_alu(nfp_prog, reg_none(), reg_a(insn->dst_reg * 2),
				 ALU_OP_OR, reg_b(insn->dst_reg * 2 + 1));
		emit_br(nfp_prog, BR_BNE, insn->off, 0);
		वापस 0;
	पूर्ण

	पंचांगp_reg = ur_load_imm_any(nfp_prog, imm & ~0U, imm_b(nfp_prog));
	emit_alu(nfp_prog, reg_none(),
		 reg_a(insn->dst_reg * 2), ALU_OP_XOR, पंचांगp_reg);
	emit_br(nfp_prog, BR_BNE, insn->off, 0);

	अगर (is_jmp32)
		वापस 0;

	पंचांगp_reg = ur_load_imm_any(nfp_prog, imm >> 32, imm_b(nfp_prog));
	emit_alu(nfp_prog, reg_none(),
		 reg_a(insn->dst_reg * 2 + 1), ALU_OP_XOR, पंचांगp_reg);
	emit_br(nfp_prog, BR_BNE, insn->off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jeq_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_insn *insn = &meta->insn;

	emit_alu(nfp_prog, imm_a(nfp_prog), reg_a(insn->dst_reg * 2),
		 ALU_OP_XOR, reg_b(insn->src_reg * 2));
	अगर (is_mbpf_jmp64(meta)) अणु
		emit_alu(nfp_prog, imm_b(nfp_prog),
			 reg_a(insn->dst_reg * 2 + 1), ALU_OP_XOR,
			 reg_b(insn->src_reg * 2 + 1));
		emit_alu(nfp_prog, reg_none(), imm_a(nfp_prog), ALU_OP_OR,
			 imm_b(nfp_prog));
	पूर्ण
	emit_br(nfp_prog, BR_BEQ, insn->off, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jset_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_test_reg(nfp_prog, meta, ALU_OP_AND, BR_BNE);
पूर्ण

अटल पूर्णांक jne_reg(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	वापस wrp_test_reg(nfp_prog, meta, ALU_OP_XOR, BR_BNE);
पूर्ण

अटल पूर्णांक
bpf_to_bpf_call(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	u32 ret_tgt, stack_depth, offset_br;
	swreg पंचांगp_reg;

	stack_depth = round_up(nfp_prog->stack_frame_depth, STACK_FRAME_ALIGN);
	/* Space क्रम saving the वापस address is accounted क्रम by the callee,
	 * so stack_depth can be zero क्रम the मुख्य function.
	 */
	अगर (stack_depth) अणु
		पंचांगp_reg = ur_load_imm_any(nfp_prog, stack_depth,
					  stack_imm(nfp_prog));
		emit_alu(nfp_prog, stack_reg(nfp_prog),
			 stack_reg(nfp_prog), ALU_OP_ADD, पंचांगp_reg);
		emit_csr_wr(nfp_prog, stack_reg(nfp_prog),
			    NFP_CSR_ACT_LM_ADDR0);
	पूर्ण

	/* Two हालs क्रम jumping to the callee:
	 *
	 * - If callee uses and needs to save R6~R9 then:
	 *     1. Put the start offset of the callee पूर्णांकo imm_b(). This will
	 *        require a fixup step, as we करो not necessarily know this
	 *        address yet.
	 *     2. Put the वापस address from the callee to the caller पूर्णांकo
	 *        रेजिस्टर ret_reg().
	 *     3. (After defer slots are consumed) Jump to the subroutine that
	 *        pushes the रेजिस्टरs to the stack.
	 *   The subroutine acts as a trampoline, and वापसs to the address in
	 *   imm_b(), i.e. jumps to the callee.
	 *
	 * - If callee करोes not need to save R6~R9 then just load वापस
	 *   address to the caller in ret_reg(), and jump to the callee
	 *   directly.
	 *
	 * Using ret_reg() to pass the वापस address to the callee is set here
	 * as a convention. The callee can then push this address onto its
	 * stack frame in its prologue. The advantages of passing the वापस
	 * address through ret_reg(), instead of pushing it to the stack right
	 * here, are the following:
	 * - It looks cleaner.
	 * - If the called function is called multiple समय, we get a lower
	 *   program size.
	 * - We save two no-op inकाष्ठाions that should be added just beक्रमe
	 *   the emit_br() when stack depth is not null otherwise.
	 * - If we ever find a रेजिस्टर to hold the वापस address during whole
	 *   execution of the callee, we will not have to push the वापस
	 *   address to the stack क्रम leaf functions.
	 */
	अगर (!meta->jmp_dst) अणु
		pr_err("BUG: BPF-to-BPF call has no destination recorded\n");
		वापस -ELOOP;
	पूर्ण
	अगर (nfp_prog->subprog[meta->jmp_dst->subprog_idx].needs_reg_push) अणु
		ret_tgt = nfp_prog_current_offset(nfp_prog) + 3;
		emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2,
			     RELO_BR_GO_CALL_PUSH_REGS);
		offset_br = nfp_prog_current_offset(nfp_prog);
		wrp_immed_relo(nfp_prog, imm_b(nfp_prog), 0, RELO_IMMED_REL);
	पूर्ण अन्यथा अणु
		ret_tgt = nfp_prog_current_offset(nfp_prog) + 2;
		emit_br(nfp_prog, BR_UNC, meta->insn.imm, 1);
		offset_br = nfp_prog_current_offset(nfp_prog);
	पूर्ण
	wrp_immed_relo(nfp_prog, ret_reg(nfp_prog), ret_tgt, RELO_IMMED_REL);

	अगर (!nfp_prog_confirm_current_offset(nfp_prog, ret_tgt))
		वापस -EINVAL;

	अगर (stack_depth) अणु
		पंचांगp_reg = ur_load_imm_any(nfp_prog, stack_depth,
					  stack_imm(nfp_prog));
		emit_alu(nfp_prog, stack_reg(nfp_prog),
			 stack_reg(nfp_prog), ALU_OP_SUB, पंचांगp_reg);
		emit_csr_wr(nfp_prog, stack_reg(nfp_prog),
			    NFP_CSR_ACT_LM_ADDR0);
		wrp_nops(nfp_prog, 3);
	पूर्ण

	meta->num_insns_after_br = nfp_prog_current_offset(nfp_prog);
	meta->num_insns_after_br -= offset_br;

	वापस 0;
पूर्ण

अटल पूर्णांक helper_call(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	चयन (meta->insn.imm) अणु
	हाल BPF_FUNC_xdp_adjust_head:
		वापस adjust_head(nfp_prog, meta);
	हाल BPF_FUNC_xdp_adjust_tail:
		वापस adjust_tail(nfp_prog, meta);
	हाल BPF_FUNC_map_lookup_elem:
	हाल BPF_FUNC_map_update_elem:
	हाल BPF_FUNC_map_delete_elem:
		वापस map_call_stack_common(nfp_prog, meta);
	हाल BPF_FUNC_get_pअक्रमom_u32:
		वापस nfp_get_pअक्रमom_u32(nfp_prog, meta);
	हाल BPF_FUNC_perf_event_output:
		वापस nfp_perf_event_output(nfp_prog, meta);
	शेष:
		WARN_ONCE(1, "verifier allowed unsupported function\n");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक call(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अगर (is_mbpf_pseuकरो_call(meta))
		वापस bpf_to_bpf_call(nfp_prog, meta);
	अन्यथा
		वापस helper_call(nfp_prog, meta);
पूर्ण

अटल bool nfp_is_मुख्य_function(काष्ठा nfp_insn_meta *meta)
अणु
	वापस meta->subprog_idx == 0;
पूर्ण

अटल पूर्णांक जाओ_out(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 0, RELO_BR_GO_OUT);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_subprog_epilogue(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अगर (nfp_prog->subprog[meta->subprog_idx].needs_reg_push) अणु
		/* Pop R6~R9 to the stack via related subroutine.
		 * We loaded the वापस address to the caller पूर्णांकo ret_reg().
		 * This means that the subroutine करोes not come back here, we
		 * make it jump back to the subprogram caller directly!
		 */
		emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 1,
			     RELO_BR_GO_CALL_POP_REGS);
		/* Pop वापस address from the stack. */
		wrp_mov(nfp_prog, ret_reg(nfp_prog), reg_lm(0, 0));
	पूर्ण अन्यथा अणु
		/* Pop वापस address from the stack. */
		wrp_mov(nfp_prog, ret_reg(nfp_prog), reg_lm(0, 0));
		/* Jump back to caller अगर no callee-saved रेजिस्टरs were used
		 * by the subprogram.
		 */
		emit_rtn(nfp_prog, ret_reg(nfp_prog), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jmp_निकास(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अगर (nfp_is_मुख्य_function(meta))
		वापस जाओ_out(nfp_prog, meta);
	अन्यथा
		वापस nfp_subprog_epilogue(nfp_prog, meta);
पूर्ण

अटल स्थिर instr_cb_t instr_cb[256] = अणु
	[BPF_ALU64 | BPF_MOV | BPF_X] =	mov_reg64,
	[BPF_ALU64 | BPF_MOV | BPF_K] =	mov_imm64,
	[BPF_ALU64 | BPF_XOR | BPF_X] =	xor_reg64,
	[BPF_ALU64 | BPF_XOR | BPF_K] =	xor_imm64,
	[BPF_ALU64 | BPF_AND | BPF_X] =	and_reg64,
	[BPF_ALU64 | BPF_AND | BPF_K] =	and_imm64,
	[BPF_ALU64 | BPF_OR | BPF_X] =	or_reg64,
	[BPF_ALU64 | BPF_OR | BPF_K] =	or_imm64,
	[BPF_ALU64 | BPF_ADD | BPF_X] =	add_reg64,
	[BPF_ALU64 | BPF_ADD | BPF_K] =	add_imm64,
	[BPF_ALU64 | BPF_SUB | BPF_X] =	sub_reg64,
	[BPF_ALU64 | BPF_SUB | BPF_K] =	sub_imm64,
	[BPF_ALU64 | BPF_MUL | BPF_X] =	mul_reg64,
	[BPF_ALU64 | BPF_MUL | BPF_K] =	mul_imm64,
	[BPF_ALU64 | BPF_DIV | BPF_X] =	भाग_reg64,
	[BPF_ALU64 | BPF_DIV | BPF_K] =	भाग_imm64,
	[BPF_ALU64 | BPF_NEG] =		neg_reg64,
	[BPF_ALU64 | BPF_LSH | BPF_X] =	shl_reg64,
	[BPF_ALU64 | BPF_LSH | BPF_K] =	shl_imm64,
	[BPF_ALU64 | BPF_RSH | BPF_X] =	shr_reg64,
	[BPF_ALU64 | BPF_RSH | BPF_K] =	shr_imm64,
	[BPF_ALU64 | BPF_ARSH | BPF_X] = ashr_reg64,
	[BPF_ALU64 | BPF_ARSH | BPF_K] = ashr_imm64,
	[BPF_ALU | BPF_MOV | BPF_X] =	mov_reg,
	[BPF_ALU | BPF_MOV | BPF_K] =	mov_imm,
	[BPF_ALU | BPF_XOR | BPF_X] =	xor_reg,
	[BPF_ALU | BPF_XOR | BPF_K] =	xor_imm,
	[BPF_ALU | BPF_AND | BPF_X] =	and_reg,
	[BPF_ALU | BPF_AND | BPF_K] =	and_imm,
	[BPF_ALU | BPF_OR | BPF_X] =	or_reg,
	[BPF_ALU | BPF_OR | BPF_K] =	or_imm,
	[BPF_ALU | BPF_ADD | BPF_X] =	add_reg,
	[BPF_ALU | BPF_ADD | BPF_K] =	add_imm,
	[BPF_ALU | BPF_SUB | BPF_X] =	sub_reg,
	[BPF_ALU | BPF_SUB | BPF_K] =	sub_imm,
	[BPF_ALU | BPF_MUL | BPF_X] =	mul_reg,
	[BPF_ALU | BPF_MUL | BPF_K] =	mul_imm,
	[BPF_ALU | BPF_DIV | BPF_X] =	भाग_reg,
	[BPF_ALU | BPF_DIV | BPF_K] =	भाग_imm,
	[BPF_ALU | BPF_NEG] =		neg_reg,
	[BPF_ALU | BPF_LSH | BPF_X] =	shl_reg,
	[BPF_ALU | BPF_LSH | BPF_K] =	shl_imm,
	[BPF_ALU | BPF_RSH | BPF_X] =	shr_reg,
	[BPF_ALU | BPF_RSH | BPF_K] =	shr_imm,
	[BPF_ALU | BPF_ARSH | BPF_X] =	ashr_reg,
	[BPF_ALU | BPF_ARSH | BPF_K] =	ashr_imm,
	[BPF_ALU | BPF_END | BPF_X] =	end_reg32,
	[BPF_LD | BPF_IMM | BPF_DW] =	imm_ld8,
	[BPF_LD | BPF_ABS | BPF_B] =	data_ld1,
	[BPF_LD | BPF_ABS | BPF_H] =	data_ld2,
	[BPF_LD | BPF_ABS | BPF_W] =	data_ld4,
	[BPF_LD | BPF_IND | BPF_B] =	data_ind_ld1,
	[BPF_LD | BPF_IND | BPF_H] =	data_ind_ld2,
	[BPF_LD | BPF_IND | BPF_W] =	data_ind_ld4,
	[BPF_LDX | BPF_MEM | BPF_B] =	mem_ldx1,
	[BPF_LDX | BPF_MEM | BPF_H] =	mem_ldx2,
	[BPF_LDX | BPF_MEM | BPF_W] =	mem_ldx4,
	[BPF_LDX | BPF_MEM | BPF_DW] =	mem_ldx8,
	[BPF_STX | BPF_MEM | BPF_B] =	mem_stx1,
	[BPF_STX | BPF_MEM | BPF_H] =	mem_stx2,
	[BPF_STX | BPF_MEM | BPF_W] =	mem_stx4,
	[BPF_STX | BPF_MEM | BPF_DW] =	mem_stx8,
	[BPF_STX | BPF_ATOMIC | BPF_W] =	mem_atomic4,
	[BPF_STX | BPF_ATOMIC | BPF_DW] =	mem_atomic8,
	[BPF_ST | BPF_MEM | BPF_B] =	mem_st1,
	[BPF_ST | BPF_MEM | BPF_H] =	mem_st2,
	[BPF_ST | BPF_MEM | BPF_W] =	mem_st4,
	[BPF_ST | BPF_MEM | BPF_DW] =	mem_st8,
	[BPF_JMP | BPF_JA | BPF_K] =	jump,
	[BPF_JMP | BPF_JEQ | BPF_K] =	jeq_imm,
	[BPF_JMP | BPF_JGT | BPF_K] =	cmp_imm,
	[BPF_JMP | BPF_JGE | BPF_K] =	cmp_imm,
	[BPF_JMP | BPF_JLT | BPF_K] =	cmp_imm,
	[BPF_JMP | BPF_JLE | BPF_K] =	cmp_imm,
	[BPF_JMP | BPF_JSGT | BPF_K] =  cmp_imm,
	[BPF_JMP | BPF_JSGE | BPF_K] =  cmp_imm,
	[BPF_JMP | BPF_JSLT | BPF_K] =  cmp_imm,
	[BPF_JMP | BPF_JSLE | BPF_K] =  cmp_imm,
	[BPF_JMP | BPF_JSET | BPF_K] =	jset_imm,
	[BPF_JMP | BPF_JNE | BPF_K] =	jne_imm,
	[BPF_JMP | BPF_JEQ | BPF_X] =	jeq_reg,
	[BPF_JMP | BPF_JGT | BPF_X] =	cmp_reg,
	[BPF_JMP | BPF_JGE | BPF_X] =	cmp_reg,
	[BPF_JMP | BPF_JLT | BPF_X] =	cmp_reg,
	[BPF_JMP | BPF_JLE | BPF_X] =	cmp_reg,
	[BPF_JMP | BPF_JSGT | BPF_X] =  cmp_reg,
	[BPF_JMP | BPF_JSGE | BPF_X] =  cmp_reg,
	[BPF_JMP | BPF_JSLT | BPF_X] =  cmp_reg,
	[BPF_JMP | BPF_JSLE | BPF_X] =  cmp_reg,
	[BPF_JMP | BPF_JSET | BPF_X] =	jset_reg,
	[BPF_JMP | BPF_JNE | BPF_X] =	jne_reg,
	[BPF_JMP32 | BPF_JEQ | BPF_K] =	jeq32_imm,
	[BPF_JMP32 | BPF_JGT | BPF_K] =	cmp_imm,
	[BPF_JMP32 | BPF_JGE | BPF_K] =	cmp_imm,
	[BPF_JMP32 | BPF_JLT | BPF_K] =	cmp_imm,
	[BPF_JMP32 | BPF_JLE | BPF_K] =	cmp_imm,
	[BPF_JMP32 | BPF_JSGT | BPF_K] =cmp_imm,
	[BPF_JMP32 | BPF_JSGE | BPF_K] =cmp_imm,
	[BPF_JMP32 | BPF_JSLT | BPF_K] =cmp_imm,
	[BPF_JMP32 | BPF_JSLE | BPF_K] =cmp_imm,
	[BPF_JMP32 | BPF_JSET | BPF_K] =jset_imm,
	[BPF_JMP32 | BPF_JNE | BPF_K] =	jne_imm,
	[BPF_JMP32 | BPF_JEQ | BPF_X] =	jeq_reg,
	[BPF_JMP32 | BPF_JGT | BPF_X] =	cmp_reg,
	[BPF_JMP32 | BPF_JGE | BPF_X] =	cmp_reg,
	[BPF_JMP32 | BPF_JLT | BPF_X] =	cmp_reg,
	[BPF_JMP32 | BPF_JLE | BPF_X] =	cmp_reg,
	[BPF_JMP32 | BPF_JSGT | BPF_X] =cmp_reg,
	[BPF_JMP32 | BPF_JSGE | BPF_X] =cmp_reg,
	[BPF_JMP32 | BPF_JSLT | BPF_X] =cmp_reg,
	[BPF_JMP32 | BPF_JSLE | BPF_X] =cmp_reg,
	[BPF_JMP32 | BPF_JSET | BPF_X] =jset_reg,
	[BPF_JMP32 | BPF_JNE | BPF_X] =	jne_reg,
	[BPF_JMP | BPF_CALL] =		call,
	[BPF_JMP | BPF_EXIT] =		jmp_निकास,
पूर्ण;

/* --- Assembler logic --- */
अटल पूर्णांक
nfp_fixup_immed_relo(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		     काष्ठा nfp_insn_meta *jmp_dst, u32 br_idx)
अणु
	अगर (immed_get_value(nfp_prog->prog[br_idx + 1])) अणु
		pr_err("BUG: failed to fix up callee register saving\n");
		वापस -EINVAL;
	पूर्ण

	immed_set_value(&nfp_prog->prog[br_idx + 1], jmp_dst->off);

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_fixup_branches(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta, *jmp_dst;
	u32 idx, br_idx;
	पूर्णांक err;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		अगर (meta->flags & FLAG_INSN_SKIP_MASK)
			जारी;
		अगर (!is_mbpf_jmp(meta))
			जारी;
		अगर (meta->insn.code == (BPF_JMP | BPF_EXIT) &&
		    !nfp_is_मुख्य_function(meta))
			जारी;
		अगर (is_mbpf_helper_call(meta))
			जारी;

		अगर (list_is_last(&meta->l, &nfp_prog->insns))
			br_idx = nfp_prog->last_bpf_off;
		अन्यथा
			br_idx = list_next_entry(meta, l)->off - 1;

		/* For BPF-to-BPF function call, a stack adjusपंचांगent sequence is
		 * generated after the वापस inकाष्ठाion. Thereक्रमe, we must
		 * withdraw the length of this sequence to have br_idx poपूर्णांकing
		 * to where the "branch" NFP inकाष्ठाion is expected to be.
		 */
		अगर (is_mbpf_pseuकरो_call(meta))
			br_idx -= meta->num_insns_after_br;

		अगर (!nfp_is_br(nfp_prog->prog[br_idx])) अणु
			pr_err("Fixup found block not ending in branch %d %02x %016llx!!\n",
			       br_idx, meta->insn.code, nfp_prog->prog[br_idx]);
			वापस -ELOOP;
		पूर्ण

		अगर (meta->insn.code == (BPF_JMP | BPF_EXIT))
			जारी;

		/* Leave special branches क्रम later */
		अगर (FIELD_GET(OP_RELO_TYPE, nfp_prog->prog[br_idx]) !=
		    RELO_BR_REL && !is_mbpf_pseuकरो_call(meta))
			जारी;

		अगर (!meta->jmp_dst) अणु
			pr_err("Non-exit jump doesn't have destination info recorded!!\n");
			वापस -ELOOP;
		पूर्ण

		jmp_dst = meta->jmp_dst;

		अगर (jmp_dst->flags & FLAG_INSN_SKIP_PREC_DEPENDENT) अणु
			pr_err("Branch landing on removed instruction!!\n");
			वापस -ELOOP;
		पूर्ण

		अगर (is_mbpf_pseuकरो_call(meta) &&
		    nfp_prog->subprog[jmp_dst->subprog_idx].needs_reg_push) अणु
			err = nfp_fixup_immed_relo(nfp_prog, meta,
						   jmp_dst, br_idx);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (FIELD_GET(OP_RELO_TYPE, nfp_prog->prog[br_idx]) !=
		    RELO_BR_REL)
			जारी;

		क्रम (idx = meta->off; idx <= br_idx; idx++) अणु
			अगर (!nfp_is_br(nfp_prog->prog[idx]))
				जारी;
			br_set_offset(&nfp_prog->prog[idx], jmp_dst->off);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nfp_पूर्णांकro(काष्ठा nfp_prog *nfp_prog)
अणु
	wrp_immed(nfp_prog, plen_reg(nfp_prog), GENMASK(13, 0));
	emit_alu(nfp_prog, plen_reg(nfp_prog),
		 plen_reg(nfp_prog), ALU_OP_AND, pv_len(nfp_prog));
पूर्ण

अटल व्योम
nfp_subprog_prologue(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	/* Save वापस address पूर्णांकo the stack. */
	wrp_mov(nfp_prog, reg_lm(0, 0), ret_reg(nfp_prog));
पूर्ण

अटल व्योम
nfp_start_subprog(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta)
अणु
	अचिन्हित पूर्णांक depth = nfp_prog->subprog[meta->subprog_idx].stack_depth;

	nfp_prog->stack_frame_depth = round_up(depth, 4);
	nfp_subprog_prologue(nfp_prog, meta);
पूर्ण

bool nfp_is_subprog_start(काष्ठा nfp_insn_meta *meta)
अणु
	वापस meta->flags & FLAG_INSN_IS_SUBPROG_START;
पूर्ण

अटल व्योम nfp_outro_tc_da(काष्ठा nfp_prog *nfp_prog)
अणु
	/* TC direct-action mode:
	 *   0,1   ok        NOT SUPPORTED[1]
	 *   2   drop  0x22 -> drop,  count as stat1
	 *   4,5 nuke  0x02 -> drop
	 *   7  redir  0x44 -> redir, count as stat2
	 *   * unspec  0x11 -> pass,  count as stat0
	 *
	 * [1] We can't support OK and RECLASSIFY because we can't tell TC
	 *     the exact decision made.  We are क्रमced to support UNSPEC
	 *     to handle पातs so that's the only one we handle क्रम passing
	 *     packets up the stack.
	 */
	/* Target क्रम पातs */
	nfp_prog->tgt_पात = nfp_prog_current_offset(nfp_prog);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2, RELO_BR_NEXT_PKT);

	wrp_mov(nfp_prog, reg_a(0), NFP_BPF_ABI_FLAGS);
	emit_ld_field(nfp_prog, reg_a(0), 0xc, reg_imm(0x11), SHF_SC_L_SHF, 16);

	/* Target क्रम normal निकासs */
	nfp_prog->tgt_out = nfp_prog_current_offset(nfp_prog);

	/* अगर R0 > 7 jump to पात */
	emit_alu(nfp_prog, reg_none(), reg_imm(7), ALU_OP_SUB, reg_b(0));
	emit_br(nfp_prog, BR_BLO, nfp_prog->tgt_पात, 0);
	wrp_mov(nfp_prog, reg_a(0), NFP_BPF_ABI_FLAGS);

	wrp_immed(nfp_prog, reg_b(2), 0x41221211);
	wrp_immed(nfp_prog, reg_b(3), 0x41001211);

	emit_shf(nfp_prog, reg_a(1),
		 reg_none(), SHF_OP_NONE, reg_b(0), SHF_SC_L_SHF, 2);

	emit_alu(nfp_prog, reg_none(), reg_a(1), ALU_OP_OR, reg_imm(0));
	emit_shf(nfp_prog, reg_a(2),
		 reg_imm(0xf), SHF_OP_AND, reg_b(2), SHF_SC_R_SHF, 0);

	emit_alu(nfp_prog, reg_none(), reg_a(1), ALU_OP_OR, reg_imm(0));
	emit_shf(nfp_prog, reg_b(2),
		 reg_imm(0xf), SHF_OP_AND, reg_b(3), SHF_SC_R_SHF, 0);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2, RELO_BR_NEXT_PKT);

	emit_shf(nfp_prog, reg_b(2),
		 reg_a(2), SHF_OP_OR, reg_b(2), SHF_SC_L_SHF, 4);
	emit_ld_field(nfp_prog, reg_a(0), 0xc, reg_b(2), SHF_SC_L_SHF, 16);
पूर्ण

अटल व्योम nfp_outro_xdp(काष्ठा nfp_prog *nfp_prog)
अणु
	/* XDP वापस codes:
	 *   0 पातed  0x82 -> drop,  count as stat3
	 *   1    drop  0x22 -> drop,  count as stat1
	 *   2    pass  0x11 -> pass,  count as stat0
	 *   3      tx  0x44 -> redir, count as stat2
	 *   * unknown  0x82 -> drop,  count as stat3
	 */
	/* Target क्रम पातs */
	nfp_prog->tgt_पात = nfp_prog_current_offset(nfp_prog);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2, RELO_BR_NEXT_PKT);

	wrp_mov(nfp_prog, reg_a(0), NFP_BPF_ABI_FLAGS);
	emit_ld_field(nfp_prog, reg_a(0), 0xc, reg_imm(0x82), SHF_SC_L_SHF, 16);

	/* Target क्रम normal निकासs */
	nfp_prog->tgt_out = nfp_prog_current_offset(nfp_prog);

	/* अगर R0 > 3 jump to पात */
	emit_alu(nfp_prog, reg_none(), reg_imm(3), ALU_OP_SUB, reg_b(0));
	emit_br(nfp_prog, BR_BLO, nfp_prog->tgt_पात, 0);

	wrp_immed(nfp_prog, reg_b(2), 0x44112282);

	emit_shf(nfp_prog, reg_a(1),
		 reg_none(), SHF_OP_NONE, reg_b(0), SHF_SC_L_SHF, 3);

	emit_alu(nfp_prog, reg_none(), reg_a(1), ALU_OP_OR, reg_imm(0));
	emit_shf(nfp_prog, reg_b(2),
		 reg_imm(0xff), SHF_OP_AND, reg_b(2), SHF_SC_R_SHF, 0);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2, RELO_BR_NEXT_PKT);

	wrp_mov(nfp_prog, reg_a(0), NFP_BPF_ABI_FLAGS);
	emit_ld_field(nfp_prog, reg_a(0), 0xc, reg_b(2), SHF_SC_L_SHF, 16);
पूर्ण

अटल bool nfp_prog_needs_callee_reg_save(काष्ठा nfp_prog *nfp_prog)
अणु
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 1; idx < nfp_prog->subprog_cnt; idx++)
		अगर (nfp_prog->subprog[idx].needs_reg_push)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम nfp_push_callee_रेजिस्टरs(काष्ठा nfp_prog *nfp_prog)
अणु
	u8 reg;

	/* Subroutine: Save all callee saved रेजिस्टरs (R6 ~ R9).
	 * imm_b() holds the वापस address.
	 */
	nfp_prog->tgt_call_push_regs = nfp_prog_current_offset(nfp_prog);
	क्रम (reg = BPF_REG_6; reg <= BPF_REG_9; reg++) अणु
		u8 adj = (reg - BPF_REG_0) * 2;
		u8 idx = (reg - BPF_REG_6) * 2;

		/* The first slot in the stack frame is used to push the वापस
		 * address in bpf_to_bpf_call(), start just after.
		 */
		wrp_mov(nfp_prog, reg_lm(0, 1 + idx), reg_b(adj));

		अगर (reg == BPF_REG_8)
			/* Prepare to jump back, last 3 insns use defer slots */
			emit_rtn(nfp_prog, imm_b(nfp_prog), 3);

		wrp_mov(nfp_prog, reg_lm(0, 1 + idx + 1), reg_b(adj + 1));
	पूर्ण
पूर्ण

अटल व्योम nfp_pop_callee_रेजिस्टरs(काष्ठा nfp_prog *nfp_prog)
अणु
	u8 reg;

	/* Subroutine: Restore all callee saved रेजिस्टरs (R6 ~ R9).
	 * ret_reg() holds the वापस address.
	 */
	nfp_prog->tgt_call_pop_regs = nfp_prog_current_offset(nfp_prog);
	क्रम (reg = BPF_REG_6; reg <= BPF_REG_9; reg++) अणु
		u8 adj = (reg - BPF_REG_0) * 2;
		u8 idx = (reg - BPF_REG_6) * 2;

		/* The first slot in the stack frame holds the वापस address,
		 * start popping just after that.
		 */
		wrp_mov(nfp_prog, reg_both(adj), reg_lm(0, 1 + idx));

		अगर (reg == BPF_REG_8)
			/* Prepare to jump back, last 3 insns use defer slots */
			emit_rtn(nfp_prog, ret_reg(nfp_prog), 3);

		wrp_mov(nfp_prog, reg_both(adj + 1), reg_lm(0, 1 + idx + 1));
	पूर्ण
पूर्ण

अटल व्योम nfp_outro(काष्ठा nfp_prog *nfp_prog)
अणु
	चयन (nfp_prog->type) अणु
	हाल BPF_PROG_TYPE_SCHED_CLS:
		nfp_outro_tc_da(nfp_prog);
		अवरोध;
	हाल BPF_PROG_TYPE_XDP:
		nfp_outro_xdp(nfp_prog);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	अगर (!nfp_prog_needs_callee_reg_save(nfp_prog))
		वापस;

	nfp_push_callee_रेजिस्टरs(nfp_prog);
	nfp_pop_callee_रेजिस्टरs(nfp_prog);
पूर्ण

अटल पूर्णांक nfp_translate(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta;
	अचिन्हित पूर्णांक depth;
	पूर्णांक err;

	depth = nfp_prog->subprog[0].stack_depth;
	nfp_prog->stack_frame_depth = round_up(depth, 4);

	nfp_पूर्णांकro(nfp_prog);
	अगर (nfp_prog->error)
		वापस nfp_prog->error;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		instr_cb_t cb = instr_cb[meta->insn.code];

		meta->off = nfp_prog_current_offset(nfp_prog);

		अगर (nfp_is_subprog_start(meta)) अणु
			nfp_start_subprog(nfp_prog, meta);
			अगर (nfp_prog->error)
				वापस nfp_prog->error;
		पूर्ण

		अगर (meta->flags & FLAG_INSN_SKIP_MASK) अणु
			nfp_prog->n_translated++;
			जारी;
		पूर्ण

		अगर (nfp_meta_has_prev(nfp_prog, meta) &&
		    nfp_meta_prev(meta)->द्विगुन_cb)
			cb = nfp_meta_prev(meta)->द्विगुन_cb;
		अगर (!cb)
			वापस -ENOENT;
		err = cb(nfp_prog, meta);
		अगर (err)
			वापस err;
		अगर (nfp_prog->error)
			वापस nfp_prog->error;

		nfp_prog->n_translated++;
	पूर्ण

	nfp_prog->last_bpf_off = nfp_prog_current_offset(nfp_prog) - 1;

	nfp_outro(nfp_prog);
	अगर (nfp_prog->error)
		वापस nfp_prog->error;

	wrp_nops(nfp_prog, NFP_USTORE_PREFETCH_WINDOW);
	अगर (nfp_prog->error)
		वापस nfp_prog->error;

	वापस nfp_fixup_branches(nfp_prog);
पूर्ण

/* --- Optimizations --- */
अटल व्योम nfp_bpf_opt_reg_init(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		काष्ठा bpf_insn insn = meta->insn;

		/* Programs converted from cBPF start with रेजिस्टर xoring */
		अगर (insn.code == (BPF_ALU64 | BPF_XOR | BPF_X) &&
		    insn.src_reg == insn.dst_reg)
			जारी;

		/* Programs start with R6 = R1 but we ignore the skb poपूर्णांकer */
		अगर (insn.code == (BPF_ALU64 | BPF_MOV | BPF_X) &&
		    insn.src_reg == 1 && insn.dst_reg == 6)
			meta->flags |= FLAG_INSN_SKIP_PREC_DEPENDENT;

		/* Return as soon as something करोesn't match */
		अगर (!(meta->flags & FLAG_INSN_SKIP_MASK))
			वापस;
	पूर्ण
पूर्ण

/* असल(insn.imm) will fit better पूर्णांकo unrestricted reg immediate -
 * convert add/sub of a negative number पूर्णांकo a sub/add of a positive one.
 */
अटल व्योम nfp_bpf_opt_neg_add_sub(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		काष्ठा bpf_insn insn = meta->insn;

		अगर (meta->flags & FLAG_INSN_SKIP_MASK)
			जारी;

		अगर (!is_mbpf_alu(meta) && !is_mbpf_jmp(meta))
			जारी;
		अगर (BPF_SRC(insn.code) != BPF_K)
			जारी;
		अगर (insn.imm >= 0)
			जारी;

		अगर (is_mbpf_jmp(meta)) अणु
			चयन (BPF_OP(insn.code)) अणु
			हाल BPF_JGE:
			हाल BPF_JSGE:
			हाल BPF_JLT:
			हाल BPF_JSLT:
				meta->jump_neg_op = true;
				अवरोध;
			शेष:
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (BPF_OP(insn.code) == BPF_ADD)
				insn.code = BPF_CLASS(insn.code) | BPF_SUB;
			अन्यथा अगर (BPF_OP(insn.code) == BPF_SUB)
				insn.code = BPF_CLASS(insn.code) | BPF_ADD;
			अन्यथा
				जारी;

			meta->insn.code = insn.code | BPF_K;
		पूर्ण

		meta->insn.imm = -insn.imm;
	पूर्ण
पूर्ण

/* Remove masking after load since our load guarantees this is not needed */
अटल व्योम nfp_bpf_opt_ld_mask(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta1, *meta2;
	अटल स्थिर s32 exp_mask[] = अणु
		[BPF_B] = 0x000000ffU,
		[BPF_H] = 0x0000ffffU,
		[BPF_W] = 0xffffffffU,
	पूर्ण;

	nfp_क्रम_each_insn_walk2(nfp_prog, meta1, meta2) अणु
		काष्ठा bpf_insn insn, next;

		insn = meta1->insn;
		next = meta2->insn;

		अगर (BPF_CLASS(insn.code) != BPF_LD)
			जारी;
		अगर (BPF_MODE(insn.code) != BPF_ABS &&
		    BPF_MODE(insn.code) != BPF_IND)
			जारी;

		अगर (next.code != (BPF_ALU64 | BPF_AND | BPF_K))
			जारी;

		अगर (!exp_mask[BPF_SIZE(insn.code)])
			जारी;
		अगर (exp_mask[BPF_SIZE(insn.code)] != next.imm)
			जारी;

		अगर (next.src_reg || next.dst_reg)
			जारी;

		अगर (meta2->flags & FLAG_INSN_IS_JUMP_DST)
			जारी;

		meta2->flags |= FLAG_INSN_SKIP_PREC_DEPENDENT;
	पूर्ण
पूर्ण

अटल व्योम nfp_bpf_opt_ld_shअगरt(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta1, *meta2, *meta3;

	nfp_क्रम_each_insn_walk3(nfp_prog, meta1, meta2, meta3) अणु
		काष्ठा bpf_insn insn, next1, next2;

		insn = meta1->insn;
		next1 = meta2->insn;
		next2 = meta3->insn;

		अगर (BPF_CLASS(insn.code) != BPF_LD)
			जारी;
		अगर (BPF_MODE(insn.code) != BPF_ABS &&
		    BPF_MODE(insn.code) != BPF_IND)
			जारी;
		अगर (BPF_SIZE(insn.code) != BPF_W)
			जारी;

		अगर (!(next1.code == (BPF_LSH | BPF_K | BPF_ALU64) &&
		      next2.code == (BPF_RSH | BPF_K | BPF_ALU64)) &&
		    !(next1.code == (BPF_RSH | BPF_K | BPF_ALU64) &&
		      next2.code == (BPF_LSH | BPF_K | BPF_ALU64)))
			जारी;

		अगर (next1.src_reg || next1.dst_reg ||
		    next2.src_reg || next2.dst_reg)
			जारी;

		अगर (next1.imm != 0x20 || next2.imm != 0x20)
			जारी;

		अगर (meta2->flags & FLAG_INSN_IS_JUMP_DST ||
		    meta3->flags & FLAG_INSN_IS_JUMP_DST)
			जारी;

		meta2->flags |= FLAG_INSN_SKIP_PREC_DEPENDENT;
		meta3->flags |= FLAG_INSN_SKIP_PREC_DEPENDENT;
	पूर्ण
पूर्ण

/* load/store pair that क्रमms memory copy sould look like the following:
 *
 *   ld_width R, [addr_src + offset_src]
 *   st_width [addr_dest + offset_dest], R
 *
 * The destination रेजिस्टर of load and source रेजिस्टर of store should
 * be the same, load and store should also perक्रमm at the same width.
 * If either of addr_src or addr_dest is stack poपूर्णांकer, we करोn't करो the
 * CPP optimization as stack is modelled by रेजिस्टरs on NFP.
 */
अटल bool
curr_pair_is_स_नकल(काष्ठा nfp_insn_meta *ld_meta,
		    काष्ठा nfp_insn_meta *st_meta)
अणु
	काष्ठा bpf_insn *ld = &ld_meta->insn;
	काष्ठा bpf_insn *st = &st_meta->insn;

	अगर (!is_mbpf_load(ld_meta) || !is_mbpf_store(st_meta))
		वापस false;

	अगर (ld_meta->ptr.type != PTR_TO_PACKET &&
	    ld_meta->ptr.type != PTR_TO_MAP_VALUE)
		वापस false;

	अगर (st_meta->ptr.type != PTR_TO_PACKET)
		वापस false;

	अगर (BPF_SIZE(ld->code) != BPF_SIZE(st->code))
		वापस false;

	अगर (ld->dst_reg != st->src_reg)
		वापस false;

	/* There is jump to the store insn in this pair. */
	अगर (st_meta->flags & FLAG_INSN_IS_JUMP_DST)
		वापस false;

	वापस true;
पूर्ण

/* Currently, we only support chaining load/store pairs अगर:
 *
 *  - Their address base रेजिस्टरs are the same.
 *  - Their address offsets are in the same order.
 *  - They operate at the same memory width.
 *  - There is no jump पूर्णांकo the middle of them.
 */
अटल bool
curr_pair_chain_with_previous(काष्ठा nfp_insn_meta *ld_meta,
			      काष्ठा nfp_insn_meta *st_meta,
			      काष्ठा bpf_insn *prev_ld,
			      काष्ठा bpf_insn *prev_st)
अणु
	u8 prev_size, curr_size, prev_ld_base, prev_st_base, prev_ld_dst;
	काष्ठा bpf_insn *ld = &ld_meta->insn;
	काष्ठा bpf_insn *st = &st_meta->insn;
	s16 prev_ld_off, prev_st_off;

	/* This pair is the start pair. */
	अगर (!prev_ld)
		वापस true;

	prev_size = BPF_LDST_BYTES(prev_ld);
	curr_size = BPF_LDST_BYTES(ld);
	prev_ld_base = prev_ld->src_reg;
	prev_st_base = prev_st->dst_reg;
	prev_ld_dst = prev_ld->dst_reg;
	prev_ld_off = prev_ld->off;
	prev_st_off = prev_st->off;

	अगर (ld->dst_reg != prev_ld_dst)
		वापस false;

	अगर (ld->src_reg != prev_ld_base || st->dst_reg != prev_st_base)
		वापस false;

	अगर (curr_size != prev_size)
		वापस false;

	/* There is jump to the head of this pair. */
	अगर (ld_meta->flags & FLAG_INSN_IS_JUMP_DST)
		वापस false;

	/* Both in ascending order. */
	अगर (prev_ld_off + prev_size == ld->off &&
	    prev_st_off + prev_size == st->off)
		वापस true;

	/* Both in descending order. */
	अगर (ld->off + curr_size == prev_ld_off &&
	    st->off + curr_size == prev_st_off)
		वापस true;

	वापस false;
पूर्ण

/* Return TRUE अगर cross memory access happens. Cross memory access means
 * store area is overlapping with load area that a later load might load
 * the value from previous store, क्रम this हाल we can't treat the sequence
 * as an memory copy.
 */
अटल bool
cross_mem_access(काष्ठा bpf_insn *ld, काष्ठा nfp_insn_meta *head_ld_meta,
		 काष्ठा nfp_insn_meta *head_st_meta)
अणु
	s16 head_ld_off, head_st_off, ld_off;

	/* Dअगरferent poपूर्णांकer types करोes not overlap. */
	अगर (head_ld_meta->ptr.type != head_st_meta->ptr.type)
		वापस false;

	/* load and store are both PTR_TO_PACKET, check ID info.  */
	अगर (head_ld_meta->ptr.id != head_st_meta->ptr.id)
		वापस true;

	/* Canonicalize the offsets. Turn all of them against the original
	 * base रेजिस्टर.
	 */
	head_ld_off = head_ld_meta->insn.off + head_ld_meta->ptr.off;
	head_st_off = head_st_meta->insn.off + head_st_meta->ptr.off;
	ld_off = ld->off + head_ld_meta->ptr.off;

	/* Ascending order cross. */
	अगर (ld_off > head_ld_off &&
	    head_ld_off < head_st_off && ld_off >= head_st_off)
		वापस true;

	/* Descending order cross. */
	अगर (ld_off < head_ld_off &&
	    head_ld_off > head_st_off && ld_off <= head_st_off)
		वापस true;

	वापस false;
पूर्ण

/* This pass try to identअगरy the following inकाष्ठाoin sequences.
 *
 *   load R, [regA + offA]
 *   store [regB + offB], R
 *   load R, [regA + offA + स्थिर_imm_A]
 *   store [regB + offB + स्थिर_imm_A], R
 *   load R, [regA + offA + 2 * स्थिर_imm_A]
 *   store [regB + offB + 2 * स्थिर_imm_A], R
 *   ...
 *
 * Above sequence is typically generated by compiler when lowering
 * स_नकल. NFP prefer using CPP inकाष्ठाions to accelerate it.
 */
अटल व्योम nfp_bpf_opt_ldst_gather(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *head_ld_meta = शून्य;
	काष्ठा nfp_insn_meta *head_st_meta = शून्य;
	काष्ठा nfp_insn_meta *meta1, *meta2;
	काष्ठा bpf_insn *prev_ld = शून्य;
	काष्ठा bpf_insn *prev_st = शून्य;
	u8 count = 0;

	nfp_क्रम_each_insn_walk2(nfp_prog, meta1, meta2) अणु
		काष्ठा bpf_insn *ld = &meta1->insn;
		काष्ठा bpf_insn *st = &meta2->insn;

		/* Reset record status अगर any of the following अगर true:
		 *   - The current insn pair is not load/store.
		 *   - The load/store pair करोesn't chain with previous one.
		 *   - The chained load/store pair crossed with previous pair.
		 *   - The chained load/store pair has a total size of memory
		 *     copy beyond 128 bytes which is the maximum length a
		 *     single NFP CPP command can transfer.
		 */
		अगर (!curr_pair_is_स_नकल(meta1, meta2) ||
		    !curr_pair_chain_with_previous(meta1, meta2, prev_ld,
						   prev_st) ||
		    (head_ld_meta && (cross_mem_access(ld, head_ld_meta,
						       head_st_meta) ||
				      head_ld_meta->ldst_gather_len >= 128))) अणु
			अगर (!count)
				जारी;

			अगर (count > 1) अणु
				s16 prev_ld_off = prev_ld->off;
				s16 prev_st_off = prev_st->off;
				s16 head_ld_off = head_ld_meta->insn.off;

				अगर (prev_ld_off < head_ld_off) अणु
					head_ld_meta->insn.off = prev_ld_off;
					head_st_meta->insn.off = prev_st_off;
					head_ld_meta->ldst_gather_len =
						-head_ld_meta->ldst_gather_len;
				पूर्ण

				head_ld_meta->paired_st = &head_st_meta->insn;
				head_st_meta->flags |=
					FLAG_INSN_SKIP_PREC_DEPENDENT;
			पूर्ण अन्यथा अणु
				head_ld_meta->ldst_gather_len = 0;
			पूर्ण

			/* If the chain is ended by an load/store pair then this
			 * could serve as the new head of the the next chain.
			 */
			अगर (curr_pair_is_स_नकल(meta1, meta2)) अणु
				head_ld_meta = meta1;
				head_st_meta = meta2;
				head_ld_meta->ldst_gather_len =
					BPF_LDST_BYTES(ld);
				meta1 = nfp_meta_next(meta1);
				meta2 = nfp_meta_next(meta2);
				prev_ld = ld;
				prev_st = st;
				count = 1;
			पूर्ण अन्यथा अणु
				head_ld_meta = शून्य;
				head_st_meta = शून्य;
				prev_ld = शून्य;
				prev_st = शून्य;
				count = 0;
			पूर्ण

			जारी;
		पूर्ण

		अगर (!head_ld_meta) अणु
			head_ld_meta = meta1;
			head_st_meta = meta2;
		पूर्ण अन्यथा अणु
			meta1->flags |= FLAG_INSN_SKIP_PREC_DEPENDENT;
			meta2->flags |= FLAG_INSN_SKIP_PREC_DEPENDENT;
		पूर्ण

		head_ld_meta->ldst_gather_len += BPF_LDST_BYTES(ld);
		meta1 = nfp_meta_next(meta1);
		meta2 = nfp_meta_next(meta2);
		prev_ld = ld;
		prev_st = st;
		count++;
	पूर्ण
पूर्ण

अटल व्योम nfp_bpf_opt_pkt_cache(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta, *range_node = शून्य;
	s16 range_start = 0, range_end = 0;
	bool cache_avail = false;
	काष्ठा bpf_insn *insn;
	s32 range_ptr_off = 0;
	u32 range_ptr_id = 0;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		अगर (meta->flags & FLAG_INSN_IS_JUMP_DST)
			cache_avail = false;

		अगर (meta->flags & FLAG_INSN_SKIP_MASK)
			जारी;

		insn = &meta->insn;

		अगर (is_mbpf_store_pkt(meta) ||
		    insn->code == (BPF_JMP | BPF_CALL) ||
		    is_mbpf_classic_store_pkt(meta) ||
		    is_mbpf_classic_load(meta)) अणु
			cache_avail = false;
			जारी;
		पूर्ण

		अगर (!is_mbpf_load(meta))
			जारी;

		अगर (meta->ptr.type != PTR_TO_PACKET || meta->ldst_gather_len) अणु
			cache_avail = false;
			जारी;
		पूर्ण

		अगर (!cache_avail) अणु
			cache_avail = true;
			अगर (range_node)
				जाओ end_current_then_start_new;
			जाओ start_new;
		पूर्ण

		/* Check ID to make sure two पढ़ोs share the same
		 * variable offset against PTR_TO_PACKET, and check OFF
		 * to make sure they also share the same स्थिरant
		 * offset.
		 *
		 * OFFs करोn't really need to be the same, because they
		 * are the स्थिरant offsets against PTR_TO_PACKET, so
		 * क्रम dअगरferent OFFs, we could canonicalize them to
		 * offsets against original packet poपूर्णांकer. We करोn't
		 * support this.
		 */
		अगर (meta->ptr.id == range_ptr_id &&
		    meta->ptr.off == range_ptr_off) अणु
			s16 new_start = range_start;
			s16 end, off = insn->off;
			s16 new_end = range_end;
			bool changed = false;

			अगर (off < range_start) अणु
				new_start = off;
				changed = true;
			पूर्ण

			end = off + BPF_LDST_BYTES(insn);
			अगर (end > range_end) अणु
				new_end = end;
				changed = true;
			पूर्ण

			अगर (!changed)
				जारी;

			अगर (new_end - new_start <= 64) अणु
				/* Install new range. */
				range_start = new_start;
				range_end = new_end;
				जारी;
			पूर्ण
		पूर्ण

end_current_then_start_new:
		range_node->pkt_cache.range_start = range_start;
		range_node->pkt_cache.range_end = range_end;
start_new:
		range_node = meta;
		range_node->pkt_cache.करो_init = true;
		range_ptr_id = range_node->ptr.id;
		range_ptr_off = range_node->ptr.off;
		range_start = insn->off;
		range_end = insn->off + BPF_LDST_BYTES(insn);
	पूर्ण

	अगर (range_node) अणु
		range_node->pkt_cache.range_start = range_start;
		range_node->pkt_cache.range_end = range_end;
	पूर्ण

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		अगर (meta->flags & FLAG_INSN_SKIP_MASK)
			जारी;

		अगर (is_mbpf_load_pkt(meta) && !meta->ldst_gather_len) अणु
			अगर (meta->pkt_cache.करो_init) अणु
				range_start = meta->pkt_cache.range_start;
				range_end = meta->pkt_cache.range_end;
			पूर्ण अन्यथा अणु
				meta->pkt_cache.range_start = range_start;
				meta->pkt_cache.range_end = range_end;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_bpf_optimize(काष्ठा nfp_prog *nfp_prog)
अणु
	nfp_bpf_opt_reg_init(nfp_prog);

	nfp_bpf_opt_neg_add_sub(nfp_prog);
	nfp_bpf_opt_ld_mask(nfp_prog);
	nfp_bpf_opt_ld_shअगरt(nfp_prog);
	nfp_bpf_opt_ldst_gather(nfp_prog);
	nfp_bpf_opt_pkt_cache(nfp_prog);

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_bpf_replace_map_ptrs(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta1, *meta2;
	काष्ठा nfp_bpf_map *nfp_map;
	काष्ठा bpf_map *map;
	u32 id;

	nfp_क्रम_each_insn_walk2(nfp_prog, meta1, meta2) अणु
		अगर (meta1->flags & FLAG_INSN_SKIP_MASK ||
		    meta2->flags & FLAG_INSN_SKIP_MASK)
			जारी;

		अगर (meta1->insn.code != (BPF_LD | BPF_IMM | BPF_DW) ||
		    meta1->insn.src_reg != BPF_PSEUDO_MAP_FD)
			जारी;

		map = (व्योम *)(अचिन्हित दीर्घ)((u32)meta1->insn.imm |
					      (u64)meta2->insn.imm << 32);
		अगर (bpf_map_offload_neutral(map)) अणु
			id = map->id;
		पूर्ण अन्यथा अणु
			nfp_map = map_to_offmap(map)->dev_priv;
			id = nfp_map->tid;
		पूर्ण

		meta1->insn.imm = id;
		meta2->insn.imm = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_bpf_ustore_calc(u64 *prog, अचिन्हित पूर्णांक len)
अणु
	__le64 *ustore = (__क्रमce __le64 *)prog;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक err;

		err = nfp_ustore_check_valid_no_ecc(prog[i]);
		अगर (err)
			वापस err;

		ustore[i] = cpu_to_le64(nfp_ustore_calc_ecc_insn(prog[i]));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nfp_bpf_prog_trim(काष्ठा nfp_prog *nfp_prog)
अणु
	व्योम *prog;

	prog = kvदो_स्मृति_array(nfp_prog->prog_len, माप(u64), GFP_KERNEL);
	अगर (!prog)
		वापस;

	nfp_prog->__prog_alloc_len = nfp_prog->prog_len * माप(u64);
	स_नकल(prog, nfp_prog->prog, nfp_prog->__prog_alloc_len);
	kvमुक्त(nfp_prog->prog);
	nfp_prog->prog = prog;
पूर्ण

पूर्णांक nfp_bpf_jit(काष्ठा nfp_prog *nfp_prog)
अणु
	पूर्णांक ret;

	ret = nfp_bpf_replace_map_ptrs(nfp_prog);
	अगर (ret)
		वापस ret;

	ret = nfp_bpf_optimize(nfp_prog);
	अगर (ret)
		वापस ret;

	ret = nfp_translate(nfp_prog);
	अगर (ret) अणु
		pr_err("Translation failed with error %d (translated: %u)\n",
		       ret, nfp_prog->n_translated);
		वापस -EINVAL;
	पूर्ण

	nfp_bpf_prog_trim(nfp_prog);

	वापस ret;
पूर्ण

व्योम nfp_bpf_jit_prepare(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta;

	/* Another pass to record jump inक्रमmation. */
	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		काष्ठा nfp_insn_meta *dst_meta;
		u64 code = meta->insn.code;
		अचिन्हित पूर्णांक dst_idx;
		bool pseuकरो_call;

		अगर (!is_mbpf_jmp(meta))
			जारी;
		अगर (BPF_OP(code) == BPF_EXIT)
			जारी;
		अगर (is_mbpf_helper_call(meta))
			जारी;

		/* If opcode is BPF_CALL at this poपूर्णांक, this can only be a
		 * BPF-to-BPF call (a.k.a pseuकरो call).
		 */
		pseuकरो_call = BPF_OP(code) == BPF_CALL;

		अगर (pseuकरो_call)
			dst_idx = meta->n + 1 + meta->insn.imm;
		अन्यथा
			dst_idx = meta->n + 1 + meta->insn.off;

		dst_meta = nfp_bpf_जाओ_meta(nfp_prog, meta, dst_idx);

		अगर (pseuकरो_call)
			dst_meta->flags |= FLAG_INSN_IS_SUBPROG_START;

		dst_meta->flags |= FLAG_INSN_IS_JUMP_DST;
		meta->jmp_dst = dst_meta;
	पूर्ण
पूर्ण

bool nfp_bpf_supported_opcode(u8 code)
अणु
	वापस !!instr_cb[code];
पूर्ण

व्योम *nfp_bpf_relo_क्रम_vnic(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_bpf_vnic *bv)
अणु
	अचिन्हित पूर्णांक i;
	u64 *prog;
	पूर्णांक err;

	prog = kmemdup(nfp_prog->prog, nfp_prog->prog_len * माप(u64),
		       GFP_KERNEL);
	अगर (!prog)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < nfp_prog->prog_len; i++) अणु
		क्रमागत nfp_relo_type special;
		u32 val;
		u16 off;

		special = FIELD_GET(OP_RELO_TYPE, prog[i]);
		चयन (special) अणु
		हाल RELO_NONE:
			जारी;
		हाल RELO_BR_REL:
			br_add_offset(&prog[i], bv->start_off);
			अवरोध;
		हाल RELO_BR_GO_OUT:
			br_set_offset(&prog[i],
				      nfp_prog->tgt_out + bv->start_off);
			अवरोध;
		हाल RELO_BR_GO_ABORT:
			br_set_offset(&prog[i],
				      nfp_prog->tgt_पात + bv->start_off);
			अवरोध;
		हाल RELO_BR_GO_CALL_PUSH_REGS:
			अगर (!nfp_prog->tgt_call_push_regs) अणु
				pr_err("BUG: failed to detect subprogram registers needs\n");
				err = -EINVAL;
				जाओ err_मुक्त_prog;
			पूर्ण
			off = nfp_prog->tgt_call_push_regs + bv->start_off;
			br_set_offset(&prog[i], off);
			अवरोध;
		हाल RELO_BR_GO_CALL_POP_REGS:
			अगर (!nfp_prog->tgt_call_pop_regs) अणु
				pr_err("BUG: failed to detect subprogram registers needs\n");
				err = -EINVAL;
				जाओ err_मुक्त_prog;
			पूर्ण
			off = nfp_prog->tgt_call_pop_regs + bv->start_off;
			br_set_offset(&prog[i], off);
			अवरोध;
		हाल RELO_BR_NEXT_PKT:
			br_set_offset(&prog[i], bv->tgt_करोne);
			अवरोध;
		हाल RELO_BR_HELPER:
			val = br_get_offset(prog[i]);
			val -= BR_OFF_RELO;
			चयन (val) अणु
			हाल BPF_FUNC_map_lookup_elem:
				val = nfp_prog->bpf->helpers.map_lookup;
				अवरोध;
			हाल BPF_FUNC_map_update_elem:
				val = nfp_prog->bpf->helpers.map_update;
				अवरोध;
			हाल BPF_FUNC_map_delete_elem:
				val = nfp_prog->bpf->helpers.map_delete;
				अवरोध;
			हाल BPF_FUNC_perf_event_output:
				val = nfp_prog->bpf->helpers.perf_event_output;
				अवरोध;
			शेष:
				pr_err("relocation of unknown helper %d\n",
				       val);
				err = -EINVAL;
				जाओ err_मुक्त_prog;
			पूर्ण
			br_set_offset(&prog[i], val);
			अवरोध;
		हाल RELO_IMMED_REL:
			immed_add_value(&prog[i], bv->start_off);
			अवरोध;
		पूर्ण

		prog[i] &= ~OP_RELO_TYPE;
	पूर्ण

	err = nfp_bpf_ustore_calc(prog, nfp_prog->prog_len);
	अगर (err)
		जाओ err_मुक्त_prog;

	वापस prog;

err_मुक्त_prog:
	kमुक्त(prog);
	वापस ERR_PTR(err);
पूर्ण
