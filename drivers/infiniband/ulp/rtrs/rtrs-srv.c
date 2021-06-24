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
#समावेश <linux/mempool.h>

#समावेश "rtrs-srv.h"
#समावेश "rtrs-log.h"
#समावेश <rdma/ib_cm.h>
#समावेश <rdma/ib_verbs.h>

MODULE_DESCRIPTION("RDMA Transport Server");
MODULE_LICENSE("GPL");

/* Must be घातer of 2, see mask from mr->page_size in ib_sg_to_pages() */
#घोषणा DEFAULT_MAX_CHUNK_SIZE (128 << 10)
#घोषणा DEFAULT_SESS_QUEUE_DEPTH 512
#घोषणा MAX_HDR_SIZE PAGE_SIZE

/* We guarantee to serve 10 paths at least */
#घोषणा CHUNK_POOL_SZ 10

अटल काष्ठा rtrs_rdma_dev_pd dev_pd;
अटल mempool_t *chunk_pool;
काष्ठा class *rtrs_dev_class;
अटल काष्ठा rtrs_srv_ib_ctx ib_ctx;

अटल पूर्णांक __पढ़ो_mostly max_chunk_size = DEFAULT_MAX_CHUNK_SIZE;
अटल पूर्णांक __पढ़ो_mostly sess_queue_depth = DEFAULT_SESS_QUEUE_DEPTH;

अटल bool always_invalidate = true;
module_param(always_invalidate, bool, 0444);
MODULE_PARM_DESC(always_invalidate,
		 "Invalidate memory registration for contiguous memory regions before accessing.");

module_param_named(max_chunk_size, max_chunk_size, पूर्णांक, 0444);
MODULE_PARM_DESC(max_chunk_size,
		 "Max size for each IO request, when change the unit is in byte (default: "
		 __stringअगरy(DEFAULT_MAX_CHUNK_SIZE) "KB)");

module_param_named(sess_queue_depth, sess_queue_depth, पूर्णांक, 0444);
MODULE_PARM_DESC(sess_queue_depth,
		 "Number of buffers for pending I/O requests to allocate per session. Maximum: "
		 __stringअगरy(MAX_SESS_QUEUE_DEPTH) " (default: "
		 __stringअगरy(DEFAULT_SESS_QUEUE_DEPTH) ")");

अटल cpumask_t cq_affinity_mask = अणु CPU_BITS_ALL पूर्ण;

अटल काष्ठा workqueue_काष्ठा *rtrs_wq;

अटल अंतरभूत काष्ठा rtrs_srv_con *to_srv_con(काष्ठा rtrs_con *c)
अणु
	वापस container_of(c, काष्ठा rtrs_srv_con, c);
पूर्ण

अटल अंतरभूत काष्ठा rtrs_srv_sess *to_srv_sess(काष्ठा rtrs_sess *s)
अणु
	वापस container_of(s, काष्ठा rtrs_srv_sess, s);
पूर्ण

अटल bool __rtrs_srv_change_state(काष्ठा rtrs_srv_sess *sess,
				     क्रमागत rtrs_srv_state new_state)
अणु
	क्रमागत rtrs_srv_state old_state;
	bool changed = false;

	lockdep_निश्चित_held(&sess->state_lock);
	old_state = sess->state;
	चयन (new_state) अणु
	हाल RTRS_SRV_CONNECTED:
		चयन (old_state) अणु
		हाल RTRS_SRV_CONNECTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_SRV_CLOSING:
		चयन (old_state) अणु
		हाल RTRS_SRV_CONNECTING:
		हाल RTRS_SRV_CONNECTED:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_SRV_CLOSED:
		चयन (old_state) अणु
		हाल RTRS_SRV_CLOSING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (changed)
		sess->state = new_state;

	वापस changed;
पूर्ण

अटल bool rtrs_srv_change_state(काष्ठा rtrs_srv_sess *sess,
				   क्रमागत rtrs_srv_state new_state)
अणु
	bool changed;

	spin_lock_irq(&sess->state_lock);
	changed = __rtrs_srv_change_state(sess, new_state);
	spin_unlock_irq(&sess->state_lock);

	वापस changed;
पूर्ण

अटल व्योम मुक्त_id(काष्ठा rtrs_srv_op *id)
अणु
	अगर (!id)
		वापस;
	kमुक्त(id);
पूर्ण

अटल व्योम rtrs_srv_मुक्त_ops_ids(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	पूर्णांक i;

	WARN_ON(atomic_पढ़ो(&sess->ids_inflight));
	अगर (sess->ops_ids) अणु
		क्रम (i = 0; i < srv->queue_depth; i++)
			मुक्त_id(sess->ops_ids[i]);
		kमुक्त(sess->ops_ids);
		sess->ops_ids = शून्य;
	पूर्ण
पूर्ण

अटल व्योम rtrs_srv_rdma_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

अटल काष्ठा ib_cqe io_comp_cqe = अणु
	.करोne = rtrs_srv_rdma_करोne
पूर्ण;

अटल पूर्णांक rtrs_srv_alloc_ops_ids(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_srv_op *id;
	पूर्णांक i;

	sess->ops_ids = kसुस्मृति(srv->queue_depth, माप(*sess->ops_ids),
				GFP_KERNEL);
	अगर (!sess->ops_ids)
		जाओ err;

	क्रम (i = 0; i < srv->queue_depth; ++i) अणु
		id = kzalloc(माप(*id), GFP_KERNEL);
		अगर (!id)
			जाओ err;

		sess->ops_ids[i] = id;
	पूर्ण
	init_रुकोqueue_head(&sess->ids_रुकोq);
	atomic_set(&sess->ids_inflight, 0);

	वापस 0;

err:
	rtrs_srv_मुक्त_ops_ids(sess);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम rtrs_srv_get_ops_ids(काष्ठा rtrs_srv_sess *sess)
अणु
	atomic_inc(&sess->ids_inflight);
पूर्ण

अटल अंतरभूत व्योम rtrs_srv_put_ops_ids(काष्ठा rtrs_srv_sess *sess)
अणु
	अगर (atomic_dec_and_test(&sess->ids_inflight))
		wake_up(&sess->ids_रुकोq);
पूर्ण

अटल व्योम rtrs_srv_रुको_ops_ids(काष्ठा rtrs_srv_sess *sess)
अणु
	रुको_event(sess->ids_रुकोq, !atomic_पढ़ो(&sess->ids_inflight));
पूर्ण


अटल व्योम rtrs_srv_reg_mr_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_srv_con *con = to_srv_con(wc->qp->qp_context);
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(s, "REG MR failed: %s\n",
			  ib_wc_status_msg(wc->status));
		बंद_sess(sess);
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा ib_cqe local_reg_cqe = अणु
	.करोne = rtrs_srv_reg_mr_करोne
पूर्ण;

अटल पूर्णांक rdma_ग_लिखो_sg(काष्ठा rtrs_srv_op *id)
अणु
	काष्ठा rtrs_sess *s = id->con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	dma_addr_t dma_addr = sess->dma_addr[id->msg_id];
	काष्ठा rtrs_srv_mr *srv_mr;
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा ib_send_wr inv_wr;
	काष्ठा ib_rdma_wr imm_wr;
	काष्ठा ib_rdma_wr *wr = शून्य;
	क्रमागत ib_send_flags flags;
	माप_प्रकार sg_cnt;
	पूर्णांक err, offset;
	bool need_inval;
	u32 rkey = 0;
	काष्ठा ib_reg_wr rwr;
	काष्ठा ib_sge *plist;
	काष्ठा ib_sge list;

	sg_cnt = le16_to_cpu(id->rd_msg->sg_cnt);
	need_inval = le16_to_cpu(id->rd_msg->flags) & RTRS_MSG_NEED_INVAL_F;
	अगर (unlikely(sg_cnt != 1))
		वापस -EINVAL;

	offset = 0;

	wr		= &id->tx_wr;
	plist		= &id->tx_sg;
	plist->addr	= dma_addr + offset;
	plist->length	= le32_to_cpu(id->rd_msg->desc[0].len);

	/* WR will fail with length error
	 * अगर this is 0
	 */
	अगर (unlikely(plist->length == 0)) अणु
		rtrs_err(s, "Invalid RDMA-Write sg list length 0\n");
		वापस -EINVAL;
	पूर्ण

	plist->lkey = sess->s.dev->ib_pd->local_dma_lkey;
	offset += plist->length;

	wr->wr.sg_list	= plist;
	wr->wr.num_sge	= 1;
	wr->remote_addr	= le64_to_cpu(id->rd_msg->desc[0].addr);
	wr->rkey	= le32_to_cpu(id->rd_msg->desc[0].key);
	अगर (rkey == 0)
		rkey = wr->rkey;
	अन्यथा
		/* Only one key is actually used */
		WARN_ON_ONCE(rkey != wr->rkey);

	wr->wr.opcode = IB_WR_RDMA_WRITE;
	wr->wr.wr_cqe   = &io_comp_cqe;
	wr->wr.ex.imm_data = 0;
	wr->wr.send_flags  = 0;

	अगर (need_inval && always_invalidate) अणु
		wr->wr.next = &rwr.wr;
		rwr.wr.next = &inv_wr;
		inv_wr.next = &imm_wr.wr;
	पूर्ण अन्यथा अगर (always_invalidate) अणु
		wr->wr.next = &rwr.wr;
		rwr.wr.next = &imm_wr.wr;
	पूर्ण अन्यथा अगर (need_inval) अणु
		wr->wr.next = &inv_wr;
		inv_wr.next = &imm_wr.wr;
	पूर्ण अन्यथा अणु
		wr->wr.next = &imm_wr.wr;
	पूर्ण
	/*
	 * From समय to समय we have to post संकेतed sends,
	 * or send queue will fill up and only QP reset can help.
	 */
	flags = (atomic_inc_वापस(&id->con->wr_cnt) % srv->queue_depth) ?
		0 : IB_SEND_SIGNALED;

	अगर (need_inval) अणु
		inv_wr.sg_list = शून्य;
		inv_wr.num_sge = 0;
		inv_wr.opcode = IB_WR_SEND_WITH_INV;
		inv_wr.wr_cqe   = &io_comp_cqe;
		inv_wr.send_flags = 0;
		inv_wr.ex.invalidate_rkey = rkey;
	पूर्ण

	imm_wr.wr.next = शून्य;
	अगर (always_invalidate) अणु
		काष्ठा rtrs_msg_rkey_rsp *msg;

		srv_mr = &sess->mrs[id->msg_id];
		rwr.wr.opcode = IB_WR_REG_MR;
		rwr.wr.wr_cqe = &local_reg_cqe;
		rwr.wr.num_sge = 0;
		rwr.mr = srv_mr->mr;
		rwr.wr.send_flags = 0;
		rwr.key = srv_mr->mr->rkey;
		rwr.access = (IB_ACCESS_LOCAL_WRITE |
			      IB_ACCESS_REMOTE_WRITE);
		msg = srv_mr->iu->buf;
		msg->buf_id = cpu_to_le16(id->msg_id);
		msg->type = cpu_to_le16(RTRS_MSG_RKEY_RSP);
		msg->rkey = cpu_to_le32(srv_mr->mr->rkey);

		list.addr   = srv_mr->iu->dma_addr;
		list.length = माप(*msg);
		list.lkey   = sess->s.dev->ib_pd->local_dma_lkey;
		imm_wr.wr.sg_list = &list;
		imm_wr.wr.num_sge = 1;
		imm_wr.wr.opcode = IB_WR_SEND_WITH_IMM;
		ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev,
					      srv_mr->iu->dma_addr,
					      srv_mr->iu->size, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		imm_wr.wr.sg_list = शून्य;
		imm_wr.wr.num_sge = 0;
		imm_wr.wr.opcode = IB_WR_RDMA_WRITE_WITH_IMM;
	पूर्ण
	imm_wr.wr.send_flags = flags;
	imm_wr.wr.ex.imm_data = cpu_to_be32(rtrs_to_io_rsp_imm(id->msg_id,
							     0, need_inval));

	imm_wr.wr.wr_cqe   = &io_comp_cqe;
	ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev, dma_addr,
				      offset, DMA_BIसूचीECTIONAL);

	err = ib_post_send(id->con->c.qp, &id->tx_wr.wr, शून्य);
	अगर (unlikely(err))
		rtrs_err(s,
			  "Posting RDMA-Write-Request to QP failed, err: %d\n",
			  err);

	वापस err;
पूर्ण

/**
 * send_io_resp_imm() - respond to client with empty IMM on failed READ/WRITE
 *                      requests or on successful WRITE request.
 * @con:	the connection to send back result
 * @id:		the id associated with the IO
 * @त्रुटि_सं:	the error number of the IO.
 *
 * Return 0 on success, त्रुटि_सं otherwise.
 */
अटल पूर्णांक send_io_resp_imm(काष्ठा rtrs_srv_con *con, काष्ठा rtrs_srv_op *id,
			    पूर्णांक त्रुटि_सं)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा ib_send_wr inv_wr, *wr = शून्य;
	काष्ठा ib_rdma_wr imm_wr;
	काष्ठा ib_reg_wr rwr;
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_srv_mr *srv_mr;
	bool need_inval = false;
	क्रमागत ib_send_flags flags;
	u32 imm;
	पूर्णांक err;

	अगर (id->dir == READ) अणु
		काष्ठा rtrs_msg_rdma_पढ़ो *rd_msg = id->rd_msg;
		माप_प्रकार sg_cnt;

		need_inval = le16_to_cpu(rd_msg->flags) &
				RTRS_MSG_NEED_INVAL_F;
		sg_cnt = le16_to_cpu(rd_msg->sg_cnt);

		अगर (need_inval) अणु
			अगर (likely(sg_cnt)) अणु
				inv_wr.wr_cqe   = &io_comp_cqe;
				inv_wr.sg_list = शून्य;
				inv_wr.num_sge = 0;
				inv_wr.opcode = IB_WR_SEND_WITH_INV;
				inv_wr.send_flags = 0;
				/* Only one key is actually used */
				inv_wr.ex.invalidate_rkey =
					le32_to_cpu(rd_msg->desc[0].key);
			पूर्ण अन्यथा अणु
				WARN_ON_ONCE(1);
				need_inval = false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (need_inval && always_invalidate) अणु
		wr = &inv_wr;
		inv_wr.next = &rwr.wr;
		rwr.wr.next = &imm_wr.wr;
	पूर्ण अन्यथा अगर (always_invalidate) अणु
		wr = &rwr.wr;
		rwr.wr.next = &imm_wr.wr;
	पूर्ण अन्यथा अगर (need_inval) अणु
		wr = &inv_wr;
		inv_wr.next = &imm_wr.wr;
	पूर्ण अन्यथा अणु
		wr = &imm_wr.wr;
	पूर्ण
	/*
	 * From समय to समय we have to post संकेतled sends,
	 * or send queue will fill up and only QP reset can help.
	 */
	flags = (atomic_inc_वापस(&con->wr_cnt) % srv->queue_depth) ?
		0 : IB_SEND_SIGNALED;
	imm = rtrs_to_io_rsp_imm(id->msg_id, त्रुटि_सं, need_inval);
	imm_wr.wr.next = शून्य;
	अगर (always_invalidate) अणु
		काष्ठा ib_sge list;
		काष्ठा rtrs_msg_rkey_rsp *msg;

		srv_mr = &sess->mrs[id->msg_id];
		rwr.wr.next = &imm_wr.wr;
		rwr.wr.opcode = IB_WR_REG_MR;
		rwr.wr.wr_cqe = &local_reg_cqe;
		rwr.wr.num_sge = 0;
		rwr.wr.send_flags = 0;
		rwr.mr = srv_mr->mr;
		rwr.key = srv_mr->mr->rkey;
		rwr.access = (IB_ACCESS_LOCAL_WRITE |
			      IB_ACCESS_REMOTE_WRITE);
		msg = srv_mr->iu->buf;
		msg->buf_id = cpu_to_le16(id->msg_id);
		msg->type = cpu_to_le16(RTRS_MSG_RKEY_RSP);
		msg->rkey = cpu_to_le32(srv_mr->mr->rkey);

		list.addr   = srv_mr->iu->dma_addr;
		list.length = माप(*msg);
		list.lkey   = sess->s.dev->ib_pd->local_dma_lkey;
		imm_wr.wr.sg_list = &list;
		imm_wr.wr.num_sge = 1;
		imm_wr.wr.opcode = IB_WR_SEND_WITH_IMM;
		ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev,
					      srv_mr->iu->dma_addr,
					      srv_mr->iu->size, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		imm_wr.wr.sg_list = शून्य;
		imm_wr.wr.num_sge = 0;
		imm_wr.wr.opcode = IB_WR_RDMA_WRITE_WITH_IMM;
	पूर्ण
	imm_wr.wr.send_flags = flags;
	imm_wr.wr.wr_cqe   = &io_comp_cqe;

	imm_wr.wr.ex.imm_data = cpu_to_be32(imm);

	err = ib_post_send(id->con->c.qp, wr, शून्य);
	अगर (unlikely(err))
		rtrs_err_rl(s, "Posting RDMA-Reply to QP failed, err: %d\n",
			     err);

	वापस err;
पूर्ण

व्योम बंद_sess(काष्ठा rtrs_srv_sess *sess)
अणु
	अगर (rtrs_srv_change_state(sess, RTRS_SRV_CLOSING))
		queue_work(rtrs_wq, &sess->बंद_work);
	WARN_ON(sess->state != RTRS_SRV_CLOSING);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *rtrs_srv_state_str(क्रमागत rtrs_srv_state state)
अणु
	चयन (state) अणु
	हाल RTRS_SRV_CONNECTING:
		वापस "RTRS_SRV_CONNECTING";
	हाल RTRS_SRV_CONNECTED:
		वापस "RTRS_SRV_CONNECTED";
	हाल RTRS_SRV_CLOSING:
		वापस "RTRS_SRV_CLOSING";
	हाल RTRS_SRV_CLOSED:
		वापस "RTRS_SRV_CLOSED";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

/**
 * rtrs_srv_resp_rdma() - Finish an RDMA request
 *
 * @id:		Internal RTRS operation identअगरier
 * @status:	Response Code sent to the other side क्रम this operation.
 *		0 = success, <=0 error
 * Context: any
 *
 * Finish a RDMA operation. A message is sent to the client and the
 * corresponding memory areas will be released.
 */
bool rtrs_srv_resp_rdma(काष्ठा rtrs_srv_op *id, पूर्णांक status)
अणु
	काष्ठा rtrs_srv_sess *sess;
	काष्ठा rtrs_srv_con *con;
	काष्ठा rtrs_sess *s;
	पूर्णांक err;

	अगर (WARN_ON(!id))
		वापस true;

	con = id->con;
	s = con->c.sess;
	sess = to_srv_sess(s);

	id->status = status;

	अगर (unlikely(sess->state != RTRS_SRV_CONNECTED)) अणु
		rtrs_err_rl(s,
			    "Sending I/O response failed,  session %s is disconnected, sess state %s\n",
			    kobject_name(&sess->kobj),
			    rtrs_srv_state_str(sess->state));
		जाओ out;
	पूर्ण
	अगर (always_invalidate) अणु
		काष्ठा rtrs_srv_mr *mr = &sess->mrs[id->msg_id];

		ib_update_fast_reg_key(mr->mr, ib_inc_rkey(mr->mr->rkey));
	पूर्ण
	अगर (unlikely(atomic_sub_वापस(1,
				       &con->sq_wr_avail) < 0)) अणु
		rtrs_err(s, "IB send queue full: sess=%s cid=%d\n",
			 kobject_name(&sess->kobj),
			 con->c.cid);
		atomic_add(1, &con->sq_wr_avail);
		spin_lock(&con->rsp_wr_रुको_lock);
		list_add_tail(&id->रुको_list, &con->rsp_wr_रुको_list);
		spin_unlock(&con->rsp_wr_रुको_lock);
		वापस false;
	पूर्ण

	अगर (status || id->dir == WRITE || !id->rd_msg->sg_cnt)
		err = send_io_resp_imm(con, id, status);
	अन्यथा
		err = rdma_ग_लिखो_sg(id);

	अगर (unlikely(err)) अणु
		rtrs_err_rl(s, "IO response failed: %d: sess=%s\n", err,
			    kobject_name(&sess->kobj));
		बंद_sess(sess);
	पूर्ण
out:
	rtrs_srv_put_ops_ids(sess);
	वापस true;
पूर्ण
EXPORT_SYMBOL(rtrs_srv_resp_rdma);

/**
 * rtrs_srv_set_sess_priv() - Set निजी poपूर्णांकer in rtrs_srv.
 * @srv:	Session poपूर्णांकer
 * @priv:	The निजी poपूर्णांकer that is associated with the session.
 */
व्योम rtrs_srv_set_sess_priv(काष्ठा rtrs_srv *srv, व्योम *priv)
अणु
	srv->priv = priv;
पूर्ण
EXPORT_SYMBOL(rtrs_srv_set_sess_priv);

अटल व्योम unmap_cont_bufs(काष्ठा rtrs_srv_sess *sess)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sess->mrs_num; i++) अणु
		काष्ठा rtrs_srv_mr *srv_mr;

		srv_mr = &sess->mrs[i];
		rtrs_iu_मुक्त(srv_mr->iu, sess->s.dev->ib_dev, 1);
		ib_dereg_mr(srv_mr->mr);
		ib_dma_unmap_sg(sess->s.dev->ib_dev, srv_mr->sgt.sgl,
				srv_mr->sgt.nents, DMA_BIसूचीECTIONAL);
		sg_मुक्त_table(&srv_mr->sgt);
	पूर्ण
	kमुक्त(sess->mrs);
पूर्ण

अटल पूर्णांक map_cont_bufs(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_sess *ss = &sess->s;
	पूर्णांक i, mri, err, mrs_num;
	अचिन्हित पूर्णांक chunk_bits;
	पूर्णांक chunks_per_mr = 1;

	/*
	 * Here we map queue_depth chunks to MR.  Firstly we have to
	 * figure out how many chunks can we map per MR.
	 */
	अगर (always_invalidate) अणु
		/*
		 * in order to करो invalidate क्रम each chunks of memory, we needs
		 * more memory regions.
		 */
		mrs_num = srv->queue_depth;
	पूर्ण अन्यथा अणु
		chunks_per_mr =
			sess->s.dev->ib_dev->attrs.max_fast_reg_page_list_len;
		mrs_num = DIV_ROUND_UP(srv->queue_depth, chunks_per_mr);
		chunks_per_mr = DIV_ROUND_UP(srv->queue_depth, mrs_num);
	पूर्ण

	sess->mrs = kसुस्मृति(mrs_num, माप(*sess->mrs), GFP_KERNEL);
	अगर (!sess->mrs)
		वापस -ENOMEM;

	sess->mrs_num = mrs_num;

	क्रम (mri = 0; mri < mrs_num; mri++) अणु
		काष्ठा rtrs_srv_mr *srv_mr = &sess->mrs[mri];
		काष्ठा sg_table *sgt = &srv_mr->sgt;
		काष्ठा scatterlist *s;
		काष्ठा ib_mr *mr;
		पूर्णांक nr, chunks;

		chunks = chunks_per_mr * mri;
		अगर (!always_invalidate)
			chunks_per_mr = min_t(पूर्णांक, chunks_per_mr,
					      srv->queue_depth - chunks);

		err = sg_alloc_table(sgt, chunks_per_mr, GFP_KERNEL);
		अगर (err)
			जाओ err;

		क्रम_each_sg(sgt->sgl, s, chunks_per_mr, i)
			sg_set_page(s, srv->chunks[chunks + i],
				    max_chunk_size, 0);

		nr = ib_dma_map_sg(sess->s.dev->ib_dev, sgt->sgl,
				   sgt->nents, DMA_BIसूचीECTIONAL);
		अगर (nr < sgt->nents) अणु
			err = nr < 0 ? nr : -EINVAL;
			जाओ मुक्त_sg;
		पूर्ण
		mr = ib_alloc_mr(sess->s.dev->ib_pd, IB_MR_TYPE_MEM_REG,
				 sgt->nents);
		अगर (IS_ERR(mr)) अणु
			err = PTR_ERR(mr);
			जाओ unmap_sg;
		पूर्ण
		nr = ib_map_mr_sg(mr, sgt->sgl, sgt->nents,
				  शून्य, max_chunk_size);
		अगर (nr < 0 || nr < sgt->nents) अणु
			err = nr < 0 ? nr : -EINVAL;
			जाओ dereg_mr;
		पूर्ण

		अगर (always_invalidate) अणु
			srv_mr->iu = rtrs_iu_alloc(1,
					माप(काष्ठा rtrs_msg_rkey_rsp),
					GFP_KERNEL, sess->s.dev->ib_dev,
					DMA_TO_DEVICE, rtrs_srv_rdma_करोne);
			अगर (!srv_mr->iu) अणु
				err = -ENOMEM;
				rtrs_err(ss, "rtrs_iu_alloc(), err: %d\n", err);
				जाओ dereg_mr;
			पूर्ण
		पूर्ण
		/* Eventually dma addr क्रम each chunk can be cached */
		क्रम_each_sg(sgt->sgl, s, sgt->orig_nents, i)
			sess->dma_addr[chunks + i] = sg_dma_address(s);

		ib_update_fast_reg_key(mr, ib_inc_rkey(mr->rkey));
		srv_mr->mr = mr;

		जारी;
err:
		जबतक (mri--) अणु
			srv_mr = &sess->mrs[mri];
			sgt = &srv_mr->sgt;
			mr = srv_mr->mr;
			rtrs_iu_मुक्त(srv_mr->iu, sess->s.dev->ib_dev, 1);
dereg_mr:
			ib_dereg_mr(mr);
unmap_sg:
			ib_dma_unmap_sg(sess->s.dev->ib_dev, sgt->sgl,
					sgt->nents, DMA_BIसूचीECTIONAL);
मुक्त_sg:
			sg_मुक्त_table(sgt);
		पूर्ण
		kमुक्त(sess->mrs);

		वापस err;
	पूर्ण

	chunk_bits = ilog2(srv->queue_depth - 1) + 1;
	sess->mem_bits = (MAX_IMM_PAYL_BITS - chunk_bits);

	वापस 0;
पूर्ण

अटल व्योम rtrs_srv_hb_err_handler(काष्ठा rtrs_con *c)
अणु
	बंद_sess(to_srv_sess(c->sess));
पूर्ण

अटल व्योम rtrs_srv_init_hb(काष्ठा rtrs_srv_sess *sess)
अणु
	rtrs_init_hb(&sess->s, &io_comp_cqe,
		      RTRS_HB_INTERVAL_MS,
		      RTRS_HB_MISSED_MAX,
		      rtrs_srv_hb_err_handler,
		      rtrs_wq);
पूर्ण

अटल व्योम rtrs_srv_start_hb(काष्ठा rtrs_srv_sess *sess)
अणु
	rtrs_start_hb(&sess->s);
पूर्ण

अटल व्योम rtrs_srv_stop_hb(काष्ठा rtrs_srv_sess *sess)
अणु
	rtrs_stop_hb(&sess->s);
पूर्ण

अटल व्योम rtrs_srv_info_rsp_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_srv_con *con = to_srv_con(wc->qp->qp_context);
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_iu *iu;

	iu = container_of(wc->wr_cqe, काष्ठा rtrs_iu, cqe);
	rtrs_iu_मुक्त(iu, sess->s.dev->ib_dev, 1);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(s, "Sess info response send failed: %s\n",
			  ib_wc_status_msg(wc->status));
		बंद_sess(sess);
		वापस;
	पूर्ण
	WARN_ON(wc->opcode != IB_WC_SEND);
पूर्ण

अटल व्योम rtrs_srv_sess_up(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_srv_ctx *ctx = srv->ctx;
	पूर्णांक up;

	mutex_lock(&srv->paths_ev_mutex);
	up = ++srv->paths_up;
	अगर (up == 1)
		ctx->ops.link_ev(srv, RTRS_SRV_LINK_EV_CONNECTED, शून्य);
	mutex_unlock(&srv->paths_ev_mutex);

	/* Mark session as established */
	sess->established = true;
पूर्ण

अटल व्योम rtrs_srv_sess_करोwn(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_srv_ctx *ctx = srv->ctx;

	अगर (!sess->established)
		वापस;

	sess->established = false;
	mutex_lock(&srv->paths_ev_mutex);
	WARN_ON(!srv->paths_up);
	अगर (--srv->paths_up == 0)
		ctx->ops.link_ev(srv, RTRS_SRV_LINK_EV_DISCONNECTED, srv->priv);
	mutex_unlock(&srv->paths_ev_mutex);
पूर्ण

अटल पूर्णांक post_recv_sess(काष्ठा rtrs_srv_sess *sess);

अटल पूर्णांक process_info_req(काष्ठा rtrs_srv_con *con,
			    काष्ठा rtrs_msg_info_req *msg)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा ib_send_wr *reg_wr = शून्य;
	काष्ठा rtrs_msg_info_rsp *rsp;
	काष्ठा rtrs_iu *tx_iu;
	काष्ठा ib_reg_wr *rwr;
	पूर्णांक mri, err;
	माप_प्रकार tx_sz;

	err = post_recv_sess(sess);
	अगर (unlikely(err)) अणु
		rtrs_err(s, "post_recv_sess(), err: %d\n", err);
		वापस err;
	पूर्ण
	rwr = kसुस्मृति(sess->mrs_num, माप(*rwr), GFP_KERNEL);
	अगर (unlikely(!rwr))
		वापस -ENOMEM;
	strlcpy(sess->s.sessname, msg->sessname, माप(sess->s.sessname));

	tx_sz  = माप(*rsp);
	tx_sz += माप(rsp->desc[0]) * sess->mrs_num;
	tx_iu = rtrs_iu_alloc(1, tx_sz, GFP_KERNEL, sess->s.dev->ib_dev,
			       DMA_TO_DEVICE, rtrs_srv_info_rsp_करोne);
	अगर (unlikely(!tx_iu)) अणु
		err = -ENOMEM;
		जाओ rwr_मुक्त;
	पूर्ण

	rsp = tx_iu->buf;
	rsp->type = cpu_to_le16(RTRS_MSG_INFO_RSP);
	rsp->sg_cnt = cpu_to_le16(sess->mrs_num);

	क्रम (mri = 0; mri < sess->mrs_num; mri++) अणु
		काष्ठा ib_mr *mr = sess->mrs[mri].mr;

		rsp->desc[mri].addr = cpu_to_le64(mr->iova);
		rsp->desc[mri].key  = cpu_to_le32(mr->rkey);
		rsp->desc[mri].len  = cpu_to_le32(mr->length);

		/*
		 * Fill in reg MR request and chain them *backwards*
		 */
		rwr[mri].wr.next = mri ? &rwr[mri - 1].wr : शून्य;
		rwr[mri].wr.opcode = IB_WR_REG_MR;
		rwr[mri].wr.wr_cqe = &local_reg_cqe;
		rwr[mri].wr.num_sge = 0;
		rwr[mri].wr.send_flags = 0;
		rwr[mri].mr = mr;
		rwr[mri].key = mr->rkey;
		rwr[mri].access = (IB_ACCESS_LOCAL_WRITE |
				   IB_ACCESS_REMOTE_WRITE);
		reg_wr = &rwr[mri].wr;
	पूर्ण

	err = rtrs_srv_create_sess_files(sess);
	अगर (unlikely(err))
		जाओ iu_मुक्त;
	kobject_get(&sess->kobj);
	get_device(&sess->srv->dev);
	rtrs_srv_change_state(sess, RTRS_SRV_CONNECTED);
	rtrs_srv_start_hb(sess);

	/*
	 * We करो not account number of established connections at the current
	 * moment, we rely on the client, which should send info request when
	 * all connections are successfully established.  Thus, simply notअगरy
	 * listener with a proper event अगर we are the first path.
	 */
	rtrs_srv_sess_up(sess);

	ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev, tx_iu->dma_addr,
				      tx_iu->size, DMA_TO_DEVICE);

	/* Send info response */
	err = rtrs_iu_post_send(&con->c, tx_iu, tx_sz, reg_wr);
	अगर (unlikely(err)) अणु
		rtrs_err(s, "rtrs_iu_post_send(), err: %d\n", err);
iu_मुक्त:
		rtrs_iu_मुक्त(tx_iu, sess->s.dev->ib_dev, 1);
	पूर्ण
rwr_मुक्त:
	kमुक्त(rwr);

	वापस err;
पूर्ण

अटल व्योम rtrs_srv_info_req_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_srv_con *con = to_srv_con(wc->qp->qp_context);
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_msg_info_req *msg;
	काष्ठा rtrs_iu *iu;
	पूर्णांक err;

	WARN_ON(con->c.cid);

	iu = container_of(wc->wr_cqe, काष्ठा rtrs_iu, cqe);
	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(s, "Sess info request receive failed: %s\n",
			  ib_wc_status_msg(wc->status));
		जाओ बंद;
	पूर्ण
	WARN_ON(wc->opcode != IB_WC_RECV);

	अगर (unlikely(wc->byte_len < माप(*msg))) अणु
		rtrs_err(s, "Sess info request is malformed: size %d\n",
			  wc->byte_len);
		जाओ बंद;
	पूर्ण
	ib_dma_sync_single_क्रम_cpu(sess->s.dev->ib_dev, iu->dma_addr,
				   iu->size, DMA_FROM_DEVICE);
	msg = iu->buf;
	अगर (unlikely(le16_to_cpu(msg->type) != RTRS_MSG_INFO_REQ)) अणु
		rtrs_err(s, "Sess info request is malformed: type %d\n",
			  le16_to_cpu(msg->type));
		जाओ बंद;
	पूर्ण
	err = process_info_req(con, msg);
	अगर (unlikely(err))
		जाओ बंद;

out:
	rtrs_iu_मुक्त(iu, sess->s.dev->ib_dev, 1);
	वापस;
बंद:
	बंद_sess(sess);
	जाओ out;
पूर्ण

अटल पूर्णांक post_recv_info_req(काष्ठा rtrs_srv_con *con)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_iu *rx_iu;
	पूर्णांक err;

	rx_iu = rtrs_iu_alloc(1, माप(काष्ठा rtrs_msg_info_req),
			       GFP_KERNEL, sess->s.dev->ib_dev,
			       DMA_FROM_DEVICE, rtrs_srv_info_req_करोne);
	अगर (unlikely(!rx_iu))
		वापस -ENOMEM;
	/* Prepare क्रम getting info response */
	err = rtrs_iu_post_recv(&con->c, rx_iu);
	अगर (unlikely(err)) अणु
		rtrs_err(s, "rtrs_iu_post_recv(), err: %d\n", err);
		rtrs_iu_मुक्त(rx_iu, sess->s.dev->ib_dev, 1);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक post_recv_io(काष्ठा rtrs_srv_con *con, माप_प्रकार q_size)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < q_size; i++) अणु
		err = rtrs_post_recv_empty(&con->c, &io_comp_cqe);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक post_recv_sess(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_sess *s = &sess->s;
	माप_प्रकार q_size;
	पूर्णांक err, cid;

	क्रम (cid = 0; cid < sess->s.con_num; cid++) अणु
		अगर (cid == 0)
			q_size = SERVICE_CON_QUEUE_DEPTH;
		अन्यथा
			q_size = srv->queue_depth;

		err = post_recv_io(to_srv_con(sess->s.con[cid]), q_size);
		अगर (unlikely(err)) अणु
			rtrs_err(s, "post_recv_io(), err: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम process_पढ़ो(काष्ठा rtrs_srv_con *con,
			 काष्ठा rtrs_msg_rdma_पढ़ो *msg,
			 u32 buf_id, u32 off)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_srv_ctx *ctx = srv->ctx;
	काष्ठा rtrs_srv_op *id;

	माप_प्रकार usr_len, data_len;
	व्योम *data;
	पूर्णांक ret;

	अगर (unlikely(sess->state != RTRS_SRV_CONNECTED)) अणु
		rtrs_err_rl(s,
			     "Processing read request failed,  session is disconnected, sess state %s\n",
			     rtrs_srv_state_str(sess->state));
		वापस;
	पूर्ण
	अगर (unlikely(msg->sg_cnt != 1 && msg->sg_cnt != 0)) अणु
		rtrs_err_rl(s,
			    "Processing read request failed, invalid message\n");
		वापस;
	पूर्ण
	rtrs_srv_get_ops_ids(sess);
	rtrs_srv_update_rdma_stats(sess->stats, off, READ);
	id = sess->ops_ids[buf_id];
	id->con		= con;
	id->dir		= READ;
	id->msg_id	= buf_id;
	id->rd_msg	= msg;
	usr_len = le16_to_cpu(msg->usr_len);
	data_len = off - usr_len;
	data = page_address(srv->chunks[buf_id]);
	ret = ctx->ops.rdma_ev(srv->priv, id, READ, data, data_len,
			   data + data_len, usr_len);

	अगर (unlikely(ret)) अणु
		rtrs_err_rl(s,
			     "Processing read request failed, user module cb reported for msg_id %d, err: %d\n",
			     buf_id, ret);
		जाओ send_err_msg;
	पूर्ण

	वापस;

send_err_msg:
	ret = send_io_resp_imm(con, id, ret);
	अगर (ret < 0) अणु
		rtrs_err_rl(s,
			     "Sending err msg for failed RDMA-Write-Req failed, msg_id %d, err: %d\n",
			     buf_id, ret);
		बंद_sess(sess);
	पूर्ण
	rtrs_srv_put_ops_ids(sess);
पूर्ण

अटल व्योम process_ग_लिखो(काष्ठा rtrs_srv_con *con,
			  काष्ठा rtrs_msg_rdma_ग_लिखो *req,
			  u32 buf_id, u32 off)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_srv_ctx *ctx = srv->ctx;
	काष्ठा rtrs_srv_op *id;

	माप_प्रकार data_len, usr_len;
	व्योम *data;
	पूर्णांक ret;

	अगर (unlikely(sess->state != RTRS_SRV_CONNECTED)) अणु
		rtrs_err_rl(s,
			     "Processing write request failed,  session is disconnected, sess state %s\n",
			     rtrs_srv_state_str(sess->state));
		वापस;
	पूर्ण
	rtrs_srv_get_ops_ids(sess);
	rtrs_srv_update_rdma_stats(sess->stats, off, WRITE);
	id = sess->ops_ids[buf_id];
	id->con    = con;
	id->dir    = WRITE;
	id->msg_id = buf_id;

	usr_len = le16_to_cpu(req->usr_len);
	data_len = off - usr_len;
	data = page_address(srv->chunks[buf_id]);
	ret = ctx->ops.rdma_ev(srv->priv, id, WRITE, data, data_len,
			   data + data_len, usr_len);
	अगर (unlikely(ret)) अणु
		rtrs_err_rl(s,
			     "Processing write request failed, user module callback reports err: %d\n",
			     ret);
		जाओ send_err_msg;
	पूर्ण

	वापस;

send_err_msg:
	ret = send_io_resp_imm(con, id, ret);
	अगर (ret < 0) अणु
		rtrs_err_rl(s,
			     "Processing write request failed, sending I/O response failed, msg_id %d, err: %d\n",
			     buf_id, ret);
		बंद_sess(sess);
	पूर्ण
	rtrs_srv_put_ops_ids(sess);
पूर्ण

अटल व्योम process_io_req(काष्ठा rtrs_srv_con *con, व्योम *msg,
			   u32 id, u32 off)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_msg_rdma_hdr *hdr;
	अचिन्हित पूर्णांक type;

	ib_dma_sync_single_क्रम_cpu(sess->s.dev->ib_dev, sess->dma_addr[id],
				   max_chunk_size, DMA_BIसूचीECTIONAL);
	hdr = msg;
	type = le16_to_cpu(hdr->type);

	चयन (type) अणु
	हाल RTRS_MSG_WRITE:
		process_ग_लिखो(con, msg, id, off);
		अवरोध;
	हाल RTRS_MSG_READ:
		process_पढ़ो(con, msg, id, off);
		अवरोध;
	शेष:
		rtrs_err(s,
			  "Processing I/O request failed, unknown message type received: 0x%02x\n",
			  type);
		जाओ err;
	पूर्ण

	वापस;

err:
	बंद_sess(sess);
पूर्ण

अटल व्योम rtrs_srv_inv_rkey_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_srv_mr *mr =
		container_of(wc->wr_cqe, typeof(*mr), inv_cqe);
	काष्ठा rtrs_srv_con *con = to_srv_con(wc->qp->qp_context);
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_srv *srv = sess->srv;
	u32 msg_id, off;
	व्योम *data;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(s, "Failed IB_WR_LOCAL_INV: %s\n",
			  ib_wc_status_msg(wc->status));
		बंद_sess(sess);
	पूर्ण
	msg_id = mr->msg_id;
	off = mr->msg_off;
	data = page_address(srv->chunks[msg_id]) + off;
	process_io_req(con, data, msg_id, off);
पूर्ण

अटल पूर्णांक rtrs_srv_inv_rkey(काष्ठा rtrs_srv_con *con,
			      काष्ठा rtrs_srv_mr *mr)
अणु
	काष्ठा ib_send_wr wr = अणु
		.opcode		    = IB_WR_LOCAL_INV,
		.wr_cqe		    = &mr->inv_cqe,
		.send_flags	    = IB_SEND_SIGNALED,
		.ex.invalidate_rkey = mr->mr->rkey,
	पूर्ण;
	mr->inv_cqe.करोne = rtrs_srv_inv_rkey_करोne;

	वापस ib_post_send(con->c.qp, &wr, शून्य);
पूर्ण

अटल व्योम rtrs_rdma_process_wr_रुको_list(काष्ठा rtrs_srv_con *con)
अणु
	spin_lock(&con->rsp_wr_रुको_lock);
	जबतक (!list_empty(&con->rsp_wr_रुको_list)) अणु
		काष्ठा rtrs_srv_op *id;
		पूर्णांक ret;

		id = list_entry(con->rsp_wr_रुको_list.next,
				काष्ठा rtrs_srv_op, रुको_list);
		list_del(&id->रुको_list);

		spin_unlock(&con->rsp_wr_रुको_lock);
		ret = rtrs_srv_resp_rdma(id, id->status);
		spin_lock(&con->rsp_wr_रुको_lock);

		अगर (!ret) अणु
			list_add(&id->रुको_list, &con->rsp_wr_रुको_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&con->rsp_wr_रुको_lock);
पूर्ण

अटल व्योम rtrs_srv_rdma_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_srv_con *con = to_srv_con(wc->qp->qp_context);
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_srv_sess *sess = to_srv_sess(s);
	काष्ठा rtrs_srv *srv = sess->srv;
	u32 imm_type, imm_payload;
	पूर्णांक err;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		अगर (wc->status != IB_WC_WR_FLUSH_ERR) अणु
			rtrs_err(s,
				  "%s (wr_cqe: %p, type: %d, vendor_err: 0x%x, len: %u)\n",
				  ib_wc_status_msg(wc->status), wc->wr_cqe,
				  wc->opcode, wc->venकरोr_err, wc->byte_len);
			बंद_sess(sess);
		पूर्ण
		वापस;
	पूर्ण

	चयन (wc->opcode) अणु
	हाल IB_WC_RECV_RDMA_WITH_IMM:
		/*
		 * post_recv() RDMA ग_लिखो completions of IO reqs (पढ़ो/ग_लिखो)
		 * and hb
		 */
		अगर (WARN_ON(wc->wr_cqe != &io_comp_cqe))
			वापस;
		err = rtrs_post_recv_empty(&con->c, &io_comp_cqe);
		अगर (unlikely(err)) अणु
			rtrs_err(s, "rtrs_post_recv(), err: %d\n", err);
			बंद_sess(sess);
			अवरोध;
		पूर्ण
		rtrs_from_imm(be32_to_cpu(wc->ex.imm_data),
			       &imm_type, &imm_payload);
		अगर (likely(imm_type == RTRS_IO_REQ_IMM)) अणु
			u32 msg_id, off;
			व्योम *data;

			msg_id = imm_payload >> sess->mem_bits;
			off = imm_payload & ((1 << sess->mem_bits) - 1);
			अगर (unlikely(msg_id >= srv->queue_depth ||
				     off >= max_chunk_size)) अणु
				rtrs_err(s, "Wrong msg_id %u, off %u\n",
					  msg_id, off);
				बंद_sess(sess);
				वापस;
			पूर्ण
			अगर (always_invalidate) अणु
				काष्ठा rtrs_srv_mr *mr = &sess->mrs[msg_id];

				mr->msg_off = off;
				mr->msg_id = msg_id;
				err = rtrs_srv_inv_rkey(con, mr);
				अगर (unlikely(err)) अणु
					rtrs_err(s, "rtrs_post_recv(), err: %d\n",
						  err);
					बंद_sess(sess);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				data = page_address(srv->chunks[msg_id]) + off;
				process_io_req(con, data, msg_id, off);
			पूर्ण
		पूर्ण अन्यथा अगर (imm_type == RTRS_HB_MSG_IMM) अणु
			WARN_ON(con->c.cid);
			rtrs_send_hb_ack(&sess->s);
		पूर्ण अन्यथा अगर (imm_type == RTRS_HB_ACK_IMM) अणु
			WARN_ON(con->c.cid);
			sess->s.hb_missed_cnt = 0;
		पूर्ण अन्यथा अणु
			rtrs_wrn(s, "Unknown IMM type %u\n", imm_type);
		पूर्ण
		अवरोध;
	हाल IB_WC_RDMA_WRITE:
	हाल IB_WC_SEND:
		/*
		 * post_send() RDMA ग_लिखो completions of IO reqs (पढ़ो/ग_लिखो)
		 */
		atomic_add(srv->queue_depth, &con->sq_wr_avail);

		अगर (unlikely(!list_empty_careful(&con->rsp_wr_रुको_list)))
			rtrs_rdma_process_wr_रुको_list(con);

		अवरोध;
	शेष:
		rtrs_wrn(s, "Unexpected WC type: %d\n", wc->opcode);
		वापस;
	पूर्ण
पूर्ण

/**
 * rtrs_srv_get_sess_name() - Get rtrs_srv peer hostname.
 * @srv:	Session
 * @sessname:	Sessname buffer
 * @len:	Length of sessname buffer
 */
पूर्णांक rtrs_srv_get_sess_name(काष्ठा rtrs_srv *srv, अक्षर *sessname, माप_प्रकार len)
अणु
	काष्ठा rtrs_srv_sess *sess;
	पूर्णांक err = -ENOTCONN;

	mutex_lock(&srv->paths_mutex);
	list_क्रम_each_entry(sess, &srv->paths_list, s.entry) अणु
		अगर (sess->state != RTRS_SRV_CONNECTED)
			जारी;
		strlcpy(sessname, sess->s.sessname,
		       min_t(माप_प्रकार, माप(sess->s.sessname), len));
		err = 0;
		अवरोध;
	पूर्ण
	mutex_unlock(&srv->paths_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(rtrs_srv_get_sess_name);

/**
 * rtrs_srv_get_sess_qdepth() - Get rtrs_srv qdepth.
 * @srv:	Session
 */
पूर्णांक rtrs_srv_get_queue_depth(काष्ठा rtrs_srv *srv)
अणु
	वापस srv->queue_depth;
पूर्ण
EXPORT_SYMBOL(rtrs_srv_get_queue_depth);

अटल पूर्णांक find_next_bit_ring(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा ib_device *ib_dev = sess->s.dev->ib_dev;
	पूर्णांक v;

	v = cpumask_next(sess->cur_cq_vector, &cq_affinity_mask);
	अगर (v >= nr_cpu_ids || v >= ib_dev->num_comp_vectors)
		v = cpumask_first(&cq_affinity_mask);
	वापस v;
पूर्ण

अटल पूर्णांक rtrs_srv_get_next_cq_vector(काष्ठा rtrs_srv_sess *sess)
अणु
	sess->cur_cq_vector = find_next_bit_ring(sess);

	वापस sess->cur_cq_vector;
पूर्ण

अटल व्योम rtrs_srv_dev_release(काष्ठा device *dev)
अणु
	काष्ठा rtrs_srv *srv = container_of(dev, काष्ठा rtrs_srv, dev);

	kमुक्त(srv);
पूर्ण

अटल व्योम मुक्त_srv(काष्ठा rtrs_srv *srv)
अणु
	पूर्णांक i;

	WARN_ON(refcount_पढ़ो(&srv->refcount));
	क्रम (i = 0; i < srv->queue_depth; i++)
		mempool_मुक्त(srv->chunks[i], chunk_pool);
	kमुक्त(srv->chunks);
	mutex_destroy(&srv->paths_mutex);
	mutex_destroy(&srv->paths_ev_mutex);
	/* last put to release the srv काष्ठाure */
	put_device(&srv->dev);
पूर्ण

अटल काष्ठा rtrs_srv *get_or_create_srv(काष्ठा rtrs_srv_ctx *ctx,
					  स्थिर uuid_t *paths_uuid,
					  bool first_conn)
अणु
	काष्ठा rtrs_srv *srv;
	पूर्णांक i;

	mutex_lock(&ctx->srv_mutex);
	list_क्रम_each_entry(srv, &ctx->srv_list, ctx_list) अणु
		अगर (uuid_equal(&srv->paths_uuid, paths_uuid) &&
		    refcount_inc_not_zero(&srv->refcount)) अणु
			mutex_unlock(&ctx->srv_mutex);
			वापस srv;
		पूर्ण
	पूर्ण
	mutex_unlock(&ctx->srv_mutex);
	/*
	 * If this request is not the first connection request from the
	 * client क्रम this session then fail and वापस error.
	 */
	अगर (!first_conn)
		वापस ERR_PTR(-ENXIO);

	/* need to allocate a new srv */
	srv = kzalloc(माप(*srv), GFP_KERNEL);
	अगर  (!srv)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&srv->paths_list);
	mutex_init(&srv->paths_mutex);
	mutex_init(&srv->paths_ev_mutex);
	uuid_copy(&srv->paths_uuid, paths_uuid);
	srv->queue_depth = sess_queue_depth;
	srv->ctx = ctx;
	device_initialize(&srv->dev);
	srv->dev.release = rtrs_srv_dev_release;

	srv->chunks = kसुस्मृति(srv->queue_depth, माप(*srv->chunks),
			      GFP_KERNEL);
	अगर (!srv->chunks)
		जाओ err_मुक्त_srv;

	क्रम (i = 0; i < srv->queue_depth; i++) अणु
		srv->chunks[i] = mempool_alloc(chunk_pool, GFP_KERNEL);
		अगर (!srv->chunks[i])
			जाओ err_मुक्त_chunks;
	पूर्ण
	refcount_set(&srv->refcount, 1);
	mutex_lock(&ctx->srv_mutex);
	list_add(&srv->ctx_list, &ctx->srv_list);
	mutex_unlock(&ctx->srv_mutex);

	वापस srv;

err_मुक्त_chunks:
	जबतक (i--)
		mempool_मुक्त(srv->chunks[i], chunk_pool);
	kमुक्त(srv->chunks);

err_मुक्त_srv:
	kमुक्त(srv);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम put_srv(काष्ठा rtrs_srv *srv)
अणु
	अगर (refcount_dec_and_test(&srv->refcount)) अणु
		काष्ठा rtrs_srv_ctx *ctx = srv->ctx;

		WARN_ON(srv->dev.kobj.state_in_sysfs);

		mutex_lock(&ctx->srv_mutex);
		list_del(&srv->ctx_list);
		mutex_unlock(&ctx->srv_mutex);
		मुक्त_srv(srv);
	पूर्ण
पूर्ण

अटल व्योम __add_path_to_srv(काष्ठा rtrs_srv *srv,
			      काष्ठा rtrs_srv_sess *sess)
अणु
	list_add_tail(&sess->s.entry, &srv->paths_list);
	srv->paths_num++;
	WARN_ON(srv->paths_num >= MAX_PATHS_NUM);
पूर्ण

अटल व्योम del_path_from_srv(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;

	अगर (WARN_ON(!srv))
		वापस;

	mutex_lock(&srv->paths_mutex);
	list_del(&sess->s.entry);
	WARN_ON(!srv->paths_num);
	srv->paths_num--;
	mutex_unlock(&srv->paths_mutex);
पूर्ण

/* वापस true अगर addresses are the same, error other wise */
अटल पूर्णांक sockaddr_cmp(स्थिर काष्ठा sockaddr *a, स्थिर काष्ठा sockaddr *b)
अणु
	चयन (a->sa_family) अणु
	हाल AF_IB:
		वापस स_भेद(&((काष्ठा sockaddr_ib *)a)->sib_addr,
			      &((काष्ठा sockaddr_ib *)b)->sib_addr,
			      माप(काष्ठा ib_addr)) &&
			(b->sa_family == AF_IB);
	हाल AF_INET:
		वापस स_भेद(&((काष्ठा sockaddr_in *)a)->sin_addr,
			      &((काष्ठा sockaddr_in *)b)->sin_addr,
			      माप(काष्ठा in_addr)) &&
			(b->sa_family == AF_INET);
	हाल AF_INET6:
		वापस स_भेद(&((काष्ठा sockaddr_in6 *)a)->sin6_addr,
			      &((काष्ठा sockaddr_in6 *)b)->sin6_addr,
			      माप(काष्ठा in6_addr)) &&
			(b->sa_family == AF_INET6);
	शेष:
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल bool __is_path_w_addr_exists(काष्ठा rtrs_srv *srv,
				    काष्ठा rdma_addr *addr)
अणु
	काष्ठा rtrs_srv_sess *sess;

	list_क्रम_each_entry(sess, &srv->paths_list, s.entry)
		अगर (!sockaddr_cmp((काष्ठा sockaddr *)&sess->s.dst_addr,
				  (काष्ठा sockaddr *)&addr->dst_addr) &&
		    !sockaddr_cmp((काष्ठा sockaddr *)&sess->s.src_addr,
				  (काष्ठा sockaddr *)&addr->src_addr))
			वापस true;

	वापस false;
पूर्ण

अटल व्योम मुक्त_sess(काष्ठा rtrs_srv_sess *sess)
अणु
	अगर (sess->kobj.state_in_sysfs) अणु
		kobject_del(&sess->kobj);
		kobject_put(&sess->kobj);
	पूर्ण अन्यथा अणु
		kमुक्त(sess);
	पूर्ण
पूर्ण

अटल व्योम rtrs_srv_बंद_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtrs_srv_sess *sess;
	काष्ठा rtrs_srv_con *con;
	पूर्णांक i;

	sess = container_of(work, typeof(*sess), बंद_work);

	rtrs_srv_destroy_sess_files(sess);
	rtrs_srv_stop_hb(sess);

	क्रम (i = 0; i < sess->s.con_num; i++) अणु
		अगर (!sess->s.con[i])
			जारी;
		con = to_srv_con(sess->s.con[i]);
		rdma_disconnect(con->c.cm_id);
		ib_drain_qp(con->c.qp);
	पूर्ण
	/* Wait क्रम all inflights */
	rtrs_srv_रुको_ops_ids(sess);

	/* Notअगरy upper layer अगर we are the last path */
	rtrs_srv_sess_करोwn(sess);

	unmap_cont_bufs(sess);
	rtrs_srv_मुक्त_ops_ids(sess);

	क्रम (i = 0; i < sess->s.con_num; i++) अणु
		अगर (!sess->s.con[i])
			जारी;
		con = to_srv_con(sess->s.con[i]);
		rtrs_cq_qp_destroy(&con->c);
		rdma_destroy_id(con->c.cm_id);
		kमुक्त(con);
	पूर्ण
	rtrs_ib_dev_put(sess->s.dev);

	del_path_from_srv(sess);
	put_srv(sess->srv);
	sess->srv = शून्य;
	rtrs_srv_change_state(sess, RTRS_SRV_CLOSED);

	kमुक्त(sess->dma_addr);
	kमुक्त(sess->s.con);
	मुक्त_sess(sess);
पूर्ण

अटल पूर्णांक rtrs_rdma_करो_accept(काष्ठा rtrs_srv_sess *sess,
			       काष्ठा rdma_cm_id *cm_id)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_msg_conn_rsp msg;
	काष्ठा rdma_conn_param param;
	पूर्णांक err;

	param = (काष्ठा rdma_conn_param) अणु
		.rnr_retry_count = 7,
		.निजी_data = &msg,
		.निजी_data_len = माप(msg),
	पूर्ण;

	msg = (काष्ठा rtrs_msg_conn_rsp) अणु
		.magic = cpu_to_le16(RTRS_MAGIC),
		.version = cpu_to_le16(RTRS_PROTO_VER),
		.queue_depth = cpu_to_le16(srv->queue_depth),
		.max_io_size = cpu_to_le32(max_chunk_size - MAX_HDR_SIZE),
		.max_hdr_size = cpu_to_le32(MAX_HDR_SIZE),
	पूर्ण;

	अगर (always_invalidate)
		msg.flags = cpu_to_le32(RTRS_MSG_NEW_RKEY_F);

	err = rdma_accept(cm_id, &param);
	अगर (err)
		pr_err("rdma_accept(), err: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक rtrs_rdma_करो_reject(काष्ठा rdma_cm_id *cm_id, पूर्णांक त्रुटि_सं)
अणु
	काष्ठा rtrs_msg_conn_rsp msg;
	पूर्णांक err;

	msg = (काष्ठा rtrs_msg_conn_rsp) अणु
		.magic = cpu_to_le16(RTRS_MAGIC),
		.version = cpu_to_le16(RTRS_PROTO_VER),
		.त्रुटि_सं = cpu_to_le16(त्रुटि_सं),
	पूर्ण;

	err = rdma_reject(cm_id, &msg, माप(msg), IB_CM_REJ_CONSUMER_DEFINED);
	अगर (err)
		pr_err("rdma_reject(), err: %d\n", err);

	/* Bounce त्रुटि_सं back */
	वापस त्रुटि_सं;
पूर्ण

अटल काष्ठा rtrs_srv_sess *
__find_sess(काष्ठा rtrs_srv *srv, स्थिर uuid_t *sess_uuid)
अणु
	काष्ठा rtrs_srv_sess *sess;

	list_क्रम_each_entry(sess, &srv->paths_list, s.entry) अणु
		अगर (uuid_equal(&sess->s.uuid, sess_uuid))
			वापस sess;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक create_con(काष्ठा rtrs_srv_sess *sess,
		      काष्ठा rdma_cm_id *cm_id,
		      अचिन्हित पूर्णांक cid)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_sess *s = &sess->s;
	काष्ठा rtrs_srv_con *con;

	u32 cq_size, wr_queue_size;
	पूर्णांक err, cq_vector;

	con = kzalloc(माप(*con), GFP_KERNEL);
	अगर (!con) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	spin_lock_init(&con->rsp_wr_रुको_lock);
	INIT_LIST_HEAD(&con->rsp_wr_रुको_list);
	con->c.cm_id = cm_id;
	con->c.sess = &sess->s;
	con->c.cid = cid;
	atomic_set(&con->wr_cnt, 1);

	अगर (con->c.cid == 0) अणु
		/*
		 * All receive and all send (each requiring invalidate)
		 * + 2 क्रम drain and heartbeat
		 */
		wr_queue_size = SERVICE_CON_QUEUE_DEPTH * 3 + 2;
		cq_size = wr_queue_size;
	पूर्ण अन्यथा अणु
		/*
		 * If we have all receive requests posted and
		 * all ग_लिखो requests posted and each पढ़ो request
		 * requires an invalidate request + drain
		 * and qp माला_लो पूर्णांकo error state.
		 */
		cq_size = srv->queue_depth * 3 + 1;
		/*
		 * In theory we might have queue_depth * 32
		 * outstanding requests अगर an unsafe global key is used
		 * and we have queue_depth पढ़ो requests each consisting
		 * of 32 dअगरferent addresses. भाग 3 क्रम mlx5.
		 */
		wr_queue_size = sess->s.dev->ib_dev->attrs.max_qp_wr / 3;
	पूर्ण
	atomic_set(&con->sq_wr_avail, wr_queue_size);
	cq_vector = rtrs_srv_get_next_cq_vector(sess);

	/* TODO: SOFTIRQ can be faster, but be careful with softirq context */
	err = rtrs_cq_qp_create(&sess->s, &con->c, 1, cq_vector, cq_size,
				 wr_queue_size, wr_queue_size,
				 IB_POLL_WORKQUEUE);
	अगर (err) अणु
		rtrs_err(s, "rtrs_cq_qp_create(), err: %d\n", err);
		जाओ मुक्त_con;
	पूर्ण
	अगर (con->c.cid == 0) अणु
		err = post_recv_info_req(con);
		अगर (err)
			जाओ मुक्त_cqqp;
	पूर्ण
	WARN_ON(sess->s.con[cid]);
	sess->s.con[cid] = &con->c;

	/*
	 * Change context from server to current connection.  The other
	 * way is to use cm_id->qp->qp_context, which करोes not work on OFED.
	 */
	cm_id->context = &con->c;

	वापस 0;

मुक्त_cqqp:
	rtrs_cq_qp_destroy(&con->c);
मुक्त_con:
	kमुक्त(con);

err:
	वापस err;
पूर्ण

अटल काष्ठा rtrs_srv_sess *__alloc_sess(काष्ठा rtrs_srv *srv,
					   काष्ठा rdma_cm_id *cm_id,
					   अचिन्हित पूर्णांक con_num,
					   अचिन्हित पूर्णांक recon_cnt,
					   स्थिर uuid_t *uuid)
अणु
	काष्ठा rtrs_srv_sess *sess;
	पूर्णांक err = -ENOMEM;
	अक्षर str[NAME_MAX];
	काष्ठा rtrs_addr path;

	अगर (srv->paths_num >= MAX_PATHS_NUM) अणु
		err = -ECONNRESET;
		जाओ err;
	पूर्ण
	अगर (__is_path_w_addr_exists(srv, &cm_id->route.addr)) अणु
		err = -EEXIST;
		pr_err("Path with same addr exists\n");
		जाओ err;
	पूर्ण
	sess = kzalloc(माप(*sess), GFP_KERNEL);
	अगर (!sess)
		जाओ err;

	sess->stats = kzalloc(माप(*sess->stats), GFP_KERNEL);
	अगर (!sess->stats)
		जाओ err_मुक्त_sess;

	sess->stats->sess = sess;

	sess->dma_addr = kसुस्मृति(srv->queue_depth, माप(*sess->dma_addr),
				 GFP_KERNEL);
	अगर (!sess->dma_addr)
		जाओ err_मुक्त_stats;

	sess->s.con = kसुस्मृति(con_num, माप(*sess->s.con), GFP_KERNEL);
	अगर (!sess->s.con)
		जाओ err_मुक्त_dma_addr;

	sess->state = RTRS_SRV_CONNECTING;
	sess->srv = srv;
	sess->cur_cq_vector = -1;
	sess->s.dst_addr = cm_id->route.addr.dst_addr;
	sess->s.src_addr = cm_id->route.addr.src_addr;

	/* temporary until receiving session-name from client */
	path.src = &sess->s.src_addr;
	path.dst = &sess->s.dst_addr;
	rtrs_addr_to_str(&path, str, माप(str));
	strlcpy(sess->s.sessname, str, माप(sess->s.sessname));

	sess->s.con_num = con_num;
	sess->s.recon_cnt = recon_cnt;
	uuid_copy(&sess->s.uuid, uuid);
	spin_lock_init(&sess->state_lock);
	INIT_WORK(&sess->बंद_work, rtrs_srv_बंद_work);
	rtrs_srv_init_hb(sess);

	sess->s.dev = rtrs_ib_dev_find_or_add(cm_id->device, &dev_pd);
	अगर (!sess->s.dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_con;
	पूर्ण
	err = map_cont_bufs(sess);
	अगर (err)
		जाओ err_put_dev;

	err = rtrs_srv_alloc_ops_ids(sess);
	अगर (err)
		जाओ err_unmap_bufs;

	__add_path_to_srv(srv, sess);

	वापस sess;

err_unmap_bufs:
	unmap_cont_bufs(sess);
err_put_dev:
	rtrs_ib_dev_put(sess->s.dev);
err_मुक्त_con:
	kमुक्त(sess->s.con);
err_मुक्त_dma_addr:
	kमुक्त(sess->dma_addr);
err_मुक्त_stats:
	kमुक्त(sess->stats);
err_मुक्त_sess:
	kमुक्त(sess);
err:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक rtrs_rdma_connect(काष्ठा rdma_cm_id *cm_id,
			      स्थिर काष्ठा rtrs_msg_conn_req *msg,
			      माप_प्रकार len)
अणु
	काष्ठा rtrs_srv_ctx *ctx = cm_id->context;
	काष्ठा rtrs_srv_sess *sess;
	काष्ठा rtrs_srv *srv;

	u16 version, con_num, cid;
	u16 recon_cnt;
	पूर्णांक err;

	अगर (len < माप(*msg)) अणु
		pr_err("Invalid RTRS connection request\n");
		जाओ reject_w_econnreset;
	पूर्ण
	अगर (le16_to_cpu(msg->magic) != RTRS_MAGIC) अणु
		pr_err("Invalid RTRS magic\n");
		जाओ reject_w_econnreset;
	पूर्ण
	version = le16_to_cpu(msg->version);
	अगर (version >> 8 != RTRS_PROTO_VER_MAJOR) अणु
		pr_err("Unsupported major RTRS version: %d, expected %d\n",
		       version >> 8, RTRS_PROTO_VER_MAJOR);
		जाओ reject_w_econnreset;
	पूर्ण
	con_num = le16_to_cpu(msg->cid_num);
	अगर (con_num > 4096) अणु
		/* Sanity check */
		pr_err("Too many connections requested: %d\n", con_num);
		जाओ reject_w_econnreset;
	पूर्ण
	cid = le16_to_cpu(msg->cid);
	अगर (cid >= con_num) अणु
		/* Sanity check */
		pr_err("Incorrect cid: %d >= %d\n", cid, con_num);
		जाओ reject_w_econnreset;
	पूर्ण
	recon_cnt = le16_to_cpu(msg->recon_cnt);
	srv = get_or_create_srv(ctx, &msg->paths_uuid, msg->first_conn);
	अगर (IS_ERR(srv)) अणु
		err = PTR_ERR(srv);
		जाओ reject_w_err;
	पूर्ण
	mutex_lock(&srv->paths_mutex);
	sess = __find_sess(srv, &msg->sess_uuid);
	अगर (sess) अणु
		काष्ठा rtrs_sess *s = &sess->s;

		/* Session alपढ़ोy holds a reference */
		put_srv(srv);

		अगर (sess->state != RTRS_SRV_CONNECTING) अणु
			rtrs_err(s, "Session in wrong state: %s\n",
				  rtrs_srv_state_str(sess->state));
			mutex_unlock(&srv->paths_mutex);
			जाओ reject_w_econnreset;
		पूर्ण
		/*
		 * Sanity checks
		 */
		अगर (con_num != s->con_num || cid >= s->con_num) अणु
			rtrs_err(s, "Incorrect request: %d, %d\n",
				  cid, con_num);
			mutex_unlock(&srv->paths_mutex);
			जाओ reject_w_econnreset;
		पूर्ण
		अगर (s->con[cid]) अणु
			rtrs_err(s, "Connection already exists: %d\n",
				  cid);
			mutex_unlock(&srv->paths_mutex);
			जाओ reject_w_econnreset;
		पूर्ण
	पूर्ण अन्यथा अणु
		sess = __alloc_sess(srv, cm_id, con_num, recon_cnt,
				    &msg->sess_uuid);
		अगर (IS_ERR(sess)) अणु
			mutex_unlock(&srv->paths_mutex);
			put_srv(srv);
			err = PTR_ERR(sess);
			जाओ reject_w_err;
		पूर्ण
	पूर्ण
	err = create_con(sess, cm_id, cid);
	अगर (err) अणु
		(व्योम)rtrs_rdma_करो_reject(cm_id, err);
		/*
		 * Since session has other connections we follow normal way
		 * through workqueue, but still वापस an error to tell cma.c
		 * to call rdma_destroy_id() क्रम current connection.
		 */
		जाओ बंद_and_वापस_err;
	पूर्ण
	err = rtrs_rdma_करो_accept(sess, cm_id);
	अगर (err) अणु
		(व्योम)rtrs_rdma_करो_reject(cm_id, err);
		/*
		 * Since current connection was successfully added to the
		 * session we follow normal way through workqueue to बंद the
		 * session, thus वापस 0 to tell cma.c we call
		 * rdma_destroy_id() ourselves.
		 */
		err = 0;
		जाओ बंद_and_वापस_err;
	पूर्ण
	mutex_unlock(&srv->paths_mutex);

	वापस 0;

reject_w_err:
	वापस rtrs_rdma_करो_reject(cm_id, err);

reject_w_econnreset:
	वापस rtrs_rdma_करो_reject(cm_id, -ECONNRESET);

बंद_and_वापस_err:
	mutex_unlock(&srv->paths_mutex);
	बंद_sess(sess);

	वापस err;
पूर्ण

अटल पूर्णांक rtrs_srv_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
				     काष्ठा rdma_cm_event *ev)
अणु
	काष्ठा rtrs_srv_sess *sess = शून्य;
	काष्ठा rtrs_sess *s = शून्य;

	अगर (ev->event != RDMA_CM_EVENT_CONNECT_REQUEST) अणु
		काष्ठा rtrs_con *c = cm_id->context;

		s = c->sess;
		sess = to_srv_sess(s);
	पूर्ण

	चयन (ev->event) अणु
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
		/*
		 * In हाल of error cma.c will destroy cm_id,
		 * see cma_process_हटाओ()
		 */
		वापस rtrs_rdma_connect(cm_id, ev->param.conn.निजी_data,
					  ev->param.conn.निजी_data_len);
	हाल RDMA_CM_EVENT_ESTABLISHED:
		/* Nothing here */
		अवरोध;
	हाल RDMA_CM_EVENT_REJECTED:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
		rtrs_err(s, "CM error (CM event: %s, err: %d)\n",
			  rdma_event_msg(ev->event), ev->status);
		fallthrough;
	हाल RDMA_CM_EVENT_DISCONNECTED:
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		बंद_sess(sess);
		अवरोध;
	शेष:
		pr_err("Ignoring unexpected CM event %s, err %d\n",
		       rdma_event_msg(ev->event), ev->status);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rdma_cm_id *rtrs_srv_cm_init(काष्ठा rtrs_srv_ctx *ctx,
					    काष्ठा sockaddr *addr,
					    क्रमागत rdma_ucm_port_space ps)
अणु
	काष्ठा rdma_cm_id *cm_id;
	पूर्णांक ret;

	cm_id = rdma_create_id(&init_net, rtrs_srv_rdma_cm_handler,
			       ctx, ps, IB_QPT_RC);
	अगर (IS_ERR(cm_id)) अणु
		ret = PTR_ERR(cm_id);
		pr_err("Creating id for RDMA connection failed, err: %d\n",
		       ret);
		जाओ err_out;
	पूर्ण
	ret = rdma_bind_addr(cm_id, addr);
	अगर (ret) अणु
		pr_err("Binding RDMA address failed, err: %d\n", ret);
		जाओ err_cm;
	पूर्ण
	ret = rdma_listen(cm_id, 64);
	अगर (ret) अणु
		pr_err("Listening on RDMA connection failed, err: %d\n",
		       ret);
		जाओ err_cm;
	पूर्ण

	वापस cm_id;

err_cm:
	rdma_destroy_id(cm_id);
err_out:

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक rtrs_srv_rdma_init(काष्ठा rtrs_srv_ctx *ctx, u16 port)
अणु
	काष्ठा sockaddr_in6 sin = अणु
		.sin6_family	= AF_INET6,
		.sin6_addr	= IN6ADDR_ANY_INIT,
		.sin6_port	= htons(port),
	पूर्ण;
	काष्ठा sockaddr_ib sib = अणु
		.sib_family			= AF_IB,
		.sib_sid	= cpu_to_be64(RDMA_IB_IP_PS_IB | port),
		.sib_sid_mask	= cpu_to_be64(0xffffffffffffffffULL),
		.sib_pkey	= cpu_to_be16(0xffff),
	पूर्ण;
	काष्ठा rdma_cm_id *cm_ip, *cm_ib;
	पूर्णांक ret;

	/*
	 * We accept both IPoIB and IB connections, so we need to keep
	 * two cm id's, one क्रम each socket type and port space.
	 * If the cm initialization of one of the id's fails, we पात
	 * everything.
	 */
	cm_ip = rtrs_srv_cm_init(ctx, (काष्ठा sockaddr *)&sin, RDMA_PS_TCP);
	अगर (IS_ERR(cm_ip))
		वापस PTR_ERR(cm_ip);

	cm_ib = rtrs_srv_cm_init(ctx, (काष्ठा sockaddr *)&sib, RDMA_PS_IB);
	अगर (IS_ERR(cm_ib)) अणु
		ret = PTR_ERR(cm_ib);
		जाओ मुक्त_cm_ip;
	पूर्ण

	ctx->cm_id_ip = cm_ip;
	ctx->cm_id_ib = cm_ib;

	वापस 0;

मुक्त_cm_ip:
	rdma_destroy_id(cm_ip);

	वापस ret;
पूर्ण

अटल काष्ठा rtrs_srv_ctx *alloc_srv_ctx(काष्ठा rtrs_srv_ops *ops)
अणु
	काष्ठा rtrs_srv_ctx *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	ctx->ops = *ops;
	mutex_init(&ctx->srv_mutex);
	INIT_LIST_HEAD(&ctx->srv_list);

	वापस ctx;
पूर्ण

अटल व्योम मुक्त_srv_ctx(काष्ठा rtrs_srv_ctx *ctx)
अणु
	WARN_ON(!list_empty(&ctx->srv_list));
	mutex_destroy(&ctx->srv_mutex);
	kमुक्त(ctx);
पूर्ण

अटल पूर्णांक rtrs_srv_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा rtrs_srv_ctx *ctx;
	पूर्णांक ret = 0;

	mutex_lock(&ib_ctx.ib_dev_mutex);
	अगर (ib_ctx.ib_dev_count)
		जाओ out;

	/*
	 * Since our CM IDs are NOT bound to any ib device we will create them
	 * only once
	 */
	ctx = ib_ctx.srv_ctx;
	ret = rtrs_srv_rdma_init(ctx, ib_ctx.port);
	अगर (ret) अणु
		/*
		 * We errored out here.
		 * According to the ib code, अगर we encounter an error here then the
		 * error code is ignored, and no more calls to our ops are made.
		 */
		pr_err("Failed to initialize RDMA connection");
		जाओ err_out;
	पूर्ण

out:
	/*
	 * Keep a track on the number of ib devices added
	 */
	ib_ctx.ib_dev_count++;

err_out:
	mutex_unlock(&ib_ctx.ib_dev_mutex);
	वापस ret;
पूर्ण

अटल व्योम rtrs_srv_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा rtrs_srv_ctx *ctx;

	mutex_lock(&ib_ctx.ib_dev_mutex);
	ib_ctx.ib_dev_count--;

	अगर (ib_ctx.ib_dev_count)
		जाओ out;

	/*
	 * Since our CM IDs are NOT bound to any ib device we will हटाओ them
	 * only once, when the last device is हटाओd
	 */
	ctx = ib_ctx.srv_ctx;
	rdma_destroy_id(ctx->cm_id_ip);
	rdma_destroy_id(ctx->cm_id_ib);

out:
	mutex_unlock(&ib_ctx.ib_dev_mutex);
पूर्ण

अटल काष्ठा ib_client rtrs_srv_client = अणु
	.name	= "rtrs_server",
	.add	= rtrs_srv_add_one,
	.हटाओ	= rtrs_srv_हटाओ_one
पूर्ण;

/**
 * rtrs_srv_खोलो() - खोलो RTRS server context
 * @ops:		callback functions
 * @port:               port to listen on
 *
 * Creates server context with specअगरied callbacks.
 *
 * Return a valid poपूर्णांकer on success otherwise PTR_ERR.
 */
काष्ठा rtrs_srv_ctx *rtrs_srv_खोलो(काष्ठा rtrs_srv_ops *ops, u16 port)
अणु
	काष्ठा rtrs_srv_ctx *ctx;
	पूर्णांक err;

	ctx = alloc_srv_ctx(ops);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&ib_ctx.ib_dev_mutex);
	ib_ctx.srv_ctx = ctx;
	ib_ctx.port = port;

	err = ib_रेजिस्टर_client(&rtrs_srv_client);
	अगर (err) अणु
		मुक्त_srv_ctx(ctx);
		वापस ERR_PTR(err);
	पूर्ण

	वापस ctx;
पूर्ण
EXPORT_SYMBOL(rtrs_srv_खोलो);

अटल व्योम बंद_sessions(काष्ठा rtrs_srv *srv)
अणु
	काष्ठा rtrs_srv_sess *sess;

	mutex_lock(&srv->paths_mutex);
	list_क्रम_each_entry(sess, &srv->paths_list, s.entry)
		बंद_sess(sess);
	mutex_unlock(&srv->paths_mutex);
पूर्ण

अटल व्योम बंद_ctx(काष्ठा rtrs_srv_ctx *ctx)
अणु
	काष्ठा rtrs_srv *srv;

	mutex_lock(&ctx->srv_mutex);
	list_क्रम_each_entry(srv, &ctx->srv_list, ctx_list)
		बंद_sessions(srv);
	mutex_unlock(&ctx->srv_mutex);
	flush_workqueue(rtrs_wq);
पूर्ण

/**
 * rtrs_srv_बंद() - बंद RTRS server context
 * @ctx: poपूर्णांकer to server context
 *
 * Closes RTRS server context with all client sessions.
 */
व्योम rtrs_srv_बंद(काष्ठा rtrs_srv_ctx *ctx)
अणु
	ib_unरेजिस्टर_client(&rtrs_srv_client);
	mutex_destroy(&ib_ctx.ib_dev_mutex);
	बंद_ctx(ctx);
	मुक्त_srv_ctx(ctx);
पूर्ण
EXPORT_SYMBOL(rtrs_srv_बंद);

अटल पूर्णांक check_module_params(व्योम)
अणु
	अगर (sess_queue_depth < 1 || sess_queue_depth > MAX_SESS_QUEUE_DEPTH) अणु
		pr_err("Invalid sess_queue_depth value %d, has to be >= %d, <= %d.\n",
		       sess_queue_depth, 1, MAX_SESS_QUEUE_DEPTH);
		वापस -EINVAL;
	पूर्ण
	अगर (max_chunk_size < 4096 || !is_घातer_of_2(max_chunk_size)) अणु
		pr_err("Invalid max_chunk_size value %d, has to be >= %d and should be power of two.\n",
		       max_chunk_size, 4096);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check अगर IB immediate data size is enough to hold the mem_id and the
	 * offset inside the memory chunk
	 */
	अगर ((ilog2(sess_queue_depth - 1) + 1) +
	    (ilog2(max_chunk_size - 1) + 1) > MAX_IMM_PAYL_BITS) अणु
		pr_err("RDMA immediate size (%db) not enough to encode %d buffers of size %dB. Reduce 'sess_queue_depth' or 'max_chunk_size' parameters.\n",
		       MAX_IMM_PAYL_BITS, sess_queue_depth, max_chunk_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init rtrs_server_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("Loading module %s, proto %s: (max_chunk_size: %d (pure IO %ld, headers %ld) , sess_queue_depth: %d, always_invalidate: %d)\n",
		KBUILD_MODNAME, RTRS_PROTO_VER_STRING,
		max_chunk_size, max_chunk_size - MAX_HDR_SIZE, MAX_HDR_SIZE,
		sess_queue_depth, always_invalidate);

	rtrs_rdma_dev_pd_init(0, &dev_pd);

	err = check_module_params();
	अगर (err) अणु
		pr_err("Failed to load module, invalid module parameters, err: %d\n",
		       err);
		वापस err;
	पूर्ण
	chunk_pool = mempool_create_page_pool(sess_queue_depth * CHUNK_POOL_SZ,
					      get_order(max_chunk_size));
	अगर (!chunk_pool)
		वापस -ENOMEM;
	rtrs_dev_class = class_create(THIS_MODULE, "rtrs-server");
	अगर (IS_ERR(rtrs_dev_class)) अणु
		err = PTR_ERR(rtrs_dev_class);
		जाओ out_chunk_pool;
	पूर्ण
	rtrs_wq = alloc_workqueue("rtrs_server_wq", 0, 0);
	अगर (!rtrs_wq) अणु
		err = -ENOMEM;
		जाओ out_dev_class;
	पूर्ण

	वापस 0;

out_dev_class:
	class_destroy(rtrs_dev_class);
out_chunk_pool:
	mempool_destroy(chunk_pool);

	वापस err;
पूर्ण

अटल व्योम __निकास rtrs_server_निकास(व्योम)
अणु
	destroy_workqueue(rtrs_wq);
	class_destroy(rtrs_dev_class);
	mempool_destroy(chunk_pool);
	rtrs_rdma_dev_pd_deinit(&dev_pd);
पूर्ण

module_init(rtrs_server_init);
module_निकास(rtrs_server_निकास);
