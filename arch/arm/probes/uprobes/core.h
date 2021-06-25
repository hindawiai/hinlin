<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Rabin Vincent <rabin at rab.in>
 */

#अगर_अघोषित __ARM_KERNEL_UPROBES_H
#घोषणा __ARM_KERNEL_UPROBES_H

क्रमागत probes_insn uprobe_decode_ldmsपंचांग(probes_opcode_t insn,
				      काष्ठा arch_probes_insn *asi,
				      स्थिर काष्ठा decode_header *d);

क्रमागत probes_insn decode_ldr(probes_opcode_t insn,
			    काष्ठा arch_probes_insn *asi,
			    स्थिर काष्ठा decode_header *d);

क्रमागत probes_insn
decode_rd12rn16rm0rs8_rwflags(probes_opcode_t insn,
			      काष्ठा arch_probes_insn *asi,
			      स्थिर काष्ठा decode_header *d);

क्रमागत probes_insn
decode_wb_pc(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
	     स्थिर काष्ठा decode_header *d, bool alu);

क्रमागत probes_insn
decode_pc_ro(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
	     स्थिर काष्ठा decode_header *d);

बाह्य स्थिर जोड़ decode_action uprobes_probes_actions[];

#पूर्ण_अगर
