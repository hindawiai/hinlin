<शैली गुरु>
/*
 * net/tipc/name_distr.c: TIPC name distribution code
 *
 * Copyright (c) 2000-2006, 2014-2019, Ericsson AB
 * Copyright (c) 2005, 2010-2011, Wind River Systems
 * Copyright (c) 2020-2021, Red Hat Inc
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
#समावेश "name_distr.h"

पूर्णांक sysctl_tipc_named_समयout __पढ़ो_mostly = 2000;

काष्ठा distr_queue_item अणु
	काष्ठा distr_item i;
	u32 dtype;
	u32 node;
	अचिन्हित दीर्घ expires;
	काष्ठा list_head next;
पूर्ण;

/**
 * publ_to_item - add खुलाation info to a खुलाation message
 * @p: खुलाation info
 * @i: location of item in the message
 */
अटल व्योम publ_to_item(काष्ठा distr_item *i, काष्ठा खुलाation *p)
अणु
	i->type = htonl(p->sr.type);
	i->lower = htonl(p->sr.lower);
	i->upper = htonl(p->sr.upper);
	i->port = htonl(p->sk.ref);
	i->key = htonl(p->key);
पूर्ण

/**
 * named_prepare_buf - allocate & initialize a खुलाation message
 * @net: the associated network namespace
 * @type: message type
 * @size: payload size
 * @dest: destination node
 *
 * The buffer वापसed is of size INT_H_SIZE + payload size
 */
अटल काष्ठा sk_buff *named_prepare_buf(काष्ठा net *net, u32 type, u32 size,
					 u32 dest)
अणु
	काष्ठा sk_buff *buf = tipc_buf_acquire(INT_H_SIZE + size, GFP_ATOMIC);
	u32 self = tipc_own_addr(net);
	काष्ठा tipc_msg *msg;

	अगर (buf != शून्य) अणु
		msg = buf_msg(buf);
		tipc_msg_init(self, msg, NAME_DISTRIBUTOR,
			      type, INT_H_SIZE, dest);
		msg_set_size(msg, INT_H_SIZE + size);
	पूर्ण
	वापस buf;
पूर्ण

/**
 * tipc_named_publish - tell other nodes about a new खुलाation by this node
 * @net: the associated network namespace
 * @p: the new खुलाation
 */
काष्ठा sk_buff *tipc_named_publish(काष्ठा net *net, काष्ठा खुलाation *p)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा distr_item *item;
	काष्ठा sk_buff *skb;

	अगर (p->scope == TIPC_NODE_SCOPE) अणु
		list_add_tail_rcu(&p->binding_node, &nt->node_scope);
		वापस शून्य;
	पूर्ण
	ग_लिखो_lock_bh(&nt->cluster_scope_lock);
	list_add_tail(&p->binding_node, &nt->cluster_scope);
	ग_लिखो_unlock_bh(&nt->cluster_scope_lock);
	skb = named_prepare_buf(net, PUBLICATION, ITEM_SIZE, 0);
	अगर (!skb) अणु
		pr_warn("Publication distribution failure\n");
		वापस शून्य;
	पूर्ण
	msg_set_named_seqno(buf_msg(skb), nt->snd_nxt++);
	msg_set_non_legacy(buf_msg(skb));
	item = (काष्ठा distr_item *)msg_data(buf_msg(skb));
	publ_to_item(item, p);
	वापस skb;
पूर्ण

/**
 * tipc_named_withdraw - tell other nodes about a withdrawn खुलाation by this node
 * @net: the associated network namespace
 * @p: the withdrawn खुलाation
 */
काष्ठा sk_buff *tipc_named_withdraw(काष्ठा net *net, काष्ठा खुलाation *p)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा distr_item *item;
	काष्ठा sk_buff *skb;

	ग_लिखो_lock_bh(&nt->cluster_scope_lock);
	list_del(&p->binding_node);
	ग_लिखो_unlock_bh(&nt->cluster_scope_lock);
	अगर (p->scope == TIPC_NODE_SCOPE)
		वापस शून्य;

	skb = named_prepare_buf(net, WITHDRAWAL, ITEM_SIZE, 0);
	अगर (!skb) अणु
		pr_warn("Withdrawal distribution failure\n");
		वापस शून्य;
	पूर्ण
	msg_set_named_seqno(buf_msg(skb), nt->snd_nxt++);
	msg_set_non_legacy(buf_msg(skb));
	item = (काष्ठा distr_item *)msg_data(buf_msg(skb));
	publ_to_item(item, p);
	वापस skb;
पूर्ण

/**
 * named_distribute - prepare name info क्रम bulk distribution to another node
 * @net: the associated network namespace
 * @list: list of messages (buffers) to be वापसed from this function
 * @dnode: node to be updated
 * @pls: linked list of खुलाation items to be packed पूर्णांकo buffer chain
 * @seqno: sequence number क्रम this message
 */
अटल व्योम named_distribute(काष्ठा net *net, काष्ठा sk_buff_head *list,
			     u32 dnode, काष्ठा list_head *pls, u16 seqno)
अणु
	काष्ठा खुलाation *publ;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा distr_item *item = शून्य;
	u32 msg_dsz = ((tipc_node_get_mtu(net, dnode, 0, false) - INT_H_SIZE) /
			ITEM_SIZE) * ITEM_SIZE;
	u32 msg_rem = msg_dsz;
	काष्ठा tipc_msg *hdr;

	list_क्रम_each_entry(publ, pls, binding_node) अणु
		/* Prepare next buffer: */
		अगर (!skb) अणु
			skb = named_prepare_buf(net, PUBLICATION, msg_rem,
						dnode);
			अगर (!skb) अणु
				pr_warn("Bulk publication failure\n");
				वापस;
			पूर्ण
			hdr = buf_msg(skb);
			msg_set_bc_ack_invalid(hdr, true);
			msg_set_bulk(hdr);
			msg_set_non_legacy(hdr);
			item = (काष्ठा distr_item *)msg_data(hdr);
		पूर्ण

		/* Pack खुलाation पूर्णांकo message: */
		publ_to_item(item, publ);
		item++;
		msg_rem -= ITEM_SIZE;

		/* Append full buffer to list: */
		अगर (!msg_rem) अणु
			__skb_queue_tail(list, skb);
			skb = शून्य;
			msg_rem = msg_dsz;
		पूर्ण
	पूर्ण
	अगर (skb) अणु
		hdr = buf_msg(skb);
		msg_set_size(hdr, INT_H_SIZE + (msg_dsz - msg_rem));
		skb_trim(skb, INT_H_SIZE + (msg_dsz - msg_rem));
		__skb_queue_tail(list, skb);
	पूर्ण
	hdr = buf_msg(skb_peek_tail(list));
	msg_set_last_bulk(hdr);
	msg_set_named_seqno(hdr, seqno);
पूर्ण

/**
 * tipc_named_node_up - tell specअगरied node about all खुलाations by this node
 * @net: the associated network namespace
 * @dnode: destination node
 * @capabilities: peer node's capabilities
 */
व्योम tipc_named_node_up(काष्ठा net *net, u32 dnode, u16 capabilities)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा sk_buff_head head;
	u16 seqno;

	__skb_queue_head_init(&head);
	spin_lock_bh(&tn->nametbl_lock);
	अगर (!(capabilities & TIPC_NAMED_BCAST))
		nt->rc_dests++;
	seqno = nt->snd_nxt;
	spin_unlock_bh(&tn->nametbl_lock);

	पढ़ो_lock_bh(&nt->cluster_scope_lock);
	named_distribute(net, &head, dnode, &nt->cluster_scope, seqno);
	tipc_node_xmit(net, &head, dnode, 0);
	पढ़ो_unlock_bh(&nt->cluster_scope_lock);
पूर्ण

/**
 * tipc_publ_purge - हटाओ खुलाation associated with a failed node
 * @net: the associated network namespace
 * @p: the खुलाation to हटाओ
 * @addr: failed node's address
 *
 * Invoked क्रम each खुलाation issued by a newly failed node.
 * Removes खुलाation काष्ठाure from name table & deletes it.
 */
अटल व्योम tipc_publ_purge(काष्ठा net *net, काष्ठा खुलाation *p, u32 addr)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा खुलाation *_p;
	काष्ठा tipc_uaddr ua;

	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, p->scope, p->sr.type,
		   p->sr.lower, p->sr.upper);
	spin_lock_bh(&tn->nametbl_lock);
	_p = tipc_nametbl_हटाओ_publ(net, &ua, &p->sk, p->key);
	अगर (_p)
		tipc_node_unsubscribe(net, &_p->binding_node, addr);
	spin_unlock_bh(&tn->nametbl_lock);
	अगर (_p)
		kमुक्त_rcu(_p, rcu);
पूर्ण

व्योम tipc_publ_notअगरy(काष्ठा net *net, काष्ठा list_head *nsub_list,
		      u32 addr, u16 capabilities)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_net *tn = tipc_net(net);

	काष्ठा खुलाation *publ, *पंचांगp;

	list_क्रम_each_entry_safe(publ, पंचांगp, nsub_list, binding_node)
		tipc_publ_purge(net, publ, addr);
	spin_lock_bh(&tn->nametbl_lock);
	अगर (!(capabilities & TIPC_NAMED_BCAST))
		nt->rc_dests--;
	spin_unlock_bh(&tn->nametbl_lock);
पूर्ण

/**
 * tipc_update_nametbl - try to process a nametable update and notअगरy
 *			 subscribers
 * @net: the associated network namespace
 * @i: location of item in the message
 * @node: node address
 * @dtype: name distributor message type
 *
 * tipc_nametbl_lock must be held.
 * Return: the खुलाation item अगर successful, otherwise शून्य.
 */
अटल bool tipc_update_nametbl(काष्ठा net *net, काष्ठा distr_item *i,
				u32 node, u32 dtype)
अणु
	काष्ठा खुलाation *p = शून्य;
	काष्ठा tipc_socket_addr sk;
	काष्ठा tipc_uaddr ua;
	u32 key = ntohl(i->key);

	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, TIPC_CLUSTER_SCOPE,
		   ntohl(i->type), ntohl(i->lower), ntohl(i->upper));
	sk.ref = ntohl(i->port);
	sk.node = node;

	अगर (dtype == PUBLICATION) अणु
		p = tipc_nametbl_insert_publ(net, &ua, &sk, key);
		अगर (p) अणु
			tipc_node_subscribe(net, &p->binding_node, node);
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अगर (dtype == WITHDRAWAL) अणु
		p = tipc_nametbl_हटाओ_publ(net, &ua, &sk, key);
		अगर (p) अणु
			tipc_node_unsubscribe(net, &p->binding_node, node);
			kमुक्त_rcu(p, rcu);
			वापस true;
		पूर्ण
		pr_warn_ratelimited("Failed to remove binding %u,%u from %u\n",
				    ua.sr.type, ua.sr.lower, node);
	पूर्ण अन्यथा अणु
		pr_warn("Unrecognized name table message received\n");
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा sk_buff *tipc_named_dequeue(काष्ठा sk_buff_head *namedq,
					  u16 *rcv_nxt, bool *खोलो)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा tipc_msg *hdr;
	u16 seqno;

	spin_lock_bh(&namedq->lock);
	skb_queue_walk_safe(namedq, skb, पंचांगp) अणु
		अगर (unlikely(skb_linearize(skb))) अणु
			__skb_unlink(skb, namedq);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण
		hdr = buf_msg(skb);
		seqno = msg_named_seqno(hdr);
		अगर (msg_is_last_bulk(hdr)) अणु
			*rcv_nxt = seqno;
			*खोलो = true;
		पूर्ण

		अगर (msg_is_bulk(hdr) || msg_is_legacy(hdr)) अणु
			__skb_unlink(skb, namedq);
			spin_unlock_bh(&namedq->lock);
			वापस skb;
		पूर्ण

		अगर (*खोलो && (*rcv_nxt == seqno)) अणु
			(*rcv_nxt)++;
			__skb_unlink(skb, namedq);
			spin_unlock_bh(&namedq->lock);
			वापस skb;
		पूर्ण

		अगर (less(seqno, *rcv_nxt)) अणु
			__skb_unlink(skb, namedq);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&namedq->lock);
	वापस शून्य;
पूर्ण

/**
 * tipc_named_rcv - process name table update messages sent by another node
 * @net: the associated network namespace
 * @namedq: queue to receive from
 * @rcv_nxt: store last received seqno here
 * @खोलो: last bulk msg was received (FIXME)
 */
व्योम tipc_named_rcv(काष्ठा net *net, काष्ठा sk_buff_head *namedq,
		    u16 *rcv_nxt, bool *खोलो)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा distr_item *item;
	काष्ठा tipc_msg *hdr;
	काष्ठा sk_buff *skb;
	u32 count, node;

	spin_lock_bh(&tn->nametbl_lock);
	जबतक ((skb = tipc_named_dequeue(namedq, rcv_nxt, खोलो))) अणु
		hdr = buf_msg(skb);
		node = msg_orignode(hdr);
		item = (काष्ठा distr_item *)msg_data(hdr);
		count = msg_data_sz(hdr) / ITEM_SIZE;
		जबतक (count--) अणु
			tipc_update_nametbl(net, item, node, msg_type(hdr));
			item++;
		पूर्ण
		kमुक्त_skb(skb);
	पूर्ण
	spin_unlock_bh(&tn->nametbl_lock);
पूर्ण

/**
 * tipc_named_reinit - re-initialize local खुलाations
 * @net: the associated network namespace
 *
 * This routine is called whenever TIPC networking is enabled.
 * All name table entries published by this node are updated to reflect
 * the node's new network address.
 */
व्योम tipc_named_reinit(काष्ठा net *net)
अणु
	काष्ठा name_table *nt = tipc_name_table(net);
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा खुलाation *p;
	u32 self = tipc_own_addr(net);

	spin_lock_bh(&tn->nametbl_lock);

	list_क्रम_each_entry_rcu(p, &nt->node_scope, binding_node)
		p->sk.node = self;
	list_क्रम_each_entry_rcu(p, &nt->cluster_scope, binding_node)
		p->sk.node = self;
	nt->rc_dests = 0;
	spin_unlock_bh(&tn->nametbl_lock);
पूर्ण
