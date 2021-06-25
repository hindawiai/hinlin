<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Emil Renner Berthing
 *
 * Based on arch/arm64/kernel/jump_label.c
 */
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memory.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/patch.h>

#घोषणा RISCV_INSN_NOP 0x00000013U
#घोषणा RISCV_INSN_JAL 0x0000006fU

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	व्योम *addr = (व्योम *)jump_entry_code(entry);
	u32 insn;

	अगर (type == JUMP_LABEL_JMP) अणु
		दीर्घ offset = jump_entry_target(entry) - jump_entry_code(entry);

		अगर (WARN_ON(offset & 1 || offset < -524288 || offset >= 524288))
			वापस;

		insn = RISCV_INSN_JAL |
			(((u32)offset & GENMASK(19, 12)) << (12 - 12)) |
			(((u32)offset & GENMASK(11, 11)) << (20 - 11)) |
			(((u32)offset & GENMASK(10,  1)) << (21 -  1)) |
			(((u32)offset & GENMASK(20, 20)) << (31 - 20));
	पूर्ण अन्यथा अणु
		insn = RISCV_INSN_NOP;
	पूर्ण

	mutex_lock(&text_mutex);
	patch_text_nosync(addr, &insn, माप(insn));
	mutex_unlock(&text_mutex);
पूर्ण

व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	/*
	 * We use the same inकाष्ठाions in the arch_अटल_branch and
	 * arch_अटल_branch_jump अंतरभूत functions, so there's no
	 * need to patch them up here.
	 * The core will call arch_jump_label_transक्रमm  when those
	 * inकाष्ठाions need to be replaced.
	 */
पूर्ण
