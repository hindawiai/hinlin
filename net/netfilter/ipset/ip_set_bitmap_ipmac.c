<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2000-2002 Joakim Axelsson <gozem@linux.nu>
 *                         Patrick Schaaf <bof@bof.de>
 *			   Martin Josefsson <gandalf@wlug.westbo.se>
 */

/* Kernel module implementing an IP set type: the biपंचांगap:ip,mac type */

#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netlink.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <net/netlink.h>

#समावेश <linux/netfilter/ipset/pfxlen.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_biपंचांगap.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1	   Counter support added */
/*				2	   Comment support added */
#घोषणा IPSET_TYPE_REV_MAX	3	/* skbinfo support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("bitmap:ip,mac", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_bitmap:ip,mac");

#घोषणा MTYPE		biपंचांगap_ipmac
#घोषणा HOST_MASK	32
#घोषणा IP_SET_BITMAP_STORED_TIMEOUT

क्रमागत अणु
	MAC_UNSET,		/* element is set, without MAC */
	MAC_FILLED,		/* element is set with MAC */
पूर्ण;

/* Type काष्ठाure */
काष्ठा biपंचांगap_ipmac अणु
	अचिन्हित दीर्घ *members;	/* the set members */
	u32 first_ip;		/* host byte order, included in range */
	u32 last_ip;		/* host byte order, included in range */
	u32 elements;		/* number of max elements in the set */
	माप_प्रकार memsize;		/* members size */
	काष्ठा समयr_list gc;	/* garbage collector */
	काष्ठा ip_set *set;	/* attached to this ip_set */
	अचिन्हित अक्षर extensions[]	/* MAC + data extensions */
		__aligned(__alignof__(u64));
पूर्ण;

/* ADT काष्ठाure क्रम generic function args */
काष्ठा biपंचांगap_ipmac_adt_elem अणु
	अचिन्हित अक्षर ether[ETH_ALEN] __aligned(2);
	u16 id;
	u16 add_mac;
पूर्ण;

काष्ठा biपंचांगap_ipmac_elem अणु
	अचिन्हित अक्षर ether[ETH_ALEN];
	अचिन्हित अक्षर filled;
पूर्ण __aligned(__alignof__(u64));

अटल u32
ip_to_id(स्थिर काष्ठा biपंचांगap_ipmac *m, u32 ip)
अणु
	वापस ip - m->first_ip;
पूर्ण

#घोषणा get_elem(extensions, id, dsize)		\
	(काष्ठा biपंचांगap_ipmac_elem *)(extensions + (id) * (dsize))

#घोषणा get_स्थिर_elem(extensions, id, dsize)	\
	(स्थिर काष्ठा biपंचांगap_ipmac_elem *)(extensions + (id) * (dsize))

/* Common functions */

अटल पूर्णांक
biपंचांगap_ipmac_करो_test(स्थिर काष्ठा biपंचांगap_ipmac_adt_elem *e,
		     स्थिर काष्ठा biपंचांगap_ipmac *map, माप_प्रकार dsize)
अणु
	स्थिर काष्ठा biपंचांगap_ipmac_elem *elem;

	अगर (!test_bit(e->id, map->members))
		वापस 0;
	elem = get_स्थिर_elem(map->extensions, e->id, dsize);
	अगर (e->add_mac && elem->filled == MAC_FILLED)
		वापस ether_addr_equal(e->ether, elem->ether);
	/* Trigger kernel to fill out the ethernet address */
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_gc_test(u16 id, स्थिर काष्ठा biपंचांगap_ipmac *map, माप_प्रकार dsize)
अणु
	स्थिर काष्ठा biपंचांगap_ipmac_elem *elem;

	अगर (!test_bit(id, map->members))
		वापस 0;
	elem = get_स्थिर_elem(map->extensions, id, dsize);
	/* Timer not started क्रम the incomplete elements */
	वापस elem->filled == MAC_FILLED;
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_is_filled(स्थिर काष्ठा biपंचांगap_ipmac_elem *elem)
अणु
	वापस elem->filled == MAC_FILLED;
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_add_समयout(अचिन्हित दीर्घ *समयout,
			 स्थिर काष्ठा biपंचांगap_ipmac_adt_elem *e,
			 स्थिर काष्ठा ip_set_ext *ext, काष्ठा ip_set *set,
			 काष्ठा biपंचांगap_ipmac *map, पूर्णांक mode)
अणु
	u32 t = ext->समयout;

	अगर (mode == IPSET_ADD_START_STORED_TIMEOUT) अणु
		अगर (t == set->समयout)
			/* Timeout was not specअगरied, get stored one */
			t = *समयout;
		ip_set_समयout_set(समयout, t);
	पूर्ण अन्यथा अणु
		/* If MAC is unset yet, we store plain समयout value
		 * because the समयr is not activated yet
		 * and we can reuse it later when MAC is filled out,
		 * possibly by the kernel
		 */
		अगर (e->add_mac)
			ip_set_समयout_set(समयout, t);
		अन्यथा
			*समयout = t;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_करो_add(स्थिर काष्ठा biपंचांगap_ipmac_adt_elem *e,
		    काष्ठा biपंचांगap_ipmac *map, u32 flags, माप_प्रकार dsize)
अणु
	काष्ठा biपंचांगap_ipmac_elem *elem;

	elem = get_elem(map->extensions, e->id, dsize);
	अगर (test_bit(e->id, map->members)) अणु
		अगर (elem->filled == MAC_FILLED) अणु
			अगर (e->add_mac &&
			    (flags & IPSET_FLAG_EXIST) &&
			    !ether_addr_equal(e->ether, elem->ether)) अणु
				/* स_नकल isn't atomic */
				clear_bit(e->id, map->members);
				smp_mb__after_atomic();
				ether_addr_copy(elem->ether, e->ether);
			पूर्ण
			वापस IPSET_ADD_FAILED;
		पूर्ण अन्यथा अगर (!e->add_mac)
			/* Alपढ़ोy added without ethernet address */
			वापस IPSET_ADD_FAILED;
		/* Fill the MAC address and trigger the समयr activation */
		clear_bit(e->id, map->members);
		smp_mb__after_atomic();
		ether_addr_copy(elem->ether, e->ether);
		elem->filled = MAC_FILLED;
		वापस IPSET_ADD_START_STORED_TIMEOUT;
	पूर्ण अन्यथा अगर (e->add_mac) अणु
		/* We can store MAC too */
		ether_addr_copy(elem->ether, e->ether);
		elem->filled = MAC_FILLED;
		वापस 0;
	पूर्ण
	elem->filled = MAC_UNSET;
	/* MAC is not stored yet, करोn't start समयr */
	वापस IPSET_ADD_STORE_PLAIN_TIMEOUT;
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_करो_del(स्थिर काष्ठा biपंचांगap_ipmac_adt_elem *e,
		    काष्ठा biपंचांगap_ipmac *map)
अणु
	वापस !test_and_clear_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_करो_list(काष्ठा sk_buff *skb, स्थिर काष्ठा biपंचांगap_ipmac *map,
		     u32 id, माप_प्रकार dsize)
अणु
	स्थिर काष्ठा biपंचांगap_ipmac_elem *elem =
		get_स्थिर_elem(map->extensions, id, dsize);

	वापस nla_put_ipaddr4(skb, IPSET_ATTR_IP,
			       htonl(map->first_ip + id)) ||
	       (elem->filled == MAC_FILLED &&
		nla_put(skb, IPSET_ATTR_ETHER, ETH_ALEN, elem->ether));
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_करो_head(काष्ठा sk_buff *skb, स्थिर काष्ठा biपंचांगap_ipmac *map)
अणु
	वापस nla_put_ipaddr4(skb, IPSET_ATTR_IP, htonl(map->first_ip)) ||
	       nla_put_ipaddr4(skb, IPSET_ATTR_IP_TO, htonl(map->last_ip));
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		  स्थिर काष्ठा xt_action_param *par,
		  क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा biपंचांगap_ipmac *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा biपंचांगap_ipmac_adt_elem e = अणु .id = 0, .add_mac = 1 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	u32 ip;

	ip = ntohl(ip4addr(skb, opt->flags & IPSET_DIM_ONE_SRC));
	अगर (ip < map->first_ip || ip > map->last_ip)
		वापस -IPSET_ERR_BITMAP_RANGE;

	/* Backward compatibility: we करोn't check the second flag */
	अगर (skb_mac_header(skb) < skb->head ||
	    (skb_mac_header(skb) + ETH_HLEN) > skb->data)
		वापस -EINVAL;

	e.id = ip_to_id(map, ip);

	अगर (opt->flags & IPSET_DIM_TWO_SRC)
		ether_addr_copy(e.ether, eth_hdr(skb)->h_source);
	अन्यथा
		ether_addr_copy(e.ether, eth_hdr(skb)->h_dest);

	अगर (is_zero_ether_addr(e.ether))
		वापस -EINVAL;

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		  क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	स्थिर काष्ठा biपंचांगap_ipmac *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा biपंचांगap_ipmac_adt_elem e = अणु .id = 0 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0;
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

	e.id = ip_to_id(map, ip);
	अगर (tb[IPSET_ATTR_ETHER]) अणु
		अगर (nla_len(tb[IPSET_ATTR_ETHER]) != ETH_ALEN)
			वापस -IPSET_ERR_PROTOCOL;
		स_नकल(e.ether, nla_data(tb[IPSET_ATTR_ETHER]), ETH_ALEN);
		e.add_mac = 1;
	पूर्ण
	ret = adtfn(set, &e, &ext, &ext, flags);

	वापस ip_set_eexist(ret, flags) ? 0 : ret;
पूर्ण

अटल bool
biपंचांगap_ipmac_same_set(स्थिर काष्ठा ip_set *a, स्थिर काष्ठा ip_set *b)
अणु
	स्थिर काष्ठा biपंचांगap_ipmac *x = a->data;
	स्थिर काष्ठा biपंचांगap_ipmac *y = b->data;

	वापस x->first_ip == y->first_ip &&
	       x->last_ip == y->last_ip &&
	       a->समयout == b->समयout &&
	       a->extensions == b->extensions;
पूर्ण

/* Plain variant */

#समावेश "ip_set_bitmap_gen.h"

/* Create biपंचांगap:ip,mac type of sets */

अटल bool
init_map_ipmac(काष्ठा ip_set *set, काष्ठा biपंचांगap_ipmac *map,
	       u32 first_ip, u32 last_ip, u32 elements)
अणु
	map->members = biपंचांगap_zalloc(elements, GFP_KERNEL | __GFP_NOWARN);
	अगर (!map->members)
		वापस false;
	map->first_ip = first_ip;
	map->last_ip = last_ip;
	map->elements = elements;
	set->समयout = IPSET_NO_TIMEOUT;

	map->set = set;
	set->data = map;
	set->family = NFPROTO_IPV4;

	वापस true;
पूर्ण

अटल पूर्णांक
biपंचांगap_ipmac_create(काष्ठा net *net, काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		    u32 flags)
अणु
	u32 first_ip = 0, last_ip = 0;
	u64 elements;
	काष्ठा biपंचांगap_ipmac *map;
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

	elements = (u64)last_ip - first_ip + 1;

	अगर (elements > IPSET_BITMAP_MAX_RANGE + 1)
		वापस -IPSET_ERR_BITMAP_RANGE_SIZE;

	set->dsize = ip_set_elem_len(set, tb,
				     माप(काष्ठा biपंचांगap_ipmac_elem),
				     __alignof__(काष्ठा biपंचांगap_ipmac_elem));
	map = ip_set_alloc(माप(*map) + elements * set->dsize);
	अगर (!map)
		वापस -ENOMEM;

	map->memsize = BITS_TO_LONGS(elements) * माप(अचिन्हित दीर्घ);
	set->variant = &biपंचांगap_ipmac;
	अगर (!init_map_ipmac(set, map, first_ip, last_ip, elements)) अणु
		ip_set_मुक्त(map);
		वापस -ENOMEM;
	पूर्ण
	अगर (tb[IPSET_ATTR_TIMEOUT]) अणु
		set->समयout = ip_set_समयout_uget(tb[IPSET_ATTR_TIMEOUT]);
		biपंचांगap_ipmac_gc_init(set, biपंचांगap_ipmac_gc);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ip_set_type biपंचांगap_ipmac_type = अणु
	.name		= "bitmap:ip,mac",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_IP | IPSET_TYPE_MAC,
	.dimension	= IPSET_DIM_TWO,
	.family		= NFPROTO_IPV4,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create		= biपंचांगap_ipmac_create,
	.create_policy	= अणु
		[IPSET_ATTR_IP]		= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_IP_TO]	= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_CIDR]	= अणु .type = NLA_U8 पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	पूर्ण,
	.adt_policy	= अणु
		[IPSET_ATTR_IP]		= अणु .type = NLA_NESTED पूर्ण,
		[IPSET_ATTR_ETHER]	= अणु .type = NLA_BINARY,
					    .len  = ETH_ALEN पूर्ण,
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
biपंचांगap_ipmac_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&biपंचांगap_ipmac_type);
पूर्ण

अटल व्योम __निकास
biपंचांगap_ipmac_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&biपंचांगap_ipmac_type);
पूर्ण

module_init(biपंचांगap_ipmac_init);
module_निकास(biपंचांगap_ipmac_fini);
