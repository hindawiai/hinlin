<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * v4l2-fh.c
 *
 * V4L2 file handles.
 *
 * Copyright (C) 2009--2010 Nokia Corporation.
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>

व्योम v4l2_fh_init(काष्ठा v4l2_fh *fh, काष्ठा video_device *vdev)
अणु
	fh->vdev = vdev;
	/* Inherit from video_device. May be overridden by the driver. */
	fh->ctrl_handler = vdev->ctrl_handler;
	INIT_LIST_HEAD(&fh->list);
	set_bit(V4L2_FL_USES_V4L2_FH, &fh->vdev->flags);
	/*
	 * determine_valid_ioctls() करोes not know अगर काष्ठा v4l2_fh
	 * is used by this driver, but here we करो. So enable the
	 * prio ioctls here.
	 */
	set_bit(_IOC_NR(VIDIOC_G_PRIORITY), vdev->valid_ioctls);
	set_bit(_IOC_NR(VIDIOC_S_PRIORITY), vdev->valid_ioctls);
	fh->prio = V4L2_PRIORITY_UNSET;
	init_रुकोqueue_head(&fh->रुको);
	INIT_LIST_HEAD(&fh->available);
	INIT_LIST_HEAD(&fh->subscribed);
	fh->sequence = -1;
	mutex_init(&fh->subscribe_lock);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_init);

व्योम v4l2_fh_add(काष्ठा v4l2_fh *fh)
अणु
	अचिन्हित दीर्घ flags;

	v4l2_prio_खोलो(fh->vdev->prio, &fh->prio);
	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	list_add(&fh->list, &fh->vdev->fh_list);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_add);

पूर्णांक v4l2_fh_खोलो(काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	काष्ठा v4l2_fh *fh = kzalloc(माप(*fh), GFP_KERNEL);

	filp->निजी_data = fh;
	अगर (fh == शून्य)
		वापस -ENOMEM;
	v4l2_fh_init(fh, vdev);
	v4l2_fh_add(fh);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_खोलो);

व्योम v4l2_fh_del(काष्ठा v4l2_fh *fh)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	list_del_init(&fh->list);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
	v4l2_prio_बंद(fh->vdev->prio, fh->prio);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_del);

व्योम v4l2_fh_निकास(काष्ठा v4l2_fh *fh)
अणु
	अगर (fh->vdev == शून्य)
		वापस;
	v4l_disable_media_source(fh->vdev);
	v4l2_event_unsubscribe_all(fh);
	mutex_destroy(&fh->subscribe_lock);
	fh->vdev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_निकास);

पूर्णांक v4l2_fh_release(काष्ठा file *filp)
अणु
	काष्ठा v4l2_fh *fh = filp->निजी_data;

	अगर (fh) अणु
		v4l2_fh_del(fh);
		v4l2_fh_निकास(fh);
		kमुक्त(fh);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_release);

पूर्णांक v4l2_fh_is_singular(काष्ठा v4l2_fh *fh)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक is_singular;

	अगर (fh == शून्य || fh->vdev == शून्य)
		वापस 0;
	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	is_singular = list_is_singular(&fh->list);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
	वापस is_singular;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fh_is_singular);
