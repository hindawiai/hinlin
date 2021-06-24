<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_ACT_API_H
#घोषणा __NET_ACT_API_H

/*
 * Public action API क्रम classअगरiers/qdiscs
*/

#समावेश <linux/refcount.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

काष्ठा tcf_idrinfo अणु
	काष्ठा mutex	lock;
	काष्ठा idr	action_idr;
	काष्ठा net	*net;
पूर्ण;

काष्ठा tc_action_ops;

काष्ठा tc_action अणु
	स्थिर काष्ठा tc_action_ops	*ops;
	__u32				type; /* क्रम backward compat(TCA_OLD_COMPAT) */
	काष्ठा tcf_idrinfo		*idrinfo;

	u32				tcfa_index;
	refcount_t			tcfa_refcnt;
	atomic_t			tcfa_bindcnt;
	पूर्णांक				tcfa_action;
	काष्ठा tcf_t			tcfa_पंचांग;
	काष्ठा gnet_stats_basic_packed	tcfa_bstats;
	काष्ठा gnet_stats_basic_packed	tcfa_bstats_hw;
	काष्ठा gnet_stats_queue		tcfa_qstats;
	काष्ठा net_rate_estimator __rcu *tcfa_rate_est;
	spinlock_t			tcfa_lock;
	काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats;
	काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats_hw;
	काष्ठा gnet_stats_queue __percpu *cpu_qstats;
	काष्ठा tc_cookie	__rcu *act_cookie;
	काष्ठा tcf_chain	__rcu *जाओ_chain;
	u32			tcfa_flags;
	u8			hw_stats;
	u8			used_hw_stats;
	bool			used_hw_stats_valid;
पूर्ण;
#घोषणा tcf_index	common.tcfa_index
#घोषणा tcf_refcnt	common.tcfa_refcnt
#घोषणा tcf_bindcnt	common.tcfa_bindcnt
#घोषणा tcf_action	common.tcfa_action
#घोषणा tcf_पंचांग		common.tcfa_पंचांग
#घोषणा tcf_bstats	common.tcfa_bstats
#घोषणा tcf_qstats	common.tcfa_qstats
#घोषणा tcf_rate_est	common.tcfa_rate_est
#घोषणा tcf_lock	common.tcfa_lock

#घोषणा TCA_ACT_HW_STATS_ANY (TCA_ACT_HW_STATS_IMMEDIATE | \
			      TCA_ACT_HW_STATS_DELAYED)

/* Update lastuse only अगर needed, to aव्योम dirtying a cache line.
 * We use a temp variable to aव्योम fetching jअगरfies twice.
 */
अटल अंतरभूत व्योम tcf_lastuse_update(काष्ठा tcf_t *पंचांग)
अणु
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (पंचांग->lastuse != now)
		पंचांग->lastuse = now;
	अगर (unlikely(!पंचांग->firstuse))
		पंचांग->firstuse = now;
पूर्ण

अटल अंतरभूत व्योम tcf_पंचांग_dump(काष्ठा tcf_t *dपंचांग, स्थिर काष्ठा tcf_t *sपंचांग)
अणु
	dपंचांग->install = jअगरfies_to_घड़ी_प्रकार(jअगरfies - sपंचांग->install);
	dपंचांग->lastuse = jअगरfies_to_घड़ी_प्रकार(jअगरfies - sपंचांग->lastuse);
	dपंचांग->firstuse = sपंचांग->firstuse ?
		jअगरfies_to_घड़ी_प्रकार(jअगरfies - sपंचांग->firstuse) : 0;
	dपंचांग->expires = jअगरfies_to_घड़ी_प्रकार(sपंचांग->expires);
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT

#घोषणा ACT_P_CREATED 1
#घोषणा ACT_P_DELETED 1

प्रकार व्योम (*tc_action_priv_deकाष्ठाor)(व्योम *priv);

काष्ठा tc_action_ops अणु
	काष्ठा list_head head;
	अक्षर    kind[IFNAMSIZ];
	क्रमागत tca_id  id; /* identअगरier should match kind */
	माप_प्रकार	size;
	काष्ठा module		*owner;
	पूर्णांक     (*act)(काष्ठा sk_buff *, स्थिर काष्ठा tc_action *,
		       काष्ठा tcf_result *); /* called under RCU BH lock*/
	पूर्णांक     (*dump)(काष्ठा sk_buff *, काष्ठा tc_action *, पूर्णांक, पूर्णांक);
	व्योम	(*cleanup)(काष्ठा tc_action *);
	पूर्णांक     (*lookup)(काष्ठा net *net, काष्ठा tc_action **a, u32 index);
	पूर्णांक     (*init)(काष्ठा net *net, काष्ठा nlattr *nla,
			काष्ठा nlattr *est, काष्ठा tc_action **act, पूर्णांक ovr,
			पूर्णांक bind, bool rtnl_held, काष्ठा tcf_proto *tp,
			u32 flags, काष्ठा netlink_ext_ack *extack);
	पूर्णांक     (*walk)(काष्ठा net *, काष्ठा sk_buff *,
			काष्ठा netlink_callback *, पूर्णांक,
			स्थिर काष्ठा tc_action_ops *,
			काष्ठा netlink_ext_ack *);
	व्योम	(*stats_update)(काष्ठा tc_action *, u64, u64, u64, u64, bool);
	माप_प्रकार  (*get_fill_size)(स्थिर काष्ठा tc_action *act);
	काष्ठा net_device *(*get_dev)(स्थिर काष्ठा tc_action *a,
				      tc_action_priv_deकाष्ठाor *deकाष्ठाor);
	काष्ठा psample_group *
	(*get_psample_group)(स्थिर काष्ठा tc_action *a,
			     tc_action_priv_deकाष्ठाor *deकाष्ठाor);
पूर्ण;

काष्ठा tc_action_net अणु
	काष्ठा tcf_idrinfo *idrinfo;
	स्थिर काष्ठा tc_action_ops *ops;
पूर्ण;

अटल अंतरभूत
पूर्णांक tc_action_net_init(काष्ठा net *net, काष्ठा tc_action_net *tn,
		       स्थिर काष्ठा tc_action_ops *ops)
अणु
	पूर्णांक err = 0;

	tn->idrinfo = kदो_स्मृति(माप(*tn->idrinfo), GFP_KERNEL);
	अगर (!tn->idrinfo)
		वापस -ENOMEM;
	tn->ops = ops;
	tn->idrinfo->net = net;
	mutex_init(&tn->idrinfo->lock);
	idr_init(&tn->idrinfo->action_idr);
	वापस err;
पूर्ण

व्योम tcf_idrinfo_destroy(स्थिर काष्ठा tc_action_ops *ops,
			 काष्ठा tcf_idrinfo *idrinfo);

अटल अंतरभूत व्योम tc_action_net_निकास(काष्ठा list_head *net_list,
				      अचिन्हित पूर्णांक id)
अणु
	काष्ठा net *net;

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		काष्ठा tc_action_net *tn = net_generic(net, id);

		tcf_idrinfo_destroy(tn->ops, tn->idrinfo);
		kमुक्त(tn->idrinfo);
	पूर्ण
	rtnl_unlock();
पूर्ण

पूर्णांक tcf_generic_walker(काष्ठा tc_action_net *tn, काष्ठा sk_buff *skb,
		       काष्ठा netlink_callback *cb, पूर्णांक type,
		       स्थिर काष्ठा tc_action_ops *ops,
		       काष्ठा netlink_ext_ack *extack);
पूर्णांक tcf_idr_search(काष्ठा tc_action_net *tn, काष्ठा tc_action **a, u32 index);
पूर्णांक tcf_idr_create(काष्ठा tc_action_net *tn, u32 index, काष्ठा nlattr *est,
		   काष्ठा tc_action **a, स्थिर काष्ठा tc_action_ops *ops,
		   पूर्णांक bind, bool cpustats, u32 flags);
पूर्णांक tcf_idr_create_from_flags(काष्ठा tc_action_net *tn, u32 index,
			      काष्ठा nlattr *est, काष्ठा tc_action **a,
			      स्थिर काष्ठा tc_action_ops *ops, पूर्णांक bind,
			      u32 flags);
व्योम tcf_idr_insert_many(काष्ठा tc_action *actions[]);
व्योम tcf_idr_cleanup(काष्ठा tc_action_net *tn, u32 index);
पूर्णांक tcf_idr_check_alloc(काष्ठा tc_action_net *tn, u32 *index,
			काष्ठा tc_action **a, पूर्णांक bind);
पूर्णांक tcf_idr_release(काष्ठा tc_action *a, bool bind);

पूर्णांक tcf_रेजिस्टर_action(काष्ठा tc_action_ops *a, काष्ठा pernet_operations *ops);
पूर्णांक tcf_unरेजिस्टर_action(काष्ठा tc_action_ops *a,
			  काष्ठा pernet_operations *ops);
पूर्णांक tcf_action_destroy(काष्ठा tc_action *actions[], पूर्णांक bind);
पूर्णांक tcf_action_exec(काष्ठा sk_buff *skb, काष्ठा tc_action **actions,
		    पूर्णांक nr_actions, काष्ठा tcf_result *res);
पूर्णांक tcf_action_init(काष्ठा net *net, काष्ठा tcf_proto *tp, काष्ठा nlattr *nla,
		    काष्ठा nlattr *est, अक्षर *name, पूर्णांक ovr, पूर्णांक bind,
		    काष्ठा tc_action *actions[], पूर्णांक init_res[], माप_प्रकार *attr_size,
		    bool rtnl_held, काष्ठा netlink_ext_ack *extack);
काष्ठा tc_action_ops *tc_action_load_ops(अक्षर *name, काष्ठा nlattr *nla,
					 bool rtnl_held,
					 काष्ठा netlink_ext_ack *extack);
काष्ठा tc_action *tcf_action_init_1(काष्ठा net *net, काष्ठा tcf_proto *tp,
				    काष्ठा nlattr *nla, काष्ठा nlattr *est,
				    अक्षर *name, पूर्णांक ovr, पूर्णांक bind,
				    काष्ठा tc_action_ops *a_o, पूर्णांक *init_res,
				    bool rtnl_held,
				    काष्ठा netlink_ext_ack *extack);
पूर्णांक tcf_action_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *actions[], पूर्णांक bind,
		    पूर्णांक ref, bool terse);
पूर्णांक tcf_action_dump_old(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक, पूर्णांक);
पूर्णांक tcf_action_dump_1(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक, पूर्णांक);

अटल अंतरभूत व्योम tcf_action_update_bstats(काष्ठा tc_action *a,
					    काष्ठा sk_buff *skb)
अणु
	अगर (likely(a->cpu_bstats)) अणु
		bstats_cpu_update(this_cpu_ptr(a->cpu_bstats), skb);
		वापस;
	पूर्ण
	spin_lock(&a->tcfa_lock);
	bstats_update(&a->tcfa_bstats, skb);
	spin_unlock(&a->tcfa_lock);
पूर्ण

अटल अंतरभूत व्योम tcf_action_inc_drop_qstats(काष्ठा tc_action *a)
अणु
	अगर (likely(a->cpu_qstats)) अणु
		qstats_drop_inc(this_cpu_ptr(a->cpu_qstats));
		वापस;
	पूर्ण
	spin_lock(&a->tcfa_lock);
	qstats_drop_inc(&a->tcfa_qstats);
	spin_unlock(&a->tcfa_lock);
पूर्ण

अटल अंतरभूत व्योम tcf_action_inc_overlimit_qstats(काष्ठा tc_action *a)
अणु
	अगर (likely(a->cpu_qstats)) अणु
		qstats_overlimit_inc(this_cpu_ptr(a->cpu_qstats));
		वापस;
	पूर्ण
	spin_lock(&a->tcfa_lock);
	qstats_overlimit_inc(&a->tcfa_qstats);
	spin_unlock(&a->tcfa_lock);
पूर्ण

व्योम tcf_action_update_stats(काष्ठा tc_action *a, u64 bytes, u64 packets,
			     u64 drops, bool hw);
पूर्णांक tcf_action_copy_stats(काष्ठा sk_buff *, काष्ठा tc_action *, पूर्णांक);

पूर्णांक tcf_action_check_ctrlact(पूर्णांक action, काष्ठा tcf_proto *tp,
			     काष्ठा tcf_chain **handle,
			     काष्ठा netlink_ext_ack *newchain);
काष्ठा tcf_chain *tcf_action_set_ctrlact(काष्ठा tc_action *a, पूर्णांक action,
					 काष्ठा tcf_chain *newchain);

#अगर_घोषित CONFIG_INET
DECLARE_STATIC_KEY_FALSE(tcf_frag_xmit_count);
#पूर्ण_अगर

पूर्णांक tcf_dev_queue_xmit(काष्ठा sk_buff *skb, पूर्णांक (*xmit)(काष्ठा sk_buff *skb));
#पूर्ण_अगर /* CONFIG_NET_CLS_ACT */

अटल अंतरभूत व्योम tcf_action_stats_update(काष्ठा tc_action *a, u64 bytes,
					   u64 packets, u64 drops,
					   u64 lastuse, bool hw)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (!a->ops->stats_update)
		वापस;

	a->ops->stats_update(a, bytes, packets, drops, lastuse, hw);
#पूर्ण_अगर
पूर्ण


#पूर्ण_अगर
