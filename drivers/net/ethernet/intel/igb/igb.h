<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2007 - 2018 Intel Corporation. */

/* Linux PRO/1000 Ethernet Driver मुख्य header file */

#अगर_अघोषित _IGB_H_
#घोषणा _IGB_H_

#समावेश "e1000_mac.h"
#समावेश "e1000_82575.h"

#समावेश <linux/समयcounter.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/pci.h>
#समावेश <linux/mdपन.स>

#समावेश <net/xdp.h>

काष्ठा igb_adapter;

#घोषणा E1000_PCS_CFG_IGN_SD	1

/* Interrupt defines */
#घोषणा IGB_START_ITR		648 /* ~6000 पूर्णांकs/sec */
#घोषणा IGB_4K_ITR		980
#घोषणा IGB_20K_ITR		196
#घोषणा IGB_70K_ITR		56

/* TX/RX descriptor defines */
#घोषणा IGB_DEFAULT_TXD		256
#घोषणा IGB_DEFAULT_TX_WORK	128
#घोषणा IGB_MIN_TXD		80
#घोषणा IGB_MAX_TXD		4096

#घोषणा IGB_DEFAULT_RXD		256
#घोषणा IGB_MIN_RXD		80
#घोषणा IGB_MAX_RXD		4096

#घोषणा IGB_DEFAULT_ITR		3 /* dynamic */
#घोषणा IGB_MAX_ITR_USECS	10000
#घोषणा IGB_MIN_ITR_USECS	10
#घोषणा NON_Q_VECTORS		1
#घोषणा MAX_Q_VECTORS		8
#घोषणा MAX_MSIX_ENTRIES	10

/* Transmit and receive queues */
#घोषणा IGB_MAX_RX_QUEUES	8
#घोषणा IGB_MAX_RX_QUEUES_82575	4
#घोषणा IGB_MAX_RX_QUEUES_I211	2
#घोषणा IGB_MAX_TX_QUEUES	8
#घोषणा IGB_MAX_VF_MC_ENTRIES	30
#घोषणा IGB_MAX_VF_FUNCTIONS	8
#घोषणा IGB_MAX_VFTA_ENTRIES	128
#घोषणा IGB_82576_VF_DEV_ID	0x10CA
#घोषणा IGB_I350_VF_DEV_ID	0x1520

/* NVM version defines */
#घोषणा IGB_MAJOR_MASK		0xF000
#घोषणा IGB_MINOR_MASK		0x0FF0
#घोषणा IGB_BUILD_MASK		0x000F
#घोषणा IGB_COMB_VER_MASK	0x00FF
#घोषणा IGB_MAJOR_SHIFT		12
#घोषणा IGB_MINOR_SHIFT		4
#घोषणा IGB_COMB_VER_SHFT	8
#घोषणा IGB_NVM_VER_INVALID	0xFFFF
#घोषणा IGB_ETRACK_SHIFT	16
#घोषणा NVM_ETRACK_WORD		0x0042
#घोषणा NVM_COMB_VER_OFF	0x0083
#घोषणा NVM_COMB_VER_PTR	0x003d

/* Transmit and receive latency (क्रम PTP बारtamps) */
#घोषणा IGB_I210_TX_LATENCY_10		9542
#घोषणा IGB_I210_TX_LATENCY_100		1024
#घोषणा IGB_I210_TX_LATENCY_1000	178
#घोषणा IGB_I210_RX_LATENCY_10		20662
#घोषणा IGB_I210_RX_LATENCY_100		2213
#घोषणा IGB_I210_RX_LATENCY_1000	448

/* XDP */
#घोषणा IGB_XDP_PASS		0
#घोषणा IGB_XDP_CONSUMED	BIT(0)
#घोषणा IGB_XDP_TX		BIT(1)
#घोषणा IGB_XDP_REसूची		BIT(2)

काष्ठा vf_data_storage अणु
	अचिन्हित अक्षर vf_mac_addresses[ETH_ALEN];
	u16 vf_mc_hashes[IGB_MAX_VF_MC_ENTRIES];
	u16 num_vf_mc_hashes;
	u32 flags;
	अचिन्हित दीर्घ last_nack;
	u16 pf_vlan; /* When set, guest VLAN config not allowed. */
	u16 pf_qos;
	u16 tx_rate;
	bool spoofchk_enabled;
	bool trusted;
पूर्ण;

/* Number of unicast MAC filters reserved क्रम the PF in the RAR रेजिस्टरs */
#घोषणा IGB_PF_MAC_FILTERS_RESERVED	3

काष्ठा vf_mac_filter अणु
	काष्ठा list_head l;
	पूर्णांक vf;
	bool मुक्त;
	u8 vf_mac[ETH_ALEN];
पूर्ण;

#घोषणा IGB_VF_FLAG_CTS            0x00000001 /* VF is clear to send data */
#घोषणा IGB_VF_FLAG_UNI_PROMISC    0x00000002 /* VF has unicast promisc */
#घोषणा IGB_VF_FLAG_MULTI_PROMISC  0x00000004 /* VF has multicast promisc */
#घोषणा IGB_VF_FLAG_PF_SET_MAC     0x00000008 /* PF has set MAC address */

/* RX descriptor control thresholds.
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
#घोषणा IGB_RX_PTHRESH	((hw->mac.type == e1000_i354) ? 12 : 8)
#घोषणा IGB_RX_HTHRESH	8
#घोषणा IGB_TX_PTHRESH	((hw->mac.type == e1000_i354) ? 20 : 8)
#घोषणा IGB_TX_HTHRESH	1
#घोषणा IGB_RX_WTHRESH	((hw->mac.type == e1000_82576 && \
			  (adapter->flags & IGB_FLAG_HAS_MSIX)) ? 1 : 4)
#घोषणा IGB_TX_WTHRESH	((hw->mac.type == e1000_82576 && \
			  (adapter->flags & IGB_FLAG_HAS_MSIX)) ? 1 : 16)

/* this is the size past which hardware will drop packets when setting LPE=0 */
#घोषणा MAXIMUM_ETHERNET_VLAN_SIZE 1522

#घोषणा IGB_ETH_PKT_HDR_PAD	(ETH_HLEN + ETH_FCS_LEN + (VLAN_HLEN * 2))

/* Supported Rx Buffer Sizes */
#घोषणा IGB_RXBUFFER_256	256
#घोषणा IGB_RXBUFFER_1536	1536
#घोषणा IGB_RXBUFFER_2048	2048
#घोषणा IGB_RXBUFFER_3072	3072
#घोषणा IGB_RX_HDR_LEN		IGB_RXBUFFER_256
#घोषणा IGB_TS_HDR_LEN		16

/* Attempt to maximize the headroom available क्रम incoming frames.  We
 * use a 2K buffer क्रम receives and need 1536/1534 to store the data क्रम
 * the frame.  This leaves us with 512 bytes of room.  From that we need
 * to deduct the space needed क्रम the shared info and the padding needed
 * to IP align the frame.
 *
 * Note: For cache line sizes 256 or larger this value is going to end
 *	 up negative.  In these हालs we should fall back to the 3K
 *	 buffers.
 */
#अगर (PAGE_SIZE < 8192)
#घोषणा IGB_MAX_FRAME_BUILD_SKB (IGB_RXBUFFER_1536 - NET_IP_ALIGN)
#घोषणा IGB_2K_TOO_SMALL_WITH_PADDING \
((NET_SKB_PAD + IGB_TS_HDR_LEN + IGB_RXBUFFER_1536) > SKB_WITH_OVERHEAD(IGB_RXBUFFER_2048))

अटल अंतरभूत पूर्णांक igb_compute_pad(पूर्णांक rx_buf_len)
अणु
	पूर्णांक page_size, pad_size;

	page_size = ALIGN(rx_buf_len, PAGE_SIZE / 2);
	pad_size = SKB_WITH_OVERHEAD(page_size) - rx_buf_len;

	वापस pad_size;
पूर्ण

अटल अंतरभूत पूर्णांक igb_skb_pad(व्योम)
अणु
	पूर्णांक rx_buf_len;

	/* If a 2K buffer cannot handle a standard Ethernet frame then
	 * optimize padding क्रम a 3K buffer instead of a 1.5K buffer.
	 *
	 * For a 3K buffer we need to add enough padding to allow क्रम
	 * tailroom due to NET_IP_ALIGN possibly shअगरting us out of
	 * cache-line alignment.
	 */
	अगर (IGB_2K_TOO_SMALL_WITH_PADDING)
		rx_buf_len = IGB_RXBUFFER_3072 + SKB_DATA_ALIGN(NET_IP_ALIGN);
	अन्यथा
		rx_buf_len = IGB_RXBUFFER_1536;

	/* अगर needed make room क्रम NET_IP_ALIGN */
	rx_buf_len -= NET_IP_ALIGN;

	वापस igb_compute_pad(rx_buf_len);
पूर्ण

#घोषणा IGB_SKB_PAD	igb_skb_pad()
#अन्यथा
#घोषणा IGB_SKB_PAD	(NET_SKB_PAD + NET_IP_ALIGN)
#पूर्ण_अगर

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IGB_RX_BUFFER_WRITE	16 /* Must be घातer of 2 */

#घोषणा IGB_RX_DMA_ATTR \
	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

#घोषणा AUTO_ALL_MODES		0
#घोषणा IGB_EEPROM_APME		0x0400

#अगर_अघोषित IGB_MASTER_SLAVE
/* Switch to override PHY master/slave setting */
#घोषणा IGB_MASTER_SLAVE	e1000_ms_hw_शेष
#पूर्ण_अगर

#घोषणा IGB_MNG_VLAN_NONE	-1

क्रमागत igb_tx_flags अणु
	/* cmd_type flags */
	IGB_TX_FLAGS_VLAN	= 0x01,
	IGB_TX_FLAGS_TSO	= 0x02,
	IGB_TX_FLAGS_TSTAMP	= 0x04,

	/* olinfo flags */
	IGB_TX_FLAGS_IPV4	= 0x10,
	IGB_TX_FLAGS_CSUM	= 0x20,
पूर्ण;

/* VLAN info */
#घोषणा IGB_TX_FLAGS_VLAN_MASK	0xffff0000
#घोषणा IGB_TX_FLAGS_VLAN_SHIFT	16

/* The largest size we can ग_लिखो to the descriptor is 65535.  In order to
 * मुख्यtain a घातer of two alignment we have to limit ourselves to 32K.
 */
#घोषणा IGB_MAX_TXD_PWR	15
#घोषणा IGB_MAX_DATA_PER_TXD	(1u << IGB_MAX_TXD_PWR)

/* Tx Descriptors needed, worst हाल */
#घोषणा TXD_USE_COUNT(S) DIV_ROUND_UP((S), IGB_MAX_DATA_PER_TXD)
#घोषणा DESC_NEEDED (MAX_SKB_FRAGS + 4)

/* EEPROM byte offsets */
#घोषणा IGB_SFF_8472_SWAP		0x5C
#घोषणा IGB_SFF_8472_COMP		0x5E

/* Biपंचांगasks */
#घोषणा IGB_SFF_ADDRESSING_MODE		0x4
#घोषणा IGB_SFF_8472_UNSUP		0x00

/* TX resources are shared between XDP and netstack
 * and we need to tag the buffer type to distinguish them
 */
क्रमागत igb_tx_buf_type अणु
	IGB_TYPE_SKB = 0,
	IGB_TYPE_XDP,
पूर्ण;

/* wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा igb_tx_buffer अणु
	जोड़ e1000_adv_tx_desc *next_to_watch;
	अचिन्हित दीर्घ समय_stamp;
	क्रमागत igb_tx_buf_type type;
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

काष्ठा igb_rx_buffer अणु
	dma_addr_t dma;
	काष्ठा page *page;
#अगर (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
#अन्यथा
	__u16 page_offset;
#पूर्ण_अगर
	__u16 pagecnt_bias;
पूर्ण;

काष्ठा igb_tx_queue_stats अणु
	u64 packets;
	u64 bytes;
	u64 restart_queue;
	u64 restart_queue2;
पूर्ण;

काष्ठा igb_rx_queue_stats अणु
	u64 packets;
	u64 bytes;
	u64 drops;
	u64 csum_err;
	u64 alloc_failed;
पूर्ण;

काष्ठा igb_ring_container अणु
	काष्ठा igb_ring *ring;		/* poपूर्णांकer to linked list of rings */
	अचिन्हित पूर्णांक total_bytes;	/* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;	/* total packets processed this पूर्णांक */
	u16 work_limit;			/* total work allowed per पूर्णांकerrupt */
	u8 count;			/* total number of rings in vector */
	u8 itr;				/* current ITR setting क्रम ring */
पूर्ण;

काष्ठा igb_ring अणु
	काष्ठा igb_q_vector *q_vector;	/* backlink to q_vector */
	काष्ठा net_device *netdev;	/* back poपूर्णांकer to net_device */
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा device *dev;		/* device poपूर्णांकer क्रम dma mapping */
	जोड़ अणु				/* array of buffer info काष्ठाs */
		काष्ठा igb_tx_buffer *tx_buffer_info;
		काष्ठा igb_rx_buffer *rx_buffer_info;
	पूर्ण;
	व्योम *desc;			/* descriptor ring memory */
	अचिन्हित दीर्घ flags;		/* ring specअगरic flags */
	व्योम __iomem *tail;		/* poपूर्णांकer to ring tail रेजिस्टर */
	dma_addr_t dma;			/* phys address of the ring */
	अचिन्हित पूर्णांक  size;		/* length of desc. ring in bytes */

	u16 count;			/* number of desc. in the ring */
	u8 queue_index;			/* logical index of the ring*/
	u8 reg_idx;			/* physical index of the ring */
	bool launchसमय_enable;		/* true अगर LaunchTime is enabled */
	bool cbs_enable;		/* indicates अगर CBS is enabled */
	s32 idleslope;			/* idleSlope in kbps */
	s32 sendslope;			/* sendSlope in kbps */
	s32 hicredit;			/* hiCredit in bytes */
	s32 locredit;			/* loCredit in bytes */

	/* everything past this poपूर्णांक are written often */
	u16 next_to_clean;
	u16 next_to_use;
	u16 next_to_alloc;

	जोड़ अणु
		/* TX */
		काष्ठा अणु
			काष्ठा igb_tx_queue_stats tx_stats;
			काष्ठा u64_stats_sync tx_syncp;
			काष्ठा u64_stats_sync tx_syncp2;
		पूर्ण;
		/* RX */
		काष्ठा अणु
			काष्ठा sk_buff *skb;
			काष्ठा igb_rx_queue_stats rx_stats;
			काष्ठा u64_stats_sync rx_syncp;
		पूर्ण;
	पूर्ण;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

काष्ठा igb_q_vector अणु
	काष्ठा igb_adapter *adapter;	/* backlink */
	पूर्णांक cpu;			/* CPU क्रम DCA */
	u32 eims_value;			/* EIMS mask value */

	u16 itr_val;
	u8 set_itr;
	व्योम __iomem *itr_रेजिस्टर;

	काष्ठा igb_ring_container rx, tx;

	काष्ठा napi_काष्ठा napi;
	काष्ठा rcu_head rcu;	/* to aव्योम race with update stats on मुक्त */
	अक्षर name[IFNAMSIZ + 9];

	/* क्रम dynamic allocation of rings associated with this q_vector */
	काष्ठा igb_ring ring[] ____cacheline_पूर्णांकernodealigned_in_smp;
पूर्ण;

क्रमागत e1000_ring_flags_t अणु
	IGB_RING_FLAG_RX_3K_BUFFER,
	IGB_RING_FLAG_RX_BUILD_SKB_ENABLED,
	IGB_RING_FLAG_RX_SCTP_CSUM,
	IGB_RING_FLAG_RX_LB_VLAN_BSWAP,
	IGB_RING_FLAG_TX_CTX_IDX,
	IGB_RING_FLAG_TX_DETECT_HANG
पूर्ण;

#घोषणा ring_uses_large_buffer(ring) \
	test_bit(IGB_RING_FLAG_RX_3K_BUFFER, &(ring)->flags)
#घोषणा set_ring_uses_large_buffer(ring) \
	set_bit(IGB_RING_FLAG_RX_3K_BUFFER, &(ring)->flags)
#घोषणा clear_ring_uses_large_buffer(ring) \
	clear_bit(IGB_RING_FLAG_RX_3K_BUFFER, &(ring)->flags)

#घोषणा ring_uses_build_skb(ring) \
	test_bit(IGB_RING_FLAG_RX_BUILD_SKB_ENABLED, &(ring)->flags)
#घोषणा set_ring_build_skb_enabled(ring) \
	set_bit(IGB_RING_FLAG_RX_BUILD_SKB_ENABLED, &(ring)->flags)
#घोषणा clear_ring_build_skb_enabled(ring) \
	clear_bit(IGB_RING_FLAG_RX_BUILD_SKB_ENABLED, &(ring)->flags)

अटल अंतरभूत अचिन्हित पूर्णांक igb_rx_bufsz(काष्ठा igb_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_large_buffer(ring))
		वापस IGB_RXBUFFER_3072;

	अगर (ring_uses_build_skb(ring))
		वापस IGB_MAX_FRAME_BUILD_SKB;
#पूर्ण_अगर
	वापस IGB_RXBUFFER_2048;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक igb_rx_pg_order(काष्ठा igb_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_large_buffer(ring))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा igb_rx_pg_size(_ring) (PAGE_SIZE << igb_rx_pg_order(_ring))

#घोषणा IGB_TXD_DCMD (E1000_ADVTXD_DCMD_EOP | E1000_ADVTXD_DCMD_RS)

#घोषणा IGB_RX_DESC(R, i)	\
	(&(((जोड़ e1000_adv_rx_desc *)((R)->desc))[i]))
#घोषणा IGB_TX_DESC(R, i)	\
	(&(((जोड़ e1000_adv_tx_desc *)((R)->desc))[i]))
#घोषणा IGB_TX_CTXTDESC(R, i)	\
	(&(((काष्ठा e1000_adv_tx_context_desc *)((R)->desc))[i]))

/* igb_test_staterr - tests bits within Rx descriptor status and error fields */
अटल अंतरभूत __le32 igb_test_staterr(जोड़ e1000_adv_rx_desc *rx_desc,
				      स्थिर u32 stat_err_bits)
अणु
	वापस rx_desc->wb.upper.status_error & cpu_to_le32(stat_err_bits);
पूर्ण

/* igb_desc_unused - calculate अगर we have unused descriptors */
अटल अंतरभूत पूर्णांक igb_desc_unused(काष्ठा igb_ring *ring)
अणु
	अगर (ring->next_to_clean > ring->next_to_use)
		वापस ring->next_to_clean - ring->next_to_use - 1;

	वापस ring->count + ring->next_to_clean - ring->next_to_use - 1;
पूर्ण

#अगर_घोषित CONFIG_IGB_HWMON

#घोषणा IGB_HWMON_TYPE_LOC	0
#घोषणा IGB_HWMON_TYPE_TEMP	1
#घोषणा IGB_HWMON_TYPE_CAUTION	2
#घोषणा IGB_HWMON_TYPE_MAX	3

काष्ठा hwmon_attr अणु
	काष्ठा device_attribute dev_attr;
	काष्ठा e1000_hw *hw;
	काष्ठा e1000_thermal_diode_data *sensor;
	अक्षर name[12];
	पूर्ण;

काष्ठा hwmon_buff अणु
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
	काष्ठा attribute *attrs[E1000_MAX_SENSORS * 4 + 1];
	काष्ठा hwmon_attr hwmon_list[E1000_MAX_SENSORS * 4];
	अचिन्हित पूर्णांक n_hwmon;
	पूर्ण;
#पूर्ण_अगर

/* The number of L2 ether-type filter रेजिस्टरs, Index 3 is reserved
 * क्रम PTP 1588 बारtamp
 */
#घोषणा MAX_ETYPE_FILTER	(4 - 1)
/* ETQF filter list: one अटल filter per filter consumer. This is
 * to aव्योम filter collisions later. Add new filters here!!
 *
 * Current filters:		Filter 3
 */
#घोषणा IGB_ETQF_FILTER_1588	3

#घोषणा IGB_N_EXTTS	2
#घोषणा IGB_N_PEROUT	2
#घोषणा IGB_N_SDP	4
#घोषणा IGB_RETA_SIZE	128

क्रमागत igb_filter_match_flags अणु
	IGB_FILTER_FLAG_ETHER_TYPE = 0x1,
	IGB_FILTER_FLAG_VLAN_TCI   = 0x2,
	IGB_FILTER_FLAG_SRC_MAC_ADDR   = 0x4,
	IGB_FILTER_FLAG_DST_MAC_ADDR   = 0x8,
पूर्ण;

#घोषणा IGB_MAX_RXNFC_FILTERS 16

/* RX network flow classअगरication data काष्ठाure */
काष्ठा igb_nfc_input अणु
	/* Byte layout in order, all values with MSB first:
	 * match_flags - 1 byte
	 * etype - 2 bytes
	 * vlan_tci - 2 bytes
	 */
	u8 match_flags;
	__be16 etype;
	__be16 vlan_tci;
	u8 src_addr[ETH_ALEN];
	u8 dst_addr[ETH_ALEN];
पूर्ण;

काष्ठा igb_nfc_filter अणु
	काष्ठा hlist_node nfc_node;
	काष्ठा igb_nfc_input filter;
	अचिन्हित दीर्घ cookie;
	u16 etype_reg_index;
	u16 sw_idx;
	u16 action;
पूर्ण;

काष्ठा igb_mac_addr अणु
	u8 addr[ETH_ALEN];
	u8 queue;
	u8 state; /* biपंचांगask */
पूर्ण;

#घोषणा IGB_MAC_STATE_DEFAULT	0x1
#घोषणा IGB_MAC_STATE_IN_USE	0x2
#घोषणा IGB_MAC_STATE_SRC_ADDR	0x4
#घोषणा IGB_MAC_STATE_QUEUE_STEERING 0x8

/* board specअगरic निजी data काष्ठाure */
काष्ठा igb_adapter अणु
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	काष्ठा net_device *netdev;
	काष्ठा bpf_prog *xdp_prog;

	अचिन्हित दीर्घ state;
	अचिन्हित पूर्णांक flags;

	अचिन्हित पूर्णांक num_q_vectors;
	काष्ठा msix_entry msix_entries[MAX_MSIX_ENTRIES];

	/* Interrupt Throttle Rate */
	u32 rx_itr_setting;
	u32 tx_itr_setting;
	u16 tx_itr;
	u16 rx_itr;

	/* TX */
	u16 tx_work_limit;
	u32 tx_समयout_count;
	पूर्णांक num_tx_queues;
	काष्ठा igb_ring *tx_ring[16];

	/* RX */
	पूर्णांक num_rx_queues;
	काष्ठा igb_ring *rx_ring[16];

	u32 max_frame_size;
	u32 min_frame_size;

	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list phy_info_समयr;

	u16 mng_vlan_id;
	u32 bd_number;
	u32 wol;
	u32 en_mng_pt;
	u16 link_speed;
	u16 link_duplex;

	u8 __iomem *io_addr; /* Mainly क्रम iounmap use */

	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा watchकरोg_task;
	bool fc_स्वतःneg;
	u8  tx_समयout_factor;
	काष्ठा समयr_list blink_समयr;
	अचिन्हित दीर्घ led_status;

	/* OS defined काष्ठाs */
	काष्ठा pci_dev *pdev;

	spinlock_t stats64_lock;
	काष्ठा rtnl_link_stats64 stats64;

	/* काष्ठाs defined in e1000_hw.h */
	काष्ठा e1000_hw hw;
	काष्ठा e1000_hw_stats stats;
	काष्ठा e1000_phy_info phy_info;

	u32 test_icr;
	काष्ठा igb_ring test_tx_ring;
	काष्ठा igb_ring test_rx_ring;

	पूर्णांक msg_enable;

	काष्ठा igb_q_vector *q_vector[MAX_Q_VECTORS];
	u32 eims_enable_mask;
	u32 eims_other;

	/* to not mess up cache alignment, always add to the bottom */
	u16 tx_ring_count;
	u16 rx_ring_count;
	अचिन्हित पूर्णांक vfs_allocated_count;
	काष्ठा vf_data_storage *vf_data;
	पूर्णांक vf_rate_link_speed;
	u32 rss_queues;
	u32 wvbr;
	u32 *shaकरोw_vfta;

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_caps;
	काष्ठा delayed_work ptp_overflow_work;
	काष्ठा work_काष्ठा ptp_tx_work;
	काष्ठा sk_buff *ptp_tx_skb;
	काष्ठा hwtstamp_config tstamp_config;
	अचिन्हित दीर्घ ptp_tx_start;
	अचिन्हित दीर्घ last_rx_ptp_check;
	अचिन्हित दीर्घ last_rx_बारtamp;
	अचिन्हित पूर्णांक ptp_flags;
	spinlock_t पंचांगreg_lock;
	काष्ठा cyclecounter cc;
	काष्ठा समयcounter tc;
	u32 tx_hwtstamp_समयouts;
	u32 tx_hwtstamp_skipped;
	u32 rx_hwtstamp_cleared;
	bool pps_sys_wrap_on;

	काष्ठा ptp_pin_desc sdp_config[IGB_N_SDP];
	काष्ठा अणु
		काष्ठा बारpec64 start;
		काष्ठा बारpec64 period;
	पूर्ण perout[IGB_N_PEROUT];

	अक्षर fw_version[32];
#अगर_घोषित CONFIG_IGB_HWMON
	काष्ठा hwmon_buff *igb_hwmon_buff;
	bool ets;
#पूर्ण_अगर
	काष्ठा i2c_algo_bit_data i2c_algo;
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_client *i2c_client;
	u32 rss_indir_tbl_init;
	u8 rss_indir_tbl[IGB_RETA_SIZE];

	अचिन्हित दीर्घ link_check_समयout;
	पूर्णांक copper_tries;
	काष्ठा e1000_info ei;
	u16 eee_advert;

	/* RX network flow classअगरication support */
	काष्ठा hlist_head nfc_filter_list;
	काष्ठा hlist_head cls_flower_list;
	अचिन्हित पूर्णांक nfc_filter_count;
	/* lock क्रम RX network flow classअगरication filter */
	spinlock_t nfc_lock;
	bool etype_biपंचांगap[MAX_ETYPE_FILTER];

	काष्ठा igb_mac_addr *mac_table;
	काष्ठा vf_mac_filter vf_macs;
	काष्ठा vf_mac_filter *vf_mac_list;
पूर्ण;

/* flags controlling PTP/1588 function */
#घोषणा IGB_PTP_ENABLED		BIT(0)
#घोषणा IGB_PTP_OVERFLOW_CHECK	BIT(1)

#घोषणा IGB_FLAG_HAS_MSI		BIT(0)
#घोषणा IGB_FLAG_DCA_ENABLED		BIT(1)
#घोषणा IGB_FLAG_QUAD_PORT_A		BIT(2)
#घोषणा IGB_FLAG_QUEUE_PAIRS		BIT(3)
#घोषणा IGB_FLAG_DMAC			BIT(4)
#घोषणा IGB_FLAG_RSS_FIELD_IPV4_UDP	BIT(6)
#घोषणा IGB_FLAG_RSS_FIELD_IPV6_UDP	BIT(7)
#घोषणा IGB_FLAG_WOL_SUPPORTED		BIT(8)
#घोषणा IGB_FLAG_NEED_LINK_UPDATE	BIT(9)
#घोषणा IGB_FLAG_MEDIA_RESET		BIT(10)
#घोषणा IGB_FLAG_MAS_CAPABLE		BIT(11)
#घोषणा IGB_FLAG_MAS_ENABLE		BIT(12)
#घोषणा IGB_FLAG_HAS_MSIX		BIT(13)
#घोषणा IGB_FLAG_EEE			BIT(14)
#घोषणा IGB_FLAG_VLAN_PROMISC		BIT(15)
#घोषणा IGB_FLAG_RX_LEGACY		BIT(16)
#घोषणा IGB_FLAG_FQTSS			BIT(17)

/* Media Auto Sense */
#घोषणा IGB_MAS_ENABLE_0		0X0001
#घोषणा IGB_MAS_ENABLE_1		0X0002
#घोषणा IGB_MAS_ENABLE_2		0X0004
#घोषणा IGB_MAS_ENABLE_3		0X0008

/* DMA Coalescing defines */
#घोषणा IGB_MIN_TXPBSIZE	20408
#घोषणा IGB_TX_BUF_4096		4096
#घोषणा IGB_DMCTLX_DCFLUSH_DIS	0x80000000  /* Disable DMA Coal Flush */

#घोषणा IGB_82576_TSYNC_SHIFT	19
क्रमागत e1000_state_t अणु
	__IGB_TESTING,
	__IGB_RESETTING,
	__IGB_DOWN,
	__IGB_PTP_TX_IN_PROGRESS,
पूर्ण;

क्रमागत igb_boards अणु
	board_82575,
पूर्ण;

बाह्य अक्षर igb_driver_name[];

पूर्णांक igb_xmit_xdp_ring(काष्ठा igb_adapter *adapter,
		      काष्ठा igb_ring *ring,
		      काष्ठा xdp_frame *xdpf);
पूर्णांक igb_खोलो(काष्ठा net_device *netdev);
पूर्णांक igb_बंद(काष्ठा net_device *netdev);
पूर्णांक igb_up(काष्ठा igb_adapter *);
व्योम igb_करोwn(काष्ठा igb_adapter *);
व्योम igb_reinit_locked(काष्ठा igb_adapter *);
व्योम igb_reset(काष्ठा igb_adapter *);
पूर्णांक igb_reinit_queues(काष्ठा igb_adapter *);
व्योम igb_ग_लिखो_rss_indir_tbl(काष्ठा igb_adapter *);
पूर्णांक igb_set_spd_dplx(काष्ठा igb_adapter *, u32, u8);
पूर्णांक igb_setup_tx_resources(काष्ठा igb_ring *);
पूर्णांक igb_setup_rx_resources(काष्ठा igb_ring *);
व्योम igb_मुक्त_tx_resources(काष्ठा igb_ring *);
व्योम igb_मुक्त_rx_resources(काष्ठा igb_ring *);
व्योम igb_configure_tx_ring(काष्ठा igb_adapter *, काष्ठा igb_ring *);
व्योम igb_configure_rx_ring(काष्ठा igb_adapter *, काष्ठा igb_ring *);
व्योम igb_setup_tctl(काष्ठा igb_adapter *);
व्योम igb_setup_rctl(काष्ठा igb_adapter *);
व्योम igb_setup_srrctl(काष्ठा igb_adapter *, काष्ठा igb_ring *);
netdev_tx_t igb_xmit_frame_ring(काष्ठा sk_buff *, काष्ठा igb_ring *);
व्योम igb_alloc_rx_buffers(काष्ठा igb_ring *, u16);
व्योम igb_update_stats(काष्ठा igb_adapter *);
bool igb_has_link(काष्ठा igb_adapter *adapter);
व्योम igb_set_ethtool_ops(काष्ठा net_device *);
व्योम igb_घातer_up_link(काष्ठा igb_adapter *);
व्योम igb_set_fw_version(काष्ठा igb_adapter *);
व्योम igb_ptp_init(काष्ठा igb_adapter *adapter);
व्योम igb_ptp_stop(काष्ठा igb_adapter *adapter);
व्योम igb_ptp_reset(काष्ठा igb_adapter *adapter);
व्योम igb_ptp_suspend(काष्ठा igb_adapter *adapter);
व्योम igb_ptp_rx_hang(काष्ठा igb_adapter *adapter);
व्योम igb_ptp_tx_hang(काष्ठा igb_adapter *adapter);
व्योम igb_ptp_rx_rgtstamp(काष्ठा igb_q_vector *q_vector, काष्ठा sk_buff *skb);
पूर्णांक igb_ptp_rx_pktstamp(काष्ठा igb_q_vector *q_vector, व्योम *va,
			kसमय_प्रकार *बारtamp);
पूर्णांक igb_ptp_set_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr);
पूर्णांक igb_ptp_get_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr);
व्योम igb_set_flag_queue_pairs(काष्ठा igb_adapter *, स्थिर u32);
अचिन्हित पूर्णांक igb_get_max_rss_queues(काष्ठा igb_adapter *);
#अगर_घोषित CONFIG_IGB_HWMON
व्योम igb_sysfs_निकास(काष्ठा igb_adapter *adapter);
पूर्णांक igb_sysfs_init(काष्ठा igb_adapter *adapter);
#पूर्ण_अगर
अटल अंतरभूत s32 igb_reset_phy(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->phy.ops.reset)
		वापस hw->phy.ops.reset(hw);

	वापस 0;
पूर्ण

अटल अंतरभूत s32 igb_पढ़ो_phy_reg(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	अगर (hw->phy.ops.पढ़ो_reg)
		वापस hw->phy.ops.पढ़ो_reg(hw, offset, data);

	वापस 0;
पूर्ण

अटल अंतरभूत s32 igb_ग_लिखो_phy_reg(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	अगर (hw->phy.ops.ग_लिखो_reg)
		वापस hw->phy.ops.ग_लिखो_reg(hw, offset, data);

	वापस 0;
पूर्ण

अटल अंतरभूत s32 igb_get_phy_info(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->phy.ops.get_phy_info)
		वापस hw->phy.ops.get_phy_info(hw);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा igb_ring *tx_ring)
अणु
	वापस netdev_get_tx_queue(tx_ring->netdev, tx_ring->queue_index);
पूर्ण

पूर्णांक igb_add_filter(काष्ठा igb_adapter *adapter,
		   काष्ठा igb_nfc_filter *input);
पूर्णांक igb_erase_filter(काष्ठा igb_adapter *adapter,
		     काष्ठा igb_nfc_filter *input);

पूर्णांक igb_add_mac_steering_filter(काष्ठा igb_adapter *adapter,
				स्थिर u8 *addr, u8 queue, u8 flags);
पूर्णांक igb_del_mac_steering_filter(काष्ठा igb_adapter *adapter,
				स्थिर u8 *addr, u8 queue, u8 flags);

#पूर्ण_अगर /* _IGB_H_ */
