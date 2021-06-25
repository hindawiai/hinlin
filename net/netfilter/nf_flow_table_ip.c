<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp_defs.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/neighbour.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
/* For layer 4 checksum field offset. */
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>

अटल पूर्णांक nf_flow_state_check(काष्ठा flow_offload *flow, पूर्णांक proto,
			       काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff)
अणु
	काष्ठा tcphdr *tcph;

	अगर (proto != IPPROTO_TCP)
		वापस 0;

	tcph = (व्योम *)(skb_network_header(skb) + thoff);
	अगर (unlikely(tcph->fin || tcph->rst)) अणु
		flow_offload_tearकरोwn(flow);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nf_flow_nat_ip_tcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
			       __be32 addr, __be32 new_addr)
अणु
	काष्ठा tcphdr *tcph;

	tcph = (व्योम *)(skb_network_header(skb) + thoff);
	inet_proto_csum_replace4(&tcph->check, skb, addr, new_addr, true);
पूर्ण

अटल व्योम nf_flow_nat_ip_udp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
			       __be32 addr, __be32 new_addr)
अणु
	काष्ठा udphdr *udph;

	udph = (व्योम *)(skb_network_header(skb) + thoff);
	अगर (udph->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
		inet_proto_csum_replace4(&udph->check, skb, addr,
					 new_addr, true);
		अगर (!udph->check)
			udph->check = CSUM_MANGLED_0;
	पूर्ण
पूर्ण

अटल व्योम nf_flow_nat_ip_l4proto(काष्ठा sk_buff *skb, काष्ठा iphdr *iph,
				   अचिन्हित पूर्णांक thoff, __be32 addr,
				   __be32 new_addr)
अणु
	चयन (iph->protocol) अणु
	हाल IPPROTO_TCP:
		nf_flow_nat_ip_tcp(skb, thoff, addr, new_addr);
		अवरोध;
	हाल IPPROTO_UDP:
		nf_flow_nat_ip_udp(skb, thoff, addr, new_addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nf_flow_snat_ip(स्थिर काष्ठा flow_offload *flow,
			    काष्ठा sk_buff *skb, काष्ठा iphdr *iph,
			    अचिन्हित पूर्णांक thoff, क्रमागत flow_offload_tuple_dir dir)
अणु
	__be32 addr, new_addr;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = iph->saddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.dst_v4.s_addr;
		iph->saddr = new_addr;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = iph->daddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.src_v4.s_addr;
		iph->daddr = new_addr;
		अवरोध;
	पूर्ण
	csum_replace4(&iph->check, addr, new_addr);

	nf_flow_nat_ip_l4proto(skb, iph, thoff, addr, new_addr);
पूर्ण

अटल व्योम nf_flow_dnat_ip(स्थिर काष्ठा flow_offload *flow,
			    काष्ठा sk_buff *skb, काष्ठा iphdr *iph,
			    अचिन्हित पूर्णांक thoff, क्रमागत flow_offload_tuple_dir dir)
अणु
	__be32 addr, new_addr;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = iph->daddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.src_v4.s_addr;
		iph->daddr = new_addr;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = iph->saddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.dst_v4.s_addr;
		iph->saddr = new_addr;
		अवरोध;
	पूर्ण
	csum_replace4(&iph->check, addr, new_addr);

	nf_flow_nat_ip_l4proto(skb, iph, thoff, addr, new_addr);
पूर्ण

अटल व्योम nf_flow_nat_ip(स्थिर काष्ठा flow_offload *flow, काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक thoff, क्रमागत flow_offload_tuple_dir dir,
			  काष्ठा iphdr *iph)
अणु
	अगर (test_bit(NF_FLOW_SNAT, &flow->flags)) अणु
		nf_flow_snat_port(flow, skb, thoff, iph->protocol, dir);
		nf_flow_snat_ip(flow, skb, iph, thoff, dir);
	पूर्ण
	अगर (test_bit(NF_FLOW_DNAT, &flow->flags)) अणु
		nf_flow_dnat_port(flow, skb, thoff, iph->protocol, dir);
		nf_flow_dnat_ip(flow, skb, iph, thoff, dir);
	पूर्ण
पूर्ण

अटल bool ip_has_options(अचिन्हित पूर्णांक thoff)
अणु
	वापस thoff != माप(काष्ठा iphdr);
पूर्ण

अटल व्योम nf_flow_tuple_encap(काष्ठा sk_buff *skb,
				काष्ठा flow_offload_tuple *tuple)
अणु
	काष्ठा vlan_ethhdr *veth;
	काष्ठा pppoe_hdr *phdr;
	पूर्णांक i = 0;

	अगर (skb_vlan_tag_present(skb)) अणु
		tuple->encap[i].id = skb_vlan_tag_get(skb);
		tuple->encap[i].proto = skb->vlan_proto;
		i++;
	पूर्ण
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_8021Q):
		veth = (काष्ठा vlan_ethhdr *)skb_mac_header(skb);
		tuple->encap[i].id = ntohs(veth->h_vlan_TCI);
		tuple->encap[i].proto = skb->protocol;
		अवरोध;
	हाल htons(ETH_P_PPP_SES):
		phdr = (काष्ठा pppoe_hdr *)skb_mac_header(skb);
		tuple->encap[i].id = ntohs(phdr->sid);
		tuple->encap[i].proto = skb->protocol;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nf_flow_tuple_ip(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			    काष्ठा flow_offload_tuple *tuple, u32 *hdrsize,
			    u32 offset)
अणु
	काष्ठा flow_ports *ports;
	अचिन्हित पूर्णांक thoff;
	काष्ठा iphdr *iph;

	अगर (!pskb_may_pull(skb, माप(*iph) + offset))
		वापस -1;

	iph = (काष्ठा iphdr *)(skb_network_header(skb) + offset);
	thoff = (iph->ihl * 4);

	अगर (ip_is_fragment(iph) ||
	    unlikely(ip_has_options(thoff)))
		वापस -1;

	thoff += offset;

	चयन (iph->protocol) अणु
	हाल IPPROTO_TCP:
		*hdrsize = माप(काष्ठा tcphdr);
		अवरोध;
	हाल IPPROTO_UDP:
		*hdrsize = माप(काष्ठा udphdr);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (iph->ttl <= 1)
		वापस -1;

	अगर (!pskb_may_pull(skb, thoff + *hdrsize))
		वापस -1;

	iph = (काष्ठा iphdr *)(skb_network_header(skb) + offset);
	ports = (काष्ठा flow_ports *)(skb_network_header(skb) + thoff);

	tuple->src_v4.s_addr	= iph->saddr;
	tuple->dst_v4.s_addr	= iph->daddr;
	tuple->src_port		= ports->source;
	tuple->dst_port		= ports->dest;
	tuple->l3proto		= AF_INET;
	tuple->l4proto		= iph->protocol;
	tuple->iअगरidx		= dev->अगरindex;
	nf_flow_tuple_encap(skb, tuple);

	वापस 0;
पूर्ण

/* Based on ip_exceeds_mtu(). */
अटल bool nf_flow_exceeds_mtu(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	अगर (skb->len <= mtu)
		वापस false;

	अगर (skb_is_gso(skb) && skb_gso_validate_network_len(skb, mtu))
		वापस false;

	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक nf_flow_xmit_xfrm(काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state,
				      काष्ठा dst_entry *dst)
अणु
	skb_orphan(skb);
	skb_dst_set_noref(skb, dst);
	dst_output(state->net, state->sk, skb);
	वापस NF_STOLEN;
पूर्ण

अटल अंतरभूत __be16 nf_flow_pppoe_proto(स्थिर काष्ठा sk_buff *skb)
अणु
	__be16 proto;

	proto = *((__be16 *)(skb_mac_header(skb) + ETH_HLEN +
			     माप(काष्ठा pppoe_hdr)));
	चयन (proto) अणु
	हाल htons(PPP_IP):
		वापस htons(ETH_P_IP);
	हाल htons(PPP_IPV6):
		वापस htons(ETH_P_IPV6);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool nf_flow_skb_encap_protocol(स्थिर काष्ठा sk_buff *skb, __be16 proto,
				       u32 *offset)
अणु
	काष्ठा vlan_ethhdr *veth;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_8021Q):
		veth = (काष्ठा vlan_ethhdr *)skb_mac_header(skb);
		अगर (veth->h_vlan_encapsulated_proto == proto) अणु
			*offset += VLAN_HLEN;
			वापस true;
		पूर्ण
		अवरोध;
	हाल htons(ETH_P_PPP_SES):
		अगर (nf_flow_pppoe_proto(skb) == proto) अणु
			*offset += PPPOE_SES_HLEN;
			वापस true;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम nf_flow_encap_pop(काष्ठा sk_buff *skb,
			      काष्ठा flow_offload_tuple_rhash *tuplehash)
अणु
	काष्ठा vlan_hdr *vlan_hdr;
	पूर्णांक i;

	क्रम (i = 0; i < tuplehash->tuple.encap_num; i++) अणु
		अगर (skb_vlan_tag_present(skb)) अणु
			__vlan_hwaccel_clear_tag(skb);
			जारी;
		पूर्ण
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_8021Q):
			vlan_hdr = (काष्ठा vlan_hdr *)skb->data;
			__skb_pull(skb, VLAN_HLEN);
			vlan_set_encap_proto(skb, vlan_hdr);
			skb_reset_network_header(skb);
			अवरोध;
		हाल htons(ETH_P_PPP_SES):
			skb->protocol = nf_flow_pppoe_proto(skb);
			skb_pull(skb, PPPOE_SES_HLEN);
			skb_reset_network_header(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक nf_flow_queue_xmit(काष्ठा net *net, काष्ठा sk_buff *skb,
				       स्थिर काष्ठा flow_offload_tuple_rhash *tuplehash,
				       अचिन्हित लघु type)
अणु
	काष्ठा net_device *outdev;

	outdev = dev_get_by_index_rcu(net, tuplehash->tuple.out.अगरidx);
	अगर (!outdev)
		वापस NF_DROP;

	skb->dev = outdev;
	dev_hard_header(skb, skb->dev, type, tuplehash->tuple.out.h_dest,
			tuplehash->tuple.out.h_source, skb->len);
	dev_queue_xmit(skb);

	वापस NF_STOLEN;
पूर्ण

अचिन्हित पूर्णांक
nf_flow_offload_ip_hook(व्योम *priv, काष्ठा sk_buff *skb,
			स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा flow_offload_tuple_rhash *tuplehash;
	काष्ठा nf_flowtable *flow_table = priv;
	काष्ठा flow_offload_tuple tuple = अणुपूर्ण;
	क्रमागत flow_offload_tuple_dir dir;
	काष्ठा flow_offload *flow;
	काष्ठा net_device *outdev;
	u32 hdrsize, offset = 0;
	अचिन्हित पूर्णांक thoff, mtu;
	काष्ठा rtable *rt;
	काष्ठा iphdr *iph;
	__be32 nexthop;
	पूर्णांक ret;

	अगर (skb->protocol != htons(ETH_P_IP) &&
	    !nf_flow_skb_encap_protocol(skb, htons(ETH_P_IP), &offset))
		वापस NF_ACCEPT;

	अगर (nf_flow_tuple_ip(skb, state->in, &tuple, &hdrsize, offset) < 0)
		वापस NF_ACCEPT;

	tuplehash = flow_offload_lookup(flow_table, &tuple);
	अगर (tuplehash == शून्य)
		वापस NF_ACCEPT;

	dir = tuplehash->tuple.dir;
	flow = container_of(tuplehash, काष्ठा flow_offload, tuplehash[dir]);

	mtu = flow->tuplehash[dir].tuple.mtu + offset;
	अगर (unlikely(nf_flow_exceeds_mtu(skb, mtu)))
		वापस NF_ACCEPT;

	iph = (काष्ठा iphdr *)(skb_network_header(skb) + offset);
	thoff = (iph->ihl * 4) + offset;
	अगर (nf_flow_state_check(flow, iph->protocol, skb, thoff))
		वापस NF_ACCEPT;

	अगर (skb_try_make_writable(skb, thoff + hdrsize))
		वापस NF_DROP;

	flow_offload_refresh(flow_table, flow);

	nf_flow_encap_pop(skb, tuplehash);
	thoff -= offset;

	iph = ip_hdr(skb);
	nf_flow_nat_ip(flow, skb, thoff, dir, iph);

	ip_decrease_ttl(iph);
	skb->tstamp = 0;

	अगर (flow_table->flags & NF_FLOWTABLE_COUNTER)
		nf_ct_acct_update(flow->ct, tuplehash->tuple.dir, skb->len);

	अगर (unlikely(tuplehash->tuple.xmit_type == FLOW_OFFLOAD_XMIT_XFRM)) अणु
		rt = (काष्ठा rtable *)tuplehash->tuple.dst_cache;
		स_रखो(skb->cb, 0, माप(काष्ठा inet_skb_parm));
		IPCB(skb)->iअगर = skb->dev->अगरindex;
		IPCB(skb)->flags = IPSKB_FORWARDED;
		वापस nf_flow_xmit_xfrm(skb, state, &rt->dst);
	पूर्ण

	चयन (tuplehash->tuple.xmit_type) अणु
	हाल FLOW_OFFLOAD_XMIT_NEIGH:
		rt = (काष्ठा rtable *)tuplehash->tuple.dst_cache;
		outdev = rt->dst.dev;
		skb->dev = outdev;
		nexthop = rt_nexthop(rt, flow->tuplehash[!dir].tuple.src_v4.s_addr);
		skb_dst_set_noref(skb, &rt->dst);
		neigh_xmit(NEIGH_ARP_TABLE, outdev, &nexthop, skb);
		ret = NF_STOLEN;
		अवरोध;
	हाल FLOW_OFFLOAD_XMIT_सूचीECT:
		ret = nf_flow_queue_xmit(state->net, skb, tuplehash, ETH_P_IP);
		अगर (ret == NF_DROP)
			flow_offload_tearकरोwn(flow);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_offload_ip_hook);

अटल व्योम nf_flow_nat_ipv6_tcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
				 काष्ठा in6_addr *addr,
				 काष्ठा in6_addr *new_addr,
				 काष्ठा ipv6hdr *ip6h)
अणु
	काष्ठा tcphdr *tcph;

	tcph = (व्योम *)(skb_network_header(skb) + thoff);
	inet_proto_csum_replace16(&tcph->check, skb, addr->s6_addr32,
				  new_addr->s6_addr32, true);
पूर्ण

अटल व्योम nf_flow_nat_ipv6_udp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
				 काष्ठा in6_addr *addr,
				 काष्ठा in6_addr *new_addr)
अणु
	काष्ठा udphdr *udph;

	udph = (व्योम *)(skb_network_header(skb) + thoff);
	अगर (udph->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
		inet_proto_csum_replace16(&udph->check, skb, addr->s6_addr32,
					  new_addr->s6_addr32, true);
		अगर (!udph->check)
			udph->check = CSUM_MANGLED_0;
	पूर्ण
पूर्ण

अटल व्योम nf_flow_nat_ipv6_l4proto(काष्ठा sk_buff *skb, काष्ठा ipv6hdr *ip6h,
				     अचिन्हित पूर्णांक thoff, काष्ठा in6_addr *addr,
				     काष्ठा in6_addr *new_addr)
अणु
	चयन (ip6h->nexthdr) अणु
	हाल IPPROTO_TCP:
		nf_flow_nat_ipv6_tcp(skb, thoff, addr, new_addr, ip6h);
		अवरोध;
	हाल IPPROTO_UDP:
		nf_flow_nat_ipv6_udp(skb, thoff, addr, new_addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nf_flow_snat_ipv6(स्थिर काष्ठा flow_offload *flow,
			      काष्ठा sk_buff *skb, काष्ठा ipv6hdr *ip6h,
			      अचिन्हित पूर्णांक thoff,
			      क्रमागत flow_offload_tuple_dir dir)
अणु
	काष्ठा in6_addr addr, new_addr;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = ip6h->saddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.dst_v6;
		ip6h->saddr = new_addr;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = ip6h->daddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.src_v6;
		ip6h->daddr = new_addr;
		अवरोध;
	पूर्ण

	nf_flow_nat_ipv6_l4proto(skb, ip6h, thoff, &addr, &new_addr);
पूर्ण

अटल व्योम nf_flow_dnat_ipv6(स्थिर काष्ठा flow_offload *flow,
			      काष्ठा sk_buff *skb, काष्ठा ipv6hdr *ip6h,
			      अचिन्हित पूर्णांक thoff,
			      क्रमागत flow_offload_tuple_dir dir)
अणु
	काष्ठा in6_addr addr, new_addr;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = ip6h->daddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.src_v6;
		ip6h->daddr = new_addr;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = ip6h->saddr;
		new_addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.dst_v6;
		ip6h->saddr = new_addr;
		अवरोध;
	पूर्ण

	nf_flow_nat_ipv6_l4proto(skb, ip6h, thoff, &addr, &new_addr);
पूर्ण

अटल व्योम nf_flow_nat_ipv6(स्थिर काष्ठा flow_offload *flow,
			     काष्ठा sk_buff *skb,
			     क्रमागत flow_offload_tuple_dir dir,
			     काष्ठा ipv6hdr *ip6h)
अणु
	अचिन्हित पूर्णांक thoff = माप(*ip6h);

	अगर (test_bit(NF_FLOW_SNAT, &flow->flags)) अणु
		nf_flow_snat_port(flow, skb, thoff, ip6h->nexthdr, dir);
		nf_flow_snat_ipv6(flow, skb, ip6h, thoff, dir);
	पूर्ण
	अगर (test_bit(NF_FLOW_DNAT, &flow->flags)) अणु
		nf_flow_dnat_port(flow, skb, thoff, ip6h->nexthdr, dir);
		nf_flow_dnat_ipv6(flow, skb, ip6h, thoff, dir);
	पूर्ण
पूर्ण

अटल पूर्णांक nf_flow_tuple_ipv6(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			      काष्ठा flow_offload_tuple *tuple, u32 *hdrsize,
			      u32 offset)
अणु
	काष्ठा flow_ports *ports;
	काष्ठा ipv6hdr *ip6h;
	अचिन्हित पूर्णांक thoff;

	thoff = माप(*ip6h) + offset;
	अगर (!pskb_may_pull(skb, thoff))
		वापस -1;

	ip6h = (काष्ठा ipv6hdr *)(skb_network_header(skb) + offset);

	चयन (ip6h->nexthdr) अणु
	हाल IPPROTO_TCP:
		*hdrsize = माप(काष्ठा tcphdr);
		अवरोध;
	हाल IPPROTO_UDP:
		*hdrsize = माप(काष्ठा udphdr);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (ip6h->hop_limit <= 1)
		वापस -1;

	अगर (!pskb_may_pull(skb, thoff + *hdrsize))
		वापस -1;

	ip6h = (काष्ठा ipv6hdr *)(skb_network_header(skb) + offset);
	ports = (काष्ठा flow_ports *)(skb_network_header(skb) + thoff);

	tuple->src_v6		= ip6h->saddr;
	tuple->dst_v6		= ip6h->daddr;
	tuple->src_port		= ports->source;
	tuple->dst_port		= ports->dest;
	tuple->l3proto		= AF_INET6;
	tuple->l4proto		= ip6h->nexthdr;
	tuple->iअगरidx		= dev->अगरindex;
	nf_flow_tuple_encap(skb, tuple);

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक
nf_flow_offload_ipv6_hook(व्योम *priv, काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा flow_offload_tuple_rhash *tuplehash;
	काष्ठा nf_flowtable *flow_table = priv;
	काष्ठा flow_offload_tuple tuple = अणुपूर्ण;
	क्रमागत flow_offload_tuple_dir dir;
	स्थिर काष्ठा in6_addr *nexthop;
	काष्ठा flow_offload *flow;
	काष्ठा net_device *outdev;
	अचिन्हित पूर्णांक thoff, mtu;
	u32 hdrsize, offset = 0;
	काष्ठा ipv6hdr *ip6h;
	काष्ठा rt6_info *rt;
	पूर्णांक ret;

	अगर (skb->protocol != htons(ETH_P_IPV6) &&
	    !nf_flow_skb_encap_protocol(skb, htons(ETH_P_IPV6), &offset))
		वापस NF_ACCEPT;

	अगर (nf_flow_tuple_ipv6(skb, state->in, &tuple, &hdrsize, offset) < 0)
		वापस NF_ACCEPT;

	tuplehash = flow_offload_lookup(flow_table, &tuple);
	अगर (tuplehash == शून्य)
		वापस NF_ACCEPT;

	dir = tuplehash->tuple.dir;
	flow = container_of(tuplehash, काष्ठा flow_offload, tuplehash[dir]);

	mtu = flow->tuplehash[dir].tuple.mtu + offset;
	अगर (unlikely(nf_flow_exceeds_mtu(skb, mtu)))
		वापस NF_ACCEPT;

	ip6h = (काष्ठा ipv6hdr *)(skb_network_header(skb) + offset);
	thoff = माप(*ip6h) + offset;
	अगर (nf_flow_state_check(flow, ip6h->nexthdr, skb, thoff))
		वापस NF_ACCEPT;

	अगर (skb_try_make_writable(skb, thoff + hdrsize))
		वापस NF_DROP;

	flow_offload_refresh(flow_table, flow);

	nf_flow_encap_pop(skb, tuplehash);

	ip6h = ipv6_hdr(skb);
	nf_flow_nat_ipv6(flow, skb, dir, ip6h);

	ip6h->hop_limit--;
	skb->tstamp = 0;

	अगर (flow_table->flags & NF_FLOWTABLE_COUNTER)
		nf_ct_acct_update(flow->ct, tuplehash->tuple.dir, skb->len);

	अगर (unlikely(tuplehash->tuple.xmit_type == FLOW_OFFLOAD_XMIT_XFRM)) अणु
		rt = (काष्ठा rt6_info *)tuplehash->tuple.dst_cache;
		स_रखो(skb->cb, 0, माप(काष्ठा inet6_skb_parm));
		IP6CB(skb)->iअगर = skb->dev->अगरindex;
		IP6CB(skb)->flags = IP6SKB_FORWARDED;
		वापस nf_flow_xmit_xfrm(skb, state, &rt->dst);
	पूर्ण

	चयन (tuplehash->tuple.xmit_type) अणु
	हाल FLOW_OFFLOAD_XMIT_NEIGH:
		rt = (काष्ठा rt6_info *)tuplehash->tuple.dst_cache;
		outdev = rt->dst.dev;
		skb->dev = outdev;
		nexthop = rt6_nexthop(rt, &flow->tuplehash[!dir].tuple.src_v6);
		skb_dst_set_noref(skb, &rt->dst);
		neigh_xmit(NEIGH_ND_TABLE, outdev, nexthop, skb);
		ret = NF_STOLEN;
		अवरोध;
	हाल FLOW_OFFLOAD_XMIT_सूचीECT:
		ret = nf_flow_queue_xmit(state->net, skb, tuplehash, ETH_P_IPV6);
		अगर (ret == NF_DROP)
			flow_offload_tearकरोwn(flow);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_offload_ipv6_hook);
