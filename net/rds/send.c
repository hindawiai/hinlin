<शैली गुरु>
/*
 * Copyright (c) 2006, 2018 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/gfp.h>
#समावेश <net/sock.h>
#समावेश <linux/in.h>
#समावेश <linux/list.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/export.h>
#समावेश <linux/sizes.h>

#समावेश "rds.h"

/* When transmitting messages in rds_send_xmit, we need to emerge from
 * समय to समय and briefly release the CPU. Otherwise the softlock watchकरोg
 * will kick our shin.
 * Also, it seems fairer to not let one busy connection stall all the
 * others.
 *
 * send_batch_count is the number of बार we'll loop in send_xmit. Setting
 * it to 0 will restore the old behavior (where we looped until we had
 * drained the queue).
 */
अटल पूर्णांक send_batch_count = SZ_1K;
module_param(send_batch_count, पूर्णांक, 0444);
MODULE_PARM_DESC(send_batch_count, " batch factor when working the send queue");

अटल व्योम rds_send_हटाओ_from_sock(काष्ठा list_head *messages, पूर्णांक status);

/*
 * Reset the send state.  Callers must ensure that this करोesn't race with
 * rds_send_xmit().
 */
व्योम rds_send_path_reset(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_message *rm, *पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (cp->cp_xmit_rm) अणु
		rm = cp->cp_xmit_rm;
		cp->cp_xmit_rm = शून्य;
		/* Tell the user the RDMA op is no दीर्घer mapped by the
		 * transport. This isn't entirely true (it's flushed out
		 * independently) but as the connection is करोwn, there's
		 * no ongoing RDMA to/from that memory */
		rds_message_unmapped(rm);
		rds_message_put(rm);
	पूर्ण

	cp->cp_xmit_sg = 0;
	cp->cp_xmit_hdr_off = 0;
	cp->cp_xmit_data_off = 0;
	cp->cp_xmit_atomic_sent = 0;
	cp->cp_xmit_rdma_sent = 0;
	cp->cp_xmit_data_sent = 0;

	cp->cp_conn->c_map_queued = 0;

	cp->cp_unacked_packets = rds_sysctl_max_unacked_packets;
	cp->cp_unacked_bytes = rds_sysctl_max_unacked_bytes;

	/* Mark messages as retransmissions, and move them to the send q */
	spin_lock_irqsave(&cp->cp_lock, flags);
	list_क्रम_each_entry_safe(rm, पंचांगp, &cp->cp_retrans, m_conn_item) अणु
		set_bit(RDS_MSG_ACK_REQUIRED, &rm->m_flags);
		set_bit(RDS_MSG_RETRANSMITTED, &rm->m_flags);
	पूर्ण
	list_splice_init(&cp->cp_retrans, &cp->cp_send_queue);
	spin_unlock_irqrestore(&cp->cp_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rds_send_path_reset);

अटल पूर्णांक acquire_in_xmit(काष्ठा rds_conn_path *cp)
अणु
	वापस test_and_set_bit(RDS_IN_XMIT, &cp->cp_flags) == 0;
पूर्ण

अटल व्योम release_in_xmit(काष्ठा rds_conn_path *cp)
अणु
	clear_bit(RDS_IN_XMIT, &cp->cp_flags);
	smp_mb__after_atomic();
	/*
	 * We करोn't use रुको_on_bit()/wake_up_bit() because our waking is in a
	 * hot path and finding रुकोers is very rare.  We करोn't want to walk
	 * the प्रणाली-wide hashed रुकोqueue buckets in the fast path only to
	 * almost never find रुकोers.
	 */
	अगर (रुकोqueue_active(&cp->cp_रुकोq))
		wake_up_all(&cp->cp_रुकोq);
पूर्ण

/*
 * We're making the conscious trade-off here to only send one message
 * करोwn the connection at a समय.
 *   Pro:
 *      - tx queueing is a simple fअगरo list
 *   	- reassembly is optional and easily करोne by transports per conn
 *      - no per flow rx lookup at all, straight to the socket
 *   	- less per-frag memory and wire overhead
 *   Con:
 *      - queued acks can be delayed behind large messages
 *   Depends:
 *      - small message latency is higher behind queued large messages
 *      - large message latency isn't starved by पूर्णांकervening small sends
 */
पूर्णांक rds_send_xmit(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;
	काष्ठा rds_message *rm;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा scatterlist *sg;
	पूर्णांक ret = 0;
	LIST_HEAD(to_be_dropped);
	पूर्णांक batch_count;
	अचिन्हित दीर्घ send_gen = 0;
	पूर्णांक same_rm = 0;

restart:
	batch_count = 0;

	/*
	 * sendmsg calls here after having queued its message on the send
	 * queue.  We only have one task feeding the connection at a समय.  If
	 * another thपढ़ो is alपढ़ोy feeding the queue then we back off.  This
	 * aव्योमs blocking the caller and trading per-connection data between
	 * caches per message.
	 */
	अगर (!acquire_in_xmit(cp)) अणु
		rds_stats_inc(s_send_lock_contention);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (rds_destroy_pending(cp->cp_conn)) अणु
		release_in_xmit(cp);
		ret = -ENETUNREACH; /* करोnt requeue send work */
		जाओ out;
	पूर्ण

	/*
	 * we record the send generation after करोing the xmit acquire.
	 * अगर someone अन्यथा manages to jump in and करो some work, we'll use
	 * this to aव्योम a जाओ restart farther करोwn.
	 *
	 * The acquire_in_xmit() check above ensures that only one
	 * caller can increment c_send_gen at any समय.
	 */
	send_gen = READ_ONCE(cp->cp_send_gen) + 1;
	WRITE_ONCE(cp->cp_send_gen, send_gen);

	/*
	 * rds_conn_shutकरोwn() sets the conn state and then tests RDS_IN_XMIT,
	 * we करो the opposite to aव्योम races.
	 */
	अगर (!rds_conn_path_up(cp)) अणु
		release_in_xmit(cp);
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (conn->c_trans->xmit_path_prepare)
		conn->c_trans->xmit_path_prepare(cp);

	/*
	 * spin trying to push headers and data करोwn the connection until
	 * the connection करोesn't make क्रमward progress.
	 */
	जबतक (1) अणु

		rm = cp->cp_xmit_rm;

		अगर (!rm) अणु
			same_rm = 0;
		पूर्ण अन्यथा अणु
			same_rm++;
			अगर (same_rm >= 4096) अणु
				rds_stats_inc(s_send_stuck_rm);
				ret = -EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If between sending messages, we can send a pending congestion
		 * map update.
		 */
		अगर (!rm && test_and_clear_bit(0, &conn->c_map_queued)) अणु
			rm = rds_cong_update_alloc(conn);
			अगर (IS_ERR(rm)) अणु
				ret = PTR_ERR(rm);
				अवरोध;
			पूर्ण
			rm->data.op_active = 1;
			rm->m_inc.i_conn_path = cp;
			rm->m_inc.i_conn = cp->cp_conn;

			cp->cp_xmit_rm = rm;
		पूर्ण

		/*
		 * If not alपढ़ोy working on one, grab the next message.
		 *
		 * cp_xmit_rm holds a ref जबतक we're sending this message करोwn
		 * the connction.  We can use this ref जबतक holding the
		 * send_sem.. rds_send_reset() is serialized with it.
		 */
		अगर (!rm) अणु
			अचिन्हित पूर्णांक len;

			batch_count++;

			/* we want to process as big a batch as we can, but
			 * we also want to aव्योम softlockups.  If we've been
			 * through a lot of messages, lets back off and see
			 * अगर anyone अन्यथा jumps in
			 */
			अगर (batch_count >= send_batch_count)
				जाओ over_batch;

			spin_lock_irqsave(&cp->cp_lock, flags);

			अगर (!list_empty(&cp->cp_send_queue)) अणु
				rm = list_entry(cp->cp_send_queue.next,
						काष्ठा rds_message,
						m_conn_item);
				rds_message_addref(rm);

				/*
				 * Move the message from the send queue to the retransmit
				 * list right away.
				 */
				list_move_tail(&rm->m_conn_item,
					       &cp->cp_retrans);
			पूर्ण

			spin_unlock_irqrestore(&cp->cp_lock, flags);

			अगर (!rm)
				अवरोध;

			/* Unक्रमtunately, the way Infiniband deals with
			 * RDMA to a bad MR key is by moving the entire
			 * queue pair to error state. We cold possibly
			 * recover from that, but right now we drop the
			 * connection.
			 * Thereक्रमe, we never retransmit messages with RDMA ops.
			 */
			अगर (test_bit(RDS_MSG_FLUSH, &rm->m_flags) ||
			    (rm->rdma.op_active &&
			    test_bit(RDS_MSG_RETRANSMITTED, &rm->m_flags))) अणु
				spin_lock_irqsave(&cp->cp_lock, flags);
				अगर (test_and_clear_bit(RDS_MSG_ON_CONN, &rm->m_flags))
					list_move(&rm->m_conn_item, &to_be_dropped);
				spin_unlock_irqrestore(&cp->cp_lock, flags);
				जारी;
			पूर्ण

			/* Require an ACK every once in a जबतक */
			len = ntohl(rm->m_inc.i_hdr.h_len);
			अगर (cp->cp_unacked_packets == 0 ||
			    cp->cp_unacked_bytes < len) अणु
				set_bit(RDS_MSG_ACK_REQUIRED, &rm->m_flags);

				cp->cp_unacked_packets =
					rds_sysctl_max_unacked_packets;
				cp->cp_unacked_bytes =
					rds_sysctl_max_unacked_bytes;
				rds_stats_inc(s_send_ack_required);
			पूर्ण अन्यथा अणु
				cp->cp_unacked_bytes -= len;
				cp->cp_unacked_packets--;
			पूर्ण

			cp->cp_xmit_rm = rm;
		पूर्ण

		/* The transport either sends the whole rdma or none of it */
		अगर (rm->rdma.op_active && !cp->cp_xmit_rdma_sent) अणु
			rm->m_final_op = &rm->rdma;
			/* The transport owns the mapped memory क्रम now.
			 * You can't unmap it while it's on the send queue
			 */
			set_bit(RDS_MSG_MAPPED, &rm->m_flags);
			ret = conn->c_trans->xmit_rdma(conn, &rm->rdma);
			अगर (ret) अणु
				clear_bit(RDS_MSG_MAPPED, &rm->m_flags);
				wake_up_पूर्णांकerruptible(&rm->m_flush_रुको);
				अवरोध;
			पूर्ण
			cp->cp_xmit_rdma_sent = 1;

		पूर्ण

		अगर (rm->atomic.op_active && !cp->cp_xmit_atomic_sent) अणु
			rm->m_final_op = &rm->atomic;
			/* The transport owns the mapped memory क्रम now.
			 * You can't unmap it while it's on the send queue
			 */
			set_bit(RDS_MSG_MAPPED, &rm->m_flags);
			ret = conn->c_trans->xmit_atomic(conn, &rm->atomic);
			अगर (ret) अणु
				clear_bit(RDS_MSG_MAPPED, &rm->m_flags);
				wake_up_पूर्णांकerruptible(&rm->m_flush_रुको);
				अवरोध;
			पूर्ण
			cp->cp_xmit_atomic_sent = 1;

		पूर्ण

		/*
		 * A number of हालs require an RDS header to be sent
		 * even अगर there is no data.
		 * We permit 0-byte sends; rds-ping depends on this.
		 * However, अगर there are exclusively attached silent ops,
		 * we skip the hdr/data send, to enable silent operation.
		 */
		अगर (rm->data.op_nents == 0) अणु
			पूर्णांक ops_present;
			पूर्णांक all_ops_are_silent = 1;

			ops_present = (rm->atomic.op_active || rm->rdma.op_active);
			अगर (rm->atomic.op_active && !rm->atomic.op_silent)
				all_ops_are_silent = 0;
			अगर (rm->rdma.op_active && !rm->rdma.op_silent)
				all_ops_are_silent = 0;

			अगर (ops_present && all_ops_are_silent
			    && !rm->m_rdma_cookie)
				rm->data.op_active = 0;
		पूर्ण

		अगर (rm->data.op_active && !cp->cp_xmit_data_sent) अणु
			rm->m_final_op = &rm->data;

			ret = conn->c_trans->xmit(conn, rm,
						  cp->cp_xmit_hdr_off,
						  cp->cp_xmit_sg,
						  cp->cp_xmit_data_off);
			अगर (ret <= 0)
				अवरोध;

			अगर (cp->cp_xmit_hdr_off < माप(काष्ठा rds_header)) अणु
				पंचांगp = min_t(पूर्णांक, ret,
					    माप(काष्ठा rds_header) -
					    cp->cp_xmit_hdr_off);
				cp->cp_xmit_hdr_off += पंचांगp;
				ret -= पंचांगp;
			पूर्ण

			sg = &rm->data.op_sg[cp->cp_xmit_sg];
			जबतक (ret) अणु
				पंचांगp = min_t(पूर्णांक, ret, sg->length -
						      cp->cp_xmit_data_off);
				cp->cp_xmit_data_off += पंचांगp;
				ret -= पंचांगp;
				अगर (cp->cp_xmit_data_off == sg->length) अणु
					cp->cp_xmit_data_off = 0;
					sg++;
					cp->cp_xmit_sg++;
					BUG_ON(ret != 0 && cp->cp_xmit_sg ==
					       rm->data.op_nents);
				पूर्ण
			पूर्ण

			अगर (cp->cp_xmit_hdr_off == माप(काष्ठा rds_header) &&
			    (cp->cp_xmit_sg == rm->data.op_nents))
				cp->cp_xmit_data_sent = 1;
		पूर्ण

		/*
		 * A rm will only take multiple बार through this loop
		 * अगर there is a data op. Thus, अगर the data is sent (or there was
		 * none), then we're करोne with the rm.
		 */
		अगर (!rm->data.op_active || cp->cp_xmit_data_sent) अणु
			cp->cp_xmit_rm = शून्य;
			cp->cp_xmit_sg = 0;
			cp->cp_xmit_hdr_off = 0;
			cp->cp_xmit_data_off = 0;
			cp->cp_xmit_rdma_sent = 0;
			cp->cp_xmit_atomic_sent = 0;
			cp->cp_xmit_data_sent = 0;

			rds_message_put(rm);
		पूर्ण
	पूर्ण

over_batch:
	अगर (conn->c_trans->xmit_path_complete)
		conn->c_trans->xmit_path_complete(cp);
	release_in_xmit(cp);

	/* Nuke any messages we decided not to retransmit. */
	अगर (!list_empty(&to_be_dropped)) अणु
		/* irqs on here, so we can put(), unlike above */
		list_क्रम_each_entry(rm, &to_be_dropped, m_conn_item)
			rds_message_put(rm);
		rds_send_हटाओ_from_sock(&to_be_dropped, RDS_RDMA_DROPPED);
	पूर्ण

	/*
	 * Other senders can queue a message after we last test the send queue
	 * but beक्रमe we clear RDS_IN_XMIT.  In that हाल they'd back off and
	 * not try and send their newly queued message.  We need to check the
	 * send queue after having cleared RDS_IN_XMIT so that their message
	 * करोesn't get stuck on the send queue.
	 *
	 * If the transport cannot जारी (i.e ret != 0), then it must
	 * call us when more room is available, such as from the tx
	 * completion handler.
	 *
	 * We have an extra generation check here so that अगर someone manages
	 * to jump in after our release_in_xmit, we'll see that they have करोne
	 * some work and we will skip our जाओ
	 */
	अगर (ret == 0) अणु
		bool raced;

		smp_mb();
		raced = send_gen != READ_ONCE(cp->cp_send_gen);

		अगर ((test_bit(0, &conn->c_map_queued) ||
		    !list_empty(&cp->cp_send_queue)) && !raced) अणु
			अगर (batch_count < send_batch_count)
				जाओ restart;
			rcu_पढ़ो_lock();
			अगर (rds_destroy_pending(cp->cp_conn))
				ret = -ENETUNREACH;
			अन्यथा
				queue_delayed_work(rds_wq, &cp->cp_send_w, 1);
			rcu_पढ़ो_unlock();
		पूर्ण अन्यथा अगर (raced) अणु
			rds_stats_inc(s_send_lock_queue_raced);
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rds_send_xmit);

अटल व्योम rds_send_sndbuf_हटाओ(काष्ठा rds_sock *rs, काष्ठा rds_message *rm)
अणु
	u32 len = be32_to_cpu(rm->m_inc.i_hdr.h_len);

	निश्चित_spin_locked(&rs->rs_lock);

	BUG_ON(rs->rs_snd_bytes < len);
	rs->rs_snd_bytes -= len;

	अगर (rs->rs_snd_bytes == 0)
		rds_stats_inc(s_send_queue_empty);
पूर्ण

अटल अंतरभूत पूर्णांक rds_send_is_acked(काष्ठा rds_message *rm, u64 ack,
				    is_acked_func is_acked)
अणु
	अगर (is_acked)
		वापस is_acked(rm, ack);
	वापस be64_to_cpu(rm->m_inc.i_hdr.h_sequence) <= ack;
पूर्ण

/*
 * This is pretty similar to what happens below in the ACK
 * handling code - except that we call here as soon as we get
 * the IB send completion on the RDMA op and the accompanying
 * message.
 */
व्योम rds_rdma_send_complete(काष्ठा rds_message *rm, पूर्णांक status)
अणु
	काष्ठा rds_sock *rs = शून्य;
	काष्ठा rm_rdma_op *ro;
	काष्ठा rds_notअगरier *notअगरier;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rm->m_rs_lock, flags);

	ro = &rm->rdma;
	अगर (test_bit(RDS_MSG_ON_SOCK, &rm->m_flags) &&
	    ro->op_active && ro->op_notअगरy && ro->op_notअगरier) अणु
		notअगरier = ro->op_notअगरier;
		rs = rm->m_rs;
		sock_hold(rds_rs_to_sk(rs));

		notअगरier->n_status = status;
		spin_lock(&rs->rs_lock);
		list_add_tail(&notअगरier->n_list, &rs->rs_notअगरy_queue);
		spin_unlock(&rs->rs_lock);

		ro->op_notअगरier = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&rm->m_rs_lock, flags);

	अगर (rs) अणु
		rds_wake_sk_sleep(rs);
		sock_put(rds_rs_to_sk(rs));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_rdma_send_complete);

/*
 * Just like above, except looks at atomic op
 */
व्योम rds_atomic_send_complete(काष्ठा rds_message *rm, पूर्णांक status)
अणु
	काष्ठा rds_sock *rs = शून्य;
	काष्ठा rm_atomic_op *ao;
	काष्ठा rds_notअगरier *notअगरier;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rm->m_rs_lock, flags);

	ao = &rm->atomic;
	अगर (test_bit(RDS_MSG_ON_SOCK, &rm->m_flags)
	    && ao->op_active && ao->op_notअगरy && ao->op_notअगरier) अणु
		notअगरier = ao->op_notअगरier;
		rs = rm->m_rs;
		sock_hold(rds_rs_to_sk(rs));

		notअगरier->n_status = status;
		spin_lock(&rs->rs_lock);
		list_add_tail(&notअगरier->n_list, &rs->rs_notअगरy_queue);
		spin_unlock(&rs->rs_lock);

		ao->op_notअगरier = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&rm->m_rs_lock, flags);

	अगर (rs) अणु
		rds_wake_sk_sleep(rs);
		sock_put(rds_rs_to_sk(rs));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_atomic_send_complete);

/*
 * This is the same as rds_rdma_send_complete except we
 * करोn't करो any locking - we have all the ingredients (message,
 * socket, socket lock) and can just move the notअगरier.
 */
अटल अंतरभूत व्योम
__rds_send_complete(काष्ठा rds_sock *rs, काष्ठा rds_message *rm, पूर्णांक status)
अणु
	काष्ठा rm_rdma_op *ro;
	काष्ठा rm_atomic_op *ao;

	ro = &rm->rdma;
	अगर (ro->op_active && ro->op_notअगरy && ro->op_notअगरier) अणु
		ro->op_notअगरier->n_status = status;
		list_add_tail(&ro->op_notअगरier->n_list, &rs->rs_notअगरy_queue);
		ro->op_notअगरier = शून्य;
	पूर्ण

	ao = &rm->atomic;
	अगर (ao->op_active && ao->op_notअगरy && ao->op_notअगरier) अणु
		ao->op_notअगरier->n_status = status;
		list_add_tail(&ao->op_notअगरier->n_list, &rs->rs_notअगरy_queue);
		ao->op_notअगरier = शून्य;
	पूर्ण

	/* No need to wake the app - caller करोes this */
पूर्ण

/*
 * This हटाओs messages from the socket's list if they're on it.  The list
 * argument must be निजी to the caller, we must be able to modअगरy it
 * without locks.  The messages must have a reference held क्रम their
 * position on the list.  This function will drop that reference after
 * removing the messages from the 'messages' list regardless of अगर it found
 * the messages on the socket list or not.
 */
अटल व्योम rds_send_हटाओ_from_sock(काष्ठा list_head *messages, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rds_sock *rs = शून्य;
	काष्ठा rds_message *rm;

	जबतक (!list_empty(messages)) अणु
		पूर्णांक was_on_sock = 0;

		rm = list_entry(messages->next, काष्ठा rds_message,
				m_conn_item);
		list_del_init(&rm->m_conn_item);

		/*
		 * If we see this flag cleared then we're *sure* that someone
		 * अन्यथा beat us to removing it from the sock.  If we race
		 * with their flag update we'll get the lock and then really
		 * see that the flag has been cleared.
		 *
		 * The message spinlock makes sure nobody clears rm->m_rs
		 * जबतक we're messing with it. It करोes not prevent the
		 * message from being हटाओd from the socket, though.
		 */
		spin_lock_irqsave(&rm->m_rs_lock, flags);
		अगर (!test_bit(RDS_MSG_ON_SOCK, &rm->m_flags))
			जाओ unlock_and_drop;

		अगर (rs != rm->m_rs) अणु
			अगर (rs) अणु
				rds_wake_sk_sleep(rs);
				sock_put(rds_rs_to_sk(rs));
			पूर्ण
			rs = rm->m_rs;
			अगर (rs)
				sock_hold(rds_rs_to_sk(rs));
		पूर्ण
		अगर (!rs)
			जाओ unlock_and_drop;
		spin_lock(&rs->rs_lock);

		अगर (test_and_clear_bit(RDS_MSG_ON_SOCK, &rm->m_flags)) अणु
			काष्ठा rm_rdma_op *ro = &rm->rdma;
			काष्ठा rds_notअगरier *notअगरier;

			list_del_init(&rm->m_sock_item);
			rds_send_sndbuf_हटाओ(rs, rm);

			अगर (ro->op_active && ro->op_notअगरier &&
			       (ro->op_notअगरy || (ro->op_recverr && status))) अणु
				notअगरier = ro->op_notअगरier;
				list_add_tail(&notअगरier->n_list,
						&rs->rs_notअगरy_queue);
				अगर (!notअगरier->n_status)
					notअगरier->n_status = status;
				rm->rdma.op_notअगरier = शून्य;
			पूर्ण
			was_on_sock = 1;
		पूर्ण
		spin_unlock(&rs->rs_lock);

unlock_and_drop:
		spin_unlock_irqrestore(&rm->m_rs_lock, flags);
		rds_message_put(rm);
		अगर (was_on_sock)
			rds_message_put(rm);
	पूर्ण

	अगर (rs) अणु
		rds_wake_sk_sleep(rs);
		sock_put(rds_rs_to_sk(rs));
	पूर्ण
पूर्ण

/*
 * Transports call here when they've determined that the receiver queued
 * messages up to, and including, the given sequence number.  Messages are
 * moved to the retrans queue when rds_send_xmit picks them off the send
 * queue. This means that in the TCP हाल, the message may not have been
 * asचिन्हित the m_ack_seq yet - but that's fine as दीर्घ as tcp_is_acked
 * checks the RDS_MSG_HAS_ACK_SEQ bit.
 */
व्योम rds_send_path_drop_acked(काष्ठा rds_conn_path *cp, u64 ack,
			      is_acked_func is_acked)
अणु
	काष्ठा rds_message *rm, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	spin_lock_irqsave(&cp->cp_lock, flags);

	list_क्रम_each_entry_safe(rm, पंचांगp, &cp->cp_retrans, m_conn_item) अणु
		अगर (!rds_send_is_acked(rm, ack, is_acked))
			अवरोध;

		list_move(&rm->m_conn_item, &list);
		clear_bit(RDS_MSG_ON_CONN, &rm->m_flags);
	पूर्ण

	/* order flag updates with spin locks */
	अगर (!list_empty(&list))
		smp_mb__after_atomic();

	spin_unlock_irqrestore(&cp->cp_lock, flags);

	/* now हटाओ the messages from the sock list as needed */
	rds_send_हटाओ_from_sock(&list, RDS_RDMA_SUCCESS);
पूर्ण
EXPORT_SYMBOL_GPL(rds_send_path_drop_acked);

व्योम rds_send_drop_acked(काष्ठा rds_connection *conn, u64 ack,
			 is_acked_func is_acked)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	rds_send_path_drop_acked(&conn->c_path[0], ack, is_acked);
पूर्ण
EXPORT_SYMBOL_GPL(rds_send_drop_acked);

व्योम rds_send_drop_to(काष्ठा rds_sock *rs, काष्ठा sockaddr_in6 *dest)
अणु
	काष्ठा rds_message *rm, *पंचांगp;
	काष्ठा rds_connection *conn;
	काष्ठा rds_conn_path *cp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	/* get all the messages we're dropping under the rs lock */
	spin_lock_irqsave(&rs->rs_lock, flags);

	list_क्रम_each_entry_safe(rm, पंचांगp, &rs->rs_send_queue, m_sock_item) अणु
		अगर (dest &&
		    (!ipv6_addr_equal(&dest->sin6_addr, &rm->m_daddr) ||
		     dest->sin6_port != rm->m_inc.i_hdr.h_dport))
			जारी;

		list_move(&rm->m_sock_item, &list);
		rds_send_sndbuf_हटाओ(rs, rm);
		clear_bit(RDS_MSG_ON_SOCK, &rm->m_flags);
	पूर्ण

	/* order flag updates with the rs lock */
	smp_mb__after_atomic();

	spin_unlock_irqrestore(&rs->rs_lock, flags);

	अगर (list_empty(&list))
		वापस;

	/* Remove the messages from the conn */
	list_क्रम_each_entry(rm, &list, m_sock_item) अणु

		conn = rm->m_inc.i_conn;
		अगर (conn->c_trans->t_mp_capable)
			cp = rm->m_inc.i_conn_path;
		अन्यथा
			cp = &conn->c_path[0];

		spin_lock_irqsave(&cp->cp_lock, flags);
		/*
		 * Maybe someone अन्यथा beat us to removing rm from the conn.
		 * If we race with their flag update we'll get the lock and
		 * then really see that the flag has been cleared.
		 */
		अगर (!test_and_clear_bit(RDS_MSG_ON_CONN, &rm->m_flags)) अणु
			spin_unlock_irqrestore(&cp->cp_lock, flags);
			जारी;
		पूर्ण
		list_del_init(&rm->m_conn_item);
		spin_unlock_irqrestore(&cp->cp_lock, flags);

		/*
		 * Couldn't grab m_rs_lock in top loop (lock ordering),
		 * but we can now.
		 */
		spin_lock_irqsave(&rm->m_rs_lock, flags);

		spin_lock(&rs->rs_lock);
		__rds_send_complete(rs, rm, RDS_RDMA_CANCELED);
		spin_unlock(&rs->rs_lock);

		spin_unlock_irqrestore(&rm->m_rs_lock, flags);

		rds_message_put(rm);
	पूर्ण

	rds_wake_sk_sleep(rs);

	जबतक (!list_empty(&list)) अणु
		rm = list_entry(list.next, काष्ठा rds_message, m_sock_item);
		list_del_init(&rm->m_sock_item);
		rds_message_रुको(rm);

		/* just in हाल the code above skipped this message
		 * because RDS_MSG_ON_CONN wasn't set, run it again here
		 * taking m_rs_lock is the only thing that keeps us
		 * from racing with ack processing.
		 */
		spin_lock_irqsave(&rm->m_rs_lock, flags);

		spin_lock(&rs->rs_lock);
		__rds_send_complete(rs, rm, RDS_RDMA_CANCELED);
		spin_unlock(&rs->rs_lock);

		spin_unlock_irqrestore(&rm->m_rs_lock, flags);

		rds_message_put(rm);
	पूर्ण
पूर्ण

/*
 * we only want this to fire once so we use the callers 'queued'.  It's
 * possible that another thपढ़ो can race with us and हटाओ the
 * message from the flow with RDS_CANCEL_SENT_TO.
 */
अटल पूर्णांक rds_send_queue_rm(काष्ठा rds_sock *rs, काष्ठा rds_connection *conn,
			     काष्ठा rds_conn_path *cp,
			     काष्ठा rds_message *rm, __be16 sport,
			     __be16 dport, पूर्णांक *queued)
अणु
	अचिन्हित दीर्घ flags;
	u32 len;

	अगर (*queued)
		जाओ out;

	len = be32_to_cpu(rm->m_inc.i_hdr.h_len);

	/* this is the only place which holds both the socket's rs_lock
	 * and the connection's c_lock */
	spin_lock_irqsave(&rs->rs_lock, flags);

	/*
	 * If there is a little space in sndbuf, we करोn't queue anything,
	 * and userspace माला_लो -EAGAIN. But poll() indicates there's send
	 * room. This can lead to bad behavior (spinning) अगर snd_bytes isn't
	 * मुक्तd up by incoming acks. So we check the *old* value of
	 * rs_snd_bytes here to allow the last msg to exceed the buffer,
	 * and poll() now knows no more data can be sent.
	 */
	अगर (rs->rs_snd_bytes < rds_sk_sndbuf(rs)) अणु
		rs->rs_snd_bytes += len;

		/* let recv side know we are बंद to send space exhaustion.
		 * This is probably not the optimal way to करो it, as this
		 * means we set the flag on *all* messages as soon as our
		 * throughput hits a certain threshold.
		 */
		अगर (rs->rs_snd_bytes >= rds_sk_sndbuf(rs) / 2)
			set_bit(RDS_MSG_ACK_REQUIRED, &rm->m_flags);

		list_add_tail(&rm->m_sock_item, &rs->rs_send_queue);
		set_bit(RDS_MSG_ON_SOCK, &rm->m_flags);
		rds_message_addref(rm);
		sock_hold(rds_rs_to_sk(rs));
		rm->m_rs = rs;

		/* The code ordering is a little weird, but we're
		   trying to minimize the समय we hold c_lock */
		rds_message_populate_header(&rm->m_inc.i_hdr, sport, dport, 0);
		rm->m_inc.i_conn = conn;
		rm->m_inc.i_conn_path = cp;
		rds_message_addref(rm);

		spin_lock(&cp->cp_lock);
		rm->m_inc.i_hdr.h_sequence = cpu_to_be64(cp->cp_next_tx_seq++);
		list_add_tail(&rm->m_conn_item, &cp->cp_send_queue);
		set_bit(RDS_MSG_ON_CONN, &rm->m_flags);
		spin_unlock(&cp->cp_lock);

		rdsdebug("queued msg %p len %d, rs %p bytes %d seq %llu\n",
			 rm, len, rs, rs->rs_snd_bytes,
			 (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(rm->m_inc.i_hdr.h_sequence));

		*queued = 1;
	पूर्ण

	spin_unlock_irqrestore(&rs->rs_lock, flags);
out:
	वापस *queued;
पूर्ण

/*
 * rds_message is getting to be quite complicated, and we'd like to allocate
 * it all in one go. This figures out how big it needs to be up front.
 */
अटल पूर्णांक rds_rm_size(काष्ठा msghdr *msg, पूर्णांक num_sgs,
		       काष्ठा rds_iov_vector_arr *vct)
अणु
	काष्ठा cmsghdr *cmsg;
	पूर्णांक size = 0;
	पूर्णांक cmsg_groups = 0;
	पूर्णांक retval;
	bool zcopy_cookie = false;
	काष्ठा rds_iov_vector *iov, *पंचांगp_iov;

	अगर (num_sgs < 0)
		वापस -EINVAL;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;

		अगर (cmsg->cmsg_level != SOL_RDS)
			जारी;

		चयन (cmsg->cmsg_type) अणु
		हाल RDS_CMSG_RDMA_ARGS:
			अगर (vct->indx >= vct->len) अणु
				vct->len += vct->incr;
				पंचांगp_iov =
					kपुनः_स्मृति(vct->vec,
						 vct->len *
						 माप(काष्ठा rds_iov_vector),
						 GFP_KERNEL);
				अगर (!पंचांगp_iov) अणु
					vct->len -= vct->incr;
					वापस -ENOMEM;
				पूर्ण
				vct->vec = पंचांगp_iov;
			पूर्ण
			iov = &vct->vec[vct->indx];
			स_रखो(iov, 0, माप(काष्ठा rds_iov_vector));
			vct->indx++;
			cmsg_groups |= 1;
			retval = rds_rdma_extra_size(CMSG_DATA(cmsg), iov);
			अगर (retval < 0)
				वापस retval;
			size += retval;

			अवरोध;

		हाल RDS_CMSG_ZCOPY_COOKIE:
			zcopy_cookie = true;
			fallthrough;

		हाल RDS_CMSG_RDMA_DEST:
		हाल RDS_CMSG_RDMA_MAP:
			cmsg_groups |= 2;
			/* these are valid but करो no add any size */
			अवरोध;

		हाल RDS_CMSG_ATOMIC_CSWP:
		हाल RDS_CMSG_ATOMIC_FADD:
		हाल RDS_CMSG_MASKED_ATOMIC_CSWP:
		हाल RDS_CMSG_MASKED_ATOMIC_FADD:
			cmsg_groups |= 1;
			size += माप(काष्ठा scatterlist);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण

	अगर ((msg->msg_flags & MSG_ZEROCOPY) && !zcopy_cookie)
		वापस -EINVAL;

	size += num_sgs * माप(काष्ठा scatterlist);

	/* Ensure (DEST, MAP) are never used with (ARGS, ATOMIC) */
	अगर (cmsg_groups == 3)
		वापस -EINVAL;

	वापस size;
पूर्ण

अटल पूर्णांक rds_cmsg_zcopy(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			  काष्ठा cmsghdr *cmsg)
अणु
	u32 *cookie;

	अगर (cmsg->cmsg_len < CMSG_LEN(माप(*cookie)) ||
	    !rm->data.op_mmp_znotअगरier)
		वापस -EINVAL;
	cookie = CMSG_DATA(cmsg);
	rm->data.op_mmp_znotअगरier->z_cookie = *cookie;
	वापस 0;
पूर्ण

अटल पूर्णांक rds_cmsg_send(काष्ठा rds_sock *rs, काष्ठा rds_message *rm,
			 काष्ठा msghdr *msg, पूर्णांक *allocated_mr,
			 काष्ठा rds_iov_vector_arr *vct)
अणु
	काष्ठा cmsghdr *cmsg;
	पूर्णांक ret = 0, ind = 0;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;

		अगर (cmsg->cmsg_level != SOL_RDS)
			जारी;

		/* As a side effect, RDMA_DEST and RDMA_MAP will set
		 * rm->rdma.m_rdma_cookie and rm->rdma.m_rdma_mr.
		 */
		चयन (cmsg->cmsg_type) अणु
		हाल RDS_CMSG_RDMA_ARGS:
			अगर (ind >= vct->indx)
				वापस -ENOMEM;
			ret = rds_cmsg_rdma_args(rs, rm, cmsg, &vct->vec[ind]);
			ind++;
			अवरोध;

		हाल RDS_CMSG_RDMA_DEST:
			ret = rds_cmsg_rdma_dest(rs, rm, cmsg);
			अवरोध;

		हाल RDS_CMSG_RDMA_MAP:
			ret = rds_cmsg_rdma_map(rs, rm, cmsg);
			अगर (!ret)
				*allocated_mr = 1;
			अन्यथा अगर (ret == -ENODEV)
				/* Accommodate the get_mr() हाल which can fail
				 * अगर connection isn't established yet.
				 */
				ret = -EAGAIN;
			अवरोध;
		हाल RDS_CMSG_ATOMIC_CSWP:
		हाल RDS_CMSG_ATOMIC_FADD:
		हाल RDS_CMSG_MASKED_ATOMIC_CSWP:
		हाल RDS_CMSG_MASKED_ATOMIC_FADD:
			ret = rds_cmsg_atomic(rs, rm, cmsg);
			अवरोध;

		हाल RDS_CMSG_ZCOPY_COOKIE:
			ret = rds_cmsg_zcopy(rs, rm, cmsg);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rds_send_mprds_hash(काष्ठा rds_sock *rs,
			       काष्ठा rds_connection *conn, पूर्णांक nonblock)
अणु
	पूर्णांक hash;

	अगर (conn->c_npaths == 0)
		hash = RDS_MPATH_HASH(rs, RDS_MPATH_WORKERS);
	अन्यथा
		hash = RDS_MPATH_HASH(rs, conn->c_npaths);
	अगर (conn->c_npaths == 0 && hash != 0) अणु
		rds_send_ping(conn, 0);

		/* The underlying connection is not up yet.  Need to रुको
		 * until it is up to be sure that the non-zero c_path can be
		 * used.  But अगर we are पूर्णांकerrupted, we have to use the zero
		 * c_path in हाल the connection ends up being non-MP capable.
		 */
		अगर (conn->c_npaths == 0) अणु
			/* Cannot रुको क्रम the connection be made, so just use
			 * the base c_path.
			 */
			अगर (nonblock)
				वापस 0;
			अगर (रुको_event_पूर्णांकerruptible(conn->c_hs_रुकोq,
						     conn->c_npaths != 0))
				hash = 0;
		पूर्ण
		अगर (conn->c_npaths == 1)
			hash = 0;
	पूर्ण
	वापस hash;
पूर्ण

अटल पूर्णांक rds_rdma_bytes(काष्ठा msghdr *msg, माप_प्रकार *rdma_bytes)
अणु
	काष्ठा rds_rdma_args *args;
	काष्ठा cmsghdr *cmsg;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;

		अगर (cmsg->cmsg_level != SOL_RDS)
			जारी;

		अगर (cmsg->cmsg_type == RDS_CMSG_RDMA_ARGS) अणु
			अगर (cmsg->cmsg_len <
			    CMSG_LEN(माप(काष्ठा rds_rdma_args)))
				वापस -EINVAL;
			args = CMSG_DATA(cmsg);
			*rdma_bytes += args->remote_vec.bytes;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rds_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार payload_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rds_sock *rs = rds_sk_to_rs(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, usin, msg->msg_name);
	__be16 dport;
	काष्ठा rds_message *rm = शून्य;
	काष्ठा rds_connection *conn;
	पूर्णांक ret = 0;
	पूर्णांक queued = 0, allocated_mr = 0;
	पूर्णांक nonblock = msg->msg_flags & MSG_DONTWAIT;
	दीर्घ समयo = sock_sndसमयo(sk, nonblock);
	काष्ठा rds_conn_path *cpath;
	काष्ठा in6_addr daddr;
	__u32 scope_id = 0;
	माप_प्रकार total_payload_len = payload_len, rdma_payload_len = 0;
	bool zcopy = ((msg->msg_flags & MSG_ZEROCOPY) &&
		      sock_flag(rds_rs_to_sk(rs), SOCK_ZEROCOPY));
	पूर्णांक num_sgs = DIV_ROUND_UP(payload_len, PAGE_SIZE);
	पूर्णांक namelen;
	काष्ठा rds_iov_vector_arr vct;
	पूर्णांक ind;

	स_रखो(&vct, 0, माप(vct));

	/* expect 1 RDMA CMSG per rds_sendmsg. can still grow अगर more needed. */
	vct.incr = 1;

	/* Mirror Linux UDP mirror of BSD error message compatibility */
	/* XXX: Perhaps MSG_MORE someday */
	अगर (msg->msg_flags & ~(MSG_DONTWAIT | MSG_CMSG_COMPAT | MSG_ZEROCOPY)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	namelen = msg->msg_namelen;
	अगर (namelen != 0) अणु
		अगर (namelen < माप(*usin)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		चयन (usin->sin_family) अणु
		हाल AF_INET:
			अगर (usin->sin_addr.s_addr == htonl(INADDR_ANY) ||
			    usin->sin_addr.s_addr == htonl(INADDR_BROADCAST) ||
			    ipv4_is_multicast(usin->sin_addr.s_addr)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ipv6_addr_set_v4mapped(usin->sin_addr.s_addr, &daddr);
			dport = usin->sin_port;
			अवरोध;

#अगर IS_ENABLED(CONFIG_IPV6)
		हाल AF_INET6: अणु
			पूर्णांक addr_type;

			अगर (namelen < माप(*sin6)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			addr_type = ipv6_addr_type(&sin6->sin6_addr);
			अगर (!(addr_type & IPV6_ADDR_UNICAST)) अणु
				__be32 addr4;

				अगर (!(addr_type & IPV6_ADDR_MAPPED)) अणु
					ret = -EINVAL;
					जाओ out;
				पूर्ण

				/* It is a mapped address.  Need to करो some
				 * sanity checks.
				 */
				addr4 = sin6->sin6_addr.s6_addr32[3];
				अगर (addr4 == htonl(INADDR_ANY) ||
				    addr4 == htonl(INADDR_BROADCAST) ||
				    ipv4_is_multicast(addr4)) अणु
					ret = -EINVAL;
					जाओ out;
				पूर्ण
			पूर्ण
			अगर (addr_type & IPV6_ADDR_LINKLOCAL) अणु
				अगर (sin6->sin6_scope_id == 0) अणु
					ret = -EINVAL;
					जाओ out;
				पूर्ण
				scope_id = sin6->sin6_scope_id;
			पूर्ण

			daddr = sin6->sin6_addr;
			dport = sin6->sin6_port;
			अवरोध;
		पूर्ण
#पूर्ण_अगर

		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We only care about consistency with ->connect() */
		lock_sock(sk);
		daddr = rs->rs_conn_addr;
		dport = rs->rs_conn_port;
		scope_id = rs->rs_bound_scope_id;
		release_sock(sk);
	पूर्ण

	lock_sock(sk);
	अगर (ipv6_addr_any(&rs->rs_bound_addr) || ipv6_addr_any(&daddr)) अणु
		release_sock(sk);
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण अन्यथा अगर (namelen != 0) अणु
		/* Cannot send to an IPv4 address using an IPv6 source
		 * address and cannot send to an IPv6 address using an
		 * IPv4 source address.
		 */
		अगर (ipv6_addr_v4mapped(&daddr) ^
		    ipv6_addr_v4mapped(&rs->rs_bound_addr)) अणु
			release_sock(sk);
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		/* If the socket is alपढ़ोy bound to a link local address,
		 * it can only send to peers on the same link.  But allow
		 * communicating between link local and non-link local address.
		 */
		अगर (scope_id != rs->rs_bound_scope_id) अणु
			अगर (!scope_id) अणु
				scope_id = rs->rs_bound_scope_id;
			पूर्ण अन्यथा अगर (rs->rs_bound_scope_id) अणु
				release_sock(sk);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	release_sock(sk);

	ret = rds_rdma_bytes(msg, &rdma_payload_len);
	अगर (ret)
		जाओ out;

	total_payload_len += rdma_payload_len;
	अगर (max_t(माप_प्रकार, payload_len, rdma_payload_len) > RDS_MAX_MSG_SIZE) अणु
		ret = -EMSGSIZE;
		जाओ out;
	पूर्ण

	अगर (payload_len > rds_sk_sndbuf(rs)) अणु
		ret = -EMSGSIZE;
		जाओ out;
	पूर्ण

	अगर (zcopy) अणु
		अगर (rs->rs_transport->t_type != RDS_TRANS_TCP) अणु
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		num_sgs = iov_iter_npages(&msg->msg_iter, पूर्णांक_उच्च);
	पूर्ण
	/* size of rm including all sgs */
	ret = rds_rm_size(msg, num_sgs, &vct);
	अगर (ret < 0)
		जाओ out;

	rm = rds_message_alloc(ret, GFP_KERNEL);
	अगर (!rm) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Attach data to the rm */
	अगर (payload_len) अणु
		rm->data.op_sg = rds_message_alloc_sgs(rm, num_sgs);
		अगर (IS_ERR(rm->data.op_sg)) अणु
			ret = PTR_ERR(rm->data.op_sg);
			जाओ out;
		पूर्ण
		ret = rds_message_copy_from_user(rm, &msg->msg_iter, zcopy);
		अगर (ret)
			जाओ out;
	पूर्ण
	rm->data.op_active = 1;

	rm->m_daddr = daddr;

	/* rds_conn_create has a spinlock that runs with IRQ off.
	 * Caching the conn in the socket helps a lot. */
	अगर (rs->rs_conn && ipv6_addr_equal(&rs->rs_conn->c_faddr, &daddr) &&
	    rs->rs_tos == rs->rs_conn->c_tos) अणु
		conn = rs->rs_conn;
	पूर्ण अन्यथा अणु
		conn = rds_conn_create_outgoing(sock_net(sock->sk),
						&rs->rs_bound_addr, &daddr,
						rs->rs_transport, rs->rs_tos,
						sock->sk->sk_allocation,
						scope_id);
		अगर (IS_ERR(conn)) अणु
			ret = PTR_ERR(conn);
			जाओ out;
		पूर्ण
		rs->rs_conn = conn;
	पूर्ण

	अगर (conn->c_trans->t_mp_capable)
		cpath = &conn->c_path[rds_send_mprds_hash(rs, conn, nonblock)];
	अन्यथा
		cpath = &conn->c_path[0];

	rm->m_conn_path = cpath;

	/* Parse any control messages the user may have included. */
	ret = rds_cmsg_send(rs, rm, msg, &allocated_mr, &vct);
	अगर (ret) अणु
		/* Trigger connection so that its पढ़ोy क्रम the next retry */
		अगर (ret ==  -EAGAIN)
			rds_conn_connect_अगर_करोwn(conn);
		जाओ out;
	पूर्ण

	अगर (rm->rdma.op_active && !conn->c_trans->xmit_rdma) अणु
		prपूर्णांकk_ratelimited(KERN_NOTICE "rdma_op %p conn xmit_rdma %p\n",
			       &rm->rdma, conn->c_trans->xmit_rdma);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (rm->atomic.op_active && !conn->c_trans->xmit_atomic) अणु
		prपूर्णांकk_ratelimited(KERN_NOTICE "atomic_op %p conn xmit_atomic %p\n",
			       &rm->atomic, conn->c_trans->xmit_atomic);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (rds_destroy_pending(conn)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (rds_conn_path_करोwn(cpath))
		rds_check_all_paths(conn);

	ret = rds_cong_रुको(conn->c_fcong, dport, nonblock, rs);
	अगर (ret) अणु
		rs->rs_seen_congestion = 1;
		जाओ out;
	पूर्ण
	जबतक (!rds_send_queue_rm(rs, conn, cpath, rm, rs->rs_bound_port,
				  dport, &queued)) अणु
		rds_stats_inc(s_send_queue_full);

		अगर (nonblock) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण

		समयo = रुको_event_पूर्णांकerruptible_समयout(*sk_sleep(sk),
					rds_send_queue_rm(rs, conn, cpath, rm,
							  rs->rs_bound_port,
							  dport,
							  &queued),
					समयo);
		rdsdebug("sendmsg woke queued %d timeo %ld\n", queued, समयo);
		अगर (समयo > 0 || समयo == MAX_SCHEDULE_TIMEOUT)
			जारी;

		ret = समयo;
		अगर (ret == 0)
			ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/*
	 * By now we've committed to the send.  We reuse rds_send_worker()
	 * to retry sends in the rds thपढ़ो अगर the transport asks us to.
	 */
	rds_stats_inc(s_send_queued);

	ret = rds_send_xmit(cpath);
	अगर (ret == -ENOMEM || ret == -EAGAIN) अणु
		ret = 0;
		rcu_पढ़ो_lock();
		अगर (rds_destroy_pending(cpath->cp_conn))
			ret = -ENETUNREACH;
		अन्यथा
			queue_delayed_work(rds_wq, &cpath->cp_send_w, 1);
		rcu_पढ़ो_unlock();
	पूर्ण
	अगर (ret)
		जाओ out;
	rds_message_put(rm);

	क्रम (ind = 0; ind < vct.indx; ind++)
		kमुक्त(vct.vec[ind].iov);
	kमुक्त(vct.vec);

	वापस payload_len;

out:
	क्रम (ind = 0; ind < vct.indx; ind++)
		kमुक्त(vct.vec[ind].iov);
	kमुक्त(vct.vec);

	/* If the user included a RDMA_MAP cmsg, we allocated a MR on the fly.
	 * If the sendmsg goes through, we keep the MR. If it fails with EAGAIN
	 * or in any other way, we need to destroy the MR again */
	अगर (allocated_mr)
		rds_rdma_unuse(rs, rds_rdma_cookie_key(rm->m_rdma_cookie), 1);

	अगर (rm)
		rds_message_put(rm);
	वापस ret;
पूर्ण

/*
 * send out a probe. Can be shared by rds_send_ping,
 * rds_send_pong, rds_send_hb.
 * rds_send_hb should use h_flags
 *   RDS_FLAG_HB_PING|RDS_FLAG_ACK_REQUIRED
 * or
 *   RDS_FLAG_HB_PONG|RDS_FLAG_ACK_REQUIRED
 */
अटल पूर्णांक
rds_send_probe(काष्ठा rds_conn_path *cp, __be16 sport,
	       __be16 dport, u8 h_flags)
अणु
	काष्ठा rds_message *rm;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	rm = rds_message_alloc(0, GFP_ATOMIC);
	अगर (!rm) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	rm->m_daddr = cp->cp_conn->c_faddr;
	rm->data.op_active = 1;

	rds_conn_path_connect_अगर_करोwn(cp);

	ret = rds_cong_रुको(cp->cp_conn->c_fcong, dport, 1, शून्य);
	अगर (ret)
		जाओ out;

	spin_lock_irqsave(&cp->cp_lock, flags);
	list_add_tail(&rm->m_conn_item, &cp->cp_send_queue);
	set_bit(RDS_MSG_ON_CONN, &rm->m_flags);
	rds_message_addref(rm);
	rm->m_inc.i_conn = cp->cp_conn;
	rm->m_inc.i_conn_path = cp;

	rds_message_populate_header(&rm->m_inc.i_hdr, sport, dport,
				    cp->cp_next_tx_seq);
	rm->m_inc.i_hdr.h_flags |= h_flags;
	cp->cp_next_tx_seq++;

	अगर (RDS_HS_PROBE(be16_to_cpu(sport), be16_to_cpu(dport)) &&
	    cp->cp_conn->c_trans->t_mp_capable) अणु
		u16 npaths = cpu_to_be16(RDS_MPATH_WORKERS);
		u32 my_gen_num = cpu_to_be32(cp->cp_conn->c_my_gen_num);

		rds_message_add_extension(&rm->m_inc.i_hdr,
					  RDS_EXTHDR_NPATHS, &npaths,
					  माप(npaths));
		rds_message_add_extension(&rm->m_inc.i_hdr,
					  RDS_EXTHDR_GEN_NUM,
					  &my_gen_num,
					  माप(u32));
	पूर्ण
	spin_unlock_irqrestore(&cp->cp_lock, flags);

	rds_stats_inc(s_send_queued);
	rds_stats_inc(s_send_pong);

	/* schedule the send work on rds_wq */
	rcu_पढ़ो_lock();
	अगर (!rds_destroy_pending(cp->cp_conn))
		queue_delayed_work(rds_wq, &cp->cp_send_w, 1);
	rcu_पढ़ो_unlock();

	rds_message_put(rm);
	वापस 0;

out:
	अगर (rm)
		rds_message_put(rm);
	वापस ret;
पूर्ण

पूर्णांक
rds_send_pong(काष्ठा rds_conn_path *cp, __be16 dport)
अणु
	वापस rds_send_probe(cp, 0, dport, 0);
पूर्ण

व्योम
rds_send_ping(काष्ठा rds_connection *conn, पूर्णांक cp_index)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rds_conn_path *cp = &conn->c_path[cp_index];

	spin_lock_irqsave(&cp->cp_lock, flags);
	अगर (conn->c_ping_triggered) अणु
		spin_unlock_irqrestore(&cp->cp_lock, flags);
		वापस;
	पूर्ण
	conn->c_ping_triggered = 1;
	spin_unlock_irqrestore(&cp->cp_lock, flags);
	rds_send_probe(cp, cpu_to_be16(RDS_FLAG_PROBE_PORT), 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rds_send_ping);
