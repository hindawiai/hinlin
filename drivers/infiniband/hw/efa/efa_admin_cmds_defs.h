<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2021 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_ADMIN_CMDS_H_
#घोषणा _EFA_ADMIN_CMDS_H_

#घोषणा EFA_ADMIN_API_VERSION_MAJOR          0
#घोषणा EFA_ADMIN_API_VERSION_MINOR          1

/* EFA admin queue opcodes */
क्रमागत efa_admin_aq_opcode अणु
	EFA_ADMIN_CREATE_QP                         = 1,
	EFA_ADMIN_MODIFY_QP                         = 2,
	EFA_ADMIN_QUERY_QP                          = 3,
	EFA_ADMIN_DESTROY_QP                        = 4,
	EFA_ADMIN_CREATE_AH                         = 5,
	EFA_ADMIN_DESTROY_AH                        = 6,
	EFA_ADMIN_REG_MR                            = 7,
	EFA_ADMIN_DEREG_MR                          = 8,
	EFA_ADMIN_CREATE_CQ                         = 9,
	EFA_ADMIN_DESTROY_CQ                        = 10,
	EFA_ADMIN_GET_FEATURE                       = 11,
	EFA_ADMIN_SET_FEATURE                       = 12,
	EFA_ADMIN_GET_STATS                         = 13,
	EFA_ADMIN_ALLOC_PD                          = 14,
	EFA_ADMIN_DEALLOC_PD                        = 15,
	EFA_ADMIN_ALLOC_UAR                         = 16,
	EFA_ADMIN_DEALLOC_UAR                       = 17,
	EFA_ADMIN_MAX_OPCODE                        = 17,
पूर्ण;

क्रमागत efa_admin_aq_feature_id अणु
	EFA_ADMIN_DEVICE_ATTR                       = 1,
	EFA_ADMIN_AENQ_CONFIG                       = 2,
	EFA_ADMIN_NETWORK_ATTR                      = 3,
	EFA_ADMIN_QUEUE_ATTR                        = 4,
	EFA_ADMIN_HW_HINTS                          = 5,
	EFA_ADMIN_HOST_INFO                         = 6,
पूर्ण;

/* QP transport type */
क्रमागत efa_admin_qp_type अणु
	/* Unreliable Datagram */
	EFA_ADMIN_QP_TYPE_UD                        = 1,
	/* Scalable Reliable Datagram */
	EFA_ADMIN_QP_TYPE_SRD                       = 2,
पूर्ण;

/* QP state */
क्रमागत efa_admin_qp_state अणु
	EFA_ADMIN_QP_STATE_RESET                    = 0,
	EFA_ADMIN_QP_STATE_INIT                     = 1,
	EFA_ADMIN_QP_STATE_RTR                      = 2,
	EFA_ADMIN_QP_STATE_RTS                      = 3,
	EFA_ADMIN_QP_STATE_SQD                      = 4,
	EFA_ADMIN_QP_STATE_SQE                      = 5,
	EFA_ADMIN_QP_STATE_ERR                      = 6,
पूर्ण;

क्रमागत efa_admin_get_stats_type अणु
	EFA_ADMIN_GET_STATS_TYPE_BASIC              = 0,
	EFA_ADMIN_GET_STATS_TYPE_MESSAGES           = 1,
	EFA_ADMIN_GET_STATS_TYPE_RDMA_READ          = 2,
पूर्ण;

क्रमागत efa_admin_get_stats_scope अणु
	EFA_ADMIN_GET_STATS_SCOPE_ALL               = 0,
	EFA_ADMIN_GET_STATS_SCOPE_QUEUE             = 1,
पूर्ण;

/*
 * QP allocation sizes, converted by fabric QueuePair (QP) create command
 * from QP capabilities.
 */
काष्ठा efa_admin_qp_alloc_size अणु
	/* Send descriptor ring size in bytes */
	u32 send_queue_ring_size;

	/* Max number of WQEs that can be outstanding on send queue. */
	u32 send_queue_depth;

	/*
	 * Recv descriptor ring size in bytes, sufficient क्रम user-provided
	 * number of WQEs
	 */
	u32 recv_queue_ring_size;

	/* Max number of WQEs that can be outstanding on recv queue */
	u32 recv_queue_depth;
पूर्ण;

काष्ठा efa_admin_create_qp_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* Protection Doमुख्य associated with this QP */
	u16 pd;

	/* QP type */
	u8 qp_type;

	/*
	 * 0 : sq_virt - If set, SQ ring base address is
	 *    भव (IOVA वापसed by MR registration)
	 * 1 : rq_virt - If set, RQ ring base address is
	 *    भव (IOVA वापसed by MR registration)
	 * 7:2 : reserved - MBZ
	 */
	u8 flags;

	/*
	 * Send queue (SQ) ring base physical address. This field is not
	 * used अगर this is a Low Latency Queue(LLQ).
	 */
	u64 sq_base_addr;

	/* Receive queue (RQ) ring base address. */
	u64 rq_base_addr;

	/* Index of CQ to be associated with Send Queue completions */
	u32 send_cq_idx;

	/* Index of CQ to be associated with Recv Queue completions */
	u32 recv_cq_idx;

	/*
	 * Memory registration key क्रम the SQ ring, used only when not in
	 * LLQ mode and base address is भव
	 */
	u32 sq_l_key;

	/*
	 * Memory registration key क्रम the RQ ring, used only when base
	 * address is भव
	 */
	u32 rq_l_key;

	/* Requested QP allocation sizes */
	काष्ठा efa_admin_qp_alloc_size qp_alloc_size;

	/* UAR number */
	u16 uar;

	/* MBZ */
	u16 reserved;

	/* MBZ */
	u32 reserved2;
पूर्ण;

काष्ठा efa_admin_create_qp_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	/*
	 * Opaque handle to be used क्रम consequent admin operations on the
	 * QP
	 */
	u32 qp_handle;

	/*
	 * QP number in the given EFA भव device. Least-signअगरicant bits (as
	 * needed according to max_qp) carry unique QP ID
	 */
	u16 qp_num;

	/* MBZ */
	u16 reserved;

	/* Index of sub-CQ क्रम Send Queue completions */
	u16 send_sub_cq_idx;

	/* Index of sub-CQ क्रम Receive Queue completions */
	u16 recv_sub_cq_idx;

	/* SQ करोorbell address, as offset to PCIe DB BAR */
	u32 sq_db_offset;

	/* RQ करोorbell address, as offset to PCIe DB BAR */
	u32 rq_db_offset;

	/*
	 * low latency send queue ring base address as an offset to PCIe
	 * MMIO LLQ_MEM BAR
	 */
	u32 llq_descriptors_offset;
पूर्ण;

काष्ठा efa_admin_modअगरy_qp_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/*
	 * Mask indicating which fields should be updated
	 * 0 : qp_state
	 * 1 : cur_qp_state
	 * 2 : qkey
	 * 3 : sq_psn
	 * 4 : sq_drained_async_notअगरy
	 * 5 : rnr_retry
	 * 31:6 : reserved
	 */
	u32 modअगरy_mask;

	/* QP handle वापसed by create_qp command */
	u32 qp_handle;

	/* QP state */
	u32 qp_state;

	/* Override current QP state (beक्रमe applying the transition) */
	u32 cur_qp_state;

	/* QKey */
	u32 qkey;

	/* SQ PSN */
	u32 sq_psn;

	/* Enable async notअगरication when SQ is drained */
	u8 sq_drained_async_notअगरy;

	/* Number of RNR retries (valid only क्रम SRD QPs) */
	u8 rnr_retry;

	/* MBZ */
	u16 reserved2;
पूर्ण;

काष्ठा efa_admin_modअगरy_qp_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

काष्ठा efa_admin_query_qp_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* QP handle वापसed by create_qp command */
	u32 qp_handle;
पूर्ण;

काष्ठा efa_admin_query_qp_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	/* QP state */
	u32 qp_state;

	/* QKey */
	u32 qkey;

	/* SQ PSN */
	u32 sq_psn;

	/* Indicates that draining is in progress */
	u8 sq_draining;

	/* Number of RNR retries (valid only क्रम SRD QPs) */
	u8 rnr_retry;

	/* MBZ */
	u16 reserved2;
पूर्ण;

काष्ठा efa_admin_destroy_qp_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* QP handle वापसed by create_qp command */
	u32 qp_handle;
पूर्ण;

काष्ठा efa_admin_destroy_qp_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

/*
 * Create Address Handle command parameters. Must not be called more than
 * once क्रम the same destination
 */
काष्ठा efa_admin_create_ah_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* Destination address in network byte order */
	u8 dest_addr[16];

	/* PD number */
	u16 pd;

	/* MBZ */
	u16 reserved;
पूर्ण;

काष्ठा efa_admin_create_ah_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	/* Target पूर्णांकerface address handle (opaque) */
	u16 ah;

	/* MBZ */
	u16 reserved;
पूर्ण;

काष्ठा efa_admin_destroy_ah_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* Target पूर्णांकerface address handle (opaque) */
	u16 ah;

	/* PD number */
	u16 pd;
पूर्ण;

काष्ठा efa_admin_destroy_ah_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

/*
 * Registration of MemoryRegion, required क्रम QP working with Virtual
 * Addresses. In standard verbs semantics, region length is limited to 2GB
 * space, but EFA offers larger MR support क्रम large memory space, to ease
 * on users working with very large datasets (i.e. full GPU memory mapping).
 */
काष्ठा efa_admin_reg_mr_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* Protection Doमुख्य */
	u16 pd;

	/* MBZ */
	u16 reserved16_w1;

	/* Physical Buffer List, each element is page-aligned. */
	जोड़ अणु
		/*
		 * Inline array of guest-physical page addresses of user
		 * memory pages (optimization क्रम लघु region
		 * registrations)
		 */
		u64 अंतरभूत_pbl_array[4];

		/* poपूर्णांकs to PBL (direct or indirect, chained अगर needed) */
		काष्ठा efa_admin_ctrl_buff_info pbl;
	पूर्ण pbl;

	/* Memory region length, in bytes. */
	u64 mr_length;

	/*
	 * flags and page size
	 * 4:0 : phys_page_size_shअगरt - page size is (1 <<
	 *    phys_page_size_shअगरt). Page size is used क्रम
	 *    building the Virtual to Physical address mapping
	 * 6:5 : reserved - MBZ
	 * 7 : mem_addr_phy_mode_en - Enable bit क्रम physical
	 *    memory registration (no translation), can be used
	 *    only by privileged clients. If set, PBL must
	 *    contain a single entry.
	 */
	u8 flags;

	/*
	 * permissions
	 * 0 : local_ग_लिखो_enable - Local ग_लिखो permissions:
	 *    must be set क्रम RQ buffers and buffers posted क्रम
	 *    RDMA Read requests
	 * 1 : reserved1 - MBZ
	 * 2 : remote_पढ़ो_enable - Remote पढ़ो permissions:
	 *    must be set to enable RDMA पढ़ो from the region
	 * 7:3 : reserved2 - MBZ
	 */
	u8 permissions;

	/* MBZ */
	u16 reserved16_w5;

	/* number of pages in PBL (redundant, could be calculated) */
	u32 page_num;

	/*
	 * IO Virtual Address associated with this MR. If
	 * mem_addr_phy_mode_en is set, contains the physical address of
	 * the region.
	 */
	u64 iova;
पूर्ण;

काष्ठा efa_admin_reg_mr_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	/*
	 * L_Key, to be used in conjunction with local buffer references in
	 * SQ and RQ WQE, or with भव RQ/CQ rings
	 */
	u32 l_key;

	/*
	 * R_Key, to be used in RDMA messages to refer to remotely accessed
	 * memory region
	 */
	u32 r_key;
पूर्ण;

काष्ठा efa_admin_dereg_mr_cmd अणु
	/* Common Admin Queue descriptor */
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/* L_Key, memory region's l_key */
	u32 l_key;
पूर्ण;

काष्ठा efa_admin_dereg_mr_resp अणु
	/* Common Admin Queue completion descriptor */
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

काष्ठा efa_admin_create_cq_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	/*
	 * 4:0 : reserved5 - MBZ
	 * 5 : पूर्णांकerrupt_mode_enabled - अगर set, cq operates
	 *    in पूर्णांकerrupt mode (i.e. CQ events and MSI-X are
	 *    generated), otherwise - polling
	 * 6 : virt - If set, ring base address is भव
	 *    (IOVA वापसed by MR registration)
	 * 7 : reserved6 - MBZ
	 */
	u8 cq_caps_1;

	/*
	 * 4:0 : cq_entry_size_words - size of CQ entry in
	 *    32-bit words, valid values: 4, 8.
	 * 7:5 : reserved7 - MBZ
	 */
	u8 cq_caps_2;

	/* completion queue depth in # of entries. must be घातer of 2 */
	u16 cq_depth;

	/* msix vector asचिन्हित to this cq */
	u32 msix_vector_idx;

	/*
	 * CQ ring base address, भव or physical depending on 'virt'
	 * flag
	 */
	काष्ठा efa_common_mem_addr cq_ba;

	/*
	 * Memory registration key क्रम the ring, used only when base
	 * address is भव
	 */
	u32 l_key;

	/*
	 * number of sub cqs - must be equal to sub_cqs_per_cq of queue
	 * attributes.
	 */
	u16 num_sub_cqs;

	/* UAR number */
	u16 uar;
पूर्ण;

काष्ठा efa_admin_create_cq_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	u16 cq_idx;

	/* actual cq depth in number of entries */
	u16 cq_actual_depth;
पूर्ण;

काष्ठा efa_admin_destroy_cq_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_desc;

	u16 cq_idx;

	/* MBZ */
	u16 reserved1;
पूर्ण;

काष्ठा efa_admin_destroy_cq_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

/*
 * EFA AQ Get Statistics command. Extended statistics are placed in control
 * buffer poपूर्णांकed by AQ entry
 */
काष्ठा efa_admin_aq_get_stats_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;

	जोड़ अणु
		/* command specअगरic अंतरभूत data */
		u32 अंतरभूत_data_w1[3];

		काष्ठा efa_admin_ctrl_buff_info control_buffer;
	पूर्ण u;

	/* stats type as defined in क्रमागत efa_admin_get_stats_type */
	u8 type;

	/* stats scope defined in क्रमागत efa_admin_get_stats_scope */
	u8 scope;

	u16 scope_modअगरier;
पूर्ण;

काष्ठा efa_admin_basic_stats अणु
	u64 tx_bytes;

	u64 tx_pkts;

	u64 rx_bytes;

	u64 rx_pkts;

	u64 rx_drops;
पूर्ण;

काष्ठा efa_admin_messages_stats अणु
	u64 send_bytes;

	u64 send_wrs;

	u64 recv_bytes;

	u64 recv_wrs;
पूर्ण;

काष्ठा efa_admin_rdma_पढ़ो_stats अणु
	u64 पढ़ो_wrs;

	u64 पढ़ो_bytes;

	u64 पढ़ो_wr_err;

	u64 पढ़ो_resp_bytes;
पूर्ण;

काष्ठा efa_admin_acq_get_stats_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	जोड़ अणु
		काष्ठा efa_admin_basic_stats basic_stats;

		काष्ठा efa_admin_messages_stats messages_stats;

		काष्ठा efa_admin_rdma_पढ़ो_stats rdma_पढ़ो_stats;
	पूर्ण u;
पूर्ण;

काष्ठा efa_admin_get_set_feature_common_desc अणु
	/* MBZ */
	u8 reserved0;

	/* as appears in efa_admin_aq_feature_id */
	u8 feature_id;

	/* MBZ */
	u16 reserved16;
पूर्ण;

काष्ठा efa_admin_feature_device_attr_desc अणु
	/* Biपंचांगap of efa_admin_aq_feature_id */
	u64 supported_features;

	/* Biपंचांगap of supported page sizes in MR registrations */
	u64 page_size_cap;

	u32 fw_version;

	u32 admin_api_version;

	u32 device_version;

	/* Bar used क्रम SQ and RQ करोorbells */
	u16 db_bar;

	/* Indicates how many bits are used on physical address access */
	u8 phys_addr_width;

	/* Indicates how many bits are used on भव address access */
	u8 virt_addr_width;

	/*
	 * 0 : rdma_पढ़ो - If set, RDMA Read is supported on
	 *    TX queues
	 * 1 : rnr_retry - If set, RNR retry is supported on
	 *    modअगरy QP command
	 * 31:2 : reserved - MBZ
	 */
	u32 device_caps;

	/* Max RDMA transfer size in bytes */
	u32 max_rdma_size;
पूर्ण;

काष्ठा efa_admin_feature_queue_attr_desc अणु
	/* The maximum number of queue pairs supported */
	u32 max_qp;

	/* Maximum number of WQEs per Send Queue */
	u32 max_sq_depth;

	/* Maximum size of data that can be sent अंतरभूत in a Send WQE */
	u32 अंतरभूत_buf_size;

	/* Maximum number of buffer descriptors per Recv Queue */
	u32 max_rq_depth;

	/* The maximum number of completion queues supported per VF */
	u32 max_cq;

	/* Maximum number of CQEs per Completion Queue */
	u32 max_cq_depth;

	/* Number of sub-CQs to be created क्रम each CQ */
	u16 sub_cqs_per_cq;

	/* Minimum number of WQEs per SQ */
	u16 min_sq_depth;

	/* Maximum number of SGEs (buffers) allowed क्रम a single send WQE */
	u16 max_wr_send_sges;

	/* Maximum number of SGEs allowed क्रम a single recv WQE */
	u16 max_wr_recv_sges;

	/* The maximum number of memory regions supported */
	u32 max_mr;

	/* The maximum number of pages can be रेजिस्टरed */
	u32 max_mr_pages;

	/* The maximum number of protection करोमुख्यs supported */
	u32 max_pd;

	/* The maximum number of address handles supported */
	u32 max_ah;

	/* The maximum size of LLQ in bytes */
	u32 max_llq_size;

	/* Maximum number of SGEs क्रम a single RDMA पढ़ो WQE */
	u16 max_wr_rdma_sges;

	/*
	 * Maximum number of bytes that can be written to SQ between two
	 * consecutive करोorbells (in units of 64B). Driver must ensure that only
	 * complete WQEs are written to queue beक्रमe issuing a करोorbell.
	 * Examples: max_tx_batch=16 and WQE size = 64B, means up to 16 WQEs can
	 * be written to SQ between two consecutive करोorbells. max_tx_batch=11
	 * and WQE size = 128B, means up to 5 WQEs can be written to SQ between
	 * two consecutive करोorbells. Zero means unlimited.
	 */
	u16 max_tx_batch;
पूर्ण;

काष्ठा efa_admin_feature_aenq_desc अणु
	/* biपंचांगask क्रम AENQ groups the device can report */
	u32 supported_groups;

	/* biपंचांगask क्रम AENQ groups to report */
	u32 enabled_groups;
पूर्ण;

काष्ठा efa_admin_feature_network_attr_desc अणु
	/* Raw address data in network byte order */
	u8 addr[16];

	/* max packet payload size in bytes */
	u32 mtu;
पूर्ण;

/*
 * When hपूर्णांक value is 0, hपूर्णांकs capabilities are not supported or driver
 * should use its own predefined value
 */
काष्ठा efa_admin_hw_hपूर्णांकs अणु
	/* value in ms */
	u16 mmio_पढ़ो_समयout;

	/* value in ms */
	u16 driver_watchकरोg_समयout;

	/* value in ms */
	u16 admin_completion_समयout;

	/* poll पूर्णांकerval in ms */
	u16 poll_पूर्णांकerval;
पूर्ण;

काष्ठा efa_admin_get_feature_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;

	काष्ठा efa_admin_ctrl_buff_info control_buffer;

	काष्ठा efa_admin_get_set_feature_common_desc feature_common;

	u32 raw[11];
पूर्ण;

काष्ठा efa_admin_get_feature_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	जोड़ अणु
		u32 raw[14];

		काष्ठा efa_admin_feature_device_attr_desc device_attr;

		काष्ठा efa_admin_feature_aenq_desc aenq;

		काष्ठा efa_admin_feature_network_attr_desc network_attr;

		काष्ठा efa_admin_feature_queue_attr_desc queue_attr;

		काष्ठा efa_admin_hw_hपूर्णांकs hw_hपूर्णांकs;
	पूर्ण u;
पूर्ण;

काष्ठा efa_admin_set_feature_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;

	काष्ठा efa_admin_ctrl_buff_info control_buffer;

	काष्ठा efa_admin_get_set_feature_common_desc feature_common;

	जोड़ अणु
		u32 raw[11];

		/* AENQ configuration */
		काष्ठा efa_admin_feature_aenq_desc aenq;
	पूर्ण u;
पूर्ण;

काष्ठा efa_admin_set_feature_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	जोड़ अणु
		u32 raw[14];
	पूर्ण u;
पूर्ण;

काष्ठा efa_admin_alloc_pd_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;
पूर्ण;

काष्ठा efa_admin_alloc_pd_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	/* PD number */
	u16 pd;

	/* MBZ */
	u16 reserved;
पूर्ण;

काष्ठा efa_admin_dealloc_pd_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;

	/* PD number */
	u16 pd;

	/* MBZ */
	u16 reserved;
पूर्ण;

काष्ठा efa_admin_dealloc_pd_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

काष्ठा efa_admin_alloc_uar_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;
पूर्ण;

काष्ठा efa_admin_alloc_uar_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;

	/* UAR number */
	u16 uar;

	/* MBZ */
	u16 reserved;
पूर्ण;

काष्ठा efa_admin_dealloc_uar_cmd अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;

	/* UAR number */
	u16 uar;

	/* MBZ */
	u16 reserved;
पूर्ण;

काष्ठा efa_admin_dealloc_uar_resp अणु
	काष्ठा efa_admin_acq_common_desc acq_common_desc;
पूर्ण;

/* asynchronous event notअगरication groups */
क्रमागत efa_admin_aenq_group अणु
	EFA_ADMIN_FATAL_ERROR                       = 1,
	EFA_ADMIN_WARNING                           = 2,
	EFA_ADMIN_NOTIFICATION                      = 3,
	EFA_ADMIN_KEEP_ALIVE                        = 4,
	EFA_ADMIN_AENQ_GROUPS_NUM                   = 5,
पूर्ण;

काष्ठा efa_admin_mmio_req_पढ़ो_less_resp अणु
	u16 req_id;

	u16 reg_off;

	/* value is valid when poll is cleared */
	u32 reg_val;
पूर्ण;

क्रमागत efa_admin_os_type अणु
	EFA_ADMIN_OS_LINUX                          = 0,
पूर्ण;

काष्ठा efa_admin_host_info अणु
	/* OS distribution string क्रमmat */
	u8 os_dist_str[128];

	/* Defined in क्रमागत efa_admin_os_type */
	u32 os_type;

	/* Kernel version string क्रमmat */
	u8 kernel_ver_str[32];

	/* Kernel version numeric क्रमmat */
	u32 kernel_ver;

	/*
	 * 7:0 : driver_module_type
	 * 15:8 : driver_sub_minor
	 * 23:16 : driver_minor
	 * 31:24 : driver_major
	 */
	u32 driver_ver;

	/*
	 * Device's Bus, Device and Function
	 * 2:0 : function
	 * 7:3 : device
	 * 15:8 : bus
	 */
	u16 bdf;

	/*
	 * Spec version
	 * 7:0 : spec_minor
	 * 15:8 : spec_major
	 */
	u16 spec_ver;

	/*
	 * 0 : पूर्णांकree - Intree driver
	 * 1 : gdr - GPUDirect RDMA supported
	 * 31:2 : reserved2
	 */
	u32 flags;
पूर्ण;

/* create_qp_cmd */
#घोषणा EFA_ADMIN_CREATE_QP_CMD_SQ_VIRT_MASK                BIT(0)
#घोषणा EFA_ADMIN_CREATE_QP_CMD_RQ_VIRT_MASK                BIT(1)

/* modअगरy_qp_cmd */
#घोषणा EFA_ADMIN_MODIFY_QP_CMD_QP_STATE_MASK               BIT(0)
#घोषणा EFA_ADMIN_MODIFY_QP_CMD_CUR_QP_STATE_MASK           BIT(1)
#घोषणा EFA_ADMIN_MODIFY_QP_CMD_QKEY_MASK                   BIT(2)
#घोषणा EFA_ADMIN_MODIFY_QP_CMD_SQ_PSN_MASK                 BIT(3)
#घोषणा EFA_ADMIN_MODIFY_QP_CMD_SQ_DRAINED_ASYNC_NOTIFY_MASK BIT(4)
#घोषणा EFA_ADMIN_MODIFY_QP_CMD_RNR_RETRY_MASK              BIT(5)

/* reg_mr_cmd */
#घोषणा EFA_ADMIN_REG_MR_CMD_PHYS_PAGE_SIZE_SHIFT_MASK      GENMASK(4, 0)
#घोषणा EFA_ADMIN_REG_MR_CMD_MEM_ADDR_PHY_MODE_EN_MASK      BIT(7)
#घोषणा EFA_ADMIN_REG_MR_CMD_LOCAL_WRITE_ENABLE_MASK        BIT(0)
#घोषणा EFA_ADMIN_REG_MR_CMD_REMOTE_READ_ENABLE_MASK        BIT(2)

/* create_cq_cmd */
#घोषणा EFA_ADMIN_CREATE_CQ_CMD_INTERRUPT_MODE_ENABLED_MASK BIT(5)
#घोषणा EFA_ADMIN_CREATE_CQ_CMD_VIRT_MASK                   BIT(6)
#घोषणा EFA_ADMIN_CREATE_CQ_CMD_CQ_ENTRY_SIZE_WORDS_MASK    GENMASK(4, 0)

/* feature_device_attr_desc */
#घोषणा EFA_ADMIN_FEATURE_DEVICE_ATTR_DESC_RDMA_READ_MASK   BIT(0)
#घोषणा EFA_ADMIN_FEATURE_DEVICE_ATTR_DESC_RNR_RETRY_MASK   BIT(1)

/* host_info */
#घोषणा EFA_ADMIN_HOST_INFO_DRIVER_MODULE_TYPE_MASK         GENMASK(7, 0)
#घोषणा EFA_ADMIN_HOST_INFO_DRIVER_SUB_MINOR_MASK           GENMASK(15, 8)
#घोषणा EFA_ADMIN_HOST_INFO_DRIVER_MINOR_MASK               GENMASK(23, 16)
#घोषणा EFA_ADMIN_HOST_INFO_DRIVER_MAJOR_MASK               GENMASK(31, 24)
#घोषणा EFA_ADMIN_HOST_INFO_FUNCTION_MASK                   GENMASK(2, 0)
#घोषणा EFA_ADMIN_HOST_INFO_DEVICE_MASK                     GENMASK(7, 3)
#घोषणा EFA_ADMIN_HOST_INFO_BUS_MASK                        GENMASK(15, 8)
#घोषणा EFA_ADMIN_HOST_INFO_SPEC_MINOR_MASK                 GENMASK(7, 0)
#घोषणा EFA_ADMIN_HOST_INFO_SPEC_MAJOR_MASK                 GENMASK(15, 8)
#घोषणा EFA_ADMIN_HOST_INFO_INTREE_MASK                     BIT(0)
#घोषणा EFA_ADMIN_HOST_INFO_GDR_MASK                        BIT(1)

#पूर्ण_अगर /* _EFA_ADMIN_CMDS_H_ */
