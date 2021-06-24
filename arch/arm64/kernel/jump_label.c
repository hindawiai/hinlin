<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Huawei Ltd.
 * Author: Jiang Liu <liuj97@gmail.com>
 *
 * Based on arch/arm/kernel/jump_label.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/insn.h>

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	व्योम *addr = (व्योम *)jump_entry_code(entry);
	u32 insn;

	अगर (type == JUMP_LABEL_JMP) अणु
		insn = aarch64_insn_gen_branch_imm(jump_entry_code(entry),
						   jump_entry_target(entry),
						   AARCH64_INSN_BRANCH_NOLINK);
	पूर्ण अन्यथा अणु
		insn = aarch64_insn_gen_nop();
	पूर्ण

	aarch64_insn_patch_text_nosync(addr, insn);
पूर्ण

व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	/*
	 * We use the architected A64 NOP in arch_अटल_branch, so there's no
	 * need to patch an identical A64 NOP over the top of it here. The core
	 * will call arch_jump_label_transक्रमm from a module notअगरier अगर the
	 * NOP needs to be replaced by a branch.
	 */
पूर्ण
