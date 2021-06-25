<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/inet.h>

#समावेश "rtrs-pri.h"
#समावेश "rtrs-log.h"

MODULE_DESCRIPTION("RDMA Transport Core");
MODULE_LICENSE("GPL");

काष्ठा rtrs_iu *rtrs_iu_alloc(u32 queue_size, माप_प्रकार size, gfp_t gfp_mask,
			      काष्ठा ib_device *dma_dev,
			      क्रमागत dma_data_direction dir,
			      व्योम (*करोne)(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc))
अणु
	काष्ठा rtrs_iu *ius, *iu;
	पूर्णांक i;

	ius = kसुस्मृति(queue_size, माप(*ius), gfp_mask);
	अगर (!ius)
		वापस शून्य;
	क्रम (i = 0; i < queue_size; i++) अणु
		iu = &ius[i];
		iu->direction = dir;
		iu->buf = kzalloc(size, gfp_mask);
		अगर (!iu->buf)
			जाओ err;

		iu->dma_addr = ib_dma_map_single(dma_dev, iu->buf, size, dir);
		अगर (ib_dma_mapping_error(dma_dev, iu->dma_addr))
			जाओ err;

		iu->cqe.करोne  = करोne;
		iu->size      = size;
	पूर्ण
	वापस ius;
err:
	rtrs_iu_मुक्त(ius, dma_dev, i);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_iu_alloc);

व्योम rtrs_iu_मुक्त(काष्ठा rtrs_iu *ius, काष्ठा ib_device *ibdev, u32 queue_size)
अणु
	काष्ठा rtrs_iu *iu;
	पूर्णांक i;

	अगर (!ius)
		वापस;

	क्रम (i = 0; i < queue_size; i++) अणु
		iu = &ius[i];
		ib_dma_unmap_single(ibdev, iu->dma_addr, iu->size, iu->direction);
		kमुक्त(iu->buf);
	पूर्ण
	kमुक्त(ius);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_iu_मुक्त);

पूर्णांक rtrs_iu_post_recv(काष्ठा rtrs_con *con, काष्ठा rtrs_iu *iu)
अणु
	काष्ठा rtrs_sess *sess = con->sess;
	काष्ठा ib_recv_wr wr;
	काष्ठा ib_sge list;

	list.addr   = iu->dma_addr;
	list.length = iu->size;
	list.lkey   = sess->dev->ib_pd->local_dma_lkey;

	अगर (list.length == 0) अणु
		rtrs_wrn(con->sess,
			  "Posting receive work request failed, sg list is empty\n");
		वापस -EINVAL;
	पूर्ण
	wr = (काष्ठा ib_recv_wr) अणु
		.wr_cqe  = &iu->cqe,
		.sg_list = &list,
		.num_sge = 1,
	पूर्ण;

	वापस ib_post_recv(con->qp, &wr, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_iu_post_recv);

पूर्णांक rtrs_post_recv_empty(काष्ठा rtrs_con *con, काष्ठा ib_cqe *cqe)
अणु
	काष्ठा ib_recv_wr wr;

	wr = (काष्ठा ib_recv_wr) अणु
		.wr_cqe  = cqe,
	पूर्ण;

	वापस ib_post_recv(con->qp, &wr, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_post_recv_empty);

अटल पूर्णांक rtrs_post_send(काष्ठा ib_qp *qp, काष्ठा ib_send_wr *head,
			     काष्ठा ib_send_wr *wr)
अणु
	अगर (head) अणु
		काष्ठा ib_send_wr *tail = head;

		जबतक (tail->next)
			tail = tail->next;
		tail->next = wr;
	पूर्ण अन्यथा अणु
		head = wr;
	पूर्ण

	वापस ib_post_send(qp, head, शून्य);
पूर्ण

पूर्णांक rtrs_iu_post_send(काष्ठा rtrs_con *con, काष्ठा rtrs_iu *iu, माप_प्रकार size,
		       काष्ठा ib_send_wr *head)
अणु
	काष्ठा rtrs_sess *sess = con->sess;
	काष्ठा ib_send_wr wr;
	काष्ठा ib_sge list;

	अगर (WARN_ON(size == 0))
		वापस -EINVAL;

	list.addr   = iu->dma_addr;
	list.length = size;
	list.lkey   = sess->dev->ib_pd->local_dma_lkey;

	wr = (काष्ठा ib_send_wr) अणु
		.wr_cqe     = &iu->cqe,
		.sg_list    = &list,
		.num_sge    = 1,
		.opcode     = IB_WR_SEND,
		.send_flags = IB_SEND_SIGNALED,
	पूर्ण;

	वापस rtrs_post_send(con->qp, head, &wr);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_iu_post_send);

पूर्णांक rtrs_iu_post_rdma_ग_लिखो_imm(काष्ठा rtrs_con *con, काष्ठा rtrs_iu *iu,
				 काष्ठा ib_sge *sge, अचिन्हित पूर्णांक num_sge,
				 u32 rkey, u64 rdma_addr, u32 imm_data,
				 क्रमागत ib_send_flags flags,
				 काष्ठा ib_send_wr *head)
अणु
	काष्ठा ib_rdma_wr wr;
	पूर्णांक i;

	wr = (काष्ठा ib_rdma_wr) अणु
		.wr.wr_cqe	  = &iu->cqe,
		.wr.sg_list	  = sge,
		.wr.num_sge	  = num_sge,
		.rkey		  = rkey,
		.remote_addr	  = rdma_addr,
		.wr.opcode	  = IB_WR_RDMA_WRITE_WITH_IMM,
		.wr.ex.imm_data = cpu_to_be32(imm_data),
		.wr.send_flags  = flags,
	पूर्ण;

	/*
	 * If one of the sges has 0 size, the operation will fail with a
	 * length error
	 */
	क्रम (i = 0; i < num_sge; i++)
		अगर (WARN_ON(sge[i].length == 0))
			वापस -EINVAL;

	वापस rtrs_post_send(con->qp, head, &wr.wr);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_iu_post_rdma_ग_लिखो_imm);

पूर्णांक rtrs_post_rdma_ग_लिखो_imm_empty(काष्ठा rtrs_con *con, काष्ठा ib_cqe *cqe,
				    u32 imm_data, क्रमागत ib_send_flags flags,
				    काष्ठा ib_send_wr *head)
अणु
	काष्ठा ib_rdma_wr wr;

	wr = (काष्ठा ib_rdma_wr) अणु
		.wr.wr_cqe	= cqe,
		.wr.send_flags	= flags,
		.wr.opcode	= IB_WR_RDMA_WRITE_WITH_IMM,
		.wr.ex.imm_data	= cpu_to_be32(imm_data),
	पूर्ण;

	वापस rtrs_post_send(con->qp, head, &wr.wr);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_post_rdma_ग_लिखो_imm_empty);

अटल व्योम qp_event_handler(काष्ठा ib_event *ev, व्योम *ctx)
अणु
	काष्ठा rtrs_con *con = ctx;

	चयन (ev->event) अणु
	हाल IB_EVENT_COMM_EST:
		rtrs_info(con->sess, "QP event %s (%d) received\n",
			   ib_event_msg(ev->event), ev->event);
		rdma_notअगरy(con->cm_id, IB_EVENT_COMM_EST);
		अवरोध;
	शेष:
		rtrs_info(con->sess, "Unhandled QP event %s (%d) received\n",
			   ib_event_msg(ev->event), ev->event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक create_cq(काष्ठा rtrs_con *con, पूर्णांक cq_vector, u16 cq_size,
		     क्रमागत ib_poll_context poll_ctx)
अणु
	काष्ठा rdma_cm_id *cm_id = con->cm_id;
	काष्ठा ib_cq *cq;

	cq = ib_cq_pool_get(cm_id->device, cq_size, cq_vector, poll_ctx);
	अगर (IS_ERR(cq)) अणु
		rtrs_err(con->sess, "Creating completion queue failed, errno: %ld\n",
			  PTR_ERR(cq));
		वापस PTR_ERR(cq);
	पूर्ण
	con->cq = cq;
	con->cq_size = cq_size;

	वापस 0;
पूर्ण

अटल पूर्णांक create_qp(काष्ठा rtrs_con *con, काष्ठा ib_pd *pd,
		     u32 max_send_wr, u32 max_recv_wr, u32 max_sge)
अणु
	काष्ठा ib_qp_init_attr init_attr = अणुशून्यपूर्ण;
	काष्ठा rdma_cm_id *cm_id = con->cm_id;
	पूर्णांक ret;

	init_attr.cap.max_send_wr = max_send_wr;
	init_attr.cap.max_recv_wr = max_recv_wr;
	init_attr.cap.max_recv_sge = 1;
	init_attr.event_handler = qp_event_handler;
	init_attr.qp_context = con;
	init_attr.cap.max_send_sge = max_sge;

	init_attr.qp_type = IB_QPT_RC;
	init_attr.send_cq = con->cq;
	init_attr.recv_cq = con->cq;
	init_attr.sq_sig_type = IB_SIGNAL_REQ_WR;

	ret = rdma_create_qp(cm_id, pd, &init_attr);
	अगर (ret) अणु
		rtrs_err(con->sess, "Creating QP failed, err: %d\n", ret);
		वापस ret;
	पूर्ण
	con->qp = cm_id->qp;

	वापस ret;
पूर्ण

पूर्णांक rtrs_cq_qp_create(काष्ठा rtrs_sess *sess, काष्ठा rtrs_con *con,
		       u32 max_send_sge, पूर्णांक cq_vector, पूर्णांक cq_size,
		       u32 max_send_wr, u32 max_recv_wr,
		       क्रमागत ib_poll_context poll_ctx)
अणु
	पूर्णांक err;

	err = create_cq(con, cq_vector, cq_size, poll_ctx);
	अगर (err)
		वापस err;

	err = create_qp(con, sess->dev->ib_pd, max_send_wr, max_recv_wr,
			max_send_sge);
	अगर (err) अणु
		ib_cq_pool_put(con->cq, con->cq_size);
		con->cq = शून्य;
		वापस err;
	पूर्ण
	con->sess = sess;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_cq_qp_create);

व्योम rtrs_cq_qp_destroy(काष्ठा rtrs_con *con)
अणु
	अगर (con->qp) अणु
		rdma_destroy_qp(con->cm_id);
		con->qp = शून्य;
	पूर्ण
	अगर (con->cq) अणु
		ib_cq_pool_put(con->cq, con->cq_size);
		con->cq = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_cq_qp_destroy);

अटल व्योम schedule_hb(काष्ठा rtrs_sess *sess)
अणु
	queue_delayed_work(sess->hb_wq, &sess->hb_dwork,
			   msecs_to_jअगरfies(sess->hb_पूर्णांकerval_ms));
पूर्ण

व्योम rtrs_send_hb_ack(काष्ठा rtrs_sess *sess)
अणु
	काष्ठा rtrs_con *usr_con = sess->con[0];
	u32 imm;
	पूर्णांक err;

	imm = rtrs_to_imm(RTRS_HB_ACK_IMM, 0);
	err = rtrs_post_rdma_ग_लिखो_imm_empty(usr_con, sess->hb_cqe, imm,
					     0, शून्य);
	अगर (err) अणु
		sess->hb_err_handler(usr_con);
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_send_hb_ack);

अटल व्योम hb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtrs_con *usr_con;
	काष्ठा rtrs_sess *sess;
	u32 imm;
	पूर्णांक err;

	sess = container_of(to_delayed_work(work), typeof(*sess), hb_dwork);
	usr_con = sess->con[0];

	अगर (sess->hb_missed_cnt > sess->hb_missed_max) अणु
		sess->hb_err_handler(usr_con);
		वापस;
	पूर्ण
	अगर (sess->hb_missed_cnt++) अणु
		/* Reschedule work without sending hb */
		schedule_hb(sess);
		वापस;
	पूर्ण

	sess->hb_last_sent = kसमय_get();

	imm = rtrs_to_imm(RTRS_HB_MSG_IMM, 0);
	err = rtrs_post_rdma_ग_लिखो_imm_empty(usr_con, sess->hb_cqe, imm,
					     0, शून्य);
	अगर (err) अणु
		sess->hb_err_handler(usr_con);
		वापस;
	पूर्ण

	schedule_hb(sess);
पूर्ण

व्योम rtrs_init_hb(काष्ठा rtrs_sess *sess, काष्ठा ib_cqe *cqe,
		  अचिन्हित पूर्णांक पूर्णांकerval_ms, अचिन्हित पूर्णांक missed_max,
		  व्योम (*err_handler)(काष्ठा rtrs_con *con),
		  काष्ठा workqueue_काष्ठा *wq)
अणु
	sess->hb_cqe = cqe;
	sess->hb_पूर्णांकerval_ms = पूर्णांकerval_ms;
	sess->hb_err_handler = err_handler;
	sess->hb_wq = wq;
	sess->hb_missed_max = missed_max;
	sess->hb_missed_cnt = 0;
	INIT_DELAYED_WORK(&sess->hb_dwork, hb_work);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_init_hb);

व्योम rtrs_start_hb(काष्ठा rtrs_sess *sess)
अणु
	schedule_hb(sess);
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_start_hb);

व्योम rtrs_stop_hb(काष्ठा rtrs_sess *sess)
अणु
	cancel_delayed_work_sync(&sess->hb_dwork);
	sess->hb_missed_cnt = 0;
	sess->hb_missed_max = 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtrs_stop_hb);

अटल पूर्णांक rtrs_str_gid_to_sockaddr(स्थिर अक्षर *addr, माप_प्रकार len,
				     लघु port, काष्ठा sockaddr_storage *dst)
अणु
	काष्ठा sockaddr_ib *dst_ib = (काष्ठा sockaddr_ib *)dst;
	पूर्णांक ret;

	/*
	 * We can use some of the IPv6 functions since GID is a valid
	 * IPv6 address क्रमmat
	 */
	ret = in6_pton(addr, len, dst_ib->sib_addr.sib_raw, '\0', शून्य);
	अगर (ret == 0)
		वापस -EINVAL;

	dst_ib->sib_family = AF_IB;
	/*
	 * Use the same TCP server port number as the IB service ID
	 * on the IB port space range
	 */
	dst_ib->sib_sid = cpu_to_be64(RDMA_IB_IP_PS_IB | port);
	dst_ib->sib_sid_mask = cpu_to_be64(0xffffffffffffffffULL);
	dst_ib->sib_pkey = cpu_to_be16(0xffff);

	वापस 0;
पूर्ण

/**
 * rtrs_str_to_sockaddr() - Convert rtrs address string to sockaddr
 * @addr:	String representation of an addr (IPv4, IPv6 or IB GID):
 *              - "ip:192.168.1.1"
 *              - "ip:fe80::200:5aee:feaa:20a2"
 *              - "gid:fe80::200:5aee:feaa:20a2"
 * @len:        String address length
 * @port:	Destination port
 * @dst:	Destination sockaddr काष्ठाure
 *
 * Returns 0 अगर conversion successful. Non-zero on error.
 */
अटल पूर्णांक rtrs_str_to_sockaddr(स्थिर अक्षर *addr, माप_प्रकार len,
				u16 port, काष्ठा sockaddr_storage *dst)
अणु
	अगर (म_भेदन(addr, "gid:", 4) == 0) अणु
		वापस rtrs_str_gid_to_sockaddr(addr + 4, len - 4, port, dst);
	पूर्ण अन्यथा अगर (म_भेदन(addr, "ip:", 3) == 0) अणु
		अक्षर port_str[8];
		अक्षर *cpy;
		पूर्णांक err;

		snम_लिखो(port_str, माप(port_str), "%u", port);
		cpy = kstrndup(addr + 3, len - 3, GFP_KERNEL);
		err = cpy ? inet_pton_with_scope(&init_net, AF_UNSPEC,
						 cpy, port_str, dst) : -ENOMEM;
		kमुक्त(cpy);

		वापस err;
	पूर्ण
	वापस -EPROTONOSUPPORT;
पूर्ण

/**
 * sockaddr_to_str() - convert sockaddr to a string.
 * @addr:	the sockadddr काष्ठाure to be converted.
 * @buf:	string containing socket addr.
 * @len:	string length.
 *
 * The वापस value is the number of अक्षरacters written पूर्णांकo buf not
 * including the trailing '\0'. If len is == 0 the function वापसs 0..
 */
पूर्णांक sockaddr_to_str(स्थिर काष्ठा sockaddr *addr, अक्षर *buf, माप_प्रकार len)
अणु

	चयन (addr->sa_family) अणु
	हाल AF_IB:
		वापस scnम_लिखो(buf, len, "gid:%pI6",
			&((काष्ठा sockaddr_ib *)addr)->sib_addr.sib_raw);
	हाल AF_INET:
		वापस scnम_लिखो(buf, len, "ip:%pI4",
			&((काष्ठा sockaddr_in *)addr)->sin_addr);
	हाल AF_INET6:
		वापस scnम_लिखो(buf, len, "ip:%pI6c",
			  &((काष्ठा sockaddr_in6 *)addr)->sin6_addr);
	पूर्ण
	वापस scnम_लिखो(buf, len, "<invalid address family>");
पूर्ण
EXPORT_SYMBOL(sockaddr_to_str);

/**
 * rtrs_addr_to_str() - convert rtrs_addr to a string "src@dst"
 * @addr:	the rtrs_addr काष्ठाure to be converted
 * @buf:	string containing source and destination addr of a path
 *		separated by '@' I.e. "ip:1.1.1.1@ip:1.1.1.2"
 *		"ip:1.1.1.1@ip:1.1.1.2".
 * @len:	string length
 *
 * The वापस value is the number of अक्षरacters written पूर्णांकo buf not
 * including the trailing '\0'.
 */
पूर्णांक rtrs_addr_to_str(स्थिर काष्ठा rtrs_addr *addr, अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक cnt;

	cnt = sockaddr_to_str((काष्ठा sockaddr *)addr->src,
			      buf, len);
	cnt += scnम_लिखो(buf + cnt, len - cnt, "@");
	sockaddr_to_str((काष्ठा sockaddr *)addr->dst,
			buf + cnt, len - cnt);
	वापस cnt;
पूर्ण
EXPORT_SYMBOL(rtrs_addr_to_str);

/**
 * rtrs_addr_to_sockaddr() - convert path string "src,dst" or "src@dst"
 * to sockaddreses
 * @str:	string containing source and destination addr of a path
 *		separated by ',' or '@' I.e. "ip:1.1.1.1,ip:1.1.1.2" or
 *		"ip:1.1.1.1@ip:1.1.1.2". If str contains only one address it's
 *		considered to be destination.
 * @len:	string length
 * @port:	Destination port number.
 * @addr:	will be set to the source/destination address or to शून्य
 *		अगर str करोesn't contain any source address.
 *
 * Returns zero अगर conversion successful. Non-zero otherwise.
 */
पूर्णांक rtrs_addr_to_sockaddr(स्थिर अक्षर *str, माप_प्रकार len, u16 port,
			  काष्ठा rtrs_addr *addr)
अणु
	स्थिर अक्षर *d;

	d = म_अक्षर(str, ',');
	अगर (!d)
		d = म_अक्षर(str, '@');
	अगर (d) अणु
		अगर (rtrs_str_to_sockaddr(str, d - str, 0, addr->src))
			वापस -EINVAL;
		d += 1;
		len -= d - str;
		str  = d;

	पूर्ण अन्यथा अणु
		addr->src = शून्य;
	पूर्ण
	वापस rtrs_str_to_sockaddr(str, len, port, addr->dst);
पूर्ण
EXPORT_SYMBOL(rtrs_addr_to_sockaddr);

व्योम rtrs_rdma_dev_pd_init(क्रमागत ib_pd_flags pd_flags,
			    काष्ठा rtrs_rdma_dev_pd *pool)
अणु
	WARN_ON(pool->ops && (!pool->ops->alloc ^ !pool->ops->मुक्त));
	INIT_LIST_HEAD(&pool->list);
	mutex_init(&pool->mutex);
	pool->pd_flags = pd_flags;
पूर्ण
EXPORT_SYMBOL(rtrs_rdma_dev_pd_init);

व्योम rtrs_rdma_dev_pd_deinit(काष्ठा rtrs_rdma_dev_pd *pool)
अणु
	mutex_destroy(&pool->mutex);
	WARN_ON(!list_empty(&pool->list));
पूर्ण
EXPORT_SYMBOL(rtrs_rdma_dev_pd_deinit);

अटल व्योम dev_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा rtrs_rdma_dev_pd *pool;
	काष्ठा rtrs_ib_dev *dev;

	dev = container_of(ref, typeof(*dev), ref);
	pool = dev->pool;

	mutex_lock(&pool->mutex);
	list_del(&dev->entry);
	mutex_unlock(&pool->mutex);

	अगर (pool->ops && pool->ops->deinit)
		pool->ops->deinit(dev);

	ib_dealloc_pd(dev->ib_pd);

	अगर (pool->ops && pool->ops->मुक्त)
		pool->ops->मुक्त(dev);
	अन्यथा
		kमुक्त(dev);
पूर्ण

पूर्णांक rtrs_ib_dev_put(काष्ठा rtrs_ib_dev *dev)
अणु
	वापस kref_put(&dev->ref, dev_मुक्त);
पूर्ण
EXPORT_SYMBOL(rtrs_ib_dev_put);

अटल पूर्णांक rtrs_ib_dev_get(काष्ठा rtrs_ib_dev *dev)
अणु
	वापस kref_get_unless_zero(&dev->ref);
पूर्ण

काष्ठा rtrs_ib_dev *
rtrs_ib_dev_find_or_add(काष्ठा ib_device *ib_dev,
			 काष्ठा rtrs_rdma_dev_pd *pool)
अणु
	काष्ठा rtrs_ib_dev *dev;

	mutex_lock(&pool->mutex);
	list_क्रम_each_entry(dev, &pool->list, entry) अणु
		अगर (dev->ib_dev->node_guid == ib_dev->node_guid &&
		    rtrs_ib_dev_get(dev))
			जाओ out_unlock;
	पूर्ण
	mutex_unlock(&pool->mutex);
	अगर (pool->ops && pool->ops->alloc)
		dev = pool->ops->alloc();
	अन्यथा
		dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (IS_ERR_OR_शून्य(dev))
		जाओ out_err;

	kref_init(&dev->ref);
	dev->pool = pool;
	dev->ib_dev = ib_dev;
	dev->ib_pd = ib_alloc_pd(ib_dev, pool->pd_flags);
	अगर (IS_ERR(dev->ib_pd))
		जाओ out_मुक्त_dev;

	अगर (pool->ops && pool->ops->init && pool->ops->init(dev))
		जाओ out_मुक्त_pd;

	mutex_lock(&pool->mutex);
	list_add(&dev->entry, &pool->list);
out_unlock:
	mutex_unlock(&pool->mutex);
	वापस dev;

out_मुक्त_pd:
	ib_dealloc_pd(dev->ib_pd);
out_मुक्त_dev:
	अगर (pool->ops && pool->ops->मुक्त)
		pool->ops->मुक्त(dev);
	अन्यथा
		kमुक्त(dev);
out_err:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(rtrs_ib_dev_find_or_add);
