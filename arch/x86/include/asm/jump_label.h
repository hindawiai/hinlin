<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_JUMP_LABEL_H
#घोषणा _ASM_X86_JUMP_LABEL_H

#घोषणा HAVE_JUMP_LABEL_BATCH

#घोषणा JUMP_LABEL_NOP_SIZE 5

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/nops.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key * स्थिर key, स्थिर bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:"
		".byte " __stringअगरy(BYTES_NOP5) "\n\t"
		".pushsection __jump_table,  \"aw\" \n\t"
		_ASM_ALIGN "\n\t"
		".long 1b - ., %l[l_yes] - . \n\t"
		_ASM_PTR "%c0 + %c1 - .\n\t"
		".popsection \n\t"
		: :  "i" (key), "i" (branch) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key * स्थिर key, स्थिर bool branch)
अणु
	यंत्र_अस्थिर_जाओ("1:"
		".byte 0xe9\n\t .long %l[l_yes] - 2f\n\t"
		"2:\n\t"
		".pushsection __jump_table,  \"aw\" \n\t"
		_ASM_ALIGN "\n\t"
		".long 1b - ., %l[l_yes] - . \n\t"
		_ASM_PTR "%c0 + %c1 - .\n\t"
		".popsection \n\t"
		: :  "i" (key), "i" (branch) : : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

#अन्यथा	/* __ASSEMBLY__ */

.macro STATIC_JUMP_IF_TRUE target, key, def
.Lअटल_jump_\@:
	.अगर \def
	/* Equivalent to "jmp.d32 \target" */
	.byte		0xe9
	.दीर्घ		\टarget - .Lअटल_jump_after_\@
.Lअटल_jump_after_\@:
	.अन्यथा
	.byte		BYTES_NOP5
	.endअगर
	.pushsection __jump_table, "aw"
	_ASM_ALIGN
	.दीर्घ		.Lअटल_jump_\@ - ., \टarget - .
	_ASM_PTR	\key - .
	.popsection
.endm

.macro STATIC_JUMP_IF_FALSE target, key, def
.Lअटल_jump_\@:
	.अगर \def
	.byte		BYTES_NOP5
	.अन्यथा
	/* Equivalent to "jmp.d32 \target" */
	.byte		0xe9
	.दीर्घ		\टarget - .Lअटल_jump_after_\@
.Lअटल_jump_after_\@:
	.endअगर
	.pushsection __jump_table, "aw"
	_ASM_ALIGN
	.दीर्घ		.Lअटल_jump_\@ - ., \टarget - .
	_ASM_PTR	\key + 1 - .
	.popsection
.endm

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर
