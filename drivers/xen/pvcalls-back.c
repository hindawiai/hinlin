<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (c) 2017 Stefano Stabellini <stefano@aporeto.com>
 */

#समावेश <linux/inet.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/list.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/module.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/रुको.h>
#समावेश <net/sock.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/request_sock.h>

#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/पूर्णांकerface/io/pvcalls.h>

#घोषणा PVCALLS_VERSIONS "1"
#घोषणा MAX_RING_ORDER XENBUS_MAX_RING_GRANT_ORDER

अटल काष्ठा pvcalls_back_global अणु
	काष्ठा list_head frontends;
	काष्ठा semaphore frontends_lock;
पूर्ण pvcalls_back_global;

/*
 * Per-frontend data काष्ठाure. It contains poपूर्णांकers to the command
 * ring, its event channel, a list of active sockets and a tree of
 * passive sockets.
 */
काष्ठा pvcalls_fedata अणु
	काष्ठा list_head list;
	काष्ठा xenbus_device *dev;
	काष्ठा xen_pvcalls_sring *sring;
	काष्ठा xen_pvcalls_back_ring ring;
	पूर्णांक irq;
	काष्ठा list_head socket_mappings;
	काष्ठा radix_tree_root socketpass_mappings;
	काष्ठा semaphore socket_lock;
पूर्ण;

काष्ठा pvcalls_ioworker अणु
	काष्ठा work_काष्ठा रेजिस्टर_work;
	काष्ठा workqueue_काष्ठा *wq;
पूर्ण;

काष्ठा sock_mapping अणु
	काष्ठा list_head list;
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा sockpass_mapping *sockpass;
	काष्ठा socket *sock;
	uपूर्णांक64_t id;
	grant_ref_t ref;
	काष्ठा pvcalls_data_पूर्णांकf *ring;
	व्योम *bytes;
	काष्ठा pvcalls_data data;
	uपूर्णांक32_t ring_order;
	पूर्णांक irq;
	atomic_t पढ़ो;
	atomic_t ग_लिखो;
	atomic_t io;
	atomic_t release;
	atomic_t eoi;
	व्योम (*saved_data_पढ़ोy)(काष्ठा sock *sk);
	काष्ठा pvcalls_ioworker ioworker;
पूर्ण;

काष्ठा sockpass_mapping अणु
	काष्ठा list_head list;
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा socket *sock;
	uपूर्णांक64_t id;
	काष्ठा xen_pvcalls_request reqcopy;
	spinlock_t copy_lock;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा रेजिस्टर_work;
	व्योम (*saved_data_पढ़ोy)(काष्ठा sock *sk);
पूर्ण;

अटल irqवापस_t pvcalls_back_conn_event(पूर्णांक irq, व्योम *sock_map);
अटल पूर्णांक pvcalls_back_release_active(काष्ठा xenbus_device *dev,
				       काष्ठा pvcalls_fedata *fedata,
				       काष्ठा sock_mapping *map);

अटल bool pvcalls_conn_back_पढ़ो(व्योम *opaque)
अणु
	काष्ठा sock_mapping *map = (काष्ठा sock_mapping *)opaque;
	काष्ठा msghdr msg;
	काष्ठा kvec vec[2];
	RING_IDX cons, prod, size, wanted, array_size, masked_prod, masked_cons;
	पूर्णांक32_t error;
	काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf = map->ring;
	काष्ठा pvcalls_data *data = &map->data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	array_size = XEN_FLEX_RING_SIZE(map->ring_order);
	cons = पूर्णांकf->in_cons;
	prod = पूर्णांकf->in_prod;
	error = पूर्णांकf->in_error;
	/* पढ़ो the indexes first, then deal with the data */
	virt_mb();

	अगर (error)
		वापस false;

	size = pvcalls_queued(prod, cons, array_size);
	अगर (size >= array_size)
		वापस false;
	spin_lock_irqsave(&map->sock->sk->sk_receive_queue.lock, flags);
	अगर (skb_queue_empty(&map->sock->sk->sk_receive_queue)) अणु
		atomic_set(&map->पढ़ो, 0);
		spin_unlock_irqrestore(&map->sock->sk->sk_receive_queue.lock,
				flags);
		वापस true;
	पूर्ण
	spin_unlock_irqrestore(&map->sock->sk->sk_receive_queue.lock, flags);
	wanted = array_size - size;
	masked_prod = pvcalls_mask(prod, array_size);
	masked_cons = pvcalls_mask(cons, array_size);

	स_रखो(&msg, 0, माप(msg));
	अगर (masked_prod < masked_cons) अणु
		vec[0].iov_base = data->in + masked_prod;
		vec[0].iov_len = wanted;
		iov_iter_kvec(&msg.msg_iter, WRITE, vec, 1, wanted);
	पूर्ण अन्यथा अणु
		vec[0].iov_base = data->in + masked_prod;
		vec[0].iov_len = array_size - masked_prod;
		vec[1].iov_base = data->in;
		vec[1].iov_len = wanted - vec[0].iov_len;
		iov_iter_kvec(&msg.msg_iter, WRITE, vec, 2, wanted);
	पूर्ण

	atomic_set(&map->पढ़ो, 0);
	ret = inet_recvmsg(map->sock, &msg, wanted, MSG_DONTWAIT);
	WARN_ON(ret > wanted);
	अगर (ret == -EAGAIN) /* shouldn't happen */
		वापस true;
	अगर (!ret)
		ret = -ENOTCONN;
	spin_lock_irqsave(&map->sock->sk->sk_receive_queue.lock, flags);
	अगर (ret > 0 && !skb_queue_empty(&map->sock->sk->sk_receive_queue))
		atomic_inc(&map->पढ़ो);
	spin_unlock_irqrestore(&map->sock->sk->sk_receive_queue.lock, flags);

	/* ग_लिखो the data, then modअगरy the indexes */
	virt_wmb();
	अगर (ret < 0) अणु
		atomic_set(&map->पढ़ो, 0);
		पूर्णांकf->in_error = ret;
	पूर्ण अन्यथा
		पूर्णांकf->in_prod = prod + ret;
	/* update the indexes, then notअगरy the other end */
	virt_wmb();
	notअगरy_remote_via_irq(map->irq);

	वापस true;
पूर्ण

अटल bool pvcalls_conn_back_ग_लिखो(काष्ठा sock_mapping *map)
अणु
	काष्ठा pvcalls_data_पूर्णांकf *पूर्णांकf = map->ring;
	काष्ठा pvcalls_data *data = &map->data;
	काष्ठा msghdr msg;
	काष्ठा kvec vec[2];
	RING_IDX cons, prod, size, array_size;
	पूर्णांक ret;

	cons = पूर्णांकf->out_cons;
	prod = पूर्णांकf->out_prod;
	/* पढ़ो the indexes beक्रमe dealing with the data */
	virt_mb();

	array_size = XEN_FLEX_RING_SIZE(map->ring_order);
	size = pvcalls_queued(prod, cons, array_size);
	अगर (size == 0)
		वापस false;

	स_रखो(&msg, 0, माप(msg));
	msg.msg_flags |= MSG_DONTWAIT;
	अगर (pvcalls_mask(prod, array_size) > pvcalls_mask(cons, array_size)) अणु
		vec[0].iov_base = data->out + pvcalls_mask(cons, array_size);
		vec[0].iov_len = size;
		iov_iter_kvec(&msg.msg_iter, READ, vec, 1, size);
	पूर्ण अन्यथा अणु
		vec[0].iov_base = data->out + pvcalls_mask(cons, array_size);
		vec[0].iov_len = array_size - pvcalls_mask(cons, array_size);
		vec[1].iov_base = data->out;
		vec[1].iov_len = size - vec[0].iov_len;
		iov_iter_kvec(&msg.msg_iter, READ, vec, 2, size);
	पूर्ण

	atomic_set(&map->ग_लिखो, 0);
	ret = inet_sendmsg(map->sock, &msg, size);
	अगर (ret == -EAGAIN) अणु
		atomic_inc(&map->ग_लिखो);
		atomic_inc(&map->io);
		वापस true;
	पूर्ण

	/* ग_लिखो the data, then update the indexes */
	virt_wmb();
	अगर (ret < 0) अणु
		पूर्णांकf->out_error = ret;
	पूर्ण अन्यथा अणु
		पूर्णांकf->out_error = 0;
		पूर्णांकf->out_cons = cons + ret;
		prod = पूर्णांकf->out_prod;
	पूर्ण
	/* update the indexes, then notअगरy the other end */
	virt_wmb();
	अगर (prod != cons + ret) अणु
		atomic_inc(&map->ग_लिखो);
		atomic_inc(&map->io);
	पूर्ण
	notअगरy_remote_via_irq(map->irq);

	वापस true;
पूर्ण

अटल व्योम pvcalls_back_ioworker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pvcalls_ioworker *ioworker = container_of(work,
		काष्ठा pvcalls_ioworker, रेजिस्टर_work);
	काष्ठा sock_mapping *map = container_of(ioworker, काष्ठा sock_mapping,
		ioworker);
	अचिन्हित पूर्णांक eoi_flags = XEN_EOI_FLAG_SPURIOUS;

	जबतक (atomic_पढ़ो(&map->io) > 0) अणु
		अगर (atomic_पढ़ो(&map->release) > 0) अणु
			atomic_set(&map->release, 0);
			वापस;
		पूर्ण

		अगर (atomic_पढ़ो(&map->पढ़ो) > 0 &&
		    pvcalls_conn_back_पढ़ो(map))
			eoi_flags = 0;
		अगर (atomic_पढ़ो(&map->ग_लिखो) > 0 &&
		    pvcalls_conn_back_ग_लिखो(map))
			eoi_flags = 0;

		अगर (atomic_पढ़ो(&map->eoi) > 0 && !atomic_पढ़ो(&map->ग_लिखो)) अणु
			atomic_set(&map->eoi, 0);
			xen_irq_lateeoi(map->irq, eoi_flags);
			eoi_flags = XEN_EOI_FLAG_SPURIOUS;
		पूर्ण

		atomic_dec(&map->io);
	पूर्ण
पूर्ण

अटल पूर्णांक pvcalls_back_socket(काष्ठा xenbus_device *dev,
		काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	पूर्णांक ret;
	काष्ठा xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	अगर (req->u.socket.करोमुख्य != AF_INET ||
	    req->u.socket.type != SOCK_STREAM ||
	    (req->u.socket.protocol != IPPROTO_IP &&
	     req->u.socket.protocol != AF_INET))
		ret = -EAFNOSUPPORT;
	अन्यथा
		ret = 0;

	/* leave the actual socket allocation क्रम later */

	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.socket.id = req->u.socket.id;
	rsp->ret = ret;

	वापस 0;
पूर्ण

अटल व्योम pvcalls_sk_state_change(काष्ठा sock *sock)
अणु
	काष्ठा sock_mapping *map = sock->sk_user_data;

	अगर (map == शून्य)
		वापस;

	atomic_inc(&map->पढ़ो);
	notअगरy_remote_via_irq(map->irq);
पूर्ण

अटल व्योम pvcalls_sk_data_पढ़ोy(काष्ठा sock *sock)
अणु
	काष्ठा sock_mapping *map = sock->sk_user_data;
	काष्ठा pvcalls_ioworker *iow;

	अगर (map == शून्य)
		वापस;

	iow = &map->ioworker;
	atomic_inc(&map->पढ़ो);
	atomic_inc(&map->io);
	queue_work(iow->wq, &iow->रेजिस्टर_work);
पूर्ण

अटल काष्ठा sock_mapping *pvcalls_new_active_socket(
		काष्ठा pvcalls_fedata *fedata,
		uपूर्णांक64_t id,
		grant_ref_t ref,
		evtchn_port_t evtchn,
		काष्ठा socket *sock)
अणु
	पूर्णांक ret;
	काष्ठा sock_mapping *map;
	व्योम *page;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य)
		वापस शून्य;

	map->fedata = fedata;
	map->sock = sock;
	map->id = id;
	map->ref = ref;

	ret = xenbus_map_ring_valloc(fedata->dev, &ref, 1, &page);
	अगर (ret < 0)
		जाओ out;
	map->ring = page;
	map->ring_order = map->ring->ring_order;
	/* first पढ़ो the order, then map the data ring */
	virt_rmb();
	अगर (map->ring_order > MAX_RING_ORDER) अणु
		pr_warn("%s frontend requested ring_order %u, which is > MAX (%u)\n",
				__func__, map->ring_order, MAX_RING_ORDER);
		जाओ out;
	पूर्ण
	ret = xenbus_map_ring_valloc(fedata->dev, map->ring->ref,
				     (1 << map->ring_order), &page);
	अगर (ret < 0)
		जाओ out;
	map->bytes = page;

	ret = bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(
			fedata->dev, evtchn,
			pvcalls_back_conn_event, 0, "pvcalls-backend", map);
	अगर (ret < 0)
		जाओ out;
	map->irq = ret;

	map->data.in = map->bytes;
	map->data.out = map->bytes + XEN_FLEX_RING_SIZE(map->ring_order);

	map->ioworker.wq = alloc_workqueue("pvcalls_io", WQ_UNBOUND, 1);
	अगर (!map->ioworker.wq)
		जाओ out;
	atomic_set(&map->io, 1);
	INIT_WORK(&map->ioworker.रेजिस्टर_work,	pvcalls_back_ioworker);

	करोwn(&fedata->socket_lock);
	list_add_tail(&map->list, &fedata->socket_mappings);
	up(&fedata->socket_lock);

	ग_लिखो_lock_bh(&map->sock->sk->sk_callback_lock);
	map->saved_data_पढ़ोy = map->sock->sk->sk_data_पढ़ोy;
	map->sock->sk->sk_user_data = map;
	map->sock->sk->sk_data_पढ़ोy = pvcalls_sk_data_पढ़ोy;
	map->sock->sk->sk_state_change = pvcalls_sk_state_change;
	ग_लिखो_unlock_bh(&map->sock->sk->sk_callback_lock);

	वापस map;
out:
	करोwn(&fedata->socket_lock);
	list_del(&map->list);
	pvcalls_back_release_active(fedata->dev, fedata, map);
	up(&fedata->socket_lock);
	वापस शून्य;
पूर्ण

अटल पूर्णांक pvcalls_back_connect(काष्ठा xenbus_device *dev,
				काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	पूर्णांक ret = -EINVAL;
	काष्ठा socket *sock;
	काष्ठा sock_mapping *map;
	काष्ठा xen_pvcalls_response *rsp;
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)&req->u.connect.addr;

	fedata = dev_get_drvdata(&dev->dev);

	अगर (req->u.connect.len < माप(sa->sa_family) ||
	    req->u.connect.len > माप(req->u.connect.addr) ||
	    sa->sa_family != AF_INET)
		जाओ out;

	ret = sock_create(AF_INET, SOCK_STREAM, 0, &sock);
	अगर (ret < 0)
		जाओ out;
	ret = inet_stream_connect(sock, sa, req->u.connect.len, 0);
	अगर (ret < 0) अणु
		sock_release(sock);
		जाओ out;
	पूर्ण

	map = pvcalls_new_active_socket(fedata,
					req->u.connect.id,
					req->u.connect.ref,
					req->u.connect.evtchn,
					sock);
	अगर (!map) अणु
		ret = -EFAULT;
		sock_release(sock);
	पूर्ण

out:
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.connect.id = req->u.connect.id;
	rsp->ret = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_release_active(काष्ठा xenbus_device *dev,
				       काष्ठा pvcalls_fedata *fedata,
				       काष्ठा sock_mapping *map)
अणु
	disable_irq(map->irq);
	अगर (map->sock->sk != शून्य) अणु
		ग_लिखो_lock_bh(&map->sock->sk->sk_callback_lock);
		map->sock->sk->sk_user_data = शून्य;
		map->sock->sk->sk_data_पढ़ोy = map->saved_data_पढ़ोy;
		ग_लिखो_unlock_bh(&map->sock->sk->sk_callback_lock);
	पूर्ण

	atomic_set(&map->release, 1);
	flush_work(&map->ioworker.रेजिस्टर_work);

	xenbus_unmap_ring_vमुक्त(dev, map->bytes);
	xenbus_unmap_ring_vमुक्त(dev, (व्योम *)map->ring);
	unbind_from_irqhandler(map->irq, map);

	sock_release(map->sock);
	kमुक्त(map);

	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_release_passive(काष्ठा xenbus_device *dev,
					काष्ठा pvcalls_fedata *fedata,
					काष्ठा sockpass_mapping *mappass)
अणु
	अगर (mappass->sock->sk != शून्य) अणु
		ग_लिखो_lock_bh(&mappass->sock->sk->sk_callback_lock);
		mappass->sock->sk->sk_user_data = शून्य;
		mappass->sock->sk->sk_data_पढ़ोy = mappass->saved_data_पढ़ोy;
		ग_लिखो_unlock_bh(&mappass->sock->sk->sk_callback_lock);
	पूर्ण
	sock_release(mappass->sock);
	flush_workqueue(mappass->wq);
	destroy_workqueue(mappass->wq);
	kमुक्त(mappass);

	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_release(काष्ठा xenbus_device *dev,
				काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा sock_mapping *map, *n;
	काष्ठा sockpass_mapping *mappass;
	पूर्णांक ret = 0;
	काष्ठा xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	करोwn(&fedata->socket_lock);
	list_क्रम_each_entry_safe(map, n, &fedata->socket_mappings, list) अणु
		अगर (map->id == req->u.release.id) अणु
			list_del(&map->list);
			up(&fedata->socket_lock);
			ret = pvcalls_back_release_active(dev, fedata, map);
			जाओ out;
		पूर्ण
	पूर्ण
	mappass = radix_tree_lookup(&fedata->socketpass_mappings,
				    req->u.release.id);
	अगर (mappass != शून्य) अणु
		radix_tree_delete(&fedata->socketpass_mappings, mappass->id);
		up(&fedata->socket_lock);
		ret = pvcalls_back_release_passive(dev, fedata, mappass);
	पूर्ण अन्यथा
		up(&fedata->socket_lock);

out:
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->u.release.id = req->u.release.id;
	rsp->cmd = req->cmd;
	rsp->ret = ret;
	वापस 0;
पूर्ण

अटल व्योम __pvcalls_back_accept(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sockpass_mapping *mappass = container_of(
		work, काष्ठा sockpass_mapping, रेजिस्टर_work);
	काष्ठा sock_mapping *map;
	काष्ठा pvcalls_ioworker *iow;
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा socket *sock;
	काष्ठा xen_pvcalls_response *rsp;
	काष्ठा xen_pvcalls_request *req;
	पूर्णांक notअगरy;
	पूर्णांक ret = -EINVAL;
	अचिन्हित दीर्घ flags;

	fedata = mappass->fedata;
	/*
	 * __pvcalls_back_accept can race against pvcalls_back_accept.
	 * We only need to check the value of "cmd" on पढ़ो. It could be
	 * करोne atomically, but to simplअगरy the code on the ग_लिखो side, we
	 * use a spinlock.
	 */
	spin_lock_irqsave(&mappass->copy_lock, flags);
	req = &mappass->reqcopy;
	अगर (req->cmd != PVCALLS_ACCEPT) अणु
		spin_unlock_irqrestore(&mappass->copy_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&mappass->copy_lock, flags);

	sock = sock_alloc();
	अगर (sock == शून्य)
		जाओ out_error;
	sock->type = mappass->sock->type;
	sock->ops = mappass->sock->ops;

	ret = inet_accept(mappass->sock, sock, O_NONBLOCK, true);
	अगर (ret == -EAGAIN) अणु
		sock_release(sock);
		वापस;
	पूर्ण

	map = pvcalls_new_active_socket(fedata,
					req->u.accept.id_new,
					req->u.accept.ref,
					req->u.accept.evtchn,
					sock);
	अगर (!map) अणु
		ret = -EFAULT;
		sock_release(sock);
		जाओ out_error;
	पूर्ण

	map->sockpass = mappass;
	iow = &map->ioworker;
	atomic_inc(&map->पढ़ो);
	atomic_inc(&map->io);
	queue_work(iow->wq, &iow->रेजिस्टर_work);

out_error:
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.accept.id = req->u.accept.id;
	rsp->ret = ret;
	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&fedata->ring, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(fedata->irq);

	mappass->reqcopy.cmd = 0;
पूर्ण

अटल व्योम pvcalls_pass_sk_data_पढ़ोy(काष्ठा sock *sock)
अणु
	काष्ठा sockpass_mapping *mappass = sock->sk_user_data;
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा xen_pvcalls_response *rsp;
	अचिन्हित दीर्घ flags;
	पूर्णांक notअगरy;

	अगर (mappass == शून्य)
		वापस;

	fedata = mappass->fedata;
	spin_lock_irqsave(&mappass->copy_lock, flags);
	अगर (mappass->reqcopy.cmd == PVCALLS_POLL) अणु
		rsp = RING_GET_RESPONSE(&fedata->ring,
					fedata->ring.rsp_prod_pvt++);
		rsp->req_id = mappass->reqcopy.req_id;
		rsp->u.poll.id = mappass->reqcopy.u.poll.id;
		rsp->cmd = mappass->reqcopy.cmd;
		rsp->ret = 0;

		mappass->reqcopy.cmd = 0;
		spin_unlock_irqrestore(&mappass->copy_lock, flags);

		RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&fedata->ring, notअगरy);
		अगर (notअगरy)
			notअगरy_remote_via_irq(mappass->fedata->irq);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&mappass->copy_lock, flags);
		queue_work(mappass->wq, &mappass->रेजिस्टर_work);
	पूर्ण
पूर्ण

अटल पूर्णांक pvcalls_back_bind(काष्ठा xenbus_device *dev,
			     काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	पूर्णांक ret;
	काष्ठा sockpass_mapping *map;
	काष्ठा xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (map == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_WORK(&map->रेजिस्टर_work, __pvcalls_back_accept);
	spin_lock_init(&map->copy_lock);
	map->wq = alloc_workqueue("pvcalls_wq", WQ_UNBOUND, 1);
	अगर (!map->wq) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = sock_create(AF_INET, SOCK_STREAM, 0, &map->sock);
	अगर (ret < 0)
		जाओ out;

	ret = inet_bind(map->sock, (काष्ठा sockaddr *)&req->u.bind.addr,
			req->u.bind.len);
	अगर (ret < 0)
		जाओ out;

	map->fedata = fedata;
	map->id = req->u.bind.id;

	करोwn(&fedata->socket_lock);
	ret = radix_tree_insert(&fedata->socketpass_mappings, map->id,
				map);
	up(&fedata->socket_lock);
	अगर (ret)
		जाओ out;

	ग_लिखो_lock_bh(&map->sock->sk->sk_callback_lock);
	map->saved_data_पढ़ोy = map->sock->sk->sk_data_पढ़ोy;
	map->sock->sk->sk_user_data = map;
	map->sock->sk->sk_data_पढ़ोy = pvcalls_pass_sk_data_पढ़ोy;
	ग_लिखो_unlock_bh(&map->sock->sk->sk_callback_lock);

out:
	अगर (ret) अणु
		अगर (map && map->sock)
			sock_release(map->sock);
		अगर (map && map->wq)
			destroy_workqueue(map->wq);
		kमुक्त(map);
	पूर्ण
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.bind.id = req->u.bind.id;
	rsp->ret = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_listen(काष्ठा xenbus_device *dev,
			       काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	पूर्णांक ret = -EINVAL;
	काष्ठा sockpass_mapping *map;
	काष्ठा xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	करोwn(&fedata->socket_lock);
	map = radix_tree_lookup(&fedata->socketpass_mappings, req->u.listen.id);
	up(&fedata->socket_lock);
	अगर (map == शून्य)
		जाओ out;

	ret = inet_listen(map->sock, req->u.listen.backlog);

out:
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.listen.id = req->u.listen.id;
	rsp->ret = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_accept(काष्ठा xenbus_device *dev,
			       काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा sockpass_mapping *mappass;
	पूर्णांक ret = -EINVAL;
	काष्ठा xen_pvcalls_response *rsp;
	अचिन्हित दीर्घ flags;

	fedata = dev_get_drvdata(&dev->dev);

	करोwn(&fedata->socket_lock);
	mappass = radix_tree_lookup(&fedata->socketpass_mappings,
		req->u.accept.id);
	up(&fedata->socket_lock);
	अगर (mappass == शून्य)
		जाओ out_error;

	/*
	 * Limitation of the current implementation: only support one
	 * concurrent accept or poll call on one socket.
	 */
	spin_lock_irqsave(&mappass->copy_lock, flags);
	अगर (mappass->reqcopy.cmd != 0) अणु
		spin_unlock_irqrestore(&mappass->copy_lock, flags);
		ret = -EINTR;
		जाओ out_error;
	पूर्ण

	mappass->reqcopy = *req;
	spin_unlock_irqrestore(&mappass->copy_lock, flags);
	queue_work(mappass->wq, &mappass->रेजिस्टर_work);

	/* Tell the caller we करोn't need to send back a notअगरication yet */
	वापस -1;

out_error:
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.accept.id = req->u.accept.id;
	rsp->ret = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_poll(काष्ठा xenbus_device *dev,
			     काष्ठा xen_pvcalls_request *req)
अणु
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा sockpass_mapping *mappass;
	काष्ठा xen_pvcalls_response *rsp;
	काष्ठा inet_connection_sock *icsk;
	काष्ठा request_sock_queue *queue;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	bool data;

	fedata = dev_get_drvdata(&dev->dev);

	करोwn(&fedata->socket_lock);
	mappass = radix_tree_lookup(&fedata->socketpass_mappings,
				    req->u.poll.id);
	up(&fedata->socket_lock);
	अगर (mappass == शून्य)
		वापस -EINVAL;

	/*
	 * Limitation of the current implementation: only support one
	 * concurrent accept or poll call on one socket.
	 */
	spin_lock_irqsave(&mappass->copy_lock, flags);
	अगर (mappass->reqcopy.cmd != 0) अणु
		ret = -EINTR;
		जाओ out;
	पूर्ण

	mappass->reqcopy = *req;
	icsk = inet_csk(mappass->sock->sk);
	queue = &icsk->icsk_accept_queue;
	data = READ_ONCE(queue->rskq_accept_head) != शून्य;
	अगर (data) अणु
		mappass->reqcopy.cmd = 0;
		ret = 0;
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&mappass->copy_lock, flags);

	/* Tell the caller we करोn't need to send back a notअगरication yet */
	वापस -1;

out:
	spin_unlock_irqrestore(&mappass->copy_lock, flags);

	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.poll.id = req->u.poll.id;
	rsp->ret = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_handle_cmd(काष्ठा xenbus_device *dev,
				   काष्ठा xen_pvcalls_request *req)
अणु
	पूर्णांक ret = 0;

	चयन (req->cmd) अणु
	हाल PVCALLS_SOCKET:
		ret = pvcalls_back_socket(dev, req);
		अवरोध;
	हाल PVCALLS_CONNECT:
		ret = pvcalls_back_connect(dev, req);
		अवरोध;
	हाल PVCALLS_RELEASE:
		ret = pvcalls_back_release(dev, req);
		अवरोध;
	हाल PVCALLS_BIND:
		ret = pvcalls_back_bind(dev, req);
		अवरोध;
	हाल PVCALLS_LISTEN:
		ret = pvcalls_back_listen(dev, req);
		अवरोध;
	हाल PVCALLS_ACCEPT:
		ret = pvcalls_back_accept(dev, req);
		अवरोध;
	हाल PVCALLS_POLL:
		ret = pvcalls_back_poll(dev, req);
		अवरोध;
	शेष:
	अणु
		काष्ठा pvcalls_fedata *fedata;
		काष्ठा xen_pvcalls_response *rsp;

		fedata = dev_get_drvdata(&dev->dev);
		rsp = RING_GET_RESPONSE(
				&fedata->ring, fedata->ring.rsp_prod_pvt++);
		rsp->req_id = req->req_id;
		rsp->cmd = req->cmd;
		rsp->ret = -ENOTSUPP;
		अवरोध;
	पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम pvcalls_back_work(काष्ठा pvcalls_fedata *fedata)
अणु
	पूर्णांक notअगरy, notअगरy_all = 0, more = 1;
	काष्ठा xen_pvcalls_request req;
	काष्ठा xenbus_device *dev = fedata->dev;

	जबतक (more) अणु
		जबतक (RING_HAS_UNCONSUMED_REQUESTS(&fedata->ring)) अणु
			RING_COPY_REQUEST(&fedata->ring,
					  fedata->ring.req_cons++,
					  &req);

			अगर (!pvcalls_back_handle_cmd(dev, &req)) अणु
				RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(
					&fedata->ring, notअगरy);
				notअगरy_all += notअगरy;
			पूर्ण
		पूर्ण

		अगर (notअगरy_all) अणु
			notअगरy_remote_via_irq(fedata->irq);
			notअगरy_all = 0;
		पूर्ण

		RING_FINAL_CHECK_FOR_REQUESTS(&fedata->ring, more);
	पूर्ण
पूर्ण

अटल irqवापस_t pvcalls_back_event(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xenbus_device *dev = dev_id;
	काष्ठा pvcalls_fedata *fedata = शून्य;
	अचिन्हित पूर्णांक eoi_flags = XEN_EOI_FLAG_SPURIOUS;

	अगर (dev) अणु
		fedata = dev_get_drvdata(&dev->dev);
		अगर (fedata) अणु
			pvcalls_back_work(fedata);
			eoi_flags = 0;
		पूर्ण
	पूर्ण

	xen_irq_lateeoi(irq, eoi_flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pvcalls_back_conn_event(पूर्णांक irq, व्योम *sock_map)
अणु
	काष्ठा sock_mapping *map = sock_map;
	काष्ठा pvcalls_ioworker *iow;

	अगर (map == शून्य || map->sock == शून्य || map->sock->sk == शून्य ||
		map->sock->sk->sk_user_data != map) अणु
		xen_irq_lateeoi(irq, 0);
		वापस IRQ_HANDLED;
	पूर्ण

	iow = &map->ioworker;

	atomic_inc(&map->ग_लिखो);
	atomic_inc(&map->eoi);
	atomic_inc(&map->io);
	queue_work(iow->wq, &iow->रेजिस्टर_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक backend_connect(काष्ठा xenbus_device *dev)
अणु
	पूर्णांक err;
	evtchn_port_t evtchn;
	grant_ref_t ring_ref;
	काष्ठा pvcalls_fedata *fedata = शून्य;

	fedata = kzalloc(माप(काष्ठा pvcalls_fedata), GFP_KERNEL);
	अगर (!fedata)
		वापस -ENOMEM;

	fedata->irq = -1;
	err = xenbus_म_पूछो(XBT_NIL, dev->otherend, "port", "%u",
			   &evtchn);
	अगर (err != 1) अणु
		err = -EINVAL;
		xenbus_dev_fatal(dev, err, "reading %s/event-channel",
				 dev->otherend);
		जाओ error;
	पूर्ण

	err = xenbus_म_पूछो(XBT_NIL, dev->otherend, "ring-ref", "%u", &ring_ref);
	अगर (err != 1) अणु
		err = -EINVAL;
		xenbus_dev_fatal(dev, err, "reading %s/ring-ref",
				 dev->otherend);
		जाओ error;
	पूर्ण

	err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_lateeoi(dev, evtchn);
	अगर (err < 0)
		जाओ error;
	fedata->irq = err;

	err = request_thपढ़ोed_irq(fedata->irq, शून्य, pvcalls_back_event,
				   IRQF_ONESHOT, "pvcalls-back", dev);
	अगर (err < 0)
		जाओ error;

	err = xenbus_map_ring_valloc(dev, &ring_ref, 1,
				     (व्योम **)&fedata->sring);
	अगर (err < 0)
		जाओ error;

	BACK_RING_INIT(&fedata->ring, fedata->sring, XEN_PAGE_SIZE * 1);
	fedata->dev = dev;

	INIT_LIST_HEAD(&fedata->socket_mappings);
	INIT_RADIX_TREE(&fedata->socketpass_mappings, GFP_KERNEL);
	sema_init(&fedata->socket_lock, 1);
	dev_set_drvdata(&dev->dev, fedata);

	करोwn(&pvcalls_back_global.frontends_lock);
	list_add_tail(&fedata->list, &pvcalls_back_global.frontends);
	up(&pvcalls_back_global.frontends_lock);

	वापस 0;

 error:
	अगर (fedata->irq >= 0)
		unbind_from_irqhandler(fedata->irq, dev);
	अगर (fedata->sring != शून्य)
		xenbus_unmap_ring_vमुक्त(dev, fedata->sring);
	kमुक्त(fedata);
	वापस err;
पूर्ण

अटल पूर्णांक backend_disconnect(काष्ठा xenbus_device *dev)
अणु
	काष्ठा pvcalls_fedata *fedata;
	काष्ठा sock_mapping *map, *n;
	काष्ठा sockpass_mapping *mappass;
	काष्ठा radix_tree_iter iter;
	व्योम **slot;


	fedata = dev_get_drvdata(&dev->dev);

	करोwn(&fedata->socket_lock);
	list_क्रम_each_entry_safe(map, n, &fedata->socket_mappings, list) अणु
		list_del(&map->list);
		pvcalls_back_release_active(dev, fedata, map);
	पूर्ण

	radix_tree_क्रम_each_slot(slot, &fedata->socketpass_mappings, &iter, 0) अणु
		mappass = radix_tree_deref_slot(slot);
		अगर (!mappass)
			जारी;
		अगर (radix_tree_exception(mappass)) अणु
			अगर (radix_tree_deref_retry(mappass))
				slot = radix_tree_iter_retry(&iter);
		पूर्ण अन्यथा अणु
			radix_tree_delete(&fedata->socketpass_mappings,
					  mappass->id);
			pvcalls_back_release_passive(dev, fedata, mappass);
		पूर्ण
	पूर्ण
	up(&fedata->socket_lock);

	unbind_from_irqhandler(fedata->irq, dev);
	xenbus_unmap_ring_vमुक्त(dev, fedata->sring);

	list_del(&fedata->list);
	kमुक्त(fedata);
	dev_set_drvdata(&dev->dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_probe(काष्ठा xenbus_device *dev,
			      स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err, पात;
	काष्ठा xenbus_transaction xbt;

again:
	पात = 1;

	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		pr_warn("%s cannot create xenstore transaction\n", __func__);
		वापस err;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "versions", "%s",
			    PVCALLS_VERSIONS);
	अगर (err) अणु
		pr_warn("%s write out 'versions' failed\n", __func__);
		जाओ पात;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "max-page-order", "%u",
			    MAX_RING_ORDER);
	अगर (err) अणु
		pr_warn("%s write out 'max-page-order' failed\n", __func__);
		जाओ पात;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "function-calls",
			    XENBUS_FUNCTIONS_CALLS);
	अगर (err) अणु
		pr_warn("%s write out 'function-calls' failed\n", __func__);
		जाओ पात;
	पूर्ण

	पात = 0;
पात:
	err = xenbus_transaction_end(xbt, पात);
	अगर (err) अणु
		अगर (err == -EAGAIN && !पात)
			जाओ again;
		pr_warn("%s cannot complete xenstore transaction\n", __func__);
		वापस err;
	पूर्ण

	अगर (पात)
		वापस -EFAULT;

	xenbus_चयन_state(dev, XenbusStateInitWait);

	वापस 0;
पूर्ण

अटल व्योम set_backend_state(काष्ठा xenbus_device *dev,
			      क्रमागत xenbus_state state)
अणु
	जबतक (dev->state != state) अणु
		चयन (dev->state) अणु
		हाल XenbusStateClosed:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateConnected:
				xenbus_चयन_state(dev, XenbusStateInitWait);
				अवरोध;
			हाल XenbusStateClosing:
				xenbus_चयन_state(dev, XenbusStateClosing);
				अवरोध;
			शेष:
				WARN_ON(1);
			पूर्ण
			अवरोध;
		हाल XenbusStateInitWait:
		हाल XenbusStateInitialised:
			चयन (state) अणु
			हाल XenbusStateConnected:
				अगर (backend_connect(dev))
					वापस;
				xenbus_चयन_state(dev, XenbusStateConnected);
				अवरोध;
			हाल XenbusStateClosing:
			हाल XenbusStateClosed:
				xenbus_चयन_state(dev, XenbusStateClosing);
				अवरोध;
			शेष:
				WARN_ON(1);
			पूर्ण
			अवरोध;
		हाल XenbusStateConnected:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateClosing:
			हाल XenbusStateClosed:
				करोwn(&pvcalls_back_global.frontends_lock);
				backend_disconnect(dev);
				up(&pvcalls_back_global.frontends_lock);
				xenbus_चयन_state(dev, XenbusStateClosing);
				अवरोध;
			शेष:
				WARN_ON(1);
			पूर्ण
			अवरोध;
		हाल XenbusStateClosing:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateConnected:
			हाल XenbusStateClosed:
				xenbus_चयन_state(dev, XenbusStateClosed);
				अवरोध;
			शेष:
				WARN_ON(1);
			पूर्ण
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pvcalls_back_changed(काष्ठा xenbus_device *dev,
				 क्रमागत xenbus_state frontend_state)
अणु
	चयन (frontend_state) अणु
	हाल XenbusStateInitialising:
		set_backend_state(dev, XenbusStateInitWait);
		अवरोध;

	हाल XenbusStateInitialised:
	हाल XenbusStateConnected:
		set_backend_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosing:
		set_backend_state(dev, XenbusStateClosing);
		अवरोध;

	हाल XenbusStateClosed:
		set_backend_state(dev, XenbusStateClosed);
		अगर (xenbus_dev_is_online(dev))
			अवरोध;
		device_unरेजिस्टर(&dev->dev);
		अवरोध;
	हाल XenbusStateUnknown:
		set_backend_state(dev, XenbusStateClosed);
		device_unरेजिस्टर(&dev->dev);
		अवरोध;

	शेष:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 frontend_state);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pvcalls_back_हटाओ(काष्ठा xenbus_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pvcalls_back_uevent(काष्ठा xenbus_device *xdev,
			       काष्ठा kobj_uevent_env *env)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id pvcalls_back_ids[] = अणु
	अणु "pvcalls" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver pvcalls_back_driver = अणु
	.ids = pvcalls_back_ids,
	.probe = pvcalls_back_probe,
	.हटाओ = pvcalls_back_हटाओ,
	.uevent = pvcalls_back_uevent,
	.otherend_changed = pvcalls_back_changed,
पूर्ण;

अटल पूर्णांक __init pvcalls_back_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	ret = xenbus_रेजिस्टर_backend(&pvcalls_back_driver);
	अगर (ret < 0)
		वापस ret;

	sema_init(&pvcalls_back_global.frontends_lock, 1);
	INIT_LIST_HEAD(&pvcalls_back_global.frontends);
	वापस 0;
पूर्ण
module_init(pvcalls_back_init);

अटल व्योम __निकास pvcalls_back_fin(व्योम)
अणु
	काष्ठा pvcalls_fedata *fedata, *nfedata;

	करोwn(&pvcalls_back_global.frontends_lock);
	list_क्रम_each_entry_safe(fedata, nfedata,
				 &pvcalls_back_global.frontends, list) अणु
		backend_disconnect(fedata->dev);
	पूर्ण
	up(&pvcalls_back_global.frontends_lock);

	xenbus_unरेजिस्टर_driver(&pvcalls_back_driver);
पूर्ण

module_निकास(pvcalls_back_fin);

MODULE_DESCRIPTION("Xen PV Calls backend driver");
MODULE_AUTHOR("Stefano Stabellini <sstabellini@kernel.org>");
MODULE_LICENSE("GPL");
