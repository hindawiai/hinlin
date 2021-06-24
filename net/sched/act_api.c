<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_api.c	Packet action API.
 *
 * Author:	Jamal Hadi Salim
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/act_api.h>
#समावेश <net/netlink.h>

#अगर_घोषित CONFIG_INET
DEFINE_STATIC_KEY_FALSE(tcf_frag_xmit_count);
EXPORT_SYMBOL_GPL(tcf_frag_xmit_count);
#पूर्ण_अगर

पूर्णांक tcf_dev_queue_xmit(काष्ठा sk_buff *skb, पूर्णांक (*xmit)(काष्ठा sk_buff *skb))
अणु
#अगर_घोषित CONFIG_INET
	अगर (अटल_branch_unlikely(&tcf_frag_xmit_count))
		वापस sch_frag_xmit_hook(skb, xmit);
#पूर्ण_अगर

	वापस xmit(skb);
पूर्ण
EXPORT_SYMBOL_GPL(tcf_dev_queue_xmit);

अटल व्योम tcf_action_जाओ_chain_exec(स्थिर काष्ठा tc_action *a,
				       काष्ठा tcf_result *res)
अणु
	स्थिर काष्ठा tcf_chain *chain = rcu_dereference_bh(a->जाओ_chain);

	res->जाओ_tp = rcu_dereference_bh(chain->filter_chain);
पूर्ण

अटल व्योम tcf_मुक्त_cookie_rcu(काष्ठा rcu_head *p)
अणु
	काष्ठा tc_cookie *cookie = container_of(p, काष्ठा tc_cookie, rcu);

	kमुक्त(cookie->data);
	kमुक्त(cookie);
पूर्ण

अटल व्योम tcf_set_action_cookie(काष्ठा tc_cookie __rcu **old_cookie,
				  काष्ठा tc_cookie *new_cookie)
अणु
	काष्ठा tc_cookie *old;

	old = xchg((__क्रमce काष्ठा tc_cookie **)old_cookie, new_cookie);
	अगर (old)
		call_rcu(&old->rcu, tcf_मुक्त_cookie_rcu);
पूर्ण

पूर्णांक tcf_action_check_ctrlact(पूर्णांक action, काष्ठा tcf_proto *tp,
			     काष्ठा tcf_chain **newchain,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक opcode = TC_ACT_EXT_OPCODE(action), ret = -EINVAL;
	u32 chain_index;

	अगर (!opcode)
		ret = action > TC_ACT_VALUE_MAX ? -EINVAL : 0;
	अन्यथा अगर (opcode <= TC_ACT_EXT_OPCODE_MAX || action == TC_ACT_UNSPEC)
		ret = 0;
	अगर (ret) अणु
		NL_SET_ERR_MSG(extack, "invalid control action");
		जाओ end;
	पूर्ण

	अगर (TC_ACT_EXT_CMP(action, TC_ACT_GOTO_CHAIN)) अणु
		chain_index = action & TC_ACT_EXT_VAL_MASK;
		अगर (!tp || !newchain) अणु
			ret = -EINVAL;
			NL_SET_ERR_MSG(extack,
				       "can't goto NULL proto/chain");
			जाओ end;
		पूर्ण
		*newchain = tcf_chain_get_by_act(tp->chain->block, chain_index);
		अगर (!*newchain) अणु
			ret = -ENOMEM;
			NL_SET_ERR_MSG(extack,
				       "can't allocate goto_chain");
		पूर्ण
	पूर्ण
end:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcf_action_check_ctrlact);

काष्ठा tcf_chain *tcf_action_set_ctrlact(काष्ठा tc_action *a, पूर्णांक action,
					 काष्ठा tcf_chain *जाओ_chain)
अणु
	a->tcfa_action = action;
	जाओ_chain = rcu_replace_poपूर्णांकer(a->जाओ_chain, जाओ_chain, 1);
	वापस जाओ_chain;
पूर्ण
EXPORT_SYMBOL(tcf_action_set_ctrlact);

/* XXX: For standalone actions, we करोn't need a RCU grace period either, because
 * actions are always connected to filters and filters are alपढ़ोy destroyed in
 * RCU callbacks, so after a RCU grace period actions are alपढ़ोy disconnected
 * from filters. Readers later can not find us.
 */
अटल व्योम मुक्त_tcf(काष्ठा tc_action *p)
अणु
	काष्ठा tcf_chain *chain = rcu_dereference_रक्षित(p->जाओ_chain, 1);

	मुक्त_percpu(p->cpu_bstats);
	मुक्त_percpu(p->cpu_bstats_hw);
	मुक्त_percpu(p->cpu_qstats);

	tcf_set_action_cookie(&p->act_cookie, शून्य);
	अगर (chain)
		tcf_chain_put_by_act(chain);

	kमुक्त(p);
पूर्ण

अटल व्योम tcf_action_cleanup(काष्ठा tc_action *p)
अणु
	अगर (p->ops->cleanup)
		p->ops->cleanup(p);

	gen_समाप्त_estimator(&p->tcfa_rate_est);
	मुक्त_tcf(p);
पूर्ण

अटल पूर्णांक __tcf_action_put(काष्ठा tc_action *p, bool bind)
अणु
	काष्ठा tcf_idrinfo *idrinfo = p->idrinfo;

	अगर (refcount_dec_and_mutex_lock(&p->tcfa_refcnt, &idrinfo->lock)) अणु
		अगर (bind)
			atomic_dec(&p->tcfa_bindcnt);
		idr_हटाओ(&idrinfo->action_idr, p->tcfa_index);
		mutex_unlock(&idrinfo->lock);

		tcf_action_cleanup(p);
		वापस 1;
	पूर्ण

	अगर (bind)
		atomic_dec(&p->tcfa_bindcnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __tcf_idr_release(काष्ठा tc_action *p, bool bind, bool strict)
अणु
	पूर्णांक ret = 0;

	/* Release with strict==1 and bind==0 is only called through act API
	 * पूर्णांकerface (classअगरiers always bind). Only हाल when action with
	 * positive reference count and zero bind count can exist is when it was
	 * also created with act API (unbinding last classअगरier will destroy the
	 * action अगर it was created by classअगरier). So only हाल when bind count
	 * can be changed after initial check is when unbound action is
	 * destroyed by act API जबतक classअगरier binds to action with same id
	 * concurrently. This result either creation of new action(same behavior
	 * as beक्रमe), or reusing existing action अगर concurrent process
	 * increments reference count beक्रमe action is deleted. Both scenarios
	 * are acceptable.
	 */
	अगर (p) अणु
		अगर (!bind && strict && atomic_पढ़ो(&p->tcfa_bindcnt) > 0)
			वापस -EPERM;

		अगर (__tcf_action_put(p, bind))
			ret = ACT_P_DELETED;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक tcf_idr_release(काष्ठा tc_action *a, bool bind)
अणु
	स्थिर काष्ठा tc_action_ops *ops = a->ops;
	पूर्णांक ret;

	ret = __tcf_idr_release(a, bind, false);
	अगर (ret == ACT_P_DELETED)
		module_put(ops->owner);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcf_idr_release);

अटल माप_प्रकार tcf_action_shared_attrs_size(स्थिर काष्ठा tc_action *act)
अणु
	काष्ठा tc_cookie *act_cookie;
	u32 cookie_len = 0;

	rcu_पढ़ो_lock();
	act_cookie = rcu_dereference(act->act_cookie);

	अगर (act_cookie)
		cookie_len = nla_total_size(act_cookie->len);
	rcu_पढ़ो_unlock();

	वापस  nla_total_size(0) /* action number nested */
		+ nla_total_size(IFNAMSIZ) /* TCA_ACT_KIND */
		+ cookie_len /* TCA_ACT_COOKIE */
		+ nla_total_size(माप(काष्ठा nla_bitfield32)) /* TCA_ACT_HW_STATS */
		+ nla_total_size(0) /* TCA_ACT_STATS nested */
		+ nla_total_size(माप(काष्ठा nla_bitfield32)) /* TCA_ACT_FLAGS */
		/* TCA_STATS_BASIC */
		+ nla_total_size_64bit(माप(काष्ठा gnet_stats_basic))
		/* TCA_STATS_PKT64 */
		+ nla_total_size_64bit(माप(u64))
		/* TCA_STATS_QUEUE */
		+ nla_total_size_64bit(माप(काष्ठा gnet_stats_queue))
		+ nla_total_size(0) /* TCA_OPTIONS nested */
		+ nla_total_size(माप(काष्ठा tcf_t)); /* TCA_GACT_TM */
पूर्ण

अटल माप_प्रकार tcf_action_full_attrs_size(माप_प्रकार sz)
अणु
	वापस NLMSG_HDRLEN                     /* काष्ठा nlmsghdr */
		+ माप(काष्ठा tcamsg)
		+ nla_total_size(0)             /* TCA_ACT_TAB nested */
		+ sz;
पूर्ण

अटल माप_प्रकार tcf_action_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	माप_प्रकार sz = tcf_action_shared_attrs_size(act);

	अगर (act->ops->get_fill_size)
		वापस act->ops->get_fill_size(act) + sz;
	वापस sz;
पूर्ण

अटल पूर्णांक
tcf_action_dump_terse(काष्ठा sk_buff *skb, काष्ठा tc_action *a, bool from_act)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_cookie *cookie;

	अगर (nla_put_string(skb, TCA_KIND, a->ops->kind))
		जाओ nla_put_failure;
	अगर (tcf_action_copy_stats(skb, a, 0))
		जाओ nla_put_failure;
	अगर (from_act && nla_put_u32(skb, TCA_ACT_INDEX, a->tcfa_index))
		जाओ nla_put_failure;

	rcu_पढ़ो_lock();
	cookie = rcu_dereference(a->act_cookie);
	अगर (cookie) अणु
		अगर (nla_put(skb, TCA_ACT_COOKIE, cookie->len, cookie->data)) अणु
			rcu_पढ़ो_unlock();
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_dump_walker(काष्ठा tcf_idrinfo *idrinfo, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb)
अणु
	पूर्णांक err = 0, index = -1, s_i = 0, n_i = 0;
	u32 act_flags = cb->args[2];
	अचिन्हित दीर्घ jअगरfy_since = cb->args[3];
	काष्ठा nlattr *nest;
	काष्ठा idr *idr = &idrinfo->action_idr;
	काष्ठा tc_action *p;
	अचिन्हित दीर्घ id = 1;
	अचिन्हित दीर्घ पंचांगp;

	mutex_lock(&idrinfo->lock);

	s_i = cb->args[0];

	idr_क्रम_each_entry_ul(idr, p, पंचांगp, id) अणु
		index++;
		अगर (index < s_i)
			जारी;
		अगर (IS_ERR(p))
			जारी;

		अगर (jअगरfy_since &&
		    समय_after(jअगरfy_since,
			       (अचिन्हित दीर्घ)p->tcfa_पंचांग.lastuse))
			जारी;

		nest = nla_nest_start_noflag(skb, n_i);
		अगर (!nest) अणु
			index--;
			जाओ nla_put_failure;
		पूर्ण
		err = (act_flags & TCA_ACT_FLAG_TERSE_DUMP) ?
			tcf_action_dump_terse(skb, p, true) :
			tcf_action_dump_1(skb, p, 0, 0);
		अगर (err < 0) अणु
			index--;
			nlmsg_trim(skb, nest);
			जाओ करोne;
		पूर्ण
		nla_nest_end(skb, nest);
		n_i++;
		अगर (!(act_flags & TCA_ACT_FLAG_LARGE_DUMP_ON) &&
		    n_i >= TCA_ACT_MAX_PRIO)
			जाओ करोne;
	पूर्ण
करोne:
	अगर (index >= 0)
		cb->args[0] = index + 1;

	mutex_unlock(&idrinfo->lock);
	अगर (n_i) अणु
		अगर (act_flags & TCA_ACT_FLAG_LARGE_DUMP_ON)
			cb->args[1] = n_i;
	पूर्ण
	वापस n_i;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	जाओ करोne;
पूर्ण

अटल पूर्णांक tcf_idr_release_unsafe(काष्ठा tc_action *p)
अणु
	अगर (atomic_पढ़ो(&p->tcfa_bindcnt) > 0)
		वापस -EPERM;

	अगर (refcount_dec_and_test(&p->tcfa_refcnt)) अणु
		idr_हटाओ(&p->idrinfo->action_idr, p->tcfa_index);
		tcf_action_cleanup(p);
		वापस ACT_P_DELETED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_del_walker(काष्ठा tcf_idrinfo *idrinfo, काष्ठा sk_buff *skb,
			  स्थिर काष्ठा tc_action_ops *ops)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक n_i = 0;
	पूर्णांक ret = -EINVAL;
	काष्ठा idr *idr = &idrinfo->action_idr;
	काष्ठा tc_action *p;
	अचिन्हित दीर्घ id = 1;
	अचिन्हित दीर्घ पंचांगp;

	nest = nla_nest_start_noflag(skb, 0);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, TCA_KIND, ops->kind))
		जाओ nla_put_failure;

	mutex_lock(&idrinfo->lock);
	idr_क्रम_each_entry_ul(idr, p, पंचांगp, id) अणु
		अगर (IS_ERR(p))
			जारी;
		ret = tcf_idr_release_unsafe(p);
		अगर (ret == ACT_P_DELETED) अणु
			module_put(ops->owner);
			n_i++;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			mutex_unlock(&idrinfo->lock);
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण
	mutex_unlock(&idrinfo->lock);

	अगर (nla_put_u32(skb, TCA_FCNT, n_i))
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);

	वापस n_i;
nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस ret;
पूर्ण

पूर्णांक tcf_generic_walker(काष्ठा tc_action_net *tn, काष्ठा sk_buff *skb,
		       काष्ठा netlink_callback *cb, पूर्णांक type,
		       स्थिर काष्ठा tc_action_ops *ops,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_idrinfo *idrinfo = tn->idrinfo;

	अगर (type == RTM_DELACTION) अणु
		वापस tcf_del_walker(idrinfo, skb, ops);
	पूर्ण अन्यथा अगर (type == RTM_GETACTION) अणु
		वापस tcf_dump_walker(idrinfo, skb, cb);
	पूर्ण अन्यथा अणु
		WARN(1, "tcf_generic_walker: unknown command %d\n", type);
		NL_SET_ERR_MSG(extack, "tcf_generic_walker: unknown command");
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcf_generic_walker);

पूर्णांक tcf_idr_search(काष्ठा tc_action_net *tn, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tcf_idrinfo *idrinfo = tn->idrinfo;
	काष्ठा tc_action *p;

	mutex_lock(&idrinfo->lock);
	p = idr_find(&idrinfo->action_idr, index);
	अगर (IS_ERR(p))
		p = शून्य;
	अन्यथा अगर (p)
		refcount_inc(&p->tcfa_refcnt);
	mutex_unlock(&idrinfo->lock);

	अगर (p) अणु
		*a = p;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(tcf_idr_search);

अटल पूर्णांक tcf_idr_delete_index(काष्ठा tcf_idrinfo *idrinfo, u32 index)
अणु
	काष्ठा tc_action *p;
	पूर्णांक ret = 0;

	mutex_lock(&idrinfo->lock);
	p = idr_find(&idrinfo->action_idr, index);
	अगर (!p) अणु
		mutex_unlock(&idrinfo->lock);
		वापस -ENOENT;
	पूर्ण

	अगर (!atomic_पढ़ो(&p->tcfa_bindcnt)) अणु
		अगर (refcount_dec_and_test(&p->tcfa_refcnt)) अणु
			काष्ठा module *owner = p->ops->owner;

			WARN_ON(p != idr_हटाओ(&idrinfo->action_idr,
						p->tcfa_index));
			mutex_unlock(&idrinfo->lock);

			tcf_action_cleanup(p);
			module_put(owner);
			वापस 0;
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EPERM;
	पूर्ण

	mutex_unlock(&idrinfo->lock);
	वापस ret;
पूर्ण

पूर्णांक tcf_idr_create(काष्ठा tc_action_net *tn, u32 index, काष्ठा nlattr *est,
		   काष्ठा tc_action **a, स्थिर काष्ठा tc_action_ops *ops,
		   पूर्णांक bind, bool cpustats, u32 flags)
अणु
	काष्ठा tc_action *p = kzalloc(ops->size, GFP_KERNEL);
	काष्ठा tcf_idrinfo *idrinfo = tn->idrinfo;
	पूर्णांक err = -ENOMEM;

	अगर (unlikely(!p))
		वापस -ENOMEM;
	refcount_set(&p->tcfa_refcnt, 1);
	अगर (bind)
		atomic_set(&p->tcfa_bindcnt, 1);

	अगर (cpustats) अणु
		p->cpu_bstats = netdev_alloc_pcpu_stats(काष्ठा gnet_stats_basic_cpu);
		अगर (!p->cpu_bstats)
			जाओ err1;
		p->cpu_bstats_hw = netdev_alloc_pcpu_stats(काष्ठा gnet_stats_basic_cpu);
		अगर (!p->cpu_bstats_hw)
			जाओ err2;
		p->cpu_qstats = alloc_percpu(काष्ठा gnet_stats_queue);
		अगर (!p->cpu_qstats)
			जाओ err3;
	पूर्ण
	spin_lock_init(&p->tcfa_lock);
	p->tcfa_index = index;
	p->tcfa_पंचांग.install = jअगरfies;
	p->tcfa_पंचांग.lastuse = jअगरfies;
	p->tcfa_पंचांग.firstuse = 0;
	p->tcfa_flags = flags;
	अगर (est) अणु
		err = gen_new_estimator(&p->tcfa_bstats, p->cpu_bstats,
					&p->tcfa_rate_est,
					&p->tcfa_lock, शून्य, est);
		अगर (err)
			जाओ err4;
	पूर्ण

	p->idrinfo = idrinfo;
	__module_get(ops->owner);
	p->ops = ops;
	*a = p;
	वापस 0;
err4:
	मुक्त_percpu(p->cpu_qstats);
err3:
	मुक्त_percpu(p->cpu_bstats_hw);
err2:
	मुक्त_percpu(p->cpu_bstats);
err1:
	kमुक्त(p);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcf_idr_create);

पूर्णांक tcf_idr_create_from_flags(काष्ठा tc_action_net *tn, u32 index,
			      काष्ठा nlattr *est, काष्ठा tc_action **a,
			      स्थिर काष्ठा tc_action_ops *ops, पूर्णांक bind,
			      u32 flags)
अणु
	/* Set cpustats according to actions flags. */
	वापस tcf_idr_create(tn, index, est, a, ops, bind,
			      !(flags & TCA_ACT_FLAGS_NO_PERCPU_STATS), flags);
पूर्ण
EXPORT_SYMBOL(tcf_idr_create_from_flags);

/* Cleanup idr index that was allocated but not initialized. */

व्योम tcf_idr_cleanup(काष्ठा tc_action_net *tn, u32 index)
अणु
	काष्ठा tcf_idrinfo *idrinfo = tn->idrinfo;

	mutex_lock(&idrinfo->lock);
	/* Remove ERR_PTR(-EBUSY) allocated by tcf_idr_check_alloc */
	WARN_ON(!IS_ERR(idr_हटाओ(&idrinfo->action_idr, index)));
	mutex_unlock(&idrinfo->lock);
पूर्ण
EXPORT_SYMBOL(tcf_idr_cleanup);

/* Check अगर action with specअगरied index exists. If actions is found, increments
 * its reference and bind counters, and वापस 1. Otherwise insert temporary
 * error poपूर्णांकer (to prevent concurrent users from inserting actions with same
 * index) and वापस 0.
 */

पूर्णांक tcf_idr_check_alloc(काष्ठा tc_action_net *tn, u32 *index,
			काष्ठा tc_action **a, पूर्णांक bind)
अणु
	काष्ठा tcf_idrinfo *idrinfo = tn->idrinfo;
	काष्ठा tc_action *p;
	पूर्णांक ret;

again:
	mutex_lock(&idrinfo->lock);
	अगर (*index) अणु
		p = idr_find(&idrinfo->action_idr, *index);
		अगर (IS_ERR(p)) अणु
			/* This means that another process allocated
			 * index but did not assign the poपूर्णांकer yet.
			 */
			mutex_unlock(&idrinfo->lock);
			जाओ again;
		पूर्ण

		अगर (p) अणु
			refcount_inc(&p->tcfa_refcnt);
			अगर (bind)
				atomic_inc(&p->tcfa_bindcnt);
			*a = p;
			ret = 1;
		पूर्ण अन्यथा अणु
			*a = शून्य;
			ret = idr_alloc_u32(&idrinfo->action_idr, शून्य, index,
					    *index, GFP_KERNEL);
			अगर (!ret)
				idr_replace(&idrinfo->action_idr,
					    ERR_PTR(-EBUSY), *index);
		पूर्ण
	पूर्ण अन्यथा अणु
		*index = 1;
		*a = शून्य;
		ret = idr_alloc_u32(&idrinfo->action_idr, शून्य, index,
				    अच_पूर्णांक_उच्च, GFP_KERNEL);
		अगर (!ret)
			idr_replace(&idrinfo->action_idr, ERR_PTR(-EBUSY),
				    *index);
	पूर्ण
	mutex_unlock(&idrinfo->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcf_idr_check_alloc);

व्योम tcf_idrinfo_destroy(स्थिर काष्ठा tc_action_ops *ops,
			 काष्ठा tcf_idrinfo *idrinfo)
अणु
	काष्ठा idr *idr = &idrinfo->action_idr;
	काष्ठा tc_action *p;
	पूर्णांक ret;
	अचिन्हित दीर्घ id = 1;
	अचिन्हित दीर्घ पंचांगp;

	idr_क्रम_each_entry_ul(idr, p, पंचांगp, id) अणु
		ret = __tcf_idr_release(p, false, true);
		अगर (ret == ACT_P_DELETED)
			module_put(ops->owner);
		अन्यथा अगर (ret < 0)
			वापस;
	पूर्ण
	idr_destroy(&idrinfo->action_idr);
पूर्ण
EXPORT_SYMBOL(tcf_idrinfo_destroy);

अटल LIST_HEAD(act_base);
अटल DEFINE_RWLOCK(act_mod_lock);

पूर्णांक tcf_रेजिस्टर_action(काष्ठा tc_action_ops *act,
			काष्ठा pernet_operations *ops)
अणु
	काष्ठा tc_action_ops *a;
	पूर्णांक ret;

	अगर (!act->act || !act->dump || !act->init || !act->walk || !act->lookup)
		वापस -EINVAL;

	/* We have to रेजिस्टर pernet ops beक्रमe making the action ops visible,
	 * otherwise tcf_action_init_1() could get a partially initialized
	 * netns.
	 */
	ret = रेजिस्टर_pernet_subsys(ops);
	अगर (ret)
		वापस ret;

	ग_लिखो_lock(&act_mod_lock);
	list_क्रम_each_entry(a, &act_base, head) अणु
		अगर (act->id == a->id || (म_भेद(act->kind, a->kind) == 0)) अणु
			ग_लिखो_unlock(&act_mod_lock);
			unरेजिस्टर_pernet_subsys(ops);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	list_add_tail(&act->head, &act_base);
	ग_लिखो_unlock(&act_mod_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcf_रेजिस्टर_action);

पूर्णांक tcf_unरेजिस्टर_action(काष्ठा tc_action_ops *act,
			  काष्ठा pernet_operations *ops)
अणु
	काष्ठा tc_action_ops *a;
	पूर्णांक err = -ENOENT;

	ग_लिखो_lock(&act_mod_lock);
	list_क्रम_each_entry(a, &act_base, head) अणु
		अगर (a == act) अणु
			list_del(&act->head);
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&act_mod_lock);
	अगर (!err)
		unरेजिस्टर_pernet_subsys(ops);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcf_unरेजिस्टर_action);

/* lookup by name */
अटल काष्ठा tc_action_ops *tc_lookup_action_n(अक्षर *kind)
अणु
	काष्ठा tc_action_ops *a, *res = शून्य;

	अगर (kind) अणु
		पढ़ो_lock(&act_mod_lock);
		list_क्रम_each_entry(a, &act_base, head) अणु
			अगर (म_भेद(kind, a->kind) == 0) अणु
				अगर (try_module_get(a->owner))
					res = a;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&act_mod_lock);
	पूर्ण
	वापस res;
पूर्ण

/* lookup by nlattr */
अटल काष्ठा tc_action_ops *tc_lookup_action(काष्ठा nlattr *kind)
अणु
	काष्ठा tc_action_ops *a, *res = शून्य;

	अगर (kind) अणु
		पढ़ो_lock(&act_mod_lock);
		list_क्रम_each_entry(a, &act_base, head) अणु
			अगर (nla_म_भेद(kind, a->kind) == 0) अणु
				अगर (try_module_get(a->owner))
					res = a;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&act_mod_lock);
	पूर्ण
	वापस res;
पूर्ण

/*TCA_ACT_MAX_PRIO is 32, there count up to 32 */
#घोषणा TCA_ACT_MAX_PRIO_MASK 0x1FF
पूर्णांक tcf_action_exec(काष्ठा sk_buff *skb, काष्ठा tc_action **actions,
		    पूर्णांक nr_actions, काष्ठा tcf_result *res)
अणु
	u32 jmp_prgcnt = 0;
	u32 jmp_ttl = TCA_ACT_MAX_PRIO; /*matches actions per filter */
	पूर्णांक i;
	पूर्णांक ret = TC_ACT_OK;

	अगर (skb_skip_tc_classअगरy(skb))
		वापस TC_ACT_OK;

restart_act_graph:
	क्रम (i = 0; i < nr_actions; i++) अणु
		स्थिर काष्ठा tc_action *a = actions[i];

		अगर (jmp_prgcnt > 0) अणु
			jmp_prgcnt -= 1;
			जारी;
		पूर्ण
repeat:
		ret = a->ops->act(skb, a, res);
		अगर (ret == TC_ACT_REPEAT)
			जाओ repeat;	/* we need a ttl - JHS */

		अगर (TC_ACT_EXT_CMP(ret, TC_ACT_JUMP)) अणु
			jmp_prgcnt = ret & TCA_ACT_MAX_PRIO_MASK;
			अगर (!jmp_prgcnt || (jmp_prgcnt > nr_actions)) अणु
				/* faulty opcode, stop pipeline */
				वापस TC_ACT_OK;
			पूर्ण अन्यथा अणु
				jmp_ttl -= 1;
				अगर (jmp_ttl > 0)
					जाओ restart_act_graph;
				अन्यथा /* faulty graph, stop pipeline */
					वापस TC_ACT_OK;
			पूर्ण
		पूर्ण अन्यथा अगर (TC_ACT_EXT_CMP(ret, TC_ACT_GOTO_CHAIN)) अणु
			अगर (unlikely(!rcu_access_poपूर्णांकer(a->जाओ_chain))) अणु
				net_warn_ratelimited("can't go to NULL chain!\n");
				वापस TC_ACT_SHOT;
			पूर्ण
			tcf_action_जाओ_chain_exec(a, res);
		पूर्ण

		अगर (ret != TC_ACT_PIPE)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcf_action_exec);

पूर्णांक tcf_action_destroy(काष्ठा tc_action *actions[], पूर्णांक bind)
अणु
	स्थिर काष्ठा tc_action_ops *ops;
	काष्ठा tc_action *a;
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < TCA_ACT_MAX_PRIO && actions[i]; i++) अणु
		a = actions[i];
		actions[i] = शून्य;
		ops = a->ops;
		ret = __tcf_idr_release(a, bind, true);
		अगर (ret == ACT_P_DELETED)
			module_put(ops->owner);
		अन्यथा अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tcf_action_put(काष्ठा tc_action *p)
अणु
	वापस __tcf_action_put(p, false);
पूर्ण

/* Put all actions in this array, skip those शून्य's. */
अटल व्योम tcf_action_put_many(काष्ठा tc_action *actions[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TCA_ACT_MAX_PRIO; i++) अणु
		काष्ठा tc_action *a = actions[i];
		स्थिर काष्ठा tc_action_ops *ops;

		अगर (!a)
			जारी;
		ops = a->ops;
		अगर (tcf_action_put(a))
			module_put(ops->owner);
	पूर्ण
पूर्ण

पूर्णांक
tcf_action_dump_old(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक bind, पूर्णांक ref)
अणु
	वापस a->ops->dump(skb, a, bind, ref);
पूर्ण

पूर्णांक
tcf_action_dump_1(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक bind, पूर्णांक ref)
अणु
	पूर्णांक err = -EINVAL;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा nlattr *nest;

	अगर (tcf_action_dump_terse(skb, a, false))
		जाओ nla_put_failure;

	अगर (a->hw_stats != TCA_ACT_HW_STATS_ANY &&
	    nla_put_bitfield32(skb, TCA_ACT_HW_STATS,
			       a->hw_stats, TCA_ACT_HW_STATS_ANY))
		जाओ nla_put_failure;

	अगर (a->used_hw_stats_valid &&
	    nla_put_bitfield32(skb, TCA_ACT_USED_HW_STATS,
			       a->used_hw_stats, TCA_ACT_HW_STATS_ANY))
		जाओ nla_put_failure;

	अगर (a->tcfa_flags &&
	    nla_put_bitfield32(skb, TCA_ACT_FLAGS,
			       a->tcfa_flags, a->tcfa_flags))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	err = tcf_action_dump_old(skb, a, bind, ref);
	अगर (err > 0) अणु
		nla_nest_end(skb, nest);
		वापस err;
	पूर्ण

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(tcf_action_dump_1);

पूर्णांक tcf_action_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *actions[],
		    पूर्णांक bind, पूर्णांक ref, bool terse)
अणु
	काष्ठा tc_action *a;
	पूर्णांक err = -EINVAL, i;
	काष्ठा nlattr *nest;

	क्रम (i = 0; i < TCA_ACT_MAX_PRIO && actions[i]; i++) अणु
		a = actions[i];
		nest = nla_nest_start_noflag(skb, i + 1);
		अगर (nest == शून्य)
			जाओ nla_put_failure;
		err = terse ? tcf_action_dump_terse(skb, a, false) :
			tcf_action_dump_1(skb, a, bind, ref);
		अगर (err < 0)
			जाओ errout;
		nla_nest_end(skb, nest);
	पूर्ण

	वापस 0;

nla_put_failure:
	err = -EINVAL;
errout:
	nla_nest_cancel(skb, nest);
	वापस err;
पूर्ण

अटल काष्ठा tc_cookie *nla_memdup_cookie(काष्ठा nlattr **tb)
अणु
	काष्ठा tc_cookie *c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस शून्य;

	c->data = nla_memdup(tb[TCA_ACT_COOKIE], GFP_KERNEL);
	अगर (!c->data) अणु
		kमुक्त(c);
		वापस शून्य;
	पूर्ण
	c->len = nla_len(tb[TCA_ACT_COOKIE]);

	वापस c;
पूर्ण

अटल u8 tcf_action_hw_stats_get(काष्ठा nlattr *hw_stats_attr)
अणु
	काष्ठा nla_bitfield32 hw_stats_bf;

	/* If the user did not pass the attr, that means he करोes
	 * not care about the type. Return "any" in that हाल
	 * which is setting on all supported types.
	 */
	अगर (!hw_stats_attr)
		वापस TCA_ACT_HW_STATS_ANY;
	hw_stats_bf = nla_get_bitfield32(hw_stats_attr);
	वापस hw_stats_bf.value;
पूर्ण

अटल स्थिर काष्ठा nla_policy tcf_action_policy[TCA_ACT_MAX + 1] = अणु
	[TCA_ACT_KIND]		= अणु .type = NLA_STRING पूर्ण,
	[TCA_ACT_INDEX]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_ACT_COOKIE]	= अणु .type = NLA_BINARY,
				    .len = TC_COOKIE_MAX_SIZE पूर्ण,
	[TCA_ACT_OPTIONS]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_ACT_FLAGS]		= NLA_POLICY_BITFIELD32(TCA_ACT_FLAGS_NO_PERCPU_STATS),
	[TCA_ACT_HW_STATS]	= NLA_POLICY_BITFIELD32(TCA_ACT_HW_STATS_ANY),
पूर्ण;

व्योम tcf_idr_insert_many(काष्ठा tc_action *actions[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TCA_ACT_MAX_PRIO; i++) अणु
		काष्ठा tc_action *a = actions[i];
		काष्ठा tcf_idrinfo *idrinfo;

		अगर (!a)
			जारी;
		idrinfo = a->idrinfo;
		mutex_lock(&idrinfo->lock);
		/* Replace ERR_PTR(-EBUSY) allocated by tcf_idr_check_alloc अगर
		 * it is just created, otherwise this is just a nop.
		 */
		idr_replace(&idrinfo->action_idr, a, a->tcfa_index);
		mutex_unlock(&idrinfo->lock);
	पूर्ण
पूर्ण

काष्ठा tc_action_ops *tc_action_load_ops(अक्षर *name, काष्ठा nlattr *nla,
					 bool rtnl_held,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_ACT_MAX + 1];
	काष्ठा tc_action_ops *a_o;
	अक्षर act_name[IFNAMSIZ];
	काष्ठा nlattr *kind;
	पूर्णांक err;

	अगर (name == शून्य) अणु
		err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX, nla,
						  tcf_action_policy, extack);
		अगर (err < 0)
			वापस ERR_PTR(err);
		err = -EINVAL;
		kind = tb[TCA_ACT_KIND];
		अगर (!kind) अणु
			NL_SET_ERR_MSG(extack, "TC action kind must be specified");
			वापस ERR_PTR(err);
		पूर्ण
		अगर (nla_strscpy(act_name, kind, IFNAMSIZ) < 0) अणु
			NL_SET_ERR_MSG(extack, "TC action name too long");
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (strlcpy(act_name, name, IFNAMSIZ) >= IFNAMSIZ) अणु
			NL_SET_ERR_MSG(extack, "TC action name too long");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	a_o = tc_lookup_action_n(act_name);
	अगर (a_o == शून्य) अणु
#अगर_घोषित CONFIG_MODULES
		अगर (rtnl_held)
			rtnl_unlock();
		request_module("act_%s", act_name);
		अगर (rtnl_held)
			rtnl_lock();

		a_o = tc_lookup_action_n(act_name);

		/* We dropped the RTNL semaphore in order to
		 * perक्रमm the module load.  So, even अगर we
		 * succeeded in loading the module we have to
		 * tell the caller to replay the request.  We
		 * indicate this using -EAGAIN.
		 */
		अगर (a_o != शून्य) अणु
			module_put(a_o->owner);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
#पूर्ण_अगर
		NL_SET_ERR_MSG(extack, "Failed to load TC action module");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस a_o;
पूर्ण

काष्ठा tc_action *tcf_action_init_1(काष्ठा net *net, काष्ठा tcf_proto *tp,
				    काष्ठा nlattr *nla, काष्ठा nlattr *est,
				    अक्षर *name, पूर्णांक ovr, पूर्णांक bind,
				    काष्ठा tc_action_ops *a_o, पूर्णांक *init_res,
				    bool rtnl_held,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nla_bitfield32 flags = अणु 0, 0 पूर्ण;
	u8 hw_stats = TCA_ACT_HW_STATS_ANY;
	काष्ठा nlattr *tb[TCA_ACT_MAX + 1];
	काष्ठा tc_cookie *cookie = शून्य;
	काष्ठा tc_action *a;
	पूर्णांक err;

	/* backward compatibility क्रम policer */
	अगर (name == शून्य) अणु
		err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX, nla,
						  tcf_action_policy, extack);
		अगर (err < 0)
			वापस ERR_PTR(err);
		अगर (tb[TCA_ACT_COOKIE]) अणु
			cookie = nla_memdup_cookie(tb);
			अगर (!cookie) अणु
				NL_SET_ERR_MSG(extack, "No memory to generate TC cookie");
				err = -ENOMEM;
				जाओ err_out;
			पूर्ण
		पूर्ण
		hw_stats = tcf_action_hw_stats_get(tb[TCA_ACT_HW_STATS]);
		अगर (tb[TCA_ACT_FLAGS])
			flags = nla_get_bitfield32(tb[TCA_ACT_FLAGS]);

		err = a_o->init(net, tb[TCA_ACT_OPTIONS], est, &a, ovr, bind,
				rtnl_held, tp, flags.value, extack);
	पूर्ण अन्यथा अणु
		err = a_o->init(net, nla, est, &a, ovr, bind, rtnl_held,
				tp, flags.value, extack);
	पूर्ण
	अगर (err < 0)
		जाओ err_out;
	*init_res = err;

	अगर (!name && tb[TCA_ACT_COOKIE])
		tcf_set_action_cookie(&a->act_cookie, cookie);

	अगर (!name)
		a->hw_stats = hw_stats;

	वापस a;

err_out:
	अगर (cookie) अणु
		kमुक्त(cookie->data);
		kमुक्त(cookie);
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

/* Returns numbers of initialized actions or negative error. */

पूर्णांक tcf_action_init(काष्ठा net *net, काष्ठा tcf_proto *tp, काष्ठा nlattr *nla,
		    काष्ठा nlattr *est, अक्षर *name, पूर्णांक ovr, पूर्णांक bind,
		    काष्ठा tc_action *actions[], पूर्णांक init_res[], माप_प्रकार *attr_size,
		    bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_ops *ops[TCA_ACT_MAX_PRIO] = अणुपूर्ण;
	काष्ठा nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	काष्ठा tc_action *act;
	माप_प्रकार sz = 0;
	पूर्णांक err;
	पूर्णांक i;

	err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX_PRIO, nla, शून्य,
					  extack);
	अगर (err < 0)
		वापस err;

	क्रम (i = 1; i <= TCA_ACT_MAX_PRIO && tb[i]; i++) अणु
		काष्ठा tc_action_ops *a_o;

		a_o = tc_action_load_ops(name, tb[i], rtnl_held, extack);
		अगर (IS_ERR(a_o)) अणु
			err = PTR_ERR(a_o);
			जाओ err_mod;
		पूर्ण
		ops[i - 1] = a_o;
	पूर्ण

	क्रम (i = 1; i <= TCA_ACT_MAX_PRIO && tb[i]; i++) अणु
		act = tcf_action_init_1(net, tp, tb[i], est, name, ovr, bind,
					ops[i - 1], &init_res[i - 1], rtnl_held,
					extack);
		अगर (IS_ERR(act)) अणु
			err = PTR_ERR(act);
			जाओ err;
		पूर्ण
		sz += tcf_action_fill_size(act);
		/* Start from index 0 */
		actions[i - 1] = act;
	पूर्ण

	/* We have to commit them all together, because अगर any error happened in
	 * between, we could not handle the failure gracefully.
	 */
	tcf_idr_insert_many(actions);

	*attr_size = tcf_action_full_attrs_size(sz);
	err = i - 1;
	जाओ err_mod;

err:
	tcf_action_destroy(actions, bind);
err_mod:
	क्रम (i = 0; i < TCA_ACT_MAX_PRIO; i++) अणु
		अगर (ops[i])
			module_put(ops[i]->owner);
	पूर्ण
	वापस err;
पूर्ण

व्योम tcf_action_update_stats(काष्ठा tc_action *a, u64 bytes, u64 packets,
			     u64 drops, bool hw)
अणु
	अगर (a->cpu_bstats) अणु
		_bstats_cpu_update(this_cpu_ptr(a->cpu_bstats), bytes, packets);

		this_cpu_ptr(a->cpu_qstats)->drops += drops;

		अगर (hw)
			_bstats_cpu_update(this_cpu_ptr(a->cpu_bstats_hw),
					   bytes, packets);
		वापस;
	पूर्ण

	_bstats_update(&a->tcfa_bstats, bytes, packets);
	a->tcfa_qstats.drops += drops;
	अगर (hw)
		_bstats_update(&a->tcfa_bstats_hw, bytes, packets);
पूर्ण
EXPORT_SYMBOL(tcf_action_update_stats);

पूर्णांक tcf_action_copy_stats(काष्ठा sk_buff *skb, काष्ठा tc_action *p,
			  पूर्णांक compat_mode)
अणु
	पूर्णांक err = 0;
	काष्ठा gnet_dump d;

	अगर (p == शून्य)
		जाओ errout;

	/* compat_mode being true specअगरies a call that is supposed
	 * to add additional backward compatibility statistic TLVs.
	 */
	अगर (compat_mode) अणु
		अगर (p->type == TCA_OLD_COMPAT)
			err = gnet_stats_start_copy_compat(skb, 0,
							   TCA_STATS,
							   TCA_XSTATS,
							   &p->tcfa_lock, &d,
							   TCA_PAD);
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा
		err = gnet_stats_start_copy(skb, TCA_ACT_STATS,
					    &p->tcfa_lock, &d, TCA_ACT_PAD);

	अगर (err < 0)
		जाओ errout;

	अगर (gnet_stats_copy_basic(शून्य, &d, p->cpu_bstats, &p->tcfa_bstats) < 0 ||
	    gnet_stats_copy_basic_hw(शून्य, &d, p->cpu_bstats_hw,
				     &p->tcfa_bstats_hw) < 0 ||
	    gnet_stats_copy_rate_est(&d, &p->tcfa_rate_est) < 0 ||
	    gnet_stats_copy_queue(&d, p->cpu_qstats,
				  &p->tcfa_qstats,
				  p->tcfa_qstats.qlen) < 0)
		जाओ errout;

	अगर (gnet_stats_finish_copy(&d) < 0)
		जाओ errout;

	वापस 0;

errout:
	वापस -1;
पूर्ण

अटल पूर्णांक tca_get_fill(काष्ठा sk_buff *skb, काष्ठा tc_action *actions[],
			u32 portid, u32 seq, u16 flags, पूर्णांक event, पूर्णांक bind,
			पूर्णांक ref)
अणु
	काष्ठा tcamsg *t;
	काष्ठा nlmsghdr *nlh;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा nlattr *nest;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*t), flags);
	अगर (!nlh)
		जाओ out_nlmsg_trim;
	t = nlmsg_data(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;

	nest = nla_nest_start_noflag(skb, TCA_ACT_TAB);
	अगर (!nest)
		जाओ out_nlmsg_trim;

	अगर (tcf_action_dump(skb, actions, bind, ref, false) < 0)
		जाओ out_nlmsg_trim;

	nla_nest_end(skb, nest);

	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	वापस skb->len;

out_nlmsg_trim:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक
tcf_get_notअगरy(काष्ठा net *net, u32 portid, काष्ठा nlmsghdr *n,
	       काष्ठा tc_action *actions[], पूर्णांक event,
	       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;
	अगर (tca_get_fill(skb, actions, portid, n->nlmsg_seq, 0, event,
			 0, 1) <= 0) अणु
		NL_SET_ERR_MSG(extack, "Failed to fill netlink attributes while adding TC action");
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	वापस rtnl_unicast(skb, net, portid);
पूर्ण

अटल काष्ठा tc_action *tcf_action_get_1(काष्ठा net *net, काष्ठा nlattr *nla,
					  काष्ठा nlmsghdr *n, u32 portid,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_ACT_MAX + 1];
	स्थिर काष्ठा tc_action_ops *ops;
	काष्ठा tc_action *a;
	पूर्णांक index;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX, nla,
					  tcf_action_policy, extack);
	अगर (err < 0)
		जाओ err_out;

	err = -EINVAL;
	अगर (tb[TCA_ACT_INDEX] == शून्य ||
	    nla_len(tb[TCA_ACT_INDEX]) < माप(index)) अणु
		NL_SET_ERR_MSG(extack, "Invalid TC action index value");
		जाओ err_out;
	पूर्ण
	index = nla_get_u32(tb[TCA_ACT_INDEX]);

	err = -EINVAL;
	ops = tc_lookup_action(tb[TCA_ACT_KIND]);
	अगर (!ops) अणु /* could happen in batch of actions */
		NL_SET_ERR_MSG(extack, "Specified TC action kind not found");
		जाओ err_out;
	पूर्ण
	err = -ENOENT;
	अगर (ops->lookup(net, &a, index) == 0) अणु
		NL_SET_ERR_MSG(extack, "TC action with specified index not found");
		जाओ err_mod;
	पूर्ण

	module_put(ops->owner);
	वापस a;

err_mod:
	module_put(ops->owner);
err_out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक tca_action_flush(काष्ठा net *net, काष्ठा nlattr *nla,
			    काष्ठा nlmsghdr *n, u32 portid,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *b;
	काष्ठा nlmsghdr *nlh;
	काष्ठा tcamsg *t;
	काष्ठा netlink_callback dcb;
	काष्ठा nlattr *nest;
	काष्ठा nlattr *tb[TCA_ACT_MAX + 1];
	स्थिर काष्ठा tc_action_ops *ops;
	काष्ठा nlattr *kind;
	पूर्णांक err = -ENOMEM;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस err;

	b = skb_tail_poपूर्णांकer(skb);

	err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX, nla,
					  tcf_action_policy, extack);
	अगर (err < 0)
		जाओ err_out;

	err = -EINVAL;
	kind = tb[TCA_ACT_KIND];
	ops = tc_lookup_action(kind);
	अगर (!ops) अणु /*some idjot trying to flush unknown action */
		NL_SET_ERR_MSG(extack, "Cannot flush unknown TC action");
		जाओ err_out;
	पूर्ण

	nlh = nlmsg_put(skb, portid, n->nlmsg_seq, RTM_DELACTION,
			माप(*t), 0);
	अगर (!nlh) अणु
		NL_SET_ERR_MSG(extack, "Failed to create TC action flush notification");
		जाओ out_module_put;
	पूर्ण
	t = nlmsg_data(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;

	nest = nla_nest_start_noflag(skb, TCA_ACT_TAB);
	अगर (!nest) अणु
		NL_SET_ERR_MSG(extack, "Failed to add new netlink message");
		जाओ out_module_put;
	पूर्ण

	err = ops->walk(net, skb, &dcb, RTM_DELACTION, ops, extack);
	अगर (err <= 0) अणु
		nla_nest_cancel(skb, nest);
		जाओ out_module_put;
	पूर्ण

	nla_nest_end(skb, nest);

	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	nlh->nlmsg_flags |= NLM_F_ROOT;
	module_put(ops->owner);
	err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	अगर (err > 0)
		वापस 0;
	अगर (err < 0)
		NL_SET_ERR_MSG(extack, "Failed to send TC action flush notification");

	वापस err;

out_module_put:
	module_put(ops->owner);
err_out:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_action_delete(काष्ठा net *net, काष्ठा tc_action *actions[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TCA_ACT_MAX_PRIO && actions[i]; i++) अणु
		काष्ठा tc_action *a = actions[i];
		स्थिर काष्ठा tc_action_ops *ops = a->ops;
		/* Actions can be deleted concurrently so we must save their
		 * type and id to search again after reference is released.
		 */
		काष्ठा tcf_idrinfo *idrinfo = a->idrinfo;
		u32 act_index = a->tcfa_index;

		actions[i] = शून्य;
		अगर (tcf_action_put(a)) अणु
			/* last reference, action was deleted concurrently */
			module_put(ops->owner);
		पूर्ण अन्यथा  अणु
			पूर्णांक ret;

			/* now करो the delete */
			ret = tcf_idr_delete_index(idrinfo, act_index);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
tcf_del_notअगरy(काष्ठा net *net, काष्ठा nlmsghdr *n, काष्ठा tc_action *actions[],
	       u32 portid, माप_प्रकार attr_size, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(attr_size <= NLMSG_GOODSIZE ? NLMSG_GOODSIZE : attr_size,
			GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tca_get_fill(skb, actions, portid, n->nlmsg_seq, 0, RTM_DELACTION,
			 0, 2) <= 0) अणु
		NL_SET_ERR_MSG(extack, "Failed to fill netlink TC action attributes");
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	/* now करो the delete */
	ret = tcf_action_delete(net, actions);
	अगर (ret < 0) अणु
		NL_SET_ERR_MSG(extack, "Failed to delete TC action");
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	ret = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	अगर (ret > 0)
		वापस 0;
	वापस ret;
पूर्ण

अटल पूर्णांक
tca_action_gd(काष्ठा net *net, काष्ठा nlattr *nla, काष्ठा nlmsghdr *n,
	      u32 portid, पूर्णांक event, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i, ret;
	काष्ठा nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	काष्ठा tc_action *act;
	माप_प्रकार attr_size = 0;
	काष्ठा tc_action *actions[TCA_ACT_MAX_PRIO] = अणुपूर्ण;

	ret = nla_parse_nested_deprecated(tb, TCA_ACT_MAX_PRIO, nla, शून्य,
					  extack);
	अगर (ret < 0)
		वापस ret;

	अगर (event == RTM_DELACTION && n->nlmsg_flags & NLM_F_ROOT) अणु
		अगर (tb[1])
			वापस tca_action_flush(net, tb[1], n, portid, extack);

		NL_SET_ERR_MSG(extack, "Invalid netlink attributes while flushing TC action");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 1; i <= TCA_ACT_MAX_PRIO && tb[i]; i++) अणु
		act = tcf_action_get_1(net, tb[i], n, portid, extack);
		अगर (IS_ERR(act)) अणु
			ret = PTR_ERR(act);
			जाओ err;
		पूर्ण
		attr_size += tcf_action_fill_size(act);
		actions[i - 1] = act;
	पूर्ण

	attr_size = tcf_action_full_attrs_size(attr_size);

	अगर (event == RTM_GETACTION)
		ret = tcf_get_notअगरy(net, portid, n, actions, event, extack);
	अन्यथा अणु /* delete */
		ret = tcf_del_notअगरy(net, n, actions, portid, attr_size, extack);
		अगर (ret)
			जाओ err;
		वापस 0;
	पूर्ण
err:
	tcf_action_put_many(actions);
	वापस ret;
पूर्ण

अटल पूर्णांक
tcf_add_notअगरy(काष्ठा net *net, काष्ठा nlmsghdr *n, काष्ठा tc_action *actions[],
	       u32 portid, माप_प्रकार attr_size, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	skb = alloc_skb(attr_size <= NLMSG_GOODSIZE ? NLMSG_GOODSIZE : attr_size,
			GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tca_get_fill(skb, actions, portid, n->nlmsg_seq, n->nlmsg_flags,
			 RTM_NEWACTION, 0, 0) <= 0) अणु
		NL_SET_ERR_MSG(extack, "Failed to fill netlink attributes while adding TC action");
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक tcf_action_add(काष्ठा net *net, काष्ठा nlattr *nla,
			  काष्ठा nlmsghdr *n, u32 portid, पूर्णांक ovr,
			  काष्ठा netlink_ext_ack *extack)
अणु
	माप_प्रकार attr_size = 0;
	पूर्णांक loop, ret, i;
	काष्ठा tc_action *actions[TCA_ACT_MAX_PRIO] = अणुपूर्ण;
	पूर्णांक init_res[TCA_ACT_MAX_PRIO] = अणुपूर्ण;

	क्रम (loop = 0; loop < 10; loop++) अणु
		ret = tcf_action_init(net, शून्य, nla, शून्य, शून्य, ovr, 0,
				      actions, init_res, &attr_size, true, extack);
		अगर (ret != -EAGAIN)
			अवरोध;
	पूर्ण

	अगर (ret < 0)
		वापस ret;
	ret = tcf_add_notअगरy(net, n, actions, portid, attr_size, extack);

	/* only put existing actions */
	क्रम (i = 0; i < TCA_ACT_MAX_PRIO; i++)
		अगर (init_res[i] == ACT_P_CREATED)
			actions[i] = शून्य;
	tcf_action_put_many(actions);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy tcaa_policy[TCA_ROOT_MAX + 1] = अणु
	[TCA_ROOT_FLAGS] = NLA_POLICY_BITFIELD32(TCA_ACT_FLAG_LARGE_DUMP_ON |
						 TCA_ACT_FLAG_TERSE_DUMP),
	[TCA_ROOT_TIME_DELTA]      = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक tc_ctl_action(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tca[TCA_ROOT_MAX + 1];
	u32 portid = NETLINK_CB(skb).portid;
	पूर्णांक ret = 0, ovr = 0;

	अगर ((n->nlmsg_type != RTM_GETACTION) &&
	    !netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	ret = nlmsg_parse_deprecated(n, माप(काष्ठा tcamsg), tca,
				     TCA_ROOT_MAX, शून्य, extack);
	अगर (ret < 0)
		वापस ret;

	अगर (tca[TCA_ACT_TAB] == शून्य) अणु
		NL_SET_ERR_MSG(extack, "Netlink action attributes missing");
		वापस -EINVAL;
	पूर्ण

	/* n->nlmsg_flags & NLM_F_CREATE */
	चयन (n->nlmsg_type) अणु
	हाल RTM_NEWACTION:
		/* we are going to assume all other flags
		 * imply create only अगर it करोesn't exist
		 * Note that CREATE | EXCL implies that
		 * but since we want aव्योम ambiguity (eg when flags
		 * is zero) then just set this
		 */
		अगर (n->nlmsg_flags & NLM_F_REPLACE)
			ovr = 1;
		ret = tcf_action_add(net, tca[TCA_ACT_TAB], n, portid, ovr,
				     extack);
		अवरोध;
	हाल RTM_DELACTION:
		ret = tca_action_gd(net, tca[TCA_ACT_TAB], n,
				    portid, RTM_DELACTION, extack);
		अवरोध;
	हाल RTM_GETACTION:
		ret = tca_action_gd(net, tca[TCA_ACT_TAB], n,
				    portid, RTM_GETACTION, extack);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा nlattr *find_dump_kind(काष्ठा nlattr **nla)
अणु
	काष्ठा nlattr *tb1, *tb2[TCA_ACT_MAX + 1];
	काष्ठा nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	काष्ठा nlattr *kind;

	tb1 = nla[TCA_ACT_TAB];
	अगर (tb1 == शून्य)
		वापस शून्य;

	अगर (nla_parse_deprecated(tb, TCA_ACT_MAX_PRIO, nla_data(tb1), NLMSG_ALIGN(nla_len(tb1)), शून्य, शून्य) < 0)
		वापस शून्य;

	अगर (tb[1] == शून्य)
		वापस शून्य;
	अगर (nla_parse_nested_deprecated(tb2, TCA_ACT_MAX, tb[1], tcf_action_policy, शून्य) < 0)
		वापस शून्य;
	kind = tb2[TCA_ACT_KIND];

	वापस kind;
पूर्ण

अटल पूर्णांक tc_dump_action(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlmsghdr *nlh;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा nlattr *nest;
	काष्ठा tc_action_ops *a_o;
	पूर्णांक ret = 0;
	काष्ठा tcamsg *t = (काष्ठा tcamsg *) nlmsg_data(cb->nlh);
	काष्ठा nlattr *tb[TCA_ROOT_MAX + 1];
	काष्ठा nlattr *count_attr = शून्य;
	अचिन्हित दीर्घ jअगरfy_since = 0;
	काष्ठा nlattr *kind = शून्य;
	काष्ठा nla_bitfield32 bf;
	u32 msecs_since = 0;
	u32 act_count = 0;

	ret = nlmsg_parse_deprecated(cb->nlh, माप(काष्ठा tcamsg), tb,
				     TCA_ROOT_MAX, tcaa_policy, cb->extack);
	अगर (ret < 0)
		वापस ret;

	kind = find_dump_kind(tb);
	अगर (kind == शून्य) अणु
		pr_info("tc_dump_action: action bad kind\n");
		वापस 0;
	पूर्ण

	a_o = tc_lookup_action(kind);
	अगर (a_o == शून्य)
		वापस 0;

	cb->args[2] = 0;
	अगर (tb[TCA_ROOT_FLAGS]) अणु
		bf = nla_get_bitfield32(tb[TCA_ROOT_FLAGS]);
		cb->args[2] = bf.value;
	पूर्ण

	अगर (tb[TCA_ROOT_TIME_DELTA]) अणु
		msecs_since = nla_get_u32(tb[TCA_ROOT_TIME_DELTA]);
	पूर्ण

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			cb->nlh->nlmsg_type, माप(*t), 0);
	अगर (!nlh)
		जाओ out_module_put;

	अगर (msecs_since)
		jअगरfy_since = jअगरfies - msecs_to_jअगरfies(msecs_since);

	t = nlmsg_data(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;
	cb->args[3] = jअगरfy_since;
	count_attr = nla_reserve(skb, TCA_ROOT_COUNT, माप(u32));
	अगर (!count_attr)
		जाओ out_module_put;

	nest = nla_nest_start_noflag(skb, TCA_ACT_TAB);
	अगर (nest == शून्य)
		जाओ out_module_put;

	ret = a_o->walk(net, skb, cb, RTM_GETACTION, a_o, शून्य);
	अगर (ret < 0)
		जाओ out_module_put;

	अगर (ret > 0) अणु
		nla_nest_end(skb, nest);
		ret = skb->len;
		act_count = cb->args[1];
		स_नकल(nla_data(count_attr), &act_count, माप(u32));
		cb->args[1] = 0;
	पूर्ण अन्यथा
		nlmsg_trim(skb, b);

	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	अगर (NETLINK_CB(cb->skb).portid && ret)
		nlh->nlmsg_flags |= NLM_F_MULTI;
	module_put(a_o->owner);
	वापस skb->len;

out_module_put:
	module_put(a_o->owner);
	nlmsg_trim(skb, b);
	वापस skb->len;
पूर्ण

अटल पूर्णांक __init tc_action_init(व्योम)
अणु
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWACTION, tc_ctl_action, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELACTION, tc_ctl_action, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETACTION, tc_ctl_action, tc_dump_action,
		      0);

	वापस 0;
पूर्ण

subsys_initcall(tc_action_init);
