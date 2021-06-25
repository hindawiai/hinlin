<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/probes/decode-thumb.h
 *
 * Copyright 2013 Linaro Ltd.
 * Written by: David A. Long
 */

#अगर_अघोषित _ARM_KERNEL_PROBES_THUMB_H
#घोषणा  _ARM_KERNEL_PROBES_THUMB_H

#समावेश "decode.h"

/*
 * True अगर current inकाष्ठाion is in an IT block.
 */
#घोषणा in_it_block(cpsr)	((cpsr & 0x06000c00) != 0x00000000)

/*
 * Return the condition code to check क्रम the currently executing inकाष्ठाion.
 * This is in ITSTATE<7:4> which is in CPSR<15:12> but is only valid अगर
 * in_it_block वापसs true.
 */
#घोषणा current_cond(cpsr)	((cpsr >> 12) & 0xf)

क्रमागत probes_t32_action अणु
	PROBES_T32_EMULATE_NONE,
	PROBES_T32_SIMULATE_NOP,
	PROBES_T32_LDMSTM,
	PROBES_T32_LDRDSTRD,
	PROBES_T32_TABLE_BRANCH,
	PROBES_T32_TST,
	PROBES_T32_CMP,
	PROBES_T32_MOV,
	PROBES_T32_ADDSUB,
	PROBES_T32_LOGICAL,
	PROBES_T32_ADDWSUBW_PC,
	PROBES_T32_ADDWSUBW,
	PROBES_T32_MOVW,
	PROBES_T32_SAT,
	PROBES_T32_BITFIELD,
	PROBES_T32_SEV,
	PROBES_T32_WFE,
	PROBES_T32_MRS,
	PROBES_T32_BRANCH_COND,
	PROBES_T32_BRANCH,
	PROBES_T32_PLDI,
	PROBES_T32_LDR_LIT,
	PROBES_T32_LDRSTR,
	PROBES_T32_SIGN_EXTEND,
	PROBES_T32_MEDIA,
	PROBES_T32_REVERSE,
	PROBES_T32_MUL_ADD,
	PROBES_T32_MUL_ADD2,
	PROBES_T32_MUL_ADD_LONG,
	NUM_PROBES_T32_ACTIONS
पूर्ण;

क्रमागत probes_t16_action अणु
	PROBES_T16_ADD_SP,
	PROBES_T16_CBZ,
	PROBES_T16_SIGN_EXTEND,
	PROBES_T16_PUSH,
	PROBES_T16_POP,
	PROBES_T16_SEV,
	PROBES_T16_WFE,
	PROBES_T16_IT,
	PROBES_T16_CMP,
	PROBES_T16_ADDSUB,
	PROBES_T16_LOGICAL,
	PROBES_T16_BLX,
	PROBES_T16_HIREGOPS,
	PROBES_T16_LDR_LIT,
	PROBES_T16_LDRHSTRH,
	PROBES_T16_LDRSTR,
	PROBES_T16_ADR,
	PROBES_T16_LDMSTM,
	PROBES_T16_BRANCH_COND,
	PROBES_T16_BRANCH,
	NUM_PROBES_T16_ACTIONS
पूर्ण;

बाह्य स्थिर जोड़ decode_item probes_decode_thumb32_table[];
बाह्य स्थिर जोड़ decode_item probes_decode_thumb16_table[];

क्रमागत probes_insn __kprobes
thumb16_probes_decode_insn(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		bool emulate, स्थिर जोड़ decode_action *actions,
		स्थिर काष्ठा decode_checker *checkers[]);
क्रमागत probes_insn __kprobes
thumb32_probes_decode_insn(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
		bool emulate, स्थिर जोड़ decode_action *actions,
		स्थिर काष्ठा decode_checker *checkers[]);

#पूर्ण_अगर
