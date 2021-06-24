<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __ASM_CSKY_UPROBES_H
#घोषणा __ASM_CSKY_UPROBES_H

#समावेश <यंत्र/probes.h>

#घोषणा MAX_UINSN_BYTES		4

#घोषणा UPROBE_SWBP_INSN	USR_BKPT
#घोषणा UPROBE_SWBP_INSN_SIZE	2
#घोषणा UPROBE_XOL_SLOT_BYTES	MAX_UINSN_BYTES

प्रकार u32 uprobe_opcode_t;

काष्ठा arch_uprobe_task अणु
	अचिन्हित दीर्घ   saved_trap_no;
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

पूर्णांक uprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs);
पूर्णांक uprobe_single_step_handler(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASM_CSKY_UPROBES_H */
