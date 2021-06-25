<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

/* Common definitions क्रम all Efx net driver code */

#अगर_अघोषित EF4_NET_DRIVER_H
#घोषणा EF4_NET_DRIVER_H

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
#समावेश <linux/i2c.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <net/busy_poll.h>

#समावेश "enum.h"
#समावेश "bitfield.h"
#समावेश "filter.h"

/**************************************************************************
 *
 * Build definitions
 *
 **************************************************************************/

#घोषणा EF4_DRIVER_VERSION	"4.1"

#अगर_घोषित DEBUG
#घोषणा EF4_BUG_ON_PARANOID(x) BUG_ON(x)
#घोषणा EF4_WARN_ON_PARANOID(x) WARN_ON(x)
#अन्यथा
#घोषणा EF4_BUG_ON_PARANOID(x) करो अणुपूर्ण जबतक (0)
#घोषणा EF4_WARN_ON_PARANOID(x) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/**************************************************************************
 *
 * Efx data काष्ठाures
 *
 **************************************************************************/

#घोषणा EF4_MAX_CHANNELS 32U
#घोषणा EF4_MAX_RX_QUEUES EF4_MAX_CHANNELS
#घोषणा EF4_EXTRA_CHANNEL_IOV	0
#घोषणा EF4_EXTRA_CHANNEL_PTP	1
#घोषणा EF4_MAX_EXTRA_CHANNELS	2U

/* Checksum generation is a per-queue option in hardware, so each
 * queue visible to the networking core is backed by two hardware TX
 * queues. */
#घोषणा EF4_MAX_TX_TC		2
#घोषणा EF4_MAX_CORE_TX_QUEUES	(EF4_MAX_TX_TC * EF4_MAX_CHANNELS)
#घोषणा EF4_TXQ_TYPE_OFFLOAD	1	/* flag */
#घोषणा EF4_TXQ_TYPE_HIGHPRI	2	/* flag */
#घोषणा EF4_TXQ_TYPES		4
#घोषणा EF4_MAX_TX_QUEUES	(EF4_TXQ_TYPES * EF4_MAX_CHANNELS)

/* Maximum possible MTU the driver supports */
#घोषणा EF4_MAX_MTU (9 * 1024)

/* Minimum MTU, from RFC791 (IP) */
#घोषणा EF4_MIN_MTU 68

/* Size of an RX scatter buffer.  Small enough to pack 2 पूर्णांकo a 4K page,
 * and should be a multiple of the cache line size.
 */
#घोषणा EF4_RX_USR_BUF_SIZE	(2048 - 256)

/* If possible, we should ensure cache line alignment at start and end
 * of every buffer.  Otherwise, we just need to ensure 4-byte
 * alignment of the network header.
 */
#अगर NET_IP_ALIGN == 0
#घोषणा EF4_RX_BUF_ALIGNMENT	L1_CACHE_BYTES
#अन्यथा
#घोषणा EF4_RX_BUF_ALIGNMENT	4
#पूर्ण_अगर

काष्ठा ef4_self_tests;

/**
 * काष्ठा ef4_buffer - A general-purpose DMA buffer
 * @addr: host base address of the buffer
 * @dma_addr: DMA base address of the buffer
 * @len: Buffer length, in bytes
 *
 * The NIC uses these buffers क्रम its पूर्णांकerrupt status रेजिस्टरs and
 * MAC stats dumps.
 */
काष्ठा ef4_buffer अणु
	व्योम *addr;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक len;
पूर्ण;

/**
 * काष्ठा ef4_special_buffer - DMA buffer entered पूर्णांकo buffer table
 * @buf: Standard &काष्ठा ef4_buffer
 * @index: Buffer index within controller;s buffer table
 * @entries: Number of buffer table entries
 *
 * The NIC has a buffer table that maps buffers of size %EF4_BUF_SIZE.
 * Event and descriptor rings are addressed via one or more buffer
 * table entries (and so can be physically non-contiguous, although we
 * currently करो not take advantage of that).  On Falcon and Siena we
 * have to take care of allocating and initialising the entries
 * ourselves.  On later hardware this is managed by the firmware and
 * @index and @entries are left as 0.
 */
काष्ठा ef4_special_buffer अणु
	काष्ठा ef4_buffer buf;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक entries;
पूर्ण;

/**
 * काष्ठा ef4_tx_buffer - buffer state क्रम a TX descriptor
 * @skb: When @flags & %EF4_TX_BUF_SKB, the associated socket buffer to be
 *	मुक्तd when descriptor completes
 * @option: When @flags & %EF4_TX_BUF_OPTION, a NIC-specअगरic option descriptor.
 * @dma_addr: DMA address of the fragment.
 * @flags: Flags क्रम allocation and DMA mapping type
 * @len: Length of this fragment.
 *	This field is zero when the queue slot is empty.
 * @unmap_len: Length of this fragment to unmap
 * @dma_offset: Offset of @dma_addr from the address of the backing DMA mapping.
 * Only valid अगर @unmap_len != 0.
 */
काष्ठा ef4_tx_buffer अणु
	स्थिर काष्ठा sk_buff *skb;
	जोड़ अणु
		ef4_qword_t option;
		dma_addr_t dma_addr;
	पूर्ण;
	अचिन्हित लघु flags;
	अचिन्हित लघु len;
	अचिन्हित लघु unmap_len;
	अचिन्हित लघु dma_offset;
पूर्ण;
#घोषणा EF4_TX_BUF_CONT		1	/* not last descriptor of packet */
#घोषणा EF4_TX_BUF_SKB		2	/* buffer is last part of skb */
#घोषणा EF4_TX_BUF_MAP_SINGLE	8	/* buffer was mapped with dma_map_single() */
#घोषणा EF4_TX_BUF_OPTION	0x10	/* empty buffer क्रम option descriptor */

/**
 * काष्ठा ef4_tx_queue - An Efx TX queue
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
 * @channel: The associated channel
 * @core_txq: The networking core TX queue काष्ठाure
 * @buffer: The software buffer ring
 * @cb_page: Array of pages of copy buffers.  Carved up according to
 *	%EF4_TX_CB_ORDER पूर्णांकo %EF4_TX_CB_SIZE-sized chunks.
 * @txd: The hardware descriptor ring
 * @ptr_mask: The size of the ring minus 1.
 * @initialised: Has hardware queue been initialised?
 * @tx_min_size: Minimum transmit size क्रम this queue. Depends on HW.
 * @पढ़ो_count: Current पढ़ो poपूर्णांकer.
 *	This is the number of buffers that have been हटाओd from both rings.
 * @old_ग_लिखो_count: The value of @ग_लिखो_count when last checked.
 *	This is here क्रम perक्रमmance reasons.  The xmit path will
 *	only get the up-to-date value of @ग_लिखो_count अगर this
 *	variable indicates that the queue is empty.  This is to
 *	aव्योम cache-line ping-pong between the xmit path and the
 *	completion path.
 * @merge_events: Number of TX merged completion events
 * @insert_count: Current insert poपूर्णांकer
 *	This is the number of buffers that have been added to the
 *	software ring.
 * @ग_लिखो_count: Current ग_लिखो poपूर्णांकer
 *	This is the number of buffers that have been added to the
 *	hardware ring.
 * @old_पढ़ो_count: The value of पढ़ो_count when last checked.
 *	This is here क्रम perक्रमmance reasons.  The xmit path will
 *	only get the up-to-date value of पढ़ो_count अगर this
 *	variable indicates that the queue is full.  This is to
 *	aव्योम cache-line ping-pong between the xmit path and the
 *	completion path.
 * @pushes: Number of बार the TX push feature has been used
 * @xmit_more_available: Are any packets रुकोing to be pushed to the NIC
 * @cb_packets: Number of बार the TX copyअवरोध feature has been used
 * @empty_पढ़ो_count: If the completion path has seen the queue as empty
 *	and the transmission path has not yet checked this, the value of
 *	@पढ़ो_count bitwise-added to %EF4_EMPTY_COUNT_VALID; otherwise 0.
 */
काष्ठा ef4_tx_queue अणु
	/* Members which करोn't change on the fast path */
	काष्ठा ef4_nic *efx ____cacheline_aligned_in_smp;
	अचिन्हित queue;
	काष्ठा ef4_channel *channel;
	काष्ठा netdev_queue *core_txq;
	काष्ठा ef4_tx_buffer *buffer;
	काष्ठा ef4_buffer *cb_page;
	काष्ठा ef4_special_buffer txd;
	अचिन्हित पूर्णांक ptr_mask;
	bool initialised;
	अचिन्हित पूर्णांक tx_min_size;

	/* Function poपूर्णांकers used in the fast path. */
	पूर्णांक (*handle_tso)(काष्ठा ef4_tx_queue*, काष्ठा sk_buff*, bool *);

	/* Members used मुख्यly on the completion path */
	अचिन्हित पूर्णांक पढ़ो_count ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक old_ग_लिखो_count;
	अचिन्हित पूर्णांक merge_events;
	अचिन्हित पूर्णांक bytes_compl;
	अचिन्हित पूर्णांक pkts_compl;

	/* Members used only on the xmit path */
	अचिन्हित पूर्णांक insert_count ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक ग_लिखो_count;
	अचिन्हित पूर्णांक old_पढ़ो_count;
	अचिन्हित पूर्णांक pushes;
	bool xmit_more_available;
	अचिन्हित पूर्णांक cb_packets;
	/* Statistics to supplement MAC stats */
	अचिन्हित दीर्घ tx_packets;

	/* Members shared between paths and someबार updated */
	अचिन्हित पूर्णांक empty_पढ़ो_count ____cacheline_aligned_in_smp;
#घोषणा EF4_EMPTY_COUNT_VALID 0x80000000
	atomic_t flush_outstanding;
पूर्ण;

#घोषणा EF4_TX_CB_ORDER	7
#घोषणा EF4_TX_CB_SIZE	(1 << EF4_TX_CB_ORDER) - NET_IP_ALIGN

/**
 * काष्ठा ef4_rx_buffer - An Efx RX data buffer
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
काष्ठा ef4_rx_buffer अणु
	dma_addr_t dma_addr;
	काष्ठा page *page;
	u16 page_offset;
	u16 len;
	u16 flags;
पूर्ण;
#घोषणा EF4_RX_BUF_LAST_IN_PAGE	0x0001
#घोषणा EF4_RX_PKT_CSUMMED	0x0002
#घोषणा EF4_RX_PKT_DISCARD	0x0004
#घोषणा EF4_RX_PKT_TCP		0x0040
#घोषणा EF4_RX_PKT_PREFIX_LEN	0x0080	/* length is in prefix only */

/**
 * काष्ठा ef4_rx_page_state - Page-based rx buffer state
 *
 * Inserted at the start of every page allocated क्रम receive buffers.
 * Used to facilitate sharing dma mappings between recycled rx buffers
 * and those passed up to the kernel.
 *
 * @dma_addr: The dma address of this page.
 */
काष्ठा ef4_rx_page_state अणु
	dma_addr_t dma_addr;

	अचिन्हित पूर्णांक __pad[] ____cacheline_aligned;
पूर्ण;

/**
 * काष्ठा ef4_rx_queue - An Efx RX queue
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
 * @slow_fill: Timer used to defer ef4_nic_generate_fill_event().
 */
काष्ठा ef4_rx_queue अणु
	काष्ठा ef4_nic *efx;
	पूर्णांक core_index;
	काष्ठा ef4_rx_buffer *buffer;
	काष्ठा ef4_special_buffer rxd;
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
पूर्ण;

/**
 * काष्ठा ef4_channel - An Efx channel
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
 * @rx_pkt_n_frags: Number of fragments in next packet to be delivered by
 *	__ef4_rx_packet(), or zero अगर there is none
 * @rx_pkt_index: Ring index of first buffer क्रम next packet to be delivered
 *	by __ef4_rx_packet(), अगर @rx_pkt_n_frags != 0
 * @rx_queue: RX queue क्रम this channel
 * @tx_queue: TX queues क्रम this channel
 */
काष्ठा ef4_channel अणु
	काष्ठा ef4_nic *efx;
	पूर्णांक channel;
	स्थिर काष्ठा ef4_channel_type *type;
	bool eventq_init;
	bool enabled;
	पूर्णांक irq;
	अचिन्हित पूर्णांक irq_moderation_us;
	काष्ठा net_device *napi_dev;
	काष्ठा napi_काष्ठा napi_str;
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित दीर्घ busy_poll_state;
#पूर्ण_अगर
	काष्ठा ef4_special_buffer eventq;
	अचिन्हित पूर्णांक eventq_mask;
	अचिन्हित पूर्णांक eventq_पढ़ो_ptr;
	पूर्णांक event_test_cpu;

	अचिन्हित पूर्णांक irq_count;
	अचिन्हित पूर्णांक irq_mod_score;
#अगर_घोषित CONFIG_RFS_ACCEL
	अचिन्हित पूर्णांक rfs_filters_added;
#घोषणा RPS_FLOW_ID_INVALID 0xFFFFFFFF
	u32 *rps_flow_id;
#पूर्ण_अगर

	अचिन्हित n_rx_tobe_disc;
	अचिन्हित n_rx_ip_hdr_chksum_err;
	अचिन्हित n_rx_tcp_udp_chksum_err;
	अचिन्हित n_rx_mcast_mismatch;
	अचिन्हित n_rx_frm_trunc;
	अचिन्हित n_rx_overlength;
	अचिन्हित n_skbuff_leaks;
	अचिन्हित पूर्णांक n_rx_nodesc_trunc;
	अचिन्हित पूर्णांक n_rx_merge_events;
	अचिन्हित पूर्णांक n_rx_merge_packets;

	अचिन्हित पूर्णांक rx_pkt_n_frags;
	अचिन्हित पूर्णांक rx_pkt_index;

	काष्ठा ef4_rx_queue rx_queue;
	काष्ठा ef4_tx_queue tx_queue[EF4_TXQ_TYPES];
पूर्ण;

/**
 * काष्ठा ef4_msi_context - Context क्रम each MSI
 * @efx: The associated NIC
 * @index: Index of the channel/IRQ
 * @name: Name of the channel/IRQ
 *
 * Unlike &काष्ठा ef4_channel, this is never पुनः_स्मृतिated and is always
 * safe क्रम the IRQ handler to access.
 */
काष्ठा ef4_msi_context अणु
	काष्ठा ef4_nic *efx;
	अचिन्हित पूर्णांक index;
	अक्षर name[IFNAMSIZ + 6];
पूर्ण;

/**
 * काष्ठा ef4_channel_type - distinguishes traffic and extra channels
 * @handle_no_channel: Handle failure to allocate an extra channel
 * @pre_probe: Set up extra state prior to initialisation
 * @post_हटाओ: Tear करोwn extra state after finalisation, अगर allocated.
 *	May be called on channels that have not been probed.
 * @get_name: Generate the channel's name (used क्रम its IRQ handler)
 * @copy: Copy the channel state prior to पुनः_स्मृतिation.  May be %शून्य अगर
 *	पुनः_स्मृतिation is not supported.
 * @receive_skb: Handle an skb पढ़ोy to be passed to netअगर_receive_skb()
 * @keep_eventq: Flag क्रम whether event queue should be kept initialised
 *	जबतक the device is stopped
 */
काष्ठा ef4_channel_type अणु
	व्योम (*handle_no_channel)(काष्ठा ef4_nic *);
	पूर्णांक (*pre_probe)(काष्ठा ef4_channel *);
	व्योम (*post_हटाओ)(काष्ठा ef4_channel *);
	व्योम (*get_name)(काष्ठा ef4_channel *, अक्षर *buf, माप_प्रकार len);
	काष्ठा ef4_channel *(*copy)(स्थिर काष्ठा ef4_channel *);
	bool (*receive_skb)(काष्ठा ef4_channel *, काष्ठा sk_buff *);
	bool keep_eventq;
पूर्ण;

क्रमागत ef4_led_mode अणु
	EF4_LED_OFF	= 0,
	EF4_LED_ON	= 1,
	EF4_LED_DEFAULT	= 2
पूर्ण;

#घोषणा STRING_TABLE_LOOKUP(val, member) \
	((val) < member ## _max) ? member ## _names[val] : "(invalid)"

बाह्य स्थिर अक्षर *स्थिर ef4_loopback_mode_names[];
बाह्य स्थिर अचिन्हित पूर्णांक ef4_loopback_mode_max;
#घोषणा LOOPBACK_MODE(efx) \
	STRING_TABLE_LOOKUP((efx)->loopback_mode, ef4_loopback_mode)

बाह्य स्थिर अक्षर *स्थिर ef4_reset_type_names[];
बाह्य स्थिर अचिन्हित पूर्णांक ef4_reset_type_max;
#घोषणा RESET_TYPE(type) \
	STRING_TABLE_LOOKUP(type, ef4_reset_type)

क्रमागत ef4_पूर्णांक_mode अणु
	/* Be careful अगर altering to correct macro below */
	EF4_INT_MODE_MSIX = 0,
	EF4_INT_MODE_MSI = 1,
	EF4_INT_MODE_LEGACY = 2,
	EF4_INT_MODE_MAX	/* Insert any new items beक्रमe this */
पूर्ण;
#घोषणा EF4_INT_MODE_USE_MSI(x) (((x)->पूर्णांकerrupt_mode) <= EF4_INT_MODE_MSI)

क्रमागत nic_state अणु
	STATE_UNINIT = 0,	/* device being probed/हटाओd or is frozen */
	STATE_READY = 1,	/* hardware पढ़ोy and netdev रेजिस्टरed */
	STATE_DISABLED = 2,	/* device disabled due to hardware errors */
	STATE_RECOVERY = 3,	/* device recovering from PCI error */
पूर्ण;

/* Forward declaration */
काष्ठा ef4_nic;

/* Pseuकरो bit-mask flow control field */
#घोषणा EF4_FC_RX	FLOW_CTRL_RX
#घोषणा EF4_FC_TX	FLOW_CTRL_TX
#घोषणा EF4_FC_AUTO	4

/**
 * काष्ठा ef4_link_state - Current state of the link
 * @up: Link is up
 * @fd: Link is full-duplex
 * @fc: Actual flow control flags
 * @speed: Link speed (Mbps)
 */
काष्ठा ef4_link_state अणु
	bool up;
	bool fd;
	u8 fc;
	अचिन्हित पूर्णांक speed;
पूर्ण;

अटल अंतरभूत bool ef4_link_state_equal(स्थिर काष्ठा ef4_link_state *left,
					स्थिर काष्ठा ef4_link_state *right)
अणु
	वापस left->up == right->up && left->fd == right->fd &&
		left->fc == right->fc && left->speed == right->speed;
पूर्ण

/**
 * काष्ठा ef4_phy_operations - Efx PHY operations table
 * @probe: Probe PHY and initialise efx->mdio.mode_support, efx->mdio.mmds,
 *	efx->loopback_modes.
 * @init: Initialise PHY
 * @fini: Shut करोwn PHY
 * @reconfigure: Reconfigure PHY (e.g. क्रम new link parameters)
 * @poll: Update @link_state and report whether it changed.
 *	Serialised by the mac_lock.
 * @get_link_ksettings: Get ethtool settings. Serialised by the mac_lock.
 * @set_link_ksettings: Set ethtool settings. Serialised by the mac_lock.
 * @set_npage_adv: Set abilities advertised in (Extended) Next Page
 *	(only needed where AN bit is set in mmds)
 * @test_alive: Test that PHY is 'alive' (online)
 * @test_name: Get the name of a PHY-specअगरic test/result
 * @run_tests: Run tests and record results as appropriate (offline).
 *	Flags are the ethtool tests flags.
 */
काष्ठा ef4_phy_operations अणु
	पूर्णांक (*probe) (काष्ठा ef4_nic *efx);
	पूर्णांक (*init) (काष्ठा ef4_nic *efx);
	व्योम (*fini) (काष्ठा ef4_nic *efx);
	व्योम (*हटाओ) (काष्ठा ef4_nic *efx);
	पूर्णांक (*reconfigure) (काष्ठा ef4_nic *efx);
	bool (*poll) (काष्ठा ef4_nic *efx);
	व्योम (*get_link_ksettings)(काष्ठा ef4_nic *efx,
				   काष्ठा ethtool_link_ksettings *cmd);
	पूर्णांक (*set_link_ksettings)(काष्ठा ef4_nic *efx,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd);
	व्योम (*set_npage_adv) (काष्ठा ef4_nic *efx, u32);
	पूर्णांक (*test_alive) (काष्ठा ef4_nic *efx);
	स्थिर अक्षर *(*test_name) (काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक index);
	पूर्णांक (*run_tests) (काष्ठा ef4_nic *efx, पूर्णांक *results, अचिन्हित flags);
	पूर्णांक (*get_module_eeprom) (काष्ठा ef4_nic *efx,
			       काष्ठा ethtool_eeprom *ee,
			       u8 *data);
	पूर्णांक (*get_module_info) (काष्ठा ef4_nic *efx,
				काष्ठा ethtool_modinfo *modinfo);
पूर्ण;

/**
 * क्रमागत ef4_phy_mode - PHY operating mode flags
 * @PHY_MODE_NORMAL: on and should pass traffic
 * @PHY_MODE_TX_DISABLED: on with TX disabled
 * @PHY_MODE_LOW_POWER: set to low घातer through MDIO
 * @PHY_MODE_OFF: चयनed off through बाह्यal control
 * @PHY_MODE_SPECIAL: on but will not pass traffic
 */
क्रमागत ef4_phy_mode अणु
	PHY_MODE_NORMAL		= 0,
	PHY_MODE_TX_DISABLED	= 1,
	PHY_MODE_LOW_POWER	= 2,
	PHY_MODE_OFF		= 4,
	PHY_MODE_SPECIAL	= 8,
पूर्ण;

अटल अंतरभूत bool ef4_phy_mode_disabled(क्रमागत ef4_phy_mode mode)
अणु
	वापस !!(mode & ~PHY_MODE_TX_DISABLED);
पूर्ण

/**
 * काष्ठा ef4_hw_stat_desc - Description of a hardware statistic
 * @name: Name of the statistic as visible through ethtool, or %शून्य अगर
 *	it should not be exposed
 * @dma_width: Width in bits (0 क्रम non-DMA statistics)
 * @offset: Offset within stats (ignored क्रम non-DMA statistics)
 */
काष्ठा ef4_hw_stat_desc अणु
	स्थिर अक्षर *name;
	u16 dma_width;
	u16 offset;
पूर्ण;

/* Number of bits used in a multicast filter hash address */
#घोषणा EF4_MCAST_HASH_BITS 8

/* Number of (single-bit) entries in a multicast filter hash */
#घोषणा EF4_MCAST_HASH_ENTRIES (1 << EF4_MCAST_HASH_BITS)

/* An Efx multicast filter hash */
जोड़ ef4_multicast_hash अणु
	u8 byte[EF4_MCAST_HASH_ENTRIES / 8];
	ef4_oword_t oword[EF4_MCAST_HASH_ENTRIES / माप(ef4_oword_t) / 8];
पूर्ण;

/**
 * काष्ठा ef4_nic - an Efx NIC
 * @name: Device name (net device name or bus id beक्रमe net device रेजिस्टरed)
 * @pci_dev: The PCI device
 * @node: List node क्रम मुख्यtaining primary/secondary function lists
 * @primary: &काष्ठा ef4_nic instance क्रम the primary function of this
 *	controller.  May be the same काष्ठाure, and may be %शून्य अगर no
 *	primary function is bound.  Serialised by rtnl_lock.
 * @secondary_list: List of &काष्ठा ef4_nic instances क्रम the secondary PCI
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
 * @पूर्णांकerrupt_mode: Interrupt mode
 * @समयr_quantum_ns: Interrupt समयr quantum, in nanoseconds
 * @समयr_max_ns: Interrupt समयr maximum value, in nanoseconds
 * @irq_rx_adaptive: Adaptive IRQ moderation enabled क्रम RX event queues
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
 *	(valid only क्रम NICs that set %EF4_RX_PKT_PREFIX_LEN; always negative)
 * @rx_packet_ts_offset: Offset of बारtamp from start of packet data
 *	(valid only अगर channel->sync_बारtamps_enabled; always negative)
 * @rx_hash_key: Toeplitz hash key क्रम RSS
 * @rx_indir_table: Indirection table क्रम RSS
 * @rx_scatter: Scatter mode enabled क्रम receives
 * @पूर्णांक_error_count: Number of पूर्णांकernal errors seen recently
 * @पूर्णांक_error_expire: Time at which error count will be expired
 * @irq_soft_enabled: Are IRQs soft-enabled? If not, IRQ handler will
 *	acknowledge but करो nothing अन्यथा.
 * @irq_status: Interrupt status buffer
 * @irq_zero_count: Number of legacy IRQs seen with queue flags == 0
 * @irq_level: IRQ level/index क्रम IRQs not triggered by an event queue
 * @selftest_work: Work item क्रम asynchronous self-test
 * @mtd_list: List of MTDs attached to the NIC
 * @nic_data: Hardware dependent state
 * @mac_lock: MAC access lock. Protects @port_enabled, @phy_mode,
 *	ef4_monitor() and ef4_reconfigure_port()
 * @port_enabled: Port enabled indicator.
 *	Serialises ef4_stop_all(), ef4_start_all(), ef4_monitor() and
 *	ef4_mac_work() with kernel पूर्णांकerfaces. Safe to पढ़ो under any
 *	one of the rtnl_lock, mac_lock, or netअगर_tx_lock, but all three must
 *	be held to modअगरy it.
 * @port_initialized: Port initialized?
 * @net_dev: Operating प्रणाली network device. Consider holding the rtnl lock
 * @fixed_features: Features which cannot be turned off
 * @stats_buffer: DMA buffer क्रम statistics
 * @phy_type: PHY type
 * @phy_op: PHY पूर्णांकerface
 * @phy_data: PHY निजी data (including PHY-specअगरic stats)
 * @mdio: PHY MDIO पूर्णांकerface
 * @phy_mode: PHY operating mode. Serialised by @mac_lock.
 * @link_advertising: Autonegotiation advertising flags
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
 * @filter_sem: Filter table rw_semaphore, क्रम मुक्तing the table
 * @filter_lock: Filter table lock, क्रम mere content changes
 * @filter_state: Architecture-dependent filter table state
 * @rps_expire_channel: Next channel to check क्रम expiry
 * @rps_expire_index: Next index to check क्रम expiry in
 *	@rps_expire_channel's @rps_flow_id
 * @active_queues: Count of RX and TX queues that haven't been flushed and drained.
 * @rxq_flush_pending: Count of number of receive queues that need to be flushed.
 *	Decremented when the ef4_flush_rx_queue() is called.
 * @rxq_flush_outstanding: Count of number of RX flushes started but not yet
 *	completed (either success or failure). Not used when MCDI is used to
 *	flush receive queues.
 * @flush_wq: रुको queue used by ef4_nic_flush_queues() to रुको क्रम flush completions.
 * @vpd_sn: Serial number पढ़ो from VPD
 * @monitor_work: Hardware monitor workitem
 * @biu_lock: BIU (bus पूर्णांकerface unit) lock
 * @last_irq_cpu: Last CPU to handle a possible test पूर्णांकerrupt.  This
 *	field is used by ef4_test_पूर्णांकerrupts() to verअगरy that an
 *	पूर्णांकerrupt has occurred.
 * @stats_lock: Statistics update lock. Must be held when calling
 *	ef4_nic_type::अणुupdate,start,stopपूर्ण_stats.
 * @n_rx_noskb_drops: Count of RX packets dropped due to failure to allocate an skb
 *
 * This is stored in the निजी area of the &काष्ठा net_device.
 */
काष्ठा ef4_nic अणु
	/* The following fields should be written very rarely */

	अक्षर name[IFNAMSIZ];
	काष्ठा list_head node;
	काष्ठा ef4_nic *primary;
	काष्ठा list_head secondary_list;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित पूर्णांक port_num;
	स्थिर काष्ठा ef4_nic_type *type;
	पूर्णांक legacy_irq;
	bool eeh_disabled_legacy_irq;
	काष्ठा workqueue_काष्ठा *workqueue;
	अक्षर workqueue_name[16];
	काष्ठा work_काष्ठा reset_work;
	resource_माप_प्रकार membase_phys;
	व्योम __iomem *membase;

	क्रमागत ef4_पूर्णांक_mode पूर्णांकerrupt_mode;
	अचिन्हित पूर्णांक समयr_quantum_ns;
	अचिन्हित पूर्णांक समयr_max_ns;
	bool irq_rx_adaptive;
	अचिन्हित पूर्णांक irq_mod_step_us;
	अचिन्हित पूर्णांक irq_rx_moderation_us;
	u32 msg_enable;

	क्रमागत nic_state state;
	अचिन्हित दीर्घ reset_pending;

	काष्ठा ef4_channel *channel[EF4_MAX_CHANNELS];
	काष्ठा ef4_msi_context msi_context[EF4_MAX_CHANNELS];
	स्थिर काष्ठा ef4_channel_type *
	extra_channel_type[EF4_MAX_EXTRA_CHANNELS];

	अचिन्हित rxq_entries;
	अचिन्हित txq_entries;
	अचिन्हित पूर्णांक txq_stop_thresh;
	अचिन्हित पूर्णांक txq_wake_thresh;

	अचिन्हित tx_dc_base;
	अचिन्हित rx_dc_base;
	अचिन्हित sram_lim_qw;
	अचिन्हित next_buffer_table;

	अचिन्हित पूर्णांक max_channels;
	अचिन्हित पूर्णांक max_tx_channels;
	अचिन्हित n_channels;
	अचिन्हित n_rx_channels;
	अचिन्हित rss_spपढ़ो;
	अचिन्हित tx_channel_offset;
	अचिन्हित n_tx_channels;
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
	u8 rx_hash_key[40];
	u32 rx_indir_table[128];
	bool rx_scatter;

	अचिन्हित पूर्णांक_error_count;
	अचिन्हित दीर्घ पूर्णांक_error_expire;

	bool irq_soft_enabled;
	काष्ठा ef4_buffer irq_status;
	अचिन्हित irq_zero_count;
	अचिन्हित irq_level;
	काष्ठा delayed_work selftest_work;

#अगर_घोषित CONFIG_SFC_FALCON_MTD
	काष्ठा list_head mtd_list;
#पूर्ण_अगर

	व्योम *nic_data;

	काष्ठा mutex mac_lock;
	काष्ठा work_काष्ठा mac_work;
	bool port_enabled;

	bool mc_bist_क्रम_other_fn;
	bool port_initialized;
	काष्ठा net_device *net_dev;

	netdev_features_t fixed_features;

	काष्ठा ef4_buffer stats_buffer;
	u64 rx_nodesc_drops_total;
	u64 rx_nodesc_drops_जबतक_करोwn;
	bool rx_nodesc_drops_prev_state;

	अचिन्हित पूर्णांक phy_type;
	स्थिर काष्ठा ef4_phy_operations *phy_op;
	व्योम *phy_data;
	काष्ठा mdio_अगर_info mdio;
	क्रमागत ef4_phy_mode phy_mode;

	u32 link_advertising;
	काष्ठा ef4_link_state link_state;
	अचिन्हित पूर्णांक n_link_state_changes;

	bool unicast_filter;
	जोड़ ef4_multicast_hash multicast_hash;
	u8 wanted_fc;
	अचिन्हित fc_disable;

	atomic_t rx_reset;
	क्रमागत ef4_loopback_mode loopback_mode;
	u64 loopback_modes;

	व्योम *loopback_selftest;

	काष्ठा rw_semaphore filter_sem;
	spinlock_t filter_lock;
	व्योम *filter_state;
#अगर_घोषित CONFIG_RFS_ACCEL
	अचिन्हित पूर्णांक rps_expire_channel;
	अचिन्हित पूर्णांक rps_expire_index;
#पूर्ण_अगर

	atomic_t active_queues;
	atomic_t rxq_flush_pending;
	atomic_t rxq_flush_outstanding;
	रुको_queue_head_t flush_wq;

	अक्षर *vpd_sn;

	/* The following fields may be written more often */

	काष्ठा delayed_work monitor_work ____cacheline_aligned_in_smp;
	spinlock_t biu_lock;
	पूर्णांक last_irq_cpu;
	spinlock_t stats_lock;
	atomic_t n_rx_noskb_drops;
पूर्ण;

अटल अंतरभूत पूर्णांक ef4_dev_रेजिस्टरed(काष्ठा ef4_nic *efx)
अणु
	वापस efx->net_dev->reg_state == NETREG_REGISTERED;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ef4_port_num(काष्ठा ef4_nic *efx)
अणु
	वापस efx->port_num;
पूर्ण

काष्ठा ef4_mtd_partition अणु
	काष्ठा list_head node;
	काष्ठा mtd_info mtd;
	स्थिर अक्षर *dev_type_name;
	स्थिर अक्षर *type_name;
	अक्षर name[IFNAMSIZ + 20];
पूर्ण;

/**
 * काष्ठा ef4_nic_type - Efx device type definition
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
 * @start_stats: Start the regular fetching of statistics
 * @pull_stats: Pull stats from the NIC and रुको until they arrive.
 * @stop_stats: Stop the regular fetching of statistics
 * @set_id_led: Set state of identअगरying LED or revert to स्वतःmatic function
 * @push_irq_moderation: Apply पूर्णांकerrupt moderation value
 * @reconfigure_port: Push loopback/घातer/txdis changes to the MAC and PHY
 * @prepare_enable_fc_tx: Prepare MAC to enable छोड़ो frame TX (may be %शून्य)
 * @reconfigure_mac: Push MAC address, MTU, flow control and filter settings
 *	to the hardware.  Serialised by the mac_lock.
 * @check_mac_fault: Check MAC fault state. True अगर fault present.
 * @get_wol: Get WoL configuration from driver state
 * @set_wol: Push WoL configuration to the NIC
 * @resume_wol: Synchronise WoL state between driver and MC (e.g. after resume)
 * @test_chip: Test रेजिस्टरs.  May use ef4_farch_test_रेजिस्टरs(), and is
 *	expected to reset the NIC.
 * @test_nvram: Test validity of NVRAM contents
 * @irq_enable_master: Enable IRQs on the NIC.  Each event queue must
 *	be separately enabled after this.
 * @irq_test_generate: Generate a test IRQ
 * @irq_disable_non_ev: Disable non-event IRQs on the NIC.  Each event
 *	queue must be separately disabled beक्रमe this.
 * @irq_handle_msi: Handle MSI क्रम a channel.  The @dev_id argument is
 *	a poपूर्णांकer to the &काष्ठा ef4_msi_context क्रम the channel.
 * @irq_handle_legacy: Handle legacy पूर्णांकerrupt.  The @dev_id argument
 *	is a poपूर्णांकer to the &काष्ठा ef4_nic.
 * @tx_probe: Allocate resources क्रम TX queue
 * @tx_init: Initialise TX queue on the NIC
 * @tx_हटाओ: Free resources क्रम TX queue
 * @tx_ग_लिखो: Write TX descriptors and करोorbell
 * @rx_push_rss_config: Write RSS hash key and indirection table to the NIC
 * @rx_probe: Allocate resources क्रम RX queue
 * @rx_init: Initialise RX queue on the NIC
 * @rx_हटाओ: Free resources क्रम RX queue
 * @rx_ग_लिखो: Write RX descriptors and करोorbell
 * @rx_defer_refill: Generate a refill reminder event
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
 *	equal to the given priority and is not %EF4_FILTER_PRI_AUTO
 * @filter_count_rx_used: Get the number of filters in use at a given priority
 * @filter_get_rx_id_limit: Get maximum value of a filter id, plus 1
 * @filter_get_rx_ids: Get list of RX filters at a given priority
 * @filter_rfs_insert: Add or replace a filter क्रम RFS.  This must be
 *	atomic.  The hardware change may be asynchronous but should
 *	not be delayed क्रम दीर्घ.  It may fail अगर this can't be करोne
 *	atomically.
 * @filter_rfs_expire_one: Consider expiring a filter inserted क्रम RFS.
 *	This must check whether the specअगरied table entry is used by RFS
 *	and that rps_may_expire_flow() वापसs true क्रम it.
 * @mtd_probe: Probe and add MTD partitions associated with this net device,
 *	 using ef4_mtd_add()
 * @mtd_नाम: Set an MTD partition name using the net device name
 * @mtd_पढ़ो: Read from an MTD partition
 * @mtd_erase: Erase part of an MTD partition
 * @mtd_ग_लिखो: Write to an MTD partition
 * @mtd_sync: Wait क्रम ग_लिखो-back to complete on MTD partition.  This
 *	also notअगरies the driver that a ग_लिखोr has finished using this
 *	partition.
 * @set_mac_address: Set the MAC address of the device
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
 * @max_पूर्णांकerrupt_mode: Highest capability पूर्णांकerrupt mode supported
 *	from &क्रमागत ef4_init_mode.
 * @समयr_period_max: Maximum period of पूर्णांकerrupt समयr (in ticks)
 * @offload_features: net_device feature flags क्रम protocol offload
 *	features implemented in hardware
 */
काष्ठा ef4_nic_type अणु
	अचिन्हित पूर्णांक mem_bar;
	अचिन्हित पूर्णांक (*mem_map_size)(काष्ठा ef4_nic *efx);
	पूर्णांक (*probe)(काष्ठा ef4_nic *efx);
	व्योम (*हटाओ)(काष्ठा ef4_nic *efx);
	पूर्णांक (*init)(काष्ठा ef4_nic *efx);
	पूर्णांक (*dimension_resources)(काष्ठा ef4_nic *efx);
	व्योम (*fini)(काष्ठा ef4_nic *efx);
	व्योम (*monitor)(काष्ठा ef4_nic *efx);
	क्रमागत reset_type (*map_reset_reason)(क्रमागत reset_type reason);
	पूर्णांक (*map_reset_flags)(u32 *flags);
	पूर्णांक (*reset)(काष्ठा ef4_nic *efx, क्रमागत reset_type method);
	पूर्णांक (*probe_port)(काष्ठा ef4_nic *efx);
	व्योम (*हटाओ_port)(काष्ठा ef4_nic *efx);
	bool (*handle_global_event)(काष्ठा ef4_channel *channel, ef4_qword_t *);
	पूर्णांक (*fini_dmaq)(काष्ठा ef4_nic *efx);
	व्योम (*prepare_flush)(काष्ठा ef4_nic *efx);
	व्योम (*finish_flush)(काष्ठा ef4_nic *efx);
	व्योम (*prepare_flr)(काष्ठा ef4_nic *efx);
	व्योम (*finish_flr)(काष्ठा ef4_nic *efx);
	माप_प्रकार (*describe_stats)(काष्ठा ef4_nic *efx, u8 *names);
	माप_प्रकार (*update_stats)(काष्ठा ef4_nic *efx, u64 *full_stats,
			       काष्ठा rtnl_link_stats64 *core_stats);
	व्योम (*start_stats)(काष्ठा ef4_nic *efx);
	व्योम (*pull_stats)(काष्ठा ef4_nic *efx);
	व्योम (*stop_stats)(काष्ठा ef4_nic *efx);
	व्योम (*set_id_led)(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode);
	व्योम (*push_irq_moderation)(काष्ठा ef4_channel *channel);
	पूर्णांक (*reconfigure_port)(काष्ठा ef4_nic *efx);
	व्योम (*prepare_enable_fc_tx)(काष्ठा ef4_nic *efx);
	पूर्णांक (*reconfigure_mac)(काष्ठा ef4_nic *efx);
	bool (*check_mac_fault)(काष्ठा ef4_nic *efx);
	व्योम (*get_wol)(काष्ठा ef4_nic *efx, काष्ठा ethtool_wolinfo *wol);
	पूर्णांक (*set_wol)(काष्ठा ef4_nic *efx, u32 type);
	व्योम (*resume_wol)(काष्ठा ef4_nic *efx);
	पूर्णांक (*test_chip)(काष्ठा ef4_nic *efx, काष्ठा ef4_self_tests *tests);
	पूर्णांक (*test_nvram)(काष्ठा ef4_nic *efx);
	व्योम (*irq_enable_master)(काष्ठा ef4_nic *efx);
	पूर्णांक (*irq_test_generate)(काष्ठा ef4_nic *efx);
	व्योम (*irq_disable_non_ev)(काष्ठा ef4_nic *efx);
	irqवापस_t (*irq_handle_msi)(पूर्णांक irq, व्योम *dev_id);
	irqवापस_t (*irq_handle_legacy)(पूर्णांक irq, व्योम *dev_id);
	पूर्णांक (*tx_probe)(काष्ठा ef4_tx_queue *tx_queue);
	व्योम (*tx_init)(काष्ठा ef4_tx_queue *tx_queue);
	व्योम (*tx_हटाओ)(काष्ठा ef4_tx_queue *tx_queue);
	व्योम (*tx_ग_लिखो)(काष्ठा ef4_tx_queue *tx_queue);
	अचिन्हित पूर्णांक (*tx_limit_len)(काष्ठा ef4_tx_queue *tx_queue,
				     dma_addr_t dma_addr, अचिन्हित पूर्णांक len);
	पूर्णांक (*rx_push_rss_config)(काष्ठा ef4_nic *efx, bool user,
				  स्थिर u32 *rx_indir_table);
	पूर्णांक (*rx_probe)(काष्ठा ef4_rx_queue *rx_queue);
	व्योम (*rx_init)(काष्ठा ef4_rx_queue *rx_queue);
	व्योम (*rx_हटाओ)(काष्ठा ef4_rx_queue *rx_queue);
	व्योम (*rx_ग_लिखो)(काष्ठा ef4_rx_queue *rx_queue);
	व्योम (*rx_defer_refill)(काष्ठा ef4_rx_queue *rx_queue);
	पूर्णांक (*ev_probe)(काष्ठा ef4_channel *channel);
	पूर्णांक (*ev_init)(काष्ठा ef4_channel *channel);
	व्योम (*ev_fini)(काष्ठा ef4_channel *channel);
	व्योम (*ev_हटाओ)(काष्ठा ef4_channel *channel);
	पूर्णांक (*ev_process)(काष्ठा ef4_channel *channel, पूर्णांक quota);
	व्योम (*ev_पढ़ो_ack)(काष्ठा ef4_channel *channel);
	व्योम (*ev_test_generate)(काष्ठा ef4_channel *channel);
	पूर्णांक (*filter_table_probe)(काष्ठा ef4_nic *efx);
	व्योम (*filter_table_restore)(काष्ठा ef4_nic *efx);
	व्योम (*filter_table_हटाओ)(काष्ठा ef4_nic *efx);
	व्योम (*filter_update_rx_scatter)(काष्ठा ef4_nic *efx);
	s32 (*filter_insert)(काष्ठा ef4_nic *efx,
			     काष्ठा ef4_filter_spec *spec, bool replace);
	पूर्णांक (*filter_हटाओ_safe)(काष्ठा ef4_nic *efx,
				  क्रमागत ef4_filter_priority priority,
				  u32 filter_id);
	पूर्णांक (*filter_get_safe)(काष्ठा ef4_nic *efx,
			       क्रमागत ef4_filter_priority priority,
			       u32 filter_id, काष्ठा ef4_filter_spec *);
	पूर्णांक (*filter_clear_rx)(काष्ठा ef4_nic *efx,
			       क्रमागत ef4_filter_priority priority);
	u32 (*filter_count_rx_used)(काष्ठा ef4_nic *efx,
				    क्रमागत ef4_filter_priority priority);
	u32 (*filter_get_rx_id_limit)(काष्ठा ef4_nic *efx);
	s32 (*filter_get_rx_ids)(काष्ठा ef4_nic *efx,
				 क्रमागत ef4_filter_priority priority,
				 u32 *buf, u32 size);
#अगर_घोषित CONFIG_RFS_ACCEL
	s32 (*filter_rfs_insert)(काष्ठा ef4_nic *efx,
				 काष्ठा ef4_filter_spec *spec);
	bool (*filter_rfs_expire_one)(काष्ठा ef4_nic *efx, u32 flow_id,
				      अचिन्हित पूर्णांक index);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SFC_FALCON_MTD
	पूर्णांक (*mtd_probe)(काष्ठा ef4_nic *efx);
	व्योम (*mtd_नाम)(काष्ठा ef4_mtd_partition *part);
	पूर्णांक (*mtd_पढ़ो)(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len,
			माप_प्रकार *retlen, u8 *buffer);
	पूर्णांक (*mtd_erase)(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len);
	पूर्णांक (*mtd_ग_लिखो)(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len,
			 माप_प्रकार *retlen, स्थिर u8 *buffer);
	पूर्णांक (*mtd_sync)(काष्ठा mtd_info *mtd);
#पूर्ण_अगर
	पूर्णांक (*get_mac_address)(काष्ठा ef4_nic *efx, अचिन्हित अक्षर *perm_addr);
	पूर्णांक (*set_mac_address)(काष्ठा ef4_nic *efx);

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
	अचिन्हित पूर्णांक max_पूर्णांकerrupt_mode;
	अचिन्हित पूर्णांक समयr_period_max;
	netdev_features_t offload_features;
	अचिन्हित पूर्णांक max_rx_ip_filters;
पूर्ण;

/**************************************************************************
 *
 * Prototypes and अंतरभूत functions
 *
 *************************************************************************/

अटल अंतरभूत काष्ठा ef4_channel *
ef4_get_channel(काष्ठा ef4_nic *efx, अचिन्हित index)
अणु
	EF4_BUG_ON_PARANOID(index >= efx->n_channels);
	वापस efx->channel[index];
पूर्ण

/* Iterate over all used channels */
#घोषणा ef4_क्रम_each_channel(_channel, _efx)				\
	क्रम (_channel = (_efx)->channel[0];				\
	     _channel;							\
	     _channel = (_channel->channel + 1 < (_efx)->n_channels) ?	\
		     (_efx)->channel[_channel->channel + 1] : शून्य)

/* Iterate over all used channels in reverse */
#घोषणा ef4_क्रम_each_channel_rev(_channel, _efx)			\
	क्रम (_channel = (_efx)->channel[(_efx)->n_channels - 1];	\
	     _channel;							\
	     _channel = _channel->channel ?				\
		     (_efx)->channel[_channel->channel - 1] : शून्य)

अटल अंतरभूत काष्ठा ef4_tx_queue *
ef4_get_tx_queue(काष्ठा ef4_nic *efx, अचिन्हित index, अचिन्हित type)
अणु
	EF4_BUG_ON_PARANOID(index >= efx->n_tx_channels ||
			    type >= EF4_TXQ_TYPES);
	वापस &efx->channel[efx->tx_channel_offset + index]->tx_queue[type];
पूर्ण

अटल अंतरभूत bool ef4_channel_has_tx_queues(काष्ठा ef4_channel *channel)
अणु
	वापस channel->channel - channel->efx->tx_channel_offset <
		channel->efx->n_tx_channels;
पूर्ण

अटल अंतरभूत काष्ठा ef4_tx_queue *
ef4_channel_get_tx_queue(काष्ठा ef4_channel *channel, अचिन्हित type)
अणु
	EF4_BUG_ON_PARANOID(!ef4_channel_has_tx_queues(channel) ||
			    type >= EF4_TXQ_TYPES);
	वापस &channel->tx_queue[type];
पूर्ण

अटल अंतरभूत bool ef4_tx_queue_used(काष्ठा ef4_tx_queue *tx_queue)
अणु
	वापस !(tx_queue->efx->net_dev->num_tc < 2 &&
		 tx_queue->queue & EF4_TXQ_TYPE_HIGHPRI);
पूर्ण

/* Iterate over all TX queues beदीर्घing to a channel */
#घोषणा ef4_क्रम_each_channel_tx_queue(_tx_queue, _channel)		\
	अगर (!ef4_channel_has_tx_queues(_channel))			\
		;							\
	अन्यथा								\
		क्रम (_tx_queue = (_channel)->tx_queue;			\
		     _tx_queue < (_channel)->tx_queue + EF4_TXQ_TYPES && \
			     ef4_tx_queue_used(_tx_queue);		\
		     _tx_queue++)

/* Iterate over all possible TX queues beदीर्घing to a channel */
#घोषणा ef4_क्रम_each_possible_channel_tx_queue(_tx_queue, _channel)	\
	अगर (!ef4_channel_has_tx_queues(_channel))			\
		;							\
	अन्यथा								\
		क्रम (_tx_queue = (_channel)->tx_queue;			\
		     _tx_queue < (_channel)->tx_queue + EF4_TXQ_TYPES;	\
		     _tx_queue++)

अटल अंतरभूत bool ef4_channel_has_rx_queue(काष्ठा ef4_channel *channel)
अणु
	वापस channel->rx_queue.core_index >= 0;
पूर्ण

अटल अंतरभूत काष्ठा ef4_rx_queue *
ef4_channel_get_rx_queue(काष्ठा ef4_channel *channel)
अणु
	EF4_BUG_ON_PARANOID(!ef4_channel_has_rx_queue(channel));
	वापस &channel->rx_queue;
पूर्ण

/* Iterate over all RX queues beदीर्घing to a channel */
#घोषणा ef4_क्रम_each_channel_rx_queue(_rx_queue, _channel)		\
	अगर (!ef4_channel_has_rx_queue(_channel))			\
		;							\
	अन्यथा								\
		क्रम (_rx_queue = &(_channel)->rx_queue;			\
		     _rx_queue;						\
		     _rx_queue = शून्य)

अटल अंतरभूत काष्ठा ef4_channel *
ef4_rx_queue_channel(काष्ठा ef4_rx_queue *rx_queue)
अणु
	वापस container_of(rx_queue, काष्ठा ef4_channel, rx_queue);
पूर्ण

अटल अंतरभूत पूर्णांक ef4_rx_queue_index(काष्ठा ef4_rx_queue *rx_queue)
अणु
	वापस ef4_rx_queue_channel(rx_queue)->channel;
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied receive buffer in the RX
 * descriptor queue.
 */
अटल अंतरभूत काष्ठा ef4_rx_buffer *ef4_rx_buffer(काष्ठा ef4_rx_queue *rx_queue,
						  अचिन्हित पूर्णांक index)
अणु
	वापस &rx_queue->buffer[index];
पूर्ण

/**
 * EF4_MAX_FRAME_LEN - calculate maximum frame length
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
#घोषणा EF4_FRAME_PAD	16
#घोषणा EF4_MAX_FRAME_LEN(mtu) \
	(ALIGN(((mtu) + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN + EF4_FRAME_PAD), 8))

/* Get all supported features.
 * If a feature is not fixed, it is present in hw_features.
 * If a feature is fixed, it करोes not present in hw_features, but
 * always in features.
 */
अटल अंतरभूत netdev_features_t ef4_supported_features(स्थिर काष्ठा ef4_nic *efx)
अणु
	स्थिर काष्ठा net_device *net_dev = efx->net_dev;

	वापस net_dev->features | net_dev->hw_features;
पूर्ण

/* Get the current TX queue insert index. */
अटल अंतरभूत अचिन्हित पूर्णांक
ef4_tx_queue_get_insert_index(स्थिर काष्ठा ef4_tx_queue *tx_queue)
अणु
	वापस tx_queue->insert_count & tx_queue->ptr_mask;
पूर्ण

/* Get a TX buffer. */
अटल अंतरभूत काष्ठा ef4_tx_buffer *
__ef4_tx_queue_get_insert_buffer(स्थिर काष्ठा ef4_tx_queue *tx_queue)
अणु
	वापस &tx_queue->buffer[ef4_tx_queue_get_insert_index(tx_queue)];
पूर्ण

/* Get a TX buffer, checking it's not currently in use. */
अटल अंतरभूत काष्ठा ef4_tx_buffer *
ef4_tx_queue_get_insert_buffer(स्थिर काष्ठा ef4_tx_queue *tx_queue)
अणु
	काष्ठा ef4_tx_buffer *buffer =
		__ef4_tx_queue_get_insert_buffer(tx_queue);

	EF4_BUG_ON_PARANOID(buffer->len);
	EF4_BUG_ON_PARANOID(buffer->flags);
	EF4_BUG_ON_PARANOID(buffer->unmap_len);

	वापस buffer;
पूर्ण

#पूर्ण_अगर /* EF4_NET_DRIVER_H */
