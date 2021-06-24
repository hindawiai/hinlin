<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2020 Mellanox Technologies. All rights reserved.
 */

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/lag.h>

अटल काष्ठा sk_buff *rdma_build_skb(काष्ठा ib_device *device,
				      काष्ठा net_device *netdev,
				      काष्ठा rdma_ah_attr *ah_attr,
				      gfp_t flags)
अणु
	काष्ठा ipv6hdr *ip6h;
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *eth;
	काष्ठा iphdr *iph;
	काष्ठा udphdr *uh;
	u8 smac[ETH_ALEN];
	bool is_ipv4;
	पूर्णांक hdr_len;

	is_ipv4 = ipv6_addr_v4mapped((काष्ठा in6_addr *)ah_attr->grh.dgid.raw);
	hdr_len = ETH_HLEN + माप(काष्ठा udphdr) + LL_RESERVED_SPACE(netdev);
	hdr_len += is_ipv4 ? माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr);

	skb = alloc_skb(hdr_len, flags);
	अगर (!skb)
		वापस शून्य;

	skb->dev = netdev;
	skb_reserve(skb, hdr_len);
	skb_push(skb, माप(काष्ठा udphdr));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);
	uh->source =
		htons(rdma_flow_label_to_udp_sport(ah_attr->grh.flow_label));
	uh->dest = htons(ROCE_V2_UDP_DPORT);
	uh->len = htons(माप(काष्ठा udphdr));

	अगर (is_ipv4) अणु
		skb_push(skb, माप(काष्ठा iphdr));
		skb_reset_network_header(skb);
		iph = ip_hdr(skb);
		iph->frag_off = 0;
		iph->version = 4;
		iph->protocol = IPPROTO_UDP;
		iph->ihl = 0x5;
		iph->tot_len = htons(माप(काष्ठा udphdr) + माप(काष्ठा
								    iphdr));
		स_नकल(&iph->saddr, ah_attr->grh.sgid_attr->gid.raw + 12,
		       माप(काष्ठा in_addr));
		स_नकल(&iph->daddr, ah_attr->grh.dgid.raw + 12,
		       माप(काष्ठा in_addr));
	पूर्ण अन्यथा अणु
		skb_push(skb, माप(काष्ठा ipv6hdr));
		skb_reset_network_header(skb);
		ip6h = ipv6_hdr(skb);
		ip6h->version = 6;
		ip6h->nexthdr = IPPROTO_UDP;
		स_नकल(&ip6h->flow_lbl, &ah_attr->grh.flow_label,
		       माप(*ip6h->flow_lbl));
		स_नकल(&ip6h->saddr, ah_attr->grh.sgid_attr->gid.raw,
		       माप(काष्ठा in6_addr));
		स_नकल(&ip6h->daddr, ah_attr->grh.dgid.raw,
		       माप(काष्ठा in6_addr));
	पूर्ण

	skb_push(skb, माप(काष्ठा ethhdr));
	skb_reset_mac_header(skb);
	eth = eth_hdr(skb);
	skb->protocol = eth->h_proto = htons(is_ipv4 ? ETH_P_IP : ETH_P_IPV6);
	rdma_पढ़ो_gid_l2_fields(ah_attr->grh.sgid_attr, शून्य, smac);
	स_नकल(eth->h_source, smac, ETH_ALEN);
	स_नकल(eth->h_dest, ah_attr->roce.dmac, ETH_ALEN);

	वापस skb;
पूर्ण

अटल काष्ठा net_device *rdma_get_xmit_slave_udp(काष्ठा ib_device *device,
						  काष्ठा net_device *master,
						  काष्ठा rdma_ah_attr *ah_attr,
						  gfp_t flags)
अणु
	काष्ठा net_device *slave;
	काष्ठा sk_buff *skb;

	skb = rdma_build_skb(device, master, ah_attr, flags);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	rcu_पढ़ो_lock();
	slave = netdev_get_xmit_slave(master, skb,
				      !!(device->lag_flags &
					 RDMA_LAG_FLAGS_HASH_ALL_SLAVES));
	अगर (slave)
		dev_hold(slave);
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
	वापस slave;
पूर्ण

व्योम rdma_lag_put_ah_roce_slave(काष्ठा net_device *xmit_slave)
अणु
	अगर (xmit_slave)
		dev_put(xmit_slave);
पूर्ण

काष्ठा net_device *rdma_lag_get_ah_roce_slave(काष्ठा ib_device *device,
					      काष्ठा rdma_ah_attr *ah_attr,
					      gfp_t flags)
अणु
	काष्ठा net_device *slave = शून्य;
	काष्ठा net_device *master;

	अगर (!(ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE &&
	      ah_attr->grh.sgid_attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP &&
	      ah_attr->grh.flow_label))
		वापस शून्य;

	rcu_पढ़ो_lock();
	master = rdma_पढ़ो_gid_attr_ndev_rcu(ah_attr->grh.sgid_attr);
	अगर (IS_ERR(master)) अणु
		rcu_पढ़ो_unlock();
		वापस master;
	पूर्ण
	dev_hold(master);
	rcu_पढ़ो_unlock();

	अगर (!netअगर_is_bond_master(master))
		जाओ put;

	slave = rdma_get_xmit_slave_udp(device, master, ah_attr, flags);
put:
	dev_put(master);
	वापस slave;
पूर्ण
