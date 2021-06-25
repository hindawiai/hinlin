<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Media device request objects
 *
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 * Copyright (C) 2018 Intel Corporation
 * Copyright (C) 2018 Google, Inc.
 *
 * Author: Hans Verkuil <hans.verkuil@cisco.com>
 * Author: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/file.h>
#समावेश <linux/refcount.h>

#समावेश <media/media-device.h>
#समावेश <media/media-request.h>

अटल स्थिर अक्षर * स्थिर request_state[] = अणु
	[MEDIA_REQUEST_STATE_IDLE]	 = "idle",
	[MEDIA_REQUEST_STATE_VALIDATING] = "validating",
	[MEDIA_REQUEST_STATE_QUEUED]	 = "queued",
	[MEDIA_REQUEST_STATE_COMPLETE]	 = "complete",
	[MEDIA_REQUEST_STATE_CLEANING]	 = "cleaning",
	[MEDIA_REQUEST_STATE_UPDATING]	 = "updating",
पूर्ण;

अटल स्थिर अक्षर *
media_request_state_str(क्रमागत media_request_state state)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(request_state) != NR_OF_MEDIA_REQUEST_STATE);

	अगर (WARN_ON(state >= ARRAY_SIZE(request_state)))
		वापस "invalid";
	वापस request_state[state];
पूर्ण

अटल व्योम media_request_clean(काष्ठा media_request *req)
अणु
	काष्ठा media_request_object *obj, *obj_safe;

	/* Just a sanity check. No other code path is allowed to change this. */
	WARN_ON(req->state != MEDIA_REQUEST_STATE_CLEANING);
	WARN_ON(req->updating_count);
	WARN_ON(req->access_count);

	list_क्रम_each_entry_safe(obj, obj_safe, &req->objects, list) अणु
		media_request_object_unbind(obj);
		media_request_object_put(obj);
	पूर्ण

	req->updating_count = 0;
	req->access_count = 0;
	WARN_ON(req->num_incomplete_objects);
	req->num_incomplete_objects = 0;
	wake_up_पूर्णांकerruptible_all(&req->poll_रुको);
पूर्ण

अटल व्योम media_request_release(काष्ठा kref *kref)
अणु
	काष्ठा media_request *req =
		container_of(kref, काष्ठा media_request, kref);
	काष्ठा media_device *mdev = req->mdev;

	dev_dbg(mdev->dev, "request: release %s\n", req->debug_str);

	/* No other users, no need क्रम a spinlock */
	req->state = MEDIA_REQUEST_STATE_CLEANING;

	media_request_clean(req);

	अगर (mdev->ops->req_मुक्त)
		mdev->ops->req_मुक्त(req);
	अन्यथा
		kमुक्त(req);
पूर्ण

व्योम media_request_put(काष्ठा media_request *req)
अणु
	kref_put(&req->kref, media_request_release);
पूर्ण
EXPORT_SYMBOL_GPL(media_request_put);

अटल पूर्णांक media_request_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा media_request *req = filp->निजी_data;

	media_request_put(req);
	वापस 0;
पूर्ण

अटल __poll_t media_request_poll(काष्ठा file *filp,
				   काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा media_request *req = filp->निजी_data;
	अचिन्हित दीर्घ flags;
	__poll_t ret = 0;

	अगर (!(poll_requested_events(रुको) & EPOLLPRI))
		वापस 0;

	poll_रुको(filp, &req->poll_रुको, रुको);
	spin_lock_irqsave(&req->lock, flags);
	अगर (req->state == MEDIA_REQUEST_STATE_COMPLETE) अणु
		ret = EPOLLPRI;
		जाओ unlock;
	पूर्ण
	अगर (req->state != MEDIA_REQUEST_STATE_QUEUED) अणु
		ret = EPOLLERR;
		जाओ unlock;
	पूर्ण

unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	वापस ret;
पूर्ण

अटल दीर्घ media_request_ioctl_queue(काष्ठा media_request *req)
अणु
	काष्ठा media_device *mdev = req->mdev;
	क्रमागत media_request_state state;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(mdev->dev, "request: queue %s\n", req->debug_str);

	/*
	 * Ensure the request that is validated will be the one that माला_लो queued
	 * next by serialising the queueing process. This mutex is also used
	 * to serialize with canceling a vb2 queue and with setting values such
	 * as controls in a request.
	 */
	mutex_lock(&mdev->req_queue_mutex);

	media_request_get(req);

	spin_lock_irqsave(&req->lock, flags);
	अगर (req->state == MEDIA_REQUEST_STATE_IDLE)
		req->state = MEDIA_REQUEST_STATE_VALIDATING;
	state = req->state;
	spin_unlock_irqrestore(&req->lock, flags);
	अगर (state != MEDIA_REQUEST_STATE_VALIDATING) अणु
		dev_dbg(mdev->dev,
			"request: unable to queue %s, request in state %s\n",
			req->debug_str, media_request_state_str(state));
		media_request_put(req);
		mutex_unlock(&mdev->req_queue_mutex);
		वापस -EBUSY;
	पूर्ण

	ret = mdev->ops->req_validate(req);

	/*
	 * If the req_validate was successful, then we mark the state as QUEUED
	 * and call req_queue. The reason we set the state first is that this
	 * allows req_queue to unbind or complete the queued objects in हाल
	 * they are immediately 'consumed'. State changes from QUEUED to another
	 * state can only happen अगर either the driver changes the state or अगर
	 * the user cancels the vb2 queue. The driver can only change the state
	 * after each object is queued through the req_queue op (and note that
	 * that op cannot fail), so setting the state to QUEUED up front is
	 * safe.
	 *
	 * The other reason क्रम changing the state is अगर the vb2 queue is
	 * canceled, and that uses the req_queue_mutex which is still locked
	 * जबतक req_queue is called, so that's safe as well.
	 */
	spin_lock_irqsave(&req->lock, flags);
	req->state = ret ? MEDIA_REQUEST_STATE_IDLE
			 : MEDIA_REQUEST_STATE_QUEUED;
	spin_unlock_irqrestore(&req->lock, flags);

	अगर (!ret)
		mdev->ops->req_queue(req);

	mutex_unlock(&mdev->req_queue_mutex);

	अगर (ret) अणु
		dev_dbg(mdev->dev, "request: can't queue %s (%d)\n",
			req->debug_str, ret);
		media_request_put(req);
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ media_request_ioctl_reinit(काष्ठा media_request *req)
अणु
	काष्ठा media_device *mdev = req->mdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&req->lock, flags);
	अगर (req->state != MEDIA_REQUEST_STATE_IDLE &&
	    req->state != MEDIA_REQUEST_STATE_COMPLETE) अणु
		dev_dbg(mdev->dev,
			"request: %s not in idle or complete state, cannot reinit\n",
			req->debug_str);
		spin_unlock_irqrestore(&req->lock, flags);
		वापस -EBUSY;
	पूर्ण
	अगर (req->access_count) अणु
		dev_dbg(mdev->dev,
			"request: %s is being accessed, cannot reinit\n",
			req->debug_str);
		spin_unlock_irqrestore(&req->lock, flags);
		वापस -EBUSY;
	पूर्ण
	req->state = MEDIA_REQUEST_STATE_CLEANING;
	spin_unlock_irqrestore(&req->lock, flags);

	media_request_clean(req);

	spin_lock_irqsave(&req->lock, flags);
	req->state = MEDIA_REQUEST_STATE_IDLE;
	spin_unlock_irqrestore(&req->lock, flags);

	वापस 0;
पूर्ण

अटल दीर्घ media_request_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा media_request *req = filp->निजी_data;

	चयन (cmd) अणु
	हाल MEDIA_REQUEST_IOC_QUEUE:
		वापस media_request_ioctl_queue(req);
	हाल MEDIA_REQUEST_IOC_REINIT:
		वापस media_request_ioctl_reinit(req);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations request_fops = अणु
	.owner = THIS_MODULE,
	.poll = media_request_poll,
	.unlocked_ioctl = media_request_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = media_request_ioctl,
#पूर्ण_अगर /* CONFIG_COMPAT */
	.release = media_request_बंद,
पूर्ण;

काष्ठा media_request *
media_request_get_by_fd(काष्ठा media_device *mdev, पूर्णांक request_fd)
अणु
	काष्ठा fd f;
	काष्ठा media_request *req;

	अगर (!mdev || !mdev->ops ||
	    !mdev->ops->req_validate || !mdev->ops->req_queue)
		वापस ERR_PTR(-EBADR);

	f = fdget(request_fd);
	अगर (!f.file)
		जाओ err_no_req_fd;

	अगर (f.file->f_op != &request_fops)
		जाओ err_fput;
	req = f.file->निजी_data;
	अगर (req->mdev != mdev)
		जाओ err_fput;

	/*
	 * Note: as दीर्घ as someone has an खोलो filehandle of the request,
	 * the request can never be released. The fdget() above ensures that
	 * even अगर userspace बंदs the request filehandle, the release()
	 * fop won't be called, so the media_request_get() always succeeds
	 * and there is no race condition where the request was released
	 * beक्रमe media_request_get() is called.
	 */
	media_request_get(req);
	fdput(f);

	वापस req;

err_fput:
	fdput(f);

err_no_req_fd:
	dev_dbg(mdev->dev, "cannot find request_fd %d\n", request_fd);
	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(media_request_get_by_fd);

पूर्णांक media_request_alloc(काष्ठा media_device *mdev, पूर्णांक *alloc_fd)
अणु
	काष्ठा media_request *req;
	काष्ठा file *filp;
	पूर्णांक fd;
	पूर्णांक ret;

	/* Either both are शून्य or both are non-शून्य */
	अगर (WARN_ON(!mdev->ops->req_alloc ^ !mdev->ops->req_मुक्त))
		वापस -ENOMEM;

	अगर (mdev->ops->req_alloc)
		req = mdev->ops->req_alloc(mdev);
	अन्यथा
		req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fd < 0) अणु
		ret = fd;
		जाओ err_मुक्त_req;
	पूर्ण

	filp = anon_inode_getfile("request", &request_fops, शून्य, O_CLOEXEC);
	अगर (IS_ERR(filp)) अणु
		ret = PTR_ERR(filp);
		जाओ err_put_fd;
	पूर्ण

	filp->निजी_data = req;
	req->mdev = mdev;
	req->state = MEDIA_REQUEST_STATE_IDLE;
	req->num_incomplete_objects = 0;
	kref_init(&req->kref);
	INIT_LIST_HEAD(&req->objects);
	spin_lock_init(&req->lock);
	init_रुकोqueue_head(&req->poll_रुको);
	req->updating_count = 0;
	req->access_count = 0;

	*alloc_fd = fd;

	snम_लिखो(req->debug_str, माप(req->debug_str), "%u:%d",
		 atomic_inc_वापस(&mdev->request_id), fd);
	dev_dbg(mdev->dev, "request: allocated %s\n", req->debug_str);

	fd_install(fd, filp);

	वापस 0;

err_put_fd:
	put_unused_fd(fd);

err_मुक्त_req:
	अगर (mdev->ops->req_मुक्त)
		mdev->ops->req_मुक्त(req);
	अन्यथा
		kमुक्त(req);

	वापस ret;
पूर्ण

अटल व्योम media_request_object_release(काष्ठा kref *kref)
अणु
	काष्ठा media_request_object *obj =
		container_of(kref, काष्ठा media_request_object, kref);
	काष्ठा media_request *req = obj->req;

	अगर (WARN_ON(req))
		media_request_object_unbind(obj);
	obj->ops->release(obj);
पूर्ण

काष्ठा media_request_object *
media_request_object_find(काष्ठा media_request *req,
			  स्थिर काष्ठा media_request_object_ops *ops,
			  व्योम *priv)
अणु
	काष्ठा media_request_object *obj;
	काष्ठा media_request_object *found = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!ops || !priv))
		वापस शून्य;

	spin_lock_irqsave(&req->lock, flags);
	list_क्रम_each_entry(obj, &req->objects, list) अणु
		अगर (obj->ops == ops && obj->priv == priv) अणु
			media_request_object_get(obj);
			found = obj;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&req->lock, flags);
	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(media_request_object_find);

व्योम media_request_object_put(काष्ठा media_request_object *obj)
अणु
	kref_put(&obj->kref, media_request_object_release);
पूर्ण
EXPORT_SYMBOL_GPL(media_request_object_put);

व्योम media_request_object_init(काष्ठा media_request_object *obj)
अणु
	obj->ops = शून्य;
	obj->req = शून्य;
	obj->priv = शून्य;
	obj->completed = false;
	INIT_LIST_HEAD(&obj->list);
	kref_init(&obj->kref);
पूर्ण
EXPORT_SYMBOL_GPL(media_request_object_init);

पूर्णांक media_request_object_bind(काष्ठा media_request *req,
			      स्थिर काष्ठा media_request_object_ops *ops,
			      व्योम *priv, bool is_buffer,
			      काष्ठा media_request_object *obj)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EBUSY;

	अगर (WARN_ON(!ops->release))
		वापस -EBADR;

	spin_lock_irqsave(&req->lock, flags);

	अगर (WARN_ON(req->state != MEDIA_REQUEST_STATE_UPDATING))
		जाओ unlock;

	obj->req = req;
	obj->ops = ops;
	obj->priv = priv;

	अगर (is_buffer)
		list_add_tail(&obj->list, &req->objects);
	अन्यथा
		list_add(&obj->list, &req->objects);
	req->num_incomplete_objects++;
	ret = 0;

unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(media_request_object_bind);

व्योम media_request_object_unbind(काष्ठा media_request_object *obj)
अणु
	काष्ठा media_request *req = obj->req;
	अचिन्हित दीर्घ flags;
	bool completed = false;

	अगर (WARN_ON(!req))
		वापस;

	spin_lock_irqsave(&req->lock, flags);
	list_del(&obj->list);
	obj->req = शून्य;

	अगर (req->state == MEDIA_REQUEST_STATE_COMPLETE)
		जाओ unlock;

	अगर (WARN_ON(req->state == MEDIA_REQUEST_STATE_VALIDATING))
		जाओ unlock;

	अगर (req->state == MEDIA_REQUEST_STATE_CLEANING) अणु
		अगर (!obj->completed)
			req->num_incomplete_objects--;
		जाओ unlock;
	पूर्ण

	अगर (WARN_ON(!req->num_incomplete_objects))
		जाओ unlock;

	req->num_incomplete_objects--;
	अगर (req->state == MEDIA_REQUEST_STATE_QUEUED &&
	    !req->num_incomplete_objects) अणु
		req->state = MEDIA_REQUEST_STATE_COMPLETE;
		completed = true;
		wake_up_पूर्णांकerruptible_all(&req->poll_रुको);
	पूर्ण

unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	अगर (obj->ops->unbind)
		obj->ops->unbind(obj);
	अगर (completed)
		media_request_put(req);
पूर्ण
EXPORT_SYMBOL_GPL(media_request_object_unbind);

व्योम media_request_object_complete(काष्ठा media_request_object *obj)
अणु
	काष्ठा media_request *req = obj->req;
	अचिन्हित दीर्घ flags;
	bool completed = false;

	spin_lock_irqsave(&req->lock, flags);
	अगर (obj->completed)
		जाओ unlock;
	obj->completed = true;
	अगर (WARN_ON(!req->num_incomplete_objects) ||
	    WARN_ON(req->state != MEDIA_REQUEST_STATE_QUEUED))
		जाओ unlock;

	अगर (!--req->num_incomplete_objects) अणु
		req->state = MEDIA_REQUEST_STATE_COMPLETE;
		wake_up_पूर्णांकerruptible_all(&req->poll_रुको);
		completed = true;
	पूर्ण
unlock:
	spin_unlock_irqrestore(&req->lock, flags);
	अगर (completed)
		media_request_put(req);
पूर्ण
EXPORT_SYMBOL_GPL(media_request_object_complete);
