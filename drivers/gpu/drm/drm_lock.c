<शैली गुरु>
/*
 * \पile drm_lock.c
 * IOCTLs क्रम locking
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Tue Feb  2 08:37:54 1999 by faith@valinux.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <drm/drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

अटल पूर्णांक drm_lock_take(काष्ठा drm_lock_data *lock_data, अचिन्हित पूर्णांक context);

/*
 * Take the heavyweight lock.
 *
 * \param lock lock poपूर्णांकer.
 * \param context locking context.
 * \लeturn one अगर the lock is held, or zero otherwise.
 *
 * Attempt to mark the lock as held by the given context, via the \p cmpxchg inकाष्ठाion.
 */
अटल
पूर्णांक drm_lock_take(काष्ठा drm_lock_data *lock_data,
		  अचिन्हित पूर्णांक context)
अणु
	अचिन्हित पूर्णांक old, new, prev;
	अस्थिर अचिन्हित पूर्णांक *lock = &lock_data->hw_lock->lock;

	spin_lock_bh(&lock_data->spinlock);
	करो अणु
		old = *lock;
		अगर (old & _DRM_LOCK_HELD)
			new = old | _DRM_LOCK_CONT;
		अन्यथा अणु
			new = context | _DRM_LOCK_HELD |
				((lock_data->user_रुकोers + lock_data->kernel_रुकोers > 1) ?
				 _DRM_LOCK_CONT : 0);
		पूर्ण
		prev = cmpxchg(lock, old, new);
	पूर्ण जबतक (prev != old);
	spin_unlock_bh(&lock_data->spinlock);

	अगर (_DRM_LOCKING_CONTEXT(old) == context) अणु
		अगर (old & _DRM_LOCK_HELD) अणु
			अगर (context != DRM_KERNEL_CONTEXT) अणु
				DRM_ERROR("%d holds heavyweight lock\n",
					  context);
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

	अगर ((_DRM_LOCKING_CONTEXT(new)) == context && (new & _DRM_LOCK_HELD)) अणु
		/* Have lock */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This takes a lock क्रमcibly and hands it to context.	Should ONLY be used
 * inside *_unlock to give lock to kernel beक्रमe calling *_dma_schedule.
 *
 * \param dev DRM device.
 * \param lock lock poपूर्णांकer.
 * \param context locking context.
 * \लeturn always one.
 *
 * Resets the lock file poपूर्णांकer.
 * Marks the lock as held by the given context, via the \p cmpxchg inकाष्ठाion.
 */
अटल पूर्णांक drm_lock_transfer(काष्ठा drm_lock_data *lock_data,
			     अचिन्हित पूर्णांक context)
अणु
	अचिन्हित पूर्णांक old, new, prev;
	अस्थिर अचिन्हित पूर्णांक *lock = &lock_data->hw_lock->lock;

	lock_data->file_priv = शून्य;
	करो अणु
		old = *lock;
		new = context | _DRM_LOCK_HELD;
		prev = cmpxchg(lock, old, new);
	पूर्ण जबतक (prev != old);
	वापस 1;
पूर्ण

अटल पूर्णांक drm_legacy_lock_मुक्त(काष्ठा drm_lock_data *lock_data,
				अचिन्हित पूर्णांक context)
अणु
	अचिन्हित पूर्णांक old, new, prev;
	अस्थिर अचिन्हित पूर्णांक *lock = &lock_data->hw_lock->lock;

	spin_lock_bh(&lock_data->spinlock);
	अगर (lock_data->kernel_रुकोers != 0) अणु
		drm_lock_transfer(lock_data, 0);
		lock_data->idle_has_lock = 1;
		spin_unlock_bh(&lock_data->spinlock);
		वापस 1;
	पूर्ण
	spin_unlock_bh(&lock_data->spinlock);

	करो अणु
		old = *lock;
		new = _DRM_LOCKING_CONTEXT(old);
		prev = cmpxchg(lock, old, new);
	पूर्ण जबतक (prev != old);

	अगर (_DRM_LOCK_IS_HELD(old) && _DRM_LOCKING_CONTEXT(old) != context) अणु
		DRM_ERROR("%d freed heavyweight lock held by %d\n",
			  context, _DRM_LOCKING_CONTEXT(old));
		वापस 1;
	पूर्ण
	wake_up_पूर्णांकerruptible(&lock_data->lock_queue);
	वापस 0;
पूर्ण

/*
 * Lock ioctl.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_lock काष्ठाure.
 * \लeturn zero on success or negative number on failure.
 *
 * Add the current task to the lock रुको queue, and attempt to take to lock.
 */
पूर्णांक drm_legacy_lock(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file_priv)
अणु
	DECLARE_WAITQUEUE(entry, current);
	काष्ठा drm_lock *lock = data;
	काष्ठा drm_master *master = file_priv->master;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	++file_priv->lock_count;

	अगर (lock->context == DRM_KERNEL_CONTEXT) अणु
		DRM_ERROR("Process %d using kernel context %d\n",
			  task_pid_nr(current), lock->context);
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG("%d (pid %d) requests lock (0x%08x), flags = 0x%08x\n",
		  lock->context, task_pid_nr(current),
		  master->lock.hw_lock ? master->lock.hw_lock->lock : -1,
		  lock->flags);

	add_रुको_queue(&master->lock.lock_queue, &entry);
	spin_lock_bh(&master->lock.spinlock);
	master->lock.user_रुकोers++;
	spin_unlock_bh(&master->lock.spinlock);

	क्रम (;;) अणु
		__set_current_state(TASK_INTERRUPTIBLE);
		अगर (!master->lock.hw_lock) अणु
			/* Device has been unरेजिस्टरed */
			send_sig(संक_इति, current, 0);
			ret = -EINTR;
			अवरोध;
		पूर्ण
		अगर (drm_lock_take(&master->lock, lock->context)) अणु
			master->lock.file_priv = file_priv;
			master->lock.lock_समय = jअगरfies;
			अवरोध;	/* Got lock */
		पूर्ण

		/* Contention */
		mutex_unlock(&drm_global_mutex);
		schedule();
		mutex_lock(&drm_global_mutex);
		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_lock_bh(&master->lock.spinlock);
	master->lock.user_रुकोers--;
	spin_unlock_bh(&master->lock.spinlock);
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&master->lock.lock_queue, &entry);

	DRM_DEBUG("%d %s\n", lock->context,
		  ret ? "interrupted" : "has lock");
	अगर (ret) वापस ret;

	/* करोn't set the block all संकेतs on the master process क्रम now 
	 * really probably not the correct answer but lets us debug xkb
 	 * xserver क्रम now */
	अगर (!drm_is_current_master(file_priv)) अणु
		dev->sigdata.context = lock->context;
		dev->sigdata.lock = master->lock.hw_lock;
	पूर्ण

	अगर (dev->driver->dma_quiescent && (lock->flags & _DRM_LOCK_QUIESCENT))
	अणु
		अगर (dev->driver->dma_quiescent(dev)) अणु
			DRM_DEBUG("%d waiting for DMA quiescent\n",
				  lock->context);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Unlock ioctl.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_lock काष्ठाure.
 * \लeturn zero on success or negative number on failure.
 *
 * Transfer and मुक्त the lock.
 */
पूर्णांक drm_legacy_unlock(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_lock *lock = data;
	काष्ठा drm_master *master = file_priv->master;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (lock->context == DRM_KERNEL_CONTEXT) अणु
		DRM_ERROR("Process %d using kernel context %d\n",
			  task_pid_nr(current), lock->context);
		वापस -EINVAL;
	पूर्ण

	अगर (drm_legacy_lock_मुक्त(&master->lock, lock->context)) अणु
		/* FIXME: Should really bail out here. */
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function वापसs immediately and takes the hw lock
 * with the kernel context अगर it is मुक्त, otherwise it माला_लो the highest priority when and अगर
 * it is eventually released.
 *
 * This guarantees that the kernel will _eventually_ have the lock _unless_ it is held
 * by a blocked process. (In the latter हाल an explicit रुको क्रम the hardware lock would cause
 * a deadlock, which is why the "idlelock" was invented).
 *
 * This should be sufficient to रुको क्रम GPU idle without
 * having to worry about starvation.
 */
व्योम drm_legacy_idlelock_take(काष्ठा drm_lock_data *lock_data)
अणु
	पूर्णांक ret;

	spin_lock_bh(&lock_data->spinlock);
	lock_data->kernel_रुकोers++;
	अगर (!lock_data->idle_has_lock) अणु

		spin_unlock_bh(&lock_data->spinlock);
		ret = drm_lock_take(lock_data, DRM_KERNEL_CONTEXT);
		spin_lock_bh(&lock_data->spinlock);

		अगर (ret == 1)
			lock_data->idle_has_lock = 1;
	पूर्ण
	spin_unlock_bh(&lock_data->spinlock);
पूर्ण
EXPORT_SYMBOL(drm_legacy_idlelock_take);

व्योम drm_legacy_idlelock_release(काष्ठा drm_lock_data *lock_data)
अणु
	अचिन्हित पूर्णांक old, prev;
	अस्थिर अचिन्हित पूर्णांक *lock = &lock_data->hw_lock->lock;

	spin_lock_bh(&lock_data->spinlock);
	अगर (--lock_data->kernel_रुकोers == 0) अणु
		अगर (lock_data->idle_has_lock) अणु
			करो अणु
				old = *lock;
				prev = cmpxchg(lock, old, DRM_KERNEL_CONTEXT);
			पूर्ण जबतक (prev != old);
			wake_up_पूर्णांकerruptible(&lock_data->lock_queue);
			lock_data->idle_has_lock = 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&lock_data->spinlock);
पूर्ण
EXPORT_SYMBOL(drm_legacy_idlelock_release);

अटल पूर्णांक drm_legacy_i_have_hw_lock(काष्ठा drm_device *dev,
				     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_master *master = file_priv->master;

	वापस (file_priv->lock_count && master->lock.hw_lock &&
		_DRM_LOCK_IS_HELD(master->lock.hw_lock->lock) &&
		master->lock.file_priv == file_priv);
पूर्ण

व्योम drm_legacy_lock_release(काष्ठा drm_device *dev, काष्ठा file *filp)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;

	/* अगर the master has gone away we can't करो anything with the lock */
	अगर (!dev->master)
		वापस;

	अगर (drm_legacy_i_have_hw_lock(dev, file_priv)) अणु
		DRM_DEBUG("File %p released, freeing lock for context %d\n",
			  filp, _DRM_LOCKING_CONTEXT(file_priv->master->lock.hw_lock->lock));
		drm_legacy_lock_मुक्त(&file_priv->master->lock,
				     _DRM_LOCKING_CONTEXT(file_priv->master->lock.hw_lock->lock));
	पूर्ण
पूर्ण

व्योम drm_legacy_lock_master_cleanup(काष्ठा drm_device *dev, काष्ठा drm_master *master)
अणु
	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	/*
	 * Since the master is disappearing, so is the
	 * possibility to lock.
	 */
	mutex_lock(&dev->काष्ठा_mutex);
	अगर (master->lock.hw_lock) अणु
		अगर (dev->sigdata.lock == master->lock.hw_lock)
			dev->sigdata.lock = शून्य;
		master->lock.hw_lock = शून्य;
		master->lock.file_priv = शून्य;
		wake_up_पूर्णांकerruptible_all(&master->lock.lock_queue);
	पूर्ण
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण
