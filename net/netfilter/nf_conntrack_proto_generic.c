<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netfilter.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>

अटल स्थिर अचिन्हित पूर्णांक nf_ct_generic_समयout = 600*HZ;

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक generic_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
					 काष्ठा net *net, व्योम *data)
अणु
	काष्ठा nf_generic_net *gn = nf_generic_pernet(net);
	अचिन्हित पूर्णांक *समयout = data;

	अगर (!समयout)
		समयout = &gn->समयout;

	अगर (tb[CTA_TIMEOUT_GENERIC_TIMEOUT])
		*समयout =
		    ntohl(nla_get_be32(tb[CTA_TIMEOUT_GENERIC_TIMEOUT])) * HZ;
	अन्यथा अणु
		/* Set शेष generic समयout. */
		*समयout = gn->समयout;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
generic_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *समयout = data;

	अगर (nla_put_be32(skb, CTA_TIMEOUT_GENERIC_TIMEOUT, htonl(*समयout / HZ)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
        वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
generic_समयout_nla_policy[CTA_TIMEOUT_GENERIC_MAX+1] = अणु
	[CTA_TIMEOUT_GENERIC_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_generic_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_generic_net *gn = nf_generic_pernet(net);

	gn->समयout = nf_ct_generic_समयout;
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_generic =
अणु
	.l4proto		= 255,
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= generic_समयout_nlattr_to_obj,
		.obj_to_nlattr	= generic_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_GENERIC_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक),
		.nla_policy	= generic_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
