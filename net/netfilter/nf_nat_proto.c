<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>

#समावेश <linux/dccp.h>
#समावेश <linux/sctp.h>
#समावेश <net/sctp/checksum.h>

#समावेश <linux/netfilter.h>
#समावेश <net/netfilter/nf_nat.h>

#समावेश <linux/ipv6.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/ip6_route.h>
#समावेश <net/xfrm.h>
#समावेश <net/ipv6.h>

#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>

अटल व्योम nf_csum_update(काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक iphdroff, __sum16 *check,
			   स्थिर काष्ठा nf_conntrack_tuple *t,
			   क्रमागत nf_nat_manip_type maniptype);

अटल व्योम
__udp_manip_pkt(काष्ठा sk_buff *skb,
	        अचिन्हित पूर्णांक iphdroff, काष्ठा udphdr *hdr,
	        स्थिर काष्ठा nf_conntrack_tuple *tuple,
	        क्रमागत nf_nat_manip_type maniptype, bool करो_csum)
अणु
	__be16 *portptr, newport;

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		/* Get rid of src port */
		newport = tuple->src.u.udp.port;
		portptr = &hdr->source;
	पूर्ण अन्यथा अणु
		/* Get rid of dst port */
		newport = tuple->dst.u.udp.port;
		portptr = &hdr->dest;
	पूर्ण
	अगर (करो_csum) अणु
		nf_csum_update(skb, iphdroff, &hdr->check, tuple, maniptype);
		inet_proto_csum_replace2(&hdr->check, skb, *portptr, newport,
					 false);
		अगर (!hdr->check)
			hdr->check = CSUM_MANGLED_0;
	पूर्ण
	*portptr = newport;
पूर्ण

अटल bool udp_manip_pkt(काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
			  स्थिर काष्ठा nf_conntrack_tuple *tuple,
			  क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा udphdr *hdr;

	अगर (skb_ensure_writable(skb, hdroff + माप(*hdr)))
		वापस false;

	hdr = (काष्ठा udphdr *)(skb->data + hdroff);
	__udp_manip_pkt(skb, iphdroff, hdr, tuple, maniptype, !!hdr->check);

	वापस true;
पूर्ण

अटल bool udplite_manip_pkt(काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
			      स्थिर काष्ठा nf_conntrack_tuple *tuple,
			      क्रमागत nf_nat_manip_type maniptype)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
	काष्ठा udphdr *hdr;

	अगर (skb_ensure_writable(skb, hdroff + माप(*hdr)))
		वापस false;

	hdr = (काष्ठा udphdr *)(skb->data + hdroff);
	__udp_manip_pkt(skb, iphdroff, hdr, tuple, maniptype, true);
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool
sctp_manip_pkt(काष्ठा sk_buff *skb,
	       अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
	       स्थिर काष्ठा nf_conntrack_tuple *tuple,
	       क्रमागत nf_nat_manip_type maniptype)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	काष्ठा sctphdr *hdr;
	पूर्णांक hdrsize = 8;

	/* This could be an inner header वापसed in imcp packet; in such
	 * हालs we cannot update the checksum field since it is outside
	 * of the 8 bytes of transport layer headers we are guaranteed.
	 */
	अगर (skb->len >= hdroff + माप(*hdr))
		hdrsize = माप(*hdr);

	अगर (skb_ensure_writable(skb, hdroff + hdrsize))
		वापस false;

	hdr = (काष्ठा sctphdr *)(skb->data + hdroff);

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		/* Get rid of src port */
		hdr->source = tuple->src.u.sctp.port;
	पूर्ण अन्यथा अणु
		/* Get rid of dst port */
		hdr->dest = tuple->dst.u.sctp.port;
	पूर्ण

	अगर (hdrsize < माप(*hdr))
		वापस true;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		hdr->checksum = sctp_compute_cksum(skb, hdroff);
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण

#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool
tcp_manip_pkt(काष्ठा sk_buff *skb,
	      अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
	      स्थिर काष्ठा nf_conntrack_tuple *tuple,
	      क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा tcphdr *hdr;
	__be16 *portptr, newport, oldport;
	पूर्णांक hdrsize = 8; /* TCP connection tracking guarantees this much */

	/* this could be a inner header वापसed in icmp packet; in such
	   हालs we cannot update the checksum field since it is outside of
	   the 8 bytes of transport layer headers we are guaranteed */
	अगर (skb->len >= hdroff + माप(काष्ठा tcphdr))
		hdrsize = माप(काष्ठा tcphdr);

	अगर (skb_ensure_writable(skb, hdroff + hdrsize))
		वापस false;

	hdr = (काष्ठा tcphdr *)(skb->data + hdroff);

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		/* Get rid of src port */
		newport = tuple->src.u.tcp.port;
		portptr = &hdr->source;
	पूर्ण अन्यथा अणु
		/* Get rid of dst port */
		newport = tuple->dst.u.tcp.port;
		portptr = &hdr->dest;
	पूर्ण

	oldport = *portptr;
	*portptr = newport;

	अगर (hdrsize < माप(*hdr))
		वापस true;

	nf_csum_update(skb, iphdroff, &hdr->check, tuple, maniptype);
	inet_proto_csum_replace2(&hdr->check, skb, oldport, newport, false);
	वापस true;
पूर्ण

अटल bool
dccp_manip_pkt(काष्ठा sk_buff *skb,
	       अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
	       स्थिर काष्ठा nf_conntrack_tuple *tuple,
	       क्रमागत nf_nat_manip_type maniptype)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	काष्ठा dccp_hdr *hdr;
	__be16 *portptr, oldport, newport;
	पूर्णांक hdrsize = 8; /* DCCP connection tracking guarantees this much */

	अगर (skb->len >= hdroff + माप(काष्ठा dccp_hdr))
		hdrsize = माप(काष्ठा dccp_hdr);

	अगर (skb_ensure_writable(skb, hdroff + hdrsize))
		वापस false;

	hdr = (काष्ठा dccp_hdr *)(skb->data + hdroff);

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		newport = tuple->src.u.dccp.port;
		portptr = &hdr->dccph_sport;
	पूर्ण अन्यथा अणु
		newport = tuple->dst.u.dccp.port;
		portptr = &hdr->dccph_dport;
	पूर्ण

	oldport = *portptr;
	*portptr = newport;

	अगर (hdrsize < माप(*hdr))
		वापस true;

	nf_csum_update(skb, iphdroff, &hdr->dccph_checksum, tuple, maniptype);
	inet_proto_csum_replace2(&hdr->dccph_checksum, skb, oldport, newport,
				 false);
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool
icmp_manip_pkt(काष्ठा sk_buff *skb,
	       अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
	       स्थिर काष्ठा nf_conntrack_tuple *tuple,
	       क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा icmphdr *hdr;

	अगर (skb_ensure_writable(skb, hdroff + माप(*hdr)))
		वापस false;

	hdr = (काष्ठा icmphdr *)(skb->data + hdroff);
	चयन (hdr->type) अणु
	हाल ICMP_ECHO:
	हाल ICMP_ECHOREPLY:
	हाल ICMP_TIMESTAMP:
	हाल ICMP_TIMESTAMPREPLY:
	हाल ICMP_INFO_REQUEST:
	हाल ICMP_INFO_REPLY:
	हाल ICMP_ADDRESS:
	हाल ICMP_ADDRESSREPLY:
		अवरोध;
	शेष:
		वापस true;
	पूर्ण
	inet_proto_csum_replace2(&hdr->checksum, skb,
				 hdr->un.echo.id, tuple->src.u.icmp.id, false);
	hdr->un.echo.id = tuple->src.u.icmp.id;
	वापस true;
पूर्ण

अटल bool
icmpv6_manip_pkt(काष्ठा sk_buff *skb,
		 अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
		 स्थिर काष्ठा nf_conntrack_tuple *tuple,
		 क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा icmp6hdr *hdr;

	अगर (skb_ensure_writable(skb, hdroff + माप(*hdr)))
		वापस false;

	hdr = (काष्ठा icmp6hdr *)(skb->data + hdroff);
	nf_csum_update(skb, iphdroff, &hdr->icmp6_cksum, tuple, maniptype);
	अगर (hdr->icmp6_type == ICMPV6_ECHO_REQUEST ||
	    hdr->icmp6_type == ICMPV6_ECHO_REPLY) अणु
		inet_proto_csum_replace2(&hdr->icmp6_cksum, skb,
					 hdr->icmp6_identअगरier,
					 tuple->src.u.icmp.id, false);
		hdr->icmp6_identअगरier = tuple->src.u.icmp.id;
	पूर्ण
	वापस true;
पूर्ण

/* manipulate a GRE packet according to maniptype */
अटल bool
gre_manip_pkt(काष्ठा sk_buff *skb,
	      अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
	      स्थिर काष्ठा nf_conntrack_tuple *tuple,
	      क्रमागत nf_nat_manip_type maniptype)
अणु
#अगर IS_ENABLED(CONFIG_NF_CT_PROTO_GRE)
	स्थिर काष्ठा gre_base_hdr *greh;
	काष्ठा pptp_gre_header *pgreh;

	/* pgreh includes two optional 32bit fields which are not required
	 * to be there.  That's where the magic '8' comes from */
	अगर (skb_ensure_writable(skb, hdroff + माप(*pgreh) - 8))
		वापस false;

	greh = (व्योम *)skb->data + hdroff;
	pgreh = (काष्ठा pptp_gre_header *)greh;

	/* we only have destination manip of a packet, since 'source key'
	 * is not present in the packet itself */
	अगर (maniptype != NF_NAT_MANIP_DST)
		वापस true;

	चयन (greh->flags & GRE_VERSION) अणु
	हाल GRE_VERSION_0:
		/* We करो not currently NAT any GREv0 packets.
		 * Try to behave like "nf_nat_proto_unknown" */
		अवरोध;
	हाल GRE_VERSION_1:
		pr_debug("call_id -> 0x%04x\n", ntohs(tuple->dst.u.gre.key));
		pgreh->call_id = tuple->dst.u.gre.key;
		अवरोध;
	शेष:
		pr_debug("can't nat unknown GRE version\n");
		वापस false;
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool l4proto_manip_pkt(काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक iphdroff, अचिन्हित पूर्णांक hdroff,
			      स्थिर काष्ठा nf_conntrack_tuple *tuple,
			      क्रमागत nf_nat_manip_type maniptype)
अणु
	चयन (tuple->dst.protonum) अणु
	हाल IPPROTO_TCP:
		वापस tcp_manip_pkt(skb, iphdroff, hdroff,
				     tuple, maniptype);
	हाल IPPROTO_UDP:
		वापस udp_manip_pkt(skb, iphdroff, hdroff,
				     tuple, maniptype);
	हाल IPPROTO_UDPLITE:
		वापस udplite_manip_pkt(skb, iphdroff, hdroff,
					 tuple, maniptype);
	हाल IPPROTO_SCTP:
		वापस sctp_manip_pkt(skb, iphdroff, hdroff,
				      tuple, maniptype);
	हाल IPPROTO_ICMP:
		वापस icmp_manip_pkt(skb, iphdroff, hdroff,
				      tuple, maniptype);
	हाल IPPROTO_ICMPV6:
		वापस icmpv6_manip_pkt(skb, iphdroff, hdroff,
					tuple, maniptype);
	हाल IPPROTO_DCCP:
		वापस dccp_manip_pkt(skb, iphdroff, hdroff,
				      tuple, maniptype);
	हाल IPPROTO_GRE:
		वापस gre_manip_pkt(skb, iphdroff, hdroff,
				     tuple, maniptype);
	पूर्ण

	/* If we करोn't know protocol -- no error, pass it unmodअगरied. */
	वापस true;
पूर्ण

अटल bool nf_nat_ipv4_manip_pkt(काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक iphdroff,
				  स्थिर काष्ठा nf_conntrack_tuple *target,
				  क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा iphdr *iph;
	अचिन्हित पूर्णांक hdroff;

	अगर (skb_ensure_writable(skb, iphdroff + माप(*iph)))
		वापस false;

	iph = (व्योम *)skb->data + iphdroff;
	hdroff = iphdroff + iph->ihl * 4;

	अगर (!l4proto_manip_pkt(skb, iphdroff, hdroff, target, maniptype))
		वापस false;
	iph = (व्योम *)skb->data + iphdroff;

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		csum_replace4(&iph->check, iph->saddr, target->src.u3.ip);
		iph->saddr = target->src.u3.ip;
	पूर्ण अन्यथा अणु
		csum_replace4(&iph->check, iph->daddr, target->dst.u3.ip);
		iph->daddr = target->dst.u3.ip;
	पूर्ण
	वापस true;
पूर्ण

अटल bool nf_nat_ipv6_manip_pkt(काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक iphdroff,
				  स्थिर काष्ठा nf_conntrack_tuple *target,
				  क्रमागत nf_nat_manip_type maniptype)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6hdr *ipv6h;
	__be16 frag_off;
	पूर्णांक hdroff;
	u8 nexthdr;

	अगर (skb_ensure_writable(skb, iphdroff + माप(*ipv6h)))
		वापस false;

	ipv6h = (व्योम *)skb->data + iphdroff;
	nexthdr = ipv6h->nexthdr;
	hdroff = ipv6_skip_exthdr(skb, iphdroff + माप(*ipv6h),
				  &nexthdr, &frag_off);
	अगर (hdroff < 0)
		जाओ manip_addr;

	अगर ((frag_off & htons(~0x7)) == 0 &&
	    !l4proto_manip_pkt(skb, iphdroff, hdroff, target, maniptype))
		वापस false;

	/* must reload, offset might have changed */
	ipv6h = (व्योम *)skb->data + iphdroff;

manip_addr:
	अगर (maniptype == NF_NAT_MANIP_SRC)
		ipv6h->saddr = target->src.u3.in6;
	अन्यथा
		ipv6h->daddr = target->dst.u3.in6;

#पूर्ण_अगर
	वापस true;
पूर्ण

अचिन्हित पूर्णांक nf_nat_manip_pkt(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			      क्रमागत nf_nat_manip_type mtype,
			      क्रमागत ip_conntrack_dir dir)
अणु
	काष्ठा nf_conntrack_tuple target;

	/* We are aiming to look like inverse of other direction. */
	nf_ct_invert_tuple(&target, &ct->tuplehash[!dir].tuple);

	चयन (target.src.l3num) अणु
	हाल NFPROTO_IPV6:
		अगर (nf_nat_ipv6_manip_pkt(skb, 0, &target, mtype))
			वापस NF_ACCEPT;
		अवरोध;
	हाल NFPROTO_IPV4:
		अगर (nf_nat_ipv4_manip_pkt(skb, 0, &target, mtype))
			वापस NF_ACCEPT;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस NF_DROP;
पूर्ण

अटल व्योम nf_nat_ipv4_csum_update(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक iphdroff, __sum16 *check,
				    स्थिर काष्ठा nf_conntrack_tuple *t,
				    क्रमागत nf_nat_manip_type maniptype)
अणु
	काष्ठा iphdr *iph = (काष्ठा iphdr *)(skb->data + iphdroff);
	__be32 oldip, newip;

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		oldip = iph->saddr;
		newip = t->src.u3.ip;
	पूर्ण अन्यथा अणु
		oldip = iph->daddr;
		newip = t->dst.u3.ip;
	पूर्ण
	inet_proto_csum_replace4(check, skb, oldip, newip, true);
पूर्ण

अटल व्योम nf_nat_ipv6_csum_update(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक iphdroff, __sum16 *check,
				    स्थिर काष्ठा nf_conntrack_tuple *t,
				    क्रमागत nf_nat_manip_type maniptype)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	स्थिर काष्ठा ipv6hdr *ipv6h = (काष्ठा ipv6hdr *)(skb->data + iphdroff);
	स्थिर काष्ठा in6_addr *oldip, *newip;

	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		oldip = &ipv6h->saddr;
		newip = &t->src.u3.in6;
	पूर्ण अन्यथा अणु
		oldip = &ipv6h->daddr;
		newip = &t->dst.u3.in6;
	पूर्ण
	inet_proto_csum_replace16(check, skb, oldip->s6_addr32,
				  newip->s6_addr32, true);
#पूर्ण_अगर
पूर्ण

अटल व्योम nf_csum_update(काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक iphdroff, __sum16 *check,
			   स्थिर काष्ठा nf_conntrack_tuple *t,
			   क्रमागत nf_nat_manip_type maniptype)
अणु
	चयन (t->src.l3num) अणु
	हाल NFPROTO_IPV4:
		nf_nat_ipv4_csum_update(skb, iphdroff, check, t, maniptype);
		वापस;
	हाल NFPROTO_IPV6:
		nf_nat_ipv6_csum_update(skb, iphdroff, check, t, maniptype);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम nf_nat_ipv4_csum_recalc(काष्ठा sk_buff *skb,
				    u8 proto, व्योम *data, __sum16 *check,
				    पूर्णांक datalen, पूर्णांक oldlen)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_headroom(skb) + skb_network_offset(skb) +
			ip_hdrlen(skb);
		skb->csum_offset = (व्योम *)check - data;
		*check = ~csum_tcpudp_magic(iph->saddr, iph->daddr, datalen,
					    proto, 0);
	पूर्ण अन्यथा अणु
		inet_proto_csum_replace2(check, skb,
					 htons(oldlen), htons(datalen), true);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम nf_nat_ipv6_csum_recalc(काष्ठा sk_buff *skb,
				    u8 proto, व्योम *data, __sum16 *check,
				    पूर्णांक datalen, पूर्णांक oldlen)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		स्थिर काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);

		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_headroom(skb) + skb_network_offset(skb) +
			(data - (व्योम *)skb->data);
		skb->csum_offset = (व्योम *)check - data;
		*check = ~csum_ipv6_magic(&ipv6h->saddr, &ipv6h->daddr,
					  datalen, proto, 0);
	पूर्ण अन्यथा अणु
		inet_proto_csum_replace2(check, skb,
					 htons(oldlen), htons(datalen), true);
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम nf_nat_csum_recalc(काष्ठा sk_buff *skb,
			u8 nfproto, u8 proto, व्योम *data, __sum16 *check,
			पूर्णांक datalen, पूर्णांक oldlen)
अणु
	चयन (nfproto) अणु
	हाल NFPROTO_IPV4:
		nf_nat_ipv4_csum_recalc(skb, proto, data, check,
					datalen, oldlen);
		वापस;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NFPROTO_IPV6:
		nf_nat_ipv6_csum_recalc(skb, proto, data, check,
					datalen, oldlen);
		वापस;
#पूर्ण_अगर
	पूर्ण

	WARN_ON_ONCE(1);
पूर्ण

पूर्णांक nf_nat_icmp_reply_translation(काष्ठा sk_buff *skb,
				  काष्ठा nf_conn *ct,
				  क्रमागत ip_conntrack_info ctinfo,
				  अचिन्हित पूर्णांक hooknum)
अणु
	काष्ठा अणु
		काष्ठा icmphdr	icmp;
		काष्ठा iphdr	ip;
	पूर्ण *inside;
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	क्रमागत nf_nat_manip_type manip = HOOK2MANIP(hooknum);
	अचिन्हित पूर्णांक hdrlen = ip_hdrlen(skb);
	काष्ठा nf_conntrack_tuple target;
	अचिन्हित दीर्घ statusbit;

	WARN_ON(ctinfo != IP_CT_RELATED && ctinfo != IP_CT_RELATED_REPLY);

	अगर (skb_ensure_writable(skb, hdrlen + माप(*inside)))
		वापस 0;
	अगर (nf_ip_checksum(skb, hooknum, hdrlen, IPPROTO_ICMP))
		वापस 0;

	inside = (व्योम *)skb->data + hdrlen;
	अगर (inside->icmp.type == ICMP_REसूचीECT) अणु
		अगर ((ct->status & IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
			वापस 0;
		अगर (ct->status & IPS_NAT_MASK)
			वापस 0;
	पूर्ण

	अगर (manip == NF_NAT_MANIP_SRC)
		statusbit = IPS_SRC_NAT;
	अन्यथा
		statusbit = IPS_DST_NAT;

	/* Invert अगर this is reply direction */
	अगर (dir == IP_CT_सूची_REPLY)
		statusbit ^= IPS_NAT_MASK;

	अगर (!(ct->status & statusbit))
		वापस 1;

	अगर (!nf_nat_ipv4_manip_pkt(skb, hdrlen + माप(inside->icmp),
				   &ct->tuplehash[!dir].tuple, !manip))
		वापस 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		/* Reloading "inside" here since manip_pkt may पुनः_स्मृतिate */
		inside = (व्योम *)skb->data + hdrlen;
		inside->icmp.checksum = 0;
		inside->icmp.checksum =
			csum_fold(skb_checksum(skb, hdrlen,
					       skb->len - hdrlen, 0));
	पूर्ण

	/* Change outer to look like the reply to an incoming packet */
	nf_ct_invert_tuple(&target, &ct->tuplehash[!dir].tuple);
	target.dst.protonum = IPPROTO_ICMP;
	अगर (!nf_nat_ipv4_manip_pkt(skb, 0, &target, manip))
		वापस 0;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_icmp_reply_translation);

अटल अचिन्हित पूर्णांक
nf_nat_ipv4_fn(व्योम *priv, काष्ठा sk_buff *skb,
	       स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस NF_ACCEPT;

	अगर (ctinfo == IP_CT_RELATED || ctinfo == IP_CT_RELATED_REPLY) अणु
		अगर (ip_hdr(skb)->protocol == IPPROTO_ICMP) अणु
			अगर (!nf_nat_icmp_reply_translation(skb, ct, ctinfo,
							   state->hook))
				वापस NF_DROP;
			अन्यथा
				वापस NF_ACCEPT;
		पूर्ण
	पूर्ण

	वापस nf_nat_inet_fn(priv, skb, state);
पूर्ण

अटल अचिन्हित पूर्णांक
nf_nat_ipv4_pre_routing(व्योम *priv, काष्ठा sk_buff *skb,
			स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक ret;
	__be32 daddr = ip_hdr(skb)->daddr;

	ret = nf_nat_ipv4_fn(priv, skb, state);
	अगर (ret == NF_ACCEPT && daddr != ip_hdr(skb)->daddr)
		skb_dst_drop(skb);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_XFRM
अटल पूर्णांक nf_xfrm_me_harder(काष्ठा net *net, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक family)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा dst_entry *dst;
	अचिन्हित पूर्णांक hh_len;
	काष्ठा flowi fl;
	पूर्णांक err;

	err = xfrm_decode_session(skb, &fl, family);
	अगर (err < 0)
		वापस err;

	dst = skb_dst(skb);
	अगर (dst->xfrm)
		dst = ((काष्ठा xfrm_dst *)dst)->route;
	अगर (!dst_hold_safe(dst))
		वापस -EHOSTUNREACH;

	अगर (sk && !net_eq(net, sock_net(sk)))
		sk = शून्य;

	dst = xfrm_lookup(net, dst, &fl, sk, 0);
	अगर (IS_ERR(dst))
		वापस PTR_ERR(dst);

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	/* Change in oअगर may mean change in hh_len. */
	hh_len = skb_dst(skb)->dev->hard_header_len;
	अगर (skb_headroom(skb) < hh_len &&
	    pskb_expand_head(skb, hh_len - skb_headroom(skb), 0, GFP_ATOMIC))
		वापस -ENOMEM;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक
nf_nat_ipv4_local_in(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	__be32 saddr = ip_hdr(skb)->saddr;
	काष्ठा sock *sk = skb->sk;
	अचिन्हित पूर्णांक ret;

	ret = nf_nat_ipv4_fn(priv, skb, state);

	अगर (ret == NF_ACCEPT && sk && saddr != ip_hdr(skb)->saddr &&
	    !inet_sk_transparent(sk))
		skb_orphan(skb); /* TCP edemux obtained wrong socket */

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
nf_nat_ipv4_out(व्योम *priv, काष्ठा sk_buff *skb,
		स्थिर काष्ठा nf_hook_state *state)
अणु
#अगर_घोषित CONFIG_XFRM
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	पूर्णांक err;
#पूर्ण_अगर
	अचिन्हित पूर्णांक ret;

	ret = nf_nat_ipv4_fn(priv, skb, state);
#अगर_घोषित CONFIG_XFRM
	अगर (ret != NF_ACCEPT)
		वापस ret;

	अगर (IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED)
		वापस ret;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);

		अगर (ct->tuplehash[dir].tuple.src.u3.ip !=
		     ct->tuplehash[!dir].tuple.dst.u3.ip ||
		    (ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMP &&
		     ct->tuplehash[dir].tuple.src.u.all !=
		     ct->tuplehash[!dir].tuple.dst.u.all)) अणु
			err = nf_xfrm_me_harder(state->net, skb, AF_INET);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
nf_nat_ipv4_local_fn(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	अचिन्हित पूर्णांक ret;
	पूर्णांक err;

	ret = nf_nat_ipv4_fn(priv, skb, state);
	अगर (ret != NF_ACCEPT)
		वापस ret;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);

		अगर (ct->tuplehash[dir].tuple.dst.u3.ip !=
		    ct->tuplehash[!dir].tuple.src.u3.ip) अणु
			err = ip_route_me_harder(state->net, state->sk, skb, RTN_UNSPEC);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
#अगर_घोषित CONFIG_XFRM
		अन्यथा अगर (!(IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED) &&
			 ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMP &&
			 ct->tuplehash[dir].tuple.dst.u.all !=
			 ct->tuplehash[!dir].tuple.src.u.all) अणु
			err = nf_xfrm_me_harder(state->net, skb, AF_INET);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops nf_nat_ipv4_ops[] = अणु
	/* Beक्रमe packet filtering, change destination */
	अणु
		.hook		= nf_nat_ipv4_pre_routing,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP_PRI_NAT_DST,
	पूर्ण,
	/* After packet filtering, change source */
	अणु
		.hook		= nf_nat_ipv4_out,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP_PRI_NAT_SRC,
	पूर्ण,
	/* Beक्रमe packet filtering, change destination */
	अणु
		.hook		= nf_nat_ipv4_local_fn,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP_PRI_NAT_DST,
	पूर्ण,
	/* After packet filtering, change source */
	अणु
		.hook		= nf_nat_ipv4_local_in,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_NAT_SRC,
	पूर्ण,
पूर्ण;

पूर्णांक nf_nat_ipv4_रेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	वापस nf_nat_रेजिस्टर_fn(net, ops->pf, ops, nf_nat_ipv4_ops,
				  ARRAY_SIZE(nf_nat_ipv4_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_ipv4_रेजिस्टर_fn);

व्योम nf_nat_ipv4_unरेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	nf_nat_unरेजिस्टर_fn(net, ops->pf, ops, ARRAY_SIZE(nf_nat_ipv4_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_ipv4_unरेजिस्टर_fn);

#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक nf_nat_icmpv6_reply_translation(काष्ठा sk_buff *skb,
				    काष्ठा nf_conn *ct,
				    क्रमागत ip_conntrack_info ctinfo,
				    अचिन्हित पूर्णांक hooknum,
				    अचिन्हित पूर्णांक hdrlen)
अणु
	काष्ठा अणु
		काष्ठा icmp6hdr	icmp6;
		काष्ठा ipv6hdr	ip6;
	पूर्ण *inside;
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	क्रमागत nf_nat_manip_type manip = HOOK2MANIP(hooknum);
	काष्ठा nf_conntrack_tuple target;
	अचिन्हित दीर्घ statusbit;

	WARN_ON(ctinfo != IP_CT_RELATED && ctinfo != IP_CT_RELATED_REPLY);

	अगर (skb_ensure_writable(skb, hdrlen + माप(*inside)))
		वापस 0;
	अगर (nf_ip6_checksum(skb, hooknum, hdrlen, IPPROTO_ICMPV6))
		वापस 0;

	inside = (व्योम *)skb->data + hdrlen;
	अगर (inside->icmp6.icmp6_type == NDISC_REसूचीECT) अणु
		अगर ((ct->status & IPS_NAT_DONE_MASK) != IPS_NAT_DONE_MASK)
			वापस 0;
		अगर (ct->status & IPS_NAT_MASK)
			वापस 0;
	पूर्ण

	अगर (manip == NF_NAT_MANIP_SRC)
		statusbit = IPS_SRC_NAT;
	अन्यथा
		statusbit = IPS_DST_NAT;

	/* Invert अगर this is reply direction */
	अगर (dir == IP_CT_सूची_REPLY)
		statusbit ^= IPS_NAT_MASK;

	अगर (!(ct->status & statusbit))
		वापस 1;

	अगर (!nf_nat_ipv6_manip_pkt(skb, hdrlen + माप(inside->icmp6),
				   &ct->tuplehash[!dir].tuple, !manip))
		वापस 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);

		inside = (व्योम *)skb->data + hdrlen;
		inside->icmp6.icmp6_cksum = 0;
		inside->icmp6.icmp6_cksum =
			csum_ipv6_magic(&ipv6h->saddr, &ipv6h->daddr,
					skb->len - hdrlen, IPPROTO_ICMPV6,
					skb_checksum(skb, hdrlen,
						     skb->len - hdrlen, 0));
	पूर्ण

	nf_ct_invert_tuple(&target, &ct->tuplehash[!dir].tuple);
	target.dst.protonum = IPPROTO_ICMPV6;
	अगर (!nf_nat_ipv6_manip_pkt(skb, 0, &target, manip))
		वापस 0;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_icmpv6_reply_translation);

अटल अचिन्हित पूर्णांक
nf_nat_ipv6_fn(व्योम *priv, काष्ठा sk_buff *skb,
	       स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	__be16 frag_off;
	पूर्णांक hdrlen;
	u8 nexthdr;

	ct = nf_ct_get(skb, &ctinfo);
	/* Can't track?  It's not due to stress, or conntrack would
	 * have dropped it.  Hence it's the user's responsibilty to
	 * packet filter it out, or implement conntrack/NAT क्रम that
	 * protocol. 8) --RR
	 */
	अगर (!ct)
		वापस NF_ACCEPT;

	अगर (ctinfo == IP_CT_RELATED || ctinfo == IP_CT_RELATED_REPLY) अणु
		nexthdr = ipv6_hdr(skb)->nexthdr;
		hdrlen = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr),
					  &nexthdr, &frag_off);

		अगर (hdrlen >= 0 && nexthdr == IPPROTO_ICMPV6) अणु
			अगर (!nf_nat_icmpv6_reply_translation(skb, ct, ctinfo,
							     state->hook,
							     hdrlen))
				वापस NF_DROP;
			अन्यथा
				वापस NF_ACCEPT;
		पूर्ण
	पूर्ण

	वापस nf_nat_inet_fn(priv, skb, state);
पूर्ण

अटल अचिन्हित पूर्णांक
nf_nat_ipv6_in(व्योम *priv, काष्ठा sk_buff *skb,
	       स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक ret;
	काष्ठा in6_addr daddr = ipv6_hdr(skb)->daddr;

	ret = nf_nat_ipv6_fn(priv, skb, state);
	अगर (ret != NF_DROP && ret != NF_STOLEN &&
	    ipv6_addr_cmp(&daddr, &ipv6_hdr(skb)->daddr))
		skb_dst_drop(skb);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
nf_nat_ipv6_out(व्योम *priv, काष्ठा sk_buff *skb,
		स्थिर काष्ठा nf_hook_state *state)
अणु
#अगर_घोषित CONFIG_XFRM
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	पूर्णांक err;
#पूर्ण_अगर
	अचिन्हित पूर्णांक ret;

	ret = nf_nat_ipv6_fn(priv, skb, state);
#अगर_घोषित CONFIG_XFRM
	अगर (ret != NF_ACCEPT)
		वापस ret;

	अगर (IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED)
		वापस ret;
	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);

		अगर (!nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3,
				      &ct->tuplehash[!dir].tuple.dst.u3) ||
		    (ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMPV6 &&
		     ct->tuplehash[dir].tuple.src.u.all !=
		     ct->tuplehash[!dir].tuple.dst.u.all)) अणु
			err = nf_xfrm_me_harder(state->net, skb, AF_INET6);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
nf_nat_ipv6_local_fn(व्योम *priv, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा nf_hook_state *state)
अणु
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	अचिन्हित पूर्णांक ret;
	पूर्णांक err;

	ret = nf_nat_ipv6_fn(priv, skb, state);
	अगर (ret != NF_ACCEPT)
		वापस ret;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);

		अगर (!nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.dst.u3,
				      &ct->tuplehash[!dir].tuple.src.u3)) अणु
			err = nf_ip6_route_me_harder(state->net, state->sk, skb);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
#अगर_घोषित CONFIG_XFRM
		अन्यथा अगर (!(IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED) &&
			 ct->tuplehash[dir].tuple.dst.protonum != IPPROTO_ICMPV6 &&
			 ct->tuplehash[dir].tuple.dst.u.all !=
			 ct->tuplehash[!dir].tuple.src.u.all) अणु
			err = nf_xfrm_me_harder(state->net, skb, AF_INET6);
			अगर (err < 0)
				ret = NF_DROP_ERR(err);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops nf_nat_ipv6_ops[] = अणु
	/* Beक्रमe packet filtering, change destination */
	अणु
		.hook		= nf_nat_ipv6_in,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP6_PRI_NAT_DST,
	पूर्ण,
	/* After packet filtering, change source */
	अणु
		.hook		= nf_nat_ipv6_out,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP6_PRI_NAT_SRC,
	पूर्ण,
	/* Beक्रमe packet filtering, change destination */
	अणु
		.hook		= nf_nat_ipv6_local_fn,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_NAT_DST,
	पूर्ण,
	/* After packet filtering, change source */
	अणु
		.hook		= nf_nat_ipv6_fn,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP6_PRI_NAT_SRC,
	पूर्ण,
पूर्ण;

पूर्णांक nf_nat_ipv6_रेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	वापस nf_nat_रेजिस्टर_fn(net, ops->pf, ops, nf_nat_ipv6_ops,
				  ARRAY_SIZE(nf_nat_ipv6_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_ipv6_रेजिस्टर_fn);

व्योम nf_nat_ipv6_unरेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	nf_nat_unरेजिस्टर_fn(net, ops->pf, ops, ARRAY_SIZE(nf_nat_ipv6_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_ipv6_unरेजिस्टर_fn);
#पूर्ण_अगर /* CONFIG_IPV6 */

#अगर defined(CONFIG_NF_TABLES_INET) && IS_ENABLED(CONFIG_NFT_NAT)
पूर्णांक nf_nat_inet_रेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(ops->pf != NFPROTO_INET))
		वापस -EINVAL;

	ret = nf_nat_रेजिस्टर_fn(net, NFPROTO_IPV6, ops, nf_nat_ipv6_ops,
				 ARRAY_SIZE(nf_nat_ipv6_ops));
	अगर (ret)
		वापस ret;

	ret = nf_nat_रेजिस्टर_fn(net, NFPROTO_IPV4, ops, nf_nat_ipv4_ops,
				 ARRAY_SIZE(nf_nat_ipv4_ops));
	अगर (ret)
		nf_nat_unरेजिस्टर_fn(net, NFPROTO_IPV6, ops,
					ARRAY_SIZE(nf_nat_ipv6_ops));
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_inet_रेजिस्टर_fn);

व्योम nf_nat_inet_unरेजिस्टर_fn(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops)
अणु
	nf_nat_unरेजिस्टर_fn(net, NFPROTO_IPV4, ops, ARRAY_SIZE(nf_nat_ipv4_ops));
	nf_nat_unरेजिस्टर_fn(net, NFPROTO_IPV6, ops, ARRAY_SIZE(nf_nat_ipv6_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_inet_unरेजिस्टर_fn);
#पूर्ण_अगर /* NFT INET NAT */
