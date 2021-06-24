<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2011-2013 Jozsef Kadlecsik <kadlec@netfilter.org> */

/* Kernel module implementing an IP set type: the hash:net,अगरace type */

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
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter/ipset/pfxlen.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_hash.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1    nomatch flag support added */
/*				2    /0 support added */
/*				3    Counters support added */
/*				4    Comments support added */
/*				5    Forceadd support added */
/*				6    skbinfo support added */
/*				7    पूर्णांकerface wildcard support added */
#घोषणा IPSET_TYPE_REV_MAX	8 /* bucketsize, initval support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("hash:net,iface", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_hash:net,iface");

/* Type specअगरic function prefix */
#घोषणा HTYPE		hash_netअगरace
#घोषणा IP_SET_HASH_WITH_NETS
#घोषणा IP_SET_HASH_WITH_MULTI
#घोषणा IP_SET_HASH_WITH_NET0

#घोषणा STRLCPY(a, b)	strlcpy(a, b, IFNAMSIZ)

/* IPv4 variant */

काष्ठा hash_netअगरace4_elem_hashed अणु
	__be32 ip;
	u8 physdev;
	u8 cidr;
	u8 nomatch;
	u8 elem;
पूर्ण;

/* Member elements */
काष्ठा hash_netअगरace4_elem अणु
	__be32 ip;
	u8 physdev;
	u8 cidr;
	u8 nomatch;
	u8 elem;
	u8 wildcard;
	अक्षर अगरace[IFNAMSIZ];
पूर्ण;

/* Common functions */

अटल bool
hash_netअगरace4_data_equal(स्थिर काष्ठा hash_netअगरace4_elem *ip1,
			  स्थिर काष्ठा hash_netअगरace4_elem *ip2,
			  u32 *multi)
अणु
	वापस ip1->ip == ip2->ip &&
	       ip1->cidr == ip2->cidr &&
	       (++*multi) &&
	       ip1->physdev == ip2->physdev &&
	       (ip1->wildcard ?
		म_भेदन(ip1->अगरace, ip2->अगरace, म_माप(ip1->अगरace)) == 0 :
		म_भेद(ip1->अगरace, ip2->अगरace) == 0);
पूर्ण

अटल पूर्णांक
hash_netअगरace4_करो_data_match(स्थिर काष्ठा hash_netअगरace4_elem *elem)
अणु
	वापस elem->nomatch ? -ENOTEMPTY : 1;
पूर्ण

अटल व्योम
hash_netअगरace4_data_set_flags(काष्ठा hash_netअगरace4_elem *elem, u32 flags)
अणु
	elem->nomatch = (flags >> 16) & IPSET_FLAG_NOMATCH;
पूर्ण

अटल व्योम
hash_netअगरace4_data_reset_flags(काष्ठा hash_netअगरace4_elem *elem, u8 *flags)
अणु
	swap(*flags, elem->nomatch);
पूर्ण

अटल व्योम
hash_netअगरace4_data_neपंचांगask(काष्ठा hash_netअगरace4_elem *elem, u8 cidr)
अणु
	elem->ip &= ip_set_neपंचांगask(cidr);
	elem->cidr = cidr;
पूर्ण

अटल bool
hash_netअगरace4_data_list(काष्ठा sk_buff *skb,
			 स्थिर काष्ठा hash_netअगरace4_elem *data)
अणु
	u32 flags = (data->physdev ? IPSET_FLAG_PHYSDEV : 0) |
		    (data->wildcard ? IPSET_FLAG_IFACE_WILDCARD : 0);

	अगर (data->nomatch)
		flags |= IPSET_FLAG_NOMATCH;
	अगर (nla_put_ipaddr4(skb, IPSET_ATTR_IP, data->ip) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR, data->cidr) ||
	    nla_put_string(skb, IPSET_ATTR_IFACE, data->अगरace) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_netअगरace4_data_next(काष्ठा hash_netअगरace4_elem *next,
			 स्थिर काष्ठा hash_netअगरace4_elem *d)
अणु
	next->ip = d->ip;
पूर्ण

#घोषणा MTYPE		hash_netअगरace4
#घोषणा HOST_MASK	32
#घोषणा HKEY_DATALEN	माप(काष्ठा hash_netअगरace4_elem_hashed)
#समावेश "ip_set_hash_gen.h"

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
अटल स्थिर अक्षर *get_physindev_name(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = nf_bridge_get_physindev(skb);

	वापस dev ? dev->name : शून्य;
पूर्ण

अटल स्थिर अक्षर *get_physoutdev_name(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = nf_bridge_get_physoutdev(skb);

	वापस dev ? dev->name : शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
hash_netअगरace4_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		    स्थिर काष्ठा xt_action_param *par,
		    क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा hash_netअगरace4 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netअगरace4_elem e = अणु
		.cidr = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK),
		.elem = 1,
	पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	अगर (adt == IPSET_TEST)
		e.cidr = HOST_MASK;

	ip4addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip);
	e.ip &= ip_set_neपंचांगask(e.cidr);

#घोषणा IFACE(dir)	(par->state->dir ? par->state->dir->name : "")
#घोषणा SRCसूची		(opt->flags & IPSET_DIM_TWO_SRC)

	अगर (opt->cmdflags & IPSET_FLAG_PHYSDEV) अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		स्थिर अक्षर *eअगरace = SRCसूची ? get_physindev_name(skb) :
					      get_physoutdev_name(skb);

		अगर (!eअगरace)
			वापस -EINVAL;
		STRLCPY(e.अगरace, eअगरace);
		e.physdev = 1;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		STRLCPY(e.अगरace, SRCसूची ? IFACE(in) : IFACE(out));
	पूर्ण

	अगर (म_माप(e.अगरace) == 0)
		वापस -EINVAL;
	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_netअगरace4_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		    क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	काष्ठा hash_netअगरace4 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netअगरace4_elem e = अणु .cidr = HOST_MASK, .elem = 1 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0;
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_IP] ||
		     !tb[IPSET_ATTR_IFACE] ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP], &ip);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_CIDR]) अणु
		e.cidr = nla_get_u8(tb[IPSET_ATTR_CIDR]);
		अगर (e.cidr > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण
	nla_strscpy(e.अगरace, tb[IPSET_ATTR_IFACE], IFNAMSIZ);

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		अगर (cadt_flags & IPSET_FLAG_PHYSDEV)
			e.physdev = 1;
		अगर (cadt_flags & IPSET_FLAG_NOMATCH)
			flags |= (IPSET_FLAG_NOMATCH << 16);
		अगर (cadt_flags & IPSET_FLAG_IFACE_WILDCARD)
			e.wildcard = 1;
	पूर्ण
	अगर (adt == IPSET_TEST || !tb[IPSET_ATTR_IP_TO]) अणु
		e.ip = htonl(ip & ip_set_hosपंचांगask(e.cidr));
		ret = adtfn(set, &e, &ext, &ext, flags);
		वापस ip_set_enomatch(ret, flags, adt, set) ? -ret :
		       ip_set_eexist(ret, flags) ? 0 : ret;
	पूर्ण

	अगर (tb[IPSET_ATTR_IP_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP_TO], &ip_to);
		अगर (ret)
			वापस ret;
		अगर (ip_to < ip)
			swap(ip, ip_to);
		अगर (ip + अच_पूर्णांक_उच्च == ip_to)
			वापस -IPSET_ERR_HASH_RANGE;
	पूर्ण अन्यथा अणु
		ip_set_mask_from_to(ip, ip_to, e.cidr);
	पूर्ण

	अगर (retried)
		ip = ntohl(h->next.ip);
	करो अणु
		e.ip = htonl(ip);
		ip = ip_set_range_to_cidr(ip, ip_to, &e.cidr);
		ret = adtfn(set, &e, &ext, &ext, flags);

		अगर (ret && !ip_set_eexist(ret, flags))
			वापस ret;

		ret = 0;
	पूर्ण जबतक (ip++ < ip_to);
	वापस ret;
पूर्ण

/* IPv6 variant */

काष्ठा hash_netअगरace6_elem_hashed अणु
	जोड़ nf_inet_addr ip;
	u8 physdev;
	u8 cidr;
	u8 nomatch;
	u8 elem;
पूर्ण;

काष्ठा hash_netअगरace6_elem अणु
	जोड़ nf_inet_addr ip;
	u8 physdev;
	u8 cidr;
	u8 nomatch;
	u8 elem;
	u8 wildcard;
	अक्षर अगरace[IFNAMSIZ];
पूर्ण;

/* Common functions */

अटल bool
hash_netअगरace6_data_equal(स्थिर काष्ठा hash_netअगरace6_elem *ip1,
			  स्थिर काष्ठा hash_netअगरace6_elem *ip2,
			  u32 *multi)
अणु
	वापस ipv6_addr_equal(&ip1->ip.in6, &ip2->ip.in6) &&
	       ip1->cidr == ip2->cidr &&
	       (++*multi) &&
	       ip1->physdev == ip2->physdev &&
	       (ip1->wildcard ?
		म_भेदन(ip1->अगरace, ip2->अगरace, म_माप(ip1->अगरace)) == 0 :
		म_भेद(ip1->अगरace, ip2->अगरace) == 0);
पूर्ण

अटल पूर्णांक
hash_netअगरace6_करो_data_match(स्थिर काष्ठा hash_netअगरace6_elem *elem)
अणु
	वापस elem->nomatch ? -ENOTEMPTY : 1;
पूर्ण

अटल व्योम
hash_netअगरace6_data_set_flags(काष्ठा hash_netअगरace6_elem *elem, u32 flags)
अणु
	elem->nomatch = (flags >> 16) & IPSET_FLAG_NOMATCH;
पूर्ण

अटल व्योम
hash_netअगरace6_data_reset_flags(काष्ठा hash_netअगरace6_elem *elem, u8 *flags)
अणु
	swap(*flags, elem->nomatch);
पूर्ण

अटल व्योम
hash_netअगरace6_data_neपंचांगask(काष्ठा hash_netअगरace6_elem *elem, u8 cidr)
अणु
	ip6_neपंचांगask(&elem->ip, cidr);
	elem->cidr = cidr;
पूर्ण

अटल bool
hash_netअगरace6_data_list(काष्ठा sk_buff *skb,
			 स्थिर काष्ठा hash_netअगरace6_elem *data)
अणु
	u32 flags = (data->physdev ? IPSET_FLAG_PHYSDEV : 0) |
		    (data->wildcard ? IPSET_FLAG_IFACE_WILDCARD : 0);

	अगर (data->nomatch)
		flags |= IPSET_FLAG_NOMATCH;
	अगर (nla_put_ipaddr6(skb, IPSET_ATTR_IP, &data->ip.in6) ||
	    nla_put_u8(skb, IPSET_ATTR_CIDR, data->cidr) ||
	    nla_put_string(skb, IPSET_ATTR_IFACE, data->अगरace) ||
	    (flags &&
	     nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(flags))))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_netअगरace6_data_next(काष्ठा hash_netअगरace6_elem *next,
			 स्थिर काष्ठा hash_netअगरace6_elem *d)
अणु
पूर्ण

#अघोषित MTYPE
#अघोषित HOST_MASK

#घोषणा MTYPE		hash_netअगरace6
#घोषणा HOST_MASK	128
#घोषणा HKEY_DATALEN	माप(काष्ठा hash_netअगरace6_elem_hashed)
#घोषणा IP_SET_EMIT_CREATE
#समावेश "ip_set_hash_gen.h"

अटल पूर्णांक
hash_netअगरace6_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		    स्थिर काष्ठा xt_action_param *par,
		    क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा hash_netअगरace6 *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netअगरace6_elem e = अणु
		.cidr = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK),
		.elem = 1,
	पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	अगर (adt == IPSET_TEST)
		e.cidr = HOST_MASK;

	ip6addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip.in6);
	ip6_neपंचांगask(&e.ip, e.cidr);

	अगर (opt->cmdflags & IPSET_FLAG_PHYSDEV) अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		स्थिर अक्षर *eअगरace = SRCसूची ? get_physindev_name(skb) :
					      get_physoutdev_name(skb);

		अगर (!eअगरace)
			वापस -EINVAL;
		STRLCPY(e.अगरace, eअगरace);
		e.physdev = 1;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		STRLCPY(e.अगरace, SRCसूची ? IFACE(in) : IFACE(out));
	पूर्ण

	अगर (म_माप(e.अगरace) == 0)
		वापस -EINVAL;

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_netअगरace6_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		    क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_netअगरace6_elem e = अणु .cidr = HOST_MASK, .elem = 1 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_IP] ||
		     !tb[IPSET_ATTR_IFACE] ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;
	अगर (unlikely(tb[IPSET_ATTR_IP_TO]))
		वापस -IPSET_ERR_HASH_RANGE_UNSUPPORTED;

	ret = ip_set_get_ipaddr6(tb[IPSET_ATTR_IP], &e.ip);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_CIDR]) अणु
		e.cidr = nla_get_u8(tb[IPSET_ATTR_CIDR]);
		अगर (e.cidr > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
	पूर्ण

	ip6_neपंचांगask(&e.ip, e.cidr);

	nla_strscpy(e.अगरace, tb[IPSET_ATTR_IFACE], IFNAMSIZ);

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		अगर (cadt_flags & IPSET_FLAG_PHYSDEV)
			e.physdev = 1;
		अगर (cadt_flags & IPSET_FLAG_NOMATCH)
			flags |= (IPSET_FLAG_NOMATCH << 16);
		अगर (cadt_flags & IPSET_FLAG_IFACE_WILDCARD)
			e.wildcard = 1;
	पूर्ण

	ret = adtfn(set, &e, &ext, &ext, flags);

	वापस ip_set_enomatch(ret, flags, adt, set) ? -ret :
	       ip_set_eexist(ret, flags) ? 0 : ret;
पूर्ण

अटल काष्ठा ip_set_type hash_netअगरace_type __पढ़ो_mostly = अणु
	.name		= "hash:net,iface",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_IP | IPSET_TYPE_IFACE |
			  IPSET_TYPE_NOMATCH,
	.dimension	= IPSET_DIM_TWO,
	.family		= NFPROTO_UNSPEC,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create_flags[IPSET_TYPE_REV_MAX] = IPSET_CREATE_FLAG_BUCKETSIZE,
	.create		= hash_netअगरace_create,
	.create_policy	= अणु
		[IPSET_ATTR_HASHSIZE]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_MAXELEM]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_INITVAL]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_BUCKETSIZE]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_RESIZE]	= अणु .type = NLA_U8  पूर्ण,
		[IPSET_ATTR_PROTO]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	पूर्ण,
	.adt_policy	= अणु
		[IPSET_ATTR_IP]		= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP_TO]	= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IFACE]	= अणु .type = NLA_NUL_STRING,
					    .len  = IFNAMSIZ - 1 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CIDR]	= अणु .type = NLA_U8 पूर्ण,
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
hash_netअगरace_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&hash_netअगरace_type);
पूर्ण

अटल व्योम __निकास
hash_netअगरace_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&hash_netअगरace_type);
पूर्ण

module_init(hash_netअगरace_init);
module_निकास(hash_netअगरace_fini);
