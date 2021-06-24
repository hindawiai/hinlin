<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_JUMP_LABEL_H
#घोषणा _ASM_S390_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/stringअगरy.h>

#घोषणा JUMP_LABEL_NOP_SIZE 6
#घोषणा JUMP_LABEL_NOP_OFFSET 2

#अगर_घोषित CONFIG_CC_IS_CLANG
#घोषणा JUMP_LABEL_STATIC_KEY_CONSTRAINT "i"
#या_अगर __GNUC__ < 9
#घोषणा JUMP_LABEL_STATIC_KEY_CONSTRAINT "X"
#अन्यथा
#घोषणा JUMP_LABEL_STATIC_KEY_CONSTRAINT "jdd"
#पूर्ण_अगर

/*
 * We use a brcl 0,2 inकाष्ठाion क्रम jump labels at compile समय so it
 * can be easily distinguished from a hotpatch generated inकाष्ठाion.
 */
अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("0:	brcl	0,"__stringअगरy(JUMP_LABEL_NOP_OFFSET)"\n"
			  ".pushsection __jump_table,\"aw\"\n"
			  ".balign	8\n"
			  ".long	0b-.,%l[label]-.\n"
			  ".quad	%0+%1-.\n"
			  ".popsection\n"
			  : : JUMP_LABEL_STATIC_KEY_CONSTRAINT (key), "i" (branch) : : label);
	वापस false;
label:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("0:	brcl 15,%l[label]\n"
			  ".pushsection __jump_table,\"aw\"\n"
			  ".balign	8\n"
			  ".long	0b-.,%l[label]-.\n"
			  ".quad	%0+%1-.\n"
			  ".popsection\n"
			  : : JUMP_LABEL_STATIC_KEY_CONSTRAINT (key), "i" (branch) : : label);
	वापस false;
label:
	वापस true;
पूर्ण

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर
