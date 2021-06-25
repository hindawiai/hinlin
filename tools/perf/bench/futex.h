<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Glibc independent futex library क्रम testing kernel functionality.
 * Shamelessly stolen from Darren Hart <dvhltc@us.ibm.com>
 *    http://git.kernel.org/cgit/linux/kernel/git/dvhart/futextest.git/
 */

#अगर_अघोषित _FUTEX_H
#घोषणा _FUTEX_H

#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <linux/futex.h>

/**
 * futex() - SYS_futex syscall wrapper
 * @uaddr:	address of first futex
 * @op:		futex op code
 * @val:	typically expected value of uaddr, but varies by op
 * @समयout:	typically an असलolute काष्ठा बारpec (except where noted
 *		otherwise). Overloaded by some ops
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
futex_रुको(u_पूर्णांक32_t *uaddr, u_पूर्णांक32_t val, काष्ठा बारpec *समयout, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAIT, val, समयout, शून्य, 0, opflags);
पूर्ण

/**
 * futex_wake() - wake one or more tasks blocked on uaddr
 * @nr_wake:	wake up to this many tasks
 */
अटल अंतरभूत पूर्णांक
futex_wake(u_पूर्णांक32_t *uaddr, पूर्णांक nr_wake, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_WAKE, nr_wake, शून्य, शून्य, 0, opflags);
पूर्ण

/**
 * futex_lock_pi() - block on uaddr as a PI mutex
 */
अटल अंतरभूत पूर्णांक
futex_lock_pi(u_पूर्णांक32_t *uaddr, काष्ठा बारpec *समयout, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_LOCK_PI, 0, समयout, शून्य, 0, opflags);
पूर्ण

/**
 * futex_unlock_pi() - release uaddr as a PI mutex, waking the top रुकोer
 */
अटल अंतरभूत पूर्णांक
futex_unlock_pi(u_पूर्णांक32_t *uaddr, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_UNLOCK_PI, 0, शून्य, शून्य, 0, opflags);
पूर्ण

/**
* futex_cmp_requeue() - requeue tasks from uaddr to uaddr2
* @nr_wake:        wake up to this many tasks
* @nr_requeue:        requeue up to this many tasks
*/
अटल अंतरभूत पूर्णांक
futex_cmp_requeue(u_पूर्णांक32_t *uaddr, u_पूर्णांक32_t val, u_पूर्णांक32_t *uaddr2, पूर्णांक nr_wake,
		 पूर्णांक nr_requeue, पूर्णांक opflags)
अणु
	वापस futex(uaddr, FUTEX_CMP_REQUEUE, nr_wake, nr_requeue, uaddr2,
		 val, opflags);
पूर्ण
#पूर्ण_अगर /* _FUTEX_H */
