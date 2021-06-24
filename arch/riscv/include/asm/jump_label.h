<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Emil Renner Berthing
 *
 * Based on arch/arm64/include/यंत्र/jump_label.h
 */
#अगर_अघोषित __ASM_JUMP_LABEL_H
#घोषणा __ASM_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/यंत्र.h>

#घोषणा JUMP_LABEL_NOP_SIZE 4

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key,
					       bool branch)
अणु
	यंत्र_अस्थिर_जाओ(
		"	.option push				\n\t"
		"	.option norelax				\n\t"
		"	.option norvc				\n\t"
		"1:	nop					\n\t"
		"	.option pop				\n\t"
		"	.pushsection	__jump_table, \"aw\"	\n\t"
		"	.align		" RISCV_LGPTR "		\n\t"
		"	.long		1b - ., %l[label] - .	\n\t"
		"	" RISCV_PTR "	%0 - .			\n\t"
		"	.popsection				\n\t"
		:  :  "i"(&((अक्षर *)key)[branch]) :  : label);

	वापस false;
label:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key,
						    bool branch)
अणु
	यंत्र_अस्थिर_जाओ(
		"	.option push				\n\t"
		"	.option norelax				\n\t"
		"	.option norvc				\n\t"
		"1:	jal		zero, %l[label]		\n\t"
		"	.option pop				\n\t"
		"	.pushsection	__jump_table, \"aw\"	\n\t"
		"	.align		" RISCV_LGPTR "		\n\t"
		"	.long		1b - ., %l[label] - .	\n\t"
		"	" RISCV_PTR "	%0 - .			\n\t"
		"	.popsection				\n\t"
		:  :  "i"(&((अक्षर *)key)[branch]) :  : label);

	वापस false;
label:
	वापस true;
पूर्ण

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर	/* __ASM_JUMP_LABEL_H */
