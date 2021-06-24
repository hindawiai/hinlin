<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	RAW sockets क्रम IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Adapted from linux/net/ipv4/raw.c
 *
 *	Fixes:
 *	Hideaki YOSHIFUJI	:	sin6_scope_id support
 *	YOSHIFUJI,H.@USAGI	:	raw checksum (RFC2292(bis) compliance)
 *	Kazunori MIYAZAWA @USAGI:	change process style to use ip6_append_data
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/slab.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/compat.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>

#समावेश <net/net_namespace.h>
#समावेश <net/ip.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/protocol.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/addrconf.h>
#समावेश <net/transp_v6.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp_states.h>
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
#समावेश <net/mip6.h>
#पूर्ण_अगर
#समावेश <linux/mroute6.h>

#समावेश <net/raw.h>
#समावेश <net/rawv6.h>
#समावेश <net/xfrm.h>

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>

#घोषणा	ICMPV6_HDRLEN	4	/* ICMPv6 header, RFC 4443 Section 2.1 */

काष्ठा raw_hashinfo raw_v6_hashinfo = अणु
	.lock = __RW_LOCK_UNLOCKED(raw_v6_hashinfo.lock),
पूर्ण;
EXPORT_SYMBOL_GPL(raw_v6_hashinfo);

काष्ठा sock *__raw_v6_lookup(काष्ठा net *net, काष्ठा sock *sk,
		अचिन्हित लघु num, स्थिर काष्ठा in6_addr *loc_addr,
		स्थिर काष्ठा in6_addr *rmt_addr, पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	bool is_multicast = ipv6_addr_is_multicast(loc_addr);

	sk_क्रम_each_from(sk)
		अगर (inet_sk(sk)->inet_num == num) अणु

			अगर (!net_eq(sock_net(sk), net))
				जारी;

			अगर (!ipv6_addr_any(&sk->sk_v6_daddr) &&
			    !ipv6_addr_equal(&sk->sk_v6_daddr, rmt_addr))
				जारी;

			अगर (!raw_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर,
						 dअगर, sdअगर))
				जारी;

			अगर (!ipv6_addr_any(&sk->sk_v6_rcv_saddr)) अणु
				अगर (ipv6_addr_equal(&sk->sk_v6_rcv_saddr, loc_addr))
					जाओ found;
				अगर (is_multicast &&
				    inet6_mc_check(sk, loc_addr, rmt_addr))
					जाओ found;
				जारी;
			पूर्ण
			जाओ found;
		पूर्ण
	sk = शून्य;
found:
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(__raw_v6_lookup);

/*
 *	0 - deliver
 *	1 - block
 */
अटल पूर्णांक icmpv6_filter(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा icmp6hdr _hdr;
	स्थिर काष्ठा icmp6hdr *hdr;

	/* We require only the four bytes of the ICMPv6 header, not any
	 * additional bytes of message body in "struct icmp6hdr".
	 */
	hdr = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
				 ICMPV6_HDRLEN, &_hdr);
	अगर (hdr) अणु
		स्थिर __u32 *data = &raw6_sk(sk)->filter.data[0];
		अचिन्हित पूर्णांक type = hdr->icmp6_type;

		वापस (data[type >> 5] & (1U << (type & 31))) != 0;
	पूर्ण
	वापस 1;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
प्रकार पूर्णांक mh_filter_t(काष्ठा sock *sock, काष्ठा sk_buff *skb);

अटल mh_filter_t __rcu *mh_filter __पढ़ो_mostly;

पूर्णांक rawv6_mh_filter_रेजिस्टर(mh_filter_t filter)
अणु
	rcu_assign_poपूर्णांकer(mh_filter, filter);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rawv6_mh_filter_रेजिस्टर);

पूर्णांक rawv6_mh_filter_unरेजिस्टर(mh_filter_t filter)
अणु
	RCU_INIT_POINTER(mh_filter, शून्य);
	synchronize_rcu();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rawv6_mh_filter_unरेजिस्टर);

#पूर्ण_अगर

/*
 *	demultiplex raw sockets.
 *	(should consider queueing the skb in the sock receive_queue
 *	without calling rawv6.c)
 *
 *	Caller owns SKB so we must make clones.
 */
अटल bool ipv6_raw_deliver(काष्ठा sk_buff *skb, पूर्णांक nexthdr)
अणु
	स्थिर काष्ठा in6_addr *saddr;
	स्थिर काष्ठा in6_addr *daddr;
	काष्ठा sock *sk;
	bool delivered = false;
	__u8 hash;
	काष्ठा net *net;

	saddr = &ipv6_hdr(skb)->saddr;
	daddr = saddr + 1;

	hash = nexthdr & (RAW_HTABLE_SIZE - 1);

	पढ़ो_lock(&raw_v6_hashinfo.lock);
	sk = sk_head(&raw_v6_hashinfo.ht[hash]);

	अगर (!sk)
		जाओ out;

	net = dev_net(skb->dev);
	sk = __raw_v6_lookup(net, sk, nexthdr, daddr, saddr,
			     inet6_iअगर(skb), inet6_sdअगर(skb));

	जबतक (sk) अणु
		पूर्णांक filtered;

		delivered = true;
		चयन (nexthdr) अणु
		हाल IPPROTO_ICMPV6:
			filtered = icmpv6_filter(sk, skb);
			अवरोध;

#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		हाल IPPROTO_MH:
		अणु
			/* XXX: To validate MH only once क्रम each packet,
			 * this is placed here. It should be after checking
			 * xfrm policy, however it करोesn't. The checking xfrm
			 * policy is placed in rawv6_rcv() because it is
			 * required क्रम each socket.
			 */
			mh_filter_t *filter;

			filter = rcu_dereference(mh_filter);
			filtered = filter ? (*filter)(sk, skb) : 0;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		शेष:
			filtered = 0;
			अवरोध;
		पूर्ण

		अगर (filtered < 0)
			अवरोध;
		अगर (filtered == 0) अणु
			काष्ठा sk_buff *clone = skb_clone(skb, GFP_ATOMIC);

			/* Not releasing hash table! */
			अगर (clone) अणु
				nf_reset_ct(clone);
				rawv6_rcv(sk, clone);
			पूर्ण
		पूर्ण
		sk = __raw_v6_lookup(net, sk_next(sk), nexthdr, daddr, saddr,
				     inet6_iअगर(skb), inet6_sdअगर(skb));
	पूर्ण
out:
	पढ़ो_unlock(&raw_v6_hashinfo.lock);
	वापस delivered;
पूर्ण

bool raw6_local_deliver(काष्ठा sk_buff *skb, पूर्णांक nexthdr)
अणु
	काष्ठा sock *raw_sk;

	raw_sk = sk_head(&raw_v6_hashinfo.ht[nexthdr & (RAW_HTABLE_SIZE - 1)]);
	अगर (raw_sk && !ipv6_raw_deliver(skb, nexthdr))
		raw_sk = शून्य;

	वापस raw_sk != शून्य;
पूर्ण

/* This cleans up af_inet6 a bit. -DaveM */
अटल पूर्णांक rawv6_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sockaddr_in6 *addr = (काष्ठा sockaddr_in6 *) uaddr;
	__be32 v4addr = 0;
	पूर्णांक addr_type;
	पूर्णांक err;

	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	अगर (addr->sin6_family != AF_INET6)
		वापस -EINVAL;

	addr_type = ipv6_addr_type(&addr->sin6_addr);

	/* Raw sockets are IPv6 only */
	अगर (addr_type == IPV6_ADDR_MAPPED)
		वापस -EADDRNOTAVAIL;

	lock_sock(sk);

	err = -EINVAL;
	अगर (sk->sk_state != TCP_CLOSE)
		जाओ out;

	rcu_पढ़ो_lock();
	/* Check अगर the address beदीर्घs to the host. */
	अगर (addr_type != IPV6_ADDR_ANY) अणु
		काष्ठा net_device *dev = शून्य;

		अगर (__ipv6_addr_needs_scope_id(addr_type)) अणु
			अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
			    addr->sin6_scope_id) अणु
				/* Override any existing binding, अगर another
				 * one is supplied by user.
				 */
				sk->sk_bound_dev_अगर = addr->sin6_scope_id;
			पूर्ण

			/* Binding to link-local address requires an पूर्णांकerface */
			अगर (!sk->sk_bound_dev_अगर)
				जाओ out_unlock;
		पूर्ण

		अगर (sk->sk_bound_dev_अगर) अणु
			err = -ENODEV;
			dev = dev_get_by_index_rcu(sock_net(sk),
						   sk->sk_bound_dev_अगर);
			अगर (!dev)
				जाओ out_unlock;
		पूर्ण

		/* ipv4 addr of the socket is invalid.  Only the
		 * unspecअगरied and mapped address have a v4 equivalent.
		 */
		v4addr = LOOPBACK4_IPV6;
		अगर (!(addr_type & IPV6_ADDR_MULTICAST) &&
		    !ipv6_can_nonlocal_bind(sock_net(sk), inet)) अणु
			err = -EADDRNOTAVAIL;
			अगर (!ipv6_chk_addr(sock_net(sk), &addr->sin6_addr,
					   dev, 0)) अणु
				जाओ out_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	inet->inet_rcv_saddr = inet->inet_saddr = v4addr;
	sk->sk_v6_rcv_saddr = addr->sin6_addr;
	अगर (!(addr_type & IPV6_ADDR_MULTICAST))
		np->saddr = addr->sin6_addr;
	err = 0;
out_unlock:
	rcu_पढ़ो_unlock();
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल व्योम rawv6_err(काष्ठा sock *sk, काष्ठा sk_buff *skb,
	       काष्ठा inet6_skb_parm *opt,
	       u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	पूर्णांक err;
	पूर्णांक harderr;

	/* Report error on raw socket, अगर:
	   1. User requested recverr.
	   2. Socket is connected (otherwise the error indication
	      is useless without recverr and error is hard.
	 */
	अगर (!np->recverr && sk->sk_state != TCP_ESTABLISHED)
		वापस;

	harderr = icmpv6_err_convert(type, code, &err);
	अगर (type == ICMPV6_PKT_TOOBIG) अणु
		ip6_sk_update_pmtu(skb, sk, info);
		harderr = (np->pmtudisc == IPV6_PMTUDISC_DO);
	पूर्ण
	अगर (type == NDISC_REसूचीECT) अणु
		ip6_sk_redirect(skb, sk);
		वापस;
	पूर्ण
	अगर (np->recverr) अणु
		u8 *payload = skb->data;
		अगर (!inet->hdrincl)
			payload += offset;
		ipv6_icmp_error(sk, skb, err, 0, ntohl(info), payload);
	पूर्ण

	अगर (np->recverr || harderr) अणु
		sk->sk_err = err;
		sk->sk_error_report(sk);
	पूर्ण
पूर्ण

व्योम raw6_icmp_error(काष्ठा sk_buff *skb, पूर्णांक nexthdr,
		u8 type, u8 code, पूर्णांक inner_offset, __be32 info)
अणु
	काष्ठा sock *sk;
	पूर्णांक hash;
	स्थिर काष्ठा in6_addr *saddr, *daddr;
	काष्ठा net *net;

	hash = nexthdr & (RAW_HTABLE_SIZE - 1);

	पढ़ो_lock(&raw_v6_hashinfo.lock);
	sk = sk_head(&raw_v6_hashinfo.ht[hash]);
	अगर (sk) अणु
		/* Note: ipv6_hdr(skb) != skb->data */
		स्थिर काष्ठा ipv6hdr *ip6h = (स्थिर काष्ठा ipv6hdr *)skb->data;
		saddr = &ip6h->saddr;
		daddr = &ip6h->daddr;
		net = dev_net(skb->dev);

		जबतक ((sk = __raw_v6_lookup(net, sk, nexthdr, saddr, daddr,
					     inet6_iअगर(skb), inet6_iअगर(skb)))) अणु
			rawv6_err(sk, skb, शून्य, type, code,
					inner_offset, info);
			sk = sk_next(sk);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&raw_v6_hashinfo.lock);
पूर्ण

अटल अंतरभूत पूर्णांक rawv6_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर ((raw6_sk(sk)->checksum || rcu_access_poपूर्णांकer(sk->sk_filter)) &&
	    skb_checksum_complete(skb)) अणु
		atomic_inc(&sk->sk_drops);
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	/* Charge it to the socket. */
	skb_dst_drop(skb);
	अगर (sock_queue_rcv_skb(sk, skb) < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	This is next to useless...
 *	अगर we demultiplex in network layer we करोn't need the extra call
 *	just to queue the skb...
 *	maybe we could have the network decide upon a hपूर्णांक अगर it
 *	should call raw_rcv क्रम demultiplexing
 */
पूर्णांक rawv6_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा raw6_sock *rp = raw6_sk(sk);

	अगर (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb)) अणु
		atomic_inc(&sk->sk_drops);
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	अगर (!rp->checksum)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		skb_postpull_rcsum(skb, skb_network_header(skb),
				   skb_network_header_len(skb));
		अगर (!csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
				     &ipv6_hdr(skb)->daddr,
				     skb->len, inet->inet_num, skb->csum))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
	अगर (!skb_csum_unnecessary(skb))
		skb->csum = ~csum_unfold(csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
							 &ipv6_hdr(skb)->daddr,
							 skb->len,
							 inet->inet_num, 0));

	अगर (inet->hdrincl) अणु
		अगर (skb_checksum_complete(skb)) अणु
			atomic_inc(&sk->sk_drops);
			kमुक्त_skb(skb);
			वापस NET_RX_DROP;
		पूर्ण
	पूर्ण

	rawv6_rcv_skb(sk, skb);
	वापस 0;
पूर्ण


/*
 *	This should be easy, अगर there is something there
 *	we वापस it, otherwise we block.
 */

अटल पूर्णांक rawv6_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			 पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);
	काष्ठा sk_buff *skb;
	माप_प्रकार copied;
	पूर्णांक err;

	अगर (flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (flags & MSG_ERRQUEUE)
		वापस ipv6_recv_error(sk, msg, len, addr_len);

	अगर (np->rxpmtu && np->rxopt.bits.rxpmtu)
		वापस ipv6_recv_rxpmtu(sk, msg, len, addr_len);

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		copied = len;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	अगर (skb_csum_unnecessary(skb)) अणु
		err = skb_copy_datagram_msg(skb, 0, msg, copied);
	पूर्ण अन्यथा अगर (msg->msg_flags&MSG_TRUNC) अणु
		अगर (__skb_checksum_complete(skb))
			जाओ csum_copy_err;
		err = skb_copy_datagram_msg(skb, 0, msg, copied);
	पूर्ण अन्यथा अणु
		err = skb_copy_and_csum_datagram_msg(skb, 0, msg);
		अगर (err == -EINVAL)
			जाओ csum_copy_err;
	पूर्ण
	अगर (err)
		जाओ out_मुक्त;

	/* Copy the address. */
	अगर (sin6) अणु
		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = 0;
		sin6->sin6_addr = ipv6_hdr(skb)->saddr;
		sin6->sin6_flowinfo = 0;
		sin6->sin6_scope_id = ipv6_अगरace_scope_id(&sin6->sin6_addr,
							  inet6_iअगर(skb));
		*addr_len = माप(*sin6);
	पूर्ण

	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (np->rxopt.all)
		ip6_datagram_recv_ctl(sk, msg, skb);

	err = copied;
	अगर (flags & MSG_TRUNC)
		err = skb->len;

out_मुक्त:
	skb_मुक्त_datagram(sk, skb);
out:
	वापस err;

csum_copy_err:
	skb_समाप्त_datagram(sk, skb, flags);

	/* Error क्रम blocking हाल is chosen to masquerade
	   as some normal condition.
	 */
	err = (flags&MSG_DONTWAIT) ? -EAGAIN : -EHOSTUNREACH;
	जाओ out;
पूर्ण

अटल पूर्णांक rawv6_push_pending_frames(काष्ठा sock *sk, काष्ठा flowi6 *fl6,
				     काष्ठा raw6_sock *rp)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;
	पूर्णांक offset;
	पूर्णांक len;
	पूर्णांक total_len;
	__wsum पंचांगp_csum;
	__sum16 csum;

	अगर (!rp->checksum)
		जाओ send;

	skb = skb_peek(&sk->sk_ग_लिखो_queue);
	अगर (!skb)
		जाओ out;

	offset = rp->offset;
	total_len = inet_sk(sk)->cork.base.length;
	अगर (offset >= total_len - 1) अणु
		err = -EINVAL;
		ip6_flush_pending_frames(sk);
		जाओ out;
	पूर्ण

	/* should be check HW csum miyazawa */
	अगर (skb_queue_len(&sk->sk_ग_लिखो_queue) == 1) अणु
		/*
		 * Only one fragment on the socket.
		 */
		पंचांगp_csum = skb->csum;
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *csum_skb = शून्य;
		पंचांगp_csum = 0;

		skb_queue_walk(&sk->sk_ग_लिखो_queue, skb) अणु
			पंचांगp_csum = csum_add(पंचांगp_csum, skb->csum);

			अगर (csum_skb)
				जारी;

			len = skb->len - skb_transport_offset(skb);
			अगर (offset >= len) अणु
				offset -= len;
				जारी;
			पूर्ण

			csum_skb = skb;
		पूर्ण

		skb = csum_skb;
	पूर्ण

	offset += skb_transport_offset(skb);
	err = skb_copy_bits(skb, offset, &csum, 2);
	अगर (err < 0) अणु
		ip6_flush_pending_frames(sk);
		जाओ out;
	पूर्ण

	/* in हाल cksum was not initialized */
	अगर (unlikely(csum))
		पंचांगp_csum = csum_sub(पंचांगp_csum, csum_unfold(csum));

	csum = csum_ipv6_magic(&fl6->saddr, &fl6->daddr,
			       total_len, fl6->flowi6_proto, पंचांगp_csum);

	अगर (csum == 0 && fl6->flowi6_proto == IPPROTO_UDP)
		csum = CSUM_MANGLED_0;

	BUG_ON(skb_store_bits(skb, offset, &csum, 2));

send:
	err = ip6_push_pending_frames(sk);
out:
	वापस err;
पूर्ण

अटल पूर्णांक rawv6_send_hdrinc(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक length,
			काष्ठा flowi6 *fl6, काष्ठा dst_entry **dstp,
			अचिन्हित पूर्णांक flags, स्थिर काष्ठा sockcm_cookie *sockc)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा ipv6hdr *iph;
	काष्ठा sk_buff *skb;
	पूर्णांक err;
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)*dstp;
	पूर्णांक hlen = LL_RESERVED_SPACE(rt->dst.dev);
	पूर्णांक tlen = rt->dst.dev->needed_tailroom;

	अगर (length > rt->dst.dev->mtu) अणु
		ipv6_local_error(sk, EMSGSIZE, fl6, rt->dst.dev->mtu);
		वापस -EMSGSIZE;
	पूर्ण
	अगर (length < माप(काष्ठा ipv6hdr))
		वापस -EINVAL;
	अगर (flags&MSG_PROBE)
		जाओ out;

	skb = sock_alloc_send_skb(sk,
				  length + hlen + tlen + 15,
				  flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		जाओ error;
	skb_reserve(skb, hlen);

	skb->protocol = htons(ETH_P_IPV6);
	skb->priority = sk->sk_priority;
	skb->mark = sockc->mark;
	skb->tstamp = sockc->transmit_समय;

	skb_put(skb, length);
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);

	skb->ip_summed = CHECKSUM_NONE;

	skb_setup_tx_बारtamp(skb, sockc->tsflags);

	अगर (flags & MSG_CONFIRM)
		skb_set_dst_pending_confirm(skb, 1);

	skb->transport_header = skb->network_header;
	err = स_नकल_from_msg(iph, msg, length);
	अगर (err) अणु
		err = -EFAULT;
		kमुक्त_skb(skb);
		जाओ error;
	पूर्ण

	skb_dst_set(skb, &rt->dst);
	*dstp = शून्य;

	/* अगर egress device is enslaved to an L3 master device pass the
	 * skb to its handler क्रम processing
	 */
	skb = l3mdev_ip6_out(sk, skb);
	अगर (unlikely(!skb))
		वापस 0;

	/* Acquire rcu_पढ़ो_lock() in हाल we need to use rt->rt6i_idev
	 * in the error path. Since skb has been मुक्तd, the dst could
	 * have been queued क्रम deletion.
	 */
	rcu_पढ़ो_lock();
	IP6_UPD_PO_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUT, skb->len);
	err = NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT, net, sk, skb,
		      शून्य, rt->dst.dev, dst_output);
	अगर (err > 0)
		err = net_xmit_त्रुटि_सं(err);
	अगर (err) अणु
		IP6_INC_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
		rcu_पढ़ो_unlock();
		जाओ error_check;
	पूर्ण
	rcu_पढ़ो_unlock();
out:
	वापस 0;

error:
	IP6_INC_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
error_check:
	अगर (err == -ENOBUFS && !np->recverr)
		err = 0;
	वापस err;
पूर्ण

काष्ठा raw6_frag_vec अणु
	काष्ठा msghdr *msg;
	पूर्णांक hlen;
	अक्षर c[4];
पूर्ण;

अटल पूर्णांक rawv6_probe_proto_opt(काष्ठा raw6_frag_vec *rfv, काष्ठा flowi6 *fl6)
अणु
	पूर्णांक err = 0;
	चयन (fl6->flowi6_proto) अणु
	हाल IPPROTO_ICMPV6:
		rfv->hlen = 2;
		err = स_नकल_from_msg(rfv->c, rfv->msg, rfv->hlen);
		अगर (!err) अणु
			fl6->fl6_icmp_type = rfv->c[0];
			fl6->fl6_icmp_code = rfv->c[1];
		पूर्ण
		अवरोध;
	हाल IPPROTO_MH:
		rfv->hlen = 4;
		err = स_नकल_from_msg(rfv->c, rfv->msg, rfv->hlen);
		अगर (!err)
			fl6->fl6_mh_type = rfv->c[2];
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक raw6_getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len, पूर्णांक odd,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा raw6_frag_vec *rfv = from;

	अगर (offset < rfv->hlen) अणु
		पूर्णांक copy = min(rfv->hlen - offset, len);

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			स_नकल(to, rfv->c + offset, copy);
		अन्यथा
			skb->csum = csum_block_add(
				skb->csum,
				csum_partial_copy_nocheck(rfv->c + offset,
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

अटल पूर्णांक rawv6_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा ipv6_txoptions *opt_to_मुक्त = शून्य;
	काष्ठा ipv6_txoptions opt_space;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);
	काष्ठा in6_addr *daddr, *final_p, final;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा raw6_sock *rp = raw6_sk(sk);
	काष्ठा ipv6_txoptions *opt = शून्य;
	काष्ठा ip6_flowlabel *flowlabel = शून्य;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा raw6_frag_vec rfv;
	काष्ठा flowi6 fl6;
	काष्ठा ipcm6_cookie ipc6;
	पूर्णांक addr_len = msg->msg_namelen;
	पूर्णांक hdrincl;
	u16 proto;
	पूर्णांक err;

	/* Rough check on arithmetic overflow,
	   better check is made in ip6_append_data().
	 */
	अगर (len > पूर्णांक_उच्च)
		वापस -EMSGSIZE;

	/* Mirror BSD error message compatibility */
	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	/* hdrincl should be READ_ONCE(inet->hdrincl)
	 * but READ_ONCE() करोesn't work with bit fields.
	 * Doing this indirectly yields the same result.
	 */
	hdrincl = inet->hdrincl;
	hdrincl = READ_ONCE(hdrincl);

	/*
	 *	Get and verअगरy the address.
	 */
	स_रखो(&fl6, 0, माप(fl6));

	fl6.flowi6_mark = sk->sk_mark;
	fl6.flowi6_uid = sk->sk_uid;

	ipcm6_init(&ipc6);
	ipc6.sockc.tsflags = sk->sk_tsflags;
	ipc6.sockc.mark = sk->sk_mark;

	अगर (sin6) अणु
		अगर (addr_len < SIN6_LEN_RFC2133)
			वापस -EINVAL;

		अगर (sin6->sin6_family && sin6->sin6_family != AF_INET6)
			वापस -EAFNOSUPPORT;

		/* port is the proto value [0..255] carried in nexthdr */
		proto = ntohs(sin6->sin6_port);

		अगर (!proto)
			proto = inet->inet_num;
		अन्यथा अगर (proto != inet->inet_num)
			वापस -EINVAL;

		अगर (proto > 255)
			वापस -EINVAL;

		daddr = &sin6->sin6_addr;
		अगर (np->sndflow) अणु
			fl6.flowlabel = sin6->sin6_flowinfo&IPV6_FLOWINFO_MASK;
			अगर (fl6.flowlabel&IPV6_FLOWLABEL_MASK) अणु
				flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
				अगर (IS_ERR(flowlabel))
					वापस -EINVAL;
			पूर्ण
		पूर्ण

		/*
		 * Otherwise it will be dअगरficult to मुख्यtain
		 * sk->sk_dst_cache.
		 */
		अगर (sk->sk_state == TCP_ESTABLISHED &&
		    ipv6_addr_equal(daddr, &sk->sk_v6_daddr))
			daddr = &sk->sk_v6_daddr;

		अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
		    sin6->sin6_scope_id &&
		    __ipv6_addr_needs_scope_id(__ipv6_addr_type(daddr)))
			fl6.flowi6_oअगर = sin6->sin6_scope_id;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;

		proto = inet->inet_num;
		daddr = &sk->sk_v6_daddr;
		fl6.flowlabel = np->flow_label;
	पूर्ण

	अगर (fl6.flowi6_oअगर == 0)
		fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;

	अगर (msg->msg_controllen) अणु
		opt = &opt_space;
		स_रखो(opt, 0, माप(काष्ठा ipv6_txoptions));
		opt->tot_len = माप(काष्ठा ipv6_txoptions);
		ipc6.opt = opt;

		err = ip6_datagram_send_ctl(sock_net(sk), sk, msg, &fl6, &ipc6);
		अगर (err < 0) अणु
			fl6_sock_release(flowlabel);
			वापस err;
		पूर्ण
		अगर ((fl6.flowlabel&IPV6_FLOWLABEL_MASK) && !flowlabel) अणु
			flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
			अगर (IS_ERR(flowlabel))
				वापस -EINVAL;
		पूर्ण
		अगर (!(opt->opt_nflen|opt->opt_flen))
			opt = शून्य;
	पूर्ण
	अगर (!opt) अणु
		opt = txopt_get(np);
		opt_to_मुक्त = opt;
	पूर्ण
	अगर (flowlabel)
		opt = fl6_merge_options(&opt_space, flowlabel, opt);
	opt = ipv6_fixup_options(&opt_space, opt);

	fl6.flowi6_proto = proto;
	fl6.flowi6_mark = ipc6.sockc.mark;

	अगर (!hdrincl) अणु
		rfv.msg = msg;
		rfv.hlen = 0;
		err = rawv6_probe_proto_opt(&rfv, &fl6);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (!ipv6_addr_any(daddr))
		fl6.daddr = *daddr;
	अन्यथा
		fl6.daddr.s6_addr[15] = 0x1; /* :: means loopback (BSD'ism) */
	अगर (ipv6_addr_any(&fl6.saddr) && !ipv6_addr_any(&np->saddr))
		fl6.saddr = np->saddr;

	final_p = fl6_update_dst(&fl6, opt, &final);

	अगर (!fl6.flowi6_oअगर && ipv6_addr_is_multicast(&fl6.daddr))
		fl6.flowi6_oअगर = np->mcast_oअगर;
	अन्यथा अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->ucast_oअगर;
	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

	अगर (hdrincl)
		fl6.flowi6_flags |= FLOWI_FLAG_KNOWN_NH;

	अगर (ipc6.tclass < 0)
		ipc6.tclass = np->tclass;

	fl6.flowlabel = ip6_make_flowinfo(ipc6.tclass, fl6.flowlabel);

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		जाओ out;
	पूर्ण
	अगर (ipc6.hlimit < 0)
		ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);

	अगर (ipc6.करोntfrag < 0)
		ipc6.करोntfrag = np->करोntfrag;

	अगर (msg->msg_flags&MSG_CONFIRM)
		जाओ करो_confirm;

back_from_confirm:
	अगर (hdrincl)
		err = rawv6_send_hdrinc(sk, msg, len, &fl6, &dst,
					msg->msg_flags, &ipc6.sockc);
	अन्यथा अणु
		ipc6.opt = opt;
		lock_sock(sk);
		err = ip6_append_data(sk, raw6_getfrag, &rfv,
			len, 0, &ipc6, &fl6, (काष्ठा rt6_info *)dst,
			msg->msg_flags);

		अगर (err)
			ip6_flush_pending_frames(sk);
		अन्यथा अगर (!(msg->msg_flags & MSG_MORE))
			err = rawv6_push_pending_frames(sk, &fl6, rp);
		release_sock(sk);
	पूर्ण
करोne:
	dst_release(dst);
out:
	fl6_sock_release(flowlabel);
	txopt_put(opt_to_मुक्त);
	वापस err < 0 ? err : len;
करो_confirm:
	अगर (msg->msg_flags & MSG_PROBE)
		dst_confirm_neigh(dst, &fl6.daddr);
	अगर (!(msg->msg_flags & MSG_PROBE) || len)
		जाओ back_from_confirm;
	err = 0;
	जाओ करोne;
पूर्ण

अटल पूर्णांक rawv6_seticmpfilter(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, पूर्णांक optlen)
अणु
	चयन (optname) अणु
	हाल ICMPV6_FILTER:
		अगर (optlen > माप(काष्ठा icmp6_filter))
			optlen = माप(काष्ठा icmp6_filter);
		अगर (copy_from_sockptr(&raw6_sk(sk)->filter, optval, optlen))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rawv6_geticmpfilter(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक len;

	चयन (optname) अणु
	हाल ICMPV6_FILTER:
		अगर (get_user(len, optlen))
			वापस -EFAULT;
		अगर (len < 0)
			वापस -EINVAL;
		अगर (len > माप(काष्ठा icmp6_filter))
			len = माप(काष्ठा icmp6_filter);
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &raw6_sk(sk)->filter, len))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक करो_rawv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा raw6_sock *rp = raw6_sk(sk);
	पूर्णांक val;

	अगर (copy_from_sockptr(&val, optval, माप(val)))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल IPV6_HDRINCL:
		अगर (sk->sk_type != SOCK_RAW)
			वापस -EINVAL;
		inet_sk(sk)->hdrincl = !!val;
		वापस 0;
	हाल IPV6_CHECKSUM:
		अगर (inet_sk(sk)->inet_num == IPPROTO_ICMPV6 &&
		    level == IPPROTO_IPV6) अणु
			/*
			 * RFC3542 tells that IPV6_CHECKSUM socket
			 * option in the IPPROTO_IPV6 level is not
			 * allowed on ICMPv6 sockets.
			 * If you want to set it, use IPPROTO_RAW
			 * level IPV6_CHECKSUM socket option
			 * (Linux extension).
			 */
			वापस -EINVAL;
		पूर्ण

		/* You may get strange result with a positive odd offset;
		   RFC2292bis agrees with me. */
		अगर (val > 0 && (val&1))
			वापस -EINVAL;
		अगर (val < 0) अणु
			rp->checksum = 0;
		पूर्ण अन्यथा अणु
			rp->checksum = 1;
			rp->offset = val;
		पूर्ण

		वापस 0;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
पूर्ण

अटल पूर्णांक rawv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	चयन (level) अणु
	हाल SOL_RAW:
		अवरोध;

	हाल SOL_ICMPV6:
		अगर (inet_sk(sk)->inet_num != IPPROTO_ICMPV6)
			वापस -EOPNOTSUPP;
		वापस rawv6_seticmpfilter(sk, level, optname, optval, optlen);
	हाल SOL_IPV6:
		अगर (optname == IPV6_CHECKSUM ||
		    optname == IPV6_HDRINCL)
			अवरोध;
		fallthrough;
	शेष:
		वापस ipv6_setsockopt(sk, level, optname, optval, optlen);
	पूर्ण

	वापस करो_rawv6_setsockopt(sk, level, optname, optval, optlen);
पूर्ण

अटल पूर्णांक करो_rawv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा raw6_sock *rp = raw6_sk(sk);
	पूर्णांक val, len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल IPV6_HDRINCL:
		val = inet_sk(sk)->hdrincl;
		अवरोध;
	हाल IPV6_CHECKSUM:
		/*
		 * We allow माला_लोockopt() क्रम IPPROTO_IPV6-level
		 * IPV6_CHECKSUM socket option on ICMPv6 sockets
		 * since RFC3542 is silent about it.
		 */
		अगर (rp->checksum == 0)
			val = -1;
		अन्यथा
			val = rp->offset;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	len = min_t(अचिन्हित पूर्णांक, माप(पूर्णांक), len);

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक rawv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	चयन (level) अणु
	हाल SOL_RAW:
		अवरोध;

	हाल SOL_ICMPV6:
		अगर (inet_sk(sk)->inet_num != IPPROTO_ICMPV6)
			वापस -EOPNOTSUPP;
		वापस rawv6_geticmpfilter(sk, level, optname, optval, optlen);
	हाल SOL_IPV6:
		अगर (optname == IPV6_CHECKSUM ||
		    optname == IPV6_HDRINCL)
			अवरोध;
		fallthrough;
	शेष:
		वापस ipv6_माला_लोockopt(sk, level, optname, optval, optlen);
	पूर्ण

	वापस करो_rawv6_माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण

अटल पूर्णांक rawv6_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
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
#अगर_घोषित CONFIG_IPV6_MROUTE
		वापस ip6mr_ioctl(sk, cmd, (व्योम __user *)arg);
#अन्यथा
		वापस -ENOIOCTLCMD;
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_rawv6_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SIOCOUTQ:
	हाल SIOCINQ:
		वापस -ENOIOCTLCMD;
	शेष:
#अगर_घोषित CONFIG_IPV6_MROUTE
		वापस ip6mr_compat_ioctl(sk, cmd, compat_ptr(arg));
#अन्यथा
		वापस -ENOIOCTLCMD;
#पूर्ण_अगर
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम rawv6_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	अगर (inet_sk(sk)->inet_num == IPPROTO_RAW)
		ip6_ra_control(sk, -1);
	ip6mr_sk_करोne(sk);
	sk_common_release(sk);
पूर्ण

अटल व्योम raw6_destroy(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	ip6_flush_pending_frames(sk);
	release_sock(sk);

	inet6_destroy_sock(sk);
पूर्ण

अटल पूर्णांक rawv6_init_sk(काष्ठा sock *sk)
अणु
	काष्ठा raw6_sock *rp = raw6_sk(sk);

	चयन (inet_sk(sk)->inet_num) अणु
	हाल IPPROTO_ICMPV6:
		rp->checksum = 1;
		rp->offset   = 2;
		अवरोध;
	हाल IPPROTO_MH:
		rp->checksum = 1;
		rp->offset   = 4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा proto rawv6_prot = अणु
	.name		   = "RAWv6",
	.owner		   = THIS_MODULE,
	.बंद		   = rawv6_बंद,
	.destroy	   = raw6_destroy,
	.connect	   = ip6_datagram_connect_v6_only,
	.disconnect	   = __udp_disconnect,
	.ioctl		   = rawv6_ioctl,
	.init		   = rawv6_init_sk,
	.setsockopt	   = rawv6_setsockopt,
	.माला_लोockopt	   = rawv6_माला_लोockopt,
	.sendmsg	   = rawv6_sendmsg,
	.recvmsg	   = rawv6_recvmsg,
	.bind		   = rawv6_bind,
	.backlog_rcv	   = rawv6_rcv_skb,
	.hash		   = raw_hash_sk,
	.unhash		   = raw_unhash_sk,
	.obj_size	   = माप(काष्ठा raw6_sock),
	.useroffset	   = दुरत्व(काष्ठा raw6_sock, filter),
	.usersize	   = माप_field(काष्ठा raw6_sock, filter),
	.h.raw_hash	   = &raw_v6_hashinfo,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = compat_rawv6_ioctl,
#पूर्ण_अगर
	.diag_destroy	   = raw_पात,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक raw6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, IPV6_SEQ_DGRAM_HEADER);
	पूर्ण अन्यथा अणु
		काष्ठा sock *sp = v;
		__u16 srcp  = inet_sk(sp)->inet_num;
		ip6_dgram_sock_seq_show(seq, v, srcp, 0,
					raw_seq_निजी(seq)->bucket);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations raw6_seq_ops = अणु
	.start =	raw_seq_start,
	.next =		raw_seq_next,
	.stop =		raw_seq_stop,
	.show =		raw6_seq_show,
पूर्ण;

अटल पूर्णांक __net_init raw6_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("raw6", 0444, net->proc_net, &raw6_seq_ops,
			माप(काष्ठा raw_iter_state), &raw_v6_hashinfo))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास raw6_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("raw6", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations raw6_net_ops = अणु
	.init = raw6_init_net,
	.निकास = raw6_निकास_net,
पूर्ण;

पूर्णांक __init raw6_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&raw6_net_ops);
पूर्ण

व्योम raw6_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&raw6_net_ops);
पूर्ण
#पूर्ण_अगर	/* CONFIG_PROC_FS */

/* Same as inet6_dgram_ops, sans udp_poll.  */
स्थिर काष्ठा proto_ops inet6_sockraw_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = inet6_bind,
	.connect	   = inet_dgram_connect,	/* ok		*/
	.socketpair	   = sock_no_socketpair,	/* a करो nothing	*/
	.accept		   = sock_no_accept,		/* a करो nothing	*/
	.getname	   = inet6_getname,
	.poll		   = datagram_poll,		/* ok		*/
	.ioctl		   = inet6_ioctl,		/* must change  */
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,		/* ok		*/
	.shutकरोwn	   = inet_shutकरोwn,		/* ok		*/
	.setsockopt	   = sock_common_setsockopt,	/* ok		*/
	.माला_लोockopt	   = sock_common_माला_लोockopt,	/* ok		*/
	.sendmsg	   = inet_sendmsg,		/* ok		*/
	.recvmsg	   = sock_common_recvmsg,	/* ok		*/
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा inet_protosw rawv6_protosw = अणु
	.type		= SOCK_RAW,
	.protocol	= IPPROTO_IP,	/* wild card */
	.prot		= &rawv6_prot,
	.ops		= &inet6_sockraw_ops,
	.flags		= INET_PROTOSW_REUSE,
पूर्ण;

पूर्णांक __init rawv6_init(व्योम)
अणु
	वापस inet6_रेजिस्टर_protosw(&rawv6_protosw);
पूर्ण

व्योम rawv6_निकास(व्योम)
अणु
	inet6_unरेजिस्टर_protosw(&rawv6_protosw);
पूर्ण
