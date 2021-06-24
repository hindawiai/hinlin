<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* Copyright (c) 2019-2020 Marvell International Ltd. */

#अगर_अघोषित _QED_FCOE_IF_H
#घोषणा _QED_FCOE_IF_H
#समावेश <linux/types.h>
#समावेश <linux/qed/qed_अगर.h>
काष्ठा qed_fcoe_stats अणु
	u64 fcoe_rx_byte_cnt;
	u64 fcoe_rx_data_pkt_cnt;
	u64 fcoe_rx_xfer_pkt_cnt;
	u64 fcoe_rx_other_pkt_cnt;
	u32 fcoe_silent_drop_pkt_cmdq_full_cnt;
	u32 fcoe_silent_drop_pkt_rq_full_cnt;
	u32 fcoe_silent_drop_pkt_crc_error_cnt;
	u32 fcoe_silent_drop_pkt_task_invalid_cnt;
	u32 fcoe_silent_drop_total_pkt_cnt;

	u64 fcoe_tx_byte_cnt;
	u64 fcoe_tx_data_pkt_cnt;
	u64 fcoe_tx_xfer_pkt_cnt;
	u64 fcoe_tx_other_pkt_cnt;
पूर्ण;

काष्ठा qed_dev_fcoe_info अणु
	काष्ठा qed_dev_info common;

	व्योम __iomem *primary_dbq_rq_addr;
	व्योम __iomem *secondary_bdq_rq_addr;

	u64 wwpn;
	u64 wwnn;

	u8 num_cqs;
पूर्ण;

काष्ठा qed_fcoe_params_offload अणु
	dma_addr_t sq_pbl_addr;
	dma_addr_t sq_curr_page_addr;
	dma_addr_t sq_next_page_addr;

	u8 src_mac[ETH_ALEN];
	u8 dst_mac[ETH_ALEN];

	u16 tx_max_fc_pay_len;
	u16 e_d_tov_समयr_val;
	u16 rec_tov_समयr_val;
	u16 rx_max_fc_pay_len;
	u16 vlan_tag;

	काष्ठा fc_addr_nw s_id;
	u8 max_conc_seqs_c3;
	काष्ठा fc_addr_nw d_id;
	u8 flags;
	u8 def_q_idx;
पूर्ण;

#घोषणा MAX_TID_BLOCKS_FCOE (512)
काष्ठा qed_fcoe_tid अणु
	u32 size;		/* In bytes per task */
	u32 num_tids_per_block;
	u8 *blocks[MAX_TID_BLOCKS_FCOE];
पूर्ण;

काष्ठा qed_fcoe_cb_ops अणु
	काष्ठा qed_common_cb_ops common;
	 u32 (*get_login_failures)(व्योम *cookie);
पूर्ण;

व्योम qed_fcoe_set_pf_params(काष्ठा qed_dev *cdev,
			    काष्ठा qed_fcoe_pf_params *params);

/**
 * काष्ठा qed_fcoe_ops - qed FCoE operations.
 * @common:		common operations poपूर्णांकer
 * @fill_dev_info:	fills FCoE specअगरic inक्रमmation
 *			@param cdev
 *			@param info
 *			@वापस 0 on sucesss, otherwise error value.
 * @रेजिस्टर_ops:	रेजिस्टर FCoE operations
 *			@param cdev
 *			@param ops - specअगरied using qed_iscsi_cb_ops
 *			@param cookie - driver निजी
 * @ll2:		light L2 operations poपूर्णांकer
 * @start:		fcoe in FW
 *			@param cdev
 *			@param tasks - qed will fill inक्रमmation about tasks
 *			वापस 0 on success, otherwise error value.
 * @stop:		stops fcoe in FW
 *			@param cdev
 *			वापस 0 on success, otherwise error value.
 * @acquire_conn:	acquire a new fcoe connection
 *			@param cdev
 *			@param handle - qed will fill handle that should be
 *				used henceक्रमth as identअगरier of the
 *				connection.
 *			@param p_करोorbell - qed will fill the address of the
 *				करोorbell.
 *			वापस 0 on sucesss, otherwise error value.
 * @release_conn:	release a previously acquired fcoe connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			वापस 0 on success, otherwise error value.
 * @offload_conn:	configures an offloaded connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			@param conn_info - the configuration to use क्रम the
 *				offload.
 *			वापस 0 on success, otherwise error value.
 * @destroy_conn:	stops an offloaded connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			@param terminate_params
 *			वापस 0 on success, otherwise error value.
 * @get_stats:		माला_लो FCoE related statistics
 *			@param cdev
 *			@param stats - poपूर्णांकer to struck that would be filled
 *				we stats
 *			वापस 0 on success, error otherwise.
 */
काष्ठा qed_fcoe_ops अणु
	स्थिर काष्ठा qed_common_ops *common;

	पूर्णांक (*fill_dev_info)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_dev_fcoe_info *info);

	व्योम (*रेजिस्टर_ops)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_fcoe_cb_ops *ops, व्योम *cookie);

	स्थिर काष्ठा qed_ll2_ops *ll2;

	पूर्णांक (*start)(काष्ठा qed_dev *cdev, काष्ठा qed_fcoe_tid *tasks);

	पूर्णांक (*stop)(काष्ठा qed_dev *cdev);

	पूर्णांक (*acquire_conn)(काष्ठा qed_dev *cdev,
			    u32 *handle,
			    u32 *fw_cid, व्योम __iomem **p_करोorbell);

	पूर्णांक (*release_conn)(काष्ठा qed_dev *cdev, u32 handle);

	पूर्णांक (*offload_conn)(काष्ठा qed_dev *cdev,
			    u32 handle,
			    काष्ठा qed_fcoe_params_offload *conn_info);
	पूर्णांक (*destroy_conn)(काष्ठा qed_dev *cdev,
			    u32 handle, dma_addr_t terminate_params);

	पूर्णांक (*get_stats)(काष्ठा qed_dev *cdev, काष्ठा qed_fcoe_stats *stats);
पूर्ण;

स्थिर काष्ठा qed_fcoe_ops *qed_get_fcoe_ops(व्योम);
व्योम qed_put_fcoe_ops(व्योम);
#पूर्ण_अगर
