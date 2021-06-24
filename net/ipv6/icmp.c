<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Internet Control Message Protocol (ICMPv6)
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on net/ipv4/icmp.c
 *
 *	RFC 1885
 */

/*
 *	Changes:
 *
 *	Andi Kleen		:	exception handling
 *	Andi Kleen			add rate limits. never reply to a icmp.
 *					add more length checks and other fixes.
 *	yoshfuji		:	ensure to sent parameter problem क्रम
 *					fragments.
 *	YOSHIFUJI Hideaki @USAGI:	added sysctl क्रम icmp rate limit.
 *	Randy Dunlap and
 *	YOSHIFUJI Hideaki @USAGI:	Per-पूर्णांकerface statistics support
 *	Kazunori MIYAZAWA @USAGI:       change output process to use ip6_append_data
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/icmpv6.h>

#समावेश <net/ip.h>
#समावेश <net/sock.h>

#समावेश <net/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/ping.h>
#समावेश <net/protocol.h>
#समावेश <net/raw.h>
#समावेश <net/rawv6.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/icmp.h>
#समावेश <net/xfrm.h>
#समावेश <net/inet_common.h>
#समावेश <net/dsfield.h>
#समावेश <net/l3mdev.h>

#समावेश <linux/uaccess.h>

/*
 *	The ICMP socket(s). This is the most convenient way to flow control
 *	our ICMP output as well as मुख्यtain a clean पूर्णांकerface throughout
 *	all layers. All Socketless IP sends will soon be gone.
 *
 *	On SMP we have one ICMP socket per-cpu.
 */
अटल काष्ठा sock *icmpv6_sk(काष्ठा net *net)
अणु
	वापस this_cpu_पढ़ो(*net->ipv6.icmp_sk);
पूर्ण

अटल पूर्णांक icmpv6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		       u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	/* icmpv6_notअगरy checks 8 bytes can be pulled, icmp6hdr is 8 bytes */
	काष्ठा icmp6hdr *icmp6 = (काष्ठा icmp6hdr *) (skb->data + offset);
	काष्ठा net *net = dev_net(skb->dev);

	अगर (type == ICMPV6_PKT_TOOBIG)
		ip6_update_pmtu(skb, net, info, skb->dev->अगरindex, 0, sock_net_uid(net, शून्य));
	अन्यथा अगर (type == NDISC_REसूचीECT)
		ip6_redirect(skb, net, skb->dev->अगरindex, 0,
			     sock_net_uid(net, शून्य));

	अगर (!(type & ICMPV6_INFOMSG_MASK))
		अगर (icmp6->icmp6_type == ICMPV6_ECHO_REQUEST)
			ping_err(skb, offset, ntohl(info));

	वापस 0;
पूर्ण

अटल पूर्णांक icmpv6_rcv(काष्ठा sk_buff *skb);

अटल स्थिर काष्ठा inet6_protocol icmpv6_protocol = अणु
	.handler	=	icmpv6_rcv,
	.err_handler	=	icmpv6_err,
	.flags		=	INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

/* Called with BH disabled */
अटल __अंतरभूत__ काष्ठा sock *icmpv6_xmit_lock(काष्ठा net *net)
अणु
	काष्ठा sock *sk;

	sk = icmpv6_sk(net);
	अगर (unlikely(!spin_trylock(&sk->sk_lock.slock))) अणु
		/* This can happen अगर the output path (f.e. SIT or
		 * ip6ip6 tunnel) संकेतs dst_link_failure() क्रम an
		 * outgoing ICMP6 packet.
		 */
		वापस शून्य;
	पूर्ण
	वापस sk;
पूर्ण

अटल __अंतरभूत__ व्योम icmpv6_xmit_unlock(काष्ठा sock *sk)
अणु
	spin_unlock(&sk->sk_lock.slock);
पूर्ण

/*
 * Figure out, may we reply to this packet with icmp error.
 *
 * We करो not reply, अगर:
 *	- it was icmp error message.
 *	- it is truncated, so that it is known, that protocol is ICMPV6
 *	  (i.e. in the middle of some exthdr)
 *
 *	--ANK (980726)
 */

अटल bool is_ineligible(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक ptr = (u8 *)(ipv6_hdr(skb) + 1) - skb->data;
	पूर्णांक len = skb->len - ptr;
	__u8 nexthdr = ipv6_hdr(skb)->nexthdr;
	__be16 frag_off;

	अगर (len < 0)
		वापस true;

	ptr = ipv6_skip_exthdr(skb, ptr, &nexthdr, &frag_off);
	अगर (ptr < 0)
		वापस false;
	अगर (nexthdr == IPPROTO_ICMPV6) अणु
		u8 _type, *tp;
		tp = skb_header_poपूर्णांकer(skb,
			ptr+दुरत्व(काष्ठा icmp6hdr, icmp6_type),
			माप(_type), &_type);

		/* Based on RFC 8200, Section 4.5 Fragment Header, वापस
		 * false अगर this is a fragment packet with no icmp header info.
		 */
		अगर (!tp && frag_off != 0)
			वापस false;
		अन्यथा अगर (!tp || !(*tp & ICMPV6_INFOMSG_MASK))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool icmpv6_mask_allow(काष्ठा net *net, पूर्णांक type)
अणु
	अगर (type > ICMPV6_MSG_MAX)
		वापस true;

	/* Limit अगर icmp type is set in ratemask. */
	अगर (!test_bit(type, net->ipv6.sysctl.icmpv6_ratemask))
		वापस true;

	वापस false;
पूर्ण

अटल bool icmpv6_global_allow(काष्ठा net *net, पूर्णांक type)
अणु
	अगर (icmpv6_mask_allow(net, type))
		वापस true;

	अगर (icmp_global_allow())
		वापस true;

	वापस false;
पूर्ण

/*
 * Check the ICMP output rate limit
 */
अटल bool icmpv6_xrlim_allow(काष्ठा sock *sk, u8 type,
			       काष्ठा flowi6 *fl6)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा dst_entry *dst;
	bool res = false;

	अगर (icmpv6_mask_allow(net, type))
		वापस true;

	/*
	 * Look up the output route.
	 * XXX: perhaps the expire क्रम routing entries cloned by
	 * this lookup should be more aggressive (not दीर्घer than समयout).
	 */
	dst = ip6_route_output(net, sk, fl6);
	अगर (dst->error) अणु
		IP6_INC_STATS(net, ip6_dst_idev(dst),
			      IPSTATS_MIB_OUTNOROUTES);
	पूर्ण अन्यथा अगर (dst->dev && (dst->dev->flags&IFF_LOOPBACK)) अणु
		res = true;
	पूर्ण अन्यथा अणु
		काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;
		पूर्णांक पंचांगo = net->ipv6.sysctl.icmpv6_समय;
		काष्ठा inet_peer *peer;

		/* Give more bandwidth to wider prefixes. */
		अगर (rt->rt6i_dst.plen < 128)
			पंचांगo >>= ((128 - rt->rt6i_dst.plen)>>5);

		peer = inet_getpeer_v6(net->ipv6.peers, &fl6->daddr, 1);
		res = inet_peer_xrlim_allow(peer, पंचांगo);
		अगर (peer)
			inet_putpeer(peer);
	पूर्ण
	dst_release(dst);
	वापस res;
पूर्ण

अटल bool icmpv6_rt_has_prefsrc(काष्ठा sock *sk, u8 type,
				  काष्ठा flowi6 *fl6)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा dst_entry *dst;
	bool res = false;

	dst = ip6_route_output(net, sk, fl6);
	अगर (!dst->error) अणु
		काष्ठा rt6_info *rt = (काष्ठा rt6_info *)dst;
		काष्ठा in6_addr prefsrc;

		rt6_get_prefsrc(rt, &prefsrc);
		res = !ipv6_addr_any(&prefsrc);
	पूर्ण
	dst_release(dst);
	वापस res;
पूर्ण

/*
 *	an अंतरभूत helper क्रम the "simple" अगर statement below
 *	checks अगर parameter problem report is caused by an
 *	unrecognized IPv6 option that has the Option Type
 *	highest-order two bits set to 10
 */

अटल bool opt_unrec(काष्ठा sk_buff *skb, __u32 offset)
अणु
	u8 _optval, *op;

	offset += skb_network_offset(skb);
	op = skb_header_poपूर्णांकer(skb, offset, माप(_optval), &_optval);
	अगर (!op)
		वापस true;
	वापस (*op & 0xC0) == 0x80;
पूर्ण

व्योम icmpv6_push_pending_frames(काष्ठा sock *sk, काष्ठा flowi6 *fl6,
				काष्ठा icmp6hdr *thdr, पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा icmp6hdr *icmp6h;

	skb = skb_peek(&sk->sk_ग_लिखो_queue);
	अगर (!skb)
		वापस;

	icmp6h = icmp6_hdr(skb);
	स_नकल(icmp6h, thdr, माप(काष्ठा icmp6hdr));
	icmp6h->icmp6_cksum = 0;

	अगर (skb_queue_len(&sk->sk_ग_लिखो_queue) == 1) अणु
		skb->csum = csum_partial(icmp6h,
					माप(काष्ठा icmp6hdr), skb->csum);
		icmp6h->icmp6_cksum = csum_ipv6_magic(&fl6->saddr,
						      &fl6->daddr,
						      len, fl6->flowi6_proto,
						      skb->csum);
	पूर्ण अन्यथा अणु
		__wsum पंचांगp_csum = 0;

		skb_queue_walk(&sk->sk_ग_लिखो_queue, skb) अणु
			पंचांगp_csum = csum_add(पंचांगp_csum, skb->csum);
		पूर्ण

		पंचांगp_csum = csum_partial(icmp6h,
					माप(काष्ठा icmp6hdr), पंचांगp_csum);
		icmp6h->icmp6_cksum = csum_ipv6_magic(&fl6->saddr,
						      &fl6->daddr,
						      len, fl6->flowi6_proto,
						      पंचांगp_csum);
	पूर्ण
	ip6_push_pending_frames(sk);
पूर्ण

काष्ठा icmpv6_msg अणु
	काष्ठा sk_buff	*skb;
	पूर्णांक		offset;
	uपूर्णांक8_t		type;
पूर्ण;

अटल पूर्णांक icmpv6_getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb)
अणु
	काष्ठा icmpv6_msg *msg = (काष्ठा icmpv6_msg *) from;
	काष्ठा sk_buff *org_skb = msg->skb;
	__wsum csum;

	csum = skb_copy_and_csum_bits(org_skb, msg->offset + offset,
				      to, len);
	skb->csum = csum_block_add(skb->csum, csum, odd);
	अगर (!(msg->type & ICMPV6_INFOMSG_MASK))
		nf_ct_attach(skb, org_skb);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
अटल व्योम mip6_addr_swap(काष्ठा sk_buff *skb, स्थिर काष्ठा inet6_skb_parm *opt)
अणु
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा ipv6_destopt_hao *hao;
	काष्ठा in6_addr पंचांगp;
	पूर्णांक off;

	अगर (opt->dsthao) अणु
		off = ipv6_find_tlv(skb, opt->dsthao, IPV6_TLV_HAO);
		अगर (likely(off >= 0)) अणु
			hao = (काष्ठा ipv6_destopt_hao *)
					(skb_network_header(skb) + off);
			पंचांगp = iph->saddr;
			iph->saddr = hao->addr;
			hao->addr = पंचांगp;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mip6_addr_swap(काष्ठा sk_buff *skb, स्थिर काष्ठा inet6_skb_parm *opt) अणुपूर्ण
#पूर्ण_अगर

अटल काष्ठा dst_entry *icmpv6_route_lookup(काष्ठा net *net,
					     काष्ठा sk_buff *skb,
					     काष्ठा sock *sk,
					     काष्ठा flowi6 *fl6)
अणु
	काष्ठा dst_entry *dst, *dst2;
	काष्ठा flowi6 fl2;
	पूर्णांक err;

	err = ip6_dst_lookup(net, sk, &dst, fl6);
	अगर (err)
		वापस ERR_PTR(err);

	/*
	 * We won't send icmp अगर the destination is known
	 * anycast.
	 */
	अगर (ipv6_anycast_destination(dst, &fl6->daddr)) अणु
		net_dbg_ratelimited("icmp6_send: acast source\n");
		dst_release(dst);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* No need to clone since we're just using its address. */
	dst2 = dst;

	dst = xfrm_lookup(net, dst, flowi6_to_flowi(fl6), sk, 0);
	अगर (!IS_ERR(dst)) अणु
		अगर (dst != dst2)
			वापस dst;
	पूर्ण अन्यथा अणु
		अगर (PTR_ERR(dst) == -EPERM)
			dst = शून्य;
		अन्यथा
			वापस dst;
	पूर्ण

	err = xfrm_decode_session_reverse(skb, flowi6_to_flowi(&fl2), AF_INET6);
	अगर (err)
		जाओ relookup_failed;

	err = ip6_dst_lookup(net, sk, &dst2, &fl2);
	अगर (err)
		जाओ relookup_failed;

	dst2 = xfrm_lookup(net, dst2, flowi6_to_flowi(&fl2), sk, XFRM_LOOKUP_ICMP);
	अगर (!IS_ERR(dst2)) अणु
		dst_release(dst);
		dst = dst2;
	पूर्ण अन्यथा अणु
		err = PTR_ERR(dst2);
		अगर (err == -EPERM) अणु
			dst_release(dst);
			वापस dst2;
		पूर्ण अन्यथा
			जाओ relookup_failed;
	पूर्ण

relookup_failed:
	अगर (dst)
		वापस dst;
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा net_device *icmp6_dev(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;

	/* क्रम local traffic to local address, skb dev is the loopback
	 * device. Check अगर there is a dst attached to the skb and अगर so
	 * get the real device index. Same is needed क्रम replies to a link
	 * local address on a device enslaved to an L3 master device
	 */
	अगर (unlikely(dev->अगरindex == LOOPBACK_IFINDEX || netअगर_is_l3_master(skb->dev))) अणु
		स्थिर काष्ठा rt6_info *rt6 = skb_rt6_info(skb);

		अगर (rt6)
			dev = rt6->rt6i_idev->dev;
	पूर्ण

	वापस dev;
पूर्ण

अटल पूर्णांक icmp6_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस icmp6_dev(skb)->अगरindex;
पूर्ण

/*
 *	Send an ICMP message in response to a packet in error
 */
व्योम icmp6_send(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info,
		स्थिर काष्ठा in6_addr *क्रमce_saddr,
		स्थिर काष्ठा inet6_skb_parm *parm)
अणु
	काष्ठा inet6_dev *idev = शून्य;
	काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	काष्ठा sock *sk;
	काष्ठा net *net;
	काष्ठा ipv6_pinfo *np;
	स्थिर काष्ठा in6_addr *saddr = शून्य;
	काष्ठा dst_entry *dst;
	काष्ठा icmp6hdr पंचांगp_hdr;
	काष्ठा flowi6 fl6;
	काष्ठा icmpv6_msg msg;
	काष्ठा ipcm6_cookie ipc6;
	पूर्णांक iअगर = 0;
	पूर्णांक addr_type = 0;
	पूर्णांक len;
	u32 mark;

	अगर ((u8 *)hdr < skb->head ||
	    (skb_network_header(skb) + माप(*hdr)) > skb_tail_poपूर्णांकer(skb))
		वापस;

	अगर (!skb->dev)
		वापस;
	net = dev_net(skb->dev);
	mark = IP6_REPLY_MARK(net, skb->mark);
	/*
	 *	Make sure we respect the rules
	 *	i.e. RFC 1885 2.4(e)
	 *	Rule (e.1) is enक्रमced by not using icmp6_send
	 *	in any code that processes icmp errors.
	 */
	addr_type = ipv6_addr_type(&hdr->daddr);

	अगर (ipv6_chk_addr(net, &hdr->daddr, skb->dev, 0) ||
	    ipv6_chk_acast_addr_src(net, skb->dev, &hdr->daddr))
		saddr = &hdr->daddr;

	/*
	 *	Dest addr check
	 */

	अगर (addr_type & IPV6_ADDR_MULTICAST || skb->pkt_type != PACKET_HOST) अणु
		अगर (type != ICMPV6_PKT_TOOBIG &&
		    !(type == ICMPV6_PARAMPROB &&
		      code == ICMPV6_UNK_OPTION &&
		      (opt_unrec(skb, info))))
			वापस;

		saddr = शून्य;
	पूर्ण

	addr_type = ipv6_addr_type(&hdr->saddr);

	/*
	 *	Source addr check
	 */

	अगर (__ipv6_addr_needs_scope_id(addr_type)) अणु
		iअगर = icmp6_iअगर(skb);
	पूर्ण अन्यथा अणु
		/*
		 * The source device is used क्रम looking up which routing table
		 * to use क्रम sending an ICMP error.
		 */
		iअगर = l3mdev_master_अगरindex(skb->dev);
	पूर्ण

	/*
	 *	Must not send error अगर the source करोes not uniquely
	 *	identअगरy a single node (RFC2463 Section 2.4).
	 *	We check unspecअगरied / multicast addresses here,
	 *	and anycast addresses will be checked later.
	 */
	अगर ((addr_type == IPV6_ADDR_ANY) || (addr_type & IPV6_ADDR_MULTICAST)) अणु
		net_dbg_ratelimited("icmp6_send: addr_any/mcast source [%pI6c > %pI6c]\n",
				    &hdr->saddr, &hdr->daddr);
		वापस;
	पूर्ण

	/*
	 *	Never answer to a ICMP packet.
	 */
	अगर (is_ineligible(skb)) अणु
		net_dbg_ratelimited("icmp6_send: no reply to icmp error [%pI6c > %pI6c]\n",
				    &hdr->saddr, &hdr->daddr);
		वापस;
	पूर्ण

	/* Needed by both icmp_global_allow and icmpv6_xmit_lock */
	local_bh_disable();

	/* Check global sysctl_icmp_msgs_per_sec ratelimit */
	अगर (!(skb->dev->flags & IFF_LOOPBACK) && !icmpv6_global_allow(net, type))
		जाओ out_bh_enable;

	mip6_addr_swap(skb, parm);

	sk = icmpv6_xmit_lock(net);
	अगर (!sk)
		जाओ out_bh_enable;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_proto = IPPROTO_ICMPV6;
	fl6.daddr = hdr->saddr;
	अगर (क्रमce_saddr)
		saddr = क्रमce_saddr;
	अगर (saddr) अणु
		fl6.saddr = *saddr;
	पूर्ण अन्यथा अगर (!icmpv6_rt_has_prefsrc(sk, type, &fl6)) अणु
		/* select a more meaningful saddr from input अगर */
		काष्ठा net_device *in_netdev;

		in_netdev = dev_get_by_index(net, parm->iअगर);
		अगर (in_netdev) अणु
			ipv6_dev_get_saddr(net, in_netdev, &fl6.daddr,
					   inet6_sk(sk)->srcprefs,
					   &fl6.saddr);
			dev_put(in_netdev);
		पूर्ण
	पूर्ण
	fl6.flowi6_mark = mark;
	fl6.flowi6_oअगर = iअगर;
	fl6.fl6_icmp_type = type;
	fl6.fl6_icmp_code = code;
	fl6.flowi6_uid = sock_net_uid(net, शून्य);
	fl6.mp_hash = rt6_multipath_hash(net, &fl6, skb, शून्य);
	security_skb_classअगरy_flow(skb, flowi6_to_flowi_common(&fl6));

	np = inet6_sk(sk);

	अगर (!icmpv6_xrlim_allow(sk, type, &fl6))
		जाओ out;

	पंचांगp_hdr.icmp6_type = type;
	पंचांगp_hdr.icmp6_code = code;
	पंचांगp_hdr.icmp6_cksum = 0;
	पंचांगp_hdr.icmp6_poपूर्णांकer = htonl(info);

	अगर (!fl6.flowi6_oअगर && ipv6_addr_is_multicast(&fl6.daddr))
		fl6.flowi6_oअगर = np->mcast_oअगर;
	अन्यथा अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->ucast_oअगर;

	ipcm6_init_sk(&ipc6, np);
	ipc6.sockc.mark = mark;
	fl6.flowlabel = ip6_make_flowinfo(ipc6.tclass, fl6.flowlabel);

	dst = icmpv6_route_lookup(net, skb, sk, &fl6);
	अगर (IS_ERR(dst))
		जाओ out;

	ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);

	msg.skb = skb;
	msg.offset = skb_network_offset(skb);
	msg.type = type;

	len = skb->len - msg.offset;
	len = min_t(अचिन्हित पूर्णांक, len, IPV6_MIN_MTU - माप(काष्ठा ipv6hdr) - माप(काष्ठा icmp6hdr));
	अगर (len < 0) अणु
		net_dbg_ratelimited("icmp: len problem [%pI6c > %pI6c]\n",
				    &hdr->saddr, &hdr->daddr);
		जाओ out_dst_release;
	पूर्ण

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(skb->dev);

	अगर (ip6_append_data(sk, icmpv6_getfrag, &msg,
			    len + माप(काष्ठा icmp6hdr),
			    माप(काष्ठा icmp6hdr),
			    &ipc6, &fl6, (काष्ठा rt6_info *)dst,
			    MSG_DONTWAIT)) अणु
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTERRORS);
		ip6_flush_pending_frames(sk);
	पूर्ण अन्यथा अणु
		icmpv6_push_pending_frames(sk, &fl6, &पंचांगp_hdr,
					   len + माप(काष्ठा icmp6hdr));
	पूर्ण
	rcu_पढ़ो_unlock();
out_dst_release:
	dst_release(dst);
out:
	icmpv6_xmit_unlock(sk);
out_bh_enable:
	local_bh_enable();
पूर्ण
EXPORT_SYMBOL(icmp6_send);

/* Slightly more convenient version of icmp6_send.
 */
व्योम icmpv6_param_prob(काष्ठा sk_buff *skb, u8 code, पूर्णांक pos)
अणु
	icmp6_send(skb, ICMPV6_PARAMPROB, code, pos, शून्य, IP6CB(skb));
	kमुक्त_skb(skb);
पूर्ण

/* Generate icmpv6 with type/code ICMPV6_DEST_UNREACH/ICMPV6_ADDR_UNREACH
 * अगर sufficient data bytes are available
 * @nhs is the size of the tunnel header(s) :
 *  Either an IPv4 header क्रम SIT encap
 *         an IPv4 header + GRE header क्रम GRE encap
 */
पूर्णांक ip6_err_gen_icmpv6_unreach(काष्ठा sk_buff *skb, पूर्णांक nhs, पूर्णांक type,
			       अचिन्हित पूर्णांक data_len)
अणु
	काष्ठा in6_addr temp_saddr;
	काष्ठा rt6_info *rt;
	काष्ठा sk_buff *skb2;
	u32 info = 0;

	अगर (!pskb_may_pull(skb, nhs + माप(काष्ठा ipv6hdr) + 8))
		वापस 1;

	/* RFC 4884 (partial) support क्रम ICMP extensions */
	अगर (data_len < 128 || (data_len & 7) || skb->len < data_len)
		data_len = 0;

	skb2 = data_len ? skb_copy(skb, GFP_ATOMIC) : skb_clone(skb, GFP_ATOMIC);

	अगर (!skb2)
		वापस 1;

	skb_dst_drop(skb2);
	skb_pull(skb2, nhs);
	skb_reset_network_header(skb2);

	rt = rt6_lookup(dev_net(skb->dev), &ipv6_hdr(skb2)->saddr, शून्य, 0,
			skb, 0);

	अगर (rt && rt->dst.dev)
		skb2->dev = rt->dst.dev;

	ipv6_addr_set_v4mapped(ip_hdr(skb)->saddr, &temp_saddr);

	अगर (data_len) अणु
		/* RFC 4884 (partial) support :
		 * insert 0 padding at the end, beक्रमe the extensions
		 */
		__skb_push(skb2, nhs);
		skb_reset_network_header(skb2);
		स_हटाओ(skb2->data, skb2->data + nhs, data_len - nhs);
		स_रखो(skb2->data + data_len - nhs, 0, nhs);
		/* RFC 4884 4.5 : Length is measured in 64-bit words,
		 * and stored in reserved[0]
		 */
		info = (data_len/8) << 24;
	पूर्ण
	अगर (type == ICMP_TIME_EXCEEDED)
		icmp6_send(skb2, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT,
			   info, &temp_saddr, IP6CB(skb2));
	अन्यथा
		icmp6_send(skb2, ICMPV6_DEST_UNREACH, ICMPV6_ADDR_UNREACH,
			   info, &temp_saddr, IP6CB(skb2));
	अगर (rt)
		ip6_rt_put(rt);

	kमुक्त_skb(skb2);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip6_err_gen_icmpv6_unreach);

अटल व्योम icmpv6_echo_reply(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा sock *sk;
	काष्ठा inet6_dev *idev;
	काष्ठा ipv6_pinfo *np;
	स्थिर काष्ठा in6_addr *saddr = शून्य;
	काष्ठा icmp6hdr *icmph = icmp6_hdr(skb);
	काष्ठा icmp6hdr पंचांगp_hdr;
	काष्ठा flowi6 fl6;
	काष्ठा icmpv6_msg msg;
	काष्ठा dst_entry *dst;
	काष्ठा ipcm6_cookie ipc6;
	u32 mark = IP6_REPLY_MARK(net, skb->mark);
	bool acast;

	अगर (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) &&
	    net->ipv6.sysctl.icmpv6_echo_ignore_multicast)
		वापस;

	saddr = &ipv6_hdr(skb)->daddr;

	acast = ipv6_anycast_destination(skb_dst(skb), saddr);
	अगर (acast && net->ipv6.sysctl.icmpv6_echo_ignore_anycast)
		वापस;

	अगर (!ipv6_unicast_destination(skb) &&
	    !(net->ipv6.sysctl.anycast_src_echo_reply && acast))
		saddr = शून्य;

	स_नकल(&पंचांगp_hdr, icmph, माप(पंचांगp_hdr));
	पंचांगp_hdr.icmp6_type = ICMPV6_ECHO_REPLY;

	स_रखो(&fl6, 0, माप(fl6));
	अगर (net->ipv6.sysctl.flowlabel_reflect & FLOWLABEL_REFLECT_ICMPV6_ECHO_REPLIES)
		fl6.flowlabel = ip6_flowlabel(ipv6_hdr(skb));

	fl6.flowi6_proto = IPPROTO_ICMPV6;
	fl6.daddr = ipv6_hdr(skb)->saddr;
	अगर (saddr)
		fl6.saddr = *saddr;
	fl6.flowi6_oअगर = icmp6_iअगर(skb);
	fl6.fl6_icmp_type = ICMPV6_ECHO_REPLY;
	fl6.flowi6_mark = mark;
	fl6.flowi6_uid = sock_net_uid(net, शून्य);
	security_skb_classअगरy_flow(skb, flowi6_to_flowi_common(&fl6));

	local_bh_disable();
	sk = icmpv6_xmit_lock(net);
	अगर (!sk)
		जाओ out_bh_enable;
	np = inet6_sk(sk);

	अगर (!fl6.flowi6_oअगर && ipv6_addr_is_multicast(&fl6.daddr))
		fl6.flowi6_oअगर = np->mcast_oअगर;
	अन्यथा अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->ucast_oअगर;

	अगर (ip6_dst_lookup(net, sk, &dst, &fl6))
		जाओ out;
	dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), sk, 0);
	अगर (IS_ERR(dst))
		जाओ out;

	/* Check the ratelimit */
	अगर ((!(skb->dev->flags & IFF_LOOPBACK) && !icmpv6_global_allow(net, ICMPV6_ECHO_REPLY)) ||
	    !icmpv6_xrlim_allow(sk, ICMPV6_ECHO_REPLY, &fl6))
		जाओ out_dst_release;

	idev = __in6_dev_get(skb->dev);

	msg.skb = skb;
	msg.offset = 0;
	msg.type = ICMPV6_ECHO_REPLY;

	ipcm6_init_sk(&ipc6, np);
	ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);
	ipc6.tclass = ipv6_get_dsfield(ipv6_hdr(skb));
	ipc6.sockc.mark = mark;

	अगर (ip6_append_data(sk, icmpv6_getfrag, &msg,
			    skb->len + माप(काष्ठा icmp6hdr),
			    माप(काष्ठा icmp6hdr), &ipc6, &fl6,
			    (काष्ठा rt6_info *)dst, MSG_DONTWAIT)) अणु
		__ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTERRORS);
		ip6_flush_pending_frames(sk);
	पूर्ण अन्यथा अणु
		icmpv6_push_pending_frames(sk, &fl6, &पंचांगp_hdr,
					   skb->len + माप(काष्ठा icmp6hdr));
	पूर्ण
out_dst_release:
	dst_release(dst);
out:
	icmpv6_xmit_unlock(sk);
out_bh_enable:
	local_bh_enable();
पूर्ण

व्योम icmpv6_notअगरy(काष्ठा sk_buff *skb, u8 type, u8 code, __be32 info)
अणु
	स्थिर काष्ठा inet6_protocol *ipprot;
	पूर्णांक inner_offset;
	__be16 frag_off;
	u8 nexthdr;
	काष्ठा net *net = dev_net(skb->dev);

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ out;

	nexthdr = ((काष्ठा ipv6hdr *)skb->data)->nexthdr;
	अगर (ipv6_ext_hdr(nexthdr)) अणु
		/* now skip over extension headers */
		inner_offset = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr),
						&nexthdr, &frag_off);
		अगर (inner_offset < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		inner_offset = माप(काष्ठा ipv6hdr);
	पूर्ण

	/* Checkin header including 8 bytes of inner protocol header. */
	अगर (!pskb_may_pull(skb, inner_offset+8))
		जाओ out;

	/* BUGGG_FUTURE: we should try to parse exthdrs in this packet.
	   Without this we will not able f.e. to make source routed
	   pmtu discovery.
	   Corresponding argument (opt) to notअगरiers is alपढ़ोy added.
	   --ANK (980726)
	 */

	ipprot = rcu_dereference(inet6_protos[nexthdr]);
	अगर (ipprot && ipprot->err_handler)
		ipprot->err_handler(skb, शून्य, type, code, inner_offset, info);

	raw6_icmp_error(skb, nexthdr, type, code, inner_offset, info);
	वापस;

out:
	__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev), ICMP6_MIB_INERRORS);
पूर्ण

/*
 *	Handle icmp messages
 */

अटल पूर्णांक icmpv6_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा net_device *dev = icmp6_dev(skb);
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);
	स्थिर काष्ठा in6_addr *saddr, *daddr;
	काष्ठा icmp6hdr *hdr;
	u8 type;
	bool success = false;

	अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
		काष्ठा sec_path *sp = skb_sec_path(skb);
		पूर्णांक nh;

		अगर (!(sp && sp->xvec[sp->len - 1]->props.flags &
				 XFRM_STATE_ICMP))
			जाओ drop_no_count;

		अगर (!pskb_may_pull(skb, माप(*hdr) + माप(काष्ठा ipv6hdr)))
			जाओ drop_no_count;

		nh = skb_network_offset(skb);
		skb_set_network_header(skb, माप(*hdr));

		अगर (!xfrm6_policy_check_reverse(शून्य, XFRM_POLICY_IN, skb))
			जाओ drop_no_count;

		skb_set_network_header(skb, nh);
	पूर्ण

	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_INMSGS);

	saddr = &ipv6_hdr(skb)->saddr;
	daddr = &ipv6_hdr(skb)->daddr;

	अगर (skb_checksum_validate(skb, IPPROTO_ICMPV6, ip6_compute_pseuकरो)) अणु
		net_dbg_ratelimited("ICMPv6 checksum failed [%pI6c > %pI6c]\n",
				    saddr, daddr);
		जाओ csum_error;
	पूर्ण

	अगर (!pskb_pull(skb, माप(*hdr)))
		जाओ discard_it;

	hdr = icmp6_hdr(skb);

	type = hdr->icmp6_type;

	ICMP6MSGIN_INC_STATS(dev_net(dev), idev, type);

	चयन (type) अणु
	हाल ICMPV6_ECHO_REQUEST:
		अगर (!net->ipv6.sysctl.icmpv6_echo_ignore_all)
			icmpv6_echo_reply(skb);
		अवरोध;

	हाल ICMPV6_ECHO_REPLY:
		success = ping_rcv(skb);
		अवरोध;

	हाल ICMPV6_EXT_ECHO_REPLY:
		success = ping_rcv(skb);
		अवरोध;

	हाल ICMPV6_PKT_TOOBIG:
		/* BUGGG_FUTURE: अगर packet contains rthdr, we cannot update
		   standard destination cache. Seems, only "advanced"
		   destination cache will allow to solve this problem
		   --ANK (980726)
		 */
		अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
			जाओ discard_it;
		hdr = icmp6_hdr(skb);

		/* to notअगरy */
		fallthrough;
	हाल ICMPV6_DEST_UNREACH:
	हाल ICMPV6_TIME_EXCEED:
	हाल ICMPV6_PARAMPROB:
		icmpv6_notअगरy(skb, type, hdr->icmp6_code, hdr->icmp6_mtu);
		अवरोध;

	हाल NDISC_ROUTER_SOLICITATION:
	हाल NDISC_ROUTER_ADVERTISEMENT:
	हाल NDISC_NEIGHBOUR_SOLICITATION:
	हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
	हाल NDISC_REसूचीECT:
		ndisc_rcv(skb);
		अवरोध;

	हाल ICMPV6_MGM_QUERY:
		igmp6_event_query(skb);
		वापस 0;

	हाल ICMPV6_MGM_REPORT:
		igmp6_event_report(skb);
		वापस 0;

	हाल ICMPV6_MGM_REDUCTION:
	हाल ICMPV6_NI_QUERY:
	हाल ICMPV6_NI_REPLY:
	हाल ICMPV6_MLD2_REPORT:
	हाल ICMPV6_DHAAD_REQUEST:
	हाल ICMPV6_DHAAD_REPLY:
	हाल ICMPV6_MOBILE_PREFIX_SOL:
	हाल ICMPV6_MOBILE_PREFIX_ADV:
		अवरोध;

	शेष:
		/* inक्रमmational */
		अगर (type & ICMPV6_INFOMSG_MASK)
			अवरोध;

		net_dbg_ratelimited("icmpv6: msg of unknown type [%pI6c > %pI6c]\n",
				    saddr, daddr);

		/*
		 * error of unknown type.
		 * must pass to upper level
		 */

		icmpv6_notअगरy(skb, type, hdr->icmp6_code, hdr->icmp6_mtu);
	पूर्ण

	/* until the v6 path can be better sorted assume failure and
	 * preserve the status quo behaviour क्रम the rest of the paths to here
	 */
	अगर (success)
		consume_skb(skb);
	अन्यथा
		kमुक्त_skb(skb);

	वापस 0;

csum_error:
	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_CSUMERRORS);
discard_it:
	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_INERRORS);
drop_no_count:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

व्योम icmpv6_flow_init(काष्ठा sock *sk, काष्ठा flowi6 *fl6,
		      u8 type,
		      स्थिर काष्ठा in6_addr *saddr,
		      स्थिर काष्ठा in6_addr *daddr,
		      पूर्णांक oअगर)
अणु
	स_रखो(fl6, 0, माप(*fl6));
	fl6->saddr = *saddr;
	fl6->daddr = *daddr;
	fl6->flowi6_proto	= IPPROTO_ICMPV6;
	fl6->fl6_icmp_type	= type;
	fl6->fl6_icmp_code	= 0;
	fl6->flowi6_oअगर		= oअगर;
	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(fl6));
पूर्ण

अटल व्योम __net_निकास icmpv6_sk_निकास(काष्ठा net *net)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		inet_ctl_sock_destroy(*per_cpu_ptr(net->ipv6.icmp_sk, i));
	मुक्त_percpu(net->ipv6.icmp_sk);
पूर्ण

अटल पूर्णांक __net_init icmpv6_sk_init(काष्ठा net *net)
अणु
	काष्ठा sock *sk;
	पूर्णांक err, i;

	net->ipv6.icmp_sk = alloc_percpu(काष्ठा sock *);
	अगर (!net->ipv6.icmp_sk)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(i) अणु
		err = inet_ctl_sock_create(&sk, PF_INET6,
					   SOCK_RAW, IPPROTO_ICMPV6, net);
		अगर (err < 0) अणु
			pr_err("Failed to initialize the ICMP6 control socket (err %d)\n",
			       err);
			जाओ fail;
		पूर्ण

		*per_cpu_ptr(net->ipv6.icmp_sk, i) = sk;

		/* Enough space क्रम 2 64K ICMP packets, including
		 * sk_buff काष्ठा overhead.
		 */
		sk->sk_sndbuf = 2 * SKB_TRUESIZE(64 * 1024);
	पूर्ण
	वापस 0;

 fail:
	icmpv6_sk_निकास(net);
	वापस err;
पूर्ण

अटल काष्ठा pernet_operations icmpv6_sk_ops = अणु
	.init = icmpv6_sk_init,
	.निकास = icmpv6_sk_निकास,
पूर्ण;

पूर्णांक __init icmpv6_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&icmpv6_sk_ops);
	अगर (err < 0)
		वापस err;

	err = -EAGAIN;
	अगर (inet6_add_protocol(&icmpv6_protocol, IPPROTO_ICMPV6) < 0)
		जाओ fail;

	err = inet6_रेजिस्टर_icmp_sender(icmp6_send);
	अगर (err)
		जाओ sender_reg_err;
	वापस 0;

sender_reg_err:
	inet6_del_protocol(&icmpv6_protocol, IPPROTO_ICMPV6);
fail:
	pr_err("Failed to register ICMP6 protocol\n");
	unरेजिस्टर_pernet_subsys(&icmpv6_sk_ops);
	वापस err;
पूर्ण

व्योम icmpv6_cleanup(व्योम)
अणु
	inet6_unरेजिस्टर_icmp_sender(icmp6_send);
	unरेजिस्टर_pernet_subsys(&icmpv6_sk_ops);
	inet6_del_protocol(&icmpv6_protocol, IPPROTO_ICMPV6);
पूर्ण


अटल स्थिर काष्ठा icmp6_err अणु
	पूर्णांक err;
	पूर्णांक fatal;
पूर्ण tab_unreach[] = अणु
	अणु	/* NOROUTE */
		.err	= ENETUNREACH,
		.fatal	= 0,
	पूर्ण,
	अणु	/* ADM_PROHIBITED */
		.err	= EACCES,
		.fatal	= 1,
	पूर्ण,
	अणु	/* Was NOT_NEIGHBOUR, now reserved */
		.err	= EHOSTUNREACH,
		.fatal	= 0,
	पूर्ण,
	अणु	/* ADDR_UNREACH	*/
		.err	= EHOSTUNREACH,
		.fatal	= 0,
	पूर्ण,
	अणु	/* PORT_UNREACH	*/
		.err	= ECONNREFUSED,
		.fatal	= 1,
	पूर्ण,
	अणु	/* POLICY_FAIL */
		.err	= EACCES,
		.fatal	= 1,
	पूर्ण,
	अणु	/* REJECT_ROUTE	*/
		.err	= EACCES,
		.fatal	= 1,
	पूर्ण,
पूर्ण;

पूर्णांक icmpv6_err_convert(u8 type, u8 code, पूर्णांक *err)
अणु
	पूर्णांक fatal = 0;

	*err = EPROTO;

	चयन (type) अणु
	हाल ICMPV6_DEST_UNREACH:
		fatal = 1;
		अगर (code < ARRAY_SIZE(tab_unreach)) अणु
			*err  = tab_unreach[code].err;
			fatal = tab_unreach[code].fatal;
		पूर्ण
		अवरोध;

	हाल ICMPV6_PKT_TOOBIG:
		*err = EMSGSIZE;
		अवरोध;

	हाल ICMPV6_PARAMPROB:
		*err = EPROTO;
		fatal = 1;
		अवरोध;

	हाल ICMPV6_TIME_EXCEED:
		*err = EHOSTUNREACH;
		अवरोध;
	पूर्ण

	वापस fatal;
पूर्ण
EXPORT_SYMBOL(icmpv6_err_convert);

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table ipv6_icmp_table_ढाँचा[] = अणु
	अणु
		.procname	= "ratelimit",
		.data		= &init_net.ipv6.sysctl.icmpv6_समय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "echo_ignore_all",
		.data		= &init_net.ipv6.sysctl.icmpv6_echo_ignore_all,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler = proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "echo_ignore_multicast",
		.data		= &init_net.ipv6.sysctl.icmpv6_echo_ignore_multicast,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler = proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "echo_ignore_anycast",
		.data		= &init_net.ipv6.sysctl.icmpv6_echo_ignore_anycast,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler = proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ratemask",
		.data		= &init_net.ipv6.sysctl.icmpv6_ratemask_ptr,
		.maxlen		= ICMPV6_MSG_MAX + 1,
		.mode		= 0644,
		.proc_handler = proc_करो_large_biपंचांगap,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

काष्ठा ctl_table * __net_init ipv6_icmp_sysctl_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = kmemdup(ipv6_icmp_table_ढाँचा,
			माप(ipv6_icmp_table_ढाँचा),
			GFP_KERNEL);

	अगर (table) अणु
		table[0].data = &net->ipv6.sysctl.icmpv6_समय;
		table[1].data = &net->ipv6.sysctl.icmpv6_echo_ignore_all;
		table[2].data = &net->ipv6.sysctl.icmpv6_echo_ignore_multicast;
		table[3].data = &net->ipv6.sysctl.icmpv6_echo_ignore_anycast;
		table[4].data = &net->ipv6.sysctl.icmpv6_ratemask_ptr;
	पूर्ण
	वापस table;
पूर्ण
#पूर्ण_अगर
