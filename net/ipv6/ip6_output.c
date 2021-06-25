<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 output functions
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on linux/net/ipv4/ip_output.c
 *
 *	Changes:
 *	A.N.Kuznetsov	:	airthmetics in fragmentation.
 *				extension headers are implemented.
 *				route changes now work.
 *				ip6_क्रमward करोes not confuse snअगरfers.
 *				etc.
 *
 *      H. von Bअक्रम    :       Added missing #समावेश <linux/माला.स>
 *	Imran Patel	:	frag id should be in NBO
 *      Kazunori MIYAZAWA @USAGI
 *			:       add ip6_append_data and related functions
 *				क्रम datagram xmit
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/route.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/bpf-cgroup.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/protocol.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/rawv6.h>
#समावेश <net/icmp.h>
#समावेश <net/xfrm.h>
#समावेश <net/checksum.h>
#समावेश <linux/mroute6.h>
#समावेश <net/l3mdev.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/ip_tunnels.h>

अटल पूर्णांक ip6_finish_output2(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net_device *dev = dst->dev;
	स्थिर काष्ठा in6_addr *nexthop;
	काष्ठा neighbour *neigh;
	पूर्णांक ret;

	अगर (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr)) अणु
		काष्ठा inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

		अगर (!(dev->flags & IFF_LOOPBACK) && sk_mc_loop(sk) &&
		    ((mroute6_is_socket(net, skb) &&
		     !(IP6CB(skb)->flags & IP6SKB_FORWARDED)) ||
		     ipv6_chk_mcast_addr(dev, &ipv6_hdr(skb)->daddr,
					 &ipv6_hdr(skb)->saddr))) अणु
			काष्ठा sk_buff *newskb = skb_clone(skb, GFP_ATOMIC);

			/* Do not check क्रम IFF_ALLMULTI; multicast routing
			   is not supported in any हाल.
			 */
			अगर (newskb)
				NF_HOOK(NFPROTO_IPV6, NF_INET_POST_ROUTING,
					net, sk, newskb, शून्य, newskb->dev,
					dev_loopback_xmit);

			अगर (ipv6_hdr(skb)->hop_limit == 0) अणु
				IP6_INC_STATS(net, idev,
					      IPSTATS_MIB_OUTDISCARDS);
				kमुक्त_skb(skb);
				वापस 0;
			पूर्ण
		पूर्ण

		IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_OUTMCAST, skb->len);

		अगर (IPV6_ADDR_MC_SCOPE(&ipv6_hdr(skb)->daddr) <=
		    IPV6_ADDR_SCOPE_NODELOCAL &&
		    !(dev->flags & IFF_LOOPBACK)) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (lwtunnel_xmit_redirect(dst->lwtstate)) अणु
		पूर्णांक res = lwtunnel_xmit(skb);

		अगर (res < 0 || res == LWTUNNEL_XMIT_DONE)
			वापस res;
	पूर्ण

	rcu_पढ़ो_lock_bh();
	nexthop = rt6_nexthop((काष्ठा rt6_info *)dst, &ipv6_hdr(skb)->daddr);
	neigh = __ipv6_neigh_lookup_noref(dst->dev, nexthop);
	अगर (unlikely(!neigh))
		neigh = __neigh_create(&nd_tbl, nexthop, dst->dev, false);
	अगर (!IS_ERR(neigh)) अणु
		sock_confirm_neigh(skb, neigh);
		ret = neigh_output(neigh, skb, false);
		rcu_पढ़ो_unlock_bh();
		वापस ret;
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTNOROUTES);
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
ip6_finish_output_gso_slowpath_drop(काष्ठा net *net, काष्ठा sock *sk,
				    काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा sk_buff *segs, *nskb;
	netdev_features_t features;
	पूर्णांक ret = 0;

	/* Please see corresponding comment in ip_finish_output_gso
	 * describing the हालs where GSO segment length exceeds the
	 * egress MTU.
	 */
	features = netअगर_skb_features(skb);
	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	consume_skb(skb);

	skb_list_walk_safe(segs, segs, nskb) अणु
		पूर्णांक err;

		skb_mark_not_on_list(segs);
		err = ip6_fragment(net, sk, segs, ip6_finish_output2);
		अगर (err && ret == 0)
			ret = err;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ip6_finish_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक mtu;

#अगर defined(CONFIG_NETFILTER) && defined(CONFIG_XFRM)
	/* Policy lookup after SNAT yielded a new policy */
	अगर (skb_dst(skb)->xfrm) अणु
		IPCB(skb)->flags |= IPSKB_REROUTED;
		वापस dst_output(net, sk, skb);
	पूर्ण
#पूर्ण_अगर

	mtu = ip6_skb_dst_mtu(skb);
	अगर (skb_is_gso(skb) && !skb_gso_validate_network_len(skb, mtu))
		वापस ip6_finish_output_gso_slowpath_drop(net, sk, skb, mtu);

	अगर ((skb->len > mtu && !skb_is_gso(skb)) ||
	    dst_allfrag(skb_dst(skb)) ||
	    (IP6CB(skb)->frag_max_size && skb->len > IP6CB(skb)->frag_max_size))
		वापस ip6_fragment(net, sk, skb, ip6_finish_output2);
	अन्यथा
		वापस ip6_finish_output2(net, sk, skb);
पूर्ण

अटल पूर्णांक ip6_finish_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	ret = BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb);
	चयन (ret) अणु
	हाल NET_XMIT_SUCCESS:
		वापस __ip6_finish_output(net, sk, skb);
	हाल NET_XMIT_CN:
		वापस __ip6_finish_output(net, sk, skb) ? : ret;
	शेष:
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण
पूर्ण

पूर्णांक ip6_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb_dst(skb)->dev, *indev = skb->dev;
	काष्ठा inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	अगर (unlikely(idev->cnf.disable_ipv6)) अणु
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCARDS);
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	वापस NF_HOOK_COND(NFPROTO_IPV6, NF_INET_POST_ROUTING,
			    net, sk, skb, indev, dev,
			    ip6_finish_output,
			    !(IP6CB(skb)->flags & IP6SKB_REROUTED));
पूर्ण
EXPORT_SYMBOL(ip6_output);

bool ip6_स्वतःflowlabel(काष्ठा net *net, स्थिर काष्ठा ipv6_pinfo *np)
अणु
	अगर (!np->स्वतःflowlabel_set)
		वापस ip6_शेष_np_स्वतःlabel(net);
	अन्यथा
		वापस np->स्वतःflowlabel;
पूर्ण

/*
 * xmit an sk_buff (used by TCP, SCTP and DCCP)
 * Note : socket lock is not held क्रम SYNACK packets, but might be modअगरied
 * by calls to skb_set_owner_w() and ipv6_local_error(),
 * which are using proper atomic operations or spinlocks.
 */
पूर्णांक ip6_xmit(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi6 *fl6,
	     __u32 mark, काष्ठा ipv6_txoptions *opt, पूर्णांक tclass, u32 priority)
अणु
	काष्ठा net *net = sock_net(sk);
	स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा in6_addr *first_hop = &fl6->daddr;
	काष्ठा dst_entry *dst = skb_dst(skb);
	अचिन्हित पूर्णांक head_room;
	काष्ठा ipv6hdr *hdr;
	u8  proto = fl6->flowi6_proto;
	पूर्णांक seg_len = skb->len;
	पूर्णांक hlimit = -1;
	u32 mtu;

	head_room = माप(काष्ठा ipv6hdr) + LL_RESERVED_SPACE(dst->dev);
	अगर (opt)
		head_room += opt->opt_nflen + opt->opt_flen;

	अगर (unlikely(skb_headroom(skb) < head_room)) अणु
		काष्ठा sk_buff *skb2 = skb_पुनः_स्मृति_headroom(skb, head_room);
		अगर (!skb2) अणु
			IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
				      IPSTATS_MIB_OUTDISCARDS);
			kमुक्त_skb(skb);
			वापस -ENOBUFS;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(skb2, skb->sk);
		consume_skb(skb);
		skb = skb2;
	पूर्ण

	अगर (opt) अणु
		seg_len += opt->opt_nflen + opt->opt_flen;

		अगर (opt->opt_flen)
			ipv6_push_frag_opts(skb, opt, &proto);

		अगर (opt->opt_nflen)
			ipv6_push_nfrag_opts(skb, opt, &proto, &first_hop,
					     &fl6->saddr);
	पूर्ण

	skb_push(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	/*
	 *	Fill in the IPv6 header
	 */
	अगर (np)
		hlimit = np->hop_limit;
	अगर (hlimit < 0)
		hlimit = ip6_dst_hoplimit(dst);

	ip6_flow_hdr(hdr, tclass, ip6_make_flowlabel(net, skb, fl6->flowlabel,
				ip6_स्वतःflowlabel(net, np), fl6));

	hdr->payload_len = htons(seg_len);
	hdr->nexthdr = proto;
	hdr->hop_limit = hlimit;

	hdr->saddr = fl6->saddr;
	hdr->daddr = *first_hop;

	skb->protocol = htons(ETH_P_IPV6);
	skb->priority = priority;
	skb->mark = mark;

	mtu = dst_mtu(dst);
	अगर ((skb->len <= mtu) || skb->ignore_df || skb_is_gso(skb)) अणु
		IP6_UPD_PO_STATS(net, ip6_dst_idev(skb_dst(skb)),
			      IPSTATS_MIB_OUT, skb->len);

		/* अगर egress device is enslaved to an L3 master device pass the
		 * skb to its handler क्रम processing
		 */
		skb = l3mdev_ip6_out((काष्ठा sock *)sk, skb);
		अगर (unlikely(!skb))
			वापस 0;

		/* hooks should never assume socket lock is held.
		 * we promote our socket to non स्थिर
		 */
		वापस NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
			       net, (काष्ठा sock *)sk, skb, शून्य, dst->dev,
			       dst_output);
	पूर्ण

	skb->dev = dst->dev;
	/* ipv6_local_error() करोes not require socket lock,
	 * we promote our socket to non स्थिर
	 */
	ipv6_local_error((काष्ठा sock *)sk, EMSGSIZE, fl6, mtu);

	IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_FRAGFAILS);
	kमुक्त_skb(skb);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL(ip6_xmit);

अटल पूर्णांक ip6_call_ra_chain(काष्ठा sk_buff *skb, पूर्णांक sel)
अणु
	काष्ठा ip6_ra_chain *ra;
	काष्ठा sock *last = शून्य;

	पढ़ो_lock(&ip6_ra_lock);
	क्रम (ra = ip6_ra_chain; ra; ra = ra->next) अणु
		काष्ठा sock *sk = ra->sk;
		अगर (sk && ra->sel == sel &&
		    (!sk->sk_bound_dev_अगर ||
		     sk->sk_bound_dev_अगर == skb->dev->अगरindex)) अणु
			काष्ठा ipv6_pinfo *np = inet6_sk(sk);

			अगर (np && np->rtalert_isolate &&
			    !net_eq(sock_net(sk), dev_net(skb->dev))) अणु
				जारी;
			पूर्ण
			अगर (last) अणु
				काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (skb2)
					rawv6_rcv(last, skb2);
			पूर्ण
			last = sk;
		पूर्ण
	पूर्ण

	अगर (last) अणु
		rawv6_rcv(last, skb);
		पढ़ो_unlock(&ip6_ra_lock);
		वापस 1;
	पूर्ण
	पढ़ो_unlock(&ip6_ra_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6_क्रमward_proxy_check(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	u8 nexthdr = hdr->nexthdr;
	__be16 frag_off;
	पूर्णांक offset;

	अगर (ipv6_ext_hdr(nexthdr)) अणु
		offset = ipv6_skip_exthdr(skb, माप(*hdr), &nexthdr, &frag_off);
		अगर (offset < 0)
			वापस 0;
	पूर्ण अन्यथा
		offset = माप(काष्ठा ipv6hdr);

	अगर (nexthdr == IPPROTO_ICMPV6) अणु
		काष्ठा icmp6hdr *icmp6;

		अगर (!pskb_may_pull(skb, (skb_network_header(skb) +
					 offset + 1 - skb->data)))
			वापस 0;

		icmp6 = (काष्ठा icmp6hdr *)(skb_network_header(skb) + offset);

		चयन (icmp6->icmp6_type) अणु
		हाल NDISC_ROUTER_SOLICITATION:
		हाल NDISC_ROUTER_ADVERTISEMENT:
		हाल NDISC_NEIGHBOUR_SOLICITATION:
		हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
		हाल NDISC_REसूचीECT:
			/* For reaction involving unicast neighbor discovery
			 * message destined to the proxied address, pass it to
			 * input function.
			 */
			वापस 1;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The proxying router can't क्रमward traffic sent to a link-local
	 * address, so संकेत the sender and discard the packet. This
	 * behavior is clarअगरied by the MIPv6 specअगरication.
	 */
	अगर (ipv6_addr_type(&hdr->daddr) & IPV6_ADDR_LINKLOCAL) अणु
		dst_link_failure(skb);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ip6_क्रमward_finish(काष्ठा net *net, काष्ठा sock *sk,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);

	__IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTFORWDATAGRAMS);
	__IP6_ADD_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTOCTETS, skb->len);

#अगर_घोषित CONFIG_NET_SWITCHDEV
	अगर (skb->offload_l3_fwd_mark) अणु
		consume_skb(skb);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	skb->tstamp = 0;
	वापस dst_output(net, sk, skb);
पूर्ण

अटल bool ip6_pkt_too_big(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	अगर (skb->len <= mtu)
		वापस false;

	/* ipv6 conntrack defrag sets max_frag_size + ignore_df */
	अगर (IP6CB(skb)->frag_max_size && IP6CB(skb)->frag_max_size > mtu)
		वापस true;

	अगर (skb->ignore_df)
		वापस false;

	अगर (skb_is_gso(skb) && skb_gso_validate_network_len(skb, mtu))
		वापस false;

	वापस true;
पूर्ण

पूर्णांक ip6_क्रमward(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get_safely(skb->dev);
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	काष्ठा net *net = dev_net(dst->dev);
	u32 mtu;

	अगर (net->ipv6.devconf_all->क्रमwarding == 0)
		जाओ error;

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ drop;

	अगर (unlikely(skb->sk))
		जाओ drop;

	अगर (skb_warn_अगर_lro(skb))
		जाओ drop;

	अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_FWD, skb)) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCARDS);
		जाओ drop;
	पूर्ण

	skb_क्रमward_csum(skb);

	/*
	 *	We DO NOT make any processing on
	 *	RA packets, pushing them to user level AS IS
	 *	without ane WARRANTY that application will be able
	 *	to पूर्णांकerpret them. The reason is that we
	 *	cannot make anything clever here.
	 *
	 *	We are not end-node, so that अगर packet contains
	 *	AH/ESP, we cannot make anything.
	 *	Defragmentation also would be mistake, RA packets
	 *	cannot be fragmented, because there is no warranty
	 *	that dअगरferent fragments will go aदीर्घ one path. --ANK
	 */
	अगर (unlikely(opt->flags & IP6SKB_ROUTERALERT)) अणु
		अगर (ip6_call_ra_chain(skb, ntohs(opt->ra)))
			वापस 0;
	पूर्ण

	/*
	 *	check and decrement ttl
	 */
	अगर (hdr->hop_limit <= 1) अणु
		icmpv6_send(skb, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT, 0);
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);

		kमुक्त_skb(skb);
		वापस -ETIMEDOUT;
	पूर्ण

	/* XXX: idev->cnf.proxy_ndp? */
	अगर (net->ipv6.devconf_all->proxy_ndp &&
	    pneigh_lookup(&nd_tbl, net, &hdr->daddr, skb->dev, 0)) अणु
		पूर्णांक proxied = ip6_क्रमward_proxy_check(skb);
		अगर (proxied > 0)
			वापस ip6_input(skb);
		अन्यथा अगर (proxied < 0) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCARDS);
			जाओ drop;
		पूर्ण
	पूर्ण

	अगर (!xfrm6_route_क्रमward(skb)) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCARDS);
		जाओ drop;
	पूर्ण
	dst = skb_dst(skb);

	/* IPv6 specs say nothing about it, but it is clear that we cannot
	   send redirects to source routed frames.
	   We करोn't send redirects to frames decapsulated from IPsec.
	 */
	अगर (IP6CB(skb)->iअगर == dst->dev->अगरindex &&
	    opt->srcrt == 0 && !skb_sec_path(skb)) अणु
		काष्ठा in6_addr *target = शून्य;
		काष्ठा inet_peer *peer;
		काष्ठा rt6_info *rt;

		/*
		 *	incoming and outgoing devices are the same
		 *	send a redirect.
		 */

		rt = (काष्ठा rt6_info *) dst;
		अगर (rt->rt6i_flags & RTF_GATEWAY)
			target = &rt->rt6i_gateway;
		अन्यथा
			target = &hdr->daddr;

		peer = inet_getpeer_v6(net->ipv6.peers, &hdr->daddr, 1);

		/* Limit redirects both by destination (here)
		   and by source (inside ndisc_send_redirect)
		 */
		अगर (inet_peer_xrlim_allow(peer, 1*HZ))
			ndisc_send_redirect(skb, target);
		अगर (peer)
			inet_putpeer(peer);
	पूर्ण अन्यथा अणु
		पूर्णांक addrtype = ipv6_addr_type(&hdr->saddr);

		/* This check is security critical. */
		अगर (addrtype == IPV6_ADDR_ANY ||
		    addrtype & (IPV6_ADDR_MULTICAST | IPV6_ADDR_LOOPBACK))
			जाओ error;
		अगर (addrtype & IPV6_ADDR_LINKLOCAL) अणु
			icmpv6_send(skb, ICMPV6_DEST_UNREACH,
				    ICMPV6_NOT_NEIGHBOUR, 0);
			जाओ error;
		पूर्ण
	पूर्ण

	mtu = ip6_dst_mtu_क्रमward(dst);
	अगर (mtu < IPV6_MIN_MTU)
		mtu = IPV6_MIN_MTU;

	अगर (ip6_pkt_too_big(skb, mtu)) अणु
		/* Again, क्रमce OUTPUT device used as source address */
		skb->dev = dst->dev;
		icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INTOOBIGERRORS);
		__IP6_INC_STATS(net, ip6_dst_idev(dst),
				IPSTATS_MIB_FRAGFAILS);
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (skb_cow(skb, dst->dev->hard_header_len)) अणु
		__IP6_INC_STATS(net, ip6_dst_idev(dst),
				IPSTATS_MIB_OUTDISCARDS);
		जाओ drop;
	पूर्ण

	hdr = ipv6_hdr(skb);

	/* Mangling hops number delayed to poपूर्णांक after skb COW */

	hdr->hop_limit--;

	वापस NF_HOOK(NFPROTO_IPV6, NF_INET_FORWARD,
		       net, शून्य, skb, skb->dev, dst->dev,
		       ip6_क्रमward_finish);

error:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल व्योम ip6_copy_metadata(काष्ठा sk_buff *to, काष्ठा sk_buff *from)
अणु
	to->pkt_type = from->pkt_type;
	to->priority = from->priority;
	to->protocol = from->protocol;
	skb_dst_drop(to);
	skb_dst_set(to, dst_clone(skb_dst(from)));
	to->dev = from->dev;
	to->mark = from->mark;

	skb_copy_hash(to, from);

#अगर_घोषित CONFIG_NET_SCHED
	to->tc_index = from->tc_index;
#पूर्ण_अगर
	nf_copy(to, from);
	skb_ext_copy(to, from);
	skb_copy_secmark(to, from);
पूर्ण

पूर्णांक ip6_fraglist_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen, u8 *prevhdr,
		      u8 nexthdr, __be32 frag_id,
		      काष्ठा ip6_fraglist_iter *iter)
अणु
	अचिन्हित पूर्णांक first_len;
	काष्ठा frag_hdr *fh;

	/* BUILD HEADER */
	*prevhdr = NEXTHDR_FRAGMENT;
	iter->पंचांगp_hdr = kmemdup(skb_network_header(skb), hlen, GFP_ATOMIC);
	अगर (!iter->पंचांगp_hdr)
		वापस -ENOMEM;

	iter->frag = skb_shinfo(skb)->frag_list;
	skb_frag_list_init(skb);

	iter->offset = 0;
	iter->hlen = hlen;
	iter->frag_id = frag_id;
	iter->nexthdr = nexthdr;

	__skb_pull(skb, hlen);
	fh = __skb_push(skb, माप(काष्ठा frag_hdr));
	__skb_push(skb, hlen);
	skb_reset_network_header(skb);
	स_नकल(skb_network_header(skb), iter->पंचांगp_hdr, hlen);

	fh->nexthdr = nexthdr;
	fh->reserved = 0;
	fh->frag_off = htons(IP6_MF);
	fh->identअगरication = frag_id;

	first_len = skb_pagelen(skb);
	skb->data_len = first_len - skb_headlen(skb);
	skb->len = first_len;
	ipv6_hdr(skb)->payload_len = htons(first_len - माप(काष्ठा ipv6hdr));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip6_fraglist_init);

व्योम ip6_fraglist_prepare(काष्ठा sk_buff *skb,
			  काष्ठा ip6_fraglist_iter *iter)
अणु
	काष्ठा sk_buff *frag = iter->frag;
	अचिन्हित पूर्णांक hlen = iter->hlen;
	काष्ठा frag_hdr *fh;

	frag->ip_summed = CHECKSUM_NONE;
	skb_reset_transport_header(frag);
	fh = __skb_push(frag, माप(काष्ठा frag_hdr));
	__skb_push(frag, hlen);
	skb_reset_network_header(frag);
	स_नकल(skb_network_header(frag), iter->पंचांगp_hdr, hlen);
	iter->offset += skb->len - hlen - माप(काष्ठा frag_hdr);
	fh->nexthdr = iter->nexthdr;
	fh->reserved = 0;
	fh->frag_off = htons(iter->offset);
	अगर (frag->next)
		fh->frag_off |= htons(IP6_MF);
	fh->identअगरication = iter->frag_id;
	ipv6_hdr(frag)->payload_len = htons(frag->len - माप(काष्ठा ipv6hdr));
	ip6_copy_metadata(frag, skb);
पूर्ण
EXPORT_SYMBOL(ip6_fraglist_prepare);

व्योम ip6_frag_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen, अचिन्हित पूर्णांक mtu,
		   अचिन्हित लघु needed_tailroom, पूर्णांक hdr_room, u8 *prevhdr,
		   u8 nexthdr, __be32 frag_id, काष्ठा ip6_frag_state *state)
अणु
	state->prevhdr = prevhdr;
	state->nexthdr = nexthdr;
	state->frag_id = frag_id;

	state->hlen = hlen;
	state->mtu = mtu;

	state->left = skb->len - hlen;	/* Space per frame */
	state->ptr = hlen;		/* Where to start from */

	state->hroom = hdr_room;
	state->troom = needed_tailroom;

	state->offset = 0;
पूर्ण
EXPORT_SYMBOL(ip6_frag_init);

काष्ठा sk_buff *ip6_frag_next(काष्ठा sk_buff *skb, काष्ठा ip6_frag_state *state)
अणु
	u8 *prevhdr = state->prevhdr, *fragnexthdr_offset;
	काष्ठा sk_buff *frag;
	काष्ठा frag_hdr *fh;
	अचिन्हित पूर्णांक len;

	len = state->left;
	/* IF: it करोesn't fit, use 'mtu' - the data space left */
	अगर (len > state->mtu)
		len = state->mtu;
	/* IF: we are not sending up to and including the packet end
	   then align the next start on an eight byte boundary */
	अगर (len < state->left)
		len &= ~7;

	/* Allocate buffer */
	frag = alloc_skb(len + state->hlen + माप(काष्ठा frag_hdr) +
			 state->hroom + state->troom, GFP_ATOMIC);
	अगर (!frag)
		वापस ERR_PTR(-ENOMEM);

	/*
	 *	Set up data on packet
	 */

	ip6_copy_metadata(frag, skb);
	skb_reserve(frag, state->hroom);
	skb_put(frag, len + state->hlen + माप(काष्ठा frag_hdr));
	skb_reset_network_header(frag);
	fh = (काष्ठा frag_hdr *)(skb_network_header(frag) + state->hlen);
	frag->transport_header = (frag->network_header + state->hlen +
				  माप(काष्ठा frag_hdr));

	/*
	 *	Charge the memory क्रम the fragment to any owner
	 *	it might possess
	 */
	अगर (skb->sk)
		skb_set_owner_w(frag, skb->sk);

	/*
	 *	Copy the packet header पूर्णांकo the new buffer.
	 */
	skb_copy_from_linear_data(skb, skb_network_header(frag), state->hlen);

	fragnexthdr_offset = skb_network_header(frag);
	fragnexthdr_offset += prevhdr - skb_network_header(skb);
	*fragnexthdr_offset = NEXTHDR_FRAGMENT;

	/*
	 *	Build fragment header.
	 */
	fh->nexthdr = state->nexthdr;
	fh->reserved = 0;
	fh->identअगरication = state->frag_id;

	/*
	 *	Copy a block of the IP datagram.
	 */
	BUG_ON(skb_copy_bits(skb, state->ptr, skb_transport_header(frag),
			     len));
	state->left -= len;

	fh->frag_off = htons(state->offset);
	अगर (state->left > 0)
		fh->frag_off |= htons(IP6_MF);
	ipv6_hdr(frag)->payload_len = htons(frag->len - माप(काष्ठा ipv6hdr));

	state->ptr += len;
	state->offset += len;

	वापस frag;
पूर्ण
EXPORT_SYMBOL(ip6_frag_next);

पूर्णांक ip6_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		 पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	काष्ठा sk_buff *frag;
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)skb_dst(skb);
	काष्ठा ipv6_pinfo *np = skb->sk && !dev_recursion_level() ?
				inet6_sk(skb->sk) : शून्य;
	काष्ठा ip6_frag_state state;
	अचिन्हित पूर्णांक mtu, hlen, nexthdr_offset;
	kसमय_प्रकार tstamp = skb->tstamp;
	पूर्णांक hroom, err = 0;
	__be32 frag_id;
	u8 *prevhdr, nexthdr = 0;

	err = ip6_find_1stfragopt(skb, &prevhdr);
	अगर (err < 0)
		जाओ fail;
	hlen = err;
	nexthdr = *prevhdr;
	nexthdr_offset = prevhdr - skb_network_header(skb);

	mtu = ip6_skb_dst_mtu(skb);

	/* We must not fragment अगर the socket is set to क्रमce MTU discovery
	 * or अगर the skb it not generated by a local socket.
	 */
	अगर (unlikely(!skb->ignore_df && skb->len > mtu))
		जाओ fail_toobig;

	अगर (IP6CB(skb)->frag_max_size) अणु
		अगर (IP6CB(skb)->frag_max_size > mtu)
			जाओ fail_toobig;

		/* करोn't send fragments larger than what we received */
		mtu = IP6CB(skb)->frag_max_size;
		अगर (mtu < IPV6_MIN_MTU)
			mtu = IPV6_MIN_MTU;
	पूर्ण

	अगर (np && np->frag_size < mtu) अणु
		अगर (np->frag_size)
			mtu = np->frag_size;
	पूर्ण
	अगर (mtu < hlen + माप(काष्ठा frag_hdr) + 8)
		जाओ fail_toobig;
	mtu -= hlen + माप(काष्ठा frag_hdr);

	frag_id = ipv6_select_ident(net, &ipv6_hdr(skb)->daddr,
				    &ipv6_hdr(skb)->saddr);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (err = skb_checksum_help(skb)))
		जाओ fail;

	prevhdr = skb_network_header(skb) + nexthdr_offset;
	hroom = LL_RESERVED_SPACE(rt->dst.dev);
	अगर (skb_has_frag_list(skb)) अणु
		अचिन्हित पूर्णांक first_len = skb_pagelen(skb);
		काष्ठा ip6_fraglist_iter iter;
		काष्ठा sk_buff *frag2;

		अगर (first_len - hlen > mtu ||
		    ((first_len - hlen) & 7) ||
		    skb_cloned(skb) ||
		    skb_headroom(skb) < (hroom + माप(काष्ठा frag_hdr)))
			जाओ slow_path;

		skb_walk_frags(skb, frag) अणु
			/* Correct geometry. */
			अगर (frag->len > mtu ||
			    ((frag->len & 7) && frag->next) ||
			    skb_headroom(frag) < (hlen + hroom + माप(काष्ठा frag_hdr)))
				जाओ slow_path_clean;

			/* Partially cloned skb? */
			अगर (skb_shared(frag))
				जाओ slow_path_clean;

			BUG_ON(frag->sk);
			अगर (skb->sk) अणु
				frag->sk = skb->sk;
				frag->deकाष्ठाor = sock_wमुक्त;
			पूर्ण
			skb->truesize -= frag->truesize;
		पूर्ण

		err = ip6_fraglist_init(skb, hlen, prevhdr, nexthdr, frag_id,
					&iter);
		अगर (err < 0)
			जाओ fail;

		क्रम (;;) अणु
			/* Prepare header of the next frame,
			 * beक्रमe previous one went करोwn. */
			अगर (iter.frag)
				ip6_fraglist_prepare(skb, &iter);

			skb->tstamp = tstamp;
			err = output(net, sk, skb);
			अगर (!err)
				IP6_INC_STATS(net, ip6_dst_idev(&rt->dst),
					      IPSTATS_MIB_FRAGCREATES);

			अगर (err || !iter.frag)
				अवरोध;

			skb = ip6_fraglist_next(&iter);
		पूर्ण

		kमुक्त(iter.पंचांगp_hdr);

		अगर (err == 0) अणु
			IP6_INC_STATS(net, ip6_dst_idev(&rt->dst),
				      IPSTATS_MIB_FRAGOKS);
			वापस 0;
		पूर्ण

		kमुक्त_skb_list(iter.frag);

		IP6_INC_STATS(net, ip6_dst_idev(&rt->dst),
			      IPSTATS_MIB_FRAGFAILS);
		वापस err;

slow_path_clean:
		skb_walk_frags(skb, frag2) अणु
			अगर (frag2 == frag)
				अवरोध;
			frag2->sk = शून्य;
			frag2->deकाष्ठाor = शून्य;
			skb->truesize += frag2->truesize;
		पूर्ण
	पूर्ण

slow_path:
	/*
	 *	Fragment the datagram.
	 */

	ip6_frag_init(skb, hlen, mtu, rt->dst.dev->needed_tailroom,
		      LL_RESERVED_SPACE(rt->dst.dev), prevhdr, nexthdr, frag_id,
		      &state);

	/*
	 *	Keep copying data until we run out.
	 */

	जबतक (state.left > 0) अणु
		frag = ip6_frag_next(skb, &state);
		अगर (IS_ERR(frag)) अणु
			err = PTR_ERR(frag);
			जाओ fail;
		पूर्ण

		/*
		 *	Put this fragment पूर्णांकo the sending queue.
		 */
		frag->tstamp = tstamp;
		err = output(net, sk, frag);
		अगर (err)
			जाओ fail;

		IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
			      IPSTATS_MIB_FRAGCREATES);
	पूर्ण
	IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
		      IPSTATS_MIB_FRAGOKS);
	consume_skb(skb);
	वापस err;

fail_toobig:
	अगर (skb->sk && dst_allfrag(skb_dst(skb)))
		sk_nocaps_add(skb->sk, NETIF_F_GSO_MASK);

	icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
	err = -EMSGSIZE;

fail:
	IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
		      IPSTATS_MIB_FRAGFAILS);
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ip6_rt_check(स्थिर काष्ठा rt6key *rt_key,
			       स्थिर काष्ठा in6_addr *fl_addr,
			       स्थिर काष्ठा in6_addr *addr_cache)
अणु
	वापस (rt_key->plen != 128 || !ipv6_addr_equal(fl_addr, &rt_key->addr)) &&
		(!addr_cache || !ipv6_addr_equal(fl_addr, addr_cache));
पूर्ण

अटल काष्ठा dst_entry *ip6_sk_dst_check(काष्ठा sock *sk,
					  काष्ठा dst_entry *dst,
					  स्थिर काष्ठा flowi6 *fl6)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा rt6_info *rt;

	अगर (!dst)
		जाओ out;

	अगर (dst->ops->family != AF_INET6) अणु
		dst_release(dst);
		वापस शून्य;
	पूर्ण

	rt = (काष्ठा rt6_info *)dst;
	/* Yes, checking route validity in not connected
	 * हाल is not very simple. Take पूर्णांकo account,
	 * that we करो not support routing by source, TOS,
	 * and MSG_DONTROUTE		--ANK (980726)
	 *
	 * 1. ip6_rt_check(): If route was host route,
	 *    check that cached destination is current.
	 *    If it is network route, we still may
	 *    check its validity using saved poपूर्णांकer
	 *    to the last used address: daddr_cache.
	 *    We करो not want to save whole address now,
	 *    (because मुख्य consumer of this service
	 *    is tcp, which has not this problem),
	 *    so that the last trick works only on connected
	 *    sockets.
	 * 2. oअगर also should be the same.
	 */
	अगर (ip6_rt_check(&rt->rt6i_dst, &fl6->daddr, np->daddr_cache) ||
#अगर_घोषित CONFIG_IPV6_SUBTREES
	    ip6_rt_check(&rt->rt6i_src, &fl6->saddr, np->saddr_cache) ||
#पूर्ण_अगर
	   (!(fl6->flowi6_flags & FLOWI_FLAG_SKIP_NH_OIF) &&
	      (fl6->flowi6_oअगर && fl6->flowi6_oअगर != dst->dev->अगरindex))) अणु
		dst_release(dst);
		dst = शून्य;
	पूर्ण

out:
	वापस dst;
पूर्ण

अटल पूर्णांक ip6_dst_lookup_tail(काष्ठा net *net, स्थिर काष्ठा sock *sk,
			       काष्ठा dst_entry **dst, काष्ठा flowi6 *fl6)
अणु
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	काष्ठा neighbour *n;
	काष्ठा rt6_info *rt;
#पूर्ण_अगर
	पूर्णांक err;
	पूर्णांक flags = 0;

	/* The correct way to handle this would be to करो
	 * ip6_route_get_saddr, and then ip6_route_output; however,
	 * the route-specअगरic preferred source क्रमces the
	 * ip6_route_output call _beक्रमe_ ip6_route_get_saddr.
	 *
	 * In source specअगरic routing (no src=any शेष route),
	 * ip6_route_output will fail given src=any saddr, though, so
	 * that's why we try it again later.
	 */
	अगर (ipv6_addr_any(&fl6->saddr) && (!*dst || !(*dst)->error)) अणु
		काष्ठा fib6_info *from;
		काष्ठा rt6_info *rt;
		bool had_dst = *dst != शून्य;

		अगर (!had_dst)
			*dst = ip6_route_output(net, sk, fl6);
		rt = (*dst)->error ? शून्य : (काष्ठा rt6_info *)*dst;

		rcu_पढ़ो_lock();
		from = rt ? rcu_dereference(rt->from) : शून्य;
		err = ip6_route_get_saddr(net, from, &fl6->daddr,
					  sk ? inet6_sk(sk)->srcprefs : 0,
					  &fl6->saddr);
		rcu_पढ़ो_unlock();

		अगर (err)
			जाओ out_err_release;

		/* If we had an erroneous initial result, pretend it
		 * never existed and let the SA-enabled version take
		 * over.
		 */
		अगर (!had_dst && (*dst)->error) अणु
			dst_release(*dst);
			*dst = शून्य;
		पूर्ण

		अगर (fl6->flowi6_oअगर)
			flags |= RT6_LOOKUP_F_IFACE;
	पूर्ण

	अगर (!*dst)
		*dst = ip6_route_output_flags(net, sk, fl6, flags);

	err = (*dst)->error;
	अगर (err)
		जाओ out_err_release;

#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	/*
	 * Here अगर the dst entry we've looked up
	 * has a neighbour entry that is in the INCOMPLETE
	 * state and the src address from the flow is
	 * marked as OPTIMISTIC, we release the found
	 * dst entry and replace it instead with the
	 * dst entry of the nexthop router
	 */
	rt = (काष्ठा rt6_info *) *dst;
	rcu_पढ़ो_lock_bh();
	n = __ipv6_neigh_lookup_noref(rt->dst.dev,
				      rt6_nexthop(rt, &fl6->daddr));
	err = n && !(n->nud_state & NUD_VALID) ? -EINVAL : 0;
	rcu_पढ़ो_unlock_bh();

	अगर (err) अणु
		काष्ठा inet6_अगरaddr *अगरp;
		काष्ठा flowi6 fl_gw6;
		पूर्णांक redirect;

		अगरp = ipv6_get_अगरaddr(net, &fl6->saddr,
				      (*dst)->dev, 1);

		redirect = (अगरp && अगरp->flags & IFA_F_OPTIMISTIC);
		अगर (अगरp)
			in6_अगरa_put(अगरp);

		अगर (redirect) अणु
			/*
			 * We need to get the dst entry क्रम the
			 * शेष router instead
			 */
			dst_release(*dst);
			स_नकल(&fl_gw6, fl6, माप(काष्ठा flowi6));
			स_रखो(&fl_gw6.daddr, 0, माप(काष्ठा in6_addr));
			*dst = ip6_route_output(net, sk, &fl_gw6);
			err = (*dst)->error;
			अगर (err)
				जाओ out_err_release;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (ipv6_addr_v4mapped(&fl6->saddr) &&
	    !(ipv6_addr_v4mapped(&fl6->daddr) || ipv6_addr_any(&fl6->daddr))) अणु
		err = -EAFNOSUPPORT;
		जाओ out_err_release;
	पूर्ण

	वापस 0;

out_err_release:
	dst_release(*dst);
	*dst = शून्य;

	अगर (err == -ENETUNREACH)
		IP6_INC_STATS(net, शून्य, IPSTATS_MIB_OUTNOROUTES);
	वापस err;
पूर्ण

/**
 *	ip6_dst_lookup - perक्रमm route lookup on flow
 *	@net: Network namespace to perक्रमm lookup in
 *	@sk: socket which provides route info
 *	@dst: poपूर्णांकer to dst_entry * क्रम result
 *	@fl6: flow to lookup
 *
 *	This function perक्रमms a route lookup on the given flow.
 *
 *	It वापसs zero on success, or a standard त्रुटि_सं code on error.
 */
पूर्णांक ip6_dst_lookup(काष्ठा net *net, काष्ठा sock *sk, काष्ठा dst_entry **dst,
		   काष्ठा flowi6 *fl6)
अणु
	*dst = शून्य;
	वापस ip6_dst_lookup_tail(net, sk, dst, fl6);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_dst_lookup);

/**
 *	ip6_dst_lookup_flow - perक्रमm route lookup on flow with ipsec
 *	@net: Network namespace to perक्रमm lookup in
 *	@sk: socket which provides route info
 *	@fl6: flow to lookup
 *	@final_dst: final destination address क्रम ipsec lookup
 *
 *	This function perक्रमms a route lookup on the given flow.
 *
 *	It वापसs a valid dst poपूर्णांकer on success, or a poपूर्णांकer encoded
 *	error code.
 */
काष्ठा dst_entry *ip6_dst_lookup_flow(काष्ठा net *net, स्थिर काष्ठा sock *sk, काष्ठा flowi6 *fl6,
				      स्थिर काष्ठा in6_addr *final_dst)
अणु
	काष्ठा dst_entry *dst = शून्य;
	पूर्णांक err;

	err = ip6_dst_lookup_tail(net, sk, &dst, fl6);
	अगर (err)
		वापस ERR_PTR(err);
	अगर (final_dst)
		fl6->daddr = *final_dst;

	वापस xfrm_lookup_route(net, dst, flowi6_to_flowi(fl6), sk, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_dst_lookup_flow);

/**
 *	ip6_sk_dst_lookup_flow - perक्रमm socket cached route lookup on flow
 *	@sk: socket which provides the dst cache and route info
 *	@fl6: flow to lookup
 *	@final_dst: final destination address क्रम ipsec lookup
 *	@connected: whether @sk is connected or not
 *
 *	This function perक्रमms a route lookup on the given flow with the
 *	possibility of using the cached route in the socket अगर it is valid.
 *	It will take the socket dst lock when operating on the dst cache.
 *	As a result, this function can only be used in process context.
 *
 *	In addition, क्रम a connected socket, cache the dst in the socket
 *	अगर the current cache is not valid.
 *
 *	It वापसs a valid dst poपूर्णांकer on success, or a poपूर्णांकer encoded
 *	error code.
 */
काष्ठा dst_entry *ip6_sk_dst_lookup_flow(काष्ठा sock *sk, काष्ठा flowi6 *fl6,
					 स्थिर काष्ठा in6_addr *final_dst,
					 bool connected)
अणु
	काष्ठा dst_entry *dst = sk_dst_check(sk, inet6_sk(sk)->dst_cookie);

	dst = ip6_sk_dst_check(sk, dst, fl6);
	अगर (dst)
		वापस dst;

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, fl6, final_dst);
	अगर (connected && !IS_ERR(dst))
		ip6_sk_dst_store_flow(sk, dst_clone(dst), fl6);

	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_sk_dst_lookup_flow);

/**
 *      ip6_dst_lookup_tunnel - perक्रमm route lookup on tunnel
 *      @skb: Packet क्रम which lookup is करोne
 *      @dev: Tunnel device
 *      @net: Network namespace of tunnel device
 *      @sock: Socket which provides route info
 *      @saddr: Memory to store the src ip address
 *      @info: Tunnel inक्रमmation
 *      @protocol: IP protocol
 *      @use_cache: Flag to enable cache usage
 *      This function perक्रमms a route lookup on a tunnel
 *
 *      It वापसs a valid dst poपूर्णांकer and stores src address to be used in
 *      tunnel in param saddr on success, अन्यथा a poपूर्णांकer encoded error code.
 */

काष्ठा dst_entry *ip6_dst_lookup_tunnel(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev,
					काष्ठा net *net,
					काष्ठा socket *sock,
					काष्ठा in6_addr *saddr,
					स्थिर काष्ठा ip_tunnel_info *info,
					u8 protocol,
					bool use_cache)
अणु
	काष्ठा dst_entry *dst = शून्य;
#अगर_घोषित CONFIG_DST_CACHE
	काष्ठा dst_cache *dst_cache;
#पूर्ण_अगर
	काष्ठा flowi6 fl6;
	__u8 prio;

#अगर_घोषित CONFIG_DST_CACHE
	dst_cache = (काष्ठा dst_cache *)&info->dst_cache;
	अगर (use_cache) अणु
		dst = dst_cache_get_ip6(dst_cache, saddr);
		अगर (dst)
			वापस dst;
	पूर्ण
#पूर्ण_अगर
	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_mark = skb->mark;
	fl6.flowi6_proto = protocol;
	fl6.daddr = info->key.u.ipv6.dst;
	fl6.saddr = info->key.u.ipv6.src;
	prio = info->key.tos;
	fl6.flowlabel = ip6_make_flowinfo(RT_TOS(prio),
					  info->key.label);

	dst = ipv6_stub->ipv6_dst_lookup_flow(net, sock->sk, &fl6,
					      शून्य);
	अगर (IS_ERR(dst)) अणु
		netdev_dbg(dev, "no route to %pI6\n", &fl6.daddr);
		वापस ERR_PTR(-ENETUNREACH);
	पूर्ण
	अगर (dst->dev == dev) अणु /* is this necessary? */
		netdev_dbg(dev, "circular route to %pI6\n", &fl6.daddr);
		dst_release(dst);
		वापस ERR_PTR(-ELOOP);
	पूर्ण
#अगर_घोषित CONFIG_DST_CACHE
	अगर (use_cache)
		dst_cache_set_ip6(dst_cache, dst, &fl6.saddr);
#पूर्ण_अगर
	*saddr = fl6.saddr;
	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_dst_lookup_tunnel);

अटल अंतरभूत काष्ठा ipv6_opt_hdr *ip6_opt_dup(काष्ठा ipv6_opt_hdr *src,
					       gfp_t gfp)
अणु
	वापस src ? kmemdup(src, (src->hdrlen + 1) * 8, gfp) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा ipv6_rt_hdr *ip6_rthdr_dup(काष्ठा ipv6_rt_hdr *src,
						gfp_t gfp)
अणु
	वापस src ? kmemdup(src, (src->hdrlen + 1) * 8, gfp) : शून्य;
पूर्ण

अटल व्योम ip6_append_data_mtu(अचिन्हित पूर्णांक *mtu,
				पूर्णांक *maxfraglen,
				अचिन्हित पूर्णांक fragheaderlen,
				काष्ठा sk_buff *skb,
				काष्ठा rt6_info *rt,
				अचिन्हित पूर्णांक orig_mtu)
अणु
	अगर (!(rt->dst.flags & DST_XFRM_TUNNEL)) अणु
		अगर (!skb) अणु
			/* first fragment, reserve header_len */
			*mtu = orig_mtu - rt->dst.header_len;

		पूर्ण अन्यथा अणु
			/*
			 * this fragment is not first, the headers
			 * space is regarded as data space.
			 */
			*mtu = orig_mtu;
		पूर्ण
		*maxfraglen = ((*mtu - fragheaderlen) & ~7)
			      + fragheaderlen - माप(काष्ठा frag_hdr);
	पूर्ण
पूर्ण

अटल पूर्णांक ip6_setup_cork(काष्ठा sock *sk, काष्ठा inet_cork_full *cork,
			  काष्ठा inet6_cork *v6_cork, काष्ठा ipcm6_cookie *ipc6,
			  काष्ठा rt6_info *rt, काष्ठा flowi6 *fl6)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	अचिन्हित पूर्णांक mtu;
	काष्ठा ipv6_txoptions *opt = ipc6->opt;

	/*
	 * setup क्रम corking
	 */
	अगर (opt) अणु
		अगर (WARN_ON(v6_cork->opt))
			वापस -EINVAL;

		v6_cork->opt = kzalloc(माप(*opt), sk->sk_allocation);
		अगर (unlikely(!v6_cork->opt))
			वापस -ENOBUFS;

		v6_cork->opt->tot_len = माप(*opt);
		v6_cork->opt->opt_flen = opt->opt_flen;
		v6_cork->opt->opt_nflen = opt->opt_nflen;

		v6_cork->opt->dst0opt = ip6_opt_dup(opt->dst0opt,
						    sk->sk_allocation);
		अगर (opt->dst0opt && !v6_cork->opt->dst0opt)
			वापस -ENOBUFS;

		v6_cork->opt->dst1opt = ip6_opt_dup(opt->dst1opt,
						    sk->sk_allocation);
		अगर (opt->dst1opt && !v6_cork->opt->dst1opt)
			वापस -ENOBUFS;

		v6_cork->opt->hopopt = ip6_opt_dup(opt->hopopt,
						   sk->sk_allocation);
		अगर (opt->hopopt && !v6_cork->opt->hopopt)
			वापस -ENOBUFS;

		v6_cork->opt->srcrt = ip6_rthdr_dup(opt->srcrt,
						    sk->sk_allocation);
		अगर (opt->srcrt && !v6_cork->opt->srcrt)
			वापस -ENOBUFS;

		/* need source address above miyazawa*/
	पूर्ण
	dst_hold(&rt->dst);
	cork->base.dst = &rt->dst;
	cork->fl.u.ip6 = *fl6;
	v6_cork->hop_limit = ipc6->hlimit;
	v6_cork->tclass = ipc6->tclass;
	अगर (rt->dst.flags & DST_XFRM_TUNNEL)
		mtu = np->pmtudisc >= IPV6_PMTUDISC_PROBE ?
		      READ_ONCE(rt->dst.dev->mtu) : dst_mtu(&rt->dst);
	अन्यथा
		mtu = np->pmtudisc >= IPV6_PMTUDISC_PROBE ?
			READ_ONCE(rt->dst.dev->mtu) : dst_mtu(xfrm_dst_path(&rt->dst));
	अगर (np->frag_size < mtu) अणु
		अगर (np->frag_size)
			mtu = np->frag_size;
	पूर्ण
	अगर (mtu < IPV6_MIN_MTU)
		वापस -EINVAL;
	cork->base.fragsize = mtu;
	cork->base.gso_size = ipc6->gso_size;
	cork->base.tx_flags = 0;
	cork->base.mark = ipc6->sockc.mark;
	sock_tx_बारtamp(sk, ipc6->sockc.tsflags, &cork->base.tx_flags);

	अगर (dst_allfrag(xfrm_dst_path(&rt->dst)))
		cork->base.flags |= IPCORK_ALLFRAG;
	cork->base.length = 0;

	cork->base.transmit_समय = ipc6->sockc.transmit_समय;

	वापस 0;
पूर्ण

अटल पूर्णांक __ip6_append_data(काष्ठा sock *sk,
			     काष्ठा flowi6 *fl6,
			     काष्ठा sk_buff_head *queue,
			     काष्ठा inet_cork *cork,
			     काष्ठा inet6_cork *v6_cork,
			     काष्ठा page_frag *pfrag,
			     पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset,
					 पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb),
			     व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
			     अचिन्हित पूर्णांक flags, काष्ठा ipcm6_cookie *ipc6)
अणु
	काष्ठा sk_buff *skb, *skb_prev = शून्य;
	अचिन्हित पूर्णांक maxfraglen, fragheaderlen, mtu, orig_mtu, pmtu;
	काष्ठा ubuf_info *uarg = शून्य;
	पूर्णांक exthdrlen = 0;
	पूर्णांक dst_exthdrlen = 0;
	पूर्णांक hh_len;
	पूर्णांक copy;
	पूर्णांक err;
	पूर्णांक offset = 0;
	u32 tskey = 0;
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)cork->dst;
	काष्ठा ipv6_txoptions *opt = v6_cork->opt;
	पूर्णांक csummode = CHECKSUM_NONE;
	अचिन्हित पूर्णांक maxnonfragsize, headersize;
	अचिन्हित पूर्णांक wmem_alloc_delta = 0;
	bool paged, extra_uref = false;

	skb = skb_peek_tail(queue);
	अगर (!skb) अणु
		exthdrlen = opt ? opt->opt_flen : 0;
		dst_exthdrlen = rt->dst.header_len - rt->rt6i_nfheader_len;
	पूर्ण

	paged = !!cork->gso_size;
	mtu = cork->gso_size ? IP6_MAX_MTU : cork->fragsize;
	orig_mtu = mtu;

	अगर (cork->tx_flags & SKBTX_ANY_SW_TSTAMP &&
	    sk->sk_tsflags & SOF_TIMESTAMPING_OPT_ID)
		tskey = sk->sk_tskey++;

	hh_len = LL_RESERVED_SPACE(rt->dst.dev);

	fragheaderlen = माप(काष्ठा ipv6hdr) + rt->rt6i_nfheader_len +
			(opt ? opt->opt_nflen : 0);
	maxfraglen = ((mtu - fragheaderlen) & ~7) + fragheaderlen -
		     माप(काष्ठा frag_hdr);

	headersize = माप(काष्ठा ipv6hdr) +
		     (opt ? opt->opt_flen + opt->opt_nflen : 0) +
		     (dst_allfrag(&rt->dst) ?
		      माप(काष्ठा frag_hdr) : 0) +
		     rt->rt6i_nfheader_len;

	/* as per RFC 7112 section 5, the entire IPv6 Header Chain must fit
	 * the first fragment
	 */
	अगर (headersize + transhdrlen > mtu)
		जाओ emsgsize;

	अगर (cork->length + length > mtu - headersize && ipc6->करोntfrag &&
	    (sk->sk_protocol == IPPROTO_UDP ||
	     sk->sk_protocol == IPPROTO_RAW)) अणु
		ipv6_local_rxpmtu(sk, fl6, mtu - headersize +
				माप(काष्ठा ipv6hdr));
		जाओ emsgsize;
	पूर्ण

	अगर (ip6_sk_ignore_df(sk))
		maxnonfragsize = माप(काष्ठा ipv6hdr) + IPV6_MAXPLEN;
	अन्यथा
		maxnonfragsize = mtu;

	अगर (cork->length + length > maxnonfragsize - headersize) अणु
emsgsize:
		pmtu = max_t(पूर्णांक, mtu - headersize + माप(काष्ठा ipv6hdr), 0);
		ipv6_local_error(sk, EMSGSIZE, fl6, pmtu);
		वापस -EMSGSIZE;
	पूर्ण

	/* CHECKSUM_PARTIAL only with no extension headers and when
	 * we are not going to fragment
	 */
	अगर (transhdrlen && sk->sk_protocol == IPPROTO_UDP &&
	    headersize == माप(काष्ठा ipv6hdr) &&
	    length <= mtu - headersize &&
	    (!(flags & MSG_MORE) || cork->gso_size) &&
	    rt->dst.dev->features & (NETIF_F_IPV6_CSUM | NETIF_F_HW_CSUM))
		csummode = CHECKSUM_PARTIAL;

	अगर (flags & MSG_ZEROCOPY && length && sock_flag(sk, SOCK_ZEROCOPY)) अणु
		uarg = msg_zerocopy_पुनः_स्मृति(sk, length, skb_zcopy(skb));
		अगर (!uarg)
			वापस -ENOBUFS;
		extra_uref = !skb_zcopy(skb);	/* only ref on new uarg */
		अगर (rt->dst.dev->features & NETIF_F_SG &&
		    csummode == CHECKSUM_PARTIAL) अणु
			paged = true;
		पूर्ण अन्यथा अणु
			uarg->zerocopy = 0;
			skb_zcopy_set(skb, uarg, &extra_uref);
		पूर्ण
	पूर्ण

	/*
	 * Let's try using as much space as possible.
	 * Use MTU अगर total length of the message fits पूर्णांकo the MTU.
	 * Otherwise, we need to reserve fragment header and
	 * fragment alignment (= 8-15 octects, in total).
	 *
	 * Note that we may need to "move" the data from the tail
	 * of the buffer to the new fragment when we split
	 * the message.
	 *
	 * FIXME: It may be fragmented पूर्णांकo multiple chunks
	 *        at once अगर non-fragmentable extension headers
	 *        are too large.
	 * --yoshfuji
	 */

	cork->length += length;
	अगर (!skb)
		जाओ alloc_new_skb;

	जबतक (length > 0) अणु
		/* Check अगर the reमुख्यing data fits पूर्णांकo current packet. */
		copy = (cork->length <= mtu && !(cork->flags & IPCORK_ALLFRAG) ? mtu : maxfraglen) - skb->len;
		अगर (copy < length)
			copy = maxfraglen - skb->len;

		अगर (copy <= 0) अणु
			अक्षर *data;
			अचिन्हित पूर्णांक datalen;
			अचिन्हित पूर्णांक fraglen;
			अचिन्हित पूर्णांक fraggap;
			अचिन्हित पूर्णांक alloclen;
			अचिन्हित पूर्णांक pagedlen;
alloc_new_skb:
			/* There's no room in the current skb */
			अगर (skb)
				fraggap = skb->len - maxfraglen;
			अन्यथा
				fraggap = 0;
			/* update mtu and maxfraglen अगर necessary */
			अगर (!skb || !skb_prev)
				ip6_append_data_mtu(&mtu, &maxfraglen,
						    fragheaderlen, skb, rt,
						    orig_mtu);

			skb_prev = skb;

			/*
			 * If reमुख्यing data exceeds the mtu,
			 * we know we need more fragment(s).
			 */
			datalen = length + fraggap;

			अगर (datalen > (cork->length <= mtu && !(cork->flags & IPCORK_ALLFRAG) ? mtu : maxfraglen) - fragheaderlen)
				datalen = maxfraglen - fragheaderlen - rt->dst.trailer_len;
			fraglen = datalen + fragheaderlen;
			pagedlen = 0;

			अगर ((flags & MSG_MORE) &&
			    !(rt->dst.dev->features&NETIF_F_SG))
				alloclen = mtu;
			अन्यथा अगर (!paged)
				alloclen = fraglen;
			अन्यथा अणु
				alloclen = min_t(पूर्णांक, fraglen, MAX_HEADER);
				pagedlen = fraglen - alloclen;
			पूर्ण

			alloclen += dst_exthdrlen;

			अगर (datalen != length + fraggap) अणु
				/*
				 * this is not the last fragment, the trailer
				 * space is regarded as data space.
				 */
				datalen += rt->dst.trailer_len;
			पूर्ण

			alloclen += rt->dst.trailer_len;
			fraglen = datalen + fragheaderlen;

			/*
			 * We just reserve space क्रम fragment header.
			 * Note: this may be overallocation अगर the message
			 * (without MSG_MORE) fits पूर्णांकo the MTU.
			 */
			alloclen += माप(काष्ठा frag_hdr);

			copy = datalen - transhdrlen - fraggap - pagedlen;
			अगर (copy < 0) अणु
				err = -EINVAL;
				जाओ error;
			पूर्ण
			अगर (transhdrlen) अणु
				skb = sock_alloc_send_skb(sk,
						alloclen + hh_len,
						(flags & MSG_DONTWAIT), &err);
			पूर्ण अन्यथा अणु
				skb = शून्य;
				अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) + wmem_alloc_delta <=
				    2 * sk->sk_sndbuf)
					skb = alloc_skb(alloclen + hh_len,
							sk->sk_allocation);
				अगर (unlikely(!skb))
					err = -ENOBUFS;
			पूर्ण
			अगर (!skb)
				जाओ error;
			/*
			 *	Fill in the control काष्ठाures
			 */
			skb->protocol = htons(ETH_P_IPV6);
			skb->ip_summed = csummode;
			skb->csum = 0;
			/* reserve क्रम fragmentation and ipsec header */
			skb_reserve(skb, hh_len + माप(काष्ठा frag_hdr) +
				    dst_exthdrlen);

			/*
			 *	Find where to start putting bytes
			 */
			data = skb_put(skb, fraglen - pagedlen);
			skb_set_network_header(skb, exthdrlen);
			data += fragheaderlen;
			skb->transport_header = (skb->network_header +
						 fragheaderlen);
			अगर (fraggap) अणु
				skb->csum = skb_copy_and_csum_bits(
					skb_prev, maxfraglen,
					data + transhdrlen, fraggap);
				skb_prev->csum = csum_sub(skb_prev->csum,
							  skb->csum);
				data += fraggap;
				pskb_trim_unique(skb_prev, maxfraglen);
			पूर्ण
			अगर (copy > 0 &&
			    getfrag(from, data + transhdrlen, offset,
				    copy, fraggap, skb) < 0) अणु
				err = -EFAULT;
				kमुक्त_skb(skb);
				जाओ error;
			पूर्ण

			offset += copy;
			length -= copy + transhdrlen;
			transhdrlen = 0;
			exthdrlen = 0;
			dst_exthdrlen = 0;

			/* Only the initial fragment is समय stamped */
			skb_shinfo(skb)->tx_flags = cork->tx_flags;
			cork->tx_flags = 0;
			skb_shinfo(skb)->tskey = tskey;
			tskey = 0;
			skb_zcopy_set(skb, uarg, &extra_uref);

			अगर ((flags & MSG_CONFIRM) && !skb_prev)
				skb_set_dst_pending_confirm(skb, 1);

			/*
			 * Put the packet on the pending queue
			 */
			अगर (!skb->deकाष्ठाor) अणु
				skb->deकाष्ठाor = sock_wमुक्त;
				skb->sk = sk;
				wmem_alloc_delta += skb->truesize;
			पूर्ण
			__skb_queue_tail(queue, skb);
			जारी;
		पूर्ण

		अगर (copy > length)
			copy = length;

		अगर (!(rt->dst.dev->features&NETIF_F_SG) &&
		    skb_tailroom(skb) >= copy) अणु
			अचिन्हित पूर्णांक off;

			off = skb->len;
			अगर (getfrag(from, skb_put(skb, copy),
						offset, copy, off, skb) < 0) अणु
				__skb_trim(skb, off);
				err = -EFAULT;
				जाओ error;
			पूर्ण
		पूर्ण अन्यथा अगर (!uarg || !uarg->zerocopy) अणु
			पूर्णांक i = skb_shinfo(skb)->nr_frags;

			err = -ENOMEM;
			अगर (!sk_page_frag_refill(sk, pfrag))
				जाओ error;

			अगर (!skb_can_coalesce(skb, i, pfrag->page,
					      pfrag->offset)) अणु
				err = -EMSGSIZE;
				अगर (i == MAX_SKB_FRAGS)
					जाओ error;

				__skb_fill_page_desc(skb, i, pfrag->page,
						     pfrag->offset, 0);
				skb_shinfo(skb)->nr_frags = ++i;
				get_page(pfrag->page);
			पूर्ण
			copy = min_t(पूर्णांक, copy, pfrag->size - pfrag->offset);
			अगर (getfrag(from,
				    page_address(pfrag->page) + pfrag->offset,
				    offset, copy, skb->len, skb) < 0)
				जाओ error_efault;

			pfrag->offset += copy;
			skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
			skb->len += copy;
			skb->data_len += copy;
			skb->truesize += copy;
			wmem_alloc_delta += copy;
		पूर्ण अन्यथा अणु
			err = skb_zerocopy_iter_dgram(skb, from, copy);
			अगर (err < 0)
				जाओ error;
		पूर्ण
		offset += copy;
		length -= copy;
	पूर्ण

	अगर (wmem_alloc_delta)
		refcount_add(wmem_alloc_delta, &sk->sk_wmem_alloc);
	वापस 0;

error_efault:
	err = -EFAULT;
error:
	net_zcopy_put_पात(uarg, extra_uref);
	cork->length -= length;
	IP6_INC_STATS(sock_net(sk), rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
	refcount_add(wmem_alloc_delta, &sk->sk_wmem_alloc);
	वापस err;
पूर्ण

पूर्णांक ip6_append_data(काष्ठा sock *sk,
		    पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len,
				पूर्णांक odd, काष्ठा sk_buff *skb),
		    व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
		    काष्ठा ipcm6_cookie *ipc6, काष्ठा flowi6 *fl6,
		    काष्ठा rt6_info *rt, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	पूर्णांक exthdrlen;
	पूर्णांक err;

	अगर (flags&MSG_PROBE)
		वापस 0;
	अगर (skb_queue_empty(&sk->sk_ग_लिखो_queue)) अणु
		/*
		 * setup क्रम corking
		 */
		err = ip6_setup_cork(sk, &inet->cork, &np->cork,
				     ipc6, rt, fl6);
		अगर (err)
			वापस err;

		exthdrlen = (ipc6->opt ? ipc6->opt->opt_flen : 0);
		length += exthdrlen;
		transhdrlen += exthdrlen;
	पूर्ण अन्यथा अणु
		fl6 = &inet->cork.fl.u.ip6;
		transhdrlen = 0;
	पूर्ण

	वापस __ip6_append_data(sk, fl6, &sk->sk_ग_लिखो_queue, &inet->cork.base,
				 &np->cork, sk_page_frag(sk), getfrag,
				 from, length, transhdrlen, flags, ipc6);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_append_data);

अटल व्योम ip6_cork_release(काष्ठा inet_cork_full *cork,
			     काष्ठा inet6_cork *v6_cork)
अणु
	अगर (v6_cork->opt) अणु
		kमुक्त(v6_cork->opt->dst0opt);
		kमुक्त(v6_cork->opt->dst1opt);
		kमुक्त(v6_cork->opt->hopopt);
		kमुक्त(v6_cork->opt->srcrt);
		kमुक्त(v6_cork->opt);
		v6_cork->opt = शून्य;
	पूर्ण

	अगर (cork->base.dst) अणु
		dst_release(cork->base.dst);
		cork->base.dst = शून्य;
		cork->base.flags &= ~IPCORK_ALLFRAG;
	पूर्ण
	स_रखो(&cork->fl, 0, माप(cork->fl));
पूर्ण

काष्ठा sk_buff *__ip6_make_skb(काष्ठा sock *sk,
			       काष्ठा sk_buff_head *queue,
			       काष्ठा inet_cork_full *cork,
			       काष्ठा inet6_cork *v6_cork)
अणु
	काष्ठा sk_buff *skb, *पंचांगp_skb;
	काष्ठा sk_buff **tail_skb;
	काष्ठा in6_addr final_dst_buf, *final_dst = &final_dst_buf;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा ipv6hdr *hdr;
	काष्ठा ipv6_txoptions *opt = v6_cork->opt;
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)cork->base.dst;
	काष्ठा flowi6 *fl6 = &cork->fl.u.ip6;
	अचिन्हित अक्षर proto = fl6->flowi6_proto;

	skb = __skb_dequeue(queue);
	अगर (!skb)
		जाओ out;
	tail_skb = &(skb_shinfo(skb)->frag_list);

	/* move skb->data to ip header from ext header */
	अगर (skb->data < skb_network_header(skb))
		__skb_pull(skb, skb_network_offset(skb));
	जबतक ((पंचांगp_skb = __skb_dequeue(queue)) != शून्य) अणु
		__skb_pull(पंचांगp_skb, skb_network_header_len(skb));
		*tail_skb = पंचांगp_skb;
		tail_skb = &(पंचांगp_skb->next);
		skb->len += पंचांगp_skb->len;
		skb->data_len += पंचांगp_skb->len;
		skb->truesize += पंचांगp_skb->truesize;
		पंचांगp_skb->deकाष्ठाor = शून्य;
		पंचांगp_skb->sk = शून्य;
	पूर्ण

	/* Allow local fragmentation. */
	skb->ignore_df = ip6_sk_ignore_df(sk);

	*final_dst = fl6->daddr;
	__skb_pull(skb, skb_network_header_len(skb));
	अगर (opt && opt->opt_flen)
		ipv6_push_frag_opts(skb, opt, &proto);
	अगर (opt && opt->opt_nflen)
		ipv6_push_nfrag_opts(skb, opt, &proto, &final_dst, &fl6->saddr);

	skb_push(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	ip6_flow_hdr(hdr, v6_cork->tclass,
		     ip6_make_flowlabel(net, skb, fl6->flowlabel,
					ip6_स्वतःflowlabel(net, np), fl6));
	hdr->hop_limit = v6_cork->hop_limit;
	hdr->nexthdr = proto;
	hdr->saddr = fl6->saddr;
	hdr->daddr = *final_dst;

	skb->priority = sk->sk_priority;
	skb->mark = cork->base.mark;

	skb->tstamp = cork->base.transmit_समय;

	skb_dst_set(skb, dst_clone(&rt->dst));
	IP6_UPD_PO_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUT, skb->len);
	अगर (proto == IPPROTO_ICMPV6) अणु
		काष्ठा inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

		ICMP6MSGOUT_INC_STATS(net, idev, icmp6_hdr(skb)->icmp6_type);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	पूर्ण

	ip6_cork_release(cork, v6_cork);
out:
	वापस skb;
पूर्ण

पूर्णांक ip6_send_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)skb_dst(skb);
	पूर्णांक err;

	err = ip6_local_out(net, skb->sk, skb);
	अगर (err) अणु
		अगर (err > 0)
			err = net_xmit_त्रुटि_सं(err);
		अगर (err)
			IP6_INC_STATS(net, rt->rt6i_idev,
				      IPSTATS_MIB_OUTDISCARDS);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ip6_push_pending_frames(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	skb = ip6_finish_skb(sk);
	अगर (!skb)
		वापस 0;

	वापस ip6_send_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_push_pending_frames);

अटल व्योम __ip6_flush_pending_frames(काष्ठा sock *sk,
				       काष्ठा sk_buff_head *queue,
				       काष्ठा inet_cork_full *cork,
				       काष्ठा inet6_cork *v6_cork)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue_tail(queue)) != शून्य) अणु
		अगर (skb_dst(skb))
			IP6_INC_STATS(sock_net(sk), ip6_dst_idev(skb_dst(skb)),
				      IPSTATS_MIB_OUTDISCARDS);
		kमुक्त_skb(skb);
	पूर्ण

	ip6_cork_release(cork, v6_cork);
पूर्ण

व्योम ip6_flush_pending_frames(काष्ठा sock *sk)
अणु
	__ip6_flush_pending_frames(sk, &sk->sk_ग_लिखो_queue,
				   &inet_sk(sk)->cork, &inet6_sk(sk)->cork);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_flush_pending_frames);

काष्ठा sk_buff *ip6_make_skb(काष्ठा sock *sk,
			     पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset,
					 पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb),
			     व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
			     काष्ठा ipcm6_cookie *ipc6, काष्ठा flowi6 *fl6,
			     काष्ठा rt6_info *rt, अचिन्हित पूर्णांक flags,
			     काष्ठा inet_cork_full *cork)
अणु
	काष्ठा inet6_cork v6_cork;
	काष्ठा sk_buff_head queue;
	पूर्णांक exthdrlen = (ipc6->opt ? ipc6->opt->opt_flen : 0);
	पूर्णांक err;

	अगर (flags & MSG_PROBE)
		वापस शून्य;

	__skb_queue_head_init(&queue);

	cork->base.flags = 0;
	cork->base.addr = 0;
	cork->base.opt = शून्य;
	cork->base.dst = शून्य;
	v6_cork.opt = शून्य;
	err = ip6_setup_cork(sk, cork, &v6_cork, ipc6, rt, fl6);
	अगर (err) अणु
		ip6_cork_release(cork, &v6_cork);
		वापस ERR_PTR(err);
	पूर्ण
	अगर (ipc6->करोntfrag < 0)
		ipc6->करोntfrag = inet6_sk(sk)->करोntfrag;

	err = __ip6_append_data(sk, fl6, &queue, &cork->base, &v6_cork,
				&current->task_frag, getfrag, from,
				length + exthdrlen, transhdrlen + exthdrlen,
				flags, ipc6);
	अगर (err) अणु
		__ip6_flush_pending_frames(sk, &queue, cork, &v6_cork);
		वापस ERR_PTR(err);
	पूर्ण

	वापस __ip6_make_skb(sk, &queue, cork, &v6_cork);
पूर्ण
