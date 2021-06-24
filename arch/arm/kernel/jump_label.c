<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/insn.h>

अटल व्योम __arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
					क्रमागत jump_label_type type,
					bool is_अटल)
अणु
	व्योम *addr = (व्योम *)entry->code;
	अचिन्हित पूर्णांक insn;

	अगर (type == JUMP_LABEL_JMP)
		insn = arm_gen_branch(entry->code, entry->target);
	अन्यथा
		insn = arm_gen_nop();

	अगर (is_अटल)
		__patch_text_early(addr, insn);
	अन्यथा
		patch_text(addr, insn);
पूर्ण

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	__arch_jump_label_transक्रमm(entry, type, false);
पूर्ण

व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	__arch_jump_label_transक्रमm(entry, type, true);
पूर्ण
