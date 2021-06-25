<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBEVF_H_
#घोषणा _IXGBEVF_H_

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <net/xdp.h>

#समावेश "vf.h"
#समावेश "ipsec.h"

#घोषणा IXGBE_MAX_TXD_PWR	14
#घोषणा IXGBE_MAX_DATA_PER_TXD	BIT(IXGBE_MAX_TXD_PWR)

/* Tx Descriptors needed, worst हाल */
#घोषणा TXD_USE_COUNT(S) DIV_ROUND_UP((S), IXGBE_MAX_DATA_PER_TXD)
#घोषणा DESC_NEEDED (MAX_SKB_FRAGS + 4)

/* wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा ixgbevf_tx_buffer अणु
	जोड़ ixgbe_adv_tx_desc *next_to_watch;
	अचिन्हित दीर्घ समय_stamp;
	जोड़ अणु
		काष्ठा sk_buff *skb;
		/* XDP uses address ptr on irq_clean */
		व्योम *data;
	पूर्ण;
	अचिन्हित पूर्णांक bytecount;
	अचिन्हित लघु gso_segs;
	__be16 protocol;
	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
	u32 tx_flags;
पूर्ण;

काष्ठा ixgbevf_rx_buffer अणु
	dma_addr_t dma;
	काष्ठा page *page;
#अगर (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
#अन्यथा
	__u16 page_offset;
#पूर्ण_अगर
	__u16 pagecnt_bias;
पूर्ण;

काष्ठा ixgbevf_stats अणु
	u64 packets;
	u64 bytes;
पूर्ण;

काष्ठा ixgbevf_tx_queue_stats अणु
	u64 restart_queue;
	u64 tx_busy;
	u64 tx_करोne_old;
पूर्ण;

काष्ठा ixgbevf_rx_queue_stats अणु
	u64 alloc_rx_page_failed;
	u64 alloc_rx_buff_failed;
	u64 alloc_rx_page;
	u64 csum_err;
पूर्ण;

क्रमागत ixgbevf_ring_state_t अणु
	__IXGBEVF_RX_3K_BUFFER,
	__IXGBEVF_RX_BUILD_SKB_ENABLED,
	__IXGBEVF_TX_DETECT_HANG,
	__IXGBEVF_HANG_CHECK_ARMED,
	__IXGBEVF_TX_XDP_RING,
	__IXGBEVF_TX_XDP_RING_PRIMED,
पूर्ण;

#घोषणा ring_is_xdp(ring) \
		test_bit(__IXGBEVF_TX_XDP_RING, &(ring)->state)
#घोषणा set_ring_xdp(ring) \
		set_bit(__IXGBEVF_TX_XDP_RING, &(ring)->state)
#घोषणा clear_ring_xdp(ring) \
		clear_bit(__IXGBEVF_TX_XDP_RING, &(ring)->state)

काष्ठा ixgbevf_ring अणु
	काष्ठा ixgbevf_ring *next;
	काष्ठा ixgbevf_q_vector *q_vector;	/* backpoपूर्णांकer to q_vector */
	काष्ठा net_device *netdev;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा device *dev;
	व्योम *desc;			/* descriptor ring memory */
	dma_addr_t dma;			/* phys. address of descriptor ring */
	अचिन्हित पूर्णांक size;		/* length in bytes */
	u16 count;			/* amount of descriptors */
	u16 next_to_use;
	u16 next_to_clean;
	u16 next_to_alloc;

	जोड़ अणु
		काष्ठा ixgbevf_tx_buffer *tx_buffer_info;
		काष्ठा ixgbevf_rx_buffer *rx_buffer_info;
	पूर्ण;
	अचिन्हित दीर्घ state;
	काष्ठा ixgbevf_stats stats;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		काष्ठा ixgbevf_tx_queue_stats tx_stats;
		काष्ठा ixgbevf_rx_queue_stats rx_stats;
	पूर्ण;
	काष्ठा xdp_rxq_info xdp_rxq;
	u64 hw_csum_rx_error;
	u8 __iomem *tail;
	काष्ठा sk_buff *skb;

	/* holds the special value that माला_लो the hardware रेजिस्टर offset
	 * associated with this ring, which is dअगरferent क्रम DCB and RSS modes
	 */
	u16 reg_idx;
	पूर्णांक queue_index; /* needed क्रम multiqueue queue management */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IXGBEVF_RX_BUFFER_WRITE	16	/* Must be घातer of 2 */

#घोषणा MAX_RX_QUEUES IXGBE_VF_MAX_RX_QUEUES
#घोषणा MAX_TX_QUEUES IXGBE_VF_MAX_TX_QUEUES
#घोषणा MAX_XDP_QUEUES IXGBE_VF_MAX_TX_QUEUES
#घोषणा IXGBEVF_MAX_RSS_QUEUES		2
#घोषणा IXGBEVF_82599_RETA_SIZE		128	/* 128 entries */
#घोषणा IXGBEVF_X550_VFRETA_SIZE	64	/* 64 entries */
#घोषणा IXGBEVF_RSS_HASH_KEY_SIZE	40
#घोषणा IXGBEVF_VFRSSRK_REGS		10	/* 10 रेजिस्टरs क्रम RSS key */

#घोषणा IXGBEVF_DEFAULT_TXD	1024
#घोषणा IXGBEVF_DEFAULT_RXD	512
#घोषणा IXGBEVF_MAX_TXD		4096
#घोषणा IXGBEVF_MIN_TXD		64
#घोषणा IXGBEVF_MAX_RXD		4096
#घोषणा IXGBEVF_MIN_RXD		64

/* Supported Rx Buffer Sizes */
#घोषणा IXGBEVF_RXBUFFER_256	256    /* Used क्रम packet split */
#घोषणा IXGBEVF_RXBUFFER_2048	2048
#घोषणा IXGBEVF_RXBUFFER_3072	3072

#घोषणा IXGBEVF_RX_HDR_SIZE	IXGBEVF_RXBUFFER_256

#घोषणा MAXIMUM_ETHERNET_VLAN_SIZE (VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)

#घोषणा IXGBEVF_SKB_PAD		(NET_SKB_PAD + NET_IP_ALIGN)
#अगर (PAGE_SIZE < 8192)
#घोषणा IXGBEVF_MAX_FRAME_BUILD_SKB \
	(SKB_WITH_OVERHEAD(IXGBEVF_RXBUFFER_2048) - IXGBEVF_SKB_PAD)
#अन्यथा
#घोषणा IXGBEVF_MAX_FRAME_BUILD_SKB	IXGBEVF_RXBUFFER_2048
#पूर्ण_अगर

#घोषणा IXGBE_TX_FLAGS_CSUM		BIT(0)
#घोषणा IXGBE_TX_FLAGS_VLAN		BIT(1)
#घोषणा IXGBE_TX_FLAGS_TSO		BIT(2)
#घोषणा IXGBE_TX_FLAGS_IPV4		BIT(3)
#घोषणा IXGBE_TX_FLAGS_IPSEC		BIT(4)
#घोषणा IXGBE_TX_FLAGS_VLAN_MASK	0xffff0000
#घोषणा IXGBE_TX_FLAGS_VLAN_PRIO_MASK	0x0000e000
#घोषणा IXGBE_TX_FLAGS_VLAN_SHIFT	16

#घोषणा ring_uses_large_buffer(ring) \
	test_bit(__IXGBEVF_RX_3K_BUFFER, &(ring)->state)
#घोषणा set_ring_uses_large_buffer(ring) \
	set_bit(__IXGBEVF_RX_3K_BUFFER, &(ring)->state)
#घोषणा clear_ring_uses_large_buffer(ring) \
	clear_bit(__IXGBEVF_RX_3K_BUFFER, &(ring)->state)

#घोषणा ring_uses_build_skb(ring) \
	test_bit(__IXGBEVF_RX_BUILD_SKB_ENABLED, &(ring)->state)
#घोषणा set_ring_build_skb_enabled(ring) \
	set_bit(__IXGBEVF_RX_BUILD_SKB_ENABLED, &(ring)->state)
#घोषणा clear_ring_build_skb_enabled(ring) \
	clear_bit(__IXGBEVF_RX_BUILD_SKB_ENABLED, &(ring)->state)

अटल अंतरभूत अचिन्हित पूर्णांक ixgbevf_rx_bufsz(काष्ठा ixgbevf_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_large_buffer(ring))
		वापस IXGBEVF_RXBUFFER_3072;

	अगर (ring_uses_build_skb(ring))
		वापस IXGBEVF_MAX_FRAME_BUILD_SKB;
#पूर्ण_अगर
	वापस IXGBEVF_RXBUFFER_2048;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ixgbevf_rx_pg_order(काष्ठा ixgbevf_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring_uses_large_buffer(ring))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा ixgbevf_rx_pg_size(_ring) (PAGE_SIZE << ixgbevf_rx_pg_order(_ring))

#घोषणा check_क्रम_tx_hang(ring) \
	test_bit(__IXGBEVF_TX_DETECT_HANG, &(ring)->state)
#घोषणा set_check_क्रम_tx_hang(ring) \
	set_bit(__IXGBEVF_TX_DETECT_HANG, &(ring)->state)
#घोषणा clear_check_क्रम_tx_hang(ring) \
	clear_bit(__IXGBEVF_TX_DETECT_HANG, &(ring)->state)

काष्ठा ixgbevf_ring_container अणु
	काष्ठा ixgbevf_ring *ring;	/* poपूर्णांकer to linked list of rings */
	अचिन्हित पूर्णांक total_bytes;	/* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;	/* total packets processed this पूर्णांक */
	u8 count;			/* total number of rings in vector */
	u8 itr;				/* current ITR setting क्रम ring */
पूर्ण;

/* iterator क्रम handling rings in ring container */
#घोषणा ixgbevf_क्रम_each_ring(pos, head) \
	क्रम (pos = (head).ring; pos != शून्य; pos = pos->next)

/* MAX_MSIX_Q_VECTORS of these are allocated,
 * but we only use one per queue-specअगरic vector.
 */
काष्ठा ixgbevf_q_vector अणु
	काष्ठा ixgbevf_adapter *adapter;
	/* index of q_vector within array, also used क्रम finding the bit in
	 * EICR and मित्रs that represents the vector क्रम this ring
	 */
	u16 v_idx;
	u16 itr; /* Interrupt throttle rate written to EITR */
	काष्ठा napi_काष्ठा napi;
	काष्ठा ixgbevf_ring_container rx, tx;
	काष्ठा rcu_head rcu;    /* to aव्योम race with update stats on मुक्त */
	अक्षर name[IFNAMSIZ + 9];

	/* क्रम dynamic allocation of rings associated with this q_vector */
	काष्ठा ixgbevf_ring ring[0] ____cacheline_पूर्णांकernodealigned_in_smp;
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित पूर्णांक state;
#घोषणा IXGBEVF_QV_STATE_IDLE		0
#घोषणा IXGBEVF_QV_STATE_NAPI		1    /* NAPI owns this QV */
#घोषणा IXGBEVF_QV_STATE_POLL		2    /* poll owns this QV */
#घोषणा IXGBEVF_QV_STATE_DISABLED	4    /* QV is disabled */
#घोषणा IXGBEVF_QV_OWNED	(IXGBEVF_QV_STATE_NAPI | IXGBEVF_QV_STATE_POLL)
#घोषणा IXGBEVF_QV_LOCKED	(IXGBEVF_QV_OWNED | IXGBEVF_QV_STATE_DISABLED)
#घोषणा IXGBEVF_QV_STATE_NAPI_YIELD	8    /* NAPI yielded this QV */
#घोषणा IXGBEVF_QV_STATE_POLL_YIELD	16   /* poll yielded this QV */
#घोषणा IXGBEVF_QV_YIELD	(IXGBEVF_QV_STATE_NAPI_YIELD | \
				 IXGBEVF_QV_STATE_POLL_YIELD)
#घोषणा IXGBEVF_QV_USER_PEND	(IXGBEVF_QV_STATE_POLL | \
				 IXGBEVF_QV_STATE_POLL_YIELD)
	spinlock_t lock;
#पूर्ण_अगर /* CONFIG_NET_RX_BUSY_POLL */
पूर्ण;

/* microsecond values क्रम various ITR rates shअगरted by 2 to fit itr रेजिस्टर
 * with the first 3 bits reserved 0
 */
#घोषणा IXGBE_MIN_RSC_ITR	24
#घोषणा IXGBE_100K_ITR		40
#घोषणा IXGBE_20K_ITR		200
#घोषणा IXGBE_12K_ITR		336

/* Helper macros to चयन between पूर्णांकs/sec and what the रेजिस्टर uses.
 * And yes, it's the same math going both ways.  The lowest value
 * supported by all of the ixgbe hardware is 8.
 */
#घोषणा EITR_INTS_PER_SEC_TO_REG(_eitr) \
	((_eitr) ? (1000000000 / ((_eitr) * 256)) : 8)
#घोषणा EITR_REG_TO_INTS_PER_SEC EITR_INTS_PER_SEC_TO_REG

/* ixgbevf_test_staterr - tests bits in Rx descriptor status and error fields */
अटल अंतरभूत __le32 ixgbevf_test_staterr(जोड़ ixgbe_adv_rx_desc *rx_desc,
					  स्थिर u32 stat_err_bits)
अणु
	वापस rx_desc->wb.upper.status_error & cpu_to_le32(stat_err_bits);
पूर्ण

अटल अंतरभूत u16 ixgbevf_desc_unused(काष्ठा ixgbevf_ring *ring)
अणु
	u16 ntc = ring->next_to_clean;
	u16 ntu = ring->next_to_use;

	वापस ((ntc > ntu) ? 0 : ring->count) + ntc - ntu - 1;
पूर्ण

अटल अंतरभूत व्योम ixgbevf_ग_लिखो_tail(काष्ठा ixgbevf_ring *ring, u32 value)
अणु
	ग_लिखोl(value, ring->tail);
पूर्ण

#घोषणा IXGBEVF_RX_DESC(R, i)	\
	(&(((जोड़ ixgbe_adv_rx_desc *)((R)->desc))[i]))
#घोषणा IXGBEVF_TX_DESC(R, i)	\
	(&(((जोड़ ixgbe_adv_tx_desc *)((R)->desc))[i]))
#घोषणा IXGBEVF_TX_CTXTDESC(R, i)	\
	(&(((काष्ठा ixgbe_adv_tx_context_desc *)((R)->desc))[i]))

#घोषणा IXGBE_MAX_JUMBO_FRAME_SIZE	9728 /* Maximum Supported Size 9.5KB */

#घोषणा OTHER_VECTOR	1
#घोषणा NON_Q_VECTORS	(OTHER_VECTOR)

#घोषणा MAX_MSIX_Q_VECTORS	2

#घोषणा MIN_MSIX_Q_VECTORS	1
#घोषणा MIN_MSIX_COUNT		(MIN_MSIX_Q_VECTORS + NON_Q_VECTORS)

#घोषणा IXGBEVF_RX_DMA_ATTR \
	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

/* board specअगरic निजी data काष्ठाure */
काष्ठा ixgbevf_adapter अणु
	/* this field must be first, see ixgbevf_process_skb_fields */
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	काष्ठा ixgbevf_q_vector *q_vector[MAX_MSIX_Q_VECTORS];

	/* Interrupt Throttle Rate */
	u16 rx_itr_setting;
	u16 tx_itr_setting;

	/* पूर्णांकerrupt masks */
	u32 eims_enable_mask;
	u32 eims_other;

	/* XDP */
	पूर्णांक num_xdp_queues;
	काष्ठा ixgbevf_ring *xdp_ring[MAX_XDP_QUEUES];

	/* TX */
	पूर्णांक num_tx_queues;
	काष्ठा ixgbevf_ring *tx_ring[MAX_TX_QUEUES]; /* One per active queue */
	u64 restart_queue;
	u32 tx_समयout_count;
	u64 tx_ipsec;

	/* RX */
	पूर्णांक num_rx_queues;
	काष्ठा ixgbevf_ring *rx_ring[MAX_TX_QUEUES]; /* One per active queue */
	u64 hw_csum_rx_error;
	u64 hw_rx_no_dma_resources;
	पूर्णांक num_msix_vectors;
	u64 alloc_rx_page_failed;
	u64 alloc_rx_buff_failed;
	u64 alloc_rx_page;
	u64 rx_ipsec;

	काष्ठा msix_entry *msix_entries;

	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा pci_dev *pdev;

	/* काष्ठाs defined in ixgbe_vf.h */
	काष्ठा ixgbe_hw hw;
	u16 msg_enable;
	/* Interrupt Throttle Rate */
	u32 eitr_param;

	काष्ठा ixgbevf_hw_stats stats;

	अचिन्हित दीर्घ state;
	u64 tx_busy;
	अचिन्हित पूर्णांक tx_ring_count;
	अचिन्हित पूर्णांक xdp_ring_count;
	अचिन्हित पूर्णांक rx_ring_count;

	u8 __iomem *io_addr; /* Mainly क्रम iounmap use */
	u32 link_speed;
	bool link_up;

	काष्ठा समयr_list service_समयr;
	काष्ठा work_काष्ठा service_task;

	spinlock_t mbx_lock;
	अचिन्हित दीर्घ last_reset;

	u32 *rss_key;
	u8 rss_indir_tbl[IXGBEVF_X550_VFRETA_SIZE];
	u32 flags;
#घोषणा IXGBEVF_FLAGS_LEGACY_RX		BIT(1)

#अगर_घोषित CONFIG_XFRM
	काष्ठा ixgbevf_ipsec *ipsec;
#पूर्ण_अगर /* CONFIG_XFRM */
पूर्ण;

क्रमागत ixbgevf_state_t अणु
	__IXGBEVF_TESTING,
	__IXGBEVF_RESETTING,
	__IXGBEVF_DOWN,
	__IXGBEVF_DISABLED,
	__IXGBEVF_REMOVING,
	__IXGBEVF_SERVICE_SCHED,
	__IXGBEVF_SERVICE_INITED,
	__IXGBEVF_RESET_REQUESTED,
	__IXGBEVF_QUEUE_RESET_REQUESTED,
पूर्ण;

क्रमागत ixgbevf_boards अणु
	board_82599_vf,
	board_82599_vf_hv,
	board_X540_vf,
	board_X540_vf_hv,
	board_X550_vf,
	board_X550_vf_hv,
	board_X550EM_x_vf,
	board_X550EM_x_vf_hv,
	board_x550em_a_vf,
पूर्ण;

क्रमागत ixgbevf_xcast_modes अणु
	IXGBEVF_XCAST_MODE_NONE = 0,
	IXGBEVF_XCAST_MODE_MULTI,
	IXGBEVF_XCAST_MODE_ALLMULTI,
	IXGBEVF_XCAST_MODE_PROMISC,
पूर्ण;

बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_82599_vf_info;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_X540_vf_info;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_X550_vf_info;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_X550EM_x_vf_info;
बाह्य स्थिर काष्ठा ixgbe_mbx_operations ixgbevf_mbx_ops;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_x550em_a_vf_info;

बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_82599_vf_hv_info;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_X540_vf_hv_info;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_X550_vf_hv_info;
बाह्य स्थिर काष्ठा ixgbevf_info ixgbevf_X550EM_x_vf_hv_info;
बाह्य स्थिर काष्ठा ixgbe_mbx_operations ixgbevf_hv_mbx_ops;

/* needed by ethtool.c */
बाह्य स्थिर अक्षर ixgbevf_driver_name[];

पूर्णांक ixgbevf_खोलो(काष्ठा net_device *netdev);
पूर्णांक ixgbevf_बंद(काष्ठा net_device *netdev);
व्योम ixgbevf_up(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_करोwn(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_reinit_locked(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_reset(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक ixgbevf_setup_rx_resources(काष्ठा ixgbevf_adapter *adapter,
			       काष्ठा ixgbevf_ring *rx_ring);
पूर्णांक ixgbevf_setup_tx_resources(काष्ठा ixgbevf_ring *);
व्योम ixgbevf_मुक्त_rx_resources(काष्ठा ixgbevf_ring *);
व्योम ixgbevf_मुक्त_tx_resources(काष्ठा ixgbevf_ring *);
व्योम ixgbevf_update_stats(काष्ठा ixgbevf_adapter *adapter);
पूर्णांक ethtool_ioctl(काष्ठा अगरreq *अगरr);

बाह्य व्योम ixgbevf_ग_लिखो_eitr(काष्ठा ixgbevf_q_vector *q_vector);

#अगर_घोषित CONFIG_IXGBEVF_IPSEC
व्योम ixgbevf_init_ipsec_offload(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_stop_ipsec_offload(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_ipsec_restore(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbevf_ipsec_rx(काष्ठा ixgbevf_ring *rx_ring,
		      जोड़ ixgbe_adv_rx_desc *rx_desc,
		      काष्ठा sk_buff *skb);
पूर्णांक ixgbevf_ipsec_tx(काष्ठा ixgbevf_ring *tx_ring,
		     काष्ठा ixgbevf_tx_buffer *first,
		     काष्ठा ixgbevf_ipsec_tx_data *itd);
#अन्यथा
अटल अंतरभूत व्योम ixgbevf_init_ipsec_offload(काष्ठा ixgbevf_adapter *adapter)
अणु पूर्ण
अटल अंतरभूत व्योम ixgbevf_stop_ipsec_offload(काष्ठा ixgbevf_adapter *adapter)
अणु पूर्ण
अटल अंतरभूत व्योम ixgbevf_ipsec_restore(काष्ठा ixgbevf_adapter *adapter) अणु पूर्ण
अटल अंतरभूत व्योम ixgbevf_ipsec_rx(काष्ठा ixgbevf_ring *rx_ring,
				    जोड़ ixgbe_adv_rx_desc *rx_desc,
				    काष्ठा sk_buff *skb) अणु पूर्ण
अटल अंतरभूत पूर्णांक ixgbevf_ipsec_tx(काष्ठा ixgbevf_ring *tx_ring,
				   काष्ठा ixgbevf_tx_buffer *first,
				   काष्ठा ixgbevf_ipsec_tx_data *itd)
अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_IXGBEVF_IPSEC */

व्योम ixgbe_napi_add_all(काष्ठा ixgbevf_adapter *adapter);
व्योम ixgbe_napi_del_all(काष्ठा ixgbevf_adapter *adapter);

#घोषणा ixgbevf_hw_to_netdev(hw) \
	(((काष्ठा ixgbevf_adapter *)(hw)->back)->netdev)

#घोषणा hw_dbg(hw, क्रमmat, arg...) \
	netdev_dbg(ixgbevf_hw_to_netdev(hw), क्रमmat, ## arg)
#पूर्ण_अगर /* _IXGBEVF_H_ */
