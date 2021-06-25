<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_BUILTIN___FLS_H_
#घोषणा _ASM_GENERIC_BITOPS_BUILTIN___FLS_H_

/**
 * __fls - find last (most-signअगरicant) set bit in a दीर्घ word
 * @word: the word to search
 *
 * Undefined अगर no set bit exists, so code should check against 0 first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	वापस (माप(word) * 8) - 1 - __builtin_clzl(word);
पूर्ण

#पूर्ण_अगर
