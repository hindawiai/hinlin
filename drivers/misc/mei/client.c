<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "hbm.h"
#समावेश "client.h"

/**
 * mei_me_cl_init - initialize me client
 *
 * @me_cl: me client
 */
व्योम mei_me_cl_init(काष्ठा mei_me_client *me_cl)
अणु
	INIT_LIST_HEAD(&me_cl->list);
	kref_init(&me_cl->refcnt);
पूर्ण

/**
 * mei_me_cl_get - increases me client refcount
 *
 * @me_cl: me client
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: me client or शून्य
 */
काष्ठा mei_me_client *mei_me_cl_get(काष्ठा mei_me_client *me_cl)
अणु
	अगर (me_cl && kref_get_unless_zero(&me_cl->refcnt))
		वापस me_cl;

	वापस शून्य;
पूर्ण

/**
 * mei_me_cl_release - मुक्त me client
 *
 * Locking: called under "dev->device_lock" lock
 *
 * @ref: me_client refcount
 */
अटल व्योम mei_me_cl_release(काष्ठा kref *ref)
अणु
	काष्ठा mei_me_client *me_cl =
		container_of(ref, काष्ठा mei_me_client, refcnt);

	kमुक्त(me_cl);
पूर्ण

/**
 * mei_me_cl_put - decrease me client refcount and मुक्त client अगर necessary
 *
 * Locking: called under "dev->device_lock" lock
 *
 * @me_cl: me client
 */
व्योम mei_me_cl_put(काष्ठा mei_me_client *me_cl)
अणु
	अगर (me_cl)
		kref_put(&me_cl->refcnt, mei_me_cl_release);
पूर्ण

/**
 * __mei_me_cl_del  - delete me client from the list and decrease
 *     reference counter
 *
 * @dev: mei device
 * @me_cl: me client
 *
 * Locking: dev->me_clients_rwsem
 */
अटल व्योम __mei_me_cl_del(काष्ठा mei_device *dev, काष्ठा mei_me_client *me_cl)
अणु
	अगर (!me_cl)
		वापस;

	list_del_init(&me_cl->list);
	mei_me_cl_put(me_cl);
पूर्ण

/**
 * mei_me_cl_del - delete me client from the list and decrease
 *     reference counter
 *
 * @dev: mei device
 * @me_cl: me client
 */
व्योम mei_me_cl_del(काष्ठा mei_device *dev, काष्ठा mei_me_client *me_cl)
अणु
	करोwn_ग_लिखो(&dev->me_clients_rwsem);
	__mei_me_cl_del(dev, me_cl);
	up_ग_लिखो(&dev->me_clients_rwsem);
पूर्ण

/**
 * mei_me_cl_add - add me client to the list
 *
 * @dev: mei device
 * @me_cl: me client
 */
व्योम mei_me_cl_add(काष्ठा mei_device *dev, काष्ठा mei_me_client *me_cl)
अणु
	करोwn_ग_लिखो(&dev->me_clients_rwsem);
	list_add(&me_cl->list, &dev->me_clients);
	up_ग_लिखो(&dev->me_clients_rwsem);
पूर्ण

/**
 * __mei_me_cl_by_uuid - locate me client by uuid
 *	increases ref count
 *
 * @dev: mei device
 * @uuid: me client uuid
 *
 * Return: me client or शून्य अगर not found
 *
 * Locking: dev->me_clients_rwsem
 */
अटल काष्ठा mei_me_client *__mei_me_cl_by_uuid(काष्ठा mei_device *dev,
					स्थिर uuid_le *uuid)
अणु
	काष्ठा mei_me_client *me_cl;
	स्थिर uuid_le *pn;

	WARN_ON(!rwsem_is_locked(&dev->me_clients_rwsem));

	list_क्रम_each_entry(me_cl, &dev->me_clients, list) अणु
		pn = &me_cl->props.protocol_name;
		अगर (uuid_le_cmp(*uuid, *pn) == 0)
			वापस mei_me_cl_get(me_cl);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * mei_me_cl_by_uuid - locate me client by uuid
 *	increases ref count
 *
 * @dev: mei device
 * @uuid: me client uuid
 *
 * Return: me client or शून्य अगर not found
 *
 * Locking: dev->me_clients_rwsem
 */
काष्ठा mei_me_client *mei_me_cl_by_uuid(काष्ठा mei_device *dev,
					स्थिर uuid_le *uuid)
अणु
	काष्ठा mei_me_client *me_cl;

	करोwn_पढ़ो(&dev->me_clients_rwsem);
	me_cl = __mei_me_cl_by_uuid(dev, uuid);
	up_पढ़ो(&dev->me_clients_rwsem);

	वापस me_cl;
पूर्ण

/**
 * mei_me_cl_by_id - locate me client by client id
 *	increases ref count
 *
 * @dev: the device काष्ठाure
 * @client_id: me client id
 *
 * Return: me client or शून्य अगर not found
 *
 * Locking: dev->me_clients_rwsem
 */
काष्ठा mei_me_client *mei_me_cl_by_id(काष्ठा mei_device *dev, u8 client_id)
अणु

	काष्ठा mei_me_client *__me_cl, *me_cl = शून्य;

	करोwn_पढ़ो(&dev->me_clients_rwsem);
	list_क्रम_each_entry(__me_cl, &dev->me_clients, list) अणु
		अगर (__me_cl->client_id == client_id) अणु
			me_cl = mei_me_cl_get(__me_cl);
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&dev->me_clients_rwsem);

	वापस me_cl;
पूर्ण

/**
 * __mei_me_cl_by_uuid_id - locate me client by client id and uuid
 *	increases ref count
 *
 * @dev: the device काष्ठाure
 * @uuid: me client uuid
 * @client_id: me client id
 *
 * Return: me client or null अगर not found
 *
 * Locking: dev->me_clients_rwsem
 */
अटल काष्ठा mei_me_client *__mei_me_cl_by_uuid_id(काष्ठा mei_device *dev,
					   स्थिर uuid_le *uuid, u8 client_id)
अणु
	काष्ठा mei_me_client *me_cl;
	स्थिर uuid_le *pn;

	WARN_ON(!rwsem_is_locked(&dev->me_clients_rwsem));

	list_क्रम_each_entry(me_cl, &dev->me_clients, list) अणु
		pn = &me_cl->props.protocol_name;
		अगर (uuid_le_cmp(*uuid, *pn) == 0 &&
		    me_cl->client_id == client_id)
			वापस mei_me_cl_get(me_cl);
	पूर्ण

	वापस शून्य;
पूर्ण


/**
 * mei_me_cl_by_uuid_id - locate me client by client id and uuid
 *	increases ref count
 *
 * @dev: the device काष्ठाure
 * @uuid: me client uuid
 * @client_id: me client id
 *
 * Return: me client or null अगर not found
 */
काष्ठा mei_me_client *mei_me_cl_by_uuid_id(काष्ठा mei_device *dev,
					   स्थिर uuid_le *uuid, u8 client_id)
अणु
	काष्ठा mei_me_client *me_cl;

	करोwn_पढ़ो(&dev->me_clients_rwsem);
	me_cl = __mei_me_cl_by_uuid_id(dev, uuid, client_id);
	up_पढ़ो(&dev->me_clients_rwsem);

	वापस me_cl;
पूर्ण

/**
 * mei_me_cl_rm_by_uuid - हटाओ all me clients matching uuid
 *
 * @dev: the device काष्ठाure
 * @uuid: me client uuid
 *
 * Locking: called under "dev->device_lock" lock
 */
व्योम mei_me_cl_rm_by_uuid(काष्ठा mei_device *dev, स्थिर uuid_le *uuid)
अणु
	काष्ठा mei_me_client *me_cl;

	dev_dbg(dev->dev, "remove %pUl\n", uuid);

	करोwn_ग_लिखो(&dev->me_clients_rwsem);
	me_cl = __mei_me_cl_by_uuid(dev, uuid);
	__mei_me_cl_del(dev, me_cl);
	mei_me_cl_put(me_cl);
	up_ग_लिखो(&dev->me_clients_rwsem);
पूर्ण

/**
 * mei_me_cl_rm_by_uuid_id - हटाओ all me clients matching client id
 *
 * @dev: the device काष्ठाure
 * @uuid: me client uuid
 * @id: me client id
 *
 * Locking: called under "dev->device_lock" lock
 */
व्योम mei_me_cl_rm_by_uuid_id(काष्ठा mei_device *dev, स्थिर uuid_le *uuid, u8 id)
अणु
	काष्ठा mei_me_client *me_cl;

	dev_dbg(dev->dev, "remove %pUl %d\n", uuid, id);

	करोwn_ग_लिखो(&dev->me_clients_rwsem);
	me_cl = __mei_me_cl_by_uuid_id(dev, uuid, id);
	__mei_me_cl_del(dev, me_cl);
	mei_me_cl_put(me_cl);
	up_ग_लिखो(&dev->me_clients_rwsem);
पूर्ण

/**
 * mei_me_cl_rm_all - हटाओ all me clients
 *
 * @dev: the device काष्ठाure
 *
 * Locking: called under "dev->device_lock" lock
 */
व्योम mei_me_cl_rm_all(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_me_client *me_cl, *next;

	करोwn_ग_लिखो(&dev->me_clients_rwsem);
	list_क्रम_each_entry_safe(me_cl, next, &dev->me_clients, list)
		__mei_me_cl_del(dev, me_cl);
	up_ग_लिखो(&dev->me_clients_rwsem);
पूर्ण

/**
 * mei_io_cb_मुक्त - मुक्त mei_cb_निजी related memory
 *
 * @cb: mei callback काष्ठा
 */
व्योम mei_io_cb_मुक्त(काष्ठा mei_cl_cb *cb)
अणु
	अगर (cb == शून्य)
		वापस;

	list_del(&cb->list);
	kमुक्त(cb->buf.data);
	kमुक्त(cb);
पूर्ण

/**
 * mei_tx_cb_queue - queue tx callback
 *
 * Locking: called under "dev->device_lock" lock
 *
 * @cb: mei callback काष्ठा
 * @head: an instance of list to queue on
 */
अटल अंतरभूत व्योम mei_tx_cb_enqueue(काष्ठा mei_cl_cb *cb,
				     काष्ठा list_head *head)
अणु
	list_add_tail(&cb->list, head);
	cb->cl->tx_cb_queued++;
पूर्ण

/**
 * mei_tx_cb_dequeue - dequeue tx callback
 *
 * Locking: called under "dev->device_lock" lock
 *
 * @cb: mei callback काष्ठा to dequeue and मुक्त
 */
अटल अंतरभूत व्योम mei_tx_cb_dequeue(काष्ठा mei_cl_cb *cb)
अणु
	अगर (!WARN_ON(cb->cl->tx_cb_queued == 0))
		cb->cl->tx_cb_queued--;

	mei_io_cb_मुक्त(cb);
पूर्ण

/**
 * mei_cl_set_पढ़ो_by_fp - set pending_पढ़ो flag to vtag काष्ठा क्रम given fp
 *
 * Locking: called under "dev->device_lock" lock
 *
 * @cl: mei client
 * @fp: poपूर्णांकer to file काष्ठाure
 */
अटल व्योम mei_cl_set_पढ़ो_by_fp(स्थिर काष्ठा mei_cl *cl,
				  स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_vtag *cl_vtag;

	list_क्रम_each_entry(cl_vtag, &cl->vtag_map, list) अणु
		अगर (cl_vtag->fp == fp) अणु
			cl_vtag->pending_पढ़ो = true;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mei_io_cb_init - allocate and initialize io callback
 *
 * @cl: mei client
 * @type: operation type
 * @fp: poपूर्णांकer to file काष्ठाure
 *
 * Return: mei_cl_cb poपूर्णांकer or शून्य;
 */
अटल काष्ठा mei_cl_cb *mei_io_cb_init(काष्ठा mei_cl *cl,
					क्रमागत mei_cb_file_ops type,
					स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_cb *cb;

	cb = kzalloc(माप(*cb), GFP_KERNEL);
	अगर (!cb)
		वापस शून्य;

	INIT_LIST_HEAD(&cb->list);
	cb->fp = fp;
	cb->cl = cl;
	cb->buf_idx = 0;
	cb->fop_type = type;
	cb->vtag = 0;

	वापस cb;
पूर्ण

/**
 * mei_io_list_flush_cl - हटाओs cbs beदीर्घing to the cl.
 *
 * @head:  an instance of our list काष्ठाure
 * @cl:    host client
 */
अटल व्योम mei_io_list_flush_cl(काष्ठा list_head *head,
				 स्थिर काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_cl_cb *cb, *next;

	list_क्रम_each_entry_safe(cb, next, head, list) अणु
		अगर (cl == cb->cl) अणु
			list_del_init(&cb->list);
			अगर (cb->fop_type == MEI_FOP_READ)
				mei_io_cb_मुक्त(cb);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mei_io_tx_list_मुक्त_cl - हटाओs cb beदीर्घing to the cl and मुक्त them
 *
 * @head: An instance of our list काष्ठाure
 * @cl: host client
 * @fp: file poपूर्णांकer (matching cb file object), may be शून्य
 */
अटल व्योम mei_io_tx_list_मुक्त_cl(काष्ठा list_head *head,
				   स्थिर काष्ठा mei_cl *cl,
				   स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_cb *cb, *next;

	list_क्रम_each_entry_safe(cb, next, head, list) अणु
		अगर (cl == cb->cl && (!fp || fp == cb->fp))
			mei_tx_cb_dequeue(cb);
	पूर्ण
पूर्ण

/**
 * mei_io_list_मुक्त_fp - मुक्त cb from a list that matches file poपूर्णांकer
 *
 * @head: io list
 * @fp: file poपूर्णांकer (matching cb file object), may be शून्य
 */
अटल व्योम mei_io_list_मुक्त_fp(काष्ठा list_head *head, स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_cb *cb, *next;

	list_क्रम_each_entry_safe(cb, next, head, list)
		अगर (!fp || fp == cb->fp)
			mei_io_cb_मुक्त(cb);
पूर्ण

/**
 * mei_cl_मुक्त_pending - मुक्त pending cb
 *
 * @cl: host client
 */
अटल व्योम mei_cl_मुक्त_pending(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_cl_cb *cb;

	cb = list_first_entry_or_null(&cl->rd_pending, काष्ठा mei_cl_cb, list);
	mei_io_cb_मुक्त(cb);
पूर्ण

/**
 * mei_cl_alloc_cb - a convenient wrapper क्रम allocating पढ़ो cb
 *
 * @cl: host client
 * @length: size of the buffer
 * @fop_type: operation type
 * @fp: associated file poपूर्णांकer (might be शून्य)
 *
 * Return: cb on success and शून्य on failure
 */
काष्ठा mei_cl_cb *mei_cl_alloc_cb(काष्ठा mei_cl *cl, माप_प्रकार length,
				  क्रमागत mei_cb_file_ops fop_type,
				  स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_cb *cb;

	cb = mei_io_cb_init(cl, fop_type, fp);
	अगर (!cb)
		वापस शून्य;

	अगर (length == 0)
		वापस cb;

	cb->buf.data = kदो_स्मृति(roundup(length, MEI_SLOT_SIZE), GFP_KERNEL);
	अगर (!cb->buf.data) अणु
		mei_io_cb_मुक्त(cb);
		वापस शून्य;
	पूर्ण
	cb->buf.size = length;

	वापस cb;
पूर्ण

/**
 * mei_cl_enqueue_ctrl_wr_cb - a convenient wrapper क्रम allocating
 *     and enqueuing of the control commands cb
 *
 * @cl: host client
 * @length: size of the buffer
 * @fop_type: operation type
 * @fp: associated file poपूर्णांकer (might be शून्य)
 *
 * Return: cb on success and शून्य on failure
 * Locking: called under "dev->device_lock" lock
 */
काष्ठा mei_cl_cb *mei_cl_enqueue_ctrl_wr_cb(काष्ठा mei_cl *cl, माप_प्रकार length,
					    क्रमागत mei_cb_file_ops fop_type,
					    स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_cb *cb;

	/* क्रम RX always allocate at least client's mtu */
	अगर (length)
		length = max_t(माप_प्रकार, length, mei_cl_mtu(cl));

	cb = mei_cl_alloc_cb(cl, length, fop_type, fp);
	अगर (!cb)
		वापस शून्य;

	list_add_tail(&cb->list, &cl->dev->ctrl_wr_list);
	वापस cb;
पूर्ण

/**
 * mei_cl_पढ़ो_cb - find this cl's callback in the पढ़ो list
 *     क्रम a specअगरic file
 *
 * @cl: host client
 * @fp: file poपूर्णांकer (matching cb file object), may be शून्य
 *
 * Return: cb on success, शून्य अगर cb is not found
 */
काष्ठा mei_cl_cb *mei_cl_पढ़ो_cb(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_cl_cb *cb;
	काष्ठा mei_cl_cb *ret_cb = शून्य;

	spin_lock(&cl->rd_completed_lock);
	list_क्रम_each_entry(cb, &cl->rd_completed, list)
		अगर (!fp || fp == cb->fp) अणु
			ret_cb = cb;
			अवरोध;
		पूर्ण
	spin_unlock(&cl->rd_completed_lock);
	वापस ret_cb;
पूर्ण

/**
 * mei_cl_flush_queues - flushes queue lists beदीर्घing to cl.
 *
 * @cl: host client
 * @fp: file poपूर्णांकer (matching cb file object), may be शून्य
 *
 * Return: 0 on success, -EINVAL अगर cl or cl->dev is शून्य.
 */
पूर्णांक mei_cl_flush_queues(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_device *dev;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -EINVAL;

	dev = cl->dev;

	cl_dbg(dev, cl, "remove list entry belonging to cl\n");
	mei_io_tx_list_मुक्त_cl(&cl->dev->ग_लिखो_list, cl, fp);
	mei_io_tx_list_मुक्त_cl(&cl->dev->ग_लिखो_रुकोing_list, cl, fp);
	/* मुक्त pending and control cb only in final flush */
	अगर (!fp) अणु
		mei_io_list_flush_cl(&cl->dev->ctrl_wr_list, cl);
		mei_io_list_flush_cl(&cl->dev->ctrl_rd_list, cl);
		mei_cl_मुक्त_pending(cl);
	पूर्ण
	spin_lock(&cl->rd_completed_lock);
	mei_io_list_मुक्त_fp(&cl->rd_completed, fp);
	spin_unlock(&cl->rd_completed_lock);

	वापस 0;
पूर्ण

/**
 * mei_cl_init - initializes cl.
 *
 * @cl: host client to be initialized
 * @dev: mei device
 */
अटल व्योम mei_cl_init(काष्ठा mei_cl *cl, काष्ठा mei_device *dev)
अणु
	स_रखो(cl, 0, माप(*cl));
	init_रुकोqueue_head(&cl->रुको);
	init_रुकोqueue_head(&cl->rx_रुको);
	init_रुकोqueue_head(&cl->tx_रुको);
	init_रुकोqueue_head(&cl->ev_रुको);
	INIT_LIST_HEAD(&cl->vtag_map);
	spin_lock_init(&cl->rd_completed_lock);
	INIT_LIST_HEAD(&cl->rd_completed);
	INIT_LIST_HEAD(&cl->rd_pending);
	INIT_LIST_HEAD(&cl->link);
	cl->writing_state = MEI_IDLE;
	cl->state = MEI_खाता_UNINITIALIZED;
	cl->dev = dev;
पूर्ण

/**
 * mei_cl_allocate - allocates cl  काष्ठाure and sets it up.
 *
 * @dev: mei device
 * Return:  The allocated file or शून्य on failure
 */
काष्ठा mei_cl *mei_cl_allocate(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_cl *cl;

	cl = kदो_स्मृति(माप(*cl), GFP_KERNEL);
	अगर (!cl)
		वापस शून्य;

	mei_cl_init(cl, dev);

	वापस cl;
पूर्ण

/**
 * mei_cl_link - allocate host id in the host map
 *
 * @cl: host client
 *
 * Return: 0 on success
 *	-EINVAL on incorrect values
 *	-EMखाता अगर खोलो count exceeded.
 */
पूर्णांक mei_cl_link(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक id;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -EINVAL;

	dev = cl->dev;

	id = find_first_zero_bit(dev->host_clients_map, MEI_CLIENTS_MAX);
	अगर (id >= MEI_CLIENTS_MAX) अणु
		dev_err(dev->dev, "id exceeded %d", MEI_CLIENTS_MAX);
		वापस -EMखाता;
	पूर्ण

	अगर (dev->खोलो_handle_count >= MEI_MAX_OPEN_HANDLE_COUNT) अणु
		dev_err(dev->dev, "open_handle_count exceeded %d",
			MEI_MAX_OPEN_HANDLE_COUNT);
		वापस -EMखाता;
	पूर्ण

	dev->खोलो_handle_count++;

	cl->host_client_id = id;
	list_add_tail(&cl->link, &dev->file_list);

	set_bit(id, dev->host_clients_map);

	cl->state = MEI_खाता_INITIALIZING;

	cl_dbg(dev, cl, "link cl\n");
	वापस 0;
पूर्ण

/**
 * mei_cl_unlink - हटाओ host client from the list
 *
 * @cl: host client
 *
 * Return: always 0
 */
पूर्णांक mei_cl_unlink(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev;

	/* करोn't shout on error निकास path */
	अगर (!cl)
		वापस 0;

	अगर (WARN_ON(!cl->dev))
		वापस 0;

	dev = cl->dev;

	cl_dbg(dev, cl, "unlink client");

	अगर (dev->खोलो_handle_count > 0)
		dev->खोलो_handle_count--;

	/* never clear the 0 bit */
	अगर (cl->host_client_id)
		clear_bit(cl->host_client_id, dev->host_clients_map);

	list_del_init(&cl->link);

	cl->state = MEI_खाता_UNINITIALIZED;
	cl->writing_state = MEI_IDLE;

	WARN_ON(!list_empty(&cl->rd_completed) ||
		!list_empty(&cl->rd_pending) ||
		!list_empty(&cl->link));

	वापस 0;
पूर्ण

व्योम mei_host_client_init(काष्ठा mei_device *dev)
अणु
	mei_set_devstate(dev, MEI_DEV_ENABLED);
	dev->reset_count = 0;

	schedule_work(&dev->bus_rescan_work);

	pm_runसमय_mark_last_busy(dev->dev);
	dev_dbg(dev->dev, "rpm: autosuspend\n");
	pm_request_स्वतःsuspend(dev->dev);
पूर्ण

/**
 * mei_hbuf_acquire - try to acquire host buffer
 *
 * @dev: the device काष्ठाure
 * Return: true अगर host buffer was acquired
 */
bool mei_hbuf_acquire(काष्ठा mei_device *dev)
अणु
	अगर (mei_pg_state(dev) == MEI_PG_ON ||
	    mei_pg_in_transition(dev)) अणु
		dev_dbg(dev->dev, "device is in pg\n");
		वापस false;
	पूर्ण

	अगर (!dev->hbuf_is_पढ़ोy) अणु
		dev_dbg(dev->dev, "hbuf is not ready\n");
		वापस false;
	पूर्ण

	dev->hbuf_is_पढ़ोy = false;

	वापस true;
पूर्ण

/**
 * mei_cl_wake_all - wake up पढ़ोers, ग_लिखोrs and event रुकोers so
 *                 they can be पूर्णांकerrupted
 *
 * @cl: host client
 */
अटल व्योम mei_cl_wake_all(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev = cl->dev;

	/* synchronized under device mutex */
	अगर (रुकोqueue_active(&cl->rx_रुको)) अणु
		cl_dbg(dev, cl, "Waking up reading client!\n");
		wake_up_पूर्णांकerruptible(&cl->rx_रुको);
	पूर्ण
	/* synchronized under device mutex */
	अगर (रुकोqueue_active(&cl->tx_रुको)) अणु
		cl_dbg(dev, cl, "Waking up writing client!\n");
		wake_up_पूर्णांकerruptible(&cl->tx_रुको);
	पूर्ण
	/* synchronized under device mutex */
	अगर (रुकोqueue_active(&cl->ev_रुको)) अणु
		cl_dbg(dev, cl, "Waking up waiting for event clients!\n");
		wake_up_पूर्णांकerruptible(&cl->ev_रुको);
	पूर्ण
	/* synchronized under device mutex */
	अगर (रुकोqueue_active(&cl->रुको)) अणु
		cl_dbg(dev, cl, "Waking up ctrl write clients!\n");
		wake_up(&cl->रुको);
	पूर्ण
पूर्ण

/**
 * mei_cl_set_disconnected - set disconnected state and clear
 *   associated states and resources
 *
 * @cl: host client
 */
अटल व्योम mei_cl_set_disconnected(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev = cl->dev;

	अगर (cl->state == MEI_खाता_DISCONNECTED ||
	    cl->state <= MEI_खाता_INITIALIZING)
		वापस;

	cl->state = MEI_खाता_DISCONNECTED;
	mei_io_tx_list_मुक्त_cl(&dev->ग_लिखो_list, cl, शून्य);
	mei_io_tx_list_मुक्त_cl(&dev->ग_लिखो_रुकोing_list, cl, शून्य);
	mei_io_list_flush_cl(&dev->ctrl_rd_list, cl);
	mei_io_list_flush_cl(&dev->ctrl_wr_list, cl);
	mei_cl_wake_all(cl);
	cl->rx_flow_ctrl_creds = 0;
	cl->tx_flow_ctrl_creds = 0;
	cl->समयr_count = 0;

	अगर (!cl->me_cl)
		वापस;

	अगर (!WARN_ON(cl->me_cl->connect_count == 0))
		cl->me_cl->connect_count--;

	अगर (cl->me_cl->connect_count == 0)
		cl->me_cl->tx_flow_ctrl_creds = 0;

	mei_me_cl_put(cl->me_cl);
	cl->me_cl = शून्य;
पूर्ण

अटल पूर्णांक mei_cl_set_connecting(काष्ठा mei_cl *cl, काष्ठा mei_me_client *me_cl)
अणु
	अगर (!mei_me_cl_get(me_cl))
		वापस -ENOENT;

	/* only one connection is allowed क्रम fixed address clients */
	अगर (me_cl->props.fixed_address) अणु
		अगर (me_cl->connect_count) अणु
			mei_me_cl_put(me_cl);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	cl->me_cl = me_cl;
	cl->state = MEI_खाता_CONNECTING;
	cl->me_cl->connect_count++;

	वापस 0;
पूर्ण

/*
 * mei_cl_send_disconnect - send disconnect request
 *
 * @cl: host client
 * @cb: callback block
 *
 * Return: 0, OK; otherwise, error.
 */
अटल पूर्णांक mei_cl_send_disconnect(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev = cl->dev;

	ret = mei_hbm_cl_disconnect_req(dev, cl);
	cl->status = ret;
	अगर (ret) अणु
		cl->state = MEI_खाता_DISCONNECT_REPLY;
		वापस ret;
	पूर्ण

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	cl->समयr_count = MEI_CONNECT_TIMEOUT;
	mei_schedule_stall_समयr(dev);

	वापस 0;
पूर्ण

/**
 * mei_cl_irq_disconnect - processes बंद related operation from
 *	पूर्णांकerrupt thपढ़ो context - send disconnect request
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0, OK; otherwise, error.
 */
पूर्णांक mei_cl_irq_disconnect(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
			  काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक ret;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_client_connect_request));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	ret = mei_cl_send_disconnect(cl, cb);
	अगर (ret)
		list_move_tail(&cb->list, cmpl_list);

	वापस ret;
पूर्ण

/**
 * __mei_cl_disconnect - disconnect host client from the me one
 *     पूर्णांकernal function runसमय pm has to be alपढ़ोy acquired
 *
 * @cl: host client
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक __mei_cl_disconnect(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;
	पूर्णांक rets;

	dev = cl->dev;

	cl->state = MEI_खाता_DISCONNECTING;

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_DISCONNECT, शून्य);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (mei_hbuf_acquire(dev)) अणु
		rets = mei_cl_send_disconnect(cl, cb);
		अगर (rets) अणु
			cl_err(dev, cl, "failed to disconnect.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(cl->रुको,
			   cl->state == MEI_खाता_DISCONNECT_REPLY ||
			   cl->state == MEI_खाता_DISCONNECTED,
			   mei_secs_to_jअगरfies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	rets = cl->status;
	अगर (cl->state != MEI_खाता_DISCONNECT_REPLY &&
	    cl->state != MEI_खाता_DISCONNECTED) अणु
		cl_dbg(dev, cl, "timeout on disconnect from FW client.\n");
		rets = -ETIME;
	पूर्ण

out:
	/* we disconnect also on error */
	mei_cl_set_disconnected(cl);
	अगर (!rets)
		cl_dbg(dev, cl, "successfully disconnected from FW client.\n");

	mei_io_cb_मुक्त(cb);
	वापस rets;
पूर्ण

/**
 * mei_cl_disconnect - disconnect host client from the me one
 *
 * @cl: host client
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक mei_cl_disconnect(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	cl_dbg(dev, cl, "disconnecting");

	अगर (!mei_cl_is_connected(cl))
		वापस 0;

	अगर (mei_cl_is_fixed_address(cl)) अणु
		mei_cl_set_disconnected(cl);
		वापस 0;
	पूर्ण

	अगर (dev->dev_state == MEI_DEV_POWERING_DOWN ||
	    dev->dev_state == MEI_DEV_POWER_DOWN) अणु
		cl_dbg(dev, cl, "Device is powering down, don't bother with disconnection\n");
		mei_cl_set_disconnected(cl);
		वापस 0;
	पूर्ण

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		वापस rets;
	पूर्ण

	rets = __mei_cl_disconnect(cl);

	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस rets;
पूर्ण


/**
 * mei_cl_is_other_connecting - checks अगर other
 *    client with the same me client id is connecting
 *
 * @cl: निजी data of the file object
 *
 * Return: true अगर other client is connected, false - otherwise.
 */
अटल bool mei_cl_is_other_connecting(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;

	dev = cl->dev;

	list_क्रम_each_entry(cb, &dev->ctrl_rd_list, list) अणु
		अगर (cb->fop_type == MEI_FOP_CONNECT &&
		    mei_cl_me_id(cl) == mei_cl_me_id(cb->cl))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * mei_cl_send_connect - send connect request
 *
 * @cl: host client
 * @cb: callback block
 *
 * Return: 0, OK; otherwise, error.
 */
अटल पूर्णांक mei_cl_send_connect(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev = cl->dev;

	ret = mei_hbm_cl_connect_req(dev, cl);
	cl->status = ret;
	अगर (ret) अणु
		cl->state = MEI_खाता_DISCONNECT_REPLY;
		वापस ret;
	पूर्ण

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	cl->समयr_count = MEI_CONNECT_TIMEOUT;
	mei_schedule_stall_समयr(dev);
	वापस 0;
पूर्ण

/**
 * mei_cl_irq_connect - send connect request in irq_thपढ़ो context
 *
 * @cl: host client
 * @cb: callback block
 * @cmpl_list: complete list
 *
 * Return: 0, OK; otherwise, error.
 */
पूर्णांक mei_cl_irq_connect(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		       काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक rets;

	अगर (mei_cl_is_other_connecting(cl))
		वापस 0;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_client_connect_request));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	rets = mei_cl_send_connect(cl, cb);
	अगर (rets)
		list_move_tail(&cb->list, cmpl_list);

	वापस rets;
पूर्ण

/**
 * mei_cl_connect - connect host client to the me one
 *
 * @cl: host client
 * @me_cl: me client
 * @fp: poपूर्णांकer to file काष्ठाure
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक mei_cl_connect(काष्ठा mei_cl *cl, काष्ठा mei_me_client *me_cl,
		   स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev || !me_cl))
		वापस -ENODEV;

	dev = cl->dev;

	rets = mei_cl_set_connecting(cl, me_cl);
	अगर (rets)
		जाओ nortpm;

	अगर (mei_cl_is_fixed_address(cl)) अणु
		cl->state = MEI_खाता_CONNECTED;
		rets = 0;
		जाओ nortpm;
	पूर्ण

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		जाओ nortpm;
	पूर्ण

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_CONNECT, fp);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण

	/* run hbuf acquire last so we करोn't have to unकरो */
	अगर (!mei_cl_is_other_connecting(cl) && mei_hbuf_acquire(dev)) अणु
		rets = mei_cl_send_connect(cl, cb);
		अगर (rets)
			जाओ out;
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(cl->रुको,
			(cl->state == MEI_खाता_CONNECTED ||
			 cl->state == MEI_खाता_DISCONNECTED ||
			 cl->state == MEI_खाता_DISCONNECT_REQUIRED ||
			 cl->state == MEI_खाता_DISCONNECT_REPLY),
			mei_secs_to_jअगरfies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	अगर (!mei_cl_is_connected(cl)) अणु
		अगर (cl->state == MEI_खाता_DISCONNECT_REQUIRED) अणु
			mei_io_list_flush_cl(&dev->ctrl_rd_list, cl);
			mei_io_list_flush_cl(&dev->ctrl_wr_list, cl);
			 /* ignore disconnect वापस valuue;
			  * in हाल of failure reset will be invoked
			  */
			__mei_cl_disconnect(cl);
			rets = -EFAULT;
			जाओ out;
		पूर्ण

		/* समयout or something went really wrong */
		अगर (!cl->status)
			cl->status = -EFAULT;
	पूर्ण

	rets = cl->status;
out:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	mei_io_cb_मुक्त(cb);

nortpm:
	अगर (!mei_cl_is_connected(cl))
		mei_cl_set_disconnected(cl);

	वापस rets;
पूर्ण

/**
 * mei_cl_alloc_linked - allocate and link host client
 *
 * @dev: the device काष्ठाure
 *
 * Return: cl on success ERR_PTR on failure
 */
काष्ठा mei_cl *mei_cl_alloc_linked(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_cl *cl;
	पूर्णांक ret;

	cl = mei_cl_allocate(dev);
	अगर (!cl) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = mei_cl_link(cl);
	अगर (ret)
		जाओ err;

	वापस cl;
err:
	kमुक्त(cl);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * mei_cl_tx_flow_ctrl_creds - checks flow_control credits क्रम cl.
 *
 * @cl: host client
 *
 * Return: 1 अगर tx_flow_ctrl_creds >0, 0 - otherwise.
 */
अटल पूर्णांक mei_cl_tx_flow_ctrl_creds(काष्ठा mei_cl *cl)
अणु
	अगर (WARN_ON(!cl || !cl->me_cl))
		वापस -EINVAL;

	अगर (cl->tx_flow_ctrl_creds > 0)
		वापस 1;

	अगर (mei_cl_is_fixed_address(cl))
		वापस 1;

	अगर (mei_cl_is_single_recv_buf(cl)) अणु
		अगर (cl->me_cl->tx_flow_ctrl_creds > 0)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mei_cl_tx_flow_ctrl_creds_reduce - reduces transmit flow control credits
 *   क्रम a client
 *
 * @cl: host client
 *
 * Return:
 *	0 on success
 *	-EINVAL when ctrl credits are <= 0
 */
अटल पूर्णांक mei_cl_tx_flow_ctrl_creds_reduce(काष्ठा mei_cl *cl)
अणु
	अगर (WARN_ON(!cl || !cl->me_cl))
		वापस -EINVAL;

	अगर (mei_cl_is_fixed_address(cl))
		वापस 0;

	अगर (mei_cl_is_single_recv_buf(cl)) अणु
		अगर (WARN_ON(cl->me_cl->tx_flow_ctrl_creds <= 0))
			वापस -EINVAL;
		cl->me_cl->tx_flow_ctrl_creds--;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(cl->tx_flow_ctrl_creds <= 0))
			वापस -EINVAL;
		cl->tx_flow_ctrl_creds--;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mei_cl_vtag_alloc - allocate and fill the vtag काष्ठाure
 *
 * @fp: poपूर्णांकer to file काष्ठाure
 * @vtag: vm tag
 *
 * Return:
 * * Poपूर्णांकer to allocated काष्ठा - on success
 * * ERR_PTR(-ENOMEM) on memory allocation failure
 */
काष्ठा mei_cl_vtag *mei_cl_vtag_alloc(काष्ठा file *fp, u8 vtag)
अणु
	काष्ठा mei_cl_vtag *cl_vtag;

	cl_vtag = kzalloc(माप(*cl_vtag), GFP_KERNEL);
	अगर (!cl_vtag)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&cl_vtag->list);
	cl_vtag->vtag = vtag;
	cl_vtag->fp = fp;

	वापस cl_vtag;
पूर्ण

/**
 * mei_cl_fp_by_vtag - obtain the file poपूर्णांकer by vtag
 *
 * @cl: host client
 * @vtag: भव tag
 *
 * Return:
 * * A file poपूर्णांकer - on success
 * * ERR_PTR(-ENOENT) अगर vtag is not found in the client vtag list
 */
स्थिर काष्ठा file *mei_cl_fp_by_vtag(स्थिर काष्ठा mei_cl *cl, u8 vtag)
अणु
	काष्ठा mei_cl_vtag *vtag_l;

	list_क्रम_each_entry(vtag_l, &cl->vtag_map, list)
		/* The client on bus has one fixed fp */
		अगर ((cl->cldev && mei_cldev_enabled(cl->cldev)) ||
		    vtag_l->vtag == vtag)
			वापस vtag_l->fp;

	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * mei_cl_reset_पढ़ो_by_vtag - reset pending_पढ़ो flag by given vtag
 *
 * @cl: host client
 * @vtag: vm tag
 */
अटल व्योम mei_cl_reset_पढ़ो_by_vtag(स्थिर काष्ठा mei_cl *cl, u8 vtag)
अणु
	काष्ठा mei_cl_vtag *vtag_l;

	list_क्रम_each_entry(vtag_l, &cl->vtag_map, list) अणु
		अगर (vtag_l->vtag == vtag) अणु
			vtag_l->pending_पढ़ो = false;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mei_cl_पढ़ो_vtag_add_fc - add flow control क्रम next pending पढ़ोer
 *                           in the vtag list
 *
 * @cl: host client
 */
अटल व्योम mei_cl_पढ़ो_vtag_add_fc(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_cl_vtag *cl_vtag;

	list_क्रम_each_entry(cl_vtag, &cl->vtag_map, list) अणु
		अगर (cl_vtag->pending_पढ़ो) अणु
			अगर (mei_cl_enqueue_ctrl_wr_cb(cl,
						      mei_cl_mtu(cl),
						      MEI_FOP_READ,
						      cl_vtag->fp))
				cl->rx_flow_ctrl_creds++;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mei_cl_vt_support_check - check अगर client support vtags
 *
 * @cl: host client
 *
 * Return:
 * * 0 - supported, or not connected at all
 * * -EOPNOTSUPP - vtags are not supported by client
 */
पूर्णांक mei_cl_vt_support_check(स्थिर काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev = cl->dev;

	अगर (!dev->hbm_f_vt_supported)
		वापस -EOPNOTSUPP;

	अगर (!cl->me_cl)
		वापस 0;

	वापस cl->me_cl->props.vt_supported ? 0 : -EOPNOTSUPP;
पूर्ण

/**
 * mei_cl_add_rd_completed - add पढ़ो completed callback to list with lock
 *                           and vtag check
 *
 * @cl: host client
 * @cb: callback block
 *
 */
व्योम mei_cl_add_rd_completed(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb)
अणु
	स्थिर काष्ठा file *fp;

	अगर (!mei_cl_vt_support_check(cl)) अणु
		fp = mei_cl_fp_by_vtag(cl, cb->vtag);
		अगर (IS_ERR(fp)) अणु
			/* client alपढ़ोy disconnected, discarding */
			mei_io_cb_मुक्त(cb);
			वापस;
		पूर्ण
		cb->fp = fp;
		mei_cl_reset_पढ़ो_by_vtag(cl, cb->vtag);
		mei_cl_पढ़ो_vtag_add_fc(cl);
	पूर्ण

	spin_lock(&cl->rd_completed_lock);
	list_add_tail(&cb->list, &cl->rd_completed);
	spin_unlock(&cl->rd_completed_lock);
पूर्ण

/**
 * mei_cl_del_rd_completed - मुक्त पढ़ो completed callback with lock
 *
 * @cl: host client
 * @cb: callback block
 *
 */
व्योम mei_cl_del_rd_completed(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb)
अणु
	spin_lock(&cl->rd_completed_lock);
	mei_io_cb_मुक्त(cb);
	spin_unlock(&cl->rd_completed_lock);
पूर्ण

/**
 *  mei_cl_notअगरy_fop2req - convert fop to proper request
 *
 * @fop: client notअगरication start response command
 *
 * Return:  MEI_HBM_NOTIFICATION_START/STOP
 */
u8 mei_cl_notअगरy_fop2req(क्रमागत mei_cb_file_ops fop)
अणु
	अगर (fop == MEI_FOP_NOTIFY_START)
		वापस MEI_HBM_NOTIFICATION_START;
	अन्यथा
		वापस MEI_HBM_NOTIFICATION_STOP;
पूर्ण

/**
 *  mei_cl_notअगरy_req2fop - convert notअगरication request top file operation type
 *
 * @req: hbm notअगरication request type
 *
 * Return:  MEI_FOP_NOTIFY_START/STOP
 */
क्रमागत mei_cb_file_ops mei_cl_notअगरy_req2fop(u8 req)
अणु
	अगर (req == MEI_HBM_NOTIFICATION_START)
		वापस MEI_FOP_NOTIFY_START;
	अन्यथा
		वापस MEI_FOP_NOTIFY_STOP;
पूर्ण

/**
 * mei_cl_irq_notअगरy - send notअगरication request in irq_thपढ़ो context
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0 on such and error otherwise.
 */
पूर्णांक mei_cl_irq_notअगरy(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		      काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक ret;
	bool request;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_client_connect_request));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	request = mei_cl_notअगरy_fop2req(cb->fop_type);
	ret = mei_hbm_cl_notअगरy_req(dev, cl, request);
	अगर (ret) अणु
		cl->status = ret;
		list_move_tail(&cb->list, cmpl_list);
		वापस ret;
	पूर्ण

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	वापस 0;
पूर्ण

/**
 * mei_cl_notअगरy_request - send notअगरication stop/start request
 *
 * @cl: host client
 * @fp: associate request with file
 * @request: 1 क्रम start or 0 क्रम stop
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on such and error otherwise.
 */
पूर्णांक mei_cl_notअगरy_request(काष्ठा mei_cl *cl,
			  स्थिर काष्ठा file *fp, u8 request)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;
	क्रमागत mei_cb_file_ops fop_type;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (!dev->hbm_f_ev_supported) अणु
		cl_dbg(dev, cl, "notifications not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!mei_cl_is_connected(cl))
		वापस -ENODEV;

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		वापस rets;
	पूर्ण

	fop_type = mei_cl_notअगरy_req2fop(request);
	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, fop_type, fp);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (mei_hbuf_acquire(dev)) अणु
		अगर (mei_hbm_cl_notअगरy_req(dev, cl, request)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
		list_move_tail(&cb->list, &dev->ctrl_rd_list);
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(cl->रुको,
			   cl->notअगरy_en == request ||
			   cl->status ||
			   !mei_cl_is_connected(cl),
			   mei_secs_to_jअगरfies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	अगर (cl->notअगरy_en != request && !cl->status)
		cl->status = -EFAULT;

	rets = cl->status;

out:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	mei_io_cb_मुक्त(cb);
	वापस rets;
पूर्ण

/**
 * mei_cl_notअगरy - उठाओ notअगरication
 *
 * @cl: host client
 *
 * Locking: called under "dev->device_lock" lock
 */
व्योम mei_cl_notअगरy(काष्ठा mei_cl *cl)
अणु
	काष्ठा mei_device *dev;

	अगर (!cl || !cl->dev)
		वापस;

	dev = cl->dev;

	अगर (!cl->notअगरy_en)
		वापस;

	cl_dbg(dev, cl, "notify event");
	cl->notअगरy_ev = true;
	अगर (!mei_cl_bus_notअगरy_event(cl))
		wake_up_पूर्णांकerruptible(&cl->ev_रुको);

	अगर (cl->ev_async)
		समाप्त_fasync(&cl->ev_async, SIGIO, POLL_PRI);

पूर्ण

/**
 * mei_cl_notअगरy_get - get or रुको क्रम notअगरication event
 *
 * @cl: host client
 * @block: this request is blocking
 * @notअगरy_ev: true अगर notअगरication event was received
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on such and error otherwise.
 */
पूर्णांक mei_cl_notअगरy_get(काष्ठा mei_cl *cl, bool block, bool *notअगरy_ev)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक rets;

	*notअगरy_ev = false;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (!dev->hbm_f_ev_supported) अणु
		cl_dbg(dev, cl, "notifications not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!mei_cl_is_connected(cl))
		वापस -ENODEV;

	अगर (cl->notअगरy_ev)
		जाओ out;

	अगर (!block)
		वापस -EAGAIN;

	mutex_unlock(&dev->device_lock);
	rets = रुको_event_पूर्णांकerruptible(cl->ev_रुको, cl->notअगरy_ev);
	mutex_lock(&dev->device_lock);

	अगर (rets < 0)
		वापस rets;

out:
	*notअगरy_ev = cl->notअगरy_ev;
	cl->notअगरy_ev = false;
	वापस 0;
पूर्ण

/**
 * mei_cl_पढ़ो_start - the start पढ़ो client message function.
 *
 * @cl: host client
 * @length: number of bytes to पढ़ो
 * @fp: poपूर्णांकer to file काष्ठाure
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक mei_cl_पढ़ो_start(काष्ठा mei_cl *cl, माप_प्रकार length, स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (!mei_cl_is_connected(cl))
		वापस -ENODEV;

	अगर (!mei_me_cl_is_active(cl->me_cl)) अणु
		cl_err(dev, cl, "no such me client\n");
		वापस  -ENOTTY;
	पूर्ण

	अगर (mei_cl_is_fixed_address(cl))
		वापस 0;

	/* HW currently supports only one pending पढ़ो */
	अगर (cl->rx_flow_ctrl_creds) अणु
		mei_cl_set_पढ़ो_by_fp(cl, fp);
		वापस -EBUSY;
	पूर्ण

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, length, MEI_FOP_READ, fp);
	अगर (!cb)
		वापस -ENOMEM;

	mei_cl_set_पढ़ो_by_fp(cl, fp);

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		जाओ nortpm;
	पूर्ण

	rets = 0;
	अगर (mei_hbuf_acquire(dev)) अणु
		rets = mei_hbm_cl_flow_control_req(dev, cl);
		अगर (rets < 0)
			जाओ out;

		list_move_tail(&cb->list, &cl->rd_pending);
	पूर्ण
	cl->rx_flow_ctrl_creds++;

out:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
nortpm:
	अगर (rets)
		mei_io_cb_मुक्त(cb);

	वापस rets;
पूर्ण

अटल अंतरभूत u8 mei_ext_hdr_set_vtag(काष्ठा mei_ext_hdr *ext, u8 vtag)
अणु
	ext->type = MEI_EXT_HDR_VTAG;
	ext->ext_payload[0] = vtag;
	ext->length = mei_data2slots(माप(*ext));
	वापस ext->length;
पूर्ण

/**
 * mei_msg_hdr_init - allocate and initialize mei message header
 *
 * @cb: message callback काष्ठाure
 *
 * Return: a poपूर्णांकer to initialized header or ERR_PTR on failure
 */
अटल काष्ठा mei_msg_hdr *mei_msg_hdr_init(स्थिर काष्ठा mei_cl_cb *cb)
अणु
	माप_प्रकार hdr_len;
	काष्ठा mei_ext_meta_hdr *meta;
	काष्ठा mei_ext_hdr *ext;
	काष्ठा mei_msg_hdr *mei_hdr;
	bool is_ext, is_vtag;

	अगर (!cb)
		वापस ERR_PTR(-EINVAL);

	/* Extended header क्रम vtag is attached only on the first fragment */
	is_vtag = (cb->vtag && cb->buf_idx == 0);
	is_ext = is_vtag;

	/* Compute extended header size */
	hdr_len = माप(*mei_hdr);

	अगर (!is_ext)
		जाओ setup_hdr;

	hdr_len += माप(*meta);
	अगर (is_vtag)
		hdr_len += माप(*ext);

setup_hdr:
	mei_hdr = kzalloc(hdr_len, GFP_KERNEL);
	अगर (!mei_hdr)
		वापस ERR_PTR(-ENOMEM);

	mei_hdr->host_addr = mei_cl_host_addr(cb->cl);
	mei_hdr->me_addr = mei_cl_me_id(cb->cl);
	mei_hdr->पूर्णांकernal = cb->पूर्णांकernal;
	mei_hdr->extended = is_ext;

	अगर (!is_ext)
		जाओ out;

	meta = (काष्ठा mei_ext_meta_hdr *)mei_hdr->extension;
	अगर (is_vtag) अणु
		meta->count++;
		meta->size += mei_ext_hdr_set_vtag(meta->hdrs, cb->vtag);
	पूर्ण
out:
	mei_hdr->length = hdr_len - माप(*mei_hdr);
	वापस mei_hdr;
पूर्ण

/**
 * mei_cl_irq_ग_लिखो - ग_लिखो a message to device
 *	from the पूर्णांकerrupt thपढ़ो context
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0, OK; otherwise error.
 */
पूर्णांक mei_cl_irq_ग_लिखो(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		     काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_msg_data *buf;
	काष्ठा mei_msg_hdr *mei_hdr = शून्य;
	माप_प्रकार hdr_len;
	माप_प्रकार hbuf_len, dr_len;
	माप_प्रकार buf_len;
	माप_प्रकार data_len;
	पूर्णांक hbuf_slots;
	u32 dr_slots;
	u32 dma_len;
	पूर्णांक rets;
	bool first_chunk;
	स्थिर व्योम *data;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	buf = &cb->buf;

	first_chunk = cb->buf_idx == 0;

	rets = first_chunk ? mei_cl_tx_flow_ctrl_creds(cl) : 1;
	अगर (rets < 0)
		जाओ err;

	अगर (rets == 0) अणु
		cl_dbg(dev, cl, "No flow control credentials: not sending.\n");
		वापस 0;
	पूर्ण

	buf_len = buf->size - cb->buf_idx;
	data = buf->data + cb->buf_idx;
	hbuf_slots = mei_hbuf_empty_slots(dev);
	अगर (hbuf_slots < 0) अणु
		rets = -EOVERFLOW;
		जाओ err;
	पूर्ण

	hbuf_len = mei_slots2data(hbuf_slots) & MEI_MSG_MAX_LEN_MASK;
	dr_slots = mei_dma_ring_empty_slots(dev);
	dr_len = mei_slots2data(dr_slots);

	mei_hdr = mei_msg_hdr_init(cb);
	अगर (IS_ERR(mei_hdr)) अणु
		rets = PTR_ERR(mei_hdr);
		mei_hdr = शून्य;
		जाओ err;
	पूर्ण

	cl_dbg(dev, cl, "Extended Header %d vtag = %d\n",
	       mei_hdr->extended, cb->vtag);

	hdr_len = माप(*mei_hdr) + mei_hdr->length;

	/**
	 * Split the message only अगर we can ग_लिखो the whole host buffer
	 * otherwise रुको क्रम next समय the host buffer is empty.
	 */
	अगर (hdr_len + buf_len <= hbuf_len) अणु
		data_len = buf_len;
		mei_hdr->msg_complete = 1;
	पूर्ण अन्यथा अगर (dr_slots && hbuf_len >= hdr_len + माप(dma_len)) अणु
		mei_hdr->dma_ring = 1;
		अगर (buf_len > dr_len)
			buf_len = dr_len;
		अन्यथा
			mei_hdr->msg_complete = 1;

		data_len = माप(dma_len);
		dma_len = buf_len;
		data = &dma_len;
	पूर्ण अन्यथा अगर ((u32)hbuf_slots == mei_hbuf_depth(dev)) अणु
		buf_len = hbuf_len - hdr_len;
		data_len = buf_len;
	पूर्ण अन्यथा अणु
		kमुक्त(mei_hdr);
		वापस 0;
	पूर्ण
	mei_hdr->length += data_len;

	अगर (mei_hdr->dma_ring)
		mei_dma_ring_ग_लिखो(dev, buf->data + cb->buf_idx, buf_len);
	rets = mei_ग_लिखो_message(dev, mei_hdr, hdr_len, data, data_len);

	अगर (rets)
		जाओ err;

	cl->status = 0;
	cl->writing_state = MEI_WRITING;
	cb->buf_idx += buf_len;

	अगर (first_chunk) अणु
		अगर (mei_cl_tx_flow_ctrl_creds_reduce(cl)) अणु
			rets = -EIO;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (mei_hdr->msg_complete)
		list_move_tail(&cb->list, &dev->ग_लिखो_रुकोing_list);

	kमुक्त(mei_hdr);
	वापस 0;

err:
	kमुक्त(mei_hdr);
	cl->status = rets;
	list_move_tail(&cb->list, cmpl_list);
	वापस rets;
पूर्ण

/**
 * mei_cl_ग_लिखो - submit a ग_लिखो cb to mei device
 *	assumes device_lock is locked
 *
 * @cl: host client
 * @cb: ग_लिखो callback with filled data
 *
 * Return: number of bytes sent on success, <0 on failure.
 */
sमाप_प्रकार mei_cl_ग_लिखो(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_msg_data *buf;
	काष्ठा mei_msg_hdr *mei_hdr = शून्य;
	माप_प्रकार hdr_len;
	माप_प्रकार hbuf_len, dr_len;
	माप_प्रकार buf_len;
	माप_प्रकार data_len;
	पूर्णांक hbuf_slots;
	u32 dr_slots;
	u32 dma_len;
	sमाप_प्रकार rets;
	bool blocking;
	स्थिर व्योम *data;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	अगर (WARN_ON(!cb))
		वापस -EINVAL;

	dev = cl->dev;

	buf = &cb->buf;
	buf_len = buf->size;

	cl_dbg(dev, cl, "buf_len=%zd\n", buf_len);

	blocking = cb->blocking;
	data = buf->data;

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %zd\n", rets);
		जाओ मुक्त;
	पूर्ण

	cb->buf_idx = 0;
	cl->writing_state = MEI_IDLE;


	rets = mei_cl_tx_flow_ctrl_creds(cl);
	अगर (rets < 0)
		जाओ err;

	mei_hdr = mei_msg_hdr_init(cb);
	अगर (IS_ERR(mei_hdr)) अणु
		rets = -PTR_ERR(mei_hdr);
		mei_hdr = शून्य;
		जाओ err;
	पूर्ण

	cl_dbg(dev, cl, "Extended Header %d vtag = %d\n",
	       mei_hdr->extended, cb->vtag);

	hdr_len = माप(*mei_hdr) + mei_hdr->length;

	अगर (rets == 0) अणु
		cl_dbg(dev, cl, "No flow control credentials: not sending.\n");
		rets = buf_len;
		जाओ out;
	पूर्ण

	अगर (!mei_hbuf_acquire(dev)) अणु
		cl_dbg(dev, cl, "Cannot acquire the host buffer: not sending.\n");
		rets = buf_len;
		जाओ out;
	पूर्ण

	hbuf_slots = mei_hbuf_empty_slots(dev);
	अगर (hbuf_slots < 0) अणु
		rets = -EOVERFLOW;
		जाओ out;
	पूर्ण

	hbuf_len = mei_slots2data(hbuf_slots) & MEI_MSG_MAX_LEN_MASK;
	dr_slots = mei_dma_ring_empty_slots(dev);
	dr_len =  mei_slots2data(dr_slots);

	अगर (hdr_len + buf_len <= hbuf_len) अणु
		data_len = buf_len;
		mei_hdr->msg_complete = 1;
	पूर्ण अन्यथा अगर (dr_slots && hbuf_len >= hdr_len + माप(dma_len)) अणु
		mei_hdr->dma_ring = 1;
		अगर (buf_len > dr_len)
			buf_len = dr_len;
		अन्यथा
			mei_hdr->msg_complete = 1;

		data_len = माप(dma_len);
		dma_len = buf_len;
		data = &dma_len;
	पूर्ण अन्यथा अणु
		buf_len = hbuf_len - hdr_len;
		data_len = buf_len;
	पूर्ण

	mei_hdr->length += data_len;

	अगर (mei_hdr->dma_ring)
		mei_dma_ring_ग_लिखो(dev, buf->data, buf_len);
	rets = mei_ग_लिखो_message(dev, mei_hdr, hdr_len, data, data_len);

	अगर (rets)
		जाओ err;

	rets = mei_cl_tx_flow_ctrl_creds_reduce(cl);
	अगर (rets)
		जाओ err;

	cl->writing_state = MEI_WRITING;
	cb->buf_idx = buf_len;
	/* restore वापस value */
	buf_len = buf->size;

out:
	अगर (mei_hdr->msg_complete)
		mei_tx_cb_enqueue(cb, &dev->ग_लिखो_रुकोing_list);
	अन्यथा
		mei_tx_cb_enqueue(cb, &dev->ग_लिखो_list);

	cb = शून्य;
	अगर (blocking && cl->writing_state != MEI_WRITE_COMPLETE) अणु

		mutex_unlock(&dev->device_lock);
		rets = रुको_event_पूर्णांकerruptible(cl->tx_रुको,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				(!mei_cl_is_connected(cl)));
		mutex_lock(&dev->device_lock);
		/* रुको_event_पूर्णांकerruptible वापसs -ERESTARTSYS */
		अगर (rets) अणु
			अगर (संकेत_pending(current))
				rets = -EINTR;
			जाओ err;
		पूर्ण
		अगर (cl->writing_state != MEI_WRITE_COMPLETE) अणु
			rets = -EFAULT;
			जाओ err;
		पूर्ण
	पूर्ण

	rets = buf_len;
err:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
मुक्त:
	mei_io_cb_मुक्त(cb);

	kमुक्त(mei_hdr);

	वापस rets;
पूर्ण

/**
 * mei_cl_complete - processes completed operation क्रम a client
 *
 * @cl: निजी data of the file object.
 * @cb: callback block.
 */
व्योम mei_cl_complete(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb)
अणु
	काष्ठा mei_device *dev = cl->dev;

	चयन (cb->fop_type) अणु
	हाल MEI_FOP_WRITE:
		mei_tx_cb_dequeue(cb);
		cl->writing_state = MEI_WRITE_COMPLETE;
		अगर (रुकोqueue_active(&cl->tx_रुको)) अणु
			wake_up_पूर्णांकerruptible(&cl->tx_रुको);
		पूर्ण अन्यथा अणु
			pm_runसमय_mark_last_busy(dev->dev);
			pm_request_स्वतःsuspend(dev->dev);
		पूर्ण
		अवरोध;

	हाल MEI_FOP_READ:
		mei_cl_add_rd_completed(cl, cb);
		अगर (!mei_cl_is_fixed_address(cl) &&
		    !WARN_ON(!cl->rx_flow_ctrl_creds))
			cl->rx_flow_ctrl_creds--;
		अगर (!mei_cl_bus_rx_event(cl))
			wake_up_पूर्णांकerruptible(&cl->rx_रुको);
		अवरोध;

	हाल MEI_FOP_CONNECT:
	हाल MEI_FOP_DISCONNECT:
	हाल MEI_FOP_NOTIFY_STOP:
	हाल MEI_FOP_NOTIFY_START:
	हाल MEI_FOP_DMA_MAP:
	हाल MEI_FOP_DMA_UNMAP:
		अगर (रुकोqueue_active(&cl->रुको))
			wake_up(&cl->रुको);

		अवरोध;
	हाल MEI_FOP_DISCONNECT_RSP:
		mei_io_cb_मुक्त(cb);
		mei_cl_set_disconnected(cl);
		अवरोध;
	शेष:
		BUG_ON(0);
	पूर्ण
पूर्ण


/**
 * mei_cl_all_disconnect - disconnect क्रमcefully all connected clients
 *
 * @dev: mei device
 */
व्योम mei_cl_all_disconnect(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_cl *cl;

	list_क्रम_each_entry(cl, &dev->file_list, link)
		mei_cl_set_disconnected(cl);
पूर्ण

अटल काष्ठा mei_cl *mei_cl_dma_map_find(काष्ठा mei_device *dev, u8 buffer_id)
अणु
	काष्ठा mei_cl *cl;

	list_क्रम_each_entry(cl, &dev->file_list, link)
		अगर (cl->dma.buffer_id == buffer_id)
			वापस cl;
	वापस शून्य;
पूर्ण

/**
 * mei_cl_irq_dma_map - send client dma map request in irq_thपढ़ो context
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0 on such and error otherwise.
 */
पूर्णांक mei_cl_irq_dma_map(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		       काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक ret;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_client_dma_map_request));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	ret = mei_hbm_cl_dma_map_req(dev, cl);
	अगर (ret) अणु
		cl->status = ret;
		list_move_tail(&cb->list, cmpl_list);
		वापस ret;
	पूर्ण

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	वापस 0;
पूर्ण

/**
 * mei_cl_irq_dma_unmap - send client dma unmap request in irq_thपढ़ो context
 *
 * @cl: client
 * @cb: callback block.
 * @cmpl_list: complete list.
 *
 * Return: 0 on such and error otherwise.
 */
पूर्णांक mei_cl_irq_dma_unmap(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
			 काष्ठा list_head *cmpl_list)
अणु
	काष्ठा mei_device *dev = cl->dev;
	u32 msg_slots;
	पूर्णांक slots;
	पूर्णांक ret;

	msg_slots = mei_hbm2slots(माप(काष्ठा hbm_client_dma_unmap_request));
	slots = mei_hbuf_empty_slots(dev);
	अगर (slots < 0)
		वापस -EOVERFLOW;

	अगर ((u32)slots < msg_slots)
		वापस -EMSGSIZE;

	ret = mei_hbm_cl_dma_unmap_req(dev, cl);
	अगर (ret) अणु
		cl->status = ret;
		list_move_tail(&cb->list, cmpl_list);
		वापस ret;
	पूर्ण

	list_move_tail(&cb->list, &dev->ctrl_rd_list);
	वापस 0;
पूर्ण

अटल पूर्णांक mei_cl_dma_alloc(काष्ठा mei_cl *cl, u8 buf_id, माप_प्रकार size)
अणु
	cl->dma.vaddr = dmam_alloc_coherent(cl->dev->dev, size,
					    &cl->dma.daddr, GFP_KERNEL);
	अगर (!cl->dma.vaddr)
		वापस -ENOMEM;

	cl->dma.buffer_id = buf_id;
	cl->dma.size = size;

	वापस 0;
पूर्ण

अटल व्योम mei_cl_dma_मुक्त(काष्ठा mei_cl *cl)
अणु
	cl->dma.buffer_id = 0;
	dmam_मुक्त_coherent(cl->dev->dev,
			   cl->dma.size, cl->dma.vaddr, cl->dma.daddr);
	cl->dma.size = 0;
	cl->dma.vaddr = शून्य;
	cl->dma.daddr = 0;
पूर्ण

/**
 * mei_cl_alloc_and_map - send client dma map request
 *
 * @cl: host client
 * @fp: poपूर्णांकer to file काष्ठाure
 * @buffer_id: id of the mapped buffer
 * @size: size of the buffer
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return:
 * * -ENODEV
 * * -EINVAL
 * * -EOPNOTSUPP
 * * -EPROTO
 * * -ENOMEM;
 */
पूर्णांक mei_cl_dma_alloc_and_map(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp,
			     u8 buffer_id, माप_प्रकार size)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (!dev->hbm_f_cd_supported) अणु
		cl_dbg(dev, cl, "client dma is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (buffer_id == 0)
		वापस -EINVAL;

	अगर (mei_cl_is_connected(cl))
		वापस -EPROTO;

	अगर (cl->dma_mapped)
		वापस -EPROTO;

	अगर (mei_cl_dma_map_find(dev, buffer_id)) अणु
		cl_dbg(dev, cl, "client dma with id %d is already allocated\n",
		       cl->dma.buffer_id);
		वापस -EPROTO;
	पूर्ण

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		वापस rets;
	पूर्ण

	rets = mei_cl_dma_alloc(cl, buffer_id, size);
	अगर (rets) अणु
		pm_runसमय_put_noidle(dev->dev);
		वापस rets;
	पूर्ण

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_DMA_MAP, fp);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (mei_hbuf_acquire(dev)) अणु
		अगर (mei_hbm_cl_dma_map_req(dev, cl)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
		list_move_tail(&cb->list, &dev->ctrl_rd_list);
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(cl->रुको,
			   cl->dma_mapped || cl->status,
			   mei_secs_to_jअगरfies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	अगर (!cl->dma_mapped && !cl->status)
		cl->status = -EFAULT;

	rets = cl->status;

out:
	अगर (rets)
		mei_cl_dma_मुक्त(cl);

	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	mei_io_cb_मुक्त(cb);
	वापस rets;
पूर्ण

/**
 * mei_cl_unmap_and_मुक्त - send client dma unmap request
 *
 * @cl: host client
 * @fp: poपूर्णांकer to file काष्ठाure
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: 0 on such and error otherwise.
 */
पूर्णांक mei_cl_dma_unmap(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_cl_cb *cb;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (!dev->hbm_f_cd_supported) अणु
		cl_dbg(dev, cl, "client dma is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* करो not allow unmap क्रम connected client */
	अगर (mei_cl_is_connected(cl))
		वापस -EPROTO;

	अगर (!cl->dma_mapped)
		वापस -EPROTO;

	rets = pm_runसमय_get(dev->dev);
	अगर (rets < 0 && rets != -EINPROGRESS) अणु
		pm_runसमय_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		वापस rets;
	पूर्ण

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_DMA_UNMAP, fp);
	अगर (!cb) अणु
		rets = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (mei_hbuf_acquire(dev)) अणु
		अगर (mei_hbm_cl_dma_unmap_req(dev, cl)) अणु
			rets = -ENODEV;
			जाओ out;
		पूर्ण
		list_move_tail(&cb->list, &dev->ctrl_rd_list);
	पूर्ण

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(cl->रुको,
			   !cl->dma_mapped || cl->status,
			   mei_secs_to_jअगरfies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	अगर (cl->dma_mapped && !cl->status)
		cl->status = -EFAULT;

	rets = cl->status;

	अगर (!rets)
		mei_cl_dma_मुक्त(cl);
out:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	mei_io_cb_मुक्त(cb);
	वापस rets;
पूर्ण
