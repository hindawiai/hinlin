<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Cadence Design Systems Inc. */

#अगर_अघोषित _ASM_XTENSA_JUMP_LABEL_H
#घोषणा _ASM_XTENSA_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

#घोषणा JUMP_LABEL_NOP_SIZE 3

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key,
					       bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
			  "_nop\n\t"
			  ".pushsection __jump_table,  \"aw\"\n\t"
			  ".word 1b, %l[l_yes], %c0\n\t"
			  ".popsection\n\t"
			  : :  "i" (&((अक्षर *)key)[branch]) :  : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key,
						    bool branch)
अणु
	/*
	 * Xtensa assembler will mark certain poपूर्णांकs in the code
	 * as unreachable, so that later assembler or linker relaxation
	 * passes could use them. A spot right after the J inकाष्ठाion
	 * is one such poपूर्णांक. Assembler and/or linker may insert padding
	 * or literals here, अवरोधing code flow in हाल the J inकाष्ठाion
	 * is later replaced with NOP. Put a label right after the J to
	 * make it reachable and wrap both पूर्णांकo a no-transक्रमm block
	 * to aव्योम any assembler पूर्णांकerference with this.
	 */
	यंत्र_अस्थिर_जाओ("1:\n\t"
			  ".begin no-transform\n\t"
			  "_j %l[l_yes]\n\t"
			  "2:\n\t"
			  ".end no-transform\n\t"
			  ".pushsection __jump_table,  \"aw\"\n\t"
			  ".word 1b, %l[l_yes], %c0\n\t"
			  ".popsection\n\t"
			  : :  "i" (&((अक्षर *)key)[branch]) :  : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

प्रकार u32 jump_label_t;

काष्ठा jump_entry अणु
	jump_label_t code;
	jump_label_t target;
	jump_label_t key;
पूर्ण;

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर
