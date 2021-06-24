<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "bat_iv_ogm.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/cache.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/pअक्रमom.h>
#समावेश <linux/prपूर्णांकk.h>
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
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "bitarray.h"
#समावेश "gateway_client.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "network-coding.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "send.h"
#समावेश "translation-table.h"
#समावेश "tvlv.h"

अटल व्योम batadv_iv_send_outstanding_bat_ogm_packet(काष्ठा work_काष्ठा *work);

/**
 * क्रमागत batadv_dup_status - duplicate status
 */
क्रमागत batadv_dup_status अणु
	/** @BATADV_NO_DUP: the packet is no duplicate */
	BATADV_NO_DUP = 0,

	/**
	 * @BATADV_ORIG_DUP: OGM is a duplicate in the originator (but not क्रम
	 *  the neighbor)
	 */
	BATADV_ORIG_DUP,

	/** @BATADV_NEIGH_DUP: OGM is a duplicate क्रम the neighbor */
	BATADV_NEIGH_DUP,

	/**
	 * @BATADV_PROTECTED: originator is currently रक्षित (after reboot)
	 */
	BATADV_PROTECTED,
पूर्ण;

/**
 * batadv_ring_buffer_set() - update the ring buffer with the given value
 * @lq_recv: poपूर्णांकer to the ring buffer
 * @lq_index: index to store the value at
 * @value: value to store in the ring buffer
 */
अटल व्योम batadv_ring_buffer_set(u8 lq_recv[], u8 *lq_index, u8 value)
अणु
	lq_recv[*lq_index] = value;
	*lq_index = (*lq_index + 1) % BATADV_TQ_GLOBAL_WINDOW_SIZE;
पूर्ण

/**
 * batadv_ring_buffer_avg() - compute the average of all non-zero values stored
 * in the given ring buffer
 * @lq_recv: poपूर्णांकer to the ring buffer
 *
 * Return: computed average value.
 */
अटल u8 batadv_ring_buffer_avg(स्थिर u8 lq_recv[])
अणु
	स्थिर u8 *ptr;
	u16 count = 0;
	u16 i = 0;
	u16 sum = 0;

	ptr = lq_recv;

	जबतक (i < BATADV_TQ_GLOBAL_WINDOW_SIZE) अणु
		अगर (*ptr != 0) अणु
			count++;
			sum += *ptr;
		पूर्ण

		i++;
		ptr++;
	पूर्ण

	अगर (count == 0)
		वापस 0;

	वापस (u8)(sum / count);
पूर्ण

/**
 * batadv_iv_ogm_orig_get() - retrieve or create (अगर करोes not exist) an
 *  originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: mac address of the originator
 *
 * Return: the originator object corresponding to the passed mac address or शून्य
 * on failure.
 * If the object करोes not exist, it is created and initialised.
 */
अटल काष्ठा batadv_orig_node *
batadv_iv_ogm_orig_get(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक hash_added;

	orig_node = batadv_orig_hash_find(bat_priv, addr);
	अगर (orig_node)
		वापस orig_node;

	orig_node = batadv_orig_node_new(bat_priv, addr);
	अगर (!orig_node)
		वापस शून्य;

	spin_lock_init(&orig_node->bat_iv.ogm_cnt_lock);

	kref_get(&orig_node->refcount);
	hash_added = batadv_hash_add(bat_priv->orig_hash, batadv_compare_orig,
				     batadv_choose_orig, orig_node,
				     &orig_node->hash_entry);
	अगर (hash_added != 0)
		जाओ मुक्त_orig_node_hash;

	वापस orig_node;

मुक्त_orig_node_hash:
	/* reference क्रम batadv_hash_add */
	batadv_orig_node_put(orig_node);
	/* reference from batadv_orig_node_new */
	batadv_orig_node_put(orig_node);

	वापस शून्य;
पूर्ण

अटल काष्ठा batadv_neigh_node *
batadv_iv_ogm_neigh_new(काष्ठा batadv_hard_अगरace *hard_अगरace,
			स्थिर u8 *neigh_addr,
			काष्ठा batadv_orig_node *orig_node,
			काष्ठा batadv_orig_node *orig_neigh)
अणु
	काष्ठा batadv_neigh_node *neigh_node;

	neigh_node = batadv_neigh_node_get_or_create(orig_node,
						     hard_अगरace, neigh_addr);
	अगर (!neigh_node)
		जाओ out;

	neigh_node->orig_node = orig_neigh;

out:
	वापस neigh_node;
पूर्ण

अटल पूर्णांक batadv_iv_ogm_अगरace_enable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	अचिन्हित अक्षर *ogm_buff;
	u32 अक्रमom_seqno;

	mutex_lock(&hard_अगरace->bat_iv.ogm_buff_mutex);

	/* अक्रमomize initial seqno to aव्योम collision */
	get_अक्रमom_bytes(&अक्रमom_seqno, माप(अक्रमom_seqno));
	atomic_set(&hard_अगरace->bat_iv.ogm_seqno, अक्रमom_seqno);

	hard_अगरace->bat_iv.ogm_buff_len = BATADV_OGM_HLEN;
	ogm_buff = kदो_स्मृति(hard_अगरace->bat_iv.ogm_buff_len, GFP_ATOMIC);
	अगर (!ogm_buff) अणु
		mutex_unlock(&hard_अगरace->bat_iv.ogm_buff_mutex);
		वापस -ENOMEM;
	पूर्ण

	hard_अगरace->bat_iv.ogm_buff = ogm_buff;

	batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)ogm_buff;
	batadv_ogm_packet->packet_type = BATADV_IV_OGM;
	batadv_ogm_packet->version = BATADV_COMPAT_VERSION;
	batadv_ogm_packet->ttl = 2;
	batadv_ogm_packet->flags = BATADV_NO_FLAGS;
	batadv_ogm_packet->reserved = 0;
	batadv_ogm_packet->tq = BATADV_TQ_MAX_VALUE;

	mutex_unlock(&hard_अगरace->bat_iv.ogm_buff_mutex);

	वापस 0;
पूर्ण

अटल व्योम batadv_iv_ogm_अगरace_disable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	mutex_lock(&hard_अगरace->bat_iv.ogm_buff_mutex);

	kमुक्त(hard_अगरace->bat_iv.ogm_buff);
	hard_अगरace->bat_iv.ogm_buff = शून्य;

	mutex_unlock(&hard_अगरace->bat_iv.ogm_buff_mutex);
पूर्ण

अटल व्योम batadv_iv_ogm_अगरace_update_mac(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	व्योम *ogm_buff;

	mutex_lock(&hard_अगरace->bat_iv.ogm_buff_mutex);

	ogm_buff = hard_अगरace->bat_iv.ogm_buff;
	अगर (!ogm_buff)
		जाओ unlock;

	batadv_ogm_packet = ogm_buff;
	ether_addr_copy(batadv_ogm_packet->orig,
			hard_अगरace->net_dev->dev_addr);
	ether_addr_copy(batadv_ogm_packet->prev_sender,
			hard_अगरace->net_dev->dev_addr);

unlock:
	mutex_unlock(&hard_अगरace->bat_iv.ogm_buff_mutex);
पूर्ण

अटल व्योम
batadv_iv_ogm_primary_अगरace_set(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	व्योम *ogm_buff;

	mutex_lock(&hard_अगरace->bat_iv.ogm_buff_mutex);

	ogm_buff = hard_अगरace->bat_iv.ogm_buff;
	अगर (!ogm_buff)
		जाओ unlock;

	batadv_ogm_packet = ogm_buff;
	batadv_ogm_packet->ttl = BATADV_TTL;

unlock:
	mutex_unlock(&hard_अगरace->bat_iv.ogm_buff_mutex);
पूर्ण

/* when करो we schedule our own ogm to be sent */
अटल अचिन्हित दीर्घ
batadv_iv_ogm_emit_send_समय(स्थिर काष्ठा batadv_priv *bat_priv)
अणु
	अचिन्हित पूर्णांक msecs;

	msecs = atomic_पढ़ो(&bat_priv->orig_पूर्णांकerval) - BATADV_JITTER;
	msecs += pअक्रमom_u32_max(2 * BATADV_JITTER);

	वापस jअगरfies + msecs_to_jअगरfies(msecs);
पूर्ण

/* when करो we schedule a ogm packet to be sent */
अटल अचिन्हित दीर्घ batadv_iv_ogm_fwd_send_समय(व्योम)
अणु
	वापस jअगरfies + msecs_to_jअगरfies(pअक्रमom_u32_max(BATADV_JITTER / 2));
पूर्ण

/* apply hop penalty क्रम a normal link */
अटल u8 batadv_hop_penalty(u8 tq, स्थिर काष्ठा batadv_priv *bat_priv)
अणु
	पूर्णांक hop_penalty = atomic_पढ़ो(&bat_priv->hop_penalty);
	पूर्णांक new_tq;

	new_tq = tq * (BATADV_TQ_MAX_VALUE - hop_penalty);
	new_tq /= BATADV_TQ_MAX_VALUE;

	वापस new_tq;
पूर्ण

/**
 * batadv_iv_ogm_aggr_packet() - checks अगर there is another OGM attached
 * @buff_pos: current position in the skb
 * @packet_len: total length of the skb
 * @ogm_packet: potential OGM in buffer
 *
 * Return: true अगर there is enough space क्रम another OGM, false otherwise.
 */
अटल bool
batadv_iv_ogm_aggr_packet(पूर्णांक buff_pos, पूर्णांक packet_len,
			  स्थिर काष्ठा batadv_ogm_packet *ogm_packet)
अणु
	पूर्णांक next_buff_pos = 0;

	/* check अगर there is enough space क्रम the header */
	next_buff_pos += buff_pos + माप(*ogm_packet);
	अगर (next_buff_pos > packet_len)
		वापस false;

	/* check अगर there is enough space क्रम the optional TVLV */
	next_buff_pos += ntohs(ogm_packet->tvlv_len);

	वापस (next_buff_pos <= packet_len) &&
	       (next_buff_pos <= BATADV_MAX_AGGREGATION_BYTES);
पूर्ण

/* send a baपंचांगan ogm to a given पूर्णांकerface */
अटल व्योम batadv_iv_ogm_send_to_अगर(काष्ठा batadv_क्रमw_packet *क्रमw_packet,
				     काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	स्थिर अक्षर *fwd_str;
	u8 packet_num;
	s16 buff_pos;
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	काष्ठा sk_buff *skb;
	u8 *packet_pos;

	अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
		वापस;

	packet_num = 0;
	buff_pos = 0;
	packet_pos = क्रमw_packet->skb->data;
	batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)packet_pos;

	/* adjust all flags and log packets */
	जबतक (batadv_iv_ogm_aggr_packet(buff_pos, क्रमw_packet->packet_len,
					 batadv_ogm_packet)) अणु
		/* we might have aggregated direct link packets with an
		 * ordinary base packet
		 */
		अगर (क्रमw_packet->direct_link_flags & BIT(packet_num) &&
		    क्रमw_packet->अगर_incoming == hard_अगरace)
			batadv_ogm_packet->flags |= BATADV_सूचीECTLINK;
		अन्यथा
			batadv_ogm_packet->flags &= ~BATADV_सूचीECTLINK;

		अगर (packet_num > 0 || !क्रमw_packet->own)
			fwd_str = "Forwarding";
		अन्यथा
			fwd_str = "Sending own";

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s %spacket (originator %pM, seqno %u, TQ %d, TTL %d, IDF %s) on interface %s [%pM]\n",
			   fwd_str, (packet_num > 0 ? "aggregated " : ""),
			   batadv_ogm_packet->orig,
			   ntohl(batadv_ogm_packet->seqno),
			   batadv_ogm_packet->tq, batadv_ogm_packet->ttl,
			   ((batadv_ogm_packet->flags & BATADV_सूचीECTLINK) ?
			    "on" : "off"),
			   hard_अगरace->net_dev->name,
			   hard_अगरace->net_dev->dev_addr);

		buff_pos += BATADV_OGM_HLEN;
		buff_pos += ntohs(batadv_ogm_packet->tvlv_len);
		packet_num++;
		packet_pos = क्रमw_packet->skb->data + buff_pos;
		batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)packet_pos;
	पूर्ण

	/* create clone because function is called more than once */
	skb = skb_clone(क्रमw_packet->skb, GFP_ATOMIC);
	अगर (skb) अणु
		batadv_inc_counter(bat_priv, BATADV_CNT_MGMT_TX);
		batadv_add_counter(bat_priv, BATADV_CNT_MGMT_TX_BYTES,
				   skb->len + ETH_HLEN);
		batadv_send_broadcast_skb(skb, hard_अगरace);
	पूर्ण
पूर्ण

/* send a baपंचांगan ogm packet */
अटल व्योम batadv_iv_ogm_emit(काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	काष्ठा net_device *soft_अगरace;

	अगर (!क्रमw_packet->अगर_incoming) अणु
		pr_err("Error - can't forward packet: incoming iface not specified\n");
		वापस;
	पूर्ण

	soft_अगरace = क्रमw_packet->अगर_incoming->soft_अगरace;

	अगर (WARN_ON(!क्रमw_packet->अगर_outgoing))
		वापस;

	अगर (क्रमw_packet->अगर_outgoing->soft_अगरace != soft_अगरace) अणु
		pr_warn("%s: soft interface switch for queued OGM\n", __func__);
		वापस;
	पूर्ण

	अगर (क्रमw_packet->अगर_incoming->अगर_status != BATADV_IF_ACTIVE)
		वापस;

	/* only क्रम one specअगरic outgoing पूर्णांकerface */
	batadv_iv_ogm_send_to_अगर(क्रमw_packet, क्रमw_packet->अगर_outgoing);
पूर्ण

/**
 * batadv_iv_ogm_can_aggregate() - find out अगर an OGM can be aggregated on an
 *  existing क्रमward packet
 * @new_bat_ogm_packet: OGM packet to be aggregated
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @packet_len: (total) length of the OGM
 * @send_समय: बारtamp (jअगरfies) when the packet is to be sent
 * @directlink: true अगर this is a direct link packet
 * @अगर_incoming: पूर्णांकerface where the packet was received
 * @अगर_outgoing: पूर्णांकerface क्रम which the retransmission should be considered
 * @क्रमw_packet: the क्रमwarded packet which should be checked
 *
 * Return: true अगर new_packet can be aggregated with क्रमw_packet
 */
अटल bool
batadv_iv_ogm_can_aggregate(स्थिर काष्ठा batadv_ogm_packet *new_bat_ogm_packet,
			    काष्ठा batadv_priv *bat_priv,
			    पूर्णांक packet_len, अचिन्हित दीर्घ send_समय,
			    bool directlink,
			    स्थिर काष्ठा batadv_hard_अगरace *अगर_incoming,
			    स्थिर काष्ठा batadv_hard_अगरace *अगर_outgoing,
			    स्थिर काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	पूर्णांक aggregated_bytes = क्रमw_packet->packet_len + packet_len;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	bool res = false;
	अचिन्हित दीर्घ aggregation_end_समय;

	batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)क्रमw_packet->skb->data;
	aggregation_end_समय = send_समय;
	aggregation_end_समय += msecs_to_jअगरfies(BATADV_MAX_AGGREGATION_MS);

	/* we can aggregate the current packet to this aggregated packet
	 * अगर:
	 *
	 * - the send समय is within our MAX_AGGREGATION_MS समय
	 * - the resulting packet won't be bigger than
	 *   MAX_AGGREGATION_BYTES
	 * otherwise aggregation is not possible
	 */
	अगर (!समय_beक्रमe(send_समय, क्रमw_packet->send_समय) ||
	    !समय_after_eq(aggregation_end_समय, क्रमw_packet->send_समय))
		वापस false;

	अगर (aggregated_bytes > BATADV_MAX_AGGREGATION_BYTES)
		वापस false;

	/* packet is not leaving on the same पूर्णांकerface. */
	अगर (क्रमw_packet->अगर_outgoing != अगर_outgoing)
		वापस false;

	/* check aggregation compatibility
	 * -> direct link packets are broadcasted on
	 *    their पूर्णांकerface only
	 * -> aggregate packet अगर the current packet is
	 *    a "global" packet as well as the base
	 *    packet
	 */
	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		वापस false;

	/* packets without direct link flag and high TTL
	 * are flooded through the net
	 */
	अगर (!directlink &&
	    !(batadv_ogm_packet->flags & BATADV_सूचीECTLINK) &&
	    batadv_ogm_packet->ttl != 1 &&

	    /* own packets originating non-primary
	     * पूर्णांकerfaces leave only that पूर्णांकerface
	     */
	    (!क्रमw_packet->own ||
	     क्रमw_packet->अगर_incoming == primary_अगर)) अणु
		res = true;
		जाओ out;
	पूर्ण

	/* अगर the incoming packet is sent via this one
	 * पूर्णांकerface only - we still can aggregate
	 */
	अगर (directlink &&
	    new_bat_ogm_packet->ttl == 1 &&
	    क्रमw_packet->अगर_incoming == अगर_incoming &&

	    /* packets from direct neighbors or
	     * own secondary पूर्णांकerface packets
	     * (= secondary पूर्णांकerface packets in general)
	     */
	    (batadv_ogm_packet->flags & BATADV_सूचीECTLINK ||
	     (क्रमw_packet->own &&
	      क्रमw_packet->अगर_incoming != primary_अगर))) अणु
		res = true;
		जाओ out;
	पूर्ण

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	वापस res;
पूर्ण

/**
 * batadv_iv_ogm_aggregate_new() - create a new aggregated packet and add this
 *  packet to it.
 * @packet_buff: poपूर्णांकer to the OGM
 * @packet_len: (total) length of the OGM
 * @send_समय: बारtamp (jअगरfies) when the packet is to be sent
 * @direct_link: whether this OGM has direct link status
 * @अगर_incoming: पूर्णांकerface where the packet was received
 * @अगर_outgoing: पूर्णांकerface क्रम which the retransmission should be considered
 * @own_packet: true अगर it is a self-generated ogm
 */
अटल व्योम batadv_iv_ogm_aggregate_new(स्थिर अचिन्हित अक्षर *packet_buff,
					पूर्णांक packet_len, अचिन्हित दीर्घ send_समय,
					bool direct_link,
					काष्ठा batadv_hard_अगरace *अगर_incoming,
					काष्ठा batadv_hard_अगरace *अगर_outgoing,
					पूर्णांक own_packet)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_क्रमw_packet *क्रमw_packet_aggr;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *skb_buff;
	अचिन्हित पूर्णांक skb_size;
	atomic_t *queue_left = own_packet ? शून्य : &bat_priv->baपंचांगan_queue_left;

	अगर (atomic_पढ़ो(&bat_priv->aggregated_ogms) &&
	    packet_len < BATADV_MAX_AGGREGATION_BYTES)
		skb_size = BATADV_MAX_AGGREGATION_BYTES;
	अन्यथा
		skb_size = packet_len;

	skb_size += ETH_HLEN;

	skb = netdev_alloc_skb_ip_align(शून्य, skb_size);
	अगर (!skb)
		वापस;

	क्रमw_packet_aggr = batadv_क्रमw_packet_alloc(अगर_incoming, अगर_outgoing,
						    queue_left, bat_priv, skb);
	अगर (!क्रमw_packet_aggr) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	क्रमw_packet_aggr->skb->priority = TC_PRIO_CONTROL;
	skb_reserve(क्रमw_packet_aggr->skb, ETH_HLEN);

	skb_buff = skb_put(क्रमw_packet_aggr->skb, packet_len);
	क्रमw_packet_aggr->packet_len = packet_len;
	स_नकल(skb_buff, packet_buff, packet_len);

	क्रमw_packet_aggr->own = own_packet;
	क्रमw_packet_aggr->direct_link_flags = BATADV_NO_FLAGS;
	क्रमw_packet_aggr->send_समय = send_समय;

	/* save packet direct link flag status */
	अगर (direct_link)
		क्रमw_packet_aggr->direct_link_flags |= 1;

	INIT_DELAYED_WORK(&क्रमw_packet_aggr->delayed_work,
			  batadv_iv_send_outstanding_bat_ogm_packet);

	batadv_क्रमw_packet_ogmv1_queue(bat_priv, क्रमw_packet_aggr, send_समय);
पूर्ण

/* aggregate a new packet पूर्णांकo the existing ogm packet */
अटल व्योम batadv_iv_ogm_aggregate(काष्ठा batadv_क्रमw_packet *क्रमw_packet_aggr,
				    स्थिर अचिन्हित अक्षर *packet_buff,
				    पूर्णांक packet_len, bool direct_link)
अणु
	अचिन्हित दीर्घ new_direct_link_flag;

	skb_put_data(क्रमw_packet_aggr->skb, packet_buff, packet_len);
	क्रमw_packet_aggr->packet_len += packet_len;
	क्रमw_packet_aggr->num_packets++;

	/* save packet direct link flag status */
	अगर (direct_link) अणु
		new_direct_link_flag = BIT(क्रमw_packet_aggr->num_packets);
		क्रमw_packet_aggr->direct_link_flags |= new_direct_link_flag;
	पूर्ण
पूर्ण

/**
 * batadv_iv_ogm_queue_add() - queue up an OGM क्रम transmission
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @packet_buff: poपूर्णांकer to the OGM
 * @packet_len: (total) length of the OGM
 * @अगर_incoming: पूर्णांकerface where the packet was received
 * @अगर_outgoing: पूर्णांकerface क्रम which the retransmission should be considered
 * @own_packet: true अगर it is a self-generated ogm
 * @send_समय: बारtamp (jअगरfies) when the packet is to be sent
 */
अटल व्योम batadv_iv_ogm_queue_add(काष्ठा batadv_priv *bat_priv,
				    अचिन्हित अक्षर *packet_buff,
				    पूर्णांक packet_len,
				    काष्ठा batadv_hard_अगरace *अगर_incoming,
				    काष्ठा batadv_hard_अगरace *अगर_outgoing,
				    पूर्णांक own_packet, अचिन्हित दीर्घ send_समय)
अणु
	/* _aggr -> poपूर्णांकer to the packet we want to aggregate with
	 * _pos -> poपूर्णांकer to the position in the queue
	 */
	काष्ठा batadv_क्रमw_packet *क्रमw_packet_aggr = शून्य;
	काष्ठा batadv_क्रमw_packet *क्रमw_packet_pos = शून्य;
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	bool direct_link;
	अचिन्हित दीर्घ max_aggregation_jअगरfies;

	batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)packet_buff;
	direct_link = !!(batadv_ogm_packet->flags & BATADV_सूचीECTLINK);
	max_aggregation_jअगरfies = msecs_to_jअगरfies(BATADV_MAX_AGGREGATION_MS);

	/* find position क्रम the packet in the क्रमward queue */
	spin_lock_bh(&bat_priv->क्रमw_bat_list_lock);
	/* own packets are not to be aggregated */
	अगर (atomic_पढ़ो(&bat_priv->aggregated_ogms) && !own_packet) अणु
		hlist_क्रम_each_entry(क्रमw_packet_pos,
				     &bat_priv->क्रमw_bat_list, list) अणु
			अगर (batadv_iv_ogm_can_aggregate(batadv_ogm_packet,
							bat_priv, packet_len,
							send_समय, direct_link,
							अगर_incoming,
							अगर_outgoing,
							क्रमw_packet_pos)) अणु
				क्रमw_packet_aggr = क्रमw_packet_pos;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* nothing to aggregate with - either aggregation disabled or no
	 * suitable aggregation packet found
	 */
	अगर (!क्रमw_packet_aggr) अणु
		/* the following section can run without the lock */
		spin_unlock_bh(&bat_priv->क्रमw_bat_list_lock);

		/* अगर we could not aggregate this packet with one of the others
		 * we hold it back क्रम a जबतक, so that it might be aggregated
		 * later on
		 */
		अगर (!own_packet && atomic_पढ़ो(&bat_priv->aggregated_ogms))
			send_समय += max_aggregation_jअगरfies;

		batadv_iv_ogm_aggregate_new(packet_buff, packet_len,
					    send_समय, direct_link,
					    अगर_incoming, अगर_outgoing,
					    own_packet);
	पूर्ण अन्यथा अणु
		batadv_iv_ogm_aggregate(क्रमw_packet_aggr, packet_buff,
					packet_len, direct_link);
		spin_unlock_bh(&bat_priv->क्रमw_bat_list_lock);
	पूर्ण
पूर्ण

अटल व्योम batadv_iv_ogm_क्रमward(काष्ठा batadv_orig_node *orig_node,
				  स्थिर काष्ठा ethhdr *ethhdr,
				  काष्ठा batadv_ogm_packet *batadv_ogm_packet,
				  bool is_single_hop_neigh,
				  bool is_from_best_next_hop,
				  काष्ठा batadv_hard_अगरace *अगर_incoming,
				  काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	u16 tvlv_len;

	अगर (batadv_ogm_packet->ttl <= 1) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv, "ttl exceeded\n");
		वापस;
	पूर्ण

	अगर (!is_from_best_next_hop) अणु
		/* Mark the क्रमwarded packet when it is not coming from our
		 * best next hop. We still need to क्रमward the packet क्रम our
		 * neighbor link quality detection to work in हाल the packet
		 * originated from a single hop neighbor. Otherwise we can
		 * simply drop the ogm.
		 */
		अगर (is_single_hop_neigh)
			batadv_ogm_packet->flags |= BATADV_NOT_BEST_NEXT_HOP;
		अन्यथा
			वापस;
	पूर्ण

	tvlv_len = ntohs(batadv_ogm_packet->tvlv_len);

	batadv_ogm_packet->ttl--;
	ether_addr_copy(batadv_ogm_packet->prev_sender, ethhdr->h_source);

	/* apply hop penalty */
	batadv_ogm_packet->tq = batadv_hop_penalty(batadv_ogm_packet->tq,
						   bat_priv);

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Forwarding packet: tq: %i, ttl: %i\n",
		   batadv_ogm_packet->tq, batadv_ogm_packet->ttl);

	अगर (is_single_hop_neigh)
		batadv_ogm_packet->flags |= BATADV_सूचीECTLINK;
	अन्यथा
		batadv_ogm_packet->flags &= ~BATADV_सूचीECTLINK;

	batadv_iv_ogm_queue_add(bat_priv, (अचिन्हित अक्षर *)batadv_ogm_packet,
				BATADV_OGM_HLEN + tvlv_len,
				अगर_incoming, अगर_outgoing, 0,
				batadv_iv_ogm_fwd_send_समय());
पूर्ण

/**
 * batadv_iv_ogm_slide_own_bcast_winकरोw() - bitshअगरt own OGM broadcast winकरोws
 *  क्रम the given पूर्णांकerface
 * @hard_अगरace: the पूर्णांकerface क्रम which the winकरोws have to be shअगरted
 */
अटल व्योम
batadv_iv_ogm_slide_own_bcast_winकरोw(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_head *head;
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	अचिन्हित दीर्घ *word;
	u32 i;
	u8 *w;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(orig_node, head, hash_entry) अणु
			hlist_क्रम_each_entry_rcu(orig_अगरinfo,
						 &orig_node->अगरinfo_list,
						 list) अणु
				अगर (orig_अगरinfo->अगर_outgoing != hard_अगरace)
					जारी;

				spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);
				word = orig_अगरinfo->bat_iv.bcast_own;
				batadv_bit_get_packet(bat_priv, word, 1, 0);
				w = &orig_अगरinfo->bat_iv.bcast_own_sum;
				*w = biपंचांगap_weight(word,
						   BATADV_TQ_LOCAL_WINDOW_SIZE);
				spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/**
 * batadv_iv_ogm_schedule_buff() - schedule submission of hardअगर ogm buffer
 * @hard_अगरace: पूर्णांकerface whose ogm buffer should be transmitted
 */
अटल व्योम batadv_iv_ogm_schedule_buff(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	अचिन्हित अक्षर **ogm_buff = &hard_अगरace->bat_iv.ogm_buff;
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	काष्ठा batadv_hard_अगरace *primary_अगर, *पंचांगp_hard_अगरace;
	पूर्णांक *ogm_buff_len = &hard_अगरace->bat_iv.ogm_buff_len;
	u32 seqno;
	u16 tvlv_len = 0;
	अचिन्हित दीर्घ send_समय;

	lockdep_निश्चित_held(&hard_अगरace->bat_iv.ogm_buff_mutex);

	/* पूर्णांकerface alपढ़ोy disabled by batadv_iv_ogm_अगरace_disable */
	अगर (!*ogm_buff)
		वापस;

	/* the पूर्णांकerface माला_लो activated here to aव्योम race conditions between
	 * the moment of activating the पूर्णांकerface in
	 * hardअगर_activate_पूर्णांकerface() where the originator mac is set and
	 * outdated packets (especially uninitialized mac addresses) in the
	 * packet queue
	 */
	अगर (hard_अगरace->अगर_status == BATADV_IF_TO_BE_ACTIVATED)
		hard_अगरace->अगर_status = BATADV_IF_ACTIVE;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);

	अगर (hard_अगरace == primary_अगर) अणु
		/* tt changes have to be committed beक्रमe the tvlv data is
		 * appended as it may alter the tt tvlv container
		 */
		batadv_tt_local_commit_changes(bat_priv);
		tvlv_len = batadv_tvlv_container_ogm_append(bat_priv, ogm_buff,
							    ogm_buff_len,
							    BATADV_OGM_HLEN);
	पूर्ण

	batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)(*ogm_buff);
	batadv_ogm_packet->tvlv_len = htons(tvlv_len);

	/* change sequence number to network order */
	seqno = (u32)atomic_पढ़ो(&hard_अगरace->bat_iv.ogm_seqno);
	batadv_ogm_packet->seqno = htonl(seqno);
	atomic_inc(&hard_अगरace->bat_iv.ogm_seqno);

	batadv_iv_ogm_slide_own_bcast_winकरोw(hard_अगरace);

	send_समय = batadv_iv_ogm_emit_send_समय(bat_priv);

	अगर (hard_अगरace != primary_अगर) अणु
		/* OGMs from secondary पूर्णांकerfaces are only scheduled on their
		 * respective पूर्णांकerfaces.
		 */
		batadv_iv_ogm_queue_add(bat_priv, *ogm_buff, *ogm_buff_len,
					hard_अगरace, hard_अगरace, 1, send_समय);
		जाओ out;
	पूर्ण

	/* OGMs from primary पूर्णांकerfaces are scheduled on all
	 * पूर्णांकerfaces.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(पंचांगp_hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (पंचांगp_hard_अगरace->soft_अगरace != hard_अगरace->soft_अगरace)
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp_hard_अगरace->refcount))
			जारी;

		batadv_iv_ogm_queue_add(bat_priv, *ogm_buff,
					*ogm_buff_len, hard_अगरace,
					पंचांगp_hard_अगरace, 1, send_समय);

		batadv_hardअगर_put(पंचांगp_hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

अटल व्योम batadv_iv_ogm_schedule(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अगर (hard_अगरace->अगर_status == BATADV_IF_NOT_IN_USE ||
	    hard_अगरace->अगर_status == BATADV_IF_TO_BE_REMOVED)
		वापस;

	mutex_lock(&hard_अगरace->bat_iv.ogm_buff_mutex);
	batadv_iv_ogm_schedule_buff(hard_अगरace);
	mutex_unlock(&hard_अगरace->bat_iv.ogm_buff_mutex);
पूर्ण

/**
 * batadv_iv_orig_अगरinfo_sum() - Get bcast_own sum क्रम originator over पूर्णांकerface
 * @orig_node: originator which reproadcasted the OGMs directly
 * @अगर_outgoing: पूर्णांकerface which transmitted the original OGM and received the
 *  direct rebroadcast
 *
 * Return: Number of replied (rebroadcasted) OGMs which were transmitted by
 *  an originator and directly (without पूर्णांकermediate hop) received by a specअगरic
 *  पूर्णांकerface
 */
अटल u8 batadv_iv_orig_अगरinfo_sum(काष्ठा batadv_orig_node *orig_node,
				    काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	u8 sum;

	orig_अगरinfo = batadv_orig_अगरinfo_get(orig_node, अगर_outgoing);
	अगर (!orig_अगरinfo)
		वापस 0;

	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);
	sum = orig_अगरinfo->bat_iv.bcast_own_sum;
	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	batadv_orig_अगरinfo_put(orig_अगरinfo);

	वापस sum;
पूर्ण

/**
 * batadv_iv_ogm_orig_update() - use OGM to update corresponding data in an
 *  originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: the orig node who originally emitted the ogm packet
 * @orig_अगरinfo: अगरinfo क्रम the outgoing पूर्णांकerface of the orig_node
 * @ethhdr: Ethernet header of the OGM
 * @batadv_ogm_packet: the ogm packet
 * @अगर_incoming: पूर्णांकerface where the packet was received
 * @अगर_outgoing: पूर्णांकerface क्रम which the retransmission should be considered
 * @dup_status: the duplicate status of this ogm packet.
 */
अटल व्योम
batadv_iv_ogm_orig_update(काष्ठा batadv_priv *bat_priv,
			  काष्ठा batadv_orig_node *orig_node,
			  काष्ठा batadv_orig_अगरinfo *orig_अगरinfo,
			  स्थिर काष्ठा ethhdr *ethhdr,
			  स्थिर काष्ठा batadv_ogm_packet *batadv_ogm_packet,
			  काष्ठा batadv_hard_अगरace *अगर_incoming,
			  काष्ठा batadv_hard_अगरace *अगर_outgoing,
			  क्रमागत batadv_dup_status dup_status)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo = शून्य;
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य;
	काष्ठा batadv_neigh_node *neigh_node = शून्य;
	काष्ठा batadv_neigh_node *पंचांगp_neigh_node = शून्य;
	काष्ठा batadv_neigh_node *router = शून्य;
	u8 sum_orig, sum_neigh;
	u8 *neigh_addr;
	u8 tq_avg;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "%s(): Searching and updating originator entry of received packet\n",
		   __func__);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_neigh_node,
				 &orig_node->neigh_list, list) अणु
		neigh_addr = पंचांगp_neigh_node->addr;
		अगर (batadv_compare_eth(neigh_addr, ethhdr->h_source) &&
		    पंचांगp_neigh_node->अगर_incoming == अगर_incoming &&
		    kref_get_unless_zero(&पंचांगp_neigh_node->refcount)) अणु
			अगर (WARN(neigh_node, "too many matching neigh_nodes"))
				batadv_neigh_node_put(neigh_node);
			neigh_node = पंचांगp_neigh_node;
			जारी;
		पूर्ण

		अगर (dup_status != BATADV_NO_DUP)
			जारी;

		/* only update the entry क्रम this outgoing पूर्णांकerface */
		neigh_अगरinfo = batadv_neigh_अगरinfo_get(पंचांगp_neigh_node,
						       अगर_outgoing);
		अगर (!neigh_अगरinfo)
			जारी;

		spin_lock_bh(&पंचांगp_neigh_node->अगरinfo_lock);
		batadv_ring_buffer_set(neigh_अगरinfo->bat_iv.tq_recv,
				       &neigh_अगरinfo->bat_iv.tq_index, 0);
		tq_avg = batadv_ring_buffer_avg(neigh_अगरinfo->bat_iv.tq_recv);
		neigh_अगरinfo->bat_iv.tq_avg = tq_avg;
		spin_unlock_bh(&पंचांगp_neigh_node->अगरinfo_lock);

		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
		neigh_अगरinfo = शून्य;
	पूर्ण

	अगर (!neigh_node) अणु
		काष्ठा batadv_orig_node *orig_पंचांगp;

		orig_पंचांगp = batadv_iv_ogm_orig_get(bat_priv, ethhdr->h_source);
		अगर (!orig_पंचांगp)
			जाओ unlock;

		neigh_node = batadv_iv_ogm_neigh_new(अगर_incoming,
						     ethhdr->h_source,
						     orig_node, orig_पंचांगp);

		batadv_orig_node_put(orig_पंचांगp);
		अगर (!neigh_node)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Updating existing last-hop neighbor of originator\n");
	पूर्ण

	rcu_पढ़ो_unlock();
	neigh_अगरinfo = batadv_neigh_अगरinfo_new(neigh_node, अगर_outgoing);
	अगर (!neigh_अगरinfo)
		जाओ out;

	neigh_node->last_seen = jअगरfies;

	spin_lock_bh(&neigh_node->अगरinfo_lock);
	batadv_ring_buffer_set(neigh_अगरinfo->bat_iv.tq_recv,
			       &neigh_अगरinfo->bat_iv.tq_index,
			       batadv_ogm_packet->tq);
	tq_avg = batadv_ring_buffer_avg(neigh_अगरinfo->bat_iv.tq_recv);
	neigh_अगरinfo->bat_iv.tq_avg = tq_avg;
	spin_unlock_bh(&neigh_node->अगरinfo_lock);

	अगर (dup_status == BATADV_NO_DUP) अणु
		orig_अगरinfo->last_ttl = batadv_ogm_packet->ttl;
		neigh_अगरinfo->last_ttl = batadv_ogm_packet->ttl;
	पूर्ण

	/* अगर this neighbor alपढ़ोy is our next hop there is nothing
	 * to change
	 */
	router = batadv_orig_router_get(orig_node, अगर_outgoing);
	अगर (router == neigh_node)
		जाओ out;

	अगर (router) अणु
		router_अगरinfo = batadv_neigh_अगरinfo_get(router, अगर_outgoing);
		अगर (!router_अगरinfo)
			जाओ out;

		/* अगर this neighbor करोes not offer a better TQ we won't
		 * consider it
		 */
		अगर (router_अगरinfo->bat_iv.tq_avg > neigh_अगरinfo->bat_iv.tq_avg)
			जाओ out;
	पूर्ण

	/* अगर the TQ is the same and the link not more symmetric we
	 * won't consider it either
	 */
	अगर (router_अगरinfo &&
	    neigh_अगरinfo->bat_iv.tq_avg == router_अगरinfo->bat_iv.tq_avg) अणु
		sum_orig = batadv_iv_orig_अगरinfo_sum(router->orig_node,
						     router->अगर_incoming);
		sum_neigh = batadv_iv_orig_अगरinfo_sum(neigh_node->orig_node,
						      neigh_node->अगर_incoming);
		अगर (sum_orig >= sum_neigh)
			जाओ out;
	पूर्ण

	batadv_update_route(bat_priv, orig_node, अगर_outgoing, neigh_node);
	जाओ out;

unlock:
	rcu_पढ़ो_unlock();
out:
	अगर (neigh_node)
		batadv_neigh_node_put(neigh_node);
	अगर (router)
		batadv_neigh_node_put(router);
	अगर (neigh_अगरinfo)
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);
पूर्ण

/**
 * batadv_iv_ogm_calc_tq() - calculate tq क्रम current received ogm packet
 * @orig_node: the orig node who originally emitted the ogm packet
 * @orig_neigh_node: the orig node काष्ठा of the neighbor who sent the packet
 * @batadv_ogm_packet: the ogm packet
 * @अगर_incoming: पूर्णांकerface where the packet was received
 * @अगर_outgoing: पूर्णांकerface क्रम which the retransmission should be considered
 *
 * Return: true अगर the link can be considered bidirectional, false otherwise
 */
अटल bool batadv_iv_ogm_calc_tq(काष्ठा batadv_orig_node *orig_node,
				  काष्ठा batadv_orig_node *orig_neigh_node,
				  काष्ठा batadv_ogm_packet *batadv_ogm_packet,
				  काष्ठा batadv_hard_अगरace *अगर_incoming,
				  काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_neigh_node *neigh_node = शून्य, *पंचांगp_neigh_node;
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo;
	u8 total_count;
	u8 orig_eq_count, neigh_rq_count, neigh_rq_inv, tq_own;
	अचिन्हित पूर्णांक tq_अगरace_hop_penalty = BATADV_TQ_MAX_VALUE;
	अचिन्हित पूर्णांक neigh_rq_inv_cube, neigh_rq_max_cube;
	अचिन्हित पूर्णांक tq_asym_penalty, inv_asym_penalty;
	अचिन्हित पूर्णांक combined_tq;
	bool ret = false;

	/* find corresponding one hop neighbor */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_neigh_node,
				 &orig_neigh_node->neigh_list, list) अणु
		अगर (!batadv_compare_eth(पंचांगp_neigh_node->addr,
					orig_neigh_node->orig))
			जारी;

		अगर (पंचांगp_neigh_node->अगर_incoming != अगर_incoming)
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp_neigh_node->refcount))
			जारी;

		neigh_node = पंचांगp_neigh_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!neigh_node)
		neigh_node = batadv_iv_ogm_neigh_new(अगर_incoming,
						     orig_neigh_node->orig,
						     orig_neigh_node,
						     orig_neigh_node);

	अगर (!neigh_node)
		जाओ out;

	/* अगर orig_node is direct neighbor update neigh_node last_seen */
	अगर (orig_node == orig_neigh_node)
		neigh_node->last_seen = jअगरfies;

	orig_node->last_seen = jअगरfies;

	/* find packet count of corresponding one hop neighbor */
	orig_eq_count = batadv_iv_orig_अगरinfo_sum(orig_neigh_node, अगर_incoming);
	neigh_अगरinfo = batadv_neigh_अगरinfo_new(neigh_node, अगर_outgoing);
	अगर (neigh_अगरinfo) अणु
		neigh_rq_count = neigh_अगरinfo->bat_iv.real_packet_count;
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
	पूर्ण अन्यथा अणु
		neigh_rq_count = 0;
	पूर्ण

	/* pay attention to not get a value bigger than 100 % */
	अगर (orig_eq_count > neigh_rq_count)
		total_count = neigh_rq_count;
	अन्यथा
		total_count = orig_eq_count;

	/* अगर we have too few packets (too less data) we set tq_own to zero
	 * अगर we receive too few packets it is not considered bidirectional
	 */
	अगर (total_count < BATADV_TQ_LOCAL_BIDRECT_SEND_MINIMUM ||
	    neigh_rq_count < BATADV_TQ_LOCAL_BIDRECT_RECV_MINIMUM)
		tq_own = 0;
	अन्यथा
		/* neigh_node->real_packet_count is never zero as we
		 * only purge old inक्रमmation when getting new
		 * inक्रमmation
		 */
		tq_own = (BATADV_TQ_MAX_VALUE * total_count) /	neigh_rq_count;

	/* 1 - ((1-x) ** 3), normalized to TQ_MAX_VALUE this करोes
	 * affect the nearly-symmetric links only a little, but
	 * punishes asymmetric links more.  This will give a value
	 * between 0 and TQ_MAX_VALUE
	 */
	neigh_rq_inv = BATADV_TQ_LOCAL_WINDOW_SIZE - neigh_rq_count;
	neigh_rq_inv_cube = neigh_rq_inv * neigh_rq_inv * neigh_rq_inv;
	neigh_rq_max_cube = BATADV_TQ_LOCAL_WINDOW_SIZE *
			    BATADV_TQ_LOCAL_WINDOW_SIZE *
			    BATADV_TQ_LOCAL_WINDOW_SIZE;
	inv_asym_penalty = BATADV_TQ_MAX_VALUE * neigh_rq_inv_cube;
	inv_asym_penalty /= neigh_rq_max_cube;
	tq_asym_penalty = BATADV_TQ_MAX_VALUE - inv_asym_penalty;
	tq_अगरace_hop_penalty -= atomic_पढ़ो(&अगर_incoming->hop_penalty);

	/* penalize अगर the OGM is क्रमwarded on the same पूर्णांकerface. WiFi
	 * पूर्णांकerfaces and other half duplex devices suffer from throughput
	 * drops as they can't send and receive at the same समय.
	 */
	अगर (अगर_outgoing && अगर_incoming == अगर_outgoing &&
	    batadv_is_wअगरi_hardअगर(अगर_outgoing))
		tq_अगरace_hop_penalty = batadv_hop_penalty(tq_अगरace_hop_penalty,
							  bat_priv);

	combined_tq = batadv_ogm_packet->tq *
		      tq_own *
		      tq_asym_penalty *
		      tq_अगरace_hop_penalty;
	combined_tq /= BATADV_TQ_MAX_VALUE *
		       BATADV_TQ_MAX_VALUE *
		       BATADV_TQ_MAX_VALUE;
	batadv_ogm_packet->tq = combined_tq;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "bidirectional: orig = %pM neigh = %pM => own_bcast = %2i, real recv = %2i, local tq: %3i, asym_penalty: %3i, iface_hop_penalty: %3i, total tq: %3i, if_incoming = %s, if_outgoing = %s\n",
		   orig_node->orig, orig_neigh_node->orig, total_count,
		   neigh_rq_count, tq_own, tq_asym_penalty,
		   tq_अगरace_hop_penalty, batadv_ogm_packet->tq,
		   अगर_incoming->net_dev->name,
		   अगर_outgoing ? अगर_outgoing->net_dev->name : "DEFAULT");

	/* अगर link has the minimum required transmission quality
	 * consider it bidirectional
	 */
	अगर (batadv_ogm_packet->tq >= BATADV_TQ_TOTAL_BIDRECT_LIMIT)
		ret = true;

out:
	अगर (neigh_node)
		batadv_neigh_node_put(neigh_node);
	वापस ret;
पूर्ण

/**
 * batadv_iv_ogm_update_seqnos() -  process a baपंचांगan packet क्रम all पूर्णांकerfaces,
 *  adjust the sequence number and find out whether it is a duplicate
 * @ethhdr: ethernet header of the packet
 * @batadv_ogm_packet: OGM packet to be considered
 * @अगर_incoming: पूर्णांकerface on which the OGM packet was received
 * @अगर_outgoing: पूर्णांकerface क्रम which the retransmission should be considered
 *
 * Return: duplicate status as क्रमागत batadv_dup_status
 */
अटल क्रमागत batadv_dup_status
batadv_iv_ogm_update_seqnos(स्थिर काष्ठा ethhdr *ethhdr,
			    स्थिर काष्ठा batadv_ogm_packet *batadv_ogm_packet,
			    स्थिर काष्ठा batadv_hard_अगरace *अगर_incoming,
			    काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo = शून्य;
	काष्ठा batadv_neigh_node *neigh_node;
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo;
	bool is_dup;
	s32 seq_dअगरf;
	bool need_update = false;
	पूर्णांक set_mark;
	क्रमागत batadv_dup_status ret = BATADV_NO_DUP;
	u32 seqno = ntohl(batadv_ogm_packet->seqno);
	u8 *neigh_addr;
	u8 packet_count;
	अचिन्हित दीर्घ *biपंचांगap;

	orig_node = batadv_iv_ogm_orig_get(bat_priv, batadv_ogm_packet->orig);
	अगर (!orig_node)
		वापस BATADV_NO_DUP;

	orig_अगरinfo = batadv_orig_अगरinfo_new(orig_node, अगर_outgoing);
	अगर (WARN_ON(!orig_अगरinfo)) अणु
		batadv_orig_node_put(orig_node);
		वापस 0;
	पूर्ण

	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);
	seq_dअगरf = seqno - orig_अगरinfo->last_real_seqno;

	/* संकेतize caller that the packet is to be dropped. */
	अगर (!hlist_empty(&orig_node->neigh_list) &&
	    batadv_winकरोw_रक्षित(bat_priv, seq_dअगरf,
				    BATADV_TQ_LOCAL_WINDOW_SIZE,
				    &orig_अगरinfo->baपंचांगan_seqno_reset, शून्य)) अणु
		ret = BATADV_PROTECTED;
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(neigh_node, &orig_node->neigh_list, list) अणु
		neigh_अगरinfo = batadv_neigh_अगरinfo_new(neigh_node,
						       अगर_outgoing);
		अगर (!neigh_अगरinfo)
			जारी;

		neigh_addr = neigh_node->addr;
		is_dup = batadv_test_bit(neigh_अगरinfo->bat_iv.real_bits,
					 orig_अगरinfo->last_real_seqno,
					 seqno);

		अगर (batadv_compare_eth(neigh_addr, ethhdr->h_source) &&
		    neigh_node->अगर_incoming == अगर_incoming) अणु
			set_mark = 1;
			अगर (is_dup)
				ret = BATADV_NEIGH_DUP;
		पूर्ण अन्यथा अणु
			set_mark = 0;
			अगर (is_dup && ret != BATADV_NEIGH_DUP)
				ret = BATADV_ORIG_DUP;
		पूर्ण

		/* अगर the winकरोw moved, set the update flag. */
		biपंचांगap = neigh_अगरinfo->bat_iv.real_bits;
		need_update |= batadv_bit_get_packet(bat_priv, biपंचांगap,
						     seq_dअगरf, set_mark);

		packet_count = biपंचांगap_weight(biपंचांगap,
					     BATADV_TQ_LOCAL_WINDOW_SIZE);
		neigh_अगरinfo->bat_iv.real_packet_count = packet_count;
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (need_update) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s updating last_seqno: old %u, new %u\n",
			   अगर_outgoing ? अगर_outgoing->net_dev->name : "DEFAULT",
			   orig_अगरinfo->last_real_seqno, seqno);
		orig_अगरinfo->last_real_seqno = seqno;
	पूर्ण

out:
	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);
	batadv_orig_node_put(orig_node);
	batadv_orig_अगरinfo_put(orig_अगरinfo);
	वापस ret;
पूर्ण

/**
 * batadv_iv_ogm_process_per_outअगर() - process a baपंचांगan iv OGM क्रम an outgoing
 *  पूर्णांकerface
 * @skb: the skb containing the OGM
 * @ogm_offset: offset from skb->data to start of ogm header
 * @orig_node: the (cached) orig node क्रम the originator of this OGM
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 * @अगर_outgoing: the पूर्णांकerface क्रम which the packet should be considered
 */
अटल व्योम
batadv_iv_ogm_process_per_outअगर(स्थिर काष्ठा sk_buff *skb, पूर्णांक ogm_offset,
				काष्ठा batadv_orig_node *orig_node,
				काष्ठा batadv_hard_अगरace *अगर_incoming,
				काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh = शून्य;
	काष्ठा batadv_neigh_node *router = शून्य;
	काष्ठा batadv_neigh_node *router_router = शून्य;
	काष्ठा batadv_orig_node *orig_neigh_node;
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_neigh_node *orig_neigh_router = शून्य;
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य;
	काष्ठा batadv_ogm_packet *ogm_packet;
	क्रमागत batadv_dup_status dup_status;
	bool is_from_best_next_hop = false;
	bool is_single_hop_neigh = false;
	bool sameseq, similar_ttl;
	काष्ठा sk_buff *skb_priv;
	काष्ठा ethhdr *ethhdr;
	u8 *prev_sender;
	bool is_bidirect;

	/* create a निजी copy of the skb, as some functions change tq value
	 * and/or flags.
	 */
	skb_priv = skb_copy(skb, GFP_ATOMIC);
	अगर (!skb_priv)
		वापस;

	ethhdr = eth_hdr(skb_priv);
	ogm_packet = (काष्ठा batadv_ogm_packet *)(skb_priv->data + ogm_offset);

	dup_status = batadv_iv_ogm_update_seqnos(ethhdr, ogm_packet,
						 अगर_incoming, अगर_outgoing);
	अगर (batadv_compare_eth(ethhdr->h_source, ogm_packet->orig))
		is_single_hop_neigh = true;

	अगर (dup_status == BATADV_PROTECTED) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: packet within seqno protection time (sender: %pM)\n",
			   ethhdr->h_source);
		जाओ out;
	पूर्ण

	अगर (ogm_packet->tq == 0) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: originator packet with tq equal 0\n");
		जाओ out;
	पूर्ण

	अगर (is_single_hop_neigh) अणु
		hardअगर_neigh = batadv_hardअगर_neigh_get(अगर_incoming,
						       ethhdr->h_source);
		अगर (hardअगर_neigh)
			hardअगर_neigh->last_seen = jअगरfies;
	पूर्ण

	router = batadv_orig_router_get(orig_node, अगर_outgoing);
	अगर (router) अणु
		router_router = batadv_orig_router_get(router->orig_node,
						       अगर_outgoing);
		router_अगरinfo = batadv_neigh_अगरinfo_get(router, अगर_outgoing);
	पूर्ण

	अगर ((router_अगरinfo && router_अगरinfo->bat_iv.tq_avg != 0) &&
	    (batadv_compare_eth(router->addr, ethhdr->h_source)))
		is_from_best_next_hop = true;

	prev_sender = ogm_packet->prev_sender;
	/* aव्योम temporary routing loops */
	अगर (router && router_router &&
	    (batadv_compare_eth(router->addr, prev_sender)) &&
	    !(batadv_compare_eth(ogm_packet->orig, prev_sender)) &&
	    (batadv_compare_eth(router->addr, router_router->addr))) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: ignoring all rebroadcast packets that may make me loop (sender: %pM)\n",
			   ethhdr->h_source);
		जाओ out;
	पूर्ण

	अगर (अगर_outgoing == BATADV_IF_DEFAULT)
		batadv_tvlv_ogm_receive(bat_priv, ogm_packet, orig_node);

	/* अगर sender is a direct neighbor the sender mac equals
	 * originator mac
	 */
	अगर (is_single_hop_neigh)
		orig_neigh_node = orig_node;
	अन्यथा
		orig_neigh_node = batadv_iv_ogm_orig_get(bat_priv,
							 ethhdr->h_source);

	अगर (!orig_neigh_node)
		जाओ out;

	/* Update nc_nodes of the originator */
	batadv_nc_update_nc_node(bat_priv, orig_node, orig_neigh_node,
				 ogm_packet, is_single_hop_neigh);

	orig_neigh_router = batadv_orig_router_get(orig_neigh_node,
						   अगर_outgoing);

	/* drop packet अगर sender is not a direct neighbor and अगर we
	 * करोn't route towards it
	 */
	अगर (!is_single_hop_neigh && !orig_neigh_router) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: OGM via unknown neighbor!\n");
		जाओ out_neigh;
	पूर्ण

	is_bidirect = batadv_iv_ogm_calc_tq(orig_node, orig_neigh_node,
					    ogm_packet, अगर_incoming,
					    अगर_outgoing);

	/* update ranking अगर it is not a duplicate or has the same
	 * seqno and similar ttl as the non-duplicate
	 */
	orig_अगरinfo = batadv_orig_अगरinfo_new(orig_node, अगर_outgoing);
	अगर (!orig_अगरinfo)
		जाओ out_neigh;

	sameseq = orig_अगरinfo->last_real_seqno == ntohl(ogm_packet->seqno);
	similar_ttl = (orig_अगरinfo->last_ttl - 3) <= ogm_packet->ttl;

	अगर (is_bidirect && (dup_status == BATADV_NO_DUP ||
			    (sameseq && similar_ttl))) अणु
		batadv_iv_ogm_orig_update(bat_priv, orig_node,
					  orig_अगरinfo, ethhdr,
					  ogm_packet, अगर_incoming,
					  अगर_outgoing, dup_status);
	पूर्ण
	batadv_orig_अगरinfo_put(orig_अगरinfo);

	/* only क्रमward क्रम specअगरic पूर्णांकerface, not क्रम the शेष one. */
	अगर (अगर_outgoing == BATADV_IF_DEFAULT)
		जाओ out_neigh;

	/* is single hop (direct) neighbor */
	अगर (is_single_hop_neigh) अणु
		/* OGMs from secondary पूर्णांकerfaces should only scheduled once
		 * per पूर्णांकerface where it has been received, not multiple बार
		 */
		अगर (ogm_packet->ttl <= 2 &&
		    अगर_incoming != अगर_outgoing) अणु
			batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
				   "Drop packet: OGM from secondary interface and wrong outgoing interface\n");
			जाओ out_neigh;
		पूर्ण
		/* mark direct link on incoming पूर्णांकerface */
		batadv_iv_ogm_क्रमward(orig_node, ethhdr, ogm_packet,
				      is_single_hop_neigh,
				      is_from_best_next_hop, अगर_incoming,
				      अगर_outgoing);

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Forwarding packet: rebroadcast neighbor packet with direct link flag\n");
		जाओ out_neigh;
	पूर्ण

	/* multihop originator */
	अगर (!is_bidirect) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: not received via bidirectional link\n");
		जाओ out_neigh;
	पूर्ण

	अगर (dup_status == BATADV_NEIGH_DUP) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: duplicate packet received\n");
		जाओ out_neigh;
	पूर्ण

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Forwarding packet: rebroadcast originator packet\n");
	batadv_iv_ogm_क्रमward(orig_node, ethhdr, ogm_packet,
			      is_single_hop_neigh, is_from_best_next_hop,
			      अगर_incoming, अगर_outgoing);

out_neigh:
	अगर (orig_neigh_node && !is_single_hop_neigh)
		batadv_orig_node_put(orig_neigh_node);
out:
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);
	अगर (router)
		batadv_neigh_node_put(router);
	अगर (router_router)
		batadv_neigh_node_put(router_router);
	अगर (orig_neigh_router)
		batadv_neigh_node_put(orig_neigh_router);
	अगर (hardअगर_neigh)
		batadv_hardअगर_neigh_put(hardअगर_neigh);

	consume_skb(skb_priv);
पूर्ण

/**
 * batadv_iv_ogm_process_reply() - Check OGM क्रम direct reply and process it
 * @ogm_packet: rebroadcast OGM packet to process
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 * @orig_node: originator which reproadcasted the OGMs
 * @अगर_incoming_seqno: OGM sequence number when rebroadcast was received
 */
अटल व्योम batadv_iv_ogm_process_reply(काष्ठा batadv_ogm_packet *ogm_packet,
					काष्ठा batadv_hard_अगरace *अगर_incoming,
					काष्ठा batadv_orig_node *orig_node,
					u32 अगर_incoming_seqno)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	s32 bit_pos;
	u8 *weight;

	/* neighbor has to indicate direct link and it has to
	 * come via the corresponding पूर्णांकerface
	 */
	अगर (!(ogm_packet->flags & BATADV_सूचीECTLINK))
		वापस;

	अगर (!batadv_compare_eth(अगर_incoming->net_dev->dev_addr,
				ogm_packet->orig))
		वापस;

	orig_अगरinfo = batadv_orig_अगरinfo_get(orig_node, अगर_incoming);
	अगर (!orig_अगरinfo)
		वापस;

	/* save packet seqno क्रम bidirectional check */
	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);
	bit_pos = अगर_incoming_seqno - 2;
	bit_pos -= ntohl(ogm_packet->seqno);
	batadv_set_bit(orig_अगरinfo->bat_iv.bcast_own, bit_pos);
	weight = &orig_अगरinfo->bat_iv.bcast_own_sum;
	*weight = biपंचांगap_weight(orig_अगरinfo->bat_iv.bcast_own,
				BATADV_TQ_LOCAL_WINDOW_SIZE);
	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	batadv_orig_अगरinfo_put(orig_अगरinfo);
पूर्ण

/**
 * batadv_iv_ogm_process() - process an incoming baपंचांगan iv OGM
 * @skb: the skb containing the OGM
 * @ogm_offset: offset to the OGM which should be processed (क्रम aggregates)
 * @अगर_incoming: the पूर्णांकerface where this packet was received
 */
अटल व्योम batadv_iv_ogm_process(स्थिर काष्ठा sk_buff *skb, पूर्णांक ogm_offset,
				  काष्ठा batadv_hard_अगरace *अगर_incoming)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_orig_node *orig_neigh_node, *orig_node;
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_ogm_packet *ogm_packet;
	u32 अगर_incoming_seqno;
	bool has_directlink_flag;
	काष्ठा ethhdr *ethhdr;
	bool is_my_olकरोrig = false;
	bool is_my_addr = false;
	bool is_my_orig = false;

	ogm_packet = (काष्ठा batadv_ogm_packet *)(skb->data + ogm_offset);
	ethhdr = eth_hdr(skb);

	/* Silently drop when the baपंचांगan packet is actually not a
	 * correct packet.
	 *
	 * This might happen अगर a packet is padded (e.g. Ethernet has a
	 * minimum frame length of 64 byte) and the aggregation पूर्णांकerprets
	 * it as an additional length.
	 *
	 * TODO: A more sane solution would be to have a bit in the
	 * batadv_ogm_packet to detect whether the packet is the last
	 * packet in an aggregation.  Here we expect that the padding
	 * is always zero (or not 0x01)
	 */
	अगर (ogm_packet->packet_type != BATADV_IV_OGM)
		वापस;

	/* could be changed by schedule_own_packet() */
	अगर_incoming_seqno = atomic_पढ़ो(&अगर_incoming->bat_iv.ogm_seqno);

	अगर (ogm_packet->flags & BATADV_सूचीECTLINK)
		has_directlink_flag = true;
	अन्यथा
		has_directlink_flag = false;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Received BATMAN packet via NB: %pM, IF: %s [%pM] (from OG: %pM, via prev OG: %pM, seqno %u, tq %d, TTL %d, V %d, IDF %d)\n",
		   ethhdr->h_source, अगर_incoming->net_dev->name,
		   अगर_incoming->net_dev->dev_addr, ogm_packet->orig,
		   ogm_packet->prev_sender, ntohl(ogm_packet->seqno),
		   ogm_packet->tq, ogm_packet->ttl,
		   ogm_packet->version, has_directlink_flag);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
			जारी;

		अगर (hard_अगरace->soft_अगरace != अगर_incoming->soft_अगरace)
			जारी;

		अगर (batadv_compare_eth(ethhdr->h_source,
				       hard_अगरace->net_dev->dev_addr))
			is_my_addr = true;

		अगर (batadv_compare_eth(ogm_packet->orig,
				       hard_अगरace->net_dev->dev_addr))
			is_my_orig = true;

		अगर (batadv_compare_eth(ogm_packet->prev_sender,
				       hard_अगरace->net_dev->dev_addr))
			is_my_olकरोrig = true;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (is_my_addr) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: received my own broadcast (sender: %pM)\n",
			   ethhdr->h_source);
		वापस;
	पूर्ण

	अगर (is_my_orig) अणु
		orig_neigh_node = batadv_iv_ogm_orig_get(bat_priv,
							 ethhdr->h_source);
		अगर (!orig_neigh_node)
			वापस;

		batadv_iv_ogm_process_reply(ogm_packet, अगर_incoming,
					    orig_neigh_node, अगर_incoming_seqno);

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: originator packet from myself (via neighbor)\n");
		batadv_orig_node_put(orig_neigh_node);
		वापस;
	पूर्ण

	अगर (is_my_olकरोrig) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: ignoring all rebroadcast echos (sender: %pM)\n",
			   ethhdr->h_source);
		वापस;
	पूर्ण

	अगर (ogm_packet->flags & BATADV_NOT_BEST_NEXT_HOP) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: ignoring all packets not forwarded from the best next hop (sender: %pM)\n",
			   ethhdr->h_source);
		वापस;
	पूर्ण

	orig_node = batadv_iv_ogm_orig_get(bat_priv, ogm_packet->orig);
	अगर (!orig_node)
		वापस;

	batadv_iv_ogm_process_per_outअगर(skb, ogm_offset, orig_node,
					अगर_incoming, BATADV_IF_DEFAULT);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
			जारी;

		अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
			जारी;

		अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
			जारी;

		batadv_iv_ogm_process_per_outअगर(skb, ogm_offset, orig_node,
						अगर_incoming, hard_अगरace);

		batadv_hardअगर_put(hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();

	batadv_orig_node_put(orig_node);
पूर्ण

अटल व्योम batadv_iv_send_outstanding_bat_ogm_packet(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_क्रमw_packet *क्रमw_packet;
	काष्ठा batadv_priv *bat_priv;
	bool dropped = false;

	delayed_work = to_delayed_work(work);
	क्रमw_packet = container_of(delayed_work, काष्ठा batadv_क्रमw_packet,
				   delayed_work);
	bat_priv = netdev_priv(क्रमw_packet->अगर_incoming->soft_अगरace);

	अगर (atomic_पढ़ो(&bat_priv->mesh_state) == BATADV_MESH_DEACTIVATING) अणु
		dropped = true;
		जाओ out;
	पूर्ण

	batadv_iv_ogm_emit(क्रमw_packet);

	/* we have to have at least one packet in the queue to determine the
	 * queues wake up समय unless we are shutting करोwn.
	 *
	 * only re-schedule अगर this is the "original" copy, e.g. the OGM of the
	 * primary पूर्णांकerface should only be rescheduled once per period, but
	 * this function will be called क्रम the क्रमw_packet instances of the
	 * other secondary पूर्णांकerfaces as well.
	 */
	अगर (क्रमw_packet->own &&
	    क्रमw_packet->अगर_incoming == क्रमw_packet->अगर_outgoing)
		batadv_iv_ogm_schedule(क्रमw_packet->अगर_incoming);

out:
	/* करो we get something क्रम मुक्त()? */
	अगर (batadv_क्रमw_packet_steal(क्रमw_packet,
				     &bat_priv->क्रमw_bat_list_lock))
		batadv_क्रमw_packet_मुक्त(क्रमw_packet, dropped);
पूर्ण

अटल पूर्णांक batadv_iv_ogm_receive(काष्ठा sk_buff *skb,
				 काष्ठा batadv_hard_अगरace *अगर_incoming)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_ogm_packet *ogm_packet;
	u8 *packet_pos;
	पूर्णांक ogm_offset;
	bool res;
	पूर्णांक ret = NET_RX_DROP;

	res = batadv_check_management_packet(skb, अगर_incoming, BATADV_OGM_HLEN);
	अगर (!res)
		जाओ मुक्त_skb;

	/* did we receive a B.A.T.M.A.N. IV OGM packet on an पूर्णांकerface
	 * that करोes not have B.A.T.M.A.N. IV enabled ?
	 */
	अगर (bat_priv->algo_ops->अगरace.enable != batadv_iv_ogm_अगरace_enable)
		जाओ मुक्त_skb;

	batadv_inc_counter(bat_priv, BATADV_CNT_MGMT_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_MGMT_RX_BYTES,
			   skb->len + ETH_HLEN);

	ogm_offset = 0;
	ogm_packet = (काष्ठा batadv_ogm_packet *)skb->data;

	/* unpack the aggregated packets and process them one by one */
	जबतक (batadv_iv_ogm_aggr_packet(ogm_offset, skb_headlen(skb),
					 ogm_packet)) अणु
		batadv_iv_ogm_process(skb, ogm_offset, अगर_incoming);

		ogm_offset += BATADV_OGM_HLEN;
		ogm_offset += ntohs(ogm_packet->tvlv_len);

		packet_pos = skb->data + ogm_offset;
		ogm_packet = (काष्ठा batadv_ogm_packet *)packet_pos;
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
 * batadv_iv_ogm_neigh_get_tq_avg() - Get the TQ average क्रम a neighbour on a
 *  given outgoing पूर्णांकerface.
 * @neigh_node: Neighbour of पूर्णांकerest
 * @अगर_outgoing: Outgoing पूर्णांकerface of पूर्णांकerest
 * @tq_avg: Poपूर्णांकer of where to store the TQ average
 *
 * Return: False अगर no average TQ available, otherwise true.
 */
अटल bool
batadv_iv_ogm_neigh_get_tq_avg(काष्ठा batadv_neigh_node *neigh_node,
			       काष्ठा batadv_hard_अगरace *अगर_outgoing,
			       u8 *tq_avg)
अणु
	काष्ठा batadv_neigh_अगरinfo *n_अगरinfo;

	n_अगरinfo = batadv_neigh_अगरinfo_get(neigh_node, अगर_outgoing);
	अगर (!n_अगरinfo)
		वापस false;

	*tq_avg = n_अगरinfo->bat_iv.tq_avg;
	batadv_neigh_अगरinfo_put(n_अगरinfo);

	वापस true;
पूर्ण

/**
 * batadv_iv_ogm_orig_dump_subentry() - Dump an originator subentry पूर्णांकo a
 *  message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 * @orig_node: Originator to dump
 * @neigh_node: Single hops neighbour
 * @best: Is the best originator
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_iv_ogm_orig_dump_subentry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
				 काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_hard_अगरace *अगर_outgoing,
				 काष्ठा batadv_orig_node *orig_node,
				 काष्ठा batadv_neigh_node *neigh_node,
				 bool best)
अणु
	व्योम *hdr;
	u8 tq_avg;
	अचिन्हित पूर्णांक last_seen_msecs;

	last_seen_msecs = jअगरfies_to_msecs(jअगरfies - orig_node->last_seen);

	अगर (!batadv_iv_ogm_neigh_get_tq_avg(neigh_node, अगर_outgoing, &tq_avg))
		वापस 0;

	अगर (अगर_outgoing != BATADV_IF_DEFAULT &&
	    अगर_outgoing != neigh_node->अगर_incoming)
		वापस 0;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family,
			  NLM_F_MULTI, BATADV_CMD_GET_ORIGINATORS);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    orig_node->orig) ||
	    nla_put(msg, BATADV_ATTR_NEIGH_ADDRESS, ETH_ALEN,
		    neigh_node->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			neigh_node->अगर_incoming->net_dev->अगरindex) ||
	    nla_put_u8(msg, BATADV_ATTR_TQ, tq_avg) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS,
			last_seen_msecs))
		जाओ nla_put_failure;

	अगर (best && nla_put_flag(msg, BATADV_ATTR_FLAG_BEST))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_iv_ogm_orig_dump_entry() - Dump an originator entry पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 * @orig_node: Originator to dump
 * @sub_s: Number of sub entries to skip
 *
 * This function assumes the caller holds rcu_पढ़ो_lock().
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_iv_ogm_orig_dump_entry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			      काष्ठा batadv_priv *bat_priv,
			      काष्ठा batadv_hard_अगरace *अगर_outgoing,
			      काष्ठा batadv_orig_node *orig_node, पूर्णांक *sub_s)
अणु
	काष्ठा batadv_neigh_node *neigh_node_best;
	काष्ठा batadv_neigh_node *neigh_node;
	पूर्णांक sub = 0;
	bool best;
	u8 tq_avg_best;

	neigh_node_best = batadv_orig_router_get(orig_node, अगर_outgoing);
	अगर (!neigh_node_best)
		जाओ out;

	अगर (!batadv_iv_ogm_neigh_get_tq_avg(neigh_node_best, अगर_outgoing,
					    &tq_avg_best))
		जाओ out;

	अगर (tq_avg_best == 0)
		जाओ out;

	hlist_क्रम_each_entry_rcu(neigh_node, &orig_node->neigh_list, list) अणु
		अगर (sub++ < *sub_s)
			जारी;

		best = (neigh_node == neigh_node_best);

		अगर (batadv_iv_ogm_orig_dump_subentry(msg, portid, seq,
						     bat_priv, अगर_outgoing,
						     orig_node, neigh_node,
						     best)) अणु
			batadv_neigh_node_put(neigh_node_best);

			*sub_s = sub - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

 out:
	अगर (neigh_node_best)
		batadv_neigh_node_put(neigh_node_best);

	*sub_s = 0;
	वापस 0;
पूर्ण

/**
 * batadv_iv_ogm_orig_dump_bucket() - Dump an originator bucket पूर्णांकo a
 *  message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 * @head: Bucket to be dumped
 * @idx_s: Number of entries to be skipped
 * @sub: Number of sub entries to be skipped
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_iv_ogm_orig_dump_bucket(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			       काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_hard_अगरace *अगर_outgoing,
			       काष्ठा hlist_head *head, पूर्णांक *idx_s, पूर्णांक *sub)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक idx = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node, head, hash_entry) अणु
		अगर (idx++ < *idx_s)
			जारी;

		अगर (batadv_iv_ogm_orig_dump_entry(msg, portid, seq, bat_priv,
						  अगर_outgoing, orig_node,
						  sub)) अणु
			rcu_पढ़ो_unlock();
			*idx_s = idx - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	*idx_s = 0;
	*sub = 0;
	वापस 0;
पूर्ण

/**
 * batadv_iv_ogm_orig_dump() - Dump the originators पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 */
अटल व्योम
batadv_iv_ogm_orig_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
			काष्ठा batadv_priv *bat_priv,
			काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_head *head;
	पूर्णांक bucket = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक sub = cb->args[2];
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;

	जबतक (bucket < hash->size) अणु
		head = &hash->table[bucket];

		अगर (batadv_iv_ogm_orig_dump_bucket(msg, portid,
						   cb->nlh->nlmsg_seq,
						   bat_priv, अगर_outgoing, head,
						   &idx, &sub))
			अवरोध;

		bucket++;
	पूर्ण

	cb->args[0] = bucket;
	cb->args[1] = idx;
	cb->args[2] = sub;
पूर्ण

/**
 * batadv_iv_ogm_neigh_dअगरf() - calculate tq dअगरference of two neighbors
 * @neigh1: the first neighbor object of the comparison
 * @अगर_outgoing1: outgoing पूर्णांकerface क्रम the first neighbor
 * @neigh2: the second neighbor object of the comparison
 * @अगर_outgoing2: outgoing पूर्णांकerface क्रम the second neighbor
 * @dअगरf: poपूर्णांकer to पूर्णांकeger receiving the calculated dअगरference
 *
 * The content of *@dअगरf is only valid when this function वापसs true.
 * It is less, equal to or greater than 0 अगर the metric via neigh1 is lower,
 * the same as or higher than the metric via neigh2
 *
 * Return: true when the dअगरference could be calculated, false otherwise
 */
अटल bool batadv_iv_ogm_neigh_dअगरf(काष्ठा batadv_neigh_node *neigh1,
				     काष्ठा batadv_hard_अगरace *अगर_outgoing1,
				     काष्ठा batadv_neigh_node *neigh2,
				     काष्ठा batadv_hard_अगरace *अगर_outgoing2,
				     पूर्णांक *dअगरf)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh1_अगरinfo, *neigh2_अगरinfo;
	u8 tq1, tq2;
	bool ret = true;

	neigh1_अगरinfo = batadv_neigh_अगरinfo_get(neigh1, अगर_outgoing1);
	neigh2_अगरinfo = batadv_neigh_अगरinfo_get(neigh2, अगर_outgoing2);

	अगर (!neigh1_अगरinfo || !neigh2_अगरinfo) अणु
		ret = false;
		जाओ out;
	पूर्ण

	tq1 = neigh1_अगरinfo->bat_iv.tq_avg;
	tq2 = neigh2_अगरinfo->bat_iv.tq_avg;
	*dअगरf = (पूर्णांक)tq1 - (पूर्णांक)tq2;

out:
	अगर (neigh1_अगरinfo)
		batadv_neigh_अगरinfo_put(neigh1_अगरinfo);
	अगर (neigh2_अगरinfo)
		batadv_neigh_अगरinfo_put(neigh2_अगरinfo);

	वापस ret;
पूर्ण

/**
 * batadv_iv_ogm_neigh_dump_neigh() - Dump a neighbour पूर्णांकo a netlink message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @hardअगर_neigh: Neighbour to be dumped
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_iv_ogm_neigh_dump_neigh(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			       काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh)
अणु
	व्योम *hdr;
	अचिन्हित पूर्णांक last_seen_msecs;

	last_seen_msecs = jअगरfies_to_msecs(jअगरfies - hardअगर_neigh->last_seen);

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family,
			  NLM_F_MULTI, BATADV_CMD_GET_NEIGHBORS);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put(msg, BATADV_ATTR_NEIGH_ADDRESS, ETH_ALEN,
		    hardअगर_neigh->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			hardअगर_neigh->अगर_incoming->net_dev->अगरindex) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS,
			last_seen_msecs))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_iv_ogm_neigh_dump_hardअगर() - Dump the neighbours of a hard पूर्णांकerface
 *  पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hard_अगरace: Hard पूर्णांकerface to dump the neighbours क्रम
 * @idx_s: Number of entries to skip
 *
 * This function assumes the caller holds rcu_पढ़ो_lock().
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_iv_ogm_neigh_dump_hardअगर(काष्ठा sk_buff *msg, u32 portid, u32 seq,
				काष्ठा batadv_priv *bat_priv,
				काष्ठा batadv_hard_अगरace *hard_अगरace,
				पूर्णांक *idx_s)
अणु
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;
	पूर्णांक idx = 0;

	hlist_क्रम_each_entry_rcu(hardअगर_neigh,
				 &hard_अगरace->neigh_list, list) अणु
		अगर (idx++ < *idx_s)
			जारी;

		अगर (batadv_iv_ogm_neigh_dump_neigh(msg, portid, seq,
						   hardअगर_neigh)) अणु
			*idx_s = idx - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	*idx_s = 0;
	वापस 0;
पूर्ण

/**
 * batadv_iv_ogm_neigh_dump() - Dump the neighbours पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @single_hardअगर: Limit dump to this hard पूर्णांकerface
 */
अटल व्योम
batadv_iv_ogm_neigh_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
			 काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_hard_अगरace *single_hardअगर)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	पूर्णांक i_hardअगर = 0;
	पूर्णांक i_hardअगर_s = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;

	rcu_पढ़ो_lock();
	अगर (single_hardअगर) अणु
		अगर (i_hardअगर_s == 0) अणु
			अगर (batadv_iv_ogm_neigh_dump_hardअगर(msg, portid,
							    cb->nlh->nlmsg_seq,
							    bat_priv,
							    single_hardअगर,
							    &idx) == 0)
				i_hardअगर++;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list,
					list) अणु
			अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
				जारी;

			अगर (i_hardअगर++ < i_hardअगर_s)
				जारी;

			अगर (batadv_iv_ogm_neigh_dump_hardअगर(msg, portid,
							    cb->nlh->nlmsg_seq,
							    bat_priv,
							    hard_अगरace, &idx)) अणु
				i_hardअगर--;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	cb->args[0] = i_hardअगर;
	cb->args[1] = idx;
पूर्ण

/**
 * batadv_iv_ogm_neigh_cmp() - compare the metrics of two neighbors
 * @neigh1: the first neighbor object of the comparison
 * @अगर_outgoing1: outgoing पूर्णांकerface क्रम the first neighbor
 * @neigh2: the second neighbor object of the comparison
 * @अगर_outgoing2: outgoing पूर्णांकerface क्रम the second neighbor
 *
 * Return: a value less, equal to or greater than 0 अगर the metric via neigh1 is
 * lower, the same as or higher than the metric via neigh2
 */
अटल पूर्णांक batadv_iv_ogm_neigh_cmp(काष्ठा batadv_neigh_node *neigh1,
				   काष्ठा batadv_hard_अगरace *अगर_outgoing1,
				   काष्ठा batadv_neigh_node *neigh2,
				   काष्ठा batadv_hard_अगरace *अगर_outgoing2)
अणु
	bool ret;
	पूर्णांक dअगरf;

	ret = batadv_iv_ogm_neigh_dअगरf(neigh1, अगर_outgoing1, neigh2,
				       अगर_outgoing2, &dअगरf);
	अगर (!ret)
		वापस 0;

	वापस dअगरf;
पूर्ण

/**
 * batadv_iv_ogm_neigh_is_sob() - check अगर neigh1 is similarly good or better
 *  than neigh2 from the metric prospective
 * @neigh1: the first neighbor object of the comparison
 * @अगर_outgoing1: outgoing पूर्णांकerface क्रम the first neighbor
 * @neigh2: the second neighbor object of the comparison
 * @अगर_outgoing2: outgoing पूर्णांकerface क्रम the second neighbor
 *
 * Return: true अगर the metric via neigh1 is equally good or better than
 * the metric via neigh2, false otherwise.
 */
अटल bool
batadv_iv_ogm_neigh_is_sob(काष्ठा batadv_neigh_node *neigh1,
			   काष्ठा batadv_hard_अगरace *अगर_outgoing1,
			   काष्ठा batadv_neigh_node *neigh2,
			   काष्ठा batadv_hard_अगरace *अगर_outgoing2)
अणु
	bool ret;
	पूर्णांक dअगरf;

	ret = batadv_iv_ogm_neigh_dअगरf(neigh1, अगर_outgoing1, neigh2,
				       अगर_outgoing2, &dअगरf);
	अगर (!ret)
		वापस false;

	ret = dअगरf > -BATADV_TQ_SIMILARITY_THRESHOLD;
	वापस ret;
पूर्ण

अटल व्योम batadv_iv_अगरace_enabled(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	/* begin scheduling originator messages on that पूर्णांकerface */
	batadv_iv_ogm_schedule(hard_अगरace);
पूर्ण

/**
 * batadv_iv_init_sel_class() - initialize GW selection class
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_iv_init_sel_class(काष्ठा batadv_priv *bat_priv)
अणु
	/* set शेष TQ dअगरference threshold to 20 */
	atomic_set(&bat_priv->gw.sel_class, 20);
पूर्ण

अटल काष्ठा batadv_gw_node *
batadv_iv_gw_get_best_gw_node(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_neigh_node *router;
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo;
	काष्ठा batadv_gw_node *gw_node, *curr_gw = शून्य;
	u64 max_gw_factor = 0;
	u64 पंचांगp_gw_factor = 0;
	u8 max_tq = 0;
	u8 tq_avg;
	काष्ठा batadv_orig_node *orig_node;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(gw_node, &bat_priv->gw.gateway_list, list) अणु
		orig_node = gw_node->orig_node;
		router = batadv_orig_router_get(orig_node, BATADV_IF_DEFAULT);
		अगर (!router)
			जारी;

		router_अगरinfo = batadv_neigh_अगरinfo_get(router,
							BATADV_IF_DEFAULT);
		अगर (!router_अगरinfo)
			जाओ next;

		अगर (!kref_get_unless_zero(&gw_node->refcount))
			जाओ next;

		tq_avg = router_अगरinfo->bat_iv.tq_avg;

		चयन (atomic_पढ़ो(&bat_priv->gw.sel_class)) अणु
		हाल 1: /* fast connection */
			पंचांगp_gw_factor = tq_avg * tq_avg;
			पंचांगp_gw_factor *= gw_node->bandwidth_करोwn;
			पंचांगp_gw_factor *= 100 * 100;
			पंचांगp_gw_factor >>= 18;

			अगर (पंचांगp_gw_factor > max_gw_factor ||
			    (पंचांगp_gw_factor == max_gw_factor &&
			     tq_avg > max_tq)) अणु
				अगर (curr_gw)
					batadv_gw_node_put(curr_gw);
				curr_gw = gw_node;
				kref_get(&curr_gw->refcount);
			पूर्ण
			अवरोध;

		शेष: /* 2:  stable connection (use best statistic)
			  * 3:  fast-चयन (use best statistic but change as
			  *     soon as a better gateway appears)
			  * XX: late-चयन (use best statistic but change as
			  *     soon as a better gateway appears which has
			  *     $routing_class more tq poपूर्णांकs)
			  */
			अगर (tq_avg > max_tq) अणु
				अगर (curr_gw)
					batadv_gw_node_put(curr_gw);
				curr_gw = gw_node;
				kref_get(&curr_gw->refcount);
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (tq_avg > max_tq)
			max_tq = tq_avg;

		अगर (पंचांगp_gw_factor > max_gw_factor)
			max_gw_factor = पंचांगp_gw_factor;

		batadv_gw_node_put(gw_node);

next:
		batadv_neigh_node_put(router);
		अगर (router_अगरinfo)
			batadv_neigh_अगरinfo_put(router_अगरinfo);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस curr_gw;
पूर्ण

अटल bool batadv_iv_gw_is_eligible(काष्ठा batadv_priv *bat_priv,
				     काष्ठा batadv_orig_node *curr_gw_orig,
				     काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_neigh_अगरinfo *router_orig_अगरinfo = शून्य;
	काष्ठा batadv_neigh_अगरinfo *router_gw_अगरinfo = शून्य;
	काष्ठा batadv_neigh_node *router_gw = शून्य;
	काष्ठा batadv_neigh_node *router_orig = शून्य;
	u8 gw_tq_avg, orig_tq_avg;
	bool ret = false;

	/* dynamic re-election is perक्रमmed only on fast or late चयन */
	अगर (atomic_पढ़ो(&bat_priv->gw.sel_class) <= 2)
		वापस false;

	router_gw = batadv_orig_router_get(curr_gw_orig, BATADV_IF_DEFAULT);
	अगर (!router_gw) अणु
		ret = true;
		जाओ out;
	पूर्ण

	router_gw_अगरinfo = batadv_neigh_अगरinfo_get(router_gw,
						   BATADV_IF_DEFAULT);
	अगर (!router_gw_अगरinfo) अणु
		ret = true;
		जाओ out;
	पूर्ण

	router_orig = batadv_orig_router_get(orig_node, BATADV_IF_DEFAULT);
	अगर (!router_orig)
		जाओ out;

	router_orig_अगरinfo = batadv_neigh_अगरinfo_get(router_orig,
						     BATADV_IF_DEFAULT);
	अगर (!router_orig_अगरinfo)
		जाओ out;

	gw_tq_avg = router_gw_अगरinfo->bat_iv.tq_avg;
	orig_tq_avg = router_orig_अगरinfo->bat_iv.tq_avg;

	/* the TQ value has to be better */
	अगर (orig_tq_avg < gw_tq_avg)
		जाओ out;

	/* अगर the routing class is greater than 3 the value tells us how much
	 * greater the TQ value of the new gateway must be
	 */
	अगर ((atomic_पढ़ो(&bat_priv->gw.sel_class) > 3) &&
	    (orig_tq_avg - gw_tq_avg < atomic_पढ़ो(&bat_priv->gw.sel_class)))
		जाओ out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Restarting gateway selection: better gateway found (tq curr: %i, tq new: %i)\n",
		   gw_tq_avg, orig_tq_avg);

	ret = true;
out:
	अगर (router_gw_अगरinfo)
		batadv_neigh_अगरinfo_put(router_gw_अगरinfo);
	अगर (router_orig_अगरinfo)
		batadv_neigh_अगरinfo_put(router_orig_अगरinfo);
	अगर (router_gw)
		batadv_neigh_node_put(router_gw);
	अगर (router_orig)
		batadv_neigh_node_put(router_orig);

	वापस ret;
पूर्ण

/**
 * batadv_iv_gw_dump_entry() - Dump a gateway पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @gw_node: Gateway to be dumped
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक batadv_iv_gw_dump_entry(काष्ठा sk_buff *msg, u32 portid,
				   काष्ठा netlink_callback *cb,
				   काष्ठा batadv_priv *bat_priv,
				   काष्ठा batadv_gw_node *gw_node)
अणु
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य;
	काष्ठा batadv_neigh_node *router;
	काष्ठा batadv_gw_node *curr_gw = शून्य;
	पूर्णांक ret = 0;
	व्योम *hdr;

	router = batadv_orig_router_get(gw_node->orig_node, BATADV_IF_DEFAULT);
	अगर (!router)
		जाओ out;

	router_अगरinfo = batadv_neigh_अगरinfo_get(router, BATADV_IF_DEFAULT);
	अगर (!router_अगरinfo)
		जाओ out;

	curr_gw = batadv_gw_get_selected_gw_node(bat_priv);

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_GATEWAYS);
	अगर (!hdr) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	genl_dump_check_consistent(cb, hdr);

	ret = -EMSGSIZE;

	अगर (curr_gw == gw_node)
		अगर (nla_put_flag(msg, BATADV_ATTR_FLAG_BEST)) अणु
			genlmsg_cancel(msg, hdr);
			जाओ out;
		पूर्ण

	अगर (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    gw_node->orig_node->orig) ||
	    nla_put_u8(msg, BATADV_ATTR_TQ, router_अगरinfo->bat_iv.tq_avg) ||
	    nla_put(msg, BATADV_ATTR_ROUTER, ETH_ALEN,
		    router->addr) ||
	    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
			   router->अगर_incoming->net_dev->name) ||
	    nla_put_u32(msg, BATADV_ATTR_BANDWIDTH_DOWN,
			gw_node->bandwidth_करोwn) ||
	    nla_put_u32(msg, BATADV_ATTR_BANDWIDTH_UP,
			gw_node->bandwidth_up)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	genlmsg_end(msg, hdr);
	ret = 0;

out:
	अगर (curr_gw)
		batadv_gw_node_put(curr_gw);
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);
	अगर (router)
		batadv_neigh_node_put(router);
	वापस ret;
पूर्ण

/**
 * batadv_iv_gw_dump() - Dump gateways पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_iv_gw_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
			      काष्ठा batadv_priv *bat_priv)
अणु
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	काष्ठा batadv_gw_node *gw_node;
	पूर्णांक idx_skip = cb->args[0];
	पूर्णांक idx = 0;

	spin_lock_bh(&bat_priv->gw.list_lock);
	cb->seq = bat_priv->gw.generation << 1 | 1;

	hlist_क्रम_each_entry(gw_node, &bat_priv->gw.gateway_list, list) अणु
		अगर (idx++ < idx_skip)
			जारी;

		अगर (batadv_iv_gw_dump_entry(msg, portid, cb, bat_priv,
					    gw_node)) अणु
			idx_skip = idx - 1;
			जाओ unlock;
		पूर्ण
	पूर्ण

	idx_skip = idx;
unlock:
	spin_unlock_bh(&bat_priv->gw.list_lock);

	cb->args[0] = idx_skip;
पूर्ण

अटल काष्ठा batadv_algo_ops batadv_baपंचांगan_iv __पढ़ो_mostly = अणु
	.name = "BATMAN_IV",
	.अगरace = अणु
		.enable = batadv_iv_ogm_अगरace_enable,
		.enabled = batadv_iv_अगरace_enabled,
		.disable = batadv_iv_ogm_अगरace_disable,
		.update_mac = batadv_iv_ogm_अगरace_update_mac,
		.primary_set = batadv_iv_ogm_primary_अगरace_set,
	पूर्ण,
	.neigh = अणु
		.cmp = batadv_iv_ogm_neigh_cmp,
		.is_similar_or_better = batadv_iv_ogm_neigh_is_sob,
		.dump = batadv_iv_ogm_neigh_dump,
	पूर्ण,
	.orig = अणु
		.dump = batadv_iv_ogm_orig_dump,
	पूर्ण,
	.gw = अणु
		.init_sel_class = batadv_iv_init_sel_class,
		.get_best_gw_node = batadv_iv_gw_get_best_gw_node,
		.is_eligible = batadv_iv_gw_is_eligible,
		.dump = batadv_iv_gw_dump,
	पूर्ण,
पूर्ण;

/**
 * batadv_iv_init() - B.A.T.M.A.N. IV initialization function
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक __init batadv_iv_init(व्योम)
अणु
	पूर्णांक ret;

	/* baपंचांगan originator packet */
	ret = batadv_recv_handler_रेजिस्टर(BATADV_IV_OGM,
					   batadv_iv_ogm_receive);
	अगर (ret < 0)
		जाओ out;

	ret = batadv_algo_रेजिस्टर(&batadv_baपंचांगan_iv);
	अगर (ret < 0)
		जाओ handler_unरेजिस्टर;

	जाओ out;

handler_unरेजिस्टर:
	batadv_recv_handler_unरेजिस्टर(BATADV_IV_OGM);
out:
	वापस ret;
पूर्ण
