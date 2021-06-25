<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Sample Host Bandwidth Manager (HBM) BPF program.
 *
 * A cgroup skb BPF egress program to limit cgroup output bandwidth.
 * It uses a modअगरied भव token bucket queue to limit average
 * egress bandwidth. The implementation uses credits instead of tokens.
 * Negative credits imply that queueing would have happened (this is
 * a भव queue, so no queueing is करोne by it. However, queueing may
 * occur at the actual qdisc (which is not used क्रम rate limiting).
 *
 * This implementation uses 3 thresholds, one to start marking packets and
 * the other two to drop packets:
 *                                  CREDIT
 *        - <--------------------------|------------------------> +
 *              |    |          |      0
 *              |  Large pkt    |
 *              |  drop thresh  |
 *   Small pkt drop             Mark threshold
 *       thresh
 *
 * The effect of marking depends on the type of packet:
 * a) If the packet is ECN enabled and it is a TCP packet, then the packet
 *    is ECN marked.
 * b) If the packet is a TCP packet, then we probabilistically call tcp_cwr
 *    to reduce the congestion winकरोw. The current implementation uses a linear
 *    distribution (0% probability at marking threshold, 100% probability
 *    at drop threshold).
 * c) If the packet is not a TCP packet, then it is dropped.
 *
 * If the credit is below the drop threshold, the packet is dropped. If it
 * is a TCP packet, then it also calls tcp_cwr since packets dropped by
 * by a cgroup skb BPF program करो not स्वतःmatically trigger a call to
 * tcp_cwr in the current kernel code.
 *
 * This BPF program actually uses 2 drop thresholds, one threshold
 * क्रम larger packets (>= 120 bytes) and another क्रम smaller packets. This
 * protects smaller packets such as SYNs, ACKs, etc.
 *
 * The शेष bandwidth limit is set at 1Gbps but this can be changed by
 * a user program through a shared BPF map. In addition, by शेष this BPF
 * program करोes not limit connections using loopback. This behavior can be
 * overwritten by the user program. There is also an option to calculate
 * some statistics, such as percent of packets marked or dropped, which
 * the user program can access.
 *
 * A latter patch provides such a program (hbm.c)
 */

#समावेश "hbm_kern.h"

SEC("cgroup_skb/egress")
पूर्णांक _hbm_out_cg(काष्ठा __sk_buff *skb)
अणु
	काष्ठा hbm_pkt_info pkti;
	पूर्णांक len = skb->len;
	अचिन्हित पूर्णांक queue_index = 0;
	अचिन्हित दीर्घ दीर्घ curसमय;
	पूर्णांक credit;
	चिन्हित दीर्घ दीर्घ delta = 0, new_credit;
	पूर्णांक max_credit = MAX_CREDIT;
	bool congestion_flag = false;
	bool drop_flag = false;
	bool cwr_flag = false;
	bool ecn_ce_flag = false;
	काष्ठा hbm_vqueue *qdp;
	काष्ठा hbm_queue_stats *qsp = शून्य;
	पूर्णांक rv = ALLOW_PKT;

	qsp = bpf_map_lookup_elem(&queue_stats, &queue_index);
	अगर (qsp != शून्य && !qsp->loopback && (skb->अगरindex == 1))
		वापस ALLOW_PKT;

	hbm_get_pkt_info(skb, &pkti);

	// We may want to account क्रम the length of headers in len
	// calculation, like ETH header + overhead, specially अगर it
	// is a gso packet. But I am not करोing it right now.

	qdp = bpf_get_local_storage(&queue_state, 0);
	अगर (!qdp)
		वापस ALLOW_PKT;
	अन्यथा अगर (qdp->lastसमय == 0)
		hbm_init_vqueue(qdp, 1024);

	curसमय = bpf_kसमय_get_ns();

	// Begin critical section
	bpf_spin_lock(&qdp->lock);
	credit = qdp->credit;
	delta = curसमय - qdp->lastसमय;
	/* delta < 0 implies that another process with a curसमय greater
	 * than ours beat us to the critical section and alपढ़ोy added
	 * the new credit, so we should not add it ourselves
	 */
	अगर (delta > 0) अणु
		qdp->lastसमय = curसमय;
		new_credit = credit + CREDIT_PER_NS(delta, qdp->rate);
		अगर (new_credit > MAX_CREDIT)
			credit = MAX_CREDIT;
		अन्यथा
			credit = new_credit;
	पूर्ण
	credit -= len;
	qdp->credit = credit;
	bpf_spin_unlock(&qdp->lock);
	// End critical section

	// Check अगर we should update rate
	अगर (qsp != शून्य && (qsp->rate * 128) != qdp->rate) अणु
		qdp->rate = qsp->rate * 128;
		bpf_prपूर्णांकk("Updating rate: %d (1sec:%llu bits)\n",
			   (पूर्णांक)qdp->rate,
			   CREDIT_PER_NS(1000000000, qdp->rate) * 8);
	पूर्ण

	// Set flags (drop, congestion, cwr)
	// Dropping => we are congested, so ignore congestion flag
	अगर (credit < -DROP_THRESH ||
	    (len > LARGE_PKT_THRESH && credit < -LARGE_PKT_DROP_THRESH)) अणु
		// Very congested, set drop packet
		drop_flag = true;
		अगर (pkti.ecn)
			congestion_flag = true;
		अन्यथा अगर (pkti.is_tcp)
			cwr_flag = true;
	पूर्ण अन्यथा अगर (credit < 0) अणु
		// Congested, set congestion flag
		अगर (pkti.ecn || pkti.is_tcp) अणु
			अगर (credit < -MARK_THRESH)
				congestion_flag = true;
			अन्यथा
				congestion_flag = false;
		पूर्ण अन्यथा अणु
			congestion_flag = true;
		पूर्ण
	पूर्ण

	अगर (congestion_flag) अणु
		अगर (bpf_skb_ecn_set_ce(skb)) अणु
			ecn_ce_flag = true;
		पूर्ण अन्यथा अणु
			अगर (pkti.is_tcp) अणु
				अचिन्हित पूर्णांक अक्रम = bpf_get_pअक्रमom_u32();

				अगर (-credit >= MARK_THRESH +
				    (अक्रम % MARK_REGION_SIZE)) अणु
					// Do congestion control
					cwr_flag = true;
				पूर्ण
			पूर्ण अन्यथा अगर (len > LARGE_PKT_THRESH) अणु
				// Problem अगर too many small packets?
				drop_flag = true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (qsp != शून्य)
		अगर (qsp->no_cn)
			cwr_flag = false;

	hbm_update_stats(qsp, len, curसमय, congestion_flag, drop_flag,
			 cwr_flag, ecn_ce_flag, &pkti, credit);

	अगर (drop_flag) अणु
		__sync_add_and_fetch(&(qdp->credit), len);
		rv = DROP_PKT;
	पूर्ण

	अगर (cwr_flag)
		rv |= 2;
	वापस rv;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
