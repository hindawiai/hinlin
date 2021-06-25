<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	xt_conntrack - Netfilter module to match connection tracking
 *	inक्रमmation. (Superset of Rusty's minimalistic state match.)
 *
 *	(C) 2001  Marc Boucher (marc@mbsi.ca).
 *	(C) 2006-2012 Patrick McHardy <kaber@trash.net>
 *	Copyright तऊ CC Computer Consultants GmbH, 2007 - 2008
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/ipv6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_conntrack.h>
#समावेश <net/netfilter/nf_conntrack.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: connection tracking state match");
MODULE_ALIAS("ipt_conntrack");
MODULE_ALIAS("ip6t_conntrack");

अटल bool
conntrack_addrcmp(स्थिर जोड़ nf_inet_addr *kaddr,
                  स्थिर जोड़ nf_inet_addr *uaddr,
                  स्थिर जोड़ nf_inet_addr *umask, अचिन्हित पूर्णांक l3proto)
अणु
	अगर (l3proto == NFPROTO_IPV4)
		वापस ((kaddr->ip ^ uaddr->ip) & umask->ip) == 0;
	अन्यथा अगर (l3proto == NFPROTO_IPV6)
		वापस ipv6_masked_addr_cmp(&kaddr->in6, &umask->in6,
		       &uaddr->in6) == 0;
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत bool
conntrack_mt_origsrc(स्थिर काष्ठा nf_conn *ct,
                     स्थिर काष्ठा xt_conntrack_mtinfo2 *info,
		     u_पूर्णांक8_t family)
अणु
	वापस conntrack_addrcmp(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3,
	       &info->origsrc_addr, &info->origsrc_mask, family);
पूर्ण

अटल अंतरभूत bool
conntrack_mt_origdst(स्थिर काष्ठा nf_conn *ct,
                     स्थिर काष्ठा xt_conntrack_mtinfo2 *info,
		     u_पूर्णांक8_t family)
अणु
	वापस conntrack_addrcmp(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.u3,
	       &info->origdst_addr, &info->origdst_mask, family);
पूर्ण

अटल अंतरभूत bool
conntrack_mt_replsrc(स्थिर काष्ठा nf_conn *ct,
                     स्थिर काष्ठा xt_conntrack_mtinfo2 *info,
		     u_पूर्णांक8_t family)
अणु
	वापस conntrack_addrcmp(&ct->tuplehash[IP_CT_सूची_REPLY].tuple.src.u3,
	       &info->replsrc_addr, &info->replsrc_mask, family);
पूर्ण

अटल अंतरभूत bool
conntrack_mt_repldst(स्थिर काष्ठा nf_conn *ct,
                     स्थिर काष्ठा xt_conntrack_mtinfo2 *info,
		     u_पूर्णांक8_t family)
अणु
	वापस conntrack_addrcmp(&ct->tuplehash[IP_CT_सूची_REPLY].tuple.dst.u3,
	       &info->repldst_addr, &info->repldst_mask, family);
पूर्ण

अटल अंतरभूत bool
ct_proto_port_check(स्थिर काष्ठा xt_conntrack_mtinfo2 *info,
                    स्थिर काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_tuple *tuple;

	tuple = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
	अगर ((info->match_flags & XT_CONNTRACK_PROTO) &&
	    (nf_ct_protonum(ct) == info->l4proto) ^
	    !(info->invert_flags & XT_CONNTRACK_PROTO))
		वापस false;

	/* Shortcut to match all recognized protocols by using ->src.all. */
	अगर ((info->match_flags & XT_CONNTRACK_ORIGSRC_PORT) &&
	    (tuple->src.u.all == info->origsrc_port) ^
	    !(info->invert_flags & XT_CONNTRACK_ORIGSRC_PORT))
		वापस false;

	अगर ((info->match_flags & XT_CONNTRACK_ORIGDST_PORT) &&
	    (tuple->dst.u.all == info->origdst_port) ^
	    !(info->invert_flags & XT_CONNTRACK_ORIGDST_PORT))
		वापस false;

	tuple = &ct->tuplehash[IP_CT_सूची_REPLY].tuple;

	अगर ((info->match_flags & XT_CONNTRACK_REPLSRC_PORT) &&
	    (tuple->src.u.all == info->replsrc_port) ^
	    !(info->invert_flags & XT_CONNTRACK_REPLSRC_PORT))
		वापस false;

	अगर ((info->match_flags & XT_CONNTRACK_REPLDST_PORT) &&
	    (tuple->dst.u.all == info->repldst_port) ^
	    !(info->invert_flags & XT_CONNTRACK_REPLDST_PORT))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool
port_match(u16 min, u16 max, u16 port, bool invert)
अणु
	वापस (port >= min && port <= max) ^ invert;
पूर्ण

अटल अंतरभूत bool
ct_proto_port_check_v3(स्थिर काष्ठा xt_conntrack_mtinfo3 *info,
		       स्थिर काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_tuple *tuple;

	tuple = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
	अगर ((info->match_flags & XT_CONNTRACK_PROTO) &&
	    (nf_ct_protonum(ct) == info->l4proto) ^
	    !(info->invert_flags & XT_CONNTRACK_PROTO))
		वापस false;

	/* Shortcut to match all recognized protocols by using ->src.all. */
	अगर ((info->match_flags & XT_CONNTRACK_ORIGSRC_PORT) &&
	    !port_match(info->origsrc_port, info->origsrc_port_high,
			ntohs(tuple->src.u.all),
			info->invert_flags & XT_CONNTRACK_ORIGSRC_PORT))
		वापस false;

	अगर ((info->match_flags & XT_CONNTRACK_ORIGDST_PORT) &&
	    !port_match(info->origdst_port, info->origdst_port_high,
			ntohs(tuple->dst.u.all),
			info->invert_flags & XT_CONNTRACK_ORIGDST_PORT))
		वापस false;

	tuple = &ct->tuplehash[IP_CT_सूची_REPLY].tuple;

	अगर ((info->match_flags & XT_CONNTRACK_REPLSRC_PORT) &&
	    !port_match(info->replsrc_port, info->replsrc_port_high,
			ntohs(tuple->src.u.all),
			info->invert_flags & XT_CONNTRACK_REPLSRC_PORT))
		वापस false;

	अगर ((info->match_flags & XT_CONNTRACK_REPLDST_PORT) &&
	    !port_match(info->repldst_port, info->repldst_port_high,
			ntohs(tuple->dst.u.all),
			info->invert_flags & XT_CONNTRACK_REPLDST_PORT))
		वापस false;

	वापस true;
पूर्ण

अटल bool
conntrack_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par,
             u16 state_mask, u16 status_mask)
अणु
	स्थिर काष्ठा xt_conntrack_mtinfo2 *info = par->matchinfo;
	क्रमागत ip_conntrack_info ctinfo;
	स्थिर काष्ठा nf_conn *ct;
	अचिन्हित पूर्णांक statebit;

	ct = nf_ct_get(skb, &ctinfo);

	अगर (ct)
		statebit = XT_CONNTRACK_STATE_BIT(ctinfo);
	अन्यथा अगर (ctinfo == IP_CT_UNTRACKED)
		statebit = XT_CONNTRACK_STATE_UNTRACKED;
	अन्यथा
		statebit = XT_CONNTRACK_STATE_INVALID;

	अगर (info->match_flags & XT_CONNTRACK_STATE) अणु
		अगर (ct != शून्य) अणु
			अगर (test_bit(IPS_SRC_NAT_BIT, &ct->status))
				statebit |= XT_CONNTRACK_STATE_SNAT;
			अगर (test_bit(IPS_DST_NAT_BIT, &ct->status))
				statebit |= XT_CONNTRACK_STATE_DNAT;
		पूर्ण
		अगर (!!(state_mask & statebit) ^
		    !(info->invert_flags & XT_CONNTRACK_STATE))
			वापस false;
	पूर्ण

	अगर (ct == शून्य)
		वापस info->match_flags & XT_CONNTRACK_STATE;
	अगर ((info->match_flags & XT_CONNTRACK_सूचीECTION) &&
	    (CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL) ^
	    !(info->invert_flags & XT_CONNTRACK_सूचीECTION))
		वापस false;

	अगर (info->match_flags & XT_CONNTRACK_ORIGSRC)
		अगर (conntrack_mt_origsrc(ct, info, xt_family(par)) ^
		    !(info->invert_flags & XT_CONNTRACK_ORIGSRC))
			वापस false;

	अगर (info->match_flags & XT_CONNTRACK_ORIGDST)
		अगर (conntrack_mt_origdst(ct, info, xt_family(par)) ^
		    !(info->invert_flags & XT_CONNTRACK_ORIGDST))
			वापस false;

	अगर (info->match_flags & XT_CONNTRACK_REPLSRC)
		अगर (conntrack_mt_replsrc(ct, info, xt_family(par)) ^
		    !(info->invert_flags & XT_CONNTRACK_REPLSRC))
			वापस false;

	अगर (info->match_flags & XT_CONNTRACK_REPLDST)
		अगर (conntrack_mt_repldst(ct, info, xt_family(par)) ^
		    !(info->invert_flags & XT_CONNTRACK_REPLDST))
			वापस false;

	अगर (par->match->revision != 3) अणु
		अगर (!ct_proto_port_check(info, ct))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (!ct_proto_port_check_v3(par->matchinfo, ct))
			वापस false;
	पूर्ण

	अगर ((info->match_flags & XT_CONNTRACK_STATUS) &&
	    (!!(status_mask & ct->status) ^
	    !(info->invert_flags & XT_CONNTRACK_STATUS)))
		वापस false;

	अगर (info->match_flags & XT_CONNTRACK_EXPIRES) अणु
		अचिन्हित दीर्घ expires = nf_ct_expires(ct) / HZ;

		अगर ((expires >= info->expires_min &&
		    expires <= info->expires_max) ^
		    !(info->invert_flags & XT_CONNTRACK_EXPIRES))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
conntrack_mt_v1(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_conntrack_mtinfo1 *info = par->matchinfo;

	वापस conntrack_mt(skb, par, info->state_mask, info->status_mask);
पूर्ण

अटल bool
conntrack_mt_v2(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_conntrack_mtinfo2 *info = par->matchinfo;

	वापस conntrack_mt(skb, par, info->state_mask, info->status_mask);
पूर्ण

अटल bool
conntrack_mt_v3(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_conntrack_mtinfo3 *info = par->matchinfo;

	वापस conntrack_mt(skb, par, info->state_mask, info->status_mask);
पूर्ण

अटल पूर्णांक conntrack_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	पूर्णांक ret;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	वापस ret;
पूर्ण

अटल व्योम conntrack_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_match conntrack_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "conntrack",
		.revision   = 1,
		.family     = NFPROTO_UNSPEC,
		.matchsize  = माप(काष्ठा xt_conntrack_mtinfo1),
		.match      = conntrack_mt_v1,
		.checkentry = conntrack_mt_check,
		.destroy    = conntrack_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "conntrack",
		.revision   = 2,
		.family     = NFPROTO_UNSPEC,
		.matchsize  = माप(काष्ठा xt_conntrack_mtinfo2),
		.match      = conntrack_mt_v2,
		.checkentry = conntrack_mt_check,
		.destroy    = conntrack_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "conntrack",
		.revision   = 3,
		.family     = NFPROTO_UNSPEC,
		.matchsize  = माप(काष्ठा xt_conntrack_mtinfo3),
		.match      = conntrack_mt_v3,
		.checkentry = conntrack_mt_check,
		.destroy    = conntrack_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init conntrack_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(conntrack_mt_reg,
	       ARRAY_SIZE(conntrack_mt_reg));
पूर्ण

अटल व्योम __निकास conntrack_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(conntrack_mt_reg, ARRAY_SIZE(conntrack_mt_reg));
पूर्ण

module_init(conntrack_mt_init);
module_निकास(conntrack_mt_निकास);
