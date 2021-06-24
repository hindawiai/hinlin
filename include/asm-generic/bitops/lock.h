<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_LOCK_H_
#घोषणा _ASM_GENERIC_BITOPS_LOCK_H_

#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>

/**
 * test_and_set_bit_lock - Set a bit and वापस its old value, क्रम lock
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and provides acquire barrier semantics अगर
 * the वापसed value is 0.
 * It can be used to implement bit locks.
 */
अटल अंतरभूत पूर्णांक test_and_set_bit_lock(अचिन्हित पूर्णांक nr,
					अस्थिर अचिन्हित दीर्घ *p)
अणु
	दीर्घ old;
	अचिन्हित दीर्घ mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	अगर (READ_ONCE(*p) & mask)
		वापस 1;

	old = atomic_दीर्घ_fetch_or_acquire(mask, (atomic_दीर्घ_t *)p);
	वापस !!(old & mask);
पूर्ण


/**
 * clear_bit_unlock - Clear a bit in memory, क्रम unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This operation is atomic and provides release barrier semantics.
 */
अटल अंतरभूत व्योम clear_bit_unlock(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	p += BIT_WORD(nr);
	atomic_दीर्घ_fetch_andnot_release(BIT_MASK(nr), (atomic_दीर्घ_t *)p);
पूर्ण

/**
 * __clear_bit_unlock - Clear a bit in memory, क्रम unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * A weaker क्रमm of clear_bit_unlock() as used by __bit_lock_unlock(). If all
 * the bits in the word are रक्षित by this lock some archs can use weaker
 * ops to safely unlock.
 *
 * See क्रम example x86's implementation.
 */
अटल अंतरभूत व्योम __clear_bit_unlock(अचिन्हित पूर्णांक nr,
				      अस्थिर अचिन्हित दीर्घ *p)
अणु
	अचिन्हित दीर्घ old;

	p += BIT_WORD(nr);
	old = READ_ONCE(*p);
	old &= ~BIT_MASK(nr);
	atomic_दीर्घ_set_release((atomic_दीर्घ_t *)p, old);
पूर्ण

/**
 * clear_bit_unlock_is_negative_byte - Clear a bit in memory and test अगर bottom
 *                                     byte is negative, क्रम unlock.
 * @nr: the bit to clear
 * @addr: the address to start counting from
 *
 * This is a bit of a one-trick-pony क्रम the filemap code, which clears
 * PG_locked and tests PG_रुकोers,
 */
#अगर_अघोषित clear_bit_unlock_is_negative_byte
अटल अंतरभूत bool clear_bit_unlock_is_negative_byte(अचिन्हित पूर्णांक nr,
						     अस्थिर अचिन्हित दीर्घ *p)
अणु
	दीर्घ old;
	अचिन्हित दीर्घ mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	old = atomic_दीर्घ_fetch_andnot_release(mask, (atomic_दीर्घ_t *)p);
	वापस !!(old & BIT(7));
पूर्ण
#घोषणा clear_bit_unlock_is_negative_byte clear_bit_unlock_is_negative_byte
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_LOCK_H_ */
