<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (c) 2019 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * Include file क्रम sample Host Bandwidth Manager (HBM) BPF programs
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/ipv6.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/filter.h>
#समावेश <uapi/linux/pkt_cls.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_ecn.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "hbm.h"

#घोषणा DROP_PKT	0
#घोषणा ALLOW_PKT	1
#घोषणा TCP_ECN_OK	1
#घोषणा CWR		2

#अगर_अघोषित HBM_DEBUG  // Define HBM_DEBUG to enable debugging
#अघोषित bpf_prपूर्णांकk
#घोषणा bpf_prपूर्णांकk(fmt, ...)
#पूर्ण_अगर

#घोषणा INITIAL_CREDIT_PACKETS	100
#घोषणा MAX_BYTES_PER_PACKET	1500
#घोषणा MARK_THRESH		(40 * MAX_BYTES_PER_PACKET)
#घोषणा DROP_THRESH		(80 * 5 * MAX_BYTES_PER_PACKET)
#घोषणा LARGE_PKT_DROP_THRESH	(DROP_THRESH - (15 * MAX_BYTES_PER_PACKET))
#घोषणा MARK_REGION_SIZE	(LARGE_PKT_DROP_THRESH - MARK_THRESH)
#घोषणा LARGE_PKT_THRESH	120
#घोषणा MAX_CREDIT		(100 * MAX_BYTES_PER_PACKET)
#घोषणा INIT_CREDIT		(INITIAL_CREDIT_PACKETS * MAX_BYTES_PER_PACKET)

// Time base accounting क्रम fq's EDT
#घोषणा BURST_SIZE_NS		100000 // 100us
#घोषणा MARK_THRESH_NS		50000 // 50us
#घोषणा DROP_THRESH_NS		500000 // 500us
// Reserve 20us of queuing क्रम small packets (less than 120 bytes)
#घोषणा LARGE_PKT_DROP_THRESH_NS (DROP_THRESH_NS - 20000)
#घोषणा MARK_REGION_SIZE_NS	(LARGE_PKT_DROP_THRESH_NS - MARK_THRESH_NS)

// rate in bytes per ns << 20
#घोषणा CREDIT_PER_NS(delta, rate) ((((u64)(delta)) * (rate)) >> 20)
#घोषणा BYTES_PER_NS(delta, rate) ((((u64)(delta)) * (rate)) >> 20)
#घोषणा BYTES_TO_NS(bytes, rate) भाग64_u64(((u64)(bytes)) << 20, (u64)(rate))

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, काष्ठा hbm_vqueue);
पूर्ण queue_state SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, u32);
	__type(value, काष्ठा hbm_queue_stats);
पूर्ण queue_stats SEC(".maps");

काष्ठा hbm_pkt_info अणु
	पूर्णांक	cwnd;
	पूर्णांक	rtt;
	पूर्णांक	packets_out;
	bool	is_ip;
	bool	is_tcp;
	लघु	ecn;
पूर्ण;

अटल पूर्णांक get_tcp_info(काष्ठा __sk_buff *skb, काष्ठा hbm_pkt_info *pkti)
अणु
	काष्ठा bpf_sock *sk;
	काष्ठा bpf_tcp_sock *tp;

	sk = skb->sk;
	अगर (sk) अणु
		sk = bpf_sk_fullsock(sk);
		अगर (sk) अणु
			अगर (sk->protocol == IPPROTO_TCP) अणु
				tp = bpf_tcp_sock(sk);
				अगर (tp) अणु
					pkti->cwnd = tp->snd_cwnd;
					pkti->rtt = tp->srtt_us >> 3;
					pkti->packets_out = tp->packets_out;
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	pkti->cwnd = 0;
	pkti->rtt = 0;
	pkti->packets_out = 0;
	वापस 1;
पूर्ण

अटल व्योम hbm_get_pkt_info(काष्ठा __sk_buff *skb,
			     काष्ठा hbm_pkt_info *pkti)
अणु
	काष्ठा iphdr iph;
	काष्ठा ipv6hdr *ip6h;

	pkti->cwnd = 0;
	pkti->rtt = 0;
	bpf_skb_load_bytes(skb, 0, &iph, 12);
	अगर (iph.version == 6) अणु
		ip6h = (काष्ठा ipv6hdr *)&iph;
		pkti->is_ip = true;
		pkti->is_tcp = (ip6h->nexthdr == 6);
		pkti->ecn = (ip6h->flow_lbl[0] >> 4) & INET_ECN_MASK;
	पूर्ण अन्यथा अगर (iph.version == 4) अणु
		pkti->is_ip = true;
		pkti->is_tcp = (iph.protocol == 6);
		pkti->ecn = iph.tos & INET_ECN_MASK;
	पूर्ण अन्यथा अणु
		pkti->is_ip = false;
		pkti->is_tcp = false;
		pkti->ecn = 0;
	पूर्ण
	अगर (pkti->is_tcp)
		get_tcp_info(skb, pkti);
पूर्ण

अटल __always_अंतरभूत व्योम hbm_init_vqueue(काष्ठा hbm_vqueue *qdp, पूर्णांक rate)
अणु
	bpf_prपूर्णांकk("Initializing queue_state, rate:%d\n", rate * 128);
	qdp->lastसमय = bpf_kसमय_get_ns();
	qdp->credit = INIT_CREDIT;
	qdp->rate = rate * 128;
पूर्ण

अटल __always_अंतरभूत व्योम hbm_init_edt_vqueue(काष्ठा hbm_vqueue *qdp,
						पूर्णांक rate)
अणु
	अचिन्हित दीर्घ दीर्घ curसमय;

	curसमय = bpf_kसमय_get_ns();
	bpf_prपूर्णांकk("Initializing queue_state, rate:%d\n", rate * 128);
	qdp->lastसमय = curसमय - BURST_SIZE_NS;	// support initial burst
	qdp->credit = 0;				// not used
	qdp->rate = rate * 128;
पूर्ण

अटल __always_अंतरभूत व्योम hbm_update_stats(काष्ठा hbm_queue_stats *qsp,
					     पूर्णांक len,
					     अचिन्हित दीर्घ दीर्घ curसमय,
					     bool congestion_flag,
					     bool drop_flag,
					     bool cwr_flag,
					     bool ecn_ce_flag,
					     काष्ठा hbm_pkt_info *pkti,
					     पूर्णांक credit)
अणु
	पूर्णांक rv = ALLOW_PKT;

	अगर (qsp != शून्य) अणु
		// Following is needed क्रम work conserving
		__sync_add_and_fetch(&(qsp->bytes_total), len);
		अगर (qsp->stats) अणु
			// Optionally update statistics
			अगर (qsp->firstPacketTime == 0)
				qsp->firstPacketTime = curसमय;
			qsp->lastPacketTime = curसमय;
			__sync_add_and_fetch(&(qsp->pkts_total), 1);
			अगर (congestion_flag) अणु
				__sync_add_and_fetch(&(qsp->pkts_marked), 1);
				__sync_add_and_fetch(&(qsp->bytes_marked), len);
			पूर्ण
			अगर (drop_flag) अणु
				__sync_add_and_fetch(&(qsp->pkts_dropped), 1);
				__sync_add_and_fetch(&(qsp->bytes_dropped),
						     len);
			पूर्ण
			अगर (ecn_ce_flag)
				__sync_add_and_fetch(&(qsp->pkts_ecn_ce), 1);
			अगर (pkti->cwnd) अणु
				__sync_add_and_fetch(&(qsp->sum_cwnd),
						     pkti->cwnd);
				__sync_add_and_fetch(&(qsp->sum_cwnd_cnt), 1);
			पूर्ण
			अगर (pkti->rtt)
				__sync_add_and_fetch(&(qsp->sum_rtt),
						     pkti->rtt);
			__sync_add_and_fetch(&(qsp->sum_credit), credit);

			अगर (drop_flag)
				rv = DROP_PKT;
			अगर (cwr_flag)
				rv |= 2;
			अगर (rv == DROP_PKT)
				__sync_add_and_fetch(&(qsp->वापसValCount[0]),
						     1);
			अन्यथा अगर (rv == ALLOW_PKT)
				__sync_add_and_fetch(&(qsp->वापसValCount[1]),
						     1);
			अन्यथा अगर (rv == 2)
				__sync_add_and_fetch(&(qsp->वापसValCount[2]),
						     1);
			अन्यथा अगर (rv == 3)
				__sync_add_and_fetch(&(qsp->वापसValCount[3]),
						     1);
		पूर्ण
	पूर्ण
पूर्ण
