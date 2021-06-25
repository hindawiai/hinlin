<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (c) 2017 Stefano Stabellini <stefano@aporeto.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/socket.h>

#समावेश <net/sock.h>

#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/पूर्णांकerface/io/pvcalls.h>

#समावेश "pvcalls-front.h"

#घोषणा PVCALLS_INVALID_ID अच_पूर्णांक_उच्च
#घोषणा PVCALLS_RING_ORDER XENBUS_MAX_RING_GRANT_ORDER
#घोषणा PVCALLS_NR_RSP_PER_RING __CONST_RING_SIZE(xen_pvcalls, XEN_PAGE_SIZE)
#घोषणा PVCALLS_FRONT_MAX_SPIN 5000

अटल काष्ठा proto pvcalls_proto = अणु
	.name	= "PVCalls",
	.owner	= THIS_MODULE,
	.obj_size = माप(काष्ठा sock),
पूर्ण;

काष्ठा pvcalls_bedata अणु
	काष्ठा xen_pvcalls_front_ring ring;
	grant_ref_t ref;
	पूर्णांक irq;

	काष्ठा list_head socket_mappings;
	spinlock_t socket_lock;

	रुको_queue_head_t inflight_req;
	काष्ठा xen_pvcalls_response rsp[PVCALLS_NR_RSP_PER_RING];
पूर्ण;
/* Only one front/back connection supported. */
अटल काष्ठा xenbus_device *pvcalls_front_dev;
अटल atomic_t pvcalls_refcount;

/* first increment refcount, then proceed */
#घोषणा pvcalls_enter() अणु               \
	atomic_inc(&pvcalls_refcount);      \
पूर्ण

/* first complete other operations, then decrement refcount */
#घोषणा pvcalls_निकास() अणु                \
	atomic_dec(&pvcalls_refcount);      \
पूर्ण

काष्ठा sock_mapping अणु
	bool active_socket;
	काष्ठा list_head list;
	काष्ठा socket *sock;
	atomic_t refcount;
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक irq;
			grant_ref_t ref;
			काष्ठा pvcalls_data_पूर्णांकf *ring;
			काष्ठा pvcalls_data data;
			काष्ठा mutex in_mutex;
			काष्ठा mutex out_mutex;

			रुको_queue_head_t inflight_conn_req;
		पूर्ण active;
		काष्ठा अणु
		/*
		 * Socket status, needs to be 64-bit aligned due to the
		 * test_and_* functions which have this requirement on arm64.
		 */
#घोषणा PVCALLS_STATUS_UNINITALIZED  0
#घोषणा PVCALLS_STATUS_BIND          1
#घोषणा PVCALLS_STATUS_LISTEN        2
			uपूर्णांक8_t status __attribute__((aligned(8)));
		/*
		 * Internal state-machine flags.
		 * Only one accept operation can be inflight क्रम a socket.
		 * Only one poll operation can be inflight क्रम a given socket.
		 * flags needs to be 64-bit aligned due to the test_and_*
		 * functions which have this requirement on arm64.
		 */
#घोषणा PVCALLS_FLAG_ACCEPT_INFLIGHT 0
#घोषणा PVCALLS_FLAG_POLL_INFLIGHT   1
#घोषणा PVCALLS_FLAG_POLL_RET        2
			uपूर्णांक8_t flags __attribute__((aligned(8)));
			uपूर्णांक32_t inflight_req_id;
			काष्ठा sock_mapping *accept_map;
			रुको_queue_head_t inflight_accept_req;
		पूर्ण passive;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा sock_mapping *pvcalls_enter_sock(काष्ठा socket *sock)
अणु
	काष्ठा sock_mapping *map;

	अगर (!pvcalls_front_dev ||
		dev_get_drvdata(&pvcalls_front_dev->dev) == शून्य)
		वापस ERR_PTR(-ENOTCONN);

	map = (काष्ठा sock_mapping *)sock->sk->sk_send_head;
	अगर (map == शून्य)
		वापस ERR_PTR(-ENOTSOCK);

	pvcalls_enter();
	atomic_inc(&map->refcount);
	वापस map;
पूर्ण

अटल अंतरभूत व्योम pvcalls_निकास_sock(काष्ठा socket *sock)
अणु
	काष्ठा sock_mapping *map;

	map = (काष्ठा sock_mapping *)sock->sk->sk_send_head;
	atomic_dec(&map->refcount);
	pvcalls_निकास();
पूर्ण

अटल अंतरभूत पूर्णांक get_request(काष्ठा pvcalls_bedata *bedata, पूर्णांक *req_id)
अणु
	*req_id = bedata->ring.req_prod_pvt & (RING_SIZE(&bedata->ring) - 1);
	अगर (RING_FULL(&bedata->ring) ||
	    bedata->rsp[*req_id].req_id != PVCALLS_INVALID_ID)
		वापस -EAGAIN;
	वापस 0;
पूर्ण

अटल bool pvcalls_front_ग_लिखो_toकरो(काष्ठा sock_mapping *map)
अणु
	काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf = map->active.ring;
	RING_IDX cons, prod, size = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);
	पूर्णांक32_t error;

	error = पूर्णांकf->out_error;
	अगर (error == -ENOTCONN)
		वापस false;
	अगर (error != 0)
		वापस true;

	cons = पूर्णांकf->out_cons;
	prod = पूर्णांकf->out_prod;
	वापस !!(size - pvcalls_queued(prod, cons, size));
पूर्ण

अटल bool pvcalls_front_पढ़ो_toकरो(काष्ठा sock_mapping *map)
अणु
	काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf = map->active.ring;
	RING_IDX cons, prod;
	पूर्णांक32_t error;

	cons = पूर्णांकf->in_cons;
	prod = पूर्णांकf->in_prod;
	error = पूर्णांकf->in_error;
	वापस (error != 0 ||
		pvcalls_queued(prod, cons,
			       XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER)) != 0);
पूर्ण

अटल irqवापस_t pvcalls_front_event_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xenbus_device *dev = dev_id;
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा xen_pvcalls_response *rsp;
	uपूर्णांक8_t *src, *dst;
	पूर्णांक req_id = 0, more = 0, करोne = 0;

	अगर (dev == शून्य)
		वापस IRQ_HANDLED;

	pvcalls_enter();
	bedata = dev_get_drvdata(&dev->dev);
	अगर (bedata == शून्य) अणु
		pvcalls_निकास();
		वापस IRQ_HANDLED;
	पूर्ण

again:
	जबतक (RING_HAS_UNCONSUMED_RESPONSES(&bedata->ring)) अणु
		rsp = RING_GET_RESPONSE(&bedata->ring, bedata->ring.rsp_cons);

		req_id = rsp->req_id;
		अगर (rsp->cmd == PVCALLS_POLL) अणु
			काष्ठा sock_mapping *map = (काष्ठा sock_mapping *)(uपूर्णांकptr_t)
						   rsp->u.poll.id;

			clear_bit(PVCALLS_FLAG_POLL_INFLIGHT,
				  (व्योम *)&map->passive.flags);
			/*
			 * clear INFLIGHT, then set RET. It pairs with
			 * the checks at the beginning of
			 * pvcalls_front_poll_passive.
			 */
			smp_wmb();
			set_bit(PVCALLS_FLAG_POLL_RET,
				(व्योम *)&map->passive.flags);
		पूर्ण अन्यथा अणु
			dst = (uपूर्णांक8_t *)&bedata->rsp[req_id] +
			      माप(rsp->req_id);
			src = (uपूर्णांक8_t *)rsp + माप(rsp->req_id);
			स_नकल(dst, src, माप(*rsp) - माप(rsp->req_id));
			/*
			 * First copy the rest of the data, then req_id. It is
			 * paired with the barrier when accessing bedata->rsp.
			 */
			smp_wmb();
			bedata->rsp[req_id].req_id = req_id;
		पूर्ण

		करोne = 1;
		bedata->ring.rsp_cons++;
	पूर्ण

	RING_FINAL_CHECK_FOR_RESPONSES(&bedata->ring, more);
	अगर (more)
		जाओ again;
	अगर (करोne)
		wake_up(&bedata->inflight_req);
	pvcalls_निकास();
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pvcalls_front_मुक्त_map(काष्ठा pvcalls_bedata *bedata,
				   काष्ठा sock_mapping *map)
अणु
	पूर्णांक i;

	unbind_from_irqhandler(map->active.irq, map);

	spin_lock(&bedata->socket_lock);
	अगर (!list_empty(&map->list))
		list_del_init(&map->list);
	spin_unlock(&bedata->socket_lock);

	क्रम (i = 0; i < (1 << PVCALLS_RING_ORDER); i++)
		gnttab_end_क्रमeign_access(map->active.ring->ref[i], 0, 0);
	gnttab_end_क्रमeign_access(map->active.ref, 0, 0);
	मुक्त_page((अचिन्हित दीर्घ)map->active.ring);

	kमुक्त(map);
पूर्ण

अटल irqवापस_t pvcalls_front_conn_handler(पूर्णांक irq, व्योम *sock_map)
अणु
	काष्ठा sock_mapping *map = sock_map;

	अगर (map == शून्य)
		वापस IRQ_HANDLED;

	wake_up_पूर्णांकerruptible(&map->active.inflight_conn_req);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक pvcalls_front_socket(काष्ठा socket *sock)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map = शून्य;
	काष्ठा xen_pvcalls_request *req;
	पूर्णांक notअगरy, req_id, ret;

	/*
	 * PVCalls only supports करोमुख्य AF_INET,
	 * type SOCK_STREAM and protocol 0 sockets क्रम now.
	 *
	 * Check socket type here, AF_INET and protocol checks are करोne
	 * by the caller.
	 */
	अगर (sock->type != SOCK_STREAM)
		वापस -EOPNOTSUPP;

	pvcalls_enter();
	अगर (!pvcalls_front_dev) अणु
		pvcalls_निकास();
		वापस -EACCES;
	पूर्ण
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य) अणु
		pvcalls_निकास();
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&bedata->socket_lock);

	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		kमुक्त(map);
		spin_unlock(&bedata->socket_lock);
		pvcalls_निकास();
		वापस ret;
	पूर्ण

	/*
	 * sock->sk->sk_send_head is not used क्रम ip sockets: reuse the
	 * field to store a poपूर्णांकer to the काष्ठा sock_mapping
	 * corresponding to the socket. This way, we can easily get the
	 * काष्ठा sock_mapping from the काष्ठा socket.
	 */
	sock->sk->sk_send_head = (व्योम *)map;
	list_add_tail(&map->list, &bedata->socket_mappings);

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_SOCKET;
	req->u.socket.id = (uपूर्णांकptr_t) map;
	req->u.socket.करोमुख्य = AF_INET;
	req->u.socket.type = SOCK_STREAM;
	req->u.socket.protocol = IPPROTO_IP;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);
	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);

	रुको_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	/* पढ़ो req_id, then the content */
	smp_rmb();
	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;

	pvcalls_निकास();
	वापस ret;
पूर्ण

अटल व्योम मुक्त_active_ring(काष्ठा sock_mapping *map)
अणु
	अगर (!map->active.ring)
		वापस;

	मुक्त_pages((अचिन्हित दीर्घ)map->active.data.in,
			map->active.ring->ring_order);
	मुक्त_page((अचिन्हित दीर्घ)map->active.ring);
पूर्ण

अटल पूर्णांक alloc_active_ring(काष्ठा sock_mapping *map)
अणु
	व्योम *bytes;

	map->active.ring = (काष्ठा pvcalls_data_पूर्णांकf *)
		get_zeroed_page(GFP_KERNEL);
	अगर (!map->active.ring)
		जाओ out;

	map->active.ring->ring_order = PVCALLS_RING_ORDER;
	bytes = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					PVCALLS_RING_ORDER);
	अगर (!bytes)
		जाओ out;

	map->active.data.in = bytes;
	map->active.data.out = bytes +
		XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);

	वापस 0;

out:
	मुक्त_active_ring(map);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक create_active(काष्ठा sock_mapping *map, evtchn_port_t *evtchn)
अणु
	व्योम *bytes;
	पूर्णांक ret, irq = -1, i;

	*evtchn = 0;
	init_रुकोqueue_head(&map->active.inflight_conn_req);

	bytes = map->active.data.in;
	क्रम (i = 0; i < (1 << PVCALLS_RING_ORDER); i++)
		map->active.ring->ref[i] = gnttab_grant_क्रमeign_access(
			pvcalls_front_dev->otherend_id,
			pfn_to_gfn(virt_to_pfn(bytes) + i), 0);

	map->active.ref = gnttab_grant_क्रमeign_access(
		pvcalls_front_dev->otherend_id,
		pfn_to_gfn(virt_to_pfn((व्योम *)map->active.ring)), 0);

	ret = xenbus_alloc_evtchn(pvcalls_front_dev, evtchn);
	अगर (ret)
		जाओ out_error;
	irq = bind_evtchn_to_irqhandler(*evtchn, pvcalls_front_conn_handler,
					0, "pvcalls-frontend", map);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out_error;
	पूर्ण

	map->active.irq = irq;
	map->active_socket = true;
	mutex_init(&map->active.in_mutex);
	mutex_init(&map->active.out_mutex);

	वापस 0;

out_error:
	अगर (*evtchn > 0)
		xenbus_मुक्त_evtchn(pvcalls_front_dev, *evtchn);
	वापस ret;
पूर्ण

पूर्णांक pvcalls_front_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
				पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map = शून्य;
	काष्ठा xen_pvcalls_request *req;
	पूर्णांक notअगरy, req_id, ret;
	evtchn_port_t evtchn;

	अगर (addr->sa_family != AF_INET || sock->type != SOCK_STREAM)
		वापस -EOPNOTSUPP;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);
	ret = alloc_active_ring(map);
	अगर (ret < 0) अणु
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		spin_unlock(&bedata->socket_lock);
		मुक्त_active_ring(map);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण
	ret = create_active(map, &evtchn);
	अगर (ret < 0) अणु
		spin_unlock(&bedata->socket_lock);
		मुक्त_active_ring(map);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_CONNECT;
	req->u.connect.id = (uपूर्णांकptr_t)map;
	req->u.connect.len = addr_len;
	req->u.connect.flags = flags;
	req->u.connect.ref = map->active.ref;
	req->u.connect.evtchn = evtchn;
	स_नकल(req->u.connect.addr, addr, माप(*addr));

	map->sock = sock;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);

	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);

	रुको_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	/* पढ़ो req_id, then the content */
	smp_rmb();
	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;
	pvcalls_निकास_sock(sock);
	वापस ret;
पूर्ण

अटल पूर्णांक __ग_लिखो_ring(काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf,
			काष्ठा pvcalls_data *data,
			काष्ठा iov_iter *msg_iter,
			पूर्णांक len)
अणु
	RING_IDX cons, prod, size, masked_prod, masked_cons;
	RING_IDX array_size = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);
	पूर्णांक32_t error;

	error = पूर्णांकf->out_error;
	अगर (error < 0)
		वापस error;
	cons = पूर्णांकf->out_cons;
	prod = पूर्णांकf->out_prod;
	/* पढ़ो indexes beक्रमe continuing */
	virt_mb();

	size = pvcalls_queued(prod, cons, array_size);
	अगर (size > array_size)
		वापस -EINVAL;
	अगर (size == array_size)
		वापस 0;
	अगर (len > array_size - size)
		len = array_size - size;

	masked_prod = pvcalls_mask(prod, array_size);
	masked_cons = pvcalls_mask(cons, array_size);

	अगर (masked_prod < masked_cons) अणु
		len = copy_from_iter(data->out + masked_prod, len, msg_iter);
	पूर्ण अन्यथा अणु
		अगर (len > array_size - masked_prod) अणु
			पूर्णांक ret = copy_from_iter(data->out + masked_prod,
				       array_size - masked_prod, msg_iter);
			अगर (ret != array_size - masked_prod) अणु
				len = ret;
				जाओ out;
			पूर्ण
			len = ret + copy_from_iter(data->out, len - ret, msg_iter);
		पूर्ण अन्यथा अणु
			len = copy_from_iter(data->out + masked_prod, len, msg_iter);
		पूर्ण
	पूर्ण
out:
	/* ग_लिखो to ring beक्रमe updating poपूर्णांकer */
	virt_wmb();
	पूर्णांकf->out_prod += len;

	वापस len;
पूर्ण

पूर्णांक pvcalls_front_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			  माप_प्रकार len)
अणु
	काष्ठा sock_mapping *map;
	पूर्णांक sent, tot_sent = 0;
	पूर्णांक count = 0, flags;

	flags = msg->msg_flags;
	अगर (flags & (MSG_CONFIRM|MSG_DONTROUTE|MSG_EOR|MSG_OOB))
		वापस -EOPNOTSUPP;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	mutex_lock(&map->active.out_mutex);
	अगर ((flags & MSG_DONTWAIT) && !pvcalls_front_ग_लिखो_toकरो(map)) अणु
		mutex_unlock(&map->active.out_mutex);
		pvcalls_निकास_sock(sock);
		वापस -EAGAIN;
	पूर्ण
	अगर (len > पूर्णांक_उच्च)
		len = पूर्णांक_उच्च;

again:
	count++;
	sent = __ग_लिखो_ring(map->active.ring,
			    &map->active.data, &msg->msg_iter,
			    len);
	अगर (sent > 0) अणु
		len -= sent;
		tot_sent += sent;
		notअगरy_remote_via_irq(map->active.irq);
	पूर्ण
	अगर (sent >= 0 && len > 0 && count < PVCALLS_FRONT_MAX_SPIN)
		जाओ again;
	अगर (sent < 0)
		tot_sent = sent;

	mutex_unlock(&map->active.out_mutex);
	pvcalls_निकास_sock(sock);
	वापस tot_sent;
पूर्ण

अटल पूर्णांक __पढ़ो_ring(काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf,
		       काष्ठा pvcalls_data *data,
		       काष्ठा iov_iter *msg_iter,
		       माप_प्रकार len, पूर्णांक flags)
अणु
	RING_IDX cons, prod, size, masked_prod, masked_cons;
	RING_IDX array_size = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);
	पूर्णांक32_t error;

	cons = पूर्णांकf->in_cons;
	prod = पूर्णांकf->in_prod;
	error = पूर्णांकf->in_error;
	/* get poपूर्णांकers beक्रमe पढ़ोing from the ring */
	virt_rmb();

	size = pvcalls_queued(prod, cons, array_size);
	masked_prod = pvcalls_mask(prod, array_size);
	masked_cons = pvcalls_mask(cons, array_size);

	अगर (size == 0)
		वापस error ?: size;

	अगर (len > size)
		len = size;

	अगर (masked_prod > masked_cons) अणु
		len = copy_to_iter(data->in + masked_cons, len, msg_iter);
	पूर्ण अन्यथा अणु
		अगर (len > (array_size - masked_cons)) अणु
			पूर्णांक ret = copy_to_iter(data->in + masked_cons,
				     array_size - masked_cons, msg_iter);
			अगर (ret != array_size - masked_cons) अणु
				len = ret;
				जाओ out;
			पूर्ण
			len = ret + copy_to_iter(data->in, len - ret, msg_iter);
		पूर्ण अन्यथा अणु
			len = copy_to_iter(data->in + masked_cons, len, msg_iter);
		पूर्ण
	पूर्ण
out:
	/* पढ़ो data from the ring beक्रमe increasing the index */
	virt_mb();
	अगर (!(flags & MSG_PEEK))
		पूर्णांकf->in_cons += len;

	वापस len;
पूर्ण

पूर्णांक pvcalls_front_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		     पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा sock_mapping *map;

	अगर (flags & (MSG_CMSG_CLOEXEC|MSG_ERRQUEUE|MSG_OOB|MSG_TRUNC))
		वापस -EOPNOTSUPP;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	mutex_lock(&map->active.in_mutex);
	अगर (len > XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER))
		len = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);

	जबतक (!(flags & MSG_DONTWAIT) && !pvcalls_front_पढ़ो_toकरो(map)) अणु
		रुको_event_पूर्णांकerruptible(map->active.inflight_conn_req,
					 pvcalls_front_पढ़ो_toकरो(map));
	पूर्ण
	ret = __पढ़ो_ring(map->active.ring, &map->active.data,
			  &msg->msg_iter, len, flags);

	अगर (ret > 0)
		notअगरy_remote_via_irq(map->active.irq);
	अगर (ret == 0)
		ret = (flags & MSG_DONTWAIT) ? -EAGAIN : 0;
	अगर (ret == -ENOTCONN)
		ret = 0;

	mutex_unlock(&map->active.in_mutex);
	pvcalls_निकास_sock(sock);
	वापस ret;
पूर्ण

पूर्णांक pvcalls_front_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map = शून्य;
	काष्ठा xen_pvcalls_request *req;
	पूर्णांक notअगरy, req_id, ret;

	अगर (addr->sa_family != AF_INET || sock->type != SOCK_STREAM)
		वापस -EOPNOTSUPP;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		spin_unlock(&bedata->socket_lock);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण
	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	map->sock = sock;
	req->cmd = PVCALLS_BIND;
	req->u.bind.id = (uपूर्णांकptr_t)map;
	स_नकल(req->u.bind.addr, addr, माप(*addr));
	req->u.bind.len = addr_len;

	init_रुकोqueue_head(&map->passive.inflight_accept_req);

	map->active_socket = false;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);
	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);

	रुको_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	/* पढ़ो req_id, then the content */
	smp_rmb();
	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;

	map->passive.status = PVCALLS_STATUS_BIND;
	pvcalls_निकास_sock(sock);
	वापस 0;
पूर्ण

पूर्णांक pvcalls_front_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map;
	काष्ठा xen_pvcalls_request *req;
	पूर्णांक notअगरy, req_id, ret;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	अगर (map->passive.status != PVCALLS_STATUS_BIND) अणु
		pvcalls_निकास_sock(sock);
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		spin_unlock(&bedata->socket_lock);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण
	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_LISTEN;
	req->u.listen.id = (uपूर्णांकptr_t) map;
	req->u.listen.backlog = backlog;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);
	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);

	रुको_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	/* पढ़ो req_id, then the content */
	smp_rmb();
	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;

	map->passive.status = PVCALLS_STATUS_LISTEN;
	pvcalls_निकास_sock(sock);
	वापस ret;
पूर्ण

पूर्णांक pvcalls_front_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map;
	काष्ठा sock_mapping *map2 = शून्य;
	काष्ठा xen_pvcalls_request *req;
	पूर्णांक notअगरy, req_id, ret, nonblock;
	evtchn_port_t evtchn;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	अगर (map->passive.status != PVCALLS_STATUS_LISTEN) अणु
		pvcalls_निकास_sock(sock);
		वापस -EINVAL;
	पूर्ण

	nonblock = flags & SOCK_NONBLOCK;
	/*
	 * Backend only supports 1 inflight accept request, will वापस
	 * errors क्रम the others
	 */
	अगर (test_and_set_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			     (व्योम *)&map->passive.flags)) अणु
		req_id = READ_ONCE(map->passive.inflight_req_id);
		अगर (req_id != PVCALLS_INVALID_ID &&
		    READ_ONCE(bedata->rsp[req_id].req_id) == req_id) अणु
			map2 = map->passive.accept_map;
			जाओ received;
		पूर्ण
		अगर (nonblock) अणु
			pvcalls_निकास_sock(sock);
			वापस -EAGAIN;
		पूर्ण
		अगर (रुको_event_पूर्णांकerruptible(map->passive.inflight_accept_req,
			!test_and_set_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
					  (व्योम *)&map->passive.flags))) अणु
			pvcalls_निकास_sock(sock);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	map2 = kzalloc(माप(*map2), GFP_KERNEL);
	अगर (map2 == शून्य) अणु
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (व्योम *)&map->passive.flags);
		pvcalls_निकास_sock(sock);
		वापस -ENOMEM;
	पूर्ण
	ret = alloc_active_ring(map2);
	अगर (ret < 0) अणु
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
				(व्योम *)&map->passive.flags);
		kमुक्त(map2);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण
	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (व्योम *)&map->passive.flags);
		spin_unlock(&bedata->socket_lock);
		मुक्त_active_ring(map2);
		kमुक्त(map2);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण

	ret = create_active(map2, &evtchn);
	अगर (ret < 0) अणु
		मुक्त_active_ring(map2);
		kमुक्त(map2);
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (व्योम *)&map->passive.flags);
		spin_unlock(&bedata->socket_lock);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण
	list_add_tail(&map2->list, &bedata->socket_mappings);

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_ACCEPT;
	req->u.accept.id = (uपूर्णांकptr_t) map;
	req->u.accept.ref = map2->active.ref;
	req->u.accept.id_new = (uपूर्णांकptr_t) map2;
	req->u.accept.evtchn = evtchn;
	map->passive.accept_map = map2;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);
	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);
	/* We could check अगर we have received a response beक्रमe वापसing. */
	अगर (nonblock) अणु
		WRITE_ONCE(map->passive.inflight_req_id, req_id);
		pvcalls_निकास_sock(sock);
		वापस -EAGAIN;
	पूर्ण

	अगर (रुको_event_पूर्णांकerruptible(bedata->inflight_req,
		READ_ONCE(bedata->rsp[req_id].req_id) == req_id)) अणु
		pvcalls_निकास_sock(sock);
		वापस -EINTR;
	पूर्ण
	/* पढ़ो req_id, then the content */
	smp_rmb();

received:
	map2->sock = newsock;
	newsock->sk = sk_alloc(sock_net(sock->sk), PF_INET, GFP_KERNEL, &pvcalls_proto, false);
	अगर (!newsock->sk) अणु
		bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;
		map->passive.inflight_req_id = PVCALLS_INVALID_ID;
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (व्योम *)&map->passive.flags);
		pvcalls_front_मुक्त_map(bedata, map2);
		pvcalls_निकास_sock(sock);
		वापस -ENOMEM;
	पूर्ण
	newsock->sk->sk_send_head = (व्योम *)map2;

	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;
	map->passive.inflight_req_id = PVCALLS_INVALID_ID;

	clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT, (व्योम *)&map->passive.flags);
	wake_up(&map->passive.inflight_accept_req);

	pvcalls_निकास_sock(sock);
	वापस ret;
पूर्ण

अटल __poll_t pvcalls_front_poll_passive(काष्ठा file *file,
					       काष्ठा pvcalls_bedata *bedata,
					       काष्ठा sock_mapping *map,
					       poll_table *रुको)
अणु
	पूर्णांक notअगरy, req_id, ret;
	काष्ठा xen_pvcalls_request *req;

	अगर (test_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
		     (व्योम *)&map->passive.flags)) अणु
		uपूर्णांक32_t req_id = READ_ONCE(map->passive.inflight_req_id);

		अगर (req_id != PVCALLS_INVALID_ID &&
		    READ_ONCE(bedata->rsp[req_id].req_id) == req_id)
			वापस EPOLLIN | EPOLLRDNORM;

		poll_रुको(file, &map->passive.inflight_accept_req, रुको);
		वापस 0;
	पूर्ण

	अगर (test_and_clear_bit(PVCALLS_FLAG_POLL_RET,
			       (व्योम *)&map->passive.flags))
		वापस EPOLLIN | EPOLLRDNORM;

	/*
	 * First check RET, then INFLIGHT. No barriers necessary to
	 * ensure execution ordering because of the conditional
	 * inकाष्ठाions creating control dependencies.
	 */

	अगर (test_and_set_bit(PVCALLS_FLAG_POLL_INFLIGHT,
			     (व्योम *)&map->passive.flags)) अणु
		poll_रुको(file, &bedata->inflight_req, रुको);
		वापस 0;
	पूर्ण

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		spin_unlock(&bedata->socket_lock);
		वापस ret;
	पूर्ण
	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_POLL;
	req->u.poll.id = (uपूर्णांकptr_t) map;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);
	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);

	poll_रुको(file, &bedata->inflight_req, रुको);
	वापस 0;
पूर्ण

अटल __poll_t pvcalls_front_poll_active(काष्ठा file *file,
					      काष्ठा pvcalls_bedata *bedata,
					      काष्ठा sock_mapping *map,
					      poll_table *रुको)
अणु
	__poll_t mask = 0;
	पूर्णांक32_t in_error, out_error;
	काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf = map->active.ring;

	out_error = पूर्णांकf->out_error;
	in_error = पूर्णांकf->in_error;

	poll_रुको(file, &map->active.inflight_conn_req, रुको);
	अगर (pvcalls_front_ग_लिखो_toकरो(map))
		mask |= EPOLLOUT | EPOLLWRNORM;
	अगर (pvcalls_front_पढ़ो_toकरो(map))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (in_error != 0 || out_error != 0)
		mask |= EPOLLERR;

	वापस mask;
पूर्ण

__poll_t pvcalls_front_poll(काष्ठा file *file, काष्ठा socket *sock,
			       poll_table *रुको)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map;
	__poll_t ret;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map))
		वापस EPOLLNVAL;
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	अगर (map->active_socket)
		ret = pvcalls_front_poll_active(file, bedata, map, रुको);
	अन्यथा
		ret = pvcalls_front_poll_passive(file, bedata, map, रुको);
	pvcalls_निकास_sock(sock);
	वापस ret;
पूर्ण

पूर्णांक pvcalls_front_release(काष्ठा socket *sock)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map;
	पूर्णांक req_id, notअगरy, ret;
	काष्ठा xen_pvcalls_request *req;

	अगर (sock->sk == शून्य)
		वापस 0;

	map = pvcalls_enter_sock(sock);
	अगर (IS_ERR(map)) अणु
		अगर (PTR_ERR(map) == -ENOTCONN)
			वापस -EIO;
		अन्यथा
			वापस 0;
	पूर्ण
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	अगर (ret < 0) अणु
		spin_unlock(&bedata->socket_lock);
		pvcalls_निकास_sock(sock);
		वापस ret;
	पूर्ण
	sock->sk->sk_send_head = शून्य;

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_RELEASE;
	req->u.release.id = (uपूर्णांकptr_t)map;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notअगरy);
	spin_unlock(&bedata->socket_lock);
	अगर (notअगरy)
		notअगरy_remote_via_irq(bedata->irq);

	रुको_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	अगर (map->active_socket) अणु
		/*
		 * Set in_error and wake up inflight_conn_req to क्रमce
		 * recvmsg रुकोers to निकास.
		 */
		map->active.ring->in_error = -EBADF;
		wake_up_पूर्णांकerruptible(&map->active.inflight_conn_req);

		/*
		 * We need to make sure that sendmsg/recvmsg on this socket have
		 * not started beक्रमe we've cleared sk_send_head here. The
		 * easiest way to guarantee this is to see that no pvcalls
		 * (other than us) is in progress on this socket.
		 */
		जबतक (atomic_पढ़ो(&map->refcount) > 1)
			cpu_relax();

		pvcalls_front_मुक्त_map(bedata, map);
	पूर्ण अन्यथा अणु
		wake_up(&bedata->inflight_req);
		wake_up(&map->passive.inflight_accept_req);

		जबतक (atomic_पढ़ो(&map->refcount) > 1)
			cpu_relax();

		spin_lock(&bedata->socket_lock);
		list_del(&map->list);
		spin_unlock(&bedata->socket_lock);
		अगर (READ_ONCE(map->passive.inflight_req_id) != PVCALLS_INVALID_ID &&
			READ_ONCE(map->passive.inflight_req_id) != 0) अणु
			pvcalls_front_मुक्त_map(bedata,
					       map->passive.accept_map);
		पूर्ण
		kमुक्त(map);
	पूर्ण
	WRITE_ONCE(bedata->rsp[req_id].req_id, PVCALLS_INVALID_ID);

	pvcalls_निकास();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id pvcalls_front_ids[] = अणु
	अणु "pvcalls" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल पूर्णांक pvcalls_front_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा pvcalls_bedata *bedata;
	काष्ठा sock_mapping *map = शून्य, *n;

	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);
	dev_set_drvdata(&dev->dev, शून्य);
	pvcalls_front_dev = शून्य;
	अगर (bedata->irq >= 0)
		unbind_from_irqhandler(bedata->irq, dev);

	list_क्रम_each_entry_safe(map, n, &bedata->socket_mappings, list) अणु
		map->sock->sk->sk_send_head = शून्य;
		अगर (map->active_socket) अणु
			map->active.ring->in_error = -EBADF;
			wake_up_पूर्णांकerruptible(&map->active.inflight_conn_req);
		पूर्ण
	पूर्ण

	smp_mb();
	जबतक (atomic_पढ़ो(&pvcalls_refcount) > 0)
		cpu_relax();
	list_क्रम_each_entry_safe(map, n, &bedata->socket_mappings, list) अणु
		अगर (map->active_socket) अणु
			/* No need to lock, refcount is 0 */
			pvcalls_front_मुक्त_map(bedata, map);
		पूर्ण अन्यथा अणु
			list_del(&map->list);
			kमुक्त(map);
		पूर्ण
	पूर्ण
	अगर (bedata->ref != -1)
		gnttab_end_क्रमeign_access(bedata->ref, 0, 0);
	kमुक्त(bedata->ring.sring);
	kमुक्त(bedata);
	xenbus_चयन_state(dev, XenbusStateClosed);
	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_front_probe(काष्ठा xenbus_device *dev,
			  स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक ret = -ENOMEM, i;
	evtchn_port_t evtchn;
	अचिन्हित पूर्णांक max_page_order, function_calls, len;
	अक्षर *versions;
	grant_ref_t gref_head = 0;
	काष्ठा xenbus_transaction xbt;
	काष्ठा pvcalls_bedata *bedata = शून्य;
	काष्ठा xen_pvcalls_sring *sring;

	अगर (pvcalls_front_dev != शून्य) अणु
		dev_err(&dev->dev, "only one PV Calls connection supported\n");
		वापस -EINVAL;
	पूर्ण

	versions = xenbus_पढ़ो(XBT_NIL, dev->otherend, "versions", &len);
	अगर (IS_ERR(versions))
		वापस PTR_ERR(versions);
	अगर (!len)
		वापस -EINVAL;
	अगर (म_भेद(versions, "1")) अणु
		kमुक्त(versions);
		वापस -EINVAL;
	पूर्ण
	kमुक्त(versions);
	max_page_order = xenbus_पढ़ो_अचिन्हित(dev->otherend,
					      "max-page-order", 0);
	अगर (max_page_order < PVCALLS_RING_ORDER)
		वापस -ENODEV;
	function_calls = xenbus_पढ़ो_अचिन्हित(dev->otherend,
					      "function-calls", 0);
	/* See XENBUS_FUNCTIONS_CALLS in pvcalls.h */
	अगर (function_calls != 1)
		वापस -ENODEV;
	pr_info("%s max-page-order is %u\n", __func__, max_page_order);

	bedata = kzalloc(माप(काष्ठा pvcalls_bedata), GFP_KERNEL);
	अगर (!bedata)
		वापस -ENOMEM;

	dev_set_drvdata(&dev->dev, bedata);
	pvcalls_front_dev = dev;
	init_रुकोqueue_head(&bedata->inflight_req);
	INIT_LIST_HEAD(&bedata->socket_mappings);
	spin_lock_init(&bedata->socket_lock);
	bedata->irq = -1;
	bedata->ref = -1;

	क्रम (i = 0; i < PVCALLS_NR_RSP_PER_RING; i++)
		bedata->rsp[i].req_id = PVCALLS_INVALID_ID;

	sring = (काष्ठा xen_pvcalls_sring *) __get_मुक्त_page(GFP_KERNEL |
							     __GFP_ZERO);
	अगर (!sring)
		जाओ error;
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&bedata->ring, sring, XEN_PAGE_SIZE);

	ret = xenbus_alloc_evtchn(dev, &evtchn);
	अगर (ret)
		जाओ error;

	bedata->irq = bind_evtchn_to_irqhandler(evtchn,
						pvcalls_front_event_handler,
						0, "pvcalls-frontend", dev);
	अगर (bedata->irq < 0) अणु
		ret = bedata->irq;
		जाओ error;
	पूर्ण

	ret = gnttab_alloc_grant_references(1, &gref_head);
	अगर (ret < 0)
		जाओ error;
	ret = gnttab_claim_grant_reference(&gref_head);
	अगर (ret < 0)
		जाओ error;
	bedata->ref = ret;
	gnttab_grant_क्रमeign_access_ref(bedata->ref, dev->otherend_id,
					virt_to_gfn((व्योम *)sring), 0);

 again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret) अणु
		xenbus_dev_fatal(dev, ret, "starting transaction");
		जाओ error;
	पूर्ण
	ret = xenbus_म_लिखो(xbt, dev->nodename, "version", "%u", 1);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "ring-ref", "%d", bedata->ref);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "port", "%u",
			    evtchn);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_transaction_end(xbt, 0);
	अगर (ret) अणु
		अगर (ret == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		जाओ error;
	पूर्ण
	xenbus_चयन_state(dev, XenbusStateInitialised);

	वापस 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
 error:
	pvcalls_front_हटाओ(dev);
	वापस ret;
पूर्ण

अटल व्योम pvcalls_front_changed(काष्ठा xenbus_device *dev,
			    क्रमागत xenbus_state backend_state)
अणु
	चयन (backend_state) अणु
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateInitWait:
		अवरोध;

	हाल XenbusStateConnected:
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		/* Missed the backend's CLOSING state */
		fallthrough;
	हाल XenbusStateClosing:
		xenbus_frontend_बंदd(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा xenbus_driver pvcalls_front_driver = अणु
	.ids = pvcalls_front_ids,
	.probe = pvcalls_front_probe,
	.हटाओ = pvcalls_front_हटाओ,
	.otherend_changed = pvcalls_front_changed,
पूर्ण;

अटल पूर्णांक __init pvcalls_frontend_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	pr_info("Initialising Xen pvcalls frontend driver\n");

	वापस xenbus_रेजिस्टर_frontend(&pvcalls_front_driver);
पूर्ण

module_init(pvcalls_frontend_init);

MODULE_DESCRIPTION("Xen PV Calls frontend driver");
MODULE_AUTHOR("Stefano Stabellini <sstabellini@kernel.org>");
MODULE_LICENSE("GPL");
