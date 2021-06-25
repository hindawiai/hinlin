<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FUTEX_H
#घोषणा _UAPI_LINUX_FUTEX_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/* Second argument to futex syscall */


#घोषणा FUTEX_WAIT		0
#घोषणा FUTEX_WAKE		1
#घोषणा FUTEX_FD		2
#घोषणा FUTEX_REQUEUE		3
#घोषणा FUTEX_CMP_REQUEUE	4
#घोषणा FUTEX_WAKE_OP		5
#घोषणा FUTEX_LOCK_PI		6
#घोषणा FUTEX_UNLOCK_PI		7
#घोषणा FUTEX_TRYLOCK_PI	8
#घोषणा FUTEX_WAIT_BITSET	9
#घोषणा FUTEX_WAKE_BITSET	10
#घोषणा FUTEX_WAIT_REQUEUE_PI	11
#घोषणा FUTEX_CMP_REQUEUE_PI	12

#घोषणा FUTEX_PRIVATE_FLAG	128
#घोषणा FUTEX_CLOCK_REALTIME	256
#घोषणा FUTEX_CMD_MASK		~(FUTEX_PRIVATE_FLAG | FUTEX_CLOCK_REALTIME)

#घोषणा FUTEX_WAIT_PRIVATE	(FUTEX_WAIT | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_WAKE_PRIVATE	(FUTEX_WAKE | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_REQUEUE_PRIVATE	(FUTEX_REQUEUE | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_CMP_REQUEUE_PRIVATE (FUTEX_CMP_REQUEUE | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_WAKE_OP_PRIVATE	(FUTEX_WAKE_OP | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_LOCK_PI_PRIVATE	(FUTEX_LOCK_PI | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_UNLOCK_PI_PRIVATE	(FUTEX_UNLOCK_PI | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_TRYLOCK_PI_PRIVATE (FUTEX_TRYLOCK_PI | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_WAIT_BITSET_PRIVATE	(FUTEX_WAIT_BITSET | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_WAKE_BITSET_PRIVATE	(FUTEX_WAKE_BITSET | FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_WAIT_REQUEUE_PI_PRIVATE	(FUTEX_WAIT_REQUEUE_PI | \
					 FUTEX_PRIVATE_FLAG)
#घोषणा FUTEX_CMP_REQUEUE_PI_PRIVATE	(FUTEX_CMP_REQUEUE_PI | \
					 FUTEX_PRIVATE_FLAG)

/*
 * Support क्रम robust futexes: the kernel cleans up held futexes at
 * thपढ़ो निकास समय.
 */

/*
 * Per-lock list entry - embedded in user-space locks, somewhere बंद
 * to the futex field. (Note: user-space uses a द्विगुन-linked list to
 * achieve O(1) list add and हटाओ, but the kernel only needs to know
 * about the क्रमward link)
 *
 * NOTE: this काष्ठाure is part of the syscall ABI, and must not be
 * changed.
 */
काष्ठा robust_list अणु
	काष्ठा robust_list __user *next;
पूर्ण;

/*
 * Per-thपढ़ो list head:
 *
 * NOTE: this काष्ठाure is part of the syscall ABI, and must only be
 * changed अगर the change is first communicated with the glibc folks.
 * (When an incompatible change is करोne, we'll increase the काष्ठाure
 *  size, which glibc will detect)
 */
काष्ठा robust_list_head अणु
	/*
	 * The head of the list. Poपूर्णांकs back to itself अगर empty:
	 */
	काष्ठा robust_list list;

	/*
	 * This relative offset is set by user-space, it gives the kernel
	 * the relative position of the futex field to examine. This way
	 * we keep userspace flexible, to मुक्तly shape its data-काष्ठाure,
	 * without hardcoding any particular offset पूर्णांकo the kernel:
	 */
	दीर्घ futex_offset;

	/*
	 * The death of the thपढ़ो may race with userspace setting
	 * up a lock's links. So to handle this race, userspace first
	 * sets this field to the address of the to-be-taken lock,
	 * then करोes the lock acquire, and then adds itself to the
	 * list, and then clears this field. Hence the kernel will
	 * always have full knowledge of all locks that the thपढ़ो
	 * _might_ have taken. We check the owner TID in any हाल,
	 * so only truly owned locks will be handled.
	 */
	काष्ठा robust_list __user *list_op_pending;
पूर्ण;

/*
 * Are there any रुकोers क्रम this robust futex:
 */
#घोषणा FUTEX_WAITERS		0x80000000

/*
 * The kernel संकेतs via this bit that a thपढ़ो holding a futex
 * has निकासed without unlocking the futex. The kernel also करोes
 * a FUTEX_WAKE on such futexes, after setting the bit, to wake
 * up any possible रुकोers:
 */
#घोषणा FUTEX_OWNER_DIED	0x40000000

/*
 * The rest of the robust-futex field is क्रम the TID:
 */
#घोषणा FUTEX_TID_MASK		0x3fffffff

/*
 * This limit protects against a deliberately circular list.
 * (Not worth पूर्णांकroducing an rlimit क्रम it)
 */
#घोषणा ROBUST_LIST_LIMIT	2048

/*
 * bitset with all bits set क्रम the FUTEX_xxx_BITSET OPs to request a
 * match of any bit.
 */
#घोषणा FUTEX_BITSET_MATCH_ANY	0xffffffff


#घोषणा FUTEX_OP_SET		0	/* *(पूर्णांक *)UADDR2 = OPARG; */
#घोषणा FUTEX_OP_ADD		1	/* *(पूर्णांक *)UADDR2 += OPARG; */
#घोषणा FUTEX_OP_OR		2	/* *(पूर्णांक *)UADDR2 |= OPARG; */
#घोषणा FUTEX_OP_ANDN		3	/* *(पूर्णांक *)UADDR2 &= ~OPARG; */
#घोषणा FUTEX_OP_XOR		4	/* *(पूर्णांक *)UADDR2 ^= OPARG; */

#घोषणा FUTEX_OP_OPARG_SHIFT	8	/* Use (1 << OPARG) instead of OPARG.  */

#घोषणा FUTEX_OP_CMP_EQ		0	/* अगर (oldval == CMPARG) wake */
#घोषणा FUTEX_OP_CMP_NE		1	/* अगर (oldval != CMPARG) wake */
#घोषणा FUTEX_OP_CMP_LT		2	/* अगर (oldval < CMPARG) wake */
#घोषणा FUTEX_OP_CMP_LE		3	/* अगर (oldval <= CMPARG) wake */
#घोषणा FUTEX_OP_CMP_GT		4	/* अगर (oldval > CMPARG) wake */
#घोषणा FUTEX_OP_CMP_GE		5	/* अगर (oldval >= CMPARG) wake */

/* FUTEX_WAKE_OP will perक्रमm atomically
   पूर्णांक oldval = *(पूर्णांक *)UADDR2;
   *(पूर्णांक *)UADDR2 = oldval OP OPARG;
   अगर (oldval CMP CMPARG)
     wake UADDR2;  */

#घोषणा FUTEX_OP(op, oparg, cmp, cmparg) \
  (((op & 0xf) << 28) | ((cmp & 0xf) << 24)		\
   | ((oparg & 0xfff) << 12) | (cmparg & 0xfff))

#पूर्ण_अगर /* _UAPI_LINUX_FUTEX_H */
