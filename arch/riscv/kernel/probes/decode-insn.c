<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <यंत्र/sections.h>

#समावेश "decode-insn.h"
#समावेश "simulate-insn.h"

/* Return:
 *   INSN_REJECTED     If inकाष्ठाion is one not allowed to kprobe,
 *   INSN_GOOD_NO_SLOT If inकाष्ठाion is supported but करोesn't use its slot.
 */
क्रमागत probe_insn __kprobes
riscv_probe_decode_insn(probe_opcode_t *addr, काष्ठा arch_probe_insn *api)
अणु
	probe_opcode_t insn = *addr;

	/*
	 * Reject inकाष्ठाions list:
	 */
	RISCV_INSN_REJECTED(प्रणाली,		insn);
	RISCV_INSN_REJECTED(fence,		insn);

	/*
	 * Simulate inकाष्ठाions list:
	 * TODO: the REJECTED ones below need to be implemented
	 */
#अगर_घोषित CONFIG_RISCV_ISA_C
	RISCV_INSN_REJECTED(c_j,		insn);
	RISCV_INSN_REJECTED(c_jr,		insn);
	RISCV_INSN_REJECTED(c_jal,		insn);
	RISCV_INSN_REJECTED(c_jalr,		insn);
	RISCV_INSN_REJECTED(c_beqz,		insn);
	RISCV_INSN_REJECTED(c_bnez,		insn);
	RISCV_INSN_REJECTED(c_eअवरोध,		insn);
#पूर्ण_अगर

	RISCV_INSN_REJECTED(auipc,		insn);
	RISCV_INSN_REJECTED(branch,		insn);

	RISCV_INSN_SET_SIMULATE(jal,		insn);
	RISCV_INSN_SET_SIMULATE(jalr,		insn);

	वापस INSN_GOOD;
पूर्ण
