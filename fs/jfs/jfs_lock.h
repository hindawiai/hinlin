<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2001
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */
#अगर_अघोषित _H_JFS_LOCK
#घोषणा _H_JFS_LOCK

#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>

/*
 *	jfs_lock.h
 */

/*
 * Conditional sleep where condition is रक्षित by spinlock
 *
 * lock_cmd and unlock_cmd take and release the spinlock
 */
#घोषणा __SLEEP_COND(wq, cond, lock_cmd, unlock_cmd)	\
करो अणु							\
	DECLARE_WAITQUEUE(__रुको, current);		\
							\
	add_रुको_queue(&wq, &__रुको);			\
	क्रम (;;) अणु					\
		set_current_state(TASK_UNINTERRUPTIBLE);\
		अगर (cond)				\
			अवरोध;				\
		unlock_cmd;				\
		io_schedule();				\
		lock_cmd;				\
	पूर्ण						\
	__set_current_state(TASK_RUNNING);			\
	हटाओ_रुको_queue(&wq, &__रुको);		\
पूर्ण जबतक (0)

#पूर्ण_अगर				/* _H_JFS_LOCK */
