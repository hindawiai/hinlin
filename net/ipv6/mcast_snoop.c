<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2010: YOSHIFUJI Hideaki <yoshfuji@linux-ipv6.org>
 * Copyright (C) 2015: Linus Lथञssing <linus.luessing@c0d3.blue>
 *
 * Based on the MLD support added to br_multicast.c by YOSHIFUJI Hideaki.
 */

#समावेश <linux/skbuff.h>
#समावेश <net/ipv6.h>
#समावेश <net/mld.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_checksum.h>

अटल पूर्णांक ipv6_mc_check_ip6hdr(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक offset = skb_network_offset(skb) + माप(*ip6h);

	अगर (!pskb_may_pull(skb, offset))
		वापस -EINVAL;

	ip6h = ipv6_hdr(skb);

	अगर (ip6h->version != 6)
		वापस -EINVAL;

	len = offset + ntohs(ip6h->payload_len);
	अगर (skb->len < len || len <= offset)
		वापस -EINVAL;

	skb_set_transport_header(skb, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_mc_check_exthdrs(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h;
	पूर्णांक offset;
	u8 nexthdr;
	__be16 frag_off;

	ip6h = ipv6_hdr(skb);

	अगर (ip6h->nexthdr != IPPROTO_HOPOPTS)
		वापस -ENOMSG;

	nexthdr = ip6h->nexthdr;
	offset = skb_network_offset(skb) + माप(*ip6h);
	offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);

	अगर (offset < 0)
		वापस -EINVAL;

	अगर (nexthdr != IPPROTO_ICMPV6)
		वापस -ENOMSG;

	skb_set_transport_header(skb, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_mc_check_mld_reportv2(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = skb_transport_offset(skb);

	len += माप(काष्ठा mld2_report);

	वापस ipv6_mc_may_pull(skb, len) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ipv6_mc_check_mld_query(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक transport_len = ipv6_transport_len(skb);
	काष्ठा mld_msg *mld;
	अचिन्हित पूर्णांक len;

	/* RFC2710+RFC3810 (MLDv1+MLDv2) require link-local source addresses */
	अगर (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL))
		वापस -EINVAL;

	/* MLDv1? */
	अगर (transport_len != माप(काष्ठा mld_msg)) अणु
		/* or MLDv2? */
		अगर (transport_len < माप(काष्ठा mld2_query))
			वापस -EINVAL;

		len = skb_transport_offset(skb) + माप(काष्ठा mld2_query);
		अगर (!ipv6_mc_may_pull(skb, len))
			वापस -EINVAL;
	पूर्ण

	mld = (काष्ठा mld_msg *)skb_transport_header(skb);

	/* RFC2710+RFC3810 (MLDv1+MLDv2) require the multicast link layer
	 * all-nodes destination address (ff02::1) क्रम general queries
	 */
	अगर (ipv6_addr_any(&mld->mld_mca) &&
	    !ipv6_addr_is_ll_all_nodes(&ipv6_hdr(skb)->daddr))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_mc_check_mld_msg(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = skb_transport_offset(skb) + माप(काष्ठा mld_msg);
	काष्ठा mld_msg *mld;

	अगर (!ipv6_mc_may_pull(skb, len))
		वापस -ENODATA;

	mld = (काष्ठा mld_msg *)skb_transport_header(skb);

	चयन (mld->mld_type) अणु
	हाल ICMPV6_MGM_REDUCTION:
	हाल ICMPV6_MGM_REPORT:
		वापस 0;
	हाल ICMPV6_MLD2_REPORT:
		वापस ipv6_mc_check_mld_reportv2(skb);
	हाल ICMPV6_MGM_QUERY:
		वापस ipv6_mc_check_mld_query(skb);
	शेष:
		वापस -ENODATA;
	पूर्ण
पूर्ण

अटल अंतरभूत __sum16 ipv6_mc_validate_checksum(काष्ठा sk_buff *skb)
अणु
	वापस skb_checksum_validate(skb, IPPROTO_ICMPV6, ip6_compute_pseuकरो);
पूर्ण

अटल पूर्णांक ipv6_mc_check_icmpv6(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = skb_transport_offset(skb) + माप(काष्ठा icmp6hdr);
	अचिन्हित पूर्णांक transport_len = ipv6_transport_len(skb);
	काष्ठा sk_buff *skb_chk;

	अगर (!ipv6_mc_may_pull(skb, len))
		वापस -EINVAL;

	skb_chk = skb_checksum_trimmed(skb, transport_len,
				       ipv6_mc_validate_checksum);
	अगर (!skb_chk)
		वापस -EINVAL;

	अगर (skb_chk != skb)
		kमुक्त_skb(skb_chk);

	वापस 0;
पूर्ण

/**
 * ipv6_mc_check_mld - checks whether this is a sane MLD packet
 * @skb: the skb to validate
 *
 * Checks whether an IPv6 packet is a valid MLD packet. If so sets
 * skb transport header accordingly and वापसs zero.
 *
 * -EINVAL: A broken packet was detected, i.e. it violates some पूर्णांकernet
 *  standard
 * -ENOMSG: IP header validation succeeded but it is not an ICMPv6 packet
 *  with a hop-by-hop option.
 * -ENODATA: IP+ICMPv6 header with hop-by-hop option validation succeeded
 *  but it is not an MLD packet.
 * -ENOMEM: A memory allocation failure happened.
 *
 * Caller needs to set the skb network header and मुक्त any वापसed skb अगर it
 * dअगरfers from the provided skb.
 */
पूर्णांक ipv6_mc_check_mld(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	ret = ipv6_mc_check_ip6hdr(skb);
	अगर (ret < 0)
		वापस ret;

	ret = ipv6_mc_check_exthdrs(skb);
	अगर (ret < 0)
		वापस ret;

	ret = ipv6_mc_check_icmpv6(skb);
	अगर (ret < 0)
		वापस ret;

	वापस ipv6_mc_check_mld_msg(skb);
पूर्ण
EXPORT_SYMBOL(ipv6_mc_check_mld);
