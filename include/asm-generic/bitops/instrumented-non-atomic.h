<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * This file provides wrappers with sanitizer instrumentation क्रम non-atomic
 * bit operations.
 *
 * To use this functionality, an arch's bitops.h file needs to define each of
 * the below bit operations with an arch_ prefix (e.g. arch_set_bit(),
 * arch___set_bit(), etc.).
 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H
#घोषणा _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H

#समावेश <linux/instrumented.h>

/**
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic. If it is called on the same
 * region of memory concurrently, the effect may be that only one operation
 * succeeds.
 */
अटल अंतरभूत व्योम __set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch___set_bit(nr, addr);
पूर्ण

/**
 * __clear_bit - Clears a bit in memory
 * @nr: the bit to clear
 * @addr: the address to start counting from
 *
 * Unlike clear_bit(), this function is non-atomic. If it is called on the same
 * region of memory concurrently, the effect may be that only one operation
 * succeeds.
 */
अटल अंतरभूत व्योम __clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch___clear_bit(nr, addr);
पूर्ण

/**
 * __change_bit - Toggle a bit in memory
 * @nr: the bit to change
 * @addr: the address to start counting from
 *
 * Unlike change_bit(), this function is non-atomic. If it is called on the same
 * region of memory concurrently, the effect may be that only one operation
 * succeeds.
 */
अटल अंतरभूत व्योम __change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	arch___change_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम __instrument_पढ़ो_ग_लिखो_bitop(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अगर (IS_ENABLED(CONFIG_KCSAN_ASSUME_PLAIN_WRITES_ATOMIC)) अणु
		/*
		 * We treat non-atomic पढ़ो-ग_लिखो bitops a little more special.
		 * Given the operations here only modअगरy a single bit, assuming
		 * non-atomicity of the ग_लिखोr is sufficient may be reasonable
		 * क्रम certain usage (and follows the permissible nature of the
		 * assume-plain-ग_लिखोs-atomic rule):
		 * 1. report पढ़ो-modअगरy-ग_लिखो races -> check पढ़ो;
		 * 2. करो not report races with marked पढ़ोers, but करो report
		 *    races with unmarked पढ़ोers -> check "atomic" ग_लिखो.
		 */
		kcsan_check_पढ़ो(addr + BIT_WORD(nr), माप(दीर्घ));
		/*
		 * Use generic ग_लिखो instrumentation, in हाल other sanitizers
		 * or tools are enabled aदीर्घside KCSAN.
		 */
		instrument_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	पूर्ण अन्यथा अणु
		instrument_पढ़ो_ग_लिखो(addr + BIT_WORD(nr), माप(दीर्घ));
	पूर्ण
पूर्ण

/**
 * __test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic. If two instances of this operation race, one
 * can appear to succeed but actually fail.
 */
अटल अंतरभूत bool __test_and_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__instrument_पढ़ो_ग_लिखो_bitop(nr, addr);
	वापस arch___test_and_set_bit(nr, addr);
पूर्ण

/**
 * __test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is non-atomic. If two instances of this operation race, one
 * can appear to succeed but actually fail.
 */
अटल अंतरभूत bool __test_and_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__instrument_पढ़ो_ग_लिखो_bitop(nr, addr);
	वापस arch___test_and_clear_bit(nr, addr);
पूर्ण

/**
 * __test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is non-atomic. If two instances of this operation race, one
 * can appear to succeed but actually fail.
 */
अटल अंतरभूत bool __test_and_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__instrument_पढ़ो_ग_लिखो_bitop(nr, addr);
	वापस arch___test_and_change_bit(nr, addr);
पूर्ण

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
अटल अंतरभूत bool test_bit(दीर्घ nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	instrument_atomic_पढ़ो(addr + BIT_WORD(nr), माप(दीर्घ));
	वापस arch_test_bit(nr, addr);
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_INSTRUMENTED_NON_ATOMIC_H */
