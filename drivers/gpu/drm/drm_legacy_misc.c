<शैली गुरु>
/*
 * \पile drm_legacy_misc.c
 * Misc legacy support functions.
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

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

व्योम drm_legacy_init_members(काष्ठा drm_device *dev)
अणु
	INIT_LIST_HEAD(&dev->ctxlist);
	INIT_LIST_HEAD(&dev->vmalist);
	INIT_LIST_HEAD(&dev->maplist);
	spin_lock_init(&dev->buf_lock);
	mutex_init(&dev->ctxlist_mutex);
पूर्ण

व्योम drm_legacy_destroy_members(काष्ठा drm_device *dev)
अणु
	mutex_destroy(&dev->ctxlist_mutex);
पूर्ण

पूर्णांक drm_legacy_setup(काष्ठा drm_device * dev)
अणु
	पूर्णांक ret;

	अगर (dev->driver->firstखोलो &&
	    drm_core_check_feature(dev, DRIVER_LEGACY)) अणु
		ret = dev->driver->firstखोलो(dev);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	ret = drm_legacy_dma_setup(dev);
	अगर (ret < 0)
		वापस ret;


	DRM_DEBUG("\n");
	वापस 0;
पूर्ण

व्योम drm_legacy_dev_reinit(काष्ठा drm_device *dev)
अणु
	अगर (dev->irq_enabled)
		drm_irq_uninstall(dev);

	mutex_lock(&dev->काष्ठा_mutex);

	drm_legacy_agp_clear(dev);

	drm_legacy_sg_cleanup(dev);
	drm_legacy_vma_flush(dev);
	drm_legacy_dma_takeकरोwn(dev);

	mutex_unlock(&dev->काष्ठा_mutex);

	dev->sigdata.lock = शून्य;

	dev->context_flag = 0;
	dev->last_context = 0;
	dev->अगर_version = 0;

	DRM_DEBUG("lastclose completed\n");
पूर्ण

व्योम drm_master_legacy_init(काष्ठा drm_master *master)
अणु
	spin_lock_init(&master->lock.spinlock);
	init_रुकोqueue_head(&master->lock.lock_queue);
पूर्ण
