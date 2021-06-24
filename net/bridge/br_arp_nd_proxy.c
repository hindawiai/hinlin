<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Handle bridge arp/nd proxy/suppress
 *
 *  Copyright (C) 2017 Cumulus Networks
 *  Copyright (c) 2017 Roopa Prabhu <roopa@cumulusnetworks.com>
 *
 *  Authors:
 *	Roopa Prabhu <roopa@cumulusnetworks.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/neighbour.h>
#समावेश <net/arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6_stubs.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ip6_checksum.h>
#पूर्ण_अगर

#समावेश "br_private.h"

व्योम br_recalculate_neigh_suppress_enabled(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;
	bool neigh_suppress = false;

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (p->flags & BR_NEIGH_SUPPRESS) अणु
			neigh_suppress = true;
			अवरोध;
		पूर्ण
	पूर्ण

	br_opt_toggle(br, BROPT_NEIGH_SUPPRESS_ENABLED, neigh_suppress);
पूर्ण

#अगर IS_ENABLED(CONFIG_INET)
अटल व्योम br_arp_send(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			काष्ठा net_device *dev, __be32 dest_ip, __be32 src_ip,
			स्थिर अचिन्हित अक्षर *dest_hw,
			स्थिर अचिन्हित अक्षर *src_hw,
			स्थिर अचिन्हित अक्षर *target_hw,
			__be16 vlan_proto, u16 vlan_tci)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा sk_buff *skb;
	u16 pvid;

	netdev_dbg(dev, "arp send dev %s dst %pI4 dst_hw %pM src %pI4 src_hw %pM\n",
		   dev->name, &dest_ip, dest_hw, &src_ip, src_hw);

	अगर (!vlan_tci) अणु
		arp_send(ARPOP_REPLY, ETH_P_ARP, dest_ip, dev, src_ip,
			 dest_hw, src_hw, target_hw);
		वापस;
	पूर्ण

	skb = arp_create(ARPOP_REPLY, ETH_P_ARP, dest_ip, dev, src_ip,
			 dest_hw, src_hw, target_hw);
	अगर (!skb)
		वापस;

	अगर (p)
		vg = nbp_vlan_group_rcu(p);
	अन्यथा
		vg = br_vlan_group_rcu(br);
	pvid = br_get_pvid(vg);
	अगर (pvid == (vlan_tci & VLAN_VID_MASK))
		vlan_tci = 0;

	अगर (vlan_tci)
		__vlan_hwaccel_put_tag(skb, vlan_proto, vlan_tci);

	अगर (p) अणु
		arp_xmit(skb);
	पूर्ण अन्यथा अणु
		skb_reset_mac_header(skb);
		__skb_pull(skb, skb_network_offset(skb));
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->pkt_type = PACKET_HOST;

		netअगर_rx_ni(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक br_chk_addr_ip(काष्ठा net_device *dev,
			  काष्ठा netdev_nested_priv *priv)
अणु
	__be32 ip = *(__be32 *)priv->data;
	काष्ठा in_device *in_dev;
	__be32 addr = 0;

	in_dev = __in_dev_get_rcu(dev);
	अगर (in_dev)
		addr = inet_confirm_addr(dev_net(dev), in_dev, 0, ip,
					 RT_SCOPE_HOST);

	अगर (addr == ip)
		वापस 1;

	वापस 0;
पूर्ण

अटल bool br_is_local_ip(काष्ठा net_device *dev, __be32 ip)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)&ip,
	पूर्ण;

	अगर (br_chk_addr_ip(dev, &priv))
		वापस true;

	/* check अगर ip is configured on upper dev */
	अगर (netdev_walk_all_upper_dev_rcu(dev, br_chk_addr_ip, &priv))
		वापस true;

	वापस false;
पूर्ण

व्योम br_करो_proxy_suppress_arp(काष्ठा sk_buff *skb, काष्ठा net_bridge *br,
			      u16 vid, काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_device *dev = br->dev;
	काष्ठा net_device *vlandev = dev;
	काष्ठा neighbour *n;
	काष्ठा arphdr *parp;
	u8 *arpptr, *sha;
	__be32 sip, tip;

	BR_INPUT_SKB_CB(skb)->proxyarp_replied = 0;

	अगर ((dev->flags & IFF_NOARP) ||
	    !pskb_may_pull(skb, arp_hdr_len(dev)))
		वापस;

	parp = arp_hdr(skb);

	अगर (parp->ar_pro != htons(ETH_P_IP) ||
	    parp->ar_hln != dev->addr_len ||
	    parp->ar_pln != 4)
		वापस;

	arpptr = (u8 *)parp + माप(काष्ठा arphdr);
	sha = arpptr;
	arpptr += dev->addr_len;	/* sha */
	स_नकल(&sip, arpptr, माप(sip));
	arpptr += माप(sip);
	arpptr += dev->addr_len;	/* tha */
	स_नकल(&tip, arpptr, माप(tip));

	अगर (ipv4_is_loopback(tip) ||
	    ipv4_is_multicast(tip))
		वापस;

	अगर (br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED)) अणु
		अगर (p && (p->flags & BR_NEIGH_SUPPRESS))
			वापस;
		अगर (parp->ar_op != htons(ARPOP_RREQUEST) &&
		    parp->ar_op != htons(ARPOP_RREPLY) &&
		    (ipv4_is_zeronet(sip) || sip == tip)) अणु
			/* prevent flooding to neigh suppress ports */
			BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
			वापस;
		पूर्ण
	पूर्ण

	अगर (parp->ar_op != htons(ARPOP_REQUEST))
		वापस;

	अगर (vid != 0) अणु
		vlandev = __vlan_find_dev_deep_rcu(br->dev, skb->vlan_proto,
						   vid);
		अगर (!vlandev)
			वापस;
	पूर्ण

	अगर (br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED) &&
	    br_is_local_ip(vlandev, tip)) अणु
		/* its our local ip, so करोn't proxy reply
		 * and करोn't क्रमward to neigh suppress ports
		 */
		BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
		वापस;
	पूर्ण

	n = neigh_lookup(&arp_tbl, &tip, vlandev);
	अगर (n) अणु
		काष्ठा net_bridge_fdb_entry *f;

		अगर (!(n->nud_state & NUD_VALID)) अणु
			neigh_release(n);
			वापस;
		पूर्ण

		f = br_fdb_find_rcu(br, n->ha, vid);
		अगर (f) अणु
			bool replied = false;

			अगर ((p && (p->flags & BR_PROXYARP)) ||
			    (f->dst && (f->dst->flags & (BR_PROXYARP_WIFI |
							 BR_NEIGH_SUPPRESS)))) अणु
				अगर (!vid)
					br_arp_send(br, p, skb->dev, sip, tip,
						    sha, n->ha, sha, 0, 0);
				अन्यथा
					br_arp_send(br, p, skb->dev, sip, tip,
						    sha, n->ha, sha,
						    skb->vlan_proto,
						    skb_vlan_tag_get(skb));
				replied = true;
			पूर्ण

			/* If we have replied or as दीर्घ as we know the
			 * mac, indicate to arp replied
			 */
			अगर (replied ||
			    br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED))
				BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
		पूर्ण

		neigh_release(n);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
काष्ठा nd_msg *br_is_nd_neigh_msg(काष्ठा sk_buff *skb, काष्ठा nd_msg *msg)
अणु
	काष्ठा nd_msg *m;

	m = skb_header_poपूर्णांकer(skb, skb_network_offset(skb) +
			       माप(काष्ठा ipv6hdr), माप(*msg), msg);
	अगर (!m)
		वापस शून्य;

	अगर (m->icmph.icmp6_code != 0 ||
	    (m->icmph.icmp6_type != NDISC_NEIGHBOUR_SOLICITATION &&
	     m->icmph.icmp6_type != NDISC_NEIGHBOUR_ADVERTISEMENT))
		वापस शून्य;

	वापस m;
पूर्ण

अटल व्योम br_nd_send(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
		       काष्ठा sk_buff *request, काष्ठा neighbour *n,
		       __be16 vlan_proto, u16 vlan_tci, काष्ठा nd_msg *ns)
अणु
	काष्ठा net_device *dev = request->dev;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा sk_buff *reply;
	काष्ठा nd_msg *na;
	काष्ठा ipv6hdr *pip6;
	पूर्णांक na_olen = 8; /* opt hdr + ETH_ALEN क्रम target */
	पूर्णांक ns_olen;
	पूर्णांक i, len;
	u8 *daddr;
	u16 pvid;

	अगर (!dev)
		वापस;

	len = LL_RESERVED_SPACE(dev) + माप(काष्ठा ipv6hdr) +
		माप(*na) + na_olen + dev->needed_tailroom;

	reply = alloc_skb(len, GFP_ATOMIC);
	अगर (!reply)
		वापस;

	reply->protocol = htons(ETH_P_IPV6);
	reply->dev = dev;
	skb_reserve(reply, LL_RESERVED_SPACE(dev));
	skb_push(reply, माप(काष्ठा ethhdr));
	skb_set_mac_header(reply, 0);

	daddr = eth_hdr(request)->h_source;

	/* Do we need option processing ? */
	ns_olen = request->len - (skb_network_offset(request) +
				  माप(काष्ठा ipv6hdr)) - माप(*ns);
	क्रम (i = 0; i < ns_olen - 1; i += (ns->opt[i + 1] << 3)) अणु
		अगर (!ns->opt[i + 1]) अणु
			kमुक्त_skb(reply);
			वापस;
		पूर्ण
		अगर (ns->opt[i] == ND_OPT_SOURCE_LL_ADDR) अणु
			daddr = ns->opt + i + माप(काष्ठा nd_opt_hdr);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Ethernet header */
	ether_addr_copy(eth_hdr(reply)->h_dest, daddr);
	ether_addr_copy(eth_hdr(reply)->h_source, n->ha);
	eth_hdr(reply)->h_proto = htons(ETH_P_IPV6);
	reply->protocol = htons(ETH_P_IPV6);

	skb_pull(reply, माप(काष्ठा ethhdr));
	skb_set_network_header(reply, 0);
	skb_put(reply, माप(काष्ठा ipv6hdr));

	/* IPv6 header */
	pip6 = ipv6_hdr(reply);
	स_रखो(pip6, 0, माप(काष्ठा ipv6hdr));
	pip6->version = 6;
	pip6->priority = ipv6_hdr(request)->priority;
	pip6->nexthdr = IPPROTO_ICMPV6;
	pip6->hop_limit = 255;
	pip6->daddr = ipv6_hdr(request)->saddr;
	pip6->saddr = *(काष्ठा in6_addr *)n->primary_key;

	skb_pull(reply, माप(काष्ठा ipv6hdr));
	skb_set_transport_header(reply, 0);

	na = (काष्ठा nd_msg *)skb_put(reply, माप(*na) + na_olen);

	/* Neighbor Advertisement */
	स_रखो(na, 0, माप(*na) + na_olen);
	na->icmph.icmp6_type = NDISC_NEIGHBOUR_ADVERTISEMENT;
	na->icmph.icmp6_router = (n->flags & NTF_ROUTER) ? 1 : 0;
	na->icmph.icmp6_override = 1;
	na->icmph.icmp6_solicited = 1;
	na->target = ns->target;
	ether_addr_copy(&na->opt[2], n->ha);
	na->opt[0] = ND_OPT_TARGET_LL_ADDR;
	na->opt[1] = na_olen >> 3;

	na->icmph.icmp6_cksum = csum_ipv6_magic(&pip6->saddr,
						&pip6->daddr,
						माप(*na) + na_olen,
						IPPROTO_ICMPV6,
						csum_partial(na, माप(*na) + na_olen, 0));

	pip6->payload_len = htons(माप(*na) + na_olen);

	skb_push(reply, माप(काष्ठा ipv6hdr));
	skb_push(reply, माप(काष्ठा ethhdr));

	reply->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (p)
		vg = nbp_vlan_group_rcu(p);
	अन्यथा
		vg = br_vlan_group_rcu(br);
	pvid = br_get_pvid(vg);
	अगर (pvid == (vlan_tci & VLAN_VID_MASK))
		vlan_tci = 0;

	अगर (vlan_tci)
		__vlan_hwaccel_put_tag(reply, vlan_proto, vlan_tci);

	netdev_dbg(dev, "nd send dev %s dst %pI6 dst_hw %pM src %pI6 src_hw %pM\n",
		   dev->name, &pip6->daddr, daddr, &pip6->saddr, n->ha);

	अगर (p) अणु
		dev_queue_xmit(reply);
	पूर्ण अन्यथा अणु
		skb_reset_mac_header(reply);
		__skb_pull(reply, skb_network_offset(reply));
		reply->ip_summed = CHECKSUM_UNNECESSARY;
		reply->pkt_type = PACKET_HOST;

		netअगर_rx_ni(reply);
	पूर्ण
पूर्ण

अटल पूर्णांक br_chk_addr_ip6(काष्ठा net_device *dev,
			   काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा in6_addr *addr = (काष्ठा in6_addr *)priv->data;

	अगर (ipv6_chk_addr(dev_net(dev), addr, dev, 0))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool br_is_local_ip6(काष्ठा net_device *dev, काष्ठा in6_addr *addr)

अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)addr,
	पूर्ण;

	अगर (br_chk_addr_ip6(dev, &priv))
		वापस true;

	/* check अगर ip is configured on upper dev */
	अगर (netdev_walk_all_upper_dev_rcu(dev, br_chk_addr_ip6, &priv))
		वापस true;

	वापस false;
पूर्ण

व्योम br_करो_suppress_nd(काष्ठा sk_buff *skb, काष्ठा net_bridge *br,
		       u16 vid, काष्ठा net_bridge_port *p, काष्ठा nd_msg *msg)
अणु
	काष्ठा net_device *dev = br->dev;
	काष्ठा net_device *vlandev = शून्य;
	काष्ठा in6_addr *saddr, *daddr;
	काष्ठा ipv6hdr *iphdr;
	काष्ठा neighbour *n;

	BR_INPUT_SKB_CB(skb)->proxyarp_replied = 0;

	अगर (p && (p->flags & BR_NEIGH_SUPPRESS))
		वापस;

	अगर (msg->icmph.icmp6_type == NDISC_NEIGHBOUR_ADVERTISEMENT &&
	    !msg->icmph.icmp6_solicited) अणु
		/* prevent flooding to neigh suppress ports */
		BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
		वापस;
	पूर्ण

	अगर (msg->icmph.icmp6_type != NDISC_NEIGHBOUR_SOLICITATION)
		वापस;

	iphdr = ipv6_hdr(skb);
	saddr = &iphdr->saddr;
	daddr = &iphdr->daddr;

	अगर (ipv6_addr_any(saddr) || !ipv6_addr_cmp(saddr, daddr)) अणु
		/* prevent flooding to neigh suppress ports */
		BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
		वापस;
	पूर्ण

	अगर (vid != 0) अणु
		/* build neigh table lookup on the vlan device */
		vlandev = __vlan_find_dev_deep_rcu(br->dev, skb->vlan_proto,
						   vid);
		अगर (!vlandev)
			वापस;
	पूर्ण अन्यथा अणु
		vlandev = dev;
	पूर्ण

	अगर (br_is_local_ip6(vlandev, &msg->target)) अणु
		/* its our own ip, so करोn't proxy reply
		 * and करोn't क्रमward to arp suppress ports
		 */
		BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
		वापस;
	पूर्ण

	n = neigh_lookup(ipv6_stub->nd_tbl, &msg->target, vlandev);
	अगर (n) अणु
		काष्ठा net_bridge_fdb_entry *f;

		अगर (!(n->nud_state & NUD_VALID)) अणु
			neigh_release(n);
			वापस;
		पूर्ण

		f = br_fdb_find_rcu(br, n->ha, vid);
		अगर (f) अणु
			bool replied = false;

			अगर (f->dst && (f->dst->flags & BR_NEIGH_SUPPRESS)) अणु
				अगर (vid != 0)
					br_nd_send(br, p, skb, n,
						   skb->vlan_proto,
						   skb_vlan_tag_get(skb), msg);
				अन्यथा
					br_nd_send(br, p, skb, n, 0, 0, msg);
				replied = true;
			पूर्ण

			/* If we have replied or as दीर्घ as we know the
			 * mac, indicate to NEIGH_SUPPRESS ports that we
			 * have replied
			 */
			अगर (replied ||
			    br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED))
				BR_INPUT_SKB_CB(skb)->proxyarp_replied = 1;
		पूर्ण
		neigh_release(n);
	पूर्ण
पूर्ण
#पूर्ण_अगर
