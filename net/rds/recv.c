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
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/in.h>
#समावेश <linux/export.h>
#समावेश <linux/समय.स>
#समावेश <linux/rds.h>

#समावेश "rds.h"

व्योम rds_inc_init(काष्ठा rds_incoming *inc, काष्ठा rds_connection *conn,
		 काष्ठा in6_addr *saddr)
अणु
	refcount_set(&inc->i_refcount, 1);
	INIT_LIST_HEAD(&inc->i_item);
	inc->i_conn = conn;
	inc->i_saddr = *saddr;
	inc->i_usercopy.rdma_cookie = 0;
	inc->i_usercopy.rx_tstamp = kसमय_set(0, 0);

	स_रखो(inc->i_rx_lat_trace, 0, माप(inc->i_rx_lat_trace));
पूर्ण
EXPORT_SYMBOL_GPL(rds_inc_init);

व्योम rds_inc_path_init(काष्ठा rds_incoming *inc, काष्ठा rds_conn_path *cp,
		       काष्ठा in6_addr  *saddr)
अणु
	refcount_set(&inc->i_refcount, 1);
	INIT_LIST_HEAD(&inc->i_item);
	inc->i_conn = cp->cp_conn;
	inc->i_conn_path = cp;
	inc->i_saddr = *saddr;
	inc->i_usercopy.rdma_cookie = 0;
	inc->i_usercopy.rx_tstamp = kसमय_set(0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rds_inc_path_init);

अटल व्योम rds_inc_addref(काष्ठा rds_incoming *inc)
अणु
	rdsdebug("addref inc %p ref %d\n", inc, refcount_पढ़ो(&inc->i_refcount));
	refcount_inc(&inc->i_refcount);
पूर्ण

व्योम rds_inc_put(काष्ठा rds_incoming *inc)
अणु
	rdsdebug("put inc %p ref %d\n", inc, refcount_पढ़ो(&inc->i_refcount));
	अगर (refcount_dec_and_test(&inc->i_refcount)) अणु
		BUG_ON(!list_empty(&inc->i_item));

		inc->i_conn->c_trans->inc_मुक्त(inc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_inc_put);

अटल व्योम rds_recv_rcvbuf_delta(काष्ठा rds_sock *rs, काष्ठा sock *sk,
				  काष्ठा rds_cong_map *map,
				  पूर्णांक delta, __be16 port)
अणु
	पूर्णांक now_congested;

	अगर (delta == 0)
		वापस;

	rs->rs_rcv_bytes += delta;
	अगर (delta > 0)
		rds_stats_add(s_recv_bytes_added_to_socket, delta);
	अन्यथा
		rds_stats_add(s_recv_bytes_हटाओd_from_socket, -delta);

	/* loop transport करोesn't send/recv congestion updates */
	अगर (rs->rs_transport->t_type == RDS_TRANS_LOOP)
		वापस;

	now_congested = rs->rs_rcv_bytes > rds_sk_rcvbuf(rs);

	rdsdebug("rs %p (%pI6c:%u) recv bytes %d buf %d "
	  "now_cong %d delta %d\n",
	  rs, &rs->rs_bound_addr,
	  ntohs(rs->rs_bound_port), rs->rs_rcv_bytes,
	  rds_sk_rcvbuf(rs), now_congested, delta);

	/* wasn't -> am congested */
	अगर (!rs->rs_congested && now_congested) अणु
		rs->rs_congested = 1;
		rds_cong_set_bit(map, port);
		rds_cong_queue_updates(map);
	पूर्ण
	/* was -> aren't congested */
	/* Require more मुक्त space beक्रमe reporting uncongested to prevent
	   bouncing cong/uncong state too often */
	अन्यथा अगर (rs->rs_congested && (rs->rs_rcv_bytes < (rds_sk_rcvbuf(rs)/2))) अणु
		rs->rs_congested = 0;
		rds_cong_clear_bit(map, port);
		rds_cong_queue_updates(map);
	पूर्ण

	/* करो nothing अगर no change in cong state */
पूर्ण

अटल व्योम rds_conn_peer_gen_update(काष्ठा rds_connection *conn,
				     u32 peer_gen_num)
अणु
	पूर्णांक i;
	काष्ठा rds_message *rm, *पंचांगp;
	अचिन्हित दीर्घ flags;

	WARN_ON(conn->c_trans->t_type != RDS_TRANS_TCP);
	अगर (peer_gen_num != 0) अणु
		अगर (conn->c_peer_gen_num != 0 &&
		    peer_gen_num != conn->c_peer_gen_num) अणु
			क्रम (i = 0; i < RDS_MPATH_WORKERS; i++) अणु
				काष्ठा rds_conn_path *cp;

				cp = &conn->c_path[i];
				spin_lock_irqsave(&cp->cp_lock, flags);
				cp->cp_next_tx_seq = 1;
				cp->cp_next_rx_seq = 0;
				list_क्रम_each_entry_safe(rm, पंचांगp,
							 &cp->cp_retrans,
							 m_conn_item) अणु
					set_bit(RDS_MSG_FLUSH, &rm->m_flags);
				पूर्ण
				spin_unlock_irqrestore(&cp->cp_lock, flags);
			पूर्ण
		पूर्ण
		conn->c_peer_gen_num = peer_gen_num;
	पूर्ण
पूर्ण

/*
 * Process all extension headers that come with this message.
 */
अटल व्योम rds_recv_incoming_exthdrs(काष्ठा rds_incoming *inc, काष्ठा rds_sock *rs)
अणु
	काष्ठा rds_header *hdr = &inc->i_hdr;
	अचिन्हित पूर्णांक pos = 0, type, len;
	जोड़ अणु
		काष्ठा rds_ext_header_version version;
		काष्ठा rds_ext_header_rdma rdma;
		काष्ठा rds_ext_header_rdma_dest rdma_dest;
	पूर्ण buffer;

	जबतक (1) अणु
		len = माप(buffer);
		type = rds_message_next_extension(hdr, &pos, &buffer, &len);
		अगर (type == RDS_EXTHDR_NONE)
			अवरोध;
		/* Process extension header here */
		चयन (type) अणु
		हाल RDS_EXTHDR_RDMA:
			rds_rdma_unuse(rs, be32_to_cpu(buffer.rdma.h_rdma_rkey), 0);
			अवरोध;

		हाल RDS_EXTHDR_RDMA_DEST:
			/* We ignore the size क्रम now. We could stash it
			 * somewhere and use it क्रम error checking. */
			inc->i_usercopy.rdma_cookie = rds_rdma_make_cookie(
					be32_to_cpu(buffer.rdma_dest.h_rdma_rkey),
					be32_to_cpu(buffer.rdma_dest.h_rdma_offset));

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rds_recv_hs_exthdrs(काष्ठा rds_header *hdr,
				काष्ठा rds_connection *conn)
अणु
	अचिन्हित पूर्णांक pos = 0, type, len;
	जोड़ अणु
		काष्ठा rds_ext_header_version version;
		u16 rds_npaths;
		u32 rds_gen_num;
	पूर्ण buffer;
	u32 new_peer_gen_num = 0;

	जबतक (1) अणु
		len = माप(buffer);
		type = rds_message_next_extension(hdr, &pos, &buffer, &len);
		अगर (type == RDS_EXTHDR_NONE)
			अवरोध;
		/* Process extension header here */
		चयन (type) अणु
		हाल RDS_EXTHDR_NPATHS:
			conn->c_npaths = min_t(पूर्णांक, RDS_MPATH_WORKERS,
					       be16_to_cpu(buffer.rds_npaths));
			अवरोध;
		हाल RDS_EXTHDR_GEN_NUM:
			new_peer_gen_num = be32_to_cpu(buffer.rds_gen_num);
			अवरोध;
		शेष:
			pr_warn_ratelimited("ignoring unknown exthdr type "
					     "0x%x\n", type);
		पूर्ण
	पूर्ण
	/* अगर RDS_EXTHDR_NPATHS was not found, शेष to a single-path */
	conn->c_npaths = max_t(पूर्णांक, conn->c_npaths, 1);
	conn->c_ping_triggered = 0;
	rds_conn_peer_gen_update(conn, new_peer_gen_num);
पूर्ण

/* rds_start_mprds() will synchronously start multiple paths when appropriate.
 * The scheme is based on the following rules:
 *
 * 1. rds_sendmsg on first connect attempt sends the probe ping, with the
 *    sender's npaths (s_npaths)
 * 2. rcvr of probe-ping knows the mprds_paths = min(s_npaths, r_npaths). It
 *    sends back a probe-pong with r_npaths. After that, अगर rcvr is the
 *    smaller ip addr, it starts rds_conn_path_connect_अगर_करोwn on all
 *    mprds_paths.
 * 3. sender माला_लो woken up, and can move to rds_conn_path_connect_अगर_करोwn.
 *    If it is the smaller ipaddr, rds_conn_path_connect_अगर_करोwn can be
 *    called after reception of the probe-pong on all mprds_paths.
 *    Otherwise (sender of probe-ping is not the smaller ip addr): just call
 *    rds_conn_path_connect_अगर_करोwn on the hashed path. (see rule 4)
 * 4. rds_connect_worker must only trigger a connection अगर laddr < faddr.
 * 5. sender may end up queuing the packet on the cp. will get sent out later.
 *    when connection is completed.
 */
अटल व्योम rds_start_mprds(काष्ठा rds_connection *conn)
अणु
	पूर्णांक i;
	काष्ठा rds_conn_path *cp;

	अगर (conn->c_npaths > 1 &&
	    rds_addr_cmp(&conn->c_laddr, &conn->c_faddr) < 0) अणु
		क्रम (i = 0; i < conn->c_npaths; i++) अणु
			cp = &conn->c_path[i];
			rds_conn_path_connect_अगर_करोwn(cp);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The transport must make sure that this is serialized against other
 * rx and conn reset on this specअगरic conn.
 *
 * We currently निश्चित that only one fragmented message will be sent
 * करोwn a connection at a समय.  This lets us reassemble in the conn
 * instead of per-flow which means that we करोn't have to go digging through
 * flows to tear करोwn partial reassembly progress on conn failure and
 * we save flow lookup and locking क्रम each frag arrival.  It करोes mean
 * that small messages will रुको behind large ones.  Fragmenting at all
 * is only to reduce the memory consumption of pre-posted buffers.
 *
 * The caller passes in saddr and daddr instead of us getting it from the
 * conn.  This lets loopback, who only has one conn क्रम both directions,
 * tell us which roles the addrs in the conn are playing क्रम this message.
 */
व्योम rds_recv_incoming(काष्ठा rds_connection *conn, काष्ठा in6_addr *saddr,
		       काष्ठा in6_addr *daddr,
		       काष्ठा rds_incoming *inc, gfp_t gfp)
अणु
	काष्ठा rds_sock *rs = शून्य;
	काष्ठा sock *sk;
	अचिन्हित दीर्घ flags;
	काष्ठा rds_conn_path *cp;

	inc->i_conn = conn;
	inc->i_rx_jअगरfies = jअगरfies;
	अगर (conn->c_trans->t_mp_capable)
		cp = inc->i_conn_path;
	अन्यथा
		cp = &conn->c_path[0];

	rdsdebug("conn %p next %llu inc %p seq %llu len %u sport %u dport %u "
		 "flags 0x%x rx_jiffies %lu\n", conn,
		 (अचिन्हित दीर्घ दीर्घ)cp->cp_next_rx_seq,
		 inc,
		 (अचिन्हित दीर्घ दीर्घ)be64_to_cpu(inc->i_hdr.h_sequence),
		 be32_to_cpu(inc->i_hdr.h_len),
		 be16_to_cpu(inc->i_hdr.h_sport),
		 be16_to_cpu(inc->i_hdr.h_dport),
		 inc->i_hdr.h_flags,
		 inc->i_rx_jअगरfies);

	/*
	 * Sequence numbers should only increase.  Messages get their
	 * sequence number as they're queued in a sending conn.  They
	 * can be dropped, though, अगर the sending socket is बंदd beक्रमe
	 * they hit the wire.  So sequence numbers can skip क्रमward
	 * under normal operation.  They can also drop back in the conn
	 * failover हाल as previously sent messages are resent करोwn the
	 * new instance of a conn.  We drop those, otherwise we have
	 * to assume that the next valid seq करोes not come after a
	 * hole in the fragment stream.
	 *
	 * The headers करोn't give us a way to realize अगर fragments of
	 * a message have been dropped.  We assume that frags that arrive
	 * to a flow are part of the current message on the flow that is
	 * being reassembled.  This means that senders can't drop messages
	 * from the sending conn until all their frags are sent.
	 *
	 * XXX we could spend more on the wire to get more robust failure
	 * detection, arguably worth it to aव्योम data corruption.
	 */
	अगर (be64_to_cpu(inc->i_hdr.h_sequence) < cp->cp_next_rx_seq &&
	    (inc->i_hdr.h_flags & RDS_FLAG_RETRANSMITTED)) अणु
		rds_stats_inc(s_recv_drop_old_seq);
		जाओ out;
	पूर्ण
	cp->cp_next_rx_seq = be64_to_cpu(inc->i_hdr.h_sequence) + 1;

	अगर (rds_sysctl_ping_enable && inc->i_hdr.h_dport == 0) अणु
		अगर (inc->i_hdr.h_sport == 0) अणु
			rdsdebug("ignore ping with 0 sport from %pI6c\n",
				 saddr);
			जाओ out;
		पूर्ण
		rds_stats_inc(s_recv_ping);
		rds_send_pong(cp, inc->i_hdr.h_sport);
		/* अगर this is a handshake ping, start multipath अगर necessary */
		अगर (RDS_HS_PROBE(be16_to_cpu(inc->i_hdr.h_sport),
				 be16_to_cpu(inc->i_hdr.h_dport))) अणु
			rds_recv_hs_exthdrs(&inc->i_hdr, cp->cp_conn);
			rds_start_mprds(cp->cp_conn);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (be16_to_cpu(inc->i_hdr.h_dport) ==  RDS_FLAG_PROBE_PORT &&
	    inc->i_hdr.h_sport == 0) अणु
		rds_recv_hs_exthdrs(&inc->i_hdr, cp->cp_conn);
		/* अगर this is a handshake pong, start multipath अगर necessary */
		rds_start_mprds(cp->cp_conn);
		wake_up(&cp->cp_conn->c_hs_रुकोq);
		जाओ out;
	पूर्ण

	rs = rds_find_bound(daddr, inc->i_hdr.h_dport, conn->c_bound_अगर);
	अगर (!rs) अणु
		rds_stats_inc(s_recv_drop_no_sock);
		जाओ out;
	पूर्ण

	/* Process extension headers */
	rds_recv_incoming_exthdrs(inc, rs);

	/* We can be racing with rds_release() which marks the socket dead. */
	sk = rds_rs_to_sk(rs);

	/* serialize with rds_release -> sock_orphan */
	ग_लिखो_lock_irqsave(&rs->rs_recv_lock, flags);
	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		rdsdebug("adding inc %p to rs %p's recv queue\n", inc, rs);
		rds_stats_inc(s_recv_queued);
		rds_recv_rcvbuf_delta(rs, sk, inc->i_conn->c_lcong,
				      be32_to_cpu(inc->i_hdr.h_len),
				      inc->i_hdr.h_dport);
		अगर (sock_flag(sk, SOCK_RCVTSTAMP))
			inc->i_usercopy.rx_tstamp = kसमय_get_real();
		rds_inc_addref(inc);
		inc->i_rx_lat_trace[RDS_MSG_RX_END] = local_घड़ी();
		list_add_tail(&inc->i_item, &rs->rs_recv_queue);
		__rds_wake_sk_sleep(sk);
	पूर्ण अन्यथा अणु
		rds_stats_inc(s_recv_drop_dead_sock);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&rs->rs_recv_lock, flags);

out:
	अगर (rs)
		rds_sock_put(rs);
पूर्ण
EXPORT_SYMBOL_GPL(rds_recv_incoming);

/*
 * be very careful here.  This is being called as the condition in
 * रुको_event_*() needs to cope with being called many बार.
 */
अटल पूर्णांक rds_next_incoming(काष्ठा rds_sock *rs, काष्ठा rds_incoming **inc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!*inc) अणु
		पढ़ो_lock_irqsave(&rs->rs_recv_lock, flags);
		अगर (!list_empty(&rs->rs_recv_queue)) अणु
			*inc = list_entry(rs->rs_recv_queue.next,
					  काष्ठा rds_incoming,
					  i_item);
			rds_inc_addref(*inc);
		पूर्ण
		पढ़ो_unlock_irqrestore(&rs->rs_recv_lock, flags);
	पूर्ण

	वापस *inc != शून्य;
पूर्ण

अटल पूर्णांक rds_still_queued(काष्ठा rds_sock *rs, काष्ठा rds_incoming *inc,
			    पूर्णांक drop)
अणु
	काष्ठा sock *sk = rds_rs_to_sk(rs);
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&rs->rs_recv_lock, flags);
	अगर (!list_empty(&inc->i_item)) अणु
		ret = 1;
		अगर (drop) अणु
			/* XXX make sure this i_conn is reliable */
			rds_recv_rcvbuf_delta(rs, sk, inc->i_conn->c_lcong,
					      -be32_to_cpu(inc->i_hdr.h_len),
					      inc->i_hdr.h_dport);
			list_del_init(&inc->i_item);
			rds_inc_put(inc);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irqrestore(&rs->rs_recv_lock, flags);

	rdsdebug("inc %p rs %p still %d dropped %d\n", inc, rs, ret, drop);
	वापस ret;
पूर्ण

/*
 * Pull errors off the error queue.
 * If msghdr is शून्य, we will just purge the error queue.
 */
पूर्णांक rds_notअगरy_queue_get(काष्ठा rds_sock *rs, काष्ठा msghdr *msghdr)
अणु
	काष्ठा rds_notअगरier *notअगरier;
	काष्ठा rds_rdma_notअगरy cmsg;
	अचिन्हित पूर्णांक count = 0, max_messages = ~0U;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(copy);
	पूर्णांक err = 0;

	स_रखो(&cmsg, 0, माप(cmsg));	/* fill holes with zero */

	/* put_cmsg copies to user space and thus may sleep. We can't करो this
	 * with rs_lock held, so first grab as many notअगरications as we can stuff
	 * in the user provided cmsg buffer. We करोn't try to copy more, to aव्योम
	 * losing notअगरications - except when the buffer is so small that it wouldn't
	 * even hold a single notअगरication. Then we give him as much of this single
	 * msg as we can squeeze in, and set MSG_CTRUNC.
	 */
	अगर (msghdr) अणु
		max_messages = msghdr->msg_controllen / CMSG_SPACE(माप(cmsg));
		अगर (!max_messages)
			max_messages = 1;
	पूर्ण

	spin_lock_irqsave(&rs->rs_lock, flags);
	जबतक (!list_empty(&rs->rs_notअगरy_queue) && count < max_messages) अणु
		notअगरier = list_entry(rs->rs_notअगरy_queue.next,
				काष्ठा rds_notअगरier, n_list);
		list_move(&notअगरier->n_list, &copy);
		count++;
	पूर्ण
	spin_unlock_irqrestore(&rs->rs_lock, flags);

	अगर (!count)
		वापस 0;

	जबतक (!list_empty(&copy)) अणु
		notअगरier = list_entry(copy.next, काष्ठा rds_notअगरier, n_list);

		अगर (msghdr) अणु
			cmsg.user_token = notअगरier->n_user_token;
			cmsg.status = notअगरier->n_status;

			err = put_cmsg(msghdr, SOL_RDS, RDS_CMSG_RDMA_STATUS,
				       माप(cmsg), &cmsg);
			अगर (err)
				अवरोध;
		पूर्ण

		list_del_init(&notअगरier->n_list);
		kमुक्त(notअगरier);
	पूर्ण

	/* If we bailed out because of an error in put_cmsg,
	 * we may be left with one or more notअगरications that we
	 * didn't process. Return them to the head of the list. */
	अगर (!list_empty(&copy)) अणु
		spin_lock_irqsave(&rs->rs_lock, flags);
		list_splice(&copy, &rs->rs_notअगरy_queue);
		spin_unlock_irqrestore(&rs->rs_lock, flags);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Queue a congestion notअगरication
 */
अटल पूर्णांक rds_notअगरy_cong(काष्ठा rds_sock *rs, काष्ठा msghdr *msghdr)
अणु
	uपूर्णांक64_t notअगरy = rs->rs_cong_notअगरy;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	err = put_cmsg(msghdr, SOL_RDS, RDS_CMSG_CONG_UPDATE,
			माप(notअगरy), &notअगरy);
	अगर (err)
		वापस err;

	spin_lock_irqsave(&rs->rs_lock, flags);
	rs->rs_cong_notअगरy &= ~notअगरy;
	spin_unlock_irqrestore(&rs->rs_lock, flags);

	वापस 0;
पूर्ण

/*
 * Receive any control messages.
 */
अटल पूर्णांक rds_cmsg_recv(काष्ठा rds_incoming *inc, काष्ठा msghdr *msg,
			 काष्ठा rds_sock *rs)
अणु
	पूर्णांक ret = 0;

	अगर (inc->i_usercopy.rdma_cookie) अणु
		ret = put_cmsg(msg, SOL_RDS, RDS_CMSG_RDMA_DEST,
				माप(inc->i_usercopy.rdma_cookie),
				&inc->i_usercopy.rdma_cookie);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर ((inc->i_usercopy.rx_tstamp != 0) &&
	    sock_flag(rds_rs_to_sk(rs), SOCK_RCVTSTAMP)) अणु
		काष्ठा __kernel_old_समयval tv =
			ns_to_kernel_old_समयval(inc->i_usercopy.rx_tstamp);

		अगर (!sock_flag(rds_rs_to_sk(rs), SOCK_TSTAMP_NEW)) अणु
			ret = put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMP_OLD,
				       माप(tv), &tv);
		पूर्ण अन्यथा अणु
			काष्ठा __kernel_sock_समयval sk_tv;

			sk_tv.tv_sec = tv.tv_sec;
			sk_tv.tv_usec = tv.tv_usec;

			ret = put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMP_NEW,
				       माप(sk_tv), &sk_tv);
		पूर्ण

		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (rs->rs_rx_traces) अणु
		काष्ठा rds_cmsg_rx_trace t;
		पूर्णांक i, j;

		स_रखो(&t, 0, माप(t));
		inc->i_rx_lat_trace[RDS_MSG_RX_CMSG] = local_घड़ी();
		t.rx_traces =  rs->rs_rx_traces;
		क्रम (i = 0; i < rs->rs_rx_traces; i++) अणु
			j = rs->rs_rx_trace[i];
			t.rx_trace_pos[i] = j;
			t.rx_trace[i] = inc->i_rx_lat_trace[j + 1] -
					  inc->i_rx_lat_trace[j];
		पूर्ण

		ret = put_cmsg(msg, SOL_RDS, RDS_CMSG_RXPATH_LATENCY,
			       माप(t), &t);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल bool rds_recvmsg_zcookie(काष्ठा rds_sock *rs, काष्ठा msghdr *msg)
अणु
	काष्ठा rds_msg_zcopy_queue *q = &rs->rs_zcookie_queue;
	काष्ठा rds_msg_zcopy_info *info = शून्य;
	काष्ठा rds_zcopy_cookies *करोne;
	अचिन्हित दीर्घ flags;

	अगर (!msg->msg_control)
		वापस false;

	अगर (!sock_flag(rds_rs_to_sk(rs), SOCK_ZEROCOPY) ||
	    msg->msg_controllen < CMSG_SPACE(माप(*करोne)))
		वापस false;

	spin_lock_irqsave(&q->lock, flags);
	अगर (!list_empty(&q->zcookie_head)) अणु
		info = list_entry(q->zcookie_head.next,
				  काष्ठा rds_msg_zcopy_info, rs_zcookie_next);
		list_del(&info->rs_zcookie_next);
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);
	अगर (!info)
		वापस false;
	करोne = &info->zcookies;
	अगर (put_cmsg(msg, SOL_RDS, RDS_CMSG_ZCOPY_COMPLETION, माप(*करोne),
		     करोne)) अणु
		spin_lock_irqsave(&q->lock, flags);
		list_add(&info->rs_zcookie_next, &q->zcookie_head);
		spin_unlock_irqrestore(&q->lock, flags);
		वापस false;
	पूर्ण
	kमुक्त(info);
	वापस true;
पूर्ण

पूर्णांक rds_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		पूर्णांक msg_flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rds_sock *rs = rds_sk_to_rs(sk);
	दीर्घ समयo;
	पूर्णांक ret = 0, nonblock = msg_flags & MSG_DONTWAIT;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, msg->msg_name);
	काष्ठा rds_incoming *inc = शून्य;

	/* udp_recvmsg()->sock_recvसमयo() माला_लो away without locking too.. */
	समयo = sock_rcvसमयo(sk, nonblock);

	rdsdebug("size %zu flags 0x%x timeo %ld\n", size, msg_flags, समयo);

	अगर (msg_flags & MSG_OOB)
		जाओ out;
	अगर (msg_flags & MSG_ERRQUEUE)
		वापस sock_recv_errqueue(sk, msg, size, SOL_IP, IP_RECVERR);

	जबतक (1) अणु
		/* If there are pending notअगरications, करो those - and nothing अन्यथा */
		अगर (!list_empty(&rs->rs_notअगरy_queue)) अणु
			ret = rds_notअगरy_queue_get(rs, msg);
			अवरोध;
		पूर्ण

		अगर (rs->rs_cong_notअगरy) अणु
			ret = rds_notअगरy_cong(rs, msg);
			अवरोध;
		पूर्ण

		अगर (!rds_next_incoming(rs, &inc)) अणु
			अगर (nonblock) अणु
				bool reaped = rds_recvmsg_zcookie(rs, msg);

				ret = reaped ?  0 : -EAGAIN;
				अवरोध;
			पूर्ण

			समयo = रुको_event_पूर्णांकerruptible_समयout(*sk_sleep(sk),
					(!list_empty(&rs->rs_notअगरy_queue) ||
					 rs->rs_cong_notअगरy ||
					 rds_next_incoming(rs, &inc)), समयo);
			rdsdebug("recvmsg woke inc %p timeo %ld\n", inc,
				 समयo);
			अगर (समयo > 0 || समयo == MAX_SCHEDULE_TIMEOUT)
				जारी;

			ret = समयo;
			अगर (ret == 0)
				ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		rdsdebug("copying inc %p from %pI6c:%u to user\n", inc,
			 &inc->i_conn->c_faddr,
			 ntohs(inc->i_hdr.h_sport));
		ret = inc->i_conn->c_trans->inc_copy_to_user(inc, &msg->msg_iter);
		अगर (ret < 0)
			अवरोध;

		/*
		 * अगर the message we just copied isn't at the head of the
		 * recv queue then someone अन्यथा raced us to वापस it, try
		 * to get the next message.
		 */
		अगर (!rds_still_queued(rs, inc, !(msg_flags & MSG_PEEK))) अणु
			rds_inc_put(inc);
			inc = शून्य;
			rds_stats_inc(s_recv_deliver_raced);
			iov_iter_revert(&msg->msg_iter, ret);
			जारी;
		पूर्ण

		अगर (ret < be32_to_cpu(inc->i_hdr.h_len)) अणु
			अगर (msg_flags & MSG_TRUNC)
				ret = be32_to_cpu(inc->i_hdr.h_len);
			msg->msg_flags |= MSG_TRUNC;
		पूर्ण

		अगर (rds_cmsg_recv(inc, msg, rs)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		rds_recvmsg_zcookie(rs, msg);

		rds_stats_inc(s_recv_delivered);

		अगर (msg->msg_name) अणु
			अगर (ipv6_addr_v4mapped(&inc->i_saddr)) अणु
				sin->sin_family = AF_INET;
				sin->sin_port = inc->i_hdr.h_sport;
				sin->sin_addr.s_addr =
				    inc->i_saddr.s6_addr32[3];
				स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
				msg->msg_namelen = माप(*sin);
			पूर्ण अन्यथा अणु
				sin6->sin6_family = AF_INET6;
				sin6->sin6_port = inc->i_hdr.h_sport;
				sin6->sin6_addr = inc->i_saddr;
				sin6->sin6_flowinfo = 0;
				sin6->sin6_scope_id = rs->rs_bound_scope_id;
				msg->msg_namelen = माप(*sin6);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (inc)
		rds_inc_put(inc);

out:
	वापस ret;
पूर्ण

/*
 * The socket is being shut करोwn and we're asked to drop messages that were
 * queued क्रम recvmsg.  The caller has unbound the socket so the receive path
 * won't queue any more incoming fragments or messages on the socket.
 */
व्योम rds_clear_recv_queue(काष्ठा rds_sock *rs)
अणु
	काष्ठा sock *sk = rds_rs_to_sk(rs);
	काष्ठा rds_incoming *inc, *पंचांगp;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&rs->rs_recv_lock, flags);
	list_क्रम_each_entry_safe(inc, पंचांगp, &rs->rs_recv_queue, i_item) अणु
		rds_recv_rcvbuf_delta(rs, sk, inc->i_conn->c_lcong,
				      -be32_to_cpu(inc->i_hdr.h_len),
				      inc->i_hdr.h_dport);
		list_del_init(&inc->i_item);
		rds_inc_put(inc);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&rs->rs_recv_lock, flags);
पूर्ण

/*
 * inc->i_saddr isn't used here because it is only set in the receive
 * path.
 */
व्योम rds_inc_info_copy(काष्ठा rds_incoming *inc,
		       काष्ठा rds_info_iterator *iter,
		       __be32 saddr, __be32 daddr, पूर्णांक flip)
अणु
	काष्ठा rds_info_message minfo;

	minfo.seq = be64_to_cpu(inc->i_hdr.h_sequence);
	minfo.len = be32_to_cpu(inc->i_hdr.h_len);
	minfo.tos = inc->i_conn->c_tos;

	अगर (flip) अणु
		minfo.laddr = daddr;
		minfo.faddr = saddr;
		minfo.lport = inc->i_hdr.h_dport;
		minfo.fport = inc->i_hdr.h_sport;
	पूर्ण अन्यथा अणु
		minfo.laddr = saddr;
		minfo.faddr = daddr;
		minfo.lport = inc->i_hdr.h_sport;
		minfo.fport = inc->i_hdr.h_dport;
	पूर्ण

	minfo.flags = 0;

	rds_info_copy(iter, &minfo, माप(minfo));
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
व्योम rds6_inc_info_copy(काष्ठा rds_incoming *inc,
			काष्ठा rds_info_iterator *iter,
			काष्ठा in6_addr *saddr, काष्ठा in6_addr *daddr,
			पूर्णांक flip)
अणु
	काष्ठा rds6_info_message minfo6;

	minfo6.seq = be64_to_cpu(inc->i_hdr.h_sequence);
	minfo6.len = be32_to_cpu(inc->i_hdr.h_len);
	minfo6.tos = inc->i_conn->c_tos;

	अगर (flip) अणु
		minfo6.laddr = *daddr;
		minfo6.faddr = *saddr;
		minfo6.lport = inc->i_hdr.h_dport;
		minfo6.fport = inc->i_hdr.h_sport;
	पूर्ण अन्यथा अणु
		minfo6.laddr = *saddr;
		minfo6.faddr = *daddr;
		minfo6.lport = inc->i_hdr.h_sport;
		minfo6.fport = inc->i_hdr.h_dport;
	पूर्ण

	minfo6.flags = 0;

	rds_info_copy(iter, &minfo6, माप(minfo6));
पूर्ण
#पूर्ण_अगर
