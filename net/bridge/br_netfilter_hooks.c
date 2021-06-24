<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Handle firewalling
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *	Bart De Schuymer		<bdschuym@panकरोra.be>
 *
 *	Lennert dedicates this file to Kerstin Wurdinger.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <uapi/linux/netfilter_bridge.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_arp.h>
#समावेश <linux/in_route.h>
#समावेश <linux/rculist.h>
#समावेश <linux/inetdevice.h>

#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/route.h>
#समावेश <net/netfilter/br_netfilter.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/uaccess.h>
#समावेश "br_private.h"
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक brnf_net_id __पढ़ो_mostly;

काष्ठा brnf_net अणु
	bool enabled;

#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header *ctl_hdr;
#पूर्ण_अगर

	/* शेष value is 1 */
	पूर्णांक call_iptables;
	पूर्णांक call_ip6tables;
	पूर्णांक call_arptables;

	/* शेष value is 0 */
	पूर्णांक filter_vlan_tagged;
	पूर्णांक filter_pppoe_tagged;
	पूर्णांक pass_vlan_indev;
पूर्ण;

#घोषणा IS_IP(skb) \
	(!skb_vlan_tag_present(skb) && skb->protocol == htons(ETH_P_IP))

#घोषणा IS_IPV6(skb) \
	(!skb_vlan_tag_present(skb) && skb->protocol == htons(ETH_P_IPV6))

#घोषणा IS_ARP(skb) \
	(!skb_vlan_tag_present(skb) && skb->protocol == htons(ETH_P_ARP))

अटल अंतरभूत __be16 vlan_proto(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb_vlan_tag_present(skb))
		वापस skb->protocol;
	अन्यथा अगर (skb->protocol == htons(ETH_P_8021Q))
		वापस vlan_eth_hdr(skb)->h_vlan_encapsulated_proto;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत bool is_vlan_ip(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net *net)
अणु
	काष्ठा brnf_net *brnet = net_generic(net, brnf_net_id);

	वापस vlan_proto(skb) == htons(ETH_P_IP) && brnet->filter_vlan_tagged;
पूर्ण

अटल अंतरभूत bool is_vlan_ipv6(स्थिर काष्ठा sk_buff *skb,
				स्थिर काष्ठा net *net)
अणु
	काष्ठा brnf_net *brnet = net_generic(net, brnf_net_id);

	वापस vlan_proto(skb) == htons(ETH_P_IPV6) &&
	       brnet->filter_vlan_tagged;
पूर्ण

अटल अंतरभूत bool is_vlan_arp(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net *net)
अणु
	काष्ठा brnf_net *brnet = net_generic(net, brnf_net_id);

	वापस vlan_proto(skb) == htons(ETH_P_ARP) && brnet->filter_vlan_tagged;
पूर्ण

अटल अंतरभूत __be16 pppoe_proto(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस *((__be16 *)(skb_mac_header(skb) + ETH_HLEN +
			    माप(काष्ठा pppoe_hdr)));
पूर्ण

अटल अंतरभूत bool is_pppoe_ip(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net *net)
अणु
	काष्ठा brnf_net *brnet = net_generic(net, brnf_net_id);

	वापस skb->protocol == htons(ETH_P_PPP_SES) &&
	       pppoe_proto(skb) == htons(PPP_IP) && brnet->filter_pppoe_tagged;
पूर्ण

अटल अंतरभूत bool is_pppoe_ipv6(स्थिर काष्ठा sk_buff *skb,
				 स्थिर काष्ठा net *net)
अणु
	काष्ठा brnf_net *brnet = net_generic(net, brnf_net_id);

	वापस skb->protocol == htons(ETH_P_PPP_SES) &&
	       pppoe_proto(skb) == htons(PPP_IPV6) &&
	       brnet->filter_pppoe_tagged;
पूर्ण

/* largest possible L2 header, see br_nf_dev_queue_xmit() */
#घोषणा NF_BRIDGE_MAX_MAC_HEADER_LENGTH (PPPOE_SES_HLEN + ETH_HLEN)

काष्ठा brnf_frag_data अणु
	अक्षर mac[NF_BRIDGE_MAX_MAC_HEADER_LENGTH];
	u8 encap_size;
	u8 size;
	u16 vlan_tci;
	__be16 vlan_proto;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा brnf_frag_data, brnf_frag_data_storage);

अटल व्योम nf_bridge_info_मुक्त(काष्ठा sk_buff *skb)
अणु
	skb_ext_del(skb, SKB_EXT_BRIDGE_NF);
पूर्ण

अटल अंतरभूत काष्ठा net_device *bridge_parent(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *port;

	port = br_port_get_rcu(dev);
	वापस port ? port->br->dev : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा nf_bridge_info *nf_bridge_unshare(काष्ठा sk_buff *skb)
अणु
	वापस skb_ext_add(skb, SKB_EXT_BRIDGE_NF);
पूर्ण

अचिन्हित पूर्णांक nf_bridge_encap_header_len(स्थिर काष्ठा sk_buff *skb)
अणु
	चयन (skb->protocol) अणु
	हाल __cpu_to_be16(ETH_P_8021Q):
		वापस VLAN_HLEN;
	हाल __cpu_to_be16(ETH_P_PPP_SES):
		वापस PPPOE_SES_HLEN;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nf_bridge_pull_encap_header(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = nf_bridge_encap_header_len(skb);

	skb_pull(skb, len);
	skb->network_header += len;
पूर्ण

अटल अंतरभूत व्योम nf_bridge_pull_encap_header_rcsum(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = nf_bridge_encap_header_len(skb);

	skb_pull_rcsum(skb, len);
	skb->network_header += len;
पूर्ण

/* When handing a packet over to the IP layer
 * check whether we have a skb that is in the
 * expected क्रमmat
 */

अटल पूर्णांक br_validate_ipv4(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph;
	u32 len;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ inhdr_error;

	iph = ip_hdr(skb);

	/* Basic sanity checks */
	अगर (iph->ihl < 5 || iph->version != 4)
		जाओ inhdr_error;

	अगर (!pskb_may_pull(skb, iph->ihl*4))
		जाओ inhdr_error;

	iph = ip_hdr(skb);
	अगर (unlikely(ip_fast_csum((u8 *)iph, iph->ihl)))
		जाओ csum_error;

	len = ntohs(iph->tot_len);
	अगर (skb->len < len) अणु
		__IP_INC_STATS(net, IPSTATS_MIB_INTRUNCATEDPKTS);
		जाओ drop;
	पूर्ण अन्यथा अगर (len < (iph->ihl*4))
		जाओ inhdr_error;

	अगर (pskb_trim_rcsum(skb, len)) अणु
		__IP_INC_STATS(net, IPSTATS_MIB_INDISCARDS);
		जाओ drop;
	पूर्ण

	स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
	/* We should really parse IP options here but until
	 * somebody who actually uses IP options complains to
	 * us we'll just silently ignore the options because
	 * we're lazy!
	 */
	वापस 0;

csum_error:
	__IP_INC_STATS(net, IPSTATS_MIB_CSUMERRORS);
inhdr_error:
	__IP_INC_STATS(net, IPSTATS_MIB_INHDRERRORS);
drop:
	वापस -1;
पूर्ण

व्योम nf_bridge_update_protocol(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	चयन (nf_bridge->orig_proto) अणु
	हाल BRNF_PROTO_8021Q:
		skb->protocol = htons(ETH_P_8021Q);
		अवरोध;
	हाल BRNF_PROTO_PPPOE:
		skb->protocol = htons(ETH_P_PPP_SES);
		अवरोध;
	हाल BRNF_PROTO_UNCHANGED:
		अवरोध;
	पूर्ण
पूर्ण

/* Obtain the correct destination MAC address, जबतक preserving the original
 * source MAC address. If we alपढ़ोy know this address, we just copy it. If we
 * करोn't, we use the neighbour framework to find out. In both हालs, we make
 * sure that br_handle_frame_finish() is called afterwards.
 */
पूर्णांक br_nf_pre_routing_finish_bridge(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा neighbour *neigh;
	काष्ठा dst_entry *dst;

	skb->dev = bridge_parent(skb->dev);
	अगर (!skb->dev)
		जाओ मुक्त_skb;
	dst = skb_dst(skb);
	neigh = dst_neigh_lookup_skb(dst, skb);
	अगर (neigh) अणु
		काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
		पूर्णांक ret;

		अगर ((neigh->nud_state & NUD_CONNECTED) && neigh->hh.hh_len) अणु
			neigh_hh_bridge(&neigh->hh, skb);
			skb->dev = nf_bridge->physindev;
			ret = br_handle_frame_finish(net, sk, skb);
		पूर्ण अन्यथा अणु
			/* the neighbour function below overग_लिखोs the complete
			 * MAC header, so we save the Ethernet source address and
			 * protocol number.
			 */
			skb_copy_from_linear_data_offset(skb,
							 -(ETH_HLEN-ETH_ALEN),
							 nf_bridge->neigh_header,
							 ETH_HLEN-ETH_ALEN);
			/* tell br_dev_xmit to जारी with क्रमwarding */
			nf_bridge->bridged_dnat = 1;
			/* FIXME Need to refragment */
			ret = neigh->output(neigh, skb);
		पूर्ण
		neigh_release(neigh);
		वापस ret;
	पूर्ण
मुक्त_skb:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल अंतरभूत bool
br_nf_ipv4_daddr_was_changed(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा nf_bridge_info *nf_bridge)
अणु
	वापस ip_hdr(skb)->daddr != nf_bridge->ipv4_daddr;
पूर्ण

/* This requires some explaining. If DNAT has taken place,
 * we will need to fix up the destination Ethernet address.
 * This is also true when SNAT takes place (क्रम the reply direction).
 *
 * There are two हालs to consider:
 * 1. The packet was DNAT'ed to a device in the same bridge
 *    port group as it was received on. We can still bridge
 *    the packet.
 * 2. The packet was DNAT'ed to a dअगरferent device, either
 *    a non-bridged device or another bridge port group.
 *    The packet will need to be routed.
 *
 * The correct way of distinguishing between these two हालs is to
 * call ip_route_input() and to look at skb->dst->dev, which is
 * changed to the destination device अगर ip_route_input() succeeds.
 *
 * Let's first consider the हाल that ip_route_input() succeeds:
 *
 * If the output device equals the logical bridge device the packet
 * came in on, we can consider this bridging. The corresponding MAC
 * address will be obtained in br_nf_pre_routing_finish_bridge.
 * Otherwise, the packet is considered to be routed and we just
 * change the destination MAC address so that the packet will
 * later be passed up to the IP stack to be routed. For a redirected
 * packet, ip_route_input() will give back the localhost as output device,
 * which dअगरfers from the bridge device.
 *
 * Let's now consider the हाल that ip_route_input() fails:
 *
 * This can be because the destination address is martian, in which हाल
 * the packet will be dropped.
 * If IP क्रमwarding is disabled, ip_route_input() will fail, जबतक
 * ip_route_output_key() can वापस success. The source
 * address क्रम ip_route_output_key() is set to zero, so ip_route_output_key()
 * thinks we're handling a locally generated packet and won't care
 * अगर IP क्रमwarding is enabled. If the output device equals the logical bridge
 * device, we proceed as अगर ip_route_input() succeeded. If it dअगरfers from the
 * logical bridge port or अगर ip_route_output_key() fails we drop the packet.
 */
अटल पूर्णांक br_nf_pre_routing_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	काष्ठा rtable *rt;
	पूर्णांक err;

	nf_bridge->frag_max_size = IPCB(skb)->frag_max_size;

	अगर (nf_bridge->pkt_otherhost) अणु
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->pkt_otherhost = false;
	पूर्ण
	nf_bridge->in_prerouting = 0;
	अगर (br_nf_ipv4_daddr_was_changed(skb, nf_bridge)) अणु
		अगर ((err = ip_route_input(skb, iph->daddr, iph->saddr, iph->tos, dev))) अणु
			काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);

			/* If err equals -EHOSTUNREACH the error is due to a
			 * martian destination or due to the fact that
			 * क्रमwarding is disabled. For most martian packets,
			 * ip_route_output_key() will fail. It won't fail क्रम 2 types of
			 * martian destinations: loopback destinations and destination
			 * 0.0.0.0. In both हालs the packet will be dropped because the
			 * destination is the loopback device and not the bridge. */
			अगर (err != -EHOSTUNREACH || !in_dev || IN_DEV_FORWARD(in_dev))
				जाओ मुक्त_skb;

			rt = ip_route_output(net, iph->daddr, 0,
					     RT_TOS(iph->tos), 0);
			अगर (!IS_ERR(rt)) अणु
				/* - Bridged-and-DNAT'ed traffic doesn't
				 *   require ip_क्रमwarding. */
				अगर (rt->dst.dev == dev) अणु
					skb_dst_set(skb, &rt->dst);
					जाओ bridged_dnat;
				पूर्ण
				ip_rt_put(rt);
			पूर्ण
मुक्त_skb:
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण अन्यथा अणु
			अगर (skb_dst(skb)->dev == dev) अणु
bridged_dnat:
				skb->dev = nf_bridge->physindev;
				nf_bridge_update_protocol(skb);
				nf_bridge_push_encap_header(skb);
				br_nf_hook_thresh(NF_BR_PRE_ROUTING,
						  net, sk, skb, skb->dev,
						  शून्य,
						  br_nf_pre_routing_finish_bridge);
				वापस 0;
			पूर्ण
			ether_addr_copy(eth_hdr(skb)->h_dest, dev->dev_addr);
			skb->pkt_type = PACKET_HOST;
		पूर्ण
	पूर्ण अन्यथा अणु
		rt = bridge_parent_rtable(nf_bridge->physindev);
		अगर (!rt) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
		skb_dst_set_noref(skb, &rt->dst);
	पूर्ण

	skb->dev = nf_bridge->physindev;
	nf_bridge_update_protocol(skb);
	nf_bridge_push_encap_header(skb);
	br_nf_hook_thresh(NF_BR_PRE_ROUTING, net, sk, skb, skb->dev, शून्य,
			  br_handle_frame_finish);
	वापस 0;
पूर्ण

अटल काष्ठा net_device *brnf_get_logical_dev(काष्ठा sk_buff *skb,
					       स्थिर काष्ठा net_device *dev,
					       स्थिर काष्ठा net *net)
अणु
	काष्ठा net_device *vlan, *br;
	काष्ठा brnf_net *brnet = net_generic(net, brnf_net_id);

	br = bridge_parent(dev);

	अगर (brnet->pass_vlan_indev == 0 || !skb_vlan_tag_present(skb))
		वापस br;

	vlan = __vlan_find_dev_deep_rcu(br, skb->vlan_proto,
				    skb_vlan_tag_get(skb) & VLAN_VID_MASK);

	वापस vlan ? vlan : br;
पूर्ण

/* Some common code क्रम IPv4/IPv6 */
काष्ठा net_device *setup_pre_routing(काष्ठा sk_buff *skb, स्थिर काष्ठा net *net)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	अगर (skb->pkt_type == PACKET_OTHERHOST) अणु
		skb->pkt_type = PACKET_HOST;
		nf_bridge->pkt_otherhost = true;
	पूर्ण

	nf_bridge->in_prerouting = 1;
	nf_bridge->physindev = skb->dev;
	skb->dev = brnf_get_logical_dev(skb, skb->dev, net);

	अगर (skb->protocol == htons(ETH_P_8021Q))
		nf_bridge->orig_proto = BRNF_PROTO_8021Q;
	अन्यथा अगर (skb->protocol == htons(ETH_P_PPP_SES))
		nf_bridge->orig_proto = BRNF_PROTO_PPPOE;

	/* Must drop socket now because of tproxy. */
	skb_orphan(skb);
	वापस skb->dev;
पूर्ण

/* Direct IPv6 traffic to br_nf_pre_routing_ipv6.
 * Replicate the checks that IPv4 करोes on packet reception.
 * Set skb->dev to the bridge device (i.e. parent of the
 * receiving device) to make netfilter happy, the REसूचीECT
 * target in particular.  Save the original destination IP
 * address to be able to detect DNAT afterwards. */
अटल अचिन्हित पूर्णांक br_nf_pre_routing(व्योम *priv,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_bridge_info *nf_bridge;
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge *br;
	__u32 len = nf_bridge_encap_header_len(skb);
	काष्ठा brnf_net *brnet;

	अगर (unlikely(!pskb_may_pull(skb, len)))
		वापस NF_DROP;

	p = br_port_get_rcu(state->in);
	अगर (p == शून्य)
		वापस NF_DROP;
	br = p->br;

	brnet = net_generic(state->net, brnf_net_id);
	अगर (IS_IPV6(skb) || is_vlan_ipv6(skb, state->net) ||
	    is_pppoe_ipv6(skb, state->net)) अणु
		अगर (!brnet->call_ip6tables &&
		    !br_opt_get(br, BROPT_NF_CALL_IP6TABLES))
			वापस NF_ACCEPT;
		अगर (!ipv6_mod_enabled()) अणु
			pr_warn_once("Module ipv6 is disabled, so call_ip6tables is not supported.");
			वापस NF_DROP;
		पूर्ण

		nf_bridge_pull_encap_header_rcsum(skb);
		वापस br_nf_pre_routing_ipv6(priv, skb, state);
	पूर्ण

	अगर (!brnet->call_iptables && !br_opt_get(br, BROPT_NF_CALL_IPTABLES))
		वापस NF_ACCEPT;

	अगर (!IS_IP(skb) && !is_vlan_ip(skb, state->net) &&
	    !is_pppoe_ip(skb, state->net))
		वापस NF_ACCEPT;

	nf_bridge_pull_encap_header_rcsum(skb);

	अगर (br_validate_ipv4(state->net, skb))
		वापस NF_DROP;

	अगर (!nf_bridge_alloc(skb))
		वापस NF_DROP;
	अगर (!setup_pre_routing(skb, state->net))
		वापस NF_DROP;

	nf_bridge = nf_bridge_info_get(skb);
	nf_bridge->ipv4_daddr = ip_hdr(skb)->daddr;

	skb->protocol = htons(ETH_P_IP);
	skb->transport_header = skb->network_header + ip_hdr(skb)->ihl * 4;

	NF_HOOK(NFPROTO_IPV4, NF_INET_PRE_ROUTING, state->net, state->sk, skb,
		skb->dev, शून्य,
		br_nf_pre_routing_finish);

	वापस NF_STOLEN;
पूर्ण


/* PF_BRIDGE/FORWARD *************************************************/
अटल पूर्णांक br_nf_क्रमward_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	काष्ठा net_device *in;

	अगर (!IS_ARP(skb) && !is_vlan_arp(skb, net)) अणु

		अगर (skb->protocol == htons(ETH_P_IP))
			nf_bridge->frag_max_size = IPCB(skb)->frag_max_size;

		अगर (skb->protocol == htons(ETH_P_IPV6))
			nf_bridge->frag_max_size = IP6CB(skb)->frag_max_size;

		in = nf_bridge->physindev;
		अगर (nf_bridge->pkt_otherhost) अणु
			skb->pkt_type = PACKET_OTHERHOST;
			nf_bridge->pkt_otherhost = false;
		पूर्ण
		nf_bridge_update_protocol(skb);
	पूर्ण अन्यथा अणु
		in = *((काष्ठा net_device **)(skb->cb));
	पूर्ण
	nf_bridge_push_encap_header(skb);

	br_nf_hook_thresh(NF_BR_FORWARD, net, sk, skb, in, skb->dev,
			  br_क्रमward_finish);
	वापस 0;
पूर्ण


/* This is the 'purely bridged' हाल.  For IP, we pass the packet to
 * netfilter with indev and outdev set to the bridge device,
 * but we are still able to filter on the 'real' indev/outdev
 * because of the physdev module. For ARP, indev and outdev are the
 * bridge ports. */
अटल अचिन्हित पूर्णांक br_nf_क्रमward_ip(व्योम *priv,
				     काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_bridge_info *nf_bridge;
	काष्ठा net_device *parent;
	u_पूर्णांक8_t pf;

	nf_bridge = nf_bridge_info_get(skb);
	अगर (!nf_bridge)
		वापस NF_ACCEPT;

	/* Need exclusive nf_bridge_info since we might have multiple
	 * dअगरferent physoutdevs. */
	अगर (!nf_bridge_unshare(skb))
		वापस NF_DROP;

	nf_bridge = nf_bridge_info_get(skb);
	अगर (!nf_bridge)
		वापस NF_DROP;

	parent = bridge_parent(state->out);
	अगर (!parent)
		वापस NF_DROP;

	अगर (IS_IP(skb) || is_vlan_ip(skb, state->net) ||
	    is_pppoe_ip(skb, state->net))
		pf = NFPROTO_IPV4;
	अन्यथा अगर (IS_IPV6(skb) || is_vlan_ipv6(skb, state->net) ||
		 is_pppoe_ipv6(skb, state->net))
		pf = NFPROTO_IPV6;
	अन्यथा
		वापस NF_ACCEPT;

	nf_bridge_pull_encap_header(skb);

	अगर (skb->pkt_type == PACKET_OTHERHOST) अणु
		skb->pkt_type = PACKET_HOST;
		nf_bridge->pkt_otherhost = true;
	पूर्ण

	अगर (pf == NFPROTO_IPV4) अणु
		अगर (br_validate_ipv4(state->net, skb))
			वापस NF_DROP;
		IPCB(skb)->frag_max_size = nf_bridge->frag_max_size;
	पूर्ण

	अगर (pf == NFPROTO_IPV6) अणु
		अगर (br_validate_ipv6(state->net, skb))
			वापस NF_DROP;
		IP6CB(skb)->frag_max_size = nf_bridge->frag_max_size;
	पूर्ण

	nf_bridge->physoutdev = skb->dev;
	अगर (pf == NFPROTO_IPV4)
		skb->protocol = htons(ETH_P_IP);
	अन्यथा
		skb->protocol = htons(ETH_P_IPV6);

	NF_HOOK(pf, NF_INET_FORWARD, state->net, शून्य, skb,
		brnf_get_logical_dev(skb, state->in, state->net),
		parent,	br_nf_क्रमward_finish);

	वापस NF_STOLEN;
पूर्ण

अटल अचिन्हित पूर्णांक br_nf_क्रमward_arp(व्योम *priv,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge *br;
	काष्ठा net_device **d = (काष्ठा net_device **)(skb->cb);
	काष्ठा brnf_net *brnet;

	p = br_port_get_rcu(state->out);
	अगर (p == शून्य)
		वापस NF_ACCEPT;
	br = p->br;

	brnet = net_generic(state->net, brnf_net_id);
	अगर (!brnet->call_arptables && !br_opt_get(br, BROPT_NF_CALL_ARPTABLES))
		वापस NF_ACCEPT;

	अगर (!IS_ARP(skb)) अणु
		अगर (!is_vlan_arp(skb, state->net))
			वापस NF_ACCEPT;
		nf_bridge_pull_encap_header(skb);
	पूर्ण

	अगर (unlikely(!pskb_may_pull(skb, माप(काष्ठा arphdr))))
		वापस NF_DROP;

	अगर (arp_hdr(skb)->ar_pln != 4) अणु
		अगर (is_vlan_arp(skb, state->net))
			nf_bridge_push_encap_header(skb);
		वापस NF_ACCEPT;
	पूर्ण
	*d = state->in;
	NF_HOOK(NFPROTO_ARP, NF_ARP_FORWARD, state->net, state->sk, skb,
		state->in, state->out, br_nf_क्रमward_finish);

	वापस NF_STOLEN;
पूर्ण

अटल पूर्णांक br_nf_push_frag_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा brnf_frag_data *data;
	पूर्णांक err;

	data = this_cpu_ptr(&brnf_frag_data_storage);
	err = skb_cow_head(skb, data->size);

	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (data->vlan_proto)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto, data->vlan_tci);

	skb_copy_to_linear_data_offset(skb, -data->size, data->mac, data->size);
	__skb_push(skb, data->encap_size);

	nf_bridge_info_मुक्त(skb);
	वापस br_dev_queue_push_xmit(net, sk, skb);
पूर्ण

अटल पूर्णांक
br_nf_ip_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		  पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	अचिन्हित पूर्णांक mtu = ip_skb_dst_mtu(sk, skb);
	काष्ठा iphdr *iph = ip_hdr(skb);

	अगर (unlikely(((iph->frag_off & htons(IP_DF)) && !skb->ignore_df) ||
		     (IPCB(skb)->frag_max_size &&
		      IPCB(skb)->frag_max_size > mtu))) अणु
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	वापस ip_करो_fragment(net, sk, skb, output);
पूर्ण

अटल अचिन्हित पूर्णांक nf_bridge_mtu_reduction(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	अगर (nf_bridge->orig_proto == BRNF_PROTO_PPPOE)
		वापस PPPOE_SES_HLEN;
	वापस 0;
पूर्ण

अटल पूर्णांक br_nf_dev_queue_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	अचिन्हित पूर्णांक mtu, mtu_reserved;

	mtu_reserved = nf_bridge_mtu_reduction(skb);
	mtu = skb->dev->mtu;

	अगर (nf_bridge->pkt_otherhost) अणु
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->pkt_otherhost = false;
	पूर्ण

	अगर (nf_bridge->frag_max_size && nf_bridge->frag_max_size < mtu)
		mtu = nf_bridge->frag_max_size;

	अगर (skb_is_gso(skb) || skb->len + mtu_reserved <= mtu) अणु
		nf_bridge_info_मुक्त(skb);
		वापस br_dev_queue_push_xmit(net, sk, skb);
	पूर्ण

	/* This is wrong! We should preserve the original fragment
	 * boundaries by preserving frag_list rather than refragmenting.
	 */
	अगर (IS_ENABLED(CONFIG_NF_DEFRAG_IPV4) &&
	    skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा brnf_frag_data *data;

		अगर (br_validate_ipv4(net, skb))
			जाओ drop;

		IPCB(skb)->frag_max_size = nf_bridge->frag_max_size;

		nf_bridge_update_protocol(skb);

		data = this_cpu_ptr(&brnf_frag_data_storage);

		अगर (skb_vlan_tag_present(skb)) अणु
			data->vlan_tci = skb->vlan_tci;
			data->vlan_proto = skb->vlan_proto;
		पूर्ण अन्यथा अणु
			data->vlan_proto = 0;
		पूर्ण

		data->encap_size = nf_bridge_encap_header_len(skb);
		data->size = ETH_HLEN + data->encap_size;

		skb_copy_from_linear_data_offset(skb, -data->size, data->mac,
						 data->size);

		वापस br_nf_ip_fragment(net, sk, skb, br_nf_push_frag_xmit);
	पूर्ण
	अगर (IS_ENABLED(CONFIG_NF_DEFRAG_IPV6) &&
	    skb->protocol == htons(ETH_P_IPV6)) अणु
		स्थिर काष्ठा nf_ipv6_ops *v6ops = nf_get_ipv6_ops();
		काष्ठा brnf_frag_data *data;

		अगर (br_validate_ipv6(net, skb))
			जाओ drop;

		IP6CB(skb)->frag_max_size = nf_bridge->frag_max_size;

		nf_bridge_update_protocol(skb);

		data = this_cpu_ptr(&brnf_frag_data_storage);
		data->encap_size = nf_bridge_encap_header_len(skb);
		data->size = ETH_HLEN + data->encap_size;

		skb_copy_from_linear_data_offset(skb, -data->size, data->mac,
						 data->size);

		अगर (v6ops)
			वापस v6ops->fragment(net, sk, skb, br_nf_push_frag_xmit);

		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण
	nf_bridge_info_मुक्त(skb);
	वापस br_dev_queue_push_xmit(net, sk, skb);
 drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* PF_BRIDGE/POST_ROUTING ********************************************/
अटल अचिन्हित पूर्णांक br_nf_post_routing(व्योम *priv,
				       काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	काष्ठा net_device *realoutdev = bridge_parent(skb->dev);
	u_पूर्णांक8_t pf;

	/* अगर nf_bridge is set, but ->physoutdev is शून्य, this packet came in
	 * on a bridge, but was delivered locally and is now being routed:
	 *
	 * POST_ROUTING was alपढ़ोy invoked from the ip stack.
	 */
	अगर (!nf_bridge || !nf_bridge->physoutdev)
		वापस NF_ACCEPT;

	अगर (!realoutdev)
		वापस NF_DROP;

	अगर (IS_IP(skb) || is_vlan_ip(skb, state->net) ||
	    is_pppoe_ip(skb, state->net))
		pf = NFPROTO_IPV4;
	अन्यथा अगर (IS_IPV6(skb) || is_vlan_ipv6(skb, state->net) ||
		 is_pppoe_ipv6(skb, state->net))
		pf = NFPROTO_IPV6;
	अन्यथा
		वापस NF_ACCEPT;

	अगर (skb->pkt_type == PACKET_OTHERHOST) अणु
		skb->pkt_type = PACKET_HOST;
		nf_bridge->pkt_otherhost = true;
	पूर्ण

	nf_bridge_pull_encap_header(skb);
	अगर (pf == NFPROTO_IPV4)
		skb->protocol = htons(ETH_P_IP);
	अन्यथा
		skb->protocol = htons(ETH_P_IPV6);

	NF_HOOK(pf, NF_INET_POST_ROUTING, state->net, state->sk, skb,
		शून्य, realoutdev,
		br_nf_dev_queue_xmit);

	वापस NF_STOLEN;
पूर्ण

/* IP/SABOTAGE *****************************************************/
/* Don't hand locally destined packets to PF_INET(6)/PRE_ROUTING
 * क्रम the second समय. */
अटल अचिन्हित पूर्णांक ip_sabotage_in(व्योम *priv,
				   काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	अगर (nf_bridge && !nf_bridge->in_prerouting &&
	    !netअगर_is_l3_master(skb->dev) &&
	    !netअगर_is_l3_slave(skb->dev)) अणु
		state->okfn(state->net, state->sk, skb);
		वापस NF_STOLEN;
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

/* This is called when br_netfilter has called पूर्णांकo iptables/netfilter,
 * and DNAT has taken place on a bridge-क्रमwarded packet.
 *
 * neigh->output has created a new MAC header, with local br0 MAC
 * as saddr.
 *
 * This restores the original MAC saddr of the bridged packet
 * beक्रमe invoking bridge क्रमward logic to transmit the packet.
 */
अटल व्योम br_nf_pre_routing_finish_bridge_slow(काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	skb_pull(skb, ETH_HLEN);
	nf_bridge->bridged_dnat = 0;

	BUILD_BUG_ON(माप(nf_bridge->neigh_header) != (ETH_HLEN - ETH_ALEN));

	skb_copy_to_linear_data_offset(skb, -(ETH_HLEN - ETH_ALEN),
				       nf_bridge->neigh_header,
				       ETH_HLEN - ETH_ALEN);
	skb->dev = nf_bridge->physindev;

	nf_bridge->physoutdev = शून्य;
	br_handle_frame_finish(dev_net(skb->dev), शून्य, skb);
पूर्ण

अटल पूर्णांक br_nf_dev_xmit(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	अगर (nf_bridge && nf_bridge->bridged_dnat) अणु
		br_nf_pre_routing_finish_bridge_slow(skb);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nf_br_ops br_ops = अणु
	.br_dev_xmit_hook =	br_nf_dev_xmit,
पूर्ण;

/* For br_nf_post_routing, we need (prio = NF_BR_PRI_LAST), because
 * br_dev_queue_push_xmit is called afterwards */
अटल स्थिर काष्ठा nf_hook_ops br_nf_ops[] = अणु
	अणु
		.hook = br_nf_pre_routing,
		.pf = NFPROTO_BRIDGE,
		.hooknum = NF_BR_PRE_ROUTING,
		.priority = NF_BR_PRI_BRNF,
	पूर्ण,
	अणु
		.hook = br_nf_क्रमward_ip,
		.pf = NFPROTO_BRIDGE,
		.hooknum = NF_BR_FORWARD,
		.priority = NF_BR_PRI_BRNF - 1,
	पूर्ण,
	अणु
		.hook = br_nf_क्रमward_arp,
		.pf = NFPROTO_BRIDGE,
		.hooknum = NF_BR_FORWARD,
		.priority = NF_BR_PRI_BRNF,
	पूर्ण,
	अणु
		.hook = br_nf_post_routing,
		.pf = NFPROTO_BRIDGE,
		.hooknum = NF_BR_POST_ROUTING,
		.priority = NF_BR_PRI_LAST,
	पूर्ण,
	अणु
		.hook = ip_sabotage_in,
		.pf = NFPROTO_IPV4,
		.hooknum = NF_INET_PRE_ROUTING,
		.priority = NF_IP_PRI_FIRST,
	पूर्ण,
	अणु
		.hook = ip_sabotage_in,
		.pf = NFPROTO_IPV6,
		.hooknum = NF_INET_PRE_ROUTING,
		.priority = NF_IP6_PRI_FIRST,
	पूर्ण,
पूर्ण;

अटल पूर्णांक brnf_device_event(काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा brnf_net *brnet;
	काष्ठा net *net;
	पूर्णांक ret;

	अगर (event != NETDEV_REGISTER || !(dev->priv_flags & IFF_EBRIDGE))
		वापस NOTIFY_DONE;

	ASSERT_RTNL();

	net = dev_net(dev);
	brnet = net_generic(net, brnf_net_id);
	अगर (brnet->enabled)
		वापस NOTIFY_OK;

	ret = nf_रेजिस्टर_net_hooks(net, br_nf_ops, ARRAY_SIZE(br_nf_ops));
	अगर (ret)
		वापस NOTIFY_BAD;

	brnet->enabled = true;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block brnf_notअगरier __पढ़ो_mostly = अणु
	.notअगरier_call = brnf_device_event,
पूर्ण;

/* recursively invokes nf_hook_slow (again), skipping alपढ़ोy-called
 * hooks (< NF_BR_PRI_BRNF).
 *
 * Called with rcu पढ़ो lock held.
 */
पूर्णांक br_nf_hook_thresh(अचिन्हित पूर्णांक hook, काष्ठा net *net,
		      काष्ठा sock *sk, काष्ठा sk_buff *skb,
		      काष्ठा net_device *indev,
		      काष्ठा net_device *outdev,
		      पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *,
				  काष्ठा sk_buff *))
अणु
	स्थिर काष्ठा nf_hook_entries *e;
	काष्ठा nf_hook_state state;
	काष्ठा nf_hook_ops **ops;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	e = rcu_dereference(net->nf.hooks_bridge[hook]);
	अगर (!e)
		वापस okfn(net, sk, skb);

	ops = nf_hook_entries_get_hook_ops(e);
	क्रम (i = 0; i < e->num_hook_entries &&
	      ops[i]->priority <= NF_BR_PRI_BRNF; i++)
		;

	nf_hook_state_init(&state, hook, NFPROTO_BRIDGE, indev, outdev,
			   sk, net, okfn);

	ret = nf_hook_slow(skb, &state, e, i);
	अगर (ret == 1)
		ret = okfn(net, sk, skb);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल
पूर्णांक brnf_sysctl_call_tables(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && *(पूर्णांक *)(ctl->data))
		*(पूर्णांक *)(ctl->data) = 1;
	वापस ret;
पूर्ण

अटल काष्ठा ctl_table brnf_table[] = अणु
	अणु
		.procname	= "bridge-nf-call-arptables",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= brnf_sysctl_call_tables,
	पूर्ण,
	अणु
		.procname	= "bridge-nf-call-iptables",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= brnf_sysctl_call_tables,
	पूर्ण,
	अणु
		.procname	= "bridge-nf-call-ip6tables",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= brnf_sysctl_call_tables,
	पूर्ण,
	अणु
		.procname	= "bridge-nf-filter-vlan-tagged",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= brnf_sysctl_call_tables,
	पूर्ण,
	अणु
		.procname	= "bridge-nf-filter-pppoe-tagged",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= brnf_sysctl_call_tables,
	पूर्ण,
	अणु
		.procname	= "bridge-nf-pass-vlan-input-dev",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= brnf_sysctl_call_tables,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल अंतरभूत व्योम br_netfilter_sysctl_शेष(काष्ठा brnf_net *brnf)
अणु
	brnf->call_iptables = 1;
	brnf->call_ip6tables = 1;
	brnf->call_arptables = 1;
	brnf->filter_vlan_tagged = 0;
	brnf->filter_pppoe_tagged = 0;
	brnf->pass_vlan_indev = 0;
पूर्ण

अटल पूर्णांक br_netfilter_sysctl_init_net(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table = brnf_table;
	काष्ठा brnf_net *brnet;

	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(brnf_table), GFP_KERNEL);
		अगर (!table)
			वापस -ENOMEM;
	पूर्ण

	brnet = net_generic(net, brnf_net_id);
	table[0].data = &brnet->call_arptables;
	table[1].data = &brnet->call_iptables;
	table[2].data = &brnet->call_ip6tables;
	table[3].data = &brnet->filter_vlan_tagged;
	table[4].data = &brnet->filter_pppoe_tagged;
	table[5].data = &brnet->pass_vlan_indev;

	br_netfilter_sysctl_शेष(brnet);

	brnet->ctl_hdr = रेजिस्टर_net_sysctl(net, "net/bridge", table);
	अगर (!brnet->ctl_hdr) अणु
		अगर (!net_eq(net, &init_net))
			kमुक्त(table);

		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम br_netfilter_sysctl_निकास_net(काष्ठा net *net,
					 काष्ठा brnf_net *brnet)
अणु
	काष्ठा ctl_table *table = brnet->ctl_hdr->ctl_table_arg;

	unरेजिस्टर_net_sysctl_table(brnet->ctl_hdr);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
पूर्ण

अटल पूर्णांक __net_init brnf_init_net(काष्ठा net *net)
अणु
	वापस br_netfilter_sysctl_init_net(net);
पूर्ण
#पूर्ण_अगर

अटल व्योम __net_निकास brnf_निकास_net(काष्ठा net *net)
अणु
	काष्ठा brnf_net *brnet;

	brnet = net_generic(net, brnf_net_id);
	अगर (brnet->enabled) अणु
		nf_unरेजिस्टर_net_hooks(net, br_nf_ops, ARRAY_SIZE(br_nf_ops));
		brnet->enabled = false;
	पूर्ण

#अगर_घोषित CONFIG_SYSCTL
	br_netfilter_sysctl_निकास_net(net, brnet);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा pernet_operations brnf_net_ops __पढ़ो_mostly = अणु
#अगर_घोषित CONFIG_SYSCTL
	.init = brnf_init_net,
#पूर्ण_अगर
	.निकास = brnf_निकास_net,
	.id   = &brnf_net_id,
	.size = माप(काष्ठा brnf_net),
पूर्ण;

अटल पूर्णांक __init br_netfilter_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&brnf_net_ops);
	अगर (ret < 0)
		वापस ret;

	ret = रेजिस्टर_netdevice_notअगरier(&brnf_notअगरier);
	अगर (ret < 0) अणु
		unरेजिस्टर_pernet_subsys(&brnf_net_ops);
		वापस ret;
	पूर्ण

	RCU_INIT_POINTER(nf_br_ops, &br_ops);
	prपूर्णांकk(KERN_NOTICE "Bridge firewalling registered\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास br_netfilter_fini(व्योम)
अणु
	RCU_INIT_POINTER(nf_br_ops, शून्य);
	unरेजिस्टर_netdevice_notअगरier(&brnf_notअगरier);
	unरेजिस्टर_pernet_subsys(&brnf_net_ops);
पूर्ण

module_init(br_netfilter_init);
module_निकास(br_netfilter_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lennert Buytenhek <buytenh@gnu.org>");
MODULE_AUTHOR("Bart De Schuymer <bdschuym@pandora.be>");
MODULE_DESCRIPTION("Linux ethernet netfilter firewall bridge");
