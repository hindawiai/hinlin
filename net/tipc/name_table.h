<शैली गुरु>
/*
 * net/tipc/name_table.h: Include file क्रम TIPC name table code
 *
 * Copyright (c) 2000-2006, 2014-2018, Ericsson AB
 * Copyright (c) 2004-2005, 2010-2011, Wind River Systems
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

#अगर_अघोषित _TIPC_NAME_TABLE_H
#घोषणा _TIPC_NAME_TABLE_H

काष्ठा tipc_subscription;
काष्ठा tipc_plist;
काष्ठा tipc_nlist;
काष्ठा tipc_group;
काष्ठा tipc_uaddr;

/*
 * TIPC name types reserved क्रम पूर्णांकernal TIPC use (both current and planned)
 */
#घोषणा TIPC_ZM_SRV		3	/* zone master service name type */
#घोषणा TIPC_PUBL_SCOPE_NUM	(TIPC_NODE_SCOPE + 1)
#घोषणा TIPC_NAMETBL_SIZE	1024	/* must be a घातer of 2 */

/**
 * काष्ठा खुलाation - info about a published service address or range
 * @sr: service range represented by this खुलाation
 * @sk: address of socket bound to this खुलाation
 * @scope: scope of खुलाation, TIPC_NODE_SCOPE or TIPC_CLUSTER_SCOPE
 * @key: खुलाation key, unique across the cluster
 * @id: खुलाation id
 * @binding_node: all खुलाations from the same node which bound this one
 * - Remote खुलाations: in node->publ_list;
 * Used by node/name distr to withdraw खुलाations when node is lost
 * - Local/node scope खुलाations: in name_table->node_scope list
 * - Local/cluster scope खुलाations: in name_table->cluster_scope list
 * @binding_sock: all खुलाations from the same socket which bound this one
 *   Used by socket to withdraw खुलाations when socket is unbound/released
 * @local_publ: list of identical खुलाations made from this node
 *   Used by बंदst_first and multicast receive lookup algorithms
 * @all_publ: all खुलाations identical to this one, whatever node and scope
 *   Used by round-robin lookup algorithm
 * @list: to क्रमm a list of खुलाations in temporal order
 * @rcu: RCU callback head used क्रम deferred मुक्तing
 */
काष्ठा खुलाation अणु
	काष्ठा tipc_service_range sr;
	काष्ठा tipc_socket_addr sk;
	u16 scope;
	u32 key;
	u32 id;
	काष्ठा list_head binding_node;
	काष्ठा list_head binding_sock;
	काष्ठा list_head local_publ;
	काष्ठा list_head all_publ;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा name_table - table containing all existing port name खुलाations
 * @services: name sequence hash lists
 * @node_scope: all local खुलाations with node scope
 *               - used by name_distr during re-init of name table
 * @cluster_scope: all local खुलाations with cluster scope
 *               - used by name_distr to send bulk updates to new nodes
 *               - used by name_distr during re-init of name table
 * @cluster_scope_lock: lock क्रम accessing @cluster_scope
 * @local_publ_count: number of खुलाations issued by this node
 * @rc_dests: destination node counter
 * @snd_nxt: next sequence number to be used
 */
काष्ठा name_table अणु
	काष्ठा hlist_head services[TIPC_NAMETBL_SIZE];
	काष्ठा list_head node_scope;
	काष्ठा list_head cluster_scope;
	rwlock_t cluster_scope_lock;
	u32 local_publ_count;
	u32 rc_dests;
	u32 snd_nxt;
पूर्ण;

पूर्णांक tipc_nl_name_table_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
bool tipc_nametbl_lookup_anycast(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
				 काष्ठा tipc_socket_addr *sk);
व्योम tipc_nametbl_lookup_mcast_sockets(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
				       bool exact, काष्ठा list_head *dports);
व्योम tipc_nametbl_lookup_mcast_nodes(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
				     काष्ठा tipc_nlist *nodes);
bool tipc_nametbl_lookup_group(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
			       काष्ठा list_head *dsts, पूर्णांक *dstcnt,
			       u32 exclude, bool mcast);
व्योम tipc_nametbl_build_group(काष्ठा net *net, काष्ठा tipc_group *grp,
			      काष्ठा tipc_uaddr *ua);
काष्ठा खुलाation *tipc_nametbl_publish(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
					 काष्ठा tipc_socket_addr *sk, u32 key);
व्योम tipc_nametbl_withdraw(काष्ठा net *net, काष्ठा tipc_uaddr *ua,
			   काष्ठा tipc_socket_addr *sk, u32 key);
काष्ठा खुलाation *tipc_nametbl_insert_publ(काष्ठा net *net,
					     काष्ठा tipc_uaddr *ua,
					     काष्ठा tipc_socket_addr *sk,
					     u32 key);
काष्ठा खुलाation *tipc_nametbl_हटाओ_publ(काष्ठा net *net,
					     काष्ठा tipc_uaddr *ua,
					     काष्ठा tipc_socket_addr *sk,
					     u32 key);
bool tipc_nametbl_subscribe(काष्ठा tipc_subscription *s);
व्योम tipc_nametbl_unsubscribe(काष्ठा tipc_subscription *s);
पूर्णांक tipc_nametbl_init(काष्ठा net *net);
व्योम tipc_nametbl_stop(काष्ठा net *net);

काष्ठा tipc_dest अणु
	काष्ठा list_head list;
	u32 port;
	u32 node;
पूर्ण;

काष्ठा tipc_dest *tipc_dest_find(काष्ठा list_head *l, u32 node, u32 port);
bool tipc_dest_push(काष्ठा list_head *l, u32 node, u32 port);
bool tipc_dest_pop(काष्ठा list_head *l, u32 *node, u32 *port);
bool tipc_dest_del(काष्ठा list_head *l, u32 node, u32 port);
व्योम tipc_dest_list_purge(काष्ठा list_head *l);
पूर्णांक tipc_dest_list_len(काष्ठा list_head *l);

#पूर्ण_अगर
