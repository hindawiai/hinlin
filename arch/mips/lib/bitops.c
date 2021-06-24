<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1994-1997, 99, 2000, 06, 07 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (c) 1999, 2000  Silicon Graphics, Inc.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/bits.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/export.h>


/**
 * __mips_set_bit - Atomically set a bit in memory.  This is called by
 * set_bit() अगर it cannot find a faster solution.
 * @nr: the bit to set
 * @addr: the address to start counting from
 */
व्योम __mips_set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *a = &addr[BIT_WORD(nr)];
	अचिन्हित पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ flags;

	mask = 1UL << bit;
	raw_local_irq_save(flags);
	*a |= mask;
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(__mips_set_bit);


/**
 * __mips_clear_bit - Clears a bit in memory.  This is called by clear_bit() अगर
 * it cannot find a faster solution.
 * @nr: Bit to clear
 * @addr: Address to start counting from
 */
व्योम __mips_clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *a = &addr[BIT_WORD(nr)];
	अचिन्हित पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ flags;

	mask = 1UL << bit;
	raw_local_irq_save(flags);
	*a &= ~mask;
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(__mips_clear_bit);


/**
 * __mips_change_bit - Toggle a bit in memory.	This is called by change_bit()
 * अगर it cannot find a faster solution.
 * @nr: Bit to change
 * @addr: Address to start counting from
 */
व्योम __mips_change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *a = &addr[BIT_WORD(nr)];
	अचिन्हित पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ flags;

	mask = 1UL << bit;
	raw_local_irq_save(flags);
	*a ^= mask;
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(__mips_change_bit);


/**
 * __mips_test_and_set_bit_lock - Set a bit and वापस its old value.  This is
 * called by test_and_set_bit_lock() अगर it cannot find a faster solution.
 * @nr: Bit to set
 * @addr: Address to count from
 */
पूर्णांक __mips_test_and_set_bit_lock(अचिन्हित दीर्घ nr,
				 अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *a = &addr[BIT_WORD(nr)];
	अचिन्हित पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a) != 0;
	*a |= mask;
	raw_local_irq_restore(flags);
	वापस res;
पूर्ण
EXPORT_SYMBOL(__mips_test_and_set_bit_lock);


/**
 * __mips_test_and_clear_bit - Clear a bit and वापस its old value.  This is
 * called by test_and_clear_bit() अगर it cannot find a faster solution.
 * @nr: Bit to clear
 * @addr: Address to count from
 */
पूर्णांक __mips_test_and_clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *a = &addr[BIT_WORD(nr)];
	अचिन्हित पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a) != 0;
	*a &= ~mask;
	raw_local_irq_restore(flags);
	वापस res;
पूर्ण
EXPORT_SYMBOL(__mips_test_and_clear_bit);


/**
 * __mips_test_and_change_bit - Change a bit and वापस its old value.	This is
 * called by test_and_change_bit() अगर it cannot find a faster solution.
 * @nr: Bit to change
 * @addr: Address to count from
 */
पूर्णांक __mips_test_and_change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *a = &addr[BIT_WORD(nr)];
	अचिन्हित पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a) != 0;
	*a ^= mask;
	raw_local_irq_restore(flags);
	वापस res;
पूर्ण
EXPORT_SYMBOL(__mips_test_and_change_bit);
