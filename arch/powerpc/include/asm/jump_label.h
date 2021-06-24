<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_JUMP_LABEL_H
#घोषणा _ASM_POWERPC_JUMP_LABEL_H

/*
 * Copyright 2010 Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

#समावेश <यंत्र/feature-fixups.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

#घोषणा JUMP_ENTRY_TYPE		stringअगरy_in_c(FTR_ENTRY_LONG)
#घोषणा JUMP_LABEL_NOP_SIZE	4

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
		 "nop # arch_static_branch\n\t"
		 ".pushsection __jump_table,  \"aw\"\n\t"
		 ".long 1b - ., %l[l_yes] - .\n\t"
		 JUMP_ENTRY_TYPE "%c0 - .\n\t"
		 ".popsection \n\t"
		 : :  "i" (&((अक्षर *)key)[branch]) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
		 "b %l[l_yes] # arch_static_branch_jump\n\t"
		 ".pushsection __jump_table,  \"aw\"\n\t"
		 ".long 1b - ., %l[l_yes] - .\n\t"
		 JUMP_ENTRY_TYPE "%c0 - .\n\t"
		 ".popsection \n\t"
		 : :  "i" (&((अक्षर *)key)[branch]) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

#अन्यथा
#घोषणा ARCH_STATIC_BRANCH(LABEL, KEY)		\
1098:	nop;					\
	.pushsection __jump_table, "aw";	\
	.दीर्घ 1098b - ., LABEL - .;		\
	FTR_ENTRY_LONG KEY - .;			\
	.popsection
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_JUMP_LABEL_H */
