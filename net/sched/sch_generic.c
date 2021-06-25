<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/sch_generic.c	Generic packet scheduler routines.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *              Jamal Hadi Salim, <hadi@cyberus.ca> 990601
 *              - Ingress support
 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skb_array.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/dst.h>
#समावेश <trace/events/qdisc.h>
#समावेश <trace/events/net.h>
#समावेश <net/xfrm.h>

/* Qdisc to use by शेष */
स्थिर काष्ठा Qdisc_ops *शेष_qdisc_ops = &pfअगरo_fast_ops;
EXPORT_SYMBOL(शेष_qdisc_ops);

अटल व्योम qdisc_maybe_clear_missed(काष्ठा Qdisc *q,
				     स्थिर काष्ठा netdev_queue *txq)
अणु
	clear_bit(__QDISC_STATE_MISSED, &q->state);

	/* Make sure the below netअगर_xmit_frozen_or_stopped()
	 * checking happens after clearing STATE_MISSED.
	 */
	smp_mb__after_atomic();

	/* Checking netअगर_xmit_frozen_or_stopped() again to
	 * make sure STATE_MISSED is set अगर the STATE_MISSED
	 * set by netअगर_tx_wake_queue()'s rescheduling of
	 * net_tx_action() is cleared by the above clear_bit().
	 */
	अगर (!netअगर_xmit_frozen_or_stopped(txq))
		set_bit(__QDISC_STATE_MISSED, &q->state);
पूर्ण

/* Main transmission queue. */

/* Modअगरications to data participating in scheduling must be रक्षित with
 * qdisc_lock(qdisc) spinlock.
 *
 * The idea is the following:
 * - enqueue, dequeue are serialized via qdisc root lock
 * - ingress filtering is also serialized via qdisc root lock
 * - updates to tree and tree walking are only करोne under the rtnl mutex.
 */

#घोषणा SKB_XOFF_MAGIC ((काष्ठा sk_buff *)1UL)

अटल अंतरभूत काष्ठा sk_buff *__skb_dequeue_bad_txq(काष्ठा Qdisc *q)
अणु
	स्थिर काष्ठा netdev_queue *txq = q->dev_queue;
	spinlock_t *lock = शून्य;
	काष्ठा sk_buff *skb;

	अगर (q->flags & TCQ_F_NOLOCK) अणु
		lock = qdisc_lock(q);
		spin_lock(lock);
	पूर्ण

	skb = skb_peek(&q->skb_bad_txq);
	अगर (skb) अणु
		/* check the reason of requeuing without tx lock first */
		txq = skb_get_tx_queue(txq->dev, skb);
		अगर (!netअगर_xmit_frozen_or_stopped(txq)) अणु
			skb = __skb_dequeue(&q->skb_bad_txq);
			अगर (qdisc_is_percpu_stats(q)) अणु
				qdisc_qstats_cpu_backlog_dec(q, skb);
				qdisc_qstats_cpu_qlen_dec(q);
			पूर्ण अन्यथा अणु
				qdisc_qstats_backlog_dec(q, skb);
				q->q.qlen--;
			पूर्ण
		पूर्ण अन्यथा अणु
			skb = SKB_XOFF_MAGIC;
			qdisc_maybe_clear_missed(q, txq);
		पूर्ण
	पूर्ण

	अगर (lock)
		spin_unlock(lock);

	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *qdisc_dequeue_skb_bad_txq(काष्ठा Qdisc *q)
अणु
	काष्ठा sk_buff *skb = skb_peek(&q->skb_bad_txq);

	अगर (unlikely(skb))
		skb = __skb_dequeue_bad_txq(q);

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम qdisc_enqueue_skb_bad_txq(काष्ठा Qdisc *q,
					     काष्ठा sk_buff *skb)
अणु
	spinlock_t *lock = शून्य;

	अगर (q->flags & TCQ_F_NOLOCK) अणु
		lock = qdisc_lock(q);
		spin_lock(lock);
	पूर्ण

	__skb_queue_tail(&q->skb_bad_txq, skb);

	अगर (qdisc_is_percpu_stats(q)) अणु
		qdisc_qstats_cpu_backlog_inc(q, skb);
		qdisc_qstats_cpu_qlen_inc(q);
	पूर्ण अन्यथा अणु
		qdisc_qstats_backlog_inc(q, skb);
		q->q.qlen++;
	पूर्ण

	अगर (lock)
		spin_unlock(lock);
पूर्ण

अटल अंतरभूत व्योम dev_requeue_skb(काष्ठा sk_buff *skb, काष्ठा Qdisc *q)
अणु
	spinlock_t *lock = शून्य;

	अगर (q->flags & TCQ_F_NOLOCK) अणु
		lock = qdisc_lock(q);
		spin_lock(lock);
	पूर्ण

	जबतक (skb) अणु
		काष्ठा sk_buff *next = skb->next;

		__skb_queue_tail(&q->gso_skb, skb);

		/* it's still part of the queue */
		अगर (qdisc_is_percpu_stats(q)) अणु
			qdisc_qstats_cpu_requeues_inc(q);
			qdisc_qstats_cpu_backlog_inc(q, skb);
			qdisc_qstats_cpu_qlen_inc(q);
		पूर्ण अन्यथा अणु
			q->qstats.requeues++;
			qdisc_qstats_backlog_inc(q, skb);
			q->q.qlen++;
		पूर्ण

		skb = next;
	पूर्ण
	अगर (lock)
		spin_unlock(lock);
	__netअगर_schedule(q);
पूर्ण

अटल व्योम try_bulk_dequeue_skb(काष्ठा Qdisc *q,
				 काष्ठा sk_buff *skb,
				 स्थिर काष्ठा netdev_queue *txq,
				 पूर्णांक *packets)
अणु
	पूर्णांक bytelimit = qdisc_avail_bulklimit(txq) - skb->len;

	जबतक (bytelimit > 0) अणु
		काष्ठा sk_buff *nskb = q->dequeue(q);

		अगर (!nskb)
			अवरोध;

		bytelimit -= nskb->len; /* covers GSO len */
		skb->next = nskb;
		skb = nskb;
		(*packets)++; /* GSO counts as one pkt */
	पूर्ण
	skb_mark_not_on_list(skb);
पूर्ण

/* This variant of try_bulk_dequeue_skb() makes sure
 * all skbs in the chain are क्रम the same txq
 */
अटल व्योम try_bulk_dequeue_skb_slow(काष्ठा Qdisc *q,
				      काष्ठा sk_buff *skb,
				      पूर्णांक *packets)
अणु
	पूर्णांक mapping = skb_get_queue_mapping(skb);
	काष्ठा sk_buff *nskb;
	पूर्णांक cnt = 0;

	करो अणु
		nskb = q->dequeue(q);
		अगर (!nskb)
			अवरोध;
		अगर (unlikely(skb_get_queue_mapping(nskb) != mapping)) अणु
			qdisc_enqueue_skb_bad_txq(q, nskb);
			अवरोध;
		पूर्ण
		skb->next = nskb;
		skb = nskb;
	पूर्ण जबतक (++cnt < 8);
	(*packets) += cnt;
	skb_mark_not_on_list(skb);
पूर्ण

/* Note that dequeue_skb can possibly वापस a SKB list (via skb->next).
 * A requeued skb (via q->gso_skb) can also be a SKB list.
 */
अटल काष्ठा sk_buff *dequeue_skb(काष्ठा Qdisc *q, bool *validate,
				   पूर्णांक *packets)
अणु
	स्थिर काष्ठा netdev_queue *txq = q->dev_queue;
	काष्ठा sk_buff *skb = शून्य;

	*packets = 1;
	अगर (unlikely(!skb_queue_empty(&q->gso_skb))) अणु
		spinlock_t *lock = शून्य;

		अगर (q->flags & TCQ_F_NOLOCK) अणु
			lock = qdisc_lock(q);
			spin_lock(lock);
		पूर्ण

		skb = skb_peek(&q->gso_skb);

		/* skb may be null अगर another cpu pulls gso_skb off in between
		 * empty check and lock.
		 */
		अगर (!skb) अणु
			अगर (lock)
				spin_unlock(lock);
			जाओ validate;
		पूर्ण

		/* skb in gso_skb were alपढ़ोy validated */
		*validate = false;
		अगर (xfrm_offload(skb))
			*validate = true;
		/* check the reason of requeuing without tx lock first */
		txq = skb_get_tx_queue(txq->dev, skb);
		अगर (!netअगर_xmit_frozen_or_stopped(txq)) अणु
			skb = __skb_dequeue(&q->gso_skb);
			अगर (qdisc_is_percpu_stats(q)) अणु
				qdisc_qstats_cpu_backlog_dec(q, skb);
				qdisc_qstats_cpu_qlen_dec(q);
			पूर्ण अन्यथा अणु
				qdisc_qstats_backlog_dec(q, skb);
				q->q.qlen--;
			पूर्ण
		पूर्ण अन्यथा अणु
			skb = शून्य;
			qdisc_maybe_clear_missed(q, txq);
		पूर्ण
		अगर (lock)
			spin_unlock(lock);
		जाओ trace;
	पूर्ण
validate:
	*validate = true;

	अगर ((q->flags & TCQ_F_ONETXQUEUE) &&
	    netअगर_xmit_frozen_or_stopped(txq)) अणु
		qdisc_maybe_clear_missed(q, txq);
		वापस skb;
	पूर्ण

	skb = qdisc_dequeue_skb_bad_txq(q);
	अगर (unlikely(skb)) अणु
		अगर (skb == SKB_XOFF_MAGIC)
			वापस शून्य;
		जाओ bulk;
	पूर्ण
	skb = q->dequeue(q);
	अगर (skb) अणु
bulk:
		अगर (qdisc_may_bulk(q))
			try_bulk_dequeue_skb(q, skb, txq, packets);
		अन्यथा
			try_bulk_dequeue_skb_slow(q, skb, packets);
	पूर्ण
trace:
	trace_qdisc_dequeue(q, txq, *packets, skb);
	वापस skb;
पूर्ण

/*
 * Transmit possibly several skbs, and handle the वापस status as
 * required. Owning running seqcount bit guarantees that
 * only one CPU can execute this function.
 *
 * Returns to the caller:
 *				false  - hardware queue frozen backoff
 *				true   - feel मुक्त to send more pkts
 */
bool sch_direct_xmit(काष्ठा sk_buff *skb, काष्ठा Qdisc *q,
		     काष्ठा net_device *dev, काष्ठा netdev_queue *txq,
		     spinlock_t *root_lock, bool validate)
अणु
	पूर्णांक ret = NETDEV_TX_BUSY;
	bool again = false;

	/* And release qdisc */
	अगर (root_lock)
		spin_unlock(root_lock);

	/* Note that we validate skb (GSO, checksum, ...) outside of locks */
	अगर (validate)
		skb = validate_xmit_skb_list(skb, dev, &again);

#अगर_घोषित CONFIG_XFRM_OFFLOAD
	अगर (unlikely(again)) अणु
		अगर (root_lock)
			spin_lock(root_lock);

		dev_requeue_skb(skb, q);
		वापस false;
	पूर्ण
#पूर्ण_अगर

	अगर (likely(skb)) अणु
		HARD_TX_LOCK(dev, txq, smp_processor_id());
		अगर (!netअगर_xmit_frozen_or_stopped(txq))
			skb = dev_hard_start_xmit(skb, dev, txq, &ret);
		अन्यथा
			qdisc_maybe_clear_missed(q, txq);

		HARD_TX_UNLOCK(dev, txq);
	पूर्ण अन्यथा अणु
		अगर (root_lock)
			spin_lock(root_lock);
		वापस true;
	पूर्ण

	अगर (root_lock)
		spin_lock(root_lock);

	अगर (!dev_xmit_complete(ret)) अणु
		/* Driver वापसed NETDEV_TX_BUSY - requeue skb */
		अगर (unlikely(ret != NETDEV_TX_BUSY))
			net_warn_ratelimited("BUG %s code %d qlen %d\n",
					     dev->name, ret, q->q.qlen);

		dev_requeue_skb(skb, q);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * NOTE: Called under qdisc_lock(q) with locally disabled BH.
 *
 * running seqcount guarantees only one CPU can process
 * this qdisc at a समय. qdisc_lock(q) serializes queue accesses क्रम
 * this queue.
 *
 *  netअगर_tx_lock serializes accesses to device driver.
 *
 *  qdisc_lock(q) and netअगर_tx_lock are mutually exclusive,
 *  अगर one is grabbed, another must be मुक्त.
 *
 * Note, that this procedure can be called by a watchकरोg समयr
 *
 * Returns to the caller:
 *				0  - queue is empty or throttled.
 *				>0 - queue is not empty.
 *
 */
अटल अंतरभूत bool qdisc_restart(काष्ठा Qdisc *q, पूर्णांक *packets)
अणु
	spinlock_t *root_lock = शून्य;
	काष्ठा netdev_queue *txq;
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;
	bool validate;

	/* Dequeue packet */
	skb = dequeue_skb(q, &validate, packets);
	अगर (unlikely(!skb))
		वापस false;

	अगर (!(q->flags & TCQ_F_NOLOCK))
		root_lock = qdisc_lock(q);

	dev = qdisc_dev(q);
	txq = skb_get_tx_queue(dev, skb);

	वापस sch_direct_xmit(skb, q, dev, txq, root_lock, validate);
पूर्ण

व्योम __qdisc_run(काष्ठा Qdisc *q)
अणु
	पूर्णांक quota = dev_tx_weight;
	पूर्णांक packets;

	जबतक (qdisc_restart(q, &packets)) अणु
		quota -= packets;
		अगर (quota <= 0) अणु
			__netअगर_schedule(q);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अचिन्हित दीर्घ dev_trans_start(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ val, res;
	अचिन्हित पूर्णांक i;

	अगर (is_vlan_dev(dev))
		dev = vlan_dev_real_dev(dev);
	अन्यथा अगर (netअगर_is_macvlan(dev))
		dev = macvlan_dev_real_dev(dev);
	res = netdev_get_tx_queue(dev, 0)->trans_start;
	क्रम (i = 1; i < dev->num_tx_queues; i++) अणु
		val = netdev_get_tx_queue(dev, i)->trans_start;
		अगर (val && समय_after(val, res))
			res = val;
	पूर्ण

	वापस res;
पूर्ण
EXPORT_SYMBOL(dev_trans_start);

अटल व्योम dev_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा net_device *dev = from_समयr(dev, t, watchकरोg_समयr);

	netअगर_tx_lock(dev);
	अगर (!qdisc_tx_is_noop(dev)) अणु
		अगर (netअगर_device_present(dev) &&
		    netअगर_running(dev) &&
		    netअगर_carrier_ok(dev)) अणु
			पूर्णांक some_queue_समयकरोut = 0;
			अचिन्हित पूर्णांक i;
			अचिन्हित दीर्घ trans_start;

			क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
				काष्ठा netdev_queue *txq;

				txq = netdev_get_tx_queue(dev, i);
				trans_start = txq->trans_start;
				अगर (netअगर_xmit_stopped(txq) &&
				    समय_after(jअगरfies, (trans_start +
							 dev->watchकरोg_समयo))) अणु
					some_queue_समयकरोut = 1;
					txq->trans_समयout++;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (some_queue_समयकरोut) अणु
				trace_net_dev_xmit_समयout(dev, i);
				WARN_ONCE(1, KERN_INFO "NETDEV WATCHDOG: %s (%s): transmit queue %u timed out\n",
				       dev->name, netdev_drivername(dev), i);
				dev->netdev_ops->nकरो_tx_समयout(dev, i);
			पूर्ण
			अगर (!mod_समयr(&dev->watchकरोg_समयr,
				       round_jअगरfies(jअगरfies +
						     dev->watchकरोg_समयo)))
				dev_hold(dev);
		पूर्ण
	पूर्ण
	netअगर_tx_unlock(dev);

	dev_put(dev);
पूर्ण

व्योम __netdev_watchकरोg_up(काष्ठा net_device *dev)
अणु
	अगर (dev->netdev_ops->nकरो_tx_समयout) अणु
		अगर (dev->watchकरोg_समयo <= 0)
			dev->watchकरोg_समयo = 5*HZ;
		अगर (!mod_समयr(&dev->watchकरोg_समयr,
			       round_jअगरfies(jअगरfies + dev->watchकरोg_समयo)))
			dev_hold(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__netdev_watchकरोg_up);

अटल व्योम dev_watchकरोg_up(काष्ठा net_device *dev)
अणु
	__netdev_watchकरोg_up(dev);
पूर्ण

अटल व्योम dev_watchकरोg_करोwn(काष्ठा net_device *dev)
अणु
	netअगर_tx_lock_bh(dev);
	अगर (del_समयr(&dev->watchकरोg_समयr))
		dev_put(dev);
	netअगर_tx_unlock_bh(dev);
पूर्ण

/**
 *	netअगर_carrier_on - set carrier
 *	@dev: network device
 *
 * Device has detected acquisition of carrier.
 */
व्योम netअगर_carrier_on(काष्ठा net_device *dev)
अणु
	अगर (test_and_clear_bit(__LINK_STATE_NOCARRIER, &dev->state)) अणु
		अगर (dev->reg_state == NETREG_UNINITIALIZED)
			वापस;
		atomic_inc(&dev->carrier_up_count);
		linkwatch_fire_event(dev);
		अगर (netअगर_running(dev))
			__netdev_watchकरोg_up(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netअगर_carrier_on);

/**
 *	netअगर_carrier_off - clear carrier
 *	@dev: network device
 *
 * Device has detected loss of carrier.
 */
व्योम netअगर_carrier_off(काष्ठा net_device *dev)
अणु
	अगर (!test_and_set_bit(__LINK_STATE_NOCARRIER, &dev->state)) अणु
		अगर (dev->reg_state == NETREG_UNINITIALIZED)
			वापस;
		atomic_inc(&dev->carrier_करोwn_count);
		linkwatch_fire_event(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(netअगर_carrier_off);

/* "NOOP" scheduler: the best scheduler, recommended क्रम all पूर्णांकerfaces
   under all circumstances. It is dअगरficult to invent anything faster or
   cheaper.
 */

अटल पूर्णांक noop_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *qdisc,
			काष्ठा sk_buff **to_मुक्त)
अणु
	__qdisc_drop(skb, to_मुक्त);
	वापस NET_XMIT_CN;
पूर्ण

अटल काष्ठा sk_buff *noop_dequeue(काष्ठा Qdisc *qdisc)
अणु
	वापस शून्य;
पूर्ण

काष्ठा Qdisc_ops noop_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"noop",
	.priv_size	=	0,
	.enqueue	=	noop_enqueue,
	.dequeue	=	noop_dequeue,
	.peek		=	noop_dequeue,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल काष्ठा netdev_queue noop_netdev_queue = अणु
	RCU_POINTER_INITIALIZER(qdisc, &noop_qdisc),
	.qdisc_sleeping	=	&noop_qdisc,
पूर्ण;

काष्ठा Qdisc noop_qdisc = अणु
	.enqueue	=	noop_enqueue,
	.dequeue	=	noop_dequeue,
	.flags		=	TCQ_F_BUILTIN,
	.ops		=	&noop_qdisc_ops,
	.q.lock		=	__SPIN_LOCK_UNLOCKED(noop_qdisc.q.lock),
	.dev_queue	=	&noop_netdev_queue,
	.running	=	SEQCNT_ZERO(noop_qdisc.running),
	.busylock	=	__SPIN_LOCK_UNLOCKED(noop_qdisc.busylock),
	.gso_skb = अणु
		.next = (काष्ठा sk_buff *)&noop_qdisc.gso_skb,
		.prev = (काष्ठा sk_buff *)&noop_qdisc.gso_skb,
		.qlen = 0,
		.lock = __SPIN_LOCK_UNLOCKED(noop_qdisc.gso_skb.lock),
	पूर्ण,
	.skb_bad_txq = अणु
		.next = (काष्ठा sk_buff *)&noop_qdisc.skb_bad_txq,
		.prev = (काष्ठा sk_buff *)&noop_qdisc.skb_bad_txq,
		.qlen = 0,
		.lock = __SPIN_LOCK_UNLOCKED(noop_qdisc.skb_bad_txq.lock),
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(noop_qdisc);

अटल पूर्णांक noqueue_init(काष्ठा Qdisc *qdisc, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	/* रेजिस्टर_qdisc() assigns a शेष of noop_enqueue अगर unset,
	 * but __dev_queue_xmit() treats noqueue only as such
	 * अगर this is शून्य - so clear it here. */
	qdisc->enqueue = शून्य;
	वापस 0;
पूर्ण

काष्ठा Qdisc_ops noqueue_qdisc_ops __पढ़ो_mostly = अणु
	.id		=	"noqueue",
	.priv_size	=	0,
	.init		=	noqueue_init,
	.enqueue	=	noop_enqueue,
	.dequeue	=	noop_dequeue,
	.peek		=	noop_dequeue,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल स्थिर u8 prio2band[TC_PRIO_MAX + 1] = अणु
	1, 2, 2, 2, 1, 2, 0, 0 , 1, 1, 1, 1, 1, 1, 1, 1
पूर्ण;

/* 3-band FIFO queue: old style, but should be a bit faster than
   generic prio+fअगरo combination.
 */

#घोषणा PFIFO_FAST_BANDS 3

/*
 * Private data क्रम a pfअगरo_fast scheduler containing:
 *	- rings क्रम priority bands
 */
काष्ठा pfअगरo_fast_priv अणु
	काष्ठा skb_array q[PFIFO_FAST_BANDS];
पूर्ण;

अटल अंतरभूत काष्ठा skb_array *band2list(काष्ठा pfअगरo_fast_priv *priv,
					  पूर्णांक band)
अणु
	वापस &priv->q[band];
पूर्ण

अटल पूर्णांक pfअगरo_fast_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *qdisc,
			      काष्ठा sk_buff **to_मुक्त)
अणु
	पूर्णांक band = prio2band[skb->priority & TC_PRIO_MAX];
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(qdisc);
	काष्ठा skb_array *q = band2list(priv, band);
	अचिन्हित पूर्णांक pkt_len = qdisc_pkt_len(skb);
	पूर्णांक err;

	err = skb_array_produce(q, skb);

	अगर (unlikely(err)) अणु
		अगर (qdisc_is_percpu_stats(qdisc))
			वापस qdisc_drop_cpu(skb, qdisc, to_मुक्त);
		अन्यथा
			वापस qdisc_drop(skb, qdisc, to_मुक्त);
	पूर्ण

	qdisc_update_stats_at_enqueue(qdisc, pkt_len);
	वापस NET_XMIT_SUCCESS;
पूर्ण

अटल काष्ठा sk_buff *pfअगरo_fast_dequeue(काष्ठा Qdisc *qdisc)
अणु
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(qdisc);
	काष्ठा sk_buff *skb = शून्य;
	bool need_retry = true;
	पूर्णांक band;

retry:
	क्रम (band = 0; band < PFIFO_FAST_BANDS && !skb; band++) अणु
		काष्ठा skb_array *q = band2list(priv, band);

		अगर (__skb_array_empty(q))
			जारी;

		skb = __skb_array_consume(q);
	पूर्ण
	अगर (likely(skb)) अणु
		qdisc_update_stats_at_dequeue(qdisc, skb);
	पूर्ण अन्यथा अगर (need_retry &&
		   test_bit(__QDISC_STATE_MISSED, &qdisc->state)) अणु
		/* Delay clearing the STATE_MISSED here to reduce
		 * the overhead of the second spin_trylock() in
		 * qdisc_run_begin() and __netअगर_schedule() calling
		 * in qdisc_run_end().
		 */
		clear_bit(__QDISC_STATE_MISSED, &qdisc->state);

		/* Make sure dequeuing happens after clearing
		 * STATE_MISSED.
		 */
		smp_mb__after_atomic();

		need_retry = false;

		जाओ retry;
	पूर्ण अन्यथा अणु
		WRITE_ONCE(qdisc->empty, true);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *pfअगरo_fast_peek(काष्ठा Qdisc *qdisc)
अणु
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(qdisc);
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक band;

	क्रम (band = 0; band < PFIFO_FAST_BANDS && !skb; band++) अणु
		काष्ठा skb_array *q = band2list(priv, band);

		skb = __skb_array_peek(q);
	पूर्ण

	वापस skb;
पूर्ण

अटल व्योम pfअगरo_fast_reset(काष्ठा Qdisc *qdisc)
अणु
	पूर्णांक i, band;
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(qdisc);

	क्रम (band = 0; band < PFIFO_FAST_BANDS; band++) अणु
		काष्ठा skb_array *q = band2list(priv, band);
		काष्ठा sk_buff *skb;

		/* शून्य ring is possible अगर destroy path is due to a failed
		 * skb_array_init() in pfअगरo_fast_init() हाल.
		 */
		अगर (!q->ring.queue)
			जारी;

		जबतक ((skb = __skb_array_consume(q)) != शून्य)
			kमुक्त_skb(skb);
	पूर्ण

	अगर (qdisc_is_percpu_stats(qdisc)) अणु
		क्रम_each_possible_cpu(i) अणु
			काष्ठा gnet_stats_queue *q;

			q = per_cpu_ptr(qdisc->cpu_qstats, i);
			q->backlog = 0;
			q->qlen = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pfअगरo_fast_dump(काष्ठा Qdisc *qdisc, काष्ठा sk_buff *skb)
अणु
	काष्ठा tc_prio_qopt opt = अणु .bands = PFIFO_FAST_BANDS पूर्ण;

	स_नकल(&opt.priomap, prio2band, TC_PRIO_MAX + 1);
	अगर (nla_put(skb, TCA_OPTIONS, माप(opt), &opt))
		जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक pfअगरo_fast_init(काष्ठा Qdisc *qdisc, काष्ठा nlattr *opt,
			   काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक qlen = qdisc_dev(qdisc)->tx_queue_len;
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(qdisc);
	पूर्णांक prio;

	/* guard against zero length rings */
	अगर (!qlen)
		वापस -EINVAL;

	क्रम (prio = 0; prio < PFIFO_FAST_BANDS; prio++) अणु
		काष्ठा skb_array *q = band2list(priv, prio);
		पूर्णांक err;

		err = skb_array_init(q, qlen, GFP_KERNEL);
		अगर (err)
			वापस -ENOMEM;
	पूर्ण

	/* Can by-pass the queue discipline */
	qdisc->flags |= TCQ_F_CAN_BYPASS;
	वापस 0;
पूर्ण

अटल व्योम pfअगरo_fast_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(sch);
	पूर्णांक prio;

	क्रम (prio = 0; prio < PFIFO_FAST_BANDS; prio++) अणु
		काष्ठा skb_array *q = band2list(priv, prio);

		/* शून्य ring is possible अगर destroy path is due to a failed
		 * skb_array_init() in pfअगरo_fast_init() हाल.
		 */
		अगर (!q->ring.queue)
			जारी;
		/* Destroy ring but no need to kमुक्त_skb because a call to
		 * pfअगरo_fast_reset() has alपढ़ोy करोne that work.
		 */
		ptr_ring_cleanup(&q->ring, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक pfअगरo_fast_change_tx_queue_len(काष्ठा Qdisc *sch,
					  अचिन्हित पूर्णांक new_len)
अणु
	काष्ठा pfअगरo_fast_priv *priv = qdisc_priv(sch);
	काष्ठा skb_array *bands[PFIFO_FAST_BANDS];
	पूर्णांक prio;

	क्रम (prio = 0; prio < PFIFO_FAST_BANDS; prio++) अणु
		काष्ठा skb_array *q = band2list(priv, prio);

		bands[prio] = q;
	पूर्ण

	वापस skb_array_resize_multiple(bands, PFIFO_FAST_BANDS, new_len,
					 GFP_KERNEL);
पूर्ण

काष्ठा Qdisc_ops pfअगरo_fast_ops __पढ़ो_mostly = अणु
	.id		=	"pfifo_fast",
	.priv_size	=	माप(काष्ठा pfअगरo_fast_priv),
	.enqueue	=	pfअगरo_fast_enqueue,
	.dequeue	=	pfअगरo_fast_dequeue,
	.peek		=	pfअगरo_fast_peek,
	.init		=	pfअगरo_fast_init,
	.destroy	=	pfअगरo_fast_destroy,
	.reset		=	pfअगरo_fast_reset,
	.dump		=	pfअगरo_fast_dump,
	.change_tx_queue_len =  pfअगरo_fast_change_tx_queue_len,
	.owner		=	THIS_MODULE,
	.अटल_flags	=	TCQ_F_NOLOCK | TCQ_F_CPUSTATS,
पूर्ण;
EXPORT_SYMBOL(pfअगरo_fast_ops);

अटल काष्ठा lock_class_key qdisc_tx_busylock;
अटल काष्ठा lock_class_key qdisc_running_key;

काष्ठा Qdisc *qdisc_alloc(काष्ठा netdev_queue *dev_queue,
			  स्थिर काष्ठा Qdisc_ops *ops,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा Qdisc *sch;
	अचिन्हित पूर्णांक size = माप(*sch) + ops->priv_size;
	पूर्णांक err = -ENOBUFS;
	काष्ठा net_device *dev;

	अगर (!dev_queue) अणु
		NL_SET_ERR_MSG(extack, "No device queue given");
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	dev = dev_queue->dev;
	sch = kzalloc_node(size, GFP_KERNEL, netdev_queue_numa_node_पढ़ो(dev_queue));

	अगर (!sch)
		जाओ errout;
	__skb_queue_head_init(&sch->gso_skb);
	__skb_queue_head_init(&sch->skb_bad_txq);
	qdisc_skb_head_init(&sch->q);
	spin_lock_init(&sch->q.lock);

	अगर (ops->अटल_flags & TCQ_F_CPUSTATS) अणु
		sch->cpu_bstats =
			netdev_alloc_pcpu_stats(काष्ठा gnet_stats_basic_cpu);
		अगर (!sch->cpu_bstats)
			जाओ errout1;

		sch->cpu_qstats = alloc_percpu(काष्ठा gnet_stats_queue);
		अगर (!sch->cpu_qstats) अणु
			मुक्त_percpu(sch->cpu_bstats);
			जाओ errout1;
		पूर्ण
	पूर्ण

	spin_lock_init(&sch->busylock);
	lockdep_set_class(&sch->busylock,
			  dev->qdisc_tx_busylock ?: &qdisc_tx_busylock);

	/* seqlock has the same scope of busylock, क्रम NOLOCK qdisc */
	spin_lock_init(&sch->seqlock);
	lockdep_set_class(&sch->busylock,
			  dev->qdisc_tx_busylock ?: &qdisc_tx_busylock);

	seqcount_init(&sch->running);
	lockdep_set_class(&sch->running,
			  dev->qdisc_running_key ?: &qdisc_running_key);

	sch->ops = ops;
	sch->flags = ops->अटल_flags;
	sch->enqueue = ops->enqueue;
	sch->dequeue = ops->dequeue;
	sch->dev_queue = dev_queue;
	sch->empty = true;
	dev_hold(dev);
	refcount_set(&sch->refcnt, 1);

	वापस sch;
errout1:
	kमुक्त(sch);
errout:
	वापस ERR_PTR(err);
पूर्ण

काष्ठा Qdisc *qdisc_create_dflt(काष्ठा netdev_queue *dev_queue,
				स्थिर काष्ठा Qdisc_ops *ops,
				अचिन्हित पूर्णांक parentid,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा Qdisc *sch;

	अगर (!try_module_get(ops->owner)) अणु
		NL_SET_ERR_MSG(extack, "Failed to increase module reference counter");
		वापस शून्य;
	पूर्ण

	sch = qdisc_alloc(dev_queue, ops, extack);
	अगर (IS_ERR(sch)) अणु
		module_put(ops->owner);
		वापस शून्य;
	पूर्ण
	sch->parent = parentid;

	अगर (!ops->init || ops->init(sch, शून्य, extack) == 0) अणु
		trace_qdisc_create(ops, dev_queue->dev, parentid);
		वापस sch;
	पूर्ण

	qdisc_put(sch);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(qdisc_create_dflt);

/* Under qdisc_lock(qdisc) and BH! */

व्योम qdisc_reset(काष्ठा Qdisc *qdisc)
अणु
	स्थिर काष्ठा Qdisc_ops *ops = qdisc->ops;
	काष्ठा sk_buff *skb, *पंचांगp;

	trace_qdisc_reset(qdisc);

	अगर (ops->reset)
		ops->reset(qdisc);

	skb_queue_walk_safe(&qdisc->gso_skb, skb, पंचांगp) अणु
		__skb_unlink(skb, &qdisc->gso_skb);
		kमुक्त_skb_list(skb);
	पूर्ण

	skb_queue_walk_safe(&qdisc->skb_bad_txq, skb, पंचांगp) अणु
		__skb_unlink(skb, &qdisc->skb_bad_txq);
		kमुक्त_skb_list(skb);
	पूर्ण

	qdisc->q.qlen = 0;
	qdisc->qstats.backlog = 0;
पूर्ण
EXPORT_SYMBOL(qdisc_reset);

व्योम qdisc_मुक्त(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc_is_percpu_stats(qdisc)) अणु
		मुक्त_percpu(qdisc->cpu_bstats);
		मुक्त_percpu(qdisc->cpu_qstats);
	पूर्ण

	kमुक्त(qdisc);
पूर्ण

अटल व्योम qdisc_मुक्त_cb(काष्ठा rcu_head *head)
अणु
	काष्ठा Qdisc *q = container_of(head, काष्ठा Qdisc, rcu);

	qdisc_मुक्त(q);
पूर्ण

अटल व्योम qdisc_destroy(काष्ठा Qdisc *qdisc)
अणु
	स्थिर काष्ठा Qdisc_ops  *ops = qdisc->ops;

#अगर_घोषित CONFIG_NET_SCHED
	qdisc_hash_del(qdisc);

	qdisc_put_stab(rtnl_dereference(qdisc->stab));
#पूर्ण_अगर
	gen_समाप्त_estimator(&qdisc->rate_est);

	qdisc_reset(qdisc);

	अगर (ops->destroy)
		ops->destroy(qdisc);

	module_put(ops->owner);
	dev_put(qdisc_dev(qdisc));

	trace_qdisc_destroy(qdisc);

	call_rcu(&qdisc->rcu, qdisc_मुक्त_cb);
पूर्ण

व्योम qdisc_put(काष्ठा Qdisc *qdisc)
अणु
	अगर (!qdisc)
		वापस;

	अगर (qdisc->flags & TCQ_F_BUILTIN ||
	    !refcount_dec_and_test(&qdisc->refcnt))
		वापस;

	qdisc_destroy(qdisc);
पूर्ण
EXPORT_SYMBOL(qdisc_put);

/* Version of qdisc_put() that is called with rtnl mutex unlocked.
 * Intended to be used as optimization, this function only takes rtnl lock अगर
 * qdisc reference counter reached zero.
 */

व्योम qdisc_put_unlocked(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc->flags & TCQ_F_BUILTIN ||
	    !refcount_dec_and_rtnl_lock(&qdisc->refcnt))
		वापस;

	qdisc_destroy(qdisc);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(qdisc_put_unlocked);

/* Attach toplevel qdisc to device queue. */
काष्ठा Qdisc *dev_graft_qdisc(काष्ठा netdev_queue *dev_queue,
			      काष्ठा Qdisc *qdisc)
अणु
	काष्ठा Qdisc *oqdisc = dev_queue->qdisc_sleeping;
	spinlock_t *root_lock;

	root_lock = qdisc_lock(oqdisc);
	spin_lock_bh(root_lock);

	/* ... and graft new one */
	अगर (qdisc == शून्य)
		qdisc = &noop_qdisc;
	dev_queue->qdisc_sleeping = qdisc;
	rcu_assign_poपूर्णांकer(dev_queue->qdisc, &noop_qdisc);

	spin_unlock_bh(root_lock);

	वापस oqdisc;
पूर्ण
EXPORT_SYMBOL(dev_graft_qdisc);

अटल व्योम attach_one_शेष_qdisc(काष्ठा net_device *dev,
				     काष्ठा netdev_queue *dev_queue,
				     व्योम *_unused)
अणु
	काष्ठा Qdisc *qdisc;
	स्थिर काष्ठा Qdisc_ops *ops = शेष_qdisc_ops;

	अगर (dev->priv_flags & IFF_NO_QUEUE)
		ops = &noqueue_qdisc_ops;
	अन्यथा अगर(dev->type == ARPHRD_CAN)
		ops = &pfअगरo_fast_ops;

	qdisc = qdisc_create_dflt(dev_queue, ops, TC_H_ROOT, शून्य);
	अगर (!qdisc)
		वापस;

	अगर (!netअगर_is_multiqueue(dev))
		qdisc->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	dev_queue->qdisc_sleeping = qdisc;
पूर्ण

अटल व्योम attach_शेष_qdiscs(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_queue *txq;
	काष्ठा Qdisc *qdisc;

	txq = netdev_get_tx_queue(dev, 0);

	अगर (!netअगर_is_multiqueue(dev) ||
	    dev->priv_flags & IFF_NO_QUEUE) अणु
		netdev_क्रम_each_tx_queue(dev, attach_one_शेष_qdisc, शून्य);
		dev->qdisc = txq->qdisc_sleeping;
		qdisc_refcount_inc(dev->qdisc);
	पूर्ण अन्यथा अणु
		qdisc = qdisc_create_dflt(txq, &mq_qdisc_ops, TC_H_ROOT, शून्य);
		अगर (qdisc) अणु
			dev->qdisc = qdisc;
			qdisc->ops->attach(qdisc);
		पूर्ण
	पूर्ण

	/* Detect शेष qdisc setup/init failed and fallback to "noqueue" */
	अगर (dev->qdisc == &noop_qdisc) अणु
		netdev_warn(dev, "default qdisc (%s) fail, fallback to %s\n",
			    शेष_qdisc_ops->id, noqueue_qdisc_ops.id);
		dev->priv_flags |= IFF_NO_QUEUE;
		netdev_क्रम_each_tx_queue(dev, attach_one_शेष_qdisc, शून्य);
		dev->qdisc = txq->qdisc_sleeping;
		qdisc_refcount_inc(dev->qdisc);
		dev->priv_flags ^= IFF_NO_QUEUE;
	पूर्ण

#अगर_घोषित CONFIG_NET_SCHED
	अगर (dev->qdisc != &noop_qdisc)
		qdisc_hash_add(dev->qdisc, false);
#पूर्ण_अगर
पूर्ण

अटल व्योम transition_one_qdisc(काष्ठा net_device *dev,
				 काष्ठा netdev_queue *dev_queue,
				 व्योम *_need_watchकरोg)
अणु
	काष्ठा Qdisc *new_qdisc = dev_queue->qdisc_sleeping;
	पूर्णांक *need_watchकरोg_p = _need_watchकरोg;

	अगर (!(new_qdisc->flags & TCQ_F_BUILTIN))
		clear_bit(__QDISC_STATE_DEACTIVATED, &new_qdisc->state);

	rcu_assign_poपूर्णांकer(dev_queue->qdisc, new_qdisc);
	अगर (need_watchकरोg_p) अणु
		dev_queue->trans_start = 0;
		*need_watchकरोg_p = 1;
	पूर्ण
पूर्ण

व्योम dev_activate(काष्ठा net_device *dev)
अणु
	पूर्णांक need_watchकरोg;

	/* No queueing discipline is attached to device;
	 * create शेष one क्रम devices, which need queueing
	 * and noqueue_qdisc क्रम भव पूर्णांकerfaces
	 */

	अगर (dev->qdisc == &noop_qdisc)
		attach_शेष_qdiscs(dev);

	अगर (!netअगर_carrier_ok(dev))
		/* Delay activation until next carrier-on event */
		वापस;

	need_watchकरोg = 0;
	netdev_क्रम_each_tx_queue(dev, transition_one_qdisc, &need_watchकरोg);
	अगर (dev_ingress_queue(dev))
		transition_one_qdisc(dev, dev_ingress_queue(dev), शून्य);

	अगर (need_watchकरोg) अणु
		netअगर_trans_update(dev);
		dev_watchकरोg_up(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dev_activate);

अटल व्योम qdisc_deactivate(काष्ठा Qdisc *qdisc)
अणु
	अगर (qdisc->flags & TCQ_F_BUILTIN)
		वापस;

	set_bit(__QDISC_STATE_DEACTIVATED, &qdisc->state);
पूर्ण

अटल व्योम dev_deactivate_queue(काष्ठा net_device *dev,
				 काष्ठा netdev_queue *dev_queue,
				 व्योम *_qdisc_शेष)
अणु
	काष्ठा Qdisc *qdisc_शेष = _qdisc_शेष;
	काष्ठा Qdisc *qdisc;

	qdisc = rtnl_dereference(dev_queue->qdisc);
	अगर (qdisc) अणु
		qdisc_deactivate(qdisc);
		rcu_assign_poपूर्णांकer(dev_queue->qdisc, qdisc_शेष);
	पूर्ण
पूर्ण

अटल व्योम dev_reset_queue(काष्ठा net_device *dev,
			    काष्ठा netdev_queue *dev_queue,
			    व्योम *_unused)
अणु
	काष्ठा Qdisc *qdisc;
	bool nolock;

	qdisc = dev_queue->qdisc_sleeping;
	अगर (!qdisc)
		वापस;

	nolock = qdisc->flags & TCQ_F_NOLOCK;

	अगर (nolock)
		spin_lock_bh(&qdisc->seqlock);
	spin_lock_bh(qdisc_lock(qdisc));

	qdisc_reset(qdisc);

	spin_unlock_bh(qdisc_lock(qdisc));
	अगर (nolock) अणु
		clear_bit(__QDISC_STATE_MISSED, &qdisc->state);
		spin_unlock_bh(&qdisc->seqlock);
	पूर्ण
पूर्ण

अटल bool some_qdisc_is_busy(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *dev_queue;
		spinlock_t *root_lock;
		काष्ठा Qdisc *q;
		पूर्णांक val;

		dev_queue = netdev_get_tx_queue(dev, i);
		q = dev_queue->qdisc_sleeping;

		root_lock = qdisc_lock(q);
		spin_lock_bh(root_lock);

		val = (qdisc_is_running(q) ||
		       test_bit(__QDISC_STATE_SCHED, &q->state));

		spin_unlock_bh(root_lock);

		अगर (val)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * 	dev_deactivate_many - deactivate transmissions on several devices
 * 	@head: list of devices to deactivate
 *
 *	This function वापसs only when all outstanding transmissions
 *	have completed, unless all devices are in dismantle phase.
 */
व्योम dev_deactivate_many(काष्ठा list_head *head)
अणु
	काष्ठा net_device *dev;

	list_क्रम_each_entry(dev, head, बंद_list) अणु
		netdev_क्रम_each_tx_queue(dev, dev_deactivate_queue,
					 &noop_qdisc);
		अगर (dev_ingress_queue(dev))
			dev_deactivate_queue(dev, dev_ingress_queue(dev),
					     &noop_qdisc);

		dev_watchकरोg_करोwn(dev);
	पूर्ण

	/* Wait क्रम outstanding qdisc-less dev_queue_xmit calls or
	 * outstanding qdisc enqueuing calls.
	 * This is aव्योमed अगर all devices are in dismantle phase :
	 * Caller will call synchronize_net() क्रम us
	 */
	synchronize_net();

	list_क्रम_each_entry(dev, head, बंद_list) अणु
		netdev_क्रम_each_tx_queue(dev, dev_reset_queue, शून्य);

		अगर (dev_ingress_queue(dev))
			dev_reset_queue(dev, dev_ingress_queue(dev), शून्य);
	पूर्ण

	/* Wait क्रम outstanding qdisc_run calls. */
	list_क्रम_each_entry(dev, head, बंद_list) अणु
		जबतक (some_qdisc_is_busy(dev)) अणु
			/* रुको_event() would aव्योम this sleep-loop but would
			 * require expensive checks in the fast paths of packet
			 * processing which isn't worth it.
			 */
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dev_deactivate(काष्ठा net_device *dev)
अणु
	LIST_HEAD(single);

	list_add(&dev->बंद_list, &single);
	dev_deactivate_many(&single);
	list_del(&single);
पूर्ण
EXPORT_SYMBOL(dev_deactivate);

अटल पूर्णांक qdisc_change_tx_queue_len(काष्ठा net_device *dev,
				     काष्ठा netdev_queue *dev_queue)
अणु
	काष्ठा Qdisc *qdisc = dev_queue->qdisc_sleeping;
	स्थिर काष्ठा Qdisc_ops *ops = qdisc->ops;

	अगर (ops->change_tx_queue_len)
		वापस ops->change_tx_queue_len(qdisc, dev->tx_queue_len);
	वापस 0;
पूर्ण

पूर्णांक dev_qdisc_change_tx_queue_len(काष्ठा net_device *dev)
अणु
	bool up = dev->flags & IFF_UP;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (up)
		dev_deactivate(dev);

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		ret = qdisc_change_tx_queue_len(dev, &dev->_tx[i]);

		/* TODO: revert changes on a partial failure */
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (up)
		dev_activate(dev);
	वापस ret;
पूर्ण

अटल व्योम dev_init_scheduler_queue(काष्ठा net_device *dev,
				     काष्ठा netdev_queue *dev_queue,
				     व्योम *_qdisc)
अणु
	काष्ठा Qdisc *qdisc = _qdisc;

	rcu_assign_poपूर्णांकer(dev_queue->qdisc, qdisc);
	dev_queue->qdisc_sleeping = qdisc;
पूर्ण

व्योम dev_init_scheduler(काष्ठा net_device *dev)
अणु
	dev->qdisc = &noop_qdisc;
	netdev_क्रम_each_tx_queue(dev, dev_init_scheduler_queue, &noop_qdisc);
	अगर (dev_ingress_queue(dev))
		dev_init_scheduler_queue(dev, dev_ingress_queue(dev), &noop_qdisc);

	समयr_setup(&dev->watchकरोg_समयr, dev_watchकरोg, 0);
पूर्ण

अटल व्योम shutकरोwn_scheduler_queue(काष्ठा net_device *dev,
				     काष्ठा netdev_queue *dev_queue,
				     व्योम *_qdisc_शेष)
अणु
	काष्ठा Qdisc *qdisc = dev_queue->qdisc_sleeping;
	काष्ठा Qdisc *qdisc_शेष = _qdisc_शेष;

	अगर (qdisc) अणु
		rcu_assign_poपूर्णांकer(dev_queue->qdisc, qdisc_शेष);
		dev_queue->qdisc_sleeping = qdisc_शेष;

		qdisc_put(qdisc);
	पूर्ण
पूर्ण

व्योम dev_shutकरोwn(काष्ठा net_device *dev)
अणु
	netdev_क्रम_each_tx_queue(dev, shutकरोwn_scheduler_queue, &noop_qdisc);
	अगर (dev_ingress_queue(dev))
		shutकरोwn_scheduler_queue(dev, dev_ingress_queue(dev), &noop_qdisc);
	qdisc_put(dev->qdisc);
	dev->qdisc = &noop_qdisc;

	WARN_ON(समयr_pending(&dev->watchकरोg_समयr));
पूर्ण

/**
 * psched_ratecfg_precompute__() - Pre-compute values क्रम reciprocal भागision
 * @rate:   Rate to compute reciprocal भागision values of
 * @mult:   Multiplier क्रम reciprocal भागision
 * @shअगरt:  Shअगरt क्रम reciprocal भागision
 *
 * The multiplier and shअगरt क्रम reciprocal भागision by rate are stored
 * in mult and shअगरt.
 *
 * The deal here is to replace a भागide by a reciprocal one
 * in fast path (a reciprocal भागide is a multiply and a shअगरt)
 *
 * Normal क्रमmula would be :
 *  समय_in_ns = (NSEC_PER_SEC * len) / rate_bps
 *
 * We compute mult/shअगरt to use instead :
 *  समय_in_ns = (len * mult) >> shअगरt;
 *
 * We try to get the highest possible mult value क्रम accuracy,
 * but have to make sure no overflows will ever happen.
 *
 * reciprocal_value() is not used here it करोesn't handle 64-bit values.
 */
अटल व्योम psched_ratecfg_precompute__(u64 rate, u32 *mult, u8 *shअगरt)
अणु
	u64 factor = NSEC_PER_SEC;

	*mult = 1;
	*shअगरt = 0;

	अगर (rate <= 0)
		वापस;

	क्रम (;;) अणु
		*mult = भाग64_u64(factor, rate);
		अगर (*mult & (1U << 31) || factor & (1ULL << 63))
			अवरोध;
		factor <<= 1;
		(*shअगरt)++;
	पूर्ण
पूर्ण

व्योम psched_ratecfg_precompute(काष्ठा psched_ratecfg *r,
			       स्थिर काष्ठा tc_ratespec *conf,
			       u64 rate64)
अणु
	स_रखो(r, 0, माप(*r));
	r->overhead = conf->overhead;
	r->rate_bytes_ps = max_t(u64, conf->rate, rate64);
	r->linklayer = (conf->linklayer & TC_LINKLAYER_MASK);
	psched_ratecfg_precompute__(r->rate_bytes_ps, &r->mult, &r->shअगरt);
पूर्ण
EXPORT_SYMBOL(psched_ratecfg_precompute);

व्योम psched_ppscfg_precompute(काष्ठा psched_pktrate *r, u64 pktrate64)
अणु
	r->rate_pkts_ps = pktrate64;
	psched_ratecfg_precompute__(r->rate_pkts_ps, &r->mult, &r->shअगरt);
पूर्ण
EXPORT_SYMBOL(psched_ppscfg_precompute);

अटल व्योम mini_qdisc_rcu_func(काष्ठा rcu_head *head)
अणु
पूर्ण

व्योम mini_qdisc_pair_swap(काष्ठा mini_Qdisc_pair *miniqp,
			  काष्ठा tcf_proto *tp_head)
अणु
	/* Protected with chain0->filter_chain_lock.
	 * Can't access chain directly because tp_head can be शून्य.
	 */
	काष्ठा mini_Qdisc *miniq_old =
		rcu_dereference_रक्षित(*miniqp->p_miniq, 1);
	काष्ठा mini_Qdisc *miniq;

	अगर (!tp_head) अणु
		RCU_INIT_POINTER(*miniqp->p_miniq, शून्य);
		/* Wait क्रम flying RCU callback beक्रमe it is मुक्तd. */
		rcu_barrier();
		वापस;
	पूर्ण

	miniq = !miniq_old || miniq_old == &miniqp->miniq2 ?
		&miniqp->miniq1 : &miniqp->miniq2;

	/* We need to make sure that पढ़ोers won't see the miniq
	 * we are about to modअगरy. So रुको until previous call_rcu callback
	 * is करोne.
	 */
	rcu_barrier();
	miniq->filter_list = tp_head;
	rcu_assign_poपूर्णांकer(*miniqp->p_miniq, miniq);

	अगर (miniq_old)
		/* This is counterpart of the rcu barriers above. We need to
		 * block potential new user of miniq_old until all पढ़ोers
		 * are not seeing it.
		 */
		call_rcu(&miniq_old->rcu, mini_qdisc_rcu_func);
पूर्ण
EXPORT_SYMBOL(mini_qdisc_pair_swap);

व्योम mini_qdisc_pair_block_init(काष्ठा mini_Qdisc_pair *miniqp,
				काष्ठा tcf_block *block)
अणु
	miniqp->miniq1.block = block;
	miniqp->miniq2.block = block;
पूर्ण
EXPORT_SYMBOL(mini_qdisc_pair_block_init);

व्योम mini_qdisc_pair_init(काष्ठा mini_Qdisc_pair *miniqp, काष्ठा Qdisc *qdisc,
			  काष्ठा mini_Qdisc __rcu **p_miniq)
अणु
	miniqp->miniq1.cpu_bstats = qdisc->cpu_bstats;
	miniqp->miniq1.cpu_qstats = qdisc->cpu_qstats;
	miniqp->miniq2.cpu_bstats = qdisc->cpu_bstats;
	miniqp->miniq2.cpu_qstats = qdisc->cpu_qstats;
	miniqp->p_miniq = p_miniq;
पूर्ण
EXPORT_SYMBOL(mini_qdisc_pair_init);
