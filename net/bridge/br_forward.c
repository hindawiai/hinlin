<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Forwarding decision
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश "br_private.h"

/* Don't क्रमward packets to originating port or क्रमwarding disabled */
अटल अंतरभूत पूर्णांक should_deliver(स्थिर काष्ठा net_bridge_port *p,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_bridge_vlan_group *vg;

	vg = nbp_vlan_group_rcu(p);
	वापस ((p->flags & BR_HAIRPIN_MODE) || skb->dev != p->dev) &&
		p->state == BR_STATE_FORWARDING && br_allowed_egress(vg, skb) &&
		nbp_चयनdev_allowed_egress(p, skb) &&
		!br_skb_isolated(p, skb);
पूर्ण

पूर्णांक br_dev_queue_push_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb_push(skb, ETH_HLEN);
	अगर (!is_skb_क्रमwardable(skb->dev, skb))
		जाओ drop;

	br_drop_fake_rtable(skb);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    eth_type_vlan(skb->protocol)) अणु
		पूर्णांक depth;

		अगर (!__vlan_get_protocol(skb, skb->protocol, &depth))
			जाओ drop;

		skb_set_network_header(skb, depth);
	पूर्ण

	dev_queue_xmit(skb);

	वापस 0;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(br_dev_queue_push_xmit);

पूर्णांक br_क्रमward_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb->tstamp = 0;
	वापस NF_HOOK(NFPROTO_BRIDGE, NF_BR_POST_ROUTING,
		       net, sk, skb, शून्य, skb->dev,
		       br_dev_queue_push_xmit);

पूर्ण
EXPORT_SYMBOL_GPL(br_क्रमward_finish);

अटल व्योम __br_क्रमward(स्थिर काष्ठा net_bridge_port *to,
			 काष्ठा sk_buff *skb, bool local_orig)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_device *indev;
	काष्ठा net *net;
	पूर्णांक br_hook;

	vg = nbp_vlan_group_rcu(to);
	skb = br_handle_vlan(to->br, to, vg, skb);
	अगर (!skb)
		वापस;

	indev = skb->dev;
	skb->dev = to->dev;
	अगर (!local_orig) अणु
		अगर (skb_warn_अगर_lro(skb)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
		br_hook = NF_BR_FORWARD;
		skb_क्रमward_csum(skb);
		net = dev_net(indev);
	पूर्ण अन्यथा अणु
		अगर (unlikely(netpoll_tx_running(to->br->dev))) अणु
			skb_push(skb, ETH_HLEN);
			अगर (!is_skb_क्रमwardable(skb->dev, skb))
				kमुक्त_skb(skb);
			अन्यथा
				br_netpoll_send_skb(to, skb);
			वापस;
		पूर्ण
		br_hook = NF_BR_LOCAL_OUT;
		net = dev_net(skb->dev);
		indev = शून्य;
	पूर्ण

	NF_HOOK(NFPROTO_BRIDGE, br_hook,
		net, शून्य, skb, indev, skb->dev,
		br_क्रमward_finish);
पूर्ण

अटल पूर्णांक deliver_clone(स्थिर काष्ठा net_bridge_port *prev,
			 काष्ठा sk_buff *skb, bool local_orig)
अणु
	काष्ठा net_device *dev = BR_INPUT_SKB_CB(skb)->brdev;

	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		dev->stats.tx_dropped++;
		वापस -ENOMEM;
	पूर्ण

	__br_क्रमward(prev, skb, local_orig);
	वापस 0;
पूर्ण

/**
 * br_क्रमward - क्रमward a packet to a specअगरic port
 * @to: destination port
 * @skb: packet being क्रमwarded
 * @local_rcv: packet will be received locally after क्रमwarding
 * @local_orig: packet is locally originated
 *
 * Should be called with rcu_पढ़ो_lock.
 */
व्योम br_क्रमward(स्थिर काष्ठा net_bridge_port *to,
		काष्ठा sk_buff *skb, bool local_rcv, bool local_orig)
अणु
	अगर (unlikely(!to))
		जाओ out;

	/* redirect to backup link अगर the destination port is करोwn */
	अगर (rcu_access_poपूर्णांकer(to->backup_port) && !netअगर_carrier_ok(to->dev)) अणु
		काष्ठा net_bridge_port *backup_port;

		backup_port = rcu_dereference(to->backup_port);
		अगर (unlikely(!backup_port))
			जाओ out;
		to = backup_port;
	पूर्ण

	अगर (should_deliver(to, skb)) अणु
		अगर (local_rcv)
			deliver_clone(to, skb, local_orig);
		अन्यथा
			__br_क्रमward(to, skb, local_orig);
		वापस;
	पूर्ण

out:
	अगर (!local_rcv)
		kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(br_क्रमward);

अटल काष्ठा net_bridge_port *maybe_deliver(
	काष्ठा net_bridge_port *prev, काष्ठा net_bridge_port *p,
	काष्ठा sk_buff *skb, bool local_orig)
अणु
	u8 igmp_type = br_multicast_igmp_type(skb);
	पूर्णांक err;

	अगर (!should_deliver(p, skb))
		वापस prev;

	अगर (!prev)
		जाओ out;

	err = deliver_clone(prev, skb, local_orig);
	अगर (err)
		वापस ERR_PTR(err);
out:
	br_multicast_count(p->br, p, skb, igmp_type, BR_MCAST_सूची_TX);

	वापस p;
पूर्ण

/* called under rcu_पढ़ो_lock */
व्योम br_flood(काष्ठा net_bridge *br, काष्ठा sk_buff *skb,
	      क्रमागत br_pkt_type pkt_type, bool local_rcv, bool local_orig)
अणु
	काष्ठा net_bridge_port *prev = शून्य;
	काष्ठा net_bridge_port *p;

	list_क्रम_each_entry_rcu(p, &br->port_list, list) अणु
		/* Do not flood unicast traffic to ports that turn it off, nor
		 * other traffic अगर flood off, except क्रम traffic we originate
		 */
		चयन (pkt_type) अणु
		हाल BR_PKT_UNICAST:
			अगर (!(p->flags & BR_FLOOD))
				जारी;
			अवरोध;
		हाल BR_PKT_MULTICAST:
			अगर (!(p->flags & BR_MCAST_FLOOD) && skb->dev != br->dev)
				जारी;
			अवरोध;
		हाल BR_PKT_BROADCAST:
			अगर (!(p->flags & BR_BCAST_FLOOD) && skb->dev != br->dev)
				जारी;
			अवरोध;
		पूर्ण

		/* Do not flood to ports that enable proxy ARP */
		अगर (p->flags & BR_PROXYARP)
			जारी;
		अगर ((p->flags & (BR_PROXYARP_WIFI | BR_NEIGH_SUPPRESS)) &&
		    BR_INPUT_SKB_CB(skb)->proxyarp_replied)
			जारी;

		prev = maybe_deliver(prev, p, skb, local_orig);
		अगर (IS_ERR(prev))
			जाओ out;
	पूर्ण

	अगर (!prev)
		जाओ out;

	अगर (local_rcv)
		deliver_clone(prev, skb, local_orig);
	अन्यथा
		__br_क्रमward(prev, skb, local_orig);
	वापस;

out:
	अगर (!local_rcv)
		kमुक्त_skb(skb);
पूर्ण

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
अटल व्योम maybe_deliver_addr(काष्ठा net_bridge_port *p, काष्ठा sk_buff *skb,
			       स्थिर अचिन्हित अक्षर *addr, bool local_orig)
अणु
	काष्ठा net_device *dev = BR_INPUT_SKB_CB(skb)->brdev;
	स्थिर अचिन्हित अक्षर *src = eth_hdr(skb)->h_source;

	अगर (!should_deliver(p, skb))
		वापस;

	/* Even with hairpin, no soliloquies - prevent अवरोधing IPv6 DAD */
	अगर (skb->dev == p->dev && ether_addr_equal(src, addr))
		वापस;

	skb = skb_copy(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		dev->stats.tx_dropped++;
		वापस;
	पूर्ण

	अगर (!is_broadcast_ether_addr(addr))
		स_नकल(eth_hdr(skb)->h_dest, addr, ETH_ALEN);

	__br_क्रमward(p, skb, local_orig);
पूर्ण

/* called with rcu_पढ़ो_lock */
व्योम br_multicast_flood(काष्ठा net_bridge_mdb_entry *mdst,
			काष्ठा sk_buff *skb,
			bool local_rcv, bool local_orig)
अणु
	काष्ठा net_device *dev = BR_INPUT_SKB_CB(skb)->brdev;
	काष्ठा net_bridge *br = netdev_priv(dev);
	काष्ठा net_bridge_port *prev = शून्य;
	काष्ठा net_bridge_port_group *p;
	bool allow_mode_include = true;
	काष्ठा hlist_node *rp;

	rp = rcu_dereference(hlist_first_rcu(&br->router_list));
	अगर (mdst) अणु
		p = rcu_dereference(mdst->ports);
		अगर (br_multicast_should_handle_mode(br, mdst->addr.proto) &&
		    br_multicast_is_star_g(&mdst->addr))
			allow_mode_include = false;
	पूर्ण अन्यथा अणु
		p = शून्य;
	पूर्ण

	जबतक (p || rp) अणु
		काष्ठा net_bridge_port *port, *lport, *rport;

		lport = p ? p->key.port : शून्य;
		rport = hlist_entry_safe(rp, काष्ठा net_bridge_port, rlist);

		अगर ((अचिन्हित दीर्घ)lport > (अचिन्हित दीर्घ)rport) अणु
			port = lport;

			अगर (port->flags & BR_MULTICAST_TO_UNICAST) अणु
				maybe_deliver_addr(lport, skb, p->eth_addr,
						   local_orig);
				जाओ delivered;
			पूर्ण
			अगर ((!allow_mode_include &&
			     p->filter_mode == MCAST_INCLUDE) ||
			    (p->flags & MDB_PG_FLAGS_BLOCKED))
				जाओ delivered;
		पूर्ण अन्यथा अणु
			port = rport;
		पूर्ण

		prev = maybe_deliver(prev, port, skb, local_orig);
		अगर (IS_ERR(prev))
			जाओ out;
delivered:
		अगर ((अचिन्हित दीर्घ)lport >= (अचिन्हित दीर्घ)port)
			p = rcu_dereference(p->next);
		अगर ((अचिन्हित दीर्घ)rport >= (अचिन्हित दीर्घ)port)
			rp = rcu_dereference(hlist_next_rcu(rp));
	पूर्ण

	अगर (!prev)
		जाओ out;

	अगर (local_rcv)
		deliver_clone(prev, skb, local_orig);
	अन्यथा
		__br_क्रमward(prev, skb, local_orig);
	वापस;

out:
	अगर (!local_rcv)
		kमुक्त_skb(skb);
पूर्ण
#पूर्ण_अगर
