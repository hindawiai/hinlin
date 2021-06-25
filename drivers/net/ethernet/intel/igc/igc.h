<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_H_
#घोषणा _IGC_H_

#समावेश <linux/kobject.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/sctp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/net_tstamp.h>

#समावेश "igc_hw.h"

व्योम igc_ethtool_set_ops(काष्ठा net_device *);

/* Transmit and receive queues */
#घोषणा IGC_MAX_RX_QUEUES		4
#घोषणा IGC_MAX_TX_QUEUES		4

#घोषणा MAX_Q_VECTORS			8
#घोषणा MAX_STD_JUMBO_FRAME_SIZE	9216

#घोषणा MAX_ETYPE_FILTER		8
#घोषणा IGC_RETA_SIZE			128

/* SDP support */
#घोषणा IGC_N_EXTTS	2
#घोषणा IGC_N_PEROUT	2
#घोषणा IGC_N_SDP	4

क्रमागत igc_mac_filter_type अणु
	IGC_MAC_FILTER_TYPE_DST = 0,
	IGC_MAC_FILTER_TYPE_SRC
पूर्ण;

काष्ठा igc_tx_queue_stats अणु
	u64 packets;
	u64 bytes;
	u64 restart_queue;
	u64 restart_queue2;
पूर्ण;

काष्ठा igc_rx_queue_stats अणु
	u64 packets;
	u64 bytes;
	u64 drops;
	u64 csum_err;
	u64 alloc_failed;
पूर्ण;

काष्ठा igc_rx_packet_stats अणु
	u64 ipv4_packets;      /* IPv4 headers processed */
	u64 ipv4e_packets;     /* IPv4E headers with extensions processed */
	u64 ipv6_packets;      /* IPv6 headers processed */
	u64 ipv6e_packets;     /* IPv6E headers with extensions processed */
	u64 tcp_packets;       /* TCP headers processed */
	u64 udp_packets;       /* UDP headers processed */
	u64 sctp_packets;      /* SCTP headers processed */
	u64 nfs_packets;       /* NFS headers processe */
	u64 other_packets;
पूर्ण;

काष्ठा igc_ring_container अणु
	काष्ठा igc_ring *ring;          /* poपूर्णांकer to linked list of rings */
	अचिन्हित पूर्णांक total_bytes;       /* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;     /* total packets processed this पूर्णांक */
	u16 work_limit;                 /* total work allowed per पूर्णांकerrupt */
	u8 count;                       /* total number of rings in vector */
	u8 itr;                         /* current ITR setting क्रम ring */
पूर्ण;

काष्ठा igc_ring अणु
	काष्ठा igc_q_vector *q_vector;  /* backlink to q_vector */
	काष्ठा net_device *netdev;      /* back poपूर्णांकer to net_device */
	काष्ठा device *dev;             /* device क्रम dma mapping */
	जोड़ अणु                         /* array of buffer info काष्ठाs */
		काष्ठा igc_tx_buffer *tx_buffer_info;
		काष्ठा igc_rx_buffer *rx_buffer_info;
	पूर्ण;
	व्योम *desc;                     /* descriptor ring memory */
	अचिन्हित दीर्घ flags;            /* ring specअगरic flags */
	व्योम __iomem *tail;             /* poपूर्णांकer to ring tail रेजिस्टर */
	dma_addr_t dma;                 /* phys address of the ring */
	अचिन्हित पूर्णांक size;              /* length of desc. ring in bytes */

	u16 count;                      /* number of desc. in the ring */
	u8 queue_index;                 /* logical index of the ring*/
	u8 reg_idx;                     /* physical index of the ring */
	bool launchसमय_enable;         /* true अगर LaunchTime is enabled */

	u32 start_समय;
	u32 end_समय;

	/* everything past this poपूर्णांक are written often */
	u16 next_to_clean;
	u16 next_to_use;
	u16 next_to_alloc;

	जोड़ अणु
		/* TX */
		काष्ठा अणु
			काष्ठा igc_tx_queue_stats tx_stats;
			काष्ठा u64_stats_sync tx_syncp;
			काष्ठा u64_stats_sync tx_syncp2;
		पूर्ण;
		/* RX */
		काष्ठा अणु
			काष्ठा igc_rx_queue_stats rx_stats;
			काष्ठा igc_rx_packet_stats pkt_stats;
			काष्ठा u64_stats_sync rx_syncp;
			काष्ठा sk_buff *skb;
		पूर्ण;
	पूर्ण;

	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

/* Board specअगरic निजी data काष्ठाure */
काष्ठा igc_adapter अणु
	काष्ठा net_device *netdev;

	काष्ठा ethtool_eee eee;
	u16 eee_advert;

	अचिन्हित दीर्घ state;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक num_q_vectors;

	काष्ठा msix_entry *msix_entries;

	/* TX */
	u16 tx_work_limit;
	u32 tx_समयout_count;
	पूर्णांक num_tx_queues;
	काष्ठा igc_ring *tx_ring[IGC_MAX_TX_QUEUES];

	/* RX */
	पूर्णांक num_rx_queues;
	काष्ठा igc_ring *rx_ring[IGC_MAX_RX_QUEUES];

	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list dma_err_समयr;
	काष्ठा समयr_list phy_info_समयr;

	u32 wol;
	u32 en_mng_pt;
	u16 link_speed;
	u16 link_duplex;

	u8 port_num;

	u8 __iomem *io_addr;
	/* Interrupt Throttle Rate */
	u32 rx_itr_setting;
	u32 tx_itr_setting;

	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा watchकरोg_task;
	काष्ठा work_काष्ठा dma_err_task;
	bool fc_स्वतःneg;

	u8 tx_समयout_factor;

	पूर्णांक msg_enable;
	u32 max_frame_size;
	u32 min_frame_size;

	kसमय_प्रकार base_समय;
	kसमय_प्रकार cycle_समय;

	/* OS defined काष्ठाs */
	काष्ठा pci_dev *pdev;
	/* lock क्रम statistics */
	spinlock_t stats64_lock;
	काष्ठा rtnl_link_stats64 stats64;

	/* काष्ठाs defined in igc_hw.h */
	काष्ठा igc_hw hw;
	काष्ठा igc_hw_stats stats;

	काष्ठा igc_q_vector *q_vector[MAX_Q_VECTORS];
	u32 eims_enable_mask;
	u32 eims_other;

	u16 tx_ring_count;
	u16 rx_ring_count;

	u32 tx_hwtstamp_समयouts;
	u32 tx_hwtstamp_skipped;
	u32 rx_hwtstamp_cleared;

	u32 rss_queues;
	u32 rss_indir_tbl_init;

	/* Any access to elements in nfc_rule_list is रक्षित by the
	 * nfc_rule_lock.
	 */
	काष्ठा mutex nfc_rule_lock;
	काष्ठा list_head nfc_rule_list;
	अचिन्हित पूर्णांक nfc_rule_count;

	u8 rss_indir_tbl[IGC_RETA_SIZE];

	अचिन्हित दीर्घ link_check_समयout;
	काष्ठा igc_info ei;

	u32 test_icr;

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_caps;
	काष्ठा work_काष्ठा ptp_tx_work;
	काष्ठा sk_buff *ptp_tx_skb;
	काष्ठा hwtstamp_config tstamp_config;
	अचिन्हित दीर्घ ptp_tx_start;
	अचिन्हित पूर्णांक ptp_flags;
	/* System समय value lock */
	spinlock_t पंचांगreg_lock;
	काष्ठा cyclecounter cc;
	काष्ठा समयcounter tc;
	काष्ठा बारpec64 prev_ptp_समय; /* Pre-reset PTP घड़ी */
	kसमय_प्रकार ptp_reset_start; /* Reset समय in घड़ी mono */

	अक्षर fw_version[32];

	काष्ठा bpf_prog *xdp_prog;

	bool pps_sys_wrap_on;

	काष्ठा ptp_pin_desc sdp_config[IGC_N_SDP];
	काष्ठा अणु
		काष्ठा बारpec64 start;
		काष्ठा बारpec64 period;
	पूर्ण perout[IGC_N_PEROUT];
पूर्ण;

व्योम igc_up(काष्ठा igc_adapter *adapter);
व्योम igc_करोwn(काष्ठा igc_adapter *adapter);
पूर्णांक igc_खोलो(काष्ठा net_device *netdev);
पूर्णांक igc_बंद(काष्ठा net_device *netdev);
पूर्णांक igc_setup_tx_resources(काष्ठा igc_ring *ring);
पूर्णांक igc_setup_rx_resources(काष्ठा igc_ring *ring);
व्योम igc_मुक्त_tx_resources(काष्ठा igc_ring *ring);
व्योम igc_मुक्त_rx_resources(काष्ठा igc_ring *ring);
अचिन्हित पूर्णांक igc_get_max_rss_queues(काष्ठा igc_adapter *adapter);
व्योम igc_set_flag_queue_pairs(काष्ठा igc_adapter *adapter,
			      स्थिर u32 max_rss_queues);
पूर्णांक igc_reinit_queues(काष्ठा igc_adapter *adapter);
व्योम igc_ग_लिखो_rss_indir_tbl(काष्ठा igc_adapter *adapter);
bool igc_has_link(काष्ठा igc_adapter *adapter);
व्योम igc_reset(काष्ठा igc_adapter *adapter);
पूर्णांक igc_set_spd_dplx(काष्ठा igc_adapter *adapter, u32 spd, u8 dplx);
व्योम igc_update_stats(काष्ठा igc_adapter *adapter);

/* igc_dump declarations */
व्योम igc_rings_dump(काष्ठा igc_adapter *adapter);
व्योम igc_regs_dump(काष्ठा igc_adapter *adapter);

बाह्य अक्षर igc_driver_name[];

#घोषणा IGC_REGS_LEN			740

/* flags controlling PTP/1588 function */
#घोषणा IGC_PTP_ENABLED		BIT(0)

/* Flags definitions */
#घोषणा IGC_FLAG_HAS_MSI		BIT(0)
#घोषणा IGC_FLAG_QUEUE_PAIRS		BIT(3)
#घोषणा IGC_FLAG_DMAC			BIT(4)
#घोषणा IGC_FLAG_PTP			BIT(8)
#घोषणा IGC_FLAG_WOL_SUPPORTED		BIT(8)
#घोषणा IGC_FLAG_NEED_LINK_UPDATE	BIT(9)
#घोषणा IGC_FLAG_MEDIA_RESET		BIT(10)
#घोषणा IGC_FLAG_MAS_ENABLE		BIT(12)
#घोषणा IGC_FLAG_HAS_MSIX		BIT(13)
#घोषणा IGC_FLAG_EEE			BIT(14)
#घोषणा IGC_FLAG_VLAN_PROMISC		BIT(15)
#घोषणा IGC_FLAG_RX_LEGACY		BIT(16)
#घोषणा IGC_FLAG_TSN_QBV_ENABLED	BIT(17)

#घोषणा IGC_FLAG_RSS_FIELD_IPV4_UDP	BIT(6)
#घोषणा IGC_FLAG_RSS_FIELD_IPV6_UDP	BIT(7)

#घोषणा IGC_MRQC_ENABLE_RSS_MQ		0x00000002
#घोषणा IGC_MRQC_RSS_FIELD_IPV4_UDP	0x00400000
#घोषणा IGC_MRQC_RSS_FIELD_IPV6_UDP	0x00800000

/* Interrupt defines */
#घोषणा IGC_START_ITR			648 /* ~6000 पूर्णांकs/sec */
#घोषणा IGC_4K_ITR			980
#घोषणा IGC_20K_ITR			196
#घोषणा IGC_70K_ITR			56

#घोषणा IGC_DEFAULT_ITR		3 /* dynamic */
#घोषणा IGC_MAX_ITR_USECS	10000
#घोषणा IGC_MIN_ITR_USECS	10
#घोषणा NON_Q_VECTORS		1
#घोषणा MAX_MSIX_ENTRIES	10

/* TX/RX descriptor defines */
#घोषणा IGC_DEFAULT_TXD		256
#घोषणा IGC_DEFAULT_TX_WORK	128
#घोषणा IGC_MIN_TXD		80
#घोषणा IGC_MAX_TXD		4096

#घोषणा IGC_DEFAULT_RXD		256
#घोषणा IGC_MIN_RXD		80
#घोषणा IGC_MAX_RXD		4096

/* Supported Rx Buffer Sizes */
#घोषणा IGC_RXBUFFER_256		256
#घोषणा IGC_RXBUFFER_2048		2048
#घोषणा IGC_RXBUFFER_3072		3072

#घोषणा AUTO_ALL_MODES		0
#घोषणा IGC_RX_HDR_LEN			IGC_RXBUFFER_256

/* Transmit and receive latency (क्रम PTP बारtamps) */
#घोषणा IGC_I225_TX_LATENCY_10		240
#घोषणा IGC_I225_TX_LATENCY_100		58
#घोषणा IGC_I225_TX_LATENCY_1000	80
#घोषणा IGC_I225_TX_LATENCY_2500	1325
#घोषणा IGC_I225_RX_LATENCY_10		6450
#घोषणा IGC_I225_RX_LATENCY_100		185
#घोषणा IGC_I225_RX_LATENCY_1000	300
#घोषणा IGC_I225_RX_LATENCY_2500	1485

/* RX and TX descriptor control thresholds.
 * PTHRESH - MAC will consider prefetch अगर it has fewer than this number of
 *           descriptors available in its onboard memory.
 *           Setting this to 0 disables RX descriptor prefetch.
 * HTHRESH - MAC will only prefetch अगर there are at least this many descriptors
 *           available in host memory.
 *           If PTHRESH is 0, this should also be 0.
 * WTHRESH - RX descriptor ग_लिखोback threshold - MAC will delay writing back
 *           descriptors until either it has this many to ग_लिखो back, or the
 *           ITR समयr expires.
 */
#घोषणा IGC_RX_PTHRESH			8
#घोषणा IGC_RX_HTHRESH			8
#घोषणा IGC_TX_PTHRESH			8
#घोषणा IGC_TX_HTHRESH			1
#घोषणा IGC_RX_WTHRESH			4
#घोषणा IGC_TX_WTHRESH			16

#घोषणा IGC_RX_DMA_ATTR \
	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

#घोषणा IGC_TS_HDR_LEN			16

#घोषणा IGC_SKB_PAD			(NET_SKB_PAD + NET_IP_ALIGN)

#अगर (PAGE_SIZE < 8192)
#घोषणा IGC_MAX_FRAME_BUILD_SKB \
	(SKB_WITH_OVERHEAD(IGC_RXBUFFER_2048) - IGC_SKB_PAD - IGC_TS_HDR_LEN)
#अन्यथा
#घोषणा IGC_MAX_FRAME_BUILD_SKB (IGC_RXBUFFER_2048 - IGC_TS_HDR_LEN)
#पूर्ण_अगर

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IGC_RX_BUFFER_WRITE	16 /* Must be घातer of 2 */

/* VLAN info */
#घोषणा IGC_TX_FLAGS_VLAN_MASK	0xffff0000

/* igc_test_staterr - tests bits within Rx descriptor status and error fields */
अटल अंतरभूत __le32 igc_test_staterr(जोड़ igc_adv_rx_desc *rx_desc,
				      स्थिर u32 stat_err_bits)
अणु
	वापस rx_desc->wb.upper.status_error & cpu_to_le32(stat_err_bits);
पूर्ण

क्रमागत igc_state_t अणु
	__IGC_TESTING,
	__IGC_RESETTING,
	__IGC_DOWN,
	__IGC_PTP_TX_IN_PROGRESS,
पूर्ण;

क्रमागत igc_tx_flags अणु
	/* cmd_type flags */
	IGC_TX_FLAGS_VLAN	= 0x01,
	IGC_TX_FLAGS_TSO	= 0x02,
	IGC_TX_FLAGS_TSTAMP	= 0x04,

	/* olinfo flags */
	IGC_TX_FLAGS_IPV4	= 0x10,
	IGC_TX_FLAGS_CSUM	= 0x20,

	IGC_TX_FLAGS_XDP	= 0x100,
पूर्ण;

क्रमागत igc_boards अणु
	board_base,
पूर्ण;

/* The largest size we can ग_लिखो to the descriptor is 65535.  In order to
 * मुख्यtain a घातer of two alignment we have to limit ourselves to 32K.
 */
#घोषणा IGC_MAX_TXD_PWR		15
#घोषणा IGC_MAX_DATA_PER_TXD	BIT(IGC_MAX_TXD_PWR)

/* Tx Descriptors needed, worst हाल */
#घोषणा TXD_USE_COUNT(S)	DIV_ROUND_UP((S), IGC_MAX_DATA_PER_TXD)
#घोषणा DESC_NEEDED	(MAX_SKB_FRAGS + 4)

/* wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा igc_tx_buffer अणु
	जोड़ igc_adv_tx_desc *next_to_watch;
	अचिन्हित दीर्घ समय_stamp;
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा xdp_frame *xdpf;
	पूर्ण;
	अचिन्हित पूर्णांक bytecount;
	u16 gso_segs;
	__be16 protocol;

	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
	u32 tx_flags;
पूर्ण;

काष्ठा igc_rx_buffer अणु
	dma_addr_t dma;
	काष्ठा page *page;
#अगर (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
#अन्यथा
	__u16 page_offset;
#पूर्ण_अगर
	__u16 pagecnt_bias;
पूर्ण;

काष्ठा igc_q_vector अणु
	काष्ठा igc_adapter *adapter;    /* backlink */
	व्योम __iomem *itr_रेजिस्टर;
	u32 eims_value;                 /* EIMS mask value */

	u16 itr_val;
	u8 set_itr;

	काष्ठा igc_ring_container rx, tx;

	काष्ठा napi_काष्ठा napi;

	काष्ठा rcu_head rcu;    /* to aव्योम race with update stats on मुक्त */
	अक्षर name[IFNAMSIZ + 9];
	काष्ठा net_device poll_dev;

	/* क्रम dynamic allocation of rings associated with this q_vector */
	काष्ठा igc_ring ring[] ____cacheline_पूर्णांकernodealigned_in_smp;
पूर्ण;

क्रमागत igc_filter_match_flags अणु
	IGC_FILTER_FLAG_ETHER_TYPE =	0x1,
	IGC_FILTER_FLAG_VLAN_TCI   =	0x2,
	IGC_FILTER_FLAG_SRC_MAC_ADDR =	0x4,
	IGC_FILTER_FLAG_DST_MAC_ADDR =	0x8,
पूर्ण;

काष्ठा igc_nfc_filter अणु
	u8 match_flags;
	u16 etype;
	u16 vlan_tci;
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
पूर्ण;

काष्ठा igc_nfc_rule अणु
	काष्ठा list_head list;
	काष्ठा igc_nfc_filter filter;
	u32 location;
	u16 action;
पूर्ण;

/* IGC supports a total of 32 NFC rules: 16 MAC address based,, 8 VLAN priority
 * based, and 8 ethertype based.
 */
#घोषणा IGC_MAX_RXNFC_RULES		32

/* igc_desc_unused - calculate अगर we have unused descriptors */
अटल अंतरभूत u16 igc_desc_unused(स्थिर काष्ठा igc_ring *ring)
अणु
	u16 ntc = ring->next_to_clean;
	u16 ntu = ring->next_to_use;

	वापस ((ntc > ntu) ? 0 : ring->count) + ntc - ntu - 1;
पूर्ण

अटल अंतरभूत s32 igc_get_phy_info(काष्ठा igc_hw *hw)
अणु
	अगर (hw->phy.ops.get_phy_info)
		वापस hw->phy.ops.get_phy_info(hw);

	वापस 0;
पूर्ण

अटल अंतरभूत s32 igc_reset_phy(काष्ठा igc_hw *hw)
अणु
	अगर (hw->phy.ops.reset)
		वापस hw->phy.ops.reset(hw);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा igc_ring *tx_ring)
अणु
	वापस netdev_get_tx_queue(tx_ring->netdev, tx_ring->queue_index);
पूर्ण

क्रमागत igc_ring_flags_t अणु
	IGC_RING_FLAG_RX_3K_BUFFER,
	IGC_RING_FLAG_RX_BUILD_SKB_ENABLED,
	IGC_RING_FLAG_RX_SCTP_CSUM,
	IGC_RING_FLAG_RX_LB_VLAN_BSWAP,
	IGC_RING_FLAG_TX_CTX_IDX,
	IGC_RING_FLAG_TX_DETECT_HANG
पूर्ण;

#घोषणा ring_uses_large_buffer(ring) \
	test_bit(IGC_RING_FLAG_RX_3K_BUFFER, &(ring)->flags)
#घोषणा set_ring_uses_large_buffer(ring) \
	set_bit(IGC_RING_FLAG_RX_3K_BUFFER, &(ring)->flags)
#घोषणा clear_ring_uses_large_buffer(ring) \
	clear_bit(IGC_RING_FLAG_RX_3K_BUFFER, &(ring)->flags)

#घोषणा ring_uses_build_skb(ring) \
	test_bit(IGC_RING_FLAG_RX_BUILD_SKB_ENABLED, &(ring)->flags)

अटल अंतरभूत अचिन्हित पूर्णांक igc_rx_bufsz(काष्ठा igc_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_large_buffer(ring))
		वापस IGC_RXBUFFER_3072;

	अगर (ring_uses_build_skb(ring))
		वापस IGC_MAX_FRAME_BUILD_SKB + IGC_TS_HDR_LEN;
#पूर्ण_अगर
	वापस IGC_RXBUFFER_2048;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक igc_rx_pg_order(काष्ठा igc_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_large_buffer(ring))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत s32 igc_पढ़ो_phy_reg(काष्ठा igc_hw *hw, u32 offset, u16 *data)
अणु
	अगर (hw->phy.ops.पढ़ो_reg)
		वापस hw->phy.ops.पढ़ो_reg(hw, offset, data);

	वापस 0;
पूर्ण

व्योम igc_reinit_locked(काष्ठा igc_adapter *);
काष्ठा igc_nfc_rule *igc_get_nfc_rule(काष्ठा igc_adapter *adapter,
				      u32 location);
पूर्णांक igc_add_nfc_rule(काष्ठा igc_adapter *adapter, काष्ठा igc_nfc_rule *rule);
व्योम igc_del_nfc_rule(काष्ठा igc_adapter *adapter, काष्ठा igc_nfc_rule *rule);

व्योम igc_ptp_init(काष्ठा igc_adapter *adapter);
व्योम igc_ptp_reset(काष्ठा igc_adapter *adapter);
व्योम igc_ptp_suspend(काष्ठा igc_adapter *adapter);
व्योम igc_ptp_stop(काष्ठा igc_adapter *adapter);
kसमय_प्रकार igc_ptp_rx_pktstamp(काष्ठा igc_adapter *adapter, __le32 *buf);
पूर्णांक igc_ptp_set_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr);
पूर्णांक igc_ptp_get_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr);
व्योम igc_ptp_tx_hang(काष्ठा igc_adapter *adapter);
व्योम igc_ptp_पढ़ो(काष्ठा igc_adapter *adapter, काष्ठा बारpec64 *ts);

#घोषणा igc_rx_pg_size(_ring) (PAGE_SIZE << igc_rx_pg_order(_ring))

#घोषणा IGC_TXD_DCMD	(IGC_ADVTXD_DCMD_EOP | IGC_ADVTXD_DCMD_RS)

#घोषणा IGC_RX_DESC(R, i)       \
	(&(((जोड़ igc_adv_rx_desc *)((R)->desc))[i]))
#घोषणा IGC_TX_DESC(R, i)       \
	(&(((जोड़ igc_adv_tx_desc *)((R)->desc))[i]))
#घोषणा IGC_TX_CTXTDESC(R, i)   \
	(&(((काष्ठा igc_adv_tx_context_desc *)((R)->desc))[i]))

#पूर्ण_अगर /* _IGC_H_ */
