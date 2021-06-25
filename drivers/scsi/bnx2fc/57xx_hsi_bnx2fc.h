<शैली गुरु>
/* 57xx_hsi_bnx2fc.h: QLogic Linux FCoE offload driver.
 * Handles operations such as session offload/upload etc, and manages
 * session resources such as connection id and qp resources.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */

#अगर_अघोषित __57XX_FCOE_HSI_LINUX_LE__
#घोषणा __57XX_FCOE_HSI_LINUX_LE__

/*
 * common data क्रम all protocols
 */
काष्ठा b577xx_करोorbell_hdr अणु
	u8 header;
#घोषणा B577XX_DOORBELL_HDR_RX (0x1<<0)
#घोषणा B577XX_DOORBELL_HDR_RX_SHIFT 0
#घोषणा B577XX_DOORBELL_HDR_DB_TYPE (0x1<<1)
#घोषणा B577XX_DOORBELL_HDR_DB_TYPE_SHIFT 1
#घोषणा B577XX_DOORBELL_HDR_DPM_SIZE (0x3<<2)
#घोषणा B577XX_DOORBELL_HDR_DPM_SIZE_SHIFT 2
#घोषणा B577XX_DOORBELL_HDR_CONN_TYPE (0xF<<4)
#घोषणा B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT 4
पूर्ण;

/*
 * करोorbell message sent to the chip
 */
काष्ठा b577xx_करोorbell अणु
#अगर defined(__BIG_ENDIAN)
	u16 zero_fill2;
	u8 zero_fill1;
	काष्ठा b577xx_करोorbell_hdr header;
#या_अगर defined(__LITTLE_ENDIAN)
	काष्ठा b577xx_करोorbell_hdr header;
	u8 zero_fill1;
	u16 zero_fill2;
#पूर्ण_अगर
पूर्ण;



/*
 * करोorbell message sent to the chip
 */
काष्ठा b577xx_करोorbell_set_prod अणु
#अगर defined(__BIG_ENDIAN)
	u16 prod;
	u8 zero_fill1;
	काष्ठा b577xx_करोorbell_hdr header;
#या_अगर defined(__LITTLE_ENDIAN)
	काष्ठा b577xx_करोorbell_hdr header;
	u8 zero_fill1;
	u16 prod;
#पूर्ण_अगर
पूर्ण;


काष्ठा regpair अणु
	__le32 lo;
	__le32 hi;
पूर्ण;


/*
 * ABTS info $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_abts_info अणु
	__le16 पातed_task_id;
	__le16 reserved0;
	__le32 reserved1;
पूर्ण;


/*
 * Fixed size काष्ठाure in order to plant it in Union काष्ठाure
 * $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_abts_rsp_जोड़ अणु
	u8 r_ctl;
	u8 rsrv[3];
	__le32 abts_rsp_payload[7];
पूर्ण;


/*
 * 4 regs size $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_bd_ctx अणु
	__le32 buf_addr_hi;
	__le32 buf_addr_lo;
	__le16 buf_len;
	__le16 rsrv0;
	__le16 flags;
	__le16 rsrv1;
पूर्ण;


/*
 * FCoE cached sges context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_cached_sge_ctx अणु
	काष्ठा regpair cur_buf_addr;
	__le16 cur_buf_rem;
	__le16 second_buf_rem;
	काष्ठा regpair second_buf_addr;
पूर्ण;


/*
 * Cleanup info $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_cleanup_info अणु
	__le16 cleaned_task_id;
	__le16 rolled_tx_seq_cnt;
	__le32 rolled_tx_data_offset;
पूर्ण;


/*
 * Fcp RSP flags $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fcp_rsp_flags अणु
	u8 flags;
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID (0x1<<0)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID_SHIFT 0
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID (0x1<<1)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID_SHIFT 1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER (0x1<<2)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER_SHIFT 2
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER (0x1<<3)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER_SHIFT 3
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_CONF_REQ (0x1<<4)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_CONF_REQ_SHIFT 4
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_BIDI_FLAGS (0x7<<5)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_BIDI_FLAGS_SHIFT 5
पूर्ण;

/*
 * Fcp RSP payload $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fcp_rsp_payload अणु
	काष्ठा regpair reserved0;
	__le32 fcp_resid;
	u8 scsi_status_code;
	काष्ठा fcoe_fcp_rsp_flags fcp_flags;
	__le16 retry_delay_समयr;
	__le32 fcp_rsp_len;
	__le32 fcp_sns_len;
पूर्ण;

/*
 * Fixed size काष्ठाure in order to plant it in Union काष्ठाure
 * $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fcp_rsp_जोड़ अणु
	काष्ठा fcoe_fcp_rsp_payload payload;
	काष्ठा regpair reserved0;
पूर्ण;

/*
 * FC header $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fc_hdr अणु
	u8 s_id[3];
	u8 cs_ctl;
	u8 d_id[3];
	u8 r_ctl;
	__le16 seq_cnt;
	u8 df_ctl;
	u8 seq_id;
	u8 f_ctl[3];
	u8 type;
	__le32 parameters;
	__le16 rx_id;
	__le16 ox_id;
पूर्ण;

/*
 * FC header जोड़ $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_mp_rsp_जोड़ अणु
	काष्ठा fcoe_fc_hdr fc_hdr;
	__le32 mp_payload_len;
	__le32 rsrv;
पूर्ण;

/*
 * Completion inक्रमmation $$KEEP_ENDIANNESS$$
 */
जोड़ fcoe_comp_flow_info अणु
	काष्ठा fcoe_fcp_rsp_जोड़ fcp_rsp;
	काष्ठा fcoe_abts_rsp_जोड़ abts_rsp;
	काष्ठा fcoe_mp_rsp_जोड़ mp_rsp;
	__le32 opaque[8];
पूर्ण;


/*
 * External ABTS info $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_ext_abts_info अणु
	__le32 rsrv0[6];
	काष्ठा fcoe_abts_info ctx;
पूर्ण;


/*
 * External cleanup info $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_ext_cleanup_info अणु
	__le32 rsrv0[6];
	काष्ठा fcoe_cleanup_info ctx;
पूर्ण;


/*
 * Fcoe FW Tx sequence context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fw_tx_seq_ctx अणु
	__le32 data_offset;
	__le16 seq_cnt;
	__le16 rsrv0;
पूर्ण;

/*
 * Fcoe बाह्यal FW Tx sequence context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_ext_fw_tx_seq_ctx अणु
	__le32 rsrv0[6];
	काष्ठा fcoe_fw_tx_seq_ctx ctx;
पूर्ण;


/*
 * FCoE multiple sges context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_mul_sges_ctx अणु
	काष्ठा regpair cur_sge_addr;
	__le16 cur_sge_off;
	u8 cur_sge_idx;
	u8 sgl_size;
पूर्ण;

/*
 * FCoE बाह्यal multiple sges context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_ext_mul_sges_ctx अणु
	काष्ठा fcoe_mul_sges_ctx mul_sgl;
	काष्ठा regpair rsrv0;
पूर्ण;


/*
 * FCP CMD payload $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fcp_cmd_payload अणु
	__le32 opaque[8];
पूर्ण;





/*
 * Fcp xfr rdy payload $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fcp_xfr_rdy_payload अणु
	__le32 burst_len;
	__le32 data_ro;
पूर्ण;


/*
 * FC frame $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_fc_frame अणु
	काष्ठा fcoe_fc_hdr fc_hdr;
	__le32 reserved0[2];
पूर्ण;




/*
 * FCoE KCQ CQE parameters $$KEEP_ENDIANNESS$$
 */
जोड़ fcoe_kcqe_params अणु
	__le32 reserved0[4];
पूर्ण;

/*
 * FCoE KCQ CQE $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kcqe अणु
	__le32 fcoe_conn_id;
	__le32 completion_status;
	__le32 fcoe_conn_context_id;
	जोड़ fcoe_kcqe_params params;
	__le16 qe_self_seq;
	u8 op_code;
	u8 flags;
#घोषणा FCOE_KCQE_RESERVED0 (0x7<<0)
#घोषणा FCOE_KCQE_RESERVED0_SHIFT 0
#घोषणा FCOE_KCQE_RAMROD_COMPLETION (0x1<<3)
#घोषणा FCOE_KCQE_RAMROD_COMPLETION_SHIFT 3
#घोषणा FCOE_KCQE_LAYER_CODE (0x7<<4)
#घोषणा FCOE_KCQE_LAYER_CODE_SHIFT 4
#घोषणा FCOE_KCQE_LINKED_WITH_NEXT (0x1<<7)
#घोषणा FCOE_KCQE_LINKED_WITH_NEXT_SHIFT 7
पूर्ण;



/*
 * FCoE KWQE header $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_header अणु
	u8 op_code;
	u8 flags;
#घोषणा FCOE_KWQE_HEADER_RESERVED0 (0xF<<0)
#घोषणा FCOE_KWQE_HEADER_RESERVED0_SHIFT 0
#घोषणा FCOE_KWQE_HEADER_LAYER_CODE (0x7<<4)
#घोषणा FCOE_KWQE_HEADER_LAYER_CODE_SHIFT 4
#घोषणा FCOE_KWQE_HEADER_RESERVED1 (0x1<<7)
#घोषणा FCOE_KWQE_HEADER_RESERVED1_SHIFT 7
पूर्ण;

/*
 * FCoE firmware init request 1 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_init1 अणु
	__le16 num_tasks;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 task_list_pbl_addr_lo;
	__le32 task_list_pbl_addr_hi;
	__le32 dummy_buffer_addr_lo;
	__le32 dummy_buffer_addr_hi;
	__le16 sq_num_wqes;
	__le16 rq_num_wqes;
	__le16 rq_buffer_log_size;
	__le16 cq_num_wqes;
	__le16 mtu;
	u8 num_sessions_log;
	u8 flags;
#घोषणा FCOE_KWQE_INIT1_LOG_PAGE_SIZE (0xF<<0)
#घोषणा FCOE_KWQE_INIT1_LOG_PAGE_SIZE_SHIFT 0
#घोषणा FCOE_KWQE_INIT1_LOG_CACHED_PBES_PER_FUNC (0x7<<4)
#घोषणा FCOE_KWQE_INIT1_LOG_CACHED_PBES_PER_FUNC_SHIFT 4
#घोषणा FCOE_KWQE_INIT1_RESERVED1 (0x1<<7)
#घोषणा FCOE_KWQE_INIT1_RESERVED1_SHIFT 7
पूर्ण;

/*
 * FCoE firmware init request 2 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_init2 अणु
	u8 hsi_major_version;
	u8 hsi_minor_version;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 hash_tbl_pbl_addr_lo;
	__le32 hash_tbl_pbl_addr_hi;
	__le32 t2_hash_tbl_addr_lo;
	__le32 t2_hash_tbl_addr_hi;
	__le32 t2_ptr_hash_tbl_addr_lo;
	__le32 t2_ptr_hash_tbl_addr_hi;
	__le32 मुक्त_list_count;
पूर्ण;

/*
 * FCoE firmware init request 3 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_init3 अणु
	__le16 reserved0;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 error_bit_map_lo;
	__le32 error_bit_map_hi;
	u8 perf_config;
	u8 reserved21[3];
	__le32 reserved2[4];
पूर्ण;

/*
 * FCoE connection offload request 1 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_conn_offload1 अणु
	__le16 fcoe_conn_id;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 sq_addr_lo;
	__le32 sq_addr_hi;
	__le32 rq_pbl_addr_lo;
	__le32 rq_pbl_addr_hi;
	__le32 rq_first_pbe_addr_lo;
	__le32 rq_first_pbe_addr_hi;
	__le16 rq_prod;
	__le16 reserved0;
पूर्ण;

/*
 * FCoE connection offload request 2 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_conn_offload2 अणु
	__le16 tx_max_fc_pay_len;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 cq_addr_lo;
	__le32 cq_addr_hi;
	__le32 xferq_addr_lo;
	__le32 xferq_addr_hi;
	__le32 conn_db_addr_lo;
	__le32 conn_db_addr_hi;
	__le32 reserved1;
पूर्ण;

/*
 * FCoE connection offload request 3 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_conn_offload3 अणु
	__le16 vlan_tag;
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_VLAN_ID (0xFFF<<0)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_VLAN_ID_SHIFT 0
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_CFI (0x1<<12)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_CFI_SHIFT 12
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_PRIORITY (0x7<<13)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_PRIORITY_SHIFT 13
	काष्ठा fcoe_kwqe_header hdr;
	u8 s_id[3];
	u8 tx_max_conc_seqs_c3;
	u8 d_id[3];
	u8 flags;
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_MUL_N_PORT_IDS (0x1<<0)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_MUL_N_PORT_IDS_SHIFT 0
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_E_D_TOV_RES (0x1<<1)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_E_D_TOV_RES_SHIFT 1
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_CONT_INCR_SEQ_CNT (0x1<<2)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_CONT_INCR_SEQ_CNT_SHIFT 2
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_CONF_REQ (0x1<<3)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_CONF_REQ_SHIFT 3
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_REC_VALID (0x1<<4)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_REC_VALID_SHIFT 4
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_C2_VALID (0x1<<5)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_C2_VALID_SHIFT 5
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_ACK_0 (0x1<<6)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_ACK_0_SHIFT 6
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_VLAN_FLAG (0x1<<7)
#घोषणा FCOE_KWQE_CONN_OFFLOAD3_B_VLAN_FLAG_SHIFT 7
	__le32 reserved;
	__le32 confq_first_pbe_addr_lo;
	__le32 confq_first_pbe_addr_hi;
	__le16 tx_total_conc_seqs;
	__le16 rx_max_fc_pay_len;
	__le16 rx_total_conc_seqs;
	u8 rx_max_conc_seqs_c3;
	u8 rx_खोलो_seqs_exch_c3;
पूर्ण;

/*
 * FCoE connection offload request 4 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_conn_offload4 अणु
	u8 e_d_tov_समयr_val;
	u8 reserved2;
	काष्ठा fcoe_kwqe_header hdr;
	u8 src_mac_addr_lo[2];
	u8 src_mac_addr_mid[2];
	u8 src_mac_addr_hi[2];
	u8 dst_mac_addr_hi[2];
	u8 dst_mac_addr_lo[2];
	u8 dst_mac_addr_mid[2];
	__le32 lcq_addr_lo;
	__le32 lcq_addr_hi;
	__le32 confq_pbl_base_addr_lo;
	__le32 confq_pbl_base_addr_hi;
पूर्ण;

/*
 * FCoE connection enable request $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_conn_enable_disable अणु
	__le16 reserved0;
	काष्ठा fcoe_kwqe_header hdr;
	u8 src_mac_addr_lo[2];
	u8 src_mac_addr_mid[2];
	u8 src_mac_addr_hi[2];
	u16 vlan_tag;
#घोषणा FCOE_KWQE_CONN_ENABLE_DISABLE_VLAN_ID (0xFFF<<0)
#घोषणा FCOE_KWQE_CONN_ENABLE_DISABLE_VLAN_ID_SHIFT 0
#घोषणा FCOE_KWQE_CONN_ENABLE_DISABLE_CFI (0x1<<12)
#घोषणा FCOE_KWQE_CONN_ENABLE_DISABLE_CFI_SHIFT 12
#घोषणा FCOE_KWQE_CONN_ENABLE_DISABLE_PRIORITY (0x7<<13)
#घोषणा FCOE_KWQE_CONN_ENABLE_DISABLE_PRIORITY_SHIFT 13
	u8 dst_mac_addr_lo[2];
	u8 dst_mac_addr_mid[2];
	u8 dst_mac_addr_hi[2];
	__le16 reserved1;
	u8 s_id[3];
	u8 vlan_flag;
	u8 d_id[3];
	u8 reserved3;
	__le32 context_id;
	__le32 conn_id;
	__le32 reserved4;
पूर्ण;

/*
 * FCoE connection destroy request $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_conn_destroy अणु
	__le16 reserved0;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 context_id;
	__le32 conn_id;
	__le32 reserved1[5];
पूर्ण;

/*
 * FCoe destroy request $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_destroy अणु
	__le16 reserved0;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 reserved1[7];
पूर्ण;

/*
 * FCoe statistics request $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_kwqe_stat अणु
	__le16 reserved0;
	काष्ठा fcoe_kwqe_header hdr;
	__le32 stat_params_addr_lo;
	__le32 stat_params_addr_hi;
	__le32 reserved1[5];
पूर्ण;

/*
 * FCoE KWQ WQE $$KEEP_ENDIANNESS$$
 */
जोड़ fcoe_kwqe अणु
	काष्ठा fcoe_kwqe_init1 init1;
	काष्ठा fcoe_kwqe_init2 init2;
	काष्ठा fcoe_kwqe_init3 init3;
	काष्ठा fcoe_kwqe_conn_offload1 conn_offload1;
	काष्ठा fcoe_kwqe_conn_offload2 conn_offload2;
	काष्ठा fcoe_kwqe_conn_offload3 conn_offload3;
	काष्ठा fcoe_kwqe_conn_offload4 conn_offload4;
	काष्ठा fcoe_kwqe_conn_enable_disable conn_enable_disable;
	काष्ठा fcoe_kwqe_conn_destroy conn_destroy;
	काष्ठा fcoe_kwqe_destroy destroy;
	काष्ठा fcoe_kwqe_stat statistics;
पूर्ण;
















/*
 * TX SGL context $$KEEP_ENDIANNESS$$
 */
जोड़ fcoe_sgl_जोड़_ctx अणु
	काष्ठा fcoe_cached_sge_ctx cached_sge;
	काष्ठा fcoe_ext_mul_sges_ctx sgl;
	__le32 opaque[5];
पूर्ण;

/*
 * Data-In/ELS/BLS inक्रमmation $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_पढ़ो_flow_info अणु
	जोड़ fcoe_sgl_जोड़_ctx sgl_ctx;
	__le32 rsrv0[3];
पूर्ण;


/*
 * Fcoe stat context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_s_stat_ctx अणु
	u8 flags;
#घोषणा FCOE_S_STAT_CTX_ACTIVE (0x1<<0)
#घोषणा FCOE_S_STAT_CTX_ACTIVE_SHIFT 0
#घोषणा FCOE_S_STAT_CTX_ACK_ABORT_SEQ_COND (0x1<<1)
#घोषणा FCOE_S_STAT_CTX_ACK_ABORT_SEQ_COND_SHIFT 1
#घोषणा FCOE_S_STAT_CTX_ABTS_PERFORMED (0x1<<2)
#घोषणा FCOE_S_STAT_CTX_ABTS_PERFORMED_SHIFT 2
#घोषणा FCOE_S_STAT_CTX_SEQ_TIMEOUT (0x1<<3)
#घोषणा FCOE_S_STAT_CTX_SEQ_TIMEOUT_SHIFT 3
#घोषणा FCOE_S_STAT_CTX_P_RJT (0x1<<4)
#घोषणा FCOE_S_STAT_CTX_P_RJT_SHIFT 4
#घोषणा FCOE_S_STAT_CTX_ACK_खातापूर्णT (0x1<<5)
#घोषणा FCOE_S_STAT_CTX_ACK_खातापूर्णT_SHIFT 5
#घोषणा FCOE_S_STAT_CTX_RSRV1 (0x3<<6)
#घोषणा FCOE_S_STAT_CTX_RSRV1_SHIFT 6
पूर्ण;

/*
 * Fcoe rx seq context $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_rx_seq_ctx अणु
	u8 seq_id;
	काष्ठा fcoe_s_stat_ctx s_stat;
	__le16 seq_cnt;
	__le32 low_exp_ro;
	__le32 high_exp_ro;
पूर्ण;


/*
 * Fcoe rx_wr जोड़ context $$KEEP_ENDIANNESS$$
 */
जोड़ fcoe_rx_wr_जोड़_ctx अणु
	काष्ठा fcoe_पढ़ो_flow_info पढ़ो_info;
	जोड़ fcoe_comp_flow_info comp_info;
	__le32 opaque[8];
पूर्ण;



/*
 * FCoE SQ element $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_sqe अणु
	__le16 wqe;
#घोषणा FCOE_SQE_TASK_ID (0x7FFF<<0)
#घोषणा FCOE_SQE_TASK_ID_SHIFT 0
#घोषणा FCOE_SQE_TOGGLE_BIT (0x1<<15)
#घोषणा FCOE_SQE_TOGGLE_BIT_SHIFT 15
पूर्ण;



/*
 * 14 regs $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_tx_only अणु
	जोड़ fcoe_sgl_जोड़_ctx sgl_ctx;
	__le32 rsrv0;
पूर्ण;

/*
 * 32 bytes (8 regs) used क्रम TX only purposes $$KEEP_ENDIANNESS$$
 */
जोड़ fcoe_tx_wr_rx_rd_जोड़_ctx अणु
	काष्ठा fcoe_fc_frame tx_frame;
	काष्ठा fcoe_fcp_cmd_payload fcp_cmd;
	काष्ठा fcoe_ext_cleanup_info cleanup;
	काष्ठा fcoe_ext_abts_info abts;
	काष्ठा fcoe_ext_fw_tx_seq_ctx tx_seq;
	__le32 opaque[8];
पूर्ण;

/*
 * tce_tx_wr_rx_rd_स्थिर $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_tx_wr_rx_rd_स्थिर अणु
	u8 init_flags;
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE (0x7<<0)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT 0
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE (0x1<<3)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT 3
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE (0x1<<4)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT 4
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_CACHED_SGE (0x3<<5)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_CACHED_SGE_SHIFT 5
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_SUPPORT_REC_TOV (0x1<<7)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_SUPPORT_REC_TOV_SHIFT 7
	u8 tx_flags;
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TX_VALID (0x1<<0)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TX_VALID_SHIFT 0
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE (0xF<<1)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT 1
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_RSRV1 (0x1<<5)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_RSRV1_SHIFT 5
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TX_SEQ_INIT (0x1<<6)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_TX_SEQ_INIT_SHIFT 6
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_RSRV2 (0x1<<7)
#घोषणा FCOE_TCE_TX_WR_RX_RD_CONST_RSRV2_SHIFT 7
	__le16 rsrv3;
	__le32 verअगरy_tx_seq;
पूर्ण;

/*
 * tce_tx_wr_rx_rd $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_tx_wr_rx_rd अणु
	जोड़ fcoe_tx_wr_rx_rd_जोड़_ctx जोड़_ctx;
	काष्ठा fcoe_tce_tx_wr_rx_rd_स्थिर स्थिर_ctx;
पूर्ण;

/*
 * tce_rx_wr_tx_rd_स्थिर $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_rx_wr_tx_rd_स्थिर अणु
	__le32 data_2_trns;
	__le32 init_flags;
#घोषणा FCOE_TCE_RX_WR_TX_RD_CONST_CID (0xFFFFFF<<0)
#घोषणा FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT 0
#घोषणा FCOE_TCE_RX_WR_TX_RD_CONST_RSRV0 (0xFF<<24)
#घोषणा FCOE_TCE_RX_WR_TX_RD_CONST_RSRV0_SHIFT 24
पूर्ण;

/*
 * tce_rx_wr_tx_rd_var $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_rx_wr_tx_rd_var अणु
	__le16 rx_flags;
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RSRV1 (0xF<<0)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RSRV1_SHIFT 0
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_NUM_RQ_WQE (0x7<<4)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_NUM_RQ_WQE_SHIFT 4
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_CONF_REQ (0x1<<7)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_CONF_REQ_SHIFT 7
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RX_STATE (0xF<<8)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RX_STATE_SHIFT 8
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME (0x1<<12)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME_SHIFT 12
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RX_SEQ_INIT (0x1<<13)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RX_SEQ_INIT_SHIFT 13
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RSRV2 (0x1<<14)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RSRV2_SHIFT 14
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RX_VALID (0x1<<15)
#घोषणा FCOE_TCE_RX_WR_TX_RD_VAR_RX_VALID_SHIFT 15
	__le16 rx_id;
	काष्ठा fcoe_fcp_xfr_rdy_payload fcp_xfr_rdy;
पूर्ण;

/*
 * tce_rx_wr_tx_rd $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_rx_wr_tx_rd अणु
	काष्ठा fcoe_tce_rx_wr_tx_rd_स्थिर स्थिर_ctx;
	काष्ठा fcoe_tce_rx_wr_tx_rd_var var_ctx;
पूर्ण;

/*
 * tce_rx_only $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tce_rx_only अणु
	काष्ठा fcoe_rx_seq_ctx rx_seq_ctx;
	जोड़ fcoe_rx_wr_जोड़_ctx जोड़_ctx;
पूर्ण;

/*
 * task_ctx_entry $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_task_ctx_entry अणु
	काष्ठा fcoe_tce_tx_only txwr_only;
	काष्ठा fcoe_tce_tx_wr_rx_rd txwr_rxrd;
	काष्ठा fcoe_tce_rx_wr_tx_rd rxwr_txrd;
	काष्ठा fcoe_tce_rx_only rxwr_only;
पूर्ण;










/*
 * FCoE XFRQ element $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_xfrqe अणु
	__le16 wqe;
#घोषणा FCOE_XFRQE_TASK_ID (0x7FFF<<0)
#घोषणा FCOE_XFRQE_TASK_ID_SHIFT 0
#घोषणा FCOE_XFRQE_TOGGLE_BIT (0x1<<15)
#घोषणा FCOE_XFRQE_TOGGLE_BIT_SHIFT 15
पूर्ण;


/*
 * fcoe rx करोorbell message sent to the chip $$KEEP_ENDIANNESS$$
 */
काष्ठा b577xx_fcoe_rx_करोorbell अणु
	काष्ठा b577xx_करोorbell_hdr hdr;
	u8 params;
#घोषणा B577XX_FCOE_RX_DOORBELL_NEGATIVE_ARM (0x1F<<0)
#घोषणा B577XX_FCOE_RX_DOORBELL_NEGATIVE_ARM_SHIFT 0
#घोषणा B577XX_FCOE_RX_DOORBELL_OPCODE (0x7<<5)
#घोषणा B577XX_FCOE_RX_DOORBELL_OPCODE_SHIFT 5
	__le16 करोorbell_cq_cons;
पूर्ण;


/*
 * FCoE CONFQ element $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_confqe अणु
	__le16 ox_id;
	__le16 rx_id;
	__le32 param;
पूर्ण;


/*
 * FCoE connection data base
 */
काष्ठा fcoe_conn_db अणु
#अगर defined(__BIG_ENDIAN)
	u16 rsrv0;
	u16 rq_prod;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 rq_prod;
	u16 rsrv0;
#पूर्ण_अगर
	u32 rsrv1;
	काष्ठा regpair cq_arm;
पूर्ण;


/*
 * FCoE CQ element $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_cqe अणु
	__le16 wqe;
#घोषणा FCOE_CQE_CQE_INFO (0x3FFF<<0)
#घोषणा FCOE_CQE_CQE_INFO_SHIFT 0
#घोषणा FCOE_CQE_CQE_TYPE (0x1<<14)
#घोषणा FCOE_CQE_CQE_TYPE_SHIFT 14
#घोषणा FCOE_CQE_TOGGLE_BIT (0x1<<15)
#घोषणा FCOE_CQE_TOGGLE_BIT_SHIFT 15
पूर्ण;


/*
 * FCoE error/warning reporting entry $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_partial_err_report_entry अणु
	__le32 err_warn_biपंचांगap_lo;
	__le32 err_warn_biपंचांगap_hi;
	__le32 tx_buf_off;
	__le32 rx_buf_off;
पूर्ण;

/*
 * FCoE error/warning reporting entry $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_err_report_entry अणु
	काष्ठा fcoe_partial_err_report_entry data;
	काष्ठा fcoe_fc_hdr fc_hdr;
पूर्ण;


/*
 * FCoE hash table entry (32 bytes) $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_hash_table_entry अणु
	u8 s_id_0;
	u8 s_id_1;
	u8 s_id_2;
	u8 d_id_0;
	u8 d_id_1;
	u8 d_id_2;
	__le16 dst_mac_addr_hi;
	__le16 dst_mac_addr_mid;
	__le16 dst_mac_addr_lo;
	__le16 src_mac_addr_hi;
	__le16 vlan_id;
	__le16 src_mac_addr_lo;
	__le16 src_mac_addr_mid;
	u8 vlan_flag;
	u8 reserved0;
	__le16 reserved1;
	__le32 reserved2;
	__le32 field_id;
#घोषणा FCOE_HASH_TABLE_ENTRY_CID (0xFFFFFF<<0)
#घोषणा FCOE_HASH_TABLE_ENTRY_CID_SHIFT 0
#घोषणा FCOE_HASH_TABLE_ENTRY_RESERVED3 (0x7F<<24)
#घोषणा FCOE_HASH_TABLE_ENTRY_RESERVED3_SHIFT 24
#घोषणा FCOE_HASH_TABLE_ENTRY_VALID (0x1<<31)
#घोषणा FCOE_HASH_TABLE_ENTRY_VALID_SHIFT 31
पूर्ण;


/*
 * FCoE LCQ element $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_lcqe अणु
	__le32 wqe;
#घोषणा FCOE_LCQE_TASK_ID (0xFFFF<<0)
#घोषणा FCOE_LCQE_TASK_ID_SHIFT 0
#घोषणा FCOE_LCQE_LCQE_TYPE (0xFF<<16)
#घोषणा FCOE_LCQE_LCQE_TYPE_SHIFT 16
#घोषणा FCOE_LCQE_RESERVED (0xFF<<24)
#घोषणा FCOE_LCQE_RESERVED_SHIFT 24
पूर्ण;



/*
 * FCoE pending work request CQE $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_pend_wq_cqe अणु
	__le16 wqe;
#घोषणा FCOE_PEND_WQ_CQE_TASK_ID (0x3FFF<<0)
#घोषणा FCOE_PEND_WQ_CQE_TASK_ID_SHIFT 0
#घोषणा FCOE_PEND_WQ_CQE_CQE_TYPE (0x1<<14)
#घोषणा FCOE_PEND_WQ_CQE_CQE_TYPE_SHIFT 14
#घोषणा FCOE_PEND_WQ_CQE_TOGGLE_BIT (0x1<<15)
#घोषणा FCOE_PEND_WQ_CQE_TOGGLE_BIT_SHIFT 15
पूर्ण;


/*
 * FCoE RX statistics parameters section#0 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_rx_stat_params_section0 अणु
	__le32 fcoe_rx_pkt_cnt;
	__le32 fcoe_rx_byte_cnt;
पूर्ण;


/*
 * FCoE RX statistics parameters section#1 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_rx_stat_params_section1 अणु
	__le32 fcoe_ver_cnt;
	__le32 fcoe_rx_drop_pkt_cnt;
पूर्ण;


/*
 * FCoE RX statistics parameters section#2 $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_rx_stat_params_section2 अणु
	__le32 fc_crc_cnt;
	__le32 eofa_del_cnt;
	__le32 miss_frame_cnt;
	__le32 seq_समयout_cnt;
	__le32 drop_seq_cnt;
	__le32 fcoe_rx_drop_pkt_cnt;
	__le32 fcp_rx_pkt_cnt;
	__le32 reserved0;
पूर्ण;


/*
 * FCoE TX statistics parameters $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_tx_stat_params अणु
	__le32 fcoe_tx_pkt_cnt;
	__le32 fcoe_tx_byte_cnt;
	__le32 fcp_tx_pkt_cnt;
	__le32 reserved0;
पूर्ण;

/*
 * FCoE statistics parameters $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_statistics_params अणु
	काष्ठा fcoe_tx_stat_params tx_stat;
	काष्ठा fcoe_rx_stat_params_section0 rx_stat0;
	काष्ठा fcoe_rx_stat_params_section1 rx_stat1;
	काष्ठा fcoe_rx_stat_params_section2 rx_stat2;
पूर्ण;


/*
 * FCoE t2 hash table entry (64 bytes) $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_t2_hash_table_entry अणु
	काष्ठा fcoe_hash_table_entry data;
	काष्ठा regpair next;
	काष्ठा regpair reserved0[3];
पूर्ण;



/*
 * FCoE unsolicited CQE $$KEEP_ENDIANNESS$$
 */
काष्ठा fcoe_unsolicited_cqe अणु
	__le16 wqe;
#घोषणा FCOE_UNSOLICITED_CQE_SUBTYPE (0x3<<0)
#घोषणा FCOE_UNSOLICITED_CQE_SUBTYPE_SHIFT 0
#घोषणा FCOE_UNSOLICITED_CQE_PKT_LEN (0xFFF<<2)
#घोषणा FCOE_UNSOLICITED_CQE_PKT_LEN_SHIFT 2
#घोषणा FCOE_UNSOLICITED_CQE_CQE_TYPE (0x1<<14)
#घोषणा FCOE_UNSOLICITED_CQE_CQE_TYPE_SHIFT 14
#घोषणा FCOE_UNSOLICITED_CQE_TOGGLE_BIT (0x1<<15)
#घोषणा FCOE_UNSOLICITED_CQE_TOGGLE_BIT_SHIFT 15
पूर्ण;

#पूर्ण_अगर /* __57XX_FCOE_HSI_LINUX_LE__ */
