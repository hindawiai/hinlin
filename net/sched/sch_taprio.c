<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* net/sched/sch_taprio.c	 Time Aware Priority Scheduler
 *
 * Authors:	Vinicius Costa Gomes <vinicius.gomes@पूर्णांकel.com>
 *
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sch_generic.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>

अटल LIST_HEAD(taprio_list);
अटल DEFINE_SPINLOCK(taprio_list_lock);

#घोषणा TAPRIO_ALL_GATES_OPEN -1

#घोषणा TXTIME_ASSIST_IS_ENABLED(flags) ((flags) & TCA_TAPRIO_ATTR_FLAG_TXTIME_ASSIST)
#घोषणा FULL_OFFLOAD_IS_ENABLED(flags) ((flags) & TCA_TAPRIO_ATTR_FLAG_FULL_OFFLOAD)
#घोषणा TAPRIO_FLAGS_INVALID U32_MAX

काष्ठा sched_entry अणु
	काष्ठा list_head list;

	/* The instant that this entry "closes" and the next one
	 * should खोलो, the qdisc will make some efक्रमt so that no
	 * packet leaves after this समय.
	 */
	kसमय_प्रकार बंद_समय;
	kसमय_प्रकार next_txसमय;
	atomic_t budget;
	पूर्णांक index;
	u32 gate_mask;
	u32 पूर्णांकerval;
	u8 command;
पूर्ण;

काष्ठा sched_gate_list अणु
	काष्ठा rcu_head rcu;
	काष्ठा list_head entries;
	माप_प्रकार num_entries;
	kसमय_प्रकार cycle_बंद_समय;
	s64 cycle_समय;
	s64 cycle_समय_extension;
	s64 base_समय;
पूर्ण;

काष्ठा taprio_sched अणु
	काष्ठा Qdisc **qdiscs;
	काष्ठा Qdisc *root;
	u32 flags;
	क्रमागत tk_offsets tk_offset;
	पूर्णांक घड़ीid;
	atomic64_t picos_per_byte; /* Using picoseconds because क्रम 10Gbps+
				    * speeds it's sub-nanoseconds per byte
				    */

	/* Protects the update side of the RCU रक्षित current_entry */
	spinlock_t current_entry_lock;
	काष्ठा sched_entry __rcu *current_entry;
	काष्ठा sched_gate_list __rcu *oper_sched;
	काष्ठा sched_gate_list __rcu *admin_sched;
	काष्ठा hrसमयr advance_समयr;
	काष्ठा list_head taprio_list;
	काष्ठा sk_buff *(*dequeue)(काष्ठा Qdisc *sch);
	काष्ठा sk_buff *(*peek)(काष्ठा Qdisc *sch);
	u32 txसमय_delay;
पूर्ण;

काष्ठा __tc_taprio_qopt_offload अणु
	refcount_t users;
	काष्ठा tc_taprio_qopt_offload offload;
पूर्ण;

अटल kसमय_प्रकार sched_base_समय(स्थिर काष्ठा sched_gate_list *sched)
अणु
	अगर (!sched)
		वापस KTIME_MAX;

	वापस ns_to_kसमय(sched->base_समय);
पूर्ण

अटल kसमय_प्रकार taprio_get_समय(काष्ठा taprio_sched *q)
अणु
	kसमय_प्रकार mono = kसमय_get();

	चयन (q->tk_offset) अणु
	हाल TK_OFFS_MAX:
		वापस mono;
	शेष:
		वापस kसमय_mono_to_any(mono, q->tk_offset);
	पूर्ण

	वापस KTIME_MAX;
पूर्ण

अटल व्योम taprio_मुक्त_sched_cb(काष्ठा rcu_head *head)
अणु
	काष्ठा sched_gate_list *sched = container_of(head, काष्ठा sched_gate_list, rcu);
	काष्ठा sched_entry *entry, *n;

	अगर (!sched)
		वापस;

	list_क्रम_each_entry_safe(entry, n, &sched->entries, list) अणु
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण

	kमुक्त(sched);
पूर्ण

अटल व्योम चयन_schedules(काष्ठा taprio_sched *q,
			     काष्ठा sched_gate_list **admin,
			     काष्ठा sched_gate_list **oper)
अणु
	rcu_assign_poपूर्णांकer(q->oper_sched, *admin);
	rcu_assign_poपूर्णांकer(q->admin_sched, शून्य);

	अगर (*oper)
		call_rcu(&(*oper)->rcu, taprio_मुक्त_sched_cb);

	*oper = *admin;
	*admin = शून्य;
पूर्ण

/* Get how much समय has been alपढ़ोy elapsed in the current cycle. */
अटल s32 get_cycle_समय_elapsed(काष्ठा sched_gate_list *sched, kसमय_प्रकार समय)
अणु
	kसमय_प्रकार समय_since_sched_start;
	s32 समय_elapsed;

	समय_since_sched_start = kसमय_sub(समय, sched->base_समय);
	भाग_s64_rem(समय_since_sched_start, sched->cycle_समय, &समय_elapsed);

	वापस समय_elapsed;
पूर्ण

अटल kसमय_प्रकार get_पूर्णांकerval_end_समय(काष्ठा sched_gate_list *sched,
				     काष्ठा sched_gate_list *admin,
				     काष्ठा sched_entry *entry,
				     kसमय_प्रकार पूर्णांकv_start)
अणु
	s32 cycle_elapsed = get_cycle_समय_elapsed(sched, पूर्णांकv_start);
	kसमय_प्रकार पूर्णांकv_end, cycle_ext_end, cycle_end;

	cycle_end = kसमय_add_ns(पूर्णांकv_start, sched->cycle_समय - cycle_elapsed);
	पूर्णांकv_end = kसमय_add_ns(पूर्णांकv_start, entry->पूर्णांकerval);
	cycle_ext_end = kसमय_add(cycle_end, sched->cycle_समय_extension);

	अगर (kसमय_beक्रमe(पूर्णांकv_end, cycle_end))
		वापस पूर्णांकv_end;
	अन्यथा अगर (admin && admin != sched &&
		 kसमय_after(admin->base_समय, cycle_end) &&
		 kसमय_beक्रमe(admin->base_समय, cycle_ext_end))
		वापस admin->base_समय;
	अन्यथा
		वापस cycle_end;
पूर्ण

अटल पूर्णांक length_to_duration(काष्ठा taprio_sched *q, पूर्णांक len)
अणु
	वापस भाग_u64(len * atomic64_पढ़ो(&q->picos_per_byte), 1000);
पूर्ण

/* Returns the entry corresponding to next available पूर्णांकerval. If
 * validate_पूर्णांकerval is set, it only validates whether the बारtamp occurs
 * when the gate corresponding to the skb's traffic class is खोलो.
 */
अटल काष्ठा sched_entry *find_entry_to_transmit(काष्ठा sk_buff *skb,
						  काष्ठा Qdisc *sch,
						  काष्ठा sched_gate_list *sched,
						  काष्ठा sched_gate_list *admin,
						  kसमय_प्रकार समय,
						  kसमय_प्रकार *पूर्णांकerval_start,
						  kसमय_प्रकार *पूर्णांकerval_end,
						  bool validate_पूर्णांकerval)
अणु
	kसमय_प्रकार curr_पूर्णांकv_start, curr_पूर्णांकv_end, cycle_end, packet_transmit_समय;
	kसमय_प्रकार earliest_txसमय = KTIME_MAX, txसमय, cycle, transmit_end_समय;
	काष्ठा sched_entry *entry = शून्य, *entry_found = शून्य;
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	bool entry_available = false;
	s32 cycle_elapsed;
	पूर्णांक tc, n;

	tc = netdev_get_prio_tc_map(dev, skb->priority);
	packet_transmit_समय = length_to_duration(q, qdisc_pkt_len(skb));

	*पूर्णांकerval_start = 0;
	*पूर्णांकerval_end = 0;

	अगर (!sched)
		वापस शून्य;

	cycle = sched->cycle_समय;
	cycle_elapsed = get_cycle_समय_elapsed(sched, समय);
	curr_पूर्णांकv_end = kसमय_sub_ns(समय, cycle_elapsed);
	cycle_end = kसमय_add_ns(curr_पूर्णांकv_end, cycle);

	list_क्रम_each_entry(entry, &sched->entries, list) अणु
		curr_पूर्णांकv_start = curr_पूर्णांकv_end;
		curr_पूर्णांकv_end = get_पूर्णांकerval_end_समय(sched, admin, entry,
						      curr_पूर्णांकv_start);

		अगर (kसमय_after(curr_पूर्णांकv_start, cycle_end))
			अवरोध;

		अगर (!(entry->gate_mask & BIT(tc)) ||
		    packet_transmit_समय > entry->पूर्णांकerval)
			जारी;

		txसमय = entry->next_txसमय;

		अगर (kसमय_beक्रमe(txसमय, समय) || validate_पूर्णांकerval) अणु
			transmit_end_समय = kसमय_add_ns(समय, packet_transmit_समय);
			अगर ((kसमय_beक्रमe(curr_पूर्णांकv_start, समय) &&
			     kसमय_beक्रमe(transmit_end_समय, curr_पूर्णांकv_end)) ||
			    (kसमय_after(curr_पूर्णांकv_start, समय) && !validate_पूर्णांकerval)) अणु
				entry_found = entry;
				*पूर्णांकerval_start = curr_पूर्णांकv_start;
				*पूर्णांकerval_end = curr_पूर्णांकv_end;
				अवरोध;
			पूर्ण अन्यथा अगर (!entry_available && !validate_पूर्णांकerval) अणु
				/* Here, we are just trying to find out the
				 * first available पूर्णांकerval in the next cycle.
				 */
				entry_available = true;
				entry_found = entry;
				*पूर्णांकerval_start = kसमय_add_ns(curr_पूर्णांकv_start, cycle);
				*पूर्णांकerval_end = kसमय_add_ns(curr_पूर्णांकv_end, cycle);
			पूर्ण
		पूर्ण अन्यथा अगर (kसमय_beक्रमe(txसमय, earliest_txसमय) &&
			   !entry_available) अणु
			earliest_txसमय = txसमय;
			entry_found = entry;
			n = भाग_s64(kसमय_sub(txसमय, curr_पूर्णांकv_start), cycle);
			*पूर्णांकerval_start = kसमय_add(curr_पूर्णांकv_start, n * cycle);
			*पूर्णांकerval_end = kसमय_add(curr_पूर्णांकv_end, n * cycle);
		पूर्ण
	पूर्ण

	वापस entry_found;
पूर्ण

अटल bool is_valid_पूर्णांकerval(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा sched_gate_list *sched, *admin;
	kसमय_प्रकार पूर्णांकerval_start, पूर्णांकerval_end;
	काष्ठा sched_entry *entry;

	rcu_पढ़ो_lock();
	sched = rcu_dereference(q->oper_sched);
	admin = rcu_dereference(q->admin_sched);

	entry = find_entry_to_transmit(skb, sch, sched, admin, skb->tstamp,
				       &पूर्णांकerval_start, &पूर्णांकerval_end, true);
	rcu_पढ़ो_unlock();

	वापस entry;
पूर्ण

अटल bool taprio_flags_valid(u32 flags)
अणु
	/* Make sure no other flag bits are set. */
	अगर (flags & ~(TCA_TAPRIO_ATTR_FLAG_TXTIME_ASSIST |
		      TCA_TAPRIO_ATTR_FLAG_FULL_OFFLOAD))
		वापस false;
	/* txसमय-assist and full offload are mutually exclusive */
	अगर ((flags & TCA_TAPRIO_ATTR_FLAG_TXTIME_ASSIST) &&
	    (flags & TCA_TAPRIO_ATTR_FLAG_FULL_OFFLOAD))
		वापस false;
	वापस true;
पूर्ण

/* This वापसs the tstamp value set by TCP in terms of the set घड़ी. */
अटल kसमय_प्रकार get_tcp_tstamp(काष्ठा taprio_sched *q, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक offset = skb_network_offset(skb);
	स्थिर काष्ठा ipv6hdr *ipv6h;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा ipv6hdr _ipv6h;

	ipv6h = skb_header_poपूर्णांकer(skb, offset, माप(_ipv6h), &_ipv6h);
	अगर (!ipv6h)
		वापस 0;

	अगर (ipv6h->version == 4) अणु
		iph = (काष्ठा iphdr *)ipv6h;
		offset += iph->ihl * 4;

		/* special-हाल 6in4 tunnelling, as that is a common way to get
		 * v6 connectivity in the home
		 */
		अगर (iph->protocol == IPPROTO_IPV6) अणु
			ipv6h = skb_header_poपूर्णांकer(skb, offset,
						   माप(_ipv6h), &_ipv6h);

			अगर (!ipv6h || ipv6h->nexthdr != IPPROTO_TCP)
				वापस 0;
		पूर्ण अन्यथा अगर (iph->protocol != IPPROTO_TCP) अणु
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (ipv6h->version == 6 && ipv6h->nexthdr != IPPROTO_TCP) अणु
		वापस 0;
	पूर्ण

	वापस kसमय_mono_to_any(skb->skb_mstamp_ns, q->tk_offset);
पूर्ण

/* There are a few scenarios where we will have to modअगरy the txसमय from
 * what is पढ़ो from next_txसमय in sched_entry. They are:
 * 1. If txसमय is in the past,
 *    a. The gate क्रम the traffic class is currently खोलो and packet can be
 *       transmitted beक्रमe it बंदs, schedule the packet right away.
 *    b. If the gate corresponding to the traffic class is going to खोलो later
 *       in the cycle, set the txसमय of packet to the पूर्णांकerval start.
 * 2. If txसमय is in the future, there are packets corresponding to the
 *    current traffic class रुकोing to be transmitted. So, the following
 *    possibilities exist:
 *    a. We can transmit the packet beक्रमe the winकरोw containing the txसमय
 *       बंदs.
 *    b. The winकरोw might बंद beक्रमe the transmission can be completed
 *       successfully. So, schedule the packet in the next खोलो winकरोw.
 */
अटल दीर्घ get_packet_txसमय(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch)
अणु
	kसमय_प्रकार transmit_end_समय, पूर्णांकerval_end, पूर्णांकerval_start, tcp_tstamp;
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा sched_gate_list *sched, *admin;
	kसमय_प्रकार minimum_समय, now, txसमय;
	पूर्णांक len, packet_transmit_समय;
	काष्ठा sched_entry *entry;
	bool sched_changed;

	now = taprio_get_समय(q);
	minimum_समय = kसमय_add_ns(now, q->txसमय_delay);

	tcp_tstamp = get_tcp_tstamp(q, skb);
	minimum_समय = max_t(kसमय_प्रकार, minimum_समय, tcp_tstamp);

	rcu_पढ़ो_lock();
	admin = rcu_dereference(q->admin_sched);
	sched = rcu_dereference(q->oper_sched);
	अगर (admin && kसमय_after(minimum_समय, admin->base_समय))
		चयन_schedules(q, &admin, &sched);

	/* Until the schedule starts, all the queues are खोलो */
	अगर (!sched || kसमय_beक्रमe(minimum_समय, sched->base_समय)) अणु
		txसमय = minimum_समय;
		जाओ करोne;
	पूर्ण

	len = qdisc_pkt_len(skb);
	packet_transmit_समय = length_to_duration(q, len);

	करो अणु
		sched_changed = false;

		entry = find_entry_to_transmit(skb, sch, sched, admin,
					       minimum_समय,
					       &पूर्णांकerval_start, &पूर्णांकerval_end,
					       false);
		अगर (!entry) अणु
			txसमय = 0;
			जाओ करोne;
		पूर्ण

		txसमय = entry->next_txसमय;
		txसमय = max_t(kसमय_प्रकार, txसमय, minimum_समय);
		txसमय = max_t(kसमय_प्रकार, txसमय, पूर्णांकerval_start);

		अगर (admin && admin != sched &&
		    kसमय_after(txसमय, admin->base_समय)) अणु
			sched = admin;
			sched_changed = true;
			जारी;
		पूर्ण

		transmit_end_समय = kसमय_add(txसमय, packet_transmit_समय);
		minimum_समय = transmit_end_समय;

		/* Update the txसमय of current entry to the next समय it's
		 * पूर्णांकerval starts.
		 */
		अगर (kसमय_after(transmit_end_समय, पूर्णांकerval_end))
			entry->next_txसमय = kसमय_add(पूर्णांकerval_start, sched->cycle_समय);
	पूर्ण जबतक (sched_changed || kसमय_after(transmit_end_समय, पूर्णांकerval_end));

	entry->next_txसमय = transmit_end_समय;

करोne:
	rcu_पढ़ो_unlock();
	वापस txसमय;
पूर्ण

अटल पूर्णांक taprio_enqueue_one(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			      काष्ठा Qdisc *child, काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);

	अगर (skb->sk && sock_flag(skb->sk, SOCK_TXTIME)) अणु
		अगर (!is_valid_पूर्णांकerval(skb, sch))
			वापस qdisc_drop(skb, sch, to_मुक्त);
	पूर्ण अन्यथा अगर (TXTIME_ASSIST_IS_ENABLED(q->flags)) अणु
		skb->tstamp = get_packet_txसमय(skb, sch);
		अगर (!skb->tstamp)
			वापस qdisc_drop(skb, sch, to_मुक्त);
	पूर्ण

	qdisc_qstats_backlog_inc(sch, skb);
	sch->q.qlen++;

	वापस qdisc_enqueue(skb, child, to_मुक्त);
पूर्ण

अटल पूर्णांक taprio_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			  काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा Qdisc *child;
	पूर्णांक queue;

	queue = skb_get_queue_mapping(skb);

	child = q->qdiscs[queue];
	अगर (unlikely(!child))
		वापस qdisc_drop(skb, sch, to_मुक्त);

	/* Large packets might not be transmitted when the transmission duration
	 * exceeds any configured पूर्णांकerval. Thereक्रमe, segment the skb पूर्णांकo
	 * smaller chunks. Skip it क्रम the full offload हाल, as the driver
	 * and/or the hardware is expected to handle this.
	 */
	अगर (skb_is_gso(skb) && !FULL_OFFLOAD_IS_ENABLED(q->flags)) अणु
		अचिन्हित पूर्णांक slen = 0, numsegs = 0, len = qdisc_pkt_len(skb);
		netdev_features_t features = netअगर_skb_features(skb);
		काष्ठा sk_buff *segs, *nskb;
		पूर्णांक ret;

		segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);
		अगर (IS_ERR_OR_शून्य(segs))
			वापस qdisc_drop(skb, sch, to_मुक्त);

		skb_list_walk_safe(segs, segs, nskb) अणु
			skb_mark_not_on_list(segs);
			qdisc_skb_cb(segs)->pkt_len = segs->len;
			slen += segs->len;

			ret = taprio_enqueue_one(segs, sch, child, to_मुक्त);
			अगर (ret != NET_XMIT_SUCCESS) अणु
				अगर (net_xmit_drop_count(ret))
					qdisc_qstats_drop(sch);
			पूर्ण अन्यथा अणु
				numsegs++;
			पूर्ण
		पूर्ण

		अगर (numsegs > 1)
			qdisc_tree_reduce_backlog(sch, 1 - numsegs, len - slen);
		consume_skb(skb);

		वापस numsegs > 0 ? NET_XMIT_SUCCESS : NET_XMIT_DROP;
	पूर्ण

	वापस taprio_enqueue_one(skb, sch, child, to_मुक्त);
पूर्ण

अटल काष्ठा sk_buff *taprio_peek_soft(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा sched_entry *entry;
	काष्ठा sk_buff *skb;
	u32 gate_mask;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	entry = rcu_dereference(q->current_entry);
	gate_mask = entry ? entry->gate_mask : TAPRIO_ALL_GATES_OPEN;
	rcu_पढ़ो_unlock();

	अगर (!gate_mask)
		वापस शून्य;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा Qdisc *child = q->qdiscs[i];
		पूर्णांक prio;
		u8 tc;

		अगर (unlikely(!child))
			जारी;

		skb = child->ops->peek(child);
		अगर (!skb)
			जारी;

		अगर (TXTIME_ASSIST_IS_ENABLED(q->flags))
			वापस skb;

		prio = skb->priority;
		tc = netdev_get_prio_tc_map(dev, prio);

		अगर (!(gate_mask & BIT(tc)))
			जारी;

		वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *taprio_peek_offload(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा Qdisc *child = q->qdiscs[i];

		अगर (unlikely(!child))
			जारी;

		skb = child->ops->peek(child);
		अगर (!skb)
			जारी;

		वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *taprio_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);

	वापस q->peek(sch);
पूर्ण

अटल व्योम taprio_set_budget(काष्ठा taprio_sched *q, काष्ठा sched_entry *entry)
अणु
	atomic_set(&entry->budget,
		   भाग64_u64((u64)entry->पूर्णांकerval * 1000,
			     atomic64_पढ़ो(&q->picos_per_byte)));
पूर्ण

अटल काष्ठा sk_buff *taprio_dequeue_soft(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sched_entry *entry;
	u32 gate_mask;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	entry = rcu_dereference(q->current_entry);
	/* अगर there's no entry, it means that the schedule didn't
	 * start yet, so क्रमce all gates to be खोलो, this is in
	 * accordance to IEEE 802.1Qbv-2015 Section 8.6.9.4.5
	 * "AdminGateSates"
	 */
	gate_mask = entry ? entry->gate_mask : TAPRIO_ALL_GATES_OPEN;

	अगर (!gate_mask)
		जाओ करोne;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा Qdisc *child = q->qdiscs[i];
		kसमय_प्रकार guard;
		पूर्णांक prio;
		पूर्णांक len;
		u8 tc;

		अगर (unlikely(!child))
			जारी;

		अगर (TXTIME_ASSIST_IS_ENABLED(q->flags)) अणु
			skb = child->ops->dequeue(child);
			अगर (!skb)
				जारी;
			जाओ skb_found;
		पूर्ण

		skb = child->ops->peek(child);
		अगर (!skb)
			जारी;

		prio = skb->priority;
		tc = netdev_get_prio_tc_map(dev, prio);

		अगर (!(gate_mask & BIT(tc))) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		len = qdisc_pkt_len(skb);
		guard = kसमय_add_ns(taprio_get_समय(q),
				     length_to_duration(q, len));

		/* In the हाल that there's no gate entry, there's no
		 * guard band ...
		 */
		अगर (gate_mask != TAPRIO_ALL_GATES_OPEN &&
		    kसमय_after(guard, entry->बंद_समय)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* ... and no budget. */
		अगर (gate_mask != TAPRIO_ALL_GATES_OPEN &&
		    atomic_sub_वापस(len, &entry->budget) < 0) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		skb = child->ops->dequeue(child);
		अगर (unlikely(!skb))
			जाओ करोne;

skb_found:
		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;

		जाओ करोne;
	पूर्ण

करोne:
	rcu_पढ़ो_unlock();

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *taprio_dequeue_offload(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा Qdisc *child = q->qdiscs[i];

		अगर (unlikely(!child))
			जारी;

		skb = child->ops->dequeue(child);
		अगर (unlikely(!skb))
			जारी;

		qdisc_bstats_update(sch, skb);
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;

		वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *taprio_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);

	वापस q->dequeue(sch);
पूर्ण

अटल bool should_restart_cycle(स्थिर काष्ठा sched_gate_list *oper,
				 स्थिर काष्ठा sched_entry *entry)
अणु
	अगर (list_is_last(&entry->list, &oper->entries))
		वापस true;

	अगर (kसमय_compare(entry->बंद_समय, oper->cycle_बंद_समय) == 0)
		वापस true;

	वापस false;
पूर्ण

अटल bool should_change_schedules(स्थिर काष्ठा sched_gate_list *admin,
				    स्थिर काष्ठा sched_gate_list *oper,
				    kसमय_प्रकार बंद_समय)
अणु
	kसमय_प्रकार next_base_समय, extension_समय;

	अगर (!admin)
		वापस false;

	next_base_समय = sched_base_समय(admin);

	/* This is the simple हाल, the बंद_समय would fall after
	 * the next schedule base_समय.
	 */
	अगर (kसमय_compare(next_base_समय, बंद_समय) <= 0)
		वापस true;

	/* This is the cycle_समय_extension हाल, अगर the बंद_समय
	 * plus the amount that can be extended would fall after the
	 * next schedule base_समय, we can extend the current schedule
	 * क्रम that amount.
	 */
	extension_समय = kसमय_add_ns(बंद_समय, oper->cycle_समय_extension);

	/* FIXME: the IEEE 802.1Q-2018 Specअगरication isn't clear about
	 * how precisely the extension should be made. So after
	 * conक्रमmance testing, this logic may change.
	 */
	अगर (kसमय_compare(next_base_समय, extension_समय) <= 0)
		वापस true;

	वापस false;
पूर्ण

अटल क्रमागत hrसमयr_restart advance_sched(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा taprio_sched *q = container_of(समयr, काष्ठा taprio_sched,
					      advance_समयr);
	काष्ठा sched_gate_list *oper, *admin;
	काष्ठा sched_entry *entry, *next;
	काष्ठा Qdisc *sch = q->root;
	kसमय_प्रकार बंद_समय;

	spin_lock(&q->current_entry_lock);
	entry = rcu_dereference_रक्षित(q->current_entry,
					  lockdep_is_held(&q->current_entry_lock));
	oper = rcu_dereference_रक्षित(q->oper_sched,
					 lockdep_is_held(&q->current_entry_lock));
	admin = rcu_dereference_रक्षित(q->admin_sched,
					  lockdep_is_held(&q->current_entry_lock));

	अगर (!oper)
		चयन_schedules(q, &admin, &oper);

	/* This can happen in two हालs: 1. this is the very first run
	 * of this function (i.e. we weren't running any schedule
	 * previously); 2. The previous schedule just ended. The first
	 * entry of all schedules are pre-calculated during the
	 * schedule initialization.
	 */
	अगर (unlikely(!entry || entry->बंद_समय == oper->base_समय)) अणु
		next = list_first_entry(&oper->entries, काष्ठा sched_entry,
					list);
		बंद_समय = next->बंद_समय;
		जाओ first_run;
	पूर्ण

	अगर (should_restart_cycle(oper, entry)) अणु
		next = list_first_entry(&oper->entries, काष्ठा sched_entry,
					list);
		oper->cycle_बंद_समय = kसमय_add_ns(oper->cycle_बंद_समय,
						      oper->cycle_समय);
	पूर्ण अन्यथा अणु
		next = list_next_entry(entry, list);
	पूर्ण

	बंद_समय = kसमय_add_ns(entry->बंद_समय, next->पूर्णांकerval);
	बंद_समय = min_t(kसमय_प्रकार, बंद_समय, oper->cycle_बंद_समय);

	अगर (should_change_schedules(admin, oper, बंद_समय)) अणु
		/* Set things so the next समय this runs, the new
		 * schedule runs.
		 */
		बंद_समय = sched_base_समय(admin);
		चयन_schedules(q, &admin, &oper);
	पूर्ण

	next->बंद_समय = बंद_समय;
	taprio_set_budget(q, next);

first_run:
	rcu_assign_poपूर्णांकer(q->current_entry, next);
	spin_unlock(&q->current_entry_lock);

	hrसमयr_set_expires(&q->advance_समयr, बंद_समय);

	rcu_पढ़ो_lock();
	__netअगर_schedule(sch);
	rcu_पढ़ो_unlock();

	वापस HRTIMER_RESTART;
पूर्ण

अटल स्थिर काष्ठा nla_policy entry_policy[TCA_TAPRIO_SCHED_ENTRY_MAX + 1] = अणु
	[TCA_TAPRIO_SCHED_ENTRY_INDEX]	   = अणु .type = NLA_U32 पूर्ण,
	[TCA_TAPRIO_SCHED_ENTRY_CMD]	   = अणु .type = NLA_U8 पूर्ण,
	[TCA_TAPRIO_SCHED_ENTRY_GATE_MASK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_TAPRIO_SCHED_ENTRY_INTERVAL]  = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy taprio_policy[TCA_TAPRIO_ATTR_MAX + 1] = अणु
	[TCA_TAPRIO_ATTR_PRIOMAP]	       = अणु
		.len = माप(काष्ठा tc_mqprio_qopt)
	पूर्ण,
	[TCA_TAPRIO_ATTR_SCHED_ENTRY_LIST]           = अणु .type = NLA_NESTED पूर्ण,
	[TCA_TAPRIO_ATTR_SCHED_BASE_TIME]            = अणु .type = NLA_S64 पूर्ण,
	[TCA_TAPRIO_ATTR_SCHED_SINGLE_ENTRY]         = अणु .type = NLA_NESTED पूर्ण,
	[TCA_TAPRIO_ATTR_SCHED_CLOCKID]              = अणु .type = NLA_S32 पूर्ण,
	[TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME]           = अणु .type = NLA_S64 पूर्ण,
	[TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME_EXTENSION] = अणु .type = NLA_S64 पूर्ण,
	[TCA_TAPRIO_ATTR_FLAGS]                      = अणु .type = NLA_U32 पूर्ण,
	[TCA_TAPRIO_ATTR_TXTIME_DELAY]		     = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक fill_sched_entry(काष्ठा taprio_sched *q, काष्ठा nlattr **tb,
			    काष्ठा sched_entry *entry,
			    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक min_duration = length_to_duration(q, ETH_ZLEN);
	u32 पूर्णांकerval = 0;

	अगर (tb[TCA_TAPRIO_SCHED_ENTRY_CMD])
		entry->command = nla_get_u8(
			tb[TCA_TAPRIO_SCHED_ENTRY_CMD]);

	अगर (tb[TCA_TAPRIO_SCHED_ENTRY_GATE_MASK])
		entry->gate_mask = nla_get_u32(
			tb[TCA_TAPRIO_SCHED_ENTRY_GATE_MASK]);

	अगर (tb[TCA_TAPRIO_SCHED_ENTRY_INTERVAL])
		पूर्णांकerval = nla_get_u32(
			tb[TCA_TAPRIO_SCHED_ENTRY_INTERVAL]);

	/* The पूर्णांकerval should allow at least the minimum ethernet
	 * frame to go out.
	 */
	अगर (पूर्णांकerval < min_duration) अणु
		NL_SET_ERR_MSG(extack, "Invalid interval for schedule entry");
		वापस -EINVAL;
	पूर्ण

	entry->पूर्णांकerval = पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_sched_entry(काष्ठा taprio_sched *q, काष्ठा nlattr *n,
			     काष्ठा sched_entry *entry, पूर्णांक index,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_TAPRIO_SCHED_ENTRY_MAX + 1] = अणु पूर्ण;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, TCA_TAPRIO_SCHED_ENTRY_MAX, n,
					  entry_policy, शून्य);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Could not parse nested entry");
		वापस -EINVAL;
	पूर्ण

	entry->index = index;

	वापस fill_sched_entry(q, tb, entry, extack);
पूर्ण

अटल पूर्णांक parse_sched_list(काष्ठा taprio_sched *q, काष्ठा nlattr *list,
			    काष्ठा sched_gate_list *sched,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *n;
	पूर्णांक err, rem;
	पूर्णांक i = 0;

	अगर (!list)
		वापस -EINVAL;

	nla_क्रम_each_nested(n, list, rem) अणु
		काष्ठा sched_entry *entry;

		अगर (nla_type(n) != TCA_TAPRIO_SCHED_ENTRY) अणु
			NL_SET_ERR_MSG(extack, "Attribute is not of type 'entry'");
			जारी;
		पूर्ण

		entry = kzalloc(माप(*entry), GFP_KERNEL);
		अगर (!entry) अणु
			NL_SET_ERR_MSG(extack, "Not enough memory for entry");
			वापस -ENOMEM;
		पूर्ण

		err = parse_sched_entry(q, n, entry, i, extack);
		अगर (err < 0) अणु
			kमुक्त(entry);
			वापस err;
		पूर्ण

		list_add_tail(&entry->list, &sched->entries);
		i++;
	पूर्ण

	sched->num_entries = i;

	वापस i;
पूर्ण

अटल पूर्णांक parse_taprio_schedule(काष्ठा taprio_sched *q, काष्ठा nlattr **tb,
				 काष्ठा sched_gate_list *new,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = 0;

	अगर (tb[TCA_TAPRIO_ATTR_SCHED_SINGLE_ENTRY]) अणु
		NL_SET_ERR_MSG(extack, "Adding a single entry is not supported");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (tb[TCA_TAPRIO_ATTR_SCHED_BASE_TIME])
		new->base_समय = nla_get_s64(tb[TCA_TAPRIO_ATTR_SCHED_BASE_TIME]);

	अगर (tb[TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME_EXTENSION])
		new->cycle_समय_extension = nla_get_s64(tb[TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME_EXTENSION]);

	अगर (tb[TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME])
		new->cycle_समय = nla_get_s64(tb[TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME]);

	अगर (tb[TCA_TAPRIO_ATTR_SCHED_ENTRY_LIST])
		err = parse_sched_list(q, tb[TCA_TAPRIO_ATTR_SCHED_ENTRY_LIST],
				       new, extack);
	अगर (err < 0)
		वापस err;

	अगर (!new->cycle_समय) अणु
		काष्ठा sched_entry *entry;
		kसमय_प्रकार cycle = 0;

		list_क्रम_each_entry(entry, &new->entries, list)
			cycle = kसमय_add_ns(cycle, entry->पूर्णांकerval);

		अगर (!cycle) अणु
			NL_SET_ERR_MSG(extack, "'cycle_time' can never be 0");
			वापस -EINVAL;
		पूर्ण

		new->cycle_समय = cycle;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक taprio_parse_mqprio_opt(काष्ठा net_device *dev,
				   काष्ठा tc_mqprio_qopt *qopt,
				   काष्ठा netlink_ext_ack *extack,
				   u32 taprio_flags)
अणु
	पूर्णांक i, j;

	अगर (!qopt && !dev->num_tc) अणु
		NL_SET_ERR_MSG(extack, "'mqprio' configuration is necessary");
		वापस -EINVAL;
	पूर्ण

	/* If num_tc is alपढ़ोy set, it means that the user alपढ़ोy
	 * configured the mqprio part
	 */
	अगर (dev->num_tc)
		वापस 0;

	/* Verअगरy num_tc is not out of max range */
	अगर (qopt->num_tc > TC_MAX_QUEUE) अणु
		NL_SET_ERR_MSG(extack, "Number of traffic classes is outside valid range");
		वापस -EINVAL;
	पूर्ण

	/* taprio imposes that traffic classes map 1:n to tx queues */
	अगर (qopt->num_tc > dev->num_tx_queues) अणु
		NL_SET_ERR_MSG(extack, "Number of traffic classes is greater than number of HW queues");
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy priority mapping uses valid tcs */
	क्रम (i = 0; i <= TC_BITMASK; i++) अणु
		अगर (qopt->prio_tc_map[i] >= qopt->num_tc) अणु
			NL_SET_ERR_MSG(extack, "Invalid traffic class in priority to traffic class mapping");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < qopt->num_tc; i++) अणु
		अचिन्हित पूर्णांक last = qopt->offset[i] + qopt->count[i];

		/* Verअगरy the queue count is in tx range being equal to the
		 * real_num_tx_queues indicates the last queue is in use.
		 */
		अगर (qopt->offset[i] >= dev->num_tx_queues ||
		    !qopt->count[i] ||
		    last > dev->real_num_tx_queues) अणु
			NL_SET_ERR_MSG(extack, "Invalid queue in traffic class to queue mapping");
			वापस -EINVAL;
		पूर्ण

		अगर (TXTIME_ASSIST_IS_ENABLED(taprio_flags))
			जारी;

		/* Verअगरy that the offset and counts करो not overlap */
		क्रम (j = i + 1; j < qopt->num_tc; j++) अणु
			अगर (last > qopt->offset[j]) अणु
				NL_SET_ERR_MSG(extack, "Detected overlap in the traffic class to queue mapping");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक taprio_get_start_समय(काष्ठा Qdisc *sch,
				 काष्ठा sched_gate_list *sched,
				 kसमय_प्रकार *start)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	kसमय_प्रकार now, base, cycle;
	s64 n;

	base = sched_base_समय(sched);
	now = taprio_get_समय(q);

	अगर (kसमय_after(base, now)) अणु
		*start = base;
		वापस 0;
	पूर्ण

	cycle = sched->cycle_समय;

	/* The qdisc is expected to have at least one sched_entry.  Moreover,
	 * any entry must have 'interval' > 0. Thus अगर the cycle समय is zero,
	 * something went really wrong. In that हाल, we should warn about this
	 * inconsistent state and वापस error.
	 */
	अगर (WARN_ON(!cycle))
		वापस -EFAULT;

	/* Schedule the start समय क्रम the beginning of the next
	 * cycle.
	 */
	n = भाग64_s64(kसमय_sub_ns(now, base), cycle);
	*start = kसमय_add_ns(base, (n + 1) * cycle);
	वापस 0;
पूर्ण

अटल व्योम setup_first_बंद_समय(काष्ठा taprio_sched *q,
				   काष्ठा sched_gate_list *sched, kसमय_प्रकार base)
अणु
	काष्ठा sched_entry *first;
	kसमय_प्रकार cycle;

	first = list_first_entry(&sched->entries,
				 काष्ठा sched_entry, list);

	cycle = sched->cycle_समय;

	/* FIXME: find a better place to करो this */
	sched->cycle_बंद_समय = kसमय_add_ns(base, cycle);

	first->बंद_समय = kसमय_add_ns(base, first->पूर्णांकerval);
	taprio_set_budget(q, first);
	rcu_assign_poपूर्णांकer(q->current_entry, शून्य);
पूर्ण

अटल व्योम taprio_start_sched(काष्ठा Qdisc *sch,
			       kसमय_प्रकार start, काष्ठा sched_gate_list *new)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	kसमय_प्रकार expires;

	अगर (FULL_OFFLOAD_IS_ENABLED(q->flags))
		वापस;

	expires = hrसमयr_get_expires(&q->advance_समयr);
	अगर (expires == 0)
		expires = KTIME_MAX;

	/* If the new schedule starts beक्रमe the next expiration, we
	 * reprogram it to the earliest one, so we change the admin
	 * schedule to the operational one at the right समय.
	 */
	start = min_t(kसमय_प्रकार, start, expires);

	hrसमयr_start(&q->advance_समयr, start, HRTIMER_MODE_ABS);
पूर्ण

अटल व्योम taprio_set_picos_per_byte(काष्ठा net_device *dev,
				      काष्ठा taprio_sched *q)
अणु
	काष्ठा ethtool_link_ksettings ecmd;
	पूर्णांक speed = SPEED_10;
	पूर्णांक picos_per_byte;
	पूर्णांक err;

	err = __ethtool_get_link_ksettings(dev, &ecmd);
	अगर (err < 0)
		जाओ skip;

	अगर (ecmd.base.speed && ecmd.base.speed != SPEED_UNKNOWN)
		speed = ecmd.base.speed;

skip:
	picos_per_byte = (USEC_PER_SEC * 8) / speed;

	atomic64_set(&q->picos_per_byte, picos_per_byte);
	netdev_dbg(dev, "taprio: set %s's picos_per_byte to: %lld, linkspeed: %d\n",
		   dev->name, (दीर्घ दीर्घ)atomic64_पढ़ो(&q->picos_per_byte),
		   ecmd.base.speed);
पूर्ण

अटल पूर्णांक taprio_dev_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			       व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net_device *qdev;
	काष्ठा taprio_sched *q;
	bool found = false;

	ASSERT_RTNL();

	अगर (event != NETDEV_UP && event != NETDEV_CHANGE)
		वापस NOTIFY_DONE;

	spin_lock(&taprio_list_lock);
	list_क्रम_each_entry(q, &taprio_list, taprio_list) अणु
		qdev = qdisc_dev(q->root);
		अगर (qdev == dev) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&taprio_list_lock);

	अगर (found)
		taprio_set_picos_per_byte(dev, q);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम setup_txसमय(काष्ठा taprio_sched *q,
			 काष्ठा sched_gate_list *sched, kसमय_प्रकार base)
अणु
	काष्ठा sched_entry *entry;
	u32 पूर्णांकerval = 0;

	list_क्रम_each_entry(entry, &sched->entries, list) अणु
		entry->next_txसमय = kसमय_add_ns(base, पूर्णांकerval);
		पूर्णांकerval += entry->पूर्णांकerval;
	पूर्ण
पूर्ण

अटल काष्ठा tc_taprio_qopt_offload *taprio_offload_alloc(पूर्णांक num_entries)
अणु
	काष्ठा __tc_taprio_qopt_offload *__offload;

	__offload = kzalloc(काष्ठा_size(__offload, offload.entries, num_entries),
			    GFP_KERNEL);
	अगर (!__offload)
		वापस शून्य;

	refcount_set(&__offload->users, 1);

	वापस &__offload->offload;
पूर्ण

काष्ठा tc_taprio_qopt_offload *taprio_offload_get(काष्ठा tc_taprio_qopt_offload
						  *offload)
अणु
	काष्ठा __tc_taprio_qopt_offload *__offload;

	__offload = container_of(offload, काष्ठा __tc_taprio_qopt_offload,
				 offload);

	refcount_inc(&__offload->users);

	वापस offload;
पूर्ण
EXPORT_SYMBOL_GPL(taprio_offload_get);

व्योम taprio_offload_मुक्त(काष्ठा tc_taprio_qopt_offload *offload)
अणु
	काष्ठा __tc_taprio_qopt_offload *__offload;

	__offload = container_of(offload, काष्ठा __tc_taprio_qopt_offload,
				 offload);

	अगर (!refcount_dec_and_test(&__offload->users))
		वापस;

	kमुक्त(__offload);
पूर्ण
EXPORT_SYMBOL_GPL(taprio_offload_मुक्त);

/* The function will only serve to keep the poपूर्णांकers to the "oper" and "admin"
 * schedules valid in relation to their base बार, so when calling dump() the
 * users looks at the right schedules.
 * When using full offload, the admin configuration is promoted to oper at the
 * base_समय in the PHC समय करोमुख्य.  But because the प्रणाली समय is not
 * necessarily in sync with that, we can't just trigger a hrसमयr to call
 * चयन_schedules at the right hardware समय.
 * At the moment we call this by hand right away from taprio, but in the future
 * it will be useful to create a mechanism क्रम drivers to notअगरy taprio of the
 * offload state (PENDING, ACTIVE, INACTIVE) so it can be visible in dump().
 * This is left as TODO.
 */
अटल व्योम taprio_offload_config_changed(काष्ठा taprio_sched *q)
अणु
	काष्ठा sched_gate_list *oper, *admin;

	spin_lock(&q->current_entry_lock);

	oper = rcu_dereference_रक्षित(q->oper_sched,
					 lockdep_is_held(&q->current_entry_lock));
	admin = rcu_dereference_रक्षित(q->admin_sched,
					  lockdep_is_held(&q->current_entry_lock));

	चयन_schedules(q, &admin, &oper);

	spin_unlock(&q->current_entry_lock);
पूर्ण

अटल u32 tc_map_to_queue_mask(काष्ठा net_device *dev, u32 tc_mask)
अणु
	u32 i, queue_mask = 0;

	क्रम (i = 0; i < dev->num_tc; i++) अणु
		u32 offset, count;

		अगर (!(tc_mask & BIT(i)))
			जारी;

		offset = dev->tc_to_txq[i].offset;
		count = dev->tc_to_txq[i].count;

		queue_mask |= GENMASK(offset + count - 1, offset);
	पूर्ण

	वापस queue_mask;
पूर्ण

अटल व्योम taprio_sched_to_offload(काष्ठा net_device *dev,
				    काष्ठा sched_gate_list *sched,
				    काष्ठा tc_taprio_qopt_offload *offload)
अणु
	काष्ठा sched_entry *entry;
	पूर्णांक i = 0;

	offload->base_समय = sched->base_समय;
	offload->cycle_समय = sched->cycle_समय;
	offload->cycle_समय_extension = sched->cycle_समय_extension;

	list_क्रम_each_entry(entry, &sched->entries, list) अणु
		काष्ठा tc_taprio_sched_entry *e = &offload->entries[i];

		e->command = entry->command;
		e->पूर्णांकerval = entry->पूर्णांकerval;
		e->gate_mask = tc_map_to_queue_mask(dev, entry->gate_mask);

		i++;
	पूर्ण

	offload->num_entries = i;
पूर्ण

अटल पूर्णांक taprio_enable_offload(काष्ठा net_device *dev,
				 काष्ठा taprio_sched *q,
				 काष्ठा sched_gate_list *sched,
				 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	काष्ठा tc_taprio_qopt_offload *offload;
	पूर्णांक err = 0;

	अगर (!ops->nकरो_setup_tc) अणु
		NL_SET_ERR_MSG(extack,
			       "Device does not support taprio offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	offload = taprio_offload_alloc(sched->num_entries);
	अगर (!offload) अणु
		NL_SET_ERR_MSG(extack,
			       "Not enough memory for enabling offload mode");
		वापस -ENOMEM;
	पूर्ण
	offload->enable = 1;
	taprio_sched_to_offload(dev, sched, offload);

	err = ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_TAPRIO, offload);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack,
			       "Device failed to setup taprio offload");
		जाओ करोne;
	पूर्ण

करोne:
	taprio_offload_मुक्त(offload);

	वापस err;
पूर्ण

अटल पूर्णांक taprio_disable_offload(काष्ठा net_device *dev,
				  काष्ठा taprio_sched *q,
				  काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	काष्ठा tc_taprio_qopt_offload *offload;
	पूर्णांक err;

	अगर (!FULL_OFFLOAD_IS_ENABLED(q->flags))
		वापस 0;

	अगर (!ops->nकरो_setup_tc)
		वापस -EOPNOTSUPP;

	offload = taprio_offload_alloc(0);
	अगर (!offload) अणु
		NL_SET_ERR_MSG(extack,
			       "Not enough memory to disable offload mode");
		वापस -ENOMEM;
	पूर्ण
	offload->enable = 0;

	err = ops->nकरो_setup_tc(dev, TC_SETUP_QDISC_TAPRIO, offload);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack,
			       "Device failed to disable offload");
		जाओ out;
	पूर्ण

out:
	taprio_offload_मुक्त(offload);

	वापस err;
पूर्ण

/* If full offload is enabled, the only possible घड़ीid is the net device's
 * PHC. For that reason, specअगरying a घड़ीid through netlink is incorrect.
 * For txसमय-assist, it is implicitly assumed that the device's PHC is kept
 * in sync with the specअगरied घड़ीid via a user space daemon such as phc2sys.
 * For both software taprio and txसमय-assist, the घड़ीid is used क्रम the
 * hrसमयr that advances the schedule and hence mandatory.
 */
अटल पूर्णांक taprio_parse_घड़ीid(काष्ठा Qdisc *sch, काष्ठा nlattr **tb,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	पूर्णांक err = -EINVAL;

	अगर (FULL_OFFLOAD_IS_ENABLED(q->flags)) अणु
		स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
		काष्ठा ethtool_ts_info info = अणु
			.cmd = ETHTOOL_GET_TS_INFO,
			.phc_index = -1,
		पूर्ण;

		अगर (tb[TCA_TAPRIO_ATTR_SCHED_CLOCKID]) अणु
			NL_SET_ERR_MSG(extack,
				       "The 'clockid' cannot be specified for full offload");
			जाओ out;
		पूर्ण

		अगर (ops && ops->get_ts_info)
			err = ops->get_ts_info(dev, &info);

		अगर (err || info.phc_index < 0) अणु
			NL_SET_ERR_MSG(extack,
				       "Device does not have a PTP clock");
			err = -ENOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (tb[TCA_TAPRIO_ATTR_SCHED_CLOCKID]) अणु
		पूर्णांक घड़ीid = nla_get_s32(tb[TCA_TAPRIO_ATTR_SCHED_CLOCKID]);

		/* We only support अटल घड़ीids and we करोn't allow
		 * क्रम it to be modअगरied after the first init.
		 */
		अगर (घड़ीid < 0 ||
		    (q->घड़ीid != -1 && q->घड़ीid != घड़ीid)) अणु
			NL_SET_ERR_MSG(extack,
				       "Changing the 'clockid' of a running schedule is not supported");
			err = -ENOTSUPP;
			जाओ out;
		पूर्ण

		चयन (घड़ीid) अणु
		हाल CLOCK_REALTIME:
			q->tk_offset = TK_OFFS_REAL;
			अवरोध;
		हाल CLOCK_MONOTONIC:
			q->tk_offset = TK_OFFS_MAX;
			अवरोध;
		हाल CLOCK_BOOTTIME:
			q->tk_offset = TK_OFFS_BOOT;
			अवरोध;
		हाल CLOCK_TAI:
			q->tk_offset = TK_OFFS_TAI;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Invalid 'clockid'");
			err = -EINVAL;
			जाओ out;
		पूर्ण

		q->घड़ीid = घड़ीid;
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(extack, "Specifying a 'clockid' is mandatory");
		जाओ out;
	पूर्ण

	/* Everything went ok, वापस success. */
	err = 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक taprio_mqprio_cmp(स्थिर काष्ठा net_device *dev,
			     स्थिर काष्ठा tc_mqprio_qopt *mqprio)
अणु
	पूर्णांक i;

	अगर (!mqprio || mqprio->num_tc != dev->num_tc)
		वापस -1;

	क्रम (i = 0; i < mqprio->num_tc; i++)
		अगर (dev->tc_to_txq[i].count != mqprio->count[i] ||
		    dev->tc_to_txq[i].offset != mqprio->offset[i])
			वापस -1;

	क्रम (i = 0; i <= TC_BITMASK; i++)
		अगर (dev->prio_tc_map[i] != mqprio->prio_tc_map[i])
			वापस -1;

	वापस 0;
पूर्ण

/* The semantics of the 'flags' argument in relation to 'change()'
 * requests, are पूर्णांकerpreted following two rules (which are applied in
 * this order): (1) an omitted 'flags' argument is पूर्णांकerpreted as
 * zero; (2) the 'flags' of a "running" taprio instance cannot be
 * changed.
 */
अटल पूर्णांक taprio_new_flags(स्थिर काष्ठा nlattr *attr, u32 old,
			    काष्ठा netlink_ext_ack *extack)
अणु
	u32 new = 0;

	अगर (attr)
		new = nla_get_u32(attr);

	अगर (old != TAPRIO_FLAGS_INVALID && old != new) अणु
		NL_SET_ERR_MSG_MOD(extack, "Changing 'flags' of a running schedule is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!taprio_flags_valid(new)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Specified 'flags' are not valid");
		वापस -EINVAL;
	पूर्ण

	वापस new;
पूर्ण

अटल पूर्णांक taprio_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_TAPRIO_ATTR_MAX + 1] = अणु पूर्ण;
	काष्ठा sched_gate_list *oper, *admin, *new_admin;
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा tc_mqprio_qopt *mqprio = शून्य;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार start;
	पूर्णांक i, err;

	err = nla_parse_nested_deprecated(tb, TCA_TAPRIO_ATTR_MAX, opt,
					  taprio_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_TAPRIO_ATTR_PRIOMAP])
		mqprio = nla_data(tb[TCA_TAPRIO_ATTR_PRIOMAP]);

	err = taprio_new_flags(tb[TCA_TAPRIO_ATTR_FLAGS],
			       q->flags, extack);
	अगर (err < 0)
		वापस err;

	q->flags = err;

	err = taprio_parse_mqprio_opt(dev, mqprio, extack, q->flags);
	अगर (err < 0)
		वापस err;

	new_admin = kzalloc(माप(*new_admin), GFP_KERNEL);
	अगर (!new_admin) अणु
		NL_SET_ERR_MSG(extack, "Not enough memory for a new schedule");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&new_admin->entries);

	rcu_पढ़ो_lock();
	oper = rcu_dereference(q->oper_sched);
	admin = rcu_dereference(q->admin_sched);
	rcu_पढ़ो_unlock();

	/* no changes - no new mqprio settings */
	अगर (!taprio_mqprio_cmp(dev, mqprio))
		mqprio = शून्य;

	अगर (mqprio && (oper || admin)) अणु
		NL_SET_ERR_MSG(extack, "Changing the traffic mapping of a running schedule is not supported");
		err = -ENOTSUPP;
		जाओ मुक्त_sched;
	पूर्ण

	err = parse_taprio_schedule(q, tb, new_admin, extack);
	अगर (err < 0)
		जाओ मुक्त_sched;

	अगर (new_admin->num_entries == 0) अणु
		NL_SET_ERR_MSG(extack, "There should be at least one entry in the schedule");
		err = -EINVAL;
		जाओ मुक्त_sched;
	पूर्ण

	err = taprio_parse_घड़ीid(sch, tb, extack);
	अगर (err < 0)
		जाओ मुक्त_sched;

	taprio_set_picos_per_byte(dev, q);

	अगर (mqprio) अणु
		netdev_set_num_tc(dev, mqprio->num_tc);
		क्रम (i = 0; i < mqprio->num_tc; i++)
			netdev_set_tc_queue(dev, i,
					    mqprio->count[i],
					    mqprio->offset[i]);

		/* Always use supplied priority mappings */
		क्रम (i = 0; i <= TC_BITMASK; i++)
			netdev_set_prio_tc_map(dev, i,
					       mqprio->prio_tc_map[i]);
	पूर्ण

	अगर (FULL_OFFLOAD_IS_ENABLED(q->flags))
		err = taprio_enable_offload(dev, q, new_admin, extack);
	अन्यथा
		err = taprio_disable_offload(dev, q, extack);
	अगर (err)
		जाओ मुक्त_sched;

	/* Protects against enqueue()/dequeue() */
	spin_lock_bh(qdisc_lock(sch));

	अगर (tb[TCA_TAPRIO_ATTR_TXTIME_DELAY]) अणु
		अगर (!TXTIME_ASSIST_IS_ENABLED(q->flags)) अणु
			NL_SET_ERR_MSG_MOD(extack, "txtime-delay can only be set when txtime-assist mode is enabled");
			err = -EINVAL;
			जाओ unlock;
		पूर्ण

		q->txसमय_delay = nla_get_u32(tb[TCA_TAPRIO_ATTR_TXTIME_DELAY]);
	पूर्ण

	अगर (!TXTIME_ASSIST_IS_ENABLED(q->flags) &&
	    !FULL_OFFLOAD_IS_ENABLED(q->flags) &&
	    !hrसमयr_active(&q->advance_समयr)) अणु
		hrसमयr_init(&q->advance_समयr, q->घड़ीid, HRTIMER_MODE_ABS);
		q->advance_समयr.function = advance_sched;
	पूर्ण

	अगर (FULL_OFFLOAD_IS_ENABLED(q->flags)) अणु
		q->dequeue = taprio_dequeue_offload;
		q->peek = taprio_peek_offload;
	पूर्ण अन्यथा अणु
		/* Be sure to always keep the function poपूर्णांकers
		 * in a consistent state.
		 */
		q->dequeue = taprio_dequeue_soft;
		q->peek = taprio_peek_soft;
	पूर्ण

	err = taprio_get_start_समय(sch, new_admin, &start);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Internal error: failed get start time");
		जाओ unlock;
	पूर्ण

	setup_txसमय(q, new_admin, start);

	अगर (TXTIME_ASSIST_IS_ENABLED(q->flags)) अणु
		अगर (!oper) अणु
			rcu_assign_poपूर्णांकer(q->oper_sched, new_admin);
			err = 0;
			new_admin = शून्य;
			जाओ unlock;
		पूर्ण

		rcu_assign_poपूर्णांकer(q->admin_sched, new_admin);
		अगर (admin)
			call_rcu(&admin->rcu, taprio_मुक्त_sched_cb);
	पूर्ण अन्यथा अणु
		setup_first_बंद_समय(q, new_admin, start);

		/* Protects against advance_sched() */
		spin_lock_irqsave(&q->current_entry_lock, flags);

		taprio_start_sched(sch, start, new_admin);

		rcu_assign_poपूर्णांकer(q->admin_sched, new_admin);
		अगर (admin)
			call_rcu(&admin->rcu, taprio_मुक्त_sched_cb);

		spin_unlock_irqrestore(&q->current_entry_lock, flags);

		अगर (FULL_OFFLOAD_IS_ENABLED(q->flags))
			taprio_offload_config_changed(q);
	पूर्ण

	new_admin = शून्य;
	err = 0;

unlock:
	spin_unlock_bh(qdisc_lock(sch));

मुक्त_sched:
	अगर (new_admin)
		call_rcu(&new_admin->rcu, taprio_मुक्त_sched_cb);

	वापस err;
पूर्ण

अटल व्योम taprio_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	पूर्णांक i;

	hrसमयr_cancel(&q->advance_समयr);
	अगर (q->qdiscs) अणु
		क्रम (i = 0; i < dev->num_tx_queues; i++)
			अगर (q->qdiscs[i])
				qdisc_reset(q->qdiscs[i]);
	पूर्ण
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल व्योम taprio_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित पूर्णांक i;

	spin_lock(&taprio_list_lock);
	list_del(&q->taprio_list);
	spin_unlock(&taprio_list_lock);


	taprio_disable_offload(dev, q, शून्य);

	अगर (q->qdiscs) अणु
		क्रम (i = 0; i < dev->num_tx_queues; i++)
			qdisc_put(q->qdiscs[i]);

		kमुक्त(q->qdiscs);
	पूर्ण
	q->qdiscs = शून्य;

	netdev_reset_tc(dev);

	अगर (q->oper_sched)
		call_rcu(&q->oper_sched->rcu, taprio_मुक्त_sched_cb);

	अगर (q->admin_sched)
		call_rcu(&q->admin_sched->rcu, taprio_मुक्त_sched_cb);
पूर्ण

अटल पूर्णांक taprio_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	पूर्णांक i;

	spin_lock_init(&q->current_entry_lock);

	hrसमयr_init(&q->advance_समयr, CLOCK_TAI, HRTIMER_MODE_ABS);
	q->advance_समयr.function = advance_sched;

	q->dequeue = taprio_dequeue_soft;
	q->peek = taprio_peek_soft;

	q->root = sch;

	/* We only support अटल घड़ीids. Use an invalid value as शेष
	 * and get the valid one on taprio_change().
	 */
	q->घड़ीid = -1;
	q->flags = TAPRIO_FLAGS_INVALID;

	spin_lock(&taprio_list_lock);
	list_add(&q->taprio_list, &taprio_list);
	spin_unlock(&taprio_list_lock);

	अगर (sch->parent != TC_H_ROOT)
		वापस -EOPNOTSUPP;

	अगर (!netअगर_is_multiqueue(dev))
		वापस -EOPNOTSUPP;

	/* pre-allocate qdisc, attachment can't fail */
	q->qdiscs = kसुस्मृति(dev->num_tx_queues,
			    माप(q->qdiscs[0]),
			    GFP_KERNEL);

	अगर (!q->qdiscs)
		वापस -ENOMEM;

	अगर (!opt)
		वापस -EINVAL;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *dev_queue;
		काष्ठा Qdisc *qdisc;

		dev_queue = netdev_get_tx_queue(dev, i);
		qdisc = qdisc_create_dflt(dev_queue,
					  &pfअगरo_qdisc_ops,
					  TC_H_MAKE(TC_H_MAJ(sch->handle),
						    TC_H_MIN(i + 1)),
					  extack);
		अगर (!qdisc)
			वापस -ENOMEM;

		अगर (i < dev->real_num_tx_queues)
			qdisc_hash_add(qdisc, false);

		q->qdiscs[i] = qdisc;
	पूर्ण

	वापस taprio_change(sch, opt, extack);
पूर्ण

अटल काष्ठा netdev_queue *taprio_queue_get(काष्ठा Qdisc *sch,
					     अचिन्हित दीर्घ cl)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित दीर्घ ntx = cl - 1;

	अगर (ntx >= dev->num_tx_queues)
		वापस शून्य;

	वापस netdev_get_tx_queue(dev, ntx);
पूर्ण

अटल पूर्णांक taprio_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			काष्ठा Qdisc *new, काष्ठा Qdisc **old,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा netdev_queue *dev_queue = taprio_queue_get(sch, cl);

	अगर (!dev_queue)
		वापस -EINVAL;

	अगर (dev->flags & IFF_UP)
		dev_deactivate(dev);

	*old = q->qdiscs[cl - 1];
	q->qdiscs[cl - 1] = new;

	अगर (new)
		new->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;

	अगर (dev->flags & IFF_UP)
		dev_activate(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dump_entry(काष्ठा sk_buff *msg,
		      स्थिर काष्ठा sched_entry *entry)
अणु
	काष्ठा nlattr *item;

	item = nla_nest_start_noflag(msg, TCA_TAPRIO_SCHED_ENTRY);
	अगर (!item)
		वापस -ENOSPC;

	अगर (nla_put_u32(msg, TCA_TAPRIO_SCHED_ENTRY_INDEX, entry->index))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, TCA_TAPRIO_SCHED_ENTRY_CMD, entry->command))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, TCA_TAPRIO_SCHED_ENTRY_GATE_MASK,
			entry->gate_mask))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, TCA_TAPRIO_SCHED_ENTRY_INTERVAL,
			entry->पूर्णांकerval))
		जाओ nla_put_failure;

	वापस nla_nest_end(msg, item);

nla_put_failure:
	nla_nest_cancel(msg, item);
	वापस -1;
पूर्ण

अटल पूर्णांक dump_schedule(काष्ठा sk_buff *msg,
			 स्थिर काष्ठा sched_gate_list *root)
अणु
	काष्ठा nlattr *entry_list;
	काष्ठा sched_entry *entry;

	अगर (nla_put_s64(msg, TCA_TAPRIO_ATTR_SCHED_BASE_TIME,
			root->base_समय, TCA_TAPRIO_PAD))
		वापस -1;

	अगर (nla_put_s64(msg, TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME,
			root->cycle_समय, TCA_TAPRIO_PAD))
		वापस -1;

	अगर (nla_put_s64(msg, TCA_TAPRIO_ATTR_SCHED_CYCLE_TIME_EXTENSION,
			root->cycle_समय_extension, TCA_TAPRIO_PAD))
		वापस -1;

	entry_list = nla_nest_start_noflag(msg,
					   TCA_TAPRIO_ATTR_SCHED_ENTRY_LIST);
	अगर (!entry_list)
		जाओ error_nest;

	list_क्रम_each_entry(entry, &root->entries, list) अणु
		अगर (dump_entry(msg, entry) < 0)
			जाओ error_nest;
	पूर्ण

	nla_nest_end(msg, entry_list);
	वापस 0;

error_nest:
	nla_nest_cancel(msg, entry_list);
	वापस -1;
पूर्ण

अटल पूर्णांक taprio_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा taprio_sched *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	काष्ठा sched_gate_list *oper, *admin;
	काष्ठा tc_mqprio_qopt opt = अणु 0 पूर्ण;
	काष्ठा nlattr *nest, *sched_nest;
	अचिन्हित पूर्णांक i;

	rcu_पढ़ो_lock();
	oper = rcu_dereference(q->oper_sched);
	admin = rcu_dereference(q->admin_sched);

	opt.num_tc = netdev_get_num_tc(dev);
	स_नकल(opt.prio_tc_map, dev->prio_tc_map, माप(opt.prio_tc_map));

	क्रम (i = 0; i < netdev_get_num_tc(dev); i++) अणु
		opt.count[i] = dev->tc_to_txq[i].count;
		opt.offset[i] = dev->tc_to_txq[i].offset;
	पूर्ण

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ start_error;

	अगर (nla_put(skb, TCA_TAPRIO_ATTR_PRIOMAP, माप(opt), &opt))
		जाओ options_error;

	अगर (!FULL_OFFLOAD_IS_ENABLED(q->flags) &&
	    nla_put_s32(skb, TCA_TAPRIO_ATTR_SCHED_CLOCKID, q->घड़ीid))
		जाओ options_error;

	अगर (q->flags && nla_put_u32(skb, TCA_TAPRIO_ATTR_FLAGS, q->flags))
		जाओ options_error;

	अगर (q->txसमय_delay &&
	    nla_put_u32(skb, TCA_TAPRIO_ATTR_TXTIME_DELAY, q->txसमय_delay))
		जाओ options_error;

	अगर (oper && dump_schedule(skb, oper))
		जाओ options_error;

	अगर (!admin)
		जाओ करोne;

	sched_nest = nla_nest_start_noflag(skb, TCA_TAPRIO_ATTR_ADMIN_SCHED);
	अगर (!sched_nest)
		जाओ options_error;

	अगर (dump_schedule(skb, admin))
		जाओ admin_error;

	nla_nest_end(skb, sched_nest);

करोne:
	rcu_पढ़ो_unlock();

	वापस nla_nest_end(skb, nest);

admin_error:
	nla_nest_cancel(skb, sched_nest);

options_error:
	nla_nest_cancel(skb, nest);

start_error:
	rcu_पढ़ो_unlock();
	वापस -ENOSPC;
पूर्ण

अटल काष्ठा Qdisc *taprio_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
	काष्ठा netdev_queue *dev_queue = taprio_queue_get(sch, cl);

	अगर (!dev_queue)
		वापस शून्य;

	वापस dev_queue->qdisc_sleeping;
पूर्ण

अटल अचिन्हित दीर्घ taprio_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	अचिन्हित पूर्णांक ntx = TC_H_MIN(classid);

	अगर (!taprio_queue_get(sch, ntx))
		वापस 0;
	वापस ntx;
पूर्ण

अटल पूर्णांक taprio_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			     काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा netdev_queue *dev_queue = taprio_queue_get(sch, cl);

	tcm->tcm_parent = TC_H_ROOT;
	tcm->tcm_handle |= TC_H_MIN(cl);
	tcm->tcm_info = dev_queue->qdisc_sleeping->handle;

	वापस 0;
पूर्ण

अटल पूर्णांक taprio_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
				   काष्ठा gnet_dump *d)
	__releases(d->lock)
	__acquires(d->lock)
अणु
	काष्ठा netdev_queue *dev_queue = taprio_queue_get(sch, cl);

	sch = dev_queue->qdisc_sleeping;
	अगर (gnet_stats_copy_basic(&sch->running, d, शून्य, &sch->bstats) < 0 ||
	    qdisc_qstats_copy(d, sch) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम taprio_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *arg)
अणु
	काष्ठा net_device *dev = qdisc_dev(sch);
	अचिन्हित दीर्घ ntx;

	अगर (arg->stop)
		वापस;

	arg->count = arg->skip;
	क्रम (ntx = arg->skip; ntx < dev->num_tx_queues; ntx++) अणु
		अगर (arg->fn(sch, ntx + 1, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
		arg->count++;
	पूर्ण
पूर्ण

अटल काष्ठा netdev_queue *taprio_select_queue(काष्ठा Qdisc *sch,
						काष्ठा tcmsg *tcm)
अणु
	वापस taprio_queue_get(sch, TC_H_MIN(tcm->tcm_parent));
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops taprio_class_ops = अणु
	.graft		= taprio_graft,
	.leaf		= taprio_leaf,
	.find		= taprio_find,
	.walk		= taprio_walk,
	.dump		= taprio_dump_class,
	.dump_stats	= taprio_dump_class_stats,
	.select_queue	= taprio_select_queue,
पूर्ण;

अटल काष्ठा Qdisc_ops taprio_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &taprio_class_ops,
	.id		= "taprio",
	.priv_size	= माप(काष्ठा taprio_sched),
	.init		= taprio_init,
	.change		= taprio_change,
	.destroy	= taprio_destroy,
	.reset		= taprio_reset,
	.peek		= taprio_peek,
	.dequeue	= taprio_dequeue,
	.enqueue	= taprio_enqueue,
	.dump		= taprio_dump,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा notअगरier_block taprio_device_notअगरier = अणु
	.notअगरier_call = taprio_dev_notअगरier,
पूर्ण;

अटल पूर्णांक __init taprio_module_init(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_netdevice_notअगरier(&taprio_device_notअगरier);

	अगर (err)
		वापस err;

	वापस रेजिस्टर_qdisc(&taprio_qdisc_ops);
पूर्ण

अटल व्योम __निकास taprio_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&taprio_qdisc_ops);
	unरेजिस्टर_netdevice_notअगरier(&taprio_device_notअगरier);
पूर्ण

module_init(taprio_module_init);
module_निकास(taprio_module_निकास);
MODULE_LICENSE("GPL");
