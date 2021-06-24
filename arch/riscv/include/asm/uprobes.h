<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _ASM_RISCV_UPROBES_H
#घोषणा _ASM_RISCV_UPROBES_H

#समावेश <यंत्र/probes.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/bug.h>

#घोषणा MAX_UINSN_BYTES		8

#अगर_घोषित CONFIG_RISCV_ISA_C
#घोषणा UPROBE_SWBP_INSN	__BUG_INSN_16
#घोषणा UPROBE_SWBP_INSN_SIZE	2
#अन्यथा
#घोषणा UPROBE_SWBP_INSN	__BUG_INSN_32
#घोषणा UPROBE_SWBP_INSN_SIZE	4
#पूर्ण_अगर
#घोषणा UPROBE_XOL_SLOT_BYTES	MAX_UINSN_BYTES

प्रकार u32 uprobe_opcode_t;

काष्ठा arch_uprobe_task अणु
	अचिन्हित दीर्घ   saved_cause;
पूर्ण;

काष्ठा arch_uprobe अणु
	जोड़ अणु
		u8 insn[MAX_UINSN_BYTES];
		u8 ixol[MAX_UINSN_BYTES];
	पूर्ण;
	काष्ठा arch_probe_insn api;
	अचिन्हित दीर्घ insn_size;
	bool simulate;
पूर्ण;

bool uprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs);
bool uprobe_single_step_handler(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* _ASM_RISCV_UPROBES_H */
