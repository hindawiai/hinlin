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
#समावेश <linux/rculist.h>
#समावेश <linux/अक्रमom.h>

#समावेश "rtrs-clt.h"
#समावेश "rtrs-log.h"

#घोषणा RTRS_CONNECT_TIMEOUT_MS 30000
/*
 * Wait a bit beक्रमe trying to reconnect after a failure
 * in order to give server समय to finish clean up which
 * leads to "false positives" failed reconnect attempts
 */
#घोषणा RTRS_RECONNECT_BACKOFF 1000
/*
 * Wait क्रम additional अक्रमom समय between 0 and 8 seconds
 * beक्रमe starting to reconnect to aव्योम clients reconnecting
 * all at once in हाल of a major network outage
 */
#घोषणा RTRS_RECONNECT_SEED 8

#घोषणा FIRST_CONN 0x01

MODULE_DESCRIPTION("RDMA Transport Client");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा rtrs_rdma_dev_pd_ops dev_pd_ops;
अटल काष्ठा rtrs_rdma_dev_pd dev_pd = अणु
	.ops = &dev_pd_ops
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *rtrs_wq;
अटल काष्ठा class *rtrs_clt_dev_class;

अटल अंतरभूत bool rtrs_clt_is_connected(स्थिर काष्ठा rtrs_clt *clt)
अणु
	काष्ठा rtrs_clt_sess *sess;
	bool connected = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sess, &clt->paths_list, s.entry)
		connected |= READ_ONCE(sess->state) == RTRS_CLT_CONNECTED;
	rcu_पढ़ो_unlock();

	वापस connected;
पूर्ण

अटल काष्ठा rtrs_permit *
__rtrs_get_permit(काष्ठा rtrs_clt *clt, क्रमागत rtrs_clt_con_type con_type)
अणु
	माप_प्रकार max_depth = clt->queue_depth;
	काष्ठा rtrs_permit *permit;
	पूर्णांक bit;

	/*
	 * Adapted from null_blk get_tag(). Callers from dअगरferent cpus may
	 * grab the same bit, since find_first_zero_bit is not atomic.
	 * But then the test_and_set_bit_lock will fail क्रम all the
	 * callers but one, so that they will loop again.
	 * This way an explicit spinlock is not required.
	 */
	करो अणु
		bit = find_first_zero_bit(clt->permits_map, max_depth);
		अगर (unlikely(bit >= max_depth))
			वापस शून्य;
	पूर्ण जबतक (unlikely(test_and_set_bit_lock(bit, clt->permits_map)));

	permit = get_permit(clt, bit);
	WARN_ON(permit->mem_id != bit);
	permit->cpu_id = raw_smp_processor_id();
	permit->con_type = con_type;

	वापस permit;
पूर्ण

अटल अंतरभूत व्योम __rtrs_put_permit(काष्ठा rtrs_clt *clt,
				      काष्ठा rtrs_permit *permit)
अणु
	clear_bit_unlock(permit->mem_id, clt->permits_map);
पूर्ण

/**
 * rtrs_clt_get_permit() - allocates permit क्रम future RDMA operation
 * @clt:	Current session
 * @con_type:	Type of connection to use with the permit
 * @can_रुको:	Wait type
 *
 * Description:
 *    Allocates permit क्रम the following RDMA operation.  Permit is used
 *    to pपुनः_स्मृतिate all resources and to propagate memory pressure
 *    up earlier.
 *
 * Context:
 *    Can sleep अगर @रुको == RTRS_PERMIT_WAIT
 */
काष्ठा rtrs_permit *rtrs_clt_get_permit(काष्ठा rtrs_clt *clt,
					  क्रमागत rtrs_clt_con_type con_type,
					  क्रमागत रुको_type can_रुको)
अणु
	काष्ठा rtrs_permit *permit;
	DEFINE_WAIT(रुको);

	permit = __rtrs_get_permit(clt, con_type);
	अगर (likely(permit) || !can_रुको)
		वापस permit;

	करो अणु
		prepare_to_रुको(&clt->permits_रुको, &रुको,
				TASK_UNINTERRUPTIBLE);
		permit = __rtrs_get_permit(clt, con_type);
		अगर (likely(permit))
			अवरोध;

		io_schedule();
	पूर्ण जबतक (1);

	finish_रुको(&clt->permits_रुको, &रुको);

	वापस permit;
पूर्ण
EXPORT_SYMBOL(rtrs_clt_get_permit);

/**
 * rtrs_clt_put_permit() - माला_दो allocated permit
 * @clt:	Current session
 * @permit:	Permit to be मुक्तd
 *
 * Context:
 *    Does not matter
 */
व्योम rtrs_clt_put_permit(काष्ठा rtrs_clt *clt, काष्ठा rtrs_permit *permit)
अणु
	अगर (WARN_ON(!test_bit(permit->mem_id, clt->permits_map)))
		वापस;

	__rtrs_put_permit(clt, permit);

	/*
	 * rtrs_clt_get_permit() adds itself to the &clt->permits_रुको list
	 * beक्रमe calling schedule(). So अगर rtrs_clt_get_permit() is sleeping
	 * it must have added itself to &clt->permits_रुको beक्रमe
	 * __rtrs_put_permit() finished.
	 * Hence it is safe to guard wake_up() with a रुकोqueue_active() test.
	 */
	अगर (रुकोqueue_active(&clt->permits_रुको))
		wake_up(&clt->permits_रुको);
पूर्ण
EXPORT_SYMBOL(rtrs_clt_put_permit);

/**
 * rtrs_permit_to_clt_con() - वापसs RDMA connection poपूर्णांकer by the permit
 * @sess: client session poपूर्णांकer
 * @permit: permit क्रम the allocation of the RDMA buffer
 * Note:
 *     IO connection starts from 1.
 *     0 connection is क्रम user messages.
 */
अटल
काष्ठा rtrs_clt_con *rtrs_permit_to_clt_con(काष्ठा rtrs_clt_sess *sess,
					    काष्ठा rtrs_permit *permit)
अणु
	पूर्णांक id = 0;

	अगर (likely(permit->con_type == RTRS_IO_CON))
		id = (permit->cpu_id % (sess->s.irq_con_num - 1)) + 1;

	वापस to_clt_con(sess->s.con[id]);
पूर्ण

/**
 * rtrs_clt_change_state() - change the session state through session state
 * machine.
 *
 * @sess: client session to change the state of.
 * @new_state: state to change to.
 *
 * वापसs true अगर sess's state is changed to new state, otherwise वापस false.
 *
 * Locks:
 * state_wq lock must be hold.
 */
अटल bool rtrs_clt_change_state(काष्ठा rtrs_clt_sess *sess,
				     क्रमागत rtrs_clt_state new_state)
अणु
	क्रमागत rtrs_clt_state old_state;
	bool changed = false;

	lockdep_निश्चित_held(&sess->state_wq.lock);

	old_state = sess->state;
	चयन (new_state) अणु
	हाल RTRS_CLT_CONNECTING:
		चयन (old_state) अणु
		हाल RTRS_CLT_RECONNECTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_CLT_RECONNECTING:
		चयन (old_state) अणु
		हाल RTRS_CLT_CONNECTED:
		हाल RTRS_CLT_CONNECTING_ERR:
		हाल RTRS_CLT_CLOSED:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_CLT_CONNECTED:
		चयन (old_state) अणु
		हाल RTRS_CLT_CONNECTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_CLT_CONNECTING_ERR:
		चयन (old_state) अणु
		हाल RTRS_CLT_CONNECTING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_CLT_CLOSING:
		चयन (old_state) अणु
		हाल RTRS_CLT_CONNECTING:
		हाल RTRS_CLT_CONNECTING_ERR:
		हाल RTRS_CLT_RECONNECTING:
		हाल RTRS_CLT_CONNECTED:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_CLT_CLOSED:
		चयन (old_state) अणु
		हाल RTRS_CLT_CLOSING:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल RTRS_CLT_DEAD:
		चयन (old_state) अणु
		हाल RTRS_CLT_CLOSED:
			changed = true;
			fallthrough;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (changed) अणु
		sess->state = new_state;
		wake_up_locked(&sess->state_wq);
	पूर्ण

	वापस changed;
पूर्ण

अटल bool rtrs_clt_change_state_from_to(काष्ठा rtrs_clt_sess *sess,
					   क्रमागत rtrs_clt_state old_state,
					   क्रमागत rtrs_clt_state new_state)
अणु
	bool changed = false;

	spin_lock_irq(&sess->state_wq.lock);
	अगर (sess->state == old_state)
		changed = rtrs_clt_change_state(sess, new_state);
	spin_unlock_irq(&sess->state_wq.lock);

	वापस changed;
पूर्ण

अटल व्योम rtrs_rdma_error_recovery(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);

	अगर (rtrs_clt_change_state_from_to(sess,
					   RTRS_CLT_CONNECTED,
					   RTRS_CLT_RECONNECTING)) अणु
		काष्ठा rtrs_clt *clt = sess->clt;
		अचिन्हित पूर्णांक delay_ms;

		/*
		 * Normal scenario, reconnect अगर we were successfully connected
		 */
		delay_ms = clt->reconnect_delay_sec * 1000;
		queue_delayed_work(rtrs_wq, &sess->reconnect_dwork,
				   msecs_to_jअगरfies(delay_ms +
						    pअक्रमom_u32() % RTRS_RECONNECT_SEED));
	पूर्ण अन्यथा अणु
		/*
		 * Error can happen just on establishing new connection,
		 * so notअगरy रुकोer with error state, रुकोer is responsible
		 * क्रम cleaning the rest and reconnect अगर needed.
		 */
		rtrs_clt_change_state_from_to(sess,
					       RTRS_CLT_CONNECTING,
					       RTRS_CLT_CONNECTING_ERR);
	पूर्ण
पूर्ण

अटल व्योम rtrs_clt_fast_reg_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_clt_con *con = to_clt_con(wc->qp->qp_context);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(con->c.sess, "Failed IB_WR_REG_MR: %s\n",
			  ib_wc_status_msg(wc->status));
		rtrs_rdma_error_recovery(con);
	पूर्ण
पूर्ण

अटल काष्ठा ib_cqe fast_reg_cqe = अणु
	.करोne = rtrs_clt_fast_reg_करोne
पूर्ण;

अटल व्योम complete_rdma_req(काष्ठा rtrs_clt_io_req *req, पूर्णांक त्रुटि_सं,
			      bool notअगरy, bool can_रुको);

अटल व्योम rtrs_clt_inv_rkey_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_clt_io_req *req =
		container_of(wc->wr_cqe, typeof(*req), inv_cqe);
	काष्ठा rtrs_clt_con *con = to_clt_con(wc->qp->qp_context);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(con->c.sess, "Failed IB_WR_LOCAL_INV: %s\n",
			  ib_wc_status_msg(wc->status));
		rtrs_rdma_error_recovery(con);
	पूर्ण
	req->need_inv = false;
	अगर (likely(req->need_inv_comp))
		complete(&req->inv_comp);
	अन्यथा
		/* Complete request from INV callback */
		complete_rdma_req(req, req->inv_त्रुटि_सं, true, false);
पूर्ण

अटल पूर्णांक rtrs_inv_rkey(काष्ठा rtrs_clt_io_req *req)
अणु
	काष्ठा rtrs_clt_con *con = req->con;
	काष्ठा ib_send_wr wr = अणु
		.opcode		    = IB_WR_LOCAL_INV,
		.wr_cqe		    = &req->inv_cqe,
		.send_flags	    = IB_SEND_SIGNALED,
		.ex.invalidate_rkey = req->mr->rkey,
	पूर्ण;
	req->inv_cqe.करोne = rtrs_clt_inv_rkey_करोne;

	वापस ib_post_send(con->c.qp, &wr, शून्य);
पूर्ण

अटल व्योम complete_rdma_req(काष्ठा rtrs_clt_io_req *req, पूर्णांक त्रुटि_सं,
			      bool notअगरy, bool can_रुको)
अणु
	काष्ठा rtrs_clt_con *con = req->con;
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक err;

	अगर (WARN_ON(!req->in_use))
		वापस;
	अगर (WARN_ON(!req->con))
		वापस;
	sess = to_clt_sess(con->c.sess);

	अगर (req->sg_cnt) अणु
		अगर (unlikely(req->dir == DMA_FROM_DEVICE && req->need_inv)) अणु
			/*
			 * We are here to invalidate पढ़ो requests
			 * ourselves.  In normal scenario server should
			 * send INV क्रम all पढ़ो requests, but
			 * we are here, thus two things could happen:
			 *
			 *    1.  this is failover, when त्रुटि_सं != 0
			 *        and can_रुको == 1,
			 *
			 *    2.  something totally bad happened and
			 *        server क्रमgot to send INV, so we
			 *        should करो that ourselves.
			 */

			अगर (likely(can_रुको)) अणु
				req->need_inv_comp = true;
			पूर्ण अन्यथा अणु
				/* This should be IO path, so always notअगरy */
				WARN_ON(!notअगरy);
				/* Save त्रुटि_सं क्रम INV callback */
				req->inv_त्रुटि_सं = त्रुटि_सं;
			पूर्ण

			err = rtrs_inv_rkey(req);
			अगर (unlikely(err)) अणु
				rtrs_err(con->c.sess, "Send INV WR key=%#x: %d\n",
					  req->mr->rkey, err);
			पूर्ण अन्यथा अगर (likely(can_रुको)) अणु
				रुको_क्रम_completion(&req->inv_comp);
			पूर्ण अन्यथा अणु
				/*
				 * Something went wrong, so request will be
				 * completed from INV callback.
				 */
				WARN_ON_ONCE(1);

				वापस;
			पूर्ण
		पूर्ण
		ib_dma_unmap_sg(sess->s.dev->ib_dev, req->sglist,
				req->sg_cnt, req->dir);
	पूर्ण
	अगर (sess->clt->mp_policy == MP_POLICY_MIN_INFLIGHT)
		atomic_dec(&sess->stats->inflight);

	req->in_use = false;
	req->con = शून्य;

	अगर (त्रुटि_सं) अणु
		rtrs_err_rl(con->c.sess,
			    "IO request failed: error=%d path=%s [%s:%u]\n",
			    त्रुटि_सं, kobject_name(&sess->kobj), sess->hca_name,
			    sess->hca_port);
	पूर्ण

	अगर (notअगरy)
		req->conf(req->priv, त्रुटि_सं);
पूर्ण

अटल पूर्णांक rtrs_post_send_rdma(काष्ठा rtrs_clt_con *con,
				काष्ठा rtrs_clt_io_req *req,
				काष्ठा rtrs_rbuf *rbuf, u32 off,
				u32 imm, काष्ठा ib_send_wr *wr)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	क्रमागत ib_send_flags flags;
	काष्ठा ib_sge sge;

	अगर (unlikely(!req->sg_size)) अणु
		rtrs_wrn(con->c.sess,
			 "Doing RDMA Write failed, no data supplied\n");
		वापस -EINVAL;
	पूर्ण

	/* user data and user message in the first list element */
	sge.addr   = req->iu->dma_addr;
	sge.length = req->sg_size;
	sge.lkey   = sess->s.dev->ib_pd->local_dma_lkey;

	/*
	 * From समय to समय we have to post संकेतled sends,
	 * or send queue will fill up and only QP reset can help.
	 */
	flags = atomic_inc_वापस(&con->io_cnt) % sess->queue_depth ?
			0 : IB_SEND_SIGNALED;

	ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev, req->iu->dma_addr,
				      req->sg_size, DMA_TO_DEVICE);

	वापस rtrs_iu_post_rdma_ग_लिखो_imm(&con->c, req->iu, &sge, 1,
					    rbuf->rkey, rbuf->addr + off,
					    imm, flags, wr);
पूर्ण

अटल व्योम process_io_rsp(काष्ठा rtrs_clt_sess *sess, u32 msg_id,
			   s16 त्रुटि_सं, bool w_inval)
अणु
	काष्ठा rtrs_clt_io_req *req;

	अगर (WARN_ON(msg_id >= sess->queue_depth))
		वापस;

	req = &sess->reqs[msg_id];
	/* Drop need_inv अगर server responded with send with invalidation */
	req->need_inv &= !w_inval;
	complete_rdma_req(req, त्रुटि_सं, true, false);
पूर्ण

अटल व्योम rtrs_clt_recv_करोne(काष्ठा rtrs_clt_con *con, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_iu *iu;
	पूर्णांक err;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);

	WARN_ON((sess->flags & RTRS_MSG_NEW_RKEY_F) == 0);
	iu = container_of(wc->wr_cqe, काष्ठा rtrs_iu,
			  cqe);
	err = rtrs_iu_post_recv(&con->c, iu);
	अगर (unlikely(err)) अणु
		rtrs_err(con->c.sess, "post iu failed %d\n", err);
		rtrs_rdma_error_recovery(con);
	पूर्ण
पूर्ण

अटल व्योम rtrs_clt_rkey_rsp_करोne(काष्ठा rtrs_clt_con *con, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_msg_rkey_rsp *msg;
	u32 imm_type, imm_payload;
	bool w_inval = false;
	काष्ठा rtrs_iu *iu;
	u32 buf_id;
	पूर्णांक err;

	WARN_ON((sess->flags & RTRS_MSG_NEW_RKEY_F) == 0);

	iu = container_of(wc->wr_cqe, काष्ठा rtrs_iu, cqe);

	अगर (unlikely(wc->byte_len < माप(*msg))) अणु
		rtrs_err(con->c.sess, "rkey response is malformed: size %d\n",
			  wc->byte_len);
		जाओ out;
	पूर्ण
	ib_dma_sync_single_क्रम_cpu(sess->s.dev->ib_dev, iu->dma_addr,
				   iu->size, DMA_FROM_DEVICE);
	msg = iu->buf;
	अगर (unlikely(le16_to_cpu(msg->type) != RTRS_MSG_RKEY_RSP)) अणु
		rtrs_err(sess->clt, "rkey response is malformed: type %d\n",
			  le16_to_cpu(msg->type));
		जाओ out;
	पूर्ण
	buf_id = le16_to_cpu(msg->buf_id);
	अगर (WARN_ON(buf_id >= sess->queue_depth))
		जाओ out;

	rtrs_from_imm(be32_to_cpu(wc->ex.imm_data), &imm_type, &imm_payload);
	अगर (likely(imm_type == RTRS_IO_RSP_IMM ||
		   imm_type == RTRS_IO_RSP_W_INV_IMM)) अणु
		u32 msg_id;

		w_inval = (imm_type == RTRS_IO_RSP_W_INV_IMM);
		rtrs_from_io_rsp_imm(imm_payload, &msg_id, &err);

		अगर (WARN_ON(buf_id != msg_id))
			जाओ out;
		sess->rbufs[buf_id].rkey = le32_to_cpu(msg->rkey);
		process_io_rsp(sess, msg_id, err, w_inval);
	पूर्ण
	ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev, iu->dma_addr,
				      iu->size, DMA_FROM_DEVICE);
	वापस rtrs_clt_recv_करोne(con, wc);
out:
	rtrs_rdma_error_recovery(con);
पूर्ण

अटल व्योम rtrs_clt_rdma_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

अटल काष्ठा ib_cqe io_comp_cqe = अणु
	.करोne = rtrs_clt_rdma_करोne
पूर्ण;

/*
 * Post x2 empty WRs: first is क्रम this RDMA with IMM,
 * second is क्रम RECV with INV, which happened earlier.
 */
अटल पूर्णांक rtrs_post_recv_empty_x2(काष्ठा rtrs_con *con, काष्ठा ib_cqe *cqe)
अणु
	काष्ठा ib_recv_wr wr_arr[2], *wr;
	पूर्णांक i;

	स_रखो(wr_arr, 0, माप(wr_arr));
	क्रम (i = 0; i < ARRAY_SIZE(wr_arr); i++) अणु
		wr = &wr_arr[i];
		wr->wr_cqe  = cqe;
		अगर (i)
			/* Chain backwards */
			wr->next = &wr_arr[i - 1];
	पूर्ण

	वापस ib_post_recv(con->qp, wr, शून्य);
पूर्ण

अटल व्योम rtrs_clt_rdma_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_clt_con *con = to_clt_con(wc->qp->qp_context);
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	u32 imm_type, imm_payload;
	bool w_inval = false;
	पूर्णांक err;

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		अगर (wc->status != IB_WC_WR_FLUSH_ERR) अणु
			rtrs_err(sess->clt, "RDMA failed: %s\n",
				  ib_wc_status_msg(wc->status));
			rtrs_rdma_error_recovery(con);
		पूर्ण
		वापस;
	पूर्ण
	rtrs_clt_update_wc_stats(con);

	चयन (wc->opcode) अणु
	हाल IB_WC_RECV_RDMA_WITH_IMM:
		/*
		 * post_recv() RDMA ग_लिखो completions of IO reqs (पढ़ो/ग_लिखो)
		 * and hb
		 */
		अगर (WARN_ON(wc->wr_cqe->करोne != rtrs_clt_rdma_करोne))
			वापस;
		rtrs_from_imm(be32_to_cpu(wc->ex.imm_data),
			       &imm_type, &imm_payload);
		अगर (likely(imm_type == RTRS_IO_RSP_IMM ||
			   imm_type == RTRS_IO_RSP_W_INV_IMM)) अणु
			u32 msg_id;

			w_inval = (imm_type == RTRS_IO_RSP_W_INV_IMM);
			rtrs_from_io_rsp_imm(imm_payload, &msg_id, &err);

			process_io_rsp(sess, msg_id, err, w_inval);
		पूर्ण अन्यथा अगर (imm_type == RTRS_HB_MSG_IMM) अणु
			WARN_ON(con->c.cid);
			rtrs_send_hb_ack(&sess->s);
			अगर (sess->flags & RTRS_MSG_NEW_RKEY_F)
				वापस  rtrs_clt_recv_करोne(con, wc);
		पूर्ण अन्यथा अगर (imm_type == RTRS_HB_ACK_IMM) अणु
			WARN_ON(con->c.cid);
			sess->s.hb_missed_cnt = 0;
			sess->s.hb_cur_latency =
				kसमय_sub(kसमय_get(), sess->s.hb_last_sent);
			अगर (sess->flags & RTRS_MSG_NEW_RKEY_F)
				वापस  rtrs_clt_recv_करोne(con, wc);
		पूर्ण अन्यथा अणु
			rtrs_wrn(con->c.sess, "Unknown IMM type %u\n",
				  imm_type);
		पूर्ण
		अगर (w_inval)
			/*
			 * Post x2 empty WRs: first is क्रम this RDMA with IMM,
			 * second is क्रम RECV with INV, which happened earlier.
			 */
			err = rtrs_post_recv_empty_x2(&con->c, &io_comp_cqe);
		अन्यथा
			err = rtrs_post_recv_empty(&con->c, &io_comp_cqe);
		अगर (unlikely(err)) अणु
			rtrs_err(con->c.sess, "rtrs_post_recv_empty(): %d\n",
				  err);
			rtrs_rdma_error_recovery(con);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IB_WC_RECV:
		/*
		 * Key invalidations from server side
		 */
		WARN_ON(!(wc->wc_flags & IB_WC_WITH_INVALIDATE ||
			  wc->wc_flags & IB_WC_WITH_IMM));
		WARN_ON(wc->wr_cqe->करोne != rtrs_clt_rdma_करोne);
		अगर (sess->flags & RTRS_MSG_NEW_RKEY_F) अणु
			अगर (wc->wc_flags & IB_WC_WITH_INVALIDATE)
				वापस  rtrs_clt_recv_करोne(con, wc);

			वापस  rtrs_clt_rkey_rsp_करोne(con, wc);
		पूर्ण
		अवरोध;
	हाल IB_WC_RDMA_WRITE:
		/*
		 * post_send() RDMA ग_लिखो completions of IO reqs (पढ़ो/ग_लिखो)
		 */
		अवरोध;

	शेष:
		rtrs_wrn(sess->clt, "Unexpected WC type: %d\n", wc->opcode);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक post_recv_io(काष्ठा rtrs_clt_con *con, माप_प्रकार q_size)
अणु
	पूर्णांक err, i;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);

	क्रम (i = 0; i < q_size; i++) अणु
		अगर (sess->flags & RTRS_MSG_NEW_RKEY_F) अणु
			काष्ठा rtrs_iu *iu = &con->rsp_ius[i];

			err = rtrs_iu_post_recv(&con->c, iu);
		पूर्ण अन्यथा अणु
			err = rtrs_post_recv_empty(&con->c, &io_comp_cqe);
		पूर्ण
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक post_recv_sess(काष्ठा rtrs_clt_sess *sess)
अणु
	माप_प्रकार q_size = 0;
	पूर्णांक err, cid;

	क्रम (cid = 0; cid < sess->s.con_num; cid++) अणु
		अगर (cid == 0)
			q_size = SERVICE_CON_QUEUE_DEPTH;
		अन्यथा
			q_size = sess->queue_depth;

		/*
		 * x2 क्रम RDMA पढ़ो responses + FR key invalidations,
		 * RDMA ग_लिखोs करो not require any FR registrations.
		 */
		q_size *= 2;

		err = post_recv_io(to_clt_con(sess->s.con[cid]), q_size);
		अगर (unlikely(err)) अणु
			rtrs_err(sess->clt, "post_recv_io(), err: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा path_it अणु
	पूर्णांक i;
	काष्ठा list_head skip_list;
	काष्ठा rtrs_clt *clt;
	काष्ठा rtrs_clt_sess *(*next_path)(काष्ठा path_it *it);
पूर्ण;

/**
 * list_next_or_null_rr_rcu - get next list element in round-robin fashion.
 * @head:	the head क्रम the list.
 * @ptr:        the list head to take the next element from.
 * @type:       the type of the काष्ठा this is embedded in.
 * @memb:       the name of the list_head within the काष्ठा.
 *
 * Next element वापसed in round-robin fashion, i.e. head will be skipped,
 * but अगर list is observed as empty, शून्य will be वापसed.
 *
 * This primitive may safely run concurrently with the _rcu list-mutation
 * primitives such as list_add_rcu() as दीर्घ as it's guarded by rcu_पढ़ो_lock().
 */
#घोषणा list_next_or_null_rr_rcu(head, ptr, type, memb) \
(अणु \
	list_next_or_null_rcu(head, ptr, type, memb) ?: \
		list_next_or_null_rcu(head, READ_ONCE((ptr)->next), \
				      type, memb); \
पूर्ण)

/**
 * get_next_path_rr() - Returns path in round-robin fashion.
 * @it:	the path poपूर्णांकer
 *
 * Related to @MP_POLICY_RR
 *
 * Locks:
 *    rcu_पढ़ो_lock() must be hold.
 */
अटल काष्ठा rtrs_clt_sess *get_next_path_rr(काष्ठा path_it *it)
अणु
	काष्ठा rtrs_clt_sess __rcu **ppcpu_path;
	काष्ठा rtrs_clt_sess *path;
	काष्ठा rtrs_clt *clt;

	clt = it->clt;

	/*
	 * Here we use two RCU objects: @paths_list and @pcpu_path
	 * poपूर्णांकer.  See rtrs_clt_हटाओ_path_from_arr() क्रम details
	 * how that is handled.
	 */

	ppcpu_path = this_cpu_ptr(clt->pcpu_path);
	path = rcu_dereference(*ppcpu_path);
	अगर (unlikely(!path))
		path = list_first_or_null_rcu(&clt->paths_list,
					      typeof(*path), s.entry);
	अन्यथा
		path = list_next_or_null_rr_rcu(&clt->paths_list,
						&path->s.entry,
						typeof(*path),
						s.entry);
	rcu_assign_poपूर्णांकer(*ppcpu_path, path);

	वापस path;
पूर्ण

/**
 * get_next_path_min_inflight() - Returns path with minimal inflight count.
 * @it:	the path poपूर्णांकer
 *
 * Related to @MP_POLICY_MIN_INFLIGHT
 *
 * Locks:
 *    rcu_पढ़ो_lock() must be hold.
 */
अटल काष्ठा rtrs_clt_sess *get_next_path_min_inflight(काष्ठा path_it *it)
अणु
	काष्ठा rtrs_clt_sess *min_path = शून्य;
	काष्ठा rtrs_clt *clt = it->clt;
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक min_inflight = पूर्णांक_उच्च;
	पूर्णांक inflight;

	list_क्रम_each_entry_rcu(sess, &clt->paths_list, s.entry) अणु
		अगर (unlikely(!list_empty(raw_cpu_ptr(sess->mp_skip_entry))))
			जारी;

		inflight = atomic_पढ़ो(&sess->stats->inflight);

		अगर (inflight < min_inflight) अणु
			min_inflight = inflight;
			min_path = sess;
		पूर्ण
	पूर्ण

	/*
	 * add the path to the skip list, so that next समय we can get
	 * a dअगरferent one
	 */
	अगर (min_path)
		list_add(raw_cpu_ptr(min_path->mp_skip_entry), &it->skip_list);

	वापस min_path;
पूर्ण

/**
 * get_next_path_min_latency() - Returns path with minimal latency.
 * @it:	the path poपूर्णांकer
 *
 * Return: a path with the lowest latency or शून्य अगर all paths are tried
 *
 * Locks:
 *    rcu_पढ़ो_lock() must be hold.
 *
 * Related to @MP_POLICY_MIN_LATENCY
 *
 * This DOES skip an alपढ़ोy-tried path.
 * There is a skip-list to skip a path अगर the path has tried but failed.
 * It will try the minimum latency path and then the second minimum latency
 * path and so on. Finally it will वापस शून्य अगर all paths are tried.
 * Thereक्रमe the caller MUST check the वापसed
 * path is शून्य and trigger the IO error.
 */
अटल काष्ठा rtrs_clt_sess *get_next_path_min_latency(काष्ठा path_it *it)
अणु
	काष्ठा rtrs_clt_sess *min_path = शून्य;
	काष्ठा rtrs_clt *clt = it->clt;
	काष्ठा rtrs_clt_sess *sess;
	kसमय_प्रकार min_latency = पूर्णांक_उच्च;
	kसमय_प्रकार latency;

	list_क्रम_each_entry_rcu(sess, &clt->paths_list, s.entry) अणु
		अगर (unlikely(READ_ONCE(sess->state) != RTRS_CLT_CONNECTED))
			जारी;

		अगर (unlikely(!list_empty(raw_cpu_ptr(sess->mp_skip_entry))))
			जारी;

		latency = sess->s.hb_cur_latency;

		अगर (latency < min_latency) अणु
			min_latency = latency;
			min_path = sess;
		पूर्ण
	पूर्ण

	/*
	 * add the path to the skip list, so that next समय we can get
	 * a dअगरferent one
	 */
	अगर (min_path)
		list_add(raw_cpu_ptr(min_path->mp_skip_entry), &it->skip_list);

	वापस min_path;
पूर्ण

अटल अंतरभूत व्योम path_it_init(काष्ठा path_it *it, काष्ठा rtrs_clt *clt)
अणु
	INIT_LIST_HEAD(&it->skip_list);
	it->clt = clt;
	it->i = 0;

	अगर (clt->mp_policy == MP_POLICY_RR)
		it->next_path = get_next_path_rr;
	अन्यथा अगर (clt->mp_policy == MP_POLICY_MIN_INFLIGHT)
		it->next_path = get_next_path_min_inflight;
	अन्यथा
		it->next_path = get_next_path_min_latency;
पूर्ण

अटल अंतरभूत व्योम path_it_deinit(काष्ठा path_it *it)
अणु
	काष्ठा list_head *skip, *पंचांगp;
	/*
	 * The skip_list is used only क्रम the MIN_INFLIGHT policy.
	 * We need to हटाओ paths from it, so that next IO can insert
	 * paths (->mp_skip_entry) पूर्णांकo a skip_list again.
	 */
	list_क्रम_each_safe(skip, पंचांगp, &it->skip_list)
		list_del_init(skip);
पूर्ण

/**
 * rtrs_clt_init_req() Initialize an rtrs_clt_io_req holding inक्रमmation
 * about an inflight IO.
 * The user buffer holding user control message (not data) is copied पूर्णांकo
 * the corresponding buffer of rtrs_iu (req->iu->buf), which later on will
 * also hold the control message of rtrs.
 * @req: an io request holding inक्रमmation about IO.
 * @sess: client session
 * @conf: conक्रमmation callback function to notअगरy upper layer.
 * @permit: permit क्रम allocation of RDMA remote buffer
 * @priv: निजी poपूर्णांकer
 * @vec: kernel vector containing control message
 * @usr_len: length of the user message
 * @sg: scater list क्रम IO data
 * @sg_cnt: number of scater list entries
 * @data_len: length of the IO data
 * @dir: direction of the IO.
 */
अटल व्योम rtrs_clt_init_req(काष्ठा rtrs_clt_io_req *req,
			      काष्ठा rtrs_clt_sess *sess,
			      व्योम (*conf)(व्योम *priv, पूर्णांक त्रुटि_सं),
			      काष्ठा rtrs_permit *permit, व्योम *priv,
			      स्थिर काष्ठा kvec *vec, माप_प्रकार usr_len,
			      काष्ठा scatterlist *sg, माप_प्रकार sg_cnt,
			      माप_प्रकार data_len, पूर्णांक dir)
अणु
	काष्ठा iov_iter iter;
	माप_प्रकार len;

	req->permit = permit;
	req->in_use = true;
	req->usr_len = usr_len;
	req->data_len = data_len;
	req->sglist = sg;
	req->sg_cnt = sg_cnt;
	req->priv = priv;
	req->dir = dir;
	req->con = rtrs_permit_to_clt_con(sess, permit);
	req->conf = conf;
	req->need_inv = false;
	req->need_inv_comp = false;
	req->inv_त्रुटि_सं = 0;

	iov_iter_kvec(&iter, READ, vec, 1, usr_len);
	len = _copy_from_iter(req->iu->buf, usr_len, &iter);
	WARN_ON(len != usr_len);

	reinit_completion(&req->inv_comp);
पूर्ण

अटल काष्ठा rtrs_clt_io_req *
rtrs_clt_get_req(काष्ठा rtrs_clt_sess *sess,
		 व्योम (*conf)(व्योम *priv, पूर्णांक त्रुटि_सं),
		 काष्ठा rtrs_permit *permit, व्योम *priv,
		 स्थिर काष्ठा kvec *vec, माप_प्रकार usr_len,
		 काष्ठा scatterlist *sg, माप_प्रकार sg_cnt,
		 माप_प्रकार data_len, पूर्णांक dir)
अणु
	काष्ठा rtrs_clt_io_req *req;

	req = &sess->reqs[permit->mem_id];
	rtrs_clt_init_req(req, sess, conf, permit, priv, vec, usr_len,
			   sg, sg_cnt, data_len, dir);
	वापस req;
पूर्ण

अटल काष्ठा rtrs_clt_io_req *
rtrs_clt_get_copy_req(काष्ठा rtrs_clt_sess *alive_sess,
		       काष्ठा rtrs_clt_io_req *fail_req)
अणु
	काष्ठा rtrs_clt_io_req *req;
	काष्ठा kvec vec = अणु
		.iov_base = fail_req->iu->buf,
		.iov_len  = fail_req->usr_len
	पूर्ण;

	req = &alive_sess->reqs[fail_req->permit->mem_id];
	rtrs_clt_init_req(req, alive_sess, fail_req->conf, fail_req->permit,
			   fail_req->priv, &vec, fail_req->usr_len,
			   fail_req->sglist, fail_req->sg_cnt,
			   fail_req->data_len, fail_req->dir);
	वापस req;
पूर्ण

अटल पूर्णांक rtrs_post_rdma_ग_लिखो_sg(काष्ठा rtrs_clt_con *con,
				    काष्ठा rtrs_clt_io_req *req,
				    काष्ठा rtrs_rbuf *rbuf,
				    u32 size, u32 imm)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा ib_sge *sge = req->sge;
	क्रमागत ib_send_flags flags;
	काष्ठा scatterlist *sg;
	माप_प्रकार num_sge;
	पूर्णांक i;

	क्रम_each_sg(req->sglist, sg, req->sg_cnt, i) अणु
		sge[i].addr   = sg_dma_address(sg);
		sge[i].length = sg_dma_len(sg);
		sge[i].lkey   = sess->s.dev->ib_pd->local_dma_lkey;
	पूर्ण
	sge[i].addr   = req->iu->dma_addr;
	sge[i].length = size;
	sge[i].lkey   = sess->s.dev->ib_pd->local_dma_lkey;

	num_sge = 1 + req->sg_cnt;

	/*
	 * From समय to समय we have to post संकेतled sends,
	 * or send queue will fill up and only QP reset can help.
	 */
	flags = atomic_inc_वापस(&con->io_cnt) % sess->queue_depth ?
			0 : IB_SEND_SIGNALED;

	ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev, req->iu->dma_addr,
				      size, DMA_TO_DEVICE);

	वापस rtrs_iu_post_rdma_ग_लिखो_imm(&con->c, req->iu, sge, num_sge,
					    rbuf->rkey, rbuf->addr, imm,
					    flags, शून्य);
पूर्ण

अटल पूर्णांक rtrs_clt_ग_लिखो_req(काष्ठा rtrs_clt_io_req *req)
अणु
	काष्ठा rtrs_clt_con *con = req->con;
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(s);
	काष्ठा rtrs_msg_rdma_ग_लिखो *msg;

	काष्ठा rtrs_rbuf *rbuf;
	पूर्णांक ret, count = 0;
	u32 imm, buf_id;

	स्थिर माप_प्रकार tsize = माप(*msg) + req->data_len + req->usr_len;

	अगर (unlikely(tsize > sess->chunk_size)) अणु
		rtrs_wrn(s, "Write request failed, size too big %zu > %d\n",
			  tsize, sess->chunk_size);
		वापस -EMSGSIZE;
	पूर्ण
	अगर (req->sg_cnt) अणु
		count = ib_dma_map_sg(sess->s.dev->ib_dev, req->sglist,
				      req->sg_cnt, req->dir);
		अगर (unlikely(!count)) अणु
			rtrs_wrn(s, "Write request failed, map failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* put rtrs msg after sg and user message */
	msg = req->iu->buf + req->usr_len;
	msg->type = cpu_to_le16(RTRS_MSG_WRITE);
	msg->usr_len = cpu_to_le16(req->usr_len);

	/* rtrs message on server side will be after user data and message */
	imm = req->permit->mem_off + req->data_len + req->usr_len;
	imm = rtrs_to_io_req_imm(imm);
	buf_id = req->permit->mem_id;
	req->sg_size = tsize;
	rbuf = &sess->rbufs[buf_id];

	/*
	 * Update stats now, after request is successfully sent it is not
	 * safe anymore to touch it.
	 */
	rtrs_clt_update_all_stats(req, WRITE);

	ret = rtrs_post_rdma_ग_लिखो_sg(req->con, req, rbuf,
				       req->usr_len + माप(*msg),
				       imm);
	अगर (unlikely(ret)) अणु
		rtrs_err_rl(s,
			    "Write request failed: error=%d path=%s [%s:%u]\n",
			    ret, kobject_name(&sess->kobj), sess->hca_name,
			    sess->hca_port);
		अगर (sess->clt->mp_policy == MP_POLICY_MIN_INFLIGHT)
			atomic_dec(&sess->stats->inflight);
		अगर (req->sg_cnt)
			ib_dma_unmap_sg(sess->s.dev->ib_dev, req->sglist,
					req->sg_cnt, req->dir);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtrs_map_sg_fr(काष्ठा rtrs_clt_io_req *req, माप_प्रकार count)
अणु
	पूर्णांक nr;

	/* Align the MR to a 4K page size to match the block virt boundary */
	nr = ib_map_mr_sg(req->mr, req->sglist, count, शून्य, SZ_4K);
	अगर (nr < 0)
		वापस nr;
	अगर (unlikely(nr < req->sg_cnt))
		वापस -EINVAL;
	ib_update_fast_reg_key(req->mr, ib_inc_rkey(req->mr->rkey));

	वापस nr;
पूर्ण

अटल पूर्णांक rtrs_clt_पढ़ो_req(काष्ठा rtrs_clt_io_req *req)
अणु
	काष्ठा rtrs_clt_con *con = req->con;
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(s);
	काष्ठा rtrs_msg_rdma_पढ़ो *msg;
	काष्ठा rtrs_ib_dev *dev = sess->s.dev;

	काष्ठा ib_reg_wr rwr;
	काष्ठा ib_send_wr *wr = शून्य;

	पूर्णांक ret, count = 0;
	u32 imm, buf_id;

	स्थिर माप_प्रकार tsize = माप(*msg) + req->data_len + req->usr_len;

	अगर (unlikely(tsize > sess->chunk_size)) अणु
		rtrs_wrn(s,
			  "Read request failed, message size is %zu, bigger than CHUNK_SIZE %d\n",
			  tsize, sess->chunk_size);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (req->sg_cnt) अणु
		count = ib_dma_map_sg(dev->ib_dev, req->sglist, req->sg_cnt,
				      req->dir);
		अगर (unlikely(!count)) अणु
			rtrs_wrn(s,
				  "Read request failed, dma map failed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* put our message पूर्णांकo req->buf after user message*/
	msg = req->iu->buf + req->usr_len;
	msg->type = cpu_to_le16(RTRS_MSG_READ);
	msg->usr_len = cpu_to_le16(req->usr_len);

	अगर (count) अणु
		ret = rtrs_map_sg_fr(req, count);
		अगर (ret < 0) अणु
			rtrs_err_rl(s,
				     "Read request failed, failed to map  fast reg. data, err: %d\n",
				     ret);
			ib_dma_unmap_sg(dev->ib_dev, req->sglist, req->sg_cnt,
					req->dir);
			वापस ret;
		पूर्ण
		rwr = (काष्ठा ib_reg_wr) अणु
			.wr.opcode = IB_WR_REG_MR,
			.wr.wr_cqe = &fast_reg_cqe,
			.mr = req->mr,
			.key = req->mr->rkey,
			.access = (IB_ACCESS_LOCAL_WRITE |
				   IB_ACCESS_REMOTE_WRITE),
		पूर्ण;
		wr = &rwr.wr;

		msg->sg_cnt = cpu_to_le16(1);
		msg->flags = cpu_to_le16(RTRS_MSG_NEED_INVAL_F);

		msg->desc[0].addr = cpu_to_le64(req->mr->iova);
		msg->desc[0].key = cpu_to_le32(req->mr->rkey);
		msg->desc[0].len = cpu_to_le32(req->mr->length);

		/* Further invalidation is required */
		req->need_inv = !!RTRS_MSG_NEED_INVAL_F;

	पूर्ण अन्यथा अणु
		msg->sg_cnt = 0;
		msg->flags = 0;
	पूर्ण
	/*
	 * rtrs message will be after the space reserved क्रम disk data and
	 * user message
	 */
	imm = req->permit->mem_off + req->data_len + req->usr_len;
	imm = rtrs_to_io_req_imm(imm);
	buf_id = req->permit->mem_id;

	req->sg_size  = माप(*msg);
	req->sg_size += le16_to_cpu(msg->sg_cnt) * माप(काष्ठा rtrs_sg_desc);
	req->sg_size += req->usr_len;

	/*
	 * Update stats now, after request is successfully sent it is not
	 * safe anymore to touch it.
	 */
	rtrs_clt_update_all_stats(req, READ);

	ret = rtrs_post_send_rdma(req->con, req, &sess->rbufs[buf_id],
				   req->data_len, imm, wr);
	अगर (unlikely(ret)) अणु
		rtrs_err_rl(s,
			    "Read request failed: error=%d path=%s [%s:%u]\n",
			    ret, kobject_name(&sess->kobj), sess->hca_name,
			    sess->hca_port);
		अगर (sess->clt->mp_policy == MP_POLICY_MIN_INFLIGHT)
			atomic_dec(&sess->stats->inflight);
		req->need_inv = false;
		अगर (req->sg_cnt)
			ib_dma_unmap_sg(dev->ib_dev, req->sglist,
					req->sg_cnt, req->dir);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * rtrs_clt_failover_req() Try to find an active path क्रम a failed request
 * @clt: clt context
 * @fail_req: a failed io request.
 */
अटल पूर्णांक rtrs_clt_failover_req(काष्ठा rtrs_clt *clt,
				 काष्ठा rtrs_clt_io_req *fail_req)
अणु
	काष्ठा rtrs_clt_sess *alive_sess;
	काष्ठा rtrs_clt_io_req *req;
	पूर्णांक err = -ECONNABORTED;
	काष्ठा path_it it;

	rcu_पढ़ो_lock();
	क्रम (path_it_init(&it, clt);
	     (alive_sess = it.next_path(&it)) && it.i < it.clt->paths_num;
	     it.i++) अणु
		अगर (unlikely(READ_ONCE(alive_sess->state) !=
			     RTRS_CLT_CONNECTED))
			जारी;
		req = rtrs_clt_get_copy_req(alive_sess, fail_req);
		अगर (req->dir == DMA_TO_DEVICE)
			err = rtrs_clt_ग_लिखो_req(req);
		अन्यथा
			err = rtrs_clt_पढ़ो_req(req);
		अगर (unlikely(err)) अणु
			req->in_use = false;
			जारी;
		पूर्ण
		/* Success path */
		rtrs_clt_inc_failover_cnt(alive_sess->stats);
		अवरोध;
	पूर्ण
	path_it_deinit(&it);
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल व्योम fail_all_outstanding_reqs(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt *clt = sess->clt;
	काष्ठा rtrs_clt_io_req *req;
	पूर्णांक i, err;

	अगर (!sess->reqs)
		वापस;
	क्रम (i = 0; i < sess->queue_depth; ++i) अणु
		req = &sess->reqs[i];
		अगर (!req->in_use)
			जारी;

		/*
		 * Safely (without notअगरication) complete failed request.
		 * After completion this request is still useble and can
		 * be failovered to another path.
		 */
		complete_rdma_req(req, -ECONNABORTED, false, true);

		err = rtrs_clt_failover_req(clt, req);
		अगर (unlikely(err))
			/* Failover failed, notअगरy anyway */
			req->conf(req->priv, err);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_sess_reqs(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt_io_req *req;
	पूर्णांक i;

	अगर (!sess->reqs)
		वापस;
	क्रम (i = 0; i < sess->queue_depth; ++i) अणु
		req = &sess->reqs[i];
		अगर (req->mr)
			ib_dereg_mr(req->mr);
		kमुक्त(req->sge);
		rtrs_iu_मुक्त(req->iu, sess->s.dev->ib_dev, 1);
	पूर्ण
	kमुक्त(sess->reqs);
	sess->reqs = शून्य;
पूर्ण

अटल पूर्णांक alloc_sess_reqs(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt_io_req *req;
	काष्ठा rtrs_clt *clt = sess->clt;
	पूर्णांक i, err = -ENOMEM;

	sess->reqs = kसुस्मृति(sess->queue_depth, माप(*sess->reqs),
			     GFP_KERNEL);
	अगर (!sess->reqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < sess->queue_depth; ++i) अणु
		req = &sess->reqs[i];
		req->iu = rtrs_iu_alloc(1, sess->max_hdr_size, GFP_KERNEL,
					 sess->s.dev->ib_dev,
					 DMA_TO_DEVICE,
					 rtrs_clt_rdma_करोne);
		अगर (!req->iu)
			जाओ out;

		req->sge = kदो_स्मृति_array(clt->max_segments + 1,
					 माप(*req->sge), GFP_KERNEL);
		अगर (!req->sge)
			जाओ out;

		req->mr = ib_alloc_mr(sess->s.dev->ib_pd, IB_MR_TYPE_MEM_REG,
				      sess->max_pages_per_mr);
		अगर (IS_ERR(req->mr)) अणु
			err = PTR_ERR(req->mr);
			req->mr = शून्य;
			pr_err("Failed to alloc sess->max_pages_per_mr %d\n",
			       sess->max_pages_per_mr);
			जाओ out;
		पूर्ण

		init_completion(&req->inv_comp);
	पूर्ण

	वापस 0;

out:
	मुक्त_sess_reqs(sess);

	वापस err;
पूर्ण

अटल पूर्णांक alloc_permits(काष्ठा rtrs_clt *clt)
अणु
	अचिन्हित पूर्णांक chunk_bits;
	पूर्णांक err, i;

	clt->permits_map = kसुस्मृति(BITS_TO_LONGS(clt->queue_depth),
				   माप(दीर्घ), GFP_KERNEL);
	अगर (!clt->permits_map) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	clt->permits = kसुस्मृति(clt->queue_depth, permit_size(clt), GFP_KERNEL);
	अगर (!clt->permits) अणु
		err = -ENOMEM;
		जाओ err_map;
	पूर्ण
	chunk_bits = ilog2(clt->queue_depth - 1) + 1;
	क्रम (i = 0; i < clt->queue_depth; i++) अणु
		काष्ठा rtrs_permit *permit;

		permit = get_permit(clt, i);
		permit->mem_id = i;
		permit->mem_off = i << (MAX_IMM_PAYL_BITS - chunk_bits);
	पूर्ण

	वापस 0;

err_map:
	kमुक्त(clt->permits_map);
	clt->permits_map = शून्य;
out_err:
	वापस err;
पूर्ण

अटल व्योम मुक्त_permits(काष्ठा rtrs_clt *clt)
अणु
	अगर (clt->permits_map) अणु
		माप_प्रकार sz = clt->queue_depth;

		रुको_event(clt->permits_रुको,
			   find_first_bit(clt->permits_map, sz) >= sz);
	पूर्ण
	kमुक्त(clt->permits_map);
	clt->permits_map = शून्य;
	kमुक्त(clt->permits);
	clt->permits = शून्य;
पूर्ण

अटल व्योम query_fast_reg_mode(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा ib_device *ib_dev;
	u64 max_pages_per_mr;
	पूर्णांक mr_page_shअगरt;

	ib_dev = sess->s.dev->ib_dev;

	/*
	 * Use the smallest page size supported by the HCA, करोwn to a
	 * minimum of 4096 bytes. We're unlikely to build large sglists
	 * out of smaller entries.
	 */
	mr_page_shअगरt      = max(12, ffs(ib_dev->attrs.page_size_cap) - 1);
	max_pages_per_mr   = ib_dev->attrs.max_mr_size;
	करो_भाग(max_pages_per_mr, (1ull << mr_page_shअगरt));
	sess->max_pages_per_mr =
		min3(sess->max_pages_per_mr, (u32)max_pages_per_mr,
		     ib_dev->attrs.max_fast_reg_page_list_len);
	sess->max_send_sge = ib_dev->attrs.max_send_sge;
पूर्ण

अटल bool rtrs_clt_change_state_get_old(काष्ठा rtrs_clt_sess *sess,
					   क्रमागत rtrs_clt_state new_state,
					   क्रमागत rtrs_clt_state *old_state)
अणु
	bool changed;

	spin_lock_irq(&sess->state_wq.lock);
	अगर (old_state)
		*old_state = sess->state;
	changed = rtrs_clt_change_state(sess, new_state);
	spin_unlock_irq(&sess->state_wq.lock);

	वापस changed;
पूर्ण

अटल व्योम rtrs_clt_hb_err_handler(काष्ठा rtrs_con *c)
अणु
	काष्ठा rtrs_clt_con *con = container_of(c, typeof(*con), c);

	rtrs_rdma_error_recovery(con);
पूर्ण

अटल व्योम rtrs_clt_init_hb(काष्ठा rtrs_clt_sess *sess)
अणु
	rtrs_init_hb(&sess->s, &io_comp_cqe,
		      RTRS_HB_INTERVAL_MS,
		      RTRS_HB_MISSED_MAX,
		      rtrs_clt_hb_err_handler,
		      rtrs_wq);
पूर्ण

अटल व्योम rtrs_clt_start_hb(काष्ठा rtrs_clt_sess *sess)
अणु
	rtrs_start_hb(&sess->s);
पूर्ण

अटल व्योम rtrs_clt_stop_hb(काष्ठा rtrs_clt_sess *sess)
अणु
	rtrs_stop_hb(&sess->s);
पूर्ण

अटल व्योम rtrs_clt_reconnect_work(काष्ठा work_काष्ठा *work);
अटल व्योम rtrs_clt_बंद_work(काष्ठा work_काष्ठा *work);

अटल काष्ठा rtrs_clt_sess *alloc_sess(काष्ठा rtrs_clt *clt,
					 स्थिर काष्ठा rtrs_addr *path,
					 माप_प्रकार con_num, u16 max_segments,
					 u32 nr_poll_queues)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक err = -ENOMEM;
	पूर्णांक cpu;
	माप_प्रकार total_con;

	sess = kzalloc(माप(*sess), GFP_KERNEL);
	अगर (!sess)
		जाओ err;

	/*
	 * irqmode and poll
	 * +1: Extra connection क्रम user messages
	 */
	total_con = con_num + nr_poll_queues + 1;
	sess->s.con = kसुस्मृति(total_con, माप(*sess->s.con), GFP_KERNEL);
	अगर (!sess->s.con)
		जाओ err_मुक्त_sess;

	sess->s.con_num = total_con;
	sess->s.irq_con_num = con_num + 1;

	sess->stats = kzalloc(माप(*sess->stats), GFP_KERNEL);
	अगर (!sess->stats)
		जाओ err_मुक्त_con;

	mutex_init(&sess->init_mutex);
	uuid_gen(&sess->s.uuid);
	स_नकल(&sess->s.dst_addr, path->dst,
	       rdma_addr_size((काष्ठा sockaddr *)path->dst));

	/*
	 * rdma_resolve_addr() passes src_addr to cma_bind_addr, which
	 * checks the sa_family to be non-zero. If user passed src_addr=शून्य
	 * the sess->src_addr will contain only zeros, which is then fine.
	 */
	अगर (path->src)
		स_नकल(&sess->s.src_addr, path->src,
		       rdma_addr_size((काष्ठा sockaddr *)path->src));
	strlcpy(sess->s.sessname, clt->sessname, माप(sess->s.sessname));
	sess->clt = clt;
	sess->max_pages_per_mr = max_segments;
	init_रुकोqueue_head(&sess->state_wq);
	sess->state = RTRS_CLT_CONNECTING;
	atomic_set(&sess->connected_cnt, 0);
	INIT_WORK(&sess->बंद_work, rtrs_clt_बंद_work);
	INIT_DELAYED_WORK(&sess->reconnect_dwork, rtrs_clt_reconnect_work);
	rtrs_clt_init_hb(sess);

	sess->mp_skip_entry = alloc_percpu(typeof(*sess->mp_skip_entry));
	अगर (!sess->mp_skip_entry)
		जाओ err_मुक्त_stats;

	क्रम_each_possible_cpu(cpu)
		INIT_LIST_HEAD(per_cpu_ptr(sess->mp_skip_entry, cpu));

	err = rtrs_clt_init_stats(sess->stats);
	अगर (err)
		जाओ err_मुक्त_percpu;

	वापस sess;

err_मुक्त_percpu:
	मुक्त_percpu(sess->mp_skip_entry);
err_मुक्त_stats:
	kमुक्त(sess->stats);
err_मुक्त_con:
	kमुक्त(sess->s.con);
err_मुक्त_sess:
	kमुक्त(sess);
err:
	वापस ERR_PTR(err);
पूर्ण

व्योम मुक्त_sess(काष्ठा rtrs_clt_sess *sess)
अणु
	मुक्त_percpu(sess->mp_skip_entry);
	mutex_destroy(&sess->init_mutex);
	kमुक्त(sess->s.con);
	kमुक्त(sess->rbufs);
	kमुक्त(sess);
पूर्ण

अटल पूर्णांक create_con(काष्ठा rtrs_clt_sess *sess, अचिन्हित पूर्णांक cid)
अणु
	काष्ठा rtrs_clt_con *con;

	con = kzalloc(माप(*con), GFP_KERNEL);
	अगर (!con)
		वापस -ENOMEM;

	/* Map first two connections to the first CPU */
	con->cpu  = (cid ? cid - 1 : 0) % nr_cpu_ids;
	con->c.cid = cid;
	con->c.sess = &sess->s;
	atomic_set(&con->io_cnt, 0);
	mutex_init(&con->con_mutex);

	sess->s.con[cid] = &con->c;

	वापस 0;
पूर्ण

अटल व्योम destroy_con(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);

	sess->s.con[con->c.cid] = शून्य;
	mutex_destroy(&con->con_mutex);
	kमुक्त(con);
पूर्ण

अटल पूर्णांक create_con_cq_qp(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	u32 max_send_wr, max_recv_wr, cq_size;
	पूर्णांक err, cq_vector;
	काष्ठा rtrs_msg_rkey_rsp *rsp;

	lockdep_निश्चित_held(&con->con_mutex);
	अगर (con->c.cid == 0) अणु
		/*
		 * One completion क्रम each receive and two क्रम each send
		 * (send request + registration)
		 * + 2 क्रम drain and heartbeat
		 * in हाल qp माला_लो पूर्णांकo error state
		 */
		max_send_wr = SERVICE_CON_QUEUE_DEPTH * 2 + 2;
		max_recv_wr = SERVICE_CON_QUEUE_DEPTH * 2 + 2;
		/* We must be the first here */
		अगर (WARN_ON(sess->s.dev))
			वापस -EINVAL;

		/*
		 * The whole session uses device from user connection.
		 * Be careful not to बंद user connection beक्रमe ib dev
		 * is gracefully put.
		 */
		sess->s.dev = rtrs_ib_dev_find_or_add(con->c.cm_id->device,
						       &dev_pd);
		अगर (!sess->s.dev) अणु
			rtrs_wrn(sess->clt,
				  "rtrs_ib_dev_find_get_or_add(): no memory\n");
			वापस -ENOMEM;
		पूर्ण
		sess->s.dev_ref = 1;
		query_fast_reg_mode(sess);
	पूर्ण अन्यथा अणु
		/*
		 * Here we assume that session members are correctly set.
		 * This is always true अगर user connection (cid == 0) is
		 * established first.
		 */
		अगर (WARN_ON(!sess->s.dev))
			वापस -EINVAL;
		अगर (WARN_ON(!sess->queue_depth))
			वापस -EINVAL;

		/* Shared between connections */
		sess->s.dev_ref++;
		max_send_wr =
			min_t(पूर्णांक, sess->s.dev->ib_dev->attrs.max_qp_wr,
			      /* QD * (REQ + RSP + FR REGS or INVS) + drain */
			      sess->queue_depth * 3 + 1);
		max_recv_wr =
			min_t(पूर्णांक, sess->s.dev->ib_dev->attrs.max_qp_wr,
			      sess->queue_depth * 3 + 1);
	पूर्ण
	/* alloc iu to recv new rkey reply when server reports flags set */
	अगर (sess->flags & RTRS_MSG_NEW_RKEY_F || con->c.cid == 0) अणु
		con->rsp_ius = rtrs_iu_alloc(max_recv_wr, माप(*rsp),
					      GFP_KERNEL, sess->s.dev->ib_dev,
					      DMA_FROM_DEVICE,
					      rtrs_clt_rdma_करोne);
		अगर (!con->rsp_ius)
			वापस -ENOMEM;
		con->queue_size = max_recv_wr;
	पूर्ण
	cq_size = max_send_wr + max_recv_wr;
	cq_vector = con->cpu % sess->s.dev->ib_dev->num_comp_vectors;
	अगर (con->c.cid >= sess->s.irq_con_num)
		err = rtrs_cq_qp_create(&sess->s, &con->c, sess->max_send_sge,
					cq_vector, cq_size, max_send_wr,
					max_recv_wr, IB_POLL_सूचीECT);
	अन्यथा
		err = rtrs_cq_qp_create(&sess->s, &con->c, sess->max_send_sge,
					cq_vector, cq_size, max_send_wr,
					max_recv_wr, IB_POLL_SOFTIRQ);
	/*
	 * In हाल of error we करो not bother to clean previous allocations,
	 * since destroy_con_cq_qp() must be called.
	 */
	वापस err;
पूर्ण

अटल व्योम destroy_con_cq_qp(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);

	/*
	 * Be careful here: destroy_con_cq_qp() can be called even
	 * create_con_cq_qp() failed, see comments there.
	 */
	lockdep_निश्चित_held(&con->con_mutex);
	rtrs_cq_qp_destroy(&con->c);
	अगर (con->rsp_ius) अणु
		rtrs_iu_मुक्त(con->rsp_ius, sess->s.dev->ib_dev, con->queue_size);
		con->rsp_ius = शून्य;
		con->queue_size = 0;
	पूर्ण
	अगर (sess->s.dev_ref && !--sess->s.dev_ref) अणु
		rtrs_ib_dev_put(sess->s.dev);
		sess->s.dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम stop_cm(काष्ठा rtrs_clt_con *con)
अणु
	rdma_disconnect(con->c.cm_id);
	अगर (con->c.qp)
		ib_drain_qp(con->c.qp);
पूर्ण

अटल व्योम destroy_cm(काष्ठा rtrs_clt_con *con)
अणु
	rdma_destroy_id(con->c.cm_id);
	con->c.cm_id = शून्य;
पूर्ण

अटल पूर्णांक rtrs_rdma_addr_resolved(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	पूर्णांक err;

	mutex_lock(&con->con_mutex);
	err = create_con_cq_qp(con);
	mutex_unlock(&con->con_mutex);
	अगर (err) अणु
		rtrs_err(s, "create_con_cq_qp(), err: %d\n", err);
		वापस err;
	पूर्ण
	err = rdma_resolve_route(con->c.cm_id, RTRS_CONNECT_TIMEOUT_MS);
	अगर (err)
		rtrs_err(s, "Resolving route failed, err: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक rtrs_rdma_route_resolved(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_clt *clt = sess->clt;
	काष्ठा rtrs_msg_conn_req msg;
	काष्ठा rdma_conn_param param;

	पूर्णांक err;

	param = (काष्ठा rdma_conn_param) अणु
		.retry_count = 7,
		.rnr_retry_count = 7,
		.निजी_data = &msg,
		.निजी_data_len = माप(msg),
	पूर्ण;

	msg = (काष्ठा rtrs_msg_conn_req) अणु
		.magic = cpu_to_le16(RTRS_MAGIC),
		.version = cpu_to_le16(RTRS_PROTO_VER),
		.cid = cpu_to_le16(con->c.cid),
		.cid_num = cpu_to_le16(sess->s.con_num),
		.recon_cnt = cpu_to_le16(sess->s.recon_cnt),
	पूर्ण;
	msg.first_conn = sess->क्रम_new_clt ? FIRST_CONN : 0;
	uuid_copy(&msg.sess_uuid, &sess->s.uuid);
	uuid_copy(&msg.paths_uuid, &clt->paths_uuid);

	err = rdma_connect_locked(con->c.cm_id, &param);
	अगर (err)
		rtrs_err(clt, "rdma_connect_locked(): %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक rtrs_rdma_conn_established(काष्ठा rtrs_clt_con *con,
				       काष्ठा rdma_cm_event *ev)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_clt *clt = sess->clt;
	स्थिर काष्ठा rtrs_msg_conn_rsp *msg;
	u16 version, queue_depth;
	पूर्णांक त्रुटि_सं;
	u8 len;

	msg = ev->param.conn.निजी_data;
	len = ev->param.conn.निजी_data_len;
	अगर (len < माप(*msg)) अणु
		rtrs_err(clt, "Invalid RTRS connection response\n");
		वापस -ECONNRESET;
	पूर्ण
	अगर (le16_to_cpu(msg->magic) != RTRS_MAGIC) अणु
		rtrs_err(clt, "Invalid RTRS magic\n");
		वापस -ECONNRESET;
	पूर्ण
	version = le16_to_cpu(msg->version);
	अगर (version >> 8 != RTRS_PROTO_VER_MAJOR) अणु
		rtrs_err(clt, "Unsupported major RTRS version: %d, expected %d\n",
			  version >> 8, RTRS_PROTO_VER_MAJOR);
		वापस -ECONNRESET;
	पूर्ण
	त्रुटि_सं = le16_to_cpu(msg->त्रुटि_सं);
	अगर (त्रुटि_सं) अणु
		rtrs_err(clt, "Invalid RTRS message: errno %d\n",
			  त्रुटि_सं);
		वापस -ECONNRESET;
	पूर्ण
	अगर (con->c.cid == 0) अणु
		queue_depth = le16_to_cpu(msg->queue_depth);

		अगर (queue_depth > MAX_SESS_QUEUE_DEPTH) अणु
			rtrs_err(clt, "Invalid RTRS message: queue=%d\n",
				  queue_depth);
			वापस -ECONNRESET;
		पूर्ण
		अगर (!sess->rbufs || sess->queue_depth < queue_depth) अणु
			kमुक्त(sess->rbufs);
			sess->rbufs = kसुस्मृति(queue_depth, माप(*sess->rbufs),
					      GFP_KERNEL);
			अगर (!sess->rbufs)
				वापस -ENOMEM;
		पूर्ण
		sess->queue_depth = queue_depth;
		sess->max_hdr_size = le32_to_cpu(msg->max_hdr_size);
		sess->max_io_size = le32_to_cpu(msg->max_io_size);
		sess->flags = le32_to_cpu(msg->flags);
		sess->chunk_size = sess->max_io_size + sess->max_hdr_size;

		/*
		 * Global queue depth and IO size is always a minimum.
		 * If जबतक a reconnection server sends us a value a bit
		 * higher - client करोes not care and uses cached minimum.
		 *
		 * Since we can have several sessions (paths) restablishing
		 * connections in parallel, use lock.
		 */
		mutex_lock(&clt->paths_mutex);
		clt->queue_depth = min_not_zero(sess->queue_depth,
						clt->queue_depth);
		clt->max_io_size = min_not_zero(sess->max_io_size,
						clt->max_io_size);
		mutex_unlock(&clt->paths_mutex);

		/*
		 * Cache the hca_port and hca_name क्रम sysfs
		 */
		sess->hca_port = con->c.cm_id->port_num;
		scnम_लिखो(sess->hca_name, माप(sess->hca_name),
			  sess->s.dev->ib_dev->name);
		sess->s.src_addr = con->c.cm_id->route.addr.src_addr;
		/* set क्रम_new_clt, to allow future reconnect on any path */
		sess->क्रम_new_clt = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम flag_success_on_conn(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);

	atomic_inc(&sess->connected_cnt);
	con->cm_err = 1;
पूर्ण

अटल पूर्णांक rtrs_rdma_conn_rejected(काष्ठा rtrs_clt_con *con,
				    काष्ठा rdma_cm_event *ev)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	स्थिर काष्ठा rtrs_msg_conn_rsp *msg;
	स्थिर अक्षर *rej_msg;
	पूर्णांक status, त्रुटि_सं;
	u8 data_len;

	status = ev->status;
	rej_msg = rdma_reject_msg(con->c.cm_id, status);
	msg = rdma_consumer_reject_data(con->c.cm_id, ev, &data_len);

	अगर (msg && data_len >= माप(*msg)) अणु
		त्रुटि_सं = (पूर्णांक16_t)le16_to_cpu(msg->त्रुटि_सं);
		अगर (त्रुटि_सं == -EBUSY)
			rtrs_err(s,
				  "Previous session is still exists on the server, please reconnect later\n");
		अन्यथा
			rtrs_err(s,
				  "Connect rejected: status %d (%s), rtrs errno %d\n",
				  status, rej_msg, त्रुटि_सं);
	पूर्ण अन्यथा अणु
		rtrs_err(s,
			  "Connect rejected but with malformed message: status %d (%s)\n",
			  status, rej_msg);
	पूर्ण

	वापस -ECONNRESET;
पूर्ण

अटल व्योम rtrs_clt_बंद_conns(काष्ठा rtrs_clt_sess *sess, bool रुको)
अणु
	अगर (rtrs_clt_change_state_get_old(sess, RTRS_CLT_CLOSING, शून्य))
		queue_work(rtrs_wq, &sess->बंद_work);
	अगर (रुको)
		flush_work(&sess->बंद_work);
पूर्ण

अटल अंतरभूत व्योम flag_error_on_conn(काष्ठा rtrs_clt_con *con, पूर्णांक cm_err)
अणु
	अगर (con->cm_err == 1) अणु
		काष्ठा rtrs_clt_sess *sess;

		sess = to_clt_sess(con->c.sess);
		अगर (atomic_dec_and_test(&sess->connected_cnt))

			wake_up(&sess->state_wq);
	पूर्ण
	con->cm_err = cm_err;
पूर्ण

अटल पूर्णांक rtrs_clt_rdma_cm_handler(काष्ठा rdma_cm_id *cm_id,
				     काष्ठा rdma_cm_event *ev)
अणु
	काष्ठा rtrs_clt_con *con = cm_id->context;
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(s);
	पूर्णांक cm_err = 0;

	चयन (ev->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
		cm_err = rtrs_rdma_addr_resolved(con);
		अवरोध;
	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		cm_err = rtrs_rdma_route_resolved(con);
		अवरोध;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		cm_err = rtrs_rdma_conn_established(con, ev);
		अगर (likely(!cm_err)) अणु
			/*
			 * Report success and wake up. Here we abuse state_wq,
			 * i.e. wake up without state change, but we set cm_err.
			 */
			flag_success_on_conn(con);
			wake_up(&sess->state_wq);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल RDMA_CM_EVENT_REJECTED:
		cm_err = rtrs_rdma_conn_rejected(con, ev);
		अवरोध;
	हाल RDMA_CM_EVENT_DISCONNECTED:
		/* No message क्रम disconnecting */
		cm_err = -ECONNRESET;
		अवरोध;
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		rtrs_wrn(s, "CM error (CM event: %s, err: %d)\n",
			 rdma_event_msg(ev->event), ev->status);
		cm_err = -ECONNRESET;
		अवरोध;
	हाल RDMA_CM_EVENT_ADDR_ERROR:
	हाल RDMA_CM_EVENT_ROUTE_ERROR:
		rtrs_wrn(s, "CM error (CM event: %s, err: %d)\n",
			 rdma_event_msg(ev->event), ev->status);
		cm_err = -EHOSTUNREACH;
		अवरोध;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		/*
		 * Device removal is a special हाल.  Queue बंद and वापस 0.
		 */
		rtrs_clt_बंद_conns(sess, false);
		वापस 0;
	शेष:
		rtrs_err(s, "Unexpected RDMA CM error (CM event: %s, err: %d)\n",
			 rdma_event_msg(ev->event), ev->status);
		cm_err = -ECONNRESET;
		अवरोध;
	पूर्ण

	अगर (cm_err) अणु
		/*
		 * cm error makes sense only on connection establishing,
		 * in other हालs we rely on normal procedure of reconnecting.
		 */
		flag_error_on_conn(con, cm_err);
		rtrs_rdma_error_recovery(con);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_cm(काष्ठा rtrs_clt_con *con)
अणु
	काष्ठा rtrs_sess *s = con->c.sess;
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(s);
	काष्ठा rdma_cm_id *cm_id;
	पूर्णांक err;

	cm_id = rdma_create_id(&init_net, rtrs_clt_rdma_cm_handler, con,
			       sess->s.dst_addr.ss_family == AF_IB ?
			       RDMA_PS_IB : RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(cm_id)) अणु
		err = PTR_ERR(cm_id);
		rtrs_err(s, "Failed to create CM ID, err: %d\n", err);

		वापस err;
	पूर्ण
	con->c.cm_id = cm_id;
	con->cm_err = 0;
	/* allow the port to be reused */
	err = rdma_set_reuseaddr(cm_id, 1);
	अगर (err != 0) अणु
		rtrs_err(s, "Set address reuse failed, err: %d\n", err);
		जाओ destroy_cm;
	पूर्ण
	err = rdma_resolve_addr(cm_id, (काष्ठा sockaddr *)&sess->s.src_addr,
				(काष्ठा sockaddr *)&sess->s.dst_addr,
				RTRS_CONNECT_TIMEOUT_MS);
	अगर (err) अणु
		rtrs_err(s, "Failed to resolve address, err: %d\n", err);
		जाओ destroy_cm;
	पूर्ण
	/*
	 * Combine connection status and session events. This is needed
	 * क्रम रुकोing two possible हालs: cm_err has something meaningful
	 * or session state was really changed to error by device removal.
	 */
	err = रुको_event_पूर्णांकerruptible_समयout(
			sess->state_wq,
			con->cm_err || sess->state != RTRS_CLT_CONNECTING,
			msecs_to_jअगरfies(RTRS_CONNECT_TIMEOUT_MS));
	अगर (err == 0 || err == -ERESTARTSYS) अणु
		अगर (err == 0)
			err = -ETIMEDOUT;
		/* Timeकरोut or पूर्णांकerrupted */
		जाओ errr;
	पूर्ण
	अगर (con->cm_err < 0) अणु
		err = con->cm_err;
		जाओ errr;
	पूर्ण
	अगर (READ_ONCE(sess->state) != RTRS_CLT_CONNECTING) अणु
		/* Device removal */
		err = -ECONNABORTED;
		जाओ errr;
	पूर्ण

	वापस 0;

errr:
	stop_cm(con);
	mutex_lock(&con->con_mutex);
	destroy_con_cq_qp(con);
	mutex_unlock(&con->con_mutex);
destroy_cm:
	destroy_cm(con);

	वापस err;
पूर्ण

अटल व्योम rtrs_clt_sess_up(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt *clt = sess->clt;
	पूर्णांक up;

	/*
	 * We can fire RECONNECTED event only when all paths were
	 * connected on rtrs_clt_खोलो(), then each was disconnected
	 * and the first one connected again.  That's why this nasty
	 * game with counter value.
	 */

	mutex_lock(&clt->paths_ev_mutex);
	up = ++clt->paths_up;
	/*
	 * Here it is safe to access paths num directly since up counter
	 * is greater than MAX_PATHS_NUM only जबतक rtrs_clt_खोलो() is
	 * in progress, thus paths removals are impossible.
	 */
	अगर (up > MAX_PATHS_NUM && up == MAX_PATHS_NUM + clt->paths_num)
		clt->paths_up = clt->paths_num;
	अन्यथा अगर (up == 1)
		clt->link_ev(clt->priv, RTRS_CLT_LINK_EV_RECONNECTED);
	mutex_unlock(&clt->paths_ev_mutex);

	/* Mark session as established */
	sess->established = true;
	sess->reconnect_attempts = 0;
	sess->stats->reconnects.successful_cnt++;
पूर्ण

अटल व्योम rtrs_clt_sess_करोwn(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt *clt = sess->clt;

	अगर (!sess->established)
		वापस;

	sess->established = false;
	mutex_lock(&clt->paths_ev_mutex);
	WARN_ON(!clt->paths_up);
	अगर (--clt->paths_up == 0)
		clt->link_ev(clt->priv, RTRS_CLT_LINK_EV_DISCONNECTED);
	mutex_unlock(&clt->paths_ev_mutex);
पूर्ण

अटल व्योम rtrs_clt_stop_and_destroy_conns(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt_con *con;
	अचिन्हित पूर्णांक cid;

	WARN_ON(READ_ONCE(sess->state) == RTRS_CLT_CONNECTED);

	/*
	 * Possible race with rtrs_clt_खोलो(), when DEVICE_REMOVAL comes
	 * exactly in between.  Start destroying after it finishes.
	 */
	mutex_lock(&sess->init_mutex);
	mutex_unlock(&sess->init_mutex);

	/*
	 * All IO paths must observe !CONNECTED state beक्रमe we
	 * मुक्त everything.
	 */
	synchronize_rcu();

	rtrs_clt_stop_hb(sess);

	/*
	 * The order it utterly crucial: firstly disconnect and complete all
	 * rdma requests with error (thus set in_use=false क्रम requests),
	 * then fail outstanding requests checking in_use क्रम each, and
	 * eventually notअगरy upper layer about session disconnection.
	 */

	क्रम (cid = 0; cid < sess->s.con_num; cid++) अणु
		अगर (!sess->s.con[cid])
			अवरोध;
		con = to_clt_con(sess->s.con[cid]);
		stop_cm(con);
	पूर्ण
	fail_all_outstanding_reqs(sess);
	मुक्त_sess_reqs(sess);
	rtrs_clt_sess_करोwn(sess);

	/*
	 * Wait क्रम graceful shutकरोwn, namely when peer side invokes
	 * rdma_disconnect(). 'connected_cnt' is decremented only on
	 * CM events, thus अगर other side had crashed and hb has detected
	 * something is wrong, here we will stuck क्रम exactly समयout ms,
	 * since CM करोes not fire anything.  That is fine, we are not in
	 * hurry.
	 */
	रुको_event_समयout(sess->state_wq, !atomic_पढ़ो(&sess->connected_cnt),
			   msecs_to_jअगरfies(RTRS_CONNECT_TIMEOUT_MS));

	क्रम (cid = 0; cid < sess->s.con_num; cid++) अणु
		अगर (!sess->s.con[cid])
			अवरोध;
		con = to_clt_con(sess->s.con[cid]);
		mutex_lock(&con->con_mutex);
		destroy_con_cq_qp(con);
		mutex_unlock(&con->con_mutex);
		destroy_cm(con);
		destroy_con(con);
	पूर्ण
पूर्ण

अटल अंतरभूत bool xchg_sessions(काष्ठा rtrs_clt_sess __rcu **rcu_ppcpu_path,
				 काष्ठा rtrs_clt_sess *sess,
				 काष्ठा rtrs_clt_sess *next)
अणु
	काष्ठा rtrs_clt_sess **ppcpu_path;

	/* Call cmpxchg() without sparse warnings */
	ppcpu_path = (typeof(ppcpu_path))rcu_ppcpu_path;
	वापस sess == cmpxchg(ppcpu_path, sess, next);
पूर्ण

अटल व्योम rtrs_clt_हटाओ_path_from_arr(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt *clt = sess->clt;
	काष्ठा rtrs_clt_sess *next;
	bool रुको_क्रम_grace = false;
	पूर्णांक cpu;

	mutex_lock(&clt->paths_mutex);
	list_del_rcu(&sess->s.entry);

	/* Make sure everybody observes path removal. */
	synchronize_rcu();

	/*
	 * At this poपूर्णांक nobody sees @sess in the list, but still we have
	 * dangling poपूर्णांकer @pcpu_path which _can_ poपूर्णांक to @sess.  Since
	 * nobody can observe @sess in the list, we guarantee that IO path
	 * will not assign @sess to @pcpu_path, i.e. @pcpu_path can be equal
	 * to @sess, but can never again become @sess.
	 */

	/*
	 * Decrement paths number only after grace period, because
	 * caller of करो_each_path() must firstly observe list without
	 * path and only then decremented paths number.
	 *
	 * Otherwise there can be the following situation:
	 *    o Two paths exist and IO is coming.
	 *    o One path is हटाओd:
	 *      CPU#0                          CPU#1
	 *      करो_each_path():                rtrs_clt_हटाओ_path_from_arr():
	 *          path = get_next_path()
	 *          ^^^                            list_del_rcu(path)
	 *          [!CONNECTED path]              clt->paths_num--
	 *                                              ^^^^^^^^^
	 *          load clt->paths_num                 from 2 to 1
	 *                    ^^^^^^^^^
	 *                    sees 1
	 *
	 *      path is observed as !CONNECTED, but करो_each_path() loop
	 *      ends, because expression i < clt->paths_num is false.
	 */
	clt->paths_num--;

	/*
	 * Get @next connection from current @sess which is going to be
	 * हटाओd.  If @sess is the last element, then @next is शून्य.
	 */
	rcu_पढ़ो_lock();
	next = list_next_or_null_rr_rcu(&clt->paths_list, &sess->s.entry,
					typeof(*next), s.entry);
	rcu_पढ़ो_unlock();

	/*
	 * @pcpu paths can still poपूर्णांक to the path which is going to be
	 * हटाओd, so change the poपूर्णांकer manually.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा rtrs_clt_sess __rcu **ppcpu_path;

		ppcpu_path = per_cpu_ptr(clt->pcpu_path, cpu);
		अगर (rcu_dereference_रक्षित(*ppcpu_path,
			lockdep_is_held(&clt->paths_mutex)) != sess)
			/*
			 * synchronize_rcu() was called just after deleting
			 * entry from the list, thus IO code path cannot
			 * change poपूर्णांकer back to the poपूर्णांकer which is going
			 * to be हटाओd, we are safe here.
			 */
			जारी;

		/*
		 * We race with IO code path, which also changes poपूर्णांकer,
		 * thus we have to be careful not to overग_लिखो it.
		 */
		अगर (xchg_sessions(ppcpu_path, sess, next))
			/*
			 * @ppcpu_path was successfully replaced with @next,
			 * that means that someone could also pick up the
			 * @sess and dereferencing it right now, so रुको क्रम
			 * a grace period is required.
			 */
			रुको_क्रम_grace = true;
	पूर्ण
	अगर (रुको_क्रम_grace)
		synchronize_rcu();

	mutex_unlock(&clt->paths_mutex);
पूर्ण

अटल व्योम rtrs_clt_add_path_to_arr(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt *clt = sess->clt;

	mutex_lock(&clt->paths_mutex);
	clt->paths_num++;

	list_add_tail_rcu(&sess->s.entry, &clt->paths_list);
	mutex_unlock(&clt->paths_mutex);
पूर्ण

अटल व्योम rtrs_clt_बंद_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtrs_clt_sess *sess;

	sess = container_of(work, काष्ठा rtrs_clt_sess, बंद_work);

	cancel_delayed_work_sync(&sess->reconnect_dwork);
	rtrs_clt_stop_and_destroy_conns(sess);
	rtrs_clt_change_state_get_old(sess, RTRS_CLT_CLOSED, शून्य);
पूर्ण

अटल पूर्णांक init_conns(काष्ठा rtrs_clt_sess *sess)
अणु
	अचिन्हित पूर्णांक cid;
	पूर्णांक err;

	/*
	 * On every new session connections increase reconnect counter
	 * to aव्योम clashes with previous sessions not yet बंदd
	 * sessions on a server side.
	 */
	sess->s.recon_cnt++;

	/* Establish all RDMA connections  */
	क्रम (cid = 0; cid < sess->s.con_num; cid++) अणु
		err = create_con(sess, cid);
		अगर (err)
			जाओ destroy;

		err = create_cm(to_clt_con(sess->s.con[cid]));
		अगर (err) अणु
			destroy_con(to_clt_con(sess->s.con[cid]));
			जाओ destroy;
		पूर्ण
	पूर्ण
	err = alloc_sess_reqs(sess);
	अगर (err)
		जाओ destroy;

	rtrs_clt_start_hb(sess);

	वापस 0;

destroy:
	जबतक (cid--) अणु
		काष्ठा rtrs_clt_con *con = to_clt_con(sess->s.con[cid]);

		stop_cm(con);

		mutex_lock(&con->con_mutex);
		destroy_con_cq_qp(con);
		mutex_unlock(&con->con_mutex);
		destroy_cm(con);
		destroy_con(con);
	पूर्ण
	/*
	 * If we've never taken async path and got an error, say,
	 * करोing rdma_resolve_addr(), चयन to CONNECTION_ERR state
	 * manually to keep reconnecting.
	 */
	rtrs_clt_change_state_get_old(sess, RTRS_CLT_CONNECTING_ERR, शून्य);

	वापस err;
पूर्ण

अटल व्योम rtrs_clt_info_req_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_clt_con *con = to_clt_con(wc->qp->qp_context);
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_iu *iu;

	iu = container_of(wc->wr_cqe, काष्ठा rtrs_iu, cqe);
	rtrs_iu_मुक्त(iu, sess->s.dev->ib_dev, 1);

	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(sess->clt, "Sess info request send failed: %s\n",
			  ib_wc_status_msg(wc->status));
		rtrs_clt_change_state_get_old(sess, RTRS_CLT_CONNECTING_ERR, शून्य);
		वापस;
	पूर्ण

	rtrs_clt_update_wc_stats(con);
पूर्ण

अटल पूर्णांक process_info_rsp(काष्ठा rtrs_clt_sess *sess,
			    स्थिर काष्ठा rtrs_msg_info_rsp *msg)
अणु
	अचिन्हित पूर्णांक sg_cnt, total_len;
	पूर्णांक i, sgi;

	sg_cnt = le16_to_cpu(msg->sg_cnt);
	अगर (unlikely(!sg_cnt || (sess->queue_depth % sg_cnt))) अणु
		rtrs_err(sess->clt, "Incorrect sg_cnt %d, is not multiple\n",
			  sg_cnt);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check अगर IB immediate data size is enough to hold the mem_id and
	 * the offset inside the memory chunk.
	 */
	अगर (unlikely((ilog2(sg_cnt - 1) + 1) +
		     (ilog2(sess->chunk_size - 1) + 1) >
		     MAX_IMM_PAYL_BITS)) अणु
		rtrs_err(sess->clt,
			  "RDMA immediate size (%db) not enough to encode %d buffers of size %dB\n",
			  MAX_IMM_PAYL_BITS, sg_cnt, sess->chunk_size);
		वापस -EINVAL;
	पूर्ण
	total_len = 0;
	क्रम (sgi = 0, i = 0; sgi < sg_cnt && i < sess->queue_depth; sgi++) अणु
		स्थिर काष्ठा rtrs_sg_desc *desc = &msg->desc[sgi];
		u32 len, rkey;
		u64 addr;

		addr = le64_to_cpu(desc->addr);
		rkey = le32_to_cpu(desc->key);
		len  = le32_to_cpu(desc->len);

		total_len += len;

		अगर (unlikely(!len || (len % sess->chunk_size))) अणु
			rtrs_err(sess->clt, "Incorrect [%d].len %d\n", sgi,
				  len);
			वापस -EINVAL;
		पूर्ण
		क्रम ( ; len && i < sess->queue_depth; i++) अणु
			sess->rbufs[i].addr = addr;
			sess->rbufs[i].rkey = rkey;

			len  -= sess->chunk_size;
			addr += sess->chunk_size;
		पूर्ण
	पूर्ण
	/* Sanity check */
	अगर (unlikely(sgi != sg_cnt || i != sess->queue_depth)) अणु
		rtrs_err(sess->clt, "Incorrect sg vector, not fully mapped\n");
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(total_len != sess->chunk_size * sess->queue_depth)) अणु
		rtrs_err(sess->clt, "Incorrect total_len %d\n", total_len);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtrs_clt_info_rsp_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा rtrs_clt_con *con = to_clt_con(wc->qp->qp_context);
	काष्ठा rtrs_clt_sess *sess = to_clt_sess(con->c.sess);
	काष्ठा rtrs_msg_info_rsp *msg;
	क्रमागत rtrs_clt_state state;
	काष्ठा rtrs_iu *iu;
	माप_प्रकार rx_sz;
	पूर्णांक err;

	state = RTRS_CLT_CONNECTING_ERR;

	WARN_ON(con->c.cid);
	iu = container_of(wc->wr_cqe, काष्ठा rtrs_iu, cqe);
	अगर (unlikely(wc->status != IB_WC_SUCCESS)) अणु
		rtrs_err(sess->clt, "Sess info response recv failed: %s\n",
			  ib_wc_status_msg(wc->status));
		जाओ out;
	पूर्ण
	WARN_ON(wc->opcode != IB_WC_RECV);

	अगर (unlikely(wc->byte_len < माप(*msg))) अणु
		rtrs_err(sess->clt, "Sess info response is malformed: size %d\n",
			  wc->byte_len);
		जाओ out;
	पूर्ण
	ib_dma_sync_single_क्रम_cpu(sess->s.dev->ib_dev, iu->dma_addr,
				   iu->size, DMA_FROM_DEVICE);
	msg = iu->buf;
	अगर (unlikely(le16_to_cpu(msg->type) != RTRS_MSG_INFO_RSP)) अणु
		rtrs_err(sess->clt, "Sess info response is malformed: type %d\n",
			  le16_to_cpu(msg->type));
		जाओ out;
	पूर्ण
	rx_sz  = माप(*msg);
	rx_sz += माप(msg->desc[0]) * le16_to_cpu(msg->sg_cnt);
	अगर (unlikely(wc->byte_len < rx_sz)) अणु
		rtrs_err(sess->clt, "Sess info response is malformed: size %d\n",
			  wc->byte_len);
		जाओ out;
	पूर्ण
	err = process_info_rsp(sess, msg);
	अगर (unlikely(err))
		जाओ out;

	err = post_recv_sess(sess);
	अगर (unlikely(err))
		जाओ out;

	state = RTRS_CLT_CONNECTED;

out:
	rtrs_clt_update_wc_stats(con);
	rtrs_iu_मुक्त(iu, sess->s.dev->ib_dev, 1);
	rtrs_clt_change_state_get_old(sess, state, शून्य);
पूर्ण

अटल पूर्णांक rtrs_send_sess_info(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt_con *usr_con = to_clt_con(sess->s.con[0]);
	काष्ठा rtrs_msg_info_req *msg;
	काष्ठा rtrs_iu *tx_iu, *rx_iu;
	माप_प्रकार rx_sz;
	पूर्णांक err;

	rx_sz  = माप(काष्ठा rtrs_msg_info_rsp);
	rx_sz += माप(u64) * MAX_SESS_QUEUE_DEPTH;

	tx_iu = rtrs_iu_alloc(1, माप(काष्ठा rtrs_msg_info_req), GFP_KERNEL,
			       sess->s.dev->ib_dev, DMA_TO_DEVICE,
			       rtrs_clt_info_req_करोne);
	rx_iu = rtrs_iu_alloc(1, rx_sz, GFP_KERNEL, sess->s.dev->ib_dev,
			       DMA_FROM_DEVICE, rtrs_clt_info_rsp_करोne);
	अगर (unlikely(!tx_iu || !rx_iu)) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	/* Prepare क्रम getting info response */
	err = rtrs_iu_post_recv(&usr_con->c, rx_iu);
	अगर (unlikely(err)) अणु
		rtrs_err(sess->clt, "rtrs_iu_post_recv(), err: %d\n", err);
		जाओ out;
	पूर्ण
	rx_iu = शून्य;

	msg = tx_iu->buf;
	msg->type = cpu_to_le16(RTRS_MSG_INFO_REQ);
	स_नकल(msg->sessname, sess->s.sessname, माप(msg->sessname));

	ib_dma_sync_single_क्रम_device(sess->s.dev->ib_dev, tx_iu->dma_addr,
				      tx_iu->size, DMA_TO_DEVICE);

	/* Send info request */
	err = rtrs_iu_post_send(&usr_con->c, tx_iu, माप(*msg), शून्य);
	अगर (unlikely(err)) अणु
		rtrs_err(sess->clt, "rtrs_iu_post_send(), err: %d\n", err);
		जाओ out;
	पूर्ण
	tx_iu = शून्य;

	/* Wait क्रम state change */
	रुको_event_पूर्णांकerruptible_समयout(sess->state_wq,
					 sess->state != RTRS_CLT_CONNECTING,
					 msecs_to_jअगरfies(
						 RTRS_CONNECT_TIMEOUT_MS));
	अगर (unlikely(READ_ONCE(sess->state) != RTRS_CLT_CONNECTED)) अणु
		अगर (READ_ONCE(sess->state) == RTRS_CLT_CONNECTING_ERR)
			err = -ECONNRESET;
		अन्यथा
			err = -ETIMEDOUT;
	पूर्ण

out:
	अगर (tx_iu)
		rtrs_iu_मुक्त(tx_iu, sess->s.dev->ib_dev, 1);
	अगर (rx_iu)
		rtrs_iu_मुक्त(rx_iu, sess->s.dev->ib_dev, 1);
	अगर (unlikely(err))
		/* If we've never taken async path because of दो_स्मृति problems */
		rtrs_clt_change_state_get_old(sess, RTRS_CLT_CONNECTING_ERR, शून्य);

	वापस err;
पूर्ण

/**
 * init_sess() - establishes all session connections and करोes handshake
 * @sess: client session.
 * In हाल of error full बंद or reconnect procedure should be taken,
 * because reconnect or बंद async works can be started.
 */
अटल पूर्णांक init_sess(काष्ठा rtrs_clt_sess *sess)
अणु
	पूर्णांक err;
	अक्षर str[NAME_MAX];
	काष्ठा rtrs_addr path = अणु
		.src = &sess->s.src_addr,
		.dst = &sess->s.dst_addr,
	पूर्ण;

	rtrs_addr_to_str(&path, str, माप(str));

	mutex_lock(&sess->init_mutex);
	err = init_conns(sess);
	अगर (err) अणु
		rtrs_err(sess->clt,
			 "init_conns() failed: err=%d path=%s [%s:%u]\n", err,
			 str, sess->hca_name, sess->hca_port);
		जाओ out;
	पूर्ण
	err = rtrs_send_sess_info(sess);
	अगर (err) अणु
		rtrs_err(
			sess->clt,
			"rtrs_send_sess_info() failed: err=%d path=%s [%s:%u]\n",
			err, str, sess->hca_name, sess->hca_port);
		जाओ out;
	पूर्ण
	rtrs_clt_sess_up(sess);
out:
	mutex_unlock(&sess->init_mutex);

	वापस err;
पूर्ण

अटल व्योम rtrs_clt_reconnect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtrs_clt_sess *sess;
	काष्ठा rtrs_clt *clt;
	अचिन्हित पूर्णांक delay_ms;
	पूर्णांक err;

	sess = container_of(to_delayed_work(work), काष्ठा rtrs_clt_sess,
			    reconnect_dwork);
	clt = sess->clt;

	अगर (READ_ONCE(sess->state) != RTRS_CLT_RECONNECTING)
		वापस;

	अगर (sess->reconnect_attempts >= clt->max_reconnect_attempts) अणु
		/* Close a session completely अगर max attempts is reached */
		rtrs_clt_बंद_conns(sess, false);
		वापस;
	पूर्ण
	sess->reconnect_attempts++;

	/* Stop everything */
	rtrs_clt_stop_and_destroy_conns(sess);
	msleep(RTRS_RECONNECT_BACKOFF);
	अगर (rtrs_clt_change_state_get_old(sess, RTRS_CLT_CONNECTING, शून्य)) अणु
		err = init_sess(sess);
		अगर (err)
			जाओ reconnect_again;
	पूर्ण

	वापस;

reconnect_again:
	अगर (rtrs_clt_change_state_get_old(sess, RTRS_CLT_RECONNECTING, शून्य)) अणु
		sess->stats->reconnects.fail_cnt++;
		delay_ms = clt->reconnect_delay_sec * 1000;
		queue_delayed_work(rtrs_wq, &sess->reconnect_dwork,
				   msecs_to_jअगरfies(delay_ms +
						    pअक्रमom_u32() %
						    RTRS_RECONNECT_SEED));
	पूर्ण
पूर्ण

अटल व्योम rtrs_clt_dev_release(काष्ठा device *dev)
अणु
	काष्ठा rtrs_clt *clt = container_of(dev, काष्ठा rtrs_clt, dev);

	kमुक्त(clt);
पूर्ण

अटल काष्ठा rtrs_clt *alloc_clt(स्थिर अक्षर *sessname, माप_प्रकार paths_num,
				  u16 port, माप_प्रकार pdu_sz, व्योम *priv,
				  व्योम	(*link_ev)(व्योम *priv,
						   क्रमागत rtrs_clt_link_ev ev),
				  अचिन्हित पूर्णांक max_segments,
				  अचिन्हित पूर्णांक reconnect_delay_sec,
				  अचिन्हित पूर्णांक max_reconnect_attempts)
अणु
	काष्ठा rtrs_clt *clt;
	पूर्णांक err;

	अगर (!paths_num || paths_num > MAX_PATHS_NUM)
		वापस ERR_PTR(-EINVAL);

	अगर (म_माप(sessname) >= माप(clt->sessname))
		वापस ERR_PTR(-EINVAL);

	clt = kzalloc(माप(*clt), GFP_KERNEL);
	अगर (!clt)
		वापस ERR_PTR(-ENOMEM);

	clt->pcpu_path = alloc_percpu(typeof(*clt->pcpu_path));
	अगर (!clt->pcpu_path) अणु
		kमुक्त(clt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	uuid_gen(&clt->paths_uuid);
	INIT_LIST_HEAD_RCU(&clt->paths_list);
	clt->paths_num = paths_num;
	clt->paths_up = MAX_PATHS_NUM;
	clt->port = port;
	clt->pdu_sz = pdu_sz;
	clt->max_segments = max_segments;
	clt->reconnect_delay_sec = reconnect_delay_sec;
	clt->max_reconnect_attempts = max_reconnect_attempts;
	clt->priv = priv;
	clt->link_ev = link_ev;
	clt->mp_policy = MP_POLICY_MIN_INFLIGHT;
	strlcpy(clt->sessname, sessname, माप(clt->sessname));
	init_रुकोqueue_head(&clt->permits_रुको);
	mutex_init(&clt->paths_ev_mutex);
	mutex_init(&clt->paths_mutex);

	clt->dev.class = rtrs_clt_dev_class;
	clt->dev.release = rtrs_clt_dev_release;
	err = dev_set_name(&clt->dev, "%s", sessname);
	अगर (err)
		जाओ err;
	/*
	 * Suppress user space notअगरication until
	 * sysfs files are created
	 */
	dev_set_uevent_suppress(&clt->dev, true);
	err = device_रेजिस्टर(&clt->dev);
	अगर (err) अणु
		put_device(&clt->dev);
		जाओ err;
	पूर्ण

	clt->kobj_paths = kobject_create_and_add("paths", &clt->dev.kobj);
	अगर (!clt->kobj_paths) अणु
		err = -ENOMEM;
		जाओ err_dev;
	पूर्ण
	err = rtrs_clt_create_sysfs_root_files(clt);
	अगर (err) अणु
		kobject_del(clt->kobj_paths);
		kobject_put(clt->kobj_paths);
		जाओ err_dev;
	पूर्ण
	dev_set_uevent_suppress(&clt->dev, false);
	kobject_uevent(&clt->dev.kobj, KOBJ_ADD);

	वापस clt;
err_dev:
	device_unरेजिस्टर(&clt->dev);
err:
	मुक्त_percpu(clt->pcpu_path);
	kमुक्त(clt);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम मुक्त_clt(काष्ठा rtrs_clt *clt)
अणु
	मुक्त_permits(clt);
	मुक्त_percpu(clt->pcpu_path);
	mutex_destroy(&clt->paths_ev_mutex);
	mutex_destroy(&clt->paths_mutex);
	/* release callback will मुक्त clt in last put */
	device_unरेजिस्टर(&clt->dev);
पूर्ण

/**
 * rtrs_clt_खोलो() - Open a session to an RTRS server
 * @ops: holds the link event callback and the निजी poपूर्णांकer.
 * @sessname: name of the session
 * @paths: Paths to be established defined by their src and dst addresses
 * @paths_num: Number of elements in the @paths array
 * @port: port to be used by the RTRS session
 * @pdu_sz: Size of extra payload which can be accessed after permit allocation.
 * @reconnect_delay_sec: समय between reconnect tries
 * @max_segments: Max. number of segments per IO request
 * @max_reconnect_attempts: Number of बार to reconnect on error beक्रमe giving
 *			    up, 0 क्रम * disabled, -1 क्रम क्रमever
 * @nr_poll_queues: number of polling mode connection using IB_POLL_सूचीECT flag
 *
 * Starts session establishment with the rtrs_server. The function can block
 * up to ~2000ms beक्रमe it वापसs.
 *
 * Return a valid poपूर्णांकer on success otherwise PTR_ERR.
 */
काष्ठा rtrs_clt *rtrs_clt_खोलो(काष्ठा rtrs_clt_ops *ops,
				 स्थिर अक्षर *sessname,
				 स्थिर काष्ठा rtrs_addr *paths,
				 माप_प्रकार paths_num, u16 port,
				 माप_प्रकार pdu_sz, u8 reconnect_delay_sec,
				 u16 max_segments,
				 s16 max_reconnect_attempts, u32 nr_poll_queues)
अणु
	काष्ठा rtrs_clt_sess *sess, *पंचांगp;
	काष्ठा rtrs_clt *clt;
	पूर्णांक err, i;

	clt = alloc_clt(sessname, paths_num, port, pdu_sz, ops->priv,
			ops->link_ev,
			max_segments, reconnect_delay_sec,
			max_reconnect_attempts);
	अगर (IS_ERR(clt)) अणु
		err = PTR_ERR(clt);
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < paths_num; i++) अणु
		काष्ठा rtrs_clt_sess *sess;

		sess = alloc_sess(clt, &paths[i], nr_cpu_ids,
				  max_segments, nr_poll_queues);
		अगर (IS_ERR(sess)) अणु
			err = PTR_ERR(sess);
			जाओ बंद_all_sess;
		पूर्ण
		अगर (!i)
			sess->क्रम_new_clt = 1;
		list_add_tail_rcu(&sess->s.entry, &clt->paths_list);

		err = init_sess(sess);
		अगर (err) अणु
			list_del_rcu(&sess->s.entry);
			rtrs_clt_बंद_conns(sess, true);
			मुक्त_sess(sess);
			जाओ बंद_all_sess;
		पूर्ण

		err = rtrs_clt_create_sess_files(sess);
		अगर (err) अणु
			list_del_rcu(&sess->s.entry);
			rtrs_clt_बंद_conns(sess, true);
			मुक्त_sess(sess);
			जाओ बंद_all_sess;
		पूर्ण
	पूर्ण
	err = alloc_permits(clt);
	अगर (err)
		जाओ बंद_all_sess;

	वापस clt;

बंद_all_sess:
	list_क्रम_each_entry_safe(sess, पंचांगp, &clt->paths_list, s.entry) अणु
		rtrs_clt_destroy_sess_files(sess, शून्य);
		rtrs_clt_बंद_conns(sess, true);
		kobject_put(&sess->kobj);
	पूर्ण
	rtrs_clt_destroy_sysfs_root(clt);
	मुक्त_clt(clt);

out:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(rtrs_clt_खोलो);

/**
 * rtrs_clt_बंद() - Close a session
 * @clt: Session handle. Session is मुक्तd upon वापस.
 */
व्योम rtrs_clt_बंद(काष्ठा rtrs_clt *clt)
अणु
	काष्ठा rtrs_clt_sess *sess, *पंचांगp;

	/* Firstly क्रमbid sysfs access */
	rtrs_clt_destroy_sysfs_root(clt);

	/* Now it is safe to iterate over all paths without locks */
	list_क्रम_each_entry_safe(sess, पंचांगp, &clt->paths_list, s.entry) अणु
		rtrs_clt_बंद_conns(sess, true);
		rtrs_clt_destroy_sess_files(sess, शून्य);
		kobject_put(&sess->kobj);
	पूर्ण
	मुक्त_clt(clt);
पूर्ण
EXPORT_SYMBOL(rtrs_clt_बंद);

पूर्णांक rtrs_clt_reconnect_from_sysfs(काष्ठा rtrs_clt_sess *sess)
अणु
	क्रमागत rtrs_clt_state old_state;
	पूर्णांक err = -EBUSY;
	bool changed;

	changed = rtrs_clt_change_state_get_old(sess, RTRS_CLT_RECONNECTING,
						 &old_state);
	अगर (changed) अणु
		sess->reconnect_attempts = 0;
		queue_delayed_work(rtrs_wq, &sess->reconnect_dwork, 0);
	पूर्ण
	अगर (changed || old_state == RTRS_CLT_RECONNECTING) अणु
		/*
		 * flush_delayed_work() queues pending work क्रम immediate
		 * execution, so करो the flush अगर we have queued something
		 * right now or work is pending.
		 */
		flush_delayed_work(&sess->reconnect_dwork);
		err = (READ_ONCE(sess->state) ==
		       RTRS_CLT_CONNECTED ? 0 : -ENOTCONN);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक rtrs_clt_disconnect_from_sysfs(काष्ठा rtrs_clt_sess *sess)
अणु
	rtrs_clt_बंद_conns(sess, true);

	वापस 0;
पूर्ण

पूर्णांक rtrs_clt_हटाओ_path_from_sysfs(काष्ठा rtrs_clt_sess *sess,
				     स्थिर काष्ठा attribute *sysfs_self)
अणु
	क्रमागत rtrs_clt_state old_state;
	bool changed;

	/*
	 * Continue stopping path till state was changed to DEAD or
	 * state was observed as DEAD:
	 * 1. State was changed to DEAD - we were fast and nobody
	 *    invoked rtrs_clt_reconnect(), which can again start
	 *    reconnecting.
	 * 2. State was observed as DEAD - we have someone in parallel
	 *    removing the path.
	 */
	करो अणु
		rtrs_clt_बंद_conns(sess, true);
		changed = rtrs_clt_change_state_get_old(sess,
							RTRS_CLT_DEAD,
							&old_state);
	पूर्ण जबतक (!changed && old_state != RTRS_CLT_DEAD);

	अगर (likely(changed)) अणु
		rtrs_clt_हटाओ_path_from_arr(sess);
		rtrs_clt_destroy_sess_files(sess, sysfs_self);
		kobject_put(&sess->kobj);
	पूर्ण

	वापस 0;
पूर्ण

व्योम rtrs_clt_set_max_reconnect_attempts(काष्ठा rtrs_clt *clt, पूर्णांक value)
अणु
	clt->max_reconnect_attempts = (अचिन्हित पूर्णांक)value;
पूर्ण

पूर्णांक rtrs_clt_get_max_reconnect_attempts(स्थिर काष्ठा rtrs_clt *clt)
अणु
	वापस (पूर्णांक)clt->max_reconnect_attempts;
पूर्ण

/**
 * rtrs_clt_request() - Request data transfer to/from server via RDMA.
 *
 * @dir:	READ/WRITE
 * @ops:	callback function to be called as confirmation, and the poपूर्णांकer.
 * @clt:	Session
 * @permit:	Pपुनः_स्मृतिated permit
 * @vec:	Message that is sent to server together with the request.
 *		Sum of len of all @vec elements limited to <= IO_MSG_SIZE.
 *		Since the msg is copied पूर्णांकernally it can be allocated on stack.
 * @nr:		Number of elements in @vec.
 * @data_len:	length of data sent to/from server
 * @sg:		Pages to be sent/received to/from server.
 * @sg_cnt:	Number of elements in the @sg
 *
 * Return:
 * 0:		Success
 * <0:		Error
 *
 * On dir=READ rtrs client will request a data transfer from Server to client.
 * The data that the server will respond with will be stored in @sg when
 * the user receives an %RTRS_CLT_RDMA_EV_RDMA_REQUEST_WRITE_COMPL event.
 * On dir=WRITE rtrs client will rdma ग_लिखो data in sg to server side.
 */
पूर्णांक rtrs_clt_request(पूर्णांक dir, काष्ठा rtrs_clt_req_ops *ops,
		     काष्ठा rtrs_clt *clt, काष्ठा rtrs_permit *permit,
		      स्थिर काष्ठा kvec *vec, माप_प्रकार nr, माप_प्रकार data_len,
		      काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_cnt)
अणु
	काष्ठा rtrs_clt_io_req *req;
	काष्ठा rtrs_clt_sess *sess;

	क्रमागत dma_data_direction dma_dir;
	पूर्णांक err = -ECONNABORTED, i;
	माप_प्रकार usr_len, hdr_len;
	काष्ठा path_it it;

	/* Get kvec length */
	क्रम (i = 0, usr_len = 0; i < nr; i++)
		usr_len += vec[i].iov_len;

	अगर (dir == READ) अणु
		hdr_len = माप(काष्ठा rtrs_msg_rdma_पढ़ो) +
			  sg_cnt * माप(काष्ठा rtrs_sg_desc);
		dma_dir = DMA_FROM_DEVICE;
	पूर्ण अन्यथा अणु
		hdr_len = माप(काष्ठा rtrs_msg_rdma_ग_लिखो);
		dma_dir = DMA_TO_DEVICE;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (path_it_init(&it, clt);
	     (sess = it.next_path(&it)) && it.i < it.clt->paths_num; it.i++) अणु
		अगर (unlikely(READ_ONCE(sess->state) != RTRS_CLT_CONNECTED))
			जारी;

		अगर (unlikely(usr_len + hdr_len > sess->max_hdr_size)) अणु
			rtrs_wrn_rl(sess->clt,
				     "%s request failed, user message size is %zu and header length %zu, but max size is %u\n",
				     dir == READ ? "Read" : "Write",
				     usr_len, hdr_len, sess->max_hdr_size);
			err = -EMSGSIZE;
			अवरोध;
		पूर्ण
		req = rtrs_clt_get_req(sess, ops->conf_fn, permit, ops->priv,
				       vec, usr_len, sg, sg_cnt, data_len,
				       dma_dir);
		अगर (dir == READ)
			err = rtrs_clt_पढ़ो_req(req);
		अन्यथा
			err = rtrs_clt_ग_लिखो_req(req);
		अगर (unlikely(err)) अणु
			req->in_use = false;
			जारी;
		पूर्ण
		/* Success path */
		अवरोध;
	पूर्ण
	path_it_deinit(&it);
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण
EXPORT_SYMBOL(rtrs_clt_request);

पूर्णांक rtrs_clt_rdma_cq_direct(काष्ठा rtrs_clt *clt, अचिन्हित पूर्णांक index)
अणु
	/* If no path, वापस -1 क्रम block layer not to try again */
	पूर्णांक cnt = -1;
	काष्ठा rtrs_con *con;
	काष्ठा rtrs_clt_sess *sess;
	काष्ठा path_it it;

	rcu_पढ़ो_lock();
	क्रम (path_it_init(&it, clt);
	     (sess = it.next_path(&it)) && it.i < it.clt->paths_num; it.i++) अणु
		अगर (READ_ONCE(sess->state) != RTRS_CLT_CONNECTED)
			जारी;

		con = sess->s.con[index + 1];
		cnt = ib_process_cq_direct(con->cq, -1);
		अगर (cnt)
			अवरोध;
	पूर्ण
	path_it_deinit(&it);
	rcu_पढ़ो_unlock();

	वापस cnt;
पूर्ण
EXPORT_SYMBOL(rtrs_clt_rdma_cq_direct);

/**
 * rtrs_clt_query() - queries RTRS session attributes
 *@clt: session poपूर्णांकer
 *@attr: query results क्रम session attributes.
 * Returns:
 *    0 on success
 *    -ECOMM		no connection to the server
 */
पूर्णांक rtrs_clt_query(काष्ठा rtrs_clt *clt, काष्ठा rtrs_attrs *attr)
अणु
	अगर (!rtrs_clt_is_connected(clt))
		वापस -ECOMM;

	attr->queue_depth      = clt->queue_depth;
	/* Cap max_io_size to min of remote buffer size and the fr pages */
	attr->max_io_size = min_t(पूर्णांक, clt->max_io_size,
				  clt->max_segments * SZ_4K);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtrs_clt_query);

पूर्णांक rtrs_clt_create_path_from_sysfs(काष्ठा rtrs_clt *clt,
				     काष्ठा rtrs_addr *addr)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक err;

	sess = alloc_sess(clt, addr, nr_cpu_ids, clt->max_segments, 0);
	अगर (IS_ERR(sess))
		वापस PTR_ERR(sess);

	/*
	 * It is totally safe to add path in CONNECTING state: coming
	 * IO will never grab it.  Also it is very important to add
	 * path beक्रमe init, since init fires LINK_CONNECTED event.
	 */
	rtrs_clt_add_path_to_arr(sess);

	err = init_sess(sess);
	अगर (err)
		जाओ बंद_sess;

	err = rtrs_clt_create_sess_files(sess);
	अगर (err)
		जाओ बंद_sess;

	वापस 0;

बंद_sess:
	rtrs_clt_हटाओ_path_from_arr(sess);
	rtrs_clt_बंद_conns(sess, true);
	मुक्त_sess(sess);

	वापस err;
पूर्ण

अटल पूर्णांक rtrs_clt_ib_dev_init(काष्ठा rtrs_ib_dev *dev)
अणु
	अगर (!(dev->ib_dev->attrs.device_cap_flags &
	      IB_DEVICE_MEM_MGT_EXTENSIONS)) अणु
		pr_err("Memory registrations not supported.\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtrs_rdma_dev_pd_ops dev_pd_ops = अणु
	.init = rtrs_clt_ib_dev_init
पूर्ण;

अटल पूर्णांक __init rtrs_client_init(व्योम)
अणु
	rtrs_rdma_dev_pd_init(0, &dev_pd);

	rtrs_clt_dev_class = class_create(THIS_MODULE, "rtrs-client");
	अगर (IS_ERR(rtrs_clt_dev_class)) अणु
		pr_err("Failed to create rtrs-client dev class\n");
		वापस PTR_ERR(rtrs_clt_dev_class);
	पूर्ण
	rtrs_wq = alloc_workqueue("rtrs_client_wq", 0, 0);
	अगर (!rtrs_wq) अणु
		class_destroy(rtrs_clt_dev_class);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास rtrs_client_निकास(व्योम)
अणु
	destroy_workqueue(rtrs_wq);
	class_destroy(rtrs_clt_dev_class);
	rtrs_rdma_dev_pd_deinit(&dev_pd);
पूर्ण

module_init(rtrs_client_init);
module_निकास(rtrs_client_निकास);
