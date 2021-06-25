<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_sfq.c	Stochastic Fairness Queueing discipline.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
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
#समावेश <linux/siphash.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/red.h>


/*	Stochastic Fairness Queuing algorithm.
	=======================================

	Source:
	Paul E. McKenney "Stochastic Fairness Queuing",
	IEEE INFOCOMM'90 Proceedings, San Francisco, 1990.

	Paul E. McKenney "Stochastic Fairness Queuing",
	"Interworking: Research and Experience", v.2, 1991, p.113-131.


	See also:
	M. Shreedhar and George Varghese "Efficient Fair
	Queuing using Deficit Round Robin", Proc. SIGCOMM 95.


	This is not the thing that is usually called (W)FQ nowadays.
	It करोes not use any बारtamp mechanism, but instead
	processes queues in round-robin order.

	ADVANTAGE:

	- It is very cheap. Both CPU and memory requirements are minimal.

	DRAWBACKS:

	- "Stochastic" -> It is not 100% fair.
	When hash collisions occur, several flows are considered as one.

	- "Round-robin" -> It पूर्णांकroduces larger delays than भव घड़ी
	based schemes, and should not be used क्रम isolating पूर्णांकeractive
	traffic	from non-पूर्णांकeractive. It means, that this scheduler
	should be used as leaf of CBQ or P3, which put पूर्णांकeractive traffic
	to higher priority band.

	We still need true WFQ क्रम top level CSZ, but using WFQ
	क्रम the best efक्रमt traffic is असलolutely poपूर्णांकless:
	SFQ is superior क्रम this purpose.

	IMPLEMENTATION:
	This implementation limits :
	- maximal queue length per flow to 127 packets.
	- max mtu to 2^18-1;
	- max 65408 flows,
	- number of hash buckets to 65536.

	It is easy to increase these values, but not in flight.  */

#घोषणा SFQ_MAX_DEPTH		127 /* max number of packets per flow */
#घोषणा SFQ_DEFAULT_FLOWS	128
#घोषणा SFQ_MAX_FLOWS		(0x10000 - SFQ_MAX_DEPTH - 1) /* max number of flows */
#घोषणा SFQ_EMPTY_SLOT		0xffff
#घोषणा SFQ_DEFAULT_HASH_DIVISOR 1024

/* We use 16 bits to store allot, and want to handle packets up to 64K
 * Scale allot by 8 (1<<3) so that no overflow occurs.
 */
#घोषणा SFQ_ALLOT_SHIFT		3
#घोषणा SFQ_ALLOT_SIZE(X)	DIV_ROUND_UP(X, 1 << SFQ_ALLOT_SHIFT)

/* This type should contain at least SFQ_MAX_DEPTH + 1 + SFQ_MAX_FLOWS values */
प्रकार u16 sfq_index;

/*
 * We करोnt use poपूर्णांकers to save space.
 * Small indexes [0 ... SFQ_MAX_FLOWS - 1] are 'pointers' to slots[] array
 * जबतक following values [SFQ_MAX_FLOWS ... SFQ_MAX_FLOWS + SFQ_MAX_DEPTH]
 * are 'pointers' to dep[] array
 */
काष्ठा sfq_head अणु
	sfq_index	next;
	sfq_index	prev;
पूर्ण;

काष्ठा sfq_slot अणु
	काष्ठा sk_buff	*skblist_next;
	काष्ठा sk_buff	*skblist_prev;
	sfq_index	qlen; /* number of skbs in skblist */
	sfq_index	next; /* next slot in sfq RR chain */
	काष्ठा sfq_head dep; /* anchor in dep[] chains */
	अचिन्हित लघु	hash; /* hash value (index in ht[]) */
	लघु		allot; /* credit क्रम this slot */

	अचिन्हित पूर्णांक    backlog;
	काष्ठा red_vars vars;
पूर्ण;

काष्ठा sfq_sched_data अणु
/* frequently used fields */
	पूर्णांक		limit;		/* limit of total number of packets in this qdisc */
	अचिन्हित पूर्णांक	भागisor;	/* number of slots in hash table */
	u8		headdrop;
	u8		maxdepth;	/* limit of packets per flow */

	siphash_key_t 	perturbation;
	u8		cur_depth;	/* depth of दीर्घest slot */
	u8		flags;
	अचिन्हित लघु  scaled_quantum; /* SFQ_ALLOT_SIZE(quantum) */
	काष्ठा tcf_proto __rcu *filter_list;
	काष्ठा tcf_block *block;
	sfq_index	*ht;		/* Hash table ('divisor' slots) */
	काष्ठा sfq_slot	*slots;		/* Flows table ('maxflows' entries) */

	काष्ठा red_parms *red_parms;
	काष्ठा tc_sfqred_stats stats;
	काष्ठा sfq_slot *tail;		/* current slot in round */

	काष्ठा sfq_head	dep[SFQ_MAX_DEPTH + 1];
					/* Linked lists of slots, indexed by depth
					 * dep[0] : list of unused flows
					 * dep[1] : list of flows with 1 packet
					 * dep[X] : list of flows with X packets
					 */

	अचिन्हित पूर्णांक	maxflows;	/* number of flows in flows array */
	पूर्णांक		perturb_period;
	अचिन्हित पूर्णांक	quantum;	/* Alloपंचांगent per round: MUST BE >= MTU */
	काष्ठा समयr_list perturb_समयr;
	काष्ठा Qdisc	*sch;
पूर्ण;

/*
 * sfq_head are either in a sfq_slot or in dep[] array
 */
अटल अंतरभूत काष्ठा sfq_head *sfq_dep_head(काष्ठा sfq_sched_data *q, sfq_index val)
अणु
	अगर (val < SFQ_MAX_FLOWS)
		वापस &q->slots[val].dep;
	वापस &q->dep[val - SFQ_MAX_FLOWS];
पूर्ण

अटल अचिन्हित पूर्णांक sfq_hash(स्थिर काष्ठा sfq_sched_data *q,
			     स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_get_hash_perturb(skb, &q->perturbation) & (q->भागisor - 1);
पूर्ण

अटल अचिन्हित पूर्णांक sfq_classअगरy(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
				 पूर्णांक *qerr)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	काष्ठा tcf_result res;
	काष्ठा tcf_proto *fl;
	पूर्णांक result;

	अगर (TC_H_MAJ(skb->priority) == sch->handle &&
	    TC_H_MIN(skb->priority) > 0 &&
	    TC_H_MIN(skb->priority) <= q->भागisor)
		वापस TC_H_MIN(skb->priority);

	fl = rcu_dereference_bh(q->filter_list);
	अगर (!fl)
		वापस sfq_hash(q, skb) + 1;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	result = tcf_classअगरy(skb, fl, &res, false);
	अगर (result >= 0) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_TRAP:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
			fallthrough;
		हाल TC_ACT_SHOT:
			वापस 0;
		पूर्ण
#पूर्ण_अगर
		अगर (TC_H_MIN(res.classid) <= q->भागisor)
			वापस TC_H_MIN(res.classid);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * x : slot number [0 .. SFQ_MAX_FLOWS - 1]
 */
अटल अंतरभूत व्योम sfq_link(काष्ठा sfq_sched_data *q, sfq_index x)
अणु
	sfq_index p, n;
	काष्ठा sfq_slot *slot = &q->slots[x];
	पूर्णांक qlen = slot->qlen;

	p = qlen + SFQ_MAX_FLOWS;
	n = q->dep[qlen].next;

	slot->dep.next = n;
	slot->dep.prev = p;

	q->dep[qlen].next = x;		/* sfq_dep_head(q, p)->next = x */
	sfq_dep_head(q, n)->prev = x;
पूर्ण

#घोषणा sfq_unlink(q, x, n, p)			\
	करो अणु					\
		n = q->slots[x].dep.next;	\
		p = q->slots[x].dep.prev;	\
		sfq_dep_head(q, p)->next = n;	\
		sfq_dep_head(q, n)->prev = p;	\
	पूर्ण जबतक (0)


अटल अंतरभूत व्योम sfq_dec(काष्ठा sfq_sched_data *q, sfq_index x)
अणु
	sfq_index p, n;
	पूर्णांक d;

	sfq_unlink(q, x, n, p);

	d = q->slots[x].qlen--;
	अगर (n == p && q->cur_depth == d)
		q->cur_depth--;
	sfq_link(q, x);
पूर्ण

अटल अंतरभूत व्योम sfq_inc(काष्ठा sfq_sched_data *q, sfq_index x)
अणु
	sfq_index p, n;
	पूर्णांक d;

	sfq_unlink(q, x, n, p);

	d = ++q->slots[x].qlen;
	अगर (q->cur_depth < d)
		q->cur_depth = d;
	sfq_link(q, x);
पूर्ण

/* helper functions : might be changed when/अगर skb use a standard list_head */

/* हटाओ one skb from tail of slot queue */
अटल अंतरभूत काष्ठा sk_buff *slot_dequeue_tail(काष्ठा sfq_slot *slot)
अणु
	काष्ठा sk_buff *skb = slot->skblist_prev;

	slot->skblist_prev = skb->prev;
	skb->prev->next = (काष्ठा sk_buff *)slot;
	skb->next = skb->prev = शून्य;
	वापस skb;
पूर्ण

/* हटाओ one skb from head of slot queue */
अटल अंतरभूत काष्ठा sk_buff *slot_dequeue_head(काष्ठा sfq_slot *slot)
अणु
	काष्ठा sk_buff *skb = slot->skblist_next;

	slot->skblist_next = skb->next;
	skb->next->prev = (काष्ठा sk_buff *)slot;
	skb->next = skb->prev = शून्य;
	वापस skb;
पूर्ण

अटल अंतरभूत व्योम slot_queue_init(काष्ठा sfq_slot *slot)
अणु
	स_रखो(slot, 0, माप(*slot));
	slot->skblist_prev = slot->skblist_next = (काष्ठा sk_buff *)slot;
पूर्ण

/* add skb to slot queue (tail add) */
अटल अंतरभूत व्योम slot_queue_add(काष्ठा sfq_slot *slot, काष्ठा sk_buff *skb)
अणु
	skb->prev = slot->skblist_prev;
	skb->next = (काष्ठा sk_buff *)slot;
	slot->skblist_prev->next = skb;
	slot->skblist_prev = skb;
पूर्ण

अटल अचिन्हित पूर्णांक sfq_drop(काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	sfq_index x, d = q->cur_depth;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;
	काष्ठा sfq_slot *slot;

	/* Queue is full! Find the दीर्घest slot and drop tail packet from it */
	अगर (d > 1) अणु
		x = q->dep[d].next;
		slot = &q->slots[x];
drop:
		skb = q->headdrop ? slot_dequeue_head(slot) : slot_dequeue_tail(slot);
		len = qdisc_pkt_len(skb);
		slot->backlog -= len;
		sfq_dec(q, x);
		sch->q.qlen--;
		qdisc_qstats_backlog_dec(sch, skb);
		qdisc_drop(skb, sch, to_मुक्त);
		वापस len;
	पूर्ण

	अगर (d == 1) अणु
		/* It is dअगरficult to believe, but ALL THE SLOTS HAVE LENGTH 1. */
		x = q->tail->next;
		slot = &q->slots[x];
		q->tail->next = slot->next;
		q->ht[slot->hash] = SFQ_EMPTY_SLOT;
		जाओ drop;
	पूर्ण

	वापस 0;
पूर्ण

/* Is ECN parameter configured */
अटल पूर्णांक sfq_prob_mark(स्थिर काष्ठा sfq_sched_data *q)
अणु
	वापस q->flags & TC_RED_ECN;
पूर्ण

/* Should packets over max threshold just be marked */
अटल पूर्णांक sfq_hard_mark(स्थिर काष्ठा sfq_sched_data *q)
अणु
	वापस (q->flags & (TC_RED_ECN | TC_RED_HARDDROP)) == TC_RED_ECN;
पूर्ण

अटल पूर्णांक sfq_headdrop(स्थिर काष्ठा sfq_sched_data *q)
अणु
	वापस q->headdrop;
पूर्ण

अटल पूर्णांक
sfq_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch, काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक hash, dropped;
	sfq_index x, qlen;
	काष्ठा sfq_slot *slot;
	पूर्णांक ret;
	काष्ठा sk_buff *head;
	पूर्णांक delta;

	hash = sfq_classअगरy(skb, sch, &ret);
	अगर (hash == 0) अणु
		अगर (ret & __NET_XMIT_BYPASS)
			qdisc_qstats_drop(sch);
		__qdisc_drop(skb, to_मुक्त);
		वापस ret;
	पूर्ण
	hash--;

	x = q->ht[hash];
	slot = &q->slots[x];
	अगर (x == SFQ_EMPTY_SLOT) अणु
		x = q->dep[0].next; /* get a मुक्त slot */
		अगर (x >= SFQ_MAX_FLOWS)
			वापस qdisc_drop(skb, sch, to_मुक्त);
		q->ht[hash] = x;
		slot = &q->slots[x];
		slot->hash = hash;
		slot->backlog = 0; /* should alपढ़ोy be 0 anyway... */
		red_set_vars(&slot->vars);
		जाओ enqueue;
	पूर्ण
	अगर (q->red_parms) अणु
		slot->vars.qavg = red_calc_qavg_no_idle_समय(q->red_parms,
							&slot->vars,
							slot->backlog);
		चयन (red_action(q->red_parms,
				   &slot->vars,
				   slot->vars.qavg)) अणु
		हाल RED_DONT_MARK:
			अवरोध;

		हाल RED_PROB_MARK:
			qdisc_qstats_overlimit(sch);
			अगर (sfq_prob_mark(q)) अणु
				/* We know we have at least one packet in queue */
				अगर (sfq_headdrop(q) &&
				    INET_ECN_set_ce(slot->skblist_next)) अणु
					q->stats.prob_mark_head++;
					अवरोध;
				पूर्ण
				अगर (INET_ECN_set_ce(skb)) अणु
					q->stats.prob_mark++;
					अवरोध;
				पूर्ण
			पूर्ण
			q->stats.prob_drop++;
			जाओ congestion_drop;

		हाल RED_HARD_MARK:
			qdisc_qstats_overlimit(sch);
			अगर (sfq_hard_mark(q)) अणु
				/* We know we have at least one packet in queue */
				अगर (sfq_headdrop(q) &&
				    INET_ECN_set_ce(slot->skblist_next)) अणु
					q->stats.क्रमced_mark_head++;
					अवरोध;
				पूर्ण
				अगर (INET_ECN_set_ce(skb)) अणु
					q->stats.क्रमced_mark++;
					अवरोध;
				पूर्ण
			पूर्ण
			q->stats.क्रमced_drop++;
			जाओ congestion_drop;
		पूर्ण
	पूर्ण

	अगर (slot->qlen >= q->maxdepth) अणु
congestion_drop:
		अगर (!sfq_headdrop(q))
			वापस qdisc_drop(skb, sch, to_मुक्त);

		/* We know we have at least one packet in queue */
		head = slot_dequeue_head(slot);
		delta = qdisc_pkt_len(head) - qdisc_pkt_len(skb);
		sch->qstats.backlog -= delta;
		slot->backlog -= delta;
		qdisc_drop(head, sch, to_मुक्त);

		slot_queue_add(slot, skb);
		qdisc_tree_reduce_backlog(sch, 0, delta);
		वापस NET_XMIT_CN;
	पूर्ण

enqueue:
	qdisc_qstats_backlog_inc(sch, skb);
	slot->backlog += qdisc_pkt_len(skb);
	slot_queue_add(slot, skb);
	sfq_inc(q, x);
	अगर (slot->qlen == 1) अणु		/* The flow is new */
		अगर (q->tail == शून्य) अणु	/* It is the first flow */
			slot->next = x;
		पूर्ण अन्यथा अणु
			slot->next = q->tail->next;
			q->tail->next = x;
		पूर्ण
		/* We put this flow at the end of our flow list.
		 * This might sound unfair क्रम a new flow to रुको after old ones,
		 * but we could endup servicing new flows only, and मुक्तze old ones.
		 */
		q->tail = slot;
		/* We could use a bigger initial quantum क्रम new flows */
		slot->allot = q->scaled_quantum;
	पूर्ण
	अगर (++sch->q.qlen <= q->limit)
		वापस NET_XMIT_SUCCESS;

	qlen = slot->qlen;
	dropped = sfq_drop(sch, to_मुक्त);
	/* Return Congestion Notअगरication only अगर we dropped a packet
	 * from this flow.
	 */
	अगर (qlen != slot->qlen) अणु
		qdisc_tree_reduce_backlog(sch, 0, dropped - qdisc_pkt_len(skb));
		वापस NET_XMIT_CN;
	पूर्ण

	/* As we dropped a packet, better let upper stack know this */
	qdisc_tree_reduce_backlog(sch, 1, dropped);
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल काष्ठा sk_buff *
sfq_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	sfq_index a, next_a;
	काष्ठा sfq_slot *slot;

	/* No active slots */
	अगर (q->tail == शून्य)
		वापस शून्य;

next_slot:
	a = q->tail->next;
	slot = &q->slots[a];
	अगर (slot->allot <= 0) अणु
		q->tail = slot;
		slot->allot += q->scaled_quantum;
		जाओ next_slot;
	पूर्ण
	skb = slot_dequeue_head(slot);
	sfq_dec(q, a);
	qdisc_bstats_update(sch, skb);
	sch->q.qlen--;
	qdisc_qstats_backlog_dec(sch, skb);
	slot->backlog -= qdisc_pkt_len(skb);
	/* Is the slot empty? */
	अगर (slot->qlen == 0) अणु
		q->ht[slot->hash] = SFQ_EMPTY_SLOT;
		next_a = slot->next;
		अगर (a == next_a) अणु
			q->tail = शून्य; /* no more active slots */
			वापस skb;
		पूर्ण
		q->tail->next = next_a;
	पूर्ण अन्यथा अणु
		slot->allot -= SFQ_ALLOT_SIZE(qdisc_pkt_len(skb));
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम
sfq_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = sfq_dequeue(sch)) != शून्य)
		rtnl_kमुक्त_skbs(skb, skb);
पूर्ण

/*
 * When q->perturbation is changed, we rehash all queued skbs
 * to aव्योम OOO (Out Of Order) effects.
 * We करोnt use sfq_dequeue()/sfq_enqueue() because we करोnt want to change
 * counters.
 */
अटल व्योम sfq_rehash(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	काष्ठा sfq_slot *slot;
	काष्ठा sk_buff_head list;
	पूर्णांक dropped = 0;
	अचिन्हित पूर्णांक drop_len = 0;

	__skb_queue_head_init(&list);

	क्रम (i = 0; i < q->maxflows; i++) अणु
		slot = &q->slots[i];
		अगर (!slot->qlen)
			जारी;
		जबतक (slot->qlen) अणु
			skb = slot_dequeue_head(slot);
			sfq_dec(q, i);
			__skb_queue_tail(&list, skb);
		पूर्ण
		slot->backlog = 0;
		red_set_vars(&slot->vars);
		q->ht[slot->hash] = SFQ_EMPTY_SLOT;
	पूर्ण
	q->tail = शून्य;

	जबतक ((skb = __skb_dequeue(&list)) != शून्य) अणु
		अचिन्हित पूर्णांक hash = sfq_hash(q, skb);
		sfq_index x = q->ht[hash];

		slot = &q->slots[x];
		अगर (x == SFQ_EMPTY_SLOT) अणु
			x = q->dep[0].next; /* get a मुक्त slot */
			अगर (x >= SFQ_MAX_FLOWS) अणु
drop:
				qdisc_qstats_backlog_dec(sch, skb);
				drop_len += qdisc_pkt_len(skb);
				kमुक्त_skb(skb);
				dropped++;
				जारी;
			पूर्ण
			q->ht[hash] = x;
			slot = &q->slots[x];
			slot->hash = hash;
		पूर्ण
		अगर (slot->qlen >= q->maxdepth)
			जाओ drop;
		slot_queue_add(slot, skb);
		अगर (q->red_parms)
			slot->vars.qavg = red_calc_qavg(q->red_parms,
							&slot->vars,
							slot->backlog);
		slot->backlog += qdisc_pkt_len(skb);
		sfq_inc(q, x);
		अगर (slot->qlen == 1) अणु		/* The flow is new */
			अगर (q->tail == शून्य) अणु	/* It is the first flow */
				slot->next = x;
			पूर्ण अन्यथा अणु
				slot->next = q->tail->next;
				q->tail->next = x;
			पूर्ण
			q->tail = slot;
			slot->allot = q->scaled_quantum;
		पूर्ण
	पूर्ण
	sch->q.qlen -= dropped;
	qdisc_tree_reduce_backlog(sch, dropped, drop_len);
पूर्ण

अटल व्योम sfq_perturbation(काष्ठा समयr_list *t)
अणु
	काष्ठा sfq_sched_data *q = from_समयr(q, t, perturb_समयr);
	काष्ठा Qdisc *sch = q->sch;
	spinlock_t *root_lock = qdisc_lock(qdisc_root_sleeping(sch));
	siphash_key_t nkey;

	get_अक्रमom_bytes(&nkey, माप(nkey));
	spin_lock(root_lock);
	q->perturbation = nkey;
	अगर (!q->filter_list && q->tail)
		sfq_rehash(sch);
	spin_unlock(root_lock);

	अगर (q->perturb_period)
		mod_समयr(&q->perturb_समयr, jअगरfies + q->perturb_period);
पूर्ण

अटल पूर्णांक sfq_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_sfq_qopt *ctl = nla_data(opt);
	काष्ठा tc_sfq_qopt_v1 *ctl_v1 = शून्य;
	अचिन्हित पूर्णांक qlen, dropped = 0;
	काष्ठा red_parms *p = शून्य;
	काष्ठा sk_buff *to_मुक्त = शून्य;
	काष्ठा sk_buff *tail = शून्य;

	अगर (opt->nla_len < nla_attr_size(माप(*ctl)))
		वापस -EINVAL;
	अगर (opt->nla_len >= nla_attr_size(माप(*ctl_v1)))
		ctl_v1 = nla_data(opt);
	अगर (ctl->भागisor &&
	    (!is_घातer_of_2(ctl->भागisor) || ctl->भागisor > 65536))
		वापस -EINVAL;

	/* slot->allot is a लघु, make sure quantum is not too big. */
	अगर (ctl->quantum) अणु
		अचिन्हित पूर्णांक scaled = SFQ_ALLOT_SIZE(ctl->quantum);

		अगर (scaled <= 0 || scaled > लघु_उच्च)
			वापस -EINVAL;
	पूर्ण

	अगर (ctl_v1 && !red_check_params(ctl_v1->qth_min, ctl_v1->qth_max,
					ctl_v1->Wlog, ctl_v1->Scell_log, शून्य))
		वापस -EINVAL;
	अगर (ctl_v1 && ctl_v1->qth_min) अणु
		p = kदो_स्मृति(माप(*p), GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
	पूर्ण
	sch_tree_lock(sch);
	अगर (ctl->quantum) अणु
		q->quantum = ctl->quantum;
		q->scaled_quantum = SFQ_ALLOT_SIZE(q->quantum);
	पूर्ण
	q->perturb_period = ctl->perturb_period * HZ;
	अगर (ctl->flows)
		q->maxflows = min_t(u32, ctl->flows, SFQ_MAX_FLOWS);
	अगर (ctl->भागisor) अणु
		q->भागisor = ctl->भागisor;
		q->maxflows = min_t(u32, q->maxflows, q->भागisor);
	पूर्ण
	अगर (ctl_v1) अणु
		अगर (ctl_v1->depth)
			q->maxdepth = min_t(u32, ctl_v1->depth, SFQ_MAX_DEPTH);
		अगर (p) अणु
			swap(q->red_parms, p);
			red_set_parms(q->red_parms,
				      ctl_v1->qth_min, ctl_v1->qth_max,
				      ctl_v1->Wlog,
				      ctl_v1->Plog, ctl_v1->Scell_log,
				      शून्य,
				      ctl_v1->max_P);
		पूर्ण
		q->flags = ctl_v1->flags;
		q->headdrop = ctl_v1->headdrop;
	पूर्ण
	अगर (ctl->limit) अणु
		q->limit = min_t(u32, ctl->limit, q->maxdepth * q->maxflows);
		q->maxflows = min_t(u32, q->maxflows, q->limit);
	पूर्ण

	qlen = sch->q.qlen;
	जबतक (sch->q.qlen > q->limit) अणु
		dropped += sfq_drop(sch, &to_मुक्त);
		अगर (!tail)
			tail = to_मुक्त;
	पूर्ण

	rtnl_kमुक्त_skbs(to_मुक्त, tail);
	qdisc_tree_reduce_backlog(sch, qlen - sch->q.qlen, dropped);

	del_समयr(&q->perturb_समयr);
	अगर (q->perturb_period) अणु
		mod_समयr(&q->perturb_समयr, jअगरfies + q->perturb_period);
		get_अक्रमom_bytes(&q->perturbation, माप(q->perturbation));
	पूर्ण
	sch_tree_unlock(sch);
	kमुक्त(p);
	वापस 0;
पूर्ण

अटल व्योम *sfq_alloc(माप_प्रकार sz)
अणु
	वापस  kvदो_स्मृति(sz, GFP_KERNEL);
पूर्ण

अटल व्योम sfq_मुक्त(व्योम *addr)
अणु
	kvमुक्त(addr);
पूर्ण

अटल व्योम sfq_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);

	tcf_block_put(q->block);
	q->perturb_period = 0;
	del_समयr_sync(&q->perturb_समयr);
	sfq_मुक्त(q->ht);
	sfq_मुक्त(q->slots);
	kमुक्त(q->red_parms);
पूर्ण

अटल पूर्णांक sfq_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	पूर्णांक i;
	पूर्णांक err;

	q->sch = sch;
	समयr_setup(&q->perturb_समयr, sfq_perturbation, TIMER_DEFERRABLE);

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < SFQ_MAX_DEPTH + 1; i++) अणु
		q->dep[i].next = i + SFQ_MAX_FLOWS;
		q->dep[i].prev = i + SFQ_MAX_FLOWS;
	पूर्ण

	q->limit = SFQ_MAX_DEPTH;
	q->maxdepth = SFQ_MAX_DEPTH;
	q->cur_depth = 0;
	q->tail = शून्य;
	q->भागisor = SFQ_DEFAULT_HASH_DIVISOR;
	q->maxflows = SFQ_DEFAULT_FLOWS;
	q->quantum = psched_mtu(qdisc_dev(sch));
	q->scaled_quantum = SFQ_ALLOT_SIZE(q->quantum);
	q->perturb_period = 0;
	get_अक्रमom_bytes(&q->perturbation, माप(q->perturbation));

	अगर (opt) अणु
		पूर्णांक err = sfq_change(sch, opt);
		अगर (err)
			वापस err;
	पूर्ण

	q->ht = sfq_alloc(माप(q->ht[0]) * q->भागisor);
	q->slots = sfq_alloc(माप(q->slots[0]) * q->maxflows);
	अगर (!q->ht || !q->slots) अणु
		/* Note: sfq_destroy() will be called by our caller */
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < q->भागisor; i++)
		q->ht[i] = SFQ_EMPTY_SLOT;

	क्रम (i = 0; i < q->maxflows; i++) अणु
		slot_queue_init(&q->slots[i]);
		sfq_link(q, i);
	पूर्ण
	अगर (q->limit >= 1)
		sch->flags |= TCQ_F_CAN_BYPASS;
	अन्यथा
		sch->flags &= ~TCQ_F_CAN_BYPASS;
	वापस 0;
पूर्ण

अटल पूर्णांक sfq_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tc_sfq_qopt_v1 opt;
	काष्ठा red_parms *p = q->red_parms;

	स_रखो(&opt, 0, माप(opt));
	opt.v0.quantum	= q->quantum;
	opt.v0.perturb_period = q->perturb_period / HZ;
	opt.v0.limit	= q->limit;
	opt.v0.भागisor	= q->भागisor;
	opt.v0.flows	= q->maxflows;
	opt.depth	= q->maxdepth;
	opt.headdrop	= q->headdrop;

	अगर (p) अणु
		opt.qth_min	= p->qth_min >> p->Wlog;
		opt.qth_max	= p->qth_max >> p->Wlog;
		opt.Wlog	= p->Wlog;
		opt.Plog	= p->Plog;
		opt.Scell_log	= p->Scell_log;
		opt.max_P	= p->max_P;
	पूर्ण
	स_नकल(&opt.stats, &q->stats, माप(opt.stats));
	opt.flags	= q->flags;

	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल काष्ठा Qdisc *sfq_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ sfq_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sfq_bind(काष्ठा Qdisc *sch, अचिन्हित दीर्घ parent,
			      u32 classid)
अणु
	वापस 0;
पूर्ण

अटल व्योम sfq_unbind(काष्ठा Qdisc *q, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल काष्ठा tcf_block *sfq_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);

	अगर (cl)
		वापस शून्य;
	वापस q->block;
पूर्ण

अटल पूर्णांक sfq_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			  काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	tcm->tcm_handle |= TC_H_MIN(cl);
	वापस 0;
पूर्ण

अटल पूर्णांक sfq_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				काष्ठा gnet_dump *d)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	sfq_index idx = q->ht[cl - 1];
	काष्ठा gnet_stats_queue qs = अणु 0 पूर्ण;
	काष्ठा tc_sfq_xstats xstats = अणु 0 पूर्ण;

	अगर (idx != SFQ_EMPTY_SLOT) अणु
		स्थिर काष्ठा sfq_slot *slot = &q->slots[idx];

		xstats.allot = slot->allot << SFQ_ALLOT_SHIFT;
		qs.qlen = slot->qlen;
		qs.backlog = slot->backlog;
	पूर्ण
	अगर (gnet_stats_copy_queue(d, शून्य, &qs, qs.qlen) < 0)
		वापस -1;
	वापस gnet_stats_copy_app(d, &xstats, माप(xstats));
पूर्ण

अटल व्योम sfq_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा sfq_sched_data *q = qdisc_priv(sch);
	अचिन्हित पूर्णांक i;

	अगर (arg->stop)
		वापस;

	क्रम (i = 0; i < q->भागisor; i++) अणु
		अगर (q->ht[i] == SFQ_EMPTY_SLOT ||
		    arg->count < arg->skip) अणु
			arg->count++;
			जारी;
		पूर्ण
		अगर (arg->fn(sch, i + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops sfq_class_ops = अणु
	.leaf		=	sfq_leaf,
	.find		=	sfq_find,
	.tcf_block	=	sfq_tcf_block,
	.bind_tcf	=	sfq_bind,
	.unbind_tcf	=	sfq_unbind,
	.dump		=	sfq_dump_class,
	.dump_stats	=	sfq_dump_class_stats,
	.walk		=	sfq_walk,
पूर्ण;

अटल काष्ठा Qdisc_ops sfq_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		=	&sfq_class_ops,
	.id		=	"sfq",
	.priv_size	=	माप(काष्ठा sfq_sched_data),
	.enqueue	=	sfq_enqueue,
	.dequeue	=	sfq_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	sfq_init,
	.reset		=	sfq_reset,
	.destroy	=	sfq_destroy,
	.change		=	शून्य,
	.dump		=	sfq_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init sfq_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&sfq_qdisc_ops);
पूर्ण
अटल व्योम __निकास sfq_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&sfq_qdisc_ops);
पूर्ण
module_init(sfq_module_init)
module_निकास(sfq_module_निकास)
MODULE_LICENSE("GPL");
