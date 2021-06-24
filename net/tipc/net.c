<शैली गुरु>
/*
 * net/tipc/net.c: TIPC network routing code
 *
 * Copyright (c) 1995-2006, 2014, Ericsson AB
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

#समावेश "core.h"
#समावेश "net.h"
#समावेश "name_distr.h"
#समावेश "subscr.h"
#समावेश "socket.h"
#समावेश "node.h"
#समावेश "bcast.h"
#समावेश "link.h"
#समावेश "netlink.h"
#समावेश "monitor.h"

/*
 * The TIPC locking policy is deचिन्हित to ensure a very fine locking
 * granularity, permitting complete parallel access to inभागidual
 * port and node/link instances. The code consists of four major
 * locking करोमुख्यs, each रक्षित with their own disjunct set of locks.
 *
 * 1: The bearer level.
 *    RTNL lock is used to serialize the process of configuring bearer
 *    on update side, and RCU lock is applied on पढ़ो side to make
 *    bearer instance valid on both paths of message transmission and
 *    reception.
 *
 * 2: The node and link level.
 *    All node instances are saved पूर्णांकo two tipc_node_list and node_htable
 *    lists. The two lists are रक्षित by node_list_lock on ग_लिखो side,
 *    and they are guarded with RCU lock on पढ़ो side. Especially node
 *    instance is destroyed only when TIPC module is हटाओd, and we can
 *    confirm that there has no any user who is accessing the node at the
 *    moment. Thereक्रमe, Except क्रम iterating the two lists within RCU
 *    protection, it's no needed to hold RCU that we access node instance
 *    in other places.
 *
 *    In addition, all members in node काष्ठाure including link instances
 *    are रक्षित by node spin lock.
 *
 * 3: The transport level of the protocol.
 *    This consists of the काष्ठाures port, (and its user level
 *    representations, such as user_port and tipc_sock), reference and
 *    tipc_user (port.c, reg.c, socket.c).
 *
 *    This layer has four dअगरferent locks:
 *     - The tipc_port spin_lock. This is protecting each port instance
 *       from parallel data access and removal. Since we can not place
 *       this lock in the port itself, it has been placed in the
 *       corresponding reference table entry, which has the same lअगरe
 *       cycle as the module. This entry is dअगरficult to access from
 *       outside the TIPC core, however, so a poपूर्णांकer to the lock has
 *       been added in the port instance, -to be used क्रम unlocking
 *       only.
 *     - A पढ़ो/ग_लिखो lock to protect the reference table itself (teg.c).
 *       (Nobody is using पढ़ो-only access to this, so it can just as
 *       well be changed to a spin_lock)
 *     - A spin lock to protect the registry of kernel/driver users (reg.c)
 *     - A global spin_lock (tipc_port_lock), which only task is to ensure
 *       consistency where more than one port is involved in an operation,
 *       i.e., when a port is part of a linked list of ports.
 *       There are two such lists; 'port_list', which is used क्रम management,
 *       and 'wait_list', which is used to queue ports during congestion.
 *
 *  4: The name table (name_table.c, name_distr.c, subscription.c)
 *     - There is one big पढ़ो/ग_लिखो-lock (tipc_nametbl_lock) protecting the
 *       overall name table काष्ठाure. Nothing must be added/हटाओd to
 *       this काष्ठाure without holding ग_लिखो access to it.
 *     - There is one local spin_lock per sub_sequence, which can be seen
 *       as a sub-करोमुख्य to the tipc_nametbl_lock करोमुख्य. It is used only
 *       क्रम translation operations, and is needed because a translation
 *       steps the root of the 'publication' linked list between each lookup.
 *       This is always used within the scope of a tipc_nametbl_lock(पढ़ो).
 *     - A local spin_lock protecting the queue of subscriber events.
*/

अटल व्योम tipc_net_finalize(काष्ठा net *net, u32 addr);

पूर्णांक tipc_net_init(काष्ठा net *net, u8 *node_id, u32 addr)
अणु
	अगर (tipc_own_id(net)) अणु
		pr_info("Cannot configure node identity twice\n");
		वापस -1;
	पूर्ण
	pr_info("Started in network mode\n");

	अगर (node_id)
		tipc_set_node_id(net, node_id);
	अगर (addr)
		tipc_net_finalize(net, addr);
	वापस 0;
पूर्ण

अटल व्योम tipc_net_finalize(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_socket_addr sk = अणु0, addrपूर्ण;
	काष्ठा tipc_uaddr ua;

	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, TIPC_CLUSTER_SCOPE,
		   TIPC_NODE_STATE, addr, addr);

	अगर (cmpxchg(&tn->node_addr, 0, addr))
		वापस;
	tipc_set_node_addr(net, addr);
	tipc_named_reinit(net);
	tipc_sk_reinit(net);
	tipc_mon_reinit_self(net);
	tipc_nametbl_publish(net, &ua, &sk, addr);
पूर्ण

व्योम tipc_net_finalize_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tipc_net *tn = container_of(work, काष्ठा tipc_net, work);

	tipc_net_finalize(tipc_link_net(tn->bcl), tn->trial_addr);
पूर्ण

व्योम tipc_net_stop(काष्ठा net *net)
अणु
	अगर (!tipc_own_id(net))
		वापस;

	rtnl_lock();
	tipc_bearer_stop(net);
	tipc_node_stop(net);
	rtnl_unlock();

	pr_info("Left network mode\n");
पूर्ण

अटल पूर्णांक __tipc_nl_add_net(काष्ठा net *net, काष्ठा tipc_nl_msg *msg)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	u64 *w0 = (u64 *)&tn->node_id[0];
	u64 *w1 = (u64 *)&tn->node_id[8];
	काष्ठा nlattr *attrs;
	व्योम *hdr;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_NET_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_NET);
	अगर (!attrs)
		जाओ msg_full;

	अगर (nla_put_u32(msg->skb, TIPC_NLA_NET_ID, tn->net_id))
		जाओ attr_msg_full;
	अगर (nla_put_u64_64bit(msg->skb, TIPC_NLA_NET_NODEID, *w0, 0))
		जाओ attr_msg_full;
	अगर (nla_put_u64_64bit(msg->skb, TIPC_NLA_NET_NODEID_W1, *w1, 0))
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

पूर्णांक tipc_nl_net_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक err;
	पूर्णांक करोne = cb->args[0];
	काष्ठा tipc_nl_msg msg;

	अगर (करोne)
		वापस 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	err = __tipc_nl_add_net(net, &msg);
	अगर (err)
		जाओ out;

	करोne = 1;
out:
	cb->args[0] = करोne;

	वापस skb->len;
पूर्ण

पूर्णांक __tipc_nl_net_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attrs[TIPC_NLA_NET_MAX + 1];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_net *tn = tipc_net(net);
	पूर्णांक err;

	अगर (!info->attrs[TIPC_NLA_NET])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_NET_MAX,
					  info->attrs[TIPC_NLA_NET],
					  tipc_nl_net_policy, info->extack);

	अगर (err)
		वापस err;

	/* Can't change net id once TIPC has joined a network */
	अगर (tipc_own_addr(net))
		वापस -EPERM;

	अगर (attrs[TIPC_NLA_NET_ID]) अणु
		u32 val;

		val = nla_get_u32(attrs[TIPC_NLA_NET_ID]);
		अगर (val < 1 || val > 9999)
			वापस -EINVAL;

		tn->net_id = val;
	पूर्ण

	अगर (attrs[TIPC_NLA_NET_ADDR]) अणु
		u32 addr;

		addr = nla_get_u32(attrs[TIPC_NLA_NET_ADDR]);
		अगर (!addr)
			वापस -EINVAL;
		tn->legacy_addr_क्रमmat = true;
		tipc_net_init(net, शून्य, addr);
	पूर्ण

	अगर (attrs[TIPC_NLA_NET_NODEID]) अणु
		u8 node_id[NODE_ID_LEN];
		u64 *w0 = (u64 *)&node_id[0];
		u64 *w1 = (u64 *)&node_id[8];

		अगर (!attrs[TIPC_NLA_NET_NODEID_W1])
			वापस -EINVAL;
		*w0 = nla_get_u64(attrs[TIPC_NLA_NET_NODEID]);
		*w1 = nla_get_u64(attrs[TIPC_NLA_NET_NODEID_W1]);
		tipc_net_init(net, node_id, 0);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक tipc_nl_net_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = __tipc_nl_net_set(skb, info);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक __tipc_nl_addr_legacy_get(काष्ठा net *net, काष्ठा tipc_nl_msg *msg)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा nlattr *attrs;
	व्योम *hdr;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  0, TIPC_NL_ADDR_LEGACY_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start(msg->skb, TIPC_NLA_NET);
	अगर (!attrs)
		जाओ msg_full;

	अगर (tn->legacy_addr_क्रमmat)
		अगर (nla_put_flag(msg->skb, TIPC_NLA_NET_ADDR_LEGACY))
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

पूर्णांक tipc_nl_net_addr_legacy_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_nl_msg msg;
	काष्ठा sk_buff *rep;
	पूर्णांक err;

	rep = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	msg.skb = rep;
	msg.portid = info->snd_portid;
	msg.seq = info->snd_seq;

	err = __tipc_nl_addr_legacy_get(net, &msg);
	अगर (err) अणु
		nlmsg_मुक्त(msg.skb);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg.skb, info);
पूर्ण
