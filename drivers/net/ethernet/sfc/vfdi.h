<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2010-2012 Solarflare Communications Inc.
 */
#अगर_अघोषित _VFDI_H
#घोषणा _VFDI_H

/**
 * DOC: Virtual Function Driver Interface
 *
 * This file contains software काष्ठाures used to क्रमm a two way
 * communication channel between the VF driver and the PF driver,
 * named Virtual Function Driver Interface (VFDI).
 *
 * For the purposes of VFDI, a page is a memory region with size and
 * alignment of 4K.  All addresses are DMA addresses to be used within
 * the करोमुख्य of the relevant VF.
 *
 * The only hardware-defined channels क्रम a VF driver to communicate
 * with the PF driver are the event mailboxes (%FR_CZ_USR_EV
 * रेजिस्टरs).  Writing to these रेजिस्टरs generates an event with
 * EV_CODE = EV_CODE_USR_EV, USER_QID set to the index of the mailbox
 * and USER_EV_REG_VALUE set to the value written.  The PF driver may
 * direct or disable delivery of these events by setting
 * %FR_CZ_USR_EV_CFG.
 *
 * The PF driver can send arbitrary events to arbitrary event queues.
 * However, क्रम consistency, VFDI events from the PF are defined to
 * follow the same क्रमm and be sent to the first event queue asचिन्हित
 * to the VF जबतक that queue is enabled by the VF driver.
 *
 * The general क्रमm of the variable bits of VFDI events is:
 *
 *       0             16                       24   31
 *      | DATA        | TYPE                   | SEQ   |
 *
 * SEQ is a sequence number which should be incremented by 1 (modulo
 * 256) क्रम each event.  The sequence numbers used in each direction
 * are independent.
 *
 * The VF submits requests of type &काष्ठा vfdi_req by sending the
 * address of the request (ADDR) in a series of 4 events:
 *
 *       0             16                       24   31
 *      | ADDR[0:15]  | VFDI_EV_TYPE_REQ_WORD0 | SEQ   |
 *      | ADDR[16:31] | VFDI_EV_TYPE_REQ_WORD1 | SEQ+1 |
 *      | ADDR[32:47] | VFDI_EV_TYPE_REQ_WORD2 | SEQ+2 |
 *      | ADDR[48:63] | VFDI_EV_TYPE_REQ_WORD3 | SEQ+3 |
 *
 * The address must be page-aligned.  After receiving such a valid
 * series of events, the PF driver will attempt to पढ़ो the request
 * and ग_लिखो a response to the same address.  In हाल of an invalid
 * sequence of events or a DMA error, there will be no response.
 *
 * The VF driver may request that the PF driver ग_लिखोs status
 * inक्रमmation पूर्णांकo its करोमुख्य asynchronously.  After writing the
 * status, the PF driver will send an event of the क्रमm:
 *
 *       0             16                       24   31
 *      | reserved    | VFDI_EV_TYPE_STATUS    | SEQ   |
 *
 * In हाल the VF must be reset क्रम any reason, the PF driver will
 * send an event of the क्रमm:
 *
 *       0             16                       24   31
 *      | reserved    | VFDI_EV_TYPE_RESET     | SEQ   |
 *
 * It is then the responsibility of the VF driver to request
 * reinitialisation of its queues.
 */
#घोषणा VFDI_EV_SEQ_LBN 24
#घोषणा VFDI_EV_SEQ_WIDTH 8
#घोषणा VFDI_EV_TYPE_LBN 16
#घोषणा VFDI_EV_TYPE_WIDTH 8
#घोषणा VFDI_EV_TYPE_REQ_WORD0 0
#घोषणा VFDI_EV_TYPE_REQ_WORD1 1
#घोषणा VFDI_EV_TYPE_REQ_WORD2 2
#घोषणा VFDI_EV_TYPE_REQ_WORD3 3
#घोषणा VFDI_EV_TYPE_STATUS 4
#घोषणा VFDI_EV_TYPE_RESET 5
#घोषणा VFDI_EV_DATA_LBN 0
#घोषणा VFDI_EV_DATA_WIDTH 16

काष्ठा vfdi_endpoपूर्णांक अणु
	u8 mac_addr[ETH_ALEN];
	__be16 tci;
पूर्ण;

/**
 * क्रमागत vfdi_op - VFDI operation क्रमागतeration
 * @VFDI_OP_RESPONSE: Indicates a response to the request.
 * @VFDI_OP_INIT_EVQ: Initialize SRAM entries and initialize an EVQ.
 * @VFDI_OP_INIT_RXQ: Initialize SRAM entries and initialize an RXQ.
 * @VFDI_OP_INIT_TXQ: Initialize SRAM entries and initialize a TXQ.
 * @VFDI_OP_FINI_ALL_QUEUES: Flush all queues, finalize all queues, then
 *	finalize the SRAM entries.
 * @VFDI_OP_INSERT_FILTER: Insert a MAC filter targeting the given RXQ.
 * @VFDI_OP_REMOVE_ALL_FILTERS: Remove all filters.
 * @VFDI_OP_SET_STATUS_PAGE: Set the DMA page(s) used क्रम status updates
 *	from PF and ग_लिखो the initial status.
 * @VFDI_OP_CLEAR_STATUS_PAGE: Clear the DMA page(s) used क्रम status
 *	updates from PF.
 */
क्रमागत vfdi_op अणु
	VFDI_OP_RESPONSE = 0,
	VFDI_OP_INIT_EVQ = 1,
	VFDI_OP_INIT_RXQ = 2,
	VFDI_OP_INIT_TXQ = 3,
	VFDI_OP_FINI_ALL_QUEUES = 4,
	VFDI_OP_INSERT_FILTER = 5,
	VFDI_OP_REMOVE_ALL_FILTERS = 6,
	VFDI_OP_SET_STATUS_PAGE = 7,
	VFDI_OP_CLEAR_STATUS_PAGE = 8,
	VFDI_OP_LIMIT,
पूर्ण;

/* Response codes क्रम VFDI operations. Other values may be used in future. */
#घोषणा VFDI_RC_SUCCESS		0
#घोषणा VFDI_RC_ENOMEM		(-12)
#घोषणा VFDI_RC_EINVAL		(-22)
#घोषणा VFDI_RC_EOPNOTSUPP	(-95)
#घोषणा VFDI_RC_ETIMEDOUT	(-110)

/**
 * काष्ठा vfdi_req - Request from VF driver to PF driver
 * @op: Operation code or response indicator, taken from &क्रमागत vfdi_op.
 * @rc: Response code.  Set to 0 on success or a negative error code on failure.
 * @u.init_evq.index: Index of event queue to create.
 * @u.init_evq.buf_count: Number of 4k buffers backing event queue.
 * @u.init_evq.addr: Array of length %u.init_evq.buf_count containing DMA
 *	address of each page backing the event queue.
 * @u.init_rxq.index: Index of receive queue to create.
 * @u.init_rxq.buf_count: Number of 4k buffers backing receive queue.
 * @u.init_rxq.evq: Instance of event queue to target receive events at.
 * @u.init_rxq.label: Label used in receive events.
 * @u.init_rxq.flags: Unused.
 * @u.init_rxq.addr: Array of length %u.init_rxq.buf_count containing DMA
 *	address of each page backing the receive queue.
 * @u.init_txq.index: Index of transmit queue to create.
 * @u.init_txq.buf_count: Number of 4k buffers backing transmit queue.
 * @u.init_txq.evq: Instance of event queue to target transmit completion
 *	events at.
 * @u.init_txq.label: Label used in transmit completion events.
 * @u.init_txq.flags: Checksum offload flags.
 * @u.init_txq.addr: Array of length %u.init_txq.buf_count containing DMA
 *	address of each page backing the transmit queue.
 * @u.mac_filter.rxq: Insert MAC filter at VF local address/VLAN targeting
 *	all traffic at this receive queue.
 * @u.mac_filter.flags: MAC filter flags.
 * @u.set_status_page.dma_addr: Base address क्रम the &काष्ठा vfdi_status.
 *	This address must be page-aligned and the PF may ग_लिखो up to a
 *	whole page (allowing क्रम extension of the काष्ठाure).
 * @u.set_status_page.peer_page_count: Number of additional pages the VF
 *	has provided पूर्णांकo which peer addresses may be DMAd.
 * @u.set_status_page.peer_page_addr: Array of DMA addresses of pages.
 *	If the number of peers exceeds 256, then the VF must provide
 *	additional pages in this array. The PF will then DMA up to
 *	512 vfdi_endpoपूर्णांक काष्ठाures पूर्णांकo each page.  These addresses
 *	must be page-aligned.
 */
काष्ठा vfdi_req अणु
	u32 op;
	u32 reserved1;
	s32 rc;
	u32 reserved2;
	जोड़ अणु
		काष्ठा अणु
			u32 index;
			u32 buf_count;
			u64 addr[];
		पूर्ण init_evq;
		काष्ठा अणु
			u32 index;
			u32 buf_count;
			u32 evq;
			u32 label;
			u32 flags;
#घोषणा VFDI_RXQ_FLAG_SCATTER_EN 1
			u32 reserved;
			u64 addr[];
		पूर्ण init_rxq;
		काष्ठा अणु
			u32 index;
			u32 buf_count;
			u32 evq;
			u32 label;
			u32 flags;
#घोषणा VFDI_TXQ_FLAG_IP_CSUM_DIS 1
#घोषणा VFDI_TXQ_FLAG_TCPUDP_CSUM_DIS 2
			u32 reserved;
			u64 addr[];
		पूर्ण init_txq;
		काष्ठा अणु
			u32 rxq;
			u32 flags;
#घोषणा VFDI_MAC_FILTER_FLAG_RSS 1
#घोषणा VFDI_MAC_FILTER_FLAG_SCATTER 2
		पूर्ण mac_filter;
		काष्ठा अणु
			u64 dma_addr;
			u64 peer_page_count;
			u64 peer_page_addr[];
		पूर्ण set_status_page;
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा vfdi_status - Status provided by PF driver to VF driver
 * @generation_start: A generation count DMA'd to VF *beक्रमe* the
 *	rest of the काष्ठाure.
 * @generation_end: A generation count DMA'd to VF *after* the
 *	rest of the काष्ठाure.
 * @version: Version of this काष्ठाure; currently set to 1.  Later
 *	versions must either be layout-compatible or only be sent to VFs
 *	that specअगरically request them.
 * @length: Total length of this काष्ठाure including embedded tables
 * @vi_scale: log2 the number of VIs available on this VF. This quantity
 *	is used by the hardware क्रम रेजिस्टर decoding.
 * @max_tx_channels: The maximum number of transmit queues the VF can use.
 * @rss_rxq_count: The number of receive queues present in the shared RSS
 *	indirection table.
 * @peer_count: Total number of peers in the complete peer list. If larger
 *	than ARRAY_SIZE(%peers), then the VF must provide sufficient
 *	additional pages each of which is filled with vfdi_endpoपूर्णांक काष्ठाures.
 * @local: The MAC address and outer VLAN tag of *this* VF
 * @peers: Table of peer addresses.  The @tci fields in these काष्ठाures
 *	are currently unused and must be ignored.  Additional peers are
 *	written पूर्णांकo any additional pages provided by the VF.
 * @समयr_quantum_ns: Timer quantum (nominal period between समयr ticks)
 *	क्रम पूर्णांकerrupt moderation समयrs, in nanoseconds. This member is only
 *	present अगर @length is sufficiently large.
 */
काष्ठा vfdi_status अणु
	u32 generation_start;
	u32 generation_end;
	u32 version;
	u32 length;
	u8 vi_scale;
	u8 max_tx_channels;
	u8 rss_rxq_count;
	u8 reserved1;
	u16 peer_count;
	u16 reserved2;
	काष्ठा vfdi_endpoपूर्णांक local;
	काष्ठा vfdi_endpoपूर्णांक peers[256];

	/* Members below here extend version 1 of this काष्ठाure */
	u32 समयr_quantum_ns;
पूर्ण;

#पूर्ण_अगर
