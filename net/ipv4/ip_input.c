<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The Internet Protocol (IP) module.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald Becker, <becker@super.org>
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *		Riअक्षरd Underwood
 *		Stefan Becker, <stefanb@yello.ping.de>
 *		Jorge Cwik, <jorge@laser.satlink.net>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *
 * Fixes:
 *		Alan Cox	:	Commented a couple of minor bits of surplus code
 *		Alan Cox	:	Undefining IP_FORWARD करोesn't include the code
 *					(just stops a compiler warning).
 *		Alan Cox	:	Frames with >=MAX_ROUTE record routes, strict routes or loose routes
 *					are junked rather than corrupting things.
 *		Alan Cox	:	Frames to bad broadcast subnets are dumped
 *					We used to process them non broadcast and
 *					boy could that cause havoc.
 *		Alan Cox	:	ip_क्रमward sets the मुक्त flag on the
 *					new frame it queues. Still crap because
 *					it copies the frame but at least it
 *					करोesn't eat memory too.
 *		Alan Cox	:	Generic queue code and memory fixes.
 *		Fred Van Kempen :	IP fragment support (borrowed from NET2E)
 *		Gerhard Koerting:	Forward fragmented frames correctly.
 *		Gerhard Koerting: 	Fixes to my fix of the above 8-).
 *		Gerhard Koerting:	IP पूर्णांकerface addressing fix.
 *		Linus Torvalds	:	More robustness checks
 *		Alan Cox	:	Even more checks: Still not as robust as it ought to be
 *		Alan Cox	:	Save IP header poपूर्णांकer क्रम later
 *		Alan Cox	:	ip option setting
 *		Alan Cox	:	Use ip_tos/ip_ttl settings
 *		Alan Cox	:	Fragmentation bogosity हटाओd
 *					(Thanks to Mark.Bush@prg.ox.ac.uk)
 *		Dmitry Gorodchanin :	Send of a raw packet crash fix.
 *		Alan Cox	:	Silly ip bug when an overlength
 *					fragment turns up. Now मुक्तs the
 *					queue.
 *		Linus Torvalds/ :	Memory leakage on fragmentation
 *		Alan Cox	:	handling.
 *		Gerhard Koerting:	Forwarding uses IP priority hपूर्णांकs
 *		Teemu Rantanen	:	Fragment problems.
 *		Alan Cox	:	General cleanup, comments and reक्रमmat
 *		Alan Cox	:	SNMP statistics
 *		Alan Cox	:	BSD address rule semantics. Also see
 *					UDP as there is a nasty checksum issue
 *					अगर you करो things the wrong way.
 *		Alan Cox	:	Always defrag, moved IP_FORWARD to the config.in file
 *		Alan Cox	: 	IP options adjust sk->priority.
 *		Pedro Roque	:	Fix mtu/length error in ip_क्रमward.
 *		Alan Cox	:	Aव्योम ip_chk_addr when possible.
 *	Riअक्षरd Underwood	:	IP multicasting.
 *		Alan Cox	:	Cleaned up multicast handlers.
 *		Alan Cox	:	RAW sockets demultiplex in the BSD style.
 *		Gunther Mayer	:	Fix the SNMP reporting typo
 *		Alan Cox	:	Always in group 224.0.0.1
 *	Pauline Middelink	:	Fast ip_checksum update when क्रमwarding
 *					Masquerading support.
 *		Alan Cox	:	Multicast loopback error क्रम 224.0.0.1
 *		Alan Cox	:	IP_MULTICAST_LOOP option.
 *		Alan Cox	:	Use notअगरiers.
 *		Bjorn Ekwall	:	Removed ip_csum (from slhc.c too)
 *		Bjorn Ekwall	:	Moved ip_fast_csum to ip.h (अंतरभूत!)
 *		Stefan Becker   :       Send out ICMP HOST REसूचीECT
 *	Arnt Gulbअक्रमsen	:	ip_build_xmit
 *		Alan Cox	:	Per socket routing cache
 *		Alan Cox	:	Fixed routing cache, added header cache.
 *		Alan Cox	:	Loopback didn't work right in original ip_build_xmit - fixed it.
 *		Alan Cox	:	Only send ICMP_REसूचीECT अगर src/dest are the same net.
 *		Alan Cox	:	Incoming IP option handling.
 *		Alan Cox	:	Set saddr on raw output frames as per BSD.
 *		Alan Cox	:	Stopped broadcast source route explosions.
 *		Alan Cox	:	Can disable source routing
 *		Takeshi Sone    :	Masquerading didn't work.
 *	Dave Bonn,Alan Cox	:	Faster IP क्रमwarding whenever possible.
 *		Alan Cox	:	Memory leaks, tramples, misc debugging.
 *		Alan Cox	:	Fixed multicast (by popular demand 8))
 *		Alan Cox	:	Fixed क्रमwarding (by even more popular demand 8))
 *		Alan Cox	:	Fixed SNMP statistics [I think]
 *	Gerhard Koerting	:	IP fragmentation क्रमwarding fix
 *		Alan Cox	:	Device lock against page fault.
 *		Alan Cox	:	IP_HDRINCL facility.
 *	Werner Almesberger	:	Zero fragment bug
 *		Alan Cox	:	RAW IP frame length bug
 *		Alan Cox	:	Outgoing firewall on build_xmit
 *		A.N.Kuznetsov	:	IP_OPTIONS support throughout the kernel
 *		Alan Cox	:	Multicast routing hooks
 *		Jos Vos		:	Do accounting *beक्रमe* call_in_firewall
 *	Willy Konynenberg	:	Transparent proxying support
 *
 * To Fix:
 *		IP fragmentation wants rewriting cleanly. The RFC815 algorithm is much more efficient
 *		and could be made very efficient with the addition of some भव memory hacks to permit
 *		the allocation of a buffer that can then be 'grown' by twiddling page tables.
 *		Output fragmentation wants updating aदीर्घ with the buffer management to use a single
 *		पूर्णांकerleaved copy algorithm so that fragmenting has a one copy overhead. Actual packet
 *		output should probably करो its own fragmentation at the UDP/RAW layer. TCP shouldn't cause
 *		fragmentation anyway.
 */

#घोषणा pr_fmt(fmt) "IPv4: " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश <linux/net.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/snmp.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/route.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/arp.h>
#समावेश <net/icmp.h>
#समावेश <net/raw.h>
#समावेश <net/checksum.h>
#समावेश <net/inet_ecn.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/xfrm.h>
#समावेश <linux/mroute.h>
#समावेश <linux/netlink.h>
#समावेश <net/dst_metadata.h>

/*
 *	Process Router Attention IP option (RFC 2113)
 */
bool ip_call_ra_chain(काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_ra_chain *ra;
	u8 protocol = ip_hdr(skb)->protocol;
	काष्ठा sock *last = शून्य;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा net *net = dev_net(dev);

	क्रम (ra = rcu_dereference(net->ipv4.ra_chain); ra; ra = rcu_dereference(ra->next)) अणु
		काष्ठा sock *sk = ra->sk;

		/* If socket is bound to an पूर्णांकerface, only report
		 * the packet अगर it came  from that पूर्णांकerface.
		 */
		अगर (sk && inet_sk(sk)->inet_num == protocol &&
		    (!sk->sk_bound_dev_अगर ||
		     sk->sk_bound_dev_अगर == dev->अगरindex)) अणु
			अगर (ip_is_fragment(ip_hdr(skb))) अणु
				अगर (ip_defrag(net, skb, IP_DEFRAG_CALL_RA_CHAIN))
					वापस true;
			पूर्ण
			अगर (last) अणु
				काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (skb2)
					raw_rcv(last, skb2);
			पूर्ण
			last = sk;
		पूर्ण
	पूर्ण

	अगर (last) अणु
		raw_rcv(last, skb);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक udp_rcv(काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक tcp_v4_rcv(काष्ठा sk_buff *));
व्योम ip_protocol_deliver_rcu(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक protocol)
अणु
	स्थिर काष्ठा net_protocol *ipprot;
	पूर्णांक raw, ret;

resubmit:
	raw = raw_local_deliver(skb, protocol);

	ipprot = rcu_dereference(inet_protos[protocol]);
	अगर (ipprot) अणु
		अगर (!ipprot->no_policy) अणु
			अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
				kमुक्त_skb(skb);
				वापस;
			पूर्ण
			nf_reset_ct(skb);
		पूर्ण
		ret = INसूचीECT_CALL_2(ipprot->handler, tcp_v4_rcv, udp_rcv,
				      skb);
		अगर (ret < 0) अणु
			protocol = -ret;
			जाओ resubmit;
		पूर्ण
		__IP_INC_STATS(net, IPSTATS_MIB_INDELIVERS);
	पूर्ण अन्यथा अणु
		अगर (!raw) अणु
			अगर (xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
				__IP_INC_STATS(net, IPSTATS_MIB_INUNKNOWNPROTOS);
				icmp_send(skb, ICMP_DEST_UNREACH,
					  ICMP_PROT_UNREACH, 0);
			पूर्ण
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			__IP_INC_STATS(net, IPSTATS_MIB_INDELIVERS);
			consume_skb(skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ip_local_deliver_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__skb_pull(skb, skb_network_header_len(skb));

	rcu_पढ़ो_lock();
	ip_protocol_deliver_rcu(net, skb, ip_hdr(skb)->protocol);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

/*
 * 	Deliver IP Packets to the higher protocol layers.
 */
पूर्णांक ip_local_deliver(काष्ठा sk_buff *skb)
अणु
	/*
	 *	Reassemble IP fragments.
	 */
	काष्ठा net *net = dev_net(skb->dev);

	अगर (ip_is_fragment(ip_hdr(skb))) अणु
		अगर (ip_defrag(net, skb, IP_DEFRAG_LOCAL_DELIVER))
			वापस 0;
	पूर्ण

	वापस NF_HOOK(NFPROTO_IPV4, NF_INET_LOCAL_IN,
		       net, शून्य, skb, skb->dev, शून्य,
		       ip_local_deliver_finish);
पूर्ण
EXPORT_SYMBOL(ip_local_deliver);

अटल अंतरभूत bool ip_rcv_options(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip_options *opt;
	स्थिर काष्ठा iphdr *iph;

	/* It looks as overसमाप्त, because not all
	   IP options require packet mangling.
	   But it is the easiest क्रम now, especially taking
	   पूर्णांकo account that combination of IP options
	   and running snअगरfer is extremely rare condition.
					      --ANK (980813)
	*/
	अगर (skb_cow(skb, skb_headroom(skb))) अणु
		__IP_INC_STATS(dev_net(dev), IPSTATS_MIB_INDISCARDS);
		जाओ drop;
	पूर्ण

	iph = ip_hdr(skb);
	opt = &(IPCB(skb)->opt);
	opt->optlen = iph->ihl*4 - माप(काष्ठा iphdr);

	अगर (ip_options_compile(dev_net(dev), opt, skb)) अणु
		__IP_INC_STATS(dev_net(dev), IPSTATS_MIB_INHDRERRORS);
		जाओ drop;
	पूर्ण

	अगर (unlikely(opt->srr)) अणु
		काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);

		अगर (in_dev) अणु
			अगर (!IN_DEV_SOURCE_ROUTE(in_dev)) अणु
				अगर (IN_DEV_LOG_MARTIANS(in_dev))
					net_info_ratelimited("source route option %pI4 -> %pI4\n",
							     &iph->saddr,
							     &iph->daddr);
				जाओ drop;
			पूर्ण
		पूर्ण

		अगर (ip_options_rcv_srr(skb, dev))
			जाओ drop;
	पूर्ण

	वापस false;
drop:
	वापस true;
पूर्ण

अटल bool ip_can_use_hपूर्णांक(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा iphdr *iph,
			    स्थिर काष्ठा sk_buff *hपूर्णांक)
अणु
	वापस hपूर्णांक && !skb_dst(skb) && ip_hdr(hपूर्णांक)->daddr == iph->daddr &&
	       ip_hdr(hपूर्णांक)->tos == iph->tos;
पूर्ण

INसूचीECT_CALLABLE_DECLARE(पूर्णांक udp_v4_early_demux(काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक tcp_v4_early_demux(काष्ठा sk_buff *));
अटल पूर्णांक ip_rcv_finish_core(काष्ठा net *net, काष्ठा sock *sk,
			      काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			      स्थिर काष्ठा sk_buff *hपूर्णांक)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	पूर्णांक (*edemux)(काष्ठा sk_buff *skb);
	काष्ठा rtable *rt;
	पूर्णांक err;

	अगर (ip_can_use_hपूर्णांक(skb, iph, hपूर्णांक)) अणु
		err = ip_route_use_hपूर्णांक(skb, iph->daddr, iph->saddr, iph->tos,
					dev, hपूर्णांक);
		अगर (unlikely(err))
			जाओ drop_error;
	पूर्ण

	अगर (net->ipv4.sysctl_ip_early_demux &&
	    !skb_dst(skb) &&
	    !skb->sk &&
	    !ip_is_fragment(iph)) अणु
		स्थिर काष्ठा net_protocol *ipprot;
		पूर्णांक protocol = iph->protocol;

		ipprot = rcu_dereference(inet_protos[protocol]);
		अगर (ipprot && (edemux = READ_ONCE(ipprot->early_demux))) अणु
			err = INसूचीECT_CALL_2(edemux, tcp_v4_early_demux,
					      udp_v4_early_demux, skb);
			अगर (unlikely(err))
				जाओ drop_error;
			/* must reload iph, skb->head might have changed */
			iph = ip_hdr(skb);
		पूर्ण
	पूर्ण

	/*
	 *	Initialise the भव path cache क्रम the packet. It describes
	 *	how the packet travels inside Linux networking.
	 */
	अगर (!skb_valid_dst(skb)) अणु
		err = ip_route_input_noref(skb, iph->daddr, iph->saddr,
					   iph->tos, dev);
		अगर (unlikely(err))
			जाओ drop_error;
	पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (unlikely(skb_dst(skb)->tclassid)) अणु
		काष्ठा ip_rt_acct *st = this_cpu_ptr(ip_rt_acct);
		u32 idx = skb_dst(skb)->tclassid;
		st[idx&0xFF].o_packets++;
		st[idx&0xFF].o_bytes += skb->len;
		st[(idx>>16)&0xFF].i_packets++;
		st[(idx>>16)&0xFF].i_bytes += skb->len;
	पूर्ण
#पूर्ण_अगर

	अगर (iph->ihl > 5 && ip_rcv_options(skb, dev))
		जाओ drop;

	rt = skb_rtable(skb);
	अगर (rt->rt_type == RTN_MULTICAST) अणु
		__IP_UPD_PO_STATS(net, IPSTATS_MIB_INMCAST, skb->len);
	पूर्ण अन्यथा अगर (rt->rt_type == RTN_BROADCAST) अणु
		__IP_UPD_PO_STATS(net, IPSTATS_MIB_INBCAST, skb->len);
	पूर्ण अन्यथा अगर (skb->pkt_type == PACKET_BROADCAST ||
		   skb->pkt_type == PACKET_MULTICAST) अणु
		काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);

		/* RFC 1122 3.3.6:
		 *
		 *   When a host sends a datagram to a link-layer broadcast
		 *   address, the IP destination address MUST be a legal IP
		 *   broadcast or IP multicast address.
		 *
		 *   A host SHOULD silently discard a datagram that is received
		 *   via a link-layer broadcast (see Section 2.4) but करोes not
		 *   specअगरy an IP multicast or broadcast destination address.
		 *
		 * This करोesn't explicitly say L2 *broadcast*, but broadcast is
		 * in a way a क्रमm of multicast and the most common use हाल क्रम
		 * this is 802.11 protecting against cross-station spoofing (the
		 * so-called "hole-196" attack) so करो it क्रम both.
		 */
		अगर (in_dev &&
		    IN_DEV_ORCONF(in_dev, DROP_UNICAST_IN_L2_MULTICAST))
			जाओ drop;
	पूर्ण

	वापस NET_RX_SUCCESS;

drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;

drop_error:
	अगर (err == -EXDEV)
		__NET_INC_STATS(net, LINUX_MIB_IPRPFILTER);
	जाओ drop;
पूर्ण

अटल पूर्णांक ip_rcv_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	पूर्णांक ret;

	/* अगर ingress device is enslaved to an L3 master device pass the
	 * skb to its handler क्रम processing
	 */
	skb = l3mdev_ip_rcv(skb);
	अगर (!skb)
		वापस NET_RX_SUCCESS;

	ret = ip_rcv_finish_core(net, sk, skb, dev, शून्य);
	अगर (ret != NET_RX_DROP)
		ret = dst_input(skb);
	वापस ret;
पूर्ण

/*
 * 	Main IP Receive routine.
 */
अटल काष्ठा sk_buff *ip_rcv_core(काष्ठा sk_buff *skb, काष्ठा net *net)
अणु
	स्थिर काष्ठा iphdr *iph;
	u32 len;

	/* When the पूर्णांकerface is in promisc. mode, drop all the crap
	 * that it receives, करो not try to analyse it.
	 */
	अगर (skb->pkt_type == PACKET_OTHERHOST)
		जाओ drop;

	__IP_UPD_PO_STATS(net, IPSTATS_MIB_IN, skb->len);

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		__IP_INC_STATS(net, IPSTATS_MIB_INDISCARDS);
		जाओ out;
	पूर्ण

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ inhdr_error;

	iph = ip_hdr(skb);

	/*
	 *	RFC1122: 3.2.1.2 MUST silently discard any IP frame that fails the checksum.
	 *
	 *	Is the datagram acceptable?
	 *
	 *	1.	Length at least the size of an ip header
	 *	2.	Version of 4
	 *	3.	Checksums correctly. [Speed optimisation क्रम later, skip loopback checksums]
	 *	4.	Doesn't have a bogus length
	 */

	अगर (iph->ihl < 5 || iph->version != 4)
		जाओ inhdr_error;

	BUILD_BUG_ON(IPSTATS_MIB_ECT1PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_1);
	BUILD_BUG_ON(IPSTATS_MIB_ECT0PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_0);
	BUILD_BUG_ON(IPSTATS_MIB_CEPKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_CE);
	__IP_ADD_STATS(net,
		       IPSTATS_MIB_NOECTPKTS + (iph->tos & INET_ECN_MASK),
		       max_t(अचिन्हित लघु, 1, skb_shinfo(skb)->gso_segs));

	अगर (!pskb_may_pull(skb, iph->ihl*4))
		जाओ inhdr_error;

	iph = ip_hdr(skb);

	अगर (unlikely(ip_fast_csum((u8 *)iph, iph->ihl)))
		जाओ csum_error;

	len = ntohs(iph->tot_len);
	अगर (skb->len < len) अणु
		__IP_INC_STATS(net, IPSTATS_MIB_INTRUNCATEDPKTS);
		जाओ drop;
	पूर्ण अन्यथा अगर (len < (iph->ihl*4))
		जाओ inhdr_error;

	/* Our transport medium may have padded the buffer out. Now we know it
	 * is IP we can trim to the true length of the frame.
	 * Note this now means skb->len holds ntohs(iph->tot_len).
	 */
	अगर (pskb_trim_rcsum(skb, len)) अणु
		__IP_INC_STATS(net, IPSTATS_MIB_INDISCARDS);
		जाओ drop;
	पूर्ण

	iph = ip_hdr(skb);
	skb->transport_header = skb->network_header + iph->ihl*4;

	/* Remove any debris in the socket control block */
	स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
	IPCB(skb)->iअगर = skb->skb_iअगर;

	/* Must drop socket now because of tproxy. */
	अगर (!skb_sk_is_prefetched(skb))
		skb_orphan(skb);

	वापस skb;

csum_error:
	__IP_INC_STATS(net, IPSTATS_MIB_CSUMERRORS);
inhdr_error:
	__IP_INC_STATS(net, IPSTATS_MIB_INHDRERRORS);
drop:
	kमुक्त_skb(skb);
out:
	वापस शून्य;
पूर्ण

/*
 * IP receive entry poपूर्णांक
 */
पूर्णांक ip_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt,
	   काष्ठा net_device *orig_dev)
अणु
	काष्ठा net *net = dev_net(dev);

	skb = ip_rcv_core(skb, net);
	अगर (skb == शून्य)
		वापस NET_RX_DROP;

	वापस NF_HOOK(NFPROTO_IPV4, NF_INET_PRE_ROUTING,
		       net, शून्य, skb, dev, शून्य,
		       ip_rcv_finish);
पूर्ण

अटल व्योम ip_sublist_rcv_finish(काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *skb, *next;

	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		skb_list_del_init(skb);
		dst_input(skb);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *ip_extract_route_hपूर्णांक(स्थिर काष्ठा net *net,
					     काष्ठा sk_buff *skb, पूर्णांक rt_type)
अणु
	अगर (fib4_has_custom_rules(net) || rt_type == RTN_BROADCAST)
		वापस शून्य;

	वापस skb;
पूर्ण

अटल व्योम ip_list_rcv_finish(काष्ठा net *net, काष्ठा sock *sk,
			       काष्ठा list_head *head)
अणु
	काष्ठा sk_buff *skb, *next, *hपूर्णांक = शून्य;
	काष्ठा dst_entry *curr_dst = शून्य;
	काष्ठा list_head sublist;

	INIT_LIST_HEAD(&sublist);
	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		काष्ठा net_device *dev = skb->dev;
		काष्ठा dst_entry *dst;

		skb_list_del_init(skb);
		/* अगर ingress device is enslaved to an L3 master device pass the
		 * skb to its handler क्रम processing
		 */
		skb = l3mdev_ip_rcv(skb);
		अगर (!skb)
			जारी;
		अगर (ip_rcv_finish_core(net, sk, skb, dev, hपूर्णांक) == NET_RX_DROP)
			जारी;

		dst = skb_dst(skb);
		अगर (curr_dst != dst) अणु
			hपूर्णांक = ip_extract_route_hपूर्णांक(net, skb,
					       ((काष्ठा rtable *)dst)->rt_type);

			/* dispatch old sublist */
			अगर (!list_empty(&sublist))
				ip_sublist_rcv_finish(&sublist);
			/* start new sublist */
			INIT_LIST_HEAD(&sublist);
			curr_dst = dst;
		पूर्ण
		list_add_tail(&skb->list, &sublist);
	पूर्ण
	/* dispatch final sublist */
	ip_sublist_rcv_finish(&sublist);
पूर्ण

अटल व्योम ip_sublist_rcv(काष्ठा list_head *head, काष्ठा net_device *dev,
			   काष्ठा net *net)
अणु
	NF_HOOK_LIST(NFPROTO_IPV4, NF_INET_PRE_ROUTING, net, शून्य,
		     head, dev, शून्य, ip_rcv_finish);
	ip_list_rcv_finish(net, शून्य, head);
पूर्ण

/* Receive a list of IP packets */
व्योम ip_list_rcv(काष्ठा list_head *head, काष्ठा packet_type *pt,
		 काष्ठा net_device *orig_dev)
अणु
	काष्ठा net_device *curr_dev = शून्य;
	काष्ठा net *curr_net = शून्य;
	काष्ठा sk_buff *skb, *next;
	काष्ठा list_head sublist;

	INIT_LIST_HEAD(&sublist);
	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		काष्ठा net_device *dev = skb->dev;
		काष्ठा net *net = dev_net(dev);

		skb_list_del_init(skb);
		skb = ip_rcv_core(skb, net);
		अगर (skb == शून्य)
			जारी;

		अगर (curr_dev != dev || curr_net != net) अणु
			/* dispatch old sublist */
			अगर (!list_empty(&sublist))
				ip_sublist_rcv(&sublist, curr_dev, curr_net);
			/* start new sublist */
			INIT_LIST_HEAD(&sublist);
			curr_dev = dev;
			curr_net = net;
		पूर्ण
		list_add_tail(&skb->list, &sublist);
	पूर्ण
	/* dispatch final sublist */
	अगर (!list_empty(&sublist))
		ip_sublist_rcv(&sublist, curr_dev, curr_net);
पूर्ण
