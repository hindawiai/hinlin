<शैली गुरु>
/*
 * Copyright (c) 2006, 2019 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/in.h>
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/ratelimit.h>

#समावेश "rds_single_path.h"
#समावेश "rds.h"
#समावेश "ib.h"
#समावेश "ib_mr.h"

/*
 * Convert IB-specअगरic error message to RDS error message and call core
 * completion handler.
 */
अटल व्योम rds_ib_send_complete(काष्ठा rds_message *rm,
				 पूर्णांक wc_status,
				 व्योम (*complete)(काष्ठा rds_message *rm, पूर्णांक status))
अणु
	पूर्णांक notअगरy_status;

	चयन (wc_status) अणु
	हाल IB_WC_WR_FLUSH_ERR:
		वापस;

	हाल IB_WC_SUCCESS:
		notअगरy_status = RDS_RDMA_SUCCESS;
		अवरोध;

	हाल IB_WC_REM_ACCESS_ERR:
		notअगरy_status = RDS_RDMA_REMOTE_ERROR;
		अवरोध;

	शेष:
		notअगरy_status = RDS_RDMA_OTHER_ERROR;
		अवरोध;
	पूर्ण
	complete(rm, notअगरy_status);
पूर्ण

अटल व्योम rds_ib_send_unmap_data(काष्ठा rds_ib_connection *ic,
				   काष्ठा rm_data_op *op,
				   पूर्णांक wc_status)
अणु
	अगर (op->op_nents)
		ib_dma_unmap_sg(ic->i_cm_id->device,
				op->op_sg, op->op_nents,
				DMA_TO_DEVICE);
पूर्ण

अटल व्योम rds_ib_send_unmap_rdma(काष्ठा rds_ib_connection *ic,
				   काष्ठा rm_rdma_op *op,
				   पूर्णांक wc_status)
अणु
	अगर (op->op_mapped) अणु
		ib_dma_unmap_sg(ic->i_cm_id->device,
				op->op_sg, op->op_nents,
				op->op_ग_लिखो ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		op->op_mapped = 0;
	पूर्ण

	/* If the user asked क्रम a completion notअगरication on this
	 * message, we can implement three dअगरferent semantics:
	 *  1.	Notअगरy when we received the ACK on the RDS message
	 *	that was queued with the RDMA. This provides reliable
	 *	notअगरication of RDMA status at the expense of a one-way
	 *	packet delay.
	 *  2.	Notअगरy when the IB stack gives us the completion event क्रम
	 *	the RDMA operation.
	 *  3.	Notअगरy when the IB stack gives us the completion event क्रम
	 *	the accompanying RDS messages.
	 * Here, we implement approach #3. To implement approach #2,
	 * we would need to take an event क्रम the rdma WR. To implement #1,
	 * करोn't call rds_rdma_send_complete at all, and fall back to the notअगरy
	 * handling in the ACK processing code.
	 *
	 * Note: There's no need to explicitly sync any RDMA buffers using
	 * ib_dma_sync_sg_क्रम_cpu - the completion क्रम the RDMA
	 * operation itself unmapped the RDMA buffers, which takes care
	 * of synching.
	 */
	rds_ib_send_complete(container_of(op, काष्ठा rds_message, rdma),
			     wc_status, rds_rdma_send_complete);

	अगर (op->op_ग_लिखो)
		rds_stats_add(s_send_rdma_bytes, op->op_bytes);
	अन्यथा
		rds_stats_add(s_recv_rdma_bytes, op->op_bytes);
पूर्ण

अटल व्योम rds_ib_send_unmap_atomic(काष्ठा rds_ib_connection *ic,
				     काष्ठा rm_atomic_op *op,
				     पूर्णांक wc_status)
अणु
	/* unmap atomic recvbuf */
	अगर (op->op_mapped) अणु
		ib_dma_unmap_sg(ic->i_cm_id->device, op->op_sg, 1,
				DMA_FROM_DEVICE);
		op->op_mapped = 0;
	पूर्ण

	rds_ib_send_complete(container_of(op, काष्ठा rds_message, atomic),
			     wc_status, rds_atomic_send_complete);

	अगर (op->op_type == RDS_ATOMIC_TYPE_CSWP)
		rds_ib_stats_inc(s_ib_atomic_cswp);
	अन्यथा
		rds_ib_stats_inc(s_ib_atomic_fadd);
पूर्ण

/*
 * Unmap the resources associated with a काष्ठा send_work.
 *
 * Returns the rm क्रम no good reason other than it is unobtainable
 * other than by चयनing on wr.opcode, currently, and the caller,
 * the event handler, needs it.
 */
अटल काष्ठा rds_message *rds_ib_send_unmap_op(काष्ठा rds_ib_connection *ic,
						काष्ठा rds_ib_send_work *send,
						पूर्णांक wc_status)
अणु
	काष्ठा rds_message *rm = शून्य;

	/* In the error हाल, wc.opcode someबार contains garbage */
	चयन (send->s_wr.opcode) अणु
	हाल IB_WR_SEND:
		अगर (send->s_op) अणु
			rm = container_of(send->s_op, काष्ठा rds_message, data);
			rds_ib_send_unmap_data(ic, send->s_op, wc_status);
		पूर्ण
		अवरोध;
	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_READ:
		अगर (send->s_op) अणु
			rm = container_of(send->s_op, काष्ठा rds_message, rdma);
			rds_ib_send_unmap_rdma(ic, send->s_op, wc_status);
		पूर्ण
		अवरोध;
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
	हाल IB_WR_ATOMIC_CMP_AND_SWP:
		अगर (send->s_op) अणु
			rm = container_of(send->s_op, काष्ठा rds_message, atomic);
			rds_ib_send_unmap_atomic(ic, send->s_op, wc_status);
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk_ratelimited(KERN_NOTICE
			       "RDS/IB: %s: unexpected opcode 0x%x in WR!\n",
			       __func__, send->s_wr.opcode);
		अवरोध;
	पूर्ण

	send->s_wr.opcode = 0xdead;

	वापस rm;
पूर्ण

व्योम rds_ib_send_init_ring(काष्ठा rds_ib_connection *ic)
अणु
	काष्ठा rds_ib_send_work *send;
	u32 i;

	क्रम (i = 0, send = ic->i_sends; i < ic->i_send_ring.w_nr; i++, send++) अणु
		काष्ठा ib_sge *sge;

		send->s_op = शून्य;

		send->s_wr.wr_id = i;
		send->s_wr.sg_list = send->s_sge;
		send->s_wr.ex.imm_data = 0;

		sge = &send->s_sge[0];
		sge->addr = ic->i_send_hdrs_dma[i];

		sge->length = माप(काष्ठा rds_header);
		sge->lkey = ic->i_pd->local_dma_lkey;

		send->s_sge[1].lkey = ic->i_pd->local_dma_lkey;
	पूर्ण
पूर्ण

व्योम rds_ib_send_clear_ring(काष्ठा rds_ib_connection *ic)
अणु
	काष्ठा rds_ib_send_work *send;
	u32 i;

	क्रम (i = 0, send = ic->i_sends; i < ic->i_send_ring.w_nr; i++, send++) अणु
		अगर (send->s_op && send->s_wr.opcode != 0xdead)
			rds_ib_send_unmap_op(ic, send, IB_WC_WR_FLUSH_ERR);
	पूर्ण
पूर्ण

/*
 * The only fast path caller always has a non-zero nr, so we करोn't
 * bother testing nr beक्रमe perक्रमming the atomic sub.
 */
अटल व्योम rds_ib_sub_संकेतed(काष्ठा rds_ib_connection *ic, पूर्णांक nr)
अणु
	अगर ((atomic_sub_वापस(nr, &ic->i_संकेतed_sends) == 0) &&
	    रुकोqueue_active(&rds_ib_ring_empty_रुको))
		wake_up(&rds_ib_ring_empty_रुको);
	BUG_ON(atomic_पढ़ो(&ic->i_संकेतed_sends) < 0);
पूर्ण

/*
 * The _oldest/_मुक्त ring operations here race cleanly with the alloc/unalloc
 * operations perक्रमmed in the send path.  As the sender allocs and potentially
 * unallocs the next मुक्त entry in the ring it करोesn't alter which is
 * the next to be मुक्तd, which is what this is concerned with.
 */
व्योम rds_ib_send_cqe_handler(काष्ठा rds_ib_connection *ic, काष्ठा ib_wc *wc)
अणु
	काष्ठा rds_message *rm = शून्य;
	काष्ठा rds_connection *conn = ic->conn;
	काष्ठा rds_ib_send_work *send;
	u32 completed;
	u32 oldest;
	u32 i = 0;
	पूर्णांक nr_sig = 0;


	rdsdebug("wc wr_id 0x%llx status %u (%s) byte_len %u imm_data %u\n",
		 (अचिन्हित दीर्घ दीर्घ)wc->wr_id, wc->status,
		 ib_wc_status_msg(wc->status), wc->byte_len,
		 be32_to_cpu(wc->ex.imm_data));
	rds_ib_stats_inc(s_ib_tx_cq_event);

	अगर (wc->wr_id == RDS_IB_ACK_WR_ID) अणु
		अगर (समय_after(jअगरfies, ic->i_ack_queued + HZ / 2))
			rds_ib_stats_inc(s_ib_tx_stalled);
		rds_ib_ack_send_complete(ic);
		वापस;
	पूर्ण

	oldest = rds_ib_ring_oldest(&ic->i_send_ring);

	completed = rds_ib_ring_completed(&ic->i_send_ring, wc->wr_id, oldest);

	क्रम (i = 0; i < completed; i++) अणु
		send = &ic->i_sends[oldest];
		अगर (send->s_wr.send_flags & IB_SEND_SIGNALED)
			nr_sig++;

		rm = rds_ib_send_unmap_op(ic, send, wc->status);

		अगर (समय_after(jअगरfies, send->s_queued + HZ / 2))
			rds_ib_stats_inc(s_ib_tx_stalled);

		अगर (send->s_op) अणु
			अगर (send->s_op == rm->m_final_op) अणु
				/* If anyone रुकोed क्रम this message to get
				 * flushed out, wake them up now
				 */
				rds_message_unmapped(rm);
			पूर्ण
			rds_message_put(rm);
			send->s_op = शून्य;
		पूर्ण

		oldest = (oldest + 1) % ic->i_send_ring.w_nr;
	पूर्ण

	rds_ib_ring_मुक्त(&ic->i_send_ring, completed);
	rds_ib_sub_संकेतed(ic, nr_sig);

	अगर (test_and_clear_bit(RDS_LL_SEND_FULL, &conn->c_flags) ||
	    test_bit(0, &conn->c_map_queued))
		queue_delayed_work(rds_wq, &conn->c_send_w, 0);

	/* We expect errors as the qp is drained during shutकरोwn */
	अगर (wc->status != IB_WC_SUCCESS && rds_conn_up(conn)) अणु
		rds_ib_conn_error(conn, "send completion on <%pI6c,%pI6c,%d> had status %u (%s), vendor err 0x%x, disconnecting and reconnecting\n",
				  &conn->c_laddr, &conn->c_faddr,
				  conn->c_tos, wc->status,
				  ib_wc_status_msg(wc->status), wc->venकरोr_err);
	पूर्ण
पूर्ण

/*
 * This is the मुख्य function क्रम allocating credits when sending
 * messages.
 *
 * Conceptually, we have two counters:
 *  -	send credits: this tells us how many WRs we're allowed
 *	to submit without overruning the receiver's queue. For
 *	each SEND WR we post, we decrement this by one.
 *
 *  -	posted credits: this tells us how many WRs we recently
 *	posted to the receive queue. This value is transferred
 *	to the peer as a "credit update" in a RDS header field.
 *	Every समय we transmit credits to the peer, we subtract
 *	the amount of transferred credits from this counter.
 *
 * It is essential that we aव्योम situations where both sides have
 * exhausted their send credits, and are unable to send new credits
 * to the peer. We achieve this by requiring that we send at least
 * one credit update to the peer beक्रमe exhausting our credits.
 * When new credits arrive, we subtract one credit that is withheld
 * until we've posted new buffers and are पढ़ोy to transmit these
 * credits (see rds_ib_send_add_credits below).
 *
 * The RDS send code is essentially single-thपढ़ोed; rds_send_xmit
 * sets RDS_IN_XMIT to ensure exclusive access to the send ring.
 * However, the ACK sending code is independent and can race with
 * message SENDs.
 *
 * In the send path, we need to update the counters क्रम send credits
 * and the counter of posted buffers atomically - when we use the
 * last available credit, we cannot allow another thपढ़ो to race us
 * and grab the posted credits counter.  Hence, we have to use a
 * spinlock to protect the credit counter, or use atomics.
 *
 * Spinlocks shared between the send and the receive path are bad,
 * because they create unnecessary delays. An early implementation
 * using a spinlock showed a 5% degradation in throughput at some
 * loads.
 *
 * This implementation aव्योमs spinlocks completely, putting both
 * counters पूर्णांकo a single atomic, and updating that atomic using
 * atomic_add (in the receive path, when receiving fresh credits),
 * and using atomic_cmpxchg when updating the two counters.
 */
पूर्णांक rds_ib_send_grab_credits(काष्ठा rds_ib_connection *ic,
			     u32 wanted, u32 *adv_credits, पूर्णांक need_posted, पूर्णांक max_posted)
अणु
	अचिन्हित पूर्णांक avail, posted, got = 0, advertise;
	दीर्घ oldval, newval;

	*adv_credits = 0;
	अगर (!ic->i_flowctl)
		वापस wanted;

try_again:
	advertise = 0;
	oldval = newval = atomic_पढ़ो(&ic->i_credits);
	posted = IB_GET_POST_CREDITS(oldval);
	avail = IB_GET_SEND_CREDITS(oldval);

	rdsdebug("wanted=%u credits=%u posted=%u\n",
			wanted, avail, posted);

	/* The last credit must be used to send a credit update. */
	अगर (avail && !posted)
		avail--;

	अगर (avail < wanted) अणु
		काष्ठा rds_connection *conn = ic->i_cm_id->context;

		/* Oops, there aren't that many credits left! */
		set_bit(RDS_LL_SEND_FULL, &conn->c_flags);
		got = avail;
	पूर्ण अन्यथा अणु
		/* Someबार you get what you want, lalala. */
		got = wanted;
	पूर्ण
	newval -= IB_SET_SEND_CREDITS(got);

	/*
	 * If need_posted is non-zero, then the caller wants
	 * the posted regardless of whether any send credits are
	 * available.
	 */
	अगर (posted && (got || need_posted)) अणु
		advertise = min_t(अचिन्हित पूर्णांक, posted, max_posted);
		newval -= IB_SET_POST_CREDITS(advertise);
	पूर्ण

	/* Finally bill everything */
	अगर (atomic_cmpxchg(&ic->i_credits, oldval, newval) != oldval)
		जाओ try_again;

	*adv_credits = advertise;
	वापस got;
पूर्ण

व्योम rds_ib_send_add_credits(काष्ठा rds_connection *conn, अचिन्हित पूर्णांक credits)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	अगर (credits == 0)
		वापस;

	rdsdebug("credits=%u current=%u%s\n",
			credits,
			IB_GET_SEND_CREDITS(atomic_पढ़ो(&ic->i_credits)),
			test_bit(RDS_LL_SEND_FULL, &conn->c_flags) ? ", ll_send_full" : "");

	atomic_add(IB_SET_SEND_CREDITS(credits), &ic->i_credits);
	अगर (test_and_clear_bit(RDS_LL_SEND_FULL, &conn->c_flags))
		queue_delayed_work(rds_wq, &conn->c_send_w, 0);

	WARN_ON(IB_GET_SEND_CREDITS(credits) >= 16384);

	rds_ib_stats_inc(s_ib_rx_credit_updates);
पूर्ण

व्योम rds_ib_advertise_credits(काष्ठा rds_connection *conn, अचिन्हित पूर्णांक posted)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	अगर (posted == 0)
		वापस;

	atomic_add(IB_SET_POST_CREDITS(posted), &ic->i_credits);

	/* Decide whether to send an update to the peer now.
	 * If we would send a credit update क्रम every single buffer we
	 * post, we would end up with an ACK storm (ACK arrives,
	 * consumes buffer, we refill the ring, send ACK to remote
	 * advertising the newly posted buffer... ad inf)
	 *
	 * Perक्रमmance pretty much depends on how often we send
	 * credit updates - too frequent updates mean lots of ACKs.
	 * Too infrequent updates, and the peer will run out of
	 * credits and has to throttle.
	 * For the समय being, 16 seems to be a good compromise.
	 */
	अगर (IB_GET_POST_CREDITS(atomic_पढ़ो(&ic->i_credits)) >= 16)
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
पूर्ण

अटल अंतरभूत पूर्णांक rds_ib_set_wr_संकेत_state(काष्ठा rds_ib_connection *ic,
					     काष्ठा rds_ib_send_work *send,
					     bool notअगरy)
अणु
	/*
	 * We want to delay संकेतing completions just enough to get
	 * the batching benefits but not so much that we create dead समय
	 * on the wire.
	 */
	अगर (ic->i_unसंकेतed_wrs-- == 0 || notअगरy) अणु
		ic->i_unसंकेतed_wrs = rds_ib_sysctl_max_unsig_wrs;
		send->s_wr.send_flags |= IB_SEND_SIGNALED;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This can be called multiple बार क्रम a given message.  The first समय
 * we see a message we map its scatterlist पूर्णांकo the IB device so that
 * we can provide that mapped address to the IB scatter gather entries
 * in the IB work requests.  We translate the scatterlist पूर्णांकo a series
 * of work requests that fragment the message.  These work requests complete
 * in order so we pass ownership of the message to the completion handler
 * once we send the final fragment.
 *
 * The RDS core uses the c_send_lock to only enter this function once
 * per connection.  This makes sure that the tx ring alloc/unalloc pairs
 * करोn't get out of sync and confuse the ring.
 */
पूर्णांक rds_ib_xmit(काष्ठा rds_connection *conn, काष्ठा rds_message *rm,
		अचिन्हित पूर्णांक hdr_off, अचिन्हित पूर्णांक sg, अचिन्हित पूर्णांक off)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा ib_device *dev = ic->i_cm_id->device;
	काष्ठा rds_ib_send_work *send = शून्य;
	काष्ठा rds_ib_send_work *first;
	काष्ठा rds_ib_send_work *prev;
	स्थिर काष्ठा ib_send_wr *failed_wr;
	काष्ठा scatterlist *scat;
	u32 pos;
	u32 i;
	u32 work_alloc;
	u32 credit_alloc = 0;
	u32 posted;
	u32 adv_credits = 0;
	पूर्णांक send_flags = 0;
	पूर्णांक bytes_sent = 0;
	पूर्णांक ret;
	पूर्णांक flow_controlled = 0;
	पूर्णांक nr_sig = 0;

	BUG_ON(off % RDS_FRAG_SIZE);
	BUG_ON(hdr_off != 0 && hdr_off != माप(काष्ठा rds_header));

	/* Do not send cong updates to IB loopback */
	अगर (conn->c_loopback
	    && rm->m_inc.i_hdr.h_flags & RDS_FLAG_CONG_BITMAP) अणु
		rds_cong_map_updated(conn->c_fcong, ~(u64) 0);
		scat = &rm->data.op_sg[sg];
		ret = max_t(पूर्णांक, RDS_CONG_MAP_BYTES, scat->length);
		वापस माप(काष्ठा rds_header) + ret;
	पूर्ण

	/* FIXME we may overallocate here */
	अगर (be32_to_cpu(rm->m_inc.i_hdr.h_len) == 0)
		i = 1;
	अन्यथा
		i = DIV_ROUND_UP(be32_to_cpu(rm->m_inc.i_hdr.h_len), RDS_FRAG_SIZE);

	work_alloc = rds_ib_ring_alloc(&ic->i_send_ring, i, &pos);
	अगर (work_alloc == 0) अणु
		set_bit(RDS_LL_SEND_FULL, &conn->c_flags);
		rds_ib_stats_inc(s_ib_tx_ring_full);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (ic->i_flowctl) अणु
		credit_alloc = rds_ib_send_grab_credits(ic, work_alloc, &posted, 0, RDS_MAX_ADV_CREDIT);
		adv_credits += posted;
		अगर (credit_alloc < work_alloc) अणु
			rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc - credit_alloc);
			work_alloc = credit_alloc;
			flow_controlled = 1;
		पूर्ण
		अगर (work_alloc == 0) अणु
			set_bit(RDS_LL_SEND_FULL, &conn->c_flags);
			rds_ib_stats_inc(s_ib_tx_throttle);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/* map the message the first समय we see it */
	अगर (!ic->i_data_op) अणु
		अगर (rm->data.op_nents) अणु
			rm->data.op_count = ib_dma_map_sg(dev,
							  rm->data.op_sg,
							  rm->data.op_nents,
							  DMA_TO_DEVICE);
			rdsdebug("ic %p mapping rm %p: %d\n", ic, rm, rm->data.op_count);
			अगर (rm->data.op_count == 0) अणु
				rds_ib_stats_inc(s_ib_tx_sg_mapping_failure);
				rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc);
				ret = -ENOMEM; /* XXX ? */
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			rm->data.op_count = 0;
		पूर्ण

		rds_message_addref(rm);
		rm->data.op_dmasg = 0;
		rm->data.op_dmaoff = 0;
		ic->i_data_op = &rm->data;

		/* Finalize the header */
		अगर (test_bit(RDS_MSG_ACK_REQUIRED, &rm->m_flags))
			rm->m_inc.i_hdr.h_flags |= RDS_FLAG_ACK_REQUIRED;
		अगर (test_bit(RDS_MSG_RETRANSMITTED, &rm->m_flags))
			rm->m_inc.i_hdr.h_flags |= RDS_FLAG_RETRANSMITTED;

		/* If it has a RDMA op, tell the peer we did it. This is
		 * used by the peer to release use-once RDMA MRs. */
		अगर (rm->rdma.op_active) अणु
			काष्ठा rds_ext_header_rdma ext_hdr;

			ext_hdr.h_rdma_rkey = cpu_to_be32(rm->rdma.op_rkey);
			rds_message_add_extension(&rm->m_inc.i_hdr,
					RDS_EXTHDR_RDMA, &ext_hdr, माप(ext_hdr));
		पूर्ण
		अगर (rm->m_rdma_cookie) अणु
			rds_message_add_rdma_dest_extension(&rm->m_inc.i_hdr,
					rds_rdma_cookie_key(rm->m_rdma_cookie),
					rds_rdma_cookie_offset(rm->m_rdma_cookie));
		पूर्ण

		/* Note - rds_ib_piggyb_ack clears the ACK_REQUIRED bit, so
		 * we should not करो this unless we have a chance of at least
		 * sticking the header पूर्णांकo the send ring. Which is why we
		 * should call rds_ib_ring_alloc first. */
		rm->m_inc.i_hdr.h_ack = cpu_to_be64(rds_ib_piggyb_ack(ic));
		rds_message_make_checksum(&rm->m_inc.i_hdr);

		/*
		 * Update adv_credits since we reset the ACK_REQUIRED bit.
		 */
		अगर (ic->i_flowctl) अणु
			rds_ib_send_grab_credits(ic, 0, &posted, 1, RDS_MAX_ADV_CREDIT - adv_credits);
			adv_credits += posted;
			BUG_ON(adv_credits > 255);
		पूर्ण
	पूर्ण

	/* Someबार you want to put a fence between an RDMA
	 * READ and the following SEND.
	 * We could either करो this all the समय
	 * or when requested by the user. Right now, we let
	 * the application choose.
	 */
	अगर (rm->rdma.op_active && rm->rdma.op_fence)
		send_flags = IB_SEND_FENCE;

	/* Each frag माला_लो a header. Msgs may be 0 bytes */
	send = &ic->i_sends[pos];
	first = send;
	prev = शून्य;
	scat = &ic->i_data_op->op_sg[rm->data.op_dmasg];
	i = 0;
	करो अणु
		अचिन्हित पूर्णांक len = 0;

		/* Set up the header */
		send->s_wr.send_flags = send_flags;
		send->s_wr.opcode = IB_WR_SEND;
		send->s_wr.num_sge = 1;
		send->s_wr.next = शून्य;
		send->s_queued = jअगरfies;
		send->s_op = शून्य;

		send->s_sge[0].addr = ic->i_send_hdrs_dma[pos];

		send->s_sge[0].length = माप(काष्ठा rds_header);
		send->s_sge[0].lkey = ic->i_pd->local_dma_lkey;

		ib_dma_sync_single_क्रम_cpu(ic->rds_ibdev->dev,
					   ic->i_send_hdrs_dma[pos],
					   माप(काष्ठा rds_header),
					   DMA_TO_DEVICE);
		स_नकल(ic->i_send_hdrs[pos], &rm->m_inc.i_hdr,
		       माप(काष्ठा rds_header));


		/* Set up the data, अगर present */
		अगर (i < work_alloc
		    && scat != &rm->data.op_sg[rm->data.op_count]) अणु
			len = min(RDS_FRAG_SIZE,
				  sg_dma_len(scat) - rm->data.op_dmaoff);
			send->s_wr.num_sge = 2;

			send->s_sge[1].addr = sg_dma_address(scat);
			send->s_sge[1].addr += rm->data.op_dmaoff;
			send->s_sge[1].length = len;
			send->s_sge[1].lkey = ic->i_pd->local_dma_lkey;

			bytes_sent += len;
			rm->data.op_dmaoff += len;
			अगर (rm->data.op_dmaoff == sg_dma_len(scat)) अणु
				scat++;
				rm->data.op_dmasg++;
				rm->data.op_dmaoff = 0;
			पूर्ण
		पूर्ण

		rds_ib_set_wr_संकेत_state(ic, send, false);

		/*
		 * Always संकेत the last one अगर we're stopping due to flow control.
		 */
		अगर (ic->i_flowctl && flow_controlled && i == (work_alloc - 1)) अणु
			rds_ib_set_wr_संकेत_state(ic, send, true);
			send->s_wr.send_flags |= IB_SEND_SOLICITED;
		पूर्ण

		अगर (send->s_wr.send_flags & IB_SEND_SIGNALED)
			nr_sig++;

		rdsdebug("send %p wr %p num_sge %u next %p\n", send,
			 &send->s_wr, send->s_wr.num_sge, send->s_wr.next);

		अगर (ic->i_flowctl && adv_credits) अणु
			काष्ठा rds_header *hdr = ic->i_send_hdrs[pos];

			/* add credit and reकरो the header checksum */
			hdr->h_credit = adv_credits;
			rds_message_make_checksum(hdr);
			adv_credits = 0;
			rds_ib_stats_inc(s_ib_tx_credit_updates);
		पूर्ण
		ib_dma_sync_single_क्रम_device(ic->rds_ibdev->dev,
					      ic->i_send_hdrs_dma[pos],
					      माप(काष्ठा rds_header),
					      DMA_TO_DEVICE);

		अगर (prev)
			prev->s_wr.next = &send->s_wr;
		prev = send;

		pos = (pos + 1) % ic->i_send_ring.w_nr;
		send = &ic->i_sends[pos];
		i++;

	पूर्ण जबतक (i < work_alloc
		 && scat != &rm->data.op_sg[rm->data.op_count]);

	/* Account the RDS header in the number of bytes we sent, but just once.
	 * The caller has no concept of fragmentation. */
	अगर (hdr_off == 0)
		bytes_sent += माप(काष्ठा rds_header);

	/* अगर we finished the message then send completion owns it */
	अगर (scat == &rm->data.op_sg[rm->data.op_count]) अणु
		prev->s_op = ic->i_data_op;
		prev->s_wr.send_flags |= IB_SEND_SOLICITED;
		अगर (!(prev->s_wr.send_flags & IB_SEND_SIGNALED))
			nr_sig += rds_ib_set_wr_संकेत_state(ic, prev, true);
		ic->i_data_op = शून्य;
	पूर्ण

	/* Put back wrs & credits we didn't use */
	अगर (i < work_alloc) अणु
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc - i);
		work_alloc = i;
	पूर्ण
	अगर (ic->i_flowctl && i < credit_alloc)
		rds_ib_send_add_credits(conn, credit_alloc - i);

	अगर (nr_sig)
		atomic_add(nr_sig, &ic->i_संकेतed_sends);

	/* XXX need to worry about failed_wr and partial sends. */
	failed_wr = &first->s_wr;
	ret = ib_post_send(ic->i_cm_id->qp, &first->s_wr, &failed_wr);
	rdsdebug("ic %p first %p (wr %p) ret %d wr %p\n", ic,
		 first, &first->s_wr, ret, failed_wr);
	BUG_ON(failed_wr != &first->s_wr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "RDS/IB: ib_post_send to %pI6c "
		       "returned %d\n", &conn->c_faddr, ret);
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc);
		rds_ib_sub_संकेतed(ic, nr_sig);
		अगर (prev->s_op) अणु
			ic->i_data_op = prev->s_op;
			prev->s_op = शून्य;
		पूर्ण

		rds_ib_conn_error(ic->conn, "ib_post_send failed\n");
		जाओ out;
	पूर्ण

	ret = bytes_sent;
out:
	BUG_ON(adv_credits);
	वापस ret;
पूर्ण

/*
 * Issue atomic operation.
 * A simplअगरied version of the rdma हाल, we always map 1 SG, and
 * only 8 bytes, क्रम the वापस value from the atomic operation.
 */
पूर्णांक rds_ib_xmit_atomic(काष्ठा rds_connection *conn, काष्ठा rm_atomic_op *op)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा rds_ib_send_work *send = शून्य;
	स्थिर काष्ठा ib_send_wr *failed_wr;
	u32 pos;
	u32 work_alloc;
	पूर्णांक ret;
	पूर्णांक nr_sig = 0;

	work_alloc = rds_ib_ring_alloc(&ic->i_send_ring, 1, &pos);
	अगर (work_alloc != 1) अणु
		rds_ib_stats_inc(s_ib_tx_ring_full);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* address of send request in ring */
	send = &ic->i_sends[pos];
	send->s_queued = jअगरfies;

	अगर (op->op_type == RDS_ATOMIC_TYPE_CSWP) अणु
		send->s_atomic_wr.wr.opcode = IB_WR_MASKED_ATOMIC_CMP_AND_SWP;
		send->s_atomic_wr.compare_add = op->op_m_cswp.compare;
		send->s_atomic_wr.swap = op->op_m_cswp.swap;
		send->s_atomic_wr.compare_add_mask = op->op_m_cswp.compare_mask;
		send->s_atomic_wr.swap_mask = op->op_m_cswp.swap_mask;
	पूर्ण अन्यथा अणु /* FADD */
		send->s_atomic_wr.wr.opcode = IB_WR_MASKED_ATOMIC_FETCH_AND_ADD;
		send->s_atomic_wr.compare_add = op->op_m_fadd.add;
		send->s_atomic_wr.swap = 0;
		send->s_atomic_wr.compare_add_mask = op->op_m_fadd.nocarry_mask;
		send->s_atomic_wr.swap_mask = 0;
	पूर्ण
	send->s_wr.send_flags = 0;
	nr_sig = rds_ib_set_wr_संकेत_state(ic, send, op->op_notअगरy);
	send->s_atomic_wr.wr.num_sge = 1;
	send->s_atomic_wr.wr.next = शून्य;
	send->s_atomic_wr.remote_addr = op->op_remote_addr;
	send->s_atomic_wr.rkey = op->op_rkey;
	send->s_op = op;
	rds_message_addref(container_of(send->s_op, काष्ठा rds_message, atomic));

	/* map 8 byte retval buffer to the device */
	ret = ib_dma_map_sg(ic->i_cm_id->device, op->op_sg, 1, DMA_FROM_DEVICE);
	rdsdebug("ic %p mapping atomic op %p. mapped %d pg\n", ic, op, ret);
	अगर (ret != 1) अणु
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc);
		rds_ib_stats_inc(s_ib_tx_sg_mapping_failure);
		ret = -ENOMEM; /* XXX ? */
		जाओ out;
	पूर्ण

	/* Convert our काष्ठा scatterlist to काष्ठा ib_sge */
	send->s_sge[0].addr = sg_dma_address(op->op_sg);
	send->s_sge[0].length = sg_dma_len(op->op_sg);
	send->s_sge[0].lkey = ic->i_pd->local_dma_lkey;

	rdsdebug("rva %Lx rpa %Lx len %u\n", op->op_remote_addr,
		 send->s_sge[0].addr, send->s_sge[0].length);

	अगर (nr_sig)
		atomic_add(nr_sig, &ic->i_संकेतed_sends);

	failed_wr = &send->s_atomic_wr.wr;
	ret = ib_post_send(ic->i_cm_id->qp, &send->s_atomic_wr.wr, &failed_wr);
	rdsdebug("ic %p send %p (wr %p) ret %d wr %p\n", ic,
		 send, &send->s_atomic_wr, ret, failed_wr);
	BUG_ON(failed_wr != &send->s_atomic_wr.wr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "RDS/IB: atomic ib_post_send to %pI6c "
		       "returned %d\n", &conn->c_faddr, ret);
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc);
		rds_ib_sub_संकेतed(ic, nr_sig);
		जाओ out;
	पूर्ण

	अगर (unlikely(failed_wr != &send->s_atomic_wr.wr)) अणु
		prपूर्णांकk(KERN_WARNING "RDS/IB: atomic ib_post_send() rc=%d, but failed_wqe updated!\n", ret);
		BUG_ON(failed_wr != &send->s_atomic_wr.wr);
	पूर्ण

out:
	वापस ret;
पूर्ण

पूर्णांक rds_ib_xmit_rdma(काष्ठा rds_connection *conn, काष्ठा rm_rdma_op *op)
अणु
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;
	काष्ठा rds_ib_send_work *send = शून्य;
	काष्ठा rds_ib_send_work *first;
	काष्ठा rds_ib_send_work *prev;
	स्थिर काष्ठा ib_send_wr *failed_wr;
	काष्ठा scatterlist *scat;
	अचिन्हित दीर्घ len;
	u64 remote_addr = op->op_remote_addr;
	u32 max_sge = ic->rds_ibdev->max_sge;
	u32 pos;
	u32 work_alloc;
	u32 i;
	u32 j;
	पूर्णांक sent;
	पूर्णांक ret;
	पूर्णांक num_sge;
	पूर्णांक nr_sig = 0;
	u64 odp_addr = op->op_odp_addr;
	u32 odp_lkey = 0;

	/* map the op the first समय we see it */
	अगर (!op->op_odp_mr) अणु
		अगर (!op->op_mapped) अणु
			op->op_count =
				ib_dma_map_sg(ic->i_cm_id->device, op->op_sg,
					      op->op_nents,
					      (op->op_ग_लिखो) ? DMA_TO_DEVICE :
							       DMA_FROM_DEVICE);
			rdsdebug("ic %p mapping op %p: %d\n", ic, op,
				 op->op_count);
			अगर (op->op_count == 0) अणु
				rds_ib_stats_inc(s_ib_tx_sg_mapping_failure);
				ret = -ENOMEM; /* XXX ? */
				जाओ out;
			पूर्ण
			op->op_mapped = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		op->op_count = op->op_nents;
		odp_lkey = rds_ib_get_lkey(op->op_odp_mr->r_trans_निजी);
	पूर्ण

	/*
	 * Instead of knowing how to वापस a partial rdma पढ़ो/ग_लिखो we insist that there
	 * be enough work requests to send the entire message.
	 */
	i = DIV_ROUND_UP(op->op_count, max_sge);

	work_alloc = rds_ib_ring_alloc(&ic->i_send_ring, i, &pos);
	अगर (work_alloc != i) अणु
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc);
		rds_ib_stats_inc(s_ib_tx_ring_full);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	send = &ic->i_sends[pos];
	first = send;
	prev = शून्य;
	scat = &op->op_sg[0];
	sent = 0;
	num_sge = op->op_count;

	क्रम (i = 0; i < work_alloc && scat != &op->op_sg[op->op_count]; i++) अणु
		send->s_wr.send_flags = 0;
		send->s_queued = jअगरfies;
		send->s_op = शून्य;

		अगर (!op->op_notअगरy)
			nr_sig += rds_ib_set_wr_संकेत_state(ic, send,
							     op->op_notअगरy);

		send->s_wr.opcode = op->op_ग_लिखो ? IB_WR_RDMA_WRITE : IB_WR_RDMA_READ;
		send->s_rdma_wr.remote_addr = remote_addr;
		send->s_rdma_wr.rkey = op->op_rkey;

		अगर (num_sge > max_sge) अणु
			send->s_rdma_wr.wr.num_sge = max_sge;
			num_sge -= max_sge;
		पूर्ण अन्यथा अणु
			send->s_rdma_wr.wr.num_sge = num_sge;
		पूर्ण

		send->s_rdma_wr.wr.next = शून्य;

		अगर (prev)
			prev->s_rdma_wr.wr.next = &send->s_rdma_wr.wr;

		क्रम (j = 0; j < send->s_rdma_wr.wr.num_sge &&
		     scat != &op->op_sg[op->op_count]; j++) अणु
			len = sg_dma_len(scat);
			अगर (!op->op_odp_mr) अणु
				send->s_sge[j].addr = sg_dma_address(scat);
				send->s_sge[j].lkey = ic->i_pd->local_dma_lkey;
			पूर्ण अन्यथा अणु
				send->s_sge[j].addr = odp_addr;
				send->s_sge[j].lkey = odp_lkey;
			पूर्ण
			send->s_sge[j].length = len;

			sent += len;
			rdsdebug("ic %p sent %d remote_addr %llu\n", ic, sent, remote_addr);

			remote_addr += len;
			odp_addr += len;
			scat++;
		पूर्ण

		rdsdebug("send %p wr %p num_sge %u next %p\n", send,
			&send->s_rdma_wr.wr,
			send->s_rdma_wr.wr.num_sge,
			send->s_rdma_wr.wr.next);

		prev = send;
		अगर (++send == &ic->i_sends[ic->i_send_ring.w_nr])
			send = ic->i_sends;
	पूर्ण

	/* give a reference to the last op */
	अगर (scat == &op->op_sg[op->op_count]) अणु
		prev->s_op = op;
		rds_message_addref(container_of(op, काष्ठा rds_message, rdma));
	पूर्ण

	अगर (i < work_alloc) अणु
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc - i);
		work_alloc = i;
	पूर्ण

	अगर (nr_sig)
		atomic_add(nr_sig, &ic->i_संकेतed_sends);

	failed_wr = &first->s_rdma_wr.wr;
	ret = ib_post_send(ic->i_cm_id->qp, &first->s_rdma_wr.wr, &failed_wr);
	rdsdebug("ic %p first %p (wr %p) ret %d wr %p\n", ic,
		 first, &first->s_rdma_wr.wr, ret, failed_wr);
	BUG_ON(failed_wr != &first->s_rdma_wr.wr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "RDS/IB: rdma ib_post_send to %pI6c "
		       "returned %d\n", &conn->c_faddr, ret);
		rds_ib_ring_unalloc(&ic->i_send_ring, work_alloc);
		rds_ib_sub_संकेतed(ic, nr_sig);
		जाओ out;
	पूर्ण

	अगर (unlikely(failed_wr != &first->s_rdma_wr.wr)) अणु
		prपूर्णांकk(KERN_WARNING "RDS/IB: ib_post_send() rc=%d, but failed_wqe updated!\n", ret);
		BUG_ON(failed_wr != &first->s_rdma_wr.wr);
	पूर्ण


out:
	वापस ret;
पूर्ण

व्योम rds_ib_xmit_path_complete(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;
	काष्ठा rds_ib_connection *ic = conn->c_transport_data;

	/* We may have a pending ACK or winकरोw update we were unable
	 * to send previously (due to flow control). Try again. */
	rds_ib_attempt_ack(ic);
पूर्ण
