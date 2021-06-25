<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IP tables module क्रम matching IPsec policy
 *
 * Copyright (c) 2004,2005 Patrick McHardy, <kaber@trash.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <net/xfrm.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/xt_policy.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: IPsec policy match");
MODULE_LICENSE("GPL");

अटल अंतरभूत bool
xt_addr_cmp(स्थिर जोड़ nf_inet_addr *a1, स्थिर जोड़ nf_inet_addr *m,
	    स्थिर जोड़ nf_inet_addr *a2, अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल NFPROTO_IPV4:
		वापस ((a1->ip ^ a2->ip) & m->ip) == 0;
	हाल NFPROTO_IPV6:
		वापस ipv6_masked_addr_cmp(&a1->in6, &m->in6, &a2->in6) == 0;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
match_xfrm_state(स्थिर काष्ठा xfrm_state *x, स्थिर काष्ठा xt_policy_elem *e,
		 अचिन्हित लघु family)
अणु
#घोषणा MATCH_ADDR(x,y,z)	(!e->match.x ||			       \
				 (xt_addr_cmp(&e->x, &e->y, (स्थिर जोड़ nf_inet_addr *)(z), family) \
				  ^ e->invert.x))
#घोषणा MATCH(x,y)		(!e->match.x || ((e->x == (y)) ^ e->invert.x))

	वापस MATCH_ADDR(saddr, smask, &x->props.saddr) &&
	       MATCH_ADDR(daddr, dmask, &x->id.daddr) &&
	       MATCH(proto, x->id.proto) &&
	       MATCH(mode, x->props.mode) &&
	       MATCH(spi, x->id.spi) &&
	       MATCH(reqid, x->props.reqid);
पूर्ण

अटल पूर्णांक
match_policy_in(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा xt_policy_info *info,
		अचिन्हित लघु family)
अणु
	स्थिर काष्ठा xt_policy_elem *e;
	स्थिर काष्ठा sec_path *sp = skb_sec_path(skb);
	पूर्णांक strict = info->flags & XT_POLICY_MATCH_STRICT;
	पूर्णांक i, pos;

	अगर (sp == शून्य)
		वापस -1;
	अगर (strict && info->len != sp->len)
		वापस 0;

	क्रम (i = sp->len - 1; i >= 0; i--) अणु
		pos = strict ? i - sp->len + 1 : 0;
		अगर (pos >= info->len)
			वापस 0;
		e = &info->pol[pos];

		अगर (match_xfrm_state(sp->xvec[i], e, family)) अणु
			अगर (!strict)
				वापस 1;
		पूर्ण अन्यथा अगर (strict)
			वापस 0;
	पूर्ण

	वापस strict ? 1 : 0;
पूर्ण

अटल पूर्णांक
match_policy_out(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा xt_policy_info *info,
		 अचिन्हित लघु family)
अणु
	स्थिर काष्ठा xt_policy_elem *e;
	स्थिर काष्ठा dst_entry *dst = skb_dst(skb);
	पूर्णांक strict = info->flags & XT_POLICY_MATCH_STRICT;
	पूर्णांक i, pos;

	अगर (dst->xfrm == शून्य)
		वापस -1;

	क्रम (i = 0; dst && dst->xfrm;
	     dst = ((काष्ठा xfrm_dst *)dst)->child, i++) अणु
		pos = strict ? i : 0;
		अगर (pos >= info->len)
			वापस 0;
		e = &info->pol[pos];

		अगर (match_xfrm_state(dst->xfrm, e, family)) अणु
			अगर (!strict)
				वापस 1;
		पूर्ण अन्यथा अगर (strict)
			वापस 0;
	पूर्ण

	वापस strict ? i == info->len : 0;
पूर्ण

अटल bool
policy_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_policy_info *info = par->matchinfo;
	पूर्णांक ret;

	अगर (info->flags & XT_POLICY_MATCH_IN)
		ret = match_policy_in(skb, info, xt_family(par));
	अन्यथा
		ret = match_policy_out(skb, info, xt_family(par));

	अगर (ret < 0)
		ret = info->flags & XT_POLICY_MATCH_NONE ? true : false;
	अन्यथा अगर (info->flags & XT_POLICY_MATCH_NONE)
		ret = false;

	वापस ret;
पूर्ण

अटल पूर्णांक policy_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_policy_info *info = par->matchinfo;
	स्थिर अक्षर *errmsg = "neither incoming nor outgoing policy selected";

	अगर (!(info->flags & (XT_POLICY_MATCH_IN|XT_POLICY_MATCH_OUT)))
		जाओ err;

	अगर (par->hook_mask & ((1 << NF_INET_PRE_ROUTING) |
	    (1 << NF_INET_LOCAL_IN)) && info->flags & XT_POLICY_MATCH_OUT) अणु
		errmsg = "output policy not valid in PREROUTING and INPUT";
		जाओ err;
	पूर्ण
	अगर (par->hook_mask & ((1 << NF_INET_POST_ROUTING) |
	    (1 << NF_INET_LOCAL_OUT)) && info->flags & XT_POLICY_MATCH_IN) अणु
		errmsg = "input policy not valid in POSTROUTING and OUTPUT";
		जाओ err;
	पूर्ण
	अगर (info->len > XT_POLICY_MAX_ELEM) अणु
		errmsg = "too many policy elements";
		जाओ err;
	पूर्ण
	वापस 0;
err:
	pr_info_ratelimited("%s\n", errmsg);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा xt_match policy_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "policy",
		.family		= NFPROTO_IPV4,
		.checkentry 	= policy_mt_check,
		.match		= policy_mt,
		.matchsize	= माप(काष्ठा xt_policy_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "policy",
		.family		= NFPROTO_IPV6,
		.checkentry	= policy_mt_check,
		.match		= policy_mt,
		.matchsize	= माप(काष्ठा xt_policy_info),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init policy_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(policy_mt_reg, ARRAY_SIZE(policy_mt_reg));
पूर्ण

अटल व्योम __निकास policy_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(policy_mt_reg, ARRAY_SIZE(policy_mt_reg));
पूर्ण

module_init(policy_mt_init);
module_निकास(policy_mt_निकास);
MODULE_ALIAS("ipt_policy");
MODULE_ALIAS("ip6t_policy");
