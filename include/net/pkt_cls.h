<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_PKT_CLS_H
#घोषणा __NET_PKT_CLS_H

#समावेश <linux/pkt_cls.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sch_generic.h>
#समावेश <net/act_api.h>
#समावेश <net/net_namespace.h>

/* TC action not accessible from user space */
#घोषणा TC_ACT_CONSUMED		(TC_ACT_VALUE_MAX + 1)

/* Basic packet classअगरier frontend definitions. */

काष्ठा tcf_walker अणु
	पूर्णांक	stop;
	पूर्णांक	skip;
	पूर्णांक	count;
	bool	nonempty;
	अचिन्हित दीर्घ cookie;
	पूर्णांक	(*fn)(काष्ठा tcf_proto *, व्योम *node, काष्ठा tcf_walker *);
पूर्ण;

पूर्णांक रेजिस्टर_tcf_proto_ops(काष्ठा tcf_proto_ops *ops);
पूर्णांक unरेजिस्टर_tcf_proto_ops(काष्ठा tcf_proto_ops *ops);

काष्ठा tcf_block_ext_info अणु
	क्रमागत flow_block_binder_type binder_type;
	tcf_chain_head_change_t *chain_head_change;
	व्योम *chain_head_change_priv;
	u32 block_index;
पूर्ण;

काष्ठा tcf_qevent अणु
	काष्ठा tcf_block	*block;
	काष्ठा tcf_block_ext_info info;
	काष्ठा tcf_proto __rcu *filter_chain;
पूर्ण;

काष्ठा tcf_block_cb;
bool tcf_queue_work(काष्ठा rcu_work *rwork, work_func_t func);

#अगर_घोषित CONFIG_NET_CLS
काष्ठा tcf_chain *tcf_chain_get_by_act(काष्ठा tcf_block *block,
				       u32 chain_index);
व्योम tcf_chain_put_by_act(काष्ठा tcf_chain *chain);
काष्ठा tcf_chain *tcf_get_next_chain(काष्ठा tcf_block *block,
				     काष्ठा tcf_chain *chain);
काष्ठा tcf_proto *tcf_get_next_proto(काष्ठा tcf_chain *chain,
				     काष्ठा tcf_proto *tp);
व्योम tcf_block_netअगर_keep_dst(काष्ठा tcf_block *block);
पूर्णांक tcf_block_get(काष्ठा tcf_block **p_block,
		  काष्ठा tcf_proto __rcu **p_filter_chain, काष्ठा Qdisc *q,
		  काष्ठा netlink_ext_ack *extack);
पूर्णांक tcf_block_get_ext(काष्ठा tcf_block **p_block, काष्ठा Qdisc *q,
		      काष्ठा tcf_block_ext_info *ei,
		      काष्ठा netlink_ext_ack *extack);
व्योम tcf_block_put(काष्ठा tcf_block *block);
व्योम tcf_block_put_ext(काष्ठा tcf_block *block, काष्ठा Qdisc *q,
		       काष्ठा tcf_block_ext_info *ei);

अटल अंतरभूत bool tcf_block_shared(काष्ठा tcf_block *block)
अणु
	वापस block->index;
पूर्ण

अटल अंतरभूत bool tcf_block_non_null_shared(काष्ठा tcf_block *block)
अणु
	वापस block && block->index;
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *tcf_block_q(काष्ठा tcf_block *block)
अणु
	WARN_ON(tcf_block_shared(block));
	वापस block->q;
पूर्ण

पूर्णांक tcf_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
		 काष्ठा tcf_result *res, bool compat_mode);
पूर्णांक tcf_classअगरy_ingress(काष्ठा sk_buff *skb,
			 स्थिर काष्ठा tcf_block *ingress_block,
			 स्थिर काष्ठा tcf_proto *tp, काष्ठा tcf_result *res,
			 bool compat_mode);

#अन्यथा
अटल अंतरभूत bool tcf_block_shared(काष्ठा tcf_block *block)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool tcf_block_non_null_shared(काष्ठा tcf_block *block)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत
पूर्णांक tcf_block_get(काष्ठा tcf_block **p_block,
		  काष्ठा tcf_proto __rcu **p_filter_chain, काष्ठा Qdisc *q,
		  काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक tcf_block_get_ext(काष्ठा tcf_block **p_block, काष्ठा Qdisc *q,
		      काष्ठा tcf_block_ext_info *ei,
		      काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tcf_block_put(काष्ठा tcf_block *block)
अणु
पूर्ण

अटल अंतरभूत
व्योम tcf_block_put_ext(काष्ठा tcf_block *block, काष्ठा Qdisc *q,
		       काष्ठा tcf_block_ext_info *ei)
अणु
पूर्ण

अटल अंतरभूत काष्ठा Qdisc *tcf_block_q(काष्ठा tcf_block *block)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
पूर्णांक tc_setup_cb_block_रेजिस्टर(काष्ठा tcf_block *block, flow_setup_cb_t *cb,
			       व्योम *cb_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम tc_setup_cb_block_unरेजिस्टर(काष्ठा tcf_block *block, flow_setup_cb_t *cb,
				  व्योम *cb_priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक tcf_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			       काष्ठा tcf_result *res, bool compat_mode)
अणु
	वापस TC_ACT_UNSPEC;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_classअगरy_ingress(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा tcf_block *ingress_block,
				       स्थिर काष्ठा tcf_proto *tp,
				       काष्ठा tcf_result *res, bool compat_mode)
अणु
	वापस TC_ACT_UNSPEC;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ
__cls_set_class(अचिन्हित दीर्घ *clp, अचिन्हित दीर्घ cl)
अणु
	वापस xchg(clp, cl);
पूर्ण

अटल अंतरभूत व्योम
__tcf_bind_filter(काष्ठा Qdisc *q, काष्ठा tcf_result *r, अचिन्हित दीर्घ base)
अणु
	अचिन्हित दीर्घ cl;

	cl = q->ops->cl_ops->bind_tcf(q, base, r->classid);
	cl = __cls_set_class(&r->class, cl);
	अगर (cl)
		q->ops->cl_ops->unbind_tcf(q, cl);
पूर्ण

अटल अंतरभूत व्योम
tcf_bind_filter(काष्ठा tcf_proto *tp, काष्ठा tcf_result *r, अचिन्हित दीर्घ base)
अणु
	काष्ठा Qdisc *q = tp->chain->block->q;

	/* Check q as it is not set क्रम shared blocks. In that हाल,
	 * setting class is not supported.
	 */
	अगर (!q)
		वापस;
	sch_tree_lock(q);
	__tcf_bind_filter(q, r, base);
	sch_tree_unlock(q);
पूर्ण

अटल अंतरभूत व्योम
__tcf_unbind_filter(काष्ठा Qdisc *q, काष्ठा tcf_result *r)
अणु
	अचिन्हित दीर्घ cl;

	अगर ((cl = __cls_set_class(&r->class, 0)) != 0)
		q->ops->cl_ops->unbind_tcf(q, cl);
पूर्ण

अटल अंतरभूत व्योम
tcf_unbind_filter(काष्ठा tcf_proto *tp, काष्ठा tcf_result *r)
अणु
	काष्ठा Qdisc *q = tp->chain->block->q;

	अगर (!q)
		वापस;
	__tcf_unbind_filter(q, r);
पूर्ण

काष्ठा tcf_exts अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	__u32	type; /* क्रम backward compat(TCA_OLD_COMPAT) */
	पूर्णांक nr_actions;
	काष्ठा tc_action **actions;
	काष्ठा net *net;
#पूर्ण_अगर
	/* Map to export classअगरier specअगरic extension TLV types to the
	 * generic extensions API. Unsupported extensions must be set to 0.
	 */
	पूर्णांक action;
	पूर्णांक police;
पूर्ण;

अटल अंतरभूत पूर्णांक tcf_exts_init(काष्ठा tcf_exts *exts, काष्ठा net *net,
				पूर्णांक action, पूर्णांक police)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	exts->type = 0;
	exts->nr_actions = 0;
	exts->net = net;
	exts->actions = kसुस्मृति(TCA_ACT_MAX_PRIO, माप(काष्ठा tc_action *),
				GFP_KERNEL);
	अगर (!exts->actions)
		वापस -ENOMEM;
#पूर्ण_अगर
	exts->action = action;
	exts->police = police;
	वापस 0;
पूर्ण

/* Return false अगर the netns is being destroyed in cleanup_net(). Callers
 * need to करो cleanup synchronously in this हाल, otherwise may race with
 * tc_action_net_निकास(). Return true क्रम other हालs.
 */
अटल अंतरभूत bool tcf_exts_get_net(काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	exts->net = maybe_get_net(exts->net);
	वापस exts->net != शून्य;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम tcf_exts_put_net(काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (exts->net)
		put_net(exts->net);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT
#घोषणा tcf_exts_क्रम_each_action(i, a, exts) \
	क्रम (i = 0; i < TCA_ACT_MAX_PRIO && ((a) = (exts)->actions[i]); i++)
#अन्यथा
#घोषणा tcf_exts_क्रम_each_action(i, a, exts) \
	क्रम (; 0; (व्योम)(i), (व्योम)(a), (व्योम)(exts))
#पूर्ण_अगर

अटल अंतरभूत व्योम
tcf_exts_stats_update(स्थिर काष्ठा tcf_exts *exts,
		      u64 bytes, u64 packets, u64 drops, u64 lastuse,
		      u8 used_hw_stats, bool used_hw_stats_valid)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	पूर्णांक i;

	preempt_disable();

	क्रम (i = 0; i < exts->nr_actions; i++) अणु
		काष्ठा tc_action *a = exts->actions[i];

		tcf_action_stats_update(a, bytes, packets, drops,
					lastuse, true);
		a->used_hw_stats = used_hw_stats;
		a->used_hw_stats_valid = used_hw_stats_valid;
	पूर्ण

	preempt_enable();
#पूर्ण_अगर
पूर्ण

/**
 * tcf_exts_has_actions - check अगर at least one action is present
 * @exts: tc filter extensions handle
 *
 * Returns true अगर at least one action is present.
 */
अटल अंतरभूत bool tcf_exts_has_actions(काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	वापस exts->nr_actions;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/**
 * tcf_exts_exec - execute tc filter extensions
 * @skb: socket buffer
 * @exts: tc filter extensions handle
 * @res: desired result
 *
 * Executes all configured extensions. Returns TC_ACT_OK on a normal execution,
 * a negative number अगर the filter must be considered unmatched or
 * a positive action code (TC_ACT_*) which must be वापसed to the
 * underlying layer.
 */
अटल अंतरभूत पूर्णांक
tcf_exts_exec(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts,
	      काष्ठा tcf_result *res)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	वापस tcf_action_exec(skb, exts->actions, exts->nr_actions, res);
#पूर्ण_अगर
	वापस TC_ACT_OK;
पूर्ण

पूर्णांक tcf_exts_validate(काष्ठा net *net, काष्ठा tcf_proto *tp,
		      काष्ठा nlattr **tb, काष्ठा nlattr *rate_tlv,
		      काष्ठा tcf_exts *exts, bool ovr, bool rtnl_held,
		      काष्ठा netlink_ext_ack *extack);
व्योम tcf_exts_destroy(काष्ठा tcf_exts *exts);
व्योम tcf_exts_change(काष्ठा tcf_exts *dst, काष्ठा tcf_exts *src);
पूर्णांक tcf_exts_dump(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts);
पूर्णांक tcf_exts_terse_dump(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts);
पूर्णांक tcf_exts_dump_stats(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts);

/**
 * काष्ठा tcf_pkt_info - packet inक्रमmation
 */
काष्ठा tcf_pkt_info अणु
	अचिन्हित अक्षर *		ptr;
	पूर्णांक			nexthdr;
पूर्ण;

#अगर_घोषित CONFIG_NET_EMATCH

काष्ठा tcf_ematch_ops;

/**
 * काष्ठा tcf_ematch - extended match (ematch)
 * 
 * @matchid: identअगरier to allow userspace to reidentअगरy a match
 * @flags: flags specअगरying attributes and the relation to other matches
 * @ops: the operations lookup table of the corresponding ematch module
 * @datalen: length of the ematch specअगरic configuration data
 * @data: ematch specअगरic data
 */
काष्ठा tcf_ematch अणु
	काष्ठा tcf_ematch_ops * ops;
	अचिन्हित दीर्घ		data;
	अचिन्हित पूर्णांक		datalen;
	u16			matchid;
	u16			flags;
	काष्ठा net		*net;
पूर्ण;

अटल अंतरभूत पूर्णांक tcf_em_is_container(काष्ठा tcf_ematch *em)
अणु
	वापस !em->ops;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_em_is_simple(काष्ठा tcf_ematch *em)
अणु
	वापस em->flags & TCF_EM_SIMPLE;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_em_is_inverted(काष्ठा tcf_ematch *em)
अणु
	वापस em->flags & TCF_EM_INVERT;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_em_last_match(काष्ठा tcf_ematch *em)
अणु
	वापस (em->flags & TCF_EM_REL_MASK) == TCF_EM_REL_END;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_em_early_end(काष्ठा tcf_ematch *em, पूर्णांक result)
अणु
	अगर (tcf_em_last_match(em))
		वापस 1;

	अगर (result == 0 && em->flags & TCF_EM_REL_AND)
		वापस 1;

	अगर (result != 0 && em->flags & TCF_EM_REL_OR)
		वापस 1;

	वापस 0;
पूर्ण
	
/**
 * काष्ठा tcf_ematch_tree - ematch tree handle
 *
 * @hdr: ematch tree header supplied by userspace
 * @matches: array of ematches
 */
काष्ठा tcf_ematch_tree अणु
	काष्ठा tcf_ematch_tree_hdr hdr;
	काष्ठा tcf_ematch *	matches;
	
पूर्ण;

/**
 * काष्ठा tcf_ematch_ops - ematch module operations
 * 
 * @kind: identअगरier (kind) of this ematch module
 * @datalen: length of expected configuration data (optional)
 * @change: called during validation (optional)
 * @match: called during ematch tree evaluation, must वापस 1/0
 * @destroy: called during destroyage (optional)
 * @dump: called during dumping process (optional)
 * @owner: owner, must be set to THIS_MODULE
 * @link: link to previous/next ematch module (पूर्णांकernal use)
 */
काष्ठा tcf_ematch_ops अणु
	पूर्णांक			kind;
	पूर्णांक			datalen;
	पूर्णांक			(*change)(काष्ठा net *net, व्योम *,
					  पूर्णांक, काष्ठा tcf_ematch *);
	पूर्णांक			(*match)(काष्ठा sk_buff *, काष्ठा tcf_ematch *,
					 काष्ठा tcf_pkt_info *);
	व्योम			(*destroy)(काष्ठा tcf_ematch *);
	पूर्णांक			(*dump)(काष्ठा sk_buff *, काष्ठा tcf_ematch *);
	काष्ठा module		*owner;
	काष्ठा list_head	link;
पूर्ण;

पूर्णांक tcf_em_रेजिस्टर(काष्ठा tcf_ematch_ops *);
व्योम tcf_em_unरेजिस्टर(काष्ठा tcf_ematch_ops *);
पूर्णांक tcf_em_tree_validate(काष्ठा tcf_proto *, काष्ठा nlattr *,
			 काष्ठा tcf_ematch_tree *);
व्योम tcf_em_tree_destroy(काष्ठा tcf_ematch_tree *);
पूर्णांक tcf_em_tree_dump(काष्ठा sk_buff *, काष्ठा tcf_ematch_tree *, पूर्णांक);
पूर्णांक __tcf_em_tree_match(काष्ठा sk_buff *, काष्ठा tcf_ematch_tree *,
			काष्ठा tcf_pkt_info *);

/**
 * tcf_em_tree_match - evaulate an ematch tree
 *
 * @skb: socket buffer of the packet in question
 * @tree: ematch tree to be used क्रम evaluation
 * @info: packet inक्रमmation examined by classअगरier
 *
 * This function matches @skb against the ematch tree in @tree by going
 * through all ematches respecting their logic relations वापसing
 * as soon as the result is obvious.
 *
 * Returns 1 अगर the ematch tree as-one matches, no ematches are configured
 * or ematch is not enabled in the kernel, otherwise 0 is वापसed.
 */
अटल अंतरभूत पूर्णांक tcf_em_tree_match(काष्ठा sk_buff *skb,
				    काष्ठा tcf_ematch_tree *tree,
				    काष्ठा tcf_pkt_info *info)
अणु
	अगर (tree->hdr.nmatches)
		वापस __tcf_em_tree_match(skb, tree, info);
	अन्यथा
		वापस 1;
पूर्ण

#घोषणा MODULE_ALIAS_TCF_EMATCH(kind)	MODULE_ALIAS("ematch-kind-" __stringअगरy(kind))

#अन्यथा /* CONFIG_NET_EMATCH */

काष्ठा tcf_ematch_tree अणु
पूर्ण;

#घोषणा tcf_em_tree_validate(tp, tb, t) ((व्योम)(t), 0)
#घोषणा tcf_em_tree_destroy(t) करो अणु (व्योम)(t); पूर्ण जबतक(0)
#घोषणा tcf_em_tree_dump(skb, t, tlv) (0)
#घोषणा tcf_em_tree_match(skb, t, info) ((व्योम)(info), 1)

#पूर्ण_अगर /* CONFIG_NET_EMATCH */

अटल अंतरभूत अचिन्हित अक्षर * tcf_get_base_ptr(काष्ठा sk_buff *skb, पूर्णांक layer)
अणु
	चयन (layer) अणु
		हाल TCF_LAYER_LINK:
			वापस skb_mac_header(skb);
		हाल TCF_LAYER_NETWORK:
			वापस skb_network_header(skb);
		हाल TCF_LAYER_TRANSPORT:
			वापस skb_transport_header(skb);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_valid_offset(स्थिर काष्ठा sk_buff *skb,
				   स्थिर अचिन्हित अक्षर *ptr, स्थिर पूर्णांक len)
अणु
	वापस likely((ptr + len) <= skb_tail_poपूर्णांकer(skb) &&
		      ptr >= skb->head &&
		      (ptr <= (ptr + len)));
पूर्ण

अटल अंतरभूत पूर्णांक
tcf_change_indev(काष्ठा net *net, काष्ठा nlattr *indev_tlv,
		 काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर indev[IFNAMSIZ];
	काष्ठा net_device *dev;

	अगर (nla_strscpy(indev, indev_tlv, IFNAMSIZ) < 0) अणु
		NL_SET_ERR_MSG_ATTR(extack, indev_tlv,
				    "Interface name too long");
		वापस -EINVAL;
	पूर्ण
	dev = __dev_get_by_name(net, indev);
	अगर (!dev) अणु
		NL_SET_ERR_MSG_ATTR(extack, indev_tlv,
				    "Network device not found");
		वापस -ENODEV;
	पूर्ण
	वापस dev->अगरindex;
पूर्ण

अटल अंतरभूत bool
tcf_match_indev(काष्ठा sk_buff *skb, पूर्णांक अगरindex)
अणु
	अगर (!अगरindex)
		वापस true;
	अगर  (!skb->skb_iअगर)
		वापस false;
	वापस अगरindex == skb->skb_iअगर;
पूर्ण

पूर्णांक tc_setup_flow_action(काष्ठा flow_action *flow_action,
			 स्थिर काष्ठा tcf_exts *exts);
व्योम tc_cleanup_flow_action(काष्ठा flow_action *flow_action);

पूर्णांक tc_setup_cb_call(काष्ठा tcf_block *block, क्रमागत tc_setup_type type,
		     व्योम *type_data, bool err_stop, bool rtnl_held);
पूर्णांक tc_setup_cb_add(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
		    क्रमागत tc_setup_type type, व्योम *type_data, bool err_stop,
		    u32 *flags, अचिन्हित पूर्णांक *in_hw_count, bool rtnl_held);
पूर्णांक tc_setup_cb_replace(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			क्रमागत tc_setup_type type, व्योम *type_data, bool err_stop,
			u32 *old_flags, अचिन्हित पूर्णांक *old_in_hw_count,
			u32 *new_flags, अचिन्हित पूर्णांक *new_in_hw_count,
			bool rtnl_held);
पूर्णांक tc_setup_cb_destroy(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			क्रमागत tc_setup_type type, व्योम *type_data, bool err_stop,
			u32 *flags, अचिन्हित पूर्णांक *in_hw_count, bool rtnl_held);
पूर्णांक tc_setup_cb_reoffload(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			  bool add, flow_setup_cb_t *cb,
			  क्रमागत tc_setup_type type, व्योम *type_data,
			  व्योम *cb_priv, u32 *flags, अचिन्हित पूर्णांक *in_hw_count);
अचिन्हित पूर्णांक tcf_exts_num_actions(काष्ठा tcf_exts *exts);

#अगर_घोषित CONFIG_NET_CLS_ACT
पूर्णांक tcf_qevent_init(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch,
		    क्रमागत flow_block_binder_type binder_type,
		    काष्ठा nlattr *block_index_attr,
		    काष्ठा netlink_ext_ack *extack);
व्योम tcf_qevent_destroy(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch);
पूर्णांक tcf_qevent_validate_change(काष्ठा tcf_qevent *qe, काष्ठा nlattr *block_index_attr,
			       काष्ठा netlink_ext_ack *extack);
काष्ठा sk_buff *tcf_qevent_handle(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch, काष्ठा sk_buff *skb,
				  काष्ठा sk_buff **to_मुक्त, पूर्णांक *ret);
पूर्णांक tcf_qevent_dump(काष्ठा sk_buff *skb, पूर्णांक attr_name, काष्ठा tcf_qevent *qe);
#अन्यथा
अटल अंतरभूत पूर्णांक tcf_qevent_init(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch,
				  क्रमागत flow_block_binder_type binder_type,
				  काष्ठा nlattr *block_index_attr,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tcf_qevent_destroy(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक tcf_qevent_validate_change(काष्ठा tcf_qevent *qe, काष्ठा nlattr *block_index_attr,
					     काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
tcf_qevent_handle(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch, काष्ठा sk_buff *skb,
		  काष्ठा sk_buff **to_मुक्त, पूर्णांक *ret)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_qevent_dump(काष्ठा sk_buff *skb, पूर्णांक attr_name, काष्ठा tcf_qevent *qe)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा tc_cls_u32_knode अणु
	काष्ठा tcf_exts *exts;
	काष्ठा tcf_result *res;
	काष्ठा tc_u32_sel *sel;
	u32 handle;
	u32 val;
	u32 mask;
	u32 link_handle;
	u8 fshअगरt;
पूर्ण;

काष्ठा tc_cls_u32_hnode अणु
	u32 handle;
	u32 prio;
	अचिन्हित पूर्णांक भागisor;
पूर्ण;

क्रमागत tc_clsu32_command अणु
	TC_CLSU32_NEW_KNODE,
	TC_CLSU32_REPLACE_KNODE,
	TC_CLSU32_DELETE_KNODE,
	TC_CLSU32_NEW_HNODE,
	TC_CLSU32_REPLACE_HNODE,
	TC_CLSU32_DELETE_HNODE,
पूर्ण;

काष्ठा tc_cls_u32_offload अणु
	काष्ठा flow_cls_common_offload common;
	/* knode values */
	क्रमागत tc_clsu32_command command;
	जोड़ अणु
		काष्ठा tc_cls_u32_knode knode;
		काष्ठा tc_cls_u32_hnode hnode;
	पूर्ण;
पूर्ण;

अटल अंतरभूत bool tc_can_offload(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->features & NETIF_F_HW_TC;
पूर्ण

अटल अंतरभूत bool tc_can_offload_extack(स्थिर काष्ठा net_device *dev,
					 काष्ठा netlink_ext_ack *extack)
अणु
	bool can = tc_can_offload(dev);

	अगर (!can)
		NL_SET_ERR_MSG(extack, "TC offload is disabled on net device");

	वापस can;
पूर्ण

अटल अंतरभूत bool
tc_cls_can_offload_and_chain0(स्थिर काष्ठा net_device *dev,
			      काष्ठा flow_cls_common_offload *common)
अणु
	अगर (!tc_can_offload_extack(dev, common->extack))
		वापस false;
	अगर (common->chain_index) अणु
		NL_SET_ERR_MSG(common->extack,
			       "Driver supports only offload of chain 0");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत bool tc_skip_hw(u32 flags)
अणु
	वापस (flags & TCA_CLS_FLAGS_SKIP_HW) ? true : false;
पूर्ण

अटल अंतरभूत bool tc_skip_sw(u32 flags)
अणु
	वापस (flags & TCA_CLS_FLAGS_SKIP_SW) ? true : false;
पूर्ण

/* SKIP_HW and SKIP_SW are mutually exclusive flags. */
अटल अंतरभूत bool tc_flags_valid(u32 flags)
अणु
	अगर (flags & ~(TCA_CLS_FLAGS_SKIP_HW | TCA_CLS_FLAGS_SKIP_SW |
		      TCA_CLS_FLAGS_VERBOSE))
		वापस false;

	flags &= TCA_CLS_FLAGS_SKIP_HW | TCA_CLS_FLAGS_SKIP_SW;
	अगर (!(flags ^ (TCA_CLS_FLAGS_SKIP_HW | TCA_CLS_FLAGS_SKIP_SW)))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool tc_in_hw(u32 flags)
अणु
	वापस (flags & TCA_CLS_FLAGS_IN_HW) ? true : false;
पूर्ण

अटल अंतरभूत व्योम
tc_cls_common_offload_init(काष्ठा flow_cls_common_offload *cls_common,
			   स्थिर काष्ठा tcf_proto *tp, u32 flags,
			   काष्ठा netlink_ext_ack *extack)
अणु
	cls_common->chain_index = tp->chain->index;
	cls_common->protocol = tp->protocol;
	cls_common->prio = tp->prio >> 16;
	अगर (tc_skip_sw(flags) || flags & TCA_CLS_FLAGS_VERBOSE)
		cls_common->extack = extack;
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
अटल अंतरभूत काष्ठा tc_skb_ext *tc_skb_ext_alloc(काष्ठा sk_buff *skb)
अणु
	काष्ठा tc_skb_ext *tc_skb_ext = skb_ext_add(skb, TC_SKB_EXT);

	अगर (tc_skb_ext)
		स_रखो(tc_skb_ext, 0, माप(*tc_skb_ext));
	वापस tc_skb_ext;
पूर्ण
#पूर्ण_अगर

क्रमागत tc_matchall_command अणु
	TC_CLSMATCHALL_REPLACE,
	TC_CLSMATCHALL_DESTROY,
	TC_CLSMATCHALL_STATS,
पूर्ण;

काष्ठा tc_cls_matchall_offload अणु
	काष्ठा flow_cls_common_offload common;
	क्रमागत tc_matchall_command command;
	काष्ठा flow_rule *rule;
	काष्ठा flow_stats stats;
	अचिन्हित दीर्घ cookie;
पूर्ण;

क्रमागत tc_clsbpf_command अणु
	TC_CLSBPF_OFFLOAD,
	TC_CLSBPF_STATS,
पूर्ण;

काष्ठा tc_cls_bpf_offload अणु
	काष्ठा flow_cls_common_offload common;
	क्रमागत tc_clsbpf_command command;
	काष्ठा tcf_exts *exts;
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_prog *oldprog;
	स्थिर अक्षर *name;
	bool exts_पूर्णांकegrated;
पूर्ण;

काष्ठा tc_mqprio_qopt_offload अणु
	/* काष्ठा tc_mqprio_qopt must always be the first element */
	काष्ठा tc_mqprio_qopt qopt;
	u16 mode;
	u16 shaper;
	u32 flags;
	u64 min_rate[TC_QOPT_MAX_QUEUE];
	u64 max_rate[TC_QOPT_MAX_QUEUE];
पूर्ण;

/* This काष्ठाure holds cookie काष्ठाure that is passed from user
 * to the kernel क्रम actions and classअगरiers
 */
काष्ठा tc_cookie अणु
	u8  *data;
	u32 len;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा tc_qopt_offload_stats अणु
	काष्ठा gnet_stats_basic_packed *bstats;
	काष्ठा gnet_stats_queue *qstats;
पूर्ण;

क्रमागत tc_mq_command अणु
	TC_MQ_CREATE,
	TC_MQ_DESTROY,
	TC_MQ_STATS,
	TC_MQ_GRAFT,
पूर्ण;

काष्ठा tc_mq_opt_offload_graft_params अणु
	अचिन्हित दीर्घ queue;
	u32 child_handle;
पूर्ण;

काष्ठा tc_mq_qopt_offload अणु
	क्रमागत tc_mq_command command;
	u32 handle;
	जोड़ अणु
		काष्ठा tc_qopt_offload_stats stats;
		काष्ठा tc_mq_opt_offload_graft_params graft_params;
	पूर्ण;
पूर्ण;

क्रमागत tc_htb_command अणु
	/* Root */
	TC_HTB_CREATE, /* Initialize HTB offload. */
	TC_HTB_DESTROY, /* Destroy HTB offload. */

	/* Classes */
	/* Allocate qid and create leaf. */
	TC_HTB_LEAF_ALLOC_QUEUE,
	/* Convert leaf to inner, preserve and वापस qid, create new leaf. */
	TC_HTB_LEAF_TO_INNER,
	/* Delete leaf, जबतक siblings reमुख्य. */
	TC_HTB_LEAF_DEL,
	/* Delete leaf, convert parent to leaf, preserving qid. */
	TC_HTB_LEAF_DEL_LAST,
	/* TC_HTB_LEAF_DEL_LAST, but delete driver data on hardware errors. */
	TC_HTB_LEAF_DEL_LAST_FORCE,
	/* Modअगरy parameters of a node. */
	TC_HTB_NODE_MODIFY,

	/* Class qdisc */
	TC_HTB_LEAF_QUERY_QUEUE, /* Query qid by classid. */
पूर्ण;

काष्ठा tc_htb_qopt_offload अणु
	काष्ठा netlink_ext_ack *extack;
	क्रमागत tc_htb_command command;
	u16 classid;
	u32 parent_classid;
	u16 qid;
	u16 moved_qid;
	u64 rate;
	u64 उच्चमान;
पूर्ण;

#घोषणा TC_HTB_CLASSID_ROOT U32_MAX

क्रमागत tc_red_command अणु
	TC_RED_REPLACE,
	TC_RED_DESTROY,
	TC_RED_STATS,
	TC_RED_XSTATS,
	TC_RED_GRAFT,
पूर्ण;

काष्ठा tc_red_qopt_offload_params अणु
	u32 min;
	u32 max;
	u32 probability;
	u32 limit;
	bool is_ecn;
	bool is_harddrop;
	bool is_nodrop;
	काष्ठा gnet_stats_queue *qstats;
पूर्ण;

काष्ठा tc_red_qopt_offload अणु
	क्रमागत tc_red_command command;
	u32 handle;
	u32 parent;
	जोड़ अणु
		काष्ठा tc_red_qopt_offload_params set;
		काष्ठा tc_qopt_offload_stats stats;
		काष्ठा red_stats *xstats;
		u32 child_handle;
	पूर्ण;
पूर्ण;

क्रमागत tc_gred_command अणु
	TC_GRED_REPLACE,
	TC_GRED_DESTROY,
	TC_GRED_STATS,
पूर्ण;

काष्ठा tc_gred_vq_qopt_offload_params अणु
	bool present;
	u32 limit;
	u32 prio;
	u32 min;
	u32 max;
	bool is_ecn;
	bool is_harddrop;
	u32 probability;
	/* Only need backlog, see काष्ठा tc_prio_qopt_offload_params */
	u32 *backlog;
पूर्ण;

काष्ठा tc_gred_qopt_offload_params अणु
	bool grio_on;
	bool wred_on;
	अचिन्हित पूर्णांक dp_cnt;
	अचिन्हित पूर्णांक dp_def;
	काष्ठा gnet_stats_queue *qstats;
	काष्ठा tc_gred_vq_qopt_offload_params tab[MAX_DPs];
पूर्ण;

काष्ठा tc_gred_qopt_offload_stats अणु
	काष्ठा gnet_stats_basic_packed bstats[MAX_DPs];
	काष्ठा gnet_stats_queue qstats[MAX_DPs];
	काष्ठा red_stats *xstats[MAX_DPs];
पूर्ण;

काष्ठा tc_gred_qopt_offload अणु
	क्रमागत tc_gred_command command;
	u32 handle;
	u32 parent;
	जोड़ अणु
		काष्ठा tc_gred_qopt_offload_params set;
		काष्ठा tc_gred_qopt_offload_stats stats;
	पूर्ण;
पूर्ण;

क्रमागत tc_prio_command अणु
	TC_PRIO_REPLACE,
	TC_PRIO_DESTROY,
	TC_PRIO_STATS,
	TC_PRIO_GRAFT,
पूर्ण;

काष्ठा tc_prio_qopt_offload_params अणु
	पूर्णांक bands;
	u8 priomap[TC_PRIO_MAX + 1];
	/* At the poपूर्णांक of un-offloading the Qdisc, the reported backlog and
	 * qlen need to be reduced by the portion that is in HW.
	 */
	काष्ठा gnet_stats_queue *qstats;
पूर्ण;

काष्ठा tc_prio_qopt_offload_graft_params अणु
	u8 band;
	u32 child_handle;
पूर्ण;

काष्ठा tc_prio_qopt_offload अणु
	क्रमागत tc_prio_command command;
	u32 handle;
	u32 parent;
	जोड़ अणु
		काष्ठा tc_prio_qopt_offload_params replace_params;
		काष्ठा tc_qopt_offload_stats stats;
		काष्ठा tc_prio_qopt_offload_graft_params graft_params;
	पूर्ण;
पूर्ण;

क्रमागत tc_root_command अणु
	TC_ROOT_GRAFT,
पूर्ण;

काष्ठा tc_root_qopt_offload अणु
	क्रमागत tc_root_command command;
	u32 handle;
	bool ingress;
पूर्ण;

क्रमागत tc_ets_command अणु
	TC_ETS_REPLACE,
	TC_ETS_DESTROY,
	TC_ETS_STATS,
	TC_ETS_GRAFT,
पूर्ण;

काष्ठा tc_ets_qopt_offload_replace_params अणु
	अचिन्हित पूर्णांक bands;
	u8 priomap[TC_PRIO_MAX + 1];
	अचिन्हित पूर्णांक quanta[TCQ_ETS_MAX_BANDS];	/* 0 क्रम strict bands. */
	अचिन्हित पूर्णांक weights[TCQ_ETS_MAX_BANDS];
	काष्ठा gnet_stats_queue *qstats;
पूर्ण;

काष्ठा tc_ets_qopt_offload_graft_params अणु
	u8 band;
	u32 child_handle;
पूर्ण;

काष्ठा tc_ets_qopt_offload अणु
	क्रमागत tc_ets_command command;
	u32 handle;
	u32 parent;
	जोड़ अणु
		काष्ठा tc_ets_qopt_offload_replace_params replace_params;
		काष्ठा tc_qopt_offload_stats stats;
		काष्ठा tc_ets_qopt_offload_graft_params graft_params;
	पूर्ण;
पूर्ण;

क्रमागत tc_tbf_command अणु
	TC_TBF_REPLACE,
	TC_TBF_DESTROY,
	TC_TBF_STATS,
पूर्ण;

काष्ठा tc_tbf_qopt_offload_replace_params अणु
	काष्ठा psched_ratecfg rate;
	u32 max_size;
	काष्ठा gnet_stats_queue *qstats;
पूर्ण;

काष्ठा tc_tbf_qopt_offload अणु
	क्रमागत tc_tbf_command command;
	u32 handle;
	u32 parent;
	जोड़ अणु
		काष्ठा tc_tbf_qopt_offload_replace_params replace_params;
		काष्ठा tc_qopt_offload_stats stats;
	पूर्ण;
पूर्ण;

क्रमागत tc_fअगरo_command अणु
	TC_FIFO_REPLACE,
	TC_FIFO_DESTROY,
	TC_FIFO_STATS,
पूर्ण;

काष्ठा tc_fअगरo_qopt_offload अणु
	क्रमागत tc_fअगरo_command command;
	u32 handle;
	u32 parent;
	जोड़ अणु
		काष्ठा tc_qopt_offload_stats stats;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर
