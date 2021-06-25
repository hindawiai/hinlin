<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_FFZ_H_
#घोषणा _ASM_GENERIC_BITOPS_FFZ_H_

/*
 * ffz - find first zero in word.
 * @word: The word to search
 *
 * Undefined अगर no zero exists, so code should check against ~0UL first.
 */
#घोषणा ffz(x)  __ffs(~(x))

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_FFZ_H_ */
