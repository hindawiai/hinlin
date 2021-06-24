<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * This file provides wrappers with sanitizer instrumentation क्रम atomic bit
 * operations.
 *
 * To use this functionality, an arch's bitops.h file needs to define each of
 * the below bit operations with an arch_ prefix (e.g. arch_set_bit(),
 * arch___set_bit(), etc.).
 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_INSTRUMENTED_ATOMIC_H
#घोषणा _ASM_GENERIC_BITOPS_INSTRUMENTED_ATOMIC_H

#समावेश <linux/instrumented.h>

/**
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This is a relaxed atomic operation (no implied memory barriers).
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch_set_bit(nr, addr);
पूर्ण

/**
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * This is a relaxed atomic operation (no implied memory barriers).
 */
अटल अंतरभूत व्योम clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch_clear_bit(nr, addr);
पूर्ण

/**
 * change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * This is a relaxed atomic operation (no implied memory barriers).
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch_change_bit(nr, addr);
पूर्ण

/**
 * test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This is an atomic fully-ordered operation (implied full memory barrier).
 */
अटल अंतरभूत bool test_and_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_पढ़ो_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	वापस arch_test_and_set_bit(nr, addr);
पूर्ण

/**
 * test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This is an atomic fully-ordered operation (implied full memory barrier).
 */
अटल अंतरभूत bool test_and_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_पढ़ो_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	वापस arch_test_and_clear_bit(nr, addr);
पूर्ण

/**
 * test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This is an atomic fully-ordered operation (implied full memory barrier).
 */
अटल अंतरभूत bool test_and_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_पढ़ो_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	वापस arch_test_and_change_bit(nr, addr);
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H */
