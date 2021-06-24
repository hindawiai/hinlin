<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The IP to API glue.
 *
 * Authors:	see ip.c
 *
 * Fixes:
 *		Many		:	Split from ip.c , see ip.c क्रम history.
 *		Martin Mares	:	TOS setting fixed.
 *		Alan Cox	:	Fixed a couple of oopses in Martin's
 *					TOS tweaks.
 *		Mike McLagan	:	Routing by source
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/udp.h>
#समावेश <linux/igmp.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/route.h>
#समावेश <linux/mroute.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/route.h>
#समावेश <net/xfrm.h>
#समावेश <net/compat.h>
#समावेश <net/checksum.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/transp_v6.h>
#पूर्ण_अगर
#समावेश <net/ip_fib.h>

#समावेश <linux/errqueue.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/bpfilter.h>

/*
 *	SOL_IP control messages.
 */

अटल व्योम ip_cmsg_recv_pktinfo(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	काष्ठा in_pktinfo info = *PKTINFO_SKB_CB(skb);

	info.ipi_addr.s_addr = ip_hdr(skb)->daddr;

	put_cmsg(msg, SOL_IP, IP_PKTINFO, माप(info), &info);
पूर्ण

अटल व्योम ip_cmsg_recv_ttl(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ttl = ip_hdr(skb)->ttl;
	put_cmsg(msg, SOL_IP, IP_TTL, माप(पूर्णांक), &ttl);
पूर्ण

अटल व्योम ip_cmsg_recv_tos(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	put_cmsg(msg, SOL_IP, IP_TOS, 1, &ip_hdr(skb)->tos);
पूर्ण

अटल व्योम ip_cmsg_recv_opts(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	अगर (IPCB(skb)->opt.optlen == 0)
		वापस;

	put_cmsg(msg, SOL_IP, IP_RECVOPTS, IPCB(skb)->opt.optlen,
		 ip_hdr(skb) + 1);
पूर्ण


अटल व्योम ip_cmsg_recv_retopts(काष्ठा net *net, काष्ठा msghdr *msg,
				 काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर optbuf[माप(काष्ठा ip_options) + 40];
	काष्ठा ip_options *opt = (काष्ठा ip_options *)optbuf;

	अगर (IPCB(skb)->opt.optlen == 0)
		वापस;

	अगर (ip_options_echo(net, opt, skb)) अणु
		msg->msg_flags |= MSG_CTRUNC;
		वापस;
	पूर्ण
	ip_options_unकरो(opt);

	put_cmsg(msg, SOL_IP, IP_RETOPTS, opt->optlen, opt->__data);
पूर्ण

अटल व्योम ip_cmsg_recv_fragsize(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	पूर्णांक val;

	अगर (IPCB(skb)->frag_max_size == 0)
		वापस;

	val = IPCB(skb)->frag_max_size;
	put_cmsg(msg, SOL_IP, IP_RECVFRAGSIZE, माप(val), &val);
पूर्ण

अटल व्योम ip_cmsg_recv_checksum(काष्ठा msghdr *msg, काष्ठा sk_buff *skb,
				  पूर्णांक tlen, पूर्णांक offset)
अणु
	__wsum csum = skb->csum;

	अगर (skb->ip_summed != CHECKSUM_COMPLETE)
		वापस;

	अगर (offset != 0) अणु
		पूर्णांक tend_off = skb_transport_offset(skb) + tlen;
		csum = csum_sub(csum, skb_checksum(skb, tend_off, offset, 0));
	पूर्ण

	put_cmsg(msg, SOL_IP, IP_CHECKSUM, माप(__wsum), &csum);
पूर्ण

अटल व्योम ip_cmsg_recv_security(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	अक्षर *secdata;
	u32 seclen, secid;
	पूर्णांक err;

	err = security_socket_getpeersec_dgram(शून्य, skb, &secid);
	अगर (err)
		वापस;

	err = security_secid_to_secctx(secid, &secdata, &seclen);
	अगर (err)
		वापस;

	put_cmsg(msg, SOL_IP, SCM_SECURITY, seclen, secdata);
	security_release_secctx(secdata, seclen);
पूर्ण

अटल व्योम ip_cmsg_recv_dstaddr(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	__be16 _ports[2], *ports;
	काष्ठा sockaddr_in sin;

	/* All current transport protocols have the port numbers in the
	 * first four bytes of the transport header and this function is
	 * written with this assumption in mind.
	 */
	ports = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
				   माप(_ports), &_ports);
	अगर (!ports)
		वापस;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = ip_hdr(skb)->daddr;
	sin.sin_port = ports[1];
	स_रखो(sin.sin_zero, 0, माप(sin.sin_zero));

	put_cmsg(msg, SOL_IP, IP_ORIGDSTADDR, माप(sin), &sin);
पूर्ण

व्योम ip_cmsg_recv_offset(काष्ठा msghdr *msg, काष्ठा sock *sk,
			 काष्ठा sk_buff *skb, पूर्णांक tlen, पूर्णांक offset)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	अचिन्हित पूर्णांक flags = inet->cmsg_flags;

	/* Ordered by supposed usage frequency */
	अगर (flags & IP_CMSG_PKTINFO) अणु
		ip_cmsg_recv_pktinfo(msg, skb);

		flags &= ~IP_CMSG_PKTINFO;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_TTL) अणु
		ip_cmsg_recv_ttl(msg, skb);

		flags &= ~IP_CMSG_TTL;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_TOS) अणु
		ip_cmsg_recv_tos(msg, skb);

		flags &= ~IP_CMSG_TOS;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_RECVOPTS) अणु
		ip_cmsg_recv_opts(msg, skb);

		flags &= ~IP_CMSG_RECVOPTS;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_RETOPTS) अणु
		ip_cmsg_recv_retopts(sock_net(sk), msg, skb);

		flags &= ~IP_CMSG_RETOPTS;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_PASSSEC) अणु
		ip_cmsg_recv_security(msg, skb);

		flags &= ~IP_CMSG_PASSSEC;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_ORIGDSTADDR) अणु
		ip_cmsg_recv_dstaddr(msg, skb);

		flags &= ~IP_CMSG_ORIGDSTADDR;
		अगर (!flags)
			वापस;
	पूर्ण

	अगर (flags & IP_CMSG_CHECKSUM)
		ip_cmsg_recv_checksum(msg, skb, tlen, offset);

	अगर (flags & IP_CMSG_RECVFRAGSIZE)
		ip_cmsg_recv_fragsize(msg, skb);
पूर्ण
EXPORT_SYMBOL(ip_cmsg_recv_offset);

पूर्णांक ip_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg, काष्ठा ipcm_cookie *ipc,
		 bool allow_ipv6)
अणु
	पूर्णांक err, val;
	काष्ठा cmsghdr *cmsg;
	काष्ठा net *net = sock_net(sk);

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (allow_ipv6 &&
		    cmsg->cmsg_level == SOL_IPV6 &&
		    cmsg->cmsg_type == IPV6_PKTINFO) अणु
			काष्ठा in6_pktinfo *src_info;

			अगर (cmsg->cmsg_len < CMSG_LEN(माप(*src_info)))
				वापस -EINVAL;
			src_info = (काष्ठा in6_pktinfo *)CMSG_DATA(cmsg);
			अगर (!ipv6_addr_v4mapped(&src_info->ipi6_addr))
				वापस -EINVAL;
			अगर (src_info->ipi6_अगरindex)
				ipc->oअगर = src_info->ipi6_अगरindex;
			ipc->addr = src_info->ipi6_addr.s6_addr32[3];
			जारी;
		पूर्ण
#पूर्ण_अगर
		अगर (cmsg->cmsg_level == SOL_SOCKET) अणु
			err = __sock_cmsg_send(sk, msg, cmsg, &ipc->sockc);
			अगर (err)
				वापस err;
			जारी;
		पूर्ण

		अगर (cmsg->cmsg_level != SOL_IP)
			जारी;
		चयन (cmsg->cmsg_type) अणु
		हाल IP_RETOPTS:
			err = cmsg->cmsg_len - माप(काष्ठा cmsghdr);

			/* Our caller is responsible क्रम मुक्तing ipc->opt */
			err = ip_options_get(net, &ipc->opt,
					     KERNEL_SOCKPTR(CMSG_DATA(cmsg)),
					     err < 40 ? err : 40);
			अगर (err)
				वापस err;
			अवरोध;
		हाल IP_PKTINFO:
		अणु
			काष्ठा in_pktinfo *info;
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(काष्ठा in_pktinfo)))
				वापस -EINVAL;
			info = (काष्ठा in_pktinfo *)CMSG_DATA(cmsg);
			अगर (info->ipi_अगरindex)
				ipc->oअगर = info->ipi_अगरindex;
			ipc->addr = info->ipi_spec_dst.s_addr;
			अवरोध;
		पूर्ण
		हाल IP_TTL:
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(पूर्णांक)))
				वापस -EINVAL;
			val = *(पूर्णांक *)CMSG_DATA(cmsg);
			अगर (val < 1 || val > 255)
				वापस -EINVAL;
			ipc->ttl = val;
			अवरोध;
		हाल IP_TOS:
			अगर (cmsg->cmsg_len == CMSG_LEN(माप(पूर्णांक)))
				val = *(पूर्णांक *)CMSG_DATA(cmsg);
			अन्यथा अगर (cmsg->cmsg_len == CMSG_LEN(माप(u8)))
				val = *(u8 *)CMSG_DATA(cmsg);
			अन्यथा
				वापस -EINVAL;
			अगर (val < 0 || val > 255)
				वापस -EINVAL;
			ipc->tos = val;
			ipc->priority = rt_tos2priority(ipc->tos);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ip_ra_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_ra_chain *ra = container_of(head, काष्ठा ip_ra_chain, rcu);

	sock_put(ra->saved_sk);
	kमुक्त(ra);
पूर्ण

पूर्णांक ip_ra_control(काष्ठा sock *sk, अचिन्हित अक्षर on,
		  व्योम (*deकाष्ठाor)(काष्ठा sock *))
अणु
	काष्ठा ip_ra_chain *ra, *new_ra;
	काष्ठा ip_ra_chain __rcu **rap;
	काष्ठा net *net = sock_net(sk);

	अगर (sk->sk_type != SOCK_RAW || inet_sk(sk)->inet_num == IPPROTO_RAW)
		वापस -EINVAL;

	new_ra = on ? kदो_स्मृति(माप(*new_ra), GFP_KERNEL) : शून्य;
	अगर (on && !new_ra)
		वापस -ENOMEM;

	mutex_lock(&net->ipv4.ra_mutex);
	क्रम (rap = &net->ipv4.ra_chain;
	     (ra = rcu_dereference_रक्षित(*rap,
			lockdep_is_held(&net->ipv4.ra_mutex))) != शून्य;
	     rap = &ra->next) अणु
		अगर (ra->sk == sk) अणु
			अगर (on) अणु
				mutex_unlock(&net->ipv4.ra_mutex);
				kमुक्त(new_ra);
				वापस -EADDRINUSE;
			पूर्ण
			/* करोnt let ip_call_ra_chain() use sk again */
			ra->sk = शून्य;
			RCU_INIT_POINTER(*rap, ra->next);
			mutex_unlock(&net->ipv4.ra_mutex);

			अगर (ra->deकाष्ठाor)
				ra->deकाष्ठाor(sk);
			/*
			 * Delay sock_put(sk) and kमुक्त(ra) after one rcu grace
			 * period. This guarantee ip_call_ra_chain() करोnt need
			 * to mess with socket refcounts.
			 */
			ra->saved_sk = sk;
			call_rcu(&ra->rcu, ip_ra_destroy_rcu);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (!new_ra) अणु
		mutex_unlock(&net->ipv4.ra_mutex);
		वापस -ENOBUFS;
	पूर्ण
	new_ra->sk = sk;
	new_ra->deकाष्ठाor = deकाष्ठाor;

	RCU_INIT_POINTER(new_ra->next, ra);
	rcu_assign_poपूर्णांकer(*rap, new_ra);
	sock_hold(sk);
	mutex_unlock(&net->ipv4.ra_mutex);

	वापस 0;
पूर्ण

अटल व्योम ipv4_icmp_error_rfc4884(स्थिर काष्ठा sk_buff *skb,
				    काष्ठा sock_ee_data_rfc4884 *out)
अणु
	चयन (icmp_hdr(skb)->type) अणु
	हाल ICMP_DEST_UNREACH:
	हाल ICMP_TIME_EXCEEDED:
	हाल ICMP_PARAMETERPROB:
		ip_icmp_error_rfc4884(skb, out, माप(काष्ठा icmphdr),
				      icmp_hdr(skb)->un.reserved[1] * 4);
	पूर्ण
पूर्ण

व्योम ip_icmp_error(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err,
		   __be16 port, u32 info, u8 *payload)
अणु
	काष्ठा sock_exterr_skb *serr;

	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_त्रुटि_सं = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_ICMP;
	serr->ee.ee_type = icmp_hdr(skb)->type;
	serr->ee.ee_code = icmp_hdr(skb)->code;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&(((काष्ठा iphdr *)(icmp_hdr(skb) + 1))->daddr) -
				   skb_network_header(skb);
	serr->port = port;

	अगर (skb_pull(skb, payload - skb->data)) अणु
		अगर (inet_sk(sk)->recverr_rfc4884)
			ipv4_icmp_error_rfc4884(skb, &serr->ee.ee_rfc4884);

		skb_reset_transport_header(skb);
		अगर (sock_queue_err_skb(sk, skb) == 0)
			वापस;
	पूर्ण
	kमुक्त_skb(skb);
पूर्ण

व्योम ip_local_error(काष्ठा sock *sk, पूर्णांक err, __be32 daddr, __be16 port, u32 info)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sock_exterr_skb *serr;
	काष्ठा iphdr *iph;
	काष्ठा sk_buff *skb;

	अगर (!inet->recverr)
		वापस;

	skb = alloc_skb(माप(काष्ठा iphdr), GFP_ATOMIC);
	अगर (!skb)
		वापस;

	skb_put(skb, माप(काष्ठा iphdr));
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	iph->daddr = daddr;

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_त्रुटि_सं = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_LOCAL;
	serr->ee.ee_type = 0;
	serr->ee.ee_code = 0;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&iph->daddr - skb_network_header(skb);
	serr->port = port;

	__skb_pull(skb, skb_tail_poपूर्णांकer(skb) - skb->data);
	skb_reset_transport_header(skb);

	अगर (sock_queue_err_skb(sk, skb))
		kमुक्त_skb(skb);
पूर्ण

/* For some errors we have valid addr_offset even with zero payload and
 * zero port. Also, addr_offset should be supported अगर port is set.
 */
अटल अंतरभूत bool ipv4_datagram_support_addr(काष्ठा sock_exterr_skb *serr)
अणु
	वापस serr->ee.ee_origin == SO_EE_ORIGIN_ICMP ||
	       serr->ee.ee_origin == SO_EE_ORIGIN_LOCAL || serr->port;
पूर्ण

/* IPv4 supports cmsg on all imcp errors and some बारtamps
 *
 * Timestamp code paths करो not initialize the fields expected by cmsg:
 * the PKTINFO fields in skb->cb[]. Fill those in here.
 */
अटल bool ipv4_datagram_support_cmsg(स्थिर काष्ठा sock *sk,
				       काष्ठा sk_buff *skb,
				       पूर्णांक ee_origin)
अणु
	काष्ठा in_pktinfo *info;

	अगर (ee_origin == SO_EE_ORIGIN_ICMP)
		वापस true;

	अगर (ee_origin == SO_EE_ORIGIN_LOCAL)
		वापस false;

	/* Support IP_PKTINFO on tstamp packets अगर requested, to correlate
	 * बारtamp with egress dev. Not possible क्रम packets without iअगर
	 * or without payload (SOF_TIMESTAMPING_OPT_TSONLY).
	 */
	info = PKTINFO_SKB_CB(skb);
	अगर (!(sk->sk_tsflags & SOF_TIMESTAMPING_OPT_CMSG) ||
	    !info->ipi_अगरindex)
		वापस false;

	info->ipi_spec_dst.s_addr = ip_hdr(skb)->saddr;
	वापस true;
पूर्ण

/*
 *	Handle MSG_ERRQUEUE
 */
पूर्णांक ip_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len, पूर्णांक *addr_len)
अणु
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sk_buff *skb;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, msg->msg_name);
	काष्ठा अणु
		काष्ठा sock_extended_err ee;
		काष्ठा sockaddr_in	 offender;
	पूर्ण errhdr;
	पूर्णांक err;
	पूर्णांक copied;

	err = -EAGAIN;
	skb = sock_dequeue_err_skb(sk);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (unlikely(err)) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण
	sock_recv_बारtamp(msg, sk, skb);

	serr = SKB_EXT_ERR(skb);

	अगर (sin && ipv4_datagram_support_addr(serr)) अणु
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = *(__be32 *)(skb_network_header(skb) +
						   serr->addr_offset);
		sin->sin_port = serr->port;
		स_रखो(&sin->sin_zero, 0, माप(sin->sin_zero));
		*addr_len = माप(*sin);
	पूर्ण

	स_नकल(&errhdr.ee, &serr->ee, माप(काष्ठा sock_extended_err));
	sin = &errhdr.offender;
	स_रखो(sin, 0, माप(*sin));

	अगर (ipv4_datagram_support_cmsg(sk, skb, serr->ee.ee_origin)) अणु
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = ip_hdr(skb)->saddr;
		अगर (inet_sk(sk)->cmsg_flags)
			ip_cmsg_recv(msg, skb);
	पूर्ण

	put_cmsg(msg, SOL_IP, IP_RECVERR, माप(errhdr), &errhdr);

	/* Now we could try to dump offended packet options */

	msg->msg_flags |= MSG_ERRQUEUE;
	err = copied;

	consume_skb(skb);
out:
	वापस err;
पूर्ण

अटल व्योम __ip_sock_set_tos(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (sk->sk_type == SOCK_STREAM) अणु
		val &= ~INET_ECN_MASK;
		val |= inet_sk(sk)->tos & INET_ECN_MASK;
	पूर्ण
	अगर (inet_sk(sk)->tos != val) अणु
		inet_sk(sk)->tos = val;
		sk->sk_priority = rt_tos2priority(val);
		sk_dst_reset(sk);
	पूर्ण
पूर्ण

व्योम ip_sock_set_tos(काष्ठा sock *sk, पूर्णांक val)
अणु
	lock_sock(sk);
	__ip_sock_set_tos(sk, val);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(ip_sock_set_tos);

व्योम ip_sock_set_मुक्तbind(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	inet_sk(sk)->मुक्तbind = true;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(ip_sock_set_मुक्तbind);

व्योम ip_sock_set_recverr(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	inet_sk(sk)->recverr = true;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(ip_sock_set_recverr);

पूर्णांक ip_sock_set_mtu_discover(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (val < IP_PMTUDISC_DONT || val > IP_PMTUDISC_OMIT)
		वापस -EINVAL;
	lock_sock(sk);
	inet_sk(sk)->pmtudisc = val;
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip_sock_set_mtu_discover);

व्योम ip_sock_set_pktinfo(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	inet_sk(sk)->cmsg_flags |= IP_CMSG_PKTINFO;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(ip_sock_set_pktinfo);

/*
 *	Socket option code क्रम IP. This is the end of the line after any
 *	TCP,UDP etc options on an IP socket.
 */
अटल bool setsockopt_needs_rtnl(पूर्णांक optname)
अणु
	चयन (optname) अणु
	हाल IP_ADD_MEMBERSHIP:
	हाल IP_ADD_SOURCE_MEMBERSHIP:
	हाल IP_BLOCK_SOURCE:
	हाल IP_DROP_MEMBERSHIP:
	हाल IP_DROP_SOURCE_MEMBERSHIP:
	हाल IP_MSFILTER:
	हाल IP_UNBLOCK_SOURCE:
	हाल MCAST_BLOCK_SOURCE:
	हाल MCAST_MSFILTER:
	हाल MCAST_JOIN_GROUP:
	हाल MCAST_JOIN_SOURCE_GROUP:
	हाल MCAST_LEAVE_GROUP:
	हाल MCAST_LEAVE_SOURCE_GROUP:
	हाल MCAST_UNBLOCK_SOURCE:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक set_mcast_msfilter(काष्ठा sock *sk, पूर्णांक अगरindex,
			      पूर्णांक numsrc, पूर्णांक भ_शेषe,
			      काष्ठा sockaddr_storage *group,
			      काष्ठा sockaddr_storage *list)
अणु
	पूर्णांक msize = IP_MSFILTER_SIZE(numsrc);
	काष्ठा ip_msfilter *msf;
	काष्ठा sockaddr_in *psin;
	पूर्णांक err, i;

	msf = kदो_स्मृति(msize, GFP_KERNEL);
	अगर (!msf)
		वापस -ENOBUFS;

	psin = (काष्ठा sockaddr_in *)group;
	अगर (psin->sin_family != AF_INET)
		जाओ Eaddrnotavail;
	msf->imsf_multiaddr = psin->sin_addr.s_addr;
	msf->imsf_पूर्णांकerface = 0;
	msf->imsf_भ_शेषe = भ_शेषe;
	msf->imsf_numsrc = numsrc;
	क्रम (i = 0; i < numsrc; ++i) अणु
		psin = (काष्ठा sockaddr_in *)&list[i];

		अगर (psin->sin_family != AF_INET)
			जाओ Eaddrnotavail;
		msf->imsf_slist[i] = psin->sin_addr.s_addr;
	पूर्ण
	err = ip_mc_msfilter(sk, msf, अगरindex);
	kमुक्त(msf);
	वापस err;

Eaddrnotavail:
	kमुक्त(msf);
	वापस -EADDRNOTAVAIL;
पूर्ण

अटल पूर्णांक copy_group_source_from_sockptr(काष्ठा group_source_req *greqs,
		sockptr_t optval, पूर्णांक optlen)
अणु
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_group_source_req gr32;

		अगर (optlen != माप(gr32))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&gr32, optval, माप(gr32)))
			वापस -EFAULT;
		greqs->gsr_पूर्णांकerface = gr32.gsr_पूर्णांकerface;
		greqs->gsr_group = gr32.gsr_group;
		greqs->gsr_source = gr32.gsr_source;
	पूर्ण अन्यथा अणु
		अगर (optlen != माप(*greqs))
			वापस -EINVAL;
		अगर (copy_from_sockptr(greqs, optval, माप(*greqs)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_mcast_group_source(काष्ठा sock *sk, पूर्णांक optname,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा group_source_req greqs;
	काष्ठा ip_mreq_source mreqs;
	काष्ठा sockaddr_in *psin;
	पूर्णांक omode, add, err;

	err = copy_group_source_from_sockptr(&greqs, optval, optlen);
	अगर (err)
		वापस err;

	अगर (greqs.gsr_group.ss_family != AF_INET ||
	    greqs.gsr_source.ss_family != AF_INET)
		वापस -EADDRNOTAVAIL;

	psin = (काष्ठा sockaddr_in *)&greqs.gsr_group;
	mreqs.imr_multiaddr = psin->sin_addr.s_addr;
	psin = (काष्ठा sockaddr_in *)&greqs.gsr_source;
	mreqs.imr_sourceaddr = psin->sin_addr.s_addr;
	mreqs.imr_पूर्णांकerface = 0; /* use index क्रम mc_source */

	अगर (optname == MCAST_BLOCK_SOURCE) अणु
		omode = MCAST_EXCLUDE;
		add = 1;
	पूर्ण अन्यथा अगर (optname == MCAST_UNBLOCK_SOURCE) अणु
		omode = MCAST_EXCLUDE;
		add = 0;
	पूर्ण अन्यथा अगर (optname == MCAST_JOIN_SOURCE_GROUP) अणु
		काष्ठा ip_mreqn mreq;

		psin = (काष्ठा sockaddr_in *)&greqs.gsr_group;
		mreq.imr_multiaddr = psin->sin_addr;
		mreq.imr_address.s_addr = 0;
		mreq.imr_अगरindex = greqs.gsr_पूर्णांकerface;
		err = ip_mc_join_group_ssm(sk, &mreq, MCAST_INCLUDE);
		अगर (err && err != -EADDRINUSE)
			वापस err;
		greqs.gsr_पूर्णांकerface = mreq.imr_अगरindex;
		omode = MCAST_INCLUDE;
		add = 1;
	पूर्ण अन्यथा /* MCAST_LEAVE_SOURCE_GROUP */ अणु
		omode = MCAST_INCLUDE;
		add = 0;
	पूर्ण
	वापस ip_mc_source(add, omode, sk, &mreqs, greqs.gsr_पूर्णांकerface);
पूर्ण

अटल पूर्णांक ip_set_mcast_msfilter(काष्ठा sock *sk, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा group_filter *gsf = शून्य;
	पूर्णांक err;

	अगर (optlen < GROUP_FILTER_SIZE(0))
		वापस -EINVAL;
	अगर (optlen > sysctl_opपंचांगem_max)
		वापस -ENOBUFS;

	gsf = memdup_sockptr(optval, optlen);
	अगर (IS_ERR(gsf))
		वापस PTR_ERR(gsf);

	/* numsrc >= (4G-140)/128 overflow in 32 bits */
	err = -ENOBUFS;
	अगर (gsf->gf_numsrc >= 0x1ffffff ||
	    gsf->gf_numsrc > sock_net(sk)->ipv4.sysctl_igmp_max_msf)
		जाओ out_मुक्त_gsf;

	err = -EINVAL;
	अगर (GROUP_FILTER_SIZE(gsf->gf_numsrc) > optlen)
		जाओ out_मुक्त_gsf;

	err = set_mcast_msfilter(sk, gsf->gf_पूर्णांकerface, gsf->gf_numsrc,
				 gsf->gf_भ_शेषe, &gsf->gf_group, gsf->gf_slist);
out_मुक्त_gsf:
	kमुक्त(gsf);
	वापस err;
पूर्ण

अटल पूर्णांक compat_ip_set_mcast_msfilter(काष्ठा sock *sk, sockptr_t optval,
		पूर्णांक optlen)
अणु
	स्थिर पूर्णांक size0 = दुरत्व(काष्ठा compat_group_filter, gf_slist);
	काष्ठा compat_group_filter *gf32;
	अचिन्हित पूर्णांक n;
	व्योम *p;
	पूर्णांक err;

	अगर (optlen < size0)
		वापस -EINVAL;
	अगर (optlen > sysctl_opपंचांगem_max - 4)
		वापस -ENOBUFS;

	p = kदो_स्मृति(optlen + 4, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	gf32 = p + 4; /* we want ->gf_group and ->gf_slist aligned */

	err = -EFAULT;
	अगर (copy_from_sockptr(gf32, optval, optlen))
		जाओ out_मुक्त_gsf;

	/* numsrc >= (4G-140)/128 overflow in 32 bits */
	n = gf32->gf_numsrc;
	err = -ENOBUFS;
	अगर (n >= 0x1ffffff)
		जाओ out_मुक्त_gsf;

	err = -EINVAL;
	अगर (दुरत्व(काष्ठा compat_group_filter, gf_slist[n]) > optlen)
		जाओ out_मुक्त_gsf;

	/* numsrc >= (4G-140)/128 overflow in 32 bits */
	err = -ENOBUFS;
	अगर (n > sock_net(sk)->ipv4.sysctl_igmp_max_msf)
		जाओ out_मुक्त_gsf;
	err = set_mcast_msfilter(sk, gf32->gf_पूर्णांकerface, n, gf32->gf_भ_शेषe,
				 &gf32->gf_group, gf32->gf_slist);
out_मुक्त_gsf:
	kमुक्त(p);
	वापस err;
पूर्ण

अटल पूर्णांक ip_mcast_join_leave(काष्ठा sock *sk, पूर्णांक optname,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा ip_mreqn mreq = अणु पूर्ण;
	काष्ठा sockaddr_in *psin;
	काष्ठा group_req greq;

	अगर (optlen < माप(काष्ठा group_req))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&greq, optval, माप(greq)))
		वापस -EFAULT;

	psin = (काष्ठा sockaddr_in *)&greq.gr_group;
	अगर (psin->sin_family != AF_INET)
		वापस -EINVAL;
	mreq.imr_multiaddr = psin->sin_addr;
	mreq.imr_अगरindex = greq.gr_पूर्णांकerface;
	अगर (optname == MCAST_JOIN_GROUP)
		वापस ip_mc_join_group(sk, &mreq);
	वापस ip_mc_leave_group(sk, &mreq);
पूर्ण

अटल पूर्णांक compat_ip_mcast_join_leave(काष्ठा sock *sk, पूर्णांक optname,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा compat_group_req greq;
	काष्ठा ip_mreqn mreq = अणु पूर्ण;
	काष्ठा sockaddr_in *psin;

	अगर (optlen < माप(काष्ठा compat_group_req))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&greq, optval, माप(greq)))
		वापस -EFAULT;

	psin = (काष्ठा sockaddr_in *)&greq.gr_group;
	अगर (psin->sin_family != AF_INET)
		वापस -EINVAL;
	mreq.imr_multiaddr = psin->sin_addr;
	mreq.imr_अगरindex = greq.gr_पूर्णांकerface;

	अगर (optname == MCAST_JOIN_GROUP)
		वापस ip_mc_join_group(sk, &mreq);
	वापस ip_mc_leave_group(sk, &mreq);
पूर्ण

अटल पूर्णांक करो_ip_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक val = 0, err;
	bool needs_rtnl = setsockopt_needs_rtnl(optname);

	चयन (optname) अणु
	हाल IP_PKTINFO:
	हाल IP_RECVTTL:
	हाल IP_RECVOPTS:
	हाल IP_RECVTOS:
	हाल IP_RETOPTS:
	हाल IP_TOS:
	हाल IP_TTL:
	हाल IP_HDRINCL:
	हाल IP_MTU_DISCOVER:
	हाल IP_RECVERR:
	हाल IP_ROUTER_ALERT:
	हाल IP_FREEBIND:
	हाल IP_PASSSEC:
	हाल IP_TRANSPARENT:
	हाल IP_MINTTL:
	हाल IP_NODEFRAG:
	हाल IP_BIND_ADDRESS_NO_PORT:
	हाल IP_UNICAST_IF:
	हाल IP_MULTICAST_TTL:
	हाल IP_MULTICAST_ALL:
	हाल IP_MULTICAST_LOOP:
	हाल IP_RECVORIGDSTADDR:
	हाल IP_CHECKSUM:
	हाल IP_RECVFRAGSIZE:
	हाल IP_RECVERR_RFC4884:
		अगर (optlen >= माप(पूर्णांक)) अणु
			अगर (copy_from_sockptr(&val, optval, माप(val)))
				वापस -EFAULT;
		पूर्ण अन्यथा अगर (optlen >= माप(अक्षर)) अणु
			अचिन्हित अक्षर ucval;

			अगर (copy_from_sockptr(&ucval, optval, माप(ucval)))
				वापस -EFAULT;
			val = (पूर्णांक) ucval;
		पूर्ण
	पूर्ण

	/* If optlen==0, it is equivalent to val == 0 */

	अगर (optname == IP_ROUTER_ALERT)
		वापस ip_ra_control(sk, val ? 1 : 0, शून्य);
	अगर (ip_mroute_opt(optname))
		वापस ip_mroute_setsockopt(sk, optname, optval, optlen);

	err = 0;
	अगर (needs_rtnl)
		rtnl_lock();
	lock_sock(sk);

	चयन (optname) अणु
	हाल IP_OPTIONS:
	अणु
		काष्ठा ip_options_rcu *old, *opt = शून्य;

		अगर (optlen > 40)
			जाओ e_inval;
		err = ip_options_get(sock_net(sk), &opt, optval, optlen);
		अगर (err)
			अवरोध;
		old = rcu_dereference_रक्षित(inet->inet_opt,
						lockdep_sock_is_held(sk));
		अगर (inet->is_icsk) अणु
			काष्ठा inet_connection_sock *icsk = inet_csk(sk);
#अगर IS_ENABLED(CONFIG_IPV6)
			अगर (sk->sk_family == PF_INET ||
			    (!((1 << sk->sk_state) &
			       (TCPF_LISTEN | TCPF_CLOSE)) &&
			     inet->inet_daddr != LOOPBACK4_IPV6)) अणु
#पूर्ण_अगर
				अगर (old)
					icsk->icsk_ext_hdr_len -= old->opt.optlen;
				अगर (opt)
					icsk->icsk_ext_hdr_len += opt->opt.optlen;
				icsk->icsk_sync_mss(sk, icsk->icsk_pmtu_cookie);
#अगर IS_ENABLED(CONFIG_IPV6)
			पूर्ण
#पूर्ण_अगर
		पूर्ण
		rcu_assign_poपूर्णांकer(inet->inet_opt, opt);
		अगर (old)
			kमुक्त_rcu(old, rcu);
		अवरोध;
	पूर्ण
	हाल IP_PKTINFO:
		अगर (val)
			inet->cmsg_flags |= IP_CMSG_PKTINFO;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_PKTINFO;
		अवरोध;
	हाल IP_RECVTTL:
		अगर (val)
			inet->cmsg_flags |=  IP_CMSG_TTL;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_TTL;
		अवरोध;
	हाल IP_RECVTOS:
		अगर (val)
			inet->cmsg_flags |=  IP_CMSG_TOS;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_TOS;
		अवरोध;
	हाल IP_RECVOPTS:
		अगर (val)
			inet->cmsg_flags |=  IP_CMSG_RECVOPTS;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_RECVOPTS;
		अवरोध;
	हाल IP_RETOPTS:
		अगर (val)
			inet->cmsg_flags |= IP_CMSG_RETOPTS;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_RETOPTS;
		अवरोध;
	हाल IP_PASSSEC:
		अगर (val)
			inet->cmsg_flags |= IP_CMSG_PASSSEC;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_PASSSEC;
		अवरोध;
	हाल IP_RECVORIGDSTADDR:
		अगर (val)
			inet->cmsg_flags |= IP_CMSG_ORIGDSTADDR;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_ORIGDSTADDR;
		अवरोध;
	हाल IP_CHECKSUM:
		अगर (val) अणु
			अगर (!(inet->cmsg_flags & IP_CMSG_CHECKSUM)) अणु
				inet_inc_convert_csum(sk);
				inet->cmsg_flags |= IP_CMSG_CHECKSUM;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (inet->cmsg_flags & IP_CMSG_CHECKSUM) अणु
				inet_dec_convert_csum(sk);
				inet->cmsg_flags &= ~IP_CMSG_CHECKSUM;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IP_RECVFRAGSIZE:
		अगर (sk->sk_type != SOCK_RAW && sk->sk_type != SOCK_DGRAM)
			जाओ e_inval;
		अगर (val)
			inet->cmsg_flags |= IP_CMSG_RECVFRAGSIZE;
		अन्यथा
			inet->cmsg_flags &= ~IP_CMSG_RECVFRAGSIZE;
		अवरोध;
	हाल IP_TOS:	/* This sets both TOS and Precedence */
		__ip_sock_set_tos(sk, val);
		अवरोध;
	हाल IP_TTL:
		अगर (optlen < 1)
			जाओ e_inval;
		अगर (val != -1 && (val < 1 || val > 255))
			जाओ e_inval;
		inet->uc_ttl = val;
		अवरोध;
	हाल IP_HDRINCL:
		अगर (sk->sk_type != SOCK_RAW) अणु
			err = -ENOPROTOOPT;
			अवरोध;
		पूर्ण
		inet->hdrincl = val ? 1 : 0;
		अवरोध;
	हाल IP_NODEFRAG:
		अगर (sk->sk_type != SOCK_RAW) अणु
			err = -ENOPROTOOPT;
			अवरोध;
		पूर्ण
		inet->nodefrag = val ? 1 : 0;
		अवरोध;
	हाल IP_BIND_ADDRESS_NO_PORT:
		inet->bind_address_no_port = val ? 1 : 0;
		अवरोध;
	हाल IP_MTU_DISCOVER:
		अगर (val < IP_PMTUDISC_DONT || val > IP_PMTUDISC_OMIT)
			जाओ e_inval;
		inet->pmtudisc = val;
		अवरोध;
	हाल IP_RECVERR:
		inet->recverr = !!val;
		अगर (!val)
			skb_queue_purge(&sk->sk_error_queue);
		अवरोध;
	हाल IP_RECVERR_RFC4884:
		अगर (val < 0 || val > 1)
			जाओ e_inval;
		inet->recverr_rfc4884 = !!val;
		अवरोध;
	हाल IP_MULTICAST_TTL:
		अगर (sk->sk_type == SOCK_STREAM)
			जाओ e_inval;
		अगर (optlen < 1)
			जाओ e_inval;
		अगर (val == -1)
			val = 1;
		अगर (val < 0 || val > 255)
			जाओ e_inval;
		inet->mc_ttl = val;
		अवरोध;
	हाल IP_MULTICAST_LOOP:
		अगर (optlen < 1)
			जाओ e_inval;
		inet->mc_loop = !!val;
		अवरोध;
	हाल IP_UNICAST_IF:
	अणु
		काष्ठा net_device *dev = शून्य;
		पूर्णांक अगरindex;
		पूर्णांक midx;

		अगर (optlen != माप(पूर्णांक))
			जाओ e_inval;

		अगरindex = (__क्रमce पूर्णांक)ntohl((__क्रमce __be32)val);
		अगर (अगरindex == 0) अणु
			inet->uc_index = 0;
			err = 0;
			अवरोध;
		पूर्ण

		dev = dev_get_by_index(sock_net(sk), अगरindex);
		err = -EADDRNOTAVAIL;
		अगर (!dev)
			अवरोध;

		midx = l3mdev_master_अगरindex(dev);
		dev_put(dev);

		err = -EINVAL;
		अगर (sk->sk_bound_dev_अगर && midx != sk->sk_bound_dev_अगर)
			अवरोध;

		inet->uc_index = अगरindex;
		err = 0;
		अवरोध;
	पूर्ण
	हाल IP_MULTICAST_IF:
	अणु
		काष्ठा ip_mreqn mreq;
		काष्ठा net_device *dev = शून्य;
		पूर्णांक midx;

		अगर (sk->sk_type == SOCK_STREAM)
			जाओ e_inval;
		/*
		 *	Check the arguments are allowable
		 */

		अगर (optlen < माप(काष्ठा in_addr))
			जाओ e_inval;

		err = -EFAULT;
		अगर (optlen >= माप(काष्ठा ip_mreqn)) अणु
			अगर (copy_from_sockptr(&mreq, optval, माप(mreq)))
				अवरोध;
		पूर्ण अन्यथा अणु
			स_रखो(&mreq, 0, माप(mreq));
			अगर (optlen >= माप(काष्ठा ip_mreq)) अणु
				अगर (copy_from_sockptr(&mreq, optval,
						      माप(काष्ठा ip_mreq)))
					अवरोध;
			पूर्ण अन्यथा अगर (optlen >= माप(काष्ठा in_addr)) अणु
				अगर (copy_from_sockptr(&mreq.imr_address, optval,
						      माप(काष्ठा in_addr)))
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (!mreq.imr_अगरindex) अणु
			अगर (mreq.imr_address.s_addr == htonl(INADDR_ANY)) अणु
				inet->mc_index = 0;
				inet->mc_addr  = 0;
				err = 0;
				अवरोध;
			पूर्ण
			dev = ip_dev_find(sock_net(sk), mreq.imr_address.s_addr);
			अगर (dev)
				mreq.imr_अगरindex = dev->अगरindex;
		पूर्ण अन्यथा
			dev = dev_get_by_index(sock_net(sk), mreq.imr_अगरindex);


		err = -EADDRNOTAVAIL;
		अगर (!dev)
			अवरोध;

		midx = l3mdev_master_अगरindex(dev);

		dev_put(dev);

		err = -EINVAL;
		अगर (sk->sk_bound_dev_अगर &&
		    mreq.imr_अगरindex != sk->sk_bound_dev_अगर &&
		    midx != sk->sk_bound_dev_अगर)
			अवरोध;

		inet->mc_index = mreq.imr_अगरindex;
		inet->mc_addr  = mreq.imr_address.s_addr;
		err = 0;
		अवरोध;
	पूर्ण

	हाल IP_ADD_MEMBERSHIP:
	हाल IP_DROP_MEMBERSHIP:
	अणु
		काष्ठा ip_mreqn mreq;

		err = -EPROTO;
		अगर (inet_sk(sk)->is_icsk)
			अवरोध;

		अगर (optlen < माप(काष्ठा ip_mreq))
			जाओ e_inval;
		err = -EFAULT;
		अगर (optlen >= माप(काष्ठा ip_mreqn)) अणु
			अगर (copy_from_sockptr(&mreq, optval, माप(mreq)))
				अवरोध;
		पूर्ण अन्यथा अणु
			स_रखो(&mreq, 0, माप(mreq));
			अगर (copy_from_sockptr(&mreq, optval,
					      माप(काष्ठा ip_mreq)))
				अवरोध;
		पूर्ण

		अगर (optname == IP_ADD_MEMBERSHIP)
			err = ip_mc_join_group(sk, &mreq);
		अन्यथा
			err = ip_mc_leave_group(sk, &mreq);
		अवरोध;
	पूर्ण
	हाल IP_MSFILTER:
	अणु
		काष्ठा ip_msfilter *msf;

		अगर (optlen < IP_MSFILTER_SIZE(0))
			जाओ e_inval;
		अगर (optlen > sysctl_opपंचांगem_max) अणु
			err = -ENOBUFS;
			अवरोध;
		पूर्ण
		msf = memdup_sockptr(optval, optlen);
		अगर (IS_ERR(msf)) अणु
			err = PTR_ERR(msf);
			अवरोध;
		पूर्ण
		/* numsrc >= (1G-4) overflow in 32 bits */
		अगर (msf->imsf_numsrc >= 0x3ffffffcU ||
		    msf->imsf_numsrc > net->ipv4.sysctl_igmp_max_msf) अणु
			kमुक्त(msf);
			err = -ENOBUFS;
			अवरोध;
		पूर्ण
		अगर (IP_MSFILTER_SIZE(msf->imsf_numsrc) > optlen) अणु
			kमुक्त(msf);
			err = -EINVAL;
			अवरोध;
		पूर्ण
		err = ip_mc_msfilter(sk, msf, 0);
		kमुक्त(msf);
		अवरोध;
	पूर्ण
	हाल IP_BLOCK_SOURCE:
	हाल IP_UNBLOCK_SOURCE:
	हाल IP_ADD_SOURCE_MEMBERSHIP:
	हाल IP_DROP_SOURCE_MEMBERSHIP:
	अणु
		काष्ठा ip_mreq_source mreqs;
		पूर्णांक omode, add;

		अगर (optlen != माप(काष्ठा ip_mreq_source))
			जाओ e_inval;
		अगर (copy_from_sockptr(&mreqs, optval, माप(mreqs))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (optname == IP_BLOCK_SOURCE) अणु
			omode = MCAST_EXCLUDE;
			add = 1;
		पूर्ण अन्यथा अगर (optname == IP_UNBLOCK_SOURCE) अणु
			omode = MCAST_EXCLUDE;
			add = 0;
		पूर्ण अन्यथा अगर (optname == IP_ADD_SOURCE_MEMBERSHIP) अणु
			काष्ठा ip_mreqn mreq;

			mreq.imr_multiaddr.s_addr = mreqs.imr_multiaddr;
			mreq.imr_address.s_addr = mreqs.imr_पूर्णांकerface;
			mreq.imr_अगरindex = 0;
			err = ip_mc_join_group_ssm(sk, &mreq, MCAST_INCLUDE);
			अगर (err && err != -EADDRINUSE)
				अवरोध;
			omode = MCAST_INCLUDE;
			add = 1;
		पूर्ण अन्यथा /* IP_DROP_SOURCE_MEMBERSHIP */ अणु
			omode = MCAST_INCLUDE;
			add = 0;
		पूर्ण
		err = ip_mc_source(add, omode, sk, &mreqs, 0);
		अवरोध;
	पूर्ण
	हाल MCAST_JOIN_GROUP:
	हाल MCAST_LEAVE_GROUP:
		अगर (in_compat_syscall())
			err = compat_ip_mcast_join_leave(sk, optname, optval,
							 optlen);
		अन्यथा
			err = ip_mcast_join_leave(sk, optname, optval, optlen);
		अवरोध;
	हाल MCAST_JOIN_SOURCE_GROUP:
	हाल MCAST_LEAVE_SOURCE_GROUP:
	हाल MCAST_BLOCK_SOURCE:
	हाल MCAST_UNBLOCK_SOURCE:
		err = करो_mcast_group_source(sk, optname, optval, optlen);
		अवरोध;
	हाल MCAST_MSFILTER:
		अगर (in_compat_syscall())
			err = compat_ip_set_mcast_msfilter(sk, optval, optlen);
		अन्यथा
			err = ip_set_mcast_msfilter(sk, optval, optlen);
		अवरोध;
	हाल IP_MULTICAST_ALL:
		अगर (optlen < 1)
			जाओ e_inval;
		अगर (val != 0 && val != 1)
			जाओ e_inval;
		inet->mc_all = val;
		अवरोध;

	हाल IP_FREEBIND:
		अगर (optlen < 1)
			जाओ e_inval;
		inet->मुक्तbind = !!val;
		अवरोध;

	हाल IP_IPSEC_POLICY:
	हाल IP_XFRM_POLICY:
		err = -EPERM;
		अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
			अवरोध;
		err = xfrm_user_policy(sk, optname, optval, optlen);
		अवरोध;

	हाल IP_TRANSPARENT:
		अगर (!!val && !ns_capable(sock_net(sk)->user_ns, CAP_NET_RAW) &&
		    !ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN)) अणु
			err = -EPERM;
			अवरोध;
		पूर्ण
		अगर (optlen < 1)
			जाओ e_inval;
		inet->transparent = !!val;
		अवरोध;

	हाल IP_MINTTL:
		अगर (optlen < 1)
			जाओ e_inval;
		अगर (val < 0 || val > 255)
			जाओ e_inval;
		inet->min_ttl = val;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	release_sock(sk);
	अगर (needs_rtnl)
		rtnl_unlock();
	वापस err;

e_inval:
	release_sock(sk);
	अगर (needs_rtnl)
		rtnl_unlock();
	वापस -EINVAL;
पूर्ण

/**
 * ipv4_pktinfo_prepare - transfer some info from rtable to skb
 * @sk: socket
 * @skb: buffer
 *
 * To support IP_CMSG_PKTINFO option, we store rt_iअगर and specअगरic
 * destination in skb->cb[] beक्रमe dst drop.
 * This way, receiver करोesn't make cache line misses to पढ़ो rtable.
 */
व्योम ipv4_pktinfo_prepare(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा in_pktinfo *pktinfo = PKTINFO_SKB_CB(skb);
	bool prepare = (inet_sk(sk)->cmsg_flags & IP_CMSG_PKTINFO) ||
		       ipv6_sk_rxinfo(sk);

	अगर (prepare && skb_rtable(skb)) अणु
		/* skb->cb is overloaded: prior to this poपूर्णांक it is IPअणु6पूर्णCB
		 * which has पूर्णांकerface index (iअगर) as the first member of the
		 * underlying inetअणु6पूर्ण_skb_parm काष्ठा. This code then overlays
		 * PKTINFO_SKB_CB and in_pktinfo also has iअगर as the first
		 * element so the iअगर is picked up from the prior IPCB. If iअगर
		 * is the loopback पूर्णांकerface, then वापस the sending पूर्णांकerface
		 * (e.g., process binds socket to eth0 क्रम Tx which is
		 * redirected to loopback in the rtable/dst).
		 */
		काष्ठा rtable *rt = skb_rtable(skb);
		bool l3slave = ipv4_l3mdev_skb(IPCB(skb)->flags);

		अगर (pktinfo->ipi_अगरindex == LOOPBACK_IFINDEX)
			pktinfo->ipi_अगरindex = inet_iअगर(skb);
		अन्यथा अगर (l3slave && rt && rt->rt_iअगर)
			pktinfo->ipi_अगरindex = rt->rt_iअगर;

		pktinfo->ipi_spec_dst.s_addr = fib_compute_spec_dst(skb);
	पूर्ण अन्यथा अणु
		pktinfo->ipi_अगरindex = 0;
		pktinfo->ipi_spec_dst.s_addr = 0;
	पूर्ण
	skb_dst_drop(skb);
पूर्ण

पूर्णांक ip_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक err;

	अगर (level != SOL_IP)
		वापस -ENOPROTOOPT;

	err = करो_ip_setsockopt(sk, level, optname, optval, optlen);
#अगर IS_ENABLED(CONFIG_BPFILTER_UMH)
	अगर (optname >= BPFILTER_IPT_SO_SET_REPLACE &&
	    optname < BPFILTER_IPT_SET_MAX)
		err = bpfilter_ip_set_sockopt(sk, optname, optval, optlen);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER
	/* we need to exclude all possible ENOPROTOOPTs except शेष हाल */
	अगर (err == -ENOPROTOOPT && optname != IP_HDRINCL &&
			optname != IP_IPSEC_POLICY &&
			optname != IP_XFRM_POLICY &&
			!ip_mroute_opt(optname))
		err = nf_setsockopt(sk, PF_INET, optname, optval, optlen);
#पूर्ण_अगर
	वापस err;
पूर्ण
EXPORT_SYMBOL(ip_setsockopt);

/*
 *	Get the options. Note क्रम future reference. The GET of IP options माला_लो
 *	the _received_ ones. The set sets the _sent_ ones.
 */

अटल bool माला_लोockopt_needs_rtnl(पूर्णांक optname)
अणु
	चयन (optname) अणु
	हाल IP_MSFILTER:
	हाल MCAST_MSFILTER:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक ip_get_mcast_msfilter(काष्ठा sock *sk, व्योम __user *optval,
		पूर्णांक __user *optlen, पूर्णांक len)
अणु
	स्थिर पूर्णांक size0 = दुरत्व(काष्ठा group_filter, gf_slist);
	काष्ठा group_filter __user *p = optval;
	काष्ठा group_filter gsf;
	पूर्णांक num;
	पूर्णांक err;

	अगर (len < size0)
		वापस -EINVAL;
	अगर (copy_from_user(&gsf, p, size0))
		वापस -EFAULT;

	num = gsf.gf_numsrc;
	err = ip_mc_gsfget(sk, &gsf, p->gf_slist);
	अगर (err)
		वापस err;
	अगर (gsf.gf_numsrc < num)
		num = gsf.gf_numsrc;
	अगर (put_user(GROUP_FILTER_SIZE(num), optlen) ||
	    copy_to_user(p, &gsf, size0))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_ip_get_mcast_msfilter(काष्ठा sock *sk, व्योम __user *optval,
		पूर्णांक __user *optlen, पूर्णांक len)
अणु
	स्थिर पूर्णांक size0 = दुरत्व(काष्ठा compat_group_filter, gf_slist);
	काष्ठा compat_group_filter __user *p = optval;
	काष्ठा compat_group_filter gf32;
	काष्ठा group_filter gf;
	पूर्णांक num;
	पूर्णांक err;

	अगर (len < size0)
		वापस -EINVAL;
	अगर (copy_from_user(&gf32, p, size0))
		वापस -EFAULT;

	gf.gf_पूर्णांकerface = gf32.gf_पूर्णांकerface;
	gf.gf_भ_शेषe = gf32.gf_भ_शेषe;
	num = gf.gf_numsrc = gf32.gf_numsrc;
	gf.gf_group = gf32.gf_group;

	err = ip_mc_gsfget(sk, &gf, p->gf_slist);
	अगर (err)
		वापस err;
	अगर (gf.gf_numsrc < num)
		num = gf.gf_numsrc;
	len = GROUP_FILTER_SIZE(num) - (माप(gf) - माप(gf32));
	अगर (put_user(len, optlen) ||
	    put_user(gf.gf_भ_शेषe, &p->gf_भ_शेषe) ||
	    put_user(gf.gf_numsrc, &p->gf_numsrc))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_ip_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	bool needs_rtnl = माला_लोockopt_needs_rtnl(optname);
	पूर्णांक val, err = 0;
	पूर्णांक len;

	अगर (level != SOL_IP)
		वापस -EOPNOTSUPP;

	अगर (ip_mroute_opt(optname))
		वापस ip_mroute_माला_लोockopt(sk, optname, optval, optlen);

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < 0)
		वापस -EINVAL;

	अगर (needs_rtnl)
		rtnl_lock();
	lock_sock(sk);

	चयन (optname) अणु
	हाल IP_OPTIONS:
	अणु
		अचिन्हित अक्षर optbuf[माप(काष्ठा ip_options)+40];
		काष्ठा ip_options *opt = (काष्ठा ip_options *)optbuf;
		काष्ठा ip_options_rcu *inet_opt;

		inet_opt = rcu_dereference_रक्षित(inet->inet_opt,
						     lockdep_sock_is_held(sk));
		opt->optlen = 0;
		अगर (inet_opt)
			स_नकल(optbuf, &inet_opt->opt,
			       माप(काष्ठा ip_options) +
			       inet_opt->opt.optlen);
		release_sock(sk);

		अगर (opt->optlen == 0)
			वापस put_user(0, optlen);

		ip_options_unकरो(opt);

		len = min_t(अचिन्हित पूर्णांक, len, opt->optlen);
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, opt->__data, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल IP_PKTINFO:
		val = (inet->cmsg_flags & IP_CMSG_PKTINFO) != 0;
		अवरोध;
	हाल IP_RECVTTL:
		val = (inet->cmsg_flags & IP_CMSG_TTL) != 0;
		अवरोध;
	हाल IP_RECVTOS:
		val = (inet->cmsg_flags & IP_CMSG_TOS) != 0;
		अवरोध;
	हाल IP_RECVOPTS:
		val = (inet->cmsg_flags & IP_CMSG_RECVOPTS) != 0;
		अवरोध;
	हाल IP_RETOPTS:
		val = (inet->cmsg_flags & IP_CMSG_RETOPTS) != 0;
		अवरोध;
	हाल IP_PASSSEC:
		val = (inet->cmsg_flags & IP_CMSG_PASSSEC) != 0;
		अवरोध;
	हाल IP_RECVORIGDSTADDR:
		val = (inet->cmsg_flags & IP_CMSG_ORIGDSTADDR) != 0;
		अवरोध;
	हाल IP_CHECKSUM:
		val = (inet->cmsg_flags & IP_CMSG_CHECKSUM) != 0;
		अवरोध;
	हाल IP_RECVFRAGSIZE:
		val = (inet->cmsg_flags & IP_CMSG_RECVFRAGSIZE) != 0;
		अवरोध;
	हाल IP_TOS:
		val = inet->tos;
		अवरोध;
	हाल IP_TTL:
	अणु
		काष्ठा net *net = sock_net(sk);
		val = (inet->uc_ttl == -1 ?
		       net->ipv4.sysctl_ip_शेष_ttl :
		       inet->uc_ttl);
		अवरोध;
	पूर्ण
	हाल IP_HDRINCL:
		val = inet->hdrincl;
		अवरोध;
	हाल IP_NODEFRAG:
		val = inet->nodefrag;
		अवरोध;
	हाल IP_BIND_ADDRESS_NO_PORT:
		val = inet->bind_address_no_port;
		अवरोध;
	हाल IP_MTU_DISCOVER:
		val = inet->pmtudisc;
		अवरोध;
	हाल IP_MTU:
	अणु
		काष्ठा dst_entry *dst;
		val = 0;
		dst = sk_dst_get(sk);
		अगर (dst) अणु
			val = dst_mtu(dst);
			dst_release(dst);
		पूर्ण
		अगर (!val) अणु
			release_sock(sk);
			वापस -ENOTCONN;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल IP_RECVERR:
		val = inet->recverr;
		अवरोध;
	हाल IP_RECVERR_RFC4884:
		val = inet->recverr_rfc4884;
		अवरोध;
	हाल IP_MULTICAST_TTL:
		val = inet->mc_ttl;
		अवरोध;
	हाल IP_MULTICAST_LOOP:
		val = inet->mc_loop;
		अवरोध;
	हाल IP_UNICAST_IF:
		val = (__क्रमce पूर्णांक)htonl((__u32) inet->uc_index);
		अवरोध;
	हाल IP_MULTICAST_IF:
	अणु
		काष्ठा in_addr addr;
		len = min_t(अचिन्हित पूर्णांक, len, माप(काष्ठा in_addr));
		addr.s_addr = inet->mc_addr;
		release_sock(sk);

		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &addr, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल IP_MSFILTER:
	अणु
		काष्ठा ip_msfilter msf;

		अगर (len < IP_MSFILTER_SIZE(0)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (copy_from_user(&msf, optval, IP_MSFILTER_SIZE(0))) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण
		err = ip_mc_msfget(sk, &msf,
				   (काष्ठा ip_msfilter __user *)optval, optlen);
		जाओ out;
	पूर्ण
	हाल MCAST_MSFILTER:
		अगर (in_compat_syscall())
			err = compat_ip_get_mcast_msfilter(sk, optval, optlen,
							   len);
		अन्यथा
			err = ip_get_mcast_msfilter(sk, optval, optlen, len);
		जाओ out;
	हाल IP_MULTICAST_ALL:
		val = inet->mc_all;
		अवरोध;
	हाल IP_PKTOPTIONS:
	अणु
		काष्ठा msghdr msg;

		release_sock(sk);

		अगर (sk->sk_type != SOCK_STREAM)
			वापस -ENOPROTOOPT;

		msg.msg_control_is_user = true;
		msg.msg_control_user = optval;
		msg.msg_controllen = len;
		msg.msg_flags = in_compat_syscall() ? MSG_CMSG_COMPAT : 0;

		अगर (inet->cmsg_flags & IP_CMSG_PKTINFO) अणु
			काष्ठा in_pktinfo info;

			info.ipi_addr.s_addr = inet->inet_rcv_saddr;
			info.ipi_spec_dst.s_addr = inet->inet_rcv_saddr;
			info.ipi_अगरindex = inet->mc_index;
			put_cmsg(&msg, SOL_IP, IP_PKTINFO, माप(info), &info);
		पूर्ण
		अगर (inet->cmsg_flags & IP_CMSG_TTL) अणु
			पूर्णांक hlim = inet->mc_ttl;
			put_cmsg(&msg, SOL_IP, IP_TTL, माप(hlim), &hlim);
		पूर्ण
		अगर (inet->cmsg_flags & IP_CMSG_TOS) अणु
			पूर्णांक tos = inet->rcv_tos;
			put_cmsg(&msg, SOL_IP, IP_TOS, माप(tos), &tos);
		पूर्ण
		len -= msg.msg_controllen;
		वापस put_user(len, optlen);
	पूर्ण
	हाल IP_FREEBIND:
		val = inet->मुक्तbind;
		अवरोध;
	हाल IP_TRANSPARENT:
		val = inet->transparent;
		अवरोध;
	हाल IP_MINTTL:
		val = inet->min_ttl;
		अवरोध;
	शेष:
		release_sock(sk);
		वापस -ENOPROTOOPT;
	पूर्ण
	release_sock(sk);

	अगर (len < माप(पूर्णांक) && len > 0 && val >= 0 && val <= 255) अणु
		अचिन्हित अक्षर ucval = (अचिन्हित अक्षर)val;
		len = 1;
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &ucval, 1))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		len = min_t(अचिन्हित पूर्णांक, माप(पूर्णांक), len);
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &val, len))
			वापस -EFAULT;
	पूर्ण
	वापस 0;

out:
	release_sock(sk);
	अगर (needs_rtnl)
		rtnl_unlock();
	वापस err;
पूर्ण

पूर्णांक ip_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level,
		  पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक err;

	err = करो_ip_माला_लोockopt(sk, level, optname, optval, optlen);

#अगर IS_ENABLED(CONFIG_BPFILTER_UMH)
	अगर (optname >= BPFILTER_IPT_SO_GET_INFO &&
	    optname < BPFILTER_IPT_GET_MAX)
		err = bpfilter_ip_get_sockopt(sk, optname, optval, optlen);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER
	/* we need to exclude all possible ENOPROTOOPTs except शेष हाल */
	अगर (err == -ENOPROTOOPT && optname != IP_PKTOPTIONS &&
			!ip_mroute_opt(optname)) अणु
		पूर्णांक len;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		err = nf_माला_लोockopt(sk, PF_INET, optname, optval, &len);
		अगर (err >= 0)
			err = put_user(len, optlen);
		वापस err;
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण
EXPORT_SYMBOL(ip_माला_लोockopt);
