<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genetlink.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/minmax.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <net/dsfield.h>
#समावेश <net/rtnetlink.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "bat_iv_ogm.h"
#समावेश "bat_v.h"
#समावेश "bridge_loop_avoidance.h"
#समावेश "distributed-arp-table.h"
#समावेश "gateway_client.h"
#समावेश "gateway_common.h"
#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "multicast.h"
#समावेश "netlink.h"
#समावेश "network-coding.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "send.h"
#समावेश "soft-interface.h"
#समावेश "tp_meter.h"
#समावेश "translation-table.h"

/* List manipulations on hardअगर_list have to be rtnl_lock()'ed,
 * list traversals just rcu-locked
 */
काष्ठा list_head batadv_hardअगर_list;
अचिन्हित पूर्णांक batadv_hardअगर_generation;
अटल पूर्णांक (*batadv_rx_handler[256])(काष्ठा sk_buff *skb,
				     काष्ठा batadv_hard_अगरace *recv_अगर);

अचिन्हित अक्षर batadv_broadcast_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

काष्ठा workqueue_काष्ठा *batadv_event_workqueue;

अटल व्योम batadv_recv_handler_init(व्योम);

#घोषणा BATADV_UEV_TYPE_VAR	"BATTYPE="
#घोषणा BATADV_UEV_ACTION_VAR	"BATACTION="
#घोषणा BATADV_UEV_DATA_VAR	"BATDATA="

अटल अक्षर *batadv_uev_action_str[] = अणु
	"add",
	"del",
	"change",
	"loopdetect",
पूर्ण;

अटल अक्षर *batadv_uev_type_str[] = अणु
	"gw",
	"bla",
पूर्ण;

अटल पूर्णांक __init batadv_init(व्योम)
अणु
	पूर्णांक ret;

	ret = batadv_tt_cache_init();
	अगर (ret < 0)
		वापस ret;

	INIT_LIST_HEAD(&batadv_hardअगर_list);
	batadv_algo_init();

	batadv_recv_handler_init();

	batadv_v_init();
	batadv_iv_init();
	batadv_nc_init();
	batadv_tp_meter_init();

	batadv_event_workqueue = create_singlethपढ़ो_workqueue("bat_events");
	अगर (!batadv_event_workqueue)
		जाओ err_create_wq;

	रेजिस्टर_netdevice_notअगरier(&batadv_hard_अगर_notअगरier);
	rtnl_link_रेजिस्टर(&batadv_link_ops);
	batadv_netlink_रेजिस्टर();

	pr_info("B.A.T.M.A.N. advanced %s (compatibility version %i) loaded\n",
		BATADV_SOURCE_VERSION, BATADV_COMPAT_VERSION);

	वापस 0;

err_create_wq:
	batadv_tt_cache_destroy();

	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास batadv_निकास(व्योम)
अणु
	batadv_netlink_unरेजिस्टर();
	rtnl_link_unरेजिस्टर(&batadv_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&batadv_hard_अगर_notअगरier);

	flush_workqueue(batadv_event_workqueue);
	destroy_workqueue(batadv_event_workqueue);
	batadv_event_workqueue = शून्य;

	rcu_barrier();

	batadv_tt_cache_destroy();
पूर्ण

/**
 * batadv_mesh_init() - Initialize soft पूर्णांकerface
 * @soft_अगरace: netdev काष्ठा of the soft पूर्णांकerface
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_mesh_init(काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	पूर्णांक ret;

	spin_lock_init(&bat_priv->क्रमw_bat_list_lock);
	spin_lock_init(&bat_priv->क्रमw_bcast_list_lock);
	spin_lock_init(&bat_priv->tt.changes_list_lock);
	spin_lock_init(&bat_priv->tt.req_list_lock);
	spin_lock_init(&bat_priv->tt.roam_list_lock);
	spin_lock_init(&bat_priv->tt.last_changeset_lock);
	spin_lock_init(&bat_priv->tt.commit_lock);
	spin_lock_init(&bat_priv->gw.list_lock);
#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	spin_lock_init(&bat_priv->mcast.mla_lock);
	spin_lock_init(&bat_priv->mcast.want_lists_lock);
#पूर्ण_अगर
	spin_lock_init(&bat_priv->tvlv.container_list_lock);
	spin_lock_init(&bat_priv->tvlv.handler_list_lock);
	spin_lock_init(&bat_priv->softअगर_vlan_list_lock);
	spin_lock_init(&bat_priv->tp_list_lock);

	INIT_HLIST_HEAD(&bat_priv->क्रमw_bat_list);
	INIT_HLIST_HEAD(&bat_priv->क्रमw_bcast_list);
	INIT_HLIST_HEAD(&bat_priv->gw.gateway_list);
#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	INIT_HLIST_HEAD(&bat_priv->mcast.want_all_unsnoopables_list);
	INIT_HLIST_HEAD(&bat_priv->mcast.want_all_ipv4_list);
	INIT_HLIST_HEAD(&bat_priv->mcast.want_all_ipv6_list);
#पूर्ण_अगर
	INIT_LIST_HEAD(&bat_priv->tt.changes_list);
	INIT_HLIST_HEAD(&bat_priv->tt.req_list);
	INIT_LIST_HEAD(&bat_priv->tt.roam_list);
#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	INIT_HLIST_HEAD(&bat_priv->mcast.mla_list);
#पूर्ण_अगर
	INIT_HLIST_HEAD(&bat_priv->tvlv.container_list);
	INIT_HLIST_HEAD(&bat_priv->tvlv.handler_list);
	INIT_HLIST_HEAD(&bat_priv->softअगर_vlan_list);
	INIT_HLIST_HEAD(&bat_priv->tp_list);

	bat_priv->gw.generation = 0;

	ret = batadv_v_mesh_init(bat_priv);
	अगर (ret < 0)
		जाओ err;

	ret = batadv_originator_init(bat_priv);
	अगर (ret < 0)
		जाओ err;

	ret = batadv_tt_init(bat_priv);
	अगर (ret < 0)
		जाओ err;

	ret = batadv_bla_init(bat_priv);
	अगर (ret < 0)
		जाओ err;

	ret = batadv_dat_init(bat_priv);
	अगर (ret < 0)
		जाओ err;

	ret = batadv_nc_mesh_init(bat_priv);
	अगर (ret < 0)
		जाओ err;

	batadv_gw_init(bat_priv);
	batadv_mcast_init(bat_priv);

	atomic_set(&bat_priv->gw.reselect, 0);
	atomic_set(&bat_priv->mesh_state, BATADV_MESH_ACTIVE);

	वापस 0;

err:
	batadv_mesh_मुक्त(soft_अगरace);
	वापस ret;
पूर्ण

/**
 * batadv_mesh_मुक्त() - Deinitialize soft पूर्णांकerface
 * @soft_अगरace: netdev काष्ठा of the soft पूर्णांकerface
 */
व्योम batadv_mesh_मुक्त(काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);

	atomic_set(&bat_priv->mesh_state, BATADV_MESH_DEACTIVATING);

	batadv_purge_outstanding_packets(bat_priv, शून्य);

	batadv_gw_node_मुक्त(bat_priv);

	batadv_v_mesh_मुक्त(bat_priv);
	batadv_nc_mesh_मुक्त(bat_priv);
	batadv_dat_मुक्त(bat_priv);
	batadv_bla_मुक्त(bat_priv);

	batadv_mcast_मुक्त(bat_priv);

	/* Free the TT and the originator tables only after having terminated
	 * all the other depending components which may use these काष्ठाures क्रम
	 * their purposes.
	 */
	batadv_tt_मुक्त(bat_priv);

	/* Since the originator table clean up routine is accessing the TT
	 * tables as well, it has to be invoked after the TT tables have been
	 * मुक्तd and marked as empty. This ensures that no cleanup RCU callbacks
	 * accessing the TT data are scheduled क्रम later execution.
	 */
	batadv_originator_मुक्त(bat_priv);

	batadv_gw_मुक्त(bat_priv);

	मुक्त_percpu(bat_priv->bat_counters);
	bat_priv->bat_counters = शून्य;

	atomic_set(&bat_priv->mesh_state, BATADV_MESH_INACTIVE);
पूर्ण

/**
 * batadv_is_my_mac() - check अगर the given mac address beदीर्घs to any of the
 *  real पूर्णांकerfaces in the current mesh
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the address to check
 *
 * Return: 'true' अगर the mac address was found, false otherwise.
 */
bool batadv_is_my_mac(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr)
अणु
	स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace;
	bool is_my_mac = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
			जारी;

		अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
			जारी;

		अगर (batadv_compare_eth(hard_अगरace->net_dev->dev_addr, addr)) अणु
			is_my_mac = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस is_my_mac;
पूर्ण

/**
 * batadv_max_header_len() - calculate maximum encapsulation overhead क्रम a
 *  payload packet
 *
 * Return: the maximum encapsulation overhead in bytes.
 */
पूर्णांक batadv_max_header_len(व्योम)
अणु
	पूर्णांक header_len = 0;

	header_len = max_t(पूर्णांक, header_len,
			   माप(काष्ठा batadv_unicast_packet));
	header_len = max_t(पूर्णांक, header_len,
			   माप(काष्ठा batadv_unicast_4addr_packet));
	header_len = max_t(पूर्णांक, header_len,
			   माप(काष्ठा batadv_bcast_packet));

#अगर_घोषित CONFIG_BATMAN_ADV_NC
	header_len = max_t(पूर्णांक, header_len,
			   माप(काष्ठा batadv_coded_packet));
#पूर्ण_अगर

	वापस header_len + ETH_HLEN;
पूर्ण

/**
 * batadv_skb_set_priority() - sets skb priority according to packet content
 * @skb: the packet to be sent
 * @offset: offset to the packet content
 *
 * This function sets a value between 256 and 263 (802.1d priority), which
 * can be पूर्णांकerpreted by the cfg80211 or other drivers.
 */
व्योम batadv_skb_set_priority(काष्ठा sk_buff *skb, पूर्णांक offset)
अणु
	काष्ठा iphdr ip_hdr_पंचांगp, *ip_hdr;
	काष्ठा ipv6hdr ip6_hdr_पंचांगp, *ip6_hdr;
	काष्ठा ethhdr ethhdr_पंचांगp, *ethhdr;
	काष्ठा vlan_ethhdr *vhdr, vhdr_पंचांगp;
	u32 prio;

	/* alपढ़ोy set, करो nothing */
	अगर (skb->priority >= 256 && skb->priority <= 263)
		वापस;

	ethhdr = skb_header_poपूर्णांकer(skb, offset, माप(*ethhdr), &ethhdr_पंचांगp);
	अगर (!ethhdr)
		वापस;

	चयन (ethhdr->h_proto) अणु
	हाल htons(ETH_P_8021Q):
		vhdr = skb_header_poपूर्णांकer(skb, offset + माप(*vhdr),
					  माप(*vhdr), &vhdr_पंचांगp);
		अगर (!vhdr)
			वापस;
		prio = ntohs(vhdr->h_vlan_TCI) & VLAN_PRIO_MASK;
		prio = prio >> VLAN_PRIO_SHIFT;
		अवरोध;
	हाल htons(ETH_P_IP):
		ip_hdr = skb_header_poपूर्णांकer(skb, offset + माप(*ethhdr),
					    माप(*ip_hdr), &ip_hdr_पंचांगp);
		अगर (!ip_hdr)
			वापस;
		prio = (ipv4_get_dsfield(ip_hdr) & 0xfc) >> 5;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		ip6_hdr = skb_header_poपूर्णांकer(skb, offset + माप(*ethhdr),
					     माप(*ip6_hdr), &ip6_hdr_पंचांगp);
		अगर (!ip6_hdr)
			वापस;
		prio = (ipv6_get_dsfield(ip6_hdr) & 0xfc) >> 5;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	skb->priority = prio + 256;
पूर्ण

अटल पूर्णांक batadv_recv_unhandled_packet(काष्ठा sk_buff *skb,
					काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	kमुक्त_skb(skb);

	वापस NET_RX_DROP;
पूर्ण

/* incoming packets with the baपंचांगan ethertype received on any active hard
 * पूर्णांकerface
 */

/**
 * batadv_baपंचांगan_skb_recv() - Handle incoming message from an hard पूर्णांकerface
 * @skb: the received packet
 * @dev: the net device that the packet was received on
 * @ptype: packet type of incoming packet (ETH_P_BATMAN)
 * @orig_dev: the original receive net device (e.g. bonded device)
 *
 * Return: NET_RX_SUCCESS on success or NET_RX_DROP in हाल of failure
 */
पूर्णांक batadv_baपंचांगan_skb_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *ptype,
			   काष्ठा net_device *orig_dev)
अणु
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_ogm_packet *batadv_ogm_packet;
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	u8 idx;

	hard_अगरace = container_of(ptype, काष्ठा batadv_hard_अगरace,
				  baपंचांगan_adv_ptype);

	/* Prevent processing a packet received on an पूर्णांकerface which is getting
	 * shut करोwn otherwise the packet may trigger de-reference errors
	 * further करोwn in the receive path.
	 */
	अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
		जाओ err_out;

	skb = skb_share_check(skb, GFP_ATOMIC);

	/* skb was released by skb_share_check() */
	अगर (!skb)
		जाओ err_put;

	/* packet should hold at least type and version */
	अगर (unlikely(!pskb_may_pull(skb, 2)))
		जाओ err_मुक्त;

	/* expect a valid ethernet header here. */
	अगर (unlikely(skb->mac_len != ETH_HLEN || !skb_mac_header(skb)))
		जाओ err_मुक्त;

	अगर (!hard_अगरace->soft_अगरace)
		जाओ err_मुक्त;

	bat_priv = netdev_priv(hard_अगरace->soft_अगरace);

	अगर (atomic_पढ़ो(&bat_priv->mesh_state) != BATADV_MESH_ACTIVE)
		जाओ err_मुक्त;

	/* discard frames on not active पूर्णांकerfaces */
	अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
		जाओ err_मुक्त;

	batadv_ogm_packet = (काष्ठा batadv_ogm_packet *)skb->data;

	अगर (batadv_ogm_packet->version != BATADV_COMPAT_VERSION) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: incompatible batman version (%i)\n",
			   batadv_ogm_packet->version);
		जाओ err_मुक्त;
	पूर्ण

	/* reset control block to aव्योम left overs from previous users */
	स_रखो(skb->cb, 0, माप(काष्ठा batadv_skb_cb));

	idx = batadv_ogm_packet->packet_type;
	(*batadv_rx_handler[idx])(skb, hard_अगरace);

	batadv_hardअगर_put(hard_अगरace);

	/* वापस NET_RX_SUCCESS in any हाल as we
	 * most probably dropped the packet क्रम
	 * routing-logical reasons.
	 */
	वापस NET_RX_SUCCESS;

err_मुक्त:
	kमुक्त_skb(skb);
err_put:
	batadv_hardअगर_put(hard_अगरace);
err_out:
	वापस NET_RX_DROP;
पूर्ण

अटल व्योम batadv_recv_handler_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(batadv_rx_handler); i++)
		batadv_rx_handler[i] = batadv_recv_unhandled_packet;

	क्रम (i = BATADV_UNICAST_MIN; i <= BATADV_UNICAST_MAX; i++)
		batadv_rx_handler[i] = batadv_recv_unhandled_unicast_packet;

	/* compile समय checks क्रम sizes */
	BUILD_BUG_ON(माप(काष्ठा batadv_bla_claim_dst) != 6);
	BUILD_BUG_ON(माप(काष्ठा batadv_ogm_packet) != 24);
	BUILD_BUG_ON(माप(काष्ठा batadv_icmp_header) != 20);
	BUILD_BUG_ON(माप(काष्ठा batadv_icmp_packet) != 20);
	BUILD_BUG_ON(माप(काष्ठा batadv_icmp_packet_rr) != 116);
	BUILD_BUG_ON(माप(काष्ठा batadv_unicast_packet) != 10);
	BUILD_BUG_ON(माप(काष्ठा batadv_unicast_4addr_packet) != 18);
	BUILD_BUG_ON(माप(काष्ठा batadv_frag_packet) != 20);
	BUILD_BUG_ON(माप(काष्ठा batadv_bcast_packet) != 14);
	BUILD_BUG_ON(माप(काष्ठा batadv_coded_packet) != 46);
	BUILD_BUG_ON(माप(काष्ठा batadv_unicast_tvlv_packet) != 20);
	BUILD_BUG_ON(माप(काष्ठा batadv_tvlv_hdr) != 4);
	BUILD_BUG_ON(माप(काष्ठा batadv_tvlv_gateway_data) != 8);
	BUILD_BUG_ON(माप(काष्ठा batadv_tvlv_tt_vlan_data) != 8);
	BUILD_BUG_ON(माप(काष्ठा batadv_tvlv_tt_change) != 12);
	BUILD_BUG_ON(माप(काष्ठा batadv_tvlv_roam_adv) != 8);

	i = माप_field(काष्ठा sk_buff, cb);
	BUILD_BUG_ON(माप(काष्ठा batadv_skb_cb) > i);

	/* broadcast packet */
	batadv_rx_handler[BATADV_BCAST] = batadv_recv_bcast_packet;

	/* unicast packets ... */
	/* unicast with 4 addresses packet */
	batadv_rx_handler[BATADV_UNICAST_4ADDR] = batadv_recv_unicast_packet;
	/* unicast packet */
	batadv_rx_handler[BATADV_UNICAST] = batadv_recv_unicast_packet;
	/* unicast tvlv packet */
	batadv_rx_handler[BATADV_UNICAST_TVLV] = batadv_recv_unicast_tvlv;
	/* baपंचांगan icmp packet */
	batadv_rx_handler[BATADV_ICMP] = batadv_recv_icmp_packet;
	/* Fragmented packets */
	batadv_rx_handler[BATADV_UNICAST_FRAG] = batadv_recv_frag_packet;
पूर्ण

/**
 * batadv_recv_handler_रेजिस्टर() - Register handler क्रम baपंचांगan-adv packet type
 * @packet_type: batadv_packettype which should be handled
 * @recv_handler: receive handler क्रम the packet type
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक
batadv_recv_handler_रेजिस्टर(u8 packet_type,
			     पूर्णांक (*recv_handler)(काष्ठा sk_buff *,
						 काष्ठा batadv_hard_अगरace *))
अणु
	पूर्णांक (*curr)(काष्ठा sk_buff *skb,
		    काष्ठा batadv_hard_अगरace *recv_अगर);
	curr = batadv_rx_handler[packet_type];

	अगर (curr != batadv_recv_unhandled_packet &&
	    curr != batadv_recv_unhandled_unicast_packet)
		वापस -EBUSY;

	batadv_rx_handler[packet_type] = recv_handler;
	वापस 0;
पूर्ण

/**
 * batadv_recv_handler_unरेजिस्टर() - Unरेजिस्टर handler क्रम packet type
 * @packet_type: batadv_packettype which should no दीर्घer be handled
 */
व्योम batadv_recv_handler_unरेजिस्टर(u8 packet_type)
अणु
	batadv_rx_handler[packet_type] = batadv_recv_unhandled_packet;
पूर्ण

/**
 * batadv_skb_crc32() - calculate CRC32 of the whole packet and skip bytes in
 *  the header
 * @skb: skb poपूर्णांकing to fragmented socket buffers
 * @payload_ptr: Poपूर्णांकer to position inside the head buffer of the skb
 *  marking the start of the data to be CRC'ed
 *
 * payload_ptr must always poपूर्णांक to an address in the skb head buffer and not to
 * a fragment.
 *
 * Return: big endian crc32c of the checksummed data
 */
__be32 batadv_skb_crc32(काष्ठा sk_buff *skb, u8 *payload_ptr)
अणु
	u32 crc = 0;
	अचिन्हित पूर्णांक from;
	अचिन्हित पूर्णांक to = skb->len;
	काष्ठा skb_seq_state st;
	स्थिर u8 *data;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक consumed = 0;

	from = (अचिन्हित पूर्णांक)(payload_ptr - skb->data);

	skb_prepare_seq_पढ़ो(skb, from, to, &st);
	जबतक ((len = skb_seq_पढ़ो(consumed, &data, &st)) != 0) अणु
		crc = crc32c(crc, data, len);
		consumed += len;
	पूर्ण

	वापस htonl(crc);
पूर्ण

/**
 * batadv_get_vid() - extract the VLAN identअगरier from skb अगर any
 * @skb: the buffer containing the packet
 * @header_len: length of the baपंचांगan header preceding the ethernet header
 *
 * Return: VID with the BATADV_VLAN_HAS_TAG flag when the packet embedded in the
 * skb is vlan tagged. Otherwise BATADV_NO_FLAGS.
 */
अचिन्हित लघु batadv_get_vid(काष्ठा sk_buff *skb, माप_प्रकार header_len)
अणु
	काष्ठा ethhdr *ethhdr = (काष्ठा ethhdr *)(skb->data + header_len);
	काष्ठा vlan_ethhdr *vhdr;
	अचिन्हित लघु vid;

	अगर (ethhdr->h_proto != htons(ETH_P_8021Q))
		वापस BATADV_NO_FLAGS;

	अगर (!pskb_may_pull(skb, header_len + VLAN_ETH_HLEN))
		वापस BATADV_NO_FLAGS;

	vhdr = (काष्ठा vlan_ethhdr *)(skb->data + header_len);
	vid = ntohs(vhdr->h_vlan_TCI) & VLAN_VID_MASK;
	vid |= BATADV_VLAN_HAS_TAG;

	वापस vid;
पूर्ण

/**
 * batadv_vlan_ap_isola_get() - वापस AP isolation status क्रम the given vlan
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: the VLAN identअगरier क्रम which the AP isolation attributed as to be
 *  looked up
 *
 * Return: true अगर AP isolation is on क्रम the VLAN identअगरied by vid, false
 * otherwise
 */
bool batadv_vlan_ap_isola_get(काष्ठा batadv_priv *bat_priv, अचिन्हित लघु vid)
अणु
	bool ap_isolation_enabled = false;
	काष्ठा batadv_softअगर_vlan *vlan;

	/* अगर the AP isolation is requested on a VLAN, then check क्रम its
	 * setting in the proper VLAN निजी data काष्ठाure
	 */
	vlan = batadv_softअगर_vlan_get(bat_priv, vid);
	अगर (vlan) अणु
		ap_isolation_enabled = atomic_पढ़ो(&vlan->ap_isolation);
		batadv_softअगर_vlan_put(vlan);
	पूर्ण

	वापस ap_isolation_enabled;
पूर्ण

/**
 * batadv_throw_uevent() - Send an uevent with baपंचांगan-adv specअगरic env data
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @type: subप्रणाली type of event. Stored in uevent's BATTYPE
 * @action: action type of event. Stored in uevent's BATACTION
 * @data: string with additional inक्रमmation to the event (ignored क्रम
 *  BATADV_UEV_DEL). Stored in uevent's BATDATA
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_throw_uevent(काष्ठा batadv_priv *bat_priv, क्रमागत batadv_uev_type type,
			क्रमागत batadv_uev_action action, स्थिर अक्षर *data)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा kobject *bat_kobj;
	अक्षर *uevent_env[4] = अणु शून्य, शून्य, शून्य, शून्य पूर्ण;

	bat_kobj = &bat_priv->soft_अगरace->dev.kobj;

	uevent_env[0] = kaप्र_लिखो(GFP_ATOMIC,
				  "%s%s", BATADV_UEV_TYPE_VAR,
				  batadv_uev_type_str[type]);
	अगर (!uevent_env[0])
		जाओ out;

	uevent_env[1] = kaप्र_लिखो(GFP_ATOMIC,
				  "%s%s", BATADV_UEV_ACTION_VAR,
				  batadv_uev_action_str[action]);
	अगर (!uevent_env[1])
		जाओ out;

	/* If the event is DEL, ignore the data field */
	अगर (action != BATADV_UEV_DEL) अणु
		uevent_env[2] = kaप्र_लिखो(GFP_ATOMIC,
					  "%s%s", BATADV_UEV_DATA_VAR, data);
		अगर (!uevent_env[2])
			जाओ out;
	पूर्ण

	ret = kobject_uevent_env(bat_kobj, KOBJ_CHANGE, uevent_env);
out:
	kमुक्त(uevent_env[0]);
	kमुक्त(uevent_env[1]);
	kमुक्त(uevent_env[2]);

	अगर (ret)
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Impossible to send uevent for (%s,%s,%s) event (err: %d)\n",
			   batadv_uev_type_str[type],
			   batadv_uev_action_str[action],
			   (action == BATADV_UEV_DEL ? "NULL" : data), ret);
	वापस ret;
पूर्ण

module_init(batadv_init);
module_निकास(batadv_निकास);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(BATADV_DRIVER_AUTHOR);
MODULE_DESCRIPTION(BATADV_DRIVER_DESC);
MODULE_VERSION(BATADV_SOURCE_VERSION);
MODULE_ALIAS_RTNL_LINK("batadv");
MODULE_ALIAS_GENL_FAMILY(BATADV_NL_NAME);
