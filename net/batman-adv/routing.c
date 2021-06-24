<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "routing.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kref.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "bitarray.h"
#समावेश "bridge_loop_avoidance.h"
#समावेश "distributed-arp-table.h"
#समावेश "fragmentation.h"
#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "network-coding.h"
#समावेश "originator.h"
#समावेश "send.h"
#समावेश "soft-interface.h"
#समावेश "tp_meter.h"
#समावेश "translation-table.h"
#समावेश "tvlv.h"

अटल पूर्णांक batadv_route_unicast_packet(काष्ठा sk_buff *skb,
				       काष्ठा batadv_hard_अगरace *recv_अगर);

/**
 * _batadv_update_route() - set the router क्रम this originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be configured
 * @recv_अगर: the receive पूर्णांकerface क्रम which this route is set
 * @neigh_node: neighbor which should be the next router
 *
 * This function करोes not perक्रमm any error checks
 */
अटल व्योम _batadv_update_route(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_orig_node *orig_node,
				 काष्ठा batadv_hard_अगरace *recv_अगर,
				 काष्ठा batadv_neigh_node *neigh_node)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_neigh_node *curr_router;

	orig_अगरinfo = batadv_orig_अगरinfo_get(orig_node, recv_अगर);
	अगर (!orig_अगरinfo)
		वापस;

	spin_lock_bh(&orig_node->neigh_list_lock);
	/* curr_router used earlier may not be the current orig_अगरinfo->router
	 * anymore because it was dereferenced outside of the neigh_list_lock
	 * रक्षित region. After the new best neighbor has replace the current
	 * best neighbor the reference counter needs to decrease. Consequently,
	 * the code needs to ensure the curr_router variable contains a poपूर्णांकer
	 * to the replaced best neighbor.
	 */

	/* increase refcount of new best neighbor */
	अगर (neigh_node)
		kref_get(&neigh_node->refcount);

	curr_router = rcu_replace_poपूर्णांकer(orig_अगरinfo->router, neigh_node,
					  true);
	spin_unlock_bh(&orig_node->neigh_list_lock);
	batadv_orig_अगरinfo_put(orig_अगरinfo);

	/* route deleted */
	अगर (curr_router && !neigh_node) अणु
		batadv_dbg(BATADV_DBG_ROUTES, bat_priv,
			   "Deleting route towards: %pM\n", orig_node->orig);
		batadv_tt_global_del_orig(bat_priv, orig_node, -1,
					  "Deleted route towards originator");

	/* route added */
	पूर्ण अन्यथा अगर (!curr_router && neigh_node) अणु
		batadv_dbg(BATADV_DBG_ROUTES, bat_priv,
			   "Adding route towards: %pM (via %pM)\n",
			   orig_node->orig, neigh_node->addr);
	/* route changed */
	पूर्ण अन्यथा अगर (neigh_node && curr_router) अणु
		batadv_dbg(BATADV_DBG_ROUTES, bat_priv,
			   "Changing route towards: %pM (now via %pM - was via %pM)\n",
			   orig_node->orig, neigh_node->addr,
			   curr_router->addr);
	पूर्ण

	/* decrease refcount of previous best neighbor */
	अगर (curr_router)
		batadv_neigh_node_put(curr_router);
पूर्ण

/**
 * batadv_update_route() - set the router क्रम this originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be configured
 * @recv_अगर: the receive पूर्णांकerface क्रम which this route is set
 * @neigh_node: neighbor which should be the next router
 */
व्योम batadv_update_route(काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_orig_node *orig_node,
			 काष्ठा batadv_hard_अगरace *recv_अगर,
			 काष्ठा batadv_neigh_node *neigh_node)
अणु
	काष्ठा batadv_neigh_node *router = शून्य;

	अगर (!orig_node)
		जाओ out;

	router = batadv_orig_router_get(orig_node, recv_अगर);

	अगर (router != neigh_node)
		_batadv_update_route(bat_priv, orig_node, recv_अगर, neigh_node);

out:
	अगर (router)
		batadv_neigh_node_put(router);
पूर्ण

/**
 * batadv_winकरोw_रक्षित() - checks whether the host restarted and is in the
 *  protection समय.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @seq_num_dअगरf: dअगरference between the current/received sequence number and
 *  the last sequence number
 * @seq_old_max_dअगरf: maximum age of sequence number not considered as restart
 * @last_reset: jअगरfies बारtamp of the last reset, will be updated when reset
 *  is detected
 * @protection_started: is set to true अगर the protection winकरोw was started,
 *   करोesn't change otherwise.
 *
 * Return:
 *  false अगर the packet is to be accepted.
 *  true अगर the packet is to be ignored.
 */
bool batadv_winकरोw_रक्षित(काष्ठा batadv_priv *bat_priv, s32 seq_num_dअगरf,
			     s32 seq_old_max_dअगरf, अचिन्हित दीर्घ *last_reset,
			     bool *protection_started)
अणु
	अगर (seq_num_dअगरf <= -seq_old_max_dअगरf ||
	    seq_num_dअगरf >= BATADV_EXPECTED_SEQNO_RANGE) अणु
		अगर (!batadv_has_समयd_out(*last_reset,
					  BATADV_RESET_PROTECTION_MS))
			वापस true;

		*last_reset = jअगरfies;
		अगर (protection_started)
			*protection_started = true;
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "old packet received, start protection\n");
	पूर्ण

	वापस false;
पूर्ण

/**
 * batadv_check_management_packet() - Check preconditions क्रम management packets
 * @skb: incoming packet buffer
 * @hard_अगरace: incoming hard पूर्णांकerface
 * @header_len: minimal header length of packet type
 *
 * Return: true when management preconditions are met, false otherwise
 */
bool batadv_check_management_packet(काष्ठा sk_buff *skb,
				    काष्ठा batadv_hard_अगरace *hard_अगरace,
				    पूर्णांक header_len)
अणु
	काष्ठा ethhdr *ethhdr;

	/* drop packet अगर it has not necessary minimum size */
	अगर (unlikely(!pskb_may_pull(skb, header_len)))
		वापस false;

	ethhdr = eth_hdr(skb);

	/* packet with broadcast indication but unicast recipient */
	अगर (!is_broadcast_ether_addr(ethhdr->h_dest))
		वापस false;

	/* packet with invalid sender address */
	अगर (!is_valid_ether_addr(ethhdr->h_source))
		वापस false;

	/* create a copy of the skb, अगर needed, to modअगरy it. */
	अगर (skb_cow(skb, 0) < 0)
		वापस false;

	/* keep skb linear */
	अगर (skb_linearize(skb) < 0)
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_recv_my_icmp_packet() - receive an icmp packet locally
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: icmp packet to process
 *
 * Return: NET_RX_SUCCESS अगर the packet has been consumed or NET_RX_DROP
 * otherwise.
 */
अटल पूर्णांक batadv_recv_my_icmp_packet(काष्ठा batadv_priv *bat_priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_icmp_header *icmph;
	पूर्णांक res, ret = NET_RX_DROP;

	icmph = (काष्ठा batadv_icmp_header *)skb->data;

	चयन (icmph->msg_type) अणु
	हाल BATADV_ECHO_REQUEST:
		/* answer echo request (ping) */
		primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
		अगर (!primary_अगर)
			जाओ out;

		/* get routing inक्रमmation */
		orig_node = batadv_orig_hash_find(bat_priv, icmph->orig);
		अगर (!orig_node)
			जाओ out;

		/* create a copy of the skb, अगर needed, to modअगरy it. */
		अगर (skb_cow(skb, ETH_HLEN) < 0)
			जाओ out;

		icmph = (काष्ठा batadv_icmp_header *)skb->data;

		ether_addr_copy(icmph->dst, icmph->orig);
		ether_addr_copy(icmph->orig, primary_अगर->net_dev->dev_addr);
		icmph->msg_type = BATADV_ECHO_REPLY;
		icmph->ttl = BATADV_TTL;

		res = batadv_send_skb_to_orig(skb, orig_node, शून्य);
		अगर (res == NET_XMIT_SUCCESS)
			ret = NET_RX_SUCCESS;

		/* skb was consumed */
		skb = शून्य;
		अवरोध;
	हाल BATADV_TP:
		अगर (!pskb_may_pull(skb, माप(काष्ठा batadv_icmp_tp_packet)))
			जाओ out;

		batadv_tp_meter_recv(bat_priv, skb);
		ret = NET_RX_SUCCESS;
		/* skb was consumed */
		skb = शून्य;
		जाओ out;
	शेष:
		/* drop unknown type */
		जाओ out;
	पूर्ण
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (orig_node)
		batadv_orig_node_put(orig_node);

	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल पूर्णांक batadv_recv_icmp_ttl_exceeded(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_icmp_packet *icmp_packet;
	पूर्णांक res, ret = NET_RX_DROP;

	icmp_packet = (काष्ठा batadv_icmp_packet *)skb->data;

	/* send TTL exceeded अगर packet is an echo request (traceroute) */
	अगर (icmp_packet->msg_type != BATADV_ECHO_REQUEST) अणु
		pr_debug("Warning - can't forward icmp packet from %pM to %pM: ttl exceeded\n",
			 icmp_packet->orig, icmp_packet->dst);
		जाओ out;
	पूर्ण

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	/* get routing inक्रमmation */
	orig_node = batadv_orig_hash_find(bat_priv, icmp_packet->orig);
	अगर (!orig_node)
		जाओ out;

	/* create a copy of the skb, अगर needed, to modअगरy it. */
	अगर (skb_cow(skb, ETH_HLEN) < 0)
		जाओ out;

	icmp_packet = (काष्ठा batadv_icmp_packet *)skb->data;

	ether_addr_copy(icmp_packet->dst, icmp_packet->orig);
	ether_addr_copy(icmp_packet->orig, primary_अगर->net_dev->dev_addr);
	icmp_packet->msg_type = BATADV_TTL_EXCEEDED;
	icmp_packet->ttl = BATADV_TTL;

	res = batadv_send_skb_to_orig(skb, orig_node, शून्य);
	अगर (res == NET_RX_SUCCESS)
		ret = NET_XMIT_SUCCESS;

	/* skb was consumed */
	skb = शून्य;

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (orig_node)
		batadv_orig_node_put(orig_node);

	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_recv_icmp_packet() - Process incoming icmp packet
 * @skb: incoming packet buffer
 * @recv_अगर: incoming hard पूर्णांकerface
 *
 * Return: NET_RX_SUCCESS on success or NET_RX_DROP in हाल of failure
 */
पूर्णांक batadv_recv_icmp_packet(काष्ठा sk_buff *skb,
			    काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_icmp_header *icmph;
	काष्ठा batadv_icmp_packet_rr *icmp_packet_rr;
	काष्ठा ethhdr *ethhdr;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	पूर्णांक hdr_size = माप(काष्ठा batadv_icmp_header);
	पूर्णांक res, ret = NET_RX_DROP;

	/* drop packet अगर it has not necessary minimum size */
	अगर (unlikely(!pskb_may_pull(skb, hdr_size)))
		जाओ मुक्त_skb;

	ethhdr = eth_hdr(skb);

	/* packet with unicast indication but non-unicast recipient */
	अगर (!is_valid_ether_addr(ethhdr->h_dest))
		जाओ मुक्त_skb;

	/* packet with broadcast/multicast sender address */
	अगर (is_multicast_ether_addr(ethhdr->h_source))
		जाओ मुक्त_skb;

	/* not क्रम me */
	अगर (!batadv_is_my_mac(bat_priv, ethhdr->h_dest))
		जाओ मुक्त_skb;

	icmph = (काष्ठा batadv_icmp_header *)skb->data;

	/* add record route inक्रमmation अगर not full */
	अगर ((icmph->msg_type == BATADV_ECHO_REPLY ||
	     icmph->msg_type == BATADV_ECHO_REQUEST) &&
	    skb->len >= माप(काष्ठा batadv_icmp_packet_rr)) अणु
		अगर (skb_linearize(skb) < 0)
			जाओ मुक्त_skb;

		/* create a copy of the skb, अगर needed, to modअगरy it. */
		अगर (skb_cow(skb, ETH_HLEN) < 0)
			जाओ मुक्त_skb;

		ethhdr = eth_hdr(skb);
		icmph = (काष्ठा batadv_icmp_header *)skb->data;
		icmp_packet_rr = (काष्ठा batadv_icmp_packet_rr *)icmph;
		अगर (icmp_packet_rr->rr_cur >= BATADV_RR_LEN)
			जाओ मुक्त_skb;

		ether_addr_copy(icmp_packet_rr->rr[icmp_packet_rr->rr_cur],
				ethhdr->h_dest);
		icmp_packet_rr->rr_cur++;
	पूर्ण

	/* packet क्रम me */
	अगर (batadv_is_my_mac(bat_priv, icmph->dst))
		वापस batadv_recv_my_icmp_packet(bat_priv, skb);

	/* TTL exceeded */
	अगर (icmph->ttl < 2)
		वापस batadv_recv_icmp_ttl_exceeded(bat_priv, skb);

	/* get routing inक्रमmation */
	orig_node = batadv_orig_hash_find(bat_priv, icmph->dst);
	अगर (!orig_node)
		जाओ मुक्त_skb;

	/* create a copy of the skb, अगर needed, to modअगरy it. */
	अगर (skb_cow(skb, ETH_HLEN) < 0)
		जाओ put_orig_node;

	icmph = (काष्ठा batadv_icmp_header *)skb->data;

	/* decrement ttl */
	icmph->ttl--;

	/* route it */
	res = batadv_send_skb_to_orig(skb, orig_node, recv_अगर);
	अगर (res == NET_XMIT_SUCCESS)
		ret = NET_RX_SUCCESS;

	/* skb was consumed */
	skb = शून्य;

put_orig_node:
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_check_unicast_packet() - Check क्रम malक्रमmed unicast packets
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: packet to check
 * @hdr_size: size of header to pull
 *
 * Checks क्रम लघु header and bad addresses in the given packet.
 *
 * Return: negative value when check fails and 0 otherwise. The negative value
 * depends on the reason: -ENODATA क्रम bad header, -EBADR क्रम broadcast
 * destination or source, and -EREMOTE क्रम non-local (other host) destination.
 */
अटल पूर्णांक batadv_check_unicast_packet(काष्ठा batadv_priv *bat_priv,
				       काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	काष्ठा ethhdr *ethhdr;

	/* drop packet अगर it has not necessary minimum size */
	अगर (unlikely(!pskb_may_pull(skb, hdr_size)))
		वापस -ENODATA;

	ethhdr = eth_hdr(skb);

	/* packet with unicast indication but non-unicast recipient */
	अगर (!is_valid_ether_addr(ethhdr->h_dest))
		वापस -EBADR;

	/* packet with broadcast/multicast sender address */
	अगर (is_multicast_ether_addr(ethhdr->h_source))
		वापस -EBADR;

	/* not क्रम me */
	अगर (!batadv_is_my_mac(bat_priv, ethhdr->h_dest))
		वापस -EREMOTE;

	वापस 0;
पूर्ण

/**
 * batadv_last_bonding_get() - Get last_bonding_candidate of orig_node
 * @orig_node: originator node whose last bonding candidate should be retrieved
 *
 * Return: last bonding candidate of router or शून्य अगर not found
 *
 * The object is वापसed with refcounter increased by 1.
 */
अटल काष्ठा batadv_orig_अगरinfo *
batadv_last_bonding_get(काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_orig_अगरinfo *last_bonding_candidate;

	spin_lock_bh(&orig_node->neigh_list_lock);
	last_bonding_candidate = orig_node->last_bonding_candidate;

	अगर (last_bonding_candidate)
		kref_get(&last_bonding_candidate->refcount);
	spin_unlock_bh(&orig_node->neigh_list_lock);

	वापस last_bonding_candidate;
पूर्ण

/**
 * batadv_last_bonding_replace() - Replace last_bonding_candidate of orig_node
 * @orig_node: originator node whose bonding candidates should be replaced
 * @new_candidate: new bonding candidate or शून्य
 */
अटल व्योम
batadv_last_bonding_replace(काष्ठा batadv_orig_node *orig_node,
			    काष्ठा batadv_orig_अगरinfo *new_candidate)
अणु
	काष्ठा batadv_orig_अगरinfo *old_candidate;

	spin_lock_bh(&orig_node->neigh_list_lock);
	old_candidate = orig_node->last_bonding_candidate;

	अगर (new_candidate)
		kref_get(&new_candidate->refcount);
	orig_node->last_bonding_candidate = new_candidate;
	spin_unlock_bh(&orig_node->neigh_list_lock);

	अगर (old_candidate)
		batadv_orig_अगरinfo_put(old_candidate);
पूर्ण

/**
 * batadv_find_router() - find a suitable router क्रम this originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: the destination node
 * @recv_अगर: poपूर्णांकer to पूर्णांकerface this packet was received on
 *
 * Return: the router which should be used क्रम this orig_node on
 * this पूर्णांकerface, or शून्य अगर not available.
 */
काष्ठा batadv_neigh_node *
batadv_find_router(काष्ठा batadv_priv *bat_priv,
		   काष्ठा batadv_orig_node *orig_node,
		   काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_algo_ops *bao = bat_priv->algo_ops;
	काष्ठा batadv_neigh_node *first_candidate_router = शून्य;
	काष्ठा batadv_neigh_node *next_candidate_router = शून्य;
	काष्ठा batadv_neigh_node *router, *cand_router = शून्य;
	काष्ठा batadv_neigh_node *last_cand_router = शून्य;
	काष्ठा batadv_orig_अगरinfo *cand, *first_candidate = शून्य;
	काष्ठा batadv_orig_अगरinfo *next_candidate = शून्य;
	काष्ठा batadv_orig_अगरinfo *last_candidate;
	bool last_candidate_found = false;

	अगर (!orig_node)
		वापस शून्य;

	router = batadv_orig_router_get(orig_node, recv_अगर);

	अगर (!router)
		वापस router;

	/* only consider bonding क्रम recv_अगर == BATADV_IF_DEFAULT (first hop)
	 * and अगर activated.
	 */
	अगर (!(recv_अगर == BATADV_IF_DEFAULT && atomic_पढ़ो(&bat_priv->bonding)))
		वापस router;

	/* bonding: loop through the list of possible routers found
	 * क्रम the various outgoing पूर्णांकerfaces and find a candidate after
	 * the last chosen bonding candidate (next_candidate). If no such
	 * router is found, use the first candidate found (the previously
	 * chosen bonding candidate might have been the last one in the list).
	 * If this can't be found either, वापस the previously chosen
	 * router - obviously there are no other candidates.
	 */
	rcu_पढ़ो_lock();
	last_candidate = batadv_last_bonding_get(orig_node);
	अगर (last_candidate)
		last_cand_router = rcu_dereference(last_candidate->router);

	hlist_क्रम_each_entry_rcu(cand, &orig_node->अगरinfo_list, list) अणु
		/* acquire some काष्ठाures and references ... */
		अगर (!kref_get_unless_zero(&cand->refcount))
			जारी;

		cand_router = rcu_dereference(cand->router);
		अगर (!cand_router)
			जाओ next;

		अगर (!kref_get_unless_zero(&cand_router->refcount)) अणु
			cand_router = शून्य;
			जाओ next;
		पूर्ण

		/* alternative candidate should be good enough to be
		 * considered
		 */
		अगर (!bao->neigh.is_similar_or_better(cand_router,
						     cand->अगर_outgoing, router,
						     recv_अगर))
			जाओ next;

		/* करोn't use the same router twice */
		अगर (last_cand_router == cand_router)
			जाओ next;

		/* mark the first possible candidate */
		अगर (!first_candidate) अणु
			kref_get(&cand_router->refcount);
			kref_get(&cand->refcount);
			first_candidate = cand;
			first_candidate_router = cand_router;
		पूर्ण

		/* check अगर the loop has alपढ़ोy passed the previously selected
		 * candidate ... this function should select the next candidate
		 * AFTER the previously used bonding candidate.
		 */
		अगर (!last_candidate || last_candidate_found) अणु
			next_candidate = cand;
			next_candidate_router = cand_router;
			अवरोध;
		पूर्ण

		अगर (last_candidate == cand)
			last_candidate_found = true;
next:
		/* मुक्त references */
		अगर (cand_router) अणु
			batadv_neigh_node_put(cand_router);
			cand_router = शून्य;
		पूर्ण
		batadv_orig_अगरinfo_put(cand);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* After finding candidates, handle the three हालs:
	 * 1) there is a next candidate, use that
	 * 2) there is no next candidate, use the first of the list
	 * 3) there is no candidate at all, वापस the शेष router
	 */
	अगर (next_candidate) अणु
		batadv_neigh_node_put(router);

		kref_get(&next_candidate_router->refcount);
		router = next_candidate_router;
		batadv_last_bonding_replace(orig_node, next_candidate);
	पूर्ण अन्यथा अगर (first_candidate) अणु
		batadv_neigh_node_put(router);

		kref_get(&first_candidate_router->refcount);
		router = first_candidate_router;
		batadv_last_bonding_replace(orig_node, first_candidate);
	पूर्ण अन्यथा अणु
		batadv_last_bonding_replace(orig_node, शून्य);
	पूर्ण

	/* cleanup of candidates */
	अगर (first_candidate) अणु
		batadv_neigh_node_put(first_candidate_router);
		batadv_orig_अगरinfo_put(first_candidate);
	पूर्ण

	अगर (next_candidate) अणु
		batadv_neigh_node_put(next_candidate_router);
		batadv_orig_अगरinfo_put(next_candidate);
	पूर्ण

	अगर (last_candidate)
		batadv_orig_अगरinfo_put(last_candidate);

	वापस router;
पूर्ण

अटल पूर्णांक batadv_route_unicast_packet(काष्ठा sk_buff *skb,
				       काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);
	पूर्णांक res, hdr_len, ret = NET_RX_DROP;
	अचिन्हित पूर्णांक len;

	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;

	/* TTL exceeded */
	अगर (unicast_packet->ttl < 2) अणु
		pr_debug("Warning - can't forward unicast packet from %pM to %pM: ttl exceeded\n",
			 ethhdr->h_source, unicast_packet->dest);
		जाओ मुक्त_skb;
	पूर्ण

	/* get routing inक्रमmation */
	orig_node = batadv_orig_hash_find(bat_priv, unicast_packet->dest);

	अगर (!orig_node)
		जाओ मुक्त_skb;

	/* create a copy of the skb, अगर needed, to modअगरy it. */
	अगर (skb_cow(skb, ETH_HLEN) < 0)
		जाओ put_orig_node;

	/* decrement ttl */
	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;
	unicast_packet->ttl--;

	चयन (unicast_packet->packet_type) अणु
	हाल BATADV_UNICAST_4ADDR:
		hdr_len = माप(काष्ठा batadv_unicast_4addr_packet);
		अवरोध;
	हाल BATADV_UNICAST:
		hdr_len = माप(काष्ठा batadv_unicast_packet);
		अवरोध;
	शेष:
		/* other packet types not supported - yet */
		hdr_len = -1;
		अवरोध;
	पूर्ण

	अगर (hdr_len > 0)
		batadv_skb_set_priority(skb, hdr_len);

	len = skb->len;
	res = batadv_send_skb_to_orig(skb, orig_node, recv_अगर);

	/* translate transmit result पूर्णांकo receive result */
	अगर (res == NET_XMIT_SUCCESS) अणु
		ret = NET_RX_SUCCESS;
		/* skb was transmitted and consumed */
		batadv_inc_counter(bat_priv, BATADV_CNT_FORWARD);
		batadv_add_counter(bat_priv, BATADV_CNT_FORWARD_BYTES,
				   len + ETH_HLEN);
	पूर्ण

	/* skb was consumed */
	skb = शून्य;

put_orig_node:
	batadv_orig_node_put(orig_node);
मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_reroute_unicast_packet() - update the unicast header क्रम re-routing
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: unicast packet to process
 * @unicast_packet: the unicast header to be updated
 * @dst_addr: the payload destination
 * @vid: VLAN identअगरier
 *
 * Search the translation table क्रम dst_addr and update the unicast header with
 * the new corresponding inक्रमmation (originator address where the destination
 * client currently is and its known TTVN)
 *
 * Return: true अगर the packet header has been updated, false otherwise
 */
अटल bool
batadv_reroute_unicast_packet(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			      काष्ठा batadv_unicast_packet *unicast_packet,
			      u8 *dst_addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	bool ret = false;
	u8 *orig_addr, orig_ttvn;

	अगर (batadv_is_my_client(bat_priv, dst_addr, vid)) अणु
		primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
		अगर (!primary_अगर)
			जाओ out;
		orig_addr = primary_अगर->net_dev->dev_addr;
		orig_ttvn = (u8)atomic_पढ़ो(&bat_priv->tt.vn);
	पूर्ण अन्यथा अणु
		orig_node = batadv_transtable_search(bat_priv, शून्य, dst_addr,
						     vid);
		अगर (!orig_node)
			जाओ out;

		अगर (batadv_compare_eth(orig_node->orig, unicast_packet->dest))
			जाओ out;

		orig_addr = orig_node->orig;
		orig_ttvn = (u8)atomic_पढ़ो(&orig_node->last_ttvn);
	पूर्ण

	/* update the packet header */
	skb_postpull_rcsum(skb, unicast_packet, माप(*unicast_packet));
	ether_addr_copy(unicast_packet->dest, orig_addr);
	unicast_packet->ttvn = orig_ttvn;
	skb_postpush_rcsum(skb, unicast_packet, माप(*unicast_packet));

	ret = true;
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (orig_node)
		batadv_orig_node_put(orig_node);

	वापस ret;
पूर्ण

अटल bool batadv_check_unicast_ttvn(काष्ठा batadv_priv *bat_priv,
				      काष्ठा sk_buff *skb, पूर्णांक hdr_len)
अणु
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	काष्ठा batadv_orig_node *orig_node;
	u8 curr_ttvn, old_ttvn;
	काष्ठा ethhdr *ethhdr;
	अचिन्हित लघु vid;
	पूर्णांक is_old_ttvn;

	/* check अगर there is enough data beक्रमe accessing it */
	अगर (!pskb_may_pull(skb, hdr_len + ETH_HLEN))
		वापस false;

	/* create a copy of the skb (in हाल of क्रम re-routing) to modअगरy it. */
	अगर (skb_cow(skb, माप(*unicast_packet)) < 0)
		वापस false;

	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;
	vid = batadv_get_vid(skb, hdr_len);
	ethhdr = (काष्ठा ethhdr *)(skb->data + hdr_len);

	/* करो not reroute multicast frames in a unicast header */
	अगर (is_multicast_ether_addr(ethhdr->h_dest))
		वापस true;

	/* check अगर the destination client was served by this node and it is now
	 * roaming. In this हाल, it means that the node has got a ROAM_ADV
	 * message and that it knows the new destination in the mesh to re-route
	 * the packet to
	 */
	अगर (batadv_tt_local_client_is_roaming(bat_priv, ethhdr->h_dest, vid)) अणु
		अगर (batadv_reroute_unicast_packet(bat_priv, skb, unicast_packet,
						  ethhdr->h_dest, vid))
			batadv_dbg_ratelimited(BATADV_DBG_TT,
					       bat_priv,
					       "Rerouting unicast packet to %pM (dst=%pM): Local Roaming\n",
					       unicast_packet->dest,
					       ethhdr->h_dest);
		/* at this poपूर्णांक the mesh destination should have been
		 * substituted with the originator address found in the global
		 * table. If not, let the packet go untouched anyway because
		 * there is nothing the node can करो
		 */
		वापस true;
	पूर्ण

	/* retrieve the TTVN known by this node क्रम the packet destination. This
	 * value is used later to check अगर the node which sent (or re-routed
	 * last समय) the packet had an updated inक्रमmation or not
	 */
	curr_ttvn = (u8)atomic_पढ़ो(&bat_priv->tt.vn);
	अगर (!batadv_is_my_mac(bat_priv, unicast_packet->dest)) अणु
		orig_node = batadv_orig_hash_find(bat_priv,
						  unicast_packet->dest);
		/* अगर it is not possible to find the orig_node representing the
		 * destination, the packet can immediately be dropped as it will
		 * not be possible to deliver it
		 */
		अगर (!orig_node)
			वापस false;

		curr_ttvn = (u8)atomic_पढ़ो(&orig_node->last_ttvn);
		batadv_orig_node_put(orig_node);
	पूर्ण

	/* check अगर the TTVN contained in the packet is fresher than what the
	 * node knows
	 */
	is_old_ttvn = batadv_seq_beक्रमe(unicast_packet->ttvn, curr_ttvn);
	अगर (!is_old_ttvn)
		वापस true;

	old_ttvn = unicast_packet->ttvn;
	/* the packet was क्रमged based on outdated network inक्रमmation. Its
	 * destination can possibly be updated and क्रमwarded towards the new
	 * target host
	 */
	अगर (batadv_reroute_unicast_packet(bat_priv, skb, unicast_packet,
					  ethhdr->h_dest, vid)) अणु
		batadv_dbg_ratelimited(BATADV_DBG_TT, bat_priv,
				       "Rerouting unicast packet to %pM (dst=%pM): TTVN mismatch old_ttvn=%u new_ttvn=%u\n",
				       unicast_packet->dest, ethhdr->h_dest,
				       old_ttvn, curr_ttvn);
		वापस true;
	पूर्ण

	/* the packet has not been re-routed: either the destination is
	 * currently served by this node or there is no destination at all and
	 * it is possible to drop the packet
	 */
	अगर (!batadv_is_my_client(bat_priv, ethhdr->h_dest, vid))
		वापस false;

	/* update the header in order to let the packet be delivered to this
	 * node's soft पूर्णांकerface
	 */
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		वापस false;

	/* update the packet header */
	skb_postpull_rcsum(skb, unicast_packet, माप(*unicast_packet));
	ether_addr_copy(unicast_packet->dest, primary_अगर->net_dev->dev_addr);
	unicast_packet->ttvn = curr_ttvn;
	skb_postpush_rcsum(skb, unicast_packet, माप(*unicast_packet));

	batadv_hardअगर_put(primary_अगर);

	वापस true;
पूर्ण

/**
 * batadv_recv_unhandled_unicast_packet() - receive and process packets which
 *	are in the unicast number space but not yet known to the implementation
 * @skb: unicast tvlv packet to process
 * @recv_अगर: poपूर्णांकer to पूर्णांकerface this packet was received on
 *
 * Return: NET_RX_SUCCESS अगर the packet has been consumed or NET_RX_DROP
 * otherwise.
 */
पूर्णांक batadv_recv_unhandled_unicast_packet(काष्ठा sk_buff *skb,
					 काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	पूर्णांक check, hdr_size = माप(*unicast_packet);

	check = batadv_check_unicast_packet(bat_priv, skb, hdr_size);
	अगर (check < 0)
		जाओ मुक्त_skb;

	/* we करोn't know about this type, drop it. */
	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;
	अगर (batadv_is_my_mac(bat_priv, unicast_packet->dest))
		जाओ मुक्त_skb;

	वापस batadv_route_unicast_packet(skb, recv_अगर);

मुक्त_skb:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

/**
 * batadv_recv_unicast_packet() - Process incoming unicast packet
 * @skb: incoming packet buffer
 * @recv_अगर: incoming hard पूर्णांकerface
 *
 * Return: NET_RX_SUCCESS on success or NET_RX_DROP in हाल of failure
 */
पूर्णांक batadv_recv_unicast_packet(काष्ठा sk_buff *skb,
			       काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा batadv_unicast_4addr_packet *unicast_4addr_packet;
	u8 *orig_addr, *orig_addr_gw;
	काष्ठा batadv_orig_node *orig_node = शून्य, *orig_node_gw = शून्य;
	पूर्णांक check, hdr_size = माप(*unicast_packet);
	क्रमागत batadv_subtype subtype;
	पूर्णांक ret = NET_RX_DROP;
	bool is4addr, is_gw;

	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;
	is4addr = unicast_packet->packet_type == BATADV_UNICAST_4ADDR;
	/* the caller function should have alपढ़ोy pulled 2 bytes */
	अगर (is4addr)
		hdr_size = माप(*unicast_4addr_packet);

	/* function वापसs -EREMOTE क्रम promiscuous packets */
	check = batadv_check_unicast_packet(bat_priv, skb, hdr_size);

	/* Even though the packet is not क्रम us, we might save it to use क्रम
	 * decoding a later received coded packet
	 */
	अगर (check == -EREMOTE)
		batadv_nc_skb_store_snअगरfed_unicast(bat_priv, skb);

	अगर (check < 0)
		जाओ मुक्त_skb;
	अगर (!batadv_check_unicast_ttvn(bat_priv, skb, hdr_size))
		जाओ मुक्त_skb;

	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;

	/* packet क्रम me */
	अगर (batadv_is_my_mac(bat_priv, unicast_packet->dest)) अणु
		/* If this is a unicast packet from another backgone gw,
		 * drop it.
		 */
		orig_addr_gw = eth_hdr(skb)->h_source;
		orig_node_gw = batadv_orig_hash_find(bat_priv, orig_addr_gw);
		अगर (orig_node_gw) अणु
			is_gw = batadv_bla_is_backbone_gw(skb, orig_node_gw,
							  hdr_size);
			batadv_orig_node_put(orig_node_gw);
			अगर (is_gw) अणु
				batadv_dbg(BATADV_DBG_BLA, bat_priv,
					   "%s(): Dropped unicast pkt received from another backbone gw %pM.\n",
					   __func__, orig_addr_gw);
				जाओ मुक्त_skb;
			पूर्ण
		पूर्ण

		अगर (is4addr) अणु
			unicast_4addr_packet =
				(काष्ठा batadv_unicast_4addr_packet *)skb->data;
			subtype = unicast_4addr_packet->subtype;
			batadv_dat_inc_counter(bat_priv, subtype);

			/* Only payload data should be considered क्रम speedy
			 * join. For example, DAT also uses unicast 4addr
			 * types, but those packets should not be considered
			 * क्रम speedy join, since the clients करो not actually
			 * reside at the sending originator.
			 */
			अगर (subtype == BATADV_P_DATA) अणु
				orig_addr = unicast_4addr_packet->src;
				orig_node = batadv_orig_hash_find(bat_priv,
								  orig_addr);
			पूर्ण
		पूर्ण

		अगर (batadv_dat_snoop_incoming_arp_request(bat_priv, skb,
							  hdr_size))
			जाओ rx_success;
		अगर (batadv_dat_snoop_incoming_arp_reply(bat_priv, skb,
							hdr_size))
			जाओ rx_success;

		batadv_dat_snoop_incoming_dhcp_ack(bat_priv, skb, hdr_size);

		batadv_पूर्णांकerface_rx(recv_अगर->soft_अगरace, skb, hdr_size,
				    orig_node);

rx_success:
		अगर (orig_node)
			batadv_orig_node_put(orig_node);

		वापस NET_RX_SUCCESS;
	पूर्ण

	ret = batadv_route_unicast_packet(skb, recv_अगर);
	/* skb was consumed */
	skb = शून्य;

मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_recv_unicast_tvlv() - receive and process unicast tvlv packets
 * @skb: unicast tvlv packet to process
 * @recv_अगर: poपूर्णांकer to पूर्णांकerface this packet was received on
 *
 * Return: NET_RX_SUCCESS अगर the packet has been consumed or NET_RX_DROP
 * otherwise.
 */
पूर्णांक batadv_recv_unicast_tvlv(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_unicast_tvlv_packet *unicast_tvlv_packet;
	अचिन्हित अक्षर *tvlv_buff;
	u16 tvlv_buff_len;
	पूर्णांक hdr_size = माप(*unicast_tvlv_packet);
	पूर्णांक ret = NET_RX_DROP;

	अगर (batadv_check_unicast_packet(bat_priv, skb, hdr_size) < 0)
		जाओ मुक्त_skb;

	/* the header is likely to be modअगरied जबतक क्रमwarding */
	अगर (skb_cow(skb, hdr_size) < 0)
		जाओ मुक्त_skb;

	/* packet needs to be linearized to access the tvlv content */
	अगर (skb_linearize(skb) < 0)
		जाओ मुक्त_skb;

	unicast_tvlv_packet = (काष्ठा batadv_unicast_tvlv_packet *)skb->data;

	tvlv_buff = (अचिन्हित अक्षर *)(skb->data + hdr_size);
	tvlv_buff_len = ntohs(unicast_tvlv_packet->tvlv_len);

	अगर (tvlv_buff_len > skb->len - hdr_size)
		जाओ मुक्त_skb;

	ret = batadv_tvlv_containers_process(bat_priv, false, शून्य,
					     unicast_tvlv_packet->src,
					     unicast_tvlv_packet->dst,
					     tvlv_buff, tvlv_buff_len);

	अगर (ret != NET_RX_SUCCESS) अणु
		ret = batadv_route_unicast_packet(skb, recv_अगर);
		/* skb was consumed */
		skb = शून्य;
	पूर्ण

मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_recv_frag_packet() - process received fragment
 * @skb: the received fragment
 * @recv_अगर: पूर्णांकerface that the skb is received on
 *
 * This function करोes one of the three following things: 1) Forward fragment, अगर
 * the assembled packet will exceed our MTU; 2) Buffer fragment, अगर we still
 * lack further fragments; 3) Merge fragments, अगर we have all needed parts.
 *
 * Return: NET_RX_DROP अगर the skb is not consumed, NET_RX_SUCCESS otherwise.
 */
पूर्णांक batadv_recv_frag_packet(काष्ठा sk_buff *skb,
			    काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_orig_node *orig_node_src = शून्य;
	काष्ठा batadv_frag_packet *frag_packet;
	पूर्णांक ret = NET_RX_DROP;

	अगर (batadv_check_unicast_packet(bat_priv, skb,
					माप(*frag_packet)) < 0)
		जाओ मुक्त_skb;

	frag_packet = (काष्ठा batadv_frag_packet *)skb->data;
	orig_node_src = batadv_orig_hash_find(bat_priv, frag_packet->orig);
	अगर (!orig_node_src)
		जाओ मुक्त_skb;

	skb->priority = frag_packet->priority + 256;

	/* Route the fragment अगर it is not क्रम us and too big to be merged. */
	अगर (!batadv_is_my_mac(bat_priv, frag_packet->dest) &&
	    batadv_frag_skb_fwd(skb, recv_अगर, orig_node_src)) अणु
		/* skb was consumed */
		skb = शून्य;
		ret = NET_RX_SUCCESS;
		जाओ put_orig_node;
	पूर्ण

	batadv_inc_counter(bat_priv, BATADV_CNT_FRAG_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_FRAG_RX_BYTES, skb->len);

	/* Add fragment to buffer and merge अगर possible. */
	अगर (!batadv_frag_skb_buffer(&skb, orig_node_src))
		जाओ put_orig_node;

	/* Deliver merged packet to the appropriate handler, अगर it was
	 * merged
	 */
	अगर (skb) अणु
		batadv_baपंचांगan_skb_recv(skb, recv_अगर->net_dev,
				       &recv_अगर->baपंचांगan_adv_ptype, शून्य);
		/* skb was consumed */
		skb = शून्य;
	पूर्ण

	ret = NET_RX_SUCCESS;

put_orig_node:
	batadv_orig_node_put(orig_node_src);
मुक्त_skb:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_recv_bcast_packet() - Process incoming broadcast packet
 * @skb: incoming packet buffer
 * @recv_अगर: incoming hard पूर्णांकerface
 *
 * Return: NET_RX_SUCCESS on success or NET_RX_DROP in हाल of failure
 */
पूर्णांक batadv_recv_bcast_packet(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_bcast_packet *bcast_packet;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक hdr_size = माप(*bcast_packet);
	पूर्णांक ret = NET_RX_DROP;
	s32 seq_dअगरf;
	u32 seqno;

	/* drop packet अगर it has not necessary minimum size */
	अगर (unlikely(!pskb_may_pull(skb, hdr_size)))
		जाओ मुक्त_skb;

	ethhdr = eth_hdr(skb);

	/* packet with broadcast indication but unicast recipient */
	अगर (!is_broadcast_ether_addr(ethhdr->h_dest))
		जाओ मुक्त_skb;

	/* packet with broadcast/multicast sender address */
	अगर (is_multicast_ether_addr(ethhdr->h_source))
		जाओ मुक्त_skb;

	/* ignore broadcasts sent by myself */
	अगर (batadv_is_my_mac(bat_priv, ethhdr->h_source))
		जाओ मुक्त_skb;

	bcast_packet = (काष्ठा batadv_bcast_packet *)skb->data;

	/* ignore broadcasts originated by myself */
	अगर (batadv_is_my_mac(bat_priv, bcast_packet->orig))
		जाओ मुक्त_skb;

	अगर (bcast_packet->ttl < 2)
		जाओ मुक्त_skb;

	orig_node = batadv_orig_hash_find(bat_priv, bcast_packet->orig);

	अगर (!orig_node)
		जाओ मुक्त_skb;

	spin_lock_bh(&orig_node->bcast_seqno_lock);

	seqno = ntohl(bcast_packet->seqno);
	/* check whether the packet is a duplicate */
	अगर (batadv_test_bit(orig_node->bcast_bits, orig_node->last_bcast_seqno,
			    seqno))
		जाओ spin_unlock;

	seq_dअगरf = seqno - orig_node->last_bcast_seqno;

	/* check whether the packet is old and the host just restarted. */
	अगर (batadv_winकरोw_रक्षित(bat_priv, seq_dअगरf,
				    BATADV_BCAST_MAX_AGE,
				    &orig_node->bcast_seqno_reset, शून्य))
		जाओ spin_unlock;

	/* mark broadcast in flood history, update winकरोw position
	 * अगर required.
	 */
	अगर (batadv_bit_get_packet(bat_priv, orig_node->bcast_bits, seq_dअगरf, 1))
		orig_node->last_bcast_seqno = seqno;

	spin_unlock_bh(&orig_node->bcast_seqno_lock);

	/* check whether this has been sent by another originator beक्रमe */
	अगर (batadv_bla_check_bcast_duplist(bat_priv, skb))
		जाओ मुक्त_skb;

	batadv_skb_set_priority(skb, माप(काष्ठा batadv_bcast_packet));

	/* rebroadcast packet */
	batadv_add_bcast_packet_to_list(bat_priv, skb, 1, false);

	/* करोn't hand the broadcast up अगर it is from an originator
	 * from the same backbone.
	 */
	अगर (batadv_bla_is_backbone_gw(skb, orig_node, hdr_size))
		जाओ मुक्त_skb;

	अगर (batadv_dat_snoop_incoming_arp_request(bat_priv, skb, hdr_size))
		जाओ rx_success;
	अगर (batadv_dat_snoop_incoming_arp_reply(bat_priv, skb, hdr_size))
		जाओ rx_success;

	batadv_dat_snoop_incoming_dhcp_ack(bat_priv, skb, hdr_size);

	/* broadcast क्रम me */
	batadv_पूर्णांकerface_rx(recv_अगर->soft_अगरace, skb, hdr_size, orig_node);

rx_success:
	ret = NET_RX_SUCCESS;
	जाओ out;

spin_unlock:
	spin_unlock_bh(&orig_node->bcast_seqno_lock);
मुक्त_skb:
	kमुक्त_skb(skb);
out:
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
	वापस ret;
पूर्ण
