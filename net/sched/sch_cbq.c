<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_cbq.c	Class-Based Queueing discipline.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>


/*	Class-Based Queueing (CBQ) algorithm.
	=======================================

	Sources: [1] Sally Floyd and Van Jacobson, "Link-sharing and Resource
		 Management Models क्रम Packet Networks",
		 IEEE/ACM Transactions on Networking, Vol.3, No.4, 1995

		 [2] Sally Floyd, "Notes on CBQ and Guaranteed Service", 1995

		 [3] Sally Floyd, "Notes on Class-Based Queueing: Setting
		 Parameters", 1996

		 [4] Sally Floyd and Michael Speer, "Experimental Results
		 क्रम Class-Based Queueing", 1998, not published.

	-----------------------------------------------------------------------

	Algorithm skeleton was taken from NS simulator cbq.cc.
	If someone wants to check this code against the LBL version,
	he should take पूर्णांकo account that ONLY the skeleton was borrowed,
	the implementation is dअगरferent. Particularly:

	--- The WRR algorithm is dअगरferent. Our version looks more
	reasonable (I hope) and works when quanta are allowed to be
	less than MTU, which is always the हाल when real समय classes
	have small rates. Note, that the statement of [3] is
	incomplete, delay may actually be estimated even अगर class
	per-round alloपंचांगent is less than MTU. Namely, अगर per-round
	alloपंचांगent is W*r_i, and r_1+...+r_k = r < 1

	delay_i <= ([MTU/(W*r_i)]*W*r + W*r + k*MTU)/B

	In the worst हाल we have IntServ estimate with D = W*r+k*MTU
	and C = MTU*r. The proof (अगर correct at all) is trivial.


	--- It seems that cbq-2.0 is not very accurate. At least, I cannot
	पूर्णांकerpret some places, which look like wrong translations
	from NS. Anyone is advised to find these dअगरferences
	and explain to me, why I am wrong 8).

	--- Linux has no EOI event, so that we cannot estimate true class
	idle समय. Workaround is to consider the next dequeue event
	as sign that previous packet is finished. This is wrong because of
	पूर्णांकernal device queueing, but on a permanently loaded link it is true.
	Moreover, combined with घड़ी पूर्णांकegrator, this scheme looks
	very बंद to an ideal solution.  */

काष्ठा cbq_sched_data;


काष्ठा cbq_class अणु
	काष्ठा Qdisc_class_common common;
	काष्ठा cbq_class	*next_alive;	/* next class with backlog in this priority band */

/* Parameters */
	अचिन्हित अक्षर		priority;	/* class priority */
	अचिन्हित अक्षर		priority2;	/* priority to be used after overlimit */
	अचिन्हित अक्षर		ewma_log;	/* समय स्थिरant क्रम idle समय calculation */

	u32			defmap;

	/* Link-sharing scheduler parameters */
	दीर्घ			maxidle;	/* Class parameters: see below. */
	दीर्घ			offसमय;
	दीर्घ			minidle;
	u32			avpkt;
	काष्ठा qdisc_rate_table	*R_tab;

	/* General scheduler (WRR) parameters */
	दीर्घ			allot;
	दीर्घ			quantum;	/* Alloपंचांगent per WRR round */
	दीर्घ			weight;		/* Relative alloपंचांगent: see below */

	काष्ठा Qdisc		*qdisc;		/* Ptr to CBQ discipline */
	काष्ठा cbq_class	*split;		/* Ptr to split node */
	काष्ठा cbq_class	*share;		/* Ptr to LS parent in the class tree */
	काष्ठा cbq_class	*tparent;	/* Ptr to tree parent in the class tree */
	काष्ठा cbq_class	*borrow;	/* शून्य अगर class is bandwidth limited;
						   parent otherwise */
	काष्ठा cbq_class	*sibling;	/* Sibling chain */
	काष्ठा cbq_class	*children;	/* Poपूर्णांकer to children chain */

	काष्ठा Qdisc		*q;		/* Elementary queueing discipline */


/* Variables */
	अचिन्हित अक्षर		cpriority;	/* Effective priority */
	अचिन्हित अक्षर		delayed;
	अचिन्हित अक्षर		level;		/* level of the class in hierarchy:
						   0 क्रम leaf classes, and maximal
						   level of children + 1 क्रम nodes.
						 */

	psched_समय_प्रकार		last;		/* Last end of service */
	psched_समय_प्रकार		underसमय;
	दीर्घ			avgidle;
	दीर्घ			deficit;	/* Saved deficit क्रम WRR */
	psched_समय_प्रकार		penalized;
	काष्ठा gnet_stats_basic_packed bstats;
	काष्ठा gnet_stats_queue qstats;
	काष्ठा net_rate_estimator __rcu *rate_est;
	काष्ठा tc_cbq_xstats	xstats;

	काष्ठा tcf_proto __rcu	*filter_list;
	काष्ठा tcf_block	*block;

	पूर्णांक			filters;

	काष्ठा cbq_class	*शेषs[TC_PRIO_MAX + 1];
पूर्ण;

काष्ठा cbq_sched_data अणु
	काष्ठा Qdisc_class_hash	clhash;			/* Hash table of all classes */
	पूर्णांक			nclasses[TC_CBQ_MAXPRIO + 1];
	अचिन्हित पूर्णांक		quanta[TC_CBQ_MAXPRIO + 1];

	काष्ठा cbq_class	link;

	अचिन्हित पूर्णांक		activemask;
	काष्ठा cbq_class	*active[TC_CBQ_MAXPRIO + 1];	/* List of all classes
								   with backlog */

#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा cbq_class	*rx_class;
#पूर्ण_अगर
	काष्ठा cbq_class	*tx_class;
	काष्ठा cbq_class	*tx_borrowed;
	पूर्णांक			tx_len;
	psched_समय_प्रकार		now;		/* Cached बारtamp */
	अचिन्हित पूर्णांक		pmask;

	काष्ठा hrसमयr		delay_समयr;
	काष्ठा qdisc_watchकरोg	watchकरोg;	/* Watchकरोg समयr,
						   started when CBQ has
						   backlog, but cannot
						   transmit just now */
	psched_tdअगरf_t		wd_expires;
	पूर्णांक			toplevel;
	u32			hgenerator;
पूर्ण;


#घोषणा L2T(cl, len)	qdisc_l2t((cl)->R_tab, len)

अटल अंतरभूत काष्ठा cbq_class *
cbq_class_lookup(काष्ठा cbq_sched_data *q, u32 classid)
अणु
	काष्ठा Qdisc_class_common *clc;

	clc = qdisc_class_find(&q->clhash, classid);
	अगर (clc == शून्य)
		वापस शून्य;
	वापस container_of(clc, काष्ठा cbq_class, common);
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT

अटल काष्ठा cbq_class *
cbq_reclassअगरy(काष्ठा sk_buff *skb, काष्ठा cbq_class *this)
अणु
	काष्ठा cbq_class *cl;

	क्रम (cl = this->tparent; cl; cl = cl->tparent) अणु
		काष्ठा cbq_class *new = cl->शेषs[TC_PRIO_BESTEFFORT];

		अगर (new != शून्य && new != this)
			वापस new;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

/* Classअगरy packet. The procedure is pretty complicated, but
 * it allows us to combine link sharing and priority scheduling
 * transparently.
 *
 * Namely, you can put link sharing rules (f.e. route based) at root of CBQ,
 * so that it resolves to split nodes. Then packets are classअगरied
 * by logical priority, or a more specअगरic classअगरier may be attached
 * to the split node.
 */

अटल काष्ठा cbq_class *
cbq_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, पूर्णांक *qerr)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *head = &q->link;
	काष्ठा cbq_class **defmap;
	काष्ठा cbq_class *cl = शून्य;
	u32 prio = skb->priority;
	काष्ठा tcf_proto *fl;
	काष्ठा tcf_result res;

	/*
	 *  Step 1. If skb->priority poपूर्णांकs to one of our classes, use it.
	 */
	अगर (TC_H_MAJ(prio ^ sch->handle) == 0 &&
	    (cl = cbq_class_lookup(q, prio)) != शून्य)
		वापस cl;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	क्रम (;;) अणु
		पूर्णांक result = 0;
		defmap = head->शेषs;

		fl = rcu_dereference_bh(head->filter_list);
		/*
		 * Step 2+n. Apply classअगरier.
		 */
		result = tcf_classअगरy(skb, fl, &res, true);
		अगर (!fl || result < 0)
			जाओ fallback;

		cl = (व्योम *)res.class;
		अगर (!cl) अणु
			अगर (TC_H_MAJ(res.classid))
				cl = cbq_class_lookup(q, res.classid);
			अन्यथा अगर ((cl = defmap[res.classid & TC_PRIO_MAX]) == शून्य)
				cl = defmap[TC_PRIO_BESTEFFORT];

			अगर (cl == शून्य)
				जाओ fallback;
		पूर्ण
		अगर (cl->level >= head->level)
			जाओ fallback;
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस शून्य;
		हाल TC_ACT_RECLASSIFY:
			वापस cbq_reclassअगरy(skb, cl);
		पूर्ण
#पूर्ण_अगर
		अगर (cl->level == 0)
			वापस cl;

		/*
		 * Step 3+n. If classअगरier selected a link sharing class,
		 *	   apply agency specअगरic classअगरier.
		 *	   Repeat this procedure until we hit a leaf node.
		 */
		head = cl;
	पूर्ण

fallback:
	cl = head;

	/*
	 * Step 4. No success...
	 */
	अगर (TC_H_MAJ(prio) == 0 &&
	    !(cl = head->शेषs[prio & TC_PRIO_MAX]) &&
	    !(cl = head->शेषs[TC_PRIO_BESTEFFORT]))
		वापस head;

	वापस cl;
पूर्ण

/*
 * A packet has just been enqueued on the empty class.
 * cbq_activate_class adds it to the tail of active class list
 * of its priority band.
 */

अटल अंतरभूत व्योम cbq_activate_class(काष्ठा cbq_class *cl)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(cl->qdisc);
	पूर्णांक prio = cl->cpriority;
	काष्ठा cbq_class *cl_tail;

	cl_tail = q->active[prio];
	q->active[prio] = cl;

	अगर (cl_tail != शून्य) अणु
		cl->next_alive = cl_tail->next_alive;
		cl_tail->next_alive = cl;
	पूर्ण अन्यथा अणु
		cl->next_alive = cl;
		q->activemask |= (1<<prio);
	पूर्ण
पूर्ण

/*
 * Unlink class from active chain.
 * Note that this same procedure is करोne directly in cbq_dequeue*
 * during round-robin procedure.
 */

अटल व्योम cbq_deactivate_class(काष्ठा cbq_class *this)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(this->qdisc);
	पूर्णांक prio = this->cpriority;
	काष्ठा cbq_class *cl;
	काष्ठा cbq_class *cl_prev = q->active[prio];

	करो अणु
		cl = cl_prev->next_alive;
		अगर (cl == this) अणु
			cl_prev->next_alive = cl->next_alive;
			cl->next_alive = शून्य;

			अगर (cl == q->active[prio]) अणु
				q->active[prio] = cl_prev;
				अगर (cl == q->active[prio]) अणु
					q->active[prio] = शून्य;
					q->activemask &= ~(1<<prio);
					वापस;
				पूर्ण
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण जबतक ((cl_prev = cl) != q->active[prio]);
पूर्ण

अटल व्योम
cbq_mark_toplevel(काष्ठा cbq_sched_data *q, काष्ठा cbq_class *cl)
अणु
	पूर्णांक toplevel = q->toplevel;

	अगर (toplevel > cl->level) अणु
		psched_समय_प्रकार now = psched_get_समय();

		करो अणु
			अगर (cl->underसमय < now) अणु
				q->toplevel = cl->level;
				वापस;
			पूर्ण
		पूर्ण जबतक ((cl = cl->borrow) != शून्य && toplevel > cl->level);
	पूर्ण
पूर्ण

अटल पूर्णांक
cbq_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
	    काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	पूर्णांक ret;
	काष्ठा cbq_class *cl = cbq_classअगरy(skb, sch, &ret);

#अगर_घोषित CONFIG_NET_CLS_ACT
	q->rx_class = cl;
#पूर्ण_अगर
	अगर (cl == शून्य) अणु
		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
	पूर्ण

	ret = qdisc_enqueue(skb, cl->q, to_मुक्त);
	अगर (ret == NET_XMIT_SUCCESS) अणु
		sch->q.qlen++;
		cbq_mark_toplevel(q, cl);
		अगर (!cl->next_alive)
			cbq_activate_class(cl);
		वापस ret;
	पूर्ण

	अगर (net_xmit_drop_count(ret)) अणु
		qdisc_qstats_drop(sch);
		cbq_mark_toplevel(q, cl);
		cl->qstats.drops++;
	पूर्ण
	वापस ret;
पूर्ण

/* Overlimit action: penalize leaf class by adding offसमय */
अटल व्योम cbq_overlimit(काष्ठा cbq_class *cl)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(cl->qdisc);
	psched_tdअगरf_t delay = cl->underसमय - q->now;

	अगर (!cl->delayed) अणु
		delay += cl->offसमय;

		/*
		 * Class goes to sleep, so that it will have no
		 * chance to work avgidle. Let's क्रमgive it 8)
		 *
		 * BTW cbq-2.0 has a crap in this
		 * place, apparently they क्रमgot to shअगरt it by cl->ewma_log.
		 */
		अगर (cl->avgidle < 0)
			delay -= (-cl->avgidle) - ((-cl->avgidle) >> cl->ewma_log);
		अगर (cl->avgidle < cl->minidle)
			cl->avgidle = cl->minidle;
		अगर (delay <= 0)
			delay = 1;
		cl->underसमय = q->now + delay;

		cl->xstats.overactions++;
		cl->delayed = 1;
	पूर्ण
	अगर (q->wd_expires == 0 || q->wd_expires > delay)
		q->wd_expires = delay;

	/* Dirty work! We must schedule wakeups based on
	 * real available rate, rather than leaf rate,
	 * which may be tiny (even zero).
	 */
	अगर (q->toplevel == TC_CBQ_MAXLEVEL) अणु
		काष्ठा cbq_class *b;
		psched_tdअगरf_t base_delay = q->wd_expires;

		क्रम (b = cl->borrow; b; b = b->borrow) अणु
			delay = b->underसमय - q->now;
			अगर (delay < base_delay) अणु
				अगर (delay <= 0)
					delay = 1;
				base_delay = delay;
			पूर्ण
		पूर्ण

		q->wd_expires = base_delay;
	पूर्ण
पूर्ण

अटल psched_tdअगरf_t cbq_undelay_prio(काष्ठा cbq_sched_data *q, पूर्णांक prio,
				       psched_समय_प्रकार now)
अणु
	काष्ठा cbq_class *cl;
	काष्ठा cbq_class *cl_prev = q->active[prio];
	psched_समय_प्रकार sched = now;

	अगर (cl_prev == शून्य)
		वापस 0;

	करो अणु
		cl = cl_prev->next_alive;
		अगर (now - cl->penalized > 0) अणु
			cl_prev->next_alive = cl->next_alive;
			cl->next_alive = शून्य;
			cl->cpriority = cl->priority;
			cl->delayed = 0;
			cbq_activate_class(cl);

			अगर (cl == q->active[prio]) अणु
				q->active[prio] = cl_prev;
				अगर (cl == q->active[prio]) अणु
					q->active[prio] = शून्य;
					वापस 0;
				पूर्ण
			पूर्ण

			cl = cl_prev->next_alive;
		पूर्ण अन्यथा अगर (sched - cl->penalized > 0)
			sched = cl->penalized;
	पूर्ण जबतक ((cl_prev = cl) != q->active[prio]);

	वापस sched - now;
पूर्ण

अटल क्रमागत hrसमयr_restart cbq_undelay(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा cbq_sched_data *q = container_of(समयr, काष्ठा cbq_sched_data,
						delay_समयr);
	काष्ठा Qdisc *sch = q->watchकरोg.qdisc;
	psched_समय_प्रकार now;
	psched_tdअगरf_t delay = 0;
	अचिन्हित पूर्णांक pmask;

	now = psched_get_समय();

	pmask = q->pmask;
	q->pmask = 0;

	जबतक (pmask) अणु
		पूर्णांक prio = ffz(~pmask);
		psched_tdअगरf_t पंचांगp;

		pmask &= ~(1<<prio);

		पंचांगp = cbq_undelay_prio(q, prio, now);
		अगर (पंचांगp > 0) अणु
			q->pmask |= 1<<prio;
			अगर (पंचांगp < delay || delay == 0)
				delay = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (delay) अणु
		kसमय_प्रकार समय;

		समय = 0;
		समय = kसमय_add_ns(समय, PSCHED_TICKS2NS(now + delay));
		hrसमयr_start(&q->delay_समयr, समय, HRTIMER_MODE_ABS_PINNED);
	पूर्ण

	__netअगर_schedule(qdisc_root(sch));
	वापस HRTIMER_NORESTART;
पूर्ण

/*
 * It is mission critical procedure.
 *
 * We "regenerate" toplevel cutoff, अगर transmitting class
 * has backlog and it is not regulated. It is not part of
 * original CBQ description, but looks more reasonable.
 * Probably, it is wrong. This question needs further investigation.
 */

अटल अंतरभूत व्योम
cbq_update_toplevel(काष्ठा cbq_sched_data *q, काष्ठा cbq_class *cl,
		    काष्ठा cbq_class *borrowed)
अणु
	अगर (cl && q->toplevel >= borrowed->level) अणु
		अगर (cl->q->q.qlen > 1) अणु
			करो अणु
				अगर (borrowed->underसमय == PSCHED_PASTPERFECT) अणु
					q->toplevel = borrowed->level;
					वापस;
				पूर्ण
			पूर्ण जबतक ((borrowed = borrowed->borrow) != शून्य);
		पूर्ण
#अगर 0
	/* It is not necessary now. Uncommenting it
	   will save CPU cycles, but decrease fairness.
	 */
		q->toplevel = TC_CBQ_MAXLEVEL;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम
cbq_update(काष्ठा cbq_sched_data *q)
अणु
	काष्ठा cbq_class *this = q->tx_class;
	काष्ठा cbq_class *cl = this;
	पूर्णांक len = q->tx_len;
	psched_समय_प्रकार now;

	q->tx_class = शून्य;
	/* Time पूर्णांकegrator. We calculate EOS समय
	 * by adding expected packet transmission समय.
	 */
	now = q->now + L2T(&q->link, len);

	क्रम ( ; cl; cl = cl->share) अणु
		दीर्घ avgidle = cl->avgidle;
		दीर्घ idle;

		cl->bstats.packets++;
		cl->bstats.bytes += len;

		/*
		 * (now - last) is total समय between packet right edges.
		 * (last_pktlen/rate) is "virtual" busy समय, so that
		 *
		 *	idle = (now - last) - last_pktlen/rate
		 */

		idle = now - cl->last;
		अगर ((अचिन्हित दीर्घ)idle > 128*1024*1024) अणु
			avgidle = cl->maxidle;
		पूर्ण अन्यथा अणु
			idle -= L2T(cl, len);

		/* true_avgidle := (1-W)*true_avgidle + W*idle,
		 * where W=2^अणु-ewma_logपूर्ण. But cl->avgidle is scaled:
		 * cl->avgidle == true_avgidle/W,
		 * hence:
		 */
			avgidle += idle - (avgidle>>cl->ewma_log);
		पूर्ण

		अगर (avgidle <= 0) अणु
			/* Overlimit or at-limit */

			अगर (avgidle < cl->minidle)
				avgidle = cl->minidle;

			cl->avgidle = avgidle;

			/* Calculate expected समय, when this class
			 * will be allowed to send.
			 * It will occur, when:
			 * (1-W)*true_avgidle + W*delay = 0, i.e.
			 * idle = (1/W - 1)*(-true_avgidle)
			 * or
			 * idle = (1 - W)*(-cl->avgidle);
			 */
			idle = (-avgidle) - ((-avgidle) >> cl->ewma_log);

			/*
			 * That is not all.
			 * To मुख्यtain the rate allocated to the class,
			 * we add to underसमय भव घड़ी,
			 * necessary to complete transmitted packet.
			 * (len/phys_bandwidth has been alपढ़ोy passed
			 * to the moment of cbq_update)
			 */

			idle -= L2T(&q->link, len);
			idle += L2T(cl, len);

			cl->underसमय = now + idle;
		पूर्ण अन्यथा अणु
			/* Underlimit */

			cl->underसमय = PSCHED_PASTPERFECT;
			अगर (avgidle > cl->maxidle)
				cl->avgidle = cl->maxidle;
			अन्यथा
				cl->avgidle = avgidle;
		पूर्ण
		अगर ((s64)(now - cl->last) > 0)
			cl->last = now;
	पूर्ण

	cbq_update_toplevel(q, this, q->tx_borrowed);
पूर्ण

अटल अंतरभूत काष्ठा cbq_class *
cbq_under_limit(काष्ठा cbq_class *cl)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(cl->qdisc);
	काष्ठा cbq_class *this_cl = cl;

	अगर (cl->tparent == शून्य)
		वापस cl;

	अगर (cl->underसमय == PSCHED_PASTPERFECT || q->now >= cl->underसमय) अणु
		cl->delayed = 0;
		वापस cl;
	पूर्ण

	करो अणु
		/* It is very suspicious place. Now overlimit
		 * action is generated क्रम not bounded classes
		 * only अगर link is completely congested.
		 * Though it is in agree with ancestor-only paradigm,
		 * it looks very stupid. Particularly,
		 * it means that this chunk of code will either
		 * never be called or result in strong amplअगरication
		 * of burstiness. Dangerous, silly, and, however,
		 * no another solution exists.
		 */
		cl = cl->borrow;
		अगर (!cl) अणु
			this_cl->qstats.overlimits++;
			cbq_overlimit(this_cl);
			वापस शून्य;
		पूर्ण
		अगर (cl->level > q->toplevel)
			वापस शून्य;
	पूर्ण जबतक (cl->underसमय != PSCHED_PASTPERFECT && q->now < cl->underसमय);

	cl->delayed = 0;
	वापस cl;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
cbq_dequeue_prio(काष्ठा Qdisc *sch, पूर्णांक prio)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl_tail, *cl_prev, *cl;
	काष्ठा sk_buff *skb;
	पूर्णांक deficit;

	cl_tail = cl_prev = q->active[prio];
	cl = cl_prev->next_alive;

	करो अणु
		deficit = 0;

		/* Start round */
		करो अणु
			काष्ठा cbq_class *borrow = cl;

			अगर (cl->q->q.qlen &&
			    (borrow = cbq_under_limit(cl)) == शून्य)
				जाओ skip_class;

			अगर (cl->deficit <= 0) अणु
				/* Class exhausted its alloपंचांगent per
				 * this round. Switch to the next one.
				 */
				deficit = 1;
				cl->deficit += cl->quantum;
				जाओ next_class;
			पूर्ण

			skb = cl->q->dequeue(cl->q);

			/* Class did not give us any skb :-(
			 * It could occur even अगर cl->q->q.qlen != 0
			 * f.e. अगर cl->q == "tbf"
			 */
			अगर (skb == शून्य)
				जाओ skip_class;

			cl->deficit -= qdisc_pkt_len(skb);
			q->tx_class = cl;
			q->tx_borrowed = borrow;
			अगर (borrow != cl) अणु
#अगर_अघोषित CBQ_XSTATS_BORROWS_BYTES
				borrow->xstats.borrows++;
				cl->xstats.borrows++;
#अन्यथा
				borrow->xstats.borrows += qdisc_pkt_len(skb);
				cl->xstats.borrows += qdisc_pkt_len(skb);
#पूर्ण_अगर
			पूर्ण
			q->tx_len = qdisc_pkt_len(skb);

			अगर (cl->deficit <= 0) अणु
				q->active[prio] = cl;
				cl = cl->next_alive;
				cl->deficit += cl->quantum;
			पूर्ण
			वापस skb;

skip_class:
			अगर (cl->q->q.qlen == 0 || prio != cl->cpriority) अणु
				/* Class is empty or penalized.
				 * Unlink it from active chain.
				 */
				cl_prev->next_alive = cl->next_alive;
				cl->next_alive = शून्य;

				/* Did cl_tail poपूर्णांक to it? */
				अगर (cl == cl_tail) अणु
					/* Repair it! */
					cl_tail = cl_prev;

					/* Was it the last class in this band? */
					अगर (cl == cl_tail) अणु
						/* Kill the band! */
						q->active[prio] = शून्य;
						q->activemask &= ~(1<<prio);
						अगर (cl->q->q.qlen)
							cbq_activate_class(cl);
						वापस शून्य;
					पूर्ण

					q->active[prio] = cl_tail;
				पूर्ण
				अगर (cl->q->q.qlen)
					cbq_activate_class(cl);

				cl = cl_prev;
			पूर्ण

next_class:
			cl_prev = cl;
			cl = cl->next_alive;
		पूर्ण जबतक (cl_prev != cl_tail);
	पूर्ण जबतक (deficit);

	q->active[prio] = cl_prev;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
cbq_dequeue_1(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक activemask;

	activemask = q->activemask & 0xFF;
	जबतक (activemask) अणु
		पूर्णांक prio = ffz(~activemask);
		activemask &= ~(1<<prio);
		skb = cbq_dequeue_prio(sch, prio);
		अगर (skb)
			वापस skb;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *
cbq_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	psched_समय_प्रकार now;

	now = psched_get_समय();

	अगर (q->tx_class)
		cbq_update(q);

	q->now = now;

	क्रम (;;) अणु
		q->wd_expires = 0;

		skb = cbq_dequeue_1(sch);
		अगर (skb) अणु
			qdisc_bstats_update(sch, skb);
			sch->q.qlen--;
			वापस skb;
		पूर्ण

		/* All the classes are overlimit.
		 *
		 * It is possible, अगर:
		 *
		 * 1. Scheduler is empty.
		 * 2. Toplevel cutoff inhibited borrowing.
		 * 3. Root class is overlimit.
		 *
		 * Reset 2d and 3d conditions and retry.
		 *
		 * Note, that NS and cbq-2.0 are buggy, peeking
		 * an arbitrary class is appropriate क्रम ancestor-only
		 * sharing, but not क्रम toplevel algorithm.
		 *
		 * Our version is better, but slower, because it requires
		 * two passes, but it is unaव्योमable with top-level sharing.
		 */

		अगर (q->toplevel == TC_CBQ_MAXLEVEL &&
		    q->link.underसमय == PSCHED_PASTPERFECT)
			अवरोध;

		q->toplevel = TC_CBQ_MAXLEVEL;
		q->link.underसमय = PSCHED_PASTPERFECT;
	पूर्ण

	/* No packets in scheduler or nobody wants to give them to us :-(
	 * Sigh... start watchकरोg समयr in the last हाल.
	 */

	अगर (sch->q.qlen) अणु
		qdisc_qstats_overlimit(sch);
		अगर (q->wd_expires)
			qdisc_watchकरोg_schedule(&q->watchकरोg,
						now + q->wd_expires);
	पूर्ण
	वापस शून्य;
पूर्ण

/* CBQ class मुख्यtenance routines */

अटल व्योम cbq_adjust_levels(काष्ठा cbq_class *this)
अणु
	अगर (this == शून्य)
		वापस;

	करो अणु
		पूर्णांक level = 0;
		काष्ठा cbq_class *cl;

		cl = this->children;
		अगर (cl) अणु
			करो अणु
				अगर (cl->level > level)
					level = cl->level;
			पूर्ण जबतक ((cl = cl->sibling) != this->children);
		पूर्ण
		this->level = level + 1;
	पूर्ण जबतक ((this = this->tparent) != शून्य);
पूर्ण

अटल व्योम cbq_normalize_quanta(काष्ठा cbq_sched_data *q, पूर्णांक prio)
अणु
	काष्ठा cbq_class *cl;
	अचिन्हित पूर्णांक h;

	अगर (q->quanta[prio] == 0)
		वापस;

	क्रम (h = 0; h < q->clhash.hashsize; h++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[h], common.hnode) अणु
			/* BUGGGG... Beware! This expression suffer of
			 * arithmetic overflows!
			 */
			अगर (cl->priority == prio) अणु
				cl->quantum = (cl->weight*cl->allot*q->nclasses[prio])/
					q->quanta[prio];
			पूर्ण
			अगर (cl->quantum <= 0 ||
			    cl->quantum > 32*qdisc_dev(cl->qdisc)->mtu) अणु
				pr_warn("CBQ: class %08x has bad quantum==%ld, repaired.\n",
					cl->common.classid, cl->quantum);
				cl->quantum = qdisc_dev(cl->qdisc)->mtu/2 + 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cbq_sync_defmap(काष्ठा cbq_class *cl)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(cl->qdisc);
	काष्ठा cbq_class *split = cl->split;
	अचिन्हित पूर्णांक h;
	पूर्णांक i;

	अगर (split == शून्य)
		वापस;

	क्रम (i = 0; i <= TC_PRIO_MAX; i++) अणु
		अगर (split->शेषs[i] == cl && !(cl->defmap & (1<<i)))
			split->शेषs[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i <= TC_PRIO_MAX; i++) अणु
		पूर्णांक level = split->level;

		अगर (split->शेषs[i])
			जारी;

		क्रम (h = 0; h < q->clhash.hashsize; h++) अणु
			काष्ठा cbq_class *c;

			hlist_क्रम_each_entry(c, &q->clhash.hash[h],
					     common.hnode) अणु
				अगर (c->split == split && c->level < level &&
				    c->defmap & (1<<i)) अणु
					split->शेषs[i] = c;
					level = c->level;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cbq_change_defmap(काष्ठा cbq_class *cl, u32 splitid, u32 def, u32 mask)
अणु
	काष्ठा cbq_class *split = शून्य;

	अगर (splitid == 0) अणु
		split = cl->split;
		अगर (!split)
			वापस;
		splitid = split->common.classid;
	पूर्ण

	अगर (split == शून्य || split->common.classid != splitid) अणु
		क्रम (split = cl->tparent; split; split = split->tparent)
			अगर (split->common.classid == splitid)
				अवरोध;
	पूर्ण

	अगर (split == शून्य)
		वापस;

	अगर (cl->split != split) अणु
		cl->defmap = 0;
		cbq_sync_defmap(cl);
		cl->split = split;
		cl->defmap = def & mask;
	पूर्ण अन्यथा
		cl->defmap = (cl->defmap & ~mask) | (def & mask);

	cbq_sync_defmap(cl);
पूर्ण

अटल व्योम cbq_unlink_class(काष्ठा cbq_class *this)
अणु
	काष्ठा cbq_class *cl, **clp;
	काष्ठा cbq_sched_data *q = qdisc_priv(this->qdisc);

	qdisc_class_hash_हटाओ(&q->clhash, &this->common);

	अगर (this->tparent) अणु
		clp = &this->sibling;
		cl = *clp;
		करो अणु
			अगर (cl == this) अणु
				*clp = cl->sibling;
				अवरोध;
			पूर्ण
			clp = &cl->sibling;
		पूर्ण जबतक ((cl = *clp) != this->sibling);

		अगर (this->tparent->children == this) अणु
			this->tparent->children = this->sibling;
			अगर (this->sibling == this)
				this->tparent->children = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(this->sibling != this);
	पूर्ण
पूर्ण

अटल व्योम cbq_link_class(काष्ठा cbq_class *this)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(this->qdisc);
	काष्ठा cbq_class *parent = this->tparent;

	this->sibling = this;
	qdisc_class_hash_insert(&q->clhash, &this->common);

	अगर (parent == शून्य)
		वापस;

	अगर (parent->children == शून्य) अणु
		parent->children = this;
	पूर्ण अन्यथा अणु
		this->sibling = parent->children->sibling;
		parent->children->sibling = this;
	पूर्ण
पूर्ण

अटल व्योम
cbq_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl;
	पूर्णांक prio;
	अचिन्हित पूर्णांक h;

	q->activemask = 0;
	q->pmask = 0;
	q->tx_class = शून्य;
	q->tx_borrowed = शून्य;
	qdisc_watchकरोg_cancel(&q->watchकरोg);
	hrसमयr_cancel(&q->delay_समयr);
	q->toplevel = TC_CBQ_MAXLEVEL;
	q->now = psched_get_समय();

	क्रम (prio = 0; prio <= TC_CBQ_MAXPRIO; prio++)
		q->active[prio] = शून्य;

	क्रम (h = 0; h < q->clhash.hashsize; h++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[h], common.hnode) अणु
			qdisc_reset(cl->q);

			cl->next_alive = शून्य;
			cl->underसमय = PSCHED_PASTPERFECT;
			cl->avgidle = cl->maxidle;
			cl->deficit = cl->quantum;
			cl->cpriority = cl->priority;
		पूर्ण
	पूर्ण
	sch->q.qlen = 0;
पूर्ण


अटल पूर्णांक cbq_set_lss(काष्ठा cbq_class *cl, काष्ठा tc_cbq_lssopt *lss)
अणु
	अगर (lss->change & TCF_CBQ_LSS_FLAGS) अणु
		cl->share = (lss->flags & TCF_CBQ_LSS_ISOLATED) ? शून्य : cl->tparent;
		cl->borrow = (lss->flags & TCF_CBQ_LSS_BOUNDED) ? शून्य : cl->tparent;
	पूर्ण
	अगर (lss->change & TCF_CBQ_LSS_EWMA)
		cl->ewma_log = lss->ewma_log;
	अगर (lss->change & TCF_CBQ_LSS_AVPKT)
		cl->avpkt = lss->avpkt;
	अगर (lss->change & TCF_CBQ_LSS_MINIDLE)
		cl->minidle = -(दीर्घ)lss->minidle;
	अगर (lss->change & TCF_CBQ_LSS_MAXIDLE) अणु
		cl->maxidle = lss->maxidle;
		cl->avgidle = lss->maxidle;
	पूर्ण
	अगर (lss->change & TCF_CBQ_LSS_OFFTIME)
		cl->offसमय = lss->offसमय;
	वापस 0;
पूर्ण

अटल व्योम cbq_rmprio(काष्ठा cbq_sched_data *q, काष्ठा cbq_class *cl)
अणु
	q->nclasses[cl->priority]--;
	q->quanta[cl->priority] -= cl->weight;
	cbq_normalize_quanta(q, cl->priority);
पूर्ण

अटल व्योम cbq_addprio(काष्ठा cbq_sched_data *q, काष्ठा cbq_class *cl)
अणु
	q->nclasses[cl->priority]++;
	q->quanta[cl->priority] += cl->weight;
	cbq_normalize_quanta(q, cl->priority);
पूर्ण

अटल पूर्णांक cbq_set_wrr(काष्ठा cbq_class *cl, काष्ठा tc_cbq_wrropt *wrr)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(cl->qdisc);

	अगर (wrr->allot)
		cl->allot = wrr->allot;
	अगर (wrr->weight)
		cl->weight = wrr->weight;
	अगर (wrr->priority) अणु
		cl->priority = wrr->priority - 1;
		cl->cpriority = cl->priority;
		अगर (cl->priority >= cl->priority2)
			cl->priority2 = TC_CBQ_MAXPRIO - 1;
	पूर्ण

	cbq_addprio(q, cl);
	वापस 0;
पूर्ण

अटल पूर्णांक cbq_set_fopt(काष्ठा cbq_class *cl, काष्ठा tc_cbq_fopt *fopt)
अणु
	cbq_change_defmap(cl, fopt->split, fopt->defmap, fopt->defchange);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy cbq_policy[TCA_CBQ_MAX + 1] = अणु
	[TCA_CBQ_LSSOPT]	= अणु .len = माप(काष्ठा tc_cbq_lssopt) पूर्ण,
	[TCA_CBQ_WRROPT]	= अणु .len = माप(काष्ठा tc_cbq_wrropt) पूर्ण,
	[TCA_CBQ_FOPT]		= अणु .len = माप(काष्ठा tc_cbq_fopt) पूर्ण,
	[TCA_CBQ_OVL_STRATEGY]	= अणु .len = माप(काष्ठा tc_cbq_ovl) पूर्ण,
	[TCA_CBQ_RATE]		= अणु .len = माप(काष्ठा tc_ratespec) पूर्ण,
	[TCA_CBQ_RTAB]		= अणु .type = NLA_BINARY, .len = TC_RTAB_SIZE पूर्ण,
	[TCA_CBQ_POLICE]	= अणु .len = माप(काष्ठा tc_cbq_police) पूर्ण,
पूर्ण;

अटल पूर्णांक cbq_opt_parse(काष्ठा nlattr *tb[TCA_CBQ_MAX + 1],
			 काष्ठा nlattr *opt,
			 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (!opt) अणु
		NL_SET_ERR_MSG(extack, "CBQ options are required for this operation");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_CBQ_MAX, opt,
					  cbq_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_CBQ_WRROPT]) अणु
		स्थिर काष्ठा tc_cbq_wrropt *wrr = nla_data(tb[TCA_CBQ_WRROPT]);

		अगर (wrr->priority > TC_CBQ_MAXPRIO) अणु
			NL_SET_ERR_MSG(extack, "priority is bigger than TC_CBQ_MAXPRIO");
			err = -EINVAL;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cbq_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_CBQ_MAX + 1];
	काष्ठा tc_ratespec *r;
	पूर्णांक err;

	qdisc_watchकरोg_init(&q->watchकरोg, sch);
	hrसमयr_init(&q->delay_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_PINNED);
	q->delay_समयr.function = cbq_undelay;

	err = cbq_opt_parse(tb, opt, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_CBQ_RTAB] || !tb[TCA_CBQ_RATE]) अणु
		NL_SET_ERR_MSG(extack, "Rate specification missing or incomplete");
		वापस -EINVAL;
	पूर्ण

	r = nla_data(tb[TCA_CBQ_RATE]);

	q->link.R_tab = qdisc_get_rtab(r, tb[TCA_CBQ_RTAB], extack);
	अगर (!q->link.R_tab)
		वापस -EINVAL;

	err = tcf_block_get(&q->link.block, &q->link.filter_list, sch, extack);
	अगर (err)
		जाओ put_rtab;

	err = qdisc_class_hash_init(&q->clhash);
	अगर (err < 0)
		जाओ put_block;

	q->link.sibling = &q->link;
	q->link.common.classid = sch->handle;
	q->link.qdisc = sch;
	q->link.q = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
				      sch->handle, शून्य);
	अगर (!q->link.q)
		q->link.q = &noop_qdisc;
	अन्यथा
		qdisc_hash_add(q->link.q, true);

	q->link.priority = TC_CBQ_MAXPRIO - 1;
	q->link.priority2 = TC_CBQ_MAXPRIO - 1;
	q->link.cpriority = TC_CBQ_MAXPRIO - 1;
	q->link.allot = psched_mtu(qdisc_dev(sch));
	q->link.quantum = q->link.allot;
	q->link.weight = q->link.R_tab->rate.rate;

	q->link.ewma_log = TC_CBQ_DEF_EWMA;
	q->link.avpkt = q->link.allot/2;
	q->link.minidle = -0x7FFFFFFF;

	q->toplevel = TC_CBQ_MAXLEVEL;
	q->now = psched_get_समय();

	cbq_link_class(&q->link);

	अगर (tb[TCA_CBQ_LSSOPT])
		cbq_set_lss(&q->link, nla_data(tb[TCA_CBQ_LSSOPT]));

	cbq_addprio(q, &q->link);
	वापस 0;

put_block:
	tcf_block_put(q->link.block);

put_rtab:
	qdisc_put_rtab(q->link.R_tab);
	वापस err;
पूर्ण

अटल पूर्णांक cbq_dump_rate(काष्ठा sk_buff *skb, काष्ठा cbq_class *cl)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);

	अगर (nla_put(skb, TCA_CBQ_RATE, माप(cl->R_tab->rate), &cl->R_tab->rate))
		जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक cbq_dump_lss(काष्ठा sk_buff *skb, काष्ठा cbq_class *cl)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_cbq_lssopt opt;

	opt.flags = 0;
	अगर (cl->borrow == शून्य)
		opt.flags |= TCF_CBQ_LSS_BOUNDED;
	अगर (cl->share == शून्य)
		opt.flags |= TCF_CBQ_LSS_ISOLATED;
	opt.ewma_log = cl->ewma_log;
	opt.level = cl->level;
	opt.avpkt = cl->avpkt;
	opt.maxidle = cl->maxidle;
	opt.minidle = (u32)(-cl->minidle);
	opt.offसमय = cl->offसमय;
	opt.change = ~0;
	अगर (nla_put(skb, TCA_CBQ_LSSOPT, माप(opt), &opt))
		जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक cbq_dump_wrr(काष्ठा sk_buff *skb, काष्ठा cbq_class *cl)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_cbq_wrropt opt;

	स_रखो(&opt, 0, माप(opt));
	opt.flags = 0;
	opt.allot = cl->allot;
	opt.priority = cl->priority + 1;
	opt.cpriority = cl->cpriority + 1;
	opt.weight = cl->weight;
	अगर (nla_put(skb, TCA_CBQ_WRROPT, माप(opt), &opt))
		जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक cbq_dump_fopt(काष्ठा sk_buff *skb, काष्ठा cbq_class *cl)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_cbq_fopt opt;

	अगर (cl->split || cl->defmap) अणु
		opt.split = cl->split ? cl->split->common.classid : 0;
		opt.defmap = cl->defmap;
		opt.defchange = ~0;
		अगर (nla_put(skb, TCA_CBQ_FOPT, माप(opt), &opt))
			जाओ nla_put_failure;
	पूर्ण
	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक cbq_dump_attr(काष्ठा sk_buff *skb, काष्ठा cbq_class *cl)
अणु
	अगर (cbq_dump_lss(skb, cl) < 0 ||
	    cbq_dump_rate(skb, cl) < 0 ||
	    cbq_dump_wrr(skb, cl) < 0 ||
	    cbq_dump_fopt(skb, cl) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक cbq_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (cbq_dump_attr(skb, &q->link) < 0)
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक
cbq_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);

	q->link.xstats.avgidle = q->link.avgidle;
	वापस gnet_stats_copy_app(d, &q->link.xstats, माप(q->link.xstats));
पूर्ण

अटल पूर्णांक
cbq_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
	       काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;
	काष्ठा nlattr *nest;

	अगर (cl->tparent)
		tcm->tcm_parent = cl->tparent->common.classid;
	अन्यथा
		tcm->tcm_parent = TC_H_ROOT;
	tcm->tcm_handle = cl->common.classid;
	tcm->tcm_info = cl->q->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;
	अगर (cbq_dump_attr(skb, cl) < 0)
		जाओ nla_put_failure;
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक
cbq_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
	काष्ठा gnet_dump *d)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;
	__u32 qlen;

	cl->xstats.avgidle = cl->avgidle;
	cl->xstats.underसमय = 0;
	qdisc_qstats_qlen_backlog(cl->q, &qlen, &cl->qstats.backlog);

	अगर (cl->underसमय != PSCHED_PASTPERFECT)
		cl->xstats.underसमय = cl->underसमय - q->now;

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, शून्य, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, शून्य, &cl->qstats, qlen) < 0)
		वापस -1;

	वापस gnet_stats_copy_app(d, &cl->xstats, माप(cl->xstats));
पूर्ण

अटल पूर्णांक cbq_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;

	अगर (new == शून्य) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					cl->common.classid, extack);
		अगर (new == शून्य)
			वापस -ENOBUFS;
	पूर्ण

	*old = qdisc_replace(sch, new, &cl->q);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *cbq_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;

	वापस cl->q;
पूर्ण

अटल व्योम cbq_qlen_notअगरy(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;

	cbq_deactivate_class(cl);
पूर्ण

अटल अचिन्हित दीर्घ cbq_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);

	वापस (अचिन्हित दीर्घ)cbq_class_lookup(q, classid);
पूर्ण

अटल व्योम cbq_destroy_class(काष्ठा Qdisc *sch, काष्ठा cbq_class *cl)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);

	WARN_ON(cl->filters);

	tcf_block_put(cl->block);
	qdisc_put(cl->q);
	qdisc_put_rtab(cl->R_tab);
	gen_समाप्त_estimator(&cl->rate_est);
	अगर (cl != &q->link)
		kमुक्त(cl);
पूर्ण

अटल व्योम cbq_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा hlist_node *next;
	काष्ठा cbq_class *cl;
	अचिन्हित पूर्णांक h;

#अगर_घोषित CONFIG_NET_CLS_ACT
	q->rx_class = शून्य;
#पूर्ण_अगर
	/*
	 * Filters must be destroyed first because we करोn't destroy the
	 * classes from root to leafs which means that filters can still
	 * be bound to classes which have been destroyed alपढ़ोy. --TGR '04
	 */
	क्रम (h = 0; h < q->clhash.hashsize; h++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[h], common.hnode) अणु
			tcf_block_put(cl->block);
			cl->block = शून्य;
		पूर्ण
	पूर्ण
	क्रम (h = 0; h < q->clhash.hashsize; h++) अणु
		hlist_क्रम_each_entry_safe(cl, next, &q->clhash.hash[h],
					  common.hnode)
			cbq_destroy_class(sch, cl);
	पूर्ण
	qdisc_class_hash_destroy(&q->clhash);
पूर्ण

अटल पूर्णांक
cbq_change_class(काष्ठा Qdisc *sch, u32 classid, u32 parentid, काष्ठा nlattr **tca,
		 अचिन्हित दीर्घ *arg, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)*arg;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_CBQ_MAX + 1];
	काष्ठा cbq_class *parent;
	काष्ठा qdisc_rate_table *rtab = शून्य;

	err = cbq_opt_parse(tb, opt, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_CBQ_OVL_STRATEGY] || tb[TCA_CBQ_POLICE]) अणु
		NL_SET_ERR_MSG(extack, "Neither overlimit strategy nor policing attributes can be used for changing class params");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cl) अणु
		/* Check parent */
		अगर (parentid) अणु
			अगर (cl->tparent &&
			    cl->tparent->common.classid != parentid) अणु
				NL_SET_ERR_MSG(extack, "Invalid parent id");
				वापस -EINVAL;
			पूर्ण
			अगर (!cl->tparent && parentid != TC_H_ROOT) अणु
				NL_SET_ERR_MSG(extack, "Parent must be root");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (tb[TCA_CBQ_RATE]) अणु
			rtab = qdisc_get_rtab(nla_data(tb[TCA_CBQ_RATE]),
					      tb[TCA_CBQ_RTAB], extack);
			अगर (rtab == शून्य)
				वापस -EINVAL;
		पूर्ण

		अगर (tca[TCA_RATE]) अणु
			err = gen_replace_estimator(&cl->bstats, शून्य,
						    &cl->rate_est,
						    शून्य,
						    qdisc_root_sleeping_running(sch),
						    tca[TCA_RATE]);
			अगर (err) अणु
				NL_SET_ERR_MSG(extack, "Failed to replace specified rate estimator");
				qdisc_put_rtab(rtab);
				वापस err;
			पूर्ण
		पूर्ण

		/* Change class parameters */
		sch_tree_lock(sch);

		अगर (cl->next_alive != शून्य)
			cbq_deactivate_class(cl);

		अगर (rtab) अणु
			qdisc_put_rtab(cl->R_tab);
			cl->R_tab = rtab;
		पूर्ण

		अगर (tb[TCA_CBQ_LSSOPT])
			cbq_set_lss(cl, nla_data(tb[TCA_CBQ_LSSOPT]));

		अगर (tb[TCA_CBQ_WRROPT]) अणु
			cbq_rmprio(q, cl);
			cbq_set_wrr(cl, nla_data(tb[TCA_CBQ_WRROPT]));
		पूर्ण

		अगर (tb[TCA_CBQ_FOPT])
			cbq_set_fopt(cl, nla_data(tb[TCA_CBQ_FOPT]));

		अगर (cl->q->q.qlen)
			cbq_activate_class(cl);

		sch_tree_unlock(sch);

		वापस 0;
	पूर्ण

	अगर (parentid == TC_H_ROOT)
		वापस -EINVAL;

	अगर (!tb[TCA_CBQ_WRROPT] || !tb[TCA_CBQ_RATE] || !tb[TCA_CBQ_LSSOPT]) अणु
		NL_SET_ERR_MSG(extack, "One of the following attributes MUST be specified: WRR, rate or link sharing");
		वापस -EINVAL;
	पूर्ण

	rtab = qdisc_get_rtab(nla_data(tb[TCA_CBQ_RATE]), tb[TCA_CBQ_RTAB],
			      extack);
	अगर (rtab == शून्य)
		वापस -EINVAL;

	अगर (classid) अणु
		err = -EINVAL;
		अगर (TC_H_MAJ(classid ^ sch->handle) ||
		    cbq_class_lookup(q, classid)) अणु
			NL_SET_ERR_MSG(extack, "Specified class not found");
			जाओ failure;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		classid = TC_H_MAKE(sch->handle, 0x8000);

		क्रम (i = 0; i < 0x8000; i++) अणु
			अगर (++q->hgenerator >= 0x8000)
				q->hgenerator = 1;
			अगर (cbq_class_lookup(q, classid|q->hgenerator) == शून्य)
				अवरोध;
		पूर्ण
		err = -ENOSR;
		अगर (i >= 0x8000) अणु
			NL_SET_ERR_MSG(extack, "Unable to generate classid");
			जाओ failure;
		पूर्ण
		classid = classid|q->hgenerator;
	पूर्ण

	parent = &q->link;
	अगर (parentid) अणु
		parent = cbq_class_lookup(q, parentid);
		err = -EINVAL;
		अगर (!parent) अणु
			NL_SET_ERR_MSG(extack, "Failed to find parentid");
			जाओ failure;
		पूर्ण
	पूर्ण

	err = -ENOBUFS;
	cl = kzalloc(माप(*cl), GFP_KERNEL);
	अगर (cl == शून्य)
		जाओ failure;

	err = tcf_block_get(&cl->block, &cl->filter_list, sch, extack);
	अगर (err) अणु
		kमुक्त(cl);
		वापस err;
	पूर्ण

	अगर (tca[TCA_RATE]) अणु
		err = gen_new_estimator(&cl->bstats, शून्य, &cl->rate_est,
					शून्य,
					qdisc_root_sleeping_running(sch),
					tca[TCA_RATE]);
		अगर (err) अणु
			NL_SET_ERR_MSG(extack, "Couldn't create new estimator");
			tcf_block_put(cl->block);
			kमुक्त(cl);
			जाओ failure;
		पूर्ण
	पूर्ण

	cl->R_tab = rtab;
	rtab = शून्य;
	cl->q = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops, classid,
				  शून्य);
	अगर (!cl->q)
		cl->q = &noop_qdisc;
	अन्यथा
		qdisc_hash_add(cl->q, true);

	cl->common.classid = classid;
	cl->tparent = parent;
	cl->qdisc = sch;
	cl->allot = parent->allot;
	cl->quantum = cl->allot;
	cl->weight = cl->R_tab->rate.rate;

	sch_tree_lock(sch);
	cbq_link_class(cl);
	cl->borrow = cl->tparent;
	अगर (cl->tparent != &q->link)
		cl->share = cl->tparent;
	cbq_adjust_levels(parent);
	cl->minidle = -0x7FFFFFFF;
	cbq_set_lss(cl, nla_data(tb[TCA_CBQ_LSSOPT]));
	cbq_set_wrr(cl, nla_data(tb[TCA_CBQ_WRROPT]));
	अगर (cl->ewma_log == 0)
		cl->ewma_log = q->link.ewma_log;
	अगर (cl->maxidle == 0)
		cl->maxidle = q->link.maxidle;
	अगर (cl->avpkt == 0)
		cl->avpkt = q->link.avpkt;
	अगर (tb[TCA_CBQ_FOPT])
		cbq_set_fopt(cl, nla_data(tb[TCA_CBQ_FOPT]));
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (अचिन्हित दीर्घ)cl;
	वापस 0;

failure:
	qdisc_put_rtab(rtab);
	वापस err;
पूर्ण

अटल पूर्णांक cbq_delete(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;

	अगर (cl->filters || cl->children || cl == &q->link)
		वापस -EBUSY;

	sch_tree_lock(sch);

	qdisc_purge_queue(cl->q);

	अगर (cl->next_alive)
		cbq_deactivate_class(cl);

	अगर (q->tx_borrowed == cl)
		q->tx_borrowed = q->tx_class;
	अगर (q->tx_class == cl) अणु
		q->tx_class = शून्य;
		q->tx_borrowed = शून्य;
	पूर्ण
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (q->rx_class == cl)
		q->rx_class = शून्य;
#पूर्ण_अगर

	cbq_unlink_class(cl);
	cbq_adjust_levels(cl->tparent);
	cl->defmap = 0;
	cbq_sync_defmap(cl);

	cbq_rmprio(q, cl);
	sch_tree_unlock(sch);

	cbq_destroy_class(sch, cl);
	वापस 0;
पूर्ण

अटल काष्ठा tcf_block *cbq_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;

	अगर (cl == शून्य)
		cl = &q->link;

	वापस cl->block;
पूर्ण

अटल अचिन्हित दीर्घ cbq_bind_filter(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
				     u32 classid)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *p = (काष्ठा cbq_class *)parent;
	काष्ठा cbq_class *cl = cbq_class_lookup(q, classid);

	अगर (cl) अणु
		अगर (p && p->level <= cl->level)
			वापस 0;
		cl->filters++;
		वापस (अचिन्हित दीर्घ)cl;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cbq_unbind_filter(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cbq_class *cl = (काष्ठा cbq_class *)arg;

	cl->filters--;
पूर्ण

अटल व्योम cbq_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा cbq_sched_data *q = qdisc_priv(sch);
	काष्ठा cbq_class *cl;
	अचिन्हित पूर्णांक h;

	अगर (arg->stop)
		वापस;

	क्रम (h = 0; h < q->clhash.hashsize; h++) अणु
		hlist_क्रम_each_entry(cl, &q->clhash.hash[h], common.hnode) अणु
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

अटल स्थिर काष्ठा Qdisc_class_ops cbq_class_ops = अणु
	.graft		=	cbq_graft,
	.leaf		=	cbq_leaf,
	.qlen_notअगरy	=	cbq_qlen_notअगरy,
	.find		=	cbq_find,
	.change		=	cbq_change_class,
	.delete		=	cbq_delete,
	.walk		=	cbq_walk,
	.tcf_block	=	cbq_tcf_block,
	.bind_tcf	=	cbq_bind_filter,
	.unbind_tcf	=	cbq_unbind_filter,
	.dump		=	cbq_dump_class,
	.dump_stats	=	cbq_dump_class_stats,
पूर्ण;

अटल काष्ठा Qdisc_ops cbq_qdisc_ops __पढ़ो_mostly = अणु
	.next		=	शून्य,
	.cl_ops		=	&cbq_class_ops,
	.id		=	"cbq",
	.priv_size	=	माप(काष्ठा cbq_sched_data),
	.enqueue	=	cbq_enqueue,
	.dequeue	=	cbq_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	cbq_init,
	.reset		=	cbq_reset,
	.destroy	=	cbq_destroy,
	.change		=	शून्य,
	.dump		=	cbq_dump,
	.dump_stats	=	cbq_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init cbq_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&cbq_qdisc_ops);
पूर्ण
अटल व्योम __निकास cbq_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&cbq_qdisc_ops);
पूर्ण
module_init(cbq_module_init)
module_निकास(cbq_module_निकास)
MODULE_LICENSE("GPL");
