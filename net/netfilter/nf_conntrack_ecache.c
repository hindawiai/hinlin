<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Event cache क्रम netfilter. */

/*
 * (C) 2005 Harald Welte <laक्रमge@gnumonks.org>
 * (C) 2005 Patrick McHardy <kaber@trash.net>
 * (C) 2005-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2005 USAGI/WIDE Project <http://www.linux-ipv6.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/err.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>

बाह्य अचिन्हित पूर्णांक nf_conntrack_net_id;

अटल DEFINE_MUTEX(nf_ct_ecache_mutex);

#घोषणा ECACHE_RETRY_WAIT (HZ/10)
#घोषणा ECACHE_STACK_ALLOC (256 / माप(व्योम *))

क्रमागत retry_state अणु
	STATE_CONGESTED,
	STATE_RESTART,
	STATE_DONE,
पूर्ण;

अटल क्रमागत retry_state ecache_work_evict_list(काष्ठा ct_pcpu *pcpu)
अणु
	काष्ठा nf_conn *refs[ECACHE_STACK_ALLOC];
	क्रमागत retry_state ret = STATE_DONE;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_node *n;
	अचिन्हित पूर्णांक evicted = 0;

	spin_lock(&pcpu->lock);

	hlist_nulls_क्रम_each_entry(h, n, &pcpu->dying, hnnode) अणु
		काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);
		काष्ठा nf_conntrack_ecache *e;

		अगर (!nf_ct_is_confirmed(ct))
			जारी;

		/* This ecache access is safe because the ct is on the
		 * pcpu dying list and we hold the spinlock -- the entry
		 * cannot be मुक्त'd until after the lock is released.
		 *
		 * This is true even अगर ct has a refcount of 0: the
		 * cpu that is about to मुक्त the entry must हटाओ it
		 * from the dying list and needs the lock to करो so.
		 */
		e = nf_ct_ecache_find(ct);
		अगर (!e || e->state != NFCT_ECACHE_DESTROY_FAIL)
			जारी;

		/* ct is in NFCT_ECACHE_DESTROY_FAIL state, this means
		 * the worker owns this entry: the ct will reमुख्य valid
		 * until the worker माला_दो its ct reference.
		 */
		अगर (nf_conntrack_event(IPCT_DESTROY, ct)) अणु
			ret = STATE_CONGESTED;
			अवरोध;
		पूर्ण

		e->state = NFCT_ECACHE_DESTROY_SENT;
		refs[evicted] = ct;

		अगर (++evicted >= ARRAY_SIZE(refs)) अणु
			ret = STATE_RESTART;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&pcpu->lock);

	/* can't _put जबतक holding lock */
	जबतक (evicted)
		nf_ct_put(refs[--evicted]);

	वापस ret;
पूर्ण

अटल व्योम ecache_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nf_conntrack_net *cnet = container_of(work, काष्ठा nf_conntrack_net, ecache_dwork.work);
	काष्ठा netns_ct *ctnet = cnet->ct_net;
	पूर्णांक cpu, delay = -1;
	काष्ठा ct_pcpu *pcpu;

	local_bh_disable();

	क्रम_each_possible_cpu(cpu) अणु
		क्रमागत retry_state ret;

		pcpu = per_cpu_ptr(ctnet->pcpu_lists, cpu);

		ret = ecache_work_evict_list(pcpu);

		चयन (ret) अणु
		हाल STATE_CONGESTED:
			delay = ECACHE_RETRY_WAIT;
			जाओ out;
		हाल STATE_RESTART:
			delay = 0;
			अवरोध;
		हाल STATE_DONE:
			अवरोध;
		पूर्ण
	पूर्ण

 out:
	local_bh_enable();

	ctnet->ecache_dwork_pending = delay > 0;
	अगर (delay >= 0)
		schedule_delayed_work(&cnet->ecache_dwork, delay);
पूर्ण

पूर्णांक nf_conntrack_evenपंचांगask_report(अचिन्हित पूर्णांक evenपंचांगask, काष्ठा nf_conn *ct,
				  u32 portid, पूर्णांक report)
अणु
	पूर्णांक ret = 0;
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_ct_event_notअगरier *notअगरy;
	काष्ठा nf_conntrack_ecache *e;

	rcu_पढ़ो_lock();
	notअगरy = rcu_dereference(net->ct.nf_conntrack_event_cb);
	अगर (!notअगरy)
		जाओ out_unlock;

	e = nf_ct_ecache_find(ct);
	अगर (!e)
		जाओ out_unlock;

	अगर (nf_ct_is_confirmed(ct)) अणु
		काष्ठा nf_ct_event item = अणु
			.ct	= ct,
			.portid	= e->portid ? e->portid : portid,
			.report = report
		पूर्ण;
		/* This is a resent of a destroy event? If so, skip missed */
		अचिन्हित दीर्घ missed = e->portid ? 0 : e->missed;

		अगर (!((evenपंचांगask | missed) & e->cपंचांगask))
			जाओ out_unlock;

		ret = notअगरy->fcn(evenपंचांगask | missed, &item);
		अगर (unlikely(ret < 0 || missed)) अणु
			spin_lock_bh(&ct->lock);
			अगर (ret < 0) अणु
				/* This is a destroy event that has been
				 * triggered by a process, we store the PORTID
				 * to include it in the retransmission.
				 */
				अगर (evenपंचांगask & (1 << IPCT_DESTROY)) अणु
					अगर (e->portid == 0 && portid != 0)
						e->portid = portid;
					e->state = NFCT_ECACHE_DESTROY_FAIL;
				पूर्ण अन्यथा अणु
					e->missed |= evenपंचांगask;
				पूर्ण
			पूर्ण अन्यथा अणु
				e->missed &= ~missed;
			पूर्ण
			spin_unlock_bh(&ct->lock);
		पूर्ण
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_evenपंचांगask_report);

/* deliver cached events and clear cache entry - must be called with locally
 * disabled softirqs */
व्योम nf_ct_deliver_cached_events(काष्ठा nf_conn *ct)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	अचिन्हित दीर्घ events, missed;
	काष्ठा nf_ct_event_notअगरier *notअगरy;
	काष्ठा nf_conntrack_ecache *e;
	काष्ठा nf_ct_event item;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	notअगरy = rcu_dereference(net->ct.nf_conntrack_event_cb);
	अगर (notअगरy == शून्य)
		जाओ out_unlock;

	अगर (!nf_ct_is_confirmed(ct) || nf_ct_is_dying(ct))
		जाओ out_unlock;

	e = nf_ct_ecache_find(ct);
	अगर (e == शून्य)
		जाओ out_unlock;

	events = xchg(&e->cache, 0);

	/* We make a copy of the missed event cache without taking
	 * the lock, thus we may send missed events twice. However,
	 * this करोes not harm and it happens very rarely. */
	missed = e->missed;

	अगर (!((events | missed) & e->cपंचांगask))
		जाओ out_unlock;

	item.ct = ct;
	item.portid = 0;
	item.report = 0;

	ret = notअगरy->fcn(events | missed, &item);

	अगर (likely(ret == 0 && !missed))
		जाओ out_unlock;

	spin_lock_bh(&ct->lock);
	अगर (ret < 0)
		e->missed |= events;
	अन्यथा
		e->missed &= ~missed;
	spin_unlock_bh(&ct->lock);

out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_deliver_cached_events);

व्योम nf_ct_expect_event_report(क्रमागत ip_conntrack_expect_events event,
			       काष्ठा nf_conntrack_expect *exp,
			       u32 portid, पूर्णांक report)

अणु
	काष्ठा net *net = nf_ct_exp_net(exp);
	काष्ठा nf_exp_event_notअगरier *notअगरy;
	काष्ठा nf_conntrack_ecache *e;

	rcu_पढ़ो_lock();
	notअगरy = rcu_dereference(net->ct.nf_expect_event_cb);
	अगर (!notअगरy)
		जाओ out_unlock;

	e = nf_ct_ecache_find(exp->master);
	अगर (!e)
		जाओ out_unlock;

	अगर (e->expmask & (1 << event)) अणु
		काष्ठा nf_exp_event item = अणु
			.exp	= exp,
			.portid	= portid,
			.report = report
		पूर्ण;
		notअगरy->fcn(1 << event, &item);
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक nf_conntrack_रेजिस्टर_notअगरier(काष्ठा net *net,
				   काष्ठा nf_ct_event_notअगरier *new)
अणु
	पूर्णांक ret;
	काष्ठा nf_ct_event_notअगरier *notअगरy;

	mutex_lock(&nf_ct_ecache_mutex);
	notअगरy = rcu_dereference_रक्षित(net->ct.nf_conntrack_event_cb,
					   lockdep_is_held(&nf_ct_ecache_mutex));
	अगर (notअगरy != शून्य) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	rcu_assign_poपूर्णांकer(net->ct.nf_conntrack_event_cb, new);
	ret = 0;

out_unlock:
	mutex_unlock(&nf_ct_ecache_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_रेजिस्टर_notअगरier);

व्योम nf_conntrack_unरेजिस्टर_notअगरier(काष्ठा net *net,
				      काष्ठा nf_ct_event_notअगरier *new)
अणु
	काष्ठा nf_ct_event_notअगरier *notअगरy;

	mutex_lock(&nf_ct_ecache_mutex);
	notअगरy = rcu_dereference_रक्षित(net->ct.nf_conntrack_event_cb,
					   lockdep_is_held(&nf_ct_ecache_mutex));
	BUG_ON(notअगरy != new);
	RCU_INIT_POINTER(net->ct.nf_conntrack_event_cb, शून्य);
	mutex_unlock(&nf_ct_ecache_mutex);
	/* synchronize_rcu() is called from ctnetlink_निकास. */
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_unरेजिस्टर_notअगरier);

पूर्णांक nf_ct_expect_रेजिस्टर_notअगरier(काष्ठा net *net,
				   काष्ठा nf_exp_event_notअगरier *new)
अणु
	पूर्णांक ret;
	काष्ठा nf_exp_event_notअगरier *notअगरy;

	mutex_lock(&nf_ct_ecache_mutex);
	notअगरy = rcu_dereference_रक्षित(net->ct.nf_expect_event_cb,
					   lockdep_is_held(&nf_ct_ecache_mutex));
	अगर (notअगरy != शून्य) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	rcu_assign_poपूर्णांकer(net->ct.nf_expect_event_cb, new);
	ret = 0;

out_unlock:
	mutex_unlock(&nf_ct_ecache_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_रेजिस्टर_notअगरier);

व्योम nf_ct_expect_unरेजिस्टर_notअगरier(काष्ठा net *net,
				      काष्ठा nf_exp_event_notअगरier *new)
अणु
	काष्ठा nf_exp_event_notअगरier *notअगरy;

	mutex_lock(&nf_ct_ecache_mutex);
	notअगरy = rcu_dereference_रक्षित(net->ct.nf_expect_event_cb,
					   lockdep_is_held(&nf_ct_ecache_mutex));
	BUG_ON(notअगरy != new);
	RCU_INIT_POINTER(net->ct.nf_expect_event_cb, शून्य);
	mutex_unlock(&nf_ct_ecache_mutex);
	/* synchronize_rcu() is called from ctnetlink_निकास. */
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_expect_unरेजिस्टर_notअगरier);

व्योम nf_conntrack_ecache_work(काष्ठा net *net, क्रमागत nf_ct_ecache_state state)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	अगर (state == NFCT_ECACHE_DESTROY_FAIL &&
	    !delayed_work_pending(&cnet->ecache_dwork)) अणु
		schedule_delayed_work(&cnet->ecache_dwork, HZ);
		net->ct.ecache_dwork_pending = true;
	पूर्ण अन्यथा अगर (state == NFCT_ECACHE_DESTROY_SENT) अणु
		net->ct.ecache_dwork_pending = false;
		mod_delayed_work(प्रणाली_wq, &cnet->ecache_dwork, 0);
	पूर्ण
पूर्ण

#घोषणा NF_CT_EVENTS_DEFAULT 1
अटल पूर्णांक nf_ct_events __पढ़ो_mostly = NF_CT_EVENTS_DEFAULT;

अटल स्थिर काष्ठा nf_ct_ext_type event_extend = अणु
	.len	= माप(काष्ठा nf_conntrack_ecache),
	.align	= __alignof__(काष्ठा nf_conntrack_ecache),
	.id	= NF_CT_EXT_ECACHE,
पूर्ण;

व्योम nf_conntrack_ecache_pernet_init(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	net->ct.sysctl_events = nf_ct_events;
	cnet->ct_net = &net->ct;
	INIT_DELAYED_WORK(&cnet->ecache_dwork, ecache_work);
पूर्ण

व्योम nf_conntrack_ecache_pernet_fini(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);

	cancel_delayed_work_sync(&cnet->ecache_dwork);
पूर्ण

पूर्णांक nf_conntrack_ecache_init(व्योम)
अणु
	पूर्णांक ret = nf_ct_extend_रेजिस्टर(&event_extend);
	अगर (ret < 0)
		pr_err("Unable to register event extension\n");

	BUILD_BUG_ON(__IPCT_MAX >= 16);	/* cपंचांगask, missed use u16 */

	वापस ret;
पूर्ण

व्योम nf_conntrack_ecache_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&event_extend);
पूर्ण
