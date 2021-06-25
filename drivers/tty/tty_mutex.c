<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/tty.h>
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/sched.h>
#समावेश "tty.h"

/* Legacy tty mutex glue */

/*
 * Getting the big tty mutex.
 */

व्योम tty_lock(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (WARN(tty->magic != TTY_MAGIC, "L Bad %p\n", tty))
		वापस;
	tty_kref_get(tty);
	mutex_lock(&tty->legacy_mutex);
पूर्ण
EXPORT_SYMBOL(tty_lock);

पूर्णांक tty_lock_पूर्णांकerruptible(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक ret;

	अगर (WARN(tty->magic != TTY_MAGIC, "L Bad %p\n", tty))
		वापस -EIO;
	tty_kref_get(tty);
	ret = mutex_lock_पूर्णांकerruptible(&tty->legacy_mutex);
	अगर (ret)
		tty_kref_put(tty);
	वापस ret;
पूर्ण

व्योम tty_unlock(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (WARN(tty->magic != TTY_MAGIC, "U Bad %p\n", tty))
		वापस;
	mutex_unlock(&tty->legacy_mutex);
	tty_kref_put(tty);
पूर्ण
EXPORT_SYMBOL(tty_unlock);

व्योम tty_lock_slave(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty && tty != tty->link)
		tty_lock(tty);
पूर्ण

व्योम tty_unlock_slave(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty && tty != tty->link)
		tty_unlock(tty);
पूर्ण

व्योम tty_set_lock_subclass(काष्ठा tty_काष्ठा *tty)
अणु
	lockdep_set_subclass(&tty->legacy_mutex, TTY_LOCK_SLAVE);
पूर्ण
