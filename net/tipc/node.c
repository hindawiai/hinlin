<शैली गुरु>
/*
 * net/tipc/node.c: TIPC node management routines
 *
 * Copyright (c) 2000-2006, 2012-2016, Ericsson AB
 * Copyright (c) 2005-2006, 2010-2014, Wind River Systems
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
#समावेश "link.h"
#समावेश "node.h"
#समावेश "name_distr.h"
#समावेश "socket.h"
#समावेश "bcast.h"
#समावेश "monitor.h"
#समावेश "discover.h"
#समावेश "netlink.h"
#समावेश "trace.h"
#समावेश "crypto.h"

#घोषणा INVALID_NODE_SIG	0x10000
#घोषणा NODE_CLEANUP_AFTER	300000

/* Flags used to take dअगरferent actions according to flag type
 * TIPC_NOTIFY_NODE_DOWN: notअगरy node is करोwn
 * TIPC_NOTIFY_NODE_UP: notअगरy node is up
 * TIPC_DISTRIBUTE_NAME: publish or withdraw link state name type
 */
क्रमागत अणु
	TIPC_NOTIFY_NODE_DOWN		= (1 << 3),
	TIPC_NOTIFY_NODE_UP		= (1 << 4),
	TIPC_NOTIFY_LINK_UP		= (1 << 6),
	TIPC_NOTIFY_LINK_DOWN		= (1 << 7)
पूर्ण;

काष्ठा tipc_link_entry अणु
	काष्ठा tipc_link *link;
	spinlock_t lock; /* per link */
	u32 mtu;
	काष्ठा sk_buff_head inputq;
	काष्ठा tipc_media_addr maddr;
पूर्ण;

काष्ठा tipc_bclink_entry अणु
	काष्ठा tipc_link *link;
	काष्ठा sk_buff_head inputq1;
	काष्ठा sk_buff_head arrvq;
	काष्ठा sk_buff_head inputq2;
	काष्ठा sk_buff_head namedq;
	u16 named_rcv_nxt;
	bool named_खोलो;
पूर्ण;

/**
 * काष्ठा tipc_node - TIPC node काष्ठाure
 * @addr: network address of node
 * @kref: reference counter to node object
 * @lock: rwlock governing access to काष्ठाure
 * @net: the applicable net namespace
 * @hash: links to adjacent nodes in unsorted hash chain
 * @inputq: poपूर्णांकer to input queue containing messages क्रम msg event
 * @namedq: poपूर्णांकer to name table input queue with name table messages
 * @active_links: bearer ids of active links, used as index पूर्णांकo links[] array
 * @links: array containing references to all links to node
 * @bc_entry: broadcast link entry
 * @action_flags: bit mask of dअगरferent types of node actions
 * @state: connectivity state vs peer node
 * @preliminary: a preliminary node or not
 * @failover_sent: failover sent or not
 * @sync_poपूर्णांक: sequence number where synch/failover is finished
 * @list: links to adjacent nodes in sorted list of cluster's nodes
 * @working_links: number of working links to node (both active and standby)
 * @link_cnt: number of links to node
 * @capabilities: biपंचांगap, indicating peer node's functional capabilities
 * @signature: node instance identअगरier
 * @link_id: local and remote bearer ids of changing link, अगर any
 * @peer_id: 128-bit ID of peer
 * @peer_id_string: ID string of peer
 * @publ_list: list of खुलाations
 * @conn_sks: list of connections (FIXME)
 * @समयr: node's keepalive समयr
 * @keepalive_पूर्णांकv: keepalive पूर्णांकerval in milliseconds
 * @rcu: rcu काष्ठा क्रम tipc_node
 * @delete_at: indicates the समय क्रम deleting a करोwn node
 * @peer_net: peer's net namespace
 * @peer_hash_mix: hash क्रम this peer (FIXME)
 * @crypto_rx: RX crypto handler
 */
काष्ठा tipc_node अणु
	u32 addr;
	काष्ठा kref kref;
	rwlock_t lock;
	काष्ठा net *net;
	काष्ठा hlist_node hash;
	पूर्णांक active_links[2];
	काष्ठा tipc_link_entry links[MAX_BEARERS];
	काष्ठा tipc_bclink_entry bc_entry;
	पूर्णांक action_flags;
	काष्ठा list_head list;
	पूर्णांक state;
	bool preliminary;
	bool failover_sent;
	u16 sync_poपूर्णांक;
	पूर्णांक link_cnt;
	u16 working_links;
	u16 capabilities;
	u32 signature;
	u32 link_id;
	u8 peer_id[16];
	अक्षर peer_id_string[NODE_ID_STR_LEN];
	काष्ठा list_head publ_list;
	काष्ठा list_head conn_sks;
	अचिन्हित दीर्घ keepalive_पूर्णांकv;
	काष्ठा समयr_list समयr;
	काष्ठा rcu_head rcu;
	अचिन्हित दीर्घ delete_at;
	काष्ठा net *peer_net;
	u32 peer_hash_mix;
#अगर_घोषित CONFIG_TIPC_CRYPTO
	काष्ठा tipc_crypto *crypto_rx;
#पूर्ण_अगर
पूर्ण;

/* Node FSM states and events:
 */
क्रमागत अणु
	SELF_DOWN_PEER_DOWN    = 0xdd,
	SELF_UP_PEER_UP        = 0xaa,
	SELF_DOWN_PEER_LEAVING = 0xd1,
	SELF_UP_PEER_COMING    = 0xac,
	SELF_COMING_PEER_UP    = 0xca,
	SELF_LEAVING_PEER_DOWN = 0x1d,
	NODE_FAILINGOVER       = 0xf0,
	NODE_SYNCHING          = 0xcc
पूर्ण;

क्रमागत अणु
	SELF_ESTABL_CONTACT_EVT = 0xece,
	SELF_LOST_CONTACT_EVT   = 0x1ce,
	PEER_ESTABL_CONTACT_EVT = 0x9ece,
	PEER_LOST_CONTACT_EVT   = 0x91ce,
	NODE_FAILOVER_BEGIN_EVT = 0xfbe,
	NODE_FAILOVER_END_EVT   = 0xfee,
	NODE_SYNCH_BEGIN_EVT    = 0xcbe,
	NODE_SYNCH_END_EVT      = 0xcee
पूर्ण;

अटल व्योम __tipc_node_link_करोwn(काष्ठा tipc_node *n, पूर्णांक *bearer_id,
				  काष्ठा sk_buff_head *xmitq,
				  काष्ठा tipc_media_addr **maddr);
अटल व्योम tipc_node_link_करोwn(काष्ठा tipc_node *n, पूर्णांक bearer_id,
				bool delete);
अटल व्योम node_lost_contact(काष्ठा tipc_node *n, काष्ठा sk_buff_head *inputq);
अटल व्योम tipc_node_delete(काष्ठा tipc_node *node);
अटल व्योम tipc_node_समयout(काष्ठा समयr_list *t);
अटल व्योम tipc_node_fsm_evt(काष्ठा tipc_node *n, पूर्णांक evt);
अटल काष्ठा tipc_node *tipc_node_find(काष्ठा net *net, u32 addr);
अटल काष्ठा tipc_node *tipc_node_find_by_id(काष्ठा net *net, u8 *id);
अटल bool node_is_up(काष्ठा tipc_node *n);
अटल व्योम tipc_node_delete_from_list(काष्ठा tipc_node *node);

काष्ठा tipc_sock_conn अणु
	u32 port;
	u32 peer_port;
	u32 peer_node;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा tipc_link *node_active_link(काष्ठा tipc_node *n, पूर्णांक sel)
अणु
	पूर्णांक bearer_id = n->active_links[sel & 1];

	अगर (unlikely(bearer_id == INVALID_BEARER_ID))
		वापस शून्य;

	वापस n->links[bearer_id].link;
पूर्ण

पूर्णांक tipc_node_get_mtu(काष्ठा net *net, u32 addr, u32 sel, bool connected)
अणु
	काष्ठा tipc_node *n;
	पूर्णांक bearer_id;
	अचिन्हित पूर्णांक mtu = MAX_MSG_SIZE;

	n = tipc_node_find(net, addr);
	अगर (unlikely(!n))
		वापस mtu;

	/* Allow MAX_MSG_SIZE when building connection oriented message
	 * अगर they are in the same core network
	 */
	अगर (n->peer_net && connected) अणु
		tipc_node_put(n);
		वापस mtu;
	पूर्ण

	bearer_id = n->active_links[sel & 1];
	अगर (likely(bearer_id != INVALID_BEARER_ID))
		mtu = n->links[bearer_id].mtu;
	tipc_node_put(n);
	वापस mtu;
पूर्ण

bool tipc_node_get_id(काष्ठा net *net, u32 addr, u8 *id)
अणु
	u8 *own_id = tipc_own_id(net);
	काष्ठा tipc_node *n;

	अगर (!own_id)
		वापस true;

	अगर (addr == tipc_own_addr(net)) अणु
		स_नकल(id, own_id, TIPC_NODEID_LEN);
		वापस true;
	पूर्ण
	n = tipc_node_find(net, addr);
	अगर (!n)
		वापस false;

	स_नकल(id, &n->peer_id, TIPC_NODEID_LEN);
	tipc_node_put(n);
	वापस true;
पूर्ण

u16 tipc_node_get_capabilities(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_node *n;
	u16 caps;

	n = tipc_node_find(net, addr);
	अगर (unlikely(!n))
		वापस TIPC_NODE_CAPABILITIES;
	caps = n->capabilities;
	tipc_node_put(n);
	वापस caps;
पूर्ण

u32 tipc_node_get_addr(काष्ठा tipc_node *node)
अणु
	वापस (node) ? node->addr : 0;
पूर्ण

अक्षर *tipc_node_get_id_str(काष्ठा tipc_node *node)
अणु
	वापस node->peer_id_string;
पूर्ण

#अगर_घोषित CONFIG_TIPC_CRYPTO
/**
 * tipc_node_crypto_rx - Retrieve crypto RX handle from node
 * @__n: target tipc_node
 * Note: node ref counter must be held first!
 */
काष्ठा tipc_crypto *tipc_node_crypto_rx(काष्ठा tipc_node *__n)
अणु
	वापस (__n) ? __n->crypto_rx : शून्य;
पूर्ण

काष्ठा tipc_crypto *tipc_node_crypto_rx_by_list(काष्ठा list_head *pos)
अणु
	वापस container_of(pos, काष्ठा tipc_node, list)->crypto_rx;
पूर्ण

काष्ठा tipc_crypto *tipc_node_crypto_rx_by_addr(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_node *n;

	n = tipc_node_find(net, addr);
	वापस (n) ? n->crypto_rx : शून्य;
पूर्ण
#पूर्ण_अगर

अटल व्योम tipc_node_मुक्त(काष्ठा rcu_head *rp)
अणु
	काष्ठा tipc_node *n = container_of(rp, काष्ठा tipc_node, rcu);

#अगर_घोषित CONFIG_TIPC_CRYPTO
	tipc_crypto_stop(&n->crypto_rx);
#पूर्ण_अगर
	kमुक्त(n);
पूर्ण

अटल व्योम tipc_node_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा tipc_node *n = container_of(kref, काष्ठा tipc_node, kref);

	kमुक्त(n->bc_entry.link);
	call_rcu(&n->rcu, tipc_node_मुक्त);
पूर्ण

व्योम tipc_node_put(काष्ठा tipc_node *node)
अणु
	kref_put(&node->kref, tipc_node_kref_release);
पूर्ण

व्योम tipc_node_get(काष्ठा tipc_node *node)
अणु
	kref_get(&node->kref);
पूर्ण

/*
 * tipc_node_find - locate specअगरied node object, अगर it exists
 */
अटल काष्ठा tipc_node *tipc_node_find(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_node *node;
	अचिन्हित पूर्णांक thash = tipc_hashfn(addr);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(node, &tn->node_htable[thash], hash) अणु
		अगर (node->addr != addr || node->preliminary)
			जारी;
		अगर (!kref_get_unless_zero(&node->kref))
			node = शून्य;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस node;
पूर्ण

/* tipc_node_find_by_id - locate specअगरied node object by its 128-bit id
 * Note: this function is called only when a discovery request failed
 * to find the node by its 32-bit id, and is not समय critical
 */
अटल काष्ठा tipc_node *tipc_node_find_by_id(काष्ठा net *net, u8 *id)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_node *n;
	bool found = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(n, &tn->node_list, list) अणु
		पढ़ो_lock_bh(&n->lock);
		अगर (!स_भेद(id, n->peer_id, 16) &&
		    kref_get_unless_zero(&n->kref))
			found = true;
		पढ़ो_unlock_bh(&n->lock);
		अगर (found)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस found ? n : शून्य;
पूर्ण

अटल व्योम tipc_node_पढ़ो_lock(काष्ठा tipc_node *n)
	__acquires(n->lock)
अणु
	पढ़ो_lock_bh(&n->lock);
पूर्ण

अटल व्योम tipc_node_पढ़ो_unlock(काष्ठा tipc_node *n)
	__releases(n->lock)
अणु
	पढ़ो_unlock_bh(&n->lock);
पूर्ण

अटल व्योम tipc_node_ग_लिखो_lock(काष्ठा tipc_node *n)
	__acquires(n->lock)
अणु
	ग_लिखो_lock_bh(&n->lock);
पूर्ण

अटल व्योम tipc_node_ग_लिखो_unlock_fast(काष्ठा tipc_node *n)
	__releases(n->lock)
अणु
	ग_लिखो_unlock_bh(&n->lock);
पूर्ण

अटल व्योम tipc_node_ग_लिखो_unlock(काष्ठा tipc_node *n)
	__releases(n->lock)
अणु
	काष्ठा tipc_socket_addr sk;
	काष्ठा net *net = n->net;
	u32 flags = n->action_flags;
	काष्ठा list_head *publ_list;
	काष्ठा tipc_uaddr ua;
	u32 bearer_id;

	अगर (likely(!flags)) अणु
		ग_लिखो_unlock_bh(&n->lock);
		वापस;
	पूर्ण

	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, TIPC_NODE_SCOPE,
		   TIPC_LINK_STATE, n->addr, n->addr);
	sk.ref = n->link_id;
	sk.node = n->addr;
	bearer_id = n->link_id & 0xffff;
	publ_list = &n->publ_list;

	n->action_flags &= ~(TIPC_NOTIFY_NODE_DOWN | TIPC_NOTIFY_NODE_UP |
			     TIPC_NOTIFY_LINK_DOWN | TIPC_NOTIFY_LINK_UP);

	ग_लिखो_unlock_bh(&n->lock);

	अगर (flags & TIPC_NOTIFY_NODE_DOWN)
		tipc_publ_notअगरy(net, publ_list, sk.node, n->capabilities);

	अगर (flags & TIPC_NOTIFY_NODE_UP)
		tipc_named_node_up(net, sk.node, n->capabilities);

	अगर (flags & TIPC_NOTIFY_LINK_UP) अणु
		tipc_mon_peer_up(net, sk.node, bearer_id);
		tipc_nametbl_publish(net, &ua, &sk, sk.ref);
	पूर्ण
	अगर (flags & TIPC_NOTIFY_LINK_DOWN) अणु
		tipc_mon_peer_करोwn(net, sk.node, bearer_id);
		tipc_nametbl_withdraw(net, &ua, &sk, sk.ref);
	पूर्ण
पूर्ण

अटल व्योम tipc_node_assign_peer_net(काष्ठा tipc_node *n, u32 hash_mixes)
अणु
	पूर्णांक net_id = tipc_netid(n->net);
	काष्ठा tipc_net *tn_peer;
	काष्ठा net *पंचांगp;
	u32 hash_chk;

	अगर (n->peer_net)
		वापस;

	क्रम_each_net_rcu(पंचांगp) अणु
		tn_peer = tipc_net(पंचांगp);
		अगर (!tn_peer)
			जारी;
		/* Integrity checking whether node exists in namespace or not */
		अगर (tn_peer->net_id != net_id)
			जारी;
		अगर (स_भेद(n->peer_id, tn_peer->node_id, NODE_ID_LEN))
			जारी;
		hash_chk = tipc_net_hash_mixes(पंचांगp, tn_peer->अक्रमom);
		अगर (hash_mixes ^ hash_chk)
			जारी;
		n->peer_net = पंचांगp;
		n->peer_hash_mix = hash_mixes;
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा tipc_node *tipc_node_create(काष्ठा net *net, u32 addr, u8 *peer_id,
				   u16 capabilities, u32 hash_mixes,
				   bool preliminary)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_node *n, *temp_node;
	काष्ठा tipc_link *l;
	अचिन्हित दीर्घ पूर्णांकv;
	पूर्णांक bearer_id;
	पूर्णांक i;

	spin_lock_bh(&tn->node_list_lock);
	n = tipc_node_find(net, addr) ?:
		tipc_node_find_by_id(net, peer_id);
	अगर (n) अणु
		अगर (!n->preliminary)
			जाओ update;
		अगर (preliminary)
			जाओ निकास;
		/* A preliminary node becomes "real" now, refresh its data */
		tipc_node_ग_लिखो_lock(n);
		n->preliminary = false;
		n->addr = addr;
		hlist_del_rcu(&n->hash);
		hlist_add_head_rcu(&n->hash,
				   &tn->node_htable[tipc_hashfn(addr)]);
		list_del_rcu(&n->list);
		list_क्रम_each_entry_rcu(temp_node, &tn->node_list, list) अणु
			अगर (n->addr < temp_node->addr)
				अवरोध;
		पूर्ण
		list_add_tail_rcu(&n->list, &temp_node->list);
		tipc_node_ग_लिखो_unlock_fast(n);

update:
		अगर (n->peer_hash_mix ^ hash_mixes)
			tipc_node_assign_peer_net(n, hash_mixes);
		अगर (n->capabilities == capabilities)
			जाओ निकास;
		/* Same node may come back with new capabilities */
		tipc_node_ग_लिखो_lock(n);
		n->capabilities = capabilities;
		क्रम (bearer_id = 0; bearer_id < MAX_BEARERS; bearer_id++) अणु
			l = n->links[bearer_id].link;
			अगर (l)
				tipc_link_update_caps(l, capabilities);
		पूर्ण
		tipc_node_ग_लिखो_unlock_fast(n);

		/* Calculate cluster capabilities */
		tn->capabilities = TIPC_NODE_CAPABILITIES;
		list_क्रम_each_entry_rcu(temp_node, &tn->node_list, list) अणु
			tn->capabilities &= temp_node->capabilities;
		पूर्ण

		tipc_bcast_toggle_rcast(net,
					(tn->capabilities & TIPC_BCAST_RCAST));

		जाओ निकास;
	पूर्ण
	n = kzalloc(माप(*n), GFP_ATOMIC);
	अगर (!n) अणु
		pr_warn("Node creation failed, no memory\n");
		जाओ निकास;
	पूर्ण
	tipc_nodeid2string(n->peer_id_string, peer_id);
#अगर_घोषित CONFIG_TIPC_CRYPTO
	अगर (unlikely(tipc_crypto_start(&n->crypto_rx, net, n))) अणु
		pr_warn("Failed to start crypto RX(%s)!\n", n->peer_id_string);
		kमुक्त(n);
		n = शून्य;
		जाओ निकास;
	पूर्ण
#पूर्ण_अगर
	n->addr = addr;
	n->preliminary = preliminary;
	स_नकल(&n->peer_id, peer_id, 16);
	n->net = net;
	n->peer_net = शून्य;
	n->peer_hash_mix = 0;
	/* Assign kernel local namespace अगर exists */
	tipc_node_assign_peer_net(n, hash_mixes);
	n->capabilities = capabilities;
	kref_init(&n->kref);
	rwlock_init(&n->lock);
	INIT_HLIST_NODE(&n->hash);
	INIT_LIST_HEAD(&n->list);
	INIT_LIST_HEAD(&n->publ_list);
	INIT_LIST_HEAD(&n->conn_sks);
	skb_queue_head_init(&n->bc_entry.namedq);
	skb_queue_head_init(&n->bc_entry.inputq1);
	__skb_queue_head_init(&n->bc_entry.arrvq);
	skb_queue_head_init(&n->bc_entry.inputq2);
	क्रम (i = 0; i < MAX_BEARERS; i++)
		spin_lock_init(&n->links[i].lock);
	n->state = SELF_DOWN_PEER_LEAVING;
	n->delete_at = jअगरfies + msecs_to_jअगरfies(NODE_CLEANUP_AFTER);
	n->signature = INVALID_NODE_SIG;
	n->active_links[0] = INVALID_BEARER_ID;
	n->active_links[1] = INVALID_BEARER_ID;
	n->bc_entry.link = शून्य;
	tipc_node_get(n);
	समयr_setup(&n->समयr, tipc_node_समयout, 0);
	/* Start a slow समयr anyway, crypto needs it */
	n->keepalive_पूर्णांकv = 10000;
	पूर्णांकv = jअगरfies + msecs_to_jअगरfies(n->keepalive_पूर्णांकv);
	अगर (!mod_समयr(&n->समयr, पूर्णांकv))
		tipc_node_get(n);
	hlist_add_head_rcu(&n->hash, &tn->node_htable[tipc_hashfn(addr)]);
	list_क्रम_each_entry_rcu(temp_node, &tn->node_list, list) अणु
		अगर (n->addr < temp_node->addr)
			अवरोध;
	पूर्ण
	list_add_tail_rcu(&n->list, &temp_node->list);
	/* Calculate cluster capabilities */
	tn->capabilities = TIPC_NODE_CAPABILITIES;
	list_क्रम_each_entry_rcu(temp_node, &tn->node_list, list) अणु
		tn->capabilities &= temp_node->capabilities;
	पूर्ण
	tipc_bcast_toggle_rcast(net, (tn->capabilities & TIPC_BCAST_RCAST));
	trace_tipc_node_create(n, true, " ");
निकास:
	spin_unlock_bh(&tn->node_list_lock);
	वापस n;
पूर्ण

अटल व्योम tipc_node_calculate_समयr(काष्ठा tipc_node *n, काष्ठा tipc_link *l)
अणु
	अचिन्हित दीर्घ tol = tipc_link_tolerance(l);
	अचिन्हित दीर्घ पूर्णांकv = ((tol / 4) > 500) ? 500 : tol / 4;

	/* Link with lowest tolerance determines समयr पूर्णांकerval */
	अगर (पूर्णांकv < n->keepalive_पूर्णांकv)
		n->keepalive_पूर्णांकv = पूर्णांकv;

	/* Ensure link's पात limit corresponds to current tolerance */
	tipc_link_set_पात_limit(l, tol / n->keepalive_पूर्णांकv);
पूर्ण

अटल व्योम tipc_node_delete_from_list(काष्ठा tipc_node *node)
अणु
#अगर_घोषित CONFIG_TIPC_CRYPTO
	tipc_crypto_key_flush(node->crypto_rx);
#पूर्ण_अगर
	list_del_rcu(&node->list);
	hlist_del_rcu(&node->hash);
	tipc_node_put(node);
पूर्ण

अटल व्योम tipc_node_delete(काष्ठा tipc_node *node)
अणु
	trace_tipc_node_delete(node, true, " ");
	tipc_node_delete_from_list(node);

	del_समयr_sync(&node->समयr);
	tipc_node_put(node);
पूर्ण

व्योम tipc_node_stop(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_node *node, *t_node;

	spin_lock_bh(&tn->node_list_lock);
	list_क्रम_each_entry_safe(node, t_node, &tn->node_list, list)
		tipc_node_delete(node);
	spin_unlock_bh(&tn->node_list_lock);
पूर्ण

व्योम tipc_node_subscribe(काष्ठा net *net, काष्ठा list_head *subscr, u32 addr)
अणु
	काष्ठा tipc_node *n;

	अगर (in_own_node(net, addr))
		वापस;

	n = tipc_node_find(net, addr);
	अगर (!n) अणु
		pr_warn("Node subscribe rejected, unknown node 0x%x\n", addr);
		वापस;
	पूर्ण
	tipc_node_ग_लिखो_lock(n);
	list_add_tail(subscr, &n->publ_list);
	tipc_node_ग_लिखो_unlock_fast(n);
	tipc_node_put(n);
पूर्ण

व्योम tipc_node_unsubscribe(काष्ठा net *net, काष्ठा list_head *subscr, u32 addr)
अणु
	काष्ठा tipc_node *n;

	अगर (in_own_node(net, addr))
		वापस;

	n = tipc_node_find(net, addr);
	अगर (!n) अणु
		pr_warn("Node unsubscribe rejected, unknown node 0x%x\n", addr);
		वापस;
	पूर्ण
	tipc_node_ग_लिखो_lock(n);
	list_del_init(subscr);
	tipc_node_ग_लिखो_unlock_fast(n);
	tipc_node_put(n);
पूर्ण

पूर्णांक tipc_node_add_conn(काष्ठा net *net, u32 dnode, u32 port, u32 peer_port)
अणु
	काष्ठा tipc_node *node;
	काष्ठा tipc_sock_conn *conn;
	पूर्णांक err = 0;

	अगर (in_own_node(net, dnode))
		वापस 0;

	node = tipc_node_find(net, dnode);
	अगर (!node) अणु
		pr_warn("Connecting sock to node 0x%x failed\n", dnode);
		वापस -EHOSTUNREACH;
	पूर्ण
	conn = kदो_स्मृति(माप(*conn), GFP_ATOMIC);
	अगर (!conn) अणु
		err = -EHOSTUNREACH;
		जाओ निकास;
	पूर्ण
	conn->peer_node = dnode;
	conn->port = port;
	conn->peer_port = peer_port;

	tipc_node_ग_लिखो_lock(node);
	list_add_tail(&conn->list, &node->conn_sks);
	tipc_node_ग_लिखो_unlock(node);
निकास:
	tipc_node_put(node);
	वापस err;
पूर्ण

व्योम tipc_node_हटाओ_conn(काष्ठा net *net, u32 dnode, u32 port)
अणु
	काष्ठा tipc_node *node;
	काष्ठा tipc_sock_conn *conn, *safe;

	अगर (in_own_node(net, dnode))
		वापस;

	node = tipc_node_find(net, dnode);
	अगर (!node)
		वापस;

	tipc_node_ग_लिखो_lock(node);
	list_क्रम_each_entry_safe(conn, safe, &node->conn_sks, list) अणु
		अगर (port != conn->port)
			जारी;
		list_del(&conn->list);
		kमुक्त(conn);
	पूर्ण
	tipc_node_ग_लिखो_unlock(node);
	tipc_node_put(node);
पूर्ण

अटल व्योम  tipc_node_clear_links(काष्ठा tipc_node *node)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		काष्ठा tipc_link_entry *le = &node->links[i];

		अगर (le->link) अणु
			kमुक्त(le->link);
			le->link = शून्य;
			node->link_cnt--;
		पूर्ण
	पूर्ण
पूर्ण

/* tipc_node_cleanup - delete nodes that करोes not
 * have active links क्रम NODE_CLEANUP_AFTER समय
 */
अटल bool tipc_node_cleanup(काष्ठा tipc_node *peer)
अणु
	काष्ठा tipc_node *temp_node;
	काष्ठा tipc_net *tn = tipc_net(peer->net);
	bool deleted = false;

	/* If lock held by tipc_node_stop() the node will be deleted anyway */
	अगर (!spin_trylock_bh(&tn->node_list_lock))
		वापस false;

	tipc_node_ग_लिखो_lock(peer);

	अगर (!node_is_up(peer) && समय_after(jअगरfies, peer->delete_at)) अणु
		tipc_node_clear_links(peer);
		tipc_node_delete_from_list(peer);
		deleted = true;
	पूर्ण
	tipc_node_ग_लिखो_unlock(peer);

	अगर (!deleted) अणु
		spin_unlock_bh(&tn->node_list_lock);
		वापस deleted;
	पूर्ण

	/* Calculate cluster capabilities */
	tn->capabilities = TIPC_NODE_CAPABILITIES;
	list_क्रम_each_entry_rcu(temp_node, &tn->node_list, list) अणु
		tn->capabilities &= temp_node->capabilities;
	पूर्ण
	tipc_bcast_toggle_rcast(peer->net,
				(tn->capabilities & TIPC_BCAST_RCAST));
	spin_unlock_bh(&tn->node_list_lock);
	वापस deleted;
पूर्ण

/* tipc_node_समयout - handle expiration of node समयr
 */
अटल व्योम tipc_node_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा tipc_node *n = from_समयr(n, t, समयr);
	काष्ठा tipc_link_entry *le;
	काष्ठा sk_buff_head xmitq;
	पूर्णांक reमुख्यs = n->link_cnt;
	पूर्णांक bearer_id;
	पूर्णांक rc = 0;

	trace_tipc_node_समयout(n, false, " ");
	अगर (!node_is_up(n) && tipc_node_cleanup(n)) अणु
		/*Removing the reference of Timer*/
		tipc_node_put(n);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_TIPC_CRYPTO
	/* Take any crypto key related actions first */
	tipc_crypto_समयout(n->crypto_rx);
#पूर्ण_अगर
	__skb_queue_head_init(&xmitq);

	/* Initial node पूर्णांकerval to value larger (10 seconds), then it will be
	 * recalculated with link lowest tolerance
	 */
	tipc_node_पढ़ो_lock(n);
	n->keepalive_पूर्णांकv = 10000;
	tipc_node_पढ़ो_unlock(n);
	क्रम (bearer_id = 0; reमुख्यs && (bearer_id < MAX_BEARERS); bearer_id++) अणु
		tipc_node_पढ़ो_lock(n);
		le = &n->links[bearer_id];
		अगर (le->link) अणु
			spin_lock_bh(&le->lock);
			/* Link tolerance may change asynchronously: */
			tipc_node_calculate_समयr(n, le->link);
			rc = tipc_link_समयout(le->link, &xmitq);
			spin_unlock_bh(&le->lock);
			reमुख्यs--;
		पूर्ण
		tipc_node_पढ़ो_unlock(n);
		tipc_bearer_xmit(n->net, bearer_id, &xmitq, &le->maddr, n);
		अगर (rc & TIPC_LINK_DOWN_EVT)
			tipc_node_link_करोwn(n, bearer_id, false);
	पूर्ण
	mod_समयr(&n->समयr, jअगरfies + msecs_to_jअगरfies(n->keepalive_पूर्णांकv));
पूर्ण

/**
 * __tipc_node_link_up - handle addition of link
 * @n: target tipc_node
 * @bearer_id: id of the bearer
 * @xmitq: queue क्रम messages to be xmited on
 * Node lock must be held by caller
 * Link becomes active (alone or shared) or standby, depending on its priority.
 */
अटल व्योम __tipc_node_link_up(काष्ठा tipc_node *n, पूर्णांक bearer_id,
				काष्ठा sk_buff_head *xmitq)
अणु
	पूर्णांक *slot0 = &n->active_links[0];
	पूर्णांक *slot1 = &n->active_links[1];
	काष्ठा tipc_link *ol = node_active_link(n, 0);
	काष्ठा tipc_link *nl = n->links[bearer_id].link;

	अगर (!nl || tipc_link_is_up(nl))
		वापस;

	tipc_link_fsm_evt(nl, LINK_ESTABLISH_EVT);
	अगर (!tipc_link_is_up(nl))
		वापस;

	n->working_links++;
	n->action_flags |= TIPC_NOTIFY_LINK_UP;
	n->link_id = tipc_link_id(nl);

	/* Leave room क्रम tunnel header when वापसing 'mtu' to users: */
	n->links[bearer_id].mtu = tipc_link_mss(nl);

	tipc_bearer_add_dest(n->net, bearer_id, n->addr);
	tipc_bcast_inc_bearer_dst_cnt(n->net, bearer_id);

	pr_debug("Established link <%s> on network plane %c\n",
		 tipc_link_name(nl), tipc_link_plane(nl));
	trace_tipc_node_link_up(n, true, " ");

	/* Ensure that a STATE message goes first */
	tipc_link_build_state_msg(nl, xmitq);

	/* First link? => give it both slots */
	अगर (!ol) अणु
		*slot0 = bearer_id;
		*slot1 = bearer_id;
		tipc_node_fsm_evt(n, SELF_ESTABL_CONTACT_EVT);
		n->action_flags |= TIPC_NOTIFY_NODE_UP;
		tipc_link_set_active(nl, true);
		tipc_bcast_add_peer(n->net, nl, xmitq);
		वापस;
	पूर्ण

	/* Second link => redistribute slots */
	अगर (tipc_link_prio(nl) > tipc_link_prio(ol)) अणु
		pr_debug("Old link <%s> becomes standby\n", tipc_link_name(ol));
		*slot0 = bearer_id;
		*slot1 = bearer_id;
		tipc_link_set_active(nl, true);
		tipc_link_set_active(ol, false);
	पूर्ण अन्यथा अगर (tipc_link_prio(nl) == tipc_link_prio(ol)) अणु
		tipc_link_set_active(nl, true);
		*slot1 = bearer_id;
	पूर्ण अन्यथा अणु
		pr_debug("New link <%s> is standby\n", tipc_link_name(nl));
	पूर्ण

	/* Prepare synchronization with first link */
	tipc_link_tnl_prepare(ol, nl, SYNCH_MSG, xmitq);
पूर्ण

/**
 * tipc_node_link_up - handle addition of link
 * @n: target tipc_node
 * @bearer_id: id of the bearer
 * @xmitq: queue क्रम messages to be xmited on
 *
 * Link becomes active (alone or shared) or standby, depending on its priority.
 */
अटल व्योम tipc_node_link_up(काष्ठा tipc_node *n, पूर्णांक bearer_id,
			      काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_media_addr *maddr;

	tipc_node_ग_लिखो_lock(n);
	__tipc_node_link_up(n, bearer_id, xmitq);
	maddr = &n->links[bearer_id].maddr;
	tipc_bearer_xmit(n->net, bearer_id, xmitq, maddr, n);
	tipc_node_ग_लिखो_unlock(n);
पूर्ण

/**
 * tipc_node_link_failover() - start failover in हाल "half-failover"
 *
 * This function is only called in a very special situation where link
 * failover can be alपढ़ोy started on peer node but not on this node.
 * This can happen when e.g.::
 *
 *	1. Both links <1A-2A>, <1B-2B> करोwn
 *	2. Link endpoपूर्णांक 2A up, but 1A still करोwn (e.g. due to network
 *	disturbance, wrong session, etc.)
 *	3. Link <1B-2B> up
 *	4. Link endpoपूर्णांक 2A करोwn (e.g. due to link tolerance समयout)
 *	5. Node 2 starts failover onto link <1B-2B>
 *
 *	==> Node 1 करोes never start link/node failover!
 *
 * @n: tipc node काष्ठाure
 * @l: link peer endpoपूर्णांक failingover (- can be शून्य)
 * @tnl: tunnel link
 * @xmitq: queue क्रम messages to be xmited on tnl link later
 */
अटल व्योम tipc_node_link_failover(काष्ठा tipc_node *n, काष्ठा tipc_link *l,
				    काष्ठा tipc_link *tnl,
				    काष्ठा sk_buff_head *xmitq)
अणु
	/* Aव्योम to be "self-failover" that can never end */
	अगर (!tipc_link_is_up(tnl))
		वापस;

	/* Don't rush, failure link may be in the process of resetting */
	अगर (l && !tipc_link_is_reset(l))
		वापस;

	tipc_link_fsm_evt(tnl, LINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);

	n->sync_poपूर्णांक = tipc_link_rcv_nxt(tnl) + (U16_MAX / 2 - 1);
	tipc_link_failover_prepare(l, tnl, xmitq);

	अगर (l)
		tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAILOVER_BEGIN_EVT);
पूर्ण

/**
 * __tipc_node_link_करोwn - handle loss of link
 * @n: target tipc_node
 * @bearer_id: id of the bearer
 * @xmitq: queue क्रम messages to be xmited on
 * @maddr: output media address of the bearer
 */
अटल व्योम __tipc_node_link_करोwn(काष्ठा tipc_node *n, पूर्णांक *bearer_id,
				  काष्ठा sk_buff_head *xmitq,
				  काष्ठा tipc_media_addr **maddr)
अणु
	काष्ठा tipc_link_entry *le = &n->links[*bearer_id];
	पूर्णांक *slot0 = &n->active_links[0];
	पूर्णांक *slot1 = &n->active_links[1];
	पूर्णांक i, highest = 0, prio;
	काष्ठा tipc_link *l, *_l, *tnl;

	l = n->links[*bearer_id].link;
	अगर (!l || tipc_link_is_reset(l))
		वापस;

	n->working_links--;
	n->action_flags |= TIPC_NOTIFY_LINK_DOWN;
	n->link_id = tipc_link_id(l);

	tipc_bearer_हटाओ_dest(n->net, *bearer_id, n->addr);

	pr_debug("Lost link <%s> on network plane %c\n",
		 tipc_link_name(l), tipc_link_plane(l));

	/* Select new active link अगर any available */
	*slot0 = INVALID_BEARER_ID;
	*slot1 = INVALID_BEARER_ID;
	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		_l = n->links[i].link;
		अगर (!_l || !tipc_link_is_up(_l))
			जारी;
		अगर (_l == l)
			जारी;
		prio = tipc_link_prio(_l);
		अगर (prio < highest)
			जारी;
		अगर (prio > highest) अणु
			highest = prio;
			*slot0 = i;
			*slot1 = i;
			जारी;
		पूर्ण
		*slot1 = i;
	पूर्ण

	अगर (!node_is_up(n)) अणु
		अगर (tipc_link_peer_is_करोwn(l))
			tipc_node_fsm_evt(n, PEER_LOST_CONTACT_EVT);
		tipc_node_fsm_evt(n, SELF_LOST_CONTACT_EVT);
		trace_tipc_link_reset(l, TIPC_DUMP_ALL, "link down!");
		tipc_link_fsm_evt(l, LINK_RESET_EVT);
		tipc_link_reset(l);
		tipc_link_build_reset_msg(l, xmitq);
		*maddr = &n->links[*bearer_id].maddr;
		node_lost_contact(n, &le->inputq);
		tipc_bcast_dec_bearer_dst_cnt(n->net, *bearer_id);
		वापस;
	पूर्ण
	tipc_bcast_dec_bearer_dst_cnt(n->net, *bearer_id);

	/* There is still a working link => initiate failover */
	*bearer_id = n->active_links[0];
	tnl = n->links[*bearer_id].link;
	tipc_link_fsm_evt(tnl, LINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);
	n->sync_poपूर्णांक = tipc_link_rcv_nxt(tnl) + (U16_MAX / 2 - 1);
	tipc_link_tnl_prepare(l, tnl, FAILOVER_MSG, xmitq);
	trace_tipc_link_reset(l, TIPC_DUMP_ALL, "link down -> failover!");
	tipc_link_reset(l);
	tipc_link_fsm_evt(l, LINK_RESET_EVT);
	tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAILOVER_BEGIN_EVT);
	*maddr = &n->links[*bearer_id].maddr;
पूर्ण

अटल व्योम tipc_node_link_करोwn(काष्ठा tipc_node *n, पूर्णांक bearer_id, bool delete)
अणु
	काष्ठा tipc_link_entry *le = &n->links[bearer_id];
	काष्ठा tipc_media_addr *maddr = शून्य;
	काष्ठा tipc_link *l = le->link;
	पूर्णांक old_bearer_id = bearer_id;
	काष्ठा sk_buff_head xmitq;

	अगर (!l)
		वापस;

	__skb_queue_head_init(&xmitq);

	tipc_node_ग_लिखो_lock(n);
	अगर (!tipc_link_is_establishing(l)) अणु
		__tipc_node_link_करोwn(n, &bearer_id, &xmitq, &maddr);
	पूर्ण अन्यथा अणु
		/* Defuse pending tipc_node_link_up() */
		tipc_link_reset(l);
		tipc_link_fsm_evt(l, LINK_RESET_EVT);
	पूर्ण
	अगर (delete) अणु
		kमुक्त(l);
		le->link = शून्य;
		n->link_cnt--;
	पूर्ण
	trace_tipc_node_link_करोwn(n, true, "node link down or deleted!");
	tipc_node_ग_लिखो_unlock(n);
	अगर (delete)
		tipc_mon_हटाओ_peer(n->net, n->addr, old_bearer_id);
	अगर (!skb_queue_empty(&xmitq))
		tipc_bearer_xmit(n->net, bearer_id, &xmitq, maddr, n);
	tipc_sk_rcv(n->net, &le->inputq);
पूर्ण

अटल bool node_is_up(काष्ठा tipc_node *n)
अणु
	वापस n->active_links[0] != INVALID_BEARER_ID;
पूर्ण

bool tipc_node_is_up(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_node *n;
	bool retval = false;

	अगर (in_own_node(net, addr))
		वापस true;

	n = tipc_node_find(net, addr);
	अगर (!n)
		वापस false;
	retval = node_is_up(n);
	tipc_node_put(n);
	वापस retval;
पूर्ण

अटल u32 tipc_node_suggest_addr(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_node *n;

	addr ^= tipc_net(net)->अक्रमom;
	जबतक ((n = tipc_node_find(net, addr))) अणु
		tipc_node_put(n);
		addr++;
	पूर्ण
	वापस addr;
पूर्ण

/* tipc_node_try_addr(): Check अगर addr can be used by peer, suggest other अगर not
 * Returns suggested address अगर any, otherwise 0
 */
u32 tipc_node_try_addr(काष्ठा net *net, u8 *id, u32 addr)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_node *n;
	bool preliminary;
	u32 sugg_addr;

	/* Suggest new address अगर some other peer is using this one */
	n = tipc_node_find(net, addr);
	अगर (n) अणु
		अगर (!स_भेद(n->peer_id, id, NODE_ID_LEN))
			addr = 0;
		tipc_node_put(n);
		अगर (!addr)
			वापस 0;
		वापस tipc_node_suggest_addr(net, addr);
	पूर्ण

	/* Suggest previously used address अगर peer is known */
	n = tipc_node_find_by_id(net, id);
	अगर (n) अणु
		sugg_addr = n->addr;
		preliminary = n->preliminary;
		tipc_node_put(n);
		अगर (!preliminary)
			वापस sugg_addr;
	पूर्ण

	/* Even this node may be in conflict */
	अगर (tn->trial_addr == addr)
		वापस tipc_node_suggest_addr(net, addr);

	वापस 0;
पूर्ण

व्योम tipc_node_check_dest(काष्ठा net *net, u32 addr,
			  u8 *peer_id, काष्ठा tipc_bearer *b,
			  u16 capabilities, u32 signature, u32 hash_mixes,
			  काष्ठा tipc_media_addr *maddr,
			  bool *respond, bool *dupl_addr)
अणु
	काष्ठा tipc_node *n;
	काष्ठा tipc_link *l, *snd_l;
	काष्ठा tipc_link_entry *le;
	bool addr_match = false;
	bool sign_match = false;
	bool link_up = false;
	bool accept_addr = false;
	bool reset = true;
	अक्षर *अगर_name;
	अचिन्हित दीर्घ पूर्णांकv;
	u16 session;

	*dupl_addr = false;
	*respond = false;

	n = tipc_node_create(net, addr, peer_id, capabilities, hash_mixes,
			     false);
	अगर (!n)
		वापस;

	tipc_node_ग_लिखो_lock(n);
	अगर (unlikely(!n->bc_entry.link)) अणु
		snd_l = tipc_bc_sndlink(net);
		अगर (!tipc_link_bc_create(net, tipc_own_addr(net),
					 addr, peer_id, U16_MAX,
					 tipc_link_min_win(snd_l),
					 tipc_link_max_win(snd_l),
					 n->capabilities,
					 &n->bc_entry.inputq1,
					 &n->bc_entry.namedq, snd_l,
					 &n->bc_entry.link)) अणु
			pr_warn("Broadcast rcv link creation failed, no mem\n");
			tipc_node_ग_लिखो_unlock_fast(n);
			tipc_node_put(n);
			वापस;
		पूर्ण
	पूर्ण

	le = &n->links[b->identity];

	/* Prepare to validate requesting node's signature and media address */
	l = le->link;
	link_up = l && tipc_link_is_up(l);
	addr_match = l && !स_भेद(&le->maddr, maddr, माप(*maddr));
	sign_match = (signature == n->signature);

	/* These three flags give us eight permutations: */

	अगर (sign_match && addr_match && link_up) अणु
		/* All is fine. Do nothing. */
		reset = false;
		/* Peer node is not a container/local namespace */
		अगर (!n->peer_hash_mix)
			n->peer_hash_mix = hash_mixes;
	पूर्ण अन्यथा अगर (sign_match && addr_match && !link_up) अणु
		/* Respond. The link will come up in due समय */
		*respond = true;
	पूर्ण अन्यथा अगर (sign_match && !addr_match && link_up) अणु
		/* Peer has changed i/f address without rebooting.
		 * If so, the link will reset soon, and the next
		 * discovery will be accepted. So we can ignore it.
		 * It may also be an cloned or malicious peer having
		 * chosen the same node address and signature as an
		 * existing one.
		 * Ignore requests until the link goes करोwn, अगर ever.
		 */
		*dupl_addr = true;
	पूर्ण अन्यथा अगर (sign_match && !addr_match && !link_up) अणु
		/* Peer link has changed i/f address without rebooting.
		 * It may also be a cloned or malicious peer; we can't
		 * distinguish between the two.
		 * The signature is correct, so we must accept.
		 */
		accept_addr = true;
		*respond = true;
	पूर्ण अन्यथा अगर (!sign_match && addr_match && link_up) अणु
		/* Peer node rebooted. Two possibilities:
		 *  - Delayed re-discovery; this link endpoपूर्णांक has alपढ़ोy
		 *    reset and re-established contact with the peer, beक्रमe
		 *    receiving a discovery message from that node.
		 *    (The peer happened to receive one from this node first).
		 *  - The peer came back so fast that our side has not
		 *    discovered it yet. Probing from this side will soon
		 *    reset the link, since there can be no working link
		 *    endpoपूर्णांक at the peer end, and the link will re-establish.
		 *  Accept the signature, since it comes from a known peer.
		 */
		n->signature = signature;
	पूर्ण अन्यथा अगर (!sign_match && addr_match && !link_up) अणु
		/*  The peer node has rebooted.
		 *  Accept signature, since it is a known peer.
		 */
		n->signature = signature;
		*respond = true;
	पूर्ण अन्यथा अगर (!sign_match && !addr_match && link_up) अणु
		/* Peer rebooted with new address, or a new/duplicate peer.
		 * Ignore until the link goes करोwn, अगर ever.
		 */
		*dupl_addr = true;
	पूर्ण अन्यथा अगर (!sign_match && !addr_match && !link_up) अणु
		/* Peer rebooted with new address, or it is a new peer.
		 * Accept signature and address.
		 */
		n->signature = signature;
		accept_addr = true;
		*respond = true;
	पूर्ण

	अगर (!accept_addr)
		जाओ निकास;

	/* Now create new link अगर not alपढ़ोy existing */
	अगर (!l) अणु
		अगर (n->link_cnt == 2)
			जाओ निकास;

		अगर_name = म_अक्षर(b->name, ':') + 1;
		get_अक्रमom_bytes(&session, माप(u16));
		अगर (!tipc_link_create(net, अगर_name, b->identity, b->tolerance,
				      b->net_plane, b->mtu, b->priority,
				      b->min_win, b->max_win, session,
				      tipc_own_addr(net), addr, peer_id,
				      n->capabilities,
				      tipc_bc_sndlink(n->net), n->bc_entry.link,
				      &le->inputq,
				      &n->bc_entry.namedq, &l)) अणु
			*respond = false;
			जाओ निकास;
		पूर्ण
		trace_tipc_link_reset(l, TIPC_DUMP_ALL, "link created!");
		tipc_link_reset(l);
		tipc_link_fsm_evt(l, LINK_RESET_EVT);
		अगर (n->state == NODE_FAILINGOVER)
			tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
		le->link = l;
		n->link_cnt++;
		tipc_node_calculate_समयr(n, l);
		अगर (n->link_cnt == 1) अणु
			पूर्णांकv = jअगरfies + msecs_to_jअगरfies(n->keepalive_पूर्णांकv);
			अगर (!mod_समयr(&n->समयr, पूर्णांकv))
				tipc_node_get(n);
		पूर्ण
	पूर्ण
	स_नकल(&le->maddr, maddr, माप(*maddr));
निकास:
	tipc_node_ग_लिखो_unlock(n);
	अगर (reset && l && !tipc_link_is_reset(l))
		tipc_node_link_करोwn(n, b->identity, false);
	tipc_node_put(n);
पूर्ण

व्योम tipc_node_delete_links(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_node *n;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(n, &tn->node_list, list) अणु
		tipc_node_link_करोwn(n, bearer_id, true);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम tipc_node_reset_links(काष्ठा tipc_node *n)
अणु
	पूर्णांक i;

	pr_warn("Resetting all links to %x\n", n->addr);

	trace_tipc_node_reset_links(n, true, " ");
	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		tipc_node_link_करोwn(n, i, false);
	पूर्ण
पूर्ण

/* tipc_node_fsm_evt - node finite state machine
 * Determines when contact is allowed with peer node
 */
अटल व्योम tipc_node_fsm_evt(काष्ठा tipc_node *n, पूर्णांक evt)
अणु
	पूर्णांक state = n->state;

	चयन (state) अणु
	हाल SELF_DOWN_PEER_DOWN:
		चयन (evt) अणु
		हाल SELF_ESTABL_CONTACT_EVT:
			state = SELF_UP_PEER_COMING;
			अवरोध;
		हाल PEER_ESTABL_CONTACT_EVT:
			state = SELF_COMING_PEER_UP;
			अवरोध;
		हाल SELF_LOST_CONTACT_EVT:
		हाल PEER_LOST_CONTACT_EVT:
			अवरोध;
		हाल NODE_SYNCH_END_EVT:
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल NODE_FAILOVER_BEGIN_EVT:
		हाल NODE_FAILOVER_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल SELF_UP_PEER_UP:
		चयन (evt) अणु
		हाल SELF_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_LEAVING;
			अवरोध;
		हाल PEER_LOST_CONTACT_EVT:
			state = SELF_LEAVING_PEER_DOWN;
			अवरोध;
		हाल NODE_SYNCH_BEGIN_EVT:
			state = NODE_SYNCHING;
			अवरोध;
		हाल NODE_FAILOVER_BEGIN_EVT:
			state = NODE_FAILINGOVER;
			अवरोध;
		हाल SELF_ESTABL_CONTACT_EVT:
		हाल PEER_ESTABL_CONTACT_EVT:
		हाल NODE_SYNCH_END_EVT:
		हाल NODE_FAILOVER_END_EVT:
			अवरोध;
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल SELF_DOWN_PEER_LEAVING:
		चयन (evt) अणु
		हाल PEER_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_DOWN;
			अवरोध;
		हाल SELF_ESTABL_CONTACT_EVT:
		हाल PEER_ESTABL_CONTACT_EVT:
		हाल SELF_LOST_CONTACT_EVT:
			अवरोध;
		हाल NODE_SYNCH_END_EVT:
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल NODE_FAILOVER_BEGIN_EVT:
		हाल NODE_FAILOVER_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल SELF_UP_PEER_COMING:
		चयन (evt) अणु
		हाल PEER_ESTABL_CONTACT_EVT:
			state = SELF_UP_PEER_UP;
			अवरोध;
		हाल SELF_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_DOWN;
			अवरोध;
		हाल SELF_ESTABL_CONTACT_EVT:
		हाल PEER_LOST_CONTACT_EVT:
		हाल NODE_SYNCH_END_EVT:
		हाल NODE_FAILOVER_BEGIN_EVT:
			अवरोध;
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल NODE_FAILOVER_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल SELF_COMING_PEER_UP:
		चयन (evt) अणु
		हाल SELF_ESTABL_CONTACT_EVT:
			state = SELF_UP_PEER_UP;
			अवरोध;
		हाल PEER_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_DOWN;
			अवरोध;
		हाल SELF_LOST_CONTACT_EVT:
		हाल PEER_ESTABL_CONTACT_EVT:
			अवरोध;
		हाल NODE_SYNCH_END_EVT:
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल NODE_FAILOVER_BEGIN_EVT:
		हाल NODE_FAILOVER_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल SELF_LEAVING_PEER_DOWN:
		चयन (evt) अणु
		हाल SELF_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_DOWN;
			अवरोध;
		हाल SELF_ESTABL_CONTACT_EVT:
		हाल PEER_ESTABL_CONTACT_EVT:
		हाल PEER_LOST_CONTACT_EVT:
			अवरोध;
		हाल NODE_SYNCH_END_EVT:
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल NODE_FAILOVER_BEGIN_EVT:
		हाल NODE_FAILOVER_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल NODE_FAILINGOVER:
		चयन (evt) अणु
		हाल SELF_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_LEAVING;
			अवरोध;
		हाल PEER_LOST_CONTACT_EVT:
			state = SELF_LEAVING_PEER_DOWN;
			अवरोध;
		हाल NODE_FAILOVER_END_EVT:
			state = SELF_UP_PEER_UP;
			अवरोध;
		हाल NODE_FAILOVER_BEGIN_EVT:
		हाल SELF_ESTABL_CONTACT_EVT:
		हाल PEER_ESTABL_CONTACT_EVT:
			अवरोध;
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल NODE_SYNCH_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	हाल NODE_SYNCHING:
		चयन (evt) अणु
		हाल SELF_LOST_CONTACT_EVT:
			state = SELF_DOWN_PEER_LEAVING;
			अवरोध;
		हाल PEER_LOST_CONTACT_EVT:
			state = SELF_LEAVING_PEER_DOWN;
			अवरोध;
		हाल NODE_SYNCH_END_EVT:
			state = SELF_UP_PEER_UP;
			अवरोध;
		हाल NODE_FAILOVER_BEGIN_EVT:
			state = NODE_FAILINGOVER;
			अवरोध;
		हाल NODE_SYNCH_BEGIN_EVT:
		हाल SELF_ESTABL_CONTACT_EVT:
		हाल PEER_ESTABL_CONTACT_EVT:
			अवरोध;
		हाल NODE_FAILOVER_END_EVT:
		शेष:
			जाओ illegal_evt;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("Unknown node fsm state %x\n", state);
		अवरोध;
	पूर्ण
	trace_tipc_node_fsm(n->peer_id, n->state, state, evt);
	n->state = state;
	वापस;

illegal_evt:
	pr_err("Illegal node fsm evt %x in state %x\n", evt, state);
	trace_tipc_node_fsm(n->peer_id, n->state, state, evt);
पूर्ण

अटल व्योम node_lost_contact(काष्ठा tipc_node *n,
			      काष्ठा sk_buff_head *inputq)
अणु
	काष्ठा tipc_sock_conn *conn, *safe;
	काष्ठा tipc_link *l;
	काष्ठा list_head *conns = &n->conn_sks;
	काष्ठा sk_buff *skb;
	uपूर्णांक i;

	pr_debug("Lost contact with %x\n", n->addr);
	n->delete_at = jअगरfies + msecs_to_jअगरfies(NODE_CLEANUP_AFTER);
	trace_tipc_node_lost_contact(n, true, " ");

	/* Clean up broadcast state */
	tipc_bcast_हटाओ_peer(n->net, n->bc_entry.link);
	skb_queue_purge(&n->bc_entry.namedq);

	/* Abort any ongoing link failover */
	क्रम (i = 0; i < MAX_BEARERS; i++) अणु
		l = n->links[i].link;
		अगर (l)
			tipc_link_fsm_evt(l, LINK_FAILOVER_END_EVT);
	पूर्ण

	/* Notअगरy खुलाations from this node */
	n->action_flags |= TIPC_NOTIFY_NODE_DOWN;
	n->peer_net = शून्य;
	n->peer_hash_mix = 0;
	/* Notअगरy sockets connected to node */
	list_क्रम_each_entry_safe(conn, safe, conns, list) अणु
		skb = tipc_msg_create(TIPC_CRITICAL_IMPORTANCE, TIPC_CONN_MSG,
				      SHORT_H_SIZE, 0, tipc_own_addr(n->net),
				      conn->peer_node, conn->port,
				      conn->peer_port, TIPC_ERR_NO_NODE);
		अगर (likely(skb))
			skb_queue_tail(inputq, skb);
		list_del(&conn->list);
		kमुक्त(conn);
	पूर्ण
पूर्ण

/**
 * tipc_node_get_linkname - get the name of a link
 *
 * @net: the applicable net namespace
 * @bearer_id: id of the bearer
 * @addr: peer node address
 * @linkname: link name output buffer
 * @len: size of @linkname output buffer
 *
 * Return: 0 on success
 */
पूर्णांक tipc_node_get_linkname(काष्ठा net *net, u32 bearer_id, u32 addr,
			   अक्षर *linkname, माप_प्रकार len)
अणु
	काष्ठा tipc_link *link;
	पूर्णांक err = -EINVAL;
	काष्ठा tipc_node *node = tipc_node_find(net, addr);

	अगर (!node)
		वापस err;

	अगर (bearer_id >= MAX_BEARERS)
		जाओ निकास;

	tipc_node_पढ़ो_lock(node);
	link = node->links[bearer_id].link;
	अगर (link) अणु
		म_नकलन(linkname, tipc_link_name(link), len);
		err = 0;
	पूर्ण
	tipc_node_पढ़ो_unlock(node);
निकास:
	tipc_node_put(node);
	वापस err;
पूर्ण

/* Caller should hold node lock क्रम the passed node */
अटल पूर्णांक __tipc_nl_add_node(काष्ठा tipc_nl_msg *msg, काष्ठा tipc_node *node)
अणु
	व्योम *hdr;
	काष्ठा nlattr *attrs;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_NODE_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_NODE);
	अगर (!attrs)
		जाओ msg_full;

	अगर (nla_put_u32(msg->skb, TIPC_NLA_NODE_ADDR, node->addr))
		जाओ attr_msg_full;
	अगर (node_is_up(node))
		अगर (nla_put_flag(msg->skb, TIPC_NLA_NODE_UP))
			जाओ attr_msg_full;

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	वापस 0;

attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण

अटल व्योम tipc_lxc_xmit(काष्ठा net *peer_net, काष्ठा sk_buff_head *list)
अणु
	काष्ठा tipc_msg *hdr = buf_msg(skb_peek(list));
	काष्ठा sk_buff_head inputq;

	चयन (msg_user(hdr)) अणु
	हाल TIPC_LOW_IMPORTANCE:
	हाल TIPC_MEDIUM_IMPORTANCE:
	हाल TIPC_HIGH_IMPORTANCE:
	हाल TIPC_CRITICAL_IMPORTANCE:
		अगर (msg_connected(hdr) || msg_named(hdr) ||
		    msg_direct(hdr)) अणु
			tipc_loopback_trace(peer_net, list);
			spin_lock_init(&list->lock);
			tipc_sk_rcv(peer_net, list);
			वापस;
		पूर्ण
		अगर (msg_mcast(hdr)) अणु
			tipc_loopback_trace(peer_net, list);
			skb_queue_head_init(&inputq);
			tipc_sk_mcast_rcv(peer_net, list, &inputq);
			__skb_queue_purge(list);
			skb_queue_purge(&inputq);
			वापस;
		पूर्ण
		वापस;
	हाल MSG_FRAGMENTER:
		अगर (tipc_msg_assemble(list)) अणु
			tipc_loopback_trace(peer_net, list);
			skb_queue_head_init(&inputq);
			tipc_sk_mcast_rcv(peer_net, list, &inputq);
			__skb_queue_purge(list);
			skb_queue_purge(&inputq);
		पूर्ण
		वापस;
	हाल GROUP_PROTOCOL:
	हाल CONN_MANAGER:
		tipc_loopback_trace(peer_net, list);
		spin_lock_init(&list->lock);
		tipc_sk_rcv(peer_net, list);
		वापस;
	हाल LINK_PROTOCOL:
	हाल NAME_DISTRIBUTOR:
	हाल TUNNEL_PROTOCOL:
	हाल BCAST_PROTOCOL:
		वापस;
	शेष:
		वापस;
	पूर्ण
पूर्ण

/**
 * tipc_node_xmit() - general link level function क्रम message sending
 * @net: the applicable net namespace
 * @list: chain of buffers containing message
 * @dnode: address of destination node
 * @selector: a number used क्रम deterministic link selection
 * Consumes the buffer chain.
 * Return: 0 अगर success, otherwise: -ELINKCONG,-EHOSTUNREACH,-EMSGSIZE,-ENOBUF
 */
पूर्णांक tipc_node_xmit(काष्ठा net *net, काष्ठा sk_buff_head *list,
		   u32 dnode, पूर्णांक selector)
अणु
	काष्ठा tipc_link_entry *le = शून्य;
	काष्ठा tipc_node *n;
	काष्ठा sk_buff_head xmitq;
	bool node_up = false;
	पूर्णांक bearer_id;
	पूर्णांक rc;

	अगर (in_own_node(net, dnode)) अणु
		tipc_loopback_trace(net, list);
		spin_lock_init(&list->lock);
		tipc_sk_rcv(net, list);
		वापस 0;
	पूर्ण

	n = tipc_node_find(net, dnode);
	अगर (unlikely(!n)) अणु
		__skb_queue_purge(list);
		वापस -EHOSTUNREACH;
	पूर्ण

	tipc_node_पढ़ो_lock(n);
	node_up = node_is_up(n);
	अगर (node_up && n->peer_net && check_net(n->peer_net)) अणु
		/* xmit inner linux container */
		tipc_lxc_xmit(n->peer_net, list);
		अगर (likely(skb_queue_empty(list))) अणु
			tipc_node_पढ़ो_unlock(n);
			tipc_node_put(n);
			वापस 0;
		पूर्ण
	पूर्ण

	bearer_id = n->active_links[selector & 1];
	अगर (unlikely(bearer_id == INVALID_BEARER_ID)) अणु
		tipc_node_पढ़ो_unlock(n);
		tipc_node_put(n);
		__skb_queue_purge(list);
		वापस -EHOSTUNREACH;
	पूर्ण

	__skb_queue_head_init(&xmitq);
	le = &n->links[bearer_id];
	spin_lock_bh(&le->lock);
	rc = tipc_link_xmit(le->link, list, &xmitq);
	spin_unlock_bh(&le->lock);
	tipc_node_पढ़ो_unlock(n);

	अगर (unlikely(rc == -ENOBUFS))
		tipc_node_link_करोwn(n, bearer_id, false);
	अन्यथा
		tipc_bearer_xmit(net, bearer_id, &xmitq, &le->maddr, n);

	tipc_node_put(n);

	वापस rc;
पूर्ण

/* tipc_node_xmit_skb(): send single buffer to destination
 * Buffers sent via this function are generally TIPC_SYSTEM_IMPORTANCE
 * messages, which will not be rejected
 * The only exception is datagram messages rerouted after secondary
 * lookup, which are rare and safe to dispose of anyway.
 */
पूर्णांक tipc_node_xmit_skb(काष्ठा net *net, काष्ठा sk_buff *skb, u32 dnode,
		       u32 selector)
अणु
	काष्ठा sk_buff_head head;

	__skb_queue_head_init(&head);
	__skb_queue_tail(&head, skb);
	tipc_node_xmit(net, &head, dnode, selector);
	वापस 0;
पूर्ण

/* tipc_node_distr_xmit(): send single buffer msgs to inभागidual destinations
 * Note: this is only क्रम SYSTEM_IMPORTANCE messages, which cannot be rejected
 */
पूर्णांक tipc_node_distr_xmit(काष्ठा net *net, काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा sk_buff *skb;
	u32 selector, dnode;

	जबतक ((skb = __skb_dequeue(xmitq))) अणु
		selector = msg_origport(buf_msg(skb));
		dnode = msg_destnode(buf_msg(skb));
		tipc_node_xmit_skb(net, skb, dnode, selector);
	पूर्ण
	वापस 0;
पूर्ण

व्योम tipc_node_broadcast(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक rc_dests)
अणु
	काष्ठा sk_buff_head xmitq;
	काष्ठा sk_buff *txskb;
	काष्ठा tipc_node *n;
	u16 dummy;
	u32 dst;

	/* Use broadcast अगर all nodes support it */
	अगर (!rc_dests && tipc_bcast_get_mode(net) != BCLINK_MODE_RCAST) अणु
		__skb_queue_head_init(&xmitq);
		__skb_queue_tail(&xmitq, skb);
		tipc_bcast_xmit(net, &xmitq, &dummy);
		वापस;
	पूर्ण

	/* Otherwise use legacy replicast method */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(n, tipc_nodes(net), list) अणु
		dst = n->addr;
		अगर (in_own_node(net, dst))
			जारी;
		अगर (!node_is_up(n))
			जारी;
		txskb = pskb_copy(skb, GFP_ATOMIC);
		अगर (!txskb)
			अवरोध;
		msg_set_destnode(buf_msg(txskb), dst);
		tipc_node_xmit_skb(net, txskb, dst, 0);
	पूर्ण
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम tipc_node_mcast_rcv(काष्ठा tipc_node *n)
अणु
	काष्ठा tipc_bclink_entry *be = &n->bc_entry;

	/* 'arrvq' is under inputq2's lock protection */
	spin_lock_bh(&be->inputq2.lock);
	spin_lock_bh(&be->inputq1.lock);
	skb_queue_splice_tail_init(&be->inputq1, &be->arrvq);
	spin_unlock_bh(&be->inputq1.lock);
	spin_unlock_bh(&be->inputq2.lock);
	tipc_sk_mcast_rcv(n->net, &be->arrvq, &be->inputq2);
पूर्ण

अटल व्योम tipc_node_bc_sync_rcv(काष्ठा tipc_node *n, काष्ठा tipc_msg *hdr,
				  पूर्णांक bearer_id, काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_link *ucl;
	पूर्णांक rc;

	rc = tipc_bcast_sync_rcv(n->net, n->bc_entry.link, hdr, xmitq);

	अगर (rc & TIPC_LINK_DOWN_EVT) अणु
		tipc_node_reset_links(n);
		वापस;
	पूर्ण

	अगर (!(rc & TIPC_LINK_SND_STATE))
		वापस;

	/* If probe message, a STATE response will be sent anyway */
	अगर (msg_probe(hdr))
		वापस;

	/* Produce a STATE message carrying broadcast NACK */
	tipc_node_पढ़ो_lock(n);
	ucl = n->links[bearer_id].link;
	अगर (ucl)
		tipc_link_build_state_msg(ucl, xmitq);
	tipc_node_पढ़ो_unlock(n);
पूर्ण

/**
 * tipc_node_bc_rcv - process TIPC broadcast packet arriving from off-node
 * @net: the applicable net namespace
 * @skb: TIPC packet
 * @bearer_id: id of bearer message arrived on
 *
 * Invoked with no locks held.
 */
अटल व्योम tipc_node_bc_rcv(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक bearer_id)
अणु
	पूर्णांक rc;
	काष्ठा sk_buff_head xmitq;
	काष्ठा tipc_bclink_entry *be;
	काष्ठा tipc_link_entry *le;
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	पूर्णांक usr = msg_user(hdr);
	u32 dnode = msg_destnode(hdr);
	काष्ठा tipc_node *n;

	__skb_queue_head_init(&xmitq);

	/* If NACK क्रम other node, let rcv link क्रम that node peek पूर्णांकo it */
	अगर ((usr == BCAST_PROTOCOL) && (dnode != tipc_own_addr(net)))
		n = tipc_node_find(net, dnode);
	अन्यथा
		n = tipc_node_find(net, msg_prevnode(hdr));
	अगर (!n) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	be = &n->bc_entry;
	le = &n->links[bearer_id];

	rc = tipc_bcast_rcv(net, be->link, skb);

	/* Broadcast ACKs are sent on a unicast link */
	अगर (rc & TIPC_LINK_SND_STATE) अणु
		tipc_node_पढ़ो_lock(n);
		tipc_link_build_state_msg(le->link, &xmitq);
		tipc_node_पढ़ो_unlock(n);
	पूर्ण

	अगर (!skb_queue_empty(&xmitq))
		tipc_bearer_xmit(net, bearer_id, &xmitq, &le->maddr, n);

	अगर (!skb_queue_empty(&be->inputq1))
		tipc_node_mcast_rcv(n);

	/* Handle NAME_DISTRIBUTOR messages sent from 1.7 nodes */
	अगर (!skb_queue_empty(&n->bc_entry.namedq))
		tipc_named_rcv(net, &n->bc_entry.namedq,
			       &n->bc_entry.named_rcv_nxt,
			       &n->bc_entry.named_खोलो);

	/* If reassembly or retransmission failure => reset all links to peer */
	अगर (rc & TIPC_LINK_DOWN_EVT)
		tipc_node_reset_links(n);

	tipc_node_put(n);
पूर्ण

/**
 * tipc_node_check_state - check and अगर necessary update node state
 * @n: target tipc_node
 * @skb: TIPC packet
 * @bearer_id: identity of bearer delivering the packet
 * @xmitq: queue क्रम messages to be xmited on
 * Return: true अगर state and msg are ok, otherwise false
 */
अटल bool tipc_node_check_state(काष्ठा tipc_node *n, काष्ठा sk_buff *skb,
				  पूर्णांक bearer_id, काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	पूर्णांक usr = msg_user(hdr);
	पूर्णांक mtyp = msg_type(hdr);
	u16 oseqno = msg_seqno(hdr);
	u16 exp_pkts = msg_msgcnt(hdr);
	u16 rcv_nxt, syncpt, dlv_nxt, inputq_len;
	पूर्णांक state = n->state;
	काष्ठा tipc_link *l, *tnl, *pl = शून्य;
	काष्ठा tipc_media_addr *maddr;
	पूर्णांक pb_id;

	अगर (trace_tipc_node_check_state_enabled()) अणु
		trace_tipc_skb_dump(skb, false, "skb for node state check");
		trace_tipc_node_check_state(n, true, " ");
	पूर्ण
	l = n->links[bearer_id].link;
	अगर (!l)
		वापस false;
	rcv_nxt = tipc_link_rcv_nxt(l);


	अगर (likely((state == SELF_UP_PEER_UP) && (usr != TUNNEL_PROTOCOL)))
		वापस true;

	/* Find parallel link, अगर any */
	क्रम (pb_id = 0; pb_id < MAX_BEARERS; pb_id++) अणु
		अगर ((pb_id != bearer_id) && n->links[pb_id].link) अणु
			pl = n->links[pb_id].link;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tipc_link_validate_msg(l, hdr)) अणु
		trace_tipc_skb_dump(skb, false, "PROTO invalid (2)!");
		trace_tipc_link_dump(l, TIPC_DUMP_NONE, "PROTO invalid (2)!");
		वापस false;
	पूर्ण

	/* Check and update node accesibility अगर applicable */
	अगर (state == SELF_UP_PEER_COMING) अणु
		अगर (!tipc_link_is_up(l))
			वापस true;
		अगर (!msg_peer_link_is_up(hdr))
			वापस true;
		tipc_node_fsm_evt(n, PEER_ESTABL_CONTACT_EVT);
	पूर्ण

	अगर (state == SELF_DOWN_PEER_LEAVING) अणु
		अगर (msg_peer_node_is_up(hdr))
			वापस false;
		tipc_node_fsm_evt(n, PEER_LOST_CONTACT_EVT);
		वापस true;
	पूर्ण

	अगर (state == SELF_LEAVING_PEER_DOWN)
		वापस false;

	/* Ignore duplicate packets */
	अगर ((usr != LINK_PROTOCOL) && less(oseqno, rcv_nxt))
		वापस true;

	/* Initiate or update failover mode अगर applicable */
	अगर ((usr == TUNNEL_PROTOCOL) && (mtyp == FAILOVER_MSG)) अणु
		syncpt = oseqno + exp_pkts - 1;
		अगर (pl && !tipc_link_is_reset(pl)) अणु
			__tipc_node_link_करोwn(n, &pb_id, xmitq, &maddr);
			trace_tipc_node_link_करोwn(n, true,
						  "node link down <- failover!");
			tipc_skb_queue_splice_tail_init(tipc_link_inputq(pl),
							tipc_link_inputq(l));
		पूर्ण

		/* If parallel link was alपढ़ोy करोwn, and this happened beक्रमe
		 * the tunnel link came up, node failover was never started.
		 * Ensure that a FAILOVER_MSG is sent to get peer out of
		 * NODE_FAILINGOVER state, also this node must accept
		 * TUNNEL_MSGs from peer.
		 */
		अगर (n->state != NODE_FAILINGOVER)
			tipc_node_link_failover(n, pl, l, xmitq);

		/* If pkts arrive out of order, use lowest calculated syncpt */
		अगर (less(syncpt, n->sync_poपूर्णांक))
			n->sync_poपूर्णांक = syncpt;
	पूर्ण

	/* Open parallel link when tunnel link reaches synch poपूर्णांक */
	अगर ((n->state == NODE_FAILINGOVER) && tipc_link_is_up(l)) अणु
		अगर (!more(rcv_nxt, n->sync_poपूर्णांक))
			वापस true;
		tipc_node_fsm_evt(n, NODE_FAILOVER_END_EVT);
		अगर (pl)
			tipc_link_fsm_evt(pl, LINK_FAILOVER_END_EVT);
		वापस true;
	पूर्ण

	/* No syncing needed अगर only one link */
	अगर (!pl || !tipc_link_is_up(pl))
		वापस true;

	/* Initiate synch mode अगर applicable */
	अगर ((usr == TUNNEL_PROTOCOL) && (mtyp == SYNCH_MSG) && (oseqno == 1)) अणु
		अगर (n->capabilities & TIPC_TUNNEL_ENHANCED)
			syncpt = msg_syncpt(hdr);
		अन्यथा
			syncpt = msg_seqno(msg_inner_hdr(hdr)) + exp_pkts - 1;
		अगर (!tipc_link_is_up(l))
			__tipc_node_link_up(n, bearer_id, xmitq);
		अगर (n->state == SELF_UP_PEER_UP) अणु
			n->sync_poपूर्णांक = syncpt;
			tipc_link_fsm_evt(l, LINK_SYNCH_BEGIN_EVT);
			tipc_node_fsm_evt(n, NODE_SYNCH_BEGIN_EVT);
		पूर्ण
	पूर्ण

	/* Open tunnel link when parallel link reaches synch poपूर्णांक */
	अगर (n->state == NODE_SYNCHING) अणु
		अगर (tipc_link_is_synching(l)) अणु
			tnl = l;
		पूर्ण अन्यथा अणु
			tnl = pl;
			pl = l;
		पूर्ण
		inputq_len = skb_queue_len(tipc_link_inputq(pl));
		dlv_nxt = tipc_link_rcv_nxt(pl) - inputq_len;
		अगर (more(dlv_nxt, n->sync_poपूर्णांक)) अणु
			tipc_link_fsm_evt(tnl, LINK_SYNCH_END_EVT);
			tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);
			वापस true;
		पूर्ण
		अगर (l == pl)
			वापस true;
		अगर ((usr == TUNNEL_PROTOCOL) && (mtyp == SYNCH_MSG))
			वापस true;
		अगर (usr == LINK_PROTOCOL)
			वापस true;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * tipc_rcv - process TIPC packets/messages arriving from off-node
 * @net: the applicable net namespace
 * @skb: TIPC packet
 * @b: poपूर्णांकer to bearer message arrived on
 *
 * Invoked with no locks held. Bearer poपूर्णांकer must poपूर्णांक to a valid bearer
 * काष्ठाure (i.e. cannot be शून्य), but bearer can be inactive.
 */
व्योम tipc_rcv(काष्ठा net *net, काष्ठा sk_buff *skb, काष्ठा tipc_bearer *b)
अणु
	काष्ठा sk_buff_head xmitq;
	काष्ठा tipc_link_entry *le;
	काष्ठा tipc_msg *hdr;
	काष्ठा tipc_node *n;
	पूर्णांक bearer_id = b->identity;
	u32 self = tipc_own_addr(net);
	पूर्णांक usr, rc = 0;
	u16 bc_ack;
#अगर_घोषित CONFIG_TIPC_CRYPTO
	काष्ठा tipc_ehdr *ehdr;

	/* Check अगर message must be decrypted first */
	अगर (TIPC_SKB_CB(skb)->decrypted || !tipc_ehdr_validate(skb))
		जाओ rcv;

	ehdr = (काष्ठा tipc_ehdr *)skb->data;
	अगर (likely(ehdr->user != LINK_CONFIG)) अणु
		n = tipc_node_find(net, ntohl(ehdr->addr));
		अगर (unlikely(!n))
			जाओ discard;
	पूर्ण अन्यथा अणु
		n = tipc_node_find_by_id(net, ehdr->id);
	पूर्ण
	tipc_crypto_rcv(net, (n) ? n->crypto_rx : शून्य, &skb, b);
	अगर (!skb)
		वापस;

rcv:
#पूर्ण_अगर
	/* Ensure message is well-क्रमmed beक्रमe touching the header */
	अगर (unlikely(!tipc_msg_validate(&skb)))
		जाओ discard;
	__skb_queue_head_init(&xmitq);
	hdr = buf_msg(skb);
	usr = msg_user(hdr);
	bc_ack = msg_bcast_ack(hdr);

	/* Handle arrival of discovery or broadcast packet */
	अगर (unlikely(msg_non_seq(hdr))) अणु
		अगर (unlikely(usr == LINK_CONFIG))
			वापस tipc_disc_rcv(net, skb, b);
		अन्यथा
			वापस tipc_node_bc_rcv(net, skb, bearer_id);
	पूर्ण

	/* Discard unicast link messages destined क्रम another node */
	अगर (unlikely(!msg_लघु(hdr) && (msg_destnode(hdr) != self)))
		जाओ discard;

	/* Locate neighboring node that sent packet */
	n = tipc_node_find(net, msg_prevnode(hdr));
	अगर (unlikely(!n))
		जाओ discard;
	le = &n->links[bearer_id];

	/* Ensure broadcast reception is in synch with peer's send state */
	अगर (unlikely(usr == LINK_PROTOCOL)) अणु
		अगर (unlikely(skb_linearize(skb))) अणु
			tipc_node_put(n);
			जाओ discard;
		पूर्ण
		hdr = buf_msg(skb);
		tipc_node_bc_sync_rcv(n, hdr, bearer_id, &xmitq);
	पूर्ण अन्यथा अगर (unlikely(tipc_link_acked(n->bc_entry.link) != bc_ack)) अणु
		tipc_bcast_ack_rcv(net, n->bc_entry.link, hdr);
	पूर्ण

	/* Receive packet directly अगर conditions permit */
	tipc_node_पढ़ो_lock(n);
	अगर (likely((n->state == SELF_UP_PEER_UP) && (usr != TUNNEL_PROTOCOL))) अणु
		spin_lock_bh(&le->lock);
		अगर (le->link) अणु
			rc = tipc_link_rcv(le->link, skb, &xmitq);
			skb = शून्य;
		पूर्ण
		spin_unlock_bh(&le->lock);
	पूर्ण
	tipc_node_पढ़ो_unlock(n);

	/* Check/update node state beक्रमe receiving */
	अगर (unlikely(skb)) अणु
		अगर (unlikely(skb_linearize(skb)))
			जाओ out_node_put;
		tipc_node_ग_लिखो_lock(n);
		अगर (tipc_node_check_state(n, skb, bearer_id, &xmitq)) अणु
			अगर (le->link) अणु
				rc = tipc_link_rcv(le->link, skb, &xmitq);
				skb = शून्य;
			पूर्ण
		पूर्ण
		tipc_node_ग_लिखो_unlock(n);
	पूर्ण

	अगर (unlikely(rc & TIPC_LINK_UP_EVT))
		tipc_node_link_up(n, bearer_id, &xmitq);

	अगर (unlikely(rc & TIPC_LINK_DOWN_EVT))
		tipc_node_link_करोwn(n, bearer_id, false);

	अगर (unlikely(!skb_queue_empty(&n->bc_entry.namedq)))
		tipc_named_rcv(net, &n->bc_entry.namedq,
			       &n->bc_entry.named_rcv_nxt,
			       &n->bc_entry.named_खोलो);

	अगर (unlikely(!skb_queue_empty(&n->bc_entry.inputq1)))
		tipc_node_mcast_rcv(n);

	अगर (!skb_queue_empty(&le->inputq))
		tipc_sk_rcv(net, &le->inputq);

	अगर (!skb_queue_empty(&xmitq))
		tipc_bearer_xmit(net, bearer_id, &xmitq, &le->maddr, n);

out_node_put:
	tipc_node_put(n);
discard:
	kमुक्त_skb(skb);
पूर्ण

व्योम tipc_node_apply_property(काष्ठा net *net, काष्ठा tipc_bearer *b,
			      पूर्णांक prop)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	पूर्णांक bearer_id = b->identity;
	काष्ठा sk_buff_head xmitq;
	काष्ठा tipc_link_entry *e;
	काष्ठा tipc_node *n;

	__skb_queue_head_init(&xmitq);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(n, &tn->node_list, list) अणु
		tipc_node_ग_लिखो_lock(n);
		e = &n->links[bearer_id];
		अगर (e->link) अणु
			अगर (prop == TIPC_NLA_PROP_TOL)
				tipc_link_set_tolerance(e->link, b->tolerance,
							&xmitq);
			अन्यथा अगर (prop == TIPC_NLA_PROP_MTU)
				tipc_link_set_mtu(e->link, b->mtu);

			/* Update MTU क्रम node link entry */
			e->mtu = tipc_link_mss(e->link);
		पूर्ण

		tipc_node_ग_लिखो_unlock(n);
		tipc_bearer_xmit(net, bearer_id, &xmitq, &e->maddr, शून्य);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक tipc_nl_peer_rm(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा nlattr *attrs[TIPC_NLA_NET_MAX + 1];
	काष्ठा tipc_node *peer, *temp_node;
	u8 node_id[NODE_ID_LEN];
	u64 *w0 = (u64 *)&node_id[0];
	u64 *w1 = (u64 *)&node_id[8];
	u32 addr;
	पूर्णांक err;

	/* We identअगरy the peer by its net */
	अगर (!info->attrs[TIPC_NLA_NET])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_NET_MAX,
					  info->attrs[TIPC_NLA_NET],
					  tipc_nl_net_policy, info->extack);
	अगर (err)
		वापस err;

	/* attrs[TIPC_NLA_NET_NODEID] and attrs[TIPC_NLA_NET_ADDR] are
	 * mutually exclusive हालs
	 */
	अगर (attrs[TIPC_NLA_NET_ADDR]) अणु
		addr = nla_get_u32(attrs[TIPC_NLA_NET_ADDR]);
		अगर (!addr)
			वापस -EINVAL;
	पूर्ण

	अगर (attrs[TIPC_NLA_NET_NODEID]) अणु
		अगर (!attrs[TIPC_NLA_NET_NODEID_W1])
			वापस -EINVAL;
		*w0 = nla_get_u64(attrs[TIPC_NLA_NET_NODEID]);
		*w1 = nla_get_u64(attrs[TIPC_NLA_NET_NODEID_W1]);
		addr = hash128to32(node_id);
	पूर्ण

	अगर (in_own_node(net, addr))
		वापस -ENOTSUPP;

	spin_lock_bh(&tn->node_list_lock);
	peer = tipc_node_find(net, addr);
	अगर (!peer) अणु
		spin_unlock_bh(&tn->node_list_lock);
		वापस -ENXIO;
	पूर्ण

	tipc_node_ग_लिखो_lock(peer);
	अगर (peer->state != SELF_DOWN_PEER_DOWN &&
	    peer->state != SELF_DOWN_PEER_LEAVING) अणु
		tipc_node_ग_लिखो_unlock(peer);
		err = -EBUSY;
		जाओ err_out;
	पूर्ण

	tipc_node_clear_links(peer);
	tipc_node_ग_लिखो_unlock(peer);
	tipc_node_delete(peer);

	/* Calculate cluster capabilities */
	tn->capabilities = TIPC_NODE_CAPABILITIES;
	list_क्रम_each_entry_rcu(temp_node, &tn->node_list, list) अणु
		tn->capabilities &= temp_node->capabilities;
	पूर्ण
	tipc_bcast_toggle_rcast(net, (tn->capabilities & TIPC_BCAST_RCAST));
	err = 0;
err_out:
	tipc_node_put(peer);
	spin_unlock_bh(&tn->node_list_lock);

	वापस err;
पूर्ण

पूर्णांक tipc_nl_node_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक err;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	पूर्णांक करोne = cb->args[0];
	पूर्णांक last_addr = cb->args[1];
	काष्ठा tipc_node *node;
	काष्ठा tipc_nl_msg msg;

	अगर (करोne)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rcu_पढ़ो_lock();
	अगर (last_addr) अणु
		node = tipc_node_find(net, last_addr);
		अगर (!node) अणु
			rcu_पढ़ो_unlock();
			/* We never set seq or call nl_dump_check_consistent()
			 * this means that setting prev_seq here will cause the
			 * consistence check to fail in the netlink callback
			 * handler. Resulting in the NLMSG_DONE message having
			 * the NLM_F_DUMP_INTR flag set अगर the node state
			 * changed जबतक we released the lock.
			 */
			cb->prev_seq = 1;
			वापस -EPIPE;
		पूर्ण
		tipc_node_put(node);
	पूर्ण

	list_क्रम_each_entry_rcu(node, &tn->node_list, list) अणु
		अगर (node->preliminary)
			जारी;
		अगर (last_addr) अणु
			अगर (node->addr == last_addr)
				last_addr = 0;
			अन्यथा
				जारी;
		पूर्ण

		tipc_node_पढ़ो_lock(node);
		err = __tipc_nl_add_node(&msg, node);
		अगर (err) अणु
			last_addr = node->addr;
			tipc_node_पढ़ो_unlock(node);
			जाओ out;
		पूर्ण

		tipc_node_पढ़ो_unlock(node);
	पूर्ण
	करोne = 1;
out:
	cb->args[0] = करोne;
	cb->args[1] = last_addr;
	rcu_पढ़ो_unlock();

	वापस skb->len;
पूर्ण

/* tipc_node_find_by_name - locate owner node of link by link's name
 * @net: the applicable net namespace
 * @name: poपूर्णांकer to link name string
 * @bearer_id: poपूर्णांकer to index in 'node->links' array where the link was found.
 *
 * Returns poपूर्णांकer to node owning the link, or 0 अगर no matching link is found.
 */
अटल काष्ठा tipc_node *tipc_node_find_by_name(काष्ठा net *net,
						स्थिर अक्षर *link_name,
						अचिन्हित पूर्णांक *bearer_id)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_link *l;
	काष्ठा tipc_node *n;
	काष्ठा tipc_node *found_node = शून्य;
	पूर्णांक i;

	*bearer_id = 0;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(n, &tn->node_list, list) अणु
		tipc_node_पढ़ो_lock(n);
		क्रम (i = 0; i < MAX_BEARERS; i++) अणु
			l = n->links[i].link;
			अगर (l && !म_भेद(tipc_link_name(l), link_name)) अणु
				*bearer_id = i;
				found_node = n;
				अवरोध;
			पूर्ण
		पूर्ण
		tipc_node_पढ़ो_unlock(n);
		अगर (found_node)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस found_node;
पूर्ण

पूर्णांक tipc_nl_node_set_link(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	पूर्णांक res = 0;
	पूर्णांक bearer_id;
	अक्षर *name;
	काष्ठा tipc_link *link;
	काष्ठा tipc_node *node;
	काष्ठा sk_buff_head xmitq;
	काष्ठा nlattr *attrs[TIPC_NLA_LINK_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);

	__skb_queue_head_init(&xmitq);

	अगर (!info->attrs[TIPC_NLA_LINK])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_LINK_MAX,
					  info->attrs[TIPC_NLA_LINK],
					  tipc_nl_link_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_LINK_NAME])
		वापस -EINVAL;

	name = nla_data(attrs[TIPC_NLA_LINK_NAME]);

	अगर (म_भेद(name, tipc_bclink_name) == 0)
		वापस tipc_nl_bc_link_set(net, attrs);

	node = tipc_node_find_by_name(net, name, &bearer_id);
	अगर (!node)
		वापस -EINVAL;

	tipc_node_पढ़ो_lock(node);

	link = node->links[bearer_id].link;
	अगर (!link) अणु
		res = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (attrs[TIPC_NLA_LINK_PROP]) अणु
		काष्ठा nlattr *props[TIPC_NLA_PROP_MAX + 1];

		err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_LINK_PROP], props);
		अगर (err) अणु
			res = err;
			जाओ out;
		पूर्ण

		अगर (props[TIPC_NLA_PROP_TOL]) अणु
			u32 tol;

			tol = nla_get_u32(props[TIPC_NLA_PROP_TOL]);
			tipc_link_set_tolerance(link, tol, &xmitq);
		पूर्ण
		अगर (props[TIPC_NLA_PROP_PRIO]) अणु
			u32 prio;

			prio = nla_get_u32(props[TIPC_NLA_PROP_PRIO]);
			tipc_link_set_prio(link, prio, &xmitq);
		पूर्ण
		अगर (props[TIPC_NLA_PROP_WIN]) अणु
			u32 max_win;

			max_win = nla_get_u32(props[TIPC_NLA_PROP_WIN]);
			tipc_link_set_queue_limits(link,
						   tipc_link_min_win(link),
						   max_win);
		पूर्ण
	पूर्ण

out:
	tipc_node_पढ़ो_unlock(node);
	tipc_bearer_xmit(net, bearer_id, &xmitq, &node->links[bearer_id].maddr,
			 शून्य);
	वापस res;
पूर्ण

पूर्णांक tipc_nl_node_get_link(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा nlattr *attrs[TIPC_NLA_LINK_MAX + 1];
	काष्ठा tipc_nl_msg msg;
	अक्षर *name;
	पूर्णांक err;

	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	अगर (!info->attrs[TIPC_NLA_LINK])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_LINK_MAX,
					  info->attrs[TIPC_NLA_LINK],
					  tipc_nl_link_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_LINK_NAME])
		वापस -EINVAL;

	name = nla_data(attrs[TIPC_NLA_LINK_NAME]);

	msg.skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!msg.skb)
		वापस -ENOMEM;

	अगर (म_भेद(name, tipc_bclink_name) == 0) अणु
		err = tipc_nl_add_bc_link(net, &msg, tipc_net(net)->bcl);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण अन्यथा अणु
		पूर्णांक bearer_id;
		काष्ठा tipc_node *node;
		काष्ठा tipc_link *link;

		node = tipc_node_find_by_name(net, name, &bearer_id);
		अगर (!node) अणु
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		tipc_node_पढ़ो_lock(node);
		link = node->links[bearer_id].link;
		अगर (!link) अणु
			tipc_node_पढ़ो_unlock(node);
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		err = __tipc_nl_add_link(net, &msg, link, 0);
		tipc_node_पढ़ो_unlock(node);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण

	वापस genlmsg_reply(msg.skb, info);

err_मुक्त:
	nlmsg_मुक्त(msg.skb);
	वापस err;
पूर्ण

पूर्णांक tipc_nl_node_reset_link_stats(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	अक्षर *link_name;
	अचिन्हित पूर्णांक bearer_id;
	काष्ठा tipc_link *link;
	काष्ठा tipc_node *node;
	काष्ठा nlattr *attrs[TIPC_NLA_LINK_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_link_entry *le;

	अगर (!info->attrs[TIPC_NLA_LINK])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_LINK_MAX,
					  info->attrs[TIPC_NLA_LINK],
					  tipc_nl_link_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!attrs[TIPC_NLA_LINK_NAME])
		वापस -EINVAL;

	link_name = nla_data(attrs[TIPC_NLA_LINK_NAME]);

	err = -EINVAL;
	अगर (!म_भेद(link_name, tipc_bclink_name)) अणु
		err = tipc_bclink_reset_stats(net, tipc_bc_sndlink(net));
		अगर (err)
			वापस err;
		वापस 0;
	पूर्ण अन्यथा अगर (म_माला(link_name, tipc_bclink_name)) अणु
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(node, &tn->node_list, list) अणु
			tipc_node_पढ़ो_lock(node);
			link = node->bc_entry.link;
			अगर (link && !म_भेद(link_name, tipc_link_name(link))) अणु
				err = tipc_bclink_reset_stats(net, link);
				tipc_node_पढ़ो_unlock(node);
				अवरोध;
			पूर्ण
			tipc_node_पढ़ो_unlock(node);
		पूर्ण
		rcu_पढ़ो_unlock();
		वापस err;
	पूर्ण

	node = tipc_node_find_by_name(net, link_name, &bearer_id);
	अगर (!node)
		वापस -EINVAL;

	le = &node->links[bearer_id];
	tipc_node_पढ़ो_lock(node);
	spin_lock_bh(&le->lock);
	link = node->links[bearer_id].link;
	अगर (!link) अणु
		spin_unlock_bh(&le->lock);
		tipc_node_पढ़ो_unlock(node);
		वापस -EINVAL;
	पूर्ण
	tipc_link_reset_stats(link);
	spin_unlock_bh(&le->lock);
	tipc_node_पढ़ो_unlock(node);
	वापस 0;
पूर्ण

/* Caller should hold node lock  */
अटल पूर्णांक __tipc_nl_add_node_links(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
				    काष्ठा tipc_node *node, u32 *prev_link,
				    bool bc_link)
अणु
	u32 i;
	पूर्णांक err;

	क्रम (i = *prev_link; i < MAX_BEARERS; i++) अणु
		*prev_link = i;

		अगर (!node->links[i].link)
			जारी;

		err = __tipc_nl_add_link(net, msg,
					 node->links[i].link, NLM_F_MULTI);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (bc_link) अणु
		*prev_link = i;
		err = tipc_nl_add_bc_link(net, msg, node->bc_entry.link);
		अगर (err)
			वापस err;
	पूर्ण

	*prev_link = 0;

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_node_dump_link(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr **attrs = genl_dumpit_info(cb)->attrs;
	काष्ठा nlattr *link[TIPC_NLA_LINK_MAX + 1];
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_node *node;
	काष्ठा tipc_nl_msg msg;
	u32 prev_node = cb->args[0];
	u32 prev_link = cb->args[1];
	पूर्णांक करोne = cb->args[2];
	bool bc_link = cb->args[3];
	पूर्णांक err;

	अगर (करोne)
		वापस 0;

	अगर (!prev_node) अणु
		/* Check अगर broadcast-receiver links dumping is needed */
		अगर (attrs && attrs[TIPC_NLA_LINK]) अणु
			err = nla_parse_nested_deprecated(link,
							  TIPC_NLA_LINK_MAX,
							  attrs[TIPC_NLA_LINK],
							  tipc_nl_link_policy,
							  शून्य);
			अगर (unlikely(err))
				वापस err;
			अगर (unlikely(!link[TIPC_NLA_LINK_BROADCAST]))
				वापस -EINVAL;
			bc_link = true;
		पूर्ण
	पूर्ण

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rcu_पढ़ो_lock();
	अगर (prev_node) अणु
		node = tipc_node_find(net, prev_node);
		अगर (!node) अणु
			/* We never set seq or call nl_dump_check_consistent()
			 * this means that setting prev_seq here will cause the
			 * consistence check to fail in the netlink callback
			 * handler. Resulting in the last NLMSG_DONE message
			 * having the NLM_F_DUMP_INTR flag set.
			 */
			cb->prev_seq = 1;
			जाओ out;
		पूर्ण
		tipc_node_put(node);

		list_क्रम_each_entry_जारी_rcu(node, &tn->node_list,
						 list) अणु
			tipc_node_पढ़ो_lock(node);
			err = __tipc_nl_add_node_links(net, &msg, node,
						       &prev_link, bc_link);
			tipc_node_पढ़ो_unlock(node);
			अगर (err)
				जाओ out;

			prev_node = node->addr;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = tipc_nl_add_bc_link(net, &msg, tn->bcl);
		अगर (err)
			जाओ out;

		list_क्रम_each_entry_rcu(node, &tn->node_list, list) अणु
			tipc_node_पढ़ो_lock(node);
			err = __tipc_nl_add_node_links(net, &msg, node,
						       &prev_link, bc_link);
			tipc_node_पढ़ो_unlock(node);
			अगर (err)
				जाओ out;

			prev_node = node->addr;
		पूर्ण
	पूर्ण
	करोne = 1;
out:
	rcu_पढ़ो_unlock();

	cb->args[0] = prev_node;
	cb->args[1] = prev_link;
	cb->args[2] = करोne;
	cb->args[3] = bc_link;

	वापस skb->len;
पूर्ण

पूर्णांक tipc_nl_node_set_monitor(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attrs[TIPC_NLA_MON_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक err;

	अगर (!info->attrs[TIPC_NLA_MON])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_MON_MAX,
					  info->attrs[TIPC_NLA_MON],
					  tipc_nl_monitor_policy,
					  info->extack);
	अगर (err)
		वापस err;

	अगर (attrs[TIPC_NLA_MON_ACTIVATION_THRESHOLD]) अणु
		u32 val;

		val = nla_get_u32(attrs[TIPC_NLA_MON_ACTIVATION_THRESHOLD]);
		err = tipc_nl_monitor_set_threshold(net, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __tipc_nl_add_monitor_prop(काष्ठा net *net, काष्ठा tipc_nl_msg *msg)
अणु
	काष्ठा nlattr *attrs;
	व्योम *hdr;
	u32 val;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  0, TIPC_NL_MON_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MON);
	अगर (!attrs)
		जाओ msg_full;

	val = tipc_nl_monitor_get_threshold(net);

	अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_ACTIVATION_THRESHOLD, val))
		जाओ attr_msg_full;

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	वापस 0;

attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण

पूर्णांक tipc_nl_node_get_monitor(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_nl_msg msg;
	पूर्णांक err;

	msg.skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!msg.skb)
		वापस -ENOMEM;
	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	err = __tipc_nl_add_monitor_prop(net, &msg);
	अगर (err) अणु
		nlmsg_मुक्त(msg.skb);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg.skb, info);
पूर्ण

पूर्णांक tipc_nl_node_dump_monitor(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	u32 prev_bearer = cb->args[0];
	काष्ठा tipc_nl_msg msg;
	पूर्णांक bearer_id;
	पूर्णांक err;

	अगर (prev_bearer == MAX_BEARERS)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rtnl_lock();
	क्रम (bearer_id = prev_bearer; bearer_id < MAX_BEARERS; bearer_id++) अणु
		err = __tipc_nl_add_monitor(net, &msg, bearer_id);
		अगर (err)
			अवरोध;
	पूर्ण
	rtnl_unlock();
	cb->args[0] = bearer_id;

	वापस skb->len;
पूर्ण

पूर्णांक tipc_nl_node_dump_monitor_peer(काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	u32 prev_node = cb->args[1];
	u32 bearer_id = cb->args[2];
	पूर्णांक करोne = cb->args[0];
	काष्ठा tipc_nl_msg msg;
	पूर्णांक err;

	अगर (!prev_node) अणु
		काष्ठा nlattr **attrs = genl_dumpit_info(cb)->attrs;
		काष्ठा nlattr *mon[TIPC_NLA_MON_MAX + 1];

		अगर (!attrs[TIPC_NLA_MON])
			वापस -EINVAL;

		err = nla_parse_nested_deprecated(mon, TIPC_NLA_MON_MAX,
						  attrs[TIPC_NLA_MON],
						  tipc_nl_monitor_policy,
						  शून्य);
		अगर (err)
			वापस err;

		अगर (!mon[TIPC_NLA_MON_REF])
			वापस -EINVAL;

		bearer_id = nla_get_u32(mon[TIPC_NLA_MON_REF]);

		अगर (bearer_id >= MAX_BEARERS)
			वापस -EINVAL;
	पूर्ण

	अगर (करोne)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rtnl_lock();
	err = tipc_nl_add_monitor_peer(net, &msg, bearer_id, &prev_node);
	अगर (!err)
		करोne = 1;

	rtnl_unlock();
	cb->args[0] = करोne;
	cb->args[1] = prev_node;
	cb->args[2] = bearer_id;

	वापस skb->len;
पूर्ण

#अगर_घोषित CONFIG_TIPC_CRYPTO
अटल पूर्णांक tipc_nl_retrieve_key(काष्ठा nlattr **attrs,
				काष्ठा tipc_aead_key **pkey)
अणु
	काष्ठा nlattr *attr = attrs[TIPC_NLA_NODE_KEY];
	काष्ठा tipc_aead_key *key;

	अगर (!attr)
		वापस -ENODATA;

	अगर (nla_len(attr) < माप(*key))
		वापस -EINVAL;
	key = (काष्ठा tipc_aead_key *)nla_data(attr);
	अगर (key->keylen > TIPC_AEAD_KEYLEN_MAX ||
	    nla_len(attr) < tipc_aead_key_size(key))
		वापस -EINVAL;

	*pkey = key;
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_retrieve_nodeid(काष्ठा nlattr **attrs, u8 **node_id)
अणु
	काष्ठा nlattr *attr = attrs[TIPC_NLA_NODE_ID];

	अगर (!attr)
		वापस -ENODATA;

	अगर (nla_len(attr) < TIPC_NODEID_LEN)
		वापस -EINVAL;

	*node_id = (u8 *)nla_data(attr);
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_retrieve_rekeying(काष्ठा nlattr **attrs, u32 *पूर्णांकv)
अणु
	काष्ठा nlattr *attr = attrs[TIPC_NLA_NODE_REKEYING];

	अगर (!attr)
		वापस -ENODATA;

	*पूर्णांकv = nla_get_u32(attr);
	वापस 0;
पूर्ण

अटल पूर्णांक __tipc_nl_node_set_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attrs[TIPC_NLA_NODE_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_crypto *tx = tipc_net(net)->crypto_tx, *c = tx;
	काष्ठा tipc_node *n = शून्य;
	काष्ठा tipc_aead_key *ukey;
	bool rekeying = true, master_key = false;
	u8 *id, *own_id, mode;
	u32 पूर्णांकv = 0;
	पूर्णांक rc = 0;

	अगर (!info->attrs[TIPC_NLA_NODE])
		वापस -EINVAL;

	rc = nla_parse_nested(attrs, TIPC_NLA_NODE_MAX,
			      info->attrs[TIPC_NLA_NODE],
			      tipc_nl_node_policy, info->extack);
	अगर (rc)
		वापस rc;

	own_id = tipc_own_id(net);
	अगर (!own_id) अणु
		GENL_SET_ERR_MSG(info, "not found own node identity (set id?)");
		वापस -EPERM;
	पूर्ण

	rc = tipc_nl_retrieve_rekeying(attrs, &पूर्णांकv);
	अगर (rc == -ENODATA)
		rekeying = false;

	rc = tipc_nl_retrieve_key(attrs, &ukey);
	अगर (rc == -ENODATA && rekeying)
		जाओ rekeying;
	अन्यथा अगर (rc)
		वापस rc;

	rc = tipc_aead_key_validate(ukey, info);
	अगर (rc)
		वापस rc;

	rc = tipc_nl_retrieve_nodeid(attrs, &id);
	चयन (rc) अणु
	हाल -ENODATA:
		mode = CLUSTER_KEY;
		master_key = !!(attrs[TIPC_NLA_NODE_KEY_MASTER]);
		अवरोध;
	हाल 0:
		mode = PER_NODE_KEY;
		अगर (स_भेद(id, own_id, NODE_ID_LEN)) अणु
			n = tipc_node_find_by_id(net, id) ?:
				tipc_node_create(net, 0, id, 0xffffu, 0, true);
			अगर (unlikely(!n))
				वापस -ENOMEM;
			c = n->crypto_rx;
		पूर्ण
		अवरोध;
	शेष:
		वापस rc;
	पूर्ण

	/* Initiate the TX/RX key */
	rc = tipc_crypto_key_init(c, ukey, mode, master_key);
	अगर (n)
		tipc_node_put(n);

	अगर (unlikely(rc < 0)) अणु
		GENL_SET_ERR_MSG(info, "unable to initiate or attach new key");
		वापस rc;
	पूर्ण अन्यथा अगर (c == tx) अणु
		/* Distribute TX key but not master one */
		अगर (!master_key && tipc_crypto_key_distr(tx, rc, शून्य))
			GENL_SET_ERR_MSG(info, "failed to replicate new key");
rekeying:
		/* Schedule TX rekeying अगर needed */
		tipc_crypto_rekeying_sched(tx, rekeying, पूर्णांकv);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_node_set_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_node_set_key(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक __tipc_nl_node_flush_key(काष्ठा sk_buff *skb,
				    काष्ठा genl_info *info)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_node *n;

	tipc_crypto_key_flush(tn->crypto_tx);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(n, &tn->node_list, list)
		tipc_crypto_key_flush(n->crypto_rx);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_node_flush_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_node_flush_key(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण
#पूर्ण_अगर

/**
 * tipc_node_dump - dump TIPC node data
 * @n: tipc node to be dumped
 * @more: dump more?
 *        - false: dump only tipc node data
 *        - true: dump node link data as well
 * @buf: वापसed buffer of dump data in क्रमmat
 */
पूर्णांक tipc_node_dump(काष्ठा tipc_node *n, bool more, अक्षर *buf)
अणु
	पूर्णांक i = 0;
	माप_प्रकार sz = (more) ? NODE_LMAX : NODE_LMIN;

	अगर (!n) अणु
		i += scnम_लिखो(buf, sz, "node data: (null)\n");
		वापस i;
	पूर्ण

	i += scnम_लिखो(buf, sz, "node data: %x", n->addr);
	i += scnम_लिखो(buf + i, sz - i, " %x", n->state);
	i += scnम_लिखो(buf + i, sz - i, " %d", n->active_links[0]);
	i += scnम_लिखो(buf + i, sz - i, " %d", n->active_links[1]);
	i += scnम_लिखो(buf + i, sz - i, " %x", n->action_flags);
	i += scnम_लिखो(buf + i, sz - i, " %u", n->failover_sent);
	i += scnम_लिखो(buf + i, sz - i, " %u", n->sync_poपूर्णांक);
	i += scnम_लिखो(buf + i, sz - i, " %d", n->link_cnt);
	i += scnम_लिखो(buf + i, sz - i, " %u", n->working_links);
	i += scnम_लिखो(buf + i, sz - i, " %x", n->capabilities);
	i += scnम_लिखो(buf + i, sz - i, " %lu\n", n->keepalive_पूर्णांकv);

	अगर (!more)
		वापस i;

	i += scnम_लिखो(buf + i, sz - i, "link_entry[0]:\n");
	i += scnम_लिखो(buf + i, sz - i, " mtu: %u\n", n->links[0].mtu);
	i += scnम_लिखो(buf + i, sz - i, " media: ");
	i += tipc_media_addr_म_लिखो(buf + i, sz - i, &n->links[0].maddr);
	i += scnम_लिखो(buf + i, sz - i, "\n");
	i += tipc_link_dump(n->links[0].link, TIPC_DUMP_NONE, buf + i);
	i += scnम_लिखो(buf + i, sz - i, " inputq: ");
	i += tipc_list_dump(&n->links[0].inputq, false, buf + i);

	i += scnम_लिखो(buf + i, sz - i, "link_entry[1]:\n");
	i += scnम_लिखो(buf + i, sz - i, " mtu: %u\n", n->links[1].mtu);
	i += scnम_लिखो(buf + i, sz - i, " media: ");
	i += tipc_media_addr_म_लिखो(buf + i, sz - i, &n->links[1].maddr);
	i += scnम_लिखो(buf + i, sz - i, "\n");
	i += tipc_link_dump(n->links[1].link, TIPC_DUMP_NONE, buf + i);
	i += scnम_लिखो(buf + i, sz - i, " inputq: ");
	i += tipc_list_dump(&n->links[1].inputq, false, buf + i);

	i += scnम_लिखो(buf + i, sz - i, "bclink:\n ");
	i += tipc_link_dump(n->bc_entry.link, TIPC_DUMP_NONE, buf + i);

	वापस i;
पूर्ण

व्योम tipc_node_pre_cleanup_net(काष्ठा net *निकास_net)
अणु
	काष्ठा tipc_node *n;
	काष्ठा tipc_net *tn;
	काष्ठा net *पंचांगp;

	rcu_पढ़ो_lock();
	क्रम_each_net_rcu(पंचांगp) अणु
		अगर (पंचांगp == निकास_net)
			जारी;
		tn = tipc_net(पंचांगp);
		अगर (!tn)
			जारी;
		spin_lock_bh(&tn->node_list_lock);
		list_क्रम_each_entry_rcu(n, &tn->node_list, list) अणु
			अगर (!n->peer_net)
				जारी;
			अगर (n->peer_net != निकास_net)
				जारी;
			tipc_node_ग_लिखो_lock(n);
			n->peer_net = शून्य;
			n->peer_hash_mix = 0;
			tipc_node_ग_लिखो_unlock_fast(n);
			अवरोध;
		पूर्ण
		spin_unlock_bh(&tn->node_list_lock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
