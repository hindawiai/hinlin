<शैली गुरु>
/*
 * netfilter module to limit the number of parallel tcp
 * connections per IP address.
 *   (c) 2000 Gerd Knorr <kraxel@bytesex.org>
 *   Nov 2002: Martin Bene <martin.bene@icomedias.com>:
 *		only ignore TIME_WAIT or gone connections
 *   (C) CC Computer Consultants GmbH, 2007
 *
 * based on ...
 *
 * Kernel module to match connection tracking inक्रमmation.
 * GPL (C) 1999  Rusty Russell (rusty@rustcorp.com.au).
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_connlimit.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_count.h>

अटल bool
connlimit_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा net *net = xt_net(par);
	स्थिर काष्ठा xt_connlimit_info *info = par->matchinfo;
	काष्ठा nf_conntrack_tuple tuple;
	स्थिर काष्ठा nf_conntrack_tuple *tuple_ptr = &tuple;
	स्थिर काष्ठा nf_conntrack_zone *zone = &nf_ct_zone_dflt;
	क्रमागत ip_conntrack_info ctinfo;
	स्थिर काष्ठा nf_conn *ct;
	अचिन्हित पूर्णांक connections;
	u32 key[5];

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct != शून्य) अणु
		tuple_ptr = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
		zone = nf_ct_zone(ct);
	पूर्ण अन्यथा अगर (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
				      xt_family(par), net, &tuple)) अणु
		जाओ hotdrop;
	पूर्ण

	अगर (xt_family(par) == NFPROTO_IPV6) अणु
		स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
		जोड़ nf_inet_addr addr;
		अचिन्हित पूर्णांक i;

		स_नकल(&addr.ip6, (info->flags & XT_CONNLIMIT_DADDR) ?
		       &iph->daddr : &iph->saddr, माप(addr.ip6));

		क्रम (i = 0; i < ARRAY_SIZE(addr.ip6); ++i)
			addr.ip6[i] &= info->mask.ip6[i];
		स_नकल(key, &addr, माप(addr.ip6));
		key[4] = zone->id;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
		key[0] = (info->flags & XT_CONNLIMIT_DADDR) ?
			  iph->daddr : iph->saddr;

		key[0] &= info->mask.ip;
		key[1] = zone->id;
	पूर्ण

	connections = nf_conncount_count(net, info->data, key, tuple_ptr,
					 zone);
	अगर (connections == 0)
		/* kदो_स्मृति failed, drop it entirely */
		जाओ hotdrop;

	वापस (connections > info->limit) ^ !!(info->flags & XT_CONNLIMIT_INVERT);

 hotdrop:
	par->hotdrop = true;
	वापस false;
पूर्ण

अटल पूर्णांक connlimit_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_connlimit_info *info = par->matchinfo;
	अचिन्हित पूर्णांक keylen;

	keylen = माप(u32);
	अगर (par->family == NFPROTO_IPV6)
		keylen += माप(काष्ठा in6_addr);
	अन्यथा
		keylen += माप(काष्ठा in_addr);

	/* init निजी data */
	info->data = nf_conncount_init(par->net, par->family, keylen);

	वापस PTR_ERR_OR_ZERO(info->data);
पूर्ण

अटल व्योम connlimit_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_connlimit_info *info = par->matchinfo;

	nf_conncount_destroy(par->net, par->family, info->data);
पूर्ण

अटल काष्ठा xt_match connlimit_mt_reg __पढ़ो_mostly = अणु
	.name       = "connlimit",
	.revision   = 1,
	.family     = NFPROTO_UNSPEC,
	.checkentry = connlimit_mt_check,
	.match      = connlimit_mt,
	.matchsize  = माप(काष्ठा xt_connlimit_info),
	.usersize   = दुरत्व(काष्ठा xt_connlimit_info, data),
	.destroy    = connlimit_mt_destroy,
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init connlimit_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&connlimit_mt_reg);
पूर्ण

अटल व्योम __निकास connlimit_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&connlimit_mt_reg);
पूर्ण

module_init(connlimit_mt_init);
module_निकास(connlimit_mt_निकास);
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: Number of connections matching");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_connlimit");
MODULE_ALIAS("ip6t_connlimit");
