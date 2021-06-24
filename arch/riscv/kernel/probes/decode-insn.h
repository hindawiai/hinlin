<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अगर_अघोषित _RISCV_KERNEL_KPROBES_DECODE_INSN_H
#घोषणा _RISCV_KERNEL_KPROBES_DECODE_INSN_H

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/kprobes.h>

क्रमागत probe_insn अणु
	INSN_REJECTED,
	INSN_GOOD_NO_SLOT,
	INSN_GOOD,
पूर्ण;

क्रमागत probe_insn __kprobes
riscv_probe_decode_insn(probe_opcode_t *addr, काष्ठा arch_probe_insn *asi);

#पूर्ण_अगर /* _RISCV_KERNEL_KPROBES_DECODE_INSN_H */
