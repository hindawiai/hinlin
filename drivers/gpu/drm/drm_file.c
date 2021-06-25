<शैली गुरु>
/*
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Daryll Strauss <daryll@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com
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

#समावेश <linux/anon_inodes.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_client.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

#अगर defined(CONFIG_MMU) && defined(CONFIG_TRANSPARENT_HUGEPAGE)
#समावेश <uapi/यंत्र/mman.h>
#समावेश <drm/drm_vma_manager.h>
#पूर्ण_अगर

/* from BKL pushकरोwn */
DEFINE_MUTEX(drm_global_mutex);

bool drm_dev_needs_global_mutex(काष्ठा drm_device *dev)
अणु
	/*
	 * Legacy drivers rely on all kinds of BKL locking semantics, करोn't
	 * bother. They also still need BKL locking क्रम their ioctls, so better
	 * safe than sorry.
	 */
	अगर (drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस true;

	/*
	 * The deprecated ->load callback must be called after the driver is
	 * alपढ़ोy रेजिस्टरed. This means such drivers rely on the BKL to make
	 * sure an खोलो can't proceed until the driver is actually fully set up.
	 * Similar hilarity holds क्रम the unload callback.
	 */
	अगर (dev->driver->load || dev->driver->unload)
		वापस true;

	/*
	 * Drivers with the lastबंद callback assume that it's synchronized
	 * against concurrent खोलोs, which again needs the BKL. The proper fix
	 * is to use the drm_client infraकाष्ठाure with proper locking क्रम each
	 * client.
	 */
	अगर (dev->driver->lastबंद)
		वापस true;

	वापस false;
पूर्ण

/**
 * DOC: file operations
 *
 * Drivers must define the file operations काष्ठाure that क्रमms the DRM
 * userspace API entry poपूर्णांक, even though most of those operations are
 * implemented in the DRM core. The resulting &काष्ठा file_operations must be
 * stored in the &drm_driver.fops field. The mandatory functions are drm_खोलो(),
 * drm_पढ़ो(), drm_ioctl() and drm_compat_ioctl() अगर CONFIG_COMPAT is enabled
 * Note that drm_compat_ioctl will be शून्य अगर CONFIG_COMPAT=n, so there's no
 * need to sprinkle #अगर_घोषित पूर्णांकo the code. Drivers which implement निजी ioctls
 * that require 32/64 bit compatibility support must provide their own
 * &file_operations.compat_ioctl handler that processes निजी ioctls and calls
 * drm_compat_ioctl() क्रम core ioctls.
 *
 * In addition drm_पढ़ो() and drm_poll() provide support क्रम DRM events. DRM
 * events are a generic and extensible means to send asynchronous events to
 * userspace through the file descriptor. They are used to send vblank event and
 * page flip completions by the KMS API. But drivers can also use it क्रम their
 * own needs, e.g. to संकेत completion of rendering.
 *
 * For the driver-side event पूर्णांकerface see drm_event_reserve_init() and
 * drm_send_event() as the मुख्य starting poपूर्णांकs.
 *
 * The memory mapping implementation will vary depending on how the driver
 * manages memory. Legacy drivers will use the deprecated drm_legacy_mmap()
 * function, modern drivers should use one of the provided memory-manager
 * specअगरic implementations. For GEM-based drivers this is drm_gem_mmap().
 *
 * No other file operations are supported by the DRM userspace API. Overall the
 * following is an example &file_operations काष्ठाure::
 *
 *     अटल स्थिर example_drm_fops = अणु
 *             .owner = THIS_MODULE,
 *             .खोलो = drm_खोलो,
 *             .release = drm_release,
 *             .unlocked_ioctl = drm_ioctl,
 *             .compat_ioctl = drm_compat_ioctl, // शून्य अगर CONFIG_COMPAT=n
 *             .poll = drm_poll,
 *             .पढ़ो = drm_पढ़ो,
 *             .llseek = no_llseek,
 *             .mmap = drm_gem_mmap,
 *     पूर्ण;
 *
 * For plain GEM based drivers there is the DEFINE_DRM_GEM_FOPS() macro, and क्रम
 * CMA based drivers there is the DEFINE_DRM_GEM_CMA_FOPS() macro to make this
 * simpler.
 *
 * The driver's &file_operations must be stored in &drm_driver.fops.
 *
 * For driver-निजी IOCTL handling see the more detailed discussion in
 * :ref:`IOCTL support in the userland पूर्णांकerfaces chapter<drm_driver_ioctl>`.
 */

/**
 * drm_file_alloc - allocate file context
 * @minor: minor to allocate on
 *
 * This allocates a new DRM file context. It is not linked पूर्णांकo any context and
 * can be used by the caller मुक्तly. Note that the context keeps a poपूर्णांकer to
 * @minor, so it must be मुक्तd beक्रमe @minor is.
 *
 * RETURNS:
 * Poपूर्णांकer to newly allocated context, ERR_PTR on failure.
 */
काष्ठा drm_file *drm_file_alloc(काष्ठा drm_minor *minor)
अणु
	काष्ठा drm_device *dev = minor->dev;
	काष्ठा drm_file *file;
	पूर्णांक ret;

	file = kzalloc(माप(*file), GFP_KERNEL);
	अगर (!file)
		वापस ERR_PTR(-ENOMEM);

	file->pid = get_pid(task_pid(current));
	file->minor = minor;

	/* क्रम compatibility root is always authenticated */
	file->authenticated = capable(CAP_SYS_ADMIN);

	INIT_LIST_HEAD(&file->lhead);
	INIT_LIST_HEAD(&file->fbs);
	mutex_init(&file->fbs_lock);
	INIT_LIST_HEAD(&file->blobs);
	INIT_LIST_HEAD(&file->pending_event_list);
	INIT_LIST_HEAD(&file->event_list);
	init_रुकोqueue_head(&file->event_रुको);
	file->event_space = 4096; /* set aside 4k क्रम event buffer */

	mutex_init(&file->event_पढ़ो_lock);

	अगर (drm_core_check_feature(dev, DRIVER_GEM))
		drm_gem_खोलो(dev, file);

	अगर (drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		drm_syncobj_खोलो(file);

	drm_prime_init_file_निजी(&file->prime);

	अगर (dev->driver->खोलो) अणु
		ret = dev->driver->खोलो(dev, file);
		अगर (ret < 0)
			जाओ out_prime_destroy;
	पूर्ण

	वापस file;

out_prime_destroy:
	drm_prime_destroy_file_निजी(&file->prime);
	अगर (drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		drm_syncobj_release(file);
	अगर (drm_core_check_feature(dev, DRIVER_GEM))
		drm_gem_release(dev, file);
	put_pid(file->pid);
	kमुक्त(file);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम drm_events_release(काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device *dev = file_priv->minor->dev;
	काष्ठा drm_pending_event *e, *et;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	/* Unlink pending events */
	list_क्रम_each_entry_safe(e, et, &file_priv->pending_event_list,
				 pending_link) अणु
		list_del(&e->pending_link);
		e->file_priv = शून्य;
	पूर्ण

	/* Remove unconsumed events */
	list_क्रम_each_entry_safe(e, et, &file_priv->event_list, link) अणु
		list_del(&e->link);
		kमुक्त(e);
	पूर्ण

	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

/**
 * drm_file_मुक्त - मुक्त file context
 * @file: context to मुक्त, or शून्य
 *
 * This destroys and deallocates a DRM file context previously allocated via
 * drm_file_alloc(). The caller must make sure to unlink it from any contexts
 * beक्रमe calling this.
 *
 * If शून्य is passed, this is a no-op.
 */
व्योम drm_file_मुक्त(काष्ठा drm_file *file)
अणु
	काष्ठा drm_device *dev;

	अगर (!file)
		वापस;

	dev = file->minor->dev;

	DRM_DEBUG("comm=\"%s\", pid=%d, dev=0x%lx, open_count=%d\n",
		  current->comm, task_pid_nr(current),
		  (दीर्घ)old_encode_dev(file->minor->kdev->devt),
		  atomic_पढ़ो(&dev->खोलो_count));

#अगर_घोषित CONFIG_DRM_LEGACY
	अगर (drm_core_check_feature(dev, DRIVER_LEGACY) &&
	    dev->driver->preबंद)
		dev->driver->preबंद(dev, file);
#पूर्ण_अगर

	अगर (drm_core_check_feature(dev, DRIVER_LEGACY))
		drm_legacy_lock_release(dev, file->filp);

	अगर (drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		drm_legacy_reclaim_buffers(dev, file);

	drm_events_release(file);

	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		drm_fb_release(file);
		drm_property_destroy_user_blobs(dev, file);
	पूर्ण

	अगर (drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		drm_syncobj_release(file);

	अगर (drm_core_check_feature(dev, DRIVER_GEM))
		drm_gem_release(dev, file);

	drm_legacy_ctxbiपंचांगap_flush(dev, file);

	अगर (drm_is_primary_client(file))
		drm_master_release(file);

	अगर (dev->driver->postबंद)
		dev->driver->postबंद(dev, file);

	drm_prime_destroy_file_निजी(&file->prime);

	WARN_ON(!list_empty(&file->event_list));

	put_pid(file->pid);
	kमुक्त(file);
पूर्ण

अटल व्योम drm_बंद_helper(काष्ठा file *filp)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev = file_priv->minor->dev;

	mutex_lock(&dev->filelist_mutex);
	list_del(&file_priv->lhead);
	mutex_unlock(&dev->filelist_mutex);

	drm_file_मुक्त(file_priv);
पूर्ण

/*
 * Check whether DRI will run on this CPU.
 *
 * \लeturn non-zero अगर the DRI will run on this CPU, or zero otherwise.
 */
अटल पूर्णांक drm_cpu_valid(व्योम)
अणु
#अगर defined(__sparc__) && !defined(__sparc_v9__)
	वापस 0;		/* No cmpxchg beक्रमe v9 sparc. */
#पूर्ण_अगर
	वापस 1;
पूर्ण

/*
 * Called whenever a process खोलोs a drm node
 *
 * \param filp file poपूर्णांकer.
 * \param minor acquired minor-object.
 * \लeturn zero on success or a negative number on failure.
 *
 * Creates and initializes a drm_file काष्ठाure क्रम the file निजी data in \p
 * filp and add it पूर्णांकo the द्विगुन linked list in \p dev.
 */
अटल पूर्णांक drm_खोलो_helper(काष्ठा file *filp, काष्ठा drm_minor *minor)
अणु
	काष्ठा drm_device *dev = minor->dev;
	काष्ठा drm_file *priv;
	पूर्णांक ret;

	अगर (filp->f_flags & O_EXCL)
		वापस -EBUSY;	/* No exclusive खोलोs */
	अगर (!drm_cpu_valid())
		वापस -EINVAL;
	अगर (dev->चयन_घातer_state != DRM_SWITCH_POWER_ON &&
	    dev->चयन_घातer_state != DRM_SWITCH_POWER_DYNAMIC_OFF)
		वापस -EINVAL;

	DRM_DEBUG("comm=\"%s\", pid=%d, minor=%d\n", current->comm,
		  task_pid_nr(current), minor->index);

	priv = drm_file_alloc(minor);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	अगर (drm_is_primary_client(priv)) अणु
		ret = drm_master_खोलो(priv);
		अगर (ret) अणु
			drm_file_मुक्त(priv);
			वापस ret;
		पूर्ण
	पूर्ण

	filp->निजी_data = priv;
	filp->f_mode |= FMODE_UNSIGNED_OFFSET;
	priv->filp = filp;

	mutex_lock(&dev->filelist_mutex);
	list_add(&priv->lhead, &dev->filelist);
	mutex_unlock(&dev->filelist_mutex);

#अगर_घोषित CONFIG_DRM_LEGACY
#अगर_घोषित __alpha__
	/*
	 * Default the hose
	 */
	अगर (!dev->hose) अणु
		काष्ठा pci_dev *pci_dev;

		pci_dev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, शून्य);
		अगर (pci_dev) अणु
			dev->hose = pci_dev->sysdata;
			pci_dev_put(pci_dev);
		पूर्ण
		अगर (!dev->hose) अणु
			काष्ठा pci_bus *b = list_entry(pci_root_buses.next,
				काष्ठा pci_bus, node);
			अगर (b)
				dev->hose = b->sysdata;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * drm_खोलो - खोलो method क्रम DRM file
 * @inode: device inode
 * @filp: file poपूर्णांकer.
 *
 * This function must be used by drivers as their &file_operations.खोलो method.
 * It looks up the correct DRM device and instantiates all the per-file
 * resources क्रम it. It also calls the &drm_driver.खोलो driver callback.
 *
 * RETURNS:
 *
 * 0 on success or negative त्रुटि_सं value on falure.
 */
पूर्णांक drm_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा drm_device *dev;
	काष्ठा drm_minor *minor;
	पूर्णांक retcode;
	पूर्णांक need_setup = 0;

	minor = drm_minor_acquire(iminor(inode));
	अगर (IS_ERR(minor))
		वापस PTR_ERR(minor);

	dev = minor->dev;
	अगर (drm_dev_needs_global_mutex(dev))
		mutex_lock(&drm_global_mutex);

	अगर (!atomic_fetch_inc(&dev->खोलो_count))
		need_setup = 1;

	/* share address_space across all अक्षर-devs of a single device */
	filp->f_mapping = dev->anon_inode->i_mapping;

	retcode = drm_खोलो_helper(filp, minor);
	अगर (retcode)
		जाओ err_unकरो;
	अगर (need_setup) अणु
		retcode = drm_legacy_setup(dev);
		अगर (retcode) अणु
			drm_बंद_helper(filp);
			जाओ err_unकरो;
		पूर्ण
	पूर्ण

	अगर (drm_dev_needs_global_mutex(dev))
		mutex_unlock(&drm_global_mutex);

	वापस 0;

err_unकरो:
	atomic_dec(&dev->खोलो_count);
	अगर (drm_dev_needs_global_mutex(dev))
		mutex_unlock(&drm_global_mutex);
	drm_minor_release(minor);
	वापस retcode;
पूर्ण
EXPORT_SYMBOL(drm_खोलो);

व्योम drm_lastबंद(काष्ठा drm_device * dev)
अणु
	DRM_DEBUG("\n");

	अगर (dev->driver->lastबंद)
		dev->driver->lastबंद(dev);
	DRM_DEBUG("driver lastclose completed\n");

	अगर (drm_core_check_feature(dev, DRIVER_LEGACY))
		drm_legacy_dev_reinit(dev);

	drm_client_dev_restore(dev);
पूर्ण

/**
 * drm_release - release method क्रम DRM file
 * @inode: device inode
 * @filp: file poपूर्णांकer.
 *
 * This function must be used by drivers as their &file_operations.release
 * method. It मुक्तs any resources associated with the खोलो file, and calls the
 * &drm_driver.postबंद driver callback. If this is the last खोलो file क्रम the
 * DRM device also proceeds to call the &drm_driver.lastबंद driver callback.
 *
 * RETURNS:
 *
 * Always succeeds and वापसs 0.
 */
पूर्णांक drm_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_minor *minor = file_priv->minor;
	काष्ठा drm_device *dev = minor->dev;

	अगर (drm_dev_needs_global_mutex(dev))
		mutex_lock(&drm_global_mutex);

	DRM_DEBUG("open_count = %d\n", atomic_पढ़ो(&dev->खोलो_count));

	drm_बंद_helper(filp);

	अगर (atomic_dec_and_test(&dev->खोलो_count))
		drm_lastबंद(dev);

	अगर (drm_dev_needs_global_mutex(dev))
		mutex_unlock(&drm_global_mutex);

	drm_minor_release(minor);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_release);

/**
 * drm_release_noglobal - release method क्रम DRM file
 * @inode: device inode
 * @filp: file poपूर्णांकer.
 *
 * This function may be used by drivers as their &file_operations.release
 * method. It मुक्तs any resources associated with the खोलो file prior to taking
 * the drm_global_mutex, which then calls the &drm_driver.postबंद driver
 * callback. If this is the last खोलो file क्रम the DRM device also proceeds to
 * call the &drm_driver.lastबंद driver callback.
 *
 * RETURNS:
 *
 * Always succeeds and वापसs 0.
 */
पूर्णांक drm_release_noglobal(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_minor *minor = file_priv->minor;
	काष्ठा drm_device *dev = minor->dev;

	drm_बंद_helper(filp);

	अगर (atomic_dec_and_mutex_lock(&dev->खोलो_count, &drm_global_mutex)) अणु
		drm_lastबंद(dev);
		mutex_unlock(&drm_global_mutex);
	पूर्ण

	drm_minor_release(minor);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_release_noglobal);

/**
 * drm_पढ़ो - पढ़ो method क्रम DRM file
 * @filp: file poपूर्णांकer
 * @buffer: userspace destination poपूर्णांकer क्रम the पढ़ो
 * @count: count in bytes to पढ़ो
 * @offset: offset to पढ़ो
 *
 * This function must be used by drivers as their &file_operations.पढ़ो
 * method अगरf they use DRM events क्रम asynchronous संकेतling to userspace.
 * Since events are used by the KMS API क्रम vblank and page flip completion this
 * means all modern display drivers must use it.
 *
 * @offset is ignored, DRM events are पढ़ो like a pipe. Thereक्रमe drivers also
 * must set the &file_operation.llseek to no_llseek(). Polling support is
 * provided by drm_poll().
 *
 * This function will only ever पढ़ो a full event. Thereक्रमe userspace must
 * supply a big enough buffer to fit any event to ensure क्रमward progress. Since
 * the maximum event space is currently 4K it's recommended to just use that क्रम
 * safety.
 *
 * RETURNS:
 *
 * Number of bytes पढ़ो (always aligned to full events, and can be 0) or a
 * negative error code on failure.
 */
sमाप_प्रकार drm_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
		 माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev = file_priv->minor->dev;
	sमाप_प्रकार ret;

	ret = mutex_lock_पूर्णांकerruptible(&file_priv->event_पढ़ो_lock);
	अगर (ret)
		वापस ret;

	क्रम (;;) अणु
		काष्ठा drm_pending_event *e = शून्य;

		spin_lock_irq(&dev->event_lock);
		अगर (!list_empty(&file_priv->event_list)) अणु
			e = list_first_entry(&file_priv->event_list,
					काष्ठा drm_pending_event, link);
			file_priv->event_space += e->event->length;
			list_del(&e->link);
		पूर्ण
		spin_unlock_irq(&dev->event_lock);

		अगर (e == शून्य) अणु
			अगर (ret)
				अवरोध;

			अगर (filp->f_flags & O_NONBLOCK) अणु
				ret = -EAGAIN;
				अवरोध;
			पूर्ण

			mutex_unlock(&file_priv->event_पढ़ो_lock);
			ret = रुको_event_पूर्णांकerruptible(file_priv->event_रुको,
						       !list_empty(&file_priv->event_list));
			अगर (ret >= 0)
				ret = mutex_lock_पूर्णांकerruptible(&file_priv->event_पढ़ो_lock);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			अचिन्हित length = e->event->length;

			अगर (length > count - ret) अणु
put_back_event:
				spin_lock_irq(&dev->event_lock);
				file_priv->event_space -= length;
				list_add(&e->link, &file_priv->event_list);
				spin_unlock_irq(&dev->event_lock);
				wake_up_पूर्णांकerruptible_poll(&file_priv->event_रुको,
					EPOLLIN | EPOLLRDNORM);
				अवरोध;
			पूर्ण

			अगर (copy_to_user(buffer + ret, e->event, length)) अणु
				अगर (ret == 0)
					ret = -EFAULT;
				जाओ put_back_event;
			पूर्ण

			ret += length;
			kमुक्त(e);
		पूर्ण
	पूर्ण
	mutex_unlock(&file_priv->event_पढ़ो_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_पढ़ो);

/**
 * drm_poll - poll method क्रम DRM file
 * @filp: file poपूर्णांकer
 * @रुको: poll रुकोer table
 *
 * This function must be used by drivers as their &file_operations.पढ़ो method
 * अगरf they use DRM events क्रम asynchronous संकेतling to userspace.  Since
 * events are used by the KMS API क्रम vblank and page flip completion this means
 * all modern display drivers must use it.
 *
 * See also drm_पढ़ो().
 *
 * RETURNS:
 *
 * Mask of POLL flags indicating the current status of the file.
 */
__poll_t drm_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &file_priv->event_रुको, रुको);

	अगर (!list_empty(&file_priv->event_list))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण
EXPORT_SYMBOL(drm_poll);

/**
 * drm_event_reserve_init_locked - init a DRM event and reserve space क्रम it
 * @dev: DRM device
 * @file_priv: DRM file निजी data
 * @p: tracking काष्ठाure क्रम the pending event
 * @e: actual event data to deliver to userspace
 *
 * This function prepares the passed in event क्रम eventual delivery. If the event
 * करोesn't get delivered (because the IOCTL fails later on, beक्रमe queuing up
 * anything) then the even must be cancelled and मुक्तd using
 * drm_event_cancel_मुक्त(). Successfully initialized events should be sent out
 * using drm_send_event() or drm_send_event_locked() to संकेत completion of the
 * asynchronous event to userspace.
 *
 * If callers embedded @p पूर्णांकo a larger काष्ठाure it must be allocated with
 * kदो_स्मृति and @p must be the first member element.
 *
 * This is the locked version of drm_event_reserve_init() क्रम callers which
 * alपढ़ोy hold &drm_device.event_lock.
 *
 * RETURNS:
 *
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_event_reserve_init_locked(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_priv,
				  काष्ठा drm_pending_event *p,
				  काष्ठा drm_event *e)
अणु
	अगर (file_priv->event_space < e->length)
		वापस -ENOMEM;

	file_priv->event_space -= e->length;

	p->event = e;
	list_add(&p->pending_link, &file_priv->pending_event_list);
	p->file_priv = file_priv;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_event_reserve_init_locked);

/**
 * drm_event_reserve_init - init a DRM event and reserve space क्रम it
 * @dev: DRM device
 * @file_priv: DRM file निजी data
 * @p: tracking काष्ठाure क्रम the pending event
 * @e: actual event data to deliver to userspace
 *
 * This function prepares the passed in event क्रम eventual delivery. If the event
 * करोesn't get delivered (because the IOCTL fails later on, beक्रमe queuing up
 * anything) then the even must be cancelled and मुक्तd using
 * drm_event_cancel_मुक्त(). Successfully initialized events should be sent out
 * using drm_send_event() or drm_send_event_locked() to संकेत completion of the
 * asynchronous event to userspace.
 *
 * If callers embedded @p पूर्णांकo a larger काष्ठाure it must be allocated with
 * kदो_स्मृति and @p must be the first member element.
 *
 * Callers which alपढ़ोy hold &drm_device.event_lock should use
 * drm_event_reserve_init_locked() instead.
 *
 * RETURNS:
 *
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_event_reserve_init(काष्ठा drm_device *dev,
			   काष्ठा drm_file *file_priv,
			   काष्ठा drm_pending_event *p,
			   काष्ठा drm_event *e)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&dev->event_lock, flags);
	ret = drm_event_reserve_init_locked(dev, file_priv, p, e);
	spin_unlock_irqrestore(&dev->event_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_event_reserve_init);

/**
 * drm_event_cancel_मुक्त - मुक्त a DRM event and release its space
 * @dev: DRM device
 * @p: tracking काष्ठाure क्रम the pending event
 *
 * This function मुक्तs the event @p initialized with drm_event_reserve_init()
 * and releases any allocated space. It is used to cancel an event when the
 * nonblocking operation could not be submitted and needed to be पातed.
 */
व्योम drm_event_cancel_मुक्त(काष्ठा drm_device *dev,
			   काष्ठा drm_pending_event *p)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (p->file_priv) अणु
		p->file_priv->event_space += p->event->length;
		list_del(&p->pending_link);
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);

	अगर (p->fence)
		dma_fence_put(p->fence);

	kमुक्त(p);
पूर्ण
EXPORT_SYMBOL(drm_event_cancel_मुक्त);

/**
 * drm_send_event_helper - send DRM event to file descriptor
 * @dev: DRM device
 * @e: DRM event to deliver
 * @बारtamp: बारtamp to set क्रम the fence event in kernel's CLOCK_MONOTONIC
 * समय करोमुख्य
 *
 * This helper function sends the event @e, initialized with
 * drm_event_reserve_init(), to its associated userspace DRM file.
 * The बारtamp variant of dma_fence_संकेत is used when the caller
 * sends a valid बारtamp.
 */
व्योम drm_send_event_helper(काष्ठा drm_device *dev,
			   काष्ठा drm_pending_event *e, kसमय_प्रकार बारtamp)
अणु
	निश्चित_spin_locked(&dev->event_lock);

	अगर (e->completion) अणु
		complete_all(e->completion);
		e->completion_release(e->completion);
		e->completion = शून्य;
	पूर्ण

	अगर (e->fence) अणु
		अगर (बारtamp)
			dma_fence_संकेत_बारtamp(e->fence, बारtamp);
		अन्यथा
			dma_fence_संकेत(e->fence);
		dma_fence_put(e->fence);
	पूर्ण

	अगर (!e->file_priv) अणु
		kमुक्त(e);
		वापस;
	पूर्ण

	list_del(&e->pending_link);
	list_add_tail(&e->link,
		      &e->file_priv->event_list);
	wake_up_पूर्णांकerruptible_poll(&e->file_priv->event_रुको,
		EPOLLIN | EPOLLRDNORM);
पूर्ण

/**
 * drm_send_event_बारtamp_locked - send DRM event to file descriptor
 * @dev: DRM device
 * @e: DRM event to deliver
 * @बारtamp: बारtamp to set क्रम the fence event in kernel's CLOCK_MONOTONIC
 * समय करोमुख्य
 *
 * This function sends the event @e, initialized with drm_event_reserve_init(),
 * to its associated userspace DRM file. Callers must alपढ़ोy hold
 * &drm_device.event_lock.
 *
 * Note that the core will take care of unlinking and disarming events when the
 * corresponding DRM file is बंदd. Drivers need not worry about whether the
 * DRM file क्रम this event still exists and can call this function upon
 * completion of the asynchronous work unconditionally.
 */
व्योम drm_send_event_बारtamp_locked(काष्ठा drm_device *dev,
				     काष्ठा drm_pending_event *e, kसमय_प्रकार बारtamp)
अणु
	drm_send_event_helper(dev, e, बारtamp);
पूर्ण
EXPORT_SYMBOL(drm_send_event_बारtamp_locked);

/**
 * drm_send_event_locked - send DRM event to file descriptor
 * @dev: DRM device
 * @e: DRM event to deliver
 *
 * This function sends the event @e, initialized with drm_event_reserve_init(),
 * to its associated userspace DRM file. Callers must alपढ़ोy hold
 * &drm_device.event_lock, see drm_send_event() क्रम the unlocked version.
 *
 * Note that the core will take care of unlinking and disarming events when the
 * corresponding DRM file is बंदd. Drivers need not worry about whether the
 * DRM file क्रम this event still exists and can call this function upon
 * completion of the asynchronous work unconditionally.
 */
व्योम drm_send_event_locked(काष्ठा drm_device *dev, काष्ठा drm_pending_event *e)
अणु
	drm_send_event_helper(dev, e, 0);
पूर्ण
EXPORT_SYMBOL(drm_send_event_locked);

/**
 * drm_send_event - send DRM event to file descriptor
 * @dev: DRM device
 * @e: DRM event to deliver
 *
 * This function sends the event @e, initialized with drm_event_reserve_init(),
 * to its associated userspace DRM file. This function acquires
 * &drm_device.event_lock, see drm_send_event_locked() क्रम callers which alपढ़ोy
 * hold this lock.
 *
 * Note that the core will take care of unlinking and disarming events when the
 * corresponding DRM file is बंदd. Drivers need not worry about whether the
 * DRM file क्रम this event still exists and can call this function upon
 * completion of the asynchronous work unconditionally.
 */
व्योम drm_send_event(काष्ठा drm_device *dev, काष्ठा drm_pending_event *e)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev->event_lock, irqflags);
	drm_send_event_helper(dev, e, 0);
	spin_unlock_irqrestore(&dev->event_lock, irqflags);
पूर्ण
EXPORT_SYMBOL(drm_send_event);

/**
 * mock_drm_getfile - Create a new काष्ठा file क्रम the drm device
 * @minor: drm minor to wrap (e.g. #drm_device.primary)
 * @flags: file creation mode (O_RDWR etc)
 *
 * This create a new काष्ठा file that wraps a DRM file context around a
 * DRM minor. This mimicks userspace खोलोing e.g. /dev/dri/card0, but without
 * invoking userspace. The काष्ठा file may be operated on using its f_op
 * (the drm_device.driver.fops) to mimick userspace operations, or be supplied
 * to userspace facing functions as an पूर्णांकernal/anonymous client.
 *
 * RETURNS:
 * Poपूर्णांकer to newly created काष्ठा file, ERR_PTR on failure.
 */
काष्ठा file *mock_drm_getfile(काष्ठा drm_minor *minor, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_device *dev = minor->dev;
	काष्ठा drm_file *priv;
	काष्ठा file *file;

	priv = drm_file_alloc(minor);
	अगर (IS_ERR(priv))
		वापस ERR_CAST(priv);

	file = anon_inode_getfile("drm", dev->driver->fops, priv, flags);
	अगर (IS_ERR(file)) अणु
		drm_file_मुक्त(priv);
		वापस file;
	पूर्ण

	/* Everyone shares a single global address space */
	file->f_mapping = dev->anon_inode->i_mapping;

	drm_dev_get(dev);
	priv->filp = file;

	वापस file;
पूर्ण
EXPORT_SYMBOL_FOR_TESTS_ONLY(mock_drm_getfile);

#अगर_घोषित CONFIG_MMU
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * drm_addr_inflate() attempts to स्थिरruct an aligned area by inflating
 * the area size and skipping the unaligned start of the area.
 * adapted from shmem_get_unmapped_area()
 */
अटल अचिन्हित दीर्घ drm_addr_inflate(अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ len,
				      अचिन्हित दीर्घ pgoff,
				      अचिन्हित दीर्घ flags,
				      अचिन्हित दीर्घ huge_size)
अणु
	अचिन्हित दीर्घ offset, inflated_len;
	अचिन्हित दीर्घ inflated_addr;
	अचिन्हित दीर्घ inflated_offset;

	offset = (pgoff << PAGE_SHIFT) & (huge_size - 1);
	अगर (offset && offset + len < 2 * huge_size)
		वापस addr;
	अगर ((addr & (huge_size - 1)) == offset)
		वापस addr;

	inflated_len = len + huge_size - PAGE_SIZE;
	अगर (inflated_len > TASK_SIZE)
		वापस addr;
	अगर (inflated_len < len)
		वापस addr;

	inflated_addr = current->mm->get_unmapped_area(शून्य, 0, inflated_len,
						       0, flags);
	अगर (IS_ERR_VALUE(inflated_addr))
		वापस addr;
	अगर (inflated_addr & ~PAGE_MASK)
		वापस addr;

	inflated_offset = inflated_addr & (huge_size - 1);
	inflated_addr += offset - inflated_offset;
	अगर (inflated_offset > offset)
		inflated_addr += huge_size;

	अगर (inflated_addr > TASK_SIZE - len)
		वापस addr;

	वापस inflated_addr;
पूर्ण

/**
 * drm_get_unmapped_area() - Get an unused user-space भव memory area
 * suitable क्रम huge page table entries.
 * @file: The काष्ठा file representing the address space being mmap()'d.
 * @uaddr: Start address suggested by user-space.
 * @len: Length of the area.
 * @pgoff: The page offset पूर्णांकo the address space.
 * @flags: mmap flags
 * @mgr: The address space manager used by the drm driver. This argument can
 * probably be हटाओd at some poपूर्णांक when all drivers use the same
 * address space manager.
 *
 * This function attempts to find an unused user-space भव memory area
 * that can accommodate the size we want to map, and that is properly
 * aligned to facilitate huge page table entries matching actual
 * huge pages or huge page aligned memory in buffer objects. Buffer objects
 * are assumed to start at huge page boundary pfns (io memory) or be
 * populated by huge pages aligned to the start of the buffer object
 * (प्रणाली- or coherent memory). Adapted from shmem_get_unmapped_area.
 *
 * Return: aligned user-space address.
 */
अचिन्हित दीर्घ drm_get_unmapped_area(काष्ठा file *file,
				    अचिन्हित दीर्घ uaddr, अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags,
				    काष्ठा drm_vma_offset_manager *mgr)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ inflated_addr;
	काष्ठा drm_vma_offset_node *node;

	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	/*
	 * @pgoff is the file page-offset the huge page boundaries of
	 * which typically aligns to physical address huge page boundaries.
	 * That's not true क्रम DRM, however, where physical address huge
	 * page boundaries instead are aligned with the offset from
	 * buffer object start. So adjust @pgoff to be the offset from
	 * buffer object start.
	 */
	drm_vma_offset_lock_lookup(mgr);
	node = drm_vma_offset_lookup_locked(mgr, pgoff, 1);
	अगर (node)
		pgoff -= node->vm_node.start;
	drm_vma_offset_unlock_lookup(mgr);

	addr = current->mm->get_unmapped_area(file, uaddr, len, pgoff, flags);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;
	अगर (addr & ~PAGE_MASK)
		वापस addr;
	अगर (addr > TASK_SIZE - len)
		वापस addr;

	अगर (len < HPAGE_PMD_SIZE)
		वापस addr;
	अगर (flags & MAP_FIXED)
		वापस addr;
	/*
	 * Our priority is to support MAP_SHARED mapped hugely;
	 * and support MAP_PRIVATE mapped hugely too, until it is COWed.
	 * But अगर caller specअगरied an address hपूर्णांक, respect that as beक्रमe.
	 */
	अगर (uaddr)
		वापस addr;

	inflated_addr = drm_addr_inflate(addr, len, pgoff, flags,
					 HPAGE_PMD_SIZE);

	अगर (IS_ENABLED(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD) &&
	    len >= HPAGE_PUD_SIZE)
		inflated_addr = drm_addr_inflate(inflated_addr, len, pgoff,
						 flags, HPAGE_PUD_SIZE);
	वापस inflated_addr;
पूर्ण
#अन्यथा /* CONFIG_TRANSPARENT_HUGEPAGE */
अचिन्हित दीर्घ drm_get_unmapped_area(काष्ठा file *file,
				    अचिन्हित दीर्घ uaddr, अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags,
				    काष्ठा drm_vma_offset_manager *mgr)
अणु
	वापस current->mm->get_unmapped_area(file, uaddr, len, pgoff, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
EXPORT_SYMBOL_GPL(drm_get_unmapped_area);
#पूर्ण_अगर /* CONFIG_MMU */
