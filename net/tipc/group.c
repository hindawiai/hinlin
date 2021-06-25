<शैली गुरु>
/*
 * net/tipc/group.c: TIPC group messaging code
 *
 * Copyright (c) 2017, Ericsson AB
 * Copyright (c) 2020, Red Hat Inc
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

#समावेश "core.h"
#समावेश "addr.h"
#समावेश "group.h"
#समावेश "bcast.h"
#समावेश "topsrv.h"
#समावेश "msg.h"
#समावेश "socket.h"
#समावेश "node.h"
#समावेश "name_table.h"
#समावेश "subscr.h"

#घोषणा ADV_UNIT (((MAX_MSG_SIZE + MAX_H_SIZE) / FLOWCTL_BLK_SZ) + 1)
#घोषणा ADV_IDLE ADV_UNIT
#घोषणा ADV_ACTIVE (ADV_UNIT * 12)

क्रमागत mbr_state अणु
	MBR_JOINING,
	MBR_PUBLISHED,
	MBR_JOINED,
	MBR_PENDING,
	MBR_ACTIVE,
	MBR_RECLAIMING,
	MBR_REMITTED,
	MBR_LEAVING
पूर्ण;

काष्ठा tipc_member अणु
	काष्ठा rb_node tree_node;
	काष्ठा list_head list;
	काष्ठा list_head small_win;
	काष्ठा sk_buff_head deferredq;
	काष्ठा tipc_group *group;
	u32 node;
	u32 port;
	u32 instance;
	क्रमागत mbr_state state;
	u16 advertised;
	u16 winकरोw;
	u16 bc_rcv_nxt;
	u16 bc_syncpt;
	u16 bc_acked;
पूर्ण;

काष्ठा tipc_group अणु
	काष्ठा rb_root members;
	काष्ठा list_head small_win;
	काष्ठा list_head pending;
	काष्ठा list_head active;
	काष्ठा tipc_nlist dests;
	काष्ठा net *net;
	पूर्णांक subid;
	u32 type;
	u32 instance;
	u32 scope;
	u32 portid;
	u16 member_cnt;
	u16 active_cnt;
	u16 max_active;
	u16 bc_snd_nxt;
	u16 bc_ackers;
	bool *खोलो;
	bool loopback;
	bool events;
पूर्ण;

अटल व्योम tipc_group_proto_xmit(काष्ठा tipc_group *grp, काष्ठा tipc_member *m,
				  पूर्णांक mtyp, काष्ठा sk_buff_head *xmitq);

अटल व्योम tipc_group_खोलो(काष्ठा tipc_member *m, bool *wakeup)
अणु
	*wakeup = false;
	अगर (list_empty(&m->small_win))
		वापस;
	list_del_init(&m->small_win);
	*m->group->खोलो = true;
	*wakeup = true;
पूर्ण

अटल व्योम tipc_group_decr_active(काष्ठा tipc_group *grp,
				   काष्ठा tipc_member *m)
अणु
	अगर (m->state == MBR_ACTIVE || m->state == MBR_RECLAIMING ||
	    m->state == MBR_REMITTED)
		grp->active_cnt--;
पूर्ण

अटल पूर्णांक tipc_group_rcvbuf_limit(काष्ठा tipc_group *grp)
अणु
	पूर्णांक max_active, active_pool, idle_pool;
	पूर्णांक mcnt = grp->member_cnt + 1;

	/* Limit simultaneous reception from other members */
	max_active = min(mcnt / 8, 64);
	max_active = max(max_active, 16);
	grp->max_active = max_active;

	/* Reserve blocks क्रम active and idle members */
	active_pool = max_active * ADV_ACTIVE;
	idle_pool = (mcnt - max_active) * ADV_IDLE;

	/* Scale to bytes, considering worst-हाल truesize/msgsize ratio */
	वापस (active_pool + idle_pool) * FLOWCTL_BLK_SZ * 4;
पूर्ण

u16 tipc_group_bc_snd_nxt(काष्ठा tipc_group *grp)
अणु
	वापस grp->bc_snd_nxt;
पूर्ण

अटल bool tipc_group_is_receiver(काष्ठा tipc_member *m)
अणु
	वापस m && m->state != MBR_JOINING && m->state != MBR_LEAVING;
पूर्ण

अटल bool tipc_group_is_sender(काष्ठा tipc_member *m)
अणु
	वापस m && m->state != MBR_JOINING && m->state != MBR_PUBLISHED;
पूर्ण

u32 tipc_group_exclude(काष्ठा tipc_group *grp)
अणु
	अगर (!grp->loopback)
		वापस grp->portid;
	वापस 0;
पूर्ण

काष्ठा tipc_group *tipc_group_create(काष्ठा net *net, u32 portid,
				     काष्ठा tipc_group_req *mreq,
				     bool *group_is_खोलो)
अणु
	u32 filter = TIPC_SUB_PORTS | TIPC_SUB_NO_STATUS;
	bool global = mreq->scope != TIPC_NODE_SCOPE;
	काष्ठा tipc_group *grp;
	u32 type = mreq->type;

	grp = kzalloc(माप(*grp), GFP_ATOMIC);
	अगर (!grp)
		वापस शून्य;
	tipc_nlist_init(&grp->dests, tipc_own_addr(net));
	INIT_LIST_HEAD(&grp->small_win);
	INIT_LIST_HEAD(&grp->active);
	INIT_LIST_HEAD(&grp->pending);
	grp->members = RB_ROOT;
	grp->net = net;
	grp->portid = portid;
	grp->type = type;
	grp->instance = mreq->instance;
	grp->scope = mreq->scope;
	grp->loopback = mreq->flags & TIPC_GROUP_LOOPBACK;
	grp->events = mreq->flags & TIPC_GROUP_MEMBER_EVTS;
	grp->खोलो = group_is_खोलो;
	*grp->खोलो = false;
	filter |= global ? TIPC_SUB_CLUSTER_SCOPE : TIPC_SUB_NODE_SCOPE;
	अगर (tipc_topsrv_kern_subscr(net, portid, type, 0, ~0,
				    filter, &grp->subid))
		वापस grp;
	kमुक्त(grp);
	वापस शून्य;
पूर्ण

व्योम tipc_group_join(काष्ठा net *net, काष्ठा tipc_group *grp, पूर्णांक *sk_rcvbuf)
अणु
	काष्ठा rb_root *tree = &grp->members;
	काष्ठा tipc_member *m, *पंचांगp;
	काष्ठा sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);
	rbtree_postorder_क्रम_each_entry_safe(m, पंचांगp, tree, tree_node) अणु
		tipc_group_proto_xmit(grp, m, GRP_JOIN_MSG, &xmitq);
		tipc_group_update_member(m, 0);
	पूर्ण
	tipc_node_distr_xmit(net, &xmitq);
	*sk_rcvbuf = tipc_group_rcvbuf_limit(grp);
पूर्ण

व्योम tipc_group_delete(काष्ठा net *net, काष्ठा tipc_group *grp)
अणु
	काष्ठा rb_root *tree = &grp->members;
	काष्ठा tipc_member *m, *पंचांगp;
	काष्ठा sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);

	rbtree_postorder_क्रम_each_entry_safe(m, पंचांगp, tree, tree_node) अणु
		tipc_group_proto_xmit(grp, m, GRP_LEAVE_MSG, &xmitq);
		__skb_queue_purge(&m->deferredq);
		list_del(&m->list);
		kमुक्त(m);
	पूर्ण
	tipc_node_distr_xmit(net, &xmitq);
	tipc_nlist_purge(&grp->dests);
	tipc_topsrv_kern_unsubscr(net, grp->subid);
	kमुक्त(grp);
पूर्ण

अटल काष्ठा tipc_member *tipc_group_find_member(काष्ठा tipc_group *grp,
						  u32 node, u32 port)
अणु
	काष्ठा rb_node *n = grp->members.rb_node;
	u64 nkey, key = (u64)node << 32 | port;
	काष्ठा tipc_member *m;

	जबतक (n) अणु
		m = container_of(n, काष्ठा tipc_member, tree_node);
		nkey = (u64)m->node << 32 | m->port;
		अगर (key < nkey)
			n = n->rb_left;
		अन्यथा अगर (key > nkey)
			n = n->rb_right;
		अन्यथा
			वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा tipc_member *tipc_group_find_dest(काष्ठा tipc_group *grp,
						u32 node, u32 port)
अणु
	काष्ठा tipc_member *m;

	m = tipc_group_find_member(grp, node, port);
	अगर (m && tipc_group_is_receiver(m))
		वापस m;
	वापस शून्य;
पूर्ण

अटल काष्ठा tipc_member *tipc_group_find_node(काष्ठा tipc_group *grp,
						u32 node)
अणु
	काष्ठा tipc_member *m;
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&grp->members); n; n = rb_next(n)) अणु
		m = container_of(n, काष्ठा tipc_member, tree_node);
		अगर (m->node == node)
			वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक tipc_group_add_to_tree(काष्ठा tipc_group *grp,
				  काष्ठा tipc_member *m)
अणु
	u64 nkey, key = (u64)m->node << 32 | m->port;
	काष्ठा rb_node **n, *parent = शून्य;
	काष्ठा tipc_member *पंचांगp;

	n = &grp->members.rb_node;
	जबतक (*n) अणु
		पंचांगp = container_of(*n, काष्ठा tipc_member, tree_node);
		parent = *n;
		पंचांगp = container_of(parent, काष्ठा tipc_member, tree_node);
		nkey = (u64)पंचांगp->node << 32 | पंचांगp->port;
		अगर (key < nkey)
			n = &(*n)->rb_left;
		अन्यथा अगर (key > nkey)
			n = &(*n)->rb_right;
		अन्यथा
			वापस -EEXIST;
	पूर्ण
	rb_link_node(&m->tree_node, parent, n);
	rb_insert_color(&m->tree_node, &grp->members);
	वापस 0;
पूर्ण

अटल काष्ठा tipc_member *tipc_group_create_member(काष्ठा tipc_group *grp,
						    u32 node, u32 port,
						    u32 instance, पूर्णांक state)
अणु
	काष्ठा tipc_member *m;
	पूर्णांक ret;

	m = kzalloc(माप(*m), GFP_ATOMIC);
	अगर (!m)
		वापस शून्य;
	INIT_LIST_HEAD(&m->list);
	INIT_LIST_HEAD(&m->small_win);
	__skb_queue_head_init(&m->deferredq);
	m->group = grp;
	m->node = node;
	m->port = port;
	m->instance = instance;
	m->bc_acked = grp->bc_snd_nxt - 1;
	ret = tipc_group_add_to_tree(grp, m);
	अगर (ret < 0) अणु
		kमुक्त(m);
		वापस शून्य;
	पूर्ण
	grp->member_cnt++;
	tipc_nlist_add(&grp->dests, m->node);
	m->state = state;
	वापस m;
पूर्ण

व्योम tipc_group_add_member(काष्ठा tipc_group *grp, u32 node,
			   u32 port, u32 instance)
अणु
	tipc_group_create_member(grp, node, port, instance, MBR_PUBLISHED);
पूर्ण

अटल व्योम tipc_group_delete_member(काष्ठा tipc_group *grp,
				     काष्ठा tipc_member *m)
अणु
	rb_erase(&m->tree_node, &grp->members);
	grp->member_cnt--;

	/* Check अगर we were रुकोing क्रम replicast ack from this member */
	अगर (grp->bc_ackers && less(m->bc_acked, grp->bc_snd_nxt - 1))
		grp->bc_ackers--;

	list_del_init(&m->list);
	list_del_init(&m->small_win);
	tipc_group_decr_active(grp, m);

	/* If last member on a node, हटाओ node from dest list */
	अगर (!tipc_group_find_node(grp, m->node))
		tipc_nlist_del(&grp->dests, m->node);

	kमुक्त(m);
पूर्ण

काष्ठा tipc_nlist *tipc_group_dests(काष्ठा tipc_group *grp)
अणु
	वापस &grp->dests;
पूर्ण

व्योम tipc_group_self(काष्ठा tipc_group *grp, काष्ठा tipc_service_range *seq,
		     पूर्णांक *scope)
अणु
	seq->type = grp->type;
	seq->lower = grp->instance;
	seq->upper = grp->instance;
	*scope = grp->scope;
पूर्ण

व्योम tipc_group_update_member(काष्ठा tipc_member *m, पूर्णांक len)
अणु
	काष्ठा tipc_group *grp = m->group;
	काष्ठा tipc_member *_m, *पंचांगp;

	अगर (!tipc_group_is_receiver(m))
		वापस;

	m->winकरोw -= len;

	अगर (m->winकरोw >= ADV_IDLE)
		वापस;

	list_del_init(&m->small_win);

	/* Sort member पूर्णांकo small_winकरोw members' list */
	list_क्रम_each_entry_safe(_m, पंचांगp, &grp->small_win, small_win) अणु
		अगर (_m->winकरोw > m->winकरोw)
			अवरोध;
	पूर्ण
	list_add_tail(&m->small_win, &_m->small_win);
पूर्ण

व्योम tipc_group_update_bc_members(काष्ठा tipc_group *grp, पूर्णांक len, bool ack)
अणु
	u16 prev = grp->bc_snd_nxt - 1;
	काष्ठा tipc_member *m;
	काष्ठा rb_node *n;
	u16 ackers = 0;

	क्रम (n = rb_first(&grp->members); n; n = rb_next(n)) अणु
		m = container_of(n, काष्ठा tipc_member, tree_node);
		अगर (tipc_group_is_receiver(m)) अणु
			tipc_group_update_member(m, len);
			m->bc_acked = prev;
			ackers++;
		पूर्ण
	पूर्ण

	/* Mark number of acknowledges to expect, अगर any */
	अगर (ack)
		grp->bc_ackers = ackers;
	grp->bc_snd_nxt++;
पूर्ण

bool tipc_group_cong(काष्ठा tipc_group *grp, u32 dnode, u32 dport,
		     पूर्णांक len, काष्ठा tipc_member **mbr)
अणु
	काष्ठा sk_buff_head xmitq;
	काष्ठा tipc_member *m;
	पूर्णांक adv, state;

	m = tipc_group_find_dest(grp, dnode, dport);
	अगर (!tipc_group_is_receiver(m)) अणु
		*mbr = शून्य;
		वापस false;
	पूर्ण
	*mbr = m;

	अगर (m->winकरोw >= len)
		वापस false;

	*grp->खोलो = false;

	/* If not fully advertised, करो it now to prevent mutual blocking */
	adv = m->advertised;
	state = m->state;
	अगर (state == MBR_JOINED && adv == ADV_IDLE)
		वापस true;
	अगर (state == MBR_ACTIVE && adv == ADV_ACTIVE)
		वापस true;
	अगर (state == MBR_PENDING && adv == ADV_IDLE)
		वापस true;
	__skb_queue_head_init(&xmitq);
	tipc_group_proto_xmit(grp, m, GRP_ADV_MSG, &xmitq);
	tipc_node_distr_xmit(grp->net, &xmitq);
	वापस true;
पूर्ण

bool tipc_group_bc_cong(काष्ठा tipc_group *grp, पूर्णांक len)
अणु
	काष्ठा tipc_member *m = शून्य;

	/* If prev bcast was replicast, reject until all receivers have acked */
	अगर (grp->bc_ackers) अणु
		*grp->खोलो = false;
		वापस true;
	पूर्ण
	अगर (list_empty(&grp->small_win))
		वापस false;

	m = list_first_entry(&grp->small_win, काष्ठा tipc_member, small_win);
	अगर (m->winकरोw >= len)
		वापस false;

	वापस tipc_group_cong(grp, m->node, m->port, len, &m);
पूर्ण

/* tipc_group_sort_msg() - sort msg पूर्णांकo queue by bcast sequence number
 */
अटल व्योम tipc_group_sort_msg(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *defq)
अणु
	काष्ठा tipc_msg *_hdr, *hdr = buf_msg(skb);
	u16 bc_seqno = msg_grp_bc_seqno(hdr);
	काष्ठा sk_buff *_skb, *पंचांगp;
	पूर्णांक mtyp = msg_type(hdr);

	/* Bcast/mcast may be bypassed by ucast or other bcast, - sort it in */
	अगर (mtyp == TIPC_GRP_BCAST_MSG || mtyp == TIPC_GRP_MCAST_MSG) अणु
		skb_queue_walk_safe(defq, _skb, पंचांगp) अणु
			_hdr = buf_msg(_skb);
			अगर (!less(bc_seqno, msg_grp_bc_seqno(_hdr)))
				जारी;
			__skb_queue_beक्रमe(defq, _skb, skb);
			वापस;
		पूर्ण
		/* Bcast was not bypassed, - add to tail */
	पूर्ण
	/* Unicasts are never bypassed, - always add to tail */
	__skb_queue_tail(defq, skb);
पूर्ण

/* tipc_group_filter_msg() - determine अगर we should accept arriving message
 */
व्योम tipc_group_filter_msg(काष्ठा tipc_group *grp, काष्ठा sk_buff_head *inputq,
			   काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा sk_buff *skb = __skb_dequeue(inputq);
	bool ack, deliver, update, leave = false;
	काष्ठा sk_buff_head *defq;
	काष्ठा tipc_member *m;
	काष्ठा tipc_msg *hdr;
	u32 node, port;
	पूर्णांक mtyp, blks;

	अगर (!skb)
		वापस;

	hdr = buf_msg(skb);
	node =  msg_orignode(hdr);
	port = msg_origport(hdr);

	अगर (!msg_in_group(hdr))
		जाओ drop;

	m = tipc_group_find_member(grp, node, port);
	अगर (!tipc_group_is_sender(m))
		जाओ drop;

	अगर (less(msg_grp_bc_seqno(hdr), m->bc_rcv_nxt))
		जाओ drop;

	TIPC_SKB_CB(skb)->orig_member = m->instance;
	defq = &m->deferredq;
	tipc_group_sort_msg(skb, defq);

	जबतक ((skb = skb_peek(defq))) अणु
		hdr = buf_msg(skb);
		mtyp = msg_type(hdr);
		blks = msg_blocks(hdr);
		deliver = true;
		ack = false;
		update = false;

		अगर (more(msg_grp_bc_seqno(hdr), m->bc_rcv_nxt))
			अवरोध;

		/* Decide what to करो with message */
		चयन (mtyp) अणु
		हाल TIPC_GRP_MCAST_MSG:
			अगर (msg_nameinst(hdr) != grp->instance) अणु
				update = true;
				deliver = false;
			पूर्ण
			fallthrough;
		हाल TIPC_GRP_BCAST_MSG:
			m->bc_rcv_nxt++;
			ack = msg_grp_bc_ack_req(hdr);
			अवरोध;
		हाल TIPC_GRP_UCAST_MSG:
			अवरोध;
		हाल TIPC_GRP_MEMBER_EVT:
			अगर (m->state == MBR_LEAVING)
				leave = true;
			अगर (!grp->events)
				deliver = false;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* Execute decisions */
		__skb_dequeue(defq);
		अगर (deliver)
			__skb_queue_tail(inputq, skb);
		अन्यथा
			kमुक्त_skb(skb);

		अगर (ack)
			tipc_group_proto_xmit(grp, m, GRP_ACK_MSG, xmitq);

		अगर (leave) अणु
			__skb_queue_purge(defq);
			tipc_group_delete_member(grp, m);
			अवरोध;
		पूर्ण
		अगर (!update)
			जारी;

		tipc_group_update_rcv_win(grp, blks, node, port, xmitq);
	पूर्ण
	वापस;
drop:
	kमुक्त_skb(skb);
पूर्ण

व्योम tipc_group_update_rcv_win(काष्ठा tipc_group *grp, पूर्णांक blks, u32 node,
			       u32 port, काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा list_head *active = &grp->active;
	पूर्णांक max_active = grp->max_active;
	पूर्णांक reclaim_limit = max_active * 3 / 4;
	पूर्णांक active_cnt = grp->active_cnt;
	काष्ठा tipc_member *m, *rm, *pm;

	m = tipc_group_find_member(grp, node, port);
	अगर (!m)
		वापस;

	m->advertised -= blks;

	चयन (m->state) अणु
	हाल MBR_JOINED:
		/* First, decide अगर member can go active */
		अगर (active_cnt <= max_active) अणु
			m->state = MBR_ACTIVE;
			list_add_tail(&m->list, active);
			grp->active_cnt++;
			tipc_group_proto_xmit(grp, m, GRP_ADV_MSG, xmitq);
		पूर्ण अन्यथा अणु
			m->state = MBR_PENDING;
			list_add_tail(&m->list, &grp->pending);
		पूर्ण

		अगर (active_cnt < reclaim_limit)
			अवरोध;

		/* Reclaim from oldest active member, अगर possible */
		अगर (!list_empty(active)) अणु
			rm = list_first_entry(active, काष्ठा tipc_member, list);
			rm->state = MBR_RECLAIMING;
			list_del_init(&rm->list);
			tipc_group_proto_xmit(grp, rm, GRP_RECLAIM_MSG, xmitq);
			अवरोध;
		पूर्ण
		/* Nobody to reclaim from; - revert oldest pending to JOINED */
		pm = list_first_entry(&grp->pending, काष्ठा tipc_member, list);
		list_del_init(&pm->list);
		pm->state = MBR_JOINED;
		tipc_group_proto_xmit(grp, pm, GRP_ADV_MSG, xmitq);
		अवरोध;
	हाल MBR_ACTIVE:
		अगर (!list_is_last(&m->list, &grp->active))
			list_move_tail(&m->list, &grp->active);
		अगर (m->advertised > (ADV_ACTIVE * 3 / 4))
			अवरोध;
		tipc_group_proto_xmit(grp, m, GRP_ADV_MSG, xmitq);
		अवरोध;
	हाल MBR_REMITTED:
		अगर (m->advertised > ADV_IDLE)
			अवरोध;
		m->state = MBR_JOINED;
		grp->active_cnt--;
		अगर (m->advertised < ADV_IDLE) अणु
			pr_warn_ratelimited("Rcv unexpected msg after REMIT\n");
			tipc_group_proto_xmit(grp, m, GRP_ADV_MSG, xmitq);
		पूर्ण

		अगर (list_empty(&grp->pending))
			वापस;

		/* Set oldest pending member to active and advertise */
		pm = list_first_entry(&grp->pending, काष्ठा tipc_member, list);
		pm->state = MBR_ACTIVE;
		list_move_tail(&pm->list, &grp->active);
		grp->active_cnt++;
		tipc_group_proto_xmit(grp, pm, GRP_ADV_MSG, xmitq);
		अवरोध;
	हाल MBR_RECLAIMING:
	हाल MBR_JOINING:
	हाल MBR_LEAVING:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tipc_group_create_event(काष्ठा tipc_group *grp,
				    काष्ठा tipc_member *m,
				    u32 event, u16 seqno,
				    काष्ठा sk_buff_head *inputq)
अणु	u32 dnode = tipc_own_addr(grp->net);
	काष्ठा tipc_event evt;
	काष्ठा sk_buff *skb;
	काष्ठा tipc_msg *hdr;

	स_रखो(&evt, 0, माप(evt));
	evt.event = event;
	evt.found_lower = m->instance;
	evt.found_upper = m->instance;
	evt.port.ref = m->port;
	evt.port.node = m->node;
	evt.s.seq.type = grp->type;
	evt.s.seq.lower = m->instance;
	evt.s.seq.upper = m->instance;

	skb = tipc_msg_create(TIPC_CRITICAL_IMPORTANCE, TIPC_GRP_MEMBER_EVT,
			      GROUP_H_SIZE, माप(evt), dnode, m->node,
			      grp->portid, m->port, 0);
	अगर (!skb)
		वापस;

	hdr = buf_msg(skb);
	msg_set_nametype(hdr, grp->type);
	msg_set_grp_evt(hdr, event);
	msg_set_dest_droppable(hdr, true);
	msg_set_grp_bc_seqno(hdr, seqno);
	स_नकल(msg_data(hdr), &evt, माप(evt));
	TIPC_SKB_CB(skb)->orig_member = m->instance;
	__skb_queue_tail(inputq, skb);
पूर्ण

अटल व्योम tipc_group_proto_xmit(काष्ठा tipc_group *grp, काष्ठा tipc_member *m,
				  पूर्णांक mtyp, काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_msg *hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक adv = 0;

	skb = tipc_msg_create(GROUP_PROTOCOL, mtyp, INT_H_SIZE, 0,
			      m->node, tipc_own_addr(grp->net),
			      m->port, grp->portid, 0);
	अगर (!skb)
		वापस;

	अगर (m->state == MBR_ACTIVE)
		adv = ADV_ACTIVE - m->advertised;
	अन्यथा अगर (m->state == MBR_JOINED || m->state == MBR_PENDING)
		adv = ADV_IDLE - m->advertised;

	hdr = buf_msg(skb);

	अगर (mtyp == GRP_JOIN_MSG) अणु
		msg_set_grp_bc_syncpt(hdr, grp->bc_snd_nxt);
		msg_set_adv_win(hdr, adv);
		m->advertised += adv;
	पूर्ण अन्यथा अगर (mtyp == GRP_LEAVE_MSG) अणु
		msg_set_grp_bc_syncpt(hdr, grp->bc_snd_nxt);
	पूर्ण अन्यथा अगर (mtyp == GRP_ADV_MSG) अणु
		msg_set_adv_win(hdr, adv);
		m->advertised += adv;
	पूर्ण अन्यथा अगर (mtyp == GRP_ACK_MSG) अणु
		msg_set_grp_bc_acked(hdr, m->bc_rcv_nxt);
	पूर्ण अन्यथा अगर (mtyp == GRP_REMIT_MSG) अणु
		msg_set_grp_remitted(hdr, m->winकरोw);
	पूर्ण
	msg_set_dest_droppable(hdr, true);
	__skb_queue_tail(xmitq, skb);
पूर्ण

व्योम tipc_group_proto_rcv(काष्ठा tipc_group *grp, bool *usr_wakeup,
			  काष्ठा tipc_msg *hdr, काष्ठा sk_buff_head *inputq,
			  काष्ठा sk_buff_head *xmitq)
अणु
	u32 node = msg_orignode(hdr);
	u32 port = msg_origport(hdr);
	काष्ठा tipc_member *m, *pm;
	u16 remitted, in_flight;

	अगर (!grp)
		वापस;

	अगर (grp->scope == TIPC_NODE_SCOPE && node != tipc_own_addr(grp->net))
		वापस;

	m = tipc_group_find_member(grp, node, port);

	चयन (msg_type(hdr)) अणु
	हाल GRP_JOIN_MSG:
		अगर (!m)
			m = tipc_group_create_member(grp, node, port,
						     0, MBR_JOINING);
		अगर (!m)
			वापस;
		m->bc_syncpt = msg_grp_bc_syncpt(hdr);
		m->bc_rcv_nxt = m->bc_syncpt;
		m->winकरोw += msg_adv_win(hdr);

		/* Wait until PUBLISH event is received अगर necessary */
		अगर (m->state != MBR_PUBLISHED)
			वापस;

		/* Member can be taken पूर्णांकo service */
		m->state = MBR_JOINED;
		tipc_group_खोलो(m, usr_wakeup);
		tipc_group_update_member(m, 0);
		tipc_group_proto_xmit(grp, m, GRP_ADV_MSG, xmitq);
		tipc_group_create_event(grp, m, TIPC_PUBLISHED,
					m->bc_syncpt, inputq);
		वापस;
	हाल GRP_LEAVE_MSG:
		अगर (!m)
			वापस;
		m->bc_syncpt = msg_grp_bc_syncpt(hdr);
		list_del_init(&m->list);
		tipc_group_खोलो(m, usr_wakeup);
		tipc_group_decr_active(grp, m);
		m->state = MBR_LEAVING;
		tipc_group_create_event(grp, m, TIPC_WITHDRAWN,
					m->bc_syncpt, inputq);
		वापस;
	हाल GRP_ADV_MSG:
		अगर (!m)
			वापस;
		m->winकरोw += msg_adv_win(hdr);
		tipc_group_खोलो(m, usr_wakeup);
		वापस;
	हाल GRP_ACK_MSG:
		अगर (!m)
			वापस;
		m->bc_acked = msg_grp_bc_acked(hdr);
		अगर (--grp->bc_ackers)
			वापस;
		list_del_init(&m->small_win);
		*m->group->खोलो = true;
		*usr_wakeup = true;
		tipc_group_update_member(m, 0);
		वापस;
	हाल GRP_RECLAIM_MSG:
		अगर (!m)
			वापस;
		tipc_group_proto_xmit(grp, m, GRP_REMIT_MSG, xmitq);
		m->winकरोw = ADV_IDLE;
		tipc_group_खोलो(m, usr_wakeup);
		वापस;
	हाल GRP_REMIT_MSG:
		अगर (!m || m->state != MBR_RECLAIMING)
			वापस;

		remitted = msg_grp_remitted(hdr);

		/* Messages preceding the REMIT still in receive queue */
		अगर (m->advertised > remitted) अणु
			m->state = MBR_REMITTED;
			in_flight = m->advertised - remitted;
			m->advertised = ADV_IDLE + in_flight;
			वापस;
		पूर्ण
		/* This should never happen */
		अगर (m->advertised < remitted)
			pr_warn_ratelimited("Unexpected REMIT msg\n");

		/* All messages preceding the REMIT have been पढ़ो */
		m->state = MBR_JOINED;
		grp->active_cnt--;
		m->advertised = ADV_IDLE;

		/* Set oldest pending member to active and advertise */
		अगर (list_empty(&grp->pending))
			वापस;
		pm = list_first_entry(&grp->pending, काष्ठा tipc_member, list);
		pm->state = MBR_ACTIVE;
		list_move_tail(&pm->list, &grp->active);
		grp->active_cnt++;
		अगर (pm->advertised <= (ADV_ACTIVE * 3 / 4))
			tipc_group_proto_xmit(grp, pm, GRP_ADV_MSG, xmitq);
		वापस;
	शेष:
		pr_warn("Received unknown GROUP_PROTO message\n");
	पूर्ण
पूर्ण

/* tipc_group_member_evt() - receive and handle a member up/करोwn event
 */
व्योम tipc_group_member_evt(काष्ठा tipc_group *grp,
			   bool *usr_wakeup,
			   पूर्णांक *sk_rcvbuf,
			   काष्ठा tipc_msg *hdr,
			   काष्ठा sk_buff_head *inputq,
			   काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_event *evt = (व्योम *)msg_data(hdr);
	u32 instance = evt->found_lower;
	u32 node = evt->port.node;
	u32 port = evt->port.ref;
	पूर्णांक event = evt->event;
	काष्ठा tipc_member *m;
	काष्ठा net *net;
	u32 self;

	अगर (!grp)
		वापस;

	net = grp->net;
	self = tipc_own_addr(net);
	अगर (!grp->loopback && node == self && port == grp->portid)
		वापस;

	m = tipc_group_find_member(grp, node, port);

	चयन (event) अणु
	हाल TIPC_PUBLISHED:
		/* Send and रुको क्रम arrival of JOIN message अगर necessary */
		अगर (!m) अणु
			m = tipc_group_create_member(grp, node, port, instance,
						     MBR_PUBLISHED);
			अगर (!m)
				अवरोध;
			tipc_group_update_member(m, 0);
			tipc_group_proto_xmit(grp, m, GRP_JOIN_MSG, xmitq);
			अवरोध;
		पूर्ण

		अगर (m->state != MBR_JOINING)
			अवरोध;

		/* Member can be taken पूर्णांकo service */
		m->instance = instance;
		m->state = MBR_JOINED;
		tipc_group_खोलो(m, usr_wakeup);
		tipc_group_update_member(m, 0);
		tipc_group_proto_xmit(grp, m, GRP_JOIN_MSG, xmitq);
		tipc_group_create_event(grp, m, TIPC_PUBLISHED,
					m->bc_syncpt, inputq);
		अवरोध;
	हाल TIPC_WITHDRAWN:
		अगर (!m)
			अवरोध;

		tipc_group_decr_active(grp, m);
		m->state = MBR_LEAVING;
		list_del_init(&m->list);
		tipc_group_खोलो(m, usr_wakeup);

		/* Only send event अगर no LEAVE message can be expected */
		अगर (!tipc_node_is_up(net, node))
			tipc_group_create_event(grp, m, TIPC_WITHDRAWN,
						m->bc_rcv_nxt, inputq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	*sk_rcvbuf = tipc_group_rcvbuf_limit(grp);
पूर्ण

पूर्णांक tipc_group_fill_sock_diag(काष्ठा tipc_group *grp, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *group = nla_nest_start_noflag(skb, TIPC_NLA_SOCK_GROUP);

	अगर (!group)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, TIPC_NLA_SOCK_GROUP_ID,
			grp->type) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_GROUP_INSTANCE,
			grp->instance) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_GROUP_BC_SEND_NEXT,
			grp->bc_snd_nxt))
		जाओ group_msg_cancel;

	अगर (grp->scope == TIPC_NODE_SCOPE)
		अगर (nla_put_flag(skb, TIPC_NLA_SOCK_GROUP_NODE_SCOPE))
			जाओ group_msg_cancel;

	अगर (grp->scope == TIPC_CLUSTER_SCOPE)
		अगर (nla_put_flag(skb, TIPC_NLA_SOCK_GROUP_CLUSTER_SCOPE))
			जाओ group_msg_cancel;

	अगर (*grp->खोलो)
		अगर (nla_put_flag(skb, TIPC_NLA_SOCK_GROUP_OPEN))
			जाओ group_msg_cancel;

	nla_nest_end(skb, group);
	वापस 0;

group_msg_cancel:
	nla_nest_cancel(skb, group);
	वापस -1;
पूर्ण
