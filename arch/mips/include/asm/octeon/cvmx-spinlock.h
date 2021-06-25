<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/**
 * Implementation of spinlocks क्रम Octeon CVMX.	 Although similar in
 * function to Linux kernel spinlocks, they are not compatible.
 * Octeon CVMX spinlocks are only used to synchronize with the boot
 * monitor and other non-Linux programs running in the प्रणाली.
 */

#अगर_अघोषित __CVMX_SPINLOCK_H__
#घोषणा __CVMX_SPINLOCK_H__

#समावेश <यंत्र/octeon/cvmx-यंत्र.h>

/* Spinlocks क्रम Octeon */

/* define these to enable recursive spinlock debugging */
/*#घोषणा CVMX_SPINLOCK_DEBUG */

/**
 * Spinlocks क्रम Octeon CVMX
 */
प्रकार काष्ठा अणु
	अस्थिर uपूर्णांक32_t value;
पूर्ण cvmx_spinlock_t;

/* note - macros not expanded in अंतरभूत ASM, so values hardcoded */
#घोषणा	 CVMX_SPINLOCK_UNLOCKED_VAL  0
#घोषणा	 CVMX_SPINLOCK_LOCKED_VAL    1

#घोषणा CVMX_SPINLOCK_UNLOCKED_INITIALIZER  अणुCVMX_SPINLOCK_UNLOCKED_VALपूर्ण

/**
 * Initialize a spinlock
 *
 * @lock:   Lock to initialize
 */
अटल अंतरभूत व्योम cvmx_spinlock_init(cvmx_spinlock_t *lock)
अणु
	lock->value = CVMX_SPINLOCK_UNLOCKED_VAL;
पूर्ण

/**
 * Return non-zero अगर the spinlock is currently locked
 *
 * @lock:   Lock to check
 * Returns Non-zero अगर locked
 */
अटल अंतरभूत पूर्णांक cvmx_spinlock_locked(cvmx_spinlock_t *lock)
अणु
	वापस lock->value != CVMX_SPINLOCK_UNLOCKED_VAL;
पूर्ण

/**
 * Releases lock
 *
 * @lock:   poपूर्णांकer to lock काष्ठाure
 */
अटल अंतरभूत व्योम cvmx_spinlock_unlock(cvmx_spinlock_t *lock)
अणु
	CVMX_SYNCWS;
	lock->value = 0;
	CVMX_SYNCWS;
पूर्ण

/**
 * Attempts to take the lock, but करोes not spin अगर lock is not available.
 * May take some समय to acquire the lock even अगर it is available
 * due to the ll/sc not succeeding.
 *
 * @lock:   poपूर्णांकer to lock काष्ठाure
 *
 * Returns 0: lock successfully taken
 *	   1: lock not taken, held by someone अन्यथा
 * These वापस values match the Linux semantics.
 */

अटल अंतरभूत अचिन्हित पूर्णांक cvmx_spinlock_trylock(cvmx_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(".set noreorder	     \n"
			     "1: ll   %[tmp], %[val] \n"
			/* अगर lock held, fail immediately */
			     "	 bnez %[tmp], 2f     \n"
			     "	 li   %[tmp], 1	     \n"
			     "	 sc   %[tmp], %[val] \n"
			     "	 beqz %[tmp], 1b     \n"
			     "	 li   %[tmp], 0	     \n"
			     "2:		     \n"
			     ".set reorder	     \n" :
			[val] "+m"(lock->value), [पंचांगp] "=&r"(पंचांगp)
			     : : "memory");

	वापस पंचांगp != 0;		/* normalize to 0 or 1 */
पूर्ण

/**
 * Gets lock, spins until lock is taken
 *
 * @lock:   poपूर्णांकer to lock काष्ठाure
 */
अटल अंतरभूत व्योम cvmx_spinlock_lock(cvmx_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(".set noreorder	     \n"
			     "1: ll   %[tmp], %[val]  \n"
			     "	 bnez %[tmp], 1b     \n"
			     "	 li   %[tmp], 1	     \n"
			     "	 sc   %[tmp], %[val] \n"
			     "	 beqz %[tmp], 1b     \n"
			     "	 nop		    \n"
			     ".set reorder	     \n" :
			[val] "+m"(lock->value), [पंचांगp] "=&r"(पंचांगp)
			: : "memory");

पूर्ण

/** ********************************************************************
 * Bit spinlocks
 * These spinlocks use a single bit (bit 31) of a 32 bit word क्रम locking.
 * The rest of the bits in the word are left undisturbed.  This enables more
 * compact data काष्ठाures as only 1 bit is consumed क्रम the lock.
 *
 */

/**
 * Gets lock, spins until lock is taken
 * Preserves the low 31 bits of the 32 bit
 * word used क्रम the lock.
 *
 *
 * @word:  word to lock bit 31 of
 */
अटल अंतरभूत व्योम cvmx_spinlock_bit_lock(uपूर्णांक32_t *word)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक sav;

	__यंत्र__ __अस्थिर__(".set noreorder	     \n"
			     ".set noat		     \n"
			     "1: ll    %[tmp], %[val]  \n"
			     "	 bbit1 %[tmp], 31, 1b	 \n"
			     "	 li    $at, 1	   \n"
			     "	 ins   %[tmp], $at, 31, 1  \n"
			     "	 sc    %[tmp], %[val] \n"
			     "	 beqz  %[tmp], 1b     \n"
			     "	 nop		    \n"
			     ".set at		   \n"
			     ".set reorder	     \n" :
			[val] "+m"(*word), [पंचांगp] "=&r"(पंचांगp), [sav] "=&r"(sav)
			     : : "memory");

पूर्ण

/**
 * Attempts to get lock, वापसs immediately with success/failure
 * Preserves the low 31 bits of the 32 bit
 * word used क्रम the lock.
 *
 *
 * @word:  word to lock bit 31 of
 * Returns 0: lock successfully taken
 *	   1: lock not taken, held by someone अन्यथा
 * These वापस values match the Linux semantics.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cvmx_spinlock_bit_trylock(uपूर्णांक32_t *word)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(".set noreorder\n\t"
			     ".set noat\n"
			     "1: ll    %[tmp], %[val] \n"
			/* अगर lock held, fail immediately */
			     "	 bbit1 %[tmp], 31, 2f	  \n"
			     "	 li    $at, 1	   \n"
			     "	 ins   %[tmp], $at, 31, 1  \n"
			     "	 sc    %[tmp], %[val] \n"
			     "	 beqz  %[tmp], 1b     \n"
			     "	 li    %[tmp], 0      \n"
			     "2:		     \n"
			     ".set at		   \n"
			     ".set reorder	     \n" :
			[val] "+m"(*word), [पंचांगp] "=&r"(पंचांगp)
			: : "memory");

	वापस पंचांगp != 0;		/* normalize to 0 or 1 */
पूर्ण

/**
 * Releases bit lock
 *
 * Unconditionally clears bit 31 of the lock word.  Note that this is
 * करोne non-atomically, as this implementation assumes that the rest
 * of the bits in the word are रक्षित by the lock.
 *
 * @word:  word to unlock bit 31 in
 */
अटल अंतरभूत व्योम cvmx_spinlock_bit_unlock(uपूर्णांक32_t *word)
अणु
	CVMX_SYNCWS;
	*word &= ~(1UL << 31);
	CVMX_SYNCWS;
पूर्ण

#पूर्ण_अगर /* __CVMX_SPINLOCK_H__ */
