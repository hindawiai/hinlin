<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
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

#समावेश <linux/atomic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "ttm_lock.h"
#समावेश "ttm_object.h"

#घोषणा TTM_WRITE_LOCK_PENDING    (1 << 0)
#घोषणा TTM_VT_LOCK_PENDING       (1 << 1)
#घोषणा TTM_SUSPEND_LOCK_PENDING  (1 << 2)
#घोषणा TTM_VT_LOCK               (1 << 3)
#घोषणा TTM_SUSPEND_LOCK          (1 << 4)

व्योम tपंचांग_lock_init(काष्ठा tपंचांग_lock *lock)
अणु
	spin_lock_init(&lock->lock);
	init_रुकोqueue_head(&lock->queue);
	lock->rw = 0;
	lock->flags = 0;
पूर्ण

व्योम tपंचांग_पढ़ो_unlock(काष्ठा tपंचांग_lock *lock)
अणु
	spin_lock(&lock->lock);
	अगर (--lock->rw == 0)
		wake_up_all(&lock->queue);
	spin_unlock(&lock->lock);
पूर्ण

अटल bool __tपंचांग_पढ़ो_lock(काष्ठा tपंचांग_lock *lock)
अणु
	bool locked = false;

	spin_lock(&lock->lock);
	अगर (lock->rw >= 0 && lock->flags == 0) अणु
		++lock->rw;
		locked = true;
	पूर्ण
	spin_unlock(&lock->lock);
	वापस locked;
पूर्ण

पूर्णांक tपंचांग_पढ़ो_lock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible)
अणु
	पूर्णांक ret = 0;

	अगर (पूर्णांकerruptible)
		ret = रुको_event_पूर्णांकerruptible(lock->queue,
					       __tपंचांग_पढ़ो_lock(lock));
	अन्यथा
		रुको_event(lock->queue, __tपंचांग_पढ़ो_lock(lock));
	वापस ret;
पूर्ण

अटल bool __tपंचांग_पढ़ो_trylock(काष्ठा tपंचांग_lock *lock, bool *locked)
अणु
	bool block = true;

	*locked = false;

	spin_lock(&lock->lock);
	अगर (lock->rw >= 0 && lock->flags == 0) अणु
		++lock->rw;
		block = false;
		*locked = true;
	पूर्ण अन्यथा अगर (lock->flags == 0) अणु
		block = false;
	पूर्ण
	spin_unlock(&lock->lock);

	वापस !block;
पूर्ण

पूर्णांक tपंचांग_पढ़ो_trylock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible)
अणु
	पूर्णांक ret = 0;
	bool locked;

	अगर (पूर्णांकerruptible)
		ret = रुको_event_पूर्णांकerruptible
			(lock->queue, __tपंचांग_पढ़ो_trylock(lock, &locked));
	अन्यथा
		रुको_event(lock->queue, __tपंचांग_पढ़ो_trylock(lock, &locked));

	अगर (unlikely(ret != 0)) अणु
		BUG_ON(locked);
		वापस ret;
	पूर्ण

	वापस (locked) ? 0 : -EBUSY;
पूर्ण

व्योम tपंचांग_ग_लिखो_unlock(काष्ठा tपंचांग_lock *lock)
अणु
	spin_lock(&lock->lock);
	lock->rw = 0;
	wake_up_all(&lock->queue);
	spin_unlock(&lock->lock);
पूर्ण

अटल bool __tपंचांग_ग_लिखो_lock(काष्ठा tपंचांग_lock *lock)
अणु
	bool locked = false;

	spin_lock(&lock->lock);
	अगर (lock->rw == 0 && ((lock->flags & ~TTM_WRITE_LOCK_PENDING) == 0)) अणु
		lock->rw = -1;
		lock->flags &= ~TTM_WRITE_LOCK_PENDING;
		locked = true;
	पूर्ण अन्यथा अणु
		lock->flags |= TTM_WRITE_LOCK_PENDING;
	पूर्ण
	spin_unlock(&lock->lock);
	वापस locked;
पूर्ण

पूर्णांक tपंचांग_ग_लिखो_lock(काष्ठा tपंचांग_lock *lock, bool पूर्णांकerruptible)
अणु
	पूर्णांक ret = 0;

	अगर (पूर्णांकerruptible) अणु
		ret = रुको_event_पूर्णांकerruptible(lock->queue,
					       __tपंचांग_ग_लिखो_lock(lock));
		अगर (unlikely(ret != 0)) अणु
			spin_lock(&lock->lock);
			lock->flags &= ~TTM_WRITE_LOCK_PENDING;
			wake_up_all(&lock->queue);
			spin_unlock(&lock->lock);
		पूर्ण
	पूर्ण अन्यथा
		रुको_event(lock->queue, __tपंचांग_ग_लिखो_lock(lock));

	वापस ret;
पूर्ण

व्योम tपंचांग_suspend_unlock(काष्ठा tपंचांग_lock *lock)
अणु
	spin_lock(&lock->lock);
	lock->flags &= ~TTM_SUSPEND_LOCK;
	wake_up_all(&lock->queue);
	spin_unlock(&lock->lock);
पूर्ण

अटल bool __tपंचांग_suspend_lock(काष्ठा tपंचांग_lock *lock)
अणु
	bool locked = false;

	spin_lock(&lock->lock);
	अगर (lock->rw == 0) अणु
		lock->flags &= ~TTM_SUSPEND_LOCK_PENDING;
		lock->flags |= TTM_SUSPEND_LOCK;
		locked = true;
	पूर्ण अन्यथा अणु
		lock->flags |= TTM_SUSPEND_LOCK_PENDING;
	पूर्ण
	spin_unlock(&lock->lock);
	वापस locked;
पूर्ण

व्योम tपंचांग_suspend_lock(काष्ठा tपंचांग_lock *lock)
अणु
	रुको_event(lock->queue, __tपंचांग_suspend_lock(lock));
पूर्ण
