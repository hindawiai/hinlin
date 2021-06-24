<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Antonio Quartulli
 */

#समावेश "bat_v_ogm.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/minmax.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pअक्रमom.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "bat_algo.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "send.h"
#समावेश "translation-table.h"
#समावेश "tvlv.h"

/**
 * batadv_v_ogm_orig_get() - retrieve and possibly create an originator node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the address of the originator
 *
 * Return: the orig_node corresponding to the specअगरied address. If such an
 * object करोes not exist, it is allocated here. In हाल of allocation failure
 * वापसs शून्य.
 */
काष्ठा batadv_orig_node *batadv_v_ogm_orig_get(काष्ठा batadv_priv *bat_priv,
					       स्थिर u8 *addr)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक hash_added;

	orig_node = batadv_orig_hash_find(bat_priv, addr);
	अगर (orig_node)
		वापस orig_node;

	orig_node = batadv_orig_node_new(bat_priv, addr);
	अगर (!orig_node)
		वापस शून्य;

	kref_get(&orig_node->refcount);
	hash_added = batadv_hash_add(bat_priv->orig_hash, batadv_compare_orig,
				     batadv_choose_orig, orig_node,
				     &orig_node->hash_entry);
	अगर (hash_added != 0) अणु
		/* हटाओ refcnt क्रम newly created orig_node and hash entry */
		batadv_orig_node_put(orig_node);
		batadv_orig_node_put(orig_node);
		orig_node = शून्य;
	पूर्ण

	वापस orig_node;
पूर्ण

/**
 * batadv_v_ogm_start_queue_समयr() - restart the OGM aggregation समयr
 * @hard_अगरace: the पूर्णांकerface to use to send the OGM
 */
अटल व्योम batadv_v_ogm_start_queue_समयr(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अचिन्हित पूर्णांक msecs = BATADV_MAX_AGGREGATION_MS * 1000;

	/* msecs * [0.9, 1.1] */
	msecs += pअक्रमom_u32_max(msecs / 5) - (msecs / 10);
	queue_delayed_work(batadv_event_workqueue, &hard_अगरace->bat_v.aggr_wq,
			   msecs_to_jअगरfies(msecs / 1000));
पूर्ण

/**
 * batadv_v_ogm_start_समयr() - restart the OGM sending समयr
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_v_ogm_start_समयr(काष्ठा batadv_priv *bat_priv)
अणु
	अचिन्हित दीर्घ msecs;
	/* this function may be invoked in dअगरferent contexts (ogm rescheduling
	 * or hard_अगरace activation), but the work समयr should not be reset
	 */
	अगर (delayed_work_pending(&bat_priv->bat_v.ogm_wq))
		वापस;

	msecs = atomic_पढ़ो(&bat_priv->orig_पूर्णांकerval) - BATADV_JITTER;
	msecs += pअक्रमom_u32_max(2 * BATADV_JITTER);
	queue_delayed_work(batadv_event_workqueue, &bat_priv->bat_v.ogm_wq,
			   msecs_to_jअगरfies(msecs));
पूर्ण

/**
 * batadv_v_ogm_send_to_अगर() - send a baपंचांगan ogm using a given पूर्णांकerface
 * @skb: the OGM to send
 * @hard_अगरace: the पूर्णांकerface to use to send the OGM
 */
अटल व्योम batadv_v_ogm_send_to_अगर(काष्ठा sk_buff *skb,
				    काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
		वापस;

	batadv_inc_counter(bat_priv, BATADV_CNT_MGMT_TX);
	batadv_add_counter(bat_priv, BATADV_CNT_MGMT_TX_BYTES,
			   skb->len + ETH_HLEN);

	batadv_send_broadcast_skb(skb, hard_अगरace);
पूर्ण

/**
 * batadv_v_ogm_len() - OGMv2 packet length
 * @skb: the OGM to check
 *
 * Return: Length of the given OGMv2 packet, including tvlv length, excluding
 * ethernet header length.
 */
अटल अचिन्हित पूर्णांक batadv_v_ogm_len(काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_ogm2_packet *ogm_packet;

	ogm_packet = (काष्ठा batadv_ogm2_packet *)skb->data;
	वापस BATADV_OGM2_HLEN + ntohs(ogm_packet->tvlv_len);
पूर्ण

/**
 * batadv_v_ogm_queue_left() - check अगर given OGM still fits aggregation queue
 * @skb: the OGM to check
 * @hard_अगरace: the पूर्णांकerface to use to send the OGM
 *
 * Caller needs to hold the hard_अगरace->bat_v.aggr_list.lock.
 *
 * Return: True, अगर the given OGMv2 packet still fits, false otherwise.
 */
अटल bool batadv_v_ogm_queue_left(काष्ठा sk_buff *skb,
				    काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अचिन्हित पूर्णांक max = min_t(अचिन्हित पूर्णांक, hard_अगरace->net_dev->mtu,
				 BATADV_MAX_AGGREGATION_BYTES);
	अचिन्हित पूर्णांक ogm_len = batadv_v_ogm_len(skb);

	lockdep_निश्चित_held(&hard_अगरace->bat_v.aggr_list.lock);

	वापस hard_अगरace->bat_v.aggr_len + ogm_len <= max;
पूर्ण

/**
 * batadv_v_ogm_aggr_list_मुक्त - मुक्त all elements in an aggregation queue
 * @hard_अगरace: the पूर्णांकerface holding the aggregation queue
 *
 * Empties the OGMv2 aggregation queue and मुक्तs all the skbs it contains.
 *
 * Caller needs to hold the hard_अगरace->bat_v.aggr_list.lock.
 */
अटल व्योम batadv_v_ogm_aggr_list_मुक्त(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	lockdep_निश्चित_held(&hard_अगरace->bat_v.aggr_list.lock);

	__skb_queue_purge(&hard_अगरace->bat_v.aggr_list);
	hard_अगरace->bat_v.aggr_len = 0;
पूर्ण

/**
 * batadv_v_ogm_aggr_send() - flush & send aggregation queue
 * @hard_अगरace: the पूर्णांकerface with the aggregation queue to flush
 *
 * Aggregates all OGMv2 packets currently in the aggregation queue पूर्णांकo a
 * single OGMv2 packet and transmits this aggregate.
 *
 * The aggregation queue is empty after this call.
 *
 * Caller needs to hold the hard_अगरace->bat_v.aggr_list.lock.
 */
अटल व्योम batadv_v_ogm_aggr_send(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अचिन्हित पूर्णांक aggr_len = hard_अगरace->bat_v.aggr_len;
	काष्ठा sk_buff *skb_aggr;
	अचिन्हित पूर्णांक ogm_len;
	काष्ठा sk_buff *skb;

	lockdep_निश्चित_held(&hard_अगरace->bat_v.aggr_list.lock);

	अगर (!aggr_len)
		वापस;

	skb_aggr = dev_alloc_skb(aggr_len + ETH_HLEN + NET_IP_ALIGN);
	अगर (!skb_aggr) अणु
		batadv_v_ogm_aggr_list_मुक्त(hard_अगरace);
		वापस;
	पूर्ण

	skb_reserve(skb_aggr, ETH_HLEN + NET_IP_ALIGN);
	skb_reset_network_header(skb_aggr);

	जबतक ((skb = __skb_dequeue(&hard_अगरace->bat_v.aggr_list))) अणु
		hard_अगरace->bat_v.aggr_len -= batadv_v_ogm_len(skb);

		ogm_len = batadv_v_ogm_len(skb);
		skb_put_data(skb_aggr, skb->data, ogm_len);

		consume_skb(skb);
	पूर्ण

	batadv_v_ogm_send_to_अगर(skb_aggr, hard_अगरace);
पूर्ण

/**
 * batadv_v_ogm_queue_on_अगर() - queue a baपंचांगan ogm on a given पूर्णांकerface
 * @skb: the OGM to queue
 * @hard_अगरace: the पूर्णांकerface to queue the OGM on
 */
अटल व्योम batadv_v_ogm_queue_on_अगर(काष्ठा sk_buff *skb,
				     काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	अगर (!atomic_पढ़ो(&bat_priv->aggregated_ogms)) अणु
		batadv_v_ogm_send_to_अगर(skb, hard_अगरace);
		वापस;
	पूर्ण

	spin_lock_bh(&hard_अगरace->bat_v.aggr_list.lock);
	अगर (!batadv_v_ogm_queue_left(skb, hard_अगरace))
		batadv_v_ogm_aggr_send(hard_अगरace);

	hard_अगरace->bat_v.aggr_len += batadv_v_ogm_len(skb);
	__skb_queue_tail(&hard_अगरace->bat_v.aggr_list, skb);
	spin_unlock_bh(&hard_अगरace->bat_v.aggr_list.lock);
पूर्ण

/**
 * batadv_v_ogm_send_softअगर() - periodic worker broadcasting the own OGM
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_v_ogm_send_softअगर(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_ogm2_packet *ogm_packet;
	काष्ठा sk_buff *skb, *skb_पंचांगp;
	अचिन्हित अक्षर *ogm_buff;
	पूर्णांक ogm_buff_len;
	u16 tvlv_len = 0;
	पूर्णांक ret;

	lockdep_निश्चित_held(&bat_priv->bat_v.ogm_buff_mutex);

	अगर (atomic_पढ़ो(&bat_priv->mesh_state) == BATADV_MESH_DEACTIVATING)
		जाओ out;

	ogm_buff = bat_priv->bat_v.ogm_buff;
	ogm_buff_len = bat_priv->bat_v.ogm_buff_len;
	/* tt changes have to be committed beक्रमe the tvlv data is
	 * appended as it may alter the tt tvlv container
	 */
	batadv_tt_local_commit_changes(bat_priv);
	tvlv_len = batadv_tvlv_container_ogm_append(bat_priv, &ogm_buff,
						    &ogm_buff_len,
						    BATADV_OGM2_HLEN);

	bat_priv->bat_v.ogm_buff = ogm_buff;
	bat_priv->bat_v.ogm_buff_len = ogm_buff_len;

	skb = netdev_alloc_skb_ip_align(शून्य, ETH_HLEN + ogm_buff_len);
	अगर (!skb)
		जाओ reschedule;

	skb_reserve(skb, ETH_HLEN);
	skb_put_data(skb, ogm_buff, ogm_buff_len);

	ogm_packet = (काष्ठा batadv_ogm2_packet *)skb->data;
	ogm_packet->seqno = htonl(atomic_पढ़ो(&bat_priv->bat_v.ogm_seqno));
	atomic_inc(&bat_priv->bat_v.ogm_seqno);
	ogm_packet->tvlv_len = htons(tvlv_len);

	/* broadcast on every पूर्णांकerface */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
			जारी;

		अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
			जारी;

		ret = batadv_hardअगर_no_broadcast(hard_अगरace, शून्य, शून्य);
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

			batadv_dbg(BATADV_DBG_BATMAN, bat_priv, "OGM2 from ourselves on %s suppressed: %s\n",
				   hard_अगरace->net_dev->name, type);

			batadv_hardअगर_put(hard_अगरace);
			जारी;
		पूर्ण

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Sending own OGM2 packet (originator %pM, seqno %u, throughput %u, TTL %d) on interface %s [%pM]\n",
			   ogm_packet->orig, ntohl(ogm_packet->seqno),
			   ntohl(ogm_packet->throughput), ogm_packet->ttl,
			   hard_अगरace->net_dev->name,
			   hard_अगरace->net_dev->dev_addr);

		/* this skb माला_लो consumed by batadv_v_ogm_send_to_अगर() */
		skb_पंचांगp = skb_clone(skb, GFP_ATOMIC);
		अगर (!skb_पंचांगp) अणु
			batadv_hardअगर_put(hard_अगरace);
			अवरोध;
		पूर्ण

		batadv_v_ogm_queue_on_अगर(skb_पंचांगp, hard_अगरace);
		batadv_hardअगर_put(hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();

	consume_skb(skb);

reschedule:
	batadv_v_ogm_start_समयr(bat_priv);
out:
	वापस;
पूर्ण

/**
 * batadv_v_ogm_send() - periodic worker broadcasting the own OGM
 * @work: work queue item
 */
अटल व्योम batadv_v_ogm_send(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा batadv_priv_bat_v *bat_v;
	काष्ठा batadv_priv *bat_priv;

	bat_v = container_of(work, काष्ठा batadv_priv_bat_v, ogm_wq.work);
	bat_priv = container_of(bat_v, काष्ठा batadv_priv, bat_v);

	mutex_lock(&bat_priv->bat_v.ogm_buff_mutex);
	batadv_v_ogm_send_softअगर(bat_priv);
	mutex_unlock(&bat_priv->bat_v.ogm_buff_mutex);
पूर्ण

/**
 * batadv_v_ogm_aggr_work() - OGM queue periodic task per पूर्णांकerface
 * @work: work queue item
 *
 * Emits aggregated OGM messages in regular पूर्णांकervals.
 */
व्योम batadv_v_ogm_aggr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा batadv_hard_अगरace_bat_v *batv;
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	batv = container_of(work, काष्ठा batadv_hard_अगरace_bat_v, aggr_wq.work);
	hard_अगरace = container_of(batv, काष्ठा batadv_hard_अगरace, bat_v);

	spin_lock_bh(&hard_अगरace->bat_v.aggr_list.lock);
	batadv_v_ogm_aggr_send(hard_अगरace);
	spin_unlock_bh(&hard_अगरace->bat_v.aggr_list.lock);

	batadv_v_ogm_start_queue_समयr(hard_अगरace);
पूर्ण

/**
 * batadv_v_ogm_अगरace_enable() - prepare an पूर्णांकerface क्रम B.A.T.M.A.N. V
 * @hard_अगरace: the पूर्णांकerface to prepare
 *
 * Takes care of scheduling its own OGM sending routine क्रम this पूर्णांकerface.
 *
 * Return: 0 on success or a negative error code otherwise
 */
पूर्णांक batadv_v_ogm_अगरace_enable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	batadv_v_ogm_start_queue_समयr(hard_अगरace);
	batadv_v_ogm_start_समयr(bat_priv);

	वापस 0;
पूर्ण

/**
 * batadv_v_ogm_अगरace_disable() - release OGM पूर्णांकerface निजी resources
 * @hard_अगरace: पूर्णांकerface क्रम which the resources have to be released
 */
व्योम batadv_v_ogm_अगरace_disable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	cancel_delayed_work_sync(&hard_अगरace->bat_v.aggr_wq);

	spin_lock_bh(&hard_अगरace->bat_v.aggr_list.lock);
	batadv_v_ogm_aggr_list_मुक्त(hard_अगरace);
	spin_unlock_bh(&hard_अगरace->bat_v.aggr_list.lock);
पूर्ण

/**
 * batadv_v_ogm_primary_अगरace_set() - set a new primary पूर्णांकerface
 * @primary_अगरace: the new primary पूर्णांकerface
 */
व्योम batadv_v_ogm_primary_अगरace_set(काष्ठा batadv_hard_अगरace *primary_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(primary_अगरace->soft_अगरace);
	काष्ठा batadv_ogm2_packet *ogm_packet;

	mutex_lock(&bat_priv->bat_v.ogm_buff_mutex);
	अगर (!bat_priv->bat_v.ogm_buff)
		जाओ unlock;

	ogm_packet = (काष्ठा batadv_ogm2_packet *)bat_priv->bat_v.ogm_buff;
	ether_addr_copy(ogm_packet->orig, primary_अगरace->net_dev->dev_addr);

unlock:
	mutex_unlock(&bat_priv->bat_v.ogm_buff_mutex);
पूर्ण

/**
 * batadv_v_क्रमward_penalty() - apply a penalty to the throughput metric
 *  क्रमwarded with B.A.T.M.A.N. V OGMs
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_incoming: the पूर्णांकerface where the OGM has been received
 * @अगर_outgoing: the पूर्णांकerface where the OGM has to be क्रमwarded to
 * @throughput: the current throughput
 *
 * Apply a penalty on the current throughput metric value based on the
 * अक्षरacteristic of the पूर्णांकerface where the OGM has been received.
 *
 * Initially the per hardअगर hop penalty is applied to the throughput. After
 * that the वापस value is then computed as follows:
 * - throughput * 50%          अगर the incoming and outgoing पूर्णांकerface are the
 *                             same WiFi पूर्णांकerface and the throughput is above
 *                             1MBit/s
 * - throughput                अगर the outgoing पूर्णांकerface is the शेष
 *                             पूर्णांकerface (i.e. this OGM is processed क्रम the
 *                             पूर्णांकernal table and not क्रमwarded)
 * - throughput * node hop penalty  otherwise
 *
 * Return: the penalised throughput metric.
 */
अटल u32 batadv_v_क्रमward_penalty(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_hard_अगरace *अगर_incoming,
				    काष्ठा batadv_hard_अगरace *अगर_outgoing,
				    u32 throughput)
अणु
	पूर्णांक अगर_hop_penalty = atomic_पढ़ो(&अगर_incoming->hop_penalty);
	पूर्णांक hop_penalty = atomic_पढ़ो(&bat_priv->hop_penalty);
	पूर्णांक hop_penalty_max = BATADV_TQ_MAX_VALUE;

	/* Apply per hardअगर hop penalty */
	throughput = throughput * (hop_penalty_max - अगर_hop_penalty) /
		     hop_penalty_max;

	/* Don't apply hop penalty in शेष originator table. */
	अगर (अगर_outgoing == BATADV_IF_DEFAULT)
		वापस throughput;

	/* Forwarding on the same WiFi पूर्णांकerface cuts the throughput in half
	 * due to the store & क्रमward अक्षरacteristics of WIFI.
	 * Very low throughput values are the exception.
	 */
	अगर (throughput > 10 &&
	    अगर_incoming == अगर_outgoing &&
	    !(अगर_incoming->bat_v.flags & BATADV_FULL_DUPLEX))
		वापस throughput / 2;

	/* hop penalty of 255 equals 100% */
	वापस throughput * (hop_penalty_max - hop_penalty) / hop_penalty_max;
पूर्ण

/**
 * batadv_v_ogm_क्रमward() - check conditions and क्रमward an OGM to the given
 *  outgoing पूर्णांकerface
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ogm_received: previously received OGM to be क्रमwarded
 * @orig_node: the originator which has been updated
 * @neigh_node: the neigh_node through with the OGM has been received
 * @अगर_incoming: the पूर्णांकerface on which this OGM was received on
 * @अगर_outgoing: the पूर्णांकerface to which the OGM has to be क्रमwarded to
 *
 * Forward an OGM to an पूर्णांकerface after having altered the throughput metric and
 * the TTL value contained in it. The original OGM isn't modअगरied.
 */
अटल व्योम batadv_v_ogm_क्रमward(काष्ठा batadv_priv *bat_priv,
				 स्थिर काष्ठा batadv_ogm2_packet *ogm_received,
				 काष्ठा batadv_orig_node *orig_node,
				 काष्ठा batadv_neigh_node *neigh_node,
				 काष्ठा batadv_hard_अगरace *अगर_incoming,
				 काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo = शून्य;
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo = शून्य;
	काष्ठा batadv_neigh_node *router = शून्य;
	काष्ठा batadv_ogm2_packet *ogm_क्रमward;
	अचिन्हित अक्षर *skb_buff;
	काष्ठा sk_buff *skb;
	माप_प्रकार packet_len;
	u16 tvlv_len;

	/* only क्रमward क्रम specअगरic पूर्णांकerfaces, not क्रम the शेष one. */
	अगर (अगर_outgoing == BATADV_IF_DEFAULT)
		जाओ out;

	orig_अगरinfo = batadv_orig_अगरinfo_new(orig_node, अगर_outgoing);
	अगर (!orig_अगरinfo)
		जाओ out;

	/* acquire possibly updated router */
	router = batadv_orig_router_get(orig_node, अगर_outgoing);

	/* strict rule: क्रमward packets coming from the best next hop only */
	अगर (neigh_node != router)
		जाओ out;

	/* करोn't क्रमward the same seqno twice on one पूर्णांकerface */
	अगर (orig_अगरinfo->last_seqno_क्रमwarded == ntohl(ogm_received->seqno))
		जाओ out;

	orig_अगरinfo->last_seqno_क्रमwarded = ntohl(ogm_received->seqno);

	अगर (ogm_received->ttl <= 1) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv, "ttl exceeded\n");
		जाओ out;
	पूर्ण

	neigh_अगरinfo = batadv_neigh_अगरinfo_get(neigh_node, अगर_outgoing);
	अगर (!neigh_अगरinfo)
		जाओ out;

	tvlv_len = ntohs(ogm_received->tvlv_len);

	packet_len = BATADV_OGM2_HLEN + tvlv_len;
	skb = netdev_alloc_skb_ip_align(अगर_outgoing->net_dev,
					ETH_HLEN + packet_len);
	अगर (!skb)
		जाओ out;

	skb_reserve(skb, ETH_HLEN);
	skb_buff = skb_put_data(skb, ogm_received, packet_len);

	/* apply क्रमward penalty */
	ogm_क्रमward = (काष्ठा batadv_ogm2_packet *)skb_buff;
	ogm_क्रमward->throughput = htonl(neigh_अगरinfo->bat_v.throughput);
	ogm_क्रमward->ttl--;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Forwarding OGM2 packet on %s: throughput %u, ttl %u, received via %s\n",
		   अगर_outgoing->net_dev->name, ntohl(ogm_क्रमward->throughput),
		   ogm_क्रमward->ttl, अगर_incoming->net_dev->name);

	batadv_v_ogm_queue_on_अगर(skb, अगर_outgoing);

out:
	अगर (orig_अगरinfo)
		batadv_orig_अगरinfo_put(orig_अगरinfo);
	अगर (router)
		batadv_neigh_node_put(router);
	अगर (neigh_अगरinfo)
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
पूर्ण

/**
 * batadv_v_ogm_metric_update() - update route metric based on OGM
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ogm2: OGM2 काष्ठाure
 * @orig_node: Originator काष्ठाure क्रम which the OGM has been received
 * @neigh_node: the neigh_node through with the OGM has been received
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 * @अगर_outgoing: the पूर्णांकerface क्रम which the packet should be considered
 *
 * Return:
 *  1  अगर the OGM is new,
 *  0  अगर it is not new but valid,
 *  <0 on error (e.g. old OGM)
 */
अटल पूर्णांक batadv_v_ogm_metric_update(काष्ठा batadv_priv *bat_priv,
				      स्थिर काष्ठा batadv_ogm2_packet *ogm2,
				      काष्ठा batadv_orig_node *orig_node,
				      काष्ठा batadv_neigh_node *neigh_node,
				      काष्ठा batadv_hard_अगरace *अगर_incoming,
				      काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo = शून्य;
	bool protection_started = false;
	पूर्णांक ret = -EINVAL;
	u32 path_throughput;
	s32 seq_dअगरf;

	orig_अगरinfo = batadv_orig_अगरinfo_new(orig_node, अगर_outgoing);
	अगर (!orig_अगरinfo)
		जाओ out;

	seq_dअगरf = ntohl(ogm2->seqno) - orig_अगरinfo->last_real_seqno;

	अगर (!hlist_empty(&orig_node->neigh_list) &&
	    batadv_winकरोw_रक्षित(bat_priv, seq_dअगरf,
				    BATADV_OGM_MAX_AGE,
				    &orig_अगरinfo->baपंचांगan_seqno_reset,
				    &protection_started)) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: packet within window protection time from %pM\n",
			   ogm2->orig);
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Last reset: %ld, %ld\n",
			   orig_अगरinfo->baपंचांगan_seqno_reset, jअगरfies);
		जाओ out;
	पूर्ण

	/* drop packets with old seqnos, however accept the first packet after
	 * a host has been rebooted.
	 */
	अगर (seq_dअगरf < 0 && !protection_started)
		जाओ out;

	neigh_node->last_seen = jअगरfies;

	orig_node->last_seen = jअगरfies;

	orig_अगरinfo->last_real_seqno = ntohl(ogm2->seqno);
	orig_अगरinfo->last_ttl = ogm2->ttl;

	neigh_अगरinfo = batadv_neigh_अगरinfo_new(neigh_node, अगर_outgoing);
	अगर (!neigh_अगरinfo)
		जाओ out;

	path_throughput = batadv_v_क्रमward_penalty(bat_priv, अगर_incoming,
						   अगर_outgoing,
						   ntohl(ogm2->throughput));
	neigh_अगरinfo->bat_v.throughput = path_throughput;
	neigh_अगरinfo->bat_v.last_seqno = ntohl(ogm2->seqno);
	neigh_अगरinfo->last_ttl = ogm2->ttl;

	अगर (seq_dअगरf > 0 || protection_started)
		ret = 1;
	अन्यथा
		ret = 0;
out:
	अगर (orig_अगरinfo)
		batadv_orig_अगरinfo_put(orig_अगरinfo);
	अगर (neigh_अगरinfo)
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);

	वापस ret;
पूर्ण

/**
 * batadv_v_ogm_route_update() - update routes based on OGM
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: the Ethernet header of the OGM2
 * @ogm2: OGM2 काष्ठाure
 * @orig_node: Originator काष्ठाure क्रम which the OGM has been received
 * @neigh_node: the neigh_node through with the OGM has been received
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 * @अगर_outgoing: the पूर्णांकerface क्रम which the packet should be considered
 *
 * Return: true अगर the packet should be क्रमwarded, false otherwise
 */
अटल bool batadv_v_ogm_route_update(काष्ठा batadv_priv *bat_priv,
				      स्थिर काष्ठा ethhdr *ethhdr,
				      स्थिर काष्ठा batadv_ogm2_packet *ogm2,
				      काष्ठा batadv_orig_node *orig_node,
				      काष्ठा batadv_neigh_node *neigh_node,
				      काष्ठा batadv_hard_अगरace *अगर_incoming,
				      काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_neigh_node *router = शून्य;
	काष्ठा batadv_orig_node *orig_neigh_node;
	काष्ठा batadv_neigh_node *orig_neigh_router = शून्य;
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य, *neigh_अगरinfo = शून्य;
	u32 router_throughput, neigh_throughput;
	u32 router_last_seqno;
	u32 neigh_last_seqno;
	s32 neigh_seq_dअगरf;
	bool क्रमward = false;

	orig_neigh_node = batadv_v_ogm_orig_get(bat_priv, ethhdr->h_source);
	अगर (!orig_neigh_node)
		जाओ out;

	orig_neigh_router = batadv_orig_router_get(orig_neigh_node,
						   अगर_outgoing);

	/* drop packet अगर sender is not a direct neighbor and अगर we
	 * करोn't route towards it
	 */
	router = batadv_orig_router_get(orig_node, अगर_outgoing);
	अगर (router && router->orig_node != orig_node && !orig_neigh_router) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: OGM via unknown neighbor!\n");
		जाओ out;
	पूर्ण

	/* Mark the OGM to be considered क्रम क्रमwarding, and update routes
	 * अगर needed.
	 */
	क्रमward = true;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Searching and updating originator entry of received packet\n");

	/* अगर this neighbor alपढ़ोy is our next hop there is nothing
	 * to change
	 */
	अगर (router == neigh_node)
		जाओ out;

	/* करोn't consider neighbours with worse throughput.
	 * also चयन route अगर this seqno is BATADV_V_MAX_ORIGDIFF newer than
	 * the last received seqno from our best next hop.
	 */
	अगर (router) अणु
		router_अगरinfo = batadv_neigh_अगरinfo_get(router, अगर_outgoing);
		neigh_अगरinfo = batadv_neigh_अगरinfo_get(neigh_node, अगर_outgoing);

		/* अगर these are not allocated, something is wrong. */
		अगर (!router_अगरinfo || !neigh_अगरinfo)
			जाओ out;

		neigh_last_seqno = neigh_अगरinfo->bat_v.last_seqno;
		router_last_seqno = router_अगरinfo->bat_v.last_seqno;
		neigh_seq_dअगरf = neigh_last_seqno - router_last_seqno;
		router_throughput = router_अगरinfo->bat_v.throughput;
		neigh_throughput = neigh_अगरinfo->bat_v.throughput;

		अगर (neigh_seq_dअगरf < BATADV_OGM_MAX_ORIGDIFF &&
		    router_throughput >= neigh_throughput)
			जाओ out;
	पूर्ण

	batadv_update_route(bat_priv, orig_node, अगर_outgoing, neigh_node);
out:
	अगर (router)
		batadv_neigh_node_put(router);
	अगर (orig_neigh_router)
		batadv_neigh_node_put(orig_neigh_router);
	अगर (orig_neigh_node)
		batadv_orig_node_put(orig_neigh_node);
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);
	अगर (neigh_अगरinfo)
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);

	वापस क्रमward;
पूर्ण

/**
 * batadv_v_ogm_process_per_outअगर() - process a baपंचांगan v OGM क्रम an outgoing अगर
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: the Ethernet header of the OGM2
 * @ogm2: OGM2 काष्ठाure
 * @orig_node: Originator काष्ठाure क्रम which the OGM has been received
 * @neigh_node: the neigh_node through with the OGM has been received
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 * @अगर_outgoing: the पूर्णांकerface क्रम which the packet should be considered
 */
अटल व्योम
batadv_v_ogm_process_per_outअगर(काष्ठा batadv_priv *bat_priv,
			       स्थिर काष्ठा ethhdr *ethhdr,
			       स्थिर काष्ठा batadv_ogm2_packet *ogm2,
			       काष्ठा batadv_orig_node *orig_node,
			       काष्ठा batadv_neigh_node *neigh_node,
			       काष्ठा batadv_hard_अगरace *अगर_incoming,
			       काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	पूर्णांक seqno_age;
	bool क्रमward;

	/* first, update the metric with according sanity checks */
	seqno_age = batadv_v_ogm_metric_update(bat_priv, ogm2, orig_node,
					       neigh_node, अगर_incoming,
					       अगर_outgoing);

	/* outdated sequence numbers are to be discarded */
	अगर (seqno_age < 0)
		वापस;

	/* only unknown & newer OGMs contain TVLVs we are पूर्णांकerested in */
	अगर (seqno_age > 0 && अगर_outgoing == BATADV_IF_DEFAULT)
		batadv_tvlv_containers_process(bat_priv, true, orig_node,
					       शून्य, शून्य,
					       (अचिन्हित अक्षर *)(ogm2 + 1),
					       ntohs(ogm2->tvlv_len));

	/* अगर the metric update went through, update routes अगर needed */
	क्रमward = batadv_v_ogm_route_update(bat_priv, ethhdr, ogm2, orig_node,
					    neigh_node, अगर_incoming,
					    अगर_outgoing);

	/* अगर the routes have been processed correctly, check and क्रमward */
	अगर (क्रमward)
		batadv_v_ogm_क्रमward(bat_priv, ogm2, orig_node, neigh_node,
				     अगर_incoming, अगर_outgoing);
पूर्ण

/**
 * batadv_v_ogm_aggr_packet() - checks अगर there is another OGM aggregated
 * @buff_pos: current position in the skb
 * @packet_len: total length of the skb
 * @ogm2_packet: potential OGM2 in buffer
 *
 * Return: true अगर there is enough space क्रम another OGM, false otherwise.
 */
अटल bool
batadv_v_ogm_aggr_packet(पूर्णांक buff_pos, पूर्णांक packet_len,
			 स्थिर काष्ठा batadv_ogm2_packet *ogm2_packet)
अणु
	पूर्णांक next_buff_pos = 0;

	/* check अगर there is enough space क्रम the header */
	next_buff_pos += buff_pos + माप(*ogm2_packet);
	अगर (next_buff_pos > packet_len)
		वापस false;

	/* check अगर there is enough space क्रम the optional TVLV */
	next_buff_pos += ntohs(ogm2_packet->tvlv_len);

	वापस (next_buff_pos <= packet_len) &&
	       (next_buff_pos <= BATADV_MAX_AGGREGATION_BYTES);
पूर्ण

/**
 * batadv_v_ogm_process() - process an incoming baपंचांगan v OGM
 * @skb: the skb containing the OGM
 * @ogm_offset: offset to the OGM which should be processed (क्रम aggregates)
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 */
अटल व्योम batadv_v_ogm_process(स्थिर काष्ठा sk_buff *skb, पूर्णांक ogm_offset,
				 काष्ठा batadv_hard_अगरace *अगर_incoming)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा ethhdr *ethhdr;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh = शून्य;
	काष्ठा batadv_neigh_node *neigh_node = शून्य;
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_ogm2_packet *ogm_packet;
	u32 ogm_throughput, link_throughput, path_throughput;
	पूर्णांक ret;

	ethhdr = eth_hdr(skb);
	ogm_packet = (काष्ठा batadv_ogm2_packet *)(skb->data + ogm_offset);

	ogm_throughput = ntohl(ogm_packet->throughput);

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Received OGM2 packet via NB: %pM, IF: %s [%pM] (from OG: %pM, seqno %u, throughput %u, TTL %u, V %u, tvlv_len %u)\n",
		   ethhdr->h_source, अगर_incoming->net_dev->name,
		   अगर_incoming->net_dev->dev_addr, ogm_packet->orig,
		   ntohl(ogm_packet->seqno), ogm_throughput, ogm_packet->ttl,
		   ogm_packet->version, ntohs(ogm_packet->tvlv_len));

	अगर (batadv_is_my_mac(bat_priv, ogm_packet->orig)) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: originator packet from ourself\n");
		वापस;
	पूर्ण

	/* If the throughput metric is 0, immediately drop the packet. No need
	 * to create orig_node / neigh_node क्रम an unusable route.
	 */
	अगर (ogm_throughput == 0) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: originator packet with throughput metric of 0\n");
		वापस;
	पूर्ण

	/* require ELP packets be to received from this neighbor first */
	hardअगर_neigh = batadv_hardअगर_neigh_get(अगर_incoming, ethhdr->h_source);
	अगर (!hardअगर_neigh) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: OGM via unknown neighbor!\n");
		जाओ out;
	पूर्ण

	orig_node = batadv_v_ogm_orig_get(bat_priv, ogm_packet->orig);
	अगर (!orig_node)
		जाओ out;

	neigh_node = batadv_neigh_node_get_or_create(orig_node, अगर_incoming,
						     ethhdr->h_source);
	अगर (!neigh_node)
		जाओ out;

	/* Update the received throughput metric to match the link
	 * अक्षरacteristic:
	 *  - If this OGM traveled one hop so far (emitted by single hop
	 *    neighbor) the path throughput metric equals the link throughput.
	 *  - For OGMs traversing more than hop the path throughput metric is
	 *    the smaller of the path throughput and the link throughput.
	 */
	link_throughput = ewma_throughput_पढ़ो(&hardअगर_neigh->bat_v.throughput);
	path_throughput = min_t(u32, link_throughput, ogm_throughput);
	ogm_packet->throughput = htonl(path_throughput);

	batadv_v_ogm_process_per_outअगर(bat_priv, ethhdr, ogm_packet, orig_node,
				       neigh_node, अगर_incoming,
				       BATADV_IF_DEFAULT);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
			जारी;

		अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
			जारी;

		अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
			जारी;

		ret = batadv_hardअगर_no_broadcast(hard_अगरace,
						 ogm_packet->orig,
						 hardअगर_neigh->orig);

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

			batadv_dbg(BATADV_DBG_BATMAN, bat_priv, "OGM2 packet from %pM on %s suppressed: %s\n",
				   ogm_packet->orig, hard_अगरace->net_dev->name,
				   type);

			batadv_hardअगर_put(hard_अगरace);
			जारी;
		पूर्ण

		batadv_v_ogm_process_per_outअगर(bat_priv, ethhdr, ogm_packet,
					       orig_node, neigh_node,
					       अगर_incoming, hard_अगरace);

		batadv_hardअगर_put(hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();
out:
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
	अगर (neigh_node)
		batadv_neigh_node_put(neigh_node);
	अगर (hardअगर_neigh)
		batadv_hardअगर_neigh_put(hardअगर_neigh);
पूर्ण

/**
 * batadv_v_ogm_packet_recv() - OGM2 receiving handler
 * @skb: the received OGM
 * @अगर_incoming: the पूर्णांकerface where this OGM has been received
 *
 * Return: NET_RX_SUCCESS and consume the skb on success or वापसs NET_RX_DROP
 * (without मुक्तing the skb) on failure
 */
पूर्णांक batadv_v_ogm_packet_recv(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *अगर_incoming)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_ogm2_packet *ogm_packet;
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);
	पूर्णांक ogm_offset;
	u8 *packet_pos;
	पूर्णांक ret = NET_RX_DROP;

	/* did we receive a OGM2 packet on an पूर्णांकerface that करोes not have
	 * B.A.T.M.A.N. V enabled ?
	 */
	अगर (म_भेद(bat_priv->algo_ops->name, "BATMAN_V") != 0)
		जाओ मुक्त_skb;

	अगर (!batadv_check_management_packet(skb, अगर_incoming, BATADV_OGM2_HLEN))
		जाओ मुक्त_skb;

	अगर (batadv_is_my_mac(bat_priv, ethhdr->h_source))
		जाओ मुक्त_skb;

	batadv_inc_counter(bat_priv, BATADV_CNT_MGMT_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_MGMT_RX_BYTES,
			   skb->len + ETH_HLEN);

	ogm_offset = 0;
	ogm_packet = (काष्ठा batadv_ogm2_packet *)skb->data;

	जबतक (batadv_v_ogm_aggr_packet(ogm_offset, skb_headlen(skb),
					ogm_packet)) अणु
		batadv_v_ogm_process(skb, ogm_offset, अगर_incoming);

		ogm_offset += BATADV_OGM2_HLEN;
		ogm_offset += ntohs(ogm_packet->tvlv_len);

		packet_pos = skb->data + ogm_offset;
		ogm_packet = (काष्ठा batadv_ogm2_packet *)packet_pos;
	पूर्ण

	ret = NET_RX_SUCCESS;

मुक्त_skb:
	अगर (ret == NET_RX_SUCCESS)
		consume_skb(skb);
	अन्यथा
		kमुक्त_skb(skb);

	वापस ret;
पूर्ण

/**
 * batadv_v_ogm_init() - initialise the OGM2 engine
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success or a negative error code in हाल of failure
 */
पूर्णांक batadv_v_ogm_init(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_ogm2_packet *ogm_packet;
	अचिन्हित अक्षर *ogm_buff;
	u32 अक्रमom_seqno;

	bat_priv->bat_v.ogm_buff_len = BATADV_OGM2_HLEN;
	ogm_buff = kzalloc(bat_priv->bat_v.ogm_buff_len, GFP_ATOMIC);
	अगर (!ogm_buff)
		वापस -ENOMEM;

	bat_priv->bat_v.ogm_buff = ogm_buff;
	ogm_packet = (काष्ठा batadv_ogm2_packet *)ogm_buff;
	ogm_packet->packet_type = BATADV_OGM2;
	ogm_packet->version = BATADV_COMPAT_VERSION;
	ogm_packet->ttl = BATADV_TTL;
	ogm_packet->flags = BATADV_NO_FLAGS;
	ogm_packet->throughput = htonl(BATADV_THROUGHPUT_MAX_VALUE);

	/* अक्रमomize initial seqno to aव्योम collision */
	get_अक्रमom_bytes(&अक्रमom_seqno, माप(अक्रमom_seqno));
	atomic_set(&bat_priv->bat_v.ogm_seqno, अक्रमom_seqno);
	INIT_DELAYED_WORK(&bat_priv->bat_v.ogm_wq, batadv_v_ogm_send);

	mutex_init(&bat_priv->bat_v.ogm_buff_mutex);

	वापस 0;
पूर्ण

/**
 * batadv_v_ogm_मुक्त() - मुक्त OGM निजी resources
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_v_ogm_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	cancel_delayed_work_sync(&bat_priv->bat_v.ogm_wq);

	mutex_lock(&bat_priv->bat_v.ogm_buff_mutex);

	kमुक्त(bat_priv->bat_v.ogm_buff);
	bat_priv->bat_v.ogm_buff = शून्य;
	bat_priv->bat_v.ogm_buff_len = 0;

	mutex_unlock(&bat_priv->bat_v.ogm_buff_mutex);
पूर्ण
