<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		RAW - implementation of IP "raw" sockets.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 * Fixes:
 *		Alan Cox	:	verअगरy_area() fixed up
 *		Alan Cox	:	ICMP error handling
 *		Alan Cox	:	EMSGSIZE अगर you send too big a packet
 *		Alan Cox	: 	Now uses generic datagrams and shared
 *					skbuff library. No more peek crashes,
 *					no more backlogs
 *		Alan Cox	:	Checks sk->broadcast.
 *		Alan Cox	:	Uses skb_मुक्त_datagram/skb_copy_datagram
 *		Alan Cox	:	Raw passes ip options too
 *		Alan Cox	:	Setsocketopt added
 *		Alan Cox	:	Fixed error वापस क्रम broadcasts
 *		Alan Cox	:	Removed wake_up calls
 *		Alan Cox	:	Use ttl/tos
 *		Alan Cox	:	Cleaned up old debugging
 *		Alan Cox	:	Use new kernel side addresses
 *	Arnt Gulbअक्रमsen	:	Fixed MSG_DONTROUTE in raw sockets.
 *		Alan Cox	:	BSD style RAW socket demultiplexing.
 *		Alan Cox	:	Beginnings of mrouted support.
 *		Alan Cox	:	Added IP_HDRINCL option.
 *		Alan Cox	:	Skip broadcast check अगर BSDism set.
 *		David S. Miller	:	New socket lookup architecture.
 */

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sockios.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/mroute.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in_route.h>
#समावेश <linux/route.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/igmp.h>
#समावेश <net/net_namespace.h>
#समावेश <net/dst.h>
#समावेश <net/sock.h>
#समावेश <linux/ip.h>
#समावेश <linux/net.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/raw.h>
#समावेश <net/snmp.h>
#समावेश <net/tcp_states.h>
#समावेश <net/inet_common.h>
#समावेश <net/checksum.h>
#समावेश <net/xfrm.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/compat.h>
#समावेश <linux/uपन.स>

काष्ठा raw_frag_vec अणु
	काष्ठा msghdr *msg;
	जोड़ अणु
		काष्ठा icmphdr icmph;
		अक्षर c[1];
	पूर्ण hdr;
	पूर्णांक hlen;
पूर्ण;

काष्ठा raw_hashinfo raw_v4_hashinfo = अणु
	.lock = __RW_LOCK_UNLOCKED(raw_v4_hashinfo.lock),
पूर्ण;
EXPORT_SYMBOL_GPL(raw_v4_hashinfo);

पूर्णांक raw_hash_sk(काष्ठा sock *sk)
अणु
	काष्ठा raw_hashinfo *h = sk->sk_prot->h.raw_hash;
	काष्ठा hlist_head *head;

	head = &h->ht[inet_sk(sk)->inet_num & (RAW_HTABLE_SIZE - 1)];

	ग_लिखो_lock_bh(&h->lock);
	sk_add_node(sk, head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	ग_लिखो_unlock_bh(&h->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(raw_hash_sk);

व्योम raw_unhash_sk(काष्ठा sock *sk)
अणु
	काष्ठा raw_hashinfo *h = sk->sk_prot->h.raw_hash;

	ग_लिखो_lock_bh(&h->lock);
	अगर (sk_del_node_init(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	ग_लिखो_unlock_bh(&h->lock);
पूर्ण
EXPORT_SYMBOL_GPL(raw_unhash_sk);

काष्ठा sock *__raw_v4_lookup(काष्ठा net *net, काष्ठा sock *sk,
			     अचिन्हित लघु num, __be32 raddr, __be32 laddr,
			     पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	sk_क्रम_each_from(sk) अणु
		काष्ठा inet_sock *inet = inet_sk(sk);

		अगर (net_eq(sock_net(sk), net) && inet->inet_num == num	&&
		    !(inet->inet_daddr && inet->inet_daddr != raddr) 	&&
		    !(inet->inet_rcv_saddr && inet->inet_rcv_saddr != laddr) &&
		    raw_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर, dअगर, sdअगर))
			जाओ found; /* gotcha */
	पूर्ण
	sk = शून्य;
found:
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(__raw_v4_lookup);

/*
 *	0 - deliver
 *	1 - block
 */
अटल पूर्णांक icmp_filter(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा icmphdr _hdr;
	स्थिर काष्ठा icmphdr *hdr;

	hdr = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
				 माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस 1;

	अगर (hdr->type < 32) अणु
		__u32 data = raw_sk(sk)->filter.data;

		वापस ((1U << hdr->type) & data) != 0;
	पूर्ण

	/* Do not block unknown ICMP types */
	वापस 0;
पूर्ण

/* IP input processing comes here क्रम RAW socket delivery.
 * Caller owns SKB, so we must make clones.
 *
 * RFC 1122: SHOULD pass TOS value up to the transport layer.
 * -> It करोes. And not only TOS, but all IP header.
 */
अटल पूर्णांक raw_v4_input(काष्ठा sk_buff *skb, स्थिर काष्ठा iphdr *iph, पूर्णांक hash)
अणु
	पूर्णांक sdअगर = inet_sdअगर(skb);
	पूर्णांक dअगर = inet_iअगर(skb);
	काष्ठा sock *sk;
	काष्ठा hlist_head *head;
	पूर्णांक delivered = 0;
	काष्ठा net *net;

	पढ़ो_lock(&raw_v4_hashinfo.lock);
	head = &raw_v4_hashinfo.ht[hash];
	अगर (hlist_empty(head))
		जाओ out;

	net = dev_net(skb->dev);
	sk = __raw_v4_lookup(net, __sk_head(head), iph->protocol,
			     iph->saddr, iph->daddr, dअगर, sdअगर);

	जबतक (sk) अणु
		delivered = 1;
		अगर ((iph->protocol != IPPROTO_ICMP || !icmp_filter(sk, skb)) &&
		    ip_mc_sf_allow(sk, iph->daddr, iph->saddr,
				   skb->dev->अगरindex, sdअगर)) अणु
			काष्ठा sk_buff *clone = skb_clone(skb, GFP_ATOMIC);

			/* Not releasing hash table! */
			अगर (clone)
				raw_rcv(sk, clone);
		पूर्ण
		sk = __raw_v4_lookup(net, sk_next(sk), iph->protocol,
				     iph->saddr, iph->daddr,
				     dअगर, sdअगर);
	पूर्ण
out:
	पढ़ो_unlock(&raw_v4_hashinfo.lock);
	वापस delivered;
पूर्ण

पूर्णांक raw_local_deliver(काष्ठा sk_buff *skb, पूर्णांक protocol)
अणु
	पूर्णांक hash;
	काष्ठा sock *raw_sk;

	hash = protocol & (RAW_HTABLE_SIZE - 1);
	raw_sk = sk_head(&raw_v4_hashinfo.ht[hash]);

	/* If there maybe a raw socket we must check - अगर not we
	 * करोn't care less
	 */
	अगर (raw_sk && !raw_v4_input(skb, ip_hdr(skb), hash))
		raw_sk = शून्य;

	वापस raw_sk != शून्य;

पूर्ण

अटल व्योम raw_err(काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	पूर्णांक err = 0;
	पूर्णांक harderr = 0;

	अगर (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED)
		ipv4_sk_update_pmtu(skb, sk, info);
	अन्यथा अगर (type == ICMP_REसूचीECT) अणु
		ipv4_sk_redirect(skb, sk);
		वापस;
	पूर्ण

	/* Report error on raw socket, अगर:
	   1. User requested ip_recverr.
	   2. Socket is connected (otherwise the error indication
	      is useless without ip_recverr and error is hard.
	 */
	अगर (!inet->recverr && sk->sk_state != TCP_ESTABLISHED)
		वापस;

	चयन (type) अणु
	शेष:
	हाल ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		अवरोध;
	हाल ICMP_SOURCE_QUENCH:
		वापस;
	हाल ICMP_PARAMETERPROB:
		err = EPROTO;
		harderr = 1;
		अवरोध;
	हाल ICMP_DEST_UNREACH:
		err = EHOSTUNREACH;
		अगर (code > NR_ICMP_UNREACH)
			अवरोध;
		अगर (code == ICMP_FRAG_NEEDED) अणु
			harderr = inet->pmtudisc != IP_PMTUDISC_DONT;
			err = EMSGSIZE;
		पूर्ण अन्यथा अणु
			err = icmp_err_convert[code].त्रुटि_सं;
			harderr = icmp_err_convert[code].fatal;
		पूर्ण
	पूर्ण

	अगर (inet->recverr) अणु
		स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
		u8 *payload = skb->data + (iph->ihl << 2);

		अगर (inet->hdrincl)
			payload = skb->data;
		ip_icmp_error(sk, skb, err, 0, info, payload);
	पूर्ण

	अगर (inet->recverr || harderr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण
पूर्ण

व्योम raw_icmp_error(काष्ठा sk_buff *skb, पूर्णांक protocol, u32 info)
अणु
	पूर्णांक hash;
	काष्ठा sock *raw_sk;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा net *net;

	hash = protocol & (RAW_HTABLE_SIZE - 1);

	पढ़ो_lock(&raw_v4_hashinfo.lock);
	raw_sk = sk_head(&raw_v4_hashinfo.ht[hash]);
	अगर (raw_sk) अणु
		पूर्णांक dअगर = skb->dev->अगरindex;
		पूर्णांक sdअगर = inet_sdअगर(skb);

		iph = (स्थिर काष्ठा iphdr *)skb->data;
		net = dev_net(skb->dev);

		जबतक ((raw_sk = __raw_v4_lookup(net, raw_sk, protocol,
						iph->daddr, iph->saddr,
						dअगर, sdअगर)) != शून्य) अणु
			raw_err(raw_sk, skb, info);
			raw_sk = sk_next(raw_sk);
			iph = (स्थिर काष्ठा iphdr *)skb->data;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&raw_v4_hashinfo.lock);
पूर्ण

अटल पूर्णांक raw_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	/* Charge it to the socket. */

	ipv4_pktinfo_prepare(sk, skb);
	अगर (sock_queue_rcv_skb(sk, skb) < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण

पूर्णांक raw_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb)) अणु
		atomic_inc(&sk->sk_drops);
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण
	nf_reset_ct(skb);

	skb_push(skb, skb->data - skb_network_header(skb));

	raw_rcv_skb(sk, skb);
	वापस 0;
पूर्ण

अटल पूर्णांक raw_send_hdrinc(काष्ठा sock *sk, काष्ठा flowi4 *fl4,
			   काष्ठा msghdr *msg, माप_प्रकार length,
			   काष्ठा rtable **rtp, अचिन्हित पूर्णांक flags,
			   स्थिर काष्ठा sockcm_cookie *sockc)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा iphdr *iph;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक iphlen;
	पूर्णांक err;
	काष्ठा rtable *rt = *rtp;
	पूर्णांक hlen, tlen;

	अगर (length > rt->dst.dev->mtu) अणु
		ip_local_error(sk, EMSGSIZE, fl4->daddr, inet->inet_dport,
			       rt->dst.dev->mtu);
		वापस -EMSGSIZE;
	पूर्ण
	अगर (length < माप(काष्ठा iphdr))
		वापस -EINVAL;

	अगर (flags&MSG_PROBE)
		जाओ out;

	hlen = LL_RESERVED_SPACE(rt->dst.dev);
	tlen = rt->dst.dev->needed_tailroom;
	skb = sock_alloc_send_skb(sk,
				  length + hlen + tlen + 15,
				  flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		जाओ error;
	skb_reserve(skb, hlen);

	skb->priority = sk->sk_priority;
	skb->mark = sockc->mark;
	skb->tstamp = sockc->transmit_समय;
	skb_dst_set(skb, &rt->dst);
	*rtp = शून्य;

	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	skb_put(skb, length);

	skb->ip_summed = CHECKSUM_NONE;

	skb_setup_tx_बारtamp(skb, sockc->tsflags);

	अगर (flags & MSG_CONFIRM)
		skb_set_dst_pending_confirm(skb, 1);

	skb->transport_header = skb->network_header;
	err = -EFAULT;
	अगर (स_नकल_from_msg(iph, msg, length))
		जाओ error_मुक्त;

	iphlen = iph->ihl * 4;

	/*
	 * We करोn't want to modअगरy the ip header, but we करो need to
	 * be sure that it won't cause problems later aदीर्घ the network
	 * stack.  Specअगरically we want to make sure that iph->ihl is a
	 * sane value.  If ihl poपूर्णांकs beyond the length of the buffer passed
	 * in, reject the frame as invalid
	 */
	err = -EINVAL;
	अगर (iphlen > length)
		जाओ error_मुक्त;

	अगर (iphlen >= माप(*iph)) अणु
		अगर (!iph->saddr)
			iph->saddr = fl4->saddr;
		iph->check   = 0;
		iph->tot_len = htons(length);
		अगर (!iph->id)
			ip_select_ident(net, skb, शून्य);

		iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph, iph->ihl);
		skb->transport_header += iphlen;
		अगर (iph->protocol == IPPROTO_ICMP &&
		    length >= iphlen + माप(काष्ठा icmphdr))
			icmp_out_count(net, ((काष्ठा icmphdr *)
				skb_transport_header(skb))->type);
	पूर्ण

	err = NF_HOOK(NFPROTO_IPV4, NF_INET_LOCAL_OUT,
		      net, sk, skb, शून्य, rt->dst.dev,
		      dst_output);
	अगर (err > 0)
		err = net_xmit_त्रुटि_सं(err);
	अगर (err)
		जाओ error;
out:
	वापस 0;

error_मुक्त:
	kमुक्त_skb(skb);
error:
	IP_INC_STATS(net, IPSTATS_MIB_OUTDISCARDS);
	अगर (err == -ENOBUFS && !inet->recverr)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक raw_probe_proto_opt(काष्ठा raw_frag_vec *rfv, काष्ठा flowi4 *fl4)
अणु
	पूर्णांक err;

	अगर (fl4->flowi4_proto != IPPROTO_ICMP)
		वापस 0;

	/* We only need the first two bytes. */
	rfv->hlen = 2;

	err = स_नकल_from_msg(rfv->hdr.c, rfv->msg, rfv->hlen);
	अगर (err)
		वापस err;

	fl4->fl4_icmp_type = rfv->hdr.icmph.type;
	fl4->fl4_icmp_code = rfv->hdr.icmph.code;

	वापस 0;
पूर्ण

अटल पूर्णांक raw_getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len, पूर्णांक odd,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा raw_frag_vec *rfv = from;

	अगर (offset < rfv->hlen) अणु
		पूर्णांक copy = min(rfv->hlen - offset, len);

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			स_नकल(to, rfv->hdr.c + offset, copy);
		अन्यथा
			skb->csum = csum_block_add(
				skb->csum,
				csum_partial_copy_nocheck(rfv->hdr.c + offset,
							  to, copy),
				odd);

		odd = 0;
		offset += copy;
		to += copy;
		len -= copy;

		अगर (!len)
			वापस 0;
	पूर्ण

	offset -= rfv->hlen;

	वापस ip_generic_getfrag(rfv->msg, to, offset, len, odd, skb);
पूर्ण

अटल पूर्णांक raw_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा ipcm_cookie ipc;
	काष्ठा rtable *rt = शून्य;
	काष्ठा flowi4 fl4;
	पूर्णांक मुक्त = 0;
	__be32 daddr;
	__be32 saddr;
	u8  tos;
	पूर्णांक err;
	काष्ठा ip_options_data opt_copy;
	काष्ठा raw_frag_vec rfv;
	पूर्णांक hdrincl;

	err = -EMSGSIZE;
	अगर (len > 0xFFFF)
		जाओ out;

	/* hdrincl should be READ_ONCE(inet->hdrincl)
	 * but READ_ONCE() करोesn't work with bit fields.
	 * Doing this indirectly yields the same result.
	 */
	hdrincl = inet->hdrincl;
	hdrincl = READ_ONCE(hdrincl);
	/*
	 *	Check the flags.
	 */

	err = -EOPNOTSUPP;
	अगर (msg->msg_flags & MSG_OOB)	/* Mirror BSD error message */
		जाओ out;               /* compatibility */

	/*
	 *	Get and verअगरy the address.
	 */

	अगर (msg->msg_namelen) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_in *, usin, msg->msg_name);
		err = -EINVAL;
		अगर (msg->msg_namelen < माप(*usin))
			जाओ out;
		अगर (usin->sin_family != AF_INET) अणु
			pr_info_once("%s: %s forgot to set AF_INET. Fix it!\n",
				     __func__, current->comm);
			err = -EAFNOSUPPORT;
			अगर (usin->sin_family)
				जाओ out;
		पूर्ण
		daddr = usin->sin_addr.s_addr;
		/* ANK: I did not क्रमget to get protocol from port field.
		 * I just करो not know, who uses this weirdness.
		 * IP_HDRINCL is much more convenient.
		 */
	पूर्ण अन्यथा अणु
		err = -EDESTADDRREQ;
		अगर (sk->sk_state != TCP_ESTABLISHED)
			जाओ out;
		daddr = inet->inet_daddr;
	पूर्ण

	ipcm_init_sk(&ipc, inet);

	अगर (msg->msg_controllen) अणु
		err = ip_cmsg_send(sk, msg, &ipc, false);
		अगर (unlikely(err)) अणु
			kमुक्त(ipc.opt);
			जाओ out;
		पूर्ण
		अगर (ipc.opt)
			मुक्त = 1;
	पूर्ण

	saddr = ipc.addr;
	ipc.addr = daddr;

	अगर (!ipc.opt) अणु
		काष्ठा ip_options_rcu *inet_opt;

		rcu_पढ़ो_lock();
		inet_opt = rcu_dereference(inet->inet_opt);
		अगर (inet_opt) अणु
			स_नकल(&opt_copy, inet_opt,
			       माप(*inet_opt) + inet_opt->opt.optlen);
			ipc.opt = &opt_copy.opt;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (ipc.opt) अणु
		err = -EINVAL;
		/* Linux करोes not mangle headers on raw sockets,
		 * so that IP options + IP_HDRINCL is non-sense.
		 */
		अगर (hdrincl)
			जाओ करोne;
		अगर (ipc.opt->opt.srr) अणु
			अगर (!daddr)
				जाओ करोne;
			daddr = ipc.opt->opt.faddr;
		पूर्ण
	पूर्ण
	tos = get_rtconn_flags(&ipc, sk);
	अगर (msg->msg_flags & MSG_DONTROUTE)
		tos |= RTO_ONLINK;

	अगर (ipv4_is_multicast(daddr)) अणु
		अगर (!ipc.oअगर || netअगर_index_is_l3_master(sock_net(sk), ipc.oअगर))
			ipc.oअगर = inet->mc_index;
		अगर (!saddr)
			saddr = inet->mc_addr;
	पूर्ण अन्यथा अगर (!ipc.oअगर) अणु
		ipc.oअगर = inet->uc_index;
	पूर्ण अन्यथा अगर (ipv4_is_lbcast(daddr) && inet->uc_index) अणु
		/* oअगर is set, packet is to local broadcast
		 * and uc_index is set. oअगर is most likely set
		 * by sk_bound_dev_अगर. If uc_index != oअगर check अगर the
		 * oअगर is an L3 master and uc_index is an L3 slave.
		 * If so, we want to allow the send using the uc_index.
		 */
		अगर (ipc.oअगर != inet->uc_index &&
		    ipc.oअगर == l3mdev_master_अगरindex_by_index(sock_net(sk),
							      inet->uc_index)) अणु
			ipc.oअगर = inet->uc_index;
		पूर्ण
	पूर्ण

	flowi4_init_output(&fl4, ipc.oअगर, ipc.sockc.mark, tos,
			   RT_SCOPE_UNIVERSE,
			   hdrincl ? IPPROTO_RAW : sk->sk_protocol,
			   inet_sk_flowi_flags(sk) |
			    (hdrincl ? FLOWI_FLAG_KNOWN_NH : 0),
			   daddr, saddr, 0, 0, sk->sk_uid);

	अगर (!hdrincl) अणु
		rfv.msg = msg;
		rfv.hlen = 0;

		err = raw_probe_proto_opt(&rfv, &fl4);
		अगर (err)
			जाओ करोne;
	पूर्ण

	security_sk_classअगरy_flow(sk, flowi4_to_flowi_common(&fl4));
	rt = ip_route_output_flow(net, &fl4, sk);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		rt = शून्य;
		जाओ करोne;
	पूर्ण

	err = -EACCES;
	अगर (rt->rt_flags & RTCF_BROADCAST && !sock_flag(sk, SOCK_BROADCAST))
		जाओ करोne;

	अगर (msg->msg_flags & MSG_CONFIRM)
		जाओ करो_confirm;
back_from_confirm:

	अगर (hdrincl)
		err = raw_send_hdrinc(sk, &fl4, msg, len,
				      &rt, msg->msg_flags, &ipc.sockc);

	 अन्यथा अणु
		अगर (!ipc.addr)
			ipc.addr = fl4.daddr;
		lock_sock(sk);
		err = ip_append_data(sk, &fl4, raw_getfrag,
				     &rfv, len, 0,
				     &ipc, &rt, msg->msg_flags);
		अगर (err)
			ip_flush_pending_frames(sk);
		अन्यथा अगर (!(msg->msg_flags & MSG_MORE)) अणु
			err = ip_push_pending_frames(sk, &fl4);
			अगर (err == -ENOBUFS && !inet->recverr)
				err = 0;
		पूर्ण
		release_sock(sk);
	पूर्ण
करोne:
	अगर (मुक्त)
		kमुक्त(ipc.opt);
	ip_rt_put(rt);

out:
	अगर (err < 0)
		वापस err;
	वापस len;

करो_confirm:
	अगर (msg->msg_flags & MSG_PROBE)
		dst_confirm_neigh(&rt->dst, &fl4.daddr);
	अगर (!(msg->msg_flags & MSG_PROBE) || len)
		जाओ back_from_confirm;
	err = 0;
	जाओ करोne;
पूर्ण

अटल व्योम raw_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	/*
	 * Raw sockets may have direct kernel references. Kill them.
	 */
	ip_ra_control(sk, 0, शून्य);

	sk_common_release(sk);
पूर्ण

अटल व्योम raw_destroy(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	ip_flush_pending_frames(sk);
	release_sock(sk);
पूर्ण

/* This माला_लो rid of all the nasties in af_inet. -DaveM */
अटल पूर्णांक raw_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sockaddr_in *addr = (काष्ठा sockaddr_in *) uaddr;
	u32 tb_id = RT_TABLE_LOCAL;
	पूर्णांक ret = -EINVAL;
	पूर्णांक chk_addr_ret;

	अगर (sk->sk_state != TCP_CLOSE || addr_len < माप(काष्ठा sockaddr_in))
		जाओ out;

	अगर (sk->sk_bound_dev_अगर)
		tb_id = l3mdev_fib_table_by_index(sock_net(sk),
						 sk->sk_bound_dev_अगर) ? : tb_id;

	chk_addr_ret = inet_addr_type_table(sock_net(sk), addr->sin_addr.s_addr,
					    tb_id);

	ret = -EADDRNOTAVAIL;
	अगर (addr->sin_addr.s_addr && chk_addr_ret != RTN_LOCAL &&
	    chk_addr_ret != RTN_MULTICAST && chk_addr_ret != RTN_BROADCAST)
		जाओ out;
	inet->inet_rcv_saddr = inet->inet_saddr = addr->sin_addr.s_addr;
	अगर (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
		inet->inet_saddr = 0;  /* Use device */
	sk_dst_reset(sk);
	ret = 0;
out:	वापस ret;
पूर्ण

/*
 *	This should be easy, अगर there is something there
 *	we वापस it, otherwise we block.
 */

अटल पूर्णांक raw_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		       पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	माप_प्रकार copied = 0;
	पूर्णांक err = -EOPNOTSUPP;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, msg->msg_name);
	काष्ठा sk_buff *skb;

	अगर (flags & MSG_OOB)
		जाओ out;

	अगर (flags & MSG_ERRQUEUE) अणु
		err = ip_recv_error(sk, msg, len, addr_len);
		जाओ out;
	पूर्ण

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ करोne;

	sock_recv_ts_and_drops(msg, sk, skb);

	/* Copy the address. */
	अगर (sin) अणु
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = ip_hdr(skb)->saddr;
		sin->sin_port = 0;
		स_रखो(&sin->sin_zero, 0, माप(sin->sin_zero));
		*addr_len = माप(*sin);
	पूर्ण
	अगर (inet->cmsg_flags)
		ip_cmsg_recv(msg, skb);
	अगर (flags & MSG_TRUNC)
		copied = skb->len;
करोne:
	skb_मुक्त_datagram(sk, skb);
out:
	अगर (err)
		वापस err;
	वापस copied;
पूर्ण

अटल पूर्णांक raw_sk_init(काष्ठा sock *sk)
अणु
	काष्ठा raw_sock *rp = raw_sk(sk);

	अगर (inet_sk(sk)->inet_num == IPPROTO_ICMP)
		स_रखो(&rp->filter, 0, माप(rp->filter));
	वापस 0;
पूर्ण

अटल पूर्णांक raw_seticmpfilter(काष्ठा sock *sk, sockptr_t optval, पूर्णांक optlen)
अणु
	अगर (optlen > माप(काष्ठा icmp_filter))
		optlen = माप(काष्ठा icmp_filter);
	अगर (copy_from_sockptr(&raw_sk(sk)->filter, optval, optlen))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक raw_geticmpfilter(काष्ठा sock *sk, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक len, ret = -EFAULT;

	अगर (get_user(len, optlen))
		जाओ out;
	ret = -EINVAL;
	अगर (len < 0)
		जाओ out;
	अगर (len > माप(काष्ठा icmp_filter))
		len = माप(काष्ठा icmp_filter);
	ret = -EFAULT;
	अगर (put_user(len, optlen) ||
	    copy_to_user(optval, &raw_sk(sk)->filter, len))
		जाओ out;
	ret = 0;
out:	वापस ret;
पूर्ण

अटल पूर्णांक करो_raw_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			     sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	अगर (optname == ICMP_FILTER) अणु
		अगर (inet_sk(sk)->inet_num != IPPROTO_ICMP)
			वापस -EOPNOTSUPP;
		अन्यथा
			वापस raw_seticmpfilter(sk, optval, optlen);
	पूर्ण
	वापस -ENOPROTOOPT;
पूर्ण

अटल पूर्णांक raw_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	अगर (level != SOL_RAW)
		वापस ip_setsockopt(sk, level, optname, optval, optlen);
	वापस करो_raw_setsockopt(sk, level, optname, optval, optlen);
पूर्ण

अटल पूर्णांक करो_raw_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	अगर (optname == ICMP_FILTER) अणु
		अगर (inet_sk(sk)->inet_num != IPPROTO_ICMP)
			वापस -EOPNOTSUPP;
		अन्यथा
			वापस raw_geticmpfilter(sk, optval, optlen);
	पूर्ण
	वापस -ENOPROTOOPT;
पूर्ण

अटल पूर्णांक raw_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	अगर (level != SOL_RAW)
		वापस ip_माला_लोockopt(sk, level, optname, optval, optlen);
	वापस करो_raw_माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण

अटल पूर्णांक raw_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SIOCOUTQ: अणु
		पूर्णांक amount = sk_wmem_alloc_get(sk);

		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण
	हाल SIOCINQ: अणु
		काष्ठा sk_buff *skb;
		पूर्णांक amount = 0;

		spin_lock_bh(&sk->sk_receive_queue.lock);
		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb)
			amount = skb->len;
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण

	शेष:
#अगर_घोषित CONFIG_IP_MROUTE
		वापस ipmr_ioctl(sk, cmd, (व्योम __user *)arg);
#अन्यथा
		वापस -ENOIOCTLCMD;
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_raw_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SIOCOUTQ:
	हाल SIOCINQ:
		वापस -ENOIOCTLCMD;
	शेष:
#अगर_घोषित CONFIG_IP_MROUTE
		वापस ipmr_compat_ioctl(sk, cmd, compat_ptr(arg));
#अन्यथा
		वापस -ENOIOCTLCMD;
#पूर्ण_अगर
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक raw_पात(काष्ठा sock *sk, पूर्णांक err)
अणु
	lock_sock(sk);

	sk->sk_err = err;
	sk->sk_error_report(sk);
	__udp_disconnect(sk, 0);

	release_sock(sk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(raw_पात);

काष्ठा proto raw_prot = अणु
	.name		   = "RAW",
	.owner		   = THIS_MODULE,
	.बंद		   = raw_बंद,
	.destroy	   = raw_destroy,
	.connect	   = ip4_datagram_connect,
	.disconnect	   = __udp_disconnect,
	.ioctl		   = raw_ioctl,
	.init		   = raw_sk_init,
	.setsockopt	   = raw_setsockopt,
	.माला_लोockopt	   = raw_माला_लोockopt,
	.sendmsg	   = raw_sendmsg,
	.recvmsg	   = raw_recvmsg,
	.bind		   = raw_bind,
	.backlog_rcv	   = raw_rcv_skb,
	.release_cb	   = ip4_datagram_release_cb,
	.hash		   = raw_hash_sk,
	.unhash		   = raw_unhash_sk,
	.obj_size	   = माप(काष्ठा raw_sock),
	.useroffset	   = दुरत्व(काष्ठा raw_sock, filter),
	.usersize	   = माप_field(काष्ठा raw_sock, filter),
	.h.raw_hash	   = &raw_v4_hashinfo,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = compat_raw_ioctl,
#पूर्ण_अगर
	.diag_destroy	   = raw_पात,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा sock *raw_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा sock *sk;
	काष्ठा raw_hashinfo *h = PDE_DATA(file_inode(seq->file));
	काष्ठा raw_iter_state *state = raw_seq_निजी(seq);

	क्रम (state->bucket = 0; state->bucket < RAW_HTABLE_SIZE;
			++state->bucket) अणु
		sk_क्रम_each(sk, &h->ht[state->bucket])
			अगर (sock_net(sk) == seq_file_net(seq))
				जाओ found;
	पूर्ण
	sk = शून्य;
found:
	वापस sk;
पूर्ण

अटल काष्ठा sock *raw_get_next(काष्ठा seq_file *seq, काष्ठा sock *sk)
अणु
	काष्ठा raw_hashinfo *h = PDE_DATA(file_inode(seq->file));
	काष्ठा raw_iter_state *state = raw_seq_निजी(seq);

	करो अणु
		sk = sk_next(sk);
try_again:
		;
	पूर्ण जबतक (sk && sock_net(sk) != seq_file_net(seq));

	अगर (!sk && ++state->bucket < RAW_HTABLE_SIZE) अणु
		sk = sk_head(&h->ht[state->bucket]);
		जाओ try_again;
	पूर्ण
	वापस sk;
पूर्ण

अटल काष्ठा sock *raw_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा sock *sk = raw_get_first(seq);

	अगर (sk)
		जबतक (pos && (sk = raw_get_next(seq, sk)) != शून्य)
			--pos;
	वापस pos ? शून्य : sk;
पूर्ण

व्योम *raw_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(&h->lock)
अणु
	काष्ठा raw_hashinfo *h = PDE_DATA(file_inode(seq->file));

	पढ़ो_lock(&h->lock);
	वापस *pos ? raw_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण
EXPORT_SYMBOL_GPL(raw_seq_start);

व्योम *raw_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sock *sk;

	अगर (v == SEQ_START_TOKEN)
		sk = raw_get_first(seq);
	अन्यथा
		sk = raw_get_next(seq, v);
	++*pos;
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(raw_seq_next);

व्योम raw_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(&h->lock)
अणु
	काष्ठा raw_hashinfo *h = PDE_DATA(file_inode(seq->file));

	पढ़ो_unlock(&h->lock);
पूर्ण
EXPORT_SYMBOL_GPL(raw_seq_stop);

अटल व्योम raw_sock_seq_show(काष्ठा seq_file *seq, काष्ठा sock *sp, पूर्णांक i)
अणु
	काष्ठा inet_sock *inet = inet_sk(sp);
	__be32 dest = inet->inet_daddr,
	       src = inet->inet_rcv_saddr;
	__u16 destp = 0,
	      srcp  = inet->inet_num;

	seq_म_लिखो(seq, "%4d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %u\n",
		i, src, srcp, dest, destp, sp->sk_state,
		sk_wmem_alloc_get(sp),
		sk_rmem_alloc_get(sp),
		0, 0L, 0,
		from_kuid_munged(seq_user_ns(seq), sock_i_uid(sp)),
		0, sock_i_ino(sp),
		refcount_पढ़ो(&sp->sk_refcnt), sp, atomic_पढ़ो(&sp->sk_drops));
पूर्ण

अटल पूर्णांक raw_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(seq, "  sl  local_address rem_address   st tx_queue "
				"rx_queue tr tm->when retrnsmt   uid  timeout "
				"inode ref pointer drops\n");
	अन्यथा
		raw_sock_seq_show(seq, v, raw_seq_निजी(seq)->bucket);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations raw_seq_ops = अणु
	.start = raw_seq_start,
	.next  = raw_seq_next,
	.stop  = raw_seq_stop,
	.show  = raw_seq_show,
पूर्ण;

अटल __net_init पूर्णांक raw_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("raw", 0444, net->proc_net, &raw_seq_ops,
			माप(काष्ठा raw_iter_state), &raw_v4_hashinfo))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल __net_निकास व्योम raw_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("raw", net->proc_net);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations raw_net_ops = अणु
	.init = raw_init_net,
	.निकास = raw_निकास_net,
पूर्ण;

पूर्णांक __init raw_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&raw_net_ops);
पूर्ण

व्योम __init raw_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&raw_net_ops);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम raw_sysctl_init_net(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	net->ipv4.sysctl_raw_l3mdev_accept = 1;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __net_init raw_sysctl_init(काष्ठा net *net)
अणु
	raw_sysctl_init_net(net);
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations __net_initdata raw_sysctl_ops = अणु
	.init	= raw_sysctl_init,
पूर्ण;

व्योम __init raw_init(व्योम)
अणु
	raw_sysctl_init_net(&init_net);
	अगर (रेजिस्टर_pernet_subsys(&raw_sysctl_ops))
		panic("RAW: failed to init sysctl parameters.\n");
पूर्ण
