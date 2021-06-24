<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

/* Common definitions क्रम all Efx net driver code */

#अगर_अघोषित EFX_NET_DRIVER_H
#घोषणा EFX_NET_DRIVER_H

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <net/busy_poll.h>
#समावेश <net/xdp.h>

#समावेश "enum.h"
#समावेश "bitfield.h"
#समावेश "filter.h"

/**************************************************************************
 *
 * Build definitions
 *
 **************************************************************************/

#अगर_घोषित DEBUG
#घोषणा EFX_WARN_ON_ONCE_PARANOID(x) WARN_ON_ONCE(x)
#घोषणा EFX_WARN_ON_PARANOID(x) WARN_ON(x)
#अन्यथा
#घोषणा EFX_WARN_ON_ONCE_PARANOID(x) करो अणुपूर्ण जबतक (0)
#घोषणा EFX_WARN_ON_PARANOID(x) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/**************************************************************************
 *
 * Efx data काष्ठाures
 *
 **************************************************************************/

#घोषणा EFX_MAX_CHANNELS 32U
#घोषणा EFX_MAX_RX_QUEUES EFX_MAX_CHANNELS
#घोषणा EFX_EXTRA_CHANNEL_IOV	0
#घोषणा EFX_EXTRA_CHANNEL_PTP	1
#घोषणा EFX_MAX_EXTRA_CHANNELS	2U

/* Checksum generation is a per-queue option in hardware, so each
 * queue visible to the networking core is backed by two hardware TX
 * queues. */
#घोषणा EFX_MAX_TX_TC		2
#घोषणा EFX_MAX_CORE_TX_QUEUES	(EFX_MAX_TX_TC * EFX_MAX_CHANNELS)
#घोषणा EFX_TXQ_TYPE_OUTER_CSUM	1	/* Outer checksum offload */
#घोषणा EFX_TXQ_TYPE_INNER_CSUM	2	/* Inner checksum offload */
#घोषणा EFX_TXQ_TYPE_HIGHPRI	4	/* High-priority (क्रम TC) */
#घोषणा EFX_TXQ_TYPES		8
/* HIGHPRI is Siena-only, and INNER_CSUM is EF10, so no need क्रम both */
#घोषणा EFX_MAX_TXQ_PER_CHANNEL	4
#घोषणा EFX_MAX_TX_QUEUES	(EFX_MAX_TXQ_PER_CHANNEL * EFX_MAX_CHANNELS)

/* Maximum possible MTU the driver supports */
#घोषणा EFX_MAX_MTU (9 * 1024)

/* Minimum MTU, from RFC791 (IP) */
#घोषणा EFX_MIN_MTU 68

/* Maximum total header length क्रम TSOv2 */
#घोषणा EFX_TSO2_MAX_HDRLEN	208

/* Size of an RX scatter buffer.  Small enough to pack 2 पूर्णांकo a 4K page,
 * and should be a multiple of the cache line size.
 */
#घोषणा EFX_RX_USR_BUF_SIZE	(2048 - 256)

/* If possible, we should ensure cache line alignment at start and end
 * of every buffer.  Otherwise, we just need to ensure 4-byte
 * alignment of the network header.
 */
#अगर NET_IP_ALIGN == 0
#घोषणा EFX_RX_BUF_ALIGNMENT	L1_CACHE_BYTES
#अन्यथा
#घोषणा EFX_RX_BUF_ALIGNMENT	4
#पूर्ण_अगर

/* Non-standard XDP_PACKET_HEADROOM and tailroom to satisfy XDP_REसूचीECT and
 * still fit two standard MTU size packets पूर्णांकo a single 4K page.
 */
#घोषणा EFX_XDP_HEADROOM	128
#घोषणा EFX_XDP_TAILROOM	SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))

/* Forward declare Precision Time Protocol (PTP) support काष्ठाure. */
काष्ठा efx_ptp_data;
काष्ठा hwtstamp_config;

काष्ठा efx_self_tests;

/**
 * काष्ठा efx_buffer - A general-purpose DMA buffer
 * @addr: host base address of the buffer
 * @dma_addr: DMA base address of the buffer
 * @len: Buffer length, in bytes
 *
 * The NIC uses these buffers क्रम its पूर्णांकerrupt status रेजिस्टरs and
 * MAC stats dumps.
 */
काष्ठा efx_buffer अणु
	व्योम *addr;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक len;
पूर्ण;

/**
 * काष्ठा efx_special_buffer - DMA buffer entered पूर्णांकo buffer table
 * @buf: Standard &काष्ठा efx_buffer
 * @index: Buffer index within controller;s buffer table
 * @entries: Number of buffer table entries
 *
 * The NIC has a buffer table that maps buffers of size %EFX_BUF_SIZE.
 * Event and descriptor rings are addressed via one or more buffer
 * table entries (and so can be physically non-contiguous, although we
 * currently करो not take advantage of that).  On Falcon and Siena we
 * have to take care of allocating and initialising the entries
 * ourselves.  On later hardware this is managed by the firmware and
 * @index and @entries are left as 0.
 */
काष्ठा efx_special_buffer अणु
	काष्ठा efx_buffer buf;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक entries;
पूर्ण;

/**
 * काष्ठा efx_tx_buffer - buffer state क्रम a TX descriptor
 * @skb: When @flags & %EFX_TX_BUF_SKB, the associated socket buffer to be
 *	मुक्तd when descriptor completes
 * @xdpf: When @flags & %EFX_TX_BUF_XDP, the XDP frame inक्रमmation; its @data
 *	member is the associated buffer to drop a page reference on.
 * @option: When @flags & %EFX_TX_BUF_OPTION, an EF10-specअगरic option
 *	descriptor.
 * @dma_addr: DMA address of the fragment.
 * @flags: Flags क्रम allocation and DMA mapping type
 * @len: Length of this fragment.
 *	This field is zero when the queue slot is empty.
 * @unmap_len: Length of this fragment to unmap
 * @dma_offset: Offset of @dma_addr from the address of the backing DMA mapping.
 * Only valid अगर @unmap_len != 0.
 */
काष्ठा efx_tx_buffer अणु
	जोड़ अणु
		स्थिर काष्ठा sk_buff *skb;
		काष्ठा xdp_frame *xdpf;
	पूर्ण;
	जोड़ अणु
		efx_qword_t option;    /* EF10 */
		dma_addr_t dma_addr;
	पूर्ण;
	अचिन्हित लघु flags;
	अचिन्हित लघु len;
	अचिन्हित लघु unmap_len;
	अचिन्हित लघु dma_offset;
पूर्ण;
#घोषणा EFX_TX_BUF_CONT		1	/* not last descriptor of packet */
#घोषणा EFX_TX_BUF_SKB		2	/* buffer is last part of skb */
#घोषणा EFX_TX_BUF_MAP_SINGLE	8	/* buffer was mapped with dma_map_single() */
#घोषणा EFX_TX_BUF_OPTION	0x10	/* empty buffer क्रम option descriptor */
#घोषणा EFX_TX_BUF_XDP		0x20	/* buffer was sent with XDP */
#घोषणा EFX_TX_BUF_TSO_V3	0x40	/* empty buffer क्रम a TSO_V3 descriptor */

/**
 * काष्ठा efx_tx_queue - An Efx TX queue
 *
 * This is a ring buffer of TX fragments.
 * Since the TX completion path always executes on the same
 * CPU and the xmit path can operate on dअगरferent CPUs,
 * perक्रमmance is increased by ensuring that the completion
 * path and the xmit path operate on dअगरferent cache lines.
 * This is particularly important अगर the xmit path is always
 * executing on one CPU which is dअगरferent from the completion
 * path.  There is also a cache line क्रम members which are
 * पढ़ो but not written on the fast path.
 *
 * @efx: The associated Efx NIC
 * @queue: DMA queue number
 * @label: Label क्रम TX completion events.
 *	Is our index within @channel->tx_queue array.
 * @type: configuration type of this TX queue.  A biपंचांगask of %EFX_TXQ_TYPE_* flags.
 * @tso_version: Version of TSO in use क्रम this queue.
 * @tso_encap: Is encapsulated TSO supported? Supported in TSOv2 on 8000 series.
 * @channel: The associated channel
 * @core_txq: The networking core TX queue काष्ठाure
 * @buffer: The software buffer ring
 * @cb_page: Array of pages of copy buffers.  Carved up according to
 *	%EFX_TX_CB_ORDER पूर्णांकo %EFX_TX_CB_SIZE-sized chunks.
 * @txd: The hardware descriptor ring
 * @ptr_mask: The size of the ring minus 1.
 * @piobuf: PIO buffer region क्रम this TX queue (shared with its partner).
 *	Size of the region is efx_piobuf_size.
 * @piobuf_offset: Buffer offset to be specअगरied in PIO descriptors
 * @initialised: Has hardware queue been initialised?
 * @बारtamping: Is बारtamping enabled क्रम this channel?
 * @xdp_tx: Is this an XDP tx queue?
 * @पढ़ो_count: Current पढ़ो poपूर्णांकer.
 *	This is the number of buffers that have been हटाओd from both rings.
 * @old_ग_लिखो_count: The value of @ग_लिखो_count when last checked.
 *	This is here क्रम perक्रमmance reasons.  The xmit path will
 *	only get the up-to-date value of @ग_लिखो_count अगर this
 *	variable indicates that the queue is empty.  This is to
 *	aव्योम cache-line ping-pong between the xmit path and the
 *	completion path.
 * @merge_events: Number of TX merged completion events
 * @completed_बारtamp_major: Top part of the most recent tx बारtamp.
 * @completed_बारtamp_minor: Low part of the most recent tx बारtamp.
 * @insert_count: Current insert poपूर्णांकer
 *	This is the number of buffers that have been added to the
 *	software ring.
 * @ग_लिखो_count: Current ग_लिखो poपूर्णांकer
 *	This is the number of buffers that have been added to the
 *	hardware ring.
 * @packet_ग_लिखो_count: Completable ग_लिखो poपूर्णांकer
 *	This is the ग_लिखो poपूर्णांकer of the last packet written.
 *	Normally this will equal @ग_लिखो_count, but as option descriptors
 *	करोn't produce completion events, they won't update this.
 *	Filled in अगरf @efx->type->option_descriptors; only used क्रम PIO.
 *	Thus, this is written and used on EF10, and neither on farch.
 * @old_पढ़ो_count: The value of पढ़ो_count when last checked.
 *	This is here क्रम perक्रमmance reasons.  The xmit path will
 *	only get the up-to-date value of पढ़ो_count अगर this
 *	variable indicates that the queue is full.  This is to
 *	aव्योम cache-line ping-pong between the xmit path and the
 *	completion path.
 * @tso_bursts: Number of बार TSO xmit invoked by kernel
 * @tso_दीर्घ_headers: Number of packets with headers too दीर्घ क्रम standard
 *	blocks
 * @tso_packets: Number of packets via the TSO xmit path
 * @tso_fallbacks: Number of बार TSO fallback used
 * @pushes: Number of बार the TX push feature has been used
 * @pio_packets: Number of बार the TX PIO feature has been used
 * @xmit_pending: Are any packets रुकोing to be pushed to the NIC
 * @cb_packets: Number of बार the TX copyअवरोध feature has been used
 * @notअगरy_count: Count of notअगरied descriptors to the NIC
 * @empty_पढ़ो_count: If the completion path has seen the queue as empty
 *	and the transmission path has not yet checked this, the value of
 *	@पढ़ो_count bitwise-added to %EFX_EMPTY_COUNT_VALID; otherwise 0.
 */
काष्ठा efx_tx_queue अणु
	/* Members which करोn't change on the fast path */
	काष्ठा efx_nic *efx ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक queue;
	अचिन्हित पूर्णांक label;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक tso_version;
	bool tso_encap;
	काष्ठा efx_channel *channel;
	काष्ठा netdev_queue *core_txq;
	काष्ठा efx_tx_buffer *buffer;
	काष्ठा efx_buffer *cb_page;
	काष्ठा efx_special_buffer txd;
	अचिन्हित पूर्णांक ptr_mask;
	व्योम __iomem *piobuf;
	अचिन्हित पूर्णांक piobuf_offset;
	bool initialised;
	bool बारtamping;
	bool xdp_tx;

	/* Members used मुख्यly on the completion path */
	अचिन्हित पूर्णांक पढ़ो_count ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक old_ग_लिखो_count;
	अचिन्हित पूर्णांक merge_events;
	अचिन्हित पूर्णांक bytes_compl;
	अचिन्हित पूर्णांक pkts_compl;
	u32 completed_बारtamp_major;
	u32 completed_बारtamp_minor;

	/* Members used only on the xmit path */
	अचिन्हित पूर्णांक insert_count ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक ग_लिखो_count;
	अचिन्हित पूर्णांक packet_ग_लिखो_count;
	अचिन्हित पूर्णांक old_पढ़ो_count;
	अचिन्हित पूर्णांक tso_bursts;
	अचिन्हित पूर्णांक tso_दीर्घ_headers;
	अचिन्हित पूर्णांक tso_packets;
	अचिन्हित पूर्णांक tso_fallbacks;
	अचिन्हित पूर्णांक pushes;
	अचिन्हित पूर्णांक pio_packets;
	bool xmit_pending;
	अचिन्हित पूर्णांक cb_packets;
	अचिन्हित पूर्णांक notअगरy_count;
	/* Statistics to supplement MAC stats */
	अचिन्हित दीर्घ tx_packets;

	/* Members shared between paths and someबार updated */
	अचिन्हित पूर्णांक empty_पढ़ो_count ____cacheline_aligned_in_smp;
#घोषणा EFX_EMPTY_COUNT_VALID 0x80000000
	atomic_t flush_outstanding;
पूर्ण;

#घोषणा EFX_TX_CB_ORDER	7
#घोषणा EFX_TX_CB_SIZE	(1 << EFX_TX_CB_ORDER) - NET_IP_ALIGN

/**
 * काष्ठा efx_rx_buffer - An Efx RX data buffer
 * @dma_addr: DMA base address of the buffer
 * @page: The associated page buffer.
 *	Will be %शून्य अगर the buffer slot is currently मुक्त.
 * @page_offset: If pending: offset in @page of DMA base address.
 *	If completed: offset in @page of Ethernet header.
 * @len: If pending: length क्रम DMA descriptor.
 *	If completed: received length, excluding hash prefix.
 * @flags: Flags क्रम buffer and packet state.  These are only set on the
 *	first buffer of a scattered packet.
 */
काष्ठा efx_rx_buffer अणु
	dma_addr_t dma_addr;
	काष्ठा page *page;
	u16 page_offset;
	u16 len;
	u16 flags;
पूर्ण;
#घोषणा EFX_RX_BUF_LAST_IN_PAGE	0x0001
#घोषणा EFX_RX_PKT_CSUMMED	0x0002
#घोषणा EFX_RX_PKT_DISCARD	0x0004
#घोषणा EFX_RX_PKT_TCP		0x0040
#घोषणा EFX_RX_PKT_PREFIX_LEN	0x0080	/* length is in prefix only */
#घोषणा EFX_RX_PKT_CSUM_LEVEL	0x0200

/**
 * काष्ठा efx_rx_page_state - Page-based rx buffer state
 *
 * Inserted at the start of every page allocated क्रम receive buffers.
 * Used to facilitate sharing dma mappings between recycled rx buffers
 * and those passed up to the kernel.
 *
 * @dma_addr: The dma address of this page.
 */
काष्ठा efx_rx_page_state अणु
	dma_addr_t dma_addr;

	अचिन्हित पूर्णांक __pad[] ____cacheline_aligned;
पूर्ण;

/**
 * काष्ठा efx_rx_queue - An Efx RX queue
 * @efx: The associated Efx NIC
 * @core_index:  Index of network core RX queue.  Will be >= 0 अगरf this
 *	is associated with a real RX queue.
 * @buffer: The software buffer ring
 * @rxd: The hardware descriptor ring
 * @ptr_mask: The size of the ring minus 1.
 * @refill_enabled: Enable refill whenever fill level is low
 * @flush_pending: Set when a RX flush is pending. Has the same lअगरeसमय as
 *	@rxq_flush_pending.
 * @added_count: Number of buffers added to the receive queue.
 * @notअगरied_count: Number of buffers given to NIC (<= @added_count).
 * @हटाओd_count: Number of buffers हटाओd from the receive queue.
 * @scatter_n: Used by NIC specअगरic receive code.
 * @scatter_len: Used by NIC specअगरic receive code.
 * @page_ring: The ring to store DMA mapped pages क्रम reuse.
 * @page_add: Counter to calculate the ग_लिखो poपूर्णांकer क्रम the recycle ring.
 * @page_हटाओ: Counter to calculate the पढ़ो poपूर्णांकer क्रम the recycle ring.
 * @page_recycle_count: The number of pages that have been recycled.
 * @page_recycle_failed: The number of pages that couldn't be recycled because
 *      the kernel still held a reference to them.
 * @page_recycle_full: The number of pages that were released because the
 *      recycle ring was full.
 * @page_ptr_mask: The number of pages in the RX recycle ring minus 1.
 * @max_fill: RX descriptor maximum fill level (<= ring size)
 * @fast_fill_trigger: RX descriptor fill level that will trigger a fast fill
 *	(<= @max_fill)
 * @min_fill: RX descriptor minimum non-zero fill level.
 *	This records the minimum fill level observed when a ring
 *	refill was triggered.
 * @recycle_count: RX buffer recycle counter.
 * @slow_fill: Timer used to defer efx_nic_generate_fill_event().
 * @xdp_rxq_info: XDP specअगरic RX queue inक्रमmation.
 * @xdp_rxq_info_valid: Is xdp_rxq_info valid data?.
 */
काष्ठा efx_rx_queue अणु
	काष्ठा efx_nic *efx;
	पूर्णांक core_index;
	काष्ठा efx_rx_buffer *buffer;
	काष्ठा efx_special_buffer rxd;
	अचिन्हित पूर्णांक ptr_mask;
	bool refill_enabled;
	bool flush_pending;

	अचिन्हित पूर्णांक added_count;
	अचिन्हित पूर्णांक notअगरied_count;
	अचिन्हित पूर्णांक हटाओd_count;
	अचिन्हित पूर्णांक scatter_n;
	अचिन्हित पूर्णांक scatter_len;
	काष्ठा page **page_ring;
	अचिन्हित पूर्णांक page_add;
	अचिन्हित पूर्णांक page_हटाओ;
	अचिन्हित पूर्णांक page_recycle_count;
	अचिन्हित पूर्णांक page_recycle_failed;
	अचिन्हित पूर्णांक page_recycle_full;
	अचिन्हित पूर्णांक page_ptr_mask;
	अचिन्हित पूर्णांक max_fill;
	अचिन्हित पूर्णांक fast_fill_trigger;
	अचिन्हित पूर्णांक min_fill;
	अचिन्हित पूर्णांक min_overfill;
	अचिन्हित पूर्णांक recycle_count;
	काष्ठा समयr_list slow_fill;
	अचिन्हित पूर्णांक slow_fill_count;
	/* Statistics to supplement MAC stats */
	अचिन्हित दीर्घ rx_packets;
	काष्ठा xdp_rxq_info xdp_rxq_info;
	bool xdp_rxq_info_valid;
पूर्ण;

क्रमागत efx_sync_events_state अणु
	SYNC_EVENTS_DISABLED = 0,
	SYNC_EVENTS_QUIESCENT,
	SYNC_EVENTS_REQUESTED,
	SYNC_EVENTS_VALID,
पूर्ण;

/**
 * काष्ठा efx_channel - An Efx channel
 *
 * A channel comprises an event queue, at least one TX queue, at least
 * one RX queue, and an associated tasklet क्रम processing the event
 * queue.
 *
 * @efx: Associated Efx NIC
 * @channel: Channel instance number
 * @type: Channel type definition
 * @eventq_init: Event queue initialised flag
 * @enabled: Channel enabled indicator
 * @irq: IRQ number (MSI and MSI-X only)
 * @irq_moderation_us: IRQ moderation value (in microseconds)
 * @napi_dev: Net device used with NAPI
 * @napi_str: NAPI control काष्ठाure
 * @state: state क्रम NAPI vs busy polling
 * @state_lock: lock protecting @state
 * @eventq: Event queue buffer
 * @eventq_mask: Event queue poपूर्णांकer mask
 * @eventq_पढ़ो_ptr: Event queue पढ़ो poपूर्णांकer
 * @event_test_cpu: Last CPU to handle पूर्णांकerrupt or test event क्रम this channel
 * @irq_count: Number of IRQs since last adaptive moderation decision
 * @irq_mod_score: IRQ moderation score
 * @rfs_filter_count: number of accelerated RFS filters currently in place;
 *	equals the count of @rps_flow_id slots filled
 * @rfs_last_expiry: value of jअगरfies last समय some accelerated RFS filters
 *	were checked क्रम expiry
 * @rfs_expire_index: next accelerated RFS filter ID to check क्रम expiry
 * @n_rfs_succeeded: number of successful accelerated RFS filter insertions
 * @n_rfs_failed: number of failed accelerated RFS filter insertions
 * @filter_work: Work item क्रम efx_filter_rfs_expire()
 * @rps_flow_id: Flow IDs of filters allocated क्रम accelerated RFS,
 *      indexed by filter ID
 * @n_rx_tobe_disc: Count of RX_TOBE_DISC errors
 * @n_rx_ip_hdr_chksum_err: Count of RX IP header checksum errors
 * @n_rx_tcp_udp_chksum_err: Count of RX TCP and UDP checksum errors
 * @n_rx_mcast_mismatch: Count of unmatched multicast frames
 * @n_rx_frm_trunc: Count of RX_FRM_TRUNC errors
 * @n_rx_overlength: Count of RX_OVERLENGTH errors
 * @n_skbuff_leaks: Count of skbuffs leaked due to RX overrun
 * @n_rx_nodesc_trunc: Number of RX packets truncated and then dropped due to
 *	lack of descriptors
 * @n_rx_merge_events: Number of RX merged completion events
 * @n_rx_merge_packets: Number of RX packets completed by merged events
 * @n_rx_xdp_drops: Count of RX packets पूर्णांकentionally dropped due to XDP
 * @n_rx_xdp_bad_drops: Count of RX packets dropped due to XDP errors
 * @n_rx_xdp_tx: Count of RX packets retransmitted due to XDP
 * @n_rx_xdp_redirect: Count of RX packets redirected to a dअगरferent NIC by XDP
 * @rx_pkt_n_frags: Number of fragments in next packet to be delivered by
 *	__efx_rx_packet(), or zero अगर there is none
 * @rx_pkt_index: Ring index of first buffer क्रम next packet to be delivered
 *	by __efx_rx_packet(), अगर @rx_pkt_n_frags != 0
 * @rx_list: list of SKBs from current RX, aरुकोing processing
 * @rx_queue: RX queue क्रम this channel
 * @tx_queue: TX queues क्रम this channel
 * @tx_queue_by_type: poपूर्णांकers पूर्णांकo @tx_queue, or %शून्य, indexed by txq type
 * @sync_events_state: Current state of sync events on this channel
 * @sync_बारtamp_major: Major part of the last ptp sync event
 * @sync_बारtamp_minor: Minor part of the last ptp sync event
 */
काष्ठा efx_channel अणु
	काष्ठा efx_nic *efx;
	पूर्णांक channel;
	स्थिर काष्ठा efx_channel_type *type;
	bool eventq_init;
	bool enabled;
	पूर्णांक irq;
	अचिन्हित पूर्णांक irq_moderation_us;
	काष्ठा net_device *napi_dev;
	काष्ठा napi_काष्ठा napi_str;
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित दीर्घ busy_poll_state;
#पूर्ण_अगर
	काष्ठा efx_special_buffer eventq;
	अचिन्हित पूर्णांक eventq_mask;
	अचिन्हित पूर्णांक eventq_पढ़ो_ptr;
	पूर्णांक event_test_cpu;

	अचिन्हित पूर्णांक irq_count;
	अचिन्हित पूर्णांक irq_mod_score;
#अगर_घोषित CONFIG_RFS_ACCEL
	अचिन्हित पूर्णांक rfs_filter_count;
	अचिन्हित पूर्णांक rfs_last_expiry;
	अचिन्हित पूर्णांक rfs_expire_index;
	अचिन्हित पूर्णांक n_rfs_succeeded;
	अचिन्हित पूर्णांक n_rfs_failed;
	काष्ठा delayed_work filter_work;
#घोषणा RPS_FLOW_ID_INVALID 0xFFFFFFFF
	u32 *rps_flow_id;
#पूर्ण_अगर

	अचिन्हित पूर्णांक n_rx_tobe_disc;
	अचिन्हित पूर्णांक n_rx_ip_hdr_chksum_err;
	अचिन्हित पूर्णांक n_rx_tcp_udp_chksum_err;
	अचिन्हित पूर्णांक n_rx_outer_ip_hdr_chksum_err;
	अचिन्हित पूर्णांक n_rx_outer_tcp_udp_chksum_err;
	अचिन्हित पूर्णांक n_rx_inner_ip_hdr_chksum_err;
	अचिन्हित पूर्णांक n_rx_inner_tcp_udp_chksum_err;
	अचिन्हित पूर्णांक n_rx_eth_crc_err;
	अचिन्हित पूर्णांक n_rx_mcast_mismatch;
	अचिन्हित पूर्णांक n_rx_frm_trunc;
	अचिन्हित पूर्णांक n_rx_overlength;
	अचिन्हित पूर्णांक n_skbuff_leaks;
	अचिन्हित पूर्णांक n_rx_nodesc_trunc;
	अचिन्हित पूर्णांक n_rx_merge_events;
	अचिन्हित पूर्णांक n_rx_merge_packets;
	अचिन्हित पूर्णांक n_rx_xdp_drops;
	अचिन्हित पूर्णांक n_rx_xdp_bad_drops;
	अचिन्हित पूर्णांक n_rx_xdp_tx;
	अचिन्हित पूर्णांक n_rx_xdp_redirect;

	अचिन्हित पूर्णांक rx_pkt_n_frags;
	अचिन्हित पूर्णांक rx_pkt_index;

	काष्ठा list_head *rx_list;

	काष्ठा efx_rx_queue rx_queue;
	काष्ठा efx_tx_queue tx_queue[EFX_MAX_TXQ_PER_CHANNEL];
	काष्ठा efx_tx_queue *tx_queue_by_type[EFX_TXQ_TYPES];

	क्रमागत efx_sync_events_state sync_events_state;
	u32 sync_बारtamp_major;
	u32 sync_बारtamp_minor;
पूर्ण;

/**
 * काष्ठा efx_msi_context - Context क्रम each MSI
 * @efx: The associated NIC
 * @index: Index of the channel/IRQ
 * @name: Name of the channel/IRQ
 *
 * Unlike &काष्ठा efx_channel, this is never पुनः_स्मृतिated and is always
 * safe क्रम the IRQ handler to access.
 */
काष्ठा efx_msi_context अणु
	काष्ठा efx_nic *efx;
	अचिन्हित पूर्णांक index;
	अक्षर name[IFNAMSIZ + 6];
पूर्ण;

/**
 * काष्ठा efx_channel_type - distinguishes traffic and extra channels
 * @handle_no_channel: Handle failure to allocate an extra channel
 * @pre_probe: Set up extra state prior to initialisation
 * @post_हटाओ: Tear करोwn extra state after finalisation, अगर allocated.
 *	May be called on channels that have not been probed.
 * @get_name: Generate the channel's name (used क्रम its IRQ handler)
 * @copy: Copy the channel state prior to पुनः_स्मृतिation.  May be %शून्य अगर
 *	पुनः_स्मृतिation is not supported.
 * @receive_skb: Handle an skb पढ़ोy to be passed to netअगर_receive_skb()
 * @want_txqs: Determine whether this channel should have TX queues
 *	created.  If %शून्य, TX queues are not created.
 * @keep_eventq: Flag क्रम whether event queue should be kept initialised
 *	जबतक the device is stopped
 * @want_pio: Flag क्रम whether PIO buffers should be linked to this
 *	channel's TX queues.
 */
काष्ठा efx_channel_type अणु
	व्योम (*handle_no_channel)(काष्ठा efx_nic *);
	पूर्णांक (*pre_probe)(काष्ठा efx_channel *);
	व्योम (*post_हटाओ)(काष्ठा efx_channel *);
	व्योम (*get_name)(काष्ठा efx_channel *, अक्षर *buf, माप_प्रकार len);
	काष्ठा efx_channel *(*copy)(स्थिर काष्ठा efx_channel *);
	bool (*receive_skb)(काष्ठा efx_channel *, काष्ठा sk_buff *);
	bool (*want_txqs)(काष्ठा efx_channel *);
	bool keep_eventq;
	bool want_pio;
पूर्ण;

क्रमागत efx_led_mode अणु
	EFX_LED_OFF	= 0,
	EFX_LED_ON	= 1,
	EFX_LED_DEFAULT	= 2
पूर्ण;

#घोषणा STRING_TABLE_LOOKUP(val, member) \
	((val) < member ## _max) ? member ## _names[val] : "(invalid)"

बाह्य स्थिर अक्षर *स्थिर efx_loopback_mode_names[];
बाह्य स्थिर अचिन्हित पूर्णांक efx_loopback_mode_max;
#घोषणा LOOPBACK_MODE(efx) \
	STRING_TABLE_LOOKUP((efx)->loopback_mode, efx_loopback_mode)

बाह्य स्थिर अक्षर *स्थिर efx_reset_type_names[];
बाह्य स्थिर अचिन्हित पूर्णांक efx_reset_type_max;
#घोषणा RESET_TYPE(type) \
	STRING_TABLE_LOOKUP(type, efx_reset_type)

क्रमागत efx_पूर्णांक_mode अणु
	/* Be careful अगर altering to correct macro below */
	EFX_INT_MODE_MSIX = 0,
	EFX_INT_MODE_MSI = 1,
	EFX_INT_MODE_LEGACY = 2,
	EFX_INT_MODE_MAX	/* Insert any new items beक्रमe this */
पूर्ण;
#घोषणा EFX_INT_MODE_USE_MSI(x) (((x)->पूर्णांकerrupt_mode) <= EFX_INT_MODE_MSI)

क्रमागत nic_state अणु
	STATE_UNINIT = 0,	/* device being probed/हटाओd or is frozen */
	STATE_READY = 1,	/* hardware पढ़ोy and netdev रेजिस्टरed */
	STATE_DISABLED = 2,	/* device disabled due to hardware errors */
	STATE_RECOVERY = 3,	/* device recovering from PCI error */
पूर्ण;

/* Forward declaration */
काष्ठा efx_nic;

/* Pseuकरो bit-mask flow control field */
#घोषणा EFX_FC_RX	FLOW_CTRL_RX
#घोषणा EFX_FC_TX	FLOW_CTRL_TX
#घोषणा EFX_FC_AUTO	4

/**
 * काष्ठा efx_link_state - Current state of the link
 * @up: Link is up
 * @fd: Link is full-duplex
 * @fc: Actual flow control flags
 * @speed: Link speed (Mbps)
 */
काष्ठा efx_link_state अणु
	bool up;
	bool fd;
	u8 fc;
	अचिन्हित पूर्णांक speed;
पूर्ण;

अटल अंतरभूत bool efx_link_state_equal(स्थिर काष्ठा efx_link_state *left,
					स्थिर काष्ठा efx_link_state *right)
अणु
	वापस left->up == right->up && left->fd == right->fd &&
		left->fc == right->fc && left->speed == right->speed;
पूर्ण

/**
 * क्रमागत efx_phy_mode - PHY operating mode flags
 * @PHY_MODE_NORMAL: on and should pass traffic
 * @PHY_MODE_TX_DISABLED: on with TX disabled
 * @PHY_MODE_LOW_POWER: set to low घातer through MDIO
 * @PHY_MODE_OFF: चयनed off through बाह्यal control
 * @PHY_MODE_SPECIAL: on but will not pass traffic
 */
क्रमागत efx_phy_mode अणु
	PHY_MODE_NORMAL		= 0,
	PHY_MODE_TX_DISABLED	= 1,
	PHY_MODE_LOW_POWER	= 2,
	PHY_MODE_OFF		= 4,
	PHY_MODE_SPECIAL	= 8,
पूर्ण;

अटल अंतरभूत bool efx_phy_mode_disabled(क्रमागत efx_phy_mode mode)
अणु
	वापस !!(mode & ~PHY_MODE_TX_DISABLED);
पूर्ण

/**
 * काष्ठा efx_hw_stat_desc - Description of a hardware statistic
 * @name: Name of the statistic as visible through ethtool, or %शून्य अगर
 *	it should not be exposed
 * @dma_width: Width in bits (0 क्रम non-DMA statistics)
 * @offset: Offset within stats (ignored क्रम non-DMA statistics)
 */
काष्ठा efx_hw_stat_desc अणु
	स्थिर अक्षर *name;
	u16 dma_width;
	u16 offset;
पूर्ण;

/* Number of bits used in a multicast filter hash address */
#घोषणा EFX_MCAST_HASH_BITS 8

/* Number of (single-bit) entries in a multicast filter hash */
#घोषणा EFX_MCAST_HASH_ENTRIES (1 << EFX_MCAST_HASH_BITS)

/* An Efx multicast filter hash */
जोड़ efx_multicast_hash अणु
	u8 byte[EFX_MCAST_HASH_ENTRIES / 8];
	efx_oword_t oword[EFX_MCAST_HASH_ENTRIES / माप(efx_oword_t) / 8];
पूर्ण;

काष्ठा vfdi_status;

/* The reserved RSS context value */
#घोषणा EFX_MCDI_RSS_CONTEXT_INVALID	0xffffffff
/**
 * काष्ठा efx_rss_context - A user-defined RSS context क्रम filtering
 * @list: node of linked list on which this काष्ठा is stored
 * @context_id: the RSS_CONTEXT_ID वापसed by MC firmware, or
 *	%EFX_MCDI_RSS_CONTEXT_INVALID अगर this context is not present on the NIC.
 *	For Siena, 0 अगर RSS is active, अन्यथा %EFX_MCDI_RSS_CONTEXT_INVALID.
 * @user_id: the rss_context ID exposed to userspace over ethtool.
 * @rx_hash_udp_4tuple: UDP 4-tuple hashing enabled
 * @rx_hash_key: Toeplitz hash key क्रम this RSS context
 * @indir_table: Indirection table क्रम this RSS context
 */
काष्ठा efx_rss_context अणु
	काष्ठा list_head list;
	u32 context_id;
	u32 user_id;
	bool rx_hash_udp_4tuple;
	u8 rx_hash_key[40];
	u32 rx_indir_table[128];
पूर्ण;

#अगर_घोषित CONFIG_RFS_ACCEL
/* Order of these is important, since filter_id >= %EFX_ARFS_FILTER_ID_PENDING
 * is used to test अगर filter करोes or will exist.
 */
#घोषणा EFX_ARFS_FILTER_ID_PENDING	-1
#घोषणा EFX_ARFS_FILTER_ID_ERROR	-2
#घोषणा EFX_ARFS_FILTER_ID_REMOVING	-3
/**
 * काष्ठा efx_arfs_rule - record of an ARFS filter and its IDs
 * @node: linkage पूर्णांकo hash table
 * @spec: details of the filter (used as key क्रम hash table).  Use efx->type to
 *	determine which member to use.
 * @rxq_index: channel to which the filter will steer traffic.
 * @arfs_id: filter ID which was वापसed to ARFS
 * @filter_id: index in software filter table.  May be
 *	%EFX_ARFS_FILTER_ID_PENDING अगर filter was not inserted yet,
 *	%EFX_ARFS_FILTER_ID_ERROR अगर filter insertion failed, or
 *	%EFX_ARFS_FILTER_ID_REMOVING अगर expiry is currently removing the filter.
 */
काष्ठा efx_arfs_rule अणु
	काष्ठा hlist_node node;
	काष्ठा efx_filter_spec spec;
	u16 rxq_index;
	u16 arfs_id;
	s32 filter_id;
पूर्ण;

/* Size chosen so that the table is one page (4kB) */
#घोषणा EFX_ARFS_HASH_TABLE_SIZE	512

/**
 * काष्ठा efx_async_filter_insertion - Request to asynchronously insert a filter
 * @net_dev: Reference to the netdevice
 * @spec: The filter to insert
 * @work: Workitem क्रम this request
 * @rxq_index: Identअगरies the channel क्रम which this request was made
 * @flow_id: Identअगरies the kernel-side flow क्रम which this request was made
 */
काष्ठा efx_async_filter_insertion अणु
	काष्ठा net_device *net_dev;
	काष्ठा efx_filter_spec spec;
	काष्ठा work_काष्ठा work;
	u16 rxq_index;
	u32 flow_id;
पूर्ण;

/* Maximum number of ARFS workitems that may be in flight on an efx_nic */
#घोषणा EFX_RPS_MAX_IN_FLIGHT	8
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

/**
 * काष्ठा efx_nic - an Efx NIC
 * @name: Device name (net device name or bus id beक्रमe net device रेजिस्टरed)
 * @pci_dev: The PCI device
 * @node: List node क्रम मुख्यtaning primary/secondary function lists
 * @primary: &काष्ठा efx_nic instance क्रम the primary function of this
 *	controller.  May be the same काष्ठाure, and may be %शून्य अगर no
 *	primary function is bound.  Serialised by rtnl_lock.
 * @secondary_list: List of &काष्ठा efx_nic instances क्रम the secondary PCI
 *	functions of the controller, अगर this is क्रम the primary function.
 *	Serialised by rtnl_lock.
 * @type: Controller type attributes
 * @legacy_irq: IRQ number
 * @workqueue: Workqueue क्रम port reconfigures and the HW monitor.
 *	Work items करो not hold and must not acquire RTNL.
 * @workqueue_name: Name of workqueue
 * @reset_work: Scheduled reset workitem
 * @membase_phys: Memory BAR value as physical address
 * @membase: Memory BAR value
 * @vi_stride: step between per-VI रेजिस्टरs / memory regions
 * @पूर्णांकerrupt_mode: Interrupt mode
 * @समयr_quantum_ns: Interrupt समयr quantum, in nanoseconds
 * @समयr_max_ns: Interrupt समयr maximum value, in nanoseconds
 * @irq_rx_adaptive: Adaptive IRQ moderation enabled क्रम RX event queues
 * @irqs_hooked: Channel पूर्णांकerrupts are hooked
 * @irq_rx_mod_step_us: Step size क्रम IRQ moderation क्रम RX event queues
 * @irq_rx_moderation_us: IRQ moderation समय क्रम RX event queues
 * @msg_enable: Log message enable flags
 * @state: Device state number (%STATE_*). Serialised by the rtnl_lock.
 * @reset_pending: Biपंचांगask क्रम pending resets
 * @tx_queue: TX DMA queues
 * @rx_queue: RX DMA queues
 * @channel: Channels
 * @msi_context: Context क्रम each MSI
 * @extra_channel_types: Types of extra (non-traffic) channels that
 *	should be allocated क्रम this NIC
 * @xdp_tx_queue_count: Number of entries in %xdp_tx_queues.
 * @xdp_tx_queues: Array of poपूर्णांकers to tx queues used क्रम XDP transmit.
 * @rxq_entries: Size of receive queues requested by user.
 * @txq_entries: Size of transmit queues requested by user.
 * @txq_stop_thresh: TX queue fill level at or above which we stop it.
 * @txq_wake_thresh: TX queue fill level at or below which we wake it.
 * @tx_dc_base: Base qword address in SRAM of TX queue descriptor caches
 * @rx_dc_base: Base qword address in SRAM of RX queue descriptor caches
 * @sram_lim_qw: Qword address limit of SRAM
 * @next_buffer_table: First available buffer table id
 * @n_channels: Number of channels in use
 * @n_rx_channels: Number of channels used क्रम RX (= number of RX queues)
 * @n_tx_channels: Number of channels used क्रम TX
 * @n_extra_tx_channels: Number of extra channels with TX queues
 * @tx_queues_per_channel: number of TX queues probed on each channel
 * @n_xdp_channels: Number of channels used क्रम XDP TX
 * @xdp_channel_offset: Offset of zeroth channel used क्रम XPD TX.
 * @xdp_tx_per_channel: Max number of TX queues on an XDP TX channel.
 * @rx_ip_align: RX DMA address offset to have IP header aligned in
 *	in accordance with NET_IP_ALIGN
 * @rx_dma_len: Current maximum RX DMA length
 * @rx_buffer_order: Order (log2) of number of pages क्रम each RX buffer
 * @rx_buffer_truesize: Amortised allocation size of an RX buffer,
 *	क्रम use in sk_buff::truesize
 * @rx_prefix_size: Size of RX prefix beक्रमe packet data
 * @rx_packet_hash_offset: Offset of RX flow hash from start of packet data
 *	(valid only अगर @rx_prefix_size != 0; always negative)
 * @rx_packet_len_offset: Offset of RX packet length from start of packet data
 *	(valid only क्रम NICs that set %EFX_RX_PKT_PREFIX_LEN; always negative)
 * @rx_packet_ts_offset: Offset of बारtamp from start of packet data
 *	(valid only अगर channel->sync_बारtamps_enabled; always negative)
 * @rx_scatter: Scatter mode enabled क्रम receives
 * @rss_context: Main RSS context.  Its @list member is the head of the list of
 *	RSS contexts created by user requests
 * @rss_lock: Protects custom RSS context software state in @rss_context.list
 * @vport_id: The function's vport ID, only relevant क्रम PFs
 * @पूर्णांक_error_count: Number of पूर्णांकernal errors seen recently
 * @पूर्णांक_error_expire: Time at which error count will be expired
 * @must_पुनः_स्मृति_vis: Flag: VIs have yet to be पुनः_स्मृतिated after MC reboot
 * @irq_soft_enabled: Are IRQs soft-enabled? If not, IRQ handler will
 *	acknowledge but करो nothing अन्यथा.
 * @irq_status: Interrupt status buffer
 * @irq_zero_count: Number of legacy IRQs seen with queue flags == 0
 * @irq_level: IRQ level/index क्रम IRQs not triggered by an event queue
 * @selftest_work: Work item क्रम asynchronous self-test
 * @mtd_list: List of MTDs attached to the NIC
 * @nic_data: Hardware dependent state
 * @mcdi: Management-Controller-to-Driver Interface state
 * @mac_lock: MAC access lock. Protects @port_enabled, @phy_mode,
 *	efx_monitor() and efx_reconfigure_port()
 * @port_enabled: Port enabled indicator.
 *	Serialises efx_stop_all(), efx_start_all(), efx_monitor() and
 *	efx_mac_work() with kernel पूर्णांकerfaces. Safe to पढ़ो under any
 *	one of the rtnl_lock, mac_lock, or netअगर_tx_lock, but all three must
 *	be held to modअगरy it.
 * @port_initialized: Port initialized?
 * @net_dev: Operating प्रणाली network device. Consider holding the rtnl lock
 * @fixed_features: Features which cannot be turned off
 * @num_mac_stats: Number of MAC stats reported by firmware (MAC_STATS_NUM_STATS
 *	field of %MC_CMD_GET_CAPABILITIES_V4 response, or %MC_CMD_MAC_NSTATS)
 * @stats_buffer: DMA buffer क्रम statistics
 * @phy_type: PHY type
 * @phy_data: PHY निजी data (including PHY-specअगरic stats)
 * @mdio: PHY MDIO पूर्णांकerface
 * @mdio_bus: PHY MDIO bus ID (only used by Siena)
 * @phy_mode: PHY operating mode. Serialised by @mac_lock.
 * @link_advertising: Autonegotiation advertising flags
 * @fec_config: Forward Error Correction configuration flags.  For bit positions
 *	see &क्रमागत ethtool_fec_config_bits.
 * @link_state: Current state of the link
 * @n_link_state_changes: Number of बार the link has changed state
 * @unicast_filter: Flag क्रम Falcon-arch simple unicast filter.
 *	Protected by @mac_lock.
 * @multicast_hash: Multicast hash table क्रम Falcon-arch.
 *	Protected by @mac_lock.
 * @wanted_fc: Wanted flow control flags
 * @fc_disable: When non-zero flow control is disabled. Typically used to
 *	ensure that network back pressure करोesn't delay dma queue flushes.
 *	Serialised by the rtnl lock.
 * @mac_work: Work item क्रम changing MAC promiscuity and multicast hash
 * @loopback_mode: Loopback status
 * @loopback_modes: Supported loopback mode biपंचांगask
 * @loopback_selftest: Offline self-test निजी state
 * @xdp_prog: Current XDP programme क्रम this पूर्णांकerface
 * @filter_sem: Filter table rw_semaphore, protects existence of @filter_state
 * @filter_state: Architecture-dependent filter table state
 * @rps_mutex: Protects RPS state of all channels
 * @rps_slot_map: biपंचांगap of in-flight entries in @rps_slot
 * @rps_slot: array of ARFS insertion requests क्रम efx_filter_rfs_work()
 * @rps_hash_lock: Protects ARFS filter mapping state (@rps_hash_table and
 *	@rps_next_id).
 * @rps_hash_table: Mapping between ARFS filters and their various IDs
 * @rps_next_id: next arfs_id क्रम an ARFS filter
 * @active_queues: Count of RX and TX queues that haven't been flushed and drained.
 * @rxq_flush_pending: Count of number of receive queues that need to be flushed.
 *	Decremented when the efx_flush_rx_queue() is called.
 * @rxq_flush_outstanding: Count of number of RX flushes started but not yet
 *	completed (either success or failure). Not used when MCDI is used to
 *	flush receive queues.
 * @flush_wq: रुको queue used by efx_nic_flush_queues() to रुको क्रम flush completions.
 * @vf_count: Number of VFs पूर्णांकended to be enabled.
 * @vf_init_count: Number of VFs that have been fully initialised.
 * @vi_scale: log2 number of vnics per VF.
 * @ptp_data: PTP state data
 * @ptp_warned: has this NIC seen and warned about unexpected PTP events?
 * @vpd_sn: Serial number पढ़ो from VPD
 * @xdp_rxq_info_failed: Have any of the rx queues failed to initialise their
 *      xdp_rxq_info काष्ठाures?
 * @netdev_notअगरier: Netdevice notअगरier.
 * @mem_bar: The BAR that is mapped पूर्णांकo membase.
 * @reg_base: Offset from the start of the bar to the function control winकरोw.
 * @monitor_work: Hardware monitor workitem
 * @biu_lock: BIU (bus पूर्णांकerface unit) lock
 * @last_irq_cpu: Last CPU to handle a possible test पूर्णांकerrupt.  This
 *	field is used by efx_test_पूर्णांकerrupts() to verअगरy that an
 *	पूर्णांकerrupt has occurred.
 * @stats_lock: Statistics update lock. Must be held when calling
 *	efx_nic_type::अणुupdate,start,stopपूर्ण_stats.
 * @n_rx_noskb_drops: Count of RX packets dropped due to failure to allocate an skb
 *
 * This is stored in the निजी area of the &काष्ठा net_device.
 */
काष्ठा efx_nic अणु
	/* The following fields should be written very rarely */

	अक्षर name[IFNAMSIZ];
	काष्ठा list_head node;
	काष्ठा efx_nic *primary;
	काष्ठा list_head secondary_list;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित पूर्णांक port_num;
	स्थिर काष्ठा efx_nic_type *type;
	पूर्णांक legacy_irq;
	bool eeh_disabled_legacy_irq;
	काष्ठा workqueue_काष्ठा *workqueue;
	अक्षर workqueue_name[16];
	काष्ठा work_काष्ठा reset_work;
	resource_माप_प्रकार membase_phys;
	व्योम __iomem *membase;

	अचिन्हित पूर्णांक vi_stride;

	क्रमागत efx_पूर्णांक_mode पूर्णांकerrupt_mode;
	अचिन्हित पूर्णांक समयr_quantum_ns;
	अचिन्हित पूर्णांक समयr_max_ns;
	bool irq_rx_adaptive;
	bool irqs_hooked;
	अचिन्हित पूर्णांक irq_mod_step_us;
	अचिन्हित पूर्णांक irq_rx_moderation_us;
	u32 msg_enable;

	क्रमागत nic_state state;
	अचिन्हित दीर्घ reset_pending;

	काष्ठा efx_channel *channel[EFX_MAX_CHANNELS];
	काष्ठा efx_msi_context msi_context[EFX_MAX_CHANNELS];
	स्थिर काष्ठा efx_channel_type *
	extra_channel_type[EFX_MAX_EXTRA_CHANNELS];

	अचिन्हित पूर्णांक xdp_tx_queue_count;
	काष्ठा efx_tx_queue **xdp_tx_queues;

	अचिन्हित rxq_entries;
	अचिन्हित txq_entries;
	अचिन्हित पूर्णांक txq_stop_thresh;
	अचिन्हित पूर्णांक txq_wake_thresh;

	अचिन्हित tx_dc_base;
	अचिन्हित rx_dc_base;
	अचिन्हित sram_lim_qw;
	अचिन्हित next_buffer_table;

	अचिन्हित पूर्णांक max_channels;
	अचिन्हित पूर्णांक max_vis;
	अचिन्हित पूर्णांक max_tx_channels;
	अचिन्हित n_channels;
	अचिन्हित n_rx_channels;
	अचिन्हित rss_spपढ़ो;
	अचिन्हित tx_channel_offset;
	अचिन्हित n_tx_channels;
	अचिन्हित n_extra_tx_channels;
	अचिन्हित पूर्णांक tx_queues_per_channel;
	अचिन्हित पूर्णांक n_xdp_channels;
	अचिन्हित पूर्णांक xdp_channel_offset;
	अचिन्हित पूर्णांक xdp_tx_per_channel;
	अचिन्हित पूर्णांक rx_ip_align;
	अचिन्हित पूर्णांक rx_dma_len;
	अचिन्हित पूर्णांक rx_buffer_order;
	अचिन्हित पूर्णांक rx_buffer_truesize;
	अचिन्हित पूर्णांक rx_page_buf_step;
	अचिन्हित पूर्णांक rx_bufs_per_page;
	अचिन्हित पूर्णांक rx_pages_per_batch;
	अचिन्हित पूर्णांक rx_prefix_size;
	पूर्णांक rx_packet_hash_offset;
	पूर्णांक rx_packet_len_offset;
	पूर्णांक rx_packet_ts_offset;
	bool rx_scatter;
	काष्ठा efx_rss_context rss_context;
	काष्ठा mutex rss_lock;
	u32 vport_id;

	अचिन्हित पूर्णांक_error_count;
	अचिन्हित दीर्घ पूर्णांक_error_expire;

	bool must_पुनः_स्मृति_vis;
	bool irq_soft_enabled;
	काष्ठा efx_buffer irq_status;
	अचिन्हित irq_zero_count;
	अचिन्हित irq_level;
	काष्ठा delayed_work selftest_work;

#अगर_घोषित CONFIG_SFC_MTD
	काष्ठा list_head mtd_list;
#पूर्ण_अगर

	व्योम *nic_data;
	काष्ठा efx_mcdi_data *mcdi;

	काष्ठा mutex mac_lock;
	काष्ठा work_काष्ठा mac_work;
	bool port_enabled;

	bool mc_bist_क्रम_other_fn;
	bool port_initialized;
	काष्ठा net_device *net_dev;

	netdev_features_t fixed_features;

	u16 num_mac_stats;
	काष्ठा efx_buffer stats_buffer;
	u64 rx_nodesc_drops_total;
	u64 rx_nodesc_drops_जबतक_करोwn;
	bool rx_nodesc_drops_prev_state;

	अचिन्हित पूर्णांक phy_type;
	व्योम *phy_data;
	काष्ठा mdio_अगर_info mdio;
	अचिन्हित पूर्णांक mdio_bus;
	क्रमागत efx_phy_mode phy_mode;

	__ETHTOOL_DECLARE_LINK_MODE_MASK(link_advertising);
	u32 fec_config;
	काष्ठा efx_link_state link_state;
	अचिन्हित पूर्णांक n_link_state_changes;

	bool unicast_filter;
	जोड़ efx_multicast_hash multicast_hash;
	u8 wanted_fc;
	अचिन्हित fc_disable;

	atomic_t rx_reset;
	क्रमागत efx_loopback_mode loopback_mode;
	u64 loopback_modes;

	व्योम *loopback_selftest;
	/* We access loopback_selftest immediately beक्रमe running XDP,
	 * so we want them next to each other.
	 */
	काष्ठा bpf_prog __rcu *xdp_prog;

	काष्ठा rw_semaphore filter_sem;
	व्योम *filter_state;
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा mutex rps_mutex;
	अचिन्हित दीर्घ rps_slot_map;
	काष्ठा efx_async_filter_insertion rps_slot[EFX_RPS_MAX_IN_FLIGHT];
	spinlock_t rps_hash_lock;
	काष्ठा hlist_head *rps_hash_table;
	u32 rps_next_id;
#पूर्ण_अगर

	atomic_t active_queues;
	atomic_t rxq_flush_pending;
	atomic_t rxq_flush_outstanding;
	रुको_queue_head_t flush_wq;

#अगर_घोषित CONFIG_SFC_SRIOV
	अचिन्हित vf_count;
	अचिन्हित vf_init_count;
	अचिन्हित vi_scale;
#पूर्ण_अगर

	काष्ठा efx_ptp_data *ptp_data;
	bool ptp_warned;

	अक्षर *vpd_sn;
	bool xdp_rxq_info_failed;

	काष्ठा notअगरier_block netdev_notअगरier;

	अचिन्हित पूर्णांक mem_bar;
	u32 reg_base;

	/* The following fields may be written more often */

	काष्ठा delayed_work monitor_work ____cacheline_aligned_in_smp;
	spinlock_t biu_lock;
	पूर्णांक last_irq_cpu;
	spinlock_t stats_lock;
	atomic_t n_rx_noskb_drops;
पूर्ण;

अटल अंतरभूत पूर्णांक efx_dev_रेजिस्टरed(काष्ठा efx_nic *efx)
अणु
	वापस efx->net_dev->reg_state == NETREG_REGISTERED;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक efx_port_num(काष्ठा efx_nic *efx)
अणु
	वापस efx->port_num;
पूर्ण

काष्ठा efx_mtd_partition अणु
	काष्ठा list_head node;
	काष्ठा mtd_info mtd;
	स्थिर अक्षर *dev_type_name;
	स्थिर अक्षर *type_name;
	अक्षर name[IFNAMSIZ + 20];
पूर्ण;

काष्ठा efx_udp_tunnel अणु
#घोषणा TUNNEL_ENCAP_UDP_PORT_ENTRY_INVALID	0xffff
	u16 type; /* TUNNEL_ENCAP_UDP_PORT_ENTRY_foo, see mcdi_pcol.h */
	__be16 port;
पूर्ण;

/**
 * काष्ठा efx_nic_type - Efx device type definition
 * @mem_bar: Get the memory BAR
 * @mem_map_size: Get memory BAR mapped size
 * @probe: Probe the controller
 * @हटाओ: Free resources allocated by probe()
 * @init: Initialise the controller
 * @dimension_resources: Dimension controller resources (buffer table,
 *	and VIs once the available पूर्णांकerrupt resources are clear)
 * @fini: Shut करोwn the controller
 * @monitor: Periodic function क्रम polling link state and hardware monitor
 * @map_reset_reason: Map ethtool reset reason to a reset method
 * @map_reset_flags: Map ethtool reset flags to a reset method, अगर possible
 * @reset: Reset the controller hardware and possibly the PHY.  This will
 *	be called जबतक the controller is uninitialised.
 * @probe_port: Probe the MAC and PHY
 * @हटाओ_port: Free resources allocated by probe_port()
 * @handle_global_event: Handle a "global" event (may be %शून्य)
 * @fini_dmaq: Flush and finalise DMA queues (RX and TX queues)
 * @prepare_flush: Prepare the hardware क्रम flushing the DMA queues
 *	(क्रम Falcon architecture)
 * @finish_flush: Clean up after flushing the DMA queues (क्रम Falcon
 *	architecture)
 * @prepare_flr: Prepare क्रम an FLR
 * @finish_flr: Clean up after an FLR
 * @describe_stats: Describe statistics क्रम ethtool
 * @update_stats: Update statistics not provided by event handling.
 *	Either argument may be %शून्य.
 * @update_stats_atomic: Update statistics जबतक in atomic context, अगर that
 *	is more limiting than @update_stats.  Otherwise, leave %शून्य and
 *	driver core will call @update_stats.
 * @start_stats: Start the regular fetching of statistics
 * @pull_stats: Pull stats from the NIC and रुको until they arrive.
 * @stop_stats: Stop the regular fetching of statistics
 * @push_irq_moderation: Apply पूर्णांकerrupt moderation value
 * @reconfigure_port: Push loopback/घातer/txdis changes to the MAC and PHY
 * @prepare_enable_fc_tx: Prepare MAC to enable छोड़ो frame TX (may be %शून्य)
 * @reconfigure_mac: Push MAC address, MTU, flow control and filter settings
 *	to the hardware.  Serialised by the mac_lock.
 * @check_mac_fault: Check MAC fault state. True अगर fault present.
 * @get_wol: Get WoL configuration from driver state
 * @set_wol: Push WoL configuration to the NIC
 * @resume_wol: Synchronise WoL state between driver and MC (e.g. after resume)
 * @get_fec_stats: Get standard FEC statistics.
 * @test_chip: Test रेजिस्टरs.  May use efx_farch_test_रेजिस्टरs(), and is
 *	expected to reset the NIC.
 * @test_nvram: Test validity of NVRAM contents
 * @mcdi_request: Send an MCDI request with the given header and SDU.
 *	The SDU length may be any value from 0 up to the protocol-
 *	defined maximum, but its buffer will be padded to a multiple
 *	of 4 bytes.
 * @mcdi_poll_response: Test whether an MCDI response is available.
 * @mcdi_पढ़ो_response: Read the MCDI response PDU.  The offset will
 *	be a multiple of 4.  The length may not be, but the buffer
 *	will be padded so it is safe to round up.
 * @mcdi_poll_reboot: Test whether the MCDI has rebooted.  If so,
 *	वापस an appropriate error code क्रम पातing any current
 *	request; otherwise वापस 0.
 * @irq_enable_master: Enable IRQs on the NIC.  Each event queue must
 *	be separately enabled after this.
 * @irq_test_generate: Generate a test IRQ
 * @irq_disable_non_ev: Disable non-event IRQs on the NIC.  Each event
 *	queue must be separately disabled beक्रमe this.
 * @irq_handle_msi: Handle MSI क्रम a channel.  The @dev_id argument is
 *	a poपूर्णांकer to the &काष्ठा efx_msi_context क्रम the channel.
 * @irq_handle_legacy: Handle legacy पूर्णांकerrupt.  The @dev_id argument
 *	is a poपूर्णांकer to the &काष्ठा efx_nic.
 * @tx_probe: Allocate resources क्रम TX queue (and select TXQ type)
 * @tx_init: Initialise TX queue on the NIC
 * @tx_हटाओ: Free resources क्रम TX queue
 * @tx_ग_लिखो: Write TX descriptors and करोorbell
 * @tx_enqueue: Add an SKB to TX queue
 * @rx_push_rss_config: Write RSS hash key and indirection table to the NIC
 * @rx_pull_rss_config: Read RSS hash key and indirection table back from the NIC
 * @rx_push_rss_context_config: Write RSS hash key and indirection table क्रम
 *	user RSS context to the NIC
 * @rx_pull_rss_context_config: Read RSS hash key and indirection table क्रम user
 *	RSS context back from the NIC
 * @rx_probe: Allocate resources क्रम RX queue
 * @rx_init: Initialise RX queue on the NIC
 * @rx_हटाओ: Free resources क्रम RX queue
 * @rx_ग_लिखो: Write RX descriptors and करोorbell
 * @rx_defer_refill: Generate a refill reminder event
 * @rx_packet: Receive the queued RX buffer on a channel
 * @rx_buf_hash_valid: Determine whether the RX prefix contains a valid hash
 * @ev_probe: Allocate resources क्रम event queue
 * @ev_init: Initialise event queue on the NIC
 * @ev_fini: Deinitialise event queue on the NIC
 * @ev_हटाओ: Free resources क्रम event queue
 * @ev_process: Process events क्रम a queue, up to the given NAPI quota
 * @ev_पढ़ो_ack: Acknowledge पढ़ो events on a queue, rearming its IRQ
 * @ev_test_generate: Generate a test event
 * @filter_table_probe: Probe filter capabilities and set up filter software state
 * @filter_table_restore: Restore filters हटाओd from hardware
 * @filter_table_हटाओ: Remove filters from hardware and tear करोwn software state
 * @filter_update_rx_scatter: Update filters after change to rx scatter setting
 * @filter_insert: add or replace a filter
 * @filter_हटाओ_safe: हटाओ a filter by ID, carefully
 * @filter_get_safe: retrieve a filter by ID, carefully
 * @filter_clear_rx: Remove all RX filters whose priority is less than or
 *	equal to the given priority and is not %EFX_FILTER_PRI_AUTO
 * @filter_count_rx_used: Get the number of filters in use at a given priority
 * @filter_get_rx_id_limit: Get maximum value of a filter id, plus 1
 * @filter_get_rx_ids: Get list of RX filters at a given priority
 * @filter_rfs_expire_one: Consider expiring a filter inserted क्रम RFS.
 *	This must check whether the specअगरied table entry is used by RFS
 *	and that rps_may_expire_flow() वापसs true क्रम it.
 * @mtd_probe: Probe and add MTD partitions associated with this net device,
 *	 using efx_mtd_add()
 * @mtd_नाम: Set an MTD partition name using the net device name
 * @mtd_पढ़ो: Read from an MTD partition
 * @mtd_erase: Erase part of an MTD partition
 * @mtd_ग_लिखो: Write to an MTD partition
 * @mtd_sync: Wait क्रम ग_लिखो-back to complete on MTD partition.  This
 *	also notअगरies the driver that a ग_लिखोr has finished using this
 *	partition.
 * @ptp_ग_लिखो_host_समय: Send host समय to MC as part of sync protocol
 * @ptp_set_ts_sync_events: Enable or disable sync events क्रम अंतरभूत RX
 *	बारtamping, possibly only temporarily क्रम the purposes of a reset.
 * @ptp_set_ts_config: Set hardware बारtamp configuration.  The flags
 *	and tx_type will alपढ़ोy have been validated but this operation
 *	must validate and update rx_filter.
 * @get_phys_port_id: Get the underlying physical port id.
 * @set_mac_address: Set the MAC address of the device
 * @tso_versions: Returns mask of firmware-assisted TSO versions supported.
 *	If %शून्य, then device करोes not support any TSO version.
 * @udp_tnl_push_ports: Push the list of UDP tunnel ports to the NIC अगर required.
 * @udp_tnl_has_port: Check अगर a port has been added as UDP tunnel
 * @prपूर्णांक_additional_fwver: Dump NIC-specअगरic additional FW version info
 * @sensor_event: Handle a sensor event from MCDI
 * @revision: Hardware architecture revision
 * @txd_ptr_tbl_base: TX descriptor ring base address
 * @rxd_ptr_tbl_base: RX descriptor ring base address
 * @buf_tbl_base: Buffer table base address
 * @evq_ptr_tbl_base: Event queue poपूर्णांकer table base address
 * @evq_rptr_tbl_base: Event queue पढ़ो-poपूर्णांकer table base address
 * @max_dma_mask: Maximum possible DMA mask
 * @rx_prefix_size: Size of RX prefix beक्रमe packet data
 * @rx_hash_offset: Offset of RX flow hash within prefix
 * @rx_ts_offset: Offset of बारtamp within prefix
 * @rx_buffer_padding: Size of padding at end of RX packet
 * @can_rx_scatter: NIC is able to scatter packets to multiple buffers
 * @always_rx_scatter: NIC will always scatter packets to multiple buffers
 * @option_descriptors: NIC supports TX option descriptors
 * @min_पूर्णांकerrupt_mode: Lowest capability पूर्णांकerrupt mode supported
 *	from &क्रमागत efx_पूर्णांक_mode.
 * @समयr_period_max: Maximum period of पूर्णांकerrupt समयr (in ticks)
 * @offload_features: net_device feature flags क्रम protocol offload
 *	features implemented in hardware
 * @mcdi_max_ver: Maximum MCDI version supported
 * @hwtstamp_filters: Mask of hardware बारtamp filter types supported
 */
काष्ठा efx_nic_type अणु
	bool is_vf;
	अचिन्हित पूर्णांक (*mem_bar)(काष्ठा efx_nic *efx);
	अचिन्हित पूर्णांक (*mem_map_size)(काष्ठा efx_nic *efx);
	पूर्णांक (*probe)(काष्ठा efx_nic *efx);
	व्योम (*हटाओ)(काष्ठा efx_nic *efx);
	पूर्णांक (*init)(काष्ठा efx_nic *efx);
	पूर्णांक (*dimension_resources)(काष्ठा efx_nic *efx);
	व्योम (*fini)(काष्ठा efx_nic *efx);
	व्योम (*monitor)(काष्ठा efx_nic *efx);
	क्रमागत reset_type (*map_reset_reason)(क्रमागत reset_type reason);
	पूर्णांक (*map_reset_flags)(u32 *flags);
	पूर्णांक (*reset)(काष्ठा efx_nic *efx, क्रमागत reset_type method);
	पूर्णांक (*probe_port)(काष्ठा efx_nic *efx);
	व्योम (*हटाओ_port)(काष्ठा efx_nic *efx);
	bool (*handle_global_event)(काष्ठा efx_channel *channel, efx_qword_t *);
	पूर्णांक (*fini_dmaq)(काष्ठा efx_nic *efx);
	व्योम (*prepare_flush)(काष्ठा efx_nic *efx);
	व्योम (*finish_flush)(काष्ठा efx_nic *efx);
	व्योम (*prepare_flr)(काष्ठा efx_nic *efx);
	व्योम (*finish_flr)(काष्ठा efx_nic *efx);
	माप_प्रकार (*describe_stats)(काष्ठा efx_nic *efx, u8 *names);
	माप_प्रकार (*update_stats)(काष्ठा efx_nic *efx, u64 *full_stats,
			       काष्ठा rtnl_link_stats64 *core_stats);
	माप_प्रकार (*update_stats_atomic)(काष्ठा efx_nic *efx, u64 *full_stats,
				      काष्ठा rtnl_link_stats64 *core_stats);
	व्योम (*start_stats)(काष्ठा efx_nic *efx);
	व्योम (*pull_stats)(काष्ठा efx_nic *efx);
	व्योम (*stop_stats)(काष्ठा efx_nic *efx);
	व्योम (*push_irq_moderation)(काष्ठा efx_channel *channel);
	पूर्णांक (*reconfigure_port)(काष्ठा efx_nic *efx);
	व्योम (*prepare_enable_fc_tx)(काष्ठा efx_nic *efx);
	पूर्णांक (*reconfigure_mac)(काष्ठा efx_nic *efx, bool mtu_only);
	bool (*check_mac_fault)(काष्ठा efx_nic *efx);
	व्योम (*get_wol)(काष्ठा efx_nic *efx, काष्ठा ethtool_wolinfo *wol);
	पूर्णांक (*set_wol)(काष्ठा efx_nic *efx, u32 type);
	व्योम (*resume_wol)(काष्ठा efx_nic *efx);
	व्योम (*get_fec_stats)(काष्ठा efx_nic *efx,
			      काष्ठा ethtool_fec_stats *fec_stats);
	अचिन्हित पूर्णांक (*check_caps)(स्थिर काष्ठा efx_nic *efx,
				   u8 flag,
				   u32 offset);
	पूर्णांक (*test_chip)(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests);
	पूर्णांक (*test_nvram)(काष्ठा efx_nic *efx);
	व्योम (*mcdi_request)(काष्ठा efx_nic *efx,
			     स्थिर efx_dword_t *hdr, माप_प्रकार hdr_len,
			     स्थिर efx_dword_t *sdu, माप_प्रकार sdu_len);
	bool (*mcdi_poll_response)(काष्ठा efx_nic *efx);
	व्योम (*mcdi_पढ़ो_response)(काष्ठा efx_nic *efx, efx_dword_t *pdu,
				   माप_प्रकार pdu_offset, माप_प्रकार pdu_len);
	पूर्णांक (*mcdi_poll_reboot)(काष्ठा efx_nic *efx);
	व्योम (*mcdi_reboot_detected)(काष्ठा efx_nic *efx);
	व्योम (*irq_enable_master)(काष्ठा efx_nic *efx);
	पूर्णांक (*irq_test_generate)(काष्ठा efx_nic *efx);
	व्योम (*irq_disable_non_ev)(काष्ठा efx_nic *efx);
	irqवापस_t (*irq_handle_msi)(पूर्णांक irq, व्योम *dev_id);
	irqवापस_t (*irq_handle_legacy)(पूर्णांक irq, व्योम *dev_id);
	पूर्णांक (*tx_probe)(काष्ठा efx_tx_queue *tx_queue);
	व्योम (*tx_init)(काष्ठा efx_tx_queue *tx_queue);
	व्योम (*tx_हटाओ)(काष्ठा efx_tx_queue *tx_queue);
	व्योम (*tx_ग_लिखो)(काष्ठा efx_tx_queue *tx_queue);
	netdev_tx_t (*tx_enqueue)(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb);
	अचिन्हित पूर्णांक (*tx_limit_len)(काष्ठा efx_tx_queue *tx_queue,
				     dma_addr_t dma_addr, अचिन्हित पूर्णांक len);
	पूर्णांक (*rx_push_rss_config)(काष्ठा efx_nic *efx, bool user,
				  स्थिर u32 *rx_indir_table, स्थिर u8 *key);
	पूर्णांक (*rx_pull_rss_config)(काष्ठा efx_nic *efx);
	पूर्णांक (*rx_push_rss_context_config)(काष्ठा efx_nic *efx,
					  काष्ठा efx_rss_context *ctx,
					  स्थिर u32 *rx_indir_table,
					  स्थिर u8 *key);
	पूर्णांक (*rx_pull_rss_context_config)(काष्ठा efx_nic *efx,
					  काष्ठा efx_rss_context *ctx);
	व्योम (*rx_restore_rss_contexts)(काष्ठा efx_nic *efx);
	पूर्णांक (*rx_probe)(काष्ठा efx_rx_queue *rx_queue);
	व्योम (*rx_init)(काष्ठा efx_rx_queue *rx_queue);
	व्योम (*rx_हटाओ)(काष्ठा efx_rx_queue *rx_queue);
	व्योम (*rx_ग_लिखो)(काष्ठा efx_rx_queue *rx_queue);
	व्योम (*rx_defer_refill)(काष्ठा efx_rx_queue *rx_queue);
	व्योम (*rx_packet)(काष्ठा efx_channel *channel);
	bool (*rx_buf_hash_valid)(स्थिर u8 *prefix);
	पूर्णांक (*ev_probe)(काष्ठा efx_channel *channel);
	पूर्णांक (*ev_init)(काष्ठा efx_channel *channel);
	व्योम (*ev_fini)(काष्ठा efx_channel *channel);
	व्योम (*ev_हटाओ)(काष्ठा efx_channel *channel);
	पूर्णांक (*ev_process)(काष्ठा efx_channel *channel, पूर्णांक quota);
	व्योम (*ev_पढ़ो_ack)(काष्ठा efx_channel *channel);
	व्योम (*ev_test_generate)(काष्ठा efx_channel *channel);
	पूर्णांक (*filter_table_probe)(काष्ठा efx_nic *efx);
	व्योम (*filter_table_restore)(काष्ठा efx_nic *efx);
	व्योम (*filter_table_हटाओ)(काष्ठा efx_nic *efx);
	व्योम (*filter_update_rx_scatter)(काष्ठा efx_nic *efx);
	s32 (*filter_insert)(काष्ठा efx_nic *efx,
			     काष्ठा efx_filter_spec *spec, bool replace);
	पूर्णांक (*filter_हटाओ_safe)(काष्ठा efx_nic *efx,
				  क्रमागत efx_filter_priority priority,
				  u32 filter_id);
	पूर्णांक (*filter_get_safe)(काष्ठा efx_nic *efx,
			       क्रमागत efx_filter_priority priority,
			       u32 filter_id, काष्ठा efx_filter_spec *);
	पूर्णांक (*filter_clear_rx)(काष्ठा efx_nic *efx,
			       क्रमागत efx_filter_priority priority);
	u32 (*filter_count_rx_used)(काष्ठा efx_nic *efx,
				    क्रमागत efx_filter_priority priority);
	u32 (*filter_get_rx_id_limit)(काष्ठा efx_nic *efx);
	s32 (*filter_get_rx_ids)(काष्ठा efx_nic *efx,
				 क्रमागत efx_filter_priority priority,
				 u32 *buf, u32 size);
#अगर_घोषित CONFIG_RFS_ACCEL
	bool (*filter_rfs_expire_one)(काष्ठा efx_nic *efx, u32 flow_id,
				      अचिन्हित पूर्णांक index);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SFC_MTD
	पूर्णांक (*mtd_probe)(काष्ठा efx_nic *efx);
	व्योम (*mtd_नाम)(काष्ठा efx_mtd_partition *part);
	पूर्णांक (*mtd_पढ़ो)(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len,
			माप_प्रकार *retlen, u8 *buffer);
	पूर्णांक (*mtd_erase)(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len);
	पूर्णांक (*mtd_ग_लिखो)(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len,
			 माप_प्रकार *retlen, स्थिर u8 *buffer);
	पूर्णांक (*mtd_sync)(काष्ठा mtd_info *mtd);
#पूर्ण_अगर
	व्योम (*ptp_ग_लिखो_host_समय)(काष्ठा efx_nic *efx, u32 host_समय);
	पूर्णांक (*ptp_set_ts_sync_events)(काष्ठा efx_nic *efx, bool en, bool temp);
	पूर्णांक (*ptp_set_ts_config)(काष्ठा efx_nic *efx,
				 काष्ठा hwtstamp_config *init);
	पूर्णांक (*sriov_configure)(काष्ठा efx_nic *efx, पूर्णांक num_vfs);
	पूर्णांक (*vlan_rx_add_vid)(काष्ठा efx_nic *efx, __be16 proto, u16 vid);
	पूर्णांक (*vlan_rx_समाप्त_vid)(काष्ठा efx_nic *efx, __be16 proto, u16 vid);
	पूर्णांक (*get_phys_port_id)(काष्ठा efx_nic *efx,
				काष्ठा netdev_phys_item_id *ppid);
	पूर्णांक (*sriov_init)(काष्ठा efx_nic *efx);
	व्योम (*sriov_fini)(काष्ठा efx_nic *efx);
	bool (*sriov_wanted)(काष्ठा efx_nic *efx);
	व्योम (*sriov_reset)(काष्ठा efx_nic *efx);
	व्योम (*sriov_flr)(काष्ठा efx_nic *efx, अचिन्हित vf_i);
	पूर्णांक (*sriov_set_vf_mac)(काष्ठा efx_nic *efx, पूर्णांक vf_i, u8 *mac);
	पूर्णांक (*sriov_set_vf_vlan)(काष्ठा efx_nic *efx, पूर्णांक vf_i, u16 vlan,
				 u8 qos);
	पूर्णांक (*sriov_set_vf_spoofchk)(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				     bool spoofchk);
	पूर्णांक (*sriov_get_vf_config)(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				   काष्ठा अगरla_vf_info *ivi);
	पूर्णांक (*sriov_set_vf_link_state)(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				       पूर्णांक link_state);
	पूर्णांक (*vचयनing_probe)(काष्ठा efx_nic *efx);
	पूर्णांक (*vचयनing_restore)(काष्ठा efx_nic *efx);
	व्योम (*vचयनing_हटाओ)(काष्ठा efx_nic *efx);
	पूर्णांक (*get_mac_address)(काष्ठा efx_nic *efx, अचिन्हित अक्षर *perm_addr);
	पूर्णांक (*set_mac_address)(काष्ठा efx_nic *efx);
	u32 (*tso_versions)(काष्ठा efx_nic *efx);
	पूर्णांक (*udp_tnl_push_ports)(काष्ठा efx_nic *efx);
	bool (*udp_tnl_has_port)(काष्ठा efx_nic *efx, __be16 port);
	माप_प्रकार (*prपूर्णांक_additional_fwver)(काष्ठा efx_nic *efx, अक्षर *buf,
					 माप_प्रकार len);
	व्योम (*sensor_event)(काष्ठा efx_nic *efx, efx_qword_t *ev);

	पूर्णांक revision;
	अचिन्हित पूर्णांक txd_ptr_tbl_base;
	अचिन्हित पूर्णांक rxd_ptr_tbl_base;
	अचिन्हित पूर्णांक buf_tbl_base;
	अचिन्हित पूर्णांक evq_ptr_tbl_base;
	अचिन्हित पूर्णांक evq_rptr_tbl_base;
	u64 max_dma_mask;
	अचिन्हित पूर्णांक rx_prefix_size;
	अचिन्हित पूर्णांक rx_hash_offset;
	अचिन्हित पूर्णांक rx_ts_offset;
	अचिन्हित पूर्णांक rx_buffer_padding;
	bool can_rx_scatter;
	bool always_rx_scatter;
	bool option_descriptors;
	अचिन्हित पूर्णांक min_पूर्णांकerrupt_mode;
	अचिन्हित पूर्णांक समयr_period_max;
	netdev_features_t offload_features;
	पूर्णांक mcdi_max_ver;
	अचिन्हित पूर्णांक max_rx_ip_filters;
	u32 hwtstamp_filters;
	अचिन्हित पूर्णांक rx_hash_key_size;
पूर्ण;

/**************************************************************************
 *
 * Prototypes and अंतरभूत functions
 *
 *************************************************************************/

अटल अंतरभूत काष्ठा efx_channel *
efx_get_channel(काष्ठा efx_nic *efx, अचिन्हित index)
अणु
	EFX_WARN_ON_ONCE_PARANOID(index >= efx->n_channels);
	वापस efx->channel[index];
पूर्ण

/* Iterate over all used channels */
#घोषणा efx_क्रम_each_channel(_channel, _efx)				\
	क्रम (_channel = (_efx)->channel[0];				\
	     _channel;							\
	     _channel = (_channel->channel + 1 < (_efx)->n_channels) ?	\
		     (_efx)->channel[_channel->channel + 1] : शून्य)

/* Iterate over all used channels in reverse */
#घोषणा efx_क्रम_each_channel_rev(_channel, _efx)			\
	क्रम (_channel = (_efx)->channel[(_efx)->n_channels - 1];	\
	     _channel;							\
	     _channel = _channel->channel ?				\
		     (_efx)->channel[_channel->channel - 1] : शून्य)

अटल अंतरभूत काष्ठा efx_channel *
efx_get_tx_channel(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक index)
अणु
	EFX_WARN_ON_ONCE_PARANOID(index >= efx->n_tx_channels);
	वापस efx->channel[efx->tx_channel_offset + index];
पूर्ण

अटल अंतरभूत काष्ठा efx_channel *
efx_get_xdp_channel(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक index)
अणु
	EFX_WARN_ON_ONCE_PARANOID(index >= efx->n_xdp_channels);
	वापस efx->channel[efx->xdp_channel_offset + index];
पूर्ण

अटल अंतरभूत bool efx_channel_is_xdp_tx(काष्ठा efx_channel *channel)
अणु
	वापस channel->channel - channel->efx->xdp_channel_offset <
	       channel->efx->n_xdp_channels;
पूर्ण

अटल अंतरभूत bool efx_channel_has_tx_queues(काष्ठा efx_channel *channel)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक efx_channel_num_tx_queues(काष्ठा efx_channel *channel)
अणु
	अगर (efx_channel_is_xdp_tx(channel))
		वापस channel->efx->xdp_tx_per_channel;
	वापस channel->efx->tx_queues_per_channel;
पूर्ण

अटल अंतरभूत काष्ठा efx_tx_queue *
efx_channel_get_tx_queue(काष्ठा efx_channel *channel, अचिन्हित पूर्णांक type)
अणु
	EFX_WARN_ON_ONCE_PARANOID(type >= EFX_TXQ_TYPES);
	वापस channel->tx_queue_by_type[type];
पूर्ण

अटल अंतरभूत काष्ठा efx_tx_queue *
efx_get_tx_queue(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक type)
अणु
	काष्ठा efx_channel *channel = efx_get_tx_channel(efx, index);

	वापस efx_channel_get_tx_queue(channel, type);
पूर्ण

/* Iterate over all TX queues beदीर्घing to a channel */
#घोषणा efx_क्रम_each_channel_tx_queue(_tx_queue, _channel)		\
	अगर (!efx_channel_has_tx_queues(_channel))			\
		;							\
	अन्यथा								\
		क्रम (_tx_queue = (_channel)->tx_queue;			\
		     _tx_queue < (_channel)->tx_queue +			\
				 efx_channel_num_tx_queues(_channel);		\
		     _tx_queue++)

अटल अंतरभूत bool efx_channel_has_rx_queue(काष्ठा efx_channel *channel)
अणु
	वापस channel->rx_queue.core_index >= 0;
पूर्ण

अटल अंतरभूत काष्ठा efx_rx_queue *
efx_channel_get_rx_queue(काष्ठा efx_channel *channel)
अणु
	EFX_WARN_ON_ONCE_PARANOID(!efx_channel_has_rx_queue(channel));
	वापस &channel->rx_queue;
पूर्ण

/* Iterate over all RX queues beदीर्घing to a channel */
#घोषणा efx_क्रम_each_channel_rx_queue(_rx_queue, _channel)		\
	अगर (!efx_channel_has_rx_queue(_channel))			\
		;							\
	अन्यथा								\
		क्रम (_rx_queue = &(_channel)->rx_queue;			\
		     _rx_queue;						\
		     _rx_queue = शून्य)

अटल अंतरभूत काष्ठा efx_channel *
efx_rx_queue_channel(काष्ठा efx_rx_queue *rx_queue)
अणु
	वापस container_of(rx_queue, काष्ठा efx_channel, rx_queue);
पूर्ण

अटल अंतरभूत पूर्णांक efx_rx_queue_index(काष्ठा efx_rx_queue *rx_queue)
अणु
	वापस efx_rx_queue_channel(rx_queue)->channel;
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied receive buffer in the RX
 * descriptor queue.
 */
अटल अंतरभूत काष्ठा efx_rx_buffer *efx_rx_buffer(काष्ठा efx_rx_queue *rx_queue,
						  अचिन्हित पूर्णांक index)
अणु
	वापस &rx_queue->buffer[index];
पूर्ण

अटल अंतरभूत काष्ठा efx_rx_buffer *
efx_rx_buf_next(काष्ठा efx_rx_queue *rx_queue, काष्ठा efx_rx_buffer *rx_buf)
अणु
	अगर (unlikely(rx_buf == efx_rx_buffer(rx_queue, rx_queue->ptr_mask)))
		वापस efx_rx_buffer(rx_queue, 0);
	अन्यथा
		वापस rx_buf + 1;
पूर्ण

/**
 * EFX_MAX_FRAME_LEN - calculate maximum frame length
 *
 * This calculates the maximum frame length that will be used क्रम a
 * given MTU.  The frame length will be equal to the MTU plus a
 * स्थिरant amount of header space and padding.  This is the quantity
 * that the net driver will program पूर्णांकo the MAC as the maximum frame
 * length.
 *
 * The 10G MAC requires 8-byte alignment on the frame
 * length, so we round up to the nearest 8.
 *
 * Re-घड़ीing by the XGXS on RX can reduce an IPG to 32 bits (half an
 * XGMII cycle).  If the frame length reaches the maximum value in the
 * same cycle, the XMAC can miss the IPG altogether.  We work around
 * this by adding a further 16 bytes.
 */
#घोषणा EFX_FRAME_PAD	16
#घोषणा EFX_MAX_FRAME_LEN(mtu) \
	(ALIGN(((mtu) + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN + EFX_FRAME_PAD), 8))

अटल अंतरभूत bool efx_xmit_with_hwtstamp(काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP;
पूर्ण
अटल अंतरभूत व्योम efx_xmit_hwtstamp_pending(काष्ठा sk_buff *skb)
अणु
	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
पूर्ण

/* Get the max fill level of the TX queues on this channel */
अटल अंतरभूत अचिन्हित पूर्णांक
efx_channel_tx_fill_level(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	अचिन्हित पूर्णांक fill_level = 0;

	efx_क्रम_each_channel_tx_queue(tx_queue, channel)
		fill_level = max(fill_level,
				 tx_queue->insert_count - tx_queue->पढ़ो_count);

	वापस fill_level;
पूर्ण

/* Conservative approximation of efx_channel_tx_fill_level using cached value */
अटल अंतरभूत अचिन्हित पूर्णांक
efx_channel_tx_old_fill_level(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	अचिन्हित पूर्णांक fill_level = 0;

	efx_क्रम_each_channel_tx_queue(tx_queue, channel)
		fill_level = max(fill_level,
				 tx_queue->insert_count - tx_queue->old_पढ़ो_count);

	वापस fill_level;
पूर्ण

/* Get all supported features.
 * If a feature is not fixed, it is present in hw_features.
 * If a feature is fixed, it करोes not present in hw_features, but
 * always in features.
 */
अटल अंतरभूत netdev_features_t efx_supported_features(स्थिर काष्ठा efx_nic *efx)
अणु
	स्थिर काष्ठा net_device *net_dev = efx->net_dev;

	वापस net_dev->features | net_dev->hw_features;
पूर्ण

/* Get the current TX queue insert index. */
अटल अंतरभूत अचिन्हित पूर्णांक
efx_tx_queue_get_insert_index(स्थिर काष्ठा efx_tx_queue *tx_queue)
अणु
	वापस tx_queue->insert_count & tx_queue->ptr_mask;
पूर्ण

/* Get a TX buffer. */
अटल अंतरभूत काष्ठा efx_tx_buffer *
__efx_tx_queue_get_insert_buffer(स्थिर काष्ठा efx_tx_queue *tx_queue)
अणु
	वापस &tx_queue->buffer[efx_tx_queue_get_insert_index(tx_queue)];
पूर्ण

/* Get a TX buffer, checking it's not currently in use. */
अटल अंतरभूत काष्ठा efx_tx_buffer *
efx_tx_queue_get_insert_buffer(स्थिर काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_tx_buffer *buffer =
		__efx_tx_queue_get_insert_buffer(tx_queue);

	EFX_WARN_ON_ONCE_PARANOID(buffer->len);
	EFX_WARN_ON_ONCE_PARANOID(buffer->flags);
	EFX_WARN_ON_ONCE_PARANOID(buffer->unmap_len);

	वापस buffer;
पूर्ण

#पूर्ण_अगर /* EFX_NET_DRIVER_H */
