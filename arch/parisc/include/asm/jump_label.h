<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_JUMP_LABEL_H
#घोषणा _ASM_PARISC_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/assembly.h>

#घोषणा JUMP_LABEL_NOP_SIZE 4

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
		 "nop\n\t"
		 ".pushsection __jump_table,  \"aw\"\n\t"
		 ".word 1b - ., %l[l_yes] - .\n\t"
		 __stringअगरy(ASM_ULONG_INSN) " %c0 - .\n\t"
		 ".popsection\n\t"
		 : :  "i" (&((अक्षर *)key)[branch]) :  : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
		 "b,n %l[l_yes]\n\t"
		 ".pushsection __jump_table,  \"aw\"\n\t"
		 ".word 1b - ., %l[l_yes] - .\n\t"
		 __stringअगरy(ASM_ULONG_INSN) " %c0 - .\n\t"
		 ".popsection\n\t"
		 : :  "i" (&((अक्षर *)key)[branch]) :  : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर
