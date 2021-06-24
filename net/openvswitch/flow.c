<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2014 Nicira, Inc.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/llc_pdu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/llc.h>
#समावेश <linux/module.h>
#समावेश <linux/in.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/mpls.h>
#समावेश <linux/sctp.h>
#समावेश <linux/smp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/rculist.h>
#समावेश <net/ip.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/ipv6.h>
#समावेश <net/mpls.h>
#समावेश <net/ndisc.h>
#समावेश <net/nsh.h>

#समावेश "conntrack.h"
#समावेश "datapath.h"
#समावेश "flow.h"
#समावेश "flow_netlink.h"
#समावेश "vport.h"

u64 ovs_flow_used_समय(अचिन्हित दीर्घ flow_jअगरfies)
अणु
	काष्ठा बारpec64 cur_ts;
	u64 cur_ms, idle_ms;

	kसमय_get_ts64(&cur_ts);
	idle_ms = jअगरfies_to_msecs(jअगरfies - flow_jअगरfies);
	cur_ms = (u64)(u32)cur_ts.tv_sec * MSEC_PER_SEC +
		 cur_ts.tv_nsec / NSEC_PER_MSEC;

	वापस cur_ms - idle_ms;
पूर्ण

#घोषणा TCP_FLAGS_BE16(tp) (*(__be16 *)&tcp_flag_word(tp) & htons(0x0FFF))

व्योम ovs_flow_stats_update(काष्ठा sw_flow *flow, __be16 tcp_flags,
			   स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा sw_flow_stats *stats;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक len = skb->len + (skb_vlan_tag_present(skb) ? VLAN_HLEN : 0);

	stats = rcu_dereference(flow->stats[cpu]);

	/* Check अगर alपढ़ोy have CPU-specअगरic stats. */
	अगर (likely(stats)) अणु
		spin_lock(&stats->lock);
		/* Mark अगर we ग_लिखो on the pre-allocated stats. */
		अगर (cpu == 0 && unlikely(flow->stats_last_ग_लिखोr != cpu))
			flow->stats_last_ग_लिखोr = cpu;
	पूर्ण अन्यथा अणु
		stats = rcu_dereference(flow->stats[0]); /* Pre-allocated. */
		spin_lock(&stats->lock);

		/* If the current CPU is the only ग_लिखोr on the
		 * pre-allocated stats keep using them.
		 */
		अगर (unlikely(flow->stats_last_ग_लिखोr != cpu)) अणु
			/* A previous locker may have alपढ़ोy allocated the
			 * stats, so we need to check again.  If CPU-specअगरic
			 * stats were alपढ़ोy allocated, we update the pre-
			 * allocated stats as we have alपढ़ोy locked them.
			 */
			अगर (likely(flow->stats_last_ग_लिखोr != -1) &&
			    likely(!rcu_access_poपूर्णांकer(flow->stats[cpu]))) अणु
				/* Try to allocate CPU-specअगरic stats. */
				काष्ठा sw_flow_stats *new_stats;

				new_stats =
					kmem_cache_alloc_node(flow_stats_cache,
							      GFP_NOWAIT |
							      __GFP_THISNODE |
							      __GFP_NOWARN |
							      __GFP_NOMEMALLOC,
							      numa_node_id());
				अगर (likely(new_stats)) अणु
					new_stats->used = jअगरfies;
					new_stats->packet_count = 1;
					new_stats->byte_count = len;
					new_stats->tcp_flags = tcp_flags;
					spin_lock_init(&new_stats->lock);

					rcu_assign_poपूर्णांकer(flow->stats[cpu],
							   new_stats);
					cpumask_set_cpu(cpu, &flow->cpu_used_mask);
					जाओ unlock;
				पूर्ण
			पूर्ण
			flow->stats_last_ग_लिखोr = cpu;
		पूर्ण
	पूर्ण

	stats->used = jअगरfies;
	stats->packet_count++;
	stats->byte_count += len;
	stats->tcp_flags |= tcp_flags;
unlock:
	spin_unlock(&stats->lock);
पूर्ण

/* Must be called with rcu_पढ़ो_lock or ovs_mutex. */
व्योम ovs_flow_stats_get(स्थिर काष्ठा sw_flow *flow,
			काष्ठा ovs_flow_stats *ovs_stats,
			अचिन्हित दीर्घ *used, __be16 *tcp_flags)
अणु
	पूर्णांक cpu;

	*used = 0;
	*tcp_flags = 0;
	स_रखो(ovs_stats, 0, माप(*ovs_stats));

	/* We खोलो code this to make sure cpu 0 is always considered */
	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu = cpumask_next(cpu, &flow->cpu_used_mask)) अणु
		काष्ठा sw_flow_stats *stats = rcu_dereference_ovsl(flow->stats[cpu]);

		अगर (stats) अणु
			/* Local CPU may ग_लिखो on non-local stats, so we must
			 * block bottom-halves here.
			 */
			spin_lock_bh(&stats->lock);
			अगर (!*used || समय_after(stats->used, *used))
				*used = stats->used;
			*tcp_flags |= stats->tcp_flags;
			ovs_stats->n_packets += stats->packet_count;
			ovs_stats->n_bytes += stats->byte_count;
			spin_unlock_bh(&stats->lock);
		पूर्ण
	पूर्ण
पूर्ण

/* Called with ovs_mutex. */
व्योम ovs_flow_stats_clear(काष्ठा sw_flow *flow)
अणु
	पूर्णांक cpu;

	/* We खोलो code this to make sure cpu 0 is always considered */
	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu = cpumask_next(cpu, &flow->cpu_used_mask)) अणु
		काष्ठा sw_flow_stats *stats = ovsl_dereference(flow->stats[cpu]);

		अगर (stats) अणु
			spin_lock_bh(&stats->lock);
			stats->used = 0;
			stats->packet_count = 0;
			stats->byte_count = 0;
			stats->tcp_flags = 0;
			spin_unlock_bh(&stats->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_header(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	अगर (unlikely(skb->len < len))
		वापस -EINVAL;
	अगर (unlikely(!pskb_may_pull(skb, len)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल bool arphdr_ok(काष्ठा sk_buff *skb)
अणु
	वापस pskb_may_pull(skb, skb_network_offset(skb) +
				  माप(काष्ठा arp_eth_header));
पूर्ण

अटल पूर्णांक check_iphdr(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक nh_ofs = skb_network_offset(skb);
	अचिन्हित पूर्णांक ip_len;
	पूर्णांक err;

	err = check_header(skb, nh_ofs + माप(काष्ठा iphdr));
	अगर (unlikely(err))
		वापस err;

	ip_len = ip_hdrlen(skb);
	अगर (unlikely(ip_len < माप(काष्ठा iphdr) ||
		     skb->len < nh_ofs + ip_len))
		वापस -EINVAL;

	skb_set_transport_header(skb, nh_ofs + ip_len);
	वापस 0;
पूर्ण

अटल bool tcphdr_ok(काष्ठा sk_buff *skb)
अणु
	पूर्णांक th_ofs = skb_transport_offset(skb);
	पूर्णांक tcp_len;

	अगर (unlikely(!pskb_may_pull(skb, th_ofs + माप(काष्ठा tcphdr))))
		वापस false;

	tcp_len = tcp_hdrlen(skb);
	अगर (unlikely(tcp_len < माप(काष्ठा tcphdr) ||
		     skb->len < th_ofs + tcp_len))
		वापस false;

	वापस true;
पूर्ण

अटल bool udphdr_ok(काष्ठा sk_buff *skb)
अणु
	वापस pskb_may_pull(skb, skb_transport_offset(skb) +
				  माप(काष्ठा udphdr));
पूर्ण

अटल bool sctphdr_ok(काष्ठा sk_buff *skb)
अणु
	वापस pskb_may_pull(skb, skb_transport_offset(skb) +
				  माप(काष्ठा sctphdr));
पूर्ण

अटल bool icmphdr_ok(काष्ठा sk_buff *skb)
अणु
	वापस pskb_may_pull(skb, skb_transport_offset(skb) +
				  माप(काष्ठा icmphdr));
पूर्ण

अटल पूर्णांक parse_ipv6hdr(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	अचिन्हित लघु frag_off;
	अचिन्हित पूर्णांक payload_ofs = 0;
	अचिन्हित पूर्णांक nh_ofs = skb_network_offset(skb);
	अचिन्हित पूर्णांक nh_len;
	काष्ठा ipv6hdr *nh;
	पूर्णांक err, nexthdr, flags = 0;

	err = check_header(skb, nh_ofs + माप(*nh));
	अगर (unlikely(err))
		वापस err;

	nh = ipv6_hdr(skb);

	key->ip.proto = NEXTHDR_NONE;
	key->ip.tos = ipv6_get_dsfield(nh);
	key->ip.ttl = nh->hop_limit;
	key->ipv6.label = *(__be32 *)nh & htonl(IPV6_FLOWINFO_FLOWLABEL);
	key->ipv6.addr.src = nh->saddr;
	key->ipv6.addr.dst = nh->daddr;

	nexthdr = ipv6_find_hdr(skb, &payload_ofs, -1, &frag_off, &flags);
	अगर (flags & IP6_FH_F_FRAG) अणु
		अगर (frag_off) अणु
			key->ip.frag = OVS_FRAG_TYPE_LATER;
			key->ip.proto = nexthdr;
			वापस 0;
		पूर्ण
		key->ip.frag = OVS_FRAG_TYPE_FIRST;
	पूर्ण अन्यथा अणु
		key->ip.frag = OVS_FRAG_TYPE_NONE;
	पूर्ण

	/* Delayed handling of error in ipv6_find_hdr() as it
	 * always sets flags and frag_off to a valid value which may be
	 * used to set key->ip.frag above.
	 */
	अगर (unlikely(nexthdr < 0))
		वापस -EPROTO;

	nh_len = payload_ofs - nh_ofs;
	skb_set_transport_header(skb, nh_ofs + nh_len);
	key->ip.proto = nexthdr;
	वापस nh_len;
पूर्ण

अटल bool icmp6hdr_ok(काष्ठा sk_buff *skb)
अणु
	वापस pskb_may_pull(skb, skb_transport_offset(skb) +
				  माप(काष्ठा icmp6hdr));
पूर्ण

/**
 * Parse vlan tag from vlan header.
 * @skb: skb containing frame to parse
 * @key_vh: poपूर्णांकer to parsed vlan tag
 * @untag_vlan: should the vlan header be हटाओd from the frame
 *
 * Returns ERROR on memory error.
 * Returns 0 अगर it encounters a non-vlan or incomplete packet.
 * Returns 1 after successfully parsing vlan tag.
 */
अटल पूर्णांक parse_vlan_tag(काष्ठा sk_buff *skb, काष्ठा vlan_head *key_vh,
			  bool untag_vlan)
अणु
	काष्ठा vlan_head *vh = (काष्ठा vlan_head *)skb->data;

	अगर (likely(!eth_type_vlan(vh->tpid)))
		वापस 0;

	अगर (unlikely(skb->len < माप(काष्ठा vlan_head) + माप(__be16)))
		वापस 0;

	अगर (unlikely(!pskb_may_pull(skb, माप(काष्ठा vlan_head) +
				 माप(__be16))))
		वापस -ENOMEM;

	vh = (काष्ठा vlan_head *)skb->data;
	key_vh->tci = vh->tci | htons(VLAN_CFI_MASK);
	key_vh->tpid = vh->tpid;

	अगर (unlikely(untag_vlan)) अणु
		पूर्णांक offset = skb->data - skb_mac_header(skb);
		u16 tci;
		पूर्णांक err;

		__skb_push(skb, offset);
		err = __skb_vlan_pop(skb, &tci);
		__skb_pull(skb, offset);
		अगर (err)
			वापस err;
		__vlan_hwaccel_put_tag(skb, key_vh->tpid, tci);
	पूर्ण अन्यथा अणु
		__skb_pull(skb, माप(काष्ठा vlan_head));
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम clear_vlan(काष्ठा sw_flow_key *key)
अणु
	key->eth.vlan.tci = 0;
	key->eth.vlan.tpid = 0;
	key->eth.cvlan.tci = 0;
	key->eth.cvlan.tpid = 0;
पूर्ण

अटल पूर्णांक parse_vlan(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक res;

	अगर (skb_vlan_tag_present(skb)) अणु
		key->eth.vlan.tci = htons(skb->vlan_tci) | htons(VLAN_CFI_MASK);
		key->eth.vlan.tpid = skb->vlan_proto;
	पूर्ण अन्यथा अणु
		/* Parse outer vlan tag in the non-accelerated हाल. */
		res = parse_vlan_tag(skb, &key->eth.vlan, true);
		अगर (res <= 0)
			वापस res;
	पूर्ण

	/* Parse inner vlan tag. */
	res = parse_vlan_tag(skb, &key->eth.cvlan, false);
	अगर (res <= 0)
		वापस res;

	वापस 0;
पूर्ण

अटल __be16 parse_ethertype(काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_snap_hdr अणु
		u8  dsap;  /* Always 0xAA */
		u8  ssap;  /* Always 0xAA */
		u8  ctrl;
		u8  oui[3];
		__be16 ethertype;
	पूर्ण;
	काष्ठा llc_snap_hdr *llc;
	__be16 proto;

	proto = *(__be16 *) skb->data;
	__skb_pull(skb, माप(__be16));

	अगर (eth_proto_is_802_3(proto))
		वापस proto;

	अगर (skb->len < माप(काष्ठा llc_snap_hdr))
		वापस htons(ETH_P_802_2);

	अगर (unlikely(!pskb_may_pull(skb, माप(काष्ठा llc_snap_hdr))))
		वापस htons(0);

	llc = (काष्ठा llc_snap_hdr *) skb->data;
	अगर (llc->dsap != LLC_SAP_SNAP ||
	    llc->ssap != LLC_SAP_SNAP ||
	    (llc->oui[0] | llc->oui[1] | llc->oui[2]) != 0)
		वापस htons(ETH_P_802_2);

	__skb_pull(skb, माप(काष्ठा llc_snap_hdr));

	अगर (eth_proto_is_802_3(llc->ethertype))
		वापस llc->ethertype;

	वापस htons(ETH_P_802_2);
पूर्ण

अटल पूर्णांक parse_icmpv6(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
			पूर्णांक nh_len)
अणु
	काष्ठा icmp6hdr *icmp = icmp6_hdr(skb);

	/* The ICMPv6 type and code fields use the 16-bit transport port
	 * fields, so we need to store them in 16-bit network byte order.
	 */
	key->tp.src = htons(icmp->icmp6_type);
	key->tp.dst = htons(icmp->icmp6_code);
	स_रखो(&key->ipv6.nd, 0, माप(key->ipv6.nd));

	अगर (icmp->icmp6_code == 0 &&
	    (icmp->icmp6_type == NDISC_NEIGHBOUR_SOLICITATION ||
	     icmp->icmp6_type == NDISC_NEIGHBOUR_ADVERTISEMENT)) अणु
		पूर्णांक icmp_len = skb->len - skb_transport_offset(skb);
		काष्ठा nd_msg *nd;
		पूर्णांक offset;

		/* In order to process neighbor discovery options, we need the
		 * entire packet.
		 */
		अगर (unlikely(icmp_len < माप(*nd)))
			वापस 0;

		अगर (unlikely(skb_linearize(skb)))
			वापस -ENOMEM;

		nd = (काष्ठा nd_msg *)skb_transport_header(skb);
		key->ipv6.nd.target = nd->target;

		icmp_len -= माप(*nd);
		offset = 0;
		जबतक (icmp_len >= 8) अणु
			काष्ठा nd_opt_hdr *nd_opt =
				 (काष्ठा nd_opt_hdr *)(nd->opt + offset);
			पूर्णांक opt_len = nd_opt->nd_opt_len * 8;

			अगर (unlikely(!opt_len || opt_len > icmp_len))
				वापस 0;

			/* Store the link layer address अगर the appropriate
			 * option is provided.  It is considered an error अगर
			 * the same link layer option is specअगरied twice.
			 */
			अगर (nd_opt->nd_opt_type == ND_OPT_SOURCE_LL_ADDR
			    && opt_len == 8) अणु
				अगर (unlikely(!is_zero_ether_addr(key->ipv6.nd.sll)))
					जाओ invalid;
				ether_addr_copy(key->ipv6.nd.sll,
						&nd->opt[offset+माप(*nd_opt)]);
			पूर्ण अन्यथा अगर (nd_opt->nd_opt_type == ND_OPT_TARGET_LL_ADDR
				   && opt_len == 8) अणु
				अगर (unlikely(!is_zero_ether_addr(key->ipv6.nd.tll)))
					जाओ invalid;
				ether_addr_copy(key->ipv6.nd.tll,
						&nd->opt[offset+माप(*nd_opt)]);
			पूर्ण

			icmp_len -= opt_len;
			offset += opt_len;
		पूर्ण
	पूर्ण

	वापस 0;

invalid:
	स_रखो(&key->ipv6.nd.target, 0, माप(key->ipv6.nd.target));
	स_रखो(key->ipv6.nd.sll, 0, माप(key->ipv6.nd.sll));
	स_रखो(key->ipv6.nd.tll, 0, माप(key->ipv6.nd.tll));

	वापस 0;
पूर्ण

अटल पूर्णांक parse_nsh(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	काष्ठा nshhdr *nh;
	अचिन्हित पूर्णांक nh_ofs = skb_network_offset(skb);
	u8 version, length;
	पूर्णांक err;

	err = check_header(skb, nh_ofs + NSH_BASE_HDR_LEN);
	अगर (unlikely(err))
		वापस err;

	nh = nsh_hdr(skb);
	version = nsh_get_ver(nh);
	length = nsh_hdr_len(nh);

	अगर (version != 0)
		वापस -EINVAL;

	err = check_header(skb, nh_ofs + length);
	अगर (unlikely(err))
		वापस err;

	nh = nsh_hdr(skb);
	key->nsh.base.flags = nsh_get_flags(nh);
	key->nsh.base.ttl = nsh_get_ttl(nh);
	key->nsh.base.mdtype = nh->mdtype;
	key->nsh.base.np = nh->np;
	key->nsh.base.path_hdr = nh->path_hdr;
	चयन (key->nsh.base.mdtype) अणु
	हाल NSH_M_TYPE1:
		अगर (length != NSH_M_TYPE1_LEN)
			वापस -EINVAL;
		स_नकल(key->nsh.context, nh->md1.context,
		       माप(nh->md1));
		अवरोध;
	हाल NSH_M_TYPE2:
		स_रखो(key->nsh.context, 0,
		       माप(nh->md1));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * key_extract_l3l4 - extracts L3/L4 header inक्रमmation.
 * @skb: sk_buff that contains the frame, with skb->data poपूर्णांकing to the
 *       L3 header
 * @key: output flow key
 *
 */
अटल पूर्णांक key_extract_l3l4(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक error;

	/* Network layer. */
	अगर (key->eth.type == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *nh;
		__be16 offset;

		error = check_iphdr(skb);
		अगर (unlikely(error)) अणु
			स_रखो(&key->ip, 0, माप(key->ip));
			स_रखो(&key->ipv4, 0, माप(key->ipv4));
			अगर (error == -EINVAL) अणु
				skb->transport_header = skb->network_header;
				error = 0;
			पूर्ण
			वापस error;
		पूर्ण

		nh = ip_hdr(skb);
		key->ipv4.addr.src = nh->saddr;
		key->ipv4.addr.dst = nh->daddr;

		key->ip.proto = nh->protocol;
		key->ip.tos = nh->tos;
		key->ip.ttl = nh->ttl;

		offset = nh->frag_off & htons(IP_OFFSET);
		अगर (offset) अणु
			key->ip.frag = OVS_FRAG_TYPE_LATER;
			स_रखो(&key->tp, 0, माप(key->tp));
			वापस 0;
		पूर्ण
		अगर (nh->frag_off & htons(IP_MF) ||
			skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
			key->ip.frag = OVS_FRAG_TYPE_FIRST;
		अन्यथा
			key->ip.frag = OVS_FRAG_TYPE_NONE;

		/* Transport layer. */
		अगर (key->ip.proto == IPPROTO_TCP) अणु
			अगर (tcphdr_ok(skb)) अणु
				काष्ठा tcphdr *tcp = tcp_hdr(skb);
				key->tp.src = tcp->source;
				key->tp.dst = tcp->dest;
				key->tp.flags = TCP_FLAGS_BE16(tcp);
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण

		पूर्ण अन्यथा अगर (key->ip.proto == IPPROTO_UDP) अणु
			अगर (udphdr_ok(skb)) अणु
				काष्ठा udphdr *udp = udp_hdr(skb);
				key->tp.src = udp->source;
				key->tp.dst = udp->dest;
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण अन्यथा अगर (key->ip.proto == IPPROTO_SCTP) अणु
			अगर (sctphdr_ok(skb)) अणु
				काष्ठा sctphdr *sctp = sctp_hdr(skb);
				key->tp.src = sctp->source;
				key->tp.dst = sctp->dest;
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण अन्यथा अगर (key->ip.proto == IPPROTO_ICMP) अणु
			अगर (icmphdr_ok(skb)) अणु
				काष्ठा icmphdr *icmp = icmp_hdr(skb);
				/* The ICMP type and code fields use the 16-bit
				 * transport port fields, so we need to store
				 * them in 16-bit network byte order. */
				key->tp.src = htons(icmp->type);
				key->tp.dst = htons(icmp->code);
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (key->eth.type == htons(ETH_P_ARP) ||
		   key->eth.type == htons(ETH_P_RARP)) अणु
		काष्ठा arp_eth_header *arp;
		bool arp_available = arphdr_ok(skb);

		arp = (काष्ठा arp_eth_header *)skb_network_header(skb);

		अगर (arp_available &&
		    arp->ar_hrd == htons(ARPHRD_ETHER) &&
		    arp->ar_pro == htons(ETH_P_IP) &&
		    arp->ar_hln == ETH_ALEN &&
		    arp->ar_pln == 4) अणु

			/* We only match on the lower 8 bits of the opcode. */
			अगर (ntohs(arp->ar_op) <= 0xff)
				key->ip.proto = ntohs(arp->ar_op);
			अन्यथा
				key->ip.proto = 0;

			स_नकल(&key->ipv4.addr.src, arp->ar_sip, माप(key->ipv4.addr.src));
			स_नकल(&key->ipv4.addr.dst, arp->ar_tip, माप(key->ipv4.addr.dst));
			ether_addr_copy(key->ipv4.arp.sha, arp->ar_sha);
			ether_addr_copy(key->ipv4.arp.tha, arp->ar_tha);
		पूर्ण अन्यथा अणु
			स_रखो(&key->ip, 0, माप(key->ip));
			स_रखो(&key->ipv4, 0, माप(key->ipv4));
		पूर्ण
	पूर्ण अन्यथा अगर (eth_p_mpls(key->eth.type)) अणु
		u8 label_count = 1;

		स_रखो(&key->mpls, 0, माप(key->mpls));
		skb_set_inner_network_header(skb, skb->mac_len);
		जबतक (1) अणु
			__be32 lse;

			error = check_header(skb, skb->mac_len +
					     label_count * MPLS_HLEN);
			अगर (unlikely(error))
				वापस 0;

			स_नकल(&lse, skb_inner_network_header(skb), MPLS_HLEN);

			अगर (label_count <= MPLS_LABEL_DEPTH)
				स_नकल(&key->mpls.lse[label_count - 1], &lse,
				       MPLS_HLEN);

			skb_set_inner_network_header(skb, skb->mac_len +
						     label_count * MPLS_HLEN);
			अगर (lse & htonl(MPLS_LS_S_MASK))
				अवरोध;

			label_count++;
		पूर्ण
		अगर (label_count > MPLS_LABEL_DEPTH)
			label_count = MPLS_LABEL_DEPTH;

		key->mpls.num_labels_mask = GENMASK(label_count - 1, 0);
	पूर्ण अन्यथा अगर (key->eth.type == htons(ETH_P_IPV6)) अणु
		पूर्णांक nh_len;             /* IPv6 Header + Extensions */

		nh_len = parse_ipv6hdr(skb, key);
		अगर (unlikely(nh_len < 0)) अणु
			चयन (nh_len) अणु
			हाल -EINVAL:
				स_रखो(&key->ip, 0, माप(key->ip));
				स_रखो(&key->ipv6.addr, 0, माप(key->ipv6.addr));
				fallthrough;
			हाल -EPROTO:
				skb->transport_header = skb->network_header;
				error = 0;
				अवरोध;
			शेष:
				error = nh_len;
			पूर्ण
			वापस error;
		पूर्ण

		अगर (key->ip.frag == OVS_FRAG_TYPE_LATER) अणु
			स_रखो(&key->tp, 0, माप(key->tp));
			वापस 0;
		पूर्ण
		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
			key->ip.frag = OVS_FRAG_TYPE_FIRST;

		/* Transport layer. */
		अगर (key->ip.proto == NEXTHDR_TCP) अणु
			अगर (tcphdr_ok(skb)) अणु
				काष्ठा tcphdr *tcp = tcp_hdr(skb);
				key->tp.src = tcp->source;
				key->tp.dst = tcp->dest;
				key->tp.flags = TCP_FLAGS_BE16(tcp);
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण अन्यथा अगर (key->ip.proto == NEXTHDR_UDP) अणु
			अगर (udphdr_ok(skb)) अणु
				काष्ठा udphdr *udp = udp_hdr(skb);
				key->tp.src = udp->source;
				key->tp.dst = udp->dest;
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण अन्यथा अगर (key->ip.proto == NEXTHDR_SCTP) अणु
			अगर (sctphdr_ok(skb)) अणु
				काष्ठा sctphdr *sctp = sctp_hdr(skb);
				key->tp.src = sctp->source;
				key->tp.dst = sctp->dest;
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण अन्यथा अगर (key->ip.proto == NEXTHDR_ICMP) अणु
			अगर (icmp6hdr_ok(skb)) अणु
				error = parse_icmpv6(skb, key, nh_len);
				अगर (error)
					वापस error;
			पूर्ण अन्यथा अणु
				स_रखो(&key->tp, 0, माप(key->tp));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (key->eth.type == htons(ETH_P_NSH)) अणु
		error = parse_nsh(skb, key);
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * key_extract - extracts a flow key from an Ethernet frame.
 * @skb: sk_buff that contains the frame, with skb->data poपूर्णांकing to the
 * Ethernet header
 * @key: output flow key
 *
 * The caller must ensure that skb->len >= ETH_HLEN.
 *
 * Returns 0 अगर successful, otherwise a negative त्रुटि_सं value.
 *
 * Initializes @skb header fields as follows:
 *
 *    - skb->mac_header: the L2 header.
 *
 *    - skb->network_header: just past the L2 header, or just past the
 *      VLAN header, to the first byte of the L2 payload.
 *
 *    - skb->transport_header: If key->eth.type is ETH_P_IP or ETH_P_IPV6
 *      on output, then just past the IP header, अगर one is present and
 *      of a correct length, otherwise the same as skb->network_header.
 *      For other key->eth.type values it is left untouched.
 *
 *    - skb->protocol: the type of the data starting at skb->network_header.
 *      Equals to key->eth.type.
 */
अटल पूर्णांक key_extract(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	काष्ठा ethhdr *eth;

	/* Flags are always used as part of stats */
	key->tp.flags = 0;

	skb_reset_mac_header(skb);

	/* Link layer. */
	clear_vlan(key);
	अगर (ovs_key_mac_proto(key) == MAC_PROTO_NONE) अणु
		अगर (unlikely(eth_type_vlan(skb->protocol)))
			वापस -EINVAL;

		skb_reset_network_header(skb);
		key->eth.type = skb->protocol;
	पूर्ण अन्यथा अणु
		eth = eth_hdr(skb);
		ether_addr_copy(key->eth.src, eth->h_source);
		ether_addr_copy(key->eth.dst, eth->h_dest);

		__skb_pull(skb, 2 * ETH_ALEN);
		/* We are going to push all headers that we pull, so no need to
		 * update skb->csum here.
		 */

		अगर (unlikely(parse_vlan(skb, key)))
			वापस -ENOMEM;

		key->eth.type = parse_ethertype(skb);
		अगर (unlikely(key->eth.type == htons(0)))
			वापस -ENOMEM;

		/* Multiple tagged packets need to retain TPID to satisfy
		 * skb_vlan_pop(), which will later shअगरt the ethertype पूर्णांकo
		 * skb->protocol.
		 */
		अगर (key->eth.cvlan.tci & htons(VLAN_CFI_MASK))
			skb->protocol = key->eth.cvlan.tpid;
		अन्यथा
			skb->protocol = key->eth.type;

		skb_reset_network_header(skb);
		__skb_push(skb, skb->data - skb_mac_header(skb));
	पूर्ण

	skb_reset_mac_len(skb);

	/* Fill out L3/L4 key info, अगर any */
	वापस key_extract_l3l4(skb, key);
पूर्ण

/* In the हाल of conntrack fragment handling it expects L3 headers,
 * add a helper.
 */
पूर्णांक ovs_flow_key_update_l3l4(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	वापस key_extract_l3l4(skb, key);
पूर्ण

पूर्णांक ovs_flow_key_update(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक res;

	res = key_extract(skb, key);
	अगर (!res)
		key->mac_proto &= ~SW_FLOW_KEY_INVALID;

	वापस res;
पूर्ण

अटल पूर्णांक key_extract_mac_proto(काष्ठा sk_buff *skb)
अणु
	चयन (skb->dev->type) अणु
	हाल ARPHRD_ETHER:
		वापस MAC_PROTO_ETHERNET;
	हाल ARPHRD_NONE:
		अगर (skb->protocol == htons(ETH_P_TEB))
			वापस MAC_PROTO_ETHERNET;
		वापस MAC_PROTO_NONE;
	पूर्ण
	WARN_ON_ONCE(1);
	वापस -EINVAL;
पूर्ण

पूर्णांक ovs_flow_key_extract(स्थिर काष्ठा ip_tunnel_info *tun_info,
			 काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	काष्ठा tc_skb_ext *tc_ext;
#पूर्ण_अगर
	bool post_ct = false;
	पूर्णांक res, err;

	/* Extract metadata from packet. */
	अगर (tun_info) अणु
		key->tun_proto = ip_tunnel_info_af(tun_info);
		स_नकल(&key->tun_key, &tun_info->key, माप(key->tun_key));

		अगर (tun_info->options_len) अणु
			BUILD_BUG_ON((1 << (माप(tun_info->options_len) *
						   8)) - 1
					> माप(key->tun_opts));

			ip_tunnel_info_opts_get(TUN_METADATA_OPTS(key, tun_info->options_len),
						tun_info);
			key->tun_opts_len = tun_info->options_len;
		पूर्ण अन्यथा अणु
			key->tun_opts_len = 0;
		पूर्ण
	पूर्ण अन्यथा  अणु
		key->tun_proto = 0;
		key->tun_opts_len = 0;
		स_रखो(&key->tun_key, 0, माप(key->tun_key));
	पूर्ण

	key->phy.priority = skb->priority;
	key->phy.in_port = OVS_CB(skb)->input_vport->port_no;
	key->phy.skb_mark = skb->mark;
	key->ovs_flow_hash = 0;
	res = key_extract_mac_proto(skb);
	अगर (res < 0)
		वापस res;
	key->mac_proto = res;

#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	अगर (अटल_branch_unlikely(&tc_recirc_sharing_support)) अणु
		tc_ext = skb_ext_find(skb, TC_SKB_EXT);
		key->recirc_id = tc_ext ? tc_ext->chain : 0;
		OVS_CB(skb)->mru = tc_ext ? tc_ext->mru : 0;
		post_ct = tc_ext ? tc_ext->post_ct : false;
	पूर्ण अन्यथा अणु
		key->recirc_id = 0;
	पूर्ण
#अन्यथा
	key->recirc_id = 0;
#पूर्ण_अगर

	err = key_extract(skb, key);
	अगर (!err)
		ovs_ct_fill_key(skb, key, post_ct);   /* Must be after key_extract(). */
	वापस err;
पूर्ण

पूर्णांक ovs_flow_key_extract_userspace(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
				   काष्ठा sk_buff *skb,
				   काष्ठा sw_flow_key *key, bool log)
अणु
	स्थिर काष्ठा nlattr *a[OVS_KEY_ATTR_MAX + 1];
	u64 attrs = 0;
	पूर्णांक err;

	err = parse_flow_nlattrs(attr, a, &attrs, log);
	अगर (err)
		वापस -EINVAL;

	/* Extract metadata from netlink attributes. */
	err = ovs_nla_get_flow_metadata(net, a, attrs, key, log);
	अगर (err)
		वापस err;

	/* key_extract assumes that skb->protocol is set-up क्रम
	 * layer 3 packets which is the हाल क्रम other callers,
	 * in particular packets received from the network stack.
	 * Here the correct value can be set from the metadata
	 * extracted above.
	 * For L2 packet key eth type would be zero. skb protocol
	 * would be set to correct value later during key-extact.
	 */

	skb->protocol = key->eth.type;
	err = key_extract(skb, key);
	अगर (err)
		वापस err;

	/* Check that we have conntrack original direction tuple metadata only
	 * क्रम packets क्रम which it makes sense.  Otherwise the key may be
	 * corrupted due to overlapping key fields.
	 */
	अगर (attrs & (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4) &&
	    key->eth.type != htons(ETH_P_IP))
		वापस -EINVAL;
	अगर (attrs & (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6) &&
	    (key->eth.type != htons(ETH_P_IPV6) ||
	     sw_flow_key_is_nd(key)))
		वापस -EINVAL;

	वापस 0;
पूर्ण
