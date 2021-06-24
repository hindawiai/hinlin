<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2017 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/sctp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/in6.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/checksum.h>
#समावेश <net/dsfield.h>
#समावेश <net/mpls.h>
#समावेश <net/sctp/checksum.h>

#समावेश "datapath.h"
#समावेश "flow.h"
#समावेश "conntrack.h"
#समावेश "vport.h"
#समावेश "flow_netlink.h"

काष्ठा deferred_action अणु
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा nlattr *actions;
	पूर्णांक actions_len;

	/* Store pkt_key clone when creating deferred action. */
	काष्ठा sw_flow_key pkt_key;
पूर्ण;

#घोषणा MAX_L2_LEN	(VLAN_ETH_HLEN + 3 * MPLS_HLEN)
काष्ठा ovs_frag_data अणु
	अचिन्हित दीर्घ dst;
	काष्ठा vport *vport;
	काष्ठा ovs_skb_cb cb;
	__be16 inner_protocol;
	u16 network_offset;	/* valid only क्रम MPLS */
	u16 vlan_tci;
	__be16 vlan_proto;
	अचिन्हित पूर्णांक l2_len;
	u8 mac_proto;
	u8 l2_data[MAX_L2_LEN];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा ovs_frag_data, ovs_frag_data_storage);

#घोषणा DEFERRED_ACTION_FIFO_SIZE 10
#घोषणा OVS_RECURSION_LIMIT 5
#घोषणा OVS_DEFERRED_ACTION_THRESHOLD (OVS_RECURSION_LIMIT - 2)
काष्ठा action_fअगरo अणु
	पूर्णांक head;
	पूर्णांक tail;
	/* Deferred action fअगरo queue storage. */
	काष्ठा deferred_action fअगरo[DEFERRED_ACTION_FIFO_SIZE];
पूर्ण;

काष्ठा action_flow_keys अणु
	काष्ठा sw_flow_key key[OVS_DEFERRED_ACTION_THRESHOLD];
पूर्ण;

अटल काष्ठा action_fअगरo __percpu *action_fअगरos;
अटल काष्ठा action_flow_keys __percpu *flow_keys;
अटल DEFINE_PER_CPU(पूर्णांक, exec_actions_level);

/* Make a clone of the 'key', using the pre-allocated percpu 'flow_keys'
 * space. Return शून्य अगर out of key spaces.
 */
अटल काष्ठा sw_flow_key *clone_key(स्थिर काष्ठा sw_flow_key *key_)
अणु
	काष्ठा action_flow_keys *keys = this_cpu_ptr(flow_keys);
	पूर्णांक level = this_cpu_पढ़ो(exec_actions_level);
	काष्ठा sw_flow_key *key = शून्य;

	अगर (level <= OVS_DEFERRED_ACTION_THRESHOLD) अणु
		key = &keys->key[level - 1];
		*key = *key_;
	पूर्ण

	वापस key;
पूर्ण

अटल व्योम action_fअगरo_init(काष्ठा action_fअगरo *fअगरo)
अणु
	fअगरo->head = 0;
	fअगरo->tail = 0;
पूर्ण

अटल bool action_fअगरo_is_empty(स्थिर काष्ठा action_fअगरo *fअगरo)
अणु
	वापस (fअगरo->head == fअगरo->tail);
पूर्ण

अटल काष्ठा deferred_action *action_fअगरo_get(काष्ठा action_fअगरo *fअगरo)
अणु
	अगर (action_fअगरo_is_empty(fअगरo))
		वापस शून्य;

	वापस &fअगरo->fअगरo[fअगरo->tail++];
पूर्ण

अटल काष्ठा deferred_action *action_fअगरo_put(काष्ठा action_fअगरo *fअगरo)
अणु
	अगर (fअगरo->head >= DEFERRED_ACTION_FIFO_SIZE - 1)
		वापस शून्य;

	वापस &fअगरo->fअगरo[fअगरo->head++];
पूर्ण

/* Return true अगर fअगरo is not full */
अटल काष्ठा deferred_action *add_deferred_actions(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा sw_flow_key *key,
				    स्थिर काष्ठा nlattr *actions,
				    स्थिर पूर्णांक actions_len)
अणु
	काष्ठा action_fअगरo *fअगरo;
	काष्ठा deferred_action *da;

	fअगरo = this_cpu_ptr(action_fअगरos);
	da = action_fअगरo_put(fअगरo);
	अगर (da) अणु
		da->skb = skb;
		da->actions = actions;
		da->actions_len = actions_len;
		da->pkt_key = *key;
	पूर्ण

	वापस da;
पूर्ण

अटल व्योम invalidate_flow_key(काष्ठा sw_flow_key *key)
अणु
	key->mac_proto |= SW_FLOW_KEY_INVALID;
पूर्ण

अटल bool is_flow_key_valid(स्थिर काष्ठा sw_flow_key *key)
अणु
	वापस !(key->mac_proto & SW_FLOW_KEY_INVALID);
पूर्ण

अटल पूर्णांक clone_execute(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			 काष्ठा sw_flow_key *key,
			 u32 recirc_id,
			 स्थिर काष्ठा nlattr *actions, पूर्णांक len,
			 bool last, bool clone_flow_key);

अटल पूर्णांक करो_execute_actions(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			      काष्ठा sw_flow_key *key,
			      स्थिर काष्ठा nlattr *attr, पूर्णांक len);

अटल पूर्णांक push_mpls(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
		     __be32 mpls_lse, __be16 mpls_ethertype, __u16 mac_len)
अणु
	पूर्णांक err;

	err = skb_mpls_push(skb, mpls_lse, mpls_ethertype, mac_len, !!mac_len);
	अगर (err)
		वापस err;

	अगर (!mac_len)
		key->mac_proto = MAC_PROTO_NONE;

	invalidate_flow_key(key);
	वापस 0;
पूर्ण

अटल पूर्णांक pop_mpls(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
		    स्थिर __be16 ethertype)
अणु
	पूर्णांक err;

	err = skb_mpls_pop(skb, ethertype, skb->mac_len,
			   ovs_key_mac_proto(key) == MAC_PROTO_ETHERNET);
	अगर (err)
		वापस err;

	अगर (ethertype == htons(ETH_P_TEB))
		key->mac_proto = MAC_PROTO_ETHERNET;

	invalidate_flow_key(key);
	वापस 0;
पूर्ण

अटल पूर्णांक set_mpls(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		    स्थिर __be32 *mpls_lse, स्थिर __be32 *mask)
अणु
	काष्ठा mpls_shim_hdr *stack;
	__be32 lse;
	पूर्णांक err;

	अगर (!pskb_may_pull(skb, skb_network_offset(skb) + MPLS_HLEN))
		वापस -ENOMEM;

	stack = mpls_hdr(skb);
	lse = OVS_MASKED(stack->label_stack_entry, *mpls_lse, *mask);
	err = skb_mpls_update_lse(skb, lse);
	अगर (err)
		वापस err;

	flow_key->mpls.lse[0] = lse;
	वापस 0;
पूर्ण

अटल पूर्णांक pop_vlan(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक err;

	err = skb_vlan_pop(skb);
	अगर (skb_vlan_tag_present(skb)) अणु
		invalidate_flow_key(key);
	पूर्ण अन्यथा अणु
		key->eth.vlan.tci = 0;
		key->eth.vlan.tpid = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक push_vlan(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
		     स्थिर काष्ठा ovs_action_push_vlan *vlan)
अणु
	अगर (skb_vlan_tag_present(skb)) अणु
		invalidate_flow_key(key);
	पूर्ण अन्यथा अणु
		key->eth.vlan.tci = vlan->vlan_tci;
		key->eth.vlan.tpid = vlan->vlan_tpid;
	पूर्ण
	वापस skb_vlan_push(skb, vlan->vlan_tpid,
			     ntohs(vlan->vlan_tci) & ~VLAN_CFI_MASK);
पूर्ण

/* 'src' is alपढ़ोy properly masked. */
अटल व्योम ether_addr_copy_masked(u8 *dst_, स्थिर u8 *src_, स्थिर u8 *mask_)
अणु
	u16 *dst = (u16 *)dst_;
	स्थिर u16 *src = (स्थिर u16 *)src_;
	स्थिर u16 *mask = (स्थिर u16 *)mask_;

	OVS_SET_MASKED(dst[0], src[0], mask[0]);
	OVS_SET_MASKED(dst[1], src[1], mask[1]);
	OVS_SET_MASKED(dst[2], src[2], mask[2]);
पूर्ण

अटल पूर्णांक set_eth_addr(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
			स्थिर काष्ठा ovs_key_ethernet *key,
			स्थिर काष्ठा ovs_key_ethernet *mask)
अणु
	पूर्णांक err;

	err = skb_ensure_writable(skb, ETH_HLEN);
	अगर (unlikely(err))
		वापस err;

	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_ALEN * 2);

	ether_addr_copy_masked(eth_hdr(skb)->h_source, key->eth_src,
			       mask->eth_src);
	ether_addr_copy_masked(eth_hdr(skb)->h_dest, key->eth_dst,
			       mask->eth_dst);

	skb_postpush_rcsum(skb, eth_hdr(skb), ETH_ALEN * 2);

	ether_addr_copy(flow_key->eth.src, eth_hdr(skb)->h_source);
	ether_addr_copy(flow_key->eth.dst, eth_hdr(skb)->h_dest);
	वापस 0;
पूर्ण

/* pop_eth करोes not support VLAN packets as this action is never called
 * क्रम them.
 */
अटल पूर्णांक pop_eth(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक err;

	err = skb_eth_pop(skb);
	अगर (err)
		वापस err;

	/* safe right beक्रमe invalidate_flow_key */
	key->mac_proto = MAC_PROTO_NONE;
	invalidate_flow_key(key);
	वापस 0;
पूर्ण

अटल पूर्णांक push_eth(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
		    स्थिर काष्ठा ovs_action_push_eth *ethh)
अणु
	पूर्णांक err;

	err = skb_eth_push(skb, ethh->addresses.eth_dst,
			   ethh->addresses.eth_src);
	अगर (err)
		वापस err;

	/* safe right beक्रमe invalidate_flow_key */
	key->mac_proto = MAC_PROTO_ETHERNET;
	invalidate_flow_key(key);
	वापस 0;
पूर्ण

अटल पूर्णांक push_nsh(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
		    स्थिर काष्ठा nshhdr *nh)
अणु
	पूर्णांक err;

	err = nsh_push(skb, nh);
	अगर (err)
		वापस err;

	/* safe right beक्रमe invalidate_flow_key */
	key->mac_proto = MAC_PROTO_NONE;
	invalidate_flow_key(key);
	वापस 0;
पूर्ण

अटल पूर्णांक pop_nsh(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक err;

	err = nsh_pop(skb);
	अगर (err)
		वापस err;

	/* safe right beक्रमe invalidate_flow_key */
	अगर (skb->protocol == htons(ETH_P_TEB))
		key->mac_proto = MAC_PROTO_ETHERNET;
	अन्यथा
		key->mac_proto = MAC_PROTO_NONE;
	invalidate_flow_key(key);
	वापस 0;
पूर्ण

अटल व्योम update_ip_l4_checksum(काष्ठा sk_buff *skb, काष्ठा iphdr *nh,
				  __be32 addr, __be32 new_addr)
अणु
	पूर्णांक transport_len = skb->len - skb_transport_offset(skb);

	अगर (nh->frag_off & htons(IP_OFFSET))
		वापस;

	अगर (nh->protocol == IPPROTO_TCP) अणु
		अगर (likely(transport_len >= माप(काष्ठा tcphdr)))
			inet_proto_csum_replace4(&tcp_hdr(skb)->check, skb,
						 addr, new_addr, true);
	पूर्ण अन्यथा अगर (nh->protocol == IPPROTO_UDP) अणु
		अगर (likely(transport_len >= माप(काष्ठा udphdr))) अणु
			काष्ठा udphdr *uh = udp_hdr(skb);

			अगर (uh->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
				inet_proto_csum_replace4(&uh->check, skb,
							 addr, new_addr, true);
				अगर (!uh->check)
					uh->check = CSUM_MANGLED_0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_ip_addr(काष्ठा sk_buff *skb, काष्ठा iphdr *nh,
			__be32 *addr, __be32 new_addr)
अणु
	update_ip_l4_checksum(skb, nh, *addr, new_addr);
	csum_replace4(&nh->check, *addr, new_addr);
	skb_clear_hash(skb);
	*addr = new_addr;
पूर्ण

अटल व्योम update_ipv6_checksum(काष्ठा sk_buff *skb, u8 l4_proto,
				 __be32 addr[4], स्थिर __be32 new_addr[4])
अणु
	पूर्णांक transport_len = skb->len - skb_transport_offset(skb);

	अगर (l4_proto == NEXTHDR_TCP) अणु
		अगर (likely(transport_len >= माप(काष्ठा tcphdr)))
			inet_proto_csum_replace16(&tcp_hdr(skb)->check, skb,
						  addr, new_addr, true);
	पूर्ण अन्यथा अगर (l4_proto == NEXTHDR_UDP) अणु
		अगर (likely(transport_len >= माप(काष्ठा udphdr))) अणु
			काष्ठा udphdr *uh = udp_hdr(skb);

			अगर (uh->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
				inet_proto_csum_replace16(&uh->check, skb,
							  addr, new_addr, true);
				अगर (!uh->check)
					uh->check = CSUM_MANGLED_0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (l4_proto == NEXTHDR_ICMP) अणु
		अगर (likely(transport_len >= माप(काष्ठा icmp6hdr)))
			inet_proto_csum_replace16(&icmp6_hdr(skb)->icmp6_cksum,
						  skb, addr, new_addr, true);
	पूर्ण
पूर्ण

अटल व्योम mask_ipv6_addr(स्थिर __be32 old[4], स्थिर __be32 addr[4],
			   स्थिर __be32 mask[4], __be32 masked[4])
अणु
	masked[0] = OVS_MASKED(old[0], addr[0], mask[0]);
	masked[1] = OVS_MASKED(old[1], addr[1], mask[1]);
	masked[2] = OVS_MASKED(old[2], addr[2], mask[2]);
	masked[3] = OVS_MASKED(old[3], addr[3], mask[3]);
पूर्ण

अटल व्योम set_ipv6_addr(काष्ठा sk_buff *skb, u8 l4_proto,
			  __be32 addr[4], स्थिर __be32 new_addr[4],
			  bool recalculate_csum)
अणु
	अगर (recalculate_csum)
		update_ipv6_checksum(skb, l4_proto, addr, new_addr);

	skb_clear_hash(skb);
	स_नकल(addr, new_addr, माप(__be32[4]));
पूर्ण

अटल व्योम set_ipv6_fl(काष्ठा ipv6hdr *nh, u32 fl, u32 mask)
अणु
	/* Bits 21-24 are always unmasked, so this retains their values. */
	OVS_SET_MASKED(nh->flow_lbl[0], (u8)(fl >> 16), (u8)(mask >> 16));
	OVS_SET_MASKED(nh->flow_lbl[1], (u8)(fl >> 8), (u8)(mask >> 8));
	OVS_SET_MASKED(nh->flow_lbl[2], (u8)fl, (u8)mask);
पूर्ण

अटल व्योम set_ip_ttl(काष्ठा sk_buff *skb, काष्ठा iphdr *nh, u8 new_ttl,
		       u8 mask)
अणु
	new_ttl = OVS_MASKED(nh->ttl, new_ttl, mask);

	csum_replace2(&nh->check, htons(nh->ttl << 8), htons(new_ttl << 8));
	nh->ttl = new_ttl;
पूर्ण

अटल पूर्णांक set_ipv4(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		    स्थिर काष्ठा ovs_key_ipv4 *key,
		    स्थिर काष्ठा ovs_key_ipv4 *mask)
अणु
	काष्ठा iphdr *nh;
	__be32 new_addr;
	पूर्णांक err;

	err = skb_ensure_writable(skb, skb_network_offset(skb) +
				  माप(काष्ठा iphdr));
	अगर (unlikely(err))
		वापस err;

	nh = ip_hdr(skb);

	/* Setting an IP addresses is typically only a side effect of
	 * matching on them in the current userspace implementation, so it
	 * makes sense to check अगर the value actually changed.
	 */
	अगर (mask->ipv4_src) अणु
		new_addr = OVS_MASKED(nh->saddr, key->ipv4_src, mask->ipv4_src);

		अगर (unlikely(new_addr != nh->saddr)) अणु
			set_ip_addr(skb, nh, &nh->saddr, new_addr);
			flow_key->ipv4.addr.src = new_addr;
		पूर्ण
	पूर्ण
	अगर (mask->ipv4_dst) अणु
		new_addr = OVS_MASKED(nh->daddr, key->ipv4_dst, mask->ipv4_dst);

		अगर (unlikely(new_addr != nh->daddr)) अणु
			set_ip_addr(skb, nh, &nh->daddr, new_addr);
			flow_key->ipv4.addr.dst = new_addr;
		पूर्ण
	पूर्ण
	अगर (mask->ipv4_tos) अणु
		ipv4_change_dsfield(nh, ~mask->ipv4_tos, key->ipv4_tos);
		flow_key->ip.tos = nh->tos;
	पूर्ण
	अगर (mask->ipv4_ttl) अणु
		set_ip_ttl(skb, nh, key->ipv4_ttl, mask->ipv4_ttl);
		flow_key->ip.ttl = nh->ttl;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_ipv6_mask_nonzero(स्थिर __be32 addr[4])
अणु
	वापस !!(addr[0] | addr[1] | addr[2] | addr[3]);
पूर्ण

अटल पूर्णांक set_ipv6(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		    स्थिर काष्ठा ovs_key_ipv6 *key,
		    स्थिर काष्ठा ovs_key_ipv6 *mask)
अणु
	काष्ठा ipv6hdr *nh;
	पूर्णांक err;

	err = skb_ensure_writable(skb, skb_network_offset(skb) +
				  माप(काष्ठा ipv6hdr));
	अगर (unlikely(err))
		वापस err;

	nh = ipv6_hdr(skb);

	/* Setting an IP addresses is typically only a side effect of
	 * matching on them in the current userspace implementation, so it
	 * makes sense to check अगर the value actually changed.
	 */
	अगर (is_ipv6_mask_nonzero(mask->ipv6_src)) अणु
		__be32 *saddr = (__be32 *)&nh->saddr;
		__be32 masked[4];

		mask_ipv6_addr(saddr, key->ipv6_src, mask->ipv6_src, masked);

		अगर (unlikely(स_भेद(saddr, masked, माप(masked)))) अणु
			set_ipv6_addr(skb, flow_key->ip.proto, saddr, masked,
				      true);
			स_नकल(&flow_key->ipv6.addr.src, masked,
			       माप(flow_key->ipv6.addr.src));
		पूर्ण
	पूर्ण
	अगर (is_ipv6_mask_nonzero(mask->ipv6_dst)) अणु
		अचिन्हित पूर्णांक offset = 0;
		पूर्णांक flags = IP6_FH_F_SKIP_RH;
		bool recalc_csum = true;
		__be32 *daddr = (__be32 *)&nh->daddr;
		__be32 masked[4];

		mask_ipv6_addr(daddr, key->ipv6_dst, mask->ipv6_dst, masked);

		अगर (unlikely(स_भेद(daddr, masked, माप(masked)))) अणु
			अगर (ipv6_ext_hdr(nh->nexthdr))
				recalc_csum = (ipv6_find_hdr(skb, &offset,
							     NEXTHDR_ROUTING,
							     शून्य, &flags)
					       != NEXTHDR_ROUTING);

			set_ipv6_addr(skb, flow_key->ip.proto, daddr, masked,
				      recalc_csum);
			स_नकल(&flow_key->ipv6.addr.dst, masked,
			       माप(flow_key->ipv6.addr.dst));
		पूर्ण
	पूर्ण
	अगर (mask->ipv6_tclass) अणु
		ipv6_change_dsfield(nh, ~mask->ipv6_tclass, key->ipv6_tclass);
		flow_key->ip.tos = ipv6_get_dsfield(nh);
	पूर्ण
	अगर (mask->ipv6_label) अणु
		set_ipv6_fl(nh, ntohl(key->ipv6_label),
			    ntohl(mask->ipv6_label));
		flow_key->ipv6.label =
		    *(__be32 *)nh & htonl(IPV6_FLOWINFO_FLOWLABEL);
	पूर्ण
	अगर (mask->ipv6_hlimit) अणु
		OVS_SET_MASKED(nh->hop_limit, key->ipv6_hlimit,
			       mask->ipv6_hlimit);
		flow_key->ip.ttl = nh->hop_limit;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_nsh(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		   स्थिर काष्ठा nlattr *a)
अणु
	काष्ठा nshhdr *nh;
	माप_प्रकार length;
	पूर्णांक err;
	u8 flags;
	u8 ttl;
	पूर्णांक i;

	काष्ठा ovs_key_nsh key;
	काष्ठा ovs_key_nsh mask;

	err = nsh_key_from_nlattr(a, &key, &mask);
	अगर (err)
		वापस err;

	/* Make sure the NSH base header is there */
	अगर (!pskb_may_pull(skb, skb_network_offset(skb) + NSH_BASE_HDR_LEN))
		वापस -ENOMEM;

	nh = nsh_hdr(skb);
	length = nsh_hdr_len(nh);

	/* Make sure the whole NSH header is there */
	err = skb_ensure_writable(skb, skb_network_offset(skb) +
				       length);
	अगर (unlikely(err))
		वापस err;

	nh = nsh_hdr(skb);
	skb_postpull_rcsum(skb, nh, length);
	flags = nsh_get_flags(nh);
	flags = OVS_MASKED(flags, key.base.flags, mask.base.flags);
	flow_key->nsh.base.flags = flags;
	ttl = nsh_get_ttl(nh);
	ttl = OVS_MASKED(ttl, key.base.ttl, mask.base.ttl);
	flow_key->nsh.base.ttl = ttl;
	nsh_set_flags_and_ttl(nh, flags, ttl);
	nh->path_hdr = OVS_MASKED(nh->path_hdr, key.base.path_hdr,
				  mask.base.path_hdr);
	flow_key->nsh.base.path_hdr = nh->path_hdr;
	चयन (nh->mdtype) अणु
	हाल NSH_M_TYPE1:
		क्रम (i = 0; i < NSH_MD1_CONTEXT_SIZE; i++) अणु
			nh->md1.context[i] =
			    OVS_MASKED(nh->md1.context[i], key.context[i],
				       mask.context[i]);
		पूर्ण
		स_नकल(flow_key->nsh.context, nh->md1.context,
		       माप(nh->md1.context));
		अवरोध;
	हाल NSH_M_TYPE2:
		स_रखो(flow_key->nsh.context, 0,
		       माप(flow_key->nsh.context));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	skb_postpush_rcsum(skb, nh, length);
	वापस 0;
पूर्ण

/* Must follow skb_ensure_writable() since that can move the skb data. */
अटल व्योम set_tp_port(काष्ठा sk_buff *skb, __be16 *port,
			__be16 new_port, __sum16 *check)
अणु
	inet_proto_csum_replace2(check, skb, *port, new_port, false);
	*port = new_port;
पूर्ण

अटल पूर्णांक set_udp(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		   स्थिर काष्ठा ovs_key_udp *key,
		   स्थिर काष्ठा ovs_key_udp *mask)
अणु
	काष्ठा udphdr *uh;
	__be16 src, dst;
	पूर्णांक err;

	err = skb_ensure_writable(skb, skb_transport_offset(skb) +
				  माप(काष्ठा udphdr));
	अगर (unlikely(err))
		वापस err;

	uh = udp_hdr(skb);
	/* Either of the masks is non-zero, so करो not bother checking them. */
	src = OVS_MASKED(uh->source, key->udp_src, mask->udp_src);
	dst = OVS_MASKED(uh->dest, key->udp_dst, mask->udp_dst);

	अगर (uh->check && skb->ip_summed != CHECKSUM_PARTIAL) अणु
		अगर (likely(src != uh->source)) अणु
			set_tp_port(skb, &uh->source, src, &uh->check);
			flow_key->tp.src = src;
		पूर्ण
		अगर (likely(dst != uh->dest)) अणु
			set_tp_port(skb, &uh->dest, dst, &uh->check);
			flow_key->tp.dst = dst;
		पूर्ण

		अगर (unlikely(!uh->check))
			uh->check = CSUM_MANGLED_0;
	पूर्ण अन्यथा अणु
		uh->source = src;
		uh->dest = dst;
		flow_key->tp.src = src;
		flow_key->tp.dst = dst;
	पूर्ण

	skb_clear_hash(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक set_tcp(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		   स्थिर काष्ठा ovs_key_tcp *key,
		   स्थिर काष्ठा ovs_key_tcp *mask)
अणु
	काष्ठा tcphdr *th;
	__be16 src, dst;
	पूर्णांक err;

	err = skb_ensure_writable(skb, skb_transport_offset(skb) +
				  माप(काष्ठा tcphdr));
	अगर (unlikely(err))
		वापस err;

	th = tcp_hdr(skb);
	src = OVS_MASKED(th->source, key->tcp_src, mask->tcp_src);
	अगर (likely(src != th->source)) अणु
		set_tp_port(skb, &th->source, src, &th->check);
		flow_key->tp.src = src;
	पूर्ण
	dst = OVS_MASKED(th->dest, key->tcp_dst, mask->tcp_dst);
	अगर (likely(dst != th->dest)) अणु
		set_tp_port(skb, &th->dest, dst, &th->check);
		flow_key->tp.dst = dst;
	पूर्ण
	skb_clear_hash(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक set_sctp(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *flow_key,
		    स्थिर काष्ठा ovs_key_sctp *key,
		    स्थिर काष्ठा ovs_key_sctp *mask)
अणु
	अचिन्हित पूर्णांक sctphoff = skb_transport_offset(skb);
	काष्ठा sctphdr *sh;
	__le32 old_correct_csum, new_csum, old_csum;
	पूर्णांक err;

	err = skb_ensure_writable(skb, sctphoff + माप(काष्ठा sctphdr));
	अगर (unlikely(err))
		वापस err;

	sh = sctp_hdr(skb);
	old_csum = sh->checksum;
	old_correct_csum = sctp_compute_cksum(skb, sctphoff);

	sh->source = OVS_MASKED(sh->source, key->sctp_src, mask->sctp_src);
	sh->dest = OVS_MASKED(sh->dest, key->sctp_dst, mask->sctp_dst);

	new_csum = sctp_compute_cksum(skb, sctphoff);

	/* Carry any checksum errors through. */
	sh->checksum = old_csum ^ old_correct_csum ^ new_csum;

	skb_clear_hash(skb);
	flow_key->tp.src = sh->source;
	flow_key->tp.dst = sh->dest;

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_vport_output(काष्ठा net *net, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा ovs_frag_data *data = this_cpu_ptr(&ovs_frag_data_storage);
	काष्ठा vport *vport = data->vport;

	अगर (skb_cow_head(skb, data->l2_len) < 0) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	__skb_dst_copy(skb, data->dst);
	*OVS_CB(skb) = data->cb;
	skb->inner_protocol = data->inner_protocol;
	अगर (data->vlan_tci & VLAN_CFI_MASK)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto, data->vlan_tci & ~VLAN_CFI_MASK);
	अन्यथा
		__vlan_hwaccel_clear_tag(skb);

	/* Reस्थिरruct the MAC header.  */
	skb_push(skb, data->l2_len);
	स_नकल(skb->data, &data->l2_data, data->l2_len);
	skb_postpush_rcsum(skb, skb->data, data->l2_len);
	skb_reset_mac_header(skb);

	अगर (eth_p_mpls(skb->protocol)) अणु
		skb->inner_network_header = skb->network_header;
		skb_set_network_header(skb, data->network_offset);
		skb_reset_mac_len(skb);
	पूर्ण

	ovs_vport_send(vport, skb, data->mac_proto);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
ovs_dst_get_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst->dev->mtu;
पूर्ण

अटल काष्ठा dst_ops ovs_dst_ops = अणु
	.family = AF_UNSPEC,
	.mtu = ovs_dst_get_mtu,
पूर्ण;

/* prepare_frag() is called once per (larger-than-MTU) frame; its inverse is
 * ovs_vport_output(), which is called once per fragmented packet.
 */
अटल व्योम prepare_frag(काष्ठा vport *vport, काष्ठा sk_buff *skb,
			 u16 orig_network_offset, u8 mac_proto)
अणु
	अचिन्हित पूर्णांक hlen = skb_network_offset(skb);
	काष्ठा ovs_frag_data *data;

	data = this_cpu_ptr(&ovs_frag_data_storage);
	data->dst = skb->_skb_refdst;
	data->vport = vport;
	data->cb = *OVS_CB(skb);
	data->inner_protocol = skb->inner_protocol;
	data->network_offset = orig_network_offset;
	अगर (skb_vlan_tag_present(skb))
		data->vlan_tci = skb_vlan_tag_get(skb) | VLAN_CFI_MASK;
	अन्यथा
		data->vlan_tci = 0;
	data->vlan_proto = skb->vlan_proto;
	data->mac_proto = mac_proto;
	data->l2_len = hlen;
	स_नकल(&data->l2_data, skb->data, hlen);

	स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
	skb_pull(skb, hlen);
पूर्ण

अटल व्योम ovs_fragment(काष्ठा net *net, काष्ठा vport *vport,
			 काष्ठा sk_buff *skb, u16 mru,
			 काष्ठा sw_flow_key *key)
अणु
	u16 orig_network_offset = 0;

	अगर (eth_p_mpls(skb->protocol)) अणु
		orig_network_offset = skb_network_offset(skb);
		skb->network_header = skb->inner_network_header;
	पूर्ण

	अगर (skb_network_offset(skb) > MAX_L2_LEN) अणु
		OVS_NLERR(1, "L2 header too long to fragment");
		जाओ err;
	पूर्ण

	अगर (key->eth.type == htons(ETH_P_IP)) अणु
		काष्ठा rtable ovs_rt = अणु 0 पूर्ण;
		अचिन्हित दीर्घ orig_dst;

		prepare_frag(vport, skb, orig_network_offset,
			     ovs_key_mac_proto(key));
		dst_init(&ovs_rt.dst, &ovs_dst_ops, शून्य, 1,
			 DST_OBSOLETE_NONE, DST_NOCOUNT);
		ovs_rt.dst.dev = vport->dev;

		orig_dst = skb->_skb_refdst;
		skb_dst_set_noref(skb, &ovs_rt.dst);
		IPCB(skb)->frag_max_size = mru;

		ip_करो_fragment(net, skb->sk, skb, ovs_vport_output);
		refdst_drop(orig_dst);
	पूर्ण अन्यथा अगर (key->eth.type == htons(ETH_P_IPV6)) अणु
		अचिन्हित दीर्घ orig_dst;
		काष्ठा rt6_info ovs_rt;

		prepare_frag(vport, skb, orig_network_offset,
			     ovs_key_mac_proto(key));
		स_रखो(&ovs_rt, 0, माप(ovs_rt));
		dst_init(&ovs_rt.dst, &ovs_dst_ops, शून्य, 1,
			 DST_OBSOLETE_NONE, DST_NOCOUNT);
		ovs_rt.dst.dev = vport->dev;

		orig_dst = skb->_skb_refdst;
		skb_dst_set_noref(skb, &ovs_rt.dst);
		IP6CB(skb)->frag_max_size = mru;

		ipv6_stub->ipv6_fragment(net, skb->sk, skb, ovs_vport_output);
		refdst_drop(orig_dst);
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Failed fragment ->%s: eth=%04x, MRU=%d, MTU=%d.",
			  ovs_vport_name(vport), ntohs(key->eth.type), mru,
			  vport->dev->mtu);
		जाओ err;
	पूर्ण

	वापस;
err:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम करो_output(काष्ठा datapath *dp, काष्ठा sk_buff *skb, पूर्णांक out_port,
		      काष्ठा sw_flow_key *key)
अणु
	काष्ठा vport *vport = ovs_vport_rcu(dp, out_port);

	अगर (likely(vport)) अणु
		u16 mru = OVS_CB(skb)->mru;
		u32 cutlen = OVS_CB(skb)->cutlen;

		अगर (unlikely(cutlen > 0)) अणु
			अगर (skb->len - cutlen > ovs_mac_header_len(key))
				pskb_trim(skb, skb->len - cutlen);
			अन्यथा
				pskb_trim(skb, ovs_mac_header_len(key));
		पूर्ण

		अगर (likely(!mru ||
		           (skb->len <= mru + vport->dev->hard_header_len))) अणु
			ovs_vport_send(vport, skb, ovs_key_mac_proto(key));
		पूर्ण अन्यथा अगर (mru <= vport->dev->mtu) अणु
			काष्ठा net *net = पढ़ो_pnet(&dp->net);

			ovs_fragment(net, vport, skb, mru, key);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक output_userspace(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			    काष्ठा sw_flow_key *key, स्थिर काष्ठा nlattr *attr,
			    स्थिर काष्ठा nlattr *actions, पूर्णांक actions_len,
			    uपूर्णांक32_t cutlen)
अणु
	काष्ठा dp_upcall_info upcall;
	स्थिर काष्ठा nlattr *a;
	पूर्णांक rem;

	स_रखो(&upcall, 0, माप(upcall));
	upcall.cmd = OVS_PACKET_CMD_ACTION;
	upcall.mru = OVS_CB(skb)->mru;

	क्रम (a = nla_data(attr), rem = nla_len(attr); rem > 0;
	     a = nla_next(a, &rem)) अणु
		चयन (nla_type(a)) अणु
		हाल OVS_USERSPACE_ATTR_USERDATA:
			upcall.userdata = a;
			अवरोध;

		हाल OVS_USERSPACE_ATTR_PID:
			upcall.portid = nla_get_u32(a);
			अवरोध;

		हाल OVS_USERSPACE_ATTR_EGRESS_TUN_PORT: अणु
			/* Get out tunnel info. */
			काष्ठा vport *vport;

			vport = ovs_vport_rcu(dp, nla_get_u32(a));
			अगर (vport) अणु
				पूर्णांक err;

				err = dev_fill_metadata_dst(vport->dev, skb);
				अगर (!err)
					upcall.egress_tun_info = skb_tunnel_info(skb);
			पूर्ण

			अवरोध;
		पूर्ण

		हाल OVS_USERSPACE_ATTR_ACTIONS: अणु
			/* Include actions. */
			upcall.actions = actions;
			upcall.actions_len = actions_len;
			अवरोध;
		पूर्ण

		पूर्ण /* End of चयन. */
	पूर्ण

	वापस ovs_dp_upcall(dp, skb, key, &upcall, cutlen);
पूर्ण

अटल पूर्णांक dec_ttl_exception_handler(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
				     काष्ठा sw_flow_key *key,
				     स्थिर काष्ठा nlattr *attr)
अणु
	/* The first attribute is always 'OVS_DEC_TTL_ATTR_ACTION'. */
	काष्ठा nlattr *actions = nla_data(attr);

	अगर (nla_len(actions))
		वापस clone_execute(dp, skb, key, 0, nla_data(actions),
				     nla_len(actions), true, false);

	consume_skb(skb);
	वापस 0;
पूर्ण

/* When 'last' is true, sample() should always consume the 'skb'.
 * Otherwise, sample() should keep 'skb' पूर्णांकact regardless what
 * actions are executed within sample().
 */
अटल पूर्णांक sample(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
		  काष्ठा sw_flow_key *key, स्थिर काष्ठा nlattr *attr,
		  bool last)
अणु
	काष्ठा nlattr *actions;
	काष्ठा nlattr *sample_arg;
	पूर्णांक rem = nla_len(attr);
	स्थिर काष्ठा sample_arg *arg;
	bool clone_flow_key;

	/* The first action is always 'OVS_SAMPLE_ATTR_ARG'. */
	sample_arg = nla_data(attr);
	arg = nla_data(sample_arg);
	actions = nla_next(sample_arg, &rem);

	अगर ((arg->probability != U32_MAX) &&
	    (!arg->probability || pअक्रमom_u32() > arg->probability)) अणु
		अगर (last)
			consume_skb(skb);
		वापस 0;
	पूर्ण

	clone_flow_key = !arg->exec;
	वापस clone_execute(dp, skb, key, 0, actions, rem, last,
			     clone_flow_key);
पूर्ण

/* When 'last' is true, clone() should always consume the 'skb'.
 * Otherwise, clone() should keep 'skb' पूर्णांकact regardless what
 * actions are executed within clone().
 */
अटल पूर्णांक clone(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
		 काष्ठा sw_flow_key *key, स्थिर काष्ठा nlattr *attr,
		 bool last)
अणु
	काष्ठा nlattr *actions;
	काष्ठा nlattr *clone_arg;
	पूर्णांक rem = nla_len(attr);
	bool करोnt_clone_flow_key;

	/* The first action is always 'OVS_CLONE_ATTR_ARG'. */
	clone_arg = nla_data(attr);
	करोnt_clone_flow_key = nla_get_u32(clone_arg);
	actions = nla_next(clone_arg, &rem);

	वापस clone_execute(dp, skb, key, 0, actions, rem, last,
			     !करोnt_clone_flow_key);
पूर्ण

अटल व्योम execute_hash(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key,
			 स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा ovs_action_hash *hash_act = nla_data(attr);
	u32 hash = 0;

	/* OVS_HASH_ALG_L4 is the only possible hash algorithm.  */
	hash = skb_get_hash(skb);
	hash = jhash_1word(hash, hash_act->hash_basis);
	अगर (!hash)
		hash = 0x1;

	key->ovs_flow_hash = hash;
पूर्ण

अटल पूर्णांक execute_set_action(काष्ठा sk_buff *skb,
			      काष्ठा sw_flow_key *flow_key,
			      स्थिर काष्ठा nlattr *a)
अणु
	/* Only tunnel set execution is supported without a mask. */
	अगर (nla_type(a) == OVS_KEY_ATTR_TUNNEL_INFO) अणु
		काष्ठा ovs_tunnel_info *tun = nla_data(a);

		skb_dst_drop(skb);
		dst_hold((काष्ठा dst_entry *)tun->tun_dst);
		skb_dst_set(skb, (काष्ठा dst_entry *)tun->tun_dst);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Mask is at the midpoपूर्णांक of the data. */
#घोषणा get_mask(a, type) ((स्थिर type)nla_data(a) + 1)

अटल पूर्णांक execute_masked_set_action(काष्ठा sk_buff *skb,
				     काष्ठा sw_flow_key *flow_key,
				     स्थिर काष्ठा nlattr *a)
अणु
	पूर्णांक err = 0;

	चयन (nla_type(a)) अणु
	हाल OVS_KEY_ATTR_PRIORITY:
		OVS_SET_MASKED(skb->priority, nla_get_u32(a),
			       *get_mask(a, u32 *));
		flow_key->phy.priority = skb->priority;
		अवरोध;

	हाल OVS_KEY_ATTR_SKB_MARK:
		OVS_SET_MASKED(skb->mark, nla_get_u32(a), *get_mask(a, u32 *));
		flow_key->phy.skb_mark = skb->mark;
		अवरोध;

	हाल OVS_KEY_ATTR_TUNNEL_INFO:
		/* Masked data not supported क्रम tunnel. */
		err = -EINVAL;
		अवरोध;

	हाल OVS_KEY_ATTR_ETHERNET:
		err = set_eth_addr(skb, flow_key, nla_data(a),
				   get_mask(a, काष्ठा ovs_key_ethernet *));
		अवरोध;

	हाल OVS_KEY_ATTR_NSH:
		err = set_nsh(skb, flow_key, a);
		अवरोध;

	हाल OVS_KEY_ATTR_IPV4:
		err = set_ipv4(skb, flow_key, nla_data(a),
			       get_mask(a, काष्ठा ovs_key_ipv4 *));
		अवरोध;

	हाल OVS_KEY_ATTR_IPV6:
		err = set_ipv6(skb, flow_key, nla_data(a),
			       get_mask(a, काष्ठा ovs_key_ipv6 *));
		अवरोध;

	हाल OVS_KEY_ATTR_TCP:
		err = set_tcp(skb, flow_key, nla_data(a),
			      get_mask(a, काष्ठा ovs_key_tcp *));
		अवरोध;

	हाल OVS_KEY_ATTR_UDP:
		err = set_udp(skb, flow_key, nla_data(a),
			      get_mask(a, काष्ठा ovs_key_udp *));
		अवरोध;

	हाल OVS_KEY_ATTR_SCTP:
		err = set_sctp(skb, flow_key, nla_data(a),
			       get_mask(a, काष्ठा ovs_key_sctp *));
		अवरोध;

	हाल OVS_KEY_ATTR_MPLS:
		err = set_mpls(skb, flow_key, nla_data(a), get_mask(a,
								    __be32 *));
		अवरोध;

	हाल OVS_KEY_ATTR_CT_STATE:
	हाल OVS_KEY_ATTR_CT_ZONE:
	हाल OVS_KEY_ATTR_CT_MARK:
	हाल OVS_KEY_ATTR_CT_LABELS:
	हाल OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4:
	हाल OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक execute_recirc(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			  काष्ठा sw_flow_key *key,
			  स्थिर काष्ठा nlattr *a, bool last)
अणु
	u32 recirc_id;

	अगर (!is_flow_key_valid(key)) अणु
		पूर्णांक err;

		err = ovs_flow_key_update(skb, key);
		अगर (err)
			वापस err;
	पूर्ण
	BUG_ON(!is_flow_key_valid(key));

	recirc_id = nla_get_u32(a);
	वापस clone_execute(dp, skb, key, recirc_id, शून्य, 0, last, true);
पूर्ण

अटल पूर्णांक execute_check_pkt_len(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
				 काष्ठा sw_flow_key *key,
				 स्थिर काष्ठा nlattr *attr, bool last)
अणु
	काष्ठा ovs_skb_cb *ovs_cb = OVS_CB(skb);
	स्थिर काष्ठा nlattr *actions, *cpl_arg;
	पूर्णांक len, max_len, rem = nla_len(attr);
	स्थिर काष्ठा check_pkt_len_arg *arg;
	bool clone_flow_key;

	/* The first netlink attribute in 'attr' is always
	 * 'OVS_CHECK_PKT_LEN_ATTR_ARG'.
	 */
	cpl_arg = nla_data(attr);
	arg = nla_data(cpl_arg);

	len = ovs_cb->mru ? ovs_cb->mru + skb->mac_len : skb->len;
	max_len = arg->pkt_len;

	अगर ((skb_is_gso(skb) && skb_gso_validate_mac_len(skb, max_len)) ||
	    len <= max_len) अणु
		/* Second netlink attribute in 'attr' is always
		 * 'OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_LESS_EQUAL'.
		 */
		actions = nla_next(cpl_arg, &rem);
		clone_flow_key = !arg->exec_क्रम_lesser_equal;
	पूर्ण अन्यथा अणु
		/* Third netlink attribute in 'attr' is always
		 * 'OVS_CHECK_PKT_LEN_ATTR_ACTIONS_IF_GREATER'.
		 */
		actions = nla_next(cpl_arg, &rem);
		actions = nla_next(actions, &rem);
		clone_flow_key = !arg->exec_क्रम_greater;
	पूर्ण

	वापस clone_execute(dp, skb, key, 0, nla_data(actions),
			     nla_len(actions), last, clone_flow_key);
पूर्ण

अटल पूर्णांक execute_dec_ttl(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	पूर्णांक err;

	अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *nh;

		err = skb_ensure_writable(skb, skb_network_offset(skb) +
					  माप(*nh));
		अगर (unlikely(err))
			वापस err;

		nh = ipv6_hdr(skb);

		अगर (nh->hop_limit <= 1)
			वापस -EHOSTUNREACH;

		key->ip.ttl = --nh->hop_limit;
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *nh;
		u8 old_ttl;

		err = skb_ensure_writable(skb, skb_network_offset(skb) +
					  माप(*nh));
		अगर (unlikely(err))
			वापस err;

		nh = ip_hdr(skb);
		अगर (nh->ttl <= 1)
			वापस -EHOSTUNREACH;

		old_ttl = nh->ttl--;
		csum_replace2(&nh->check, htons(old_ttl << 8),
			      htons(nh->ttl << 8));
		key->ip.ttl = nh->ttl;
	पूर्ण
	वापस 0;
पूर्ण

/* Execute a list of actions against 'skb'. */
अटल पूर्णांक करो_execute_actions(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			      काष्ठा sw_flow_key *key,
			      स्थिर काष्ठा nlattr *attr, पूर्णांक len)
अणु
	स्थिर काष्ठा nlattr *a;
	पूर्णांक rem;

	क्रम (a = attr, rem = len; rem > 0;
	     a = nla_next(a, &rem)) अणु
		पूर्णांक err = 0;

		चयन (nla_type(a)) अणु
		हाल OVS_ACTION_ATTR_OUTPUT: अणु
			पूर्णांक port = nla_get_u32(a);
			काष्ठा sk_buff *clone;

			/* Every output action needs a separate clone
			 * of 'skb', In हाल the output action is the
			 * last action, cloning can be aव्योमed.
			 */
			अगर (nla_is_last(a, rem)) अणु
				करो_output(dp, skb, port, key);
				/* 'skb' has been used क्रम output.
				 */
				वापस 0;
			पूर्ण

			clone = skb_clone(skb, GFP_ATOMIC);
			अगर (clone)
				करो_output(dp, clone, port, key);
			OVS_CB(skb)->cutlen = 0;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_TRUNC: अणु
			काष्ठा ovs_action_trunc *trunc = nla_data(a);

			अगर (skb->len > trunc->max_len)
				OVS_CB(skb)->cutlen = skb->len - trunc->max_len;
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_USERSPACE:
			output_userspace(dp, skb, key, a, attr,
						     len, OVS_CB(skb)->cutlen);
			OVS_CB(skb)->cutlen = 0;
			अवरोध;

		हाल OVS_ACTION_ATTR_HASH:
			execute_hash(skb, key, a);
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_MPLS: अणु
			काष्ठा ovs_action_push_mpls *mpls = nla_data(a);

			err = push_mpls(skb, key, mpls->mpls_lse,
					mpls->mpls_ethertype, skb->mac_len);
			अवरोध;
		पूर्ण
		हाल OVS_ACTION_ATTR_ADD_MPLS: अणु
			काष्ठा ovs_action_add_mpls *mpls = nla_data(a);
			__u16 mac_len = 0;

			अगर (mpls->tun_flags & OVS_MPLS_L3_TUNNEL_FLAG_MASK)
				mac_len = skb->mac_len;

			err = push_mpls(skb, key, mpls->mpls_lse,
					mpls->mpls_ethertype, mac_len);
			अवरोध;
		पूर्ण
		हाल OVS_ACTION_ATTR_POP_MPLS:
			err = pop_mpls(skb, key, nla_get_be16(a));
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_VLAN:
			err = push_vlan(skb, key, nla_data(a));
			अवरोध;

		हाल OVS_ACTION_ATTR_POP_VLAN:
			err = pop_vlan(skb, key);
			अवरोध;

		हाल OVS_ACTION_ATTR_RECIRC: अणु
			bool last = nla_is_last(a, rem);

			err = execute_recirc(dp, skb, key, a, last);
			अगर (last) अणु
				/* If this is the last action, the skb has
				 * been consumed or मुक्तd.
				 * Return immediately.
				 */
				वापस err;
			पूर्ण
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_SET:
			err = execute_set_action(skb, key, nla_data(a));
			अवरोध;

		हाल OVS_ACTION_ATTR_SET_MASKED:
		हाल OVS_ACTION_ATTR_SET_TO_MASKED:
			err = execute_masked_set_action(skb, key, nla_data(a));
			अवरोध;

		हाल OVS_ACTION_ATTR_SAMPLE: अणु
			bool last = nla_is_last(a, rem);

			err = sample(dp, skb, key, a, last);
			अगर (last)
				वापस err;

			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_CT:
			अगर (!is_flow_key_valid(key)) अणु
				err = ovs_flow_key_update(skb, key);
				अगर (err)
					वापस err;
			पूर्ण

			err = ovs_ct_execute(ovs_dp_get_net(dp), skb, key,
					     nla_data(a));

			/* Hide stolen IP fragments from user space. */
			अगर (err)
				वापस err == -EINPROGRESS ? 0 : err;
			अवरोध;

		हाल OVS_ACTION_ATTR_CT_CLEAR:
			err = ovs_ct_clear(skb, key);
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_ETH:
			err = push_eth(skb, key, nla_data(a));
			अवरोध;

		हाल OVS_ACTION_ATTR_POP_ETH:
			err = pop_eth(skb, key);
			अवरोध;

		हाल OVS_ACTION_ATTR_PUSH_NSH: अणु
			u8 buffer[NSH_HDR_MAX_LEN];
			काष्ठा nshhdr *nh = (काष्ठा nshhdr *)buffer;

			err = nsh_hdr_from_nlattr(nla_data(a), nh,
						  NSH_HDR_MAX_LEN);
			अगर (unlikely(err))
				अवरोध;
			err = push_nsh(skb, key, nh);
			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_POP_NSH:
			err = pop_nsh(skb, key);
			अवरोध;

		हाल OVS_ACTION_ATTR_METER:
			अगर (ovs_meter_execute(dp, skb, key, nla_get_u32(a))) अणु
				consume_skb(skb);
				वापस 0;
			पूर्ण
			अवरोध;

		हाल OVS_ACTION_ATTR_CLONE: अणु
			bool last = nla_is_last(a, rem);

			err = clone(dp, skb, key, a, last);
			अगर (last)
				वापस err;

			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_CHECK_PKT_LEN: अणु
			bool last = nla_is_last(a, rem);

			err = execute_check_pkt_len(dp, skb, key, a, last);
			अगर (last)
				वापस err;

			अवरोध;
		पूर्ण

		हाल OVS_ACTION_ATTR_DEC_TTL:
			err = execute_dec_ttl(skb, key);
			अगर (err == -EHOSTUNREACH)
				वापस dec_ttl_exception_handler(dp, skb,
								 key, a);
			अवरोध;
		पूर्ण

		अगर (unlikely(err)) अणु
			kमुक्त_skb(skb);
			वापस err;
		पूर्ण
	पूर्ण

	consume_skb(skb);
	वापस 0;
पूर्ण

/* Execute the actions on the clone of the packet. The effect of the
 * execution करोes not affect the original 'skb' nor the original 'key'.
 *
 * The execution may be deferred in हाल the actions can not be executed
 * immediately.
 */
अटल पूर्णांक clone_execute(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			 काष्ठा sw_flow_key *key, u32 recirc_id,
			 स्थिर काष्ठा nlattr *actions, पूर्णांक len,
			 bool last, bool clone_flow_key)
अणु
	काष्ठा deferred_action *da;
	काष्ठा sw_flow_key *clone;

	skb = last ? skb : skb_clone(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		/* Out of memory, skip this action.
		 */
		वापस 0;
	पूर्ण

	/* When clone_flow_key is false, the 'key' will not be change
	 * by the actions, then the 'key' can be used directly.
	 * Otherwise, try to clone key from the next recursion level of
	 * 'flow_keys'. If clone is successful, execute the actions
	 * without deferring.
	 */
	clone = clone_flow_key ? clone_key(key) : key;
	अगर (clone) अणु
		पूर्णांक err = 0;

		अगर (actions) अणु /* Sample action */
			अगर (clone_flow_key)
				__this_cpu_inc(exec_actions_level);

			err = करो_execute_actions(dp, skb, clone,
						 actions, len);

			अगर (clone_flow_key)
				__this_cpu_dec(exec_actions_level);
		पूर्ण अन्यथा अणु /* Recirc action */
			clone->recirc_id = recirc_id;
			ovs_dp_process_packet(skb, clone);
		पूर्ण
		वापस err;
	पूर्ण

	/* Out of 'flow_keys' space. Defer actions */
	da = add_deferred_actions(skb, key, actions, len);
	अगर (da) अणु
		अगर (!actions) अणु /* Recirc action */
			key = &da->pkt_key;
			key->recirc_id = recirc_id;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Out of per CPU action FIFO space. Drop the 'skb' and
		 * log an error.
		 */
		kमुक्त_skb(skb);

		अगर (net_ratelimit()) अणु
			अगर (actions) अणु /* Sample action */
				pr_warn("%s: deferred action limit reached, drop sample action\n",
					ovs_dp_name(dp));
			पूर्ण अन्यथा अणु  /* Recirc action */
				pr_warn("%s: deferred action limit reached, drop recirc action\n",
					ovs_dp_name(dp));
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम process_deferred_actions(काष्ठा datapath *dp)
अणु
	काष्ठा action_fअगरo *fअगरo = this_cpu_ptr(action_fअगरos);

	/* Do not touch the FIFO in हाल there is no deferred actions. */
	अगर (action_fअगरo_is_empty(fअगरo))
		वापस;

	/* Finishing executing all deferred actions. */
	करो अणु
		काष्ठा deferred_action *da = action_fअगरo_get(fअगरo);
		काष्ठा sk_buff *skb = da->skb;
		काष्ठा sw_flow_key *key = &da->pkt_key;
		स्थिर काष्ठा nlattr *actions = da->actions;
		पूर्णांक actions_len = da->actions_len;

		अगर (actions)
			करो_execute_actions(dp, skb, key, actions, actions_len);
		अन्यथा
			ovs_dp_process_packet(skb, key);
	पूर्ण जबतक (!action_fअगरo_is_empty(fअगरo));

	/* Reset FIFO क्रम the next packet.  */
	action_fअगरo_init(fअगरo);
पूर्ण

/* Execute a list of actions against 'skb'. */
पूर्णांक ovs_execute_actions(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			स्थिर काष्ठा sw_flow_actions *acts,
			काष्ठा sw_flow_key *key)
अणु
	पूर्णांक err, level;

	level = __this_cpu_inc_वापस(exec_actions_level);
	अगर (unlikely(level > OVS_RECURSION_LIMIT)) अणु
		net_crit_ratelimited("ovs: recursion limit reached on datapath %s, probable configuration error\n",
				     ovs_dp_name(dp));
		kमुक्त_skb(skb);
		err = -ENETDOWN;
		जाओ out;
	पूर्ण

	OVS_CB(skb)->acts_origlen = acts->orig_len;
	err = करो_execute_actions(dp, skb, key,
				 acts->actions, acts->actions_len);

	अगर (level == 1)
		process_deferred_actions(dp);

out:
	__this_cpu_dec(exec_actions_level);
	वापस err;
पूर्ण

पूर्णांक action_fअगरos_init(व्योम)
अणु
	action_fअगरos = alloc_percpu(काष्ठा action_fअगरo);
	अगर (!action_fअगरos)
		वापस -ENOMEM;

	flow_keys = alloc_percpu(काष्ठा action_flow_keys);
	अगर (!flow_keys) अणु
		मुक्त_percpu(action_fअगरos);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम action_fअगरos_निकास(व्योम)
अणु
	मुक्त_percpu(action_fअगरos);
	मुक्त_percpu(flow_keys);
पूर्ण
