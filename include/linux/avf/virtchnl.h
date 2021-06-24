<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
 *
 * Intel Ethernet Controller XL710 Family Linux Virtual Function Driver
 * Copyright(c) 2013 - 2014 Intel Corporation.
 *
 * Contact Inक्रमmation:
 * e1000-devel Mailing List <e1000-devel@lists.sourceक्रमge.net>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 ******************************************************************************/

#अगर_अघोषित _VIRTCHNL_H_
#घोषणा _VIRTCHNL_H_

/* Description:
 * This header file describes the VF-PF communication protocol used
 * by the drivers क्रम all devices starting from our 40G product line
 *
 * Admin queue buffer usage:
 * desc->opcode is always aqc_opc_send_msg_to_pf
 * flags, retval, datalen, and data addr are all used normally.
 * The Firmware copies the cookie fields when sending messages between the
 * PF and VF, but uses all other fields पूर्णांकernally. Due to this limitation,
 * we must send all messages as "indirect", i.e. using an बाह्यal buffer.
 *
 * All the VSI indexes are relative to the VF. Each VF can have maximum of
 * three VSIs. All the queue indexes are relative to the VSI.  Each VF can
 * have a maximum of sixteen queues क्रम all of its VSIs.
 *
 * The PF is required to वापस a status code in v_retval क्रम all messages
 * except RESET_VF, which करोes not require any response. The वापस value
 * is of status_code type, defined in the shared type.h.
 *
 * In general, VF driver initialization should roughly follow the order of
 * these opcodes. The VF driver must first validate the API version of the
 * PF driver, then request a reset, then get resources, then configure
 * queues and पूर्णांकerrupts. After these operations are complete, the VF
 * driver may start its queues, optionally add MAC and VLAN filters, and
 * process traffic.
 */

/* START GENERIC DEFINES
 * Need to ensure the following क्रमागतs and defines hold the same meaning and
 * value in current and future projects
 */

/* Error Codes */
क्रमागत virtchnl_status_code अणु
	VIRTCHNL_STATUS_SUCCESS				= 0,
	VIRTCHNL_STATUS_ERR_PARAM			= -5,
	VIRTCHNL_STATUS_ERR_NO_MEMORY			= -18,
	VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH		= -38,
	VIRTCHNL_STATUS_ERR_CQP_COMPL_ERROR		= -39,
	VIRTCHNL_STATUS_ERR_INVALID_VF_ID		= -40,
	VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR		= -53,
	VIRTCHNL_STATUS_ERR_NOT_SUPPORTED		= -64,
पूर्ण;

/* Backward compatibility */
#घोषणा VIRTCHNL_ERR_PARAM VIRTCHNL_STATUS_ERR_PARAM
#घोषणा VIRTCHNL_STATUS_NOT_SUPPORTED VIRTCHNL_STATUS_ERR_NOT_SUPPORTED

#घोषणा VIRTCHNL_LINK_SPEED_2_5GB_SHIFT		0x0
#घोषणा VIRTCHNL_LINK_SPEED_100MB_SHIFT		0x1
#घोषणा VIRTCHNL_LINK_SPEED_1000MB_SHIFT	0x2
#घोषणा VIRTCHNL_LINK_SPEED_10GB_SHIFT		0x3
#घोषणा VIRTCHNL_LINK_SPEED_40GB_SHIFT		0x4
#घोषणा VIRTCHNL_LINK_SPEED_20GB_SHIFT		0x5
#घोषणा VIRTCHNL_LINK_SPEED_25GB_SHIFT		0x6
#घोषणा VIRTCHNL_LINK_SPEED_5GB_SHIFT		0x7

क्रमागत virtchnl_link_speed अणु
	VIRTCHNL_LINK_SPEED_UNKNOWN	= 0,
	VIRTCHNL_LINK_SPEED_100MB	= BIT(VIRTCHNL_LINK_SPEED_100MB_SHIFT),
	VIRTCHNL_LINK_SPEED_1GB		= BIT(VIRTCHNL_LINK_SPEED_1000MB_SHIFT),
	VIRTCHNL_LINK_SPEED_10GB	= BIT(VIRTCHNL_LINK_SPEED_10GB_SHIFT),
	VIRTCHNL_LINK_SPEED_40GB	= BIT(VIRTCHNL_LINK_SPEED_40GB_SHIFT),
	VIRTCHNL_LINK_SPEED_20GB	= BIT(VIRTCHNL_LINK_SPEED_20GB_SHIFT),
	VIRTCHNL_LINK_SPEED_25GB	= BIT(VIRTCHNL_LINK_SPEED_25GB_SHIFT),
	VIRTCHNL_LINK_SPEED_2_5GB	= BIT(VIRTCHNL_LINK_SPEED_2_5GB_SHIFT),
	VIRTCHNL_LINK_SPEED_5GB		= BIT(VIRTCHNL_LINK_SPEED_5GB_SHIFT),
पूर्ण;

/* क्रम hsplit_0 field of Rx HMC context */
/* deprecated with AVF 1.0 */
क्रमागत virtchnl_rx_hsplit अणु
	VIRTCHNL_RX_HSPLIT_NO_SPLIT      = 0,
	VIRTCHNL_RX_HSPLIT_SPLIT_L2      = 1,
	VIRTCHNL_RX_HSPLIT_SPLIT_IP      = 2,
	VIRTCHNL_RX_HSPLIT_SPLIT_TCP_UDP = 4,
	VIRTCHNL_RX_HSPLIT_SPLIT_SCTP    = 8,
पूर्ण;

/* END GENERIC DEFINES */

/* Opcodes क्रम VF-PF communication. These are placed in the v_opcode field
 * of the virtchnl_msg काष्ठाure.
 */
क्रमागत virtchnl_ops अणु
/* The PF sends status change events to VFs using
 * the VIRTCHNL_OP_EVENT opcode.
 * VFs send requests to the PF using the other ops.
 * Use of "advanced opcode" features must be negotiated as part of capabilities
 * exchange and are not considered part of base mode feature set.
 */
	VIRTCHNL_OP_UNKNOWN = 0,
	VIRTCHNL_OP_VERSION = 1, /* must ALWAYS be 1 */
	VIRTCHNL_OP_RESET_VF = 2,
	VIRTCHNL_OP_GET_VF_RESOURCES = 3,
	VIRTCHNL_OP_CONFIG_TX_QUEUE = 4,
	VIRTCHNL_OP_CONFIG_RX_QUEUE = 5,
	VIRTCHNL_OP_CONFIG_VSI_QUEUES = 6,
	VIRTCHNL_OP_CONFIG_IRQ_MAP = 7,
	VIRTCHNL_OP_ENABLE_QUEUES = 8,
	VIRTCHNL_OP_DISABLE_QUEUES = 9,
	VIRTCHNL_OP_ADD_ETH_ADDR = 10,
	VIRTCHNL_OP_DEL_ETH_ADDR = 11,
	VIRTCHNL_OP_ADD_VLAN = 12,
	VIRTCHNL_OP_DEL_VLAN = 13,
	VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE = 14,
	VIRTCHNL_OP_GET_STATS = 15,
	VIRTCHNL_OP_RSVD = 16,
	VIRTCHNL_OP_EVENT = 17, /* must ALWAYS be 17 */
	VIRTCHNL_OP_IWARP = 20, /* advanced opcode */
	VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP = 21, /* advanced opcode */
	VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP = 22, /* advanced opcode */
	VIRTCHNL_OP_CONFIG_RSS_KEY = 23,
	VIRTCHNL_OP_CONFIG_RSS_LUT = 24,
	VIRTCHNL_OP_GET_RSS_HENA_CAPS = 25,
	VIRTCHNL_OP_SET_RSS_HENA = 26,
	VIRTCHNL_OP_ENABLE_VLAN_STRIPPING = 27,
	VIRTCHNL_OP_DISABLE_VLAN_STRIPPING = 28,
	VIRTCHNL_OP_REQUEST_QUEUES = 29,
	VIRTCHNL_OP_ENABLE_CHANNELS = 30,
	VIRTCHNL_OP_DISABLE_CHANNELS = 31,
	VIRTCHNL_OP_ADD_CLOUD_FILTER = 32,
	VIRTCHNL_OP_DEL_CLOUD_FILTER = 33,
	/* opcode 34 - 44 are reserved */
	VIRTCHNL_OP_ADD_RSS_CFG = 45,
	VIRTCHNL_OP_DEL_RSS_CFG = 46,
	VIRTCHNL_OP_ADD_Fसूची_FILTER = 47,
	VIRTCHNL_OP_DEL_Fसूची_FILTER = 48,
	VIRTCHNL_OP_MAX,
पूर्ण;

/* These macros are used to generate compilation errors अगर a काष्ठाure/जोड़
 * is not exactly the correct length. It gives a भागide by zero error अगर the
 * काष्ठाure/जोड़ is not of the correct size, otherwise it creates an क्रमागत
 * that is never used.
 */
#घोषणा VIRTCHNL_CHECK_STRUCT_LEN(n, X) क्रमागत virtchnl_अटल_निश्चित_क्रमागत_##X \
	अणु virtchnl_अटल_निश्चित_##X = (n)/((माप(काष्ठा X) == (n)) ? 1 : 0) पूर्ण
#घोषणा VIRTCHNL_CHECK_UNION_LEN(n, X) क्रमागत virtchnl_अटल_asset_क्रमागत_##X \
	अणु virtchnl_अटल_निश्चित_##X = (n)/((माप(जोड़ X) == (n)) ? 1 : 0) पूर्ण

/* Virtual channel message descriptor. This overlays the admin queue
 * descriptor. All other data is passed in बाह्यal buffers.
 */

काष्ठा virtchnl_msg अणु
	u8 pad[8];			 /* AQ flags/opcode/len/retval fields */
	क्रमागत virtchnl_ops v_opcode; /* aव्योम confusion with desc->opcode */
	क्रमागत virtchnl_status_code v_retval;  /* ditto क्रम desc->retval */
	u32 vfid;			 /* used by PF when sending to VF */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(20, virtchnl_msg);

/* Message descriptions and data काष्ठाures. */

/* VIRTCHNL_OP_VERSION
 * VF posts its version number to the PF. PF responds with its version number
 * in the same क्रमmat, aदीर्घ with a वापस code.
 * Reply from PF has its major/minor versions also in param0 and param1.
 * If there is a major version mismatch, then the VF cannot operate.
 * If there is a minor version mismatch, then the VF can operate but should
 * add a warning to the प्रणाली log.
 *
 * This क्रमागत element MUST always be specअगरied as == 1, regardless of other
 * changes in the API. The PF must always respond to this message without
 * error regardless of version mismatch.
 */
#घोषणा VIRTCHNL_VERSION_MAJOR		1
#घोषणा VIRTCHNL_VERSION_MINOR		1
#घोषणा VIRTCHNL_VERSION_MINOR_NO_VF_CAPS	0

काष्ठा virtchnl_version_info अणु
	u32 major;
	u32 minor;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(8, virtchnl_version_info);

#घोषणा VF_IS_V10(_v) (((_v)->major == 1) && ((_v)->minor == 0))
#घोषणा VF_IS_V11(_ver) (((_ver)->major == 1) && ((_ver)->minor == 1))

/* VIRTCHNL_OP_RESET_VF
 * VF sends this request to PF with no parameters
 * PF करोes NOT respond! VF driver must delay then poll VFGEN_RSTAT रेजिस्टर
 * until reset completion is indicated. The admin queue must be reinitialized
 * after this operation.
 *
 * When reset is complete, PF must ensure that all queues in all VSIs associated
 * with the VF are stopped, all queue configurations in the HMC are set to 0,
 * and all MAC and VLAN filters (except the शेष MAC address) on all VSIs
 * are cleared.
 */

/* VSI types that use VIRTCHNL पूर्णांकerface क्रम VF-PF communication. VSI_SRIOV
 * vsi_type should always be 6 क्रम backward compatibility. Add other fields
 * as needed.
 */
क्रमागत virtchnl_vsi_type अणु
	VIRTCHNL_VSI_TYPE_INVALID = 0,
	VIRTCHNL_VSI_SRIOV = 6,
पूर्ण;

/* VIRTCHNL_OP_GET_VF_RESOURCES
 * Version 1.0 VF sends this request to PF with no parameters
 * Version 1.1 VF sends this request to PF with u32 biपंचांगap of its capabilities
 * PF responds with an indirect message containing
 * virtchnl_vf_resource and one or more
 * virtchnl_vsi_resource काष्ठाures.
 */

काष्ठा virtchnl_vsi_resource अणु
	u16 vsi_id;
	u16 num_queue_pairs;
	क्रमागत virtchnl_vsi_type vsi_type;
	u16 qset_handle;
	u8 शेष_mac_addr[ETH_ALEN];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(16, virtchnl_vsi_resource);

/* VF capability flags
 * VIRTCHNL_VF_OFFLOAD_L2 flag is inclusive of base mode L2 offloads including
 * TX/RX Checksum offloading and TSO क्रम non-tunnelled packets.
 */
#घोषणा VIRTCHNL_VF_OFFLOAD_L2			0x00000001
#घोषणा VIRTCHNL_VF_OFFLOAD_IWARP		0x00000002
#घोषणा VIRTCHNL_VF_OFFLOAD_RSVD		0x00000004
#घोषणा VIRTCHNL_VF_OFFLOAD_RSS_AQ		0x00000008
#घोषणा VIRTCHNL_VF_OFFLOAD_RSS_REG		0x00000010
#घोषणा VIRTCHNL_VF_OFFLOAD_WB_ON_ITR		0x00000020
#घोषणा VIRTCHNL_VF_OFFLOAD_REQ_QUEUES		0x00000040
#घोषणा VIRTCHNL_VF_OFFLOAD_VLAN		0x00010000
#घोषणा VIRTCHNL_VF_OFFLOAD_RX_POLLING		0x00020000
#घोषणा VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2	0x00040000
#घोषणा VIRTCHNL_VF_OFFLOAD_RSS_PF		0X00080000
#घोषणा VIRTCHNL_VF_OFFLOAD_ENCAP		0X00100000
#घोषणा VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM		0X00200000
#घोषणा VIRTCHNL_VF_OFFLOAD_RX_ENCAP_CSUM	0X00400000
#घोषणा VIRTCHNL_VF_OFFLOAD_ADQ			0X00800000
#घोषणा VIRTCHNL_VF_OFFLOAD_USO			0X02000000
#घोषणा VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF		0X08000000
#घोषणा VIRTCHNL_VF_OFFLOAD_Fसूची_PF		0X10000000

/* Define below the capability flags that are not offloads */
#घोषणा VIRTCHNL_VF_CAP_ADV_LINK_SPEED		0x00000080
#घोषणा VF_BASE_MODE_OFFLOADS (VIRTCHNL_VF_OFFLOAD_L2 | \
			       VIRTCHNL_VF_OFFLOAD_VLAN | \
			       VIRTCHNL_VF_OFFLOAD_RSS_PF)

काष्ठा virtchnl_vf_resource अणु
	u16 num_vsis;
	u16 num_queue_pairs;
	u16 max_vectors;
	u16 max_mtu;

	u32 vf_cap_flags;
	u32 rss_key_size;
	u32 rss_lut_size;

	काष्ठा virtchnl_vsi_resource vsi_res[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(36, virtchnl_vf_resource);

/* VIRTCHNL_OP_CONFIG_TX_QUEUE
 * VF sends this message to set up parameters क्रम one TX queue.
 * External data buffer contains one instance of virtchnl_txq_info.
 * PF configures requested queue and वापसs a status code.
 */

/* Tx queue config info */
काष्ठा virtchnl_txq_info अणु
	u16 vsi_id;
	u16 queue_id;
	u16 ring_len;		/* number of descriptors, multiple of 8 */
	u16 headwb_enabled; /* deprecated with AVF 1.0 */
	u64 dma_ring_addr;
	u64 dma_headwb_addr; /* deprecated with AVF 1.0 */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(24, virtchnl_txq_info);

/* VIRTCHNL_OP_CONFIG_RX_QUEUE
 * VF sends this message to set up parameters क्रम one RX queue.
 * External data buffer contains one instance of virtchnl_rxq_info.
 * PF configures requested queue and वापसs a status code.
 */

/* Rx queue config info */
काष्ठा virtchnl_rxq_info अणु
	u16 vsi_id;
	u16 queue_id;
	u32 ring_len;		/* number of descriptors, multiple of 32 */
	u16 hdr_size;
	u16 splithdr_enabled; /* deprecated with AVF 1.0 */
	u32 databuffer_size;
	u32 max_pkt_size;
	u32 pad1;
	u64 dma_ring_addr;
	क्रमागत virtchnl_rx_hsplit rx_split_pos; /* deprecated with AVF 1.0 */
	u32 pad2;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(40, virtchnl_rxq_info);

/* VIRTCHNL_OP_CONFIG_VSI_QUEUES
 * VF sends this message to set parameters क्रम all active TX and RX queues
 * associated with the specअगरied VSI.
 * PF configures queues and वापसs status.
 * If the number of queues specअगरied is greater than the number of queues
 * associated with the VSI, an error is वापसed and no queues are configured.
 */
काष्ठा virtchnl_queue_pair_info अणु
	/* NOTE: vsi_id and queue_id should be identical क्रम both queues. */
	काष्ठा virtchnl_txq_info txq;
	काष्ठा virtchnl_rxq_info rxq;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(64, virtchnl_queue_pair_info);

काष्ठा virtchnl_vsi_queue_config_info अणु
	u16 vsi_id;
	u16 num_queue_pairs;
	u32 pad;
	काष्ठा virtchnl_queue_pair_info qpair[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(72, virtchnl_vsi_queue_config_info);

/* VIRTCHNL_OP_REQUEST_QUEUES
 * VF sends this message to request the PF to allocate additional queues to
 * this VF.  Each VF माला_लो a guaranteed number of queues on init but asking क्रम
 * additional queues must be negotiated.  This is a best efक्रमt request as it
 * is possible the PF करोes not have enough queues left to support the request.
 * If the PF cannot support the number requested it will respond with the
 * maximum number it is able to support.  If the request is successful, PF will
 * then reset the VF to institute required changes.
 */

/* VF resource request */
काष्ठा virtchnl_vf_res_request अणु
	u16 num_queue_pairs;
पूर्ण;

/* VIRTCHNL_OP_CONFIG_IRQ_MAP
 * VF uses this message to map vectors to queues.
 * The rxq_map and txq_map fields are biपंचांगaps used to indicate which queues
 * are to be associated with the specअगरied vector.
 * The "other" causes are always mapped to vector 0.
 * PF configures पूर्णांकerrupt mapping and वापसs status.
 */
काष्ठा virtchnl_vector_map अणु
	u16 vsi_id;
	u16 vector_id;
	u16 rxq_map;
	u16 txq_map;
	u16 rxitr_idx;
	u16 txitr_idx;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(12, virtchnl_vector_map);

काष्ठा virtchnl_irq_map_info अणु
	u16 num_vectors;
	काष्ठा virtchnl_vector_map vecmap[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(14, virtchnl_irq_map_info);

/* VIRTCHNL_OP_ENABLE_QUEUES
 * VIRTCHNL_OP_DISABLE_QUEUES
 * VF sends these message to enable or disable TX/RX queue pairs.
 * The queues fields are biपंचांगaps indicating which queues to act upon.
 * (Currently, we only support 16 queues per VF, but we make the field
 * u32 to allow क्रम expansion.)
 * PF perक्रमms requested action and वापसs status.
 */
काष्ठा virtchnl_queue_select अणु
	u16 vsi_id;
	u16 pad;
	u32 rx_queues;
	u32 tx_queues;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(12, virtchnl_queue_select);

/* VIRTCHNL_OP_ADD_ETH_ADDR
 * VF sends this message in order to add one or more unicast or multicast
 * address filters क्रम the specअगरied VSI.
 * PF adds the filters and वापसs status.
 */

/* VIRTCHNL_OP_DEL_ETH_ADDR
 * VF sends this message in order to हटाओ one or more unicast or multicast
 * filters क्रम the specअगरied VSI.
 * PF हटाओs the filters and वापसs status.
 */

काष्ठा virtchnl_ether_addr अणु
	u8 addr[ETH_ALEN];
	u8 pad[2];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(8, virtchnl_ether_addr);

काष्ठा virtchnl_ether_addr_list अणु
	u16 vsi_id;
	u16 num_elements;
	काष्ठा virtchnl_ether_addr list[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(12, virtchnl_ether_addr_list);

/* VIRTCHNL_OP_ADD_VLAN
 * VF sends this message to add one or more VLAN tag filters क्रम receives.
 * PF adds the filters and वापसs status.
 * If a port VLAN is configured by the PF, this operation will वापस an
 * error to the VF.
 */

/* VIRTCHNL_OP_DEL_VLAN
 * VF sends this message to हटाओ one or more VLAN tag filters क्रम receives.
 * PF हटाओs the filters and वापसs status.
 * If a port VLAN is configured by the PF, this operation will वापस an
 * error to the VF.
 */

काष्ठा virtchnl_vlan_filter_list अणु
	u16 vsi_id;
	u16 num_elements;
	u16 vlan_id[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(6, virtchnl_vlan_filter_list);

/* VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE
 * VF sends VSI id and flags.
 * PF वापसs status code in retval.
 * Note: we assume that broadcast accept mode is always enabled.
 */
काष्ठा virtchnl_promisc_info अणु
	u16 vsi_id;
	u16 flags;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(4, virtchnl_promisc_info);

#घोषणा FLAG_VF_UNICAST_PROMISC	0x00000001
#घोषणा FLAG_VF_MULTICAST_PROMISC	0x00000002

/* VIRTCHNL_OP_GET_STATS
 * VF sends this message to request stats क्रम the selected VSI. VF uses
 * the virtchnl_queue_select काष्ठा to specअगरy the VSI. The queue_id
 * field is ignored by the PF.
 *
 * PF replies with काष्ठा eth_stats in an बाह्यal buffer.
 */

/* VIRTCHNL_OP_CONFIG_RSS_KEY
 * VIRTCHNL_OP_CONFIG_RSS_LUT
 * VF sends these messages to configure RSS. Only supported अगर both PF
 * and VF drivers set the VIRTCHNL_VF_OFFLOAD_RSS_PF bit during
 * configuration negotiation. If this is the हाल, then the RSS fields in
 * the VF resource काष्ठा are valid.
 * Both the key and LUT are initialized to 0 by the PF, meaning that
 * RSS is effectively disabled until set up by the VF.
 */
काष्ठा virtchnl_rss_key अणु
	u16 vsi_id;
	u16 key_len;
	u8 key[1];         /* RSS hash key, packed bytes */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(6, virtchnl_rss_key);

काष्ठा virtchnl_rss_lut अणु
	u16 vsi_id;
	u16 lut_entries;
	u8 lut[1];        /* RSS lookup table */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(6, virtchnl_rss_lut);

/* VIRTCHNL_OP_GET_RSS_HENA_CAPS
 * VIRTCHNL_OP_SET_RSS_HENA
 * VF sends these messages to get and set the hash filter enable bits क्रम RSS.
 * By शेष, the PF sets these to all possible traffic types that the
 * hardware supports. The VF can query this value अगर it wants to change the
 * traffic types that are hashed by the hardware.
 */
काष्ठा virtchnl_rss_hena अणु
	u64 hena;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(8, virtchnl_rss_hena);

/* VIRTCHNL_OP_ENABLE_CHANNELS
 * VIRTCHNL_OP_DISABLE_CHANNELS
 * VF sends these messages to enable or disable channels based on
 * the user specअगरied queue count and queue offset क्रम each traffic class.
 * This काष्ठा encompasses all the inक्रमmation that the PF needs from
 * VF to create a channel.
 */
काष्ठा virtchnl_channel_info अणु
	u16 count; /* number of queues in a channel */
	u16 offset; /* queues in a channel start from 'offset' */
	u32 pad;
	u64 max_tx_rate;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(16, virtchnl_channel_info);

काष्ठा virtchnl_tc_info अणु
	u32	num_tc;
	u32	pad;
	काष्ठा	virtchnl_channel_info list[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(24, virtchnl_tc_info);

/* VIRTCHNL_ADD_CLOUD_FILTER
 * VIRTCHNL_DEL_CLOUD_FILTER
 * VF sends these messages to add or delete a cloud filter based on the
 * user specअगरied match and action filters. These काष्ठाures encompass
 * all the inक्रमmation that the PF needs from the VF to add/delete a
 * cloud filter.
 */

काष्ठा virtchnl_l4_spec अणु
	u8	src_mac[ETH_ALEN];
	u8	dst_mac[ETH_ALEN];
	__be16	vlan_id;
	__be16	pad; /* reserved क्रम future use */
	__be32	src_ip[4];
	__be32	dst_ip[4];
	__be16	src_port;
	__be16	dst_port;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(52, virtchnl_l4_spec);

जोड़ virtchnl_flow_spec अणु
	काष्ठा	virtchnl_l4_spec tcp_spec;
	u8	buffer[128]; /* reserved क्रम future use */
पूर्ण;

VIRTCHNL_CHECK_UNION_LEN(128, virtchnl_flow_spec);

क्रमागत virtchnl_action अणु
	/* action types */
	VIRTCHNL_ACTION_DROP = 0,
	VIRTCHNL_ACTION_TC_REसूचीECT,
	VIRTCHNL_ACTION_PASSTHRU,
	VIRTCHNL_ACTION_QUEUE,
	VIRTCHNL_ACTION_Q_REGION,
	VIRTCHNL_ACTION_MARK,
	VIRTCHNL_ACTION_COUNT,
पूर्ण;

क्रमागत virtchnl_flow_type अणु
	/* flow types */
	VIRTCHNL_TCP_V4_FLOW = 0,
	VIRTCHNL_TCP_V6_FLOW,
पूर्ण;

काष्ठा virtchnl_filter अणु
	जोड़	virtchnl_flow_spec data;
	जोड़	virtchnl_flow_spec mask;
	क्रमागत	virtchnl_flow_type flow_type;
	क्रमागत	virtchnl_action action;
	u32	action_meta;
	u8	field_flags;
	u8	pad[3];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(272, virtchnl_filter);

/* VIRTCHNL_OP_EVENT
 * PF sends this message to inक्रमm the VF driver of events that may affect it.
 * No direct response is expected from the VF, though it may generate other
 * messages in response to this one.
 */
क्रमागत virtchnl_event_codes अणु
	VIRTCHNL_EVENT_UNKNOWN = 0,
	VIRTCHNL_EVENT_LINK_CHANGE,
	VIRTCHNL_EVENT_RESET_IMPENDING,
	VIRTCHNL_EVENT_PF_DRIVER_CLOSE,
पूर्ण;

#घोषणा PF_EVENT_SEVERITY_INFO		0
#घोषणा PF_EVENT_SEVERITY_CERTAIN_DOOM	255

काष्ठा virtchnl_pf_event अणु
	क्रमागत virtchnl_event_codes event;
	जोड़ अणु
		/* If the PF driver करोes not support the new speed reporting
		 * capabilities then use link_event अन्यथा use link_event_adv to
		 * get the speed and link inक्रमmation. The ability to understand
		 * new speeds is indicated by setting the capability flag
		 * VIRTCHNL_VF_CAP_ADV_LINK_SPEED in vf_cap_flags parameter
		 * in virtchnl_vf_resource काष्ठा and can be used to determine
		 * which link event काष्ठा to use below.
		 */
		काष्ठा अणु
			क्रमागत virtchnl_link_speed link_speed;
			bool link_status;
		पूर्ण link_event;
		काष्ठा अणु
			/* link_speed provided in Mbps */
			u32 link_speed;
			u8 link_status;
			u8 pad[3];
		पूर्ण link_event_adv;
	पूर्ण event_data;

	पूर्णांक severity;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(16, virtchnl_pf_event);

/* VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP
 * VF uses this message to request PF to map IWARP vectors to IWARP queues.
 * The request क्रम this originates from the VF IWARP driver through
 * a client पूर्णांकerface between VF LAN and VF IWARP driver.
 * A vector could have an AEQ and CEQ attached to it although
 * there is a single AEQ per VF IWARP instance in which हाल
 * most vectors will have an INVALID_IDX क्रम aeq and valid idx क्रम ceq.
 * There will never be a हाल where there will be multiple CEQs attached
 * to a single vector.
 * PF configures पूर्णांकerrupt mapping and वापसs status.
 */

काष्ठा virtchnl_iwarp_qv_info अणु
	u32 v_idx; /* msix_vector */
	u16 ceq_idx;
	u16 aeq_idx;
	u8 itr_idx;
	u8 pad[3];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(12, virtchnl_iwarp_qv_info);

काष्ठा virtchnl_iwarp_qvlist_info अणु
	u32 num_vectors;
	काष्ठा virtchnl_iwarp_qv_info qv_info[1];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(16, virtchnl_iwarp_qvlist_info);

/* VF reset states - these are written पूर्णांकo the RSTAT रेजिस्टर:
 * VFGEN_RSTAT on the VF
 * When the PF initiates a reset, it ग_लिखोs 0
 * When the reset is complete, it ग_लिखोs 1
 * When the PF detects that the VF has recovered, it ग_लिखोs 2
 * VF checks this रेजिस्टर periodically to determine अगर a reset has occurred,
 * then polls it to know when the reset is complete.
 * If either the PF or VF पढ़ोs the रेजिस्टर जबतक the hardware
 * is in a reset state, it will वापस DEADBEEF, which, when masked
 * will result in 3.
 */
क्रमागत virtchnl_vfr_states अणु
	VIRTCHNL_VFR_INPROGRESS = 0,
	VIRTCHNL_VFR_COMPLETED,
	VIRTCHNL_VFR_VFACTIVE,
पूर्ण;

/* Type of RSS algorithm */
क्रमागत virtchnl_rss_algorithm अणु
	VIRTCHNL_RSS_ALG_TOEPLITZ_ASYMMETRIC	= 0,
	VIRTCHNL_RSS_ALG_R_ASYMMETRIC		= 1,
	VIRTCHNL_RSS_ALG_TOEPLITZ_SYMMETRIC	= 2,
	VIRTCHNL_RSS_ALG_XOR_SYMMETRIC		= 3,
पूर्ण;

#घोषणा VIRTCHNL_MAX_NUM_PROTO_HDRS	32
#घोषणा PROTO_HDR_SHIFT			5
#घोषणा PROTO_HDR_FIELD_START(proto_hdr_type) ((proto_hdr_type) << PROTO_HDR_SHIFT)
#घोषणा PROTO_HDR_FIELD_MASK ((1UL << PROTO_HDR_SHIFT) - 1)

/* VF use these macros to configure each protocol header.
 * Specअगरy which protocol headers and protocol header fields base on
 * virtchnl_proto_hdr_type and virtchnl_proto_hdr_field.
 * @param hdr: a काष्ठा of virtchnl_proto_hdr
 * @param hdr_type: ETH/IPV4/TCP, etc
 * @param field: SRC/DST/TEID/SPI, etc
 */
#घोषणा VIRTCHNL_ADD_PROTO_HDR_FIELD(hdr, field) \
	((hdr)->field_selector |= BIT((field) & PROTO_HDR_FIELD_MASK))
#घोषणा VIRTCHNL_DEL_PROTO_HDR_FIELD(hdr, field) \
	((hdr)->field_selector &= ~BIT((field) & PROTO_HDR_FIELD_MASK))
#घोषणा VIRTCHNL_TEST_PROTO_HDR_FIELD(hdr, val) \
	((hdr)->field_selector & BIT((val) & PROTO_HDR_FIELD_MASK))
#घोषणा VIRTCHNL_GET_PROTO_HDR_FIELD(hdr)	((hdr)->field_selector)

#घोषणा VIRTCHNL_ADD_PROTO_HDR_FIELD_BIT(hdr, hdr_type, field) \
	(VIRTCHNL_ADD_PROTO_HDR_FIELD(hdr, \
		VIRTCHNL_PROTO_HDR_ ## hdr_type ## _ ## field))
#घोषणा VIRTCHNL_DEL_PROTO_HDR_FIELD_BIT(hdr, hdr_type, field) \
	(VIRTCHNL_DEL_PROTO_HDR_FIELD(hdr, \
		VIRTCHNL_PROTO_HDR_ ## hdr_type ## _ ## field))

#घोषणा VIRTCHNL_SET_PROTO_HDR_TYPE(hdr, hdr_type) \
	((hdr)->type = VIRTCHNL_PROTO_HDR_ ## hdr_type)
#घोषणा VIRTCHNL_GET_PROTO_HDR_TYPE(hdr) \
	(((hdr)->type) >> PROTO_HDR_SHIFT)
#घोषणा VIRTCHNL_TEST_PROTO_HDR_TYPE(hdr, val) \
	((hdr)->type == ((val) >> PROTO_HDR_SHIFT))
#घोषणा VIRTCHNL_TEST_PROTO_HDR(hdr, val) \
	(VIRTCHNL_TEST_PROTO_HDR_TYPE((hdr), (val)) && \
	 VIRTCHNL_TEST_PROTO_HDR_FIELD((hdr), (val)))

/* Protocol header type within a packet segment. A segment consists of one or
 * more protocol headers that make up a logical group of protocol headers. Each
 * logical group of protocol headers encapsulates or is encapsulated using/by
 * tunneling or encapsulation protocols क्रम network भवization.
 */
क्रमागत virtchnl_proto_hdr_type अणु
	VIRTCHNL_PROTO_HDR_NONE,
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_S_VLAN,
	VIRTCHNL_PROTO_HDR_C_VLAN,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_TCP,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_SCTP,
	VIRTCHNL_PROTO_HDR_GTPU_IP,
	VIRTCHNL_PROTO_HDR_GTPU_EH,
	VIRTCHNL_PROTO_HDR_GTPU_EH_PDU_DWN,
	VIRTCHNL_PROTO_HDR_GTPU_EH_PDU_UP,
	VIRTCHNL_PROTO_HDR_PPPOE,
	VIRTCHNL_PROTO_HDR_L2TPV3,
	VIRTCHNL_PROTO_HDR_ESP,
	VIRTCHNL_PROTO_HDR_AH,
	VIRTCHNL_PROTO_HDR_PFCP,
पूर्ण;

/* Protocol header field within a protocol header. */
क्रमागत virtchnl_proto_hdr_field अणु
	/* ETHER */
	VIRTCHNL_PROTO_HDR_ETH_SRC =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_ETH),
	VIRTCHNL_PROTO_HDR_ETH_DST,
	VIRTCHNL_PROTO_HDR_ETH_ETHERTYPE,
	/* S-VLAN */
	VIRTCHNL_PROTO_HDR_S_VLAN_ID =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_S_VLAN),
	/* C-VLAN */
	VIRTCHNL_PROTO_HDR_C_VLAN_ID =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_C_VLAN),
	/* IPV4 */
	VIRTCHNL_PROTO_HDR_IPV4_SRC =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_IPV4),
	VIRTCHNL_PROTO_HDR_IPV4_DST,
	VIRTCHNL_PROTO_HDR_IPV4_DSCP,
	VIRTCHNL_PROTO_HDR_IPV4_TTL,
	VIRTCHNL_PROTO_HDR_IPV4_PROT,
	/* IPV6 */
	VIRTCHNL_PROTO_HDR_IPV6_SRC =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_IPV6),
	VIRTCHNL_PROTO_HDR_IPV6_DST,
	VIRTCHNL_PROTO_HDR_IPV6_TC,
	VIRTCHNL_PROTO_HDR_IPV6_HOP_LIMIT,
	VIRTCHNL_PROTO_HDR_IPV6_PROT,
	/* TCP */
	VIRTCHNL_PROTO_HDR_TCP_SRC_PORT =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_TCP),
	VIRTCHNL_PROTO_HDR_TCP_DST_PORT,
	/* UDP */
	VIRTCHNL_PROTO_HDR_UDP_SRC_PORT =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_UDP),
	VIRTCHNL_PROTO_HDR_UDP_DST_PORT,
	/* SCTP */
	VIRTCHNL_PROTO_HDR_SCTP_SRC_PORT =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_SCTP),
	VIRTCHNL_PROTO_HDR_SCTP_DST_PORT,
	/* GTPU_IP */
	VIRTCHNL_PROTO_HDR_GTPU_IP_TEID =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_GTPU_IP),
	/* GTPU_EH */
	VIRTCHNL_PROTO_HDR_GTPU_EH_PDU =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_GTPU_EH),
	VIRTCHNL_PROTO_HDR_GTPU_EH_QFI,
	/* PPPOE */
	VIRTCHNL_PROTO_HDR_PPPOE_SESS_ID =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_PPPOE),
	/* L2TPV3 */
	VIRTCHNL_PROTO_HDR_L2TPV3_SESS_ID =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_L2TPV3),
	/* ESP */
	VIRTCHNL_PROTO_HDR_ESP_SPI =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_ESP),
	/* AH */
	VIRTCHNL_PROTO_HDR_AH_SPI =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_AH),
	/* PFCP */
	VIRTCHNL_PROTO_HDR_PFCP_S_FIELD =
		PROTO_HDR_FIELD_START(VIRTCHNL_PROTO_HDR_PFCP),
	VIRTCHNL_PROTO_HDR_PFCP_SEID,
पूर्ण;

काष्ठा virtchnl_proto_hdr अणु
	क्रमागत virtchnl_proto_hdr_type type;
	u32 field_selector; /* a bit mask to select field क्रम header type */
	u8 buffer[64];
	/**
	 * binary buffer in network order क्रम specअगरic header type.
	 * For example, अगर type = VIRTCHNL_PROTO_HDR_IPV4, a IPv4
	 * header is expected to be copied पूर्णांकo the buffer.
	 */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(72, virtchnl_proto_hdr);

काष्ठा virtchnl_proto_hdrs अणु
	u8 tunnel_level;
	u8 pad[3];
	/**
	 * specअगरy where protocol header start from.
	 * 0 - from the outer layer
	 * 1 - from the first inner layer
	 * 2 - from the second inner layer
	 * ....
	 **/
	पूर्णांक count; /* the proto layers must < VIRTCHNL_MAX_NUM_PROTO_HDRS */
	काष्ठा virtchnl_proto_hdr proto_hdr[VIRTCHNL_MAX_NUM_PROTO_HDRS];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(2312, virtchnl_proto_hdrs);

काष्ठा virtchnl_rss_cfg अणु
	काष्ठा virtchnl_proto_hdrs proto_hdrs;	   /* protocol headers */
	क्रमागत virtchnl_rss_algorithm rss_algorithm; /* RSS algorithm type */
	u8 reserved[128];			   /* reserve क्रम future */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(2444, virtchnl_rss_cfg);

/* action configuration क्रम Fसूची */
काष्ठा virtchnl_filter_action अणु
	क्रमागत virtchnl_action type;
	जोड़ अणु
		/* used क्रम queue and qgroup action */
		काष्ठा अणु
			u16 index;
			u8 region;
		पूर्ण queue;
		/* used क्रम count action */
		काष्ठा अणु
			/* share counter ID with other flow rules */
			u8 shared;
			u32 id; /* counter ID */
		पूर्ण count;
		/* used क्रम mark action */
		u32 mark_id;
		u8 reserve[32];
	पूर्ण act_conf;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(36, virtchnl_filter_action);

#घोषणा VIRTCHNL_MAX_NUM_ACTIONS  8

काष्ठा virtchnl_filter_action_set अणु
	/* action number must be less then VIRTCHNL_MAX_NUM_ACTIONS */
	पूर्णांक count;
	काष्ठा virtchnl_filter_action actions[VIRTCHNL_MAX_NUM_ACTIONS];
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(292, virtchnl_filter_action_set);

/* pattern and action क्रम Fसूची rule */
काष्ठा virtchnl_fdir_rule अणु
	काष्ठा virtchnl_proto_hdrs proto_hdrs;
	काष्ठा virtchnl_filter_action_set action_set;
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(2604, virtchnl_fdir_rule);

/* Status वापसed to VF after VF requests Fसूची commands
 * VIRTCHNL_Fसूची_SUCCESS
 * VF Fसूची related request is successfully करोne by PF
 * The request can be OP_ADD/DEL.
 *
 * VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE
 * OP_ADD_Fसूची_FILTER request is failed due to no Hardware resource.
 *
 * VIRTCHNL_Fसूची_FAILURE_RULE_EXIST
 * OP_ADD_Fसूची_FILTER request is failed due to the rule is alपढ़ोy existed.
 *
 * VIRTCHNL_Fसूची_FAILURE_RULE_CONFLICT
 * OP_ADD_Fसूची_FILTER request is failed due to conflict with existing rule.
 *
 * VIRTCHNL_Fसूची_FAILURE_RULE_NONEXIST
 * OP_DEL_Fसूची_FILTER request is failed due to this rule करोesn't exist.
 *
 * VIRTCHNL_Fसूची_FAILURE_RULE_INVALID
 * OP_ADD_Fसूची_FILTER request is failed due to parameters validation
 * or HW करोesn't support.
 *
 * VIRTCHNL_Fसूची_FAILURE_RULE_TIMEOUT
 * OP_ADD/DEL_Fसूची_FILTER request is failed due to timing out
 * क्रम programming.
 */
क्रमागत virtchnl_fdir_prgm_status अणु
	VIRTCHNL_Fसूची_SUCCESS = 0,
	VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE,
	VIRTCHNL_Fसूची_FAILURE_RULE_EXIST,
	VIRTCHNL_Fसूची_FAILURE_RULE_CONFLICT,
	VIRTCHNL_Fसूची_FAILURE_RULE_NONEXIST,
	VIRTCHNL_Fसूची_FAILURE_RULE_INVALID,
	VIRTCHNL_Fसूची_FAILURE_RULE_TIMEOUT,
पूर्ण;

/* VIRTCHNL_OP_ADD_Fसूची_FILTER
 * VF sends this request to PF by filling out vsi_id,
 * validate_only and rule_cfg. PF will वापस flow_id
 * अगर the request is successfully करोne and वापस add_status to VF.
 */
काष्ठा virtchnl_fdir_add अणु
	u16 vsi_id;  /* INPUT */
	/*
	 * 1 क्रम validating a fdir rule, 0 क्रम creating a fdir rule.
	 * Validate and create share one ops: VIRTCHNL_OP_ADD_Fसूची_FILTER.
	 */
	u16 validate_only; /* INPUT */
	u32 flow_id;       /* OUTPUT */
	काष्ठा virtchnl_fdir_rule rule_cfg; /* INPUT */
	क्रमागत virtchnl_fdir_prgm_status status; /* OUTPUT */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(2616, virtchnl_fdir_add);

/* VIRTCHNL_OP_DEL_Fसूची_FILTER
 * VF sends this request to PF by filling out vsi_id
 * and flow_id. PF will वापस del_status to VF.
 */
काष्ठा virtchnl_fdir_del अणु
	u16 vsi_id;  /* INPUT */
	u16 pad;
	u32 flow_id; /* INPUT */
	क्रमागत virtchnl_fdir_prgm_status status; /* OUTPUT */
पूर्ण;

VIRTCHNL_CHECK_STRUCT_LEN(12, virtchnl_fdir_del);

/**
 * virtchnl_vc_validate_vf_msg
 * @ver: Virtchnl version info
 * @v_opcode: Opcode क्रम the message
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 *
 * validate msg क्रमmat against काष्ठा क्रम each opcode
 */
अटल अंतरभूत पूर्णांक
virtchnl_vc_validate_vf_msg(काष्ठा virtchnl_version_info *ver, u32 v_opcode,
			    u8 *msg, u16 msglen)
अणु
	bool err_msg_क्रमmat = false;
	पूर्णांक valid_len = 0;

	/* Validate message length. */
	चयन (v_opcode) अणु
	हाल VIRTCHNL_OP_VERSION:
		valid_len = माप(काष्ठा virtchnl_version_info);
		अवरोध;
	हाल VIRTCHNL_OP_RESET_VF:
		अवरोध;
	हाल VIRTCHNL_OP_GET_VF_RESOURCES:
		अगर (VF_IS_V11(ver))
			valid_len = माप(u32);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_TX_QUEUE:
		valid_len = माप(काष्ठा virtchnl_txq_info);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RX_QUEUE:
		valid_len = माप(काष्ठा virtchnl_rxq_info);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_VSI_QUEUES:
		valid_len = माप(काष्ठा virtchnl_vsi_queue_config_info);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_vsi_queue_config_info *vqc =
			    (काष्ठा virtchnl_vsi_queue_config_info *)msg;
			valid_len += (vqc->num_queue_pairs *
				      माप(काष्ठा
					     virtchnl_queue_pair_info));
			अगर (vqc->num_queue_pairs == 0)
				err_msg_क्रमmat = true;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_IRQ_MAP:
		valid_len = माप(काष्ठा virtchnl_irq_map_info);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_irq_map_info *vimi =
			    (काष्ठा virtchnl_irq_map_info *)msg;
			valid_len += (vimi->num_vectors *
				      माप(काष्ठा virtchnl_vector_map));
			अगर (vimi->num_vectors == 0)
				err_msg_क्रमmat = true;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_QUEUES:
	हाल VIRTCHNL_OP_DISABLE_QUEUES:
		valid_len = माप(काष्ठा virtchnl_queue_select);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_ETH_ADDR:
	हाल VIRTCHNL_OP_DEL_ETH_ADDR:
		valid_len = माप(काष्ठा virtchnl_ether_addr_list);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_ether_addr_list *veal =
			    (काष्ठा virtchnl_ether_addr_list *)msg;
			valid_len += veal->num_elements *
			    माप(काष्ठा virtchnl_ether_addr);
			अगर (veal->num_elements == 0)
				err_msg_क्रमmat = true;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_ADD_VLAN:
	हाल VIRTCHNL_OP_DEL_VLAN:
		valid_len = माप(काष्ठा virtchnl_vlan_filter_list);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_vlan_filter_list *vfl =
			    (काष्ठा virtchnl_vlan_filter_list *)msg;
			valid_len += vfl->num_elements * माप(u16);
			अगर (vfl->num_elements == 0)
				err_msg_क्रमmat = true;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE:
		valid_len = माप(काष्ठा virtchnl_promisc_info);
		अवरोध;
	हाल VIRTCHNL_OP_GET_STATS:
		valid_len = माप(काष्ठा virtchnl_queue_select);
		अवरोध;
	हाल VIRTCHNL_OP_IWARP:
		/* These messages are opaque to us and will be validated in
		 * the RDMA client code. We just need to check क्रम nonzero
		 * length. The firmware will enक्रमce max length restrictions.
		 */
		अगर (msglen)
			valid_len = msglen;
		अन्यथा
			err_msg_क्रमmat = true;
		अवरोध;
	हाल VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP:
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP:
		valid_len = माप(काष्ठा virtchnl_iwarp_qvlist_info);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_iwarp_qvlist_info *qv =
				(काष्ठा virtchnl_iwarp_qvlist_info *)msg;
			अगर (qv->num_vectors == 0) अणु
				err_msg_क्रमmat = true;
				अवरोध;
			पूर्ण
			valid_len += ((qv->num_vectors - 1) *
				माप(काष्ठा virtchnl_iwarp_qv_info));
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RSS_KEY:
		valid_len = माप(काष्ठा virtchnl_rss_key);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_rss_key *vrk =
				(काष्ठा virtchnl_rss_key *)msg;
			valid_len += vrk->key_len - 1;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RSS_LUT:
		valid_len = माप(काष्ठा virtchnl_rss_lut);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_rss_lut *vrl =
				(काष्ठा virtchnl_rss_lut *)msg;
			valid_len += vrl->lut_entries - 1;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_GET_RSS_HENA_CAPS:
		अवरोध;
	हाल VIRTCHNL_OP_SET_RSS_HENA:
		valid_len = माप(काष्ठा virtchnl_rss_hena);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_VLAN_STRIPPING:
	हाल VIRTCHNL_OP_DISABLE_VLAN_STRIPPING:
		अवरोध;
	हाल VIRTCHNL_OP_REQUEST_QUEUES:
		valid_len = माप(काष्ठा virtchnl_vf_res_request);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_CHANNELS:
		valid_len = माप(काष्ठा virtchnl_tc_info);
		अगर (msglen >= valid_len) अणु
			काष्ठा virtchnl_tc_info *vti =
				(काष्ठा virtchnl_tc_info *)msg;
			valid_len += (vti->num_tc - 1) *
				     माप(काष्ठा virtchnl_channel_info);
			अगर (vti->num_tc == 0)
				err_msg_क्रमmat = true;
		पूर्ण
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_CHANNELS:
		अवरोध;
	हाल VIRTCHNL_OP_ADD_CLOUD_FILTER:
		valid_len = माप(काष्ठा virtchnl_filter);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_CLOUD_FILTER:
		valid_len = माप(काष्ठा virtchnl_filter);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_RSS_CFG:
	हाल VIRTCHNL_OP_DEL_RSS_CFG:
		valid_len = माप(काष्ठा virtchnl_rss_cfg);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_Fसूची_FILTER:
		valid_len = माप(काष्ठा virtchnl_fdir_add);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_Fसूची_FILTER:
		valid_len = माप(काष्ठा virtchnl_fdir_del);
		अवरोध;
	/* These are always errors coming from the VF. */
	हाल VIRTCHNL_OP_EVENT:
	हाल VIRTCHNL_OP_UNKNOWN:
	शेष:
		वापस VIRTCHNL_STATUS_ERR_PARAM;
	पूर्ण
	/* few more checks */
	अगर (err_msg_क्रमmat || valid_len != msglen)
		वापस VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* _VIRTCHNL_H_ */
