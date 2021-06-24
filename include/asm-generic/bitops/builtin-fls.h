<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_BUILTIN_FLS_H_
#घोषणा _ASM_GENERIC_BITOPS_BUILTIN_FLS_H_

/**
 * fls - find last (most-signअगरicant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
अटल __always_अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	वापस x ? माप(x) * 8 - __builtin_clz(x) : 0;
पूर्ण

#पूर्ण_अगर
