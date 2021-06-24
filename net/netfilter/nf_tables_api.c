<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2009 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/audit.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_offload.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>

#घोषणा NFT_MODULE_AUTOLOAD_LIMIT (MODULE_NAME_LEN - माप("nft-expr-255-"))

अचिन्हित पूर्णांक nf_tables_net_id __पढ़ो_mostly;

अटल LIST_HEAD(nf_tables_expressions);
अटल LIST_HEAD(nf_tables_objects);
अटल LIST_HEAD(nf_tables_flowtables);
अटल LIST_HEAD(nf_tables_destroy_list);
अटल DEFINE_SPINLOCK(nf_tables_destroy_list_lock);
अटल u64 table_handle;

क्रमागत अणु
	NFT_VALIDATE_SKIP	= 0,
	NFT_VALIDATE_NEED,
	NFT_VALIDATE_DO,
पूर्ण;

अटल काष्ठा rhltable nft_objname_ht;

अटल u32 nft_chain_hash(स्थिर व्योम *data, u32 len, u32 seed);
अटल u32 nft_chain_hash_obj(स्थिर व्योम *data, u32 len, u32 seed);
अटल पूर्णांक nft_chain_hash_cmp(काष्ठा rhashtable_compare_arg *, स्थिर व्योम *);

अटल u32 nft_objname_hash(स्थिर व्योम *data, u32 len, u32 seed);
अटल u32 nft_objname_hash_obj(स्थिर व्योम *data, u32 len, u32 seed);
अटल पूर्णांक nft_objname_hash_cmp(काष्ठा rhashtable_compare_arg *, स्थिर व्योम *);

अटल स्थिर काष्ठा rhashtable_params nft_chain_ht_params = अणु
	.head_offset		= दुरत्व(काष्ठा nft_chain, rhlhead),
	.key_offset		= दुरत्व(काष्ठा nft_chain, name),
	.hashfn			= nft_chain_hash,
	.obj_hashfn		= nft_chain_hash_obj,
	.obj_cmpfn		= nft_chain_hash_cmp,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params nft_objname_ht_params = अणु
	.head_offset		= दुरत्व(काष्ठा nft_object, rhlhead),
	.key_offset		= दुरत्व(काष्ठा nft_object, key),
	.hashfn			= nft_objname_hash,
	.obj_hashfn		= nft_objname_hash_obj,
	.obj_cmpfn		= nft_objname_hash_cmp,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

काष्ठा nft_audit_data अणु
	काष्ठा nft_table *table;
	पूर्णांक entries;
	पूर्णांक op;
	काष्ठा list_head list;
पूर्ण;

अटल स्थिर u8 nft2audit_op[NFT_MSG_MAX] = अणु // क्रमागत nf_tables_msg_types
	[NFT_MSG_NEWTABLE]	= AUDIT_NFT_OP_TABLE_REGISTER,
	[NFT_MSG_GETTABLE]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELTABLE]	= AUDIT_NFT_OP_TABLE_UNREGISTER,
	[NFT_MSG_NEWCHAIN]	= AUDIT_NFT_OP_CHAIN_REGISTER,
	[NFT_MSG_GETCHAIN]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELCHAIN]	= AUDIT_NFT_OP_CHAIN_UNREGISTER,
	[NFT_MSG_NEWRULE]	= AUDIT_NFT_OP_RULE_REGISTER,
	[NFT_MSG_GETRULE]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELRULE]	= AUDIT_NFT_OP_RULE_UNREGISTER,
	[NFT_MSG_NEWSET]	= AUDIT_NFT_OP_SET_REGISTER,
	[NFT_MSG_GETSET]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELSET]	= AUDIT_NFT_OP_SET_UNREGISTER,
	[NFT_MSG_NEWSETELEM]	= AUDIT_NFT_OP_SETELEM_REGISTER,
	[NFT_MSG_GETSETELEM]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELSETELEM]	= AUDIT_NFT_OP_SETELEM_UNREGISTER,
	[NFT_MSG_NEWGEN]	= AUDIT_NFT_OP_GEN_REGISTER,
	[NFT_MSG_GETGEN]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_TRACE]		= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_NEWOBJ]	= AUDIT_NFT_OP_OBJ_REGISTER,
	[NFT_MSG_GETOBJ]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELOBJ]	= AUDIT_NFT_OP_OBJ_UNREGISTER,
	[NFT_MSG_GETOBJ_RESET]	= AUDIT_NFT_OP_OBJ_RESET,
	[NFT_MSG_NEWFLOWTABLE]	= AUDIT_NFT_OP_FLOWTABLE_REGISTER,
	[NFT_MSG_GETFLOWTABLE]	= AUDIT_NFT_OP_INVALID,
	[NFT_MSG_DELFLOWTABLE]	= AUDIT_NFT_OP_FLOWTABLE_UNREGISTER,
पूर्ण;

अटल व्योम nft_validate_state_update(काष्ठा net *net, u8 new_validate_state)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);

	चयन (nft_net->validate_state) अणु
	हाल NFT_VALIDATE_SKIP:
		WARN_ON_ONCE(new_validate_state == NFT_VALIDATE_DO);
		अवरोध;
	हाल NFT_VALIDATE_NEED:
		अवरोध;
	हाल NFT_VALIDATE_DO:
		अगर (new_validate_state == NFT_VALIDATE_NEED)
			वापस;
	पूर्ण

	nft_net->validate_state = new_validate_state;
पूर्ण
अटल व्योम nf_tables_trans_destroy_work(काष्ठा work_काष्ठा *w);
अटल DECLARE_WORK(trans_destroy_work, nf_tables_trans_destroy_work);

अटल व्योम nft_ctx_init(काष्ठा nft_ctx *ctx,
			 काष्ठा net *net,
			 स्थिर काष्ठा sk_buff *skb,
			 स्थिर काष्ठा nlmsghdr *nlh,
			 u8 family,
			 काष्ठा nft_table *table,
			 काष्ठा nft_chain *chain,
			 स्थिर काष्ठा nlattr * स्थिर *nla)
अणु
	ctx->net	= net;
	ctx->family	= family;
	ctx->level	= 0;
	ctx->table	= table;
	ctx->chain	= chain;
	ctx->nla   	= nla;
	ctx->portid	= NETLINK_CB(skb).portid;
	ctx->report	= nlmsg_report(nlh);
	ctx->flags	= nlh->nlmsg_flags;
	ctx->seq	= nlh->nlmsg_seq;
पूर्ण

अटल काष्ठा nft_trans *nft_trans_alloc_gfp(स्थिर काष्ठा nft_ctx *ctx,
					     पूर्णांक msg_type, u32 size, gfp_t gfp)
अणु
	काष्ठा nft_trans *trans;

	trans = kzalloc(माप(काष्ठा nft_trans) + size, gfp);
	अगर (trans == शून्य)
		वापस शून्य;

	trans->msg_type = msg_type;
	trans->ctx	= *ctx;

	वापस trans;
पूर्ण

अटल काष्ठा nft_trans *nft_trans_alloc(स्थिर काष्ठा nft_ctx *ctx,
					 पूर्णांक msg_type, u32 size)
अणु
	वापस nft_trans_alloc_gfp(ctx, msg_type, size, GFP_KERNEL);
पूर्ण

अटल व्योम nft_trans_destroy(काष्ठा nft_trans *trans)
अणु
	list_del(&trans->list);
	kमुक्त(trans);
पूर्ण

अटल व्योम nft_set_trans_bind(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा net *net = ctx->net;
	काष्ठा nft_trans *trans;

	अगर (!nft_set_is_anonymous(set))
		वापस;

	nft_net = nft_pernet(net);
	list_क्रम_each_entry_reverse(trans, &nft_net->commit_list, list) अणु
		चयन (trans->msg_type) अणु
		हाल NFT_MSG_NEWSET:
			अगर (nft_trans_set(trans) == set)
				nft_trans_set_bound(trans) = true;
			अवरोध;
		हाल NFT_MSG_NEWSETELEM:
			अगर (nft_trans_elem_set(trans) == set)
				nft_trans_elem_set_bound(trans) = true;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक nft_netdev_रेजिस्टर_hooks(काष्ठा net *net,
				     काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook;
	पूर्णांक err, j;

	j = 0;
	list_क्रम_each_entry(hook, hook_list, list) अणु
		err = nf_रेजिस्टर_net_hook(net, &hook->ops);
		अगर (err < 0)
			जाओ err_रेजिस्टर;

		j++;
	पूर्ण
	वापस 0;

err_रेजिस्टर:
	list_क्रम_each_entry(hook, hook_list, list) अणु
		अगर (j-- <= 0)
			अवरोध;

		nf_unरेजिस्टर_net_hook(net, &hook->ops);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम nft_netdev_unरेजिस्टर_hooks(काष्ठा net *net,
					काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook;

	list_क्रम_each_entry(hook, hook_list, list)
		nf_unरेजिस्टर_net_hook(net, &hook->ops);
पूर्ण

अटल पूर्णांक nf_tables_रेजिस्टर_hook(काष्ठा net *net,
				   स्थिर काष्ठा nft_table *table,
				   काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_base_chain *basechain;
	स्थिर काष्ठा nf_hook_ops *ops;

	अगर (table->flags & NFT_TABLE_F_DORMANT ||
	    !nft_is_base_chain(chain))
		वापस 0;

	basechain = nft_base_chain(chain);
	ops = &basechain->ops;

	अगर (basechain->type->ops_रेजिस्टर)
		वापस basechain->type->ops_रेजिस्टर(net, ops);

	अगर (nft_base_chain_netdev(table->family, basechain->ops.hooknum))
		वापस nft_netdev_रेजिस्टर_hooks(net, &basechain->hook_list);

	वापस nf_रेजिस्टर_net_hook(net, &basechain->ops);
पूर्ण

अटल व्योम nf_tables_unरेजिस्टर_hook(काष्ठा net *net,
				      स्थिर काष्ठा nft_table *table,
				      काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_base_chain *basechain;
	स्थिर काष्ठा nf_hook_ops *ops;

	अगर (table->flags & NFT_TABLE_F_DORMANT ||
	    !nft_is_base_chain(chain))
		वापस;
	basechain = nft_base_chain(chain);
	ops = &basechain->ops;

	अगर (basechain->type->ops_unरेजिस्टर)
		वापस basechain->type->ops_unरेजिस्टर(net, ops);

	अगर (nft_base_chain_netdev(table->family, basechain->ops.hooknum))
		nft_netdev_unरेजिस्टर_hooks(net, &basechain->hook_list);
	अन्यथा
		nf_unरेजिस्टर_net_hook(net, &basechain->ops);
पूर्ण

अटल व्योम nft_trans_commit_list_add_tail(काष्ठा net *net, काष्ठा nft_trans *trans)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);

	list_add_tail(&trans->list, &nft_net->commit_list);
पूर्ण

अटल पूर्णांक nft_trans_table_add(काष्ठा nft_ctx *ctx, पूर्णांक msg_type)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type, माप(काष्ठा nft_trans_table));
	अगर (trans == शून्य)
		वापस -ENOMEM;

	अगर (msg_type == NFT_MSG_NEWTABLE)
		nft_activate_next(ctx->net, ctx->table);

	nft_trans_commit_list_add_tail(ctx->net, trans);
	वापस 0;
पूर्ण

अटल पूर्णांक nft_deltable(काष्ठा nft_ctx *ctx)
अणु
	पूर्णांक err;

	err = nft_trans_table_add(ctx, NFT_MSG_DELTABLE);
	अगर (err < 0)
		वापस err;

	nft_deactivate_next(ctx->net, ctx->table);
	वापस err;
पूर्ण

अटल काष्ठा nft_trans *nft_trans_chain_add(काष्ठा nft_ctx *ctx, पूर्णांक msg_type)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type, माप(काष्ठा nft_trans_chain));
	अगर (trans == शून्य)
		वापस ERR_PTR(-ENOMEM);

	अगर (msg_type == NFT_MSG_NEWCHAIN) अणु
		nft_activate_next(ctx->net, ctx->chain);

		अगर (ctx->nla[NFTA_CHAIN_ID]) अणु
			nft_trans_chain_id(trans) =
				ntohl(nla_get_be32(ctx->nla[NFTA_CHAIN_ID]));
		पूर्ण
	पूर्ण

	nft_trans_commit_list_add_tail(ctx->net, trans);
	वापस trans;
पूर्ण

अटल पूर्णांक nft_delchain(काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_chain_add(ctx, NFT_MSG_DELCHAIN);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	ctx->table->use--;
	nft_deactivate_next(ctx->net, ctx->chain);

	वापस 0;
पूर्ण

अटल व्योम nft_rule_expr_activate(स्थिर काष्ठा nft_ctx *ctx,
				   काष्ठा nft_rule *rule)
अणु
	काष्ठा nft_expr *expr;

	expr = nft_expr_first(rule);
	जबतक (nft_expr_more(rule, expr)) अणु
		अगर (expr->ops->activate)
			expr->ops->activate(ctx, expr);

		expr = nft_expr_next(expr);
	पूर्ण
पूर्ण

अटल व्योम nft_rule_expr_deactivate(स्थिर काष्ठा nft_ctx *ctx,
				     काष्ठा nft_rule *rule,
				     क्रमागत nft_trans_phase phase)
अणु
	काष्ठा nft_expr *expr;

	expr = nft_expr_first(rule);
	जबतक (nft_expr_more(rule, expr)) अणु
		अगर (expr->ops->deactivate)
			expr->ops->deactivate(ctx, expr, phase);

		expr = nft_expr_next(expr);
	पूर्ण
पूर्ण

अटल पूर्णांक
nf_tables_delrule_deactivate(काष्ठा nft_ctx *ctx, काष्ठा nft_rule *rule)
अणु
	/* You cannot delete the same rule twice */
	अगर (nft_is_active_next(ctx->net, rule)) अणु
		nft_deactivate_next(ctx->net, rule);
		ctx->chain->use--;
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल काष्ठा nft_trans *nft_trans_rule_add(काष्ठा nft_ctx *ctx, पूर्णांक msg_type,
					    काष्ठा nft_rule *rule)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type, माप(काष्ठा nft_trans_rule));
	अगर (trans == शून्य)
		वापस शून्य;

	अगर (msg_type == NFT_MSG_NEWRULE && ctx->nla[NFTA_RULE_ID] != शून्य) अणु
		nft_trans_rule_id(trans) =
			ntohl(nla_get_be32(ctx->nla[NFTA_RULE_ID]));
	पूर्ण
	nft_trans_rule(trans) = rule;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस trans;
पूर्ण

अटल पूर्णांक nft_delrule(काष्ठा nft_ctx *ctx, काष्ठा nft_rule *rule)
अणु
	काष्ठा nft_flow_rule *flow;
	काष्ठा nft_trans *trans;
	पूर्णांक err;

	trans = nft_trans_rule_add(ctx, NFT_MSG_DELRULE, rule);
	अगर (trans == शून्य)
		वापस -ENOMEM;

	अगर (ctx->chain->flags & NFT_CHAIN_HW_OFFLOAD) अणु
		flow = nft_flow_rule_create(ctx->net, rule);
		अगर (IS_ERR(flow)) अणु
			nft_trans_destroy(trans);
			वापस PTR_ERR(flow);
		पूर्ण

		nft_trans_flow_rule(trans) = flow;
	पूर्ण

	err = nf_tables_delrule_deactivate(ctx, rule);
	अगर (err < 0) अणु
		nft_trans_destroy(trans);
		वापस err;
	पूर्ण
	nft_rule_expr_deactivate(ctx, rule, NFT_TRANS_PREPARE);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_delrule_by_chain(काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_rule *rule;
	पूर्णांक err;

	list_क्रम_each_entry(rule, &ctx->chain->rules, list) अणु
		अगर (!nft_is_active_next(ctx->net, rule))
			जारी;

		err = nft_delrule(ctx, rule);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nft_trans_set_add(स्थिर काष्ठा nft_ctx *ctx, पूर्णांक msg_type,
			     काष्ठा nft_set *set)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type, माप(काष्ठा nft_trans_set));
	अगर (trans == शून्य)
		वापस -ENOMEM;

	अगर (msg_type == NFT_MSG_NEWSET && ctx->nla[NFTA_SET_ID] != शून्य) अणु
		nft_trans_set_id(trans) =
			ntohl(nla_get_be32(ctx->nla[NFTA_SET_ID]));
		nft_activate_next(ctx->net, set);
	पूर्ण
	nft_trans_set(trans) = set;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_dअन्यथाt(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set)
अणु
	पूर्णांक err;

	err = nft_trans_set_add(ctx, NFT_MSG_DELSET, set);
	अगर (err < 0)
		वापस err;

	nft_deactivate_next(ctx->net, set);
	ctx->table->use--;

	वापस err;
पूर्ण

अटल पूर्णांक nft_trans_obj_add(काष्ठा nft_ctx *ctx, पूर्णांक msg_type,
			     काष्ठा nft_object *obj)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type, माप(काष्ठा nft_trans_obj));
	अगर (trans == शून्य)
		वापस -ENOMEM;

	अगर (msg_type == NFT_MSG_NEWOBJ)
		nft_activate_next(ctx->net, obj);

	nft_trans_obj(trans) = obj;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_delobj(काष्ठा nft_ctx *ctx, काष्ठा nft_object *obj)
अणु
	पूर्णांक err;

	err = nft_trans_obj_add(ctx, NFT_MSG_DELOBJ, obj);
	अगर (err < 0)
		वापस err;

	nft_deactivate_next(ctx->net, obj);
	ctx->table->use--;

	वापस err;
पूर्ण

अटल पूर्णांक nft_trans_flowtable_add(काष्ठा nft_ctx *ctx, पूर्णांक msg_type,
				   काष्ठा nft_flowtable *flowtable)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type,
				माप(काष्ठा nft_trans_flowtable));
	अगर (trans == शून्य)
		वापस -ENOMEM;

	अगर (msg_type == NFT_MSG_NEWFLOWTABLE)
		nft_activate_next(ctx->net, flowtable);

	nft_trans_flowtable(trans) = flowtable;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_delflowtable(काष्ठा nft_ctx *ctx,
			    काष्ठा nft_flowtable *flowtable)
अणु
	पूर्णांक err;

	err = nft_trans_flowtable_add(ctx, NFT_MSG_DELFLOWTABLE, flowtable);
	अगर (err < 0)
		वापस err;

	nft_deactivate_next(ctx->net, flowtable);
	ctx->table->use--;

	वापस err;
पूर्ण

/*
 * Tables
 */

अटल काष्ठा nft_table *nft_table_lookup(स्थिर काष्ठा net *net,
					  स्थिर काष्ठा nlattr *nla,
					  u8 family, u8 genmask, u32 nlpid)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_table *table;

	अगर (nla == शून्य)
		वापस ERR_PTR(-EINVAL);

	nft_net = nft_pernet(net);
	list_क्रम_each_entry_rcu(table, &nft_net->tables, list,
				lockdep_is_held(&nft_net->commit_mutex)) अणु
		अगर (!nla_म_भेद(nla, table->name) &&
		    table->family == family &&
		    nft_active_genmask(table, genmask)) अणु
			अगर (nft_table_has_owner(table) &&
			    table->nlpid != nlpid)
				वापस ERR_PTR(-EPERM);

			वापस table;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा nft_table *nft_table_lookup_byhandle(स्थिर काष्ठा net *net,
						   स्थिर काष्ठा nlattr *nla,
						   u8 genmask)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_table *table;

	nft_net = nft_pernet(net);
	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		अगर (be64_to_cpu(nla_get_be64(nla)) == table->handle &&
		    nft_active_genmask(table, genmask))
			वापस table;
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल अंतरभूत u64 nf_tables_alloc_handle(काष्ठा nft_table *table)
अणु
	वापस ++table->hgenerator;
पूर्ण

अटल स्थिर काष्ठा nft_chain_type *chain_type[NFPROTO_NUMPROTO][NFT_CHAIN_T_MAX];

अटल स्थिर काष्ठा nft_chain_type *
__nft_chain_type_get(u8 family, क्रमागत nft_chain_types type)
अणु
	अगर (family >= NFPROTO_NUMPROTO ||
	    type >= NFT_CHAIN_T_MAX)
		वापस शून्य;

	वापस chain_type[family][type];
पूर्ण

अटल स्थिर काष्ठा nft_chain_type *
__nf_tables_chain_type_lookup(स्थिर काष्ठा nlattr *nla, u8 family)
अणु
	स्थिर काष्ठा nft_chain_type *type;
	पूर्णांक i;

	क्रम (i = 0; i < NFT_CHAIN_T_MAX; i++) अणु
		type = __nft_chain_type_get(family, i);
		अगर (!type)
			जारी;
		अगर (!nla_म_भेद(nla, type->name))
			वापस type;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा nft_module_request अणु
	काष्ठा list_head	list;
	अक्षर			module[MODULE_NAME_LEN];
	bool			करोne;
पूर्ण;

#अगर_घोषित CONFIG_MODULES
__म_लिखो(2, 3) पूर्णांक nft_request_module(काष्ठा net *net, स्थिर अक्षर *fmt,
				      ...)
अणु
	अक्षर module_name[MODULE_NAME_LEN];
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_module_request *req;
	बहु_सूची args;
	पूर्णांक ret;

	बहु_शुरू(args, fmt);
	ret = vsnम_लिखो(module_name, MODULE_NAME_LEN, fmt, args);
	बहु_पूर्ण(args);
	अगर (ret >= MODULE_NAME_LEN)
		वापस 0;

	nft_net = nft_pernet(net);
	list_क्रम_each_entry(req, &nft_net->module_list, list) अणु
		अगर (!म_भेद(req->module, module_name)) अणु
			अगर (req->करोne)
				वापस 0;

			/* A request to load this module alपढ़ोy exists. */
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	req = kदो_स्मृति(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->करोne = false;
	strlcpy(req->module, module_name, MODULE_NAME_LEN);
	list_add_tail(&req->list, &nft_net->module_list);

	वापस -EAGAIN;
पूर्ण
EXPORT_SYMBOL_GPL(nft_request_module);
#पूर्ण_अगर

अटल व्योम lockdep_nfnl_nft_mutex_not_held(व्योम)
अणु
#अगर_घोषित CONFIG_PROVE_LOCKING
	अगर (debug_locks)
		WARN_ON_ONCE(lockdep_nfnl_is_held(NFNL_SUBSYS_NFTABLES));
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा nft_chain_type *
nf_tables_chain_type_lookup(काष्ठा net *net, स्थिर काष्ठा nlattr *nla,
			    u8 family, bool स्वतःload)
अणु
	स्थिर काष्ठा nft_chain_type *type;

	type = __nf_tables_chain_type_lookup(nla, family);
	अगर (type != शून्य)
		वापस type;

	lockdep_nfnl_nft_mutex_not_held();
#अगर_घोषित CONFIG_MODULES
	अगर (स्वतःload) अणु
		अगर (nft_request_module(net, "nft-chain-%u-%.*s", family,
				       nla_len(nla),
				       (स्थिर अक्षर *)nla_data(nla)) == -EAGAIN)
			वापस ERR_PTR(-EAGAIN);
	पूर्ण
#पूर्ण_अगर
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल __be16 nft_base_seq(स्थिर काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);

	वापस htons(nft_net->base_seq & 0xffff);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_table_policy[NFTA_TABLE_MAX + 1] = अणु
	[NFTA_TABLE_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_TABLE_MAXNAMELEN - 1 पूर्ण,
	[NFTA_TABLE_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TABLE_HANDLE]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_TABLE_USERDATA]	= अणु .type = NLA_BINARY,
				    .len = NFT_USERDATA_MAXLEN पूर्ण
पूर्ण;

अटल पूर्णांक nf_tables_fill_table_info(काष्ठा sk_buff *skb, काष्ठा net *net,
				     u32 portid, u32 seq, पूर्णांक event, u32 flags,
				     पूर्णांक family, स्थिर काष्ठा nft_table *table)
अणु
	काष्ठा nlmsghdr *nlh;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, family,
			   NFNETLINK_V0, nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_TABLE_NAME, table->name) ||
	    nla_put_be32(skb, NFTA_TABLE_FLAGS,
			 htonl(table->flags & NFT_TABLE_F_MASK)) ||
	    nla_put_be32(skb, NFTA_TABLE_USE, htonl(table->use)) ||
	    nla_put_be64(skb, NFTA_TABLE_HANDLE, cpu_to_be64(table->handle),
			 NFTA_TABLE_PAD))
		जाओ nla_put_failure;
	अगर (nft_table_has_owner(table) &&
	    nla_put_be32(skb, NFTA_TABLE_OWNER, htonl(table->nlpid)))
		जाओ nla_put_failure;

	अगर (table->udata) अणु
		अगर (nla_put(skb, NFTA_TABLE_USERDATA, table->udlen, table->udata))
			जाओ nla_put_failure;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

काष्ठा nftnl_skb_parms अणु
	bool report;
पूर्ण;
#घोषणा NFT_CB(skb)	(*(काष्ठा nftnl_skb_parms*)&((skb)->cb))

अटल व्योम nft_notअगरy_enqueue(काष्ठा sk_buff *skb, bool report,
			       काष्ठा list_head *notअगरy_list)
अणु
	NFT_CB(skb).report = report;
	list_add_tail(&skb->list, notअगरy_list);
पूर्ण

अटल व्योम nf_tables_table_notअगरy(स्थिर काष्ठा nft_ctx *ctx, पूर्णांक event)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (!ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_table_info(skb, ctx->net, ctx->portid, ctx->seq,
					event, 0, ctx->family, ctx->table);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_net = nft_pernet(ctx->net);
	nft_notअगरy_enqueue(skb, ctx->report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(ctx->net, ctx->portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण

अटल पूर्णांक nf_tables_dump_tables(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	काष्ठा nftables_pernet *nft_net;
	स्थिर काष्ठा nft_table *table;
	अचिन्हित पूर्णांक idx = 0, s_idx = cb->args[0];
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक family = nfmsg->nfgen_family;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	cb->seq = nft_net->base_seq;

	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (family != NFPROTO_UNSPEC && family != table->family)
			जारी;

		अगर (idx < s_idx)
			जाओ cont;
		अगर (idx > s_idx)
			स_रखो(&cb->args[1], 0,
			       माप(cb->args) - माप(cb->args[0]));
		अगर (!nft_is_active(net, table))
			जारी;
		अगर (nf_tables_fill_table_info(skb, net,
					      NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq,
					      NFT_MSG_NEWTABLE, NLM_F_MULTI,
					      table->family, table) < 0)
			जाओ करोne;

		nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
		idx++;
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nft_netlink_dump_start_rcu(काष्ठा sock *nlsk, काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nlmsghdr *nlh,
				      काष्ठा netlink_dump_control *c)
अणु
	पूर्णांक err;

	अगर (!try_module_get(THIS_MODULE))
		वापस -EINVAL;

	rcu_पढ़ो_unlock();
	err = netlink_dump_start(nlsk, skb, nlh, c);
	rcu_पढ़ो_lock();
	module_put(THIS_MODULE);

	वापस err;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_gettable(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	स्थिर काष्ठा nft_table *table;
	काष्ठा net *net = info->net;
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = nf_tables_dump_tables,
			.module = THIS_MODULE,
		पूर्ण;

		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	table = nft_table_lookup(net, nla[NFTA_TABLE_NAME], family, genmask, 0);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_TABLE_NAME]);
		वापस PTR_ERR(table);
	पूर्ण

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb2)
		वापस -ENOMEM;

	err = nf_tables_fill_table_info(skb2, net, NETLINK_CB(skb).portid,
					info->nlh->nlmsg_seq, NFT_MSG_NEWTABLE,
					0, family, table);
	अगर (err < 0)
		जाओ err_fill_table_info;

	वापस nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_table_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल व्योम nft_table_disable(काष्ठा net *net, काष्ठा nft_table *table, u32 cnt)
अणु
	काष्ठा nft_chain *chain;
	u32 i = 0;

	list_क्रम_each_entry(chain, &table->chains, list) अणु
		अगर (!nft_is_active_next(net, chain))
			जारी;
		अगर (!nft_is_base_chain(chain))
			जारी;

		अगर (cnt && i++ == cnt)
			अवरोध;

		nf_tables_unरेजिस्टर_hook(net, table, chain);
	पूर्ण
पूर्ण

अटल पूर्णांक nf_tables_table_enable(काष्ठा net *net, काष्ठा nft_table *table)
अणु
	काष्ठा nft_chain *chain;
	पूर्णांक err, i = 0;

	list_क्रम_each_entry(chain, &table->chains, list) अणु
		अगर (!nft_is_active_next(net, chain))
			जारी;
		अगर (!nft_is_base_chain(chain))
			जारी;

		err = nf_tables_रेजिस्टर_hook(net, table, chain);
		अगर (err < 0)
			जाओ err_रेजिस्टर_hooks;

		i++;
	पूर्ण
	वापस 0;

err_रेजिस्टर_hooks:
	अगर (i)
		nft_table_disable(net, table, i);
	वापस err;
पूर्ण

अटल व्योम nf_tables_table_disable(काष्ठा net *net, काष्ठा nft_table *table)
अणु
	table->flags &= ~NFT_TABLE_F_DORMANT;
	nft_table_disable(net, table, 0);
	table->flags |= NFT_TABLE_F_DORMANT;
पूर्ण

#घोषणा __NFT_TABLE_F_INTERNAL		(NFT_TABLE_F_MASK + 1)
#घोषणा __NFT_TABLE_F_WAS_DORMANT	(__NFT_TABLE_F_INTERNAL << 0)
#घोषणा __NFT_TABLE_F_WAS_AWAKEN	(__NFT_TABLE_F_INTERNAL << 1)
#घोषणा __NFT_TABLE_F_UPDATE		(__NFT_TABLE_F_WAS_DORMANT | \
					 __NFT_TABLE_F_WAS_AWAKEN)

अटल पूर्णांक nf_tables_updtable(काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_trans *trans;
	u32 flags;
	पूर्णांक ret;

	अगर (!ctx->nla[NFTA_TABLE_FLAGS])
		वापस 0;

	flags = ntohl(nla_get_be32(ctx->nla[NFTA_TABLE_FLAGS]));
	अगर (flags & ~NFT_TABLE_F_MASK)
		वापस -EOPNOTSUPP;

	अगर (flags == ctx->table->flags)
		वापस 0;

	अगर ((nft_table_has_owner(ctx->table) &&
	     !(flags & NFT_TABLE_F_OWNER)) ||
	    (!nft_table_has_owner(ctx->table) &&
	     flags & NFT_TABLE_F_OWNER))
		वापस -EOPNOTSUPP;

	trans = nft_trans_alloc(ctx, NFT_MSG_NEWTABLE,
				माप(काष्ठा nft_trans_table));
	अगर (trans == शून्य)
		वापस -ENOMEM;

	अगर ((flags & NFT_TABLE_F_DORMANT) &&
	    !(ctx->table->flags & NFT_TABLE_F_DORMANT)) अणु
		ctx->table->flags |= NFT_TABLE_F_DORMANT;
		अगर (!(ctx->table->flags & __NFT_TABLE_F_UPDATE))
			ctx->table->flags |= __NFT_TABLE_F_WAS_AWAKEN;
	पूर्ण अन्यथा अगर (!(flags & NFT_TABLE_F_DORMANT) &&
		   ctx->table->flags & NFT_TABLE_F_DORMANT) अणु
		ctx->table->flags &= ~NFT_TABLE_F_DORMANT;
		अगर (!(ctx->table->flags & __NFT_TABLE_F_UPDATE)) अणु
			ret = nf_tables_table_enable(ctx->net, ctx->table);
			अगर (ret < 0)
				जाओ err_रेजिस्टर_hooks;

			ctx->table->flags |= __NFT_TABLE_F_WAS_DORMANT;
		पूर्ण
	पूर्ण

	nft_trans_table_update(trans) = true;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;

err_रेजिस्टर_hooks:
	nft_trans_destroy(trans);
	वापस ret;
पूर्ण

अटल u32 nft_chain_hash(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर अक्षर *name = data;

	वापस jhash(name, म_माप(name), seed);
पूर्ण

अटल u32 nft_chain_hash_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nft_chain *chain = data;

	वापस nft_chain_hash(chain->name, 0, seed);
पूर्ण

अटल पूर्णांक nft_chain_hash_cmp(काष्ठा rhashtable_compare_arg *arg,
			      स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा nft_chain *chain = ptr;
	स्थिर अक्षर *name = arg->key;

	वापस म_भेद(chain->name, name);
पूर्ण

अटल u32 nft_objname_hash(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nft_object_hash_key *k = data;

	seed ^= hash_ptr(k->table, 32);

	वापस jhash(k->name, म_माप(k->name), seed);
पूर्ण

अटल u32 nft_objname_hash_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nft_object *obj = data;

	वापस nft_objname_hash(&obj->key, 0, seed);
पूर्ण

अटल पूर्णांक nft_objname_hash_cmp(काष्ठा rhashtable_compare_arg *arg,
				स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा nft_object_hash_key *k = arg->key;
	स्थिर काष्ठा nft_object *obj = ptr;

	अगर (obj->key.table != k->table)
		वापस -1;

	वापस म_भेद(obj->key.name, k->name);
पूर्ण

अटल पूर्णांक nf_tables_newtable(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(info->net);
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_table *table;
	काष्ठा nft_ctx ctx;
	u32 flags = 0;
	पूर्णांक err;

	lockdep_निश्चित_held(&nft_net->commit_mutex);
	attr = nla[NFTA_TABLE_NAME];
	table = nft_table_lookup(net, attr, family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		अगर (PTR_ERR(table) != -ENOENT)
			वापस PTR_ERR(table);
	पूर्ण अन्यथा अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL) अणु
			NL_SET_BAD_ATTR(extack, attr);
			वापस -EEXIST;
		पूर्ण
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE)
			वापस -EOPNOTSUPP;

		nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

		वापस nf_tables_updtable(&ctx);
	पूर्ण

	अगर (nla[NFTA_TABLE_FLAGS]) अणु
		flags = ntohl(nla_get_be32(nla[NFTA_TABLE_FLAGS]));
		अगर (flags & ~NFT_TABLE_F_MASK)
			वापस -EOPNOTSUPP;
	पूर्ण

	err = -ENOMEM;
	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (table == शून्य)
		जाओ err_kzalloc;

	table->name = nla_strdup(attr, GFP_KERNEL);
	अगर (table->name == शून्य)
		जाओ err_strdup;

	अगर (nla[NFTA_TABLE_USERDATA]) अणु
		table->udata = nla_memdup(nla[NFTA_TABLE_USERDATA], GFP_KERNEL);
		अगर (table->udata == शून्य)
			जाओ err_table_udata;

		table->udlen = nla_len(nla[NFTA_TABLE_USERDATA]);
	पूर्ण

	err = rhltable_init(&table->chains_ht, &nft_chain_ht_params);
	अगर (err)
		जाओ err_chain_ht;

	INIT_LIST_HEAD(&table->chains);
	INIT_LIST_HEAD(&table->sets);
	INIT_LIST_HEAD(&table->objects);
	INIT_LIST_HEAD(&table->flowtables);
	table->family = family;
	table->flags = flags;
	table->handle = ++table_handle;
	अगर (table->flags & NFT_TABLE_F_OWNER)
		table->nlpid = NETLINK_CB(skb).portid;

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);
	err = nft_trans_table_add(&ctx, NFT_MSG_NEWTABLE);
	अगर (err < 0)
		जाओ err_trans;

	list_add_tail_rcu(&table->list, &nft_net->tables);
	वापस 0;
err_trans:
	rhltable_destroy(&table->chains_ht);
err_chain_ht:
	kमुक्त(table->udata);
err_table_udata:
	kमुक्त(table->name);
err_strdup:
	kमुक्त(table);
err_kzalloc:
	वापस err;
पूर्ण

अटल पूर्णांक nft_flush_table(काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_flowtable *flowtable, *nft;
	काष्ठा nft_chain *chain, *nc;
	काष्ठा nft_object *obj, *ne;
	काष्ठा nft_set *set, *ns;
	पूर्णांक err;

	list_क्रम_each_entry(chain, &ctx->table->chains, list) अणु
		अगर (!nft_is_active_next(ctx->net, chain))
			जारी;

		अगर (nft_chain_is_bound(chain))
			जारी;

		ctx->chain = chain;

		err = nft_delrule_by_chain(ctx);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(set, ns, &ctx->table->sets, list) अणु
		अगर (!nft_is_active_next(ctx->net, set))
			जारी;

		अगर (nft_set_is_anonymous(set) &&
		    !list_empty(&set->bindings))
			जारी;

		err = nft_dअन्यथाt(ctx, set);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(flowtable, nft, &ctx->table->flowtables, list) अणु
		अगर (!nft_is_active_next(ctx->net, flowtable))
			जारी;

		err = nft_delflowtable(ctx, flowtable);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(obj, ne, &ctx->table->objects, list) अणु
		अगर (!nft_is_active_next(ctx->net, obj))
			जारी;

		err = nft_delobj(ctx, obj);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(chain, nc, &ctx->table->chains, list) अणु
		अगर (!nft_is_active_next(ctx->net, chain))
			जारी;

		अगर (nft_chain_is_bound(chain))
			जारी;

		ctx->chain = chain;

		err = nft_delchain(ctx);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	err = nft_deltable(ctx);
out:
	वापस err;
पूर्ण

अटल पूर्णांक nft_flush(काष्ठा nft_ctx *ctx, पूर्णांक family)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
	स्थिर काष्ठा nlattr * स्थिर *nla = ctx->nla;
	काष्ठा nft_table *table, *nt;
	पूर्णांक err = 0;

	list_क्रम_each_entry_safe(table, nt, &nft_net->tables, list) अणु
		अगर (family != AF_UNSPEC && table->family != family)
			जारी;

		ctx->family = table->family;

		अगर (!nft_is_active_next(ctx->net, table))
			जारी;

		अगर (nft_table_has_owner(table) && table->nlpid != ctx->portid)
			जारी;

		अगर (nla[NFTA_TABLE_NAME] &&
		    nla_म_भेद(nla[NFTA_TABLE_NAME], table->name) != 0)
			जारी;

		ctx->table = table;

		err = nft_flush_table(ctx);
		अगर (err < 0)
			जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_deltable(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_table *table;
	काष्ठा nft_ctx ctx;

	nft_ctx_init(&ctx, net, skb, info->nlh, 0, शून्य, शून्य, nla);
	अगर (family == AF_UNSPEC ||
	    (!nla[NFTA_TABLE_NAME] && !nla[NFTA_TABLE_HANDLE]))
		वापस nft_flush(&ctx, family);

	अगर (nla[NFTA_TABLE_HANDLE]) अणु
		attr = nla[NFTA_TABLE_HANDLE];
		table = nft_table_lookup_byhandle(net, attr, genmask);
	पूर्ण अन्यथा अणु
		attr = nla[NFTA_TABLE_NAME];
		table = nft_table_lookup(net, attr, family, genmask,
					 NETLINK_CB(skb).portid);
	पूर्ण

	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस PTR_ERR(table);
	पूर्ण

	अगर (info->nlh->nlmsg_flags & NLM_F_NONREC &&
	    table->use > 0)
		वापस -EBUSY;

	ctx.family = family;
	ctx.table = table;

	वापस nft_flush_table(&ctx);
पूर्ण

अटल व्योम nf_tables_table_destroy(काष्ठा nft_ctx *ctx)
अणु
	अगर (WARN_ON(ctx->table->use > 0))
		वापस;

	rhltable_destroy(&ctx->table->chains_ht);
	kमुक्त(ctx->table->name);
	kमुक्त(ctx->table->udata);
	kमुक्त(ctx->table);
पूर्ण

व्योम nft_रेजिस्टर_chain_type(स्थिर काष्ठा nft_chain_type *ctype)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	अगर (WARN_ON(__nft_chain_type_get(ctype->family, ctype->type))) अणु
		nfnl_unlock(NFNL_SUBSYS_NFTABLES);
		वापस;
	पूर्ण
	chain_type[ctype->family][ctype->type] = ctype;
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
पूर्ण
EXPORT_SYMBOL_GPL(nft_रेजिस्टर_chain_type);

व्योम nft_unरेजिस्टर_chain_type(स्थिर काष्ठा nft_chain_type *ctype)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	chain_type[ctype->family][ctype->type] = शून्य;
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
पूर्ण
EXPORT_SYMBOL_GPL(nft_unरेजिस्टर_chain_type);

/*
 * Chains
 */

अटल काष्ठा nft_chain *
nft_chain_lookup_byhandle(स्थिर काष्ठा nft_table *table, u64 handle, u8 genmask)
अणु
	काष्ठा nft_chain *chain;

	list_क्रम_each_entry(chain, &table->chains, list) अणु
		अगर (chain->handle == handle &&
		    nft_active_genmask(chain, genmask))
			वापस chain;
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल bool lockdep_commit_lock_is_held(स्थिर काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROVE_LOCKING
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);

	वापस lockdep_is_held(&nft_net->commit_mutex);
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा nft_chain *nft_chain_lookup(काष्ठा net *net,
					  काष्ठा nft_table *table,
					  स्थिर काष्ठा nlattr *nla, u8 genmask)
अणु
	अक्षर search[NFT_CHAIN_MAXNAMELEN + 1];
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा nft_chain *chain;

	अगर (nla == शून्य)
		वापस ERR_PTR(-EINVAL);

	nla_strscpy(search, nla, माप(search));

	WARN_ON(!rcu_पढ़ो_lock_held() &&
		!lockdep_commit_lock_is_held(net));

	chain = ERR_PTR(-ENOENT);
	rcu_पढ़ो_lock();
	list = rhltable_lookup(&table->chains_ht, search, nft_chain_ht_params);
	अगर (!list)
		जाओ out_unlock;

	rhl_क्रम_each_entry_rcu(chain, पंचांगp, list, rhlhead) अणु
		अगर (nft_active_genmask(chain, genmask))
			जाओ out_unlock;
	पूर्ण
	chain = ERR_PTR(-ENOENT);
out_unlock:
	rcu_पढ़ो_unlock();
	वापस chain;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_chain_policy[NFTA_CHAIN_MAX + 1] = अणु
	[NFTA_CHAIN_TABLE]	= अणु .type = NLA_STRING,
				    .len = NFT_TABLE_MAXNAMELEN - 1 पूर्ण,
	[NFTA_CHAIN_HANDLE]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_CHAIN_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_CHAIN_MAXNAMELEN - 1 पूर्ण,
	[NFTA_CHAIN_HOOK]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_CHAIN_POLICY]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CHAIN_TYPE]	= अणु .type = NLA_STRING,
				    .len = NFT_MODULE_AUTOLOAD_LIMIT पूर्ण,
	[NFTA_CHAIN_COUNTERS]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_CHAIN_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CHAIN_ID]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CHAIN_USERDATA]	= अणु .type = NLA_BINARY,
				    .len = NFT_USERDATA_MAXLEN पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_hook_policy[NFTA_HOOK_MAX + 1] = अणु
	[NFTA_HOOK_HOOKNUM]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HOOK_PRIORITY]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_HOOK_DEV]		= अणु .type = NLA_STRING,
				    .len = IFNAMSIZ - 1 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_dump_stats(काष्ठा sk_buff *skb, काष्ठा nft_stats __percpu *stats)
अणु
	काष्ठा nft_stats *cpu_stats, total;
	काष्ठा nlattr *nest;
	अचिन्हित पूर्णांक seq;
	u64 pkts, bytes;
	पूर्णांक cpu;

	अगर (!stats)
		वापस 0;

	स_रखो(&total, 0, माप(total));
	क्रम_each_possible_cpu(cpu) अणु
		cpu_stats = per_cpu_ptr(stats, cpu);
		करो अणु
			seq = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			pkts = cpu_stats->pkts;
			bytes = cpu_stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, seq));
		total.pkts += pkts;
		total.bytes += bytes;
	पूर्ण
	nest = nla_nest_start_noflag(skb, NFTA_CHAIN_COUNTERS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_be64(skb, NFTA_COUNTER_PACKETS, cpu_to_be64(total.pkts),
			 NFTA_COUNTER_PAD) ||
	    nla_put_be64(skb, NFTA_COUNTER_BYTES, cpu_to_be64(total.bytes),
			 NFTA_COUNTER_PAD))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक nft_dump_basechain_hook(काष्ठा sk_buff *skb, पूर्णांक family,
				   स्थिर काष्ठा nft_base_chain *basechain)
अणु
	स्थिर काष्ठा nf_hook_ops *ops = &basechain->ops;
	काष्ठा nft_hook *hook, *first = शून्य;
	काष्ठा nlattr *nest, *nest_devs;
	पूर्णांक n = 0;

	nest = nla_nest_start_noflag(skb, NFTA_CHAIN_HOOK);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HOOK_HOOKNUM, htonl(ops->hooknum)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_HOOK_PRIORITY, htonl(ops->priority)))
		जाओ nla_put_failure;

	अगर (nft_base_chain_netdev(family, ops->hooknum)) अणु
		nest_devs = nla_nest_start_noflag(skb, NFTA_HOOK_DEVS);
		list_क्रम_each_entry(hook, &basechain->hook_list, list) अणु
			अगर (!first)
				first = hook;

			अगर (nla_put_string(skb, NFTA_DEVICE_NAME,
					   hook->ops.dev->name))
				जाओ nla_put_failure;
			n++;
		पूर्ण
		nla_nest_end(skb, nest_devs);

		अगर (n == 1 &&
		    nla_put_string(skb, NFTA_HOOK_DEV, first->ops.dev->name))
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, nest);

	वापस 0;
nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nf_tables_fill_chain_info(काष्ठा sk_buff *skb, काष्ठा net *net,
				     u32 portid, u32 seq, पूर्णांक event, u32 flags,
				     पूर्णांक family, स्थिर काष्ठा nft_table *table,
				     स्थिर काष्ठा nft_chain *chain)
अणु
	काष्ठा nlmsghdr *nlh;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, family,
			   NFNETLINK_V0, nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_CHAIN_TABLE, table->name))
		जाओ nla_put_failure;
	अगर (nla_put_be64(skb, NFTA_CHAIN_HANDLE, cpu_to_be64(chain->handle),
			 NFTA_CHAIN_PAD))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, NFTA_CHAIN_NAME, chain->name))
		जाओ nla_put_failure;

	अगर (nft_is_base_chain(chain)) अणु
		स्थिर काष्ठा nft_base_chain *basechain = nft_base_chain(chain);
		काष्ठा nft_stats __percpu *stats;

		अगर (nft_dump_basechain_hook(skb, family, basechain))
			जाओ nla_put_failure;

		अगर (nla_put_be32(skb, NFTA_CHAIN_POLICY,
				 htonl(basechain->policy)))
			जाओ nla_put_failure;

		अगर (nla_put_string(skb, NFTA_CHAIN_TYPE, basechain->type->name))
			जाओ nla_put_failure;

		stats = rcu_dereference_check(basechain->stats,
					      lockdep_commit_lock_is_held(net));
		अगर (nft_dump_stats(skb, stats))
			जाओ nla_put_failure;
	पूर्ण

	अगर (chain->flags &&
	    nla_put_be32(skb, NFTA_CHAIN_FLAGS, htonl(chain->flags)))
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_CHAIN_USE, htonl(chain->use)))
		जाओ nla_put_failure;

	अगर (chain->udata &&
	    nla_put(skb, NFTA_CHAIN_USERDATA, chain->udlen, chain->udata))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

अटल व्योम nf_tables_chain_notअगरy(स्थिर काष्ठा nft_ctx *ctx, पूर्णांक event)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (!ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_chain_info(skb, ctx->net, ctx->portid, ctx->seq,
					event, 0, ctx->family, ctx->table,
					ctx->chain);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_net = nft_pernet(ctx->net);
	nft_notअगरy_enqueue(skb, ctx->report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(ctx->net, ctx->portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण

अटल पूर्णांक nf_tables_dump_chains(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	अचिन्हित पूर्णांक idx = 0, s_idx = cb->args[0];
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nftables_pernet *nft_net;
	स्थिर काष्ठा nft_table *table;
	स्थिर काष्ठा nft_chain *chain;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	cb->seq = nft_net->base_seq;

	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (family != NFPROTO_UNSPEC && family != table->family)
			जारी;

		list_क्रम_each_entry_rcu(chain, &table->chains, list) अणु
			अगर (idx < s_idx)
				जाओ cont;
			अगर (idx > s_idx)
				स_रखो(&cb->args[1], 0,
				       माप(cb->args) - माप(cb->args[0]));
			अगर (!nft_is_active(net, chain))
				जारी;
			अगर (nf_tables_fill_chain_info(skb, net,
						      NETLINK_CB(cb->skb).portid,
						      cb->nlh->nlmsg_seq,
						      NFT_MSG_NEWCHAIN,
						      NLM_F_MULTI,
						      table->family, table,
						      chain) < 0)
				जाओ करोne;

			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_अ_लोhain(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	स्थिर काष्ठा nft_chain *chain;
	काष्ठा net *net = info->net;
	काष्ठा nft_table *table;
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = nf_tables_dump_chains,
			.module = THIS_MODULE,
		पूर्ण;

		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	table = nft_table_lookup(net, nla[NFTA_CHAIN_TABLE], family, genmask, 0);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	chain = nft_chain_lookup(net, table, nla[NFTA_CHAIN_NAME], genmask);
	अगर (IS_ERR(chain)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_NAME]);
		वापस PTR_ERR(chain);
	पूर्ण

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb2)
		वापस -ENOMEM;

	err = nf_tables_fill_chain_info(skb2, net, NETLINK_CB(skb).portid,
					info->nlh->nlmsg_seq, NFT_MSG_NEWCHAIN,
					0, family, table, chain);
	अगर (err < 0)
		जाओ err_fill_chain_info;

	वापस nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_chain_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_counter_policy[NFTA_COUNTER_MAX + 1] = अणु
	[NFTA_COUNTER_PACKETS]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_COUNTER_BYTES]	= अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल काष्ठा nft_stats __percpu *nft_stats_alloc(स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[NFTA_COUNTER_MAX+1];
	काष्ठा nft_stats __percpu *newstats;
	काष्ठा nft_stats *stats;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_COUNTER_MAX, attr,
					  nft_counter_policy, शून्य);
	अगर (err < 0)
		वापस ERR_PTR(err);

	अगर (!tb[NFTA_COUNTER_BYTES] || !tb[NFTA_COUNTER_PACKETS])
		वापस ERR_PTR(-EINVAL);

	newstats = netdev_alloc_pcpu_stats(काष्ठा nft_stats);
	अगर (newstats == शून्य)
		वापस ERR_PTR(-ENOMEM);

	/* Restore old counters on this cpu, no problem. Per-cpu statistics
	 * are not exposed to userspace.
	 */
	preempt_disable();
	stats = this_cpu_ptr(newstats);
	stats->bytes = be64_to_cpu(nla_get_be64(tb[NFTA_COUNTER_BYTES]));
	stats->pkts = be64_to_cpu(nla_get_be64(tb[NFTA_COUNTER_PACKETS]));
	preempt_enable();

	वापस newstats;
पूर्ण

अटल व्योम nft_chain_stats_replace(काष्ठा nft_trans *trans)
अणु
	काष्ठा nft_base_chain *chain = nft_base_chain(trans->ctx.chain);

	अगर (!nft_trans_chain_stats(trans))
		वापस;

	nft_trans_chain_stats(trans) =
		rcu_replace_poपूर्णांकer(chain->stats, nft_trans_chain_stats(trans),
				    lockdep_commit_lock_is_held(trans->ctx.net));

	अगर (!nft_trans_chain_stats(trans))
		अटल_branch_inc(&nft_counters_enabled);
पूर्ण

अटल व्योम nf_tables_chain_मुक्त_chain_rules(काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_rule **g0 = rcu_dereference_raw(chain->rules_gen_0);
	काष्ठा nft_rule **g1 = rcu_dereference_raw(chain->rules_gen_1);

	अगर (g0 != g1)
		kvमुक्त(g1);
	kvमुक्त(g0);

	/* should be शून्य either via पात or via successful commit */
	WARN_ON_ONCE(chain->rules_next);
	kvमुक्त(chain->rules_next);
पूर्ण

व्योम nf_tables_chain_destroy(काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_chain *chain = ctx->chain;
	काष्ठा nft_hook *hook, *next;

	अगर (WARN_ON(chain->use > 0))
		वापस;

	/* no concurrent access possible anymore */
	nf_tables_chain_मुक्त_chain_rules(chain);

	अगर (nft_is_base_chain(chain)) अणु
		काष्ठा nft_base_chain *basechain = nft_base_chain(chain);

		अगर (nft_base_chain_netdev(ctx->family, basechain->ops.hooknum)) अणु
			list_क्रम_each_entry_safe(hook, next,
						 &basechain->hook_list, list) अणु
				list_del_rcu(&hook->list);
				kमुक्त_rcu(hook, rcu);
			पूर्ण
		पूर्ण
		module_put(basechain->type->owner);
		अगर (rcu_access_poपूर्णांकer(basechain->stats)) अणु
			अटल_branch_dec(&nft_counters_enabled);
			मुक्त_percpu(rcu_dereference_raw(basechain->stats));
		पूर्ण
		kमुक्त(chain->name);
		kमुक्त(chain->udata);
		kमुक्त(basechain);
	पूर्ण अन्यथा अणु
		kमुक्त(chain->name);
		kमुक्त(chain->udata);
		kमुक्त(chain);
	पूर्ण
पूर्ण

अटल काष्ठा nft_hook *nft_netdev_hook_alloc(काष्ठा net *net,
					      स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा net_device *dev;
	अक्षर अगरname[IFNAMSIZ];
	काष्ठा nft_hook *hook;
	पूर्णांक err;

	hook = kदो_स्मृति(माप(काष्ठा nft_hook), GFP_KERNEL);
	अगर (!hook) अणु
		err = -ENOMEM;
		जाओ err_hook_alloc;
	पूर्ण

	nla_strscpy(अगरname, attr, IFNAMSIZ);
	/* nf_tables_netdev_event() is called under rtnl_mutex, this is
	 * indirectly serializing all the other holders of the commit_mutex with
	 * the rtnl_mutex.
	 */
	dev = __dev_get_by_name(net, अगरname);
	अगर (!dev) अणु
		err = -ENOENT;
		जाओ err_hook_dev;
	पूर्ण
	hook->ops.dev = dev;
	hook->inactive = false;

	वापस hook;

err_hook_dev:
	kमुक्त(hook);
err_hook_alloc:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा nft_hook *nft_hook_list_find(काष्ठा list_head *hook_list,
					   स्थिर काष्ठा nft_hook *this)
अणु
	काष्ठा nft_hook *hook;

	list_क्रम_each_entry(hook, hook_list, list) अणु
		अगर (this->ops.dev == hook->ops.dev)
			वापस hook;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक nf_tables_parse_netdev_hooks(काष्ठा net *net,
					स्थिर काष्ठा nlattr *attr,
					काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook, *next;
	स्थिर काष्ठा nlattr *पंचांगp;
	पूर्णांक rem, n = 0, err;

	nla_क्रम_each_nested(पंचांगp, attr, rem) अणु
		अगर (nla_type(पंचांगp) != NFTA_DEVICE_NAME) अणु
			err = -EINVAL;
			जाओ err_hook;
		पूर्ण

		hook = nft_netdev_hook_alloc(net, पंचांगp);
		अगर (IS_ERR(hook)) अणु
			err = PTR_ERR(hook);
			जाओ err_hook;
		पूर्ण
		अगर (nft_hook_list_find(hook_list, hook)) अणु
			kमुक्त(hook);
			err = -EEXIST;
			जाओ err_hook;
		पूर्ण
		list_add_tail(&hook->list, hook_list);
		n++;

		अगर (n == NFT_NETDEVICE_MAX) अणु
			err = -EFBIG;
			जाओ err_hook;
		पूर्ण
	पूर्ण

	वापस 0;

err_hook:
	list_क्रम_each_entry_safe(hook, next, hook_list, list) अणु
		list_del(&hook->list);
		kमुक्त(hook);
	पूर्ण
	वापस err;
पूर्ण

काष्ठा nft_chain_hook अणु
	u32				num;
	s32				priority;
	स्थिर काष्ठा nft_chain_type	*type;
	काष्ठा list_head		list;
पूर्ण;

अटल पूर्णांक nft_chain_parse_netdev(काष्ठा net *net,
				  काष्ठा nlattr *tb[],
				  काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook;
	पूर्णांक err;

	अगर (tb[NFTA_HOOK_DEV]) अणु
		hook = nft_netdev_hook_alloc(net, tb[NFTA_HOOK_DEV]);
		अगर (IS_ERR(hook))
			वापस PTR_ERR(hook);

		list_add_tail(&hook->list, hook_list);
	पूर्ण अन्यथा अगर (tb[NFTA_HOOK_DEVS]) अणु
		err = nf_tables_parse_netdev_hooks(net, tb[NFTA_HOOK_DEVS],
						   hook_list);
		अगर (err < 0)
			वापस err;

		अगर (list_empty(hook_list))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_chain_parse_hook(काष्ठा net *net,
				स्थिर काष्ठा nlattr * स्थिर nla[],
				काष्ठा nft_chain_hook *hook, u8 family,
				काष्ठा netlink_ext_ack *extack, bool स्वतःload)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nlattr *ha[NFTA_HOOK_MAX + 1];
	स्थिर काष्ठा nft_chain_type *type;
	पूर्णांक err;

	lockdep_निश्चित_held(&nft_net->commit_mutex);
	lockdep_nfnl_nft_mutex_not_held();

	err = nla_parse_nested_deprecated(ha, NFTA_HOOK_MAX,
					  nla[NFTA_CHAIN_HOOK],
					  nft_hook_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (ha[NFTA_HOOK_HOOKNUM] == शून्य ||
	    ha[NFTA_HOOK_PRIORITY] == शून्य)
		वापस -EINVAL;

	hook->num = ntohl(nla_get_be32(ha[NFTA_HOOK_HOOKNUM]));
	hook->priority = ntohl(nla_get_be32(ha[NFTA_HOOK_PRIORITY]));

	type = __nft_chain_type_get(family, NFT_CHAIN_T_DEFAULT);
	अगर (!type)
		वापस -EOPNOTSUPP;

	अगर (nla[NFTA_CHAIN_TYPE]) अणु
		type = nf_tables_chain_type_lookup(net, nla[NFTA_CHAIN_TYPE],
						   family, स्वतःload);
		अगर (IS_ERR(type)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_TYPE]);
			वापस PTR_ERR(type);
		पूर्ण
	पूर्ण
	अगर (hook->num >= NFT_MAX_HOOKS || !(type->hook_mask & (1 << hook->num)))
		वापस -EOPNOTSUPP;

	अगर (type->type == NFT_CHAIN_T_NAT &&
	    hook->priority <= NF_IP_PRI_CONNTRACK)
		वापस -EOPNOTSUPP;

	अगर (!try_module_get(type->owner)) अणु
		अगर (nla[NFTA_CHAIN_TYPE])
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_TYPE]);
		वापस -ENOENT;
	पूर्ण

	hook->type = type;

	INIT_LIST_HEAD(&hook->list);
	अगर (nft_base_chain_netdev(family, hook->num)) अणु
		err = nft_chain_parse_netdev(net, ha, &hook->list);
		अगर (err < 0) अणु
			module_put(type->owner);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (ha[NFTA_HOOK_DEV] || ha[NFTA_HOOK_DEVS]) अणु
		module_put(type->owner);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nft_chain_release_hook(काष्ठा nft_chain_hook *hook)
अणु
	काष्ठा nft_hook *h, *next;

	list_क्रम_each_entry_safe(h, next, &hook->list, list) अणु
		list_del(&h->list);
		kमुक्त(h);
	पूर्ण
	module_put(hook->type->owner);
पूर्ण

काष्ठा nft_rules_old अणु
	काष्ठा rcu_head h;
	काष्ठा nft_rule **start;
पूर्ण;

अटल काष्ठा nft_rule **nf_tables_chain_alloc_rules(स्थिर काष्ठा nft_chain *chain,
						     अचिन्हित पूर्णांक alloc)
अणु
	अगर (alloc > पूर्णांक_उच्च)
		वापस शून्य;

	alloc += 1;	/* शून्य, ends rules */
	अगर (माप(काष्ठा nft_rule *) > पूर्णांक_उच्च / alloc)
		वापस शून्य;

	alloc *= माप(काष्ठा nft_rule *);
	alloc += माप(काष्ठा nft_rules_old);

	वापस kvदो_स्मृति(alloc, GFP_KERNEL);
पूर्ण

अटल व्योम nft_basechain_hook_init(काष्ठा nf_hook_ops *ops, u8 family,
				    स्थिर काष्ठा nft_chain_hook *hook,
				    काष्ठा nft_chain *chain)
अणु
	ops->pf		= family;
	ops->hooknum	= hook->num;
	ops->priority	= hook->priority;
	ops->priv	= chain;
	ops->hook	= hook->type->hooks[ops->hooknum];
पूर्ण

अटल पूर्णांक nft_basechain_init(काष्ठा nft_base_chain *basechain, u8 family,
			      काष्ठा nft_chain_hook *hook, u32 flags)
अणु
	काष्ठा nft_chain *chain;
	काष्ठा nft_hook *h;

	basechain->type = hook->type;
	INIT_LIST_HEAD(&basechain->hook_list);
	chain = &basechain->chain;

	अगर (nft_base_chain_netdev(family, hook->num)) अणु
		list_splice_init(&hook->list, &basechain->hook_list);
		list_क्रम_each_entry(h, &basechain->hook_list, list)
			nft_basechain_hook_init(&h->ops, family, hook, chain);

		basechain->ops.hooknum	= hook->num;
		basechain->ops.priority	= hook->priority;
	पूर्ण अन्यथा अणु
		nft_basechain_hook_init(&basechain->ops, family, hook, chain);
	पूर्ण

	chain->flags |= NFT_CHAIN_BASE | flags;
	basechain->policy = NF_ACCEPT;
	अगर (chain->flags & NFT_CHAIN_HW_OFFLOAD &&
	    nft_chain_offload_priority(basechain) < 0)
		वापस -EOPNOTSUPP;

	flow_block_init(&basechain->flow_block);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_chain_add(काष्ठा nft_table *table, काष्ठा nft_chain *chain)
अणु
	पूर्णांक err;

	err = rhltable_insert_key(&table->chains_ht, chain->name,
				  &chain->rhlhead, nft_chain_ht_params);
	अगर (err)
		वापस err;

	list_add_tail_rcu(&chain->list, &table->chains);

	वापस 0;
पूर्ण

अटल u64 chain_id;

अटल पूर्णांक nf_tables_addchain(काष्ठा nft_ctx *ctx, u8 family, u8 genmask,
			      u8 policy, u32 flags,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = ctx->nla;
	काष्ठा nft_table *table = ctx->table;
	काष्ठा nft_base_chain *basechain;
	काष्ठा nft_stats __percpu *stats;
	काष्ठा net *net = ctx->net;
	अक्षर name[NFT_NAME_MAXLEN];
	काष्ठा nft_trans *trans;
	काष्ठा nft_chain *chain;
	काष्ठा nft_rule **rules;
	पूर्णांक err;

	अगर (table->use == अच_पूर्णांक_उच्च)
		वापस -EOVERFLOW;

	अगर (nla[NFTA_CHAIN_HOOK]) अणु
		काष्ठा nft_chain_hook hook;

		अगर (flags & NFT_CHAIN_BINDING)
			वापस -EOPNOTSUPP;

		err = nft_chain_parse_hook(net, nla, &hook, family, extack,
					   true);
		अगर (err < 0)
			वापस err;

		basechain = kzalloc(माप(*basechain), GFP_KERNEL);
		अगर (basechain == शून्य) अणु
			nft_chain_release_hook(&hook);
			वापस -ENOMEM;
		पूर्ण
		chain = &basechain->chain;

		अगर (nla[NFTA_CHAIN_COUNTERS]) अणु
			stats = nft_stats_alloc(nla[NFTA_CHAIN_COUNTERS]);
			अगर (IS_ERR(stats)) अणु
				nft_chain_release_hook(&hook);
				kमुक्त(basechain);
				वापस PTR_ERR(stats);
			पूर्ण
			rcu_assign_poपूर्णांकer(basechain->stats, stats);
			अटल_branch_inc(&nft_counters_enabled);
		पूर्ण

		err = nft_basechain_init(basechain, family, &hook, flags);
		अगर (err < 0) अणु
			nft_chain_release_hook(&hook);
			kमुक्त(basechain);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (flags & NFT_CHAIN_BASE)
			वापस -EINVAL;
		अगर (flags & NFT_CHAIN_HW_OFFLOAD)
			वापस -EOPNOTSUPP;

		chain = kzalloc(माप(*chain), GFP_KERNEL);
		अगर (chain == शून्य)
			वापस -ENOMEM;

		chain->flags = flags;
	पूर्ण
	ctx->chain = chain;

	INIT_LIST_HEAD(&chain->rules);
	chain->handle = nf_tables_alloc_handle(table);
	chain->table = table;

	अगर (nla[NFTA_CHAIN_NAME]) अणु
		chain->name = nla_strdup(nla[NFTA_CHAIN_NAME], GFP_KERNEL);
	पूर्ण अन्यथा अणु
		अगर (!(flags & NFT_CHAIN_BINDING)) अणु
			err = -EINVAL;
			जाओ err_destroy_chain;
		पूर्ण

		snम_लिखो(name, माप(name), "__chain%llu", ++chain_id);
		chain->name = kstrdup(name, GFP_KERNEL);
	पूर्ण

	अगर (!chain->name) अणु
		err = -ENOMEM;
		जाओ err_destroy_chain;
	पूर्ण

	अगर (nla[NFTA_CHAIN_USERDATA]) अणु
		chain->udata = nla_memdup(nla[NFTA_CHAIN_USERDATA], GFP_KERNEL);
		अगर (chain->udata == शून्य) अणु
			err = -ENOMEM;
			जाओ err_destroy_chain;
		पूर्ण
		chain->udlen = nla_len(nla[NFTA_CHAIN_USERDATA]);
	पूर्ण

	rules = nf_tables_chain_alloc_rules(chain, 0);
	अगर (!rules) अणु
		err = -ENOMEM;
		जाओ err_destroy_chain;
	पूर्ण

	*rules = शून्य;
	rcu_assign_poपूर्णांकer(chain->rules_gen_0, rules);
	rcu_assign_poपूर्णांकer(chain->rules_gen_1, rules);

	err = nf_tables_रेजिस्टर_hook(net, table, chain);
	अगर (err < 0)
		जाओ err_destroy_chain;

	trans = nft_trans_chain_add(ctx, NFT_MSG_NEWCHAIN);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		जाओ err_unरेजिस्टर_hook;
	पूर्ण

	nft_trans_chain_policy(trans) = NFT_CHAIN_POLICY_UNSET;
	अगर (nft_is_base_chain(chain))
		nft_trans_chain_policy(trans) = policy;

	err = nft_chain_add(table, chain);
	अगर (err < 0) अणु
		nft_trans_destroy(trans);
		जाओ err_unरेजिस्टर_hook;
	पूर्ण

	table->use++;

	वापस 0;
err_unरेजिस्टर_hook:
	nf_tables_unरेजिस्टर_hook(net, table, chain);
err_destroy_chain:
	nf_tables_chain_destroy(ctx);

	वापस err;
पूर्ण

अटल bool nft_hook_list_equal(काष्ठा list_head *hook_list1,
				काष्ठा list_head *hook_list2)
अणु
	काष्ठा nft_hook *hook;
	पूर्णांक n = 0, m = 0;

	n = 0;
	list_क्रम_each_entry(hook, hook_list2, list) अणु
		अगर (!nft_hook_list_find(hook_list1, hook))
			वापस false;

		n++;
	पूर्ण
	list_क्रम_each_entry(hook, hook_list1, list)
		m++;

	वापस n == m;
पूर्ण

अटल पूर्णांक nf_tables_updchain(काष्ठा nft_ctx *ctx, u8 genmask, u8 policy,
			      u32 flags, स्थिर काष्ठा nlattr *attr,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = ctx->nla;
	काष्ठा nft_table *table = ctx->table;
	काष्ठा nft_chain *chain = ctx->chain;
	काष्ठा nft_base_chain *basechain;
	काष्ठा nft_stats *stats = शून्य;
	काष्ठा nft_chain_hook hook;
	काष्ठा nf_hook_ops *ops;
	काष्ठा nft_trans *trans;
	पूर्णांक err;

	अगर (chain->flags ^ flags)
		वापस -EOPNOTSUPP;

	अगर (nla[NFTA_CHAIN_HOOK]) अणु
		अगर (!nft_is_base_chain(chain)) अणु
			NL_SET_BAD_ATTR(extack, attr);
			वापस -EEXIST;
		पूर्ण
		err = nft_chain_parse_hook(ctx->net, nla, &hook, ctx->family,
					   extack, false);
		अगर (err < 0)
			वापस err;

		basechain = nft_base_chain(chain);
		अगर (basechain->type != hook.type) अणु
			nft_chain_release_hook(&hook);
			NL_SET_BAD_ATTR(extack, attr);
			वापस -EEXIST;
		पूर्ण

		अगर (nft_base_chain_netdev(ctx->family, hook.num)) अणु
			अगर (!nft_hook_list_equal(&basechain->hook_list,
						 &hook.list)) अणु
				nft_chain_release_hook(&hook);
				NL_SET_BAD_ATTR(extack, attr);
				वापस -EEXIST;
			पूर्ण
		पूर्ण अन्यथा अणु
			ops = &basechain->ops;
			अगर (ops->hooknum != hook.num ||
			    ops->priority != hook.priority) अणु
				nft_chain_release_hook(&hook);
				NL_SET_BAD_ATTR(extack, attr);
				वापस -EEXIST;
			पूर्ण
		पूर्ण
		nft_chain_release_hook(&hook);
	पूर्ण

	अगर (nla[NFTA_CHAIN_HANDLE] &&
	    nla[NFTA_CHAIN_NAME]) अणु
		काष्ठा nft_chain *chain2;

		chain2 = nft_chain_lookup(ctx->net, table,
					  nla[NFTA_CHAIN_NAME], genmask);
		अगर (!IS_ERR(chain2)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_NAME]);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	अगर (nla[NFTA_CHAIN_COUNTERS]) अणु
		अगर (!nft_is_base_chain(chain))
			वापस -EOPNOTSUPP;

		stats = nft_stats_alloc(nla[NFTA_CHAIN_COUNTERS]);
		अगर (IS_ERR(stats))
			वापस PTR_ERR(stats);
	पूर्ण

	err = -ENOMEM;
	trans = nft_trans_alloc(ctx, NFT_MSG_NEWCHAIN,
				माप(काष्ठा nft_trans_chain));
	अगर (trans == शून्य)
		जाओ err;

	nft_trans_chain_stats(trans) = stats;
	nft_trans_chain_update(trans) = true;

	अगर (nla[NFTA_CHAIN_POLICY])
		nft_trans_chain_policy(trans) = policy;
	अन्यथा
		nft_trans_chain_policy(trans) = -1;

	अगर (nla[NFTA_CHAIN_HANDLE] &&
	    nla[NFTA_CHAIN_NAME]) अणु
		काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
		काष्ठा nft_trans *पंचांगp;
		अक्षर *name;

		err = -ENOMEM;
		name = nla_strdup(nla[NFTA_CHAIN_NAME], GFP_KERNEL);
		अगर (!name)
			जाओ err;

		err = -EEXIST;
		list_क्रम_each_entry(पंचांगp, &nft_net->commit_list, list) अणु
			अगर (पंचांगp->msg_type == NFT_MSG_NEWCHAIN &&
			    पंचांगp->ctx.table == table &&
			    nft_trans_chain_update(पंचांगp) &&
			    nft_trans_chain_name(पंचांगp) &&
			    म_भेद(name, nft_trans_chain_name(पंचांगp)) == 0) अणु
				NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_NAME]);
				kमुक्त(name);
				जाओ err;
			पूर्ण
		पूर्ण

		nft_trans_chain_name(trans) = name;
	पूर्ण
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;
err:
	मुक्त_percpu(stats);
	kमुक्त(trans);
	वापस err;
पूर्ण

अटल काष्ठा nft_chain *nft_chain_lookup_byid(स्थिर काष्ठा net *net,
					       स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	u32 id = ntohl(nla_get_be32(nla));
	काष्ठा nft_trans *trans;

	list_क्रम_each_entry(trans, &nft_net->commit_list, list) अणु
		काष्ठा nft_chain *chain = trans->ctx.chain;

		अगर (trans->msg_type == NFT_MSG_NEWCHAIN &&
		    id == nft_trans_chain_id(trans))
			वापस chain;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक nf_tables_newchain(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(info->net);
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_chain *chain = शून्य;
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_table *table;
	u8 policy = NF_ACCEPT;
	काष्ठा nft_ctx ctx;
	u64 handle = 0;
	u32 flags = 0;

	lockdep_निश्चित_held(&nft_net->commit_mutex);

	table = nft_table_lookup(net, nla[NFTA_CHAIN_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	chain = शून्य;
	attr = nla[NFTA_CHAIN_NAME];

	अगर (nla[NFTA_CHAIN_HANDLE]) अणु
		handle = be64_to_cpu(nla_get_be64(nla[NFTA_CHAIN_HANDLE]));
		chain = nft_chain_lookup_byhandle(table, handle, genmask);
		अगर (IS_ERR(chain)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_HANDLE]);
			वापस PTR_ERR(chain);
		पूर्ण
		attr = nla[NFTA_CHAIN_HANDLE];
	पूर्ण अन्यथा अगर (nla[NFTA_CHAIN_NAME]) अणु
		chain = nft_chain_lookup(net, table, attr, genmask);
		अगर (IS_ERR(chain)) अणु
			अगर (PTR_ERR(chain) != -ENOENT) अणु
				NL_SET_BAD_ATTR(extack, attr);
				वापस PTR_ERR(chain);
			पूर्ण
			chain = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (!nla[NFTA_CHAIN_ID]) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (nla[NFTA_CHAIN_POLICY]) अणु
		अगर (chain != शून्य &&
		    !nft_is_base_chain(chain)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_POLICY]);
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (chain == शून्य &&
		    nla[NFTA_CHAIN_HOOK] == शून्य) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_POLICY]);
			वापस -EOPNOTSUPP;
		पूर्ण

		policy = ntohl(nla_get_be32(nla[NFTA_CHAIN_POLICY]));
		चयन (policy) अणु
		हाल NF_DROP:
		हाल NF_ACCEPT:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (nla[NFTA_CHAIN_FLAGS])
		flags = ntohl(nla_get_be32(nla[NFTA_CHAIN_FLAGS]));
	अन्यथा अगर (chain)
		flags = chain->flags;

	अगर (flags & ~NFT_CHAIN_FLAGS)
		वापस -EOPNOTSUPP;

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, chain, nla);

	अगर (chain != शून्य) अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL) अणु
			NL_SET_BAD_ATTR(extack, attr);
			वापस -EEXIST;
		पूर्ण
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE)
			वापस -EOPNOTSUPP;

		flags |= chain->flags & NFT_CHAIN_BASE;
		वापस nf_tables_updchain(&ctx, genmask, policy, flags, attr,
					  extack);
	पूर्ण

	वापस nf_tables_addchain(&ctx, family, genmask, policy, flags, extack);
पूर्ण

अटल पूर्णांक nf_tables_delchain(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_table *table;
	काष्ठा nft_chain *chain;
	काष्ठा nft_rule *rule;
	काष्ठा nft_ctx ctx;
	u64 handle;
	u32 use;
	पूर्णांक err;

	table = nft_table_lookup(net, nla[NFTA_CHAIN_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	अगर (nla[NFTA_CHAIN_HANDLE]) अणु
		attr = nla[NFTA_CHAIN_HANDLE];
		handle = be64_to_cpu(nla_get_be64(attr));
		chain = nft_chain_lookup_byhandle(table, handle, genmask);
	पूर्ण अन्यथा अणु
		attr = nla[NFTA_CHAIN_NAME];
		chain = nft_chain_lookup(net, table, attr, genmask);
	पूर्ण
	अगर (IS_ERR(chain)) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस PTR_ERR(chain);
	पूर्ण

	अगर (info->nlh->nlmsg_flags & NLM_F_NONREC &&
	    chain->use > 0)
		वापस -EBUSY;

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, chain, nla);

	use = chain->use;
	list_क्रम_each_entry(rule, &chain->rules, list) अणु
		अगर (!nft_is_active_next(net, rule))
			जारी;
		use--;

		err = nft_delrule(&ctx, rule);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* There are rules and elements that are still holding references to us,
	 * we cannot करो a recursive removal in this हाल.
	 */
	अगर (use > 0) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस -EBUSY;
	पूर्ण

	वापस nft_delchain(&ctx);
पूर्ण

/*
 * Expressions
 */

/**
 *	nft_रेजिस्टर_expr - रेजिस्टर nf_tables expr type
 *	@type: expr type
 *
 *	Registers the expr type क्रम use with nf_tables. Returns zero on
 *	success or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक nft_रेजिस्टर_expr(काष्ठा nft_expr_type *type)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	अगर (type->family == NFPROTO_UNSPEC)
		list_add_tail_rcu(&type->list, &nf_tables_expressions);
	अन्यथा
		list_add_rcu(&type->list, &nf_tables_expressions);
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_रेजिस्टर_expr);

/**
 *	nft_unरेजिस्टर_expr - unरेजिस्टर nf_tables expr type
 *	@type: expr type
 *
 * 	Unरेजिस्टरs the expr typeक्रम use with nf_tables.
 */
व्योम nft_unरेजिस्टर_expr(काष्ठा nft_expr_type *type)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	list_del_rcu(&type->list);
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
पूर्ण
EXPORT_SYMBOL_GPL(nft_unरेजिस्टर_expr);

अटल स्थिर काष्ठा nft_expr_type *__nft_expr_type_get(u8 family,
						       काष्ठा nlattr *nla)
अणु
	स्थिर काष्ठा nft_expr_type *type, *candidate = शून्य;

	list_क्रम_each_entry(type, &nf_tables_expressions, list) अणु
		अगर (!nla_म_भेद(nla, type->name)) अणु
			अगर (!type->family && !candidate)
				candidate = type;
			अन्यथा अगर (type->family == family)
				candidate = type;
		पूर्ण
	पूर्ण
	वापस candidate;
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल पूर्णांक nft_expr_type_request_module(काष्ठा net *net, u8 family,
					काष्ठा nlattr *nla)
अणु
	अगर (nft_request_module(net, "nft-expr-%u-%.*s", family,
			       nla_len(nla), (अक्षर *)nla_data(nla)) == -EAGAIN)
		वापस -EAGAIN;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा nft_expr_type *nft_expr_type_get(काष्ठा net *net,
						     u8 family,
						     काष्ठा nlattr *nla)
अणु
	स्थिर काष्ठा nft_expr_type *type;

	अगर (nla == शून्य)
		वापस ERR_PTR(-EINVAL);

	type = __nft_expr_type_get(family, nla);
	अगर (type != शून्य && try_module_get(type->owner))
		वापस type;

	lockdep_nfnl_nft_mutex_not_held();
#अगर_घोषित CONFIG_MODULES
	अगर (type == शून्य) अणु
		अगर (nft_expr_type_request_module(net, family, nla) == -EAGAIN)
			वापस ERR_PTR(-EAGAIN);

		अगर (nft_request_module(net, "nft-expr-%.*s",
				       nla_len(nla),
				       (अक्षर *)nla_data(nla)) == -EAGAIN)
			वापस ERR_PTR(-EAGAIN);
	पूर्ण
#पूर्ण_अगर
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_expr_policy[NFTA_EXPR_MAX + 1] = अणु
	[NFTA_EXPR_NAME]	= अणु .type = NLA_STRING,
				    .len = NFT_MODULE_AUTOLOAD_LIMIT पूर्ण,
	[NFTA_EXPR_DATA]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nf_tables_fill_expr_info(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nft_expr *expr)
अणु
	अगर (nla_put_string(skb, NFTA_EXPR_NAME, expr->ops->type->name))
		जाओ nla_put_failure;

	अगर (expr->ops->dump) अणु
		काष्ठा nlattr *data = nla_nest_start_noflag(skb,
							    NFTA_EXPR_DATA);
		अगर (data == शून्य)
			जाओ nla_put_failure;
		अगर (expr->ops->dump(skb, expr) < 0)
			जाओ nla_put_failure;
		nla_nest_end(skb, data);
	पूर्ण

	वापस skb->len;

nla_put_failure:
	वापस -1;
पूर्ण;

पूर्णांक nft_expr_dump(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक attr,
		  स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, attr);
	अगर (!nest)
		जाओ nla_put_failure;
	अगर (nf_tables_fill_expr_info(skb, expr) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

काष्ठा nft_expr_info अणु
	स्थिर काष्ठा nft_expr_ops	*ops;
	स्थिर काष्ठा nlattr		*attr;
	काष्ठा nlattr			*tb[NFT_EXPR_MAXATTR + 1];
पूर्ण;

अटल पूर्णांक nf_tables_expr_parse(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nlattr *nla,
				काष्ठा nft_expr_info *info)
अणु
	स्थिर काष्ठा nft_expr_type *type;
	स्थिर काष्ठा nft_expr_ops *ops;
	काष्ठा nlattr *tb[NFTA_EXPR_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_EXPR_MAX, nla,
					  nft_expr_policy, शून्य);
	अगर (err < 0)
		वापस err;

	type = nft_expr_type_get(ctx->net, ctx->family, tb[NFTA_EXPR_NAME]);
	अगर (IS_ERR(type))
		वापस PTR_ERR(type);

	अगर (tb[NFTA_EXPR_DATA]) अणु
		err = nla_parse_nested_deprecated(info->tb, type->maxattr,
						  tb[NFTA_EXPR_DATA],
						  type->policy, शून्य);
		अगर (err < 0)
			जाओ err1;
	पूर्ण अन्यथा
		स_रखो(info->tb, 0, माप(info->tb[0]) * (type->maxattr + 1));

	अगर (type->select_ops != शून्य) अणु
		ops = type->select_ops(ctx,
				       (स्थिर काष्ठा nlattr * स्थिर *)info->tb);
		अगर (IS_ERR(ops)) अणु
			err = PTR_ERR(ops);
#अगर_घोषित CONFIG_MODULES
			अगर (err == -EAGAIN)
				अगर (nft_expr_type_request_module(ctx->net,
								 ctx->family,
								 tb[NFTA_EXPR_NAME]) != -EAGAIN)
					err = -ENOENT;
#पूर्ण_अगर
			जाओ err1;
		पूर्ण
	पूर्ण अन्यथा
		ops = type->ops;

	info->attr = nla;
	info->ops = ops;

	वापस 0;

err1:
	module_put(type->owner);
	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_newexpr(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nft_expr_info *expr_info,
			     काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_expr_ops *ops = expr_info->ops;
	पूर्णांक err;

	expr->ops = ops;
	अगर (ops->init) अणु
		err = ops->init(ctx, expr, (स्थिर काष्ठा nlattr **)expr_info->tb);
		अगर (err < 0)
			जाओ err1;
	पूर्ण

	वापस 0;
err1:
	expr->ops = शून्य;
	वापस err;
पूर्ण

अटल व्योम nf_tables_expr_destroy(स्थिर काष्ठा nft_ctx *ctx,
				   काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_expr_type *type = expr->ops->type;

	अगर (expr->ops->destroy)
		expr->ops->destroy(ctx, expr);
	module_put(type->owner);
पूर्ण

अटल काष्ठा nft_expr *nft_expr_init(स्थिर काष्ठा nft_ctx *ctx,
				      स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nft_expr_info expr_info;
	काष्ठा nft_expr *expr;
	काष्ठा module *owner;
	पूर्णांक err;

	err = nf_tables_expr_parse(ctx, nla, &expr_info);
	अगर (err < 0)
		जाओ err1;

	err = -ENOMEM;
	expr = kzalloc(expr_info.ops->size, GFP_KERNEL);
	अगर (expr == शून्य)
		जाओ err2;

	err = nf_tables_newexpr(ctx, &expr_info, expr);
	अगर (err < 0)
		जाओ err3;

	वापस expr;
err3:
	kमुक्त(expr);
err2:
	owner = expr_info.ops->type->owner;
	अगर (expr_info.ops->type->release_ops)
		expr_info.ops->type->release_ops(expr_info.ops);

	module_put(owner);
err1:
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक nft_expr_clone(काष्ठा nft_expr *dst, काष्ठा nft_expr *src)
अणु
	पूर्णांक err;

	अगर (src->ops->clone) अणु
		dst->ops = src->ops;
		err = src->ops->clone(dst, src);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		स_नकल(dst, src, src->ops->size);
	पूर्ण

	__module_get(src->ops->type->owner);

	वापस 0;
पूर्ण

व्योम nft_expr_destroy(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_expr *expr)
अणु
	nf_tables_expr_destroy(ctx, expr);
	kमुक्त(expr);
पूर्ण

/*
 * Rules
 */

अटल काष्ठा nft_rule *__nft_rule_lookup(स्थिर काष्ठा nft_chain *chain,
					  u64 handle)
अणु
	काष्ठा nft_rule *rule;

	// FIXME: this sucks
	list_क्रम_each_entry_rcu(rule, &chain->rules, list) अणु
		अगर (handle == rule->handle)
			वापस rule;
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा nft_rule *nft_rule_lookup(स्थिर काष्ठा nft_chain *chain,
					स्थिर काष्ठा nlattr *nla)
अणु
	अगर (nla == शून्य)
		वापस ERR_PTR(-EINVAL);

	वापस __nft_rule_lookup(chain, be64_to_cpu(nla_get_be64(nla)));
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_rule_policy[NFTA_RULE_MAX + 1] = अणु
	[NFTA_RULE_TABLE]	= अणु .type = NLA_STRING,
				    .len = NFT_TABLE_MAXNAMELEN - 1 पूर्ण,
	[NFTA_RULE_CHAIN]	= अणु .type = NLA_STRING,
				    .len = NFT_CHAIN_MAXNAMELEN - 1 पूर्ण,
	[NFTA_RULE_HANDLE]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_RULE_EXPRESSIONS]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_RULE_COMPAT]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_RULE_POSITION]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_RULE_USERDATA]	= अणु .type = NLA_BINARY,
				    .len = NFT_USERDATA_MAXLEN पूर्ण,
	[NFTA_RULE_ID]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_RULE_POSITION_ID]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_RULE_CHAIN_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nf_tables_fill_rule_info(काष्ठा sk_buff *skb, काष्ठा net *net,
				    u32 portid, u32 seq, पूर्णांक event,
				    u32 flags, पूर्णांक family,
				    स्थिर काष्ठा nft_table *table,
				    स्थिर काष्ठा nft_chain *chain,
				    स्थिर काष्ठा nft_rule *rule,
				    स्थिर काष्ठा nft_rule *prule)
अणु
	काष्ठा nlmsghdr *nlh;
	स्थिर काष्ठा nft_expr *expr, *next;
	काष्ठा nlattr *list;
	u16 type = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);

	nlh = nfnl_msg_put(skb, portid, seq, type, flags, family, NFNETLINK_V0,
			   nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_RULE_TABLE, table->name))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, NFTA_RULE_CHAIN, chain->name))
		जाओ nla_put_failure;
	अगर (nla_put_be64(skb, NFTA_RULE_HANDLE, cpu_to_be64(rule->handle),
			 NFTA_RULE_PAD))
		जाओ nla_put_failure;

	अगर (event != NFT_MSG_DELRULE && prule) अणु
		अगर (nla_put_be64(skb, NFTA_RULE_POSITION,
				 cpu_to_be64(prule->handle),
				 NFTA_RULE_PAD))
			जाओ nla_put_failure;
	पूर्ण

	अगर (chain->flags & NFT_CHAIN_HW_OFFLOAD)
		nft_flow_rule_stats(chain, rule);

	list = nla_nest_start_noflag(skb, NFTA_RULE_EXPRESSIONS);
	अगर (list == शून्य)
		जाओ nla_put_failure;
	nft_rule_क्रम_each_expr(expr, next, rule) अणु
		अगर (nft_expr_dump(skb, NFTA_LIST_ELEM, expr) < 0)
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, list);

	अगर (rule->udata) अणु
		काष्ठा nft_userdata *udata = nft_userdata(rule);
		अगर (nla_put(skb, NFTA_RULE_USERDATA, udata->len + 1,
			    udata->data) < 0)
			जाओ nla_put_failure;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

अटल व्योम nf_tables_rule_notअगरy(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nft_rule *rule, पूर्णांक event)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (!ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_rule_info(skb, ctx->net, ctx->portid, ctx->seq,
				       event, 0, ctx->family, ctx->table,
				       ctx->chain, rule, शून्य);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_notअगरy_enqueue(skb, ctx->report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(ctx->net, ctx->portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण

काष्ठा nft_rule_dump_ctx अणु
	अक्षर *table;
	अक्षर *chain;
पूर्ण;

अटल पूर्णांक __nf_tables_dump_rules(काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक *idx,
				  काष्ठा netlink_callback *cb,
				  स्थिर काष्ठा nft_table *table,
				  स्थिर काष्ठा nft_chain *chain)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	स्थिर काष्ठा nft_rule *rule, *prule;
	अचिन्हित पूर्णांक s_idx = cb->args[0];

	prule = शून्य;
	list_क्रम_each_entry_rcu(rule, &chain->rules, list) अणु
		अगर (!nft_is_active(net, rule))
			जाओ cont_skip;
		अगर (*idx < s_idx)
			जाओ cont;
		अगर (*idx > s_idx) अणु
			स_रखो(&cb->args[1], 0,
					माप(cb->args) - माप(cb->args[0]));
		पूर्ण
		अगर (nf_tables_fill_rule_info(skb, net, NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq,
					NFT_MSG_NEWRULE,
					NLM_F_MULTI | NLM_F_APPEND,
					table->family,
					table, chain, rule, prule) < 0)
			वापस 1;

		nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
		prule = rule;
cont_skip:
		(*idx)++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_dump_rules(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	स्थिर काष्ठा nft_rule_dump_ctx *ctx = cb->data;
	काष्ठा nft_table *table;
	स्थिर काष्ठा nft_chain *chain;
	अचिन्हित पूर्णांक idx = 0;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nftables_pernet *nft_net;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	cb->seq = nft_net->base_seq;

	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (family != NFPROTO_UNSPEC && family != table->family)
			जारी;

		अगर (ctx && ctx->table && म_भेद(ctx->table, table->name) != 0)
			जारी;

		अगर (ctx && ctx->table && ctx->chain) अणु
			काष्ठा rhlist_head *list, *पंचांगp;

			list = rhltable_lookup(&table->chains_ht, ctx->chain,
					       nft_chain_ht_params);
			अगर (!list)
				जाओ करोne;

			rhl_क्रम_each_entry_rcu(chain, पंचांगp, list, rhlhead) अणु
				अगर (!nft_is_active(net, chain))
					जारी;
				__nf_tables_dump_rules(skb, &idx,
						       cb, table, chain);
				अवरोध;
			पूर्ण
			जाओ करोne;
		पूर्ण

		list_क्रम_each_entry_rcu(chain, &table->chains, list) अणु
			अगर (__nf_tables_dump_rules(skb, &idx, cb, table, chain))
				जाओ करोne;
		पूर्ण

		अगर (ctx && ctx->table)
			अवरोध;
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();

	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nf_tables_dump_rules_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = cb->data;
	काष्ठा nft_rule_dump_ctx *ctx = शून्य;

	अगर (nla[NFTA_RULE_TABLE] || nla[NFTA_RULE_CHAIN]) अणु
		ctx = kzalloc(माप(*ctx), GFP_ATOMIC);
		अगर (!ctx)
			वापस -ENOMEM;

		अगर (nla[NFTA_RULE_TABLE]) अणु
			ctx->table = nla_strdup(nla[NFTA_RULE_TABLE],
							GFP_ATOMIC);
			अगर (!ctx->table) अणु
				kमुक्त(ctx);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		अगर (nla[NFTA_RULE_CHAIN]) अणु
			ctx->chain = nla_strdup(nla[NFTA_RULE_CHAIN],
						GFP_ATOMIC);
			अगर (!ctx->chain) अणु
				kमुक्त(ctx->table);
				kमुक्त(ctx);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	cb->data = ctx;
	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_dump_rules_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nft_rule_dump_ctx *ctx = cb->data;

	अगर (ctx) अणु
		kमुक्त(ctx->table);
		kमुक्त(ctx->chain);
		kमुक्त(ctx);
	पूर्ण
	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_getrule(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	स्थिर काष्ठा nft_chain *chain;
	स्थिर काष्ठा nft_rule *rule;
	काष्ठा net *net = info->net;
	काष्ठा nft_table *table;
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start= nf_tables_dump_rules_start,
			.dump = nf_tables_dump_rules,
			.करोne = nf_tables_dump_rules_करोne,
			.module = THIS_MODULE,
			.data = (व्योम *)nla,
		पूर्ण;

		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	table = nft_table_lookup(net, nla[NFTA_RULE_TABLE], family, genmask, 0);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	chain = nft_chain_lookup(net, table, nla[NFTA_RULE_CHAIN], genmask);
	अगर (IS_ERR(chain)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_CHAIN]);
		वापस PTR_ERR(chain);
	पूर्ण

	rule = nft_rule_lookup(chain, nla[NFTA_RULE_HANDLE]);
	अगर (IS_ERR(rule)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_HANDLE]);
		वापस PTR_ERR(rule);
	पूर्ण

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb2)
		वापस -ENOMEM;

	err = nf_tables_fill_rule_info(skb2, net, NETLINK_CB(skb).portid,
				       info->nlh->nlmsg_seq, NFT_MSG_NEWRULE, 0,
				       family, table, chain, rule, शून्य);
	अगर (err < 0)
		जाओ err_fill_rule_info;

	वापस nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_rule_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल व्योम nf_tables_rule_destroy(स्थिर काष्ठा nft_ctx *ctx,
				   काष्ठा nft_rule *rule)
अणु
	काष्ठा nft_expr *expr, *next;

	/*
	 * Careful: some expressions might not be initialized in हाल this
	 * is called on error from nf_tables_newrule().
	 */
	expr = nft_expr_first(rule);
	जबतक (nft_expr_more(rule, expr)) अणु
		next = nft_expr_next(expr);
		nf_tables_expr_destroy(ctx, expr);
		expr = next;
	पूर्ण
	kमुक्त(rule);
पूर्ण

व्योम nf_tables_rule_release(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_rule *rule)
अणु
	nft_rule_expr_deactivate(ctx, rule, NFT_TRANS_RELEASE);
	nf_tables_rule_destroy(ctx, rule);
पूर्ण

पूर्णांक nft_chain_validate(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_expr *expr, *last;
	स्थिर काष्ठा nft_data *data;
	काष्ठा nft_rule *rule;
	पूर्णांक err;

	अगर (ctx->level == NFT_JUMP_STACK_SIZE)
		वापस -EMLINK;

	list_क्रम_each_entry(rule, &chain->rules, list) अणु
		अगर (!nft_is_active_next(ctx->net, rule))
			जारी;

		nft_rule_क्रम_each_expr(expr, last, rule) अणु
			अगर (!expr->ops->validate)
				जारी;

			err = expr->ops->validate(ctx, expr, &data);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_chain_validate);

अटल पूर्णांक nft_table_validate(काष्ठा net *net, स्थिर काष्ठा nft_table *table)
अणु
	काष्ठा nft_chain *chain;
	काष्ठा nft_ctx ctx = अणु
		.net	= net,
		.family	= table->family,
	पूर्ण;
	पूर्णांक err;

	list_क्रम_each_entry(chain, &table->chains, list) अणु
		अगर (!nft_is_base_chain(chain))
			जारी;

		ctx.chain = chain;
		err = nft_chain_validate(&ctx, chain);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nft_rule *nft_rule_lookup_byid(स्थिर काष्ठा net *net,
					     स्थिर काष्ठा nlattr *nla);

#घोषणा NFT_RULE_MAXEXPRS	128

अटल पूर्णांक nf_tables_newrule(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(info->net);
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	अचिन्हित पूर्णांक size, i, n, ulen = 0, usize = 0;
	u8 genmask = nft_genmask_next(info->net);
	काष्ठा nft_rule *rule, *old_rule = शून्य;
	काष्ठा nft_expr_info *expr_info = शून्य;
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा net *net = info->net;
	काष्ठा nft_flow_rule *flow;
	काष्ठा nft_userdata *udata;
	काष्ठा nft_table *table;
	काष्ठा nft_chain *chain;
	काष्ठा nft_trans *trans;
	u64 handle, pos_handle;
	काष्ठा nft_expr *expr;
	काष्ठा nft_ctx ctx;
	काष्ठा nlattr *पंचांगp;
	पूर्णांक err, rem;

	lockdep_निश्चित_held(&nft_net->commit_mutex);

	table = nft_table_lookup(net, nla[NFTA_RULE_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	अगर (nla[NFTA_RULE_CHAIN]) अणु
		chain = nft_chain_lookup(net, table, nla[NFTA_RULE_CHAIN],
					 genmask);
		अगर (IS_ERR(chain)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_CHAIN]);
			वापस PTR_ERR(chain);
		पूर्ण
		अगर (nft_chain_is_bound(chain))
			वापस -EOPNOTSUPP;

	पूर्ण अन्यथा अगर (nla[NFTA_RULE_CHAIN_ID]) अणु
		chain = nft_chain_lookup_byid(net, nla[NFTA_RULE_CHAIN_ID]);
		अगर (IS_ERR(chain)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_CHAIN_ID]);
			वापस PTR_ERR(chain);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (nla[NFTA_RULE_HANDLE]) अणु
		handle = be64_to_cpu(nla_get_be64(nla[NFTA_RULE_HANDLE]));
		rule = __nft_rule_lookup(chain, handle);
		अगर (IS_ERR(rule)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_HANDLE]);
			वापस PTR_ERR(rule);
		पूर्ण

		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_HANDLE]);
			वापस -EEXIST;
		पूर्ण
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE)
			old_rule = rule;
		अन्यथा
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		अगर (!(info->nlh->nlmsg_flags & NLM_F_CREATE) ||
		    info->nlh->nlmsg_flags & NLM_F_REPLACE)
			वापस -EINVAL;
		handle = nf_tables_alloc_handle(table);

		अगर (chain->use == अच_पूर्णांक_उच्च)
			वापस -EOVERFLOW;

		अगर (nla[NFTA_RULE_POSITION]) अणु
			pos_handle = be64_to_cpu(nla_get_be64(nla[NFTA_RULE_POSITION]));
			old_rule = __nft_rule_lookup(chain, pos_handle);
			अगर (IS_ERR(old_rule)) अणु
				NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_POSITION]);
				वापस PTR_ERR(old_rule);
			पूर्ण
		पूर्ण अन्यथा अगर (nla[NFTA_RULE_POSITION_ID]) अणु
			old_rule = nft_rule_lookup_byid(net, nla[NFTA_RULE_POSITION_ID]);
			अगर (IS_ERR(old_rule)) अणु
				NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_POSITION_ID]);
				वापस PTR_ERR(old_rule);
			पूर्ण
		पूर्ण
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, chain, nla);

	n = 0;
	size = 0;
	अगर (nla[NFTA_RULE_EXPRESSIONS]) अणु
		expr_info = kvदो_स्मृति_array(NFT_RULE_MAXEXPRS,
					   माप(काष्ठा nft_expr_info),
					   GFP_KERNEL);
		अगर (!expr_info)
			वापस -ENOMEM;

		nla_क्रम_each_nested(पंचांगp, nla[NFTA_RULE_EXPRESSIONS], rem) अणु
			err = -EINVAL;
			अगर (nla_type(पंचांगp) != NFTA_LIST_ELEM)
				जाओ err1;
			अगर (n == NFT_RULE_MAXEXPRS)
				जाओ err1;
			err = nf_tables_expr_parse(&ctx, पंचांगp, &expr_info[n]);
			अगर (err < 0) अणु
				NL_SET_BAD_ATTR(extack, पंचांगp);
				जाओ err1;
			पूर्ण
			size += expr_info[n].ops->size;
			n++;
		पूर्ण
	पूर्ण
	/* Check क्रम overflow of dlen field */
	err = -EFBIG;
	अगर (size >= 1 << 12)
		जाओ err1;

	अगर (nla[NFTA_RULE_USERDATA]) अणु
		ulen = nla_len(nla[NFTA_RULE_USERDATA]);
		अगर (ulen > 0)
			usize = माप(काष्ठा nft_userdata) + ulen;
	पूर्ण

	err = -ENOMEM;
	rule = kzalloc(माप(*rule) + size + usize, GFP_KERNEL);
	अगर (rule == शून्य)
		जाओ err1;

	nft_activate_next(net, rule);

	rule->handle = handle;
	rule->dlen   = size;
	rule->udata  = ulen ? 1 : 0;

	अगर (ulen) अणु
		udata = nft_userdata(rule);
		udata->len = ulen - 1;
		nla_स_नकल(udata->data, nla[NFTA_RULE_USERDATA], ulen);
	पूर्ण

	expr = nft_expr_first(rule);
	क्रम (i = 0; i < n; i++) अणु
		err = nf_tables_newexpr(&ctx, &expr_info[i], expr);
		अगर (err < 0) अणु
			NL_SET_BAD_ATTR(extack, expr_info[i].attr);
			जाओ err2;
		पूर्ण

		अगर (expr_info[i].ops->validate)
			nft_validate_state_update(net, NFT_VALIDATE_NEED);

		expr_info[i].ops = शून्य;
		expr = nft_expr_next(expr);
	पूर्ण

	अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE) अणु
		trans = nft_trans_rule_add(&ctx, NFT_MSG_NEWRULE, rule);
		अगर (trans == शून्य) अणु
			err = -ENOMEM;
			जाओ err2;
		पूर्ण
		err = nft_delrule(&ctx, old_rule);
		अगर (err < 0) अणु
			nft_trans_destroy(trans);
			जाओ err2;
		पूर्ण

		list_add_tail_rcu(&rule->list, &old_rule->list);
	पूर्ण अन्यथा अणु
		trans = nft_trans_rule_add(&ctx, NFT_MSG_NEWRULE, rule);
		अगर (!trans) अणु
			err = -ENOMEM;
			जाओ err2;
		पूर्ण

		अगर (info->nlh->nlmsg_flags & NLM_F_APPEND) अणु
			अगर (old_rule)
				list_add_rcu(&rule->list, &old_rule->list);
			अन्यथा
				list_add_tail_rcu(&rule->list, &chain->rules);
		 पूर्ण अन्यथा अणु
			अगर (old_rule)
				list_add_tail_rcu(&rule->list, &old_rule->list);
			अन्यथा
				list_add_rcu(&rule->list, &chain->rules);
		पूर्ण
	पूर्ण
	kvमुक्त(expr_info);
	chain->use++;

	अगर (nft_net->validate_state == NFT_VALIDATE_DO)
		वापस nft_table_validate(net, table);

	अगर (chain->flags & NFT_CHAIN_HW_OFFLOAD) अणु
		flow = nft_flow_rule_create(net, rule);
		अगर (IS_ERR(flow))
			वापस PTR_ERR(flow);

		nft_trans_flow_rule(trans) = flow;
	पूर्ण

	वापस 0;
err2:
	nf_tables_rule_release(&ctx, rule);
err1:
	क्रम (i = 0; i < n; i++) अणु
		अगर (expr_info[i].ops) अणु
			module_put(expr_info[i].ops->type->owner);
			अगर (expr_info[i].ops->type->release_ops)
				expr_info[i].ops->type->release_ops(expr_info[i].ops);
		पूर्ण
	पूर्ण
	kvमुक्त(expr_info);

	वापस err;
पूर्ण

अटल काष्ठा nft_rule *nft_rule_lookup_byid(स्थिर काष्ठा net *net,
					     स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	u32 id = ntohl(nla_get_be32(nla));
	काष्ठा nft_trans *trans;

	list_क्रम_each_entry(trans, &nft_net->commit_list, list) अणु
		काष्ठा nft_rule *rule = nft_trans_rule(trans);

		अगर (trans->msg_type == NFT_MSG_NEWRULE &&
		    id == nft_trans_rule_id(trans))
			वापस rule;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक nf_tables_delrule(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	पूर्णांक family = nfmsg->nfgen_family, err = 0;
	u8 genmask = nft_genmask_next(info->net);
	काष्ठा nft_chain *chain = शून्य;
	काष्ठा net *net = info->net;
	काष्ठा nft_table *table;
	काष्ठा nft_rule *rule;
	काष्ठा nft_ctx ctx;

	table = nft_table_lookup(net, nla[NFTA_RULE_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	अगर (nla[NFTA_RULE_CHAIN]) अणु
		chain = nft_chain_lookup(net, table, nla[NFTA_RULE_CHAIN],
					 genmask);
		अगर (IS_ERR(chain)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_CHAIN]);
			वापस PTR_ERR(chain);
		पूर्ण
		अगर (nft_chain_is_bound(chain))
			वापस -EOPNOTSUPP;
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, chain, nla);

	अगर (chain) अणु
		अगर (nla[NFTA_RULE_HANDLE]) अणु
			rule = nft_rule_lookup(chain, nla[NFTA_RULE_HANDLE]);
			अगर (IS_ERR(rule)) अणु
				NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_HANDLE]);
				वापस PTR_ERR(rule);
			पूर्ण

			err = nft_delrule(&ctx, rule);
		पूर्ण अन्यथा अगर (nla[NFTA_RULE_ID]) अणु
			rule = nft_rule_lookup_byid(net, nla[NFTA_RULE_ID]);
			अगर (IS_ERR(rule)) अणु
				NL_SET_BAD_ATTR(extack, nla[NFTA_RULE_ID]);
				वापस PTR_ERR(rule);
			पूर्ण

			err = nft_delrule(&ctx, rule);
		पूर्ण अन्यथा अणु
			err = nft_delrule_by_chain(&ctx);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(chain, &table->chains, list) अणु
			अगर (!nft_is_active_next(net, chain))
				जारी;

			ctx.chain = chain;
			err = nft_delrule_by_chain(&ctx);
			अगर (err < 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/*
 * Sets
 */
अटल स्थिर काष्ठा nft_set_type *nft_set_types[] = अणु
	&nft_set_hash_fast_type,
	&nft_set_hash_type,
	&nft_set_rhash_type,
	&nft_set_biपंचांगap_type,
	&nft_set_rbtree_type,
#अगर defined(CONFIG_X86_64) && !defined(CONFIG_UML)
	&nft_set_pipapo_avx2_type,
#पूर्ण_अगर
	&nft_set_pipapo_type,
पूर्ण;

#घोषणा NFT_SET_FEATURES	(NFT_SET_INTERVAL | NFT_SET_MAP | \
				 NFT_SET_TIMEOUT | NFT_SET_OBJECT | \
				 NFT_SET_EVAL)

अटल bool nft_set_ops_candidate(स्थिर काष्ठा nft_set_type *type, u32 flags)
अणु
	वापस (flags & type->features) == (flags & NFT_SET_FEATURES);
पूर्ण

/*
 * Select a set implementation based on the data अक्षरacteristics and the
 * given policy. The total memory use might not be known अगर no size is
 * given, in that हाल the amount of memory per element is used.
 */
अटल स्थिर काष्ठा nft_set_ops *
nft_select_set_ops(स्थिर काष्ठा nft_ctx *ctx,
		   स्थिर काष्ठा nlattr * स्थिर nla[],
		   स्थिर काष्ठा nft_set_desc *desc,
		   क्रमागत nft_set_policies policy)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
	स्थिर काष्ठा nft_set_ops *ops, *bops;
	काष्ठा nft_set_estimate est, best;
	स्थिर काष्ठा nft_set_type *type;
	u32 flags = 0;
	पूर्णांक i;

	lockdep_निश्चित_held(&nft_net->commit_mutex);
	lockdep_nfnl_nft_mutex_not_held();

	अगर (nla[NFTA_SET_FLAGS] != शून्य)
		flags = ntohl(nla_get_be32(nla[NFTA_SET_FLAGS]));

	bops	    = शून्य;
	best.size   = ~0;
	best.lookup = ~0;
	best.space  = ~0;

	क्रम (i = 0; i < ARRAY_SIZE(nft_set_types); i++) अणु
		type = nft_set_types[i];
		ops = &type->ops;

		अगर (!nft_set_ops_candidate(type, flags))
			जारी;
		अगर (!ops->estimate(desc, flags, &est))
			जारी;

		चयन (policy) अणु
		हाल NFT_SET_POL_PERFORMANCE:
			अगर (est.lookup < best.lookup)
				अवरोध;
			अगर (est.lookup == best.lookup &&
			    est.space < best.space)
				अवरोध;
			जारी;
		हाल NFT_SET_POL_MEMORY:
			अगर (!desc->size) अणु
				अगर (est.space < best.space)
					अवरोध;
				अगर (est.space == best.space &&
				    est.lookup < best.lookup)
					अवरोध;
			पूर्ण अन्यथा अगर (est.size < best.size || !bops) अणु
				अवरोध;
			पूर्ण
			जारी;
		शेष:
			अवरोध;
		पूर्ण

		bops = ops;
		best = est;
	पूर्ण

	अगर (bops != शून्य)
		वापस bops;

	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_set_policy[NFTA_SET_MAX + 1] = अणु
	[NFTA_SET_TABLE]		= अणु .type = NLA_STRING,
					    .len = NFT_TABLE_MAXNAMELEN - 1 पूर्ण,
	[NFTA_SET_NAME]			= अणु .type = NLA_STRING,
					    .len = NFT_SET_MAXNAMELEN - 1 पूर्ण,
	[NFTA_SET_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_KEY_TYPE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_KEY_LEN]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_DATA_TYPE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_DATA_LEN]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_POLICY]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_DESC]			= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_ID]			= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_TIMEOUT]		= अणु .type = NLA_U64 पूर्ण,
	[NFTA_SET_GC_INTERVAL]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_USERDATA]		= अणु .type = NLA_BINARY,
					    .len  = NFT_USERDATA_MAXLEN पूर्ण,
	[NFTA_SET_OBJ_TYPE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_HANDLE]		= अणु .type = NLA_U64 पूर्ण,
	[NFTA_SET_EXPR]			= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_EXPRESSIONS]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_set_desc_policy[NFTA_SET_DESC_MAX + 1] = अणु
	[NFTA_SET_DESC_SIZE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_DESC_CONCAT]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_ctx_init_from_setattr(काष्ठा nft_ctx *ctx, काष्ठा net *net,
				     स्थिर काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nlmsghdr *nlh,
				     स्थिर काष्ठा nlattr * स्थिर nla[],
				     काष्ठा netlink_ext_ack *extack,
				     u8 genmask, u32 nlpid)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(nlh);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_table *table = शून्य;

	अगर (nla[NFTA_SET_TABLE] != शून्य) अणु
		table = nft_table_lookup(net, nla[NFTA_SET_TABLE], family,
					 genmask, nlpid);
		अगर (IS_ERR(table)) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_SET_TABLE]);
			वापस PTR_ERR(table);
		पूर्ण
	पूर्ण

	nft_ctx_init(ctx, net, skb, nlh, family, table, शून्य, nla);
	वापस 0;
पूर्ण

अटल काष्ठा nft_set *nft_set_lookup(स्थिर काष्ठा nft_table *table,
				      स्थिर काष्ठा nlattr *nla, u8 genmask)
अणु
	काष्ठा nft_set *set;

	अगर (nla == शून्य)
		वापस ERR_PTR(-EINVAL);

	list_क्रम_each_entry_rcu(set, &table->sets, list) अणु
		अगर (!nla_म_भेद(nla, set->name) &&
		    nft_active_genmask(set, genmask))
			वापस set;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा nft_set *nft_set_lookup_byhandle(स्थिर काष्ठा nft_table *table,
					       स्थिर काष्ठा nlattr *nla,
					       u8 genmask)
अणु
	काष्ठा nft_set *set;

	list_क्रम_each_entry(set, &table->sets, list) अणु
		अगर (be64_to_cpu(nla_get_be64(nla)) == set->handle &&
		    nft_active_genmask(set, genmask))
			वापस set;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा nft_set *nft_set_lookup_byid(स्थिर काष्ठा net *net,
					   स्थिर काष्ठा nlattr *nla, u8 genmask)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	u32 id = ntohl(nla_get_be32(nla));
	काष्ठा nft_trans *trans;

	list_क्रम_each_entry(trans, &nft_net->commit_list, list) अणु
		अगर (trans->msg_type == NFT_MSG_NEWSET) अणु
			काष्ठा nft_set *set = nft_trans_set(trans);

			अगर (id == nft_trans_set_id(trans) &&
			    nft_active_genmask(set, genmask))
				वापस set;
		पूर्ण
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

काष्ठा nft_set *nft_set_lookup_global(स्थिर काष्ठा net *net,
				      स्थिर काष्ठा nft_table *table,
				      स्थिर काष्ठा nlattr *nla_set_name,
				      स्थिर काष्ठा nlattr *nla_set_id,
				      u8 genmask)
अणु
	काष्ठा nft_set *set;

	set = nft_set_lookup(table, nla_set_name, genmask);
	अगर (IS_ERR(set)) अणु
		अगर (!nla_set_id)
			वापस set;

		set = nft_set_lookup_byid(net, nla_set_id, genmask);
	पूर्ण
	वापस set;
पूर्ण
EXPORT_SYMBOL_GPL(nft_set_lookup_global);

अटल पूर्णांक nf_tables_set_alloc_name(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
				    स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा nft_set *i;
	स्थिर अक्षर *p;
	अचिन्हित दीर्घ *inuse;
	अचिन्हित पूर्णांक n = 0, min = 0;

	p = म_अक्षर(name, '%');
	अगर (p != शून्य) अणु
		अगर (p[1] != 'd' || strchr(p + 2, '%'))
			वापस -EINVAL;

		inuse = (अचिन्हित दीर्घ *)get_zeroed_page(GFP_KERNEL);
		अगर (inuse == शून्य)
			वापस -ENOMEM;
cont:
		list_क्रम_each_entry(i, &ctx->table->sets, list) अणु
			पूर्णांक पंचांगp;

			अगर (!nft_is_active_next(ctx->net, set))
				जारी;
			अगर (!माला_पूछो(i->name, name, &पंचांगp))
				जारी;
			अगर (पंचांगp < min || पंचांगp >= min + BITS_PER_BYTE * PAGE_SIZE)
				जारी;

			set_bit(पंचांगp - min, inuse);
		पूर्ण

		n = find_first_zero_bit(inuse, BITS_PER_BYTE * PAGE_SIZE);
		अगर (n >= BITS_PER_BYTE * PAGE_SIZE) अणु
			min += BITS_PER_BYTE * PAGE_SIZE;
			स_रखो(inuse, 0, PAGE_SIZE);
			जाओ cont;
		पूर्ण
		मुक्त_page((अचिन्हित दीर्घ)inuse);
	पूर्ण

	set->name = kaप्र_लिखो(GFP_KERNEL, name, min + n);
	अगर (!set->name)
		वापस -ENOMEM;

	list_क्रम_each_entry(i, &ctx->table->sets, list) अणु
		अगर (!nft_is_active_next(ctx->net, i))
			जारी;
		अगर (!म_भेद(set->name, i->name)) अणु
			kमुक्त(set->name);
			set->name = शून्य;
			वापस -ENखाता;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक nf_msecs_to_jअगरfies64(स्थिर काष्ठा nlattr *nla, u64 *result)
अणु
	u64 ms = be64_to_cpu(nla_get_be64(nla));
	u64 max = (u64)(~((u64)0));

	max = भाग_u64(max, NSEC_PER_MSEC);
	अगर (ms >= max)
		वापस -दुस्फल;

	ms *= NSEC_PER_MSEC;
	*result = nsecs_to_jअगरfies64(ms);
	वापस 0;
पूर्ण

__be64 nf_jअगरfies64_to_msecs(u64 input)
अणु
	वापस cpu_to_be64(jअगरfies64_to_msecs(input));
पूर्ण

अटल पूर्णांक nf_tables_fill_set_concat(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nlattr *concat, *field;
	पूर्णांक i;

	concat = nla_nest_start_noflag(skb, NFTA_SET_DESC_CONCAT);
	अगर (!concat)
		वापस -ENOMEM;

	क्रम (i = 0; i < set->field_count; i++) अणु
		field = nla_nest_start_noflag(skb, NFTA_LIST_ELEM);
		अगर (!field)
			वापस -ENOMEM;

		अगर (nla_put_be32(skb, NFTA_SET_FIELD_LEN,
				 htonl(set->field_len[i])))
			वापस -ENOMEM;

		nla_nest_end(skb, field);
	पूर्ण

	nla_nest_end(skb, concat);

	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_fill_set(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_set *set, u16 event, u16 flags)
अणु
	काष्ठा nlmsghdr *nlh;
	u32 portid = ctx->portid;
	काष्ठा nlattr *nest;
	u32 seq = ctx->seq;
	पूर्णांक i;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, ctx->family,
			   NFNETLINK_V0, nft_base_seq(ctx->net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_SET_TABLE, ctx->table->name))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, NFTA_SET_NAME, set->name))
		जाओ nla_put_failure;
	अगर (nla_put_be64(skb, NFTA_SET_HANDLE, cpu_to_be64(set->handle),
			 NFTA_SET_PAD))
		जाओ nla_put_failure;
	अगर (set->flags != 0)
		अगर (nla_put_be32(skb, NFTA_SET_FLAGS, htonl(set->flags)))
			जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_SET_KEY_TYPE, htonl(set->ktype)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_SET_KEY_LEN, htonl(set->klen)))
		जाओ nla_put_failure;
	अगर (set->flags & NFT_SET_MAP) अणु
		अगर (nla_put_be32(skb, NFTA_SET_DATA_TYPE, htonl(set->dtype)))
			जाओ nla_put_failure;
		अगर (nla_put_be32(skb, NFTA_SET_DATA_LEN, htonl(set->dlen)))
			जाओ nla_put_failure;
	पूर्ण
	अगर (set->flags & NFT_SET_OBJECT &&
	    nla_put_be32(skb, NFTA_SET_OBJ_TYPE, htonl(set->objtype)))
		जाओ nla_put_failure;

	अगर (set->समयout &&
	    nla_put_be64(skb, NFTA_SET_TIMEOUT,
			 nf_jअगरfies64_to_msecs(set->समयout),
			 NFTA_SET_PAD))
		जाओ nla_put_failure;
	अगर (set->gc_पूर्णांक &&
	    nla_put_be32(skb, NFTA_SET_GC_INTERVAL, htonl(set->gc_पूर्णांक)))
		जाओ nla_put_failure;

	अगर (set->policy != NFT_SET_POL_PERFORMANCE) अणु
		अगर (nla_put_be32(skb, NFTA_SET_POLICY, htonl(set->policy)))
			जाओ nla_put_failure;
	पूर्ण

	अगर (set->udata &&
	    nla_put(skb, NFTA_SET_USERDATA, set->udlen, set->udata))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, NFTA_SET_DESC);
	अगर (!nest)
		जाओ nla_put_failure;
	अगर (set->size &&
	    nla_put_be32(skb, NFTA_SET_DESC_SIZE, htonl(set->size)))
		जाओ nla_put_failure;

	अगर (set->field_count > 1 &&
	    nf_tables_fill_set_concat(skb, set))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (set->num_exprs == 1) अणु
		nest = nla_nest_start_noflag(skb, NFTA_SET_EXPR);
		अगर (nf_tables_fill_expr_info(skb, set->exprs[0]) < 0)
			जाओ nla_put_failure;

		nla_nest_end(skb, nest);
	पूर्ण अन्यथा अगर (set->num_exprs > 1) अणु
		nest = nla_nest_start_noflag(skb, NFTA_SET_EXPRESSIONS);
		अगर (nest == शून्य)
			जाओ nla_put_failure;

		क्रम (i = 0; i < set->num_exprs; i++) अणु
			अगर (nft_expr_dump(skb, NFTA_LIST_ELEM,
					  set->exprs[i]) < 0)
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

अटल व्योम nf_tables_set_notअगरy(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_set *set, पूर्णांक event,
			         gfp_t gfp_flags)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
	काष्ठा sk_buff *skb;
	u32 portid = ctx->portid;
	पूर्णांक err;

	अगर (!ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, gfp_flags);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_set(skb, ctx, set, event, 0);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_notअगरy_enqueue(skb, ctx->report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(ctx->net, portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण

अटल पूर्णांक nf_tables_dump_sets(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nft_set *set;
	अचिन्हित पूर्णांक idx, s_idx = cb->args[0];
	काष्ठा nft_table *table, *cur_table = (काष्ठा nft_table *)cb->args[2];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nft_ctx *ctx = cb->data, ctx_set;
	काष्ठा nftables_pernet *nft_net;

	अगर (cb->args[1])
		वापस skb->len;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	cb->seq = nft_net->base_seq;

	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (ctx->family != NFPROTO_UNSPEC &&
		    ctx->family != table->family)
			जारी;

		अगर (ctx->table && ctx->table != table)
			जारी;

		अगर (cur_table) अणु
			अगर (cur_table != table)
				जारी;

			cur_table = शून्य;
		पूर्ण
		idx = 0;
		list_क्रम_each_entry_rcu(set, &table->sets, list) अणु
			अगर (idx < s_idx)
				जाओ cont;
			अगर (!nft_is_active(net, set))
				जाओ cont;

			ctx_set = *ctx;
			ctx_set.table = table;
			ctx_set.family = table->family;

			अगर (nf_tables_fill_set(skb, &ctx_set, set,
					       NFT_MSG_NEWSET,
					       NLM_F_MULTI) < 0) अणु
				cb->args[0] = idx;
				cb->args[2] = (अचिन्हित दीर्घ) table;
				जाओ करोne;
			पूर्ण
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
		अगर (s_idx)
			s_idx = 0;
	पूर्ण
	cb->args[1] = 1;
करोne:
	rcu_पढ़ो_unlock();
	वापस skb->len;
पूर्ण

अटल पूर्णांक nf_tables_dump_sets_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nft_ctx *ctx_dump = शून्य;

	ctx_dump = kmemdup(cb->data, माप(*ctx_dump), GFP_ATOMIC);
	अगर (ctx_dump == शून्य)
		वापस -ENOMEM;

	cb->data = ctx_dump;
	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_dump_sets_करोne(काष्ठा netlink_callback *cb)
अणु
	kमुक्त(cb->data);
	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_माला_लोet(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nft_set *set;
	काष्ठा sk_buff *skb2;
	काष्ठा nft_ctx ctx;
	पूर्णांक err;

	/* Verअगरy existence beक्रमe starting dump */
	err = nft_ctx_init_from_setattr(&ctx, net, skb, info->nlh, nla, extack,
					genmask, 0);
	अगर (err < 0)
		वापस err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = nf_tables_dump_sets_start,
			.dump = nf_tables_dump_sets,
			.करोne = nf_tables_dump_sets_करोne,
			.data = &ctx,
			.module = THIS_MODULE,
		पूर्ण;

		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	/* Only accept unspec with dump */
	अगर (nfmsg->nfgen_family == NFPROTO_UNSPEC)
		वापस -EAFNOSUPPORT;
	अगर (!nla[NFTA_SET_TABLE])
		वापस -EINVAL;

	set = nft_set_lookup(ctx.table, nla[NFTA_SET_NAME], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (skb2 == शून्य)
		वापस -ENOMEM;

	err = nf_tables_fill_set(skb2, &ctx, set, NFT_MSG_NEWSET, 0);
	अगर (err < 0)
		जाओ err_fill_set_info;

	वापस nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_set_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_concat_policy[NFTA_SET_FIELD_MAX + 1] = अणु
	[NFTA_SET_FIELD_LEN]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_set_desc_concat_parse(स्थिर काष्ठा nlattr *attr,
				     काष्ठा nft_set_desc *desc)
अणु
	काष्ठा nlattr *tb[NFTA_SET_FIELD_MAX + 1];
	u32 len;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_SET_FIELD_MAX, attr,
					  nft_concat_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_SET_FIELD_LEN])
		वापस -EINVAL;

	len = ntohl(nla_get_be32(tb[NFTA_SET_FIELD_LEN]));

	अगर (len * BITS_PER_BYTE / 32 > NFT_REG32_COUNT)
		वापस -E2BIG;

	desc->field_len[desc->field_count++] = len;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_set_desc_concat(काष्ठा nft_set_desc *desc,
			       स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nlattr *attr;
	पूर्णांक rem, err;

	nla_क्रम_each_nested(attr, nla, rem) अणु
		अगर (nla_type(attr) != NFTA_LIST_ELEM)
			वापस -EINVAL;

		err = nft_set_desc_concat_parse(attr, desc);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_set_desc_parse(काष्ठा nft_set_desc *desc,
				    स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nlattr *da[NFTA_SET_DESC_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(da, NFTA_SET_DESC_MAX, nla,
					  nft_set_desc_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (da[NFTA_SET_DESC_SIZE] != शून्य)
		desc->size = ntohl(nla_get_be32(da[NFTA_SET_DESC_SIZE]));
	अगर (da[NFTA_SET_DESC_CONCAT])
		err = nft_set_desc_concat(desc, da[NFTA_SET_DESC_CONCAT]);

	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_newset(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u32 ktype, dtype, flags, policy, gc_पूर्णांक, objtype;
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	स्थिर काष्ठा nft_set_ops *ops;
	काष्ठा nft_expr *expr = शून्य;
	काष्ठा net *net = info->net;
	काष्ठा nft_set_desc desc;
	काष्ठा nft_table *table;
	अचिन्हित अक्षर *udata;
	काष्ठा nft_set *set;
	काष्ठा nft_ctx ctx;
	माप_प्रकार alloc_size;
	u64 समयout;
	अक्षर *name;
	पूर्णांक err, i;
	u16 udlen;
	u64 size;

	अगर (nla[NFTA_SET_TABLE] == शून्य ||
	    nla[NFTA_SET_NAME] == शून्य ||
	    nla[NFTA_SET_KEY_LEN] == शून्य ||
	    nla[NFTA_SET_ID] == शून्य)
		वापस -EINVAL;

	स_रखो(&desc, 0, माप(desc));

	ktype = NFT_DATA_VALUE;
	अगर (nla[NFTA_SET_KEY_TYPE] != शून्य) अणु
		ktype = ntohl(nla_get_be32(nla[NFTA_SET_KEY_TYPE]));
		अगर ((ktype & NFT_DATA_RESERVED_MASK) == NFT_DATA_RESERVED_MASK)
			वापस -EINVAL;
	पूर्ण

	desc.klen = ntohl(nla_get_be32(nla[NFTA_SET_KEY_LEN]));
	अगर (desc.klen == 0 || desc.klen > NFT_DATA_VALUE_MAXLEN)
		वापस -EINVAL;

	flags = 0;
	अगर (nla[NFTA_SET_FLAGS] != शून्य) अणु
		flags = ntohl(nla_get_be32(nla[NFTA_SET_FLAGS]));
		अगर (flags & ~(NFT_SET_ANONYMOUS | NFT_SET_CONSTANT |
			      NFT_SET_INTERVAL | NFT_SET_TIMEOUT |
			      NFT_SET_MAP | NFT_SET_EVAL |
			      NFT_SET_OBJECT | NFT_SET_CONCAT | NFT_SET_EXPR))
			वापस -EOPNOTSUPP;
		/* Only one of these operations is supported */
		अगर ((flags & (NFT_SET_MAP | NFT_SET_OBJECT)) ==
			     (NFT_SET_MAP | NFT_SET_OBJECT))
			वापस -EOPNOTSUPP;
		अगर ((flags & (NFT_SET_EVAL | NFT_SET_OBJECT)) ==
			     (NFT_SET_EVAL | NFT_SET_OBJECT))
			वापस -EOPNOTSUPP;
	पूर्ण

	dtype = 0;
	अगर (nla[NFTA_SET_DATA_TYPE] != शून्य) अणु
		अगर (!(flags & NFT_SET_MAP))
			वापस -EINVAL;

		dtype = ntohl(nla_get_be32(nla[NFTA_SET_DATA_TYPE]));
		अगर ((dtype & NFT_DATA_RESERVED_MASK) == NFT_DATA_RESERVED_MASK &&
		    dtype != NFT_DATA_VERDICT)
			वापस -EINVAL;

		अगर (dtype != NFT_DATA_VERDICT) अणु
			अगर (nla[NFTA_SET_DATA_LEN] == शून्य)
				वापस -EINVAL;
			desc.dlen = ntohl(nla_get_be32(nla[NFTA_SET_DATA_LEN]));
			अगर (desc.dlen == 0 || desc.dlen > NFT_DATA_VALUE_MAXLEN)
				वापस -EINVAL;
		पूर्ण अन्यथा
			desc.dlen = माप(काष्ठा nft_verdict);
	पूर्ण अन्यथा अगर (flags & NFT_SET_MAP)
		वापस -EINVAL;

	अगर (nla[NFTA_SET_OBJ_TYPE] != शून्य) अणु
		अगर (!(flags & NFT_SET_OBJECT))
			वापस -EINVAL;

		objtype = ntohl(nla_get_be32(nla[NFTA_SET_OBJ_TYPE]));
		अगर (objtype == NFT_OBJECT_UNSPEC ||
		    objtype > NFT_OBJECT_MAX)
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (flags & NFT_SET_OBJECT)
		वापस -EINVAL;
	अन्यथा
		objtype = NFT_OBJECT_UNSPEC;

	समयout = 0;
	अगर (nla[NFTA_SET_TIMEOUT] != शून्य) अणु
		अगर (!(flags & NFT_SET_TIMEOUT))
			वापस -EINVAL;

		err = nf_msecs_to_jअगरfies64(nla[NFTA_SET_TIMEOUT], &समयout);
		अगर (err)
			वापस err;
	पूर्ण
	gc_पूर्णांक = 0;
	अगर (nla[NFTA_SET_GC_INTERVAL] != शून्य) अणु
		अगर (!(flags & NFT_SET_TIMEOUT))
			वापस -EINVAL;
		gc_पूर्णांक = ntohl(nla_get_be32(nla[NFTA_SET_GC_INTERVAL]));
	पूर्ण

	policy = NFT_SET_POL_PERFORMANCE;
	अगर (nla[NFTA_SET_POLICY] != शून्य)
		policy = ntohl(nla_get_be32(nla[NFTA_SET_POLICY]));

	अगर (nla[NFTA_SET_DESC] != शून्य) अणु
		err = nf_tables_set_desc_parse(&desc, nla[NFTA_SET_DESC]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (nla[NFTA_SET_EXPR] || nla[NFTA_SET_EXPRESSIONS])
		desc.expr = true;

	table = nft_table_lookup(net, nla[NFTA_SET_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_SET_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

	set = nft_set_lookup(table, nla[NFTA_SET_NAME], genmask);
	अगर (IS_ERR(set)) अणु
		अगर (PTR_ERR(set) != -ENOENT) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_SET_NAME]);
			वापस PTR_ERR(set);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_SET_NAME]);
			वापस -EEXIST;
		पूर्ण
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE)
			वापस -EOPNOTSUPP;

		वापस 0;
	पूर्ण

	अगर (!(info->nlh->nlmsg_flags & NLM_F_CREATE))
		वापस -ENOENT;

	ops = nft_select_set_ops(&ctx, nla, &desc, policy);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);

	udlen = 0;
	अगर (nla[NFTA_SET_USERDATA])
		udlen = nla_len(nla[NFTA_SET_USERDATA]);

	size = 0;
	अगर (ops->privsize != शून्य)
		size = ops->privsize(nla, &desc);
	alloc_size = माप(*set) + size + udlen;
	अगर (alloc_size < size)
		वापस -ENOMEM;
	set = kvzalloc(alloc_size, GFP_KERNEL);
	अगर (!set)
		वापस -ENOMEM;

	name = nla_strdup(nla[NFTA_SET_NAME], GFP_KERNEL);
	अगर (!name) अणु
		err = -ENOMEM;
		जाओ err_set_name;
	पूर्ण

	err = nf_tables_set_alloc_name(&ctx, set, name);
	kमुक्त(name);
	अगर (err < 0)
		जाओ err_set_name;

	udata = शून्य;
	अगर (udlen) अणु
		udata = set->data + size;
		nla_स_नकल(udata, nla[NFTA_SET_USERDATA], udlen);
	पूर्ण

	INIT_LIST_HEAD(&set->bindings);
	INIT_LIST_HEAD(&set->catchall_list);
	set->table = table;
	ग_लिखो_pnet(&set->net, net);
	set->ops = ops;
	set->ktype = ktype;
	set->klen = desc.klen;
	set->dtype = dtype;
	set->objtype = objtype;
	set->dlen = desc.dlen;
	set->flags = flags;
	set->size = desc.size;
	set->policy = policy;
	set->udlen = udlen;
	set->udata = udata;
	set->समयout = समयout;
	set->gc_पूर्णांक = gc_पूर्णांक;

	set->field_count = desc.field_count;
	क्रम (i = 0; i < desc.field_count; i++)
		set->field_len[i] = desc.field_len[i];

	err = ops->init(set, &desc, nla);
	अगर (err < 0)
		जाओ err_set_init;

	अगर (nla[NFTA_SET_EXPR]) अणु
		expr = nft_set_elem_expr_alloc(&ctx, set, nla[NFTA_SET_EXPR]);
		अगर (IS_ERR(expr)) अणु
			err = PTR_ERR(expr);
			जाओ err_set_expr_alloc;
		पूर्ण
		set->exprs[0] = expr;
		set->num_exprs++;
	पूर्ण अन्यथा अगर (nla[NFTA_SET_EXPRESSIONS]) अणु
		काष्ठा nft_expr *expr;
		काष्ठा nlattr *पंचांगp;
		पूर्णांक left;

		अगर (!(flags & NFT_SET_EXPR)) अणु
			err = -EINVAL;
			जाओ err_set_expr_alloc;
		पूर्ण
		i = 0;
		nla_क्रम_each_nested(पंचांगp, nla[NFTA_SET_EXPRESSIONS], left) अणु
			अगर (i == NFT_SET_EXPR_MAX) अणु
				err = -E2BIG;
				जाओ err_set_expr_alloc;
			पूर्ण
			अगर (nla_type(पंचांगp) != NFTA_LIST_ELEM) अणु
				err = -EINVAL;
				जाओ err_set_expr_alloc;
			पूर्ण
			expr = nft_set_elem_expr_alloc(&ctx, set, पंचांगp);
			अगर (IS_ERR(expr)) अणु
				err = PTR_ERR(expr);
				जाओ err_set_expr_alloc;
			पूर्ण
			set->exprs[i++] = expr;
			set->num_exprs++;
		पूर्ण
	पूर्ण

	set->handle = nf_tables_alloc_handle(table);

	err = nft_trans_set_add(&ctx, NFT_MSG_NEWSET, set);
	अगर (err < 0)
		जाओ err_set_expr_alloc;

	list_add_tail_rcu(&set->list, &table->sets);
	table->use++;
	वापस 0;

err_set_expr_alloc:
	क्रम (i = 0; i < set->num_exprs; i++)
		nft_expr_destroy(&ctx, set->exprs[i]);

	ops->destroy(set);
err_set_init:
	kमुक्त(set->name);
err_set_name:
	kvमुक्त(set);
	वापस err;
पूर्ण

काष्ठा nft_set_elem_catchall अणु
	काष्ठा list_head	list;
	काष्ठा rcu_head		rcu;
	व्योम			*elem;
पूर्ण;

अटल व्योम nft_set_catchall_destroy(स्थिर काष्ठा nft_ctx *ctx,
				     काष्ठा nft_set *set)
अणु
	काष्ठा nft_set_elem_catchall *catchall;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		list_del_rcu(&catchall->list);
		nft_set_elem_destroy(set, catchall->elem, true);
		kमुक्त_rcu(catchall);
	पूर्ण
पूर्ण

अटल व्योम nft_set_destroy(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set)
अणु
	पूर्णांक i;

	अगर (WARN_ON(set->use > 0))
		वापस;

	क्रम (i = 0; i < set->num_exprs; i++)
		nft_expr_destroy(ctx, set->exprs[i]);

	set->ops->destroy(set);
	nft_set_catchall_destroy(ctx, set);
	kमुक्त(set->name);
	kvमुक्त(set);
पूर्ण

अटल पूर्णांक nf_tables_dअन्यथाt(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_set *set;
	काष्ठा nft_ctx ctx;
	पूर्णांक err;

	अगर (nfmsg->nfgen_family == NFPROTO_UNSPEC)
		वापस -EAFNOSUPPORT;
	अगर (nla[NFTA_SET_TABLE] == शून्य)
		वापस -EINVAL;

	err = nft_ctx_init_from_setattr(&ctx, net, skb, info->nlh, nla, extack,
					genmask, NETLINK_CB(skb).portid);
	अगर (err < 0)
		वापस err;

	अगर (nla[NFTA_SET_HANDLE]) अणु
		attr = nla[NFTA_SET_HANDLE];
		set = nft_set_lookup_byhandle(ctx.table, attr, genmask);
	पूर्ण अन्यथा अणु
		attr = nla[NFTA_SET_NAME];
		set = nft_set_lookup(ctx.table, attr, genmask);
	पूर्ण

	अगर (IS_ERR(set)) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस PTR_ERR(set);
	पूर्ण
	अगर (set->use ||
	    (info->nlh->nlmsg_flags & NLM_F_NONREC &&
	     atomic_पढ़ो(&set->nelems) > 0)) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस -EBUSY;
	पूर्ण

	वापस nft_dअन्यथाt(&ctx, set);
पूर्ण

अटल पूर्णांक nft_validate_रेजिस्टर_store(स्थिर काष्ठा nft_ctx *ctx,
				       क्रमागत nft_रेजिस्टरs reg,
				       स्थिर काष्ठा nft_data *data,
				       क्रमागत nft_data_types type,
				       अचिन्हित पूर्णांक len);

अटल पूर्णांक nft_setelem_data_validate(स्थिर काष्ठा nft_ctx *ctx,
				     काष्ठा nft_set *set,
				     काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);
	क्रमागत nft_रेजिस्टरs dreg;

	dreg = nft_type_to_reg(set->dtype);
	वापस nft_validate_रेजिस्टर_store(ctx, dreg, nft_set_ext_data(ext),
					   set->dtype == NFT_DATA_VERDICT ?
					   NFT_DATA_VERDICT : NFT_DATA_VALUE,
					   set->dlen);
पूर्ण

अटल पूर्णांक nf_tables_bind_check_setelem(स्थिर काष्ठा nft_ctx *ctx,
					काष्ठा nft_set *set,
					स्थिर काष्ठा nft_set_iter *iter,
					काष्ठा nft_set_elem *elem)
अणु
	वापस nft_setelem_data_validate(ctx, set, elem);
पूर्ण

अटल पूर्णांक nft_set_catchall_bind_check(स्थिर काष्ठा nft_ctx *ctx,
				       काष्ठा nft_set *set)
अणु
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_set_elem_catchall *catchall;
	काष्ठा nft_set_elem elem;
	काष्ठा nft_set_ext *ext;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (!nft_set_elem_active(ext, genmask))
			जारी;

		elem.priv = catchall->elem;
		ret = nft_setelem_data_validate(ctx, set, &elem);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक nf_tables_bind_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
		       काष्ठा nft_set_binding *binding)
अणु
	काष्ठा nft_set_binding *i;
	काष्ठा nft_set_iter iter;

	अगर (set->use == अच_पूर्णांक_उच्च)
		वापस -EOVERFLOW;

	अगर (!list_empty(&set->bindings) && nft_set_is_anonymous(set))
		वापस -EBUSY;

	अगर (binding->flags & NFT_SET_MAP) अणु
		/* If the set is alपढ़ोy bound to the same chain all
		 * jumps are alपढ़ोy validated क्रम that chain.
		 */
		list_क्रम_each_entry(i, &set->bindings, list) अणु
			अगर (i->flags & NFT_SET_MAP &&
			    i->chain == binding->chain)
				जाओ bind;
		पूर्ण

		iter.genmask	= nft_genmask_next(ctx->net);
		iter.skip 	= 0;
		iter.count	= 0;
		iter.err	= 0;
		iter.fn		= nf_tables_bind_check_setelem;

		set->ops->walk(ctx, set, &iter);
		अगर (!iter.err)
			iter.err = nft_set_catchall_bind_check(ctx, set);

		अगर (iter.err < 0)
			वापस iter.err;
	पूर्ण
bind:
	binding->chain = ctx->chain;
	list_add_tail_rcu(&binding->list, &set->bindings);
	nft_set_trans_bind(ctx, set);
	set->use++;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_tables_bind_set);

अटल व्योम nf_tables_unbind_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
				 काष्ठा nft_set_binding *binding, bool event)
अणु
	list_del_rcu(&binding->list);

	अगर (list_empty(&set->bindings) && nft_set_is_anonymous(set)) अणु
		list_del_rcu(&set->list);
		अगर (event)
			nf_tables_set_notअगरy(ctx, set, NFT_MSG_DELSET,
					     GFP_KERNEL);
	पूर्ण
पूर्ण

व्योम nf_tables_deactivate_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			      काष्ठा nft_set_binding *binding,
			      क्रमागत nft_trans_phase phase)
अणु
	चयन (phase) अणु
	हाल NFT_TRANS_PREPARE:
		set->use--;
		वापस;
	हाल NFT_TRANS_ABORT:
	हाल NFT_TRANS_RELEASE:
		set->use--;
		fallthrough;
	शेष:
		nf_tables_unbind_set(ctx, set, binding,
				     phase == NFT_TRANS_COMMIT);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_tables_deactivate_set);

व्योम nf_tables_destroy_set(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set)
अणु
	अगर (list_empty(&set->bindings) && nft_set_is_anonymous(set))
		nft_set_destroy(ctx, set);
पूर्ण
EXPORT_SYMBOL_GPL(nf_tables_destroy_set);

स्थिर काष्ठा nft_set_ext_type nft_set_ext_types[] = अणु
	[NFT_SET_EXT_KEY]		= अणु
		.align	= __alignof__(u32),
	पूर्ण,
	[NFT_SET_EXT_DATA]		= अणु
		.align	= __alignof__(u32),
	पूर्ण,
	[NFT_SET_EXT_EXPRESSIONS]	= अणु
		.align	= __alignof__(काष्ठा nft_set_elem_expr),
	पूर्ण,
	[NFT_SET_EXT_OBJREF]		= अणु
		.len	= माप(काष्ठा nft_object *),
		.align	= __alignof__(काष्ठा nft_object *),
	पूर्ण,
	[NFT_SET_EXT_FLAGS]		= अणु
		.len	= माप(u8),
		.align	= __alignof__(u8),
	पूर्ण,
	[NFT_SET_EXT_TIMEOUT]		= अणु
		.len	= माप(u64),
		.align	= __alignof__(u64),
	पूर्ण,
	[NFT_SET_EXT_EXPIRATION]	= अणु
		.len	= माप(u64),
		.align	= __alignof__(u64),
	पूर्ण,
	[NFT_SET_EXT_USERDATA]		= अणु
		.len	= माप(काष्ठा nft_userdata),
		.align	= __alignof__(काष्ठा nft_userdata),
	पूर्ण,
	[NFT_SET_EXT_KEY_END]		= अणु
		.align	= __alignof__(u32),
	पूर्ण,
पूर्ण;

/*
 * Set elements
 */

अटल स्थिर काष्ठा nla_policy nft_set_elem_policy[NFTA_SET_ELEM_MAX + 1] = अणु
	[NFTA_SET_ELEM_KEY]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_ELEM_DATA]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_ELEM_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SET_ELEM_TIMEOUT]		= अणु .type = NLA_U64 पूर्ण,
	[NFTA_SET_ELEM_EXPIRATION]	= अणु .type = NLA_U64 पूर्ण,
	[NFTA_SET_ELEM_USERDATA]	= अणु .type = NLA_BINARY,
					    .len = NFT_USERDATA_MAXLEN पूर्ण,
	[NFTA_SET_ELEM_EXPR]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_ELEM_OBJREF]		= अणु .type = NLA_STRING,
					    .len = NFT_OBJ_MAXNAMELEN - 1 पूर्ण,
	[NFTA_SET_ELEM_KEY_END]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_ELEM_EXPRESSIONS]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_set_elem_list_policy[NFTA_SET_ELEM_LIST_MAX + 1] = अणु
	[NFTA_SET_ELEM_LIST_TABLE]	= अणु .type = NLA_STRING,
					    .len = NFT_TABLE_MAXNAMELEN - 1 पूर्ण,
	[NFTA_SET_ELEM_LIST_SET]	= अणु .type = NLA_STRING,
					    .len = NFT_SET_MAXNAMELEN - 1 पूर्ण,
	[NFTA_SET_ELEM_LIST_ELEMENTS]	= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_SET_ELEM_LIST_SET_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_ctx_init_from_elemattr(काष्ठा nft_ctx *ctx, काष्ठा net *net,
				      स्थिर काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nlmsghdr *nlh,
				      स्थिर काष्ठा nlattr * स्थिर nla[],
				      काष्ठा netlink_ext_ack *extack,
				      u8 genmask, u32 nlpid)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(nlh);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_table *table;

	table = nft_table_lookup(net, nla[NFTA_SET_ELEM_LIST_TABLE], family,
				 genmask, nlpid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_SET_ELEM_LIST_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	nft_ctx_init(ctx, net, skb, nlh, family, table, शून्य, nla);
	वापस 0;
पूर्ण

अटल पूर्णांक nft_set_elem_expr_dump(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nft_set *set,
				  स्थिर काष्ठा nft_set_ext *ext)
अणु
	काष्ठा nft_set_elem_expr *elem_expr;
	u32 size, num_exprs = 0;
	काष्ठा nft_expr *expr;
	काष्ठा nlattr *nest;

	elem_expr = nft_set_ext_expr(ext);
	nft_setelem_expr_क्रमeach(expr, elem_expr, size)
		num_exprs++;

	अगर (num_exprs == 1) अणु
		expr = nft_setelem_expr_at(elem_expr, 0);
		अगर (nft_expr_dump(skb, NFTA_SET_ELEM_EXPR, expr) < 0)
			वापस -1;

		वापस 0;
	पूर्ण अन्यथा अगर (num_exprs > 1) अणु
		nest = nla_nest_start_noflag(skb, NFTA_SET_ELEM_EXPRESSIONS);
		अगर (nest == शून्य)
			जाओ nla_put_failure;

		nft_setelem_expr_क्रमeach(expr, elem_expr, size) अणु
			expr = nft_setelem_expr_at(elem_expr, size);
			अगर (nft_expr_dump(skb, NFTA_LIST_ELEM, expr) < 0)
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, nest);
	पूर्ण
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nf_tables_fill_setelem(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nft_set *set,
				  स्थिर काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, NFTA_LIST_ELEM);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_KEY) &&
	    nft_data_dump(skb, NFTA_SET_ELEM_KEY, nft_set_ext_key(ext),
			  NFT_DATA_VALUE, set->klen) < 0)
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_KEY_END) &&
	    nft_data_dump(skb, NFTA_SET_ELEM_KEY_END, nft_set_ext_key_end(ext),
			  NFT_DATA_VALUE, set->klen) < 0)
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_DATA) &&
	    nft_data_dump(skb, NFTA_SET_ELEM_DATA, nft_set_ext_data(ext),
			  set->dtype == NFT_DATA_VERDICT ? NFT_DATA_VERDICT : NFT_DATA_VALUE,
			  set->dlen) < 0)
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_EXPRESSIONS) &&
	    nft_set_elem_expr_dump(skb, set, ext))
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF) &&
	    nla_put_string(skb, NFTA_SET_ELEM_OBJREF,
			   (*nft_set_ext_obj(ext))->key.name) < 0)
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_FLAGS) &&
	    nla_put_be32(skb, NFTA_SET_ELEM_FLAGS,
		         htonl(*nft_set_ext_flags(ext))))
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_TIMEOUT) &&
	    nla_put_be64(skb, NFTA_SET_ELEM_TIMEOUT,
			 nf_jअगरfies64_to_msecs(*nft_set_ext_समयout(ext)),
			 NFTA_SET_ELEM_PAD))
		जाओ nla_put_failure;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_EXPIRATION)) अणु
		u64 expires, now = get_jअगरfies_64();

		expires = *nft_set_ext_expiration(ext);
		अगर (समय_beक्रमe64(now, expires))
			expires -= now;
		अन्यथा
			expires = 0;

		अगर (nla_put_be64(skb, NFTA_SET_ELEM_EXPIRATION,
				 nf_jअगरfies64_to_msecs(expires),
				 NFTA_SET_ELEM_PAD))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_USERDATA)) अणु
		काष्ठा nft_userdata *udata;

		udata = nft_set_ext_userdata(ext);
		अगर (nla_put(skb, NFTA_SET_ELEM_USERDATA,
			    udata->len + 1, udata->data))
			जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -EMSGSIZE;
पूर्ण

काष्ठा nft_set_dump_args अणु
	स्थिर काष्ठा netlink_callback	*cb;
	काष्ठा nft_set_iter		iter;
	काष्ठा sk_buff			*skb;
पूर्ण;

अटल पूर्णांक nf_tables_dump_setelem(स्थिर काष्ठा nft_ctx *ctx,
				  काष्ठा nft_set *set,
				  स्थिर काष्ठा nft_set_iter *iter,
				  काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_set_dump_args *args;

	args = container_of(iter, काष्ठा nft_set_dump_args, iter);
	वापस nf_tables_fill_setelem(args->skb, set, elem);
पूर्ण

काष्ठा nft_set_dump_ctx अणु
	स्थिर काष्ठा nft_set	*set;
	काष्ठा nft_ctx		ctx;
पूर्ण;

अटल पूर्णांक nft_set_catchall_dump(काष्ठा net *net, काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_set_elem_catchall *catchall;
	u8 genmask = nft_genmask_cur(net);
	काष्ठा nft_set_elem elem;
	काष्ठा nft_set_ext *ext;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (!nft_set_elem_active(ext, genmask) ||
		    nft_set_elem_expired(ext))
			जारी;

		elem.priv = catchall->elem;
		ret = nf_tables_fill_setelem(skb, set, &elem);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nf_tables_dump_set(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nft_set_dump_ctx *dump_ctx = cb->data;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_table *table;
	काष्ठा nft_set *set;
	काष्ठा nft_set_dump_args args;
	bool set_found = false;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nest;
	u32 portid, seq;
	पूर्णांक event;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (dump_ctx->ctx.family != NFPROTO_UNSPEC &&
		    dump_ctx->ctx.family != table->family)
			जारी;

		अगर (table != dump_ctx->ctx.table)
			जारी;

		list_क्रम_each_entry_rcu(set, &table->sets, list) अणु
			अगर (set == dump_ctx->set) अणु
				set_found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!set_found) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	event  = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, NFT_MSG_NEWSETELEM);
	portid = NETLINK_CB(cb->skb).portid;
	seq    = cb->nlh->nlmsg_seq;

	nlh = nfnl_msg_put(skb, portid, seq, event, NLM_F_MULTI,
			   table->family, NFNETLINK_V0, nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_SET_ELEM_LIST_TABLE, table->name))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, NFTA_SET_ELEM_LIST_SET, set->name))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, NFTA_SET_ELEM_LIST_ELEMENTS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	args.cb			= cb;
	args.skb		= skb;
	args.iter.genmask	= nft_genmask_cur(net);
	args.iter.skip		= cb->args[0];
	args.iter.count		= 0;
	args.iter.err		= 0;
	args.iter.fn		= nf_tables_dump_setelem;
	set->ops->walk(&dump_ctx->ctx, set, &args.iter);

	अगर (!args.iter.err && args.iter.count == cb->args[0])
		args.iter.err = nft_set_catchall_dump(net, skb, set);
	rcu_पढ़ो_unlock();

	nla_nest_end(skb, nest);
	nlmsg_end(skb, nlh);

	अगर (args.iter.err && args.iter.err != -EMSGSIZE)
		वापस args.iter.err;
	अगर (args.iter.count == cb->args[0])
		वापस 0;

	cb->args[0] = args.iter.count;
	वापस skb->len;

nla_put_failure:
	rcu_पढ़ो_unlock();
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक nf_tables_dump_set_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nft_set_dump_ctx *dump_ctx = cb->data;

	cb->data = kmemdup(dump_ctx, माप(*dump_ctx), GFP_ATOMIC);

	वापस cb->data ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक nf_tables_dump_set_करोne(काष्ठा netlink_callback *cb)
अणु
	kमुक्त(cb->data);
	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_fill_setelem_info(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nft_ctx *ctx, u32 seq,
				       u32 portid, पूर्णांक event, u16 flags,
				       स्थिर काष्ठा nft_set *set,
				       स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nest;
	पूर्णांक err;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, ctx->family,
			   NFNETLINK_V0, nft_base_seq(ctx->net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_SET_TABLE, ctx->table->name))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, NFTA_SET_NAME, set->name))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, NFTA_SET_ELEM_LIST_ELEMENTS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	err = nf_tables_fill_setelem(skb, set, elem);
	अगर (err < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक nft_setelem_parse_flags(स्थिर काष्ठा nft_set *set,
				   स्थिर काष्ठा nlattr *attr, u32 *flags)
अणु
	अगर (attr == शून्य)
		वापस 0;

	*flags = ntohl(nla_get_be32(attr));
	अगर (*flags & ~(NFT_SET_ELEM_INTERVAL_END | NFT_SET_ELEM_CATCHALL))
		वापस -EOPNOTSUPP;
	अगर (!(set->flags & NFT_SET_INTERVAL) &&
	    *flags & NFT_SET_ELEM_INTERVAL_END)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_setelem_parse_key(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
				 काष्ठा nft_data *key, काष्ठा nlattr *attr)
अणु
	काष्ठा nft_data_desc desc;
	पूर्णांक err;

	err = nft_data_init(ctx, key, NFT_DATA_VALUE_MAXLEN, &desc, attr);
	अगर (err < 0)
		वापस err;

	अगर (desc.type != NFT_DATA_VALUE || desc.len != set->klen) अणु
		nft_data_release(key, desc.type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_setelem_parse_data(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
				  काष्ठा nft_data_desc *desc,
				  काष्ठा nft_data *data,
				  काष्ठा nlattr *attr)
अणु
	पूर्णांक err;

	err = nft_data_init(ctx, data, NFT_DATA_VALUE_MAXLEN, desc, attr);
	अगर (err < 0)
		वापस err;

	अगर (desc->type != NFT_DATA_VERDICT && desc->len != set->dlen) अणु
		nft_data_release(data, desc->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *nft_setelem_catchall_get(स्थिर काष्ठा net *net,
				      स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_set_elem_catchall *catchall;
	u8 genmask = nft_genmask_cur(net);
	काष्ठा nft_set_ext *ext;
	व्योम *priv = शून्य;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (!nft_set_elem_active(ext, genmask) ||
		    nft_set_elem_expired(ext))
			जारी;

		priv = catchall->elem;
		अवरोध;
	पूर्ण

	वापस priv;
पूर्ण

अटल पूर्णांक nft_setelem_get(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			   काष्ठा nft_set_elem *elem, u32 flags)
अणु
	व्योम *priv;

	अगर (!(flags & NFT_SET_ELEM_CATCHALL)) अणु
		priv = set->ops->get(ctx->net, set, elem, flags);
		अगर (IS_ERR(priv))
			वापस PTR_ERR(priv);
	पूर्ण अन्यथा अणु
		priv = nft_setelem_catchall_get(ctx->net, set);
		अगर (!priv)
			वापस -ENOENT;
	पूर्ण
	elem->priv = priv;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_get_set_elem(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			    स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *nla[NFTA_SET_ELEM_MAX + 1];
	काष्ठा nft_set_elem elem;
	काष्ठा sk_buff *skb;
	uपूर्णांक32_t flags = 0;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(nla, NFTA_SET_ELEM_MAX, attr,
					  nft_set_elem_policy, शून्य);
	अगर (err < 0)
		वापस err;

	err = nft_setelem_parse_flags(set, nla[NFTA_SET_ELEM_FLAGS], &flags);
	अगर (err < 0)
		वापस err;

	अगर (!nla[NFTA_SET_ELEM_KEY] && !(flags & NFT_SET_ELEM_CATCHALL))
		वापस -EINVAL;

	अगर (nla[NFTA_SET_ELEM_KEY]) अणु
		err = nft_setelem_parse_key(ctx, set, &elem.key.val,
					    nla[NFTA_SET_ELEM_KEY]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_KEY_END]) अणु
		err = nft_setelem_parse_key(ctx, set, &elem.key_end.val,
					    nla[NFTA_SET_ELEM_KEY_END]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = nft_setelem_get(ctx, set, &elem, flags);
	अगर (err < 0)
		वापस err;

	err = -ENOMEM;
	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस err;

	err = nf_tables_fill_setelem_info(skb, ctx, ctx->seq, ctx->portid,
					  NFT_MSG_NEWSETELEM, 0, set, &elem);
	अगर (err < 0)
		जाओ err_fill_setelem;

	वापस nfnetlink_unicast(skb, ctx->net, ctx->portid);

err_fill_setelem:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_माला_लोetelem(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nfnl_info *info,
				स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	काष्ठा net *net = info->net;
	काष्ठा nft_set *set;
	काष्ठा nlattr *attr;
	काष्ठा nft_ctx ctx;
	पूर्णांक rem, err = 0;

	err = nft_ctx_init_from_elemattr(&ctx, net, skb, info->nlh, nla, extack,
					 genmask, NETLINK_CB(skb).portid);
	अगर (err < 0)
		वापस err;

	set = nft_set_lookup(ctx.table, nla[NFTA_SET_ELEM_LIST_SET], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = nf_tables_dump_set_start,
			.dump = nf_tables_dump_set,
			.करोne = nf_tables_dump_set_करोne,
			.module = THIS_MODULE,
		पूर्ण;
		काष्ठा nft_set_dump_ctx dump_ctx = अणु
			.set = set,
			.ctx = ctx,
		पूर्ण;

		c.data = &dump_ctx;
		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	अगर (!nla[NFTA_SET_ELEM_LIST_ELEMENTS])
		वापस -EINVAL;

	nla_क्रम_each_nested(attr, nla[NFTA_SET_ELEM_LIST_ELEMENTS], rem) अणु
		err = nft_get_set_elem(&ctx, set, attr);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम nf_tables_setelem_notअगरy(स्थिर काष्ठा nft_ctx *ctx,
				     स्थिर काष्ठा nft_set *set,
				     स्थिर काष्ठा nft_set_elem *elem,
				     पूर्णांक event, u16 flags)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा net *net = ctx->net;
	u32 portid = ctx->portid;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (!ctx->report && !nfnetlink_has_listeners(net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_setelem_info(skb, ctx, 0, portid, event, flags,
					  set, elem);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_net = nft_pernet(net);
	nft_notअगरy_enqueue(skb, ctx->report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(net, portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण

अटल काष्ठा nft_trans *nft_trans_elem_alloc(काष्ठा nft_ctx *ctx,
					      पूर्णांक msg_type,
					      काष्ठा nft_set *set)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc(ctx, msg_type, माप(काष्ठा nft_trans_elem));
	अगर (trans == शून्य)
		वापस शून्य;

	nft_trans_elem_set(trans) = set;
	वापस trans;
पूर्ण

काष्ठा nft_expr *nft_set_elem_expr_alloc(स्थिर काष्ठा nft_ctx *ctx,
					 स्थिर काष्ठा nft_set *set,
					 स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nft_expr *expr;
	पूर्णांक err;

	expr = nft_expr_init(ctx, attr);
	अगर (IS_ERR(expr))
		वापस expr;

	err = -EOPNOTSUPP;
	अगर (!(expr->ops->type->flags & NFT_EXPR_STATEFUL))
		जाओ err_set_elem_expr;

	अगर (expr->ops->type->flags & NFT_EXPR_GC) अणु
		अगर (set->flags & NFT_SET_TIMEOUT)
			जाओ err_set_elem_expr;
		अगर (!set->ops->gc_init)
			जाओ err_set_elem_expr;
		set->ops->gc_init(set);
	पूर्ण

	वापस expr;

err_set_elem_expr:
	nft_expr_destroy(ctx, expr);
	वापस ERR_PTR(err);
पूर्ण

व्योम *nft_set_elem_init(स्थिर काष्ठा nft_set *set,
			स्थिर काष्ठा nft_set_ext_पंचांगpl *पंचांगpl,
			स्थिर u32 *key, स्थिर u32 *key_end,
			स्थिर u32 *data, u64 समयout, u64 expiration, gfp_t gfp)
अणु
	काष्ठा nft_set_ext *ext;
	व्योम *elem;

	elem = kzalloc(set->ops->elemsize + पंचांगpl->len, gfp);
	अगर (elem == शून्य)
		वापस शून्य;

	ext = nft_set_elem_ext(set, elem);
	nft_set_ext_init(ext, पंचांगpl);

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_KEY))
		स_नकल(nft_set_ext_key(ext), key, set->klen);
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_KEY_END))
		स_नकल(nft_set_ext_key_end(ext), key_end, set->klen);
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_DATA))
		स_नकल(nft_set_ext_data(ext), data, set->dlen);
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_EXPIRATION)) अणु
		*nft_set_ext_expiration(ext) = get_jअगरfies_64() + expiration;
		अगर (expiration == 0)
			*nft_set_ext_expiration(ext) += समयout;
	पूर्ण
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_TIMEOUT))
		*nft_set_ext_समयout(ext) = समयout;

	वापस elem;
पूर्ण

अटल व्योम __nft_set_elem_expr_destroy(स्थिर काष्ठा nft_ctx *ctx,
					काष्ठा nft_expr *expr)
अणु
	अगर (expr->ops->destroy_clone) अणु
		expr->ops->destroy_clone(ctx, expr);
		module_put(expr->ops->type->owner);
	पूर्ण अन्यथा अणु
		nf_tables_expr_destroy(ctx, expr);
	पूर्ण
पूर्ण

अटल व्योम nft_set_elem_expr_destroy(स्थिर काष्ठा nft_ctx *ctx,
				      काष्ठा nft_set_elem_expr *elem_expr)
अणु
	काष्ठा nft_expr *expr;
	u32 size;

	nft_setelem_expr_क्रमeach(expr, elem_expr, size)
		__nft_set_elem_expr_destroy(ctx, expr);
पूर्ण

व्योम nft_set_elem_destroy(स्थिर काष्ठा nft_set *set, व्योम *elem,
			  bool destroy_expr)
अणु
	काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem);
	काष्ठा nft_ctx ctx = अणु
		.net	= पढ़ो_pnet(&set->net),
		.family	= set->table->family,
	पूर्ण;

	nft_data_release(nft_set_ext_key(ext), NFT_DATA_VALUE);
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_DATA))
		nft_data_release(nft_set_ext_data(ext), set->dtype);
	अगर (destroy_expr && nft_set_ext_exists(ext, NFT_SET_EXT_EXPRESSIONS))
		nft_set_elem_expr_destroy(&ctx, nft_set_ext_expr(ext));

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF))
		(*nft_set_ext_obj(ext))->use--;
	kमुक्त(elem);
पूर्ण
EXPORT_SYMBOL_GPL(nft_set_elem_destroy);

/* Only called from commit path, nft_setelem_data_deactivate() alपढ़ोy deals
 * with the refcounting from the preparation phase.
 */
अटल व्योम nf_tables_set_elem_destroy(स्थिर काष्ठा nft_ctx *ctx,
				       स्थिर काष्ठा nft_set *set, व्योम *elem)
अणु
	काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem);

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_EXPRESSIONS))
		nft_set_elem_expr_destroy(ctx, nft_set_ext_expr(ext));

	kमुक्त(elem);
पूर्ण

पूर्णांक nft_set_elem_expr_clone(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			    काष्ठा nft_expr *expr_array[])
अणु
	काष्ठा nft_expr *expr;
	पूर्णांक err, i, k;

	क्रम (i = 0; i < set->num_exprs; i++) अणु
		expr = kzalloc(set->exprs[i]->ops->size, GFP_KERNEL);
		अगर (!expr)
			जाओ err_expr;

		err = nft_expr_clone(expr, set->exprs[i]);
		अगर (err < 0) अणु
			nft_expr_destroy(ctx, expr);
			जाओ err_expr;
		पूर्ण
		expr_array[i] = expr;
	पूर्ण

	वापस 0;

err_expr:
	क्रम (k = i - 1; k >= 0; k--)
		nft_expr_destroy(ctx, expr_array[k]);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक nft_set_elem_expr_setup(काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nft_set_ext *ext,
				   काष्ठा nft_expr *expr_array[],
				   u32 num_exprs)
अणु
	काष्ठा nft_set_elem_expr *elem_expr = nft_set_ext_expr(ext);
	काष्ठा nft_expr *expr;
	पूर्णांक i, err;

	क्रम (i = 0; i < num_exprs; i++) अणु
		expr = nft_setelem_expr_at(elem_expr, elem_expr->size);
		err = nft_expr_clone(expr, expr_array[i]);
		अगर (err < 0)
			जाओ err_elem_expr_setup;

		elem_expr->size += expr_array[i]->ops->size;
		nft_expr_destroy(ctx, expr_array[i]);
		expr_array[i] = शून्य;
	पूर्ण

	वापस 0;

err_elem_expr_setup:
	क्रम (; i < num_exprs; i++) अणु
		nft_expr_destroy(ctx, expr_array[i]);
		expr_array[i] = शून्य;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

काष्ठा nft_set_ext *nft_set_catchall_lookup(स्थिर काष्ठा net *net,
					    स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_set_elem_catchall *catchall;
	u8 genmask = nft_genmask_cur(net);
	काष्ठा nft_set_ext *ext;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (nft_set_elem_active(ext, genmask) &&
		    !nft_set_elem_expired(ext))
			वापस ext;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nft_set_catchall_lookup);

व्योम *nft_set_catchall_gc(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_set_elem_catchall *catchall, *next;
	काष्ठा nft_set_ext *ext;
	व्योम *elem = शून्य;

	list_क्रम_each_entry_safe(catchall, next, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);

		अगर (!nft_set_elem_expired(ext) ||
		    nft_set_elem_mark_busy(ext))
			जारी;

		elem = catchall->elem;
		list_del_rcu(&catchall->list);
		kमुक्त_rcu(catchall, rcu);
		अवरोध;
	पूर्ण

	वापस elem;
पूर्ण
EXPORT_SYMBOL_GPL(nft_set_catchall_gc);

अटल पूर्णांक nft_setelem_catchall_insert(स्थिर काष्ठा net *net,
				       काष्ठा nft_set *set,
				       स्थिर काष्ठा nft_set_elem *elem,
				       काष्ठा nft_set_ext **pext)
अणु
	काष्ठा nft_set_elem_catchall *catchall;
	u8 genmask = nft_genmask_next(net);
	काष्ठा nft_set_ext *ext;

	list_क्रम_each_entry(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (nft_set_elem_active(ext, genmask)) अणु
			*pext = ext;
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	catchall = kदो_स्मृति(माप(*catchall), GFP_KERNEL);
	अगर (!catchall)
		वापस -ENOMEM;

	catchall->elem = elem->priv;
	list_add_tail_rcu(&catchall->list, &set->catchall_list);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_setelem_insert(स्थिर काष्ठा net *net,
			      काष्ठा nft_set *set,
			      स्थिर काष्ठा nft_set_elem *elem,
			      काष्ठा nft_set_ext **ext, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;

	अगर (flags & NFT_SET_ELEM_CATCHALL)
		ret = nft_setelem_catchall_insert(net, set, elem, ext);
	अन्यथा
		ret = set->ops->insert(net, set, elem, ext);

	वापस ret;
पूर्ण

अटल bool nft_setelem_is_catchall(स्थिर काष्ठा nft_set *set,
				    स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_FLAGS) &&
	    *nft_set_ext_flags(ext) & NFT_SET_ELEM_CATCHALL)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम nft_setelem_activate(काष्ठा net *net, काष्ठा nft_set *set,
				 काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	अगर (nft_setelem_is_catchall(set, elem)) अणु
		nft_set_elem_change_active(net, set, ext);
		nft_set_elem_clear_busy(ext);
	पूर्ण अन्यथा अणु
		set->ops->activate(net, set, elem);
	पूर्ण
पूर्ण

अटल पूर्णांक nft_setelem_catchall_deactivate(स्थिर काष्ठा net *net,
					   काष्ठा nft_set *set,
					   काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_set_elem_catchall *catchall;
	काष्ठा nft_set_ext *ext;

	list_क्रम_each_entry(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (!nft_is_active(net, ext) ||
		    nft_set_elem_mark_busy(ext))
			जारी;

		kमुक्त(elem->priv);
		elem->priv = catchall->elem;
		nft_set_elem_change_active(net, set, ext);
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक __nft_setelem_deactivate(स्थिर काष्ठा net *net,
				    काष्ठा nft_set *set,
				    काष्ठा nft_set_elem *elem)
अणु
	व्योम *priv;

	priv = set->ops->deactivate(net, set, elem);
	अगर (!priv)
		वापस -ENOENT;

	kमुक्त(elem->priv);
	elem->priv = priv;
	set->ndeact++;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_setelem_deactivate(स्थिर काष्ठा net *net,
				  काष्ठा nft_set *set,
				  काष्ठा nft_set_elem *elem, u32 flags)
अणु
	पूर्णांक ret;

	अगर (flags & NFT_SET_ELEM_CATCHALL)
		ret = nft_setelem_catchall_deactivate(net, set, elem);
	अन्यथा
		ret = __nft_setelem_deactivate(net, set, elem);

	वापस ret;
पूर्ण

अटल व्योम nft_setelem_catchall_हटाओ(स्थिर काष्ठा net *net,
					स्थिर काष्ठा nft_set *set,
					स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_set_elem_catchall *catchall, *next;

	list_क्रम_each_entry_safe(catchall, next, &set->catchall_list, list) अणु
		अगर (catchall->elem == elem->priv) अणु
			list_del_rcu(&catchall->list);
			kमुक्त_rcu(catchall);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nft_setelem_हटाओ(स्थिर काष्ठा net *net,
			       स्थिर काष्ठा nft_set *set,
			       स्थिर काष्ठा nft_set_elem *elem)
अणु
	अगर (nft_setelem_is_catchall(set, elem))
		nft_setelem_catchall_हटाओ(net, set, elem);
	अन्यथा
		set->ops->हटाओ(net, set, elem);
पूर्ण

अटल पूर्णांक nft_add_set_elem(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			    स्थिर काष्ठा nlattr *attr, u32 nlmsg_flags)
अणु
	काष्ठा nft_expr *expr_array[NFT_SET_EXPR_MAX] = अणुपूर्ण;
	काष्ठा nlattr *nla[NFTA_SET_ELEM_MAX + 1];
	u8 genmask = nft_genmask_next(ctx->net);
	u32 flags = 0, size = 0, num_exprs = 0;
	काष्ठा nft_set_ext_पंचांगpl पंचांगpl;
	काष्ठा nft_set_ext *ext, *ext2;
	काष्ठा nft_set_elem elem;
	काष्ठा nft_set_binding *binding;
	काष्ठा nft_object *obj = शून्य;
	काष्ठा nft_userdata *udata;
	काष्ठा nft_data_desc desc;
	क्रमागत nft_रेजिस्टरs dreg;
	काष्ठा nft_trans *trans;
	u64 समयout;
	u64 expiration;
	पूर्णांक err, i;
	u8 ulen;

	err = nla_parse_nested_deprecated(nla, NFTA_SET_ELEM_MAX, attr,
					  nft_set_elem_policy, शून्य);
	अगर (err < 0)
		वापस err;

	nft_set_ext_prepare(&पंचांगpl);

	err = nft_setelem_parse_flags(set, nla[NFTA_SET_ELEM_FLAGS], &flags);
	अगर (err < 0)
		वापस err;

	अगर (!nla[NFTA_SET_ELEM_KEY] && !(flags & NFT_SET_ELEM_CATCHALL))
		वापस -EINVAL;

	अगर (flags != 0)
		nft_set_ext_add(&पंचांगpl, NFT_SET_EXT_FLAGS);

	अगर (set->flags & NFT_SET_MAP) अणु
		अगर (nla[NFTA_SET_ELEM_DATA] == शून्य &&
		    !(flags & NFT_SET_ELEM_INTERVAL_END))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (nla[NFTA_SET_ELEM_DATA] != शून्य)
			वापस -EINVAL;
	पूर्ण

	अगर ((flags & NFT_SET_ELEM_INTERVAL_END) &&
	     (nla[NFTA_SET_ELEM_DATA] ||
	      nla[NFTA_SET_ELEM_OBJREF] ||
	      nla[NFTA_SET_ELEM_TIMEOUT] ||
	      nla[NFTA_SET_ELEM_EXPIRATION] ||
	      nla[NFTA_SET_ELEM_USERDATA] ||
	      nla[NFTA_SET_ELEM_EXPR] ||
	      nla[NFTA_SET_ELEM_EXPRESSIONS]))
		वापस -EINVAL;

	समयout = 0;
	अगर (nla[NFTA_SET_ELEM_TIMEOUT] != शून्य) अणु
		अगर (!(set->flags & NFT_SET_TIMEOUT))
			वापस -EINVAL;
		err = nf_msecs_to_jअगरfies64(nla[NFTA_SET_ELEM_TIMEOUT],
					    &समयout);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (set->flags & NFT_SET_TIMEOUT) अणु
		समयout = set->समयout;
	पूर्ण

	expiration = 0;
	अगर (nla[NFTA_SET_ELEM_EXPIRATION] != शून्य) अणु
		अगर (!(set->flags & NFT_SET_TIMEOUT))
			वापस -EINVAL;
		err = nf_msecs_to_jअगरfies64(nla[NFTA_SET_ELEM_EXPIRATION],
					    &expiration);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_EXPR]) अणु
		काष्ठा nft_expr *expr;

		अगर (set->num_exprs && set->num_exprs != 1)
			वापस -EOPNOTSUPP;

		expr = nft_set_elem_expr_alloc(ctx, set,
					       nla[NFTA_SET_ELEM_EXPR]);
		अगर (IS_ERR(expr))
			वापस PTR_ERR(expr);

		expr_array[0] = expr;
		num_exprs = 1;

		अगर (set->num_exprs && set->exprs[0]->ops != expr->ops) अणु
			err = -EOPNOTSUPP;
			जाओ err_set_elem_expr;
		पूर्ण
	पूर्ण अन्यथा अगर (nla[NFTA_SET_ELEM_EXPRESSIONS]) अणु
		काष्ठा nft_expr *expr;
		काष्ठा nlattr *पंचांगp;
		पूर्णांक left;

		i = 0;
		nla_क्रम_each_nested(पंचांगp, nla[NFTA_SET_ELEM_EXPRESSIONS], left) अणु
			अगर (i == NFT_SET_EXPR_MAX ||
			    (set->num_exprs && set->num_exprs == i)) अणु
				err = -E2BIG;
				जाओ err_set_elem_expr;
			पूर्ण
			अगर (nla_type(पंचांगp) != NFTA_LIST_ELEM) अणु
				err = -EINVAL;
				जाओ err_set_elem_expr;
			पूर्ण
			expr = nft_set_elem_expr_alloc(ctx, set, पंचांगp);
			अगर (IS_ERR(expr)) अणु
				err = PTR_ERR(expr);
				जाओ err_set_elem_expr;
			पूर्ण
			expr_array[i] = expr;
			num_exprs++;

			अगर (set->num_exprs && expr->ops != set->exprs[i]->ops) अणु
				err = -EOPNOTSUPP;
				जाओ err_set_elem_expr;
			पूर्ण
			i++;
		पूर्ण
		अगर (set->num_exprs && set->num_exprs != i) अणु
			err = -EOPNOTSUPP;
			जाओ err_set_elem_expr;
		पूर्ण
	पूर्ण अन्यथा अगर (set->num_exprs > 0) अणु
		err = nft_set_elem_expr_clone(ctx, set, expr_array);
		अगर (err < 0)
			जाओ err_set_elem_expr_clone;

		num_exprs = set->num_exprs;
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_KEY]) अणु
		err = nft_setelem_parse_key(ctx, set, &elem.key.val,
					    nla[NFTA_SET_ELEM_KEY]);
		अगर (err < 0)
			जाओ err_set_elem_expr;

		nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_KEY, set->klen);
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_KEY_END]) अणु
		err = nft_setelem_parse_key(ctx, set, &elem.key_end.val,
					    nla[NFTA_SET_ELEM_KEY_END]);
		अगर (err < 0)
			जाओ err_parse_key;

		nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_KEY_END, set->klen);
	पूर्ण

	अगर (समयout > 0) अणु
		nft_set_ext_add(&पंचांगpl, NFT_SET_EXT_EXPIRATION);
		अगर (समयout != set->समयout)
			nft_set_ext_add(&पंचांगpl, NFT_SET_EXT_TIMEOUT);
	पूर्ण

	अगर (num_exprs) अणु
		क्रम (i = 0; i < num_exprs; i++)
			size += expr_array[i]->ops->size;

		nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_EXPRESSIONS,
				       माप(काष्ठा nft_set_elem_expr) +
				       size);
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_OBJREF] != शून्य) अणु
		अगर (!(set->flags & NFT_SET_OBJECT)) अणु
			err = -EINVAL;
			जाओ err_parse_key_end;
		पूर्ण
		obj = nft_obj_lookup(ctx->net, ctx->table,
				     nla[NFTA_SET_ELEM_OBJREF],
				     set->objtype, genmask);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ err_parse_key_end;
		पूर्ण
		nft_set_ext_add(&पंचांगpl, NFT_SET_EXT_OBJREF);
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_DATA] != शून्य) अणु
		err = nft_setelem_parse_data(ctx, set, &desc, &elem.data.val,
					     nla[NFTA_SET_ELEM_DATA]);
		अगर (err < 0)
			जाओ err_parse_key_end;

		dreg = nft_type_to_reg(set->dtype);
		list_क्रम_each_entry(binding, &set->bindings, list) अणु
			काष्ठा nft_ctx bind_ctx = अणु
				.net	= ctx->net,
				.family	= ctx->family,
				.table	= ctx->table,
				.chain	= (काष्ठा nft_chain *)binding->chain,
			पूर्ण;

			अगर (!(binding->flags & NFT_SET_MAP))
				जारी;

			err = nft_validate_रेजिस्टर_store(&bind_ctx, dreg,
							  &elem.data.val,
							  desc.type, desc.len);
			अगर (err < 0)
				जाओ err_parse_data;

			अगर (desc.type == NFT_DATA_VERDICT &&
			    (elem.data.val.verdict.code == NFT_GOTO ||
			     elem.data.val.verdict.code == NFT_JUMP))
				nft_validate_state_update(ctx->net,
							  NFT_VALIDATE_NEED);
		पूर्ण

		nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_DATA, desc.len);
	पूर्ण

	/* The full maximum length of userdata can exceed the maximum
	 * offset value (U8_MAX) क्रम following extensions, thereक्रम it
	 * must be the last extension added.
	 */
	ulen = 0;
	अगर (nla[NFTA_SET_ELEM_USERDATA] != शून्य) अणु
		ulen = nla_len(nla[NFTA_SET_ELEM_USERDATA]);
		अगर (ulen > 0)
			nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_USERDATA,
					       ulen);
	पूर्ण

	err = -ENOMEM;
	elem.priv = nft_set_elem_init(set, &पंचांगpl, elem.key.val.data,
				      elem.key_end.val.data, elem.data.val.data,
				      समयout, expiration, GFP_KERNEL);
	अगर (elem.priv == शून्य)
		जाओ err_parse_data;

	ext = nft_set_elem_ext(set, elem.priv);
	अगर (flags)
		*nft_set_ext_flags(ext) = flags;
	अगर (ulen > 0) अणु
		udata = nft_set_ext_userdata(ext);
		udata->len = ulen - 1;
		nla_स_नकल(&udata->data, nla[NFTA_SET_ELEM_USERDATA], ulen);
	पूर्ण
	अगर (obj) अणु
		*nft_set_ext_obj(ext) = obj;
		obj->use++;
	पूर्ण
	err = nft_set_elem_expr_setup(ctx, ext, expr_array, num_exprs);
	अगर (err < 0)
		जाओ err_elem_expr;

	trans = nft_trans_elem_alloc(ctx, NFT_MSG_NEWSETELEM, set);
	अगर (trans == शून्य) अणु
		err = -ENOMEM;
		जाओ err_elem_expr;
	पूर्ण

	ext->genmask = nft_genmask_cur(ctx->net) | NFT_SET_ELEM_BUSY_MASK;

	err = nft_setelem_insert(ctx->net, set, &elem, &ext2, flags);
	अगर (err) अणु
		अगर (err == -EEXIST) अणु
			अगर (nft_set_ext_exists(ext, NFT_SET_EXT_DATA) ^
			    nft_set_ext_exists(ext2, NFT_SET_EXT_DATA) ||
			    nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF) ^
			    nft_set_ext_exists(ext2, NFT_SET_EXT_OBJREF))
				जाओ err_element_clash;
			अगर ((nft_set_ext_exists(ext, NFT_SET_EXT_DATA) &&
			     nft_set_ext_exists(ext2, NFT_SET_EXT_DATA) &&
			     स_भेद(nft_set_ext_data(ext),
				    nft_set_ext_data(ext2), set->dlen) != 0) ||
			    (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF) &&
			     nft_set_ext_exists(ext2, NFT_SET_EXT_OBJREF) &&
			     *nft_set_ext_obj(ext) != *nft_set_ext_obj(ext2)))
				जाओ err_element_clash;
			अन्यथा अगर (!(nlmsg_flags & NLM_F_EXCL))
				err = 0;
		पूर्ण अन्यथा अगर (err == -ENOTEMPTY) अणु
			/* ENOTEMPTY reports overlapping between this element
			 * and an existing one.
			 */
			err = -EEXIST;
		पूर्ण
		जाओ err_element_clash;
	पूर्ण

	अगर (!(flags & NFT_SET_ELEM_CATCHALL) && set->size &&
	    !atomic_add_unless(&set->nelems, 1, set->size + set->ndeact)) अणु
		err = -ENखाता;
		जाओ err_set_full;
	पूर्ण

	nft_trans_elem(trans) = elem;
	nft_trans_commit_list_add_tail(ctx->net, trans);
	वापस 0;

err_set_full:
	nft_setelem_हटाओ(ctx->net, set, &elem);
err_element_clash:
	kमुक्त(trans);
err_elem_expr:
	अगर (obj)
		obj->use--;

	nf_tables_set_elem_destroy(ctx, set, elem.priv);
err_parse_data:
	अगर (nla[NFTA_SET_ELEM_DATA] != शून्य)
		nft_data_release(&elem.data.val, desc.type);
err_parse_key_end:
	nft_data_release(&elem.key_end.val, NFT_DATA_VALUE);
err_parse_key:
	nft_data_release(&elem.key.val, NFT_DATA_VALUE);
err_set_elem_expr:
	क्रम (i = 0; i < num_exprs && expr_array[i]; i++)
		nft_expr_destroy(ctx, expr_array[i]);
err_set_elem_expr_clone:
	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_newsetelem(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nfnl_info *info,
				स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(info->net);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_set *set;
	काष्ठा nft_ctx ctx;
	पूर्णांक rem, err;

	अगर (nla[NFTA_SET_ELEM_LIST_ELEMENTS] == शून्य)
		वापस -EINVAL;

	err = nft_ctx_init_from_elemattr(&ctx, net, skb, info->nlh, nla, extack,
					 genmask, NETLINK_CB(skb).portid);
	अगर (err < 0)
		वापस err;

	set = nft_set_lookup_global(net, ctx.table, nla[NFTA_SET_ELEM_LIST_SET],
				    nla[NFTA_SET_ELEM_LIST_SET_ID], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	अगर (!list_empty(&set->bindings) && set->flags & NFT_SET_CONSTANT)
		वापस -EBUSY;

	nla_क्रम_each_nested(attr, nla[NFTA_SET_ELEM_LIST_ELEMENTS], rem) अणु
		err = nft_add_set_elem(&ctx, set, attr, info->nlh->nlmsg_flags);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (nft_net->validate_state == NFT_VALIDATE_DO)
		वापस nft_table_validate(net, ctx.table);

	वापस 0;
पूर्ण

/**
 *	nft_data_hold - hold a nft_data item
 *
 *	@data: काष्ठा nft_data to release
 *	@type: type of data
 *
 *	Hold a nft_data item. NFT_DATA_VALUE types can be silently discarded,
 *	NFT_DATA_VERDICT bumps the reference to chains in हाल of NFT_JUMP and
 *	NFT_GOTO verdicts. This function must be called on active data objects
 *	from the second phase of the commit protocol.
 */
व्योम nft_data_hold(स्थिर काष्ठा nft_data *data, क्रमागत nft_data_types type)
अणु
	काष्ठा nft_chain *chain;
	काष्ठा nft_rule *rule;

	अगर (type == NFT_DATA_VERDICT) अणु
		चयन (data->verdict.code) अणु
		हाल NFT_JUMP:
		हाल NFT_GOTO:
			chain = data->verdict.chain;
			chain->use++;

			अगर (!nft_chain_is_bound(chain))
				अवरोध;

			chain->table->use++;
			list_क्रम_each_entry(rule, &chain->rules, list)
				chain->use++;

			nft_chain_add(chain->table, chain);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nft_setelem_data_activate(स्थिर काष्ठा net *net,
				      स्थिर काष्ठा nft_set *set,
				      काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_DATA))
		nft_data_hold(nft_set_ext_data(ext), set->dtype);
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF))
		(*nft_set_ext_obj(ext))->use++;
पूर्ण

अटल व्योम nft_setelem_data_deactivate(स्थिर काष्ठा net *net,
					स्थिर काष्ठा nft_set *set,
					काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_DATA))
		nft_data_release(nft_set_ext_data(ext), set->dtype);
	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF))
		(*nft_set_ext_obj(ext))->use--;
पूर्ण

अटल पूर्णांक nft_del_setelem(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			   स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *nla[NFTA_SET_ELEM_MAX + 1];
	काष्ठा nft_set_ext_पंचांगpl पंचांगpl;
	काष्ठा nft_set_elem elem;
	काष्ठा nft_set_ext *ext;
	काष्ठा nft_trans *trans;
	u32 flags = 0;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(nla, NFTA_SET_ELEM_MAX, attr,
					  nft_set_elem_policy, शून्य);
	अगर (err < 0)
		वापस err;

	err = nft_setelem_parse_flags(set, nla[NFTA_SET_ELEM_FLAGS], &flags);
	अगर (err < 0)
		वापस err;

	अगर (!nla[NFTA_SET_ELEM_KEY] && !(flags & NFT_SET_ELEM_CATCHALL))
		वापस -EINVAL;

	nft_set_ext_prepare(&पंचांगpl);

	अगर (flags != 0)
		nft_set_ext_add(&पंचांगpl, NFT_SET_EXT_FLAGS);

	अगर (nla[NFTA_SET_ELEM_KEY]) अणु
		err = nft_setelem_parse_key(ctx, set, &elem.key.val,
					    nla[NFTA_SET_ELEM_KEY]);
		अगर (err < 0)
			वापस err;

		nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_KEY, set->klen);
	पूर्ण

	अगर (nla[NFTA_SET_ELEM_KEY_END]) अणु
		err = nft_setelem_parse_key(ctx, set, &elem.key_end.val,
					    nla[NFTA_SET_ELEM_KEY_END]);
		अगर (err < 0)
			वापस err;

		nft_set_ext_add_length(&पंचांगpl, NFT_SET_EXT_KEY_END, set->klen);
	पूर्ण

	err = -ENOMEM;
	elem.priv = nft_set_elem_init(set, &पंचांगpl, elem.key.val.data,
				      elem.key_end.val.data, शून्य, 0, 0,
				      GFP_KERNEL);
	अगर (elem.priv == शून्य)
		जाओ fail_elem;

	ext = nft_set_elem_ext(set, elem.priv);
	अगर (flags)
		*nft_set_ext_flags(ext) = flags;

	trans = nft_trans_elem_alloc(ctx, NFT_MSG_DELSETELEM, set);
	अगर (trans == शून्य)
		जाओ fail_trans;

	err = nft_setelem_deactivate(ctx->net, set, &elem, flags);
	अगर (err < 0)
		जाओ fail_ops;

	nft_setelem_data_deactivate(ctx->net, set, &elem);

	nft_trans_elem(trans) = elem;
	nft_trans_commit_list_add_tail(ctx->net, trans);
	वापस 0;

fail_ops:
	kमुक्त(trans);
fail_trans:
	kमुक्त(elem.priv);
fail_elem:
	nft_data_release(&elem.key.val, NFT_DATA_VALUE);
	वापस err;
पूर्ण

अटल पूर्णांक nft_setelem_flush(स्थिर काष्ठा nft_ctx *ctx,
			     काष्ठा nft_set *set,
			     स्थिर काष्ठा nft_set_iter *iter,
			     काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_trans *trans;
	पूर्णांक err;

	trans = nft_trans_alloc_gfp(ctx, NFT_MSG_DELSETELEM,
				    माप(काष्ठा nft_trans_elem), GFP_ATOMIC);
	अगर (!trans)
		वापस -ENOMEM;

	अगर (!set->ops->flush(ctx->net, set, elem->priv)) अणु
		err = -ENOENT;
		जाओ err1;
	पूर्ण
	set->ndeact++;

	nft_setelem_data_deactivate(ctx->net, set, elem);
	nft_trans_elem_set(trans) = set;
	nft_trans_elem(trans) = *elem;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;
err1:
	kमुक्त(trans);
	वापस err;
पूर्ण

अटल पूर्णांक __nft_set_catchall_flush(स्थिर काष्ठा nft_ctx *ctx,
				    काष्ठा nft_set *set,
				    काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_trans *trans;

	trans = nft_trans_alloc_gfp(ctx, NFT_MSG_DELSETELEM,
				    माप(काष्ठा nft_trans_elem), GFP_KERNEL);
	अगर (!trans)
		वापस -ENOMEM;

	nft_setelem_data_deactivate(ctx->net, set, elem);
	nft_trans_elem_set(trans) = set;
	nft_trans_elem(trans) = *elem;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;
पूर्ण

अटल पूर्णांक nft_set_catchall_flush(स्थिर काष्ठा nft_ctx *ctx,
				  काष्ठा nft_set *set)
अणु
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_set_elem_catchall *catchall;
	काष्ठा nft_set_elem elem;
	काष्ठा nft_set_ext *ext;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (!nft_set_elem_active(ext, genmask) ||
		    nft_set_elem_mark_busy(ext))
			जारी;

		elem.priv = catchall->elem;
		ret = __nft_set_catchall_flush(ctx, set, &elem);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nft_set_flush(काष्ठा nft_ctx *ctx, काष्ठा nft_set *set, u8 genmask)
अणु
	काष्ठा nft_set_iter iter = अणु
		.genmask	= genmask,
		.fn		= nft_setelem_flush,
	पूर्ण;

	set->ops->walk(ctx, set, &iter);
	अगर (!iter.err)
		iter.err = nft_set_catchall_flush(ctx, set);

	वापस iter.err;
पूर्ण

अटल पूर्णांक nf_tables_dअन्यथाtelem(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nfnl_info *info,
				स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_set *set;
	काष्ठा nft_ctx ctx;
	पूर्णांक rem, err = 0;

	err = nft_ctx_init_from_elemattr(&ctx, net, skb, info->nlh, nla, extack,
					 genmask, NETLINK_CB(skb).portid);
	अगर (err < 0)
		वापस err;

	set = nft_set_lookup(ctx.table, nla[NFTA_SET_ELEM_LIST_SET], genmask);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);
	अगर (!list_empty(&set->bindings) && set->flags & NFT_SET_CONSTANT)
		वापस -EBUSY;

	अगर (!nla[NFTA_SET_ELEM_LIST_ELEMENTS])
		वापस nft_set_flush(&ctx, set, genmask);

	nla_क्रम_each_nested(attr, nla[NFTA_SET_ELEM_LIST_ELEMENTS], rem) अणु
		err = nft_del_setelem(&ctx, set, attr);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

व्योम nft_set_gc_batch_release(काष्ठा rcu_head *rcu)
अणु
	काष्ठा nft_set_gc_batch *gcb;
	अचिन्हित पूर्णांक i;

	gcb = container_of(rcu, काष्ठा nft_set_gc_batch, head.rcu);
	क्रम (i = 0; i < gcb->head.cnt; i++)
		nft_set_elem_destroy(gcb->head.set, gcb->elems[i], true);
	kमुक्त(gcb);
पूर्ण

काष्ठा nft_set_gc_batch *nft_set_gc_batch_alloc(स्थिर काष्ठा nft_set *set,
						gfp_t gfp)
अणु
	काष्ठा nft_set_gc_batch *gcb;

	gcb = kzalloc(माप(*gcb), gfp);
	अगर (gcb == शून्य)
		वापस gcb;
	gcb->head.set = set;
	वापस gcb;
पूर्ण

/*
 * Stateful objects
 */

/**
 *	nft_रेजिस्टर_obj- रेजिस्टर nf_tables stateful object type
 *	@obj_type: object type
 *
 *	Registers the object type क्रम use with nf_tables. Returns zero on
 *	success or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक nft_रेजिस्टर_obj(काष्ठा nft_object_type *obj_type)
अणु
	अगर (obj_type->type == NFT_OBJECT_UNSPEC)
		वापस -EINVAL;

	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	list_add_rcu(&obj_type->list, &nf_tables_objects);
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_रेजिस्टर_obj);

/**
 *	nft_unरेजिस्टर_obj - unरेजिस्टर nf_tables object type
 *	@obj_type: object type
 *
 * 	Unरेजिस्टरs the object type क्रम use with nf_tables.
 */
व्योम nft_unरेजिस्टर_obj(काष्ठा nft_object_type *obj_type)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	list_del_rcu(&obj_type->list);
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
पूर्ण
EXPORT_SYMBOL_GPL(nft_unरेजिस्टर_obj);

काष्ठा nft_object *nft_obj_lookup(स्थिर काष्ठा net *net,
				  स्थिर काष्ठा nft_table *table,
				  स्थिर काष्ठा nlattr *nla, u32 objtype,
				  u8 genmask)
अणु
	काष्ठा nft_object_hash_key k = अणु .table = table पूर्ण;
	अक्षर search[NFT_OBJ_MAXNAMELEN];
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा nft_object *obj;

	nla_strscpy(search, nla, माप(search));
	k.name = search;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() &&
		     !lockdep_commit_lock_is_held(net));

	rcu_पढ़ो_lock();
	list = rhltable_lookup(&nft_objname_ht, &k, nft_objname_ht_params);
	अगर (!list)
		जाओ out;

	rhl_क्रम_each_entry_rcu(obj, पंचांगp, list, rhlhead) अणु
		अगर (objtype == obj->ops->type->type &&
		    nft_active_genmask(obj, genmask)) अणु
			rcu_पढ़ो_unlock();
			वापस obj;
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL_GPL(nft_obj_lookup);

अटल काष्ठा nft_object *nft_obj_lookup_byhandle(स्थिर काष्ठा nft_table *table,
						  स्थिर काष्ठा nlattr *nla,
						  u32 objtype, u8 genmask)
अणु
	काष्ठा nft_object *obj;

	list_क्रम_each_entry(obj, &table->objects, list) अणु
		अगर (be64_to_cpu(nla_get_be64(nla)) == obj->handle &&
		    objtype == obj->ops->type->type &&
		    nft_active_genmask(obj, genmask))
			वापस obj;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_obj_policy[NFTA_OBJ_MAX + 1] = अणु
	[NFTA_OBJ_TABLE]	= अणु .type = NLA_STRING,
				    .len = NFT_TABLE_MAXNAMELEN - 1 पूर्ण,
	[NFTA_OBJ_NAME]		= अणु .type = NLA_STRING,
				    .len = NFT_OBJ_MAXNAMELEN - 1 पूर्ण,
	[NFTA_OBJ_TYPE]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_OBJ_DATA]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_OBJ_HANDLE]	= अणु .type = NLA_U64पूर्ण,
	[NFTA_OBJ_USERDATA]	= अणु .type = NLA_BINARY,
				    .len = NFT_USERDATA_MAXLEN पूर्ण,
पूर्ण;

अटल काष्ठा nft_object *nft_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				       स्थिर काष्ठा nft_object_type *type,
				       स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr **tb;
	स्थिर काष्ठा nft_object_ops *ops;
	काष्ठा nft_object *obj;
	पूर्णांक err = -ENOMEM;

	tb = kदो_स्मृति_array(type->maxattr + 1, माप(*tb), GFP_KERNEL);
	अगर (!tb)
		जाओ err1;

	अगर (attr) अणु
		err = nla_parse_nested_deprecated(tb, type->maxattr, attr,
						  type->policy, शून्य);
		अगर (err < 0)
			जाओ err2;
	पूर्ण अन्यथा अणु
		स_रखो(tb, 0, माप(tb[0]) * (type->maxattr + 1));
	पूर्ण

	अगर (type->select_ops) अणु
		ops = type->select_ops(ctx, (स्थिर काष्ठा nlattr * स्थिर *)tb);
		अगर (IS_ERR(ops)) अणु
			err = PTR_ERR(ops);
			जाओ err2;
		पूर्ण
	पूर्ण अन्यथा अणु
		ops = type->ops;
	पूर्ण

	err = -ENOMEM;
	obj = kzalloc(माप(*obj) + ops->size, GFP_KERNEL);
	अगर (!obj)
		जाओ err2;

	err = ops->init(ctx, (स्थिर काष्ठा nlattr * स्थिर *)tb, obj);
	अगर (err < 0)
		जाओ err3;

	obj->ops = ops;

	kमुक्त(tb);
	वापस obj;
err3:
	kमुक्त(obj);
err2:
	kमुक्त(tb);
err1:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक nft_object_dump(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक attr,
			   काष्ठा nft_object *obj, bool reset)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, attr);
	अगर (!nest)
		जाओ nla_put_failure;
	अगर (obj->ops->dump(skb, obj, reset) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nft_object_type *__nft_obj_type_get(u32 objtype)
अणु
	स्थिर काष्ठा nft_object_type *type;

	list_क्रम_each_entry(type, &nf_tables_objects, list) अणु
		अगर (objtype == type->type)
			वापस type;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nft_object_type *
nft_obj_type_get(काष्ठा net *net, u32 objtype)
अणु
	स्थिर काष्ठा nft_object_type *type;

	type = __nft_obj_type_get(objtype);
	अगर (type != शून्य && try_module_get(type->owner))
		वापस type;

	lockdep_nfnl_nft_mutex_not_held();
#अगर_घोषित CONFIG_MODULES
	अगर (type == शून्य) अणु
		अगर (nft_request_module(net, "nft-obj-%u", objtype) == -EAGAIN)
			वापस ERR_PTR(-EAGAIN);
	पूर्ण
#पूर्ण_अगर
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक nf_tables_upकरोbj(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_object_type *type,
			    स्थिर काष्ठा nlattr *attr,
			    काष्ठा nft_object *obj)
अणु
	काष्ठा nft_object *newobj;
	काष्ठा nft_trans *trans;
	पूर्णांक err;

	trans = nft_trans_alloc(ctx, NFT_MSG_NEWOBJ,
				माप(काष्ठा nft_trans_obj));
	अगर (!trans)
		वापस -ENOMEM;

	newobj = nft_obj_init(ctx, type, attr);
	अगर (IS_ERR(newobj)) अणु
		err = PTR_ERR(newobj);
		जाओ err_मुक्त_trans;
	पूर्ण

	nft_trans_obj(trans) = obj;
	nft_trans_obj_update(trans) = true;
	nft_trans_obj_newobj(trans) = newobj;
	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;

err_मुक्त_trans:
	kमुक्त(trans);
	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_newobj(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	स्थिर काष्ठा nft_object_type *type;
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा net *net = info->net;
	काष्ठा nft_table *table;
	काष्ठा nft_object *obj;
	काष्ठा nft_ctx ctx;
	u32 objtype;
	पूर्णांक err;

	अगर (!nla[NFTA_OBJ_TYPE] ||
	    !nla[NFTA_OBJ_NAME] ||
	    !nla[NFTA_OBJ_DATA])
		वापस -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_OBJ_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	objtype = ntohl(nla_get_be32(nla[NFTA_OBJ_TYPE]));
	obj = nft_obj_lookup(net, table, nla[NFTA_OBJ_NAME], objtype, genmask);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		अगर (err != -ENOENT) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_NAME]);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_NAME]);
			वापस -EEXIST;
		पूर्ण
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE)
			वापस -EOPNOTSUPP;

		type = __nft_obj_type_get(objtype);
		nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

		वापस nf_tables_upकरोbj(&ctx, type, nla[NFTA_OBJ_DATA], obj);
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

	type = nft_obj_type_get(net, objtype);
	अगर (IS_ERR(type))
		वापस PTR_ERR(type);

	obj = nft_obj_init(&ctx, type, nla[NFTA_OBJ_DATA]);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ err_init;
	पूर्ण
	obj->key.table = table;
	obj->handle = nf_tables_alloc_handle(table);

	obj->key.name = nla_strdup(nla[NFTA_OBJ_NAME], GFP_KERNEL);
	अगर (!obj->key.name) अणु
		err = -ENOMEM;
		जाओ err_strdup;
	पूर्ण

	अगर (nla[NFTA_OBJ_USERDATA]) अणु
		obj->udata = nla_memdup(nla[NFTA_OBJ_USERDATA], GFP_KERNEL);
		अगर (obj->udata == शून्य)
			जाओ err_userdata;

		obj->udlen = nla_len(nla[NFTA_OBJ_USERDATA]);
	पूर्ण

	err = nft_trans_obj_add(&ctx, NFT_MSG_NEWOBJ, obj);
	अगर (err < 0)
		जाओ err_trans;

	err = rhltable_insert(&nft_objname_ht, &obj->rhlhead,
			      nft_objname_ht_params);
	अगर (err < 0)
		जाओ err_obj_ht;

	list_add_tail_rcu(&obj->list, &table->objects);
	table->use++;
	वापस 0;
err_obj_ht:
	/* queued in transaction log */
	INIT_LIST_HEAD(&obj->list);
	वापस err;
err_trans:
	kमुक्त(obj->udata);
err_userdata:
	kमुक्त(obj->key.name);
err_strdup:
	अगर (obj->ops->destroy)
		obj->ops->destroy(&ctx, obj);
	kमुक्त(obj);
err_init:
	module_put(type->owner);
	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_fill_obj_info(काष्ठा sk_buff *skb, काष्ठा net *net,
				   u32 portid, u32 seq, पूर्णांक event, u32 flags,
				   पूर्णांक family, स्थिर काष्ठा nft_table *table,
				   काष्ठा nft_object *obj, bool reset)
अणु
	काष्ठा nlmsghdr *nlh;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, family,
			   NFNETLINK_V0, nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_OBJ_TABLE, table->name) ||
	    nla_put_string(skb, NFTA_OBJ_NAME, obj->key.name) ||
	    nla_put_be32(skb, NFTA_OBJ_TYPE, htonl(obj->ops->type->type)) ||
	    nla_put_be32(skb, NFTA_OBJ_USE, htonl(obj->use)) ||
	    nft_object_dump(skb, NFTA_OBJ_DATA, obj, reset) ||
	    nla_put_be64(skb, NFTA_OBJ_HANDLE, cpu_to_be64(obj->handle),
			 NFTA_OBJ_PAD))
		जाओ nla_put_failure;

	अगर (obj->udata &&
	    nla_put(skb, NFTA_OBJ_USERDATA, obj->udlen, obj->udata))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

काष्ठा nft_obj_filter अणु
	अक्षर		*table;
	u32		type;
पूर्ण;

अटल पूर्णांक nf_tables_dump_obj(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	स्थिर काष्ठा nft_table *table;
	अचिन्हित पूर्णांक idx = 0, s_idx = cb->args[0];
	काष्ठा nft_obj_filter *filter = cb->data;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_object *obj;
	bool reset = false;

	अगर (NFNL_MSG_TYPE(cb->nlh->nlmsg_type) == NFT_MSG_GETOBJ_RESET)
		reset = true;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	cb->seq = nft_net->base_seq;

	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (family != NFPROTO_UNSPEC && family != table->family)
			जारी;

		list_क्रम_each_entry_rcu(obj, &table->objects, list) अणु
			अगर (!nft_is_active(net, obj))
				जाओ cont;
			अगर (idx < s_idx)
				जाओ cont;
			अगर (idx > s_idx)
				स_रखो(&cb->args[1], 0,
				       माप(cb->args) - माप(cb->args[0]));
			अगर (filter && filter->table &&
			    म_भेद(filter->table, table->name))
				जाओ cont;
			अगर (filter &&
			    filter->type != NFT_OBJECT_UNSPEC &&
			    obj->ops->type->type != filter->type)
				जाओ cont;
			अगर (reset) अणु
				अक्षर *buf = kaप्र_लिखो(GFP_ATOMIC,
						      "%s:%u",
						      table->name,
						      nft_net->base_seq);

				audit_log_nfcfg(buf,
						family,
						obj->handle,
						AUDIT_NFT_OP_OBJ_RESET,
						GFP_ATOMIC);
				kमुक्त(buf);
			पूर्ण

			अगर (nf_tables_fill_obj_info(skb, net, NETLINK_CB(cb->skb).portid,
						    cb->nlh->nlmsg_seq,
						    NFT_MSG_NEWOBJ,
						    NLM_F_MULTI | NLM_F_APPEND,
						    table->family, table,
						    obj, reset) < 0)
				जाओ करोne;

			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();

	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nf_tables_dump_obj_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = cb->data;
	काष्ठा nft_obj_filter *filter = शून्य;

	अगर (nla[NFTA_OBJ_TABLE] || nla[NFTA_OBJ_TYPE]) अणु
		filter = kzalloc(माप(*filter), GFP_ATOMIC);
		अगर (!filter)
			वापस -ENOMEM;

		अगर (nla[NFTA_OBJ_TABLE]) अणु
			filter->table = nla_strdup(nla[NFTA_OBJ_TABLE], GFP_ATOMIC);
			अगर (!filter->table) अणु
				kमुक्त(filter);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		अगर (nla[NFTA_OBJ_TYPE])
			filter->type = ntohl(nla_get_be32(nla[NFTA_OBJ_TYPE]));
	पूर्ण

	cb->data = filter;
	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_dump_obj_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nft_obj_filter *filter = cb->data;

	अगर (filter) अणु
		kमुक्त(filter->table);
		kमुक्त(filter);
	पूर्ण

	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_getobj(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_cur(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	स्थिर काष्ठा nft_table *table;
	काष्ठा net *net = info->net;
	काष्ठा nft_object *obj;
	काष्ठा sk_buff *skb2;
	bool reset = false;
	u32 objtype;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = nf_tables_dump_obj_start,
			.dump = nf_tables_dump_obj,
			.करोne = nf_tables_dump_obj_करोne,
			.module = THIS_MODULE,
			.data = (व्योम *)nla,
		पूर्ण;

		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	अगर (!nla[NFTA_OBJ_NAME] ||
	    !nla[NFTA_OBJ_TYPE])
		वापस -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_OBJ_TABLE], family, genmask, 0);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	objtype = ntohl(nla_get_be32(nla[NFTA_OBJ_TYPE]));
	obj = nft_obj_lookup(net, table, nla[NFTA_OBJ_NAME], objtype, genmask);
	अगर (IS_ERR(obj)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_NAME]);
		वापस PTR_ERR(obj);
	पूर्ण

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb2)
		वापस -ENOMEM;

	अगर (NFNL_MSG_TYPE(info->nlh->nlmsg_type) == NFT_MSG_GETOBJ_RESET)
		reset = true;

	अगर (reset) अणु
		स्थिर काष्ठा nftables_pernet *nft_net;
		अक्षर *buf;

		nft_net = nft_pernet(net);
		buf = kaप्र_लिखो(GFP_ATOMIC, "%s:%u", table->name, nft_net->base_seq);

		audit_log_nfcfg(buf,
				family,
				obj->handle,
				AUDIT_NFT_OP_OBJ_RESET,
				GFP_ATOMIC);
		kमुक्त(buf);
	पूर्ण

	err = nf_tables_fill_obj_info(skb2, net, NETLINK_CB(skb).portid,
				      info->nlh->nlmsg_seq, NFT_MSG_NEWOBJ, 0,
				      family, table, obj, reset);
	अगर (err < 0)
		जाओ err_fill_obj_info;

	वापस nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_obj_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल व्योम nft_obj_destroy(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_object *obj)
अणु
	अगर (obj->ops->destroy)
		obj->ops->destroy(ctx, obj);

	module_put(obj->ops->type->owner);
	kमुक्त(obj->key.name);
	kमुक्त(obj->udata);
	kमुक्त(obj);
पूर्ण

अटल पूर्णांक nf_tables_delobj(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_table *table;
	काष्ठा nft_object *obj;
	काष्ठा nft_ctx ctx;
	u32 objtype;

	अगर (!nla[NFTA_OBJ_TYPE] ||
	    (!nla[NFTA_OBJ_NAME] && !nla[NFTA_OBJ_HANDLE]))
		वापस -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_OBJ_TABLE], family, genmask,
				 NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_OBJ_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	objtype = ntohl(nla_get_be32(nla[NFTA_OBJ_TYPE]));
	अगर (nla[NFTA_OBJ_HANDLE]) अणु
		attr = nla[NFTA_OBJ_HANDLE];
		obj = nft_obj_lookup_byhandle(table, attr, objtype, genmask);
	पूर्ण अन्यथा अणु
		attr = nla[NFTA_OBJ_NAME];
		obj = nft_obj_lookup(net, table, attr, objtype, genmask);
	पूर्ण

	अगर (IS_ERR(obj)) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस PTR_ERR(obj);
	पूर्ण
	अगर (obj->use > 0) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस -EBUSY;
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

	वापस nft_delobj(&ctx, obj);
पूर्ण

व्योम nft_obj_notअगरy(काष्ठा net *net, स्थिर काष्ठा nft_table *table,
		    काष्ठा nft_object *obj, u32 portid, u32 seq, पूर्णांक event,
		    पूर्णांक family, पूर्णांक report, gfp_t gfp)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा sk_buff *skb;
	पूर्णांक err;
	अक्षर *buf = kaप्र_लिखो(gfp, "%s:%u",
			      table->name, nft_net->base_seq);

	audit_log_nfcfg(buf,
			family,
			obj->handle,
			event == NFT_MSG_NEWOBJ ?
				 AUDIT_NFT_OP_OBJ_REGISTER :
				 AUDIT_NFT_OP_OBJ_UNREGISTER,
			gfp);
	kमुक्त(buf);

	अगर (!report &&
	    !nfnetlink_has_listeners(net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, gfp);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_obj_info(skb, net, portid, seq, event, 0, family,
				      table, obj, false);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_notअगरy_enqueue(skb, report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(net, portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण
EXPORT_SYMBOL_GPL(nft_obj_notअगरy);

अटल व्योम nf_tables_obj_notअगरy(स्थिर काष्ठा nft_ctx *ctx,
				 काष्ठा nft_object *obj, पूर्णांक event)
अणु
	nft_obj_notअगरy(ctx->net, ctx->table, obj, ctx->portid, ctx->seq, event,
		       ctx->family, ctx->report, GFP_KERNEL);
पूर्ण

/*
 * Flow tables
 */
व्योम nft_रेजिस्टर_flowtable_type(काष्ठा nf_flowtable_type *type)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	list_add_tail_rcu(&type->list, &nf_tables_flowtables);
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
पूर्ण
EXPORT_SYMBOL_GPL(nft_रेजिस्टर_flowtable_type);

व्योम nft_unरेजिस्टर_flowtable_type(काष्ठा nf_flowtable_type *type)
अणु
	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	list_del_rcu(&type->list);
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
पूर्ण
EXPORT_SYMBOL_GPL(nft_unरेजिस्टर_flowtable_type);

अटल स्थिर काष्ठा nla_policy nft_flowtable_policy[NFTA_FLOWTABLE_MAX + 1] = अणु
	[NFTA_FLOWTABLE_TABLE]		= अणु .type = NLA_STRING,
					    .len = NFT_NAME_MAXLEN - 1 पूर्ण,
	[NFTA_FLOWTABLE_NAME]		= अणु .type = NLA_STRING,
					    .len = NFT_NAME_MAXLEN - 1 पूर्ण,
	[NFTA_FLOWTABLE_HOOK]		= अणु .type = NLA_NESTED पूर्ण,
	[NFTA_FLOWTABLE_HANDLE]		= अणु .type = NLA_U64 पूर्ण,
	[NFTA_FLOWTABLE_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

काष्ठा nft_flowtable *nft_flowtable_lookup(स्थिर काष्ठा nft_table *table,
					   स्थिर काष्ठा nlattr *nla, u8 genmask)
अणु
	काष्ठा nft_flowtable *flowtable;

	list_क्रम_each_entry_rcu(flowtable, &table->flowtables, list) अणु
		अगर (!nla_म_भेद(nla, flowtable->name) &&
		    nft_active_genmask(flowtable, genmask))
			वापस flowtable;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL_GPL(nft_flowtable_lookup);

व्योम nf_tables_deactivate_flowtable(स्थिर काष्ठा nft_ctx *ctx,
				    काष्ठा nft_flowtable *flowtable,
				    क्रमागत nft_trans_phase phase)
अणु
	चयन (phase) अणु
	हाल NFT_TRANS_PREPARE:
	हाल NFT_TRANS_ABORT:
	हाल NFT_TRANS_RELEASE:
		flowtable->use--;
		fallthrough;
	शेष:
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_tables_deactivate_flowtable);

अटल काष्ठा nft_flowtable *
nft_flowtable_lookup_byhandle(स्थिर काष्ठा nft_table *table,
			      स्थिर काष्ठा nlattr *nla, u8 genmask)
अणु
       काष्ठा nft_flowtable *flowtable;

       list_क्रम_each_entry(flowtable, &table->flowtables, list) अणु
               अगर (be64_to_cpu(nla_get_be64(nla)) == flowtable->handle &&
                   nft_active_genmask(flowtable, genmask))
                       वापस flowtable;
       पूर्ण
       वापस ERR_PTR(-ENOENT);
पूर्ण

काष्ठा nft_flowtable_hook अणु
	u32			num;
	पूर्णांक			priority;
	काष्ठा list_head	list;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_flowtable_hook_policy[NFTA_FLOWTABLE_HOOK_MAX + 1] = अणु
	[NFTA_FLOWTABLE_HOOK_NUM]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_FLOWTABLE_HOOK_PRIORITY]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_FLOWTABLE_HOOK_DEVS]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nft_flowtable_parse_hook(स्थिर काष्ठा nft_ctx *ctx,
				    स्थिर काष्ठा nlattr *attr,
				    काष्ठा nft_flowtable_hook *flowtable_hook,
				    काष्ठा nft_flowtable *flowtable, bool add)
अणु
	काष्ठा nlattr *tb[NFTA_FLOWTABLE_HOOK_MAX + 1];
	काष्ठा nft_hook *hook;
	पूर्णांक hooknum, priority;
	पूर्णांक err;

	INIT_LIST_HEAD(&flowtable_hook->list);

	err = nla_parse_nested_deprecated(tb, NFTA_FLOWTABLE_HOOK_MAX, attr,
					  nft_flowtable_hook_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (add) अणु
		अगर (!tb[NFTA_FLOWTABLE_HOOK_NUM] ||
		    !tb[NFTA_FLOWTABLE_HOOK_PRIORITY])
			वापस -EINVAL;

		hooknum = ntohl(nla_get_be32(tb[NFTA_FLOWTABLE_HOOK_NUM]));
		अगर (hooknum != NF_NETDEV_INGRESS)
			वापस -EOPNOTSUPP;

		priority = ntohl(nla_get_be32(tb[NFTA_FLOWTABLE_HOOK_PRIORITY]));

		flowtable_hook->priority	= priority;
		flowtable_hook->num		= hooknum;
	पूर्ण अन्यथा अणु
		अगर (tb[NFTA_FLOWTABLE_HOOK_NUM]) अणु
			hooknum = ntohl(nla_get_be32(tb[NFTA_FLOWTABLE_HOOK_NUM]));
			अगर (hooknum != flowtable->hooknum)
				वापस -EOPNOTSUPP;
		पूर्ण

		अगर (tb[NFTA_FLOWTABLE_HOOK_PRIORITY]) अणु
			priority = ntohl(nla_get_be32(tb[NFTA_FLOWTABLE_HOOK_PRIORITY]));
			अगर (priority != flowtable->data.priority)
				वापस -EOPNOTSUPP;
		पूर्ण

		flowtable_hook->priority	= flowtable->data.priority;
		flowtable_hook->num		= flowtable->hooknum;
	पूर्ण

	अगर (tb[NFTA_FLOWTABLE_HOOK_DEVS]) अणु
		err = nf_tables_parse_netdev_hooks(ctx->net,
						   tb[NFTA_FLOWTABLE_HOOK_DEVS],
						   &flowtable_hook->list);
		अगर (err < 0)
			वापस err;
	पूर्ण

	list_क्रम_each_entry(hook, &flowtable_hook->list, list) अणु
		hook->ops.pf		= NFPROTO_NETDEV;
		hook->ops.hooknum	= flowtable_hook->num;
		hook->ops.priority	= flowtable_hook->priority;
		hook->ops.priv		= &flowtable->data;
		hook->ops.hook		= flowtable->data.type->hook;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nf_flowtable_type *__nft_flowtable_type_get(u8 family)
अणु
	स्थिर काष्ठा nf_flowtable_type *type;

	list_क्रम_each_entry(type, &nf_tables_flowtables, list) अणु
		अगर (family == type->family)
			वापस type;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nf_flowtable_type *
nft_flowtable_type_get(काष्ठा net *net, u8 family)
अणु
	स्थिर काष्ठा nf_flowtable_type *type;

	type = __nft_flowtable_type_get(family);
	अगर (type != शून्य && try_module_get(type->owner))
		वापस type;

	lockdep_nfnl_nft_mutex_not_held();
#अगर_घोषित CONFIG_MODULES
	अगर (type == शून्य) अणु
		अगर (nft_request_module(net, "nf-flowtable-%u", family) == -EAGAIN)
			वापस ERR_PTR(-EAGAIN);
	पूर्ण
#पूर्ण_अगर
	वापस ERR_PTR(-ENOENT);
पूर्ण

/* Only called from error and netdev event paths. */
अटल व्योम nft_unरेजिस्टर_flowtable_hook(काष्ठा net *net,
					  काष्ठा nft_flowtable *flowtable,
					  काष्ठा nft_hook *hook)
अणु
	nf_unरेजिस्टर_net_hook(net, &hook->ops);
	flowtable->data.type->setup(&flowtable->data, hook->ops.dev,
				    FLOW_BLOCK_UNBIND);
पूर्ण

अटल व्योम nft_unरेजिस्टर_flowtable_net_hooks(काष्ठा net *net,
					       काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook;

	list_क्रम_each_entry(hook, hook_list, list)
		nf_unरेजिस्टर_net_hook(net, &hook->ops);
पूर्ण

अटल पूर्णांक nft_रेजिस्टर_flowtable_net_hooks(काष्ठा net *net,
					    काष्ठा nft_table *table,
					    काष्ठा list_head *hook_list,
					    काष्ठा nft_flowtable *flowtable)
अणु
	काष्ठा nft_hook *hook, *hook2, *next;
	काष्ठा nft_flowtable *ft;
	पूर्णांक err, i = 0;

	list_क्रम_each_entry(hook, hook_list, list) अणु
		list_क्रम_each_entry(ft, &table->flowtables, list) अणु
			अगर (!nft_is_active_next(net, ft))
				जारी;

			list_क्रम_each_entry(hook2, &ft->hook_list, list) अणु
				अगर (hook->ops.dev == hook2->ops.dev &&
				    hook->ops.pf == hook2->ops.pf) अणु
					err = -EEXIST;
					जाओ err_unरेजिस्टर_net_hooks;
				पूर्ण
			पूर्ण
		पूर्ण

		err = flowtable->data.type->setup(&flowtable->data,
						  hook->ops.dev,
						  FLOW_BLOCK_BIND);
		अगर (err < 0)
			जाओ err_unरेजिस्टर_net_hooks;

		err = nf_रेजिस्टर_net_hook(net, &hook->ops);
		अगर (err < 0) अणु
			flowtable->data.type->setup(&flowtable->data,
						    hook->ops.dev,
						    FLOW_BLOCK_UNBIND);
			जाओ err_unरेजिस्टर_net_hooks;
		पूर्ण

		i++;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_net_hooks:
	list_क्रम_each_entry_safe(hook, next, hook_list, list) अणु
		अगर (i-- <= 0)
			अवरोध;

		nft_unरेजिस्टर_flowtable_hook(net, flowtable, hook);
		list_del_rcu(&hook->list);
		kमुक्त_rcu(hook, rcu);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम nft_flowtable_hooks_destroy(काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook, *next;

	list_क्रम_each_entry_safe(hook, next, hook_list, list) अणु
		list_del_rcu(&hook->list);
		kमुक्त_rcu(hook, rcu);
	पूर्ण
पूर्ण

अटल पूर्णांक nft_flowtable_update(काष्ठा nft_ctx *ctx, स्थिर काष्ठा nlmsghdr *nlh,
				काष्ठा nft_flowtable *flowtable)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = ctx->nla;
	काष्ठा nft_flowtable_hook flowtable_hook;
	काष्ठा nft_hook *hook, *next;
	काष्ठा nft_trans *trans;
	bool unरेजिस्टर = false;
	u32 flags;
	पूर्णांक err;

	err = nft_flowtable_parse_hook(ctx, nla[NFTA_FLOWTABLE_HOOK],
				       &flowtable_hook, flowtable, false);
	अगर (err < 0)
		वापस err;

	list_क्रम_each_entry_safe(hook, next, &flowtable_hook.list, list) अणु
		अगर (nft_hook_list_find(&flowtable->hook_list, hook)) अणु
			list_del(&hook->list);
			kमुक्त(hook);
		पूर्ण
	पूर्ण

	अगर (nla[NFTA_FLOWTABLE_FLAGS]) अणु
		flags = ntohl(nla_get_be32(nla[NFTA_FLOWTABLE_FLAGS]));
		अगर (flags & ~NFT_FLOWTABLE_MASK)
			वापस -EOPNOTSUPP;
		अगर ((flowtable->data.flags & NFT_FLOWTABLE_HW_OFFLOAD) ^
		    (flags & NFT_FLOWTABLE_HW_OFFLOAD))
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		flags = flowtable->data.flags;
	पूर्ण

	err = nft_रेजिस्टर_flowtable_net_hooks(ctx->net, ctx->table,
					       &flowtable_hook.list, flowtable);
	अगर (err < 0)
		जाओ err_flowtable_update_hook;

	trans = nft_trans_alloc(ctx, NFT_MSG_NEWFLOWTABLE,
				माप(काष्ठा nft_trans_flowtable));
	अगर (!trans) अणु
		unरेजिस्टर = true;
		err = -ENOMEM;
		जाओ err_flowtable_update_hook;
	पूर्ण

	nft_trans_flowtable_flags(trans) = flags;
	nft_trans_flowtable(trans) = flowtable;
	nft_trans_flowtable_update(trans) = true;
	INIT_LIST_HEAD(&nft_trans_flowtable_hooks(trans));
	list_splice(&flowtable_hook.list, &nft_trans_flowtable_hooks(trans));

	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;

err_flowtable_update_hook:
	list_क्रम_each_entry_safe(hook, next, &flowtable_hook.list, list) अणु
		अगर (unरेजिस्टर)
			nft_unरेजिस्टर_flowtable_hook(ctx->net, flowtable, hook);
		list_del_rcu(&hook->list);
		kमुक्त_rcu(hook, rcu);
	पूर्ण

	वापस err;

पूर्ण

अटल पूर्णांक nf_tables_newflowtable(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nfnl_info *info,
				  स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा nft_flowtable_hook flowtable_hook;
	u8 genmask = nft_genmask_next(info->net);
	स्थिर काष्ठा nf_flowtable_type *type;
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_flowtable *flowtable;
	काष्ठा nft_hook *hook, *next;
	काष्ठा net *net = info->net;
	काष्ठा nft_table *table;
	काष्ठा nft_ctx ctx;
	पूर्णांक err;

	अगर (!nla[NFTA_FLOWTABLE_TABLE] ||
	    !nla[NFTA_FLOWTABLE_NAME] ||
	    !nla[NFTA_FLOWTABLE_HOOK])
		वापस -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_FLOWTABLE_TABLE], family,
				 genmask, NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_FLOWTABLE_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	flowtable = nft_flowtable_lookup(table, nla[NFTA_FLOWTABLE_NAME],
					 genmask);
	अगर (IS_ERR(flowtable)) अणु
		err = PTR_ERR(flowtable);
		अगर (err != -ENOENT) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_FLOWTABLE_NAME]);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL) अणु
			NL_SET_BAD_ATTR(extack, nla[NFTA_FLOWTABLE_NAME]);
			वापस -EEXIST;
		पूर्ण

		nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

		वापस nft_flowtable_update(&ctx, info->nlh, flowtable);
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

	flowtable = kzalloc(माप(*flowtable), GFP_KERNEL);
	अगर (!flowtable)
		वापस -ENOMEM;

	flowtable->table = table;
	flowtable->handle = nf_tables_alloc_handle(table);
	INIT_LIST_HEAD(&flowtable->hook_list);

	flowtable->name = nla_strdup(nla[NFTA_FLOWTABLE_NAME], GFP_KERNEL);
	अगर (!flowtable->name) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	type = nft_flowtable_type_get(net, family);
	अगर (IS_ERR(type)) अणु
		err = PTR_ERR(type);
		जाओ err2;
	पूर्ण

	अगर (nla[NFTA_FLOWTABLE_FLAGS]) अणु
		flowtable->data.flags =
			ntohl(nla_get_be32(nla[NFTA_FLOWTABLE_FLAGS]));
		अगर (flowtable->data.flags & ~NFT_FLOWTABLE_MASK) अणु
			err = -EOPNOTSUPP;
			जाओ err3;
		पूर्ण
	पूर्ण

	ग_लिखो_pnet(&flowtable->data.net, net);
	flowtable->data.type = type;
	err = type->init(&flowtable->data);
	अगर (err < 0)
		जाओ err3;

	err = nft_flowtable_parse_hook(&ctx, nla[NFTA_FLOWTABLE_HOOK],
				       &flowtable_hook, flowtable, true);
	अगर (err < 0)
		जाओ err4;

	list_splice(&flowtable_hook.list, &flowtable->hook_list);
	flowtable->data.priority = flowtable_hook.priority;
	flowtable->hooknum = flowtable_hook.num;

	err = nft_रेजिस्टर_flowtable_net_hooks(ctx.net, table,
					       &flowtable->hook_list,
					       flowtable);
	अगर (err < 0) अणु
		nft_flowtable_hooks_destroy(&flowtable->hook_list);
		जाओ err4;
	पूर्ण

	err = nft_trans_flowtable_add(&ctx, NFT_MSG_NEWFLOWTABLE, flowtable);
	अगर (err < 0)
		जाओ err5;

	list_add_tail_rcu(&flowtable->list, &table->flowtables);
	table->use++;

	वापस 0;
err5:
	list_क्रम_each_entry_safe(hook, next, &flowtable->hook_list, list) अणु
		nft_unरेजिस्टर_flowtable_hook(net, flowtable, hook);
		list_del_rcu(&hook->list);
		kमुक्त_rcu(hook, rcu);
	पूर्ण
err4:
	flowtable->data.type->मुक्त(&flowtable->data);
err3:
	module_put(type->owner);
err2:
	kमुक्त(flowtable->name);
err1:
	kमुक्त(flowtable);
	वापस err;
पूर्ण

अटल व्योम nft_flowtable_hook_release(काष्ठा nft_flowtable_hook *flowtable_hook)
अणु
	काष्ठा nft_hook *this, *next;

	list_क्रम_each_entry_safe(this, next, &flowtable_hook->list, list) अणु
		list_del(&this->list);
		kमुक्त(this);
	पूर्ण
पूर्ण

अटल पूर्णांक nft_delflowtable_hook(काष्ठा nft_ctx *ctx,
				 काष्ठा nft_flowtable *flowtable)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = ctx->nla;
	काष्ठा nft_flowtable_hook flowtable_hook;
	काष्ठा nft_hook *this, *hook;
	काष्ठा nft_trans *trans;
	पूर्णांक err;

	err = nft_flowtable_parse_hook(ctx, nla[NFTA_FLOWTABLE_HOOK],
				       &flowtable_hook, flowtable, false);
	अगर (err < 0)
		वापस err;

	list_क्रम_each_entry(this, &flowtable_hook.list, list) अणु
		hook = nft_hook_list_find(&flowtable->hook_list, this);
		अगर (!hook) अणु
			err = -ENOENT;
			जाओ err_flowtable_del_hook;
		पूर्ण
		hook->inactive = true;
	पूर्ण

	trans = nft_trans_alloc(ctx, NFT_MSG_DELFLOWTABLE,
				माप(काष्ठा nft_trans_flowtable));
	अगर (!trans) अणु
		err = -ENOMEM;
		जाओ err_flowtable_del_hook;
	पूर्ण

	nft_trans_flowtable(trans) = flowtable;
	nft_trans_flowtable_update(trans) = true;
	INIT_LIST_HEAD(&nft_trans_flowtable_hooks(trans));
	nft_flowtable_hook_release(&flowtable_hook);

	nft_trans_commit_list_add_tail(ctx->net, trans);

	वापस 0;

err_flowtable_del_hook:
	list_क्रम_each_entry(this, &flowtable_hook.list, list) अणु
		hook = nft_hook_list_find(&flowtable->hook_list, this);
		अगर (!hook)
			अवरोध;

		hook->inactive = false;
	पूर्ण
	nft_flowtable_hook_release(&flowtable_hook);

	वापस err;
पूर्ण

अटल पूर्णांक nf_tables_delflowtable(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nfnl_info *info,
				  स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा netlink_ext_ack *extack = info->extack;
	u8 genmask = nft_genmask_next(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_flowtable *flowtable;
	काष्ठा net *net = info->net;
	स्थिर काष्ठा nlattr *attr;
	काष्ठा nft_table *table;
	काष्ठा nft_ctx ctx;

	अगर (!nla[NFTA_FLOWTABLE_TABLE] ||
	    (!nla[NFTA_FLOWTABLE_NAME] &&
	     !nla[NFTA_FLOWTABLE_HANDLE]))
		वापस -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_FLOWTABLE_TABLE], family,
				 genmask, NETLINK_CB(skb).portid);
	अगर (IS_ERR(table)) अणु
		NL_SET_BAD_ATTR(extack, nla[NFTA_FLOWTABLE_TABLE]);
		वापस PTR_ERR(table);
	पूर्ण

	अगर (nla[NFTA_FLOWTABLE_HANDLE]) अणु
		attr = nla[NFTA_FLOWTABLE_HANDLE];
		flowtable = nft_flowtable_lookup_byhandle(table, attr, genmask);
	पूर्ण अन्यथा अणु
		attr = nla[NFTA_FLOWTABLE_NAME];
		flowtable = nft_flowtable_lookup(table, attr, genmask);
	पूर्ण

	अगर (IS_ERR(flowtable)) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस PTR_ERR(flowtable);
	पूर्ण

	nft_ctx_init(&ctx, net, skb, info->nlh, family, table, शून्य, nla);

	अगर (nla[NFTA_FLOWTABLE_HOOK])
		वापस nft_delflowtable_hook(&ctx, flowtable);

	अगर (flowtable->use > 0) अणु
		NL_SET_BAD_ATTR(extack, attr);
		वापस -EBUSY;
	पूर्ण

	वापस nft_delflowtable(&ctx, flowtable);
पूर्ण

अटल पूर्णांक nf_tables_fill_flowtable_info(काष्ठा sk_buff *skb, काष्ठा net *net,
					 u32 portid, u32 seq, पूर्णांक event,
					 u32 flags, पूर्णांक family,
					 काष्ठा nft_flowtable *flowtable,
					 काष्ठा list_head *hook_list)
अणु
	काष्ठा nlattr *nest, *nest_devs;
	काष्ठा nft_hook *hook;
	काष्ठा nlmsghdr *nlh;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, family,
			   NFNETLINK_V0, nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_FLOWTABLE_TABLE, flowtable->table->name) ||
	    nla_put_string(skb, NFTA_FLOWTABLE_NAME, flowtable->name) ||
	    nla_put_be32(skb, NFTA_FLOWTABLE_USE, htonl(flowtable->use)) ||
	    nla_put_be64(skb, NFTA_FLOWTABLE_HANDLE, cpu_to_be64(flowtable->handle),
			 NFTA_FLOWTABLE_PAD) ||
	    nla_put_be32(skb, NFTA_FLOWTABLE_FLAGS, htonl(flowtable->data.flags)))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, NFTA_FLOWTABLE_HOOK);
	अगर (!nest)
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_FLOWTABLE_HOOK_NUM, htonl(flowtable->hooknum)) ||
	    nla_put_be32(skb, NFTA_FLOWTABLE_HOOK_PRIORITY, htonl(flowtable->data.priority)))
		जाओ nla_put_failure;

	nest_devs = nla_nest_start_noflag(skb, NFTA_FLOWTABLE_HOOK_DEVS);
	अगर (!nest_devs)
		जाओ nla_put_failure;

	list_क्रम_each_entry_rcu(hook, hook_list, list) अणु
		अगर (nla_put_string(skb, NFTA_DEVICE_NAME, hook->ops.dev->name))
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, nest_devs);
	nla_nest_end(skb, nest);

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -1;
पूर्ण

काष्ठा nft_flowtable_filter अणु
	अक्षर		*table;
पूर्ण;

अटल पूर्णांक nf_tables_dump_flowtable(काष्ठा sk_buff *skb,
				    काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	काष्ठा nft_flowtable_filter *filter = cb->data;
	अचिन्हित पूर्णांक idx = 0, s_idx = cb->args[0];
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_flowtable *flowtable;
	काष्ठा nftables_pernet *nft_net;
	स्थिर काष्ठा nft_table *table;

	rcu_पढ़ो_lock();
	nft_net = nft_pernet(net);
	cb->seq = nft_net->base_seq;

	list_क्रम_each_entry_rcu(table, &nft_net->tables, list) अणु
		अगर (family != NFPROTO_UNSPEC && family != table->family)
			जारी;

		list_क्रम_each_entry_rcu(flowtable, &table->flowtables, list) अणु
			अगर (!nft_is_active(net, flowtable))
				जाओ cont;
			अगर (idx < s_idx)
				जाओ cont;
			अगर (idx > s_idx)
				स_रखो(&cb->args[1], 0,
				       माप(cb->args) - माप(cb->args[0]));
			अगर (filter && filter->table &&
			    म_भेद(filter->table, table->name))
				जाओ cont;

			अगर (nf_tables_fill_flowtable_info(skb, net, NETLINK_CB(cb->skb).portid,
							  cb->nlh->nlmsg_seq,
							  NFT_MSG_NEWFLOWTABLE,
							  NLM_F_MULTI | NLM_F_APPEND,
							  table->family,
							  flowtable,
							  &flowtable->hook_list) < 0)
				जाओ करोne;

			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();

	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल पूर्णांक nf_tables_dump_flowtable_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlattr * स्थिर *nla = cb->data;
	काष्ठा nft_flowtable_filter *filter = शून्य;

	अगर (nla[NFTA_FLOWTABLE_TABLE]) अणु
		filter = kzalloc(माप(*filter), GFP_ATOMIC);
		अगर (!filter)
			वापस -ENOMEM;

		filter->table = nla_strdup(nla[NFTA_FLOWTABLE_TABLE],
					   GFP_ATOMIC);
		अगर (!filter->table) अणु
			kमुक्त(filter);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cb->data = filter;
	वापस 0;
पूर्ण

अटल पूर्णांक nf_tables_dump_flowtable_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nft_flowtable_filter *filter = cb->data;

	अगर (!filter)
		वापस 0;

	kमुक्त(filter->table);
	kमुक्त(filter);

	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल पूर्णांक nf_tables_getflowtable(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nfnl_info *info,
				  स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	स्थिर काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u8 genmask = nft_genmask_cur(info->net);
	पूर्णांक family = nfmsg->nfgen_family;
	काष्ठा nft_flowtable *flowtable;
	स्थिर काष्ठा nft_table *table;
	काष्ठा net *net = info->net;
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = nf_tables_dump_flowtable_start,
			.dump = nf_tables_dump_flowtable,
			.करोne = nf_tables_dump_flowtable_करोne,
			.module = THIS_MODULE,
			.data = (व्योम *)nla,
		पूर्ण;

		वापस nft_netlink_dump_start_rcu(info->sk, skb, info->nlh, &c);
	पूर्ण

	अगर (!nla[NFTA_FLOWTABLE_NAME])
		वापस -EINVAL;

	table = nft_table_lookup(net, nla[NFTA_FLOWTABLE_TABLE], family,
				 genmask, 0);
	अगर (IS_ERR(table))
		वापस PTR_ERR(table);

	flowtable = nft_flowtable_lookup(table, nla[NFTA_FLOWTABLE_NAME],
					 genmask);
	अगर (IS_ERR(flowtable))
		वापस PTR_ERR(flowtable);

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb2)
		वापस -ENOMEM;

	err = nf_tables_fill_flowtable_info(skb2, net, NETLINK_CB(skb).portid,
					    info->nlh->nlmsg_seq,
					    NFT_MSG_NEWFLOWTABLE, 0, family,
					    flowtable, &flowtable->hook_list);
	अगर (err < 0)
		जाओ err_fill_flowtable_info;

	वापस nfnetlink_unicast(skb2, net, NETLINK_CB(skb).portid);

err_fill_flowtable_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल व्योम nf_tables_flowtable_notअगरy(काष्ठा nft_ctx *ctx,
				       काष्ठा nft_flowtable *flowtable,
				       काष्ठा list_head *hook_list,
				       पूर्णांक event)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(ctx->net);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (!ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		वापस;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ err;

	err = nf_tables_fill_flowtable_info(skb, ctx->net, ctx->portid,
					    ctx->seq, event, 0,
					    ctx->family, flowtable, hook_list);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	nft_notअगरy_enqueue(skb, ctx->report, &nft_net->notअगरy_list);
	वापस;
err:
	nfnetlink_set_err(ctx->net, ctx->portid, NFNLGRP_NFTABLES, -ENOBUFS);
पूर्ण

अटल व्योम nf_tables_flowtable_destroy(काष्ठा nft_flowtable *flowtable)
अणु
	काष्ठा nft_hook *hook, *next;

	flowtable->data.type->मुक्त(&flowtable->data);
	list_क्रम_each_entry_safe(hook, next, &flowtable->hook_list, list) अणु
		flowtable->data.type->setup(&flowtable->data, hook->ops.dev,
					    FLOW_BLOCK_UNBIND);
		list_del_rcu(&hook->list);
		kमुक्त(hook);
	पूर्ण
	kमुक्त(flowtable->name);
	module_put(flowtable->data.type->owner);
	kमुक्त(flowtable);
पूर्ण

अटल पूर्णांक nf_tables_fill_gen_info(काष्ठा sk_buff *skb, काष्ठा net *net,
				   u32 portid, u32 seq)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nlmsghdr *nlh;
	अक्षर buf[TASK_COMM_LEN];
	पूर्णांक event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, NFT_MSG_NEWGEN);

	nlh = nfnl_msg_put(skb, portid, seq, event, 0, AF_UNSPEC,
			   NFNETLINK_V0, nft_base_seq(net));
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_GEN_ID, htonl(nft_net->base_seq)) ||
	    nla_put_be32(skb, NFTA_GEN_PROC_PID, htonl(task_pid_nr(current))) ||
	    nla_put_string(skb, NFTA_GEN_PROC_NAME, get_task_comm(buf, current)))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम nft_flowtable_event(अचिन्हित दीर्घ event, काष्ठा net_device *dev,
				काष्ठा nft_flowtable *flowtable)
अणु
	काष्ठा nft_hook *hook;

	list_क्रम_each_entry(hook, &flowtable->hook_list, list) अणु
		अगर (hook->ops.dev != dev)
			जारी;

		/* flow_offload_netdev_event() cleans up entries क्रम us. */
		nft_unरेजिस्टर_flowtable_hook(dev_net(dev), flowtable, hook);
		list_del_rcu(&hook->list);
		kमुक्त_rcu(hook, rcu);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nf_tables_flowtable_event(काष्ठा notअगरier_block *this,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा nft_flowtable *flowtable;
	काष्ठा nftables_pernet *nft_net;
	काष्ठा nft_table *table;
	काष्ठा net *net;

	अगर (event != NETDEV_UNREGISTER)
		वापस 0;

	net = dev_net(dev);
	nft_net = nft_pernet(net);
	mutex_lock(&nft_net->commit_mutex);
	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		list_क्रम_each_entry(flowtable, &table->flowtables, list) अणु
			nft_flowtable_event(event, dev, flowtable);
		पूर्ण
	पूर्ण
	mutex_unlock(&nft_net->commit_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nf_tables_flowtable_notअगरier = अणु
	.notअगरier_call	= nf_tables_flowtable_event,
पूर्ण;

अटल व्योम nf_tables_gen_notअगरy(काष्ठा net *net, काष्ठा sk_buff *skb,
				 पूर्णांक event)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(skb);
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (!nlmsg_report(nlh) &&
	    !nfnetlink_has_listeners(net, NFNLGRP_NFTABLES))
		वापस;

	skb2 = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (skb2 == शून्य)
		जाओ err;

	err = nf_tables_fill_gen_info(skb2, net, NETLINK_CB(skb).portid,
				      nlh->nlmsg_seq);
	अगर (err < 0) अणु
		kमुक्त_skb(skb2);
		जाओ err;
	पूर्ण

	nfnetlink_send(skb2, net, NETLINK_CB(skb).portid, NFNLGRP_NFTABLES,
		       nlmsg_report(nlh), GFP_KERNEL);
	वापस;
err:
	nfnetlink_set_err(net, NETLINK_CB(skb).portid, NFNLGRP_NFTABLES,
			  -ENOBUFS);
पूर्ण

अटल पूर्णांक nf_tables_getgen(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			    स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (skb2 == शून्य)
		वापस -ENOMEM;

	err = nf_tables_fill_gen_info(skb2, info->net, NETLINK_CB(skb).portid,
				      info->nlh->nlmsg_seq);
	अगर (err < 0)
		जाओ err_fill_gen_info;

	वापस nfnetlink_unicast(skb2, info->net, NETLINK_CB(skb).portid);

err_fill_gen_info:
	kमुक्त_skb(skb2);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nfnl_callback nf_tables_cb[NFT_MSG_MAX] = अणु
	[NFT_MSG_NEWTABLE] = अणु
		.call		= nf_tables_newtable,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_TABLE_MAX,
		.policy		= nft_table_policy,
	पूर्ण,
	[NFT_MSG_GETTABLE] = अणु
		.call		= nf_tables_gettable,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_TABLE_MAX,
		.policy		= nft_table_policy,
	पूर्ण,
	[NFT_MSG_DELTABLE] = अणु
		.call		= nf_tables_deltable,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_TABLE_MAX,
		.policy		= nft_table_policy,
	पूर्ण,
	[NFT_MSG_NEWCHAIN] = अणु
		.call		= nf_tables_newchain,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_CHAIN_MAX,
		.policy		= nft_chain_policy,
	पूर्ण,
	[NFT_MSG_GETCHAIN] = अणु
		.call		= nf_tables_अ_लोhain,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_CHAIN_MAX,
		.policy		= nft_chain_policy,
	पूर्ण,
	[NFT_MSG_DELCHAIN] = अणु
		.call		= nf_tables_delchain,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_CHAIN_MAX,
		.policy		= nft_chain_policy,
	पूर्ण,
	[NFT_MSG_NEWRULE] = अणु
		.call		= nf_tables_newrule,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_RULE_MAX,
		.policy		= nft_rule_policy,
	पूर्ण,
	[NFT_MSG_GETRULE] = अणु
		.call		= nf_tables_getrule,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_RULE_MAX,
		.policy		= nft_rule_policy,
	पूर्ण,
	[NFT_MSG_DELRULE] = अणु
		.call		= nf_tables_delrule,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_RULE_MAX,
		.policy		= nft_rule_policy,
	पूर्ण,
	[NFT_MSG_NEWSET] = अणु
		.call		= nf_tables_newset,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_SET_MAX,
		.policy		= nft_set_policy,
	पूर्ण,
	[NFT_MSG_GETSET] = अणु
		.call		= nf_tables_माला_लोet,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_SET_MAX,
		.policy		= nft_set_policy,
	पूर्ण,
	[NFT_MSG_DELSET] = अणु
		.call		= nf_tables_dअन्यथाt,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_SET_MAX,
		.policy		= nft_set_policy,
	पूर्ण,
	[NFT_MSG_NEWSETELEM] = अणु
		.call		= nf_tables_newsetelem,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_SET_ELEM_LIST_MAX,
		.policy		= nft_set_elem_list_policy,
	पूर्ण,
	[NFT_MSG_GETSETELEM] = अणु
		.call		= nf_tables_माला_लोetelem,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_SET_ELEM_LIST_MAX,
		.policy		= nft_set_elem_list_policy,
	पूर्ण,
	[NFT_MSG_DELSETELEM] = अणु
		.call		= nf_tables_dअन्यथाtelem,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_SET_ELEM_LIST_MAX,
		.policy		= nft_set_elem_list_policy,
	पूर्ण,
	[NFT_MSG_GETGEN] = अणु
		.call		= nf_tables_getgen,
		.type		= NFNL_CB_RCU,
	पूर्ण,
	[NFT_MSG_NEWOBJ] = अणु
		.call		= nf_tables_newobj,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_OBJ_MAX,
		.policy		= nft_obj_policy,
	पूर्ण,
	[NFT_MSG_GETOBJ] = अणु
		.call		= nf_tables_getobj,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_OBJ_MAX,
		.policy		= nft_obj_policy,
	पूर्ण,
	[NFT_MSG_DELOBJ] = अणु
		.call		= nf_tables_delobj,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_OBJ_MAX,
		.policy		= nft_obj_policy,
	पूर्ण,
	[NFT_MSG_GETOBJ_RESET] = अणु
		.call		= nf_tables_getobj,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_OBJ_MAX,
		.policy		= nft_obj_policy,
	पूर्ण,
	[NFT_MSG_NEWFLOWTABLE] = अणु
		.call		= nf_tables_newflowtable,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_FLOWTABLE_MAX,
		.policy		= nft_flowtable_policy,
	पूर्ण,
	[NFT_MSG_GETFLOWTABLE] = अणु
		.call		= nf_tables_getflowtable,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFTA_FLOWTABLE_MAX,
		.policy		= nft_flowtable_policy,
	पूर्ण,
	[NFT_MSG_DELFLOWTABLE] = अणु
		.call		= nf_tables_delflowtable,
		.type		= NFNL_CB_BATCH,
		.attr_count	= NFTA_FLOWTABLE_MAX,
		.policy		= nft_flowtable_policy,
	पूर्ण,
पूर्ण;

अटल पूर्णांक nf_tables_validate(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_table *table;

	चयन (nft_net->validate_state) अणु
	हाल NFT_VALIDATE_SKIP:
		अवरोध;
	हाल NFT_VALIDATE_NEED:
		nft_validate_state_update(net, NFT_VALIDATE_DO);
		fallthrough;
	हाल NFT_VALIDATE_DO:
		list_क्रम_each_entry(table, &nft_net->tables, list) अणु
			अगर (nft_table_validate(net, table) < 0)
				वापस -EAGAIN;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* a drop policy has to be deferred until all rules have been activated,
 * otherwise a large ruleset that contains a drop-policy base chain will
 * cause all packets to get dropped until the full transaction has been
 * processed.
 *
 * We defer the drop policy until the transaction has been finalized.
 */
अटल व्योम nft_chain_commit_drop_policy(काष्ठा nft_trans *trans)
अणु
	काष्ठा nft_base_chain *basechain;

	अगर (nft_trans_chain_policy(trans) != NF_DROP)
		वापस;

	अगर (!nft_is_base_chain(trans->ctx.chain))
		वापस;

	basechain = nft_base_chain(trans->ctx.chain);
	basechain->policy = NF_DROP;
पूर्ण

अटल व्योम nft_chain_commit_update(काष्ठा nft_trans *trans)
अणु
	काष्ठा nft_base_chain *basechain;

	अगर (nft_trans_chain_name(trans)) अणु
		rhltable_हटाओ(&trans->ctx.table->chains_ht,
				&trans->ctx.chain->rhlhead,
				nft_chain_ht_params);
		swap(trans->ctx.chain->name, nft_trans_chain_name(trans));
		rhltable_insert_key(&trans->ctx.table->chains_ht,
				    trans->ctx.chain->name,
				    &trans->ctx.chain->rhlhead,
				    nft_chain_ht_params);
	पूर्ण

	अगर (!nft_is_base_chain(trans->ctx.chain))
		वापस;

	nft_chain_stats_replace(trans);

	basechain = nft_base_chain(trans->ctx.chain);

	चयन (nft_trans_chain_policy(trans)) अणु
	हाल NF_DROP:
	हाल NF_ACCEPT:
		basechain->policy = nft_trans_chain_policy(trans);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nft_obj_commit_update(काष्ठा nft_trans *trans)
अणु
	काष्ठा nft_object *newobj;
	काष्ठा nft_object *obj;

	obj = nft_trans_obj(trans);
	newobj = nft_trans_obj_newobj(trans);

	अगर (obj->ops->update)
		obj->ops->update(obj, newobj);

	kमुक्त(newobj);
पूर्ण

अटल व्योम nft_commit_release(काष्ठा nft_trans *trans)
अणु
	चयन (trans->msg_type) अणु
	हाल NFT_MSG_DELTABLE:
		nf_tables_table_destroy(&trans->ctx);
		अवरोध;
	हाल NFT_MSG_NEWCHAIN:
		मुक्त_percpu(nft_trans_chain_stats(trans));
		kमुक्त(nft_trans_chain_name(trans));
		अवरोध;
	हाल NFT_MSG_DELCHAIN:
		nf_tables_chain_destroy(&trans->ctx);
		अवरोध;
	हाल NFT_MSG_DELRULE:
		nf_tables_rule_destroy(&trans->ctx, nft_trans_rule(trans));
		अवरोध;
	हाल NFT_MSG_DELSET:
		nft_set_destroy(&trans->ctx, nft_trans_set(trans));
		अवरोध;
	हाल NFT_MSG_DELSETELEM:
		nf_tables_set_elem_destroy(&trans->ctx,
					   nft_trans_elem_set(trans),
					   nft_trans_elem(trans).priv);
		अवरोध;
	हाल NFT_MSG_DELOBJ:
		nft_obj_destroy(&trans->ctx, nft_trans_obj(trans));
		अवरोध;
	हाल NFT_MSG_DELFLOWTABLE:
		अगर (nft_trans_flowtable_update(trans))
			nft_flowtable_hooks_destroy(&nft_trans_flowtable_hooks(trans));
		अन्यथा
			nf_tables_flowtable_destroy(nft_trans_flowtable(trans));
		अवरोध;
	पूर्ण

	अगर (trans->put_net)
		put_net(trans->ctx.net);

	kमुक्त(trans);
पूर्ण

अटल व्योम nf_tables_trans_destroy_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nft_trans *trans, *next;
	LIST_HEAD(head);

	spin_lock(&nf_tables_destroy_list_lock);
	list_splice_init(&nf_tables_destroy_list, &head);
	spin_unlock(&nf_tables_destroy_list_lock);

	अगर (list_empty(&head))
		वापस;

	synchronize_rcu();

	list_क्रम_each_entry_safe(trans, next, &head, list) अणु
		list_del(&trans->list);
		nft_commit_release(trans);
	पूर्ण
पूर्ण

व्योम nf_tables_trans_destroy_flush_work(व्योम)
अणु
	flush_work(&trans_destroy_work);
पूर्ण
EXPORT_SYMBOL_GPL(nf_tables_trans_destroy_flush_work);

अटल पूर्णांक nf_tables_commit_chain_prepare(काष्ठा net *net, काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_rule *rule;
	अचिन्हित पूर्णांक alloc = 0;
	पूर्णांक i;

	/* alपढ़ोy handled or inactive chain? */
	अगर (chain->rules_next || !nft_is_active_next(net, chain))
		वापस 0;

	rule = list_entry(&chain->rules, काष्ठा nft_rule, list);
	i = 0;

	list_क्रम_each_entry_जारी(rule, &chain->rules, list) अणु
		अगर (nft_is_active_next(net, rule))
			alloc++;
	पूर्ण

	chain->rules_next = nf_tables_chain_alloc_rules(chain, alloc);
	अगर (!chain->rules_next)
		वापस -ENOMEM;

	list_क्रम_each_entry_जारी(rule, &chain->rules, list) अणु
		अगर (nft_is_active_next(net, rule))
			chain->rules_next[i++] = rule;
	पूर्ण

	chain->rules_next[i] = शून्य;
	वापस 0;
पूर्ण

अटल व्योम nf_tables_commit_chain_prepare_cancel(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_trans *trans, *next;

	list_क्रम_each_entry_safe(trans, next, &nft_net->commit_list, list) अणु
		काष्ठा nft_chain *chain = trans->ctx.chain;

		अगर (trans->msg_type == NFT_MSG_NEWRULE ||
		    trans->msg_type == NFT_MSG_DELRULE) अणु
			kvमुक्त(chain->rules_next);
			chain->rules_next = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __nf_tables_commit_chain_मुक्त_rules_old(काष्ठा rcu_head *h)
अणु
	काष्ठा nft_rules_old *o = container_of(h, काष्ठा nft_rules_old, h);

	kvमुक्त(o->start);
पूर्ण

अटल व्योम nf_tables_commit_chain_मुक्त_rules_old(काष्ठा nft_rule **rules)
अणु
	काष्ठा nft_rule **r = rules;
	काष्ठा nft_rules_old *old;

	जबतक (*r)
		r++;

	r++;	/* rcu_head is after end marker */
	old = (व्योम *) r;
	old->start = rules;

	call_rcu(&old->h, __nf_tables_commit_chain_मुक्त_rules_old);
पूर्ण

अटल व्योम nf_tables_commit_chain(काष्ठा net *net, काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_rule **g0, **g1;
	bool next_genbit;

	next_genbit = nft_gencursor_next(net);

	g0 = rcu_dereference_रक्षित(chain->rules_gen_0,
				       lockdep_commit_lock_is_held(net));
	g1 = rcu_dereference_रक्षित(chain->rules_gen_1,
				       lockdep_commit_lock_is_held(net));

	/* No changes to this chain? */
	अगर (chain->rules_next == शून्य) अणु
		/* chain had no change in last or next generation */
		अगर (g0 == g1)
			वापस;
		/*
		 * chain had no change in this generation; make sure next
		 * one uses same rules as current generation.
		 */
		अगर (next_genbit) अणु
			rcu_assign_poपूर्णांकer(chain->rules_gen_1, g0);
			nf_tables_commit_chain_मुक्त_rules_old(g1);
		पूर्ण अन्यथा अणु
			rcu_assign_poपूर्णांकer(chain->rules_gen_0, g1);
			nf_tables_commit_chain_मुक्त_rules_old(g0);
		पूर्ण

		वापस;
	पूर्ण

	अगर (next_genbit)
		rcu_assign_poपूर्णांकer(chain->rules_gen_1, chain->rules_next);
	अन्यथा
		rcu_assign_poपूर्णांकer(chain->rules_gen_0, chain->rules_next);

	chain->rules_next = शून्य;

	अगर (g0 == g1)
		वापस;

	अगर (next_genbit)
		nf_tables_commit_chain_मुक्त_rules_old(g1);
	अन्यथा
		nf_tables_commit_chain_मुक्त_rules_old(g0);
पूर्ण

अटल व्योम nft_obj_del(काष्ठा nft_object *obj)
अणु
	rhltable_हटाओ(&nft_objname_ht, &obj->rhlhead, nft_objname_ht_params);
	list_del_rcu(&obj->list);
पूर्ण

व्योम nft_chain_del(काष्ठा nft_chain *chain)
अणु
	काष्ठा nft_table *table = chain->table;

	WARN_ON_ONCE(rhltable_हटाओ(&table->chains_ht, &chain->rhlhead,
				     nft_chain_ht_params));
	list_del_rcu(&chain->list);
पूर्ण

अटल व्योम nft_flowtable_hooks_del(काष्ठा nft_flowtable *flowtable,
				    काष्ठा list_head *hook_list)
अणु
	काष्ठा nft_hook *hook, *next;

	list_क्रम_each_entry_safe(hook, next, &flowtable->hook_list, list) अणु
		अगर (hook->inactive)
			list_move(&hook->list, hook_list);
	पूर्ण
पूर्ण

अटल व्योम nf_tables_module_स्वतःload_cleanup(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_module_request *req, *next;

	WARN_ON_ONCE(!list_empty(&nft_net->commit_list));
	list_क्रम_each_entry_safe(req, next, &nft_net->module_list, list) अणु
		WARN_ON_ONCE(!req->करोne);
		list_del(&req->list);
		kमुक्त(req);
	पूर्ण
पूर्ण

अटल व्योम nf_tables_commit_release(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_trans *trans;

	/* all side effects have to be made visible.
	 * For example, अगर a chain named 'foo' has been deleted, a
	 * new transaction must not find it anymore.
	 *
	 * Memory reclaim happens asynchronously from work queue
	 * to prevent expensive synchronize_rcu() in commit phase.
	 */
	अगर (list_empty(&nft_net->commit_list)) अणु
		nf_tables_module_स्वतःload_cleanup(net);
		mutex_unlock(&nft_net->commit_mutex);
		वापस;
	पूर्ण

	trans = list_last_entry(&nft_net->commit_list,
				काष्ठा nft_trans, list);
	get_net(trans->ctx.net);
	WARN_ON_ONCE(trans->put_net);

	trans->put_net = true;
	spin_lock(&nf_tables_destroy_list_lock);
	list_splice_tail_init(&nft_net->commit_list, &nf_tables_destroy_list);
	spin_unlock(&nf_tables_destroy_list_lock);

	nf_tables_module_स्वतःload_cleanup(net);
	schedule_work(&trans_destroy_work);

	mutex_unlock(&nft_net->commit_mutex);
पूर्ण

अटल व्योम nft_commit_notअगरy(काष्ठा net *net, u32 portid)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा sk_buff *batch_skb = शून्य, *nskb, *skb;
	अचिन्हित अक्षर *data;
	पूर्णांक len;

	list_क्रम_each_entry_safe(skb, nskb, &nft_net->notअगरy_list, list) अणु
		अगर (!batch_skb) अणु
new_batch:
			batch_skb = skb;
			len = NLMSG_GOODSIZE - skb->len;
			list_del(&skb->list);
			जारी;
		पूर्ण
		len -= skb->len;
		अगर (len > 0 && NFT_CB(skb).report == NFT_CB(batch_skb).report) अणु
			data = skb_put(batch_skb, skb->len);
			स_नकल(data, skb->data, skb->len);
			list_del(&skb->list);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण
		nfnetlink_send(batch_skb, net, portid, NFNLGRP_NFTABLES,
			       NFT_CB(batch_skb).report, GFP_KERNEL);
		जाओ new_batch;
	पूर्ण

	अगर (batch_skb) अणु
		nfnetlink_send(batch_skb, net, portid, NFNLGRP_NFTABLES,
			       NFT_CB(batch_skb).report, GFP_KERNEL);
	पूर्ण

	WARN_ON_ONCE(!list_empty(&nft_net->notअगरy_list));
पूर्ण

अटल पूर्णांक nf_tables_commit_audit_alloc(काष्ठा list_head *adl,
					काष्ठा nft_table *table)
अणु
	काष्ठा nft_audit_data *adp;

	list_क्रम_each_entry(adp, adl, list) अणु
		अगर (adp->table == table)
			वापस 0;
	पूर्ण
	adp = kzalloc(माप(*adp), GFP_KERNEL);
	अगर (!adp)
		वापस -ENOMEM;
	adp->table = table;
	list_add(&adp->list, adl);
	वापस 0;
पूर्ण

अटल व्योम nf_tables_commit_audit_collect(काष्ठा list_head *adl,
					   काष्ठा nft_table *table, u32 op)
अणु
	काष्ठा nft_audit_data *adp;

	list_क्रम_each_entry(adp, adl, list) अणु
		अगर (adp->table == table)
			जाओ found;
	पूर्ण
	WARN_ONCE(1, "table=%s not expected in commit list", table->name);
	वापस;
found:
	adp->entries++;
	अगर (!adp->op || adp->op > op)
		adp->op = op;
पूर्ण

#घोषणा AUNFTABLENAMELEN (NFT_TABLE_MAXNAMELEN + 22)

अटल व्योम nf_tables_commit_audit_log(काष्ठा list_head *adl, u32 generation)
अणु
	काष्ठा nft_audit_data *adp, *adn;
	अक्षर aubuf[AUNFTABLENAMELEN];

	list_क्रम_each_entry_safe(adp, adn, adl, list) अणु
		snम_लिखो(aubuf, AUNFTABLENAMELEN, "%s:%u", adp->table->name,
			 generation);
		audit_log_nfcfg(aubuf, adp->table->family, adp->entries,
				nft2audit_op[adp->op], GFP_KERNEL);
		list_del(&adp->list);
		kमुक्त(adp);
	पूर्ण
पूर्ण

अटल पूर्णांक nf_tables_commit(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_trans *trans, *next;
	काष्ठा nft_trans_elem *te;
	काष्ठा nft_chain *chain;
	काष्ठा nft_table *table;
	LIST_HEAD(adl);
	पूर्णांक err;

	अगर (list_empty(&nft_net->commit_list)) अणु
		mutex_unlock(&nft_net->commit_mutex);
		वापस 0;
	पूर्ण

	/* 0. Validate ruleset, otherwise roll back क्रम error reporting. */
	अगर (nf_tables_validate(net) < 0)
		वापस -EAGAIN;

	err = nft_flow_rule_offload_commit(net);
	अगर (err < 0)
		वापस err;

	/* 1.  Allocate space क्रम next generation rules_gen_X[] */
	list_क्रम_each_entry_safe(trans, next, &nft_net->commit_list, list) अणु
		पूर्णांक ret;

		ret = nf_tables_commit_audit_alloc(&adl, trans->ctx.table);
		अगर (ret) अणु
			nf_tables_commit_chain_prepare_cancel(net);
			वापस ret;
		पूर्ण
		अगर (trans->msg_type == NFT_MSG_NEWRULE ||
		    trans->msg_type == NFT_MSG_DELRULE) अणु
			chain = trans->ctx.chain;

			ret = nf_tables_commit_chain_prepare(net, chain);
			अगर (ret < 0) अणु
				nf_tables_commit_chain_prepare_cancel(net);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/* step 2.  Make rules_gen_X visible to packet path */
	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		list_क्रम_each_entry(chain, &table->chains, list)
			nf_tables_commit_chain(net, chain);
	पूर्ण

	/*
	 * Bump generation counter, invalidate any dump in progress.
	 * Cannot fail after this poपूर्णांक.
	 */
	जबतक (++nft_net->base_seq == 0)
		;

	/* step 3. Start new generation, rules_gen_X now in use. */
	net->nft.gencursor = nft_gencursor_next(net);

	list_क्रम_each_entry_safe(trans, next, &nft_net->commit_list, list) अणु
		nf_tables_commit_audit_collect(&adl, trans->ctx.table,
					       trans->msg_type);
		चयन (trans->msg_type) अणु
		हाल NFT_MSG_NEWTABLE:
			अगर (nft_trans_table_update(trans)) अणु
				अगर (!(trans->ctx.table->flags & __NFT_TABLE_F_UPDATE)) अणु
					nft_trans_destroy(trans);
					अवरोध;
				पूर्ण
				अगर (trans->ctx.table->flags & NFT_TABLE_F_DORMANT)
					nf_tables_table_disable(net, trans->ctx.table);

				trans->ctx.table->flags &= ~__NFT_TABLE_F_UPDATE;
			पूर्ण अन्यथा अणु
				nft_clear(net, trans->ctx.table);
			पूर्ण
			nf_tables_table_notअगरy(&trans->ctx, NFT_MSG_NEWTABLE);
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_DELTABLE:
			list_del_rcu(&trans->ctx.table->list);
			nf_tables_table_notअगरy(&trans->ctx, NFT_MSG_DELTABLE);
			अवरोध;
		हाल NFT_MSG_NEWCHAIN:
			अगर (nft_trans_chain_update(trans)) अणु
				nft_chain_commit_update(trans);
				nf_tables_chain_notअगरy(&trans->ctx, NFT_MSG_NEWCHAIN);
				/* trans destroyed after rcu grace period */
			पूर्ण अन्यथा अणु
				nft_chain_commit_drop_policy(trans);
				nft_clear(net, trans->ctx.chain);
				nf_tables_chain_notअगरy(&trans->ctx, NFT_MSG_NEWCHAIN);
				nft_trans_destroy(trans);
			पूर्ण
			अवरोध;
		हाल NFT_MSG_DELCHAIN:
			nft_chain_del(trans->ctx.chain);
			nf_tables_chain_notअगरy(&trans->ctx, NFT_MSG_DELCHAIN);
			nf_tables_unरेजिस्टर_hook(trans->ctx.net,
						  trans->ctx.table,
						  trans->ctx.chain);
			अवरोध;
		हाल NFT_MSG_NEWRULE:
			nft_clear(trans->ctx.net, nft_trans_rule(trans));
			nf_tables_rule_notअगरy(&trans->ctx,
					      nft_trans_rule(trans),
					      NFT_MSG_NEWRULE);
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_DELRULE:
			list_del_rcu(&nft_trans_rule(trans)->list);
			nf_tables_rule_notअगरy(&trans->ctx,
					      nft_trans_rule(trans),
					      NFT_MSG_DELRULE);
			nft_rule_expr_deactivate(&trans->ctx,
						 nft_trans_rule(trans),
						 NFT_TRANS_COMMIT);
			अवरोध;
		हाल NFT_MSG_NEWSET:
			nft_clear(net, nft_trans_set(trans));
			/* This aव्योमs hitting -EBUSY when deleting the table
			 * from the transaction.
			 */
			अगर (nft_set_is_anonymous(nft_trans_set(trans)) &&
			    !list_empty(&nft_trans_set(trans)->bindings))
				trans->ctx.table->use--;

			nf_tables_set_notअगरy(&trans->ctx, nft_trans_set(trans),
					     NFT_MSG_NEWSET, GFP_KERNEL);
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_DELSET:
			list_del_rcu(&nft_trans_set(trans)->list);
			nf_tables_set_notअगरy(&trans->ctx, nft_trans_set(trans),
					     NFT_MSG_DELSET, GFP_KERNEL);
			अवरोध;
		हाल NFT_MSG_NEWSETELEM:
			te = (काष्ठा nft_trans_elem *)trans->data;

			nft_setelem_activate(net, te->set, &te->elem);
			nf_tables_setelem_notअगरy(&trans->ctx, te->set,
						 &te->elem,
						 NFT_MSG_NEWSETELEM, 0);
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_DELSETELEM:
			te = (काष्ठा nft_trans_elem *)trans->data;

			nf_tables_setelem_notअगरy(&trans->ctx, te->set,
						 &te->elem,
						 NFT_MSG_DELSETELEM, 0);
			nft_setelem_हटाओ(net, te->set, &te->elem);
			अगर (!nft_setelem_is_catchall(te->set, &te->elem)) अणु
				atomic_dec(&te->set->nelems);
				te->set->ndeact--;
			पूर्ण
			अवरोध;
		हाल NFT_MSG_NEWOBJ:
			अगर (nft_trans_obj_update(trans)) अणु
				nft_obj_commit_update(trans);
				nf_tables_obj_notअगरy(&trans->ctx,
						     nft_trans_obj(trans),
						     NFT_MSG_NEWOBJ);
			पूर्ण अन्यथा अणु
				nft_clear(net, nft_trans_obj(trans));
				nf_tables_obj_notअगरy(&trans->ctx,
						     nft_trans_obj(trans),
						     NFT_MSG_NEWOBJ);
				nft_trans_destroy(trans);
			पूर्ण
			अवरोध;
		हाल NFT_MSG_DELOBJ:
			nft_obj_del(nft_trans_obj(trans));
			nf_tables_obj_notअगरy(&trans->ctx, nft_trans_obj(trans),
					     NFT_MSG_DELOBJ);
			अवरोध;
		हाल NFT_MSG_NEWFLOWTABLE:
			अगर (nft_trans_flowtable_update(trans)) अणु
				nft_trans_flowtable(trans)->data.flags =
					nft_trans_flowtable_flags(trans);
				nf_tables_flowtable_notअगरy(&trans->ctx,
							   nft_trans_flowtable(trans),
							   &nft_trans_flowtable_hooks(trans),
							   NFT_MSG_NEWFLOWTABLE);
				list_splice(&nft_trans_flowtable_hooks(trans),
					    &nft_trans_flowtable(trans)->hook_list);
			पूर्ण अन्यथा अणु
				nft_clear(net, nft_trans_flowtable(trans));
				nf_tables_flowtable_notअगरy(&trans->ctx,
							   nft_trans_flowtable(trans),
							   &nft_trans_flowtable(trans)->hook_list,
							   NFT_MSG_NEWFLOWTABLE);
			पूर्ण
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_DELFLOWTABLE:
			अगर (nft_trans_flowtable_update(trans)) अणु
				nft_flowtable_hooks_del(nft_trans_flowtable(trans),
							&nft_trans_flowtable_hooks(trans));
				nf_tables_flowtable_notअगरy(&trans->ctx,
							   nft_trans_flowtable(trans),
							   &nft_trans_flowtable_hooks(trans),
							   NFT_MSG_DELFLOWTABLE);
				nft_unरेजिस्टर_flowtable_net_hooks(net,
								   &nft_trans_flowtable_hooks(trans));
			पूर्ण अन्यथा अणु
				list_del_rcu(&nft_trans_flowtable(trans)->list);
				nf_tables_flowtable_notअगरy(&trans->ctx,
							   nft_trans_flowtable(trans),
							   &nft_trans_flowtable(trans)->hook_list,
							   NFT_MSG_DELFLOWTABLE);
				nft_unरेजिस्टर_flowtable_net_hooks(net,
						&nft_trans_flowtable(trans)->hook_list);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	nft_commit_notअगरy(net, NETLINK_CB(skb).portid);
	nf_tables_gen_notअगरy(net, skb, NFT_MSG_NEWGEN);
	nf_tables_commit_audit_log(&adl, nft_net->base_seq);
	nf_tables_commit_release(net);

	वापस 0;
पूर्ण

अटल व्योम nf_tables_module_स्वतःload(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_module_request *req, *next;
	LIST_HEAD(module_list);

	list_splice_init(&nft_net->module_list, &module_list);
	mutex_unlock(&nft_net->commit_mutex);
	list_क्रम_each_entry_safe(req, next, &module_list, list) अणु
		request_module("%s", req->module);
		req->करोne = true;
	पूर्ण
	mutex_lock(&nft_net->commit_mutex);
	list_splice(&module_list, &nft_net->module_list);
पूर्ण

अटल व्योम nf_tables_पात_release(काष्ठा nft_trans *trans)
अणु
	चयन (trans->msg_type) अणु
	हाल NFT_MSG_NEWTABLE:
		nf_tables_table_destroy(&trans->ctx);
		अवरोध;
	हाल NFT_MSG_NEWCHAIN:
		nf_tables_chain_destroy(&trans->ctx);
		अवरोध;
	हाल NFT_MSG_NEWRULE:
		nf_tables_rule_destroy(&trans->ctx, nft_trans_rule(trans));
		अवरोध;
	हाल NFT_MSG_NEWSET:
		nft_set_destroy(&trans->ctx, nft_trans_set(trans));
		अवरोध;
	हाल NFT_MSG_NEWSETELEM:
		nft_set_elem_destroy(nft_trans_elem_set(trans),
				     nft_trans_elem(trans).priv, true);
		अवरोध;
	हाल NFT_MSG_NEWOBJ:
		nft_obj_destroy(&trans->ctx, nft_trans_obj(trans));
		अवरोध;
	हाल NFT_MSG_NEWFLOWTABLE:
		अगर (nft_trans_flowtable_update(trans))
			nft_flowtable_hooks_destroy(&nft_trans_flowtable_hooks(trans));
		अन्यथा
			nf_tables_flowtable_destroy(nft_trans_flowtable(trans));
		अवरोध;
	पूर्ण
	kमुक्त(trans);
पूर्ण

अटल पूर्णांक __nf_tables_पात(काष्ठा net *net, क्रमागत nfnl_पात_action action)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_trans *trans, *next;
	काष्ठा nft_trans_elem *te;
	काष्ठा nft_hook *hook;

	अगर (action == NFNL_ABORT_VALIDATE &&
	    nf_tables_validate(net) < 0)
		वापस -EAGAIN;

	list_क्रम_each_entry_safe_reverse(trans, next, &nft_net->commit_list,
					 list) अणु
		चयन (trans->msg_type) अणु
		हाल NFT_MSG_NEWTABLE:
			अगर (nft_trans_table_update(trans)) अणु
				अगर (!(trans->ctx.table->flags & __NFT_TABLE_F_UPDATE)) अणु
					nft_trans_destroy(trans);
					अवरोध;
				पूर्ण
				अगर (trans->ctx.table->flags & __NFT_TABLE_F_WAS_DORMANT) अणु
					nf_tables_table_disable(net, trans->ctx.table);
					trans->ctx.table->flags |= NFT_TABLE_F_DORMANT;
				पूर्ण अन्यथा अगर (trans->ctx.table->flags & __NFT_TABLE_F_WAS_AWAKEN) अणु
					trans->ctx.table->flags &= ~NFT_TABLE_F_DORMANT;
				पूर्ण
				trans->ctx.table->flags &= ~__NFT_TABLE_F_UPDATE;
				nft_trans_destroy(trans);
			पूर्ण अन्यथा अणु
				list_del_rcu(&trans->ctx.table->list);
			पूर्ण
			अवरोध;
		हाल NFT_MSG_DELTABLE:
			nft_clear(trans->ctx.net, trans->ctx.table);
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_NEWCHAIN:
			अगर (nft_trans_chain_update(trans)) अणु
				मुक्त_percpu(nft_trans_chain_stats(trans));
				kमुक्त(nft_trans_chain_name(trans));
				nft_trans_destroy(trans);
			पूर्ण अन्यथा अणु
				अगर (nft_chain_is_bound(trans->ctx.chain)) अणु
					nft_trans_destroy(trans);
					अवरोध;
				पूर्ण
				trans->ctx.table->use--;
				nft_chain_del(trans->ctx.chain);
				nf_tables_unरेजिस्टर_hook(trans->ctx.net,
							  trans->ctx.table,
							  trans->ctx.chain);
			पूर्ण
			अवरोध;
		हाल NFT_MSG_DELCHAIN:
			trans->ctx.table->use++;
			nft_clear(trans->ctx.net, trans->ctx.chain);
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_NEWRULE:
			trans->ctx.chain->use--;
			list_del_rcu(&nft_trans_rule(trans)->list);
			nft_rule_expr_deactivate(&trans->ctx,
						 nft_trans_rule(trans),
						 NFT_TRANS_ABORT);
			अवरोध;
		हाल NFT_MSG_DELRULE:
			trans->ctx.chain->use++;
			nft_clear(trans->ctx.net, nft_trans_rule(trans));
			nft_rule_expr_activate(&trans->ctx, nft_trans_rule(trans));
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_NEWSET:
			trans->ctx.table->use--;
			अगर (nft_trans_set_bound(trans)) अणु
				nft_trans_destroy(trans);
				अवरोध;
			पूर्ण
			list_del_rcu(&nft_trans_set(trans)->list);
			अवरोध;
		हाल NFT_MSG_DELSET:
			trans->ctx.table->use++;
			nft_clear(trans->ctx.net, nft_trans_set(trans));
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_NEWSETELEM:
			अगर (nft_trans_elem_set_bound(trans)) अणु
				nft_trans_destroy(trans);
				अवरोध;
			पूर्ण
			te = (काष्ठा nft_trans_elem *)trans->data;
			nft_setelem_हटाओ(net, te->set, &te->elem);
			अगर (!nft_setelem_is_catchall(te->set, &te->elem))
				atomic_dec(&te->set->nelems);
			अवरोध;
		हाल NFT_MSG_DELSETELEM:
			te = (काष्ठा nft_trans_elem *)trans->data;

			nft_setelem_data_activate(net, te->set, &te->elem);
			nft_setelem_activate(net, te->set, &te->elem);
			अगर (!nft_setelem_is_catchall(te->set, &te->elem))
				te->set->ndeact--;

			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_NEWOBJ:
			अगर (nft_trans_obj_update(trans)) अणु
				kमुक्त(nft_trans_obj_newobj(trans));
				nft_trans_destroy(trans);
			पूर्ण अन्यथा अणु
				trans->ctx.table->use--;
				nft_obj_del(nft_trans_obj(trans));
			पूर्ण
			अवरोध;
		हाल NFT_MSG_DELOBJ:
			trans->ctx.table->use++;
			nft_clear(trans->ctx.net, nft_trans_obj(trans));
			nft_trans_destroy(trans);
			अवरोध;
		हाल NFT_MSG_NEWFLOWTABLE:
			अगर (nft_trans_flowtable_update(trans)) अणु
				nft_unरेजिस्टर_flowtable_net_hooks(net,
						&nft_trans_flowtable_hooks(trans));
			पूर्ण अन्यथा अणु
				trans->ctx.table->use--;
				list_del_rcu(&nft_trans_flowtable(trans)->list);
				nft_unरेजिस्टर_flowtable_net_hooks(net,
						&nft_trans_flowtable(trans)->hook_list);
			पूर्ण
			अवरोध;
		हाल NFT_MSG_DELFLOWTABLE:
			अगर (nft_trans_flowtable_update(trans)) अणु
				list_क्रम_each_entry(hook, &nft_trans_flowtable(trans)->hook_list, list)
					hook->inactive = false;
			पूर्ण अन्यथा अणु
				trans->ctx.table->use++;
				nft_clear(trans->ctx.net, nft_trans_flowtable(trans));
			पूर्ण
			nft_trans_destroy(trans);
			अवरोध;
		पूर्ण
	पूर्ण

	synchronize_rcu();

	list_क्रम_each_entry_safe_reverse(trans, next,
					 &nft_net->commit_list, list) अणु
		list_del(&trans->list);
		nf_tables_पात_release(trans);
	पूर्ण

	अगर (action == NFNL_ABORT_AUTOLOAD)
		nf_tables_module_स्वतःload(net);
	अन्यथा
		nf_tables_module_स्वतःload_cleanup(net);

	वापस 0;
पूर्ण

अटल व्योम nf_tables_cleanup(काष्ठा net *net)
अणु
	nft_validate_state_update(net, NFT_VALIDATE_SKIP);
पूर्ण

अटल पूर्णांक nf_tables_पात(काष्ठा net *net, काष्ठा sk_buff *skb,
			   क्रमागत nfnl_पात_action action)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	पूर्णांक ret = __nf_tables_पात(net, action);

	mutex_unlock(&nft_net->commit_mutex);

	वापस ret;
पूर्ण

अटल bool nf_tables_valid_genid(काष्ठा net *net, u32 genid)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	bool genid_ok;

	mutex_lock(&nft_net->commit_mutex);

	genid_ok = genid == 0 || nft_net->base_seq == genid;
	अगर (!genid_ok)
		mutex_unlock(&nft_net->commit_mutex);

	/* अन्यथा, commit mutex has to be released by commit or पात function */
	वापस genid_ok;
पूर्ण

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nf_tables_subsys = अणु
	.name		= "nf_tables",
	.subsys_id	= NFNL_SUBSYS_NFTABLES,
	.cb_count	= NFT_MSG_MAX,
	.cb		= nf_tables_cb,
	.commit		= nf_tables_commit,
	.पात		= nf_tables_पात,
	.cleanup	= nf_tables_cleanup,
	.valid_genid	= nf_tables_valid_genid,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक nft_chain_validate_dependency(स्थिर काष्ठा nft_chain *chain,
				  क्रमागत nft_chain_types type)
अणु
	स्थिर काष्ठा nft_base_chain *basechain;

	अगर (nft_is_base_chain(chain)) अणु
		basechain = nft_base_chain(chain);
		अगर (basechain->type->type != type)
			वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_chain_validate_dependency);

पूर्णांक nft_chain_validate_hooks(स्थिर काष्ठा nft_chain *chain,
			     अचिन्हित पूर्णांक hook_flags)
अणु
	काष्ठा nft_base_chain *basechain;

	अगर (nft_is_base_chain(chain)) अणु
		basechain = nft_base_chain(chain);

		अगर ((1 << basechain->ops.hooknum) & hook_flags)
			वापस 0;

		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_chain_validate_hooks);

/*
 * Loop detection - walk through the ruleset beginning at the destination chain
 * of a new jump until either the source chain is reached (loop) or all
 * reachable chains have been traversed.
 *
 * The loop check is perक्रमmed whenever a new jump verdict is added to an
 * expression or verdict map or a verdict map is bound to a new chain.
 */

अटल पूर्णांक nf_tables_check_loops(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_chain *chain);

अटल पूर्णांक nft_check_loops(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_set_ext *ext)
अणु
	स्थिर काष्ठा nft_data *data;
	पूर्णांक ret;

	data = nft_set_ext_data(ext);
	चयन (data->verdict.code) अणु
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		ret = nf_tables_check_loops(ctx, data->verdict.chain);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nf_tables_loop_check_setelem(स्थिर काष्ठा nft_ctx *ctx,
					काष्ठा nft_set *set,
					स्थिर काष्ठा nft_set_iter *iter,
					काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_FLAGS) &&
	    *nft_set_ext_flags(ext) & NFT_SET_ELEM_INTERVAL_END)
		वापस 0;

	वापस nft_check_loops(ctx, ext);
पूर्ण

अटल पूर्णांक nft_set_catchall_loops(स्थिर काष्ठा nft_ctx *ctx,
				  काष्ठा nft_set *set)
अणु
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nft_set_elem_catchall *catchall;
	काष्ठा nft_set_ext *ext;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_rcu(catchall, &set->catchall_list, list) अणु
		ext = nft_set_elem_ext(set, catchall->elem);
		अगर (!nft_set_elem_active(ext, genmask))
			जारी;

		ret = nft_check_loops(ctx, ext);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nf_tables_check_loops(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_chain *chain)
अणु
	स्थिर काष्ठा nft_rule *rule;
	स्थिर काष्ठा nft_expr *expr, *last;
	काष्ठा nft_set *set;
	काष्ठा nft_set_binding *binding;
	काष्ठा nft_set_iter iter;

	अगर (ctx->chain == chain)
		वापस -ELOOP;

	list_क्रम_each_entry(rule, &chain->rules, list) अणु
		nft_rule_क्रम_each_expr(expr, last, rule) अणु
			काष्ठा nft_immediate_expr *priv;
			स्थिर काष्ठा nft_data *data;
			पूर्णांक err;

			अगर (म_भेद(expr->ops->type->name, "immediate"))
				जारी;

			priv = nft_expr_priv(expr);
			अगर (priv->dreg != NFT_REG_VERDICT)
				जारी;

			data = &priv->data;
			चयन (data->verdict.code) अणु
			हाल NFT_JUMP:
			हाल NFT_GOTO:
				err = nf_tables_check_loops(ctx,
							data->verdict.chain);
				अगर (err < 0)
					वापस err;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(set, &ctx->table->sets, list) अणु
		अगर (!nft_is_active_next(ctx->net, set))
			जारी;
		अगर (!(set->flags & NFT_SET_MAP) ||
		    set->dtype != NFT_DATA_VERDICT)
			जारी;

		list_क्रम_each_entry(binding, &set->bindings, list) अणु
			अगर (!(binding->flags & NFT_SET_MAP) ||
			    binding->chain != chain)
				जारी;

			iter.genmask	= nft_genmask_next(ctx->net);
			iter.skip 	= 0;
			iter.count	= 0;
			iter.err	= 0;
			iter.fn		= nf_tables_loop_check_setelem;

			set->ops->walk(ctx, set, &iter);
			अगर (!iter.err)
				iter.err = nft_set_catchall_loops(ctx, set);

			अगर (iter.err < 0)
				वापस iter.err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	nft_parse_u32_check - fetch u32 attribute and check क्रम maximum value
 *
 *	@attr: netlink attribute to fetch value from
 *	@max: maximum value to be stored in dest
 *	@dest: poपूर्णांकer to the variable
 *
 *	Parse, check and store a given u32 netlink attribute पूर्णांकo variable.
 *	This function वापसs -दुस्फल अगर the value goes over maximum value.
 *	Otherwise a 0 is वापसed and the attribute value is stored in the
 *	destination variable.
 */
पूर्णांक nft_parse_u32_check(स्थिर काष्ठा nlattr *attr, पूर्णांक max, u32 *dest)
अणु
	u32 val;

	val = ntohl(nla_get_be32(attr));
	अगर (val > max)
		वापस -दुस्फल;

	*dest = val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_parse_u32_check);

अटल अचिन्हित पूर्णांक nft_parse_रेजिस्टर(स्थिर काष्ठा nlattr *attr)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ntohl(nla_get_be32(attr));
	चयन (reg) अणु
	हाल NFT_REG_VERDICT...NFT_REG_4:
		वापस reg * NFT_REG_SIZE / NFT_REG32_SIZE;
	शेष:
		वापस reg + NFT_REG_SIZE / NFT_REG32_SIZE - NFT_REG32_00;
	पूर्ण
पूर्ण

/**
 *	nft_dump_रेजिस्टर - dump a रेजिस्टर value to a netlink attribute
 *
 *	@skb: socket buffer
 *	@attr: attribute number
 *	@reg: रेजिस्टर number
 *
 *	Conकाष्ठा a netlink attribute containing the रेजिस्टर number. For
 *	compatibility reasons, रेजिस्टर numbers being a multiple of 4 are
 *	translated to the corresponding 128 bit रेजिस्टर numbers.
 */
पूर्णांक nft_dump_रेजिस्टर(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक attr, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg % (NFT_REG_SIZE / NFT_REG32_SIZE) == 0)
		reg = reg / (NFT_REG_SIZE / NFT_REG32_SIZE);
	अन्यथा
		reg = reg - NFT_REG_SIZE / NFT_REG32_SIZE + NFT_REG32_00;

	वापस nla_put_be32(skb, attr, htonl(reg));
पूर्ण
EXPORT_SYMBOL_GPL(nft_dump_रेजिस्टर);

अटल पूर्णांक nft_validate_रेजिस्टर_load(क्रमागत nft_रेजिस्टरs reg, अचिन्हित पूर्णांक len)
अणु
	अगर (reg < NFT_REG_1 * NFT_REG_SIZE / NFT_REG32_SIZE)
		वापस -EINVAL;
	अगर (len == 0)
		वापस -EINVAL;
	अगर (reg * NFT_REG32_SIZE + len > माप_field(काष्ठा nft_regs, data))
		वापस -दुस्फल;

	वापस 0;
पूर्ण

पूर्णांक nft_parse_रेजिस्टर_load(स्थिर काष्ठा nlattr *attr, u8 *sreg, u32 len)
अणु
	u32 reg;
	पूर्णांक err;

	reg = nft_parse_रेजिस्टर(attr);
	err = nft_validate_रेजिस्टर_load(reg, len);
	अगर (err < 0)
		वापस err;

	*sreg = reg;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_parse_रेजिस्टर_load);

अटल पूर्णांक nft_validate_रेजिस्टर_store(स्थिर काष्ठा nft_ctx *ctx,
				       क्रमागत nft_रेजिस्टरs reg,
				       स्थिर काष्ठा nft_data *data,
				       क्रमागत nft_data_types type,
				       अचिन्हित पूर्णांक len)
अणु
	पूर्णांक err;

	चयन (reg) अणु
	हाल NFT_REG_VERDICT:
		अगर (type != NFT_DATA_VERDICT)
			वापस -EINVAL;

		अगर (data != शून्य &&
		    (data->verdict.code == NFT_GOTO ||
		     data->verdict.code == NFT_JUMP)) अणु
			err = nf_tables_check_loops(ctx, data->verdict.chain);
			अगर (err < 0)
				वापस err;
		पूर्ण

		वापस 0;
	शेष:
		अगर (reg < NFT_REG_1 * NFT_REG_SIZE / NFT_REG32_SIZE)
			वापस -EINVAL;
		अगर (len == 0)
			वापस -EINVAL;
		अगर (reg * NFT_REG32_SIZE + len >
		    माप_field(काष्ठा nft_regs, data))
			वापस -दुस्फल;

		अगर (data != शून्य && type != NFT_DATA_VALUE)
			वापस -EINVAL;
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक nft_parse_रेजिस्टर_store(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nlattr *attr, u8 *dreg,
			     स्थिर काष्ठा nft_data *data,
			     क्रमागत nft_data_types type, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक err;
	u32 reg;

	reg = nft_parse_रेजिस्टर(attr);
	err = nft_validate_रेजिस्टर_store(ctx, reg, data, type, len);
	अगर (err < 0)
		वापस err;

	*dreg = reg;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nft_parse_रेजिस्टर_store);

अटल स्थिर काष्ठा nla_policy nft_verdict_policy[NFTA_VERDICT_MAX + 1] = अणु
	[NFTA_VERDICT_CODE]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_VERDICT_CHAIN]	= अणु .type = NLA_STRING,
				    .len = NFT_CHAIN_MAXNAMELEN - 1 पूर्ण,
	[NFTA_VERDICT_CHAIN_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_verdict_init(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_data *data,
			    काष्ठा nft_data_desc *desc, स्थिर काष्ठा nlattr *nla)
अणु
	u8 genmask = nft_genmask_next(ctx->net);
	काष्ठा nlattr *tb[NFTA_VERDICT_MAX + 1];
	काष्ठा nft_chain *chain;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_VERDICT_MAX, nla,
					  nft_verdict_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_VERDICT_CODE])
		वापस -EINVAL;
	data->verdict.code = ntohl(nla_get_be32(tb[NFTA_VERDICT_CODE]));

	चयन (data->verdict.code) अणु
	शेष:
		चयन (data->verdict.code & NF_VERDICT_MASK) अणु
		हाल NF_ACCEPT:
		हाल NF_DROP:
		हाल NF_QUEUE:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		fallthrough;
	हाल NFT_CONTINUE:
	हाल NFT_BREAK:
	हाल NFT_RETURN:
		अवरोध;
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		अगर (tb[NFTA_VERDICT_CHAIN]) अणु
			chain = nft_chain_lookup(ctx->net, ctx->table,
						 tb[NFTA_VERDICT_CHAIN],
						 genmask);
		पूर्ण अन्यथा अगर (tb[NFTA_VERDICT_CHAIN_ID]) अणु
			chain = nft_chain_lookup_byid(ctx->net,
						      tb[NFTA_VERDICT_CHAIN_ID]);
			अगर (IS_ERR(chain))
				वापस PTR_ERR(chain);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		अगर (IS_ERR(chain))
			वापस PTR_ERR(chain);
		अगर (nft_is_base_chain(chain))
			वापस -EOPNOTSUPP;

		chain->use++;
		data->verdict.chain = chain;
		अवरोध;
	पूर्ण

	desc->len = माप(data->verdict);
	desc->type = NFT_DATA_VERDICT;
	वापस 0;
पूर्ण

अटल व्योम nft_verdict_uninit(स्थिर काष्ठा nft_data *data)
अणु
	काष्ठा nft_chain *chain;
	काष्ठा nft_rule *rule;

	चयन (data->verdict.code) अणु
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		chain = data->verdict.chain;
		chain->use--;

		अगर (!nft_chain_is_bound(chain))
			अवरोध;

		chain->table->use--;
		list_क्रम_each_entry(rule, &chain->rules, list)
			chain->use--;

		nft_chain_del(chain);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक nft_verdict_dump(काष्ठा sk_buff *skb, पूर्णांक type, स्थिर काष्ठा nft_verdict *v)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, type);
	अगर (!nest)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_VERDICT_CODE, htonl(v->code)))
		जाओ nla_put_failure;

	चयन (v->code) अणु
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		अगर (nla_put_string(skb, NFTA_VERDICT_CHAIN,
				   v->chain->name))
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_value_init(स्थिर काष्ठा nft_ctx *ctx,
			  काष्ठा nft_data *data, अचिन्हित पूर्णांक size,
			  काष्ठा nft_data_desc *desc, स्थिर काष्ठा nlattr *nla)
अणु
	अचिन्हित पूर्णांक len;

	len = nla_len(nla);
	अगर (len == 0)
		वापस -EINVAL;
	अगर (len > size)
		वापस -EOVERFLOW;

	nla_स_नकल(data->data, nla, len);
	desc->type = NFT_DATA_VALUE;
	desc->len  = len;
	वापस 0;
पूर्ण

अटल पूर्णांक nft_value_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_data *data,
			  अचिन्हित पूर्णांक len)
अणु
	वापस nla_put(skb, NFTA_DATA_VALUE, len, data->data);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_data_policy[NFTA_DATA_MAX + 1] = अणु
	[NFTA_DATA_VALUE]	= अणु .type = NLA_BINARY पूर्ण,
	[NFTA_DATA_VERDICT]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/**
 *	nft_data_init - parse nf_tables data netlink attributes
 *
 *	@ctx: context of the expression using the data
 *	@data: destination काष्ठा nft_data
 *	@size: maximum data length
 *	@desc: data description
 *	@nla: netlink attribute containing data
 *
 *	Parse the netlink data attributes and initialize a काष्ठा nft_data.
 *	The type and length of data are वापसed in the data description.
 *
 *	The caller can indicate that it only wants to accept data of type
 *	NFT_DATA_VALUE by passing शून्य क्रम the ctx argument.
 */
पूर्णांक nft_data_init(स्थिर काष्ठा nft_ctx *ctx,
		  काष्ठा nft_data *data, अचिन्हित पूर्णांक size,
		  काष्ठा nft_data_desc *desc, स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nlattr *tb[NFTA_DATA_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_DATA_MAX, nla,
					  nft_data_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_DATA_VALUE])
		वापस nft_value_init(ctx, data, size, desc,
				      tb[NFTA_DATA_VALUE]);
	अगर (tb[NFTA_DATA_VERDICT] && ctx != शून्य)
		वापस nft_verdict_init(ctx, data, desc, tb[NFTA_DATA_VERDICT]);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(nft_data_init);

/**
 *	nft_data_release - release a nft_data item
 *
 *	@data: काष्ठा nft_data to release
 *	@type: type of data
 *
 *	Release a nft_data item. NFT_DATA_VALUE types can be silently discarded,
 *	all others need to be released by calling this function.
 */
व्योम nft_data_release(स्थिर काष्ठा nft_data *data, क्रमागत nft_data_types type)
अणु
	अगर (type < NFT_DATA_VERDICT)
		वापस;
	चयन (type) अणु
	हाल NFT_DATA_VERDICT:
		वापस nft_verdict_uninit(data);
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nft_data_release);

पूर्णांक nft_data_dump(काष्ठा sk_buff *skb, पूर्णांक attr, स्थिर काष्ठा nft_data *data,
		  क्रमागत nft_data_types type, अचिन्हित पूर्णांक len)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक err;

	nest = nla_nest_start_noflag(skb, attr);
	अगर (nest == शून्य)
		वापस -1;

	चयन (type) अणु
	हाल NFT_DATA_VALUE:
		err = nft_value_dump(skb, data, len);
		अवरोध;
	हाल NFT_DATA_VERDICT:
		err = nft_verdict_dump(skb, NFTA_DATA_VERDICT, &data->verdict);
		अवरोध;
	शेष:
		err = -EINVAL;
		WARN_ON(1);
	पूर्ण

	nla_nest_end(skb, nest);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nft_data_dump);

पूर्णांक __nft_release_basechain(काष्ठा nft_ctx *ctx)
अणु
	काष्ठा nft_rule *rule, *nr;

	अगर (WARN_ON(!nft_is_base_chain(ctx->chain)))
		वापस 0;

	nf_tables_unरेजिस्टर_hook(ctx->net, ctx->chain->table, ctx->chain);
	list_क्रम_each_entry_safe(rule, nr, &ctx->chain->rules, list) अणु
		list_del(&rule->list);
		ctx->chain->use--;
		nf_tables_rule_release(ctx, rule);
	पूर्ण
	nft_chain_del(ctx->chain);
	ctx->table->use--;
	nf_tables_chain_destroy(ctx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__nft_release_basechain);

अटल व्योम __nft_release_hook(काष्ठा net *net, काष्ठा nft_table *table)
अणु
	काष्ठा nft_chain *chain;

	list_क्रम_each_entry(chain, &table->chains, list)
		nf_tables_unरेजिस्टर_hook(net, table, chain);
पूर्ण

अटल व्योम __nft_release_hooks(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_table *table;

	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		अगर (nft_table_has_owner(table))
			जारी;

		__nft_release_hook(net, table);
	पूर्ण
पूर्ण

अटल व्योम __nft_release_table(काष्ठा net *net, काष्ठा nft_table *table)
अणु
	काष्ठा nft_flowtable *flowtable, *nf;
	काष्ठा nft_chain *chain, *nc;
	काष्ठा nft_object *obj, *ne;
	काष्ठा nft_rule *rule, *nr;
	काष्ठा nft_set *set, *ns;
	काष्ठा nft_ctx ctx = अणु
		.net	= net,
		.family	= NFPROTO_NETDEV,
	पूर्ण;

	ctx.family = table->family;
	ctx.table = table;
	list_क्रम_each_entry(chain, &table->chains, list) अणु
		ctx.chain = chain;
		list_क्रम_each_entry_safe(rule, nr, &chain->rules, list) अणु
			list_del(&rule->list);
			chain->use--;
			nf_tables_rule_release(&ctx, rule);
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(flowtable, nf, &table->flowtables, list) अणु
		list_del(&flowtable->list);
		table->use--;
		nf_tables_flowtable_destroy(flowtable);
	पूर्ण
	list_क्रम_each_entry_safe(set, ns, &table->sets, list) अणु
		list_del(&set->list);
		table->use--;
		nft_set_destroy(&ctx, set);
	पूर्ण
	list_क्रम_each_entry_safe(obj, ne, &table->objects, list) अणु
		nft_obj_del(obj);
		table->use--;
		nft_obj_destroy(&ctx, obj);
	पूर्ण
	list_क्रम_each_entry_safe(chain, nc, &table->chains, list) अणु
		ctx.chain = chain;
		nft_chain_del(chain);
		table->use--;
		nf_tables_chain_destroy(&ctx);
	पूर्ण
	list_del(&table->list);
	nf_tables_table_destroy(&ctx);
पूर्ण

अटल व्योम __nft_release_tables(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);
	काष्ठा nft_table *table, *nt;

	list_क्रम_each_entry_safe(table, nt, &nft_net->tables, list) अणु
		अगर (nft_table_has_owner(table))
			जारी;

		__nft_release_table(net, table);
	पूर्ण
पूर्ण

अटल पूर्णांक nft_rcv_nl_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा nftables_pernet *nft_net;
	काष्ठा netlink_notअगरy *n = ptr;
	काष्ठा nft_table *table, *nt;
	काष्ठा net *net = n->net;
	bool release = false;

	अगर (event != NETLINK_URELEASE || n->protocol != NETLINK_NETFILTER)
		वापस NOTIFY_DONE;

	nft_net = nft_pernet(net);
	mutex_lock(&nft_net->commit_mutex);
	list_क्रम_each_entry(table, &nft_net->tables, list) अणु
		अगर (nft_table_has_owner(table) &&
		    n->portid == table->nlpid) अणु
			__nft_release_hook(net, table);
			release = true;
		पूर्ण
	पूर्ण
	अगर (release) अणु
		synchronize_rcu();
		list_क्रम_each_entry_safe(table, nt, &nft_net->tables, list) अणु
			अगर (nft_table_has_owner(table) &&
			    n->portid == table->nlpid)
				__nft_release_table(net, table);
		पूर्ण
	पूर्ण
	mutex_unlock(&nft_net->commit_mutex);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nft_nl_notअगरier = अणु
	.notअगरier_call  = nft_rcv_nl_event,
पूर्ण;

अटल पूर्णांक __net_init nf_tables_init_net(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);

	INIT_LIST_HEAD(&nft_net->tables);
	INIT_LIST_HEAD(&nft_net->commit_list);
	INIT_LIST_HEAD(&nft_net->module_list);
	INIT_LIST_HEAD(&nft_net->notअगरy_list);
	mutex_init(&nft_net->commit_mutex);
	nft_net->base_seq = 1;
	nft_net->validate_state = NFT_VALIDATE_SKIP;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास nf_tables_pre_निकास_net(काष्ठा net *net)
अणु
	__nft_release_hooks(net);
पूर्ण

अटल व्योम __net_निकास nf_tables_निकास_net(काष्ठा net *net)
अणु
	काष्ठा nftables_pernet *nft_net = nft_pernet(net);

	mutex_lock(&nft_net->commit_mutex);
	अगर (!list_empty(&nft_net->commit_list))
		__nf_tables_पात(net, NFNL_ABORT_NONE);
	__nft_release_tables(net);
	mutex_unlock(&nft_net->commit_mutex);
	WARN_ON_ONCE(!list_empty(&nft_net->tables));
	WARN_ON_ONCE(!list_empty(&nft_net->module_list));
	WARN_ON_ONCE(!list_empty(&nft_net->notअगरy_list));
पूर्ण

अटल काष्ठा pernet_operations nf_tables_net_ops = अणु
	.init		= nf_tables_init_net,
	.pre_निकास	= nf_tables_pre_निकास_net,
	.निकास		= nf_tables_निकास_net,
	.id		= &nf_tables_net_id,
	.size		= माप(काष्ठा nftables_pernet),
पूर्ण;

अटल पूर्णांक __init nf_tables_module_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&nf_tables_net_ops);
	अगर (err < 0)
		वापस err;

	err = nft_chain_filter_init();
	अगर (err < 0)
		जाओ err_chain_filter;

	err = nf_tables_core_module_init();
	अगर (err < 0)
		जाओ err_core_module;

	err = रेजिस्टर_netdevice_notअगरier(&nf_tables_flowtable_notअगरier);
	अगर (err < 0)
		जाओ err_netdev_notअगरier;

	err = rhltable_init(&nft_objname_ht, &nft_objname_ht_params);
	अगर (err < 0)
		जाओ err_rht_objname;

	err = nft_offload_init();
	अगर (err < 0)
		जाओ err_offload;

	err = netlink_रेजिस्टर_notअगरier(&nft_nl_notअगरier);
	अगर (err < 0)
		जाओ err_netlink_notअगरier;

	/* must be last */
	err = nfnetlink_subsys_रेजिस्टर(&nf_tables_subsys);
	अगर (err < 0)
		जाओ err_nfnl_subsys;

	nft_chain_route_init();

	वापस err;

err_nfnl_subsys:
	netlink_unरेजिस्टर_notअगरier(&nft_nl_notअगरier);
err_netlink_notअगरier:
	nft_offload_निकास();
err_offload:
	rhltable_destroy(&nft_objname_ht);
err_rht_objname:
	unरेजिस्टर_netdevice_notअगरier(&nf_tables_flowtable_notअगरier);
err_netdev_notअगरier:
	nf_tables_core_module_निकास();
err_core_module:
	nft_chain_filter_fini();
err_chain_filter:
	unरेजिस्टर_pernet_subsys(&nf_tables_net_ops);
	वापस err;
पूर्ण

अटल व्योम __निकास nf_tables_module_निकास(व्योम)
अणु
	nfnetlink_subsys_unरेजिस्टर(&nf_tables_subsys);
	netlink_unरेजिस्टर_notअगरier(&nft_nl_notअगरier);
	nft_offload_निकास();
	unरेजिस्टर_netdevice_notअगरier(&nf_tables_flowtable_notअगरier);
	nft_chain_filter_fini();
	nft_chain_route_fini();
	unरेजिस्टर_pernet_subsys(&nf_tables_net_ops);
	cancel_work_sync(&trans_destroy_work);
	rcu_barrier();
	rhltable_destroy(&nft_objname_ht);
	nf_tables_core_module_निकास();
पूर्ण

module_init(nf_tables_module_init);
module_निकास(nf_tables_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_NFTABLES);
