<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * This file provides wrappers with sanitizer instrumentation क्रम bit
 * locking operations.
 *
 * To use this functionality, an arch's bitops.h file needs to define each of
 * the below bit operations with an arch_ prefix (e.g. arch_set_bit(),
 * arch___set_bit(), etc.).
 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_INSTRUMENTED_LOCK_H
#घोषणा _ASM_GENERIC_BITOPS_INSTRUMENTED_LOCK_H

#समावेश <linux/instrumented.h>

/**
 * clear_bit_unlock - Clear a bit in memory, क्रम unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This operation is atomic and provides release barrier semantics.
 */
अटल अंतरभूत व्योम clear_bit_unlock(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch_clear_bit_unlock(nr, addr);
पूर्ण

/**
 * __clear_bit_unlock - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * This is a non-atomic operation but implies a release barrier beक्रमe the
 * memory operation. It can be used क्रम an unlock अगर no other CPUs can
 * concurrently modअगरy other bits in the word.
 */
अटल अंतरभूत व्योम __clear_bit_unlock(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch___clear_bit_unlock(nr, addr);
पूर्ण

/**
 * test_and_set_bit_lock - Set a bit and वापस its old value, क्रम lock
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and provides acquire barrier semantics अगर
 * the वापसed value is 0.
 * It can be used to implement bit locks.
 */
अटल अंतरभूत bool test_and_set_bit_lock(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_पढ़ो_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	वापस arch_test_and_set_bit_lock(nr, addr);
पूर्ण

#अगर defined(arch_clear_bit_unlock_is_negative_byte)
/**
 * clear_bit_unlock_is_negative_byte - Clear a bit in memory and test अगर bottom
 *                                     byte is negative, क्रम unlock.
 * @nr: the bit to clear
 * @addr: the address to start counting from
 *
 * This operation is atomic and provides release barrier semantics.
 *
 * This is a bit of a one-trick-pony क्रम the filemap code, which clears
 * PG_locked and tests PG_रुकोers,
 */
अटल अंतरभूत bool
clear_bit_unlock_is_negative_byte(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	वापस arch_clear_bit_unlock_is_negative_byte(nr, addr);
पूर्ण
/* Let everybody know we have it. */
#घोषणा clear_bit_unlock_is_negative_byte clear_bit_unlock_is_negative_byte
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_INSTRUMENTED_LOCK_H */
