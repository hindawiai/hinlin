<शैली गुरु>
/*
 * net/tipc/bcast.c: TIPC broadcast code
 *
 * Copyright (c) 2004-2006, 2014-2017, Ericsson AB
 * Copyright (c) 2004, Intel Corporation.
 * Copyright (c) 2005, 2010-2011, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/tipc_config.h>
#समावेश "socket.h"
#समावेश "msg.h"
#समावेश "bcast.h"
#समावेश "link.h"
#समावेश "name_table.h"

#घोषणा BCLINK_WIN_DEFAULT  50	/* bcast link winकरोw size (शेष) */
#घोषणा BCLINK_WIN_MIN      32	/* bcast minimum link winकरोw size */

स्थिर अक्षर tipc_bclink_name[] = "broadcast-link";
अचिन्हित दीर्घ sysctl_tipc_bc_retruni __पढ़ो_mostly;

/**
 * काष्ठा tipc_bc_base - base काष्ठाure क्रम keeping broadcast send state
 * @link: broadcast send link काष्ठाure
 * @inputq: data input queue; will only carry SOCK_WAKEUP messages
 * @dests: array keeping number of reachable destinations per bearer
 * @primary_bearer: a bearer having links to all broadcast destinations, अगर any
 * @bcast_support: indicates अगर primary bearer, अगर any, supports broadcast
 * @क्रमce_bcast: क्रमces broadcast क्रम multicast traffic
 * @rcast_support: indicates अगर all peer nodes support replicast
 * @क्रमce_rcast: क्रमces replicast क्रम multicast traffic
 * @rc_ratio: dest count as percentage of cluster size where send method changes
 * @bc_threshold: calculated from rc_ratio; अगर dests > threshold use broadcast
 */
काष्ठा tipc_bc_base अणु
	काष्ठा tipc_link *link;
	काष्ठा sk_buff_head inputq;
	पूर्णांक dests[MAX_BEARERS];
	पूर्णांक primary_bearer;
	bool bcast_support;
	bool क्रमce_bcast;
	bool rcast_support;
	bool क्रमce_rcast;
	पूर्णांक rc_ratio;
	पूर्णांक bc_threshold;
पूर्ण;

अटल काष्ठा tipc_bc_base *tipc_bc_base(काष्ठा net *net)
अणु
	वापस tipc_net(net)->bcbase;
पूर्ण

/* tipc_bcast_get_mtu(): -get the MTU currently used by broadcast link
 * Note: the MTU is decremented to give room क्रम a tunnel header, in
 * हाल the message needs to be sent as replicast
 */
पूर्णांक tipc_bcast_get_mtu(काष्ठा net *net)
अणु
	वापस tipc_link_mss(tipc_bc_sndlink(net));
पूर्ण

व्योम tipc_bcast_toggle_rcast(काष्ठा net *net, bool supp)
अणु
	tipc_bc_base(net)->rcast_support = supp;
पूर्ण

अटल व्योम tipc_bcbase_calc_bc_threshold(काष्ठा net *net)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);
	पूर्णांक cluster_size = tipc_link_bc_peers(tipc_bc_sndlink(net));

	bb->bc_threshold = 1 + (cluster_size * bb->rc_ratio / 100);
पूर्ण

/* tipc_bcbase_select_primary(): find a bearer with links to all destinations,
 *                               अगर any, and make it primary bearer
 */
अटल व्योम tipc_bcbase_select_primary(काष्ठा net *net)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);
	पूर्णांक all_dests =  tipc_link_bc_peers(bb->link);
	पूर्णांक max_win = tipc_link_max_win(bb->link);
	पूर्णांक min_win = tipc_link_min_win(bb->link);
	पूर्णांक i, mtu, prim;

	bb->primary_bearer = INVALID_BEARER_ID;
	bb->bcast_support = true;

	अगर (!all_dests)
		वापस;

	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		अगर (!bb->dests[i])
			जारी;

		mtu = tipc_bearer_mtu(net, i);
		अगर (mtu < tipc_link_mtu(bb->link)) अणु
			tipc_link_set_mtu(bb->link, mtu);
			tipc_link_set_queue_limits(bb->link,
						   min_win,
						   max_win);
		पूर्ण
		bb->bcast_support &= tipc_bearer_bcast_support(net, i);
		अगर (bb->dests[i] < all_dests)
			जारी;

		bb->primary_bearer = i;

		/* Reduce risk that all nodes select same primary */
		अगर ((i ^ tipc_own_addr(net)) & 1)
			अवरोध;
	पूर्ण
	prim = bb->primary_bearer;
	अगर (prim != INVALID_BEARER_ID)
		bb->bcast_support = tipc_bearer_bcast_support(net, prim);
पूर्ण

व्योम tipc_bcast_inc_bearer_dst_cnt(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);

	tipc_bcast_lock(net);
	bb->dests[bearer_id]++;
	tipc_bcbase_select_primary(net);
	tipc_bcast_unlock(net);
पूर्ण

व्योम tipc_bcast_dec_bearer_dst_cnt(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);

	tipc_bcast_lock(net);
	bb->dests[bearer_id]--;
	tipc_bcbase_select_primary(net);
	tipc_bcast_unlock(net);
पूर्ण

/* tipc_bcbase_xmit - broadcast a packet queue across one or more bearers
 *
 * Note that number of reachable destinations, as indicated in the dests[]
 * array, may transitionally dअगरfer from the number of destinations indicated
 * in each sent buffer. We can sustain this. Excess destination nodes will
 * drop and never acknowledge the unexpected packets, and missing destinations
 * will either require retransmission (अगर they are just about to be added to
 * the bearer), or be हटाओd from the buffer's 'ackers' counter (अगर they
 * just went करोwn)
 */
अटल व्योम tipc_bcbase_xmit(काष्ठा net *net, काष्ठा sk_buff_head *xmitq)
अणु
	पूर्णांक bearer_id;
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);
	काष्ठा sk_buff *skb, *_skb;
	काष्ठा sk_buff_head _xmitq;

	अगर (skb_queue_empty(xmitq))
		वापस;

	/* The typical हाल: at least one bearer has links to all nodes */
	bearer_id = bb->primary_bearer;
	अगर (bearer_id >= 0) अणु
		tipc_bearer_bc_xmit(net, bearer_id, xmitq);
		वापस;
	पूर्ण

	/* We have to transmit across all bearers */
	__skb_queue_head_init(&_xmitq);
	क्रम (bearer_id = 0; bearer_id < MAX_BEARERS; bearer_id++) अणु
		अगर (!bb->dests[bearer_id])
			जारी;

		skb_queue_walk(xmitq, skb) अणु
			_skb = pskb_copy_क्रम_clone(skb, GFP_ATOMIC);
			अगर (!_skb)
				अवरोध;
			__skb_queue_tail(&_xmitq, _skb);
		पूर्ण
		tipc_bearer_bc_xmit(net, bearer_id, &_xmitq);
	पूर्ण
	__skb_queue_purge(xmitq);
	__skb_queue_purge(&_xmitq);
पूर्ण

अटल व्योम tipc_bcast_select_xmit_method(काष्ठा net *net, पूर्णांक dests,
					  काष्ठा tipc_mc_method *method)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);
	अचिन्हित दीर्घ exp = method->expires;

	/* Broadcast supported by used bearer/bearers? */
	अगर (!bb->bcast_support) अणु
		method->rcast = true;
		वापस;
	पूर्ण
	/* Any destinations which करोn't support replicast ? */
	अगर (!bb->rcast_support) अणु
		method->rcast = false;
		वापस;
	पूर्ण
	/* Can current method be changed ? */
	method->expires = jअगरfies + TIPC_METHOD_EXPIRE;
	अगर (method->mandatory)
		वापस;

	अगर (!(tipc_net(net)->capabilities & TIPC_MCAST_RBCTL) &&
	    समय_beक्रमe(jअगरfies, exp))
		वापस;

	/* Configuration as क्रमce 'broadcast' method */
	अगर (bb->क्रमce_bcast) अणु
		method->rcast = false;
		वापस;
	पूर्ण
	/* Configuration as क्रमce 'replicast' method */
	अगर (bb->क्रमce_rcast) अणु
		method->rcast = true;
		वापस;
	पूर्ण
	/* Configuration as 'autoselect' or शेष method */
	/* Determine method to use now */
	method->rcast = dests <= bb->bc_threshold;
पूर्ण

/* tipc_bcast_xmit - broadcast the buffer chain to all बाह्यal nodes
 * @net: the applicable net namespace
 * @pkts: chain of buffers containing message
 * @cong_link_cnt: set to 1 अगर broadcast link is congested, otherwise 0
 * Consumes the buffer chain.
 * Returns 0 अगर success, otherwise त्रुटि_सं: -EHOSTUNREACH,-EMSGSIZE
 */
पूर्णांक tipc_bcast_xmit(काष्ठा net *net, काष्ठा sk_buff_head *pkts,
		    u16 *cong_link_cnt)
अणु
	काष्ठा tipc_link *l = tipc_bc_sndlink(net);
	काष्ठा sk_buff_head xmitq;
	पूर्णांक rc = 0;

	__skb_queue_head_init(&xmitq);
	tipc_bcast_lock(net);
	अगर (tipc_link_bc_peers(l))
		rc = tipc_link_xmit(l, pkts, &xmitq);
	tipc_bcast_unlock(net);
	tipc_bcbase_xmit(net, &xmitq);
	__skb_queue_purge(pkts);
	अगर (rc == -ELINKCONG) अणु
		*cong_link_cnt = 1;
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

/* tipc_rcast_xmit - replicate and send a message to given destination nodes
 * @net: the applicable net namespace
 * @pkts: chain of buffers containing message
 * @dests: list of destination nodes
 * @cong_link_cnt: वापसs number of congested links
 * @cong_links: वापसs identities of congested links
 * Returns 0 अगर success, otherwise त्रुटि_सं
 */
अटल पूर्णांक tipc_rcast_xmit(काष्ठा net *net, काष्ठा sk_buff_head *pkts,
			   काष्ठा tipc_nlist *dests, u16 *cong_link_cnt)
अणु
	काष्ठा tipc_dest *dst, *पंचांगp;
	काष्ठा sk_buff_head _pkts;
	u32 dnode, selector;

	selector = msg_link_selector(buf_msg(skb_peek(pkts)));
	__skb_queue_head_init(&_pkts);

	list_क्रम_each_entry_safe(dst, पंचांगp, &dests->list, list) अणु
		dnode = dst->node;
		अगर (!tipc_msg_pskb_copy(dnode, pkts, &_pkts))
			वापस -ENOMEM;

		/* Any other वापस value than -ELINKCONG is ignored */
		अगर (tipc_node_xmit(net, &_pkts, dnode, selector) == -ELINKCONG)
			(*cong_link_cnt)++;
	पूर्ण
	वापस 0;
पूर्ण

/* tipc_mcast_send_sync - deliver a dummy message with SYN bit
 * @net: the applicable net namespace
 * @skb: socket buffer to copy
 * @method: send method to be used
 * @dests: destination nodes क्रम message.
 * Returns 0 अगर success, otherwise त्रुटि_सं
 */
अटल पूर्णांक tipc_mcast_send_sync(काष्ठा net *net, काष्ठा sk_buff *skb,
				काष्ठा tipc_mc_method *method,
				काष्ठा tipc_nlist *dests)
अणु
	काष्ठा tipc_msg *hdr, *_hdr;
	काष्ठा sk_buff_head पंचांगpq;
	काष्ठा sk_buff *_skb;
	u16 cong_link_cnt;
	पूर्णांक rc = 0;

	/* Is a cluster supporting with new capabilities ? */
	अगर (!(tipc_net(net)->capabilities & TIPC_MCAST_RBCTL))
		वापस 0;

	hdr = buf_msg(skb);
	अगर (msg_user(hdr) == MSG_FRAGMENTER)
		hdr = msg_inner_hdr(hdr);
	अगर (msg_type(hdr) != TIPC_MCAST_MSG)
		वापस 0;

	/* Allocate dummy message */
	_skb = tipc_buf_acquire(MCAST_H_SIZE, GFP_KERNEL);
	अगर (!_skb)
		वापस -ENOMEM;

	/* Preparing क्रम 'synching' header */
	msg_set_syn(hdr, 1);

	/* Copy skb's header पूर्णांकo a dummy header */
	skb_copy_to_linear_data(_skb, hdr, MCAST_H_SIZE);
	skb_orphan(_skb);

	/* Reverse method क्रम dummy message */
	_hdr = buf_msg(_skb);
	msg_set_size(_hdr, MCAST_H_SIZE);
	msg_set_is_rcast(_hdr, !msg_is_rcast(hdr));
	msg_set_errcode(_hdr, TIPC_ERR_NO_PORT);

	__skb_queue_head_init(&पंचांगpq);
	__skb_queue_tail(&पंचांगpq, _skb);
	अगर (method->rcast)
		rc = tipc_bcast_xmit(net, &पंचांगpq, &cong_link_cnt);
	अन्यथा
		rc = tipc_rcast_xmit(net, &पंचांगpq, dests, &cong_link_cnt);

	/* This queue should normally be empty by now */
	__skb_queue_purge(&पंचांगpq);

	वापस rc;
पूर्ण

/* tipc_mcast_xmit - deliver message to indicated destination nodes
 *                   and to identअगरied node local sockets
 * @net: the applicable net namespace
 * @pkts: chain of buffers containing message
 * @method: send method to be used
 * @dests: destination nodes क्रम message.
 * @cong_link_cnt: वापसs number of encountered congested destination links
 * Consumes buffer chain.
 * Returns 0 अगर success, otherwise त्रुटि_सं
 */
पूर्णांक tipc_mcast_xmit(काष्ठा net *net, काष्ठा sk_buff_head *pkts,
		    काष्ठा tipc_mc_method *method, काष्ठा tipc_nlist *dests,
		    u16 *cong_link_cnt)
अणु
	काष्ठा sk_buff_head inputq, localq;
	bool rcast = method->rcast;
	काष्ठा tipc_msg *hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक rc = 0;

	skb_queue_head_init(&inputq);
	__skb_queue_head_init(&localq);

	/* Clone packets beक्रमe they are consumed by next call */
	अगर (dests->local && !tipc_msg_reassemble(pkts, &localq)) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण
	/* Send according to determined transmit method */
	अगर (dests->remote) अणु
		tipc_bcast_select_xmit_method(net, dests->remote, method);

		skb = skb_peek(pkts);
		hdr = buf_msg(skb);
		अगर (msg_user(hdr) == MSG_FRAGMENTER)
			hdr = msg_inner_hdr(hdr);
		msg_set_is_rcast(hdr, method->rcast);

		/* Switch method ? */
		अगर (rcast != method->rcast) अणु
			rc = tipc_mcast_send_sync(net, skb, method, dests);
			अगर (unlikely(rc)) अणु
				pr_err("Unable to send SYN: method %d, rc %d\n",
				       rcast, rc);
				जाओ निकास;
			पूर्ण
		पूर्ण

		अगर (method->rcast)
			rc = tipc_rcast_xmit(net, pkts, dests, cong_link_cnt);
		अन्यथा
			rc = tipc_bcast_xmit(net, pkts, cong_link_cnt);
	पूर्ण

	अगर (dests->local) अणु
		tipc_loopback_trace(net, &localq);
		tipc_sk_mcast_rcv(net, &localq, &inputq);
	पूर्ण
निकास:
	/* This queue should normally be empty by now */
	__skb_queue_purge(pkts);
	वापस rc;
पूर्ण

/* tipc_bcast_rcv - receive a broadcast packet, and deliver to rcv link
 *
 * RCU is locked, no other locks set
 */
पूर्णांक tipc_bcast_rcv(काष्ठा net *net, काष्ठा tipc_link *l, काष्ठा sk_buff *skb)
अणु
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	काष्ठा sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	काष्ठा sk_buff_head xmitq;
	पूर्णांक rc;

	__skb_queue_head_init(&xmitq);

	अगर (msg_mc_netid(hdr) != tipc_netid(net) || !tipc_link_is_up(l)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	tipc_bcast_lock(net);
	अगर (msg_user(hdr) == BCAST_PROTOCOL)
		rc = tipc_link_bc_nack_rcv(l, skb, &xmitq);
	अन्यथा
		rc = tipc_link_rcv(l, skb, शून्य);
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	अगर (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);

	वापस rc;
पूर्ण

/* tipc_bcast_ack_rcv - receive and handle a broadcast acknowledge
 *
 * RCU is locked, no other locks set
 */
व्योम tipc_bcast_ack_rcv(काष्ठा net *net, काष्ठा tipc_link *l,
			काष्ठा tipc_msg *hdr)
अणु
	काष्ठा sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	u16 acked = msg_bcast_ack(hdr);
	काष्ठा sk_buff_head xmitq;

	/* Ignore bc acks sent by peer beक्रमe bcast synch poपूर्णांक was received */
	अगर (msg_bc_ack_invalid(hdr))
		वापस;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_lock(net);
	tipc_link_bc_ack_rcv(l, acked, 0, शून्य, &xmitq, शून्य);
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	अगर (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);
पूर्ण

/* tipc_bcast_synch_rcv -  check and update rcv link with peer's send state
 *
 * RCU is locked, no other locks set
 */
पूर्णांक tipc_bcast_sync_rcv(काष्ठा net *net, काष्ठा tipc_link *l,
			काष्ठा tipc_msg *hdr,
			काष्ठा sk_buff_head *retrq)
अणु
	काष्ठा sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	काष्ठा tipc_gap_ack_blks *ga;
	काष्ठा sk_buff_head xmitq;
	पूर्णांक rc = 0;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_lock(net);
	अगर (msg_type(hdr) != STATE_MSG) अणु
		tipc_link_bc_init_rcv(l, hdr);
	पूर्ण अन्यथा अगर (!msg_bc_ack_invalid(hdr)) अणु
		tipc_get_gap_ack_blks(&ga, l, hdr, false);
		अगर (!sysctl_tipc_bc_retruni)
			retrq = &xmitq;
		rc = tipc_link_bc_ack_rcv(l, msg_bcast_ack(hdr),
					  msg_bc_gap(hdr), ga, &xmitq,
					  retrq);
		rc |= tipc_link_bc_sync_rcv(l, hdr, &xmitq);
	पूर्ण
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	अगर (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);
	वापस rc;
पूर्ण

/* tipc_bcast_add_peer - add a peer node to broadcast link and bearer
 *
 * RCU is locked, node lock is set
 */
व्योम tipc_bcast_add_peer(काष्ठा net *net, काष्ठा tipc_link *uc_l,
			 काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_link *snd_l = tipc_bc_sndlink(net);

	tipc_bcast_lock(net);
	tipc_link_add_bc_peer(snd_l, uc_l, xmitq);
	tipc_bcbase_select_primary(net);
	tipc_bcbase_calc_bc_threshold(net);
	tipc_bcast_unlock(net);
पूर्ण

/* tipc_bcast_हटाओ_peer - हटाओ a peer node from broadcast link and bearer
 *
 * RCU is locked, node lock is set
 */
व्योम tipc_bcast_हटाओ_peer(काष्ठा net *net, काष्ठा tipc_link *rcv_l)
अणु
	काष्ठा tipc_link *snd_l = tipc_bc_sndlink(net);
	काष्ठा sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	काष्ठा sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_lock(net);
	tipc_link_हटाओ_bc_peer(snd_l, rcv_l, &xmitq);
	tipc_bcbase_select_primary(net);
	tipc_bcbase_calc_bc_threshold(net);
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	अगर (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);
पूर्ण

पूर्णांक tipc_bclink_reset_stats(काष्ठा net *net, काष्ठा tipc_link *l)
अणु
	अगर (!l)
		वापस -ENOPROTOOPT;

	tipc_bcast_lock(net);
	tipc_link_reset_stats(l);
	tipc_bcast_unlock(net);
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_bc_link_set_queue_limits(काष्ठा net *net, u32 max_win)
अणु
	काष्ठा tipc_link *l = tipc_bc_sndlink(net);

	अगर (!l)
		वापस -ENOPROTOOPT;
	अगर (max_win < BCLINK_WIN_MIN)
		max_win = BCLINK_WIN_MIN;
	अगर (max_win > TIPC_MAX_LINK_WIN)
		वापस -EINVAL;
	tipc_bcast_lock(net);
	tipc_link_set_queue_limits(l, tipc_link_min_win(l), max_win);
	tipc_bcast_unlock(net);
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_bc_link_set_broadcast_mode(काष्ठा net *net, u32 bc_mode)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);

	चयन (bc_mode) अणु
	हाल BCLINK_MODE_BCAST:
		अगर (!bb->bcast_support)
			वापस -ENOPROTOOPT;

		bb->क्रमce_bcast = true;
		bb->क्रमce_rcast = false;
		अवरोध;
	हाल BCLINK_MODE_RCAST:
		अगर (!bb->rcast_support)
			वापस -ENOPROTOOPT;

		bb->क्रमce_bcast = false;
		bb->क्रमce_rcast = true;
		अवरोध;
	हाल BCLINK_MODE_SEL:
		अगर (!bb->bcast_support || !bb->rcast_support)
			वापस -ENOPROTOOPT;

		bb->क्रमce_bcast = false;
		bb->क्रमce_rcast = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_bc_link_set_broadcast_ratio(काष्ठा net *net, u32 bc_ratio)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);

	अगर (!bb->bcast_support || !bb->rcast_support)
		वापस -ENOPROTOOPT;

	अगर (bc_ratio > 100 || bc_ratio <= 0)
		वापस -EINVAL;

	bb->rc_ratio = bc_ratio;
	tipc_bcast_lock(net);
	tipc_bcbase_calc_bc_threshold(net);
	tipc_bcast_unlock(net);

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_bc_link_set(काष्ठा net *net, काष्ठा nlattr *attrs[])
अणु
	पूर्णांक err;
	u32 win;
	u32 bc_mode;
	u32 bc_ratio;
	काष्ठा nlattr *props[TIPC_NLA_PROP_MAX + 1];

	अगर (!attrs[TIPC_NLA_LINK_PROP])
		वापस -EINVAL;

	err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_LINK_PROP], props);
	अगर (err)
		वापस err;

	अगर (!props[TIPC_NLA_PROP_WIN] &&
	    !props[TIPC_NLA_PROP_BROADCAST] &&
	    !props[TIPC_NLA_PROP_BROADCAST_RATIO]) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (props[TIPC_NLA_PROP_BROADCAST]) अणु
		bc_mode = nla_get_u32(props[TIPC_NLA_PROP_BROADCAST]);
		err = tipc_bc_link_set_broadcast_mode(net, bc_mode);
	पूर्ण

	अगर (!err && props[TIPC_NLA_PROP_BROADCAST_RATIO]) अणु
		bc_ratio = nla_get_u32(props[TIPC_NLA_PROP_BROADCAST_RATIO]);
		err = tipc_bc_link_set_broadcast_ratio(net, bc_ratio);
	पूर्ण

	अगर (!err && props[TIPC_NLA_PROP_WIN]) अणु
		win = nla_get_u32(props[TIPC_NLA_PROP_WIN]);
		err = tipc_bc_link_set_queue_limits(net, win);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक tipc_bcast_init(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_bc_base *bb = शून्य;
	काष्ठा tipc_link *l = शून्य;

	bb = kzalloc(माप(*bb), GFP_KERNEL);
	अगर (!bb)
		जाओ enomem;
	tn->bcbase = bb;
	spin_lock_init(&tipc_net(net)->bघड़ी);

	अगर (!tipc_link_bc_create(net, 0, 0, शून्य,
				 FB_MTU,
				 BCLINK_WIN_DEFAULT,
				 BCLINK_WIN_DEFAULT,
				 0,
				 &bb->inputq,
				 शून्य,
				 शून्य,
				 &l))
		जाओ enomem;
	bb->link = l;
	tn->bcl = l;
	bb->rc_ratio = 10;
	bb->rcast_support = true;
	वापस 0;
enomem:
	kमुक्त(bb);
	kमुक्त(l);
	वापस -ENOMEM;
पूर्ण

व्योम tipc_bcast_stop(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);

	synchronize_net();
	kमुक्त(tn->bcbase);
	kमुक्त(tn->bcl);
पूर्ण

व्योम tipc_nlist_init(काष्ठा tipc_nlist *nl, u32 self)
अणु
	स_रखो(nl, 0, माप(*nl));
	INIT_LIST_HEAD(&nl->list);
	nl->self = self;
पूर्ण

व्योम tipc_nlist_add(काष्ठा tipc_nlist *nl, u32 node)
अणु
	अगर (node == nl->self)
		nl->local = true;
	अन्यथा अगर (tipc_dest_push(&nl->list, node, 0))
		nl->remote++;
पूर्ण

व्योम tipc_nlist_del(काष्ठा tipc_nlist *nl, u32 node)
अणु
	अगर (node == nl->self)
		nl->local = false;
	अन्यथा अगर (tipc_dest_del(&nl->list, node, 0))
		nl->remote--;
पूर्ण

व्योम tipc_nlist_purge(काष्ठा tipc_nlist *nl)
अणु
	tipc_dest_list_purge(&nl->list);
	nl->remote = 0;
	nl->local = false;
पूर्ण

u32 tipc_bcast_get_mode(काष्ठा net *net)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);

	अगर (bb->क्रमce_bcast)
		वापस BCLINK_MODE_BCAST;

	अगर (bb->क्रमce_rcast)
		वापस BCLINK_MODE_RCAST;

	अगर (bb->bcast_support && bb->rcast_support)
		वापस BCLINK_MODE_SEL;

	वापस 0;
पूर्ण

u32 tipc_bcast_get_broadcast_ratio(काष्ठा net *net)
अणु
	काष्ठा tipc_bc_base *bb = tipc_bc_base(net);

	वापस bb->rc_ratio;
पूर्ण

व्योम tipc_mcast_filter_msg(काष्ठा net *net, काष्ठा sk_buff_head *defq,
			   काष्ठा sk_buff_head *inputq)
अणु
	काष्ठा sk_buff *skb, *_skb, *पंचांगp;
	काष्ठा tipc_msg *hdr, *_hdr;
	bool match = false;
	u32 node, port;

	skb = skb_peek(inputq);
	अगर (!skb)
		वापस;

	hdr = buf_msg(skb);

	अगर (likely(!msg_is_syn(hdr) && skb_queue_empty(defq)))
		वापस;

	node = msg_orignode(hdr);
	अगर (node == tipc_own_addr(net))
		वापस;

	port = msg_origport(hdr);

	/* Has the twin SYN message alपढ़ोy arrived ? */
	skb_queue_walk(defq, _skb) अणु
		_hdr = buf_msg(_skb);
		अगर (msg_orignode(_hdr) != node)
			जारी;
		अगर (msg_origport(_hdr) != port)
			जारी;
		match = true;
		अवरोध;
	पूर्ण

	अगर (!match) अणु
		अगर (!msg_is_syn(hdr))
			वापस;
		__skb_dequeue(inputq);
		__skb_queue_tail(defq, skb);
		वापस;
	पूर्ण

	/* Deliver non-SYN message from other link, otherwise queue it */
	अगर (!msg_is_syn(hdr)) अणु
		अगर (msg_is_rcast(hdr) != msg_is_rcast(_hdr))
			वापस;
		__skb_dequeue(inputq);
		__skb_queue_tail(defq, skb);
		वापस;
	पूर्ण

	/* Queue non-SYN/SYN message from same link */
	अगर (msg_is_rcast(hdr) == msg_is_rcast(_hdr)) अणु
		__skb_dequeue(inputq);
		__skb_queue_tail(defq, skb);
		वापस;
	पूर्ण

	/* Matching SYN messages => वापस the one with data, अगर any */
	__skb_unlink(_skb, defq);
	अगर (msg_data_sz(hdr)) अणु
		kमुक्त_skb(_skb);
	पूर्ण अन्यथा अणु
		__skb_dequeue(inputq);
		kमुक्त_skb(skb);
		__skb_queue_tail(inputq, _skb);
	पूर्ण

	/* Deliver subsequent non-SYN messages from same peer */
	skb_queue_walk_safe(defq, _skb, पंचांगp) अणु
		_hdr = buf_msg(_skb);
		अगर (msg_orignode(_hdr) != node)
			जारी;
		अगर (msg_origport(_hdr) != port)
			जारी;
		अगर (msg_is_syn(_hdr))
			अवरोध;
		__skb_unlink(_skb, defq);
		__skb_queue_tail(inputq, _skb);
	पूर्ण
पूर्ण
