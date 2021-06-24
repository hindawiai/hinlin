<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2010 Michael Ellerman, IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/inst.h>

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	काष्ठा ppc_inst *addr = (काष्ठा ppc_inst *)jump_entry_code(entry);

	अगर (type == JUMP_LABEL_JMP)
		patch_branch(addr, jump_entry_target(entry), 0);
	अन्यथा
		patch_inकाष्ठाion(addr, ppc_inst(PPC_INST_NOP));
पूर्ण
