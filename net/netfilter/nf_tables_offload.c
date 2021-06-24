<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <net/flow_offload.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>
#समावेश <net/pkt_cls.h>

अटल काष्ठा nft_flow_rule *nft_flow_rule_alloc(पूर्णांक num_actions)
अणु
	काष्ठा nft_flow_rule *flow;

	flow = kzalloc(माप(काष्ठा nft_flow_rule), GFP_KERNEL);
	अगर (!flow)
		वापस शून्य;

	flow->rule = flow_rule_alloc(num_actions);
	अगर (!flow->rule) अणु
		kमुक्त(flow);
		वापस शून्य;
	पूर्ण

	flow->rule->match.dissector	= &flow->match.dissector;
	flow->rule->match.mask		= &flow->match.mask;
	flow->rule->match.key		= &flow->match.key;

	वापस flow;
पूर्ण

व्योम nft_flow_rule_set_addr_type(काष्ठा nft_flow_rule *flow,
				 क्रमागत flow_dissector_key_id addr_type)
अणु
	काष्ठा nft_flow_match *match = &flow->match;
	काष्ठा nft_flow_key *mask = &match->mask;
	काष्ठा nft_flow_key *key = &match->key;

	अगर (match->dissector.used_keys & BIT(FLOW_DISSECTOR_KEY_CONTROL))
		वापस;

	key->control.addr_type = addr_type;
	mask->control.addr_type = 0xffff;
	match->dissector.used_keys |= BIT(FLOW_DISSECTOR_KEY_CONTROL);
	match->dissector.offset[FLOW_DISSECTOR_KEY_CONTROL] =
		दुरत्व(काष्ठा nft_flow_key, control);
पूर्ण

काष्ठा nft_offload_ethertype अणु
	__be16 value;
	__be16 mask;
पूर्ण;

अटल व्योम nft_flow_rule_transfer_vlan(काष्ठा nft_offload_ctx *ctx,
					काष्ठा nft_flow_rule *flow)
अणु
	काष्ठा nft_flow_match *match = &flow->match;
	काष्ठा nft_offload_ethertype ethertype;

	अगर (match->dissector.used_keys & BIT(FLOW_DISSECTOR_KEY_CONTROL) &&
	    match->key.basic.n_proto != htons(ETH_P_8021Q) &&
	    match->key.basic.n_proto != htons(ETH_P_8021AD))
		वापस;

	ethertype.value = match->key.basic.n_proto;
	ethertype.mask = match->mask.basic.n_proto;

	अगर (match->dissector.used_keys & BIT(FLOW_DISSECTOR_KEY_VLAN) &&
	    (match->key.vlan.vlan_tpid == htons(ETH_P_8021Q) ||
	     match->key.vlan.vlan_tpid == htons(ETH_P_8021AD))) अणु
		match->key.basic.n_proto = match->key.cvlan.vlan_tpid;
		match->mask.basic.n_proto = match->mask.cvlan.vlan_tpid;
		match->key.cvlan.vlan_tpid = match->key.vlan.vlan_tpid;
		match->mask.cvlan.vlan_tpid = match->mask.vlan.vlan_tpid;
		match->key.vlan.vlan_tpid = ethertype.value;
		match->mask.vlan.vlan_tpid = ethertype.mask;
		match->dissector.offset[FLOW_DISSECTOR_KEY_CVLAN] =
			दुरत्व(काष्ठा nft_flow_key, cvlan);
		match->dissector.used_keys |= BIT(FLOW_DISSECTOR_KEY_CVLAN);
	पूर्ण अन्यथा अणु
		match->key.basic.n_proto = match->key.vlan.vlan_tpid;
		match->mask.basic.n_proto = match->mask.vlan.vlan_tpid;
		match->key.vlan.vlan_tpid = ethertype.value;
		match->mask.vlan.vlan_tpid = ethertype.mask;
		match->dissector.offset[FLOW_DISSECTOR_KEY_VLAN] =
			दुरत्व(काष्ठा nft_flow_key, vlan);
		match->dissector.used_keys |= BIT(FLOW_DISSECTOR_KEY_VLAN);
	पूर्ण
पूर्ण

काष्ठा nft_flow_rule *nft_flow_rule_create(काष्ठा net *net,
					   स्थिर काष्ठा nft_rule *rule)
अणु
	काष्ठा nft_offload_ctx *ctx;
	काष्ठा nft_flow_rule *flow;
	पूर्णांक num_actions = 0, err;
	काष्ठा nft_expr *expr;

	expr = nft_expr_first(rule);
	जबतक (nft_expr_more(rule, expr)) अणु
		अगर (expr->ops->offload_flags & NFT_OFFLOAD_F_ACTION)
			num_actions++;

		expr = nft_expr_next(expr);
	पूर्ण

	अगर (num_actions == 0)
		वापस ERR_PTR(-EOPNOTSUPP);

	flow = nft_flow_rule_alloc(num_actions);
	अगर (!flow)
		वापस ERR_PTR(-ENOMEM);

	expr = nft_expr_first(rule);

	ctx = kzalloc(माप(काष्ठा nft_offload_ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	ctx->net = net;
	ctx->dep.type = NFT_OFFLOAD_DEP_UNSPEC;

	जबतक (nft_expr_more(rule, expr)) अणु
		अगर (!expr->ops->offload) अणु
			err = -EOPNOTSUPP;
			जाओ err_out;
		पूर्ण
		err = expr->ops->offload(ctx, flow, expr);
		अगर (err < 0)
			जाओ err_out;

		expr = nft_expr_next(expr);
	पूर्ण
	nft_flow_rule_transfer_vlan(ctx, flow);

	flow->proto = ctx->dep.l3num;
	kमुक्त(ctx);

	वापस flow;
err_out:
	kमुक्त(ctx);
	nft_flow_rule_destroy(flow);

	वापस ERR_PTR(err);
पूर्ण

व्योम nft_flow_rule_destroy(काष्ठा nft_flow_rule *flow)
अणु
	काष्ठा flow_action_entry *entry;
	पूर्णांक i;

	flow_action_क्रम_each(i, entry, &flow->rule->action) अणु
		चयन (entry->id) अणु
		हाल FLOW_ACTION_REसूचीECT:
		हाल FLOW_ACTION_MIRRED:
			dev_put(entry->dev);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(flow->rule);
	kमुक्त(flow);
पूर्ण

व्योम nft_offload_set_dependency(काष्ठा nft_offload_ctx *ctx,
				क्रमागत nft_offload_dep_type type)
अणु
	ctx->dep.type = type;
पूर्ण

व्योम nft_offload_update_dependency(काष्ठा nft_offload_ctx *ctx,
				   स्थिर व्योम *data, u32 len)
अणु
	चयन (ctx->dep.type) अणु
	हाल NFT_OFFLOAD_DEP_NETWORK:
		WARN_ON(len != माप(__u16));
		स_नकल(&ctx->dep.l3num, data, माप(__u16));
		अवरोध;
	हाल NFT_OFFLOAD_DEP_TRANSPORT:
		WARN_ON(len != माप(__u8));
		स_नकल(&ctx->dep.protonum, data, माप(__u8));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ctx->dep.type = NFT_OFFLOAD_DEP_UNSPEC;
पूर्ण

अटल व्योम nft_flow_offload_common_init(काष्ठा flow_cls_common_offload *common,
					 __be16 proto, पूर्णांक priority,
					 काष्ठा netlink_ext_ack *extack)
अणु
	common->protocol = proto;
	common->prio = priority;
	common->extack = extack;
पूर्ण

अटल पूर्णांक nft_setup_cb_call(क्रमागत tc_setup_type type, व्योम *type_data,
			     काष्ठा list_head *cb_list)
अणु
	काष्ठा flow_block_cb *block_cb;
	पूर्णांक err;

	list_क्रम_each_entry(block_cb, cb_list, list) अणु
		err = block_cb->cb(type, type_data, block_cb->cb_priv);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक nft_chain_offload_priority(काष्ठा nft_base_chain *basechain)
अणु
	अगर (basechain->ops.priority <= 0 ||
	    basechain->ops.priority > अच_लघु_उच्च)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम nft_flow_cls_offload_setup(काष्ठा flow_cls_offload *cls_flow,
				       स्थिर काष्ठा nft_base_chain *basechain,
				       स्थिर काष्ठा nft_rule *rule,
				       स्थिर काष्ठा nft_flow_rule *flow,
				       काष्ठा netlink_ext_ack *extack,
				       क्रमागत flow_cls_command command)
अणु
	__be16 proto = ETH_P_ALL;

	स_रखो(cls_flow, 0, माप(*cls_flow));

	अगर (flow)
		proto = flow->proto;

	nft_flow_offload_common_init(&cls_flow->common, proto,
				     basechain->ops.priority, extack);
	cls_flow->command = command;
	cls_flow->cookie = (अचिन्हित दीर्घ) rule;
	अगर (flow)
		cls_flow->rule = flow->rule;
पूर्ण

अटल पूर्णांक nft_flow_offload_cmd(स्थिर काष्ठा nft_chain *chain,
				स्थिर काष्ठा nft_rule *rule,
				काष्ठा nft_flow_rule *flow,
				क्रमागत flow_cls_command command,
				काष्ठा flow_cls_offload *cls_flow)
अणु
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा nft_base_chain *basechain;

	अगर (!nft_is_base_chain(chain))
		वापस -EOPNOTSUPP;

	basechain = nft_base_chain(chain);
	nft_flow_cls_offload_setup(cls_flow, basechain, rule, flow, &extack,
				   command);

	वापस nft_setup_cb_call(TC_SETUP_CLSFLOWER, cls_flow,
				 &basechain->flow_block.cb_list);
पूर्ण

अटल पूर्णांक nft_flow_offload_rule(स्थिर काष्ठा nft_chain *chain,
				 काष्ठा nft_rule *rule,
				 काष्ठा nft_flow_rule *flow,
				 क्रमागत flow_cls_command command)
अणु
	काष्ठा flow_cls_offload cls_flow;

	वापस nft_flow_offload_cmd(chain, rule, flow, command, &cls_flow);
पूर्ण

पूर्णांक nft_flow_rule_stats(स्थिर काष्ठा nft_chain *chain,
			स्थिर काष्ठा nft_rule *rule)
अणु
	काष्ठा flow_cls_offload cls_flow = अणुपूर्ण;
	काष्ठा nft_expr *expr, *next;
	पूर्णांक err;

	err = nft_flow_offload_cmd(chain, rule, शून्य, FLOW_CLS_STATS,
				   &cls_flow);
	अगर (err < 0)
		वापस err;

	nft_rule_क्रम_each_expr(expr, next, rule) अणु
		अगर (expr->ops->offload_stats)
			expr->ops->offload_stats(expr, &cls_flow.stats);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_flow_offload_bind(काष्ठा flow_block_offload *bo,
				 काष्ठा nft_base_chain *basechain)
अणु
	list_splice(&bo->cb_list, &basechain->flow_block.cb_list);
	वापस 0;
पूर्ण

अटल पूर्णांक nft_flow_offload_unbind(काष्ठा flow_block_offload *bo,
				   काष्ठा nft_base_chain *basechain)
अणु
	काष्ठा flow_block_cb *block_cb, *next;
	काष्ठा flow_cls_offload cls_flow;
	काष्ठा netlink_ext_ack extack;
	काष्ठा nft_chain *chain;
	काष्ठा nft_rule *rule;

	chain = &basechain->chain;
	list_क्रम_each_entry(rule, &chain->rules, list) अणु
		स_रखो(&extack, 0, माप(extack));
		nft_flow_cls_offload_setup(&cls_flow, basechain, rule, शून्य,
					   &extack, FLOW_CLS_DESTROY);
		nft_setup_cb_call(TC_SETUP_CLSFLOWER, &cls_flow, &bo->cb_list);
	पूर्ण

	list_क्रम_each_entry_safe(block_cb, next, &bo->cb_list, list) अणु
		list_del(&block_cb->list);
		flow_block_cb_मुक्त(block_cb);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_block_setup(काष्ठा nft_base_chain *basechain,
			   काष्ठा flow_block_offload *bo,
			   क्रमागत flow_block_command cmd)
अणु
	पूर्णांक err;

	चयन (cmd) अणु
	हाल FLOW_BLOCK_BIND:
		err = nft_flow_offload_bind(bo, basechain);
		अवरोध;
	हाल FLOW_BLOCK_UNBIND:
		err = nft_flow_offload_unbind(bo, basechain);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम nft_flow_block_offload_init(काष्ठा flow_block_offload *bo,
					काष्ठा net *net,
					क्रमागत flow_block_command cmd,
					काष्ठा nft_base_chain *basechain,
					काष्ठा netlink_ext_ack *extack)
अणु
	स_रखो(bo, 0, माप(*bo));
	bo->net		= net;
	bo->block	= &basechain->flow_block;
	bo->command	= cmd;
	bo->binder_type	= FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS;
	bo->extack	= extack;
	INIT_LIST_HEAD(&bo->cb_list);
पूर्ण

अटल पूर्णांक nft_block_offload_cmd(काष्ठा nft_base_chain *chain,
				 काष्ठा net_device *dev,
				 क्रमागत flow_block_command cmd)
अणु
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा flow_block_offload bo;
	पूर्णांक err;

	nft_flow_block_offload_init(&bo, dev_net(dev), cmd, chain, &extack);

	err = dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_BLOCK, &bo);
	अगर (err < 0)
		वापस err;

	वापस nft_block_setup(chain, &bo, cmd);
पूर्ण

अटल व्योम nft_indr_block_cleanup(काष्ठा flow_block_cb *block_cb)
अणु
	काष्ठा nft_base_chain *basechain = block_cb->indr.data;
	काष्ठा net_device *dev = block_cb->indr.dev;
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा nftables_pernet *nft_net;
	काष्ठा net *net = dev_net(dev);
	काष्ठा flow_block_offload bo;

	nft_flow_block_offload_init(&bo, dev_net(dev), FLOW_BLOCK_UNBIND,
				    basechain, &extack);
	nft_net = nft_pernet(net);
	mutex_lock(&nft_net->commit_mutex);
	list_del(&block_cb->driver_list);
	list_move(&block_cb->list, &bo.cb_list);
	nft_flow_offload_unbind(&bo, basechain);
	mutex_unlock(&nft_net->commit_mutex);
पूर्ण

अटल पूर्णांक nft_indr_block_offload_cmd(काष्ठा nft_base_chain *basechain,
				      काष्ठा net_device *dev,
				      क्रमागत flow_block_command cmd)
अणु
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा flow_block_offload bo;
	पूर्णांक err;

	nft_flow_block_offload_init(&bo, dev_net(dev), cmd, basechain, &extack);

	err = flow_indr_dev_setup_offload(dev, शून्य, TC_SETUP_BLOCK, basechain, &bo,
					  nft_indr_block_cleanup);
	अगर (err < 0)
		वापस err;

	अगर (list_empty(&bo.cb_list))
		वापस -EOPNOTSUPP;

	वापस nft_block_setup(basechain, &bo, cmd);
पूर्ण

अटल पूर्णांक nft_chain_offload_cmd(काष्ठा nft_base_chain *basechain,
				 काष्ठा net_device *dev,
				 क्रमागत flow_block_command cmd)
अणु
	पूर्णांक err;

	अगर (dev->netdev_ops->nकरो_setup_tc)
		err = nft_block_offload_cmd(basechain, dev, cmd);
	अन्यथा
		err = nft_indr_block_offload_cmd(basechain, dev, cmd);

	वापस err;
पूर्ण

अटल पूर्णांक nft_flow_block_chain(काष्ठा nft_base_chain *basechain,
				स्थिर काष्ठा net_device *this_dev,
				क्रमागत flow_block_command cmd)
अणु
	काष्ठा net_device *dev;
	काष्ठा nft_hook *hook;
	पूर्णांक err, i = 0;

	list_क्रम_each_entry(hook, &basechain->hook_list, list) अणु
		dev = hook->ops.dev;
		अगर (this_dev && this_dev != dev)
			जारी;

		err = nft_chain_offload_cmd(basechain, dev, cmd);
		अगर (err < 0 && cmd == FLOW_BLOCK_BIND) अणु
			अगर (!this_dev)
				जाओ err_flow_block;

			वापस err;
		पूर्ण
		i++;
	पूर्ण

	वापस 0;

err_flow_block:
	list_क्रम_each_entry(hook, &basechain->hook_list, list) अणु
		अगर (i-- <= 0)
			अवरोध;

		dev = hook->ops.dev;
		nft_chain_offload_cmd(basechain, dev, FLOW_BLOCK_UNBIND);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक nft_flow_offload_chain(काष्ठा nft_chain *chain, u8 *ppolicy,
				  क्रमागत flow_block_command cmd)
अणु
	काष्ठा nft_base_chain *basechain;
	u8 policy;

	अगर (!nft_is_base_chain(chain))
		वापस -EOPNOTSUPP;

	basechain = nft_base_chain(chain);
	policy = ppolicy ? *ppolicy : basechain->policy;

	/* Only शेष policy to accept is supported क्रम now. */
	अगर (cmd == FLOW_BLOCK_BIND && policy == NF_DROP)
		वापस -EOPNOTSUPP;

	वापस nft_flow_block_chain(basechain, शून्य, cmd);
पूर्ण

अटल व्योम nft_flow_rule_offload_पात(काष्ठा net *net,
					काष्ठा nft_trans *trans)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	पूर्णांक err = 0;

	list_क्रम_each_entry_जारी_reverse(trans, &nft_net->commit_list, list) अणु
		अगर (trans->ctx.family != NFPROTO_NETDEV)
			जारी;

		चयन (trans->msg_type) अणु
		हाल NFT_MSG_NEWCHAIN:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD) ||
			    nft_trans_chain_update(trans))
				जारी;

			err = nft_flow_offload_chain(trans->ctx.chain, शून्य,
						     FLOW_BLOCK_UNBIND);
			अवरोध;
		हाल NFT_MSG_DELCHAIN:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			err = nft_flow_offload_chain(trans->ctx.chain, शून्य,
						     FLOW_BLOCK_BIND);
			अवरोध;
		हाल NFT_MSG_NEWRULE:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			err = nft_flow_offload_rule(trans->ctx.chain,
						    nft_trans_rule(trans),
						    शून्य, FLOW_CLS_DESTROY);
			अवरोध;
		हाल NFT_MSG_DELRULE:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			err = nft_flow_offload_rule(trans->ctx.chain,
						    nft_trans_rule(trans),
						    nft_trans_flow_rule(trans),
						    FLOW_CLS_REPLACE);
			अवरोध;
		पूर्ण

		अगर (WARN_ON_ONCE(err))
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक nft_flow_rule_offload_commit(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_trans *trans;
	पूर्णांक err = 0;
	u8 policy;

	list_क्रम_each_entry(trans, &nft_net->commit_list, list) अणु
		अगर (trans->ctx.family != NFPROTO_NETDEV)
			जारी;

		चयन (trans->msg_type) अणु
		हाल NFT_MSG_NEWCHAIN:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD) ||
			    nft_trans_chain_update(trans))
				जारी;

			policy = nft_trans_chain_policy(trans);
			err = nft_flow_offload_chain(trans->ctx.chain, &policy,
						     FLOW_BLOCK_BIND);
			अवरोध;
		हाल NFT_MSG_DELCHAIN:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			policy = nft_trans_chain_policy(trans);
			err = nft_flow_offload_chain(trans->ctx.chain, &policy,
						     FLOW_BLOCK_UNBIND);
			अवरोध;
		हाल NFT_MSG_NEWRULE:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			अगर (trans->ctx.flags & NLM_F_REPLACE ||
			    !(trans->ctx.flags & NLM_F_APPEND)) अणु
				err = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			err = nft_flow_offload_rule(trans->ctx.chain,
						    nft_trans_rule(trans),
						    nft_trans_flow_rule(trans),
						    FLOW_CLS_REPLACE);
			अवरोध;
		हाल NFT_MSG_DELRULE:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			err = nft_flow_offload_rule(trans->ctx.chain,
						    nft_trans_rule(trans),
						    शून्य, FLOW_CLS_DESTROY);
			अवरोध;
		पूर्ण

		अगर (err) अणु
			nft_flow_rule_offload_पात(net, trans);
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(trans, &nft_net->commit_list, list) अणु
		अगर (trans->ctx.family != NFPROTO_NETDEV)
			जारी;

		चयन (trans->msg_type) अणु
		हाल NFT_MSG_NEWRULE:
		हाल NFT_MSG_DELRULE:
			अगर (!(trans->ctx.chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			nft_flow_rule_destroy(nft_trans_flow_rule(trans));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा nft_chain *__nft_offload_get_chain(स्थिर काष्ठा nftables_pernet *nft_net,
						 काष्ठा net_device *dev)
अणु
	काष्ठा nft_base_chain *basechain;
	काष्ठा nft_hook *hook, *found;
	स्थिर काष्ठा nft_table *table;
	काष्ठा nft_chain *chain;

	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		अगर (table->family != NFPROTO_NETDEV)
			जारी;

		list_क्रम_each_entry(chain, &table->chains, list) अणु
			अगर (!nft_is_base_chain(chain) ||
			    !(chain->flags & NFT_CHAIN_HW_OFFLOAD))
				जारी;

			found = शून्य;
			basechain = nft_base_chain(chain);
			list_क्रम_each_entry(hook, &basechain->hook_list, list) अणु
				अगर (hook->ops.dev != dev)
					जारी;

				found = hook;
				अवरोध;
			पूर्ण
			अगर (!found)
				जारी;

			वापस chain;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक nft_offload_netdev_event(काष्ठा notअगरier_block *this,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा nftables_pernet *nft_net;
	काष्ठा net *net = dev_net(dev);
	काष्ठा nft_chain *chain;

	अगर (event != NETDEV_UNREGISTER)
		वापस NOTIFY_DONE;

	nft_net = nft_pernet(net);
	mutex_lock(&nft_net->commit_mutex);
	chain = __nft_offload_get_chain(nft_net, dev);
	अगर (chain)
		nft_flow_block_chain(nft_base_chain(chain), dev,
				     FLOW_BLOCK_UNBIND);

	mutex_unlock(&nft_net->commit_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nft_offload_netdev_notअगरier = अणु
	.notअगरier_call	= nft_offload_netdev_event,
पूर्ण;

पूर्णांक nft_offload_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&nft_offload_netdev_notअगरier);
पूर्ण

व्योम nft_offload_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&nft_offload_netdev_notअगरier);
पूर्ण
