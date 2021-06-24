<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org> */

/* Kernel module implementing an IP set type: the hash:ip,port,net type */

#समावेश <linux/jhash.h>
#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/netlink.h>
#समावेश <net/tcp.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/ipset/pfxlen.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_getport.h>
#समावेश <linux/netfilter/ipset/ip_set_hash.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1    SCTP and UDPLITE support added */
/*				2    Range as input support क्रम IPv4 added */
/*				3    nomatch flag support added */
/*				4    Counters support added */
/*				5    Comments support added */
/*				6    Forceadd support added */
/*				7    skbinfo support added */
#घोषणा IPSET_TYPE_REV_MAX	8 /* bucketsize, initval support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("hash:ip,port,net", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_hash:ip,port,net");

/* Type specअगरic function prefix */
#घोषणा HTYPE		hash_ipportnet

/* We squeeze the "nomatch" flag पूर्णांकo cidr: we करोn't support cidr == 0
 * However this way we have to store पूर्णांकernally cidr - 1,
 * dancing back and क्रमth.
 */
#घोषणा IP_SET_HASH_WITH_NETS_PACKED
#घोषणा IP_SET_HASH_WITH_PROTO
#घोषणा IP_SET_HASH_WITH_NETS

/* IPv4 variant */

/* Member elements */
काष्ठा hash_ipportnet4_elem अणु
	__be32 ip;
	__be32 ip2;
	__be16 port;
	u8 cidr:7;
	u8 nomatch:1;
	u8 proto;
पूर्ण;

/* Common functions */

अटल bool
hash_ipportnet4_data_equal(स्थिर काष्ठा hash_ipportnet4_elem *ip1,
			   स्थिर काष्ठा hash_ipportnet4_elem *ip2,
			   u32 *multi)
अणु
	वापस ip1->ip == ip2->ip &&
	       ip1->ip2 == ip2->ip2 &&
	       ip1->cidr == ip2->cidr &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto;
पूर्ण

अटल पूर्णांक
hash_ipportnet4_करो_data_match(स्थिर काष्ठा hash_ipportnet4_elem *elem)
अणु
	वापस elem->nomatch ? -ENOTEMPTY : 1;
पूर्ण

अटल व्योम
hash_ipportnet4_data_set_flags(काष्ठा hash_ipportnet4_elem *elem, u32 flags)
अणु
	elem->nomatch = !!((flags >> 16) & IPSET_FLAG_NOMATCH);
पूर्ण

अटल व्योम
hash_ipportnet4_data_reset_flags(काष्ठा hash_ipportnet4_elem *elem, u8 *flags)
अणु
	swap(*flags, elem->nomatch);
पूर्ण

अटल व्योम
hash_ipportnet4_data_neपंचांगask(काष्ठा hash_ipportnet4_elem *elem, u8 cidr)
अणु
	elem->ip2 &= ip_set_neपंचांगask(cidr);
	elem->cidr = cidr - 1;
पूर्ण

अटल bool
hash_ipportnet4_data_list(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा hash_ipportnet4_elem *data)
अणु
	u32 flags = data->nomatch ? IPSET_FLAG_NOMATCH : 0;

	अगर (nla_put_ipaddr4(skb, IPSET_ATTR_IP, data->ip) ||
	    nla_put_ipaddr4(skb, IPSET_ATTR_IP2, data->ip2) ||
	    nla_put_net16(skb, IPSET_ATTR_PORT, data->port) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR2, data->cidr + 1) ||
	    nla_put_u8(skb, IPSET_ATTR_PROTO, data->proto) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_ipportnet4_data_next(काष्ठा hash_ipportnet4_elem *next,
			  स्थिर काष्ठा hash_ipportnet4_elem *d)
अणु
	next->ip = d->ip;
	next->port = d->port;
	next->ip2 = d->ip2;
पूर्ण

#घोषणा MTYPE		hash_ipportnet4
#घोषणा HOST_MASK	32
#समावेश "ip_set_hash_gen.h"

अटल पूर्णांक
hash_ipportnet4_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		     स्थिर काष्ठा xt_action_param *par,
		     क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	स्थिर काष्ठा hash_ipportnet4 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_ipportnet4_elem e = अणु
		.cidr = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK),
	पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	अगर (adt == IPSET_TEST)
		e.cidr = HOST_MASK - 1;

	अगर (!ip_set_get_ip4_port(skb, opt->flags & IPSET_DIM_TWO_SRC,
				 &e.port, &e.proto))
		वापस -EINVAL;

	ip4addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip);
	ip4addrptr(skb, opt->flags & IPSET_DIM_THREE_SRC, &e.ip2);
	e.ip2 &= ip_set_neपंचांगask(e.cidr + 1);

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_ipportnet4_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		     क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	स्थिर काष्ठा hash_ipportnet4 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_ipportnet4_elem e = अणु .cidr = HOST_MASK - 1 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0, p = 0, port, port_to;
	u32 ip2_from = 0, ip2_to = 0, ip2;
	bool with_ports = false;
	u8 cidr;
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_IP] || !tb[IPSET_ATTR_IP2] ||
		     !ip_set_attr_netorder(tb, IPSET_ATTR_PORT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_PORT_TO) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP], &ip);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP2], &ip2_from);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_CIDR2]) अणु
		cidr = nla_get_u8(tb[IPSET_ATTR_CIDR2]);
		अगर (!cidr || cidr > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
		e.cidr = cidr - 1;
	पूर्ण

	e.port = nla_get_be16(tb[IPSET_ATTR_PORT]);

	अगर (tb[IPSET_ATTR_PROTO]) अणु
		e.proto = nla_get_u8(tb[IPSET_ATTR_PROTO]);
		with_ports = ip_set_proto_with_ports(e.proto);

		अगर (e.proto == 0)
			वापस -IPSET_ERR_INVALID_PROTO;
	पूर्ण अन्यथा अणु
		वापस -IPSET_ERR_MISSING_PROTO;
	पूर्ण

	अगर (!(with_ports || e.proto == IPPROTO_ICMP))
		e.port = 0;

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		अगर (cadt_flags & IPSET_FLAG_NOMATCH)
			flags |= (IPSET_FLAG_NOMATCH << 16);
	पूर्ण

	with_ports = with_ports && tb[IPSET_ATTR_PORT_TO];
	अगर (adt == IPSET_TEST ||
	    !(tb[IPSET_ATTR_CIDR] || tb[IPSET_ATTR_IP_TO] || with_ports ||
	      tb[IPSET_ATTR_IP2_TO])) अणु
		e.ip = htonl(ip);
		e.ip2 = htonl(ip2_from & ip_set_hosपंचांगask(e.cidr + 1));
		ret = adtfn(set, &e, &ext, &ext, flags);
		वापस ip_set_enomatch(ret, flags, adt, set) ? -ret :
		       ip_set_eexist(ret, flags) ? 0 : ret;
	पूर्ण

	ip_to = ip;
	अगर (tb[IPSET_ATTR_IP_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP_TO], &ip_to);
		अगर (ret)
			वापस ret;
		अगर (ip > ip_to)
			swap(ip, ip_to);
	पूर्ण अन्यथा अगर (tb[IPSET_ATTR_CIDR]) अणु
		cidr = nla_get_u8(tb[IPSET_ATTR_CIDR]);

		अगर (!cidr || cidr > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
		ip_set_mask_from_to(ip, ip_to, cidr);
	पूर्ण

	port_to = port = ntohs(e.port);
	अगर (tb[IPSET_ATTR_PORT_TO]) अणु
		port_to = ip_set_get_h16(tb[IPSET_ATTR_PORT_TO]);
		अगर (port > port_to)
			swap(port, port_to);
	पूर्ण

	ip2_to = ip2_from;
	अगर (tb[IPSET_ATTR_IP2_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP2_TO], &ip2_to);
		अगर (ret)
			वापस ret;
		अगर (ip2_from > ip2_to)
			swap(ip2_from, ip2_to);
		अगर (ip2_from + अच_पूर्णांक_उच्च == ip2_to)
			वापस -IPSET_ERR_HASH_RANGE;
	पूर्ण अन्यथा अणु
		ip_set_mask_from_to(ip2_from, ip2_to, e.cidr + 1);
	पूर्ण

	अगर (retried) अणु
		ip = ntohl(h->next.ip);
		p = ntohs(h->next.port);
		ip2 = ntohl(h->next.ip2);
	पूर्ण अन्यथा अणु
		p = port;
		ip2 = ip2_from;
	पूर्ण
	क्रम (; ip <= ip_to; ip++) अणु
		e.ip = htonl(ip);
		क्रम (; p <= port_to; p++) अणु
			e.port = htons(p);
			करो अणु
				e.ip2 = htonl(ip2);
				ip2 = ip_set_range_to_cidr(ip2, ip2_to, &cidr);
				e.cidr = cidr - 1;
				ret = adtfn(set, &e, &ext, &ext, flags);

				अगर (ret && !ip_set_eexist(ret, flags))
					वापस ret;

				ret = 0;
			पूर्ण जबतक (ip2++ < ip2_to);
			ip2 = ip2_from;
		पूर्ण
		p = port;
	पूर्ण
	वापस ret;
पूर्ण

/* IPv6 variant */

काष्ठा hash_ipportnet6_elem अणु
	जोड़ nf_inet_addr ip;
	जोड़ nf_inet_addr ip2;
	__be16 port;
	u8 cidr:7;
	u8 nomatch:1;
	u8 proto;
पूर्ण;

/* Common functions */

अटल bool
hash_ipportnet6_data_equal(स्थिर काष्ठा hash_ipportnet6_elem *ip1,
			   स्थिर काष्ठा hash_ipportnet6_elem *ip2,
			   u32 *multi)
अणु
	वापस ipv6_addr_equal(&ip1->ip.in6, &ip2->ip.in6) &&
	       ipv6_addr_equal(&ip1->ip2.in6, &ip2->ip2.in6) &&
	       ip1->cidr == ip2->cidr &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto;
पूर्ण

अटल पूर्णांक
hash_ipportnet6_करो_data_match(स्थिर काष्ठा hash_ipportnet6_elem *elem)
अणु
	वापस elem->nomatch ? -ENOTEMPTY : 1;
पूर्ण

अटल व्योम
hash_ipportnet6_data_set_flags(काष्ठा hash_ipportnet6_elem *elem, u32 flags)
अणु
	elem->nomatch = !!((flags >> 16) & IPSET_FLAG_NOMATCH);
पूर्ण

अटल व्योम
hash_ipportnet6_data_reset_flags(काष्ठा hash_ipportnet6_elem *elem, u8 *flags)
अणु
	swap(*flags, elem->nomatch);
पूर्ण

अटल व्योम
hash_ipportnet6_data_neपंचांगask(काष्ठा hash_ipportnet6_elem *elem, u8 cidr)
अणु
	ip6_neपंचांगask(&elem->ip2, cidr);
	elem->cidr = cidr - 1;
पूर्ण

अटल bool
hash_ipportnet6_data_list(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा hash_ipportnet6_elem *data)
अणु
	u32 flags = data->nomatch ? IPSET_FLAG_NOMATCH : 0;

	अगर (nla_put_ipaddr6(skb, IPSET_ATTR_IP, &data->ip.in6) ||
	    nla_put_ipaddr6(skb, IPSET_ATTR_IP2, &data->ip2.in6) ||
	    nla_put_net16(skb, IPSET_ATTR_PORT, data->port) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR2, data->cidr + 1) ||
	    nla_put_u8(skb, IPSET_ATTR_PROTO, data->proto) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_ipportnet6_data_next(काष्ठा hash_ipportnet6_elem *next,
			  स्थिर काष्ठा hash_ipportnet6_elem *d)
अणु
	next->port = d->port;
पूर्ण

#अघोषित MTYPE
#अघोषित HOST_MASK

#घोषणा MTYPE		hash_ipportnet6
#घोषणा HOST_MASK	128
#घोषणा IP_SET_EMIT_CREATE
#समावेश "ip_set_hash_gen.h"

अटल पूर्णांक
hash_ipportnet6_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		     स्थिर काष्ठा xt_action_param *par,
		     क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	स्थिर काष्ठा hash_ipportnet6 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_ipportnet6_elem e = अणु
		.cidr = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK),
	पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	अगर (adt == IPSET_TEST)
		e.cidr = HOST_MASK - 1;

	अगर (!ip_set_get_ip6_port(skb, opt->flags & IPSET_DIM_TWO_SRC,
				 &e.port, &e.proto))
		वापस -EINVAL;

	ip6addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip.in6);
	ip6addrptr(skb, opt->flags & IPSET_DIM_THREE_SRC, &e.ip2.in6);
	ip6_neपंचांगask(&e.ip2, e.cidr + 1);

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_ipportnet6_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		     क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	स्थिर काष्ठा hash_ipportnet6 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_ipportnet6_elem e = अणु .cidr = HOST_MASK - 1 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 port, port_to;
	bool with_ports = false;
	u8 cidr;
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_IP] || !tb[IPSET_ATTR_IP2] ||
		     !ip_set_attr_netorder(tb, IPSET_ATTR_PORT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_PORT_TO) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;
	अगर (unlikely(tb[IPSET_ATTR_IP_TO]))
		वापस -IPSET_ERR_HASH_RANGE_UNSUPPORTED;
	अगर (unlikely(tb[IPSET_ATTR_CIDR])) अणु
		cidr = nla_get_u8(tb[IPSET_ATTR_CIDR]);

		अगर (cidr != HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण

	ret = ip_set_get_ipaddr6(tb[IPSET_ATTR_IP], &e.ip);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_ipaddr6(tb[IPSET_ATTR_IP2], &e.ip2);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_CIDR2]) अणु
		cidr = nla_get_u8(tb[IPSET_ATTR_CIDR2]);
		अगर (!cidr || cidr > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
		e.cidr = cidr - 1;
	पूर्ण

	ip6_neपंचांगask(&e.ip2, e.cidr + 1);

	e.port = nla_get_be16(tb[IPSET_ATTR_PORT]);

	अगर (tb[IPSET_ATTR_PROTO]) अणु
		e.proto = nla_get_u8(tb[IPSET_ATTR_PROTO]);
		with_ports = ip_set_proto_with_ports(e.proto);

		अगर (e.proto == 0)
			वापस -IPSET_ERR_INVALID_PROTO;
	पूर्ण अन्यथा अणु
		वापस -IPSET_ERR_MISSING_PROTO;
	पूर्ण

	अगर (!(with_ports || e.proto == IPPROTO_ICMPV6))
		e.port = 0;

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		अगर (cadt_flags & IPSET_FLAG_NOMATCH)
			flags |= (IPSET_FLAG_NOMATCH << 16);
	पूर्ण

	अगर (adt == IPSET_TEST || !with_ports || !tb[IPSET_ATTR_PORT_TO]) अणु
		ret = adtfn(set, &e, &ext, &ext, flags);
		वापस ip_set_enomatch(ret, flags, adt, set) ? -ret :
		       ip_set_eexist(ret, flags) ? 0 : ret;
	पूर्ण

	port = ntohs(e.port);
	port_to = ip_set_get_h16(tb[IPSET_ATTR_PORT_TO]);
	अगर (port > port_to)
		swap(port, port_to);

	अगर (retried)
		port = ntohs(h->next.port);
	क्रम (; port <= port_to; port++) अणु
		e.port = htons(port);
		ret = adtfn(set, &e, &ext, &ext, flags);

		अगर (ret && !ip_set_eexist(ret, flags))
			वापस ret;

		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा ip_set_type hash_ipportnet_type __पढ़ो_mostly = अणु
	.name		= "hash:ip,port,net",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_IP | IPSET_TYPE_PORT | IPSET_TYPE_IP2 |
			  IPSET_TYPE_NOMATCH,
	.dimension	= IPSET_DIM_THREE,
	.family		= NFPROTO_UNSPEC,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create_flags[IPSET_TYPE_REV_MAX] = IPSET_CREATE_FLAG_BUCKETSIZE,
	.create		= hash_ipportnet_create,
	.create_policy	= अणु
		[IPSET_ATTR_HASHSIZE]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_MAXELEM]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_INITVAL]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_BUCKETSIZE]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_RESIZE]	= अणु .type = NLA_U8  पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	पूर्ण,
	.adt_policy	= अणु
		[IPSET_ATTR_IP]		= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP_TO]	= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP2]	= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP2_TO]	= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_PORT]	= अणु .type = NLA_U16 पूर्ण,
		[IPSET_ATTR_PORT_TO]	= अणु .type = NLA_U16 पूर्ण,
		[IPSET_ATTR_CIDR]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_CIDR2]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_PROTO]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_LINENO]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_BYTES]	= अणु .type = NLA_U64 पूर्ण,
		[IPSET_ATTR_PACKETS]	= अणु .type = NLA_U64 पूर्ण,
		[IPSET_ATTR_COMMENT]	= अणु .type = NLA_NUL_STRING,
					    .len  = IPSET_MAX_COMMENT_SIZE पूर्ण,
		[IPSET_ATTR_SKBMARK]	= अणु .type = NLA_U64 पूर्ण,
		[IPSET_ATTR_SKBPRIO]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_SKBQUEUE]	= अणु .type = NLA_U16 पूर्ण,
	पूर्ण,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init
hash_ipportnet_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&hash_ipportnet_type);
पूर्ण

अटल व्योम __निकास
hash_ipportnet_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&hash_ipportnet_type);
पूर्ण

module_init(hash_ipportnet_init);
module_निकास(hash_ipportnet_fini);
