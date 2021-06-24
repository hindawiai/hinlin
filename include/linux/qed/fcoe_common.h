<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015 QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित __FCOE_COMMON__
#घोषणा __FCOE_COMMON__

/*********************/
/* FCOE FW CONSTANTS */
/*********************/

#घोषणा FC_ABTS_REPLY_MAX_PAYLOAD_LEN	12

/* The fcoe storm task context protection-inक्रमmation of Ystorm */
काष्ठा protection_info_ctx अणु
	__le16 flags;
#घोषणा PROTECTION_INFO_CTX_HOST_INTERFACE_MASK		0x3
#घोषणा PROTECTION_INFO_CTX_HOST_INTERFACE_SHIFT	0
#घोषणा PROTECTION_INFO_CTX_DIF_TO_PEER_MASK		0x1
#घोषणा PROTECTION_INFO_CTX_DIF_TO_PEER_SHIFT		2
#घोषणा PROTECTION_INFO_CTX_VALIDATE_DIX_APP_TAG_MASK	0x1
#घोषणा PROTECTION_INFO_CTX_VALIDATE_DIX_APP_TAG_SHIFT	3
#घोषणा PROTECTION_INFO_CTX_INTERVAL_SIZE_LOG_MASK	0xF
#घोषणा PROTECTION_INFO_CTX_INTERVAL_SIZE_LOG_SHIFT	4
#घोषणा PROTECTION_INFO_CTX_VALIDATE_DIX_REF_TAG_MASK	0x1
#घोषणा PROTECTION_INFO_CTX_VALIDATE_DIX_REF_TAG_SHIFT	8
#घोषणा PROTECTION_INFO_CTX_RESERVED0_MASK		0x7F
#घोषणा PROTECTION_INFO_CTX_RESERVED0_SHIFT		9
	u8 dix_block_size;
	u8 dst_size;
पूर्ण;

/* The fcoe storm task context protection-inक्रमmation of Ystorm */
जोड़ protection_info_जोड़_ctx अणु
	काष्ठा protection_info_ctx info;
	__le32 value;
पूर्ण;

/* FCP CMD payload */
काष्ठा fcoe_fcp_cmd_payload अणु
	__le32 opaque[8];
पूर्ण;

/* FCP RSP payload */
काष्ठा fcoe_fcp_rsp_payload अणु
	__le32 opaque[6];
पूर्ण;

/* FCP RSP payload */
काष्ठा fcp_rsp_payload_padded अणु
	काष्ठा fcoe_fcp_rsp_payload rsp_payload;
	__le32 reserved[2];
पूर्ण;

/* FCP RSP payload */
काष्ठा fcoe_fcp_xfer_payload अणु
	__le32 opaque[3];
पूर्ण;

/* FCP RSP payload */
काष्ठा fcp_xfer_payload_padded अणु
	काष्ठा fcoe_fcp_xfer_payload xfer_payload;
	__le32 reserved[5];
पूर्ण;

/* Task params */
काष्ठा fcoe_tx_data_params अणु
	__le32 data_offset;
	__le32 offset_in_io;
	u8 flags;
#घोषणा FCOE_TX_DATA_PARAMS_OFFSET_IN_IO_VALID_MASK	0x1
#घोषणा FCOE_TX_DATA_PARAMS_OFFSET_IN_IO_VALID_SHIFT	0
#घोषणा FCOE_TX_DATA_PARAMS_DROP_DATA_MASK		0x1
#घोषणा FCOE_TX_DATA_PARAMS_DROP_DATA_SHIFT		1
#घोषणा FCOE_TX_DATA_PARAMS_AFTER_SEQ_REC_MASK		0x1
#घोषणा FCOE_TX_DATA_PARAMS_AFTER_SEQ_REC_SHIFT		2
#घोषणा FCOE_TX_DATA_PARAMS_RESERVED0_MASK		0x1F
#घोषणा FCOE_TX_DATA_PARAMS_RESERVED0_SHIFT		3
	u8 dअगर_residual;
	__le16 seq_cnt;
	__le16 single_sge_saved_offset;
	__le16 next_dअगर_offset;
	__le16 seq_id;
	__le16 reserved3;
पूर्ण;

/* Middle path parameters: FC header fields provided by the driver */
काष्ठा fcoe_tx_mid_path_params अणु
	__le32 parameter;
	u8 r_ctl;
	u8 type;
	u8 cs_ctl;
	u8 df_ctl;
	__le16 rx_id;
	__le16 ox_id;
पूर्ण;

/* Task params */
काष्ठा fcoe_tx_params अणु
	काष्ठा fcoe_tx_data_params data;
	काष्ठा fcoe_tx_mid_path_params mid_path;
पूर्ण;

/* Union of FCP CMD payload \ TX params \ ABTS \ Cleanup */
जोड़ fcoe_tx_info_जोड़_ctx अणु
	काष्ठा fcoe_fcp_cmd_payload fcp_cmd_payload;
	काष्ठा fcp_rsp_payload_padded fcp_rsp_payload;
	काष्ठा fcp_xfer_payload_padded fcp_xfer_payload;
	काष्ठा fcoe_tx_params tx_params;
पूर्ण;

/* Data sgl */
काष्ठा fcoe_slow_sgl_ctx अणु
	काष्ठा regpair base_sgl_addr;
	__le16 curr_sge_off;
	__le16 reमुख्यder_num_sges;
	__le16 curr_sgl_index;
	__le16 reserved;
पूर्ण;

/* Union of DIX SGL \ cached DIX sges */
जोड़ fcoe_dix_desc_ctx अणु
	काष्ठा fcoe_slow_sgl_ctx dix_sgl;
	काष्ठा scsi_sge cached_dix_sge;
पूर्ण;

/* The fcoe storm task context of Ystorm */
काष्ठा ystorm_fcoe_task_st_ctx अणु
	u8 task_type;
	u8 sgl_mode;
#घोषणा YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE_MASK	0x1
#घोषणा YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE_SHIFT	0
#घोषणा YSTORM_FCOE_TASK_ST_CTX_RSRV_MASK		0x7F
#घोषणा YSTORM_FCOE_TASK_ST_CTX_RSRV_SHIFT		1
	u8 cached_dix_sge;
	u8 expect_first_xfer;
	__le32 num_pbf_zero_ग_लिखो;
	जोड़ protection_info_जोड़_ctx protection_info_जोड़;
	__le32 data_2_trns_rem;
	काष्ठा scsi_sgl_params sgl_params;
	u8 reserved1[12];
	जोड़ fcoe_tx_info_जोड़_ctx tx_info_जोड़;
	जोड़ fcoe_dix_desc_ctx dix_desc;
	काष्ठा scsi_cached_sges data_desc;
	__le16 ox_id;
	__le16 rx_id;
	__le32 task_rety_identअगरier;
	u8 reserved2[8];
पूर्ण;

काष्ठा e4_ystorm_fcoe_task_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	__le16 word0;
	u8 flags0;
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_NIBBLE0_MASK		0xF
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_NIBBLE0_SHIFT	0
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT0_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT0_SHIFT		4
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT1_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT1_SHIFT		5
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT2_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT2_SHIFT		6
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT3_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT3_SHIFT		7
	u8 flags1;
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF0_MASK		0x3
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF0_SHIFT		0
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF1_MASK		0x3
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF1_SHIFT		2
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF2SPECIAL_MASK	0x3
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF2SPECIAL_SHIFT	4
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF0EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF0EN_SHIFT		6
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF1EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_CF1EN_SHIFT		7
	u8 flags2;
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT4_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_BIT4_SHIFT		0
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE0EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE0EN_SHIFT	1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE1EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE1EN_SHIFT	2
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE2EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE2EN_SHIFT	3
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE3EN_SHIFT	4
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE4EN_SHIFT	5
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE5EN_SHIFT	6
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_YSTORM_FCOE_TASK_AG_CTX_RULE6EN_SHIFT	7
	u8 byte2;
	__le32 reg0;
	u8 byte3;
	u8 byte4;
	__le16 rx_id;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le16 word5;
	__le32 reg1;
	__le32 reg2;
पूर्ण;

काष्ठा e4_tstorm_fcoe_task_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	__le16 icid;
	u8 flags0;
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_BIT1_SHIFT			5
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_WAIT_ABTS_RSP_F_MASK		0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_WAIT_ABTS_RSP_F_SHIFT	6
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_VALID_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_VALID_SHIFT			7
	u8 flags1;
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_FALSE_RR_TOV_MASK	0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_FALSE_RR_TOV_SHIFT	0
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_BIT5_MASK		0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_BIT5_SHIFT		1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_REC_RR_TOV_CF_MASK	0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_REC_RR_TOV_CF_SHIFT	2
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_ED_TOV_CF_MASK	0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_ED_TOV_CF_SHIFT	4
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_CF2_MASK		0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_CF2_SHIFT		6
	u8 flags2;
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_TIMER_STOP_ALL_MASK		0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_TIMER_STOP_ALL_SHIFT		0
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_MASK		0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_SHIFT		2
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_MASK		0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_SHIFT		4
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_RECOVERY_CF_MASK		0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_RECOVERY_CF_SHIFT	6
	u8 flags3;
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_UNSOL_COMP_CF_MASK		0x3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_UNSOL_COMP_CF_SHIFT		0
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_REC_RR_TOV_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_REC_RR_TOV_CF_EN_SHIFT	2
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_ED_TOV_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_ED_TOV_CF_EN_SHIFT		3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_CF2EN_SHIFT			4
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_TIMER_STOP_ALL_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_TIMER_STOP_ALL_EN_SHIFT	5
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_EN_SHIFT	6
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_EN_MASK		0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_INIT_CF_EN_SHIFT		7
	u8 flags4;
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_RECOVERY_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_SEQ_RECOVERY_CF_EN_SHIFT	0
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_UNSOL_COMP_CF_EN_MASK	0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_UNSOL_COMP_CF_EN_SHIFT	1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE0EN_SHIFT		2
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE1EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE1EN_SHIFT		3
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE2EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE2EN_SHIFT		4
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE3EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE3EN_SHIFT		5
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE4EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE4EN_SHIFT		6
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE5EN_MASK			0x1
#घोषणा E4_TSTORM_FCOE_TASK_AG_CTX_RULE5EN_SHIFT		7
	u8 cleanup_state;
	__le16 last_sent_tid;
	__le32 rec_rr_tov_exp_समयout;
	u8 byte3;
	u8 byte4;
	__le16 word2;
	__le16 word3;
	__le16 word4;
	__le32 data_offset_end_of_seq;
	__le32 data_offset_next;
पूर्ण;

/* Cached data sges */
काष्ठा fcoe_exp_ro अणु
	__le32 data_offset;
	__le32 reserved;
पूर्ण;

/* Union of Cleanup address \ expected relative offsets */
जोड़ fcoe_cleanup_addr_exp_ro_जोड़ अणु
	काष्ठा regpair abts_rsp_fc_payload_hi;
	काष्ठा fcoe_exp_ro exp_ro;
पूर्ण;

/* Fields coppied from ABTSrsp pckt */
काष्ठा fcoe_abts_pkt अणु
	__le32 abts_rsp_fc_payload_lo;
	__le16 abts_rsp_rx_id;
	u8 abts_rsp_rctl;
	u8 reserved2;
पूर्ण;

/* FW पढ़ो- ग_लिखो (modअगरyable) part The fcoe task storm context of Tstorm */
काष्ठा fcoe_tstorm_fcoe_task_st_ctx_पढ़ो_ग_लिखो अणु
	जोड़ fcoe_cleanup_addr_exp_ro_जोड़ cleanup_addr_exp_ro_जोड़;
	__le16 flags;
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RX_SGL_MODE_MASK	0x1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RX_SGL_MODE_SHIFT	0
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME_MASK	0x1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME_SHIFT	1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_SEQ_ACTIVE_MASK		0x1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_SEQ_ACTIVE_SHIFT	2
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_SEQ_TIMEOUT_MASK	0x1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_SEQ_TIMEOUT_SHIFT	3
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_SINGLE_PKT_IN_EX_MASK	0x1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_SINGLE_PKT_IN_EX_SHIFT	4
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_OOO_RX_SEQ_STAT_MASK	0x1
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_OOO_RX_SEQ_STAT_SHIFT	5
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_CQ_ADD_ADV_MASK		0x3
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_CQ_ADD_ADV_SHIFT	6
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RSRV1_MASK		0xFF
#घोषणा FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RSRV1_SHIFT		8
	__le16 seq_cnt;
	u8 seq_id;
	u8 ooo_rx_seq_id;
	__le16 rx_id;
	काष्ठा fcoe_abts_pkt abts_data;
	__le32 e_d_tov_exp_समयout_val;
	__le16 ooo_rx_seq_cnt;
	__le16 reserved1;
पूर्ण;

/* FW पढ़ो only part The fcoe task storm context of Tstorm */
काष्ठा fcoe_tstorm_fcoe_task_st_ctx_पढ़ो_only अणु
	u8 task_type;
	u8 dev_type;
	u8 conf_supported;
	u8 glbl_q_num;
	__le32 cid;
	__le32 fcp_cmd_trns_size;
	__le32 rsrv;
पूर्ण;

/** The fcoe task storm context of Tstorm */
काष्ठा tstorm_fcoe_task_st_ctx अणु
	काष्ठा fcoe_tstorm_fcoe_task_st_ctx_पढ़ो_ग_लिखो पढ़ो_ग_लिखो;
	काष्ठा fcoe_tstorm_fcoe_task_st_ctx_पढ़ो_only पढ़ो_only;
पूर्ण;

काष्ठा e4_mstorm_fcoe_task_ag_ctx अणु
	u8 byte0;
	u8 byte1;
	__le16 icid;
	u8 flags0;
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CQE_PLACED_MASK		0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CQE_PLACED_SHIFT		5
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_BIT2_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_BIT2_SHIFT			6
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_BIT3_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_BIT3_SHIFT			7
	u8 flags1;
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_MASK		0x3
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_SHIFT		0
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF1_MASK			0x3
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF1_SHIFT			2
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF2_MASK			0x3
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF2_SHIFT			4
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_EN_MASK	0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_EX_CLEANUP_CF_EN_SHIFT	6
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF1EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF1EN_SHIFT			7
	u8 flags2;
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_CF2EN_SHIFT			0
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE0EN_SHIFT		1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE1EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE1EN_SHIFT		2
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE2EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE2EN_SHIFT		3
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE3EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE3EN_SHIFT		4
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE4EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE4EN_SHIFT		5
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_XFER_PLACEMENT_EN_MASK	0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_XFER_PLACEMENT_EN_SHIFT	6
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE6EN_MASK			0x1
#घोषणा E4_MSTORM_FCOE_TASK_AG_CTX_RULE6EN_SHIFT		7
	u8 cleanup_state;
	__le32 received_bytes;
	u8 byte3;
	u8 glbl_q_num;
	__le16 word1;
	__le16 tid_to_xfer;
	__le16 word3;
	__le16 word4;
	__le16 word5;
	__le32 expected_bytes;
	__le32 reg2;
पूर्ण;

/* The fcoe task storm context of Mstorm */
काष्ठा mstorm_fcoe_task_st_ctx अणु
	काष्ठा regpair rsp_buf_addr;
	__le32 rsrv[2];
	काष्ठा scsi_sgl_params sgl_params;
	__le32 data_2_trns_rem;
	__le32 data_buffer_offset;
	__le16 parent_id;
	__le16 flags;
#घोषणा MSTORM_FCOE_TASK_ST_CTX_INTERVAL_SIZE_LOG_MASK		0xF
#घोषणा MSTORM_FCOE_TASK_ST_CTX_INTERVAL_SIZE_LOG_SHIFT		0
#घोषणा MSTORM_FCOE_TASK_ST_CTX_HOST_INTERFACE_MASK		0x3
#घोषणा MSTORM_FCOE_TASK_ST_CTX_HOST_INTERFACE_SHIFT		4
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIF_TO_PEER_MASK		0x1
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIF_TO_PEER_SHIFT		6
#घोषणा MSTORM_FCOE_TASK_ST_CTX_MP_INCLUDE_FC_HEADER_MASK	0x1
#घोषणा MSTORM_FCOE_TASK_ST_CTX_MP_INCLUDE_FC_HEADER_SHIFT	7
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIX_BLOCK_SIZE_MASK		0x3
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIX_BLOCK_SIZE_SHIFT		8
#घोषणा MSTORM_FCOE_TASK_ST_CTX_VALIDATE_DIX_REF_TAG_MASK	0x1
#घोषणा MSTORM_FCOE_TASK_ST_CTX_VALIDATE_DIX_REF_TAG_SHIFT	10
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIX_CACHED_SGE_FLG_MASK		0x1
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIX_CACHED_SGE_FLG_SHIFT	11
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIF_SUPPORTED_MASK		0x1
#घोषणा MSTORM_FCOE_TASK_ST_CTX_DIF_SUPPORTED_SHIFT		12
#घोषणा MSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE_MASK		0x1
#घोषणा MSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE_SHIFT		13
#घोषणा MSTORM_FCOE_TASK_ST_CTX_RESERVED_MASK			0x3
#घोषणा MSTORM_FCOE_TASK_ST_CTX_RESERVED_SHIFT			14
	काष्ठा scsi_cached_sges data_desc;
पूर्ण;

काष्ठा e4_ustorm_fcoe_task_ag_ctx अणु
	u8 reserved;
	u8 byte1;
	__le16 icid;
	u8 flags0;
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_MASK		0xF
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CONNECTION_TYPE_SHIFT	0
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_MASK		0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_EXIST_IN_QM0_SHIFT		4
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_BIT1_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_BIT1_SHIFT			5
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF0_MASK			0x3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF0_SHIFT			6
	u8 flags1;
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF1_MASK		0x3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF1_SHIFT		0
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF2_MASK		0x3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF2_SHIFT		2
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF3_MASK		0x3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF3_SHIFT		4
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_DIF_ERROR_CF_MASK	0x3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_DIF_ERROR_CF_SHIFT	6
	u8 flags2;
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF0EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF0EN_SHIFT			0
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF1EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF1EN_SHIFT			1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF2EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF2EN_SHIFT			2
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF3EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_CF3EN_SHIFT			3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_DIF_ERROR_CF_EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_DIF_ERROR_CF_EN_SHIFT	4
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE0EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE0EN_SHIFT		5
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE1EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE1EN_SHIFT		6
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE2EN_MASK			0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE2EN_SHIFT		7
	u8 flags3;
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE3EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE3EN_SHIFT	0
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE4EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE4EN_SHIFT	1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE5EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE5EN_SHIFT	2
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE6EN_MASK		0x1
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_RULE6EN_SHIFT	3
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_DIF_ERROR_TYPE_MASK	0xF
#घोषणा E4_USTORM_FCOE_TASK_AG_CTX_DIF_ERROR_TYPE_SHIFT	4
	__le32 dअगर_err_पूर्णांकervals;
	__le32 dअगर_error_1st_पूर्णांकerval;
	__le32 global_cq_num;
	__le32 reg3;
	__le32 reg4;
	__le32 reg5;
पूर्ण;

/* FCoE task context */
काष्ठा e4_fcoe_task_context अणु
	काष्ठा ystorm_fcoe_task_st_ctx ystorm_st_context;
	काष्ठा regpair ystorm_st_padding[2];
	काष्ठा tdअगर_task_context tdअगर_context;
	काष्ठा e4_ystorm_fcoe_task_ag_ctx ystorm_ag_context;
	काष्ठा e4_tstorm_fcoe_task_ag_ctx tstorm_ag_context;
	काष्ठा समयrs_context समयr_context;
	काष्ठा tstorm_fcoe_task_st_ctx tstorm_st_context;
	काष्ठा regpair tstorm_st_padding[2];
	काष्ठा e4_mstorm_fcoe_task_ag_ctx mstorm_ag_context;
	काष्ठा mstorm_fcoe_task_st_ctx mstorm_st_context;
	काष्ठा e4_ustorm_fcoe_task_ag_ctx ustorm_ag_context;
	काष्ठा rdअगर_task_context rdअगर_context;
पूर्ण;

/* FCoE additional WQE (Sq/XferQ) inक्रमmation */
जोड़ fcoe_additional_info_जोड़ अणु
	__le32 previous_tid;
	__le32 parent_tid;
	__le32 burst_length;
	__le32 seq_rec_updated_offset;
पूर्ण;

/* FCoE Ramrod Command IDs */
क्रमागत fcoe_completion_status अणु
	FCOE_COMPLETION_STATUS_SUCCESS,
	FCOE_COMPLETION_STATUS_FCOE_VER_ERR,
	FCOE_COMPLETION_STATUS_SRC_MAC_ADD_ARR_ERR,
	MAX_FCOE_COMPLETION_STATUS
पूर्ण;

/* FC address (SID/DID) network presentation */
काष्ठा fc_addr_nw अणु
	u8 addr_lo;
	u8 addr_mid;
	u8 addr_hi;
पूर्ण;

/* FCoE connection offload */
काष्ठा fcoe_conn_offload_ramrod_data अणु
	काष्ठा regpair sq_pbl_addr;
	काष्ठा regpair sq_curr_page_addr;
	काष्ठा regpair sq_next_page_addr;
	काष्ठा regpair xferq_pbl_addr;
	काष्ठा regpair xferq_curr_page_addr;
	काष्ठा regpair xferq_next_page_addr;
	काष्ठा regpair respq_pbl_addr;
	काष्ठा regpair respq_curr_page_addr;
	काष्ठा regpair respq_next_page_addr;
	__le16 dst_mac_addr_lo;
	__le16 dst_mac_addr_mid;
	__le16 dst_mac_addr_hi;
	__le16 src_mac_addr_lo;
	__le16 src_mac_addr_mid;
	__le16 src_mac_addr_hi;
	__le16 tx_max_fc_pay_len;
	__le16 e_d_tov_समयr_val;
	__le16 rx_max_fc_pay_len;
	__le16 vlan_tag;
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_VLAN_ID_MASK	0xFFF
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_VLAN_ID_SHIFT	0
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_CFI_MASK		0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_CFI_SHIFT		12
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_PRIORITY_MASK	0x7
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_PRIORITY_SHIFT	13
	__le16 physical_q0;
	__le16 rec_rr_tov_समयr_val;
	काष्ठा fc_addr_nw s_id;
	u8 max_conc_seqs_c3;
	काष्ठा fc_addr_nw d_id;
	u8 flags;
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_CONT_INCR_SEQ_CNT_MASK	0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_CONT_INCR_SEQ_CNT_SHIFT	0
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_CONF_REQ_MASK		0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_CONF_REQ_SHIFT		1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_REC_VALID_MASK		0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_REC_VALID_SHIFT		2
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_VLAN_FLAG_MASK		0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_VLAN_FLAG_SHIFT		3
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_SINGLE_VLAN_MASK	0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_B_SINGLE_VLAN_SHIFT	4
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_MODE_MASK			0x3
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_MODE_SHIFT		5
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_RESERVED0_MASK		0x1
#घोषणा FCOE_CONN_OFFLOAD_RAMROD_DATA_RESERVED0_SHIFT		7
	__le16 conn_id;
	u8 def_q_idx;
	u8 reserved[5];
पूर्ण;

/* FCoE terminate connection request */
काष्ठा fcoe_conn_terminate_ramrod_data अणु
	काष्ठा regpair terminate_params_addr;
पूर्ण;

/* FCoE device type */
क्रमागत fcoe_device_type अणु
	FCOE_TASK_DEV_TYPE_DISK,
	FCOE_TASK_DEV_TYPE_TAPE,
	MAX_FCOE_DEVICE_TYPE
पूर्ण;

/* Data sgl */
काष्ठा fcoe_fast_sgl_ctx अणु
	काष्ठा regpair sgl_start_addr;
	__le32 sgl_byte_offset;
	__le16 task_reuse_cnt;
	__le16 init_offset_in_first_sge;
पूर्ण;

/* FCoE firmware function init */
काष्ठा fcoe_init_func_ramrod_data अणु
	काष्ठा scsi_init_func_params func_params;
	काष्ठा scsi_init_func_queues q_params;
	__le16 mtu;
	__le16 sq_num_pages_in_pbl;
	__le32 reserved[3];
पूर्ण;

/* FCoE: Mode of the connection: Target or Initiator or both */
क्रमागत fcoe_mode_type अणु
	FCOE_INITIATOR_MODE = 0x0,
	FCOE_TARGET_MODE = 0x1,
	FCOE_BOTH_OR_NOT_CHOSEN = 0x3,
	MAX_FCOE_MODE_TYPE
पूर्ण;

/* Per PF FCoE receive path statistics - tStorm RAM काष्ठाure */
काष्ठा fcoe_rx_stat अणु
	काष्ठा regpair fcoe_rx_byte_cnt;
	काष्ठा regpair fcoe_rx_data_pkt_cnt;
	काष्ठा regpair fcoe_rx_xfer_pkt_cnt;
	काष्ठा regpair fcoe_rx_other_pkt_cnt;
	__le32 fcoe_silent_drop_pkt_cmdq_full_cnt;
	__le32 fcoe_silent_drop_pkt_rq_full_cnt;
	__le32 fcoe_silent_drop_pkt_crc_error_cnt;
	__le32 fcoe_silent_drop_pkt_task_invalid_cnt;
	__le32 fcoe_silent_drop_total_pkt_cnt;
	__le32 rsrv;
पूर्ण;

/* FCoE SQE request type */
क्रमागत fcoe_sqe_request_type अणु
	SEND_FCOE_CMD,
	SEND_FCOE_MIDPATH,
	SEND_FCOE_ABTS_REQUEST,
	FCOE_EXCHANGE_CLEANUP,
	FCOE_SEQUENCE_RECOVERY,
	SEND_FCOE_XFER_RDY,
	SEND_FCOE_RSP,
	SEND_FCOE_RSP_WITH_SENSE_DATA,
	SEND_FCOE_TARGET_DATA,
	SEND_FCOE_INITIATOR_DATA,
	SEND_FCOE_XFER_CONTINUATION_RDY,
	SEND_FCOE_TARGET_ABTS_RSP,
	MAX_FCOE_SQE_REQUEST_TYPE
पूर्ण;

/* FCoe statistics request */
काष्ठा fcoe_stat_ramrod_data अणु
	काष्ठा regpair stat_params_addr;
पूर्ण;

/* FCoE task type */
क्रमागत fcoe_task_type अणु
	FCOE_TASK_TYPE_WRITE_INITIATOR,
	FCOE_TASK_TYPE_READ_INITIATOR,
	FCOE_TASK_TYPE_MIDPATH,
	FCOE_TASK_TYPE_UNSOLICITED,
	FCOE_TASK_TYPE_ABTS,
	FCOE_TASK_TYPE_EXCHANGE_CLEANUP,
	FCOE_TASK_TYPE_SEQUENCE_CLEANUP,
	FCOE_TASK_TYPE_WRITE_TARGET,
	FCOE_TASK_TYPE_READ_TARGET,
	FCOE_TASK_TYPE_RSP,
	FCOE_TASK_TYPE_RSP_SENSE_DATA,
	FCOE_TASK_TYPE_ABTS_TARGET,
	FCOE_TASK_TYPE_ENUM_SIZE,
	MAX_FCOE_TASK_TYPE
पूर्ण;

/* Per PF FCoE transmit path statistics - pStorm RAM काष्ठाure */
काष्ठा fcoe_tx_stat अणु
	काष्ठा regpair fcoe_tx_byte_cnt;
	काष्ठा regpair fcoe_tx_data_pkt_cnt;
	काष्ठा regpair fcoe_tx_xfer_pkt_cnt;
	काष्ठा regpair fcoe_tx_other_pkt_cnt;
पूर्ण;

/* FCoE SQ/XferQ element */
काष्ठा fcoe_wqe अणु
	__le16 task_id;
	__le16 flags;
#घोषणा FCOE_WQE_REQ_TYPE_MASK		0xF
#घोषणा FCOE_WQE_REQ_TYPE_SHIFT		0
#घोषणा FCOE_WQE_SGL_MODE_MASK		0x1
#घोषणा FCOE_WQE_SGL_MODE_SHIFT		4
#घोषणा FCOE_WQE_CONTINUATION_MASK	0x1
#घोषणा FCOE_WQE_CONTINUATION_SHIFT	5
#घोषणा FCOE_WQE_SEND_AUTO_RSP_MASK	0x1
#घोषणा FCOE_WQE_SEND_AUTO_RSP_SHIFT	6
#घोषणा FCOE_WQE_RESERVED_MASK		0x1
#घोषणा FCOE_WQE_RESERVED_SHIFT		7
#घोषणा FCOE_WQE_NUM_SGES_MASK		0xF
#घोषणा FCOE_WQE_NUM_SGES_SHIFT		8
#घोषणा FCOE_WQE_RESERVED1_MASK		0xF
#घोषणा FCOE_WQE_RESERVED1_SHIFT	12
	जोड़ fcoe_additional_info_जोड़ additional_info_जोड़;
पूर्ण;

/* FCoE XFRQ element */
काष्ठा xfrqe_prot_flags अणु
	u8 flags;
#घोषणा XFRQE_PROT_FLAGS_PROT_INTERVAL_SIZE_LOG_MASK	0xF
#घोषणा XFRQE_PROT_FLAGS_PROT_INTERVAL_SIZE_LOG_SHIFT	0
#घोषणा XFRQE_PROT_FLAGS_DIF_TO_PEER_MASK		0x1
#घोषणा XFRQE_PROT_FLAGS_DIF_TO_PEER_SHIFT		4
#घोषणा XFRQE_PROT_FLAGS_HOST_INTERFACE_MASK		0x3
#घोषणा XFRQE_PROT_FLAGS_HOST_INTERFACE_SHIFT		5
#घोषणा XFRQE_PROT_FLAGS_RESERVED_MASK			0x1
#घोषणा XFRQE_PROT_FLAGS_RESERVED_SHIFT			7
पूर्ण;

/* FCoE करोorbell data */
काष्ठा fcoe_db_data अणु
	u8 params;
#घोषणा FCOE_DB_DATA_DEST_MASK		0x3
#घोषणा FCOE_DB_DATA_DEST_SHIFT		0
#घोषणा FCOE_DB_DATA_AGG_CMD_MASK	0x3
#घोषणा FCOE_DB_DATA_AGG_CMD_SHIFT	2
#घोषणा FCOE_DB_DATA_BYPASS_EN_MASK	0x1
#घोषणा FCOE_DB_DATA_BYPASS_EN_SHIFT	4
#घोषणा FCOE_DB_DATA_RESERVED_MASK	0x1
#घोषणा FCOE_DB_DATA_RESERVED_SHIFT	5
#घोषणा FCOE_DB_DATA_AGG_VAL_SEL_MASK	0x3
#घोषणा FCOE_DB_DATA_AGG_VAL_SEL_SHIFT	6
	u8 agg_flags;
	__le16 sq_prod;
पूर्ण;

#पूर्ण_अगर /* __FCOE_COMMON__ */
