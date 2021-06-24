<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		"Ping" sockets
 *
 * Based on ipv4/ping.c code.
 *
 * Authors:	Lorenzo Colitti (IPv6 support)
 *		Vasiliy Kulikov / Openwall (IPv4 implementation, क्रम Linux 2.6),
 *		Pavel Kankovsky (IPv4 implementation, क्रम Linux 2.4.32)
 */

#समावेश <net/addrconf.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/protocol.h>
#समावेश <net/udp.h>
#समावेश <net/transp_v6.h>
#समावेश <linux/proc_fs.h>
#समावेश <net/ping.h>

/* Compatibility glue so we can support IPv6 when it's compiled as a module */
अटल पूर्णांक dummy_ipv6_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
				 पूर्णांक *addr_len)
अणु
	वापस -EAFNOSUPPORT;
पूर्ण
अटल व्योम dummy_ip6_datagram_recv_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
				       काष्ठा sk_buff *skb)
अणु
पूर्ण
अटल पूर्णांक dummy_icmpv6_err_convert(u8 type, u8 code, पूर्णांक *err)
अणु
	वापस -EAFNOSUPPORT;
पूर्ण
अटल व्योम dummy_ipv6_icmp_error(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err,
				  __be16 port, u32 info, u8 *payload) अणुपूर्ण
अटल पूर्णांक dummy_ipv6_chk_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			       स्थिर काष्ठा net_device *dev, पूर्णांक strict)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ping_v6_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा icmp6hdr user_icmph;
	पूर्णांक addr_type;
	काष्ठा in6_addr *daddr;
	पूर्णांक oअगर = 0;
	काष्ठा flowi6 fl6;
	पूर्णांक err;
	काष्ठा dst_entry *dst;
	काष्ठा rt6_info *rt;
	काष्ठा pingfakehdr pfh;
	काष्ठा ipcm6_cookie ipc6;

	pr_debug("ping_v6_sendmsg(sk=%p,sk->num=%u)\n", inet, inet->inet_num);

	err = ping_common_sendmsg(AF_INET6, msg, len, &user_icmph,
				  माप(user_icmph));
	अगर (err)
		वापस err;

	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, u, msg->msg_name);
		अगर (msg->msg_namelen < माप(*u))
			वापस -EINVAL;
		अगर (u->sin6_family != AF_INET6) अणु
			वापस -EAFNOSUPPORT;
		पूर्ण
		daddr = &(u->sin6_addr);
		अगर (__ipv6_addr_needs_scope_id(ipv6_addr_type(daddr)))
			oअगर = u->sin6_scope_id;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;
		daddr = &sk->sk_v6_daddr;
	पूर्ण

	अगर (!oअगर)
		oअगर = sk->sk_bound_dev_अगर;

	अगर (!oअगर)
		oअगर = np->sticky_pktinfo.ipi6_अगरindex;

	अगर (!oअगर && ipv6_addr_is_multicast(daddr))
		oअगर = np->mcast_oअगर;
	अन्यथा अगर (!oअगर)
		oअगर = np->ucast_oअगर;

	addr_type = ipv6_addr_type(daddr);
	अगर ((__ipv6_addr_needs_scope_id(addr_type) && !oअगर) ||
	    (addr_type & IPV6_ADDR_MAPPED) ||
	    (oअगर && sk->sk_bound_dev_अगर && oअगर != sk->sk_bound_dev_अगर))
		वापस -EINVAL;

	/* TODO: use ip6_datagram_send_ctl to get options from cmsg */

	स_रखो(&fl6, 0, माप(fl6));

	fl6.flowi6_proto = IPPROTO_ICMPV6;
	fl6.saddr = np->saddr;
	fl6.daddr = *daddr;
	fl6.flowi6_oअगर = oअगर;
	fl6.flowi6_mark = sk->sk_mark;
	fl6.flowi6_uid = sk->sk_uid;
	fl6.fl6_icmp_type = user_icmph.icmp6_type;
	fl6.fl6_icmp_code = user_icmph.icmp6_code;
	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

	ipcm6_init_sk(&ipc6, np);
	ipc6.sockc.mark = sk->sk_mark;
	fl6.flowlabel = ip6_make_flowinfo(ipc6.tclass, fl6.flowlabel);

	dst = ip6_sk_dst_lookup_flow(sk, &fl6, daddr, false);
	अगर (IS_ERR(dst))
		वापस PTR_ERR(dst);
	rt = (काष्ठा rt6_info *) dst;

	अगर (!fl6.flowi6_oअगर && ipv6_addr_is_multicast(&fl6.daddr))
		fl6.flowi6_oअगर = np->mcast_oअगर;
	अन्यथा अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->ucast_oअगर;

	pfh.icmph.type = user_icmph.icmp6_type;
	pfh.icmph.code = user_icmph.icmp6_code;
	pfh.icmph.checksum = 0;
	pfh.icmph.un.echo.id = inet->inet_sport;
	pfh.icmph.un.echo.sequence = user_icmph.icmp6_sequence;
	pfh.msg = msg;
	pfh.wcheck = 0;
	pfh.family = AF_INET6;

	ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);

	lock_sock(sk);
	err = ip6_append_data(sk, ping_getfrag, &pfh, len,
			      0, &ipc6, &fl6, rt,
			      MSG_DONTWAIT);

	अगर (err) अणु
		ICMP6_INC_STATS(sock_net(sk), rt->rt6i_idev,
				ICMP6_MIB_OUTERRORS);
		ip6_flush_pending_frames(sk);
	पूर्ण अन्यथा अणु
		icmpv6_push_pending_frames(sk, &fl6,
					   (काष्ठा icmp6hdr *)&pfh.icmph, len);
	पूर्ण
	release_sock(sk);

	dst_release(dst);

	अगर (err)
		वापस err;

	वापस len;
पूर्ण

काष्ठा proto pingv6_prot = अणु
	.name =		"PINGv6",
	.owner =	THIS_MODULE,
	.init =		ping_init_sock,
	.बंद =	ping_बंद,
	.connect =	ip6_datagram_connect_v6_only,
	.disconnect =	__udp_disconnect,
	.setsockopt =	ipv6_setsockopt,
	.माला_लोockopt =	ipv6_माला_लोockopt,
	.sendmsg =	ping_v6_sendmsg,
	.recvmsg =	ping_recvmsg,
	.bind =		ping_bind,
	.backlog_rcv =	ping_queue_rcv_skb,
	.hash =		ping_hash,
	.unhash =	ping_unhash,
	.get_port =	ping_get_port,
	.obj_size =	माप(काष्ठा raw6_sock),
पूर्ण;
EXPORT_SYMBOL_GPL(pingv6_prot);

अटल काष्ठा inet_protosw pingv6_protosw = अणु
	.type =      SOCK_DGRAM,
	.protocol =  IPPROTO_ICMPV6,
	.prot =      &pingv6_prot,
	.ops =       &inet6_sockraw_ops,
	.flags =     INET_PROTOSW_REUSE,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *ping_v6_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस ping_seq_start(seq, pos, AF_INET6);
पूर्ण

अटल पूर्णांक ping_v6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, IPV6_SEQ_DGRAM_HEADER);
	पूर्ण अन्यथा अणु
		पूर्णांक bucket = ((काष्ठा ping_iter_state *) seq->निजी)->bucket;
		काष्ठा inet_sock *inet = inet_sk(v);
		__u16 srcp = ntohs(inet->inet_sport);
		__u16 destp = ntohs(inet->inet_dport);
		ip6_dgram_sock_seq_show(seq, v, srcp, destp, bucket);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ping_v6_seq_ops = अणु
	.start		= ping_v6_seq_start,
	.show		= ping_v6_seq_show,
	.next		= ping_seq_next,
	.stop		= ping_seq_stop,
पूर्ण;

अटल पूर्णांक __net_init ping_v6_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net("icmp6", 0444, net->proc_net, &ping_v6_seq_ops,
			माप(काष्ठा ping_iter_state)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ping_v6_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("icmp6", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations ping_v6_net_ops = अणु
	.init = ping_v6_proc_init_net,
	.निकास = ping_v6_proc_निकास_net,
पूर्ण;
#पूर्ण_अगर

पूर्णांक __init pingv6_init(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	पूर्णांक ret = रेजिस्टर_pernet_subsys(&ping_v6_net_ops);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर
	pingv6_ops.ipv6_recv_error = ipv6_recv_error;
	pingv6_ops.ip6_datagram_recv_common_ctl = ip6_datagram_recv_common_ctl;
	pingv6_ops.ip6_datagram_recv_specअगरic_ctl =
		ip6_datagram_recv_specअगरic_ctl;
	pingv6_ops.icmpv6_err_convert = icmpv6_err_convert;
	pingv6_ops.ipv6_icmp_error = ipv6_icmp_error;
	pingv6_ops.ipv6_chk_addr = ipv6_chk_addr;
	वापस inet6_रेजिस्टर_protosw(&pingv6_protosw);
पूर्ण

/* This never माला_लो called because it's not possible to unload the ipv6 module,
 * but just in हाल.
 */
व्योम pingv6_निकास(व्योम)
अणु
	pingv6_ops.ipv6_recv_error = dummy_ipv6_recv_error;
	pingv6_ops.ip6_datagram_recv_common_ctl = dummy_ip6_datagram_recv_ctl;
	pingv6_ops.ip6_datagram_recv_specअगरic_ctl = dummy_ip6_datagram_recv_ctl;
	pingv6_ops.icmpv6_err_convert = dummy_icmpv6_err_convert;
	pingv6_ops.ipv6_icmp_error = dummy_ipv6_icmp_error;
	pingv6_ops.ipv6_chk_addr = dummy_ipv6_chk_addr;
#अगर_घोषित CONFIG_PROC_FS
	unरेजिस्टर_pernet_subsys(&ping_v6_net_ops);
#पूर्ण_अगर
	inet6_unरेजिस्टर_protosw(&pingv6_protosw);
पूर्ण
