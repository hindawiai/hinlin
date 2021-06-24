<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org>
 * Copyright (C) 2013 Oliver Smith <oliver@8.c.9.b.0.7.4.0.1.0.0.2.ip6.arpa>
 */

/* Kernel module implementing an IP set type: the hash:net type */

#समावेश <linux/jhash.h>
#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/netlink.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/ipset/pfxlen.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_hash.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1	   Forceadd support added */
/*				2	   skbinfo support added */
#घोषणा IPSET_TYPE_REV_MAX	3	/* bucketsize, initval support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oliver Smith <oliver@8.c.9.b.0.7.4.0.1.0.0.2.ip6.arpa>");
IP_SET_MODULE_DESC("hash:net,net", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_hash:net,net");

/* Type specअगरic function prefix */
#घोषणा HTYPE		hash_netnet
#घोषणा IP_SET_HASH_WITH_NETS
#घोषणा IPSET_NET_COUNT 2

/* IPv4 variants */

/* Member elements  */
काष्ठा hash_netnet4_elem अणु
	जोड़ अणु
		__be32 ip[2];
		__be64 ipcmp;
	पूर्ण;
	u8 nomatch;
	u8 padding;
	जोड़ अणु
		u8 cidr[2];
		u16 ccmp;
	पूर्ण;
पूर्ण;

/* Common functions */

अटल bool
hash_netnet4_data_equal(स्थिर काष्ठा hash_netnet4_elem *ip1,
			स्थिर काष्ठा hash_netnet4_elem *ip2,
			u32 *multi)
अणु
	वापस ip1->ipcmp == ip2->ipcmp &&
	       ip1->ccmp == ip2->ccmp;
पूर्ण

अटल पूर्णांक
hash_netnet4_करो_data_match(स्थिर काष्ठा hash_netnet4_elem *elem)
अणु
	वापस elem->nomatch ? -ENOTEMPTY : 1;
पूर्ण

अटल व्योम
hash_netnet4_data_set_flags(काष्ठा hash_netnet4_elem *elem, u32 flags)
अणु
	elem->nomatch = (flags >> 16) & IPSET_FLAG_NOMATCH;
पूर्ण

अटल व्योम
hash_netnet4_data_reset_flags(काष्ठा hash_netnet4_elem *elem, u8 *flags)
अणु
	swap(*flags, elem->nomatch);
पूर्ण

अटल व्योम
hash_netnet4_data_reset_elem(काष्ठा hash_netnet4_elem *elem,
			     काष्ठा hash_netnet4_elem *orig)
अणु
	elem->ip[1] = orig->ip[1];
पूर्ण

अटल व्योम
hash_netnet4_data_neपंचांगask(काष्ठा hash_netnet4_elem *elem, u8 cidr, bool inner)
अणु
	अगर (inner) अणु
		elem->ip[1] &= ip_set_neपंचांगask(cidr);
		elem->cidr[1] = cidr;
	पूर्ण अन्यथा अणु
		elem->ip[0] &= ip_set_neपंचांगask(cidr);
		elem->cidr[0] = cidr;
	पूर्ण
पूर्ण

अटल bool
hash_netnet4_data_list(काष्ठा sk_buff *skb,
		       स्थिर काष्ठा hash_netnet4_elem *data)
अणु
	u32 flags = data->nomatch ? IPSET_FLAG_NOMATCH : 0;

	अगर (nla_put_ipaddr4(skb, IPSET_ATTR_IP, data->ip[0]) ||
	    nla_put_ipaddr4(skb, IPSET_ATTR_IP2, data->ip[1]) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR, data->cidr[0]) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR2, data->cidr[1]) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_netnet4_data_next(काष्ठा hash_netnet4_elem *next,
		       स्थिर काष्ठा hash_netnet4_elem *d)
अणु
	next->ipcmp = d->ipcmp;
पूर्ण

#घोषणा MTYPE		hash_netnet4
#घोषणा HOST_MASK	32
#समावेश "ip_set_hash_gen.h"

अटल व्योम
hash_netnet4_init(काष्ठा hash_netnet4_elem *e)
अणु
	e->cidr[0] = HOST_MASK;
	e->cidr[1] = HOST_MASK;
पूर्ण

अटल पूर्णांक
hash_netnet4_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		  स्थिर काष्ठा xt_action_param *par,
		  क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	स्थिर काष्ठा hash_netnet4 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netnet4_elem e = अणु पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	e.cidr[0] = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK);
	e.cidr[1] = INIT_CIDR(h->nets[0].cidr[1], HOST_MASK);
	अगर (adt == IPSET_TEST)
		e.ccmp = (HOST_MASK << (माप(e.cidr[0]) * 8)) | HOST_MASK;

	ip4addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip[0]);
	ip4addrptr(skb, opt->flags & IPSET_DIM_TWO_SRC, &e.ip[1]);
	e.ip[0] &= ip_set_neपंचांगask(e.cidr[0]);
	e.ip[1] &= ip_set_neपंचांगask(e.cidr[1]);

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_netnet4_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		  क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	स्थिर काष्ठा hash_netnet4 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netnet4_elem e = अणु पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0;
	u32 ip2 = 0, ip2_from = 0, ip2_to = 0;
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	hash_netnet4_init(&e);
	अगर (unlikely(!tb[IPSET_ATTR_IP] || !tb[IPSET_ATTR_IP2] ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP], &ip);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP2], &ip2_from);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_CIDR]) अणु
		e.cidr[0] = nla_get_u8(tb[IPSET_ATTR_CIDR]);
		अगर (!e.cidr[0] || e.cidr[0] > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण

	अगर (tb[IPSET_ATTR_CIDR2]) अणु
		e.cidr[1] = nla_get_u8(tb[IPSET_ATTR_CIDR2]);
		अगर (!e.cidr[1] || e.cidr[1] > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		अगर (cadt_flags & IPSET_FLAG_NOMATCH)
			flags |= (IPSET_FLAG_NOMATCH << 16);
	पूर्ण

	अगर (adt == IPSET_TEST || !(tb[IPSET_ATTR_IP_TO] ||
				   tb[IPSET_ATTR_IP2_TO])) अणु
		e.ip[0] = htonl(ip & ip_set_hosपंचांगask(e.cidr[0]));
		e.ip[1] = htonl(ip2_from & ip_set_hosपंचांगask(e.cidr[1]));
		ret = adtfn(set, &e, &ext, &ext, flags);
		वापस ip_set_enomatch(ret, flags, adt, set) ? -ret :
		       ip_set_eexist(ret, flags) ? 0 : ret;
	पूर्ण

	ip_to = ip;
	अगर (tb[IPSET_ATTR_IP_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP_TO], &ip_to);
		अगर (ret)
			वापस ret;
		अगर (ip_to < ip)
			swap(ip, ip_to);
		अगर (unlikely(ip + अच_पूर्णांक_उच्च == ip_to))
			वापस -IPSET_ERR_HASH_RANGE;
	पूर्ण अन्यथा अणु
		ip_set_mask_from_to(ip, ip_to, e.cidr[0]);
	पूर्ण

	ip2_to = ip2_from;
	अगर (tb[IPSET_ATTR_IP2_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP2_TO], &ip2_to);
		अगर (ret)
			वापस ret;
		अगर (ip2_to < ip2_from)
			swap(ip2_from, ip2_to);
		अगर (unlikely(ip2_from + अच_पूर्णांक_उच्च == ip2_to))
			वापस -IPSET_ERR_HASH_RANGE;
	पूर्ण अन्यथा अणु
		ip_set_mask_from_to(ip2_from, ip2_to, e.cidr[1]);
	पूर्ण

	अगर (retried) अणु
		ip = ntohl(h->next.ip[0]);
		ip2 = ntohl(h->next.ip[1]);
	पूर्ण अन्यथा अणु
		ip2 = ip2_from;
	पूर्ण

	करो अणु
		e.ip[0] = htonl(ip);
		ip = ip_set_range_to_cidr(ip, ip_to, &e.cidr[0]);
		करो अणु
			e.ip[1] = htonl(ip2);
			ip2 = ip_set_range_to_cidr(ip2, ip2_to, &e.cidr[1]);
			ret = adtfn(set, &e, &ext, &ext, flags);
			अगर (ret && !ip_set_eexist(ret, flags))
				वापस ret;

			ret = 0;
		पूर्ण जबतक (ip2++ < ip2_to);
		ip2 = ip2_from;
	पूर्ण जबतक (ip++ < ip_to);
	वापस ret;
पूर्ण

/* IPv6 variants */

काष्ठा hash_netnet6_elem अणु
	जोड़ nf_inet_addr ip[2];
	u8 nomatch;
	u8 padding;
	जोड़ अणु
		u8 cidr[2];
		u16 ccmp;
	पूर्ण;
पूर्ण;

/* Common functions */

अटल bool
hash_netnet6_data_equal(स्थिर काष्ठा hash_netnet6_elem *ip1,
			स्थिर काष्ठा hash_netnet6_elem *ip2,
			u32 *multi)
अणु
	वापस ipv6_addr_equal(&ip1->ip[0].in6, &ip2->ip[0].in6) &&
	       ipv6_addr_equal(&ip1->ip[1].in6, &ip2->ip[1].in6) &&
	       ip1->ccmp == ip2->ccmp;
पूर्ण

अटल पूर्णांक
hash_netnet6_करो_data_match(स्थिर काष्ठा hash_netnet6_elem *elem)
अणु
	वापस elem->nomatch ? -ENOTEMPTY : 1;
पूर्ण

अटल व्योम
hash_netnet6_data_set_flags(काष्ठा hash_netnet6_elem *elem, u32 flags)
अणु
	elem->nomatch = (flags >> 16) & IPSET_FLAG_NOMATCH;
पूर्ण

अटल व्योम
hash_netnet6_data_reset_flags(काष्ठा hash_netnet6_elem *elem, u8 *flags)
अणु
	swap(*flags, elem->nomatch);
पूर्ण

अटल व्योम
hash_netnet6_data_reset_elem(काष्ठा hash_netnet6_elem *elem,
			     काष्ठा hash_netnet6_elem *orig)
अणु
	elem->ip[1] = orig->ip[1];
पूर्ण

अटल व्योम
hash_netnet6_data_neपंचांगask(काष्ठा hash_netnet6_elem *elem, u8 cidr, bool inner)
अणु
	अगर (inner) अणु
		ip6_neपंचांगask(&elem->ip[1], cidr);
		elem->cidr[1] = cidr;
	पूर्ण अन्यथा अणु
		ip6_neपंचांगask(&elem->ip[0], cidr);
		elem->cidr[0] = cidr;
	पूर्ण
पूर्ण

अटल bool
hash_netnet6_data_list(काष्ठा sk_buff *skb,
		       स्थिर काष्ठा hash_netnet6_elem *data)
अणु
	u32 flags = data->nomatch ? IPSET_FLAG_NOMATCH : 0;

	अगर (nla_put_ipaddr6(skb, IPSET_ATTR_IP, &data->ip[0].in6) ||
	    nla_put_ipaddr6(skb, IPSET_ATTR_IP2, &data->ip[1].in6) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR, data->cidr[0]) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR2, data->cidr[1]) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_netnet6_data_next(काष्ठा hash_netnet6_elem *next,
		       स्थिर काष्ठा hash_netnet6_elem *d)
अणु
पूर्ण

#अघोषित MTYPE
#अघोषित HOST_MASK

#घोषणा MTYPE		hash_netnet6
#घोषणा HOST_MASK	128
#घोषणा IP_SET_EMIT_CREATE
#समावेश "ip_set_hash_gen.h"

अटल व्योम
hash_netnet6_init(काष्ठा hash_netnet6_elem *e)
अणु
	e->cidr[0] = HOST_MASK;
	e->cidr[1] = HOST_MASK;
पूर्ण

अटल पूर्णांक
hash_netnet6_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		  स्थिर काष्ठा xt_action_param *par,
		  क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	स्थिर काष्ठा hash_netnet6 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netnet6_elem e = अणु पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	e.cidr[0] = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK);
	e.cidr[1] = INIT_CIDR(h->nets[0].cidr[1], HOST_MASK);
	अगर (adt == IPSET_TEST)
		e.ccmp = (HOST_MASK << (माप(u8) * 8)) | HOST_MASK;

	ip6addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip[0].in6);
	ip6addrptr(skb, opt->flags & IPSET_DIM_TWO_SRC, &e.ip[1].in6);
	ip6_neपंचांगask(&e.ip[0], e.cidr[0]);
	ip6_neपंचांगask(&e.ip[1], e.cidr[1]);

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_netnet6_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		  क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netnet6_elem e = अणु पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	hash_netnet6_init(&e);
	अगर (unlikely(!tb[IPSET_ATTR_IP] || !tb[IPSET_ATTR_IP2] ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;
	अगर (unlikely(tb[IPSET_ATTR_IP_TO] || tb[IPSET_ATTR_IP2_TO]))
		वापस -IPSET_ERR_HASH_RANGE_UNSUPPORTED;

	ret = ip_set_get_ipaddr6(tb[IPSET_ATTR_IP], &e.ip[0]);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_ipaddr6(tb[IPSET_ATTR_IP2], &e.ip[1]);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_CIDR]) अणु
		e.cidr[0] = nla_get_u8(tb[IPSET_ATTR_CIDR]);
		अगर (!e.cidr[0] || e.cidr[0] > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण

	अगर (tb[IPSET_ATTR_CIDR2]) अणु
		e.cidr[1] = nla_get_u8(tb[IPSET_ATTR_CIDR2]);
		अगर (!e.cidr[1] || e.cidr[1] > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण

	ip6_neपंचांगask(&e.ip[0], e.cidr[0]);
	ip6_neपंचांगask(&e.ip[1], e.cidr[1]);

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		अगर (cadt_flags & IPSET_FLAG_NOMATCH)
			flags |= (IPSET_FLAG_NOMATCH << 16);
	पूर्ण

	ret = adtfn(set, &e, &ext, &ext, flags);

	वापस ip_set_enomatch(ret, flags, adt, set) ? -ret :
	       ip_set_eexist(ret, flags) ? 0 : ret;
पूर्ण

अटल काष्ठा ip_set_type hash_netnet_type __पढ़ो_mostly = अणु
	.name		= "hash:net,net",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_IP | IPSET_TYPE_IP2 | IPSET_TYPE_NOMATCH,
	.dimension	= IPSET_DIM_TWO,
	.family		= NFPROTO_UNSPEC,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create_flags[IPSET_TYPE_REV_MAX] = IPSET_CREATE_FLAG_BUCKETSIZE,
	.create		= hash_netnet_create,
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
		[IPSET_ATTR_CIDR]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_CIDR2]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_LINENO]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
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
hash_netnet_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&hash_netnet_type);
पूर्ण

अटल व्योम __निकास
hash_netnet_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&hash_netnet_type);
पूर्ण

module_init(hash_netnet_init);
module_निकास(hash_netnet_fini);
