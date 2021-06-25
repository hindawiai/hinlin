<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2010 Cavium Networks, Inc.
 */
#अगर_अघोषित _ASM_MIPS_JUMP_LABEL_H
#घोषणा _ASM_MIPS_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/isa-rev.h>

#घोषणा JUMP_LABEL_NOP_SIZE 4

#अगर_घोषित CONFIG_64BIT
#घोषणा WORD_INSN ".dword"
#अन्यथा
#घोषणा WORD_INSN ".word"
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_MICROMIPS
# define B_INSN "b32"
# define J_INSN "j32"
#या_अगर MIPS_ISA_REV >= 6
# define B_INSN "bc"
# define J_INSN "bc"
#अन्यथा
# define B_INSN "b"
# define J_INSN "j"
#पूर्ण_अगर

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\t" B_INSN " 2f\n\t"
		"2:\t.insn\n\t"
		".pushsection __jump_table,  \"aw\"\n\t"
		WORD_INSN " 1b, %l[l_yes], %0\n\t"
		".popsection\n\t"
		: :  "i" (&((अक्षर *)key)[branch]) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key, bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:\t" J_INSN " %l[l_yes]\n\t"
		".pushsection __jump_table,  \"aw\"\n\t"
		WORD_INSN " 1b, %l[l_yes], %0\n\t"
		".popsection\n\t"
		: :  "i" (&((अक्षर *)key)[branch]) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_64BIT
प्रकार u64 jump_label_t;
#अन्यथा
प्रकार u32 jump_label_t;
#पूर्ण_अगर

काष्ठा jump_entry अणु
	jump_label_t code;
	jump_label_t target;
	jump_label_t key;
पूर्ण;

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_MIPS_JUMP_LABEL_H */
