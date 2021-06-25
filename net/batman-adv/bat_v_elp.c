<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Linus Lथञssing, Marek Lindner
 */

#समावेश "bat_v_elp.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/minmax.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/pअक्रमom.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <net/cfg80211.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "bat_algo.h"
#समावेश "bat_v_ogm.h"
#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "send.h"

/**
 * batadv_v_elp_start_समयr() - restart समयr क्रम ELP periodic work
 * @hard_अगरace: the पूर्णांकerface क्रम which the समयr has to be reset
 */
अटल व्योम batadv_v_elp_start_समयr(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अचिन्हित पूर्णांक msecs;

	msecs = atomic_पढ़ो(&hard_अगरace->bat_v.elp_पूर्णांकerval) - BATADV_JITTER;
	msecs += pअक्रमom_u32_max(2 * BATADV_JITTER);

	queue_delayed_work(batadv_event_workqueue, &hard_अगरace->bat_v.elp_wq,
			   msecs_to_jअगरfies(msecs));
पूर्ण

/**
 * batadv_v_elp_get_throughput() - get the throughput towards a neighbour
 * @neigh: the neighbour क्रम which the throughput has to be obtained
 *
 * Return: The throughput towards the given neighbour in multiples of 100kpbs
 *         (a value of '1' equals 0.1Mbps, '10' equals 1Mbps, etc).
 */
अटल u32 batadv_v_elp_get_throughput(काष्ठा batadv_hardअगर_neigh_node *neigh)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace = neigh->अगर_incoming;
	काष्ठा ethtool_link_ksettings link_settings;
	काष्ठा net_device *real_netdev;
	काष्ठा station_info sinfo;
	u32 throughput;
	पूर्णांक ret;

	/* अगर the user specअगरied a customised value क्रम this पूर्णांकerface, then
	 * वापस it directly
	 */
	throughput =  atomic_पढ़ो(&hard_अगरace->bat_v.throughput_override);
	अगर (throughput != 0)
		वापस throughput;

	/* अगर this is a wireless device, then ask its throughput through
	 * cfg80211 API
	 */
	अगर (batadv_is_wअगरi_hardअगर(hard_अगरace)) अणु
		अगर (!batadv_is_cfg80211_hardअगर(hard_अगरace))
			/* unsupported WiFi driver version */
			जाओ शेष_throughput;

		real_netdev = batadv_get_real_netdev(hard_अगरace->net_dev);
		अगर (!real_netdev)
			जाओ शेष_throughput;

		ret = cfg80211_get_station(real_netdev, neigh->addr, &sinfo);

		अगर (!ret) अणु
			/* मुक्त the TID stats immediately */
			cfg80211_sinfo_release_content(&sinfo);
		पूर्ण

		dev_put(real_netdev);
		अगर (ret == -ENOENT) अणु
			/* Node is not associated anymore! It would be
			 * possible to delete this neighbor. For now set
			 * the throughput metric to 0.
			 */
			वापस 0;
		पूर्ण
		अगर (ret)
			जाओ शेष_throughput;

		अगर (sinfo.filled & BIT(NL80211_STA_INFO_EXPECTED_THROUGHPUT))
			वापस sinfo.expected_throughput / 100;

		/* try to estimate the expected throughput based on reported tx
		 * rates
		 */
		अगर (sinfo.filled & BIT(NL80211_STA_INFO_TX_BITRATE))
			वापस cfg80211_calculate_bitrate(&sinfo.txrate) / 3;

		जाओ शेष_throughput;
	पूर्ण

	/* अगर not a wअगरi पूर्णांकerface, check अगर this device provides data via
	 * ethtool (e.g. an Ethernet adapter)
	 */
	स_रखो(&link_settings, 0, माप(link_settings));
	rtnl_lock();
	ret = __ethtool_get_link_ksettings(hard_अगरace->net_dev, &link_settings);
	rtnl_unlock();
	अगर (ret == 0) अणु
		/* link अक्षरacteristics might change over समय */
		अगर (link_settings.base.duplex == DUPLEX_FULL)
			hard_अगरace->bat_v.flags |= BATADV_FULL_DUPLEX;
		अन्यथा
			hard_अगरace->bat_v.flags &= ~BATADV_FULL_DUPLEX;

		throughput = link_settings.base.speed;
		अगर (throughput && throughput != SPEED_UNKNOWN)
			वापस throughput * 10;
	पूर्ण

शेष_throughput:
	अगर (!(hard_अगरace->bat_v.flags & BATADV_WARNING_DEFAULT)) अणु
		batadv_info(hard_अगरace->soft_अगरace,
			    "WiFi driver or ethtool info does not provide information about link speeds on interface %s, therefore defaulting to hardcoded throughput values of %u.%1u Mbps. Consider overriding the throughput manually or checking your driver.\n",
			    hard_अगरace->net_dev->name,
			    BATADV_THROUGHPUT_DEFAULT_VALUE / 10,
			    BATADV_THROUGHPUT_DEFAULT_VALUE % 10);
		hard_अगरace->bat_v.flags |= BATADV_WARNING_DEFAULT;
	पूर्ण

	/* अगर none of the above हालs apply, वापस the base_throughput */
	वापस BATADV_THROUGHPUT_DEFAULT_VALUE;
पूर्ण

/**
 * batadv_v_elp_throughput_metric_update() - worker updating the throughput
 *  metric of a single hop neighbour
 * @work: the work queue item
 */
व्योम batadv_v_elp_throughput_metric_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा batadv_hardअगर_neigh_node_bat_v *neigh_bat_v;
	काष्ठा batadv_hardअगर_neigh_node *neigh;

	neigh_bat_v = container_of(work, काष्ठा batadv_hardअगर_neigh_node_bat_v,
				   metric_work);
	neigh = container_of(neigh_bat_v, काष्ठा batadv_hardअगर_neigh_node,
			     bat_v);

	ewma_throughput_add(&neigh->bat_v.throughput,
			    batadv_v_elp_get_throughput(neigh));

	/* decrement refcounter to balance increment perक्रमmed beक्रमe scheduling
	 * this task
	 */
	batadv_hardअगर_neigh_put(neigh);
पूर्ण

/**
 * batadv_v_elp_wअगरi_neigh_probe() - send link probing packets to a neighbour
 * @neigh: the neighbour to probe
 *
 * Sends a predefined number of unicast wअगरi packets to a given neighbour in
 * order to trigger the throughput estimation on this link by the RC algorithm.
 * Packets are sent only अगर there is not enough payload unicast traffic towards
 * this neighbour..
 *
 * Return: True on success and false in हाल of error during skb preparation.
 */
अटल bool
batadv_v_elp_wअगरi_neigh_probe(काष्ठा batadv_hardअगर_neigh_node *neigh)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace = neigh->अगर_incoming;
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	अचिन्हित दीर्घ last_tx_dअगरf;
	काष्ठा sk_buff *skb;
	पूर्णांक probe_len, i;
	पूर्णांक elp_skb_len;

	/* this probing routine is क्रम Wअगरi neighbours only */
	अगर (!batadv_is_wअगरi_hardअगर(hard_अगरace))
		वापस true;

	/* probe the neighbor only अगर no unicast packets have been sent
	 * to it in the last 100 milliseconds: this is the rate control
	 * algorithm sampling पूर्णांकerval (minstrel). In this way, अगर not
	 * enough traffic has been sent to the neighbor, baपंचांगan-adv can
	 * generate 2 probe packets and push the RC algorithm to perक्रमm
	 * the sampling
	 */
	last_tx_dअगरf = jअगरfies_to_msecs(jअगरfies - neigh->bat_v.last_unicast_tx);
	अगर (last_tx_dअगरf <= BATADV_ELP_PROBE_MAX_TX_DIFF)
		वापस true;

	probe_len = max_t(पूर्णांक, माप(काष्ठा batadv_elp_packet),
			  BATADV_ELP_MIN_PROBE_SIZE);

	क्रम (i = 0; i < BATADV_ELP_PROBES_PER_NODE; i++) अणु
		elp_skb_len = hard_अगरace->bat_v.elp_skb->len;
		skb = skb_copy_expand(hard_अगरace->bat_v.elp_skb, 0,
				      probe_len - elp_skb_len,
				      GFP_ATOMIC);
		अगर (!skb)
			वापस false;

		/* Tell the skb to get as big as the allocated space (we want
		 * the packet to be exactly of that size to make the link
		 * throughput estimation effective.
		 */
		skb_put_zero(skb, probe_len - hard_अगरace->bat_v.elp_skb->len);

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Sending unicast (probe) ELP packet on interface %s to %pM\n",
			   hard_अगरace->net_dev->name, neigh->addr);

		batadv_send_skb_packet(skb, hard_अगरace, neigh->addr);
	पूर्ण

	वापस true;
पूर्ण

/**
 * batadv_v_elp_periodic_work() - ELP periodic task per पूर्णांकerface
 * @work: work queue item
 *
 * Emits broadcast ELP messages in regular पूर्णांकervals.
 */
अटल व्योम batadv_v_elp_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_hard_अगरace_bat_v *bat_v;
	काष्ठा batadv_elp_packet *elp_packet;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा sk_buff *skb;
	u32 elp_पूर्णांकerval;
	bool ret;

	bat_v = container_of(work, काष्ठा batadv_hard_अगरace_bat_v, elp_wq.work);
	hard_अगरace = container_of(bat_v, काष्ठा batadv_hard_अगरace, bat_v);
	bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	अगर (atomic_पढ़ो(&bat_priv->mesh_state) == BATADV_MESH_DEACTIVATING)
		जाओ out;

	/* we are in the process of shutting this पूर्णांकerface करोwn */
	अगर (hard_अगरace->अगर_status == BATADV_IF_NOT_IN_USE ||
	    hard_अगरace->अगर_status == BATADV_IF_TO_BE_REMOVED)
		जाओ out;

	/* the पूर्णांकerface was enabled but may not be पढ़ोy yet */
	अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
		जाओ restart_समयr;

	skb = skb_copy(hard_अगरace->bat_v.elp_skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ restart_समयr;

	elp_packet = (काष्ठा batadv_elp_packet *)skb->data;
	elp_packet->seqno = htonl(atomic_पढ़ो(&hard_अगरace->bat_v.elp_seqno));
	elp_पूर्णांकerval = atomic_पढ़ो(&hard_अगरace->bat_v.elp_पूर्णांकerval);
	elp_packet->elp_पूर्णांकerval = htonl(elp_पूर्णांकerval);

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Sending broadcast ELP packet on interface %s, seqno %u\n",
		   hard_अगरace->net_dev->name,
		   atomic_पढ़ो(&hard_अगरace->bat_v.elp_seqno));

	batadv_send_broadcast_skb(skb, hard_अगरace);

	atomic_inc(&hard_अगरace->bat_v.elp_seqno);

	/* The throughput metric is updated on each sent packet. This way, अगर a
	 * node is dead and no दीर्घer sends packets, baपंचांगan-adv is still able to
	 * react समयly to its death.
	 *
	 * The throughput metric is updated by following these steps:
	 * 1) अगर the hard_अगरace is wअगरi => send a number of unicast ELPs क्रम
	 *    probing/sampling to each neighbor
	 * 2) update the throughput metric value of each neighbor (note that the
	 *    value retrieved in this step might be 100ms old because the
	 *    probing packets at poपूर्णांक 1) could still be in the HW queue)
	 */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(hardअगर_neigh, &hard_अगरace->neigh_list, list) अणु
		अगर (!batadv_v_elp_wअगरi_neigh_probe(hardअगर_neigh))
			/* अगर something goes wrong जबतक probing, better to stop
			 * sending packets immediately and reschedule the task
			 */
			अवरोध;

		अगर (!kref_get_unless_zero(&hardअगर_neigh->refcount))
			जारी;

		/* Reading the estimated throughput from cfg80211 is a task that
		 * may sleep and that is not allowed in an rcu रक्षित
		 * context. Thereक्रमe schedule a task क्रम that.
		 */
		ret = queue_work(batadv_event_workqueue,
				 &hardअगर_neigh->bat_v.metric_work);

		अगर (!ret)
			batadv_hardअगर_neigh_put(hardअगर_neigh);
	पूर्ण
	rcu_पढ़ो_unlock();

restart_समयr:
	batadv_v_elp_start_समयr(hard_अगरace);
out:
	वापस;
पूर्ण

/**
 * batadv_v_elp_अगरace_enable() - setup the ELP पूर्णांकerface निजी resources
 * @hard_अगरace: पूर्णांकerface क्रम which the data has to be prepared
 *
 * Return: 0 on success or a -ENOMEM in हाल of failure.
 */
पूर्णांक batadv_v_elp_अगरace_enable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	अटल स्थिर माप_प्रकार tvlv_padding = माप(__be32);
	काष्ठा batadv_elp_packet *elp_packet;
	अचिन्हित अक्षर *elp_buff;
	u32 अक्रमom_seqno;
	माप_प्रकार size;
	पूर्णांक res = -ENOMEM;

	size = ETH_HLEN + NET_IP_ALIGN + BATADV_ELP_HLEN + tvlv_padding;
	hard_अगरace->bat_v.elp_skb = dev_alloc_skb(size);
	अगर (!hard_अगरace->bat_v.elp_skb)
		जाओ out;

	skb_reserve(hard_अगरace->bat_v.elp_skb, ETH_HLEN + NET_IP_ALIGN);
	elp_buff = skb_put_zero(hard_अगरace->bat_v.elp_skb,
				BATADV_ELP_HLEN + tvlv_padding);
	elp_packet = (काष्ठा batadv_elp_packet *)elp_buff;

	elp_packet->packet_type = BATADV_ELP;
	elp_packet->version = BATADV_COMPAT_VERSION;

	/* अक्रमomize initial seqno to aव्योम collision */
	get_अक्रमom_bytes(&अक्रमom_seqno, माप(अक्रमom_seqno));
	atomic_set(&hard_अगरace->bat_v.elp_seqno, अक्रमom_seqno);

	/* assume full-duplex by शेष */
	hard_अगरace->bat_v.flags |= BATADV_FULL_DUPLEX;

	/* warn the user (again) अगर there is no throughput data is available */
	hard_अगरace->bat_v.flags &= ~BATADV_WARNING_DEFAULT;

	अगर (batadv_is_wअगरi_hardअगर(hard_अगरace))
		hard_अगरace->bat_v.flags &= ~BATADV_FULL_DUPLEX;

	INIT_DELAYED_WORK(&hard_अगरace->bat_v.elp_wq,
			  batadv_v_elp_periodic_work);
	batadv_v_elp_start_समयr(hard_अगरace);
	res = 0;

out:
	वापस res;
पूर्ण

/**
 * batadv_v_elp_अगरace_disable() - release ELP पूर्णांकerface निजी resources
 * @hard_अगरace: पूर्णांकerface क्रम which the resources have to be released
 */
व्योम batadv_v_elp_अगरace_disable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	cancel_delayed_work_sync(&hard_अगरace->bat_v.elp_wq);

	dev_kमुक्त_skb(hard_अगरace->bat_v.elp_skb);
	hard_अगरace->bat_v.elp_skb = शून्य;
पूर्ण

/**
 * batadv_v_elp_अगरace_activate() - update the ELP buffer beदीर्घing to the given
 *  hard-पूर्णांकerface
 * @primary_अगरace: the new primary पूर्णांकerface
 * @hard_अगरace: पूर्णांकerface holding the to-be-updated buffer
 */
व्योम batadv_v_elp_अगरace_activate(काष्ठा batadv_hard_अगरace *primary_अगरace,
				 काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_elp_packet *elp_packet;
	काष्ठा sk_buff *skb;

	अगर (!hard_अगरace->bat_v.elp_skb)
		वापस;

	skb = hard_अगरace->bat_v.elp_skb;
	elp_packet = (काष्ठा batadv_elp_packet *)skb->data;
	ether_addr_copy(elp_packet->orig,
			primary_अगरace->net_dev->dev_addr);
पूर्ण

/**
 * batadv_v_elp_primary_अगरace_set() - change पूर्णांकernal data to reflect the new
 *  primary पूर्णांकerface
 * @primary_अगरace: the new primary पूर्णांकerface
 */
व्योम batadv_v_elp_primary_अगरace_set(काष्ठा batadv_hard_अगरace *primary_अगरace)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;

	/* update orig field of every elp अगरace beदीर्घing to this mesh */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (primary_अगरace->soft_अगरace != hard_अगरace->soft_अगरace)
			जारी;

		batadv_v_elp_अगरace_activate(primary_अगरace, hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * batadv_v_elp_neigh_update() - update an ELP neighbour node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @neigh_addr: the neighbour पूर्णांकerface address
 * @अगर_incoming: the पूर्णांकerface the packet was received through
 * @elp_packet: the received ELP packet
 *
 * Updates the ELP neighbour node state with the data received within the new
 * ELP packet.
 */
अटल व्योम batadv_v_elp_neigh_update(काष्ठा batadv_priv *bat_priv,
				      u8 *neigh_addr,
				      काष्ठा batadv_hard_अगरace *अगर_incoming,
				      काष्ठा batadv_elp_packet *elp_packet)

अणु
	काष्ठा batadv_neigh_node *neigh;
	काष्ठा batadv_orig_node *orig_neigh;
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;
	s32 seqno_dअगरf;
	s32 elp_latest_seqno;

	orig_neigh = batadv_v_ogm_orig_get(bat_priv, elp_packet->orig);
	अगर (!orig_neigh)
		वापस;

	neigh = batadv_neigh_node_get_or_create(orig_neigh,
						अगर_incoming, neigh_addr);
	अगर (!neigh)
		जाओ orig_मुक्त;

	hardअगर_neigh = batadv_hardअगर_neigh_get(अगर_incoming, neigh_addr);
	अगर (!hardअगर_neigh)
		जाओ neigh_मुक्त;

	elp_latest_seqno = hardअगर_neigh->bat_v.elp_latest_seqno;
	seqno_dअगरf = ntohl(elp_packet->seqno) - elp_latest_seqno;

	/* known or older sequence numbers are ignored. However always aकरोpt
	 * अगर the router seems to have been restarted.
	 */
	अगर (seqno_dअगरf < 1 && seqno_dअगरf > -BATADV_ELP_MAX_AGE)
		जाओ hardअगर_मुक्त;

	neigh->last_seen = jअगरfies;
	hardअगर_neigh->last_seen = jअगरfies;
	hardअगर_neigh->bat_v.elp_latest_seqno = ntohl(elp_packet->seqno);
	hardअगर_neigh->bat_v.elp_पूर्णांकerval = ntohl(elp_packet->elp_पूर्णांकerval);

hardअगर_मुक्त:
	अगर (hardअगर_neigh)
		batadv_hardअगर_neigh_put(hardअगर_neigh);
neigh_मुक्त:
	अगर (neigh)
		batadv_neigh_node_put(neigh);
orig_मुक्त:
	अगर (orig_neigh)
		batadv_orig_node_put(orig_neigh);
पूर्ण

/**
 * batadv_v_elp_packet_recv() - मुख्य ELP packet handler
 * @skb: the received packet
 * @अगर_incoming: the पूर्णांकerface this packet was received through
 *
 * Return: NET_RX_SUCCESS and consumes the skb अगर the packet was properly
 * processed or NET_RX_DROP in हाल of failure.
 */
पूर्णांक batadv_v_elp_packet_recv(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *अगर_incoming)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(अगर_incoming->soft_अगरace);
	काष्ठा batadv_elp_packet *elp_packet;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	काष्ठा ethhdr *ethhdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	bool res;
	पूर्णांक ret = NET_RX_DROP;

	res = batadv_check_management_packet(skb, अगर_incoming, BATADV_ELP_HLEN);
	अगर (!res)
		जाओ मुक्त_skb;

	अगर (batadv_is_my_mac(bat_priv, ethhdr->h_source))
		जाओ मुक्त_skb;

	/* did we receive a B.A.T.M.A.N. V ELP packet on an पूर्णांकerface
	 * that करोes not have B.A.T.M.A.N. V ELP enabled ?
	 */
	अगर (म_भेद(bat_priv->algo_ops->name, "BATMAN_V") != 0)
		जाओ मुक्त_skb;

	elp_packet = (काष्ठा batadv_elp_packet *)skb->data;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Received ELP packet from %pM seqno %u ORIG: %pM\n",
		   ethhdr->h_source, ntohl(elp_packet->seqno),
		   elp_packet->orig);

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ मुक्त_skb;

	batadv_v_elp_neigh_update(bat_priv, ethhdr->h_source, अगर_incoming,
				  elp_packet);

	ret = NET_RX_SUCCESS;
	batadv_hardअगर_put(primary_अगर);

मुक्त_skb:
	अगर (ret == NET_RX_SUCCESS)
		consume_skb(skb);
	अन्यथा
		kमुक्त_skb(skb);

	वापस ret;
पूर्ण
