<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_qfq.c         Quick Fair Queueing Plus Scheduler.
 *
 * Copyright (c) 2009 Fabio Checconi, Luigi Rizzo, and Paolo Valente.
 * Copyright (c) 2012 Paolo Valente.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>


/*  Quick Fair Queueing Plus
    ========================

    Sources:

    [1] Paolo Valente,
    "Reducing the Execution Time of Fair-Queueing Schedulers."
    http://algo.ing.unimo.it/people/paolo/agg-sched/agg-sched.pdf

    Sources क्रम QFQ:

    [2] Fabio Checconi, Luigi Rizzo, and Paolo Valente: "QFQ: Efficient
    Packet Scheduling with Tight Bandwidth Distribution Guarantees."

    See also:
    http://retis.sssup.it/~fabio/linux/qfq/
 */

/*

  QFQ+ भागides classes पूर्णांकo aggregates of at most MAX_AGG_CLASSES
  classes. Each aggregate is बारtamped with a भव start समय S
  and a भव finish समय F, and scheduled according to its
  बारtamps. S and F are computed as a function of a प्रणाली भव
  समय function V. The classes within each aggregate are instead
  scheduled with DRR.

  To speed up operations, QFQ+ भागides also aggregates पूर्णांकo a limited
  number of groups. Which group a class beदीर्घs to depends on the
  ratio between the maximum packet length क्रम the class and the weight
  of the class. Groups have their own S and F. In the end, QFQ+
  schedules groups, then aggregates within groups, then classes within
  aggregates. See [1] and [2] क्रम a full description.

  Virtual समय computations.

  S, F and V are all computed in fixed poपूर्णांक arithmetic with
  FRAC_BITS decimal bits.

  QFQ_MAX_INDEX is the maximum index allowed क्रम a group. We need
	one bit per index.
  QFQ_MAX_WSHIFT is the maximum घातer of two supported as a weight.

  The layout of the bits is as below:

                   [ MTU_SHIFT ][      FRAC_BITS    ]
                   [ MAX_INDEX    ][ MIN_SLOT_SHIFT ]
				 ^.__grp->index = 0
				 *.__grp->slot_shअगरt

  where MIN_SLOT_SHIFT is derived by dअगरference from the others.

  The max group index corresponds to Lmax/w_min, where
  Lmax=1<<MTU_SHIFT, w_min = 1 .
  From this, and knowing how many groups (MAX_INDEX) we want,
  we can derive the shअगरt corresponding to each group.

  Because we often need to compute
	F = S + len/w_i  and V = V + len/wsum
  instead of storing w_i store the value
	inv_w = (1<<FRAC_BITS)/w_i
  so we can करो F = S + len * inv_w * wsum.
  We use W_TOT in the क्रमmulas so we can easily move between
  अटल and adaptive weight sum.

  The per-scheduler-instance data contain all the data काष्ठाures
  क्रम the scheduler: biपंचांगaps and bucket lists.

 */

/*
 * Maximum number of consecutive slots occupied by backlogged classes
 * inside a group.
 */
#घोषणा QFQ_MAX_SLOTS	32

/*
 * Shअगरts used क्रम aggregate<->group mapping.  We allow class weights that are
 * in the range [1, 2^MAX_WSHIFT], and we try to map each aggregate i to the
 * group with the smallest index that can support the L_i / r_i configured
 * क्रम the classes in the aggregate.
 *
 * grp->index is the index of the group; and grp->slot_shअगरt
 * is the shअगरt क्रम the corresponding (scaled) sigma_i.
 */
#घोषणा QFQ_MAX_INDEX		24
#घोषणा QFQ_MAX_WSHIFT		10

#घोषणा	QFQ_MAX_WEIGHT		(1<<QFQ_MAX_WSHIFT) /* see qfq_slot_insert */
#घोषणा QFQ_MAX_WSUM		(64*QFQ_MAX_WEIGHT)

#घोषणा FRAC_BITS		30	/* fixed poपूर्णांक arithmetic */
#घोषणा ONE_FP			(1UL << FRAC_BITS)

#घोषणा QFQ_MTU_SHIFT		16	/* to support TSO/GSO */
#घोषणा QFQ_MIN_LMAX		512	/* see qfq_slot_insert */

#घोषणा QFQ_MAX_AGG_CLASSES	8 /* max num classes per aggregate allowed */

/*
 * Possible group states.  These values are used as indexes क्रम the biपंचांगaps
 * array of काष्ठा qfq_queue.
 */
क्रमागत qfq_state अणु ER, IR, EB, IB, QFQ_MAX_STATE पूर्ण;

काष्ठा qfq_group;

काष्ठा qfq_aggregate;

काष्ठा qfq_class अणु
	काष्ठा Qdisc_class_common common;

	अचिन्हित पूर्णांक filter_cnt;

	काष्ठा gnet_stats_basic_packed bstats;
	काष्ठा gnet_stats_queue qstats;
	काष्ठा net_rate_estimator __rcu *rate_est;
	काष्ठा Qdisc *qdisc;
	काष्ठा list_head alist;		/* Link क्रम active-classes list. */
	काष्ठा qfq_aggregate *agg;	/* Parent aggregate. */
	पूर्णांक deficit;			/* DRR deficit counter. */
पूर्ण;

काष्ठा qfq_aggregate अणु
	काष्ठा hlist_node next;	/* Link क्रम the slot list. */
	u64 S, F;		/* flow बारtamps (exact) */

	/* group we beदीर्घ to. In principle we would need the index,
	 * which is log_2(lmax/weight), but we never reference it
	 * directly, only the group.
	 */
	काष्ठा qfq_group *grp;

	/* these are copied from the flowset. */
	u32	class_weight; /* Weight of each class in this aggregate. */
	/* Max pkt size क्रम the classes in this aggregate, DRR quantum. */
	पूर्णांक	lmax;

	u32	inv_w;	    /* ONE_FP/(sum of weights of classes in aggr.). */
	u32	budgeपंचांगax;  /* Max budget क्रम this aggregate. */
	u32	initial_budget, budget;     /* Initial and current budget. */

	पूर्णांक		  num_classes;	/* Number of classes in this aggr. */
	काष्ठा list_head  active;	/* DRR queue of active classes. */

	काष्ठा hlist_node nonfull_next;	/* See nonfull_aggs in qfq_sched. */
पूर्ण;

काष्ठा qfq_group अणु
	u64 S, F;			/* group बारtamps (approx). */
	अचिन्हित पूर्णांक slot_shअगरt;	/* Slot shअगरt. */
	अचिन्हित पूर्णांक index;		/* Group index. */
	अचिन्हित पूर्णांक front;		/* Index of the front slot. */
	अचिन्हित दीर्घ full_slots;	/* non-empty slots */

	/* Array of RR lists of active aggregates. */
	काष्ठा hlist_head slots[QFQ_MAX_SLOTS];
पूर्ण;

काष्ठा qfq_sched अणु
	काष्ठा tcf_proto __rcu *filter_list;
	काष्ठा tcf_block	*block;
	काष्ठा Qdisc_class_hash clhash;

	u64			oldV, V;	/* Precise भव बार. */
	काष्ठा qfq_aggregate	*in_serv_agg;   /* Aggregate being served. */
	u32			wsum;		/* weight sum */
	u32			iwsum;		/* inverse weight sum */

	अचिन्हित दीर्घ biपंचांगaps[QFQ_MAX_STATE];	    /* Group biपंचांगaps. */
	काष्ठा qfq_group groups[QFQ_MAX_INDEX + 1]; /* The groups. */
	u32 min_slot_shअगरt;	/* Index of the group-0 bit in the biपंचांगaps. */

	u32 max_agg_classes;		/* Max number of classes per aggr. */
	काष्ठा hlist_head nonfull_aggs; /* Aggs with room क्रम more classes. */
पूर्ण;

/*
 * Possible reasons why the बारtamps of an aggregate are updated
 * enqueue: the aggregate चयनes from idle to active and must scheduled
 *	    क्रम service
 * requeue: the aggregate finishes its budget, so it stops being served and
 *	    must be rescheduled क्रम service
 */
क्रमागत update_reason अणुenqueue, requeueपूर्ण;

अटल काष्ठा qfq_class *qfq_find_class(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा Qdisc_class_common *clc;

	clc = qdisc_class_find(&q->clhash, classid);
	अगर (clc == शून्य)
		वापस शून्य;
	वापस container_of(clc, काष्ठा qfq_class, common);
पूर्ण

अटल स्थिर काष्ठा nla_policy qfq_policy[TCA_QFQ_MAX + 1] = अणु
	[TCA_QFQ_WEIGHT] = अणु .type = NLA_U32 पूर्ण,
	[TCA_QFQ_LMAX] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/*
 * Calculate a flow index, given its weight and maximum packet length.
 * index = log_2(maxlen/weight) but we need to apply the scaling.
 * This is used only once at flow creation.
 */
अटल पूर्णांक qfq_calc_index(u32 inv_w, अचिन्हित पूर्णांक maxlen, u32 min_slot_shअगरt)
अणु
	u64 slot_size = (u64)maxlen * inv_w;
	अचिन्हित दीर्घ size_map;
	पूर्णांक index = 0;

	size_map = slot_size >> min_slot_shअगरt;
	अगर (!size_map)
		जाओ out;

	index = __fls(size_map) + 1;	/* basically a log_2 */
	index -= !(slot_size - (1ULL << (index + min_slot_shअगरt - 1)));

	अगर (index < 0)
		index = 0;
out:
	pr_debug("qfq calc_index: W = %lu, L = %u, I = %d\n",
		 (अचिन्हित दीर्घ) ONE_FP/inv_w, maxlen, index);

	वापस index;
पूर्ण

अटल व्योम qfq_deactivate_agg(काष्ठा qfq_sched *, काष्ठा qfq_aggregate *);
अटल व्योम qfq_activate_agg(काष्ठा qfq_sched *, काष्ठा qfq_aggregate *,
			     क्रमागत update_reason);

अटल व्योम qfq_init_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg,
			 u32 lmax, u32 weight)
अणु
	INIT_LIST_HEAD(&agg->active);
	hlist_add_head(&agg->nonfull_next, &q->nonfull_aggs);

	agg->lmax = lmax;
	agg->class_weight = weight;
पूर्ण

अटल काष्ठा qfq_aggregate *qfq_find_agg(काष्ठा qfq_sched *q,
					  u32 lmax, u32 weight)
अणु
	काष्ठा qfq_aggregate *agg;

	hlist_क्रम_each_entry(agg, &q->nonfull_aggs, nonfull_next)
		अगर (agg->lmax == lmax && agg->class_weight == weight)
			वापस agg;

	वापस शून्य;
पूर्ण


/* Update aggregate as a function of the new number of classes. */
अटल व्योम qfq_update_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg,
			   पूर्णांक new_num_classes)
अणु
	u32 new_agg_weight;

	अगर (new_num_classes == q->max_agg_classes)
		hlist_del_init(&agg->nonfull_next);

	अगर (agg->num_classes > new_num_classes &&
	    new_num_classes == q->max_agg_classes - 1) /* agg no more full */
		hlist_add_head(&agg->nonfull_next, &q->nonfull_aggs);

	/* The next assignment may let
	 * agg->initial_budget > agg->budgeपंचांगax
	 * hold, we will take it पूर्णांकo account in अक्षरge_actual_service().
	 */
	agg->budgeपंचांगax = new_num_classes * agg->lmax;
	new_agg_weight = agg->class_weight * new_num_classes;
	agg->inv_w = ONE_FP/new_agg_weight;

	अगर (agg->grp == शून्य) अणु
		पूर्णांक i = qfq_calc_index(agg->inv_w, agg->budgeपंचांगax,
				       q->min_slot_shअगरt);
		agg->grp = &q->groups[i];
	पूर्ण

	q->wsum +=
		(पूर्णांक) agg->class_weight * (new_num_classes - agg->num_classes);
	q->iwsum = ONE_FP / q->wsum;

	agg->num_classes = new_num_classes;
पूर्ण

/* Add class to aggregate. */
अटल व्योम qfq_add_to_agg(काष्ठा qfq_sched *q,
			   काष्ठा qfq_aggregate *agg,
			   काष्ठा qfq_class *cl)
अणु
	cl->agg = agg;

	qfq_update_agg(q, agg, agg->num_classes+1);
	अगर (cl->qdisc->q.qlen > 0) अणु /* adding an active class */
		list_add_tail(&cl->alist, &agg->active);
		अगर (list_first_entry(&agg->active, काष्ठा qfq_class, alist) ==
		    cl && q->in_serv_agg != agg) /* agg was inactive */
			qfq_activate_agg(q, agg, enqueue); /* schedule agg */
	पूर्ण
पूर्ण

अटल काष्ठा qfq_aggregate *qfq_choose_next_agg(काष्ठा qfq_sched *);

अटल व्योम qfq_destroy_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg)
अणु
	hlist_del_init(&agg->nonfull_next);
	q->wsum -= agg->class_weight;
	अगर (q->wsum != 0)
		q->iwsum = ONE_FP / q->wsum;

	अगर (q->in_serv_agg == agg)
		q->in_serv_agg = qfq_choose_next_agg(q);
	kमुक्त(agg);
पूर्ण

/* Deschedule class from within its parent aggregate. */
अटल व्योम qfq_deactivate_class(काष्ठा qfq_sched *q, काष्ठा qfq_class *cl)
अणु
	काष्ठा qfq_aggregate *agg = cl->agg;


	list_del(&cl->alist); /* हटाओ from RR queue of the aggregate */
	अगर (list_empty(&agg->active)) /* agg is now inactive */
		qfq_deactivate_agg(q, agg);
पूर्ण

/* Remove class from its parent aggregate. */
अटल व्योम qfq_rm_from_agg(काष्ठा qfq_sched *q, काष्ठा qfq_class *cl)
अणु
	काष्ठा qfq_aggregate *agg = cl->agg;

	cl->agg = शून्य;
	अगर (agg->num_classes == 1) अणु /* agg being emptied, destroy it */
		qfq_destroy_agg(q, agg);
		वापस;
	पूर्ण
	qfq_update_agg(q, agg, agg->num_classes-1);
पूर्ण

/* Deschedule class and हटाओ it from its parent aggregate. */
अटल व्योम qfq_deact_rm_from_agg(काष्ठा qfq_sched *q, काष्ठा qfq_class *cl)
अणु
	अगर (cl->qdisc->q.qlen > 0) /* class is active */
		qfq_deactivate_class(q, cl);

	qfq_rm_from_agg(q, cl);
पूर्ण

/* Move class to a new aggregate, matching the new class weight and/or lmax */
अटल पूर्णांक qfq_change_agg(काष्ठा Qdisc *sch, काष्ठा qfq_class *cl, u32 weight,
			   u32 lmax)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_aggregate *new_agg = qfq_find_agg(q, lmax, weight);

	अगर (new_agg == शून्य) अणु /* create new aggregate */
		new_agg = kzalloc(माप(*new_agg), GFP_ATOMIC);
		अगर (new_agg == शून्य)
			वापस -ENOBUFS;
		qfq_init_agg(q, new_agg, lmax, weight);
	पूर्ण
	qfq_deact_rm_from_agg(q, cl);
	qfq_add_to_agg(q, new_agg, cl);

	वापस 0;
पूर्ण

अटल पूर्णांक qfq_change_class(काष्ठा Qdisc *sch, u32 classid, u32 parentid,
			    काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)*arg;
	bool existing = false;
	काष्ठा nlattr *tb[TCA_QFQ_MAX + 1];
	काष्ठा qfq_aggregate *new_agg = शून्य;
	u32 weight, lmax, inv_w;
	पूर्णांक err;
	पूर्णांक delta_w;

	अगर (tca[TCA_OPTIONS] == शून्य) अणु
		pr_notice("qfq: no options\n");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_QFQ_MAX, tca[TCA_OPTIONS],
					  qfq_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_QFQ_WEIGHT]) अणु
		weight = nla_get_u32(tb[TCA_QFQ_WEIGHT]);
		अगर (!weight || weight > (1UL << QFQ_MAX_WSHIFT)) अणु
			pr_notice("qfq: invalid weight %u\n", weight);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		weight = 1;

	अगर (tb[TCA_QFQ_LMAX]) अणु
		lmax = nla_get_u32(tb[TCA_QFQ_LMAX]);
		अगर (lmax < QFQ_MIN_LMAX || lmax > (1UL << QFQ_MTU_SHIFT)) अणु
			pr_notice("qfq: invalid max length %u\n", lmax);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		lmax = psched_mtu(qdisc_dev(sch));

	inv_w = ONE_FP / weight;
	weight = ONE_FP / inv_w;

	अगर (cl != शून्य &&
	    lmax == cl->agg->lmax &&
	    weight == cl->agg->class_weight)
		वापस 0; /* nothing to change */

	delta_w = weight - (cl ? cl->agg->class_weight : 0);

	अगर (q->wsum + delta_w > QFQ_MAX_WSUM) अणु
		pr_notice("qfq: total weight out of range (%d + %u)\n",
			  delta_w, q->wsum);
		वापस -EINVAL;
	पूर्ण

	अगर (cl != शून्य) अणु /* modअगरy existing class */
		अगर (tca[TCA_RATE]) अणु
			err = gen_replace_estimator(&cl->bstats, शून्य,
						    &cl->rate_est,
						    शून्य,
						    qdisc_root_sleeping_running(sch),
						    tca[TCA_RATE]);
			अगर (err)
				वापस err;
		पूर्ण
		existing = true;
		जाओ set_change_agg;
	पूर्ण

	/* create and init new class */
	cl = kzalloc(माप(काष्ठा qfq_class), GFP_KERNEL);
	अगर (cl == शून्य)
		वापस -ENOBUFS;

	cl->common.classid = classid;
	cl->deficit = lmax;

	cl->qdisc = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
				      classid, शून्य);
	अगर (cl->qdisc == शून्य)
		cl->qdisc = &noop_qdisc;

	अगर (tca[TCA_RATE]) अणु
		err = gen_new_estimator(&cl->bstats, शून्य,
					&cl->rate_est,
					शून्य,
					qdisc_root_sleeping_running(sch),
					tca[TCA_RATE]);
		अगर (err)
			जाओ destroy_class;
	पूर्ण

	अगर (cl->qdisc != &noop_qdisc)
		qdisc_hash_add(cl->qdisc, true);
	sch_tree_lock(sch);
	qdisc_class_hash_insert(&q->clhash, &cl->common);
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

set_change_agg:
	sch_tree_lock(sch);
	new_agg = qfq_find_agg(q, lmax, weight);
	अगर (new_agg == शून्य) अणु /* create new aggregate */
		sch_tree_unlock(sch);
		new_agg = kzalloc(माप(*new_agg), GFP_KERNEL);
		अगर (new_agg == शून्य) अणु
			err = -ENOBUFS;
			gen_समाप्त_estimator(&cl->rate_est);
			जाओ destroy_class;
		पूर्ण
		sch_tree_lock(sch);
		qfq_init_agg(q, new_agg, lmax, weight);
	पूर्ण
	अगर (existing)
		qfq_deact_rm_from_agg(q, cl);
	qfq_add_to_agg(q, new_agg, cl);
	sch_tree_unlock(sch);

	*arg = (अचिन्हित दीर्घ)cl;
	वापस 0;

destroy_class:
	qdisc_put(cl->qdisc);
	kमुक्त(cl);
	वापस err;
पूर्ण

अटल व्योम qfq_destroy_class(काष्ठा Qdisc *sch, काष्ठा qfq_class *cl)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);

	qfq_rm_from_agg(q, cl);
	gen_समाप्त_estimator(&cl->rate_est);
	qdisc_put(cl->qdisc);
	kमुक्त(cl);
पूर्ण

अटल पूर्णांक qfq_delete_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;

	अगर (cl->filter_cnt > 0)
		वापस -EBUSY;

	sch_tree_lock(sch);

	qdisc_purge_queue(cl->qdisc);
	qdisc_class_hash_हटाओ(&q->clhash, &cl->common);

	sch_tree_unlock(sch);

	qfq_destroy_class(sch, cl);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ qfq_search_class(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस (अचिन्हित दीर्घ)qfq_find_class(sch, classid);
पूर्ण

अटल काष्ठा tcf_block *qfq_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;

	वापस q->block;
पूर्ण

अटल अचिन्हित दीर्घ qfq_bind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
				  u32 classid)
अणु
	काष्ठा qfq_class *cl = qfq_find_class(sch, classid);

	अगर (cl != शून्य)
		cl->filter_cnt++;

	वापस (अचिन्हित दीर्घ)cl;
पूर्ण

अटल व्योम qfq_unbind_tcf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;

	cl->filter_cnt--;
पूर्ण

अटल पूर्णांक qfq_graft_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			   काष्ठा Qdisc *new, काष्ठा Qdisc **old,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;

	अगर (new == शून्य) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					cl->common.classid, शून्य);
		अगर (new == शून्य)
			new = &noop_qdisc;
	पूर्ण

	*old = qdisc_replace(sch, new, &cl->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *qfq_class_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;

	वापस cl->qdisc;
पूर्ण

अटल पूर्णांक qfq_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;
	काष्ठा nlattr *nest;

	tcm->tcm_parent	= TC_H_ROOT;
	tcm->tcm_handle	= cl->common.classid;
	tcm->tcm_info	= cl->qdisc->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, TCA_QFQ_WEIGHT, cl->agg->class_weight) ||
	    nla_put_u32(skb, TCA_QFQ_LMAX, cl->agg->lmax))
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक qfq_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
				काष्ठा gnet_dump *d)
अणु
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;
	काष्ठा tc_qfq_stats xstats;

	स_रखो(&xstats, 0, माप(xstats));

	xstats.weight = cl->agg->class_weight;
	xstats.lmax = cl->agg->lmax;

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, शून्य, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    qdisc_qstats_copy(d, cl->qdisc) < 0)
		वापस -1;

	वापस gnet_stats_copy_app(d, &xstats, माप(xstats));
पूर्ण

अटल व्योम qfq_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl;
	अचिन्हित पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], common.hnode) अणु
			अगर (arg->count < arg->skip) अणु
				arg->count++;
				जारी;
			पूर्ण
			अगर (arg->fn(sch, (अचिन्हित दीर्घ)cl, arg) < 0) अणु
				arg->stop = 1;
				वापस;
			पूर्ण
			arg->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा qfq_class *qfq_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				      पूर्णांक *qerr)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl;
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *fl;
	पूर्णांक result;

	अगर (TC_H_MAJ(skb->priority ^ sch->handle) == 0) अणु
		pr_debug("qfq_classify: found %d\n", skb->priority);
		cl = qfq_find_class(sch, skb->priority);
		अगर (cl != शून्य)
			वापस cl;
	पूर्ण

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	fl = rcu_dereference_bh(q->filter_list);
	result = tcf_classअगरy(skb, fl, &res, false);
	अगर (result >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस शून्य;
		पूर्ण
#पूर्ण_अगर
		cl = (काष्ठा qfq_class *)res.class;
		अगर (cl == शून्य)
			cl = qfq_find_class(sch, res.classid);
		वापस cl;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Generic comparison function, handling wraparound. */
अटल अंतरभूत पूर्णांक qfq_gt(u64 a, u64 b)
अणु
	वापस (s64)(a - b) > 0;
पूर्ण

/* Round a precise बारtamp to its slotted value. */
अटल अंतरभूत u64 qfq_round_करोwn(u64 ts, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस ts & ~((1ULL << shअगरt) - 1);
पूर्ण

/* वापस the poपूर्णांकer to the group with lowest index in the biपंचांगap */
अटल अंतरभूत काष्ठा qfq_group *qfq_ffs(काष्ठा qfq_sched *q,
					अचिन्हित दीर्घ biपंचांगap)
अणु
	पूर्णांक index = __ffs(biपंचांगap);
	वापस &q->groups[index];
पूर्ण
/* Calculate a mask to mimic what would be ffs_from(). */
अटल अंतरभूत अचिन्हित दीर्घ mask_from(अचिन्हित दीर्घ biपंचांगap, पूर्णांक from)
अणु
	वापस biपंचांगap & ~((1UL << from) - 1);
पूर्ण

/*
 * The state computation relies on ER=0, IR=1, EB=2, IB=3
 * First compute eligibility comparing grp->S, q->V,
 * then check अगर someone is blocking us and possibly add EB
 */
अटल पूर्णांक qfq_calc_state(काष्ठा qfq_sched *q, स्थिर काष्ठा qfq_group *grp)
अणु
	/* अगर S > V we are not eligible */
	अचिन्हित पूर्णांक state = qfq_gt(grp->S, q->V);
	अचिन्हित दीर्घ mask = mask_from(q->biपंचांगaps[ER], grp->index);
	काष्ठा qfq_group *next;

	अगर (mask) अणु
		next = qfq_ffs(q, mask);
		अगर (qfq_gt(grp->F, next->F))
			state |= EB;
	पूर्ण

	वापस state;
पूर्ण


/*
 * In principle
 *	q->biपंचांगaps[dst] |= q->biपंचांगaps[src] & mask;
 *	q->biपंचांगaps[src] &= ~mask;
 * but we should make sure that src != dst
 */
अटल अंतरभूत व्योम qfq_move_groups(काष्ठा qfq_sched *q, अचिन्हित दीर्घ mask,
				   पूर्णांक src, पूर्णांक dst)
अणु
	q->biपंचांगaps[dst] |= q->biपंचांगaps[src] & mask;
	q->biपंचांगaps[src] &= ~mask;
पूर्ण

अटल व्योम qfq_unblock_groups(काष्ठा qfq_sched *q, पूर्णांक index, u64 old_F)
अणु
	अचिन्हित दीर्घ mask = mask_from(q->biपंचांगaps[ER], index + 1);
	काष्ठा qfq_group *next;

	अगर (mask) अणु
		next = qfq_ffs(q, mask);
		अगर (!qfq_gt(next->F, old_F))
			वापस;
	पूर्ण

	mask = (1UL << index) - 1;
	qfq_move_groups(q, mask, EB, ER);
	qfq_move_groups(q, mask, IB, IR);
पूर्ण

/*
 * perhaps
 *
	old_V ^= q->V;
	old_V >>= q->min_slot_shअगरt;
	अगर (old_V) अणु
		...
	पूर्ण
 *
 */
अटल व्योम qfq_make_eligible(काष्ठा qfq_sched *q)
अणु
	अचिन्हित दीर्घ vslot = q->V >> q->min_slot_shअगरt;
	अचिन्हित दीर्घ old_vslot = q->oldV >> q->min_slot_shअगरt;

	अगर (vslot != old_vslot) अणु
		अचिन्हित दीर्घ mask;
		पूर्णांक last_flip_pos = fls(vslot ^ old_vslot);

		अगर (last_flip_pos > 31) /* higher than the number of groups */
			mask = ~0UL;    /* make all groups eligible */
		अन्यथा
			mask = (1UL << last_flip_pos) - 1;

		qfq_move_groups(q, mask, IR, ER);
		qfq_move_groups(q, mask, IB, EB);
	पूर्ण
पूर्ण

/*
 * The index of the slot in which the input aggregate agg is to be
 * inserted must not be higher than QFQ_MAX_SLOTS-2. There is a '-2'
 * and not a '-1' because the start समय of the group may be moved
 * backward by one slot after the aggregate has been inserted, and
 * this would cause non-empty slots to be right-shअगरted by one
 * position.
 *
 * QFQ+ fully satisfies this bound to the slot index अगर the parameters
 * of the classes are not changed dynamically, and अगर QFQ+ never
 * happens to postpone the service of agg unjustly, i.e., it never
 * happens that the aggregate becomes backlogged and eligible, or just
 * eligible, जबतक an aggregate with a higher approximated finish समय
 * is being served. In particular, in this हाल QFQ+ guarantees that
 * the बारtamps of agg are low enough that the slot index is never
 * higher than 2. Unक्रमtunately, QFQ+ cannot provide the same
 * guarantee अगर it happens to unjustly postpone the service of agg, or
 * अगर the parameters of some class are changed.
 *
 * As क्रम the first event, i.e., an out-of-order service, the
 * upper bound to the slot index guaranteed by QFQ+ grows to
 * 2 +
 * QFQ_MAX_AGG_CLASSES * ((1<<QFQ_MTU_SHIFT)/QFQ_MIN_LMAX) *
 * (current_max_weight/current_wsum) <= 2 + 8 * 128 * 1.
 *
 * The following function deals with this problem by backward-shअगरting
 * the बारtamps of agg, अगर needed, so as to guarantee that the slot
 * index is never higher than QFQ_MAX_SLOTS-2. This backward-shअगरt may
 * cause the service of other aggregates to be postponed, yet the
 * worst-हाल guarantees of these aggregates are not violated.  In
 * fact, in हाल of no out-of-order service, the बारtamps of agg
 * would have been even lower than they are after the backward shअगरt,
 * because QFQ+ would have guaranteed a maximum value equal to 2 क्रम
 * the slot index, and 2 < QFQ_MAX_SLOTS-2. Hence the aggregates whose
 * service is postponed because of the backward-shअगरt would have
 * however रुकोed क्रम the service of agg beक्रमe being served.
 *
 * The other event that may cause the slot index to be higher than 2
 * क्रम agg is a recent change of the parameters of some class. If the
 * weight of a class is increased or the lmax (max_pkt_size) of the
 * class is decreased, then a new aggregate with smaller slot size
 * than the original parent aggregate of the class may happen to be
 * activated. The activation of this aggregate should be properly
 * delayed to when the service of the class has finished in the ideal
 * प्रणाली tracked by QFQ+. If the activation of the aggregate is not
 * delayed to this reference समय instant, then this aggregate may be
 * unjustly served beक्रमe other aggregates रुकोing क्रम service. This
 * may cause the above bound to the slot index to be violated क्रम some
 * of these unlucky aggregates.
 *
 * Instead of delaying the activation of the new aggregate, which is
 * quite complex, the above-discussed capping of the slot index is
 * used to handle also the consequences of a change of the parameters
 * of a class.
 */
अटल व्योम qfq_slot_insert(काष्ठा qfq_group *grp, काष्ठा qfq_aggregate *agg,
			    u64 roundedS)
अणु
	u64 slot = (roundedS - grp->S) >> grp->slot_shअगरt;
	अचिन्हित पूर्णांक i; /* slot index in the bucket list */

	अगर (unlikely(slot > QFQ_MAX_SLOTS - 2)) अणु
		u64 deltaS = roundedS - grp->S -
			((u64)(QFQ_MAX_SLOTS - 2)<<grp->slot_shअगरt);
		agg->S -= deltaS;
		agg->F -= deltaS;
		slot = QFQ_MAX_SLOTS - 2;
	पूर्ण

	i = (grp->front + slot) % QFQ_MAX_SLOTS;

	hlist_add_head(&agg->next, &grp->slots[i]);
	__set_bit(slot, &grp->full_slots);
पूर्ण

/* Maybe पूर्णांकroduce hlist_first_entry?? */
अटल काष्ठा qfq_aggregate *qfq_slot_head(काष्ठा qfq_group *grp)
अणु
	वापस hlist_entry(grp->slots[grp->front].first,
			   काष्ठा qfq_aggregate, next);
पूर्ण

/*
 * हटाओ the entry from the slot
 */
अटल व्योम qfq_front_slot_हटाओ(काष्ठा qfq_group *grp)
अणु
	काष्ठा qfq_aggregate *agg = qfq_slot_head(grp);

	BUG_ON(!agg);
	hlist_del(&agg->next);
	अगर (hlist_empty(&grp->slots[grp->front]))
		__clear_bit(0, &grp->full_slots);
पूर्ण

/*
 * Returns the first aggregate in the first non-empty bucket of the
 * group. As a side effect, adjusts the bucket list so the first
 * non-empty bucket is at position 0 in full_slots.
 */
अटल काष्ठा qfq_aggregate *qfq_slot_scan(काष्ठा qfq_group *grp)
अणु
	अचिन्हित पूर्णांक i;

	pr_debug("qfq slot_scan: grp %u full %#lx\n",
		 grp->index, grp->full_slots);

	अगर (grp->full_slots == 0)
		वापस शून्य;

	i = __ffs(grp->full_slots);  /* zero based */
	अगर (i > 0) अणु
		grp->front = (grp->front + i) % QFQ_MAX_SLOTS;
		grp->full_slots >>= i;
	पूर्ण

	वापस qfq_slot_head(grp);
पूर्ण

/*
 * adjust the bucket list. When the start समय of a group decreases,
 * we move the index करोwn (modulo QFQ_MAX_SLOTS) so we करोn't need to
 * move the objects. The mask of occupied slots must be shअगरted
 * because we use ffs() to find the first non-empty slot.
 * This covers decreases in the group's start समय, but what about
 * increases of the start समय ?
 * Here too we should make sure that i is less than 32
 */
अटल व्योम qfq_slot_rotate(काष्ठा qfq_group *grp, u64 roundedS)
अणु
	अचिन्हित पूर्णांक i = (grp->S - roundedS) >> grp->slot_shअगरt;

	grp->full_slots <<= i;
	grp->front = (grp->front - i) % QFQ_MAX_SLOTS;
पूर्ण

अटल व्योम qfq_update_eligible(काष्ठा qfq_sched *q)
अणु
	काष्ठा qfq_group *grp;
	अचिन्हित दीर्घ ineligible;

	ineligible = q->biपंचांगaps[IR] | q->biपंचांगaps[IB];
	अगर (ineligible) अणु
		अगर (!q->biपंचांगaps[ER]) अणु
			grp = qfq_ffs(q, ineligible);
			अगर (qfq_gt(grp->S, q->V))
				q->V = grp->S;
		पूर्ण
		qfq_make_eligible(q);
	पूर्ण
पूर्ण

/* Dequeue head packet of the head class in the DRR queue of the aggregate. */
अटल व्योम agg_dequeue(काष्ठा qfq_aggregate *agg,
			काष्ठा qfq_class *cl, अचिन्हित पूर्णांक len)
अणु
	qdisc_dequeue_peeked(cl->qdisc);

	cl->deficit -= (पूर्णांक) len;

	अगर (cl->qdisc->q.qlen == 0) /* no more packets, हटाओ from list */
		list_del(&cl->alist);
	अन्यथा अगर (cl->deficit < qdisc_pkt_len(cl->qdisc->ops->peek(cl->qdisc))) अणु
		cl->deficit += agg->lmax;
		list_move_tail(&cl->alist, &agg->active);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *qfq_peek_skb(काष्ठा qfq_aggregate *agg,
					   काष्ठा qfq_class **cl,
					   अचिन्हित पूर्णांक *len)
अणु
	काष्ठा sk_buff *skb;

	*cl = list_first_entry(&agg->active, काष्ठा qfq_class, alist);
	skb = (*cl)->qdisc->ops->peek((*cl)->qdisc);
	अगर (skb == शून्य)
		WARN_ONCE(1, "qfq_dequeue: non-workconserving leaf\n");
	अन्यथा
		*len = qdisc_pkt_len(skb);

	वापस skb;
पूर्ण

/* Update F according to the actual service received by the aggregate. */
अटल अंतरभूत व्योम अक्षरge_actual_service(काष्ठा qfq_aggregate *agg)
अणु
	/* Compute the service received by the aggregate, taking पूर्णांकo
	 * account that, after decreasing the number of classes in
	 * agg, it may happen that
	 * agg->initial_budget - agg->budget > agg->bugdeपंचांगax
	 */
	u32 service_received = min(agg->budgeपंचांगax,
				   agg->initial_budget - agg->budget);

	agg->F = agg->S + (u64)service_received * agg->inv_w;
पूर्ण

/* Assign a reasonable start समय क्रम a new aggregate in group i.
 * Admissible values क्रम \hat(F) are multiples of \sigma_i
 * no greater than V+\sigma_i . Larger values mean that
 * we had a wraparound so we consider the बारtamp to be stale.
 *
 * If F is not stale and F >= V then we set S = F.
 * Otherwise we should assign S = V, but this may violate
 * the ordering in EB (see [2]). So, अगर we have groups in ER,
 * set S to the F_j of the first group j which would be blocking us.
 * We are guaranteed not to move S backward because
 * otherwise our group i would still be blocked.
 */
अटल व्योम qfq_update_start(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg)
अणु
	अचिन्हित दीर्घ mask;
	u64 limit, roundedF;
	पूर्णांक slot_shअगरt = agg->grp->slot_shअगरt;

	roundedF = qfq_round_करोwn(agg->F, slot_shअगरt);
	limit = qfq_round_करोwn(q->V, slot_shअगरt) + (1ULL << slot_shअगरt);

	अगर (!qfq_gt(agg->F, q->V) || qfq_gt(roundedF, limit)) अणु
		/* बारtamp was stale */
		mask = mask_from(q->biपंचांगaps[ER], agg->grp->index);
		अगर (mask) अणु
			काष्ठा qfq_group *next = qfq_ffs(q, mask);
			अगर (qfq_gt(roundedF, next->F)) अणु
				अगर (qfq_gt(limit, next->F))
					agg->S = next->F;
				अन्यथा /* preserve बारtamp correctness */
					agg->S = limit;
				वापस;
			पूर्ण
		पूर्ण
		agg->S = q->V;
	पूर्ण अन्यथा  /* बारtamp is not stale */
		agg->S = agg->F;
पूर्ण

/* Update the बारtamps of agg beक्रमe scheduling/rescheduling it क्रम
 * service.  In particular, assign to agg->F its maximum possible
 * value, i.e., the भव finish समय with which the aggregate
 * should be labeled अगर it used all its budget once in service.
 */
अटल अंतरभूत व्योम
qfq_update_agg_ts(काष्ठा qfq_sched *q,
		    काष्ठा qfq_aggregate *agg, क्रमागत update_reason reason)
अणु
	अगर (reason != requeue)
		qfq_update_start(q, agg);
	अन्यथा /* just अक्षरge agg क्रम the service received */
		agg->S = agg->F;

	agg->F = agg->S + (u64)agg->budgeपंचांगax * agg->inv_w;
पूर्ण

अटल व्योम qfq_schedule_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg);

अटल काष्ठा sk_buff *qfq_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_aggregate *in_serv_agg = q->in_serv_agg;
	काष्ठा qfq_class *cl;
	काष्ठा sk_buff *skb = शून्य;
	/* next-packet len, 0 means no more active classes in in-service agg */
	अचिन्हित पूर्णांक len = 0;

	अगर (in_serv_agg == शून्य)
		वापस शून्य;

	अगर (!list_empty(&in_serv_agg->active))
		skb = qfq_peek_skb(in_serv_agg, &cl, &len);

	/*
	 * If there are no active classes in the in-service aggregate,
	 * or अगर the aggregate has not enough budget to serve its next
	 * class, then choose the next aggregate to serve.
	 */
	अगर (len == 0 || in_serv_agg->budget < len) अणु
		अक्षरge_actual_service(in_serv_agg);

		/* reअक्षरge the budget of the aggregate */
		in_serv_agg->initial_budget = in_serv_agg->budget =
			in_serv_agg->budgeपंचांगax;

		अगर (!list_empty(&in_serv_agg->active)) अणु
			/*
			 * Still active: reschedule क्रम
			 * service. Possible optimization: अगर no other
			 * aggregate is active, then there is no poपूर्णांक
			 * in rescheduling this aggregate, and we can
			 * just keep it as the in-service one. This
			 * should be however a corner हाल, and to
			 * handle it, we would need to मुख्यtain an
			 * extra num_active_aggs field.
			*/
			qfq_update_agg_ts(q, in_serv_agg, requeue);
			qfq_schedule_agg(q, in_serv_agg);
		पूर्ण अन्यथा अगर (sch->q.qlen == 0) अणु /* no aggregate to serve */
			q->in_serv_agg = शून्य;
			वापस शून्य;
		पूर्ण

		/*
		 * If we get here, there are other aggregates queued:
		 * choose the new aggregate to serve.
		 */
		in_serv_agg = q->in_serv_agg = qfq_choose_next_agg(q);
		skb = qfq_peek_skb(in_serv_agg, &cl, &len);
	पूर्ण
	अगर (!skb)
		वापस शून्य;

	qdisc_qstats_backlog_dec(sch, skb);
	sch->q.qlen--;
	qdisc_bstats_update(sch, skb);

	agg_dequeue(in_serv_agg, cl, len);
	/* If lmax is lowered, through qfq_change_class, क्रम a class
	 * owning pending packets with larger size than the new value
	 * of lmax, then the following condition may hold.
	 */
	अगर (unlikely(in_serv_agg->budget < len))
		in_serv_agg->budget = 0;
	अन्यथा
		in_serv_agg->budget -= len;

	q->V += (u64)len * q->iwsum;
	pr_debug("qfq dequeue: len %u F %lld now %lld\n",
		 len, (अचिन्हित दीर्घ दीर्घ) in_serv_agg->F,
		 (अचिन्हित दीर्घ दीर्घ) q->V);

	वापस skb;
पूर्ण

अटल काष्ठा qfq_aggregate *qfq_choose_next_agg(काष्ठा qfq_sched *q)
अणु
	काष्ठा qfq_group *grp;
	काष्ठा qfq_aggregate *agg, *new_front_agg;
	u64 old_F;

	qfq_update_eligible(q);
	q->oldV = q->V;

	अगर (!q->biपंचांगaps[ER])
		वापस शून्य;

	grp = qfq_ffs(q, q->biपंचांगaps[ER]);
	old_F = grp->F;

	agg = qfq_slot_head(grp);

	/* agg starts to be served, हटाओ it from schedule */
	qfq_front_slot_हटाओ(grp);

	new_front_agg = qfq_slot_scan(grp);

	अगर (new_front_agg == शून्य) /* group is now inactive, हटाओ from ER */
		__clear_bit(grp->index, &q->biपंचांगaps[ER]);
	अन्यथा अणु
		u64 roundedS = qfq_round_करोwn(new_front_agg->S,
					      grp->slot_shअगरt);
		अचिन्हित पूर्णांक s;

		अगर (grp->S == roundedS)
			वापस agg;
		grp->S = roundedS;
		grp->F = roundedS + (2ULL << grp->slot_shअगरt);
		__clear_bit(grp->index, &q->biपंचांगaps[ER]);
		s = qfq_calc_state(q, grp);
		__set_bit(grp->index, &q->biपंचांगaps[s]);
	पूर्ण

	qfq_unblock_groups(q, grp->index, old_F);

	वापस agg;
पूर्ण

अटल पूर्णांक qfq_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb), gso_segs;
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl;
	काष्ठा qfq_aggregate *agg;
	पूर्णांक err = 0;
	bool first;

	cl = qfq_classअगरy(skb, sch, &err);
	अगर (cl == शून्य) अणु
		अगर (err & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस err;
	पूर्ण
	pr_debug("qfq_enqueue: cl = %x\n", cl->common.classid);

	अगर (unlikely(cl->agg->lmax < len)) अणु
		pr_debug("qfq: increasing maxpkt from %u to %u for class %u",
			 cl->agg->lmax, len, cl->common.classid);
		err = qfq_change_agg(sch, cl, cl->agg->class_weight, len);
		अगर (err) अणु
			cl->qstats.drops++;
			वापस qdisc_drop(skb, sch, to_मुक्त);
		पूर्ण
	पूर्ण

	gso_segs = skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
	first = !cl->qdisc->q.qlen;
	err = qdisc_enqueue(skb, cl->qdisc, to_मुक्त);
	अगर (unlikely(err != NET_XMIT_SUCCESS)) अणु
		pr_debug("qfq_enqueue: enqueue failed %d\n", err);
		अगर (net_xmit_drop_count(err)) अणु
			cl->qstats.drops++;
			qdisc_qstats_drop(sch);
		पूर्ण
		वापस err;
	पूर्ण

	cl->bstats.bytes += len;
	cl->bstats.packets += gso_segs;
	sch->qstats.backlog += len;
	++sch->q.qlen;

	agg = cl->agg;
	/* अगर the queue was not empty, then करोne here */
	अगर (!first) अणु
		अगर (unlikely(skb == cl->qdisc->ops->peek(cl->qdisc)) &&
		    list_first_entry(&agg->active, काष्ठा qfq_class, alist)
		    == cl && cl->deficit < len)
			list_move_tail(&cl->alist, &agg->active);

		वापस err;
	पूर्ण

	/* schedule class क्रम service within the aggregate */
	cl->deficit = agg->lmax;
	list_add_tail(&cl->alist, &agg->active);

	अगर (list_first_entry(&agg->active, काष्ठा qfq_class, alist) != cl ||
	    q->in_serv_agg == agg)
		वापस err; /* non-empty or in service, nothing अन्यथा to करो */

	qfq_activate_agg(q, agg, enqueue);

	वापस err;
पूर्ण

/*
 * Schedule aggregate according to its बारtamps.
 */
अटल व्योम qfq_schedule_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg)
अणु
	काष्ठा qfq_group *grp = agg->grp;
	u64 roundedS;
	पूर्णांक s;

	roundedS = qfq_round_करोwn(agg->S, grp->slot_shअगरt);

	/*
	 * Insert agg in the correct bucket.
	 * If agg->S >= grp->S we करोn't need to adjust the
	 * bucket list and simply go to the insertion phase.
	 * Otherwise grp->S is decreasing, we must make room
	 * in the bucket list, and also recompute the group state.
	 * Finally, अगर there were no flows in this group and nobody
	 * was in ER make sure to adjust V.
	 */
	अगर (grp->full_slots) अणु
		अगर (!qfq_gt(grp->S, agg->S))
			जाओ skip_update;

		/* create a slot क्रम this agg->S */
		qfq_slot_rotate(grp, roundedS);
		/* group was surely ineligible, हटाओ */
		__clear_bit(grp->index, &q->biपंचांगaps[IR]);
		__clear_bit(grp->index, &q->biपंचांगaps[IB]);
	पूर्ण अन्यथा अगर (!q->biपंचांगaps[ER] && qfq_gt(roundedS, q->V) &&
		   q->in_serv_agg == शून्य)
		q->V = roundedS;

	grp->S = roundedS;
	grp->F = roundedS + (2ULL << grp->slot_shअगरt);
	s = qfq_calc_state(q, grp);
	__set_bit(grp->index, &q->biपंचांगaps[s]);

	pr_debug("qfq enqueue: new state %d %#lx S %lld F %lld V %lld\n",
		 s, q->biपंचांगaps[s],
		 (अचिन्हित दीर्घ दीर्घ) agg->S,
		 (अचिन्हित दीर्घ दीर्घ) agg->F,
		 (अचिन्हित दीर्घ दीर्घ) q->V);

skip_update:
	qfq_slot_insert(grp, agg, roundedS);
पूर्ण


/* Update agg ts and schedule agg क्रम service */
अटल व्योम qfq_activate_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg,
			     क्रमागत update_reason reason)
अणु
	agg->initial_budget = agg->budget = agg->budgeपंचांगax; /* reअक्षरge budg. */

	qfq_update_agg_ts(q, agg, reason);
	अगर (q->in_serv_agg == शून्य) अणु /* no aggr. in service or scheduled */
		q->in_serv_agg = agg; /* start serving this aggregate */
		 /* update V: to be in service, agg must be eligible */
		q->oldV = q->V = agg->S;
	पूर्ण अन्यथा अगर (agg != q->in_serv_agg)
		qfq_schedule_agg(q, agg);
पूर्ण

अटल व्योम qfq_slot_हटाओ(काष्ठा qfq_sched *q, काष्ठा qfq_group *grp,
			    काष्ठा qfq_aggregate *agg)
अणु
	अचिन्हित पूर्णांक i, offset;
	u64 roundedS;

	roundedS = qfq_round_करोwn(agg->S, grp->slot_shअगरt);
	offset = (roundedS - grp->S) >> grp->slot_shअगरt;

	i = (grp->front + offset) % QFQ_MAX_SLOTS;

	hlist_del(&agg->next);
	अगर (hlist_empty(&grp->slots[i]))
		__clear_bit(offset, &grp->full_slots);
पूर्ण

/*
 * Called to क्रमcibly deschedule an aggregate.  If the aggregate is
 * not in the front bucket, or अगर the latter has other aggregates in
 * the front bucket, we can simply हटाओ the aggregate with no other
 * side effects.
 * Otherwise we must propagate the event up.
 */
अटल व्योम qfq_deactivate_agg(काष्ठा qfq_sched *q, काष्ठा qfq_aggregate *agg)
अणु
	काष्ठा qfq_group *grp = agg->grp;
	अचिन्हित दीर्घ mask;
	u64 roundedS;
	पूर्णांक s;

	अगर (agg == q->in_serv_agg) अणु
		अक्षरge_actual_service(agg);
		q->in_serv_agg = qfq_choose_next_agg(q);
		वापस;
	पूर्ण

	agg->F = agg->S;
	qfq_slot_हटाओ(q, grp, agg);

	अगर (!grp->full_slots) अणु
		__clear_bit(grp->index, &q->biपंचांगaps[IR]);
		__clear_bit(grp->index, &q->biपंचांगaps[EB]);
		__clear_bit(grp->index, &q->biपंचांगaps[IB]);

		अगर (test_bit(grp->index, &q->biपंचांगaps[ER]) &&
		    !(q->biपंचांगaps[ER] & ~((1UL << grp->index) - 1))) अणु
			mask = q->biपंचांगaps[ER] & ((1UL << grp->index) - 1);
			अगर (mask)
				mask = ~((1UL << __fls(mask)) - 1);
			अन्यथा
				mask = ~0UL;
			qfq_move_groups(q, mask, EB, ER);
			qfq_move_groups(q, mask, IB, IR);
		पूर्ण
		__clear_bit(grp->index, &q->biपंचांगaps[ER]);
	पूर्ण अन्यथा अगर (hlist_empty(&grp->slots[grp->front])) अणु
		agg = qfq_slot_scan(grp);
		roundedS = qfq_round_करोwn(agg->S, grp->slot_shअगरt);
		अगर (grp->S != roundedS) अणु
			__clear_bit(grp->index, &q->biपंचांगaps[ER]);
			__clear_bit(grp->index, &q->biपंचांगaps[IR]);
			__clear_bit(grp->index, &q->biपंचांगaps[EB]);
			__clear_bit(grp->index, &q->biपंचांगaps[IB]);
			grp->S = roundedS;
			grp->F = roundedS + (2ULL << grp->slot_shअगरt);
			s = qfq_calc_state(q, grp);
			__set_bit(grp->index, &q->biपंचांगaps[s]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qfq_qlen_notअगरy(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl = (काष्ठा qfq_class *)arg;

	qfq_deactivate_class(q, cl);
पूर्ण

अटल पूर्णांक qfq_init_qdisc(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_group *grp;
	पूर्णांक i, j, err;
	u32 max_cl_shअगरt, maxbudg_shअगरt, max_classes;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	err = qdisc_class_hash_init(&q->clhash);
	अगर (err < 0)
		वापस err;

	अगर (qdisc_dev(sch)->tx_queue_len + 1 > QFQ_MAX_AGG_CLASSES)
		max_classes = QFQ_MAX_AGG_CLASSES;
	अन्यथा
		max_classes = qdisc_dev(sch)->tx_queue_len + 1;
	/* max_cl_shअगरt = न्यूनमान(log_2(max_classes)) */
	max_cl_shअगरt = __fls(max_classes);
	q->max_agg_classes = 1<<max_cl_shअगरt;

	/* maxbudg_shअगरt = log2(max_len * max_classes_per_agg) */
	maxbudg_shअगरt = QFQ_MTU_SHIFT + max_cl_shअगरt;
	q->min_slot_shअगरt = FRAC_BITS + maxbudg_shअगरt - QFQ_MAX_INDEX;

	क्रम (i = 0; i <= QFQ_MAX_INDEX; i++) अणु
		grp = &q->groups[i];
		grp->index = i;
		grp->slot_shअगरt = q->min_slot_shअगरt + i;
		क्रम (j = 0; j < QFQ_MAX_SLOTS; j++)
			INIT_HLIST_HEAD(&grp->slots[j]);
	पूर्ण

	INIT_HLIST_HEAD(&q->nonfull_aggs);

	वापस 0;
पूर्ण

अटल व्योम qfq_reset_qdisc(काष्ठा Qdisc *sch)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], common.hnode) अणु
			अगर (cl->qdisc->q.qlen > 0)
				qfq_deactivate_class(q, cl);

			qdisc_reset(cl->qdisc);
		पूर्ण
	पूर्ण
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल व्योम qfq_destroy_qdisc(काष्ठा Qdisc *sch)
अणु
	काष्ठा qfq_sched *q = qdisc_priv(sch);
	काष्ठा qfq_class *cl;
	काष्ठा hlist_node *next;
	अचिन्हित पूर्णांक i;

	tcf_block_put(q->block);

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry_safe(cl, next, &q->clhash.hash[i],
					  common.hnode) अणु
			qfq_destroy_class(sch, cl);
		पूर्ण
	पूर्ण
	qdisc_class_hash_destroy(&q->clhash);
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops qfq_class_ops = अणु
	.change		= qfq_change_class,
	.delete		= qfq_delete_class,
	.find		= qfq_search_class,
	.tcf_block	= qfq_tcf_block,
	.bind_tcf	= qfq_bind_tcf,
	.unbind_tcf	= qfq_unbind_tcf,
	.graft		= qfq_graft_class,
	.leaf		= qfq_class_leaf,
	.qlen_notअगरy	= qfq_qlen_notअगरy,
	.dump		= qfq_dump_class,
	.dump_stats	= qfq_dump_class_stats,
	.walk		= qfq_walk,
पूर्ण;

अटल काष्ठा Qdisc_ops qfq_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &qfq_class_ops,
	.id		= "qfq",
	.priv_size	= माप(काष्ठा qfq_sched),
	.enqueue	= qfq_enqueue,
	.dequeue	= qfq_dequeue,
	.peek		= qdisc_peek_dequeued,
	.init		= qfq_init_qdisc,
	.reset		= qfq_reset_qdisc,
	.destroy	= qfq_destroy_qdisc,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init qfq_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&qfq_qdisc_ops);
पूर्ण

अटल व्योम __निकास qfq_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&qfq_qdisc_ops);
पूर्ण

module_init(qfq_init);
module_निकास(qfq_निकास);
MODULE_LICENSE("GPL");
