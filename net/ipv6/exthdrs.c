<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Extension Header handling क्रम IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Andi Kleen		<ak@muc.de>
 *	Alexey Kuznetsov	<kuznet@ms2.inr.ac.ru>
 */

/* Changes:
 *	yoshfuji		: ensure not to overrun जबतक parsing
 *				  tlv options.
 *	Mitsuru KANDA @USAGI and: Remove ipv6_parse_exthdrs().
 *	YOSHIFUJI Hideaki @USAGI  Register inbound extension header
 *				  handlers as inet6_protocolअणुपूर्ण.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <net/dst.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/rawv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/calipso.h>
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
#समावेश <net/xfrm.h>
#पूर्ण_अगर
#समावेश <linux/seg6.h>
#समावेश <net/seg6.h>
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
#समावेश <net/seg6_hmac.h>
#पूर्ण_अगर
#समावेश <net/rpl.h>

#समावेश <linux/uaccess.h>

/*
 *	Parsing tlv encoded headers.
 *
 *	Parsing function "func" वापसs true, अगर parsing succeed
 *	and false, अगर it failed.
 *	It MUST NOT touch skb->h.
 */

काष्ठा tlvtype_proc अणु
	पूर्णांक	type;
	bool	(*func)(काष्ठा sk_buff *skb, पूर्णांक offset);
पूर्ण;

/*********************
  Generic functions
 *********************/

/* An unknown option is detected, decide what to करो */

अटल bool ip6_tlvopt_unknown(काष्ठा sk_buff *skb, पूर्णांक optoff,
			       bool disallow_unknowns)
अणु
	अगर (disallow_unknowns) अणु
		/* If unknown TLVs are disallowed by configuration
		 * then always silently drop packet. Note this also
		 * means no ICMP parameter problem is sent which
		 * could be a good property to mitigate a reflection DOS
		 * attack.
		 */

		जाओ drop;
	पूर्ण

	चयन ((skb_network_header(skb)[optoff] & 0xC0) >> 6) अणु
	हाल 0: /* ignore */
		वापस true;

	हाल 1: /* drop packet */
		अवरोध;

	हाल 3: /* Send ICMP अगर not a multicast address and drop packet */
		/* Actually, it is redundant check. icmp_send
		   will recheck in any हाल.
		 */
		अगर (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr))
			अवरोध;
		fallthrough;
	हाल 2: /* send ICMP PARM PROB regardless and drop packet */
		icmpv6_param_prob(skb, ICMPV6_UNK_OPTION, optoff);
		वापस false;
	पूर्ण

drop:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

/* Parse tlv encoded option header (hop-by-hop or destination) */

अटल bool ip6_parse_tlv(स्थिर काष्ठा tlvtype_proc *procs,
			  काष्ठा sk_buff *skb,
			  पूर्णांक max_count)
अणु
	पूर्णांक len = (skb_transport_header(skb)[1] + 1) << 3;
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	पूर्णांक off = skb_network_header_len(skb);
	स्थिर काष्ठा tlvtype_proc *curr;
	bool disallow_unknowns = false;
	पूर्णांक tlv_count = 0;
	पूर्णांक padlen = 0;

	अगर (unlikely(max_count < 0)) अणु
		disallow_unknowns = true;
		max_count = -max_count;
	पूर्ण

	अगर (skb_transport_offset(skb) + len > skb_headlen(skb))
		जाओ bad;

	off += 2;
	len -= 2;

	जबतक (len > 0) अणु
		पूर्णांक optlen = nh[off + 1] + 2;
		पूर्णांक i;

		चयन (nh[off]) अणु
		हाल IPV6_TLV_PAD1:
			optlen = 1;
			padlen++;
			अगर (padlen > 7)
				जाओ bad;
			अवरोध;

		हाल IPV6_TLV_PADN:
			/* RFC 2460 states that the purpose of PadN is
			 * to align the containing header to multiples
			 * of 8. 7 is thereक्रमe the highest valid value.
			 * See also RFC 4942, Section 2.1.9.5.
			 */
			padlen += optlen;
			अगर (padlen > 7)
				जाओ bad;
			/* RFC 4942 recommends receiving hosts to
			 * actively check PadN payload to contain
			 * only zeroes.
			 */
			क्रम (i = 2; i < optlen; i++) अणु
				अगर (nh[off + i] != 0)
					जाओ bad;
			पूर्ण
			अवरोध;

		शेष: /* Other TLV code so scan list */
			अगर (optlen > len)
				जाओ bad;

			tlv_count++;
			अगर (tlv_count > max_count)
				जाओ bad;

			क्रम (curr = procs; curr->type >= 0; curr++) अणु
				अगर (curr->type == nh[off]) अणु
					/* type specअगरic length/alignment
					   checks will be perक्रमmed in the
					   func(). */
					अगर (curr->func(skb, off) == false)
						वापस false;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (curr->type < 0 &&
			    !ip6_tlvopt_unknown(skb, off, disallow_unknowns))
				वापस false;

			padlen = 0;
			अवरोध;
		पूर्ण
		off += optlen;
		len -= optlen;
	पूर्ण

	अगर (len == 0)
		वापस true;
bad:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

/*****************************
  Destination options header.
 *****************************/

#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
अटल bool ipv6_dest_hao(काष्ठा sk_buff *skb, पूर्णांक optoff)
अणु
	काष्ठा ipv6_destopt_hao *hao;
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	पूर्णांक ret;

	अगर (opt->dsthao) अणु
		net_dbg_ratelimited("hao duplicated\n");
		जाओ discard;
	पूर्ण
	opt->dsthao = opt->dst1;
	opt->dst1 = 0;

	hao = (काष्ठा ipv6_destopt_hao *)(skb_network_header(skb) + optoff);

	अगर (hao->length != 16) अणु
		net_dbg_ratelimited("hao invalid option length = %d\n",
				    hao->length);
		जाओ discard;
	पूर्ण

	अगर (!(ipv6_addr_type(&hao->addr) & IPV6_ADDR_UNICAST)) अणु
		net_dbg_ratelimited("hao is not an unicast addr: %pI6\n",
				    &hao->addr);
		जाओ discard;
	पूर्ण

	ret = xfrm6_input_addr(skb, (xfrm_address_t *)&ipv6h->daddr,
			       (xfrm_address_t *)&hao->addr, IPPROTO_DSTOPTS);
	अगर (unlikely(ret < 0))
		जाओ discard;

	अगर (skb_cloned(skb)) अणु
		अगर (pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
			जाओ discard;

		/* update all variable using below by copied skbuff */
		hao = (काष्ठा ipv6_destopt_hao *)(skb_network_header(skb) +
						  optoff);
		ipv6h = ipv6_hdr(skb);
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;

	swap(ipv6h->saddr, hao->addr);

	अगर (skb->tstamp == 0)
		__net_बारtamp(skb);

	वापस true;

 discard:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा tlvtype_proc tlvprocdestopt_lst[] = अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	अणु
		.type	= IPV6_TLV_HAO,
		.func	= ipv6_dest_hao,
	पूर्ण,
#पूर्ण_अगर
	अणु-1,			शून्यपूर्ण
पूर्ण;

अटल पूर्णांक ipv6_destopt_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(skb->dev);
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	__u16 dstbuf;
#पूर्ण_अगर
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक extlen;

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + 8) ||
	    !pskb_may_pull(skb, (skb_transport_offset(skb) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) अणु
		__IP6_INC_STATS(dev_net(dst->dev), idev,
				IPSTATS_MIB_INHDRERRORS);
fail_and_मुक्त:
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	extlen = (skb_transport_header(skb)[1] + 1) << 3;
	अगर (extlen > net->ipv6.sysctl.max_dst_opts_len)
		जाओ fail_and_मुक्त;

	opt->lastopt = opt->dst1 = skb_network_header_len(skb);
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	dstbuf = opt->dst1;
#पूर्ण_अगर

	अगर (ip6_parse_tlv(tlvprocdestopt_lst, skb,
			  init_net.ipv6.sysctl.max_dst_opts_cnt)) अणु
		skb->transport_header += extlen;
		opt = IP6CB(skb);
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		opt->nhoff = dstbuf;
#अन्यथा
		opt->nhoff = opt->dst1;
#पूर्ण_अगर
		वापस 1;
	पूर्ण

	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
	वापस -1;
पूर्ण

अटल व्योम seg6_update_csum(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_sr_hdr *hdr;
	काष्ठा in6_addr *addr;
	__be32 from, to;

	/* srh is at transport offset and seg_left is alपढ़ोy decremented
	 * but daddr is not yet updated with next segment
	 */

	hdr = (काष्ठा ipv6_sr_hdr *)skb_transport_header(skb);
	addr = hdr->segments + hdr->segments_left;

	hdr->segments_left++;
	from = *(__be32 *)hdr;

	hdr->segments_left--;
	to = *(__be32 *)hdr;

	/* update skb csum with dअगरf resulting from seg_left decrement */

	update_csum_dअगरf4(skb, from, to);

	/* compute csum dअगरf between current and next segment and update */

	update_csum_dअगरf16(skb, (__be32 *)(&ipv6_hdr(skb)->daddr),
			   (__be32 *)addr);
पूर्ण

अटल पूर्णांक ipv6_srh_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ipv6_sr_hdr *hdr;
	काष्ठा inet6_dev *idev;
	काष्ठा in6_addr *addr;
	पूर्णांक accept_seg6;

	hdr = (काष्ठा ipv6_sr_hdr *)skb_transport_header(skb);

	idev = __in6_dev_get(skb->dev);

	accept_seg6 = net->ipv6.devconf_all->seg6_enabled;
	अगर (accept_seg6 > idev->cnf.seg6_enabled)
		accept_seg6 = idev->cnf.seg6_enabled;

	अगर (!accept_seg6) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अगर (!seg6_hmac_validate_skb(skb)) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण
#पूर्ण_अगर

looped_back:
	अगर (hdr->segments_left == 0) अणु
		अगर (hdr->nexthdr == NEXTHDR_IPV6 || hdr->nexthdr == NEXTHDR_IPV4) अणु
			पूर्णांक offset = (hdr->hdrlen + 1) << 3;

			skb_postpull_rcsum(skb, skb_network_header(skb),
					   skb_network_header_len(skb));

			अगर (!pskb_pull(skb, offset)) अणु
				kमुक्त_skb(skb);
				वापस -1;
			पूर्ण
			skb_postpull_rcsum(skb, skb_transport_header(skb),
					   offset);

			skb_reset_network_header(skb);
			skb_reset_transport_header(skb);
			skb->encapsulation = 0;
			अगर (hdr->nexthdr == NEXTHDR_IPV4)
				skb->protocol = htons(ETH_P_IP);
			__skb_tunnel_rx(skb, skb->dev, net);

			netअगर_rx(skb);
			वापस -1;
		पूर्ण

		opt->srcrt = skb_network_header_len(skb);
		opt->lastopt = opt->srcrt;
		skb->transport_header += (hdr->hdrlen + 1) << 3;
		opt->nhoff = (&hdr->nexthdr) - skb_network_header(skb);

		वापस 1;
	पूर्ण

	अगर (hdr->segments_left >= (hdr->hdrlen >> 1)) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
				  ((&hdr->segments_left) -
				   skb_network_header(skb)));
		वापस -1;
	पूर्ण

	अगर (skb_cloned(skb)) अणु
		अगर (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) अणु
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
					IPSTATS_MIB_OUTDISCARDS);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
	पूर्ण

	hdr = (काष्ठा ipv6_sr_hdr *)skb_transport_header(skb);

	hdr->segments_left--;
	addr = hdr->segments + hdr->segments_left;

	skb_push(skb, माप(काष्ठा ipv6hdr));

	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		seg6_update_csum(skb);

	ipv6_hdr(skb)->daddr = *addr;

	skb_dst_drop(skb);

	ip6_route_input(skb);

	अगर (skb_dst(skb)->error) अणु
		dst_input(skb);
		वापस -1;
	पूर्ण

	अगर (skb_dst(skb)->dev->flags & IFF_LOOPBACK) अणु
		अगर (ipv6_hdr(skb)->hop_limit <= 1) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPLIMIT, 0);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		ipv6_hdr(skb)->hop_limit--;

		skb_pull(skb, माप(काष्ठा ipv6hdr));
		जाओ looped_back;
	पूर्ण

	dst_input(skb);

	वापस -1;
पूर्ण

अटल पूर्णांक ipv6_rpl_srh_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_rpl_sr_hdr *hdr, *ohdr, *chdr;
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा inet6_dev *idev;
	काष्ठा ipv6hdr *oldhdr;
	काष्ठा in6_addr addr;
	अचिन्हित अक्षर *buf;
	पूर्णांक accept_rpl_seg;
	पूर्णांक i, err;
	u64 n = 0;
	u32 r;

	idev = __in6_dev_get(skb->dev);

	accept_rpl_seg = net->ipv6.devconf_all->rpl_seg_enabled;
	अगर (accept_rpl_seg > idev->cnf.rpl_seg_enabled)
		accept_rpl_seg = idev->cnf.rpl_seg_enabled;

	अगर (!accept_rpl_seg) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

looped_back:
	hdr = (काष्ठा ipv6_rpl_sr_hdr *)skb_transport_header(skb);

	अगर (hdr->segments_left == 0) अणु
		अगर (hdr->nexthdr == NEXTHDR_IPV6) अणु
			पूर्णांक offset = (hdr->hdrlen + 1) << 3;

			skb_postpull_rcsum(skb, skb_network_header(skb),
					   skb_network_header_len(skb));

			अगर (!pskb_pull(skb, offset)) अणु
				kमुक्त_skb(skb);
				वापस -1;
			पूर्ण
			skb_postpull_rcsum(skb, skb_transport_header(skb),
					   offset);

			skb_reset_network_header(skb);
			skb_reset_transport_header(skb);
			skb->encapsulation = 0;

			__skb_tunnel_rx(skb, skb->dev, net);

			netअगर_rx(skb);
			वापस -1;
		पूर्ण

		opt->srcrt = skb_network_header_len(skb);
		opt->lastopt = opt->srcrt;
		skb->transport_header += (hdr->hdrlen + 1) << 3;
		opt->nhoff = (&hdr->nexthdr) - skb_network_header(skb);

		वापस 1;
	पूर्ण

	अगर (!pskb_may_pull(skb, माप(*hdr))) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	n = (hdr->hdrlen << 3) - hdr->pad - (16 - hdr->cmpre);
	r = करो_भाग(n, (16 - hdr->cmpri));
	/* checks अगर calculation was without reमुख्यder and n fits पूर्णांकo
	 * अचिन्हित अक्षर which is segments_left field. Should not be
	 * higher than that.
	 */
	अगर (r || (n + 1) > 255) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	अगर (hdr->segments_left > n + 1) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
				  ((&hdr->segments_left) -
				   skb_network_header(skb)));
		वापस -1;
	पूर्ण

	अगर (skb_cloned(skb)) अणु
		अगर (pskb_expand_head(skb, IPV6_RPL_SRH_WORST_SWAP_SIZE, 0,
				     GFP_ATOMIC)) अणु
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
					IPSTATS_MIB_OUTDISCARDS);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = skb_cow_head(skb, IPV6_RPL_SRH_WORST_SWAP_SIZE);
		अगर (unlikely(err)) अणु
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
	पूर्ण

	hdr = (काष्ठा ipv6_rpl_sr_hdr *)skb_transport_header(skb);

	अगर (!pskb_may_pull(skb, ipv6_rpl_srh_size(n, hdr->cmpri,
						  hdr->cmpre))) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	hdr->segments_left--;
	i = n - hdr->segments_left;

	buf = kसुस्मृति(काष्ठा_size(hdr, segments.addr, n + 2), 2, GFP_ATOMIC);
	अगर (unlikely(!buf)) अणु
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	ohdr = (काष्ठा ipv6_rpl_sr_hdr *)buf;
	ipv6_rpl_srh_decompress(ohdr, hdr, &ipv6_hdr(skb)->daddr, n);
	chdr = (काष्ठा ipv6_rpl_sr_hdr *)(buf + ((ohdr->hdrlen + 1) << 3));

	अगर ((ipv6_addr_type(&ipv6_hdr(skb)->daddr) & IPV6_ADDR_MULTICAST) ||
	    (ipv6_addr_type(&ohdr->rpl_segaddr[i]) & IPV6_ADDR_MULTICAST)) अणु
		kमुक्त_skb(skb);
		kमुक्त(buf);
		वापस -1;
	पूर्ण

	err = ipv6_chk_rpl_srh_loop(net, ohdr->rpl_segaddr, n + 1);
	अगर (err) अणु
		icmpv6_send(skb, ICMPV6_PARAMPROB, 0, 0);
		kमुक्त_skb(skb);
		kमुक्त(buf);
		वापस -1;
	पूर्ण

	addr = ipv6_hdr(skb)->daddr;
	ipv6_hdr(skb)->daddr = ohdr->rpl_segaddr[i];
	ohdr->rpl_segaddr[i] = addr;

	ipv6_rpl_srh_compress(chdr, ohdr, &ipv6_hdr(skb)->daddr, n);

	oldhdr = ipv6_hdr(skb);

	skb_pull(skb, ((hdr->hdrlen + 1) << 3));
	skb_postpull_rcsum(skb, oldhdr,
			   माप(काष्ठा ipv6hdr) + ((hdr->hdrlen + 1) << 3));
	skb_push(skb, ((chdr->hdrlen + 1) << 3) + माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	स_हटाओ(ipv6_hdr(skb), oldhdr, माप(काष्ठा ipv6hdr));
	स_नकल(skb_transport_header(skb), chdr, (chdr->hdrlen + 1) << 3);

	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_postpush_rcsum(skb, ipv6_hdr(skb),
			   माप(काष्ठा ipv6hdr) + ((chdr->hdrlen + 1) << 3));

	kमुक्त(buf);

	skb_dst_drop(skb);

	ip6_route_input(skb);

	अगर (skb_dst(skb)->error) अणु
		dst_input(skb);
		वापस -1;
	पूर्ण

	अगर (skb_dst(skb)->dev->flags & IFF_LOOPBACK) अणु
		अगर (ipv6_hdr(skb)->hop_limit <= 1) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPLIMIT, 0);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		ipv6_hdr(skb)->hop_limit--;

		skb_pull(skb, माप(काष्ठा ipv6hdr));
		जाओ looped_back;
	पूर्ण

	dst_input(skb);

	वापस -1;
पूर्ण

/********************************
  Routing header.
 ********************************/

/* called with rcu_पढ़ो_lock() */
अटल पूर्णांक ipv6_rthdr_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(skb->dev);
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	काष्ठा in6_addr *addr = शून्य;
	काष्ठा in6_addr daddr;
	पूर्णांक n, i;
	काष्ठा ipv6_rt_hdr *hdr;
	काष्ठा rt0_hdr *rthdr;
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक accept_source_route = net->ipv6.devconf_all->accept_source_route;

	idev = __in6_dev_get(skb->dev);
	अगर (idev && accept_source_route > idev->cnf.accept_source_route)
		accept_source_route = idev->cnf.accept_source_route;

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + 8) ||
	    !pskb_may_pull(skb, (skb_transport_offset(skb) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	hdr = (काष्ठा ipv6_rt_hdr *)skb_transport_header(skb);

	अगर (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) ||
	    skb->pkt_type != PACKET_HOST) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	चयन (hdr->type) अणु
	हाल IPV6_SRCRT_TYPE_4:
		/* segment routing */
		वापस ipv6_srh_rcv(skb);
	हाल IPV6_SRCRT_TYPE_3:
		/* rpl segment routing */
		वापस ipv6_rpl_srh_rcv(skb);
	शेष:
		अवरोध;
	पूर्ण

looped_back:
	अगर (hdr->segments_left == 0) अणु
		चयन (hdr->type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
		हाल IPV6_SRCRT_TYPE_2:
			/* Silently discard type 2 header unless it was
			 * processed by own
			 */
			अगर (!addr) अणु
				__IP6_INC_STATS(net, idev,
						IPSTATS_MIB_INADDRERRORS);
				kमुक्त_skb(skb);
				वापस -1;
			पूर्ण
			अवरोध;
#पूर्ण_अगर
		शेष:
			अवरोध;
		पूर्ण

		opt->lastopt = opt->srcrt = skb_network_header_len(skb);
		skb->transport_header += (hdr->hdrlen + 1) << 3;
		opt->dst0 = opt->dst1;
		opt->dst1 = 0;
		opt->nhoff = (&hdr->nexthdr) - skb_network_header(skb);
		वापस 1;
	पूर्ण

	चयन (hdr->type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	हाल IPV6_SRCRT_TYPE_2:
		अगर (accept_source_route < 0)
			जाओ unknown_rh;
		/* Silently discard invalid RTH type 2 */
		अगर (hdr->hdrlen != 2 || hdr->segments_left != 1) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		जाओ unknown_rh;
	पूर्ण

	/*
	 *	This is the routing header क्रमwarding algorithm from
	 *	RFC 2460, page 16.
	 */

	n = hdr->hdrlen >> 1;

	अगर (hdr->segments_left > n) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
				  ((&hdr->segments_left) -
				   skb_network_header(skb)));
		वापस -1;
	पूर्ण

	/* We are about to mangle packet header. Be careful!
	   Do not damage packets queued somewhere.
	 */
	अगर (skb_cloned(skb)) अणु
		/* the copy is a क्रमwarded packet */
		अगर (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) अणु
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
					IPSTATS_MIB_OUTDISCARDS);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		hdr = (काष्ठा ipv6_rt_hdr *)skb_transport_header(skb);
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;

	i = n - --hdr->segments_left;

	rthdr = (काष्ठा rt0_hdr *) hdr;
	addr = rthdr->addr;
	addr += i - 1;

	चयन (hdr->type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
	हाल IPV6_SRCRT_TYPE_2:
		अगर (xfrm6_input_addr(skb, (xfrm_address_t *)addr,
				     (xfrm_address_t *)&ipv6_hdr(skb)->saddr,
				     IPPROTO_ROUTING) < 0) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		अगर (!ipv6_chk_home_addr(dev_net(skb_dst(skb)->dev), addr)) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	अगर (ipv6_addr_is_multicast(addr)) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	daddr = *addr;
	*addr = ipv6_hdr(skb)->daddr;
	ipv6_hdr(skb)->daddr = daddr;

	skb_dst_drop(skb);
	ip6_route_input(skb);
	अगर (skb_dst(skb)->error) अणु
		skb_push(skb, skb->data - skb_network_header(skb));
		dst_input(skb);
		वापस -1;
	पूर्ण

	अगर (skb_dst(skb)->dev->flags&IFF_LOOPBACK) अणु
		अगर (ipv6_hdr(skb)->hop_limit <= 1) अणु
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT,
				    0);
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण
		ipv6_hdr(skb)->hop_limit--;
		जाओ looped_back;
	पूर्ण

	skb_push(skb, skb->data - skb_network_header(skb));
	dst_input(skb);
	वापस -1;

unknown_rh:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
	icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
			  (&hdr->type) - skb_network_header(skb));
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा inet6_protocol rthdr_protocol = अणु
	.handler	=	ipv6_rthdr_rcv,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol destopt_protocol = अणु
	.handler	=	ipv6_destopt_rcv,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

अटल स्थिर काष्ठा inet6_protocol nodata_protocol = अणु
	.handler	=	dst_discard,
	.flags		=	INET6_PROTO_NOPOLICY,
पूर्ण;

पूर्णांक __init ipv6_exthdrs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = inet6_add_protocol(&rthdr_protocol, IPPROTO_ROUTING);
	अगर (ret)
		जाओ out;

	ret = inet6_add_protocol(&destopt_protocol, IPPROTO_DSTOPTS);
	अगर (ret)
		जाओ out_rthdr;

	ret = inet6_add_protocol(&nodata_protocol, IPPROTO_NONE);
	अगर (ret)
		जाओ out_destopt;

out:
	वापस ret;
out_destopt:
	inet6_del_protocol(&destopt_protocol, IPPROTO_DSTOPTS);
out_rthdr:
	inet6_del_protocol(&rthdr_protocol, IPPROTO_ROUTING);
	जाओ out;
पूर्ण;

व्योम ipv6_exthdrs_निकास(व्योम)
अणु
	inet6_del_protocol(&nodata_protocol, IPPROTO_NONE);
	inet6_del_protocol(&destopt_protocol, IPPROTO_DSTOPTS);
	inet6_del_protocol(&rthdr_protocol, IPPROTO_ROUTING);
पूर्ण

/**********************************
  Hop-by-hop options.
 **********************************/

/*
 * Note: we cannot rely on skb_dst(skb) beक्रमe we assign it in ip6_route_input().
 */
अटल अंतरभूत काष्ठा net *ipv6_skb_net(काष्ठा sk_buff *skb)
अणु
	वापस skb_dst(skb) ? dev_net(skb_dst(skb)->dev) : dev_net(skb->dev);
पूर्ण

/* Router Alert as of RFC 2711 */

अटल bool ipv6_hop_ra(काष्ठा sk_buff *skb, पूर्णांक optoff)
अणु
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);

	अगर (nh[optoff + 1] == 2) अणु
		IP6CB(skb)->flags |= IP6SKB_ROUTERALERT;
		स_नकल(&IP6CB(skb)->ra, nh + optoff + 2, माप(IP6CB(skb)->ra));
		वापस true;
	पूर्ण
	net_dbg_ratelimited("ipv6_hop_ra: wrong RA length %d\n",
			    nh[optoff + 1]);
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

/* Jumbo payload */

अटल bool ipv6_hop_jumbo(काष्ठा sk_buff *skb, पूर्णांक optoff)
अणु
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	काष्ठा inet6_dev *idev = __in6_dev_get_safely(skb->dev);
	काष्ठा net *net = ipv6_skb_net(skb);
	u32 pkt_len;

	अगर (nh[optoff + 1] != 4 || (optoff & 3) != 2) अणु
		net_dbg_ratelimited("ipv6_hop_jumbo: wrong jumbo opt length/alignment %d\n",
				    nh[optoff+1]);
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		जाओ drop;
	पूर्ण

	pkt_len = ntohl(*(__be32 *)(nh + optoff + 2));
	अगर (pkt_len <= IPV6_MAXPLEN) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD, optoff+2);
		वापस false;
	पूर्ण
	अगर (ipv6_hdr(skb)->payload_len) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD, optoff);
		वापस false;
	पूर्ण

	अगर (pkt_len > skb->len - माप(काष्ठा ipv6hdr)) अणु
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INTRUNCATEDPKTS);
		जाओ drop;
	पूर्ण

	अगर (pskb_trim_rcsum(skb, pkt_len + माप(काष्ठा ipv6hdr)))
		जाओ drop;

	IP6CB(skb)->flags |= IP6SKB_JUMBOGRAM;
	वापस true;

drop:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

/* CALIPSO RFC 5570 */

अटल bool ipv6_hop_calipso(काष्ठा sk_buff *skb, पूर्णांक optoff)
अणु
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);

	अगर (nh[optoff + 1] < 8)
		जाओ drop;

	अगर (nh[optoff + 6] * 4 + 8 > nh[optoff + 1])
		जाओ drop;

	अगर (!calipso_validate(skb, nh + optoff))
		जाओ drop;

	वापस true;

drop:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

अटल स्थिर काष्ठा tlvtype_proc tlvprochopopt_lst[] = अणु
	अणु
		.type	= IPV6_TLV_ROUTERALERT,
		.func	= ipv6_hop_ra,
	पूर्ण,
	अणु
		.type	= IPV6_TLV_JUMBO,
		.func	= ipv6_hop_jumbo,
	पूर्ण,
	अणु
		.type	= IPV6_TLV_CALIPSO,
		.func	= ipv6_hop_calipso,
	पूर्ण,
	अणु -1, पूर्ण
पूर्ण;

पूर्णांक ipv6_parse_hopopts(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक extlen;

	/*
	 * skb_network_header(skb) is equal to skb->data, and
	 * skb_network_header_len(skb) is always equal to
	 * माप(काष्ठा ipv6hdr) by definition of
	 * hop-by-hop options.
	 */
	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr) + 8) ||
	    !pskb_may_pull(skb, (माप(काष्ठा ipv6hdr) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) अणु
fail_and_मुक्त:
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	extlen = (skb_transport_header(skb)[1] + 1) << 3;
	अगर (extlen > net->ipv6.sysctl.max_hbh_opts_len)
		जाओ fail_and_मुक्त;

	opt->flags |= IP6SKB_HOPBYHOP;
	अगर (ip6_parse_tlv(tlvprochopopt_lst, skb,
			  init_net.ipv6.sysctl.max_hbh_opts_cnt)) अणु
		skb->transport_header += extlen;
		opt = IP6CB(skb);
		opt->nhoff = माप(काष्ठा ipv6hdr);
		वापस 1;
	पूर्ण
	वापस -1;
पूर्ण

/*
 *	Creating outbound headers.
 *
 *	"build" functions work when skb is filled from head to tail (datagram)
 *	"push"	functions work when headers are added from tail to head (tcp)
 *
 *	In both हालs we assume, that caller reserved enough room
 *	क्रम headers.
 */

अटल व्योम ipv6_push_rthdr0(काष्ठा sk_buff *skb, u8 *proto,
			     काष्ठा ipv6_rt_hdr *opt,
			     काष्ठा in6_addr **addr_p, काष्ठा in6_addr *saddr)
अणु
	काष्ठा rt0_hdr *phdr, *ihdr;
	पूर्णांक hops;

	ihdr = (काष्ठा rt0_hdr *) opt;

	phdr = skb_push(skb, (ihdr->rt_hdr.hdrlen + 1) << 3);
	स_नकल(phdr, ihdr, माप(काष्ठा rt0_hdr));

	hops = ihdr->rt_hdr.hdrlen >> 1;

	अगर (hops > 1)
		स_नकल(phdr->addr, ihdr->addr + 1,
		       (hops - 1) * माप(काष्ठा in6_addr));

	phdr->addr[hops - 1] = **addr_p;
	*addr_p = ihdr->addr;

	phdr->rt_hdr.nexthdr = *proto;
	*proto = NEXTHDR_ROUTING;
पूर्ण

अटल व्योम ipv6_push_rthdr4(काष्ठा sk_buff *skb, u8 *proto,
			     काष्ठा ipv6_rt_hdr *opt,
			     काष्ठा in6_addr **addr_p, काष्ठा in6_addr *saddr)
अणु
	काष्ठा ipv6_sr_hdr *sr_phdr, *sr_ihdr;
	पूर्णांक plen, hops;

	sr_ihdr = (काष्ठा ipv6_sr_hdr *)opt;
	plen = (sr_ihdr->hdrlen + 1) << 3;

	sr_phdr = skb_push(skb, plen);
	स_नकल(sr_phdr, sr_ihdr, माप(काष्ठा ipv6_sr_hdr));

	hops = sr_ihdr->first_segment + 1;
	स_नकल(sr_phdr->segments + 1, sr_ihdr->segments + 1,
	       (hops - 1) * माप(काष्ठा in6_addr));

	sr_phdr->segments[0] = **addr_p;
	*addr_p = &sr_ihdr->segments[sr_ihdr->segments_left];

	अगर (sr_ihdr->hdrlen > hops * 2) अणु
		पूर्णांक tlvs_offset, tlvs_length;

		tlvs_offset = (1 + hops * 2) << 3;
		tlvs_length = (sr_ihdr->hdrlen - hops * 2) << 3;
		स_नकल((अक्षर *)sr_phdr + tlvs_offset,
		       (अक्षर *)sr_ihdr + tlvs_offset, tlvs_length);
	पूर्ण

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अगर (sr_has_hmac(sr_phdr)) अणु
		काष्ठा net *net = शून्य;

		अगर (skb->dev)
			net = dev_net(skb->dev);
		अन्यथा अगर (skb->sk)
			net = sock_net(skb->sk);

		WARN_ON(!net);

		अगर (net)
			seg6_push_hmac(net, saddr, sr_phdr);
	पूर्ण
#पूर्ण_अगर

	sr_phdr->nexthdr = *proto;
	*proto = NEXTHDR_ROUTING;
पूर्ण

अटल व्योम ipv6_push_rthdr(काष्ठा sk_buff *skb, u8 *proto,
			    काष्ठा ipv6_rt_hdr *opt,
			    काष्ठा in6_addr **addr_p, काष्ठा in6_addr *saddr)
अणु
	चयन (opt->type) अणु
	हाल IPV6_SRCRT_TYPE_0:
	हाल IPV6_SRCRT_STRICT:
	हाल IPV6_SRCRT_TYPE_2:
		ipv6_push_rthdr0(skb, proto, opt, addr_p, saddr);
		अवरोध;
	हाल IPV6_SRCRT_TYPE_4:
		ipv6_push_rthdr4(skb, proto, opt, addr_p, saddr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ipv6_push_exthdr(काष्ठा sk_buff *skb, u8 *proto, u8 type, काष्ठा ipv6_opt_hdr *opt)
अणु
	काष्ठा ipv6_opt_hdr *h = skb_push(skb, ipv6_optlen(opt));

	स_नकल(h, opt, ipv6_optlen(opt));
	h->nexthdr = *proto;
	*proto = type;
पूर्ण

व्योम ipv6_push_nfrag_opts(काष्ठा sk_buff *skb, काष्ठा ipv6_txoptions *opt,
			  u8 *proto,
			  काष्ठा in6_addr **daddr, काष्ठा in6_addr *saddr)
अणु
	अगर (opt->srcrt) अणु
		ipv6_push_rthdr(skb, proto, opt->srcrt, daddr, saddr);
		/*
		 * IPV6_RTHDRDSTOPTS is ignored
		 * unless IPV6_RTHDR is set (RFC3542).
		 */
		अगर (opt->dst0opt)
			ipv6_push_exthdr(skb, proto, NEXTHDR_DEST, opt->dst0opt);
	पूर्ण
	अगर (opt->hopopt)
		ipv6_push_exthdr(skb, proto, NEXTHDR_HOP, opt->hopopt);
पूर्ण

व्योम ipv6_push_frag_opts(काष्ठा sk_buff *skb, काष्ठा ipv6_txoptions *opt, u8 *proto)
अणु
	अगर (opt->dst1opt)
		ipv6_push_exthdr(skb, proto, NEXTHDR_DEST, opt->dst1opt);
पूर्ण
EXPORT_SYMBOL(ipv6_push_frag_opts);

काष्ठा ipv6_txoptions *
ipv6_dup_options(काष्ठा sock *sk, काष्ठा ipv6_txoptions *opt)
अणु
	काष्ठा ipv6_txoptions *opt2;

	opt2 = sock_kदो_स्मृति(sk, opt->tot_len, GFP_ATOMIC);
	अगर (opt2) अणु
		दीर्घ dअगर = (अक्षर *)opt2 - (अक्षर *)opt;
		स_नकल(opt2, opt, opt->tot_len);
		अगर (opt2->hopopt)
			*((अक्षर **)&opt2->hopopt) += dअगर;
		अगर (opt2->dst0opt)
			*((अक्षर **)&opt2->dst0opt) += dअगर;
		अगर (opt2->dst1opt)
			*((अक्षर **)&opt2->dst1opt) += dअगर;
		अगर (opt2->srcrt)
			*((अक्षर **)&opt2->srcrt) += dअगर;
		refcount_set(&opt2->refcnt, 1);
	पूर्ण
	वापस opt2;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_dup_options);

अटल व्योम ipv6_renew_option(पूर्णांक renewtype,
			      काष्ठा ipv6_opt_hdr **dest,
			      काष्ठा ipv6_opt_hdr *old,
			      काष्ठा ipv6_opt_hdr *new,
			      पूर्णांक newtype, अक्षर **p)
अणु
	काष्ठा ipv6_opt_hdr *src;

	src = (renewtype == newtype ? new : old);
	अगर (!src)
		वापस;

	स_नकल(*p, src, ipv6_optlen(src));
	*dest = (काष्ठा ipv6_opt_hdr *)*p;
	*p += CMSG_ALIGN(ipv6_optlen(*dest));
पूर्ण

/**
 * ipv6_renew_options - replace a specअगरic ext hdr with a new one.
 *
 * @sk: sock from which to allocate memory
 * @opt: original options
 * @newtype: option type to replace in @opt
 * @newopt: new option of type @newtype to replace (user-mem)
 *
 * Returns a new set of options which is a copy of @opt with the
 * option type @newtype replaced with @newopt.
 *
 * @opt may be शून्य, in which हाल a new set of options is वापसed
 * containing just @newopt.
 *
 * @newopt may be शून्य, in which हाल the specअगरied option type is
 * not copied पूर्णांकo the new set of options.
 *
 * The new set of options is allocated from the socket option memory
 * buffer of @sk.
 */
काष्ठा ipv6_txoptions *
ipv6_renew_options(काष्ठा sock *sk, काष्ठा ipv6_txoptions *opt,
		   पूर्णांक newtype, काष्ठा ipv6_opt_hdr *newopt)
अणु
	पूर्णांक tot_len = 0;
	अक्षर *p;
	काष्ठा ipv6_txoptions *opt2;

	अगर (opt) अणु
		अगर (newtype != IPV6_HOPOPTS && opt->hopopt)
			tot_len += CMSG_ALIGN(ipv6_optlen(opt->hopopt));
		अगर (newtype != IPV6_RTHDRDSTOPTS && opt->dst0opt)
			tot_len += CMSG_ALIGN(ipv6_optlen(opt->dst0opt));
		अगर (newtype != IPV6_RTHDR && opt->srcrt)
			tot_len += CMSG_ALIGN(ipv6_optlen(opt->srcrt));
		अगर (newtype != IPV6_DSTOPTS && opt->dst1opt)
			tot_len += CMSG_ALIGN(ipv6_optlen(opt->dst1opt));
	पूर्ण

	अगर (newopt)
		tot_len += CMSG_ALIGN(ipv6_optlen(newopt));

	अगर (!tot_len)
		वापस शून्य;

	tot_len += माप(*opt2);
	opt2 = sock_kदो_स्मृति(sk, tot_len, GFP_ATOMIC);
	अगर (!opt2)
		वापस ERR_PTR(-ENOBUFS);

	स_रखो(opt2, 0, tot_len);
	refcount_set(&opt2->refcnt, 1);
	opt2->tot_len = tot_len;
	p = (अक्षर *)(opt2 + 1);

	ipv6_renew_option(IPV6_HOPOPTS, &opt2->hopopt,
			  (opt ? opt->hopopt : शून्य),
			  newopt, newtype, &p);
	ipv6_renew_option(IPV6_RTHDRDSTOPTS, &opt2->dst0opt,
			  (opt ? opt->dst0opt : शून्य),
			  newopt, newtype, &p);
	ipv6_renew_option(IPV6_RTHDR,
			  (काष्ठा ipv6_opt_hdr **)&opt2->srcrt,
			  (opt ? (काष्ठा ipv6_opt_hdr *)opt->srcrt : शून्य),
			  newopt, newtype, &p);
	ipv6_renew_option(IPV6_DSTOPTS, &opt2->dst1opt,
			  (opt ? opt->dst1opt : शून्य),
			  newopt, newtype, &p);

	opt2->opt_nflen = (opt2->hopopt ? ipv6_optlen(opt2->hopopt) : 0) +
			  (opt2->dst0opt ? ipv6_optlen(opt2->dst0opt) : 0) +
			  (opt2->srcrt ? ipv6_optlen(opt2->srcrt) : 0);
	opt2->opt_flen = (opt2->dst1opt ? ipv6_optlen(opt2->dst1opt) : 0);

	वापस opt2;
पूर्ण

काष्ठा ipv6_txoptions *ipv6_fixup_options(काष्ठा ipv6_txoptions *opt_space,
					  काष्ठा ipv6_txoptions *opt)
अणु
	/*
	 * ignore the dest beक्रमe srcrt unless srcrt is being included.
	 * --yoshfuji
	 */
	अगर (opt && opt->dst0opt && !opt->srcrt) अणु
		अगर (opt_space != opt) अणु
			स_नकल(opt_space, opt, माप(*opt_space));
			opt = opt_space;
		पूर्ण
		opt->opt_nflen -= ipv6_optlen(opt->dst0opt);
		opt->dst0opt = शून्य;
	पूर्ण

	वापस opt;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_fixup_options);

/**
 * fl6_update_dst - update flowi destination address with info given
 *                  by srcrt option, अगर any.
 *
 * @fl6: flowi6 क्रम which daddr is to be updated
 * @opt: काष्ठा ipv6_txoptions in which to look क्रम srcrt opt
 * @orig: copy of original daddr address अगर modअगरied
 *
 * Returns शून्य अगर no txoptions or no srcrt, otherwise वापसs orig
 * and initial value of fl6->daddr set in orig
 */
काष्ठा in6_addr *fl6_update_dst(काष्ठा flowi6 *fl6,
				स्थिर काष्ठा ipv6_txoptions *opt,
				काष्ठा in6_addr *orig)
अणु
	अगर (!opt || !opt->srcrt)
		वापस शून्य;

	*orig = fl6->daddr;

	चयन (opt->srcrt->type) अणु
	हाल IPV6_SRCRT_TYPE_0:
	हाल IPV6_SRCRT_STRICT:
	हाल IPV6_SRCRT_TYPE_2:
		fl6->daddr = *((काष्ठा rt0_hdr *)opt->srcrt)->addr;
		अवरोध;
	हाल IPV6_SRCRT_TYPE_4:
	अणु
		काष्ठा ipv6_sr_hdr *srh = (काष्ठा ipv6_sr_hdr *)opt->srcrt;

		fl6->daddr = srh->segments[srh->segments_left];
		अवरोध;
	पूर्ण
	शेष:
		वापस शून्य;
	पूर्ण

	वापस orig;
पूर्ण
EXPORT_SYMBOL_GPL(fl6_update_dst);
