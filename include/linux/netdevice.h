<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the Interfaces handler.
 *
 * Version:	@(#)dev.h	1.0.10	08/12/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Corey Minyard <wf-rch!minyard@relay.EU.net>
 *		Donald J. Becker, <becker@cesdis.gsfc.nasa.gov>
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *		Bjorn Ekwall. <bj0rn@blox.se>
 *              Pekka Riikonen <priikone@poseiकरोn.pspt.fi>
 *
 *		Moved to /usr/include/linux क्रम NET3
 */
#अगर_अघोषित _LINUX_NETDEVICE_H
#घोषणा _LINUX_NETDEVICE_H

#समावेश <linux/समयr.h>
#समावेश <linux/bug.h>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/percpu.h>
#समावेश <linux/rculist.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/dynamic_queue_सीमा.स>

#समावेश <net/net_namespace.h>
#अगर_घोषित CONFIG_DCB
#समावेश <net/dcbnl.h>
#पूर्ण_अगर
#समावेश <net/netprio_cgroup.h>
#समावेश <net/xdp.h>

#समावेश <linux/netdev_features.h>
#समावेश <linux/neighbour.h>
#समावेश <uapi/linux/netdevice.h>
#समावेश <uapi/linux/अगर_bonding.h>
#समावेश <uapi/linux/pkt_cls.h>
#समावेश <linux/hashtable.h>

काष्ठा netpoll_info;
काष्ठा device;
काष्ठा ethtool_ops;
काष्ठा phy_device;
काष्ठा dsa_port;
काष्ठा ip_tunnel_parm;
काष्ठा macsec_context;
काष्ठा macsec_ops;

काष्ठा sfp_bus;
/* 802.11 specअगरic */
काष्ठा wireless_dev;
/* 802.15.4 specअगरic */
काष्ठा wpan_dev;
काष्ठा mpls_dev;
/* UDP Tunnel offloads */
काष्ठा udp_tunnel_info;
काष्ठा udp_tunnel_nic_info;
काष्ठा udp_tunnel_nic;
काष्ठा bpf_prog;
काष्ठा xdp_buff;

व्योम synchronize_net(व्योम);
व्योम netdev_set_शेष_ethtool_ops(काष्ठा net_device *dev,
				    स्थिर काष्ठा ethtool_ops *ops);

/* Backlog congestion levels */
#घोषणा NET_RX_SUCCESS		0	/* keep 'em coming, baby */
#घोषणा NET_RX_DROP		1	/* packet dropped */

#घोषणा MAX_NEST_DEV 8

/*
 * Transmit वापस codes: transmit वापस codes originate from three dअगरferent
 * namespaces:
 *
 * - qdisc वापस codes
 * - driver transmit वापस codes
 * - त्रुटि_सं values
 *
 * Drivers are allowed to वापस any one of those in their hard_start_xmit()
 * function. Real network devices commonly used with qdiscs should only वापस
 * the driver transmit वापस codes though - when qdiscs are used, the actual
 * transmission happens asynchronously, so the value is not propagated to
 * higher layers. Virtual network devices transmit synchronously; in this हाल
 * the driver transmit वापस codes are consumed by dev_queue_xmit(), and all
 * others are propagated to higher layers.
 */

/* qdisc ->enqueue() वापस codes. */
#घोषणा NET_XMIT_SUCCESS	0x00
#घोषणा NET_XMIT_DROP		0x01	/* skb dropped			*/
#घोषणा NET_XMIT_CN		0x02	/* congestion notअगरication	*/
#घोषणा NET_XMIT_MASK		0x0f	/* qdisc flags in net/sch_generic.h */

/* NET_XMIT_CN is special. It करोes not guarantee that this packet is lost. It
 * indicates that the device will soon be dropping packets, or alपढ़ोy drops
 * some packets of the same priority; prompting us to send less aggressively. */
#घोषणा net_xmit_eval(e)	((e) == NET_XMIT_CN ? 0 : (e))
#घोषणा net_xmit_त्रुटि_सं(e)	((e) != NET_XMIT_CN ? -ENOBUFS : 0)

/* Driver transmit वापस codes */
#घोषणा NETDEV_TX_MASK		0xf0

क्रमागत netdev_tx अणु
	__NETDEV_TX_MIN	 = पूर्णांक_न्यून,	/* make sure क्रमागत is चिन्हित */
	NETDEV_TX_OK	 = 0x00,	/* driver took care of packet */
	NETDEV_TX_BUSY	 = 0x10,	/* driver tx path was busy*/
पूर्ण;
प्रकार क्रमागत netdev_tx netdev_tx_t;

/*
 * Current order: NETDEV_TX_MASK > NET_XMIT_MASK >= 0 is signअगरicant;
 * hard_start_xmit() वापस < NET_XMIT_MASK means skb was consumed.
 */
अटल अंतरभूत bool dev_xmit_complete(पूर्णांक rc)
अणु
	/*
	 * Positive हालs with an skb consumed by a driver:
	 * - successful transmission (rc == NETDEV_TX_OK)
	 * - error जबतक transmitting (rc < 0)
	 * - error जबतक queueing to a dअगरferent device (rc & NET_XMIT_MASK)
	 */
	अगर (likely(rc < NET_XMIT_MASK))
		वापस true;

	वापस false;
पूर्ण

/*
 *	Compute the worst-हाल header length according to the protocols
 *	used.
 */

#अगर defined(CONFIG_HYPERV_NET)
# define LL_MAX_HEADER 128
#या_अगर defined(CONFIG_WLAN) || IS_ENABLED(CONFIG_AX25)
# अगर defined(CONFIG_MAC80211_MESH)
#  define LL_MAX_HEADER 128
# अन्यथा
#  define LL_MAX_HEADER 96
# endअगर
#अन्यथा
# define LL_MAX_HEADER 32
#पूर्ण_अगर

#अगर !IS_ENABLED(CONFIG_NET_IPIP) && !IS_ENABLED(CONFIG_NET_IPGRE) && \
    !IS_ENABLED(CONFIG_IPV6_SIT) && !IS_ENABLED(CONFIG_IPV6_TUNNEL)
#घोषणा MAX_HEADER LL_MAX_HEADER
#अन्यथा
#घोषणा MAX_HEADER (LL_MAX_HEADER + 48)
#पूर्ण_अगर

/*
 *	Old network device statistics. Fields are native words
 *	(अचिन्हित दीर्घ) so they can be पढ़ो and written atomically.
 */

काष्ठा net_device_stats अणु
	अचिन्हित दीर्घ	rx_packets;
	अचिन्हित दीर्घ	tx_packets;
	अचिन्हित दीर्घ	rx_bytes;
	अचिन्हित दीर्घ	tx_bytes;
	अचिन्हित दीर्घ	rx_errors;
	अचिन्हित दीर्घ	tx_errors;
	अचिन्हित दीर्घ	rx_dropped;
	अचिन्हित दीर्घ	tx_dropped;
	अचिन्हित दीर्घ	multicast;
	अचिन्हित दीर्घ	collisions;
	अचिन्हित दीर्घ	rx_length_errors;
	अचिन्हित दीर्घ	rx_over_errors;
	अचिन्हित दीर्घ	rx_crc_errors;
	अचिन्हित दीर्घ	rx_frame_errors;
	अचिन्हित दीर्घ	rx_fअगरo_errors;
	अचिन्हित दीर्घ	rx_missed_errors;
	अचिन्हित दीर्घ	tx_पातed_errors;
	अचिन्हित दीर्घ	tx_carrier_errors;
	अचिन्हित दीर्घ	tx_fअगरo_errors;
	अचिन्हित दीर्घ	tx_heartbeat_errors;
	अचिन्हित दीर्घ	tx_winकरोw_errors;
	अचिन्हित दीर्घ	rx_compressed;
	अचिन्हित दीर्घ	tx_compressed;
पूर्ण;


#समावेश <linux/cache.h>
#समावेश <linux/skbuff.h>

#अगर_घोषित CONFIG_RPS
#समावेश <linux/अटल_key.h>
बाह्य काष्ठा अटल_key_false rps_needed;
बाह्य काष्ठा अटल_key_false rfs_needed;
#पूर्ण_अगर

काष्ठा neighbour;
काष्ठा neigh_parms;
काष्ठा sk_buff;

काष्ठा netdev_hw_addr अणु
	काष्ठा list_head	list;
	अचिन्हित अक्षर		addr[MAX_ADDR_LEN];
	अचिन्हित अक्षर		type;
#घोषणा NETDEV_HW_ADDR_T_LAN		1
#घोषणा NETDEV_HW_ADDR_T_SAN		2
#घोषणा NETDEV_HW_ADDR_T_UNICAST	3
#घोषणा NETDEV_HW_ADDR_T_MULTICAST	4
	bool			global_use;
	पूर्णांक			sync_cnt;
	पूर्णांक			refcount;
	पूर्णांक			synced;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

काष्ठा netdev_hw_addr_list अणु
	काष्ठा list_head	list;
	पूर्णांक			count;
पूर्ण;

#घोषणा netdev_hw_addr_list_count(l) ((l)->count)
#घोषणा netdev_hw_addr_list_empty(l) (netdev_hw_addr_list_count(l) == 0)
#घोषणा netdev_hw_addr_list_क्रम_each(ha, l) \
	list_क्रम_each_entry(ha, &(l)->list, list)

#घोषणा netdev_uc_count(dev) netdev_hw_addr_list_count(&(dev)->uc)
#घोषणा netdev_uc_empty(dev) netdev_hw_addr_list_empty(&(dev)->uc)
#घोषणा netdev_क्रम_each_uc_addr(ha, dev) \
	netdev_hw_addr_list_क्रम_each(ha, &(dev)->uc)

#घोषणा netdev_mc_count(dev) netdev_hw_addr_list_count(&(dev)->mc)
#घोषणा netdev_mc_empty(dev) netdev_hw_addr_list_empty(&(dev)->mc)
#घोषणा netdev_क्रम_each_mc_addr(ha, dev) \
	netdev_hw_addr_list_क्रम_each(ha, &(dev)->mc)

काष्ठा hh_cache अणु
	अचिन्हित पूर्णांक	hh_len;
	seqlock_t	hh_lock;

	/* cached hardware header; allow क्रम machine alignment needs.        */
#घोषणा HH_DATA_MOD	16
#घोषणा HH_DATA_OFF(__len) \
	(HH_DATA_MOD - (((__len - 1) & (HH_DATA_MOD - 1)) + 1))
#घोषणा HH_DATA_ALIGN(__len) \
	(((__len)+(HH_DATA_MOD-1))&~(HH_DATA_MOD - 1))
	अचिन्हित दीर्घ	hh_data[HH_DATA_ALIGN(LL_MAX_HEADER) / माप(दीर्घ)];
पूर्ण;

/* Reserve HH_DATA_MOD byte-aligned hard_header_len, but at least that much.
 * Alternative is:
 *   dev->hard_header_len ? (dev->hard_header_len +
 *                           (HH_DATA_MOD - 1)) & ~(HH_DATA_MOD - 1) : 0
 *
 * We could use other alignment values, but we must मुख्यtain the
 * relationship HH alignment <= LL alignment.
 */
#घोषणा LL_RESERVED_SPACE(dev) \
	((((dev)->hard_header_len+(dev)->needed_headroom)&~(HH_DATA_MOD - 1)) + HH_DATA_MOD)
#घोषणा LL_RESERVED_SPACE_EXTRA(dev,extra) \
	((((dev)->hard_header_len+(dev)->needed_headroom+(extra))&~(HH_DATA_MOD - 1)) + HH_DATA_MOD)

काष्ठा header_ops अणु
	पूर्णांक	(*create) (काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   अचिन्हित लघु type, स्थिर व्योम *daddr,
			   स्थिर व्योम *saddr, अचिन्हित पूर्णांक len);
	पूर्णांक	(*parse)(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr);
	पूर्णांक	(*cache)(स्थिर काष्ठा neighbour *neigh, काष्ठा hh_cache *hh, __be16 type);
	व्योम	(*cache_update)(काष्ठा hh_cache *hh,
				स्थिर काष्ठा net_device *dev,
				स्थिर अचिन्हित अक्षर *haddr);
	bool	(*validate)(स्थिर अक्षर *ll_header, अचिन्हित पूर्णांक len);
	__be16	(*parse_protocol)(स्थिर काष्ठा sk_buff *skb);
पूर्ण;

/* These flag bits are निजी to the generic network queueing
 * layer; they may not be explicitly referenced by any other
 * code.
 */

क्रमागत netdev_state_t अणु
	__LINK_STATE_START,
	__LINK_STATE_PRESENT,
	__LINK_STATE_NOCARRIER,
	__LINK_STATE_LINKWATCH_PENDING,
	__LINK_STATE_DORMANT,
	__LINK_STATE_TESTING,
पूर्ण;


/*
 * This काष्ठाure holds boot-समय configured netdevice settings. They
 * are then used in the device probing.
 */
काष्ठा netdev_boot_setup अणु
	अक्षर name[IFNAMSIZ];
	काष्ठा अगरmap map;
पूर्ण;
#घोषणा NETDEV_BOOT_SETUP_MAX 8

पूर्णांक __init netdev_boot_setup(अक्षर *str);

काष्ठा gro_list अणु
	काष्ठा list_head	list;
	पूर्णांक			count;
पूर्ण;

/*
 * size of gro hash buckets, must less than bit number of
 * napi_काष्ठा::gro_biपंचांगask
 */
#घोषणा GRO_HASH_BUCKETS	8

/*
 * Structure क्रम NAPI scheduling similar to tasklet but with weighting
 */
काष्ठा napi_काष्ठा अणु
	/* The poll_list must only be managed by the entity which
	 * changes the state of the NAPI_STATE_SCHED bit.  This means
	 * whoever atomically sets that bit can add this napi_काष्ठा
	 * to the per-CPU poll_list, and whoever clears that bit
	 * can हटाओ from the list right beक्रमe clearing the bit.
	 */
	काष्ठा list_head	poll_list;

	अचिन्हित दीर्घ		state;
	पूर्णांक			weight;
	पूर्णांक			defer_hard_irqs_count;
	अचिन्हित दीर्घ		gro_biपंचांगask;
	पूर्णांक			(*poll)(काष्ठा napi_काष्ठा *, पूर्णांक);
#अगर_घोषित CONFIG_NETPOLL
	पूर्णांक			poll_owner;
#पूर्ण_अगर
	काष्ठा net_device	*dev;
	काष्ठा gro_list		gro_hash[GRO_HASH_BUCKETS];
	काष्ठा sk_buff		*skb;
	काष्ठा list_head	rx_list; /* Pending GRO_NORMAL skbs */
	पूर्णांक			rx_count; /* length of rx_list */
	काष्ठा hrसमयr		समयr;
	काष्ठा list_head	dev_list;
	काष्ठा hlist_node	napi_hash_node;
	अचिन्हित पूर्णांक		napi_id;
	काष्ठा task_काष्ठा	*thपढ़ो;
पूर्ण;

क्रमागत अणु
	NAPI_STATE_SCHED,		/* Poll is scheduled */
	NAPI_STATE_MISSED,		/* reschedule a napi */
	NAPI_STATE_DISABLE,		/* Disable pending */
	NAPI_STATE_NPSVC,		/* Netpoll - करोn't dequeue from poll_list */
	NAPI_STATE_LISTED,		/* NAPI added to प्रणाली lists */
	NAPI_STATE_NO_BUSY_POLL,	/* Do not add in napi_hash, no busy polling */
	NAPI_STATE_IN_BUSY_POLL,	/* sk_busy_loop() owns this NAPI */
	NAPI_STATE_PREFER_BUSY_POLL,	/* prefer busy-polling over softirq processing*/
	NAPI_STATE_THREADED,		/* The poll is perक्रमmed inside its own thपढ़ो*/
	NAPI_STATE_SCHED_THREADED,	/* Napi is currently scheduled in thपढ़ोed mode */
पूर्ण;

क्रमागत अणु
	NAPIF_STATE_SCHED		= BIT(NAPI_STATE_SCHED),
	NAPIF_STATE_MISSED		= BIT(NAPI_STATE_MISSED),
	NAPIF_STATE_DISABLE		= BIT(NAPI_STATE_DISABLE),
	NAPIF_STATE_NPSVC		= BIT(NAPI_STATE_NPSVC),
	NAPIF_STATE_LISTED		= BIT(NAPI_STATE_LISTED),
	NAPIF_STATE_NO_BUSY_POLL	= BIT(NAPI_STATE_NO_BUSY_POLL),
	NAPIF_STATE_IN_BUSY_POLL	= BIT(NAPI_STATE_IN_BUSY_POLL),
	NAPIF_STATE_PREFER_BUSY_POLL	= BIT(NAPI_STATE_PREFER_BUSY_POLL),
	NAPIF_STATE_THREADED		= BIT(NAPI_STATE_THREADED),
	NAPIF_STATE_SCHED_THREADED	= BIT(NAPI_STATE_SCHED_THREADED),
पूर्ण;

क्रमागत gro_result अणु
	GRO_MERGED,
	GRO_MERGED_FREE,
	GRO_HELD,
	GRO_NORMAL,
	GRO_CONSUMED,
पूर्ण;
प्रकार क्रमागत gro_result gro_result_t;

/*
 * क्रमागत rx_handler_result - Possible वापस values क्रम rx_handlers.
 * @RX_HANDLER_CONSUMED: skb was consumed by rx_handler, करो not process it
 * further.
 * @RX_HANDLER_ANOTHER: Do another round in receive path. This is indicated in
 * हाल skb->dev was changed by rx_handler.
 * @RX_HANDLER_EXACT: Force exact delivery, no wildcard.
 * @RX_HANDLER_PASS: Do nothing, pass the skb as अगर no rx_handler was called.
 *
 * rx_handlers are functions called from inside __netअगर_receive_skb(), to करो
 * special processing of the skb, prior to delivery to protocol handlers.
 *
 * Currently, a net_device can only have a single rx_handler रेजिस्टरed. Trying
 * to रेजिस्टर a second rx_handler will वापस -EBUSY.
 *
 * To रेजिस्टर a rx_handler on a net_device, use netdev_rx_handler_रेजिस्टर().
 * To unरेजिस्टर a rx_handler on a net_device, use
 * netdev_rx_handler_unरेजिस्टर().
 *
 * Upon वापस, rx_handler is expected to tell __netअगर_receive_skb() what to
 * करो with the skb.
 *
 * If the rx_handler consumed the skb in some way, it should वापस
 * RX_HANDLER_CONSUMED. This is appropriate when the rx_handler arranged क्रम
 * the skb to be delivered in some other way.
 *
 * If the rx_handler changed skb->dev, to भागert the skb to another
 * net_device, it should वापस RX_HANDLER_ANOTHER. The rx_handler क्रम the
 * new device will be called अगर it exists.
 *
 * If the rx_handler decides the skb should be ignored, it should वापस
 * RX_HANDLER_EXACT. The skb will only be delivered to protocol handlers that
 * are रेजिस्टरed on exact device (ptype->dev == skb->dev).
 *
 * If the rx_handler didn't change skb->dev, but wants the skb to be normally
 * delivered, it should वापस RX_HANDLER_PASS.
 *
 * A device without a रेजिस्टरed rx_handler will behave as अगर rx_handler
 * वापसed RX_HANDLER_PASS.
 */

क्रमागत rx_handler_result अणु
	RX_HANDLER_CONSUMED,
	RX_HANDLER_ANOTHER,
	RX_HANDLER_EXACT,
	RX_HANDLER_PASS,
पूर्ण;
प्रकार क्रमागत rx_handler_result rx_handler_result_t;
प्रकार rx_handler_result_t rx_handler_func_t(काष्ठा sk_buff **pskb);

व्योम __napi_schedule(काष्ठा napi_काष्ठा *n);
व्योम __napi_schedule_irqoff(काष्ठा napi_काष्ठा *n);

अटल अंतरभूत bool napi_disable_pending(काष्ठा napi_काष्ठा *n)
अणु
	वापस test_bit(NAPI_STATE_DISABLE, &n->state);
पूर्ण

अटल अंतरभूत bool napi_prefer_busy_poll(काष्ठा napi_काष्ठा *n)
अणु
	वापस test_bit(NAPI_STATE_PREFER_BUSY_POLL, &n->state);
पूर्ण

bool napi_schedule_prep(काष्ठा napi_काष्ठा *n);

/**
 *	napi_schedule - schedule NAPI poll
 *	@n: NAPI context
 *
 * Schedule NAPI poll routine to be called अगर it is not alपढ़ोy
 * running.
 */
अटल अंतरभूत व्योम napi_schedule(काष्ठा napi_काष्ठा *n)
अणु
	अगर (napi_schedule_prep(n))
		__napi_schedule(n);
पूर्ण

/**
 *	napi_schedule_irqoff - schedule NAPI poll
 *	@n: NAPI context
 *
 * Variant of napi_schedule(), assuming hard irqs are masked.
 */
अटल अंतरभूत व्योम napi_schedule_irqoff(काष्ठा napi_काष्ठा *n)
अणु
	अगर (napi_schedule_prep(n))
		__napi_schedule_irqoff(n);
पूर्ण

/* Try to reschedule poll. Called by dev->poll() after napi_complete().  */
अटल अंतरभूत bool napi_reschedule(काष्ठा napi_काष्ठा *napi)
अणु
	अगर (napi_schedule_prep(napi)) अणु
		__napi_schedule(napi);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool napi_complete_करोne(काष्ठा napi_काष्ठा *n, पूर्णांक work_करोne);
/**
 *	napi_complete - NAPI processing complete
 *	@n: NAPI context
 *
 * Mark NAPI processing as complete.
 * Consider using napi_complete_करोne() instead.
 * Return false अगर device should aव्योम rearming पूर्णांकerrupts.
 */
अटल अंतरभूत bool napi_complete(काष्ठा napi_काष्ठा *n)
अणु
	वापस napi_complete_करोne(n, 0);
पूर्ण

पूर्णांक dev_set_thपढ़ोed(काष्ठा net_device *dev, bool thपढ़ोed);

/**
 *	napi_disable - prevent NAPI from scheduling
 *	@n: NAPI context
 *
 * Stop NAPI from being scheduled on this context.
 * Waits till any outstanding processing completes.
 */
व्योम napi_disable(काष्ठा napi_काष्ठा *n);

व्योम napi_enable(काष्ठा napi_काष्ठा *n);

/**
 *	napi_synchronize - रुको until NAPI is not running
 *	@n: NAPI context
 *
 * Wait until NAPI is करोne being scheduled on this context.
 * Waits till any outstanding processing completes but
 * करोes not disable future activations.
 */
अटल अंतरभूत व्योम napi_synchronize(स्थिर काष्ठा napi_काष्ठा *n)
अणु
	अगर (IS_ENABLED(CONFIG_SMP))
		जबतक (test_bit(NAPI_STATE_SCHED, &n->state))
			msleep(1);
	अन्यथा
		barrier();
पूर्ण

/**
 *	napi_अगर_scheduled_mark_missed - अगर napi is running, set the
 *	NAPIF_STATE_MISSED
 *	@n: NAPI context
 *
 * If napi is running, set the NAPIF_STATE_MISSED, and वापस true अगर
 * NAPI is scheduled.
 **/
अटल अंतरभूत bool napi_अगर_scheduled_mark_missed(काष्ठा napi_काष्ठा *n)
अणु
	अचिन्हित दीर्घ val, new;

	करो अणु
		val = READ_ONCE(n->state);
		अगर (val & NAPIF_STATE_DISABLE)
			वापस true;

		अगर (!(val & NAPIF_STATE_SCHED))
			वापस false;

		new = val | NAPIF_STATE_MISSED;
	पूर्ण जबतक (cmpxchg(&n->state, val, new) != val);

	वापस true;
पूर्ण

क्रमागत netdev_queue_state_t अणु
	__QUEUE_STATE_DRV_XOFF,
	__QUEUE_STATE_STACK_XOFF,
	__QUEUE_STATE_FROZEN,
पूर्ण;

#घोषणा QUEUE_STATE_DRV_XOFF	(1 << __QUEUE_STATE_DRV_XOFF)
#घोषणा QUEUE_STATE_STACK_XOFF	(1 << __QUEUE_STATE_STACK_XOFF)
#घोषणा QUEUE_STATE_FROZEN	(1 << __QUEUE_STATE_FROZEN)

#घोषणा QUEUE_STATE_ANY_XOFF	(QUEUE_STATE_DRV_XOFF | QUEUE_STATE_STACK_XOFF)
#घोषणा QUEUE_STATE_ANY_XOFF_OR_FROZEN (QUEUE_STATE_ANY_XOFF | \
					QUEUE_STATE_FROZEN)
#घोषणा QUEUE_STATE_DRV_XOFF_OR_FROZEN (QUEUE_STATE_DRV_XOFF | \
					QUEUE_STATE_FROZEN)

/*
 * __QUEUE_STATE_DRV_XOFF is used by drivers to stop the transmit queue.  The
 * netअगर_tx_* functions below are used to manipulate this flag.  The
 * __QUEUE_STATE_STACK_XOFF flag is used by the stack to stop the transmit
 * queue independently.  The netअगर_xmit_*stopped functions below are called
 * to check अगर the queue has been stopped by the driver or stack (either
 * of the XOFF bits are set in the state).  Drivers should not need to call
 * netअगर_xmit*stopped functions, they should only be using netअगर_tx_*.
 */

काष्ठा netdev_queue अणु
/*
 * पढ़ो-mostly part
 */
	काष्ठा net_device	*dev;
	काष्ठा Qdisc __rcu	*qdisc;
	काष्ठा Qdisc		*qdisc_sleeping;
#अगर_घोषित CONFIG_SYSFS
	काष्ठा kobject		kobj;
#पूर्ण_अगर
#अगर defined(CONFIG_XPS) && defined(CONFIG_NUMA)
	पूर्णांक			numa_node;
#पूर्ण_अगर
	अचिन्हित दीर्घ		tx_maxrate;
	/*
	 * Number of TX समयouts क्रम this queue
	 * (/sys/class/net/DEV/Q/trans_समयout)
	 */
	अचिन्हित दीर्घ		trans_समयout;

	/* Subordinate device that the queue has been asचिन्हित to */
	काष्ठा net_device	*sb_dev;
#अगर_घोषित CONFIG_XDP_SOCKETS
	काष्ठा xsk_buff_pool    *pool;
#पूर्ण_अगर
/*
 * ग_लिखो-mostly part
 */
	spinlock_t		_xmit_lock ____cacheline_aligned_in_smp;
	पूर्णांक			xmit_lock_owner;
	/*
	 * Time (in jअगरfies) of last Tx
	 */
	अचिन्हित दीर्घ		trans_start;

	अचिन्हित दीर्घ		state;

#अगर_घोषित CONFIG_BQL
	काष्ठा dql		dql;
#पूर्ण_अगर
पूर्ण ____cacheline_aligned_in_smp;

बाह्य पूर्णांक sysctl_fb_tunnels_only_क्रम_init_net;
बाह्य पूर्णांक sysctl_devconf_inherit_init_net;

/*
 * sysctl_fb_tunnels_only_क्रम_init_net == 0 : For all netns
 *                                     == 1 : For initns only
 *                                     == 2 : For none.
 */
अटल अंतरभूत bool net_has_fallback_tunnels(स्थिर काष्ठा net *net)
अणु
	वापस !IS_ENABLED(CONFIG_SYSCTL) ||
	       !sysctl_fb_tunnels_only_क्रम_init_net ||
	       (net == &init_net && sysctl_fb_tunnels_only_क्रम_init_net == 1);
पूर्ण

अटल अंतरभूत पूर्णांक netdev_queue_numa_node_पढ़ो(स्थिर काष्ठा netdev_queue *q)
अणु
#अगर defined(CONFIG_XPS) && defined(CONFIG_NUMA)
	वापस q->numa_node;
#अन्यथा
	वापस NUMA_NO_NODE;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम netdev_queue_numa_node_ग_लिखो(काष्ठा netdev_queue *q, पूर्णांक node)
अणु
#अगर defined(CONFIG_XPS) && defined(CONFIG_NUMA)
	q->numa_node = node;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_RPS
/*
 * This काष्ठाure holds an RPS map which can be of variable length.  The
 * map is an array of CPUs.
 */
काष्ठा rps_map अणु
	अचिन्हित पूर्णांक len;
	काष्ठा rcu_head rcu;
	u16 cpus[];
पूर्ण;
#घोषणा RPS_MAP_SIZE(_num) (माप(काष्ठा rps_map) + ((_num) * माप(u16)))

/*
 * The rps_dev_flow काष्ठाure contains the mapping of a flow to a CPU, the
 * tail poपूर्णांकer क्रम that CPU's input queue at the समय of last enqueue, and
 * a hardware filter index.
 */
काष्ठा rps_dev_flow अणु
	u16 cpu;
	u16 filter;
	अचिन्हित पूर्णांक last_qtail;
पूर्ण;
#घोषणा RPS_NO_FILTER 0xffff

/*
 * The rps_dev_flow_table काष्ठाure contains a table of flow mappings.
 */
काष्ठा rps_dev_flow_table अणु
	अचिन्हित पूर्णांक mask;
	काष्ठा rcu_head rcu;
	काष्ठा rps_dev_flow flows[];
पूर्ण;
#घोषणा RPS_DEV_FLOW_TABLE_SIZE(_num) (माप(काष्ठा rps_dev_flow_table) + \
    ((_num) * माप(काष्ठा rps_dev_flow)))

/*
 * The rps_sock_flow_table contains mappings of flows to the last CPU
 * on which they were processed by the application (set in recvmsg).
 * Each entry is a 32bit value. Upper part is the high-order bits
 * of flow hash, lower part is CPU number.
 * rps_cpu_mask is used to partition the space, depending on number of
 * possible CPUs : rps_cpu_mask = roundup_घात_of_two(nr_cpu_ids) - 1
 * For example, अगर 64 CPUs are possible, rps_cpu_mask = 0x3f,
 * meaning we use 32-6=26 bits क्रम the hash.
 */
काष्ठा rps_sock_flow_table अणु
	u32	mask;

	u32	ents[] ____cacheline_aligned_in_smp;
पूर्ण;
#घोषणा	RPS_SOCK_FLOW_TABLE_SIZE(_num) (दुरत्व(काष्ठा rps_sock_flow_table, ents[_num]))

#घोषणा RPS_NO_CPU 0xffff

बाह्य u32 rps_cpu_mask;
बाह्य काष्ठा rps_sock_flow_table __rcu *rps_sock_flow_table;

अटल अंतरभूत व्योम rps_record_sock_flow(काष्ठा rps_sock_flow_table *table,
					u32 hash)
अणु
	अगर (table && hash) अणु
		अचिन्हित पूर्णांक index = hash & table->mask;
		u32 val = hash & ~rps_cpu_mask;

		/* We only give a hपूर्णांक, preemption can change CPU under us */
		val |= raw_smp_processor_id();

		अगर (table->ents[index] != val)
			table->ents[index] = val;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
bool rps_may_expire_flow(काष्ठा net_device *dev, u16 rxq_index, u32 flow_id,
			 u16 filter_id);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_RPS */

/* This काष्ठाure contains an instance of an RX queue. */
काष्ठा netdev_rx_queue अणु
#अगर_घोषित CONFIG_RPS
	काष्ठा rps_map __rcu		*rps_map;
	काष्ठा rps_dev_flow_table __rcu	*rps_flow_table;
#पूर्ण_अगर
	काष्ठा kobject			kobj;
	काष्ठा net_device		*dev;
	काष्ठा xdp_rxq_info		xdp_rxq;
#अगर_घोषित CONFIG_XDP_SOCKETS
	काष्ठा xsk_buff_pool            *pool;
#पूर्ण_अगर
पूर्ण ____cacheline_aligned_in_smp;

/*
 * RX queue sysfs काष्ठाures and functions.
 */
काष्ठा rx_queue_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा netdev_rx_queue *queue, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा netdev_rx_queue *queue,
			 स्थिर अक्षर *buf, माप_प्रकार len);
पूर्ण;

/* XPS map type and offset of the xps map within net_device->xps_maps[]. */
क्रमागत xps_map_type अणु
	XPS_CPUS = 0,
	XPS_RXQS,
	XPS_MAPS_MAX,
पूर्ण;

#अगर_घोषित CONFIG_XPS
/*
 * This काष्ठाure holds an XPS map which can be of variable length.  The
 * map is an array of queues.
 */
काष्ठा xps_map अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक alloc_len;
	काष्ठा rcu_head rcu;
	u16 queues[];
पूर्ण;
#घोषणा XPS_MAP_SIZE(_num) (माप(काष्ठा xps_map) + ((_num) * माप(u16)))
#घोषणा XPS_MIN_MAP_ALLOC ((L1_CACHE_ALIGN(दुरत्व(काष्ठा xps_map, queues[1])) \
       - माप(काष्ठा xps_map)) / माप(u16))

/*
 * This काष्ठाure holds all XPS maps क्रम device.  Maps are indexed by CPU.
 *
 * We keep track of the number of cpus/rxqs used when the काष्ठा is allocated,
 * in nr_ids. This will help not accessing out-of-bound memory.
 *
 * We keep track of the number of traffic classes used when the काष्ठा is
 * allocated, in num_tc. This will be used to navigate the maps, to ensure we're
 * not crossing its upper bound, as the original dev->num_tc can be updated in
 * the meanसमय.
 */
काष्ठा xps_dev_maps अणु
	काष्ठा rcu_head rcu;
	अचिन्हित पूर्णांक nr_ids;
	s16 num_tc;
	काष्ठा xps_map __rcu *attr_map[]; /* Either CPUs map or RXQs map */
पूर्ण;

#घोषणा XPS_CPU_DEV_MAPS_SIZE(_tcs) (माप(काष्ठा xps_dev_maps) +	\
	(nr_cpu_ids * (_tcs) * माप(काष्ठा xps_map *)))

#घोषणा XPS_RXQ_DEV_MAPS_SIZE(_tcs, _rxqs) (माप(काष्ठा xps_dev_maps) +\
	(_rxqs * (_tcs) * माप(काष्ठा xps_map *)))

#पूर्ण_अगर /* CONFIG_XPS */

#घोषणा TC_MAX_QUEUE	16
#घोषणा TC_BITMASK	15
/* HW offloaded queuing disciplines txq count and offset maps */
काष्ठा netdev_tc_txq अणु
	u16 count;
	u16 offset;
पूर्ण;

#अगर defined(CONFIG_FCOE) || defined(CONFIG_FCOE_MODULE)
/*
 * This काष्ठाure is to hold inक्रमmation about the device
 * configured to run FCoE protocol stack.
 */
काष्ठा netdev_fcoe_hbainfo अणु
	अक्षर	manufacturer[64];
	अक्षर	serial_number[64];
	अक्षर	hardware_version[64];
	अक्षर	driver_version[64];
	अक्षर	optionrom_version[64];
	अक्षर	firmware_version[64];
	अक्षर	model[256];
	अक्षर	model_description[256];
पूर्ण;
#पूर्ण_अगर

#घोषणा MAX_PHYS_ITEM_ID_LEN 32

/* This काष्ठाure holds a unique identअगरier to identअगरy some
 * physical item (port क्रम example) used by a netdevice.
 */
काष्ठा netdev_phys_item_id अणु
	अचिन्हित अक्षर id[MAX_PHYS_ITEM_ID_LEN];
	अचिन्हित अक्षर id_len;
पूर्ण;

अटल अंतरभूत bool netdev_phys_item_id_same(काष्ठा netdev_phys_item_id *a,
					    काष्ठा netdev_phys_item_id *b)
अणु
	वापस a->id_len == b->id_len &&
	       स_भेद(a->id, b->id, a->id_len) == 0;
पूर्ण

प्रकार u16 (*select_queue_fallback_t)(काष्ठा net_device *dev,
				       काष्ठा sk_buff *skb,
				       काष्ठा net_device *sb_dev);

क्रमागत net_device_path_type अणु
	DEV_PATH_ETHERNET = 0,
	DEV_PATH_VLAN,
	DEV_PATH_BRIDGE,
	DEV_PATH_PPPOE,
	DEV_PATH_DSA,
पूर्ण;

काष्ठा net_device_path अणु
	क्रमागत net_device_path_type	type;
	स्थिर काष्ठा net_device		*dev;
	जोड़ अणु
		काष्ठा अणु
			u16		id;
			__be16		proto;
			u8		h_dest[ETH_ALEN];
		पूर्ण encap;
		काष्ठा अणु
			क्रमागत अणु
				DEV_PATH_BR_VLAN_KEEP,
				DEV_PATH_BR_VLAN_TAG,
				DEV_PATH_BR_VLAN_UNTAG,
				DEV_PATH_BR_VLAN_UNTAG_HW,
			पूर्ण		vlan_mode;
			u16		vlan_id;
			__be16		vlan_proto;
		पूर्ण bridge;
		काष्ठा अणु
			पूर्णांक port;
			u16 proto;
		पूर्ण dsa;
	पूर्ण;
पूर्ण;

#घोषणा NET_DEVICE_PATH_STACK_MAX	5
#घोषणा NET_DEVICE_PATH_VLAN_MAX	2

काष्ठा net_device_path_stack अणु
	पूर्णांक			num_paths;
	काष्ठा net_device_path	path[NET_DEVICE_PATH_STACK_MAX];
पूर्ण;

काष्ठा net_device_path_ctx अणु
	स्थिर काष्ठा net_device *dev;
	स्थिर u8		*daddr;

	पूर्णांक			num_vlans;
	काष्ठा अणु
		u16		id;
		__be16		proto;
	पूर्ण vlan[NET_DEVICE_PATH_VLAN_MAX];
पूर्ण;

क्रमागत tc_setup_type अणु
	TC_SETUP_QDISC_MQPRIO,
	TC_SETUP_CLSU32,
	TC_SETUP_CLSFLOWER,
	TC_SETUP_CLSMATCHALL,
	TC_SETUP_CLSBPF,
	TC_SETUP_BLOCK,
	TC_SETUP_QDISC_CBS,
	TC_SETUP_QDISC_RED,
	TC_SETUP_QDISC_PRIO,
	TC_SETUP_QDISC_MQ,
	TC_SETUP_QDISC_ETF,
	TC_SETUP_ROOT_QDISC,
	TC_SETUP_QDISC_GRED,
	TC_SETUP_QDISC_TAPRIO,
	TC_SETUP_FT,
	TC_SETUP_QDISC_ETS,
	TC_SETUP_QDISC_TBF,
	TC_SETUP_QDISC_FIFO,
	TC_SETUP_QDISC_HTB,
पूर्ण;

/* These काष्ठाures hold the attributes of bpf state that are being passed
 * to the netdevice through the bpf op.
 */
क्रमागत bpf_netdev_command अणु
	/* Set or clear a bpf program used in the earliest stages of packet
	 * rx. The prog will have been loaded as BPF_PROG_TYPE_XDP. The callee
	 * is responsible क्रम calling bpf_prog_put on any old progs that are
	 * stored. In हाल of error, the callee need not release the new prog
	 * reference, but on success it takes ownership and must bpf_prog_put
	 * when it is no दीर्घer used.
	 */
	XDP_SETUP_PROG,
	XDP_SETUP_PROG_HW,
	/* BPF program क्रम offload callbacks, invoked at program load समय. */
	BPF_OFFLOAD_MAP_ALLOC,
	BPF_OFFLOAD_MAP_FREE,
	XDP_SETUP_XSK_POOL,
पूर्ण;

काष्ठा bpf_prog_offload_ops;
काष्ठा netlink_ext_ack;
काष्ठा xdp_umem;
काष्ठा xdp_dev_bulk_queue;
काष्ठा bpf_xdp_link;

क्रमागत bpf_xdp_mode अणु
	XDP_MODE_SKB = 0,
	XDP_MODE_DRV = 1,
	XDP_MODE_HW = 2,
	__MAX_XDP_MODE
पूर्ण;

काष्ठा bpf_xdp_entity अणु
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_xdp_link *link;
पूर्ण;

काष्ठा netdev_bpf अणु
	क्रमागत bpf_netdev_command command;
	जोड़ अणु
		/* XDP_SETUP_PROG */
		काष्ठा अणु
			u32 flags;
			काष्ठा bpf_prog *prog;
			काष्ठा netlink_ext_ack *extack;
		पूर्ण;
		/* BPF_OFFLOAD_MAP_ALLOC, BPF_OFFLOAD_MAP_FREE */
		काष्ठा अणु
			काष्ठा bpf_offloaded_map *offmap;
		पूर्ण;
		/* XDP_SETUP_XSK_POOL */
		काष्ठा अणु
			काष्ठा xsk_buff_pool *pool;
			u16 queue_id;
		पूर्ण xsk;
	पूर्ण;
पूर्ण;

/* Flags क्रम nकरो_xsk_wakeup. */
#घोषणा XDP_WAKEUP_RX (1 << 0)
#घोषणा XDP_WAKEUP_TX (1 << 1)

#अगर_घोषित CONFIG_XFRM_OFFLOAD
काष्ठा xfrmdev_ops अणु
	पूर्णांक	(*xकरो_dev_state_add) (काष्ठा xfrm_state *x);
	व्योम	(*xकरो_dev_state_delete) (काष्ठा xfrm_state *x);
	व्योम	(*xकरो_dev_state_मुक्त) (काष्ठा xfrm_state *x);
	bool	(*xकरो_dev_offload_ok) (काष्ठा sk_buff *skb,
				       काष्ठा xfrm_state *x);
	व्योम	(*xकरो_dev_state_advance_esn) (काष्ठा xfrm_state *x);
पूर्ण;
#पूर्ण_अगर

काष्ठा dev_अगरalias अणु
	काष्ठा rcu_head rcuhead;
	अक्षर अगरalias[];
पूर्ण;

काष्ठा devlink;
काष्ठा tlsdev_ops;

काष्ठा netdev_name_node अणु
	काष्ठा hlist_node hlist;
	काष्ठा list_head list;
	काष्ठा net_device *dev;
	स्थिर अक्षर *name;
पूर्ण;

पूर्णांक netdev_name_node_alt_create(काष्ठा net_device *dev, स्थिर अक्षर *name);
पूर्णांक netdev_name_node_alt_destroy(काष्ठा net_device *dev, स्थिर अक्षर *name);

काष्ठा netdev_net_notअगरier अणु
	काष्ठा list_head list;
	काष्ठा notअगरier_block *nb;
पूर्ण;

/*
 * This काष्ठाure defines the management hooks क्रम network devices.
 * The following hooks can be defined; unless noted otherwise, they are
 * optional and can be filled with a null poपूर्णांकer.
 *
 * पूर्णांक (*nकरो_init)(काष्ठा net_device *dev);
 *     This function is called once when a network device is रेजिस्टरed.
 *     The network device can use this क्रम any late stage initialization
 *     or semantic validation. It can fail with an error code which will
 *     be propagated back to रेजिस्टर_netdev.
 *
 * व्योम (*nकरो_uninit)(काष्ठा net_device *dev);
 *     This function is called when device is unरेजिस्टरed or when registration
 *     fails. It is not called अगर init fails.
 *
 * पूर्णांक (*nकरो_खोलो)(काष्ठा net_device *dev);
 *     This function is called when a network device transitions to the up
 *     state.
 *
 * पूर्णांक (*nकरो_stop)(काष्ठा net_device *dev);
 *     This function is called when a network device transitions to the करोwn
 *     state.
 *
 * netdev_tx_t (*nकरो_start_xmit)(काष्ठा sk_buff *skb,
 *                               काष्ठा net_device *dev);
 *	Called when a packet needs to be transmitted.
 *	Returns NETDEV_TX_OK.  Can वापस NETDEV_TX_BUSY, but you should stop
 *	the queue beक्रमe that can happen; it's क्रम obsolete devices and weird
 *	corner हालs, but the stack really करोes a non-trivial amount
 *	of useless work अगर you वापस NETDEV_TX_BUSY.
 *	Required; cannot be शून्य.
 *
 * netdev_features_t (*nकरो_features_check)(काष्ठा sk_buff *skb,
 *					   काष्ठा net_device *dev
 *					   netdev_features_t features);
 *	Called by core transmit path to determine अगर device is capable of
 *	perक्रमming offload operations on a given packet. This is to give
 *	the device an opportunity to implement any restrictions that cannot
 *	be otherwise expressed by feature flags. The check is called with
 *	the set of features that the stack has calculated and it वापसs
 *	those the driver believes to be appropriate.
 *
 * u16 (*nकरो_select_queue)(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
 *                         काष्ठा net_device *sb_dev);
 *	Called to decide which queue to use when device supports multiple
 *	transmit queues.
 *
 * व्योम (*nकरो_change_rx_flags)(काष्ठा net_device *dev, पूर्णांक flags);
 *	This function is called to allow device receiver to make
 *	changes to configuration when multicast or promiscuous is enabled.
 *
 * व्योम (*nकरो_set_rx_mode)(काष्ठा net_device *dev);
 *	This function is called device changes address list filtering.
 *	If driver handles unicast address filtering, it should set
 *	IFF_UNICAST_FLT in its priv_flags.
 *
 * पूर्णांक (*nकरो_set_mac_address)(काष्ठा net_device *dev, व्योम *addr);
 *	This function  is called when the Media Access Control address
 *	needs to be changed. If this पूर्णांकerface is not defined, the
 *	MAC address can not be changed.
 *
 * पूर्णांक (*nकरो_validate_addr)(काष्ठा net_device *dev);
 *	Test अगर Media Access Control address is valid क्रम the device.
 *
 * पूर्णांक (*nकरो_करो_ioctl)(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
 *	Called when a user requests an ioctl which can't be handled by
 *	the generic पूर्णांकerface code. If not defined ioctls वापस
 *	not supported error code.
 *
 * पूर्णांक (*nकरो_set_config)(काष्ठा net_device *dev, काष्ठा अगरmap *map);
 *	Used to set network devices bus पूर्णांकerface parameters. This पूर्णांकerface
 *	is retained क्रम legacy reasons; new devices should use the bus
 *	पूर्णांकerface (PCI) क्रम low level management.
 *
 * पूर्णांक (*nकरो_change_mtu)(काष्ठा net_device *dev, पूर्णांक new_mtu);
 *	Called when a user wants to change the Maximum Transfer Unit
 *	of a device.
 *
 * व्योम (*nकरो_tx_समयout)(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
 *	Callback used when the transmitter has not made any progress
 *	क्रम dev->watchकरोg ticks.
 *
 * व्योम (*nकरो_get_stats64)(काष्ठा net_device *dev,
 *                         काष्ठा rtnl_link_stats64 *storage);
 * काष्ठा net_device_stats* (*nकरो_get_stats)(काष्ठा net_device *dev);
 *	Called when a user wants to get the network device usage
 *	statistics. Drivers must करो one of the following:
 *	1. Define @nकरो_get_stats64 to fill in a zero-initialised
 *	   rtnl_link_stats64 काष्ठाure passed by the caller.
 *	2. Define @nकरो_get_stats to update a net_device_stats काष्ठाure
 *	   (which should normally be dev->stats) and वापस a poपूर्णांकer to
 *	   it. The काष्ठाure may be changed asynchronously only अगर each
 *	   field is written atomically.
 *	3. Update dev->stats asynchronously and atomically, and define
 *	   neither operation.
 *
 * bool (*nकरो_has_offload_stats)(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id)
 *	Return true अगर this device supports offload stats of this attr_id.
 *
 * पूर्णांक (*nकरो_get_offload_stats)(पूर्णांक attr_id, स्थिर काष्ठा net_device *dev,
 *	व्योम *attr_data)
 *	Get statistics क्रम offload operations by attr_id. Write it पूर्णांकo the
 *	attr_data poपूर्णांकer.
 *
 * पूर्णांक (*nकरो_vlan_rx_add_vid)(काष्ठा net_device *dev, __be16 proto, u16 vid);
 *	If device supports VLAN filtering this function is called when a
 *	VLAN id is रेजिस्टरed.
 *
 * पूर्णांक (*nकरो_vlan_rx_समाप्त_vid)(काष्ठा net_device *dev, __be16 proto, u16 vid);
 *	If device supports VLAN filtering this function is called when a
 *	VLAN id is unरेजिस्टरed.
 *
 * व्योम (*nकरो_poll_controller)(काष्ठा net_device *dev);
 *
 *	SR-IOV management functions.
 * पूर्णांक (*nकरो_set_vf_mac)(काष्ठा net_device *dev, पूर्णांक vf, u8* mac);
 * पूर्णांक (*nकरो_set_vf_vlan)(काष्ठा net_device *dev, पूर्णांक vf, u16 vlan,
 *			  u8 qos, __be16 proto);
 * पूर्णांक (*nकरो_set_vf_rate)(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक min_tx_rate,
 *			  पूर्णांक max_tx_rate);
 * पूर्णांक (*nकरो_set_vf_spoofchk)(काष्ठा net_device *dev, पूर्णांक vf, bool setting);
 * पूर्णांक (*nकरो_set_vf_trust)(काष्ठा net_device *dev, पूर्णांक vf, bool setting);
 * पूर्णांक (*nकरो_get_vf_config)(काष्ठा net_device *dev,
 *			    पूर्णांक vf, काष्ठा अगरla_vf_info *ivf);
 * पूर्णांक (*nकरो_set_vf_link_state)(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक link_state);
 * पूर्णांक (*nकरो_set_vf_port)(काष्ठा net_device *dev, पूर्णांक vf,
 *			  काष्ठा nlattr *port[]);
 *
 *      Enable or disable the VF ability to query its RSS Redirection Table and
 *      Hash Key. This is needed since on some devices VF share this inक्रमmation
 *      with PF and querying it may पूर्णांकroduce a theoretical security risk.
 * पूर्णांक (*nकरो_set_vf_rss_query_en)(काष्ठा net_device *dev, पूर्णांक vf, bool setting);
 * पूर्णांक (*nकरो_get_vf_port)(काष्ठा net_device *dev, पूर्णांक vf, काष्ठा sk_buff *skb);
 * पूर्णांक (*nकरो_setup_tc)(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
 *		       व्योम *type_data);
 *	Called to setup any 'tc' scheduler, classअगरier or action on @dev.
 *	This is always called from the stack with the rtnl lock held and netअगर
 *	tx queues stopped. This allows the netdevice to perक्रमm queue
 *	management safely.
 *
 *	Fiber Channel over Ethernet (FCoE) offload functions.
 * पूर्णांक (*nकरो_fcoe_enable)(काष्ठा net_device *dev);
 *	Called when the FCoE protocol stack wants to start using LLD क्रम FCoE
 *	so the underlying device can perक्रमm whatever needed configuration or
 *	initialization to support acceleration of FCoE traffic.
 *
 * पूर्णांक (*nकरो_fcoe_disable)(काष्ठा net_device *dev);
 *	Called when the FCoE protocol stack wants to stop using LLD क्रम FCoE
 *	so the underlying device can perक्रमm whatever needed clean-ups to
 *	stop supporting acceleration of FCoE traffic.
 *
 * पूर्णांक (*nकरो_fcoe_ddp_setup)(काष्ठा net_device *dev, u16 xid,
 *			     काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc);
 *	Called when the FCoE Initiator wants to initialize an I/O that
 *	is a possible candidate क्रम Direct Data Placement (DDP). The LLD can
 *	perक्रमm necessary setup and वापसs 1 to indicate the device is set up
 *	successfully to perक्रमm DDP on this I/O, otherwise this वापसs 0.
 *
 * पूर्णांक (*nकरो_fcoe_ddp_करोne)(काष्ठा net_device *dev,  u16 xid);
 *	Called when the FCoE Initiator/Target is करोne with the DDPed I/O as
 *	indicated by the FC exchange id 'xid', so the underlying device can
 *	clean up and reuse resources क्रम later DDP requests.
 *
 * पूर्णांक (*nकरो_fcoe_ddp_target)(काष्ठा net_device *dev, u16 xid,
 *			      काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc);
 *	Called when the FCoE Target wants to initialize an I/O that
 *	is a possible candidate क्रम Direct Data Placement (DDP). The LLD can
 *	perक्रमm necessary setup and वापसs 1 to indicate the device is set up
 *	successfully to perक्रमm DDP on this I/O, otherwise this वापसs 0.
 *
 * पूर्णांक (*nकरो_fcoe_get_hbainfo)(काष्ठा net_device *dev,
 *			       काष्ठा netdev_fcoe_hbainfo *hbainfo);
 *	Called when the FCoE Protocol stack wants inक्रमmation on the underlying
 *	device. This inक्रमmation is utilized by the FCoE protocol stack to
 *	रेजिस्टर attributes with Fiber Channel management service as per the
 *	FC-GS Fabric Device Management Inक्रमmation(FDMI) specअगरication.
 *
 * पूर्णांक (*nकरो_fcoe_get_wwn)(काष्ठा net_device *dev, u64 *wwn, पूर्णांक type);
 *	Called when the underlying device wants to override शेष World Wide
 *	Name (WWN) generation mechanism in FCoE protocol stack to pass its own
 *	World Wide Port Name (WWPN) or World Wide Node Name (WWNN) to the FCoE
 *	protocol stack to use.
 *
 *	RFS acceleration.
 * पूर्णांक (*nकरो_rx_flow_steer)(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
 *			    u16 rxq_index, u32 flow_id);
 *	Set hardware filter क्रम RFS.  rxq_index is the target queue index;
 *	flow_id is a flow ID to be passed to rps_may_expire_flow() later.
 *	Return the filter ID on success, or a negative error code.
 *
 *	Slave management functions (क्रम bridge, bonding, etc).
 * पूर्णांक (*nकरो_add_slave)(काष्ठा net_device *dev, काष्ठा net_device *slave_dev);
 *	Called to make another netdev an underling.
 *
 * पूर्णांक (*nकरो_del_slave)(काष्ठा net_device *dev, काष्ठा net_device *slave_dev);
 *	Called to release previously enslaved netdev.
 *
 * काष्ठा net_device *(*nकरो_get_xmit_slave)(काष्ठा net_device *dev,
 *					    काष्ठा sk_buff *skb,
 *					    bool all_slaves);
 *	Get the xmit slave of master device. If all_slaves is true, function
 *	assume all the slaves can transmit.
 *
 *      Feature/offload setting functions.
 * netdev_features_t (*nकरो_fix_features)(काष्ठा net_device *dev,
 *		netdev_features_t features);
 *	Adjusts the requested feature flags according to device-specअगरic
 *	स्थिरraपूर्णांकs, and वापसs the resulting flags. Must not modअगरy
 *	the device state.
 *
 * पूर्णांक (*nकरो_set_features)(काष्ठा net_device *dev, netdev_features_t features);
 *	Called to update device configuration to new features. Passed
 *	feature set might be less than what was वापसed by nकरो_fix_features()).
 *	Must वापस >0 or -त्रुटि_सं अगर it changed dev->features itself.
 *
 * पूर्णांक (*nकरो_fdb_add)(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
 *		      काष्ठा net_device *dev,
 *		      स्थिर अचिन्हित अक्षर *addr, u16 vid, u16 flags,
 *		      काष्ठा netlink_ext_ack *extack);
 *	Adds an FDB entry to dev क्रम addr.
 * पूर्णांक (*nकरो_fdb_del)(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
 *		      काष्ठा net_device *dev,
 *		      स्थिर अचिन्हित अक्षर *addr, u16 vid)
 *	Deletes the FDB entry from dev coresponding to addr.
 * पूर्णांक (*nकरो_fdb_dump)(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
 *		       काष्ठा net_device *dev, काष्ठा net_device *filter_dev,
 *		       पूर्णांक *idx)
 *	Used to add FDB entries to dump requests. Implementers should add
 *	entries to skb and update idx with the number of entries.
 *
 * पूर्णांक (*nकरो_bridge_setlink)(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
 *			     u16 flags, काष्ठा netlink_ext_ack *extack)
 * पूर्णांक (*nकरो_bridge_getlink)(काष्ठा sk_buff *skb, u32 pid, u32 seq,
 *			     काष्ठा net_device *dev, u32 filter_mask,
 *			     पूर्णांक nlflags)
 * पूर्णांक (*nकरो_bridge_dellink)(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
 *			     u16 flags);
 *
 * पूर्णांक (*nकरो_change_carrier)(काष्ठा net_device *dev, bool new_carrier);
 *	Called to change device carrier. Soft-devices (like dummy, team, etc)
 *	which करो not represent real hardware may define this to allow their
 *	userspace components to manage their भव carrier state. Devices
 *	that determine carrier state from physical hardware properties (eg
 *	network cables) or protocol-dependent mechanisms (eg
 *	USB_CDC_NOTIFY_NETWORK_CONNECTION) should NOT implement this function.
 *
 * पूर्णांक (*nकरो_get_phys_port_id)(काष्ठा net_device *dev,
 *			       काष्ठा netdev_phys_item_id *ppid);
 *	Called to get ID of physical port of this device. If driver करोes
 *	not implement this, it is assumed that the hw is not able to have
 *	multiple net devices on single physical port.
 *
 * पूर्णांक (*nकरो_get_port_parent_id)(काष्ठा net_device *dev,
 *				 काष्ठा netdev_phys_item_id *ppid)
 *	Called to get the parent ID of the physical port of this device.
 *
 * व्योम* (*nकरो_dfwd_add_station)(काष्ठा net_device *pdev,
 *				 काष्ठा net_device *dev)
 *	Called by upper layer devices to accelerate चयनing or other
 *	station functionality पूर्णांकo hardware. 'pdev is the lowerdev
 *	to use क्रम the offload and 'dev' is the net device that will
 *	back the offload. Returns a poपूर्णांकer to the निजी काष्ठाure
 *	the upper layer will मुख्यtain.
 * व्योम (*nकरो_dfwd_del_station)(काष्ठा net_device *pdev, व्योम *priv)
 *	Called by upper layer device to delete the station created
 *	by 'ndo_dfwd_add_station'. 'pdev' is the net device backing
 *	the station and priv is the काष्ठाure वापसed by the add
 *	operation.
 * पूर्णांक (*nकरो_set_tx_maxrate)(काष्ठा net_device *dev,
 *			     पूर्णांक queue_index, u32 maxrate);
 *	Called when a user wants to set a max-rate limitation of specअगरic
 *	TX queue.
 * पूर्णांक (*nकरो_get_अगरlink)(स्थिर काष्ठा net_device *dev);
 *	Called to get the अगरlink value of this device.
 * व्योम (*nकरो_change_proto_करोwn)(काष्ठा net_device *dev,
 *				 bool proto_करोwn);
 *	This function is used to pass protocol port error state inक्रमmation
 *	to the चयन driver. The चयन driver can react to the proto_करोwn
 *      by करोing a phys करोwn on the associated चयन port.
 * पूर्णांक (*nकरो_fill_metadata_dst)(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
 *	This function is used to get egress tunnel inक्रमmation क्रम given skb.
 *	This is useful क्रम retrieving outer tunnel header parameters जबतक
 *	sampling packet.
 * व्योम (*nकरो_set_rx_headroom)(काष्ठा net_device *dev, पूर्णांक needed_headroom);
 *	This function is used to specअगरy the headroom that the skb must
 *	consider when allocation skb during packet reception. Setting
 *	appropriate rx headroom value allows aव्योमing skb head copy on
 *	क्रमward. Setting a negative value resets the rx headroom to the
 *	शेष value.
 * पूर्णांक (*nकरो_bpf)(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf);
 *	This function is used to set or query state related to XDP on the
 *	netdevice and manage BPF offload. See definition of
 *	क्रमागत bpf_netdev_command क्रम details.
 * पूर्णांक (*nकरो_xdp_xmit)(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **xdp,
 *			u32 flags);
 *	This function is used to submit @n XDP packets क्रम transmit on a
 *	netdevice. Returns number of frames successfully transmitted, frames
 *	that got dropped are मुक्तd/वापसed via xdp_वापस_frame().
 *	Returns negative number, means general error invoking nकरो, meaning
 *	no frames were xmit'ed and core-caller will मुक्त all frames.
 * पूर्णांक (*nकरो_xsk_wakeup)(काष्ठा net_device *dev, u32 queue_id, u32 flags);
 *      This function is used to wake up the softirq, ksoftirqd or kthपढ़ो
 *	responsible क्रम sending and/or receiving packets on a specअगरic
 *	queue id bound to an AF_XDP socket. The flags field specअगरies अगर
 *	only RX, only Tx, or both should be woken up using the flags
 *	XDP_WAKEUP_RX and XDP_WAKEUP_TX.
 * काष्ठा devlink_port *(*nकरो_get_devlink_port)(काष्ठा net_device *dev);
 *	Get devlink port instance associated with a given netdev.
 *	Called with a reference on the netdevice and devlink locks only,
 *	rtnl_lock is not held.
 * पूर्णांक (*nकरो_tunnel_ctl)(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p,
 *			 पूर्णांक cmd);
 *	Add, change, delete or get inक्रमmation on an IPv4 tunnel.
 * काष्ठा net_device *(*nकरो_get_peer_dev)(काष्ठा net_device *dev);
 *	If a device is paired with a peer device, वापस the peer instance.
 *	The caller must be under RCU पढ़ो context.
 * पूर्णांक (*nकरो_fill_क्रमward_path)(काष्ठा net_device_path_ctx *ctx, काष्ठा net_device_path *path);
 *     Get the क्रमwarding path to reach the real device from the HW destination address
 */
काष्ठा net_device_ops अणु
	पूर्णांक			(*nकरो_init)(काष्ठा net_device *dev);
	व्योम			(*nकरो_uninit)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_खोलो)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_stop)(काष्ठा net_device *dev);
	netdev_tx_t		(*nकरो_start_xmit)(काष्ठा sk_buff *skb,
						  काष्ठा net_device *dev);
	netdev_features_t	(*nकरो_features_check)(काष्ठा sk_buff *skb,
						      काष्ठा net_device *dev,
						      netdev_features_t features);
	u16			(*nकरो_select_queue)(काष्ठा net_device *dev,
						    काष्ठा sk_buff *skb,
						    काष्ठा net_device *sb_dev);
	व्योम			(*nकरो_change_rx_flags)(काष्ठा net_device *dev,
						       पूर्णांक flags);
	व्योम			(*nकरो_set_rx_mode)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_set_mac_address)(काष्ठा net_device *dev,
						       व्योम *addr);
	पूर्णांक			(*nकरो_validate_addr)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_करो_ioctl)(काष्ठा net_device *dev,
					        काष्ठा अगरreq *अगरr, पूर्णांक cmd);
	पूर्णांक			(*nकरो_set_config)(काष्ठा net_device *dev,
					          काष्ठा अगरmap *map);
	पूर्णांक			(*nकरो_change_mtu)(काष्ठा net_device *dev,
						  पूर्णांक new_mtu);
	पूर्णांक			(*nकरो_neigh_setup)(काष्ठा net_device *dev,
						   काष्ठा neigh_parms *);
	व्योम			(*nकरो_tx_समयout) (काष्ठा net_device *dev,
						   अचिन्हित पूर्णांक txqueue);

	व्योम			(*nकरो_get_stats64)(काष्ठा net_device *dev,
						   काष्ठा rtnl_link_stats64 *storage);
	bool			(*nकरो_has_offload_stats)(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id);
	पूर्णांक			(*nकरो_get_offload_stats)(पूर्णांक attr_id,
							 स्थिर काष्ठा net_device *dev,
							 व्योम *attr_data);
	काष्ठा net_device_stats* (*nकरो_get_stats)(काष्ठा net_device *dev);

	पूर्णांक			(*nकरो_vlan_rx_add_vid)(काष्ठा net_device *dev,
						       __be16 proto, u16 vid);
	पूर्णांक			(*nकरो_vlan_rx_समाप्त_vid)(काष्ठा net_device *dev,
						        __be16 proto, u16 vid);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	व्योम                    (*nकरो_poll_controller)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_netpoll_setup)(काष्ठा net_device *dev,
						     काष्ठा netpoll_info *info);
	व्योम			(*nकरो_netpoll_cleanup)(काष्ठा net_device *dev);
#पूर्ण_अगर
	पूर्णांक			(*nकरो_set_vf_mac)(काष्ठा net_device *dev,
						  पूर्णांक queue, u8 *mac);
	पूर्णांक			(*nकरो_set_vf_vlan)(काष्ठा net_device *dev,
						   पूर्णांक queue, u16 vlan,
						   u8 qos, __be16 proto);
	पूर्णांक			(*nकरो_set_vf_rate)(काष्ठा net_device *dev,
						   पूर्णांक vf, पूर्णांक min_tx_rate,
						   पूर्णांक max_tx_rate);
	पूर्णांक			(*nकरो_set_vf_spoofchk)(काष्ठा net_device *dev,
						       पूर्णांक vf, bool setting);
	पूर्णांक			(*nकरो_set_vf_trust)(काष्ठा net_device *dev,
						    पूर्णांक vf, bool setting);
	पूर्णांक			(*nकरो_get_vf_config)(काष्ठा net_device *dev,
						     पूर्णांक vf,
						     काष्ठा अगरla_vf_info *ivf);
	पूर्णांक			(*nकरो_set_vf_link_state)(काष्ठा net_device *dev,
							 पूर्णांक vf, पूर्णांक link_state);
	पूर्णांक			(*nकरो_get_vf_stats)(काष्ठा net_device *dev,
						    पूर्णांक vf,
						    काष्ठा अगरla_vf_stats
						    *vf_stats);
	पूर्णांक			(*nकरो_set_vf_port)(काष्ठा net_device *dev,
						   पूर्णांक vf,
						   काष्ठा nlattr *port[]);
	पूर्णांक			(*nकरो_get_vf_port)(काष्ठा net_device *dev,
						   पूर्णांक vf, काष्ठा sk_buff *skb);
	पूर्णांक			(*nकरो_get_vf_guid)(काष्ठा net_device *dev,
						   पूर्णांक vf,
						   काष्ठा अगरla_vf_guid *node_guid,
						   काष्ठा अगरla_vf_guid *port_guid);
	पूर्णांक			(*nकरो_set_vf_guid)(काष्ठा net_device *dev,
						   पूर्णांक vf, u64 guid,
						   पूर्णांक guid_type);
	पूर्णांक			(*nकरो_set_vf_rss_query_en)(
						   काष्ठा net_device *dev,
						   पूर्णांक vf, bool setting);
	पूर्णांक			(*nकरो_setup_tc)(काष्ठा net_device *dev,
						क्रमागत tc_setup_type type,
						व्योम *type_data);
#अगर IS_ENABLED(CONFIG_FCOE)
	पूर्णांक			(*nकरो_fcoe_enable)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_fcoe_disable)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_fcoe_ddp_setup)(काष्ठा net_device *dev,
						      u16 xid,
						      काष्ठा scatterlist *sgl,
						      अचिन्हित पूर्णांक sgc);
	पूर्णांक			(*nकरो_fcoe_ddp_करोne)(काष्ठा net_device *dev,
						     u16 xid);
	पूर्णांक			(*nकरो_fcoe_ddp_target)(काष्ठा net_device *dev,
						       u16 xid,
						       काष्ठा scatterlist *sgl,
						       अचिन्हित पूर्णांक sgc);
	पूर्णांक			(*nकरो_fcoe_get_hbainfo)(काष्ठा net_device *dev,
							काष्ठा netdev_fcoe_hbainfo *hbainfo);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_LIBFCOE)
#घोषणा NETDEV_FCOE_WWNN 0
#घोषणा NETDEV_FCOE_WWPN 1
	पूर्णांक			(*nकरो_fcoe_get_wwn)(काष्ठा net_device *dev,
						    u64 *wwn, पूर्णांक type);
#पूर्ण_अगर

#अगर_घोषित CONFIG_RFS_ACCEL
	पूर्णांक			(*nकरो_rx_flow_steer)(काष्ठा net_device *dev,
						     स्थिर काष्ठा sk_buff *skb,
						     u16 rxq_index,
						     u32 flow_id);
#पूर्ण_अगर
	पूर्णांक			(*nकरो_add_slave)(काष्ठा net_device *dev,
						 काष्ठा net_device *slave_dev,
						 काष्ठा netlink_ext_ack *extack);
	पूर्णांक			(*nकरो_del_slave)(काष्ठा net_device *dev,
						 काष्ठा net_device *slave_dev);
	काष्ठा net_device*	(*nकरो_get_xmit_slave)(काष्ठा net_device *dev,
						      काष्ठा sk_buff *skb,
						      bool all_slaves);
	काष्ठा net_device*	(*nकरो_sk_get_lower_dev)(काष्ठा net_device *dev,
							काष्ठा sock *sk);
	netdev_features_t	(*nकरो_fix_features)(काष्ठा net_device *dev,
						    netdev_features_t features);
	पूर्णांक			(*nकरो_set_features)(काष्ठा net_device *dev,
						    netdev_features_t features);
	पूर्णांक			(*nकरो_neigh_स्थिरruct)(काष्ठा net_device *dev,
						       काष्ठा neighbour *n);
	व्योम			(*nकरो_neigh_destroy)(काष्ठा net_device *dev,
						     काष्ठा neighbour *n);

	पूर्णांक			(*nकरो_fdb_add)(काष्ठा ndmsg *ndm,
					       काष्ठा nlattr *tb[],
					       काष्ठा net_device *dev,
					       स्थिर अचिन्हित अक्षर *addr,
					       u16 vid,
					       u16 flags,
					       काष्ठा netlink_ext_ack *extack);
	पूर्णांक			(*nकरो_fdb_del)(काष्ठा ndmsg *ndm,
					       काष्ठा nlattr *tb[],
					       काष्ठा net_device *dev,
					       स्थिर अचिन्हित अक्षर *addr,
					       u16 vid);
	पूर्णांक			(*nकरो_fdb_dump)(काष्ठा sk_buff *skb,
						काष्ठा netlink_callback *cb,
						काष्ठा net_device *dev,
						काष्ठा net_device *filter_dev,
						पूर्णांक *idx);
	पूर्णांक			(*nकरो_fdb_get)(काष्ठा sk_buff *skb,
					       काष्ठा nlattr *tb[],
					       काष्ठा net_device *dev,
					       स्थिर अचिन्हित अक्षर *addr,
					       u16 vid, u32 portid, u32 seq,
					       काष्ठा netlink_ext_ack *extack);
	पूर्णांक			(*nकरो_bridge_setlink)(काष्ठा net_device *dev,
						      काष्ठा nlmsghdr *nlh,
						      u16 flags,
						      काष्ठा netlink_ext_ack *extack);
	पूर्णांक			(*nकरो_bridge_getlink)(काष्ठा sk_buff *skb,
						      u32 pid, u32 seq,
						      काष्ठा net_device *dev,
						      u32 filter_mask,
						      पूर्णांक nlflags);
	पूर्णांक			(*nकरो_bridge_dellink)(काष्ठा net_device *dev,
						      काष्ठा nlmsghdr *nlh,
						      u16 flags);
	पूर्णांक			(*nकरो_change_carrier)(काष्ठा net_device *dev,
						      bool new_carrier);
	पूर्णांक			(*nकरो_get_phys_port_id)(काष्ठा net_device *dev,
							काष्ठा netdev_phys_item_id *ppid);
	पूर्णांक			(*nकरो_get_port_parent_id)(काष्ठा net_device *dev,
							  काष्ठा netdev_phys_item_id *ppid);
	पूर्णांक			(*nकरो_get_phys_port_name)(काष्ठा net_device *dev,
							  अक्षर *name, माप_प्रकार len);
	व्योम*			(*nकरो_dfwd_add_station)(काष्ठा net_device *pdev,
							काष्ठा net_device *dev);
	व्योम			(*nकरो_dfwd_del_station)(काष्ठा net_device *pdev,
							व्योम *priv);

	पूर्णांक			(*nकरो_set_tx_maxrate)(काष्ठा net_device *dev,
						      पूर्णांक queue_index,
						      u32 maxrate);
	पूर्णांक			(*nकरो_get_अगरlink)(स्थिर काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_change_proto_करोwn)(काष्ठा net_device *dev,
							 bool proto_करोwn);
	पूर्णांक			(*nकरो_fill_metadata_dst)(काष्ठा net_device *dev,
						       काष्ठा sk_buff *skb);
	व्योम			(*nकरो_set_rx_headroom)(काष्ठा net_device *dev,
						       पूर्णांक needed_headroom);
	पूर्णांक			(*nकरो_bpf)(काष्ठा net_device *dev,
					   काष्ठा netdev_bpf *bpf);
	पूर्णांक			(*nकरो_xdp_xmit)(काष्ठा net_device *dev, पूर्णांक n,
						काष्ठा xdp_frame **xdp,
						u32 flags);
	पूर्णांक			(*nकरो_xsk_wakeup)(काष्ठा net_device *dev,
						  u32 queue_id, u32 flags);
	काष्ठा devlink_port *	(*nकरो_get_devlink_port)(काष्ठा net_device *dev);
	पूर्णांक			(*nकरो_tunnel_ctl)(काष्ठा net_device *dev,
						  काष्ठा ip_tunnel_parm *p, पूर्णांक cmd);
	काष्ठा net_device *	(*nकरो_get_peer_dev)(काष्ठा net_device *dev);
	पूर्णांक                     (*nकरो_fill_क्रमward_path)(काष्ठा net_device_path_ctx *ctx,
                                                         काष्ठा net_device_path *path);
पूर्ण;

/**
 * क्रमागत netdev_priv_flags - &काष्ठा net_device priv_flags
 *
 * These are the &काष्ठा net_device, they are only set पूर्णांकernally
 * by drivers and used in the kernel. These flags are invisible to
 * userspace; this means that the order of these flags can change
 * during any kernel release.
 *
 * You should have a pretty good reason to be extending these flags.
 *
 * @IFF_802_1Q_VLAN: 802.1Q VLAN device
 * @IFF_EBRIDGE: Ethernet bridging device
 * @IFF_BONDING: bonding master or slave
 * @IFF_ISATAP: ISATAP पूर्णांकerface (RFC4214)
 * @IFF_WAN_HDLC: WAN HDLC device
 * @IFF_XMIT_DST_RELEASE: dev_hard_start_xmit() is allowed to
 *	release skb->dst
 * @IFF_DONT_BRIDGE: disallow bridging this ether dev
 * @IFF_DISABLE_NETPOLL: disable netpoll at run-समय
 * @IFF_MACVLAN_PORT: device used as macvlan port
 * @IFF_BRIDGE_PORT: device used as bridge port
 * @IFF_OVS_DATAPATH: device used as Open vSwitch datapath port
 * @IFF_TX_SKB_SHARING: The पूर्णांकerface supports sharing skbs on transmit
 * @IFF_UNICAST_FLT: Supports unicast filtering
 * @IFF_TEAM_PORT: device used as team port
 * @IFF_SUPP_NOFCS: device supports sending custom FCS
 * @IFF_LIVE_ADDR_CHANGE: device supports hardware address
 *	change when it's running
 * @IFF_MACVLAN: Macvlan device
 * @IFF_XMIT_DST_RELEASE_PERM: IFF_XMIT_DST_RELEASE not taking पूर्णांकo account
 *	underlying stacked devices
 * @IFF_L3MDEV_MASTER: device is an L3 master device
 * @IFF_NO_QUEUE: device can run without qdisc attached
 * @IFF_OPENVSWITCH: device is a Open vSwitch master
 * @IFF_L3MDEV_SLAVE: device is enslaved to an L3 master device
 * @IFF_TEAM: device is a team device
 * @IFF_RXFH_CONFIGURED: device has had Rx Flow indirection table configured
 * @IFF_PHONY_HEADROOM: the headroom value is controlled by an बाह्यal
 *	entity (i.e. the master device क्रम bridged veth)
 * @IFF_MACSEC: device is a MACsec device
 * @IFF_NO_RX_HANDLER: device करोesn't support the rx_handler hook
 * @IFF_FAILOVER: device is a failover master device
 * @IFF_FAILOVER_SLAVE: device is lower dev of a failover master device
 * @IFF_L3MDEV_RX_HANDLER: only invoke the rx handler of L3 master device
 * @IFF_LIVE_RENAME_OK: नाम is allowed जबतक device is up and running
 * @IFF_TX_SKB_NO_LINEAR: device/driver is capable of xmitting frames with
 *	skb_headlen(skb) == 0 (data starts from frag0)
 */
क्रमागत netdev_priv_flags अणु
	IFF_802_1Q_VLAN			= 1<<0,
	IFF_EBRIDGE			= 1<<1,
	IFF_BONDING			= 1<<2,
	IFF_ISATAP			= 1<<3,
	IFF_WAN_HDLC			= 1<<4,
	IFF_XMIT_DST_RELEASE		= 1<<5,
	IFF_DONT_BRIDGE			= 1<<6,
	IFF_DISABLE_NETPOLL		= 1<<7,
	IFF_MACVLAN_PORT		= 1<<8,
	IFF_BRIDGE_PORT			= 1<<9,
	IFF_OVS_DATAPATH		= 1<<10,
	IFF_TX_SKB_SHARING		= 1<<11,
	IFF_UNICAST_FLT			= 1<<12,
	IFF_TEAM_PORT			= 1<<13,
	IFF_SUPP_NOFCS			= 1<<14,
	IFF_LIVE_ADDR_CHANGE		= 1<<15,
	IFF_MACVLAN			= 1<<16,
	IFF_XMIT_DST_RELEASE_PERM	= 1<<17,
	IFF_L3MDEV_MASTER		= 1<<18,
	IFF_NO_QUEUE			= 1<<19,
	IFF_OPENVSWITCH			= 1<<20,
	IFF_L3MDEV_SLAVE		= 1<<21,
	IFF_TEAM			= 1<<22,
	IFF_RXFH_CONFIGURED		= 1<<23,
	IFF_PHONY_HEADROOM		= 1<<24,
	IFF_MACSEC			= 1<<25,
	IFF_NO_RX_HANDLER		= 1<<26,
	IFF_FAILOVER			= 1<<27,
	IFF_FAILOVER_SLAVE		= 1<<28,
	IFF_L3MDEV_RX_HANDLER		= 1<<29,
	IFF_LIVE_RENAME_OK		= 1<<30,
	IFF_TX_SKB_NO_LINEAR		= 1<<31,
पूर्ण;

#घोषणा IFF_802_1Q_VLAN			IFF_802_1Q_VLAN
#घोषणा IFF_EBRIDGE			IFF_EBRIDGE
#घोषणा IFF_BONDING			IFF_BONDING
#घोषणा IFF_ISATAP			IFF_ISATAP
#घोषणा IFF_WAN_HDLC			IFF_WAN_HDLC
#घोषणा IFF_XMIT_DST_RELEASE		IFF_XMIT_DST_RELEASE
#घोषणा IFF_DONT_BRIDGE			IFF_DONT_BRIDGE
#घोषणा IFF_DISABLE_NETPOLL		IFF_DISABLE_NETPOLL
#घोषणा IFF_MACVLAN_PORT		IFF_MACVLAN_PORT
#घोषणा IFF_BRIDGE_PORT			IFF_BRIDGE_PORT
#घोषणा IFF_OVS_DATAPATH		IFF_OVS_DATAPATH
#घोषणा IFF_TX_SKB_SHARING		IFF_TX_SKB_SHARING
#घोषणा IFF_UNICAST_FLT			IFF_UNICAST_FLT
#घोषणा IFF_TEAM_PORT			IFF_TEAM_PORT
#घोषणा IFF_SUPP_NOFCS			IFF_SUPP_NOFCS
#घोषणा IFF_LIVE_ADDR_CHANGE		IFF_LIVE_ADDR_CHANGE
#घोषणा IFF_MACVLAN			IFF_MACVLAN
#घोषणा IFF_XMIT_DST_RELEASE_PERM	IFF_XMIT_DST_RELEASE_PERM
#घोषणा IFF_L3MDEV_MASTER		IFF_L3MDEV_MASTER
#घोषणा IFF_NO_QUEUE			IFF_NO_QUEUE
#घोषणा IFF_OPENVSWITCH			IFF_OPENVSWITCH
#घोषणा IFF_L3MDEV_SLAVE		IFF_L3MDEV_SLAVE
#घोषणा IFF_TEAM			IFF_TEAM
#घोषणा IFF_RXFH_CONFIGURED		IFF_RXFH_CONFIGURED
#घोषणा IFF_PHONY_HEADROOM		IFF_PHONY_HEADROOM
#घोषणा IFF_MACSEC			IFF_MACSEC
#घोषणा IFF_NO_RX_HANDLER		IFF_NO_RX_HANDLER
#घोषणा IFF_FAILOVER			IFF_FAILOVER
#घोषणा IFF_FAILOVER_SLAVE		IFF_FAILOVER_SLAVE
#घोषणा IFF_L3MDEV_RX_HANDLER		IFF_L3MDEV_RX_HANDLER
#घोषणा IFF_LIVE_RENAME_OK		IFF_LIVE_RENAME_OK
#घोषणा IFF_TX_SKB_NO_LINEAR		IFF_TX_SKB_NO_LINEAR

/* Specअगरies the type of the काष्ठा net_device::ml_priv poपूर्णांकer */
क्रमागत netdev_ml_priv_type अणु
	ML_PRIV_NONE,
	ML_PRIV_CAN,
पूर्ण;

/**
 *	काष्ठा net_device - The DEVICE काष्ठाure.
 *
 *	Actually, this whole काष्ठाure is a big mistake.  It mixes I/O
 *	data with strictly "high-level" data, and it has to know about
 *	almost every data काष्ठाure used in the INET module.
 *
 *	@name:	This is the first field of the "visible" part of this काष्ठाure
 *		(i.e. as seen by users in the "Space.c" file).  It is the name
 *		of the पूर्णांकerface.
 *
 *	@name_node:	Name hashlist node
 *	@अगरalias:	SNMP alias
 *	@mem_end:	Shared memory end
 *	@mem_start:	Shared memory start
 *	@base_addr:	Device I/O address
 *	@irq:		Device IRQ number
 *
 *	@state:		Generic network queuing layer state, see netdev_state_t
 *	@dev_list:	The global list of network devices
 *	@napi_list:	List entry used क्रम polling NAPI devices
 *	@unreg_list:	List entry  when we are unरेजिस्टरing the
 *			device; see the function unरेजिस्टर_netdev
 *	@बंद_list:	List entry used when we are closing the device
 *	@ptype_all:     Device-specअगरic packet handlers क्रम all protocols
 *	@ptype_specअगरic: Device-specअगरic, protocol-specअगरic packet handlers
 *
 *	@adj_list:	Directly linked devices, like slaves क्रम bonding
 *	@features:	Currently active device features
 *	@hw_features:	User-changeable features
 *
 *	@wanted_features:	User-requested features
 *	@vlan_features:		Mask of features inheritable by VLAN devices
 *
 *	@hw_enc_features:	Mask of features inherited by encapsulating devices
 *				This field indicates what encapsulation
 *				offloads the hardware is capable of करोing,
 *				and drivers will need to set them appropriately.
 *
 *	@mpls_features:	Mask of features inheritable by MPLS
 *	@gso_partial_features: value(s) from NETIF_F_GSO\*
 *
 *	@अगरindex:	पूर्णांकerface index
 *	@group:		The group the device beदीर्घs to
 *
 *	@stats:		Statistics काष्ठा, which was left as a legacy, use
 *			rtnl_link_stats64 instead
 *
 *	@rx_dropped:	Dropped packets by core network,
 *			करो not use this in drivers
 *	@tx_dropped:	Dropped packets by core network,
 *			करो not use this in drivers
 *	@rx_nohandler:	nohandler dropped packets by core network on
 *			inactive devices, करो not use this in drivers
 *	@carrier_up_count:	Number of बार the carrier has been up
 *	@carrier_करोwn_count:	Number of बार the carrier has been करोwn
 *
 *	@wireless_handlers:	List of functions to handle Wireless Extensions,
 *				instead of ioctl,
 *				see <net/iw_handler.h> क्रम details.
 *	@wireless_data:	Instance data managed by the core of wireless extensions
 *
 *	@netdev_ops:	Includes several poपूर्णांकers to callbacks,
 *			अगर one wants to override the nकरो_*() functions
 *	@ethtool_ops:	Management operations
 *	@l3mdev_ops:	Layer 3 master device operations
 *	@ndisc_ops:	Includes callbacks क्रम dअगरferent IPv6 neighbour
 *			discovery handling. Necessary क्रम e.g. 6LoWPAN.
 *	@xfrmdev_ops:	Transक्रमmation offload operations
 *	@tlsdev_ops:	Transport Layer Security offload operations
 *	@header_ops:	Includes callbacks क्रम creating,parsing,caching,etc
 *			of Layer 2 headers.
 *
 *	@flags:		Interface flags (a la BSD)
 *	@priv_flags:	Like 'flags' but invisible to userspace,
 *			see अगर.h क्रम the definitions
 *	@gflags:	Global flags ( kept as legacy )
 *	@padded:	How much padding added by alloc_netdev()
 *	@operstate:	RFC2863 operstate
 *	@link_mode:	Mapping policy to operstate
 *	@अगर_port:	Selectable AUI, TP, ...
 *	@dma:		DMA channel
 *	@mtu:		Interface MTU value
 *	@min_mtu:	Interface Minimum MTU value
 *	@max_mtu:	Interface Maximum MTU value
 *	@type:		Interface hardware type
 *	@hard_header_len: Maximum hardware header length.
 *	@min_header_len:  Minimum hardware header length
 *
 *	@needed_headroom: Extra headroom the hardware may need, but not in all
 *			  हालs can this be guaranteed
 *	@needed_tailroom: Extra tailroom the hardware may need, but not in all
 *			  हालs can this be guaranteed. Some हालs also use
 *			  LL_MAX_HEADER instead to allocate the skb
 *
 *	पूर्णांकerface address info:
 *
 * 	@perm_addr:		Permanent hw address
 * 	@addr_assign_type:	Hw address assignment type
 * 	@addr_len:		Hardware address length
 *	@upper_level:		Maximum depth level of upper devices.
 *	@lower_level:		Maximum depth level of lower devices.
 *	@neigh_priv_len:	Used in neigh_alloc()
 * 	@dev_id:		Used to dअगरferentiate devices that share
 * 				the same link layer address
 * 	@dev_port:		Used to dअगरferentiate devices that share
 * 				the same function
 *	@addr_list_lock:	XXX: need comments on this one
 *	@name_assign_type:	network पूर्णांकerface name assignment type
 *	@uc_promisc:		Counter that indicates promiscuous mode
 *				has been enabled due to the need to listen to
 *				additional unicast addresses in a device that
 *				करोes not implement nकरो_set_rx_mode()
 *	@uc:			unicast mac addresses
 *	@mc:			multicast mac addresses
 *	@dev_addrs:		list of device hw addresses
 *	@queues_kset:		Group of all Kobjects in the Tx and RX queues
 *	@promiscuity:		Number of बार the NIC is told to work in
 *				promiscuous mode; अगर it becomes 0 the NIC will
 *				निकास promiscuous mode
 *	@allmulti:		Counter, enables or disables allmulticast mode
 *
 *	@vlan_info:	VLAN info
 *	@dsa_ptr:	dsa specअगरic data
 *	@tipc_ptr:	TIPC specअगरic data
 *	@atalk_ptr:	AppleTalk link
 *	@ip_ptr:	IPv4 specअगरic data
 *	@dn_ptr:	DECnet specअगरic data
 *	@ip6_ptr:	IPv6 specअगरic data
 *	@ax25_ptr:	AX.25 specअगरic data
 *	@ieee80211_ptr:	IEEE 802.11 specअगरic data, assign beक्रमe रेजिस्टरing
 *	@ieee802154_ptr: IEEE 802.15.4 low-rate Wireless Personal Area Network
 *			 device काष्ठा
 *	@mpls_ptr:	mpls_dev काष्ठा poपूर्णांकer
 *
 *	@dev_addr:	Hw address (beक्रमe bcast,
 *			because most packets are unicast)
 *
 *	@_rx:			Array of RX queues
 *	@num_rx_queues:		Number of RX queues
 *				allocated at रेजिस्टर_netdev() समय
 *	@real_num_rx_queues: 	Number of RX queues currently active in device
 *	@xdp_prog:		XDP sockets filter program poपूर्णांकer
 *	@gro_flush_समयout:	समयout क्रम GRO layer in NAPI
 *	@napi_defer_hard_irqs:	If not zero, provides a counter that would
 *				allow to aव्योम NIC hard IRQ, on busy queues.
 *
 *	@rx_handler:		handler क्रम received packets
 *	@rx_handler_data: 	XXX: need comments on this one
 *	@miniq_ingress:		ingress/clsact qdisc specअगरic data क्रम
 *				ingress processing
 *	@ingress_queue:		XXX: need comments on this one
 *	@nf_hooks_ingress:	netfilter hooks executed क्रम ingress packets
 *	@broadcast:		hw bcast address
 *
 *	@rx_cpu_rmap:	CPU reverse-mapping क्रम RX completion पूर्णांकerrupts,
 *			indexed by RX queue number. Asचिन्हित by driver.
 *			This must only be set अगर the nकरो_rx_flow_steer
 *			operation is defined
 *	@index_hlist:		Device index hash chain
 *
 *	@_tx:			Array of TX queues
 *	@num_tx_queues:		Number of TX queues allocated at alloc_netdev_mq() समय
 *	@real_num_tx_queues: 	Number of TX queues currently active in device
 *	@qdisc:			Root qdisc from userspace poपूर्णांक of view
 *	@tx_queue_len:		Max frames per queue allowed
 *	@tx_global_lock: 	XXX: need comments on this one
 *	@xdp_bulkq:		XDP device bulk queue
 *	@xps_maps:		all CPUs/RXQs maps क्रम XPS device
 *
 *	@xps_maps:	XXX: need comments on this one
 *	@miniq_egress:		clsact qdisc specअगरic data क्रम
 *				egress processing
 *	@qdisc_hash:		qdisc hash table
 *	@watchकरोg_समयo:	Represents the समयout that is used by
 *				the watchकरोg (see dev_watchकरोg())
 *	@watchकरोg_समयr:	List of समयrs
 *
 *	@proto_करोwn_reason:	reason a netdev पूर्णांकerface is held करोwn
 *	@pcpu_refcnt:		Number of references to this device
 *	@dev_refcnt:		Number of references to this device
 *	@toकरो_list:		Delayed रेजिस्टर/unरेजिस्टर
 *	@link_watch_list:	XXX: need comments on this one
 *
 *	@reg_state:		Register/unरेजिस्टर state machine
 *	@dismantle:		Device is going to be मुक्तd
 *	@rtnl_link_state:	This क्रमागत represents the phases of creating
 *				a new link
 *
 *	@needs_मुक्त_netdev:	Should unरेजिस्टर perक्रमm मुक्त_netdev?
 *	@priv_deकाष्ठाor:	Called from unरेजिस्टर
 *	@npinfo:		XXX: need comments on this one
 * 	@nd_net:		Network namespace this network device is inside
 *
 * 	@ml_priv:	Mid-layer निजी
 *	@ml_priv_type:  Mid-layer निजी type
 * 	@lstats:	Loopback statistics
 * 	@tstats:	Tunnel statistics
 * 	@dstats:	Dummy statistics
 * 	@vstats:	Virtual ethernet statistics
 *
 *	@garp_port:	GARP
 *	@mrp_port:	MRP
 *
 *	@dev:		Class/net/name entry
 *	@sysfs_groups:	Space क्रम optional device, statistics and wireless
 *			sysfs groups
 *
 *	@sysfs_rx_queue_group:	Space क्रम optional per-rx queue attributes
 *	@rtnl_link_ops:	Rtnl_link_ops
 *
 *	@gso_max_size:	Maximum size of generic segmentation offload
 *	@gso_max_segs:	Maximum number of segments that can be passed to the
 *			NIC क्रम GSO
 *
 *	@dcbnl_ops:	Data Center Bridging netlink ops
 *	@num_tc:	Number of traffic classes in the net device
 *	@tc_to_txq:	XXX: need comments on this one
 *	@prio_tc_map:	XXX: need comments on this one
 *
 *	@fcoe_ddp_xid:	Max exchange id क्रम FCoE LRO by ddp
 *
 *	@priomap:	XXX: need comments on this one
 *	@phydev:	Physical device may attach itself
 *			क्रम hardware बारtamping
 *	@sfp_bus:	attached &काष्ठा sfp_bus काष्ठाure.
 *
 *	@qdisc_tx_busylock: lockdep class annotating Qdisc->busylock spinlock
 *	@qdisc_running_key: lockdep class annotating Qdisc->running seqcount
 *
 *	@proto_करोwn:	protocol port state inक्रमmation can be sent to the
 *			चयन driver and used to set the phys state of the
 *			चयन port.
 *
 *	@wol_enabled:	Wake-on-LAN is enabled
 *
 *	@thपढ़ोed:	napi thपढ़ोed mode is enabled
 *
 *	@net_notअगरier_list:	List of per-net netdev notअगरier block
 *				that follow this device when it is moved
 *				to another network namespace.
 *
 *	@macsec_ops:    MACsec offloading ops
 *
 *	@udp_tunnel_nic_info:	अटल काष्ठाure describing the UDP tunnel
 *				offload capabilities of the device
 *	@udp_tunnel_nic:	UDP tunnel offload state
 *	@xdp_state:		stores info on attached XDP BPF programs
 *
 *	@nested_level:	Used as as a parameter of spin_lock_nested() of
 *			dev->addr_list_lock.
 *	@unlink_list:	As netअगर_addr_lock() can be called recursively,
 *			keep a list of पूर्णांकerfaces to be deleted.
 *
 *	FIXME: cleanup काष्ठा net_device such that network protocol info
 *	moves out.
 */

काष्ठा net_device अणु
	अक्षर			name[IFNAMSIZ];
	काष्ठा netdev_name_node	*name_node;
	काष्ठा dev_अगरalias	__rcu *अगरalias;
	/*
	 *	I/O specअगरic fields
	 *	FIXME: Merge these and काष्ठा अगरmap पूर्णांकo one
	 */
	अचिन्हित दीर्घ		mem_end;
	अचिन्हित दीर्घ		mem_start;
	अचिन्हित दीर्घ		base_addr;

	/*
	 *	Some hardware also needs these fields (state,dev_list,
	 *	napi_list,unreg_list,बंद_list) but they are not
	 *	part of the usual set specअगरied in Space.c.
	 */

	अचिन्हित दीर्घ		state;

	काष्ठा list_head	dev_list;
	काष्ठा list_head	napi_list;
	काष्ठा list_head	unreg_list;
	काष्ठा list_head	बंद_list;
	काष्ठा list_head	ptype_all;
	काष्ठा list_head	ptype_specअगरic;

	काष्ठा अणु
		काष्ठा list_head upper;
		काष्ठा list_head lower;
	पूर्ण adj_list;

	/* Read-mostly cache-line क्रम fast-path access */
	अचिन्हित पूर्णांक		flags;
	अचिन्हित पूर्णांक		priv_flags;
	स्थिर काष्ठा net_device_ops *netdev_ops;
	पूर्णांक			अगरindex;
	अचिन्हित लघु		gflags;
	अचिन्हित लघु		hard_header_len;

	/* Note : dev->mtu is often पढ़ो without holding a lock.
	 * Writers usually hold RTNL.
	 * It is recommended to use READ_ONCE() to annotate the पढ़ोs,
	 * and to use WRITE_ONCE() to annotate the ग_लिखोs.
	 */
	अचिन्हित पूर्णांक		mtu;
	अचिन्हित लघु		needed_headroom;
	अचिन्हित लघु		needed_tailroom;

	netdev_features_t	features;
	netdev_features_t	hw_features;
	netdev_features_t	wanted_features;
	netdev_features_t	vlan_features;
	netdev_features_t	hw_enc_features;
	netdev_features_t	mpls_features;
	netdev_features_t	gso_partial_features;

	अचिन्हित पूर्णांक		min_mtu;
	अचिन्हित पूर्णांक		max_mtu;
	अचिन्हित लघु		type;
	अचिन्हित अक्षर		min_header_len;
	अचिन्हित अक्षर		name_assign_type;

	पूर्णांक			group;

	काष्ठा net_device_stats	stats; /* not used by modern drivers */

	atomic_दीर्घ_t		rx_dropped;
	atomic_दीर्घ_t		tx_dropped;
	atomic_दीर्घ_t		rx_nohandler;

	/* Stats to monitor link on/off, flapping */
	atomic_t		carrier_up_count;
	atomic_t		carrier_करोwn_count;

#अगर_घोषित CONFIG_WIRELESS_EXT
	स्थिर काष्ठा iw_handler_def *wireless_handlers;
	काष्ठा iw_खुला_data	*wireless_data;
#पूर्ण_अगर
	स्थिर काष्ठा ethtool_ops *ethtool_ops;
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	स्थिर काष्ठा l3mdev_ops	*l3mdev_ops;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	स्थिर काष्ठा ndisc_ops *ndisc_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFRM_OFFLOAD
	स्थिर काष्ठा xfrmdev_ops *xfrmdev_ops;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
	स्थिर काष्ठा tlsdev_ops *tlsdev_ops;
#पूर्ण_अगर

	स्थिर काष्ठा header_ops *header_ops;

	अचिन्हित अक्षर		operstate;
	अचिन्हित अक्षर		link_mode;

	अचिन्हित अक्षर		अगर_port;
	अचिन्हित अक्षर		dma;

	/* Interface address info. */
	अचिन्हित अक्षर		perm_addr[MAX_ADDR_LEN];
	अचिन्हित अक्षर		addr_assign_type;
	अचिन्हित अक्षर		addr_len;
	अचिन्हित अक्षर		upper_level;
	अचिन्हित अक्षर		lower_level;

	अचिन्हित लघु		neigh_priv_len;
	अचिन्हित लघु          dev_id;
	अचिन्हित लघु          dev_port;
	अचिन्हित लघु		padded;

	spinlock_t		addr_list_lock;
	पूर्णांक			irq;

	काष्ठा netdev_hw_addr_list	uc;
	काष्ठा netdev_hw_addr_list	mc;
	काष्ठा netdev_hw_addr_list	dev_addrs;

#अगर_घोषित CONFIG_SYSFS
	काष्ठा kset		*queues_kset;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOCKDEP
	काष्ठा list_head	unlink_list;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		promiscuity;
	अचिन्हित पूर्णांक		allmulti;
	bool			uc_promisc;
#अगर_घोषित CONFIG_LOCKDEP
	अचिन्हित अक्षर		nested_level;
#पूर्ण_अगर


	/* Protocol-specअगरic poपूर्णांकers */

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	काष्ठा vlan_info __rcu	*vlan_info;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_DSA)
	काष्ठा dsa_port		*dsa_ptr;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_TIPC)
	काष्ठा tipc_bearer __rcu *tipc_ptr;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IRDA) || IS_ENABLED(CONFIG_ATALK)
	व्योम 			*atalk_ptr;
#पूर्ण_अगर
	काष्ठा in_device __rcu	*ip_ptr;
#अगर IS_ENABLED(CONFIG_DECNET)
	काष्ठा dn_dev __rcu     *dn_ptr;
#पूर्ण_अगर
	काष्ठा inet6_dev __rcu	*ip6_ptr;
#अगर IS_ENABLED(CONFIG_AX25)
	व्योम			*ax25_ptr;
#पूर्ण_अगर
	काष्ठा wireless_dev	*ieee80211_ptr;
	काष्ठा wpan_dev		*ieee802154_ptr;
#अगर IS_ENABLED(CONFIG_MPLS_ROUTING)
	काष्ठा mpls_dev __rcu	*mpls_ptr;
#पूर्ण_अगर

/*
 * Cache lines mostly used on receive path (including eth_type_trans())
 */
	/* Interface address info used in eth_type_trans() */
	अचिन्हित अक्षर		*dev_addr;

	काष्ठा netdev_rx_queue	*_rx;
	अचिन्हित पूर्णांक		num_rx_queues;
	अचिन्हित पूर्णांक		real_num_rx_queues;

	काष्ठा bpf_prog __rcu	*xdp_prog;
	अचिन्हित दीर्घ		gro_flush_समयout;
	पूर्णांक			napi_defer_hard_irqs;
	rx_handler_func_t __rcu	*rx_handler;
	व्योम __rcu		*rx_handler_data;

#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा mini_Qdisc __rcu	*miniq_ingress;
#पूर्ण_अगर
	काष्ठा netdev_queue __rcu *ingress_queue;
#अगर_घोषित CONFIG_NETFILTER_INGRESS
	काष्ठा nf_hook_entries __rcu *nf_hooks_ingress;
#पूर्ण_अगर

	अचिन्हित अक्षर		broadcast[MAX_ADDR_LEN];
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा cpu_rmap		*rx_cpu_rmap;
#पूर्ण_अगर
	काष्ठा hlist_node	index_hlist;

/*
 * Cache lines mostly used on transmit path
 */
	काष्ठा netdev_queue	*_tx ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक		num_tx_queues;
	अचिन्हित पूर्णांक		real_num_tx_queues;
	काष्ठा Qdisc		*qdisc;
	अचिन्हित पूर्णांक		tx_queue_len;
	spinlock_t		tx_global_lock;

	काष्ठा xdp_dev_bulk_queue __percpu *xdp_bulkq;

#अगर_घोषित CONFIG_XPS
	काष्ठा xps_dev_maps __rcu *xps_maps[XPS_MAPS_MAX];
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_CLS_ACT
	काष्ठा mini_Qdisc __rcu	*miniq_egress;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_SCHED
	DECLARE_HASHTABLE	(qdisc_hash, 4);
#पूर्ण_अगर
	/* These may be needed क्रम future network-घातer-करोwn code. */
	काष्ठा समयr_list	watchकरोg_समयr;
	पूर्णांक			watchकरोg_समयo;

	u32                     proto_करोwn_reason;

	काष्ठा list_head	toकरो_list;

#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	पूर्णांक __percpu		*pcpu_refcnt;
#अन्यथा
	refcount_t		dev_refcnt;
#पूर्ण_अगर

	काष्ठा list_head	link_watch_list;

	क्रमागत अणु NETREG_UNINITIALIZED=0,
	       NETREG_REGISTERED,	/* completed रेजिस्टर_netdevice */
	       NETREG_UNREGISTERING,	/* called unरेजिस्टर_netdevice */
	       NETREG_UNREGISTERED,	/* completed unरेजिस्टर toकरो */
	       NETREG_RELEASED,		/* called मुक्त_netdev */
	       NETREG_DUMMY,		/* dummy device क्रम NAPI poll */
	पूर्ण reg_state:8;

	bool dismantle;

	क्रमागत अणु
		RTNL_LINK_INITIALIZED,
		RTNL_LINK_INITIALIZING,
	पूर्ण rtnl_link_state:16;

	bool needs_मुक्त_netdev;
	व्योम (*priv_deकाष्ठाor)(काष्ठा net_device *dev);

#अगर_घोषित CONFIG_NETPOLL
	काष्ठा netpoll_info __rcu	*npinfo;
#पूर्ण_अगर

	possible_net_t			nd_net;

	/* mid-layer निजी */
	व्योम				*ml_priv;
	क्रमागत netdev_ml_priv_type	ml_priv_type;

	जोड़ अणु
		काष्ठा pcpu_lstats __percpu		*lstats;
		काष्ठा pcpu_sw_netstats __percpu	*tstats;
		काष्ठा pcpu_dstats __percpu		*dstats;
	पूर्ण;

#अगर IS_ENABLED(CONFIG_GARP)
	काष्ठा garp_port __rcu	*garp_port;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MRP)
	काष्ठा mrp_port __rcu	*mrp_port;
#पूर्ण_अगर

	काष्ठा device		dev;
	स्थिर काष्ठा attribute_group *sysfs_groups[4];
	स्थिर काष्ठा attribute_group *sysfs_rx_queue_group;

	स्थिर काष्ठा rtnl_link_ops *rtnl_link_ops;

	/* क्रम setting kernel sock attribute on TCP connection setup */
#घोषणा GSO_MAX_SIZE		65536
	अचिन्हित पूर्णांक		gso_max_size;
#घोषणा GSO_MAX_SEGS		65535
	u16			gso_max_segs;

#अगर_घोषित CONFIG_DCB
	स्थिर काष्ठा dcbnl_rtnl_ops *dcbnl_ops;
#पूर्ण_अगर
	s16			num_tc;
	काष्ठा netdev_tc_txq	tc_to_txq[TC_MAX_QUEUE];
	u8			prio_tc_map[TC_BITMASK + 1];

#अगर IS_ENABLED(CONFIG_FCOE)
	अचिन्हित पूर्णांक		fcoe_ddp_xid;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CGROUP_NET_PRIO)
	काष्ठा netprio_map __rcu *priomap;
#पूर्ण_अगर
	काष्ठा phy_device	*phydev;
	काष्ठा sfp_bus		*sfp_bus;
	काष्ठा lock_class_key	*qdisc_tx_busylock;
	काष्ठा lock_class_key	*qdisc_running_key;
	bool			proto_करोwn;
	अचिन्हित		wol_enabled:1;
	अचिन्हित		thपढ़ोed:1;

	काष्ठा list_head	net_notअगरier_list;

#अगर IS_ENABLED(CONFIG_MACSEC)
	/* MACsec management functions */
	स्थिर काष्ठा macsec_ops *macsec_ops;
#पूर्ण_अगर
	स्थिर काष्ठा udp_tunnel_nic_info	*udp_tunnel_nic_info;
	काष्ठा udp_tunnel_nic	*udp_tunnel_nic;

	/* रक्षित by rtnl_lock */
	काष्ठा bpf_xdp_entity	xdp_state[__MAX_XDP_MODE];
पूर्ण;
#घोषणा to_net_dev(d) container_of(d, काष्ठा net_device, dev)

अटल अंतरभूत bool netअगर_elide_gro(स्थिर काष्ठा net_device *dev)
अणु
	अगर (!(dev->features & NETIF_F_GRO) || dev->xdp_prog)
		वापस true;
	वापस false;
पूर्ण

#घोषणा	NETDEV_ALIGN		32

अटल अंतरभूत
पूर्णांक netdev_get_prio_tc_map(स्थिर काष्ठा net_device *dev, u32 prio)
अणु
	वापस dev->prio_tc_map[prio & TC_BITMASK];
पूर्ण

अटल अंतरभूत
पूर्णांक netdev_set_prio_tc_map(काष्ठा net_device *dev, u8 prio, u8 tc)
अणु
	अगर (tc >= dev->num_tc)
		वापस -EINVAL;

	dev->prio_tc_map[prio & TC_BITMASK] = tc & TC_BITMASK;
	वापस 0;
पूर्ण

पूर्णांक netdev_txq_to_tc(काष्ठा net_device *dev, अचिन्हित पूर्णांक txq);
व्योम netdev_reset_tc(काष्ठा net_device *dev);
पूर्णांक netdev_set_tc_queue(काष्ठा net_device *dev, u8 tc, u16 count, u16 offset);
पूर्णांक netdev_set_num_tc(काष्ठा net_device *dev, u8 num_tc);

अटल अंतरभूत
पूर्णांक netdev_get_num_tc(काष्ठा net_device *dev)
अणु
	वापस dev->num_tc;
पूर्ण

अटल अंतरभूत व्योम net_prefetch(व्योम *p)
अणु
	prefetch(p);
#अगर L1_CACHE_BYTES < 128
	prefetch((u8 *)p + L1_CACHE_BYTES);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम net_prefetchw(व्योम *p)
अणु
	prefetchw(p);
#अगर L1_CACHE_BYTES < 128
	prefetchw((u8 *)p + L1_CACHE_BYTES);
#पूर्ण_अगर
पूर्ण

व्योम netdev_unbind_sb_channel(काष्ठा net_device *dev,
			      काष्ठा net_device *sb_dev);
पूर्णांक netdev_bind_sb_channel_queue(काष्ठा net_device *dev,
				 काष्ठा net_device *sb_dev,
				 u8 tc, u16 count, u16 offset);
पूर्णांक netdev_set_sb_channel(काष्ठा net_device *dev, u16 channel);
अटल अंतरभूत पूर्णांक netdev_get_sb_channel(काष्ठा net_device *dev)
अणु
	वापस max_t(पूर्णांक, -dev->num_tc, 0);
पूर्ण

अटल अंतरभूत
काष्ठा netdev_queue *netdev_get_tx_queue(स्थिर काष्ठा net_device *dev,
					 अचिन्हित पूर्णांक index)
अणु
	वापस &dev->_tx[index];
पूर्ण

अटल अंतरभूत काष्ठा netdev_queue *skb_get_tx_queue(स्थिर काष्ठा net_device *dev,
						    स्थिर काष्ठा sk_buff *skb)
अणु
	वापस netdev_get_tx_queue(dev, skb_get_queue_mapping(skb));
पूर्ण

अटल अंतरभूत व्योम netdev_क्रम_each_tx_queue(काष्ठा net_device *dev,
					    व्योम (*f)(काष्ठा net_device *,
						      काष्ठा netdev_queue *,
						      व्योम *),
					    व्योम *arg)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++)
		f(dev, &dev->_tx[i], arg);
पूर्ण

#घोषणा netdev_lockdep_set_classes(dev)				\
अणु								\
	अटल काष्ठा lock_class_key qdisc_tx_busylock_key;	\
	अटल काष्ठा lock_class_key qdisc_running_key;		\
	अटल काष्ठा lock_class_key qdisc_xmit_lock_key;	\
	अटल काष्ठा lock_class_key dev_addr_list_lock_key;	\
	अचिन्हित पूर्णांक i;						\
								\
	(dev)->qdisc_tx_busylock = &qdisc_tx_busylock_key;	\
	(dev)->qdisc_running_key = &qdisc_running_key;		\
	lockdep_set_class(&(dev)->addr_list_lock,		\
			  &dev_addr_list_lock_key);		\
	क्रम (i = 0; i < (dev)->num_tx_queues; i++)		\
		lockdep_set_class(&(dev)->_tx[i]._xmit_lock,	\
				  &qdisc_xmit_lock_key);	\
पूर्ण

u16 netdev_pick_tx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		     काष्ठा net_device *sb_dev);
काष्ठा netdev_queue *netdev_core_pick_tx(काष्ठा net_device *dev,
					 काष्ठा sk_buff *skb,
					 काष्ठा net_device *sb_dev);

/* वापसs the headroom that the master device needs to take in account
 * when क्रमwarding to this dev
 */
अटल अंतरभूत अचिन्हित netdev_get_fwd_headroom(काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_PHONY_HEADROOM ? 0 : dev->needed_headroom;
पूर्ण

अटल अंतरभूत व्योम netdev_set_rx_headroom(काष्ठा net_device *dev, पूर्णांक new_hr)
अणु
	अगर (dev->netdev_ops->nकरो_set_rx_headroom)
		dev->netdev_ops->nकरो_set_rx_headroom(dev, new_hr);
पूर्ण

/* set the device rx headroom to the dev's शेष */
अटल अंतरभूत व्योम netdev_reset_rx_headroom(काष्ठा net_device *dev)
अणु
	netdev_set_rx_headroom(dev, -1);
पूर्ण

अटल अंतरभूत व्योम *netdev_get_ml_priv(काष्ठा net_device *dev,
				       क्रमागत netdev_ml_priv_type type)
अणु
	अगर (dev->ml_priv_type != type)
		वापस शून्य;

	वापस dev->ml_priv;
पूर्ण

अटल अंतरभूत व्योम netdev_set_ml_priv(काष्ठा net_device *dev,
				      व्योम *ml_priv,
				      क्रमागत netdev_ml_priv_type type)
अणु
	WARN(dev->ml_priv_type && dev->ml_priv_type != type,
	     "Overwriting already set ml_priv_type (%u) with different ml_priv_type (%u)!\n",
	     dev->ml_priv_type, type);
	WARN(!dev->ml_priv_type && dev->ml_priv,
	     "Overwriting already set ml_priv and ml_priv_type is ML_PRIV_NONE!\n");

	dev->ml_priv = ml_priv;
	dev->ml_priv_type = type;
पूर्ण

/*
 * Net namespace अंतरभूतs
 */
अटल अंतरभूत
काष्ठा net *dev_net(स्थिर काष्ठा net_device *dev)
अणु
	वापस पढ़ो_pnet(&dev->nd_net);
पूर्ण

अटल अंतरभूत
व्योम dev_net_set(काष्ठा net_device *dev, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&dev->nd_net, net);
पूर्ण

/**
 *	netdev_priv - access network device निजी data
 *	@dev: network device
 *
 * Get network device निजी data
 */
अटल अंतरभूत व्योम *netdev_priv(स्थिर काष्ठा net_device *dev)
अणु
	वापस (अक्षर *)dev + ALIGN(माप(काष्ठा net_device), NETDEV_ALIGN);
पूर्ण

/* Set the sysfs physical device reference क्रम the network logical device
 * अगर set prior to registration will cause a symlink during initialization.
 */
#घोषणा SET_NETDEV_DEV(net, pdev)	((net)->dev.parent = (pdev))

/* Set the sysfs device type क्रम the network logical device to allow
 * fine-grained identअगरication of dअगरferent network device types. For
 * example Ethernet, Wireless LAN, Bluetooth, WiMAX etc.
 */
#घोषणा SET_NETDEV_DEVTYPE(net, devtype)	((net)->dev.type = (devtype))

/* Default NAPI poll() weight
 * Device drivers are strongly advised to not use bigger value
 */
#घोषणा NAPI_POLL_WEIGHT 64

/**
 *	netअगर_napi_add - initialize a NAPI context
 *	@dev:  network device
 *	@napi: NAPI context
 *	@poll: polling function
 *	@weight: शेष weight
 *
 * netअगर_napi_add() must be used to initialize a NAPI context prior to calling
 * *any* of the other NAPI-related functions.
 */
व्योम netअगर_napi_add(काष्ठा net_device *dev, काष्ठा napi_काष्ठा *napi,
		    पूर्णांक (*poll)(काष्ठा napi_काष्ठा *, पूर्णांक), पूर्णांक weight);

/**
 *	netअगर_tx_napi_add - initialize a NAPI context
 *	@dev:  network device
 *	@napi: NAPI context
 *	@poll: polling function
 *	@weight: शेष weight
 *
 * This variant of netअगर_napi_add() should be used from drivers using NAPI
 * to exclusively poll a TX queue.
 * This will aव्योम we add it पूर्णांकo napi_hash[], thus polluting this hash table.
 */
अटल अंतरभूत व्योम netअगर_tx_napi_add(काष्ठा net_device *dev,
				     काष्ठा napi_काष्ठा *napi,
				     पूर्णांक (*poll)(काष्ठा napi_काष्ठा *, पूर्णांक),
				     पूर्णांक weight)
अणु
	set_bit(NAPI_STATE_NO_BUSY_POLL, &napi->state);
	netअगर_napi_add(dev, napi, poll, weight);
पूर्ण

/**
 *  __netअगर_napi_del - हटाओ a NAPI context
 *  @napi: NAPI context
 *
 * Warning: caller must observe RCU grace period beक्रमe मुक्तing memory
 * containing @napi. Drivers might want to call this helper to combine
 * all the needed RCU grace periods पूर्णांकo a single one.
 */
व्योम __netअगर_napi_del(काष्ठा napi_काष्ठा *napi);

/**
 *  netअगर_napi_del - हटाओ a NAPI context
 *  @napi: NAPI context
 *
 *  netअगर_napi_del() हटाओs a NAPI context from the network device NAPI list
 */
अटल अंतरभूत व्योम netअगर_napi_del(काष्ठा napi_काष्ठा *napi)
अणु
	__netअगर_napi_del(napi);
	synchronize_net();
पूर्ण

काष्ठा napi_gro_cb अणु
	/* Virtual address of skb_shinfo(skb)->frags[0].page + offset. */
	व्योम	*frag0;

	/* Length of frag0. */
	अचिन्हित पूर्णांक frag0_len;

	/* This indicates where we are processing relative to skb->data. */
	पूर्णांक	data_offset;

	/* This is non-zero अगर the packet cannot be merged with the new skb. */
	u16	flush;

	/* Save the IP ID here and check when we get to the transport layer */
	u16	flush_id;

	/* Number of segments aggregated. */
	u16	count;

	/* Start offset क्रम remote checksum offload */
	u16	gro_remcsum_start;

	/* jअगरfies when first packet was created/queued */
	अचिन्हित दीर्घ age;

	/* Used in ipv6_gro_receive() and foo-over-udp */
	u16	proto;

	/* This is non-zero अगर the packet may be of the same flow. */
	u8	same_flow:1;

	/* Used in tunnel GRO receive */
	u8	encap_mark:1;

	/* GRO checksum is valid */
	u8	csum_valid:1;

	/* Number of checksums via CHECKSUM_UNNECESSARY */
	u8	csum_cnt:3;

	/* Free the skb? */
	u8	मुक्त:2;
#घोषणा NAPI_GRO_FREE		  1
#घोषणा NAPI_GRO_FREE_STOLEN_HEAD 2

	/* Used in foo-over-udp, set in udp[46]_gro_receive */
	u8	is_ipv6:1;

	/* Used in GRE, set in fou/gue_gro_receive */
	u8	is_fou:1;

	/* Used to determine अगर flush_id can be ignored */
	u8	is_atomic:1;

	/* Number of gro_receive callbacks this packet alपढ़ोy went through */
	u8 recursion_counter:4;

	/* GRO is करोne by frag_list poपूर्णांकer chaining. */
	u8	is_flist:1;

	/* used to support CHECKSUM_COMPLETE क्रम tunneling protocols */
	__wsum	csum;

	/* used in skb_gro_receive() slow path */
	काष्ठा sk_buff *last;
पूर्ण;

#घोषणा NAPI_GRO_CB(skb) ((काष्ठा napi_gro_cb *)(skb)->cb)

#घोषणा GRO_RECURSION_LIMIT 15
अटल अंतरभूत पूर्णांक gro_recursion_inc_test(काष्ठा sk_buff *skb)
अणु
	वापस ++NAPI_GRO_CB(skb)->recursion_counter == GRO_RECURSION_LIMIT;
पूर्ण

प्रकार काष्ठा sk_buff *(*gro_receive_t)(काष्ठा list_head *, काष्ठा sk_buff *);
अटल अंतरभूत काष्ठा sk_buff *call_gro_receive(gro_receive_t cb,
					       काष्ठा list_head *head,
					       काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(gro_recursion_inc_test(skb))) अणु
		NAPI_GRO_CB(skb)->flush |= 1;
		वापस शून्य;
	पूर्ण

	वापस cb(head, skb);
पूर्ण

प्रकार काष्ठा sk_buff *(*gro_receive_sk_t)(काष्ठा sock *, काष्ठा list_head *,
					    काष्ठा sk_buff *);
अटल अंतरभूत काष्ठा sk_buff *call_gro_receive_sk(gro_receive_sk_t cb,
						  काष्ठा sock *sk,
						  काष्ठा list_head *head,
						  काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(gro_recursion_inc_test(skb))) अणु
		NAPI_GRO_CB(skb)->flush |= 1;
		वापस शून्य;
	पूर्ण

	वापस cb(sk, head, skb);
पूर्ण

काष्ठा packet_type अणु
	__be16			type;	/* This is really htons(ether_type). */
	bool			ignore_outgoing;
	काष्ठा net_device	*dev;	/* शून्य is wildcarded here	     */
	पूर्णांक			(*func) (काष्ठा sk_buff *,
					 काष्ठा net_device *,
					 काष्ठा packet_type *,
					 काष्ठा net_device *);
	व्योम			(*list_func) (काष्ठा list_head *,
					      काष्ठा packet_type *,
					      काष्ठा net_device *);
	bool			(*id_match)(काष्ठा packet_type *ptype,
					    काष्ठा sock *sk);
	व्योम			*af_packet_priv;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा offload_callbacks अणु
	काष्ठा sk_buff		*(*gso_segment)(काष्ठा sk_buff *skb,
						netdev_features_t features);
	काष्ठा sk_buff		*(*gro_receive)(काष्ठा list_head *head,
						काष्ठा sk_buff *skb);
	पूर्णांक			(*gro_complete)(काष्ठा sk_buff *skb, पूर्णांक nhoff);
पूर्ण;

काष्ठा packet_offload अणु
	__be16			 type;	/* This is really htons(ether_type). */
	u16			 priority;
	काष्ठा offload_callbacks callbacks;
	काष्ठा list_head	 list;
पूर्ण;

/* often modअगरied stats are per-CPU, other are shared (netdev->stats) */
काष्ठा pcpu_sw_netstats अणु
	u64     rx_packets;
	u64     rx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
	काष्ठा u64_stats_sync   syncp;
पूर्ण __aligned(4 * माप(u64));

काष्ठा pcpu_lstats अणु
	u64_stats_t packets;
	u64_stats_t bytes;
	काष्ठा u64_stats_sync syncp;
पूर्ण __aligned(2 * माप(u64));

व्योम dev_lstats_पढ़ो(काष्ठा net_device *dev, u64 *packets, u64 *bytes);

अटल अंतरभूत व्योम dev_sw_netstats_rx_add(काष्ठा net_device *dev, अचिन्हित पूर्णांक len)
अणु
	काष्ठा pcpu_sw_netstats *tstats = this_cpu_ptr(dev->tstats);

	u64_stats_update_begin(&tstats->syncp);
	tstats->rx_bytes += len;
	tstats->rx_packets++;
	u64_stats_update_end(&tstats->syncp);
पूर्ण

अटल अंतरभूत व्योम dev_sw_netstats_tx_add(काष्ठा net_device *dev,
					  अचिन्हित पूर्णांक packets,
					  अचिन्हित पूर्णांक len)
अणु
	काष्ठा pcpu_sw_netstats *tstats = this_cpu_ptr(dev->tstats);

	u64_stats_update_begin(&tstats->syncp);
	tstats->tx_bytes += len;
	tstats->tx_packets += packets;
	u64_stats_update_end(&tstats->syncp);
पूर्ण

अटल अंतरभूत व्योम dev_lstats_add(काष्ठा net_device *dev, अचिन्हित पूर्णांक len)
अणु
	काष्ठा pcpu_lstats *lstats = this_cpu_ptr(dev->lstats);

	u64_stats_update_begin(&lstats->syncp);
	u64_stats_add(&lstats->bytes, len);
	u64_stats_inc(&lstats->packets);
	u64_stats_update_end(&lstats->syncp);
पूर्ण

#घोषणा __netdev_alloc_pcpu_stats(type, gfp)				\
(अणु									\
	typeof(type) __percpu *pcpu_stats = alloc_percpu_gfp(type, gfp);\
	अगर (pcpu_stats)	अणु						\
		पूर्णांक __cpu;						\
		क्रम_each_possible_cpu(__cpu) अणु				\
			typeof(type) *stat;				\
			stat = per_cpu_ptr(pcpu_stats, __cpu);		\
			u64_stats_init(&stat->syncp);			\
		पूर्ण							\
	पूर्ण								\
	pcpu_stats;							\
पूर्ण)

#घोषणा netdev_alloc_pcpu_stats(type)					\
	__netdev_alloc_pcpu_stats(type, GFP_KERNEL)

#घोषणा devm_netdev_alloc_pcpu_stats(dev, type)				\
(अणु									\
	typeof(type) __percpu *pcpu_stats = devm_alloc_percpu(dev, type);\
	अगर (pcpu_stats) अणु						\
		पूर्णांक __cpu;						\
		क्रम_each_possible_cpu(__cpu) अणु				\
			typeof(type) *stat;				\
			stat = per_cpu_ptr(pcpu_stats, __cpu);		\
			u64_stats_init(&stat->syncp);			\
		पूर्ण							\
	पूर्ण								\
	pcpu_stats;							\
पूर्ण)

क्रमागत netdev_lag_tx_type अणु
	NETDEV_LAG_TX_TYPE_UNKNOWN,
	NETDEV_LAG_TX_TYPE_RANDOM,
	NETDEV_LAG_TX_TYPE_BROADCAST,
	NETDEV_LAG_TX_TYPE_ROUNDROBIN,
	NETDEV_LAG_TX_TYPE_ACTIVEBACKUP,
	NETDEV_LAG_TX_TYPE_HASH,
पूर्ण;

क्रमागत netdev_lag_hash अणु
	NETDEV_LAG_HASH_NONE,
	NETDEV_LAG_HASH_L2,
	NETDEV_LAG_HASH_L34,
	NETDEV_LAG_HASH_L23,
	NETDEV_LAG_HASH_E23,
	NETDEV_LAG_HASH_E34,
	NETDEV_LAG_HASH_VLAN_SRCMAC,
	NETDEV_LAG_HASH_UNKNOWN,
पूर्ण;

काष्ठा netdev_lag_upper_info अणु
	क्रमागत netdev_lag_tx_type tx_type;
	क्रमागत netdev_lag_hash hash_type;
पूर्ण;

काष्ठा netdev_lag_lower_state_info अणु
	u8 link_up : 1,
	   tx_enabled : 1;
पूर्ण;

#समावेश <linux/notअगरier.h>

/* netdevice notअगरier chain. Please remember to update netdev_cmd_to_name()
 * and the rtnetlink notअगरication exclusion list in rtnetlink_event() when
 * adding new types.
 */
क्रमागत netdev_cmd अणु
	NETDEV_UP	= 1,	/* For now you can't veto a device up/करोwn */
	NETDEV_DOWN,
	NETDEV_REBOOT,		/* Tell a protocol stack a network पूर्णांकerface
				   detected a hardware crash and restarted
				   - we can use this eg to kick tcp sessions
				   once करोne */
	NETDEV_CHANGE,		/* Notअगरy device state change */
	NETDEV_REGISTER,
	NETDEV_UNREGISTER,
	NETDEV_CHANGEMTU,	/* notअगरy after mtu change happened */
	NETDEV_CHANGEADDR,	/* notअगरy after the address change */
	NETDEV_PRE_CHANGEADDR,	/* notअगरy beक्रमe the address change */
	NETDEV_GOING_DOWN,
	NETDEV_CHANGENAME,
	NETDEV_FEAT_CHANGE,
	NETDEV_BONDING_FAILOVER,
	NETDEV_PRE_UP,
	NETDEV_PRE_TYPE_CHANGE,
	NETDEV_POST_TYPE_CHANGE,
	NETDEV_POST_INIT,
	NETDEV_RELEASE,
	NETDEV_NOTIFY_PEERS,
	NETDEV_JOIN,
	NETDEV_CHANGEUPPER,
	NETDEV_RESEND_IGMP,
	NETDEV_PRECHANGEMTU,	/* notअगरy beक्रमe mtu change happened */
	NETDEV_CHANGEINFODATA,
	NETDEV_BONDING_INFO,
	NETDEV_PRECHANGEUPPER,
	NETDEV_CHANGELOWERSTATE,
	NETDEV_UDP_TUNNEL_PUSH_INFO,
	NETDEV_UDP_TUNNEL_DROP_INFO,
	NETDEV_CHANGE_TX_QUEUE_LEN,
	NETDEV_CVLAN_FILTER_PUSH_INFO,
	NETDEV_CVLAN_FILTER_DROP_INFO,
	NETDEV_SVLAN_FILTER_PUSH_INFO,
	NETDEV_SVLAN_FILTER_DROP_INFO,
पूर्ण;
स्थिर अक्षर *netdev_cmd_to_name(क्रमागत netdev_cmd cmd);

पूर्णांक रेजिस्टर_netdevice_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_netdevice_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक रेजिस्टर_netdevice_notअगरier_net(काष्ठा net *net, काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_netdevice_notअगरier_net(काष्ठा net *net,
				      काष्ठा notअगरier_block *nb);
पूर्णांक रेजिस्टर_netdevice_notअगरier_dev_net(काष्ठा net_device *dev,
					काष्ठा notअगरier_block *nb,
					काष्ठा netdev_net_notअगरier *nn);
पूर्णांक unरेजिस्टर_netdevice_notअगरier_dev_net(काष्ठा net_device *dev,
					  काष्ठा notअगरier_block *nb,
					  काष्ठा netdev_net_notअगरier *nn);

काष्ठा netdev_notअगरier_info अणु
	काष्ठा net_device	*dev;
	काष्ठा netlink_ext_ack	*extack;
पूर्ण;

काष्ठा netdev_notअगरier_info_ext अणु
	काष्ठा netdev_notअगरier_info info; /* must be first */
	जोड़ अणु
		u32 mtu;
	पूर्ण ext;
पूर्ण;

काष्ठा netdev_notअगरier_change_info अणु
	काष्ठा netdev_notअगरier_info info; /* must be first */
	अचिन्हित पूर्णांक flags_changed;
पूर्ण;

काष्ठा netdev_notअगरier_changeupper_info अणु
	काष्ठा netdev_notअगरier_info info; /* must be first */
	काष्ठा net_device *upper_dev; /* new upper dev */
	bool master; /* is upper dev master */
	bool linking; /* is the notअगरication क्रम link or unlink */
	व्योम *upper_info; /* upper dev info */
पूर्ण;

काष्ठा netdev_notअगरier_changelowerstate_info अणु
	काष्ठा netdev_notअगरier_info info; /* must be first */
	व्योम *lower_state_info; /* is lower dev state */
पूर्ण;

काष्ठा netdev_notअगरier_pre_changeaddr_info अणु
	काष्ठा netdev_notअगरier_info info; /* must be first */
	स्थिर अचिन्हित अक्षर *dev_addr;
पूर्ण;

अटल अंतरभूत व्योम netdev_notअगरier_info_init(काष्ठा netdev_notअगरier_info *info,
					     काष्ठा net_device *dev)
अणु
	info->dev = dev;
	info->extack = शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_device *
netdev_notअगरier_info_to_dev(स्थिर काष्ठा netdev_notअगरier_info *info)
अणु
	वापस info->dev;
पूर्ण

अटल अंतरभूत काष्ठा netlink_ext_ack *
netdev_notअगरier_info_to_extack(स्थिर काष्ठा netdev_notअगरier_info *info)
अणु
	वापस info->extack;
पूर्ण

पूर्णांक call_netdevice_notअगरiers(अचिन्हित दीर्घ val, काष्ठा net_device *dev);


बाह्य rwlock_t				dev_base_lock;		/* Device list lock */

#घोषणा क्रम_each_netdev(net, d)		\
		list_क्रम_each_entry(d, &(net)->dev_base_head, dev_list)
#घोषणा क्रम_each_netdev_reverse(net, d)	\
		list_क्रम_each_entry_reverse(d, &(net)->dev_base_head, dev_list)
#घोषणा क्रम_each_netdev_rcu(net, d)		\
		list_क्रम_each_entry_rcu(d, &(net)->dev_base_head, dev_list)
#घोषणा क्रम_each_netdev_safe(net, d, n)	\
		list_क्रम_each_entry_safe(d, n, &(net)->dev_base_head, dev_list)
#घोषणा क्रम_each_netdev_जारी(net, d)		\
		list_क्रम_each_entry_जारी(d, &(net)->dev_base_head, dev_list)
#घोषणा क्रम_each_netdev_जारी_reverse(net, d)		\
		list_क्रम_each_entry_जारी_reverse(d, &(net)->dev_base_head, \
						     dev_list)
#घोषणा क्रम_each_netdev_जारी_rcu(net, d)		\
	list_क्रम_each_entry_जारी_rcu(d, &(net)->dev_base_head, dev_list)
#घोषणा क्रम_each_netdev_in_bond_rcu(bond, slave)	\
		क्रम_each_netdev_rcu(&init_net, slave)	\
			अगर (netdev_master_upper_dev_get_rcu(slave) == (bond))
#घोषणा net_device_entry(lh)	list_entry(lh, काष्ठा net_device, dev_list)

अटल अंतरभूत काष्ठा net_device *next_net_device(काष्ठा net_device *dev)
अणु
	काष्ठा list_head *lh;
	काष्ठा net *net;

	net = dev_net(dev);
	lh = dev->dev_list.next;
	वापस lh == &net->dev_base_head ? शून्य : net_device_entry(lh);
पूर्ण

अटल अंतरभूत काष्ठा net_device *next_net_device_rcu(काष्ठा net_device *dev)
अणु
	काष्ठा list_head *lh;
	काष्ठा net *net;

	net = dev_net(dev);
	lh = rcu_dereference(list_next_rcu(&dev->dev_list));
	वापस lh == &net->dev_base_head ? शून्य : net_device_entry(lh);
पूर्ण

अटल अंतरभूत काष्ठा net_device *first_net_device(काष्ठा net *net)
अणु
	वापस list_empty(&net->dev_base_head) ? शून्य :
		net_device_entry(net->dev_base_head.next);
पूर्ण

अटल अंतरभूत काष्ठा net_device *first_net_device_rcu(काष्ठा net *net)
अणु
	काष्ठा list_head *lh = rcu_dereference(list_next_rcu(&net->dev_base_head));

	वापस lh == &net->dev_base_head ? शून्य : net_device_entry(lh);
पूर्ण

पूर्णांक netdev_boot_setup_check(काष्ठा net_device *dev);
अचिन्हित दीर्घ netdev_boot_base(स्थिर अक्षर *prefix, पूर्णांक unit);
काष्ठा net_device *dev_getbyhwaddr_rcu(काष्ठा net *net, अचिन्हित लघु type,
				       स्थिर अक्षर *hwaddr);
काष्ठा net_device *dev_getfirstbyhwtype(काष्ठा net *net, अचिन्हित लघु type);
व्योम dev_add_pack(काष्ठा packet_type *pt);
व्योम dev_हटाओ_pack(काष्ठा packet_type *pt);
व्योम __dev_हटाओ_pack(काष्ठा packet_type *pt);
व्योम dev_add_offload(काष्ठा packet_offload *po);
व्योम dev_हटाओ_offload(काष्ठा packet_offload *po);

पूर्णांक dev_get_अगरlink(स्थिर काष्ठा net_device *dev);
पूर्णांक dev_fill_metadata_dst(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
पूर्णांक dev_fill_क्रमward_path(स्थिर काष्ठा net_device *dev, स्थिर u8 *daddr,
			  काष्ठा net_device_path_stack *stack);
काष्ठा net_device *__dev_get_by_flags(काष्ठा net *net, अचिन्हित लघु flags,
				      अचिन्हित लघु mask);
काष्ठा net_device *dev_get_by_name(काष्ठा net *net, स्थिर अक्षर *name);
काष्ठा net_device *dev_get_by_name_rcu(काष्ठा net *net, स्थिर अक्षर *name);
काष्ठा net_device *__dev_get_by_name(काष्ठा net *net, स्थिर अक्षर *name);
पूर्णांक dev_alloc_name(काष्ठा net_device *dev, स्थिर अक्षर *name);
पूर्णांक dev_खोलो(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack);
व्योम dev_बंद(काष्ठा net_device *dev);
व्योम dev_बंद_many(काष्ठा list_head *head, bool unlink);
व्योम dev_disable_lro(काष्ठा net_device *dev);
पूर्णांक dev_loopback_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *newskb);
u16 dev_pick_tx_zero(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		     काष्ठा net_device *sb_dev);
u16 dev_pick_tx_cpu_id(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा net_device *sb_dev);

पूर्णांक dev_queue_xmit(काष्ठा sk_buff *skb);
पूर्णांक dev_queue_xmit_accel(काष्ठा sk_buff *skb, काष्ठा net_device *sb_dev);
पूर्णांक __dev_direct_xmit(काष्ठा sk_buff *skb, u16 queue_id);

अटल अंतरभूत पूर्णांक dev_direct_xmit(काष्ठा sk_buff *skb, u16 queue_id)
अणु
	पूर्णांक ret;

	ret = __dev_direct_xmit(skb, queue_id);
	अगर (!dev_xmit_complete(ret))
		kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक रेजिस्टर_netdevice(काष्ठा net_device *dev);
व्योम unरेजिस्टर_netdevice_queue(काष्ठा net_device *dev, काष्ठा list_head *head);
व्योम unरेजिस्टर_netdevice_many(काष्ठा list_head *head);
अटल अंतरभूत व्योम unरेजिस्टर_netdevice(काष्ठा net_device *dev)
अणु
	unरेजिस्टर_netdevice_queue(dev, शून्य);
पूर्ण

पूर्णांक netdev_refcnt_पढ़ो(स्थिर काष्ठा net_device *dev);
व्योम मुक्त_netdev(काष्ठा net_device *dev);
व्योम netdev_मुक्तmem(काष्ठा net_device *dev);
पूर्णांक init_dummy_netdev(काष्ठा net_device *dev);

काष्ठा net_device *netdev_get_xmit_slave(काष्ठा net_device *dev,
					 काष्ठा sk_buff *skb,
					 bool all_slaves);
काष्ठा net_device *netdev_sk_get_lowest_dev(काष्ठा net_device *dev,
					    काष्ठा sock *sk);
काष्ठा net_device *dev_get_by_index(काष्ठा net *net, पूर्णांक अगरindex);
काष्ठा net_device *__dev_get_by_index(काष्ठा net *net, पूर्णांक अगरindex);
काष्ठा net_device *dev_get_by_index_rcu(काष्ठा net *net, पूर्णांक अगरindex);
काष्ठा net_device *dev_get_by_napi_id(अचिन्हित पूर्णांक napi_id);
पूर्णांक netdev_get_name(काष्ठा net *net, अक्षर *name, पूर्णांक अगरindex);
पूर्णांक dev_restart(काष्ठा net_device *dev);
पूर्णांक skb_gro_receive(काष्ठा sk_buff *p, काष्ठा sk_buff *skb);
पूर्णांक skb_gro_receive_list(काष्ठा sk_buff *p, काष्ठा sk_buff *skb);

अटल अंतरभूत अचिन्हित पूर्णांक skb_gro_offset(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस NAPI_GRO_CB(skb)->data_offset;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक skb_gro_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->len - NAPI_GRO_CB(skb)->data_offset;
पूर्ण

अटल अंतरभूत व्योम skb_gro_pull(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	NAPI_GRO_CB(skb)->data_offset += len;
पूर्ण

अटल अंतरभूत व्योम *skb_gro_header_fast(काष्ठा sk_buff *skb,
					अचिन्हित पूर्णांक offset)
अणु
	वापस NAPI_GRO_CB(skb)->frag0 + offset;
पूर्ण

अटल अंतरभूत पूर्णांक skb_gro_header_hard(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen)
अणु
	वापस NAPI_GRO_CB(skb)->frag0_len < hlen;
पूर्ण

अटल अंतरभूत व्योम skb_gro_frag0_invalidate(काष्ठा sk_buff *skb)
अणु
	NAPI_GRO_CB(skb)->frag0 = शून्य;
	NAPI_GRO_CB(skb)->frag0_len = 0;
पूर्ण

अटल अंतरभूत व्योम *skb_gro_header_slow(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen,
					अचिन्हित पूर्णांक offset)
अणु
	अगर (!pskb_may_pull(skb, hlen))
		वापस शून्य;

	skb_gro_frag0_invalidate(skb);
	वापस skb->data + offset;
पूर्ण

अटल अंतरभूत व्योम *skb_gro_network_header(काष्ठा sk_buff *skb)
अणु
	वापस (NAPI_GRO_CB(skb)->frag0 ?: skb->data) +
	       skb_network_offset(skb);
पूर्ण

अटल अंतरभूत व्योम skb_gro_postpull_rcsum(काष्ठा sk_buff *skb,
					स्थिर व्योम *start, अचिन्हित पूर्णांक len)
अणु
	अगर (NAPI_GRO_CB(skb)->csum_valid)
		NAPI_GRO_CB(skb)->csum = csum_sub(NAPI_GRO_CB(skb)->csum,
						  csum_partial(start, len, 0));
पूर्ण

/* GRO checksum functions. These are logical equivalents of the normal
 * checksum functions (in skbuff.h) except that they operate on the GRO
 * offsets and fields in sk_buff.
 */

__sum16 __skb_gro_checksum_complete(काष्ठा sk_buff *skb);

अटल अंतरभूत bool skb_at_gro_remcsum_start(काष्ठा sk_buff *skb)
अणु
	वापस (NAPI_GRO_CB(skb)->gro_remcsum_start == skb_gro_offset(skb));
पूर्ण

अटल अंतरभूत bool __skb_gro_checksum_validate_needed(काष्ठा sk_buff *skb,
						      bool zero_okay,
						      __sum16 check)
अणु
	वापस ((skb->ip_summed != CHECKSUM_PARTIAL ||
		skb_checksum_start_offset(skb) <
		 skb_gro_offset(skb)) &&
		!skb_at_gro_remcsum_start(skb) &&
		NAPI_GRO_CB(skb)->csum_cnt == 0 &&
		(!zero_okay || check));
पूर्ण

अटल अंतरभूत __sum16 __skb_gro_checksum_validate_complete(काष्ठा sk_buff *skb,
							   __wsum psum)
अणु
	अगर (NAPI_GRO_CB(skb)->csum_valid &&
	    !csum_fold(csum_add(psum, NAPI_GRO_CB(skb)->csum)))
		वापस 0;

	NAPI_GRO_CB(skb)->csum = psum;

	वापस __skb_gro_checksum_complete(skb);
पूर्ण

अटल अंतरभूत व्योम skb_gro_incr_csum_unnecessary(काष्ठा sk_buff *skb)
अणु
	अगर (NAPI_GRO_CB(skb)->csum_cnt > 0) अणु
		/* Consume a checksum from CHECKSUM_UNNECESSARY */
		NAPI_GRO_CB(skb)->csum_cnt--;
	पूर्ण अन्यथा अणु
		/* Update skb क्रम CHECKSUM_UNNECESSARY and csum_level when we
		 * verअगरied a new top level checksum or an encapsulated one
		 * during GRO. This saves work अगर we fallback to normal path.
		 */
		__skb_incr_checksum_unnecessary(skb);
	पूर्ण
पूर्ण

#घोषणा __skb_gro_checksum_validate(skb, proto, zero_okay, check,	\
				    compute_pseuकरो)			\
(अणु									\
	__sum16 __ret = 0;						\
	अगर (__skb_gro_checksum_validate_needed(skb, zero_okay, check))	\
		__ret = __skb_gro_checksum_validate_complete(skb,	\
				compute_pseuकरो(skb, proto));		\
	अगर (!__ret)							\
		skb_gro_incr_csum_unnecessary(skb);			\
	__ret;								\
पूर्ण)

#घोषणा skb_gro_checksum_validate(skb, proto, compute_pseuकरो)		\
	__skb_gro_checksum_validate(skb, proto, false, 0, compute_pseuकरो)

#घोषणा skb_gro_checksum_validate_zero_check(skb, proto, check,		\
					     compute_pseuकरो)		\
	__skb_gro_checksum_validate(skb, proto, true, check, compute_pseuकरो)

#घोषणा skb_gro_checksum_simple_validate(skb)				\
	__skb_gro_checksum_validate(skb, 0, false, 0, null_compute_pseuकरो)

अटल अंतरभूत bool __skb_gro_checksum_convert_check(काष्ठा sk_buff *skb)
अणु
	वापस (NAPI_GRO_CB(skb)->csum_cnt == 0 &&
		!NAPI_GRO_CB(skb)->csum_valid);
पूर्ण

अटल अंतरभूत व्योम __skb_gro_checksum_convert(काष्ठा sk_buff *skb,
					      __wsum pseuकरो)
अणु
	NAPI_GRO_CB(skb)->csum = ~pseuकरो;
	NAPI_GRO_CB(skb)->csum_valid = 1;
पूर्ण

#घोषणा skb_gro_checksum_try_convert(skb, proto, compute_pseuकरो)	\
करो अणु									\
	अगर (__skb_gro_checksum_convert_check(skb))			\
		__skb_gro_checksum_convert(skb, 			\
					   compute_pseuकरो(skb, proto));	\
पूर्ण जबतक (0)

काष्ठा gro_remcsum अणु
	पूर्णांक offset;
	__wsum delta;
पूर्ण;

अटल अंतरभूत व्योम skb_gro_remcsum_init(काष्ठा gro_remcsum *grc)
अणु
	grc->offset = 0;
	grc->delta = 0;
पूर्ण

अटल अंतरभूत व्योम *skb_gro_remcsum_process(काष्ठा sk_buff *skb, व्योम *ptr,
					    अचिन्हित पूर्णांक off, माप_प्रकार hdrlen,
					    पूर्णांक start, पूर्णांक offset,
					    काष्ठा gro_remcsum *grc,
					    bool nopartial)
अणु
	__wsum delta;
	माप_प्रकार plen = hdrlen + max_t(माप_प्रकार, offset + माप(u16), start);

	BUG_ON(!NAPI_GRO_CB(skb)->csum_valid);

	अगर (!nopartial) अणु
		NAPI_GRO_CB(skb)->gro_remcsum_start = off + hdrlen + start;
		वापस ptr;
	पूर्ण

	ptr = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, off + plen)) अणु
		ptr = skb_gro_header_slow(skb, off + plen, off);
		अगर (!ptr)
			वापस शून्य;
	पूर्ण

	delta = remcsum_adjust(ptr + hdrlen, NAPI_GRO_CB(skb)->csum,
			       start, offset);

	/* Adjust skb->csum since we changed the packet */
	NAPI_GRO_CB(skb)->csum = csum_add(NAPI_GRO_CB(skb)->csum, delta);

	grc->offset = off + hdrlen + offset;
	grc->delta = delta;

	वापस ptr;
पूर्ण

अटल अंतरभूत व्योम skb_gro_remcsum_cleanup(काष्ठा sk_buff *skb,
					   काष्ठा gro_remcsum *grc)
अणु
	व्योम *ptr;
	माप_प्रकार plen = grc->offset + माप(u16);

	अगर (!grc->delta)
		वापस;

	ptr = skb_gro_header_fast(skb, grc->offset);
	अगर (skb_gro_header_hard(skb, grc->offset + माप(u16))) अणु
		ptr = skb_gro_header_slow(skb, plen, grc->offset);
		अगर (!ptr)
			वापस;
	पूर्ण

	remcsum_unadjust((__sum16 *)ptr, grc->delta);
पूर्ण

#अगर_घोषित CONFIG_XFRM_OFFLOAD
अटल अंतरभूत व्योम skb_gro_flush_final(काष्ठा sk_buff *skb, काष्ठा sk_buff *pp, पूर्णांक flush)
अणु
	अगर (PTR_ERR(pp) != -EINPROGRESS)
		NAPI_GRO_CB(skb)->flush |= flush;
पूर्ण
अटल अंतरभूत व्योम skb_gro_flush_final_remcsum(काष्ठा sk_buff *skb,
					       काष्ठा sk_buff *pp,
					       पूर्णांक flush,
					       काष्ठा gro_remcsum *grc)
अणु
	अगर (PTR_ERR(pp) != -EINPROGRESS) अणु
		NAPI_GRO_CB(skb)->flush |= flush;
		skb_gro_remcsum_cleanup(skb, grc);
		skb->remcsum_offload = 0;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम skb_gro_flush_final(काष्ठा sk_buff *skb, काष्ठा sk_buff *pp, पूर्णांक flush)
अणु
	NAPI_GRO_CB(skb)->flush |= flush;
पूर्ण
अटल अंतरभूत व्योम skb_gro_flush_final_remcsum(काष्ठा sk_buff *skb,
					       काष्ठा sk_buff *pp,
					       पूर्णांक flush,
					       काष्ठा gro_remcsum *grc)
अणु
	NAPI_GRO_CB(skb)->flush |= flush;
	skb_gro_remcsum_cleanup(skb, grc);
	skb->remcsum_offload = 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक dev_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				  अचिन्हित लघु type,
				  स्थिर व्योम *daddr, स्थिर व्योम *saddr,
				  अचिन्हित पूर्णांक len)
अणु
	अगर (!dev->header_ops || !dev->header_ops->create)
		वापस 0;

	वापस dev->header_ops->create(skb, dev, type, daddr, saddr, len);
पूर्ण

अटल अंतरभूत पूर्णांक dev_parse_header(स्थिर काष्ठा sk_buff *skb,
				   अचिन्हित अक्षर *haddr)
अणु
	स्थिर काष्ठा net_device *dev = skb->dev;

	अगर (!dev->header_ops || !dev->header_ops->parse)
		वापस 0;
	वापस dev->header_ops->parse(skb, haddr);
पूर्ण

अटल अंतरभूत __be16 dev_parse_header_protocol(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा net_device *dev = skb->dev;

	अगर (!dev->header_ops || !dev->header_ops->parse_protocol)
		वापस 0;
	वापस dev->header_ops->parse_protocol(skb);
पूर्ण

/* ll_header must have at least hard_header_len allocated */
अटल अंतरभूत bool dev_validate_header(स्थिर काष्ठा net_device *dev,
				       अक्षर *ll_header, पूर्णांक len)
अणु
	अगर (likely(len >= dev->hard_header_len))
		वापस true;
	अगर (len < dev->min_header_len)
		वापस false;

	अगर (capable(CAP_SYS_RAWIO)) अणु
		स_रखो(ll_header + len, 0, dev->hard_header_len - len);
		वापस true;
	पूर्ण

	अगर (dev->header_ops && dev->header_ops->validate)
		वापस dev->header_ops->validate(ll_header, len);

	वापस false;
पूर्ण

अटल अंतरभूत bool dev_has_header(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->header_ops && dev->header_ops->create;
पूर्ण

प्रकार पूर्णांक gअगरconf_func_t(काष्ठा net_device * dev, अक्षर __user * bufptr,
			   पूर्णांक len, पूर्णांक size);
पूर्णांक रेजिस्टर_gअगरconf(अचिन्हित पूर्णांक family, gअगरconf_func_t *gअगरconf);
अटल अंतरभूत पूर्णांक unरेजिस्टर_gअगरconf(अचिन्हित पूर्णांक family)
अणु
	वापस रेजिस्टर_gअगरconf(family, शून्य);
पूर्ण

#अगर_घोषित CONFIG_NET_FLOW_LIMIT
#घोषणा FLOW_LIMIT_HISTORY	(1 << 7)  /* must be ^2 and !overflow buckets */
काष्ठा sd_flow_limit अणु
	u64			count;
	अचिन्हित पूर्णांक		num_buckets;
	अचिन्हित पूर्णांक		history_head;
	u16			history[FLOW_LIMIT_HISTORY];
	u8			buckets[];
पूर्ण;

बाह्य पूर्णांक netdev_flow_limit_table_len;
#पूर्ण_अगर /* CONFIG_NET_FLOW_LIMIT */

/*
 * Incoming packets are placed on per-CPU queues
 */
काष्ठा softnet_data अणु
	काष्ठा list_head	poll_list;
	काष्ठा sk_buff_head	process_queue;

	/* stats */
	अचिन्हित पूर्णांक		processed;
	अचिन्हित पूर्णांक		समय_squeeze;
	अचिन्हित पूर्णांक		received_rps;
#अगर_घोषित CONFIG_RPS
	काष्ठा softnet_data	*rps_ipi_list;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_FLOW_LIMIT
	काष्ठा sd_flow_limit __rcu *flow_limit;
#पूर्ण_अगर
	काष्ठा Qdisc		*output_queue;
	काष्ठा Qdisc		**output_queue_tailp;
	काष्ठा sk_buff		*completion_queue;
#अगर_घोषित CONFIG_XFRM_OFFLOAD
	काष्ठा sk_buff_head	xfrm_backlog;
#पूर्ण_अगर
	/* written and पढ़ो only by owning cpu: */
	काष्ठा अणु
		u16 recursion;
		u8  more;
	पूर्ण xmit;
#अगर_घोषित CONFIG_RPS
	/* input_queue_head should be written by cpu owning this काष्ठा,
	 * and only पढ़ो by other cpus. Worth using a cache line.
	 */
	अचिन्हित पूर्णांक		input_queue_head ____cacheline_aligned_in_smp;

	/* Elements below can be accessed between CPUs क्रम RPS/RFS */
	call_single_data_t	csd ____cacheline_aligned_in_smp;
	काष्ठा softnet_data	*rps_ipi_next;
	अचिन्हित पूर्णांक		cpu;
	अचिन्हित पूर्णांक		input_queue_tail;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		dropped;
	काष्ठा sk_buff_head	input_pkt_queue;
	काष्ठा napi_काष्ठा	backlog;

पूर्ण;

अटल अंतरभूत व्योम input_queue_head_incr(काष्ठा softnet_data *sd)
अणु
#अगर_घोषित CONFIG_RPS
	sd->input_queue_head++;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम input_queue_tail_incr_save(काष्ठा softnet_data *sd,
					      अचिन्हित पूर्णांक *qtail)
अणु
#अगर_घोषित CONFIG_RPS
	*qtail = ++sd->input_queue_tail;
#पूर्ण_अगर
पूर्ण

DECLARE_PER_CPU_ALIGNED(काष्ठा softnet_data, softnet_data);

अटल अंतरभूत पूर्णांक dev_recursion_level(व्योम)
अणु
	वापस this_cpu_पढ़ो(softnet_data.xmit.recursion);
पूर्ण

#घोषणा XMIT_RECURSION_LIMIT	8
अटल अंतरभूत bool dev_xmit_recursion(व्योम)
अणु
	वापस unlikely(__this_cpu_पढ़ो(softnet_data.xmit.recursion) >
			XMIT_RECURSION_LIMIT);
पूर्ण

अटल अंतरभूत व्योम dev_xmit_recursion_inc(व्योम)
अणु
	__this_cpu_inc(softnet_data.xmit.recursion);
पूर्ण

अटल अंतरभूत व्योम dev_xmit_recursion_dec(व्योम)
अणु
	__this_cpu_dec(softnet_data.xmit.recursion);
पूर्ण

व्योम __netअगर_schedule(काष्ठा Qdisc *q);
व्योम netअगर_schedule_queue(काष्ठा netdev_queue *txq);

अटल अंतरभूत व्योम netअगर_tx_schedule_all(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++)
		netअगर_schedule_queue(netdev_get_tx_queue(dev, i));
पूर्ण

अटल __always_अंतरभूत व्योम netअगर_tx_start_queue(काष्ठा netdev_queue *dev_queue)
अणु
	clear_bit(__QUEUE_STATE_DRV_XOFF, &dev_queue->state);
पूर्ण

/**
 *	netअगर_start_queue - allow transmit
 *	@dev: network device
 *
 *	Allow upper layers to call the device hard_start_xmit routine.
 */
अटल अंतरभूत व्योम netअगर_start_queue(काष्ठा net_device *dev)
अणु
	netअगर_tx_start_queue(netdev_get_tx_queue(dev, 0));
पूर्ण

अटल अंतरभूत व्योम netअगर_tx_start_all_queues(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);
		netअगर_tx_start_queue(txq);
	पूर्ण
पूर्ण

व्योम netअगर_tx_wake_queue(काष्ठा netdev_queue *dev_queue);

/**
 *	netअगर_wake_queue - restart transmit
 *	@dev: network device
 *
 *	Allow upper layers to call the device hard_start_xmit routine.
 *	Used क्रम flow control when transmit resources are available.
 */
अटल अंतरभूत व्योम netअगर_wake_queue(काष्ठा net_device *dev)
अणु
	netअगर_tx_wake_queue(netdev_get_tx_queue(dev, 0));
पूर्ण

अटल अंतरभूत व्योम netअगर_tx_wake_all_queues(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);
		netअगर_tx_wake_queue(txq);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम netअगर_tx_stop_queue(काष्ठा netdev_queue *dev_queue)
अणु
	set_bit(__QUEUE_STATE_DRV_XOFF, &dev_queue->state);
पूर्ण

/**
 *	netअगर_stop_queue - stop transmitted packets
 *	@dev: network device
 *
 *	Stop upper layers calling the device hard_start_xmit routine.
 *	Used क्रम flow control when transmit resources are unavailable.
 */
अटल अंतरभूत व्योम netअगर_stop_queue(काष्ठा net_device *dev)
अणु
	netअगर_tx_stop_queue(netdev_get_tx_queue(dev, 0));
पूर्ण

व्योम netअगर_tx_stop_all_queues(काष्ठा net_device *dev);

अटल अंतरभूत bool netअगर_tx_queue_stopped(स्थिर काष्ठा netdev_queue *dev_queue)
अणु
	वापस test_bit(__QUEUE_STATE_DRV_XOFF, &dev_queue->state);
पूर्ण

/**
 *	netअगर_queue_stopped - test अगर transmit queue is flowblocked
 *	@dev: network device
 *
 *	Test अगर transmit queue on device is currently unable to send.
 */
अटल अंतरभूत bool netअगर_queue_stopped(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_tx_queue_stopped(netdev_get_tx_queue(dev, 0));
पूर्ण

अटल अंतरभूत bool netअगर_xmit_stopped(स्थिर काष्ठा netdev_queue *dev_queue)
अणु
	वापस dev_queue->state & QUEUE_STATE_ANY_XOFF;
पूर्ण

अटल अंतरभूत bool
netअगर_xmit_frozen_or_stopped(स्थिर काष्ठा netdev_queue *dev_queue)
अणु
	वापस dev_queue->state & QUEUE_STATE_ANY_XOFF_OR_FROZEN;
पूर्ण

अटल अंतरभूत bool
netअगर_xmit_frozen_or_drv_stopped(स्थिर काष्ठा netdev_queue *dev_queue)
अणु
	वापस dev_queue->state & QUEUE_STATE_DRV_XOFF_OR_FROZEN;
पूर्ण

/**
 *	netdev_queue_set_dql_min_limit - set dql minimum limit
 *	@dev_queue: poपूर्णांकer to transmit queue
 *	@min_limit: dql minimum limit
 *
 * Forces xmit_more() to वापस true until the minimum threshold
 * defined by @min_limit is reached (or until the tx queue is
 * empty). Warning: to be use with care, misuse will impact the
 * latency.
 */
अटल अंतरभूत व्योम netdev_queue_set_dql_min_limit(काष्ठा netdev_queue *dev_queue,
						  अचिन्हित पूर्णांक min_limit)
अणु
#अगर_घोषित CONFIG_BQL
	dev_queue->dql.min_limit = min_limit;
#पूर्ण_अगर
पूर्ण

/**
 *	netdev_txq_bql_enqueue_prefetchw - prefetch bql data क्रम ग_लिखो
 *	@dev_queue: poपूर्णांकer to transmit queue
 *
 * BQL enabled drivers might use this helper in their nकरो_start_xmit(),
 * to give appropriate hपूर्णांक to the CPU.
 */
अटल अंतरभूत व्योम netdev_txq_bql_enqueue_prefetchw(काष्ठा netdev_queue *dev_queue)
अणु
#अगर_घोषित CONFIG_BQL
	prefetchw(&dev_queue->dql.num_queued);
#पूर्ण_अगर
पूर्ण

/**
 *	netdev_txq_bql_complete_prefetchw - prefetch bql data क्रम ग_लिखो
 *	@dev_queue: poपूर्णांकer to transmit queue
 *
 * BQL enabled drivers might use this helper in their TX completion path,
 * to give appropriate hपूर्णांक to the CPU.
 */
अटल अंतरभूत व्योम netdev_txq_bql_complete_prefetchw(काष्ठा netdev_queue *dev_queue)
अणु
#अगर_घोषित CONFIG_BQL
	prefetchw(&dev_queue->dql.limit);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम netdev_tx_sent_queue(काष्ठा netdev_queue *dev_queue,
					अचिन्हित पूर्णांक bytes)
अणु
#अगर_घोषित CONFIG_BQL
	dql_queued(&dev_queue->dql, bytes);

	अगर (likely(dql_avail(&dev_queue->dql) >= 0))
		वापस;

	set_bit(__QUEUE_STATE_STACK_XOFF, &dev_queue->state);

	/*
	 * The XOFF flag must be set beक्रमe checking the dql_avail below,
	 * because in netdev_tx_completed_queue we update the dql_completed
	 * beक्रमe checking the XOFF flag.
	 */
	smp_mb();

	/* check again in हाल another CPU has just made room avail */
	अगर (unlikely(dql_avail(&dev_queue->dql) >= 0))
		clear_bit(__QUEUE_STATE_STACK_XOFF, &dev_queue->state);
#पूर्ण_अगर
पूर्ण

/* Variant of netdev_tx_sent_queue() क्रम drivers that are aware
 * that they should not test BQL status themselves.
 * We करो want to change __QUEUE_STATE_STACK_XOFF only क्रम the last
 * skb of a batch.
 * Returns true अगर the करोorbell must be used to kick the NIC.
 */
अटल अंतरभूत bool __netdev_tx_sent_queue(काष्ठा netdev_queue *dev_queue,
					  अचिन्हित पूर्णांक bytes,
					  bool xmit_more)
अणु
	अगर (xmit_more) अणु
#अगर_घोषित CONFIG_BQL
		dql_queued(&dev_queue->dql, bytes);
#पूर्ण_अगर
		वापस netअगर_tx_queue_stopped(dev_queue);
	पूर्ण
	netdev_tx_sent_queue(dev_queue, bytes);
	वापस true;
पूर्ण

/**
 * 	netdev_sent_queue - report the number of bytes queued to hardware
 * 	@dev: network device
 * 	@bytes: number of bytes queued to the hardware device queue
 *
 * 	Report the number of bytes queued क्रम sending/completion to the network
 * 	device hardware queue. @bytes should be a good approximation and should
 * 	exactly match netdev_completed_queue() @bytes
 */
अटल अंतरभूत व्योम netdev_sent_queue(काष्ठा net_device *dev, अचिन्हित पूर्णांक bytes)
अणु
	netdev_tx_sent_queue(netdev_get_tx_queue(dev, 0), bytes);
पूर्ण

अटल अंतरभूत bool __netdev_sent_queue(काष्ठा net_device *dev,
				       अचिन्हित पूर्णांक bytes,
				       bool xmit_more)
अणु
	वापस __netdev_tx_sent_queue(netdev_get_tx_queue(dev, 0), bytes,
				      xmit_more);
पूर्ण

अटल अंतरभूत व्योम netdev_tx_completed_queue(काष्ठा netdev_queue *dev_queue,
					     अचिन्हित पूर्णांक pkts, अचिन्हित पूर्णांक bytes)
अणु
#अगर_घोषित CONFIG_BQL
	अगर (unlikely(!bytes))
		वापस;

	dql_completed(&dev_queue->dql, bytes);

	/*
	 * Without the memory barrier there is a small possiblity that
	 * netdev_tx_sent_queue will miss the update and cause the queue to
	 * be stopped क्रमever
	 */
	smp_mb();

	अगर (unlikely(dql_avail(&dev_queue->dql) < 0))
		वापस;

	अगर (test_and_clear_bit(__QUEUE_STATE_STACK_XOFF, &dev_queue->state))
		netअगर_schedule_queue(dev_queue);
#पूर्ण_अगर
पूर्ण

/**
 * 	netdev_completed_queue - report bytes and packets completed by device
 * 	@dev: network device
 * 	@pkts: actual number of packets sent over the medium
 * 	@bytes: actual number of bytes sent over the medium
 *
 * 	Report the number of bytes and packets transmitted by the network device
 * 	hardware queue over the physical medium, @bytes must exactly match the
 * 	@bytes amount passed to netdev_sent_queue()
 */
अटल अंतरभूत व्योम netdev_completed_queue(काष्ठा net_device *dev,
					  अचिन्हित पूर्णांक pkts, अचिन्हित पूर्णांक bytes)
अणु
	netdev_tx_completed_queue(netdev_get_tx_queue(dev, 0), pkts, bytes);
पूर्ण

अटल अंतरभूत व्योम netdev_tx_reset_queue(काष्ठा netdev_queue *q)
अणु
#अगर_घोषित CONFIG_BQL
	clear_bit(__QUEUE_STATE_STACK_XOFF, &q->state);
	dql_reset(&q->dql);
#पूर्ण_अगर
पूर्ण

/**
 * 	netdev_reset_queue - reset the packets and bytes count of a network device
 * 	@dev_queue: network device
 *
 * 	Reset the bytes and packet count of a network device and clear the
 * 	software flow control OFF bit क्रम this network device
 */
अटल अंतरभूत व्योम netdev_reset_queue(काष्ठा net_device *dev_queue)
अणु
	netdev_tx_reset_queue(netdev_get_tx_queue(dev_queue, 0));
पूर्ण

/**
 * 	netdev_cap_txqueue - check अगर selected tx queue exceeds device queues
 * 	@dev: network device
 * 	@queue_index: given tx queue index
 *
 * 	Returns 0 अगर given tx queue index >= number of device tx queues,
 * 	otherwise वापसs the originally passed tx queue index.
 */
अटल अंतरभूत u16 netdev_cap_txqueue(काष्ठा net_device *dev, u16 queue_index)
अणु
	अगर (unlikely(queue_index >= dev->real_num_tx_queues)) अणु
		net_warn_ratelimited("%s selects TX queue %d, but real number of TX queues is %d\n",
				     dev->name, queue_index,
				     dev->real_num_tx_queues);
		वापस 0;
	पूर्ण

	वापस queue_index;
पूर्ण

/**
 *	netअगर_running - test अगर up
 *	@dev: network device
 *
 *	Test अगर the device has been brought up.
 */
अटल अंतरभूत bool netअगर_running(स्थिर काष्ठा net_device *dev)
अणु
	वापस test_bit(__LINK_STATE_START, &dev->state);
पूर्ण

/*
 * Routines to manage the subqueues on a device.  We only need start,
 * stop, and a check अगर it's stopped.  All other device management is
 * करोne at the overall netdevice level.
 * Also test the device अगर we're multiqueue.
 */

/**
 *	netअगर_start_subqueue - allow sending packets on subqueue
 *	@dev: network device
 *	@queue_index: sub queue index
 *
 * Start inभागidual transmit queue of a device with multiple transmit queues.
 */
अटल अंतरभूत व्योम netअगर_start_subqueue(काष्ठा net_device *dev, u16 queue_index)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, queue_index);

	netअगर_tx_start_queue(txq);
पूर्ण

/**
 *	netअगर_stop_subqueue - stop sending packets on subqueue
 *	@dev: network device
 *	@queue_index: sub queue index
 *
 * Stop inभागidual transmit queue of a device with multiple transmit queues.
 */
अटल अंतरभूत व्योम netअगर_stop_subqueue(काष्ठा net_device *dev, u16 queue_index)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, queue_index);
	netअगर_tx_stop_queue(txq);
पूर्ण

/**
 *	__netअगर_subqueue_stopped - test status of subqueue
 *	@dev: network device
 *	@queue_index: sub queue index
 *
 * Check inभागidual transmit queue of a device with multiple transmit queues.
 */
अटल अंतरभूत bool __netअगर_subqueue_stopped(स्थिर काष्ठा net_device *dev,
					    u16 queue_index)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, queue_index);

	वापस netअगर_tx_queue_stopped(txq);
पूर्ण

/**
 *	netअगर_subqueue_stopped - test status of subqueue
 *	@dev: network device
 *	@skb: sub queue buffer poपूर्णांकer
 *
 * Check inभागidual transmit queue of a device with multiple transmit queues.
 */
अटल अंतरभूत bool netअगर_subqueue_stopped(स्थिर काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb)
अणु
	वापस __netअगर_subqueue_stopped(dev, skb_get_queue_mapping(skb));
पूर्ण

/**
 *	netअगर_wake_subqueue - allow sending packets on subqueue
 *	@dev: network device
 *	@queue_index: sub queue index
 *
 * Resume inभागidual transmit queue of a device with multiple transmit queues.
 */
अटल अंतरभूत व्योम netअगर_wake_subqueue(काष्ठा net_device *dev, u16 queue_index)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, queue_index);

	netअगर_tx_wake_queue(txq);
पूर्ण

#अगर_घोषित CONFIG_XPS
पूर्णांक netअगर_set_xps_queue(काष्ठा net_device *dev, स्थिर काष्ठा cpumask *mask,
			u16 index);
पूर्णांक __netअगर_set_xps_queue(काष्ठा net_device *dev, स्थिर अचिन्हित दीर्घ *mask,
			  u16 index, क्रमागत xps_map_type type);

/**
 *	netअगर_attr_test_mask - Test a CPU or Rx queue set in a mask
 *	@j: CPU/Rx queue index
 *	@mask: biपंचांगask of all cpus/rx queues
 *	@nr_bits: number of bits in the biपंचांगask
 *
 * Test अगर a CPU or Rx queue index is set in a mask of all CPU/Rx queues.
 */
अटल अंतरभूत bool netअगर_attr_test_mask(अचिन्हित दीर्घ j,
					स्थिर अचिन्हित दीर्घ *mask,
					अचिन्हित पूर्णांक nr_bits)
अणु
	cpu_max_bits_warn(j, nr_bits);
	वापस test_bit(j, mask);
पूर्ण

/**
 *	netअगर_attr_test_online - Test क्रम online CPU/Rx queue
 *	@j: CPU/Rx queue index
 *	@online_mask: biपंचांगask क्रम CPUs/Rx queues that are online
 *	@nr_bits: number of bits in the biपंचांगask
 *
 * Returns true अगर a CPU/Rx queue is online.
 */
अटल अंतरभूत bool netअगर_attr_test_online(अचिन्हित दीर्घ j,
					  स्थिर अचिन्हित दीर्घ *online_mask,
					  अचिन्हित पूर्णांक nr_bits)
अणु
	cpu_max_bits_warn(j, nr_bits);

	अगर (online_mask)
		वापस test_bit(j, online_mask);

	वापस (j < nr_bits);
पूर्ण

/**
 *	netअगर_attrmask_next - get the next CPU/Rx queue in a cpu/Rx queues mask
 *	@n: CPU/Rx queue index
 *	@srcp: the cpumask/Rx queue mask poपूर्णांकer
 *	@nr_bits: number of bits in the biपंचांगask
 *
 * Returns >= nr_bits अगर no further CPUs/Rx queues set.
 */
अटल अंतरभूत अचिन्हित पूर्णांक netअगर_attrmask_next(पूर्णांक n, स्थिर अचिन्हित दीर्घ *srcp,
					       अचिन्हित पूर्णांक nr_bits)
अणु
	/* -1 is a legal arg here. */
	अगर (n != -1)
		cpu_max_bits_warn(n, nr_bits);

	अगर (srcp)
		वापस find_next_bit(srcp, nr_bits, n + 1);

	वापस n + 1;
पूर्ण

/**
 *	netअगर_attrmask_next_and - get the next CPU/Rx queue in \*src1p & \*src2p
 *	@n: CPU/Rx queue index
 *	@src1p: the first CPUs/Rx queues mask poपूर्णांकer
 *	@src2p: the second CPUs/Rx queues mask poपूर्णांकer
 *	@nr_bits: number of bits in the biपंचांगask
 *
 * Returns >= nr_bits अगर no further CPUs/Rx queues set in both.
 */
अटल अंतरभूत पूर्णांक netअगर_attrmask_next_and(पूर्णांक n, स्थिर अचिन्हित दीर्घ *src1p,
					  स्थिर अचिन्हित दीर्घ *src2p,
					  अचिन्हित पूर्णांक nr_bits)
अणु
	/* -1 is a legal arg here. */
	अगर (n != -1)
		cpu_max_bits_warn(n, nr_bits);

	अगर (src1p && src2p)
		वापस find_next_and_bit(src1p, src2p, nr_bits, n + 1);
	अन्यथा अगर (src1p)
		वापस find_next_bit(src1p, nr_bits, n + 1);
	अन्यथा अगर (src2p)
		वापस find_next_bit(src2p, nr_bits, n + 1);

	वापस n + 1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक netअगर_set_xps_queue(काष्ठा net_device *dev,
				      स्थिर काष्ठा cpumask *mask,
				      u16 index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __netअगर_set_xps_queue(काष्ठा net_device *dev,
					स्थिर अचिन्हित दीर्घ *mask,
					u16 index, क्रमागत xps_map_type type)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 *	netअगर_is_multiqueue - test अगर device has multiple transmit queues
 *	@dev: network device
 *
 * Check अगर device has multiple transmit queues
 */
अटल अंतरभूत bool netअगर_is_multiqueue(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->num_tx_queues > 1;
पूर्ण

पूर्णांक netअगर_set_real_num_tx_queues(काष्ठा net_device *dev, अचिन्हित पूर्णांक txq);

#अगर_घोषित CONFIG_SYSFS
पूर्णांक netअगर_set_real_num_rx_queues(काष्ठा net_device *dev, अचिन्हित पूर्णांक rxq);
#अन्यथा
अटल अंतरभूत पूर्णांक netअगर_set_real_num_rx_queues(काष्ठा net_device *dev,
						अचिन्हित पूर्णांक rxqs)
अणु
	dev->real_num_rx_queues = rxqs;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा netdev_rx_queue *
__netअगर_get_rx_queue(काष्ठा net_device *dev, अचिन्हित पूर्णांक rxq)
अणु
	वापस dev->_rx + rxq;
पूर्ण

#अगर_घोषित CONFIG_SYSFS
अटल अंतरभूत अचिन्हित पूर्णांक get_netdev_rx_queue_index(
		काष्ठा netdev_rx_queue *queue)
अणु
	काष्ठा net_device *dev = queue->dev;
	पूर्णांक index = queue - dev->_rx;

	BUG_ON(index >= dev->num_rx_queues);
	वापस index;
पूर्ण
#पूर्ण_अगर

#घोषणा DEFAULT_MAX_NUM_RSS_QUEUES	(8)
पूर्णांक netअगर_get_num_शेष_rss_queues(व्योम);

क्रमागत skb_मुक्त_reason अणु
	SKB_REASON_CONSUMED,
	SKB_REASON_DROPPED,
पूर्ण;

व्योम __dev_kमुक्त_skb_irq(काष्ठा sk_buff *skb, क्रमागत skb_मुक्त_reason reason);
व्योम __dev_kमुक्त_skb_any(काष्ठा sk_buff *skb, क्रमागत skb_मुक्त_reason reason);

/*
 * It is not allowed to call kमुक्त_skb() or consume_skb() from hardware
 * पूर्णांकerrupt context or with hardware पूर्णांकerrupts being disabled.
 * (in_irq() || irqs_disabled())
 *
 * We provide four helpers that can be used in following contexts :
 *
 * dev_kमुक्त_skb_irq(skb) when caller drops a packet from irq context,
 *  replacing kमुक्त_skb(skb)
 *
 * dev_consume_skb_irq(skb) when caller consumes a packet from irq context.
 *  Typically used in place of consume_skb(skb) in TX completion path
 *
 * dev_kमुक्त_skb_any(skb) when caller करोesn't know its current irq context,
 *  replacing kमुक्त_skb(skb)
 *
 * dev_consume_skb_any(skb) when caller करोesn't know its current irq context,
 *  and consumed a packet. Used in place of consume_skb(skb)
 */
अटल अंतरभूत व्योम dev_kमुक्त_skb_irq(काष्ठा sk_buff *skb)
अणु
	__dev_kमुक्त_skb_irq(skb, SKB_REASON_DROPPED);
पूर्ण

अटल अंतरभूत व्योम dev_consume_skb_irq(काष्ठा sk_buff *skb)
अणु
	__dev_kमुक्त_skb_irq(skb, SKB_REASON_CONSUMED);
पूर्ण

अटल अंतरभूत व्योम dev_kमुक्त_skb_any(काष्ठा sk_buff *skb)
अणु
	__dev_kमुक्त_skb_any(skb, SKB_REASON_DROPPED);
पूर्ण

अटल अंतरभूत व्योम dev_consume_skb_any(काष्ठा sk_buff *skb)
अणु
	__dev_kमुक्त_skb_any(skb, SKB_REASON_CONSUMED);
पूर्ण

व्योम generic_xdp_tx(काष्ठा sk_buff *skb, काष्ठा bpf_prog *xdp_prog);
पूर्णांक करो_xdp_generic(काष्ठा bpf_prog *xdp_prog, काष्ठा sk_buff *skb);
पूर्णांक netअगर_rx(काष्ठा sk_buff *skb);
पूर्णांक netअगर_rx_ni(काष्ठा sk_buff *skb);
पूर्णांक netअगर_rx_any_context(काष्ठा sk_buff *skb);
पूर्णांक netअगर_receive_skb(काष्ठा sk_buff *skb);
पूर्णांक netअगर_receive_skb_core(काष्ठा sk_buff *skb);
व्योम netअगर_receive_skb_list(काष्ठा list_head *head);
gro_result_t napi_gro_receive(काष्ठा napi_काष्ठा *napi, काष्ठा sk_buff *skb);
व्योम napi_gro_flush(काष्ठा napi_काष्ठा *napi, bool flush_old);
काष्ठा sk_buff *napi_get_frags(काष्ठा napi_काष्ठा *napi);
gro_result_t napi_gro_frags(काष्ठा napi_काष्ठा *napi);
काष्ठा packet_offload *gro_find_receive_by_type(__be16 type);
काष्ठा packet_offload *gro_find_complete_by_type(__be16 type);

अटल अंतरभूत व्योम napi_मुक्त_frags(काष्ठा napi_काष्ठा *napi)
अणु
	kमुक्त_skb(napi->skb);
	napi->skb = शून्य;
पूर्ण

bool netdev_is_rx_handler_busy(काष्ठा net_device *dev);
पूर्णांक netdev_rx_handler_रेजिस्टर(काष्ठा net_device *dev,
			       rx_handler_func_t *rx_handler,
			       व्योम *rx_handler_data);
व्योम netdev_rx_handler_unरेजिस्टर(काष्ठा net_device *dev);

bool dev_valid_name(स्थिर अक्षर *name);
पूर्णांक dev_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, काष्ठा अगरreq *अगरr,
		bool *need_copyout);
पूर्णांक dev_अगरconf(काष्ठा net *net, काष्ठा अगरconf *, पूर्णांक);
पूर्णांक dev_ethtool(काष्ठा net *net, काष्ठा अगरreq *);
अचिन्हित पूर्णांक dev_get_flags(स्थिर काष्ठा net_device *);
पूर्णांक __dev_change_flags(काष्ठा net_device *dev, अचिन्हित पूर्णांक flags,
		       काष्ठा netlink_ext_ack *extack);
पूर्णांक dev_change_flags(काष्ठा net_device *dev, अचिन्हित पूर्णांक flags,
		     काष्ठा netlink_ext_ack *extack);
व्योम __dev_notअगरy_flags(काष्ठा net_device *, अचिन्हित पूर्णांक old_flags,
			अचिन्हित पूर्णांक gchanges);
पूर्णांक dev_change_name(काष्ठा net_device *, स्थिर अक्षर *);
पूर्णांक dev_set_alias(काष्ठा net_device *, स्थिर अक्षर *, माप_प्रकार);
पूर्णांक dev_get_alias(स्थिर काष्ठा net_device *, अक्षर *, माप_प्रकार);
पूर्णांक __dev_change_net_namespace(काष्ठा net_device *dev, काष्ठा net *net,
			       स्थिर अक्षर *pat, पूर्णांक new_अगरindex);
अटल अंतरभूत
पूर्णांक dev_change_net_namespace(काष्ठा net_device *dev, काष्ठा net *net,
			     स्थिर अक्षर *pat)
अणु
	वापस __dev_change_net_namespace(dev, net, pat, 0);
पूर्ण
पूर्णांक __dev_set_mtu(काष्ठा net_device *, पूर्णांक);
पूर्णांक dev_validate_mtu(काष्ठा net_device *dev, पूर्णांक mtu,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक dev_set_mtu_ext(काष्ठा net_device *dev, पूर्णांक mtu,
		    काष्ठा netlink_ext_ack *extack);
पूर्णांक dev_set_mtu(काष्ठा net_device *, पूर्णांक);
पूर्णांक dev_change_tx_queue_len(काष्ठा net_device *, अचिन्हित दीर्घ);
व्योम dev_set_group(काष्ठा net_device *, पूर्णांक);
पूर्णांक dev_pre_changeaddr_notअगरy(काष्ठा net_device *dev, स्थिर अक्षर *addr,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक dev_set_mac_address(काष्ठा net_device *dev, काष्ठा sockaddr *sa,
			काष्ठा netlink_ext_ack *extack);
पूर्णांक dev_set_mac_address_user(काष्ठा net_device *dev, काष्ठा sockaddr *sa,
			     काष्ठा netlink_ext_ack *extack);
पूर्णांक dev_get_mac_address(काष्ठा sockaddr *sa, काष्ठा net *net, अक्षर *dev_name);
पूर्णांक dev_change_carrier(काष्ठा net_device *, bool new_carrier);
पूर्णांक dev_get_phys_port_id(काष्ठा net_device *dev,
			 काष्ठा netdev_phys_item_id *ppid);
पूर्णांक dev_get_phys_port_name(काष्ठा net_device *dev,
			   अक्षर *name, माप_प्रकार len);
पूर्णांक dev_get_port_parent_id(काष्ठा net_device *dev,
			   काष्ठा netdev_phys_item_id *ppid, bool recurse);
bool netdev_port_same_parent_id(काष्ठा net_device *a, काष्ठा net_device *b);
पूर्णांक dev_change_proto_करोwn(काष्ठा net_device *dev, bool proto_करोwn);
पूर्णांक dev_change_proto_करोwn_generic(काष्ठा net_device *dev, bool proto_करोwn);
व्योम dev_change_proto_करोwn_reason(काष्ठा net_device *dev, अचिन्हित दीर्घ mask,
				  u32 value);
काष्ठा sk_buff *validate_xmit_skb_list(काष्ठा sk_buff *skb, काष्ठा net_device *dev, bool *again);
काष्ठा sk_buff *dev_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				    काष्ठा netdev_queue *txq, पूर्णांक *ret);

प्रकार पूर्णांक (*bpf_op_t)(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf);
पूर्णांक dev_change_xdp_fd(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack,
		      पूर्णांक fd, पूर्णांक expected_fd, u32 flags);
पूर्णांक bpf_xdp_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog);
u32 dev_xdp_prog_id(काष्ठा net_device *dev, क्रमागत bpf_xdp_mode mode);

पूर्णांक __dev_क्रमward_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
पूर्णांक dev_क्रमward_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
पूर्णांक dev_क्रमward_skb_nomtu(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
bool is_skb_क्रमwardable(स्थिर काष्ठा net_device *dev,
			स्थिर काष्ठा sk_buff *skb);

अटल __always_अंतरभूत bool __is_skb_क्रमwardable(स्थिर काष्ठा net_device *dev,
						 स्थिर काष्ठा sk_buff *skb,
						 स्थिर bool check_mtu)
अणु
	स्थिर u32 vlan_hdr_len = 4; /* VLAN_HLEN */
	अचिन्हित पूर्णांक len;

	अगर (!(dev->flags & IFF_UP))
		वापस false;

	अगर (!check_mtu)
		वापस true;

	len = dev->mtu + dev->hard_header_len + vlan_hdr_len;
	अगर (skb->len <= len)
		वापस true;

	/* अगर TSO is enabled, we करोn't care about the length as the packet
	 * could be क्रमwarded without being segmented beक्रमe
	 */
	अगर (skb_is_gso(skb))
		वापस true;

	वापस false;
पूर्ण

अटल __always_अंतरभूत पूर्णांक ____dev_क्रमward_skb(काष्ठा net_device *dev,
					       काष्ठा sk_buff *skb,
					       स्थिर bool check_mtu)
अणु
	अगर (skb_orphan_frags(skb, GFP_ATOMIC) ||
	    unlikely(!__is_skb_क्रमwardable(dev, skb, check_mtu))) अणु
		atomic_दीर्घ_inc(&dev->rx_dropped);
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	skb_scrub_packet(skb, true);
	skb->priority = 0;
	वापस 0;
पूर्ण

bool dev_nit_active(काष्ठा net_device *dev);
व्योम dev_queue_xmit_nit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

बाह्य पूर्णांक		netdev_budget;
बाह्य अचिन्हित पूर्णांक	netdev_budget_usecs;

/* Called by rtnetlink.c:rtnl_unlock() */
व्योम netdev_run_toकरो(व्योम);

/**
 *	dev_put - release reference to device
 *	@dev: network device
 *
 * Release reference to device to allow it to be मुक्तd.
 */
अटल अंतरभूत व्योम dev_put(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	this_cpu_dec(*dev->pcpu_refcnt);
#अन्यथा
	refcount_dec(&dev->dev_refcnt);
#पूर्ण_अगर
पूर्ण

/**
 *	dev_hold - get reference to device
 *	@dev: network device
 *
 * Hold reference to device to keep it from being मुक्तd.
 */
अटल अंतरभूत व्योम dev_hold(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_PCPU_DEV_REFCNT
	this_cpu_inc(*dev->pcpu_refcnt);
#अन्यथा
	refcount_inc(&dev->dev_refcnt);
#पूर्ण_अगर
पूर्ण

/* Carrier loss detection, dial on demand. The functions netअगर_carrier_on
 * and _off may be called from IRQ context, but it is caller
 * who is responsible क्रम serialization of these calls.
 *
 * The name carrier is inappropriate, these functions should really be
 * called netअगर_lowerlayer_*() because they represent the state of any
 * kind of lower layer not just hardware media.
 */

व्योम linkwatch_init_dev(काष्ठा net_device *dev);
व्योम linkwatch_fire_event(काष्ठा net_device *dev);
व्योम linkwatch_क्रमget_dev(काष्ठा net_device *dev);

/**
 *	netअगर_carrier_ok - test अगर carrier present
 *	@dev: network device
 *
 * Check अगर carrier is present on device
 */
अटल अंतरभूत bool netअगर_carrier_ok(स्थिर काष्ठा net_device *dev)
अणु
	वापस !test_bit(__LINK_STATE_NOCARRIER, &dev->state);
पूर्ण

अचिन्हित दीर्घ dev_trans_start(काष्ठा net_device *dev);

व्योम __netdev_watchकरोg_up(काष्ठा net_device *dev);

व्योम netअगर_carrier_on(काष्ठा net_device *dev);

व्योम netअगर_carrier_off(काष्ठा net_device *dev);

/**
 *	netअगर_करोrmant_on - mark device as करोrmant.
 *	@dev: network device
 *
 * Mark device as करोrmant (as per RFC2863).
 *
 * The करोrmant state indicates that the relevant पूर्णांकerface is not
 * actually in a condition to pass packets (i.e., it is not 'up') but is
 * in a "pending" state, रुकोing क्रम some बाह्यal event.  For "on-
 * demand" पूर्णांकerfaces, this new state identअगरies the situation where the
 * पूर्णांकerface is रुकोing क्रम events to place it in the up state.
 */
अटल अंतरभूत व्योम netअगर_करोrmant_on(काष्ठा net_device *dev)
अणु
	अगर (!test_and_set_bit(__LINK_STATE_DORMANT, &dev->state))
		linkwatch_fire_event(dev);
पूर्ण

/**
 *	netअगर_करोrmant_off - set device as not करोrmant.
 *	@dev: network device
 *
 * Device is not in करोrmant state.
 */
अटल अंतरभूत व्योम netअगर_करोrmant_off(काष्ठा net_device *dev)
अणु
	अगर (test_and_clear_bit(__LINK_STATE_DORMANT, &dev->state))
		linkwatch_fire_event(dev);
पूर्ण

/**
 *	netअगर_करोrmant - test अगर device is करोrmant
 *	@dev: network device
 *
 * Check अगर device is करोrmant.
 */
अटल अंतरभूत bool netअगर_करोrmant(स्थिर काष्ठा net_device *dev)
अणु
	वापस test_bit(__LINK_STATE_DORMANT, &dev->state);
पूर्ण


/**
 *	netअगर_testing_on - mark device as under test.
 *	@dev: network device
 *
 * Mark device as under test (as per RFC2863).
 *
 * The testing state indicates that some test(s) must be perक्रमmed on
 * the पूर्णांकerface. After completion, of the test, the पूर्णांकerface state
 * will change to up, करोrmant, or करोwn, as appropriate.
 */
अटल अंतरभूत व्योम netअगर_testing_on(काष्ठा net_device *dev)
अणु
	अगर (!test_and_set_bit(__LINK_STATE_TESTING, &dev->state))
		linkwatch_fire_event(dev);
पूर्ण

/**
 *	netअगर_testing_off - set device as not under test.
 *	@dev: network device
 *
 * Device is not in testing state.
 */
अटल अंतरभूत व्योम netअगर_testing_off(काष्ठा net_device *dev)
अणु
	अगर (test_and_clear_bit(__LINK_STATE_TESTING, &dev->state))
		linkwatch_fire_event(dev);
पूर्ण

/**
 *	netअगर_testing - test अगर device is under test
 *	@dev: network device
 *
 * Check अगर device is under test
 */
अटल अंतरभूत bool netअगर_testing(स्थिर काष्ठा net_device *dev)
अणु
	वापस test_bit(__LINK_STATE_TESTING, &dev->state);
पूर्ण


/**
 *	netअगर_oper_up - test अगर device is operational
 *	@dev: network device
 *
 * Check अगर carrier is operational
 */
अटल अंतरभूत bool netअगर_oper_up(स्थिर काष्ठा net_device *dev)
अणु
	वापस (dev->operstate == IF_OPER_UP ||
		dev->operstate == IF_OPER_UNKNOWN /* backward compat */);
पूर्ण

/**
 *	netअगर_device_present - is device available or हटाओd
 *	@dev: network device
 *
 * Check अगर device has not been हटाओd from प्रणाली.
 */
अटल अंतरभूत bool netअगर_device_present(स्थिर काष्ठा net_device *dev)
अणु
	वापस test_bit(__LINK_STATE_PRESENT, &dev->state);
पूर्ण

व्योम netअगर_device_detach(काष्ठा net_device *dev);

व्योम netअगर_device_attach(काष्ठा net_device *dev);

/*
 * Network पूर्णांकerface message level settings
 */

क्रमागत अणु
	NETIF_MSG_DRV_BIT,
	NETIF_MSG_PROBE_BIT,
	NETIF_MSG_LINK_BIT,
	NETIF_MSG_TIMER_BIT,
	NETIF_MSG_IFDOWN_BIT,
	NETIF_MSG_IFUP_BIT,
	NETIF_MSG_RX_ERR_BIT,
	NETIF_MSG_TX_ERR_BIT,
	NETIF_MSG_TX_QUEUED_BIT,
	NETIF_MSG_INTR_BIT,
	NETIF_MSG_TX_DONE_BIT,
	NETIF_MSG_RX_STATUS_BIT,
	NETIF_MSG_PKTDATA_BIT,
	NETIF_MSG_HW_BIT,
	NETIF_MSG_WOL_BIT,

	/* When you add a new bit above, update netअगर_msg_class_names array
	 * in net/ethtool/common.c
	 */
	NETIF_MSG_CLASS_COUNT,
पूर्ण;
/* Both ethtool_ops पूर्णांकerface and पूर्णांकernal driver implementation use u32 */
अटल_निश्चित(NETIF_MSG_CLASS_COUNT <= 32);

#घोषणा __NETIF_MSG_BIT(bit)	((u32)1 << (bit))
#घोषणा __NETIF_MSG(name)	__NETIF_MSG_BIT(NETIF_MSG_ ## name ## _BIT)

#घोषणा NETIF_MSG_DRV		__NETIF_MSG(DRV)
#घोषणा NETIF_MSG_PROBE		__NETIF_MSG(PROBE)
#घोषणा NETIF_MSG_LINK		__NETIF_MSG(LINK)
#घोषणा NETIF_MSG_TIMER		__NETIF_MSG(TIMER)
#घोषणा NETIF_MSG_IFDOWN	__NETIF_MSG(IFDOWN)
#घोषणा NETIF_MSG_IFUP		__NETIF_MSG(IFUP)
#घोषणा NETIF_MSG_RX_ERR	__NETIF_MSG(RX_ERR)
#घोषणा NETIF_MSG_TX_ERR	__NETIF_MSG(TX_ERR)
#घोषणा NETIF_MSG_TX_QUEUED	__NETIF_MSG(TX_QUEUED)
#घोषणा NETIF_MSG_INTR		__NETIF_MSG(INTR)
#घोषणा NETIF_MSG_TX_DONE	__NETIF_MSG(TX_DONE)
#घोषणा NETIF_MSG_RX_STATUS	__NETIF_MSG(RX_STATUS)
#घोषणा NETIF_MSG_PKTDATA	__NETIF_MSG(PKTDATA)
#घोषणा NETIF_MSG_HW		__NETIF_MSG(HW)
#घोषणा NETIF_MSG_WOL		__NETIF_MSG(WOL)

#घोषणा netअगर_msg_drv(p)	((p)->msg_enable & NETIF_MSG_DRV)
#घोषणा netअगर_msg_probe(p)	((p)->msg_enable & NETIF_MSG_PROBE)
#घोषणा netअगर_msg_link(p)	((p)->msg_enable & NETIF_MSG_LINK)
#घोषणा netअगर_msg_समयr(p)	((p)->msg_enable & NETIF_MSG_TIMER)
#घोषणा netअगर_msg_अगरकरोwn(p)	((p)->msg_enable & NETIF_MSG_IFDOWN)
#घोषणा netअगर_msg_अगरup(p)	((p)->msg_enable & NETIF_MSG_IFUP)
#घोषणा netअगर_msg_rx_err(p)	((p)->msg_enable & NETIF_MSG_RX_ERR)
#घोषणा netअगर_msg_tx_err(p)	((p)->msg_enable & NETIF_MSG_TX_ERR)
#घोषणा netअगर_msg_tx_queued(p)	((p)->msg_enable & NETIF_MSG_TX_QUEUED)
#घोषणा netअगर_msg_पूर्णांकr(p)	((p)->msg_enable & NETIF_MSG_INTR)
#घोषणा netअगर_msg_tx_करोne(p)	((p)->msg_enable & NETIF_MSG_TX_DONE)
#घोषणा netअगर_msg_rx_status(p)	((p)->msg_enable & NETIF_MSG_RX_STATUS)
#घोषणा netअगर_msg_pktdata(p)	((p)->msg_enable & NETIF_MSG_PKTDATA)
#घोषणा netअगर_msg_hw(p)		((p)->msg_enable & NETIF_MSG_HW)
#घोषणा netअगर_msg_wol(p)	((p)->msg_enable & NETIF_MSG_WOL)

अटल अंतरभूत u32 netअगर_msg_init(पूर्णांक debug_value, पूर्णांक शेष_msg_enable_bits)
अणु
	/* use शेष */
	अगर (debug_value < 0 || debug_value >= (माप(u32) * 8))
		वापस शेष_msg_enable_bits;
	अगर (debug_value == 0)	/* no output */
		वापस 0;
	/* set low N bits */
	वापस (1U << debug_value) - 1;
पूर्ण

अटल अंतरभूत व्योम __netअगर_tx_lock(काष्ठा netdev_queue *txq, पूर्णांक cpu)
अणु
	spin_lock(&txq->_xmit_lock);
	txq->xmit_lock_owner = cpu;
पूर्ण

अटल अंतरभूत bool __netअगर_tx_acquire(काष्ठा netdev_queue *txq)
अणु
	__acquire(&txq->_xmit_lock);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम __netअगर_tx_release(काष्ठा netdev_queue *txq)
अणु
	__release(&txq->_xmit_lock);
पूर्ण

अटल अंतरभूत व्योम __netअगर_tx_lock_bh(काष्ठा netdev_queue *txq)
अणु
	spin_lock_bh(&txq->_xmit_lock);
	txq->xmit_lock_owner = smp_processor_id();
पूर्ण

अटल अंतरभूत bool __netअगर_tx_trylock(काष्ठा netdev_queue *txq)
अणु
	bool ok = spin_trylock(&txq->_xmit_lock);
	अगर (likely(ok))
		txq->xmit_lock_owner = smp_processor_id();
	वापस ok;
पूर्ण

अटल अंतरभूत व्योम __netअगर_tx_unlock(काष्ठा netdev_queue *txq)
अणु
	txq->xmit_lock_owner = -1;
	spin_unlock(&txq->_xmit_lock);
पूर्ण

अटल अंतरभूत व्योम __netअगर_tx_unlock_bh(काष्ठा netdev_queue *txq)
अणु
	txq->xmit_lock_owner = -1;
	spin_unlock_bh(&txq->_xmit_lock);
पूर्ण

अटल अंतरभूत व्योम txq_trans_update(काष्ठा netdev_queue *txq)
अणु
	अगर (txq->xmit_lock_owner != -1)
		txq->trans_start = jअगरfies;
पूर्ण

/* legacy drivers only, netdev_start_xmit() sets txq->trans_start */
अटल अंतरभूत व्योम netअगर_trans_update(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, 0);

	अगर (txq->trans_start != jअगरfies)
		txq->trans_start = jअगरfies;
पूर्ण

/**
 *	netअगर_tx_lock - grab network device transmit lock
 *	@dev: network device
 *
 * Get network device transmit lock
 */
अटल अंतरभूत व्योम netअगर_tx_lock(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक cpu;

	spin_lock(&dev->tx_global_lock);
	cpu = smp_processor_id();
	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);

		/* We are the only thपढ़ो of execution करोing a
		 * मुक्तze, but we have to grab the _xmit_lock in
		 * order to synchronize with thपढ़ोs which are in
		 * the ->hard_start_xmit() handler and alपढ़ोy
		 * checked the frozen bit.
		 */
		__netअगर_tx_lock(txq, cpu);
		set_bit(__QUEUE_STATE_FROZEN, &txq->state);
		__netअगर_tx_unlock(txq);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम netअगर_tx_lock_bh(काष्ठा net_device *dev)
अणु
	local_bh_disable();
	netअगर_tx_lock(dev);
पूर्ण

अटल अंतरभूत व्योम netअगर_tx_unlock(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);

		/* No need to grab the _xmit_lock here.  If the
		 * queue is not stopped क्रम another reason, we
		 * क्रमce a schedule.
		 */
		clear_bit(__QUEUE_STATE_FROZEN, &txq->state);
		netअगर_schedule_queue(txq);
	पूर्ण
	spin_unlock(&dev->tx_global_lock);
पूर्ण

अटल अंतरभूत व्योम netअगर_tx_unlock_bh(काष्ठा net_device *dev)
अणु
	netअगर_tx_unlock(dev);
	local_bh_enable();
पूर्ण

#घोषणा HARD_TX_LOCK(dev, txq, cpu) अणु			\
	अगर ((dev->features & NETIF_F_LLTX) == 0) अणु	\
		__netअगर_tx_lock(txq, cpu);		\
	पूर्ण अन्यथा अणु					\
		__netअगर_tx_acquire(txq);		\
	पूर्ण						\
पूर्ण

#घोषणा HARD_TX_TRYLOCK(dev, txq)			\
	(((dev->features & NETIF_F_LLTX) == 0) ?	\
		__netअगर_tx_trylock(txq) :		\
		__netअगर_tx_acquire(txq))

#घोषणा HARD_TX_UNLOCK(dev, txq) अणु			\
	अगर ((dev->features & NETIF_F_LLTX) == 0) अणु	\
		__netअगर_tx_unlock(txq);			\
	पूर्ण अन्यथा अणु					\
		__netअगर_tx_release(txq);		\
	पूर्ण						\
पूर्ण

अटल अंतरभूत व्योम netअगर_tx_disable(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक cpu;

	local_bh_disable();
	cpu = smp_processor_id();
	spin_lock(&dev->tx_global_lock);
	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, i);

		__netअगर_tx_lock(txq, cpu);
		netअगर_tx_stop_queue(txq);
		__netअगर_tx_unlock(txq);
	पूर्ण
	spin_unlock(&dev->tx_global_lock);
	local_bh_enable();
पूर्ण

अटल अंतरभूत व्योम netअगर_addr_lock(काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर nest_level = 0;

#अगर_घोषित CONFIG_LOCKDEP
	nest_level = dev->nested_level;
#पूर्ण_अगर
	spin_lock_nested(&dev->addr_list_lock, nest_level);
पूर्ण

अटल अंतरभूत व्योम netअगर_addr_lock_bh(काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर nest_level = 0;

#अगर_घोषित CONFIG_LOCKDEP
	nest_level = dev->nested_level;
#पूर्ण_अगर
	local_bh_disable();
	spin_lock_nested(&dev->addr_list_lock, nest_level);
पूर्ण

अटल अंतरभूत व्योम netअगर_addr_unlock(काष्ठा net_device *dev)
अणु
	spin_unlock(&dev->addr_list_lock);
पूर्ण

अटल अंतरभूत व्योम netअगर_addr_unlock_bh(काष्ठा net_device *dev)
अणु
	spin_unlock_bh(&dev->addr_list_lock);
पूर्ण

/*
 * dev_addrs walker. Should be used only क्रम पढ़ो access. Call with
 * rcu_पढ़ो_lock held.
 */
#घोषणा क्रम_each_dev_addr(dev, ha) \
		list_क्रम_each_entry_rcu(ha, &dev->dev_addrs.list, list)

/* These functions live अन्यथाwhere (drivers/net/net_init.c, but related) */

व्योम ether_setup(काष्ठा net_device *dev);

/* Support क्रम loadable net-drivers */
काष्ठा net_device *alloc_netdev_mqs(पूर्णांक माप_priv, स्थिर अक्षर *name,
				    अचिन्हित अक्षर name_assign_type,
				    व्योम (*setup)(काष्ठा net_device *),
				    अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs);
#घोषणा alloc_netdev(माप_priv, name, name_assign_type, setup) \
	alloc_netdev_mqs(माप_priv, name, name_assign_type, setup, 1, 1)

#घोषणा alloc_netdev_mq(माप_priv, name, name_assign_type, setup, count) \
	alloc_netdev_mqs(माप_priv, name, name_assign_type, setup, count, \
			 count)

पूर्णांक रेजिस्टर_netdev(काष्ठा net_device *dev);
व्योम unरेजिस्टर_netdev(काष्ठा net_device *dev);

पूर्णांक devm_रेजिस्टर_netdev(काष्ठा device *dev, काष्ठा net_device *ndev);

/* General hardware address lists handling functions */
पूर्णांक __hw_addr_sync(काष्ठा netdev_hw_addr_list *to_list,
		   काष्ठा netdev_hw_addr_list *from_list, पूर्णांक addr_len);
व्योम __hw_addr_unsync(काष्ठा netdev_hw_addr_list *to_list,
		      काष्ठा netdev_hw_addr_list *from_list, पूर्णांक addr_len);
पूर्णांक __hw_addr_sync_dev(काष्ठा netdev_hw_addr_list *list,
		       काष्ठा net_device *dev,
		       पूर्णांक (*sync)(काष्ठा net_device *, स्थिर अचिन्हित अक्षर *),
		       पूर्णांक (*unsync)(काष्ठा net_device *,
				     स्थिर अचिन्हित अक्षर *));
पूर्णांक __hw_addr_ref_sync_dev(काष्ठा netdev_hw_addr_list *list,
			   काष्ठा net_device *dev,
			   पूर्णांक (*sync)(काष्ठा net_device *,
				       स्थिर अचिन्हित अक्षर *, पूर्णांक),
			   पूर्णांक (*unsync)(काष्ठा net_device *,
					 स्थिर अचिन्हित अक्षर *, पूर्णांक));
व्योम __hw_addr_ref_unsync_dev(काष्ठा netdev_hw_addr_list *list,
			      काष्ठा net_device *dev,
			      पूर्णांक (*unsync)(काष्ठा net_device *,
					    स्थिर अचिन्हित अक्षर *, पूर्णांक));
व्योम __hw_addr_unsync_dev(काष्ठा netdev_hw_addr_list *list,
			  काष्ठा net_device *dev,
			  पूर्णांक (*unsync)(काष्ठा net_device *,
					स्थिर अचिन्हित अक्षर *));
व्योम __hw_addr_init(काष्ठा netdev_hw_addr_list *list);

/* Functions used क्रम device addresses handling */
पूर्णांक dev_addr_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
		 अचिन्हित अक्षर addr_type);
पूर्णांक dev_addr_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr,
		 अचिन्हित अक्षर addr_type);
व्योम dev_addr_flush(काष्ठा net_device *dev);
पूर्णांक dev_addr_init(काष्ठा net_device *dev);

/* Functions used क्रम unicast addresses handling */
पूर्णांक dev_uc_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_uc_add_excl(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_uc_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_uc_sync(काष्ठा net_device *to, काष्ठा net_device *from);
पूर्णांक dev_uc_sync_multiple(काष्ठा net_device *to, काष्ठा net_device *from);
व्योम dev_uc_unsync(काष्ठा net_device *to, काष्ठा net_device *from);
व्योम dev_uc_flush(काष्ठा net_device *dev);
व्योम dev_uc_init(काष्ठा net_device *dev);

/**
 *  __dev_uc_sync - Synchonize device's unicast list
 *  @dev:  device to sync
 *  @sync: function to call अगर address should be added
 *  @unsync: function to call अगर address should be हटाओd
 *
 *  Add newly added addresses to the पूर्णांकerface, and release
 *  addresses that have been deleted.
 */
अटल अंतरभूत पूर्णांक __dev_uc_sync(काष्ठा net_device *dev,
				पूर्णांक (*sync)(काष्ठा net_device *,
					    स्थिर अचिन्हित अक्षर *),
				पूर्णांक (*unsync)(काष्ठा net_device *,
					      स्थिर अचिन्हित अक्षर *))
अणु
	वापस __hw_addr_sync_dev(&dev->uc, dev, sync, unsync);
पूर्ण

/**
 *  __dev_uc_unsync - Remove synchronized addresses from device
 *  @dev:  device to sync
 *  @unsync: function to call अगर address should be हटाओd
 *
 *  Remove all addresses that were added to the device by dev_uc_sync().
 */
अटल अंतरभूत व्योम __dev_uc_unsync(काष्ठा net_device *dev,
				   पूर्णांक (*unsync)(काष्ठा net_device *,
						 स्थिर अचिन्हित अक्षर *))
अणु
	__hw_addr_unsync_dev(&dev->uc, dev, unsync);
पूर्ण

/* Functions used क्रम multicast addresses handling */
पूर्णांक dev_mc_add(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_mc_add_global(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_mc_add_excl(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_mc_del(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_mc_del_global(काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr);
पूर्णांक dev_mc_sync(काष्ठा net_device *to, काष्ठा net_device *from);
पूर्णांक dev_mc_sync_multiple(काष्ठा net_device *to, काष्ठा net_device *from);
व्योम dev_mc_unsync(काष्ठा net_device *to, काष्ठा net_device *from);
व्योम dev_mc_flush(काष्ठा net_device *dev);
व्योम dev_mc_init(काष्ठा net_device *dev);

/**
 *  __dev_mc_sync - Synchonize device's multicast list
 *  @dev:  device to sync
 *  @sync: function to call अगर address should be added
 *  @unsync: function to call अगर address should be हटाओd
 *
 *  Add newly added addresses to the पूर्णांकerface, and release
 *  addresses that have been deleted.
 */
अटल अंतरभूत पूर्णांक __dev_mc_sync(काष्ठा net_device *dev,
				पूर्णांक (*sync)(काष्ठा net_device *,
					    स्थिर अचिन्हित अक्षर *),
				पूर्णांक (*unsync)(काष्ठा net_device *,
					      स्थिर अचिन्हित अक्षर *))
अणु
	वापस __hw_addr_sync_dev(&dev->mc, dev, sync, unsync);
पूर्ण

/**
 *  __dev_mc_unsync - Remove synchronized addresses from device
 *  @dev:  device to sync
 *  @unsync: function to call अगर address should be हटाओd
 *
 *  Remove all addresses that were added to the device by dev_mc_sync().
 */
अटल अंतरभूत व्योम __dev_mc_unsync(काष्ठा net_device *dev,
				   पूर्णांक (*unsync)(काष्ठा net_device *,
						 स्थिर अचिन्हित अक्षर *))
अणु
	__hw_addr_unsync_dev(&dev->mc, dev, unsync);
पूर्ण

/* Functions used क्रम secondary unicast and multicast support */
व्योम dev_set_rx_mode(काष्ठा net_device *dev);
व्योम __dev_set_rx_mode(काष्ठा net_device *dev);
पूर्णांक dev_set_promiscuity(काष्ठा net_device *dev, पूर्णांक inc);
पूर्णांक dev_set_allmulti(काष्ठा net_device *dev, पूर्णांक inc);
व्योम netdev_state_change(काष्ठा net_device *dev);
व्योम __netdev_notअगरy_peers(काष्ठा net_device *dev);
व्योम netdev_notअगरy_peers(काष्ठा net_device *dev);
व्योम netdev_features_change(काष्ठा net_device *dev);
/* Load a device via the kmod */
व्योम dev_load(काष्ठा net *net, स्थिर अक्षर *name);
काष्ठा rtnl_link_stats64 *dev_get_stats(काष्ठा net_device *dev,
					काष्ठा rtnl_link_stats64 *storage);
व्योम netdev_stats_to_stats64(काष्ठा rtnl_link_stats64 *stats64,
			     स्थिर काष्ठा net_device_stats *netdev_stats);
व्योम dev_fetch_sw_netstats(काष्ठा rtnl_link_stats64 *s,
			   स्थिर काष्ठा pcpu_sw_netstats __percpu *netstats);
व्योम dev_get_tstats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *s);

बाह्य पूर्णांक		netdev_max_backlog;
बाह्य पूर्णांक		netdev_tstamp_prequeue;
बाह्य पूर्णांक		netdev_unरेजिस्टर_समयout_secs;
बाह्य पूर्णांक		weight_p;
बाह्य पूर्णांक		dev_weight_rx_bias;
बाह्य पूर्णांक		dev_weight_tx_bias;
बाह्य पूर्णांक		dev_rx_weight;
बाह्य पूर्णांक		dev_tx_weight;
बाह्य पूर्णांक		gro_normal_batch;

क्रमागत अणु
	NESTED_SYNC_IMM_BIT,
	NESTED_SYNC_TODO_BIT,
पूर्ण;

#घोषणा __NESTED_SYNC_BIT(bit)	((u32)1 << (bit))
#घोषणा __NESTED_SYNC(name)	__NESTED_SYNC_BIT(NESTED_SYNC_ ## name ## _BIT)

#घोषणा NESTED_SYNC_IMM		__NESTED_SYNC(IMM)
#घोषणा NESTED_SYNC_TODO	__NESTED_SYNC(TODO)

काष्ठा netdev_nested_priv अणु
	अचिन्हित अक्षर flags;
	व्योम *data;
पूर्ण;

bool netdev_has_upper_dev(काष्ठा net_device *dev, काष्ठा net_device *upper_dev);
काष्ठा net_device *netdev_upper_get_next_dev_rcu(काष्ठा net_device *dev,
						     काष्ठा list_head **iter);
काष्ठा net_device *netdev_all_upper_get_next_dev_rcu(काष्ठा net_device *dev,
						     काष्ठा list_head **iter);

#अगर_घोषित CONFIG_LOCKDEP
अटल LIST_HEAD(net_unlink_list);

अटल अंतरभूत व्योम net_unlink_toकरो(काष्ठा net_device *dev)
अणु
	अगर (list_empty(&dev->unlink_list))
		list_add_tail(&dev->unlink_list, &net_unlink_list);
पूर्ण
#पूर्ण_अगर

/* iterate through upper list, must be called under RCU पढ़ो lock */
#घोषणा netdev_क्रम_each_upper_dev_rcu(dev, updev, iter) \
	क्रम (iter = &(dev)->adj_list.upper, \
	     updev = netdev_upper_get_next_dev_rcu(dev, &(iter)); \
	     updev; \
	     updev = netdev_upper_get_next_dev_rcu(dev, &(iter)))

पूर्णांक netdev_walk_all_upper_dev_rcu(काष्ठा net_device *dev,
				  पूर्णांक (*fn)(काष्ठा net_device *upper_dev,
					    काष्ठा netdev_nested_priv *priv),
				  काष्ठा netdev_nested_priv *priv);

bool netdev_has_upper_dev_all_rcu(काष्ठा net_device *dev,
				  काष्ठा net_device *upper_dev);

bool netdev_has_any_upper_dev(काष्ठा net_device *dev);

व्योम *netdev_lower_get_next_निजी(काष्ठा net_device *dev,
				    काष्ठा list_head **iter);
व्योम *netdev_lower_get_next_निजी_rcu(काष्ठा net_device *dev,
					काष्ठा list_head **iter);

#घोषणा netdev_क्रम_each_lower_निजी(dev, priv, iter) \
	क्रम (iter = (dev)->adj_list.lower.next, \
	     priv = netdev_lower_get_next_निजी(dev, &(iter)); \
	     priv; \
	     priv = netdev_lower_get_next_निजी(dev, &(iter)))

#घोषणा netdev_क्रम_each_lower_निजी_rcu(dev, priv, iter) \
	क्रम (iter = &(dev)->adj_list.lower, \
	     priv = netdev_lower_get_next_निजी_rcu(dev, &(iter)); \
	     priv; \
	     priv = netdev_lower_get_next_निजी_rcu(dev, &(iter)))

व्योम *netdev_lower_get_next(काष्ठा net_device *dev,
				काष्ठा list_head **iter);

#घोषणा netdev_क्रम_each_lower_dev(dev, ldev, iter) \
	क्रम (iter = (dev)->adj_list.lower.next, \
	     ldev = netdev_lower_get_next(dev, &(iter)); \
	     ldev; \
	     ldev = netdev_lower_get_next(dev, &(iter)))

काष्ठा net_device *netdev_next_lower_dev_rcu(काष्ठा net_device *dev,
					     काष्ठा list_head **iter);
पूर्णांक netdev_walk_all_lower_dev(काष्ठा net_device *dev,
			      पूर्णांक (*fn)(काष्ठा net_device *lower_dev,
					काष्ठा netdev_nested_priv *priv),
			      काष्ठा netdev_nested_priv *priv);
पूर्णांक netdev_walk_all_lower_dev_rcu(काष्ठा net_device *dev,
				  पूर्णांक (*fn)(काष्ठा net_device *lower_dev,
					    काष्ठा netdev_nested_priv *priv),
				  काष्ठा netdev_nested_priv *priv);

व्योम *netdev_adjacent_get_निजी(काष्ठा list_head *adj_list);
व्योम *netdev_lower_get_first_निजी_rcu(काष्ठा net_device *dev);
काष्ठा net_device *netdev_master_upper_dev_get(काष्ठा net_device *dev);
काष्ठा net_device *netdev_master_upper_dev_get_rcu(काष्ठा net_device *dev);
पूर्णांक netdev_upper_dev_link(काष्ठा net_device *dev, काष्ठा net_device *upper_dev,
			  काष्ठा netlink_ext_ack *extack);
पूर्णांक netdev_master_upper_dev_link(काष्ठा net_device *dev,
				 काष्ठा net_device *upper_dev,
				 व्योम *upper_priv, व्योम *upper_info,
				 काष्ठा netlink_ext_ack *extack);
व्योम netdev_upper_dev_unlink(काष्ठा net_device *dev,
			     काष्ठा net_device *upper_dev);
पूर्णांक netdev_adjacent_change_prepare(काष्ठा net_device *old_dev,
				   काष्ठा net_device *new_dev,
				   काष्ठा net_device *dev,
				   काष्ठा netlink_ext_ack *extack);
व्योम netdev_adjacent_change_commit(काष्ठा net_device *old_dev,
				   काष्ठा net_device *new_dev,
				   काष्ठा net_device *dev);
व्योम netdev_adjacent_change_पात(काष्ठा net_device *old_dev,
				  काष्ठा net_device *new_dev,
				  काष्ठा net_device *dev);
व्योम netdev_adjacent_नाम_links(काष्ठा net_device *dev, अक्षर *oldname);
व्योम *netdev_lower_dev_get_निजी(काष्ठा net_device *dev,
				   काष्ठा net_device *lower_dev);
व्योम netdev_lower_state_changed(काष्ठा net_device *lower_dev,
				व्योम *lower_state_info);

/* RSS keys are 40 or 52 bytes दीर्घ */
#घोषणा NETDEV_RSS_KEY_LEN 52
बाह्य u8 netdev_rss_key[NETDEV_RSS_KEY_LEN] __पढ़ो_mostly;
व्योम netdev_rss_key_fill(व्योम *buffer, माप_प्रकार len);

पूर्णांक skb_checksum_help(काष्ठा sk_buff *skb);
पूर्णांक skb_crc32c_csum_help(काष्ठा sk_buff *skb);
पूर्णांक skb_csum_hwoffload_help(काष्ठा sk_buff *skb,
			    स्थिर netdev_features_t features);

काष्ठा sk_buff *__skb_gso_segment(काष्ठा sk_buff *skb,
				  netdev_features_t features, bool tx_path);
काष्ठा sk_buff *skb_mac_gso_segment(काष्ठा sk_buff *skb,
				    netdev_features_t features);

काष्ठा netdev_bonding_info अणु
	अगरslave	slave;
	अगरbond	master;
पूर्ण;

काष्ठा netdev_notअगरier_bonding_info अणु
	काष्ठा netdev_notअगरier_info info; /* must be first */
	काष्ठा netdev_bonding_info  bonding_info;
पूर्ण;

व्योम netdev_bonding_info_change(काष्ठा net_device *dev,
				काष्ठा netdev_bonding_info *bonding_info);

#अगर IS_ENABLED(CONFIG_ETHTOOL_NETLINK)
व्योम ethtool_notअगरy(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd, स्थिर व्योम *data);
#अन्यथा
अटल अंतरभूत व्योम ethtool_notअगरy(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd,
				  स्थिर व्योम *data)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत
काष्ठा sk_buff *skb_gso_segment(काष्ठा sk_buff *skb, netdev_features_t features)
अणु
	वापस __skb_gso_segment(skb, features, true);
पूर्ण
__be16 skb_network_protocol(काष्ठा sk_buff *skb, पूर्णांक *depth);

अटल अंतरभूत bool can_checksum_protocol(netdev_features_t features,
					 __be16 protocol)
अणु
	अगर (protocol == htons(ETH_P_FCOE))
		वापस !!(features & NETIF_F_FCOE_CRC);

	/* Assume this is an IP checksum (not SCTP CRC) */

	अगर (features & NETIF_F_HW_CSUM) अणु
		/* Can checksum everything */
		वापस true;
	पूर्ण

	चयन (protocol) अणु
	हाल htons(ETH_P_IP):
		वापस !!(features & NETIF_F_IP_CSUM);
	हाल htons(ETH_P_IPV6):
		वापस !!(features & NETIF_F_IPV6_CSUM);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_BUG
व्योम netdev_rx_csum_fault(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
#अन्यथा
अटल अंतरभूत व्योम netdev_rx_csum_fault(काष्ठा net_device *dev,
					काष्ठा sk_buff *skb)
अणु
पूर्ण
#पूर्ण_अगर
/* rx skb बारtamps */
व्योम net_enable_बारtamp(व्योम);
व्योम net_disable_बारtamp(व्योम);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक __init dev_proc_init(व्योम);
#अन्यथा
#घोषणा dev_proc_init() 0
#पूर्ण_अगर

अटल अंतरभूत netdev_tx_t __netdev_start_xmit(स्थिर काष्ठा net_device_ops *ops,
					      काष्ठा sk_buff *skb, काष्ठा net_device *dev,
					      bool more)
अणु
	__this_cpu_ग_लिखो(softnet_data.xmit.more, more);
	वापस ops->nकरो_start_xmit(skb, dev);
पूर्ण

अटल अंतरभूत bool netdev_xmit_more(व्योम)
अणु
	वापस __this_cpu_पढ़ो(softnet_data.xmit.more);
पूर्ण

अटल अंतरभूत netdev_tx_t netdev_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
					    काष्ठा netdev_queue *txq, bool more)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	netdev_tx_t rc;

	rc = __netdev_start_xmit(ops, skb, dev, more);
	अगर (rc == NETDEV_TX_OK)
		txq_trans_update(txq);

	वापस rc;
पूर्ण

पूर्णांक netdev_class_create_file_ns(स्थिर काष्ठा class_attribute *class_attr,
				स्थिर व्योम *ns);
व्योम netdev_class_हटाओ_file_ns(स्थिर काष्ठा class_attribute *class_attr,
				 स्थिर व्योम *ns);

बाह्य स्थिर काष्ठा kobj_ns_type_operations net_ns_type_operations;

स्थिर अक्षर *netdev_drivername(स्थिर काष्ठा net_device *dev);

व्योम linkwatch_run_queue(व्योम);

अटल अंतरभूत netdev_features_t netdev_पूर्णांकersect_features(netdev_features_t f1,
							  netdev_features_t f2)
अणु
	अगर ((f1 ^ f2) & NETIF_F_HW_CSUM) अणु
		अगर (f1 & NETIF_F_HW_CSUM)
			f1 |= (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
		अन्यथा
			f2 |= (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
	पूर्ण

	वापस f1 & f2;
पूर्ण

अटल अंतरभूत netdev_features_t netdev_get_wanted_features(
	काष्ठा net_device *dev)
अणु
	वापस (dev->features & ~dev->hw_features) | dev->wanted_features;
पूर्ण
netdev_features_t netdev_increment_features(netdev_features_t all,
	netdev_features_t one, netdev_features_t mask);

/* Allow TSO being used on stacked device :
 * Perक्रमming the GSO segmentation beक्रमe last device
 * is a perक्रमmance improvement.
 */
अटल अंतरभूत netdev_features_t netdev_add_tso_features(netdev_features_t features,
							netdev_features_t mask)
अणु
	वापस netdev_increment_features(features, NETIF_F_ALL_TSO, mask);
पूर्ण

पूर्णांक __netdev_update_features(काष्ठा net_device *dev);
व्योम netdev_update_features(काष्ठा net_device *dev);
व्योम netdev_change_features(काष्ठा net_device *dev);

व्योम netअगर_stacked_transfer_operstate(स्थिर काष्ठा net_device *rootdev,
					काष्ठा net_device *dev);

netdev_features_t passthru_features_check(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev,
					  netdev_features_t features);
netdev_features_t netअगर_skb_features(काष्ठा sk_buff *skb);

अटल अंतरभूत bool net_gso_ok(netdev_features_t features, पूर्णांक gso_type)
अणु
	netdev_features_t feature = (netdev_features_t)gso_type << NETIF_F_GSO_SHIFT;

	/* check flags correspondence */
	BUILD_BUG_ON(SKB_GSO_TCPV4   != (NETIF_F_TSO >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_DODGY   != (NETIF_F_GSO_ROBUST >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_TCP_ECN != (NETIF_F_TSO_ECN >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_TCP_FIXEDID != (NETIF_F_TSO_MANGLEID >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_TCPV6   != (NETIF_F_TSO6 >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_FCOE    != (NETIF_F_FSO >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_GRE     != (NETIF_F_GSO_GRE >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_GRE_CSUM != (NETIF_F_GSO_GRE_CSUM >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_IPXIP4  != (NETIF_F_GSO_IPXIP4 >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_IPXIP6  != (NETIF_F_GSO_IPXIP6 >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_UDP_TUNNEL != (NETIF_F_GSO_UDP_TUNNEL >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_UDP_TUNNEL_CSUM != (NETIF_F_GSO_UDP_TUNNEL_CSUM >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_PARTIAL != (NETIF_F_GSO_PARTIAL >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_TUNNEL_REMCSUM != (NETIF_F_GSO_TUNNEL_REMCSUM >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_SCTP    != (NETIF_F_GSO_SCTP >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_ESP != (NETIF_F_GSO_ESP >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_UDP != (NETIF_F_GSO_UDP >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_UDP_L4 != (NETIF_F_GSO_UDP_L4 >> NETIF_F_GSO_SHIFT));
	BUILD_BUG_ON(SKB_GSO_FRAGLIST != (NETIF_F_GSO_FRAGLIST >> NETIF_F_GSO_SHIFT));

	वापस (features & feature) == feature;
पूर्ण

अटल अंतरभूत bool skb_gso_ok(काष्ठा sk_buff *skb, netdev_features_t features)
अणु
	वापस net_gso_ok(features, skb_shinfo(skb)->gso_type) &&
	       (!skb_has_frag_list(skb) || (features & NETIF_F_FRAGLIST));
पूर्ण

अटल अंतरभूत bool netअगर_needs_gso(काष्ठा sk_buff *skb,
				   netdev_features_t features)
अणु
	वापस skb_is_gso(skb) && (!skb_gso_ok(skb, features) ||
		unlikely((skb->ip_summed != CHECKSUM_PARTIAL) &&
			 (skb->ip_summed != CHECKSUM_UNNECESSARY)));
पूर्ण

अटल अंतरभूत व्योम netअगर_set_gso_max_size(काष्ठा net_device *dev,
					  अचिन्हित पूर्णांक size)
अणु
	dev->gso_max_size = size;
पूर्ण

अटल अंतरभूत व्योम skb_gso_error_unwind(काष्ठा sk_buff *skb, __be16 protocol,
					पूर्णांक pulled_hlen, u16 mac_offset,
					पूर्णांक mac_len)
अणु
	skb->protocol = protocol;
	skb->encapsulation = 1;
	skb_push(skb, pulled_hlen);
	skb_reset_transport_header(skb);
	skb->mac_header = mac_offset;
	skb->network_header = skb->mac_header + mac_len;
	skb->mac_len = mac_len;
पूर्ण

अटल अंतरभूत bool netअगर_is_macsec(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_MACSEC;
पूर्ण

अटल अंतरभूत bool netअगर_is_macvlan(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_MACVLAN;
पूर्ण

अटल अंतरभूत bool netअगर_is_macvlan_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_MACVLAN_PORT;
पूर्ण

अटल अंतरभूत bool netअगर_is_bond_master(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->flags & IFF_MASTER && dev->priv_flags & IFF_BONDING;
पूर्ण

अटल अंतरभूत bool netअगर_is_bond_slave(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->flags & IFF_SLAVE && dev->priv_flags & IFF_BONDING;
पूर्ण

अटल अंतरभूत bool netअगर_supports_nofcs(काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_SUPP_NOFCS;
पूर्ण

अटल अंतरभूत bool netअगर_has_l3_rx_handler(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_L3MDEV_RX_HANDLER;
पूर्ण

अटल अंतरभूत bool netअगर_is_l3_master(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_L3MDEV_MASTER;
पूर्ण

अटल अंतरभूत bool netअगर_is_l3_slave(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_L3MDEV_SLAVE;
पूर्ण

अटल अंतरभूत bool netअगर_is_bridge_master(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_EBRIDGE;
पूर्ण

अटल अंतरभूत bool netअगर_is_bridge_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_BRIDGE_PORT;
पूर्ण

अटल अंतरभूत bool netअगर_is_ovs_master(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_OPENVSWITCH;
पूर्ण

अटल अंतरभूत bool netअगर_is_ovs_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_OVS_DATAPATH;
पूर्ण

अटल अंतरभूत bool netअगर_is_any_bridge_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_is_bridge_port(dev) || netअगर_is_ovs_port(dev);
पूर्ण

अटल अंतरभूत bool netअगर_is_team_master(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_TEAM;
पूर्ण

अटल अंतरभूत bool netअगर_is_team_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_TEAM_PORT;
पूर्ण

अटल अंतरभूत bool netअगर_is_lag_master(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_is_bond_master(dev) || netअगर_is_team_master(dev);
पूर्ण

अटल अंतरभूत bool netअगर_is_lag_port(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_is_bond_slave(dev) || netअगर_is_team_port(dev);
पूर्ण

अटल अंतरभूत bool netअगर_is_rxfh_configured(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_RXFH_CONFIGURED;
पूर्ण

अटल अंतरभूत bool netअगर_is_failover(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_FAILOVER;
पूर्ण

अटल अंतरभूत bool netअगर_is_failover_slave(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->priv_flags & IFF_FAILOVER_SLAVE;
पूर्ण

/* This device needs to keep skb dst क्रम qdisc enqueue or nकरो_start_xmit() */
अटल अंतरभूत व्योम netअगर_keep_dst(काष्ठा net_device *dev)
अणु
	dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE | IFF_XMIT_DST_RELEASE_PERM);
पूर्ण

/* वापस true अगर dev can't cope with mtu frames that need vlan tag insertion */
अटल अंतरभूत bool netअगर_reduces_vlan_mtu(काष्ठा net_device *dev)
अणु
	/* TODO: reserve and use an additional IFF bit, अगर we get more users */
	वापस dev->priv_flags & IFF_MACSEC;
पूर्ण

बाह्य काष्ठा pernet_operations __net_initdata loopback_net_ops;

/* Logging, debugging and troubleshooting/diagnostic helpers. */

/* netdev_prपूर्णांकk helpers, similar to dev_prपूर्णांकk */

अटल अंतरभूत स्थिर अक्षर *netdev_name(स्थिर काष्ठा net_device *dev)
अणु
	अगर (!dev->name[0] || म_अक्षर(dev->name, '%'))
		वापस "(unnamed net_device)";
	वापस dev->name;
पूर्ण

अटल अंतरभूत bool netdev_unरेजिस्टरing(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->reg_state == NETREG_UNREGISTERING;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *netdev_reg_state(स्थिर काष्ठा net_device *dev)
अणु
	चयन (dev->reg_state) अणु
	हाल NETREG_UNINITIALIZED: वापस " (uninitialized)";
	हाल NETREG_REGISTERED: वापस "";
	हाल NETREG_UNREGISTERING: वापस " (unregistering)";
	हाल NETREG_UNREGISTERED: वापस " (unregistered)";
	हाल NETREG_RELEASED: वापस " (released)";
	हाल NETREG_DUMMY: वापस " (dummy)";
	पूर्ण

	WARN_ONCE(1, "%s: unknown reg_state %d\n", dev->name, dev->reg_state);
	वापस " (unknown)";
पूर्ण

__म_लिखो(3, 4) __cold
व्योम netdev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा net_device *dev,
		   स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_emerg(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_alert(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_crit(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_err(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_warn(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_notice(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(2, 3) __cold
व्योम netdev_info(स्थिर काष्ठा net_device *dev, स्थिर अक्षर *क्रमmat, ...);

#घोषणा netdev_level_once(level, dev, fmt, ...)			\
करो अणु								\
	अटल bool __prपूर्णांक_once __पढ़ो_mostly;			\
								\
	अगर (!__prपूर्णांक_once) अणु					\
		__prपूर्णांक_once = true;				\
		netdev_prपूर्णांकk(level, dev, fmt, ##__VA_ARGS__);	\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा netdev_emerg_once(dev, fmt, ...) \
	netdev_level_once(KERN_EMERG, dev, fmt, ##__VA_ARGS__)
#घोषणा netdev_alert_once(dev, fmt, ...) \
	netdev_level_once(KERN_ALERT, dev, fmt, ##__VA_ARGS__)
#घोषणा netdev_crit_once(dev, fmt, ...) \
	netdev_level_once(KERN_CRIT, dev, fmt, ##__VA_ARGS__)
#घोषणा netdev_err_once(dev, fmt, ...) \
	netdev_level_once(KERN_ERR, dev, fmt, ##__VA_ARGS__)
#घोषणा netdev_warn_once(dev, fmt, ...) \
	netdev_level_once(KERN_WARNING, dev, fmt, ##__VA_ARGS__)
#घोषणा netdev_notice_once(dev, fmt, ...) \
	netdev_level_once(KERN_NOTICE, dev, fmt, ##__VA_ARGS__)
#घोषणा netdev_info_once(dev, fmt, ...) \
	netdev_level_once(KERN_INFO, dev, fmt, ##__VA_ARGS__)

#घोषणा MODULE_ALIAS_NETDEV(device) \
	MODULE_ALIAS("netdev-" device)

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#घोषणा netdev_dbg(__dev, क्रमmat, args...)			\
करो अणु								\
	dynamic_netdev_dbg(__dev, क्रमmat, ##args);		\
पूर्ण जबतक (0)
#या_अगर defined(DEBUG)
#घोषणा netdev_dbg(__dev, क्रमmat, args...)			\
	netdev_prपूर्णांकk(KERN_DEBUG, __dev, क्रमmat, ##args)
#अन्यथा
#घोषणा netdev_dbg(__dev, क्रमmat, args...)			\
(अणु								\
	अगर (0)							\
		netdev_prपूर्णांकk(KERN_DEBUG, __dev, क्रमmat, ##args); \
पूर्ण)
#पूर्ण_अगर

#अगर defined(VERBOSE_DEBUG)
#घोषणा netdev_vdbg	netdev_dbg
#अन्यथा

#घोषणा netdev_vdbg(dev, क्रमmat, args...)			\
(अणु								\
	अगर (0)							\
		netdev_prपूर्णांकk(KERN_DEBUG, dev, क्रमmat, ##args);	\
	0;							\
पूर्ण)
#पूर्ण_अगर

/*
 * netdev_WARN() acts like dev_prपूर्णांकk(), but with the key dअगरference
 * of using a WARN/WARN_ON to get the message out, including the
 * file/line inक्रमmation and a backtrace.
 */
#घोषणा netdev_WARN(dev, क्रमmat, args...)			\
	WARN(1, "netdevice: %s%s: " क्रमmat, netdev_name(dev),	\
	     netdev_reg_state(dev), ##args)

#घोषणा netdev_WARN_ONCE(dev, क्रमmat, args...)				\
	WARN_ONCE(1, "netdevice: %s%s: " क्रमmat, netdev_name(dev),	\
		  netdev_reg_state(dev), ##args)

/* netअगर prपूर्णांकk helpers, similar to netdev_prपूर्णांकk */

#घोषणा netअगर_prपूर्णांकk(priv, type, level, dev, fmt, args...)	\
करो अणु					  			\
	अगर (netअगर_msg_##type(priv))				\
		netdev_prपूर्णांकk(level, (dev), fmt, ##args);	\
पूर्ण जबतक (0)

#घोषणा netअगर_level(level, priv, type, dev, fmt, args...)	\
करो अणु								\
	अगर (netअगर_msg_##type(priv))				\
		netdev_##level(dev, fmt, ##args);		\
पूर्ण जबतक (0)

#घोषणा netअगर_emerg(priv, type, dev, fmt, args...)		\
	netअगर_level(emerg, priv, type, dev, fmt, ##args)
#घोषणा netअगर_alert(priv, type, dev, fmt, args...)		\
	netअगर_level(alert, priv, type, dev, fmt, ##args)
#घोषणा netअगर_crit(priv, type, dev, fmt, args...)		\
	netअगर_level(crit, priv, type, dev, fmt, ##args)
#घोषणा netअगर_err(priv, type, dev, fmt, args...)		\
	netअगर_level(err, priv, type, dev, fmt, ##args)
#घोषणा netअगर_warn(priv, type, dev, fmt, args...)		\
	netअगर_level(warn, priv, type, dev, fmt, ##args)
#घोषणा netअगर_notice(priv, type, dev, fmt, args...)		\
	netअगर_level(notice, priv, type, dev, fmt, ##args)
#घोषणा netअगर_info(priv, type, dev, fmt, args...)		\
	netअगर_level(info, priv, type, dev, fmt, ##args)

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#घोषणा netअगर_dbg(priv, type, netdev, क्रमmat, args...)		\
करो अणु								\
	अगर (netअगर_msg_##type(priv))				\
		dynamic_netdev_dbg(netdev, क्रमmat, ##args);	\
पूर्ण जबतक (0)
#या_अगर defined(DEBUG)
#घोषणा netअगर_dbg(priv, type, dev, क्रमmat, args...)		\
	netअगर_prपूर्णांकk(priv, type, KERN_DEBUG, dev, क्रमmat, ##args)
#अन्यथा
#घोषणा netअगर_dbg(priv, type, dev, क्रमmat, args...)			\
(अणु									\
	अगर (0)								\
		netअगर_prपूर्णांकk(priv, type, KERN_DEBUG, dev, क्रमmat, ##args); \
	0;								\
पूर्ण)
#पूर्ण_अगर

/* अगर @cond then करोwngrade to debug, अन्यथा prपूर्णांक at @level */
#घोषणा netअगर_cond_dbg(priv, type, netdev, cond, level, fmt, args...)     \
	करो अणु                                                              \
		अगर (cond)                                                 \
			netअगर_dbg(priv, type, netdev, fmt, ##args);       \
		अन्यथा                                                      \
			netअगर_ ## level(priv, type, netdev, fmt, ##args); \
	पूर्ण जबतक (0)

#अगर defined(VERBOSE_DEBUG)
#घोषणा netअगर_vdbg	netअगर_dbg
#अन्यथा
#घोषणा netअगर_vdbg(priv, type, dev, क्रमmat, args...)		\
(अणु								\
	अगर (0)							\
		netअगर_prपूर्णांकk(priv, type, KERN_DEBUG, dev, क्रमmat, ##args); \
	0;							\
पूर्ण)
#पूर्ण_अगर

/*
 *	The list of packet types we will receive (as opposed to discard)
 *	and the routines to invoke.
 *
 *	Why 16. Because with 16 the only overlap we get on a hash of the
 *	low nibble of the protocol value is RARP/SNAP/X.25.
 *
 *		0800	IP
 *		0001	802.3
 *		0002	AX.25
 *		0004	802.2
 *		8035	RARP
 *		0005	SNAP
 *		0805	X.25
 *		0806	ARP
 *		8137	IPX
 *		0009	Localtalk
 *		86DD	IPv6
 */
#घोषणा PTYPE_HASH_SIZE	(16)
#घोषणा PTYPE_HASH_MASK	(PTYPE_HASH_SIZE - 1)

बाह्य काष्ठा list_head ptype_all __पढ़ो_mostly;
बाह्य काष्ठा list_head ptype_base[PTYPE_HASH_SIZE] __पढ़ो_mostly;

बाह्य काष्ठा net_device *blackhole_netdev;

#पूर्ण_अगर	/* _LINUX_NETDEVICE_H */
