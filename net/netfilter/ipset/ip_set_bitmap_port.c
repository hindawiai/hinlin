<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org> */

/* Kernel module implementing an IP set type: the biपंचांगap:port type */

#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netlink.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <net/netlink.h>

#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_biपंचांगap.h>
#समावेश <linux/netfilter/ipset/ip_set_getport.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1	   Counter support added */
/*				2	   Comment support added */
#घोषणा IPSET_TYPE_REV_MAX	3	/* skbinfo support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("bitmap:port", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_bitmap:port");

#घोषणा MTYPE		biपंचांगap_port

/* Type काष्ठाure */
काष्ठा biपंचांगap_port अणु
	अचिन्हित दीर्घ *members;	/* the set members */
	u16 first_port;		/* host byte order, included in range */
	u16 last_port;		/* host byte order, included in range */
	u32 elements;		/* number of max elements in the set */
	माप_प्रकार memsize;		/* members size */
	काष्ठा समयr_list gc;	/* garbage collection */
	काष्ठा ip_set *set;	/* attached to this ip_set */
	अचिन्हित अक्षर extensions[]	/* data extensions */
		__aligned(__alignof__(u64));
पूर्ण;

/* ADT काष्ठाure क्रम generic function args */
काष्ठा biपंचांगap_port_adt_elem अणु
	u16 id;
पूर्ण;

अटल u16
port_to_id(स्थिर काष्ठा biपंचांगap_port *m, u16 port)
अणु
	वापस port - m->first_port;
पूर्ण

/* Common functions */

अटल पूर्णांक
biपंचांगap_port_करो_test(स्थिर काष्ठा biपंचांगap_port_adt_elem *e,
		    स्थिर काष्ठा biपंचांगap_port *map, माप_प्रकार dsize)
अणु
	वापस !!test_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_port_gc_test(u16 id, स्थिर काष्ठा biपंचांगap_port *map, माप_प्रकार dsize)
अणु
	वापस !!test_bit(id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_port_करो_add(स्थिर काष्ठा biपंचांगap_port_adt_elem *e,
		   काष्ठा biपंचांगap_port *map, u32 flags, माप_प्रकार dsize)
अणु
	वापस !!test_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_port_करो_del(स्थिर काष्ठा biपंचांगap_port_adt_elem *e,
		   काष्ठा biपंचांगap_port *map)
अणु
	वापस !test_and_clear_bit(e->id, map->members);
पूर्ण

अटल पूर्णांक
biपंचांगap_port_करो_list(काष्ठा sk_buff *skb, स्थिर काष्ठा biपंचांगap_port *map, u32 id,
		    माप_प्रकार dsize)
अणु
	वापस nla_put_net16(skb, IPSET_ATTR_PORT,
			     htons(map->first_port + id));
पूर्ण

अटल पूर्णांक
biपंचांगap_port_करो_head(काष्ठा sk_buff *skb, स्थिर काष्ठा biपंचांगap_port *map)
अणु
	वापस nla_put_net16(skb, IPSET_ATTR_PORT, htons(map->first_port)) ||
	       nla_put_net16(skb, IPSET_ATTR_PORT_TO, htons(map->last_port));
पूर्ण

अटल bool
ip_set_get_ip_port(स्थिर काष्ठा sk_buff *skb, u8 pf, bool src, __be16 *port)
अणु
	bool ret;
	u8 proto;

	चयन (pf) अणु
	हाल NFPROTO_IPV4:
		ret = ip_set_get_ip4_port(skb, src, port, &proto);
		अवरोध;
	हाल NFPROTO_IPV6:
		ret = ip_set_get_ip6_port(skb, src, port, &proto);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	अगर (!ret)
		वापस ret;
	चयन (proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक
biपंचांगap_port_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		 स्थिर काष्ठा xt_action_param *par,
		 क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा biपंचांगap_port *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा biपंचांगap_port_adt_elem e = अणु .id = 0 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	__be16 __port;
	u16 port = 0;

	अगर (!ip_set_get_ip_port(skb, opt->family,
				opt->flags & IPSET_DIM_ONE_SRC, &__port))
		वापस -EINVAL;

	port = ntohs(__port);

	अगर (port < map->first_port || port > map->last_port)
		वापस -IPSET_ERR_BITMAP_RANGE;

	e.id = port_to_id(map, port);

	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
biपंचांगap_port_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		 क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	काष्ठा biपंचांगap_port *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा biपंचांगap_port_adt_elem e = अणु .id = 0 पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 port;	/* wraparound */
	u16 port_to;
	पूर्णांक ret = 0;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!ip_set_attr_netorder(tb, IPSET_ATTR_PORT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_PORT_TO)))
		वापस -IPSET_ERR_PROTOCOL;

	port = ip_set_get_h16(tb[IPSET_ATTR_PORT]);
	अगर (port < map->first_port || port > map->last_port)
		वापस -IPSET_ERR_BITMAP_RANGE;
	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;

	अगर (adt == IPSET_TEST) अणु
		e.id = port_to_id(map, port);
		वापस adtfn(set, &e, &ext, &ext, flags);
	पूर्ण

	अगर (tb[IPSET_ATTR_PORT_TO]) अणु
		port_to = ip_set_get_h16(tb[IPSET_ATTR_PORT_TO]);
		अगर (port > port_to) अणु
			swap(port, port_to);
			अगर (port < map->first_port)
				वापस -IPSET_ERR_BITMAP_RANGE;
		पूर्ण
	पूर्ण अन्यथा अणु
		port_to = port;
	पूर्ण

	अगर (port_to > map->last_port)
		वापस -IPSET_ERR_BITMAP_RANGE;

	क्रम (; port <= port_to; port++) अणु
		e.id = port_to_id(map, port);
		ret = adtfn(set, &e, &ext, &ext, flags);

		अगर (ret && !ip_set_eexist(ret, flags))
			वापस ret;

		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool
biपंचांगap_port_same_set(स्थिर काष्ठा ip_set *a, स्थिर काष्ठा ip_set *b)
अणु
	स्थिर काष्ठा biपंचांगap_port *x = a->data;
	स्थिर काष्ठा biपंचांगap_port *y = b->data;

	वापस x->first_port == y->first_port &&
	       x->last_port == y->last_port &&
	       a->समयout == b->समयout &&
	       a->extensions == b->extensions;
पूर्ण

/* Plain variant */

काष्ठा biपंचांगap_port_elem अणु
पूर्ण;

#समावेश "ip_set_bitmap_gen.h"

/* Create biपंचांगap:ip type of sets */

अटल bool
init_map_port(काष्ठा ip_set *set, काष्ठा biपंचांगap_port *map,
	      u16 first_port, u16 last_port)
अणु
	map->members = biपंचांगap_zalloc(map->elements, GFP_KERNEL | __GFP_NOWARN);
	अगर (!map->members)
		वापस false;
	map->first_port = first_port;
	map->last_port = last_port;
	set->समयout = IPSET_NO_TIMEOUT;

	map->set = set;
	set->data = map;
	set->family = NFPROTO_UNSPEC;

	वापस true;
पूर्ण

अटल पूर्णांक
biपंचांगap_port_create(काष्ठा net *net, काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		   u32 flags)
अणु
	काष्ठा biपंचांगap_port *map;
	u16 first_port, last_port;
	u32 elements;

	अगर (unlikely(!ip_set_attr_netorder(tb, IPSET_ATTR_PORT) ||
		     !ip_set_attr_netorder(tb, IPSET_ATTR_PORT_TO) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_TIMEOUT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	first_port = ip_set_get_h16(tb[IPSET_ATTR_PORT]);
	last_port = ip_set_get_h16(tb[IPSET_ATTR_PORT_TO]);
	अगर (first_port > last_port)
		swap(first_port, last_port);

	elements = last_port - first_port + 1;
	set->dsize = ip_set_elem_len(set, tb, 0, 0);
	map = ip_set_alloc(माप(*map) + elements * set->dsize);
	अगर (!map)
		वापस -ENOMEM;

	map->elements = elements;
	map->memsize = BITS_TO_LONGS(elements) * माप(अचिन्हित दीर्घ);
	set->variant = &biपंचांगap_port;
	अगर (!init_map_port(set, map, first_port, last_port)) अणु
		ip_set_मुक्त(map);
		वापस -ENOMEM;
	पूर्ण
	अगर (tb[IPSET_ATTR_TIMEOUT]) अणु
		set->समयout = ip_set_समयout_uget(tb[IPSET_ATTR_TIMEOUT]);
		biपंचांगap_port_gc_init(set, biपंचांगap_port_gc);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ip_set_type biपंचांगap_port_type = अणु
	.name		= "bitmap:port",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_PORT,
	.dimension	= IPSET_DIM_ONE,
	.family		= NFPROTO_UNSPEC,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create		= biपंचांगap_port_create,
	.create_policy	= अणु
		[IPSET_ATTR_PORT]	= अणु .type = NLA_U16 पूर्ण,
		[IPSET_ATTR_PORT_TO]	= अणु .type = NLA_U16 पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	पूर्ण,
	.adt_policy	= अणु
		[IPSET_ATTR_PORT]	= अणु .type = NLA_U16 पूर्ण,
		[IPSET_ATTR_PORT_TO]	= अणु .type = NLA_U16 पूर्ण,
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
biपंचांगap_port_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&biपंचांगap_port_type);
पूर्ण

अटल व्योम __निकास
biपंचांगap_port_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&biपंचांगap_port_type);
पूर्ण

module_init(biपंचांगap_port_init);
module_निकास(biपंचांगap_port_fini);
