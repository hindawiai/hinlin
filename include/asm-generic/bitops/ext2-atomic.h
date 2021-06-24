<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_EXT2_ATOMIC_H_
#घोषणा _ASM_GENERIC_BITOPS_EXT2_ATOMIC_H_

/*
 * Spinlock based version of ext2 atomic bitops
 */

#घोषणा ext2_set_bit_atomic(lock, nr, addr)		\
	(अणु						\
		पूर्णांक ret;				\
		spin_lock(lock);			\
		ret = __test_and_set_bit_le(nr, addr);	\
		spin_unlock(lock);			\
		ret;					\
	पूर्ण)

#घोषणा ext2_clear_bit_atomic(lock, nr, addr)		\
	(अणु						\
		पूर्णांक ret;				\
		spin_lock(lock);			\
		ret = __test_and_clear_bit_le(nr, addr);	\
		spin_unlock(lock);			\
		ret;					\
	पूर्ण)

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_EXT2_ATOMIC_H_ */
