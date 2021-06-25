<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SYNC_BITOPS_H
#घोषणा _ASM_X86_SYNC_BITOPS_H

/*
 * Copyright 1992, Linus Torvalds.
 */

/*
 * These have to be करोne with अंतरभूत assembly: that way the bit-setting
 * is guaranteed to be atomic. All bit operations वापस 0 अगर the bit
 * was cleared beक्रमe the operation and != 0 अगर it was not.
 *
 * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).
 */

#समावेश <यंत्र/rmwcc.h>

#घोषणा ADDR (*(अस्थिर दीर्घ *)addr)

/**
 * sync_set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * अगर you करो not require the atomic guarantees.
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम sync_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	यंत्र अस्थिर("lock; " __ASM_SIZE(bts) " %1,%0"
		     : "+m" (ADDR)
		     : "Ir" (nr)
		     : "memory");
पूर्ण

/**
 * sync_clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * sync_clear_bit() is atomic and may not be reordered.  However, it करोes
 * not contain a memory barrier, so अगर it is used क्रम locking purposes,
 * you should call smp_mb__beक्रमe_atomic() and/or smp_mb__after_atomic()
 * in order to ensure changes are visible on other processors.
 */
अटल अंतरभूत व्योम sync_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	यंत्र अस्थिर("lock; " __ASM_SIZE(btr) " %1,%0"
		     : "+m" (ADDR)
		     : "Ir" (nr)
		     : "memory");
पूर्ण

/**
 * sync_change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * sync_change_bit() is atomic and may not be reordered.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम sync_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	यंत्र अस्थिर("lock; " __ASM_SIZE(btc) " %1,%0"
		     : "+m" (ADDR)
		     : "Ir" (nr)
		     : "memory");
पूर्ण

/**
 * sync_test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत bool sync_test_and_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस GEN_BINARY_RMWcc("lock; " __ASM_SIZE(bts), *addr, c, "Ir", nr);
पूर्ण

/**
 * sync_test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत पूर्णांक sync_test_and_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस GEN_BINARY_RMWcc("lock; " __ASM_SIZE(btr), *addr, c, "Ir", nr);
पूर्ण

/**
 * sync_test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत पूर्णांक sync_test_and_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस GEN_BINARY_RMWcc("lock; " __ASM_SIZE(btc), *addr, c, "Ir", nr);
पूर्ण

#घोषणा sync_test_bit(nr, addr) test_bit(nr, addr)

#अघोषित ADDR

#पूर्ण_अगर /* _ASM_X86_SYNC_BITOPS_H */
