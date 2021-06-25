<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_htb.c	Hierarchical token bucket, feed tree version
 *
 * Authors:	Martin Devera, <devik@cdi.cz>
 *
 * Credits (in समय order) क्रम older HTB versions:
 *              Stef Coene <stef.coene@करोcum.org>
 *			HTB support at LARTC mailing list
 *		Ondrej Kraus, <krauso@barr.cz>
 *			found missing INIT_QDISC(htb)
 *		Vladimir Smelhaus, Aamer Akhter, Bert Hubert
 *			helped a lot to locate nasty class stall bug
 *		Andi Kleen, Jamal Hadi, Bert Hubert
 *			code review and helpful comments on shaping
 *		Tomasz Wrona, <tw@eter.tym.pl>
 *			created test हाल so that I was able to fix nasty bug
 *		Wilfried Weissmann
 *			spotted bug in dequeue code and helped with fix
 *		Jiri Fojtasek
 *			fixed requeue routine
 *		and many others. thanks.
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/list.h>
#समावेश <linux/compiler.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <net/netlink.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

/* HTB algorithm.
    Author: devik@cdi.cz
    ========================================================================
    HTB is like TBF with multiple classes. It is also similar to CBQ because
    it allows to assign priority to each class in hierarchy.
    In fact it is another implementation of Floyd's क्रमmal sharing.

    Levels:
    Each class is asचिन्हित level. Leaf has ALWAYS level 0 and root
    classes have level TC_HTB_MAXDEPTH-1. Interior nodes has level
    one less than their parent.
*/

अटल पूर्णांक htb_hysteresis __पढ़ो_mostly = 0; /* whether to use mode hysteresis क्रम speedup */
#घोषणा HTB_VER 0x30011		/* major must be matched with number suplied by TC as version */

#अगर HTB_VER >> 16 != TC_HTB_PROTOVER
#त्रुटि "Mismatched sch_htb.c and pkt_sch.h"
#पूर्ण_अगर

/* Module parameter and sysfs export */
module_param    (htb_hysteresis, पूर्णांक, 0640);
MODULE_PARM_DESC(htb_hysteresis, "Hysteresis mode, less CPU load, less accurate");

अटल पूर्णांक htb_rate_est = 0; /* htb classes have a शेष rate estimator */
module_param(htb_rate_est, पूर्णांक, 0640);
MODULE_PARM_DESC(htb_rate_est, "setup a default rate estimator (4sec 16sec) for htb classes");

/* used पूर्णांकernaly to keep status of single class */
क्रमागत htb_cmode अणु
	HTB_CANT_SEND,		/* class can't send and can't borrow */
	HTB_MAY_BORROW,		/* class can't send but may borrow */
	HTB_CAN_SEND		/* class can send */
पूर्ण;

काष्ठा htb_prio अणु
	जोड़ अणु
		काष्ठा rb_root	row;
		काष्ठा rb_root	feed;
	पूर्ण;
	काष्ठा rb_node	*ptr;
	/* When class changes from state 1->2 and disconnects from
	 * parent's feed then we lost ptr value and start from the
	 * first child again. Here we store classid of the
	 * last valid ptr (used when ptr is शून्य).
	 */
	u32		last_ptr_id;
पूर्ण;

/* पूर्णांकerior & leaf nodes; props specअगरic to leaves are marked L:
 * To reduce false sharing, place mostly पढ़ो fields at beginning,
 * and mostly written ones at the end.
 */
काष्ठा htb_class अणु
	काष्ठा Qdisc_class_common common;
	काष्ठा psched_ratecfg	rate;
	काष्ठा psched_ratecfg	उच्चमान;
	s64			buffer, cbuffer;/* token bucket depth/rate */
	s64			mbuffer;	/* max रुको समय */
	u32			prio;		/* these two are used only by leaves... */
	पूर्णांक			quantum;	/* but stored क्रम parent-to-leaf वापस */

	काष्ठा tcf_proto __rcu	*filter_list;	/* class attached filters */
	काष्ठा tcf_block	*block;
	पूर्णांक			filter_cnt;

	पूर्णांक			level;		/* our level (see above) */
	अचिन्हित पूर्णांक		children;
	काष्ठा htb_class	*parent;	/* parent class */

	काष्ठा net_rate_estimator __rcu *rate_est;

	/*
	 * Written often fields
	 */
	काष्ठा gnet_stats_basic_packed bstats;
	काष्ठा gnet_stats_basic_packed bstats_bias;
	काष्ठा tc_htb_xstats	xstats;	/* our special stats */

	/* token bucket parameters */
	s64			tokens, ctokens;/* current number of tokens */
	s64			t_c;		/* checkpoपूर्णांक समय */

	जोड़ अणु
		काष्ठा htb_class_leaf अणु
			पूर्णांक		deficit[TC_HTB_MAXDEPTH];
			काष्ठा Qdisc	*q;
		पूर्ण leaf;
		काष्ठा htb_class_inner अणु
			काष्ठा htb_prio clprio[TC_HTB_NUMPRIO];
		पूर्ण inner;
	पूर्ण;
	s64			pq_key;

	पूर्णांक			prio_activity;	/* क्रम which prios are we active */
	क्रमागत htb_cmode		cmode;		/* current mode of the class */
	काष्ठा rb_node		pq_node;	/* node क्रम event queue */
	काष्ठा rb_node		node[TC_HTB_NUMPRIO];	/* node क्रम self or feed tree */

	अचिन्हित पूर्णांक drops ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक		overlimits;
पूर्ण;

काष्ठा htb_level अणु
	काष्ठा rb_root	रुको_pq;
	काष्ठा htb_prio hprio[TC_HTB_NUMPRIO];
पूर्ण;

काष्ठा htb_sched अणु
	काष्ठा Qdisc_class_hash clhash;
	पूर्णांक			defcls;		/* class where unclassअगरied flows go to */
	पूर्णांक			rate2quantum;	/* quant = rate / rate2quantum */

	/* filters क्रम qdisc itself */
	काष्ठा tcf_proto __rcu	*filter_list;
	काष्ठा tcf_block	*block;

#घोषणा HTB_WARN_TOOMANYEVENTS	0x1
	अचिन्हित पूर्णांक		warned;	/* only one warning */
	पूर्णांक			direct_qlen;
	काष्ठा work_काष्ठा	work;

	/* non shaped skbs; let them go directly thru */
	काष्ठा qdisc_skb_head	direct_queue;
	u32			direct_pkts;
	u32			overlimits;

	काष्ठा qdisc_watchकरोg	watchकरोg;

	s64			now;	/* cached dequeue समय */

	/* समय of nearest event per level (row) */
	s64			near_ev_cache[TC_HTB_MAXDEPTH];

	पूर्णांक			row_mask[TC_HTB_MAXDEPTH];

	काष्ठा htb_level	hlevel[TC_HTB_MAXDEPTH];

	काष्ठा Qdisc		**direct_qdiscs;
	अचिन्हित पूर्णांक            num_direct_qdiscs;

	bool			offload;
पूर्ण;

/* find class in global hash table using given handle */
अटल अंतरभूत काष्ठा htb_class *htb_find(u32 handle, काष्ठा Qdisc *sch)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा Qdisc_class_common *clc;

	clc = qdisc_class_find(&q->clhash, handle);
	अगर (clc == शून्य)
		वापस शून्य;
	वापस container_of(clc, काष्ठा htb_class, common);
पूर्ण

अटल अचिन्हित दीर्घ htb_search(काष्ठा Qdisc *sch, u32 handle)
अणु
	वापस (अचिन्हित दीर्घ)htb_find(handle, sch);
पूर्ण
/**
 * htb_classअगरy - classअगरy a packet पूर्णांकo class
 *
 * It वापसs शून्य अगर the packet should be dropped or -1 अगर the packet
 * should be passed directly thru. In all other हालs leaf class is वापसed.
 * We allow direct class selection by classid in priority. The we examine
 * filters in qdisc and in inner nodes (अगर higher filter poपूर्णांकs to the inner
 * node). If we end up with classid MAJOR:0 we enqueue the skb पूर्णांकo special
 * पूर्णांकernal fअगरo (direct). These packets then go directly thru. If we still
 * have no valid leaf we try to use MAJOR:शेष leaf. It still unsuccessful
 * then finish and वापस direct queue.
 */
#घोषणा HTB_सूचीECT ((काष्ठा htb_class *)-1L)

अटल काष्ठा htb_class *htb_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				      पूर्णांक *qerr)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl;
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *tcf;
	पूर्णांक result;

	/* allow to select class by setting skb->priority to valid classid;
	 * note that nfmark can be used too by attaching filter fw with no
	 * rules in it
	 */
	अगर (skb->priority == sch->handle)
		वापस HTB_सूचीECT;	/* X:0 (direct flow) selected */
	cl = htb_find(skb->priority, sch);
	अगर (cl) अणु
		अगर (cl->level == 0)
			वापस cl;
		/* Start with inner filter chain अगर a non-leaf class is selected */
		tcf = rcu_dereference_bh(cl->filter_list);
	पूर्ण अन्यथा अणु
		tcf = rcu_dereference_bh(q->filter_list);
	पूर्ण

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	जबतक (tcf && (result = tcf_classअगरy(skb, tcf, &res, false)) >= 0) अणु
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
		cl = (व्योम *)res.class;
		अगर (!cl) अणु
			अगर (res.classid == sch->handle)
				वापस HTB_सूचीECT;	/* X:0 (direct flow) */
			cl = htb_find(res.classid, sch);
			अगर (!cl)
				अवरोध;	/* filter selected invalid classid */
		पूर्ण
		अगर (!cl->level)
			वापस cl;	/* we hit leaf; वापस it */

		/* we have got inner class; apply inner filter chain */
		tcf = rcu_dereference_bh(cl->filter_list);
	पूर्ण
	/* classअगरication failed; try to use शेष class */
	cl = htb_find(TC_H_MAKE(TC_H_MAJ(sch->handle), q->defcls), sch);
	अगर (!cl || cl->level)
		वापस HTB_सूचीECT;	/* bad शेष .. this is safe bet */
	वापस cl;
पूर्ण

/**
 * htb_add_to_id_tree - adds class to the round robin list
 *
 * Routine adds class to the list (actually tree) sorted by classid.
 * Make sure that class is not alपढ़ोy on such list क्रम given prio.
 */
अटल व्योम htb_add_to_id_tree(काष्ठा rb_root *root,
			       काष्ठा htb_class *cl, पूर्णांक prio)
अणु
	काष्ठा rb_node **p = &root->rb_node, *parent = शून्य;

	जबतक (*p) अणु
		काष्ठा htb_class *c;
		parent = *p;
		c = rb_entry(parent, काष्ठा htb_class, node[prio]);

		अगर (cl->common.classid > c->common.classid)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&cl->node[prio], parent, p);
	rb_insert_color(&cl->node[prio], root);
पूर्ण

/**
 * htb_add_to_रुको_tree - adds class to the event queue with delay
 *
 * The class is added to priority event queue to indicate that class will
 * change its mode in cl->pq_key microseconds. Make sure that class is not
 * alपढ़ोy in the queue.
 */
अटल व्योम htb_add_to_रुको_tree(काष्ठा htb_sched *q,
				 काष्ठा htb_class *cl, s64 delay)
अणु
	काष्ठा rb_node **p = &q->hlevel[cl->level].रुको_pq.rb_node, *parent = शून्य;

	cl->pq_key = q->now + delay;
	अगर (cl->pq_key == q->now)
		cl->pq_key++;

	/* update the nearest event cache */
	अगर (q->near_ev_cache[cl->level] > cl->pq_key)
		q->near_ev_cache[cl->level] = cl->pq_key;

	जबतक (*p) अणु
		काष्ठा htb_class *c;
		parent = *p;
		c = rb_entry(parent, काष्ठा htb_class, pq_node);
		अगर (cl->pq_key >= c->pq_key)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&cl->pq_node, parent, p);
	rb_insert_color(&cl->pq_node, &q->hlevel[cl->level].रुको_pq);
पूर्ण

/**
 * htb_next_rb_node - finds next node in binary tree
 *
 * When we are past last key we वापस शून्य.
 * Average complनिकासy is 2 steps per call.
 */
अटल अंतरभूत व्योम htb_next_rb_node(काष्ठा rb_node **n)
अणु
	*n = rb_next(*n);
पूर्ण

/**
 * htb_add_class_to_row - add class to its row
 *
 * The class is added to row at priorities marked in mask.
 * It करोes nothing अगर mask == 0.
 */
अटल अंतरभूत व्योम htb_add_class_to_row(काष्ठा htb_sched *q,
					काष्ठा htb_class *cl, पूर्णांक mask)
अणु
	q->row_mask[cl->level] |= mask;
	जबतक (mask) अणु
		पूर्णांक prio = ffz(~mask);
		mask &= ~(1 << prio);
		htb_add_to_id_tree(&q->hlevel[cl->level].hprio[prio].row, cl, prio);
	पूर्ण
पूर्ण

/* If this triggers, it is a bug in this code, but it need not be fatal */
अटल व्योम htb_safe_rb_erase(काष्ठा rb_node *rb, काष्ठा rb_root *root)
अणु
	अगर (RB_EMPTY_NODE(rb)) अणु
		WARN_ON(1);
	पूर्ण अन्यथा अणु
		rb_erase(rb, root);
		RB_CLEAR_NODE(rb);
	पूर्ण
पूर्ण


/**
 * htb_हटाओ_class_from_row - हटाओs class from its row
 *
 * The class is हटाओd from row at priorities marked in mask.
 * It करोes nothing अगर mask == 0.
 */
अटल अंतरभूत व्योम htb_हटाओ_class_from_row(काष्ठा htb_sched *q,
						 काष्ठा htb_class *cl, पूर्णांक mask)
अणु
	पूर्णांक m = 0;
	काष्ठा htb_level *hlevel = &q->hlevel[cl->level];

	जबतक (mask) अणु
		पूर्णांक prio = ffz(~mask);
		काष्ठा htb_prio *hprio = &hlevel->hprio[prio];

		mask &= ~(1 << prio);
		अगर (hprio->ptr == cl->node + prio)
			htb_next_rb_node(&hprio->ptr);

		htb_safe_rb_erase(cl->node + prio, &hprio->row);
		अगर (!hprio->row.rb_node)
			m |= 1 << prio;
	पूर्ण
	q->row_mask[cl->level] &= ~m;
पूर्ण

/**
 * htb_activate_prios - creates active classe's feed chain
 *
 * The class is connected to ancestors and/or appropriate rows
 * क्रम priorities it is participating on. cl->cmode must be new
 * (activated) mode. It करोes nothing अगर cl->prio_activity == 0.
 */
अटल व्योम htb_activate_prios(काष्ठा htb_sched *q, काष्ठा htb_class *cl)
अणु
	काष्ठा htb_class *p = cl->parent;
	दीर्घ m, mask = cl->prio_activity;

	जबतक (cl->cmode == HTB_MAY_BORROW && p && mask) अणु
		m = mask;
		जबतक (m) अणु
			पूर्णांक prio = ffz(~m);
			m &= ~(1 << prio);

			अगर (p->inner.clprio[prio].feed.rb_node)
				/* parent alपढ़ोy has its feed in use so that
				 * reset bit in mask as parent is alपढ़ोy ok
				 */
				mask &= ~(1 << prio);

			htb_add_to_id_tree(&p->inner.clprio[prio].feed, cl, prio);
		पूर्ण
		p->prio_activity |= mask;
		cl = p;
		p = cl->parent;

	पूर्ण
	अगर (cl->cmode == HTB_CAN_SEND && mask)
		htb_add_class_to_row(q, cl, mask);
पूर्ण

/**
 * htb_deactivate_prios - हटाओ class from feed chain
 *
 * cl->cmode must represent old mode (beक्रमe deactivation). It करोes
 * nothing अगर cl->prio_activity == 0. Class is हटाओd from all feed
 * chains and rows.
 */
अटल व्योम htb_deactivate_prios(काष्ठा htb_sched *q, काष्ठा htb_class *cl)
अणु
	काष्ठा htb_class *p = cl->parent;
	दीर्घ m, mask = cl->prio_activity;

	जबतक (cl->cmode == HTB_MAY_BORROW && p && mask) अणु
		m = mask;
		mask = 0;
		जबतक (m) अणु
			पूर्णांक prio = ffz(~m);
			m &= ~(1 << prio);

			अगर (p->inner.clprio[prio].ptr == cl->node + prio) अणु
				/* we are removing child which is poपूर्णांकed to from
				 * parent feed - क्रमget the poपूर्णांकer but remember
				 * classid
				 */
				p->inner.clprio[prio].last_ptr_id = cl->common.classid;
				p->inner.clprio[prio].ptr = शून्य;
			पूर्ण

			htb_safe_rb_erase(cl->node + prio,
					  &p->inner.clprio[prio].feed);

			अगर (!p->inner.clprio[prio].feed.rb_node)
				mask |= 1 << prio;
		पूर्ण

		p->prio_activity &= ~mask;
		cl = p;
		p = cl->parent;

	पूर्ण
	अगर (cl->cmode == HTB_CAN_SEND && mask)
		htb_हटाओ_class_from_row(q, cl, mask);
पूर्ण

अटल अंतरभूत s64 htb_lowater(स्थिर काष्ठा htb_class *cl)
अणु
	अगर (htb_hysteresis)
		वापस cl->cmode != HTB_CANT_SEND ? -cl->cbuffer : 0;
	अन्यथा
		वापस 0;
पूर्ण
अटल अंतरभूत s64 htb_hiwater(स्थिर काष्ठा htb_class *cl)
अणु
	अगर (htb_hysteresis)
		वापस cl->cmode == HTB_CAN_SEND ? -cl->buffer : 0;
	अन्यथा
		वापस 0;
पूर्ण


/**
 * htb_class_mode - computes and वापसs current class mode
 *
 * It computes cl's mode at समय cl->t_c+dअगरf and वापसs it. If mode
 * is not HTB_CAN_SEND then cl->pq_key is updated to समय dअगरference
 * from now to समय when cl will change its state.
 * Also it is worth to note that class mode करोesn't change simply
 * at cl->अणुc,पूर्णtokens == 0 but there can rather be hysteresis of
 * 0 .. -cl->अणुc,पूर्णbuffer range. It is meant to limit number of
 * mode transitions per समय unit. The speed gain is about 1/6.
 */
अटल अंतरभूत क्रमागत htb_cmode
htb_class_mode(काष्ठा htb_class *cl, s64 *dअगरf)
अणु
	s64 toks;

	अगर ((toks = (cl->ctokens + *dअगरf)) < htb_lowater(cl)) अणु
		*dअगरf = -toks;
		वापस HTB_CANT_SEND;
	पूर्ण

	अगर ((toks = (cl->tokens + *dअगरf)) >= htb_hiwater(cl))
		वापस HTB_CAN_SEND;

	*dअगरf = -toks;
	वापस HTB_MAY_BORROW;
पूर्ण

/**
 * htb_change_class_mode - changes classe's mode
 *
 * This should be the only way how to change classe's mode under normal
 * cirsumstances. Routine will update feed lists linkage, change mode
 * and add class to the रुको event queue अगर appropriate. New mode should
 * be dअगरferent from old one and cl->pq_key has to be valid अगर changing
 * to mode other than HTB_CAN_SEND (see htb_add_to_रुको_tree).
 */
अटल व्योम
htb_change_class_mode(काष्ठा htb_sched *q, काष्ठा htb_class *cl, s64 *dअगरf)
अणु
	क्रमागत htb_cmode new_mode = htb_class_mode(cl, dअगरf);

	अगर (new_mode == cl->cmode)
		वापस;

	अगर (new_mode == HTB_CANT_SEND) अणु
		cl->overlimits++;
		q->overlimits++;
	पूर्ण

	अगर (cl->prio_activity) अणु	/* not necessary: speed optimization */
		अगर (cl->cmode != HTB_CANT_SEND)
			htb_deactivate_prios(q, cl);
		cl->cmode = new_mode;
		अगर (new_mode != HTB_CANT_SEND)
			htb_activate_prios(q, cl);
	पूर्ण अन्यथा
		cl->cmode = new_mode;
पूर्ण

/**
 * htb_activate - inserts leaf cl पूर्णांकo appropriate active feeds
 *
 * Routine learns (new) priority of leaf and activates feed chain
 * क्रम the prio. It can be called on alपढ़ोy active leaf safely.
 * It also adds leaf पूर्णांकo droplist.
 */
अटल अंतरभूत व्योम htb_activate(काष्ठा htb_sched *q, काष्ठा htb_class *cl)
अणु
	WARN_ON(cl->level || !cl->leaf.q || !cl->leaf.q->q.qlen);

	अगर (!cl->prio_activity) अणु
		cl->prio_activity = 1 << cl->prio;
		htb_activate_prios(q, cl);
	पूर्ण
पूर्ण

/**
 * htb_deactivate - हटाओ leaf cl from active feeds
 *
 * Make sure that leaf is active. In the other words it can't be called
 * with non-active leaf. It also हटाओs class from the drop list.
 */
अटल अंतरभूत व्योम htb_deactivate(काष्ठा htb_sched *q, काष्ठा htb_class *cl)
अणु
	WARN_ON(!cl->prio_activity);

	htb_deactivate_prios(q, cl);
	cl->prio_activity = 0;
पूर्ण

अटल पूर्णांक htb_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		       काष्ठा sk_buff **to_मुक्त)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl = htb_classअगरy(skb, sch, &ret);

	अगर (cl == HTB_सूचीECT) अणु
		/* enqueue to helper queue */
		अगर (q->direct_queue.qlen < q->direct_qlen) अणु
			__qdisc_enqueue_tail(skb, &q->direct_queue);
			q->direct_pkts++;
		पूर्ण अन्यथा अणु
			वापस qdisc_drop(skb, sch, to_मुक्त);
		पूर्ण
#अगर_घोषित CONFIG_NET_CLS_ACT
	पूर्ण अन्यथा अगर (!cl) अणु
		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर ((ret = qdisc_enqueue(skb, cl->leaf.q,
					to_मुक्त)) != NET_XMIT_SUCCESS) अणु
		अगर (net_xmit_drop_count(ret)) अणु
			qdisc_qstats_drop(sch);
			cl->drops++;
		पूर्ण
		वापस ret;
	पूर्ण अन्यथा अणु
		htb_activate(q, cl);
	पूर्ण

	sch->qstats.backlog += len;
	sch->q.qlen++;
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल अंतरभूत व्योम htb_accnt_tokens(काष्ठा htb_class *cl, पूर्णांक bytes, s64 dअगरf)
अणु
	s64 toks = dअगरf + cl->tokens;

	अगर (toks > cl->buffer)
		toks = cl->buffer;
	toks -= (s64) psched_l2t_ns(&cl->rate, bytes);
	अगर (toks <= -cl->mbuffer)
		toks = 1 - cl->mbuffer;

	cl->tokens = toks;
पूर्ण

अटल अंतरभूत व्योम htb_accnt_ctokens(काष्ठा htb_class *cl, पूर्णांक bytes, s64 dअगरf)
अणु
	s64 toks = dअगरf + cl->ctokens;

	अगर (toks > cl->cbuffer)
		toks = cl->cbuffer;
	toks -= (s64) psched_l2t_ns(&cl->उच्चमान, bytes);
	अगर (toks <= -cl->mbuffer)
		toks = 1 - cl->mbuffer;

	cl->ctokens = toks;
पूर्ण

/**
 * htb_अक्षरge_class - अक्षरges amount "bytes" to leaf and ancestors
 *
 * Routine assumes that packet "bytes" दीर्घ was dequeued from leaf cl
 * borrowing from "level". It accounts bytes to उच्चमान leaky bucket क्रम
 * leaf and all ancestors and to rate bucket क्रम ancestors at levels
 * "level" and higher. It also handles possible change of mode resulting
 * from the update. Note that mode can also increase here (MAY_BORROW to
 * CAN_SEND) because we can use more precise घड़ी that event queue here.
 * In such हाल we हटाओ class from event queue first.
 */
अटल व्योम htb_अक्षरge_class(काष्ठा htb_sched *q, काष्ठा htb_class *cl,
			     पूर्णांक level, काष्ठा sk_buff *skb)
अणु
	पूर्णांक bytes = qdisc_pkt_len(skb);
	क्रमागत htb_cmode old_mode;
	s64 dअगरf;

	जबतक (cl) अणु
		dअगरf = min_t(s64, q->now - cl->t_c, cl->mbuffer);
		अगर (cl->level >= level) अणु
			अगर (cl->level == level)
				cl->xstats.lends++;
			htb_accnt_tokens(cl, bytes, dअगरf);
		पूर्ण अन्यथा अणु
			cl->xstats.borrows++;
			cl->tokens += dअगरf;	/* we moved t_c; update tokens */
		पूर्ण
		htb_accnt_ctokens(cl, bytes, dअगरf);
		cl->t_c = q->now;

		old_mode = cl->cmode;
		dअगरf = 0;
		htb_change_class_mode(q, cl, &dअगरf);
		अगर (old_mode != cl->cmode) अणु
			अगर (old_mode != HTB_CAN_SEND)
				htb_safe_rb_erase(&cl->pq_node, &q->hlevel[cl->level].रुको_pq);
			अगर (cl->cmode != HTB_CAN_SEND)
				htb_add_to_रुको_tree(q, cl, dअगरf);
		पूर्ण

		/* update basic stats except क्रम leaves which are alपढ़ोy updated */
		अगर (cl->level)
			bstats_update(&cl->bstats, skb);

		cl = cl->parent;
	पूर्ण
पूर्ण

/**
 * htb_करो_events - make mode changes to classes at the level
 *
 * Scans event queue क्रम pending events and applies them. Returns समय of
 * next pending event (0 क्रम no event in pq, q->now क्रम too many events).
 * Note: Applied are events whose have cl->pq_key <= q->now.
 */
अटल s64 htb_करो_events(काष्ठा htb_sched *q, स्थिर पूर्णांक level,
			 अचिन्हित दीर्घ start)
अणु
	/* करोn't run क्रम दीर्घer than 2 jअगरfies; 2 is used instead of
	 * 1 to simplअगरy things when jअगरfy is going to be incremented
	 * too soon
	 */
	अचिन्हित दीर्घ stop_at = start + 2;
	काष्ठा rb_root *रुको_pq = &q->hlevel[level].रुको_pq;

	जबतक (समय_beक्रमe(jअगरfies, stop_at)) अणु
		काष्ठा htb_class *cl;
		s64 dअगरf;
		काष्ठा rb_node *p = rb_first(रुको_pq);

		अगर (!p)
			वापस 0;

		cl = rb_entry(p, काष्ठा htb_class, pq_node);
		अगर (cl->pq_key > q->now)
			वापस cl->pq_key;

		htb_safe_rb_erase(p, रुको_pq);
		dअगरf = min_t(s64, q->now - cl->t_c, cl->mbuffer);
		htb_change_class_mode(q, cl, &dअगरf);
		अगर (cl->cmode != HTB_CAN_SEND)
			htb_add_to_रुको_tree(q, cl, dअगरf);
	पूर्ण

	/* too much load - let's जारी after a अवरोध क्रम scheduling */
	अगर (!(q->warned & HTB_WARN_TOOMANYEVENTS)) अणु
		pr_warn("htb: too many events!\n");
		q->warned |= HTB_WARN_TOOMANYEVENTS;
	पूर्ण

	वापस q->now;
पूर्ण

/* Returns class->node+prio from id-tree where classe's id is >= id. शून्य
 * is no such one exists.
 */
अटल काष्ठा rb_node *htb_id_find_next_upper(पूर्णांक prio, काष्ठा rb_node *n,
					      u32 id)
अणु
	काष्ठा rb_node *r = शून्य;
	जबतक (n) अणु
		काष्ठा htb_class *cl =
		    rb_entry(n, काष्ठा htb_class, node[prio]);

		अगर (id > cl->common.classid) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अगर (id < cl->common.classid) अणु
			r = n;
			n = n->rb_left;
		पूर्ण अन्यथा अणु
			वापस n;
		पूर्ण
	पूर्ण
	वापस r;
पूर्ण

/**
 * htb_lookup_leaf - वापसs next leaf class in DRR order
 *
 * Find leaf where current feed poपूर्णांकers poपूर्णांकs to.
 */
अटल काष्ठा htb_class *htb_lookup_leaf(काष्ठा htb_prio *hprio, स्थिर पूर्णांक prio)
अणु
	पूर्णांक i;
	काष्ठा अणु
		काष्ठा rb_node *root;
		काष्ठा rb_node **pptr;
		u32 *pid;
	पूर्ण stk[TC_HTB_MAXDEPTH], *sp = stk;

	BUG_ON(!hprio->row.rb_node);
	sp->root = hprio->row.rb_node;
	sp->pptr = &hprio->ptr;
	sp->pid = &hprio->last_ptr_id;

	क्रम (i = 0; i < 65535; i++) अणु
		अगर (!*sp->pptr && *sp->pid) अणु
			/* ptr was invalidated but id is valid - try to recover
			 * the original or next ptr
			 */
			*sp->pptr =
			    htb_id_find_next_upper(prio, sp->root, *sp->pid);
		पूर्ण
		*sp->pid = 0;	/* ptr is valid now so that हटाओ this hपूर्णांक as it
				 * can become out of date quickly
				 */
		अगर (!*sp->pptr) अणु	/* we are at right end; शुरुआत & go up */
			*sp->pptr = sp->root;
			जबतक ((*sp->pptr)->rb_left)
				*sp->pptr = (*sp->pptr)->rb_left;
			अगर (sp > stk) अणु
				sp--;
				अगर (!*sp->pptr) अणु
					WARN_ON(1);
					वापस शून्य;
				पूर्ण
				htb_next_rb_node(sp->pptr);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा htb_class *cl;
			काष्ठा htb_prio *clp;

			cl = rb_entry(*sp->pptr, काष्ठा htb_class, node[prio]);
			अगर (!cl->level)
				वापस cl;
			clp = &cl->inner.clprio[prio];
			(++sp)->root = clp->feed.rb_node;
			sp->pptr = &clp->ptr;
			sp->pid = &clp->last_ptr_id;
		पूर्ण
	पूर्ण
	WARN_ON(1);
	वापस शून्य;
पूर्ण

/* dequeues packet at given priority and level; call only अगर
 * you are sure that there is active class at prio/level
 */
अटल काष्ठा sk_buff *htb_dequeue_tree(काष्ठा htb_sched *q, स्थिर पूर्णांक prio,
					स्थिर पूर्णांक level)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा htb_class *cl, *start;
	काष्ठा htb_level *hlevel = &q->hlevel[level];
	काष्ठा htb_prio *hprio = &hlevel->hprio[prio];

	/* look initial class up in the row */
	start = cl = htb_lookup_leaf(hprio, prio);

	करो अणु
next:
		अगर (unlikely(!cl))
			वापस शून्य;

		/* class can be empty - it is unlikely but can be true अगर leaf
		 * qdisc drops packets in enqueue routine or अगर someone used
		 * graft operation on the leaf since last dequeue;
		 * simply deactivate and skip such class
		 */
		अगर (unlikely(cl->leaf.q->q.qlen == 0)) अणु
			काष्ठा htb_class *next;
			htb_deactivate(q, cl);

			/* row/level might become empty */
			अगर ((q->row_mask[level] & (1 << prio)) == 0)
				वापस शून्य;

			next = htb_lookup_leaf(hprio, prio);

			अगर (cl == start)	/* fix start अगर we just deleted it */
				start = next;
			cl = next;
			जाओ next;
		पूर्ण

		skb = cl->leaf.q->dequeue(cl->leaf.q);
		अगर (likely(skb != शून्य))
			अवरोध;

		qdisc_warn_nonwc("htb", cl->leaf.q);
		htb_next_rb_node(level ? &cl->parent->inner.clprio[prio].ptr:
					 &q->hlevel[0].hprio[prio].ptr);
		cl = htb_lookup_leaf(hprio, prio);

	पूर्ण जबतक (cl != start);

	अगर (likely(skb != शून्य)) अणु
		bstats_update(&cl->bstats, skb);
		cl->leaf.deficit[level] -= qdisc_pkt_len(skb);
		अगर (cl->leaf.deficit[level] < 0) अणु
			cl->leaf.deficit[level] += cl->quantum;
			htb_next_rb_node(level ? &cl->parent->inner.clprio[prio].ptr :
						 &q->hlevel[0].hprio[prio].ptr);
		पूर्ण
		/* this used to be after अक्षरge_class but this स्थिरelation
		 * gives us slightly better perक्रमmance
		 */
		अगर (!cl->leaf.q->q.qlen)
			htb_deactivate(q, cl);
		htb_अक्षरge_class(q, cl, level, skb);
	पूर्ण
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *htb_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	पूर्णांक level;
	s64 next_event;
	अचिन्हित दीर्घ start_at;

	/* try to dequeue direct packets as high prio (!) to minimize cpu work */
	skb = __qdisc_dequeue_head(&q->direct_queue);
	अगर (skb != शून्य) अणु
ok:
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;
		वापस skb;
	पूर्ण

	अगर (!sch->q.qlen)
		जाओ fin;
	q->now = kसमय_get_ns();
	start_at = jअगरfies;

	next_event = q->now + 5LLU * NSEC_PER_SEC;

	क्रम (level = 0; level < TC_HTB_MAXDEPTH; level++) अणु
		/* common हाल optimization - skip event handler quickly */
		पूर्णांक m;
		s64 event = q->near_ev_cache[level];

		अगर (q->now >= event) अणु
			event = htb_करो_events(q, level, start_at);
			अगर (!event)
				event = q->now + NSEC_PER_SEC;
			q->near_ev_cache[level] = event;
		पूर्ण

		अगर (next_event > event)
			next_event = event;

		m = ~q->row_mask[level];
		जबतक (m != (पूर्णांक)(-1)) अणु
			पूर्णांक prio = ffz(m);

			m |= 1 << prio;
			skb = htb_dequeue_tree(q, prio, level);
			अगर (likely(skb != शून्य))
				जाओ ok;
		पूर्ण
	पूर्ण
	अगर (likely(next_event > q->now))
		qdisc_watchकरोg_schedule_ns(&q->watchकरोg, next_event);
	अन्यथा
		schedule_work(&q->work);
fin:
	वापस skb;
पूर्ण

/* reset all classes */
/* always caled under BH & queue lock */
अटल व्योम htb_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], common.hnode) अणु
			अगर (cl->level)
				स_रखो(&cl->inner, 0, माप(cl->inner));
			अन्यथा अणु
				अगर (cl->leaf.q && !q->offload)
					qdisc_reset(cl->leaf.q);
			पूर्ण
			cl->prio_activity = 0;
			cl->cmode = HTB_CAN_SEND;
		पूर्ण
	पूर्ण
	qdisc_watchकरोg_cancel(&q->watchकरोg);
	__qdisc_reset_queue(&q->direct_queue);
	sch->q.qlen = 0;
	sch->qstats.backlog = 0;
	स_रखो(q->hlevel, 0, माप(q->hlevel));
	स_रखो(q->row_mask, 0, माप(q->row_mask));
पूर्ण

अटल स्थिर काष्ठा nla_policy htb_policy[TCA_HTB_MAX + 1] = अणु
	[TCA_HTB_PARMS]	= अणु .len = माप(काष्ठा tc_htb_opt) पूर्ण,
	[TCA_HTB_INIT]	= अणु .len = माप(काष्ठा tc_htb_glob) पूर्ण,
	[TCA_HTB_CTAB]	= अणु .type = NLA_BINARY, .len = TC_RTAB_SIZE पूर्ण,
	[TCA_HTB_RTAB]	= अणु .type = NLA_BINARY, .len = TC_RTAB_SIZE पूर्ण,
	[TCA_HTB_सूचीECT_QLEN] = अणु .type = NLA_U32 पूर्ण,
	[TCA_HTB_RATE64] = अणु .type = NLA_U64 पूर्ण,
	[TCA_HTB_CEIL64] = अणु .type = NLA_U64 पूर्ण,
	[TCA_HTB_OFFLOAD] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल व्योम htb_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा htb_sched *q = container_of(work, काष्ठा htb_sched, work);
	काष्ठा Qdisc *sch = q->watchकरोg.qdisc;

	rcu_पढ़ो_lock();
	__netअगर_schedule(qdisc_root(sch));
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम htb_set_lockdep_class_child(काष्ठा Qdisc *q)
अणु
	अटल काष्ठा lock_class_key child_key;

	lockdep_set_class(qdisc_lock(q), &child_key);
पूर्ण

अटल पूर्णांक htb_offload(काष्ठा net_device *dev, काष्ठा tc_htb_qopt_offload *opt)
अणु
	वापस dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_HTB, opt);
पूर्ण

अटल पूर्णांक htb_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_htb_qopt_offload offload_opt;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_HTB_MAX + 1];
	काष्ठा tc_htb_glob *gopt;
	अचिन्हित पूर्णांक ntx;
	bool offload;
	पूर्णांक err;

	qdisc_watchकरोg_init(&q->watchकरोg, sch);
	INIT_WORK(&q->work, htb_work_func);

	अगर (!opt)
		वापस -EINVAL;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	err = nla_parse_nested_deprecated(tb, TCA_HTB_MAX, opt, htb_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_HTB_INIT])
		वापस -EINVAL;

	gopt = nla_data(tb[TCA_HTB_INIT]);
	अगर (gopt->version != HTB_VER >> 16)
		वापस -EINVAL;

	offload = nla_get_flag(tb[TCA_HTB_OFFLOAD]);

	अगर (offload) अणु
		अगर (sch->parent != TC_H_ROOT)
			वापस -EOPNOTSUPP;

		अगर (!tc_can_offload(dev) || !dev->netdev_ops->nकरो_setup_tc)
			वापस -EOPNOTSUPP;

		q->num_direct_qdiscs = dev->real_num_tx_queues;
		q->direct_qdiscs = kसुस्मृति(q->num_direct_qdiscs,
					   माप(*q->direct_qdiscs),
					   GFP_KERNEL);
		अगर (!q->direct_qdiscs)
			वापस -ENOMEM;
	पूर्ण

	err = qdisc_class_hash_init(&q->clhash);
	अगर (err < 0)
		जाओ err_मुक्त_direct_qdiscs;

	qdisc_skb_head_init(&q->direct_queue);

	अगर (tb[TCA_HTB_सूचीECT_QLEN])
		q->direct_qlen = nla_get_u32(tb[TCA_HTB_सूचीECT_QLEN]);
	अन्यथा
		q->direct_qlen = qdisc_dev(sch)->tx_queue_len;

	अगर ((q->rate2quantum = gopt->rate2quantum) < 1)
		q->rate2quantum = 1;
	q->defcls = gopt->defcls;

	अगर (!offload)
		वापस 0;

	क्रम (ntx = 0; ntx < q->num_direct_qdiscs; ntx++) अणु
		काष्ठा netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		काष्ठा Qdisc *qdisc;

		qdisc = qdisc_create_dflt(dev_queue, &pfअगरo_qdisc_ops,
					  TC_H_MAKE(sch->handle, 0), extack);
		अगर (!qdisc) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_qdiscs;
		पूर्ण

		htb_set_lockdep_class_child(qdisc);
		q->direct_qdiscs[ntx] = qdisc;
		qdisc->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	पूर्ण

	sch->flags |= TCQ_F_MQROOT;

	offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
		.command = TC_HTB_CREATE,
		.parent_classid = TC_H_MAJ(sch->handle) >> 16,
		.classid = TC_H_MIN(q->defcls),
		.extack = extack,
	पूर्ण;
	err = htb_offload(dev, &offload_opt);
	अगर (err)
		जाओ err_मुक्त_qdiscs;

	/* Defer this assignment, so that htb_destroy skips offload-related
	 * parts (especially calling nकरो_setup_tc) on errors.
	 */
	q->offload = true;

	वापस 0;

err_मुक्त_qdiscs:
	क्रम (ntx = 0; ntx < q->num_direct_qdiscs && q->direct_qdiscs[ntx];
	     ntx++)
		qdisc_put(q->direct_qdiscs[ntx]);

	qdisc_class_hash_destroy(&q->clhash);
	/* Prevent use-after-मुक्त and द्विगुन-मुक्त when htb_destroy माला_लो called.
	 */
	q->clhash.hash = शून्य;
	q->clhash.hashsize = 0;

err_मुक्त_direct_qdiscs:
	kमुक्त(q->direct_qdiscs);
	q->direct_qdiscs = शून्य;
	वापस err;
पूर्ण

अटल व्योम htb_attach_offload(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा htb_sched *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक ntx;

	क्रम (ntx = 0; ntx < q->num_direct_qdiscs; ntx++) अणु
		काष्ठा Qdisc *old, *qdisc = q->direct_qdiscs[ntx];

		old = dev_graft_qdisc(qdisc->dev_queue, qdisc);
		qdisc_put(old);
		qdisc_hash_add(qdisc, false);
	पूर्ण
	क्रम (ntx = q->num_direct_qdiscs; ntx < dev->num_tx_queues; ntx++) अणु
		काष्ठा netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		काष्ठा Qdisc *old = dev_graft_qdisc(dev_queue, शून्य);

		qdisc_put(old);
	पूर्ण

	kमुक्त(q->direct_qdiscs);
	q->direct_qdiscs = शून्य;
पूर्ण

अटल व्योम htb_attach_software(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित पूर्णांक ntx;

	/* Resemble qdisc_graft behavior. */
	क्रम (ntx = 0; ntx < dev->num_tx_queues; ntx++) अणु
		काष्ठा netdev_queue *dev_queue = netdev_get_tx_queue(dev, ntx);
		काष्ठा Qdisc *old = dev_graft_qdisc(dev_queue, sch);

		qdisc_refcount_inc(sch);

		qdisc_put(old);
	पूर्ण
पूर्ण

अटल व्योम htb_attach(काष्ठा Qdisc *sch)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);

	अगर (q->offload)
		htb_attach_offload(sch);
	अन्यथा
		htb_attach_software(sch);
पूर्ण

अटल पूर्णांक htb_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *nest;
	काष्ठा tc_htb_glob gopt;

	अगर (q->offload)
		sch->flags |= TCQ_F_OFFLOADED;
	अन्यथा
		sch->flags &= ~TCQ_F_OFFLOADED;

	sch->qstats.overlimits = q->overlimits;
	/* Its safe to not acquire qdisc lock. As we hold RTNL,
	 * no change can happen on the qdisc parameters.
	 */

	gopt.direct_pkts = q->direct_pkts;
	gopt.version = HTB_VER;
	gopt.rate2quantum = q->rate2quantum;
	gopt.defcls = q->defcls;
	gopt.debug = 0;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put(skb, TCA_HTB_INIT, माप(gopt), &gopt) ||
	    nla_put_u32(skb, TCA_HTB_सूचीECT_QLEN, q->direct_qlen))
		जाओ nla_put_failure;
	अगर (q->offload && nla_put_flag(skb, TCA_HTB_OFFLOAD))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक htb_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा nlattr *nest;
	काष्ठा tc_htb_opt opt;

	/* Its safe to not acquire qdisc lock. As we hold RTNL,
	 * no change can happen on the class parameters.
	 */
	tcm->tcm_parent = cl->parent ? cl->parent->common.classid : TC_H_ROOT;
	tcm->tcm_handle = cl->common.classid;
	अगर (!cl->level && cl->leaf.q)
		tcm->tcm_info = cl->leaf.q->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	स_रखो(&opt, 0, माप(opt));

	psched_ratecfg_getrate(&opt.rate, &cl->rate);
	opt.buffer = PSCHED_NS2TICKS(cl->buffer);
	psched_ratecfg_getrate(&opt.उच्चमान, &cl->उच्चमान);
	opt.cbuffer = PSCHED_NS2TICKS(cl->cbuffer);
	opt.quantum = cl->quantum;
	opt.prio = cl->prio;
	opt.level = cl->level;
	अगर (nla_put(skb, TCA_HTB_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;
	अगर (q->offload && nla_put_flag(skb, TCA_HTB_OFFLOAD))
		जाओ nla_put_failure;
	अगर ((cl->rate.rate_bytes_ps >= (1ULL << 32)) &&
	    nla_put_u64_64bit(skb, TCA_HTB_RATE64, cl->rate.rate_bytes_ps,
			      TCA_HTB_PAD))
		जाओ nla_put_failure;
	अगर ((cl->उच्चमान.rate_bytes_ps >= (1ULL << 32)) &&
	    nla_put_u64_64bit(skb, TCA_HTB_CEIL64, cl->उच्चमान.rate_bytes_ps,
			      TCA_HTB_PAD))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम htb_offload_aggregate_stats(काष्ठा htb_sched *q,
					काष्ठा htb_class *cl)
अणु
	काष्ठा htb_class *c;
	अचिन्हित पूर्णांक i;

	स_रखो(&cl->bstats, 0, माप(cl->bstats));

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(c, &q->clhash.hash[i], common.hnode) अणु
			काष्ठा htb_class *p = c;

			जबतक (p && p->level < cl->level)
				p = p->parent;

			अगर (p != cl)
				जारी;

			cl->bstats.bytes += c->bstats_bias.bytes;
			cl->bstats.packets += c->bstats_bias.packets;
			अगर (c->level == 0) अणु
				cl->bstats.bytes += c->leaf.q->bstats.bytes;
				cl->bstats.packets += c->leaf.q->bstats.packets;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
htb_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा gnet_dump *d)
अणु
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा gnet_stats_queue qs = अणु
		.drops = cl->drops,
		.overlimits = cl->overlimits,
	पूर्ण;
	__u32 qlen = 0;

	अगर (!cl->level && cl->leaf.q)
		qdisc_qstats_qlen_backlog(cl->leaf.q, &qlen, &qs.backlog);

	cl->xstats.tokens = clamp_t(s64, PSCHED_NS2TICKS(cl->tokens),
				    पूर्णांक_न्यून, पूर्णांक_उच्च);
	cl->xstats.ctokens = clamp_t(s64, PSCHED_NS2TICKS(cl->ctokens),
				     पूर्णांक_न्यून, पूर्णांक_उच्च);

	अगर (q->offload) अणु
		अगर (!cl->level) अणु
			अगर (cl->leaf.q)
				cl->bstats = cl->leaf.q->bstats;
			अन्यथा
				स_रखो(&cl->bstats, 0, माप(cl->bstats));
			cl->bstats.bytes += cl->bstats_bias.bytes;
			cl->bstats.packets += cl->bstats_bias.packets;
		पूर्ण अन्यथा अणु
			htb_offload_aggregate_stats(q, cl);
		पूर्ण
	पूर्ण

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, शून्य, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, शून्य, &qs, qlen) < 0)
		वापस -1;

	वापस gnet_stats_copy_app(d, &cl->xstats, माप(cl->xstats));
पूर्ण

अटल काष्ठा netdev_queue *
htb_select_queue(काष्ठा Qdisc *sch, काष्ठा tcmsg *tcm)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_htb_qopt_offload offload_opt;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	पूर्णांक err;

	अगर (!q->offload)
		वापस sch->dev_queue;

	offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
		.command = TC_HTB_LEAF_QUERY_QUEUE,
		.classid = TC_H_MIN(tcm->tcm_parent),
	पूर्ण;
	err = htb_offload(dev, &offload_opt);
	अगर (err || offload_opt.qid >= dev->num_tx_queues)
		वापस शून्य;
	वापस netdev_get_tx_queue(dev, offload_opt.qid);
पूर्ण

अटल काष्ठा Qdisc *
htb_graft_helper(काष्ठा netdev_queue *dev_queue, काष्ठा Qdisc *new_q)
अणु
	काष्ठा net_device *dev = dev_queue->dev;
	काष्ठा Qdisc *old_q;

	अगर (dev->flags & IFF_UP)
		dev_deactivate(dev);
	old_q = dev_graft_qdisc(dev_queue, new_q);
	अगर (new_q)
		new_q->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	अगर (dev->flags & IFF_UP)
		dev_activate(dev);

	वापस old_q;
पूर्ण

अटल व्योम htb_offload_move_qdisc(काष्ठा Qdisc *sch, u16 qid_old, u16 qid_new)
अणु
	काष्ठा netdev_queue *queue_old, *queue_new;
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा Qdisc *qdisc;

	queue_old = netdev_get_tx_queue(dev, qid_old);
	queue_new = netdev_get_tx_queue(dev, qid_new);

	अगर (dev->flags & IFF_UP)
		dev_deactivate(dev);
	qdisc = dev_graft_qdisc(queue_old, शून्य);
	qdisc->dev_queue = queue_new;
	qdisc = dev_graft_qdisc(queue_new, qdisc);
	अगर (dev->flags & IFF_UP)
		dev_activate(dev);

	WARN_ON(!(qdisc->flags & TCQ_F_BUILTIN));
पूर्ण

अटल पूर्णांक htb_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netdev_queue *dev_queue = sch->dev_queue;
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा Qdisc *old_q;

	अगर (cl->level)
		वापस -EINVAL;

	अगर (q->offload) अणु
		dev_queue = new->dev_queue;
		WARN_ON(dev_queue != cl->leaf.q->dev_queue);
	पूर्ण

	अगर (!new) अणु
		new = qdisc_create_dflt(dev_queue, &pfअगरo_qdisc_ops,
					cl->common.classid, extack);
		अगर (!new)
			वापस -ENOBUFS;
	पूर्ण

	अगर (q->offload) अणु
		htb_set_lockdep_class_child(new);
		/* One ref क्रम cl->leaf.q, the other क्रम dev_queue->qdisc. */
		qdisc_refcount_inc(new);
		old_q = htb_graft_helper(dev_queue, new);
	पूर्ण

	*old = qdisc_replace(sch, new, &cl->leaf.q);

	अगर (q->offload) अणु
		WARN_ON(old_q != *old);
		qdisc_put(old_q);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *htb_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;
	वापस !cl->level ? cl->leaf.q : शून्य;
पूर्ण

अटल व्योम htb_qlen_notअगरy(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;

	htb_deactivate(qdisc_priv(sch), cl);
पूर्ण

अटल अंतरभूत पूर्णांक htb_parent_last_child(काष्ठा htb_class *cl)
अणु
	अगर (!cl->parent)
		/* the root class */
		वापस 0;
	अगर (cl->parent->children > 1)
		/* not the last child */
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम htb_parent_to_leaf(काष्ठा Qdisc *sch, काष्ठा htb_class *cl,
			       काष्ठा Qdisc *new_q)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *parent = cl->parent;

	WARN_ON(cl->level || !cl->leaf.q || cl->prio_activity);

	अगर (parent->cmode != HTB_CAN_SEND)
		htb_safe_rb_erase(&parent->pq_node,
				  &q->hlevel[parent->level].रुको_pq);

	parent->level = 0;
	स_रखो(&parent->inner, 0, माप(parent->inner));
	parent->leaf.q = new_q ? new_q : &noop_qdisc;
	parent->tokens = parent->buffer;
	parent->ctokens = parent->cbuffer;
	parent->t_c = kसमय_get_ns();
	parent->cmode = HTB_CAN_SEND;
पूर्ण

अटल व्योम htb_parent_to_leaf_offload(काष्ठा Qdisc *sch,
				       काष्ठा netdev_queue *dev_queue,
				       काष्ठा Qdisc *new_q)
अणु
	काष्ठा Qdisc *old_q;

	/* One ref क्रम cl->leaf.q, the other क्रम dev_queue->qdisc. */
	अगर (new_q)
		qdisc_refcount_inc(new_q);
	old_q = htb_graft_helper(dev_queue, new_q);
	WARN_ON(!(old_q->flags & TCQ_F_BUILTIN));
पूर्ण

अटल पूर्णांक htb_destroy_class_offload(काष्ठा Qdisc *sch, काष्ठा htb_class *cl,
				     bool last_child, bool destroying,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_htb_qopt_offload offload_opt;
	काष्ठा Qdisc *q = cl->leaf.q;
	काष्ठा Qdisc *old = शून्य;
	पूर्णांक err;

	अगर (cl->level)
		वापस -EINVAL;

	WARN_ON(!q);
	अगर (!destroying) अणु
		/* On destroy of HTB, two हालs are possible:
		 * 1. q is a normal qdisc, but q->dev_queue has noop qdisc.
		 * 2. q is a noop qdisc (क्रम nodes that were inner),
		 *    q->dev_queue is noop_netdev_queue.
		 */
		old = htb_graft_helper(q->dev_queue, शून्य);
		WARN_ON(!old);
		WARN_ON(old != q);
	पूर्ण

	अगर (cl->parent) अणु
		cl->parent->bstats_bias.bytes += q->bstats.bytes;
		cl->parent->bstats_bias.packets += q->bstats.packets;
	पूर्ण

	offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
		.command = !last_child ? TC_HTB_LEAF_DEL :
			   destroying ? TC_HTB_LEAF_DEL_LAST_FORCE :
			   TC_HTB_LEAF_DEL_LAST,
		.classid = cl->common.classid,
		.extack = extack,
	पूर्ण;
	err = htb_offload(qdisc_dev(sch), &offload_opt);

	अगर (!err || destroying)
		qdisc_put(old);
	अन्यथा
		htb_graft_helper(q->dev_queue, old);

	अगर (last_child)
		वापस err;

	अगर (!err && offload_opt.moved_qid != 0) अणु
		अगर (destroying)
			q->dev_queue = netdev_get_tx_queue(qdisc_dev(sch),
							   offload_opt.qid);
		अन्यथा
			htb_offload_move_qdisc(sch, offload_opt.moved_qid,
					       offload_opt.qid);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम htb_destroy_class(काष्ठा Qdisc *sch, काष्ठा htb_class *cl)
अणु
	अगर (!cl->level) अणु
		WARN_ON(!cl->leaf.q);
		qdisc_put(cl->leaf.q);
	पूर्ण
	gen_समाप्त_estimator(&cl->rate_est);
	tcf_block_put(cl->block);
	kमुक्त(cl);
पूर्ण

अटल व्योम htb_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_htb_qopt_offload offload_opt;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा hlist_node *next;
	bool nonempty, changed;
	काष्ठा htb_class *cl;
	अचिन्हित पूर्णांक i;

	cancel_work_sync(&q->work);
	qdisc_watchकरोg_cancel(&q->watchकरोg);
	/* This line used to be after htb_destroy_class call below
	 * and surprisingly it worked in 2.4. But it must precede it
	 * because filter need its target class alive to be able to call
	 * unbind_filter on it (without Oops).
	 */
	tcf_block_put(q->block);

	क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[i], common.hnode) अणु
			tcf_block_put(cl->block);
			cl->block = शून्य;
		पूर्ण
	पूर्ण

	करो अणु
		nonempty = false;
		changed = false;
		क्रम (i = 0; i < q->clhash.hashsize; i++) अणु
			hlist_क्रम_each_entry_safe(cl, next, &q->clhash.hash[i],
						  common.hnode) अणु
				bool last_child;

				अगर (!q->offload) अणु
					htb_destroy_class(sch, cl);
					जारी;
				पूर्ण

				nonempty = true;

				अगर (cl->level)
					जारी;

				changed = true;

				last_child = htb_parent_last_child(cl);
				htb_destroy_class_offload(sch, cl, last_child,
							  true, शून्य);
				qdisc_class_hash_हटाओ(&q->clhash,
							&cl->common);
				अगर (cl->parent)
					cl->parent->children--;
				अगर (last_child)
					htb_parent_to_leaf(sch, cl, शून्य);
				htb_destroy_class(sch, cl);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (changed);
	WARN_ON(nonempty);

	qdisc_class_hash_destroy(&q->clhash);
	__qdisc_reset_queue(&q->direct_queue);

	अगर (!q->offload)
		वापस;

	offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
		.command = TC_HTB_DESTROY,
	पूर्ण;
	htb_offload(dev, &offload_opt);

	अगर (!q->direct_qdiscs)
		वापस;
	क्रम (i = 0; i < q->num_direct_qdiscs && q->direct_qdiscs[i]; i++)
		qdisc_put(q->direct_qdiscs[i]);
	kमुक्त(q->direct_qdiscs);
पूर्ण

अटल पूर्णांक htb_delete(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;
	काष्ठा Qdisc *new_q = शून्य;
	पूर्णांक last_child = 0;
	पूर्णांक err;

	/* TODO: why करोn't allow to delete subtree ? references ? करोes
	 * tc subsys guarantee us that in htb_destroy it holds no class
	 * refs so that we can हटाओ children safely there ?
	 */
	अगर (cl->children || cl->filter_cnt)
		वापस -EBUSY;

	अगर (!cl->level && htb_parent_last_child(cl))
		last_child = 1;

	अगर (q->offload) अणु
		err = htb_destroy_class_offload(sch, cl, last_child, false,
						extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (last_child) अणु
		काष्ठा netdev_queue *dev_queue;

		dev_queue = q->offload ? cl->leaf.q->dev_queue : sch->dev_queue;
		new_q = qdisc_create_dflt(dev_queue, &pfअगरo_qdisc_ops,
					  cl->parent->common.classid,
					  शून्य);
		अगर (q->offload) अणु
			अगर (new_q)
				htb_set_lockdep_class_child(new_q);
			htb_parent_to_leaf_offload(sch, dev_queue, new_q);
		पूर्ण
	पूर्ण

	sch_tree_lock(sch);

	अगर (!cl->level)
		qdisc_purge_queue(cl->leaf.q);

	/* delete from hash and active; reमुख्यder in destroy_class */
	qdisc_class_hash_हटाओ(&q->clhash, &cl->common);
	अगर (cl->parent)
		cl->parent->children--;

	अगर (cl->prio_activity)
		htb_deactivate(q, cl);

	अगर (cl->cmode != HTB_CAN_SEND)
		htb_safe_rb_erase(&cl->pq_node,
				  &q->hlevel[cl->level].रुको_pq);

	अगर (last_child)
		htb_parent_to_leaf(sch, cl, new_q);

	sch_tree_unlock(sch);

	htb_destroy_class(sch, cl);
	वापस 0;
पूर्ण

अटल पूर्णांक htb_change_class(काष्ठा Qdisc *sch, u32 classid,
			    u32 parentid, काष्ठा nlattr **tca,
			    अचिन्हित दीर्घ *arg, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl = (काष्ठा htb_class *)*arg, *parent;
	काष्ठा tc_htb_qopt_offload offload_opt;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_HTB_MAX + 1];
	काष्ठा Qdisc *parent_qdisc = शून्य;
	काष्ठा netdev_queue *dev_queue;
	काष्ठा tc_htb_opt *hopt;
	u64 rate64, उच्चमान64;
	पूर्णांक warn = 0;

	/* extract all subattrs from opt attr */
	अगर (!opt)
		जाओ failure;

	err = nla_parse_nested_deprecated(tb, TCA_HTB_MAX, opt, htb_policy,
					  शून्य);
	अगर (err < 0)
		जाओ failure;

	err = -EINVAL;
	अगर (tb[TCA_HTB_PARMS] == शून्य)
		जाओ failure;

	parent = parentid == TC_H_ROOT ? शून्य : htb_find(parentid, sch);

	hopt = nla_data(tb[TCA_HTB_PARMS]);
	अगर (!hopt->rate.rate || !hopt->उच्चमान.rate)
		जाओ failure;

	/* Keeping backward compatible with rate_table based iproute2 tc */
	अगर (hopt->rate.linklayer == TC_LINKLAYER_UNAWARE)
		qdisc_put_rtab(qdisc_get_rtab(&hopt->rate, tb[TCA_HTB_RTAB],
					      शून्य));

	अगर (hopt->उच्चमान.linklayer == TC_LINKLAYER_UNAWARE)
		qdisc_put_rtab(qdisc_get_rtab(&hopt->उच्चमान, tb[TCA_HTB_CTAB],
					      शून्य));

	rate64 = tb[TCA_HTB_RATE64] ? nla_get_u64(tb[TCA_HTB_RATE64]) : 0;
	उच्चमान64 = tb[TCA_HTB_CEIL64] ? nla_get_u64(tb[TCA_HTB_CEIL64]) : 0;

	अगर (!cl) अणु		/* new class */
		काष्ठा net_device *dev = qdisc_dev(sch);
		काष्ठा Qdisc *new_q, *old_q;
		पूर्णांक prio;
		काष्ठा अणु
			काष्ठा nlattr		nla;
			काष्ठा gnet_estimator	opt;
		पूर्ण est = अणु
			.nla = अणु
				.nla_len	= nla_attr_size(माप(est.opt)),
				.nla_type	= TCA_RATE,
			पूर्ण,
			.opt = अणु
				/* 4s पूर्णांकerval, 16s averaging स्थिरant */
				.पूर्णांकerval	= 2,
				.ewma_log	= 2,
			पूर्ण,
		पूर्ण;

		/* check क्रम valid classid */
		अगर (!classid || TC_H_MAJ(classid ^ sch->handle) ||
		    htb_find(classid, sch))
			जाओ failure;

		/* check maximal depth */
		अगर (parent && parent->parent && parent->parent->level < 2) अणु
			pr_err("htb: tree is too deep\n");
			जाओ failure;
		पूर्ण
		err = -ENOBUFS;
		cl = kzalloc(माप(*cl), GFP_KERNEL);
		अगर (!cl)
			जाओ failure;

		err = tcf_block_get(&cl->block, &cl->filter_list, sch, extack);
		अगर (err) अणु
			kमुक्त(cl);
			जाओ failure;
		पूर्ण
		अगर (htb_rate_est || tca[TCA_RATE]) अणु
			err = gen_new_estimator(&cl->bstats, शून्य,
						&cl->rate_est,
						शून्य,
						qdisc_root_sleeping_running(sch),
						tca[TCA_RATE] ? : &est.nla);
			अगर (err)
				जाओ err_block_put;
		पूर्ण

		cl->children = 0;
		RB_CLEAR_NODE(&cl->pq_node);

		क्रम (prio = 0; prio < TC_HTB_NUMPRIO; prio++)
			RB_CLEAR_NODE(&cl->node[prio]);

		cl->common.classid = classid;

		/* Make sure nothing पूर्णांकerrupts us in between of two
		 * nकरो_setup_tc calls.
		 */
		ASSERT_RTNL();

		/* create leaf qdisc early because it uses kदो_स्मृति(GFP_KERNEL)
		 * so that can't be used inside of sch_tree_lock
		 * -- thanks to Karlis Peisenieks
		 */
		अगर (!q->offload) अणु
			dev_queue = sch->dev_queue;
		पूर्ण अन्यथा अगर (!(parent && !parent->level)) अणु
			/* Assign a dev_queue to this classid. */
			offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
				.command = TC_HTB_LEAF_ALLOC_QUEUE,
				.classid = cl->common.classid,
				.parent_classid = parent ?
					TC_H_MIN(parent->common.classid) :
					TC_HTB_CLASSID_ROOT,
				.rate = max_t(u64, hopt->rate.rate, rate64),
				.उच्चमान = max_t(u64, hopt->उच्चमान.rate, उच्चमान64),
				.extack = extack,
			पूर्ण;
			err = htb_offload(dev, &offload_opt);
			अगर (err) अणु
				pr_err("htb: TC_HTB_LEAF_ALLOC_QUEUE failed with err = %d\n",
				       err);
				जाओ err_समाप्त_estimator;
			पूर्ण
			dev_queue = netdev_get_tx_queue(dev, offload_opt.qid);
		पूर्ण अन्यथा अणु /* First child. */
			dev_queue = parent->leaf.q->dev_queue;
			old_q = htb_graft_helper(dev_queue, शून्य);
			WARN_ON(old_q != parent->leaf.q);
			offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
				.command = TC_HTB_LEAF_TO_INNER,
				.classid = cl->common.classid,
				.parent_classid =
					TC_H_MIN(parent->common.classid),
				.rate = max_t(u64, hopt->rate.rate, rate64),
				.उच्चमान = max_t(u64, hopt->उच्चमान.rate, उच्चमान64),
				.extack = extack,
			पूर्ण;
			err = htb_offload(dev, &offload_opt);
			अगर (err) अणु
				pr_err("htb: TC_HTB_LEAF_TO_INNER failed with err = %d\n",
				       err);
				htb_graft_helper(dev_queue, old_q);
				जाओ err_समाप्त_estimator;
			पूर्ण
			parent->bstats_bias.bytes += old_q->bstats.bytes;
			parent->bstats_bias.packets += old_q->bstats.packets;
			qdisc_put(old_q);
		पूर्ण
		new_q = qdisc_create_dflt(dev_queue, &pfअगरo_qdisc_ops,
					  classid, शून्य);
		अगर (q->offload) अणु
			अगर (new_q) अणु
				htb_set_lockdep_class_child(new_q);
				/* One ref क्रम cl->leaf.q, the other क्रम
				 * dev_queue->qdisc.
				 */
				qdisc_refcount_inc(new_q);
			पूर्ण
			old_q = htb_graft_helper(dev_queue, new_q);
			/* No qdisc_put needed. */
			WARN_ON(!(old_q->flags & TCQ_F_BUILTIN));
		पूर्ण
		sch_tree_lock(sch);
		अगर (parent && !parent->level) अणु
			/* turn parent पूर्णांकo inner node */
			qdisc_purge_queue(parent->leaf.q);
			parent_qdisc = parent->leaf.q;
			अगर (parent->prio_activity)
				htb_deactivate(q, parent);

			/* हटाओ from evt list because of level change */
			अगर (parent->cmode != HTB_CAN_SEND) अणु
				htb_safe_rb_erase(&parent->pq_node, &q->hlevel[0].रुको_pq);
				parent->cmode = HTB_CAN_SEND;
			पूर्ण
			parent->level = (parent->parent ? parent->parent->level
					 : TC_HTB_MAXDEPTH) - 1;
			स_रखो(&parent->inner, 0, माप(parent->inner));
		पूर्ण

		/* leaf (we) needs elementary qdisc */
		cl->leaf.q = new_q ? new_q : &noop_qdisc;

		cl->parent = parent;

		/* set class to be in HTB_CAN_SEND state */
		cl->tokens = PSCHED_TICKS2NS(hopt->buffer);
		cl->ctokens = PSCHED_TICKS2NS(hopt->cbuffer);
		cl->mbuffer = 60ULL * NSEC_PER_SEC;	/* 1min */
		cl->t_c = kसमय_get_ns();
		cl->cmode = HTB_CAN_SEND;

		/* attach to the hash list and parent's family */
		qdisc_class_hash_insert(&q->clhash, &cl->common);
		अगर (parent)
			parent->children++;
		अगर (cl->leaf.q != &noop_qdisc)
			qdisc_hash_add(cl->leaf.q, true);
	पूर्ण अन्यथा अणु
		अगर (tca[TCA_RATE]) अणु
			err = gen_replace_estimator(&cl->bstats, शून्य,
						    &cl->rate_est,
						    शून्य,
						    qdisc_root_sleeping_running(sch),
						    tca[TCA_RATE]);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (q->offload) अणु
			काष्ठा net_device *dev = qdisc_dev(sch);

			offload_opt = (काष्ठा tc_htb_qopt_offload) अणु
				.command = TC_HTB_NODE_MODIFY,
				.classid = cl->common.classid,
				.rate = max_t(u64, hopt->rate.rate, rate64),
				.उच्चमान = max_t(u64, hopt->उच्चमान.rate, उच्चमान64),
				.extack = extack,
			पूर्ण;
			err = htb_offload(dev, &offload_opt);
			अगर (err)
				/* Estimator was replaced, and rollback may fail
				 * as well, so we करोn't try to recover it, and
				 * the estimator won't work property with the
				 * offload anyway, because bstats are updated
				 * only when the stats are queried.
				 */
				वापस err;
		पूर्ण

		sch_tree_lock(sch);
	पूर्ण

	psched_ratecfg_precompute(&cl->rate, &hopt->rate, rate64);
	psched_ratecfg_precompute(&cl->उच्चमान, &hopt->उच्चमान, उच्चमान64);

	/* it used to be a nasty bug here, we have to check that node
	 * is really leaf beक्रमe changing cl->leaf !
	 */
	अगर (!cl->level) अणु
		u64 quantum = cl->rate.rate_bytes_ps;

		करो_भाग(quantum, q->rate2quantum);
		cl->quantum = min_t(u64, quantum, पूर्णांक_उच्च);

		अगर (!hopt->quantum && cl->quantum < 1000) अणु
			warn = -1;
			cl->quantum = 1000;
		पूर्ण
		अगर (!hopt->quantum && cl->quantum > 200000) अणु
			warn = 1;
			cl->quantum = 200000;
		पूर्ण
		अगर (hopt->quantum)
			cl->quantum = hopt->quantum;
		अगर ((cl->prio = hopt->prio) >= TC_HTB_NUMPRIO)
			cl->prio = TC_HTB_NUMPRIO - 1;
	पूर्ण

	cl->buffer = PSCHED_TICKS2NS(hopt->buffer);
	cl->cbuffer = PSCHED_TICKS2NS(hopt->cbuffer);

	sch_tree_unlock(sch);
	qdisc_put(parent_qdisc);

	अगर (warn)
		pr_warn("HTB: quantum of class %X is %s. Consider r2q change.\n",
			    cl->common.classid, (warn == -1 ? "small" : "big"));

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (अचिन्हित दीर्घ)cl;
	वापस 0;

err_समाप्त_estimator:
	gen_समाप्त_estimator(&cl->rate_est);
err_block_put:
	tcf_block_put(cl->block);
	kमुक्त(cl);
failure:
	वापस err;
पूर्ण

अटल काष्ठा tcf_block *htb_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;

	वापस cl ? cl->block : q->block;
पूर्ण

अटल अचिन्हित दीर्घ htb_bind_filter(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
				     u32 classid)
अणु
	काष्ठा htb_class *cl = htb_find(classid, sch);

	/*अगर (cl && !cl->level) वापस 0;
	 * The line above used to be there to prevent attaching filters to
	 * leaves. But at least tc_index filter uses this just to get class
	 * क्रम other reasons so that we have to allow क्रम it.
	 * ----
	 * 19.6.2002 As Werner explained it is ok - bind filter is just
	 * another way to "lock" the class - unlike "get" this lock can
	 * be broken by class during destroy IIUC.
	 */
	अगर (cl)
		cl->filter_cnt++;
	वापस (अचिन्हित दीर्घ)cl;
पूर्ण

अटल व्योम htb_unbind_filter(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा htb_class *cl = (काष्ठा htb_class *)arg;

	अगर (cl)
		cl->filter_cnt--;
पूर्ण

अटल व्योम htb_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा htb_sched *q = qdisc_priv(sch);
	काष्ठा htb_class *cl;
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

अटल स्थिर काष्ठा Qdisc_class_ops htb_class_ops = अणु
	.select_queue	=	htb_select_queue,
	.graft		=	htb_graft,
	.leaf		=	htb_leaf,
	.qlen_notअगरy	=	htb_qlen_notअगरy,
	.find		=	htb_search,
	.change		=	htb_change_class,
	.delete		=	htb_delete,
	.walk		=	htb_walk,
	.tcf_block	=	htb_tcf_block,
	.bind_tcf	=	htb_bind_filter,
	.unbind_tcf	=	htb_unbind_filter,
	.dump		=	htb_dump_class,
	.dump_stats	=	htb_dump_class_stats,
पूर्ण;

अटल काष्ठा Qdisc_ops htb_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		=	&htb_class_ops,
	.id		=	"htb",
	.priv_size	=	माप(काष्ठा htb_sched),
	.enqueue	=	htb_enqueue,
	.dequeue	=	htb_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	htb_init,
	.attach		=	htb_attach,
	.reset		=	htb_reset,
	.destroy	=	htb_destroy,
	.dump		=	htb_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init htb_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&htb_qdisc_ops);
पूर्ण
अटल व्योम __निकास htb_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&htb_qdisc_ops);
पूर्ण

module_init(htb_module_init)
module_निकास(htb_module_निकास)
MODULE_LICENSE("GPL");
