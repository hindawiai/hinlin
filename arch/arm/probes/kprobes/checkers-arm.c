<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/probes/kprobes/checkers-arm.c
 *
 * Copyright (C) 2014 Huawei Inc.
 */

#समावेश <linux/kernel.h>
#समावेश "../decode.h"
#समावेश "../decode-arm.h"
#समावेश "checkers.h"

अटल क्रमागत probes_insn __kprobes arm_check_stack(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	/*
	 * PROBES_LDRSTRD, PROBES_LDMSTM, PROBES_STORE,
	 * PROBES_STORE_EXTRA may get here. Simply mark all normal
	 * insns as STACK_USE_NONE.
	 */
	अटल स्थिर जोड़ decode_item table[] = अणु
		/*
		 * 'STR{,D,B,H}, Rt, [Rn, Rm]' should be marked as UNKNOWN
		 * अगर Rn or Rm is SP.
		 *                                 x
		 * STR (रेजिस्टर)	cccc 011x x0x0 xxxx xxxx xxxx xxxx xxxx
		 * STRB (रेजिस्टर)	cccc 011x x1x0 xxxx xxxx xxxx xxxx xxxx
		 */
		DECODE_OR	(0x0e10000f, 0x0600000d),
		DECODE_OR	(0x0e1f0000, 0x060d0000),

		/*
		 *                                                     x
		 * STRD (रेजिस्टर)	cccc 000x x0x0 xxxx xxxx xxxx 1111 xxxx
		 * STRH (रेजिस्टर)	cccc 000x x0x0 xxxx xxxx xxxx 1011 xxxx
		 */
		DECODE_OR	(0x0e5000bf, 0x000000bd),
		DECODE_CUSTOM	(0x0e5f00b0, 0x000d00b0, STACK_USE_UNKNOWN),

		/*
		 * For PROBES_LDMSTM, only sपंचांगdx sp, [...] need to examine
		 *
		 * Bit B/A (bit 24) encodes arithmetic operation order. 1 means
		 * beक्रमe, 0 means after.
		 * Bit I/D (bit 23) encodes arithmetic operation. 1 means
		 * increment, 0 means decrement.
		 *
		 * So:
		 *                              B I
		 *                              / /
		 *                              A D   | Rn |
		 * STMDX SP, [...]	cccc 100x 00x0 xxxx xxxx xxxx xxxx xxxx
		 */
		DECODE_CUSTOM	(0x0edf0000, 0x080d0000, STACK_USE_STMDX),

		/*                              P U W | Rn | Rt |     imm12    |*/
		/* STR (immediate)	cccc 010x x0x0 1101 xxxx xxxx xxxx xxxx */
		/* STRB (immediate)	cccc 010x x1x0 1101 xxxx xxxx xxxx xxxx */
		/*                              P U W | Rn | Rt |imm4|    |imm4|*/
		/* STRD (immediate)	cccc 000x x1x0 1101 xxxx xxxx 1111 xxxx */
		/* STRH (immediate)	cccc 000x x1x0 1101 xxxx xxxx 1011 xxxx */
		/*
		 * index = (P == '1'); add = (U == '1').
		 * Above insns with:
		 *    index == 0 (strअणु,d,hपूर्ण rx, [sp], #+/-imm) or
		 *    add == 1 (strअणु,d,hपूर्ण rx, [sp, #+<imm>])
		 * should be STACK_USE_NONE.
		 * Only strअणु,b,d,hपूर्ण rx,[sp,#-n] (P == 1 and U == 0) are
		 * required to be examined.
		 */
		/* STRअणु,Bपूर्ण Rt,[SP,#-n]	cccc 0101 0xx0 1101 xxxx xxxx xxxx xxxx */
		DECODE_CUSTOM	(0x0f9f0000, 0x050d0000, STACK_USE_FIXED_XXX),

		/* STRअणुD,Hपूर्ण Rt,[SP,#-n]	cccc 0001 01x0 1101 xxxx xxxx 1x11 xxxx */
		DECODE_CUSTOM	(0x0fdf00b0, 0x014d00b0, STACK_USE_FIXED_X0X),

		/* fall through */
		DECODE_CUSTOM	(0, 0, STACK_USE_NONE),
		DECODE_END
	पूर्ण;

	वापस probes_decode_insn(insn, asi, table, false, false, stack_check_actions, शून्य);
पूर्ण

स्थिर काष्ठा decode_checker arm_stack_checker[NUM_PROBES_ARM_ACTIONS] = अणु
	[PROBES_LDRSTRD] = अणु.checker = arm_check_stackपूर्ण,
	[PROBES_STORE_EXTRA] = अणु.checker = arm_check_stackपूर्ण,
	[PROBES_STORE] = अणु.checker = arm_check_stackपूर्ण,
	[PROBES_LDMSTM] = अणु.checker = arm_check_stackपूर्ण,
पूर्ण;

अटल क्रमागत probes_insn __kprobes arm_check_regs_nouse(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	asi->रेजिस्टर_usage_flags = 0;
	वापस INSN_GOOD;
पूर्ण

अटल क्रमागत probes_insn arm_check_regs_normal(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	u32 regs = h->type_regs.bits >> DECODE_TYPE_BITS;
	पूर्णांक i;

	asi->रेजिस्टर_usage_flags = 0;
	क्रम (i = 0; i < 5; regs >>= 4, insn >>= 4, i++)
		अगर (regs & 0xf)
			asi->रेजिस्टर_usage_flags |= 1 << (insn & 0xf);

	वापस INSN_GOOD;
पूर्ण


अटल क्रमागत probes_insn arm_check_regs_ldmsपंचांग(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	अचिन्हित पूर्णांक reglist = insn & 0xffff;
	अचिन्हित पूर्णांक rn = (insn >> 16) & 0xf;
	asi->रेजिस्टर_usage_flags = reglist | (1 << rn);
	वापस INSN_GOOD;
पूर्ण

अटल क्रमागत probes_insn arm_check_regs_mov_ip_sp(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	/* Inकाष्ठाion is 'mov ip, sp' i.e. 'mov r12, r13' */
	asi->रेजिस्टर_usage_flags = (1 << 12) | (1<< 13);
	वापस INSN_GOOD;
पूर्ण

/*
 *                                    | Rn |Rt/d|         | Rm |
 * LDRD (रेजिस्टर)      cccc 000x x0x0 xxxx xxxx xxxx 1101 xxxx
 * STRD (रेजिस्टर)      cccc 000x x0x0 xxxx xxxx xxxx 1111 xxxx
 *                                    | Rn |Rt/d|         |imm4L|
 * LDRD (immediate)     cccc 000x x1x0 xxxx xxxx xxxx 1101 xxxx
 * STRD (immediate)     cccc 000x x1x0 xxxx xxxx xxxx 1111 xxxx
 *
 * Such inकाष्ठाions access Rt/d and its next रेजिस्टर, so dअगरferent
 * from others, a specअगरic checker is required to handle this extra
 * implicit रेजिस्टर usage.
 */
अटल क्रमागत probes_insn arm_check_regs_ldrdstrd(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	पूर्णांक rdt = (insn >> 12) & 0xf;
	arm_check_regs_normal(insn, asi, h);
	asi->रेजिस्टर_usage_flags |= 1 << (rdt + 1);
	वापस INSN_GOOD;
पूर्ण


स्थिर काष्ठा decode_checker arm_regs_checker[NUM_PROBES_ARM_ACTIONS] = अणु
	[PROBES_MRS] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_SATURATING_ARITHMETIC] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_MUL1] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_MUL2] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_MUL_ADD_LONG] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_MUL_ADD] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_LOAD] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_LOAD_EXTRA] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_STORE] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_STORE_EXTRA] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_DATA_PROCESSING_REG] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_DATA_PROCESSING_IMM] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_SEV] = अणु.checker = arm_check_regs_nouseपूर्ण,
	[PROBES_WFE] = अणु.checker = arm_check_regs_nouseपूर्ण,
	[PROBES_SATURATE] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_REV] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_MMI] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_PACK] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_EXTEND] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_EXTEND_ADD] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_BITFIELD] = अणु.checker = arm_check_regs_normalपूर्ण,
	[PROBES_LDMSTM] = अणु.checker = arm_check_regs_ldmsपंचांगपूर्ण,
	[PROBES_MOV_IP_SP] = अणु.checker = arm_check_regs_mov_ip_spपूर्ण,
	[PROBES_LDRSTRD] = अणु.checker = arm_check_regs_ldrdstrdपूर्ण,
पूर्ण;
