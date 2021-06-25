<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	common UDP/RAW code
 *	Linux INET implementation
 *
 * Authors:
 * 	Hideaki YOSHIFUJI <yoshfuji@linux-ipv6.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <net/ip.h>
#समावेश <net/sock.h>
#समावेश <net/route.h>
#समावेश <net/tcp_states.h>
#समावेश <net/sock_reuseport.h>

पूर्णांक __ip4_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sockaddr_in *usin = (काष्ठा sockaddr_in *) uaddr;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;
	__be32 saddr;
	पूर्णांक oअगर;
	पूर्णांक err;


	अगर (addr_len < माप(*usin))
		वापस -EINVAL;

	अगर (usin->sin_family != AF_INET)
		वापस -EAFNOSUPPORT;

	sk_dst_reset(sk);

	oअगर = sk->sk_bound_dev_अगर;
	saddr = inet->inet_saddr;
	अगर (ipv4_is_multicast(usin->sin_addr.s_addr)) अणु
		अगर (!oअगर || netअगर_index_is_l3_master(sock_net(sk), oअगर))
			oअगर = inet->mc_index;
		अगर (!saddr)
			saddr = inet->mc_addr;
	पूर्ण
	fl4 = &inet->cork.fl.u.ip4;
	rt = ip_route_connect(fl4, usin->sin_addr.s_addr, saddr,
			      RT_CONN_FLAGS(sk), oअगर,
			      sk->sk_protocol,
			      inet->inet_sport, usin->sin_port, sk);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		अगर (err == -ENETUNREACH)
			IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOROUTES);
		जाओ out;
	पूर्ण

	अगर ((rt->rt_flags & RTCF_BROADCAST) && !sock_flag(sk, SOCK_BROADCAST)) अणु
		ip_rt_put(rt);
		err = -EACCES;
		जाओ out;
	पूर्ण
	अगर (!inet->inet_saddr)
		inet->inet_saddr = fl4->saddr;	/* Update source address */
	अगर (!inet->inet_rcv_saddr) अणु
		inet->inet_rcv_saddr = fl4->saddr;
		अगर (sk->sk_prot->rehash)
			sk->sk_prot->rehash(sk);
	पूर्ण
	inet->inet_daddr = fl4->daddr;
	inet->inet_dport = usin->sin_port;
	reuseport_has_conns(sk, true);
	sk->sk_state = TCP_ESTABLISHED;
	sk_set_txhash(sk);
	inet->inet_id = pअक्रमom_u32();

	sk_dst_set(sk, &rt->dst);
	err = 0;
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(__ip4_datagram_connect);

पूर्णांक ip4_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	पूर्णांक res;

	lock_sock(sk);
	res = __ip4_datagram_connect(sk, uaddr, addr_len);
	release_sock(sk);
	वापस res;
पूर्ण
EXPORT_SYMBOL(ip4_datagram_connect);

/* Because UDP xmit path can manipulate sk_dst_cache without holding
 * socket lock, we need to use sk_dst_set() here,
 * even अगर we own the socket lock.
 */
व्योम ip4_datagram_release_cb(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा ip_options_rcu *inet_opt;
	__be32 daddr = inet->inet_daddr;
	काष्ठा dst_entry *dst;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;

	rcu_पढ़ो_lock();

	dst = __sk_dst_get(sk);
	अगर (!dst || !dst->obsolete || dst->ops->check(dst, 0)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	inet_opt = rcu_dereference(inet->inet_opt);
	अगर (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	rt = ip_route_output_ports(sock_net(sk), &fl4, sk, daddr,
				   inet->inet_saddr, inet->inet_dport,
				   inet->inet_sport, sk->sk_protocol,
				   RT_CONN_FLAGS(sk), sk->sk_bound_dev_अगर);

	dst = !IS_ERR(rt) ? &rt->dst : शून्य;
	sk_dst_set(sk, dst);

	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ip4_datagram_release_cb);
