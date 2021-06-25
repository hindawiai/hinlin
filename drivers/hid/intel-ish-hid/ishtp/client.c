<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP client logic
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश "hbm.h"
#समावेश "client.h"

पूर्णांक ishtp_cl_get_tx_मुक्त_buffer_size(काष्ठा ishtp_cl *cl)
अणु
	अचिन्हित दीर्घ tx_मुक्त_flags;
	पूर्णांक size;

	spin_lock_irqsave(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);
	size = cl->tx_ring_मुक्त_size * cl->device->fw_client->props.max_msg_length;
	spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);

	वापस size;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_get_tx_मुक्त_buffer_size);

पूर्णांक ishtp_cl_get_tx_मुक्त_rings(काष्ठा ishtp_cl *cl)
अणु
	वापस cl->tx_ring_मुक्त_size;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_get_tx_मुक्त_rings);

/**
 * ishtp_पढ़ो_list_flush() - Flush पढ़ो queue
 * @cl: ishtp client instance
 *
 * Used to हटाओ all entries from पढ़ो queue क्रम a client
 */
अटल व्योम ishtp_पढ़ो_list_flush(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_cl_rb *rb;
	काष्ठा ishtp_cl_rb *next;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&cl->dev->पढ़ो_list_spinlock, flags);
	list_क्रम_each_entry_safe(rb, next, &cl->dev->पढ़ो_list.list, list)
		अगर (rb->cl && ishtp_cl_cmp_id(cl, rb->cl)) अणु
			list_del(&rb->list);
			ishtp_io_rb_मुक्त(rb);
		पूर्ण
	spin_unlock_irqrestore(&cl->dev->पढ़ो_list_spinlock, flags);
पूर्ण

/**
 * ishtp_cl_flush_queues() - Flush all queues क्रम a client
 * @cl: ishtp client instance
 *
 * Used to हटाओ all queues क्रम a client. This is called when a client device
 * needs reset due to error, S3 resume or during module removal
 *
 * Return: 0 on success अन्यथा -EINVAL अगर device is शून्य
 */
पूर्णांक ishtp_cl_flush_queues(काष्ठा ishtp_cl *cl)
अणु
	अगर (WARN_ON(!cl || !cl->dev))
		वापस -EINVAL;

	ishtp_पढ़ो_list_flush(cl);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_flush_queues);

/**
 * ishtp_cl_init() - Initialize all fields of a client device
 * @cl: ishtp client instance
 * @dev: ishtp device
 *
 * Initializes a client device fields: Init spinlocks, init queues etc.
 * This function is called during new client creation
 */
अटल व्योम ishtp_cl_init(काष्ठा ishtp_cl *cl, काष्ठा ishtp_device *dev)
अणु
	स_रखो(cl, 0, माप(काष्ठा ishtp_cl));
	init_रुकोqueue_head(&cl->रुको_ctrl_res);
	spin_lock_init(&cl->मुक्त_list_spinlock);
	spin_lock_init(&cl->in_process_spinlock);
	spin_lock_init(&cl->tx_list_spinlock);
	spin_lock_init(&cl->tx_मुक्त_list_spinlock);
	spin_lock_init(&cl->fc_spinlock);
	INIT_LIST_HEAD(&cl->link);
	cl->dev = dev;

	INIT_LIST_HEAD(&cl->मुक्त_rb_list.list);
	INIT_LIST_HEAD(&cl->tx_list.list);
	INIT_LIST_HEAD(&cl->tx_मुक्त_list.list);
	INIT_LIST_HEAD(&cl->in_process_list.list);

	cl->rx_ring_size = CL_DEF_RX_RING_SIZE;
	cl->tx_ring_size = CL_DEF_TX_RING_SIZE;
	cl->tx_ring_मुक्त_size = cl->tx_ring_size;

	/* dma */
	cl->last_tx_path = CL_TX_PATH_IPC;
	cl->last_dma_acked = 1;
	cl->last_dma_addr = शून्य;
	cl->last_ipc_acked = 1;
पूर्ण

/**
 * ishtp_cl_allocate() - allocates client काष्ठाure and sets it up.
 * @dev: ishtp device
 *
 * Allocate memory क्रम new client device and call to initialize each field.
 *
 * Return: The allocated client instance or शून्य on failure
 */
काष्ठा ishtp_cl *ishtp_cl_allocate(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl *cl;

	cl = kदो_स्मृति(माप(काष्ठा ishtp_cl), GFP_KERNEL);
	अगर (!cl)
		वापस शून्य;

	ishtp_cl_init(cl, cl_device->ishtp_dev);
	वापस cl;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_allocate);

/**
 * ishtp_cl_मुक्त() - Frees a client device
 * @cl: client device instance
 *
 * Frees a client device
 */
व्योम	ishtp_cl_मुक्त(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	अचिन्हित दीर्घ flags;

	अगर (!cl)
		वापस;

	dev = cl->dev;
	अगर (!dev)
		वापस;

	spin_lock_irqsave(&dev->cl_list_lock, flags);
	ishtp_cl_मुक्त_rx_ring(cl);
	ishtp_cl_मुक्त_tx_ring(cl);
	kमुक्त(cl);
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);
पूर्ण
EXPORT_SYMBOL(ishtp_cl_मुक्त);

/**
 * ishtp_cl_link() - Reserve a host id and link the client instance
 * @cl: client device instance
 *
 * This allocates a single bit in the hosपंचांगap. This function will make sure
 * that not many client sessions are खोलोed at the same समय. Once allocated
 * the client device instance is added to the ishtp device in the current
 * client list
 *
 * Return: 0 or error code on failure
 */
पूर्णांक ishtp_cl_link(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	अचिन्हित दीर्घ flags, flags_cl;
	पूर्णांक id, ret = 0;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -EINVAL;

	dev = cl->dev;

	spin_lock_irqsave(&dev->device_lock, flags);

	अगर (dev->खोलो_handle_count >= ISHTP_MAX_OPEN_HANDLE_COUNT) अणु
		ret = -EMखाता;
		जाओ unlock_dev;
	पूर्ण

	id = find_first_zero_bit(dev->host_clients_map, ISHTP_CLIENTS_MAX);

	अगर (id >= ISHTP_CLIENTS_MAX) अणु
		spin_unlock_irqrestore(&dev->device_lock, flags);
		dev_err(&cl->device->dev, "id exceeded %d", ISHTP_CLIENTS_MAX);
		वापस -ENOENT;
	पूर्ण

	dev->खोलो_handle_count++;
	cl->host_client_id = id;
	spin_lock_irqsave(&dev->cl_list_lock, flags_cl);
	अगर (dev->dev_state != ISHTP_DEV_ENABLED) अणु
		ret = -ENODEV;
		जाओ unlock_cl;
	पूर्ण
	list_add_tail(&cl->link, &dev->cl_list);
	set_bit(id, dev->host_clients_map);
	cl->state = ISHTP_CL_INITIALIZING;

unlock_cl:
	spin_unlock_irqrestore(&dev->cl_list_lock, flags_cl);
unlock_dev:
	spin_unlock_irqrestore(&dev->device_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_link);

/**
 * ishtp_cl_unlink() - हटाओ fw_cl from the client device list
 * @cl: client device instance
 *
 * Remove a previously linked device to a ishtp device
 */
व्योम ishtp_cl_unlink(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	काष्ठा ishtp_cl *pos;
	अचिन्हित दीर्घ	flags;

	/* करोn't shout on error निकास path */
	अगर (!cl || !cl->dev)
		वापस;

	dev = cl->dev;

	spin_lock_irqsave(&dev->device_lock, flags);
	अगर (dev->खोलो_handle_count > 0) अणु
		clear_bit(cl->host_client_id, dev->host_clients_map);
		dev->खोलो_handle_count--;
	पूर्ण
	spin_unlock_irqrestore(&dev->device_lock, flags);

	/*
	 * This checks that 'cl' is actually linked into device's काष्ठाure,
	 * beक्रमe attempting 'list_del'
	 */
	spin_lock_irqsave(&dev->cl_list_lock, flags);
	list_क्रम_each_entry(pos, &dev->cl_list, link)
		अगर (cl->host_client_id == pos->host_client_id) अणु
			list_del_init(&pos->link);
			अवरोध;
		पूर्ण
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);
पूर्ण
EXPORT_SYMBOL(ishtp_cl_unlink);

/**
 * ishtp_cl_disconnect() - Send disconnect request to firmware
 * @cl: client device instance
 *
 * Send a disconnect request क्रम a client to firmware.
 *
 * Return: 0 अगर successful disconnect response from the firmware or error
 * code on failure
 */
पूर्णांक ishtp_cl_disconnect(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	पूर्णांक err;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	dev->prपूर्णांक_log(dev, "%s() state %d\n", __func__, cl->state);

	अगर (cl->state != ISHTP_CL_DISCONNECTING) अणु
		dev->prपूर्णांक_log(dev, "%s() Disconnect in progress\n", __func__);
		वापस 0;
	पूर्ण

	अगर (ishtp_hbm_cl_disconnect_req(dev, cl)) अणु
		dev->prपूर्णांक_log(dev, "%s() Failed to disconnect\n", __func__);
		dev_err(&cl->device->dev, "failed to disconnect.\n");
		वापस -ENODEV;
	पूर्ण

	err = रुको_event_पूर्णांकerruptible_समयout(cl->रुको_ctrl_res,
			(dev->dev_state != ISHTP_DEV_ENABLED ||
			cl->state == ISHTP_CL_DISCONNECTED),
			ishtp_secs_to_jअगरfies(ISHTP_CL_CONNECT_TIMEOUT));

	/*
	 * If FW reset arrived, this will happen. Don't check cl->,
	 * as 'cl' may be मुक्तd alपढ़ोy
	 */
	अगर (dev->dev_state != ISHTP_DEV_ENABLED) अणु
		dev->prपूर्णांक_log(dev, "%s() dev_state != ISHTP_DEV_ENABLED\n",
			       __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (cl->state == ISHTP_CL_DISCONNECTED) अणु
		dev->prपूर्णांक_log(dev, "%s() successful\n", __func__);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_disconnect);

/**
 * ishtp_cl_is_other_connecting() - Check other client is connecting
 * @cl: client device instance
 *
 * Checks अगर other client with the same fw client id is connecting
 *
 * Return: true अगर other client is connected अन्यथा false
 */
अटल bool ishtp_cl_is_other_connecting(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	काष्ठा ishtp_cl *pos;
	अचिन्हित दीर्घ	flags;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस false;

	dev = cl->dev;
	spin_lock_irqsave(&dev->cl_list_lock, flags);
	list_क्रम_each_entry(pos, &dev->cl_list, link) अणु
		अगर ((pos->state == ISHTP_CL_CONNECTING) && (pos != cl) &&
				cl->fw_client_id == pos->fw_client_id) अणु
			spin_unlock_irqrestore(&dev->cl_list_lock, flags);
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->cl_list_lock, flags);

	वापस false;
पूर्ण

/**
 * ishtp_cl_connect() - Send connect request to firmware
 * @cl: client device instance
 *
 * Send a connect request क्रम a client to firmware. If successful it will
 * RX and TX ring buffers
 *
 * Return: 0 अगर successful connect response from the firmware and able
 * to bind and allocate ring buffers or error code on failure
 */
पूर्णांक ishtp_cl_connect(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	पूर्णांक rets;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	dev->prपूर्णांक_log(dev, "%s() current_state = %d\n", __func__, cl->state);

	अगर (ishtp_cl_is_other_connecting(cl)) अणु
		dev->prपूर्णांक_log(dev, "%s() Busy\n", __func__);
		वापस	-EBUSY;
	पूर्ण

	अगर (ishtp_hbm_cl_connect_req(dev, cl)) अणु
		dev->prपूर्णांक_log(dev, "%s() HBM connect req fail\n", __func__);
		वापस -ENODEV;
	पूर्ण

	rets = रुको_event_पूर्णांकerruptible_समयout(cl->रुको_ctrl_res,
				(dev->dev_state == ISHTP_DEV_ENABLED &&
				(cl->state == ISHTP_CL_CONNECTED ||
				 cl->state == ISHTP_CL_DISCONNECTED)),
				ishtp_secs_to_jअगरfies(
					ISHTP_CL_CONNECT_TIMEOUT));
	/*
	 * If FW reset arrived, this will happen. Don't check cl->,
	 * as 'cl' may be मुक्तd alपढ़ोy
	 */
	अगर (dev->dev_state != ISHTP_DEV_ENABLED) अणु
		dev->prपूर्णांक_log(dev, "%s() dev_state != ISHTP_DEV_ENABLED\n",
			       __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (cl->state != ISHTP_CL_CONNECTED) अणु
		dev->prपूर्णांक_log(dev, "%s() state != ISHTP_CL_CONNECTED\n",
			       __func__);
		वापस -EFAULT;
	पूर्ण

	rets = cl->status;
	अगर (rets) अणु
		dev->prपूर्णांक_log(dev, "%s() Invalid status\n", __func__);
		वापस rets;
	पूर्ण

	rets = ishtp_cl_device_bind(cl);
	अगर (rets) अणु
		dev->prपूर्णांक_log(dev, "%s() Bind error\n", __func__);
		ishtp_cl_disconnect(cl);
		वापस rets;
	पूर्ण

	rets = ishtp_cl_alloc_rx_ring(cl);
	अगर (rets) अणु
		dev->prपूर्णांक_log(dev, "%s() Alloc RX ring failed\n", __func__);
		/* अगर failed allocation, disconnect */
		ishtp_cl_disconnect(cl);
		वापस rets;
	पूर्ण

	rets = ishtp_cl_alloc_tx_ring(cl);
	अगर (rets) अणु
		dev->prपूर्णांक_log(dev, "%s() Alloc TX ring failed\n", __func__);
		/* अगर failed allocation, disconnect */
		ishtp_cl_मुक्त_rx_ring(cl);
		ishtp_cl_disconnect(cl);
		वापस rets;
	पूर्ण

	/* Upon successful connection and allocation, emit flow-control */
	rets = ishtp_cl_पढ़ो_start(cl);

	dev->prपूर्णांक_log(dev, "%s() successful\n", __func__);

	वापस rets;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_connect);

/**
 * ishtp_cl_पढ़ो_start() - Prepare to पढ़ो client message
 * @cl: client device instance
 *
 * Get a मुक्त buffer from pool of मुक्त पढ़ो buffers and add to पढ़ो buffer
 * pool to add contents. Send a flow control request to firmware to be able
 * send next message.
 *
 * Return: 0 अगर successful or error code on failure
 */
पूर्णांक ishtp_cl_पढ़ो_start(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_device *dev;
	काष्ठा ishtp_cl_rb *rb;
	पूर्णांक rets;
	पूर्णांक i;
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	dev_flags;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (cl->state != ISHTP_CL_CONNECTED)
		वापस -ENODEV;

	अगर (dev->dev_state != ISHTP_DEV_ENABLED)
		वापस -ENODEV;

	i = ishtp_fw_cl_by_id(dev, cl->fw_client_id);
	अगर (i < 0) अणु
		dev_err(&cl->device->dev, "no such fw client %d\n",
			cl->fw_client_id);
		वापस -ENODEV;
	पूर्ण

	/* The current rb is the head of the मुक्त rb list */
	spin_lock_irqsave(&cl->मुक्त_list_spinlock, flags);
	अगर (list_empty(&cl->मुक्त_rb_list.list)) अणु
		dev_warn(&cl->device->dev,
			 "[ishtp-ish] Rx buffers pool is empty\n");
		rets = -ENOMEM;
		rb = शून्य;
		spin_unlock_irqrestore(&cl->मुक्त_list_spinlock, flags);
		जाओ out;
	पूर्ण
	rb = list_entry(cl->मुक्त_rb_list.list.next, काष्ठा ishtp_cl_rb, list);
	list_del_init(&rb->list);
	spin_unlock_irqrestore(&cl->मुक्त_list_spinlock, flags);

	rb->cl = cl;
	rb->buf_idx = 0;

	INIT_LIST_HEAD(&rb->list);
	rets = 0;

	/*
	 * This must be BEFORE sending flow control -
	 * response in ISR may come too fast...
	 */
	spin_lock_irqsave(&dev->पढ़ो_list_spinlock, dev_flags);
	list_add_tail(&rb->list, &dev->पढ़ो_list.list);
	spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, dev_flags);
	अगर (ishtp_hbm_cl_flow_control_req(dev, cl)) अणु
		rets = -ENODEV;
		जाओ out;
	पूर्ण
out:
	/* अगर ishtp_hbm_cl_flow_control_req failed, वापस rb to मुक्त list */
	अगर (rets && rb) अणु
		spin_lock_irqsave(&dev->पढ़ो_list_spinlock, dev_flags);
		list_del(&rb->list);
		spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, dev_flags);

		spin_lock_irqsave(&cl->मुक्त_list_spinlock, flags);
		list_add_tail(&rb->list, &cl->मुक्त_rb_list.list);
		spin_unlock_irqrestore(&cl->मुक्त_list_spinlock, flags);
	पूर्ण
	वापस rets;
पूर्ण

/**
 * ishtp_cl_send() - Send a message to firmware
 * @cl: client device instance
 * @buf: message buffer
 * @length: length of message
 *
 * If the client is correct state to send message, this function माला_लो a buffer
 * from tx ring buffers, copy the message data and call to send the message
 * using ishtp_cl_send_msg()
 *
 * Return: 0 अगर successful or error code on failure
 */
पूर्णांक ishtp_cl_send(काष्ठा ishtp_cl *cl, uपूर्णांक8_t *buf, माप_प्रकार length)
अणु
	काष्ठा ishtp_device	*dev;
	पूर्णांक	id;
	काष्ठा ishtp_cl_tx_ring	*cl_msg;
	पूर्णांक	have_msg_to_send = 0;
	अचिन्हित दीर्घ	tx_flags, tx_मुक्त_flags;

	अगर (WARN_ON(!cl || !cl->dev))
		वापस -ENODEV;

	dev = cl->dev;

	अगर (cl->state != ISHTP_CL_CONNECTED) अणु
		++cl->err_send_msg;
		वापस -EPIPE;
	पूर्ण

	अगर (dev->dev_state != ISHTP_DEV_ENABLED) अणु
		++cl->err_send_msg;
		वापस -ENODEV;
	पूर्ण

	/* Check अगर we have fw client device */
	id = ishtp_fw_cl_by_id(dev, cl->fw_client_id);
	अगर (id < 0) अणु
		++cl->err_send_msg;
		वापस -ENOENT;
	पूर्ण

	अगर (length > dev->fw_clients[id].props.max_msg_length) अणु
		++cl->err_send_msg;
		वापस -EMSGSIZE;
	पूर्ण

	/* No मुक्त bufs */
	spin_lock_irqsave(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);
	अगर (list_empty(&cl->tx_मुक्त_list.list)) अणु
		spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock,
			tx_मुक्त_flags);
		++cl->err_send_msg;
		वापस	-ENOMEM;
	पूर्ण

	cl_msg = list_first_entry(&cl->tx_मुक्त_list.list,
		काष्ठा ishtp_cl_tx_ring, list);
	अगर (!cl_msg->send_buf.data) अणु
		spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock,
			tx_मुक्त_flags);
		वापस	-EIO;
		/* Should not happen, as मुक्त list is pre-allocated */
	पूर्ण
	/*
	 * This is safe, as 'length' is alपढ़ोy checked क्रम not exceeding
	 * max ISHTP message size per client
	 */
	list_del_init(&cl_msg->list);
	--cl->tx_ring_मुक्त_size;

	spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);
	स_नकल(cl_msg->send_buf.data, buf, length);
	cl_msg->send_buf.size = length;
	spin_lock_irqsave(&cl->tx_list_spinlock, tx_flags);
	have_msg_to_send = !list_empty(&cl->tx_list.list);
	list_add_tail(&cl_msg->list, &cl->tx_list.list);
	spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);

	अगर (!have_msg_to_send && cl->ishtp_flow_ctrl_creds > 0)
		ishtp_cl_send_msg(dev, cl);

	वापस	0;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_send);

/**
 * ishtp_cl_पढ़ो_complete() - पढ़ो complete
 * @rb: Poपूर्णांकer to client request block
 *
 * If the message is completely received call ishtp_cl_bus_rx_event()
 * to process message
 */
अटल व्योम ishtp_cl_पढ़ो_complete(काष्ठा ishtp_cl_rb *rb)
अणु
	अचिन्हित दीर्घ	flags;
	पूर्णांक	schedule_work_flag = 0;
	काष्ठा ishtp_cl	*cl = rb->cl;

	spin_lock_irqsave(&cl->in_process_spinlock, flags);
	/*
	 * अगर in-process list is empty, then need to schedule
	 * the processing thपढ़ो
	 */
	schedule_work_flag = list_empty(&cl->in_process_list.list);
	list_add_tail(&rb->list, &cl->in_process_list.list);
	spin_unlock_irqrestore(&cl->in_process_spinlock, flags);

	अगर (schedule_work_flag)
		ishtp_cl_bus_rx_event(cl->device);
पूर्ण

/**
 * ipc_tx_callback() - IPC tx callback function
 * @prm: Poपूर्णांकer to client device instance
 *
 * Send message over IPC either first समय or on callback on previous message
 * completion
 */
अटल व्योम ipc_tx_callback(व्योम *prm)
अणु
	काष्ठा ishtp_cl	*cl = prm;
	काष्ठा ishtp_cl_tx_ring	*cl_msg;
	माप_प्रकार	rem;
	काष्ठा ishtp_device	*dev = (cl ? cl->dev : शून्य);
	काष्ठा ishtp_msg_hdr	ishtp_hdr;
	अचिन्हित दीर्घ	tx_flags, tx_मुक्त_flags;
	अचिन्हित अक्षर	*pmsg;

	अगर (!dev)
		वापस;

	/*
	 * Other conditions अगर some critical error has
	 * occurred beक्रमe this callback is called
	 */
	अगर (dev->dev_state != ISHTP_DEV_ENABLED)
		वापस;

	अगर (cl->state != ISHTP_CL_CONNECTED)
		वापस;

	spin_lock_irqsave(&cl->tx_list_spinlock, tx_flags);
	अगर (list_empty(&cl->tx_list.list)) अणु
		spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);
		वापस;
	पूर्ण

	अगर (cl->ishtp_flow_ctrl_creds != 1 && !cl->sending) अणु
		spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);
		वापस;
	पूर्ण

	अगर (!cl->sending) अणु
		--cl->ishtp_flow_ctrl_creds;
		cl->last_ipc_acked = 0;
		cl->last_tx_path = CL_TX_PATH_IPC;
		cl->sending = 1;
	पूर्ण

	cl_msg = list_entry(cl->tx_list.list.next, काष्ठा ishtp_cl_tx_ring,
			    list);
	rem = cl_msg->send_buf.size - cl->tx_offs;

	ishtp_hdr.host_addr = cl->host_client_id;
	ishtp_hdr.fw_addr = cl->fw_client_id;
	ishtp_hdr.reserved = 0;
	pmsg = cl_msg->send_buf.data + cl->tx_offs;

	अगर (rem <= dev->mtu) अणु
		ishtp_hdr.length = rem;
		ishtp_hdr.msg_complete = 1;
		cl->sending = 0;
		list_del_init(&cl_msg->list);	/* Must be beक्रमe ग_लिखो */
		spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);
		/* Submit to IPC queue with no callback */
		ishtp_ग_लिखो_message(dev, &ishtp_hdr, pmsg);
		spin_lock_irqsave(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);
		list_add_tail(&cl_msg->list, &cl->tx_मुक्त_list.list);
		++cl->tx_ring_मुक्त_size;
		spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock,
			tx_मुक्त_flags);
	पूर्ण अन्यथा अणु
		/* Send IPC fragment */
		spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);
		cl->tx_offs += dev->mtu;
		ishtp_hdr.length = dev->mtu;
		ishtp_hdr.msg_complete = 0;
		ishtp_send_msg(dev, &ishtp_hdr, pmsg, ipc_tx_callback, cl);
	पूर्ण
पूर्ण

/**
 * ishtp_cl_send_msg_ipc() -Send message using IPC
 * @dev: ISHTP device instance
 * @cl: Poपूर्णांकer to client device instance
 *
 * Send message over IPC not using DMA
 */
अटल व्योम ishtp_cl_send_msg_ipc(काष्ठा ishtp_device *dev,
				  काष्ठा ishtp_cl *cl)
अणु
	/* If last DMA message wasn't acked yet, leave this one in Tx queue */
	अगर (cl->last_tx_path == CL_TX_PATH_DMA && cl->last_dma_acked == 0)
		वापस;

	cl->tx_offs = 0;
	ipc_tx_callback(cl);
	++cl->send_msg_cnt_ipc;
पूर्ण

/**
 * ishtp_cl_send_msg_dma() -Send message using DMA
 * @dev: ISHTP device instance
 * @cl: Poपूर्णांकer to client device instance
 *
 * Send message using DMA
 */
अटल व्योम ishtp_cl_send_msg_dma(काष्ठा ishtp_device *dev,
	काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_msg_hdr	hdr;
	काष्ठा dma_xfer_hbm	dma_xfer;
	अचिन्हित अक्षर	*msg_addr;
	पूर्णांक off;
	काष्ठा ishtp_cl_tx_ring	*cl_msg;
	अचिन्हित दीर्घ tx_flags, tx_मुक्त_flags;

	/* If last IPC message wasn't acked yet, leave this one in Tx queue */
	अगर (cl->last_tx_path == CL_TX_PATH_IPC && cl->last_ipc_acked == 0)
		वापस;

	spin_lock_irqsave(&cl->tx_list_spinlock, tx_flags);
	अगर (list_empty(&cl->tx_list.list)) अणु
		spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);
		वापस;
	पूर्ण

	cl_msg = list_entry(cl->tx_list.list.next, काष्ठा ishtp_cl_tx_ring,
		list);

	msg_addr = ishtp_cl_get_dma_send_buf(dev, cl_msg->send_buf.size);
	अगर (!msg_addr) अणु
		spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);
		अगर (dev->transfer_path == CL_TX_PATH_DEFAULT)
			ishtp_cl_send_msg_ipc(dev, cl);
		वापस;
	पूर्ण

	list_del_init(&cl_msg->list);	/* Must be beक्रमe ग_लिखो */
	spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);

	--cl->ishtp_flow_ctrl_creds;
	cl->last_dma_acked = 0;
	cl->last_dma_addr = msg_addr;
	cl->last_tx_path = CL_TX_PATH_DMA;

	/* ग_लिखो msg to dma buf */
	स_नकल(msg_addr, cl_msg->send_buf.data, cl_msg->send_buf.size);

	/* send dma_xfer hbm msg */
	off = msg_addr - (अचिन्हित अक्षर *)dev->ishtp_host_dma_tx_buf;
	ishtp_hbm_hdr(&hdr, माप(काष्ठा dma_xfer_hbm));
	dma_xfer.hbm = DMA_XFER;
	dma_xfer.fw_client_id = cl->fw_client_id;
	dma_xfer.host_client_id = cl->host_client_id;
	dma_xfer.reserved = 0;
	dma_xfer.msg_addr = dev->ishtp_host_dma_tx_buf_phys + off;
	dma_xfer.msg_length = cl_msg->send_buf.size;
	dma_xfer.reserved2 = 0;
	ishtp_ग_लिखो_message(dev, &hdr, (अचिन्हित अक्षर *)&dma_xfer);
	spin_lock_irqsave(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);
	list_add_tail(&cl_msg->list, &cl->tx_मुक्त_list.list);
	++cl->tx_ring_मुक्त_size;
	spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock, tx_मुक्त_flags);
	++cl->send_msg_cnt_dma;
पूर्ण

/**
 * ishtp_cl_send_msg() -Send message using DMA or IPC
 * @dev: ISHTP device instance
 * @cl: Poपूर्णांकer to client device instance
 *
 * Send message using DMA or IPC based on transfer_path
 */
व्योम ishtp_cl_send_msg(काष्ठा ishtp_device *dev, काष्ठा ishtp_cl *cl)
अणु
	अगर (dev->transfer_path == CL_TX_PATH_DMA)
		ishtp_cl_send_msg_dma(dev, cl);
	अन्यथा
		ishtp_cl_send_msg_ipc(dev, cl);
पूर्ण

/**
 * recv_ishtp_cl_msg() -Receive client message
 * @dev: ISHTP device instance
 * @ishtp_hdr: Poपूर्णांकer to message header
 *
 * Receive and dispatch ISHTP client messages. This function executes in ISR
 * or work queue context
 */
व्योम recv_ishtp_cl_msg(काष्ठा ishtp_device *dev,
		       काष्ठा ishtp_msg_hdr *ishtp_hdr)
अणु
	काष्ठा ishtp_cl *cl;
	काष्ठा ishtp_cl_rb *rb;
	काष्ठा ishtp_cl_rb *new_rb;
	अचिन्हित अक्षर *buffer = शून्य;
	काष्ठा ishtp_cl_rb *complete_rb = शून्य;
	अचिन्हित दीर्घ	flags;
	पूर्णांक	rb_count;

	अगर (ishtp_hdr->reserved) अणु
		dev_err(dev->devc, "corrupted message header.\n");
		जाओ	eoi;
	पूर्ण

	अगर (ishtp_hdr->length > IPC_PAYLOAD_SIZE) अणु
		dev_err(dev->devc,
			"ISHTP message length in hdr exceeds IPC MTU\n");
		जाओ	eoi;
	पूर्ण

	spin_lock_irqsave(&dev->पढ़ो_list_spinlock, flags);
	rb_count = -1;
	list_क्रम_each_entry(rb, &dev->पढ़ो_list.list, list) अणु
		++rb_count;
		cl = rb->cl;
		अगर (!cl || !(cl->host_client_id == ishtp_hdr->host_addr &&
				cl->fw_client_id == ishtp_hdr->fw_addr) ||
				!(cl->state == ISHTP_CL_CONNECTED))
			जारी;

		 /* If no Rx buffer is allocated, disband the rb */
		अगर (rb->buffer.size == 0 || rb->buffer.data == शून्य) अणु
			spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, flags);
			dev_err(&cl->device->dev,
				"Rx buffer is not allocated.\n");
			list_del(&rb->list);
			ishtp_io_rb_मुक्त(rb);
			cl->status = -ENOMEM;
			जाओ	eoi;
		पूर्ण

		/*
		 * If message buffer overflown (exceeds max. client msg
		 * size, drop message and वापस to मुक्त buffer.
		 * Do we need to disconnect such a client? (We करोn't send
		 * back FC, so communication will be stuck anyway)
		 */
		अगर (rb->buffer.size < ishtp_hdr->length + rb->buf_idx) अणु
			spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, flags);
			dev_err(&cl->device->dev,
				"message overflow. size %d len %d idx %ld\n",
				rb->buffer.size, ishtp_hdr->length,
				rb->buf_idx);
			list_del(&rb->list);
			ishtp_cl_io_rb_recycle(rb);
			cl->status = -EIO;
			जाओ	eoi;
		पूर्ण

		buffer = rb->buffer.data + rb->buf_idx;
		dev->ops->ishtp_पढ़ो(dev, buffer, ishtp_hdr->length);

		rb->buf_idx += ishtp_hdr->length;
		अगर (ishtp_hdr->msg_complete) अणु
			/* Last fragment in message - it's complete */
			cl->status = 0;
			list_del(&rb->list);
			complete_rb = rb;

			--cl->out_flow_ctrl_creds;
			/*
			 * the whole msg arrived, send a new FC, and add a new
			 * rb buffer क्रम the next coming msg
			 */
			spin_lock(&cl->मुक्त_list_spinlock);

			अगर (!list_empty(&cl->मुक्त_rb_list.list)) अणु
				new_rb = list_entry(cl->मुक्त_rb_list.list.next,
					काष्ठा ishtp_cl_rb, list);
				list_del_init(&new_rb->list);
				spin_unlock(&cl->मुक्त_list_spinlock);
				new_rb->cl = cl;
				new_rb->buf_idx = 0;
				INIT_LIST_HEAD(&new_rb->list);
				list_add_tail(&new_rb->list,
					&dev->पढ़ो_list.list);

				ishtp_hbm_cl_flow_control_req(dev, cl);
			पूर्ण अन्यथा अणु
				spin_unlock(&cl->मुक्त_list_spinlock);
			पूर्ण
		पूर्ण
		/* One more fragment in message (even अगर this was last) */
		++cl->recv_msg_num_frags;

		/*
		 * We can safely अवरोध here (and in BH too),
		 * a single input message can go only to a single request!
		 */
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, flags);
	/* If it's nobody's message, just पढ़ो and discard it */
	अगर (!buffer) अणु
		uपूर्णांक8_t	rd_msg_buf[ISHTP_RD_MSG_BUF_SIZE];

		dev_err(dev->devc, "Dropped Rx msg - no request\n");
		dev->ops->ishtp_पढ़ो(dev, rd_msg_buf, ishtp_hdr->length);
		जाओ	eoi;
	पूर्ण

	अगर (complete_rb) अणु
		cl = complete_rb->cl;
		cl->ts_rx = kसमय_get();
		++cl->recv_msg_cnt_ipc;
		ishtp_cl_पढ़ो_complete(complete_rb);
	पूर्ण
eoi:
	वापस;
पूर्ण

/**
 * recv_ishtp_cl_msg_dma() -Receive client message
 * @dev: ISHTP device instance
 * @msg: message poपूर्णांकer
 * @hbm: hbm buffer
 *
 * Receive and dispatch ISHTP client messages using DMA. This function executes
 * in ISR or work queue context
 */
व्योम recv_ishtp_cl_msg_dma(काष्ठा ishtp_device *dev, व्योम *msg,
			   काष्ठा dma_xfer_hbm *hbm)
अणु
	काष्ठा ishtp_cl *cl;
	काष्ठा ishtp_cl_rb *rb;
	काष्ठा ishtp_cl_rb *new_rb;
	अचिन्हित अक्षर *buffer = शून्य;
	काष्ठा ishtp_cl_rb *complete_rb = शून्य;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&dev->पढ़ो_list_spinlock, flags);

	list_क्रम_each_entry(rb, &dev->पढ़ो_list.list, list) अणु
		cl = rb->cl;
		अगर (!cl || !(cl->host_client_id == hbm->host_client_id &&
				cl->fw_client_id == hbm->fw_client_id) ||
				!(cl->state == ISHTP_CL_CONNECTED))
			जारी;

		/*
		 * If no Rx buffer is allocated, disband the rb
		 */
		अगर (rb->buffer.size == 0 || rb->buffer.data == शून्य) अणु
			spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, flags);
			dev_err(&cl->device->dev,
				"response buffer is not allocated.\n");
			list_del(&rb->list);
			ishtp_io_rb_मुक्त(rb);
			cl->status = -ENOMEM;
			जाओ	eoi;
		पूर्ण

		/*
		 * If message buffer overflown (exceeds max. client msg
		 * size, drop message and वापस to मुक्त buffer.
		 * Do we need to disconnect such a client? (We करोn't send
		 * back FC, so communication will be stuck anyway)
		 */
		अगर (rb->buffer.size < hbm->msg_length) अणु
			spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, flags);
			dev_err(&cl->device->dev,
				"message overflow. size %d len %d idx %ld\n",
				rb->buffer.size, hbm->msg_length, rb->buf_idx);
			list_del(&rb->list);
			ishtp_cl_io_rb_recycle(rb);
			cl->status = -EIO;
			जाओ	eoi;
		पूर्ण

		buffer = rb->buffer.data;
		स_नकल(buffer, msg, hbm->msg_length);
		rb->buf_idx = hbm->msg_length;

		/* Last fragment in message - it's complete */
		cl->status = 0;
		list_del(&rb->list);
		complete_rb = rb;

		--cl->out_flow_ctrl_creds;
		/*
		 * the whole msg arrived, send a new FC, and add a new
		 * rb buffer क्रम the next coming msg
		 */
		spin_lock(&cl->मुक्त_list_spinlock);

		अगर (!list_empty(&cl->मुक्त_rb_list.list)) अणु
			new_rb = list_entry(cl->मुक्त_rb_list.list.next,
				काष्ठा ishtp_cl_rb, list);
			list_del_init(&new_rb->list);
			spin_unlock(&cl->मुक्त_list_spinlock);
			new_rb->cl = cl;
			new_rb->buf_idx = 0;
			INIT_LIST_HEAD(&new_rb->list);
			list_add_tail(&new_rb->list,
				&dev->पढ़ो_list.list);

			ishtp_hbm_cl_flow_control_req(dev, cl);
		पूर्ण अन्यथा अणु
			spin_unlock(&cl->मुक्त_list_spinlock);
		पूर्ण

		/* One more fragment in message (this is always last) */
		++cl->recv_msg_num_frags;

		/*
		 * We can safely अवरोध here (and in BH too),
		 * a single input message can go only to a single request!
		 */
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&dev->पढ़ो_list_spinlock, flags);
	/* If it's nobody's message, just पढ़ो and discard it */
	अगर (!buffer) अणु
		dev_err(dev->devc, "Dropped Rx (DMA) msg - no request\n");
		जाओ	eoi;
	पूर्ण

	अगर (complete_rb) अणु
		cl = complete_rb->cl;
		cl->ts_rx = kसमय_get();
		++cl->recv_msg_cnt_dma;
		ishtp_cl_पढ़ो_complete(complete_rb);
	पूर्ण
eoi:
	वापस;
पूर्ण

व्योम *ishtp_get_client_data(काष्ठा ishtp_cl *cl)
अणु
	वापस cl->client_data;
पूर्ण
EXPORT_SYMBOL(ishtp_get_client_data);

व्योम ishtp_set_client_data(काष्ठा ishtp_cl *cl, व्योम *data)
अणु
	cl->client_data = data;
पूर्ण
EXPORT_SYMBOL(ishtp_set_client_data);

काष्ठा ishtp_device *ishtp_get_ishtp_device(काष्ठा ishtp_cl *cl)
अणु
	वापस cl->dev;
पूर्ण
EXPORT_SYMBOL(ishtp_get_ishtp_device);

व्योम ishtp_set_tx_ring_size(काष्ठा ishtp_cl *cl, पूर्णांक size)
अणु
	cl->tx_ring_size = size;
पूर्ण
EXPORT_SYMBOL(ishtp_set_tx_ring_size);

व्योम ishtp_set_rx_ring_size(काष्ठा ishtp_cl *cl, पूर्णांक size)
अणु
	cl->rx_ring_size = size;
पूर्ण
EXPORT_SYMBOL(ishtp_set_rx_ring_size);

व्योम ishtp_set_connection_state(काष्ठा ishtp_cl *cl, पूर्णांक state)
अणु
	cl->state = state;
पूर्ण
EXPORT_SYMBOL(ishtp_set_connection_state);

व्योम ishtp_cl_set_fw_client_id(काष्ठा ishtp_cl *cl, पूर्णांक fw_client_id)
अणु
	cl->fw_client_id = fw_client_id;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_set_fw_client_id);
