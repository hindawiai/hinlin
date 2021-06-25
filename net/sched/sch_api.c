<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_api.c	Packet scheduler API.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Fixes:
 *
 * Rani Assaf <rani@magic.metawire.com> :980802: JIFFIES and CPU घड़ी sources are repaired.
 * Eduarकरो J. Blanco <ejbs@netद_असल.com.uy> :990222: kmod support
 * Jamal Hadi Salim <hadi@nortelnetworks.com>: 990601: ingress support
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/hashtable.h>

#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

#समावेश <trace/events/qdisc.h>

/*

   Short review.
   -------------

   This file consists of two पूर्णांकerrelated parts:

   1. queueing disciplines manager frontend.
   2. traffic classes manager frontend.

   Generally, queueing discipline ("qdisc") is a black box,
   which is able to enqueue packets and to dequeue them (when
   device is पढ़ोy to send something) in order and at बार
   determined by algorithm hidden in it.

   qdisc's are भागided to two categories:
   - "queues", which have no पूर्णांकernal काष्ठाure visible from outside.
   - "schedulers", which split all the packets to "traffic classes",
     using "packet classifiers" (look at cls_api.c)

   In turn, classes may have child qdiscs (as rule, queues)
   attached to them etc. etc. etc.

   The goal of the routines in this file is to translate
   inक्रमmation supplied by user in the क्रमm of handles
   to more पूर्णांकelligible क्रम kernel क्रमm, to make some sanity
   checks and part of work, which is common to all qdiscs
   and to provide rtnetlink notअगरications.

   All real पूर्णांकelligent work is करोne inside qdisc modules.



   Every discipline has two major routines: enqueue and dequeue.

   ---dequeue

   dequeue usually वापसs a skb to send. It is allowed to वापस शून्य,
   but it करोes not mean that queue is empty, it just means that
   discipline करोes not want to send anything this समय.
   Queue is really empty अगर q->q.qlen == 0.
   For complicated disciplines with multiple queues q->q is not
   real packet queue, but however q->q.qlen must be valid.

   ---enqueue

   enqueue वापसs 0, अगर packet was enqueued successfully.
   If packet (this one or another one) was dropped, it वापसs
   not zero error code.
   NET_XMIT_DROP 	- this packet dropped
     Expected action: करो not backoff, but रुको until queue will clear.
   NET_XMIT_CN	 	- probably this packet enqueued, but another one dropped.
     Expected action: backoff or ignore

   Auxiliary routines:

   ---peek

   like dequeue but without removing a packet from the queue

   ---reset

   वापसs qdisc to initial state: purge all buffers, clear all
   समयrs, counters (except क्रम statistics) etc.

   ---init

   initializes newly created qdisc.

   ---destroy

   destroys resources allocated by init and during lअगरeसमय of qdisc.

   ---change

   changes qdisc parameters.
 */

/* Protects list of रेजिस्टरed TC modules. It is pure SMP lock. */
अटल DEFINE_RWLOCK(qdisc_mod_lock);


/************************************************
 *	Queueing disciplines manipulation.	*
 ************************************************/


/* The list of all installed queueing disciplines. */

अटल काष्ठा Qdisc_ops *qdisc_base;

/* Register/unरेजिस्टर queueing discipline */

पूर्णांक रेजिस्टर_qdisc(काष्ठा Qdisc_ops *qops)
अणु
	काष्ठा Qdisc_ops *q, **qp;
	पूर्णांक rc = -EEXIST;

	ग_लिखो_lock(&qdisc_mod_lock);
	क्रम (qp = &qdisc_base; (q = *qp) != शून्य; qp = &q->next)
		अगर (!म_भेद(qops->id, q->id))
			जाओ out;

	अगर (qops->enqueue == शून्य)
		qops->enqueue = noop_qdisc_ops.enqueue;
	अगर (qops->peek == शून्य) अणु
		अगर (qops->dequeue == शून्य)
			qops->peek = noop_qdisc_ops.peek;
		अन्यथा
			जाओ out_einval;
	पूर्ण
	अगर (qops->dequeue == शून्य)
		qops->dequeue = noop_qdisc_ops.dequeue;

	अगर (qops->cl_ops) अणु
		स्थिर काष्ठा Qdisc_class_ops *cops = qops->cl_ops;

		अगर (!(cops->find && cops->walk && cops->leaf))
			जाओ out_einval;

		अगर (cops->tcf_block && !(cops->bind_tcf && cops->unbind_tcf))
			जाओ out_einval;
	पूर्ण

	qops->next = शून्य;
	*qp = qops;
	rc = 0;
out:
	ग_लिखो_unlock(&qdisc_mod_lock);
	वापस rc;

out_einval:
	rc = -EINVAL;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_qdisc);

पूर्णांक unरेजिस्टर_qdisc(काष्ठा Qdisc_ops *qops)
अणु
	काष्ठा Qdisc_ops *q, **qp;
	पूर्णांक err = -ENOENT;

	ग_लिखो_lock(&qdisc_mod_lock);
	क्रम (qp = &qdisc_base; (q = *qp) != शून्य; qp = &q->next)
		अगर (q == qops)
			अवरोध;
	अगर (q) अणु
		*qp = q->next;
		q->next = शून्य;
		err = 0;
	पूर्ण
	ग_लिखो_unlock(&qdisc_mod_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_qdisc);

/* Get शेष qdisc अगर not otherwise specअगरied */
व्योम qdisc_get_शेष(अक्षर *name, माप_प्रकार len)
अणु
	पढ़ो_lock(&qdisc_mod_lock);
	strlcpy(name, शेष_qdisc_ops->id, len);
	पढ़ो_unlock(&qdisc_mod_lock);
पूर्ण

अटल काष्ठा Qdisc_ops *qdisc_lookup_शेष(स्थिर अक्षर *name)
अणु
	काष्ठा Qdisc_ops *q = शून्य;

	क्रम (q = qdisc_base; q; q = q->next) अणु
		अगर (!म_भेद(name, q->id)) अणु
			अगर (!try_module_get(q->owner))
				q = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस q;
पूर्ण

/* Set new शेष qdisc to use */
पूर्णांक qdisc_set_शेष(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा Qdisc_ops *ops;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	ग_लिखो_lock(&qdisc_mod_lock);
	ops = qdisc_lookup_शेष(name);
	अगर (!ops) अणु
		/* Not found, drop lock and try to load module */
		ग_लिखो_unlock(&qdisc_mod_lock);
		request_module("sch_%s", name);
		ग_लिखो_lock(&qdisc_mod_lock);

		ops = qdisc_lookup_शेष(name);
	पूर्ण

	अगर (ops) अणु
		/* Set new शेष */
		module_put(शेष_qdisc_ops->owner);
		शेष_qdisc_ops = ops;
	पूर्ण
	ग_लिखो_unlock(&qdisc_mod_lock);

	वापस ops ? 0 : -ENOENT;
पूर्ण

#अगर_घोषित CONFIG_NET_SCH_DEFAULT
/* Set शेष value from kernel config */
अटल पूर्णांक __init sch_शेष_qdisc(व्योम)
अणु
	वापस qdisc_set_शेष(CONFIG_DEFAULT_NET_SCH);
पूर्ण
late_initcall(sch_शेष_qdisc);
#पूर्ण_अगर

/* We know handle. Find qdisc among all qdisc's attached to device
 * (root qdisc, all its children, children of children etc.)
 * Note: caller either uses rtnl or rcu_पढ़ो_lock()
 */

अटल काष्ठा Qdisc *qdisc_match_from_root(काष्ठा Qdisc *root, u32 handle)
अणु
	काष्ठा Qdisc *q;

	अगर (!qdisc_dev(root))
		वापस (root->handle == handle ? root : शून्य);

	अगर (!(root->flags & TCQ_F_BUILTIN) &&
	    root->handle == handle)
		वापस root;

	hash_क्रम_each_possible_rcu(qdisc_dev(root)->qdisc_hash, q, hash, handle,
				   lockdep_rtnl_is_held()) अणु
		अगर (q->handle == handle)
			वापस q;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम qdisc_hash_add(काष्ठा Qdisc *q, bool invisible)
अणु
	अगर ((q->parent != TC_H_ROOT) && !(q->flags & TCQ_F_INGRESS)) अणु
		ASSERT_RTNL();
		hash_add_rcu(qdisc_dev(q)->qdisc_hash, &q->hash, q->handle);
		अगर (invisible)
			q->flags |= TCQ_F_INVISIBLE;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qdisc_hash_add);

व्योम qdisc_hash_del(काष्ठा Qdisc *q)
अणु
	अगर ((q->parent != TC_H_ROOT) && !(q->flags & TCQ_F_INGRESS)) अणु
		ASSERT_RTNL();
		hash_del_rcu(&q->hash);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qdisc_hash_del);

काष्ठा Qdisc *qdisc_lookup(काष्ठा net_device *dev, u32 handle)
अणु
	काष्ठा Qdisc *q;

	अगर (!handle)
		वापस शून्य;
	q = qdisc_match_from_root(dev->qdisc, handle);
	अगर (q)
		जाओ out;

	अगर (dev_ingress_queue(dev))
		q = qdisc_match_from_root(
			dev_ingress_queue(dev)->qdisc_sleeping,
			handle);
out:
	वापस q;
पूर्ण

काष्ठा Qdisc *qdisc_lookup_rcu(काष्ठा net_device *dev, u32 handle)
अणु
	काष्ठा netdev_queue *nq;
	काष्ठा Qdisc *q;

	अगर (!handle)
		वापस शून्य;
	q = qdisc_match_from_root(dev->qdisc, handle);
	अगर (q)
		जाओ out;

	nq = dev_ingress_queue_rcu(dev);
	अगर (nq)
		q = qdisc_match_from_root(nq->qdisc_sleeping, handle);
out:
	वापस q;
पूर्ण

अटल काष्ठा Qdisc *qdisc_leaf(काष्ठा Qdisc *p, u32 classid)
अणु
	अचिन्हित दीर्घ cl;
	स्थिर काष्ठा Qdisc_class_ops *cops = p->ops->cl_ops;

	अगर (cops == शून्य)
		वापस शून्य;
	cl = cops->find(p, classid);

	अगर (cl == 0)
		वापस शून्य;
	वापस cops->leaf(p, cl);
पूर्ण

/* Find queueing discipline by name */

अटल काष्ठा Qdisc_ops *qdisc_lookup_ops(काष्ठा nlattr *kind)
अणु
	काष्ठा Qdisc_ops *q = शून्य;

	अगर (kind) अणु
		पढ़ो_lock(&qdisc_mod_lock);
		क्रम (q = qdisc_base; q; q = q->next) अणु
			अगर (nla_म_भेद(kind, q->id) == 0) अणु
				अगर (!try_module_get(q->owner))
					q = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&qdisc_mod_lock);
	पूर्ण
	वापस q;
पूर्ण

/* The linklayer setting were not transferred from iproute2, in older
 * versions, and the rate tables lookup प्रणालीs have been dropped in
 * the kernel. To keep backward compatible with older iproute2 tc
 * utils, we detect the linklayer setting by detecting अगर the rate
 * table were modअगरied.
 *
 * For linklayer ATM table entries, the rate table will be aligned to
 * 48 bytes, thus some table entries will contain the same value.  The
 * mpu (min packet unit) is also encoded पूर्णांकo the old rate table, thus
 * starting from the mpu, we find low and high table entries क्रम
 * mapping this cell.  If these entries contain the same value, when
 * the rate tables have been modअगरied क्रम linklayer ATM.
 *
 * This is करोne by rounding mpu to the nearest 48 bytes cell/entry,
 * and then roundup to the next cell, calc the table entry one below,
 * and compare.
 */
अटल __u8 __detect_linklayer(काष्ठा tc_ratespec *r, __u32 *rtab)
अणु
	पूर्णांक low       = roundup(r->mpu, 48);
	पूर्णांक high      = roundup(low+1, 48);
	पूर्णांक cell_low  = low >> r->cell_log;
	पूर्णांक cell_high = (high >> r->cell_log) - 1;

	/* rtab is too inaccurate at rates > 100Mbit/s */
	अगर ((r->rate > (100000000/8)) || (rtab[0] == 0)) अणु
		pr_debug("TC linklayer: Giving up ATM detection\n");
		वापस TC_LINKLAYER_ETHERNET;
	पूर्ण

	अगर ((cell_high > cell_low) && (cell_high < 256)
	    && (rtab[cell_low] == rtab[cell_high])) अणु
		pr_debug("TC linklayer: Detected ATM, low(%d)=high(%d)=%u\n",
			 cell_low, cell_high, rtab[cell_high]);
		वापस TC_LINKLAYER_ATM;
	पूर्ण
	वापस TC_LINKLAYER_ETHERNET;
पूर्ण

अटल काष्ठा qdisc_rate_table *qdisc_rtab_list;

काष्ठा qdisc_rate_table *qdisc_get_rtab(काष्ठा tc_ratespec *r,
					काष्ठा nlattr *tab,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qdisc_rate_table *rtab;

	अगर (tab == शून्य || r->rate == 0 ||
	    r->cell_log == 0 || r->cell_log >= 32 ||
	    nla_len(tab) != TC_RTAB_SIZE) अणु
		NL_SET_ERR_MSG(extack, "Invalid rate table parameters for searching");
		वापस शून्य;
	पूर्ण

	क्रम (rtab = qdisc_rtab_list; rtab; rtab = rtab->next) अणु
		अगर (!स_भेद(&rtab->rate, r, माप(काष्ठा tc_ratespec)) &&
		    !स_भेद(&rtab->data, nla_data(tab), 1024)) अणु
			rtab->refcnt++;
			वापस rtab;
		पूर्ण
	पूर्ण

	rtab = kदो_स्मृति(माप(*rtab), GFP_KERNEL);
	अगर (rtab) अणु
		rtab->rate = *r;
		rtab->refcnt = 1;
		स_नकल(rtab->data, nla_data(tab), 1024);
		अगर (r->linklayer == TC_LINKLAYER_UNAWARE)
			r->linklayer = __detect_linklayer(r, rtab->data);
		rtab->next = qdisc_rtab_list;
		qdisc_rtab_list = rtab;
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(extack, "Failed to allocate new qdisc rate table");
	पूर्ण
	वापस rtab;
पूर्ण
EXPORT_SYMBOL(qdisc_get_rtab);

व्योम qdisc_put_rtab(काष्ठा qdisc_rate_table *tab)
अणु
	काष्ठा qdisc_rate_table *rtab, **rtabp;

	अगर (!tab || --tab->refcnt)
		वापस;

	क्रम (rtabp = &qdisc_rtab_list;
	     (rtab = *rtabp) != शून्य;
	     rtabp = &rtab->next) अणु
		अगर (rtab == tab) अणु
			*rtabp = rtab->next;
			kमुक्त(rtab);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qdisc_put_rtab);

अटल LIST_HEAD(qdisc_stab_list);

अटल स्थिर काष्ठा nla_policy stab_policy[TCA_STAB_MAX + 1] = अणु
	[TCA_STAB_BASE]	= अणु .len = माप(काष्ठा tc_sizespec) पूर्ण,
	[TCA_STAB_DATA] = अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

अटल काष्ठा qdisc_माप_प्रकारable *qdisc_get_stab(काष्ठा nlattr *opt,
					       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_STAB_MAX + 1];
	काष्ठा qdisc_माप_प्रकारable *stab;
	काष्ठा tc_sizespec *s;
	अचिन्हित पूर्णांक tsize = 0;
	u16 *tab = शून्य;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, TCA_STAB_MAX, opt, stab_policy,
					  extack);
	अगर (err < 0)
		वापस ERR_PTR(err);
	अगर (!tb[TCA_STAB_BASE]) अणु
		NL_SET_ERR_MSG(extack, "Size table base attribute is missing");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	s = nla_data(tb[TCA_STAB_BASE]);

	अगर (s->tsize > 0) अणु
		अगर (!tb[TCA_STAB_DATA]) अणु
			NL_SET_ERR_MSG(extack, "Size table data attribute is missing");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		tab = nla_data(tb[TCA_STAB_DATA]);
		tsize = nla_len(tb[TCA_STAB_DATA]) / माप(u16);
	पूर्ण

	अगर (tsize != s->tsize || (!tab && tsize > 0)) अणु
		NL_SET_ERR_MSG(extack, "Invalid size of size table");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	list_क्रम_each_entry(stab, &qdisc_stab_list, list) अणु
		अगर (स_भेद(&stab->szopts, s, माप(*s)))
			जारी;
		अगर (tsize > 0 && स_भेद(stab->data, tab, tsize * माप(u16)))
			जारी;
		stab->refcnt++;
		वापस stab;
	पूर्ण

	stab = kदो_स्मृति(माप(*stab) + tsize * माप(u16), GFP_KERNEL);
	अगर (!stab)
		वापस ERR_PTR(-ENOMEM);

	stab->refcnt = 1;
	stab->szopts = *s;
	अगर (tsize > 0)
		स_नकल(stab->data, tab, tsize * माप(u16));

	list_add_tail(&stab->list, &qdisc_stab_list);

	वापस stab;
पूर्ण

व्योम qdisc_put_stab(काष्ठा qdisc_माप_प्रकारable *tab)
अणु
	अगर (!tab)
		वापस;

	अगर (--tab->refcnt == 0) अणु
		list_del(&tab->list);
		kमुक्त_rcu(tab, rcu);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qdisc_put_stab);

अटल पूर्णांक qdisc_dump_stab(काष्ठा sk_buff *skb, काष्ठा qdisc_माप_प्रकारable *stab)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_STAB);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put(skb, TCA_STAB_BASE, माप(stab->szopts), &stab->szopts))
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);

	वापस skb->len;

nla_put_failure:
	वापस -1;
पूर्ण

व्योम __qdisc_calculate_pkt_len(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा qdisc_माप_प्रकारable *stab)
अणु
	पूर्णांक pkt_len, slot;

	pkt_len = skb->len + stab->szopts.overhead;
	अगर (unlikely(!stab->szopts.tsize))
		जाओ out;

	slot = pkt_len + stab->szopts.cell_align;
	अगर (unlikely(slot < 0))
		slot = 0;

	slot >>= stab->szopts.cell_log;
	अगर (likely(slot < stab->szopts.tsize))
		pkt_len = stab->data[slot];
	अन्यथा
		pkt_len = stab->data[stab->szopts.tsize - 1] *
				(slot / stab->szopts.tsize) +
				stab->data[slot % stab->szopts.tsize];

	pkt_len <<= stab->szopts.size_log;
out:
	अगर (unlikely(pkt_len < 1))
		pkt_len = 1;
	qdisc_skb_cb(skb)->pkt_len = pkt_len;
पूर्ण
EXPORT_SYMBOL(__qdisc_calculate_pkt_len);

व्योम qdisc_warn_nonwc(स्थिर अक्षर *txt, काष्ठा Qdisc *qdisc)
अणु
	अगर (!(qdisc->flags & TCQ_F_WARN_NONWC)) अणु
		pr_warn("%s: %s qdisc %X: is non-work-conserving?\n",
			txt, qdisc->ops->id, qdisc->handle >> 16);
		qdisc->flags |= TCQ_F_WARN_NONWC;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qdisc_warn_nonwc);

अटल क्रमागत hrसमयr_restart qdisc_watchकरोg(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा qdisc_watchकरोg *wd = container_of(समयr, काष्ठा qdisc_watchकरोg,
						 समयr);

	rcu_पढ़ो_lock();
	__netअगर_schedule(qdisc_root(wd->qdisc));
	rcu_पढ़ो_unlock();

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम qdisc_watchकरोg_init_घड़ीid(काष्ठा qdisc_watchकरोg *wd, काष्ठा Qdisc *qdisc,
				 घड़ीid_t घड़ीid)
अणु
	hrसमयr_init(&wd->समयr, घड़ीid, HRTIMER_MODE_ABS_PINNED);
	wd->समयr.function = qdisc_watchकरोg;
	wd->qdisc = qdisc;
पूर्ण
EXPORT_SYMBOL(qdisc_watchकरोg_init_घड़ीid);

व्योम qdisc_watchकरोg_init(काष्ठा qdisc_watchकरोg *wd, काष्ठा Qdisc *qdisc)
अणु
	qdisc_watchकरोg_init_घड़ीid(wd, qdisc, CLOCK_MONOTONIC);
पूर्ण
EXPORT_SYMBOL(qdisc_watchकरोg_init);

व्योम qdisc_watchकरोg_schedule_range_ns(काष्ठा qdisc_watchकरोg *wd, u64 expires,
				      u64 delta_ns)
अणु
	अगर (test_bit(__QDISC_STATE_DEACTIVATED,
		     &qdisc_root_sleeping(wd->qdisc)->state))
		वापस;

	अगर (hrसमयr_is_queued(&wd->समयr)) अणु
		/* If समयr is alपढ़ोy set in [expires, expires + delta_ns],
		 * करो not reprogram it.
		 */
		अगर (wd->last_expires - expires <= delta_ns)
			वापस;
	पूर्ण

	wd->last_expires = expires;
	hrसमयr_start_range_ns(&wd->समयr,
			       ns_to_kसमय(expires),
			       delta_ns,
			       HRTIMER_MODE_ABS_PINNED);
पूर्ण
EXPORT_SYMBOL(qdisc_watchकरोg_schedule_range_ns);

व्योम qdisc_watchकरोg_cancel(काष्ठा qdisc_watchकरोg *wd)
अणु
	hrसमयr_cancel(&wd->समयr);
पूर्ण
EXPORT_SYMBOL(qdisc_watchकरोg_cancel);

अटल काष्ठा hlist_head *qdisc_class_hash_alloc(अचिन्हित पूर्णांक n)
अणु
	काष्ठा hlist_head *h;
	अचिन्हित पूर्णांक i;

	h = kvदो_स्मृति_array(n, माप(काष्ठा hlist_head), GFP_KERNEL);

	अगर (h != शून्य) अणु
		क्रम (i = 0; i < n; i++)
			INIT_HLIST_HEAD(&h[i]);
	पूर्ण
	वापस h;
पूर्ण

व्योम qdisc_class_hash_grow(काष्ठा Qdisc *sch, काष्ठा Qdisc_class_hash *clhash)
अणु
	काष्ठा Qdisc_class_common *cl;
	काष्ठा hlist_node *next;
	काष्ठा hlist_head *nhash, *ohash;
	अचिन्हित पूर्णांक nsize, nmask, osize;
	अचिन्हित पूर्णांक i, h;

	/* Rehash when load factor exceeds 0.75 */
	अगर (clhash->hashelems * 4 <= clhash->hashsize * 3)
		वापस;
	nsize = clhash->hashsize * 2;
	nmask = nsize - 1;
	nhash = qdisc_class_hash_alloc(nsize);
	अगर (nhash == शून्य)
		वापस;

	ohash = clhash->hash;
	osize = clhash->hashsize;

	sch_tree_lock(sch);
	क्रम (i = 0; i < osize; i++) अणु
		hlist_क्रम_each_entry_safe(cl, next, &ohash[i], hnode) अणु
			h = qdisc_class_hash(cl->classid, nmask);
			hlist_add_head(&cl->hnode, &nhash[h]);
		पूर्ण
	पूर्ण
	clhash->hash     = nhash;
	clhash->hashsize = nsize;
	clhash->hashmask = nmask;
	sch_tree_unlock(sch);

	kvमुक्त(ohash);
पूर्ण
EXPORT_SYMBOL(qdisc_class_hash_grow);

पूर्णांक qdisc_class_hash_init(काष्ठा Qdisc_class_hash *clhash)
अणु
	अचिन्हित पूर्णांक size = 4;

	clhash->hash = qdisc_class_hash_alloc(size);
	अगर (!clhash->hash)
		वापस -ENOMEM;
	clhash->hashsize  = size;
	clhash->hashmask  = size - 1;
	clhash->hashelems = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qdisc_class_hash_init);

व्योम qdisc_class_hash_destroy(काष्ठा Qdisc_class_hash *clhash)
अणु
	kvमुक्त(clhash->hash);
पूर्ण
EXPORT_SYMBOL(qdisc_class_hash_destroy);

व्योम qdisc_class_hash_insert(काष्ठा Qdisc_class_hash *clhash,
			     काष्ठा Qdisc_class_common *cl)
अणु
	अचिन्हित पूर्णांक h;

	INIT_HLIST_NODE(&cl->hnode);
	h = qdisc_class_hash(cl->classid, clhash->hashmask);
	hlist_add_head(&cl->hnode, &clhash->hash[h]);
	clhash->hashelems++;
पूर्ण
EXPORT_SYMBOL(qdisc_class_hash_insert);

व्योम qdisc_class_hash_हटाओ(काष्ठा Qdisc_class_hash *clhash,
			     काष्ठा Qdisc_class_common *cl)
अणु
	hlist_del(&cl->hnode);
	clhash->hashelems--;
पूर्ण
EXPORT_SYMBOL(qdisc_class_hash_हटाओ);

/* Allocate an unique handle from space managed by kernel
 * Possible range is [8000-FFFF]:0000 (0x8000 values)
 */
अटल u32 qdisc_alloc_handle(काष्ठा net_device *dev)
अणु
	पूर्णांक i = 0x8000;
	अटल u32 स्वतःhandle = TC_H_MAKE(0x80000000U, 0);

	करो अणु
		स्वतःhandle += TC_H_MAKE(0x10000U, 0);
		अगर (स्वतःhandle == TC_H_MAKE(TC_H_ROOT, 0))
			स्वतःhandle = TC_H_MAKE(0x80000000U, 0);
		अगर (!qdisc_lookup(dev, स्वतःhandle))
			वापस स्वतःhandle;
		cond_resched();
	पूर्ण जबतक	(--i > 0);

	वापस 0;
पूर्ण

व्योम qdisc_tree_reduce_backlog(काष्ठा Qdisc *sch, पूर्णांक n, पूर्णांक len)
अणु
	bool qdisc_is_offloaded = sch->flags & TCQ_F_OFFLOADED;
	स्थिर काष्ठा Qdisc_class_ops *cops;
	अचिन्हित दीर्घ cl;
	u32 parentid;
	bool notअगरy;
	पूर्णांक drops;

	अगर (n == 0 && len == 0)
		वापस;
	drops = max_t(पूर्णांक, n, 0);
	rcu_पढ़ो_lock();
	जबतक ((parentid = sch->parent)) अणु
		अगर (TC_H_MAJ(parentid) == TC_H_MAJ(TC_H_INGRESS))
			अवरोध;

		अगर (sch->flags & TCQ_F_NOPARENT)
			अवरोध;
		/* Notअगरy parent qdisc only अगर child qdisc becomes empty.
		 *
		 * If child was empty even beक्रमe update then backlog
		 * counter is screwed and we skip notअगरication because
		 * parent class is alपढ़ोy passive.
		 *
		 * If the original child was offloaded then it is allowed
		 * to be seem as empty, so the parent is notअगरied anyway.
		 */
		notअगरy = !sch->q.qlen && !WARN_ON_ONCE(!n &&
						       !qdisc_is_offloaded);
		/* TODO: perक्रमm the search on a per txq basis */
		sch = qdisc_lookup(qdisc_dev(sch), TC_H_MAJ(parentid));
		अगर (sch == शून्य) अणु
			WARN_ON_ONCE(parentid != TC_H_ROOT);
			अवरोध;
		पूर्ण
		cops = sch->ops->cl_ops;
		अगर (notअगरy && cops->qlen_notअगरy) अणु
			cl = cops->find(sch, parentid);
			cops->qlen_notअगरy(sch, cl);
		पूर्ण
		sch->q.qlen -= n;
		sch->qstats.backlog -= len;
		__qdisc_qstats_drop(sch, drops);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(qdisc_tree_reduce_backlog);

पूर्णांक qdisc_offload_dump_helper(काष्ठा Qdisc *sch, क्रमागत tc_setup_type type,
			      व्योम *type_data)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	पूर्णांक err;

	sch->flags &= ~TCQ_F_OFFLOADED;
	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस 0;

	err = dev->netdev_ops->nकरो_setup_tc(dev, type, type_data);
	अगर (err == -EOPNOTSUPP)
		वापस 0;

	अगर (!err)
		sch->flags |= TCQ_F_OFFLOADED;

	वापस err;
पूर्ण
EXPORT_SYMBOL(qdisc_offload_dump_helper);

व्योम qdisc_offload_graft_helper(काष्ठा net_device *dev, काष्ठा Qdisc *sch,
				काष्ठा Qdisc *new, काष्ठा Qdisc *old,
				क्रमागत tc_setup_type type, व्योम *type_data,
				काष्ठा netlink_ext_ack *extack)
अणु
	bool any_qdisc_is_offloaded;
	पूर्णांक err;

	अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
		वापस;

	err = dev->netdev_ops->nकरो_setup_tc(dev, type, type_data);

	/* Don't report error अगर the graft is part of destroy operation. */
	अगर (!err || !new || new == &noop_qdisc)
		वापस;

	/* Don't report error अगर the parent, the old child and the new
	 * one are not offloaded.
	 */
	any_qdisc_is_offloaded = new->flags & TCQ_F_OFFLOADED;
	any_qdisc_is_offloaded |= sch && sch->flags & TCQ_F_OFFLOADED;
	any_qdisc_is_offloaded |= old && old->flags & TCQ_F_OFFLOADED;

	अगर (any_qdisc_is_offloaded)
		NL_SET_ERR_MSG(extack, "Offloading graft operation failed.");
पूर्ण
EXPORT_SYMBOL(qdisc_offload_graft_helper);

अटल व्योम qdisc_offload_graft_root(काष्ठा net_device *dev,
				     काष्ठा Qdisc *new, काष्ठा Qdisc *old,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_root_qopt_offload graft_offload = अणु
		.command	= TC_ROOT_GRAFT,
		.handle		= new ? new->handle : 0,
		.ingress	= (new && new->flags & TCQ_F_INGRESS) ||
				  (old && old->flags & TCQ_F_INGRESS),
	पूर्ण;

	qdisc_offload_graft_helper(dev, शून्य, new, old,
				   TC_SETUP_ROOT_QDISC, &graft_offload, extack);
पूर्ण

अटल पूर्णांक tc_fill_qdisc(काष्ठा sk_buff *skb, काष्ठा Qdisc *q, u32 clid,
			 u32 portid, u32 seq, u16 flags, पूर्णांक event)
अणु
	काष्ठा gnet_stats_basic_cpu __percpu *cpu_bstats = शून्य;
	काष्ठा gnet_stats_queue __percpu *cpu_qstats = शून्य;
	काष्ठा tcmsg *tcm;
	काष्ठा nlmsghdr  *nlh;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा gnet_dump d;
	काष्ठा qdisc_माप_प्रकारable *stab;
	u32 block_index;
	__u32 qlen;

	cond_resched();
	nlh = nlmsg_put(skb, portid, seq, event, माप(*tcm), flags);
	अगर (!nlh)
		जाओ out_nlmsg_trim;
	tcm = nlmsg_data(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_अगरindex = qdisc_dev(q)->अगरindex;
	tcm->tcm_parent = clid;
	tcm->tcm_handle = q->handle;
	tcm->tcm_info = refcount_पढ़ो(&q->refcnt);
	अगर (nla_put_string(skb, TCA_KIND, q->ops->id))
		जाओ nla_put_failure;
	अगर (q->ops->ingress_block_get) अणु
		block_index = q->ops->ingress_block_get(q);
		अगर (block_index &&
		    nla_put_u32(skb, TCA_INGRESS_BLOCK, block_index))
			जाओ nla_put_failure;
	पूर्ण
	अगर (q->ops->egress_block_get) अणु
		block_index = q->ops->egress_block_get(q);
		अगर (block_index &&
		    nla_put_u32(skb, TCA_EGRESS_BLOCK, block_index))
			जाओ nla_put_failure;
	पूर्ण
	अगर (q->ops->dump && q->ops->dump(q, skb) < 0)
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, TCA_HW_OFFLOAD, !!(q->flags & TCQ_F_OFFLOADED)))
		जाओ nla_put_failure;
	qlen = qdisc_qlen_sum(q);

	stab = rtnl_dereference(q->stab);
	अगर (stab && qdisc_dump_stab(skb, stab) < 0)
		जाओ nla_put_failure;

	अगर (gnet_stats_start_copy_compat(skb, TCA_STATS2, TCA_STATS, TCA_XSTATS,
					 शून्य, &d, TCA_PAD) < 0)
		जाओ nla_put_failure;

	अगर (q->ops->dump_stats && q->ops->dump_stats(q, &d) < 0)
		जाओ nla_put_failure;

	अगर (qdisc_is_percpu_stats(q)) अणु
		cpu_bstats = q->cpu_bstats;
		cpu_qstats = q->cpu_qstats;
	पूर्ण

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(q),
				  &d, cpu_bstats, &q->bstats) < 0 ||
	    gnet_stats_copy_rate_est(&d, &q->rate_est) < 0 ||
	    gnet_stats_copy_queue(&d, cpu_qstats, &q->qstats, qlen) < 0)
		जाओ nla_put_failure;

	अगर (gnet_stats_finish_copy(&d) < 0)
		जाओ nla_put_failure;

	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	वापस skb->len;

out_nlmsg_trim:
nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल bool tc_qdisc_dump_ignore(काष्ठा Qdisc *q, bool dump_invisible)
अणु
	अगर (q->flags & TCQ_F_BUILTIN)
		वापस true;
	अगर ((q->flags & TCQ_F_INVISIBLE) && !dump_invisible)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक qdisc_notअगरy(काष्ठा net *net, काष्ठा sk_buff *oskb,
			काष्ठा nlmsghdr *n, u32 clid,
			काष्ठा Qdisc *old, काष्ठा Qdisc *new)
अणु
	काष्ठा sk_buff *skb;
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (old && !tc_qdisc_dump_ignore(old, false)) अणु
		अगर (tc_fill_qdisc(skb, old, clid, portid, n->nlmsg_seq,
				  0, RTM_DELQDISC) < 0)
			जाओ err_out;
	पूर्ण
	अगर (new && !tc_qdisc_dump_ignore(new, false)) अणु
		अगर (tc_fill_qdisc(skb, new, clid, portid, n->nlmsg_seq,
				  old ? NLM_F_REPLACE : 0, RTM_NEWQDISC) < 0)
			जाओ err_out;
	पूर्ण

	अगर (skb->len)
		वापस rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				      n->nlmsg_flags & NLM_F_ECHO);

err_out:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल व्योम notअगरy_and_destroy(काष्ठा net *net, काष्ठा sk_buff *skb,
			       काष्ठा nlmsghdr *n, u32 clid,
			       काष्ठा Qdisc *old, काष्ठा Qdisc *new)
अणु
	अगर (new || old)
		qdisc_notअगरy(net, skb, n, clid, old, new);

	अगर (old)
		qdisc_put(old);
पूर्ण

अटल व्योम qdisc_clear_nolock(काष्ठा Qdisc *sch)
अणु
	sch->flags &= ~TCQ_F_NOLOCK;
	अगर (!(sch->flags & TCQ_F_CPUSTATS))
		वापस;

	मुक्त_percpu(sch->cpu_bstats);
	मुक्त_percpu(sch->cpu_qstats);
	sch->cpu_bstats = शून्य;
	sch->cpu_qstats = शून्य;
	sch->flags &= ~TCQ_F_CPUSTATS;
पूर्ण

/* Graft qdisc "new" to class "classid" of qdisc "parent" or
 * to device "dev".
 *
 * When appropriate send a netlink notअगरication using 'skb'
 * and "n".
 *
 * On success, destroy old qdisc.
 */

अटल पूर्णांक qdisc_graft(काष्ठा net_device *dev, काष्ठा Qdisc *parent,
		       काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n, u32 classid,
		       काष्ठा Qdisc *new, काष्ठा Qdisc *old,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा Qdisc *q = old;
	काष्ठा net *net = dev_net(dev);

	अगर (parent == शून्य) अणु
		अचिन्हित पूर्णांक i, num_q, ingress;

		ingress = 0;
		num_q = dev->num_tx_queues;
		अगर ((q && q->flags & TCQ_F_INGRESS) ||
		    (new && new->flags & TCQ_F_INGRESS)) अणु
			num_q = 1;
			ingress = 1;
			अगर (!dev_ingress_queue(dev)) अणु
				NL_SET_ERR_MSG(extack, "Device does not have an ingress queue");
				वापस -ENOENT;
			पूर्ण
		पूर्ण

		अगर (dev->flags & IFF_UP)
			dev_deactivate(dev);

		qdisc_offload_graft_root(dev, new, old, extack);

		अगर (new && new->ops->attach)
			जाओ skip;

		क्रम (i = 0; i < num_q; i++) अणु
			काष्ठा netdev_queue *dev_queue = dev_ingress_queue(dev);

			अगर (!ingress)
				dev_queue = netdev_get_tx_queue(dev, i);

			old = dev_graft_qdisc(dev_queue, new);
			अगर (new && i > 0)
				qdisc_refcount_inc(new);

			अगर (!ingress)
				qdisc_put(old);
		पूर्ण

skip:
		अगर (!ingress) अणु
			notअगरy_and_destroy(net, skb, n, classid,
					   dev->qdisc, new);
			अगर (new && !new->ops->attach)
				qdisc_refcount_inc(new);
			dev->qdisc = new ? : &noop_qdisc;

			अगर (new && new->ops->attach)
				new->ops->attach(new);
		पूर्ण अन्यथा अणु
			notअगरy_and_destroy(net, skb, n, classid, old, new);
		पूर्ण

		अगर (dev->flags & IFF_UP)
			dev_activate(dev);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा Qdisc_class_ops *cops = parent->ops->cl_ops;
		अचिन्हित दीर्घ cl;
		पूर्णांक err;

		/* Only support running class lockless अगर parent is lockless */
		अगर (new && (new->flags & TCQ_F_NOLOCK) && !(parent->flags & TCQ_F_NOLOCK))
			qdisc_clear_nolock(new);

		अगर (!cops || !cops->graft)
			वापस -EOPNOTSUPP;

		cl = cops->find(parent, classid);
		अगर (!cl) अणु
			NL_SET_ERR_MSG(extack, "Specified class not found");
			वापस -ENOENT;
		पूर्ण

		err = cops->graft(parent, cl, new, &old, extack);
		अगर (err)
			वापस err;
		notअगरy_and_destroy(net, skb, n, classid, old, new);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qdisc_block_indexes_set(काष्ठा Qdisc *sch, काष्ठा nlattr **tca,
				   काष्ठा netlink_ext_ack *extack)
अणु
	u32 block_index;

	अगर (tca[TCA_INGRESS_BLOCK]) अणु
		block_index = nla_get_u32(tca[TCA_INGRESS_BLOCK]);

		अगर (!block_index) अणु
			NL_SET_ERR_MSG(extack, "Ingress block index cannot be 0");
			वापस -EINVAL;
		पूर्ण
		अगर (!sch->ops->ingress_block_set) अणु
			NL_SET_ERR_MSG(extack, "Ingress block sharing is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
		sch->ops->ingress_block_set(sch, block_index);
	पूर्ण
	अगर (tca[TCA_EGRESS_BLOCK]) अणु
		block_index = nla_get_u32(tca[TCA_EGRESS_BLOCK]);

		अगर (!block_index) अणु
			NL_SET_ERR_MSG(extack, "Egress block index cannot be 0");
			वापस -EINVAL;
		पूर्ण
		अगर (!sch->ops->egress_block_set) अणु
			NL_SET_ERR_MSG(extack, "Egress block sharing is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
		sch->ops->egress_block_set(sch, block_index);
	पूर्ण
	वापस 0;
पूर्ण

/*
   Allocate and initialize new qdisc.

   Parameters are passed via opt.
 */

अटल काष्ठा Qdisc *qdisc_create(काष्ठा net_device *dev,
				  काष्ठा netdev_queue *dev_queue,
				  काष्ठा Qdisc *p, u32 parent, u32 handle,
				  काष्ठा nlattr **tca, पूर्णांक *errp,
				  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा nlattr *kind = tca[TCA_KIND];
	काष्ठा Qdisc *sch;
	काष्ठा Qdisc_ops *ops;
	काष्ठा qdisc_माप_प्रकारable *stab;

	ops = qdisc_lookup_ops(kind);
#अगर_घोषित CONFIG_MODULES
	अगर (ops == शून्य && kind != शून्य) अणु
		अक्षर name[IFNAMSIZ];
		अगर (nla_strscpy(name, kind, IFNAMSIZ) >= 0) अणु
			/* We dropped the RTNL semaphore in order to
			 * perक्रमm the module load.  So, even अगर we
			 * succeeded in loading the module we have to
			 * tell the caller to replay the request.  We
			 * indicate this using -EAGAIN.
			 * We replay the request because the device may
			 * go away in the mean समय.
			 */
			rtnl_unlock();
			request_module("sch_%s", name);
			rtnl_lock();
			ops = qdisc_lookup_ops(kind);
			अगर (ops != शून्य) अणु
				/* We will try again qdisc_lookup_ops,
				 * so करोn't keep a reference.
				 */
				module_put(ops->owner);
				err = -EAGAIN;
				जाओ err_out;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	err = -ENOENT;
	अगर (!ops) अणु
		NL_SET_ERR_MSG(extack, "Specified qdisc not found");
		जाओ err_out;
	पूर्ण

	sch = qdisc_alloc(dev_queue, ops, extack);
	अगर (IS_ERR(sch)) अणु
		err = PTR_ERR(sch);
		जाओ err_out2;
	पूर्ण

	sch->parent = parent;

	अगर (handle == TC_H_INGRESS) अणु
		sch->flags |= TCQ_F_INGRESS;
		handle = TC_H_MAKE(TC_H_INGRESS, 0);
	पूर्ण अन्यथा अणु
		अगर (handle == 0) अणु
			handle = qdisc_alloc_handle(dev);
			अगर (handle == 0) अणु
				NL_SET_ERR_MSG(extack, "Maximum number of qdisc handles was exceeded");
				err = -ENOSPC;
				जाओ err_out3;
			पूर्ण
		पूर्ण
		अगर (!netअगर_is_multiqueue(dev))
			sch->flags |= TCQ_F_ONETXQUEUE;
	पूर्ण

	sch->handle = handle;

	/* This exist to keep backward compatible with a userspace
	 * loophole, what allowed userspace to get IFF_NO_QUEUE
	 * facility on older kernels by setting tx_queue_len=0 (prior
	 * to qdisc init), and then क्रमgot to reinit tx_queue_len
	 * beक्रमe again attaching a qdisc.
	 */
	अगर ((dev->priv_flags & IFF_NO_QUEUE) && (dev->tx_queue_len == 0)) अणु
		dev->tx_queue_len = DEFAULT_TX_QUEUE_LEN;
		netdev_info(dev, "Caught tx_queue_len zero misconfig\n");
	पूर्ण

	err = qdisc_block_indexes_set(sch, tca, extack);
	अगर (err)
		जाओ err_out3;

	अगर (ops->init) अणु
		err = ops->init(sch, tca[TCA_OPTIONS], extack);
		अगर (err != 0)
			जाओ err_out5;
	पूर्ण

	अगर (tca[TCA_STAB]) अणु
		stab = qdisc_get_stab(tca[TCA_STAB], extack);
		अगर (IS_ERR(stab)) अणु
			err = PTR_ERR(stab);
			जाओ err_out4;
		पूर्ण
		rcu_assign_poपूर्णांकer(sch->stab, stab);
	पूर्ण
	अगर (tca[TCA_RATE]) अणु
		seqcount_t *running;

		err = -EOPNOTSUPP;
		अगर (sch->flags & TCQ_F_MQROOT) अणु
			NL_SET_ERR_MSG(extack, "Cannot attach rate estimator to a multi-queue root qdisc");
			जाओ err_out4;
		पूर्ण

		अगर (sch->parent != TC_H_ROOT &&
		    !(sch->flags & TCQ_F_INGRESS) &&
		    (!p || !(p->flags & TCQ_F_MQROOT)))
			running = qdisc_root_sleeping_running(sch);
		अन्यथा
			running = &sch->running;

		err = gen_new_estimator(&sch->bstats,
					sch->cpu_bstats,
					&sch->rate_est,
					शून्य,
					running,
					tca[TCA_RATE]);
		अगर (err) अणु
			NL_SET_ERR_MSG(extack, "Failed to generate new estimator");
			जाओ err_out4;
		पूर्ण
	पूर्ण

	qdisc_hash_add(sch, false);
	trace_qdisc_create(ops, dev, parent);

	वापस sch;

err_out5:
	/* ops->init() failed, we call ->destroy() like qdisc_create_dflt() */
	अगर (ops->destroy)
		ops->destroy(sch);
err_out3:
	dev_put(dev);
	qdisc_मुक्त(sch);
err_out2:
	module_put(ops->owner);
err_out:
	*errp = err;
	वापस शून्य;

err_out4:
	/*
	 * Any broken qdiscs that would require a ops->reset() here?
	 * The qdisc was never in action so it shouldn't be necessary.
	 */
	qdisc_put_stab(rtnl_dereference(sch->stab));
	अगर (ops->destroy)
		ops->destroy(sch);
	जाओ err_out3;
पूर्ण

अटल पूर्णांक qdisc_change(काष्ठा Qdisc *sch, काष्ठा nlattr **tca,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qdisc_माप_प्रकारable *ostab, *stab = शून्य;
	पूर्णांक err = 0;

	अगर (tca[TCA_OPTIONS]) अणु
		अगर (!sch->ops->change) अणु
			NL_SET_ERR_MSG(extack, "Change operation not supported by specified qdisc");
			वापस -EINVAL;
		पूर्ण
		अगर (tca[TCA_INGRESS_BLOCK] || tca[TCA_EGRESS_BLOCK]) अणु
			NL_SET_ERR_MSG(extack, "Change of blocks is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
		err = sch->ops->change(sch, tca[TCA_OPTIONS], extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tca[TCA_STAB]) अणु
		stab = qdisc_get_stab(tca[TCA_STAB], extack);
		अगर (IS_ERR(stab))
			वापस PTR_ERR(stab);
	पूर्ण

	ostab = rtnl_dereference(sch->stab);
	rcu_assign_poपूर्णांकer(sch->stab, stab);
	qdisc_put_stab(ostab);

	अगर (tca[TCA_RATE]) अणु
		/* NB: ignores errors from replace_estimator
		   because change can't be unकरोne. */
		अगर (sch->flags & TCQ_F_MQROOT)
			जाओ out;
		gen_replace_estimator(&sch->bstats,
				      sch->cpu_bstats,
				      &sch->rate_est,
				      शून्य,
				      qdisc_root_sleeping_running(sch),
				      tca[TCA_RATE]);
	पूर्ण
out:
	वापस 0;
पूर्ण

काष्ठा check_loop_arg अणु
	काष्ठा qdisc_walker	w;
	काष्ठा Qdisc		*p;
	पूर्णांक			depth;
पूर्ण;

अटल पूर्णांक check_loop_fn(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl,
			 काष्ठा qdisc_walker *w);

अटल पूर्णांक check_loop(काष्ठा Qdisc *q, काष्ठा Qdisc *p, पूर्णांक depth)
अणु
	काष्ठा check_loop_arg	arg;

	अगर (q->ops->cl_ops == शून्य)
		वापस 0;

	arg.w.stop = arg.w.skip = arg.w.count = 0;
	arg.w.fn = check_loop_fn;
	arg.depth = depth;
	arg.p = p;
	q->ops->cl_ops->walk(q, &arg.w);
	वापस arg.w.stop ? -ELOOP : 0;
पूर्ण

अटल पूर्णांक
check_loop_fn(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl, काष्ठा qdisc_walker *w)
अणु
	काष्ठा Qdisc *leaf;
	स्थिर काष्ठा Qdisc_class_ops *cops = q->ops->cl_ops;
	काष्ठा check_loop_arg *arg = (काष्ठा check_loop_arg *)w;

	leaf = cops->leaf(q, cl);
	अगर (leaf) अणु
		अगर (leaf == arg->p || arg->depth > 7)
			वापस -ELOOP;
		वापस check_loop(leaf, arg->p, arg->depth + 1);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा nla_policy rपंचांग_tca_policy[TCA_MAX + 1] = अणु
	[TCA_KIND]		= अणु .type = NLA_STRING पूर्ण,
	[TCA_RATE]		= अणु .type = NLA_BINARY,
				    .len = माप(काष्ठा tc_estimator) पूर्ण,
	[TCA_STAB]		= अणु .type = NLA_NESTED पूर्ण,
	[TCA_DUMP_INVISIBLE]	= अणु .type = NLA_FLAG पूर्ण,
	[TCA_CHAIN]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_INGRESS_BLOCK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_EGRESS_BLOCK]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/*
 * Delete/get qdisc.
 */

अटल पूर्णांक tc_get_qdisc(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tcmsg *tcm = nlmsg_data(n);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	काष्ठा net_device *dev;
	u32 clid;
	काष्ठा Qdisc *q = शून्य;
	काष्ठा Qdisc *p = शून्य;
	पूर्णांक err;

	अगर ((n->nlmsg_type != RTM_GETQDISC) &&
	    !netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	err = nlmsg_parse_deprecated(n, माप(*tcm), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	dev = __dev_get_by_index(net, tcm->tcm_अगरindex);
	अगर (!dev)
		वापस -ENODEV;

	clid = tcm->tcm_parent;
	अगर (clid) अणु
		अगर (clid != TC_H_ROOT) अणु
			अगर (TC_H_MAJ(clid) != TC_H_MAJ(TC_H_INGRESS)) अणु
				p = qdisc_lookup(dev, TC_H_MAJ(clid));
				अगर (!p) अणु
					NL_SET_ERR_MSG(extack, "Failed to find qdisc with specified classid");
					वापस -ENOENT;
				पूर्ण
				q = qdisc_leaf(p, clid);
			पूर्ण अन्यथा अगर (dev_ingress_queue(dev)) अणु
				q = dev_ingress_queue(dev)->qdisc_sleeping;
			पूर्ण
		पूर्ण अन्यथा अणु
			q = dev->qdisc;
		पूर्ण
		अगर (!q) अणु
			NL_SET_ERR_MSG(extack, "Cannot find specified qdisc on specified device");
			वापस -ENOENT;
		पूर्ण

		अगर (tcm->tcm_handle && q->handle != tcm->tcm_handle) अणु
			NL_SET_ERR_MSG(extack, "Invalid handle");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		q = qdisc_lookup(dev, tcm->tcm_handle);
		अगर (!q) अणु
			NL_SET_ERR_MSG(extack, "Failed to find qdisc with specified handle");
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	अगर (tca[TCA_KIND] && nla_म_भेद(tca[TCA_KIND], q->ops->id)) अणु
		NL_SET_ERR_MSG(extack, "Invalid qdisc name");
		वापस -EINVAL;
	पूर्ण

	अगर (n->nlmsg_type == RTM_DELQDISC) अणु
		अगर (!clid) अणु
			NL_SET_ERR_MSG(extack, "Classid cannot be zero");
			वापस -EINVAL;
		पूर्ण
		अगर (q->handle == 0) अणु
			NL_SET_ERR_MSG(extack, "Cannot delete qdisc with handle of zero");
			वापस -ENOENT;
		पूर्ण
		err = qdisc_graft(dev, p, skb, n, clid, शून्य, q, extack);
		अगर (err != 0)
			वापस err;
	पूर्ण अन्यथा अणु
		qdisc_notअगरy(net, skb, n, clid, शून्य, q);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Create/change qdisc.
 */

अटल पूर्णांक tc_modअगरy_qdisc(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tcmsg *tcm;
	काष्ठा nlattr *tca[TCA_MAX + 1];
	काष्ठा net_device *dev;
	u32 clid;
	काष्ठा Qdisc *q, *p;
	पूर्णांक err;

	अगर (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

replay:
	/* Reinit, just in हाल something touches this. */
	err = nlmsg_parse_deprecated(n, माप(*tcm), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	tcm = nlmsg_data(n);
	clid = tcm->tcm_parent;
	q = p = शून्य;

	dev = __dev_get_by_index(net, tcm->tcm_अगरindex);
	अगर (!dev)
		वापस -ENODEV;


	अगर (clid) अणु
		अगर (clid != TC_H_ROOT) अणु
			अगर (clid != TC_H_INGRESS) अणु
				p = qdisc_lookup(dev, TC_H_MAJ(clid));
				अगर (!p) अणु
					NL_SET_ERR_MSG(extack, "Failed to find specified qdisc");
					वापस -ENOENT;
				पूर्ण
				q = qdisc_leaf(p, clid);
			पूर्ण अन्यथा अगर (dev_ingress_queue_create(dev)) अणु
				q = dev_ingress_queue(dev)->qdisc_sleeping;
			पूर्ण
		पूर्ण अन्यथा अणु
			q = dev->qdisc;
		पूर्ण

		/* It may be शेष qdisc, ignore it */
		अगर (q && q->handle == 0)
			q = शून्य;

		अगर (!q || !tcm->tcm_handle || q->handle != tcm->tcm_handle) अणु
			अगर (tcm->tcm_handle) अणु
				अगर (q && !(n->nlmsg_flags & NLM_F_REPLACE)) अणु
					NL_SET_ERR_MSG(extack, "NLM_F_REPLACE needed to override");
					वापस -EEXIST;
				पूर्ण
				अगर (TC_H_MIN(tcm->tcm_handle)) अणु
					NL_SET_ERR_MSG(extack, "Invalid minor handle");
					वापस -EINVAL;
				पूर्ण
				q = qdisc_lookup(dev, tcm->tcm_handle);
				अगर (!q)
					जाओ create_n_graft;
				अगर (n->nlmsg_flags & NLM_F_EXCL) अणु
					NL_SET_ERR_MSG(extack, "Exclusivity flag on, cannot override");
					वापस -EEXIST;
				पूर्ण
				अगर (tca[TCA_KIND] &&
				    nla_म_भेद(tca[TCA_KIND], q->ops->id)) अणु
					NL_SET_ERR_MSG(extack, "Invalid qdisc name");
					वापस -EINVAL;
				पूर्ण
				अगर (q == p ||
				    (p && check_loop(q, p, 0))) अणु
					NL_SET_ERR_MSG(extack, "Qdisc parent/child loop detected");
					वापस -ELOOP;
				पूर्ण
				qdisc_refcount_inc(q);
				जाओ graft;
			पूर्ण अन्यथा अणु
				अगर (!q)
					जाओ create_n_graft;

				/* This magic test requires explanation.
				 *
				 *   We know, that some child q is alपढ़ोy
				 *   attached to this parent and have choice:
				 *   either to change it or to create/graft new one.
				 *
				 *   1. We are allowed to create/graft only
				 *   अगर CREATE and REPLACE flags are set.
				 *
				 *   2. If EXCL is set, requestor wanted to say,
				 *   that qdisc tcm_handle is not expected
				 *   to exist, so that we choose create/graft too.
				 *
				 *   3. The last हाल is when no flags are set.
				 *   Alas, it is sort of hole in API, we
				 *   cannot decide what to करो unambiguously.
				 *   For now we select create/graft, अगर
				 *   user gave KIND, which करोes not match existing.
				 */
				अगर ((n->nlmsg_flags & NLM_F_CREATE) &&
				    (n->nlmsg_flags & NLM_F_REPLACE) &&
				    ((n->nlmsg_flags & NLM_F_EXCL) ||
				     (tca[TCA_KIND] &&
				      nla_म_भेद(tca[TCA_KIND], q->ops->id))))
					जाओ create_n_graft;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!tcm->tcm_handle) अणु
			NL_SET_ERR_MSG(extack, "Handle cannot be zero");
			वापस -EINVAL;
		पूर्ण
		q = qdisc_lookup(dev, tcm->tcm_handle);
	पूर्ण

	/* Change qdisc parameters */
	अगर (!q) अणु
		NL_SET_ERR_MSG(extack, "Specified qdisc not found");
		वापस -ENOENT;
	पूर्ण
	अगर (n->nlmsg_flags & NLM_F_EXCL) अणु
		NL_SET_ERR_MSG(extack, "Exclusivity flag on, cannot modify");
		वापस -EEXIST;
	पूर्ण
	अगर (tca[TCA_KIND] && nla_म_भेद(tca[TCA_KIND], q->ops->id)) अणु
		NL_SET_ERR_MSG(extack, "Invalid qdisc name");
		वापस -EINVAL;
	पूर्ण
	err = qdisc_change(q, tca, extack);
	अगर (err == 0)
		qdisc_notअगरy(net, skb, n, clid, शून्य, q);
	वापस err;

create_n_graft:
	अगर (!(n->nlmsg_flags & NLM_F_CREATE)) अणु
		NL_SET_ERR_MSG(extack, "Qdisc not found. To create specify NLM_F_CREATE flag");
		वापस -ENOENT;
	पूर्ण
	अगर (clid == TC_H_INGRESS) अणु
		अगर (dev_ingress_queue(dev)) अणु
			q = qdisc_create(dev, dev_ingress_queue(dev), p,
					 tcm->tcm_parent, tcm->tcm_parent,
					 tca, &err, extack);
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG(extack, "Cannot find ingress queue for specified device");
			err = -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा netdev_queue *dev_queue;

		अगर (p && p->ops->cl_ops && p->ops->cl_ops->select_queue)
			dev_queue = p->ops->cl_ops->select_queue(p, tcm);
		अन्यथा अगर (p)
			dev_queue = p->dev_queue;
		अन्यथा
			dev_queue = netdev_get_tx_queue(dev, 0);

		q = qdisc_create(dev, dev_queue, p,
				 tcm->tcm_parent, tcm->tcm_handle,
				 tca, &err, extack);
	पूर्ण
	अगर (q == शून्य) अणु
		अगर (err == -EAGAIN)
			जाओ replay;
		वापस err;
	पूर्ण

graft:
	err = qdisc_graft(dev, p, skb, n, clid, q, शून्य, extack);
	अगर (err) अणु
		अगर (q)
			qdisc_put(q);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc_dump_qdisc_root(काष्ठा Qdisc *root, काष्ठा sk_buff *skb,
			      काष्ठा netlink_callback *cb,
			      पूर्णांक *q_idx_p, पूर्णांक s_q_idx, bool recur,
			      bool dump_invisible)
अणु
	पूर्णांक ret = 0, q_idx = *q_idx_p;
	काष्ठा Qdisc *q;
	पूर्णांक b;

	अगर (!root)
		वापस 0;

	q = root;
	अगर (q_idx < s_q_idx) अणु
		q_idx++;
	पूर्ण अन्यथा अणु
		अगर (!tc_qdisc_dump_ignore(q, dump_invisible) &&
		    tc_fill_qdisc(skb, q, q->parent, NETLINK_CB(cb->skb).portid,
				  cb->nlh->nlmsg_seq, NLM_F_MULTI,
				  RTM_NEWQDISC) <= 0)
			जाओ करोne;
		q_idx++;
	पूर्ण

	/* If dumping singletons, there is no qdisc_dev(root) and the singleton
	 * itself has alपढ़ोy been dumped.
	 *
	 * If we've alपढ़ोy dumped the top-level (ingress) qdisc above and the global
	 * qdisc hashtable, we करोn't want to hit it again
	 */
	अगर (!qdisc_dev(root) || !recur)
		जाओ out;

	hash_क्रम_each(qdisc_dev(root)->qdisc_hash, b, q, hash) अणु
		अगर (q_idx < s_q_idx) अणु
			q_idx++;
			जारी;
		पूर्ण
		अगर (!tc_qdisc_dump_ignore(q, dump_invisible) &&
		    tc_fill_qdisc(skb, q, q->parent, NETLINK_CB(cb->skb).portid,
				  cb->nlh->nlmsg_seq, NLM_F_MULTI,
				  RTM_NEWQDISC) <= 0)
			जाओ करोne;
		q_idx++;
	पूर्ण

out:
	*q_idx_p = q_idx;
	वापस ret;
करोne:
	ret = -1;
	जाओ out;
पूर्ण

अटल पूर्णांक tc_dump_qdisc(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक idx, q_idx;
	पूर्णांक s_idx, s_q_idx;
	काष्ठा net_device *dev;
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा nlattr *tca[TCA_MAX + 1];
	पूर्णांक err;

	s_idx = cb->args[0];
	s_q_idx = q_idx = cb->args[1];

	idx = 0;
	ASSERT_RTNL();

	err = nlmsg_parse_deprecated(nlh, माप(काष्ठा tcmsg), tca, TCA_MAX,
				     rपंचांग_tca_policy, cb->extack);
	अगर (err < 0)
		वापस err;

	क्रम_each_netdev(net, dev) अणु
		काष्ठा netdev_queue *dev_queue;

		अगर (idx < s_idx)
			जाओ cont;
		अगर (idx > s_idx)
			s_q_idx = 0;
		q_idx = 0;

		अगर (tc_dump_qdisc_root(dev->qdisc, skb, cb, &q_idx, s_q_idx,
				       true, tca[TCA_DUMP_INVISIBLE]) < 0)
			जाओ करोne;

		dev_queue = dev_ingress_queue(dev);
		अगर (dev_queue &&
		    tc_dump_qdisc_root(dev_queue->qdisc_sleeping, skb, cb,
				       &q_idx, s_q_idx, false,
				       tca[TCA_DUMP_INVISIBLE]) < 0)
			जाओ करोne;

cont:
		idx++;
	पूर्ण

करोne:
	cb->args[0] = idx;
	cb->args[1] = q_idx;

	वापस skb->len;
पूर्ण



/************************************************
 *	Traffic classes manipulation.		*
 ************************************************/

अटल पूर्णांक tc_fill_tclass(काष्ठा sk_buff *skb, काष्ठा Qdisc *q,
			  अचिन्हित दीर्घ cl,
			  u32 portid, u32 seq, u16 flags, पूर्णांक event)
अणु
	काष्ठा tcmsg *tcm;
	काष्ठा nlmsghdr  *nlh;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा gnet_dump d;
	स्थिर काष्ठा Qdisc_class_ops *cl_ops = q->ops->cl_ops;

	cond_resched();
	nlh = nlmsg_put(skb, portid, seq, event, माप(*tcm), flags);
	अगर (!nlh)
		जाओ out_nlmsg_trim;
	tcm = nlmsg_data(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_अगरindex = qdisc_dev(q)->अगरindex;
	tcm->tcm_parent = q->handle;
	tcm->tcm_handle = q->handle;
	tcm->tcm_info = 0;
	अगर (nla_put_string(skb, TCA_KIND, q->ops->id))
		जाओ nla_put_failure;
	अगर (cl_ops->dump && cl_ops->dump(q, cl, skb, tcm) < 0)
		जाओ nla_put_failure;

	अगर (gnet_stats_start_copy_compat(skb, TCA_STATS2, TCA_STATS, TCA_XSTATS,
					 शून्य, &d, TCA_PAD) < 0)
		जाओ nla_put_failure;

	अगर (cl_ops->dump_stats && cl_ops->dump_stats(q, cl, &d) < 0)
		जाओ nla_put_failure;

	अगर (gnet_stats_finish_copy(&d) < 0)
		जाओ nla_put_failure;

	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - b;
	वापस skb->len;

out_nlmsg_trim:
nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tclass_notअगरy(काष्ठा net *net, काष्ठा sk_buff *oskb,
			 काष्ठा nlmsghdr *n, काष्ठा Qdisc *q,
			 अचिन्हित दीर्घ cl, पूर्णांक event)
अणु
	काष्ठा sk_buff *skb;
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	पूर्णांक err = 0;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tc_fill_tclass(skb, q, cl, portid, n->nlmsg_seq, 0, event) < 0) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक tclass_del_notअगरy(काष्ठा net *net,
			     स्थिर काष्ठा Qdisc_class_ops *cops,
			     काष्ठा sk_buff *oskb, काष्ठा nlmsghdr *n,
			     काष्ठा Qdisc *q, अचिन्हित दीर्घ cl,
			     काष्ठा netlink_ext_ack *extack)
अणु
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	अगर (!cops->delete)
		वापस -EOPNOTSUPP;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (tc_fill_tclass(skb, q, cl, portid, n->nlmsg_seq, 0,
			   RTM_DELTCLASS) < 0) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	err = cops->delete(q, cl, extack);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	अगर (err > 0)
		err = 0;
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NET_CLS

काष्ठा tcf_bind_args अणु
	काष्ठा tcf_walker w;
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ cl;
	u32 classid;
पूर्ण;

अटल पूर्णांक tcf_node_bind(काष्ठा tcf_proto *tp, व्योम *n, काष्ठा tcf_walker *arg)
अणु
	काष्ठा tcf_bind_args *a = (व्योम *)arg;

	अगर (tp->ops->bind_class) अणु
		काष्ठा Qdisc *q = tcf_block_q(tp->chain->block);

		sch_tree_lock(q);
		tp->ops->bind_class(n, a->classid, a->cl, q, a->base);
		sch_tree_unlock(q);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा tc_bind_class_args अणु
	काष्ठा qdisc_walker w;
	अचिन्हित दीर्घ new_cl;
	u32 portid;
	u32 clid;
पूर्ण;

अटल पूर्णांक tc_bind_class_walker(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl,
				काष्ठा qdisc_walker *w)
अणु
	काष्ठा tc_bind_class_args *a = (काष्ठा tc_bind_class_args *)w;
	स्थिर काष्ठा Qdisc_class_ops *cops = q->ops->cl_ops;
	काष्ठा tcf_block *block;
	काष्ठा tcf_chain *chain;

	block = cops->tcf_block(q, cl, शून्य);
	अगर (!block)
		वापस 0;
	क्रम (chain = tcf_get_next_chain(block, शून्य);
	     chain;
	     chain = tcf_get_next_chain(block, chain)) अणु
		काष्ठा tcf_proto *tp;

		क्रम (tp = tcf_get_next_proto(chain, शून्य);
		     tp; tp = tcf_get_next_proto(chain, tp)) अणु
			काष्ठा tcf_bind_args arg = अणुपूर्ण;

			arg.w.fn = tcf_node_bind;
			arg.classid = a->clid;
			arg.base = cl;
			arg.cl = a->new_cl;
			tp->ops->walk(tp, &arg.w, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tc_bind_tclass(काष्ठा Qdisc *q, u32 portid, u32 clid,
			   अचिन्हित दीर्घ new_cl)
अणु
	स्थिर काष्ठा Qdisc_class_ops *cops = q->ops->cl_ops;
	काष्ठा tc_bind_class_args args = अणुपूर्ण;

	अगर (!cops->tcf_block)
		वापस;
	args.portid = portid;
	args.clid = clid;
	args.new_cl = new_cl;
	args.w.fn = tc_bind_class_walker;
	q->ops->cl_ops->walk(q, &args.w);
पूर्ण

#अन्यथा

अटल व्योम tc_bind_tclass(काष्ठा Qdisc *q, u32 portid, u32 clid,
			   अचिन्हित दीर्घ new_cl)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक tc_ctl_tclass(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *n,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tcmsg *tcm = nlmsg_data(n);
	काष्ठा nlattr *tca[TCA_MAX + 1];
	काष्ठा net_device *dev;
	काष्ठा Qdisc *q = शून्य;
	स्थिर काष्ठा Qdisc_class_ops *cops;
	अचिन्हित दीर्घ cl = 0;
	अचिन्हित दीर्घ new_cl;
	u32 portid;
	u32 clid;
	u32 qid;
	पूर्णांक err;

	अगर ((n->nlmsg_type != RTM_GETTCLASS) &&
	    !netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	err = nlmsg_parse_deprecated(n, माप(*tcm), tca, TCA_MAX,
				     rपंचांग_tca_policy, extack);
	अगर (err < 0)
		वापस err;

	dev = __dev_get_by_index(net, tcm->tcm_अगरindex);
	अगर (!dev)
		वापस -ENODEV;

	/*
	   parent == TC_H_UNSPEC - unspecअगरied parent.
	   parent == TC_H_ROOT   - class is root, which has no parent.
	   parent == X:0	 - parent is root class.
	   parent == X:Y	 - parent is a node in hierarchy.
	   parent == 0:Y	 - parent is X:Y, where X:0 is qdisc.

	   handle == 0:0	 - generate handle from kernel pool.
	   handle == 0:Y	 - class is X:Y, where X:0 is qdisc.
	   handle == X:Y	 - clear.
	   handle == X:0	 - root class.
	 */

	/* Step 1. Determine qdisc handle X:0 */

	portid = tcm->tcm_parent;
	clid = tcm->tcm_handle;
	qid = TC_H_MAJ(clid);

	अगर (portid != TC_H_ROOT) अणु
		u32 qid1 = TC_H_MAJ(portid);

		अगर (qid && qid1) अणु
			/* If both majors are known, they must be identical. */
			अगर (qid != qid1)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (qid1) अणु
			qid = qid1;
		पूर्ण अन्यथा अगर (qid == 0)
			qid = dev->qdisc->handle;

		/* Now qid is genuine qdisc handle consistent
		 * both with parent and child.
		 *
		 * TC_H_MAJ(portid) still may be unspecअगरied, complete it now.
		 */
		अगर (portid)
			portid = TC_H_MAKE(qid, portid);
	पूर्ण अन्यथा अणु
		अगर (qid == 0)
			qid = dev->qdisc->handle;
	पूर्ण

	/* OK. Locate qdisc */
	q = qdisc_lookup(dev, qid);
	अगर (!q)
		वापस -ENOENT;

	/* An check that it supports classes */
	cops = q->ops->cl_ops;
	अगर (cops == शून्य)
		वापस -EINVAL;

	/* Now try to get class */
	अगर (clid == 0) अणु
		अगर (portid == TC_H_ROOT)
			clid = qid;
	पूर्ण अन्यथा
		clid = TC_H_MAKE(qid, clid);

	अगर (clid)
		cl = cops->find(q, clid);

	अगर (cl == 0) अणु
		err = -ENOENT;
		अगर (n->nlmsg_type != RTM_NEWTCLASS ||
		    !(n->nlmsg_flags & NLM_F_CREATE))
			जाओ out;
	पूर्ण अन्यथा अणु
		चयन (n->nlmsg_type) अणु
		हाल RTM_NEWTCLASS:
			err = -EEXIST;
			अगर (n->nlmsg_flags & NLM_F_EXCL)
				जाओ out;
			अवरोध;
		हाल RTM_DELTCLASS:
			err = tclass_del_notअगरy(net, cops, skb, n, q, cl, extack);
			/* Unbind the class with flilters with 0 */
			tc_bind_tclass(q, portid, clid, 0);
			जाओ out;
		हाल RTM_GETTCLASS:
			err = tclass_notअगरy(net, skb, n, q, cl, RTM_NEWTCLASS);
			जाओ out;
		शेष:
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (tca[TCA_INGRESS_BLOCK] || tca[TCA_EGRESS_BLOCK]) अणु
		NL_SET_ERR_MSG(extack, "Shared blocks are not supported for classes");
		वापस -EOPNOTSUPP;
	पूर्ण

	new_cl = cl;
	err = -EOPNOTSUPP;
	अगर (cops->change)
		err = cops->change(q, clid, portid, tca, &new_cl, extack);
	अगर (err == 0) अणु
		tclass_notअगरy(net, skb, n, q, new_cl, RTM_NEWTCLASS);
		/* We just create a new class, need to करो reverse binding. */
		अगर (cl != new_cl)
			tc_bind_tclass(q, portid, clid, new_cl);
	पूर्ण
out:
	वापस err;
पूर्ण

काष्ठा qdisc_dump_args अणु
	काष्ठा qdisc_walker	w;
	काष्ठा sk_buff		*skb;
	काष्ठा netlink_callback	*cb;
पूर्ण;

अटल पूर्णांक qdisc_class_dump(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl,
			    काष्ठा qdisc_walker *arg)
अणु
	काष्ठा qdisc_dump_args *a = (काष्ठा qdisc_dump_args *)arg;

	वापस tc_fill_tclass(a->skb, q, cl, NETLINK_CB(a->cb->skb).portid,
			      a->cb->nlh->nlmsg_seq, NLM_F_MULTI,
			      RTM_NEWTCLASS);
पूर्ण

अटल पूर्णांक tc_dump_tclass_qdisc(काष्ठा Qdisc *q, काष्ठा sk_buff *skb,
				काष्ठा tcmsg *tcm, काष्ठा netlink_callback *cb,
				पूर्णांक *t_p, पूर्णांक s_t)
अणु
	काष्ठा qdisc_dump_args arg;

	अगर (tc_qdisc_dump_ignore(q, false) ||
	    *t_p < s_t || !q->ops->cl_ops ||
	    (tcm->tcm_parent &&
	     TC_H_MAJ(tcm->tcm_parent) != q->handle)) अणु
		(*t_p)++;
		वापस 0;
	पूर्ण
	अगर (*t_p > s_t)
		स_रखो(&cb->args[1], 0, माप(cb->args)-माप(cb->args[0]));
	arg.w.fn = qdisc_class_dump;
	arg.skb = skb;
	arg.cb = cb;
	arg.w.stop  = 0;
	arg.w.skip = cb->args[1];
	arg.w.count = 0;
	q->ops->cl_ops->walk(q, &arg.w);
	cb->args[1] = arg.w.count;
	अगर (arg.w.stop)
		वापस -1;
	(*t_p)++;
	वापस 0;
पूर्ण

अटल पूर्णांक tc_dump_tclass_root(काष्ठा Qdisc *root, काष्ठा sk_buff *skb,
			       काष्ठा tcmsg *tcm, काष्ठा netlink_callback *cb,
			       पूर्णांक *t_p, पूर्णांक s_t, bool recur)
अणु
	काष्ठा Qdisc *q;
	पूर्णांक b;

	अगर (!root)
		वापस 0;

	अगर (tc_dump_tclass_qdisc(root, skb, tcm, cb, t_p, s_t) < 0)
		वापस -1;

	अगर (!qdisc_dev(root) || !recur)
		वापस 0;

	अगर (tcm->tcm_parent) अणु
		q = qdisc_match_from_root(root, TC_H_MAJ(tcm->tcm_parent));
		अगर (q && q != root &&
		    tc_dump_tclass_qdisc(q, skb, tcm, cb, t_p, s_t) < 0)
			वापस -1;
		वापस 0;
	पूर्ण
	hash_क्रम_each(qdisc_dev(root)->qdisc_hash, b, q, hash) अणु
		अगर (tc_dump_tclass_qdisc(q, skb, tcm, cb, t_p, s_t) < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tc_dump_tclass(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा tcmsg *tcm = nlmsg_data(cb->nlh);
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा netdev_queue *dev_queue;
	काष्ठा net_device *dev;
	पूर्णांक t, s_t;

	अगर (nlmsg_len(cb->nlh) < माप(*tcm))
		वापस 0;
	dev = dev_get_by_index(net, tcm->tcm_अगरindex);
	अगर (!dev)
		वापस 0;

	s_t = cb->args[0];
	t = 0;

	अगर (tc_dump_tclass_root(dev->qdisc, skb, tcm, cb, &t, s_t, true) < 0)
		जाओ करोne;

	dev_queue = dev_ingress_queue(dev);
	अगर (dev_queue &&
	    tc_dump_tclass_root(dev_queue->qdisc_sleeping, skb, tcm, cb,
				&t, s_t, false) < 0)
		जाओ करोne;

करोne:
	cb->args[0] = t;

	dev_put(dev);
	वापस skb->len;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक psched_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_म_लिखो(seq, "%08x %08x %08x %08x\n",
		   (u32)NSEC_PER_USEC, (u32)PSCHED_TICKS2NS(1),
		   1000000,
		   (u32)NSEC_PER_SEC / hrसमयr_resolution);

	वापस 0;
पूर्ण

अटल पूर्णांक __net_init psched_net_init(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *e;

	e = proc_create_single("psched", 0, net->proc_net, psched_show);
	अगर (e == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास psched_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("psched", net->proc_net);
पूर्ण
#अन्यथा
अटल पूर्णांक __net_init psched_net_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम __net_निकास psched_net_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pernet_operations psched_net_ops = अणु
	.init = psched_net_init,
	.निकास = psched_net_निकास,
पूर्ण;

अटल पूर्णांक __init pktsched_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&psched_net_ops);
	अगर (err) अणु
		pr_err("pktsched_init: "
		       "cannot initialize per netns operations\n");
		वापस err;
	पूर्ण

	रेजिस्टर_qdisc(&pfअगरo_fast_ops);
	रेजिस्टर_qdisc(&pfअगरo_qdisc_ops);
	रेजिस्टर_qdisc(&bfअगरo_qdisc_ops);
	रेजिस्टर_qdisc(&pfअगरo_head_drop_qdisc_ops);
	रेजिस्टर_qdisc(&mq_qdisc_ops);
	रेजिस्टर_qdisc(&noqueue_qdisc_ops);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWQDISC, tc_modअगरy_qdisc, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELQDISC, tc_get_qdisc, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETQDISC, tc_get_qdisc, tc_dump_qdisc,
		      0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWTCLASS, tc_ctl_tclass, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELTCLASS, tc_ctl_tclass, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETTCLASS, tc_ctl_tclass, tc_dump_tclass,
		      0);

	वापस 0;
पूर्ण

subsys_initcall(pktsched_init);
