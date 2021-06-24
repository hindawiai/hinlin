<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET        An implementation of the TCP/IP protocol suite क्रम the LINUX
 *             operating प्रणाली.  INET is implemented using the  BSD Socket
 *             पूर्णांकerface as the means of communication with the user level.
 *
 *             Support क्रम INET6 connection oriented protocols.
 *
 * Authors:    See the TCPv6 sources
 */

#समावेश <linux/module.h>
#समावेश <linux/in6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>

#समावेश <net/addrconf.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/ip6_route.h>
#समावेश <net/sock.h>
#समावेश <net/inet6_connection_sock.h>
#समावेश <net/sock_reuseport.h>

काष्ठा dst_entry *inet6_csk_route_req(स्थिर काष्ठा sock *sk,
				      काष्ठा flowi6 *fl6,
				      स्थिर काष्ठा request_sock *req,
				      u8 proto)
अणु
	काष्ठा inet_request_sock *ireq = inet_rsk(req);
	स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा in6_addr *final_p, final;
	काष्ठा dst_entry *dst;

	स_रखो(fl6, 0, माप(*fl6));
	fl6->flowi6_proto = proto;
	fl6->daddr = ireq->ir_v6_rmt_addr;
	rcu_पढ़ो_lock();
	final_p = fl6_update_dst(fl6, rcu_dereference(np->opt), &final);
	rcu_पढ़ो_unlock();
	fl6->saddr = ireq->ir_v6_loc_addr;
	fl6->flowi6_oअगर = ireq->ir_iअगर;
	fl6->flowi6_mark = ireq->ir_mark;
	fl6->fl6_dport = ireq->ir_rmt_port;
	fl6->fl6_sport = htons(ireq->ir_num);
	fl6->flowi6_uid = sk->sk_uid;
	security_req_classअगरy_flow(req, flowi6_to_flowi_common(fl6));

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, fl6, final_p);
	अगर (IS_ERR(dst))
		वापस शून्य;

	वापस dst;
पूर्ण
EXPORT_SYMBOL(inet6_csk_route_req);

व्योम inet6_csk_addr2sockaddr(काष्ठा sock *sk, काष्ठा sockaddr *uaddr)
अणु
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *) uaddr;

	sin6->sin6_family = AF_INET6;
	sin6->sin6_addr = sk->sk_v6_daddr;
	sin6->sin6_port	= inet_sk(sk)->inet_dport;
	/* We करो not store received flowlabel क्रम TCP */
	sin6->sin6_flowinfo = 0;
	sin6->sin6_scope_id = ipv6_अगरace_scope_id(&sin6->sin6_addr,
						  sk->sk_bound_dev_अगर);
पूर्ण
EXPORT_SYMBOL_GPL(inet6_csk_addr2sockaddr);

अटल अंतरभूत
काष्ठा dst_entry *__inet6_csk_dst_check(काष्ठा sock *sk, u32 cookie)
अणु
	वापस __sk_dst_check(sk, cookie);
पूर्ण

अटल काष्ठा dst_entry *inet6_csk_route_socket(काष्ठा sock *sk,
						काष्ठा flowi6 *fl6)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा in6_addr *final_p, final;
	काष्ठा dst_entry *dst;

	स_रखो(fl6, 0, माप(*fl6));
	fl6->flowi6_proto = sk->sk_protocol;
	fl6->daddr = sk->sk_v6_daddr;
	fl6->saddr = np->saddr;
	fl6->flowlabel = np->flow_label;
	IP6_ECN_flow_xmit(sk, fl6->flowlabel);
	fl6->flowi6_oअगर = sk->sk_bound_dev_अगर;
	fl6->flowi6_mark = sk->sk_mark;
	fl6->fl6_sport = inet->inet_sport;
	fl6->fl6_dport = inet->inet_dport;
	fl6->flowi6_uid = sk->sk_uid;
	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(fl6));

	rcu_पढ़ो_lock();
	final_p = fl6_update_dst(fl6, rcu_dereference(np->opt), &final);
	rcu_पढ़ो_unlock();

	dst = __inet6_csk_dst_check(sk, np->dst_cookie);
	अगर (!dst) अणु
		dst = ip6_dst_lookup_flow(sock_net(sk), sk, fl6, final_p);

		अगर (!IS_ERR(dst))
			ip6_dst_store(sk, dst, शून्य, शून्य);
	पूर्ण
	वापस dst;
पूर्ण

पूर्णांक inet6_csk_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl_unused)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;
	पूर्णांक res;

	dst = inet6_csk_route_socket(sk, &fl6);
	अगर (IS_ERR(dst)) अणु
		sk->sk_err_soft = -PTR_ERR(dst);
		sk->sk_route_caps = 0;
		kमुक्त_skb(skb);
		वापस PTR_ERR(dst);
	पूर्ण

	rcu_पढ़ो_lock();
	skb_dst_set_noref(skb, dst);

	/* Restore final destination back after routing करोne */
	fl6.daddr = sk->sk_v6_daddr;

	res = ip6_xmit(sk, skb, &fl6, sk->sk_mark, rcu_dereference(np->opt),
		       np->tclass,  sk->sk_priority);
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(inet6_csk_xmit);

काष्ठा dst_entry *inet6_csk_update_pmtu(काष्ठा sock *sk, u32 mtu)
अणु
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst = inet6_csk_route_socket(sk, &fl6);

	अगर (IS_ERR(dst))
		वापस शून्य;
	dst->ops->update_pmtu(dst, sk, शून्य, mtu, true);

	dst = inet6_csk_route_socket(sk, &fl6);
	वापस IS_ERR(dst) ? शून्य : dst;
पूर्ण
EXPORT_SYMBOL_GPL(inet6_csk_update_pmtu);
