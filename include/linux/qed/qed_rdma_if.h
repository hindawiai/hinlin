<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_RDMA_IF_H
#घोषणा _QED_RDMA_IF_H
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_ll2_अगर.h>
#समावेश <linux/qed/rdma_common.h>

#घोषणा QED_RDMA_MAX_CNQ_SIZE               (0xFFFF)

/* rdma पूर्णांकerface */

क्रमागत qed_roce_qp_state अणु
	QED_ROCE_QP_STATE_RESET,
	QED_ROCE_QP_STATE_INIT,
	QED_ROCE_QP_STATE_RTR,
	QED_ROCE_QP_STATE_RTS,
	QED_ROCE_QP_STATE_SQD,
	QED_ROCE_QP_STATE_ERR,
	QED_ROCE_QP_STATE_SQE
पूर्ण;

क्रमागत qed_rdma_qp_type अणु
	QED_RDMA_QP_TYPE_RC,
	QED_RDMA_QP_TYPE_XRC_INI,
	QED_RDMA_QP_TYPE_XRC_TGT,
	QED_RDMA_QP_TYPE_INVAL = 0xffff,
पूर्ण;

क्रमागत qed_rdma_tid_type अणु
	QED_RDMA_TID_REGISTERED_MR,
	QED_RDMA_TID_FMR,
	QED_RDMA_TID_MW
पूर्ण;

काष्ठा qed_rdma_events अणु
	व्योम *context;
	व्योम (*affiliated_event)(व्योम *context, u8 fw_event_code,
				 व्योम *fw_handle);
	व्योम (*unaffiliated_event)(व्योम *context, u8 event_code);
पूर्ण;

काष्ठा qed_rdma_device अणु
	u32 venकरोr_id;
	u32 venकरोr_part_id;
	u32 hw_ver;
	u64 fw_ver;

	u64 node_guid;
	u64 sys_image_guid;

	u8 max_cnq;
	u8 max_sge;
	u8 max_srq_sge;
	u16 max_अंतरभूत;
	u32 max_wqe;
	u32 max_srq_wqe;
	u8 max_qp_resp_rd_atomic_resc;
	u8 max_qp_req_rd_atomic_resc;
	u64 max_dev_resp_rd_atomic_resc;
	u32 max_cq;
	u32 max_qp;
	u32 max_srq;
	u32 max_mr;
	u64 max_mr_size;
	u32 max_cqe;
	u32 max_mw;
	u32 max_mr_mw_fmr_pbl;
	u64 max_mr_mw_fmr_size;
	u32 max_pd;
	u32 max_ah;
	u8 max_pkey;
	u16 max_srq_wr;
	u8 max_stats_queues;
	u32 dev_caps;

	/* Abilty to support RNR-NAK generation */

#घोषणा QED_RDMA_DEV_CAP_RNR_NAK_MASK                           0x1
#घोषणा QED_RDMA_DEV_CAP_RNR_NAK_SHIFT                  0
	/* Abilty to support shutकरोwn port */
#घोषणा QED_RDMA_DEV_CAP_SHUTDOWN_PORT_MASK                     0x1
#घोषणा QED_RDMA_DEV_CAP_SHUTDOWN_PORT_SHIFT                    1
	/* Abilty to support port active event */
#घोषणा QED_RDMA_DEV_CAP_PORT_ACTIVE_EVENT_MASK         0x1
#घोषणा QED_RDMA_DEV_CAP_PORT_ACTIVE_EVENT_SHIFT                2
	/* Abilty to support port change event */
#घोषणा QED_RDMA_DEV_CAP_PORT_CHANGE_EVENT_MASK         0x1
#घोषणा QED_RDMA_DEV_CAP_PORT_CHANGE_EVENT_SHIFT                3
	/* Abilty to support प्रणाली image GUID */
#घोषणा QED_RDMA_DEV_CAP_SYS_IMAGE_MASK                 0x1
#घोषणा QED_RDMA_DEV_CAP_SYS_IMAGE_SHIFT                        4
	/* Abilty to support bad P_Key counter support */
#घोषणा QED_RDMA_DEV_CAP_BAD_PKEY_CNT_MASK                      0x1
#घोषणा QED_RDMA_DEV_CAP_BAD_PKEY_CNT_SHIFT                     5
	/* Abilty to support atomic operations */
#घोषणा QED_RDMA_DEV_CAP_ATOMIC_OP_MASK                 0x1
#घोषणा QED_RDMA_DEV_CAP_ATOMIC_OP_SHIFT                        6
#घोषणा QED_RDMA_DEV_CAP_RESIZE_CQ_MASK                 0x1
#घोषणा QED_RDMA_DEV_CAP_RESIZE_CQ_SHIFT                        7
	/* Abilty to support modअगरying the maximum number of
	 * outstanding work requests per QP
	 */
#घोषणा QED_RDMA_DEV_CAP_RESIZE_MAX_WR_MASK                     0x1
#घोषणा QED_RDMA_DEV_CAP_RESIZE_MAX_WR_SHIFT                    8
	/* Abilty to support स्वतःmatic path migration */
#घोषणा QED_RDMA_DEV_CAP_AUTO_PATH_MIG_MASK                     0x1
#घोषणा QED_RDMA_DEV_CAP_AUTO_PATH_MIG_SHIFT                    9
	/* Abilty to support the base memory management extensions */
#घोषणा QED_RDMA_DEV_CAP_BASE_MEMORY_EXT_MASK                   0x1
#घोषणा QED_RDMA_DEV_CAP_BASE_MEMORY_EXT_SHIFT          10
#घोषणा QED_RDMA_DEV_CAP_BASE_QUEUE_EXT_MASK                    0x1
#घोषणा QED_RDMA_DEV_CAP_BASE_QUEUE_EXT_SHIFT                   11
	/* Abilty to support multipile page sizes per memory region */
#घोषणा QED_RDMA_DEV_CAP_MULTI_PAGE_PER_MR_EXT_MASK             0x1
#घोषणा QED_RDMA_DEV_CAP_MULTI_PAGE_PER_MR_EXT_SHIFT            12
	/* Abilty to support block list physical buffer list */
#घोषणा QED_RDMA_DEV_CAP_BLOCK_MODE_MASK                        0x1
#घोषणा QED_RDMA_DEV_CAP_BLOCK_MODE_SHIFT                       13
	/* Abilty to support zero based भव addresses */
#घोषणा QED_RDMA_DEV_CAP_ZBVA_MASK                              0x1
#घोषणा QED_RDMA_DEV_CAP_ZBVA_SHIFT                             14
	/* Abilty to support local invalidate fencing */
#घोषणा QED_RDMA_DEV_CAP_LOCAL_INV_FENCE_MASK                   0x1
#घोषणा QED_RDMA_DEV_CAP_LOCAL_INV_FENCE_SHIFT          15
	/* Abilty to support Loopback on QP */
#घोषणा QED_RDMA_DEV_CAP_LB_INDICATOR_MASK                      0x1
#घोषणा QED_RDMA_DEV_CAP_LB_INDICATOR_SHIFT                     16
	u64 page_size_caps;
	u8 dev_ack_delay;
	u32 reserved_lkey;
	u32 bad_pkey_counter;
	काष्ठा qed_rdma_events events;
पूर्ण;

क्रमागत qed_port_state अणु
	QED_RDMA_PORT_UP,
	QED_RDMA_PORT_DOWN,
पूर्ण;

क्रमागत qed_roce_capability अणु
	QED_ROCE_V1 = 1 << 0,
	QED_ROCE_V2 = 1 << 1,
पूर्ण;

काष्ठा qed_rdma_port अणु
	क्रमागत qed_port_state port_state;
	पूर्णांक link_speed;
	u64 max_msg_size;
	u8 source_gid_table_len;
	व्योम *source_gid_table_ptr;
	u8 pkey_table_len;
	व्योम *pkey_table_ptr;
	u32 pkey_bad_counter;
	क्रमागत qed_roce_capability capability;
पूर्ण;

काष्ठा qed_rdma_cnq_params अणु
	u8 num_pbl_pages;
	u64 pbl_ptr;
पूर्ण;

/* The CQ Mode affects the CQ करोorbell transaction size.
 * 64/32 bit machines should configure to 32/16 bits respectively.
 */
क्रमागत qed_rdma_cq_mode अणु
	QED_RDMA_CQ_MODE_16_BITS,
	QED_RDMA_CQ_MODE_32_BITS,
पूर्ण;

काष्ठा qed_roce_dcqcn_params अणु
	u8 notअगरication_poपूर्णांक;
	u8 reaction_poपूर्णांक;

	/* fields क्रम notअगरication poपूर्णांक */
	u32 cnp_send_समयout;

	/* fields क्रम reaction poपूर्णांक */
	u32 rl_bc_rate;
	u16 rl_max_rate;
	u16 rl_r_ai;
	u16 rl_r_hai;
	u16 dcqcn_g;
	u32 dcqcn_k_us;
	u32 dcqcn_समयout_us;
पूर्ण;

काष्ठा qed_rdma_start_in_params अणु
	काष्ठा qed_rdma_events *events;
	काष्ठा qed_rdma_cnq_params cnq_pbl_list[128];
	u8 desired_cnq;
	क्रमागत qed_rdma_cq_mode cq_mode;
	काष्ठा qed_roce_dcqcn_params dcqcn_params;
	u16 max_mtu;
	u8 mac_addr[ETH_ALEN];
	u8 iwarp_flags;
पूर्ण;

काष्ठा qed_rdma_add_user_out_params अणु
	u16 dpi;
	व्योम __iomem *dpi_addr;
	u64 dpi_phys_addr;
	u32 dpi_size;
	u16 wid_count;
पूर्ण;

क्रमागत roce_mode अणु
	ROCE_V1,
	ROCE_V2_IPV4,
	ROCE_V2_IPV6,
	MAX_ROCE_MODE
पूर्ण;

जोड़ qed_gid अणु
	u8 bytes[16];
	u16 words[8];
	u32 dwords[4];
	u64 qwords[2];
	u32 ipv4_addr;
पूर्ण;

काष्ठा qed_rdma_रेजिस्टर_tid_in_params अणु
	u32 itid;
	क्रमागत qed_rdma_tid_type tid_type;
	u8 key;
	u16 pd;
	bool local_पढ़ो;
	bool local_ग_लिखो;
	bool remote_पढ़ो;
	bool remote_ग_लिखो;
	bool remote_atomic;
	bool mw_bind;
	u64 pbl_ptr;
	bool pbl_two_level;
	u8 pbl_page_size_log;
	u8 page_size_log;
	u64 length;
	u64 vaddr;
	bool phy_mr;
	bool dma_mr;

	bool dअगर_enabled;
	u64 dअगर_error_addr;
पूर्ण;

काष्ठा qed_rdma_create_cq_in_params अणु
	u32 cq_handle_lo;
	u32 cq_handle_hi;
	u32 cq_size;
	u16 dpi;
	bool pbl_two_level;
	u64 pbl_ptr;
	u16 pbl_num_pages;
	u8 pbl_page_size_log;
	u8 cnq_id;
	u16 पूर्णांक_समयout;
पूर्ण;

काष्ठा qed_rdma_create_srq_in_params अणु
	u64 pbl_base_addr;
	u64 prod_pair_addr;
	u16 num_pages;
	u16 pd_id;
	u16 page_size;

	/* XRC related only */
	bool reserved_key_en;
	bool is_xrc;
	u32 cq_cid;
	u16 xrcd_id;
पूर्ण;

काष्ठा qed_rdma_destroy_cq_in_params अणु
	u16 icid;
पूर्ण;

काष्ठा qed_rdma_destroy_cq_out_params अणु
	u16 num_cq_notअगर;
पूर्ण;

काष्ठा qed_rdma_create_qp_in_params अणु
	u32 qp_handle_lo;
	u32 qp_handle_hi;
	u32 qp_handle_async_lo;
	u32 qp_handle_async_hi;
	bool use_srq;
	bool संकेत_all;
	bool fmr_and_reserved_lkey;
	u16 pd;
	u16 dpi;
	u16 sq_cq_id;
	u16 sq_num_pages;
	u64 sq_pbl_ptr;
	u8 max_sq_sges;
	u16 rq_cq_id;
	u16 rq_num_pages;
	u64 rq_pbl_ptr;
	u16 srq_id;
	u16 xrcd_id;
	u8 stats_queue;
	क्रमागत qed_rdma_qp_type qp_type;
	u8 flags;
#घोषणा QED_ROCE_EDPM_MODE_MASK      0x1
#घोषणा QED_ROCE_EDPM_MODE_SHIFT     0
पूर्ण;

काष्ठा qed_rdma_create_qp_out_params अणु
	u32 qp_id;
	u16 icid;
	व्योम *rq_pbl_virt;
	dma_addr_t rq_pbl_phys;
	व्योम *sq_pbl_virt;
	dma_addr_t sq_pbl_phys;
पूर्ण;

काष्ठा qed_rdma_modअगरy_qp_in_params अणु
	u32 modअगरy_flags;
#घोषणा QED_RDMA_MODIFY_QP_VALID_NEW_STATE_MASK               0x1
#घोषणा QED_RDMA_MODIFY_QP_VALID_NEW_STATE_SHIFT              0
#घोषणा QED_ROCE_MODIFY_QP_VALID_PKEY_MASK                    0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_PKEY_SHIFT                   1
#घोषणा QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN_MASK             0x1
#घोषणा QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN_SHIFT            2
#घोषणा QED_ROCE_MODIFY_QP_VALID_DEST_QP_MASK                 0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_DEST_QP_SHIFT                3
#घोषणा QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR_MASK          0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR_SHIFT         4
#घोषणा QED_ROCE_MODIFY_QP_VALID_RQ_PSN_MASK                  0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_RQ_PSN_SHIFT                 5
#घोषणा QED_ROCE_MODIFY_QP_VALID_SQ_PSN_MASK                  0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_SQ_PSN_SHIFT                 6
#घोषणा QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ_MASK       0x1
#घोषणा QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ_SHIFT      7
#घोषणा QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP_MASK      0x1
#घोषणा QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP_SHIFT     8
#घोषणा QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT_MASK             0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT_SHIFT            9
#घोषणा QED_ROCE_MODIFY_QP_VALID_RETRY_CNT_MASK               0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_RETRY_CNT_SHIFT              10
#घोषणा QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT_MASK           0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT_SHIFT          11
#घोषणा QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER_MASK       0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER_SHIFT      12
#घोषणा QED_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN_MASK     0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN_SHIFT    13
#घोषणा QED_ROCE_MODIFY_QP_VALID_ROCE_MODE_MASK               0x1
#घोषणा QED_ROCE_MODIFY_QP_VALID_ROCE_MODE_SHIFT              14

	क्रमागत qed_roce_qp_state new_state;
	u16 pkey;
	bool incoming_rdma_पढ़ो_en;
	bool incoming_rdma_ग_लिखो_en;
	bool incoming_atomic_en;
	bool e2e_flow_control_en;
	u32 dest_qp;
	bool lb_indication;
	u16 mtu;
	u8 traffic_class_tos;
	u8 hop_limit_ttl;
	u32 flow_label;
	जोड़ qed_gid sgid;
	जोड़ qed_gid dgid;
	u16 udp_src_port;

	u16 vlan_id;

	u32 rq_psn;
	u32 sq_psn;
	u8 max_rd_atomic_resp;
	u8 max_rd_atomic_req;
	u32 ack_समयout;
	u8 retry_cnt;
	u8 rnr_retry_cnt;
	u8 min_rnr_nak_समयr;
	bool sqd_async;
	u8 remote_mac_addr[6];
	u8 local_mac_addr[6];
	bool use_local_mac;
	क्रमागत roce_mode roce_mode;
पूर्ण;

काष्ठा qed_rdma_query_qp_out_params अणु
	क्रमागत qed_roce_qp_state state;
	u32 rq_psn;
	u32 sq_psn;
	bool draining;
	u16 mtu;
	u32 dest_qp;
	bool incoming_rdma_पढ़ो_en;
	bool incoming_rdma_ग_लिखो_en;
	bool incoming_atomic_en;
	bool e2e_flow_control_en;
	जोड़ qed_gid sgid;
	जोड़ qed_gid dgid;
	u32 flow_label;
	u8 hop_limit_ttl;
	u8 traffic_class_tos;
	u32 समयout;
	u8 rnr_retry;
	u8 retry_cnt;
	u8 min_rnr_nak_समयr;
	u16 pkey_index;
	u8 max_rd_atomic;
	u8 max_dest_rd_atomic;
	bool sqd_async;
पूर्ण;

काष्ठा qed_rdma_create_srq_out_params अणु
	u16 srq_id;
पूर्ण;

काष्ठा qed_rdma_destroy_srq_in_params अणु
	u16 srq_id;
	bool is_xrc;
पूर्ण;

काष्ठा qed_rdma_modअगरy_srq_in_params अणु
	u32 wqe_limit;
	u16 srq_id;
	bool is_xrc;
पूर्ण;

काष्ठा qed_rdma_stats_out_params अणु
	u64 sent_bytes;
	u64 sent_pkts;
	u64 rcv_bytes;
	u64 rcv_pkts;
पूर्ण;

काष्ठा qed_rdma_counters_out_params अणु
	u64 pd_count;
	u64 max_pd;
	u64 dpi_count;
	u64 max_dpi;
	u64 cq_count;
	u64 max_cq;
	u64 qp_count;
	u64 max_qp;
	u64 tid_count;
	u64 max_tid;
पूर्ण;

#घोषणा QED_ROCE_TX_HEAD_FAILURE        (1)
#घोषणा QED_ROCE_TX_FRAG_FAILURE        (2)

क्रमागत qed_iwarp_event_type अणु
	QED_IWARP_EVENT_MPA_REQUEST,	  /* Passive side request received */
	QED_IWARP_EVENT_PASSIVE_COMPLETE, /* ack on mpa response */
	QED_IWARP_EVENT_ACTIVE_COMPLETE,  /* Active side reply received */
	QED_IWARP_EVENT_DISCONNECT,
	QED_IWARP_EVENT_CLOSE,
	QED_IWARP_EVENT_IRQ_FULL,
	QED_IWARP_EVENT_RQ_EMPTY,
	QED_IWARP_EVENT_LLP_TIMEOUT,
	QED_IWARP_EVENT_REMOTE_PROTECTION_ERROR,
	QED_IWARP_EVENT_CQ_OVERFLOW,
	QED_IWARP_EVENT_QP_CATASTROPHIC,
	QED_IWARP_EVENT_ACTIVE_MPA_REPLY,
	QED_IWARP_EVENT_LOCAL_ACCESS_ERROR,
	QED_IWARP_EVENT_REMOTE_OPERATION_ERROR,
	QED_IWARP_EVENT_TERMINATE_RECEIVED,
	QED_IWARP_EVENT_SRQ_LIMIT,
	QED_IWARP_EVENT_SRQ_EMPTY,
पूर्ण;

क्रमागत qed_tcp_ip_version अणु
	QED_TCP_IPV4,
	QED_TCP_IPV6,
पूर्ण;

काष्ठा qed_iwarp_cm_info अणु
	क्रमागत qed_tcp_ip_version ip_version;
	u32 remote_ip[4];
	u32 local_ip[4];
	u16 remote_port;
	u16 local_port;
	u16 vlan;
	u8 ord;
	u8 ird;
	u16 निजी_data_len;
	स्थिर व्योम *निजी_data;
पूर्ण;

काष्ठा qed_iwarp_cm_event_params अणु
	क्रमागत qed_iwarp_event_type event;
	स्थिर काष्ठा qed_iwarp_cm_info *cm_info;
	व्योम *ep_context;	/* To be passed to accept call */
	पूर्णांक status;
पूर्ण;

प्रकार पूर्णांक (*iwarp_event_handler) (व्योम *context,
				    काष्ठा qed_iwarp_cm_event_params *event);

काष्ठा qed_iwarp_connect_in अणु
	iwarp_event_handler event_cb;
	व्योम *cb_context;
	काष्ठा qed_rdma_qp *qp;
	काष्ठा qed_iwarp_cm_info cm_info;
	u16 mss;
	u8 remote_mac_addr[ETH_ALEN];
	u8 local_mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा qed_iwarp_connect_out अणु
	व्योम *ep_context;
पूर्ण;

काष्ठा qed_iwarp_listen_in अणु
	iwarp_event_handler event_cb;
	व्योम *cb_context;	/* passed to event_cb */
	u32 max_backlog;
	क्रमागत qed_tcp_ip_version ip_version;
	u32 ip_addr[4];
	u16 port;
	u16 vlan;
पूर्ण;

काष्ठा qed_iwarp_listen_out अणु
	व्योम *handle;
पूर्ण;

काष्ठा qed_iwarp_accept_in अणु
	व्योम *ep_context;
	व्योम *cb_context;
	काष्ठा qed_rdma_qp *qp;
	स्थिर व्योम *निजी_data;
	u16 निजी_data_len;
	u8 ord;
	u8 ird;
पूर्ण;

काष्ठा qed_iwarp_reject_in अणु
	व्योम *ep_context;
	व्योम *cb_context;
	स्थिर व्योम *निजी_data;
	u16 निजी_data_len;
पूर्ण;

काष्ठा qed_iwarp_send_rtr_in अणु
	व्योम *ep_context;
पूर्ण;

काष्ठा qed_roce_ll2_header अणु
	व्योम *vaddr;
	dma_addr_t baddr;
	माप_प्रकार len;
पूर्ण;

काष्ठा qed_roce_ll2_buffer अणु
	dma_addr_t baddr;
	माप_प्रकार len;
पूर्ण;

काष्ठा qed_roce_ll2_packet अणु
	काष्ठा qed_roce_ll2_header header;
	पूर्णांक n_seg;
	काष्ठा qed_roce_ll2_buffer payload[RDMA_MAX_SGE_PER_SQ_WQE];
	पूर्णांक roce_mode;
	क्रमागत qed_ll2_tx_dest tx_dest;
पूर्ण;

क्रमागत qed_rdma_type अणु
	QED_RDMA_TYPE_ROCE,
	QED_RDMA_TYPE_IWARP
पूर्ण;

काष्ठा qed_dev_rdma_info अणु
	काष्ठा qed_dev_info common;
	क्रमागत qed_rdma_type rdma_type;
	u8 user_dpm_enabled;
पूर्ण;

काष्ठा qed_rdma_ops अणु
	स्थिर काष्ठा qed_common_ops *common;

	पूर्णांक (*fill_dev_info)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_dev_rdma_info *info);
	व्योम *(*rdma_get_rdma_ctx)(काष्ठा qed_dev *cdev);

	पूर्णांक (*rdma_init)(काष्ठा qed_dev *dev,
			 काष्ठा qed_rdma_start_in_params *iparams);

	पूर्णांक (*rdma_add_user)(व्योम *rdma_cxt,
			     काष्ठा qed_rdma_add_user_out_params *oparams);

	व्योम (*rdma_हटाओ_user)(व्योम *rdma_cxt, u16 dpi);
	पूर्णांक (*rdma_stop)(व्योम *rdma_cxt);
	काष्ठा qed_rdma_device* (*rdma_query_device)(व्योम *rdma_cxt);
	काष्ठा qed_rdma_port* (*rdma_query_port)(व्योम *rdma_cxt);
	पूर्णांक (*rdma_get_start_sb)(काष्ठा qed_dev *cdev);
	पूर्णांक (*rdma_get_min_cnq_msix)(काष्ठा qed_dev *cdev);
	व्योम (*rdma_cnq_prod_update)(व्योम *rdma_cxt, u8 cnq_index, u16 prod);
	पूर्णांक (*rdma_get_rdma_पूर्णांक)(काष्ठा qed_dev *cdev,
				 काष्ठा qed_पूर्णांक_info *info);
	पूर्णांक (*rdma_set_rdma_पूर्णांक)(काष्ठा qed_dev *cdev, u16 cnt);
	पूर्णांक (*rdma_alloc_pd)(व्योम *rdma_cxt, u16 *pd);
	व्योम (*rdma_dealloc_pd)(व्योम *rdma_cxt, u16 pd);
	पूर्णांक (*rdma_alloc_xrcd)(व्योम *rdma_cxt, u16 *xrcd);
	व्योम (*rdma_dealloc_xrcd)(व्योम *rdma_cxt, u16 xrcd);
	पूर्णांक (*rdma_create_cq)(व्योम *rdma_cxt,
			      काष्ठा qed_rdma_create_cq_in_params *params,
			      u16 *icid);
	पूर्णांक (*rdma_destroy_cq)(व्योम *rdma_cxt,
			       काष्ठा qed_rdma_destroy_cq_in_params *iparams,
			       काष्ठा qed_rdma_destroy_cq_out_params *oparams);
	काष्ठा qed_rdma_qp *
	(*rdma_create_qp)(व्योम *rdma_cxt,
			  काष्ठा qed_rdma_create_qp_in_params *iparams,
			  काष्ठा qed_rdma_create_qp_out_params *oparams);

	पूर्णांक (*rdma_modअगरy_qp)(व्योम *roce_cxt, काष्ठा qed_rdma_qp *qp,
			      काष्ठा qed_rdma_modअगरy_qp_in_params *iparams);

	पूर्णांक (*rdma_query_qp)(व्योम *rdma_cxt, काष्ठा qed_rdma_qp *qp,
			     काष्ठा qed_rdma_query_qp_out_params *oparams);
	पूर्णांक (*rdma_destroy_qp)(व्योम *rdma_cxt, काष्ठा qed_rdma_qp *qp);

	पूर्णांक
	(*rdma_रेजिस्टर_tid)(व्योम *rdma_cxt,
			     काष्ठा qed_rdma_रेजिस्टर_tid_in_params *iparams);

	पूर्णांक (*rdma_deरेजिस्टर_tid)(व्योम *rdma_cxt, u32 itid);
	पूर्णांक (*rdma_alloc_tid)(व्योम *rdma_cxt, u32 *itid);
	व्योम (*rdma_मुक्त_tid)(व्योम *rdma_cxt, u32 itid);

	पूर्णांक (*rdma_create_srq)(व्योम *rdma_cxt,
			       काष्ठा qed_rdma_create_srq_in_params *iparams,
			       काष्ठा qed_rdma_create_srq_out_params *oparams);
	पूर्णांक (*rdma_destroy_srq)(व्योम *rdma_cxt,
				काष्ठा qed_rdma_destroy_srq_in_params *iparams);
	पूर्णांक (*rdma_modअगरy_srq)(व्योम *rdma_cxt,
			       काष्ठा qed_rdma_modअगरy_srq_in_params *iparams);

	पूर्णांक (*ll2_acquire_connection)(व्योम *rdma_cxt,
				      काष्ठा qed_ll2_acquire_data *data);

	पूर्णांक (*ll2_establish_connection)(व्योम *rdma_cxt, u8 connection_handle);
	पूर्णांक (*ll2_terminate_connection)(व्योम *rdma_cxt, u8 connection_handle);
	व्योम (*ll2_release_connection)(व्योम *rdma_cxt, u8 connection_handle);

	पूर्णांक (*ll2_prepare_tx_packet)(व्योम *rdma_cxt,
				     u8 connection_handle,
				     काष्ठा qed_ll2_tx_pkt_info *pkt,
				     bool notअगरy_fw);

	पूर्णांक (*ll2_set_fragment_of_tx_packet)(व्योम *rdma_cxt,
					     u8 connection_handle,
					     dma_addr_t addr,
					     u16 nbytes);
	पूर्णांक (*ll2_post_rx_buffer)(व्योम *rdma_cxt, u8 connection_handle,
				  dma_addr_t addr, u16 buf_len, व्योम *cookie,
				  u8 notअगरy_fw);
	पूर्णांक (*ll2_get_stats)(व्योम *rdma_cxt,
			     u8 connection_handle,
			     काष्ठा qed_ll2_stats *p_stats);
	पूर्णांक (*ll2_set_mac_filter)(काष्ठा qed_dev *cdev,
				  u8 *old_mac_address, u8 *new_mac_address);

	पूर्णांक (*iwarp_set_engine_affin)(काष्ठा qed_dev *cdev, bool b_reset);

	पूर्णांक (*iwarp_connect)(व्योम *rdma_cxt,
			     काष्ठा qed_iwarp_connect_in *iparams,
			     काष्ठा qed_iwarp_connect_out *oparams);

	पूर्णांक (*iwarp_create_listen)(व्योम *rdma_cxt,
				   काष्ठा qed_iwarp_listen_in *iparams,
				   काष्ठा qed_iwarp_listen_out *oparams);

	पूर्णांक (*iwarp_accept)(व्योम *rdma_cxt,
			    काष्ठा qed_iwarp_accept_in *iparams);

	पूर्णांक (*iwarp_reject)(व्योम *rdma_cxt,
			    काष्ठा qed_iwarp_reject_in *iparams);

	पूर्णांक (*iwarp_destroy_listen)(व्योम *rdma_cxt, व्योम *handle);

	पूर्णांक (*iwarp_send_rtr)(व्योम *rdma_cxt,
			      काष्ठा qed_iwarp_send_rtr_in *iparams);
पूर्ण;

स्थिर काष्ठा qed_rdma_ops *qed_get_rdma_ops(व्योम);

#पूर्ण_अगर
