<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	NET3:	Implementation of the ICMP protocol layer.
 *
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *
 *	Some of the function names and the icmp unreach table क्रम this
 *	module were derived from [icmp.c 1.0.11 06/02/93] by
 *	Ross Biro, Fred N. van Kempen, Mark Evans, Alan Cox, Gerhard Koerting.
 *	Other than that this module is a complete reग_लिखो.
 *
 *	Fixes:
 *	Clemens Fruhwirth	:	पूर्णांकroduce global icmp rate limiting
 *					with icmp type masking ability instead
 *					of broken per type icmp समयouts.
 *		Mike Shaver	:	RFC1122 checks.
 *		Alan Cox	:	Multicast ping reply as self.
 *		Alan Cox	:	Fix atomicity lockup in ip_build_xmit
 *					call.
 *		Alan Cox	:	Added 216,128 byte paths to the MTU
 *					code.
 *		Martin Mares	:	RFC1812 checks.
 *		Martin Mares	:	Can be configured to follow redirects
 *					अगर acting as a router _without_ a
 *					routing protocol (RFC 1812).
 *		Martin Mares	:	Echo requests may be configured to
 *					be ignored (RFC 1812).
 *		Martin Mares	:	Limitation of ICMP error message
 *					transmit rate (RFC 1812).
 *		Martin Mares	:	TOS and Precedence set correctly
 *					(RFC 1812).
 *		Martin Mares	:	Now copying as much data from the
 *					original packet as we can without
 *					exceeding 576 bytes (RFC 1812).
 *	Willy Konynenberg	:	Transparent proxying support.
 *		Keith Owens	:	RFC1191 correction क्रम 4.2BSD based
 *					path MTU bug.
 *		Thomas Quinot	:	ICMP Dest Unreach codes up to 15 are
 *					valid (RFC 1812).
 *		Andi Kleen	:	Check all packet lengths properly
 *					and moved all kमुक्त_skb() up to
 *					icmp_rcv.
 *		Andi Kleen	:	Move the rate limit bookkeeping
 *					पूर्णांकo the dest entry and use a token
 *					bucket filter (thanks to ANK). Make
 *					the rates sysctl configurable.
 *		Yu Tianli	:	Fixed two ugly bugs in icmp_send
 *					- IP option length was accounted wrongly
 *					- ICMP header length was not accounted
 *					  at all.
 *              Tristan Greaves :       Added sysctl option to ignore bogus
 *              			broadcast responses from broken routers.
 *
 * To Fix:
 *
 *	- Should use skb_pull() instead of all the manual checking.
 *	  This would also greatly simply some upper layer error handlers. --AK
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/slab.h>
#समावेश <net/snmp.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/protocol.h>
#समावेश <net/icmp.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/raw.h>
#समावेश <net/ping.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>
#समावेश <net/checksum.h>
#समावेश <net/xfrm.h>
#समावेश <net/inet_common.h>
#समावेश <net/ip_fib.h>
#समावेश <net/l3mdev.h>

/*
 *	Build xmit assembly blocks
 */

काष्ठा icmp_bxm अणु
	काष्ठा sk_buff *skb;
	पूर्णांक offset;
	पूर्णांक data_len;

	काष्ठा अणु
		काष्ठा icmphdr icmph;
		__be32	       बार[3];
	पूर्ण data;
	पूर्णांक head_len;
	काष्ठा ip_options_data replyopts;
पूर्ण;

/* An array of त्रुटि_सं क्रम error messages from dest unreach. */
/* RFC 1122: 3.2.2.1 States that NET_UNREACH, HOST_UNREACH and SR_FAILED MUST be considered 'transient errs'. */

स्थिर काष्ठा icmp_err icmp_err_convert[] = अणु
	अणु
		.त्रुटि_सं = ENETUNREACH,	/* ICMP_NET_UNREACH */
		.fatal = 0,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTUNREACH,	/* ICMP_HOST_UNREACH */
		.fatal = 0,
	पूर्ण,
	अणु
		.त्रुटि_सं = ENOPROTOOPT	/* ICMP_PROT_UNREACH */,
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = ECONNREFUSED,	/* ICMP_PORT_UNREACH */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = EMSGSIZE,	/* ICMP_FRAG_NEEDED */
		.fatal = 0,
	पूर्ण,
	अणु
		.त्रुटि_सं = EOPNOTSUPP,	/* ICMP_SR_FAILED */
		.fatal = 0,
	पूर्ण,
	अणु
		.त्रुटि_सं = ENETUNREACH,	/* ICMP_NET_UNKNOWN */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTDOWN,	/* ICMP_HOST_UNKNOWN */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = ENONET,	/* ICMP_HOST_ISOLATED */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = ENETUNREACH,	/* ICMP_NET_ANO	*/
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTUNREACH,	/* ICMP_HOST_ANO */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = ENETUNREACH,	/* ICMP_NET_UNR_TOS */
		.fatal = 0,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTUNREACH,	/* ICMP_HOST_UNR_TOS */
		.fatal = 0,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTUNREACH,	/* ICMP_PKT_FILTERED */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTUNREACH,	/* ICMP_PREC_VIOLATION */
		.fatal = 1,
	पूर्ण,
	अणु
		.त्रुटि_सं = EHOSTUNREACH,	/* ICMP_PREC_CUTOFF */
		.fatal = 1,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(icmp_err_convert);

/*
 *	ICMP control array. This specअगरies what to करो with each ICMP.
 */

काष्ठा icmp_control अणु
	bool (*handler)(काष्ठा sk_buff *skb);
	लघु   error;		/* This ICMP is classed as an error message */
पूर्ण;

अटल स्थिर काष्ठा icmp_control icmp_poपूर्णांकers[NR_ICMP_TYPES+1];

/*
 *	The ICMP socket(s). This is the most convenient way to flow control
 *	our ICMP output as well as मुख्यtain a clean पूर्णांकerface throughout
 *	all layers. All Socketless IP sends will soon be gone.
 *
 *	On SMP we have one ICMP socket per-cpu.
 */
अटल काष्ठा sock *icmp_sk(काष्ठा net *net)
अणु
	वापस this_cpu_पढ़ो(*net->ipv4.icmp_sk);
पूर्ण

/* Called with BH disabled */
अटल अंतरभूत काष्ठा sock *icmp_xmit_lock(काष्ठा net *net)
अणु
	काष्ठा sock *sk;

	sk = icmp_sk(net);

	अगर (unlikely(!spin_trylock(&sk->sk_lock.slock))) अणु
		/* This can happen अगर the output path संकेतs a
		 * dst_link_failure() क्रम an outgoing ICMP packet.
		 */
		वापस शून्य;
	पूर्ण
	वापस sk;
पूर्ण

अटल अंतरभूत व्योम icmp_xmit_unlock(काष्ठा sock *sk)
अणु
	spin_unlock(&sk->sk_lock.slock);
पूर्ण

पूर्णांक sysctl_icmp_msgs_per_sec __पढ़ो_mostly = 1000;
पूर्णांक sysctl_icmp_msgs_burst __पढ़ो_mostly = 50;

अटल काष्ठा अणु
	spinlock_t	lock;
	u32		credit;
	u32		stamp;
पूर्ण icmp_global = अणु
	.lock		= __SPIN_LOCK_UNLOCKED(icmp_global.lock),
पूर्ण;

/**
 * icmp_global_allow - Are we allowed to send one more ICMP message ?
 *
 * Uses a token bucket to limit our ICMP messages to ~sysctl_icmp_msgs_per_sec.
 * Returns false अगर we reached the limit and can not send another packet.
 * Note: called with BH disabled
 */
bool icmp_global_allow(व्योम)
अणु
	u32 credit, delta, incr = 0, now = (u32)jअगरfies;
	bool rc = false;

	/* Check अगर token bucket is empty and cannot be refilled
	 * without taking the spinlock. The READ_ONCE() are paired
	 * with the following WRITE_ONCE() in this same function.
	 */
	अगर (!READ_ONCE(icmp_global.credit)) अणु
		delta = min_t(u32, now - READ_ONCE(icmp_global.stamp), HZ);
		अगर (delta < HZ / 50)
			वापस false;
	पूर्ण

	spin_lock(&icmp_global.lock);
	delta = min_t(u32, now - icmp_global.stamp, HZ);
	अगर (delta >= HZ / 50) अणु
		incr = sysctl_icmp_msgs_per_sec * delta / HZ ;
		अगर (incr)
			WRITE_ONCE(icmp_global.stamp, now);
	पूर्ण
	credit = min_t(u32, icmp_global.credit + incr, sysctl_icmp_msgs_burst);
	अगर (credit) अणु
		/* We want to use a credit of one in average, but need to अक्रमomize
		 * it क्रम security reasons.
		 */
		credit = max_t(पूर्णांक, credit - pअक्रमom_u32_max(3), 0);
		rc = true;
	पूर्ण
	WRITE_ONCE(icmp_global.credit, credit);
	spin_unlock(&icmp_global.lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(icmp_global_allow);

अटल bool icmpv4_mask_allow(काष्ठा net *net, पूर्णांक type, पूर्णांक code)
अणु
	अगर (type > NR_ICMP_TYPES)
		वापस true;

	/* Don't limit PMTU discovery. */
	अगर (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED)
		वापस true;

	/* Limit अगर icmp type is enabled in ratemask. */
	अगर (!((1 << type) & net->ipv4.sysctl_icmp_ratemask))
		वापस true;

	वापस false;
पूर्ण

अटल bool icmpv4_global_allow(काष्ठा net *net, पूर्णांक type, पूर्णांक code)
अणु
	अगर (icmpv4_mask_allow(net, type, code))
		वापस true;

	अगर (icmp_global_allow())
		वापस true;

	वापस false;
पूर्ण

/*
 *	Send an ICMP frame.
 */

अटल bool icmpv4_xrlim_allow(काष्ठा net *net, काष्ठा rtable *rt,
			       काष्ठा flowi4 *fl4, पूर्णांक type, पूर्णांक code)
अणु
	काष्ठा dst_entry *dst = &rt->dst;
	काष्ठा inet_peer *peer;
	bool rc = true;
	पूर्णांक vअगर;

	अगर (icmpv4_mask_allow(net, type, code))
		जाओ out;

	/* No rate limit on loopback */
	अगर (dst->dev && (dst->dev->flags&IFF_LOOPBACK))
		जाओ out;

	vअगर = l3mdev_master_अगरindex(dst->dev);
	peer = inet_getpeer_v4(net->ipv4.peers, fl4->daddr, vअगर, 1);
	rc = inet_peer_xrlim_allow(peer, net->ipv4.sysctl_icmp_ratelimit);
	अगर (peer)
		inet_putpeer(peer);
out:
	वापस rc;
पूर्ण

/*
 *	Maपूर्णांकain the counters used in the SNMP statistics क्रम outgoing ICMP
 */
व्योम icmp_out_count(काष्ठा net *net, अचिन्हित अक्षर type)
अणु
	ICMPMSGOUT_INC_STATS(net, type);
	ICMP_INC_STATS(net, ICMP_MIB_OUTMSGS);
पूर्ण

/*
 *	Checksum each fragment, and on the first include the headers and final
 *	checksum.
 */
अटल पूर्णांक icmp_glue_bits(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len, पूर्णांक odd,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा icmp_bxm *icmp_param = (काष्ठा icmp_bxm *)from;
	__wsum csum;

	csum = skb_copy_and_csum_bits(icmp_param->skb,
				      icmp_param->offset + offset,
				      to, len);

	skb->csum = csum_block_add(skb->csum, csum, odd);
	अगर (icmp_poपूर्णांकers[icmp_param->data.icmph.type].error)
		nf_ct_attach(skb, icmp_param->skb);
	वापस 0;
पूर्ण

अटल व्योम icmp_push_reply(काष्ठा icmp_bxm *icmp_param,
			    काष्ठा flowi4 *fl4,
			    काष्ठा ipcm_cookie *ipc, काष्ठा rtable **rt)
अणु
	काष्ठा sock *sk;
	काष्ठा sk_buff *skb;

	sk = icmp_sk(dev_net((*rt)->dst.dev));
	अगर (ip_append_data(sk, fl4, icmp_glue_bits, icmp_param,
			   icmp_param->data_len+icmp_param->head_len,
			   icmp_param->head_len,
			   ipc, rt, MSG_DONTWAIT) < 0) अणु
		__ICMP_INC_STATS(sock_net(sk), ICMP_MIB_OUTERRORS);
		ip_flush_pending_frames(sk);
	पूर्ण अन्यथा अगर ((skb = skb_peek(&sk->sk_ग_लिखो_queue)) != शून्य) अणु
		काष्ठा icmphdr *icmph = icmp_hdr(skb);
		__wsum csum;
		काष्ठा sk_buff *skb1;

		csum = csum_partial_copy_nocheck((व्योम *)&icmp_param->data,
						 (अक्षर *)icmph,
						 icmp_param->head_len);
		skb_queue_walk(&sk->sk_ग_लिखो_queue, skb1) अणु
			csum = csum_add(csum, skb1->csum);
		पूर्ण
		icmph->checksum = csum_fold(csum);
		skb->ip_summed = CHECKSUM_NONE;
		ip_push_pending_frames(sk, fl4);
	पूर्ण
पूर्ण

/*
 *	Driving logic क्रम building and sending ICMP messages.
 */

अटल व्योम icmp_reply(काष्ठा icmp_bxm *icmp_param, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipcm_cookie ipc;
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा net *net = dev_net(rt->dst.dev);
	काष्ठा flowi4 fl4;
	काष्ठा sock *sk;
	काष्ठा inet_sock *inet;
	__be32 daddr, saddr;
	u32 mark = IP4_REPLY_MARK(net, skb->mark);
	पूर्णांक type = icmp_param->data.icmph.type;
	पूर्णांक code = icmp_param->data.icmph.code;

	अगर (ip_options_echo(net, &icmp_param->replyopts.opt.opt, skb))
		वापस;

	/* Needed by both icmp_global_allow and icmp_xmit_lock */
	local_bh_disable();

	/* global icmp_msgs_per_sec */
	अगर (!icmpv4_global_allow(net, type, code))
		जाओ out_bh_enable;

	sk = icmp_xmit_lock(net);
	अगर (!sk)
		जाओ out_bh_enable;
	inet = inet_sk(sk);

	icmp_param->data.icmph.checksum = 0;

	ipcm_init(&ipc);
	inet->tos = ip_hdr(skb)->tos;
	ipc.sockc.mark = mark;
	daddr = ipc.addr = ip_hdr(skb)->saddr;
	saddr = fib_compute_spec_dst(skb);

	अगर (icmp_param->replyopts.opt.opt.optlen) अणु
		ipc.opt = &icmp_param->replyopts.opt;
		अगर (ipc.opt->opt.srr)
			daddr = icmp_param->replyopts.opt.opt.faddr;
	पूर्ण
	स_रखो(&fl4, 0, माप(fl4));
	fl4.daddr = daddr;
	fl4.saddr = saddr;
	fl4.flowi4_mark = mark;
	fl4.flowi4_uid = sock_net_uid(net, शून्य);
	fl4.flowi4_tos = RT_TOS(ip_hdr(skb)->tos);
	fl4.flowi4_proto = IPPROTO_ICMP;
	fl4.flowi4_oअगर = l3mdev_master_अगरindex(skb->dev);
	security_skb_classअगरy_flow(skb, flowi4_to_flowi_common(&fl4));
	rt = ip_route_output_key(net, &fl4);
	अगर (IS_ERR(rt))
		जाओ out_unlock;
	अगर (icmpv4_xrlim_allow(net, rt, &fl4, type, code))
		icmp_push_reply(icmp_param, &fl4, &ipc, &rt);
	ip_rt_put(rt);
out_unlock:
	icmp_xmit_unlock(sk);
out_bh_enable:
	local_bh_enable();
पूर्ण

/*
 * The device used क्रम looking up which routing table to use क्रम sending an ICMP
 * error is preferably the source whenever it is set, which should ensure the
 * icmp error can be sent to the source host, अन्यथा lookup using the routing
 * table of the destination device, अन्यथा use the मुख्य routing table (index 0).
 */
अटल काष्ठा net_device *icmp_get_route_lookup_dev(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *route_lookup_dev = शून्य;

	अगर (skb->dev)
		route_lookup_dev = skb->dev;
	अन्यथा अगर (skb_dst(skb))
		route_lookup_dev = skb_dst(skb)->dev;
	वापस route_lookup_dev;
पूर्ण

अटल काष्ठा rtable *icmp_route_lookup(काष्ठा net *net,
					काष्ठा flowi4 *fl4,
					काष्ठा sk_buff *skb_in,
					स्थिर काष्ठा iphdr *iph,
					__be32 saddr, u8 tos, u32 mark,
					पूर्णांक type, पूर्णांक code,
					काष्ठा icmp_bxm *param)
अणु
	काष्ठा net_device *route_lookup_dev;
	काष्ठा rtable *rt, *rt2;
	काष्ठा flowi4 fl4_dec;
	पूर्णांक err;

	स_रखो(fl4, 0, माप(*fl4));
	fl4->daddr = (param->replyopts.opt.opt.srr ?
		      param->replyopts.opt.opt.faddr : iph->saddr);
	fl4->saddr = saddr;
	fl4->flowi4_mark = mark;
	fl4->flowi4_uid = sock_net_uid(net, शून्य);
	fl4->flowi4_tos = RT_TOS(tos);
	fl4->flowi4_proto = IPPROTO_ICMP;
	fl4->fl4_icmp_type = type;
	fl4->fl4_icmp_code = code;
	route_lookup_dev = icmp_get_route_lookup_dev(skb_in);
	fl4->flowi4_oअगर = l3mdev_master_अगरindex(route_lookup_dev);

	security_skb_classअगरy_flow(skb_in, flowi4_to_flowi_common(fl4));
	rt = ip_route_output_key_hash(net, fl4, skb_in);
	अगर (IS_ERR(rt))
		वापस rt;

	/* No need to clone since we're just using its address. */
	rt2 = rt;

	rt = (काष्ठा rtable *) xfrm_lookup(net, &rt->dst,
					   flowi4_to_flowi(fl4), शून्य, 0);
	अगर (!IS_ERR(rt)) अणु
		अगर (rt != rt2)
			वापस rt;
	पूर्ण अन्यथा अगर (PTR_ERR(rt) == -EPERM) अणु
		rt = शून्य;
	पूर्ण अन्यथा
		वापस rt;

	err = xfrm_decode_session_reverse(skb_in, flowi4_to_flowi(&fl4_dec), AF_INET);
	अगर (err)
		जाओ relookup_failed;

	अगर (inet_addr_type_dev_table(net, route_lookup_dev,
				     fl4_dec.saddr) == RTN_LOCAL) अणु
		rt2 = __ip_route_output_key(net, &fl4_dec);
		अगर (IS_ERR(rt2))
			err = PTR_ERR(rt2);
	पूर्ण अन्यथा अणु
		काष्ठा flowi4 fl4_2 = अणुपूर्ण;
		अचिन्हित दीर्घ orefdst;

		fl4_2.daddr = fl4_dec.saddr;
		rt2 = ip_route_output_key(net, &fl4_2);
		अगर (IS_ERR(rt2)) अणु
			err = PTR_ERR(rt2);
			जाओ relookup_failed;
		पूर्ण
		/* Ugh! */
		orefdst = skb_in->_skb_refdst; /* save old refdst */
		skb_dst_set(skb_in, शून्य);
		err = ip_route_input(skb_in, fl4_dec.daddr, fl4_dec.saddr,
				     RT_TOS(tos), rt2->dst.dev);

		dst_release(&rt2->dst);
		rt2 = skb_rtable(skb_in);
		skb_in->_skb_refdst = orefdst; /* restore old refdst */
	पूर्ण

	अगर (err)
		जाओ relookup_failed;

	rt2 = (काष्ठा rtable *) xfrm_lookup(net, &rt2->dst,
					    flowi4_to_flowi(&fl4_dec), शून्य,
					    XFRM_LOOKUP_ICMP);
	अगर (!IS_ERR(rt2)) अणु
		dst_release(&rt->dst);
		स_नकल(fl4, &fl4_dec, माप(*fl4));
		rt = rt2;
	पूर्ण अन्यथा अगर (PTR_ERR(rt2) == -EPERM) अणु
		अगर (rt)
			dst_release(&rt->dst);
		वापस rt2;
	पूर्ण अन्यथा अणु
		err = PTR_ERR(rt2);
		जाओ relookup_failed;
	पूर्ण
	वापस rt;

relookup_failed:
	अगर (rt)
		वापस rt;
	वापस ERR_PTR(err);
पूर्ण

/*
 *	Send an ICMP message in response to a situation
 *
 *	RFC 1122: 3.2.2	MUST send at least the IP header and 8 bytes of header.
 *		  MAY send more (we करो).
 *			MUST NOT change this header inक्रमmation.
 *			MUST NOT reply to a multicast/broadcast IP address.
 *			MUST NOT reply to a multicast/broadcast MAC address.
 *			MUST reply to only the first fragment.
 */

व्योम __icmp_send(काष्ठा sk_buff *skb_in, पूर्णांक type, पूर्णांक code, __be32 info,
		 स्थिर काष्ठा ip_options *opt)
अणु
	काष्ठा iphdr *iph;
	पूर्णांक room;
	काष्ठा icmp_bxm icmp_param;
	काष्ठा rtable *rt = skb_rtable(skb_in);
	काष्ठा ipcm_cookie ipc;
	काष्ठा flowi4 fl4;
	__be32 saddr;
	u8  tos;
	u32 mark;
	काष्ठा net *net;
	काष्ठा sock *sk;

	अगर (!rt)
		जाओ out;

	अगर (rt->dst.dev)
		net = dev_net(rt->dst.dev);
	अन्यथा अगर (skb_in->dev)
		net = dev_net(skb_in->dev);
	अन्यथा
		जाओ out;

	/*
	 *	Find the original header. It is expected to be valid, of course.
	 *	Check this, icmp_send is called from the most obscure devices
	 *	someबार.
	 */
	iph = ip_hdr(skb_in);

	अगर ((u8 *)iph < skb_in->head ||
	    (skb_network_header(skb_in) + माप(*iph)) >
	    skb_tail_poपूर्णांकer(skb_in))
		जाओ out;

	/*
	 *	No replies to physical multicast/broadcast
	 */
	अगर (skb_in->pkt_type != PACKET_HOST)
		जाओ out;

	/*
	 *	Now check at the protocol level
	 */
	अगर (rt->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		जाओ out;

	/*
	 *	Only reply to fragment 0. We byte re-order the स्थिरant
	 *	mask क्रम efficiency.
	 */
	अगर (iph->frag_off & htons(IP_OFFSET))
		जाओ out;

	/*
	 *	If we send an ICMP error to an ICMP error a mess would result..
	 */
	अगर (icmp_poपूर्णांकers[type].error) अणु
		/*
		 *	We are an error, check अगर we are replying to an
		 *	ICMP error
		 */
		अगर (iph->protocol == IPPROTO_ICMP) अणु
			u8 _inner_type, *itp;

			itp = skb_header_poपूर्णांकer(skb_in,
						 skb_network_header(skb_in) +
						 (iph->ihl << 2) +
						 दुरत्व(काष्ठा icmphdr,
							  type) -
						 skb_in->data,
						 माप(_inner_type),
						 &_inner_type);
			अगर (!itp)
				जाओ out;

			/*
			 *	Assume any unknown ICMP type is an error. This
			 *	isn't specअगरied by the RFC, but think about it..
			 */
			अगर (*itp > NR_ICMP_TYPES ||
			    icmp_poपूर्णांकers[*itp].error)
				जाओ out;
		पूर्ण
	पूर्ण

	/* Needed by both icmp_global_allow and icmp_xmit_lock */
	local_bh_disable();

	/* Check global sysctl_icmp_msgs_per_sec ratelimit, unless
	 * incoming dev is loopback.  If outgoing dev change to not be
	 * loopback, then peer ratelimit still work (in icmpv4_xrlim_allow)
	 */
	अगर (!(skb_in->dev && (skb_in->dev->flags&IFF_LOOPBACK)) &&
	      !icmpv4_global_allow(net, type, code))
		जाओ out_bh_enable;

	sk = icmp_xmit_lock(net);
	अगर (!sk)
		जाओ out_bh_enable;

	/*
	 *	Conकाष्ठा source address and options.
	 */

	saddr = iph->daddr;
	अगर (!(rt->rt_flags & RTCF_LOCAL)) अणु
		काष्ठा net_device *dev = शून्य;

		rcu_पढ़ो_lock();
		अगर (rt_is_input_route(rt) &&
		    net->ipv4.sysctl_icmp_errors_use_inbound_अगरaddr)
			dev = dev_get_by_index_rcu(net, inet_iअगर(skb_in));

		अगर (dev)
			saddr = inet_select_addr(dev, iph->saddr,
						 RT_SCOPE_LINK);
		अन्यथा
			saddr = 0;
		rcu_पढ़ो_unlock();
	पूर्ण

	tos = icmp_poपूर्णांकers[type].error ? (RT_TOS(iph->tos) |
					   IPTOS_PREC_INTERNETCONTROL) :
					   iph->tos;
	mark = IP4_REPLY_MARK(net, skb_in->mark);

	अगर (__ip_options_echo(net, &icmp_param.replyopts.opt.opt, skb_in, opt))
		जाओ out_unlock;


	/*
	 *	Prepare data क्रम ICMP header.
	 */

	icmp_param.data.icmph.type	 = type;
	icmp_param.data.icmph.code	 = code;
	icmp_param.data.icmph.un.gateway = info;
	icmp_param.data.icmph.checksum	 = 0;
	icmp_param.skb	  = skb_in;
	icmp_param.offset = skb_network_offset(skb_in);
	inet_sk(sk)->tos = tos;
	ipcm_init(&ipc);
	ipc.addr = iph->saddr;
	ipc.opt = &icmp_param.replyopts.opt;
	ipc.sockc.mark = mark;

	rt = icmp_route_lookup(net, &fl4, skb_in, iph, saddr, tos, mark,
			       type, code, &icmp_param);
	अगर (IS_ERR(rt))
		जाओ out_unlock;

	/* peer icmp_ratelimit */
	अगर (!icmpv4_xrlim_allow(net, rt, &fl4, type, code))
		जाओ ende;

	/* RFC says वापस as much as we can without exceeding 576 bytes. */

	room = dst_mtu(&rt->dst);
	अगर (room > 576)
		room = 576;
	room -= माप(काष्ठा iphdr) + icmp_param.replyopts.opt.opt.optlen;
	room -= माप(काष्ठा icmphdr);

	icmp_param.data_len = skb_in->len - icmp_param.offset;
	अगर (icmp_param.data_len > room)
		icmp_param.data_len = room;
	icmp_param.head_len = माप(काष्ठा icmphdr);

	/* अगर we करोn't have a source address at this poपूर्णांक, fall back to the
	 * dummy address instead of sending out a packet with a source address
	 * of 0.0.0.0
	 */
	अगर (!fl4.saddr)
		fl4.saddr = htonl(INADDR_DUMMY);

	icmp_push_reply(&icmp_param, &fl4, &ipc, &rt);
ende:
	ip_rt_put(rt);
out_unlock:
	icmp_xmit_unlock(sk);
out_bh_enable:
	local_bh_enable();
out:;
पूर्ण
EXPORT_SYMBOL(__icmp_send);

#अगर IS_ENABLED(CONFIG_NF_NAT)
#समावेश <net/netfilter/nf_conntrack.h>
व्योम icmp_nकरो_send(काष्ठा sk_buff *skb_in, पूर्णांक type, पूर्णांक code, __be32 info)
अणु
	काष्ठा sk_buff *cloned_skb = शून्य;
	काष्ठा ip_options opts = अणु 0 पूर्ण;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	__be32 orig_ip;

	ct = nf_ct_get(skb_in, &ctinfo);
	अगर (!ct || !(ct->status & IPS_SRC_NAT)) अणु
		__icmp_send(skb_in, type, code, info, &opts);
		वापस;
	पूर्ण

	अगर (skb_shared(skb_in))
		skb_in = cloned_skb = skb_clone(skb_in, GFP_ATOMIC);

	अगर (unlikely(!skb_in || skb_network_header(skb_in) < skb_in->head ||
	    (skb_network_header(skb_in) + माप(काष्ठा iphdr)) >
	    skb_tail_poपूर्णांकer(skb_in) || skb_ensure_writable(skb_in,
	    skb_network_offset(skb_in) + माप(काष्ठा iphdr))))
		जाओ out;

	orig_ip = ip_hdr(skb_in)->saddr;
	ip_hdr(skb_in)->saddr = ct->tuplehash[0].tuple.src.u3.ip;
	__icmp_send(skb_in, type, code, info, &opts);
	ip_hdr(skb_in)->saddr = orig_ip;
out:
	consume_skb(cloned_skb);
पूर्ण
EXPORT_SYMBOL(icmp_nकरो_send);
#पूर्ण_अगर

अटल व्योम icmp_socket_deliver(काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	स्थिर काष्ठा net_protocol *ipprot;
	पूर्णांक protocol = iph->protocol;

	/* Checkin full IP header plus 8 bytes of protocol to
	 * aव्योम additional coding at protocol handlers.
	 */
	अगर (!pskb_may_pull(skb, iph->ihl * 4 + 8)) अणु
		__ICMP_INC_STATS(dev_net(skb->dev), ICMP_MIB_INERRORS);
		वापस;
	पूर्ण

	raw_icmp_error(skb, protocol, info);

	ipprot = rcu_dereference(inet_protos[protocol]);
	अगर (ipprot && ipprot->err_handler)
		ipprot->err_handler(skb, info);
पूर्ण

अटल bool icmp_tag_validation(पूर्णांक proto)
अणु
	bool ok;

	rcu_पढ़ो_lock();
	ok = rcu_dereference(inet_protos[proto])->icmp_strict_tag_validation;
	rcu_पढ़ो_unlock();
	वापस ok;
पूर्ण

/*
 *	Handle ICMP_DEST_UNREACH, ICMP_TIME_EXCEEDED, ICMP_QUENCH, and
 *	ICMP_PARAMETERPROB.
 */

अटल bool icmp_unreach(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph;
	काष्ठा icmphdr *icmph;
	काष्ठा net *net;
	u32 info = 0;

	net = dev_net(skb_dst(skb)->dev);

	/*
	 *	Incomplete header ?
	 * 	Only checks क्रम the IP header, there should be an
	 *	additional check क्रम दीर्घer headers in upper levels.
	 */

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ out_err;

	icmph = icmp_hdr(skb);
	iph   = (स्थिर काष्ठा iphdr *)skb->data;

	अगर (iph->ihl < 5) /* Mangled header, drop. */
		जाओ out_err;

	चयन (icmph->type) अणु
	हाल ICMP_DEST_UNREACH:
		चयन (icmph->code & 15) अणु
		हाल ICMP_NET_UNREACH:
		हाल ICMP_HOST_UNREACH:
		हाल ICMP_PROT_UNREACH:
		हाल ICMP_PORT_UNREACH:
			अवरोध;
		हाल ICMP_FRAG_NEEDED:
			/* क्रम करोcumentation of the ip_no_pmtu_disc
			 * values please see
			 * Documentation/networking/ip-sysctl.rst
			 */
			चयन (net->ipv4.sysctl_ip_no_pmtu_disc) अणु
			शेष:
				net_dbg_ratelimited("%pI4: fragmentation needed and DF set\n",
						    &iph->daddr);
				अवरोध;
			हाल 2:
				जाओ out;
			हाल 3:
				अगर (!icmp_tag_validation(iph->protocol))
					जाओ out;
				fallthrough;
			हाल 0:
				info = ntohs(icmph->un.frag.mtu);
			पूर्ण
			अवरोध;
		हाल ICMP_SR_FAILED:
			net_dbg_ratelimited("%pI4: Source Route Failed\n",
					    &iph->daddr);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (icmph->code > NR_ICMP_UNREACH)
			जाओ out;
		अवरोध;
	हाल ICMP_PARAMETERPROB:
		info = ntohl(icmph->un.gateway) >> 24;
		अवरोध;
	हाल ICMP_TIME_EXCEEDED:
		__ICMP_INC_STATS(net, ICMP_MIB_INTIMEEXCDS);
		अगर (icmph->code == ICMP_EXC_FRAGTIME)
			जाओ out;
		अवरोध;
	पूर्ण

	/*
	 *	Throw it at our lower layers
	 *
	 *	RFC 1122: 3.2.2 MUST extract the protocol ID from the passed
	 *		  header.
	 *	RFC 1122: 3.2.2.1 MUST pass ICMP unreach messages to the
	 *		  transport layer.
	 *	RFC 1122: 3.2.2.2 MUST pass ICMP समय expired messages to
	 *		  transport layer.
	 */

	/*
	 *	Check the other end isn't violating RFC 1122. Some routers send
	 *	bogus responses to broadcast frames. If you see this message
	 *	first check your neपंचांगask matches at both ends, अगर it करोes then
	 *	get the other venकरोr to fix their kit.
	 */

	अगर (!net->ipv4.sysctl_icmp_ignore_bogus_error_responses &&
	    inet_addr_type_dev_table(net, skb->dev, iph->daddr) == RTN_BROADCAST) अणु
		net_warn_ratelimited("%pI4 sent an invalid ICMP type %u, code %u error to a broadcast: %pI4 on %s\n",
				     &ip_hdr(skb)->saddr,
				     icmph->type, icmph->code,
				     &iph->daddr, skb->dev->name);
		जाओ out;
	पूर्ण

	icmp_socket_deliver(skb, info);

out:
	वापस true;
out_err:
	__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
	वापस false;
पूर्ण


/*
 *	Handle ICMP_REसूचीECT.
 */

अटल bool icmp_redirect(काष्ठा sk_buff *skb)
अणु
	अगर (skb->len < माप(काष्ठा iphdr)) अणु
		__ICMP_INC_STATS(dev_net(skb->dev), ICMP_MIB_INERRORS);
		वापस false;
	पूर्ण

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr))) अणु
		/* there aught to be a stat */
		वापस false;
	पूर्ण

	icmp_socket_deliver(skb, ntohl(icmp_hdr(skb)->un.gateway));
	वापस true;
पूर्ण

/*
 *	Handle ICMP_ECHO ("ping") and ICMP_EXT_ECHO ("PROBE") requests.
 *
 *	RFC 1122: 3.2.2.6 MUST have an echo server that answers ICMP echo
 *		  requests.
 *	RFC 1122: 3.2.2.6 Data received in the ICMP_ECHO request MUST be
 *		  included in the reply.
 *	RFC 1812: 4.3.3.6 SHOULD have a config option क्रम silently ignoring
 *		  echo requests, MUST have शेष=NOT.
 *	RFC 8335: 8 MUST have a config option to enable/disable ICMP
 *		  Extended Echo Functionality, MUST be disabled by शेष
 *	See also WRT handling of options once they are करोne and working.
 */

अटल bool icmp_echo(काष्ठा sk_buff *skb)
अणु
	काष्ठा icmp_ext_hdr *ext_hdr, _ext_hdr;
	काष्ठा icmp_ext_echo_iio *iio, _iio;
	काष्ठा icmp_bxm icmp_param;
	काष्ठा net_device *dev;
	अक्षर buff[IFNAMSIZ];
	काष्ठा net *net;
	u16 ident_len;
	u8 status;

	net = dev_net(skb_dst(skb)->dev);
	/* should there be an ICMP stat क्रम ignored echos? */
	अगर (net->ipv4.sysctl_icmp_echo_ignore_all)
		वापस true;

	icmp_param.data.icmph	   = *icmp_hdr(skb);
	icmp_param.skb		   = skb;
	icmp_param.offset	   = 0;
	icmp_param.data_len	   = skb->len;
	icmp_param.head_len	   = माप(काष्ठा icmphdr);

	अगर (icmp_param.data.icmph.type == ICMP_ECHO) अणु
		icmp_param.data.icmph.type = ICMP_ECHOREPLY;
		जाओ send_reply;
	पूर्ण
	अगर (!net->ipv4.sysctl_icmp_echo_enable_probe)
		वापस true;
	/* We currently only support probing पूर्णांकerfaces on the proxy node
	 * Check to ensure L-bit is set
	 */
	अगर (!(ntohs(icmp_param.data.icmph.un.echo.sequence) & 1))
		वापस true;
	/* Clear status bits in reply message */
	icmp_param.data.icmph.un.echo.sequence &= htons(0xFF00);
	icmp_param.data.icmph.type = ICMP_EXT_ECHOREPLY;
	ext_hdr = skb_header_poपूर्णांकer(skb, 0, माप(_ext_hdr), &_ext_hdr);
	/* Size of iio is class_type dependent.
	 * Only check header here and assign length based on ctype in the चयन statement
	 */
	iio = skb_header_poपूर्णांकer(skb, माप(_ext_hdr), माप(iio->extobj_hdr), &_iio);
	अगर (!ext_hdr || !iio)
		जाओ send_mal_query;
	अगर (ntohs(iio->extobj_hdr.length) <= माप(iio->extobj_hdr))
		जाओ send_mal_query;
	ident_len = ntohs(iio->extobj_hdr.length) - माप(iio->extobj_hdr);
	status = 0;
	dev = शून्य;
	चयन (iio->extobj_hdr.class_type) अणु
	हाल ICMP_EXT_ECHO_CTYPE_NAME:
		iio = skb_header_poपूर्णांकer(skb, माप(_ext_hdr), माप(_iio), &_iio);
		अगर (ident_len >= IFNAMSIZ)
			जाओ send_mal_query;
		स_रखो(buff, 0, माप(buff));
		स_नकल(buff, &iio->ident.name, ident_len);
		dev = dev_get_by_name(net, buff);
		अवरोध;
	हाल ICMP_EXT_ECHO_CTYPE_INDEX:
		iio = skb_header_poपूर्णांकer(skb, माप(_ext_hdr), माप(iio->extobj_hdr) +
					 माप(iio->ident.अगरindex), &_iio);
		अगर (ident_len != माप(iio->ident.अगरindex))
			जाओ send_mal_query;
		dev = dev_get_by_index(net, ntohl(iio->ident.अगरindex));
		अवरोध;
	हाल ICMP_EXT_ECHO_CTYPE_ADDR:
		अगर (ident_len != माप(iio->ident.addr.ctype3_hdr) +
				 iio->ident.addr.ctype3_hdr.addrlen)
			जाओ send_mal_query;
		चयन (ntohs(iio->ident.addr.ctype3_hdr.afi)) अणु
		हाल ICMP_AFI_IP:
			iio = skb_header_poपूर्णांकer(skb, माप(_ext_hdr), माप(iio->extobj_hdr) +
						 माप(काष्ठा in_addr), &_iio);
			अगर (ident_len != माप(iio->ident.addr.ctype3_hdr) +
					 माप(काष्ठा in_addr))
				जाओ send_mal_query;
			dev = ip_dev_find(net, iio->ident.addr.ip_addr.ipv4_addr.s_addr);
			अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल ICMP_AFI_IP6:
			iio = skb_header_poपूर्णांकer(skb, माप(_ext_hdr), माप(_iio), &_iio);
			अगर (ident_len != माप(iio->ident.addr.ctype3_hdr) +
					 माप(काष्ठा in6_addr))
				जाओ send_mal_query;
			dev = ipv6_stub->ipv6_dev_find(net, &iio->ident.addr.ip_addr.ipv6_addr, dev);
			अगर (dev)
				dev_hold(dev);
			अवरोध;
#पूर्ण_अगर
		शेष:
			जाओ send_mal_query;
		पूर्ण
		अवरोध;
	शेष:
		जाओ send_mal_query;
	पूर्ण
	अगर (!dev) अणु
		icmp_param.data.icmph.code = ICMP_EXT_CODE_NO_IF;
		जाओ send_reply;
	पूर्ण
	/* Fill bits in reply message */
	अगर (dev->flags & IFF_UP)
		status |= ICMP_EXT_ECHOREPLY_ACTIVE;
	अगर (__in_dev_get_rcu(dev) && __in_dev_get_rcu(dev)->अगरa_list)
		status |= ICMP_EXT_ECHOREPLY_IPV4;
	अगर (!list_empty(&rcu_dereference(dev->ip6_ptr)->addr_list))
		status |= ICMP_EXT_ECHOREPLY_IPV6;
	dev_put(dev);
	icmp_param.data.icmph.un.echo.sequence |= htons(status);
send_reply:
	icmp_reply(&icmp_param, skb);
		वापस true;
send_mal_query:
	icmp_param.data.icmph.code = ICMP_EXT_CODE_MAL_QUERY;
	जाओ send_reply;
पूर्ण

/*
 *	Handle ICMP Timestamp requests.
 *	RFC 1122: 3.2.2.8 MAY implement ICMP बारtamp requests.
 *		  SHOULD be in the kernel क्रम minimum अक्रमom latency.
 *		  MUST be accurate to a few minutes.
 *		  MUST be updated at least at 15Hz.
 */
अटल bool icmp_बारtamp(काष्ठा sk_buff *skb)
अणु
	काष्ठा icmp_bxm icmp_param;
	/*
	 *	Too लघु.
	 */
	अगर (skb->len < 4)
		जाओ out_err;

	/*
	 *	Fill in the current समय as ms since midnight UT:
	 */
	icmp_param.data.बार[1] = inet_current_बारtamp();
	icmp_param.data.बार[2] = icmp_param.data.बार[1];

	BUG_ON(skb_copy_bits(skb, 0, &icmp_param.data.बार[0], 4));

	icmp_param.data.icmph	   = *icmp_hdr(skb);
	icmp_param.data.icmph.type = ICMP_TIMESTAMPREPLY;
	icmp_param.data.icmph.code = 0;
	icmp_param.skb		   = skb;
	icmp_param.offset	   = 0;
	icmp_param.data_len	   = 0;
	icmp_param.head_len	   = माप(काष्ठा icmphdr) + 12;
	icmp_reply(&icmp_param, skb);
	वापस true;

out_err:
	__ICMP_INC_STATS(dev_net(skb_dst(skb)->dev), ICMP_MIB_INERRORS);
	वापस false;
पूर्ण

अटल bool icmp_discard(काष्ठा sk_buff *skb)
अणु
	/* pretend it was a success */
	वापस true;
पूर्ण

/*
 *	Deal with incoming ICMP packets.
 */
पूर्णांक icmp_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा icmphdr *icmph;
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा net *net = dev_net(rt->dst.dev);
	bool success;

	अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
		काष्ठा sec_path *sp = skb_sec_path(skb);
		पूर्णांक nh;

		अगर (!(sp && sp->xvec[sp->len - 1]->props.flags &
				 XFRM_STATE_ICMP))
			जाओ drop;

		अगर (!pskb_may_pull(skb, माप(*icmph) + माप(काष्ठा iphdr)))
			जाओ drop;

		nh = skb_network_offset(skb);
		skb_set_network_header(skb, माप(*icmph));

		अगर (!xfrm4_policy_check_reverse(शून्य, XFRM_POLICY_IN, skb))
			जाओ drop;

		skb_set_network_header(skb, nh);
	पूर्ण

	__ICMP_INC_STATS(net, ICMP_MIB_INMSGS);

	अगर (skb_checksum_simple_validate(skb))
		जाओ csum_error;

	अगर (!pskb_pull(skb, माप(*icmph)))
		जाओ error;

	icmph = icmp_hdr(skb);

	ICMPMSGIN_INC_STATS(net, icmph->type);

	/* Check क्रम ICMP Extended Echo (PROBE) messages */
	अगर (icmph->type == ICMP_EXT_ECHO) अणु
		/* We can't use icmp_poपूर्णांकers[].handler() because it is an array of
		 * size NR_ICMP_TYPES + 1 (19 elements) and PROBE has code 42.
		 */
		success = icmp_echo(skb);
		जाओ success_check;
	पूर्ण

	अगर (icmph->type == ICMP_EXT_ECHOREPLY) अणु
		success = ping_rcv(skb);
		जाओ success_check;
	पूर्ण

	/*
	 *	18 is the highest 'known' ICMP type. Anything अन्यथा is a mystery
	 *
	 *	RFC 1122: 3.2.2  Unknown ICMP messages types MUST be silently
	 *		  discarded.
	 */
	अगर (icmph->type > NR_ICMP_TYPES)
		जाओ error;

	/*
	 *	Parse the ICMP message
	 */

	अगर (rt->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST)) अणु
		/*
		 *	RFC 1122: 3.2.2.6 An ICMP_ECHO to broadcast MAY be
		 *	  silently ignored (we let user decide with a sysctl).
		 *	RFC 1122: 3.2.2.8 An ICMP_TIMESTAMP MAY be silently
		 *	  discarded अगर to broadcast/multicast.
		 */
		अगर ((icmph->type == ICMP_ECHO ||
		     icmph->type == ICMP_TIMESTAMP) &&
		    net->ipv4.sysctl_icmp_echo_ignore_broadcasts) अणु
			जाओ error;
		पूर्ण
		अगर (icmph->type != ICMP_ECHO &&
		    icmph->type != ICMP_TIMESTAMP &&
		    icmph->type != ICMP_ADDRESS &&
		    icmph->type != ICMP_ADDRESSREPLY) अणु
			जाओ error;
		पूर्ण
	पूर्ण

	success = icmp_poपूर्णांकers[icmph->type].handler(skb);
success_check:
	अगर (success)  अणु
		consume_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
csum_error:
	__ICMP_INC_STATS(net, ICMP_MIB_CSUMERRORS);
error:
	__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
	जाओ drop;
पूर्ण

अटल bool ip_icmp_error_rfc4884_validate(स्थिर काष्ठा sk_buff *skb, पूर्णांक off)
अणु
	काष्ठा icmp_extobj_hdr *objh, _objh;
	काष्ठा icmp_ext_hdr *exth, _exth;
	u16 olen;

	exth = skb_header_poपूर्णांकer(skb, off, माप(_exth), &_exth);
	अगर (!exth)
		वापस false;
	अगर (exth->version != 2)
		वापस true;

	अगर (exth->checksum &&
	    csum_fold(skb_checksum(skb, off, skb->len - off, 0)))
		वापस false;

	off += माप(_exth);
	जबतक (off < skb->len) अणु
		objh = skb_header_poपूर्णांकer(skb, off, माप(_objh), &_objh);
		अगर (!objh)
			वापस false;

		olen = ntohs(objh->length);
		अगर (olen < माप(_objh))
			वापस false;

		off += olen;
		अगर (off > skb->len)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम ip_icmp_error_rfc4884(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा sock_ee_data_rfc4884 *out,
			   पूर्णांक thlen, पूर्णांक off)
अणु
	पूर्णांक hlen;

	/* original datagram headers: end of icmph to payload (skb->data) */
	hlen = -skb_transport_offset(skb) - thlen;

	/* per rfc 4884: minimal datagram length of 128 bytes */
	अगर (off < 128 || off < hlen)
		वापस;

	/* kernel has stripped headers: वापस payload offset in bytes */
	off -= hlen;
	अगर (off + माप(काष्ठा icmp_ext_hdr) > skb->len)
		वापस;

	out->len = off;

	अगर (!ip_icmp_error_rfc4884_validate(skb, off))
		out->flags |= SO_EE_RFC4884_FLAG_INVALID;
पूर्ण
EXPORT_SYMBOL_GPL(ip_icmp_error_rfc4884);

पूर्णांक icmp_err(काष्ठा sk_buff *skb, u32 info)
अणु
	काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;
	पूर्णांक offset = iph->ihl<<2;
	काष्ठा icmphdr *icmph = (काष्ठा icmphdr *)(skb->data + offset);
	पूर्णांक type = icmp_hdr(skb)->type;
	पूर्णांक code = icmp_hdr(skb)->code;
	काष्ठा net *net = dev_net(skb->dev);

	/*
	 * Use ping_err to handle all icmp errors except those
	 * triggered by ICMP_ECHOREPLY which sent from kernel.
	 */
	अगर (icmph->type != ICMP_ECHOREPLY) अणु
		ping_err(skb, offset, info);
		वापस 0;
	पूर्ण

	अगर (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED)
		ipv4_update_pmtu(skb, net, info, 0, IPPROTO_ICMP);
	अन्यथा अगर (type == ICMP_REसूचीECT)
		ipv4_redirect(skb, net, 0, IPPROTO_ICMP);

	वापस 0;
पूर्ण

/*
 *	This table is the definition of how we handle ICMP.
 */
अटल स्थिर काष्ठा icmp_control icmp_poपूर्णांकers[NR_ICMP_TYPES + 1] = अणु
	[ICMP_ECHOREPLY] = अणु
		.handler = ping_rcv,
	पूर्ण,
	[1] = अणु
		.handler = icmp_discard,
		.error = 1,
	पूर्ण,
	[2] = अणु
		.handler = icmp_discard,
		.error = 1,
	पूर्ण,
	[ICMP_DEST_UNREACH] = अणु
		.handler = icmp_unreach,
		.error = 1,
	पूर्ण,
	[ICMP_SOURCE_QUENCH] = अणु
		.handler = icmp_unreach,
		.error = 1,
	पूर्ण,
	[ICMP_REसूचीECT] = अणु
		.handler = icmp_redirect,
		.error = 1,
	पूर्ण,
	[6] = अणु
		.handler = icmp_discard,
		.error = 1,
	पूर्ण,
	[7] = अणु
		.handler = icmp_discard,
		.error = 1,
	पूर्ण,
	[ICMP_ECHO] = अणु
		.handler = icmp_echo,
	पूर्ण,
	[9] = अणु
		.handler = icmp_discard,
		.error = 1,
	पूर्ण,
	[10] = अणु
		.handler = icmp_discard,
		.error = 1,
	पूर्ण,
	[ICMP_TIME_EXCEEDED] = अणु
		.handler = icmp_unreach,
		.error = 1,
	पूर्ण,
	[ICMP_PARAMETERPROB] = अणु
		.handler = icmp_unreach,
		.error = 1,
	पूर्ण,
	[ICMP_TIMESTAMP] = अणु
		.handler = icmp_बारtamp,
	पूर्ण,
	[ICMP_TIMESTAMPREPLY] = अणु
		.handler = icmp_discard,
	पूर्ण,
	[ICMP_INFO_REQUEST] = अणु
		.handler = icmp_discard,
	पूर्ण,
	[ICMP_INFO_REPLY] = अणु
		.handler = icmp_discard,
	पूर्ण,
	[ICMP_ADDRESS] = अणु
		.handler = icmp_discard,
	पूर्ण,
	[ICMP_ADDRESSREPLY] = अणु
		.handler = icmp_discard,
	पूर्ण,
पूर्ण;

अटल व्योम __net_निकास icmp_sk_निकास(काष्ठा net *net)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		inet_ctl_sock_destroy(*per_cpu_ptr(net->ipv4.icmp_sk, i));
	मुक्त_percpu(net->ipv4.icmp_sk);
	net->ipv4.icmp_sk = शून्य;
पूर्ण

अटल पूर्णांक __net_init icmp_sk_init(काष्ठा net *net)
अणु
	पूर्णांक i, err;

	net->ipv4.icmp_sk = alloc_percpu(काष्ठा sock *);
	अगर (!net->ipv4.icmp_sk)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा sock *sk;

		err = inet_ctl_sock_create(&sk, PF_INET,
					   SOCK_RAW, IPPROTO_ICMP, net);
		अगर (err < 0)
			जाओ fail;

		*per_cpu_ptr(net->ipv4.icmp_sk, i) = sk;

		/* Enough space क्रम 2 64K ICMP packets, including
		 * sk_buff/skb_shared_info काष्ठा overhead.
		 */
		sk->sk_sndbuf =	2 * SKB_TRUESIZE(64 * 1024);

		/*
		 * Speedup sock_wमुक्त()
		 */
		sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);
		inet_sk(sk)->pmtudisc = IP_PMTUDISC_DONT;
	पूर्ण

	/* Control parameters क्रम ECHO replies. */
	net->ipv4.sysctl_icmp_echo_ignore_all = 0;
	net->ipv4.sysctl_icmp_echo_enable_probe = 0;
	net->ipv4.sysctl_icmp_echo_ignore_broadcasts = 1;

	/* Control parameter - ignore bogus broadcast responses? */
	net->ipv4.sysctl_icmp_ignore_bogus_error_responses = 1;

	/*
	 * 	Configurable global rate limit.
	 *
	 *	ratelimit defines tokens/packet consumed क्रम dst->rate_token
	 *	bucket ratemask defines which icmp types are ratelimited by
	 *	setting	it's bit position.
	 *
	 *	शेष:
	 *	dest unreachable (3), source quench (4),
	 *	समय exceeded (11), parameter problem (12)
	 */

	net->ipv4.sysctl_icmp_ratelimit = 1 * HZ;
	net->ipv4.sysctl_icmp_ratemask = 0x1818;
	net->ipv4.sysctl_icmp_errors_use_inbound_अगरaddr = 0;

	वापस 0;

fail:
	icmp_sk_निकास(net);
	वापस err;
पूर्ण

अटल काष्ठा pernet_operations __net_initdata icmp_sk_ops = अणु
       .init = icmp_sk_init,
       .निकास = icmp_sk_निकास,
पूर्ण;

पूर्णांक __init icmp_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&icmp_sk_ops);
पूर्ण
