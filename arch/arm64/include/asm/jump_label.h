<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Huawei Ltd.
 * Author: Jiang Liu <liuj97@gmail.com>
 *
 * Based on arch/arm/include/यंत्र/jump_label.h
 */
#अगर_अघोषित __ASM_JUMP_LABEL_H
#घोषणा __ASM_JUMP_LABEL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/insn.h>

#घोषणा JUMP_LABEL_NOP_SIZE		AARCH64_INSN_SIZE

अटल __always_अंतरभूत bool arch_अटल_branch(काष्ठा अटल_key *key,
					       bool branch)
अणु
	यंत्र_अस्थिर_जाओ(
		"1:	nop					\n\t"
		 "	.pushsection	__jump_table, \"aw\"	\n\t"
		 "	.align		3			\n\t"
		 "	.long		1b - ., %l[l_yes] - .	\n\t"
		 "	.quad		%c0 - .			\n\t"
		 "	.popsection				\n\t"
		 :  :  "i"(&((अक्षर *)key)[branch]) :  : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool arch_अटल_branch_jump(काष्ठा अटल_key *key,
						    bool branch)
अणु
	यंत्र_अस्थिर_जाओ(
		"1:	b		%l[l_yes]		\n\t"
		 "	.pushsection	__jump_table, \"aw\"	\n\t"
		 "	.align		3			\n\t"
		 "	.long		1b - ., %l[l_yes] - .	\n\t"
		 "	.quad		%c0 - .			\n\t"
		 "	.popsection				\n\t"
		 :  :  "i"(&((अक्षर *)key)[branch]) :  : l_yes);

	वापस false;
l_yes:
	वापस true;
पूर्ण

#पूर्ण_अगर  /* __ASSEMBLY__ */
#पूर्ण_अगर	/* __ASM_JUMP_LABEL_H */
