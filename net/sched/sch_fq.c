<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_fq.c Fair Queue Packet Scheduler (per flow pacing)
 *
 *  Copyright (C) 2013-2015 Eric Dumazet <edumazet@google.com>
 *
 *  Meant to be mostly used क्रम locally generated traffic :
 *  Fast classअगरication depends on skb->sk being set beक्रमe reaching us.
 *  If not, (router workload), we use rxhash as fallback, with 32 bits wide hash.
 *  All packets beदीर्घing to a socket are considered as a 'flow'.
 *
 *  Flows are dynamically allocated and stored in a hash table of RB trees
 *  They are also part of one Round Robin 'queues' (new or old flows)
 *
 *  Burst aव्योमance (aka pacing) capability :
 *
 *  Transport (eg TCP) can set in sk->sk_pacing_rate a rate, enqueue a
 *  bunch of packets, and this packet scheduler adds delay between
 *  packets to respect rate limitation.
 *
 *  enqueue() :
 *   - lookup one RB tree (out of 1024 or more) to find the flow.
 *     If non existent flow, create it, add it to the tree.
 *     Add skb to the per flow list of skb (fअगरo).
 *   - Use a special fअगरo क्रम high prio packets
 *
 *  dequeue() : serves flows in Round Robin
 *  Note : When a flow becomes empty, we करो not immediately हटाओ it from
 *  rb trees, क्रम perक्रमmance reasons (its expected to send additional packets,
 *  or SLAB cache will reuse socket क्रम another flow)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/hash.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/tcp.h>

काष्ठा fq_skb_cb अणु
	u64	        समय_प्रकारo_send;
पूर्ण;

अटल अंतरभूत काष्ठा fq_skb_cb *fq_skb_cb(काष्ठा sk_buff *skb)
अणु
	qdisc_cb_निजी_validate(skb, माप(काष्ठा fq_skb_cb));
	वापस (काष्ठा fq_skb_cb *)qdisc_skb_cb(skb)->data;
पूर्ण

/*
 * Per flow काष्ठाure, dynamically allocated.
 * If packets have monotically increasing समय_प्रकारo_send, they are placed in O(1)
 * in linear list (head,tail), otherwise are placed in a rbtree (t_root).
 */
काष्ठा fq_flow अणु
/* First cache line : used in fq_gc(), fq_enqueue(), fq_dequeue() */
	काष्ठा rb_root	t_root;
	काष्ठा sk_buff	*head;		/* list of skbs क्रम this flow : first skb */
	जोड़ अणु
		काष्ठा sk_buff *tail;	/* last skb in the list */
		अचिन्हित दीर्घ  age;	/* (jअगरfies | 1UL) when flow was emptied, क्रम gc */
	पूर्ण;
	काष्ठा rb_node	fq_node;	/* anchor in fq_root[] trees */
	काष्ठा sock	*sk;
	u32		socket_hash;	/* sk_hash */
	पूर्णांक		qlen;		/* number of packets in flow queue */

/* Second cache line, used in fq_dequeue() */
	पूर्णांक		credit;
	/* 32bit hole on 64bit arches */

	काष्ठा fq_flow *next;		/* next poपूर्णांकer in RR lists */

	काष्ठा rb_node  rate_node;	/* anchor in q->delayed tree */
	u64		समय_next_packet;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा fq_flow_head अणु
	काष्ठा fq_flow *first;
	काष्ठा fq_flow *last;
पूर्ण;

काष्ठा fq_sched_data अणु
	काष्ठा fq_flow_head new_flows;

	काष्ठा fq_flow_head old_flows;

	काष्ठा rb_root	delayed;	/* क्रम rate limited flows */
	u64		समय_next_delayed_flow;
	u64		kसमय_cache;	/* copy of last kसमय_get_ns() */
	अचिन्हित दीर्घ	unthrottle_latency_ns;

	काष्ठा fq_flow	पूर्णांकernal;	/* क्रम non classअगरied or high prio packets */
	u32		quantum;
	u32		initial_quantum;
	u32		flow_refill_delay;
	u32		flow_plimit;	/* max packets per flow */
	अचिन्हित दीर्घ	flow_max_rate;	/* optional max rate per flow */
	u64		ce_threshold;
	u64		horizon;	/* horizon in ns */
	u32		orphan_mask;	/* mask क्रम orphaned skb */
	u32		low_rate_threshold;
	काष्ठा rb_root	*fq_root;
	u8		rate_enable;
	u8		fq_trees_log;
	u8		horizon_drop;
	u32		flows;
	u32		inactive_flows;
	u32		throttled_flows;

	u64		stat_gc_flows;
	u64		stat_पूर्णांकernal_packets;
	u64		stat_throttled;
	u64		stat_ce_mark;
	u64		stat_horizon_drops;
	u64		stat_horizon_caps;
	u64		stat_flows_plimit;
	u64		stat_pkts_too_दीर्घ;
	u64		stat_allocation_errors;

	u32		समयr_slack; /* hrसमयr slack in ns */
	काष्ठा qdisc_watchकरोg watchकरोg;
पूर्ण;

/*
 * f->tail and f->age share the same location.
 * We can use the low order bit to dअगरferentiate अगर this location poपूर्णांकs
 * to a sk_buff or contains a jअगरfies value, अगर we क्रमce this value to be odd.
 * This assumes f->tail low order bit must be 0 since alignof(काष्ठा sk_buff) >= 2
 */
अटल व्योम fq_flow_set_detached(काष्ठा fq_flow *f)
अणु
	f->age = jअगरfies | 1UL;
पूर्ण

अटल bool fq_flow_is_detached(स्थिर काष्ठा fq_flow *f)
अणु
	वापस !!(f->age & 1UL);
पूर्ण

/* special value to mark a throttled flow (not on old/new list) */
अटल काष्ठा fq_flow throttled;

अटल bool fq_flow_is_throttled(स्थिर काष्ठा fq_flow *f)
अणु
	वापस f->next == &throttled;
पूर्ण

अटल व्योम fq_flow_add_tail(काष्ठा fq_flow_head *head, काष्ठा fq_flow *flow)
अणु
	अगर (head->first)
		head->last->next = flow;
	अन्यथा
		head->first = flow;
	head->last = flow;
	flow->next = शून्य;
पूर्ण

अटल व्योम fq_flow_unset_throttled(काष्ठा fq_sched_data *q, काष्ठा fq_flow *f)
अणु
	rb_erase(&f->rate_node, &q->delayed);
	q->throttled_flows--;
	fq_flow_add_tail(&q->old_flows, f);
पूर्ण

अटल व्योम fq_flow_set_throttled(काष्ठा fq_sched_data *q, काष्ठा fq_flow *f)
अणु
	काष्ठा rb_node **p = &q->delayed.rb_node, *parent = शून्य;

	जबतक (*p) अणु
		काष्ठा fq_flow *aux;

		parent = *p;
		aux = rb_entry(parent, काष्ठा fq_flow, rate_node);
		अगर (f->समय_next_packet >= aux->समय_next_packet)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&f->rate_node, parent, p);
	rb_insert_color(&f->rate_node, &q->delayed);
	q->throttled_flows++;
	q->stat_throttled++;

	f->next = &throttled;
	अगर (q->समय_next_delayed_flow > f->समय_next_packet)
		q->समय_next_delayed_flow = f->समय_next_packet;
पूर्ण


अटल काष्ठा kmem_cache *fq_flow_cachep __पढ़ो_mostly;


/* limit number of collected flows per round */
#घोषणा FQ_GC_MAX 8
#घोषणा FQ_GC_AGE (3*HZ)

अटल bool fq_gc_candidate(स्थिर काष्ठा fq_flow *f)
अणु
	वापस fq_flow_is_detached(f) &&
	       समय_after(jअगरfies, f->age + FQ_GC_AGE);
पूर्ण

अटल व्योम fq_gc(काष्ठा fq_sched_data *q,
		  काष्ठा rb_root *root,
		  काष्ठा sock *sk)
अणु
	काष्ठा rb_node **p, *parent;
	व्योम *toमुक्त[FQ_GC_MAX];
	काष्ठा fq_flow *f;
	पूर्णांक i, fcnt = 0;

	p = &root->rb_node;
	parent = शून्य;
	जबतक (*p) अणु
		parent = *p;

		f = rb_entry(parent, काष्ठा fq_flow, fq_node);
		अगर (f->sk == sk)
			अवरोध;

		अगर (fq_gc_candidate(f)) अणु
			toमुक्त[fcnt++] = f;
			अगर (fcnt == FQ_GC_MAX)
				अवरोध;
		पूर्ण

		अगर (f->sk > sk)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण

	अगर (!fcnt)
		वापस;

	क्रम (i = fcnt; i > 0; ) अणु
		f = toमुक्त[--i];
		rb_erase(&f->fq_node, root);
	पूर्ण
	q->flows -= fcnt;
	q->inactive_flows -= fcnt;
	q->stat_gc_flows += fcnt;

	kmem_cache_मुक्त_bulk(fq_flow_cachep, fcnt, toमुक्त);
पूर्ण

अटल काष्ठा fq_flow *fq_classअगरy(काष्ठा sk_buff *skb, काष्ठा fq_sched_data *q)
अणु
	काष्ठा rb_node **p, *parent;
	काष्ठा sock *sk = skb->sk;
	काष्ठा rb_root *root;
	काष्ठा fq_flow *f;

	/* warning: no starvation prevention... */
	अगर (unlikely((skb->priority & TC_PRIO_MAX) == TC_PRIO_CONTROL))
		वापस &q->पूर्णांकernal;

	/* SYNACK messages are attached to a TCP_NEW_SYN_RECV request socket
	 * or a listener (SYNCOOKIE mode)
	 * 1) request sockets are not full blown,
	 *    they करो not contain sk_pacing_rate
	 * 2) They are not part of a 'flow' yet
	 * 3) We करो not want to rate limit them (eg SYNFLOOD attack),
	 *    especially अगर the listener set SO_MAX_PACING_RATE
	 * 4) We pretend they are orphaned
	 */
	अगर (!sk || sk_listener(sk)) अणु
		अचिन्हित दीर्घ hash = skb_get_hash(skb) & q->orphan_mask;

		/* By क्रमcing low order bit to 1, we make sure to not
		 * collide with a local flow (socket poपूर्णांकers are word aligned)
		 */
		sk = (काष्ठा sock *)((hash << 1) | 1UL);
		skb_orphan(skb);
	पूर्ण अन्यथा अगर (sk->sk_state == TCP_CLOSE) अणु
		अचिन्हित दीर्घ hash = skb_get_hash(skb) & q->orphan_mask;
		/*
		 * Sockets in TCP_CLOSE are non connected.
		 * Typical use हाल is UDP sockets, they can send packets
		 * with sendto() to many dअगरferent destinations.
		 * We probably could use a generic bit advertising
		 * non connected sockets, instead of sk_state == TCP_CLOSE,
		 * अगर we care enough.
		 */
		sk = (काष्ठा sock *)((hash << 1) | 1UL);
	पूर्ण

	root = &q->fq_root[hash_ptr(sk, q->fq_trees_log)];

	अगर (q->flows >= (2U << q->fq_trees_log) &&
	    q->inactive_flows > q->flows/2)
		fq_gc(q, root, sk);

	p = &root->rb_node;
	parent = शून्य;
	जबतक (*p) अणु
		parent = *p;

		f = rb_entry(parent, काष्ठा fq_flow, fq_node);
		अगर (f->sk == sk) अणु
			/* socket might have been पुनः_स्मृतिated, so check
			 * अगर its sk_hash is the same.
			 * It not, we need to refill credit with
			 * initial quantum
			 */
			अगर (unlikely(skb->sk == sk &&
				     f->socket_hash != sk->sk_hash)) अणु
				f->credit = q->initial_quantum;
				f->socket_hash = sk->sk_hash;
				अगर (q->rate_enable)
					smp_store_release(&sk->sk_pacing_status,
							  SK_PACING_FQ);
				अगर (fq_flow_is_throttled(f))
					fq_flow_unset_throttled(q, f);
				f->समय_next_packet = 0ULL;
			पूर्ण
			वापस f;
		पूर्ण
		अगर (f->sk > sk)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण

	f = kmem_cache_zalloc(fq_flow_cachep, GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!f)) अणु
		q->stat_allocation_errors++;
		वापस &q->पूर्णांकernal;
	पूर्ण
	/* f->t_root is alपढ़ोy zeroed after kmem_cache_zalloc() */

	fq_flow_set_detached(f);
	f->sk = sk;
	अगर (skb->sk == sk) अणु
		f->socket_hash = sk->sk_hash;
		अगर (q->rate_enable)
			smp_store_release(&sk->sk_pacing_status,
					  SK_PACING_FQ);
	पूर्ण
	f->credit = q->initial_quantum;

	rb_link_node(&f->fq_node, parent, p);
	rb_insert_color(&f->fq_node, root);

	q->flows++;
	q->inactive_flows++;
	वापस f;
पूर्ण

अटल काष्ठा sk_buff *fq_peek(काष्ठा fq_flow *flow)
अणु
	काष्ठा sk_buff *skb = skb_rb_first(&flow->t_root);
	काष्ठा sk_buff *head = flow->head;

	अगर (!skb)
		वापस head;

	अगर (!head)
		वापस skb;

	अगर (fq_skb_cb(skb)->समय_प्रकारo_send < fq_skb_cb(head)->समय_प्रकारo_send)
		वापस skb;
	वापस head;
पूर्ण

अटल व्योम fq_erase_head(काष्ठा Qdisc *sch, काष्ठा fq_flow *flow,
			  काष्ठा sk_buff *skb)
अणु
	अगर (skb == flow->head) अणु
		flow->head = skb->next;
	पूर्ण अन्यथा अणु
		rb_erase(&skb->rbnode, &flow->t_root);
		skb->dev = qdisc_dev(sch);
	पूर्ण
पूर्ण

/* Remove one skb from flow queue.
 * This skb must be the वापस value of prior fq_peek().
 */
अटल व्योम fq_dequeue_skb(काष्ठा Qdisc *sch, काष्ठा fq_flow *flow,
			   काष्ठा sk_buff *skb)
अणु
	fq_erase_head(sch, flow, skb);
	skb_mark_not_on_list(skb);
	flow->qlen--;
	qdisc_qstats_backlog_dec(sch, skb);
	sch->q.qlen--;
पूर्ण

अटल व्योम flow_queue_add(काष्ठा fq_flow *flow, काष्ठा sk_buff *skb)
अणु
	काष्ठा rb_node **p, *parent;
	काष्ठा sk_buff *head, *aux;

	head = flow->head;
	अगर (!head ||
	    fq_skb_cb(skb)->समय_प्रकारo_send >= fq_skb_cb(flow->tail)->समय_प्रकारo_send) अणु
		अगर (!head)
			flow->head = skb;
		अन्यथा
			flow->tail->next = skb;
		flow->tail = skb;
		skb->next = शून्य;
		वापस;
	पूर्ण

	p = &flow->t_root.rb_node;
	parent = शून्य;

	जबतक (*p) अणु
		parent = *p;
		aux = rb_to_skb(parent);
		अगर (fq_skb_cb(skb)->समय_प्रकारo_send >= fq_skb_cb(aux)->समय_प्रकारo_send)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&skb->rbnode, parent, p);
	rb_insert_color(&skb->rbnode, &flow->t_root);
पूर्ण

अटल bool fq_packet_beyond_horizon(स्थिर काष्ठा sk_buff *skb,
				    स्थिर काष्ठा fq_sched_data *q)
अणु
	वापस unlikely((s64)skb->tstamp > (s64)(q->kसमय_cache + q->horizon));
पूर्ण

अटल पूर्णांक fq_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
		      काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	काष्ठा fq_flow *f;

	अगर (unlikely(sch->q.qlen >= sch->limit))
		वापस qdisc_drop(skb, sch, to_मुक्त);

	अगर (!skb->tstamp) अणु
		fq_skb_cb(skb)->समय_प्रकारo_send = q->kसमय_cache = kसमय_get_ns();
	पूर्ण अन्यथा अणु
		/* Check अगर packet बारtamp is too far in the future.
		 * Try first अगर our cached value, to aव्योम kसमय_get_ns()
		 * cost in most हालs.
		 */
		अगर (fq_packet_beyond_horizon(skb, q)) अणु
			/* Refresh our cache and check another समय */
			q->kसमय_cache = kसमय_get_ns();
			अगर (fq_packet_beyond_horizon(skb, q)) अणु
				अगर (q->horizon_drop) अणु
					q->stat_horizon_drops++;
					वापस qdisc_drop(skb, sch, to_मुक्त);
				पूर्ण
				q->stat_horizon_caps++;
				skb->tstamp = q->kसमय_cache + q->horizon;
			पूर्ण
		पूर्ण
		fq_skb_cb(skb)->समय_प्रकारo_send = skb->tstamp;
	पूर्ण

	f = fq_classअगरy(skb, q);
	अगर (unlikely(f->qlen >= q->flow_plimit && f != &q->पूर्णांकernal)) अणु
		q->stat_flows_plimit++;
		वापस qdisc_drop(skb, sch, to_मुक्त);
	पूर्ण

	f->qlen++;
	qdisc_qstats_backlog_inc(sch, skb);
	अगर (fq_flow_is_detached(f)) अणु
		fq_flow_add_tail(&q->new_flows, f);
		अगर (समय_after(jअगरfies, f->age + q->flow_refill_delay))
			f->credit = max_t(u32, f->credit, q->quantum);
		q->inactive_flows--;
	पूर्ण

	/* Note: this overग_लिखोs f->age */
	flow_queue_add(f, skb);

	अगर (unlikely(f == &q->पूर्णांकernal)) अणु
		q->stat_पूर्णांकernal_packets++;
	पूर्ण
	sch->q.qlen++;

	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल व्योम fq_check_throttled(काष्ठा fq_sched_data *q, u64 now)
अणु
	अचिन्हित दीर्घ sample;
	काष्ठा rb_node *p;

	अगर (q->समय_next_delayed_flow > now)
		वापस;

	/* Update unthrottle latency EWMA.
	 * This is cheap and can help diagnosing समयr/latency problems.
	 */
	sample = (अचिन्हित दीर्घ)(now - q->समय_next_delayed_flow);
	q->unthrottle_latency_ns -= q->unthrottle_latency_ns >> 3;
	q->unthrottle_latency_ns += sample >> 3;

	q->समय_next_delayed_flow = ~0ULL;
	जबतक ((p = rb_first(&q->delayed)) != शून्य) अणु
		काष्ठा fq_flow *f = rb_entry(p, काष्ठा fq_flow, rate_node);

		अगर (f->समय_next_packet > now) अणु
			q->समय_next_delayed_flow = f->समय_next_packet;
			अवरोध;
		पूर्ण
		fq_flow_unset_throttled(q, f);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *fq_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	काष्ठा fq_flow_head *head;
	काष्ठा sk_buff *skb;
	काष्ठा fq_flow *f;
	अचिन्हित दीर्घ rate;
	u32 plen;
	u64 now;

	अगर (!sch->q.qlen)
		वापस शून्य;

	skb = fq_peek(&q->पूर्णांकernal);
	अगर (unlikely(skb)) अणु
		fq_dequeue_skb(sch, &q->पूर्णांकernal, skb);
		जाओ out;
	पूर्ण

	q->kसमय_cache = now = kसमय_get_ns();
	fq_check_throttled(q, now);
begin:
	head = &q->new_flows;
	अगर (!head->first) अणु
		head = &q->old_flows;
		अगर (!head->first) अणु
			अगर (q->समय_next_delayed_flow != ~0ULL)
				qdisc_watchकरोg_schedule_range_ns(&q->watchकरोg,
							q->समय_next_delayed_flow,
							q->समयr_slack);
			वापस शून्य;
		पूर्ण
	पूर्ण
	f = head->first;

	अगर (f->credit <= 0) अणु
		f->credit += q->quantum;
		head->first = f->next;
		fq_flow_add_tail(&q->old_flows, f);
		जाओ begin;
	पूर्ण

	skb = fq_peek(f);
	अगर (skb) अणु
		u64 समय_next_packet = max_t(u64, fq_skb_cb(skb)->समय_प्रकारo_send,
					     f->समय_next_packet);

		अगर (now < समय_next_packet) अणु
			head->first = f->next;
			f->समय_next_packet = समय_next_packet;
			fq_flow_set_throttled(q, f);
			जाओ begin;
		पूर्ण
		prefetch(&skb->end);
		अगर ((s64)(now - समय_next_packet - q->ce_threshold) > 0) अणु
			INET_ECN_set_ce(skb);
			q->stat_ce_mark++;
		पूर्ण
		fq_dequeue_skb(sch, f, skb);
	पूर्ण अन्यथा अणु
		head->first = f->next;
		/* क्रमce a pass through old_flows to prevent starvation */
		अगर ((head == &q->new_flows) && q->old_flows.first) अणु
			fq_flow_add_tail(&q->old_flows, f);
		पूर्ण अन्यथा अणु
			fq_flow_set_detached(f);
			q->inactive_flows++;
		पूर्ण
		जाओ begin;
	पूर्ण
	plen = qdisc_pkt_len(skb);
	f->credit -= plen;

	अगर (!q->rate_enable)
		जाओ out;

	rate = q->flow_max_rate;

	/* If EDT समय was provided क्रम this skb, we need to
	 * update f->समय_next_packet only अगर this qdisc enक्रमces
	 * a flow max rate.
	 */
	अगर (!skb->tstamp) अणु
		अगर (skb->sk)
			rate = min(skb->sk->sk_pacing_rate, rate);

		अगर (rate <= q->low_rate_threshold) अणु
			f->credit = 0;
		पूर्ण अन्यथा अणु
			plen = max(plen, q->quantum);
			अगर (f->credit > 0)
				जाओ out;
		पूर्ण
	पूर्ण
	अगर (rate != ~0UL) अणु
		u64 len = (u64)plen * NSEC_PER_SEC;

		अगर (likely(rate))
			len = भाग64_ul(len, rate);
		/* Since socket rate can change later,
		 * clamp the delay to 1 second.
		 * Really, providers of too big packets should be fixed !
		 */
		अगर (unlikely(len > NSEC_PER_SEC)) अणु
			len = NSEC_PER_SEC;
			q->stat_pkts_too_दीर्घ++;
		पूर्ण
		/* Account क्रम schedule/समयrs drअगरts.
		 * f->समय_next_packet was set when prior packet was sent,
		 * and current समय (@now) can be too late by tens of us.
		 */
		अगर (f->समय_next_packet)
			len -= min(len/2, now - f->समय_next_packet);
		f->समय_next_packet = now + len;
	पूर्ण
out:
	qdisc_bstats_update(sch, skb);
	वापस skb;
पूर्ण

अटल व्योम fq_flow_purge(काष्ठा fq_flow *flow)
अणु
	काष्ठा rb_node *p = rb_first(&flow->t_root);

	जबतक (p) अणु
		काष्ठा sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);
		rb_erase(&skb->rbnode, &flow->t_root);
		rtnl_kमुक्त_skbs(skb, skb);
	पूर्ण
	rtnl_kमुक्त_skbs(flow->head, flow->tail);
	flow->head = शून्य;
	flow->qlen = 0;
पूर्ण

अटल व्योम fq_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	काष्ठा rb_root *root;
	काष्ठा rb_node *p;
	काष्ठा fq_flow *f;
	अचिन्हित पूर्णांक idx;

	sch->q.qlen = 0;
	sch->qstats.backlog = 0;

	fq_flow_purge(&q->पूर्णांकernal);

	अगर (!q->fq_root)
		वापस;

	क्रम (idx = 0; idx < (1U << q->fq_trees_log); idx++) अणु
		root = &q->fq_root[idx];
		जबतक ((p = rb_first(root)) != शून्य) अणु
			f = rb_entry(p, काष्ठा fq_flow, fq_node);
			rb_erase(p, root);

			fq_flow_purge(f);

			kmem_cache_मुक्त(fq_flow_cachep, f);
		पूर्ण
	पूर्ण
	q->new_flows.first	= शून्य;
	q->old_flows.first	= शून्य;
	q->delayed		= RB_ROOT;
	q->flows		= 0;
	q->inactive_flows	= 0;
	q->throttled_flows	= 0;
पूर्ण

अटल व्योम fq_rehash(काष्ठा fq_sched_data *q,
		      काष्ठा rb_root *old_array, u32 old_log,
		      काष्ठा rb_root *new_array, u32 new_log)
अणु
	काष्ठा rb_node *op, **np, *parent;
	काष्ठा rb_root *oroot, *nroot;
	काष्ठा fq_flow *of, *nf;
	पूर्णांक fcnt = 0;
	u32 idx;

	क्रम (idx = 0; idx < (1U << old_log); idx++) अणु
		oroot = &old_array[idx];
		जबतक ((op = rb_first(oroot)) != शून्य) अणु
			rb_erase(op, oroot);
			of = rb_entry(op, काष्ठा fq_flow, fq_node);
			अगर (fq_gc_candidate(of)) अणु
				fcnt++;
				kmem_cache_मुक्त(fq_flow_cachep, of);
				जारी;
			पूर्ण
			nroot = &new_array[hash_ptr(of->sk, new_log)];

			np = &nroot->rb_node;
			parent = शून्य;
			जबतक (*np) अणु
				parent = *np;

				nf = rb_entry(parent, काष्ठा fq_flow, fq_node);
				BUG_ON(nf->sk == of->sk);

				अगर (nf->sk > of->sk)
					np = &parent->rb_right;
				अन्यथा
					np = &parent->rb_left;
			पूर्ण

			rb_link_node(&of->fq_node, parent, np);
			rb_insert_color(&of->fq_node, nroot);
		पूर्ण
	पूर्ण
	q->flows -= fcnt;
	q->inactive_flows -= fcnt;
	q->stat_gc_flows += fcnt;
पूर्ण

अटल व्योम fq_मुक्त(व्योम *addr)
अणु
	kvमुक्त(addr);
पूर्ण

अटल पूर्णांक fq_resize(काष्ठा Qdisc *sch, u32 log)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	काष्ठा rb_root *array;
	व्योम *old_fq_root;
	u32 idx;

	अगर (q->fq_root && log == q->fq_trees_log)
		वापस 0;

	/* If XPS was setup, we can allocate memory on right NUMA node */
	array = kvदो_स्मृति_node(माप(काष्ठा rb_root) << log, GFP_KERNEL | __GFP_RETRY_MAYFAIL,
			      netdev_queue_numa_node_पढ़ो(sch->dev_queue));
	अगर (!array)
		वापस -ENOMEM;

	क्रम (idx = 0; idx < (1U << log); idx++)
		array[idx] = RB_ROOT;

	sch_tree_lock(sch);

	old_fq_root = q->fq_root;
	अगर (old_fq_root)
		fq_rehash(q, old_fq_root, q->fq_trees_log, array, log);

	q->fq_root = array;
	q->fq_trees_log = log;

	sch_tree_unlock(sch);

	fq_मुक्त(old_fq_root);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy fq_policy[TCA_FQ_MAX + 1] = अणु
	[TCA_FQ_UNSPEC]			= अणु .strict_start_type = TCA_FQ_TIMER_SLACK पूर्ण,

	[TCA_FQ_PLIMIT]			= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_FLOW_PLIMIT]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_QUANTUM]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_INITIAL_QUANTUM]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_RATE_ENABLE]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_FLOW_DEFAULT_RATE]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_FLOW_MAX_RATE]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_BUCKETS_LOG]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_FLOW_REFILL_DELAY]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_ORPHAN_MASK]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_LOW_RATE_THRESHOLD]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_CE_THRESHOLD]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_TIMER_SLACK]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_HORIZON]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FQ_HORIZON_DROP]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक fq_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_FQ_MAX + 1];
	पूर्णांक err, drop_count = 0;
	अचिन्हित drop_len = 0;
	u32 fq_log;

	अगर (!opt)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_FQ_MAX, opt, fq_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	sch_tree_lock(sch);

	fq_log = q->fq_trees_log;

	अगर (tb[TCA_FQ_BUCKETS_LOG]) अणु
		u32 nval = nla_get_u32(tb[TCA_FQ_BUCKETS_LOG]);

		अगर (nval >= 1 && nval <= ilog2(256*1024))
			fq_log = nval;
		अन्यथा
			err = -EINVAL;
	पूर्ण
	अगर (tb[TCA_FQ_PLIMIT])
		sch->limit = nla_get_u32(tb[TCA_FQ_PLIMIT]);

	अगर (tb[TCA_FQ_FLOW_PLIMIT])
		q->flow_plimit = nla_get_u32(tb[TCA_FQ_FLOW_PLIMIT]);

	अगर (tb[TCA_FQ_QUANTUM]) अणु
		u32 quantum = nla_get_u32(tb[TCA_FQ_QUANTUM]);

		अगर (quantum > 0 && quantum <= (1 << 20)) अणु
			q->quantum = quantum;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG_MOD(extack, "invalid quantum");
			err = -EINVAL;
		पूर्ण
	पूर्ण

	अगर (tb[TCA_FQ_INITIAL_QUANTUM])
		q->initial_quantum = nla_get_u32(tb[TCA_FQ_INITIAL_QUANTUM]);

	अगर (tb[TCA_FQ_FLOW_DEFAULT_RATE])
		pr_warn_ratelimited("sch_fq: defrate %u ignored.\n",
				    nla_get_u32(tb[TCA_FQ_FLOW_DEFAULT_RATE]));

	अगर (tb[TCA_FQ_FLOW_MAX_RATE]) अणु
		u32 rate = nla_get_u32(tb[TCA_FQ_FLOW_MAX_RATE]);

		q->flow_max_rate = (rate == ~0U) ? ~0UL : rate;
	पूर्ण
	अगर (tb[TCA_FQ_LOW_RATE_THRESHOLD])
		q->low_rate_threshold =
			nla_get_u32(tb[TCA_FQ_LOW_RATE_THRESHOLD]);

	अगर (tb[TCA_FQ_RATE_ENABLE]) अणु
		u32 enable = nla_get_u32(tb[TCA_FQ_RATE_ENABLE]);

		अगर (enable <= 1)
			q->rate_enable = enable;
		अन्यथा
			err = -EINVAL;
	पूर्ण

	अगर (tb[TCA_FQ_FLOW_REFILL_DELAY]) अणु
		u32 usecs_delay = nla_get_u32(tb[TCA_FQ_FLOW_REFILL_DELAY]) ;

		q->flow_refill_delay = usecs_to_jअगरfies(usecs_delay);
	पूर्ण

	अगर (tb[TCA_FQ_ORPHAN_MASK])
		q->orphan_mask = nla_get_u32(tb[TCA_FQ_ORPHAN_MASK]);

	अगर (tb[TCA_FQ_CE_THRESHOLD])
		q->ce_threshold = (u64)NSEC_PER_USEC *
				  nla_get_u32(tb[TCA_FQ_CE_THRESHOLD]);

	अगर (tb[TCA_FQ_TIMER_SLACK])
		q->समयr_slack = nla_get_u32(tb[TCA_FQ_TIMER_SLACK]);

	अगर (tb[TCA_FQ_HORIZON])
		q->horizon = (u64)NSEC_PER_USEC *
				  nla_get_u32(tb[TCA_FQ_HORIZON]);

	अगर (tb[TCA_FQ_HORIZON_DROP])
		q->horizon_drop = nla_get_u8(tb[TCA_FQ_HORIZON_DROP]);

	अगर (!err) अणु

		sch_tree_unlock(sch);
		err = fq_resize(sch, fq_log);
		sch_tree_lock(sch);
	पूर्ण
	जबतक (sch->q.qlen > sch->limit) अणु
		काष्ठा sk_buff *skb = fq_dequeue(sch);

		अगर (!skb)
			अवरोध;
		drop_len += qdisc_pkt_len(skb);
		rtnl_kमुक्त_skbs(skb, skb);
		drop_count++;
	पूर्ण
	qdisc_tree_reduce_backlog(sch, drop_count, drop_len);

	sch_tree_unlock(sch);
	वापस err;
पूर्ण

अटल व्योम fq_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);

	fq_reset(sch);
	fq_मुक्त(q->fq_root);
	qdisc_watchकरोg_cancel(&q->watchकरोg);
पूर्ण

अटल पूर्णांक fq_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	पूर्णांक err;

	sch->limit		= 10000;
	q->flow_plimit		= 100;
	q->quantum		= 2 * psched_mtu(qdisc_dev(sch));
	q->initial_quantum	= 10 * psched_mtu(qdisc_dev(sch));
	q->flow_refill_delay	= msecs_to_jअगरfies(40);
	q->flow_max_rate	= ~0UL;
	q->समय_next_delayed_flow = ~0ULL;
	q->rate_enable		= 1;
	q->new_flows.first	= शून्य;
	q->old_flows.first	= शून्य;
	q->delayed		= RB_ROOT;
	q->fq_root		= शून्य;
	q->fq_trees_log		= ilog2(1024);
	q->orphan_mask		= 1024 - 1;
	q->low_rate_threshold	= 550000 / 8;

	q->समयr_slack = 10 * NSEC_PER_USEC; /* 10 usec of hrसमयr slack */

	q->horizon = 10ULL * NSEC_PER_SEC; /* 10 seconds */
	q->horizon_drop = 1; /* by शेष, drop packets beyond horizon */

	/* Default ce_threshold of 4294 seconds */
	q->ce_threshold		= (u64)NSEC_PER_USEC * ~0U;

	qdisc_watchकरोg_init_घड़ीid(&q->watchकरोg, sch, CLOCK_MONOTONIC);

	अगर (opt)
		err = fq_change(sch, opt, extack);
	अन्यथा
		err = fq_resize(sch, q->fq_trees_log);

	वापस err;
पूर्ण

अटल पूर्णांक fq_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	u64 ce_threshold = q->ce_threshold;
	u64 horizon = q->horizon;
	काष्ठा nlattr *opts;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;

	/* TCA_FQ_FLOW_DEFAULT_RATE is not used anymore */

	करो_भाग(ce_threshold, NSEC_PER_USEC);
	करो_भाग(horizon, NSEC_PER_USEC);

	अगर (nla_put_u32(skb, TCA_FQ_PLIMIT, sch->limit) ||
	    nla_put_u32(skb, TCA_FQ_FLOW_PLIMIT, q->flow_plimit) ||
	    nla_put_u32(skb, TCA_FQ_QUANTUM, q->quantum) ||
	    nla_put_u32(skb, TCA_FQ_INITIAL_QUANTUM, q->initial_quantum) ||
	    nla_put_u32(skb, TCA_FQ_RATE_ENABLE, q->rate_enable) ||
	    nla_put_u32(skb, TCA_FQ_FLOW_MAX_RATE,
			min_t(अचिन्हित दीर्घ, q->flow_max_rate, ~0U)) ||
	    nla_put_u32(skb, TCA_FQ_FLOW_REFILL_DELAY,
			jअगरfies_to_usecs(q->flow_refill_delay)) ||
	    nla_put_u32(skb, TCA_FQ_ORPHAN_MASK, q->orphan_mask) ||
	    nla_put_u32(skb, TCA_FQ_LOW_RATE_THRESHOLD,
			q->low_rate_threshold) ||
	    nla_put_u32(skb, TCA_FQ_CE_THRESHOLD, (u32)ce_threshold) ||
	    nla_put_u32(skb, TCA_FQ_BUCKETS_LOG, q->fq_trees_log) ||
	    nla_put_u32(skb, TCA_FQ_TIMER_SLACK, q->समयr_slack) ||
	    nla_put_u32(skb, TCA_FQ_HORIZON, (u32)horizon) ||
	    nla_put_u8(skb, TCA_FQ_HORIZON_DROP, q->horizon_drop))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक fq_dump_stats(काष्ठा Qdisc *sch, काष्ठा gnet_dump *d)
अणु
	काष्ठा fq_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_fq_qd_stats st;

	sch_tree_lock(sch);

	st.gc_flows		  = q->stat_gc_flows;
	st.highprio_packets	  = q->stat_पूर्णांकernal_packets;
	st.tcp_retrans		  = 0;
	st.throttled		  = q->stat_throttled;
	st.flows_plimit		  = q->stat_flows_plimit;
	st.pkts_too_दीर्घ	  = q->stat_pkts_too_दीर्घ;
	st.allocation_errors	  = q->stat_allocation_errors;
	st.समय_next_delayed_flow = q->समय_next_delayed_flow + q->समयr_slack -
				    kसमय_get_ns();
	st.flows		  = q->flows;
	st.inactive_flows	  = q->inactive_flows;
	st.throttled_flows	  = q->throttled_flows;
	st.unthrottle_latency_ns  = min_t(अचिन्हित दीर्घ,
					  q->unthrottle_latency_ns, ~0U);
	st.ce_mark		  = q->stat_ce_mark;
	st.horizon_drops	  = q->stat_horizon_drops;
	st.horizon_caps		  = q->stat_horizon_caps;
	sch_tree_unlock(sch);

	वापस gnet_stats_copy_app(d, &st, माप(st));
पूर्ण

अटल काष्ठा Qdisc_ops fq_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"fq",
	.priv_size	=	माप(काष्ठा fq_sched_data),

	.enqueue	=	fq_enqueue,
	.dequeue	=	fq_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	fq_init,
	.reset		=	fq_reset,
	.destroy	=	fq_destroy,
	.change		=	fq_change,
	.dump		=	fq_dump,
	.dump_stats	=	fq_dump_stats,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init fq_module_init(व्योम)
अणु
	पूर्णांक ret;

	fq_flow_cachep = kmem_cache_create("fq_flow_cache",
					   माप(काष्ठा fq_flow),
					   0, 0, शून्य);
	अगर (!fq_flow_cachep)
		वापस -ENOMEM;

	ret = रेजिस्टर_qdisc(&fq_qdisc_ops);
	अगर (ret)
		kmem_cache_destroy(fq_flow_cachep);
	वापस ret;
पूर्ण

अटल व्योम __निकास fq_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&fq_qdisc_ops);
	kmem_cache_destroy(fq_flow_cachep);
पूर्ण

module_init(fq_module_init)
module_निकास(fq_module_निकास)
MODULE_AUTHOR("Eric Dumazet");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fair Queue Packet Scheduler");
