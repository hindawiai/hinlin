<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 * Copyright 2020 NXP
 */
#अगर_अघोषित __FSL_DPNI_H
#घोषणा __FSL_DPNI_H

#समावेश "dpkg.h"

काष्ठा fsl_mc_io;

/* Data Path Network Interface API
 * Contains initialization APIs and runसमय control APIs क्रम DPNI
 */

/** General DPNI macros */

/**
 * DPNI_MAX_TC - Maximum number of traffic classes
 */
#घोषणा DPNI_MAX_TC				8
/**
 * DPNI_MAX_DPBP - Maximum number of buffer pools per DPNI
 */
#घोषणा DPNI_MAX_DPBP				8

/**
 * DPNI_ALL_TCS - All traffic classes considered; see dpni_set_queue()
 */
#घोषणा DPNI_ALL_TCS				(u8)(-1)
/**
 * DPNI_ALL_TC_FLOWS - All flows within traffic class considered; see
 * dpni_set_queue()
 */
#घोषणा DPNI_ALL_TC_FLOWS			(u16)(-1)
/**
 * DPNI_NEW_FLOW_ID - Generate new flow ID; see dpni_set_queue()
 */
#घोषणा DPNI_NEW_FLOW_ID			(u16)(-1)

/**
 * DPNI_OPT_TX_FRM_RELEASE - Tx traffic is always released to a buffer pool on
 * transmit, there are no resources allocated to have the frames confirmed back
 * to the source after transmission.
 */
#घोषणा DPNI_OPT_TX_FRM_RELEASE			0x000001
/**
 * DPNI_OPT_NO_MAC_FILTER - Disables support क्रम MAC address filtering क्रम
 * addresses other than primary MAC address. This affects both unicast and
 * multicast. Promiscuous mode can still be enabled/disabled क्रम both unicast
 * and multicast. If promiscuous mode is disabled, only traffic matching the
 * primary MAC address will be accepted.
 */
#घोषणा DPNI_OPT_NO_MAC_FILTER			0x000002
/**
 * DPNI_OPT_HAS_POLICING - Allocate policers क्रम this DPNI. They can be used to
 * rate-limit traffic per traffic class (TC) basis.
 */
#घोषणा DPNI_OPT_HAS_POLICING			0x000004
/**
 * DPNI_OPT_SHARED_CONGESTION - Congestion can be managed in several ways,
 * allowing the buffer pool to deplete on ingress, taildrop on each queue or
 * use congestion groups क्रम sets of queues. If set, it configures a single
 * congestion groups across all TCs.  If reset, a congestion group is allocated
 * क्रम each TC. Only relevant अगर the DPNI has multiple traffic classes.
 */
#घोषणा DPNI_OPT_SHARED_CONGESTION		0x000008
/**
 * DPNI_OPT_HAS_KEY_MASKING - Enables TCAM क्रम Flow Steering and QoS look-ups.
 * If not specअगरied, all look-ups are exact match. Note that TCAM is not
 * available on LS1088 and its variants. Setting this bit on these SoCs will
 * trigger an error.
 */
#घोषणा DPNI_OPT_HAS_KEY_MASKING		0x000010
/**
 * DPNI_OPT_NO_FS - Disables the flow steering table.
 */
#घोषणा DPNI_OPT_NO_FS				0x000020
/**
 * DPNI_OPT_SHARED_FS - Flow steering table is shared between all traffic
 * classes
 */
#घोषणा DPNI_OPT_SHARED_FS			0x001000

पूर्णांक dpni_खोलो(काष्ठा fsl_mc_io	*mc_io,
	      u32		cmd_flags,
	      पूर्णांक		dpni_id,
	      u16		*token);

पूर्णांक dpni_बंद(काष्ठा fsl_mc_io	*mc_io,
	       u32		cmd_flags,
	       u16		token);

/**
 * काष्ठा dpni_pools_cfg - Structure representing buffer pools configuration
 * @num_dpbp: Number of DPBPs
 * @pools: Array of buffer pools parameters; The number of valid entries
 *	must match 'num_dpbp' value
 * @pools.dpbp_id: DPBP object ID
 * @pools.buffer_size: Buffer size
 * @pools.backup_pool: Backup pool
 */
काष्ठा dpni_pools_cfg अणु
	u8		num_dpbp;
	काष्ठा अणु
		पूर्णांक	dpbp_id;
		u16	buffer_size;
		पूर्णांक	backup_pool;
	पूर्ण pools[DPNI_MAX_DPBP];
पूर्ण;

पूर्णांक dpni_set_pools(काष्ठा fsl_mc_io		*mc_io,
		   u32				cmd_flags,
		   u16				token,
		   स्थिर काष्ठा dpni_pools_cfg	*cfg);

पूर्णांक dpni_enable(काष्ठा fsl_mc_io	*mc_io,
		u32			cmd_flags,
		u16			token);

पूर्णांक dpni_disable(काष्ठा fsl_mc_io	*mc_io,
		 u32			cmd_flags,
		 u16			token);

पूर्णांक dpni_is_enabled(काष्ठा fsl_mc_io	*mc_io,
		    u32			cmd_flags,
		    u16			token,
		    पूर्णांक			*en);

पूर्णांक dpni_reset(काष्ठा fsl_mc_io	*mc_io,
	       u32		cmd_flags,
	       u16		token);

/* DPNI IRQ Index and Events */

#घोषणा DPNI_IRQ_INDEX				0

/* DPNI_IRQ_EVENT_LINK_CHANGED - indicates a change in link state */
#घोषणा DPNI_IRQ_EVENT_LINK_CHANGED		0x00000001

/* DPNI_IRQ_EVENT_ENDPOINT_CHANGED - indicates a change in endpoपूर्णांक */
#घोषणा DPNI_IRQ_EVENT_ENDPOINT_CHANGED		0x00000002

पूर्णांक dpni_set_irq_enable(काष्ठा fsl_mc_io	*mc_io,
			u32			cmd_flags,
			u16			token,
			u8			irq_index,
			u8			en);

पूर्णांक dpni_get_irq_enable(काष्ठा fsl_mc_io	*mc_io,
			u32			cmd_flags,
			u16			token,
			u8			irq_index,
			u8			*en);

पूर्णांक dpni_set_irq_mask(काष्ठा fsl_mc_io	*mc_io,
		      u32		cmd_flags,
		      u16		token,
		      u8		irq_index,
		      u32		mask);

पूर्णांक dpni_get_irq_mask(काष्ठा fsl_mc_io	*mc_io,
		      u32		cmd_flags,
		      u16		token,
		      u8		irq_index,
		      u32		*mask);

पूर्णांक dpni_get_irq_status(काष्ठा fsl_mc_io	*mc_io,
			u32			cmd_flags,
			u16			token,
			u8			irq_index,
			u32			*status);

पूर्णांक dpni_clear_irq_status(काष्ठा fsl_mc_io	*mc_io,
			  u32			cmd_flags,
			  u16			token,
			  u8			irq_index,
			  u32			status);

/**
 * काष्ठा dpni_attr - Structure representing DPNI attributes
 * @options: Any combination of the following options:
 *		DPNI_OPT_TX_FRM_RELEASE
 *		DPNI_OPT_NO_MAC_FILTER
 *		DPNI_OPT_HAS_POLICING
 *		DPNI_OPT_SHARED_CONGESTION
 *		DPNI_OPT_HAS_KEY_MASKING
 *		DPNI_OPT_NO_FS
 * @num_queues: Number of Tx and Rx queues used क्रम traffic distribution.
 * @num_tcs: Number of traffic classes (TCs), reserved क्रम the DPNI.
 * @mac_filter_entries: Number of entries in the MAC address filtering table.
 * @vlan_filter_entries: Number of entries in the VLAN address filtering table.
 * @qos_entries: Number of entries in the QoS classअगरication table.
 * @fs_entries: Number of entries in the flow steering table.
 * @qos_key_size: Size, in bytes, of the QoS look-up key. Defining a key larger
 *		than this when adding QoS entries will result in an error.
 * @fs_key_size: Size, in bytes, of the flow steering look-up key. Defining a
 *		key larger than this when composing the hash + FS key will
 *		result in an error.
 * @wriop_version: Version of WRIOP HW block. The 3 version values are stored
 *		on 6, 5, 5 bits respectively.
 */
काष्ठा dpni_attr अणु
	u32 options;
	u8 num_queues;
	u8 num_tcs;
	u8 mac_filter_entries;
	u8 vlan_filter_entries;
	u8 qos_entries;
	u16 fs_entries;
	u8 qos_key_size;
	u8 fs_key_size;
	u16 wriop_version;
पूर्ण;

पूर्णांक dpni_get_attributes(काष्ठा fsl_mc_io	*mc_io,
			u32			cmd_flags,
			u16			token,
			काष्ठा dpni_attr	*attr);

/* DPNI errors */

/**
 * DPNI_ERROR_खातापूर्णHE - Extract out of frame header error
 */
#घोषणा DPNI_ERROR_खातापूर्णHE	0x00020000
/**
 * DPNI_ERROR_FLE - Frame length error
 */
#घोषणा DPNI_ERROR_FLE		0x00002000
/**
 * DPNI_ERROR_FPE - Frame physical error
 */
#घोषणा DPNI_ERROR_FPE		0x00001000
/**
 * DPNI_ERROR_PHE - Parsing header error
 */
#घोषणा DPNI_ERROR_PHE		0x00000020
/**
 * DPNI_ERROR_L3CE - Parser L3 checksum error
 */
#घोषणा DPNI_ERROR_L3CE		0x00000004
/**
 * DPNI_ERROR_L4CE - Parser L3 checksum error
 */
#घोषणा DPNI_ERROR_L4CE		0x00000001

/**
 * क्रमागत dpni_error_action - Defines DPNI behavior क्रम errors
 * @DPNI_ERROR_ACTION_DISCARD: Discard the frame
 * @DPNI_ERROR_ACTION_CONTINUE: Continue with the normal flow
 * @DPNI_ERROR_ACTION_SEND_TO_ERROR_QUEUE: Send the frame to the error queue
 */
क्रमागत dpni_error_action अणु
	DPNI_ERROR_ACTION_DISCARD = 0,
	DPNI_ERROR_ACTION_CONTINUE = 1,
	DPNI_ERROR_ACTION_SEND_TO_ERROR_QUEUE = 2
पूर्ण;

/**
 * काष्ठा dpni_error_cfg - Structure representing DPNI errors treaपंचांगent
 * @errors: Errors mask; use 'DPNI_ERROR__<X>
 * @error_action: The desired action क्रम the errors mask
 * @set_frame_annotation: Set to '1' to mark the errors in frame annotation
 *		status (FAS); relevant only क्रम the non-discard action
 */
काष्ठा dpni_error_cfg अणु
	u32			errors;
	क्रमागत dpni_error_action	error_action;
	पूर्णांक			set_frame_annotation;
पूर्ण;

पूर्णांक dpni_set_errors_behavior(काष्ठा fsl_mc_io		*mc_io,
			     u32			cmd_flags,
			     u16			token,
			     काष्ठा dpni_error_cfg	*cfg);

/* DPNI buffer layout modअगरication options */

/**
 * DPNI_BUF_LAYOUT_OPT_TIMESTAMP - Select to modअगरy the समय-stamp setting
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_TIMESTAMP		0x00000001
/**
 * DPNI_BUF_LAYOUT_OPT_PARSER_RESULT - Select to modअगरy the parser-result
 * setting; not applicable क्रम Tx
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_PARSER_RESULT	0x00000002
/**
 * DPNI_BUF_LAYOUT_OPT_FRAME_STATUS - Select to modअगरy the frame-status setting
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_FRAME_STATUS	0x00000004
/**
 * DPNI_BUF_LAYOUT_OPT_PRIVATE_DATA_SIZE - Select to modअगरy the निजी-data-size setting
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_PRIVATE_DATA_SIZE	0x00000008
/**
 * DPNI_BUF_LAYOUT_OPT_DATA_ALIGN - Select to modअगरy the data-alignment setting
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_DATA_ALIGN		0x00000010
/**
 * DPNI_BUF_LAYOUT_OPT_DATA_HEAD_ROOM - Select to modअगरy the data-head-room setting
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_DATA_HEAD_ROOM	0x00000020
/**
 * DPNI_BUF_LAYOUT_OPT_DATA_TAIL_ROOM - Select to modअगरy the data-tail-room setting
 */
#घोषणा DPNI_BUF_LAYOUT_OPT_DATA_TAIL_ROOM	0x00000040

/**
 * काष्ठा dpni_buffer_layout - Structure representing DPNI buffer layout
 * @options: Flags representing the suggested modअगरications to the buffer
 *		layout; Use any combination of 'DPNI_BUF_LAYOUT_OPT_<X>' flags
 * @pass_बारtamp: Pass बारtamp value
 * @pass_parser_result: Pass parser results
 * @pass_frame_status: Pass frame status
 * @निजी_data_size: Size kept क्रम निजी data (in bytes)
 * @data_align: Data alignment
 * @data_head_room: Data head room
 * @data_tail_room: Data tail room
 */
काष्ठा dpni_buffer_layout अणु
	u32	options;
	पूर्णांक	pass_बारtamp;
	पूर्णांक	pass_parser_result;
	पूर्णांक	pass_frame_status;
	u16	निजी_data_size;
	u16	data_align;
	u16	data_head_room;
	u16	data_tail_room;
पूर्ण;

/**
 * क्रमागत dpni_queue_type - Identअगरies a type of queue targeted by the command
 * @DPNI_QUEUE_RX: Rx queue
 * @DPNI_QUEUE_TX: Tx queue
 * @DPNI_QUEUE_TX_CONFIRM: Tx confirmation queue
 * @DPNI_QUEUE_RX_ERR: Rx error queue
 */
क्रमागत dpni_queue_type अणु
	DPNI_QUEUE_RX,
	DPNI_QUEUE_TX,
	DPNI_QUEUE_TX_CONFIRM,
	DPNI_QUEUE_RX_ERR,
पूर्ण;

पूर्णांक dpni_get_buffer_layout(काष्ठा fsl_mc_io		*mc_io,
			   u32				cmd_flags,
			   u16				token,
			   क्रमागत dpni_queue_type		qtype,
			   काष्ठा dpni_buffer_layout	*layout);

पूर्णांक dpni_set_buffer_layout(काष्ठा fsl_mc_io		   *mc_io,
			   u32				   cmd_flags,
			   u16				   token,
			   क्रमागत dpni_queue_type		   qtype,
			   स्थिर काष्ठा dpni_buffer_layout *layout);

/**
 * क्रमागत dpni_offload - Identअगरies a type of offload targeted by the command
 * @DPNI_OFF_RX_L3_CSUM: Rx L3 checksum validation
 * @DPNI_OFF_RX_L4_CSUM: Rx L4 checksum validation
 * @DPNI_OFF_TX_L3_CSUM: Tx L3 checksum generation
 * @DPNI_OFF_TX_L4_CSUM: Tx L4 checksum generation
 */
क्रमागत dpni_offload अणु
	DPNI_OFF_RX_L3_CSUM,
	DPNI_OFF_RX_L4_CSUM,
	DPNI_OFF_TX_L3_CSUM,
	DPNI_OFF_TX_L4_CSUM,
पूर्ण;

पूर्णांक dpni_set_offload(काष्ठा fsl_mc_io	*mc_io,
		     u32		cmd_flags,
		     u16		token,
		     क्रमागत dpni_offload	type,
		     u32		config);

पूर्णांक dpni_get_offload(काष्ठा fsl_mc_io	*mc_io,
		     u32		cmd_flags,
		     u16		token,
		     क्रमागत dpni_offload	type,
		     u32		*config);

पूर्णांक dpni_get_qdid(काष्ठा fsl_mc_io	*mc_io,
		  u32			cmd_flags,
		  u16			token,
		  क्रमागत dpni_queue_type	qtype,
		  u16			*qdid);

पूर्णांक dpni_get_tx_data_offset(काष्ठा fsl_mc_io	*mc_io,
			    u32			cmd_flags,
			    u16			token,
			    u16			*data_offset);

#घोषणा DPNI_STATISTICS_CNT		7

/**
 * जोड़ dpni_statistics - Union describing the DPNI statistics
 * @page_0: Page_0 statistics काष्ठाure
 * @page_0.ingress_all_frames: Ingress frame count
 * @page_0.ingress_all_bytes: Ingress byte count
 * @page_0.ingress_multicast_frames: Ingress multicast frame count
 * @page_0.ingress_multicast_bytes: Ingress multicast byte count
 * @page_0.ingress_broadcast_frames: Ingress broadcast frame count
 * @page_0.ingress_broadcast_bytes: Ingress broadcast byte count
 * @page_1: Page_1 statistics काष्ठाure
 * @page_1.egress_all_frames: Egress frame count
 * @page_1.egress_all_bytes: Egress byte count
 * @page_1.egress_multicast_frames: Egress multicast frame count
 * @page_1.egress_multicast_bytes: Egress multicast byte count
 * @page_1.egress_broadcast_frames: Egress broadcast frame count
 * @page_1.egress_broadcast_bytes: Egress broadcast byte count
 * @page_2: Page_2 statistics काष्ठाure
 * @page_2.ingress_filtered_frames: Ingress filtered frame count
 * @page_2.ingress_discarded_frames: Ingress discarded frame count
 * @page_2.ingress_nobuffer_discards: Ingress discarded frame count due to
 *	lack of buffers
 * @page_2.egress_discarded_frames: Egress discarded frame count
 * @page_2.egress_confirmed_frames: Egress confirmed frame count
 * @page_3: Page_3 statistics काष्ठाure
 * @page_3.egress_dequeue_bytes: Cumulative count of the number of bytes
 *	dequeued from egress FQs
 * @page_3.egress_dequeue_frames: Cumulative count of the number of frames
 *	dequeued from egress FQs
 * @page_3.egress_reject_bytes: Cumulative count of the number of bytes in
 *	egress frames whose enqueue was rejected
 * @page_3.egress_reject_frames: Cumulative count of the number of egress
 *	frames whose enqueue was rejected
 * @page_4: Page_4 statistics काष्ठाure: congestion poपूर्णांकs
 * @page_4.cgr_reject_frames: number of rejected frames due to congestion poपूर्णांक
 * @page_4.cgr_reject_bytes: number of rejected bytes due to congestion poपूर्णांक
 * @page_5: Page_5 statistics काष्ठाure: policer
 * @page_5.policer_cnt_red: NUmber of red colored frames
 * @page_5.policer_cnt_yellow: number of yellow colored frames
 * @page_5.policer_cnt_green: number of green colored frames
 * @page_5.policer_cnt_re_red: number of recolored red frames
 * @page_5.policer_cnt_re_yellow: number of recolored yellow frames
 * @page_6: Page_6 statistics काष्ठाure
 * @page_6.tx_pending_frames: total number of frames pending in egress FQs
 * @raw: raw statistics काष्ठाure, used to index counters
 */
जोड़ dpni_statistics अणु
	काष्ठा अणु
		u64 ingress_all_frames;
		u64 ingress_all_bytes;
		u64 ingress_multicast_frames;
		u64 ingress_multicast_bytes;
		u64 ingress_broadcast_frames;
		u64 ingress_broadcast_bytes;
	पूर्ण page_0;
	काष्ठा अणु
		u64 egress_all_frames;
		u64 egress_all_bytes;
		u64 egress_multicast_frames;
		u64 egress_multicast_bytes;
		u64 egress_broadcast_frames;
		u64 egress_broadcast_bytes;
	पूर्ण page_1;
	काष्ठा अणु
		u64 ingress_filtered_frames;
		u64 ingress_discarded_frames;
		u64 ingress_nobuffer_discards;
		u64 egress_discarded_frames;
		u64 egress_confirmed_frames;
	पूर्ण page_2;
	काष्ठा अणु
		u64 egress_dequeue_bytes;
		u64 egress_dequeue_frames;
		u64 egress_reject_bytes;
		u64 egress_reject_frames;
	पूर्ण page_3;
	काष्ठा अणु
		u64 cgr_reject_frames;
		u64 cgr_reject_bytes;
	पूर्ण page_4;
	काष्ठा अणु
		u64 policer_cnt_red;
		u64 policer_cnt_yellow;
		u64 policer_cnt_green;
		u64 policer_cnt_re_red;
		u64 policer_cnt_re_yellow;
	पूर्ण page_5;
	काष्ठा अणु
		u64 tx_pending_frames;
	पूर्ण page_6;
	काष्ठा अणु
		u64 counter[DPNI_STATISTICS_CNT];
	पूर्ण raw;
पूर्ण;

पूर्णांक dpni_get_statistics(काष्ठा fsl_mc_io	*mc_io,
			u32			cmd_flags,
			u16			token,
			u8			page,
			जोड़ dpni_statistics	*stat);

#घोषणा DPNI_LINK_OPT_AUTONEG		0x0000000000000001ULL
#घोषणा DPNI_LINK_OPT_HALF_DUPLEX	0x0000000000000002ULL
#घोषणा DPNI_LINK_OPT_PAUSE		0x0000000000000004ULL
#घोषणा DPNI_LINK_OPT_ASYM_PAUSE	0x0000000000000008ULL
#घोषणा DPNI_LINK_OPT_PFC_PAUSE		0x0000000000000010ULL

/**
 * काष्ठा dpni_link_cfg - Structure representing DPNI link configuration
 * @rate: Rate
 * @options: Mask of available options; use 'DPNI_LINK_OPT_<X>' values
 */
काष्ठा dpni_link_cfg अणु
	u32 rate;
	u64 options;
पूर्ण;

पूर्णांक dpni_set_link_cfg(काष्ठा fsl_mc_io			*mc_io,
		      u32				cmd_flags,
		      u16				token,
		      स्थिर काष्ठा dpni_link_cfg	*cfg);

पूर्णांक dpni_get_link_cfg(काष्ठा fsl_mc_io			*mc_io,
		      u32				cmd_flags,
		      u16				token,
		      काष्ठा dpni_link_cfg		*cfg);

/**
 * काष्ठा dpni_link_state - Structure representing DPNI link state
 * @rate: Rate
 * @options: Mask of available options; use 'DPNI_LINK_OPT_<X>' values
 * @up: Link state; '0' for down, '1' क्रम up
 */
काष्ठा dpni_link_state अणु
	u32	rate;
	u64	options;
	पूर्णांक	up;
पूर्ण;

पूर्णांक dpni_get_link_state(काष्ठा fsl_mc_io	*mc_io,
			u32			cmd_flags,
			u16			token,
			काष्ठा dpni_link_state	*state);

पूर्णांक dpni_set_max_frame_length(काष्ठा fsl_mc_io	*mc_io,
			      u32		cmd_flags,
			      u16		token,
			      u16		max_frame_length);

पूर्णांक dpni_get_max_frame_length(काष्ठा fsl_mc_io	*mc_io,
			      u32		cmd_flags,
			      u16		token,
			      u16		*max_frame_length);

पूर्णांक dpni_set_multicast_promisc(काष्ठा fsl_mc_io *mc_io,
			       u32		cmd_flags,
			       u16		token,
			       पूर्णांक		en);

पूर्णांक dpni_get_multicast_promisc(काष्ठा fsl_mc_io *mc_io,
			       u32		cmd_flags,
			       u16		token,
			       पूर्णांक		*en);

पूर्णांक dpni_set_unicast_promisc(काष्ठा fsl_mc_io	*mc_io,
			     u32		cmd_flags,
			     u16		token,
			     पूर्णांक		en);

पूर्णांक dpni_get_unicast_promisc(काष्ठा fsl_mc_io	*mc_io,
			     u32		cmd_flags,
			     u16		token,
			     पूर्णांक		*en);

पूर्णांक dpni_set_primary_mac_addr(काष्ठा fsl_mc_io *mc_io,
			      u32		cmd_flags,
			      u16		token,
			      स्थिर u8		mac_addr[6]);

पूर्णांक dpni_get_primary_mac_addr(काष्ठा fsl_mc_io	*mc_io,
			      u32		cmd_flags,
			      u16		token,
			      u8		mac_addr[6]);

पूर्णांक dpni_get_port_mac_addr(काष्ठा fsl_mc_io	*mc_io,
			   u32			cm_flags,
			   u16			token,
			   u8			mac_addr[6]);

पूर्णांक dpni_add_mac_addr(काष्ठा fsl_mc_io	*mc_io,
		      u32		cmd_flags,
		      u16		token,
		      स्थिर u8		mac_addr[6]);

पूर्णांक dpni_हटाओ_mac_addr(काष्ठा fsl_mc_io	*mc_io,
			 u32			cmd_flags,
			 u16			token,
			 स्थिर u8		mac_addr[6]);

पूर्णांक dpni_clear_mac_filters(काष्ठा fsl_mc_io	*mc_io,
			   u32			cmd_flags,
			   u16			token,
			   पूर्णांक			unicast,
			   पूर्णांक			multicast);

/**
 * क्रमागत dpni_dist_mode - DPNI distribution mode
 * @DPNI_DIST_MODE_NONE: No distribution
 * @DPNI_DIST_MODE_HASH: Use hash distribution; only relevant अगर
 *		the 'DPNI_OPT_DIST_HASH' option was set at DPNI creation
 * @DPNI_DIST_MODE_FS:  Use explicit flow steering; only relevant अगर
 *	 the 'DPNI_OPT_DIST_FS' option was set at DPNI creation
 */
क्रमागत dpni_dist_mode अणु
	DPNI_DIST_MODE_NONE = 0,
	DPNI_DIST_MODE_HASH = 1,
	DPNI_DIST_MODE_FS = 2
पूर्ण;

/**
 * क्रमागत dpni_fs_miss_action -   DPNI Flow Steering miss action
 * @DPNI_FS_MISS_DROP: In हाल of no-match, drop the frame
 * @DPNI_FS_MISS_EXPLICIT_FLOWID: In हाल of no-match, use explicit flow-id
 * @DPNI_FS_MISS_HASH: In हाल of no-match, distribute using hash
 */
क्रमागत dpni_fs_miss_action अणु
	DPNI_FS_MISS_DROP = 0,
	DPNI_FS_MISS_EXPLICIT_FLOWID = 1,
	DPNI_FS_MISS_HASH = 2
पूर्ण;

/**
 * काष्ठा dpni_fs_tbl_cfg - Flow Steering table configuration
 * @miss_action: Miss action selection
 * @शेष_flow_id: Used when 'miss_action = DPNI_FS_MISS_EXPLICIT_FLOWID'
 */
काष्ठा dpni_fs_tbl_cfg अणु
	क्रमागत dpni_fs_miss_action	miss_action;
	u16				शेष_flow_id;
पूर्ण;

पूर्णांक dpni_prepare_key_cfg(स्थिर काष्ठा dpkg_profile_cfg *cfg,
			 u8 *key_cfg_buf);

/**
 * काष्ठा dpni_rx_tc_dist_cfg - Rx traffic class distribution configuration
 * @dist_size: Set the distribution size;
 *	supported values: 1,2,3,4,6,7,8,12,14,16,24,28,32,48,56,64,96,
 *	112,128,192,224,256,384,448,512,768,896,1024
 * @dist_mode: Distribution mode
 * @key_cfg_iova: I/O भव address of 256 bytes DMA-able memory filled with
 *		the extractions to be used क्रम the distribution key by calling
 *		dpni_prepare_key_cfg() relevant only when
 *		'dist_mode != DPNI_DIST_MODE_NONE', otherwise it can be '0'
 * @fs_cfg: Flow Steering table configuration; only relevant अगर
 *		'dist_mode = DPNI_DIST_MODE_FS'
 */
काष्ठा dpni_rx_tc_dist_cfg अणु
	u16			dist_size;
	क्रमागत dpni_dist_mode	dist_mode;
	u64			key_cfg_iova;
	काष्ठा dpni_fs_tbl_cfg	fs_cfg;
पूर्ण;

पूर्णांक dpni_set_rx_tc_dist(काष्ठा fsl_mc_io			*mc_io,
			u32					cmd_flags,
			u16					token,
			u8					tc_id,
			स्थिर काष्ठा dpni_rx_tc_dist_cfg	*cfg);

/**
 * DPNI_FS_MISS_DROP - When used क्रम fs_miss_flow_id in function
 * dpni_set_rx_dist, will संकेत to dpni to drop all unclassअगरied frames
 */
#घोषणा DPNI_FS_MISS_DROP		((uपूर्णांक16_t)-1)

/**
 * काष्ठा dpni_rx_dist_cfg - Rx distribution configuration
 * @dist_size:	distribution size
 * @key_cfg_iova: I/O भव address of 256 bytes DMA-able memory filled with
 *		the extractions to be used क्रम the distribution key by calling
 *		dpni_prepare_key_cfg(); relevant only when enable!=0 otherwise
 *		it can be '0'
 * @enable: enable/disable the distribution.
 * @tc: TC id क्रम which distribution is set
 * @fs_miss_flow_id: when packet misses all rules from flow steering table and
 *		hash is disabled it will be put पूर्णांकo this queue id; use
 *		DPNI_FS_MISS_DROP to drop frames. The value of this field is
 *		used only when flow steering distribution is enabled and hash
 *		distribution is disabled
 */
काष्ठा dpni_rx_dist_cfg अणु
	u16 dist_size;
	u64 key_cfg_iova;
	u8 enable;
	u8 tc;
	u16 fs_miss_flow_id;
पूर्ण;

पूर्णांक dpni_set_rx_fs_dist(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			स्थिर काष्ठा dpni_rx_dist_cfg *cfg);

पूर्णांक dpni_set_rx_hash_dist(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  u16 token,
			  स्थिर काष्ठा dpni_rx_dist_cfg *cfg);

/**
 * काष्ठा dpni_qos_tbl_cfg - Structure representing QOS table configuration
 * @key_cfg_iova: I/O भव address of 256 bytes DMA-able memory filled with
 *		key extractions to be used as the QoS criteria by calling
 *		dpkg_prepare_key_cfg()
 * @discard_on_miss: Set to '1' to discard frames in हाल of no match (miss);
 *		'0' to use the 'default_tc' in such हालs
 * @शेष_tc: Used in हाल of no-match and 'discard_on_miss'= 0
 */
काष्ठा dpni_qos_tbl_cfg अणु
	u64 key_cfg_iova;
	पूर्णांक discard_on_miss;
	u8 शेष_tc;
पूर्ण;

पूर्णांक dpni_set_qos_table(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       स्थिर काष्ठा dpni_qos_tbl_cfg *cfg);

/**
 * क्रमागत dpni_dest - DPNI destination types
 * @DPNI_DEST_NONE: Unasचिन्हित destination; The queue is set in parked mode and
 *		करोes not generate FQDAN notअगरications; user is expected to
 *		dequeue from the queue based on polling or other user-defined
 *		method
 * @DPNI_DEST_DPIO: The queue is set in schedule mode and generates FQDAN
 *		notअगरications to the specअगरied DPIO; user is expected to dequeue
 *		from the queue only after notअगरication is received
 * @DPNI_DEST_DPCON: The queue is set in schedule mode and करोes not generate
 *		FQDAN notअगरications, but is connected to the specअगरied DPCON
 *		object; user is expected to dequeue from the DPCON channel
 */
क्रमागत dpni_dest अणु
	DPNI_DEST_NONE = 0,
	DPNI_DEST_DPIO = 1,
	DPNI_DEST_DPCON = 2
पूर्ण;

/**
 * काष्ठा dpni_queue - Queue काष्ठाure
 * @destination: - Destination काष्ठाure
 * @destination.id: ID of the destination, only relevant अगर DEST_TYPE is > 0.
 *	Identअगरies either a DPIO or a DPCON object.
 *	Not relevant क्रम Tx queues.
 * @destination.type:	May be one of the following:
 *	0 - No destination, queue can be manually
 *		queried, but will not push traffic or
 *		notअगरications to a DPIO;
 *	1 - The destination is a DPIO. When traffic
 *		becomes available in the queue a FQDAN
 *		(FQ data available notअगरication) will be
 *		generated to selected DPIO;
 *	2 - The destination is a DPCON. The queue is
 *		associated with a DPCON object क्रम the
 *		purpose of scheduling between multiple
 *		queues. The DPCON may be independently
 *		configured to generate notअगरications.
 *		Not relevant क्रम Tx queues.
 * @destination.hold_active: Hold active, मुख्यtains a queue scheduled क्रम दीर्घer
 *	in a DPIO during dequeue to reduce spपढ़ो of traffic.
 *	Only relevant अगर queues are
 *	not affined to a single DPIO.
 * @user_context: User data, presented to the user aदीर्घ with any frames
 *	from this queue. Not relevant क्रम Tx queues.
 * @flc: FD FLow Context काष्ठाure
 * @flc.value: Default FLC value क्रम traffic dequeued from
 *      this queue.  Please check description of FD
 *      काष्ठाure क्रम more inक्रमmation.
 *      Note that FLC values set using dpni_add_fs_entry,
 *      अगर any, take precedence over values per queue.
 * @flc.stash_control: Boolean, indicates whether the 6 lowest
 *      - signअगरicant bits are used क्रम stash control.
 *      signअगरicant bits are used क्रम stash control.  If set, the 6
 *      least signअगरicant bits in value are पूर्णांकerpreted as follows:
 *      - bits 0-1: indicates the number of 64 byte units of context
 *      that are stashed.  FLC value is पूर्णांकerpreted as a memory address
 *      in this हाल, excluding the 6 LS bits.
 *      - bits 2-3: indicates the number of 64 byte units of frame
 *      annotation to be stashed.  Annotation is placed at FD[ADDR].
 *      - bits 4-5: indicates the number of 64 byte units of frame
 *      data to be stashed.  Frame data is placed at FD[ADDR] +
 *      FD[OFFSET].
 *      For more details check the Frame Descriptor section in the
 *      hardware करोcumentation.
 */
काष्ठा dpni_queue अणु
	काष्ठा अणु
		u16 id;
		क्रमागत dpni_dest type;
		अक्षर hold_active;
		u8 priority;
	पूर्ण destination;
	u64 user_context;
	काष्ठा अणु
		u64 value;
		अक्षर stash_control;
	पूर्ण flc;
पूर्ण;

/**
 * काष्ठा dpni_queue_id - Queue identअगरication, used क्रम enqueue commands
 *			or queue control
 * @fqid: FQID used क्रम enqueueing to and/or configuration of this specअगरic FQ
 * @qdbin: Queueing bin, used to enqueue using QDID, DQBIN, QPRI. Only relevant
 *		क्रम Tx queues.
 */
काष्ठा dpni_queue_id अणु
	u32 fqid;
	u16 qdbin;
पूर्ण;

/* Set User Context */
#घोषणा DPNI_QUEUE_OPT_USER_CTX		0x00000001
#घोषणा DPNI_QUEUE_OPT_DEST		0x00000002
#घोषणा DPNI_QUEUE_OPT_FLC		0x00000004
#घोषणा DPNI_QUEUE_OPT_HOLD_ACTIVE	0x00000008

पूर्णांक dpni_set_queue(काष्ठा fsl_mc_io	*mc_io,
		   u32			cmd_flags,
		   u16			token,
		   क्रमागत dpni_queue_type	qtype,
		   u8			tc,
		   u8			index,
		   u8			options,
		   स्थिर काष्ठा dpni_queue *queue);

पूर्णांक dpni_get_queue(काष्ठा fsl_mc_io	*mc_io,
		   u32			cmd_flags,
		   u16			token,
		   क्रमागत dpni_queue_type	qtype,
		   u8			tc,
		   u8			index,
		   काष्ठा dpni_queue	*queue,
		   काष्ठा dpni_queue_id	*qid);

/**
 * क्रमागत dpni_congestion_unit - DPNI congestion units
 * @DPNI_CONGESTION_UNIT_BYTES: bytes units
 * @DPNI_CONGESTION_UNIT_FRAMES: frames units
 */
क्रमागत dpni_congestion_unit अणु
	DPNI_CONGESTION_UNIT_BYTES = 0,
	DPNI_CONGESTION_UNIT_FRAMES
पूर्ण;

/**
 * क्रमागत dpni_congestion_poपूर्णांक - Structure representing congestion poपूर्णांक
 * @DPNI_CP_QUEUE: Set taildrop per queue, identअगरied by QUEUE_TYPE, TC and
 *		QUEUE_INDEX
 * @DPNI_CP_GROUP: Set taildrop per queue group. Depending on options used to
 *		define the DPNI this can be either per TC (शेष) or per
 *		पूर्णांकerface (DPNI_OPT_SHARED_CONGESTION set at DPNI create).
 *		QUEUE_INDEX is ignored अगर this type is used.
 */
क्रमागत dpni_congestion_poपूर्णांक अणु
	DPNI_CP_QUEUE,
	DPNI_CP_GROUP,
पूर्ण;

/**
 * काष्ठा dpni_dest_cfg - Structure representing DPNI destination parameters
 * @dest_type:	Destination type
 * @dest_id:	Either DPIO ID or DPCON ID, depending on the destination type
 * @priority:	Priority selection within the DPIO or DPCON channel; valid
 *		values are 0-1 or 0-7, depending on the number of priorities
 *		in that channel; not relevant क्रम 'DPNI_DEST_NONE' option
 */
काष्ठा dpni_dest_cfg अणु
	क्रमागत dpni_dest dest_type;
	पूर्णांक dest_id;
	u8 priority;
पूर्ण;

/* DPNI congestion options */

/**
 * DPNI_CONG_OPT_FLOW_CONTROL - This congestion will trigger flow control or
 * priority flow control.  This will have effect only अगर flow control is
 * enabled with dpni_set_link_cfg().
 */
#घोषणा DPNI_CONG_OPT_FLOW_CONTROL		0x00000040

/**
 * काष्ठा dpni_congestion_notअगरication_cfg - congestion notअगरication
 *					configuration
 * @units: Units type
 * @threshold_entry: Above this threshold we enter a congestion state.
 *		set it to '0' to disable it
 * @threshold_निकास: Below this threshold we निकास the congestion state.
 * @message_ctx: The context that will be part of the CSCN message
 * @message_iova: I/O भव address (must be in DMA-able memory),
 *		must be 16B aligned; valid only अगर 'DPNI_CONG_OPT_WRITE_MEM_<X>'
 *		is contained in 'options'
 * @dest_cfg: CSCN can be send to either DPIO or DPCON WQ channel
 * @notअगरication_mode: Mask of available options; use 'DPNI_CONG_OPT_<X>' values
 */

काष्ठा dpni_congestion_notअगरication_cfg अणु
	क्रमागत dpni_congestion_unit units;
	u32 threshold_entry;
	u32 threshold_निकास;
	u64 message_ctx;
	u64 message_iova;
	काष्ठा dpni_dest_cfg dest_cfg;
	u16 notअगरication_mode;
पूर्ण;

पूर्णांक dpni_set_congestion_notअगरication(
			काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			क्रमागत dpni_queue_type qtype,
			u8 tc_id,
			स्थिर काष्ठा dpni_congestion_notअगरication_cfg *cfg);

/**
 * काष्ठा dpni_taildrop - Structure representing the taildrop
 * @enable:	Indicates whether the taildrop is active or not.
 * @units:	Indicates the unit of THRESHOLD. Queue taildrop only supports
 *		byte units, this field is ignored and assumed = 0 अगर
 *		CONGESTION_POINT is 0.
 * @threshold:	Threshold value, in units identअगरied by UNITS field. Value 0
 *		cannot be used as a valid taildrop threshold, THRESHOLD must
 *		be > 0 अगर the taildrop is enabled.
 */
काष्ठा dpni_taildrop अणु
	अक्षर enable;
	क्रमागत dpni_congestion_unit units;
	u32 threshold;
पूर्ण;

पूर्णांक dpni_set_taildrop(काष्ठा fsl_mc_io *mc_io,
		      u32 cmd_flags,
		      u16 token,
		      क्रमागत dpni_congestion_poपूर्णांक cg_poपूर्णांक,
		      क्रमागत dpni_queue_type q_type,
		      u8 tc,
		      u8 q_index,
		      काष्ठा dpni_taildrop *taildrop);

पूर्णांक dpni_get_taildrop(काष्ठा fsl_mc_io *mc_io,
		      u32 cmd_flags,
		      u16 token,
		      क्रमागत dpni_congestion_poपूर्णांक cg_poपूर्णांक,
		      क्रमागत dpni_queue_type q_type,
		      u8 tc,
		      u8 q_index,
		      काष्ठा dpni_taildrop *taildrop);

/**
 * काष्ठा dpni_rule_cfg - Rule configuration क्रम table lookup
 * @key_iova: I/O भव address of the key (must be in DMA-able memory)
 * @mask_iova: I/O भव address of the mask (must be in DMA-able memory)
 * @key_size: key and mask size (in bytes)
 */
काष्ठा dpni_rule_cfg अणु
	u64	key_iova;
	u64	mask_iova;
	u8	key_size;
पूर्ण;

/**
 * DPNI_FS_OPT_DISCARD - Discard matching traffic. If set, this takes
 * precedence over any other configuration and matching traffic is always
 * discarded.
 */
 #घोषणा DPNI_FS_OPT_DISCARD            0x1

/**
 * DPNI_FS_OPT_SET_FLC - Set FLC value. If set, flc member of काष्ठा
 * dpni_fs_action_cfg is used to override the FLC value set per queue.
 * For more details check the Frame Descriptor section in the hardware
 * करोcumentation.
 */
#घोषणा DPNI_FS_OPT_SET_FLC            0x2

/**
 * DPNI_FS_OPT_SET_STASH_CONTROL - Indicates whether the 6 lowest signअगरicant
 * bits of FLC are used क्रम stash control. If set, the 6 least signअगरicant bits
 * in value are पूर्णांकerpreted as follows:
 *     - bits 0-1: indicates the number of 64 byte units of context that are
 *     stashed. FLC value is पूर्णांकerpreted as a memory address in this हाल,
 *     excluding the 6 LS bits.
 *     - bits 2-3: indicates the number of 64 byte units of frame annotation
 *     to be stashed. Annotation is placed at FD[ADDR].
 *     - bits 4-5: indicates the number of 64 byte units of frame data to be
 *     stashed. Frame data is placed at FD[ADDR] + FD[OFFSET].
 * This flag is ignored अगर DPNI_FS_OPT_SET_FLC is not specअगरied.
 */
#घोषणा DPNI_FS_OPT_SET_STASH_CONTROL  0x4

/**
 * काष्ठा dpni_fs_action_cfg - Action configuration क्रम table look-up
 * @flc:	FLC value क्रम traffic matching this rule. Please check the
 *		Frame Descriptor section in the hardware करोcumentation क्रम
 *		more inक्रमmation.
 * @flow_id:	Identअगरies the Rx queue used क्रम matching traffic. Supported
 *		values are in range 0 to num_queue-1.
 * @options:	Any combination of DPNI_FS_OPT_ values.
 */
काष्ठा dpni_fs_action_cfg अणु
	u64 flc;
	u16 flow_id;
	u16 options;
पूर्ण;

पूर्णांक dpni_add_fs_entry(काष्ठा fsl_mc_io *mc_io,
		      u32 cmd_flags,
		      u16 token,
		      u8 tc_id,
		      u16 index,
		      स्थिर काष्ठा dpni_rule_cfg *cfg,
		      स्थिर काष्ठा dpni_fs_action_cfg *action);

पूर्णांक dpni_हटाओ_fs_entry(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 tc_id,
			 स्थिर काष्ठा dpni_rule_cfg *cfg);

पूर्णांक dpni_add_qos_entry(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       स्थिर काष्ठा dpni_rule_cfg *cfg,
		       u8 tc_id,
		       u16 index);

पूर्णांक dpni_हटाओ_qos_entry(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  u16 token,
			  स्थिर काष्ठा dpni_rule_cfg *cfg);

पूर्णांक dpni_clear_qos_table(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token);

पूर्णांक dpni_get_api_version(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 *major_ver,
			 u16 *minor_ver);
/**
 * काष्ठा dpni_tx_shaping_cfg - Structure representing DPNI tx shaping configuration
 * @rate_limit:		Rate in Mbps
 * @max_burst_size:	Burst size in bytes (up to 64KB)
 */
काष्ठा dpni_tx_shaping_cfg अणु
	u32 rate_limit;
	u16 max_burst_size;
पूर्ण;

पूर्णांक dpni_set_tx_shaping(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			स्थिर काष्ठा dpni_tx_shaping_cfg *tx_cr_shaper,
			स्थिर काष्ठा dpni_tx_shaping_cfg *tx_er_shaper,
			पूर्णांक coupled);

/**
 * काष्ठा dpni_single_step_cfg - configure single step PTP (IEEE 1588)
 * @en:		enable single step PTP. When enabled the PTPv1 functionality
 *		will not work. If the field is zero, offset and ch_update
 *		parameters will be ignored
 * @offset:	start offset from the beginning of the frame where
 *		बारtamp field is found. The offset must respect all MAC
 *		headers, VLAN tags and other protocol headers
 * @ch_update:	when set UDP checksum will be updated inside packet
 * @peer_delay:	For peer-to-peer transparent घड़ीs add this value to the
 *		correction field in addition to the transient समय update.
 *		The value expresses nanoseconds.
 */
काष्ठा dpni_single_step_cfg अणु
	u8	en;
	u8	ch_update;
	u16	offset;
	u32	peer_delay;
पूर्ण;

पूर्णांक dpni_set_single_step_cfg(काष्ठा fsl_mc_io *mc_io,
			     u32 cmd_flags,
			     u16 token,
			     काष्ठा dpni_single_step_cfg *ptp_cfg);

पूर्णांक dpni_get_single_step_cfg(काष्ठा fsl_mc_io *mc_io,
			     u32 cmd_flags,
			     u16 token,
			     काष्ठा dpni_single_step_cfg *ptp_cfg);

पूर्णांक dpni_enable_vlan_filter(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			    u32 en);

पूर्णांक dpni_add_vlan_id(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		     u16 vlan_id, u8 flags, u8 tc_id, u8 flow_id);

पूर्णांक dpni_हटाओ_vlan_id(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u16 vlan_id);

#पूर्ण_अगर /* __FSL_DPNI_H */
