<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SPARC_JUMP_LABEL_H
#घोषणा _ASM_SPARC_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

#घोषणा JUMP_LABEL_NOP_SIZE 4

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
		 "nop\n\t"
		 "nop\n\t"
		 ".pushsection __jump_table,  \"aw\"\n\t"
		 ".align 4\n\t"
		 ".word 1b, %l[l_yes], %c0\n\t"
		 ".popsection \n\t"
		 : :  "i" (&((अक्षर *)key)[branch]) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\n\t"
		 "b %l[l_yes]\n\t"
		 "nop\n\t"
		 ".pushsection __jump_table,  \"aw\"\n\t"
		 ".align 4\n\t"
		 ".word 1b, %l[l_yes], %c0\n\t"
		 ".popsection \n\t"
		 : :  "i" (&((अक्षर *)key)[branch]) : : l_yes);

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
