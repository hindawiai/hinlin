<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 1995, Russell King.
 * Various bits and pieces copyrights include:
 *  Linus Torvalds (test_bit).
 * Big endian support: Copyright 2001, Nicolas Pitre
 *  reworked by rmk.
 *
 * bit 0 is the LSB of an "unsigned long" quantity.
 *
 * Please note that the code in this file should never be included
 * from user space.  Many of these are not implemented in assembler
 * since they would be too costly.  Also, they require privileged
 * inकाष्ठाions (which are not available from user mode) to ensure
 * that they are atomic.
 */

#अगर_अघोषित __ASM_ARM_BITOPS_H
#घोषणा __ASM_ARM_BITOPS_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/barrier.h>

/*
 * These functions are the basis of our bit ops.
 *
 * First, the atomic bitops. These use native endian.
 */
अटल अंतरभूत व्योम ____atomic_set_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask = BIT_MASK(bit);

	p += BIT_WORD(bit);

	raw_local_irq_save(flags);
	*p |= mask;
	raw_local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम ____atomic_clear_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask = BIT_MASK(bit);

	p += BIT_WORD(bit);

	raw_local_irq_save(flags);
	*p &= ~mask;
	raw_local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम ____atomic_change_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask = BIT_MASK(bit);

	p += BIT_WORD(bit);

	raw_local_irq_save(flags);
	*p ^= mask;
	raw_local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक
____atomic_test_and_set_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक res;
	अचिन्हित दीर्घ mask = BIT_MASK(bit);

	p += BIT_WORD(bit);

	raw_local_irq_save(flags);
	res = *p;
	*p = res | mask;
	raw_local_irq_restore(flags);

	वापस (res & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक
____atomic_test_and_clear_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक res;
	अचिन्हित दीर्घ mask = BIT_MASK(bit);

	p += BIT_WORD(bit);

	raw_local_irq_save(flags);
	res = *p;
	*p = res & ~mask;
	raw_local_irq_restore(flags);

	वापस (res & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक
____atomic_test_and_change_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक res;
	अचिन्हित दीर्घ mask = BIT_MASK(bit);

	p += BIT_WORD(bit);

	raw_local_irq_save(flags);
	res = *p;
	*p = res ^ mask;
	raw_local_irq_restore(flags);

	वापस (res & mask) != 0;
पूर्ण

#समावेश <यंत्र-generic/bitops/non-atomic.h>

/*
 *  A note about Endian-ness.
 *  -------------------------
 *
 * When the ARM is put पूर्णांकo big endian mode via CR15, the processor
 * merely swaps the order of bytes within words, thus:
 *
 *          ------------ physical data bus bits -----------
 *          D31 ... D24  D23 ... D16  D15 ... D8  D7 ... D0
 * little     byte 3       byte 2       byte 1      byte 0
 * big        byte 0       byte 1       byte 2      byte 3
 *
 * This means that पढ़ोing a 32-bit word at address 0 वापसs the same
 * value irrespective of the endian mode bit.
 *
 * Peripheral devices should be connected with the data bus reversed in
 * "Big Endian" mode.  ARM Application Note 61 is applicable, and is
 * available from http://www.arm.com/.
 *
 * The following assumes that the data bus connectivity क्रम big endian
 * mode has been followed.
 *
 * Note that bit 0 is defined to be 32-bit word bit 0, not byte 0 bit 0.
 */

/*
 * Native endian assembly bitops.  nr = 0 -> word 0 bit 0.
 */
बाह्य व्योम _set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * p);
बाह्य व्योम _clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * p);
बाह्य व्योम _change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * p);
बाह्य पूर्णांक _test_and_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * p);
बाह्य पूर्णांक _test_and_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * p);
बाह्य पूर्णांक _test_and_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * p);

/*
 * Little endian assembly bitops.  nr = 0 -> byte 0 bit 0.
 */
बाह्य पूर्णांक _find_first_zero_bit_le(स्थिर अचिन्हित दीर्घ *p, अचिन्हित size);
बाह्य पूर्णांक _find_next_zero_bit_le(स्थिर अचिन्हित दीर्घ *p, पूर्णांक size, पूर्णांक offset);
बाह्य पूर्णांक _find_first_bit_le(स्थिर अचिन्हित दीर्घ *p, अचिन्हित size);
बाह्य पूर्णांक _find_next_bit_le(स्थिर अचिन्हित दीर्घ *p, पूर्णांक size, पूर्णांक offset);

/*
 * Big endian assembly bitops.  nr = 0 -> byte 3 bit 0.
 */
बाह्य पूर्णांक _find_first_zero_bit_be(स्थिर अचिन्हित दीर्घ *p, अचिन्हित size);
बाह्य पूर्णांक _find_next_zero_bit_be(स्थिर अचिन्हित दीर्घ *p, पूर्णांक size, पूर्णांक offset);
बाह्य पूर्णांक _find_first_bit_be(स्थिर अचिन्हित दीर्घ *p, अचिन्हित size);
बाह्य पूर्णांक _find_next_bit_be(स्थिर अचिन्हित दीर्घ *p, पूर्णांक size, पूर्णांक offset);

#अगर_अघोषित CONFIG_SMP
/*
 * The __* क्रमm of bitops are non-atomic and may be reordered.
 */
#घोषणा ATOMIC_BITOP(name,nr,p)			\
	(__builtin_स्थिरant_p(nr) ? ____atomic_##name(nr, p) : _##name(nr,p))
#अन्यथा
#घोषणा ATOMIC_BITOP(name,nr,p)		_##name(nr,p)
#पूर्ण_अगर

/*
 * Native endian atomic definitions.
 */
#घोषणा set_bit(nr,p)			ATOMIC_BITOP(set_bit,nr,p)
#घोषणा clear_bit(nr,p)			ATOMIC_BITOP(clear_bit,nr,p)
#घोषणा change_bit(nr,p)		ATOMIC_BITOP(change_bit,nr,p)
#घोषणा test_and_set_bit(nr,p)		ATOMIC_BITOP(test_and_set_bit,nr,p)
#घोषणा test_and_clear_bit(nr,p)	ATOMIC_BITOP(test_and_clear_bit,nr,p)
#घोषणा test_and_change_bit(nr,p)	ATOMIC_BITOP(test_and_change_bit,nr,p)

#अगर_अघोषित __ARMEB__
/*
 * These are the little endian, atomic definitions.
 */
#घोषणा find_first_zero_bit(p,sz)	_find_first_zero_bit_le(p,sz)
#घोषणा find_next_zero_bit(p,sz,off)	_find_next_zero_bit_le(p,sz,off)
#घोषणा find_first_bit(p,sz)		_find_first_bit_le(p,sz)
#घोषणा find_next_bit(p,sz,off)		_find_next_bit_le(p,sz,off)

#अन्यथा
/*
 * These are the big endian, atomic definitions.
 */
#घोषणा find_first_zero_bit(p,sz)	_find_first_zero_bit_be(p,sz)
#घोषणा find_next_zero_bit(p,sz,off)	_find_next_zero_bit_be(p,sz,off)
#घोषणा find_first_bit(p,sz)		_find_first_bit_be(p,sz)
#घोषणा find_next_bit(p,sz,off)		_find_next_bit_be(p,sz,off)

#पूर्ण_अगर

#अगर __LINUX_ARM_ARCH__ < 5

#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/__ffs.h>
#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/ffs.h>

#अन्यथा

/*
 * On ARMv5 and above, the gcc built-ins may rely on the clz inकाष्ठाion
 * and produce optimal अंतरभूतd code in all हालs. On ARMv7 it is even
 * better by also using the rbit inकाष्ठाion.
 */
#समावेश <यंत्र-generic/bitops/builtin-__fls.h>
#समावेश <यंत्र-generic/bitops/builtin-__ffs.h>
#समावेश <यंत्र-generic/bitops/builtin-fls.h>
#समावेश <यंत्र-generic/bitops/builtin-ffs.h>

#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/ffz.h>

#समावेश <यंत्र-generic/bitops/fls64.h>

#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>

#अगर_घोषित __ARMEB__

अटल अंतरभूत पूर्णांक find_first_zero_bit_le(स्थिर व्योम *p, अचिन्हित size)
अणु
	वापस _find_first_zero_bit_le(p, size);
पूर्ण
#घोषणा find_first_zero_bit_le find_first_zero_bit_le

अटल अंतरभूत पूर्णांक find_next_zero_bit_le(स्थिर व्योम *p, पूर्णांक size, पूर्णांक offset)
अणु
	वापस _find_next_zero_bit_le(p, size, offset);
पूर्ण
#घोषणा find_next_zero_bit_le find_next_zero_bit_le

अटल अंतरभूत पूर्णांक find_next_bit_le(स्थिर व्योम *p, पूर्णांक size, पूर्णांक offset)
अणु
	वापस _find_next_bit_le(p, size, offset);
पूर्ण
#घोषणा find_next_bit_le find_next_bit_le

#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/le.h>

/*
 * Ext2 is defined to use little-endian byte ordering.
 */
#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ARM_BITOPS_H */
