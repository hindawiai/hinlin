<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Handle incoming frames
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netfilter_bridge.h>
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
#समावेश <net/netfilter/nf_queue.h>
#पूर्ण_अगर
#समावेश <linux/neighbour.h>
#समावेश <net/arp.h>
#समावेश <net/dsa.h>
#समावेश <linux/export.h>
#समावेश <linux/rculist.h>
#समावेश "br_private.h"
#समावेश "br_private_tunnel.h"

अटल पूर्णांक
br_netअगर_receive_skb(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	br_drop_fake_rtable(skb);
	वापस netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक br_pass_frame_up(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *indev, *brdev = BR_INPUT_SKB_CB(skb)->brdev;
	काष्ठा net_bridge *br = netdev_priv(brdev);
	काष्ठा net_bridge_vlan_group *vg;

	dev_sw_netstats_rx_add(brdev, skb->len);

	vg = br_vlan_group_rcu(br);
	/* Bridge is just like any other port.  Make sure the
	 * packet is allowed except in promisc mode when someone
	 * may be running packet capture.
	 */
	अगर (!(brdev->flags & IFF_PROMISC) &&
	    !br_allowed_egress(vg, skb)) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	indev = skb->dev;
	skb->dev = brdev;
	skb = br_handle_vlan(br, शून्य, vg, skb);
	अगर (!skb)
		वापस NET_RX_DROP;
	/* update the multicast stats अगर the packet is IGMP/MLD */
	br_multicast_count(br, शून्य, skb, br_multicast_igmp_type(skb),
			   BR_MCAST_सूची_TX);

	वापस NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_IN,
		       dev_net(indev), शून्य, skb, indev, शून्य,
		       br_netअगर_receive_skb);
पूर्ण

/* note: alपढ़ोy called with rcu_पढ़ो_lock */
पूर्णांक br_handle_frame_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_bridge_port *p = br_port_get_rcu(skb->dev);
	क्रमागत br_pkt_type pkt_type = BR_PKT_UNICAST;
	काष्ठा net_bridge_fdb_entry *dst = शून्य;
	काष्ठा net_bridge_mdb_entry *mdst;
	bool local_rcv, mcast_hit = false;
	काष्ठा net_bridge *br;
	u16 vid = 0;
	u8 state;

	अगर (!p || p->state == BR_STATE_DISABLED)
		जाओ drop;

	state = p->state;
	अगर (!br_allowed_ingress(p->br, nbp_vlan_group_rcu(p), skb, &vid,
				&state))
		जाओ out;

	nbp_चयनdev_frame_mark(p, skb);

	/* insert पूर्णांकo क्रमwarding database after filtering to aव्योम spoofing */
	br = p->br;
	अगर (p->flags & BR_LEARNING)
		br_fdb_update(br, p, eth_hdr(skb)->h_source, vid, 0);

	local_rcv = !!(br->dev->flags & IFF_PROMISC);
	अगर (is_multicast_ether_addr(eth_hdr(skb)->h_dest)) अणु
		/* by definition the broadcast is also a multicast address */
		अगर (is_broadcast_ether_addr(eth_hdr(skb)->h_dest)) अणु
			pkt_type = BR_PKT_BROADCAST;
			local_rcv = true;
		पूर्ण अन्यथा अणु
			pkt_type = BR_PKT_MULTICAST;
			अगर (br_multicast_rcv(br, p, skb, vid))
				जाओ drop;
		पूर्ण
	पूर्ण

	अगर (state == BR_STATE_LEARNING)
		जाओ drop;

	BR_INPUT_SKB_CB(skb)->brdev = br->dev;
	BR_INPUT_SKB_CB(skb)->src_port_isolated = !!(p->flags & BR_ISOLATED);

	अगर (IS_ENABLED(CONFIG_INET) &&
	    (skb->protocol == htons(ETH_P_ARP) ||
	     skb->protocol == htons(ETH_P_RARP))) अणु
		br_करो_proxy_suppress_arp(skb, br, vid, p);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6) &&
		   skb->protocol == htons(ETH_P_IPV6) &&
		   br_opt_get(br, BROPT_NEIGH_SUPPRESS_ENABLED) &&
		   pskb_may_pull(skb, माप(काष्ठा ipv6hdr) +
				 माप(काष्ठा nd_msg)) &&
		   ipv6_hdr(skb)->nexthdr == IPPROTO_ICMPV6) अणु
			काष्ठा nd_msg *msg, _msg;

			msg = br_is_nd_neigh_msg(skb, &_msg);
			अगर (msg)
				br_करो_suppress_nd(skb, br, vid, p, msg);
	पूर्ण

	चयन (pkt_type) अणु
	हाल BR_PKT_MULTICAST:
		mdst = br_mdb_get(br, skb, vid);
		अगर ((mdst || BR_INPUT_SKB_CB_MROUTERS_ONLY(skb)) &&
		    br_multicast_querier_exists(br, eth_hdr(skb), mdst)) अणु
			अगर ((mdst && mdst->host_joined) ||
			    br_multicast_is_router(br)) अणु
				local_rcv = true;
				br->dev->stats.multicast++;
			पूर्ण
			mcast_hit = true;
		पूर्ण अन्यथा अणु
			local_rcv = true;
			br->dev->stats.multicast++;
		पूर्ण
		अवरोध;
	हाल BR_PKT_UNICAST:
		dst = br_fdb_find_rcu(br, eth_hdr(skb)->h_dest, vid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (dst) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		अगर (test_bit(BR_FDB_LOCAL, &dst->flags))
			वापस br_pass_frame_up(skb);

		अगर (now != dst->used)
			dst->used = now;
		br_क्रमward(dst->dst, skb, local_rcv, false);
	पूर्ण अन्यथा अणु
		अगर (!mcast_hit)
			br_flood(br, skb, pkt_type, local_rcv, false);
		अन्यथा
			br_multicast_flood(mdst, skb, local_rcv, false);
	पूर्ण

	अगर (local_rcv)
		वापस br_pass_frame_up(skb);

out:
	वापस 0;
drop:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(br_handle_frame_finish);

अटल व्योम __br_handle_local_finish(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_bridge_port *p = br_port_get_rcu(skb->dev);
	u16 vid = 0;

	/* check अगर vlan is allowed, to aव्योम spoofing */
	अगर ((p->flags & BR_LEARNING) &&
	    nbp_state_should_learn(p) &&
	    !br_opt_get(p->br, BROPT_NO_LL_LEARN) &&
	    br_should_learn(p, skb, &vid))
		br_fdb_update(p->br, p, eth_hdr(skb)->h_source, vid, 0);
पूर्ण

/* note: alपढ़ोy called with rcu_पढ़ो_lock */
अटल पूर्णांक br_handle_local_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__br_handle_local_finish(skb);

	/* वापस 1 to संकेत the okfn() was called so it's ok to use the skb */
	वापस 1;
पूर्ण

अटल पूर्णांक nf_hook_bridge_pre(काष्ठा sk_buff *skb, काष्ठा sk_buff **pskb)
अणु
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
	काष्ठा nf_hook_entries *e = शून्य;
	काष्ठा nf_hook_state state;
	अचिन्हित पूर्णांक verdict, i;
	काष्ठा net *net;
	पूर्णांक ret;

	net = dev_net(skb->dev);
#अगर_घोषित HAVE_JUMP_LABEL
	अगर (!अटल_key_false(&nf_hooks_needed[NFPROTO_BRIDGE][NF_BR_PRE_ROUTING]))
		जाओ frame_finish;
#पूर्ण_अगर

	e = rcu_dereference(net->nf.hooks_bridge[NF_BR_PRE_ROUTING]);
	अगर (!e)
		जाओ frame_finish;

	nf_hook_state_init(&state, NF_BR_PRE_ROUTING,
			   NFPROTO_BRIDGE, skb->dev, शून्य, शून्य,
			   net, br_handle_frame_finish);

	क्रम (i = 0; i < e->num_hook_entries; i++) अणु
		verdict = nf_hook_entry_hookfn(&e->hooks[i], skb, &state);
		चयन (verdict & NF_VERDICT_MASK) अणु
		हाल NF_ACCEPT:
			अगर (BR_INPUT_SKB_CB(skb)->br_netfilter_broute) अणु
				*pskb = skb;
				वापस RX_HANDLER_PASS;
			पूर्ण
			अवरोध;
		हाल NF_DROP:
			kमुक्त_skb(skb);
			वापस RX_HANDLER_CONSUMED;
		हाल NF_QUEUE:
			ret = nf_queue(skb, &state, i, verdict);
			अगर (ret == 1)
				जारी;
			वापस RX_HANDLER_CONSUMED;
		शेष: /* STOLEN */
			वापस RX_HANDLER_CONSUMED;
		पूर्ण
	पूर्ण
frame_finish:
	net = dev_net(skb->dev);
	br_handle_frame_finish(net, शून्य, skb);
#अन्यथा
	br_handle_frame_finish(dev_net(skb->dev), शून्य, skb);
#पूर्ण_अगर
	वापस RX_HANDLER_CONSUMED;
पूर्ण

/* Return 0 अगर the frame was not processed otherwise 1
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल पूर्णांक br_process_frame_type(काष्ठा net_bridge_port *p,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा br_frame_type *पंचांगp;

	hlist_क्रम_each_entry_rcu(पंचांगp, &p->br->frame_type_list, list)
		अगर (unlikely(पंचांगp->type == skb->protocol))
			वापस पंचांगp->frame_handler(p, skb);

	वापस 0;
पूर्ण

/*
 * Return शून्य अगर skb is handled
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल rx_handler_result_t br_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा net_bridge_port *p;
	काष्ठा sk_buff *skb = *pskb;
	स्थिर अचिन्हित अक्षर *dest = eth_hdr(skb)->h_dest;

	अगर (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		वापस RX_HANDLER_PASS;

	अगर (!is_valid_ether_addr(eth_hdr(skb)->h_source))
		जाओ drop;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस RX_HANDLER_CONSUMED;

	स_रखो(skb->cb, 0, माप(काष्ठा br_input_skb_cb));

	p = br_port_get_rcu(skb->dev);
	अगर (p->flags & BR_VLAN_TUNNEL) अणु
		अगर (br_handle_ingress_vlan_tunnel(skb, p,
						  nbp_vlan_group_rcu(p)))
			जाओ drop;
	पूर्ण

	अगर (unlikely(is_link_local_ether_addr(dest))) अणु
		u16 fwd_mask = p->br->group_fwd_mask_required;

		/*
		 * See IEEE 802.1D Table 7-10 Reserved addresses
		 *
		 * Assignment		 		Value
		 * Bridge Group Address		01-80-C2-00-00-00
		 * (MAC Control) 802.3		01-80-C2-00-00-01
		 * (Link Aggregation) 802.3	01-80-C2-00-00-02
		 * 802.1X PAE address		01-80-C2-00-00-03
		 *
		 * 802.1AB LLDP 		01-80-C2-00-00-0E
		 *
		 * Others reserved क्रम future standardization
		 */
		fwd_mask |= p->group_fwd_mask;
		चयन (dest[5]) अणु
		हाल 0x00:	/* Bridge Group Address */
			/* If STP is turned off,
			   then must क्रमward to keep loop detection */
			अगर (p->br->stp_enabled == BR_NO_STP ||
			    fwd_mask & (1u << dest[5]))
				जाओ क्रमward;
			*pskb = skb;
			__br_handle_local_finish(skb);
			वापस RX_HANDLER_PASS;

		हाल 0x01:	/* IEEE MAC (Pause) */
			जाओ drop;

		हाल 0x0E:	/* 802.1AB LLDP */
			fwd_mask |= p->br->group_fwd_mask;
			अगर (fwd_mask & (1u << dest[5]))
				जाओ क्रमward;
			*pskb = skb;
			__br_handle_local_finish(skb);
			वापस RX_HANDLER_PASS;

		शेष:
			/* Allow selective क्रमwarding क्रम most other protocols */
			fwd_mask |= p->br->group_fwd_mask;
			अगर (fwd_mask & (1u << dest[5]))
				जाओ क्रमward;
		पूर्ण

		/* The अन्यथा clause should be hit when nf_hook():
		 *   - वापसs < 0 (drop/error)
		 *   - वापसs = 0 (stolen/nf_queue)
		 * Thus वापस 1 from the okfn() to संकेत the skb is ok to pass
		 */
		अगर (NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_IN,
			    dev_net(skb->dev), शून्य, skb, skb->dev, शून्य,
			    br_handle_local_finish) == 1) अणु
			वापस RX_HANDLER_PASS;
		पूर्ण अन्यथा अणु
			वापस RX_HANDLER_CONSUMED;
		पूर्ण
	पूर्ण

	अगर (unlikely(br_process_frame_type(p, skb)))
		वापस RX_HANDLER_PASS;

क्रमward:
	चयन (p->state) अणु
	हाल BR_STATE_FORWARDING:
	हाल BR_STATE_LEARNING:
		अगर (ether_addr_equal(p->br->dev->dev_addr, dest))
			skb->pkt_type = PACKET_HOST;

		वापस nf_hook_bridge_pre(skb, pskb);
	शेष:
drop:
		kमुक्त_skb(skb);
	पूर्ण
	वापस RX_HANDLER_CONSUMED;
पूर्ण

/* This function has no purpose other than to appease the br_port_get_rcu/rtnl
 * helpers which identअगरy bridged ports according to the rx_handler installed
 * on them (so there _needs_ to be a bridge rx_handler even अगर we करोn't need it
 * to करो anything useful). This bridge won't support traffic to/from the stack,
 * but only hardware bridging. So वापस RX_HANDLER_PASS so we करोn't steal
 * frames from the ETH_P_XDSA packet_type handler.
 */
अटल rx_handler_result_t br_handle_frame_dummy(काष्ठा sk_buff **pskb)
अणु
	वापस RX_HANDLER_PASS;
पूर्ण

rx_handler_func_t *br_get_rx_handler(स्थिर काष्ठा net_device *dev)
अणु
	अगर (netdev_uses_dsa(dev))
		वापस br_handle_frame_dummy;

	वापस br_handle_frame;
पूर्ण

व्योम br_add_frame(काष्ठा net_bridge *br, काष्ठा br_frame_type *ft)
अणु
	hlist_add_head_rcu(&ft->list, &br->frame_type_list);
पूर्ण

व्योम br_del_frame(काष्ठा net_bridge *br, काष्ठा br_frame_type *ft)
अणु
	काष्ठा br_frame_type *पंचांगp;

	hlist_क्रम_each_entry(पंचांगp, &br->frame_type_list, list)
		अगर (ft == पंचांगp) अणु
			hlist_del_rcu(&ft->list);
			वापस;
		पूर्ण
पूर्ण
