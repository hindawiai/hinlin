<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_TYPES_H_
#घोषणा _NET_BATMAN_ADV_TYPES_H_

#अगर_अघोषित _NET_BATMAN_ADV_MAIN_H_
#त्रुटि only "main.h" can be included directly
#पूर्ण_अगर

#समावेश <linux/average.h>
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/sched.h> /* क्रम linux/रुको.h */
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#अगर_घोषित CONFIG_BATMAN_ADV_DAT

/**
 * प्रकार batadv_dat_addr_t - type used क्रम all DHT addresses
 *
 * If it is changed, BATADV_DAT_ADDR_MAX is changed as well.
 *
 * *Please be careful: batadv_dat_addr_t must be UNSIGNED*
 */
प्रकार u16 batadv_dat_addr_t;

#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DAT */

/**
 * क्रमागत batadv_dhcp_recipient - dhcp destination
 */
क्रमागत batadv_dhcp_recipient अणु
	/** @BATADV_DHCP_NO: packet is not a dhcp message */
	BATADV_DHCP_NO = 0,

	/** @BATADV_DHCP_TO_SERVER: dhcp message is directed to a server */
	BATADV_DHCP_TO_SERVER,

	/** @BATADV_DHCP_TO_CLIENT: dhcp message is directed to a client */
	BATADV_DHCP_TO_CLIENT,
पूर्ण;

/**
 * BATADV_TT_REMOTE_MASK - biपंचांगask selecting the flags that are sent over the
 *  wire only
 */
#घोषणा BATADV_TT_REMOTE_MASK	0x00FF

/**
 * BATADV_TT_SYNC_MASK - biपंचांगask of the flags that need to be kept in sync
 *  among the nodes. These flags are used to compute the global/local CRC
 */
#घोषणा BATADV_TT_SYNC_MASK	0x00F0

/**
 * काष्ठा batadv_hard_अगरace_bat_iv - per hard-पूर्णांकerface B.A.T.M.A.N. IV data
 */
काष्ठा batadv_hard_अगरace_bat_iv अणु
	/** @ogm_buff: buffer holding the OGM packet */
	अचिन्हित अक्षर *ogm_buff;

	/** @ogm_buff_len: length of the OGM packet buffer */
	पूर्णांक ogm_buff_len;

	/** @ogm_seqno: OGM sequence number - used to identअगरy each OGM */
	atomic_t ogm_seqno;

	/** @ogm_buff_mutex: lock protecting ogm_buff and ogm_buff_len */
	काष्ठा mutex ogm_buff_mutex;
पूर्ण;

/**
 * क्रमागत batadv_v_hard_अगरace_flags - पूर्णांकerface flags useful to B.A.T.M.A.N. V
 */
क्रमागत batadv_v_hard_अगरace_flags अणु
	/**
	 * @BATADV_FULL_DUPLEX: tells अगर the connection over this link is
	 *  full-duplex
	 */
	BATADV_FULL_DUPLEX	= BIT(0),

	/**
	 * @BATADV_WARNING_DEFAULT: tells whether we have warned the user that
	 *  no throughput data is available क्रम this पूर्णांकerface and that शेष
	 *  values are assumed.
	 */
	BATADV_WARNING_DEFAULT	= BIT(1),
पूर्ण;

/**
 * काष्ठा batadv_hard_अगरace_bat_v - per hard-पूर्णांकerface B.A.T.M.A.N. V data
 */
काष्ठा batadv_hard_अगरace_bat_v अणु
	/** @elp_पूर्णांकerval: समय पूर्णांकerval between two ELP transmissions */
	atomic_t elp_पूर्णांकerval;

	/** @elp_seqno: current ELP sequence number */
	atomic_t elp_seqno;

	/** @elp_skb: base skb containing the ELP message to send */
	काष्ठा sk_buff *elp_skb;

	/** @elp_wq: workqueue used to schedule ELP transmissions */
	काष्ठा delayed_work elp_wq;

	/** @aggr_wq: workqueue used to transmit queued OGM packets */
	काष्ठा delayed_work aggr_wq;

	/** @aggr_list: queue क्रम to be aggregated OGM packets */
	काष्ठा sk_buff_head aggr_list;

	/** @aggr_len: size of the OGM aggregate (excluding ethernet header) */
	अचिन्हित पूर्णांक aggr_len;

	/**
	 * @throughput_override: throughput override to disable link
	 *  स्वतः-detection
	 */
	atomic_t throughput_override;

	/** @flags: पूर्णांकerface specअगरic flags */
	u8 flags;
पूर्ण;

/**
 * क्रमागत batadv_hard_अगरace_wअगरi_flags - Flags describing the wअगरi configuration
 *  of a batadv_hard_अगरace
 */
क्रमागत batadv_hard_अगरace_wअगरi_flags अणु
	/** @BATADV_HARDIF_WIFI_WEXT_सूचीECT: it is a wext wअगरi device */
	BATADV_HARDIF_WIFI_WEXT_सूचीECT = BIT(0),

	/** @BATADV_HARDIF_WIFI_CFG80211_सूचीECT: it is a cfg80211 wअगरi device */
	BATADV_HARDIF_WIFI_CFG80211_सूचीECT = BIT(1),

	/**
	 * @BATADV_HARDIF_WIFI_WEXT_INसूचीECT: link device is a wext wअगरi device
	 */
	BATADV_HARDIF_WIFI_WEXT_INसूचीECT = BIT(2),

	/**
	 * @BATADV_HARDIF_WIFI_CFG80211_INसूचीECT: link device is a cfg80211 wअगरi
	 * device
	 */
	BATADV_HARDIF_WIFI_CFG80211_INसूचीECT = BIT(3),
पूर्ण;

/**
 * काष्ठा batadv_hard_अगरace - network device known to baपंचांगan-adv
 */
काष्ठा batadv_hard_अगरace अणु
	/** @list: list node क्रम batadv_hardअगर_list */
	काष्ठा list_head list;

	/** @अगर_status: status of the पूर्णांकerface क्रम baपंचांगan-adv */
	अक्षर अगर_status;

	/**
	 * @num_bcasts: number of payload re-broadcasts on this पूर्णांकerface (ARQ)
	 */
	u8 num_bcasts;

	/**
	 * @wअगरi_flags: flags whether this is (directly or indirectly) a wअगरi
	 *  पूर्णांकerface
	 */
	u32 wअगरi_flags;

	/** @net_dev: poपूर्णांकer to the net_device */
	काष्ठा net_device *net_dev;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/**
	 * @baपंचांगan_adv_ptype: packet type describing packets that should be
	 * processed by baपंचांगan-adv क्रम this पूर्णांकerface
	 */
	काष्ठा packet_type baपंचांगan_adv_ptype;

	/**
	 * @soft_अगरace: the baपंचांगan-adv पूर्णांकerface which uses this network
	 *  पूर्णांकerface
	 */
	काष्ठा net_device *soft_अगरace;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;

	/**
	 * @hop_penalty: penalty which will be applied to the tq-field
	 * of an OGM received via this पूर्णांकerface
	 */
	atomic_t hop_penalty;

	/** @bat_iv: per hard-पूर्णांकerface B.A.T.M.A.N. IV data */
	काष्ठा batadv_hard_अगरace_bat_iv bat_iv;

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	/** @bat_v: per hard-पूर्णांकerface B.A.T.M.A.N. V data */
	काष्ठा batadv_hard_अगरace_bat_v bat_v;
#पूर्ण_अगर

	/**
	 * @neigh_list: list of unique single hop neighbors via this पूर्णांकerface
	 */
	काष्ठा hlist_head neigh_list;

	/** @neigh_list_lock: lock protecting neigh_list */
	spinlock_t neigh_list_lock;
पूर्ण;

/**
 * काष्ठा batadv_orig_अगरinfo_bat_iv - B.A.T.M.A.N. IV निजी orig_अगरinfo
 *  members
 */
काष्ठा batadv_orig_अगरinfo_bat_iv अणु
	/**
	 * @bcast_own: bitfield which counts the number of our OGMs this
	 * orig_node rebroadcasted "back" to us  (relative to last_real_seqno)
	 */
	DECLARE_BITMAP(bcast_own, BATADV_TQ_LOCAL_WINDOW_SIZE);

	/** @bcast_own_sum: sum of bcast_own */
	u8 bcast_own_sum;
पूर्ण;

/**
 * काष्ठा batadv_orig_अगरinfo - originator info per outgoing पूर्णांकerface
 */
काष्ठा batadv_orig_अगरinfo अणु
	/** @list: list node क्रम &batadv_orig_node.अगरinfo_list */
	काष्ठा hlist_node list;

	/** @अगर_outgoing: poपूर्णांकer to outgoing hard-पूर्णांकerface */
	काष्ठा batadv_hard_अगरace *अगर_outgoing;

	/** @router: router that should be used to reach this originator */
	काष्ठा batadv_neigh_node __rcu *router;

	/** @last_real_seqno: last and best known sequence number */
	u32 last_real_seqno;

	/** @last_ttl: ttl of last received packet */
	u8 last_ttl;

	/** @last_seqno_क्रमwarded: seqno of the OGM which was क्रमwarded last */
	u32 last_seqno_क्रमwarded;

	/** @baपंचांगan_seqno_reset: समय when the baपंचांगan seqno winकरोw was reset */
	अचिन्हित दीर्घ baपंचांगan_seqno_reset;

	/** @bat_iv: B.A.T.M.A.N. IV निजी काष्ठाure */
	काष्ठा batadv_orig_अगरinfo_bat_iv bat_iv;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_frag_table_entry - head in the fragment buffer table
 */
काष्ठा batadv_frag_table_entry अणु
	/** @fragment_list: head of list with fragments */
	काष्ठा hlist_head fragment_list;

	/** @lock: lock to protect the list of fragments */
	spinlock_t lock;

	/** @बारtamp: समय (jअगरfie) of last received fragment */
	अचिन्हित दीर्घ बारtamp;

	/** @seqno: sequence number of the fragments in the list */
	u16 seqno;

	/** @size: accumulated size of packets in list */
	u16 size;

	/** @total_size: expected size of the assembled packet */
	u16 total_size;
पूर्ण;

/**
 * काष्ठा batadv_frag_list_entry - entry in a list of fragments
 */
काष्ठा batadv_frag_list_entry अणु
	/** @list: list node inक्रमmation */
	काष्ठा hlist_node list;

	/** @skb: fragment */
	काष्ठा sk_buff *skb;

	/** @no: fragment number in the set */
	u8 no;
पूर्ण;

/**
 * काष्ठा batadv_vlan_tt - VLAN specअगरic TT attributes
 */
काष्ठा batadv_vlan_tt अणु
	/** @crc: CRC32 checksum of the entries beदीर्घing to this vlan */
	u32 crc;

	/** @num_entries: number of TT entries क्रम this VLAN */
	atomic_t num_entries;
पूर्ण;

/**
 * काष्ठा batadv_orig_node_vlan - VLAN specअगरic data per orig_node
 */
काष्ठा batadv_orig_node_vlan अणु
	/** @vid: the VLAN identअगरier */
	अचिन्हित लघु vid;

	/** @tt: VLAN specअगरic TT attributes */
	काष्ठा batadv_vlan_tt tt;

	/** @list: list node क्रम &batadv_orig_node.vlan_list */
	काष्ठा hlist_node list;

	/**
	 * @refcount: number of context where this object is currently in use
	 */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in a RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_orig_bat_iv - B.A.T.M.A.N. IV निजी orig_node members
 */
काष्ठा batadv_orig_bat_iv अणु
	/**
	 * @ogm_cnt_lock: lock protecting &batadv_orig_अगरinfo_bat_iv.bcast_own,
	 * &batadv_orig_अगरinfo_bat_iv.bcast_own_sum,
	 * &batadv_neigh_अगरinfo_bat_iv.bat_iv.real_bits and
	 * &batadv_neigh_अगरinfo_bat_iv.real_packet_count
	 */
	spinlock_t ogm_cnt_lock;
पूर्ण;

/**
 * काष्ठा batadv_orig_node - काष्ठाure क्रम orig_list मुख्यtaining nodes of mesh
 */
काष्ठा batadv_orig_node अणु
	/** @orig: originator ethernet address */
	u8 orig[ETH_ALEN];

	/** @अगरinfo_list: list क्रम routers per outgoing पूर्णांकerface */
	काष्ठा hlist_head अगरinfo_list;

	/**
	 * @last_bonding_candidate: poपूर्णांकer to last अगरinfo of last used router
	 */
	काष्ठा batadv_orig_अगरinfo *last_bonding_candidate;

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	/** @dat_addr: address of the orig node in the distributed hash */
	batadv_dat_addr_t dat_addr;
#पूर्ण_अगर

	/** @last_seen: समय when last packet from this node was received */
	अचिन्हित दीर्घ last_seen;

	/**
	 * @bcast_seqno_reset: समय when the broadcast seqno winकरोw was reset
	 */
	अचिन्हित दीर्घ bcast_seqno_reset;

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	/**
	 * @mcast_handler_lock: synchronizes mcast-capability and -flag changes
	 */
	spinlock_t mcast_handler_lock;

	/** @mcast_flags: multicast flags announced by the orig node */
	u8 mcast_flags;

	/**
	 * @mcast_want_all_unsnoopables_node: a list node क्रम the
	 *  mcast.want_all_unsnoopables list
	 */
	काष्ठा hlist_node mcast_want_all_unsnoopables_node;

	/**
	 * @mcast_want_all_ipv4_node: a list node क्रम the mcast.want_all_ipv4
	 *  list
	 */
	काष्ठा hlist_node mcast_want_all_ipv4_node;
	/**
	 * @mcast_want_all_ipv6_node: a list node क्रम the mcast.want_all_ipv6
	 *  list
	 */
	काष्ठा hlist_node mcast_want_all_ipv6_node;

	/**
	 * @mcast_want_all_rtr4_node: a list node क्रम the mcast.want_all_rtr4
	 *  list
	 */
	काष्ठा hlist_node mcast_want_all_rtr4_node;
	/**
	 * @mcast_want_all_rtr6_node: a list node क्रम the mcast.want_all_rtr6
	 *  list
	 */
	काष्ठा hlist_node mcast_want_all_rtr6_node;
#पूर्ण_अगर

	/** @capabilities: announced capabilities of this originator */
	अचिन्हित दीर्घ capabilities;

	/**
	 * @capa_initialized: bitfield to remember whether a capability was
	 *  initialized
	 */
	अचिन्हित दीर्घ capa_initialized;

	/** @last_ttvn: last seen translation table version number */
	atomic_t last_ttvn;

	/** @tt_buff: last tt changeset this node received from the orig node */
	अचिन्हित अक्षर *tt_buff;

	/**
	 * @tt_buff_len: length of the last tt changeset this node received
	 *  from the orig node
	 */
	s16 tt_buff_len;

	/** @tt_buff_lock: lock that protects tt_buff and tt_buff_len */
	spinlock_t tt_buff_lock;

	/**
	 * @tt_lock: aव्योमs concurrent पढ़ो from and ग_लिखो to the table. Table
	 *  update is made up of two operations (data काष्ठाure update and
	 *  metadata -CRC/TTVN-recalculation) and they have to be executed
	 *  atomically in order to aव्योम another thपढ़ो to पढ़ो the
	 *  table/metadata between those.
	 */
	spinlock_t tt_lock;

	/**
	 * @bcast_bits: bitfield containing the info which payload broadcast
	 *  originated from this orig node this host alपढ़ोy has seen (relative
	 *  to last_bcast_seqno)
	 */
	DECLARE_BITMAP(bcast_bits, BATADV_TQ_LOCAL_WINDOW_SIZE);

	/**
	 * @last_bcast_seqno: last broadcast sequence number received by this
	 *  host
	 */
	u32 last_bcast_seqno;

	/**
	 * @neigh_list: list of potential next hop neighbor towards this orig
	 *  node
	 */
	काष्ठा hlist_head neigh_list;

	/**
	 * @neigh_list_lock: lock protecting neigh_list, अगरinfo_list,
	 *  last_bonding_candidate and router
	 */
	spinlock_t neigh_list_lock;

	/** @hash_entry: hlist node क्रम &batadv_priv.orig_hash */
	काष्ठा hlist_node hash_entry;

	/** @bat_priv: poपूर्णांकer to soft_अगरace this orig node beदीर्घs to */
	काष्ठा batadv_priv *bat_priv;

	/** @bcast_seqno_lock: lock protecting bcast_bits & last_bcast_seqno */
	spinlock_t bcast_seqno_lock;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;

#अगर_घोषित CONFIG_BATMAN_ADV_NC
	/** @in_coding_list: list of nodes this orig can hear */
	काष्ठा list_head in_coding_list;

	/** @out_coding_list: list of nodes that can hear this orig */
	काष्ठा list_head out_coding_list;

	/** @in_coding_list_lock: protects in_coding_list */
	spinlock_t in_coding_list_lock;

	/** @out_coding_list_lock: protects out_coding_list */
	spinlock_t out_coding_list_lock;
#पूर्ण_अगर

	/** @fragments: array with heads क्रम fragment chains */
	काष्ठा batadv_frag_table_entry fragments[BATADV_FRAG_BUFFER_COUNT];

	/**
	 * @vlan_list: a list of orig_node_vlan काष्ठाs, one per VLAN served by
	 *  the originator represented by this object
	 */
	काष्ठा hlist_head vlan_list;

	/** @vlan_list_lock: lock protecting vlan_list */
	spinlock_t vlan_list_lock;

	/** @bat_iv: B.A.T.M.A.N. IV निजी काष्ठाure */
	काष्ठा batadv_orig_bat_iv bat_iv;
पूर्ण;

/**
 * क्रमागत batadv_orig_capabilities - orig node capabilities
 */
क्रमागत batadv_orig_capabilities अणु
	/**
	 * @BATADV_ORIG_CAPA_HAS_DAT: orig node has distributed arp table
	 *  enabled
	 */
	BATADV_ORIG_CAPA_HAS_DAT,

	/** @BATADV_ORIG_CAPA_HAS_NC: orig node has network coding enabled */
	BATADV_ORIG_CAPA_HAS_NC,

	/** @BATADV_ORIG_CAPA_HAS_TT: orig node has tt capability */
	BATADV_ORIG_CAPA_HAS_TT,

	/**
	 * @BATADV_ORIG_CAPA_HAS_MCAST: orig node has some multicast capability
	 *  (= orig node announces a tvlv of type BATADV_TVLV_MCAST)
	 */
	BATADV_ORIG_CAPA_HAS_MCAST,
पूर्ण;

/**
 * काष्ठा batadv_gw_node - काष्ठाure क्रम orig nodes announcing gw capabilities
 */
काष्ठा batadv_gw_node अणु
	/** @list: list node क्रम &batadv_priv_gw.list */
	काष्ठा hlist_node list;

	/** @orig_node: poपूर्णांकer to corresponding orig node */
	काष्ठा batadv_orig_node *orig_node;

	/** @bandwidth_करोwn: advertised uplink करोwnload bandwidth */
	u32 bandwidth_करोwn;

	/** @bandwidth_up: advertised uplink upload bandwidth */
	u32 bandwidth_up;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

DECLARE_EWMA(throughput, 10, 8)

/**
 * काष्ठा batadv_hardअगर_neigh_node_bat_v - B.A.T.M.A.N. V निजी neighbor
 *  inक्रमmation
 */
काष्ठा batadv_hardअगर_neigh_node_bat_v अणु
	/** @throughput: ewma link throughput towards this neighbor */
	काष्ठा ewma_throughput throughput;

	/** @elp_पूर्णांकerval: समय पूर्णांकerval between two ELP transmissions */
	u32 elp_पूर्णांकerval;

	/** @elp_latest_seqno: latest and best known ELP sequence number */
	u32 elp_latest_seqno;

	/**
	 * @last_unicast_tx: when the last unicast packet has been sent to this
	 *  neighbor
	 */
	अचिन्हित दीर्घ last_unicast_tx;

	/** @metric_work: work queue callback item क्रम metric update */
	काष्ठा work_काष्ठा metric_work;
पूर्ण;

/**
 * काष्ठा batadv_hardअगर_neigh_node - unique neighbor per hard-पूर्णांकerface
 */
काष्ठा batadv_hardअगर_neigh_node अणु
	/** @list: list node क्रम &batadv_hard_अगरace.neigh_list */
	काष्ठा hlist_node list;

	/** @addr: the MAC address of the neighboring पूर्णांकerface */
	u8 addr[ETH_ALEN];

	/**
	 * @orig: the address of the originator this neighbor node beदीर्घs to
	 */
	u8 orig[ETH_ALEN];

	/** @अगर_incoming: poपूर्णांकer to incoming hard-पूर्णांकerface */
	काष्ठा batadv_hard_अगरace *अगर_incoming;

	/** @last_seen: when last packet via this neighbor was received */
	अचिन्हित दीर्घ last_seen;

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	/** @bat_v: B.A.T.M.A.N. V निजी data */
	काष्ठा batadv_hardअगर_neigh_node_bat_v bat_v;
#पूर्ण_अगर

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in a RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_neigh_node - काष्ठाure क्रम single hops neighbors
 */
काष्ठा batadv_neigh_node अणु
	/** @list: list node क्रम &batadv_orig_node.neigh_list */
	काष्ठा hlist_node list;

	/** @orig_node: poपूर्णांकer to corresponding orig_node */
	काष्ठा batadv_orig_node *orig_node;

	/** @addr: the MAC address of the neighboring पूर्णांकerface */
	u8 addr[ETH_ALEN];

	/** @अगरinfo_list: list क्रम routing metrics per outgoing पूर्णांकerface */
	काष्ठा hlist_head अगरinfo_list;

	/** @अगरinfo_lock: lock protecting अगरinfo_list and its members */
	spinlock_t अगरinfo_lock;

	/** @अगर_incoming: poपूर्णांकer to incoming hard-पूर्णांकerface */
	काष्ठा batadv_hard_अगरace *अगर_incoming;

	/** @last_seen: when last packet via this neighbor was received */
	अचिन्हित दीर्घ last_seen;

	/** @hardअगर_neigh: hardअगर_neigh of this neighbor */
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_neigh_अगरinfo_bat_iv - neighbor inक्रमmation per outgoing
 *  पूर्णांकerface क्रम B.A.T.M.A.N. IV
 */
काष्ठा batadv_neigh_अगरinfo_bat_iv अणु
	/** @tq_recv: ring buffer of received TQ values from this neigh node */
	u8 tq_recv[BATADV_TQ_GLOBAL_WINDOW_SIZE];

	/** @tq_index: ring buffer index */
	u8 tq_index;

	/**
	 * @tq_avg: averaged tq of all tq values in the ring buffer (tq_recv)
	 */
	u8 tq_avg;

	/**
	 * @real_bits: bitfield containing the number of OGMs received from this
	 *  neigh node (relative to orig_node->last_real_seqno)
	 */
	DECLARE_BITMAP(real_bits, BATADV_TQ_LOCAL_WINDOW_SIZE);

	/** @real_packet_count: counted result of real_bits */
	u8 real_packet_count;
पूर्ण;

/**
 * काष्ठा batadv_neigh_अगरinfo_bat_v - neighbor inक्रमmation per outgoing
 *  पूर्णांकerface क्रम B.A.T.M.A.N. V
 */
काष्ठा batadv_neigh_अगरinfo_bat_v अणु
	/**
	 * @throughput: last throughput metric received from originator via this
	 *  neigh
	 */
	u32 throughput;

	/** @last_seqno: last sequence number known क्रम this neighbor */
	u32 last_seqno;
पूर्ण;

/**
 * काष्ठा batadv_neigh_अगरinfo - neighbor inक्रमmation per outgoing पूर्णांकerface
 */
काष्ठा batadv_neigh_अगरinfo अणु
	/** @list: list node क्रम &batadv_neigh_node.अगरinfo_list */
	काष्ठा hlist_node list;

	/** @अगर_outgoing: poपूर्णांकer to outgoing hard-पूर्णांकerface */
	काष्ठा batadv_hard_अगरace *अगर_outgoing;

	/** @bat_iv: B.A.T.M.A.N. IV निजी काष्ठाure */
	काष्ठा batadv_neigh_अगरinfo_bat_iv bat_iv;

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	/** @bat_v: B.A.T.M.A.N. V निजी data */
	काष्ठा batadv_neigh_अगरinfo_bat_v bat_v;
#पूर्ण_अगर

	/** @last_ttl: last received ttl from this neigh node */
	u8 last_ttl;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in a RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA

/**
 * काष्ठा batadv_bcast_duplist_entry - काष्ठाure क्रम LAN broadcast suppression
 */
काष्ठा batadv_bcast_duplist_entry अणु
	/** @orig: mac address of orig node originating the broadcast */
	u8 orig[ETH_ALEN];

	/** @crc: crc32 checksum of broadcast payload */
	__be32 crc;

	/** @entryसमय: समय when the broadcast packet was received */
	अचिन्हित दीर्घ entryसमय;
पूर्ण;
#पूर्ण_अगर

/**
 * क्रमागत batadv_counters - indices क्रम traffic counters
 */
क्रमागत batadv_counters अणु
	/** @BATADV_CNT_TX: transmitted payload traffic packet counter */
	BATADV_CNT_TX,

	/** @BATADV_CNT_TX_BYTES: transmitted payload traffic bytes counter */
	BATADV_CNT_TX_BYTES,

	/**
	 * @BATADV_CNT_TX_DROPPED: dropped transmission payload traffic packet
	 *  counter
	 */
	BATADV_CNT_TX_DROPPED,

	/** @BATADV_CNT_RX: received payload traffic packet counter */
	BATADV_CNT_RX,

	/** @BATADV_CNT_RX_BYTES: received payload traffic bytes counter */
	BATADV_CNT_RX_BYTES,

	/** @BATADV_CNT_FORWARD: क्रमwarded payload traffic packet counter */
	BATADV_CNT_FORWARD,

	/**
	 * @BATADV_CNT_FORWARD_BYTES: क्रमwarded payload traffic bytes counter
	 */
	BATADV_CNT_FORWARD_BYTES,

	/**
	 * @BATADV_CNT_MGMT_TX: transmitted routing protocol traffic packet
	 *  counter
	 */
	BATADV_CNT_MGMT_TX,

	/**
	 * @BATADV_CNT_MGMT_TX_BYTES: transmitted routing protocol traffic bytes
	 *  counter
	 */
	BATADV_CNT_MGMT_TX_BYTES,

	/**
	 * @BATADV_CNT_MGMT_RX: received routing protocol traffic packet counter
	 */
	BATADV_CNT_MGMT_RX,

	/**
	 * @BATADV_CNT_MGMT_RX_BYTES: received routing protocol traffic bytes
	 *  counter
	 */
	BATADV_CNT_MGMT_RX_BYTES,

	/** @BATADV_CNT_FRAG_TX: transmitted fragment traffic packet counter */
	BATADV_CNT_FRAG_TX,

	/**
	 * @BATADV_CNT_FRAG_TX_BYTES: transmitted fragment traffic bytes counter
	 */
	BATADV_CNT_FRAG_TX_BYTES,

	/** @BATADV_CNT_FRAG_RX: received fragment traffic packet counter */
	BATADV_CNT_FRAG_RX,

	/**
	 * @BATADV_CNT_FRAG_RX_BYTES: received fragment traffic bytes counter
	 */
	BATADV_CNT_FRAG_RX_BYTES,

	/** @BATADV_CNT_FRAG_FWD: क्रमwarded fragment traffic packet counter */
	BATADV_CNT_FRAG_FWD,

	/**
	 * @BATADV_CNT_FRAG_FWD_BYTES: क्रमwarded fragment traffic bytes counter
	 */
	BATADV_CNT_FRAG_FWD_BYTES,

	/**
	 * @BATADV_CNT_TT_REQUEST_TX: transmitted tt req traffic packet counter
	 */
	BATADV_CNT_TT_REQUEST_TX,

	/** @BATADV_CNT_TT_REQUEST_RX: received tt req traffic packet counter */
	BATADV_CNT_TT_REQUEST_RX,

	/**
	 * @BATADV_CNT_TT_RESPONSE_TX: transmitted tt resp traffic packet
	 *  counter
	 */
	BATADV_CNT_TT_RESPONSE_TX,

	/**
	 * @BATADV_CNT_TT_RESPONSE_RX: received tt resp traffic packet counter
	 */
	BATADV_CNT_TT_RESPONSE_RX,

	/**
	 * @BATADV_CNT_TT_ROAM_ADV_TX: transmitted tt roam traffic packet
	 *  counter
	 */
	BATADV_CNT_TT_ROAM_ADV_TX,

	/**
	 * @BATADV_CNT_TT_ROAM_ADV_RX: received tt roam traffic packet counter
	 */
	BATADV_CNT_TT_ROAM_ADV_RX,

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	/**
	 * @BATADV_CNT_DAT_GET_TX: transmitted dht GET traffic packet counter
	 */
	BATADV_CNT_DAT_GET_TX,

	/** @BATADV_CNT_DAT_GET_RX: received dht GET traffic packet counter */
	BATADV_CNT_DAT_GET_RX,

	/**
	 * @BATADV_CNT_DAT_PUT_TX: transmitted dht PUT traffic packet counter
	 */
	BATADV_CNT_DAT_PUT_TX,

	/** @BATADV_CNT_DAT_PUT_RX: received dht PUT traffic packet counter */
	BATADV_CNT_DAT_PUT_RX,

	/**
	 * @BATADV_CNT_DAT_CACHED_REPLY_TX: transmitted dat cache reply traffic
	 *  packet counter
	 */
	BATADV_CNT_DAT_CACHED_REPLY_TX,
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_NC
	/**
	 * @BATADV_CNT_NC_CODE: transmitted nc-combined traffic packet counter
	 */
	BATADV_CNT_NC_CODE,

	/**
	 * @BATADV_CNT_NC_CODE_BYTES: transmitted nc-combined traffic bytes
	 *  counter
	 */
	BATADV_CNT_NC_CODE_BYTES,

	/**
	 * @BATADV_CNT_NC_RECODE: transmitted nc-recombined traffic packet
	 *  counter
	 */
	BATADV_CNT_NC_RECODE,

	/**
	 * @BATADV_CNT_NC_RECODE_BYTES: transmitted nc-recombined traffic bytes
	 *  counter
	 */
	BATADV_CNT_NC_RECODE_BYTES,

	/**
	 * @BATADV_CNT_NC_BUFFER: counter क्रम packets buffered क्रम later nc
	 *  decoding
	 */
	BATADV_CNT_NC_BUFFER,

	/**
	 * @BATADV_CNT_NC_DECODE: received and nc-decoded traffic packet counter
	 */
	BATADV_CNT_NC_DECODE,

	/**
	 * @BATADV_CNT_NC_DECODE_BYTES: received and nc-decoded traffic bytes
	 *  counter
	 */
	BATADV_CNT_NC_DECODE_BYTES,

	/**
	 * @BATADV_CNT_NC_DECODE_FAILED: received and decode-failed traffic
	 *  packet counter
	 */
	BATADV_CNT_NC_DECODE_FAILED,

	/**
	 * @BATADV_CNT_NC_SNIFFED: counter क्रम nc-decoded packets received in
	 *  promisc mode.
	 */
	BATADV_CNT_NC_SNIFFED,
#पूर्ण_अगर

	/** @BATADV_CNT_NUM: number of traffic counters */
	BATADV_CNT_NUM,
पूर्ण;

/**
 * काष्ठा batadv_priv_tt - per mesh पूर्णांकerface translation table data
 */
काष्ठा batadv_priv_tt अणु
	/** @vn: translation table version number */
	atomic_t vn;

	/**
	 * @ogm_append_cnt: counter of number of OGMs containing the local tt
	 *  dअगरf
	 */
	atomic_t ogm_append_cnt;

	/** @local_changes: changes रेजिस्टरed in an originator पूर्णांकerval */
	atomic_t local_changes;

	/**
	 * @changes_list: tracks tt local changes within an originator पूर्णांकerval
	 */
	काष्ठा list_head changes_list;

	/** @local_hash: local translation table hash table */
	काष्ठा batadv_hashtable *local_hash;

	/** @global_hash: global translation table hash table */
	काष्ठा batadv_hashtable *global_hash;

	/** @req_list: list of pending & unanswered tt_requests */
	काष्ठा hlist_head req_list;

	/**
	 * @roam_list: list of the last roaming events of each client limiting
	 *  the number of roaming events to aव्योम route flapping
	 */
	काष्ठा list_head roam_list;

	/** @changes_list_lock: lock protecting changes_list */
	spinlock_t changes_list_lock;

	/** @req_list_lock: lock protecting req_list */
	spinlock_t req_list_lock;

	/** @roam_list_lock: lock protecting roam_list */
	spinlock_t roam_list_lock;

	/** @last_changeset: last tt changeset this host has generated */
	अचिन्हित अक्षर *last_changeset;

	/**
	 * @last_changeset_len: length of last tt changeset this host has
	 *  generated
	 */
	s16 last_changeset_len;

	/**
	 * @last_changeset_lock: lock protecting last_changeset &
	 *  last_changeset_len
	 */
	spinlock_t last_changeset_lock;

	/**
	 * @commit_lock: prevents from executing a local TT commit जबतक पढ़ोing
	 *  the local table. The local TT commit is made up of two operations
	 *  (data काष्ठाure update and metadata -CRC/TTVN- recalculation) and
	 *  they have to be executed atomically in order to aव्योम another thपढ़ो
	 *  to पढ़ो the table/metadata between those.
	 */
	spinlock_t commit_lock;

	/** @work: work queue callback item क्रम translation table purging */
	काष्ठा delayed_work work;
पूर्ण;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA

/**
 * काष्ठा batadv_priv_bla - per mesh पूर्णांकerface bridge loop aव्योमance data
 */
काष्ठा batadv_priv_bla अणु
	/** @num_requests: number of bla requests in flight */
	atomic_t num_requests;

	/**
	 * @claim_hash: hash table containing mesh nodes this host has claimed
	 */
	काष्ठा batadv_hashtable *claim_hash;

	/**
	 * @backbone_hash: hash table containing all detected backbone gateways
	 */
	काष्ठा batadv_hashtable *backbone_hash;

	/** @loopdetect_addr: MAC address used क्रम own loopdetection frames */
	u8 loopdetect_addr[ETH_ALEN];

	/**
	 * @loopdetect_lastसमय: समय when the loopdetection frames were sent
	 */
	अचिन्हित दीर्घ loopdetect_lastसमय;

	/**
	 * @loopdetect_next: how many periods to रुको क्रम the next loopdetect
	 *  process
	 */
	atomic_t loopdetect_next;

	/**
	 * @bcast_duplist: recently received broadcast packets array (क्रम
	 *  broadcast duplicate suppression)
	 */
	काष्ठा batadv_bcast_duplist_entry bcast_duplist[BATADV_DUPLIST_SIZE];

	/**
	 * @bcast_duplist_curr: index of last broadcast packet added to
	 *  bcast_duplist
	 */
	पूर्णांक bcast_duplist_curr;

	/**
	 * @bcast_duplist_lock: lock protecting bcast_duplist &
	 *  bcast_duplist_curr
	 */
	spinlock_t bcast_duplist_lock;

	/** @claim_dest: local claim data (e.g. claim group) */
	काष्ठा batadv_bla_claim_dst claim_dest;

	/** @work: work queue callback item क्रम cleanups & bla announcements */
	काष्ठा delayed_work work;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG

/**
 * काष्ठा batadv_priv_debug_log - debug logging data
 */
काष्ठा batadv_priv_debug_log अणु
	/** @log_buff: buffer holding the logs (ring buffer) */
	अक्षर log_buff[BATADV_LOG_BUF_LEN];

	/** @log_start: index of next अक्षरacter to पढ़ो */
	अचिन्हित दीर्घ log_start;

	/** @log_end: index of next अक्षरacter to ग_लिखो */
	अचिन्हित दीर्घ log_end;

	/** @lock: lock protecting log_buff, log_start & log_end */
	spinlock_t lock;

	/** @queue_रुको: log पढ़ोer's रुको queue */
	रुको_queue_head_t queue_रुको;
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा batadv_priv_gw - per mesh पूर्णांकerface gateway data
 */
काष्ठा batadv_priv_gw अणु
	/** @gateway_list: list of available gateway nodes */
	काष्ठा hlist_head gateway_list;

	/** @list_lock: lock protecting gateway_list, curr_gw, generation */
	spinlock_t list_lock;

	/** @curr_gw: poपूर्णांकer to currently selected gateway node */
	काष्ठा batadv_gw_node __rcu *curr_gw;

	/** @generation: current (generation) sequence number */
	अचिन्हित पूर्णांक generation;

	/**
	 * @mode: gateway operation: off, client or server (see batadv_gw_modes)
	 */
	atomic_t mode;

	/** @sel_class: gateway selection class (applies अगर gw_mode client) */
	atomic_t sel_class;

	/**
	 * @bandwidth_करोwn: advertised uplink करोwnload bandwidth (अगर gw_mode
	 *  server)
	 */
	atomic_t bandwidth_करोwn;

	/**
	 * @bandwidth_up: advertised uplink upload bandwidth (अगर gw_mode server)
	 */
	atomic_t bandwidth_up;

	/** @reselect: bool indicating a gateway re-selection is in progress */
	atomic_t reselect;
पूर्ण;

/**
 * काष्ठा batadv_priv_tvlv - per mesh पूर्णांकerface tvlv data
 */
काष्ठा batadv_priv_tvlv अणु
	/**
	 * @container_list: list of रेजिस्टरed tvlv containers to be sent with
	 *  each OGM
	 */
	काष्ठा hlist_head container_list;

	/** @handler_list: list of the various tvlv content handlers */
	काष्ठा hlist_head handler_list;

	/** @container_list_lock: protects tvlv container list access */
	spinlock_t container_list_lock;

	/** @handler_list_lock: protects handler list access */
	spinlock_t handler_list_lock;
पूर्ण;

#अगर_घोषित CONFIG_BATMAN_ADV_DAT

/**
 * काष्ठा batadv_priv_dat - per mesh पूर्णांकerface DAT निजी data
 */
काष्ठा batadv_priv_dat अणु
	/** @addr: node DAT address */
	batadv_dat_addr_t addr;

	/** @hash: hashtable representing the local ARP cache */
	काष्ठा batadv_hashtable *hash;

	/** @work: work queue callback item क्रम cache purging */
	काष्ठा delayed_work work;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
/**
 * काष्ठा batadv_mcast_querier_state - IGMP/MLD querier state when bridged
 */
काष्ठा batadv_mcast_querier_state अणु
	/** @exists: whether a querier exists in the mesh */
	अचिन्हित अक्षर exists:1;

	/**
	 * @shaकरोwing: अगर a querier exists, whether it is potentially shaकरोwing
	 *  multicast listeners (i.e. querier is behind our own bridge segment)
	 */
	अचिन्हित अक्षर shaकरोwing:1;
पूर्ण;

/**
 * काष्ठा batadv_mcast_mla_flags - flags क्रम the querier, bridge and tvlv state
 */
काष्ठा batadv_mcast_mla_flags अणु
	/** @querier_ipv4: the current state of an IGMP querier in the mesh */
	काष्ठा batadv_mcast_querier_state querier_ipv4;

	/** @querier_ipv6: the current state of an MLD querier in the mesh */
	काष्ठा batadv_mcast_querier_state querier_ipv6;

	/** @enabled: whether the multicast tvlv is currently enabled */
	अचिन्हित अक्षर enabled:1;

	/** @bridged: whether the soft पूर्णांकerface has a bridge on top */
	अचिन्हित अक्षर bridged:1;

	/** @tvlv_flags: the flags we have last sent in our mcast tvlv */
	u8 tvlv_flags;
पूर्ण;

/**
 * काष्ठा batadv_priv_mcast - per mesh पूर्णांकerface mcast data
 */
काष्ठा batadv_priv_mcast अणु
	/**
	 * @mla_list: list of multicast addresses we are currently announcing
	 *  via TT
	 */
	काष्ठा hlist_head mla_list; /* see __batadv_mcast_mla_update() */

	/**
	 * @want_all_unsnoopables_list: a list of orig_nodes wanting all
	 *  unsnoopable multicast traffic
	 */
	काष्ठा hlist_head want_all_unsnoopables_list;

	/**
	 * @want_all_ipv4_list: a list of orig_nodes wanting all IPv4 multicast
	 *  traffic
	 */
	काष्ठा hlist_head want_all_ipv4_list;

	/**
	 * @want_all_ipv6_list: a list of orig_nodes wanting all IPv6 multicast
	 *  traffic
	 */
	काष्ठा hlist_head want_all_ipv6_list;

	/**
	 * @want_all_rtr4_list: a list of orig_nodes wanting all routable IPv4
	 *  multicast traffic
	 */
	काष्ठा hlist_head want_all_rtr4_list;

	/**
	 * @want_all_rtr6_list: a list of orig_nodes wanting all routable IPv6
	 *  multicast traffic
	 */
	काष्ठा hlist_head want_all_rtr6_list;

	/**
	 * @mla_flags: flags क्रम the querier, bridge and tvlv state
	 */
	काष्ठा batadv_mcast_mla_flags mla_flags;

	/**
	 * @mla_lock: a lock protecting mla_list and mla_flags
	 */
	spinlock_t mla_lock;

	/**
	 * @num_want_all_unsnoopables: number of nodes wanting unsnoopable IP
	 *  traffic
	 */
	atomic_t num_want_all_unsnoopables;

	/** @num_want_all_ipv4: counter क्रम items in want_all_ipv4_list */
	atomic_t num_want_all_ipv4;

	/** @num_want_all_ipv6: counter क्रम items in want_all_ipv6_list */
	atomic_t num_want_all_ipv6;

	/** @num_want_all_rtr4: counter क्रम items in want_all_rtr4_list */
	atomic_t num_want_all_rtr4;

	/** @num_want_all_rtr6: counter क्रम items in want_all_rtr6_list */
	atomic_t num_want_all_rtr6;

	/**
	 * @want_lists_lock: lock क्रम protecting modअगरications to mcasts
	 *  want_all_अणुunsnoopables,ipv4,ipv6पूर्ण_list (traversals are rcu-locked)
	 */
	spinlock_t want_lists_lock;

	/** @work: work queue callback item क्रम multicast TT and TVLV updates */
	काष्ठा delayed_work work;
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा batadv_priv_nc - per mesh पूर्णांकerface network coding निजी data
 */
काष्ठा batadv_priv_nc अणु
	/** @work: work queue callback item क्रम cleanup */
	काष्ठा delayed_work work;

	/**
	 * @min_tq: only consider neighbors क्रम encoding अगर neigh_tq > min_tq
	 */
	u8 min_tq;

	/**
	 * @max_fwd_delay: maximum packet क्रमward delay to allow coding of
	 *  packets
	 */
	u32 max_fwd_delay;

	/**
	 * @max_buffer_समय: buffer समय क्रम snअगरfed packets used to decoding
	 */
	u32 max_buffer_समय;

	/**
	 * @बारtamp_fwd_flush: बारtamp of last क्रमward packet queue flush
	 */
	अचिन्हित दीर्घ बारtamp_fwd_flush;

	/**
	 * @बारtamp_snअगरfed_purge: बारtamp of last snअगरfed packet queue
	 *  purge
	 */
	अचिन्हित दीर्घ बारtamp_snअगरfed_purge;

	/**
	 * @coding_hash: Hash table used to buffer skbs जबतक रुकोing क्रम
	 *  another incoming skb to code it with. Skbs are added to the buffer
	 *  just beक्रमe being क्रमwarded in routing.c
	 */
	काष्ठा batadv_hashtable *coding_hash;

	/**
	 * @decoding_hash: Hash table used to buffer skbs that might be needed
	 *  to decode a received coded skb. The buffer is used क्रम 1) skbs
	 *  arriving on the soft-पूर्णांकerface; 2) skbs overheard on the
	 *  hard-पूर्णांकerface; and 3) skbs क्रमwarded by baपंचांगan-adv.
	 */
	काष्ठा batadv_hashtable *decoding_hash;
पूर्ण;

/**
 * काष्ठा batadv_tp_unacked - unacked packet meta-inक्रमmation
 *
 * This काष्ठा is supposed to represent a buffer unacked packet. However, since
 * the purpose of the TP meter is to count the traffic only, there is no need to
 * store the entire sk_buff, the starting offset and the length are enough
 */
काष्ठा batadv_tp_unacked अणु
	/** @seqno: seqno of the unacked packet */
	u32 seqno;

	/** @len: length of the packet */
	u16 len;

	/** @list: list node क्रम &batadv_tp_vars.unacked_list */
	काष्ठा list_head list;
पूर्ण;

/**
 * क्रमागत batadv_tp_meter_role - Modus in tp meter session
 */
क्रमागत batadv_tp_meter_role अणु
	/** @BATADV_TP_RECEIVER: Initialized as receiver */
	BATADV_TP_RECEIVER,

	/** @BATADV_TP_SENDER: Initialized as sender */
	BATADV_TP_SENDER
पूर्ण;

/**
 * काष्ठा batadv_tp_vars - tp meter निजी variables per session
 */
काष्ठा batadv_tp_vars अणु
	/** @list: list node क्रम &bat_priv.tp_list */
	काष्ठा hlist_node list;

	/** @समयr: समयr क्रम ack (receiver) and retry (sender) */
	काष्ठा समयr_list समयr;

	/** @bat_priv: poपूर्णांकer to the mesh object */
	काष्ठा batadv_priv *bat_priv;

	/** @start_समय: start समय in jअगरfies */
	अचिन्हित दीर्घ start_समय;

	/** @other_end: mac address of remote */
	u8 other_end[ETH_ALEN];

	/** @role: receiver/sender modi */
	क्रमागत batadv_tp_meter_role role;

	/** @sending: sending binary semaphore: 1 अगर sending, 0 is not */
	atomic_t sending;

	/** @reason: reason क्रम a stopped session */
	क्रमागत batadv_tp_meter_reason reason;

	/** @finish_work: work item क्रम the finishing procedure */
	काष्ठा delayed_work finish_work;

	/** @test_length: test length in milliseconds */
	u32 test_length;

	/** @session: TP session identअगरier */
	u8 session[2];

	/** @icmp_uid: local ICMP "socket" index */
	u8 icmp_uid;

	/* sender variables */

	/** @dec_cwnd: decimal part of the cwnd used during linear growth */
	u16 dec_cwnd;

	/** @cwnd: current size of the congestion winकरोw */
	u32 cwnd;

	/** @cwnd_lock: lock करो protect @cwnd & @dec_cwnd */
	spinlock_t cwnd_lock;

	/**
	 * @ss_threshold: Slow Start threshold. Once cwnd exceeds this value the
	 *  connection चयनes to the Congestion Aव्योमance state
	 */
	u32 ss_threshold;

	/** @last_acked: last acked byte */
	atomic_t last_acked;

	/** @last_sent: last sent byte, not yet acked */
	u32 last_sent;

	/** @tot_sent: amount of data sent/ACKed so far */
	atomic64_t tot_sent;

	/** @dup_acks: duplicate ACKs counter */
	atomic_t dup_acks;

	/** @fast_recovery: true अगर in Fast Recovery mode */
	अचिन्हित अक्षर fast_recovery:1;

	/** @recover: last sent seqno when entering Fast Recovery */
	u32 recover;

	/** @rto: sender समयout */
	u32 rto;

	/** @srtt: smoothed RTT scaled by 2^3 */
	u32 srtt;

	/** @rttvar: RTT variation scaled by 2^2 */
	u32 rttvar;

	/**
	 * @more_bytes: रुकोing queue anchor when रुकोing क्रम more ack/retry
	 *  समयout
	 */
	रुको_queue_head_t more_bytes;

	/** @preअक्रमom_offset: offset inside the preअक्रमom buffer */
	u32 preअक्रमom_offset;

	/** @preअक्रमom_lock: spinlock protecting access to preअक्रमom_offset */
	spinlock_t preअक्रमom_lock;

	/* receiver variables */

	/** @last_recv: last in-order received packet */
	u32 last_recv;

	/** @unacked_list: list of unacked packets (meta-info only) */
	काष्ठा list_head unacked_list;

	/** @unacked_lock: protect unacked_list */
	spinlock_t unacked_lock;

	/** @last_recv_समय: समय (jअगरfies) a msg was received */
	अचिन्हित दीर्घ last_recv_समय;

	/** @refcount: number of context where the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_softअगर_vlan - per VLAN attributes set
 */
काष्ठा batadv_softअगर_vlan अणु
	/** @bat_priv: poपूर्णांकer to the mesh object */
	काष्ठा batadv_priv *bat_priv;

	/** @vid: VLAN identअगरier */
	अचिन्हित लघु vid;

	/** @ap_isolation: AP isolation state */
	atomic_t ap_isolation;		/* boolean */

	/** @tt: TT निजी attributes (VLAN specअगरic) */
	काष्ठा batadv_vlan_tt tt;

	/** @list: list node क्रम &bat_priv.softअगर_vlan_list */
	काष्ठा hlist_node list;

	/**
	 * @refcount: number of context where this object is currently in use
	 */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in a RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_priv_bat_v - B.A.T.M.A.N. V per soft-पूर्णांकerface निजी data
 */
काष्ठा batadv_priv_bat_v अणु
	/** @ogm_buff: buffer holding the OGM packet */
	अचिन्हित अक्षर *ogm_buff;

	/** @ogm_buff_len: length of the OGM packet buffer */
	पूर्णांक ogm_buff_len;

	/** @ogm_seqno: OGM sequence number - used to identअगरy each OGM */
	atomic_t ogm_seqno;

	/** @ogm_buff_mutex: lock protecting ogm_buff and ogm_buff_len */
	काष्ठा mutex ogm_buff_mutex;

	/** @ogm_wq: workqueue used to schedule OGM transmissions */
	काष्ठा delayed_work ogm_wq;
पूर्ण;

/**
 * काष्ठा batadv_priv - per mesh पूर्णांकerface data
 */
काष्ठा batadv_priv अणु
	/**
	 * @mesh_state: current status of the mesh
	 *  (inactive/active/deactivating)
	 */
	atomic_t mesh_state;

	/** @soft_अगरace: net device which holds this काष्ठा as निजी data */
	काष्ठा net_device *soft_अगरace;

	/**
	 * @bat_counters: mesh पूर्णांकernal traffic statistic counters (see
	 *  batadv_counters)
	 */
	u64 __percpu *bat_counters; /* Per cpu counters */

	/**
	 * @aggregated_ogms: bool indicating whether OGM aggregation is enabled
	 */
	atomic_t aggregated_ogms;

	/** @bonding: bool indicating whether traffic bonding is enabled */
	atomic_t bonding;

	/**
	 * @fragmentation: bool indicating whether traffic fragmentation is
	 *  enabled
	 */
	atomic_t fragmentation;

	/**
	 * @packet_size_max: max packet size that can be transmitted via
	 *  multiple fragmented skbs or a single frame अगर fragmentation is
	 *  disabled
	 */
	atomic_t packet_size_max;

	/**
	 * @frag_seqno: incremental counter to identअगरy chains of egress
	 *  fragments
	 */
	atomic_t frag_seqno;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	/**
	 * @bridge_loop_aव्योमance: bool indicating whether bridge loop
	 *  aव्योमance is enabled
	 */
	atomic_t bridge_loop_aव्योमance;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	/**
	 * @distributed_arp_table: bool indicating whether distributed ARP table
	 *  is enabled
	 */
	atomic_t distributed_arp_table;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	/**
	 * @multicast_mode: Enable or disable multicast optimizations on this
	 *  node's sender/originating side
	 */
	atomic_t multicast_mode;

	/**
	 * @multicast_fanout: Maximum number of packet copies to generate क्रम a
	 *  multicast-to-unicast conversion
	 */
	atomic_t multicast_fanout;
#पूर्ण_अगर

	/** @orig_पूर्णांकerval: OGM broadcast पूर्णांकerval in milliseconds */
	atomic_t orig_पूर्णांकerval;

	/**
	 * @hop_penalty: penalty which will be applied to an OGM's tq-field on
	 *  every hop
	 */
	atomic_t hop_penalty;

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG
	/** @log_level: configured log level (see batadv_dbg_level) */
	atomic_t log_level;
#पूर्ण_अगर

	/**
	 * @isolation_mark: the skb->mark value used to match packets क्रम AP
	 *  isolation
	 */
	u32 isolation_mark;

	/**
	 * @isolation_mark_mask: biपंचांगask identअगरying the bits in skb->mark to be
	 *  used क्रम the isolation mark
	 */
	u32 isolation_mark_mask;

	/** @bcast_seqno: last sent broadcast packet sequence number */
	atomic_t bcast_seqno;

	/**
	 * @bcast_queue_left: number of reमुख्यing buffered broadcast packet
	 *  slots
	 */
	atomic_t bcast_queue_left;

	/** @baपंचांगan_queue_left: number of reमुख्यing OGM packet slots */
	atomic_t baपंचांगan_queue_left;

	/** @क्रमw_bat_list: list of aggregated OGMs that will be क्रमwarded */
	काष्ठा hlist_head क्रमw_bat_list;

	/**
	 * @क्रमw_bcast_list: list of broadcast packets that will be
	 *  rebroadcasted
	 */
	काष्ठा hlist_head क्रमw_bcast_list;

	/** @tp_list: list of tp sessions */
	काष्ठा hlist_head tp_list;

	/** @orig_hash: hash table containing mesh participants (orig nodes) */
	काष्ठा batadv_hashtable *orig_hash;

	/** @क्रमw_bat_list_lock: lock protecting क्रमw_bat_list */
	spinlock_t क्रमw_bat_list_lock;

	/** @क्रमw_bcast_list_lock: lock protecting क्रमw_bcast_list */
	spinlock_t क्रमw_bcast_list_lock;

	/** @tp_list_lock: spinlock protecting @tp_list */
	spinlock_t tp_list_lock;

	/** @tp_num: number of currently active tp sessions */
	atomic_t tp_num;

	/** @orig_work: work queue callback item क्रम orig node purging */
	काष्ठा delayed_work orig_work;

	/**
	 * @primary_अगर: one of the hard-पूर्णांकerfaces asचिन्हित to this mesh
	 *  पूर्णांकerface becomes the primary पूर्णांकerface
	 */
	काष्ठा batadv_hard_अगरace __rcu *primary_अगर;  /* rcu रक्षित poपूर्णांकer */

	/** @algo_ops: routing algorithm used by this mesh पूर्णांकerface */
	काष्ठा batadv_algo_ops *algo_ops;

	/**
	 * @softअगर_vlan_list: a list of softअगर_vlan काष्ठाs, one per VLAN
	 *  created on top of the mesh पूर्णांकerface represented by this object
	 */
	काष्ठा hlist_head softअगर_vlan_list;

	/** @softअगर_vlan_list_lock: lock protecting softअगर_vlan_list */
	spinlock_t softअगर_vlan_list_lock;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	/** @bla: bridge loop aव्योमance data */
	काष्ठा batadv_priv_bla bla;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG
	/** @debug_log: holding debug logging relevant data */
	काष्ठा batadv_priv_debug_log *debug_log;
#पूर्ण_अगर

	/** @gw: gateway data */
	काष्ठा batadv_priv_gw gw;

	/** @tt: translation table data */
	काष्ठा batadv_priv_tt tt;

	/** @tvlv: type-version-length-value data */
	काष्ठा batadv_priv_tvlv tvlv;

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	/** @dat: distributed arp table data */
	काष्ठा batadv_priv_dat dat;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	/** @mcast: multicast data */
	काष्ठा batadv_priv_mcast mcast;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BATMAN_ADV_NC
	/**
	 * @network_coding: bool indicating whether network coding is enabled
	 */
	atomic_t network_coding;

	/** @nc: network coding data */
	काष्ठा batadv_priv_nc nc;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_NC */

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	/** @bat_v: B.A.T.M.A.N. V per soft-पूर्णांकerface निजी data */
	काष्ठा batadv_priv_bat_v bat_v;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा batadv_socket_client - layer2 icmp socket client data
 */
काष्ठा batadv_socket_client अणु
	/**
	 * @queue_list: packet queue क्रम packets destined क्रम this socket client
	 */
	काष्ठा list_head queue_list;

	/** @queue_len: number of packets in the packet queue (queue_list) */
	अचिन्हित पूर्णांक queue_len;

	/** @index: socket client's index in the batadv_socket_client_hash */
	अचिन्हित अक्षर index;

	/** @lock: lock protecting queue_list, queue_len & index */
	spinlock_t lock;

	/** @queue_रुको: socket client's रुको queue */
	रुको_queue_head_t queue_रुको;

	/** @bat_priv: poपूर्णांकer to soft_अगरace this client beदीर्घs to */
	काष्ठा batadv_priv *bat_priv;
पूर्ण;

/**
 * काष्ठा batadv_socket_packet - layer2 icmp packet क्रम socket client
 */
काष्ठा batadv_socket_packet अणु
	/** @list: list node क्रम &batadv_socket_client.queue_list */
	काष्ठा list_head list;

	/** @icmp_len: size of the layer2 icmp packet */
	माप_प्रकार icmp_len;

	/** @icmp_packet: layer2 icmp packet */
	u8 icmp_packet[BATADV_ICMP_MAX_PACKET_SIZE];
पूर्ण;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA

/**
 * काष्ठा batadv_bla_backbone_gw - baपंचांगan-adv gateway bridged पूर्णांकo the LAN
 */
काष्ठा batadv_bla_backbone_gw अणु
	/**
	 * @orig: originator address of backbone node (mac address of primary
	 *  अगरace)
	 */
	u8 orig[ETH_ALEN];

	/** @vid: vlan id this gateway was detected on */
	अचिन्हित लघु vid;

	/** @hash_entry: hlist node क्रम &batadv_priv_bla.backbone_hash */
	काष्ठा hlist_node hash_entry;

	/** @bat_priv: poपूर्णांकer to soft_अगरace this backbone gateway beदीर्घs to */
	काष्ठा batadv_priv *bat_priv;

	/** @lastसमय: last समय we heard of this backbone gw */
	अचिन्हित दीर्घ lastसमय;

	/**
	 * @रुको_periods: grace समय क्रम bridge क्रमward delays and bla group
	 *  क्रमming at bootup phase - no bcast traffic is क्रमmwared until it has
	 *  elapsed
	 */
	atomic_t रुको_periods;

	/**
	 * @request_sent: अगर this bool is set to true we are out of sync with
	 *  this backbone gateway - no bcast traffic is क्रमmwared until the
	 *  situation was resolved
	 */
	atomic_t request_sent;

	/** @crc: crc16 checksum over all claims */
	u16 crc;

	/** @crc_lock: lock protecting crc */
	spinlock_t crc_lock;

	/** @report_work: work काष्ठा क्रम reporting detected loops */
	काष्ठा work_काष्ठा report_work;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_bla_claim - claimed non-mesh client काष्ठाure
 */
काष्ठा batadv_bla_claim अणु
	/** @addr: mac address of claimed non-mesh client */
	u8 addr[ETH_ALEN];

	/** @vid: vlan id this client was detected on */
	अचिन्हित लघु vid;

	/** @backbone_gw: poपूर्णांकer to backbone gw claiming this client */
	काष्ठा batadv_bla_backbone_gw *backbone_gw;

	/** @backbone_lock: lock protecting backbone_gw poपूर्णांकer */
	spinlock_t backbone_lock;

	/** @lastसमय: last समय we heard of claim (locals only) */
	अचिन्हित दीर्घ lastसमय;

	/** @hash_entry: hlist node क्रम &batadv_priv_bla.claim_hash */
	काष्ठा hlist_node hash_entry;

	/** @refcount: number of contexts the object is used */
	काष्ठा rcu_head rcu;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा kref refcount;
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा batadv_tt_common_entry - tt local & tt global common data
 */
काष्ठा batadv_tt_common_entry अणु
	/** @addr: mac address of non-mesh client */
	u8 addr[ETH_ALEN];

	/** @vid: VLAN identअगरier */
	अचिन्हित लघु vid;

	/**
	 * @hash_entry: hlist node क्रम &batadv_priv_tt.local_hash or क्रम
	 *  &batadv_priv_tt.global_hash
	 */
	काष्ठा hlist_node hash_entry;

	/** @flags: various state handling flags (see batadv_tt_client_flags) */
	u16 flags;

	/** @added_at: बारtamp used क्रम purging stale tt common entries */
	अचिन्हित दीर्घ added_at;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_tt_local_entry - translation table local entry data
 */
काष्ठा batadv_tt_local_entry अणु
	/** @common: general translation table data */
	काष्ठा batadv_tt_common_entry common;

	/** @last_seen: बारtamp used क्रम purging stale tt local entries */
	अचिन्हित दीर्घ last_seen;

	/** @vlan: soft-पूर्णांकerface vlan of the entry */
	काष्ठा batadv_softअगर_vlan *vlan;
पूर्ण;

/**
 * काष्ठा batadv_tt_global_entry - translation table global entry data
 */
काष्ठा batadv_tt_global_entry अणु
	/** @common: general translation table data */
	काष्ठा batadv_tt_common_entry common;

	/** @orig_list: list of orig nodes announcing this non-mesh client */
	काष्ठा hlist_head orig_list;

	/** @orig_list_count: number of items in the orig_list */
	atomic_t orig_list_count;

	/** @list_lock: lock protecting orig_list */
	spinlock_t list_lock;

	/** @roam_at: समय at which TT_GLOBAL_ROAM was set */
	अचिन्हित दीर्घ roam_at;
पूर्ण;

/**
 * काष्ठा batadv_tt_orig_list_entry - orig node announcing a non-mesh client
 */
काष्ठा batadv_tt_orig_list_entry अणु
	/** @orig_node: poपूर्णांकer to orig node announcing this non-mesh client */
	काष्ठा batadv_orig_node *orig_node;

	/**
	 * @ttvn: translation table version number which added the non-mesh
	 *  client
	 */
	u8 ttvn;

	/** @flags: per orig entry TT sync flags */
	u8 flags;

	/** @list: list node क्रम &batadv_tt_global_entry.orig_list */
	काष्ठा hlist_node list;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_tt_change_node - काष्ठाure क्रम tt changes occurred
 */
काष्ठा batadv_tt_change_node अणु
	/** @list: list node क्रम &batadv_priv_tt.changes_list */
	काष्ठा list_head list;

	/** @change: holds the actual translation table dअगरf data */
	काष्ठा batadv_tvlv_tt_change change;
पूर्ण;

/**
 * काष्ठा batadv_tt_req_node - data to keep track of the tt requests in flight
 */
काष्ठा batadv_tt_req_node अणु
	/**
	 * @addr: mac address of the originator this request was sent to
	 */
	u8 addr[ETH_ALEN];

	/** @issued_at: बारtamp used क्रम purging stale tt requests */
	अचिन्हित दीर्घ issued_at;

	/** @refcount: number of contexts the object is used by */
	काष्ठा kref refcount;

	/** @list: list node क्रम &batadv_priv_tt.req_list */
	काष्ठा hlist_node list;
पूर्ण;

/**
 * काष्ठा batadv_tt_roam_node - roaming client data
 */
काष्ठा batadv_tt_roam_node अणु
	/** @addr: mac address of the client in the roaming phase */
	u8 addr[ETH_ALEN];

	/**
	 * @counter: number of allowed roaming events per client within a single
	 * OGM पूर्णांकerval (changes are committed with each OGM)
	 */
	atomic_t counter;

	/**
	 * @first_समय: बारtamp used क्रम purging stale roaming node entries
	 */
	अचिन्हित दीर्घ first_समय;

	/** @list: list node क्रम &batadv_priv_tt.roam_list */
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा batadv_nc_node - network coding node
 */
काष्ठा batadv_nc_node अणु
	/** @list: next and prev poपूर्णांकer क्रम the list handling */
	काष्ठा list_head list;

	/** @addr: the node's mac address */
	u8 addr[ETH_ALEN];

	/** @refcount: number of contexts the object is used by */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;

	/** @orig_node: poपूर्णांकer to corresponding orig node काष्ठा */
	काष्ठा batadv_orig_node *orig_node;

	/** @last_seen: बारtamp of last ogm received from this node */
	अचिन्हित दीर्घ last_seen;
पूर्ण;

/**
 * काष्ठा batadv_nc_path - network coding path
 */
काष्ठा batadv_nc_path अणु
	/** @hash_entry: next and prev poपूर्णांकer क्रम the list handling */
	काष्ठा hlist_node hash_entry;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;

	/** @refcount: number of contexts the object is used by */
	काष्ठा kref refcount;

	/** @packet_list: list of buffered packets क्रम this path */
	काष्ठा list_head packet_list;

	/** @packet_list_lock: access lock क्रम packet list */
	spinlock_t packet_list_lock;

	/** @next_hop: next hop (destination) of path */
	u8 next_hop[ETH_ALEN];

	/** @prev_hop: previous hop (source) of path */
	u8 prev_hop[ETH_ALEN];

	/** @last_valid: बारtamp क्रम last validation of path */
	अचिन्हित दीर्घ last_valid;
पूर्ण;

/**
 * काष्ठा batadv_nc_packet - network coding packet used when coding and
 *  decoding packets
 */
काष्ठा batadv_nc_packet अणु
	/** @list: next and prev poपूर्णांकer क्रम the list handling */
	काष्ठा list_head list;

	/** @packet_id: crc32 checksum of skb data */
	__be32 packet_id;

	/**
	 * @बारtamp: field containing the info when the packet was added to
	 *  path
	 */
	अचिन्हित दीर्घ बारtamp;

	/** @neigh_node: poपूर्णांकer to original next hop neighbor of skb */
	काष्ठा batadv_neigh_node *neigh_node;

	/** @skb: skb which can be encoded or used क्रम decoding */
	काष्ठा sk_buff *skb;

	/** @nc_path: poपूर्णांकer to path this nc packet is attached to */
	काष्ठा batadv_nc_path *nc_path;
पूर्ण;

/**
 * काष्ठा batadv_skb_cb - control buffer काष्ठाure used to store निजी data
 *  relevant to baपंचांगan-adv in the skb->cb buffer in skbs.
 */
काष्ठा batadv_skb_cb अणु
	/**
	 * @decoded: Marks a skb as decoded, which is checked when searching क्रम
	 *  coding opportunities in network-coding.c
	 */
	अचिन्हित अक्षर decoded:1;

	/** @num_bcasts: Counter क्रम broadcast packet retransmissions */
	अचिन्हित अक्षर num_bcasts;
पूर्ण;

/**
 * काष्ठा batadv_क्रमw_packet - काष्ठाure क्रम bcast packets to be sent/क्रमwarded
 */
काष्ठा batadv_क्रमw_packet अणु
	/**
	 * @list: list node क्रम &batadv_priv.क्रमw.bcast_list and
	 *  &batadv_priv.क्रमw.bat_list
	 */
	काष्ठा hlist_node list;

	/** @cleanup_list: list node क्रम purging functions */
	काष्ठा hlist_node cleanup_list;

	/** @send_समय: execution समय क्रम delayed_work (packet sending) */
	अचिन्हित दीर्घ send_समय;

	/**
	 * @own: bool क्रम locally generated packets (local OGMs are re-scheduled
	 * after sending)
	 */
	u8 own;

	/** @skb: bcast packet's skb buffer */
	काष्ठा sk_buff *skb;

	/** @packet_len: size of aggregated OGM packet inside the skb buffer */
	u16 packet_len;

	/** @direct_link_flags: direct link flags क्रम aggregated OGM packets */
	u32 direct_link_flags;

	/** @num_packets: counter क्रम aggregated OGMv1 packets */
	u8 num_packets;

	/** @delayed_work: work queue callback item क्रम packet sending */
	काष्ठा delayed_work delayed_work;

	/**
	 * @अगर_incoming: poपूर्णांकer to incoming hard-अगरace or primary अगरace अगर
	 *  locally generated packet
	 */
	काष्ठा batadv_hard_अगरace *अगर_incoming;

	/**
	 * @अगर_outgoing: packet where the packet should be sent to, or शून्य अगर
	 *  unspecअगरied
	 */
	काष्ठा batadv_hard_अगरace *अगर_outgoing;

	/** @queue_left: The queue (counter) this packet was applied to */
	atomic_t *queue_left;
पूर्ण;

/**
 * काष्ठा batadv_algo_अगरace_ops - mesh algorithm callbacks (पूर्णांकerface specअगरic)
 */
काष्ठा batadv_algo_अगरace_ops अणु
	/**
	 * @activate: start routing mechanisms when hard-पूर्णांकerface is brought up
	 *  (optional)
	 */
	व्योम (*activate)(काष्ठा batadv_hard_अगरace *hard_अगरace);

	/** @enable: init routing info when hard-पूर्णांकerface is enabled */
	पूर्णांक (*enable)(काष्ठा batadv_hard_अगरace *hard_अगरace);

	/** @enabled: notअगरication when hard-पूर्णांकerface was enabled (optional) */
	व्योम (*enabled)(काष्ठा batadv_hard_अगरace *hard_अगरace);

	/** @disable: de-init routing info when hard-पूर्णांकerface is disabled */
	व्योम (*disable)(काष्ठा batadv_hard_अगरace *hard_अगरace);

	/**
	 * @update_mac: (re-)init mac addresses of the protocol inक्रमmation
	 *  beदीर्घing to this hard-पूर्णांकerface
	 */
	व्योम (*update_mac)(काष्ठा batadv_hard_अगरace *hard_अगरace);

	/** @primary_set: called when primary पूर्णांकerface is selected / changed */
	व्योम (*primary_set)(काष्ठा batadv_hard_अगरace *hard_अगरace);
पूर्ण;

/**
 * काष्ठा batadv_algo_neigh_ops - mesh algorithm callbacks (neighbour specअगरic)
 */
काष्ठा batadv_algo_neigh_ops अणु
	/** @hardअगर_init: called on creation of single hop entry (optional) */
	व्योम (*hardअगर_init)(काष्ठा batadv_hardअगर_neigh_node *neigh);

	/**
	 * @cmp: compare the metrics of two neighbors क्रम their respective
	 *  outgoing पूर्णांकerfaces
	 */
	पूर्णांक (*cmp)(काष्ठा batadv_neigh_node *neigh1,
		   काष्ठा batadv_hard_अगरace *अगर_outgoing1,
		   काष्ठा batadv_neigh_node *neigh2,
		   काष्ठा batadv_hard_अगरace *अगर_outgoing2);

	/**
	 * @is_similar_or_better: check अगर neigh1 is equally similar or better
	 *  than neigh2 क्रम their respective outgoing पूर्णांकerface from the metric
	 *  prospective
	 */
	bool (*is_similar_or_better)(काष्ठा batadv_neigh_node *neigh1,
				     काष्ठा batadv_hard_अगरace *अगर_outgoing1,
				     काष्ठा batadv_neigh_node *neigh2,
				     काष्ठा batadv_hard_अगरace *अगर_outgoing2);

	/** @dump: dump neighbors to a netlink socket (optional) */
	व्योम (*dump)(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
		     काष्ठा batadv_priv *priv,
		     काष्ठा batadv_hard_अगरace *hard_अगरace);
पूर्ण;

/**
 * काष्ठा batadv_algo_orig_ops - mesh algorithm callbacks (originator specअगरic)
 */
काष्ठा batadv_algo_orig_ops अणु
	/** @dump: dump originators to a netlink socket (optional) */
	व्योम (*dump)(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
		     काष्ठा batadv_priv *priv,
		     काष्ठा batadv_hard_अगरace *hard_अगरace);
पूर्ण;

/**
 * काष्ठा batadv_algo_gw_ops - mesh algorithm callbacks (GW specअगरic)
 */
काष्ठा batadv_algo_gw_ops अणु
	/** @init_sel_class: initialize GW selection class (optional) */
	व्योम (*init_sel_class)(काष्ठा batadv_priv *bat_priv);

	/**
	 * @store_sel_class: parse and stores a new GW selection class
	 *  (optional)
	 */
	sमाप_प्रकार (*store_sel_class)(काष्ठा batadv_priv *bat_priv, अक्षर *buff,
				   माप_प्रकार count);
	/**
	 * @get_best_gw_node: select the best GW from the list of available
	 *  nodes (optional)
	 */
	काष्ठा batadv_gw_node *(*get_best_gw_node)
		(काष्ठा batadv_priv *bat_priv);

	/**
	 * @is_eligible: check अगर a newly discovered GW is a potential candidate
	 *  क्रम the election as best GW (optional)
	 */
	bool (*is_eligible)(काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_orig_node *curr_gw_orig,
			    काष्ठा batadv_orig_node *orig_node);

	/** @dump: dump gateways to a netlink socket (optional) */
	व्योम (*dump)(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
		     काष्ठा batadv_priv *priv);
पूर्ण;

/**
 * काष्ठा batadv_algo_ops - mesh algorithm callbacks
 */
काष्ठा batadv_algo_ops अणु
	/** @list: list node क्रम the batadv_algo_list */
	काष्ठा hlist_node list;

	/** @name: name of the algorithm */
	अक्षर *name;

	/** @अगरace: callbacks related to पूर्णांकerface handling */
	काष्ठा batadv_algo_अगरace_ops अगरace;

	/** @neigh: callbacks related to neighbors handling */
	काष्ठा batadv_algo_neigh_ops neigh;

	/** @orig: callbacks related to originators handling */
	काष्ठा batadv_algo_orig_ops orig;

	/** @gw: callbacks related to GW mode */
	काष्ठा batadv_algo_gw_ops gw;
पूर्ण;

/**
 * काष्ठा batadv_dat_entry - it is a single entry of baपंचांगan-adv ARP backend. It
 * is used to stored ARP entries needed क्रम the global DAT cache
 */
काष्ठा batadv_dat_entry अणु
	/** @ip: the IPv4 corresponding to this DAT/ARP entry */
	__be32 ip;

	/** @mac_addr: the MAC address associated to the stored IPv4 */
	u8 mac_addr[ETH_ALEN];

	/** @vid: the vlan ID associated to this entry */
	अचिन्हित लघु vid;

	/**
	 * @last_update: समय in jअगरfies when this entry was refreshed last समय
	 */
	अचिन्हित दीर्घ last_update;

	/** @hash_entry: hlist node क्रम &batadv_priv_dat.hash */
	काष्ठा hlist_node hash_entry;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा batadv_hw_addr - a list entry क्रम a MAC address
 */
काष्ठा batadv_hw_addr अणु
	/** @list: list node क्रम the linking of entries */
	काष्ठा hlist_node list;

	/** @addr: the MAC address of this list entry */
	अचिन्हित अक्षर addr[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा batadv_dat_candidate - candidate destination क्रम DAT operations
 */
काष्ठा batadv_dat_candidate अणु
	/**
	 * @type: the type of the selected candidate. It can one of the
	 *  following:
	 *	  - BATADV_DAT_CANDIDATE_NOT_FOUND
	 *	  - BATADV_DAT_CANDIDATE_ORIG
	 */
	पूर्णांक type;

	/**
	 * @orig_node: अगर type is BATADV_DAT_CANDIDATE_ORIG this field poपूर्णांकs to
	 * the corresponding originator node काष्ठाure
	 */
	काष्ठा batadv_orig_node *orig_node;
पूर्ण;

/**
 * काष्ठा batadv_tvlv_container - container क्रम tvlv appended to OGMs
 */
काष्ठा batadv_tvlv_container अणु
	/** @list: hlist node क्रम &batadv_priv_tvlv.container_list */
	काष्ठा hlist_node list;

	/** @tvlv_hdr: tvlv header inक्रमmation needed to स्थिरruct the tvlv */
	काष्ठा batadv_tvlv_hdr tvlv_hdr;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;
पूर्ण;

/**
 * काष्ठा batadv_tvlv_handler - handler क्रम specअगरic tvlv type and version
 */
काष्ठा batadv_tvlv_handler अणु
	/** @list: hlist node क्रम &batadv_priv_tvlv.handler_list */
	काष्ठा hlist_node list;

	/**
	 * @ogm_handler: handler callback which is given the tvlv payload to
	 *  process on incoming OGM packets
	 */
	व्योम (*ogm_handler)(काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_orig_node *orig,
			    u8 flags, व्योम *tvlv_value, u16 tvlv_value_len);

	/**
	 * @unicast_handler: handler callback which is given the tvlv payload to
	 *  process on incoming unicast tvlv packets
	 */
	पूर्णांक (*unicast_handler)(काष्ठा batadv_priv *bat_priv,
			       u8 *src, u8 *dst,
			       व्योम *tvlv_value, u16 tvlv_value_len);

	/** @type: tvlv type this handler feels responsible क्रम */
	u8 type;

	/** @version: tvlv version this handler feels responsible क्रम */
	u8 version;

	/** @flags: tvlv handler flags */
	u8 flags;

	/** @refcount: number of contexts the object is used */
	काष्ठा kref refcount;

	/** @rcu: काष्ठा used क्रम मुक्तing in an RCU-safe manner */
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * क्रमागत batadv_tvlv_handler_flags - tvlv handler flags definitions
 */
क्रमागत batadv_tvlv_handler_flags अणु
	/**
	 * @BATADV_TVLV_HANDLER_OGM_CIFNOTFND: tvlv ogm processing function
	 *  will call this handler even अगर its type was not found (with no data)
	 */
	BATADV_TVLV_HANDLER_OGM_CIFNOTFND = BIT(1),

	/**
	 * @BATADV_TVLV_HANDLER_OGM_CALLED: पूर्णांकerval tvlv handling flag - the
	 *  API marks a handler as being called, so it won't be called अगर the
	 *  BATADV_TVLV_HANDLER_OGM_CIFNOTFND flag was set
	 */
	BATADV_TVLV_HANDLER_OGM_CALLED = BIT(2),
पूर्ण;

#पूर्ण_अगर /* _NET_BATMAN_ADV_TYPES_H_ */
