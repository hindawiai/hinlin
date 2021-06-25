<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2007-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

/** @file tपंचांग_lock.h
 * This file implements a simple replacement क्रम the buffer manager use
 * of the DRM heavyweight hardware lock.
 * The lock is a पढ़ो-ग_लिखो lock. Taking it in पढ़ो mode and ग_लिखो mode
 * is relatively fast, and पूर्णांकended क्रम in-kernel use only.
 *
 * The vt mode is used only when there is a need to block all
 * user-space processes from validating buffers.
 * It's allowed to leave kernel space with the vt lock held.
 * If a user-space process dies जबतक having the vt-lock,
 * it will be released during the file descriptor release. The vt lock
 * excludes ग_लिखो lock and पढ़ो lock.
 *
 * The suspend mode is used to lock out all TTM users when preparing क्रम
 * and executing suspend operations.
 *
 */

#अगर_अघोषित _TTM_LOCK_H_
#घोषणा _TTM_LOCK_H_

#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>

#समावेश "ttm_object.h"

/**
 * काष्ठा tपंचांग_lock
 *
 * @base: tपंचांग base object used solely to release the lock अगर the client
 * holding the lock dies.
 * @queue: Queue क्रम processes रुकोing क्रम lock change-of-status.
 * @lock: Spinlock protecting some lock members.
 * @rw: Read-ग_लिखो lock counter. Protected by @lock.
 * @flags: Lock state. Protected by @lock.
 */

काष्ठा tपंचांग_lock अणु
	काष्ठा tपंचांग_base_object base;
	रुको_queue_head_t queue;
	spinlock_t lock;
	पूर्णांक32_t rw;
	uपूर्णांक32_t flags;
पूर्ण;


/**
 * tपंचांग_lock_init
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 * Initializes the lock.
 */
बाह्य व्योम tपंचांग_lock_init(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_पढ़ो_unlock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Releases a पढ़ो lock.
 */
बाह्य व्योम tपंचांग_पढ़ो_unlock(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_पढ़ो_lock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 * @पूर्णांकerruptible: Interruptible sleeping जबतक रुकोing क्रम a lock.
 *
 * Takes the lock in पढ़ो mode.
 * Returns:
 * -ERESTARTSYS If पूर्णांकerrupted by a संकेत and पूर्णांकerruptible is true.
 */
बाह्य पूर्णांक tपंचांग_पढ़ो_lock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible);

/**
 * tपंचांग_पढ़ो_trylock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 * @पूर्णांकerruptible: Interruptible sleeping जबतक रुकोing क्रम a lock.
 *
 * Tries to take the lock in पढ़ो mode. If the lock is alपढ़ोy held
 * in ग_लिखो mode, the function will वापस -EBUSY. If the lock is held
 * in vt or suspend mode, the function will sleep until these modes
 * are unlocked.
 *
 * Returns:
 * -EBUSY The lock was alपढ़ोy held in ग_लिखो mode.
 * -ERESTARTSYS If पूर्णांकerrupted by a संकेत and पूर्णांकerruptible is true.
 */
बाह्य पूर्णांक tपंचांग_पढ़ो_trylock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible);

/**
 * tपंचांग_ग_लिखो_unlock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Releases a ग_लिखो lock.
 */
बाह्य व्योम tपंचांग_ग_लिखो_unlock(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_ग_लिखो_lock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 * @पूर्णांकerruptible: Interruptible sleeping जबतक रुकोing क्रम a lock.
 *
 * Takes the lock in ग_लिखो mode.
 * Returns:
 * -ERESTARTSYS If पूर्णांकerrupted by a संकेत and पूर्णांकerruptible is true.
 */
बाह्य पूर्णांक tपंचांग_ग_लिखो_lock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible);

/**
 * tपंचांग_lock_करोwngrade
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Downgrades a ग_लिखो lock to a पढ़ो lock.
 */
बाह्य व्योम tपंचांग_lock_करोwngrade(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_suspend_lock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Takes the lock in suspend mode. Excludes पढ़ो and ग_लिखो mode.
 */
बाह्य व्योम tपंचांग_suspend_lock(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_suspend_unlock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Releases a suspend lock
 */
बाह्य व्योम tपंचांग_suspend_unlock(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_vt_lock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 * @पूर्णांकerruptible: Interruptible sleeping जबतक रुकोing क्रम a lock.
 * @tfile: Poपूर्णांकer to a काष्ठा tपंचांग_object_file to रेजिस्टर the lock with.
 *
 * Takes the lock in vt mode.
 * Returns:
 * -ERESTARTSYS If पूर्णांकerrupted by a संकेत and पूर्णांकerruptible is true.
 * -ENOMEM: Out of memory when locking.
 */
बाह्य पूर्णांक tपंचांग_vt_lock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible,
		       काष्ठा tपंचांग_object_file *tfile);

/**
 * tपंचांग_vt_unlock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Releases a vt lock.
 * Returns:
 * -EINVAL If the lock was not held.
 */
बाह्य पूर्णांक tपंचांग_vt_unlock(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_ग_लिखो_unlock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 *
 * Releases a ग_लिखो lock.
 */
बाह्य व्योम tपंचांग_ग_लिखो_unlock(काष्ठा tपंचांग_lock *lock);

/**
 * tपंचांग_ग_लिखो_lock
 *
 * @lock: Poपूर्णांकer to a काष्ठा tपंचांग_lock
 * @पूर्णांकerruptible: Interruptible sleeping जबतक रुकोing क्रम a lock.
 *
 * Takes the lock in ग_लिखो mode.
 * Returns:
 * -ERESTARTSYS If पूर्णांकerrupted by a संकेत and पूर्णांकerruptible is true.
 */
बाह्य पूर्णांक tपंचांग_ग_लिखो_lock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible);

#पूर्ण_अगर
