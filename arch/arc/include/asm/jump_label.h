<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARC_JUMP_LABEL_H
#घोषणा _ASM_ARC_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>

#घोषणा JUMP_LABEL_NOP_SIZE 4

/*
 * NOTE about '.balign 4':
 *
 * To make atomic update of patched inकाष्ठाion available we need to guarantee
 * that this inकाष्ठाion करोesn't cross L1 cache line boundary.
 *
 * As of today we simply align inकाष्ठाion which can be patched by 4 byte using
 * ".balign 4" directive. In that हाल patched inकाष्ठाion is aligned with one
 * 16-bit NOP_S अगर this is required.
 * However 'align by 4' directive is much stricter than it actually required.
 * It's enough that our 32-bit instruction don't cross L1 cache line boundary /
 * L1 I$ fetch block boundary which can be achieved by using
 * ".bundle_align_mode" assembler directive. That will save us from adding
 * useless NOP_S padding in most of the हालs.
 *
 * TODO: चयन to ".bundle_align_mode" directive using whin it will be
 * supported by ARC toolchain.
 */

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key,
					       bool branch)
अणु
	यंत्र_अस्थिर_जाओ(".balign "__stringअगरy(JUMP_LABEL_NOP_SIZE)"	\n"
		 "1:							\n"
		 "nop							\n"
		 ".pushsection __jump_table, \"aw\"			\n"
		 ".word 1b, %l[l_yes], %c0				\n"
		 ".popsection						\n"
		 : : "i" (&((अक्षर *)key)[branch]) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key,
						    bool branch)
अणु
	यंत्र_अस्थिर_जाओ(".balign "__stringअगरy(JUMP_LABEL_NOP_SIZE)"	\n"
		 "1:							\n"
		 "b %l[l_yes]						\n"
		 ".pushsection __jump_table, \"aw\"			\n"
		 ".word 1b, %l[l_yes], %c0				\n"
		 ".popsection						\n"
		 : : "i" (&((अक्षर *)key)[branch]) : : l_yes);

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
