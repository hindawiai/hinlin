<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/ip.h> /* क्रम ipv4 options. */
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_flow_table.h>

काष्ठा nft_flow_offload अणु
	काष्ठा nft_flowtable	*flowtable;
पूर्ण;

अटल क्रमागत flow_offload_xmit_type nft_xmit_type(काष्ठा dst_entry *dst)
अणु
	अगर (dst_xfrm(dst))
		वापस FLOW_OFFLOAD_XMIT_XFRM;

	वापस FLOW_OFFLOAD_XMIT_NEIGH;
पूर्ण

अटल व्योम nft_शेष_क्रमward_path(काष्ठा nf_flow_route *route,
				     काष्ठा dst_entry *dst_cache,
				     क्रमागत ip_conntrack_dir dir)
अणु
	route->tuple[!dir].in.अगरindex	= dst_cache->dev->अगरindex;
	route->tuple[dir].dst		= dst_cache;
	route->tuple[dir].xmit_type	= nft_xmit_type(dst_cache);
पूर्ण

अटल पूर्णांक nft_dev_fill_क्रमward_path(स्थिर काष्ठा nf_flow_route *route,
				     स्थिर काष्ठा dst_entry *dst_cache,
				     स्थिर काष्ठा nf_conn *ct,
				     क्रमागत ip_conntrack_dir dir, u8 *ha,
				     काष्ठा net_device_path_stack *stack)
अणु
	स्थिर व्योम *daddr = &ct->tuplehash[!dir].tuple.src.u3;
	काष्ठा net_device *dev = dst_cache->dev;
	काष्ठा neighbour *n;
	u8 nud_state;

	n = dst_neigh_lookup(dst_cache, daddr);
	अगर (!n)
		वापस -1;

	पढ़ो_lock_bh(&n->lock);
	nud_state = n->nud_state;
	ether_addr_copy(ha, n->ha);
	पढ़ो_unlock_bh(&n->lock);
	neigh_release(n);

	अगर (!(nud_state & NUD_VALID))
		वापस -1;

	वापस dev_fill_क्रमward_path(dev, ha, stack);
पूर्ण

काष्ठा nft_क्रमward_info अणु
	स्थिर काष्ठा net_device *indev;
	स्थिर काष्ठा net_device *outdev;
	स्थिर काष्ठा net_device *hw_outdev;
	काष्ठा id अणु
		__u16	id;
		__be16	proto;
	पूर्ण encap[NF_FLOW_TABLE_ENCAP_MAX];
	u8 num_encaps;
	u8 ingress_vlans;
	u8 h_source[ETH_ALEN];
	u8 h_dest[ETH_ALEN];
	क्रमागत flow_offload_xmit_type xmit_type;
पूर्ण;

अटल bool nft_is_valid_ether_device(स्थिर काष्ठा net_device *dev)
अणु
	अगर (!dev || (dev->flags & IFF_LOOPBACK) || dev->type != ARPHRD_ETHER ||
	    dev->addr_len != ETH_ALEN || !is_valid_ether_addr(dev->dev_addr))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम nft_dev_path_info(स्थिर काष्ठा net_device_path_stack *stack,
			      काष्ठा nft_क्रमward_info *info,
			      अचिन्हित अक्षर *ha, काष्ठा nf_flowtable *flowtable)
अणु
	स्थिर काष्ठा net_device_path *path;
	पूर्णांक i;

	स_नकल(info->h_dest, ha, ETH_ALEN);

	क्रम (i = 0; i < stack->num_paths; i++) अणु
		path = &stack->path[i];
		चयन (path->type) अणु
		हाल DEV_PATH_ETHERNET:
		हाल DEV_PATH_DSA:
		हाल DEV_PATH_VLAN:
		हाल DEV_PATH_PPPOE:
			info->indev = path->dev;
			अगर (is_zero_ether_addr(info->h_source))
				स_नकल(info->h_source, path->dev->dev_addr, ETH_ALEN);

			अगर (path->type == DEV_PATH_ETHERNET)
				अवरोध;
			अगर (path->type == DEV_PATH_DSA) अणु
				i = stack->num_paths;
				अवरोध;
			पूर्ण

			/* DEV_PATH_VLAN and DEV_PATH_PPPOE */
			अगर (info->num_encaps >= NF_FLOW_TABLE_ENCAP_MAX) अणु
				info->indev = शून्य;
				अवरोध;
			पूर्ण
			info->outdev = path->dev;
			info->encap[info->num_encaps].id = path->encap.id;
			info->encap[info->num_encaps].proto = path->encap.proto;
			info->num_encaps++;
			अगर (path->type == DEV_PATH_PPPOE)
				स_नकल(info->h_dest, path->encap.h_dest, ETH_ALEN);
			अवरोध;
		हाल DEV_PATH_BRIDGE:
			अगर (is_zero_ether_addr(info->h_source))
				स_नकल(info->h_source, path->dev->dev_addr, ETH_ALEN);

			चयन (path->bridge.vlan_mode) अणु
			हाल DEV_PATH_BR_VLAN_UNTAG_HW:
				info->ingress_vlans |= BIT(info->num_encaps - 1);
				अवरोध;
			हाल DEV_PATH_BR_VLAN_TAG:
				info->encap[info->num_encaps].id = path->bridge.vlan_id;
				info->encap[info->num_encaps].proto = path->bridge.vlan_proto;
				info->num_encaps++;
				अवरोध;
			हाल DEV_PATH_BR_VLAN_UNTAG:
				info->num_encaps--;
				अवरोध;
			हाल DEV_PATH_BR_VLAN_KEEP:
				अवरोध;
			पूर्ण
			info->xmit_type = FLOW_OFFLOAD_XMIT_सूचीECT;
			अवरोध;
		शेष:
			info->indev = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!info->outdev)
		info->outdev = info->indev;

	info->hw_outdev = info->indev;

	अगर (nf_flowtable_hw_offload(flowtable) &&
	    nft_is_valid_ether_device(info->indev))
		info->xmit_type = FLOW_OFFLOAD_XMIT_सूचीECT;
पूर्ण

अटल bool nft_flowtable_find_dev(स्थिर काष्ठा net_device *dev,
				   काष्ठा nft_flowtable *ft)
अणु
	काष्ठा nft_hook *hook;
	bool found = false;

	list_क्रम_each_entry_rcu(hook, &ft->hook_list, list) अणु
		अगर (hook->ops.dev != dev)
			जारी;

		found = true;
		अवरोध;
	पूर्ण

	वापस found;
पूर्ण

अटल व्योम nft_dev_क्रमward_path(काष्ठा nf_flow_route *route,
				 स्थिर काष्ठा nf_conn *ct,
				 क्रमागत ip_conntrack_dir dir,
				 काष्ठा nft_flowtable *ft)
अणु
	स्थिर काष्ठा dst_entry *dst = route->tuple[dir].dst;
	काष्ठा net_device_path_stack stack;
	काष्ठा nft_क्रमward_info info = अणुपूर्ण;
	अचिन्हित अक्षर ha[ETH_ALEN];
	पूर्णांक i;

	अगर (nft_dev_fill_क्रमward_path(route, dst, ct, dir, ha, &stack) >= 0)
		nft_dev_path_info(&stack, &info, ha, &ft->data);

	अगर (!info.indev || !nft_flowtable_find_dev(info.indev, ft))
		वापस;

	route->tuple[!dir].in.अगरindex = info.indev->अगरindex;
	क्रम (i = 0; i < info.num_encaps; i++) अणु
		route->tuple[!dir].in.encap[i].id = info.encap[i].id;
		route->tuple[!dir].in.encap[i].proto = info.encap[i].proto;
	पूर्ण
	route->tuple[!dir].in.num_encaps = info.num_encaps;
	route->tuple[!dir].in.ingress_vlans = info.ingress_vlans;

	अगर (info.xmit_type == FLOW_OFFLOAD_XMIT_सूचीECT) अणु
		स_नकल(route->tuple[dir].out.h_source, info.h_source, ETH_ALEN);
		स_नकल(route->tuple[dir].out.h_dest, info.h_dest, ETH_ALEN);
		route->tuple[dir].out.अगरindex = info.outdev->अगरindex;
		route->tuple[dir].out.hw_अगरindex = info.hw_outdev->अगरindex;
		route->tuple[dir].xmit_type = info.xmit_type;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_flow_route(स्थिर काष्ठा nft_pktinfo *pkt,
			  स्थिर काष्ठा nf_conn *ct,
			  काष्ठा nf_flow_route *route,
			  क्रमागत ip_conntrack_dir dir,
			  काष्ठा nft_flowtable *ft)
अणु
	काष्ठा dst_entry *this_dst = skb_dst(pkt->skb);
	काष्ठा dst_entry *other_dst = शून्य;
	काष्ठा flowi fl;

	स_रखो(&fl, 0, माप(fl));
	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		fl.u.ip4.daddr = ct->tuplehash[dir].tuple.src.u3.ip;
		fl.u.ip4.flowi4_oअगर = nft_in(pkt)->अगरindex;
		अवरोध;
	हाल NFPROTO_IPV6:
		fl.u.ip6.daddr = ct->tuplehash[dir].tuple.src.u3.in6;
		fl.u.ip6.flowi6_oअगर = nft_in(pkt)->अगरindex;
		अवरोध;
	पूर्ण

	nf_route(nft_net(pkt), &other_dst, &fl, false, nft_pf(pkt));
	अगर (!other_dst)
		वापस -ENOENT;

	nft_शेष_क्रमward_path(route, this_dst, dir);
	nft_शेष_क्रमward_path(route, other_dst, !dir);

	अगर (route->tuple[dir].xmit_type	== FLOW_OFFLOAD_XMIT_NEIGH &&
	    route->tuple[!dir].xmit_type == FLOW_OFFLOAD_XMIT_NEIGH) अणु
		nft_dev_क्रमward_path(route, ct, dir, ft);
		nft_dev_क्रमward_path(route, ct, !dir, ft);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool nft_flow_offload_skip(काष्ठा sk_buff *skb, पूर्णांक family)
अणु
	अगर (skb_sec_path(skb))
		वापस true;

	अगर (family == NFPROTO_IPV4) अणु
		स्थिर काष्ठा ip_options *opt;

		opt = &(IPCB(skb)->opt);

		अगर (unlikely(opt->optlen))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम nft_flow_offload_eval(स्थिर काष्ठा nft_expr *expr,
				  काष्ठा nft_regs *regs,
				  स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_flow_offload *priv = nft_expr_priv(expr);
	काष्ठा nf_flowtable *flowtable = &priv->flowtable->data;
	काष्ठा tcphdr _tcph, *tcph = शून्य;
	काष्ठा nf_flow_route route = अणुपूर्ण;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा flow_offload *flow;
	क्रमागत ip_conntrack_dir dir;
	काष्ठा nf_conn *ct;
	पूर्णांक ret;

	अगर (nft_flow_offload_skip(pkt->skb, nft_pf(pkt)))
		जाओ out;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	अगर (!ct)
		जाओ out;

	चयन (ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.protonum) अणु
	हाल IPPROTO_TCP:
		tcph = skb_header_poपूर्णांकer(pkt->skb, pkt->xt.thoff,
					  माप(_tcph), &_tcph);
		अगर (unlikely(!tcph || tcph->fin || tcph->rst))
			जाओ out;
		अवरोध;
	हाल IPPROTO_UDP:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	अगर (nf_ct_ext_exist(ct, NF_CT_EXT_HELPER) ||
	    ct->status & (IPS_SEQ_ADJUST | IPS_NAT_CLASH))
		जाओ out;

	अगर (!nf_ct_is_confirmed(ct))
		जाओ out;

	अगर (test_and_set_bit(IPS_OFFLOAD_BIT, &ct->status))
		जाओ out;

	dir = CTINFO2सूची(ctinfo);
	अगर (nft_flow_route(pkt, ct, &route, dir, priv->flowtable) < 0)
		जाओ err_flow_route;

	flow = flow_offload_alloc(ct);
	अगर (!flow)
		जाओ err_flow_alloc;

	अगर (flow_offload_route_init(flow, &route) < 0)
		जाओ err_flow_add;

	अगर (tcph) अणु
		ct->proto.tcp.seen[0].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
		ct->proto.tcp.seen[1].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
	पूर्ण

	ret = flow_offload_add(flowtable, flow);
	अगर (ret < 0)
		जाओ err_flow_add;

	dst_release(route.tuple[!dir].dst);
	वापस;

err_flow_add:
	flow_offload_मुक्त(flow);
err_flow_alloc:
	dst_release(route.tuple[!dir].dst);
err_flow_route:
	clear_bit(IPS_OFFLOAD_BIT, &ct->status);
out:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_flow_offload_validate(स्थिर काष्ठा nft_ctx *ctx,
				     स्थिर काष्ठा nft_expr *expr,
				     स्थिर काष्ठा nft_data **data)
अणु
	अचिन्हित पूर्णांक hook_mask = (1 << NF_INET_FORWARD);

	वापस nft_chain_validate_hooks(ctx->chain, hook_mask);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_flow_offload_policy[NFTA_FLOW_MAX + 1] = अणु
	[NFTA_FLOW_TABLE_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_NAME_MAXLEN - 1 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_flow_offload_init(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_expr *expr,
				 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_flow_offload *priv = nft_expr_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_flowtable *flowtable;

	अगर (!tb[NFTA_FLOW_TABLE_NAME])
		वापस -EINVAL;

	flowtable = nft_flowtable_lookup(ctx->table, tb[NFTA_FLOW_TABLE_NAME],
					 genmask);
	अगर (IS_ERR(flowtable))
		वापस PTR_ERR(flowtable);

	priv->flowtable = flowtable;
	flowtable->use++;

	वापस nf_ct_netns_get(ctx->net, ctx->family);
पूर्ण

अटल व्योम nft_flow_offload_deactivate(स्थिर काष्ठा nft_ctx *ctx,
					स्थिर काष्ठा nft_expr *expr,
					क्रमागत nft_trans_phase phase)
अणु
	काष्ठा nft_flow_offload *priv = nft_expr_priv(expr);

	nf_tables_deactivate_flowtable(ctx, priv->flowtable, phase);
पूर्ण

अटल व्योम nft_flow_offload_activate(स्थिर काष्ठा nft_ctx *ctx,
				      स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_flow_offload *priv = nft_expr_priv(expr);

	priv->flowtable->use++;
पूर्ण

अटल व्योम nft_flow_offload_destroy(स्थिर काष्ठा nft_ctx *ctx,
				     स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, ctx->family);
पूर्ण

अटल पूर्णांक nft_flow_offload_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_flow_offload *priv = nft_expr_priv(expr);

	अगर (nla_put_string(skb, NFTA_FLOW_TABLE_NAME, priv->flowtable->name))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_flow_offload_type;
अटल स्थिर काष्ठा nft_expr_ops nft_flow_offload_ops = अणु
	.type		= &nft_flow_offload_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_flow_offload)),
	.eval		= nft_flow_offload_eval,
	.init		= nft_flow_offload_init,
	.activate	= nft_flow_offload_activate,
	.deactivate	= nft_flow_offload_deactivate,
	.destroy	= nft_flow_offload_destroy,
	.validate	= nft_flow_offload_validate,
	.dump		= nft_flow_offload_dump,
पूर्ण;

अटल काष्ठा nft_expr_type nft_flow_offload_type __पढ़ो_mostly = अणु
	.name		= "flow_offload",
	.ops		= &nft_flow_offload_ops,
	.policy		= nft_flow_offload_policy,
	.maxattr	= NFTA_FLOW_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक flow_offload_netdev_event(काष्ठा notअगरier_block *this,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (event != NETDEV_DOWN)
		वापस NOTIFY_DONE;

	nf_flow_table_cleanup(dev);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block flow_offload_netdev_notअगरier = अणु
	.notअगरier_call	= flow_offload_netdev_event,
पूर्ण;

अटल पूर्णांक __init nft_flow_offload_module_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_netdevice_notअगरier(&flow_offload_netdev_notअगरier);
	अगर (err)
		जाओ err;

	err = nft_रेजिस्टर_expr(&nft_flow_offload_type);
	अगर (err < 0)
		जाओ रेजिस्टर_expr;

	वापस 0;

रेजिस्टर_expr:
	unरेजिस्टर_netdevice_notअगरier(&flow_offload_netdev_notअगरier);
err:
	वापस err;
पूर्ण

अटल व्योम __निकास nft_flow_offload_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_flow_offload_type);
	unरेजिस्टर_netdevice_notअगरier(&flow_offload_netdev_notअगरier);
पूर्ण

module_init(nft_flow_offload_module_init);
module_निकास(nft_flow_offload_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_EXPR("flow_offload");
MODULE_DESCRIPTION("nftables hardware flow offload module");
