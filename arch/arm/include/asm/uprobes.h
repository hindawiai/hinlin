<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Rabin Vincent <rabin at rab.in>
 */

#अगर_अघोषित _ASM_UPROBES_H
#घोषणा _ASM_UPROBES_H

#समावेश <यंत्र/probes.h>
#समावेश <यंत्र/opcodes.h>

प्रकार u32 uprobe_opcode_t;

#घोषणा MAX_UINSN_BYTES		4
#घोषणा UPROBE_XOL_SLOT_BYTES	64

#घोषणा UPROBE_SWBP_ARM_INSN	0xe7f001f9
#घोषणा UPROBE_SS_ARM_INSN	0xe7f001fa
#घोषणा UPROBE_SWBP_INSN	__opcode_to_mem_arm(UPROBE_SWBP_ARM_INSN)
#घोषणा UPROBE_SWBP_INSN_SIZE	4

काष्ठा arch_uprobe_task अणु
	u32 backup;
	अचिन्हित दीर्घ	saved_trap_no;
पूर्ण;

काष्ठा arch_uprobe अणु
	u8 insn[MAX_UINSN_BYTES];
	अचिन्हित दीर्घ ixol[2];
	uprobe_opcode_t bpinsn;
	bool simulate;
	u32 pcreg;
	व्योम (*prehandler)(काष्ठा arch_uprobe *auprobe,
			   काष्ठा arch_uprobe_task *autask,
			   काष्ठा pt_regs *regs);
	व्योम (*posthandler)(काष्ठा arch_uprobe *auprobe,
			    काष्ठा arch_uprobe_task *autask,
			    काष्ठा pt_regs *regs);
	काष्ठा arch_probes_insn asi;
पूर्ण;

#पूर्ण_अगर
