<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */
#अगर_अघोषित _ENA_ADMIN_H_
#घोषणा _ENA_ADMIN_H_

#घोषणा ENA_ADMIN_RSS_KEY_PARTS              10

क्रमागत ena_admin_aq_opcode अणु
	ENA_ADMIN_CREATE_SQ                         = 1,
	ENA_ADMIN_DESTROY_SQ                        = 2,
	ENA_ADMIN_CREATE_CQ                         = 3,
	ENA_ADMIN_DESTROY_CQ                        = 4,
	ENA_ADMIN_GET_FEATURE                       = 8,
	ENA_ADMIN_SET_FEATURE                       = 9,
	ENA_ADMIN_GET_STATS                         = 11,
पूर्ण;

क्रमागत ena_admin_aq_completion_status अणु
	ENA_ADMIN_SUCCESS                           = 0,
	ENA_ADMIN_RESOURCE_ALLOCATION_FAILURE       = 1,
	ENA_ADMIN_BAD_OPCODE                        = 2,
	ENA_ADMIN_UNSUPPORTED_OPCODE                = 3,
	ENA_ADMIN_MALFORMED_REQUEST                 = 4,
	/* Additional status is provided in ACQ entry extended_status */
	ENA_ADMIN_ILLEGAL_PARAMETER                 = 5,
	ENA_ADMIN_UNKNOWN_ERROR                     = 6,
	ENA_ADMIN_RESOURCE_BUSY                     = 7,
पूर्ण;

/* subcommands क्रम the set/get feature admin commands */
क्रमागत ena_admin_aq_feature_id अणु
	ENA_ADMIN_DEVICE_ATTRIBUTES                 = 1,
	ENA_ADMIN_MAX_QUEUES_NUM                    = 2,
	ENA_ADMIN_HW_HINTS                          = 3,
	ENA_ADMIN_LLQ                               = 4,
	ENA_ADMIN_MAX_QUEUES_EXT                    = 7,
	ENA_ADMIN_RSS_HASH_FUNCTION                 = 10,
	ENA_ADMIN_STATELESS_OFFLOAD_CONFIG          = 11,
	ENA_ADMIN_RSS_INसूचीECTION_TABLE_CONFIG      = 12,
	ENA_ADMIN_MTU                               = 14,
	ENA_ADMIN_RSS_HASH_INPUT                    = 18,
	ENA_ADMIN_INTERRUPT_MODERATION              = 20,
	ENA_ADMIN_AENQ_CONFIG                       = 26,
	ENA_ADMIN_LINK_CONFIG                       = 27,
	ENA_ADMIN_HOST_ATTR_CONFIG                  = 28,
	ENA_ADMIN_FEATURES_OPCODE_NUM               = 32,
पूर्ण;

क्रमागत ena_admin_placement_policy_type अणु
	/* descriptors and headers are in host memory */
	ENA_ADMIN_PLACEMENT_POLICY_HOST             = 1,
	/* descriptors and headers are in device memory (a.k.a Low Latency
	 * Queue)
	 */
	ENA_ADMIN_PLACEMENT_POLICY_DEV              = 3,
पूर्ण;

क्रमागत ena_admin_link_types अणु
	ENA_ADMIN_LINK_SPEED_1G                     = 0x1,
	ENA_ADMIN_LINK_SPEED_2_HALF_G               = 0x2,
	ENA_ADMIN_LINK_SPEED_5G                     = 0x4,
	ENA_ADMIN_LINK_SPEED_10G                    = 0x8,
	ENA_ADMIN_LINK_SPEED_25G                    = 0x10,
	ENA_ADMIN_LINK_SPEED_40G                    = 0x20,
	ENA_ADMIN_LINK_SPEED_50G                    = 0x40,
	ENA_ADMIN_LINK_SPEED_100G                   = 0x80,
	ENA_ADMIN_LINK_SPEED_200G                   = 0x100,
	ENA_ADMIN_LINK_SPEED_400G                   = 0x200,
पूर्ण;

क्रमागत ena_admin_completion_policy_type अणु
	/* completion queue entry क्रम each sq descriptor */
	ENA_ADMIN_COMPLETION_POLICY_DESC            = 0,
	/* completion queue entry upon request in sq descriptor */
	ENA_ADMIN_COMPLETION_POLICY_DESC_ON_DEMAND  = 1,
	/* current queue head poपूर्णांकer is updated in OS memory upon sq
	 * descriptor request
	 */
	ENA_ADMIN_COMPLETION_POLICY_HEAD_ON_DEMAND  = 2,
	/* current queue head poपूर्णांकer is updated in OS memory क्रम each sq
	 * descriptor
	 */
	ENA_ADMIN_COMPLETION_POLICY_HEAD            = 3,
पूर्ण;

/* basic stats वापस ena_admin_basic_stats जबतक extanded stats वापस a
 * buffer (string क्रमmat) with additional statistics per queue and per
 * device id
 */
क्रमागत ena_admin_get_stats_type अणु
	ENA_ADMIN_GET_STATS_TYPE_BASIC              = 0,
	ENA_ADMIN_GET_STATS_TYPE_EXTENDED           = 1,
	/* extra HW stats क्रम specअगरic network पूर्णांकerface */
	ENA_ADMIN_GET_STATS_TYPE_ENI                = 2,
पूर्ण;

क्रमागत ena_admin_get_stats_scope अणु
	ENA_ADMIN_SPECIFIC_QUEUE                    = 0,
	ENA_ADMIN_ETH_TRAFFIC                       = 1,
पूर्ण;

काष्ठा ena_admin_aq_common_desc अणु
	/* 11:0 : command_id
	 * 15:12 : reserved12
	 */
	u16 command_id;

	/* as appears in ena_admin_aq_opcode */
	u8 opcode;

	/* 0 : phase
	 * 1 : ctrl_data - control buffer address valid
	 * 2 : ctrl_data_indirect - control buffer address
	 *    poपूर्णांकs to list of pages with addresses of control
	 *    buffers
	 * 7:3 : reserved3
	 */
	u8 flags;
पूर्ण;

/* used in ena_admin_aq_entry. Can poपूर्णांक directly to control data, or to a
 * page list chunk. Used also at the end of indirect mode page list chunks,
 * क्रम chaining.
 */
काष्ठा ena_admin_ctrl_buff_info अणु
	u32 length;

	काष्ठा ena_common_mem_addr address;
पूर्ण;

काष्ठा ena_admin_sq अणु
	u16 sq_idx;

	/* 4:0 : reserved
	 * 7:5 : sq_direction - 0x1 - Tx; 0x2 - Rx
	 */
	u8 sq_identity;

	u8 reserved1;
पूर्ण;

काष्ठा ena_admin_aq_entry अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	जोड़ अणु
		u32 अंतरभूत_data_w1[3];

		काष्ठा ena_admin_ctrl_buff_info control_buffer;
	पूर्ण u;

	u32 अंतरभूत_data_w4[12];
पूर्ण;

काष्ठा ena_admin_acq_common_desc अणु
	/* command identअगरier to associate it with the aq descriptor
	 * 11:0 : command_id
	 * 15:12 : reserved12
	 */
	u16 command;

	u8 status;

	/* 0 : phase
	 * 7:1 : reserved1
	 */
	u8 flags;

	u16 extended_status;

	/* indicates to the driver which AQ entry has been consumed by the
	 * device and could be reused
	 */
	u16 sq_head_indx;
पूर्ण;

काष्ठा ena_admin_acq_entry अणु
	काष्ठा ena_admin_acq_common_desc acq_common_descriptor;

	u32 response_specअगरic_data[14];
पूर्ण;

काष्ठा ena_admin_aq_create_sq_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	/* 4:0 : reserved0_w1
	 * 7:5 : sq_direction - 0x1 - Tx, 0x2 - Rx
	 */
	u8 sq_identity;

	u8 reserved8_w1;

	/* 3:0 : placement_policy - Describing where the SQ
	 *    descriptor ring and the SQ packet headers reside:
	 *    0x1 - descriptors and headers are in OS memory,
	 *    0x3 - descriptors and headers in device memory
	 *    (a.k.a Low Latency Queue)
	 * 6:4 : completion_policy - Describing what policy
	 *    to use क्रम generation completion entry (cqe) in
	 *    the CQ associated with this SQ: 0x0 - cqe क्रम each
	 *    sq descriptor, 0x1 - cqe upon request in sq
	 *    descriptor, 0x2 - current queue head poपूर्णांकer is
	 *    updated in OS memory upon sq descriptor request
	 *    0x3 - current queue head poपूर्णांकer is updated in OS
	 *    memory क्रम each sq descriptor
	 * 7 : reserved15_w1
	 */
	u8 sq_caps_2;

	/* 0 : is_physically_contiguous - Described अगर the
	 *    queue ring memory is allocated in physical
	 *    contiguous pages or split.
	 * 7:1 : reserved17_w1
	 */
	u8 sq_caps_3;

	/* associated completion queue id. This CQ must be created prior to SQ
	 * creation
	 */
	u16 cq_idx;

	/* submission queue depth in entries */
	u16 sq_depth;

	/* SQ physical base address in OS memory. This field should not be
	 * used क्रम Low Latency queues. Has to be page aligned.
	 */
	काष्ठा ena_common_mem_addr sq_ba;

	/* specअगरies queue head ग_लिखोback location in OS memory. Valid अगर
	 * completion_policy is set to completion_policy_head_on_demand or
	 * completion_policy_head. Has to be cache aligned
	 */
	काष्ठा ena_common_mem_addr sq_head_ग_लिखोback;

	u32 reserved0_w7;

	u32 reserved0_w8;
पूर्ण;

क्रमागत ena_admin_sq_direction अणु
	ENA_ADMIN_SQ_सूचीECTION_TX                   = 1,
	ENA_ADMIN_SQ_सूचीECTION_RX                   = 2,
पूर्ण;

काष्ठा ena_admin_acq_create_sq_resp_desc अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;

	u16 sq_idx;

	u16 reserved;

	/* queue करोorbell address as an offset to PCIe MMIO REG BAR */
	u32 sq_करोorbell_offset;

	/* low latency queue ring base address as an offset to PCIe MMIO
	 * LLQ_MEM BAR
	 */
	u32 llq_descriptors_offset;

	/* low latency queue headers' memory as an offset to PCIe MMIO
	 * LLQ_MEM BAR
	 */
	u32 llq_headers_offset;
पूर्ण;

काष्ठा ena_admin_aq_destroy_sq_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	काष्ठा ena_admin_sq sq;
पूर्ण;

काष्ठा ena_admin_acq_destroy_sq_resp_desc अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;
पूर्ण;

काष्ठा ena_admin_aq_create_cq_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	/* 4:0 : reserved5
	 * 5 : पूर्णांकerrupt_mode_enabled - अगर set, cq operates
	 *    in पूर्णांकerrupt mode, otherwise - polling
	 * 7:6 : reserved6
	 */
	u8 cq_caps_1;

	/* 4:0 : cq_entry_size_words - size of CQ entry in
	 *    32-bit words, valid values: 4, 8.
	 * 7:5 : reserved7
	 */
	u8 cq_caps_2;

	/* completion queue depth in # of entries. must be घातer of 2 */
	u16 cq_depth;

	/* msix vector asचिन्हित to this cq */
	u32 msix_vector;

	/* cq physical base address in OS memory. CQ must be physically
	 * contiguous
	 */
	काष्ठा ena_common_mem_addr cq_ba;
पूर्ण;

काष्ठा ena_admin_acq_create_cq_resp_desc अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;

	u16 cq_idx;

	/* actual cq depth in number of entries */
	u16 cq_actual_depth;

	u32 numa_node_रेजिस्टर_offset;

	u32 cq_head_db_रेजिस्टर_offset;

	u32 cq_पूर्णांकerrupt_unmask_रेजिस्टर_offset;
पूर्ण;

काष्ठा ena_admin_aq_destroy_cq_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	u16 cq_idx;

	u16 reserved1;
पूर्ण;

काष्ठा ena_admin_acq_destroy_cq_resp_desc अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;
पूर्ण;

/* ENA AQ Get Statistics command. Extended statistics are placed in control
 * buffer poपूर्णांकed by AQ entry
 */
काष्ठा ena_admin_aq_get_stats_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	जोड़ अणु
		/* command specअगरic अंतरभूत data */
		u32 अंतरभूत_data_w1[3];

		काष्ठा ena_admin_ctrl_buff_info control_buffer;
	पूर्ण u;

	/* stats type as defined in क्रमागत ena_admin_get_stats_type */
	u8 type;

	/* stats scope defined in क्रमागत ena_admin_get_stats_scope */
	u8 scope;

	u16 reserved3;

	/* queue id. used when scope is specअगरic_queue */
	u16 queue_idx;

	/* device id, value 0xFFFF means mine. only privileged device can get
	 * stats of other device
	 */
	u16 device_id;
पूर्ण;

/* Basic Statistics Command. */
काष्ठा ena_admin_basic_stats अणु
	u32 tx_bytes_low;

	u32 tx_bytes_high;

	u32 tx_pkts_low;

	u32 tx_pkts_high;

	u32 rx_bytes_low;

	u32 rx_bytes_high;

	u32 rx_pkts_low;

	u32 rx_pkts_high;

	u32 rx_drops_low;

	u32 rx_drops_high;

	u32 tx_drops_low;

	u32 tx_drops_high;
पूर्ण;

/* ENI Statistics Command. */
काष्ठा ena_admin_eni_stats अणु
	/* The number of packets shaped due to inbound aggregate BW
	 * allowance being exceeded
	 */
	u64 bw_in_allowance_exceeded;

	/* The number of packets shaped due to outbound aggregate BW
	 * allowance being exceeded
	 */
	u64 bw_out_allowance_exceeded;

	/* The number of packets shaped due to PPS allowance being exceeded */
	u64 pps_allowance_exceeded;

	/* The number of packets shaped due to connection tracking
	 * allowance being exceeded and leading to failure in establishment
	 * of new connections
	 */
	u64 conntrack_allowance_exceeded;

	/* The number of packets shaped due to linklocal packet rate
	 * allowance being exceeded
	 */
	u64 linklocal_allowance_exceeded;
पूर्ण;

काष्ठा ena_admin_acq_get_stats_resp अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;

	जोड़ अणु
		u64 raw[7];

		काष्ठा ena_admin_basic_stats basic_stats;

		काष्ठा ena_admin_eni_stats eni_stats;
	पूर्ण u;
पूर्ण;

काष्ठा ena_admin_get_set_feature_common_desc अणु
	/* 1:0 : select - 0x1 - current value; 0x3 - शेष
	 *    value
	 * 7:3 : reserved3
	 */
	u8 flags;

	/* as appears in ena_admin_aq_feature_id */
	u8 feature_id;

	/* The driver specअगरies the max feature version it supports and the
	 * device responds with the currently supported feature version. The
	 * field is zero based
	 */
	u8 feature_version;

	u8 reserved8;
पूर्ण;

काष्ठा ena_admin_device_attr_feature_desc अणु
	u32 impl_id;

	u32 device_version;

	/* biपंचांगap of ena_admin_aq_feature_id, which represents supported
	 * subcommands क्रम the set/get feature admin commands.
	 */
	u32 supported_features;

	u32 reserved3;

	/* Indicates how many bits are used physical address access. */
	u32 phys_addr_width;

	/* Indicates how many bits are used भव address access. */
	u32 virt_addr_width;

	/* unicast MAC address (in Network byte order) */
	u8 mac_addr[6];

	u8 reserved7[2];

	u32 max_mtu;
पूर्ण;

क्रमागत ena_admin_llq_header_location अणु
	/* header is in descriptor list */
	ENA_ADMIN_INLINE_HEADER                     = 1,
	/* header in a separate ring, implies 16B descriptor list entry */
	ENA_ADMIN_HEADER_RING                       = 2,
पूर्ण;

क्रमागत ena_admin_llq_ring_entry_size अणु
	ENA_ADMIN_LIST_ENTRY_SIZE_128B              = 1,
	ENA_ADMIN_LIST_ENTRY_SIZE_192B              = 2,
	ENA_ADMIN_LIST_ENTRY_SIZE_256B              = 4,
पूर्ण;

क्रमागत ena_admin_llq_num_descs_beक्रमe_header अणु
	ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_0     = 0,
	ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_1     = 1,
	ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2     = 2,
	ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_4     = 4,
	ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_8     = 8,
पूर्ण;

/* packet descriptor list entry always starts with one or more descriptors,
 * followed by a header. The rest of the descriptors are located in the
 * beginning of the subsequent entry. Stride refers to how the rest of the
 * descriptors are placed. This field is relevant only क्रम अंतरभूत header
 * mode
 */
क्रमागत ena_admin_llq_stride_ctrl अणु
	ENA_ADMIN_SINGLE_DESC_PER_ENTRY             = 1,
	ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY          = 2,
पूर्ण;

क्रमागत ena_admin_accel_mode_feat अणु
	ENA_ADMIN_DISABLE_META_CACHING              = 0,
	ENA_ADMIN_LIMIT_TX_BURST                    = 1,
पूर्ण;

काष्ठा ena_admin_accel_mode_get अणु
	/* bit field of क्रमागत ena_admin_accel_mode_feat */
	u16 supported_flags;

	/* maximum burst size between two करोorbells. The size is in bytes */
	u16 max_tx_burst_size;
पूर्ण;

काष्ठा ena_admin_accel_mode_set अणु
	/* bit field of क्रमागत ena_admin_accel_mode_feat */
	u16 enabled_flags;

	u16 reserved;
पूर्ण;

काष्ठा ena_admin_accel_mode_req अणु
	जोड़ अणु
		u32 raw[2];

		काष्ठा ena_admin_accel_mode_get get;

		काष्ठा ena_admin_accel_mode_set set;
	पूर्ण u;
पूर्ण;

काष्ठा ena_admin_feature_llq_desc अणु
	u32 max_llq_num;

	u32 max_llq_depth;

	/* specअगरy the header locations the device supports. bitfield of क्रमागत
	 * ena_admin_llq_header_location.
	 */
	u16 header_location_ctrl_supported;

	/* the header location the driver selected to use. */
	u16 header_location_ctrl_enabled;

	/* अगर अंतरभूत header is specअगरied - this is the size of descriptor list
	 * entry. If header in a separate ring is specअगरied - this is the size
	 * of header ring entry. bitfield of क्रमागत ena_admin_llq_ring_entry_size.
	 * specअगरy the entry sizes the device supports
	 */
	u16 entry_size_ctrl_supported;

	/* the entry size the driver selected to use. */
	u16 entry_size_ctrl_enabled;

	/* valid only अगर अंतरभूत header is specअगरied. First entry associated with
	 * the packet includes descriptors and header. Rest of the entries
	 * occupied by descriptors. This parameter defines the max number of
	 * descriptors precedding the header in the first entry. The field is
	 * bitfield of क्रमागत ena_admin_llq_num_descs_beक्रमe_header and specअगरy
	 * the values the device supports
	 */
	u16 desc_num_beक्रमe_header_supported;

	/* the desire field the driver selected to use */
	u16 desc_num_beक्रमe_header_enabled;

	/* valid only अगर अंतरभूत was chosen. bitfield of क्रमागत
	 * ena_admin_llq_stride_ctrl
	 */
	u16 descriptors_stride_ctrl_supported;

	/* the stride control the driver selected to use */
	u16 descriptors_stride_ctrl_enabled;

	/* reserved */
	u32 reserved1;

	/* accelerated low latency queues requirement. driver needs to
	 * support those requirements in order to use accelerated llq
	 */
	काष्ठा ena_admin_accel_mode_req accel_mode;
पूर्ण;

काष्ठा ena_admin_queue_ext_feature_fields अणु
	u32 max_tx_sq_num;

	u32 max_tx_cq_num;

	u32 max_rx_sq_num;

	u32 max_rx_cq_num;

	u32 max_tx_sq_depth;

	u32 max_tx_cq_depth;

	u32 max_rx_sq_depth;

	u32 max_rx_cq_depth;

	u32 max_tx_header_size;

	/* Maximum Descriptors number, including meta descriptor, allowed क्रम a
	 * single Tx packet
	 */
	u16 max_per_packet_tx_descs;

	/* Maximum Descriptors number allowed क्रम a single Rx packet */
	u16 max_per_packet_rx_descs;
पूर्ण;

काष्ठा ena_admin_queue_feature_desc अणु
	u32 max_sq_num;

	u32 max_sq_depth;

	u32 max_cq_num;

	u32 max_cq_depth;

	u32 max_legacy_llq_num;

	u32 max_legacy_llq_depth;

	u32 max_header_size;

	/* Maximum Descriptors number, including meta descriptor, allowed क्रम a
	 * single Tx packet
	 */
	u16 max_packet_tx_descs;

	/* Maximum Descriptors number allowed क्रम a single Rx packet */
	u16 max_packet_rx_descs;
पूर्ण;

काष्ठा ena_admin_set_feature_mtu_desc अणु
	/* exclude L2 */
	u32 mtu;
पूर्ण;

काष्ठा ena_admin_set_feature_host_attr_desc अणु
	/* host OS info base address in OS memory. host info is 4KB of
	 * physically contiguous
	 */
	काष्ठा ena_common_mem_addr os_info_ba;

	/* host debug area base address in OS memory. debug area must be
	 * physically contiguous
	 */
	काष्ठा ena_common_mem_addr debug_ba;

	/* debug area size */
	u32 debug_area_size;
पूर्ण;

काष्ठा ena_admin_feature_पूर्णांकr_moder_desc अणु
	/* पूर्णांकerrupt delay granularity in usec */
	u16 पूर्णांकr_delay_resolution;

	u16 reserved;
पूर्ण;

काष्ठा ena_admin_get_feature_link_desc अणु
	/* Link speed in Mb */
	u32 speed;

	/* bit field of क्रमागत ena_admin_link types */
	u32 supported;

	/* 0 : स्वतःneg
	 * 1 : duplex - Full Duplex
	 * 31:2 : reserved2
	 */
	u32 flags;
पूर्ण;

काष्ठा ena_admin_feature_aenq_desc अणु
	/* biपंचांगask क्रम AENQ groups the device can report */
	u32 supported_groups;

	/* biपंचांगask क्रम AENQ groups to report */
	u32 enabled_groups;
पूर्ण;

काष्ठा ena_admin_feature_offload_desc अणु
	/* 0 : TX_L3_csum_ipv4
	 * 1 : TX_L4_ipv4_csum_part - The checksum field
	 *    should be initialized with pseuकरो header checksum
	 * 2 : TX_L4_ipv4_csum_full
	 * 3 : TX_L4_ipv6_csum_part - The checksum field
	 *    should be initialized with pseuकरो header checksum
	 * 4 : TX_L4_ipv6_csum_full
	 * 5 : tso_ipv4
	 * 6 : tso_ipv6
	 * 7 : tso_ecn
	 */
	u32 tx;

	/* Receive side supported stateless offload
	 * 0 : RX_L3_csum_ipv4 - IPv4 checksum
	 * 1 : RX_L4_ipv4_csum - TCP/UDP/IPv4 checksum
	 * 2 : RX_L4_ipv6_csum - TCP/UDP/IPv6 checksum
	 * 3 : RX_hash - Hash calculation
	 */
	u32 rx_supported;

	u32 rx_enabled;
पूर्ण;

क्रमागत ena_admin_hash_functions अणु
	ENA_ADMIN_TOEPLITZ                          = 1,
	ENA_ADMIN_CRC32                             = 2,
पूर्ण;

काष्ठा ena_admin_feature_rss_flow_hash_control अणु
	u32 key_parts;

	u32 reserved;

	u32 key[ENA_ADMIN_RSS_KEY_PARTS];
पूर्ण;

काष्ठा ena_admin_feature_rss_flow_hash_function अणु
	/* 7:0 : funcs - biपंचांगask of ena_admin_hash_functions */
	u32 supported_func;

	/* 7:0 : selected_func - biपंचांगask of
	 *    ena_admin_hash_functions
	 */
	u32 selected_func;

	/* initial value */
	u32 init_val;
पूर्ण;

/* RSS flow hash protocols */
क्रमागत ena_admin_flow_hash_proto अणु
	ENA_ADMIN_RSS_TCP4                          = 0,
	ENA_ADMIN_RSS_UDP4                          = 1,
	ENA_ADMIN_RSS_TCP6                          = 2,
	ENA_ADMIN_RSS_UDP6                          = 3,
	ENA_ADMIN_RSS_IP4                           = 4,
	ENA_ADMIN_RSS_IP6                           = 5,
	ENA_ADMIN_RSS_IP4_FRAG                      = 6,
	ENA_ADMIN_RSS_NOT_IP                        = 7,
	/* TCPv6 with extension header */
	ENA_ADMIN_RSS_TCP6_EX                       = 8,
	/* IPv6 with extension header */
	ENA_ADMIN_RSS_IP6_EX                        = 9,
	ENA_ADMIN_RSS_PROTO_NUM                     = 16,
पूर्ण;

/* RSS flow hash fields */
क्रमागत ena_admin_flow_hash_fields अणु
	/* Ethernet Dest Addr */
	ENA_ADMIN_RSS_L2_DA                         = BIT(0),
	/* Ethernet Src Addr */
	ENA_ADMIN_RSS_L2_SA                         = BIT(1),
	/* ipv4/6 Dest Addr */
	ENA_ADMIN_RSS_L3_DA                         = BIT(2),
	/* ipv4/6 Src Addr */
	ENA_ADMIN_RSS_L3_SA                         = BIT(3),
	/* tcp/udp Dest Port */
	ENA_ADMIN_RSS_L4_DP                         = BIT(4),
	/* tcp/udp Src Port */
	ENA_ADMIN_RSS_L4_SP                         = BIT(5),
पूर्ण;

काष्ठा ena_admin_proto_input अणु
	/* flow hash fields (bitwise according to ena_admin_flow_hash_fields) */
	u16 fields;

	u16 reserved2;
पूर्ण;

काष्ठा ena_admin_feature_rss_hash_control अणु
	काष्ठा ena_admin_proto_input supported_fields[ENA_ADMIN_RSS_PROTO_NUM];

	काष्ठा ena_admin_proto_input selected_fields[ENA_ADMIN_RSS_PROTO_NUM];

	काष्ठा ena_admin_proto_input reserved2[ENA_ADMIN_RSS_PROTO_NUM];

	काष्ठा ena_admin_proto_input reserved3[ENA_ADMIN_RSS_PROTO_NUM];
पूर्ण;

काष्ठा ena_admin_feature_rss_flow_hash_input अणु
	/* supported hash input sorting
	 * 1 : L3_sort - support swap L3 addresses अगर DA is
	 *    smaller than SA
	 * 2 : L4_sort - support swap L4 ports अगर DP smaller
	 *    SP
	 */
	u16 supported_input_sort;

	/* enabled hash input sorting
	 * 1 : enable_L3_sort - enable swap L3 addresses अगर
	 *    DA smaller than SA
	 * 2 : enable_L4_sort - enable swap L4 ports अगर DP
	 *    smaller than SP
	 */
	u16 enabled_input_sort;
पूर्ण;

क्रमागत ena_admin_os_type अणु
	ENA_ADMIN_OS_LINUX                          = 1,
	ENA_ADMIN_OS_WIN                            = 2,
	ENA_ADMIN_OS_DPDK                           = 3,
	ENA_ADMIN_OS_FREEBSD                        = 4,
	ENA_ADMIN_OS_IPXE                           = 5,
	ENA_ADMIN_OS_ESXI                           = 6,
	ENA_ADMIN_OS_GROUPS_NUM                     = 6,
पूर्ण;

काष्ठा ena_admin_host_info अणु
	/* defined in क्रमागत ena_admin_os_type */
	u32 os_type;

	/* os distribution string क्रमmat */
	u8 os_dist_str[128];

	/* OS distribution numeric क्रमmat */
	u32 os_dist;

	/* kernel version string क्रमmat */
	u8 kernel_ver_str[32];

	/* Kernel version numeric क्रमmat */
	u32 kernel_ver;

	/* 7:0 : major
	 * 15:8 : minor
	 * 23:16 : sub_minor
	 * 31:24 : module_type
	 */
	u32 driver_version;

	/* features biपंचांगap */
	u32 supported_network_features[2];

	/* ENA spec version of driver */
	u16 ena_spec_version;

	/* ENA device's Bus, Device and Function
	 * 2:0 : function
	 * 7:3 : device
	 * 15:8 : bus
	 */
	u16 bdf;

	/* Number of CPUs */
	u16 num_cpus;

	u16 reserved;

	/* 0 : reserved
	 * 1 : rx_offset
	 * 2 : पूर्णांकerrupt_moderation
	 * 3 : rx_buf_mirroring
	 * 4 : rss_configurable_function_key
	 * 31:5 : reserved
	 */
	u32 driver_supported_features;
पूर्ण;

काष्ठा ena_admin_rss_ind_table_entry अणु
	u16 cq_idx;

	u16 reserved;
पूर्ण;

काष्ठा ena_admin_feature_rss_ind_table अणु
	/* min supported table size (2^min_size) */
	u16 min_size;

	/* max supported table size (2^max_size) */
	u16 max_size;

	/* table size (2^size) */
	u16 size;

	u16 reserved;

	/* index of the अंतरभूत entry. 0xFFFFFFFF means invalid */
	u32 अंतरभूत_index;

	/* used क्रम updating single entry, ignored when setting the entire
	 * table through the control buffer.
	 */
	काष्ठा ena_admin_rss_ind_table_entry अंतरभूत_entry;
पूर्ण;

/* When hपूर्णांक value is 0, driver should use it's own predefined value */
काष्ठा ena_admin_ena_hw_hपूर्णांकs अणु
	/* value in ms */
	u16 mmio_पढ़ो_समयout;

	/* value in ms */
	u16 driver_watchकरोg_समयout;

	/* Per packet tx completion समयout. value in ms */
	u16 missing_tx_completion_समयout;

	u16 missed_tx_completion_count_threshold_to_reset;

	/* value in ms */
	u16 admin_completion_tx_समयout;

	u16 netdev_wd_समयout;

	u16 max_tx_sgl_size;

	u16 max_rx_sgl_size;

	u16 reserved[8];
पूर्ण;

काष्ठा ena_admin_get_feat_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	काष्ठा ena_admin_ctrl_buff_info control_buffer;

	काष्ठा ena_admin_get_set_feature_common_desc feat_common;

	u32 raw[11];
पूर्ण;

काष्ठा ena_admin_queue_ext_feature_desc अणु
	/* version */
	u8 version;

	u8 reserved1[3];

	जोड़ अणु
		काष्ठा ena_admin_queue_ext_feature_fields max_queue_ext;

		u32 raw[10];
	पूर्ण;
पूर्ण;

काष्ठा ena_admin_get_feat_resp अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;

	जोड़ अणु
		u32 raw[14];

		काष्ठा ena_admin_device_attr_feature_desc dev_attr;

		काष्ठा ena_admin_feature_llq_desc llq;

		काष्ठा ena_admin_queue_feature_desc max_queue;

		काष्ठा ena_admin_queue_ext_feature_desc max_queue_ext;

		काष्ठा ena_admin_feature_aenq_desc aenq;

		काष्ठा ena_admin_get_feature_link_desc link;

		काष्ठा ena_admin_feature_offload_desc offload;

		काष्ठा ena_admin_feature_rss_flow_hash_function flow_hash_func;

		काष्ठा ena_admin_feature_rss_flow_hash_input flow_hash_input;

		काष्ठा ena_admin_feature_rss_ind_table ind_table;

		काष्ठा ena_admin_feature_पूर्णांकr_moder_desc पूर्णांकr_moderation;

		काष्ठा ena_admin_ena_hw_hपूर्णांकs hw_hपूर्णांकs;
	पूर्ण u;
पूर्ण;

काष्ठा ena_admin_set_feat_cmd अणु
	काष्ठा ena_admin_aq_common_desc aq_common_descriptor;

	काष्ठा ena_admin_ctrl_buff_info control_buffer;

	काष्ठा ena_admin_get_set_feature_common_desc feat_common;

	जोड़ अणु
		u32 raw[11];

		/* mtu size */
		काष्ठा ena_admin_set_feature_mtu_desc mtu;

		/* host attributes */
		काष्ठा ena_admin_set_feature_host_attr_desc host_attr;

		/* AENQ configuration */
		काष्ठा ena_admin_feature_aenq_desc aenq;

		/* rss flow hash function */
		काष्ठा ena_admin_feature_rss_flow_hash_function flow_hash_func;

		/* rss flow hash input */
		काष्ठा ena_admin_feature_rss_flow_hash_input flow_hash_input;

		/* rss indirection table */
		काष्ठा ena_admin_feature_rss_ind_table ind_table;

		/* LLQ configuration */
		काष्ठा ena_admin_feature_llq_desc llq;
	पूर्ण u;
पूर्ण;

काष्ठा ena_admin_set_feat_resp अणु
	काष्ठा ena_admin_acq_common_desc acq_common_desc;

	जोड़ अणु
		u32 raw[14];
	पूर्ण u;
पूर्ण;

काष्ठा ena_admin_aenq_common_desc अणु
	u16 group;

	u16 syndrome;

	/* 0 : phase
	 * 7:1 : reserved - MBZ
	 */
	u8 flags;

	u8 reserved1[3];

	u32 बारtamp_low;

	u32 बारtamp_high;
पूर्ण;

/* asynchronous event notअगरication groups */
क्रमागत ena_admin_aenq_group अणु
	ENA_ADMIN_LINK_CHANGE                       = 0,
	ENA_ADMIN_FATAL_ERROR                       = 1,
	ENA_ADMIN_WARNING                           = 2,
	ENA_ADMIN_NOTIFICATION                      = 3,
	ENA_ADMIN_KEEP_ALIVE                        = 4,
	ENA_ADMIN_AENQ_GROUPS_NUM                   = 5,
पूर्ण;

क्रमागत ena_admin_aenq_notअगरication_syndrome अणु
	ENA_ADMIN_SUSPEND                           = 0,
	ENA_ADMIN_RESUME                            = 1,
	ENA_ADMIN_UPDATE_HINTS                      = 2,
पूर्ण;

काष्ठा ena_admin_aenq_entry अणु
	काष्ठा ena_admin_aenq_common_desc aenq_common_desc;

	/* command specअगरic अंतरभूत data */
	u32 अंतरभूत_data_w4[12];
पूर्ण;

काष्ठा ena_admin_aenq_link_change_desc अणु
	काष्ठा ena_admin_aenq_common_desc aenq_common_desc;

	/* 0 : link_status */
	u32 flags;
पूर्ण;

काष्ठा ena_admin_aenq_keep_alive_desc अणु
	काष्ठा ena_admin_aenq_common_desc aenq_common_desc;

	u32 rx_drops_low;

	u32 rx_drops_high;

	u32 tx_drops_low;

	u32 tx_drops_high;
पूर्ण;

काष्ठा ena_admin_ena_mmio_req_पढ़ो_less_resp अणु
	u16 req_id;

	u16 reg_off;

	/* value is valid when poll is cleared */
	u32 reg_val;
पूर्ण;

/* aq_common_desc */
#घोषणा ENA_ADMIN_AQ_COMMON_DESC_COMMAND_ID_MASK            GENMASK(11, 0)
#घोषणा ENA_ADMIN_AQ_COMMON_DESC_PHASE_MASK                 BIT(0)
#घोषणा ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_SHIFT            1
#घोषणा ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_MASK             BIT(1)
#घोषणा ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_SHIFT   2
#घोषणा ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_MASK    BIT(2)

/* sq */
#घोषणा ENA_ADMIN_SQ_SQ_सूचीECTION_SHIFT                     5
#घोषणा ENA_ADMIN_SQ_SQ_सूचीECTION_MASK                      GENMASK(7, 5)

/* acq_common_desc */
#घोषणा ENA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID_MASK           GENMASK(11, 0)
#घोषणा ENA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK                BIT(0)

/* aq_create_sq_cmd */
#घोषणा ENA_ADMIN_AQ_CREATE_SQ_CMD_SQ_सूचीECTION_SHIFT       5
#घोषणा ENA_ADMIN_AQ_CREATE_SQ_CMD_SQ_सूचीECTION_MASK        GENMASK(7, 5)
#घोषणा ENA_ADMIN_AQ_CREATE_SQ_CMD_PLACEMENT_POLICY_MASK    GENMASK(3, 0)
#घोषणा ENA_ADMIN_AQ_CREATE_SQ_CMD_COMPLETION_POLICY_SHIFT  4
#घोषणा ENA_ADMIN_AQ_CREATE_SQ_CMD_COMPLETION_POLICY_MASK   GENMASK(6, 4)
#घोषणा ENA_ADMIN_AQ_CREATE_SQ_CMD_IS_PHYSICALLY_CONTIGUOUS_MASK BIT(0)

/* aq_create_cq_cmd */
#घोषणा ENA_ADMIN_AQ_CREATE_CQ_CMD_INTERRUPT_MODE_ENABLED_SHIFT 5
#घोषणा ENA_ADMIN_AQ_CREATE_CQ_CMD_INTERRUPT_MODE_ENABLED_MASK BIT(5)
#घोषणा ENA_ADMIN_AQ_CREATE_CQ_CMD_CQ_ENTRY_SIZE_WORDS_MASK GENMASK(4, 0)

/* get_set_feature_common_desc */
#घोषणा ENA_ADMIN_GET_SET_FEATURE_COMMON_DESC_SELECT_MASK   GENMASK(1, 0)

/* get_feature_link_desc */
#घोषणा ENA_ADMIN_GET_FEATURE_LINK_DESC_AUTONEG_MASK        BIT(0)
#घोषणा ENA_ADMIN_GET_FEATURE_LINK_DESC_DUPLEX_SHIFT        1
#घोषणा ENA_ADMIN_GET_FEATURE_LINK_DESC_DUPLEX_MASK         BIT(1)

/* feature_offload_desc */
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L3_CSUM_IPV4_MASK BIT(0)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_SHIFT 1
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_MASK BIT(1)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_FULL_SHIFT 2
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_FULL_MASK BIT(2)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_PART_SHIFT 3
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_PART_MASK BIT(3)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_FULL_SHIFT 4
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_FULL_MASK BIT(4)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV4_SHIFT       5
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV4_MASK        BIT(5)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV6_SHIFT       6
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV6_MASK        BIT(6)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_ECN_SHIFT        7
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_ECN_MASK         BIT(7)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L3_CSUM_IPV4_MASK BIT(0)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV4_CSUM_SHIFT 1
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV4_CSUM_MASK BIT(1)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV6_CSUM_SHIFT 2
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV6_CSUM_MASK BIT(2)
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_HASH_SHIFT        3
#घोषणा ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_HASH_MASK         BIT(3)

/* feature_rss_flow_hash_function */
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_FUNCTION_FUNCS_MASK GENMASK(7, 0)
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_FUNCTION_SELECTED_FUNC_MASK GENMASK(7, 0)

/* feature_rss_flow_hash_input */
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L3_SORT_SHIFT 1
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L3_SORT_MASK  BIT(1)
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L4_SORT_SHIFT 2
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L4_SORT_MASK  BIT(2)
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_ENABLE_L3_SORT_SHIFT 1
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_ENABLE_L3_SORT_MASK BIT(1)
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_ENABLE_L4_SORT_SHIFT 2
#घोषणा ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_ENABLE_L4_SORT_MASK BIT(2)

/* host_info */
#घोषणा ENA_ADMIN_HOST_INFO_MAJOR_MASK                      GENMASK(7, 0)
#घोषणा ENA_ADMIN_HOST_INFO_MINOR_SHIFT                     8
#घोषणा ENA_ADMIN_HOST_INFO_MINOR_MASK                      GENMASK(15, 8)
#घोषणा ENA_ADMIN_HOST_INFO_SUB_MINOR_SHIFT                 16
#घोषणा ENA_ADMIN_HOST_INFO_SUB_MINOR_MASK                  GENMASK(23, 16)
#घोषणा ENA_ADMIN_HOST_INFO_MODULE_TYPE_SHIFT               24
#घोषणा ENA_ADMIN_HOST_INFO_MODULE_TYPE_MASK                GENMASK(31, 24)
#घोषणा ENA_ADMIN_HOST_INFO_FUNCTION_MASK                   GENMASK(2, 0)
#घोषणा ENA_ADMIN_HOST_INFO_DEVICE_SHIFT                    3
#घोषणा ENA_ADMIN_HOST_INFO_DEVICE_MASK                     GENMASK(7, 3)
#घोषणा ENA_ADMIN_HOST_INFO_BUS_SHIFT                       8
#घोषणा ENA_ADMIN_HOST_INFO_BUS_MASK                        GENMASK(15, 8)
#घोषणा ENA_ADMIN_HOST_INFO_RX_OFFSET_SHIFT                 1
#घोषणा ENA_ADMIN_HOST_INFO_RX_OFFSET_MASK                  BIT(1)
#घोषणा ENA_ADMIN_HOST_INFO_INTERRUPT_MODERATION_SHIFT      2
#घोषणा ENA_ADMIN_HOST_INFO_INTERRUPT_MODERATION_MASK       BIT(2)
#घोषणा ENA_ADMIN_HOST_INFO_RX_BUF_MIRRORING_SHIFT          3
#घोषणा ENA_ADMIN_HOST_INFO_RX_BUF_MIRRORING_MASK           BIT(3)
#घोषणा ENA_ADMIN_HOST_INFO_RSS_CONFIGURABLE_FUNCTION_KEY_SHIFT 4
#घोषणा ENA_ADMIN_HOST_INFO_RSS_CONFIGURABLE_FUNCTION_KEY_MASK BIT(4)

/* aenq_common_desc */
#घोषणा ENA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK               BIT(0)

/* aenq_link_change_desc */
#घोषणा ENA_ADMIN_AENQ_LINK_CHANGE_DESC_LINK_STATUS_MASK    BIT(0)

#पूर्ण_अगर /* _ENA_ADMIN_H_ */
