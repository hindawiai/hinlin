<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_TXRX_H_
#घोषणा _IAVF_TXRX_H_

/* Interrupt Throttling and Rate Limiting Goodies */
#घोषणा IAVF_DEFAULT_IRQ_WORK      256

/* The datasheet क्रम the X710 and XL710 indicate that the maximum value क्रम
 * the ITR is 8160usec which is then called out as 0xFF0 with a 2usec
 * resolution. 8160 is 0x1FE0 when written out in hex. So instead of storing
 * the रेजिस्टर value which is भागided by 2 lets use the actual values and
 * aव्योम an excessive amount of translation.
 */
#घोषणा IAVF_ITR_DYNAMIC	0x8000	/* use top bit as a flag */
#घोषणा IAVF_ITR_MASK		0x1FFE	/* mask क्रम ITR रेजिस्टर value */
#घोषणा IAVF_MIN_ITR		     2	/* reg uses 2 usec resolution */
#घोषणा IAVF_ITR_100K		    10	/* all values below must be even */
#घोषणा IAVF_ITR_50K		    20
#घोषणा IAVF_ITR_20K		    50
#घोषणा IAVF_ITR_18K		    60
#घोषणा IAVF_ITR_8K		   122
#घोषणा IAVF_MAX_ITR		  8160	/* maximum value as per datasheet */
#घोषणा ITR_TO_REG(setting) ((setting) & ~IAVF_ITR_DYNAMIC)
#घोषणा ITR_REG_ALIGN(setting) __ALIGN_MASK(setting, ~IAVF_ITR_MASK)
#घोषणा ITR_IS_DYNAMIC(setting) (!!((setting) & IAVF_ITR_DYNAMIC))

#घोषणा IAVF_ITR_RX_DEF		(IAVF_ITR_20K | IAVF_ITR_DYNAMIC)
#घोषणा IAVF_ITR_TX_DEF		(IAVF_ITR_20K | IAVF_ITR_DYNAMIC)

/* 0x40 is the enable bit क्रम पूर्णांकerrupt rate limiting, and must be set अगर
 * the value of the rate limit is non-zero
 */
#घोषणा INTRL_ENA                  BIT(6)
#घोषणा IAVF_MAX_INTRL             0x3B    /* reg uses 4 usec resolution */
#घोषणा INTRL_REG_TO_USEC(पूर्णांकrl) ((पूर्णांकrl & ~INTRL_ENA) << 2)
#घोषणा INTRL_USEC_TO_REG(set) ((set) ? ((set) >> 2) | INTRL_ENA : 0)
#घोषणा IAVF_INTRL_8K              125     /* 8000 पूर्णांकs/sec */
#घोषणा IAVF_INTRL_62K             16      /* 62500 पूर्णांकs/sec */
#घोषणा IAVF_INTRL_83K             12      /* 83333 पूर्णांकs/sec */

#घोषणा IAVF_QUEUE_END_OF_LIST 0x7FF

/* this क्रमागत matches hardware bits and is meant to be used by DYN_CTLN
 * रेजिस्टरs and QINT रेजिस्टरs or more generally anywhere in the manual
 * mentioning ITR_INDX, ITR_NONE cannot be used as an index 'n' पूर्णांकo any
 * रेजिस्टर but instead is a special value meaning "don't update" ITR0/1/2.
 */
क्रमागत iavf_dyn_idx_t अणु
	IAVF_IDX_ITR0 = 0,
	IAVF_IDX_ITR1 = 1,
	IAVF_IDX_ITR2 = 2,
	IAVF_ITR_NONE = 3	/* ITR_NONE must not be used as an index */
पूर्ण;

/* these are indexes पूर्णांकo ITRN रेजिस्टरs */
#घोषणा IAVF_RX_ITR    IAVF_IDX_ITR0
#घोषणा IAVF_TX_ITR    IAVF_IDX_ITR1
#घोषणा IAVF_PE_ITR    IAVF_IDX_ITR2

/* Supported RSS offloads */
#घोषणा IAVF_DEFAULT_RSS_HENA ( \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV4_UDP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV4_SCTP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV4_TCP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV4_OTHER) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_FRAG_IPV4) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV6_UDP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV6_TCP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV6_SCTP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV6_OTHER) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_FRAG_IPV6) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_L2_PAYLOAD))

#घोषणा IAVF_DEFAULT_RSS_HENA_EXPANDED (IAVF_DEFAULT_RSS_HENA | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_UNICAST_IPV4_UDP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_MULTICAST_IPV4_UDP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_UNICAST_IPV6_UDP) | \
	BIT_ULL(IAVF_FILTER_PCTYPE_NONF_MULTICAST_IPV6_UDP))

/* Supported Rx Buffer Sizes (a multiple of 128) */
#घोषणा IAVF_RXBUFFER_256   256
#घोषणा IAVF_RXBUFFER_1536  1536  /* 128B aligned standard Ethernet frame */
#घोषणा IAVF_RXBUFFER_2048  2048
#घोषणा IAVF_RXBUFFER_3072  3072  /* Used क्रम large frames w/ padding */
#घोषणा IAVF_MAX_RXBUFFER   9728  /* largest size क्रम single descriptor */

/* NOTE: netdev_alloc_skb reserves up to 64 bytes, NET_IP_ALIGN means we
 * reserve 2 more, and skb_shared_info adds an additional 384 bytes more,
 * this adds up to 512 bytes of extra data meaning the smallest allocation
 * we could have is 1K.
 * i.e. RXBUFFER_256 --> 960 byte skb (size-1024 slab)
 * i.e. RXBUFFER_512 --> 1216 byte skb (size-2048 slab)
 */
#घोषणा IAVF_RX_HDR_SIZE IAVF_RXBUFFER_256
#घोषणा IAVF_PACKET_HDR_PAD (ETH_HLEN + ETH_FCS_LEN + (VLAN_HLEN * 2))
#घोषणा iavf_rx_desc iavf_32byte_rx_desc

#घोषणा IAVF_RX_DMA_ATTR \
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
#घोषणा IAVF_2K_TOO_SMALL_WITH_PADDING \
((NET_SKB_PAD + IAVF_RXBUFFER_1536) > SKB_WITH_OVERHEAD(IAVF_RXBUFFER_2048))

अटल अंतरभूत पूर्णांक iavf_compute_pad(पूर्णांक rx_buf_len)
अणु
	पूर्णांक page_size, pad_size;

	page_size = ALIGN(rx_buf_len, PAGE_SIZE / 2);
	pad_size = SKB_WITH_OVERHEAD(page_size) - rx_buf_len;

	वापस pad_size;
पूर्ण

अटल अंतरभूत पूर्णांक iavf_skb_pad(व्योम)
अणु
	पूर्णांक rx_buf_len;

	/* If a 2K buffer cannot handle a standard Ethernet frame then
	 * optimize padding क्रम a 3K buffer instead of a 1.5K buffer.
	 *
	 * For a 3K buffer we need to add enough padding to allow क्रम
	 * tailroom due to NET_IP_ALIGN possibly shअगरting us out of
	 * cache-line alignment.
	 */
	अगर (IAVF_2K_TOO_SMALL_WITH_PADDING)
		rx_buf_len = IAVF_RXBUFFER_3072 + SKB_DATA_ALIGN(NET_IP_ALIGN);
	अन्यथा
		rx_buf_len = IAVF_RXBUFFER_1536;

	/* अगर needed make room क्रम NET_IP_ALIGN */
	rx_buf_len -= NET_IP_ALIGN;

	वापस iavf_compute_pad(rx_buf_len);
पूर्ण

#घोषणा IAVF_SKB_PAD iavf_skb_pad()
#अन्यथा
#घोषणा IAVF_2K_TOO_SMALL_WITH_PADDING false
#घोषणा IAVF_SKB_PAD (NET_SKB_PAD + NET_IP_ALIGN)
#पूर्ण_अगर

/**
 * iavf_test_staterr - tests bits in Rx descriptor status and error fields
 * @rx_desc: poपूर्णांकer to receive descriptor (in le64 क्रमmat)
 * @stat_err_bits: value to mask
 *
 * This function करोes some fast chicanery in order to वापस the
 * value of the mask which is really only used क्रम boolean tests.
 * The status_error_len करोesn't need to be shअगरted because it begins
 * at offset zero.
 */
अटल अंतरभूत bool iavf_test_staterr(जोड़ iavf_rx_desc *rx_desc,
				     स्थिर u64 stat_err_bits)
अणु
	वापस !!(rx_desc->wb.qword1.status_error_len &
		  cpu_to_le64(stat_err_bits));
पूर्ण

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IAVF_RX_INCREMENT(r, i) \
	करो अणु					\
		(i)++;				\
		अगर ((i) == (r)->count)		\
			i = 0;			\
		r->next_to_clean = i;		\
	पूर्ण जबतक (0)

#घोषणा IAVF_RX_NEXT_DESC(r, i, n)		\
	करो अणु					\
		(i)++;				\
		अगर ((i) == (r)->count)		\
			i = 0;			\
		(n) = IAVF_RX_DESC((r), (i));	\
	पूर्ण जबतक (0)

#घोषणा IAVF_RX_NEXT_DESC_PREFETCH(r, i, n)		\
	करो अणु						\
		IAVF_RX_NEXT_DESC((r), (i), (n));	\
		prefetch((n));				\
	पूर्ण जबतक (0)

#घोषणा IAVF_MAX_BUFFER_TXD	8
#घोषणा IAVF_MIN_TX_LEN		17

/* The size limit क्रम a transmit buffer in a descriptor is (16K - 1).
 * In order to align with the पढ़ो requests we will align the value to
 * the nearest 4K which represents our maximum पढ़ो request size.
 */
#घोषणा IAVF_MAX_READ_REQ_SIZE		4096
#घोषणा IAVF_MAX_DATA_PER_TXD		(16 * 1024 - 1)
#घोषणा IAVF_MAX_DATA_PER_TXD_ALIGNED \
	(IAVF_MAX_DATA_PER_TXD & ~(IAVF_MAX_READ_REQ_SIZE - 1))

/**
 * iavf_txd_use_count  - estimate the number of descriptors needed क्रम Tx
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
अटल अंतरभूत अचिन्हित पूर्णांक iavf_txd_use_count(अचिन्हित पूर्णांक size)
अणु
	वापस ((size * 85) >> 20) + 1;
पूर्ण

/* Tx Descriptors needed, worst हाल */
#घोषणा DESC_NEEDED (MAX_SKB_FRAGS + 6)
#घोषणा IAVF_MIN_DESC_PENDING	4

#घोषणा IAVF_TX_FLAGS_HW_VLAN		BIT(1)
#घोषणा IAVF_TX_FLAGS_SW_VLAN		BIT(2)
#घोषणा IAVF_TX_FLAGS_TSO		BIT(3)
#घोषणा IAVF_TX_FLAGS_IPV4		BIT(4)
#घोषणा IAVF_TX_FLAGS_IPV6		BIT(5)
#घोषणा IAVF_TX_FLAGS_FCCRC		BIT(6)
#घोषणा IAVF_TX_FLAGS_FSO		BIT(7)
#घोषणा IAVF_TX_FLAGS_FD_SB		BIT(9)
#घोषणा IAVF_TX_FLAGS_VXLAN_TUNNEL	BIT(10)
#घोषणा IAVF_TX_FLAGS_VLAN_MASK		0xffff0000
#घोषणा IAVF_TX_FLAGS_VLAN_PRIO_MASK	0xe0000000
#घोषणा IAVF_TX_FLAGS_VLAN_PRIO_SHIFT	29
#घोषणा IAVF_TX_FLAGS_VLAN_SHIFT	16

काष्ठा iavf_tx_buffer अणु
	काष्ठा iavf_tx_desc *next_to_watch;
	जोड़ अणु
		काष्ठा sk_buff *skb;
		व्योम *raw_buf;
	पूर्ण;
	अचिन्हित पूर्णांक bytecount;
	अचिन्हित लघु gso_segs;

	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
	u32 tx_flags;
पूर्ण;

काष्ठा iavf_rx_buffer अणु
	dma_addr_t dma;
	काष्ठा page *page;
#अगर (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
#अन्यथा
	__u16 page_offset;
#पूर्ण_अगर
	__u16 pagecnt_bias;
पूर्ण;

काष्ठा iavf_queue_stats अणु
	u64 packets;
	u64 bytes;
पूर्ण;

काष्ठा iavf_tx_queue_stats अणु
	u64 restart_queue;
	u64 tx_busy;
	u64 tx_करोne_old;
	u64 tx_linearize;
	u64 tx_क्रमce_wb;
	पूर्णांक prev_pkt_ctr;
	u64 tx_lost_पूर्णांकerrupt;
पूर्ण;

काष्ठा iavf_rx_queue_stats अणु
	u64 non_eop_descs;
	u64 alloc_page_failed;
	u64 alloc_buff_failed;
	u64 page_reuse_count;
	u64 पुनः_स्मृति_count;
पूर्ण;

क्रमागत iavf_ring_state_t अणु
	__IAVF_TX_Fसूची_INIT_DONE,
	__IAVF_TX_XPS_INIT_DONE,
	__IAVF_RING_STATE_NBITS /* must be last */
पूर्ण;

/* some useful defines क्रम virtchannel पूर्णांकerface, which
 * is the only reमुख्यing user of header split
 */
#घोषणा IAVF_RX_DTYPE_NO_SPLIT      0
#घोषणा IAVF_RX_DTYPE_HEADER_SPLIT  1
#घोषणा IAVF_RX_DTYPE_SPLIT_ALWAYS  2
#घोषणा IAVF_RX_SPLIT_L2      0x1
#घोषणा IAVF_RX_SPLIT_IP      0x2
#घोषणा IAVF_RX_SPLIT_TCP_UDP 0x4
#घोषणा IAVF_RX_SPLIT_SCTP    0x8

/* काष्ठा that defines a descriptor ring, associated with a VSI */
काष्ठा iavf_ring अणु
	काष्ठा iavf_ring *next;		/* poपूर्णांकer to next ring in q_vector */
	व्योम *desc;			/* Descriptor ring memory */
	काष्ठा device *dev;		/* Used क्रम DMA mapping */
	काष्ठा net_device *netdev;	/* netdev ring maps to */
	जोड़ अणु
		काष्ठा iavf_tx_buffer *tx_bi;
		काष्ठा iavf_rx_buffer *rx_bi;
	पूर्ण;
	DECLARE_BITMAP(state, __IAVF_RING_STATE_NBITS);
	u16 queue_index;		/* Queue number of ring */
	u8 dcb_tc;			/* Traffic class of ring */
	u8 __iomem *tail;

	/* high bit set means dynamic, use accessors routines to पढ़ो/ग_लिखो.
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

	u8 atr_sample_rate;
	u8 atr_count;

	bool ring_active;		/* is ring online or not */
	bool arm_wb;		/* करो something to arm ग_लिखो back */
	u8 packet_stride;

	u16 flags;
#घोषणा IAVF_TXR_FLAGS_WB_ON_ITR		BIT(0)
#घोषणा IAVF_RXR_FLAGS_BUILD_SKB_ENABLED	BIT(1)

	/* stats काष्ठाs */
	काष्ठा iavf_queue_stats	stats;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		काष्ठा iavf_tx_queue_stats tx_stats;
		काष्ठा iavf_rx_queue_stats rx_stats;
	पूर्ण;

	अचिन्हित पूर्णांक size;		/* length of descriptor ring in bytes */
	dma_addr_t dma;			/* physical address of ring */

	काष्ठा iavf_vsi *vsi;		/* Backreference to associated VSI */
	काष्ठा iavf_q_vector *q_vector;	/* Backreference to associated vector */

	काष्ठा rcu_head rcu;		/* to aव्योम race on मुक्त */
	u16 next_to_alloc;
	काष्ठा sk_buff *skb;		/* When iavf_clean_rx_ring_irq() must
					 * वापस beक्रमe it sees the EOP क्रम
					 * the current packet, we save that skb
					 * here and resume receiving this
					 * packet the next समय
					 * iavf_clean_rx_ring_irq() is called
					 * क्रम this ring.
					 */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

अटल अंतरभूत bool ring_uses_build_skb(काष्ठा iavf_ring *ring)
अणु
	वापस !!(ring->flags & IAVF_RXR_FLAGS_BUILD_SKB_ENABLED);
पूर्ण

अटल अंतरभूत व्योम set_ring_build_skb_enabled(काष्ठा iavf_ring *ring)
अणु
	ring->flags |= IAVF_RXR_FLAGS_BUILD_SKB_ENABLED;
पूर्ण

अटल अंतरभूत व्योम clear_ring_build_skb_enabled(काष्ठा iavf_ring *ring)
अणु
	ring->flags &= ~IAVF_RXR_FLAGS_BUILD_SKB_ENABLED;
पूर्ण

#घोषणा IAVF_ITR_ADAPTIVE_MIN_INC	0x0002
#घोषणा IAVF_ITR_ADAPTIVE_MIN_USECS	0x0002
#घोषणा IAVF_ITR_ADAPTIVE_MAX_USECS	0x007e
#घोषणा IAVF_ITR_ADAPTIVE_LATENCY	0x8000
#घोषणा IAVF_ITR_ADAPTIVE_BULK		0x0000
#घोषणा ITR_IS_BULK(x) (!((x) & IAVF_ITR_ADAPTIVE_LATENCY))

काष्ठा iavf_ring_container अणु
	काष्ठा iavf_ring *ring;		/* poपूर्णांकer to linked list of ring(s) */
	अचिन्हित दीर्घ next_update;	/* jअगरfies value of next update */
	अचिन्हित पूर्णांक total_bytes;	/* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;	/* total packets processed this पूर्णांक */
	u16 count;
	u16 target_itr;			/* target ITR setting क्रम ring(s) */
	u16 current_itr;		/* current ITR setting क्रम ring(s) */
पूर्ण;

/* iterator क्रम handling rings in ring container */
#घोषणा iavf_क्रम_each_ring(pos, head) \
	क्रम (pos = (head).ring; pos != शून्य; pos = pos->next)

अटल अंतरभूत अचिन्हित पूर्णांक iavf_rx_pg_order(काष्ठा iavf_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring->rx_buf_len > (PAGE_SIZE / 2))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा iavf_rx_pg_size(_ring) (PAGE_SIZE << iavf_rx_pg_order(_ring))

bool iavf_alloc_rx_buffers(काष्ठा iavf_ring *rxr, u16 cleaned_count);
netdev_tx_t iavf_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);
व्योम iavf_clean_tx_ring(काष्ठा iavf_ring *tx_ring);
व्योम iavf_clean_rx_ring(काष्ठा iavf_ring *rx_ring);
पूर्णांक iavf_setup_tx_descriptors(काष्ठा iavf_ring *tx_ring);
पूर्णांक iavf_setup_rx_descriptors(काष्ठा iavf_ring *rx_ring);
व्योम iavf_मुक्त_tx_resources(काष्ठा iavf_ring *tx_ring);
व्योम iavf_मुक्त_rx_resources(काष्ठा iavf_ring *rx_ring);
पूर्णांक iavf_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम iavf_क्रमce_wb(काष्ठा iavf_vsi *vsi, काष्ठा iavf_q_vector *q_vector);
u32 iavf_get_tx_pending(काष्ठा iavf_ring *ring, bool in_sw);
व्योम iavf_detect_recover_hung(काष्ठा iavf_vsi *vsi);
पूर्णांक __iavf_maybe_stop_tx(काष्ठा iavf_ring *tx_ring, पूर्णांक size);
bool __iavf_chk_linearize(काष्ठा sk_buff *skb);

/**
 * iavf_xmit_descriptor_count - calculate number of Tx descriptors needed
 * @skb:     send buffer
 *
 * Returns number of data descriptors needed क्रम this skb. Returns 0 to indicate
 * there is not enough descriptors available in this ring since we need at least
 * one descriptor.
 **/
अटल अंतरभूत पूर्णांक iavf_xmit_descriptor_count(काष्ठा sk_buff *skb)
अणु
	स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[0];
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक count = 0, size = skb_headlen(skb);

	क्रम (;;) अणु
		count += iavf_txd_use_count(size);

		अगर (!nr_frags--)
			अवरोध;

		size = skb_frag_size(frag++);
	पूर्ण

	वापस count;
पूर्ण

/**
 * iavf_maybe_stop_tx - 1st level check क्रम Tx stop conditions
 * @tx_ring: the ring to be checked
 * @size:    the size buffer we want to assure is available
 *
 * Returns 0 अगर stop is not needed
 **/
अटल अंतरभूत पूर्णांक iavf_maybe_stop_tx(काष्ठा iavf_ring *tx_ring, पूर्णांक size)
अणु
	अगर (likely(IAVF_DESC_UNUSED(tx_ring) >= size))
		वापस 0;
	वापस __iavf_maybe_stop_tx(tx_ring, size);
पूर्ण

/**
 * iavf_chk_linearize - Check अगर there are more than 8 fragments per packet
 * @skb:      send buffer
 * @count:    number of buffers used
 *
 * Note: Our HW can't scatter-gather more than 8 fragments to build
 * a packet on the wire and so we need to figure out the हालs where we
 * need to linearize the skb.
 **/
अटल अंतरभूत bool iavf_chk_linearize(काष्ठा sk_buff *skb, पूर्णांक count)
अणु
	/* Both TSO and single send will work अगर count is less than 8 */
	अगर (likely(count < IAVF_MAX_BUFFER_TXD))
		वापस false;

	अगर (skb_is_gso(skb))
		वापस __iavf_chk_linearize(skb);

	/* we can support up to 8 data buffers क्रम a single send */
	वापस count != IAVF_MAX_BUFFER_TXD;
पूर्ण
/**
 * txring_txq - helper to convert from a ring to a queue
 * @ring: Tx ring to find the netdev equivalent of
 **/
अटल अंतरभूत काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा iavf_ring *ring)
अणु
	वापस netdev_get_tx_queue(ring->netdev, ring->queue_index);
पूर्ण
#पूर्ण_अगर /* _IAVF_TXRX_H_ */
