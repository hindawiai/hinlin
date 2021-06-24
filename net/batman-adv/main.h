<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_MAIN_H_
#घोषणा _NET_BATMAN_ADV_MAIN_H_

#घोषणा BATADV_DRIVER_AUTHOR "Marek Lindner <mareklindner@neomailbox.ch>, " \
			     "Simon Wunderlich <sw@simonwunderlich.de>"
#घोषणा BATADV_DRIVER_DESC   "B.A.T.M.A.N. advanced"
#घोषणा BATADV_DRIVER_DEVICE "batman-adv"

#अगर_अघोषित BATADV_SOURCE_VERSION
#घोषणा BATADV_SOURCE_VERSION "2021.1"
#पूर्ण_अगर

/* B.A.T.M.A.N. parameters */

#घोषणा BATADV_TQ_MAX_VALUE 255
#घोषणा BATADV_THROUGHPUT_MAX_VALUE 0xFFFFFFFF
#घोषणा BATADV_JITTER 20

/* Time To Live of broadcast messages */
#घोषणा BATADV_TTL 50

/* maximum sequence number age of broadcast messages */
#घोषणा BATADV_BCAST_MAX_AGE 64

/* purge originators after समय in seconds अगर no valid packet comes in
 * -> TODO: check influence on BATADV_TQ_LOCAL_WINDOW_SIZE
 */
#घोषणा BATADV_PURGE_TIMEOUT 200000 /* 200 seconds */
#घोषणा BATADV_TT_LOCAL_TIMEOUT 600000 /* in milliseconds */
#घोषणा BATADV_TT_CLIENT_ROAM_TIMEOUT 600000 /* in milliseconds */
#घोषणा BATADV_TT_CLIENT_TEMP_TIMEOUT 600000 /* in milliseconds */
#घोषणा BATADV_TT_WORK_PERIOD 5000 /* 5 seconds */
#घोषणा BATADV_ORIG_WORK_PERIOD 1000 /* 1 second */
#घोषणा BATADV_MCAST_WORK_PERIOD 500 /* 0.5 seconds */
#घोषणा BATADV_DAT_ENTRY_TIMEOUT (5 * 60000) /* 5 mins in milliseconds */
/* sliding packet range of received originator messages in sequence numbers
 * (should be a multiple of our word size)
 */
#घोषणा BATADV_TQ_LOCAL_WINDOW_SIZE 64
/* milliseconds we have to keep pending tt_req */
#घोषणा BATADV_TT_REQUEST_TIMEOUT 3000

#घोषणा BATADV_TQ_GLOBAL_WINDOW_SIZE 5
#घोषणा BATADV_TQ_LOCAL_BIDRECT_SEND_MINIMUM 1
#घोषणा BATADV_TQ_LOCAL_BIDRECT_RECV_MINIMUM 1
#घोषणा BATADV_TQ_TOTAL_BIDRECT_LIMIT 1

/* B.A.T.M.A.N. V */
#घोषणा BATADV_THROUGHPUT_DEFAULT_VALUE 10 /* 1 Mbps */
#घोषणा BATADV_ELP_PROBES_PER_NODE 2
#घोषणा BATADV_ELP_MIN_PROBE_SIZE 200 /* bytes */
#घोषणा BATADV_ELP_PROBE_MAX_TX_DIFF 100 /* milliseconds */
#घोषणा BATADV_ELP_MAX_AGE 64
#घोषणा BATADV_OGM_MAX_ORIGDIFF 5
#घोषणा BATADV_OGM_MAX_AGE 64

/* number of OGMs sent with the last tt dअगरf */
#घोषणा BATADV_TT_OGM_APPEND_MAX 3

/* Time in which a client can roam at most ROAMING_MAX_COUNT बार in
 * milliseconds
 */
#घोषणा BATADV_ROAMING_MAX_TIME 20000
#घोषणा BATADV_ROAMING_MAX_COUNT 5

#घोषणा BATADV_NO_FLAGS 0

#घोषणा BATADV_शून्य_IFINDEX 0 /* dummy अगरindex used to aव्योम अगरace checks */

#घोषणा BATADV_NO_MARK 0

/* शेष पूर्णांकerface क्रम multi पूर्णांकerface operation. The शेष पूर्णांकerface is
 * used क्रम communication which originated locally (i.e. is not क्रमwarded)
 * or where special क्रमwarding is not desired/necessary.
 */
#घोषणा BATADV_IF_DEFAULT	((काष्ठा batadv_hard_अगरace *)शून्य)

#घोषणा BATADV_NUM_WORDS BITS_TO_LONGS(BATADV_TQ_LOCAL_WINDOW_SIZE)

#घोषणा BATADV_LOG_BUF_LEN 8192	  /* has to be a घातer of 2 */

/* number of packets to send क्रम broadcasts on dअगरferent पूर्णांकerface types */
#घोषणा BATADV_NUM_BCASTS_DEFAULT 1
#घोषणा BATADV_NUM_BCASTS_WIRELESS 3
#घोषणा BATADV_NUM_BCASTS_MAX 3

/* length of the single packet used by the TP meter */
#घोषणा BATADV_TP_PACKET_LEN ETH_DATA_LEN

/* msecs after which an ARP_REQUEST is sent in broadcast as fallback */
#घोषणा ARP_REQ_DELAY 250
/* numbers of originator to contact क्रम any PUT/GET DHT operation */
#घोषणा BATADV_DAT_CANDIDATES_NUM 3

/* BATADV_TQ_SIMILARITY_THRESHOLD - TQ poपूर्णांकs that a secondary metric can dअगरfer
 * at most from the primary one in order to be still considered acceptable
 */
#घोषणा BATADV_TQ_SIMILARITY_THRESHOLD 50

/* should not be bigger than 512 bytes or change the size of
 * क्रमw_packet->direct_link_flags
 */
#घोषणा BATADV_MAX_AGGREGATION_BYTES 512
#घोषणा BATADV_MAX_AGGREGATION_MS 100

#घोषणा BATADV_BLA_PERIOD_LENGTH	10000	/* 10 seconds */
#घोषणा BATADV_BLA_BACKBONE_TIMEOUT	(BATADV_BLA_PERIOD_LENGTH * 6)
#घोषणा BATADV_BLA_CLAIM_TIMEOUT	(BATADV_BLA_PERIOD_LENGTH * 10)
#घोषणा BATADV_BLA_WAIT_PERIODS		3
#घोषणा BATADV_BLA_LOOPDETECT_PERIODS	6
#घोषणा BATADV_BLA_LOOPDETECT_TIMEOUT	3000	/* 3 seconds */

#घोषणा BATADV_DUPLIST_SIZE		16
#घोषणा BATADV_DUPLIST_TIMEOUT		500	/* 500 ms */
/* करोn't reset again within 30 seconds */
#घोषणा BATADV_RESET_PROTECTION_MS 30000
#घोषणा BATADV_EXPECTED_SEQNO_RANGE	65536

#घोषणा BATADV_NC_NODE_TIMEOUT 10000 /* Milliseconds */

/**
 * BATADV_TP_MAX_NUM - maximum number of simultaneously active tp sessions
 */
#घोषणा BATADV_TP_MAX_NUM 5

/**
 * क्रमागत batadv_mesh_state - State of a soft पूर्णांकerface
 */
क्रमागत batadv_mesh_state अणु
	/** @BATADV_MESH_INACTIVE: soft पूर्णांकerface is not yet running */
	BATADV_MESH_INACTIVE,

	/** @BATADV_MESH_ACTIVE: पूर्णांकerface is up and running */
	BATADV_MESH_ACTIVE,

	/** @BATADV_MESH_DEACTIVATING: पूर्णांकerface is getting shut करोwn */
	BATADV_MESH_DEACTIVATING,
पूर्ण;

#घोषणा BATADV_BCAST_QUEUE_LEN		256
#घोषणा BATADV_BATMAN_QUEUE_LEN	256

/**
 * क्रमागत batadv_uev_action - action type of uevent
 */
क्रमागत batadv_uev_action अणु
	/** @BATADV_UEV_ADD: gateway was selected (after none was selected) */
	BATADV_UEV_ADD = 0,

	/**
	 * @BATADV_UEV_DEL: selected gateway was हटाओd and none is selected
	 * anymore
	 */
	BATADV_UEV_DEL,

	/**
	 * @BATADV_UEV_CHANGE: a dअगरferent gateway was selected as based gateway
	 */
	BATADV_UEV_CHANGE,

	/**
	 * @BATADV_UEV_LOOPDETECT: loop was detected which cannot be handled by
	 * bridge loop aव्योमance
	 */
	BATADV_UEV_LOOPDETECT,
पूर्ण;

/**
 * क्रमागत batadv_uev_type - Type of uevent
 */
क्रमागत batadv_uev_type अणु
	/** @BATADV_UEV_GW: selected gateway was modअगरied */
	BATADV_UEV_GW = 0,

	/** @BATADV_UEV_BLA: bridge loop aव्योमance event */
	BATADV_UEV_BLA,
पूर्ण;

#घोषणा BATADV_GW_THRESHOLD	50

/* Number of fragment chains क्रम each orig_node */
#घोषणा BATADV_FRAG_BUFFER_COUNT 8
/* Maximum number of fragments क्रम one packet */
#घोषणा BATADV_FRAG_MAX_FRAGMENTS 16
/* Maxumim size of each fragment */
#घोषणा BATADV_FRAG_MAX_FRAG_SIZE 1280
/* Time to keep fragments जबतक रुकोing क्रम rest of the fragments */
#घोषणा BATADV_FRAG_TIMEOUT 10000

#घोषणा BATADV_DAT_CANDIDATE_NOT_FOUND	0
#घोषणा BATADV_DAT_CANDIDATE_ORIG	1

/* Debug Messages */
#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर
/* Append 'batman-adv: ' beक्रमe kernel messages */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* Kernel headers */

#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/percpu.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "types.h"
#समावेश "main.h"

/**
 * batadv_prपूर्णांक_vid() - वापस prपूर्णांकable version of vid inक्रमmation
 * @vid: the VLAN identअगरier
 *
 * Return: -1 when no VLAN is used, VLAN id otherwise
 */
अटल अंतरभूत पूर्णांक batadv_prपूर्णांक_vid(अचिन्हित लघु vid)
अणु
	अगर (vid & BATADV_VLAN_HAS_TAG)
		वापस (पूर्णांक)(vid & VLAN_VID_MASK);
	अन्यथा
		वापस -1;
पूर्ण

बाह्य काष्ठा list_head batadv_hardअगर_list;
बाह्य अचिन्हित पूर्णांक batadv_hardअगर_generation;

बाह्य अचिन्हित अक्षर batadv_broadcast_addr[];
बाह्य काष्ठा workqueue_काष्ठा *batadv_event_workqueue;

पूर्णांक batadv_mesh_init(काष्ठा net_device *soft_अगरace);
व्योम batadv_mesh_मुक्त(काष्ठा net_device *soft_अगरace);
bool batadv_is_my_mac(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr);
पूर्णांक batadv_max_header_len(व्योम);
व्योम batadv_skb_set_priority(काष्ठा sk_buff *skb, पूर्णांक offset);
पूर्णांक batadv_baपंचांगan_skb_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *ptype,
			   काष्ठा net_device *orig_dev);
पूर्णांक
batadv_recv_handler_रेजिस्टर(u8 packet_type,
			     पूर्णांक (*recv_handler)(काष्ठा sk_buff *,
						 काष्ठा batadv_hard_अगरace *));
व्योम batadv_recv_handler_unरेजिस्टर(u8 packet_type);
__be32 batadv_skb_crc32(काष्ठा sk_buff *skb, u8 *payload_ptr);

/**
 * batadv_compare_eth() - Compare two not u16 aligned Ethernet addresses
 * @data1: Poपूर्णांकer to a six-byte array containing the Ethernet address
 * @data2: Poपूर्णांकer other six-byte array containing the Ethernet address
 *
 * note: can't use ether_addr_equal() as it requires aligned memory
 *
 * Return: true अगर they are the same ethernet addr
 */
अटल अंतरभूत bool batadv_compare_eth(स्थिर व्योम *data1, स्थिर व्योम *data2)
अणु
	वापस ether_addr_equal_unaligned(data1, data2);
पूर्ण

/**
 * batadv_has_समयd_out() - compares current समय (jअगरfies) and बारtamp +
 *  समयout
 * @बारtamp:		base value to compare with (in jअगरfies)
 * @समयout:		added to base value beक्रमe comparing (in milliseconds)
 *
 * Return: true अगर current समय is after बारtamp + समयout
 */
अटल अंतरभूत bool batadv_has_समयd_out(अचिन्हित दीर्घ बारtamp,
					अचिन्हित पूर्णांक समयout)
अणु
	वापस समय_is_beक्रमe_jअगरfies(बारtamp + msecs_to_jअगरfies(समयout));
पूर्ण

/**
 * batadv_atomic_dec_not_zero() - Decrease unless the number is 0
 * @v: poपूर्णांकer of type atomic_t
 *
 * Return: non-zero अगर v was not 0, and zero otherwise.
 */
#घोषणा batadv_atomic_dec_not_zero(v)	atomic_add_unless((v), -1, 0)

/**
 * batadv_smallest_चिन्हित_पूर्णांक() - Returns the smallest चिन्हित पूर्णांकeger in two's
 *  complement with the माप x
 * @x: type of पूर्णांकeger
 *
 * Return: smallest चिन्हित पूर्णांकeger of type
 */
#घोषणा batadv_smallest_चिन्हित_पूर्णांक(x) (1u << (7u + 8u * (माप(x) - 1u)))

/**
 * batadv_seq_beक्रमe() - Checks अगर a sequence number x is a predecessor of y
 * @x: potential predecessor of @y
 * @y: value to compare @x against
 *
 * It handles overflows/underflows and can correctly check क्रम a predecessor
 * unless the variable sequence number has grown by more than
 * 2**(bitwidth(x)-1)-1.
 *
 * This means that क्रम a u8 with the maximum value 255, it would think:
 *
 * * when adding nothing - it is neither a predecessor nor a successor
 * * beक्रमe adding more than 127 to the starting value - it is a predecessor,
 * * when adding 128 - it is neither a predecessor nor a successor,
 * * after adding more than 127 to the starting value - it is a successor
 *
 * Return: true when x is a predecessor of y, false otherwise
 */
#घोषणा batadv_seq_beक्रमe(x, y) (अणु \
	typeof(x)_d1 = (x); \
	typeof(y)_d2 = (y); \
	typeof(x)_dummy = (_d1 - _d2); \
	(व्योम)(&_d1 == &_d2); \
	_dummy > batadv_smallest_चिन्हित_पूर्णांक(_dummy); \
पूर्ण)

/**
 * batadv_seq_after() - Checks अगर a sequence number x is a successor of y
 * @x: potential successor of @y
 * @y: value to compare @x against
 *
 * It handles overflows/underflows and can correctly check क्रम a successor
 * unless the variable sequence number has grown by more than
 * 2**(bitwidth(x)-1)-1.
 *
 * This means that क्रम a u8 with the maximum value 255, it would think:
 *
 * * when adding nothing - it is neither a predecessor nor a successor
 * * beक्रमe adding more than 127 to the starting value - it is a predecessor,
 * * when adding 128 - it is neither a predecessor nor a successor,
 * * after adding more than 127 to the starting value - it is a successor
 *
 * Return: true when x is a successor of y, false otherwise
 */
#घोषणा batadv_seq_after(x, y) batadv_seq_beक्रमe(y, x)

/**
 * batadv_add_counter() - Add to per cpu statistics counter of soft पूर्णांकerface
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @idx: counter index which should be modअगरied
 * @count: value to increase counter by
 *
 * Stop preemption on local cpu जबतक incrementing the counter
 */
अटल अंतरभूत व्योम batadv_add_counter(काष्ठा batadv_priv *bat_priv, माप_प्रकार idx,
				      माप_प्रकार count)
अणु
	this_cpu_add(bat_priv->bat_counters[idx], count);
पूर्ण

/**
 * batadv_inc_counter() - Increase per cpu statistics counter of soft पूर्णांकerface
 * @b: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @i: counter index which should be modअगरied
 */
#घोषणा batadv_inc_counter(b, i) batadv_add_counter(b, i, 1)

/**
 * BATADV_SKB_CB() - Get batadv_skb_cb from skb control buffer
 * @__skb: skb holding the control buffer
 *
 * The members of the control buffer are defined in काष्ठा batadv_skb_cb in
 * types.h. The macro is inspired by the similar macro TCP_SKB_CB() in tcp.h.
 *
 * Return: poपूर्णांकer to the batadv_skb_cb of the skb
 */
#घोषणा BATADV_SKB_CB(__skb)       ((काष्ठा batadv_skb_cb *)&((__skb)->cb[0]))

अचिन्हित लघु batadv_get_vid(काष्ठा sk_buff *skb, माप_प्रकार header_len);
bool batadv_vlan_ap_isola_get(काष्ठा batadv_priv *bat_priv, अचिन्हित लघु vid);
पूर्णांक batadv_throw_uevent(काष्ठा batadv_priv *bat_priv, क्रमागत batadv_uev_type type,
			क्रमागत batadv_uev_action action, स्थिर अक्षर *data);

#पूर्ण_अगर /* _NET_BATMAN_ADV_MAIN_H_ */
