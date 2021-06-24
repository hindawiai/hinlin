<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - control channel and configuration commands
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/workqueue.h>

#समावेश "ctl.h"


#घोषणा TB_CTL_RX_PKG_COUNT	10
#घोषणा TB_CTL_RETRIES		1

/**
 * काष्ठा tb_ctl - Thunderbolt control channel
 * @nhi: Poपूर्णांकer to the NHI काष्ठाure
 * @tx: Transmit ring
 * @rx: Receive ring
 * @frame_pool: DMA pool क्रम control messages
 * @rx_packets: Received control messages
 * @request_queue_lock: Lock protecting @request_queue
 * @request_queue: List of outstanding requests
 * @running: Is the control channel running at the moment
 * @समयout_msec: Default समयout क्रम non-raw control messages
 * @callback: Callback called when hotplug message is received
 * @callback_data: Data passed to @callback
 */
काष्ठा tb_ctl अणु
	काष्ठा tb_nhi *nhi;
	काष्ठा tb_ring *tx;
	काष्ठा tb_ring *rx;

	काष्ठा dma_pool *frame_pool;
	काष्ठा ctl_pkg *rx_packets[TB_CTL_RX_PKG_COUNT];
	काष्ठा mutex request_queue_lock;
	काष्ठा list_head request_queue;
	bool running;

	पूर्णांक समयout_msec;
	event_cb callback;
	व्योम *callback_data;
पूर्ण;


#घोषणा tb_ctl_WARN(ctl, क्रमmat, arg...) \
	dev_WARN(&(ctl)->nhi->pdev->dev, क्रमmat, ## arg)

#घोषणा tb_ctl_err(ctl, क्रमmat, arg...) \
	dev_err(&(ctl)->nhi->pdev->dev, क्रमmat, ## arg)

#घोषणा tb_ctl_warn(ctl, क्रमmat, arg...) \
	dev_warn(&(ctl)->nhi->pdev->dev, क्रमmat, ## arg)

#घोषणा tb_ctl_info(ctl, क्रमmat, arg...) \
	dev_info(&(ctl)->nhi->pdev->dev, क्रमmat, ## arg)

#घोषणा tb_ctl_dbg(ctl, क्रमmat, arg...) \
	dev_dbg(&(ctl)->nhi->pdev->dev, क्रमmat, ## arg)

अटल DECLARE_WAIT_QUEUE_HEAD(tb_cfg_request_cancel_queue);
/* Serializes access to request kref_get/put */
अटल DEFINE_MUTEX(tb_cfg_request_lock);

/**
 * tb_cfg_request_alloc() - Allocates a new config request
 *
 * This is refcounted object so when you are करोne with this, call
 * tb_cfg_request_put() to it.
 */
काष्ठा tb_cfg_request *tb_cfg_request_alloc(व्योम)
अणु
	काष्ठा tb_cfg_request *req;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस शून्य;

	kref_init(&req->kref);

	वापस req;
पूर्ण

/**
 * tb_cfg_request_get() - Increase refcount of a request
 * @req: Request whose refcount is increased
 */
व्योम tb_cfg_request_get(काष्ठा tb_cfg_request *req)
अणु
	mutex_lock(&tb_cfg_request_lock);
	kref_get(&req->kref);
	mutex_unlock(&tb_cfg_request_lock);
पूर्ण

अटल व्योम tb_cfg_request_destroy(काष्ठा kref *kref)
अणु
	काष्ठा tb_cfg_request *req = container_of(kref, typeof(*req), kref);

	kमुक्त(req);
पूर्ण

/**
 * tb_cfg_request_put() - Decrease refcount and possibly release the request
 * @req: Request whose refcount is decreased
 *
 * Call this function when you are करोne with the request. When refcount
 * goes to %0 the object is released.
 */
व्योम tb_cfg_request_put(काष्ठा tb_cfg_request *req)
अणु
	mutex_lock(&tb_cfg_request_lock);
	kref_put(&req->kref, tb_cfg_request_destroy);
	mutex_unlock(&tb_cfg_request_lock);
पूर्ण

अटल पूर्णांक tb_cfg_request_enqueue(काष्ठा tb_ctl *ctl,
				  काष्ठा tb_cfg_request *req)
अणु
	WARN_ON(test_bit(TB_CFG_REQUEST_ACTIVE, &req->flags));
	WARN_ON(req->ctl);

	mutex_lock(&ctl->request_queue_lock);
	अगर (!ctl->running) अणु
		mutex_unlock(&ctl->request_queue_lock);
		वापस -ENOTCONN;
	पूर्ण
	req->ctl = ctl;
	list_add_tail(&req->list, &ctl->request_queue);
	set_bit(TB_CFG_REQUEST_ACTIVE, &req->flags);
	mutex_unlock(&ctl->request_queue_lock);
	वापस 0;
पूर्ण

अटल व्योम tb_cfg_request_dequeue(काष्ठा tb_cfg_request *req)
अणु
	काष्ठा tb_ctl *ctl = req->ctl;

	mutex_lock(&ctl->request_queue_lock);
	list_del(&req->list);
	clear_bit(TB_CFG_REQUEST_ACTIVE, &req->flags);
	अगर (test_bit(TB_CFG_REQUEST_CANCELED, &req->flags))
		wake_up(&tb_cfg_request_cancel_queue);
	mutex_unlock(&ctl->request_queue_lock);
पूर्ण

अटल bool tb_cfg_request_is_active(काष्ठा tb_cfg_request *req)
अणु
	वापस test_bit(TB_CFG_REQUEST_ACTIVE, &req->flags);
पूर्ण

अटल काष्ठा tb_cfg_request *
tb_cfg_request_find(काष्ठा tb_ctl *ctl, काष्ठा ctl_pkg *pkg)
अणु
	काष्ठा tb_cfg_request *req;
	bool found = false;

	mutex_lock(&pkg->ctl->request_queue_lock);
	list_क्रम_each_entry(req, &pkg->ctl->request_queue, list) अणु
		tb_cfg_request_get(req);
		अगर (req->match(req, pkg)) अणु
			found = true;
			अवरोध;
		पूर्ण
		tb_cfg_request_put(req);
	पूर्ण
	mutex_unlock(&pkg->ctl->request_queue_lock);

	वापस found ? req : शून्य;
पूर्ण

/* utility functions */


अटल पूर्णांक check_header(स्थिर काष्ठा ctl_pkg *pkg, u32 len,
			क्रमागत tb_cfg_pkg_type type, u64 route)
अणु
	काष्ठा tb_cfg_header *header = pkg->buffer;

	/* check frame, TODO: frame flags */
	अगर (WARN(len != pkg->frame.size,
			"wrong framesize (expected %#x, got %#x)\n",
			len, pkg->frame.size))
		वापस -EIO;
	अगर (WARN(type != pkg->frame.eof, "wrong eof (expected %#x, got %#x)\n",
			type, pkg->frame.eof))
		वापस -EIO;
	अगर (WARN(pkg->frame.sof, "wrong sof (expected 0x0, got %#x)\n",
			pkg->frame.sof))
		वापस -EIO;

	/* check header */
	अगर (WARN(header->unknown != 1 << 9,
			"header->unknown is %#x\n", header->unknown))
		वापस -EIO;
	अगर (WARN(route != tb_cfg_get_route(header),
			"wrong route (expected %llx, got %llx)",
			route, tb_cfg_get_route(header)))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक check_config_address(काष्ठा tb_cfg_address addr,
				क्रमागत tb_cfg_space space, u32 offset,
				u32 length)
अणु
	अगर (WARN(addr.zero, "addr.zero is %#x\n", addr.zero))
		वापस -EIO;
	अगर (WARN(space != addr.space, "wrong space (expected %x, got %x\n)",
			space, addr.space))
		वापस -EIO;
	अगर (WARN(offset != addr.offset, "wrong offset (expected %x, got %x\n)",
			offset, addr.offset))
		वापस -EIO;
	अगर (WARN(length != addr.length, "wrong space (expected %x, got %x\n)",
			length, addr.length))
		वापस -EIO;
	/*
	 * We cannot check addr->port as it is set to the upstream port of the
	 * sender.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा tb_cfg_result decode_error(स्थिर काष्ठा ctl_pkg *response)
अणु
	काष्ठा cfg_error_pkg *pkg = response->buffer;
	काष्ठा tb_ctl *ctl = response->ctl;
	काष्ठा tb_cfg_result res = अणु 0 पूर्ण;
	res.response_route = tb_cfg_get_route(&pkg->header);
	res.response_port = 0;
	res.err = check_header(response, माप(*pkg), TB_CFG_PKG_ERROR,
			       tb_cfg_get_route(&pkg->header));
	अगर (res.err)
		वापस res;

	अगर (pkg->zero1)
		tb_ctl_warn(ctl, "pkg->zero1 is %#x\n", pkg->zero1);
	अगर (pkg->zero2)
		tb_ctl_warn(ctl, "pkg->zero2 is %#x\n", pkg->zero2);
	अगर (pkg->zero3)
		tb_ctl_warn(ctl, "pkg->zero3 is %#x\n", pkg->zero3);

	res.err = 1;
	res.tb_error = pkg->error;
	res.response_port = pkg->port;
	वापस res;

पूर्ण

अटल काष्ठा tb_cfg_result parse_header(स्थिर काष्ठा ctl_pkg *pkg, u32 len,
					 क्रमागत tb_cfg_pkg_type type, u64 route)
अणु
	काष्ठा tb_cfg_header *header = pkg->buffer;
	काष्ठा tb_cfg_result res = अणु 0 पूर्ण;

	अगर (pkg->frame.eof == TB_CFG_PKG_ERROR)
		वापस decode_error(pkg);

	res.response_port = 0; /* will be updated later क्रम cfg_पढ़ो/ग_लिखो */
	res.response_route = tb_cfg_get_route(header);
	res.err = check_header(pkg, len, type, route);
	वापस res;
पूर्ण

अटल व्योम tb_cfg_prपूर्णांक_error(काष्ठा tb_ctl *ctl,
			       स्थिर काष्ठा tb_cfg_result *res)
अणु
	WARN_ON(res->err != 1);
	चयन (res->tb_error) अणु
	हाल TB_CFG_ERROR_PORT_NOT_CONNECTED:
		/* Port is not connected. This can happen during surprise
		 * removal. Do not warn. */
		वापस;
	हाल TB_CFG_ERROR_INVALID_CONFIG_SPACE:
		/*
		 * Invalid cfg_space/offset/length combination in
		 * cfg_पढ़ो/cfg_ग_लिखो.
		 */
		tb_ctl_dbg(ctl, "%llx:%x: invalid config space or offset\n",
			   res->response_route, res->response_port);
		वापस;
	हाल TB_CFG_ERROR_NO_SUCH_PORT:
		/*
		 * - The route contains a non-existent port.
		 * - The route contains a non-PHY port (e.g. PCIe).
		 * - The port in cfg_पढ़ो/cfg_ग_लिखो करोes not exist.
		 */
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Invalid port\n",
			res->response_route, res->response_port);
		वापस;
	हाल TB_CFG_ERROR_LOOP:
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Route contains a loop\n",
			res->response_route, res->response_port);
		वापस;
	हाल TB_CFG_ERROR_LOCK:
		tb_ctl_warn(ctl, "%llx:%x: downstream port is locked\n",
			    res->response_route, res->response_port);
		वापस;
	शेष:
		/* 5,6,7,9 and 11 are also valid error codes */
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Unknown error\n",
			res->response_route, res->response_port);
		वापस;
	पूर्ण
पूर्ण

अटल __be32 tb_crc(स्थिर व्योम *data, माप_प्रकार len)
अणु
	वापस cpu_to_be32(~__crc32c_le(~0, data, len));
पूर्ण

अटल व्योम tb_ctl_pkg_मुक्त(काष्ठा ctl_pkg *pkg)
अणु
	अगर (pkg) अणु
		dma_pool_मुक्त(pkg->ctl->frame_pool,
			      pkg->buffer, pkg->frame.buffer_phy);
		kमुक्त(pkg);
	पूर्ण
पूर्ण

अटल काष्ठा ctl_pkg *tb_ctl_pkg_alloc(काष्ठा tb_ctl *ctl)
अणु
	काष्ठा ctl_pkg *pkg = kzalloc(माप(*pkg), GFP_KERNEL);
	अगर (!pkg)
		वापस शून्य;
	pkg->ctl = ctl;
	pkg->buffer = dma_pool_alloc(ctl->frame_pool, GFP_KERNEL,
				     &pkg->frame.buffer_phy);
	अगर (!pkg->buffer) अणु
		kमुक्त(pkg);
		वापस शून्य;
	पूर्ण
	वापस pkg;
पूर्ण


/* RX/TX handling */

अटल व्योम tb_ctl_tx_callback(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame,
			       bool canceled)
अणु
	काष्ठा ctl_pkg *pkg = container_of(frame, typeof(*pkg), frame);
	tb_ctl_pkg_मुक्त(pkg);
पूर्ण

/*
 * tb_cfg_tx() - transmit a packet on the control channel
 *
 * len must be a multiple of four.
 *
 * Return: Returns 0 on success or an error code on failure.
 */
अटल पूर्णांक tb_ctl_tx(काष्ठा tb_ctl *ctl, स्थिर व्योम *data, माप_प्रकार len,
		     क्रमागत tb_cfg_pkg_type type)
अणु
	पूर्णांक res;
	काष्ठा ctl_pkg *pkg;
	अगर (len % 4 != 0) अणु /* required क्रम le->be conversion */
		tb_ctl_WARN(ctl, "TX: invalid size: %zu\n", len);
		वापस -EINVAL;
	पूर्ण
	अगर (len > TB_FRAME_SIZE - 4) अणु /* checksum is 4 bytes */
		tb_ctl_WARN(ctl, "TX: packet too large: %zu/%d\n",
			    len, TB_FRAME_SIZE - 4);
		वापस -EINVAL;
	पूर्ण
	pkg = tb_ctl_pkg_alloc(ctl);
	अगर (!pkg)
		वापस -ENOMEM;
	pkg->frame.callback = tb_ctl_tx_callback;
	pkg->frame.size = len + 4;
	pkg->frame.sof = type;
	pkg->frame.eof = type;
	cpu_to_be32_array(pkg->buffer, data, len / 4);
	*(__be32 *) (pkg->buffer + len) = tb_crc(pkg->buffer, len);

	res = tb_ring_tx(ctl->tx, &pkg->frame);
	अगर (res) /* ring is stopped */
		tb_ctl_pkg_मुक्त(pkg);
	वापस res;
पूर्ण

/*
 * tb_ctl_handle_event() - acknowledge a plug event, invoke ctl->callback
 */
अटल bool tb_ctl_handle_event(काष्ठा tb_ctl *ctl, क्रमागत tb_cfg_pkg_type type,
				काष्ठा ctl_pkg *pkg, माप_प्रकार size)
अणु
	वापस ctl->callback(ctl->callback_data, type, pkg->buffer, size);
पूर्ण

अटल व्योम tb_ctl_rx_submit(काष्ठा ctl_pkg *pkg)
अणु
	tb_ring_rx(pkg->ctl->rx, &pkg->frame); /*
					     * We ignore failures during stop.
					     * All rx packets are referenced
					     * from ctl->rx_packets, so we करो
					     * not loose them.
					     */
पूर्ण

अटल पूर्णांक tb_async_error(स्थिर काष्ठा ctl_pkg *pkg)
अणु
	स्थिर काष्ठा cfg_error_pkg *error = (स्थिर काष्ठा cfg_error_pkg *)pkg;

	अगर (pkg->frame.eof != TB_CFG_PKG_ERROR)
		वापस false;

	चयन (error->error) अणु
	हाल TB_CFG_ERROR_LINK_ERROR:
	हाल TB_CFG_ERROR_HEC_ERROR_DETECTED:
	हाल TB_CFG_ERROR_FLOW_CONTROL_ERROR:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम tb_ctl_rx_callback(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame,
			       bool canceled)
अणु
	काष्ठा ctl_pkg *pkg = container_of(frame, typeof(*pkg), frame);
	काष्ठा tb_cfg_request *req;
	__be32 crc32;

	अगर (canceled)
		वापस; /*
			 * ring is stopped, packet is referenced from
			 * ctl->rx_packets.
			 */

	अगर (frame->size < 4 || frame->size % 4 != 0) अणु
		tb_ctl_err(pkg->ctl, "RX: invalid size %#x, dropping packet\n",
			   frame->size);
		जाओ rx;
	पूर्ण

	frame->size -= 4; /* हटाओ checksum */
	crc32 = tb_crc(pkg->buffer, frame->size);
	be32_to_cpu_array(pkg->buffer, pkg->buffer, frame->size / 4);

	चयन (frame->eof) अणु
	हाल TB_CFG_PKG_READ:
	हाल TB_CFG_PKG_WRITE:
	हाल TB_CFG_PKG_ERROR:
	हाल TB_CFG_PKG_OVERRIDE:
	हाल TB_CFG_PKG_RESET:
		अगर (*(__be32 *)(pkg->buffer + frame->size) != crc32) अणु
			tb_ctl_err(pkg->ctl,
				   "RX: checksum mismatch, dropping packet\n");
			जाओ rx;
		पूर्ण
		अगर (tb_async_error(pkg)) अणु
			tb_ctl_handle_event(pkg->ctl, frame->eof,
					    pkg, frame->size);
			जाओ rx;
		पूर्ण
		अवरोध;

	हाल TB_CFG_PKG_EVENT:
	हाल TB_CFG_PKG_XDOMAIN_RESP:
	हाल TB_CFG_PKG_XDOMAIN_REQ:
		अगर (*(__be32 *)(pkg->buffer + frame->size) != crc32) अणु
			tb_ctl_err(pkg->ctl,
				   "RX: checksum mismatch, dropping packet\n");
			जाओ rx;
		पूर्ण
		fallthrough;
	हाल TB_CFG_PKG_ICM_EVENT:
		अगर (tb_ctl_handle_event(pkg->ctl, frame->eof, pkg, frame->size))
			जाओ rx;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/*
	 * The received packet will be processed only अगर there is an
	 * active request and that the packet is what is expected. This
	 * prevents packets such as replies coming after समयout has
	 * triggered from messing with the active requests.
	 */
	req = tb_cfg_request_find(pkg->ctl, pkg);
	अगर (req) अणु
		अगर (req->copy(req, pkg))
			schedule_work(&req->work);
		tb_cfg_request_put(req);
	पूर्ण

rx:
	tb_ctl_rx_submit(pkg);
पूर्ण

अटल व्योम tb_cfg_request_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_cfg_request *req = container_of(work, typeof(*req), work);

	अगर (!test_bit(TB_CFG_REQUEST_CANCELED, &req->flags))
		req->callback(req->callback_data);

	tb_cfg_request_dequeue(req);
	tb_cfg_request_put(req);
पूर्ण

/**
 * tb_cfg_request() - Start control request not रुकोing क्रम it to complete
 * @ctl: Control channel to use
 * @req: Request to start
 * @callback: Callback called when the request is completed
 * @callback_data: Data to be passed to @callback
 *
 * This queues @req on the given control channel without रुकोing क्रम it
 * to complete. When the request completes @callback is called.
 */
पूर्णांक tb_cfg_request(काष्ठा tb_ctl *ctl, काष्ठा tb_cfg_request *req,
		   व्योम (*callback)(व्योम *), व्योम *callback_data)
अणु
	पूर्णांक ret;

	req->flags = 0;
	req->callback = callback;
	req->callback_data = callback_data;
	INIT_WORK(&req->work, tb_cfg_request_work);
	INIT_LIST_HEAD(&req->list);

	tb_cfg_request_get(req);
	ret = tb_cfg_request_enqueue(ctl, req);
	अगर (ret)
		जाओ err_put;

	ret = tb_ctl_tx(ctl, req->request, req->request_size,
			req->request_type);
	अगर (ret)
		जाओ err_dequeue;

	अगर (!req->response)
		schedule_work(&req->work);

	वापस 0;

err_dequeue:
	tb_cfg_request_dequeue(req);
err_put:
	tb_cfg_request_put(req);

	वापस ret;
पूर्ण

/**
 * tb_cfg_request_cancel() - Cancel a control request
 * @req: Request to cancel
 * @err: Error to assign to the request
 *
 * This function can be used to cancel ongoing request. It will रुको
 * until the request is not active anymore.
 */
व्योम tb_cfg_request_cancel(काष्ठा tb_cfg_request *req, पूर्णांक err)
अणु
	set_bit(TB_CFG_REQUEST_CANCELED, &req->flags);
	schedule_work(&req->work);
	रुको_event(tb_cfg_request_cancel_queue, !tb_cfg_request_is_active(req));
	req->result.err = err;
पूर्ण

अटल व्योम tb_cfg_request_complete(व्योम *data)
अणु
	complete(data);
पूर्ण

/**
 * tb_cfg_request_sync() - Start control request and रुको until it completes
 * @ctl: Control channel to use
 * @req: Request to start
 * @समयout_msec: Timeout how दीर्घ to रुको @req to complete
 *
 * Starts a control request and रुकोs until it completes. If समयout
 * triggers the request is canceled beक्रमe function वापसs. Note the
 * caller needs to make sure only one message क्रम given चयन is active
 * at a समय.
 */
काष्ठा tb_cfg_result tb_cfg_request_sync(काष्ठा tb_ctl *ctl,
					 काष्ठा tb_cfg_request *req,
					 पूर्णांक समयout_msec)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(समयout_msec);
	काष्ठा tb_cfg_result res = अणु 0 पूर्ण;
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक ret;

	ret = tb_cfg_request(ctl, req, tb_cfg_request_complete, &करोne);
	अगर (ret) अणु
		res.err = ret;
		वापस res;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&करोne, समयout))
		tb_cfg_request_cancel(req, -ETIMEDOUT);

	flush_work(&req->work);

	वापस req->result;
पूर्ण

/* खुला पूर्णांकerface, alloc/start/stop/मुक्त */

/**
 * tb_ctl_alloc() - allocate a control channel
 * @nhi: Poपूर्णांकer to NHI
 * @समयout_msec: Default समयout used with non-raw control messages
 * @cb: Callback called क्रम plug events
 * @cb_data: Data passed to @cb
 *
 * cb will be invoked once क्रम every hot plug event.
 *
 * Return: Returns a poपूर्णांकer on success or शून्य on failure.
 */
काष्ठा tb_ctl *tb_ctl_alloc(काष्ठा tb_nhi *nhi, पूर्णांक समयout_msec, event_cb cb,
			    व्योम *cb_data)
अणु
	पूर्णांक i;
	काष्ठा tb_ctl *ctl = kzalloc(माप(*ctl), GFP_KERNEL);
	अगर (!ctl)
		वापस शून्य;
	ctl->nhi = nhi;
	ctl->समयout_msec = समयout_msec;
	ctl->callback = cb;
	ctl->callback_data = cb_data;

	mutex_init(&ctl->request_queue_lock);
	INIT_LIST_HEAD(&ctl->request_queue);
	ctl->frame_pool = dma_pool_create("thunderbolt_ctl", &nhi->pdev->dev,
					 TB_FRAME_SIZE, 4, 0);
	अगर (!ctl->frame_pool)
		जाओ err;

	ctl->tx = tb_ring_alloc_tx(nhi, 0, 10, RING_FLAG_NO_SUSPEND);
	अगर (!ctl->tx)
		जाओ err;

	ctl->rx = tb_ring_alloc_rx(nhi, 0, 10, RING_FLAG_NO_SUSPEND, 0, 0xffff,
				   0xffff, शून्य, शून्य);
	अगर (!ctl->rx)
		जाओ err;

	क्रम (i = 0; i < TB_CTL_RX_PKG_COUNT; i++) अणु
		ctl->rx_packets[i] = tb_ctl_pkg_alloc(ctl);
		अगर (!ctl->rx_packets[i])
			जाओ err;
		ctl->rx_packets[i]->frame.callback = tb_ctl_rx_callback;
	पूर्ण

	tb_ctl_dbg(ctl, "control channel created\n");
	वापस ctl;
err:
	tb_ctl_मुक्त(ctl);
	वापस शून्य;
पूर्ण

/**
 * tb_ctl_मुक्त() - मुक्त a control channel
 * @ctl: Control channel to मुक्त
 *
 * Must be called after tb_ctl_stop.
 *
 * Must NOT be called from ctl->callback.
 */
व्योम tb_ctl_मुक्त(काष्ठा tb_ctl *ctl)
अणु
	पूर्णांक i;

	अगर (!ctl)
		वापस;

	अगर (ctl->rx)
		tb_ring_मुक्त(ctl->rx);
	अगर (ctl->tx)
		tb_ring_मुक्त(ctl->tx);

	/* मुक्त RX packets */
	क्रम (i = 0; i < TB_CTL_RX_PKG_COUNT; i++)
		tb_ctl_pkg_मुक्त(ctl->rx_packets[i]);


	dma_pool_destroy(ctl->frame_pool);
	kमुक्त(ctl);
पूर्ण

/**
 * tb_cfg_start() - start/resume the control channel
 * @ctl: Control channel to start
 */
व्योम tb_ctl_start(काष्ठा tb_ctl *ctl)
अणु
	पूर्णांक i;
	tb_ctl_dbg(ctl, "control channel starting...\n");
	tb_ring_start(ctl->tx); /* is used to ack hotplug packets, start first */
	tb_ring_start(ctl->rx);
	क्रम (i = 0; i < TB_CTL_RX_PKG_COUNT; i++)
		tb_ctl_rx_submit(ctl->rx_packets[i]);

	ctl->running = true;
पूर्ण

/**
 * tb_ctrl_stop() - छोड़ो the control channel
 * @ctl: Control channel to stop
 *
 * All invocations of ctl->callback will have finished after this method
 * वापसs.
 *
 * Must NOT be called from ctl->callback.
 */
व्योम tb_ctl_stop(काष्ठा tb_ctl *ctl)
अणु
	mutex_lock(&ctl->request_queue_lock);
	ctl->running = false;
	mutex_unlock(&ctl->request_queue_lock);

	tb_ring_stop(ctl->rx);
	tb_ring_stop(ctl->tx);

	अगर (!list_empty(&ctl->request_queue))
		tb_ctl_WARN(ctl, "dangling request in request_queue\n");
	INIT_LIST_HEAD(&ctl->request_queue);
	tb_ctl_dbg(ctl, "control channel stopped\n");
पूर्ण

/* खुला पूर्णांकerface, commands */

/**
 * tb_cfg_ack_plug() - Ack hot plug/unplug event
 * @ctl: Control channel to use
 * @route: Router that originated the event
 * @port: Port where the hot plug/unplug happened
 * @unplug: Ack hot plug or unplug
 *
 * Call this as response क्रम hot plug/unplug event to ack it.
 * Returns %0 on success or an error code on failure.
 */
पूर्णांक tb_cfg_ack_plug(काष्ठा tb_ctl *ctl, u64 route, u32 port, bool unplug)
अणु
	काष्ठा cfg_error_pkg pkg = अणु
		.header = tb_cfg_make_header(route),
		.port = port,
		.error = TB_CFG_ERROR_ACK_PLUG_EVENT,
		.pg = unplug ? TB_CFG_ERROR_PG_HOT_UNPLUG
			     : TB_CFG_ERROR_PG_HOT_PLUG,
	पूर्ण;
	tb_ctl_dbg(ctl, "acking hot %splug event on %llx:%x\n",
		   unplug ? "un" : "", route, port);
	वापस tb_ctl_tx(ctl, &pkg, माप(pkg), TB_CFG_PKG_ERROR);
पूर्ण

अटल bool tb_cfg_match(स्थिर काष्ठा tb_cfg_request *req,
			 स्थिर काष्ठा ctl_pkg *pkg)
अणु
	u64 route = tb_cfg_get_route(pkg->buffer) & ~BIT_ULL(63);

	अगर (pkg->frame.eof == TB_CFG_PKG_ERROR)
		वापस true;

	अगर (pkg->frame.eof != req->response_type)
		वापस false;
	अगर (route != tb_cfg_get_route(req->request))
		वापस false;
	अगर (pkg->frame.size != req->response_size)
		वापस false;

	अगर (pkg->frame.eof == TB_CFG_PKG_READ ||
	    pkg->frame.eof == TB_CFG_PKG_WRITE) अणु
		स्थिर काष्ठा cfg_पढ़ो_pkg *req_hdr = req->request;
		स्थिर काष्ठा cfg_पढ़ो_pkg *res_hdr = pkg->buffer;

		अगर (req_hdr->addr.seq != res_hdr->addr.seq)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tb_cfg_copy(काष्ठा tb_cfg_request *req, स्थिर काष्ठा ctl_pkg *pkg)
अणु
	काष्ठा tb_cfg_result res;

	/* Now make sure it is in expected क्रमmat */
	res = parse_header(pkg, req->response_size, req->response_type,
			   tb_cfg_get_route(req->request));
	अगर (!res.err)
		स_नकल(req->response, pkg->buffer, req->response_size);

	req->result = res;

	/* Always complete when first response is received */
	वापस true;
पूर्ण

/**
 * tb_cfg_reset() - send a reset packet and रुको क्रम a response
 * @ctl: Control channel poपूर्णांकer
 * @route: Router string क्रम the router to send reset
 *
 * If the चयन at route is incorrectly configured then we will not receive a
 * reply (even though the चयन will reset). The caller should check क्रम
 * -ETIMEDOUT and attempt to reconfigure the चयन.
 */
काष्ठा tb_cfg_result tb_cfg_reset(काष्ठा tb_ctl *ctl, u64 route)
अणु
	काष्ठा cfg_reset_pkg request = अणु .header = tb_cfg_make_header(route) पूर्ण;
	काष्ठा tb_cfg_result res = अणु 0 पूर्ण;
	काष्ठा tb_cfg_header reply;
	काष्ठा tb_cfg_request *req;

	req = tb_cfg_request_alloc();
	अगर (!req) अणु
		res.err = -ENOMEM;
		वापस res;
	पूर्ण

	req->match = tb_cfg_match;
	req->copy = tb_cfg_copy;
	req->request = &request;
	req->request_size = माप(request);
	req->request_type = TB_CFG_PKG_RESET;
	req->response = &reply;
	req->response_size = माप(reply);
	req->response_type = TB_CFG_PKG_RESET;

	res = tb_cfg_request_sync(ctl, req, ctl->समयout_msec);

	tb_cfg_request_put(req);

	वापस res;
पूर्ण

/**
 * tb_cfg_पढ़ो_raw() - पढ़ो from config space पूर्णांकo buffer
 * @ctl: Poपूर्णांकer to the control channel
 * @buffer: Buffer where the data is पढ़ो
 * @route: Route string of the router
 * @port: Port number when पढ़ोing from %TB_CFG_PORT, %0 otherwise
 * @space: Config space selector
 * @offset: Dword word offset of the रेजिस्टर to start पढ़ोing
 * @length: Number of dwords to पढ़ो
 * @समयout_msec: Timeout in ms how दीर्घ to रुको क्रम the response
 *
 * Reads from router config space without translating the possible error.
 */
काष्ठा tb_cfg_result tb_cfg_पढ़ो_raw(काष्ठा tb_ctl *ctl, व्योम *buffer,
		u64 route, u32 port, क्रमागत tb_cfg_space space,
		u32 offset, u32 length, पूर्णांक समयout_msec)
अणु
	काष्ठा tb_cfg_result res = अणु 0 पूर्ण;
	काष्ठा cfg_पढ़ो_pkg request = अणु
		.header = tb_cfg_make_header(route),
		.addr = अणु
			.port = port,
			.space = space,
			.offset = offset,
			.length = length,
		पूर्ण,
	पूर्ण;
	काष्ठा cfg_ग_लिखो_pkg reply;
	पूर्णांक retries = 0;

	जबतक (retries < TB_CTL_RETRIES) अणु
		काष्ठा tb_cfg_request *req;

		req = tb_cfg_request_alloc();
		अगर (!req) अणु
			res.err = -ENOMEM;
			वापस res;
		पूर्ण

		request.addr.seq = retries++;

		req->match = tb_cfg_match;
		req->copy = tb_cfg_copy;
		req->request = &request;
		req->request_size = माप(request);
		req->request_type = TB_CFG_PKG_READ;
		req->response = &reply;
		req->response_size = 12 + 4 * length;
		req->response_type = TB_CFG_PKG_READ;

		res = tb_cfg_request_sync(ctl, req, समयout_msec);

		tb_cfg_request_put(req);

		अगर (res.err != -ETIMEDOUT)
			अवरोध;

		/* Wait a bit (arbitrary समय) until we send a retry */
		usleep_range(10, 100);
	पूर्ण

	अगर (res.err)
		वापस res;

	res.response_port = reply.addr.port;
	res.err = check_config_address(reply.addr, space, offset, length);
	अगर (!res.err)
		स_नकल(buffer, &reply.data, 4 * length);
	वापस res;
पूर्ण

/**
 * tb_cfg_ग_लिखो() - ग_लिखो from buffer पूर्णांकo config space
 * @ctl: Poपूर्णांकer to the control channel
 * @buffer: Data to ग_लिखो
 * @route: Route string of the router
 * @port: Port number when writing to %TB_CFG_PORT, %0 otherwise
 * @space: Config space selector
 * @offset: Dword word offset of the रेजिस्टर to start writing
 * @length: Number of dwords to ग_लिखो
 * @समयout_msec: Timeout in ms how दीर्घ to रुको क्रम the response
 *
 * Writes to router config space without translating the possible error.
 */
काष्ठा tb_cfg_result tb_cfg_ग_लिखो_raw(काष्ठा tb_ctl *ctl, स्थिर व्योम *buffer,
		u64 route, u32 port, क्रमागत tb_cfg_space space,
		u32 offset, u32 length, पूर्णांक समयout_msec)
अणु
	काष्ठा tb_cfg_result res = अणु 0 पूर्ण;
	काष्ठा cfg_ग_लिखो_pkg request = अणु
		.header = tb_cfg_make_header(route),
		.addr = अणु
			.port = port,
			.space = space,
			.offset = offset,
			.length = length,
		पूर्ण,
	पूर्ण;
	काष्ठा cfg_पढ़ो_pkg reply;
	पूर्णांक retries = 0;

	स_नकल(&request.data, buffer, length * 4);

	जबतक (retries < TB_CTL_RETRIES) अणु
		काष्ठा tb_cfg_request *req;

		req = tb_cfg_request_alloc();
		अगर (!req) अणु
			res.err = -ENOMEM;
			वापस res;
		पूर्ण

		request.addr.seq = retries++;

		req->match = tb_cfg_match;
		req->copy = tb_cfg_copy;
		req->request = &request;
		req->request_size = 12 + 4 * length;
		req->request_type = TB_CFG_PKG_WRITE;
		req->response = &reply;
		req->response_size = माप(reply);
		req->response_type = TB_CFG_PKG_WRITE;

		res = tb_cfg_request_sync(ctl, req, समयout_msec);

		tb_cfg_request_put(req);

		अगर (res.err != -ETIMEDOUT)
			अवरोध;

		/* Wait a bit (arbitrary समय) until we send a retry */
		usleep_range(10, 100);
	पूर्ण

	अगर (res.err)
		वापस res;

	res.response_port = reply.addr.port;
	res.err = check_config_address(reply.addr, space, offset, length);
	वापस res;
पूर्ण

अटल पूर्णांक tb_cfg_get_error(काष्ठा tb_ctl *ctl, क्रमागत tb_cfg_space space,
			    स्थिर काष्ठा tb_cfg_result *res)
अणु
	/*
	 * For unimplemented ports access to port config space may वापस
	 * TB_CFG_ERROR_INVALID_CONFIG_SPACE (alternatively their type is
	 * set to TB_TYPE_INACTIVE). In the क्रमmer हाल वापस -ENODEV so
	 * that the caller can mark the port as disabled.
	 */
	अगर (space == TB_CFG_PORT &&
	    res->tb_error == TB_CFG_ERROR_INVALID_CONFIG_SPACE)
		वापस -ENODEV;

	tb_cfg_prपूर्णांक_error(ctl, res);

	अगर (res->tb_error == TB_CFG_ERROR_LOCK)
		वापस -EACCES;
	अन्यथा अगर (res->tb_error == TB_CFG_ERROR_PORT_NOT_CONNECTED)
		वापस -ENOTCONN;

	वापस -EIO;
पूर्ण

पूर्णांक tb_cfg_पढ़ो(काष्ठा tb_ctl *ctl, व्योम *buffer, u64 route, u32 port,
		क्रमागत tb_cfg_space space, u32 offset, u32 length)
अणु
	काष्ठा tb_cfg_result res = tb_cfg_पढ़ो_raw(ctl, buffer, route, port,
			space, offset, length, ctl->समयout_msec);
	चयन (res.err) अणु
	हाल 0:
		/* Success */
		अवरोध;

	हाल 1:
		/* Thunderbolt error, tb_error holds the actual number */
		वापस tb_cfg_get_error(ctl, space, &res);

	हाल -ETIMEDOUT:
		tb_ctl_warn(ctl, "%llx: timeout reading config space %u from %#x\n",
			    route, space, offset);
		अवरोध;

	शेष:
		WARN(1, "tb_cfg_read: %d\n", res.err);
		अवरोध;
	पूर्ण
	वापस res.err;
पूर्ण

पूर्णांक tb_cfg_ग_लिखो(काष्ठा tb_ctl *ctl, स्थिर व्योम *buffer, u64 route, u32 port,
		 क्रमागत tb_cfg_space space, u32 offset, u32 length)
अणु
	काष्ठा tb_cfg_result res = tb_cfg_ग_लिखो_raw(ctl, buffer, route, port,
			space, offset, length, ctl->समयout_msec);
	चयन (res.err) अणु
	हाल 0:
		/* Success */
		अवरोध;

	हाल 1:
		/* Thunderbolt error, tb_error holds the actual number */
		वापस tb_cfg_get_error(ctl, space, &res);

	हाल -ETIMEDOUT:
		tb_ctl_warn(ctl, "%llx: timeout writing config space %u to %#x\n",
			    route, space, offset);
		अवरोध;

	शेष:
		WARN(1, "tb_cfg_write: %d\n", res.err);
		अवरोध;
	पूर्ण
	वापस res.err;
पूर्ण

/**
 * tb_cfg_get_upstream_port() - get upstream port number of चयन at route
 * @ctl: Poपूर्णांकer to the control channel
 * @route: Route string of the router
 *
 * Reads the first dword from the चयनes TB_CFG_SWITCH config area and
 * वापसs the port number from which the reply originated.
 *
 * Return: Returns the upstream port number on success or an error code on
 * failure.
 */
पूर्णांक tb_cfg_get_upstream_port(काष्ठा tb_ctl *ctl, u64 route)
अणु
	u32 dummy;
	काष्ठा tb_cfg_result res = tb_cfg_पढ़ो_raw(ctl, &dummy, route, 0,
						   TB_CFG_SWITCH, 0, 1,
						   ctl->समयout_msec);
	अगर (res.err == 1)
		वापस -EIO;
	अगर (res.err)
		वापस res.err;
	वापस res.response_port;
पूर्ण
