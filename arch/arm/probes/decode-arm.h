<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/probes/decode-arm.h
 *
 * Copyright 2013 Linaro Ltd.
 * Written by: David A. Long
 */

#अगर_अघोषित _ARM_KERNEL_PROBES_ARM_H
#घोषणा  _ARM_KERNEL_PROBES_ARM_H

#समावेश "decode.h"

क्रमागत probes_arm_action अणु
	PROBES_PRELOAD_IMM,
	PROBES_PRELOAD_REG,
	PROBES_BRANCH_IMM,
	PROBES_BRANCH_REG,
	PROBES_MRS,
	PROBES_CLZ,
	PROBES_SATURATING_ARITHMETIC,
	PROBES_MUL1,
	PROBES_MUL2,
	PROBES_SWP,
	PROBES_LDRSTRD,
	PROBES_LOAD,
	PROBES_STORE,
	PROBES_LOAD_EXTRA,
	PROBES_STORE_EXTRA,
	PROBES_MOV_IP_SP,
	PROBES_DATA_PROCESSING_REG,
	PROBES_DATA_PROCESSING_IMM,
	PROBES_MOV_HALFWORD,
	PROBES_SEV,
	PROBES_WFE,
	PROBES_SATURATE,
	PROBES_REV,
	PROBES_MMI,
	PROBES_PACK,
	PROBES_EXTEND,
	PROBES_EXTEND_ADD,
	PROBES_MUL_ADD_LONG,
	PROBES_MUL_ADD,
	PROBES_BITFIELD,
	PROBES_BRANCH,
	PROBES_LDMSTM,
	NUM_PROBES_ARM_ACTIONS
पूर्ण;

व्योम __kprobes simulate_bbl(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs);
व्योम __kprobes simulate_blx1(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs);
व्योम __kprobes simulate_blx2bx(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs);
व्योम __kprobes simulate_mrs(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs);
व्योम __kprobes simulate_mov_ipsp(probes_opcode_t opcode,
	काष्ठा arch_probes_insn *asi, काष्ठा pt_regs *regs);

बाह्य स्थिर जोड़ decode_item probes_decode_arm_table[];

क्रमागत probes_insn arm_probes_decode_insn(probes_opcode_t,
		काष्ठा arch_probes_insn *, bool emulate,
		स्थिर जोड़ decode_action *actions,
		स्थिर काष्ठा decode_checker *checkers[]);

#पूर्ण_अगर
