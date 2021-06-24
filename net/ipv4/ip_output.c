<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The Internet Protocol (IP) output module.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald Becker, <becker@super.org>
 *		Alan Cox, <Alan.Cox@linux.org>
 *		Riअक्षरd Underwood
 *		Stefan Becker, <stefanb@yello.ping.de>
 *		Jorge Cwik, <jorge@laser.satlink.net>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Hirokazu Takahashi, <taka@valinux.co.jp>
 *
 *	See ip_input.c क्रम original log
 *
 *	Fixes:
 *		Alan Cox	:	Missing nonblock feature in ip_build_xmit.
 *		Mike Kilburn	:	htons() missing in ip_build_xmit.
 *		Bradक्रमd Johnson:	Fix faulty handling of some frames when
 *					no route is found.
 *		Alexander Demenshin:	Missing sk/skb मुक्त in ip_queue_xmit
 *					(in हाल अगर packet not accepted by
 *					output firewall rules)
 *		Mike McLagan	:	Routing by source
 *		Alexey Kuznetsov:	use new route cache
 *		Andi Kleen:		Fix broken PMTU recovery and हटाओ
 *					some redundant tests.
 *	Vitaly E. Lavrov	:	Transparent proxy revived after year coma.
 *		Andi Kleen	: 	Replace ip_reply with ip_send_reply.
 *		Andi Kleen	:	Split fast and slow ip_build_xmit path
 *					क्रम decreased रेजिस्टर pressure on x86
 *					and more पढ़ोability.
 *		Marc Boucher	:	When call_out_firewall वापसs FW_QUEUE,
 *					silently drop skb instead of failing with -EPERM.
 *		Detlev Wengorz	:	Copy protocol क्रम fragments.
 *		Hirokazu Takahashi:	HW checksumming क्रम outgoing UDP
 *					datagrams.
 *		Hirokazu Takahashi:	sendfile() on UDP works now.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>

#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>

#समावेश <net/snmp.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/route.h>
#समावेश <net/xfrm.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/arp.h>
#समावेश <net/icmp.h>
#समावेश <net/checksum.h>
#समावेश <net/inetpeer.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/lwtunnel.h>
#समावेश <linux/bpf-cgroup.h>
#समावेश <linux/igmp.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netlink.h>
#समावेश <linux/tcp.h>

अटल पूर्णांक
ip_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
	    अचिन्हित पूर्णांक mtu,
	    पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *));

/* Generate a checksum क्रम an outgoing IP datagram. */
व्योम ip_send_check(काष्ठा iphdr *iph)
अणु
	iph->check = 0;
	iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph, iph->ihl);
पूर्ण
EXPORT_SYMBOL(ip_send_check);

पूर्णांक __ip_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	iph->tot_len = htons(skb->len);
	ip_send_check(iph);

	/* अगर egress device is enslaved to an L3 master device pass the
	 * skb to its handler क्रम processing
	 */
	skb = l3mdev_ip_out(sk, skb);
	अगर (unlikely(!skb))
		वापस 0;

	skb->protocol = htons(ETH_P_IP);

	वापस nf_hook(NFPROTO_IPV4, NF_INET_LOCAL_OUT,
		       net, sk, skb, शून्य, skb_dst(skb)->dev,
		       dst_output);
पूर्ण

पूर्णांक ip_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = __ip_local_out(net, sk, skb);
	अगर (likely(err == 1))
		err = dst_output(net, sk, skb);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ip_local_out);

अटल अंतरभूत पूर्णांक ip_select_ttl(काष्ठा inet_sock *inet, काष्ठा dst_entry *dst)
अणु
	पूर्णांक ttl = inet->uc_ttl;

	अगर (ttl < 0)
		ttl = ip4_dst_hoplimit(dst);
	वापस ttl;
पूर्ण

/*
 *		Add an ip header to a skbuff and send it out.
 *
 */
पूर्णांक ip_build_and_send_pkt(काष्ठा sk_buff *skb, स्थिर काष्ठा sock *sk,
			  __be32 saddr, __be32 daddr, काष्ठा ip_options_rcu *opt,
			  u8 tos)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा net *net = sock_net(sk);
	काष्ठा iphdr *iph;

	/* Build the IP header. */
	skb_push(skb, माप(काष्ठा iphdr) + (opt ? opt->opt.optlen : 0));
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	iph->version  = 4;
	iph->ihl      = 5;
	iph->tos      = tos;
	iph->ttl      = ip_select_ttl(inet, &rt->dst);
	iph->daddr    = (opt && opt->opt.srr ? opt->opt.faddr : daddr);
	iph->saddr    = saddr;
	iph->protocol = sk->sk_protocol;
	अगर (ip_करोnt_fragment(sk, &rt->dst)) अणु
		iph->frag_off = htons(IP_DF);
		iph->id = 0;
	पूर्ण अन्यथा अणु
		iph->frag_off = 0;
		__ip_select_ident(net, iph, 1);
	पूर्ण

	अगर (opt && opt->opt.optlen) अणु
		iph->ihl += opt->opt.optlen>>2;
		ip_options_build(skb, &opt->opt, daddr, rt, 0);
	पूर्ण

	skb->priority = sk->sk_priority;
	अगर (!skb->mark)
		skb->mark = sk->sk_mark;

	/* Send it out. */
	वापस ip_local_out(net, skb->sk, skb);
पूर्ण
EXPORT_SYMBOL_GPL(ip_build_and_send_pkt);

अटल पूर्णांक ip_finish_output2(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा rtable *rt = (काष्ठा rtable *)dst;
	काष्ठा net_device *dev = dst->dev;
	अचिन्हित पूर्णांक hh_len = LL_RESERVED_SPACE(dev);
	काष्ठा neighbour *neigh;
	bool is_v6gw = false;

	अगर (rt->rt_type == RTN_MULTICAST) अणु
		IP_UPD_PO_STATS(net, IPSTATS_MIB_OUTMCAST, skb->len);
	पूर्ण अन्यथा अगर (rt->rt_type == RTN_BROADCAST)
		IP_UPD_PO_STATS(net, IPSTATS_MIB_OUTBCAST, skb->len);

	/* Be paranoid, rather than too clever. */
	अगर (unlikely(skb_headroom(skb) < hh_len && dev->header_ops)) अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_पुनः_स्मृति_headroom(skb, LL_RESERVED_SPACE(dev));
		अगर (!skb2) अणु
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(skb2, skb->sk);
		consume_skb(skb);
		skb = skb2;
	पूर्ण

	अगर (lwtunnel_xmit_redirect(dst->lwtstate)) अणु
		पूर्णांक res = lwtunnel_xmit(skb);

		अगर (res < 0 || res == LWTUNNEL_XMIT_DONE)
			वापस res;
	पूर्ण

	rcu_पढ़ो_lock_bh();
	neigh = ip_neigh_क्रम_gw(rt, skb, &is_v6gw);
	अगर (!IS_ERR(neigh)) अणु
		पूर्णांक res;

		sock_confirm_neigh(skb, neigh);
		/* अगर crossing protocols, can not use the cached header */
		res = neigh_output(neigh, skb, is_v6gw);
		rcu_पढ़ो_unlock_bh();
		वापस res;
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	net_dbg_ratelimited("%s: No header cache and no neighbour!\n",
			    __func__);
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ip_finish_output_gso(काष्ठा net *net, काष्ठा sock *sk,
				काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा sk_buff *segs, *nskb;
	netdev_features_t features;
	पूर्णांक ret = 0;

	/* common हाल: seglen is <= mtu
	 */
	अगर (skb_gso_validate_network_len(skb, mtu))
		वापस ip_finish_output2(net, sk, skb);

	/* Slowpath -  GSO segment length exceeds the egress MTU.
	 *
	 * This can happen in several हालs:
	 *  - Forwarding of a TCP GRO skb, when DF flag is not set.
	 *  - Forwarding of an skb that arrived on a भवization पूर्णांकerface
	 *    (virtio-net/vhost/tap) with TSO/GSO size set by other network
	 *    stack.
	 *  - Local GSO skb transmitted on an NETIF_F_TSO tunnel stacked over an
	 *    पूर्णांकerface with a smaller MTU.
	 *  - Arriving GRO skb (or GSO skb in a भवized environment) that is
	 *    bridged to a NETIF_F_TSO tunnel stacked over an पूर्णांकerface with an
	 *    insufficient MTU.
	 */
	features = netअगर_skb_features(skb);
	BUILD_BUG_ON(माप(*IPCB(skb)) > SKB_GSO_CB_OFFSET);
	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	consume_skb(skb);

	skb_list_walk_safe(segs, segs, nskb) अणु
		पूर्णांक err;

		skb_mark_not_on_list(segs);
		err = ip_fragment(net, sk, segs, mtu, ip_finish_output2);

		अगर (err && ret == 0)
			ret = err;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ip_finish_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक mtu;

#अगर defined(CONFIG_NETFILTER) && defined(CONFIG_XFRM)
	/* Policy lookup after SNAT yielded a new policy */
	अगर (skb_dst(skb)->xfrm) अणु
		IPCB(skb)->flags |= IPSKB_REROUTED;
		वापस dst_output(net, sk, skb);
	पूर्ण
#पूर्ण_अगर
	mtu = ip_skb_dst_mtu(sk, skb);
	अगर (skb_is_gso(skb))
		वापस ip_finish_output_gso(net, sk, skb, mtu);

	अगर (skb->len > mtu || IPCB(skb)->frag_max_size)
		वापस ip_fragment(net, sk, skb, mtu, ip_finish_output2);

	वापस ip_finish_output2(net, sk, skb);
पूर्ण

अटल पूर्णांक ip_finish_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	ret = BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb);
	चयन (ret) अणु
	हाल NET_XMIT_SUCCESS:
		वापस __ip_finish_output(net, sk, skb);
	हाल NET_XMIT_CN:
		वापस __ip_finish_output(net, sk, skb) ? : ret;
	शेष:
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण
पूर्ण

अटल पूर्णांक ip_mc_finish_output(काष्ठा net *net, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *new_rt;
	bool करो_cn = false;
	पूर्णांक ret, err;

	ret = BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb);
	चयन (ret) अणु
	हाल NET_XMIT_CN:
		करो_cn = true;
		fallthrough;
	हाल NET_XMIT_SUCCESS:
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	/* Reset rt_iअगर so that inet_iअगर() will वापस skb->skb_iअगर. Setting
	 * this to non-zero causes ipi_अगरindex in in_pktinfo to be overwritten,
	 * see ipv4_pktinfo_prepare().
	 */
	new_rt = rt_dst_clone(net->loopback_dev, skb_rtable(skb));
	अगर (new_rt) अणु
		new_rt->rt_iअगर = 0;
		skb_dst_drop(skb);
		skb_dst_set(skb, &new_rt->dst);
	पूर्ण

	err = dev_loopback_xmit(net, sk, skb);
	वापस (करो_cn && err) ? ret : err;
पूर्ण

पूर्णांक ip_mc_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा net_device *dev = rt->dst.dev;

	/*
	 *	If the indicated पूर्णांकerface is up and running, send the packet.
	 */
	IP_UPD_PO_STATS(net, IPSTATS_MIB_OUT, skb->len);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_IP);

	/*
	 *	Multicasts are looped back क्रम other local users
	 */

	अगर (rt->rt_flags&RTCF_MULTICAST) अणु
		अगर (sk_mc_loop(sk)
#अगर_घोषित CONFIG_IP_MROUTE
		/* Small optimization: करो not loopback not local frames,
		   which वापसed after क्रमwarding; they will be  dropped
		   by ip_mr_input in any हाल.
		   Note, that local frames are looped back to be delivered
		   to local recipients.

		   This check is duplicated in ip_mr_input at the moment.
		 */
		    &&
		    ((rt->rt_flags & RTCF_LOCAL) ||
		     !(IPCB(skb)->flags & IPSKB_FORWARDED))
#पूर्ण_अगर
		   ) अणु
			काष्ठा sk_buff *newskb = skb_clone(skb, GFP_ATOMIC);
			अगर (newskb)
				NF_HOOK(NFPROTO_IPV4, NF_INET_POST_ROUTING,
					net, sk, newskb, शून्य, newskb->dev,
					ip_mc_finish_output);
		पूर्ण

		/* Multicasts with ttl 0 must not go beyond the host */

		अगर (ip_hdr(skb)->ttl == 0) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (rt->rt_flags&RTCF_BROADCAST) अणु
		काष्ठा sk_buff *newskb = skb_clone(skb, GFP_ATOMIC);
		अगर (newskb)
			NF_HOOK(NFPROTO_IPV4, NF_INET_POST_ROUTING,
				net, sk, newskb, शून्य, newskb->dev,
				ip_mc_finish_output);
	पूर्ण

	वापस NF_HOOK_COND(NFPROTO_IPV4, NF_INET_POST_ROUTING,
			    net, sk, skb, शून्य, skb->dev,
			    ip_finish_output,
			    !(IPCB(skb)->flags & IPSKB_REROUTED));
पूर्ण

पूर्णांक ip_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb_dst(skb)->dev, *indev = skb->dev;

	IP_UPD_PO_STATS(net, IPSTATS_MIB_OUT, skb->len);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_IP);

	वापस NF_HOOK_COND(NFPROTO_IPV4, NF_INET_POST_ROUTING,
			    net, sk, skb, indev, dev,
			    ip_finish_output,
			    !(IPCB(skb)->flags & IPSKB_REROUTED));
पूर्ण
EXPORT_SYMBOL(ip_output);

/*
 * copy saddr and daddr, possibly using 64bit load/stores
 * Equivalent to :
 *   iph->saddr = fl4->saddr;
 *   iph->daddr = fl4->daddr;
 */
अटल व्योम ip_copy_addrs(काष्ठा iphdr *iph, स्थिर काष्ठा flowi4 *fl4)
अणु
	BUILD_BUG_ON(दुरत्व(typeof(*fl4), daddr) !=
		     दुरत्व(typeof(*fl4), saddr) + माप(fl4->saddr));
	स_नकल(&iph->saddr, &fl4->saddr,
	       माप(fl4->saddr) + माप(fl4->daddr));
पूर्ण

/* Note: skb->sk can be dअगरferent from sk, in हाल of tunnels */
पूर्णांक __ip_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl,
		    __u8 tos)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा ip_options_rcu *inet_opt;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;
	काष्ठा iphdr *iph;
	पूर्णांक res;

	/* Skip all of this अगर the packet is alपढ़ोy routed,
	 * f.e. by something like SCTP.
	 */
	rcu_पढ़ो_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	fl4 = &fl->u.ip4;
	rt = skb_rtable(skb);
	अगर (rt)
		जाओ packet_routed;

	/* Make sure we can route this packet. */
	rt = (काष्ठा rtable *)__sk_dst_check(sk, 0);
	अगर (!rt) अणु
		__be32 daddr;

		/* Use correct destination address अगर we have options. */
		daddr = inet->inet_daddr;
		अगर (inet_opt && inet_opt->opt.srr)
			daddr = inet_opt->opt.faddr;

		/* If this fails, retransmit mechanism of transport layer will
		 * keep trying until route appears or the connection बार
		 * itself out.
		 */
		rt = ip_route_output_ports(net, fl4, sk,
					   daddr, inet->inet_saddr,
					   inet->inet_dport,
					   inet->inet_sport,
					   sk->sk_protocol,
					   RT_CONN_FLAGS_TOS(sk, tos),
					   sk->sk_bound_dev_अगर);
		अगर (IS_ERR(rt))
			जाओ no_route;
		sk_setup_caps(sk, &rt->dst);
	पूर्ण
	skb_dst_set_noref(skb, &rt->dst);

packet_routed:
	अगर (inet_opt && inet_opt->opt.is_strictroute && rt->rt_uses_gateway)
		जाओ no_route;

	/* OK, we know where to send it, allocate and build IP header. */
	skb_push(skb, माप(काष्ठा iphdr) + (inet_opt ? inet_opt->opt.optlen : 0));
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);
	*((__be16 *)iph) = htons((4 << 12) | (5 << 8) | (tos & 0xff));
	अगर (ip_करोnt_fragment(sk, &rt->dst) && !skb->ignore_df)
		iph->frag_off = htons(IP_DF);
	अन्यथा
		iph->frag_off = 0;
	iph->ttl      = ip_select_ttl(inet, &rt->dst);
	iph->protocol = sk->sk_protocol;
	ip_copy_addrs(iph, fl4);

	/* Transport layer set skb->h.foo itself. */

	अगर (inet_opt && inet_opt->opt.optlen) अणु
		iph->ihl += inet_opt->opt.optlen >> 2;
		ip_options_build(skb, &inet_opt->opt, inet->inet_daddr, rt, 0);
	पूर्ण

	ip_select_ident_segs(net, skb, sk,
			     skb_shinfo(skb)->gso_segs ?: 1);

	/* TODO : should we use skb->sk here instead of sk ? */
	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;

	res = ip_local_out(net, sk, skb);
	rcu_पढ़ो_unlock();
	वापस res;

no_route:
	rcu_पढ़ो_unlock();
	IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
	kमुक्त_skb(skb);
	वापस -EHOSTUNREACH;
पूर्ण
EXPORT_SYMBOL(__ip_queue_xmit);

पूर्णांक ip_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl)
अणु
	वापस __ip_queue_xmit(sk, skb, fl, inet_sk(sk)->tos);
पूर्ण
EXPORT_SYMBOL(ip_queue_xmit);

अटल व्योम ip_copy_metadata(काष्ठा sk_buff *to, काष्ठा sk_buff *from)
अणु
	to->pkt_type = from->pkt_type;
	to->priority = from->priority;
	to->protocol = from->protocol;
	to->skb_iअगर = from->skb_iअगर;
	skb_dst_drop(to);
	skb_dst_copy(to, from);
	to->dev = from->dev;
	to->mark = from->mark;

	skb_copy_hash(to, from);

#अगर_घोषित CONFIG_NET_SCHED
	to->tc_index = from->tc_index;
#पूर्ण_अगर
	nf_copy(to, from);
	skb_ext_copy(to, from);
#अगर IS_ENABLED(CONFIG_IP_VS)
	to->ipvs_property = from->ipvs_property;
#पूर्ण_अगर
	skb_copy_secmark(to, from);
पूर्ण

अटल पूर्णांक ip_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक mtu,
		       पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	अगर ((iph->frag_off & htons(IP_DF)) == 0)
		वापस ip_करो_fragment(net, sk, skb, output);

	अगर (unlikely(!skb->ignore_df ||
		     (IPCB(skb)->frag_max_size &&
		      IPCB(skb)->frag_max_size > mtu))) अणु
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
			  htonl(mtu));
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	वापस ip_करो_fragment(net, sk, skb, output);
पूर्ण

व्योम ip_fraglist_init(काष्ठा sk_buff *skb, काष्ठा iphdr *iph,
		      अचिन्हित पूर्णांक hlen, काष्ठा ip_fraglist_iter *iter)
अणु
	अचिन्हित पूर्णांक first_len = skb_pagelen(skb);

	iter->frag = skb_shinfo(skb)->frag_list;
	skb_frag_list_init(skb);

	iter->offset = 0;
	iter->iph = iph;
	iter->hlen = hlen;

	skb->data_len = first_len - skb_headlen(skb);
	skb->len = first_len;
	iph->tot_len = htons(first_len);
	iph->frag_off = htons(IP_MF);
	ip_send_check(iph);
पूर्ण
EXPORT_SYMBOL(ip_fraglist_init);

अटल व्योम ip_fraglist_ipcb_prepare(काष्ठा sk_buff *skb,
				     काष्ठा ip_fraglist_iter *iter)
अणु
	काष्ठा sk_buff *to = iter->frag;

	/* Copy the flags to each fragment. */
	IPCB(to)->flags = IPCB(skb)->flags;

	अगर (iter->offset == 0)
		ip_options_fragment(to);
पूर्ण

व्योम ip_fraglist_prepare(काष्ठा sk_buff *skb, काष्ठा ip_fraglist_iter *iter)
अणु
	अचिन्हित पूर्णांक hlen = iter->hlen;
	काष्ठा iphdr *iph = iter->iph;
	काष्ठा sk_buff *frag;

	frag = iter->frag;
	frag->ip_summed = CHECKSUM_NONE;
	skb_reset_transport_header(frag);
	__skb_push(frag, hlen);
	skb_reset_network_header(frag);
	स_नकल(skb_network_header(frag), iph, hlen);
	iter->iph = ip_hdr(frag);
	iph = iter->iph;
	iph->tot_len = htons(frag->len);
	ip_copy_metadata(frag, skb);
	iter->offset += skb->len - hlen;
	iph->frag_off = htons(iter->offset >> 3);
	अगर (frag->next)
		iph->frag_off |= htons(IP_MF);
	/* Ready, complete checksum */
	ip_send_check(iph);
पूर्ण
EXPORT_SYMBOL(ip_fraglist_prepare);

व्योम ip_frag_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen,
		  अचिन्हित पूर्णांक ll_rs, अचिन्हित पूर्णांक mtu, bool DF,
		  काष्ठा ip_frag_state *state)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	state->DF = DF;
	state->hlen = hlen;
	state->ll_rs = ll_rs;
	state->mtu = mtu;

	state->left = skb->len - hlen;	/* Space per frame */
	state->ptr = hlen;		/* Where to start from */

	state->offset = (ntohs(iph->frag_off) & IP_OFFSET) << 3;
	state->not_last_frag = iph->frag_off & htons(IP_MF);
पूर्ण
EXPORT_SYMBOL(ip_frag_init);

अटल व्योम ip_frag_ipcb(काष्ठा sk_buff *from, काष्ठा sk_buff *to,
			 bool first_frag, काष्ठा ip_frag_state *state)
अणु
	/* Copy the flags to each fragment. */
	IPCB(to)->flags = IPCB(from)->flags;

	/* ANK: dirty, but effective trick. Upgrade options only अगर
	 * the segment to be fragmented was THE FIRST (otherwise,
	 * options are alपढ़ोy fixed) and make it ONCE
	 * on the initial skb, so that all the following fragments
	 * will inherit fixed options.
	 */
	अगर (first_frag)
		ip_options_fragment(from);
पूर्ण

काष्ठा sk_buff *ip_frag_next(काष्ठा sk_buff *skb, काष्ठा ip_frag_state *state)
अणु
	अचिन्हित पूर्णांक len = state->left;
	काष्ठा sk_buff *skb2;
	काष्ठा iphdr *iph;

	len = state->left;
	/* IF: it करोesn't fit, use 'mtu' - the data space left */
	अगर (len > state->mtu)
		len = state->mtu;
	/* IF: we are not sending up to and including the packet end
	   then align the next start on an eight byte boundary */
	अगर (len < state->left)	अणु
		len &= ~7;
	पूर्ण

	/* Allocate buffer */
	skb2 = alloc_skb(len + state->hlen + state->ll_rs, GFP_ATOMIC);
	अगर (!skb2)
		वापस ERR_PTR(-ENOMEM);

	/*
	 *	Set up data on packet
	 */

	ip_copy_metadata(skb2, skb);
	skb_reserve(skb2, state->ll_rs);
	skb_put(skb2, len + state->hlen);
	skb_reset_network_header(skb2);
	skb2->transport_header = skb2->network_header + state->hlen;

	/*
	 *	Charge the memory क्रम the fragment to any owner
	 *	it might possess
	 */

	अगर (skb->sk)
		skb_set_owner_w(skb2, skb->sk);

	/*
	 *	Copy the packet header पूर्णांकo the new buffer.
	 */

	skb_copy_from_linear_data(skb, skb_network_header(skb2), state->hlen);

	/*
	 *	Copy a block of the IP datagram.
	 */
	अगर (skb_copy_bits(skb, state->ptr, skb_transport_header(skb2), len))
		BUG();
	state->left -= len;

	/*
	 *	Fill in the new header fields.
	 */
	iph = ip_hdr(skb2);
	iph->frag_off = htons((state->offset >> 3));
	अगर (state->DF)
		iph->frag_off |= htons(IP_DF);

	/*
	 *	Added AC : If we are fragmenting a fragment that's not the
	 *		   last fragment then keep MF on each bit
	 */
	अगर (state->left > 0 || state->not_last_frag)
		iph->frag_off |= htons(IP_MF);
	state->ptr += len;
	state->offset += len;

	iph->tot_len = htons(len + state->hlen);

	ip_send_check(iph);

	वापस skb2;
पूर्ण
EXPORT_SYMBOL(ip_frag_next);

/*
 *	This IP datagram is too large to be sent in one piece.  Break it up पूर्णांकo
 *	smaller pieces (each of size equal to IP header plus
 *	a block of the data of the original IP data part) that will yet fit in a
 *	single device frame, and queue such a frame क्रम sending.
 */

पूर्णांक ip_करो_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		   पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	काष्ठा iphdr *iph;
	काष्ठा sk_buff *skb2;
	काष्ठा rtable *rt = skb_rtable(skb);
	अचिन्हित पूर्णांक mtu, hlen, ll_rs;
	काष्ठा ip_fraglist_iter iter;
	kसमय_प्रकार tstamp = skb->tstamp;
	काष्ठा ip_frag_state state;
	पूर्णांक err = 0;

	/* क्रम offloaded checksums cleanup checksum beक्रमe fragmentation */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (err = skb_checksum_help(skb)))
		जाओ fail;

	/*
	 *	Poपूर्णांक पूर्णांकo the IP datagram header.
	 */

	iph = ip_hdr(skb);

	mtu = ip_skb_dst_mtu(sk, skb);
	अगर (IPCB(skb)->frag_max_size && IPCB(skb)->frag_max_size < mtu)
		mtu = IPCB(skb)->frag_max_size;

	/*
	 *	Setup starting values.
	 */

	hlen = iph->ihl * 4;
	mtu = mtu - hlen;	/* Size of data space */
	IPCB(skb)->flags |= IPSKB_FRAG_COMPLETE;
	ll_rs = LL_RESERVED_SPACE(rt->dst.dev);

	/* When frag_list is given, use it. First, check its validity:
	 * some transक्रमmers could create wrong frag_list or अवरोध existing
	 * one, it is not prohibited. In this हाल fall back to copying.
	 *
	 * LATER: this step can be merged to real generation of fragments,
	 * we can चयन to copy when see the first bad fragment.
	 */
	अगर (skb_has_frag_list(skb)) अणु
		काष्ठा sk_buff *frag, *frag2;
		अचिन्हित पूर्णांक first_len = skb_pagelen(skb);

		अगर (first_len - hlen > mtu ||
		    ((first_len - hlen) & 7) ||
		    ip_is_fragment(iph) ||
		    skb_cloned(skb) ||
		    skb_headroom(skb) < ll_rs)
			जाओ slow_path;

		skb_walk_frags(skb, frag) अणु
			/* Correct geometry. */
			अगर (frag->len > mtu ||
			    ((frag->len & 7) && frag->next) ||
			    skb_headroom(frag) < hlen + ll_rs)
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

		/* Everything is OK. Generate! */
		ip_fraglist_init(skb, iph, hlen, &iter);

		क्रम (;;) अणु
			/* Prepare header of the next frame,
			 * beक्रमe previous one went करोwn. */
			अगर (iter.frag) अणु
				ip_fraglist_ipcb_prepare(skb, &iter);
				ip_fraglist_prepare(skb, &iter);
			पूर्ण

			skb->tstamp = tstamp;
			err = output(net, sk, skb);

			अगर (!err)
				IP_INC_STATS(net, IPSTATS_MIB_FRAGCREATES);
			अगर (err || !iter.frag)
				अवरोध;

			skb = ip_fraglist_next(&iter);
		पूर्ण

		अगर (err == 0) अणु
			IP_INC_STATS(net, IPSTATS_MIB_FRAGOKS);
			वापस 0;
		पूर्ण

		kमुक्त_skb_list(iter.frag);

		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
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

	ip_frag_init(skb, hlen, ll_rs, mtu, IPCB(skb)->flags & IPSKB_FRAG_PMTU,
		     &state);

	/*
	 *	Keep copying data until we run out.
	 */

	जबतक (state.left > 0) अणु
		bool first_frag = (state.offset == 0);

		skb2 = ip_frag_next(skb, &state);
		अगर (IS_ERR(skb2)) अणु
			err = PTR_ERR(skb2);
			जाओ fail;
		पूर्ण
		ip_frag_ipcb(skb, skb2, first_frag, &state);

		/*
		 *	Put this fragment पूर्णांकo the sending queue.
		 */
		skb2->tstamp = tstamp;
		err = output(net, sk, skb2);
		अगर (err)
			जाओ fail;

		IP_INC_STATS(net, IPSTATS_MIB_FRAGCREATES);
	पूर्ण
	consume_skb(skb);
	IP_INC_STATS(net, IPSTATS_MIB_FRAGOKS);
	वापस err;

fail:
	kमुक्त_skb(skb);
	IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ip_करो_fragment);

पूर्णांक
ip_generic_getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb)
अणु
	काष्ठा msghdr *msg = from;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (!copy_from_iter_full(to, len, &msg->msg_iter))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		__wsum csum = 0;
		अगर (!csum_and_copy_from_iter_full(to, len, &csum, &msg->msg_iter))
			वापस -EFAULT;
		skb->csum = csum_block_add(skb->csum, csum, odd);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip_generic_getfrag);

अटल अंतरभूत __wsum
csum_page(काष्ठा page *page, पूर्णांक offset, पूर्णांक copy)
अणु
	अक्षर *kaddr;
	__wsum csum;
	kaddr = kmap(page);
	csum = csum_partial(kaddr + offset, copy, 0);
	kunmap(page);
	वापस csum;
पूर्ण

अटल पूर्णांक __ip_append_data(काष्ठा sock *sk,
			    काष्ठा flowi4 *fl4,
			    काष्ठा sk_buff_head *queue,
			    काष्ठा inet_cork *cork,
			    काष्ठा page_frag *pfrag,
			    पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset,
					पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb),
			    व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
			    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ubuf_info *uarg = शून्य;
	काष्ठा sk_buff *skb;

	काष्ठा ip_options *opt = cork->opt;
	पूर्णांक hh_len;
	पूर्णांक exthdrlen;
	पूर्णांक mtu;
	पूर्णांक copy;
	पूर्णांक err;
	पूर्णांक offset = 0;
	अचिन्हित पूर्णांक maxfraglen, fragheaderlen, maxnonfragsize;
	पूर्णांक csummode = CHECKSUM_NONE;
	काष्ठा rtable *rt = (काष्ठा rtable *)cork->dst;
	अचिन्हित पूर्णांक wmem_alloc_delta = 0;
	bool paged, extra_uref = false;
	u32 tskey = 0;

	skb = skb_peek_tail(queue);

	exthdrlen = !skb ? rt->dst.header_len : 0;
	mtu = cork->gso_size ? IP_MAX_MTU : cork->fragsize;
	paged = !!cork->gso_size;

	अगर (cork->tx_flags & SKBTX_ANY_SW_TSTAMP &&
	    sk->sk_tsflags & SOF_TIMESTAMPING_OPT_ID)
		tskey = sk->sk_tskey++;

	hh_len = LL_RESERVED_SPACE(rt->dst.dev);

	fragheaderlen = माप(काष्ठा iphdr) + (opt ? opt->optlen : 0);
	maxfraglen = ((mtu - fragheaderlen) & ~7) + fragheaderlen;
	maxnonfragsize = ip_sk_ignore_df(sk) ? IP_MAX_MTU : mtu;

	अगर (cork->length + length > maxnonfragsize - fragheaderlen) अणु
		ip_local_error(sk, EMSGSIZE, fl4->daddr, inet->inet_dport,
			       mtu - (opt ? opt->optlen : 0));
		वापस -EMSGSIZE;
	पूर्ण

	/*
	 * transhdrlen > 0 means that this is the first fragment and we wish
	 * it won't be fragmented in the future.
	 */
	अगर (transhdrlen &&
	    length + fragheaderlen <= mtu &&
	    rt->dst.dev->features & (NETIF_F_HW_CSUM | NETIF_F_IP_CSUM) &&
	    (!(flags & MSG_MORE) || cork->gso_size) &&
	    (!exthdrlen || (rt->dst.dev->features & NETIF_F_HW_ESP_TX_CSUM)))
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

	cork->length += length;

	/* So, what's going on in the loop below?
	 *
	 * We use calculated fragment length to generate chained skb,
	 * each of segments is IP fragment पढ़ोy क्रम sending to network after
	 * adding appropriate IP header.
	 */

	अगर (!skb)
		जाओ alloc_new_skb;

	जबतक (length > 0) अणु
		/* Check अगर the reमुख्यing data fits पूर्णांकo current packet. */
		copy = mtu - skb->len;
		अगर (copy < length)
			copy = maxfraglen - skb->len;
		अगर (copy <= 0) अणु
			अक्षर *data;
			अचिन्हित पूर्णांक datalen;
			अचिन्हित पूर्णांक fraglen;
			अचिन्हित पूर्णांक fraggap;
			अचिन्हित पूर्णांक alloclen;
			अचिन्हित पूर्णांक pagedlen;
			काष्ठा sk_buff *skb_prev;
alloc_new_skb:
			skb_prev = skb;
			अगर (skb_prev)
				fraggap = skb_prev->len - maxfraglen;
			अन्यथा
				fraggap = 0;

			/*
			 * If reमुख्यing data exceeds the mtu,
			 * we know we need more fragment(s).
			 */
			datalen = length + fraggap;
			अगर (datalen > mtu - fragheaderlen)
				datalen = maxfraglen - fragheaderlen;
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

			alloclen += exthdrlen;

			/* The last fragment माला_लो additional space at tail.
			 * Note, with MSG_MORE we overallocate on fragments,
			 * because we have no idea what fragment will be
			 * the last.
			 */
			अगर (datalen == length + fraggap)
				alloclen += rt->dst.trailer_len;

			अगर (transhdrlen) अणु
				skb = sock_alloc_send_skb(sk,
						alloclen + hh_len + 15,
						(flags & MSG_DONTWAIT), &err);
			पूर्ण अन्यथा अणु
				skb = शून्य;
				अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) + wmem_alloc_delta <=
				    2 * sk->sk_sndbuf)
					skb = alloc_skb(alloclen + hh_len + 15,
							sk->sk_allocation);
				अगर (unlikely(!skb))
					err = -ENOBUFS;
			पूर्ण
			अगर (!skb)
				जाओ error;

			/*
			 *	Fill in the control काष्ठाures
			 */
			skb->ip_summed = csummode;
			skb->csum = 0;
			skb_reserve(skb, hh_len);

			/*
			 *	Find where to start putting bytes.
			 */
			data = skb_put(skb, fraglen + exthdrlen - pagedlen);
			skb_set_network_header(skb, exthdrlen);
			skb->transport_header = (skb->network_header +
						 fragheaderlen);
			data += fragheaderlen + exthdrlen;

			अगर (fraggap) अणु
				skb->csum = skb_copy_and_csum_bits(
					skb_prev, maxfraglen,
					data + transhdrlen, fraggap);
				skb_prev->csum = csum_sub(skb_prev->csum,
							  skb->csum);
				data += fraggap;
				pskb_trim_unique(skb_prev, maxfraglen);
			पूर्ण

			copy = datalen - transhdrlen - fraggap - pagedlen;
			अगर (copy > 0 && getfrag(from, data + transhdrlen, offset, copy, fraggap, skb) < 0) अणु
				err = -EFAULT;
				kमुक्त_skb(skb);
				जाओ error;
			पूर्ण

			offset += copy;
			length -= copy + transhdrlen;
			transhdrlen = 0;
			exthdrlen = 0;
			csummode = CHECKSUM_NONE;

			/* only the initial fragment is समय stamped */
			skb_shinfo(skb)->tx_flags = cork->tx_flags;
			cork->tx_flags = 0;
			skb_shinfo(skb)->tskey = tskey;
			tskey = 0;
			skb_zcopy_set(skb, uarg, &extra_uref);

			अगर ((flags & MSG_CONFIRM) && !skb_prev)
				skb_set_dst_pending_confirm(skb, 1);

			/*
			 * Put the packet on the pending queue.
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
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTDISCARDS);
	refcount_add(wmem_alloc_delta, &sk->sk_wmem_alloc);
	वापस err;
पूर्ण

अटल पूर्णांक ip_setup_cork(काष्ठा sock *sk, काष्ठा inet_cork *cork,
			 काष्ठा ipcm_cookie *ipc, काष्ठा rtable **rtp)
अणु
	काष्ठा ip_options_rcu *opt;
	काष्ठा rtable *rt;

	rt = *rtp;
	अगर (unlikely(!rt))
		वापस -EFAULT;

	/*
	 * setup क्रम corking.
	 */
	opt = ipc->opt;
	अगर (opt) अणु
		अगर (!cork->opt) अणु
			cork->opt = kदो_स्मृति(माप(काष्ठा ip_options) + 40,
					    sk->sk_allocation);
			अगर (unlikely(!cork->opt))
				वापस -ENOBUFS;
		पूर्ण
		स_नकल(cork->opt, &opt->opt, माप(काष्ठा ip_options) + opt->opt.optlen);
		cork->flags |= IPCORK_OPT;
		cork->addr = ipc->addr;
	पूर्ण

	cork->fragsize = ip_sk_use_pmtu(sk) ?
			 dst_mtu(&rt->dst) : READ_ONCE(rt->dst.dev->mtu);

	अगर (!inetdev_valid_mtu(cork->fragsize))
		वापस -ENETUNREACH;

	cork->gso_size = ipc->gso_size;

	cork->dst = &rt->dst;
	/* We stole this route, caller should not release it. */
	*rtp = शून्य;

	cork->length = 0;
	cork->ttl = ipc->ttl;
	cork->tos = ipc->tos;
	cork->mark = ipc->sockc.mark;
	cork->priority = ipc->priority;
	cork->transmit_समय = ipc->sockc.transmit_समय;
	cork->tx_flags = 0;
	sock_tx_बारtamp(sk, ipc->sockc.tsflags, &cork->tx_flags);

	वापस 0;
पूर्ण

/*
 *	ip_append_data() and ip_append_page() can make one large IP datagram
 *	from many pieces of data. Each pieces will be holded on the socket
 *	until ip_push_pending_frames() is called. Each piece can be a page
 *	or non-page data.
 *
 *	Not only UDP, other transport protocols - e.g. raw sockets - can use
 *	this पूर्णांकerface potentially.
 *
 *	LATER: length must be adjusted by pad at tail, when it is required.
 */
पूर्णांक ip_append_data(काष्ठा sock *sk, काष्ठा flowi4 *fl4,
		   पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len,
			       पूर्णांक odd, काष्ठा sk_buff *skb),
		   व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
		   काष्ठा ipcm_cookie *ipc, काष्ठा rtable **rtp,
		   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	पूर्णांक err;

	अगर (flags&MSG_PROBE)
		वापस 0;

	अगर (skb_queue_empty(&sk->sk_ग_लिखो_queue)) अणु
		err = ip_setup_cork(sk, &inet->cork.base, ipc, rtp);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		transhdrlen = 0;
	पूर्ण

	वापस __ip_append_data(sk, fl4, &sk->sk_ग_लिखो_queue, &inet->cork.base,
				sk_page_frag(sk), getfrag,
				from, length, transhdrlen, flags);
पूर्ण

sमाप_प्रकार	ip_append_page(काष्ठा sock *sk, काष्ठा flowi4 *fl4, काष्ठा page *page,
		       पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा rtable *rt;
	काष्ठा ip_options *opt = शून्य;
	काष्ठा inet_cork *cork;
	पूर्णांक hh_len;
	पूर्णांक mtu;
	पूर्णांक len;
	पूर्णांक err;
	अचिन्हित पूर्णांक maxfraglen, fragheaderlen, fraggap, maxnonfragsize;

	अगर (inet->hdrincl)
		वापस -EPERM;

	अगर (flags&MSG_PROBE)
		वापस 0;

	अगर (skb_queue_empty(&sk->sk_ग_लिखो_queue))
		वापस -EINVAL;

	cork = &inet->cork.base;
	rt = (काष्ठा rtable *)cork->dst;
	अगर (cork->flags & IPCORK_OPT)
		opt = cork->opt;

	अगर (!(rt->dst.dev->features & NETIF_F_SG))
		वापस -EOPNOTSUPP;

	hh_len = LL_RESERVED_SPACE(rt->dst.dev);
	mtu = cork->gso_size ? IP_MAX_MTU : cork->fragsize;

	fragheaderlen = माप(काष्ठा iphdr) + (opt ? opt->optlen : 0);
	maxfraglen = ((mtu - fragheaderlen) & ~7) + fragheaderlen;
	maxnonfragsize = ip_sk_ignore_df(sk) ? 0xFFFF : mtu;

	अगर (cork->length + size > maxnonfragsize - fragheaderlen) अणु
		ip_local_error(sk, EMSGSIZE, fl4->daddr, inet->inet_dport,
			       mtu - (opt ? opt->optlen : 0));
		वापस -EMSGSIZE;
	पूर्ण

	skb = skb_peek_tail(&sk->sk_ग_लिखो_queue);
	अगर (!skb)
		वापस -EINVAL;

	cork->length += size;

	जबतक (size > 0) अणु
		/* Check अगर the reमुख्यing data fits पूर्णांकo current packet. */
		len = mtu - skb->len;
		अगर (len < size)
			len = maxfraglen - skb->len;

		अगर (len <= 0) अणु
			काष्ठा sk_buff *skb_prev;
			पूर्णांक alloclen;

			skb_prev = skb;
			fraggap = skb_prev->len - maxfraglen;

			alloclen = fragheaderlen + hh_len + fraggap + 15;
			skb = sock_wदो_स्मृति(sk, alloclen, 1, sk->sk_allocation);
			अगर (unlikely(!skb)) अणु
				err = -ENOBUFS;
				जाओ error;
			पूर्ण

			/*
			 *	Fill in the control काष्ठाures
			 */
			skb->ip_summed = CHECKSUM_NONE;
			skb->csum = 0;
			skb_reserve(skb, hh_len);

			/*
			 *	Find where to start putting bytes.
			 */
			skb_put(skb, fragheaderlen + fraggap);
			skb_reset_network_header(skb);
			skb->transport_header = (skb->network_header +
						 fragheaderlen);
			अगर (fraggap) अणु
				skb->csum = skb_copy_and_csum_bits(skb_prev,
								   maxfraglen,
						    skb_transport_header(skb),
								   fraggap);
				skb_prev->csum = csum_sub(skb_prev->csum,
							  skb->csum);
				pskb_trim_unique(skb_prev, maxfraglen);
			पूर्ण

			/*
			 * Put the packet on the pending queue.
			 */
			__skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
			जारी;
		पूर्ण

		अगर (len > size)
			len = size;

		अगर (skb_append_pagefrags(skb, page, offset, len)) अणु
			err = -EMSGSIZE;
			जाओ error;
		पूर्ण

		अगर (skb->ip_summed == CHECKSUM_NONE) अणु
			__wsum csum;
			csum = csum_page(page, offset, len);
			skb->csum = csum_block_add(skb->csum, csum, skb->len);
		पूर्ण

		skb->len += len;
		skb->data_len += len;
		skb->truesize += len;
		refcount_add(len, &sk->sk_wmem_alloc);
		offset += len;
		size -= len;
	पूर्ण
	वापस 0;

error:
	cork->length -= size;
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTDISCARDS);
	वापस err;
पूर्ण

अटल व्योम ip_cork_release(काष्ठा inet_cork *cork)
अणु
	cork->flags &= ~IPCORK_OPT;
	kमुक्त(cork->opt);
	cork->opt = शून्य;
	dst_release(cork->dst);
	cork->dst = शून्य;
पूर्ण

/*
 *	Combined all pending IP fragments on the socket as one IP datagram
 *	and push them out.
 */
काष्ठा sk_buff *__ip_make_skb(काष्ठा sock *sk,
			      काष्ठा flowi4 *fl4,
			      काष्ठा sk_buff_head *queue,
			      काष्ठा inet_cork *cork)
अणु
	काष्ठा sk_buff *skb, *पंचांगp_skb;
	काष्ठा sk_buff **tail_skb;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा ip_options *opt = शून्य;
	काष्ठा rtable *rt = (काष्ठा rtable *)cork->dst;
	काष्ठा iphdr *iph;
	__be16 df = 0;
	__u8 ttl;

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

	/* Unless user demanded real pmtu discovery (IP_PMTUDISC_DO), we allow
	 * to fragment the frame generated here. No matter, what transक्रमms
	 * how transक्रमms change size of the packet, it will come out.
	 */
	skb->ignore_df = ip_sk_ignore_df(sk);

	/* DF bit is set when we want to see DF on outgoing frames.
	 * If ignore_df is set too, we still allow to fragment this frame
	 * locally. */
	अगर (inet->pmtudisc == IP_PMTUDISC_DO ||
	    inet->pmtudisc == IP_PMTUDISC_PROBE ||
	    (skb->len <= dst_mtu(&rt->dst) &&
	     ip_करोnt_fragment(sk, &rt->dst)))
		df = htons(IP_DF);

	अगर (cork->flags & IPCORK_OPT)
		opt = cork->opt;

	अगर (cork->ttl != 0)
		ttl = cork->ttl;
	अन्यथा अगर (rt->rt_type == RTN_MULTICAST)
		ttl = inet->mc_ttl;
	अन्यथा
		ttl = ip_select_ttl(inet, &rt->dst);

	iph = ip_hdr(skb);
	iph->version = 4;
	iph->ihl = 5;
	iph->tos = (cork->tos != -1) ? cork->tos : inet->tos;
	iph->frag_off = df;
	iph->ttl = ttl;
	iph->protocol = sk->sk_protocol;
	ip_copy_addrs(iph, fl4);
	ip_select_ident(net, skb, sk);

	अगर (opt) अणु
		iph->ihl += opt->optlen >> 2;
		ip_options_build(skb, opt, cork->addr, rt, 0);
	पूर्ण

	skb->priority = (cork->tos != -1) ? cork->priority: sk->sk_priority;
	skb->mark = cork->mark;
	skb->tstamp = cork->transmit_समय;
	/*
	 * Steal rt from cork.dst to aव्योम a pair of atomic_inc/atomic_dec
	 * on dst refcount
	 */
	cork->dst = शून्य;
	skb_dst_set(skb, &rt->dst);

	अगर (iph->protocol == IPPROTO_ICMP)
		icmp_out_count(net, ((काष्ठा icmphdr *)
			skb_transport_header(skb))->type);

	ip_cork_release(cork);
out:
	वापस skb;
पूर्ण

पूर्णांक ip_send_skb(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = ip_local_out(net, skb->sk, skb);
	अगर (err) अणु
		अगर (err > 0)
			err = net_xmit_त्रुटि_सं(err);
		अगर (err)
			IP_INC_STATS(net, IPSTATS_MIB_OUTDISCARDS);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ip_push_pending_frames(काष्ठा sock *sk, काष्ठा flowi4 *fl4)
अणु
	काष्ठा sk_buff *skb;

	skb = ip_finish_skb(sk, fl4);
	अगर (!skb)
		वापस 0;

	/* Netfilter माला_लो whole the not fragmented skb. */
	वापस ip_send_skb(sock_net(sk), skb);
पूर्ण

/*
 *	Throw away all pending data on the socket.
 */
अटल व्योम __ip_flush_pending_frames(काष्ठा sock *sk,
				      काष्ठा sk_buff_head *queue,
				      काष्ठा inet_cork *cork)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue_tail(queue)) != शून्य)
		kमुक्त_skb(skb);

	ip_cork_release(cork);
पूर्ण

व्योम ip_flush_pending_frames(काष्ठा sock *sk)
अणु
	__ip_flush_pending_frames(sk, &sk->sk_ग_लिखो_queue, &inet_sk(sk)->cork.base);
पूर्ण

काष्ठा sk_buff *ip_make_skb(काष्ठा sock *sk,
			    काष्ठा flowi4 *fl4,
			    पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset,
					पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb),
			    व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
			    काष्ठा ipcm_cookie *ipc, काष्ठा rtable **rtp,
			    काष्ठा inet_cork *cork, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sk_buff_head queue;
	पूर्णांक err;

	अगर (flags & MSG_PROBE)
		वापस शून्य;

	__skb_queue_head_init(&queue);

	cork->flags = 0;
	cork->addr = 0;
	cork->opt = शून्य;
	err = ip_setup_cork(sk, cork, ipc, rtp);
	अगर (err)
		वापस ERR_PTR(err);

	err = __ip_append_data(sk, fl4, &queue, cork,
			       &current->task_frag, getfrag,
			       from, length, transhdrlen, flags);
	अगर (err) अणु
		__ip_flush_pending_frames(sk, &queue, cork);
		वापस ERR_PTR(err);
	पूर्ण

	वापस __ip_make_skb(sk, fl4, &queue, cork);
पूर्ण

/*
 *	Fetch data from kernel space and fill in checksum अगर needed.
 */
अटल पूर्णांक ip_reply_glue_bits(व्योम *dptr, अक्षर *to, पूर्णांक offset,
			      पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb)
अणु
	__wsum csum;

	csum = csum_partial_copy_nocheck(dptr+offset, to, len);
	skb->csum = csum_block_add(skb->csum, csum, odd);
	वापस 0;
पूर्ण

/*
 *	Generic function to send a packet as reply to another packet.
 *	Used to send some TCP resets/acks so far.
 */
व्योम ip_send_unicast_reply(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   स्थिर काष्ठा ip_options *sopt,
			   __be32 daddr, __be32 saddr,
			   स्थिर काष्ठा ip_reply_arg *arg,
			   अचिन्हित पूर्णांक len, u64 transmit_समय)
अणु
	काष्ठा ip_options_data replyopts;
	काष्ठा ipcm_cookie ipc;
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा net *net = sock_net(sk);
	काष्ठा sk_buff *nskb;
	पूर्णांक err;
	पूर्णांक oअगर;

	अगर (__ip_options_echo(net, &replyopts.opt.opt, skb, sopt))
		वापस;

	ipcm_init(&ipc);
	ipc.addr = daddr;
	ipc.sockc.transmit_समय = transmit_समय;

	अगर (replyopts.opt.opt.optlen) अणु
		ipc.opt = &replyopts.opt;

		अगर (replyopts.opt.opt.srr)
			daddr = replyopts.opt.opt.faddr;
	पूर्ण

	oअगर = arg->bound_dev_अगर;
	अगर (!oअगर && netअगर_index_is_l3_master(net, skb->skb_iअगर))
		oअगर = skb->skb_iअगर;

	flowi4_init_output(&fl4, oअगर,
			   IP4_REPLY_MARK(net, skb->mark) ?: sk->sk_mark,
			   RT_TOS(arg->tos),
			   RT_SCOPE_UNIVERSE, ip_hdr(skb)->protocol,
			   ip_reply_arg_flowi_flags(arg),
			   daddr, saddr,
			   tcp_hdr(skb)->source, tcp_hdr(skb)->dest,
			   arg->uid);
	security_skb_classअगरy_flow(skb, flowi4_to_flowi_common(&fl4));
	rt = ip_route_output_key(net, &fl4);
	अगर (IS_ERR(rt))
		वापस;

	inet_sk(sk)->tos = arg->tos & ~INET_ECN_MASK;

	sk->sk_protocol = ip_hdr(skb)->protocol;
	sk->sk_bound_dev_अगर = arg->bound_dev_अगर;
	sk->sk_sndbuf = sysctl_wmem_शेष;
	ipc.sockc.mark = fl4.flowi4_mark;
	err = ip_append_data(sk, &fl4, ip_reply_glue_bits, arg->iov->iov_base,
			     len, 0, &ipc, &rt, MSG_DONTWAIT);
	अगर (unlikely(err)) अणु
		ip_flush_pending_frames(sk);
		जाओ out;
	पूर्ण

	nskb = skb_peek(&sk->sk_ग_लिखो_queue);
	अगर (nskb) अणु
		अगर (arg->csumoffset >= 0)
			*((__sum16 *)skb_transport_header(nskb) +
			  arg->csumoffset) = csum_fold(csum_add(nskb->csum,
								arg->csum));
		nskb->ip_summed = CHECKSUM_NONE;
		ip_push_pending_frames(sk, &fl4);
	पूर्ण
out:
	ip_rt_put(rt);
पूर्ण

व्योम __init ip_init(व्योम)
अणु
	ip_rt_init();
	inet_initpeers();

#अगर defined(CONFIG_IP_MULTICAST)
	igmp_mc_init();
#पूर्ण_अगर
पूर्ण
