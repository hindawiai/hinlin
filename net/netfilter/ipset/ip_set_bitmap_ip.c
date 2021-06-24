<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2000-2002 Joakim Axelsson <gozem@linux.nu>
 *                         Patrick Schaaf <bof@bof.de>
 * Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org>
 */

/* Kernel module implementing an IP set type: the biपंचांगap:ip type */

#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netlink.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <net/netlink.h>
#समावेश <net/tcp.h>

#समावेश <linux/netfilter/ipset/pfxlen.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_biपंचांगap.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1	   Counter support added */
/*				2	   Comment support added */
#घोषणा IPSET_TYPE_REV_MAX	3	/* skbinfo support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("bitmap:ip", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_bitmap:ip");

#घोषणा MTYPE		biपंचांगap_ip
#घोषणा HOST_MASK	32

/* Type काष्ठाure */
काष्ठा biपंचांगap_ip अणु
	अचिन्हित दीर्घ *members;	/* the set members */
	u32 first_ip;		/* host byte order, included in range */
	u32 last_ip;		/* host byte order, included in range */
	u32 elements;		/* number of max elements in the set */
	u32 hosts;		/* number of hosts in a subnet */
	माप_प्रकार memsize;		/* members size */
	u8 neपंचांगask;		/* subnet neपंचांगask */
	काष्ठा समयr_list gc;	/* garbage collection */
	काष्ठा ip_set *set;	/* attached to this ip_set */
	अचिन्हित अक्षर extensions[]	/* data extensions */
		__aligned(__alignof__(u64));
पूर्ण;

/* ADT काष्ठाure क्रम generic function args */
काष्ठा biपंचांगap_ip_adt_elem अणु
	u16 id;
पूर्ण;

अटल u32
ip_to_id(स्थिर काष्ठा biपंचांगap_ip *m, u32 ip)
अणु
	वापस ((ip & ip_set_hosपंचांगask(m->neपंचांगask)) - m->first_ip) / m->hosts;
पूर्ण

/* Common functions */

अटल पूर्णांक
biपंचांगap_ip_करो_test(स्थिर काष्ठा biपंचांगap_ip_adt_elem *e,
		  काष्ठा biपंचांगap_ip *map, माप_प्रकार dsize)
अणु
	वापस !!test_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_gc_test(u16 id, स्थिर काष्ठा biपंचांगap_ip *map, माप_प्रकार dsize)
अणु
	वापस !!test_bit(id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_करो_add(स्थिर काष्ठा biपंचांगap_ip_adt_elem *e, काष्ठा biपंचांगap_ip *map,
		 u32 flags, माप_प्रकार dsize)
अणु
	वापस !!test_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_करो_del(स्थिर काष्ठा biपंचांगap_ip_adt_elem *e, काष्ठा biपंचांगap_ip *map)
अणु
	वापस !test_and_clear_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_करो_list(काष्ठा sk_buff *skb, स्थिर काष्ठा biपंचांगap_ip *map, u32 id,
		  माप_प्रकार dsize)
अणु
	वापस nla_put_ipaddr4(skb, IPSET_ATTR_IP,
			htonl(map->first_ip + id * map->hosts));
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_करो_head(काष्ठा sk_buff *skb, स्थिर काष्ठा biपंचांगap_ip *map)
अणु
	वापस nla_put_ipaddr4(skb, IPSET_ATTR_IP, htonl(map->first_ip)) ||
	       nla_put_ipaddr4(skb, IPSET_ATTR_IP_TO, htonl(map->last_ip)) ||
	       (map->neपंचांगask != 32 &&
		nla_put_u8(skb, IPSET_ATTR_NETMASK, map->neपंचांगask));
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
	       स्थिर काष्ठा xt_action_param *par,
	       क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा biपंचांगap_ip *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा biपंचांगap_ip_adt_elem e = अणु .id = 0 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	u32 ip;

	ip = ntohl(ip4addr(skb, opt->flags & IPSET_DIM_ONE_SRC));
	अगर (ip < map->first_ip || ip > map->last_ip)
		वापस -IPSET_ERR_BITMAP_RANGE;

	e.id = ip_to_id(map, ip);

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
	       क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	काष्ठा biपंचांगap_ip *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	u32 ip = 0, ip_to = 0;
	काष्ठा biपंचांगap_ip_adt_elem e = अणु .id = 0 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	पूर्णांक ret = 0;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_IP]))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP], &ip);
	अगर (ret)
		वापस ret;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	अगर (ip < map->first_ip || ip > map->last_ip)
		वापस -IPSET_ERR_BITMAP_RANGE;

	अगर (adt == IPSET_TEST) अणु
		e.id = ip_to_id(map, ip);
		वापस adtfn(set, &e, &ext, &ext, flags);
	पूर्ण

	अगर (tb[IPSET_ATTR_IP_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP_TO], &ip_to);
		अगर (ret)
			वापस ret;
		अगर (ip > ip_to) अणु
			swap(ip, ip_to);
			अगर (ip < map->first_ip)
				वापस -IPSET_ERR_BITMAP_RANGE;
		पूर्ण
	पूर्ण अन्यथा अगर (tb[IPSET_ATTR_CIDR]) अणु
		u8 cidr = nla_get_u8(tb[IPSET_ATTR_CIDR]);

		अगर (!cidr || cidr > HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
		ip_set_mask_from_to(ip, ip_to, cidr);
	पूर्ण अन्यथा अणु
		ip_to = ip;
	पूर्ण

	अगर (ip_to > map->last_ip)
		वापस -IPSET_ERR_BITMAP_RANGE;

	क्रम (; !beक्रमe(ip_to, ip); ip += map->hosts) अणु
		e.id = ip_to_id(map, ip);
		ret = adtfn(set, &e, &ext, &ext, flags);

		अगर (ret && !ip_set_eexist(ret, flags))
			वापस ret;

		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool
biपंचांगap_ip_same_set(स्थिर काष्ठा ip_set *a, स्थिर काष्ठा ip_set *b)
अणु
	स्थिर काष्ठा biपंचांगap_ip *x = a->data;
	स्थिर काष्ठा biपंचांगap_ip *y = b->data;

	वापस x->first_ip == y->first_ip &&
	       x->last_ip == y->last_ip &&
	       x->neपंचांगask == y->neपंचांगask &&
	       a->समयout == b->समयout &&
	       a->extensions == b->extensions;
पूर्ण

/* Plain variant */

काष्ठा biपंचांगap_ip_elem अणु
पूर्ण;

#समावेश "ip_set_bitmap_gen.h"

/* Create biपंचांगap:ip type of sets */

अटल bool
init_map_ip(काष्ठा ip_set *set, काष्ठा biपंचांगap_ip *map,
	    u32 first_ip, u32 last_ip,
	    u32 elements, u32 hosts, u8 neपंचांगask)
अणु
	map->members = biपंचांगap_zalloc(elements, GFP_KERNEL | __GFP_NOWARN);
	अगर (!map->members)
		वापस false;
	map->first_ip = first_ip;
	map->last_ip = last_ip;
	map->elements = elements;
	map->hosts = hosts;
	map->neपंचांगask = neपंचांगask;
	set->समयout = IPSET_NO_TIMEOUT;

	map->set = set;
	set->data = map;
	set->family = NFPROTO_IPV4;

	वापस true;
पूर्ण

अटल u32
range_to_mask(u32 from, u32 to, u8 *bits)
अणु
	u32 mask = 0xFFFFFFFE;

	*bits = 32;
	जबतक (--(*bits) > 0 && mask && (to & mask) != from)
		mask <<= 1;

	वापस mask;
पूर्ण

अटल पूर्णांक
biपंचांगap_ip_create(काष्ठा net *net, काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		 u32 flags)
अणु
	काष्ठा biपंचांगap_ip *map;
	u32 first_ip = 0, last_ip = 0, hosts;
	u64 elements;
	u8 neपंचांगask = 32;
	पूर्णांक ret;

	अगर (unlikely(!tb[IPSET_ATTR_IP] ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_TIMEOUT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP], &first_ip);
	अगर (ret)
		वापस ret;

	अगर (tb[IPSET_ATTR_IP_TO]) अणु
		ret = ip_set_get_hostipaddr4(tb[IPSET_ATTR_IP_TO], &last_ip);
		अगर (ret)
			वापस ret;
		अगर (first_ip > last_ip)
			swap(first_ip, last_ip);
	पूर्ण अन्यथा अगर (tb[IPSET_ATTR_CIDR]) अणु
		u8 cidr = nla_get_u8(tb[IPSET_ATTR_CIDR]);

		अगर (cidr >= HOST_MASK)
			वापस -IPSET_ERR_INVALID_CIDR;
		ip_set_mask_from_to(first_ip, last_ip, cidr);
	पूर्ण अन्यथा अणु
		वापस -IPSET_ERR_PROTOCOL;
	पूर्ण

	अगर (tb[IPSET_ATTR_NETMASK]) अणु
		neपंचांगask = nla_get_u8(tb[IPSET_ATTR_NETMASK]);

		अगर (neपंचांगask > HOST_MASK)
			वापस -IPSET_ERR_INVALID_NETMASK;

		first_ip &= ip_set_hosपंचांगask(neपंचांगask);
		last_ip |= ~ip_set_hosपंचांगask(neपंचांगask);
	पूर्ण

	अगर (neपंचांगask == 32) अणु
		hosts = 1;
		elements = (u64)last_ip - first_ip + 1;
	पूर्ण अन्यथा अणु
		u8 mask_bits;
		u32 mask;

		mask = range_to_mask(first_ip, last_ip, &mask_bits);

		अगर ((!mask && (first_ip || last_ip != 0xFFFFFFFF)) ||
		    neपंचांगask <= mask_bits)
			वापस -IPSET_ERR_BITMAP_RANGE;

		pr_debug("mask_bits %u, netmask %u\n", mask_bits, neपंचांगask);
		hosts = 2 << (32 - neपंचांगask - 1);
		elements = 2 << (neपंचांगask - mask_bits - 1);
	पूर्ण
	अगर (elements > IPSET_BITMAP_MAX_RANGE + 1)
		वापस -IPSET_ERR_BITMAP_RANGE_SIZE;

	pr_debug("hosts %u, elements %llu\n",
		 hosts, (अचिन्हित दीर्घ दीर्घ)elements);

	set->dsize = ip_set_elem_len(set, tb, 0, 0);
	map = ip_set_alloc(माप(*map) + elements * set->dsize);
	अगर (!map)
		वापस -ENOMEM;

	map->memsize = BITS_TO_LONGS(elements) * माप(अचिन्हित दीर्घ);
	set->variant = &biपंचांगap_ip;
	अगर (!init_map_ip(set, map, first_ip, last_ip,
			 elements, hosts, neपंचांगask)) अणु
		ip_set_मुक्त(map);
		वापस -ENOMEM;
	पूर्ण
	अगर (tb[IPSET_ATTR_TIMEOUT]) अणु
		set->समयout = ip_set_समयout_uget(tb[IPSET_ATTR_TIMEOUT]);
		biपंचांगap_ip_gc_init(set, biपंचांगap_ip_gc);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ip_set_type biपंचांगap_ip_type __पढ़ो_mostly = अणु
	.name		= "bitmap:ip",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_IP,
	.dimension	= IPSET_DIM_ONE,
	.family		= NFPROTO_IPV4,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create		= biपंचांगap_ip_create,
	.create_policy	= अणु
		[IPSET_ATTR_IP]		= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP_TO]	= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_CIDR]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_NETMASK]	= अणु .type = NLA_U8  पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	पूर्ण,
	.adt_policy	= अणु
		[IPSET_ATTR_IP]		= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP_TO]	= अणु .type = NLA_NESTED पूर्ण,
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
biपंचांगap_ip_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&biपंचांगap_ip_type);
पूर्ण

अटल व्योम __निकास
biपंचांगap_ip_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&biपंचांगap_ip_type);
पूर्ण

module_init(biपंचांगap_ip_init);
module_निकास(biपंचांगap_ip_fini);
