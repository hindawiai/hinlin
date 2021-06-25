<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Media device request objects
 *
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 * Copyright (C) 2018 Intel Corporation
 *
 * Author: Hans Verkuil <hans.verkuil@cisco.com>
 * Author: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#अगर_अघोषित MEDIA_REQUEST_H
#घोषणा MEDIA_REQUEST_H

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/refcount.h>

#समावेश <media/media-device.h>

/**
 * क्रमागत media_request_state - media request state
 *
 * @MEDIA_REQUEST_STATE_IDLE:		Idle
 * @MEDIA_REQUEST_STATE_VALIDATING:	Validating the request, no state changes
 *					allowed
 * @MEDIA_REQUEST_STATE_QUEUED:		Queued
 * @MEDIA_REQUEST_STATE_COMPLETE:	Completed, the request is करोne
 * @MEDIA_REQUEST_STATE_CLEANING:	Cleaning, the request is being re-inited
 * @MEDIA_REQUEST_STATE_UPDATING:	The request is being updated, i.e.
 *					request objects are being added,
 *					modअगरied or हटाओd
 * @NR_OF_MEDIA_REQUEST_STATE:		The number of media request states, used
 *					पूर्णांकernally क्रम sanity check purposes
 */
क्रमागत media_request_state अणु
	MEDIA_REQUEST_STATE_IDLE,
	MEDIA_REQUEST_STATE_VALIDATING,
	MEDIA_REQUEST_STATE_QUEUED,
	MEDIA_REQUEST_STATE_COMPLETE,
	MEDIA_REQUEST_STATE_CLEANING,
	MEDIA_REQUEST_STATE_UPDATING,
	NR_OF_MEDIA_REQUEST_STATE,
पूर्ण;

काष्ठा media_request_object;

/**
 * काष्ठा media_request - Media device request
 * @mdev: Media device this request beदीर्घs to
 * @kref: Reference count
 * @debug_str: Prefix क्रम debug messages (process name:fd)
 * @state: The state of the request
 * @updating_count: count the number of request updates that are in progress
 * @access_count: count the number of request accesses that are in progress
 * @objects: List of @काष्ठा media_request_object request objects
 * @num_incomplete_objects: The number of incomplete objects in the request
 * @poll_रुको: Wait queue क्रम poll
 * @lock: Serializes access to this काष्ठा
 */
काष्ठा media_request अणु
	काष्ठा media_device *mdev;
	काष्ठा kref kref;
	अक्षर debug_str[TASK_COMM_LEN + 11];
	क्रमागत media_request_state state;
	अचिन्हित पूर्णांक updating_count;
	अचिन्हित पूर्णांक access_count;
	काष्ठा list_head objects;
	अचिन्हित पूर्णांक num_incomplete_objects;
	रुको_queue_head_t poll_रुको;
	spinlock_t lock;
पूर्ण;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER

/**
 * media_request_lock_क्रम_access - Lock the request to access its objects
 *
 * @req: The media request
 *
 * Use beक्रमe accessing a completed request. A reference to the request must
 * be held during the access. This usually takes place स्वतःmatically through
 * a file handle. Use @media_request_unlock_क्रम_access when करोne.
 */
अटल अंतरभूत पूर्णांक __must_check
media_request_lock_क्रम_access(काष्ठा media_request *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EBUSY;

	spin_lock_irqsave(&req->lock, flags);
	अगर (req->state == MEDIA_REQUEST_STATE_COMPLETE) अणु
		req->access_count++;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&req->lock, flags);

	वापस ret;
पूर्ण

/**
 * media_request_unlock_क्रम_access - Unlock a request previously locked क्रम
 *				     access
 *
 * @req: The media request
 *
 * Unlock a request that has previously been locked using
 * @media_request_lock_क्रम_access.
 */
अटल अंतरभूत व्योम media_request_unlock_क्रम_access(काष्ठा media_request *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&req->lock, flags);
	अगर (!WARN_ON(!req->access_count))
		req->access_count--;
	spin_unlock_irqrestore(&req->lock, flags);
पूर्ण

/**
 * media_request_lock_क्रम_update - Lock the request क्रम updating its objects
 *
 * @req: The media request
 *
 * Use beक्रमe updating a request, i.e. adding, modअगरying or removing a request
 * object in it. A reference to the request must be held during the update. This
 * usually takes place स्वतःmatically through a file handle. Use
 * @media_request_unlock_क्रम_update when करोne.
 */
अटल अंतरभूत पूर्णांक __must_check
media_request_lock_क्रम_update(काष्ठा media_request *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&req->lock, flags);
	अगर (req->state == MEDIA_REQUEST_STATE_IDLE ||
	    req->state == MEDIA_REQUEST_STATE_UPDATING) अणु
		req->state = MEDIA_REQUEST_STATE_UPDATING;
		req->updating_count++;
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&req->lock, flags);

	वापस ret;
पूर्ण

/**
 * media_request_unlock_क्रम_update - Unlock a request previously locked क्रम
 *				     update
 *
 * @req: The media request
 *
 * Unlock a request that has previously been locked using
 * @media_request_lock_क्रम_update.
 */
अटल अंतरभूत व्योम media_request_unlock_क्रम_update(काष्ठा media_request *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&req->lock, flags);
	WARN_ON(req->updating_count <= 0);
	अगर (!--req->updating_count)
		req->state = MEDIA_REQUEST_STATE_IDLE;
	spin_unlock_irqrestore(&req->lock, flags);
पूर्ण

/**
 * media_request_get - Get the media request
 *
 * @req: The media request
 *
 * Get the media request.
 */
अटल अंतरभूत व्योम media_request_get(काष्ठा media_request *req)
अणु
	kref_get(&req->kref);
पूर्ण

/**
 * media_request_put - Put the media request
 *
 * @req: The media request
 *
 * Put the media request. The media request will be released
 * when the refcount reaches 0.
 */
व्योम media_request_put(काष्ठा media_request *req);

/**
 * media_request_get_by_fd - Get a media request by fd
 *
 * @mdev: Media device this request beदीर्घs to
 * @request_fd: The file descriptor of the request
 *
 * Get the request represented by @request_fd that is owned
 * by the media device.
 *
 * Return a -EBADR error poपूर्णांकer अगर requests are not supported
 * by this driver. Return -EINVAL अगर the request was not found.
 * Return the poपूर्णांकer to the request अगर found: the caller will
 * have to call @media_request_put when it finished using the
 * request.
 */
काष्ठा media_request *
media_request_get_by_fd(काष्ठा media_device *mdev, पूर्णांक request_fd);

/**
 * media_request_alloc - Allocate the media request
 *
 * @mdev: Media device this request beदीर्घs to
 * @alloc_fd: Store the request's file descriptor in this पूर्णांक
 *
 * Allocated the media request and put the fd in @alloc_fd.
 */
पूर्णांक media_request_alloc(काष्ठा media_device *mdev,
			पूर्णांक *alloc_fd);

#अन्यथा

अटल अंतरभूत व्योम media_request_get(काष्ठा media_request *req)
अणु
पूर्ण

अटल अंतरभूत व्योम media_request_put(काष्ठा media_request *req)
अणु
पूर्ण

अटल अंतरभूत काष्ठा media_request *
media_request_get_by_fd(काष्ठा media_device *mdev, पूर्णांक request_fd)
अणु
	वापस ERR_PTR(-EBADR);
पूर्ण

#पूर्ण_अगर

/**
 * काष्ठा media_request_object_ops - Media request object operations
 * @prepare: Validate and prepare the request object, optional.
 * @unprepare: Unprepare the request object, optional.
 * @queue: Queue the request object, optional.
 * @unbind: Unbind the request object, optional.
 * @release: Release the request object, required.
 */
काष्ठा media_request_object_ops अणु
	पूर्णांक (*prepare)(काष्ठा media_request_object *object);
	व्योम (*unprepare)(काष्ठा media_request_object *object);
	व्योम (*queue)(काष्ठा media_request_object *object);
	व्योम (*unbind)(काष्ठा media_request_object *object);
	व्योम (*release)(काष्ठा media_request_object *object);
पूर्ण;

/**
 * काष्ठा media_request_object - An opaque object that beदीर्घs to a media
 *				 request
 *
 * @ops: object's operations
 * @priv: object's priv poपूर्णांकer
 * @req: the request this object beदीर्घs to (can be शून्य)
 * @list: List entry of the object क्रम @काष्ठा media_request
 * @kref: Reference count of the object, acquire beक्रमe releasing req->lock
 * @completed: If true, then this object was completed.
 *
 * An object related to the request. This काष्ठा is always embedded in
 * another काष्ठा that contains the actual data क्रम this request object.
 */
काष्ठा media_request_object अणु
	स्थिर काष्ठा media_request_object_ops *ops;
	व्योम *priv;
	काष्ठा media_request *req;
	काष्ठा list_head list;
	काष्ठा kref kref;
	bool completed;
पूर्ण;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER

/**
 * media_request_object_get - Get a media request object
 *
 * @obj: The object
 *
 * Get a media request object.
 */
अटल अंतरभूत व्योम media_request_object_get(काष्ठा media_request_object *obj)
अणु
	kref_get(&obj->kref);
पूर्ण

/**
 * media_request_object_put - Put a media request object
 *
 * @obj: The object
 *
 * Put a media request object. Once all references are gone, the
 * object's memory is released.
 */
व्योम media_request_object_put(काष्ठा media_request_object *obj);

/**
 * media_request_object_find - Find an object in a request
 *
 * @req: The media request
 * @ops: Find an object with this ops value
 * @priv: Find an object with this priv value
 *
 * Both @ops and @priv must be non-शून्य.
 *
 * Returns the object poपूर्णांकer or शून्य अगर not found. The caller must
 * call media_request_object_put() once it finished using the object.
 *
 * Since this function needs to walk the list of objects it takes
 * the @req->lock spin lock to make this safe.
 */
काष्ठा media_request_object *
media_request_object_find(काष्ठा media_request *req,
			  स्थिर काष्ठा media_request_object_ops *ops,
			  व्योम *priv);

/**
 * media_request_object_init - Initialise a media request object
 *
 * @obj: The object
 *
 * Initialise a media request object. The object will be released using the
 * release callback of the ops once it has no references (this function
 * initialises references to one).
 */
व्योम media_request_object_init(काष्ठा media_request_object *obj);

/**
 * media_request_object_bind - Bind a media request object to a request
 *
 * @req: The media request
 * @ops: The object ops क्रम this object
 * @priv: A driver-specअगरic priv poपूर्णांकer associated with this object
 * @is_buffer: Set to true अगर the object a buffer object.
 * @obj: The object
 *
 * Bind this object to the request and set the ops and priv values of
 * the object so it can be found later with media_request_object_find().
 *
 * Every bound object must be unbound or completed by the kernel at some
 * poपूर्णांक in समय, otherwise the request will never complete. When the
 * request is released all completed objects will be unbound by the
 * request core code.
 *
 * Buffer objects will be added to the end of the request's object
 * list, non-buffer objects will be added to the front of the list.
 * This ensures that all buffer objects are at the end of the list
 * and that all non-buffer objects that they depend on are processed
 * first.
 */
पूर्णांक media_request_object_bind(काष्ठा media_request *req,
			      स्थिर काष्ठा media_request_object_ops *ops,
			      व्योम *priv, bool is_buffer,
			      काष्ठा media_request_object *obj);

/**
 * media_request_object_unbind - Unbind a media request object
 *
 * @obj: The object
 *
 * Unbind the media request object from the request.
 */
व्योम media_request_object_unbind(काष्ठा media_request_object *obj);

/**
 * media_request_object_complete - Mark the media request object as complete
 *
 * @obj: The object
 *
 * Mark the media request object as complete. Only bound objects can
 * be completed.
 */
व्योम media_request_object_complete(काष्ठा media_request_object *obj);

#अन्यथा

अटल अंतरभूत पूर्णांक __must_check
media_request_lock_क्रम_access(काष्ठा media_request *req)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम media_request_unlock_क्रम_access(काष्ठा media_request *req)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __must_check
media_request_lock_क्रम_update(काष्ठा media_request *req)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम media_request_unlock_क्रम_update(काष्ठा media_request *req)
अणु
पूर्ण

अटल अंतरभूत व्योम media_request_object_get(काष्ठा media_request_object *obj)
अणु
पूर्ण

अटल अंतरभूत व्योम media_request_object_put(काष्ठा media_request_object *obj)
अणु
पूर्ण

अटल अंतरभूत काष्ठा media_request_object *
media_request_object_find(काष्ठा media_request *req,
			  स्थिर काष्ठा media_request_object_ops *ops,
			  व्योम *priv)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम media_request_object_init(काष्ठा media_request_object *obj)
अणु
	obj->ops = शून्य;
	obj->req = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक media_request_object_bind(काष्ठा media_request *req,
			       स्थिर काष्ठा media_request_object_ops *ops,
			       व्योम *priv, bool is_buffer,
			       काष्ठा media_request_object *obj)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम media_request_object_unbind(काष्ठा media_request_object *obj)
अणु
पूर्ण

अटल अंतरभूत व्योम media_request_object_complete(काष्ठा media_request_object *obj)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
