<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/dst_cache.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/protocol.h>
#समावेश <uapi/linux/ila.h>
#समावेश "ila.h"

काष्ठा ila_lwt अणु
	काष्ठा ila_params p;
	काष्ठा dst_cache dst_cache;
	u32 connected : 1;
	u32 lwt_output : 1;
पूर्ण;

अटल अंतरभूत काष्ठा ila_lwt *ila_lwt_lwtunnel(
	काष्ठा lwtunnel_state *lwt)
अणु
	वापस (काष्ठा ila_lwt *)lwt->data;
पूर्ण

अटल अंतरभूत काष्ठा ila_params *ila_params_lwtunnel(
	काष्ठा lwtunnel_state *lwt)
अणु
	वापस &ila_lwt_lwtunnel(lwt)->p;
पूर्ण

अटल पूर्णांक ila_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *orig_dst = skb_dst(skb);
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)orig_dst;
	काष्ठा ila_lwt *ilwt = ila_lwt_lwtunnel(orig_dst->lwtstate);
	काष्ठा dst_entry *dst;
	पूर्णांक err = -EINVAL;

	अगर (skb->protocol != htons(ETH_P_IPV6))
		जाओ drop;

	अगर (ilwt->lwt_output)
		ila_update_ipv6_locator(skb,
					ila_params_lwtunnel(orig_dst->lwtstate),
					true);

	अगर (rt->rt6i_flags & (RTF_GATEWAY | RTF_CACHE)) अणु
		/* Alपढ़ोy have a next hop address in route, no need क्रम
		 * dest cache route.
		 */
		वापस orig_dst->lwtstate->orig_output(net, sk, skb);
	पूर्ण

	dst = dst_cache_get(&ilwt->dst_cache);
	अगर (unlikely(!dst)) अणु
		काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
		काष्ठा flowi6 fl6;

		/* Lookup a route क्रम the new destination. Take पूर्णांकo
		 * account that the base route may alपढ़ोy have a gateway.
		 */

		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_oअगर = orig_dst->dev->अगरindex;
		fl6.flowi6_iअगर = LOOPBACK_IFINDEX;
		fl6.daddr = *rt6_nexthop((काष्ठा rt6_info *)orig_dst,
					 &ip6h->daddr);

		dst = ip6_route_output(net, शून्य, &fl6);
		अगर (dst->error) अणु
			err = -EHOSTUNREACH;
			dst_release(dst);
			जाओ drop;
		पूर्ण

		dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), शून्य, 0);
		अगर (IS_ERR(dst)) अणु
			err = PTR_ERR(dst);
			जाओ drop;
		पूर्ण

		अगर (ilwt->connected)
			dst_cache_set_ip6(&ilwt->dst_cache, dst, &fl6.saddr);
	पूर्ण

	skb_dst_set(skb, dst);
	वापस dst_output(net, sk, skb);

drop:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक ila_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा ila_lwt *ilwt = ila_lwt_lwtunnel(dst->lwtstate);

	अगर (skb->protocol != htons(ETH_P_IPV6))
		जाओ drop;

	अगर (!ilwt->lwt_output)
		ila_update_ipv6_locator(skb,
					ila_params_lwtunnel(dst->lwtstate),
					false);

	वापस dst->lwtstate->orig_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nla_policy ila_nl_policy[ILA_ATTR_MAX + 1] = अणु
	[ILA_ATTR_LOCATOR] = अणु .type = NLA_U64, पूर्ण,
	[ILA_ATTR_CSUM_MODE] = अणु .type = NLA_U8, पूर्ण,
	[ILA_ATTR_IDENT_TYPE] = अणु .type = NLA_U8, पूर्ण,
	[ILA_ATTR_HOOK_TYPE] = अणु .type = NLA_U8, पूर्ण,
पूर्ण;

अटल पूर्णांक ila_build_state(काष्ठा net *net, काष्ठा nlattr *nla,
			   अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			   काष्ठा lwtunnel_state **ts,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ila_lwt *ilwt;
	काष्ठा ila_params *p;
	काष्ठा nlattr *tb[ILA_ATTR_MAX + 1];
	काष्ठा lwtunnel_state *newts;
	स्थिर काष्ठा fib6_config *cfg6 = cfg;
	काष्ठा ila_addr *iaddr;
	u8 ident_type = ILA_ATYPE_USE_FORMAT;
	u8 hook_type = ILA_HOOK_ROUTE_OUTPUT;
	u8 csum_mode = ILA_CSUM_NO_ACTION;
	bool lwt_output = true;
	u8 eff_ident_type;
	पूर्णांक ret;

	अगर (family != AF_INET6)
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(tb, ILA_ATTR_MAX, nla,
					  ila_nl_policy, extack);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[ILA_ATTR_LOCATOR])
		वापस -EINVAL;

	iaddr = (काष्ठा ila_addr *)&cfg6->fc_dst;

	अगर (tb[ILA_ATTR_IDENT_TYPE])
		ident_type = nla_get_u8(tb[ILA_ATTR_IDENT_TYPE]);

	अगर (ident_type == ILA_ATYPE_USE_FORMAT) अणु
		/* Infer identअगरier type from type field in क्रमmatted
		 * identअगरier.
		 */

		अगर (cfg6->fc_dst_len < 8 * माप(काष्ठा ila_locator) + 3) अणु
			/* Need to have full locator and at least type field
			 * included in destination
			 */
			वापस -EINVAL;
		पूर्ण

		eff_ident_type = iaddr->ident.type;
	पूर्ण अन्यथा अणु
		eff_ident_type = ident_type;
	पूर्ण

	चयन (eff_ident_type) अणु
	हाल ILA_ATYPE_IID:
		/* Don't allow ILA क्रम IID type */
		वापस -EINVAL;
	हाल ILA_ATYPE_LUID:
		अवरोध;
	हाल ILA_ATYPE_VIRT_V4:
	हाल ILA_ATYPE_VIRT_UNI_V6:
	हाल ILA_ATYPE_VIRT_MULTI_V6:
	हाल ILA_ATYPE_NONLOCAL_ADDR:
		/* These ILA क्रमmats are not supported yet. */
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tb[ILA_ATTR_HOOK_TYPE])
		hook_type = nla_get_u8(tb[ILA_ATTR_HOOK_TYPE]);

	चयन (hook_type) अणु
	हाल ILA_HOOK_ROUTE_OUTPUT:
		lwt_output = true;
		अवरोध;
	हाल ILA_HOOK_ROUTE_INPUT:
		lwt_output = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tb[ILA_ATTR_CSUM_MODE])
		csum_mode = nla_get_u8(tb[ILA_ATTR_CSUM_MODE]);

	अगर (csum_mode == ILA_CSUM_NEUTRAL_MAP &&
	    ila_csum_neutral_set(iaddr->ident)) अणु
		/* Don't allow translation अगर checksum neutral bit is
		 * configured and it's set in the SIR address.
		 */
		वापस -EINVAL;
	पूर्ण

	newts = lwtunnel_state_alloc(माप(*ilwt));
	अगर (!newts)
		वापस -ENOMEM;

	ilwt = ila_lwt_lwtunnel(newts);
	ret = dst_cache_init(&ilwt->dst_cache, GFP_ATOMIC);
	अगर (ret) अणु
		kमुक्त(newts);
		वापस ret;
	पूर्ण

	ilwt->lwt_output = !!lwt_output;

	p = ila_params_lwtunnel(newts);

	p->csum_mode = csum_mode;
	p->ident_type = ident_type;
	p->locator.v64 = (__क्रमce __be64)nla_get_u64(tb[ILA_ATTR_LOCATOR]);

	/* Precompute checksum dअगरference क्रम translation since we
	 * know both the old locator and the new one.
	 */
	p->locator_match = iaddr->loc;

	ila_init_saved_csum(p);

	newts->type = LWTUNNEL_ENCAP_ILA;
	newts->flags |= LWTUNNEL_STATE_OUTPUT_REसूचीECT |
			LWTUNNEL_STATE_INPUT_REसूचीECT;

	अगर (cfg6->fc_dst_len == 8 * माप(काष्ठा in6_addr))
		ilwt->connected = 1;

	*ts = newts;

	वापस 0;
पूर्ण

अटल व्योम ila_destroy_state(काष्ठा lwtunnel_state *lwt)
अणु
	dst_cache_destroy(&ila_lwt_lwtunnel(lwt)->dst_cache);
पूर्ण

अटल पूर्णांक ila_fill_encap_info(काष्ठा sk_buff *skb,
			       काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा ila_params *p = ila_params_lwtunnel(lwtstate);
	काष्ठा ila_lwt *ilwt = ila_lwt_lwtunnel(lwtstate);

	अगर (nla_put_u64_64bit(skb, ILA_ATTR_LOCATOR, (__क्रमce u64)p->locator.v64,
			      ILA_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, ILA_ATTR_CSUM_MODE, (__क्रमce u8)p->csum_mode))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, ILA_ATTR_IDENT_TYPE, (__क्रमce u8)p->ident_type))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, ILA_ATTR_HOOK_TYPE,
		       ilwt->lwt_output ? ILA_HOOK_ROUTE_OUTPUT :
					  ILA_HOOK_ROUTE_INPUT))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ila_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस nla_total_size_64bit(माप(u64)) + /* ILA_ATTR_LOCATOR */
	       nla_total_size(माप(u8)) +        /* ILA_ATTR_CSUM_MODE */
	       nla_total_size(माप(u8)) +        /* ILA_ATTR_IDENT_TYPE */
	       nla_total_size(माप(u8)) +        /* ILA_ATTR_HOOK_TYPE */
	       0;
पूर्ण

अटल पूर्णांक ila_encap_cmp(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	काष्ठा ila_params *a_p = ila_params_lwtunnel(a);
	काष्ठा ila_params *b_p = ila_params_lwtunnel(b);

	वापस (a_p->locator.v64 != b_p->locator.v64);
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops ila_encap_ops = अणु
	.build_state = ila_build_state,
	.destroy_state = ila_destroy_state,
	.output = ila_output,
	.input = ila_input,
	.fill_encap = ila_fill_encap_info,
	.get_encap_size = ila_encap_nlsize,
	.cmp_encap = ila_encap_cmp,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक ila_lwt_init(व्योम)
अणु
	वापस lwtunnel_encap_add_ops(&ila_encap_ops, LWTUNNEL_ENCAP_ILA);
पूर्ण

व्योम ila_lwt_fini(व्योम)
अणु
	lwtunnel_encap_del_ops(&ila_encap_ops, LWTUNNEL_ENCAP_ILA);
पूर्ण
