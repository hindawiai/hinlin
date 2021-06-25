<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_api.c	Packet classअगरier API.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Changes:
 *
 * Eduarकरो J. Blanco <ejbs@netद_असल.com.uy> :990222: kmod support
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/jhash.h>
#समावेश <linux/rculist.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_vlan.h>
#समावेश <net/tc_act/tc_tunnel_key.h>
#समावेश <net/tc_act/tc_csum.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_police.h>
#समावेश <net/tc_act/tc_sample.h>
#समावेश <net/tc_act/tc_skbedit.h>
#समावेश <net/tc_act/tc_ct.h>
#समावेश <net/tc_act/tc_mpls.h>
#समावेश <net/tc_act/tc_gate.h>
#समावेश <net/flow_offload.h>

बाह्य स्थिर काष्ठा nla_policy rपंचांग_tca_policy[TCA_MAX + 1];

/* The list of all installed classअगरier types */
अटल LIST_HEAD(tcf_proto_base);

/* Protects list of रेजिस्टरed TC modules. It is pure SMP lock. */
अटल DEFINE_RWLOCK(cls_mod_lock);

अटल u32 destroy_obj_hashfn(स्थिर काष्ठा tcf_proto *tp)
अणु
	वापस jhash_3words(tp->chain->index, tp->prio,
			    (__क्रमce __u32)tp->protocol, 0);
पूर्ण

अटल व्योम tcf_proto_संकेत_destroying(काष्ठा tcf_chain *chain,
					काष्ठा tcf_proto *tp)
अणु
	काष्ठा tcf_block *block = chain->block;

	mutex_lock(&block->proto_destroy_lock);
	hash_add_rcu(block->proto_destroy_ht, &tp->destroy_ht_node,
		     destroy_obj_hashfn(tp));
	mutex_unlock(&block->proto_destroy_lock);
पूर्ण

अटल bool tcf_proto_cmp(स्थिर काष्ठा tcf_proto *tp1,
			  स्थिर काष्ठा tcf_proto *tp2)
अणु
	वापस tp1->chain->index == tp2->chain->index &&
	       tp1->prio == tp2->prio &&
	       tp1->protocol == tp2->protocol;
पूर्ण

अटल bool tcf_proto_exists_destroying(काष्ठा tcf_chain *chain,
					काष्ठा tcf_proto *tp)
अणु
	u32 hash = destroy_obj_hashfn(tp);
	काष्ठा tcf_proto *iter;
	bool found = false;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(chain->block->proto_destroy_ht, iter,
				   destroy_ht_node, hash) अणु
		अगर (tcf_proto_cmp(tp, iter)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस found;
पूर्ण

अटल व्योम
tcf_proto_संकेत_destroyed(काष्ठा tcf_chain *chain, काष्ठा tcf_proto *tp)
अणु
	काष्ठा tcf_block *block = chain->block;

	mutex_lock(&block->proto_destroy_lock);
	अगर (hash_hashed(&tp->destroy_ht_node))
		hash_del_rcu(&tp->destroy_ht_node);
	mutex_unlock(&block->proto_destroy_lock);
पूर्ण

/* Find classअगरier type by string name */

अटल स्थिर काष्ठा tcf_proto_ops *__tcf_proto_lookup_ops(स्थिर अक्षर *kind)
अणु
	स्थिर काष्ठा tcf_proto_ops *t, *res = शून्य;

	अगर (kind) अणु
		पढ़ो_lock(&cls_mod_lock);
		list_क्रम_each_entry(t, &tcf_proto_base, head) अणु
			अगर (म_भेद(kind, t->kind) == 0) अणु
				अगर (try_module_get(t->owner))
					res = t;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&cls_mod_lock);
	पूर्ण
	वापस res;
पूर्ण

अटल स्थिर काष्ठा tcf_proto_ops *
tcf_proto_lookup_ops(स्थिर अक्षर *kind, bool rtnl_held,
		     काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा tcf_proto_ops *ops;

	ops = __tcf_proto_lookup_ops(kind);
	अगर (ops)
		वापस ops;
#अगर_घोषित CONFIG_MODULES
	अगर (rtnl_held)
		rtnl_unlock();
	request_module("cls_%s", kind);
	अगर (rtnl_held)
		rtnl_lock();
	ops = __tcf_proto_lookup_ops(kind);
	/* We dropped the RTNL semaphore in order to perक्रमm
	 * the module load. So, even अगर we succeeded in loading
	 * the module we have to replay the request. We indicate
	 * this using -EAGAIN.
	 */
	अगर (ops) अणु
		module_put(ops->owner);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण
#पूर्ण_अगर
	NL_SET_ERR_MSG(extack, "TC classifier not found");
	वापस ERR_PTR(-ENOENT);
पूर्ण

/* Register(unरेजिस्टर) new classअगरier type */

पूर्णांक रेजिस्टर_tcf_proto_ops(काष्ठा tcf_proto_ops *ops)
अणु
	काष्ठा tcf_proto_ops *t;
	पूर्णांक rc = -EEXIST;

	ग_लिखो_lock(&cls_mod_lock);
	list_क्रम_each_entry(t, &tcf_proto_base, head)
		अगर (!म_भेद(ops->kind, t->kind))
			जाओ out;

	list_add_tail(&ops->head, &tcf_proto_base);
	rc = 0;
out:
	ग_लिखो_unlock(&cls_mod_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_tcf_proto_ops);

अटल काष्ठा workqueue_काष्ठा *tc_filter_wq;

पूर्णांक unरेजिस्टर_tcf_proto_ops(काष्ठा tcf_proto_ops *ops)
अणु
	काष्ठा tcf_proto_ops *t;
	पूर्णांक rc = -ENOENT;

	/* Wait क्रम outstanding call_rcu()s, अगर any, from a
	 * tcf_proto_ops's destroy() handler.
	 */
	rcu_barrier();
	flush_workqueue(tc_filter_wq);

	ग_लिखो_lock(&cls_mod_lock);
	list_क्रम_each_entry(t, &tcf_proto_base, head) अणु
		अगर (t == ops) अणु
			list_del(&t->head);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&cls_mod_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_tcf_proto_ops);

bool tcf_queue_work(काष्ठा rcu_work *rwork, work_func_t func)
अणु
	INIT_RCU_WORK(rwork, func);
	वापस queue_rcu_work(tc_filter_wq, rwork);
पूर्ण
EXPORT_SYMBOL(tcf_queue_work);

/* Select new prio value from the range, managed by kernel. */

अटल अंतरभूत u32 tcf_स्वतः_prio(काष्ठा tcf_proto *tp)
अणु
	u32 first = TC_H_MAKE(0xC0000000U, 0U);

	अगर (tp)
		first = tp->prio - 1;

	वापस TC_H_MAJ(first);
पूर्ण

अटल bool tcf_proto_check_kind(काष्ठा nlattr *kind, अक्षर *name)
अणु
	अगर (kind)
		वापस nla_strscpy(name, kind, IFNAMSIZ) < 0;
	स_रखो(name, 0, IFNAMSIZ);
	वापस false;
पूर्ण

अटल bool tcf_proto_is_unlocked(स्थिर अक्षर *kind)
अणु
	स्थिर काष्ठा tcf_proto_ops *ops;
	bool ret;

	अगर (म_माप(kind) == 0)
		वापस false;

	ops = tcf_proto_lookup_ops(kind, false, शून्य);
	/* On error वापस false to take rtnl lock. Proto lookup/create
	 * functions will perक्रमm lookup again and properly handle errors.
	 */
	अगर (IS_ERR(ops))
		वापस false;

	ret = !!(ops->flags & TCF_PROTO_OPS_DOIT_UNLOCKED);
	module_put(ops->owner);
	वापस ret;
पूर्ण

अटल काष्ठा tcf_proto *tcf_proto_create(स्थिर अक्षर *kind, u32 protocol,
					  u32 prio, काष्ठा tcf_chain *chain,
					  bool rtnl_held,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_proto *tp;
	पूर्णांक err;

	tp = kzalloc(माप(*tp), GFP_KERNEL);
	अगर (!tp)
		वापस ERR_PTR(-ENOBUFS);

	tp->ops = tcf_proto_lookup_ops(kind, rtnl_held, extack);
	अगर (IS_ERR(tp->ops)) अणु
		err = PTR_ERR(tp->ops);
		जाओ errout;
	पूर्ण
	tp->classअगरy = tp->ops->classअगरy;
	tp->protocol = protocol;
	tp->prio = prio;
	tp->chain = chain;
	spin_lock_init(&tp->lock);
	refcount_set(&tp->refcnt, 1);

	err = tp->ops->init(tp);
	अगर (err) अणु
		module_put(tp->ops->owner);
		जाओ errout;
	पूर्ण
	वापस tp;

errout:
	kमुक्त(tp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tcf_proto_get(काष्ठा tcf_proto *tp)
अणु
	refcount_inc(&tp->refcnt);
पूर्ण

अटल व्योम tcf_chain_put(काष्ठा tcf_chain *chain);

अटल व्योम tcf_proto_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			      bool sig_destroy, काष्ठा netlink_ext_ack *extack)
अणु
	tp->ops->destroy(tp, rtnl_held, extack);
	अगर (sig_destroy)
		tcf_proto_संकेत_destroyed(tp->chain, tp);
	tcf_chain_put(tp->chain);
	module_put(tp->ops->owner);
	kमुक्त_rcu(tp, rcu);
पूर्ण

अटल व्योम tcf_proto_put(काष्ठा tcf_proto *tp, bool rtnl_held,
			  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (refcount_dec_and_test(&tp->refcnt))
		tcf_proto_destroy(tp, rtnl_held, true, extack);
पूर्ण

अटल bool tcf_proto_check_delete(काष्ठा tcf_proto *tp)
अणु
	अगर (tp->ops->delete_empty)
		वापस tp->ops->delete_empty(tp);

	tp->deleting = true;
	वापस tp->deleting;
पूर्ण

अटल व्योम tcf_proto_mark_delete(काष्ठा tcf_proto *tp)
अणु
	spin_lock(&tp->lock);
	tp->deleting = true;
	spin_unlock(&tp->lock);
पूर्ण

अटल bool tcf_proto_is_deleting(काष्ठा tcf_proto *tp)
अणु
	bool deleting;

	spin_lock(&tp->lock);
	deleting = tp->deleting;
	spin_unlock(&tp->lock);

	वापस deleting;
पूर्ण

#घोषणा ASSERT_BLOCK_LOCKED(block)					\
	lockdep_निश्चित_held(&(block)->lock)

काष्ठा tcf_filter_chain_list_item अणु
	काष्ठा list_head list;
	tcf_chain_head_change_t *chain_head_change;
	व्योम *chain_head_change_priv;
पूर्ण;

अटल काष्ठा tcf_chain *tcf_chain_create(काष्ठा tcf_block *block,
					  u32 chain_index)
अणु
	काष्ठा tcf_chain *chain;

	ASSERT_BLOCK_LOCKED(block);

	chain = kzalloc(माप(*chain), GFP_KERNEL);
	अगर (!chain)
		वापस शून्य;
	list_add_tail_rcu(&chain->list, &block->chain_list);
	mutex_init(&chain->filter_chain_lock);
	chain->block = block;
	chain->index = chain_index;
	chain->refcnt = 1;
	अगर (!chain->index)
		block->chain0.chain = chain;
	वापस chain;
पूर्ण

अटल व्योम tcf_chain_head_change_item(काष्ठा tcf_filter_chain_list_item *item,
				       काष्ठा tcf_proto *tp_head)
अणु
	अगर (item->chain_head_change)
		item->chain_head_change(tp_head, item->chain_head_change_priv);
पूर्ण

अटल व्योम tcf_chain0_head_change(काष्ठा tcf_chain *chain,
				   काष्ठा tcf_proto *tp_head)
अणु
	काष्ठा tcf_filter_chain_list_item *item;
	काष्ठा tcf_block *block = chain->block;

	अगर (chain->index)
		वापस;

	mutex_lock(&block->lock);
	list_क्रम_each_entry(item, &block->chain0.filter_chain_list, list)
		tcf_chain_head_change_item(item, tp_head);
	mutex_unlock(&block->lock);
पूर्ण

/* Returns true अगर block can be safely मुक्तd. */

अटल bool tcf_chain_detach(काष्ठा tcf_chain *chain)
अणु
	काष्ठा tcf_block *block = chain->block;

	ASSERT_BLOCK_LOCKED(block);

	list_del_rcu(&chain->list);
	अगर (!chain->index)
		block->chain0.chain = शून्य;

	अगर (list_empty(&block->chain_list) &&
	    refcount_पढ़ो(&block->refcnt) == 0)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम tcf_block_destroy(काष्ठा tcf_block *block)
अणु
	mutex_destroy(&block->lock);
	mutex_destroy(&block->proto_destroy_lock);
	kमुक्त_rcu(block, rcu);
पूर्ण

अटल व्योम tcf_chain_destroy(काष्ठा tcf_chain *chain, bool मुक्त_block)
अणु
	काष्ठा tcf_block *block = chain->block;

	mutex_destroy(&chain->filter_chain_lock);
	kमुक्त_rcu(chain, rcu);
	अगर (मुक्त_block)
		tcf_block_destroy(block);
पूर्ण

अटल व्योम tcf_chain_hold(काष्ठा tcf_chain *chain)
अणु
	ASSERT_BLOCK_LOCKED(chain->block);

	++chain->refcnt;
पूर्ण

अटल bool tcf_chain_held_by_acts_only(काष्ठा tcf_chain *chain)
अणु
	ASSERT_BLOCK_LOCKED(chain->block);

	/* In हाल all the references are action references, this
	 * chain should not be shown to the user.
	 */
	वापस chain->refcnt == chain->action_refcnt;
पूर्ण

अटल काष्ठा tcf_chain *tcf_chain_lookup(काष्ठा tcf_block *block,
					  u32 chain_index)
अणु
	काष्ठा tcf_chain *chain;

	ASSERT_BLOCK_LOCKED(block);

	list_क्रम_each_entry(chain, &block->chain_list, list) अणु
		अगर (chain->index == chain_index)
			वापस chain;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
अटल काष्ठा tcf_chain *tcf_chain_lookup_rcu(स्थिर काष्ठा tcf_block *block,
					      u32 chain_index)
अणु
	काष्ठा tcf_chain *chain;

	list_क्रम_each_entry_rcu(chain, &block->chain_list, list) अणु
		अगर (chain->index == chain_index)
			वापस chain;
	पूर्ण
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tc_chain_notअगरy(काष्ठा tcf_chain *chain, काष्ठा sk_buff *oskb,
			   u32 seq, u16 flags, पूर्णांक event, bool unicast);

अटल काष्ठा tcf_chain *__tcf_chain_get(काष्ठा tcf_block *block,
					 u32 chain_index, bool create,
					 bool by_act)
अणु
	काष्ठा tcf_chain *chain = शून्य;
	bool is_first_reference;

	mutex_lock(&block->lock);
	chain = tcf_chain_lookup(block, chain_index);
	अगर (chain) अणु
		tcf_chain_hold(chain);
	पूर्ण अन्यथा अणु
		अगर (!create)
			जाओ errout;
		chain = tcf_chain_create(block, chain_index);
		अगर (!chain)
			जाओ errout;
	पूर्ण

	अगर (by_act)
		++chain->action_refcnt;
	is_first_reference = chain->refcnt - chain->action_refcnt == 1;
	mutex_unlock(&block->lock);

	/* Send notअगरication only in हाल we got the first
	 * non-action reference. Until then, the chain acts only as
	 * a placeholder क्रम actions poपूर्णांकing to it and user ought
	 * not know about them.
	 */
	अगर (is_first_reference && !by_act)
		tc_chain_notअगरy(chain, शून्य, 0, NLM_F_CREATE | NLM_F_EXCL,
				RTM_NEWCHAIN, false);

	वापस chain;

errout:
	mutex_unlock(&block->lock);
	वापस chain;
पूर्ण

अटल काष्ठा tcf_chain *tcf_chain_get(काष्ठा tcf_block *block, u32 chain_index,
				       bool create)
अणु
	वापस __tcf_chain_get(block, chain_index, create, false);
पूर्ण

काष्ठा tcf_chain *tcf_chain_get_by_act(काष्ठा tcf_block *block, u32 chain_index)
अणु
	वापस __tcf_chain_get(block, chain_index, true, true);
पूर्ण
EXPORT_SYMBOL(tcf_chain_get_by_act);

अटल व्योम tc_chain_पंचांगplt_del(स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops,
			       व्योम *पंचांगplt_priv);
अटल पूर्णांक tc_chain_notअगरy_delete(स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops,
				  व्योम *पंचांगplt_priv, u32 chain_index,
				  काष्ठा tcf_block *block, काष्ठा sk_buff *oskb,
				  u32 seq, u16 flags, bool unicast);

अटल व्योम __tcf_chain_put(काष्ठा tcf_chain *chain, bool by_act,
			    bool explicitly_created)
अणु
	काष्ठा tcf_block *block = chain->block;
	स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops;
	bool मुक्त_block = false;
	अचिन्हित पूर्णांक refcnt;
	व्योम *पंचांगplt_priv;

	mutex_lock(&block->lock);
	अगर (explicitly_created) अणु
		अगर (!chain->explicitly_created) अणु
			mutex_unlock(&block->lock);
			वापस;
		पूर्ण
		chain->explicitly_created = false;
	पूर्ण

	अगर (by_act)
		chain->action_refcnt--;

	/* tc_chain_notअगरy_delete can't be called जबतक holding block lock.
	 * However, when block is unlocked chain can be changed concurrently, so
	 * save these to temporary variables.
	 */
	refcnt = --chain->refcnt;
	पंचांगplt_ops = chain->पंचांगplt_ops;
	पंचांगplt_priv = chain->पंचांगplt_priv;

	/* The last dropped non-action reference will trigger notअगरication. */
	अगर (refcnt - chain->action_refcnt == 0 && !by_act) अणु
		tc_chain_notअगरy_delete(पंचांगplt_ops, पंचांगplt_priv, chain->index,
				       block, शून्य, 0, 0, false);
		/* Last reference to chain, no need to lock. */
		chain->flushing = false;
	पूर्ण

	अगर (refcnt == 0)
		मुक्त_block = tcf_chain_detach(chain);
	mutex_unlock(&block->lock);

	अगर (refcnt == 0) अणु
		tc_chain_पंचांगplt_del(पंचांगplt_ops, पंचांगplt_priv);
		tcf_chain_destroy(chain, मुक्त_block);
	पूर्ण
पूर्ण

अटल व्योम tcf_chain_put(काष्ठा tcf_chain *chain)
अणु
	__tcf_chain_put(chain, false, false);
पूर्ण

व्योम tcf_chain_put_by_act(काष्ठा tcf_chain *chain)
अणु
	__tcf_chain_put(chain, true, false);
पूर्ण
EXPORT_SYMBOL(tcf_chain_put_by_act);

अटल व्योम tcf_chain_put_explicitly_created(काष्ठा tcf_chain *chain)
अणु
	__tcf_chain_put(chain, false, true);
पूर्ण

अटल व्योम tcf_chain_flush(काष्ठा tcf_chain *chain, bool rtnl_held)
अणु
	काष्ठा tcf_proto *tp, *tp_next;

	mutex_lock(&chain->filter_chain_lock);
	tp = tcf_chain_dereference(chain->filter_chain, chain);
	जबतक (tp) अणु
		tp_next = rcu_dereference_रक्षित(tp->next, 1);
		tcf_proto_संकेत_destroying(chain, tp);
		tp = tp_next;
	पूर्ण
	tp = tcf_chain_dereference(chain->filter_chain, chain);
	RCU_INIT_POINTER(chain->filter_chain, शून्य);
	tcf_chain0_head_change(chain, शून्य);
	chain->flushing = true;
	mutex_unlock(&chain->filter_chain_lock);

	जबतक (tp) अणु
		tp_next = rcu_dereference_रक्षित(tp->next, 1);
		tcf_proto_put(tp, rtnl_held, शून्य);
		tp = tp_next;
	पूर्ण
पूर्ण

अटल पूर्णांक tcf_block_setup(काष्ठा tcf_block *block,
			   काष्ठा flow_block_offload *bo);

अटल व्योम tcf_block_offload_init(काष्ठा flow_block_offload *bo,
				   काष्ठा net_device *dev, काष्ठा Qdisc *sch,
				   क्रमागत flow_block_command command,
				   क्रमागत flow_block_binder_type binder_type,
				   काष्ठा flow_block *flow_block,
				   bool shared, काष्ठा netlink_ext_ack *extack)
अणु
	bo->net = dev_net(dev);
	bo->command = command;
	bo->binder_type = binder_type;
	bo->block = flow_block;
	bo->block_shared = shared;
	bo->extack = extack;
	bo->sch = sch;
	INIT_LIST_HEAD(&bo->cb_list);
पूर्ण

अटल व्योम tcf_block_unbind(काष्ठा tcf_block *block,
			     काष्ठा flow_block_offload *bo);

अटल व्योम tc_block_indr_cleanup(काष्ठा flow_block_cb *block_cb)
अणु
	काष्ठा tcf_block *block = block_cb->indr.data;
	काष्ठा net_device *dev = block_cb->indr.dev;
	काष्ठा Qdisc *sch = block_cb->indr.sch;
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा flow_block_offload bo = अणुपूर्ण;

	tcf_block_offload_init(&bo, dev, sch, FLOW_BLOCK_UNBIND,
			       block_cb->indr.binder_type,
			       &block->flow_block, tcf_block_shared(block),
			       &extack);
	rtnl_lock();
	करोwn_ग_लिखो(&block->cb_lock);
	list_del(&block_cb->driver_list);
	list_move(&block_cb->list, &bo.cb_list);
	tcf_block_unbind(block, &bo);
	up_ग_लिखो(&block->cb_lock);
	rtnl_unlock();
पूर्ण

अटल bool tcf_block_offload_in_use(काष्ठा tcf_block *block)
अणु
	वापस atomic_पढ़ो(&block->offloadcnt);
पूर्ण

अटल पूर्णांक tcf_block_offload_cmd(काष्ठा tcf_block *block,
				 काष्ठा net_device *dev, काष्ठा Qdisc *sch,
				 काष्ठा tcf_block_ext_info *ei,
				 क्रमागत flow_block_command command,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_block_offload bo = अणुपूर्ण;

	tcf_block_offload_init(&bo, dev, sch, command, ei->binder_type,
			       &block->flow_block, tcf_block_shared(block),
			       extack);

	अगर (dev->netdev_ops->nकरो_setup_tc) अणु
		पूर्णांक err;

		err = dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_BLOCK, &bo);
		अगर (err < 0) अणु
			अगर (err != -EOPNOTSUPP)
				NL_SET_ERR_MSG(extack, "Driver ndo_setup_tc failed");
			वापस err;
		पूर्ण

		वापस tcf_block_setup(block, &bo);
	पूर्ण

	flow_indr_dev_setup_offload(dev, sch, TC_SETUP_BLOCK, block, &bo,
				    tc_block_indr_cleanup);
	tcf_block_setup(block, &bo);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक tcf_block_offload_bind(काष्ठा tcf_block *block, काष्ठा Qdisc *q,
				  काष्ठा tcf_block_ext_info *ei,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = q->dev_queue->dev;
	पूर्णांक err;

	करोwn_ग_लिखो(&block->cb_lock);

	/* If tc offload feature is disabled and the block we try to bind
	 * to alपढ़ोy has some offloaded filters, क्रमbid to bind.
	 */
	अगर (dev->netdev_ops->nकरो_setup_tc &&
	    !tc_can_offload(dev) &&
	    tcf_block_offload_in_use(block)) अणु
		NL_SET_ERR_MSG(extack, "Bind to offloaded block failed as dev has offload disabled");
		err = -EOPNOTSUPP;
		जाओ err_unlock;
	पूर्ण

	err = tcf_block_offload_cmd(block, dev, q, ei, FLOW_BLOCK_BIND, extack);
	अगर (err == -EOPNOTSUPP)
		जाओ no_offload_dev_inc;
	अगर (err)
		जाओ err_unlock;

	up_ग_लिखो(&block->cb_lock);
	वापस 0;

no_offload_dev_inc:
	अगर (tcf_block_offload_in_use(block))
		जाओ err_unlock;

	err = 0;
	block->nooffloaddevcnt++;
err_unlock:
	up_ग_लिखो(&block->cb_lock);
	वापस err;
पूर्ण

अटल व्योम tcf_block_offload_unbind(काष्ठा tcf_block *block, काष्ठा Qdisc *q,
				     काष्ठा tcf_block_ext_info *ei)
अणु
	काष्ठा net_device *dev = q->dev_queue->dev;
	पूर्णांक err;

	करोwn_ग_लिखो(&block->cb_lock);
	err = tcf_block_offload_cmd(block, dev, q, ei, FLOW_BLOCK_UNBIND, शून्य);
	अगर (err == -EOPNOTSUPP)
		जाओ no_offload_dev_dec;
	up_ग_लिखो(&block->cb_lock);
	वापस;

no_offload_dev_dec:
	WARN_ON(block->nooffloaddevcnt-- == 0);
	up_ग_लिखो(&block->cb_lock);
पूर्ण

अटल पूर्णांक
tcf_chain0_head_change_cb_add(काष्ठा tcf_block *block,
			      काष्ठा tcf_block_ext_info *ei,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_filter_chain_list_item *item;
	काष्ठा tcf_chain *chain0;

	item = kदो_स्मृति(माप(*item), GFP_KERNEL);
	अगर (!item) अणु
		NL_SET_ERR_MSG(extack, "Memory allocation for head change callback item failed");
		वापस -ENOMEM;
	पूर्ण
	item->chain_head_change = ei->chain_head_change;
	item->chain_head_change_priv = ei->chain_head_change_priv;

	mutex_lock(&block->lock);
	chain0 = block->chain0.chain;
	अगर (chain0)
		tcf_chain_hold(chain0);
	अन्यथा
		list_add(&item->list, &block->chain0.filter_chain_list);
	mutex_unlock(&block->lock);

	अगर (chain0) अणु
		काष्ठा tcf_proto *tp_head;

		mutex_lock(&chain0->filter_chain_lock);

		tp_head = tcf_chain_dereference(chain0->filter_chain, chain0);
		अगर (tp_head)
			tcf_chain_head_change_item(item, tp_head);

		mutex_lock(&block->lock);
		list_add(&item->list, &block->chain0.filter_chain_list);
		mutex_unlock(&block->lock);

		mutex_unlock(&chain0->filter_chain_lock);
		tcf_chain_put(chain0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
tcf_chain0_head_change_cb_del(काष्ठा tcf_block *block,
			      काष्ठा tcf_block_ext_info *ei)
अणु
	काष्ठा tcf_filter_chain_list_item *item;

	mutex_lock(&block->lock);
	list_क्रम_each_entry(item, &block->chain0.filter_chain_list, list) अणु
		अगर ((!ei->chain_head_change && !ei->chain_head_change_priv) ||
		    (item->chain_head_change == ei->chain_head_change &&
		     item->chain_head_change_priv == ei->chain_head_change_priv)) अणु
			अगर (block->chain0.chain)
				tcf_chain_head_change_item(item, शून्य);
			list_del(&item->list);
			mutex_unlock(&block->lock);

			kमुक्त(item);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&block->lock);
	WARN_ON(1);
पूर्ण

काष्ठा tcf_net अणु
	spinlock_t idr_lock; /* Protects idr */
	काष्ठा idr idr;
पूर्ण;

अटल अचिन्हित पूर्णांक tcf_net_id;

अटल पूर्णांक tcf_block_insert(काष्ठा tcf_block *block, काष्ठा net *net,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_net *tn = net_generic(net, tcf_net_id);
	पूर्णांक err;

	idr_preload(GFP_KERNEL);
	spin_lock(&tn->idr_lock);
	err = idr_alloc_u32(&tn->idr, block, &block->index, block->index,
			    GFP_NOWAIT);
	spin_unlock(&tn->idr_lock);
	idr_preload_end();

	वापस err;
पूर्ण

अटल व्योम tcf_block_हटाओ(काष्ठा tcf_block *block, काष्ठा net *net)
अणु
	काष्ठा tcf_net *tn = net_generic(net, tcf_net_id);

	spin_lock(&tn->idr_lock);
	idr_हटाओ(&tn->idr, block->index);
	spin_unlock(&tn->idr_lock);
पूर्ण

अटल काष्ठा tcf_block *tcf_block_create(काष्ठा net *net, काष्ठा Qdisc *q,
					  u32 block_index,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block;

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block) अणु
		NL_SET_ERR_MSG(extack, "Memory allocation for block failed");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	mutex_init(&block->lock);
	mutex_init(&block->proto_destroy_lock);
	init_rwsem(&block->cb_lock);
	flow_block_init(&block->flow_block);
	INIT_LIST_HEAD(&block->chain_list);
	INIT_LIST_HEAD(&block->owner_list);
	INIT_LIST_HEAD(&block->chain0.filter_chain_list);

	refcount_set(&block->refcnt, 1);
	block->net = net;
	block->index = block_index;

	/* Don't store q poपूर्णांकer क्रम blocks which are shared */
	अगर (!tcf_block_shared(block))
		block->q = q;
	वापस block;
पूर्ण

अटल काष्ठा tcf_block *tcf_block_lookup(काष्ठा net *net, u32 block_index)
अणु
	काष्ठा tcf_net *tn = net_generic(net, tcf_net_id);

	वापस idr_find(&tn->idr, block_index);
पूर्ण

अटल काष्ठा tcf_block *tcf_block_refcnt_get(काष्ठा net *net, u32 block_index)
अणु
	काष्ठा tcf_block *block;

	rcu_पढ़ो_lock();
	block = tcf_block_lookup(net, block_index);
	अगर (block && !refcount_inc_not_zero(&block->refcnt))
		block = शून्य;
	rcu_पढ़ो_unlock();

	वापस block;
पूर्ण

अटल काष्ठा tcf_chain *
__tcf_get_next_chain(काष्ठा tcf_block *block, काष्ठा tcf_chain *chain)
अणु
	mutex_lock(&block->lock);
	अगर (chain)
		chain = list_is_last(&chain->list, &block->chain_list) ?
			शून्य : list_next_entry(chain, list);
	अन्यथा
		chain = list_first_entry_or_null(&block->chain_list,
						 काष्ठा tcf_chain, list);

	/* skip all action-only chains */
	जबतक (chain && tcf_chain_held_by_acts_only(chain))
		chain = list_is_last(&chain->list, &block->chain_list) ?
			शून्य : list_next_entry(chain, list);

	अगर (chain)
		tcf_chain_hold(chain);
	mutex_unlock(&block->lock);

	वापस chain;
पूर्ण

/* Function to be used by all clients that want to iterate over all chains on
 * block. It properly obtains block->lock and takes reference to chain beक्रमe
 * वापसing it. Users of this function must be tolerant to concurrent chain
 * insertion/deletion or ensure that no concurrent chain modअगरication is
 * possible. Note that all netlink dump callbacks cannot guarantee to provide
 * consistent dump because rtnl lock is released each समय skb is filled with
 * data and sent to user-space.
 */

काष्ठा tcf_chain *
tcf_get_next_chain(काष्ठा tcf_block *block, काष्ठा tcf_chain *chain)
अणु
	काष्ठा tcf_chain *chain_next = __tcf_get_next_chain(block, chain);

	अगर (chain)
		tcf_chain_put(chain);

	वापस chain_next;
पूर्ण
EXPORT_SYMBOL(tcf_get_next_chain);

अटल काष्ठा tcf_proto *
__tcf_get_next_proto(काष्ठा tcf_chain *chain, काष्ठा tcf_proto *tp)
अणु
	u32 prio = 0;

	ASSERT_RTNL();
	mutex_lock(&chain->filter_chain_lock);

	अगर (!tp) अणु
		tp = tcf_chain_dereference(chain->filter_chain, chain);
	पूर्ण अन्यथा अगर (tcf_proto_is_deleting(tp)) अणु
		/* 'deleting' flag is set and chain->filter_chain_lock was
		 * unlocked, which means next poपूर्णांकer could be invalid. Restart
		 * search.
		 */
		prio = tp->prio + 1;
		tp = tcf_chain_dereference(chain->filter_chain, chain);

		क्रम (; tp; tp = tcf_chain_dereference(tp->next, chain))
			अगर (!tp->deleting && tp->prio >= prio)
				अवरोध;
	पूर्ण अन्यथा अणु
		tp = tcf_chain_dereference(tp->next, chain);
	पूर्ण

	अगर (tp)
		tcf_proto_get(tp);

	mutex_unlock(&chain->filter_chain_lock);

	वापस tp;
पूर्ण

/* Function to be used by all clients that want to iterate over all tp's on
 * chain. Users of this function must be tolerant to concurrent tp
 * insertion/deletion or ensure that no concurrent chain modअगरication is
 * possible. Note that all netlink dump callbacks cannot guarantee to provide
 * consistent dump because rtnl lock is released each समय skb is filled with
 * data and sent to user-space.
 */

काष्ठा tcf_proto *
tcf_get_next_proto(काष्ठा tcf_chain *chain, काष्ठा tcf_proto *tp)
अणु
	काष्ठा tcf_proto *tp_next = __tcf_get_next_proto(chain, tp);

	अगर (tp)
		tcf_proto_put(tp, true, शून्य);

	वापस tp_next;
पूर्ण
EXPORT_SYMBOL(tcf_get_next_proto);

अटल व्योम tcf_block_flush_all_chains(काष्ठा tcf_block *block, bool rtnl_held)
अणु
	काष्ठा tcf_chain *chain;

	/* Last reference to block. At this poपूर्णांक chains cannot be added or
	 * हटाओd concurrently.
	 */
	क्रम (chain = tcf_get_next_chain(block, शून्य);
	     chain;
	     chain = tcf_get_next_chain(block, chain)) अणु
		tcf_chain_put_explicitly_created(chain);
		tcf_chain_flush(chain, rtnl_held);
	पूर्ण
पूर्ण

/* Lookup Qdisc and increments its reference counter.
 * Set parent, अगर necessary.
 */

अटल पूर्णांक __tcf_qdisc_find(काष्ठा net *net, काष्ठा Qdisc **q,
			    u32 *parent, पूर्णांक अगरindex, bool rtnl_held,
			    काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा Qdisc_class_ops *cops;
	काष्ठा net_device *dev;
	पूर्णांक err = 0;

	अगर (अगरindex == TCM_IFINDEX_MAGIC_BLOCK)
		वापस 0;

	rcu_पढ़ो_lock();

	/* Find link */
	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (!dev) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण

	/* Find qdisc */
	अगर (!*parent) अणु
		*q = dev->qdisc;
		*parent = (*q)->handle;
	पूर्ण अन्यथा अणु
		*q = qdisc_lookup_rcu(dev, TC_H_MAJ(*parent));
		अगर (!*q) अणु
			NL_SET_ERR_MSG(extack, "Parent Qdisc doesn't exists");
			err = -EINVAL;
			जाओ errout_rcu;
		पूर्ण
	पूर्ण

	*q = qdisc_refcount_inc_nz(*q);
	अगर (!*q) अणु
		NL_SET_ERR_MSG(extack, "Parent Qdisc doesn't exists");
		err = -EINVAL;
		जाओ errout_rcu;
	पूर्ण

	/* Is it classful? */
	cops = (*q)->ops->cl_ops;
	अगर (!cops) अणु
		NL_SET_ERR_MSG(extack, "Qdisc not classful");
		err = -EINVAL;
		जाओ errout_qdisc;
	पूर्ण

	अगर (!cops->tcf_block) अणु
		NL_SET_ERR_MSG(extack, "Class doesn't support blocks");
		err = -EOPNOTSUPP;
		जाओ errout_qdisc;
	पूर्ण

errout_rcu:
	/* At this poपूर्णांक we know that qdisc is not noop_qdisc,
	 * which means that qdisc holds a reference to net_device
	 * and we hold a reference to qdisc, so it is safe to release
	 * rcu पढ़ो lock.
	 */
	rcu_पढ़ो_unlock();
	वापस err;

errout_qdisc:
	rcu_पढ़ो_unlock();

	अगर (rtnl_held)
		qdisc_put(*q);
	अन्यथा
		qdisc_put_unlocked(*q);
	*q = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक __tcf_qdisc_cl_find(काष्ठा Qdisc *q, u32 parent, अचिन्हित दीर्घ *cl,
			       पूर्णांक अगरindex, काष्ठा netlink_ext_ack *extack)
अणु
	अगर (अगरindex == TCM_IFINDEX_MAGIC_BLOCK)
		वापस 0;

	/* Do we search क्रम filter, attached to class? */
	अगर (TC_H_MIN(parent)) अणु
		स्थिर काष्ठा Qdisc_class_ops *cops = q->ops->cl_ops;

		*cl = cops->find(q, parent);
		अगर (*cl == 0) अणु
			NL_SET_ERR_MSG(extack, "Specified class doesn't exist");
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा tcf_block *__tcf_block_find(काष्ठा net *net, काष्ठा Qdisc *q,
					  अचिन्हित दीर्घ cl, पूर्णांक अगरindex,
					  u32 block_index,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block;

	अगर (अगरindex == TCM_IFINDEX_MAGIC_BLOCK) अणु
		block = tcf_block_refcnt_get(net, block_index);
		अगर (!block) अणु
			NL_SET_ERR_MSG(extack, "Block of given index was not found");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा Qdisc_class_ops *cops = q->ops->cl_ops;

		block = cops->tcf_block(q, cl, extack);
		अगर (!block)
			वापस ERR_PTR(-EINVAL);

		अगर (tcf_block_shared(block)) अणु
			NL_SET_ERR_MSG(extack, "This filter block is shared. Please use the block index to manipulate the filters");
			वापस ERR_PTR(-EOPNOTSUPP);
		पूर्ण

		/* Always take reference to block in order to support execution
		 * of rules update path of cls API without rtnl lock. Caller
		 * must release block when it is finished using it. 'if' block
		 * of this conditional obtain reference to block by calling
		 * tcf_block_refcnt_get().
		 */
		refcount_inc(&block->refcnt);
	पूर्ण

	वापस block;
पूर्ण

अटल व्योम __tcf_block_put(काष्ठा tcf_block *block, काष्ठा Qdisc *q,
			    काष्ठा tcf_block_ext_info *ei, bool rtnl_held)
अणु
	अगर (refcount_dec_and_mutex_lock(&block->refcnt, &block->lock)) अणु
		/* Flushing/putting all chains will cause the block to be
		 * deallocated when last chain is मुक्तd. However, अगर chain_list
		 * is empty, block has to be manually deallocated. After block
		 * reference counter reached 0, it is no दीर्घer possible to
		 * increment it or add new chains to block.
		 */
		bool मुक्त_block = list_empty(&block->chain_list);

		mutex_unlock(&block->lock);
		अगर (tcf_block_shared(block))
			tcf_block_हटाओ(block, block->net);

		अगर (q)
			tcf_block_offload_unbind(block, q, ei);

		अगर (मुक्त_block)
			tcf_block_destroy(block);
		अन्यथा
			tcf_block_flush_all_chains(block, rtnl_held);
	पूर्ण अन्यथा अगर (q) अणु
		tcf_block_offload_unbind(block, q, ei);
	पूर्ण
पूर्ण

अटल व्योम tcf_block_refcnt_put(काष्ठा tcf_block *block, bool rtnl_held)
अणु
	__tcf_block_put(block, शून्य, शून्य, rtnl_held);
पूर्ण

/* Find tcf block.
 * Set q, parent, cl when appropriate.
 */

अटल काष्ठा tcf_block *tcf_block_find(काष्ठा net *net, काष्ठा Qdisc **q,
					u32 *parent, अचिन्हित दीर्घ *cl,
					पूर्णांक अगरindex, u32 block_index,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block;
	पूर्णांक err = 0;

	ASSERT_RTNL();

	err = __tcf_qdisc_find(net, q, parent, अगरindex, true, extack);
	अगर (err)
		जाओ errout;

	err = __tcf_qdisc_cl_find(*q, *parent, cl, अगरindex, extack);
	अगर (err)
		जाओ errout_qdisc;

	block = __tcf_block_find(net, *q, *cl, अगरindex, block_index, extack);
	अगर (IS_ERR(block)) अणु
		err = PTR_ERR(block);
		जाओ errout_qdisc;
	पूर्ण

	वापस block;

errout_qdisc:
	अगर (*q)
		qdisc_put(*q);
errout:
	*q = शून्य;
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tcf_block_release(काष्ठा Qdisc *q, काष्ठा tcf_block *block,
			      bool rtnl_held)
अणु
	अगर (!IS_ERR_OR_शून्य(block))
		tcf_block_refcnt_put(block, rtnl_held);

	अगर (q) अणु
		अगर (rtnl_held)
			qdisc_put(q);
		अन्यथा
			qdisc_put_unlocked(q);
	पूर्ण
पूर्ण

काष्ठा tcf_block_owner_item अणु
	काष्ठा list_head list;
	काष्ठा Qdisc *q;
	क्रमागत flow_block_binder_type binder_type;
पूर्ण;

अटल व्योम
tcf_block_owner_netअगर_keep_dst(काष्ठा tcf_block *block,
			       काष्ठा Qdisc *q,
			       क्रमागत flow_block_binder_type binder_type)
अणु
	अगर (block->keep_dst &&
	    binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS &&
	    binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS)
		netअगर_keep_dst(qdisc_dev(q));
पूर्ण

व्योम tcf_block_netअगर_keep_dst(काष्ठा tcf_block *block)
अणु
	काष्ठा tcf_block_owner_item *item;

	block->keep_dst = true;
	list_क्रम_each_entry(item, &block->owner_list, list)
		tcf_block_owner_netअगर_keep_dst(block, item->q,
					       item->binder_type);
पूर्ण
EXPORT_SYMBOL(tcf_block_netअगर_keep_dst);

अटल पूर्णांक tcf_block_owner_add(काष्ठा tcf_block *block,
			       काष्ठा Qdisc *q,
			       क्रमागत flow_block_binder_type binder_type)
अणु
	काष्ठा tcf_block_owner_item *item;

	item = kदो_स्मृति(माप(*item), GFP_KERNEL);
	अगर (!item)
		वापस -ENOMEM;
	item->q = q;
	item->binder_type = binder_type;
	list_add(&item->list, &block->owner_list);
	वापस 0;
पूर्ण

अटल व्योम tcf_block_owner_del(काष्ठा tcf_block *block,
				काष्ठा Qdisc *q,
				क्रमागत flow_block_binder_type binder_type)
अणु
	काष्ठा tcf_block_owner_item *item;

	list_क्रम_each_entry(item, &block->owner_list, list) अणु
		अगर (item->q == q && item->binder_type == binder_type) अणु
			list_del(&item->list);
			kमुक्त(item);
			वापस;
		पूर्ण
	पूर्ण
	WARN_ON(1);
पूर्ण

पूर्णांक tcf_block_get_ext(काष्ठा tcf_block **p_block, काष्ठा Qdisc *q,
		      काष्ठा tcf_block_ext_info *ei,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = qdisc_net(q);
	काष्ठा tcf_block *block = शून्य;
	पूर्णांक err;

	अगर (ei->block_index)
		/* block_index not 0 means the shared block is requested */
		block = tcf_block_refcnt_get(net, ei->block_index);

	अगर (!block) अणु
		block = tcf_block_create(net, q, ei->block_index, extack);
		अगर (IS_ERR(block))
			वापस PTR_ERR(block);
		अगर (tcf_block_shared(block)) अणु
			err = tcf_block_insert(block, net, extack);
			अगर (err)
				जाओ err_block_insert;
		पूर्ण
	पूर्ण

	err = tcf_block_owner_add(block, q, ei->binder_type);
	अगर (err)
		जाओ err_block_owner_add;

	tcf_block_owner_netअगर_keep_dst(block, q, ei->binder_type);

	err = tcf_chain0_head_change_cb_add(block, ei, extack);
	अगर (err)
		जाओ err_chain0_head_change_cb_add;

	err = tcf_block_offload_bind(block, q, ei, extack);
	अगर (err)
		जाओ err_block_offload_bind;

	*p_block = block;
	वापस 0;

err_block_offload_bind:
	tcf_chain0_head_change_cb_del(block, ei);
err_chain0_head_change_cb_add:
	tcf_block_owner_del(block, q, ei->binder_type);
err_block_owner_add:
err_block_insert:
	tcf_block_refcnt_put(block, true);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcf_block_get_ext);

अटल व्योम tcf_chain_head_change_dflt(काष्ठा tcf_proto *tp_head, व्योम *priv)
अणु
	काष्ठा tcf_proto __rcu **p_filter_chain = priv;

	rcu_assign_poपूर्णांकer(*p_filter_chain, tp_head);
पूर्ण

पूर्णांक tcf_block_get(काष्ठा tcf_block **p_block,
		  काष्ठा tcf_proto __rcu **p_filter_chain, काष्ठा Qdisc *q,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block_ext_info ei = अणु
		.chain_head_change = tcf_chain_head_change_dflt,
		.chain_head_change_priv = p_filter_chain,
	पूर्ण;

	WARN_ON(!p_filter_chain);
	वापस tcf_block_get_ext(p_block, q, &ei, extack);
पूर्ण
EXPORT_SYMBOL(tcf_block_get);

/* XXX: Standalone actions are not allowed to jump to any chain, and bound
 * actions should be all हटाओd after flushing.
 */
व्योम tcf_block_put_ext(काष्ठा tcf_block *block, काष्ठा Qdisc *q,
		       काष्ठा tcf_block_ext_info *ei)
अणु
	अगर (!block)
		वापस;
	tcf_chain0_head_change_cb_del(block, ei);
	tcf_block_owner_del(block, q, ei->binder_type);

	__tcf_block_put(block, q, ei, true);
पूर्ण
EXPORT_SYMBOL(tcf_block_put_ext);

व्योम tcf_block_put(काष्ठा tcf_block *block)
अणु
	काष्ठा tcf_block_ext_info ei = अणु0, पूर्ण;

	अगर (!block)
		वापस;
	tcf_block_put_ext(block, block->q, &ei);
पूर्ण

EXPORT_SYMBOL(tcf_block_put);

अटल पूर्णांक
tcf_block_playback_offloads(काष्ठा tcf_block *block, flow_setup_cb_t *cb,
			    व्योम *cb_priv, bool add, bool offload_in_use,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_chain *chain, *chain_prev;
	काष्ठा tcf_proto *tp, *tp_prev;
	पूर्णांक err;

	lockdep_निश्चित_held(&block->cb_lock);

	क्रम (chain = __tcf_get_next_chain(block, शून्य);
	     chain;
	     chain_prev = chain,
		     chain = __tcf_get_next_chain(block, chain),
		     tcf_chain_put(chain_prev)) अणु
		क्रम (tp = __tcf_get_next_proto(chain, शून्य); tp;
		     tp_prev = tp,
			     tp = __tcf_get_next_proto(chain, tp),
			     tcf_proto_put(tp_prev, true, शून्य)) अणु
			अगर (tp->ops->reoffload) अणु
				err = tp->ops->reoffload(tp, add, cb, cb_priv,
							 extack);
				अगर (err && add)
					जाओ err_playback_हटाओ;
			पूर्ण अन्यथा अगर (add && offload_in_use) अणु
				err = -EOPNOTSUPP;
				NL_SET_ERR_MSG(extack, "Filter HW offload failed - classifier without re-offloading support");
				जाओ err_playback_हटाओ;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_playback_हटाओ:
	tcf_proto_put(tp, true, शून्य);
	tcf_chain_put(chain);
	tcf_block_playback_offloads(block, cb, cb_priv, false, offload_in_use,
				    extack);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_block_bind(काष्ठा tcf_block *block,
			  काष्ठा flow_block_offload *bo)
अणु
	काष्ठा flow_block_cb *block_cb, *next;
	पूर्णांक err, i = 0;

	lockdep_निश्चित_held(&block->cb_lock);

	list_क्रम_each_entry(block_cb, &bo->cb_list, list) अणु
		err = tcf_block_playback_offloads(block, block_cb->cb,
						  block_cb->cb_priv, true,
						  tcf_block_offload_in_use(block),
						  bo->extack);
		अगर (err)
			जाओ err_unroll;
		अगर (!bo->unlocked_driver_cb)
			block->lockeddevcnt++;

		i++;
	पूर्ण
	list_splice(&bo->cb_list, &block->flow_block.cb_list);

	वापस 0;

err_unroll:
	list_क्रम_each_entry_safe(block_cb, next, &bo->cb_list, list) अणु
		अगर (i-- > 0) अणु
			list_del(&block_cb->list);
			tcf_block_playback_offloads(block, block_cb->cb,
						    block_cb->cb_priv, false,
						    tcf_block_offload_in_use(block),
						    शून्य);
			अगर (!bo->unlocked_driver_cb)
				block->lockeddevcnt--;
		पूर्ण
		flow_block_cb_मुक्त(block_cb);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम tcf_block_unbind(काष्ठा tcf_block *block,
			     काष्ठा flow_block_offload *bo)
अणु
	काष्ठा flow_block_cb *block_cb, *next;

	lockdep_निश्चित_held(&block->cb_lock);

	list_क्रम_each_entry_safe(block_cb, next, &bo->cb_list, list) अणु
		tcf_block_playback_offloads(block, block_cb->cb,
					    block_cb->cb_priv, false,
					    tcf_block_offload_in_use(block),
					    शून्य);
		list_del(&block_cb->list);
		flow_block_cb_मुक्त(block_cb);
		अगर (!bo->unlocked_driver_cb)
			block->lockeddevcnt--;
	पूर्ण
पूर्ण

अटल पूर्णांक tcf_block_setup(काष्ठा tcf_block *block,
			   काष्ठा flow_block_offload *bo)
अणु
	पूर्णांक err;

	चयन (bo->command) अणु
	हाल FLOW_BLOCK_BIND:
		err = tcf_block_bind(block, bo);
		अवरोध;
	हाल FLOW_BLOCK_UNBIND:
		err = 0;
		tcf_block_unbind(block, bo);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

/* Main classअगरier routine: scans classअगरier chain attached
 * to this qdisc, (optionally) tests क्रम protocol and asks
 * specअगरic classअगरiers.
 */
अटल अंतरभूत पूर्णांक __tcf_classअगरy(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा tcf_proto *tp,
				 स्थिर काष्ठा tcf_proto *orig_tp,
				 काष्ठा tcf_result *res,
				 bool compat_mode,
				 u32 *last_executed_chain)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	स्थिर पूर्णांक max_reclassअगरy_loop = 4;
	स्थिर काष्ठा tcf_proto *first_tp;
	पूर्णांक limit = 0;

reclassअगरy:
#पूर्ण_अगर
	क्रम (; tp; tp = rcu_dereference_bh(tp->next)) अणु
		__be16 protocol = skb_protocol(skb, false);
		पूर्णांक err;

		अगर (tp->protocol != protocol &&
		    tp->protocol != htons(ETH_P_ALL))
			जारी;

		err = tp->classअगरy(skb, tp, res);
#अगर_घोषित CONFIG_NET_CLS_ACT
		अगर (unlikely(err == TC_ACT_RECLASSIFY && !compat_mode)) अणु
			first_tp = orig_tp;
			*last_executed_chain = first_tp->chain->index;
			जाओ reset;
		पूर्ण अन्यथा अगर (unlikely(TC_ACT_EXT_CMP(err, TC_ACT_GOTO_CHAIN))) अणु
			first_tp = res->जाओ_tp;
			*last_executed_chain = err & TC_ACT_EXT_VAL_MASK;
			जाओ reset;
		पूर्ण
#पूर्ण_अगर
		अगर (err >= 0)
			वापस err;
	पूर्ण

	वापस TC_ACT_UNSPEC; /* संकेत: जारी lookup */
#अगर_घोषित CONFIG_NET_CLS_ACT
reset:
	अगर (unlikely(limit++ >= max_reclassअगरy_loop)) अणु
		net_notice_ratelimited("%u: reclassify loop, rule prio %u, protocol %02x\n",
				       tp->chain->block->index,
				       tp->prio & 0xffff,
				       ntohs(tp->protocol));
		वापस TC_ACT_SHOT;
	पूर्ण

	tp = first_tp;
	जाओ reclassअगरy;
#पूर्ण_अगर
पूर्ण

पूर्णांक tcf_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
		 काष्ठा tcf_result *res, bool compat_mode)
अणु
	u32 last_executed_chain = 0;

	वापस __tcf_classअगरy(skb, tp, tp, res, compat_mode,
			      &last_executed_chain);
पूर्ण
EXPORT_SYMBOL(tcf_classअगरy);

पूर्णांक tcf_classअगरy_ingress(काष्ठा sk_buff *skb,
			 स्थिर काष्ठा tcf_block *ingress_block,
			 स्थिर काष्ठा tcf_proto *tp,
			 काष्ठा tcf_result *res, bool compat_mode)
अणु
#अगर !IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	u32 last_executed_chain = 0;

	वापस __tcf_classअगरy(skb, tp, tp, res, compat_mode,
			      &last_executed_chain);
#अन्यथा
	u32 last_executed_chain = tp ? tp->chain->index : 0;
	स्थिर काष्ठा tcf_proto *orig_tp = tp;
	काष्ठा tc_skb_ext *ext;
	पूर्णांक ret;

	ext = skb_ext_find(skb, TC_SKB_EXT);

	अगर (ext && ext->chain) अणु
		काष्ठा tcf_chain *fchain;

		fchain = tcf_chain_lookup_rcu(ingress_block, ext->chain);
		अगर (!fchain)
			वापस TC_ACT_SHOT;

		/* Consume, so cloned/redirect skbs won't inherit ext */
		skb_ext_del(skb, TC_SKB_EXT);

		tp = rcu_dereference_bh(fchain->filter_chain);
		last_executed_chain = fchain->index;
	पूर्ण

	ret = __tcf_classअगरy(skb, tp, orig_tp, res, compat_mode,
			     &last_executed_chain);

	/* If we missed on some chain */
	अगर (ret == TC_ACT_UNSPEC && last_executed_chain) अणु
		ext = tc_skb_ext_alloc(skb);
		अगर (WARN_ON_ONCE(!ext))
			वापस TC_ACT_SHOT;
		ext->chain = last_executed_chain;
		ext->mru = qdisc_skb_cb(skb)->mru;
		ext->post_ct = qdisc_skb_cb(skb)->post_ct;
	पूर्ण

	वापस ret;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(tcf_classअगरy_ingress);

काष्ठा tcf_chain_info अणु
	काष्ठा tcf_proto __rcu **pprev;
	काष्ठा tcf_proto __rcu *next;
पूर्ण;

अटल काष्ठा tcf_proto *tcf_chain_tp_prev(काष्ठा tcf_chain *chain,
					   काष्ठा tcf_chain_info *chain_info)
अणु
	वापस tcf_chain_dereference(*chain_info->pprev, chain);
पूर्ण

अटल पूर्णांक tcf_chain_tp_insert(काष्ठा tcf_chain *chain,
			       काष्ठा tcf_chain_info *chain_info,
			       काष्ठा tcf_proto *tp)
अणु
	अगर (chain->flushing)
		वापस -EAGAIN;

	अगर (*chain_info->pprev == chain->filter_chain)
		tcf_chain0_head_change(chain, tp);
	tcf_proto_get(tp);
	RCU_INIT_POINTER(tp->next, tcf_chain_tp_prev(chain, chain_info));
	rcu_assign_poपूर्णांकer(*chain_info->pprev, tp);

	वापस 0;
पूर्ण

अटल व्योम tcf_chain_tp_हटाओ(काष्ठा tcf_chain *chain,
				काष्ठा tcf_chain_info *chain_info,
				काष्ठा tcf_proto *tp)
अणु
	काष्ठा tcf_proto *next = tcf_chain_dereference(chain_info->next, chain);

	tcf_proto_mark_delete(tp);
	अगर (tp == chain->filter_chain)
		tcf_chain0_head_change(chain, next);
	RCU_INIT_POINTER(*chain_info->pprev, next);
पूर्ण

अटल काष्ठा tcf_proto *tcf_chain_tp_find(काष्ठा tcf_chain *chain,
					   काष्ठा tcf_chain_info *chain_info,
					   u32 protocol, u32 prio,
					   bool prio_allocate);

/* Try to insert new proto.
 * If proto with specअगरied priority alपढ़ोy exists, मुक्त new proto
 * and वापस existing one.
 */

अटल काष्ठा tcf_proto *tcf_chain_tp_insert_unique(काष्ठा tcf_chain *chain,
						    काष्ठा tcf_proto *tp_new,
						    u32 protocol, u32 prio,
						    bool rtnl_held)
अणु
	काष्ठा tcf_chain_info chain_info;
	काष्ठा tcf_proto *tp;
	पूर्णांक err = 0;

	mutex_lock(&chain->filter_chain_lock);

	अगर (tcf_proto_exists_destroying(chain, tp_new)) अणु
		mutex_unlock(&chain->filter_chain_lock);
		tcf_proto_destroy(tp_new, rtnl_held, false, शून्य);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण

	tp = tcf_chain_tp_find(chain, &chain_info,
			       protocol, prio, false);
	अगर (!tp)
		err = tcf_chain_tp_insert(chain, &chain_info, tp_new);
	mutex_unlock(&chain->filter_chain_lock);

	अगर (tp) अणु
		tcf_proto_destroy(tp_new, rtnl_held, false, शून्य);
		tp_new = tp;
	पूर्ण अन्यथा अगर (err) अणु
		tcf_proto_destroy(tp_new, rtnl_held, false, शून्य);
		tp_new = ERR_PTR(err);
	पूर्ण

	वापस tp_new;
पूर्ण

अटल व्योम tcf_chain_tp_delete_empty(काष्ठा tcf_chain *chain,
				      काष्ठा tcf_proto *tp, bool rtnl_held,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_chain_info chain_info;
	काष्ठा tcf_proto *tp_iter;
	काष्ठा tcf_proto **pprev;
	काष्ठा tcf_proto *next;

	mutex_lock(&chain->filter_chain_lock);

	/* Atomically find and हटाओ tp from chain. */
	क्रम (pprev = &chain->filter_chain;
	     (tp_iter = tcf_chain_dereference(*pprev, chain));
	     pprev = &tp_iter->next) अणु
		अगर (tp_iter == tp) अणु
			chain_info.pprev = pprev;
			chain_info.next = tp_iter->next;
			WARN_ON(tp_iter->deleting);
			अवरोध;
		पूर्ण
	पूर्ण
	/* Verअगरy that tp still exists and no new filters were inserted
	 * concurrently.
	 * Mark tp क्रम deletion अगर it is empty.
	 */
	अगर (!tp_iter || !tcf_proto_check_delete(tp)) अणु
		mutex_unlock(&chain->filter_chain_lock);
		वापस;
	पूर्ण

	tcf_proto_संकेत_destroying(chain, tp);
	next = tcf_chain_dereference(chain_info.next, chain);
	अगर (tp == chain->filter_chain)
		tcf_chain0_head_change(chain, next);
	RCU_INIT_POINTER(*chain_info.pprev, next);
	mutex_unlock(&chain->filter_chain_lock);

	tcf_proto_put(tp, rtnl_held, extack);
पूर्ण

अटल काष्ठा tcf_proto *tcf_chain_tp_find(काष्ठा tcf_chain *chain,
					   काष्ठा tcf_chain_info *chain_info,
					   u32 protocol, u32 prio,
					   bool prio_allocate)
अणु
	काष्ठा tcf_proto **pprev;
	काष्ठा tcf_proto *tp;

	/* Check the chain क्रम existence of proto-tcf with this priority */
	क्रम (pprev = &chain->filter_chain;
	     (tp = tcf_chain_dereference(*pprev, chain));
	     pprev = &tp->next) अणु
		अगर (tp->prio >= prio) अणु
			अगर (tp->prio == prio) अणु
				अगर (prio_allocate ||
				    (tp->protocol != protocol && protocol))
					वापस ERR_PTR(-EINVAL);
			पूर्ण अन्यथा अणु
				tp = शून्य;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	chain_info->pprev = pprev;
	अगर (tp) अणु
		chain_info->next = tp->next;
		tcf_proto_get(tp);
	पूर्ण अन्यथा अणु
		chain_info->next = शून्य;
	पूर्ण
	वापस tp;
पूर्ण

अटल पूर्णांक tcf_fill_node(काष्ठा net *net, काष्ठा sk_buff *skb,
			 काष्ठा tcf_proto *tp, काष्ठा tcf_block *block,
			 काष्ठा Qdisc *q, u32 parent, व्योम *fh,
			 u32 portid, u32 seq, u16 flags, पूर्णांक event,
			 bool terse_dump, bool rtnl_held)
अणु
	काष्ठा tcmsg *tcm;
	काष्ठा nlmsghdr  *nlh;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);

	nlh = nlmsg_put(skb, portid, seq, event, माप(*tcm), flags);
	अगर (!nlh)
		जाओ out_nlmsg_trim;
	tcm = nlmsg_data(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	अगर (q) अणु
		tcm->tcm_अगरindex = qdisc_dev(q)->अगरindex;
		tcm->tcm_parent = parent;
	पूर्ण अन्यथा अणु
		tcm->tcm_अगरindex = TCM_IFINDEX_MAGIC_BLOCK;
		tcm->tcm_block_index = block->index;
	पूर्ण
	tcm->tcm_info = TC_H_MAKE(tp->prio, tp->protocol);
	अगर (nla_put_string(skb, TCA_KIND, tp->ops->kind))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, TCA_CHAIN, tp->chain->index))
		जाओ nla_put_failure;
	अगर (!fh) अणु
		tcm->tcm_handle = 0;
	पूर्ण अन्यथा अगर (terse_dump) अणु
		अगर (tp->ops->terse_dump) अणु
			अगर (tp->ops->terse_dump(net, tp, fh, skb, tcm,
						rtnl_held) < 0)
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			जाओ cls_op_not_supp;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tp->ops->dump &&
		    tp->ops->dump(net, tp, fh, skb, tcm, rtnl_held) < 0)
			जाओ nla_put_failure;
	पूर्ण
	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	वापस skb->len;

out_nlmsg_trim:
nla_put_failure:
cls_op_not_supp:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tfilter_notअगरy(काष्ठा net *net, काष्ठा sk_buff *oskb,
			  काष्ठा nlmsghdr *n, काष्ठा tcf_proto *tp,
			  काष्ठा tcf_block *block, काष्ठा Qdisc *q,
			  u32 parent, व्योम *fh, पूर्णांक event, bool unicast,
			  bool rtnl_held)
अणु
	काष्ठा sk_buff *skb;
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	पूर्णांक err = 0;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tcf_fill_node(net, skb, tp, block, q, parent, fh, portid,
			  n->nlmsg_seq, n->nlmsg_flags, event,
			  false, rtnl_held) <= 0) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (unicast)
		err = netlink_unicast(net->rtnl, skb, portid, MSG_DONTWAIT);
	अन्यथा
		err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				     n->nlmsg_flags & NLM_F_ECHO);

	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक tfilter_del_notअगरy(काष्ठा net *net, काष्ठा sk_buff *oskb,
			      काष्ठा nlmsghdr *n, काष्ठा tcf_proto *tp,
			      काष्ठा tcf_block *block, काष्ठा Qdisc *q,
			      u32 parent, व्योम *fh, bool unicast, bool *last,
			      bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sk_buff *skb;
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	पूर्णांक err;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tcf_fill_node(net, skb, tp, block, q, parent, fh, portid,
			  n->nlmsg_seq, n->nlmsg_flags, RTM_DELTFILTER,
			  false, rtnl_held) <= 0) अणु
		NL_SET_ERR_MSG(extack, "Failed to build del event notification");
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	err = tp->ops->delete(tp, fh, last, rtnl_held, extack);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	अगर (unicast)
		err = netlink_unicast(net->rtnl, skb, portid, MSG_DONTWAIT);
	अन्यथा
		err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				     n->nlmsg_flags & NLM_F_ECHO);
	अगर (err < 0)
		NL_SET_ERR_MSG(extack, "Failed to send filter delete notification");

	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

अटल व्योम tfilter_notअगरy_chain(काष्ठा net *net, काष्ठा sk_buff *oskb,
				 काष्ठा tcf_block *block, काष्ठा Qdisc *q,
				 u32 parent, काष्ठा nlmsghdr *n,
				 काष्ठा tcf_chain *chain, पूर्णांक event)
अणु
	काष्ठा tcf_proto *tp;

	क्रम (tp = tcf_get_next_proto(chain, शून्य);
	     tp; tp = tcf_get_next_proto(chain, tp))
		tfilter_notअगरy(net, oskb, n, tp, block,
			       q, parent, शून्य, event, false, true);
पूर्ण

अटल व्योम tfilter_put(काष्ठा tcf_proto *tp, व्योम *fh)
अणु
	अगर (tp->ops->put && fh)
		tp->ops->put(tp, fh);
पूर्ण

अटल पूर्णांक tc_new_tfilter(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	अक्षर name[IFNAMSIZ];
	काष्ठा tcmsg *t;
	u32 protocol;
	u32 prio;
	bool prio_allocate;
	u32 parent;
	u32 chain_index;
	काष्ठा Qdisc *q = शून्य;
	काष्ठा tcf_chain_info chain_info;
	काष्ठा tcf_chain *chain = शून्य;
	काष्ठा tcf_block *block;
	काष्ठा tcf_proto *tp;
	अचिन्हित दीर्घ cl;
	व्योम *fh;
	पूर्णांक err;
	पूर्णांक tp_created;
	bool rtnl_held = false;

	अगर (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

replay:
	tp_created = 0;

	err = nlmsg_parse_deprecated(n, माप(*t), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	t = nlmsg_data(n);
	protocol = TC_H_MIN(t->tcm_info);
	prio = TC_H_MAJ(t->tcm_info);
	prio_allocate = false;
	parent = t->tcm_parent;
	tp = शून्य;
	cl = 0;
	block = शून्य;

	अगर (prio == 0) अणु
		/* If no priority is provided by the user,
		 * we allocate one.
		 */
		अगर (n->nlmsg_flags & NLM_F_CREATE) अणु
			prio = TC_H_MAKE(0x80000000U, 0U);
			prio_allocate = true;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG(extack, "Invalid filter command with priority of zero");
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	/* Find head of filter chain. */

	err = __tcf_qdisc_find(net, &q, &parent, t->tcm_अगरindex, false, extack);
	अगर (err)
		वापस err;

	अगर (tcf_proto_check_kind(tca[TCA_KIND], name)) अणु
		NL_SET_ERR_MSG(extack, "Specified TC filter name too long");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	/* Take rtnl mutex अगर rtnl_held was set to true on previous iteration,
	 * block is shared (no qdisc found), qdisc is not unlocked, classअगरier
	 * type is not specअगरied, classअगरier is not unlocked.
	 */
	अगर (rtnl_held ||
	    (q && !(q->ops->cl_ops->flags & QDISC_CLASS_OPS_DOIT_UNLOCKED)) ||
	    !tcf_proto_is_unlocked(name)) अणु
		rtnl_held = true;
		rtnl_lock();
	पूर्ण

	err = __tcf_qdisc_cl_find(q, parent, &cl, t->tcm_अगरindex, extack);
	अगर (err)
		जाओ errout;

	block = __tcf_block_find(net, q, cl, t->tcm_अगरindex, t->tcm_block_index,
				 extack);
	अगर (IS_ERR(block)) अणु
		err = PTR_ERR(block);
		जाओ errout;
	पूर्ण
	block->classid = parent;

	chain_index = tca[TCA_CHAIN] ? nla_get_u32(tca[TCA_CHAIN]) : 0;
	अगर (chain_index > TC_ACT_EXT_VAL_MASK) अणु
		NL_SET_ERR_MSG(extack, "Specified chain index exceeds upper limit");
		err = -EINVAL;
		जाओ errout;
	पूर्ण
	chain = tcf_chain_get(block, chain_index, true);
	अगर (!chain) अणु
		NL_SET_ERR_MSG(extack, "Cannot create specified filter chain");
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	mutex_lock(&chain->filter_chain_lock);
	tp = tcf_chain_tp_find(chain, &chain_info, protocol,
			       prio, prio_allocate);
	अगर (IS_ERR(tp)) अणु
		NL_SET_ERR_MSG(extack, "Filter with specified priority/protocol not found");
		err = PTR_ERR(tp);
		जाओ errout_locked;
	पूर्ण

	अगर (tp == शून्य) अणु
		काष्ठा tcf_proto *tp_new = शून्य;

		अगर (chain->flushing) अणु
			err = -EAGAIN;
			जाओ errout_locked;
		पूर्ण

		/* Proto-tcf करोes not exist, create new one */

		अगर (tca[TCA_KIND] == शून्य || !protocol) अणु
			NL_SET_ERR_MSG(extack, "Filter kind and protocol must be specified");
			err = -EINVAL;
			जाओ errout_locked;
		पूर्ण

		अगर (!(n->nlmsg_flags & NLM_F_CREATE)) अणु
			NL_SET_ERR_MSG(extack, "Need both RTM_NEWTFILTER and NLM_F_CREATE to create a new filter");
			err = -ENOENT;
			जाओ errout_locked;
		पूर्ण

		अगर (prio_allocate)
			prio = tcf_स्वतः_prio(tcf_chain_tp_prev(chain,
							       &chain_info));

		mutex_unlock(&chain->filter_chain_lock);
		tp_new = tcf_proto_create(name, protocol, prio, chain,
					  rtnl_held, extack);
		अगर (IS_ERR(tp_new)) अणु
			err = PTR_ERR(tp_new);
			जाओ errout_tp;
		पूर्ण

		tp_created = 1;
		tp = tcf_chain_tp_insert_unique(chain, tp_new, protocol, prio,
						rtnl_held);
		अगर (IS_ERR(tp)) अणु
			err = PTR_ERR(tp);
			जाओ errout_tp;
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&chain->filter_chain_lock);
	पूर्ण

	अगर (tca[TCA_KIND] && nla_म_भेद(tca[TCA_KIND], tp->ops->kind)) अणु
		NL_SET_ERR_MSG(extack, "Specified filter kind does not match existing one");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	fh = tp->ops->get(tp, t->tcm_handle);

	अगर (!fh) अणु
		अगर (!(n->nlmsg_flags & NLM_F_CREATE)) अणु
			NL_SET_ERR_MSG(extack, "Need both RTM_NEWTFILTER and NLM_F_CREATE to create a new filter");
			err = -ENOENT;
			जाओ errout;
		पूर्ण
	पूर्ण अन्यथा अगर (n->nlmsg_flags & NLM_F_EXCL) अणु
		tfilter_put(tp, fh);
		NL_SET_ERR_MSG(extack, "Filter already exists");
		err = -EEXIST;
		जाओ errout;
	पूर्ण

	अगर (chain->पंचांगplt_ops && chain->पंचांगplt_ops != tp->ops) अणु
		NL_SET_ERR_MSG(extack, "Chain template is set to a different filter kind");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	err = tp->ops->change(net, skb, tp, cl, t->tcm_handle, tca, &fh,
			      n->nlmsg_flags & NLM_F_CREATE ? TCA_ACT_NOREPLACE : TCA_ACT_REPLACE,
			      rtnl_held, extack);
	अगर (err == 0) अणु
		tfilter_notअगरy(net, skb, n, tp, block, q, parent, fh,
			       RTM_NEWTFILTER, false, rtnl_held);
		tfilter_put(tp, fh);
		/* q poपूर्णांकer is शून्य क्रम shared blocks */
		अगर (q)
			q->flags &= ~TCQ_F_CAN_BYPASS;
	पूर्ण

errout:
	अगर (err && tp_created)
		tcf_chain_tp_delete_empty(chain, tp, rtnl_held, शून्य);
errout_tp:
	अगर (chain) अणु
		अगर (tp && !IS_ERR(tp))
			tcf_proto_put(tp, rtnl_held, शून्य);
		अगर (!tp_created)
			tcf_chain_put(chain);
	पूर्ण
	tcf_block_release(q, block, rtnl_held);

	अगर (rtnl_held)
		rtnl_unlock();

	अगर (err == -EAGAIN) अणु
		/* Take rtnl lock in हाल EAGAIN is caused by concurrent flush
		 * of target chain.
		 */
		rtnl_held = true;
		/* Replay the request. */
		जाओ replay;
	पूर्ण
	वापस err;

errout_locked:
	mutex_unlock(&chain->filter_chain_lock);
	जाओ errout;
पूर्ण

अटल पूर्णांक tc_del_tfilter(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	अक्षर name[IFNAMSIZ];
	काष्ठा tcmsg *t;
	u32 protocol;
	u32 prio;
	u32 parent;
	u32 chain_index;
	काष्ठा Qdisc *q = शून्य;
	काष्ठा tcf_chain_info chain_info;
	काष्ठा tcf_chain *chain = शून्य;
	काष्ठा tcf_block *block = शून्य;
	काष्ठा tcf_proto *tp = शून्य;
	अचिन्हित दीर्घ cl = 0;
	व्योम *fh = शून्य;
	पूर्णांक err;
	bool rtnl_held = false;

	अगर (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	err = nlmsg_parse_deprecated(n, माप(*t), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	t = nlmsg_data(n);
	protocol = TC_H_MIN(t->tcm_info);
	prio = TC_H_MAJ(t->tcm_info);
	parent = t->tcm_parent;

	अगर (prio == 0 && (protocol || t->tcm_handle || tca[TCA_KIND])) अणु
		NL_SET_ERR_MSG(extack, "Cannot flush filters with protocol, handle or kind set");
		वापस -ENOENT;
	पूर्ण

	/* Find head of filter chain. */

	err = __tcf_qdisc_find(net, &q, &parent, t->tcm_अगरindex, false, extack);
	अगर (err)
		वापस err;

	अगर (tcf_proto_check_kind(tca[TCA_KIND], name)) अणु
		NL_SET_ERR_MSG(extack, "Specified TC filter name too long");
		err = -EINVAL;
		जाओ errout;
	पूर्ण
	/* Take rtnl mutex अगर flushing whole chain, block is shared (no qdisc
	 * found), qdisc is not unlocked, classअगरier type is not specअगरied,
	 * classअगरier is not unlocked.
	 */
	अगर (!prio ||
	    (q && !(q->ops->cl_ops->flags & QDISC_CLASS_OPS_DOIT_UNLOCKED)) ||
	    !tcf_proto_is_unlocked(name)) अणु
		rtnl_held = true;
		rtnl_lock();
	पूर्ण

	err = __tcf_qdisc_cl_find(q, parent, &cl, t->tcm_अगरindex, extack);
	अगर (err)
		जाओ errout;

	block = __tcf_block_find(net, q, cl, t->tcm_अगरindex, t->tcm_block_index,
				 extack);
	अगर (IS_ERR(block)) अणु
		err = PTR_ERR(block);
		जाओ errout;
	पूर्ण

	chain_index = tca[TCA_CHAIN] ? nla_get_u32(tca[TCA_CHAIN]) : 0;
	अगर (chain_index > TC_ACT_EXT_VAL_MASK) अणु
		NL_SET_ERR_MSG(extack, "Specified chain index exceeds upper limit");
		err = -EINVAL;
		जाओ errout;
	पूर्ण
	chain = tcf_chain_get(block, chain_index, false);
	अगर (!chain) अणु
		/* User requested flush on non-existent chain. Nothing to करो,
		 * so just वापस success.
		 */
		अगर (prio == 0) अणु
			err = 0;
			जाओ errout;
		पूर्ण
		NL_SET_ERR_MSG(extack, "Cannot find specified filter chain");
		err = -ENOENT;
		जाओ errout;
	पूर्ण

	अगर (prio == 0) अणु
		tfilter_notअगरy_chain(net, skb, block, q, parent, n,
				     chain, RTM_DELTFILTER);
		tcf_chain_flush(chain, rtnl_held);
		err = 0;
		जाओ errout;
	पूर्ण

	mutex_lock(&chain->filter_chain_lock);
	tp = tcf_chain_tp_find(chain, &chain_info, protocol,
			       prio, false);
	अगर (!tp || IS_ERR(tp)) अणु
		NL_SET_ERR_MSG(extack, "Filter with specified priority/protocol not found");
		err = tp ? PTR_ERR(tp) : -ENOENT;
		जाओ errout_locked;
	पूर्ण अन्यथा अगर (tca[TCA_KIND] && nla_म_भेद(tca[TCA_KIND], tp->ops->kind)) अणु
		NL_SET_ERR_MSG(extack, "Specified filter kind does not match existing one");
		err = -EINVAL;
		जाओ errout_locked;
	पूर्ण अन्यथा अगर (t->tcm_handle == 0) अणु
		tcf_proto_संकेत_destroying(chain, tp);
		tcf_chain_tp_हटाओ(chain, &chain_info, tp);
		mutex_unlock(&chain->filter_chain_lock);

		tcf_proto_put(tp, rtnl_held, शून्य);
		tfilter_notअगरy(net, skb, n, tp, block, q, parent, fh,
			       RTM_DELTFILTER, false, rtnl_held);
		err = 0;
		जाओ errout;
	पूर्ण
	mutex_unlock(&chain->filter_chain_lock);

	fh = tp->ops->get(tp, t->tcm_handle);

	अगर (!fh) अणु
		NL_SET_ERR_MSG(extack, "Specified filter handle not found");
		err = -ENOENT;
	पूर्ण अन्यथा अणु
		bool last;

		err = tfilter_del_notअगरy(net, skb, n, tp, block,
					 q, parent, fh, false, &last,
					 rtnl_held, extack);

		अगर (err)
			जाओ errout;
		अगर (last)
			tcf_chain_tp_delete_empty(chain, tp, rtnl_held, extack);
	पूर्ण

errout:
	अगर (chain) अणु
		अगर (tp && !IS_ERR(tp))
			tcf_proto_put(tp, rtnl_held, शून्य);
		tcf_chain_put(chain);
	पूर्ण
	tcf_block_release(q, block, rtnl_held);

	अगर (rtnl_held)
		rtnl_unlock();

	वापस err;

errout_locked:
	mutex_unlock(&chain->filter_chain_lock);
	जाओ errout;
पूर्ण

अटल पूर्णांक tc_get_tfilter(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	अक्षर name[IFNAMSIZ];
	काष्ठा tcmsg *t;
	u32 protocol;
	u32 prio;
	u32 parent;
	u32 chain_index;
	काष्ठा Qdisc *q = शून्य;
	काष्ठा tcf_chain_info chain_info;
	काष्ठा tcf_chain *chain = शून्य;
	काष्ठा tcf_block *block = शून्य;
	काष्ठा tcf_proto *tp = शून्य;
	अचिन्हित दीर्घ cl = 0;
	व्योम *fh = शून्य;
	पूर्णांक err;
	bool rtnl_held = false;

	err = nlmsg_parse_deprecated(n, माप(*t), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	t = nlmsg_data(n);
	protocol = TC_H_MIN(t->tcm_info);
	prio = TC_H_MAJ(t->tcm_info);
	parent = t->tcm_parent;

	अगर (prio == 0) अणु
		NL_SET_ERR_MSG(extack, "Invalid filter command with priority of zero");
		वापस -ENOENT;
	पूर्ण

	/* Find head of filter chain. */

	err = __tcf_qdisc_find(net, &q, &parent, t->tcm_अगरindex, false, extack);
	अगर (err)
		वापस err;

	अगर (tcf_proto_check_kind(tca[TCA_KIND], name)) अणु
		NL_SET_ERR_MSG(extack, "Specified TC filter name too long");
		err = -EINVAL;
		जाओ errout;
	पूर्ण
	/* Take rtnl mutex अगर block is shared (no qdisc found), qdisc is not
	 * unlocked, classअगरier type is not specअगरied, classअगरier is not
	 * unlocked.
	 */
	अगर ((q && !(q->ops->cl_ops->flags & QDISC_CLASS_OPS_DOIT_UNLOCKED)) ||
	    !tcf_proto_is_unlocked(name)) अणु
		rtnl_held = true;
		rtnl_lock();
	पूर्ण

	err = __tcf_qdisc_cl_find(q, parent, &cl, t->tcm_अगरindex, extack);
	अगर (err)
		जाओ errout;

	block = __tcf_block_find(net, q, cl, t->tcm_अगरindex, t->tcm_block_index,
				 extack);
	अगर (IS_ERR(block)) अणु
		err = PTR_ERR(block);
		जाओ errout;
	पूर्ण

	chain_index = tca[TCA_CHAIN] ? nla_get_u32(tca[TCA_CHAIN]) : 0;
	अगर (chain_index > TC_ACT_EXT_VAL_MASK) अणु
		NL_SET_ERR_MSG(extack, "Specified chain index exceeds upper limit");
		err = -EINVAL;
		जाओ errout;
	पूर्ण
	chain = tcf_chain_get(block, chain_index, false);
	अगर (!chain) अणु
		NL_SET_ERR_MSG(extack, "Cannot find specified filter chain");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	mutex_lock(&chain->filter_chain_lock);
	tp = tcf_chain_tp_find(chain, &chain_info, protocol,
			       prio, false);
	mutex_unlock(&chain->filter_chain_lock);
	अगर (!tp || IS_ERR(tp)) अणु
		NL_SET_ERR_MSG(extack, "Filter with specified priority/protocol not found");
		err = tp ? PTR_ERR(tp) : -ENOENT;
		जाओ errout;
	पूर्ण अन्यथा अगर (tca[TCA_KIND] && nla_म_भेद(tca[TCA_KIND], tp->ops->kind)) अणु
		NL_SET_ERR_MSG(extack, "Specified filter kind does not match existing one");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	fh = tp->ops->get(tp, t->tcm_handle);

	अगर (!fh) अणु
		NL_SET_ERR_MSG(extack, "Specified filter handle not found");
		err = -ENOENT;
	पूर्ण अन्यथा अणु
		err = tfilter_notअगरy(net, skb, n, tp, block, q, parent,
				     fh, RTM_NEWTFILTER, true, rtnl_held);
		अगर (err < 0)
			NL_SET_ERR_MSG(extack, "Failed to send filter notify message");
	पूर्ण

	tfilter_put(tp, fh);
errout:
	अगर (chain) अणु
		अगर (tp && !IS_ERR(tp))
			tcf_proto_put(tp, rtnl_held, शून्य);
		tcf_chain_put(chain);
	पूर्ण
	tcf_block_release(q, block, rtnl_held);

	अगर (rtnl_held)
		rtnl_unlock();

	वापस err;
पूर्ण

काष्ठा tcf_dump_args अणु
	काष्ठा tcf_walker w;
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	काष्ठा tcf_block *block;
	काष्ठा Qdisc *q;
	u32 parent;
	bool terse_dump;
पूर्ण;

अटल पूर्णांक tcf_node_dump(काष्ठा tcf_proto *tp, व्योम *n, काष्ठा tcf_walker *arg)
अणु
	काष्ठा tcf_dump_args *a = (व्योम *)arg;
	काष्ठा net *net = sock_net(a->skb->sk);

	वापस tcf_fill_node(net, a->skb, tp, a->block, a->q, a->parent,
			     n, NETLINK_CB(a->cb->skb).portid,
			     a->cb->nlh->nlmsg_seq, NLM_F_MULTI,
			     RTM_NEWTFILTER, a->terse_dump, true);
पूर्ण

अटल bool tcf_chain_dump(काष्ठा tcf_chain *chain, काष्ठा Qdisc *q, u32 parent,
			   काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			   दीर्घ index_start, दीर्घ *p_index, bool terse)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tcf_block *block = chain->block;
	काष्ठा tcmsg *tcm = nlmsg_data(cb->nlh);
	काष्ठा tcf_proto *tp, *tp_prev;
	काष्ठा tcf_dump_args arg;

	क्रम (tp = __tcf_get_next_proto(chain, शून्य);
	     tp;
	     tp_prev = tp,
		     tp = __tcf_get_next_proto(chain, tp),
		     tcf_proto_put(tp_prev, true, शून्य),
		     (*p_index)++) अणु
		अगर (*p_index < index_start)
			जारी;
		अगर (TC_H_MAJ(tcm->tcm_info) &&
		    TC_H_MAJ(tcm->tcm_info) != tp->prio)
			जारी;
		अगर (TC_H_MIN(tcm->tcm_info) &&
		    TC_H_MIN(tcm->tcm_info) != tp->protocol)
			जारी;
		अगर (*p_index > index_start)
			स_रखो(&cb->args[1], 0,
			       माप(cb->args) - माप(cb->args[0]));
		अगर (cb->args[1] == 0) अणु
			अगर (tcf_fill_node(net, skb, tp, block, q, parent, शून्य,
					  NETLINK_CB(cb->skb).portid,
					  cb->nlh->nlmsg_seq, NLM_F_MULTI,
					  RTM_NEWTFILTER, false, true) <= 0)
				जाओ errout;
			cb->args[1] = 1;
		पूर्ण
		अगर (!tp->ops->walk)
			जारी;
		arg.w.fn = tcf_node_dump;
		arg.skb = skb;
		arg.cb = cb;
		arg.block = block;
		arg.q = q;
		arg.parent = parent;
		arg.w.stop = 0;
		arg.w.skip = cb->args[1] - 1;
		arg.w.count = 0;
		arg.w.cookie = cb->args[2];
		arg.terse_dump = terse;
		tp->ops->walk(tp, &arg.w, true);
		cb->args[2] = arg.w.cookie;
		cb->args[1] = arg.w.count + 1;
		अगर (arg.w.stop)
			जाओ errout;
	पूर्ण
	वापस true;

errout:
	tcf_proto_put(tp, true, शून्य);
	वापस false;
पूर्ण

अटल स्थिर काष्ठा nla_policy tcf_tfilter_dump_policy[TCA_MAX + 1] = अणु
	[TCA_DUMP_FLAGS] = NLA_POLICY_BITFIELD32(TCA_DUMP_FLAGS_TERSE),
पूर्ण;

/* called with RTNL */
अटल पूर्णांक tc_dump_tfilter(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा tcf_chain *chain, *chain_prev;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	काष्ठा Qdisc *q = शून्य;
	काष्ठा tcf_block *block;
	काष्ठा tcmsg *tcm = nlmsg_data(cb->nlh);
	bool terse_dump = false;
	दीर्घ index_start;
	दीर्घ index;
	u32 parent;
	पूर्णांक err;

	अगर (nlmsg_len(cb->nlh) < माप(*tcm))
		वापस skb->len;

	err = nlmsg_parse_deprecated(cb->nlh, माप(*tcm), tca, TCA_MAX,
				     tcf_tfilter_dump_policy, cb->extack);
	अगर (err)
		वापस err;

	अगर (tca[TCA_DUMP_FLAGS]) अणु
		काष्ठा nla_bitfield32 flags =
			nla_get_bitfield32(tca[TCA_DUMP_FLAGS]);

		terse_dump = flags.value & TCA_DUMP_FLAGS_TERSE;
	पूर्ण

	अगर (tcm->tcm_अगरindex == TCM_IFINDEX_MAGIC_BLOCK) अणु
		block = tcf_block_refcnt_get(net, tcm->tcm_block_index);
		अगर (!block)
			जाओ out;
		/* If we work with block index, q is शून्य and parent value
		 * will never be used in the following code. The check
		 * in tcf_fill_node prevents it. However, compiler करोes not
		 * see that far, so set parent to zero to silence the warning
		 * about parent being uninitialized.
		 */
		parent = 0;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा Qdisc_class_ops *cops;
		काष्ठा net_device *dev;
		अचिन्हित दीर्घ cl = 0;

		dev = __dev_get_by_index(net, tcm->tcm_अगरindex);
		अगर (!dev)
			वापस skb->len;

		parent = tcm->tcm_parent;
		अगर (!parent)
			q = dev->qdisc;
		अन्यथा
			q = qdisc_lookup(dev, TC_H_MAJ(tcm->tcm_parent));
		अगर (!q)
			जाओ out;
		cops = q->ops->cl_ops;
		अगर (!cops)
			जाओ out;
		अगर (!cops->tcf_block)
			जाओ out;
		अगर (TC_H_MIN(tcm->tcm_parent)) अणु
			cl = cops->find(q, tcm->tcm_parent);
			अगर (cl == 0)
				जाओ out;
		पूर्ण
		block = cops->tcf_block(q, cl, शून्य);
		अगर (!block)
			जाओ out;
		parent = block->classid;
		अगर (tcf_block_shared(block))
			q = शून्य;
	पूर्ण

	index_start = cb->args[0];
	index = 0;

	क्रम (chain = __tcf_get_next_chain(block, शून्य);
	     chain;
	     chain_prev = chain,
		     chain = __tcf_get_next_chain(block, chain),
		     tcf_chain_put(chain_prev)) अणु
		अगर (tca[TCA_CHAIN] &&
		    nla_get_u32(tca[TCA_CHAIN]) != chain->index)
			जारी;
		अगर (!tcf_chain_dump(chain, q, parent, skb, cb,
				    index_start, &index, terse_dump)) अणु
			tcf_chain_put(chain);
			err = -EMSGSIZE;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (tcm->tcm_अगरindex == TCM_IFINDEX_MAGIC_BLOCK)
		tcf_block_refcnt_put(block, true);
	cb->args[0] = index;

out:
	/* If we did no progress, the error (EMSGSIZE) is real */
	अगर (skb->len == 0 && err)
		वापस err;
	वापस skb->len;
पूर्ण

अटल पूर्णांक tc_chain_fill_node(स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops,
			      व्योम *पंचांगplt_priv, u32 chain_index,
			      काष्ठा net *net, काष्ठा sk_buff *skb,
			      काष्ठा tcf_block *block,
			      u32 portid, u32 seq, u16 flags, पूर्णांक event)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	स्थिर काष्ठा tcf_proto_ops *ops;
	काष्ठा nlmsghdr *nlh;
	काष्ठा tcmsg *tcm;
	व्योम *priv;

	ops = पंचांगplt_ops;
	priv = पंचांगplt_priv;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*tcm), flags);
	अगर (!nlh)
		जाओ out_nlmsg_trim;
	tcm = nlmsg_data(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_handle = 0;
	अगर (block->q) अणु
		tcm->tcm_अगरindex = qdisc_dev(block->q)->अगरindex;
		tcm->tcm_parent = block->q->handle;
	पूर्ण अन्यथा अणु
		tcm->tcm_अगरindex = TCM_IFINDEX_MAGIC_BLOCK;
		tcm->tcm_block_index = block->index;
	पूर्ण

	अगर (nla_put_u32(skb, TCA_CHAIN, chain_index))
		जाओ nla_put_failure;

	अगर (ops) अणु
		अगर (nla_put_string(skb, TCA_KIND, ops->kind))
			जाओ nla_put_failure;
		अगर (ops->पंचांगplt_dump(skb, net, priv) < 0)
			जाओ nla_put_failure;
	पूर्ण

	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	वापस skb->len;

out_nlmsg_trim:
nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक tc_chain_notअगरy(काष्ठा tcf_chain *chain, काष्ठा sk_buff *oskb,
			   u32 seq, u16 flags, पूर्णांक event, bool unicast)
अणु
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	काष्ठा tcf_block *block = chain->block;
	काष्ठा net *net = block->net;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tc_chain_fill_node(chain->पंचांगplt_ops, chain->पंचांगplt_priv,
			       chain->index, net, skb, block, portid,
			       seq, flags, event) <= 0) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (unicast)
		err = netlink_unicast(net->rtnl, skb, portid, MSG_DONTWAIT);
	अन्यथा
		err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				     flags & NLM_F_ECHO);

	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक tc_chain_notअगरy_delete(स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops,
				  व्योम *पंचांगplt_priv, u32 chain_index,
				  काष्ठा tcf_block *block, काष्ठा sk_buff *oskb,
				  u32 seq, u16 flags, bool unicast)
अणु
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	काष्ठा net *net = block->net;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tc_chain_fill_node(पंचांगplt_ops, पंचांगplt_priv, chain_index, net, skb,
			       block, portid, seq, flags, RTM_DELCHAIN) <= 0) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (unicast)
		वापस netlink_unicast(net->rtnl, skb, portid, MSG_DONTWAIT);

	वापस rtnetlink_send(skb, net, portid, RTNLGRP_TC, flags & NLM_F_ECHO);
पूर्ण

अटल पूर्णांक tc_chain_पंचांगplt_add(काष्ठा tcf_chain *chain, काष्ठा net *net,
			      काष्ठा nlattr **tca,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा tcf_proto_ops *ops;
	अक्षर name[IFNAMSIZ];
	व्योम *पंचांगplt_priv;

	/* If kind is not set, user did not specअगरy ढाँचा. */
	अगर (!tca[TCA_KIND])
		वापस 0;

	अगर (tcf_proto_check_kind(tca[TCA_KIND], name)) अणु
		NL_SET_ERR_MSG(extack, "Specified TC chain template name too long");
		वापस -EINVAL;
	पूर्ण

	ops = tcf_proto_lookup_ops(name, true, extack);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);
	अगर (!ops->पंचांगplt_create || !ops->पंचांगplt_destroy || !ops->पंचांगplt_dump) अणु
		NL_SET_ERR_MSG(extack, "Chain templates are not supported with specified classifier");
		वापस -EOPNOTSUPP;
	पूर्ण

	पंचांगplt_priv = ops->पंचांगplt_create(net, chain, tca, extack);
	अगर (IS_ERR(पंचांगplt_priv)) अणु
		module_put(ops->owner);
		वापस PTR_ERR(पंचांगplt_priv);
	पूर्ण
	chain->पंचांगplt_ops = ops;
	chain->पंचांगplt_priv = पंचांगplt_priv;
	वापस 0;
पूर्ण

अटल व्योम tc_chain_पंचांगplt_del(स्थिर काष्ठा tcf_proto_ops *पंचांगplt_ops,
			       व्योम *पंचांगplt_priv)
अणु
	/* If ढाँचा ops are set, no work to करो क्रम us. */
	अगर (!पंचांगplt_ops)
		वापस;

	पंचांगplt_ops->पंचांगplt_destroy(पंचांगplt_priv);
	module_put(पंचांगplt_ops->owner);
पूर्ण

/* Add/delete/get a chain */

अटल पूर्णांक tc_ctl_chain(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	काष्ठा tcmsg *t;
	u32 parent;
	u32 chain_index;
	काष्ठा Qdisc *q = शून्य;
	काष्ठा tcf_chain *chain = शून्य;
	काष्ठा tcf_block *block;
	अचिन्हित दीर्घ cl;
	पूर्णांक err;

	अगर (n->nlmsg_type != RTM_GETCHAIN &&
	    !netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

replay:
	err = nlmsg_parse_deprecated(n, माप(*t), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	t = nlmsg_data(n);
	parent = t->tcm_parent;
	cl = 0;

	block = tcf_block_find(net, &q, &parent, &cl,
			       t->tcm_अगरindex, t->tcm_block_index, extack);
	अगर (IS_ERR(block))
		वापस PTR_ERR(block);

	chain_index = tca[TCA_CHAIN] ? nla_get_u32(tca[TCA_CHAIN]) : 0;
	अगर (chain_index > TC_ACT_EXT_VAL_MASK) अणु
		NL_SET_ERR_MSG(extack, "Specified chain index exceeds upper limit");
		err = -EINVAL;
		जाओ errout_block;
	पूर्ण

	mutex_lock(&block->lock);
	chain = tcf_chain_lookup(block, chain_index);
	अगर (n->nlmsg_type == RTM_NEWCHAIN) अणु
		अगर (chain) अणु
			अगर (tcf_chain_held_by_acts_only(chain)) अणु
				/* The chain exists only because there is
				 * some action referencing it.
				 */
				tcf_chain_hold(chain);
			पूर्ण अन्यथा अणु
				NL_SET_ERR_MSG(extack, "Filter chain already exists");
				err = -EEXIST;
				जाओ errout_block_locked;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(n->nlmsg_flags & NLM_F_CREATE)) अणु
				NL_SET_ERR_MSG(extack, "Need both RTM_NEWCHAIN and NLM_F_CREATE to create a new chain");
				err = -ENOENT;
				जाओ errout_block_locked;
			पूर्ण
			chain = tcf_chain_create(block, chain_index);
			अगर (!chain) अणु
				NL_SET_ERR_MSG(extack, "Failed to create filter chain");
				err = -ENOMEM;
				जाओ errout_block_locked;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!chain || tcf_chain_held_by_acts_only(chain)) अणु
			NL_SET_ERR_MSG(extack, "Cannot find specified filter chain");
			err = -EINVAL;
			जाओ errout_block_locked;
		पूर्ण
		tcf_chain_hold(chain);
	पूर्ण

	अगर (n->nlmsg_type == RTM_NEWCHAIN) अणु
		/* Modअगरying chain requires holding parent block lock. In हाल
		 * the chain was successfully added, take a reference to the
		 * chain. This ensures that an empty chain करोes not disappear at
		 * the end of this function.
		 */
		tcf_chain_hold(chain);
		chain->explicitly_created = true;
	पूर्ण
	mutex_unlock(&block->lock);

	चयन (n->nlmsg_type) अणु
	हाल RTM_NEWCHAIN:
		err = tc_chain_पंचांगplt_add(chain, net, tca, extack);
		अगर (err) अणु
			tcf_chain_put_explicitly_created(chain);
			जाओ errout;
		पूर्ण

		tc_chain_notअगरy(chain, शून्य, 0, NLM_F_CREATE | NLM_F_EXCL,
				RTM_NEWCHAIN, false);
		अवरोध;
	हाल RTM_DELCHAIN:
		tfilter_notअगरy_chain(net, skb, block, q, parent, n,
				     chain, RTM_DELTFILTER);
		/* Flush the chain first as the user requested chain removal. */
		tcf_chain_flush(chain, true);
		/* In हाल the chain was successfully deleted, put a reference
		 * to the chain previously taken during addition.
		 */
		tcf_chain_put_explicitly_created(chain);
		अवरोध;
	हाल RTM_GETCHAIN:
		err = tc_chain_notअगरy(chain, skb, n->nlmsg_seq,
				      n->nlmsg_seq, n->nlmsg_type, true);
		अगर (err < 0)
			NL_SET_ERR_MSG(extack, "Failed to send chain notify message");
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		NL_SET_ERR_MSG(extack, "Unsupported message type");
		जाओ errout;
	पूर्ण

errout:
	tcf_chain_put(chain);
errout_block:
	tcf_block_release(q, block, true);
	अगर (err == -EAGAIN)
		/* Replay the request. */
		जाओ replay;
	वापस err;

errout_block_locked:
	mutex_unlock(&block->lock);
	जाओ errout_block;
पूर्ण

/* called with RTNL */
अटल पूर्णांक tc_dump_chain(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	काष्ठा Qdisc *q = शून्य;
	काष्ठा tcf_block *block;
	काष्ठा tcmsg *tcm = nlmsg_data(cb->nlh);
	काष्ठा tcf_chain *chain;
	दीर्घ index_start;
	दीर्घ index;
	पूर्णांक err;

	अगर (nlmsg_len(cb->nlh) < माप(*tcm))
		वापस skb->len;

	err = nlmsg_parse_deprecated(cb->nlh, माप(*tcm), tca, TCA_MAX,
				     rपंचांग_tca_policy, cb->extack);
	अगर (err)
		वापस err;

	अगर (tcm->tcm_अगरindex == TCM_IFINDEX_MAGIC_BLOCK) अणु
		block = tcf_block_refcnt_get(net, tcm->tcm_block_index);
		अगर (!block)
			जाओ out;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा Qdisc_class_ops *cops;
		काष्ठा net_device *dev;
		अचिन्हित दीर्घ cl = 0;

		dev = __dev_get_by_index(net, tcm->tcm_अगरindex);
		अगर (!dev)
			वापस skb->len;

		अगर (!tcm->tcm_parent)
			q = dev->qdisc;
		अन्यथा
			q = qdisc_lookup(dev, TC_H_MAJ(tcm->tcm_parent));

		अगर (!q)
			जाओ out;
		cops = q->ops->cl_ops;
		अगर (!cops)
			जाओ out;
		अगर (!cops->tcf_block)
			जाओ out;
		अगर (TC_H_MIN(tcm->tcm_parent)) अणु
			cl = cops->find(q, tcm->tcm_parent);
			अगर (cl == 0)
				जाओ out;
		पूर्ण
		block = cops->tcf_block(q, cl, शून्य);
		अगर (!block)
			जाओ out;
		अगर (tcf_block_shared(block))
			q = शून्य;
	पूर्ण

	index_start = cb->args[0];
	index = 0;

	mutex_lock(&block->lock);
	list_क्रम_each_entry(chain, &block->chain_list, list) अणु
		अगर ((tca[TCA_CHAIN] &&
		     nla_get_u32(tca[TCA_CHAIN]) != chain->index))
			जारी;
		अगर (index < index_start) अणु
			index++;
			जारी;
		पूर्ण
		अगर (tcf_chain_held_by_acts_only(chain))
			जारी;
		err = tc_chain_fill_node(chain->पंचांगplt_ops, chain->पंचांगplt_priv,
					 chain->index, net, skb, block,
					 NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq, NLM_F_MULTI,
					 RTM_NEWCHAIN);
		अगर (err <= 0)
			अवरोध;
		index++;
	पूर्ण
	mutex_unlock(&block->lock);

	अगर (tcm->tcm_अगरindex == TCM_IFINDEX_MAGIC_BLOCK)
		tcf_block_refcnt_put(block, true);
	cb->args[0] = index;

out:
	/* If we did no progress, the error (EMSGSIZE) is real */
	अगर (skb->len == 0 && err)
		वापस err;
	वापस skb->len;
पूर्ण

व्योम tcf_exts_destroy(काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (exts->actions) अणु
		tcf_action_destroy(exts->actions, TCA_ACT_UNBIND);
		kमुक्त(exts->actions);
	पूर्ण
	exts->nr_actions = 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(tcf_exts_destroy);

पूर्णांक tcf_exts_validate(काष्ठा net *net, काष्ठा tcf_proto *tp, काष्ठा nlattr **tb,
		      काष्ठा nlattr *rate_tlv, काष्ठा tcf_exts *exts, bool ovr,
		      bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अणु
		पूर्णांक init_res[TCA_ACT_MAX_PRIO] = अणुपूर्ण;
		काष्ठा tc_action *act;
		माप_प्रकार attr_size = 0;

		अगर (exts->police && tb[exts->police]) अणु
			काष्ठा tc_action_ops *a_o;

			a_o = tc_action_load_ops("police", tb[exts->police], rtnl_held, extack);
			अगर (IS_ERR(a_o))
				वापस PTR_ERR(a_o);
			act = tcf_action_init_1(net, tp, tb[exts->police],
						rate_tlv, "police", ovr,
						TCA_ACT_BIND, a_o, init_res,
						rtnl_held, extack);
			module_put(a_o->owner);
			अगर (IS_ERR(act))
				वापस PTR_ERR(act);

			act->type = exts->type = TCA_OLD_COMPAT;
			exts->actions[0] = act;
			exts->nr_actions = 1;
			tcf_idr_insert_many(exts->actions);
		पूर्ण अन्यथा अगर (exts->action && tb[exts->action]) अणु
			पूर्णांक err;

			err = tcf_action_init(net, tp, tb[exts->action],
					      rate_tlv, शून्य, ovr, TCA_ACT_BIND,
					      exts->actions, init_res,
					      &attr_size, rtnl_held, extack);
			अगर (err < 0)
				वापस err;
			exts->nr_actions = err;
		पूर्ण
	पूर्ण
#अन्यथा
	अगर ((exts->action && tb[exts->action]) ||
	    (exts->police && tb[exts->police])) अणु
		NL_SET_ERR_MSG(extack, "Classifier actions are not supported per compile options (CONFIG_NET_CLS_ACT)");
		वापस -EOPNOTSUPP;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcf_exts_validate);

व्योम tcf_exts_change(काष्ठा tcf_exts *dst, काष्ठा tcf_exts *src)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा tcf_exts old = *dst;

	*dst = *src;
	tcf_exts_destroy(&old);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(tcf_exts_change);

#अगर_घोषित CONFIG_NET_CLS_ACT
अटल काष्ठा tc_action *tcf_exts_first_act(काष्ठा tcf_exts *exts)
अणु
	अगर (exts->nr_actions == 0)
		वापस शून्य;
	अन्यथा
		वापस exts->actions[0];
पूर्ण
#पूर्ण_अगर

पूर्णांक tcf_exts_dump(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा nlattr *nest;

	अगर (exts->action && tcf_exts_has_actions(exts)) अणु
		/*
		 * again क्रम backward compatible mode - we want
		 * to work with both old and new modes of entering
		 * tc data even अगर iproute2  was newer - jhs
		 */
		अगर (exts->type != TCA_OLD_COMPAT) अणु
			nest = nla_nest_start_noflag(skb, exts->action);
			अगर (nest == शून्य)
				जाओ nla_put_failure;

			अगर (tcf_action_dump(skb, exts->actions, 0, 0, false)
			    < 0)
				जाओ nla_put_failure;
			nla_nest_end(skb, nest);
		पूर्ण अन्यथा अगर (exts->police) अणु
			काष्ठा tc_action *act = tcf_exts_first_act(exts);
			nest = nla_nest_start_noflag(skb, exts->police);
			अगर (nest == शून्य || !act)
				जाओ nla_put_failure;
			अगर (tcf_action_dump_old(skb, act, 0, 0) < 0)
				जाओ nla_put_failure;
			nla_nest_end(skb, nest);
		पूर्ण
	पूर्ण
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(tcf_exts_dump);

पूर्णांक tcf_exts_terse_dump(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा nlattr *nest;

	अगर (!exts->action || !tcf_exts_has_actions(exts))
		वापस 0;

	nest = nla_nest_start_noflag(skb, exts->action);
	अगर (!nest)
		जाओ nla_put_failure;

	अगर (tcf_action_dump(skb, exts->actions, 0, 0, true) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(tcf_exts_terse_dump);

पूर्णांक tcf_exts_dump_stats(काष्ठा sk_buff *skb, काष्ठा tcf_exts *exts)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा tc_action *a = tcf_exts_first_act(exts);
	अगर (a != शून्य && tcf_action_copy_stats(skb, a, 1) < 0)
		वापस -1;
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcf_exts_dump_stats);

अटल व्योम tcf_block_offload_inc(काष्ठा tcf_block *block, u32 *flags)
अणु
	अगर (*flags & TCA_CLS_FLAGS_IN_HW)
		वापस;
	*flags |= TCA_CLS_FLAGS_IN_HW;
	atomic_inc(&block->offloadcnt);
पूर्ण

अटल व्योम tcf_block_offload_dec(काष्ठा tcf_block *block, u32 *flags)
अणु
	अगर (!(*flags & TCA_CLS_FLAGS_IN_HW))
		वापस;
	*flags &= ~TCA_CLS_FLAGS_IN_HW;
	atomic_dec(&block->offloadcnt);
पूर्ण

अटल व्योम tc_cls_offload_cnt_update(काष्ठा tcf_block *block,
				      काष्ठा tcf_proto *tp, u32 *cnt,
				      u32 *flags, u32 dअगरf, bool add)
अणु
	lockdep_निश्चित_held(&block->cb_lock);

	spin_lock(&tp->lock);
	अगर (add) अणु
		अगर (!*cnt)
			tcf_block_offload_inc(block, flags);
		*cnt += dअगरf;
	पूर्ण अन्यथा अणु
		*cnt -= dअगरf;
		अगर (!*cnt)
			tcf_block_offload_dec(block, flags);
	पूर्ण
	spin_unlock(&tp->lock);
पूर्ण

अटल व्योम
tc_cls_offload_cnt_reset(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			 u32 *cnt, u32 *flags)
अणु
	lockdep_निश्चित_held(&block->cb_lock);

	spin_lock(&tp->lock);
	tcf_block_offload_dec(block, flags);
	*cnt = 0;
	spin_unlock(&tp->lock);
पूर्ण

अटल पूर्णांक
__tc_setup_cb_call(काष्ठा tcf_block *block, क्रमागत tc_setup_type type,
		   व्योम *type_data, bool err_stop)
अणु
	काष्ठा flow_block_cb *block_cb;
	पूर्णांक ok_count = 0;
	पूर्णांक err;

	list_क्रम_each_entry(block_cb, &block->flow_block.cb_list, list) अणु
		err = block_cb->cb(type, type_data, block_cb->cb_priv);
		अगर (err) अणु
			अगर (err_stop)
				वापस err;
		पूर्ण अन्यथा अणु
			ok_count++;
		पूर्ण
	पूर्ण
	वापस ok_count;
पूर्ण

पूर्णांक tc_setup_cb_call(काष्ठा tcf_block *block, क्रमागत tc_setup_type type,
		     व्योम *type_data, bool err_stop, bool rtnl_held)
अणु
	bool take_rtnl = READ_ONCE(block->lockeddevcnt) && !rtnl_held;
	पूर्णांक ok_count;

retry:
	अगर (take_rtnl)
		rtnl_lock();
	करोwn_पढ़ो(&block->cb_lock);
	/* Need to obtain rtnl lock अगर block is bound to devs that require it.
	 * In block bind code cb_lock is obtained जबतक holding rtnl, so we must
	 * obtain the locks in same order here.
	 */
	अगर (!rtnl_held && !take_rtnl && block->lockeddevcnt) अणु
		up_पढ़ो(&block->cb_lock);
		take_rtnl = true;
		जाओ retry;
	पूर्ण

	ok_count = __tc_setup_cb_call(block, type, type_data, err_stop);

	up_पढ़ो(&block->cb_lock);
	अगर (take_rtnl)
		rtnl_unlock();
	वापस ok_count;
पूर्ण
EXPORT_SYMBOL(tc_setup_cb_call);

/* Non-deकाष्ठाive filter add. If filter that wasn't alपढ़ोy in hardware is
 * successfully offloaded, increment block offloads counter. On failure,
 * previously offloaded filter is considered to be पूर्णांकact and offloads counter
 * is not decremented.
 */

पूर्णांक tc_setup_cb_add(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
		    क्रमागत tc_setup_type type, व्योम *type_data, bool err_stop,
		    u32 *flags, अचिन्हित पूर्णांक *in_hw_count, bool rtnl_held)
अणु
	bool take_rtnl = READ_ONCE(block->lockeddevcnt) && !rtnl_held;
	पूर्णांक ok_count;

retry:
	अगर (take_rtnl)
		rtnl_lock();
	करोwn_पढ़ो(&block->cb_lock);
	/* Need to obtain rtnl lock अगर block is bound to devs that require it.
	 * In block bind code cb_lock is obtained जबतक holding rtnl, so we must
	 * obtain the locks in same order here.
	 */
	अगर (!rtnl_held && !take_rtnl && block->lockeddevcnt) अणु
		up_पढ़ो(&block->cb_lock);
		take_rtnl = true;
		जाओ retry;
	पूर्ण

	/* Make sure all netdevs sharing this block are offload-capable. */
	अगर (block->nooffloaddevcnt && err_stop) अणु
		ok_count = -EOPNOTSUPP;
		जाओ err_unlock;
	पूर्ण

	ok_count = __tc_setup_cb_call(block, type, type_data, err_stop);
	अगर (ok_count < 0)
		जाओ err_unlock;

	अगर (tp->ops->hw_add)
		tp->ops->hw_add(tp, type_data);
	अगर (ok_count > 0)
		tc_cls_offload_cnt_update(block, tp, in_hw_count, flags,
					  ok_count, true);
err_unlock:
	up_पढ़ो(&block->cb_lock);
	अगर (take_rtnl)
		rtnl_unlock();
	वापस ok_count < 0 ? ok_count : 0;
पूर्ण
EXPORT_SYMBOL(tc_setup_cb_add);

/* Deकाष्ठाive filter replace. If filter that wasn't alपढ़ोy in hardware is
 * successfully offloaded, increment block offload counter. On failure,
 * previously offloaded filter is considered to be destroyed and offload counter
 * is decremented.
 */

पूर्णांक tc_setup_cb_replace(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			क्रमागत tc_setup_type type, व्योम *type_data, bool err_stop,
			u32 *old_flags, अचिन्हित पूर्णांक *old_in_hw_count,
			u32 *new_flags, अचिन्हित पूर्णांक *new_in_hw_count,
			bool rtnl_held)
अणु
	bool take_rtnl = READ_ONCE(block->lockeddevcnt) && !rtnl_held;
	पूर्णांक ok_count;

retry:
	अगर (take_rtnl)
		rtnl_lock();
	करोwn_पढ़ो(&block->cb_lock);
	/* Need to obtain rtnl lock अगर block is bound to devs that require it.
	 * In block bind code cb_lock is obtained जबतक holding rtnl, so we must
	 * obtain the locks in same order here.
	 */
	अगर (!rtnl_held && !take_rtnl && block->lockeddevcnt) अणु
		up_पढ़ो(&block->cb_lock);
		take_rtnl = true;
		जाओ retry;
	पूर्ण

	/* Make sure all netdevs sharing this block are offload-capable. */
	अगर (block->nooffloaddevcnt && err_stop) अणु
		ok_count = -EOPNOTSUPP;
		जाओ err_unlock;
	पूर्ण

	tc_cls_offload_cnt_reset(block, tp, old_in_hw_count, old_flags);
	अगर (tp->ops->hw_del)
		tp->ops->hw_del(tp, type_data);

	ok_count = __tc_setup_cb_call(block, type, type_data, err_stop);
	अगर (ok_count < 0)
		जाओ err_unlock;

	अगर (tp->ops->hw_add)
		tp->ops->hw_add(tp, type_data);
	अगर (ok_count > 0)
		tc_cls_offload_cnt_update(block, tp, new_in_hw_count,
					  new_flags, ok_count, true);
err_unlock:
	up_पढ़ो(&block->cb_lock);
	अगर (take_rtnl)
		rtnl_unlock();
	वापस ok_count < 0 ? ok_count : 0;
पूर्ण
EXPORT_SYMBOL(tc_setup_cb_replace);

/* Destroy filter and decrement block offload counter, अगर filter was previously
 * offloaded.
 */

पूर्णांक tc_setup_cb_destroy(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			क्रमागत tc_setup_type type, व्योम *type_data, bool err_stop,
			u32 *flags, अचिन्हित पूर्णांक *in_hw_count, bool rtnl_held)
अणु
	bool take_rtnl = READ_ONCE(block->lockeddevcnt) && !rtnl_held;
	पूर्णांक ok_count;

retry:
	अगर (take_rtnl)
		rtnl_lock();
	करोwn_पढ़ो(&block->cb_lock);
	/* Need to obtain rtnl lock अगर block is bound to devs that require it.
	 * In block bind code cb_lock is obtained जबतक holding rtnl, so we must
	 * obtain the locks in same order here.
	 */
	अगर (!rtnl_held && !take_rtnl && block->lockeddevcnt) अणु
		up_पढ़ो(&block->cb_lock);
		take_rtnl = true;
		जाओ retry;
	पूर्ण

	ok_count = __tc_setup_cb_call(block, type, type_data, err_stop);

	tc_cls_offload_cnt_reset(block, tp, in_hw_count, flags);
	अगर (tp->ops->hw_del)
		tp->ops->hw_del(tp, type_data);

	up_पढ़ो(&block->cb_lock);
	अगर (take_rtnl)
		rtnl_unlock();
	वापस ok_count < 0 ? ok_count : 0;
पूर्ण
EXPORT_SYMBOL(tc_setup_cb_destroy);

पूर्णांक tc_setup_cb_reoffload(काष्ठा tcf_block *block, काष्ठा tcf_proto *tp,
			  bool add, flow_setup_cb_t *cb,
			  क्रमागत tc_setup_type type, व्योम *type_data,
			  व्योम *cb_priv, u32 *flags, अचिन्हित पूर्णांक *in_hw_count)
अणु
	पूर्णांक err = cb(type, type_data, cb_priv);

	अगर (err) अणु
		अगर (add && tc_skip_sw(*flags))
			वापस err;
	पूर्ण अन्यथा अणु
		tc_cls_offload_cnt_update(block, tp, in_hw_count, flags, 1,
					  add);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tc_setup_cb_reoffload);

अटल पूर्णांक tcf_act_get_cookie(काष्ठा flow_action_entry *entry,
			      स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tc_cookie *cookie;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	cookie = rcu_dereference(act->act_cookie);
	अगर (cookie) अणु
		entry->cookie = flow_action_cookie_create(cookie->data,
							  cookie->len,
							  GFP_ATOMIC);
		अगर (!entry->cookie)
			err = -ENOMEM;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल व्योम tcf_act_put_cookie(काष्ठा flow_action_entry *entry)
अणु
	flow_action_cookie_destroy(entry->cookie);
पूर्ण

व्योम tc_cleanup_flow_action(काष्ठा flow_action *flow_action)
अणु
	काष्ठा flow_action_entry *entry;
	पूर्णांक i;

	flow_action_क्रम_each(i, entry, flow_action) अणु
		tcf_act_put_cookie(entry);
		अगर (entry->deकाष्ठाor)
			entry->deकाष्ठाor(entry->deकाष्ठाor_priv);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tc_cleanup_flow_action);

अटल व्योम tcf_mirred_get_dev(काष्ठा flow_action_entry *entry,
			       स्थिर काष्ठा tc_action *act)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	entry->dev = act->ops->get_dev(act, &entry->deकाष्ठाor);
	अगर (!entry->dev)
		वापस;
	entry->deकाष्ठाor_priv = entry->dev;
#पूर्ण_अगर
पूर्ण

अटल व्योम tcf_tunnel_encap_put_tunnel(व्योम *priv)
अणु
	काष्ठा ip_tunnel_info *tunnel = priv;

	kमुक्त(tunnel);
पूर्ण

अटल पूर्णांक tcf_tunnel_encap_get_tunnel(काष्ठा flow_action_entry *entry,
				       स्थिर काष्ठा tc_action *act)
अणु
	entry->tunnel = tcf_tunnel_info_copy(act);
	अगर (!entry->tunnel)
		वापस -ENOMEM;
	entry->deकाष्ठाor = tcf_tunnel_encap_put_tunnel;
	entry->deकाष्ठाor_priv = entry->tunnel;
	वापस 0;
पूर्ण

अटल व्योम tcf_sample_get_group(काष्ठा flow_action_entry *entry,
				 स्थिर काष्ठा tc_action *act)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	entry->sample.psample_group =
		act->ops->get_psample_group(act, &entry->deकाष्ठाor);
	entry->deकाष्ठाor_priv = entry->sample.psample_group;
#पूर्ण_अगर
पूर्ण

अटल व्योम tcf_gate_entry_deकाष्ठाor(व्योम *priv)
अणु
	काष्ठा action_gate_entry *oe = priv;

	kमुक्त(oe);
पूर्ण

अटल पूर्णांक tcf_gate_get_entries(काष्ठा flow_action_entry *entry,
				स्थिर काष्ठा tc_action *act)
अणु
	entry->gate.entries = tcf_gate_get_list(act);

	अगर (!entry->gate.entries)
		वापस -EINVAL;

	entry->deकाष्ठाor = tcf_gate_entry_deकाष्ठाor;
	entry->deकाष्ठाor_priv = entry->gate.entries;

	वापस 0;
पूर्ण

अटल क्रमागत flow_action_hw_stats tc_act_hw_stats(u8 hw_stats)
अणु
	अगर (WARN_ON_ONCE(hw_stats > TCA_ACT_HW_STATS_ANY))
		वापस FLOW_ACTION_HW_STATS_DONT_CARE;
	अन्यथा अगर (!hw_stats)
		वापस FLOW_ACTION_HW_STATS_DISABLED;

	वापस hw_stats;
पूर्ण

पूर्णांक tc_setup_flow_action(काष्ठा flow_action *flow_action,
			 स्थिर काष्ठा tcf_exts *exts)
अणु
	काष्ठा tc_action *act;
	पूर्णांक i, j, k, err = 0;

	BUILD_BUG_ON(TCA_ACT_HW_STATS_ANY != FLOW_ACTION_HW_STATS_ANY);
	BUILD_BUG_ON(TCA_ACT_HW_STATS_IMMEDIATE != FLOW_ACTION_HW_STATS_IMMEDIATE);
	BUILD_BUG_ON(TCA_ACT_HW_STATS_DELAYED != FLOW_ACTION_HW_STATS_DELAYED);

	अगर (!exts)
		वापस 0;

	j = 0;
	tcf_exts_क्रम_each_action(i, act, exts) अणु
		काष्ठा flow_action_entry *entry;

		entry = &flow_action->entries[j];
		spin_lock_bh(&act->tcfa_lock);
		err = tcf_act_get_cookie(entry, act);
		अगर (err)
			जाओ err_out_locked;

		entry->hw_stats = tc_act_hw_stats(act->hw_stats);

		अगर (is_tcf_gact_ok(act)) अणु
			entry->id = FLOW_ACTION_ACCEPT;
		पूर्ण अन्यथा अगर (is_tcf_gact_shot(act)) अणु
			entry->id = FLOW_ACTION_DROP;
		पूर्ण अन्यथा अगर (is_tcf_gact_trap(act)) अणु
			entry->id = FLOW_ACTION_TRAP;
		पूर्ण अन्यथा अगर (is_tcf_gact_जाओ_chain(act)) अणु
			entry->id = FLOW_ACTION_GOTO;
			entry->chain_index = tcf_gact_जाओ_chain_index(act);
		पूर्ण अन्यथा अगर (is_tcf_mirred_egress_redirect(act)) अणु
			entry->id = FLOW_ACTION_REसूचीECT;
			tcf_mirred_get_dev(entry, act);
		पूर्ण अन्यथा अगर (is_tcf_mirred_egress_mirror(act)) अणु
			entry->id = FLOW_ACTION_MIRRED;
			tcf_mirred_get_dev(entry, act);
		पूर्ण अन्यथा अगर (is_tcf_mirred_ingress_redirect(act)) अणु
			entry->id = FLOW_ACTION_REसूचीECT_INGRESS;
			tcf_mirred_get_dev(entry, act);
		पूर्ण अन्यथा अगर (is_tcf_mirred_ingress_mirror(act)) अणु
			entry->id = FLOW_ACTION_MIRRED_INGRESS;
			tcf_mirred_get_dev(entry, act);
		पूर्ण अन्यथा अगर (is_tcf_vlan(act)) अणु
			चयन (tcf_vlan_action(act)) अणु
			हाल TCA_VLAN_ACT_PUSH:
				entry->id = FLOW_ACTION_VLAN_PUSH;
				entry->vlan.vid = tcf_vlan_push_vid(act);
				entry->vlan.proto = tcf_vlan_push_proto(act);
				entry->vlan.prio = tcf_vlan_push_prio(act);
				अवरोध;
			हाल TCA_VLAN_ACT_POP:
				entry->id = FLOW_ACTION_VLAN_POP;
				अवरोध;
			हाल TCA_VLAN_ACT_MODIFY:
				entry->id = FLOW_ACTION_VLAN_MANGLE;
				entry->vlan.vid = tcf_vlan_push_vid(act);
				entry->vlan.proto = tcf_vlan_push_proto(act);
				entry->vlan.prio = tcf_vlan_push_prio(act);
				अवरोध;
			शेष:
				err = -EOPNOTSUPP;
				जाओ err_out_locked;
			पूर्ण
		पूर्ण अन्यथा अगर (is_tcf_tunnel_set(act)) अणु
			entry->id = FLOW_ACTION_TUNNEL_ENCAP;
			err = tcf_tunnel_encap_get_tunnel(entry, act);
			अगर (err)
				जाओ err_out_locked;
		पूर्ण अन्यथा अगर (is_tcf_tunnel_release(act)) अणु
			entry->id = FLOW_ACTION_TUNNEL_DECAP;
		पूर्ण अन्यथा अगर (is_tcf_pedit(act)) अणु
			क्रम (k = 0; k < tcf_pedit_nkeys(act); k++) अणु
				चयन (tcf_pedit_cmd(act, k)) अणु
				हाल TCA_PEDIT_KEY_EX_CMD_SET:
					entry->id = FLOW_ACTION_MANGLE;
					अवरोध;
				हाल TCA_PEDIT_KEY_EX_CMD_ADD:
					entry->id = FLOW_ACTION_ADD;
					अवरोध;
				शेष:
					err = -EOPNOTSUPP;
					जाओ err_out_locked;
				पूर्ण
				entry->mangle.htype = tcf_pedit_htype(act, k);
				entry->mangle.mask = tcf_pedit_mask(act, k);
				entry->mangle.val = tcf_pedit_val(act, k);
				entry->mangle.offset = tcf_pedit_offset(act, k);
				entry->hw_stats = tc_act_hw_stats(act->hw_stats);
				entry = &flow_action->entries[++j];
			पूर्ण
		पूर्ण अन्यथा अगर (is_tcf_csum(act)) अणु
			entry->id = FLOW_ACTION_CSUM;
			entry->csum_flags = tcf_csum_update_flags(act);
		पूर्ण अन्यथा अगर (is_tcf_skbedit_mark(act)) अणु
			entry->id = FLOW_ACTION_MARK;
			entry->mark = tcf_skbedit_mark(act);
		पूर्ण अन्यथा अगर (is_tcf_sample(act)) अणु
			entry->id = FLOW_ACTION_SAMPLE;
			entry->sample.trunc_size = tcf_sample_trunc_size(act);
			entry->sample.truncate = tcf_sample_truncate(act);
			entry->sample.rate = tcf_sample_rate(act);
			tcf_sample_get_group(entry, act);
		पूर्ण अन्यथा अगर (is_tcf_police(act)) अणु
			entry->id = FLOW_ACTION_POLICE;
			entry->police.burst = tcf_police_burst(act);
			entry->police.rate_bytes_ps =
				tcf_police_rate_bytes_ps(act);
			entry->police.burst_pkt = tcf_police_burst_pkt(act);
			entry->police.rate_pkt_ps =
				tcf_police_rate_pkt_ps(act);
			entry->police.mtu = tcf_police_tcfp_mtu(act);
			entry->police.index = act->tcfa_index;
		पूर्ण अन्यथा अगर (is_tcf_ct(act)) अणु
			entry->id = FLOW_ACTION_CT;
			entry->ct.action = tcf_ct_action(act);
			entry->ct.zone = tcf_ct_zone(act);
			entry->ct.flow_table = tcf_ct_ft(act);
		पूर्ण अन्यथा अगर (is_tcf_mpls(act)) अणु
			चयन (tcf_mpls_action(act)) अणु
			हाल TCA_MPLS_ACT_PUSH:
				entry->id = FLOW_ACTION_MPLS_PUSH;
				entry->mpls_push.proto = tcf_mpls_proto(act);
				entry->mpls_push.label = tcf_mpls_label(act);
				entry->mpls_push.tc = tcf_mpls_tc(act);
				entry->mpls_push.bos = tcf_mpls_bos(act);
				entry->mpls_push.ttl = tcf_mpls_ttl(act);
				अवरोध;
			हाल TCA_MPLS_ACT_POP:
				entry->id = FLOW_ACTION_MPLS_POP;
				entry->mpls_pop.proto = tcf_mpls_proto(act);
				अवरोध;
			हाल TCA_MPLS_ACT_MODIFY:
				entry->id = FLOW_ACTION_MPLS_MANGLE;
				entry->mpls_mangle.label = tcf_mpls_label(act);
				entry->mpls_mangle.tc = tcf_mpls_tc(act);
				entry->mpls_mangle.bos = tcf_mpls_bos(act);
				entry->mpls_mangle.ttl = tcf_mpls_ttl(act);
				अवरोध;
			शेष:
				जाओ err_out_locked;
			पूर्ण
		पूर्ण अन्यथा अगर (is_tcf_skbedit_ptype(act)) अणु
			entry->id = FLOW_ACTION_PTYPE;
			entry->ptype = tcf_skbedit_ptype(act);
		पूर्ण अन्यथा अगर (is_tcf_skbedit_priority(act)) अणु
			entry->id = FLOW_ACTION_PRIORITY;
			entry->priority = tcf_skbedit_priority(act);
		पूर्ण अन्यथा अगर (is_tcf_gate(act)) अणु
			entry->id = FLOW_ACTION_GATE;
			entry->gate.index = tcf_gate_index(act);
			entry->gate.prio = tcf_gate_prio(act);
			entry->gate.baseसमय = tcf_gate_baseसमय(act);
			entry->gate.cycleसमय = tcf_gate_cycleसमय(act);
			entry->gate.cycleसमयext = tcf_gate_cycleसमयext(act);
			entry->gate.num_entries = tcf_gate_num_entries(act);
			err = tcf_gate_get_entries(entry, act);
			अगर (err)
				जाओ err_out_locked;
		पूर्ण अन्यथा अणु
			err = -EOPNOTSUPP;
			जाओ err_out_locked;
		पूर्ण
		spin_unlock_bh(&act->tcfa_lock);

		अगर (!is_tcf_pedit(act))
			j++;
	पूर्ण

err_out:
	अगर (err)
		tc_cleanup_flow_action(flow_action);

	वापस err;
err_out_locked:
	spin_unlock_bh(&act->tcfa_lock);
	जाओ err_out;
पूर्ण
EXPORT_SYMBOL(tc_setup_flow_action);

अचिन्हित पूर्णांक tcf_exts_num_actions(काष्ठा tcf_exts *exts)
अणु
	अचिन्हित पूर्णांक num_acts = 0;
	काष्ठा tc_action *act;
	पूर्णांक i;

	tcf_exts_क्रम_each_action(i, act, exts) अणु
		अगर (is_tcf_pedit(act))
			num_acts += tcf_pedit_nkeys(act);
		अन्यथा
			num_acts++;
	पूर्ण
	वापस num_acts;
पूर्ण
EXPORT_SYMBOL(tcf_exts_num_actions);

#अगर_घोषित CONFIG_NET_CLS_ACT
अटल पूर्णांक tcf_qevent_parse_block_index(काष्ठा nlattr *block_index_attr,
					u32 *p_block_index,
					काष्ठा netlink_ext_ack *extack)
अणु
	*p_block_index = nla_get_u32(block_index_attr);
	अगर (!*p_block_index) अणु
		NL_SET_ERR_MSG(extack, "Block number may not be zero");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tcf_qevent_init(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch,
		    क्रमागत flow_block_binder_type binder_type,
		    काष्ठा nlattr *block_index_attr,
		    काष्ठा netlink_ext_ack *extack)
अणु
	u32 block_index;
	पूर्णांक err;

	अगर (!block_index_attr)
		वापस 0;

	err = tcf_qevent_parse_block_index(block_index_attr, &block_index, extack);
	अगर (err)
		वापस err;

	अगर (!block_index)
		वापस 0;

	qe->info.binder_type = binder_type;
	qe->info.chain_head_change = tcf_chain_head_change_dflt;
	qe->info.chain_head_change_priv = &qe->filter_chain;
	qe->info.block_index = block_index;

	वापस tcf_block_get_ext(&qe->block, sch, &qe->info, extack);
पूर्ण
EXPORT_SYMBOL(tcf_qevent_init);

व्योम tcf_qevent_destroy(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch)
अणु
	अगर (qe->info.block_index)
		tcf_block_put_ext(qe->block, sch, &qe->info);
पूर्ण
EXPORT_SYMBOL(tcf_qevent_destroy);

पूर्णांक tcf_qevent_validate_change(काष्ठा tcf_qevent *qe, काष्ठा nlattr *block_index_attr,
			       काष्ठा netlink_ext_ack *extack)
अणु
	u32 block_index;
	पूर्णांक err;

	अगर (!block_index_attr)
		वापस 0;

	err = tcf_qevent_parse_block_index(block_index_attr, &block_index, extack);
	अगर (err)
		वापस err;

	/* Bounce newly-configured block or change in block. */
	अगर (block_index != qe->info.block_index) अणु
		NL_SET_ERR_MSG(extack, "Change of blocks is not supported");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcf_qevent_validate_change);

काष्ठा sk_buff *tcf_qevent_handle(काष्ठा tcf_qevent *qe, काष्ठा Qdisc *sch, काष्ठा sk_buff *skb,
				  काष्ठा sk_buff **to_मुक्त, पूर्णांक *ret)
अणु
	काष्ठा tcf_result cl_res;
	काष्ठा tcf_proto *fl;

	अगर (!qe->info.block_index)
		वापस skb;

	fl = rcu_dereference_bh(qe->filter_chain);

	चयन (tcf_classअगरy(skb, fl, &cl_res, false)) अणु
	हाल TC_ACT_SHOT:
		qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		*ret = __NET_XMIT_BYPASS;
		वापस शून्य;
	हाल TC_ACT_STOLEN:
	हाल TC_ACT_QUEUED:
	हाल TC_ACT_TRAP:
		__qdisc_drop(skb, to_मुक्त);
		*ret = __NET_XMIT_STOLEN;
		वापस शून्य;
	हाल TC_ACT_REसूचीECT:
		skb_करो_redirect(skb);
		*ret = __NET_XMIT_STOLEN;
		वापस शून्य;
	पूर्ण

	वापस skb;
पूर्ण
EXPORT_SYMBOL(tcf_qevent_handle);

पूर्णांक tcf_qevent_dump(काष्ठा sk_buff *skb, पूर्णांक attr_name, काष्ठा tcf_qevent *qe)
अणु
	अगर (!qe->info.block_index)
		वापस 0;
	वापस nla_put_u32(skb, attr_name, qe->info.block_index);
पूर्ण
EXPORT_SYMBOL(tcf_qevent_dump);
#पूर्ण_अगर

अटल __net_init पूर्णांक tcf_net_init(काष्ठा net *net)
अणु
	काष्ठा tcf_net *tn = net_generic(net, tcf_net_id);

	spin_lock_init(&tn->idr_lock);
	idr_init(&tn->idr);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास tcf_net_निकास(काष्ठा net *net)
अणु
	काष्ठा tcf_net *tn = net_generic(net, tcf_net_id);

	idr_destroy(&tn->idr);
पूर्ण

अटल काष्ठा pernet_operations tcf_net_ops = अणु
	.init = tcf_net_init,
	.निकास = tcf_net_निकास,
	.id   = &tcf_net_id,
	.size = माप(काष्ठा tcf_net),
पूर्ण;

अटल पूर्णांक __init tc_filter_init(व्योम)
अणु
	पूर्णांक err;

	tc_filter_wq = alloc_ordered_workqueue("tc_filter_workqueue", 0);
	अगर (!tc_filter_wq)
		वापस -ENOMEM;

	err = रेजिस्टर_pernet_subsys(&tcf_net_ops);
	अगर (err)
		जाओ err_रेजिस्टर_pernet_subsys;

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWTFILTER, tc_new_tfilter, शून्य,
		      RTNL_FLAG_DOIT_UNLOCKED);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELTFILTER, tc_del_tfilter, शून्य,
		      RTNL_FLAG_DOIT_UNLOCKED);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETTFILTER, tc_get_tfilter,
		      tc_dump_tfilter, RTNL_FLAG_DOIT_UNLOCKED);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWCHAIN, tc_ctl_chain, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELCHAIN, tc_ctl_chain, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETCHAIN, tc_ctl_chain,
		      tc_dump_chain, 0);

	वापस 0;

err_रेजिस्टर_pernet_subsys:
	destroy_workqueue(tc_filter_wq);
	वापस err;
पूर्ण

subsys_initcall(tc_filter_init);
