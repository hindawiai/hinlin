<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_TXRX_H_
#घोषणा _ICE_TXRX_H_

#समावेश "ice_type.h"

#घोषणा ICE_DFLT_IRQ_WORK	256
#घोषणा ICE_RXBUF_3072		3072
#घोषणा ICE_RXBUF_2048		2048
#घोषणा ICE_RXBUF_1536		1536
#घोषणा ICE_MAX_CHAINED_RX_BUFS	5
#घोषणा ICE_MAX_BUF_TXD		8
#घोषणा ICE_MIN_TX_LEN		17

/* The size limit क्रम a transmit buffer in a descriptor is (16K - 1).
 * In order to align with the पढ़ो requests we will align the value to
 * the nearest 4K which represents our maximum पढ़ो request size.
 */
#घोषणा ICE_MAX_READ_REQ_SIZE	4096
#घोषणा ICE_MAX_DATA_PER_TXD	(16 * 1024 - 1)
#घोषणा ICE_MAX_DATA_PER_TXD_ALIGNED \
	(~(ICE_MAX_READ_REQ_SIZE - 1) & ICE_MAX_DATA_PER_TXD)

#घोषणा ICE_RX_BUF_WRITE	16	/* Must be घातer of 2 */
#घोषणा ICE_MAX_TXQ_PER_TXQG	128

/* Attempt to maximize the headroom available क्रम incoming frames. We use a 2K
 * buffer क्रम MTUs <= 1500 and need 1536/1534 to store the data क्रम the frame.
 * This leaves us with 512 bytes of room.  From that we need to deduct the
 * space needed क्रम the shared info and the padding needed to IP align the
 * frame.
 *
 * Note: For cache line sizes 256 or larger this value is going to end
 *	 up negative.  In these हालs we should fall back to the legacy
 *	 receive path.
 */
#अगर (PAGE_SIZE < 8192)
#घोषणा ICE_2K_TOO_SMALL_WITH_PADDING \
	((अचिन्हित पूर्णांक)(NET_SKB_PAD + ICE_RXBUF_1536) > \
			SKB_WITH_OVERHEAD(ICE_RXBUF_2048))

/**
 * ice_compute_pad - compute the padding
 * @rx_buf_len: buffer length
 *
 * Figure out the size of half page based on given buffer length and
 * then subtract the skb_shared_info followed by subtraction of the
 * actual buffer length; this in turn results in the actual space that
 * is left क्रम padding usage
 */
अटल अंतरभूत पूर्णांक ice_compute_pad(पूर्णांक rx_buf_len)
अणु
	पूर्णांक half_page_size;

	half_page_size = ALIGN(rx_buf_len, PAGE_SIZE / 2);
	वापस SKB_WITH_OVERHEAD(half_page_size) - rx_buf_len;
पूर्ण

/**
 * ice_skb_pad - determine the padding that we can supply
 *
 * Figure out the right Rx buffer size and based on that calculate the
 * padding
 */
अटल अंतरभूत पूर्णांक ice_skb_pad(व्योम)
अणु
	पूर्णांक rx_buf_len;

	/* If a 2K buffer cannot handle a standard Ethernet frame then
	 * optimize padding क्रम a 3K buffer instead of a 1.5K buffer.
	 *
	 * For a 3K buffer we need to add enough padding to allow क्रम
	 * tailroom due to NET_IP_ALIGN possibly shअगरting us out of
	 * cache-line alignment.
	 */
	अगर (ICE_2K_TOO_SMALL_WITH_PADDING)
		rx_buf_len = ICE_RXBUF_3072 + SKB_DATA_ALIGN(NET_IP_ALIGN);
	अन्यथा
		rx_buf_len = ICE_RXBUF_1536;

	/* अगर needed make room क्रम NET_IP_ALIGN */
	rx_buf_len -= NET_IP_ALIGN;

	वापस ice_compute_pad(rx_buf_len);
पूर्ण

#घोषणा ICE_SKB_PAD ice_skb_pad()
#अन्यथा
#घोषणा ICE_2K_TOO_SMALL_WITH_PADDING false
#घोषणा ICE_SKB_PAD (NET_SKB_PAD + NET_IP_ALIGN)
#पूर्ण_अगर

/* We are assuming that the cache line is always 64 Bytes here क्रम ice.
 * In order to make sure that is a correct assumption there is a check in probe
 * to prपूर्णांक a warning अगर the पढ़ो from GLPCI_CNF2 tells us that the cache line
 * size is 128 bytes. We करो it this way because we करो not want to पढ़ो the
 * GLPCI_CNF2 रेजिस्टर or a variable containing the value on every pass through
 * the Tx path.
 */
#घोषणा ICE_CACHE_LINE_BYTES		64
#घोषणा ICE_DESCS_PER_CACHE_LINE	(ICE_CACHE_LINE_BYTES / \
					 माप(काष्ठा ice_tx_desc))
#घोषणा ICE_DESCS_FOR_CTX_DESC		1
#घोषणा ICE_DESCS_FOR_SKB_DATA_PTR	1
/* Tx descriptors needed, worst हाल */
#घोषणा DESC_NEEDED (MAX_SKB_FRAGS + ICE_DESCS_FOR_CTX_DESC + \
		     ICE_DESCS_PER_CACHE_LINE + ICE_DESCS_FOR_SKB_DATA_PTR)
#घोषणा ICE_DESC_UNUSED(R)	\
	(u16)((((R)->next_to_clean > (R)->next_to_use) ? 0 : (R)->count) + \
	      (R)->next_to_clean - (R)->next_to_use - 1)

#घोषणा ICE_TX_FLAGS_TSO	BIT(0)
#घोषणा ICE_TX_FLAGS_HW_VLAN	BIT(1)
#घोषणा ICE_TX_FLAGS_SW_VLAN	BIT(2)
/* ICE_TX_FLAGS_DUMMY_PKT is used to mark dummy packets that should be
 * मुक्तd instead of वापसed like skb packets.
 */
#घोषणा ICE_TX_FLAGS_DUMMY_PKT	BIT(3)
#घोषणा ICE_TX_FLAGS_IPV4	BIT(5)
#घोषणा ICE_TX_FLAGS_IPV6	BIT(6)
#घोषणा ICE_TX_FLAGS_TUNNEL	BIT(7)
#घोषणा ICE_TX_FLAGS_VLAN_M	0xffff0000
#घोषणा ICE_TX_FLAGS_VLAN_PR_M	0xe0000000
#घोषणा ICE_TX_FLAGS_VLAN_PR_S	29
#घोषणा ICE_TX_FLAGS_VLAN_S	16

#घोषणा ICE_XDP_PASS		0
#घोषणा ICE_XDP_CONSUMED	BIT(0)
#घोषणा ICE_XDP_TX		BIT(1)
#घोषणा ICE_XDP_REसूची		BIT(2)

#घोषणा ICE_RX_DMA_ATTR \
	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

#घोषणा ICE_ETH_PKT_HDR_PAD	(ETH_HLEN + ETH_FCS_LEN + (VLAN_HLEN * 2))

#घोषणा ICE_TXD_LAST_DESC_CMD (ICE_TX_DESC_CMD_EOP | ICE_TX_DESC_CMD_RS)

काष्ठा ice_tx_buf अणु
	काष्ठा ice_tx_desc *next_to_watch;
	जोड़ अणु
		काष्ठा sk_buff *skb;
		व्योम *raw_buf; /* used क्रम XDP */
	पूर्ण;
	अचिन्हित पूर्णांक bytecount;
	अचिन्हित लघु gso_segs;
	u32 tx_flags;
	DEFINE_DMA_UNMAP_LEN(len);
	DEFINE_DMA_UNMAP_ADDR(dma);
पूर्ण;

काष्ठा ice_tx_offload_params अणु
	u64 cd_qw1;
	काष्ठा ice_ring *tx_ring;
	u32 td_cmd;
	u32 td_offset;
	u32 td_l2tag1;
	u32 cd_tunnel_params;
	u16 cd_l2tag2;
	u8 header_len;
पूर्ण;

काष्ठा ice_rx_buf अणु
	जोड़ अणु
		काष्ठा अणु
			dma_addr_t dma;
			काष्ठा page *page;
			अचिन्हित पूर्णांक page_offset;
			u16 pagecnt_bias;
		पूर्ण;
		काष्ठा अणु
			काष्ठा xdp_buff *xdp;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा ice_q_stats अणु
	u64 pkts;
	u64 bytes;
पूर्ण;

काष्ठा ice_txq_stats अणु
	u64 restart_q;
	u64 tx_busy;
	u64 tx_linearize;
	पूर्णांक prev_pkt; /* negative अगर no pending Tx descriptors */
पूर्ण;

काष्ठा ice_rxq_stats अणु
	u64 non_eop_descs;
	u64 alloc_page_failed;
	u64 alloc_buf_failed;
पूर्ण;

क्रमागत ice_ring_state_t अणु
	ICE_TX_XPS_INIT_DONE,
	ICE_TX_NBITS,
पूर्ण;

/* this क्रमागत matches hardware bits and is meant to be used by DYN_CTLN
 * रेजिस्टरs and QINT रेजिस्टरs or more generally anywhere in the manual
 * mentioning ITR_INDX, ITR_NONE cannot be used as an index 'n' पूर्णांकo any
 * रेजिस्टर but instead is a special value meaning "don't update" ITR0/1/2.
 */
क्रमागत ice_dyn_idx_t अणु
	ICE_IDX_ITR0 = 0,
	ICE_IDX_ITR1 = 1,
	ICE_IDX_ITR2 = 2,
	ICE_ITR_NONE = 3	/* ITR_NONE must not be used as an index */
पूर्ण;

/* Header split modes defined by DTYPE field of Rx RLAN context */
क्रमागत ice_rx_dtype अणु
	ICE_RX_DTYPE_NO_SPLIT		= 0,
	ICE_RX_DTYPE_HEADER_SPLIT	= 1,
	ICE_RX_DTYPE_SPLIT_ALWAYS	= 2,
पूर्ण;

/* indices पूर्णांकo GLINT_ITR रेजिस्टरs */
#घोषणा ICE_RX_ITR	ICE_IDX_ITR0
#घोषणा ICE_TX_ITR	ICE_IDX_ITR1
#घोषणा ICE_ITR_8K	124
#घोषणा ICE_ITR_20K	50
#घोषणा ICE_ITR_MAX	8160 /* 0x1FE0 */
#घोषणा ICE_DFLT_TX_ITR	ICE_ITR_20K
#घोषणा ICE_DFLT_RX_ITR	ICE_ITR_20K
क्रमागत ice_dynamic_itr अणु
	ITR_STATIC = 0,
	ITR_DYNAMIC = 1
पूर्ण;

#घोषणा ITR_IS_DYNAMIC(rc) ((rc)->itr_mode == ITR_DYNAMIC)
#घोषणा ICE_ITR_GRAN_S		1	/* ITR granularity is always 2us */
#घोषणा ICE_ITR_GRAN_US		BIT(ICE_ITR_GRAN_S)
#घोषणा ICE_ITR_MASK		0x1FFE	/* ITR रेजिस्टर value alignment mask */
#घोषणा ITR_REG_ALIGN(setting)	((setting) & ICE_ITR_MASK)

#घोषणा ICE_DFLT_INTRL	0
#घोषणा ICE_MAX_INTRL	236

#घोषणा ICE_IN_WB_ON_ITR_MODE	255
/* Sets WB_ON_ITR and assumes INTENA bit is alपढ़ोy cleared, which allows
 * setting the MSK_M bit to tell hardware to ignore the INTENA_M bit. Also,
 * set the ग_लिखो-back latency to the usecs passed in.
 */
#घोषणा ICE_GLINT_DYN_CTL_WB_ON_ITR(usecs, itr_idx)	\
	((((usecs) << (GLINT_DYN_CTL_INTERVAL_S - ICE_ITR_GRAN_S)) & \
	  GLINT_DYN_CTL_INTERVAL_M) | \
	 (((itr_idx) << GLINT_DYN_CTL_ITR_INDX_S) & \
	  GLINT_DYN_CTL_ITR_INDX_M) | GLINT_DYN_CTL_INTENA_MSK_M | \
	 GLINT_DYN_CTL_WB_ON_ITR_M)

/* Legacy or Advanced Mode Queue */
#घोषणा ICE_TX_ADVANCED	0
#घोषणा ICE_TX_LEGACY	1

/* descriptor ring, associated with a VSI */
काष्ठा ice_ring अणु
	/* CL1 - 1st cacheline starts here */
	काष्ठा ice_ring *next;		/* poपूर्णांकer to next ring in q_vector */
	व्योम *desc;			/* Descriptor ring memory */
	काष्ठा device *dev;		/* Used क्रम DMA mapping */
	काष्ठा net_device *netdev;	/* netdev ring maps to */
	काष्ठा ice_vsi *vsi;		/* Backreference to associated VSI */
	काष्ठा ice_q_vector *q_vector;	/* Backreference to associated vector */
	u8 __iomem *tail;
	जोड़ अणु
		काष्ठा ice_tx_buf *tx_buf;
		काष्ठा ice_rx_buf *rx_buf;
	पूर्ण;
	/* CL2 - 2nd cacheline starts here */
	u16 q_index;			/* Queue number of ring */
	u16 q_handle;			/* Queue handle per TC */

	u8 ring_active:1;		/* is ring online or not */

	u16 count;			/* Number of descriptors */
	u16 reg_idx;			/* HW रेजिस्टर index of the ring */

	/* used in पूर्णांकerrupt processing */
	u16 next_to_use;
	u16 next_to_clean;
	u16 next_to_alloc;

	/* stats काष्ठाs */
	काष्ठा ice_q_stats	stats;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		काष्ठा ice_txq_stats tx_stats;
		काष्ठा ice_rxq_stats rx_stats;
	पूर्ण;

	काष्ठा rcu_head rcu;		/* to aव्योम race on मुक्त */
	DECLARE_BITMAP(xps_state, ICE_TX_NBITS);	/* XPS Config State */
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xsk_buff_pool *xsk_pool;
	u16 rx_offset;
	/* CL3 - 3rd cacheline starts here */
	काष्ठा xdp_rxq_info xdp_rxq;
	काष्ठा sk_buff *skb;
	/* CLX - the below items are only accessed infrequently and should be
	 * in their own cache line अगर possible
	 */
#घोषणा ICE_TX_FLAGS_RING_XDP		BIT(0)
#घोषणा ICE_RX_FLAGS_RING_BUILD_SKB	BIT(1)
	u8 flags;
	dma_addr_t dma;			/* physical address of ring */
	अचिन्हित पूर्णांक size;		/* length of descriptor ring in bytes */
	u32 txq_teid;			/* Added Tx queue TEID */
	u16 rx_buf_len;
	u8 dcb_tc;			/* Traffic class of ring */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

अटल अंतरभूत bool ice_ring_uses_build_skb(काष्ठा ice_ring *ring)
अणु
	वापस !!(ring->flags & ICE_RX_FLAGS_RING_BUILD_SKB);
पूर्ण

अटल अंतरभूत व्योम ice_set_ring_build_skb_ena(काष्ठा ice_ring *ring)
अणु
	ring->flags |= ICE_RX_FLAGS_RING_BUILD_SKB;
पूर्ण

अटल अंतरभूत व्योम ice_clear_ring_build_skb_ena(काष्ठा ice_ring *ring)
अणु
	ring->flags &= ~ICE_RX_FLAGS_RING_BUILD_SKB;
पूर्ण

अटल अंतरभूत bool ice_ring_is_xdp(काष्ठा ice_ring *ring)
अणु
	वापस !!(ring->flags & ICE_TX_FLAGS_RING_XDP);
पूर्ण

काष्ठा ice_ring_container अणु
	/* head of linked-list of rings */
	काष्ठा ice_ring *ring;
	काष्ठा dim dim;		/* data क्रम net_dim algorithm */
	u16 itr_idx;		/* index in the पूर्णांकerrupt vector */
	/* this matches the maximum number of ITR bits, but in usec
	 * values, so it is shअगरted left one bit (bit zero is ignored)
	 */
	u16 itr_setting:13;
	u16 itr_reserved:2;
	u16 itr_mode:1;
पूर्ण;

काष्ठा ice_coalesce_stored अणु
	u16 itr_tx;
	u16 itr_rx;
	u8 पूर्णांकrl;
	u8 tx_valid;
	u8 rx_valid;
पूर्ण;

/* iterator क्रम handling rings in ring container */
#घोषणा ice_क्रम_each_ring(pos, head) \
	क्रम (pos = (head).ring; pos; pos = pos->next)

अटल अंतरभूत अचिन्हित पूर्णांक ice_rx_pg_order(काष्ठा ice_ring *ring)
अणु
#अगर (PAGE_SIZE < 8192)
	अगर (ring->rx_buf_len > (PAGE_SIZE / 2))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#घोषणा ice_rx_pg_size(_ring) (PAGE_SIZE << ice_rx_pg_order(_ring))

जोड़ ice_32b_rx_flex_desc;

bool ice_alloc_rx_bufs(काष्ठा ice_ring *rxr, u16 cleaned_count);
netdev_tx_t ice_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);
व्योम ice_clean_tx_ring(काष्ठा ice_ring *tx_ring);
व्योम ice_clean_rx_ring(काष्ठा ice_ring *rx_ring);
पूर्णांक ice_setup_tx_ring(काष्ठा ice_ring *tx_ring);
पूर्णांक ice_setup_rx_ring(काष्ठा ice_ring *rx_ring);
व्योम ice_मुक्त_tx_ring(काष्ठा ice_ring *tx_ring);
व्योम ice_मुक्त_rx_ring(काष्ठा ice_ring *rx_ring);
पूर्णांक ice_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक
ice_prgm_fdir_fltr(काष्ठा ice_vsi *vsi, काष्ठा ice_fltr_desc *fdir_desc,
		   u8 *raw_packet);
पूर्णांक ice_clean_rx_irq(काष्ठा ice_ring *rx_ring, पूर्णांक budget);
व्योम ice_clean_ctrl_tx_irq(काष्ठा ice_ring *tx_ring);
#पूर्ण_अगर /* _ICE_TXRX_H_ */
