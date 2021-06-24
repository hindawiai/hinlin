<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2009
 *
 * DESCRIPTION
 *      GCC atomic builtin wrappers
 *      http://gcc.gnu.org/onlineकरोcs/gcc-4.1.0/gcc/Atomic-Builtins.hपंचांगl
 *
 * AUTHOR
 *      Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 * HISTORY
 *      2009-Nov-17: Initial version by Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 *****************************************************************************/

#अगर_अघोषित _ATOMIC_H
#घोषणा _ATOMIC_H

प्रकार काष्ठा अणु
	अस्थिर पूर्णांक val;
पूर्ण atomic_t;

#घोषणा ATOMIC_INITIALIZER अणु 0 पूर्ण

/**
 * atomic_cmpxchg() - Atomic compare and exchange
 * @uaddr:	The address of the futex to be modअगरied
 * @oldval:	The expected value of the futex
 * @newval:	The new value to try and assign the futex
 *
 * Return the old value of addr->val.
 */
अटल अंतरभूत पूर्णांक
atomic_cmpxchg(atomic_t *addr, पूर्णांक oldval, पूर्णांक newval)
अणु
	वापस __sync_val_compare_and_swap(&addr->val, oldval, newval);
पूर्ण

/**
 * atomic_inc() - Atomic incrememnt
 * @addr:	Address of the variable to increment
 *
 * Return the new value of addr->val.
 */
अटल अंतरभूत पूर्णांक
atomic_inc(atomic_t *addr)
अणु
	वापस __sync_add_and_fetch(&addr->val, 1);
पूर्ण

/**
 * atomic_dec() - Atomic decrement
 * @addr:	Address of the variable to decrement
 *
 * Return the new value of addr-val.
 */
अटल अंतरभूत पूर्णांक
atomic_dec(atomic_t *addr)
अणु
	वापस __sync_sub_and_fetch(&addr->val, 1);
पूर्ण

/**
 * atomic_set() - Atomic set
 * @addr:	Address of the variable to set
 * @newval:	New value क्रम the atomic_t
 *
 * Return the new value of addr->val.
 */
अटल अंतरभूत पूर्णांक
atomic_set(atomic_t *addr, पूर्णांक newval)
अणु
	addr->val = newval;
	वापस newval;
पूर्ण

#पूर्ण_अगर
