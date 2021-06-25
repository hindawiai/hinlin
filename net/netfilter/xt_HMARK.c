<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xt_HMARK - Netfilter module to set mark by means of hashing
 *
 * (C) 2012 by Hans Schillstrom <hans.schillstrom@ericsson.com>
 * (C) 2012 by Pablo Neira Ayuso <pablo@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmp.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_HMARK.h>

#समावेश <net/ip.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
#समावेश <net/ipv6.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#पूर्ण_अगर

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hans Schillstrom <hans.schillstrom@ericsson.com>");
MODULE_DESCRIPTION("Xtables: packet marking using hash calculation");
MODULE_ALIAS("ipt_HMARK");
MODULE_ALIAS("ip6t_HMARK");

काष्ठा hmark_tuple अणु
	__be32			src;
	__be32			dst;
	जोड़ hmark_ports	uports;
	u8			proto;
पूर्ण;

अटल अंतरभूत __be32 hmark_addr6_mask(स्थिर __be32 *addr32, स्थिर __be32 *mask)
अणु
	वापस (addr32[0] & mask[0]) ^
	       (addr32[1] & mask[1]) ^
	       (addr32[2] & mask[2]) ^
	       (addr32[3] & mask[3]);
पूर्ण

अटल अंतरभूत __be32
hmark_addr_mask(पूर्णांक l3num, स्थिर __be32 *addr32, स्थिर __be32 *mask)
अणु
	चयन (l3num) अणु
	हाल AF_INET:
		वापस *addr32 & *mask;
	हाल AF_INET6:
		वापस hmark_addr6_mask(addr32, mask);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hmark_swap_ports(जोड़ hmark_ports *uports,
				    स्थिर काष्ठा xt_hmark_info *info)
अणु
	जोड़ hmark_ports hp;
	u16 src, dst;

	hp.b32 = (uports->b32 & info->port_mask.b32) | info->port_set.b32;
	src = ntohs(hp.b16.src);
	dst = ntohs(hp.b16.dst);

	अगर (dst > src)
		uports->v32 = (dst << 16) | src;
	अन्यथा
		uports->v32 = (src << 16) | dst;
पूर्ण

अटल पूर्णांक
hmark_ct_set_htuple(स्थिर काष्ठा sk_buff *skb, काष्ठा hmark_tuple *t,
		    स्थिर काष्ठा xt_hmark_info *info)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_conntrack_tuple *otuple;
	काष्ठा nf_conntrack_tuple *rtuple;

	अगर (ct == शून्य)
		वापस -1;

	otuple = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
	rtuple = &ct->tuplehash[IP_CT_सूची_REPLY].tuple;

	t->src = hmark_addr_mask(otuple->src.l3num, otuple->src.u3.ip6,
				 info->src_mask.ip6);
	t->dst = hmark_addr_mask(otuple->src.l3num, rtuple->src.u3.ip6,
				 info->dst_mask.ip6);

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_METHOD_L3))
		वापस 0;

	t->proto = nf_ct_protonum(ct);
	अगर (t->proto != IPPROTO_ICMP) अणु
		t->uports.b16.src = otuple->src.u.all;
		t->uports.b16.dst = rtuple->src.u.all;
		hmark_swap_ports(&t->uports, info);
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -1;
#पूर्ण_अगर
पूर्ण

/* This hash function is endian independent, to ensure consistent hashing अगर
 * the cluster is composed of big and little endian प्रणालीs. */
अटल अंतरभूत u32
hmark_hash(काष्ठा hmark_tuple *t, स्थिर काष्ठा xt_hmark_info *info)
अणु
	u32 hash;
	u32 src = ntohl(t->src);
	u32 dst = ntohl(t->dst);

	अगर (dst < src)
		swap(src, dst);

	hash = jhash_3words(src, dst, t->uports.v32, info->hashrnd);
	hash = hash ^ (t->proto & info->proto_mask);

	वापस reciprocal_scale(hash, info->hmodulus) + info->hoffset;
पूर्ण

अटल व्योम
hmark_set_tuple_ports(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nhoff,
		      काष्ठा hmark_tuple *t, स्थिर काष्ठा xt_hmark_info *info)
अणु
	पूर्णांक protoff;

	protoff = proto_ports_offset(t->proto);
	अगर (protoff < 0)
		वापस;

	nhoff += protoff;
	अगर (skb_copy_bits(skb, nhoff, &t->uports, माप(t->uports)) < 0)
		वापस;

	hmark_swap_ports(&t->uports, info);
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल पूर्णांक get_inner6_hdr(स्थिर काष्ठा sk_buff *skb, पूर्णांक *offset)
अणु
	काष्ठा icmp6hdr *icmp6h, _ih6;

	icmp6h = skb_header_poपूर्णांकer(skb, *offset, माप(_ih6), &_ih6);
	अगर (icmp6h == शून्य)
		वापस 0;

	अगर (icmp6h->icmp6_type && icmp6h->icmp6_type < 128) अणु
		*offset += माप(काष्ठा icmp6hdr);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
hmark_pkt_set_htuple_ipv6(स्थिर काष्ठा sk_buff *skb, काष्ठा hmark_tuple *t,
			  स्थिर काष्ठा xt_hmark_info *info)
अणु
	काष्ठा ipv6hdr *ip6, _ip6;
	पूर्णांक flag = IP6_FH_F_AUTH;
	अचिन्हित पूर्णांक nhoff = 0;
	u16 fragoff = 0;
	पूर्णांक nexthdr;

	ip6 = (काष्ठा ipv6hdr *) (skb->data + skb_network_offset(skb));
	nexthdr = ipv6_find_hdr(skb, &nhoff, -1, &fragoff, &flag);
	अगर (nexthdr < 0)
		वापस 0;
	/* No need to check क्रम icmp errors on fragments */
	अगर ((flag & IP6_FH_F_FRAG) || (nexthdr != IPPROTO_ICMPV6))
		जाओ noicmp;
	/* Use inner header in हाल of ICMP errors */
	अगर (get_inner6_hdr(skb, &nhoff)) अणु
		ip6 = skb_header_poपूर्णांकer(skb, nhoff, माप(_ip6), &_ip6);
		अगर (ip6 == शून्य)
			वापस -1;
		/* If AH present, use SPI like in ESP. */
		flag = IP6_FH_F_AUTH;
		nexthdr = ipv6_find_hdr(skb, &nhoff, -1, &fragoff, &flag);
		अगर (nexthdr < 0)
			वापस -1;
	पूर्ण
noicmp:
	t->src = hmark_addr6_mask(ip6->saddr.s6_addr32, info->src_mask.ip6);
	t->dst = hmark_addr6_mask(ip6->daddr.s6_addr32, info->dst_mask.ip6);

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_METHOD_L3))
		वापस 0;

	t->proto = nexthdr;
	अगर (t->proto == IPPROTO_ICMPV6)
		वापस 0;

	अगर (flag & IP6_FH_F_FRAG)
		वापस 0;

	hmark_set_tuple_ports(skb, nhoff, t, info);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
hmark_tg_v6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_hmark_info *info = par->targinfo;
	काष्ठा hmark_tuple t;

	स_रखो(&t, 0, माप(काष्ठा hmark_tuple));

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_CT)) अणु
		अगर (hmark_ct_set_htuple(skb, &t, info) < 0)
			वापस XT_CONTINUE;
	पूर्ण अन्यथा अणु
		अगर (hmark_pkt_set_htuple_ipv6(skb, &t, info) < 0)
			वापस XT_CONTINUE;
	पूर्ण

	skb->mark = hmark_hash(&t, info);
	वापस XT_CONTINUE;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_inner_hdr(स्थिर काष्ठा sk_buff *skb, पूर्णांक iphsz, पूर्णांक *nhoff)
अणु
	स्थिर काष्ठा icmphdr *icmph;
	काष्ठा icmphdr _ih;

	/* Not enough header? */
	icmph = skb_header_poपूर्णांकer(skb, *nhoff + iphsz, माप(_ih), &_ih);
	अगर (icmph == शून्य || icmph->type > NR_ICMP_TYPES)
		वापस 0;

	/* Error message? */
	अगर (!icmp_is_err(icmph->type))
		वापस 0;

	*nhoff += iphsz + माप(_ih);
	वापस 1;
पूर्ण

अटल पूर्णांक
hmark_pkt_set_htuple_ipv4(स्थिर काष्ठा sk_buff *skb, काष्ठा hmark_tuple *t,
			  स्थिर काष्ठा xt_hmark_info *info)
अणु
	काष्ठा iphdr *ip, _ip;
	पूर्णांक nhoff = skb_network_offset(skb);

	ip = (काष्ठा iphdr *) (skb->data + nhoff);
	अगर (ip->protocol == IPPROTO_ICMP) अणु
		/* Use inner header in हाल of ICMP errors */
		अगर (get_inner_hdr(skb, ip->ihl * 4, &nhoff)) अणु
			ip = skb_header_poपूर्णांकer(skb, nhoff, माप(_ip), &_ip);
			अगर (ip == शून्य)
				वापस -1;
		पूर्ण
	पूर्ण

	t->src = ip->saddr & info->src_mask.ip;
	t->dst = ip->daddr & info->dst_mask.ip;

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_METHOD_L3))
		वापस 0;

	t->proto = ip->protocol;

	/* ICMP has no ports, skip */
	अगर (t->proto == IPPROTO_ICMP)
		वापस 0;

	/* follow-up fragments करोn't contain ports, skip all fragments */
	अगर (ip_is_fragment(ip))
		वापस 0;

	hmark_set_tuple_ports(skb, (ip->ihl * 4) + nhoff, t, info);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
hmark_tg_v4(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_hmark_info *info = par->targinfo;
	काष्ठा hmark_tuple t;

	स_रखो(&t, 0, माप(काष्ठा hmark_tuple));

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_CT)) अणु
		अगर (hmark_ct_set_htuple(skb, &t, info) < 0)
			वापस XT_CONTINUE;
	पूर्ण अन्यथा अणु
		अगर (hmark_pkt_set_htuple_ipv4(skb, &t, info) < 0)
			वापस XT_CONTINUE;
	पूर्ण

	skb->mark = hmark_hash(&t, info);
	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक hmark_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_hmark_info *info = par->targinfo;
	स्थिर अक्षर *errmsg = "proto mask must be zero with L3 mode";

	अगर (!info->hmodulus)
		वापस -EINVAL;

	अगर (info->proto_mask &&
	    (info->flags & XT_HMARK_FLAG(XT_HMARK_METHOD_L3)))
		जाओ err;

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_SPI_MASK) &&
	    (info->flags & (XT_HMARK_FLAG(XT_HMARK_SPORT_MASK) |
			     XT_HMARK_FLAG(XT_HMARK_DPORT_MASK))))
		वापस -EINVAL;

	अगर (info->flags & XT_HMARK_FLAG(XT_HMARK_SPI) &&
	    (info->flags & (XT_HMARK_FLAG(XT_HMARK_SPORT) |
			     XT_HMARK_FLAG(XT_HMARK_DPORT)))) अणु
		errmsg = "spi-set and port-set can't be combined";
		जाओ err;
	पूर्ण
	वापस 0;
err:
	pr_info_ratelimited("%s\n", errmsg);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा xt_target hmark_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "HMARK",
		.family		= NFPROTO_IPV4,
		.target		= hmark_tg_v4,
		.tarमाला_लोize	= माप(काष्ठा xt_hmark_info),
		.checkentry	= hmark_tg_check,
		.me		= THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name		= "HMARK",
		.family		= NFPROTO_IPV6,
		.target		= hmark_tg_v6,
		.tarमाला_लोize	= माप(काष्ठा xt_hmark_info),
		.checkentry	= hmark_tg_check,
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init hmark_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(hmark_tg_reg, ARRAY_SIZE(hmark_tg_reg));
पूर्ण

अटल व्योम __निकास hmark_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(hmark_tg_reg, ARRAY_SIZE(hmark_tg_reg));
पूर्ण

module_init(hmark_tg_init);
module_निकास(hmark_tg_निकास);
