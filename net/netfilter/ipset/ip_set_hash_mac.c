<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2014 Jozsef Kadlecsik <kadlec@netfilter.org> */

/* Kernel module implementing an IP set type: the hash:mac type */

#समावेश <linux/jhash.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>
#समावेश <net/netlink.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_hash.h>

#घोषणा IPSET_TYPE_REV_MIN	0
#घोषणा IPSET_TYPE_REV_MAX	1	/* bucketsize, initval support */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("hash:mac", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_hash:mac");

/* Type specअगरic function prefix */
#घोषणा HTYPE		hash_mac

/* Member elements */
काष्ठा hash_mac4_elem अणु
	/* Zero valued IP addresses cannot be stored */
	जोड़ अणु
		अचिन्हित अक्षर ether[ETH_ALEN];
		__be32 foo[2];
	पूर्ण;
पूर्ण;

/* Common functions */

अटल bool
hash_mac4_data_equal(स्थिर काष्ठा hash_mac4_elem *e1,
		     स्थिर काष्ठा hash_mac4_elem *e2,
		     u32 *multi)
अणु
	वापस ether_addr_equal(e1->ether, e2->ether);
पूर्ण

अटल bool
hash_mac4_data_list(काष्ठा sk_buff *skb, स्थिर काष्ठा hash_mac4_elem *e)
अणु
	अगर (nla_put(skb, IPSET_ATTR_ETHER, ETH_ALEN, e->ether))
		जाओ nla_put_failure;
	वापस false;

nla_put_failure:
	वापस true;
पूर्ण

अटल व्योम
hash_mac4_data_next(काष्ठा hash_mac4_elem *next,
		    स्थिर काष्ठा hash_mac4_elem *e)
अणु
पूर्ण

#घोषणा MTYPE		hash_mac4
#घोषणा HOST_MASK	32
#घोषणा IP_SET_EMIT_CREATE
#घोषणा IP_SET_PROTO_UNDEF
#समावेश "ip_set_hash_gen.h"

अटल पूर्णांक
hash_mac4_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
	       स्थिर काष्ठा xt_action_param *par,
	       क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_mac4_elem e = अणु अणु .foo[0] = 0, .foo[1] = 0 पूर्ण पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	अगर (skb_mac_header(skb) < skb->head ||
	    (skb_mac_header(skb) + ETH_HLEN) > skb->data)
		वापस -EINVAL;

	अगर (opt->flags & IPSET_DIM_ONE_SRC)
		ether_addr_copy(e.ether, eth_hdr(skb)->h_source);
	अन्यथा
		ether_addr_copy(e.ether, eth_hdr(skb)->h_dest);

	अगर (is_zero_ether_addr(e.ether))
		वापस -EINVAL;
	वापस adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
पूर्ण

अटल पूर्णांक
hash_mac4_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
	       क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा hash_mac4_elem e = अणु अणु .foo[0] = 0, .foo[1] = 0 पूर्ण पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	पूर्णांक ret;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_ETHER] ||
		     nla_len(tb[IPSET_ATTR_ETHER]) != ETH_ALEN))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;
	ether_addr_copy(e.ether, nla_data(tb[IPSET_ATTR_ETHER]));
	अगर (is_zero_ether_addr(e.ether))
		वापस -IPSET_ERR_HASH_ELEM;

	वापस adtfn(set, &e, &ext, &ext, flags);
पूर्ण

अटल काष्ठा ip_set_type hash_mac_type __पढ़ो_mostly = अणु
	.name		= "hash:mac",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_MAC,
	.dimension	= IPSET_DIM_ONE,
	.family		= NFPROTO_UNSPEC,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create_flags[IPSET_TYPE_REV_MAX] = IPSET_CREATE_FLAG_BUCKETSIZE,
	.create		= hash_mac_create,
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
hash_mac_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&hash_mac_type);
पूर्ण

अटल व्योम __निकास
hash_mac_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&hash_mac_type);
पूर्ण

module_init(hash_mac_init);
module_निकास(hash_mac_fini);
