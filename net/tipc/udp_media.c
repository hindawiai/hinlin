<शैली गुरु>
/* net/tipc/udp_media.c: IP bearer support क्रम TIPC
 *
 * Copyright (c) 2015, Ericsson AB
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

#समावेश <linux/socket.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <linux/tipc_netlink.h>
#समावेश "core.h"
#समावेश "addr.h"
#समावेश "net.h"
#समावेश "bearer.h"
#समावेश "netlink.h"
#समावेश "msg.h"
#समावेश "udp_media.h"

/* IANA asचिन्हित UDP port */
#घोषणा UDP_PORT_DEFAULT	6118

#घोषणा UDP_MIN_HEADROOM        48

/**
 * काष्ठा udp_media_addr - IP/UDP addressing inक्रमmation
 *
 * This is the bearer level originating address used in neighbor discovery
 * messages, and all fields should be in network byte order
 *
 * @proto: Ethernet protocol in use
 * @port: port being used
 * @ipv4: IPv4 address of neighbor
 * @ipv6: IPv6 address of neighbor
 */
काष्ठा udp_media_addr अणु
	__be16	proto;
	__be16	port;
	जोड़ अणु
		काष्ठा in_addr ipv4;
		काष्ठा in6_addr ipv6;
	पूर्ण;
पूर्ण;

/* काष्ठा udp_replicast - container क्रम UDP remote addresses */
काष्ठा udp_replicast अणु
	काष्ठा udp_media_addr addr;
	काष्ठा dst_cache dst_cache;
	काष्ठा rcu_head rcu;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा udp_bearer - ip/udp bearer data काष्ठाure
 * @bearer:	associated generic tipc bearer
 * @ubsock:	bearer associated socket
 * @अगरindex:	local address scope
 * @work:	used to schedule deferred work on a bearer
 * @rcast:	associated udp_replicast container
 */
काष्ठा udp_bearer अणु
	काष्ठा tipc_bearer __rcu *bearer;
	काष्ठा socket *ubsock;
	u32 अगरindex;
	काष्ठा work_काष्ठा work;
	काष्ठा udp_replicast rcast;
पूर्ण;

अटल पूर्णांक tipc_udp_is_mcast_addr(काष्ठा udp_media_addr *addr)
अणु
	अगर (ntohs(addr->proto) == ETH_P_IP)
		वापस ipv4_is_multicast(addr->ipv4.s_addr);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा
		वापस ipv6_addr_is_multicast(&addr->ipv6);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* udp_media_addr_set - convert a ip/udp address to a TIPC media address */
अटल व्योम tipc_udp_media_addr_set(काष्ठा tipc_media_addr *addr,
				    काष्ठा udp_media_addr *ua)
अणु
	स_रखो(addr, 0, माप(काष्ठा tipc_media_addr));
	addr->media_id = TIPC_MEDIA_TYPE_UDP;
	स_नकल(addr->value, ua, माप(काष्ठा udp_media_addr));

	अगर (tipc_udp_is_mcast_addr(ua))
		addr->broadcast = TIPC_BROADCAST_SUPPORT;
पूर्ण

/* tipc_udp_addr2str - convert ip/udp address to string */
अटल पूर्णांक tipc_udp_addr2str(काष्ठा tipc_media_addr *a, अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा udp_media_addr *ua = (काष्ठा udp_media_addr *)&a->value;

	अगर (ntohs(ua->proto) == ETH_P_IP)
		snम_लिखो(buf, size, "%pI4:%u", &ua->ipv4, ntohs(ua->port));
	अन्यथा अगर (ntohs(ua->proto) == ETH_P_IPV6)
		snम_लिखो(buf, size, "%pI6:%u", &ua->ipv6, ntohs(ua->port));
	अन्यथा
		pr_err("Invalid UDP media address\n");
	वापस 0;
पूर्ण

/* tipc_udp_msg2addr - extract an ip/udp address from a TIPC ndisc message */
अटल पूर्णांक tipc_udp_msg2addr(काष्ठा tipc_bearer *b, काष्ठा tipc_media_addr *a,
			     अक्षर *msg)
अणु
	काष्ठा udp_media_addr *ua;

	ua = (काष्ठा udp_media_addr *) (msg + TIPC_MEDIA_ADDR_OFFSET);
	अगर (msg[TIPC_MEDIA_TYPE_OFFSET] != TIPC_MEDIA_TYPE_UDP)
		वापस -EINVAL;
	tipc_udp_media_addr_set(a, ua);
	वापस 0;
पूर्ण

/* tipc_udp_addr2msg - ग_लिखो an ip/udp address to a TIPC ndisc message */
अटल पूर्णांक tipc_udp_addr2msg(अक्षर *msg, काष्ठा tipc_media_addr *a)
अणु
	स_रखो(msg, 0, TIPC_MEDIA_INFO_SIZE);
	msg[TIPC_MEDIA_TYPE_OFFSET] = TIPC_MEDIA_TYPE_UDP;
	स_नकल(msg + TIPC_MEDIA_ADDR_OFFSET, a->value,
	       माप(काष्ठा udp_media_addr));
	वापस 0;
पूर्ण

/* tipc_send_msg - enqueue a send request */
अटल पूर्णांक tipc_udp_xmit(काष्ठा net *net, काष्ठा sk_buff *skb,
			 काष्ठा udp_bearer *ub, काष्ठा udp_media_addr *src,
			 काष्ठा udp_media_addr *dst, काष्ठा dst_cache *cache)
अणु
	काष्ठा dst_entry *ndst;
	पूर्णांक ttl, err = 0;

	local_bh_disable();
	ndst = dst_cache_get(cache);
	अगर (dst->proto == htons(ETH_P_IP)) अणु
		काष्ठा rtable *rt = (काष्ठा rtable *)ndst;

		अगर (!rt) अणु
			काष्ठा flowi4 fl = अणु
				.daddr = dst->ipv4.s_addr,
				.saddr = src->ipv4.s_addr,
				.flowi4_mark = skb->mark,
				.flowi4_proto = IPPROTO_UDP
			पूर्ण;
			rt = ip_route_output_key(net, &fl);
			अगर (IS_ERR(rt)) अणु
				err = PTR_ERR(rt);
				जाओ tx_error;
			पूर्ण
			dst_cache_set_ip4(cache, &rt->dst, fl.saddr);
		पूर्ण

		ttl = ip4_dst_hoplimit(&rt->dst);
		udp_tunnel_xmit_skb(rt, ub->ubsock->sk, skb, src->ipv4.s_addr,
				    dst->ipv4.s_addr, 0, ttl, 0, src->port,
				    dst->port, false, true);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		अगर (!ndst) अणु
			काष्ठा flowi6 fl6 = अणु
				.flowi6_oअगर = ub->अगरindex,
				.daddr = dst->ipv6,
				.saddr = src->ipv6,
				.flowi6_proto = IPPROTO_UDP
			पूर्ण;
			ndst = ipv6_stub->ipv6_dst_lookup_flow(net,
							       ub->ubsock->sk,
							       &fl6, शून्य);
			अगर (IS_ERR(ndst)) अणु
				err = PTR_ERR(ndst);
				जाओ tx_error;
			पूर्ण
			dst_cache_set_ip6(cache, ndst, &fl6.saddr);
		पूर्ण
		ttl = ip6_dst_hoplimit(ndst);
		err = udp_tunnel6_xmit_skb(ndst, ub->ubsock->sk, skb, शून्य,
					   &src->ipv6, &dst->ipv6, 0, ttl, 0,
					   src->port, dst->port, false);
#पूर्ण_अगर
	पूर्ण
	local_bh_enable();
	वापस err;

tx_error:
	local_bh_enable();
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक tipc_udp_send_msg(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा tipc_bearer *b,
			     काष्ठा tipc_media_addr *addr)
अणु
	काष्ठा udp_media_addr *src = (काष्ठा udp_media_addr *)&b->addr.value;
	काष्ठा udp_media_addr *dst = (काष्ठा udp_media_addr *)&addr->value;
	काष्ठा udp_replicast *rcast;
	काष्ठा udp_bearer *ub;
	पूर्णांक err = 0;

	अगर (skb_headroom(skb) < UDP_MIN_HEADROOM) अणु
		err = pskb_expand_head(skb, UDP_MIN_HEADROOM, 0, GFP_ATOMIC);
		अगर (err)
			जाओ out;
	पूर्ण

	skb_set_inner_protocol(skb, htons(ETH_P_TIPC));
	ub = rcu_dereference(b->media_ptr);
	अगर (!ub) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (addr->broadcast != TIPC_REPLICAST_SUPPORT)
		वापस tipc_udp_xmit(net, skb, ub, src, dst,
				     &ub->rcast.dst_cache);

	/* Replicast, send an skb to each configured IP address */
	list_क्रम_each_entry_rcu(rcast, &ub->rcast.list, list) अणु
		काष्ठा sk_buff *_skb;

		_skb = pskb_copy(skb, GFP_ATOMIC);
		अगर (!_skb) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = tipc_udp_xmit(net, _skb, ub, src, &rcast->addr,
				    &rcast->dst_cache);
		अगर (err)
			जाओ out;
	पूर्ण
	err = 0;
out:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल bool tipc_udp_is_known_peer(काष्ठा tipc_bearer *b,
				   काष्ठा udp_media_addr *addr)
अणु
	काष्ठा udp_replicast *rcast, *पंचांगp;
	काष्ठा udp_bearer *ub;

	ub = rcu_dereference_rtnl(b->media_ptr);
	अगर (!ub) अणु
		pr_err_ratelimited("UDP bearer instance not found\n");
		वापस false;
	पूर्ण

	list_क्रम_each_entry_safe(rcast, पंचांगp, &ub->rcast.list, list) अणु
		अगर (!स_भेद(&rcast->addr, addr, माप(काष्ठा udp_media_addr)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tipc_udp_rcast_add(काष्ठा tipc_bearer *b,
			      काष्ठा udp_media_addr *addr)
अणु
	काष्ठा udp_replicast *rcast;
	काष्ठा udp_bearer *ub;

	ub = rcu_dereference_rtnl(b->media_ptr);
	अगर (!ub)
		वापस -ENODEV;

	rcast = kदो_स्मृति(माप(*rcast), GFP_ATOMIC);
	अगर (!rcast)
		वापस -ENOMEM;

	अगर (dst_cache_init(&rcast->dst_cache, GFP_ATOMIC)) अणु
		kमुक्त(rcast);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&rcast->addr, addr, माप(काष्ठा udp_media_addr));

	अगर (ntohs(addr->proto) == ETH_P_IP)
		pr_info("New replicast peer: %pI4\n", &rcast->addr.ipv4);
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (ntohs(addr->proto) == ETH_P_IPV6)
		pr_info("New replicast peer: %pI6\n", &rcast->addr.ipv6);
#पूर्ण_अगर
	b->bcast_addr.broadcast = TIPC_REPLICAST_SUPPORT;
	list_add_rcu(&rcast->list, &ub->rcast.list);
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_udp_rcast_disc(काष्ठा tipc_bearer *b, काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_media_addr src = अणु0पूर्ण;
	काष्ठा udp_media_addr *dst;

	dst = (काष्ठा udp_media_addr *)&b->bcast_addr.value;
	अगर (tipc_udp_is_mcast_addr(dst))
		वापस 0;

	src.port = udp_hdr(skb)->source;

	अगर (ip_hdr(skb)->version == 4) अणु
		काष्ठा iphdr *iphdr = ip_hdr(skb);

		src.proto = htons(ETH_P_IP);
		src.ipv4.s_addr = iphdr->saddr;
		अगर (ipv4_is_multicast(iphdr->daddr))
			वापस 0;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (ip_hdr(skb)->version == 6) अणु
		काष्ठा ipv6hdr *iphdr = ipv6_hdr(skb);

		src.proto = htons(ETH_P_IPV6);
		src.ipv6 = iphdr->saddr;
		अगर (ipv6_addr_is_multicast(&iphdr->daddr))
			वापस 0;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (likely(tipc_udp_is_known_peer(b, &src)))
		वापस 0;

	वापस tipc_udp_rcast_add(b, &src);
पूर्ण

/* tipc_udp_recv - पढ़ो data from bearer socket */
अटल पूर्णांक tipc_udp_recv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_bearer *ub;
	काष्ठा tipc_bearer *b;
	काष्ठा tipc_msg *hdr;
	पूर्णांक err;

	ub = rcu_dereference_sk_user_data(sk);
	अगर (!ub) अणु
		pr_err_ratelimited("Failed to get UDP bearer reference");
		जाओ out;
	पूर्ण
	skb_pull(skb, माप(काष्ठा udphdr));
	hdr = buf_msg(skb);

	b = rcu_dereference(ub->bearer);
	अगर (!b)
		जाओ out;

	अगर (b && test_bit(0, &b->up)) अणु
		TIPC_SKB_CB(skb)->flags = 0;
		tipc_rcv(sock_net(sk), skb, b);
		वापस 0;
	पूर्ण

	अगर (unlikely(msg_user(hdr) == LINK_CONFIG)) अणु
		err = tipc_udp_rcast_disc(b, skb);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक enable_mcast(काष्ठा udp_bearer *ub, काष्ठा udp_media_addr *remote)
अणु
	पूर्णांक err = 0;
	काष्ठा ip_mreqn mreqn;
	काष्ठा sock *sk = ub->ubsock->sk;

	अगर (ntohs(remote->proto) == ETH_P_IP) अणु
		mreqn.imr_multiaddr = remote->ipv4;
		mreqn.imr_अगरindex = ub->अगरindex;
		err = ip_mc_join_group(sk, &mreqn);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		lock_sock(sk);
		err = ipv6_stub->ipv6_sock_mc_join(sk, ub->अगरindex,
						   &remote->ipv6);
		release_sock(sk);
#पूर्ण_अगर
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __tipc_nl_add_udp_addr(काष्ठा sk_buff *skb,
				  काष्ठा udp_media_addr *addr, पूर्णांक nla_t)
अणु
	अगर (ntohs(addr->proto) == ETH_P_IP) अणु
		काष्ठा sockaddr_in ip4;

		स_रखो(&ip4, 0, माप(ip4));
		ip4.sin_family = AF_INET;
		ip4.sin_port = addr->port;
		ip4.sin_addr.s_addr = addr->ipv4.s_addr;
		अगर (nla_put(skb, nla_t, माप(ip4), &ip4))
			वापस -EMSGSIZE;

#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (ntohs(addr->proto) == ETH_P_IPV6) अणु
		काष्ठा sockaddr_in6 ip6;

		स_रखो(&ip6, 0, माप(ip6));
		ip6.sin6_family = AF_INET6;
		ip6.sin6_port  = addr->port;
		स_नकल(&ip6.sin6_addr, &addr->ipv6, माप(काष्ठा in6_addr));
		अगर (nla_put(skb, nla_t, माप(ip6), &ip6))
			वापस -EMSGSIZE;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tipc_udp_nl_dump_remoteip(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	u32 bid = cb->args[0];
	u32 skip_cnt = cb->args[1];
	u32 portid = NETLINK_CB(cb->skb).portid;
	काष्ठा udp_replicast *rcast, *पंचांगp;
	काष्ठा tipc_bearer *b;
	काष्ठा udp_bearer *ub;
	व्योम *hdr;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!bid && !skip_cnt) अणु
		काष्ठा nlattr **attrs = genl_dumpit_info(cb)->attrs;
		काष्ठा net *net = sock_net(skb->sk);
		काष्ठा nlattr *battrs[TIPC_NLA_BEARER_MAX + 1];
		अक्षर *bname;

		अगर (!attrs[TIPC_NLA_BEARER])
			वापस -EINVAL;

		err = nla_parse_nested_deprecated(battrs, TIPC_NLA_BEARER_MAX,
						  attrs[TIPC_NLA_BEARER],
						  tipc_nl_bearer_policy, शून्य);
		अगर (err)
			वापस err;

		अगर (!battrs[TIPC_NLA_BEARER_NAME])
			वापस -EINVAL;

		bname = nla_data(battrs[TIPC_NLA_BEARER_NAME]);

		rtnl_lock();
		b = tipc_bearer_find(net, bname);
		अगर (!b) अणु
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण
		bid = b->identity;
	पूर्ण अन्यथा अणु
		काष्ठा net *net = sock_net(skb->sk);
		काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);

		rtnl_lock();
		b = rtnl_dereference(tn->bearer_list[bid]);
		अगर (!b) अणु
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ub = rtnl_dereference(b->media_ptr);
	अगर (!ub) अणु
		rtnl_unlock();
		वापस -EINVAL;
	पूर्ण

	i = 0;
	list_क्रम_each_entry_safe(rcast, पंचांगp, &ub->rcast.list, list) अणु
		अगर (i < skip_cnt)
			जाओ count;

		hdr = genlmsg_put(skb, portid, cb->nlh->nlmsg_seq,
				  &tipc_genl_family, NLM_F_MULTI,
				  TIPC_NL_BEARER_GET);
		अगर (!hdr)
			जाओ करोne;

		err = __tipc_nl_add_udp_addr(skb, &rcast->addr,
					     TIPC_NLA_UDP_REMOTE);
		अगर (err) अणु
			genlmsg_cancel(skb, hdr);
			जाओ करोne;
		पूर्ण
		genlmsg_end(skb, hdr);
count:
		i++;
	पूर्ण
करोne:
	rtnl_unlock();
	cb->args[0] = bid;
	cb->args[1] = i;

	वापस skb->len;
पूर्ण

पूर्णांक tipc_udp_nl_add_bearer_data(काष्ठा tipc_nl_msg *msg, काष्ठा tipc_bearer *b)
अणु
	काष्ठा udp_media_addr *src = (काष्ठा udp_media_addr *)&b->addr.value;
	काष्ठा udp_media_addr *dst;
	काष्ठा udp_bearer *ub;
	काष्ठा nlattr *nest;

	ub = rtnl_dereference(b->media_ptr);
	अगर (!ub)
		वापस -ENODEV;

	nest = nla_nest_start_noflag(msg->skb, TIPC_NLA_BEARER_UDP_OPTS);
	अगर (!nest)
		जाओ msg_full;

	अगर (__tipc_nl_add_udp_addr(msg->skb, src, TIPC_NLA_UDP_LOCAL))
		जाओ msg_full;

	dst = (काष्ठा udp_media_addr *)&b->bcast_addr.value;
	अगर (__tipc_nl_add_udp_addr(msg->skb, dst, TIPC_NLA_UDP_REMOTE))
		जाओ msg_full;

	अगर (!list_empty(&ub->rcast.list)) अणु
		अगर (nla_put_flag(msg->skb, TIPC_NLA_UDP_MULTI_REMOTEIP))
			जाओ msg_full;
	पूर्ण

	nla_nest_end(msg->skb, nest);
	वापस 0;
msg_full:
	nla_nest_cancel(msg->skb, nest);
	वापस -EMSGSIZE;
पूर्ण

/**
 * tipc_parse_udp_addr - build udp media address from netlink data
 * @nla:	netlink attribute containing sockaddr storage aligned address
 * @addr:	tipc media address to fill with address, port and protocol type
 * @scope_id:	IPv6 scope id poपूर्णांकer, not शून्य indicates it's required
 */

अटल पूर्णांक tipc_parse_udp_addr(काष्ठा nlattr *nla, काष्ठा udp_media_addr *addr,
			       u32 *scope_id)
अणु
	काष्ठा sockaddr_storage sa;

	nla_स_नकल(&sa, nla, माप(sa));
	अगर (sa.ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *ip4 = (काष्ठा sockaddr_in *)&sa;

		addr->proto = htons(ETH_P_IP);
		addr->port = ip4->sin_port;
		addr->ipv4.s_addr = ip4->sin_addr.s_addr;
		वापस 0;

#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (sa.ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *ip6 = (काष्ठा sockaddr_in6 *)&sa;

		addr->proto = htons(ETH_P_IPV6);
		addr->port = ip6->sin6_port;
		स_नकल(&addr->ipv6, &ip6->sin6_addr, माप(काष्ठा in6_addr));

		/* Scope ID is only पूर्णांकeresting क्रम local addresses */
		अगर (scope_id) अणु
			पूर्णांक atype;

			atype = ipv6_addr_type(&ip6->sin6_addr);
			अगर (__ipv6_addr_needs_scope_id(atype) &&
			    !ip6->sin6_scope_id) अणु
				वापस -EINVAL;
			पूर्ण

			*scope_id = ip6->sin6_scope_id ? : 0;
		पूर्ण

		वापस 0;
#पूर्ण_अगर
	पूर्ण
	वापस -EADDRNOTAVAIL;
पूर्ण

पूर्णांक tipc_udp_nl_bearer_add(काष्ठा tipc_bearer *b, काष्ठा nlattr *attr)
अणु
	पूर्णांक err;
	काष्ठा udp_media_addr addr = अणु0पूर्ण;
	काष्ठा nlattr *opts[TIPC_NLA_UDP_MAX + 1];
	काष्ठा udp_media_addr *dst;

	अगर (nla_parse_nested_deprecated(opts, TIPC_NLA_UDP_MAX, attr, tipc_nl_udp_policy, शून्य))
		वापस -EINVAL;

	अगर (!opts[TIPC_NLA_UDP_REMOTE])
		वापस -EINVAL;

	err = tipc_parse_udp_addr(opts[TIPC_NLA_UDP_REMOTE], &addr, शून्य);
	अगर (err)
		वापस err;

	dst = (काष्ठा udp_media_addr *)&b->bcast_addr.value;
	अगर (tipc_udp_is_mcast_addr(dst)) अणु
		pr_err("Can't add remote ip to TIPC UDP multicast bearer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (tipc_udp_is_known_peer(b, &addr))
		वापस 0;

	वापस tipc_udp_rcast_add(b, &addr);
पूर्ण

/**
 * tipc_udp_enable - callback to create a new udp bearer instance
 * @net:	network namespace
 * @b:		poपूर्णांकer to generic tipc_bearer
 * @attrs:	netlink bearer configuration
 *
 * validate the bearer parameters and initialize the udp bearer
 * rtnl_lock should be held
 */
अटल पूर्णांक tipc_udp_enable(काष्ठा net *net, काष्ठा tipc_bearer *b,
			   काष्ठा nlattr *attrs[])
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा udp_bearer *ub;
	काष्ठा udp_media_addr remote = अणु0पूर्ण;
	काष्ठा udp_media_addr local = अणु0पूर्ण;
	काष्ठा udp_port_cfg udp_conf = अणु0पूर्ण;
	काष्ठा udp_tunnel_sock_cfg tuncfg = अणुशून्यपूर्ण;
	काष्ठा nlattr *opts[TIPC_NLA_UDP_MAX + 1];
	u8 node_id[NODE_ID_LEN] = अणु0,पूर्ण;
	काष्ठा net_device *dev;
	पूर्णांक rmcast = 0;

	ub = kzalloc(माप(*ub), GFP_ATOMIC);
	अगर (!ub)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ub->rcast.list);

	अगर (!attrs[TIPC_NLA_BEARER_UDP_OPTS])
		जाओ err;

	अगर (nla_parse_nested_deprecated(opts, TIPC_NLA_UDP_MAX, attrs[TIPC_NLA_BEARER_UDP_OPTS], tipc_nl_udp_policy, शून्य))
		जाओ err;

	अगर (!opts[TIPC_NLA_UDP_LOCAL] || !opts[TIPC_NLA_UDP_REMOTE]) अणु
		pr_err("Invalid UDP bearer configuration");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = tipc_parse_udp_addr(opts[TIPC_NLA_UDP_LOCAL], &local,
				  &ub->अगरindex);
	अगर (err)
		जाओ err;

	err = tipc_parse_udp_addr(opts[TIPC_NLA_UDP_REMOTE], &remote, शून्य);
	अगर (err)
		जाओ err;

	अगर (remote.proto != local.proto) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/* Checking remote ip address */
	rmcast = tipc_udp_is_mcast_addr(&remote);

	/* Autoconfigure own node identity अगर needed */
	अगर (!tipc_own_id(net)) अणु
		स_नकल(node_id, local.ipv6.in6_u.u6_addr8, 16);
		tipc_net_init(net, node_id, 0);
	पूर्ण
	अगर (!tipc_own_id(net)) अणु
		pr_warn("Failed to set node id, please configure manually\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	b->bcast_addr.media_id = TIPC_MEDIA_TYPE_UDP;
	b->bcast_addr.broadcast = TIPC_BROADCAST_SUPPORT;
	rcu_assign_poपूर्णांकer(b->media_ptr, ub);
	rcu_assign_poपूर्णांकer(ub->bearer, b);
	tipc_udp_media_addr_set(&b->addr, &local);
	अगर (local.proto == htons(ETH_P_IP)) अणु
		dev = __ip_dev_find(net, local.ipv4.s_addr, false);
		अगर (!dev) अणु
			err = -ENODEV;
			जाओ err;
		पूर्ण
		udp_conf.family = AF_INET;

		/* Switch to use ANY to receive packets from group */
		अगर (rmcast)
			udp_conf.local_ip.s_addr = htonl(INADDR_ANY);
		अन्यथा
			udp_conf.local_ip.s_addr = local.ipv4.s_addr;
		udp_conf.use_udp_checksums = false;
		ub->अगरindex = dev->अगरindex;
		अगर (tipc_mtu_bad(dev, माप(काष्ठा iphdr) +
				      माप(काष्ठा udphdr))) अणु
			err = -EINVAL;
			जाओ err;
		पूर्ण
		b->mtu = b->media->mtu;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (local.proto == htons(ETH_P_IPV6)) अणु
		dev = ub->अगरindex ? __dev_get_by_index(net, ub->अगरindex) : शून्य;
		dev = ipv6_dev_find(net, &local.ipv6, dev);
		अगर (!dev) अणु
			err = -ENODEV;
			जाओ err;
		पूर्ण
		udp_conf.family = AF_INET6;
		udp_conf.use_udp6_tx_checksums = true;
		udp_conf.use_udp6_rx_checksums = true;
		अगर (rmcast)
			udp_conf.local_ip6 = in6addr_any;
		अन्यथा
			udp_conf.local_ip6 = local.ipv6;
		ub->अगरindex = dev->अगरindex;
		b->mtu = 1280;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		err = -EAFNOSUPPORT;
		जाओ err;
	पूर्ण
	udp_conf.local_udp_port = local.port;
	err = udp_sock_create(net, &udp_conf, &ub->ubsock);
	अगर (err)
		जाओ err;
	tuncfg.sk_user_data = ub;
	tuncfg.encap_type = 1;
	tuncfg.encap_rcv = tipc_udp_recv;
	tuncfg.encap_destroy = शून्य;
	setup_udp_tunnel_sock(net, ub->ubsock, &tuncfg);

	err = dst_cache_init(&ub->rcast.dst_cache, GFP_ATOMIC);
	अगर (err)
		जाओ मुक्त;

	/*
	 * The bcast media address port is used क्रम all peers and the ip
	 * is used अगर it's a multicast address.
	 */
	स_नकल(&b->bcast_addr.value, &remote, माप(remote));
	अगर (rmcast)
		err = enable_mcast(ub, &remote);
	अन्यथा
		err = tipc_udp_rcast_add(b, &remote);
	अगर (err)
		जाओ मुक्त;

	वापस 0;

मुक्त:
	dst_cache_destroy(&ub->rcast.dst_cache);
	udp_tunnel_sock_release(ub->ubsock);
err:
	kमुक्त(ub);
	वापस err;
पूर्ण

/* cleanup_bearer - अवरोध the socket/bearer association */
अटल व्योम cleanup_bearer(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा udp_bearer *ub = container_of(work, काष्ठा udp_bearer, work);
	काष्ठा udp_replicast *rcast, *पंचांगp;

	list_क्रम_each_entry_safe(rcast, पंचांगp, &ub->rcast.list, list) अणु
		dst_cache_destroy(&rcast->dst_cache);
		list_del_rcu(&rcast->list);
		kमुक्त_rcu(rcast, rcu);
	पूर्ण

	atomic_dec(&tipc_net(sock_net(ub->ubsock->sk))->wq_count);
	dst_cache_destroy(&ub->rcast.dst_cache);
	udp_tunnel_sock_release(ub->ubsock);
	synchronize_net();
	kमुक्त(ub);
पूर्ण

/* tipc_udp_disable - detach bearer from socket */
अटल व्योम tipc_udp_disable(काष्ठा tipc_bearer *b)
अणु
	काष्ठा udp_bearer *ub;

	ub = rtnl_dereference(b->media_ptr);
	अगर (!ub) अणु
		pr_err("UDP bearer instance not found\n");
		वापस;
	पूर्ण
	sock_set_flag(ub->ubsock->sk, SOCK_DEAD);
	RCU_INIT_POINTER(ub->bearer, शून्य);

	/* sock_release need to be करोne outside of rtnl lock */
	atomic_inc(&tipc_net(sock_net(ub->ubsock->sk))->wq_count);
	INIT_WORK(&ub->work, cleanup_bearer);
	schedule_work(&ub->work);
पूर्ण

काष्ठा tipc_media udp_media_info = अणु
	.send_msg	= tipc_udp_send_msg,
	.enable_media	= tipc_udp_enable,
	.disable_media	= tipc_udp_disable,
	.addr2str	= tipc_udp_addr2str,
	.addr2msg	= tipc_udp_addr2msg,
	.msg2addr	= tipc_udp_msg2addr,
	.priority	= TIPC_DEF_LINK_PRI,
	.tolerance	= TIPC_DEF_LINK_TOL,
	.min_win	= TIPC_DEF_LINK_WIN,
	.max_win	= TIPC_DEF_LINK_WIN,
	.mtu		= TIPC_DEF_LINK_UDP_MTU,
	.type_id	= TIPC_MEDIA_TYPE_UDP,
	.hwaddr_len	= 0,
	.name		= "udp"
पूर्ण;
