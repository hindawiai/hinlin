<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * iptables module क्रम DCCP protocol header matching
 *
 * (C) 2005 by Harald Welte <laक्रमge@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/ip.h>
#समावेश <linux/dccp.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_dccp.h>

#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: DCCP protocol packet match");
MODULE_ALIAS("ipt_dccp");
MODULE_ALIAS("ip6t_dccp");

#घोषणा DCCHECK(cond, option, flag, invflag) (!((flag) & (option)) \
				  || (!!((invflag) & (option)) ^ (cond)))

अटल अचिन्हित अक्षर *dccp_optbuf;
अटल DEFINE_SPINLOCK(dccp_buflock);

अटल अंतरभूत bool
dccp_find_option(u_पूर्णांक8_t option,
		 स्थिर काष्ठा sk_buff *skb,
		 अचिन्हित पूर्णांक protoff,
		 स्थिर काष्ठा dccp_hdr *dh,
		 bool *hotdrop)
अणु
	/* tcp.करोff is only 4 bits, ie. max 15 * 4 bytes */
	स्थिर अचिन्हित अक्षर *op;
	अचिन्हित पूर्णांक optoff = __dccp_hdr_len(dh);
	अचिन्हित पूर्णांक optlen = dh->dccph_करोff*4 - __dccp_hdr_len(dh);
	अचिन्हित पूर्णांक i;

	अगर (dh->dccph_करोff * 4 < __dccp_hdr_len(dh))
		जाओ invalid;

	अगर (!optlen)
		वापस false;

	spin_lock_bh(&dccp_buflock);
	op = skb_header_poपूर्णांकer(skb, protoff + optoff, optlen, dccp_optbuf);
	अगर (op == शून्य) अणु
		/* If we करोn't have the whole header, drop packet. */
		जाओ partial;
	पूर्ण

	क्रम (i = 0; i < optlen; ) अणु
		अगर (op[i] == option) अणु
			spin_unlock_bh(&dccp_buflock);
			वापस true;
		पूर्ण

		अगर (op[i] < 2)
			i++;
		अन्यथा
			i += op[i+1]?:1;
	पूर्ण

	spin_unlock_bh(&dccp_buflock);
	वापस false;

partial:
	spin_unlock_bh(&dccp_buflock);
invalid:
	*hotdrop = true;
	वापस false;
पूर्ण


अटल अंतरभूत bool
match_types(स्थिर काष्ठा dccp_hdr *dh, u_पूर्णांक16_t typemask)
अणु
	वापस typemask & (1 << dh->dccph_type);
पूर्ण

अटल अंतरभूत bool
match_option(u_पूर्णांक8_t option, स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
	     स्थिर काष्ठा dccp_hdr *dh, bool *hotdrop)
अणु
	वापस dccp_find_option(option, skb, protoff, dh, hotdrop);
पूर्ण

अटल bool
dccp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_dccp_info *info = par->matchinfo;
	स्थिर काष्ठा dccp_hdr *dh;
	काष्ठा dccp_hdr _dh;

	अगर (par->fragoff != 0)
		वापस false;

	dh = skb_header_poपूर्णांकer(skb, par->thoff, माप(_dh), &_dh);
	अगर (dh == शून्य) अणु
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस  DCCHECK(ntohs(dh->dccph_sport) >= info->spts[0]
			&& ntohs(dh->dccph_sport) <= info->spts[1],
			XT_DCCP_SRC_PORTS, info->flags, info->invflags)
		&& DCCHECK(ntohs(dh->dccph_dport) >= info->dpts[0]
			&& ntohs(dh->dccph_dport) <= info->dpts[1],
			XT_DCCP_DEST_PORTS, info->flags, info->invflags)
		&& DCCHECK(match_types(dh, info->typemask),
			   XT_DCCP_TYPE, info->flags, info->invflags)
		&& DCCHECK(match_option(info->option, skb, par->thoff, dh,
					&par->hotdrop),
			   XT_DCCP_OPTION, info->flags, info->invflags);
पूर्ण

अटल पूर्णांक dccp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_dccp_info *info = par->matchinfo;

	अगर (info->flags & ~XT_DCCP_VALID_FLAGS)
		वापस -EINVAL;
	अगर (info->invflags & ~XT_DCCP_VALID_FLAGS)
		वापस -EINVAL;
	अगर (info->invflags & ~info->flags)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_match dccp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name 		= "dccp",
		.family		= NFPROTO_IPV4,
		.checkentry	= dccp_mt_check,
		.match		= dccp_mt,
		.matchsize	= माप(काष्ठा xt_dccp_info),
		.proto		= IPPROTO_DCCP,
		.me 		= THIS_MODULE,
	पूर्ण,
	अणु
		.name 		= "dccp",
		.family		= NFPROTO_IPV6,
		.checkentry	= dccp_mt_check,
		.match		= dccp_mt,
		.matchsize	= माप(काष्ठा xt_dccp_info),
		.proto		= IPPROTO_DCCP,
		.me 		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dccp_mt_init(व्योम)
अणु
	पूर्णांक ret;

	/* करोff is 8 bits, so the maximum option size is (4*256).  Don't put
	 * this in BSS since DaveM is worried about locked TLB's क्रम kernel
	 * BSS. */
	dccp_optbuf = kदो_स्मृति(256 * 4, GFP_KERNEL);
	अगर (!dccp_optbuf)
		वापस -ENOMEM;
	ret = xt_रेजिस्टर_matches(dccp_mt_reg, ARRAY_SIZE(dccp_mt_reg));
	अगर (ret)
		जाओ out_kमुक्त;
	वापस ret;

out_kमुक्त:
	kमुक्त(dccp_optbuf);
	वापस ret;
पूर्ण

अटल व्योम __निकास dccp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(dccp_mt_reg, ARRAY_SIZE(dccp_mt_reg));
	kमुक्त(dccp_optbuf);
पूर्ण

module_init(dccp_mt_init);
module_निकास(dccp_mt_निकास);
