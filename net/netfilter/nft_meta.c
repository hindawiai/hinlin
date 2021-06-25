<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2014 Intel Corporation
 * Author: Tomasz Bursztyka <tomasz.bursztyka@linux.पूर्णांकel.com>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/smp.h>
#समावेश <linux/अटल_key.h>
#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h> /* क्रम TCP_TIME_WAIT */
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nft_meta.h>
#समावेश <net/netfilter/nf_tables_offload.h>

#समावेश <uapi/linux/netfilter_bridge.h> /* NF_BR_PRE_ROUTING */

#घोषणा NFT_META_SECS_PER_MINUTE	60
#घोषणा NFT_META_SECS_PER_HOUR		3600
#घोषणा NFT_META_SECS_PER_DAY		86400
#घोषणा NFT_META_DAYS_PER_WEEK		7

अटल DEFINE_PER_CPU(काष्ठा rnd_state, nft_pअक्रमom_state);

अटल u8 nft_meta_weekday(व्योम)
अणु
	समय64_t secs = kसमय_get_real_seconds();
	अचिन्हित पूर्णांक dse;
	u8 wday;

	secs -= NFT_META_SECS_PER_MINUTE * sys_tz.tz_minuteswest;
	dse = भाग_u64(secs, NFT_META_SECS_PER_DAY);
	wday = (4 + dse) % NFT_META_DAYS_PER_WEEK;

	वापस wday;
पूर्ण

अटल u32 nft_meta_hour(समय64_t secs)
अणु
	काष्ठा पंचांग पंचांग;

	समय64_to_पंचांग(secs, 0, &पंचांग);

	वापस पंचांग.पंचांग_hour * NFT_META_SECS_PER_HOUR
		+ पंचांग.पंचांग_min * NFT_META_SECS_PER_MINUTE
		+ पंचांग.पंचांग_sec;
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
nft_meta_get_eval_समय(क्रमागत nft_meta_keys key,
		       u32 *dest)
अणु
	चयन (key) अणु
	हाल NFT_META_TIME_NS:
		nft_reg_store64(dest, kसमय_get_real_ns());
		अवरोध;
	हाल NFT_META_TIME_DAY:
		nft_reg_store8(dest, nft_meta_weekday());
		अवरोध;
	हाल NFT_META_TIME_HOUR:
		*dest = nft_meta_hour(kसमय_get_real_seconds());
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल noअंतरभूत bool
nft_meta_get_eval_pkttype_lo(स्थिर काष्ठा nft_pktinfo *pkt,
			     u32 *dest)
अणु
	स्थिर काष्ठा sk_buff *skb = pkt->skb;

	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		अगर (ipv4_is_multicast(ip_hdr(skb)->daddr))
			nft_reg_store8(dest, PACKET_MULTICAST);
		अन्यथा
			nft_reg_store8(dest, PACKET_BROADCAST);
		अवरोध;
	हाल NFPROTO_IPV6:
		nft_reg_store8(dest, PACKET_MULTICAST);
		अवरोध;
	हाल NFPROTO_NETDEV:
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP): अणु
			पूर्णांक noff = skb_network_offset(skb);
			काष्ठा iphdr *iph, _iph;

			iph = skb_header_poपूर्णांकer(skb, noff,
						 माप(_iph), &_iph);
			अगर (!iph)
				वापस false;

			अगर (ipv4_is_multicast(iph->daddr))
				nft_reg_store8(dest, PACKET_MULTICAST);
			अन्यथा
				nft_reg_store8(dest, PACKET_BROADCAST);

			अवरोध;
		पूर्ण
		हाल htons(ETH_P_IPV6):
			nft_reg_store8(dest, PACKET_MULTICAST);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			वापस false;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल noअंतरभूत bool
nft_meta_get_eval_skugid(क्रमागत nft_meta_keys key,
			 u32 *dest,
			 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा sock *sk = skb_to_full_sk(pkt->skb);
	काष्ठा socket *sock;

	अगर (!sk || !sk_fullsock(sk) || !net_eq(nft_net(pkt), sock_net(sk)))
		वापस false;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	sock = sk->sk_socket;
	अगर (!sock || !sock->file) अणु
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
		वापस false;
	पूर्ण

	चयन (key) अणु
	हाल NFT_META_SKUID:
		*dest = from_kuid_munged(sock_net(sk)->user_ns,
					 sock->file->f_cred->fsuid);
		अवरोध;
	हाल NFT_META_SKGID:
		*dest =	from_kgid_munged(sock_net(sk)->user_ns,
					 sock->file->f_cred->fsgid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
अटल noअंतरभूत bool
nft_meta_get_eval_cgroup(u32 *dest, स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा sock *sk = skb_to_full_sk(pkt->skb);

	अगर (!sk || !sk_fullsock(sk) || !net_eq(nft_net(pkt), sock_net(sk)))
		वापस false;

	*dest = sock_cgroup_classid(&sk->sk_cgrp_data);
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल noअंतरभूत bool nft_meta_get_eval_kind(क्रमागत nft_meta_keys key,
					    u32 *dest,
					    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा net_device *in = nft_in(pkt), *out = nft_out(pkt);

	चयन (key) अणु
	हाल NFT_META_IIFKIND:
		अगर (!in || !in->rtnl_link_ops)
			वापस false;
		म_नकलन((अक्षर *)dest, in->rtnl_link_ops->kind, IFNAMSIZ);
		अवरोध;
	हाल NFT_META_OIFKIND:
		अगर (!out || !out->rtnl_link_ops)
			वापस false;
		म_नकलन((अक्षर *)dest, out->rtnl_link_ops->kind, IFNAMSIZ);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम nft_meta_store_अगरindex(u32 *dest, स्थिर काष्ठा net_device *dev)
अणु
	*dest = dev ? dev->अगरindex : 0;
पूर्ण

अटल व्योम nft_meta_store_अगरname(u32 *dest, स्थिर काष्ठा net_device *dev)
अणु
	म_नकलन((अक्षर *)dest, dev ? dev->name : "", IFNAMSIZ);
पूर्ण

अटल bool nft_meta_store_अगरtype(u32 *dest, स्थिर काष्ठा net_device *dev)
अणु
	अगर (!dev)
		वापस false;

	nft_reg_store16(dest, dev->type);
	वापस true;
पूर्ण

अटल bool nft_meta_store_अगरgroup(u32 *dest, स्थिर काष्ठा net_device *dev)
अणु
	अगर (!dev)
		वापस false;

	*dest = dev->group;
	वापस true;
पूर्ण

अटल bool nft_meta_get_eval_अगरname(क्रमागत nft_meta_keys key, u32 *dest,
				     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	चयन (key) अणु
	हाल NFT_META_IIFNAME:
		nft_meta_store_अगरname(dest, nft_in(pkt));
		अवरोध;
	हाल NFT_META_OIFNAME:
		nft_meta_store_अगरname(dest, nft_out(pkt));
		अवरोध;
	हाल NFT_META_IIF:
		nft_meta_store_अगरindex(dest, nft_in(pkt));
		अवरोध;
	हाल NFT_META_OIF:
		nft_meta_store_अगरindex(dest, nft_out(pkt));
		अवरोध;
	हाल NFT_META_IIFTYPE:
		अगर (!nft_meta_store_अगरtype(dest, nft_in(pkt)))
			वापस false;
		अवरोध;
	हाल NFT_META_OIFTYPE:
		अगर (!nft_meta_store_अगरtype(dest, nft_out(pkt)))
			वापस false;
		अवरोध;
	हाल NFT_META_IIFGROUP:
		अगर (!nft_meta_store_अगरgroup(dest, nft_in(pkt)))
			वापस false;
		अवरोध;
	हाल NFT_META_OIFGROUP:
		अगर (!nft_meta_store_अगरgroup(dest, nft_out(pkt)))
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल noअंतरभूत u32 nft_pअक्रमom_u32(व्योम)
अणु
	काष्ठा rnd_state *state = this_cpu_ptr(&nft_pअक्रमom_state);

	वापस pअक्रमom_u32_state(state);
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
अटल noअंतरभूत bool
nft_meta_get_eval_rtclassid(स्थिर काष्ठा sk_buff *skb, u32 *dest)
अणु
	स्थिर काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (!dst)
		वापस false;

	*dest = dst->tclassid;
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल noअंतरभूत u32 nft_meta_get_eval_sdअगर(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		वापस inet_sdअगर(pkt->skb);
	हाल NFPROTO_IPV6:
		वापस inet6_sdअगर(pkt->skb);
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत व्योम
nft_meta_get_eval_sdअगरname(u32 *dest, स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	u32 sdअगर = nft_meta_get_eval_sdअगर(pkt);
	स्थिर काष्ठा net_device *dev;

	dev = sdअगर ? dev_get_by_index_rcu(nft_net(pkt), sdअगर) : शून्य;
	nft_meta_store_अगरname(dest, dev);
पूर्ण

व्योम nft_meta_get_eval(स्थिर काष्ठा nft_expr *expr,
		       काष्ठा nft_regs *regs,
		       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);
	स्थिर काष्ठा sk_buff *skb = pkt->skb;
	u32 *dest = &regs->data[priv->dreg];

	चयन (priv->key) अणु
	हाल NFT_META_LEN:
		*dest = skb->len;
		अवरोध;
	हाल NFT_META_PROTOCOL:
		nft_reg_store16(dest, (__क्रमce u16)skb->protocol);
		अवरोध;
	हाल NFT_META_NFPROTO:
		nft_reg_store8(dest, nft_pf(pkt));
		अवरोध;
	हाल NFT_META_L4PROTO:
		अगर (!pkt->tprot_set)
			जाओ err;
		nft_reg_store8(dest, pkt->tprot);
		अवरोध;
	हाल NFT_META_PRIORITY:
		*dest = skb->priority;
		अवरोध;
	हाल NFT_META_MARK:
		*dest = skb->mark;
		अवरोध;
	हाल NFT_META_IIF:
	हाल NFT_META_OIF:
	हाल NFT_META_IIFNAME:
	हाल NFT_META_OIFNAME:
	हाल NFT_META_IIFTYPE:
	हाल NFT_META_OIFTYPE:
	हाल NFT_META_IIFGROUP:
	हाल NFT_META_OIFGROUP:
		अगर (!nft_meta_get_eval_अगरname(priv->key, dest, pkt))
			जाओ err;
		अवरोध;
	हाल NFT_META_SKUID:
	हाल NFT_META_SKGID:
		अगर (!nft_meta_get_eval_skugid(priv->key, dest, pkt))
			जाओ err;
		अवरोध;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	हाल NFT_META_RTCLASSID:
		अगर (!nft_meta_get_eval_rtclassid(skb, dest))
			जाओ err;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETWORK_SECMARK
	हाल NFT_META_SECMARK:
		*dest = skb->secmark;
		अवरोध;
#पूर्ण_अगर
	हाल NFT_META_PKTTYPE:
		अगर (skb->pkt_type != PACKET_LOOPBACK) अणु
			nft_reg_store8(dest, skb->pkt_type);
			अवरोध;
		पूर्ण

		अगर (!nft_meta_get_eval_pkttype_lo(pkt, dest))
			जाओ err;
		अवरोध;
	हाल NFT_META_CPU:
		*dest = raw_smp_processor_id();
		अवरोध;
#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
	हाल NFT_META_CGROUP:
		अगर (!nft_meta_get_eval_cgroup(dest, pkt))
			जाओ err;
		अवरोध;
#पूर्ण_अगर
	हाल NFT_META_PRANDOM:
		*dest = nft_pअक्रमom_u32();
		अवरोध;
#अगर_घोषित CONFIG_XFRM
	हाल NFT_META_SECPATH:
		nft_reg_store8(dest, secpath_exists(skb));
		अवरोध;
#पूर्ण_अगर
	हाल NFT_META_IIFKIND:
	हाल NFT_META_OIFKIND:
		अगर (!nft_meta_get_eval_kind(priv->key, dest, pkt))
			जाओ err;
		अवरोध;
	हाल NFT_META_TIME_NS:
	हाल NFT_META_TIME_DAY:
	हाल NFT_META_TIME_HOUR:
		nft_meta_get_eval_समय(priv->key, dest);
		अवरोध;
	हाल NFT_META_SDIF:
		*dest = nft_meta_get_eval_sdअगर(pkt);
		अवरोध;
	हाल NFT_META_SDIFNAME:
		nft_meta_get_eval_sdअगरname(dest, pkt);
		अवरोध;
	शेष:
		WARN_ON(1);
		जाओ err;
	पूर्ण
	वापस;

err:
	regs->verdict.code = NFT_BREAK;
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_get_eval);

व्योम nft_meta_set_eval(स्थिर काष्ठा nft_expr *expr,
		       काष्ठा nft_regs *regs,
		       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_meta *meta = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	u32 *sreg = &regs->data[meta->sreg];
	u32 value = *sreg;
	u8 value8;

	चयन (meta->key) अणु
	हाल NFT_META_MARK:
		skb->mark = value;
		अवरोध;
	हाल NFT_META_PRIORITY:
		skb->priority = value;
		अवरोध;
	हाल NFT_META_PKTTYPE:
		value8 = nft_reg_load8(sreg);

		अगर (skb->pkt_type != value8 &&
		    skb_pkt_type_ok(value8) &&
		    skb_pkt_type_ok(skb->pkt_type))
			skb->pkt_type = value8;
		अवरोध;
	हाल NFT_META_NFTRACE:
		value8 = nft_reg_load8(sreg);

		skb->nf_trace = !!value8;
		अवरोध;
#अगर_घोषित CONFIG_NETWORK_SECMARK
	हाल NFT_META_SECMARK:
		skb->secmark = value;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_set_eval);

स्थिर काष्ठा nla_policy nft_meta_policy[NFTA_META_MAX + 1] = अणु
	[NFTA_META_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_META_KEY]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_META_SREG]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(nft_meta_policy);

पूर्णांक nft_meta_get_init(स्थिर काष्ठा nft_ctx *ctx,
		      स्थिर काष्ठा nft_expr *expr,
		      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_meta *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;

	priv->key = ntohl(nla_get_be32(tb[NFTA_META_KEY]));
	चयन (priv->key) अणु
	हाल NFT_META_PROTOCOL:
	हाल NFT_META_IIFTYPE:
	हाल NFT_META_OIFTYPE:
		len = माप(u16);
		अवरोध;
	हाल NFT_META_NFPROTO:
	हाल NFT_META_L4PROTO:
	हाल NFT_META_LEN:
	हाल NFT_META_PRIORITY:
	हाल NFT_META_MARK:
	हाल NFT_META_IIF:
	हाल NFT_META_OIF:
	हाल NFT_META_SDIF:
	हाल NFT_META_SKUID:
	हाल NFT_META_SKGID:
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	हाल NFT_META_RTCLASSID:
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETWORK_SECMARK
	हाल NFT_META_SECMARK:
#पूर्ण_अगर
	हाल NFT_META_PKTTYPE:
	हाल NFT_META_CPU:
	हाल NFT_META_IIFGROUP:
	हाल NFT_META_OIFGROUP:
#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
	हाल NFT_META_CGROUP:
#पूर्ण_अगर
		len = माप(u32);
		अवरोध;
	हाल NFT_META_IIFNAME:
	हाल NFT_META_OIFNAME:
	हाल NFT_META_IIFKIND:
	हाल NFT_META_OIFKIND:
	हाल NFT_META_SDIFNAME:
		len = IFNAMSIZ;
		अवरोध;
	हाल NFT_META_PRANDOM:
		pअक्रमom_init_once(&nft_pअक्रमom_state);
		len = माप(u32);
		अवरोध;
#अगर_घोषित CONFIG_XFRM
	हाल NFT_META_SECPATH:
		len = माप(u8);
		अवरोध;
#पूर्ण_अगर
	हाल NFT_META_TIME_NS:
		len = माप(u64);
		अवरोध;
	हाल NFT_META_TIME_DAY:
		len = माप(u8);
		अवरोध;
	हाल NFT_META_TIME_HOUR:
		len = माप(u32);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_META_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, len);
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_get_init);

अटल पूर्णांक nft_meta_get_validate_sdअगर(स्थिर काष्ठा nft_ctx *ctx)
अणु
	अचिन्हित पूर्णांक hooks;

	चयन (ctx->family) अणु
	हाल NFPROTO_IPV4:
	हाल NFPROTO_IPV6:
	हाल NFPROTO_INET:
		hooks = (1 << NF_INET_LOCAL_IN) |
			(1 << NF_INET_FORWARD);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_chain_validate_hooks(ctx->chain, hooks);
पूर्ण

अटल पूर्णांक nft_meta_get_validate_xfrm(स्थिर काष्ठा nft_ctx *ctx)
अणु
#अगर_घोषित CONFIG_XFRM
	अचिन्हित पूर्णांक hooks;

	चयन (ctx->family) अणु
	हाल NFPROTO_NETDEV:
		hooks = 1 << NF_NETDEV_INGRESS;
		अवरोध;
	हाल NFPROTO_IPV4:
	हाल NFPROTO_IPV6:
	हाल NFPROTO_INET:
		hooks = (1 << NF_INET_PRE_ROUTING) |
			(1 << NF_INET_LOCAL_IN) |
			(1 << NF_INET_FORWARD);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_chain_validate_hooks(ctx->chain, hooks);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक nft_meta_get_validate(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_expr *expr,
				 स्थिर काष्ठा nft_data **data)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);

	चयन (priv->key) अणु
	हाल NFT_META_SECPATH:
		वापस nft_meta_get_validate_xfrm(ctx);
	हाल NFT_META_SDIF:
	हाल NFT_META_SDIFNAME:
		वापस nft_meta_get_validate_sdअगर(ctx);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nft_meta_set_validate(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr,
			  स्थिर काष्ठा nft_data **data)
अणु
	काष्ठा nft_meta *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक hooks;

	अगर (priv->key != NFT_META_PKTTYPE)
		वापस 0;

	चयन (ctx->family) अणु
	हाल NFPROTO_BRIDGE:
		hooks = 1 << NF_BR_PRE_ROUTING;
		अवरोध;
	हाल NFPROTO_NETDEV:
		hooks = 1 << NF_NETDEV_INGRESS;
		अवरोध;
	हाल NFPROTO_IPV4:
	हाल NFPROTO_IPV6:
	हाल NFPROTO_INET:
		hooks = 1 << NF_INET_PRE_ROUTING;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_chain_validate_hooks(ctx->chain, hooks);
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_set_validate);

पूर्णांक nft_meta_set_init(स्थिर काष्ठा nft_ctx *ctx,
		      स्थिर काष्ठा nft_expr *expr,
		      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_meta *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	priv->key = ntohl(nla_get_be32(tb[NFTA_META_KEY]));
	चयन (priv->key) अणु
	हाल NFT_META_MARK:
	हाल NFT_META_PRIORITY:
#अगर_घोषित CONFIG_NETWORK_SECMARK
	हाल NFT_META_SECMARK:
#पूर्ण_अगर
		len = माप(u32);
		अवरोध;
	हाल NFT_META_NFTRACE:
		len = माप(u8);
		अवरोध;
	हाल NFT_META_PKTTYPE:
		len = माप(u8);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = nft_parse_रेजिस्टर_load(tb[NFTA_META_SREG], &priv->sreg, len);
	अगर (err < 0)
		वापस err;

	अगर (priv->key == NFT_META_NFTRACE)
		अटल_branch_inc(&nft_trace_enabled);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_set_init);

पूर्णांक nft_meta_get_dump(काष्ठा sk_buff *skb,
		      स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);

	अगर (nla_put_be32(skb, NFTA_META_KEY, htonl(priv->key)))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_META_DREG, priv->dreg))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_get_dump);

पूर्णांक nft_meta_set_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);

	अगर (nla_put_be32(skb, NFTA_META_KEY, htonl(priv->key)))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_META_SREG, priv->sreg))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_set_dump);

व्योम nft_meta_set_destroy(स्थिर काष्ठा nft_ctx *ctx,
			  स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);

	अगर (priv->key == NFT_META_NFTRACE)
		अटल_branch_dec(&nft_trace_enabled);
पूर्ण
EXPORT_SYMBOL_GPL(nft_meta_set_destroy);

अटल पूर्णांक nft_meta_get_offload(काष्ठा nft_offload_ctx *ctx,
				काष्ठा nft_flow_rule *flow,
				स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);
	काष्ठा nft_offload_reg *reg = &ctx->regs[priv->dreg];

	चयन (priv->key) अणु
	हाल NFT_META_PROTOCOL:
		NFT_OFFLOAD_MATCH_EXACT(FLOW_DISSECTOR_KEY_BASIC, basic, n_proto,
					माप(__u16), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_NETWORK);
		अवरोध;
	हाल NFT_META_L4PROTO:
		NFT_OFFLOAD_MATCH_EXACT(FLOW_DISSECTOR_KEY_BASIC, basic, ip_proto,
					माप(__u8), reg);
		nft_offload_set_dependency(ctx, NFT_OFFLOAD_DEP_TRANSPORT);
		अवरोध;
	हाल NFT_META_IIF:
		NFT_OFFLOAD_MATCH_EXACT(FLOW_DISSECTOR_KEY_META, meta,
					ingress_अगरindex, माप(__u32), reg);
		अवरोध;
	हाल NFT_META_IIFTYPE:
		NFT_OFFLOAD_MATCH_EXACT(FLOW_DISSECTOR_KEY_META, meta,
					ingress_अगरtype, माप(__u16), reg);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_meta_get_ops = अणु
	.type		= &nft_meta_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_meta)),
	.eval		= nft_meta_get_eval,
	.init		= nft_meta_get_init,
	.dump		= nft_meta_get_dump,
	.validate	= nft_meta_get_validate,
	.offload	= nft_meta_get_offload,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_meta_set_ops = अणु
	.type		= &nft_meta_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_meta)),
	.eval		= nft_meta_set_eval,
	.init		= nft_meta_set_init,
	.destroy	= nft_meta_set_destroy,
	.dump		= nft_meta_set_dump,
	.validate	= nft_meta_set_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_meta_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_META_KEY] == शून्य)
		वापस ERR_PTR(-EINVAL);

	अगर (tb[NFTA_META_DREG] && tb[NFTA_META_SREG])
		वापस ERR_PTR(-EINVAL);

#अगर IS_ENABLED(CONFIG_NF_TABLES_BRIDGE) && IS_MODULE(CONFIG_NFT_BRIDGE_META)
	अगर (ctx->family == NFPROTO_BRIDGE)
		वापस ERR_PTR(-EAGAIN);
#पूर्ण_अगर
	अगर (tb[NFTA_META_DREG])
		वापस &nft_meta_get_ops;

	अगर (tb[NFTA_META_SREG])
		वापस &nft_meta_set_ops;

	वापस ERR_PTR(-EINVAL);
पूर्ण

काष्ठा nft_expr_type nft_meta_type __पढ़ो_mostly = अणु
	.name		= "meta",
	.select_ops	= nft_meta_select_ops,
	.policy		= nft_meta_policy,
	.maxattr	= NFTA_META_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_NETWORK_SECMARK
काष्ठा nft_secmark अणु
	u32 secid;
	अक्षर *ctx;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_secmark_policy[NFTA_SECMARK_MAX + 1] = अणु
	[NFTA_SECMARK_CTX]     = अणु .type = NLA_STRING, .len = NFT_SECMARK_CTX_MAXLEN पूर्ण,
पूर्ण;

अटल पूर्णांक nft_secmark_compute_secid(काष्ठा nft_secmark *priv)
अणु
	u32 पंचांगp_secid = 0;
	पूर्णांक err;

	err = security_secctx_to_secid(priv->ctx, म_माप(priv->ctx), &पंचांगp_secid);
	अगर (err)
		वापस err;

	अगर (!पंचांगp_secid)
		वापस -ENOENT;

	err = security_secmark_relabel_packet(पंचांगp_secid);
	अगर (err)
		वापस err;

	priv->secid = पंचांगp_secid;
	वापस 0;
पूर्ण

अटल व्योम nft_secmark_obj_eval(काष्ठा nft_object *obj, काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_secmark *priv = nft_obj_data(obj);
	काष्ठा sk_buff *skb = pkt->skb;

	skb->secmark = priv->secid;
पूर्ण

अटल पूर्णांक nft_secmark_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nlattr * स्थिर tb[],
				काष्ठा nft_object *obj)
अणु
	काष्ठा nft_secmark *priv = nft_obj_data(obj);
	पूर्णांक err;

	अगर (tb[NFTA_SECMARK_CTX] == शून्य)
		वापस -EINVAL;

	priv->ctx = nla_strdup(tb[NFTA_SECMARK_CTX], GFP_KERNEL);
	अगर (!priv->ctx)
		वापस -ENOMEM;

	err = nft_secmark_compute_secid(priv);
	अगर (err) अणु
		kमुक्त(priv->ctx);
		वापस err;
	पूर्ण

	security_secmark_refcount_inc();

	वापस 0;
पूर्ण

अटल पूर्णांक nft_secmark_obj_dump(काष्ठा sk_buff *skb, काष्ठा nft_object *obj,
				bool reset)
अणु
	काष्ठा nft_secmark *priv = nft_obj_data(obj);
	पूर्णांक err;

	अगर (nla_put_string(skb, NFTA_SECMARK_CTX, priv->ctx))
		वापस -1;

	अगर (reset) अणु
		err = nft_secmark_compute_secid(priv);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nft_secmark_obj_destroy(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_object *obj)
अणु
	काष्ठा nft_secmark *priv = nft_obj_data(obj);

	security_secmark_refcount_dec();

	kमुक्त(priv->ctx);
पूर्ण

अटल स्थिर काष्ठा nft_object_ops nft_secmark_obj_ops = अणु
	.type		= &nft_secmark_obj_type,
	.size		= माप(काष्ठा nft_secmark),
	.init		= nft_secmark_obj_init,
	.eval		= nft_secmark_obj_eval,
	.dump		= nft_secmark_obj_dump,
	.destroy	= nft_secmark_obj_destroy,
पूर्ण;
काष्ठा nft_object_type nft_secmark_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_SECMARK,
	.ops		= &nft_secmark_obj_ops,
	.maxattr	= NFTA_SECMARK_MAX,
	.policy		= nft_secmark_policy,
	.owner		= THIS_MODULE,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NETWORK_SECMARK */
