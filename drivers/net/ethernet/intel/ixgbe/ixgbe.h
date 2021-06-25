<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_H_
#घोषणा _IXGBE_H_

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/aer.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/phy.h>

#समावेश <linux/समयcounter.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश "ixgbe_type.h"
#समावेश "ixgbe_common.h"
#समावेश "ixgbe_dcb.h"
#अगर IS_ENABLED(CONFIG_FCOE)
#घोषणा IXGBE_FCOE
#समावेश "ixgbe_fcoe.h"
#पूर्ण_अगर /* IS_ENABLED(CONFIG_FCOE) */
#अगर_घोषित CONFIG_IXGBE_DCA
#समावेश <linux/dca.h>
#पूर्ण_अगर
#समावेश "ixgbe_ipsec.h"

#समावेश <net/xdp.h>

/* common prefix used by pr_<> macros */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* TX/RX descriptor defines */
#घोषणा IXGBE_DEFAULT_TXD		    512
#घोषणा IXGBE_DEFAULT_TX_WORK		    256
#घोषणा IXGBE_MAX_TXD			   4096
#घोषणा IXGBE_MIN_TXD			     64

#अगर (PAGE_SIZE < 8192)
#घोषणा IXGBE_DEFAULT_RXD		    512
#अन्यथा
#घोषणा IXGBE_DEFAULT_RXD		    128
#पूर्ण_अगर
#घोषणा IXGBE_MAX_RXD			   4096
#घोषणा IXGBE_MIN_RXD			     64

/* flow control */
#घोषणा IXGBE_MIN_FCRTL			   0x40
#घोषणा IXGBE_MAX_FCRTL			0x7FF80
#घोषणा IXGBE_MIN_FCRTH			  0x600
#घोषणा IXGBE_MAX_FCRTH			0x7FFF0
#घोषणा IXGBE_DEFAULT_FCPAUSE		 0xFFFF
#घोषणा IXGBE_MIN_FCPAUSE		      0
#घोषणा IXGBE_MAX_FCPAUSE		 0xFFFF

/* Supported Rx Buffer Sizes */
#घोषणा IXGBE_RXBUFFER_256    256  /* Used क्रम skb receive header */
#घोषणा IXGBE_RXBUFFER_1536  1536
#घोषणा IXGBE_RXBUFFER_2K    2048
#घोषणा IXGBE_RXBUFFER_3K    3072
#घोषणा IXGBE_RXBUFFER_4K    4096
#घोषणा IXGBE_MAX_RXBUFFER  16384  /* largest size क्रम a single descriptor */

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
#घोषणा IXGBE_MAX_2K_FRAME_BUILD_SKB (IXGBE_RXBUFFER_1536 - NET_IP_ALIGN)
#घोषणा IXGBE_2K_TOO_SMALL_WITH_PADDING \
((NET_SKB_PAD + IXGBE_RXBUFFER_1536) > SKB_WITH_OVERHEAD(IXGBE_RXBUFFER_2K))

अटल अंतरभूत पूर्णांक ixgbe_compute_pad(पूर्णांक rx_buf_len)
अणु
	पूर्णांक page_size, pad_size;

	page_size = ALIGN(rx_buf_len, PAGE_SIZE / 2);
	pad_size = SKB_WITH_OVERHEAD(page_size) - rx_buf_len;

	वापस pad_size;
पूर्ण

अटल अंतरभूत पूर्णांक ixgbe_skb_pad(व्योम)
अणु
	पूर्णांक rx_buf_len;

	/* If a 2K buffer cannot handle a standard Ethernet frame then
	 * optimize padding क्रम a 3K buffer instead of a 1.5K buffer.
	 *
	 * For a 3K buffer we need to add enough padding to allow क्रम
	 * tailroom due to NET_IP_ALIGN possibly shअगरting us out of
	 * cache-line alignment.
	 */
	अगर (IXGBE_2K_TOO_SMALL_WITH_PADDING)
		rx_buf_len = IXGBE_RXBUFFER_3K + SKB_DATA_ALIGN(NET_IP_ALIGN);
	अन्यथा
		rx_buf_len = IXGBE_RXBUFFER_1536;

	/* अगर needed make room क्रम NET_IP_ALIGN */
	rx_buf_len -= NET_IP_ALIGN;

	वापस ixgbe_compute_pad(rx_buf_len);
पूर्ण

#घोषणा IXGBE_SKB_PAD	ixgbe_skb_pad()
#अन्यथा
#घोषणा IXGBE_SKB_PAD	(NET_SKB_PAD + NET_IP_ALIGN)
#पूर्ण_अगर

/*
 * NOTE: netdev_alloc_skb reserves up to 64 bytes, NET_IP_ALIGN means we
 * reserve 64 more, and skb_shared_info adds an additional 320 bytes more,
 * this adds up to 448 bytes of extra data.
 *
 * Since netdev_alloc_skb now allocates a page fragment we can use a value
 * of 256 and the resultant skb will have a truesize of 960 or less.
 */
#घोषणा IXGBE_RX_HDR_SIZE IXGBE_RXBUFFER_256

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IXGBE_RX_BUFFER_WRITE	16	/* Must be घातer of 2 */

#घोषणा IXGBE_RX_DMA_ATTR \
	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

क्रमागत ixgbe_tx_flags अणु
	/* cmd_type flags */
	IXGBE_TX_FLAGS_HW_VLAN	= 0x01,
	IXGBE_TX_FLAGS_TSO	= 0x02,
	IXGBE_TX_FLAGS_TSTAMP	= 0x04,

	/* olinfo flags */
	IXGBE_TX_FLAGS_CC	= 0x08,
	IXGBE_TX_FLAGS_IPV4	= 0x10,
	IXGBE_TX_FLAGS_CSUM	= 0x20,
	IXGBE_TX_FLAGS_IPSEC	= 0x40,

	/* software defined flags */
	IXGBE_TX_FLAGS_SW_VLAN	= 0x80,
	IXGBE_TX_FLAGS_FCOE	= 0x100,
पूर्ण;

/* VLAN info */
#घोषणा IXGBE_TX_FLAGS_VLAN_MASK	0xffff0000
#घोषणा IXGBE_TX_FLAGS_VLAN_PRIO_MASK	0xe0000000
#घोषणा IXGBE_TX_FLAGS_VLAN_PRIO_SHIFT  29
#घोषणा IXGBE_TX_FLAGS_VLAN_SHIFT	16

#घोषणा IXGBE_MAX_VF_MC_ENTRIES         30
#घोषणा IXGBE_MAX_VF_FUNCTIONS          64
#घोषणा IXGBE_MAX_VFTA_ENTRIES          128
#घोषणा MAX_EMULATION_MAC_ADDRS         16
#घोषणा IXGBE_MAX_PF_MACVLANS           15
#घोषणा VMDQ_P(p)   ((p) + adapter->ring_feature[RING_F_VMDQ].offset)
#घोषणा IXGBE_82599_VF_DEVICE_ID        0x10ED
#घोषणा IXGBE_X540_VF_DEVICE_ID         0x1515

काष्ठा vf_data_storage अणु
	काष्ठा pci_dev *vfdev;
	अचिन्हित अक्षर vf_mac_addresses[ETH_ALEN];
	u16 vf_mc_hashes[IXGBE_MAX_VF_MC_ENTRIES];
	u16 num_vf_mc_hashes;
	bool clear_to_send;
	bool pf_set_mac;
	u16 pf_vlan; /* When set, guest VLAN config not allowed. */
	u16 pf_qos;
	u16 tx_rate;
	u8 spoofchk_enabled;
	bool rss_query_enabled;
	u8 trusted;
	पूर्णांक xcast_mode;
	अचिन्हित पूर्णांक vf_api;
पूर्ण;

क्रमागत ixgbevf_xcast_modes अणु
	IXGBEVF_XCAST_MODE_NONE = 0,
	IXGBEVF_XCAST_MODE_MULTI,
	IXGBEVF_XCAST_MODE_ALLMULTI,
	IXGBEVF_XCAST_MODE_PROMISC,
पूर्ण;

काष्ठा vf_macvlans अणु
	काष्ठा list_head l;
	पूर्णांक vf;
	bool मुक्त;
	bool is_macvlan;
	u8 vf_macvlan[ETH_ALEN];
पूर्ण;

#घोषणा IXGBE_MAX_TXD_PWR	14
#घोषणा IXGBE_MAX_DATA_PER_TXD	(1u << IXGBE_MAX_TXD_PWR)

/* Tx Descriptors needed, worst हाल */
#घोषणा TXD_USE_COUNT(S) DIV_ROUND_UP((S), IXGBE_MAX_DATA_PER_TXD)
#घोषणा DESC_NEEDED (MAX_SKB_FRAGS + 4)

/* wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer */
काष्ठा ixgbe_tx_buffer अणु
	जोड़ ixgbe_adv_tx_desc *next_to_watch;
	अचिन्हित दीर्घ समय_stamp;
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा xdp_frame *xdpf;
	पूर्ण;
	अचिन्हित पूर्णांक bytecount;
	अचिन्हित लघु gso_segs;
	__be16 protocol;
	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
	u32 tx_flags;
पूर्ण;

काष्ठा ixgbe_rx_buffer अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा sk_buff *skb;
			dma_addr_t dma;
			काष्ठा page *page;
			__u32 page_offset;
			__u16 pagecnt_bias;
		पूर्ण;
		काष्ठा अणु
			bool discard;
			काष्ठा xdp_buff *xdp;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा ixgbe_queue_stats अणु
	u64 packets;
	u64 bytes;
पूर्ण;

काष्ठा ixgbe_tx_queue_stats अणु
	u64 restart_queue;
	u64 tx_busy;
	u64 tx_करोne_old;
पूर्ण;

काष्ठा ixgbe_rx_queue_stats अणु
	u64 rsc_count;
	u64 rsc_flush;
	u64 non_eop_descs;
	u64 alloc_rx_page;
	u64 alloc_rx_page_failed;
	u64 alloc_rx_buff_failed;
	u64 csum_err;
पूर्ण;

#घोषणा IXGBE_TS_HDR_LEN 8

क्रमागत ixgbe_ring_state_t अणु
	__IXGBE_RX_3K_BUFFER,
	__IXGBE_RX_BUILD_SKB_ENABLED,
	__IXGBE_RX_RSC_ENABLED,
	__IXGBE_RX_CSUM_UDP_ZERO_ERR,
	__IXGBE_RX_FCOE,
	__IXGBE_TX_Fसूची_INIT_DONE,
	__IXGBE_TX_XPS_INIT_DONE,
	__IXGBE_TX_DETECT_HANG,
	__IXGBE_HANG_CHECK_ARMED,
	__IXGBE_TX_XDP_RING,
	__IXGBE_TX_DISABLED,
पूर्ण;

#घोषणा ring_uses_build_skb(ring) \
	test_bit(__IXGBE_RX_BUILD_SKB_ENABLED, &(ring)->state)

काष्ठा ixgbe_fwd_adapter अणु
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	काष्ठा net_device *netdev;
	अचिन्हित पूर्णांक tx_base_queue;
	अचिन्हित पूर्णांक rx_base_queue;
	पूर्णांक pool;
पूर्ण;

#घोषणा check_क्रम_tx_hang(ring) \
	test_bit(__IXGBE_TX_DETECT_HANG, &(ring)->state)
#घोषणा set_check_क्रम_tx_hang(ring) \
	set_bit(__IXGBE_TX_DETECT_HANG, &(ring)->state)
#घोषणा clear_check_क्रम_tx_hang(ring) \
	clear_bit(__IXGBE_TX_DETECT_HANG, &(ring)->state)
#घोषणा ring_is_rsc_enabled(ring) \
	test_bit(__IXGBE_RX_RSC_ENABLED, &(ring)->state)
#घोषणा set_ring_rsc_enabled(ring) \
	set_bit(__IXGBE_RX_RSC_ENABLED, &(ring)->state)
#घोषणा clear_ring_rsc_enabled(ring) \
	clear_bit(__IXGBE_RX_RSC_ENABLED, &(ring)->state)
#घोषणा ring_is_xdp(ring) \
	test_bit(__IXGBE_TX_XDP_RING, &(ring)->state)
#घोषणा set_ring_xdp(ring) \
	set_bit(__IXGBE_TX_XDP_RING, &(ring)->state)
#घोषणा clear_ring_xdp(ring) \
	clear_bit(__IXGBE_TX_XDP_RING, &(ring)->state)
काष्ठा ixgbe_ring अणु
	काष्ठा ixgbe_ring *next;	/* poपूर्णांकer to next ring in q_vector */
	काष्ठा ixgbe_q_vector *q_vector; /* backpoपूर्णांकer to host q_vector */
	काष्ठा net_device *netdev;	/* netdev ring beदीर्घs to */
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा device *dev;		/* device क्रम DMA mapping */
	व्योम *desc;			/* descriptor ring memory */
	जोड़ अणु
		काष्ठा ixgbe_tx_buffer *tx_buffer_info;
		काष्ठा ixgbe_rx_buffer *rx_buffer_info;
	पूर्ण;
	अचिन्हित दीर्घ state;
	u8 __iomem *tail;
	dma_addr_t dma;			/* phys. address of descriptor ring */
	अचिन्हित पूर्णांक size;		/* length in bytes */

	u16 count;			/* amount of descriptors */

	u8 queue_index; /* needed क्रम multiqueue queue management */
	u8 reg_idx;			/* holds the special value that माला_लो
					 * the hardware रेजिस्टर offset
					 * associated with this ring, which is
					 * dअगरferent क्रम DCB and RSS modes
					 */
	u16 next_to_use;
	u16 next_to_clean;

	अचिन्हित दीर्घ last_rx_बारtamp;

	जोड़ अणु
		u16 next_to_alloc;
		काष्ठा अणु
			u8 atr_sample_rate;
			u8 atr_count;
		पूर्ण;
	पूर्ण;

	u8 dcb_tc;
	काष्ठा ixgbe_queue_stats stats;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		काष्ठा ixgbe_tx_queue_stats tx_stats;
		काष्ठा ixgbe_rx_queue_stats rx_stats;
	पूर्ण;
	u16 rx_offset;
	काष्ठा xdp_rxq_info xdp_rxq;
	काष्ठा xsk_buff_pool *xsk_pool;
	u16 ring_idx;		/* अणुrx,tx,xdpपूर्ण_ring back reference idx */
	u16 rx_buf_len;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

क्रमागत ixgbe_ring_f_क्रमागत अणु
	RING_F_NONE = 0,
	RING_F_VMDQ,  /* SR-IOV uses the same ring feature */
	RING_F_RSS,
	RING_F_Fसूची,
#अगर_घोषित IXGBE_FCOE
	RING_F_FCOE,
#पूर्ण_अगर /* IXGBE_FCOE */

	RING_F_ARRAY_SIZE      /* must be last in क्रमागत set */
पूर्ण;

#घोषणा IXGBE_MAX_RSS_INDICES		16
#घोषणा IXGBE_MAX_RSS_INDICES_X550	63
#घोषणा IXGBE_MAX_VMDQ_INDICES		64
#घोषणा IXGBE_MAX_Fसूची_INDICES		63	/* based on q_vector limit */
#घोषणा IXGBE_MAX_FCOE_INDICES		8
#घोषणा MAX_RX_QUEUES			(IXGBE_MAX_Fसूची_INDICES + 1)
#घोषणा MAX_TX_QUEUES			(IXGBE_MAX_Fसूची_INDICES + 1)
#घोषणा MAX_XDP_QUEUES			(IXGBE_MAX_Fसूची_INDICES + 1)
#घोषणा IXGBE_MAX_L2A_QUEUES		4
#घोषणा IXGBE_BAD_L2A_QUEUE		3
#घोषणा IXGBE_MAX_MACVLANS		63

काष्ठा ixgbe_ring_feature अणु
	u16 limit;	/* upper limit on feature indices */
	u16 indices;	/* current value of indices */
	u16 mask;	/* Mask used क्रम feature to ring mapping */
	u16 offset;	/* offset to start of feature */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

#घोषणा IXGBE_82599_VMDQ_8Q_MASK 0x78
#घोषणा IXGBE_82599_VMDQ_4Q_MASK 0x7C
#घोषणा IXGBE_82599_VMDQ_2Q_MASK 0x7E

/*
 * FCoE requires that all Rx buffers be over 2200 bytes in length.  Since
 * this is twice the size of a half page we need to द्विगुन the page order
 * क्रम FCoE enabled Rx queues.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ixgbe_rx_bufsz(काष्ठा ixgbe_ring *ring)
अणु
	अगर (test_bit(__IXGBE_RX_3K_BUFFER, &ring->state))
		वापस IXGBE_RXBUFFER_3K;
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_build_skb(ring))
		वापस IXGBE_MAX_2K_FRAME_BUILD_SKB;
#पूर्ण_अगर
	वापस IXGBE_RXBUFFER_2K;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ixgbe_rx_pg_order(काष्ठा ixgbe_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (test_bit(__IXGBE_RX_3K_BUFFER, &ring->state))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण
#घोषणा ixgbe_rx_pg_size(_ring) (PAGE_SIZE << ixgbe_rx_pg_order(_ring))

#घोषणा IXGBE_ITR_ADAPTIVE_MIN_INC	2
#घोषणा IXGBE_ITR_ADAPTIVE_MIN_USECS	10
#घोषणा IXGBE_ITR_ADAPTIVE_MAX_USECS	126
#घोषणा IXGBE_ITR_ADAPTIVE_LATENCY	0x80
#घोषणा IXGBE_ITR_ADAPTIVE_BULK		0x00

काष्ठा ixgbe_ring_container अणु
	काष्ठा ixgbe_ring *ring;	/* poपूर्णांकer to linked list of rings */
	अचिन्हित दीर्घ next_update;	/* jअगरfies value of last update */
	अचिन्हित पूर्णांक total_bytes;	/* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;	/* total packets processed this पूर्णांक */
	u16 work_limit;			/* total work allowed per पूर्णांकerrupt */
	u8 count;			/* total number of rings in vector */
	u8 itr;				/* current ITR setting क्रम ring */
पूर्ण;

/* iterator क्रम handling rings in ring container */
#घोषणा ixgbe_क्रम_each_ring(pos, head) \
	क्रम (pos = (head).ring; pos != शून्य; pos = pos->next)

#घोषणा MAX_RX_PACKET_BUFFERS ((adapter->flags & IXGBE_FLAG_DCB_ENABLED) \
			      ? 8 : 1)
#घोषणा MAX_TX_PACKET_BUFFERS MAX_RX_PACKET_BUFFERS

/* MAX_Q_VECTORS of these are allocated,
 * but we only use one per queue-specअगरic vector.
 */
काष्ठा ixgbe_q_vector अणु
	काष्ठा ixgbe_adapter *adapter;
#अगर_घोषित CONFIG_IXGBE_DCA
	पूर्णांक cpu;	    /* CPU क्रम DCA */
#पूर्ण_अगर
	u16 v_idx;		/* index of q_vector within array, also used क्रम
				 * finding the bit in EICR and मित्रs that
				 * represents the vector क्रम this ring */
	u16 itr;		/* Interrupt throttle rate written to EITR */
	काष्ठा ixgbe_ring_container rx, tx;

	काष्ठा napi_काष्ठा napi;
	cpumask_t affinity_mask;
	पूर्णांक numa_node;
	काष्ठा rcu_head rcu;	/* to aव्योम race with update stats on मुक्त */
	अक्षर name[IFNAMSIZ + 9];

	/* क्रम dynamic allocation of rings associated with this q_vector */
	काष्ठा ixgbe_ring ring[] ____cacheline_पूर्णांकernodealigned_in_smp;
पूर्ण;

#अगर_घोषित CONFIG_IXGBE_HWMON

#घोषणा IXGBE_HWMON_TYPE_LOC		0
#घोषणा IXGBE_HWMON_TYPE_TEMP		1
#घोषणा IXGBE_HWMON_TYPE_CAUTION	2
#घोषणा IXGBE_HWMON_TYPE_MAX		3

काष्ठा hwmon_attr अणु
	काष्ठा device_attribute dev_attr;
	काष्ठा ixgbe_hw *hw;
	काष्ठा ixgbe_thermal_diode_data *sensor;
	अक्षर name[12];
पूर्ण;

काष्ठा hwmon_buff अणु
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
	काष्ठा attribute *attrs[IXGBE_MAX_SENSORS * 4 + 1];
	काष्ठा hwmon_attr hwmon_list[IXGBE_MAX_SENSORS * 4];
	अचिन्हित पूर्णांक n_hwmon;
पूर्ण;
#पूर्ण_अगर /* CONFIG_IXGBE_HWMON */

/*
 * microsecond values क्रम various ITR rates shअगरted by 2 to fit itr रेजिस्टर
 * with the first 3 bits reserved 0
 */
#घोषणा IXGBE_MIN_RSC_ITR	24
#घोषणा IXGBE_100K_ITR		40
#घोषणा IXGBE_20K_ITR		200
#घोषणा IXGBE_12K_ITR		336

/* ixgbe_test_staterr - tests bits in Rx descriptor status and error fields */
अटल अंतरभूत __le32 ixgbe_test_staterr(जोड़ ixgbe_adv_rx_desc *rx_desc,
					स्थिर u32 stat_err_bits)
अणु
	वापस rx_desc->wb.upper.status_error & cpu_to_le32(stat_err_bits);
पूर्ण

अटल अंतरभूत u16 ixgbe_desc_unused(काष्ठा ixgbe_ring *ring)
अणु
	u16 ntc = ring->next_to_clean;
	u16 ntu = ring->next_to_use;

	वापस ((ntc > ntu) ? 0 : ring->count) + ntc - ntu - 1;
पूर्ण

#घोषणा IXGBE_RX_DESC(R, i)	    \
	(&(((जोड़ ixgbe_adv_rx_desc *)((R)->desc))[i]))
#घोषणा IXGBE_TX_DESC(R, i)	    \
	(&(((जोड़ ixgbe_adv_tx_desc *)((R)->desc))[i]))
#घोषणा IXGBE_TX_CTXTDESC(R, i)	    \
	(&(((काष्ठा ixgbe_adv_tx_context_desc *)((R)->desc))[i]))

#घोषणा IXGBE_MAX_JUMBO_FRAME_SIZE	9728 /* Maximum Supported Size 9.5KB */
#अगर_घोषित IXGBE_FCOE
/* Use 3K as the baby jumbo frame size क्रम FCoE */
#घोषणा IXGBE_FCOE_JUMBO_FRAME_SIZE       3072
#पूर्ण_अगर /* IXGBE_FCOE */

#घोषणा OTHER_VECTOR 1
#घोषणा NON_Q_VECTORS (OTHER_VECTOR)

#घोषणा MAX_MSIX_VECTORS_82599 64
#घोषणा MAX_Q_VECTORS_82599 64
#घोषणा MAX_MSIX_VECTORS_82598 18
#घोषणा MAX_Q_VECTORS_82598 16

काष्ठा ixgbe_mac_addr अणु
	u8 addr[ETH_ALEN];
	u16 pool;
	u16 state; /* biपंचांगask */
पूर्ण;

#घोषणा IXGBE_MAC_STATE_DEFAULT		0x1
#घोषणा IXGBE_MAC_STATE_MODIFIED	0x2
#घोषणा IXGBE_MAC_STATE_IN_USE		0x4

#घोषणा MAX_Q_VECTORS MAX_Q_VECTORS_82599
#घोषणा MAX_MSIX_COUNT MAX_MSIX_VECTORS_82599

#घोषणा MIN_MSIX_Q_VECTORS 1
#घोषणा MIN_MSIX_COUNT (MIN_MSIX_Q_VECTORS + NON_Q_VECTORS)

/* शेष to trying क्रम four seconds */
#घोषणा IXGBE_TRY_LINK_TIMEOUT (4 * HZ)
#घोषणा IXGBE_SFP_POLL_JIFFIES (2 * HZ)	/* SFP poll every 2 seconds */

/* board specअगरic निजी data काष्ठाure */
काष्ठा ixgbe_adapter अणु
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा pci_dev *pdev;
	काष्ठा mii_bus *mii_bus;

	अचिन्हित दीर्घ state;

	/* Some features need tri-state capability,
	 * thus the additional *_CAPABLE flags.
	 */
	u32 flags;
#घोषणा IXGBE_FLAG_MSI_ENABLED			BIT(1)
#घोषणा IXGBE_FLAG_MSIX_ENABLED			BIT(3)
#घोषणा IXGBE_FLAG_RX_1BUF_CAPABLE		BIT(4)
#घोषणा IXGBE_FLAG_RX_PS_CAPABLE		BIT(5)
#घोषणा IXGBE_FLAG_RX_PS_ENABLED		BIT(6)
#घोषणा IXGBE_FLAG_DCA_ENABLED			BIT(8)
#घोषणा IXGBE_FLAG_DCA_CAPABLE			BIT(9)
#घोषणा IXGBE_FLAG_IMIR_ENABLED			BIT(10)
#घोषणा IXGBE_FLAG_MQ_CAPABLE			BIT(11)
#घोषणा IXGBE_FLAG_DCB_ENABLED			BIT(12)
#घोषणा IXGBE_FLAG_VMDQ_CAPABLE			BIT(13)
#घोषणा IXGBE_FLAG_VMDQ_ENABLED			BIT(14)
#घोषणा IXGBE_FLAG_FAN_FAIL_CAPABLE		BIT(15)
#घोषणा IXGBE_FLAG_NEED_LINK_UPDATE		BIT(16)
#घोषणा IXGBE_FLAG_NEED_LINK_CONFIG		BIT(17)
#घोषणा IXGBE_FLAG_Fसूची_HASH_CAPABLE		BIT(18)
#घोषणा IXGBE_FLAG_Fसूची_PERFECT_CAPABLE		BIT(19)
#घोषणा IXGBE_FLAG_FCOE_CAPABLE			BIT(20)
#घोषणा IXGBE_FLAG_FCOE_ENABLED			BIT(21)
#घोषणा IXGBE_FLAG_SRIOV_CAPABLE		BIT(22)
#घोषणा IXGBE_FLAG_SRIOV_ENABLED		BIT(23)
#घोषणा IXGBE_FLAG_RX_HWTSTAMP_ENABLED		BIT(25)
#घोषणा IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER	BIT(26)
#घोषणा IXGBE_FLAG_DCB_CAPABLE			BIT(27)

	u32 flags2;
#घोषणा IXGBE_FLAG2_RSC_CAPABLE			BIT(0)
#घोषणा IXGBE_FLAG2_RSC_ENABLED			BIT(1)
#घोषणा IXGBE_FLAG2_TEMP_SENSOR_CAPABLE		BIT(2)
#घोषणा IXGBE_FLAG2_TEMP_SENSOR_EVENT		BIT(3)
#घोषणा IXGBE_FLAG2_SEARCH_FOR_SFP		BIT(4)
#घोषणा IXGBE_FLAG2_SFP_NEEDS_RESET		BIT(5)
#घोषणा IXGBE_FLAG2_Fसूची_REQUIRES_REINIT	BIT(7)
#घोषणा IXGBE_FLAG2_RSS_FIELD_IPV4_UDP		BIT(8)
#घोषणा IXGBE_FLAG2_RSS_FIELD_IPV6_UDP		BIT(9)
#घोषणा IXGBE_FLAG2_PTP_PPS_ENABLED		BIT(10)
#घोषणा IXGBE_FLAG2_PHY_INTERRUPT		BIT(11)
#घोषणा IXGBE_FLAG2_VLAN_PROMISC		BIT(13)
#घोषणा IXGBE_FLAG2_EEE_CAPABLE			BIT(14)
#घोषणा IXGBE_FLAG2_EEE_ENABLED			BIT(15)
#घोषणा IXGBE_FLAG2_RX_LEGACY			BIT(16)
#घोषणा IXGBE_FLAG2_IPSEC_ENABLED		BIT(17)
#घोषणा IXGBE_FLAG2_VF_IPSEC_ENABLED		BIT(18)

	/* Tx fast path data */
	पूर्णांक num_tx_queues;
	u16 tx_itr_setting;
	u16 tx_work_limit;
	u64 tx_ipsec;

	/* Rx fast path data */
	पूर्णांक num_rx_queues;
	u16 rx_itr_setting;
	u64 rx_ipsec;

	/* Port number used to identअगरy VXLAN traffic */
	__be16 vxlan_port;
	__be16 geneve_port;

	/* XDP */
	पूर्णांक num_xdp_queues;
	काष्ठा ixgbe_ring *xdp_ring[MAX_XDP_QUEUES];
	अचिन्हित दीर्घ *af_xdp_zc_qps; /* tracks AF_XDP ZC enabled rings */

	/* TX */
	काष्ठा ixgbe_ring *tx_ring[MAX_TX_QUEUES] ____cacheline_aligned_in_smp;

	u64 restart_queue;
	u64 lsc_पूर्णांक;
	u32 tx_समयout_count;

	/* RX */
	काष्ठा ixgbe_ring *rx_ring[MAX_RX_QUEUES];
	पूर्णांक num_rx_pools;		/* == num_rx_queues in 82598 */
	पूर्णांक num_rx_queues_per_pool;	/* 1 अगर 82598, can be many अगर 82599 */
	u64 hw_csum_rx_error;
	u64 hw_rx_no_dma_resources;
	u64 rsc_total_count;
	u64 rsc_total_flush;
	u64 non_eop_descs;
	u32 alloc_rx_page;
	u32 alloc_rx_page_failed;
	u32 alloc_rx_buff_failed;

	काष्ठा ixgbe_q_vector *q_vector[MAX_Q_VECTORS];

	/* DCB parameters */
	काष्ठा ieee_pfc *ixgbe_ieee_pfc;
	काष्ठा ieee_ets *ixgbe_ieee_ets;
	काष्ठा ixgbe_dcb_config dcb_cfg;
	काष्ठा ixgbe_dcb_config temp_dcb_cfg;
	u8 hw_tcs;
	u8 dcb_set_biपंचांगap;
	u8 dcbx_cap;
	क्रमागत ixgbe_fc_mode last_lfc_mode;

	पूर्णांक num_q_vectors;	/* current number of q_vectors क्रम device */
	पूर्णांक max_q_vectors;	/* true count of q_vectors क्रम device */
	काष्ठा ixgbe_ring_feature ring_feature[RING_F_ARRAY_SIZE];
	काष्ठा msix_entry *msix_entries;

	u32 test_icr;
	काष्ठा ixgbe_ring test_tx_ring;
	काष्ठा ixgbe_ring test_rx_ring;

	/* काष्ठाs defined in ixgbe_hw.h */
	काष्ठा ixgbe_hw hw;
	u16 msg_enable;
	काष्ठा ixgbe_hw_stats stats;

	u64 tx_busy;
	अचिन्हित पूर्णांक tx_ring_count;
	अचिन्हित पूर्णांक xdp_ring_count;
	अचिन्हित पूर्णांक rx_ring_count;

	u32 link_speed;
	bool link_up;
	अचिन्हित दीर्घ sfp_poll_समय;
	अचिन्हित दीर्घ link_check_समयout;

	काष्ठा समयr_list service_समयr;
	काष्ठा work_काष्ठा service_task;

	काष्ठा hlist_head fdir_filter_list;
	अचिन्हित दीर्घ fdir_overflow; /* number of बार ATR was backed off */
	जोड़ ixgbe_atr_input fdir_mask;
	पूर्णांक fdir_filter_count;
	u32 fdir_pballoc;
	u32 atr_sample_rate;
	spinlock_t fdir_perfect_lock;

#अगर_घोषित IXGBE_FCOE
	काष्ठा ixgbe_fcoe fcoe;
#पूर्ण_अगर /* IXGBE_FCOE */
	u8 __iomem *io_addr; /* Mainly क्रम iounmap use */
	u32 wol;

	u16 bridge_mode;

	अक्षर eeprom_id[NVM_VER_SIZE];
	u16 eeprom_cap;

	u32 पूर्णांकerrupt_event;
	u32 led_reg;

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_caps;
	काष्ठा work_काष्ठा ptp_tx_work;
	काष्ठा sk_buff *ptp_tx_skb;
	काष्ठा hwtstamp_config tstamp_config;
	अचिन्हित दीर्घ ptp_tx_start;
	अचिन्हित दीर्घ last_overflow_check;
	अचिन्हित दीर्घ last_rx_ptp_check;
	अचिन्हित दीर्घ last_rx_बारtamp;
	spinlock_t पंचांगreg_lock;
	काष्ठा cyclecounter hw_cc;
	काष्ठा समयcounter hw_tc;
	u32 base_incval;
	u32 tx_hwtstamp_समयouts;
	u32 tx_hwtstamp_skipped;
	u32 rx_hwtstamp_cleared;
	व्योम (*ptp_setup_sdp)(काष्ठा ixgbe_adapter *);

	/* SR-IOV */
	DECLARE_BITMAP(active_vfs, IXGBE_MAX_VF_FUNCTIONS);
	अचिन्हित पूर्णांक num_vfs;
	काष्ठा vf_data_storage *vfinfo;
	पूर्णांक vf_rate_link_speed;
	काष्ठा vf_macvlans vf_mvs;
	काष्ठा vf_macvlans *mv_list;

	u32 समयr_event_accumulator;
	u32 vferr_refcount;
	काष्ठा ixgbe_mac_addr *mac_table;
	काष्ठा kobject *info_kobj;
#अगर_घोषित CONFIG_IXGBE_HWMON
	काष्ठा hwmon_buff *ixgbe_hwmon_buff;
#पूर्ण_अगर /* CONFIG_IXGBE_HWMON */
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *ixgbe_dbg_adapter;
#पूर्ण_अगर /*CONFIG_DEBUG_FS*/

	u8 शेष_up;
	/* Biपंचांगask indicating in use pools */
	DECLARE_BITMAP(fwd_biपंचांगask, IXGBE_MAX_MACVLANS + 1);

#घोषणा IXGBE_MAX_LINK_HANDLE 10
	काष्ठा ixgbe_jump_table *jump_tables[IXGBE_MAX_LINK_HANDLE];
	अचिन्हित दीर्घ tables;

/* maximum number of RETA entries among all devices supported by ixgbe
 * driver: currently it's x550 device in non-SRIOV mode
 */
#घोषणा IXGBE_MAX_RETA_ENTRIES 512
	u8 rss_indir_tbl[IXGBE_MAX_RETA_ENTRIES];

#घोषणा IXGBE_RSS_KEY_SIZE     40  /* size of RSS Hash Key in bytes */
	u32 *rss_key;

#अगर_घोषित CONFIG_IXGBE_IPSEC
	काष्ठा ixgbe_ipsec *ipsec;
#पूर्ण_अगर /* CONFIG_IXGBE_IPSEC */
पूर्ण;

अटल अंतरभूत u8 ixgbe_max_rss_indices(काष्ठा ixgbe_adapter *adapter)
अणु
	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82598EB:
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
		वापस IXGBE_MAX_RSS_INDICES;
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		वापस IXGBE_MAX_RSS_INDICES_X550;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा ixgbe_fdir_filter अणु
	काष्ठा hlist_node fdir_node;
	जोड़ ixgbe_atr_input filter;
	u16 sw_idx;
	u64 action;
पूर्ण;

क्रमागत ixgbe_state_t अणु
	__IXGBE_TESTING,
	__IXGBE_RESETTING,
	__IXGBE_DOWN,
	__IXGBE_DISABLED,
	__IXGBE_REMOVING,
	__IXGBE_SERVICE_SCHED,
	__IXGBE_SERVICE_INITED,
	__IXGBE_IN_SFP_INIT,
	__IXGBE_PTP_RUNNING,
	__IXGBE_PTP_TX_IN_PROGRESS,
	__IXGBE_RESET_REQUESTED,
पूर्ण;

काष्ठा ixgbe_cb अणु
	जोड़ अणु				/* Union defining head/tail partner */
		काष्ठा sk_buff *head;
		काष्ठा sk_buff *tail;
	पूर्ण;
	dma_addr_t dma;
	u16 append_cnt;
	bool page_released;
पूर्ण;
#घोषणा IXGBE_CB(skb) ((काष्ठा ixgbe_cb *)(skb)->cb)

क्रमागत ixgbe_boards अणु
	board_82598,
	board_82599,
	board_X540,
	board_X550,
	board_X550EM_x,
	board_x550em_x_fw,
	board_x550em_a,
	board_x550em_a_fw,
पूर्ण;

बाह्य स्थिर काष्ठा ixgbe_info ixgbe_82598_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_82599_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_X540_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_X550_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_X550EM_x_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_x550em_x_fw_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_x550em_a_info;
बाह्य स्थिर काष्ठा ixgbe_info ixgbe_x550em_a_fw_info;
#अगर_घोषित CONFIG_IXGBE_DCB
बाह्य स्थिर काष्ठा dcbnl_rtnl_ops ixgbe_dcbnl_ops;
#पूर्ण_अगर

बाह्य अक्षर ixgbe_driver_name[];
#अगर_घोषित IXGBE_FCOE
बाह्य अक्षर ixgbe_शेष_device_descr[];
#पूर्ण_अगर /* IXGBE_FCOE */

पूर्णांक ixgbe_खोलो(काष्ठा net_device *netdev);
पूर्णांक ixgbe_बंद(काष्ठा net_device *netdev);
व्योम ixgbe_up(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_करोwn(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_reinit_locked(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_reset(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक ixgbe_setup_rx_resources(काष्ठा ixgbe_adapter *, काष्ठा ixgbe_ring *);
पूर्णांक ixgbe_setup_tx_resources(काष्ठा ixgbe_ring *);
व्योम ixgbe_मुक्त_rx_resources(काष्ठा ixgbe_ring *);
व्योम ixgbe_मुक्त_tx_resources(काष्ठा ixgbe_ring *);
व्योम ixgbe_configure_rx_ring(काष्ठा ixgbe_adapter *, काष्ठा ixgbe_ring *);
व्योम ixgbe_configure_tx_ring(काष्ठा ixgbe_adapter *, काष्ठा ixgbe_ring *);
व्योम ixgbe_disable_rx(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_disable_tx(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_update_stats(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_init_पूर्णांकerrupt_scheme(काष्ठा ixgbe_adapter *adapter);
bool ixgbe_wol_supported(काष्ठा ixgbe_adapter *adapter, u16 device_id,
			 u16 subdevice_id);
#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_full_sync_mac_table(काष्ठा ixgbe_adapter *adapter);
#पूर्ण_अगर
पूर्णांक ixgbe_add_mac_filter(काष्ठा ixgbe_adapter *adapter,
			 स्थिर u8 *addr, u16 queue);
पूर्णांक ixgbe_del_mac_filter(काष्ठा ixgbe_adapter *adapter,
			 स्थिर u8 *addr, u16 queue);
व्योम ixgbe_update_pf_promisc_vlvf(काष्ठा ixgbe_adapter *adapter, u32 vid);
व्योम ixgbe_clear_पूर्णांकerrupt_scheme(काष्ठा ixgbe_adapter *adapter);
netdev_tx_t ixgbe_xmit_frame_ring(काष्ठा sk_buff *, काष्ठा ixgbe_adapter *,
				  काष्ठा ixgbe_ring *);
व्योम ixgbe_unmap_and_मुक्त_tx_resource(काष्ठा ixgbe_ring *,
				      काष्ठा ixgbe_tx_buffer *);
व्योम ixgbe_alloc_rx_buffers(काष्ठा ixgbe_ring *, u16);
व्योम ixgbe_ग_लिखो_eitr(काष्ठा ixgbe_q_vector *);
पूर्णांक ixgbe_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ethtool_ioctl(काष्ठा अगरreq *अगरr);
s32 ixgbe_reinit_fdir_tables_82599(काष्ठा ixgbe_hw *hw);
s32 ixgbe_init_fdir_signature_82599(काष्ठा ixgbe_hw *hw, u32 fdirctrl);
s32 ixgbe_init_fdir_perfect_82599(काष्ठा ixgbe_hw *hw, u32 fdirctrl);
s32 ixgbe_fdir_add_signature_filter_82599(काष्ठा ixgbe_hw *hw,
					  जोड़ ixgbe_atr_hash_dword input,
					  जोड़ ixgbe_atr_hash_dword common,
					  u8 queue);
s32 ixgbe_fdir_set_input_mask_82599(काष्ठा ixgbe_hw *hw,
				    जोड़ ixgbe_atr_input *input_mask);
s32 ixgbe_fdir_ग_लिखो_perfect_filter_82599(काष्ठा ixgbe_hw *hw,
					  जोड़ ixgbe_atr_input *input,
					  u16 soft_id, u8 queue);
s32 ixgbe_fdir_erase_perfect_filter_82599(काष्ठा ixgbe_hw *hw,
					  जोड़ ixgbe_atr_input *input,
					  u16 soft_id);
व्योम ixgbe_atr_compute_perfect_hash_82599(जोड़ ixgbe_atr_input *input,
					  जोड़ ixgbe_atr_input *mask);
पूर्णांक ixgbe_update_ethtool_fdir_entry(काष्ठा ixgbe_adapter *adapter,
				    काष्ठा ixgbe_fdir_filter *input,
				    u16 sw_idx);
व्योम ixgbe_set_rx_mode(काष्ठा net_device *netdev);
#अगर_घोषित CONFIG_IXGBE_DCB
व्योम ixgbe_set_rx_drop_en(काष्ठा ixgbe_adapter *adapter);
#पूर्ण_अगर
पूर्णांक ixgbe_setup_tc(काष्ठा net_device *dev, u8 tc);
व्योम ixgbe_tx_ctxtdesc(काष्ठा ixgbe_ring *, u32, u32, u32, u32);
व्योम ixgbe_करो_reset(काष्ठा net_device *netdev);
#अगर_घोषित CONFIG_IXGBE_HWMON
व्योम ixgbe_sysfs_निकास(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_sysfs_init(काष्ठा ixgbe_adapter *adapter);
#पूर्ण_अगर /* CONFIG_IXGBE_HWMON */
#अगर_घोषित IXGBE_FCOE
व्योम ixgbe_configure_fcoe(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_fso(काष्ठा ixgbe_ring *tx_ring, काष्ठा ixgbe_tx_buffer *first,
	      u8 *hdr_len);
पूर्णांक ixgbe_fcoe_ddp(काष्ठा ixgbe_adapter *adapter,
		   जोड़ ixgbe_adv_rx_desc *rx_desc, काष्ठा sk_buff *skb);
पूर्णांक ixgbe_fcoe_ddp_get(काष्ठा net_device *netdev, u16 xid,
		       काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc);
पूर्णांक ixgbe_fcoe_ddp_target(काष्ठा net_device *netdev, u16 xid,
			  काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc);
पूर्णांक ixgbe_fcoe_ddp_put(काष्ठा net_device *netdev, u16 xid);
पूर्णांक ixgbe_setup_fcoe_ddp_resources(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_मुक्त_fcoe_ddp_resources(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_fcoe_enable(काष्ठा net_device *netdev);
पूर्णांक ixgbe_fcoe_disable(काष्ठा net_device *netdev);
#अगर_घोषित CONFIG_IXGBE_DCB
u8 ixgbe_fcoe_getapp(काष्ठा ixgbe_adapter *adapter);
u8 ixgbe_fcoe_setapp(काष्ठा ixgbe_adapter *adapter, u8 up);
#पूर्ण_अगर /* CONFIG_IXGBE_DCB */
पूर्णांक ixgbe_fcoe_get_wwn(काष्ठा net_device *netdev, u64 *wwn, पूर्णांक type);
पूर्णांक ixgbe_fcoe_get_hbainfo(काष्ठा net_device *netdev,
			   काष्ठा netdev_fcoe_hbainfo *info);
u8 ixgbe_fcoe_get_tc(काष्ठा ixgbe_adapter *adapter);
#पूर्ण_अगर /* IXGBE_FCOE */
#अगर_घोषित CONFIG_DEBUG_FS
व्योम ixgbe_dbg_adapter_init(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_dbg_adapter_निकास(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_dbg_init(व्योम);
व्योम ixgbe_dbg_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ixgbe_dbg_adapter_init(काष्ठा ixgbe_adapter *adapter) अणुपूर्ण
अटल अंतरभूत व्योम ixgbe_dbg_adapter_निकास(काष्ठा ixgbe_adapter *adapter) अणुपूर्ण
अटल अंतरभूत व्योम ixgbe_dbg_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम ixgbe_dbg_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
अटल अंतरभूत काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा ixgbe_ring *ring)
अणु
	वापस netdev_get_tx_queue(ring->netdev, ring->queue_index);
पूर्ण

व्योम ixgbe_ptp_init(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_suspend(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_stop(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_overflow_check(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_rx_hang(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_tx_hang(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_rx_pktstamp(काष्ठा ixgbe_q_vector *, काष्ठा sk_buff *);
व्योम ixgbe_ptp_rx_rgtstamp(काष्ठा ixgbe_q_vector *, काष्ठा sk_buff *skb);
अटल अंतरभूत व्योम ixgbe_ptp_rx_hwtstamp(काष्ठा ixgbe_ring *rx_ring,
					 जोड़ ixgbe_adv_rx_desc *rx_desc,
					 काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_TSIP))) अणु
		ixgbe_ptp_rx_pktstamp(rx_ring->q_vector, skb);
		वापस;
	पूर्ण

	अगर (unlikely(!ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_STAT_TS)))
		वापस;

	ixgbe_ptp_rx_rgtstamp(rx_ring->q_vector, skb);

	/* Update the last_rx_बारtamp समयr in order to enable watchकरोg check
	 * क्रम error हाल of latched बारtamp on a dropped packet.
	 */
	rx_ring->last_rx_बारtamp = jअगरfies;
पूर्ण

पूर्णांक ixgbe_ptp_set_ts_config(काष्ठा ixgbe_adapter *adapter, काष्ठा अगरreq *अगरr);
पूर्णांक ixgbe_ptp_get_ts_config(काष्ठा ixgbe_adapter *adapter, काष्ठा अगरreq *अगरr);
व्योम ixgbe_ptp_start_cyclecounter(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_reset(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ptp_check_pps_event(काष्ठा ixgbe_adapter *adapter);
#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_sriov_reinit(काष्ठा ixgbe_adapter *adapter);
#पूर्ण_अगर

netdev_tx_t ixgbe_xmit_frame_ring(काष्ठा sk_buff *skb,
				  काष्ठा ixgbe_adapter *adapter,
				  काष्ठा ixgbe_ring *tx_ring);
u32 ixgbe_rss_indir_tbl_entries(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_store_key(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_store_reta(काष्ठा ixgbe_adapter *adapter);
s32 ixgbe_negotiate_fc(काष्ठा ixgbe_hw *hw, u32 adv_reg, u32 lp_reg,
		       u32 adv_sym, u32 adv_यंत्र, u32 lp_sym, u32 lp_यंत्र);
#अगर_घोषित CONFIG_IXGBE_IPSEC
व्योम ixgbe_init_ipsec_offload(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_stop_ipsec_offload(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ipsec_restore(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ipsec_rx(काष्ठा ixgbe_ring *rx_ring,
		    जोड़ ixgbe_adv_rx_desc *rx_desc,
		    काष्ठा sk_buff *skb);
पूर्णांक ixgbe_ipsec_tx(काष्ठा ixgbe_ring *tx_ring, काष्ठा ixgbe_tx_buffer *first,
		   काष्ठा ixgbe_ipsec_tx_data *itd);
व्योम ixgbe_ipsec_vf_clear(काष्ठा ixgbe_adapter *adapter, u32 vf);
पूर्णांक ixgbe_ipsec_vf_add_sa(काष्ठा ixgbe_adapter *adapter, u32 *mbuf, u32 vf);
पूर्णांक ixgbe_ipsec_vf_del_sa(काष्ठा ixgbe_adapter *adapter, u32 *mbuf, u32 vf);
#अन्यथा
अटल अंतरभूत व्योम ixgbe_init_ipsec_offload(काष्ठा ixgbe_adapter *adapter) अणु पूर्ण
अटल अंतरभूत व्योम ixgbe_stop_ipsec_offload(काष्ठा ixgbe_adapter *adapter) अणु पूर्ण
अटल अंतरभूत व्योम ixgbe_ipsec_restore(काष्ठा ixgbe_adapter *adapter) अणु पूर्ण
अटल अंतरभूत व्योम ixgbe_ipsec_rx(काष्ठा ixgbe_ring *rx_ring,
				  जोड़ ixgbe_adv_rx_desc *rx_desc,
				  काष्ठा sk_buff *skb) अणु पूर्ण
अटल अंतरभूत पूर्णांक ixgbe_ipsec_tx(काष्ठा ixgbe_ring *tx_ring,
				 काष्ठा ixgbe_tx_buffer *first,
				 काष्ठा ixgbe_ipsec_tx_data *itd) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ixgbe_ipsec_vf_clear(काष्ठा ixgbe_adapter *adapter,
					u32 vf) अणु पूर्ण
अटल अंतरभूत पूर्णांक ixgbe_ipsec_vf_add_sa(काष्ठा ixgbe_adapter *adapter,
					u32 *mbuf, u32 vf) अणु वापस -EACCES; पूर्ण
अटल अंतरभूत पूर्णांक ixgbe_ipsec_vf_del_sa(काष्ठा ixgbe_adapter *adapter,
					u32 *mbuf, u32 vf) अणु वापस -EACCES; पूर्ण
#पूर्ण_अगर /* CONFIG_IXGBE_IPSEC */

अटल अंतरभूत bool ixgbe_enabled_xdp_adapter(काष्ठा ixgbe_adapter *adapter)
अणु
	वापस !!adapter->xdp_prog;
पूर्ण

#पूर्ण_अगर /* _IXGBE_H_ */
