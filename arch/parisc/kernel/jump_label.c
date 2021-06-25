<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Helge Deller <deller@gmx.de>
 *
 * Based on arch/arm64/kernel/jump_label.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/patch.h>

अटल अंतरभूत पूर्णांक reassemble_17(पूर्णांक as17)
अणु
	वापस (((as17 & 0x10000) >> 16) |
		((as17 & 0x0f800) << 5) |
		((as17 & 0x00400) >> 8) |
		((as17 & 0x003ff) << 3));
पूर्ण

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	व्योम *addr = (व्योम *)jump_entry_code(entry);
	u32 insn;

	अगर (type == JUMP_LABEL_JMP) अणु
		व्योम *target = (व्योम *)jump_entry_target(entry);
		पूर्णांक distance = target - addr;
		/*
		 * Encode the PA1.1 "b,n" inकाष्ठाion with a 17-bit
		 * displacement.  In हाल we hit the BUG(), we could use
		 * another branch inकाष्ठाion with a 22-bit displacement on
		 * 64-bit CPUs instead. But this seems sufficient क्रम now.
		 */
		distance -= 8;
		BUG_ON(distance > 262143 || distance < -262144);
		insn = 0xe8000002 | reassemble_17(distance >> 2);
	पूर्ण अन्यथा अणु
		insn = INSN_NOP;
	पूर्ण

	patch_text(addr, insn);
पूर्ण

व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	/*
	 * We use the architected NOP in arch_अटल_branch, so there's no
	 * need to patch an identical NOP over the top of it here. The core
	 * will call arch_jump_label_transक्रमm from a module notअगरier अगर the
	 * NOP needs to be replaced by a branch.
	 */
पूर्ण
