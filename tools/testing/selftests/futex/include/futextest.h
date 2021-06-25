<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *   Copyright तऊ International Business Machines  Corp., 2009
 *
 * DESCRIPTION
 *      Glibc independent futex library क्रम testing kernel functionality.
 *
 * AUTHOR
 *      Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 * HISTORY
 *      2009-Nov-6: Initial version by Darren Hart <dvhart@linux.पूर्णांकel.com>
 *
 *****************************************************************************/

#अगर_अघोषित _FUTEXTEST_H
#घोषणा _FUTEXTEST_H

#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <linux/futex.h>

प्रकार अस्थिर u_पूर्णांक32_t futex_t;
#घोषणा FUTEX_INITIALIZER 0

/* Define the newer op codes अगर the प्रणाली header file is not up to date. */
#अगर_अघोषित FUTEX_WAIT_BITSET
#घोषणा FUTEX_WAIT_BITSET		9
#पूर्ण_अगर
#अगर_अघोषित FUTEX_WAKE_BITSET
#घोषणा FUTEX_WAKE_BITSET		10
#पूर्ण_अगर
#अगर_अघोषित FUTEX_WAIT_REQUEUE_PI
#घोषणा FUTEX_WAIT_REQUEUE_PI		11
#पूर्ण_अगर
#अगर_अघोषित FUTEX_CMP_REQUEUE_PI
#घोषणा FUTEX_CMP_REQUEUE_PI		12
#पूर्ण_अगर
#अगर_अघोषित FUTEX_WAIT_REQUEUE_PI_PRIVATE
#घोषणा FUTEX_WAIT_REQUEUE_PI_PRIVATE	(FUTEX_WAIT_REQUEUE_PI | \
					 FUTEX_PRIVATE_FLAG)
#पूर्ण_अगर
#अगर_अघोषित FUTEX_REQUEUE_PI_PRIVATE
#घोषणा FUTEX_CMP_REQUEUE_PI_PRIVATE	(FUTEX_CMP_REQUEUE_PI | \
					 FUTEX_PRIVATE_FLAG)
#पूर्ण_अगर

/**
 * futex() - SYS_futex syscall wrapper
 * @uaddr:	address of first futex
 * @op:		futex op code
 * @val:	typically expected value of uaddr, but varies by op
 * @समयout:	typically an असलolute काष्ठा बारpec (except where noted
 *              otherwise). Overloaded by some ops
 * @uaddr2:	address of second futex क्रम some ops\
 * @val3:	varies by op
 * @opflags:	flags to be bitwise OR'd with op, such as FUTEX_PRIVATE_FLAG
 *
 * futex() is used by all the following futex op wrappers. It can also be
 * used क्रम misuse and abuse testing. Generally, the specअगरic op wrappers
 * should be used instead. It is a macro instead of an अटल अंतरभूत function as
 * some of the types over overloaded (समयout is used क्रम nr_requeue क्रम
 * example).
 *
 * These argument descriptions are the शेषs क्रम all
 * like-named arguments in the following wrappers except where noted below.
 */
#घोषणा futex(uaddr, op, val, समयout, uaddr2, val3, opflags) \
	syscall(SYS_futex, uaddr, op | opflags, val, समयout, uaddr2, val3)

/**
 * futex_रुको() - block on uaddr with optional समयout
 * @समयout:	relative समयout
 */
अटल अंतरभूत पूर्णांक
futex_रुको(futex_t *uaddr, futex_t val, काष्ठा बारpec *समयout, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAIT, val, समयout, शून्य, 0, opflags);
पूर्ण

/**
 * futex_wake() - wake one or more tasks blocked on uaddr
 * @nr_wake:	wake up to this many tasks
 */
अटल अंतरभूत पूर्णांक
futex_wake(futex_t *uaddr, पूर्णांक nr_wake, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAKE, nr_wake, शून्य, शून्य, 0, opflags);
पूर्ण

/**
 * futex_रुको_bitset() - block on uaddr with bitset
 * @bitset:	bitset to be used with futex_wake_bitset
 */
अटल अंतरभूत पूर्णांक
futex_रुको_bitset(futex_t *uaddr, futex_t val, काष्ठा बारpec *समयout,
		  u_पूर्णांक32_t bitset, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAIT_BITSET, val, समयout, शून्य, bitset,
		     opflags);
पूर्ण

/**
 * futex_wake_bitset() - wake one or more tasks blocked on uaddr with bitset
 * @bitset:	bitset to compare with that used in futex_रुको_bitset
 */
अटल अंतरभूत पूर्णांक
futex_wake_bitset(futex_t *uaddr, पूर्णांक nr_wake, u_पूर्णांक32_t bitset, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAKE_BITSET, nr_wake, शून्य, शून्य, bitset,
		     opflags);
पूर्ण

/**
 * futex_lock_pi() - block on uaddr as a PI mutex
 * @detect:	whether (1) or not (0) to perक्रमm deadlock detection
 */
अटल अंतरभूत पूर्णांक
futex_lock_pi(futex_t *uaddr, काष्ठा बारpec *समयout, पूर्णांक detect,
	      पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_LOCK_PI, detect, समयout, शून्य, 0, opflags);
पूर्ण

/**
 * futex_unlock_pi() - release uaddr as a PI mutex, waking the top रुकोer
 */
अटल अंतरभूत पूर्णांक
futex_unlock_pi(futex_t *uaddr, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_UNLOCK_PI, 0, शून्य, शून्य, 0, opflags);
पूर्ण

/**
 * futex_wake_op() - FIXME: COME UP WITH A GOOD ONE LINE DESCRIPTION
 */
अटल अंतरभूत पूर्णांक
futex_wake_op(futex_t *uaddr, futex_t *uaddr2, पूर्णांक nr_wake, पूर्णांक nr_wake2,
	      पूर्णांक wake_op, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAKE_OP, nr_wake, nr_wake2, uaddr2, wake_op,
		     opflags);
पूर्ण

/**
 * futex_requeue() - requeue without expected value comparison, deprecated
 * @nr_wake:	wake up to this many tasks
 * @nr_requeue:	requeue up to this many tasks
 *
 * Due to its inherently racy implementation, futex_requeue() is deprecated in
 * favor of futex_cmp_requeue().
 */
अटल अंतरभूत पूर्णांक
futex_requeue(futex_t *uaddr, futex_t *uaddr2, पूर्णांक nr_wake, पूर्णांक nr_requeue,
	      पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_REQUEUE, nr_wake, nr_requeue, uaddr2, 0,
		     opflags);
पूर्ण

/**
 * futex_cmp_requeue() - requeue tasks from uaddr to uaddr2
 * @nr_wake:	wake up to this many tasks
 * @nr_requeue:	requeue up to this many tasks
 */
अटल अंतरभूत पूर्णांक
futex_cmp_requeue(futex_t *uaddr, futex_t val, futex_t *uaddr2, पूर्णांक nr_wake,
		  पूर्णांक nr_requeue, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_CMP_REQUEUE, nr_wake, nr_requeue, uaddr2,
		     val, opflags);
पूर्ण

/**
 * futex_रुको_requeue_pi() - block on uaddr and prepare to requeue to uaddr2
 * @uaddr:	non-PI futex source
 * @uaddr2:	PI futex target
 *
 * This is the first half of the requeue_pi mechanism. It shall always be
 * paired with futex_cmp_requeue_pi().
 */
अटल अंतरभूत पूर्णांक
futex_रुको_requeue_pi(futex_t *uaddr, futex_t val, futex_t *uaddr2,
		      काष्ठा बारpec *समयout, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAIT_REQUEUE_PI, val, समयout, uaddr2, 0,
		     opflags);
पूर्ण

/**
 * futex_cmp_requeue_pi() - requeue tasks from uaddr to uaddr2 (PI aware)
 * @uaddr:	non-PI futex source
 * @uaddr2:	PI futex target
 * @nr_wake:	wake up to this many tasks
 * @nr_requeue:	requeue up to this many tasks
 */
अटल अंतरभूत पूर्णांक
futex_cmp_requeue_pi(futex_t *uaddr, futex_t val, futex_t *uaddr2, पूर्णांक nr_wake,
		     पूर्णांक nr_requeue, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_CMP_REQUEUE_PI, nr_wake, nr_requeue, uaddr2,
		     val, opflags);
पूर्ण

/**
 * futex_cmpxchg() - atomic compare and exchange
 * @uaddr:	The address of the futex to be modअगरied
 * @oldval:	The expected value of the futex
 * @newval:	The new value to try and assign the futex
 *
 * Implement cmpxchg using gcc atomic builtins.
 * http://gcc.gnu.org/onlineकरोcs/gcc-4.1.0/gcc/Atomic-Builtins.hपंचांगl
 *
 * Return the old futex value.
 */
अटल अंतरभूत u_पूर्णांक32_t
futex_cmpxchg(futex_t *uaddr, u_पूर्णांक32_t oldval, u_पूर्णांक32_t newval)
अणु
	वापस __sync_val_compare_and_swap(uaddr, oldval, newval);
पूर्ण

/**
 * futex_dec() - atomic decrement of the futex value
 * @uaddr:	The address of the futex to be modअगरied
 *
 * Return the new futex value.
 */
अटल अंतरभूत u_पूर्णांक32_t
futex_dec(futex_t *uaddr)
अणु
	वापस __sync_sub_and_fetch(uaddr, 1);
पूर्ण

/**
 * futex_inc() - atomic increment of the futex value
 * @uaddr:	the address of the futex to be modअगरied
 *
 * Return the new futex value.
 */
अटल अंतरभूत u_पूर्णांक32_t
futex_inc(futex_t *uaddr)
अणु
	वापस __sync_add_and_fetch(uaddr, 1);
पूर्ण

/**
 * futex_set() - atomic decrement of the futex value
 * @uaddr:	the address of the futex to be modअगरied
 * @newval:	New value क्रम the atomic_t
 *
 * Return the new futex value.
 */
अटल अंतरभूत u_पूर्णांक32_t
futex_set(futex_t *uaddr, u_पूर्णांक32_t newval)
अणु
	*uaddr = newval;
	वापस newval;
पूर्ण

#पूर्ण_अगर
