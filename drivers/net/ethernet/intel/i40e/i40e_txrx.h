<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _I40E_TXRX_H_
#घोषणा _I40E_TXRX_H_

#समावेश <net/xdp.h>

/* Interrupt Throttling and Rate Limiting Goodies */
#घोषणा I40E_DEFAULT_IRQ_WORK      256

/* The datasheet क्रम the X710 and XL710 indicate that the maximum value क्रम
 * the ITR is 8160usec which is then called out as 0xFF0 with a 2usec
 * resolution. 8160 is 0x1FE0 when written out in hex. So instead of storing
 * the रेजिस्टर value which is भागided by 2 lets use the actual values and
 * aव्योम an excessive amount of translation.
 */
#घोषणा I40E_ITR_DYNAMIC	0x8000	/* use top bit as a flag */
#घोषणा I40E_ITR_MASK		0x1FFE	/* mask क्रम ITR रेजिस्टर value */
#घोषणा I40E_MIN_ITR		     2	/* reg uses 2 usec resolution */
#घोषणा I40E_ITR_20K		    50
#घोषणा I40E_ITR_8K		   122
#घोषणा I40E_MAX_ITR		  8160	/* maximum value as per datasheet */
#घोषणा ITR_TO_REG(setting) ((setting) & ~I40E_ITR_DYNAMIC)
#घोषणा ITR_REG_ALIGN(setting) __ALIGN_MASK(setting, ~I40E_ITR_MASK)
#घोषणा ITR_IS_DYNAMIC(setting) (!!((setting) & I40E_ITR_DYNAMIC))

#घोषणा I40E_ITR_RX_DEF		(I40E_ITR_20K | I40E_ITR_DYNAMIC)
#घोषणा I40E_ITR_TX_DEF		(I40E_ITR_20K | I40E_ITR_DYNAMIC)

/* 0x40 is the enable bit क्रम पूर्णांकerrupt rate limiting, and must be set अगर
 * the value of the rate limit is non-zero
 */
#घोषणा INTRL_ENA                  BIT(6)
#घोषणा I40E_MAX_INTRL             0x3B    /* reg uses 4 usec resolution */
#घोषणा INTRL_REG_TO_USEC(पूर्णांकrl) ((पूर्णांकrl & ~INTRL_ENA) << 2)

/**
 * i40e_पूर्णांकrl_usec_to_reg - convert पूर्णांकerrupt rate limit to रेजिस्टर
 * @पूर्णांकrl: पूर्णांकerrupt rate limit to convert
 *
 * This function converts a decimal पूर्णांकerrupt rate limit to the appropriate
 * रेजिस्टर क्रमmat expected by the firmware when setting पूर्णांकerrupt rate limit.
 */
अटल अंतरभूत u16 i40e_पूर्णांकrl_usec_to_reg(पूर्णांक पूर्णांकrl)
अणु
	अगर (पूर्णांकrl >> 2)
		वापस ((पूर्णांकrl >> 2) | INTRL_ENA);
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा I40E_QUEUE_END_OF_LIST 0x7FF

/* this क्रमागत matches hardware bits and is meant to be used by DYN_CTLN
 * रेजिस्टरs and QINT रेजिस्टरs or more generally anywhere in the manual
 * mentioning ITR_INDX, ITR_NONE cannot be used as an index 'n' पूर्णांकo any
 * रेजिस्टर but instead is a special value meaning "don't update" ITR0/1/2.
 */
क्रमागत i40e_dyn_idx_t अणु
	I40E_IDX_ITR0 = 0,
	I40E_IDX_ITR1 = 1,
	I40E_IDX_ITR2 = 2,
	I40E_ITR_NONE = 3	/* ITR_NONE must not be used as an index */
पूर्ण;

/* these are indexes पूर्णांकo ITRN रेजिस्टरs */
#घोषणा I40E_RX_ITR    I40E_IDX_ITR0
#घोषणा I40E_TX_ITR    I40E_IDX_ITR1

/* Supported RSS offloads */
#घोषणा I40E_DEFAULT_RSS_HENA ( \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_UDP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_SCTP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_TCP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_OTHER) | \
	BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV4) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_UDP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_TCP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_SCTP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_OTHER) | \
	BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV6) | \
	BIT_ULL(I40E_FILTER_PCTYPE_L2_PAYLOAD))

#घोषणा I40E_DEFAULT_RSS_HENA_EXPANDED (I40E_DEFAULT_RSS_HENA | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_UNICAST_IPV4_UDP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV4_UDP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_UNICAST_IPV6_UDP) | \
	BIT_ULL(I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV6_UDP))

#घोषणा i40e_pf_get_शेष_rss_hena(pf) \
	(((pf)->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE) ? \
	  I40E_DEFAULT_RSS_HENA_EXPANDED : I40E_DEFAULT_RSS_HENA)

/* Supported Rx Buffer Sizes (a multiple of 128) */
#घोषणा I40E_RXBUFFER_256   256
#घोषणा I40E_RXBUFFER_1536  1536  /* 128B aligned standard Ethernet frame */
#घोषणा I40E_RXBUFFER_2048  2048
#घोषणा I40E_RXBUFFER_3072  3072  /* Used क्रम large frames w/ padding */
#घोषणा I40E_MAX_RXBUFFER   9728  /* largest size क्रम single descriptor */

/* NOTE: netdev_alloc_skb reserves up to 64 bytes, NET_IP_ALIGN means we
 * reserve 2 more, and skb_shared_info adds an additional 384 bytes more,
 * this adds up to 512 bytes of extra data meaning the smallest allocation
 * we could have is 1K.
 * i.e. RXBUFFER_256 --> 960 byte skb (size-1024 slab)
 * i.e. RXBUFFER_512 --> 1216 byte skb (size-2048 slab)
 */
#घोषणा I40E_RX_HDR_SIZE I40E_RXBUFFER_256
#घोषणा I40E_PACKET_HDR_PAD (ETH_HLEN + ETH_FCS_LEN + (VLAN_HLEN * 2))
#घोषणा i40e_rx_desc i40e_16byte_rx_desc

#घोषणा I40E_RX_DMA_ATTR \
	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

/* Attempt to maximize the headroom available क्रम incoming frames.  We
 * use a 2K buffer क्रम receives and need 1536/1534 to store the data क्रम
 * the frame.  This leaves us with 512 bytes of room.  From that we need
 * to deduct the space needed क्रम the shared info and the padding needed
 * to IP align the frame.
 *
 * Note: For cache line sizes 256 or larger this value is going to end
 *	 up negative.  In these हालs we should fall back to the legacy
 *	 receive path.
 */
#अगर (PAGE_SIZE < 8192)
#घोषणा I40E_2K_TOO_SMALL_WITH_PADDING \
((NET_SKB_PAD + I40E_RXBUFFER_1536) > SKB_WITH_OVERHEAD(I40E_RXBUFFER_2048))

अटल अंतरभूत पूर्णांक i40e_compute_pad(पूर्णांक rx_buf_len)
अणु
	पूर्णांक page_size, pad_size;

	page_size = ALIGN(rx_buf_len, PAGE_SIZE / 2);
	pad_size = SKB_WITH_OVERHEAD(page_size) - rx_buf_len;

	वापस pad_size;
पूर्ण

अटल अंतरभूत पूर्णांक i40e_skb_pad(व्योम)
अणु
	पूर्णांक rx_buf_len;

	/* If a 2K buffer cannot handle a standard Ethernet frame then
	 * optimize padding क्रम a 3K buffer instead of a 1.5K buffer.
	 *
	 * For a 3K buffer we need to add enough padding to allow क्रम
	 * tailroom due to NET_IP_ALIGN possibly shअगरting us out of
	 * cache-line alignment.
	 */
	अगर (I40E_2K_TOO_SMALL_WITH_PADDING)
		rx_buf_len = I40E_RXBUFFER_3072 + SKB_DATA_ALIGN(NET_IP_ALIGN);
	अन्यथा
		rx_buf_len = I40E_RXBUFFER_1536;

	/* अगर needed make room क्रम NET_IP_ALIGN */
	rx_buf_len -= NET_IP_ALIGN;

	वापस i40e_compute_pad(rx_buf_len);
पूर्ण

#घोषणा I40E_SKB_PAD i40e_skb_pad()
#अन्यथा
#घोषणा I40E_2K_TOO_SMALL_WITH_PADDING false
#घोषणा I40E_SKB_PAD (NET_SKB_PAD + NET_IP_ALIGN)
#पूर्ण_अगर

/**
 * i40e_test_staterr - tests bits in Rx descriptor status and error fields
 * @rx_desc: poपूर्णांकer to receive descriptor (in le64 क्रमmat)
 * @stat_err_bits: value to mask
 *
 * This function करोes some fast chicanery in order to वापस the
 * value of the mask which is really only used क्रम boolean tests.
 * The status_error_len करोesn't need to be shअगरted because it begins
 * at offset zero.
 */
अटल अंतरभूत bool i40e_test_staterr(जोड़ i40e_rx_desc *rx_desc,
				     स्थिर u64 stat_err_bits)
अणु
	वापस !!(rx_desc->wb.qword1.status_error_len &
		  cpu_to_le64(stat_err_bits));
पूर्ण

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा I40E_RX_BUFFER_WRITE	32	/* Must be घातer of 2 */

#घोषणा I40E_RX_NEXT_DESC(r, i, n)		\
	करो अणु					\
		(i)++;				\
		अगर ((i) == (r)->count)		\
			i = 0;			\
		(n) = I40E_RX_DESC((r), (i));	\
	पूर्ण जबतक (0)


#घोषणा I40E_MAX_BUFFER_TXD	8
#घोषणा I40E_MIN_TX_LEN		17

/* The size limit क्रम a transmit buffer in a descriptor is (16K - 1).
 * In order to align with the पढ़ो requests we will align the value to
 * the nearest 4K which represents our maximum पढ़ो request size.
 */
#घोषणा I40E_MAX_READ_REQ_SIZE		4096
#घोषणा I40E_MAX_DATA_PER_TXD		(16 * 1024 - 1)
#घोषणा I40E_MAX_DATA_PER_TXD_ALIGNED \
	(I40E_MAX_DATA_PER_TXD & ~(I40E_MAX_READ_REQ_SIZE - 1))

/**
 * i40e_txd_use_count  - estimate the number of descriptors needed क्रम Tx
 * @size: transmit request size in bytes
 *
 * Due to hardware alignment restrictions (4K alignment), we need to
 * assume that we can have no more than 12K of data per descriptor, even
 * though each descriptor can take up to 16K - 1 bytes of aligned memory.
 * Thus, we need to भागide by 12K. But भागision is slow! Instead,
 * we decompose the operation पूर्णांकo shअगरts and one relatively cheap
 * multiply operation.
 *
 * To भागide by 12K, we first भागide by 4K, then भागide by 3:
 *     To भागide by 4K, shअगरt right by 12 bits
 *     To भागide by 3, multiply by 85, then भागide by 256
 *     (Divide by 256 is करोne by shअगरting right by 8 bits)
 * Finally, we add one to round up. Because 256 isn't an exact multiple of
 * 3, we'll underestimate near each multiple of 12K. This is actually more
 * accurate as we have 4K - 1 of wiggle room that we can fit पूर्णांकo the last
 * segment.  For our purposes this is accurate out to 1M which is orders of
 * magnitude greater than our largest possible GSO size.
 *
 * This would then be implemented as:
 *     वापस (((size >> 12) * 85) >> 8) + 1;
 *
 * Since multiplication and भागision are commutative, we can reorder
 * operations पूर्णांकo:
 *     वापस ((size * 85) >> 20) + 1;
 */
अटल अंतरभूत अचिन्हित पूर्णांक i40e_txd_use_count(अचिन्हित पूर्णांक size)
अणु
	वापस ((size * 85) >> 20) + 1;
पूर्ण

/* Tx Descriptors needed, worst हाल */
#घोषणा DESC_NEEDED (MAX_SKB_FRAGS + 6)

#घोषणा I40E_TX_FLAGS_HW_VLAN		BIT(1)
#घोषणा I40E_TX_FLAGS_SW_VLAN		BIT(2)
#घोषणा I40E_TX_FLAGS_TSO		BIT(3)
#घोषणा I40E_TX_FLAGS_IPV4		BIT(4)
#घोषणा I40E_TX_FLAGS_IPV6		BIT(5)
#घोषणा I40E_TX_FLAGS_TSYN		BIT(8)
#घोषणा I40E_TX_FLAGS_FD_SB		BIT(9)
#घोषणा I40E_TX_FLAGS_UDP_TUNNEL	BIT(10)
#घोषणा I40E_TX_FLAGS_VLAN_MASK		0xffff0000
#घोषणा I40E_TX_FLAGS_VLAN_PRIO_MASK	0xe0000000
#घोषणा I40E_TX_FLAGS_VLAN_PRIO_SHIFT	29
#घोषणा I40E_TX_FLAGS_VLAN_SHIFT	16

काष्ठा i40e_tx_buffer अणु
	काष्ठा i40e_tx_desc *next_to_watch;
	जोड़ अणु
		काष्ठा xdp_frame *xdpf;
		काष्ठा sk_buff *skb;
		व्योम *raw_buf;
	पूर्ण;
	अचिन्हित पूर्णांक bytecount;
	अचिन्हित लघु gso_segs;

	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
	u32 tx_flags;
पूर्ण;

काष्ठा i40e_rx_buffer अणु
	dma_addr_t dma;
	काष्ठा page *page;
	__u32 page_offset;
	__u16 pagecnt_bias;
पूर्ण;

काष्ठा i40e_queue_stats अणु
	u64 packets;
	u64 bytes;
पूर्ण;

काष्ठा i40e_tx_queue_stats अणु
	u64 restart_queue;
	u64 tx_busy;
	u64 tx_करोne_old;
	u64 tx_linearize;
	u64 tx_क्रमce_wb;
	पूर्णांक prev_pkt_ctr;
पूर्ण;

काष्ठा i40e_rx_queue_stats अणु
	u64 non_eop_descs;
	u64 alloc_page_failed;
	u64 alloc_buff_failed;
	u64 page_reuse_count;
	u64 पुनः_स्मृति_count;
पूर्ण;

क्रमागत i40e_ring_state_t अणु
	__I40E_TX_Fसूची_INIT_DONE,
	__I40E_TX_XPS_INIT_DONE,
	__I40E_RING_STATE_NBITS /* must be last */
पूर्ण;

/* some useful defines क्रम virtchannel पूर्णांकerface, which
 * is the only reमुख्यing user of header split
 */
#घोषणा I40E_RX_DTYPE_HEADER_SPLIT  1
#घोषणा I40E_RX_SPLIT_L2      0x1
#घोषणा I40E_RX_SPLIT_IP      0x2
#घोषणा I40E_RX_SPLIT_TCP_UDP 0x4
#घोषणा I40E_RX_SPLIT_SCTP    0x8

/* काष्ठा that defines a descriptor ring, associated with a VSI */
काष्ठा i40e_ring अणु
	काष्ठा i40e_ring *next;		/* poपूर्णांकer to next ring in q_vector */
	व्योम *desc;			/* Descriptor ring memory */
	काष्ठा device *dev;		/* Used क्रम DMA mapping */
	काष्ठा net_device *netdev;	/* netdev ring maps to */
	काष्ठा bpf_prog *xdp_prog;
	जोड़ अणु
		काष्ठा i40e_tx_buffer *tx_bi;
		काष्ठा i40e_rx_buffer *rx_bi;
		काष्ठा xdp_buff **rx_bi_zc;
	पूर्ण;
	DECLARE_BITMAP(state, __I40E_RING_STATE_NBITS);
	u16 queue_index;		/* Queue number of ring */
	u8 dcb_tc;			/* Traffic class of ring */
	u8 __iomem *tail;

	/* high bit set means dynamic, use accessor routines to पढ़ो/ग_लिखो.
	 * hardware only supports 2us resolution क्रम the ITR रेजिस्टरs.
	 * these values always store the USER setting, and must be converted
	 * beक्रमe programming to a रेजिस्टर.
	 */
	u16 itr_setting;

	u16 count;			/* Number of descriptors */
	u16 reg_idx;			/* HW रेजिस्टर index of the ring */
	u16 rx_buf_len;

	/* used in पूर्णांकerrupt processing */
	u16 next_to_use;
	u16 next_to_clean;
	u16 xdp_tx_active;

	u8 atr_sample_rate;
	u8 atr_count;

	bool ring_active;		/* is ring online or not */
	bool arm_wb;		/* करो something to arm ग_लिखो back */
	u8 packet_stride;

	u16 flags;
#घोषणा I40E_TXR_FLAGS_WB_ON_ITR		BIT(0)
#घोषणा I40E_RXR_FLAGS_BUILD_SKB_ENABLED	BIT(1)
#घोषणा I40E_TXR_FLAGS_XDP			BIT(2)

	/* stats काष्ठाs */
	काष्ठा i40e_queue_stats	stats;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		काष्ठा i40e_tx_queue_stats tx_stats;
		काष्ठा i40e_rx_queue_stats rx_stats;
	पूर्ण;

	अचिन्हित पूर्णांक size;		/* length of descriptor ring in bytes */
	dma_addr_t dma;			/* physical address of ring */

	काष्ठा i40e_vsi *vsi;		/* Backreference to associated VSI */
	काष्ठा i40e_q_vector *q_vector;	/* Backreference to associated vector */

	काष्ठा rcu_head rcu;		/* to aव्योम race on मुक्त */
	u16 next_to_alloc;
	काष्ठा sk_buff *skb;		/* When i40e_clean_rx_ring_irq() must
					 * वापस beक्रमe it sees the EOP क्रम
					 * the current packet, we save that skb
					 * here and resume receiving this
					 * packet the next समय
					 * i40e_clean_rx_ring_irq() is called
					 * क्रम this ring.
					 */

	काष्ठा i40e_channel *ch;
	u16 rx_offset;
	काष्ठा xdp_rxq_info xdp_rxq;
	काष्ठा xsk_buff_pool *xsk_pool;
	काष्ठा xdp_desc *xsk_descs;      /* For storing descriptors in the AF_XDP ZC path */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

अटल अंतरभूत bool ring_uses_build_skb(काष्ठा i40e_ring *ring)
अणु
	वापस !!(ring->flags & I40E_RXR_FLAGS_BUILD_SKB_ENABLED);
पूर्ण

अटल अंतरभूत व्योम set_ring_build_skb_enabled(काष्ठा i40e_ring *ring)
अणु
	ring->flags |= I40E_RXR_FLAGS_BUILD_SKB_ENABLED;
पूर्ण

अटल अंतरभूत व्योम clear_ring_build_skb_enabled(काष्ठा i40e_ring *ring)
अणु
	ring->flags &= ~I40E_RXR_FLAGS_BUILD_SKB_ENABLED;
पूर्ण

अटल अंतरभूत bool ring_is_xdp(काष्ठा i40e_ring *ring)
अणु
	वापस !!(ring->flags & I40E_TXR_FLAGS_XDP);
पूर्ण

अटल अंतरभूत व्योम set_ring_xdp(काष्ठा i40e_ring *ring)
अणु
	ring->flags |= I40E_TXR_FLAGS_XDP;
पूर्ण

#घोषणा I40E_ITR_ADAPTIVE_MIN_INC	0x0002
#घोषणा I40E_ITR_ADAPTIVE_MIN_USECS	0x0002
#घोषणा I40E_ITR_ADAPTIVE_MAX_USECS	0x007e
#घोषणा I40E_ITR_ADAPTIVE_LATENCY	0x8000
#घोषणा I40E_ITR_ADAPTIVE_BULK		0x0000

काष्ठा i40e_ring_container अणु
	काष्ठा i40e_ring *ring;		/* poपूर्णांकer to linked list of ring(s) */
	अचिन्हित दीर्घ next_update;	/* jअगरfies value of next update */
	अचिन्हित पूर्णांक total_bytes;	/* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;	/* total packets processed this पूर्णांक */
	u16 count;
	u16 target_itr;			/* target ITR setting क्रम ring(s) */
	u16 current_itr;		/* current ITR setting क्रम ring(s) */
पूर्ण;

/* iterator क्रम handling rings in ring container */
#घोषणा i40e_क्रम_each_ring(pos, head) \
	क्रम (pos = (head).ring; pos != शून्य; pos = pos->next)

अटल अंतरभूत अचिन्हित पूर्णांक i40e_rx_pg_order(काष्ठा i40e_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring->rx_buf_len > (PAGE_SIZE / 2))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा i40e_rx_pg_size(_ring) (PAGE_SIZE << i40e_rx_pg_order(_ring))

bool i40e_alloc_rx_buffers(काष्ठा i40e_ring *rxr, u16 cleaned_count);
netdev_tx_t i40e_lan_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);
व्योम i40e_clean_tx_ring(काष्ठा i40e_ring *tx_ring);
व्योम i40e_clean_rx_ring(काष्ठा i40e_ring *rx_ring);
पूर्णांक i40e_setup_tx_descriptors(काष्ठा i40e_ring *tx_ring);
पूर्णांक i40e_setup_rx_descriptors(काष्ठा i40e_ring *rx_ring);
व्योम i40e_मुक्त_tx_resources(काष्ठा i40e_ring *tx_ring);
व्योम i40e_मुक्त_rx_resources(काष्ठा i40e_ring *rx_ring);
पूर्णांक i40e_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम i40e_क्रमce_wb(काष्ठा i40e_vsi *vsi, काष्ठा i40e_q_vector *q_vector);
u32 i40e_get_tx_pending(काष्ठा i40e_ring *ring, bool in_sw);
व्योम i40e_detect_recover_hung(काष्ठा i40e_vsi *vsi);
पूर्णांक __i40e_maybe_stop_tx(काष्ठा i40e_ring *tx_ring, पूर्णांक size);
bool __i40e_chk_linearize(काष्ठा sk_buff *skb);
पूर्णांक i40e_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **frames,
		  u32 flags);
पूर्णांक i40e_alloc_rx_bi(काष्ठा i40e_ring *rx_ring);

/**
 * i40e_get_head - Retrieve head from head ग_लिखोback
 * @tx_ring:  tx ring to fetch head of
 *
 * Returns value of Tx ring head based on value stored
 * in head ग_लिखो-back location
 **/
अटल अंतरभूत u32 i40e_get_head(काष्ठा i40e_ring *tx_ring)
अणु
	व्योम *head = (काष्ठा i40e_tx_desc *)tx_ring->desc + tx_ring->count;

	वापस le32_to_cpu(*(अस्थिर __le32 *)head);
पूर्ण

/**
 * i40e_xmit_descriptor_count - calculate number of Tx descriptors needed
 * @skb:     send buffer
 *
 * Returns number of data descriptors needed क्रम this skb. Returns 0 to indicate
 * there is not enough descriptors available in this ring since we need at least
 * one descriptor.
 **/
अटल अंतरभूत पूर्णांक i40e_xmit_descriptor_count(काष्ठा sk_buff *skb)
अणु
	स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[0];
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक count = 0, size = skb_headlen(skb);

	क्रम (;;) अणु
		count += i40e_txd_use_count(size);

		अगर (!nr_frags--)
			अवरोध;

		size = skb_frag_size(frag++);
	पूर्ण

	वापस count;
पूर्ण

/**
 * i40e_maybe_stop_tx - 1st level check क्रम Tx stop conditions
 * @tx_ring: the ring to be checked
 * @size:    the size buffer we want to assure is available
 *
 * Returns 0 अगर stop is not needed
 **/
अटल अंतरभूत पूर्णांक i40e_maybe_stop_tx(काष्ठा i40e_ring *tx_ring, पूर्णांक size)
अणु
	अगर (likely(I40E_DESC_UNUSED(tx_ring) >= size))
		वापस 0;
	वापस __i40e_maybe_stop_tx(tx_ring, size);
पूर्ण

/**
 * i40e_chk_linearize - Check अगर there are more than 8 fragments per packet
 * @skb:      send buffer
 * @count:    number of buffers used
 *
 * Note: Our HW can't scatter-gather more than 8 fragments to build
 * a packet on the wire and so we need to figure out the हालs where we
 * need to linearize the skb.
 **/
अटल अंतरभूत bool i40e_chk_linearize(काष्ठा sk_buff *skb, पूर्णांक count)
अणु
	/* Both TSO and single send will work अगर count is less than 8 */
	अगर (likely(count < I40E_MAX_BUFFER_TXD))
		वापस false;

	अगर (skb_is_gso(skb))
		वापस __i40e_chk_linearize(skb);

	/* we can support up to 8 data buffers क्रम a single send */
	वापस count != I40E_MAX_BUFFER_TXD;
पूर्ण

/**
 * txring_txq - Find the netdev Tx ring based on the i40e Tx ring
 * @ring: Tx ring to find the netdev equivalent of
 **/
अटल अंतरभूत काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा i40e_ring *ring)
अणु
	वापस netdev_get_tx_queue(ring->netdev, ring->queue_index);
पूर्ण
#पूर्ण_अगर /* _I40E_TXRX_H_ */
