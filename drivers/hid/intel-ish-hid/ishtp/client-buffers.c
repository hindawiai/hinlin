<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP Ring Buffers
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#समावेश <linux/slab.h>
#समावेश "client.h"

/**
 * ishtp_cl_alloc_rx_ring() - Allocate RX ring buffers
 * @cl: client device instance
 *
 * Allocate and initialize RX ring buffers
 *
 * Return: 0 on success अन्यथा -ENOMEM
 */
पूर्णांक ishtp_cl_alloc_rx_ring(काष्ठा ishtp_cl *cl)
अणु
	माप_प्रकार	len = cl->device->fw_client->props.max_msg_length;
	पूर्णांक	j;
	काष्ठा ishtp_cl_rb *rb;
	पूर्णांक	ret = 0;
	अचिन्हित दीर्घ	flags;

	क्रम (j = 0; j < cl->rx_ring_size; ++j) अणु
		rb = ishtp_io_rb_init(cl);
		अगर (!rb) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = ishtp_io_rb_alloc_buf(rb, len);
		अगर (ret)
			जाओ out;
		spin_lock_irqsave(&cl->मुक्त_list_spinlock, flags);
		list_add_tail(&rb->list, &cl->मुक्त_rb_list.list);
		spin_unlock_irqrestore(&cl->मुक्त_list_spinlock, flags);
	पूर्ण

	वापस	0;

out:
	dev_err(&cl->device->dev, "error in allocating Rx buffers\n");
	ishtp_cl_मुक्त_rx_ring(cl);
	वापस	ret;
पूर्ण

/**
 * ishtp_cl_alloc_tx_ring() - Allocate TX ring buffers
 * @cl: client device instance
 *
 * Allocate and initialize TX ring buffers
 *
 * Return: 0 on success अन्यथा -ENOMEM
 */
पूर्णांक ishtp_cl_alloc_tx_ring(काष्ठा ishtp_cl *cl)
अणु
	माप_प्रकार	len = cl->device->fw_client->props.max_msg_length;
	पूर्णांक	j;
	अचिन्हित दीर्घ	flags;

	cl->tx_ring_मुक्त_size = 0;

	/* Allocate pool to मुक्त Tx bufs */
	क्रम (j = 0; j < cl->tx_ring_size; ++j) अणु
		काष्ठा ishtp_cl_tx_ring	*tx_buf;

		tx_buf = kzalloc(माप(काष्ठा ishtp_cl_tx_ring), GFP_KERNEL);
		अगर (!tx_buf)
			जाओ	out;

		tx_buf->send_buf.data = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!tx_buf->send_buf.data) अणु
			kमुक्त(tx_buf);
			जाओ	out;
		पूर्ण

		spin_lock_irqsave(&cl->tx_मुक्त_list_spinlock, flags);
		list_add_tail(&tx_buf->list, &cl->tx_मुक्त_list.list);
		++cl->tx_ring_मुक्त_size;
		spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock, flags);
	पूर्ण
	वापस	0;
out:
	dev_err(&cl->device->dev, "error in allocating Tx pool\n");
	ishtp_cl_मुक्त_tx_ring(cl);
	वापस	-ENOMEM;
पूर्ण

/**
 * ishtp_cl_मुक्त_rx_ring() - Free RX ring buffers
 * @cl: client device instance
 *
 * Free RX ring buffers
 */
व्योम ishtp_cl_मुक्त_rx_ring(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_cl_rb *rb;
	अचिन्हित दीर्घ	flags;

	/* release allocated memory - pass over मुक्त_rb_list */
	spin_lock_irqsave(&cl->मुक्त_list_spinlock, flags);
	जबतक (!list_empty(&cl->मुक्त_rb_list.list)) अणु
		rb = list_entry(cl->मुक्त_rb_list.list.next, काष्ठा ishtp_cl_rb,
				list);
		list_del(&rb->list);
		kमुक्त(rb->buffer.data);
		kमुक्त(rb);
	पूर्ण
	spin_unlock_irqrestore(&cl->मुक्त_list_spinlock, flags);
	/* release allocated memory - pass over in_process_list */
	spin_lock_irqsave(&cl->in_process_spinlock, flags);
	जबतक (!list_empty(&cl->in_process_list.list)) अणु
		rb = list_entry(cl->in_process_list.list.next,
				काष्ठा ishtp_cl_rb, list);
		list_del(&rb->list);
		kमुक्त(rb->buffer.data);
		kमुक्त(rb);
	पूर्ण
	spin_unlock_irqrestore(&cl->in_process_spinlock, flags);
पूर्ण

/**
 * ishtp_cl_मुक्त_tx_ring() - Free TX ring buffers
 * @cl: client device instance
 *
 * Free TX ring buffers
 */
व्योम ishtp_cl_मुक्त_tx_ring(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_cl_tx_ring	*tx_buf;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&cl->tx_मुक्त_list_spinlock, flags);
	/* release allocated memory - pass over tx_मुक्त_list */
	जबतक (!list_empty(&cl->tx_मुक्त_list.list)) अणु
		tx_buf = list_entry(cl->tx_मुक्त_list.list.next,
				    काष्ठा ishtp_cl_tx_ring, list);
		list_del(&tx_buf->list);
		--cl->tx_ring_मुक्त_size;
		kमुक्त(tx_buf->send_buf.data);
		kमुक्त(tx_buf);
	पूर्ण
	spin_unlock_irqrestore(&cl->tx_मुक्त_list_spinlock, flags);

	spin_lock_irqsave(&cl->tx_list_spinlock, flags);
	/* release allocated memory - pass over tx_list */
	जबतक (!list_empty(&cl->tx_list.list)) अणु
		tx_buf = list_entry(cl->tx_list.list.next,
				    काष्ठा ishtp_cl_tx_ring, list);
		list_del(&tx_buf->list);
		kमुक्त(tx_buf->send_buf.data);
		kमुक्त(tx_buf);
	पूर्ण
	spin_unlock_irqrestore(&cl->tx_list_spinlock, flags);
पूर्ण

/**
 * ishtp_io_rb_मुक्त() - Free IO request block
 * @rb: IO request block
 *
 * Free io request block memory
 */
व्योम ishtp_io_rb_मुक्त(काष्ठा ishtp_cl_rb *rb)
अणु
	अगर (rb == शून्य)
		वापस;

	kमुक्त(rb->buffer.data);
	kमुक्त(rb);
पूर्ण

/**
 * ishtp_io_rb_init() - Allocate and init IO request block
 * @cl: client device instance
 *
 * Allocate and initialize request block
 *
 * Return: Allocted IO request block poपूर्णांकer
 */
काष्ठा ishtp_cl_rb *ishtp_io_rb_init(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_cl_rb *rb;

	rb = kzalloc(माप(काष्ठा ishtp_cl_rb), GFP_KERNEL);
	अगर (!rb)
		वापस शून्य;

	INIT_LIST_HEAD(&rb->list);
	rb->cl = cl;
	rb->buf_idx = 0;
	वापस rb;
पूर्ण

/**
 * ishtp_io_rb_alloc_buf() - Allocate and init response buffer
 * @rb: IO request block
 * @length: length of response buffer
 *
 * Allocate respose buffer
 *
 * Return: 0 on success अन्यथा -ENOMEM
 */
पूर्णांक ishtp_io_rb_alloc_buf(काष्ठा ishtp_cl_rb *rb, माप_प्रकार length)
अणु
	अगर (!rb)
		वापस -EINVAL;

	अगर (length == 0)
		वापस 0;

	rb->buffer.data = kदो_स्मृति(length, GFP_KERNEL);
	अगर (!rb->buffer.data)
		वापस -ENOMEM;

	rb->buffer.size = length;
	वापस 0;
पूर्ण

/**
 * ishtp_cl_io_rb_recycle() - Recycle IO request blocks
 * @rb: IO request block
 *
 * Re-append rb to its client's मुक्त list and send flow control अगर needed
 *
 * Return: 0 on success अन्यथा -EFAULT
 */
पूर्णांक ishtp_cl_io_rb_recycle(काष्ठा ishtp_cl_rb *rb)
अणु
	काष्ठा ishtp_cl *cl;
	पूर्णांक	rets = 0;
	अचिन्हित दीर्घ	flags;

	अगर (!rb || !rb->cl)
		वापस	-EFAULT;

	cl = rb->cl;
	spin_lock_irqsave(&cl->मुक्त_list_spinlock, flags);
	list_add_tail(&rb->list, &cl->मुक्त_rb_list.list);
	spin_unlock_irqrestore(&cl->मुक्त_list_spinlock, flags);

	/*
	 * If we वापसed the first buffer to empty 'free' list,
	 * send flow control
	 */
	अगर (!cl->out_flow_ctrl_creds)
		rets = ishtp_cl_पढ़ो_start(cl);

	वापस	rets;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_io_rb_recycle);

/**
 * ishtp_cl_tx_empty() -test whether client device tx buffer is empty
 * @cl: Poपूर्णांकer to client device instance
 *
 * Look client device tx buffer list, and check whether this list is empty
 *
 * Return: true अगर client tx buffer list is empty अन्यथा false
 */
bool ishtp_cl_tx_empty(काष्ठा ishtp_cl *cl)
अणु
	पूर्णांक tx_list_empty;
	अचिन्हित दीर्घ tx_flags;

	spin_lock_irqsave(&cl->tx_list_spinlock, tx_flags);
	tx_list_empty = list_empty(&cl->tx_list.list);
	spin_unlock_irqrestore(&cl->tx_list_spinlock, tx_flags);

	वापस !!tx_list_empty;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_tx_empty);

/**
 * ishtp_cl_rx_get_rb() -Get a rb from client device rx buffer list
 * @cl: Poपूर्णांकer to client device instance
 *
 * Check client device in-processing buffer list and get a rb from it.
 *
 * Return: rb poपूर्णांकer अगर buffer list isn't empty अन्यथा शून्य
 */
काष्ठा ishtp_cl_rb *ishtp_cl_rx_get_rb(काष्ठा ishtp_cl *cl)
अणु
	अचिन्हित दीर्घ rx_flags;
	काष्ठा ishtp_cl_rb *rb;

	spin_lock_irqsave(&cl->in_process_spinlock, rx_flags);
	rb = list_first_entry_or_null(&cl->in_process_list.list,
				काष्ठा ishtp_cl_rb, list);
	अगर (rb)
		list_del_init(&rb->list);
	spin_unlock_irqrestore(&cl->in_process_spinlock, rx_flags);

	वापस rb;
पूर्ण
EXPORT_SYMBOL(ishtp_cl_rx_get_rb);
