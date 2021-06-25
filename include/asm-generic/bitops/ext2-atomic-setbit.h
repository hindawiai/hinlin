<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_EXT2_ATOMIC_SETBIT_H_
#घोषणा _ASM_GENERIC_BITOPS_EXT2_ATOMIC_SETBIT_H_

/*
 * Atomic bitops based version of ext2 atomic bitops
 */

#घोषणा ext2_set_bit_atomic(l, nr, addr)	test_and_set_bit_le(nr, addr)
#घोषणा ext2_clear_bit_atomic(l, nr, addr)	test_and_clear_bit_le(nr, addr)

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_EXT2_ATOMIC_SETBIT_H_ */
