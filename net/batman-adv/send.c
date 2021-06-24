<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "send.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/workqueue.h>

#समावेश "distributed-arp-table.h"
#समावेश "fragmentation.h"
#समावेश "gateway_client.h"
#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "network-coding.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"

अटल व्योम batadv_send_outstanding_bcast_packet(काष्ठा work_काष्ठा *work);

/**
 * batadv_send_skb_packet() - send an alपढ़ोy prepared packet
 * @skb: the packet to send
 * @hard_अगरace: the पूर्णांकerface to use to send the broadcast packet
 * @dst_addr: the payload destination
 *
 * Send out an alपढ़ोy prepared packet to the given neighbor or broadcast it
 * using the specअगरied पूर्णांकerface. Either hard_अगरace or neigh_node must be not
 * शून्य.
 * If neigh_node is शून्य, then the packet is broadcasted using hard_अगरace,
 * otherwise it is sent as unicast to the given neighbor.
 *
 * Regardless of the वापस value, the skb is consumed.
 *
 * Return: A negative त्रुटि_सं code is वापसed on a failure. A success करोes not
 * guarantee the frame will be transmitted as it may be dropped due
 * to congestion or traffic shaping.
 */
पूर्णांक batadv_send_skb_packet(काष्ठा sk_buff *skb,
			   काष्ठा batadv_hard_अगरace *hard_अगरace,
			   स्थिर u8 *dst_addr)
अणु
	काष्ठा batadv_priv *bat_priv;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक ret;

	bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
		जाओ send_skb_err;

	अगर (unlikely(!hard_अगरace->net_dev))
		जाओ send_skb_err;

	अगर (!(hard_अगरace->net_dev->flags & IFF_UP)) अणु
		pr_warn("Interface %s is not up - can't send packet via that interface!\n",
			hard_अगरace->net_dev->name);
		जाओ send_skb_err;
	पूर्ण

	/* push to the ethernet header. */
	अगर (batadv_skb_head_push(skb, ETH_HLEN) < 0)
		जाओ send_skb_err;

	skb_reset_mac_header(skb);

	ethhdr = eth_hdr(skb);
	ether_addr_copy(ethhdr->h_source, hard_अगरace->net_dev->dev_addr);
	ether_addr_copy(ethhdr->h_dest, dst_addr);
	ethhdr->h_proto = htons(ETH_P_BATMAN);

	skb_set_network_header(skb, ETH_HLEN);
	skb->protocol = htons(ETH_P_BATMAN);

	skb->dev = hard_अगरace->net_dev;

	/* Save a clone of the skb to use when decoding coded packets */
	batadv_nc_skb_store_क्रम_decoding(bat_priv, skb);

	/* dev_queue_xmit() वापसs a negative result on error.	 However on
	 * congestion and traffic shaping, it drops and वापसs NET_XMIT_DROP
	 * (which is > 0). This will not be treated as an error.
	 */
	ret = dev_queue_xmit(skb);
	वापस net_xmit_eval(ret);
send_skb_err:
	kमुक्त_skb(skb);
	वापस NET_XMIT_DROP;
पूर्ण

/**
 * batadv_send_broadcast_skb() - Send broadcast packet via hard पूर्णांकerface
 * @skb: packet to be transmitted (with batadv header and no outer eth header)
 * @hard_अगरace: outgoing पूर्णांकerface
 *
 * Return: A negative त्रुटि_सं code is वापसed on a failure. A success करोes not
 * guarantee the frame will be transmitted as it may be dropped due
 * to congestion or traffic shaping.
 */
पूर्णांक batadv_send_broadcast_skb(काष्ठा sk_buff *skb,
			      काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	वापस batadv_send_skb_packet(skb, hard_अगरace, batadv_broadcast_addr);
पूर्ण

/**
 * batadv_send_unicast_skb() - Send unicast packet to neighbor
 * @skb: packet to be transmitted (with batadv header and no outer eth header)
 * @neigh: neighbor which is used as next hop to destination
 *
 * Return: A negative त्रुटि_सं code is वापसed on a failure. A success करोes not
 * guarantee the frame will be transmitted as it may be dropped due
 * to congestion or traffic shaping.
 */
पूर्णांक batadv_send_unicast_skb(काष्ठा sk_buff *skb,
			    काष्ठा batadv_neigh_node *neigh)
अणु
#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;
#पूर्ण_अगर
	पूर्णांक ret;

	ret = batadv_send_skb_packet(skb, neigh->अगर_incoming, neigh->addr);

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	hardअगर_neigh = batadv_hardअगर_neigh_get(neigh->अगर_incoming, neigh->addr);

	अगर (hardअगर_neigh && ret != NET_XMIT_DROP)
		hardअगर_neigh->bat_v.last_unicast_tx = jअगरfies;

	अगर (hardअगर_neigh)
		batadv_hardअगर_neigh_put(hardअगर_neigh);
#पूर्ण_अगर

	वापस ret;
पूर्ण

/**
 * batadv_send_skb_to_orig() - Lookup next-hop and transmit skb.
 * @skb: Packet to be transmitted.
 * @orig_node: Final destination of the packet.
 * @recv_अगर: Interface used when receiving the packet (can be शून्य).
 *
 * Looks up the best next-hop towards the passed originator and passes the
 * skb on क्रम preparation of MAC header. If the packet originated from this
 * host, शून्य can be passed as recv_अगर and no पूर्णांकerface alternating is
 * attempted.
 *
 * Return: negative त्रुटि_सं code on a failure, -EINPROGRESS अगर the skb is
 * buffered क्रम later transmit or the NET_XMIT status वापसed by the
 * lower routine अगर the packet has been passed करोwn.
 */
पूर्णांक batadv_send_skb_to_orig(काष्ठा sk_buff *skb,
			    काष्ठा batadv_orig_node *orig_node,
			    काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = orig_node->bat_priv;
	काष्ठा batadv_neigh_node *neigh_node;
	पूर्णांक ret;

	/* batadv_find_router() increases neigh_nodes refcount अगर found. */
	neigh_node = batadv_find_router(bat_priv, orig_node, recv_अगर);
	अगर (!neigh_node) अणु
		ret = -EINVAL;
		जाओ मुक्त_skb;
	पूर्ण

	/* Check अगर the skb is too large to send in one piece and fragment
	 * it अगर needed.
	 */
	अगर (atomic_पढ़ो(&bat_priv->fragmentation) &&
	    skb->len > neigh_node->अगर_incoming->net_dev->mtu) अणु
		/* Fragment and send packet. */
		ret = batadv_frag_send_packet(skb, orig_node, neigh_node);
		/* skb was consumed */
		skb = शून्य;

		जाओ put_neigh_node;
	पूर्ण

	/* try to network code the packet, अगर it is received on an पूर्णांकerface
	 * (i.e. being क्रमwarded). If the packet originates from this node or अगर
	 * network coding fails, then send the packet as usual.
	 */
	अगर (recv_अगर && batadv_nc_skb_क्रमward(skb, neigh_node))
		ret = -EINPROGRESS;
	अन्यथा
		ret = batadv_send_unicast_skb(skb, neigh_node);

	/* skb was consumed */
	skb = शून्य;

put_neigh_node:
	batadv_neigh_node_put(neigh_node);
मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_send_skb_push_fill_unicast() - extend the buffer and initialize the
 *  common fields क्रम unicast packets
 * @skb: the skb carrying the unicast header to initialize
 * @hdr_size: amount of bytes to push at the beginning of the skb
 * @orig_node: the destination node
 *
 * Return: false अगर the buffer extension was not possible or true otherwise.
 */
अटल bool
batadv_send_skb_push_fill_unicast(काष्ठा sk_buff *skb, पूर्णांक hdr_size,
				  काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_unicast_packet *unicast_packet;
	u8 ttvn = (u8)atomic_पढ़ो(&orig_node->last_ttvn);

	अगर (batadv_skb_head_push(skb, hdr_size) < 0)
		वापस false;

	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;
	unicast_packet->version = BATADV_COMPAT_VERSION;
	/* baपंचांगan packet type: unicast */
	unicast_packet->packet_type = BATADV_UNICAST;
	/* set unicast ttl */
	unicast_packet->ttl = BATADV_TTL;
	/* copy the destination क्रम faster routing */
	ether_addr_copy(unicast_packet->dest, orig_node->orig);
	/* set the destination tt version number */
	unicast_packet->ttvn = ttvn;

	वापस true;
पूर्ण

/**
 * batadv_send_skb_prepare_unicast() - encapsulate an skb with a unicast header
 * @skb: the skb containing the payload to encapsulate
 * @orig_node: the destination node
 *
 * Return: false अगर the payload could not be encapsulated or true otherwise.
 */
अटल bool batadv_send_skb_prepare_unicast(काष्ठा sk_buff *skb,
					    काष्ठा batadv_orig_node *orig_node)
अणु
	माप_प्रकार uni_size = माप(काष्ठा batadv_unicast_packet);

	वापस batadv_send_skb_push_fill_unicast(skb, uni_size, orig_node);
पूर्ण

/**
 * batadv_send_skb_prepare_unicast_4addr() - encapsulate an skb with a
 *  unicast 4addr header
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the skb containing the payload to encapsulate
 * @orig: the destination node
 * @packet_subtype: the unicast 4addr packet subtype to use
 *
 * Return: false अगर the payload could not be encapsulated or true otherwise.
 */
bool batadv_send_skb_prepare_unicast_4addr(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb,
					   काष्ठा batadv_orig_node *orig,
					   पूर्णांक packet_subtype)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर;
	काष्ठा batadv_unicast_4addr_packet *uc_4addr_packet;
	bool ret = false;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	/* Pull the header space and fill the unicast_packet subकाष्ठाure.
	 * We can करो that because the first member of the uc_4addr_packet
	 * is of type काष्ठा unicast_packet
	 */
	अगर (!batadv_send_skb_push_fill_unicast(skb, माप(*uc_4addr_packet),
					       orig))
		जाओ out;

	uc_4addr_packet = (काष्ठा batadv_unicast_4addr_packet *)skb->data;
	uc_4addr_packet->u.packet_type = BATADV_UNICAST_4ADDR;
	ether_addr_copy(uc_4addr_packet->src, primary_अगर->net_dev->dev_addr);
	uc_4addr_packet->subtype = packet_subtype;
	uc_4addr_packet->reserved = 0;

	ret = true;
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	वापस ret;
पूर्ण

/**
 * batadv_send_skb_unicast() - encapsulate and send an skb via unicast
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: payload to send
 * @packet_type: the baपंचांगan unicast packet type to use
 * @packet_subtype: the unicast 4addr packet subtype (only relevant क्रम unicast
 *  4addr packets)
 * @orig_node: the originator to send the packet to
 * @vid: the vid to be used to search the translation table
 *
 * Wrap the given skb पूर्णांकo a baपंचांगan-adv unicast or unicast-4addr header
 * depending on whether BATADV_UNICAST or BATADV_UNICAST_4ADDR was supplied
 * as packet_type. Then send this frame to the given orig_node.
 *
 * Return: NET_XMIT_DROP in हाल of error or NET_XMIT_SUCCESS otherwise.
 */
पूर्णांक batadv_send_skb_unicast(काष्ठा batadv_priv *bat_priv,
			    काष्ठा sk_buff *skb, पूर्णांक packet_type,
			    पूर्णांक packet_subtype,
			    काष्ठा batadv_orig_node *orig_node,
			    अचिन्हित लघु vid)
अणु
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक ret = NET_XMIT_DROP;

	अगर (!orig_node)
		जाओ out;

	चयन (packet_type) अणु
	हाल BATADV_UNICAST:
		अगर (!batadv_send_skb_prepare_unicast(skb, orig_node))
			जाओ out;
		अवरोध;
	हाल BATADV_UNICAST_4ADDR:
		अगर (!batadv_send_skb_prepare_unicast_4addr(bat_priv, skb,
							   orig_node,
							   packet_subtype))
			जाओ out;
		अवरोध;
	शेष:
		/* this function supports UNICAST and UNICAST_4ADDR only. It
		 * should never be invoked with any other packet type
		 */
		जाओ out;
	पूर्ण

	/* skb->data might have been पुनः_स्मृतिated by
	 * batadv_send_skb_prepare_unicastअणु,_4addrपूर्ण()
	 */
	ethhdr = eth_hdr(skb);
	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;

	/* inक्रमm the destination node that we are still missing a correct route
	 * क्रम this client. The destination will receive this packet and will
	 * try to reroute it because the ttvn contained in the header is less
	 * than the current one
	 */
	अगर (batadv_tt_global_client_is_roaming(bat_priv, ethhdr->h_dest, vid))
		unicast_packet->ttvn = unicast_packet->ttvn - 1;

	ret = batadv_send_skb_to_orig(skb, orig_node, शून्य);
	 /* skb was consumed */
	skb = शून्य;

out:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/**
 * batadv_send_skb_via_tt_generic() - send an skb via TT lookup
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: payload to send
 * @packet_type: the baपंचांगan unicast packet type to use
 * @packet_subtype: the unicast 4addr packet subtype (only relevant क्रम unicast
 *  4addr packets)
 * @dst_hपूर्णांक: can be used to override the destination contained in the skb
 * @vid: the vid to be used to search the translation table
 *
 * Look up the recipient node क्रम the destination address in the ethernet
 * header via the translation table. Wrap the given skb पूर्णांकo a baपंचांगan-adv
 * unicast or unicast-4addr header depending on whether BATADV_UNICAST or
 * BATADV_UNICAST_4ADDR was supplied as packet_type. Then send this frame
 * to the according destination node.
 *
 * Return: NET_XMIT_DROP in हाल of error or NET_XMIT_SUCCESS otherwise.
 */
पूर्णांक batadv_send_skb_via_tt_generic(काष्ठा batadv_priv *bat_priv,
				   काष्ठा sk_buff *skb, पूर्णांक packet_type,
				   पूर्णांक packet_subtype, u8 *dst_hपूर्णांक,
				   अचिन्हित लघु vid)
अणु
	काष्ठा ethhdr *ethhdr = (काष्ठा ethhdr *)skb->data;
	काष्ठा batadv_orig_node *orig_node;
	u8 *src, *dst;
	पूर्णांक ret;

	src = ethhdr->h_source;
	dst = ethhdr->h_dest;

	/* अगर we got an hपूर्णांक! let's send the packet to this client (अगर any) */
	अगर (dst_hपूर्णांक) अणु
		src = शून्य;
		dst = dst_hपूर्णांक;
	पूर्ण
	orig_node = batadv_transtable_search(bat_priv, src, dst, vid);

	ret = batadv_send_skb_unicast(bat_priv, skb, packet_type,
				      packet_subtype, orig_node, vid);

	अगर (orig_node)
		batadv_orig_node_put(orig_node);

	वापस ret;
पूर्ण

/**
 * batadv_send_skb_via_gw() - send an skb via gateway lookup
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: payload to send
 * @vid: the vid to be used to search the translation table
 *
 * Look up the currently selected gateway. Wrap the given skb पूर्णांकo a baपंचांगan-adv
 * unicast header and send this frame to this gateway node.
 *
 * Return: NET_XMIT_DROP in हाल of error or NET_XMIT_SUCCESS otherwise.
 */
पूर्णांक batadv_send_skb_via_gw(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			   अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक ret;

	orig_node = batadv_gw_get_selected_orig(bat_priv);
	ret = batadv_send_skb_unicast(bat_priv, skb, BATADV_UNICAST_4ADDR,
				      BATADV_P_DATA, orig_node, vid);

	अगर (orig_node)
		batadv_orig_node_put(orig_node);

	वापस ret;
पूर्ण

/**
 * batadv_क्रमw_packet_मुक्त() - मुक्त a क्रमwarding packet
 * @क्रमw_packet: The packet to मुक्त
 * @dropped: whether the packet is मुक्तd because is dropped
 *
 * This मुक्तs a क्रमwarding packet and releases any resources it might
 * have claimed.
 */
व्योम batadv_क्रमw_packet_मुक्त(काष्ठा batadv_क्रमw_packet *क्रमw_packet,
			     bool dropped)
अणु
	अगर (dropped)
		kमुक्त_skb(क्रमw_packet->skb);
	अन्यथा
		consume_skb(क्रमw_packet->skb);

	अगर (क्रमw_packet->अगर_incoming)
		batadv_hardअगर_put(क्रमw_packet->अगर_incoming);
	अगर (क्रमw_packet->अगर_outgoing)
		batadv_hardअगर_put(क्रमw_packet->अगर_outgoing);
	अगर (क्रमw_packet->queue_left)
		atomic_inc(क्रमw_packet->queue_left);
	kमुक्त(क्रमw_packet);
पूर्ण

/**
 * batadv_क्रमw_packet_alloc() - allocate a क्रमwarding packet
 * @अगर_incoming: The (optional) अगर_incoming to be grabbed
 * @अगर_outgoing: The (optional) अगर_outgoing to be grabbed
 * @queue_left: The (optional) queue counter to decrease
 * @bat_priv: The bat_priv क्रम the mesh of this क्रमw_packet
 * @skb: The raw packet this क्रमwarding packet shall contain
 *
 * Allocates a क्रमwarding packet and tries to get a reference to the
 * (optional) अगर_incoming, अगर_outgoing and queue_left. If queue_left
 * is शून्य then bat_priv is optional, too.
 *
 * Return: An allocated क्रमwarding packet on success, शून्य otherwise.
 */
काष्ठा batadv_क्रमw_packet *
batadv_क्रमw_packet_alloc(काष्ठा batadv_hard_अगरace *अगर_incoming,
			 काष्ठा batadv_hard_अगरace *अगर_outgoing,
			 atomic_t *queue_left,
			 काष्ठा batadv_priv *bat_priv,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_क्रमw_packet *क्रमw_packet;
	स्थिर अक्षर *qname;

	अगर (queue_left && !batadv_atomic_dec_not_zero(queue_left)) अणु
		qname = "unknown";

		अगर (queue_left == &bat_priv->bcast_queue_left)
			qname = "bcast";

		अगर (queue_left == &bat_priv->baपंचांगan_queue_left)
			qname = "batman";

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s queue is full\n", qname);

		वापस शून्य;
	पूर्ण

	क्रमw_packet = kदो_स्मृति(माप(*क्रमw_packet), GFP_ATOMIC);
	अगर (!क्रमw_packet)
		जाओ err;

	अगर (अगर_incoming)
		kref_get(&अगर_incoming->refcount);

	अगर (अगर_outgoing)
		kref_get(&अगर_outgoing->refcount);

	INIT_HLIST_NODE(&क्रमw_packet->list);
	INIT_HLIST_NODE(&क्रमw_packet->cleanup_list);
	क्रमw_packet->skb = skb;
	क्रमw_packet->queue_left = queue_left;
	क्रमw_packet->अगर_incoming = अगर_incoming;
	क्रमw_packet->अगर_outgoing = अगर_outgoing;
	क्रमw_packet->num_packets = 0;

	वापस क्रमw_packet;

err:
	अगर (queue_left)
		atomic_inc(queue_left);

	वापस शून्य;
पूर्ण

/**
 * batadv_क्रमw_packet_was_stolen() - check whether someone stole this packet
 * @क्रमw_packet: the क्रमwarding packet to check
 *
 * This function checks whether the given क्रमwarding packet was claimed by
 * someone अन्यथा क्रम मुक्त().
 *
 * Return: True अगर someone stole it, false otherwise.
 */
अटल bool
batadv_क्रमw_packet_was_stolen(काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	वापस !hlist_unhashed(&क्रमw_packet->cleanup_list);
पूर्ण

/**
 * batadv_क्रमw_packet_steal() - claim a क्रमw_packet क्रम मुक्त()
 * @क्रमw_packet: the क्रमwarding packet to steal
 * @lock: a key to the store to steal from (e.g. क्रमw_अणुbat,bcastपूर्ण_list_lock)
 *
 * This function tries to steal a specअगरic क्रमw_packet from global
 * visibility क्रम the purpose of getting it क्रम मुक्त(). That means
 * the caller is *not* allowed to requeue it afterwards.
 *
 * Return: True अगर stealing was successful. False अगर someone अन्यथा stole it
 * beक्रमe us.
 */
bool batadv_क्रमw_packet_steal(काष्ठा batadv_क्रमw_packet *क्रमw_packet,
			      spinlock_t *lock)
अणु
	/* did purging routine steal it earlier? */
	spin_lock_bh(lock);
	अगर (batadv_क्रमw_packet_was_stolen(क्रमw_packet)) अणु
		spin_unlock_bh(lock);
		वापस false;
	पूर्ण

	hlist_del_init(&क्रमw_packet->list);

	/* Just to spot misuse of this function */
	hlist_add_fake(&क्रमw_packet->cleanup_list);

	spin_unlock_bh(lock);
	वापस true;
पूर्ण

/**
 * batadv_क्रमw_packet_list_steal() - claim a list of क्रमward packets क्रम मुक्त()
 * @क्रमw_list: the to be stolen क्रमward packets
 * @cleanup_list: a backup poपूर्णांकer, to be able to dispose the packet later
 * @hard_अगरace: the पूर्णांकerface to steal क्रमward packets from
 *
 * This function claims responsibility to मुक्त any क्रमw_packet queued on the
 * given hard_अगरace. If hard_अगरace is शून्य क्रमwarding packets on all hard
 * पूर्णांकerfaces will be claimed.
 *
 * The packets are being moved from the क्रमw_list to the cleanup_list. This
 * makes it possible क्रम alपढ़ोy running thपढ़ोs to notice the claim.
 */
अटल व्योम
batadv_क्रमw_packet_list_steal(काष्ठा hlist_head *क्रमw_list,
			      काष्ठा hlist_head *cleanup_list,
			      स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_क्रमw_packet *क्रमw_packet;
	काष्ठा hlist_node *safe_पंचांगp_node;

	hlist_क्रम_each_entry_safe(क्रमw_packet, safe_पंचांगp_node,
				  क्रमw_list, list) अणु
		/* अगर purge_outstanding_packets() was called with an argument
		 * we delete only packets beदीर्घing to the given पूर्णांकerface
		 */
		अगर (hard_अगरace &&
		    क्रमw_packet->अगर_incoming != hard_अगरace &&
		    क्रमw_packet->अगर_outgoing != hard_अगरace)
			जारी;

		hlist_del(&क्रमw_packet->list);
		hlist_add_head(&क्रमw_packet->cleanup_list, cleanup_list);
	पूर्ण
पूर्ण

/**
 * batadv_क्रमw_packet_list_मुक्त() - मुक्त a list of क्रमward packets
 * @head: a list of to be मुक्तd क्रमw_packets
 *
 * This function cancels the scheduling of any packet in the provided list,
 * रुकोs क्रम any possibly running packet क्रमwarding thपढ़ो to finish and
 * finally, safely मुक्तs this क्रमward packet.
 *
 * This function might sleep.
 */
अटल व्योम batadv_क्रमw_packet_list_मुक्त(काष्ठा hlist_head *head)
अणु
	काष्ठा batadv_क्रमw_packet *क्रमw_packet;
	काष्ठा hlist_node *safe_पंचांगp_node;

	hlist_क्रम_each_entry_safe(क्रमw_packet, safe_पंचांगp_node, head,
				  cleanup_list) अणु
		cancel_delayed_work_sync(&क्रमw_packet->delayed_work);

		hlist_del(&क्रमw_packet->cleanup_list);
		batadv_क्रमw_packet_मुक्त(क्रमw_packet, true);
	पूर्ण
पूर्ण

/**
 * batadv_क्रमw_packet_queue() - try to queue a क्रमwarding packet
 * @क्रमw_packet: the क्रमwarding packet to queue
 * @lock: a key to the store (e.g. क्रमw_अणुbat,bcastपूर्ण_list_lock)
 * @head: the shelve to queue it on (e.g. क्रमw_अणुbat,bcastपूर्ण_list)
 * @send_समय: बारtamp (jअगरfies) when the packet is to be sent
 *
 * This function tries to (re)queue a क्रमwarding packet. Requeuing
 * is prevented अगर the according पूर्णांकerface is shutting करोwn
 * (e.g. अगर batadv_क्रमw_packet_list_steal() was called क्रम this
 * packet earlier).
 *
 * Calling batadv_क्रमw_packet_queue() after a call to
 * batadv_क्रमw_packet_steal() is क्रमbidden!
 *
 * Caller needs to ensure that क्रमw_packet->delayed_work was initialized.
 */
अटल व्योम batadv_क्रमw_packet_queue(काष्ठा batadv_क्रमw_packet *क्रमw_packet,
				     spinlock_t *lock, काष्ठा hlist_head *head,
				     अचिन्हित दीर्घ send_समय)
अणु
	spin_lock_bh(lock);

	/* did purging routine steal it from us? */
	अगर (batadv_क्रमw_packet_was_stolen(क्रमw_packet)) अणु
		/* If you got it क्रम मुक्त() without trouble, then
		 * करोn't get back पूर्णांकo the queue after stealing...
		 */
		WARN_ONCE(hlist_fake(&क्रमw_packet->cleanup_list),
			  "Requeuing after batadv_forw_packet_steal() not allowed!\n");

		spin_unlock_bh(lock);
		वापस;
	पूर्ण

	hlist_del_init(&क्रमw_packet->list);
	hlist_add_head(&क्रमw_packet->list, head);

	queue_delayed_work(batadv_event_workqueue,
			   &क्रमw_packet->delayed_work,
			   send_समय - jअगरfies);
	spin_unlock_bh(lock);
पूर्ण

/**
 * batadv_क्रमw_packet_bcast_queue() - try to queue a broadcast packet
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @क्रमw_packet: the क्रमwarding packet to queue
 * @send_समय: बारtamp (jअगरfies) when the packet is to be sent
 *
 * This function tries to (re)queue a broadcast packet.
 *
 * Caller needs to ensure that क्रमw_packet->delayed_work was initialized.
 */
अटल व्योम
batadv_क्रमw_packet_bcast_queue(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_क्रमw_packet *क्रमw_packet,
			       अचिन्हित दीर्घ send_समय)
अणु
	batadv_क्रमw_packet_queue(क्रमw_packet, &bat_priv->क्रमw_bcast_list_lock,
				 &bat_priv->क्रमw_bcast_list, send_समय);
पूर्ण

/**
 * batadv_क्रमw_packet_ogmv1_queue() - try to queue an OGMv1 packet
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @क्रमw_packet: the क्रमwarding packet to queue
 * @send_समय: बारtamp (jअगरfies) when the packet is to be sent
 *
 * This function tries to (re)queue an OGMv1 packet.
 *
 * Caller needs to ensure that क्रमw_packet->delayed_work was initialized.
 */
व्योम batadv_क्रमw_packet_ogmv1_queue(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_क्रमw_packet *क्रमw_packet,
				    अचिन्हित दीर्घ send_समय)
अणु
	batadv_क्रमw_packet_queue(क्रमw_packet, &bat_priv->क्रमw_bat_list_lock,
				 &bat_priv->क्रमw_bat_list, send_समय);
पूर्ण

/**
 * batadv_add_bcast_packet_to_list() - queue broadcast packet क्रम multiple sends
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: broadcast packet to add
 * @delay: number of jअगरfies to रुको beक्रमe sending
 * @own_packet: true अगर it is a self-generated broadcast packet
 *
 * add a broadcast packet to the queue and setup समयrs. broadcast packets
 * are sent multiple बार to increase probability क्रम being received.
 *
 * The skb is not consumed, so the caller should make sure that the
 * skb is मुक्तd.
 *
 * Return: NETDEV_TX_OK on success and NETDEV_TX_BUSY on errors.
 */
पूर्णांक batadv_add_bcast_packet_to_list(काष्ठा batadv_priv *bat_priv,
				    स्थिर काष्ठा sk_buff *skb,
				    अचिन्हित दीर्घ delay,
				    bool own_packet)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर;
	काष्ठा batadv_क्रमw_packet *क्रमw_packet;
	काष्ठा batadv_bcast_packet *bcast_packet;
	काष्ठा sk_buff *newskb;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ err;

	newskb = skb_copy(skb, GFP_ATOMIC);
	अगर (!newskb) अणु
		batadv_hardअगर_put(primary_अगर);
		जाओ err;
	पूर्ण

	क्रमw_packet = batadv_क्रमw_packet_alloc(primary_अगर, शून्य,
					       &bat_priv->bcast_queue_left,
					       bat_priv, newskb);
	batadv_hardअगर_put(primary_अगर);
	अगर (!क्रमw_packet)
		जाओ err_packet_मुक्त;

	/* as we have a copy now, it is safe to decrease the TTL */
	bcast_packet = (काष्ठा batadv_bcast_packet *)newskb->data;
	bcast_packet->ttl--;

	क्रमw_packet->own = own_packet;

	INIT_DELAYED_WORK(&क्रमw_packet->delayed_work,
			  batadv_send_outstanding_bcast_packet);

	batadv_क्रमw_packet_bcast_queue(bat_priv, क्रमw_packet, jअगरfies + delay);
	वापस NETDEV_TX_OK;

err_packet_मुक्त:
	kमुक्त_skb(newskb);
err:
	वापस NETDEV_TX_BUSY;
पूर्ण

/**
 * batadv_क्रमw_packet_bcasts_left() - check अगर a retransmission is necessary
 * @क्रमw_packet: the क्रमwarding packet to check
 * @hard_अगरace: the पूर्णांकerface to check on
 *
 * Checks whether a given packet has any (re)transmissions left on the provided
 * पूर्णांकerface.
 *
 * hard_अगरace may be शून्य: In that हाल the number of transmissions this skb had
 * so far is compared with the maximum amount of retransmissions independent of
 * any पूर्णांकerface instead.
 *
 * Return: True अगर (re)transmissions are left, false otherwise.
 */
अटल bool
batadv_क्रमw_packet_bcasts_left(काष्ठा batadv_क्रमw_packet *क्रमw_packet,
			       काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अचिन्हित पूर्णांक max;

	अगर (hard_अगरace)
		max = hard_अगरace->num_bcasts;
	अन्यथा
		max = BATADV_NUM_BCASTS_MAX;

	वापस BATADV_SKB_CB(क्रमw_packet->skb)->num_bcasts < max;
पूर्ण

/**
 * batadv_क्रमw_packet_bcasts_inc() - increment retransmission counter of a
 *  packet
 * @क्रमw_packet: the packet to increase the counter क्रम
 */
अटल व्योम
batadv_क्रमw_packet_bcasts_inc(काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	BATADV_SKB_CB(क्रमw_packet->skb)->num_bcasts++;
पूर्ण

/**
 * batadv_क्रमw_packet_is_rebroadcast() - check packet क्रम previous transmissions
 * @क्रमw_packet: the packet to check
 *
 * Return: True अगर this packet was transmitted beक्रमe, false otherwise.
 */
bool batadv_क्रमw_packet_is_rebroadcast(काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	वापस BATADV_SKB_CB(क्रमw_packet->skb)->num_bcasts > 0;
पूर्ण

अटल व्योम batadv_send_outstanding_bcast_packet(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_hardअगर_neigh_node *neigh_node;
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_क्रमw_packet *क्रमw_packet;
	काष्ठा batadv_bcast_packet *bcast_packet;
	काष्ठा sk_buff *skb1;
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_priv *bat_priv;
	अचिन्हित दीर्घ send_समय = jअगरfies + msecs_to_jअगरfies(5);
	bool dropped = false;
	u8 *neigh_addr;
	u8 *orig_neigh;
	पूर्णांक ret = 0;

	delayed_work = to_delayed_work(work);
	क्रमw_packet = container_of(delayed_work, काष्ठा batadv_क्रमw_packet,
				   delayed_work);
	soft_अगरace = क्रमw_packet->अगर_incoming->soft_अगरace;
	bat_priv = netdev_priv(soft_अगरace);

	अगर (atomic_पढ़ो(&bat_priv->mesh_state) == BATADV_MESH_DEACTIVATING) अणु
		dropped = true;
		जाओ out;
	पूर्ण

	अगर (batadv_dat_drop_broadcast_packet(bat_priv, क्रमw_packet)) अणु
		dropped = true;
		जाओ out;
	पूर्ण

	bcast_packet = (काष्ठा batadv_bcast_packet *)क्रमw_packet->skb->data;

	/* rebroadcast packet */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->soft_अगरace != soft_अगरace)
			जारी;

		अगर (!batadv_क्रमw_packet_bcasts_left(क्रमw_packet, hard_अगरace))
			जारी;

		अगर (क्रमw_packet->own) अणु
			neigh_node = शून्य;
		पूर्ण अन्यथा अणु
			neigh_addr = eth_hdr(क्रमw_packet->skb)->h_source;
			neigh_node = batadv_hardअगर_neigh_get(hard_अगरace,
							     neigh_addr);
		पूर्ण

		orig_neigh = neigh_node ? neigh_node->orig : शून्य;

		ret = batadv_hardअगर_no_broadcast(hard_अगरace, bcast_packet->orig,
						 orig_neigh);

		अगर (ret) अणु
			अक्षर *type;

			चयन (ret) अणु
			हाल BATADV_HARDIF_BCAST_NORECIPIENT:
				type = "no neighbor";
				अवरोध;
			हाल BATADV_HARDIF_BCAST_DUPFWD:
				type = "single neighbor is source";
				अवरोध;
			हाल BATADV_HARDIF_BCAST_DUPORIG:
				type = "single neighbor is originator";
				अवरोध;
			शेष:
				type = "unknown";
			पूर्ण

			batadv_dbg(BATADV_DBG_BATMAN, bat_priv, "BCAST packet from orig %pM on %s suppressed: %s\n",
				   bcast_packet->orig,
				   hard_अगरace->net_dev->name, type);

			अगर (neigh_node)
				batadv_hardअगर_neigh_put(neigh_node);

			जारी;
		पूर्ण

		अगर (neigh_node)
			batadv_hardअगर_neigh_put(neigh_node);

		अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
			जारी;

		/* send a copy of the saved skb */
		skb1 = skb_clone(क्रमw_packet->skb, GFP_ATOMIC);
		अगर (skb1)
			batadv_send_broadcast_skb(skb1, hard_अगरace);

		batadv_hardअगर_put(hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();

	batadv_क्रमw_packet_bcasts_inc(क्रमw_packet);

	/* अगर we still have some more bcasts to send */
	अगर (batadv_क्रमw_packet_bcasts_left(क्रमw_packet, शून्य)) अणु
		batadv_क्रमw_packet_bcast_queue(bat_priv, क्रमw_packet,
					       send_समय);
		वापस;
	पूर्ण

out:
	/* करो we get something क्रम मुक्त()? */
	अगर (batadv_क्रमw_packet_steal(क्रमw_packet,
				     &bat_priv->क्रमw_bcast_list_lock))
		batadv_क्रमw_packet_मुक्त(क्रमw_packet, dropped);
पूर्ण

/**
 * batadv_purge_outstanding_packets() - stop/purge scheduled bcast/OGMv1 packets
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hard_अगरace: the hard पूर्णांकerface to cancel and purge bcast/ogm packets on
 *
 * This method cancels and purges any broadcast and OGMv1 packet on the given
 * hard_अगरace. If hard_अगरace is शून्य, broadcast and OGMv1 packets on all hard
 * पूर्णांकerfaces will be canceled and purged.
 *
 * This function might sleep.
 */
व्योम
batadv_purge_outstanding_packets(काष्ठा batadv_priv *bat_priv,
				 स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा hlist_head head = HLIST_HEAD_INIT;

	अगर (hard_अगरace)
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s(): %s\n",
			   __func__, hard_अगरace->net_dev->name);
	अन्यथा
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s()\n", __func__);

	/* claim bcast list क्रम मुक्त() */
	spin_lock_bh(&bat_priv->क्रमw_bcast_list_lock);
	batadv_क्रमw_packet_list_steal(&bat_priv->क्रमw_bcast_list, &head,
				      hard_अगरace);
	spin_unlock_bh(&bat_priv->क्रमw_bcast_list_lock);

	/* claim baपंचांगan packet list क्रम मुक्त() */
	spin_lock_bh(&bat_priv->क्रमw_bat_list_lock);
	batadv_क्रमw_packet_list_steal(&bat_priv->क्रमw_bat_list, &head,
				      hard_अगरace);
	spin_unlock_bh(&bat_priv->क्रमw_bat_list_lock);

	/* then cancel or रुको क्रम packet workers to finish and मुक्त */
	batadv_क्रमw_packet_list_मुक्त(&head);
पूर्ण
