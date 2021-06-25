<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/sch_netem.c	Network emulator
 *
 *  		Many of the algorithms and ideas क्रम this came from
 *		NIST Net which is not copyrighted.
 *
 * Authors:	Stephen Hemminger <shemminger@osdl.org>
 *		Catalin(ux aka Dino) BOIE <catab at umbrella करोt ro>
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/reciprocal_भाग.h>
#समावेश <linux/rbtree.h>

#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/inet_ecn.h>

#घोषणा VERSION "1.3"

/*	Network Emulation Queuing algorithm.
	====================================

	Sources: [1] Mark Carson, Darrin Santay, "NIST Net - A Linux-based
		 Network Emulation Tool
		 [2] Luigi Rizzo, DummyNet क्रम FreeBSD

	 ----------------------------------------------------------------

	 This started out as a simple way to delay outgoing packets to
	 test TCP but has grown to include most of the functionality
	 of a full blown network emulator like NISTnet. It can delay
	 packets and add अक्रमom jitter (and correlation). The अक्रमom
	 distribution can be loaded from a table as well to provide
	 normal, Pareto, or experimental curves. Packet loss,
	 duplication, and reordering can also be emulated.

	 This qdisc करोes not करो classअगरication that can be handled in
	 layering other disciplines.  It करोes not need to करो bandwidth
	 control either since that can be handled by using token
	 bucket or other rate control.

     Correlated Loss Generator models

	Added generation of correlated loss according to the
	"Gilbert-Elliot" model, a 4-state markov model.

	References:
	[1] NetemCLG Home http://netgroup.uniroma2.it/NetemCLG
	[2] S. Salsano, F. Luकरोvici, A. Ordine, "Definition of a general
	and पूर्णांकuitive loss model क्रम packet networks and its implementation
	in the Netem module in the Linux kernel", available in [1]

	Authors: Stefano Salsano <stefano.salsano at uniroma2.it
		 Fabio Luकरोvici <fabio.luकरोvici at yahoo.it>
*/

काष्ठा disttable अणु
	u32  size;
	s16 table[];
पूर्ण;

काष्ठा netem_sched_data अणु
	/* पूर्णांकernal t(ime)fअगरo qdisc uses t_root and sch->limit */
	काष्ठा rb_root t_root;

	/* a linear queue; reduces rbtree rebalancing when jitter is low */
	काष्ठा sk_buff	*t_head;
	काष्ठा sk_buff	*t_tail;

	/* optional qdisc क्रम classful handling (शून्य at netem init) */
	काष्ठा Qdisc	*qdisc;

	काष्ठा qdisc_watchकरोg watchकरोg;

	s64 latency;
	s64 jitter;

	u32 loss;
	u32 ecn;
	u32 limit;
	u32 counter;
	u32 gap;
	u32 duplicate;
	u32 reorder;
	u32 corrupt;
	u64 rate;
	s32 packet_overhead;
	u32 cell_size;
	काष्ठा reciprocal_value cell_size_reciprocal;
	s32 cell_overhead;

	काष्ठा crndstate अणु
		u32 last;
		u32 rho;
	पूर्ण delay_cor, loss_cor, dup_cor, reorder_cor, corrupt_cor;

	काष्ठा disttable *delay_dist;

	क्रमागत  अणु
		CLG_RANDOM,
		CLG_4_STATES,
		CLG_GILB_ELL,
	पूर्ण loss_model;

	क्रमागत अणु
		TX_IN_GAP_PERIOD = 1,
		TX_IN_BURST_PERIOD,
		LOST_IN_GAP_PERIOD,
		LOST_IN_BURST_PERIOD,
	पूर्ण _4_state_model;

	क्रमागत अणु
		GOOD_STATE = 1,
		BAD_STATE,
	पूर्ण GE_state_model;

	/* Correlated Loss Generation models */
	काष्ठा clgstate अणु
		/* state of the Markov chain */
		u8 state;

		/* 4-states and Gilbert-Elliot models */
		u32 a1;	/* p13 क्रम 4-states or p क्रम GE */
		u32 a2;	/* p31 क्रम 4-states or r क्रम GE */
		u32 a3;	/* p32 क्रम 4-states or h क्रम GE */
		u32 a4;	/* p14 क्रम 4-states or 1-k क्रम GE */
		u32 a5; /* p23 used only in 4-states */
	पूर्ण clg;

	काष्ठा tc_netem_slot slot_config;
	काष्ठा slotstate अणु
		u64 slot_next;
		s32 packets_left;
		s32 bytes_left;
	पूर्ण slot;

	काष्ठा disttable *slot_dist;
पूर्ण;

/* Time stamp put पूर्णांकo socket buffer control block
 * Only valid when skbs are in our पूर्णांकernal t(ime)fअगरo queue.
 *
 * As skb->rbnode uses same storage than skb->next, skb->prev and skb->tstamp,
 * and skb->next & skb->prev are scratch space क्रम a qdisc,
 * we save skb->tstamp value in skb->cb[] beक्रमe destroying it.
 */
काष्ठा netem_skb_cb अणु
	u64	        समय_प्रकारo_send;
पूर्ण;

अटल अंतरभूत काष्ठा netem_skb_cb *netem_skb_cb(काष्ठा sk_buff *skb)
अणु
	/* we assume we can use skb next/prev/tstamp as storage क्रम rb_node */
	qdisc_cb_निजी_validate(skb, माप(काष्ठा netem_skb_cb));
	वापस (काष्ठा netem_skb_cb *)qdisc_skb_cb(skb)->data;
पूर्ण

/* init_cअक्रमom - initialize correlated अक्रमom number generator
 * Use entropy source क्रम initial seed.
 */
अटल व्योम init_cअक्रमom(काष्ठा crndstate *state, अचिन्हित दीर्घ rho)
अणु
	state->rho = rho;
	state->last = pअक्रमom_u32();
पूर्ण

/* get_cअक्रमom - correlated अक्रमom number generator
 * Next number depends on last value.
 * rho is scaled to aव्योम भग्नing poपूर्णांक.
 */
अटल u32 get_cअक्रमom(काष्ठा crndstate *state)
अणु
	u64 value, rho;
	अचिन्हित दीर्घ answer;

	अगर (!state || state->rho == 0)	/* no correlation */
		वापस pअक्रमom_u32();

	value = pअक्रमom_u32();
	rho = (u64)state->rho + 1;
	answer = (value * ((1ull<<32) - rho) + state->last * rho) >> 32;
	state->last = answer;
	वापस answer;
पूर्ण

/* loss_4state - 4-state model loss generator
 * Generates losses according to the 4-state Markov chain aकरोpted in
 * the GI (General and Intuitive) loss model.
 */
अटल bool loss_4state(काष्ठा netem_sched_data *q)
अणु
	काष्ठा clgstate *clg = &q->clg;
	u32 rnd = pअक्रमom_u32();

	/*
	 * Makes a comparison between rnd and the transition
	 * probabilities outgoing from the current state, then decides the
	 * next state and अगर the next packet has to be transmitted or lost.
	 * The four states correspond to:
	 *   TX_IN_GAP_PERIOD => successfully transmitted packets within a gap period
	 *   LOST_IN_BURST_PERIOD => isolated losses within a gap period
	 *   LOST_IN_GAP_PERIOD => lost packets within a burst period
	 *   TX_IN_GAP_PERIOD => successfully transmitted packets within a burst period
	 */
	चयन (clg->state) अणु
	हाल TX_IN_GAP_PERIOD:
		अगर (rnd < clg->a4) अणु
			clg->state = LOST_IN_BURST_PERIOD;
			वापस true;
		पूर्ण अन्यथा अगर (clg->a4 < rnd && rnd < clg->a1 + clg->a4) अणु
			clg->state = LOST_IN_GAP_PERIOD;
			वापस true;
		पूर्ण अन्यथा अगर (clg->a1 + clg->a4 < rnd) अणु
			clg->state = TX_IN_GAP_PERIOD;
		पूर्ण

		अवरोध;
	हाल TX_IN_BURST_PERIOD:
		अगर (rnd < clg->a5) अणु
			clg->state = LOST_IN_GAP_PERIOD;
			वापस true;
		पूर्ण अन्यथा अणु
			clg->state = TX_IN_BURST_PERIOD;
		पूर्ण

		अवरोध;
	हाल LOST_IN_GAP_PERIOD:
		अगर (rnd < clg->a3)
			clg->state = TX_IN_BURST_PERIOD;
		अन्यथा अगर (clg->a3 < rnd && rnd < clg->a2 + clg->a3) अणु
			clg->state = TX_IN_GAP_PERIOD;
		पूर्ण अन्यथा अगर (clg->a2 + clg->a3 < rnd) अणु
			clg->state = LOST_IN_GAP_PERIOD;
			वापस true;
		पूर्ण
		अवरोध;
	हाल LOST_IN_BURST_PERIOD:
		clg->state = TX_IN_GAP_PERIOD;
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/* loss_gilb_ell - Gilbert-Elliot model loss generator
 * Generates losses according to the Gilbert-Elliot loss model or
 * its special हालs  (Gilbert or Simple Gilbert)
 *
 * Makes a comparison between अक्रमom number and the transition
 * probabilities outgoing from the current state, then decides the
 * next state. A second अक्रमom number is extracted and the comparison
 * with the loss probability of the current state decides अगर the next
 * packet will be transmitted or lost.
 */
अटल bool loss_gilb_ell(काष्ठा netem_sched_data *q)
अणु
	काष्ठा clgstate *clg = &q->clg;

	चयन (clg->state) अणु
	हाल GOOD_STATE:
		अगर (pअक्रमom_u32() < clg->a1)
			clg->state = BAD_STATE;
		अगर (pअक्रमom_u32() < clg->a4)
			वापस true;
		अवरोध;
	हाल BAD_STATE:
		अगर (pअक्रमom_u32() < clg->a2)
			clg->state = GOOD_STATE;
		अगर (pअक्रमom_u32() > clg->a3)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool loss_event(काष्ठा netem_sched_data *q)
अणु
	चयन (q->loss_model) अणु
	हाल CLG_RANDOM:
		/* Ranकरोm packet drop 0 => none, ~0 => all */
		वापस q->loss && q->loss >= get_cअक्रमom(&q->loss_cor);

	हाल CLG_4_STATES:
		/* 4state loss model algorithm (used also क्रम GI model)
		* Extracts a value from the markov 4 state loss generator,
		* अगर it is 1 drops a packet and अगर needed ग_लिखोs the event in
		* the kernel logs
		*/
		वापस loss_4state(q);

	हाल CLG_GILB_ELL:
		/* Gilbert-Elliot loss model algorithm
		* Extracts a value from the Gilbert-Elliot loss generator,
		* अगर it is 1 drops a packet and अगर needed ग_लिखोs the event in
		* the kernel logs
		*/
		वापस loss_gilb_ell(q);
	पूर्ण

	वापस false;	/* not reached */
पूर्ण


/* tabledist - वापस a pseuकरो-अक्रमomly distributed value with mean mu and
 * std deviation sigma.  Uses table lookup to approximate the desired
 * distribution, and a unअगरormly-distributed pseuकरो-अक्रमom source.
 */
अटल s64 tabledist(s64 mu, s32 sigma,
		     काष्ठा crndstate *state,
		     स्थिर काष्ठा disttable *dist)
अणु
	s64 x;
	दीर्घ t;
	u32 rnd;

	अगर (sigma == 0)
		वापस mu;

	rnd = get_cअक्रमom(state);

	/* शेष unअगरorm distribution */
	अगर (dist == शून्य)
		वापस ((rnd % (2 * (u32)sigma)) + mu) - sigma;

	t = dist->table[rnd % dist->size];
	x = (sigma % NETEM_DIST_SCALE) * t;
	अगर (x >= 0)
		x += NETEM_DIST_SCALE/2;
	अन्यथा
		x -= NETEM_DIST_SCALE/2;

	वापस  x / NETEM_DIST_SCALE + (sigma / NETEM_DIST_SCALE) * t + mu;
पूर्ण

अटल u64 packet_समय_ns(u64 len, स्थिर काष्ठा netem_sched_data *q)
अणु
	len += q->packet_overhead;

	अगर (q->cell_size) अणु
		u32 cells = reciprocal_भागide(len, q->cell_size_reciprocal);

		अगर (len > cells * q->cell_size)	/* extra cell needed क्रम reमुख्यder */
			cells++;
		len = cells * (q->cell_size + q->cell_overhead);
	पूर्ण

	वापस भाग64_u64(len * NSEC_PER_SEC, q->rate);
पूर्ण

अटल व्योम tfअगरo_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	काष्ठा rb_node *p = rb_first(&q->t_root);

	जबतक (p) अणु
		काष्ठा sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);
		rb_erase(&skb->rbnode, &q->t_root);
		rtnl_kमुक्त_skbs(skb, skb);
	पूर्ण

	rtnl_kमुक्त_skbs(q->t_head, q->t_tail);
	q->t_head = शून्य;
	q->t_tail = शून्य;
पूर्ण

अटल व्योम tfअगरo_enqueue(काष्ठा sk_buff *nskb, काष्ठा Qdisc *sch)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	u64 tnext = netem_skb_cb(nskb)->समय_प्रकारo_send;

	अगर (!q->t_tail || tnext >= netem_skb_cb(q->t_tail)->समय_प्रकारo_send) अणु
		अगर (q->t_tail)
			q->t_tail->next = nskb;
		अन्यथा
			q->t_head = nskb;
		q->t_tail = nskb;
	पूर्ण अन्यथा अणु
		काष्ठा rb_node **p = &q->t_root.rb_node, *parent = शून्य;

		जबतक (*p) अणु
			काष्ठा sk_buff *skb;

			parent = *p;
			skb = rb_to_skb(parent);
			अगर (tnext >= netem_skb_cb(skb)->समय_प्रकारo_send)
				p = &parent->rb_right;
			अन्यथा
				p = &parent->rb_left;
		पूर्ण
		rb_link_node(&nskb->rbnode, parent, p);
		rb_insert_color(&nskb->rbnode, &q->t_root);
	पूर्ण
	sch->q.qlen++;
पूर्ण

/* netem can't properly corrupt a megapacket (like we get from GSO), so instead
 * when we statistically choose to corrupt one, we instead segment it, वापसing
 * the first packet to be corrupted, and re-enqueue the reमुख्यing frames
 */
अटल काष्ठा sk_buff *netem_segment(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				     काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा sk_buff *segs;
	netdev_features_t features = netअगर_skb_features(skb);

	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);

	अगर (IS_ERR_OR_शून्य(segs)) अणु
		qdisc_drop(skb, sch, to_मुक्त);
		वापस शून्य;
	पूर्ण
	consume_skb(skb);
	वापस segs;
पूर्ण

/*
 * Insert one skb पूर्णांकo qdisc.
 * Note: parent depends on वापस value to account क्रम queue length.
 * 	NET_XMIT_DROP: queue length didn't change.
 *      NET_XMIT_SUCCESS: one skb was queued.
 */
अटल पूर्णांक netem_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			 काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	/* We करोn't fill cb now as skb_unshare() may invalidate it */
	काष्ठा netem_skb_cb *cb;
	काष्ठा sk_buff *skb2;
	काष्ठा sk_buff *segs = शून्य;
	अचिन्हित पूर्णांक prev_len = qdisc_pkt_len(skb);
	पूर्णांक count = 1;
	पूर्णांक rc = NET_XMIT_SUCCESS;
	पूर्णांक rc_drop = NET_XMIT_DROP;

	/* Do not fool qdisc_drop_all() */
	skb->prev = शून्य;

	/* Ranकरोm duplication */
	अगर (q->duplicate && q->duplicate >= get_cअक्रमom(&q->dup_cor))
		++count;

	/* Drop packet? */
	अगर (loss_event(q)) अणु
		अगर (q->ecn && INET_ECN_set_ce(skb))
			qdisc_qstats_drop(sch); /* mark packet */
		अन्यथा
			--count;
	पूर्ण
	अगर (count == 0) अणु
		qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	पूर्ण

	/* If a delay is expected, orphan the skb. (orphaning usually takes
	 * place at TX completion समय, so _beक्रमe_ the link transit delay)
	 */
	अगर (q->latency || q->jitter || q->rate)
		skb_orphan_partial(skb);

	/*
	 * If we need to duplicate packet, then re-insert at top of the
	 * qdisc tree, since parent queuer expects that only one
	 * skb will be queued.
	 */
	अगर (count > 1 && (skb2 = skb_clone(skb, GFP_ATOMIC)) != शून्य) अणु
		काष्ठा Qdisc *rootq = qdisc_root_bh(sch);
		u32 dupsave = q->duplicate; /* prevent duplicating a dup... */

		q->duplicate = 0;
		rootq->enqueue(skb2, rootq, to_मुक्त);
		q->duplicate = dupsave;
		rc_drop = NET_XMIT_SUCCESS;
	पूर्ण

	/*
	 * Ranकरोmized packet corruption.
	 * Make copy अगर needed since we are modअगरying
	 * If packet is going to be hardware checksummed, then
	 * करो it now in software beक्रमe we mangle it.
	 */
	अगर (q->corrupt && q->corrupt >= get_cअक्रमom(&q->corrupt_cor)) अणु
		अगर (skb_is_gso(skb)) अणु
			skb = netem_segment(skb, sch, to_मुक्त);
			अगर (!skb)
				वापस rc_drop;
			segs = skb->next;
			skb_mark_not_on_list(skb);
			qdisc_skb_cb(skb)->pkt_len = skb->len;
		पूर्ण

		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (unlikely(!skb)) अणु
			qdisc_qstats_drop(sch);
			जाओ finish_segs;
		पूर्ण
		अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
		    skb_checksum_help(skb)) अणु
			qdisc_drop(skb, sch, to_मुक्त);
			skb = शून्य;
			जाओ finish_segs;
		पूर्ण

		skb->data[pअक्रमom_u32() % skb_headlen(skb)] ^=
			1<<(pअक्रमom_u32() % 8);
	पूर्ण

	अगर (unlikely(sch->q.qlen >= sch->limit)) अणु
		/* re-link segs, so that qdisc_drop_all() मुक्तs them all */
		skb->next = segs;
		qdisc_drop_all(skb, sch, to_मुक्त);
		वापस rc_drop;
	पूर्ण

	qdisc_qstats_backlog_inc(sch, skb);

	cb = netem_skb_cb(skb);
	अगर (q->gap == 0 ||		/* not करोing reordering */
	    q->counter < q->gap - 1 ||	/* inside last reordering gap */
	    q->reorder < get_cअक्रमom(&q->reorder_cor)) अणु
		u64 now;
		s64 delay;

		delay = tabledist(q->latency, q->jitter,
				  &q->delay_cor, q->delay_dist);

		now = kसमय_get_ns();

		अगर (q->rate) अणु
			काष्ठा netem_skb_cb *last = शून्य;

			अगर (sch->q.tail)
				last = netem_skb_cb(sch->q.tail);
			अगर (q->t_root.rb_node) अणु
				काष्ठा sk_buff *t_skb;
				काष्ठा netem_skb_cb *t_last;

				t_skb = skb_rb_last(&q->t_root);
				t_last = netem_skb_cb(t_skb);
				अगर (!last ||
				    t_last->समय_प्रकारo_send > last->समय_प्रकारo_send)
					last = t_last;
			पूर्ण
			अगर (q->t_tail) अणु
				काष्ठा netem_skb_cb *t_last =
					netem_skb_cb(q->t_tail);

				अगर (!last ||
				    t_last->समय_प्रकारo_send > last->समय_प्रकारo_send)
					last = t_last;
			पूर्ण

			अगर (last) अणु
				/*
				 * Last packet in queue is reference poपूर्णांक (now),
				 * calculate this समय bonus and subtract
				 * from delay.
				 */
				delay -= last->समय_प्रकारo_send - now;
				delay = max_t(s64, 0, delay);
				now = last->समय_प्रकारo_send;
			पूर्ण

			delay += packet_समय_ns(qdisc_pkt_len(skb), q);
		पूर्ण

		cb->समय_प्रकारo_send = now + delay;
		++q->counter;
		tfअगरo_enqueue(skb, sch);
	पूर्ण अन्यथा अणु
		/*
		 * Do re-ordering by putting one out of N packets at the front
		 * of the queue.
		 */
		cb->समय_प्रकारo_send = kसमय_get_ns();
		q->counter = 0;

		__qdisc_enqueue_head(skb, &sch->q);
		sch->qstats.requeues++;
	पूर्ण

finish_segs:
	अगर (segs) अणु
		अचिन्हित पूर्णांक len, last_len;
		पूर्णांक nb;

		len = skb ? skb->len : 0;
		nb = skb ? 1 : 0;

		जबतक (segs) अणु
			skb2 = segs->next;
			skb_mark_not_on_list(segs);
			qdisc_skb_cb(segs)->pkt_len = segs->len;
			last_len = segs->len;
			rc = qdisc_enqueue(segs, sch, to_मुक्त);
			अगर (rc != NET_XMIT_SUCCESS) अणु
				अगर (net_xmit_drop_count(rc))
					qdisc_qstats_drop(sch);
			पूर्ण अन्यथा अणु
				nb++;
				len += last_len;
			पूर्ण
			segs = skb2;
		पूर्ण
		/* Parent qdiscs accounted क्रम 1 skb of size @prev_len */
		qdisc_tree_reduce_backlog(sch, -(nb - 1), -(len - prev_len));
	पूर्ण अन्यथा अगर (!skb) अणु
		वापस NET_XMIT_DROP;
	पूर्ण
	वापस NET_XMIT_SUCCESS;
पूर्ण

/* Delay the next round with a new future slot with a
 * correct number of bytes and packets.
 */

अटल व्योम get_slot_next(काष्ठा netem_sched_data *q, u64 now)
अणु
	s64 next_delay;

	अगर (!q->slot_dist)
		next_delay = q->slot_config.min_delay +
				(pअक्रमom_u32() *
				 (q->slot_config.max_delay -
				  q->slot_config.min_delay) >> 32);
	अन्यथा
		next_delay = tabledist(q->slot_config.dist_delay,
				       (s32)(q->slot_config.dist_jitter),
				       शून्य, q->slot_dist);

	q->slot.slot_next = now + next_delay;
	q->slot.packets_left = q->slot_config.max_packets;
	q->slot.bytes_left = q->slot_config.max_bytes;
पूर्ण

अटल काष्ठा sk_buff *netem_peek(काष्ठा netem_sched_data *q)
अणु
	काष्ठा sk_buff *skb = skb_rb_first(&q->t_root);
	u64 t1, t2;

	अगर (!skb)
		वापस q->t_head;
	अगर (!q->t_head)
		वापस skb;

	t1 = netem_skb_cb(skb)->समय_प्रकारo_send;
	t2 = netem_skb_cb(q->t_head)->समय_प्रकारo_send;
	अगर (t1 < t2)
		वापस skb;
	वापस q->t_head;
पूर्ण

अटल व्योम netem_erase_head(काष्ठा netem_sched_data *q, काष्ठा sk_buff *skb)
अणु
	अगर (skb == q->t_head) अणु
		q->t_head = skb->next;
		अगर (!q->t_head)
			q->t_tail = शून्य;
	पूर्ण अन्यथा अणु
		rb_erase(&skb->rbnode, &q->t_root);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *netem_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;

tfअगरo_dequeue:
	skb = __qdisc_dequeue_head(&sch->q);
	अगर (skb) अणु
		qdisc_qstats_backlog_dec(sch, skb);
deliver:
		qdisc_bstats_update(sch, skb);
		वापस skb;
	पूर्ण
	skb = netem_peek(q);
	अगर (skb) अणु
		u64 समय_प्रकारo_send;
		u64 now = kसमय_get_ns();

		/* अगर more समय reमुख्यing? */
		समय_प्रकारo_send = netem_skb_cb(skb)->समय_प्रकारo_send;
		अगर (q->slot.slot_next && q->slot.slot_next < समय_प्रकारo_send)
			get_slot_next(q, now);

		अगर (समय_प्रकारo_send <= now && q->slot.slot_next <= now) अणु
			netem_erase_head(q, skb);
			sch->q.qlen--;
			qdisc_qstats_backlog_dec(sch, skb);
			skb->next = शून्य;
			skb->prev = शून्य;
			/* skb->dev shares skb->rbnode area,
			 * we need to restore its value.
			 */
			skb->dev = qdisc_dev(sch);

			अगर (q->slot.slot_next) अणु
				q->slot.packets_left--;
				q->slot.bytes_left -= qdisc_pkt_len(skb);
				अगर (q->slot.packets_left <= 0 ||
				    q->slot.bytes_left <= 0)
					get_slot_next(q, now);
			पूर्ण

			अगर (q->qdisc) अणु
				अचिन्हित पूर्णांक pkt_len = qdisc_pkt_len(skb);
				काष्ठा sk_buff *to_मुक्त = शून्य;
				पूर्णांक err;

				err = qdisc_enqueue(skb, q->qdisc, &to_मुक्त);
				kमुक्त_skb_list(to_मुक्त);
				अगर (err != NET_XMIT_SUCCESS &&
				    net_xmit_drop_count(err)) अणु
					qdisc_qstats_drop(sch);
					qdisc_tree_reduce_backlog(sch, 1,
								  pkt_len);
				पूर्ण
				जाओ tfअगरo_dequeue;
			पूर्ण
			जाओ deliver;
		पूर्ण

		अगर (q->qdisc) अणु
			skb = q->qdisc->ops->dequeue(q->qdisc);
			अगर (skb)
				जाओ deliver;
		पूर्ण

		qdisc_watchकरोg_schedule_ns(&q->watchकरोg,
					   max(समय_प्रकारo_send,
					       q->slot.slot_next));
	पूर्ण

	अगर (q->qdisc) अणु
		skb = q->qdisc->ops->dequeue(q->qdisc);
		अगर (skb)
			जाओ deliver;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम netem_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);

	qdisc_reset_queue(sch);
	tfअगरo_reset(sch);
	अगर (q->qdisc)
		qdisc_reset(q->qdisc);
	qdisc_watchकरोg_cancel(&q->watchकरोg);
पूर्ण

अटल व्योम dist_मुक्त(काष्ठा disttable *d)
अणु
	kvमुक्त(d);
पूर्ण

/*
 * Distribution data is a variable size payload containing
 * चिन्हित 16 bit values.
 */

अटल पूर्णांक get_dist_table(काष्ठा Qdisc *sch, काष्ठा disttable **tbl,
			  स्थिर काष्ठा nlattr *attr)
अणु
	माप_प्रकार n = nla_len(attr)/माप(__s16);
	स्थिर __s16 *data = nla_data(attr);
	spinlock_t *root_lock;
	काष्ठा disttable *d;
	पूर्णांक i;

	अगर (!n || n > NETEM_DIST_MAX)
		वापस -EINVAL;

	d = kvदो_स्मृति(माप(काष्ठा disttable) + n * माप(s16), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->size = n;
	क्रम (i = 0; i < n; i++)
		d->table[i] = data[i];

	root_lock = qdisc_root_sleeping_lock(sch);

	spin_lock_bh(root_lock);
	swap(*tbl, d);
	spin_unlock_bh(root_lock);

	dist_मुक्त(d);
	वापस 0;
पूर्ण

अटल व्योम get_slot(काष्ठा netem_sched_data *q, स्थिर काष्ठा nlattr *attr)
अणु
	स्थिर काष्ठा tc_netem_slot *c = nla_data(attr);

	q->slot_config = *c;
	अगर (q->slot_config.max_packets == 0)
		q->slot_config.max_packets = पूर्णांक_उच्च;
	अगर (q->slot_config.max_bytes == 0)
		q->slot_config.max_bytes = पूर्णांक_उच्च;

	/* capping dist_jitter to the range acceptable by tabledist() */
	q->slot_config.dist_jitter = min_t(__s64, पूर्णांक_उच्च, असल(q->slot_config.dist_jitter));

	q->slot.packets_left = q->slot_config.max_packets;
	q->slot.bytes_left = q->slot_config.max_bytes;
	अगर (q->slot_config.min_delay | q->slot_config.max_delay |
	    q->slot_config.dist_jitter)
		q->slot.slot_next = kसमय_get_ns();
	अन्यथा
		q->slot.slot_next = 0;
पूर्ण

अटल व्योम get_correlation(काष्ठा netem_sched_data *q, स्थिर काष्ठा nlattr *attr)
अणु
	स्थिर काष्ठा tc_netem_corr *c = nla_data(attr);

	init_cअक्रमom(&q->delay_cor, c->delay_corr);
	init_cअक्रमom(&q->loss_cor, c->loss_corr);
	init_cअक्रमom(&q->dup_cor, c->dup_corr);
पूर्ण

अटल व्योम get_reorder(काष्ठा netem_sched_data *q, स्थिर काष्ठा nlattr *attr)
अणु
	स्थिर काष्ठा tc_netem_reorder *r = nla_data(attr);

	q->reorder = r->probability;
	init_cअक्रमom(&q->reorder_cor, r->correlation);
पूर्ण

अटल व्योम get_corrupt(काष्ठा netem_sched_data *q, स्थिर काष्ठा nlattr *attr)
अणु
	स्थिर काष्ठा tc_netem_corrupt *r = nla_data(attr);

	q->corrupt = r->probability;
	init_cअक्रमom(&q->corrupt_cor, r->correlation);
पूर्ण

अटल व्योम get_rate(काष्ठा netem_sched_data *q, स्थिर काष्ठा nlattr *attr)
अणु
	स्थिर काष्ठा tc_netem_rate *r = nla_data(attr);

	q->rate = r->rate;
	q->packet_overhead = r->packet_overhead;
	q->cell_size = r->cell_size;
	q->cell_overhead = r->cell_overhead;
	अगर (q->cell_size)
		q->cell_size_reciprocal = reciprocal_value(q->cell_size);
	अन्यथा
		q->cell_size_reciprocal = (काष्ठा reciprocal_value) अणु 0 पूर्ण;
पूर्ण

अटल पूर्णांक get_loss_clg(काष्ठा netem_sched_data *q, स्थिर काष्ठा nlattr *attr)
अणु
	स्थिर काष्ठा nlattr *la;
	पूर्णांक rem;

	nla_क्रम_each_nested(la, attr, rem) अणु
		u16 type = nla_type(la);

		चयन (type) अणु
		हाल NETEM_LOSS_GI: अणु
			स्थिर काष्ठा tc_netem_gimodel *gi = nla_data(la);

			अगर (nla_len(la) < माप(काष्ठा tc_netem_gimodel)) अणु
				pr_info("netem: incorrect gi model size\n");
				वापस -EINVAL;
			पूर्ण

			q->loss_model = CLG_4_STATES;

			q->clg.state = TX_IN_GAP_PERIOD;
			q->clg.a1 = gi->p13;
			q->clg.a2 = gi->p31;
			q->clg.a3 = gi->p32;
			q->clg.a4 = gi->p14;
			q->clg.a5 = gi->p23;
			अवरोध;
		पूर्ण

		हाल NETEM_LOSS_GE: अणु
			स्थिर काष्ठा tc_netem_gemodel *ge = nla_data(la);

			अगर (nla_len(la) < माप(काष्ठा tc_netem_gemodel)) अणु
				pr_info("netem: incorrect ge model size\n");
				वापस -EINVAL;
			पूर्ण

			q->loss_model = CLG_GILB_ELL;
			q->clg.state = GOOD_STATE;
			q->clg.a1 = ge->p;
			q->clg.a2 = ge->r;
			q->clg.a3 = ge->h;
			q->clg.a4 = ge->k1;
			अवरोध;
		पूर्ण

		शेष:
			pr_info("netem: unknown loss type %u\n", type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy netem_policy[TCA_NETEM_MAX + 1] = अणु
	[TCA_NETEM_CORR]	= अणु .len = माप(काष्ठा tc_netem_corr) पूर्ण,
	[TCA_NETEM_REORDER]	= अणु .len = माप(काष्ठा tc_netem_reorder) पूर्ण,
	[TCA_NETEM_CORRUPT]	= अणु .len = माप(काष्ठा tc_netem_corrupt) पूर्ण,
	[TCA_NETEM_RATE]	= अणु .len = माप(काष्ठा tc_netem_rate) पूर्ण,
	[TCA_NETEM_LOSS]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_NETEM_ECN]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_NETEM_RATE64]	= अणु .type = NLA_U64 पूर्ण,
	[TCA_NETEM_LATENCY64]	= अणु .type = NLA_S64 पूर्ण,
	[TCA_NETEM_JITTER64]	= अणु .type = NLA_S64 पूर्ण,
	[TCA_NETEM_SLOT]	= अणु .len = माप(काष्ठा tc_netem_slot) पूर्ण,
पूर्ण;

अटल पूर्णांक parse_attr(काष्ठा nlattr *tb[], पूर्णांक maxtype, काष्ठा nlattr *nla,
		      स्थिर काष्ठा nla_policy *policy, पूर्णांक len)
अणु
	पूर्णांक nested_len = nla_len(nla) - NLA_ALIGN(len);

	अगर (nested_len < 0) अणु
		pr_info("netem: invalid attributes len %d\n", nested_len);
		वापस -EINVAL;
	पूर्ण

	अगर (nested_len >= nla_attr_size(0))
		वापस nla_parse_deprecated(tb, maxtype,
					    nla_data(nla) + NLA_ALIGN(len),
					    nested_len, policy, शून्य);

	स_रखो(tb, 0, माप(काष्ठा nlattr *) * (maxtype + 1));
	वापस 0;
पूर्ण

/* Parse netlink message to set options */
अटल पूर्णांक netem_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_NETEM_MAX + 1];
	काष्ठा tc_netem_qopt *qopt;
	काष्ठा clgstate old_clg;
	पूर्णांक old_loss_model = CLG_RANDOM;
	पूर्णांक ret;

	अगर (opt == शून्य)
		वापस -EINVAL;

	qopt = nla_data(opt);
	ret = parse_attr(tb, TCA_NETEM_MAX, opt, netem_policy, माप(*qopt));
	अगर (ret < 0)
		वापस ret;

	/* backup q->clg and q->loss_model */
	old_clg = q->clg;
	old_loss_model = q->loss_model;

	अगर (tb[TCA_NETEM_LOSS]) अणु
		ret = get_loss_clg(q, tb[TCA_NETEM_LOSS]);
		अगर (ret) अणु
			q->loss_model = old_loss_model;
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		q->loss_model = CLG_RANDOM;
	पूर्ण

	अगर (tb[TCA_NETEM_DELAY_DIST]) अणु
		ret = get_dist_table(sch, &q->delay_dist,
				     tb[TCA_NETEM_DELAY_DIST]);
		अगर (ret)
			जाओ get_table_failure;
	पूर्ण

	अगर (tb[TCA_NETEM_SLOT_DIST]) अणु
		ret = get_dist_table(sch, &q->slot_dist,
				     tb[TCA_NETEM_SLOT_DIST]);
		अगर (ret)
			जाओ get_table_failure;
	पूर्ण

	sch->limit = qopt->limit;

	q->latency = PSCHED_TICKS2NS(qopt->latency);
	q->jitter = PSCHED_TICKS2NS(qopt->jitter);
	q->limit = qopt->limit;
	q->gap = qopt->gap;
	q->counter = 0;
	q->loss = qopt->loss;
	q->duplicate = qopt->duplicate;

	/* क्रम compatibility with earlier versions.
	 * अगर gap is set, need to assume 100% probability
	 */
	अगर (q->gap)
		q->reorder = ~0;

	अगर (tb[TCA_NETEM_CORR])
		get_correlation(q, tb[TCA_NETEM_CORR]);

	अगर (tb[TCA_NETEM_REORDER])
		get_reorder(q, tb[TCA_NETEM_REORDER]);

	अगर (tb[TCA_NETEM_CORRUPT])
		get_corrupt(q, tb[TCA_NETEM_CORRUPT]);

	अगर (tb[TCA_NETEM_RATE])
		get_rate(q, tb[TCA_NETEM_RATE]);

	अगर (tb[TCA_NETEM_RATE64])
		q->rate = max_t(u64, q->rate,
				nla_get_u64(tb[TCA_NETEM_RATE64]));

	अगर (tb[TCA_NETEM_LATENCY64])
		q->latency = nla_get_s64(tb[TCA_NETEM_LATENCY64]);

	अगर (tb[TCA_NETEM_JITTER64])
		q->jitter = nla_get_s64(tb[TCA_NETEM_JITTER64]);

	अगर (tb[TCA_NETEM_ECN])
		q->ecn = nla_get_u32(tb[TCA_NETEM_ECN]);

	अगर (tb[TCA_NETEM_SLOT])
		get_slot(q, tb[TCA_NETEM_SLOT]);

	/* capping jitter to the range acceptable by tabledist() */
	q->jitter = min_t(s64, असल(q->jitter), पूर्णांक_उच्च);

	वापस ret;

get_table_failure:
	/* recover clg and loss_model, in हाल of
	 * q->clg and q->loss_model were modअगरied
	 * in get_loss_clg()
	 */
	q->clg = old_clg;
	q->loss_model = old_loss_model;
	वापस ret;
पूर्ण

अटल पूर्णांक netem_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	पूर्णांक ret;

	qdisc_watchकरोg_init(&q->watchकरोg, sch);

	अगर (!opt)
		वापस -EINVAL;

	q->loss_model = CLG_RANDOM;
	ret = netem_change(sch, opt, extack);
	अगर (ret)
		pr_info("netem: change failed\n");
	वापस ret;
पूर्ण

अटल व्योम netem_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);

	qdisc_watchकरोg_cancel(&q->watchकरोg);
	अगर (q->qdisc)
		qdisc_put(q->qdisc);
	dist_मुक्त(q->delay_dist);
	dist_मुक्त(q->slot_dist);
पूर्ण

अटल पूर्णांक dump_loss_model(स्थिर काष्ठा netem_sched_data *q,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_NETEM_LOSS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	चयन (q->loss_model) अणु
	हाल CLG_RANDOM:
		/* legacy loss model */
		nla_nest_cancel(skb, nest);
		वापस 0;	/* no data */

	हाल CLG_4_STATES: अणु
		काष्ठा tc_netem_gimodel gi = अणु
			.p13 = q->clg.a1,
			.p31 = q->clg.a2,
			.p32 = q->clg.a3,
			.p14 = q->clg.a4,
			.p23 = q->clg.a5,
		पूर्ण;

		अगर (nla_put(skb, NETEM_LOSS_GI, माप(gi), &gi))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण
	हाल CLG_GILB_ELL: अणु
		काष्ठा tc_netem_gemodel ge = अणु
			.p = q->clg.a1,
			.r = q->clg.a2,
			.h = q->clg.a3,
			.k1 = q->clg.a4,
		पूर्ण;

		अगर (nla_put(skb, NETEM_LOSS_GE, माप(ge), &ge))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक netem_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा netem_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *nla = (काष्ठा nlattr *) skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_netem_qopt qopt;
	काष्ठा tc_netem_corr cor;
	काष्ठा tc_netem_reorder reorder;
	काष्ठा tc_netem_corrupt corrupt;
	काष्ठा tc_netem_rate rate;
	काष्ठा tc_netem_slot slot;

	qopt.latency = min_t(psched_tdअगरf_t, PSCHED_NS2TICKS(q->latency),
			     अच_पूर्णांक_उच्च);
	qopt.jitter = min_t(psched_tdअगरf_t, PSCHED_NS2TICKS(q->jitter),
			    अच_पूर्णांक_उच्च);
	qopt.limit = q->limit;
	qopt.loss = q->loss;
	qopt.gap = q->gap;
	qopt.duplicate = q->duplicate;
	अगर (nla_put(skb, TCA_OPTIONS, माप(qopt), &qopt))
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_NETEM_LATENCY64, माप(q->latency), &q->latency))
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_NETEM_JITTER64, माप(q->jitter), &q->jitter))
		जाओ nla_put_failure;

	cor.delay_corr = q->delay_cor.rho;
	cor.loss_corr = q->loss_cor.rho;
	cor.dup_corr = q->dup_cor.rho;
	अगर (nla_put(skb, TCA_NETEM_CORR, माप(cor), &cor))
		जाओ nla_put_failure;

	reorder.probability = q->reorder;
	reorder.correlation = q->reorder_cor.rho;
	अगर (nla_put(skb, TCA_NETEM_REORDER, माप(reorder), &reorder))
		जाओ nla_put_failure;

	corrupt.probability = q->corrupt;
	corrupt.correlation = q->corrupt_cor.rho;
	अगर (nla_put(skb, TCA_NETEM_CORRUPT, माप(corrupt), &corrupt))
		जाओ nla_put_failure;

	अगर (q->rate >= (1ULL << 32)) अणु
		अगर (nla_put_u64_64bit(skb, TCA_NETEM_RATE64, q->rate,
				      TCA_NETEM_PAD))
			जाओ nla_put_failure;
		rate.rate = ~0U;
	पूर्ण अन्यथा अणु
		rate.rate = q->rate;
	पूर्ण
	rate.packet_overhead = q->packet_overhead;
	rate.cell_size = q->cell_size;
	rate.cell_overhead = q->cell_overhead;
	अगर (nla_put(skb, TCA_NETEM_RATE, माप(rate), &rate))
		जाओ nla_put_failure;

	अगर (q->ecn && nla_put_u32(skb, TCA_NETEM_ECN, q->ecn))
		जाओ nla_put_failure;

	अगर (dump_loss_model(q, skb) != 0)
		जाओ nla_put_failure;

	अगर (q->slot_config.min_delay | q->slot_config.max_delay |
	    q->slot_config.dist_jitter) अणु
		slot = q->slot_config;
		अगर (slot.max_packets == पूर्णांक_उच्च)
			slot.max_packets = 0;
		अगर (slot.max_bytes == पूर्णांक_उच्च)
			slot.max_bytes = 0;
		अगर (nla_put(skb, TCA_NETEM_SLOT, माप(slot), &slot))
			जाओ nla_put_failure;
	पूर्ण

	वापस nla_nest_end(skb, nla);

nla_put_failure:
	nlmsg_trim(skb, nla);
	वापस -1;
पूर्ण

अटल पूर्णांक netem_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);

	अगर (cl != 1 || !q->qdisc) 	/* only one class */
		वापस -ENOENT;

	tcm->tcm_handle |= TC_H_MIN(1);
	tcm->tcm_info = q->qdisc->handle;

	वापस 0;
पूर्ण

अटल पूर्णांक netem_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg, काष्ठा Qdisc *new,
		     काष्ठा Qdisc **old, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);

	*old = qdisc_replace(sch, new, &q->qdisc);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *netem_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा netem_sched_data *q = qdisc_priv(sch);
	वापस q->qdisc;
पूर्ण

अटल अचिन्हित दीर्घ netem_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 1;
पूर्ण

अटल व्योम netem_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
	अगर (!walker->stop) अणु
		अगर (walker->count >= walker->skip)
			अगर (walker->fn(sch, 1, walker) < 0) अणु
				walker->stop = 1;
				वापस;
			पूर्ण
		walker->count++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops netem_class_ops = अणु
	.graft		=	netem_graft,
	.leaf		=	netem_leaf,
	.find		=	netem_find,
	.walk		=	netem_walk,
	.dump		=	netem_dump_class,
पूर्ण;

अटल काष्ठा Qdisc_ops netem_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"netem",
	.cl_ops		=	&netem_class_ops,
	.priv_size	=	माप(काष्ठा netem_sched_data),
	.enqueue	=	netem_enqueue,
	.dequeue	=	netem_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	netem_init,
	.reset		=	netem_reset,
	.destroy	=	netem_destroy,
	.change		=	netem_change,
	.dump		=	netem_dump,
	.owner		=	THIS_MODULE,
पूर्ण;


अटल पूर्णांक __init netem_module_init(व्योम)
अणु
	pr_info("netem: version " VERSION "\n");
	वापस रेजिस्टर_qdisc(&netem_qdisc_ops);
पूर्ण
अटल व्योम __निकास netem_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&netem_qdisc_ops);
पूर्ण
module_init(netem_module_init)
module_निकास(netem_module_निकास)
MODULE_LICENSE("GPL");
