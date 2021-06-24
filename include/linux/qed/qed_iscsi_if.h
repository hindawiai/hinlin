<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_ISCSI_IF_H
#घोषणा _QED_ISCSI_IF_H
#समावेश <linux/types.h>
#समावेश <linux/qed/qed_अगर.h>

प्रकार पूर्णांक (*iscsi_event_cb_t) (व्योम *context,
				 u8 fw_event_code, व्योम *fw_handle);
काष्ठा qed_iscsi_stats अणु
	u64 iscsi_rx_bytes_cnt;
	u64 iscsi_rx_packet_cnt;
	u64 iscsi_rx_new_ooo_isle_events_cnt;
	u32 iscsi_cmdq_threshold_cnt;
	u32 iscsi_rq_threshold_cnt;
	u32 iscsi_immq_threshold_cnt;

	u64 iscsi_rx_dropped_pdus_task_not_valid;

	u64 iscsi_rx_data_pdu_cnt;
	u64 iscsi_rx_r2t_pdu_cnt;
	u64 iscsi_rx_total_pdu_cnt;

	u64 iscsi_tx_go_to_slow_start_event_cnt;
	u64 iscsi_tx_fast_retransmit_event_cnt;

	u64 iscsi_tx_data_pdu_cnt;
	u64 iscsi_tx_r2t_pdu_cnt;
	u64 iscsi_tx_total_pdu_cnt;

	u64 iscsi_tx_bytes_cnt;
	u64 iscsi_tx_packet_cnt;
पूर्ण;

काष्ठा qed_dev_iscsi_info अणु
	काष्ठा qed_dev_info common;

	व्योम __iomem *primary_dbq_rq_addr;
	व्योम __iomem *secondary_bdq_rq_addr;

	u8 num_cqs;
पूर्ण;

काष्ठा qed_iscsi_id_params अणु
	u8 mac[ETH_ALEN];
	u32 ip[4];
	u16 port;
पूर्ण;

काष्ठा qed_iscsi_params_offload अणु
	u8 layer_code;
	dma_addr_t sq_pbl_addr;
	u32 initial_ack;

	काष्ठा qed_iscsi_id_params src;
	काष्ठा qed_iscsi_id_params dst;
	u16 vlan_id;
	u8 tcp_flags;
	u8 ip_version;
	u8 शेष_cq;

	u8 ka_max_probe_cnt;
	u8 dup_ack_theshold;
	u32 rcv_next;
	u32 snd_una;
	u32 snd_next;
	u32 snd_max;
	u32 snd_wnd;
	u32 rcv_wnd;
	u32 snd_wl1;
	u32 cwnd;
	u32 ss_thresh;
	u16 srtt;
	u16 rtt_var;
	u32 ts_recent;
	u32 ts_recent_age;
	u32 total_rt;
	u32 ka_समयout_delta;
	u32 rt_समयout_delta;
	u8 dup_ack_cnt;
	u8 snd_wnd_probe_cnt;
	u8 ka_probe_cnt;
	u8 rt_cnt;
	u32 flow_label;
	u32 ka_समयout;
	u32 ka_पूर्णांकerval;
	u32 max_rt_समय;
	u32 initial_rcv_wnd;
	u8 ttl;
	u8 tos_or_tc;
	u16 remote_port;
	u16 local_port;
	u16 mss;
	u8 snd_wnd_scale;
	u8 rcv_wnd_scale;
	u16 da_समयout_value;
	u8 ack_frequency;
पूर्ण;

काष्ठा qed_iscsi_params_update अणु
	u8 update_flag;
#घोषणा QED_ISCSI_CONN_HD_EN            BIT(0)
#घोषणा QED_ISCSI_CONN_DD_EN            BIT(1)
#घोषणा QED_ISCSI_CONN_INITIAL_R2T      BIT(2)
#घोषणा QED_ISCSI_CONN_IMMEDIATE_DATA   BIT(3)

	u32 max_seq_size;
	u32 max_recv_pdu_length;
	u32 max_send_pdu_length;
	u32 first_seq_length;
	u32 exp_stat_sn;
पूर्ण;

#घोषणा MAX_TID_BLOCKS_ISCSI (512)
काष्ठा qed_iscsi_tid अणु
	u32 size;		/* In bytes per task */
	u32 num_tids_per_block;
	u8 *blocks[MAX_TID_BLOCKS_ISCSI];
पूर्ण;

काष्ठा qed_iscsi_cb_ops अणु
	काष्ठा qed_common_cb_ops common;
पूर्ण;

/**
 * काष्ठा qed_iscsi_ops - qed iSCSI operations.
 * @common:		common operations poपूर्णांकer
 * @ll2:		light L2 operations poपूर्णांकer
 * @fill_dev_info:	fills iSCSI specअगरic inक्रमmation
 *			@param cdev
 *			@param info
 *			@वापस 0 on sucesss, otherwise error value.
 * @रेजिस्टर_ops:	रेजिस्टर iscsi operations
 *			@param cdev
 *			@param ops - specअगरied using qed_iscsi_cb_ops
 *			@param cookie - driver निजी
 * @start:		iscsi in FW
 *			@param cdev
 *			@param tasks - qed will fill inक्रमmation about tasks
 *			वापस 0 on success, otherwise error value.
 * @stop:		iscsi in FW
 *			@param cdev
 *			वापस 0 on success, otherwise error value.
 * @acquire_conn:	acquire a new iscsi connection
 *			@param cdev
 *			@param handle - qed will fill handle that should be
 *				used henceक्रमth as identअगरier of the
 *				connection.
 *			@param p_करोorbell - qed will fill the address of the
 *				करोorbell.
 *			@वापस 0 on sucesss, otherwise error value.
 * @release_conn:	release a previously acquired iscsi connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			@वापस 0 on success, otherwise error value.
 * @offload_conn:	configures an offloaded connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			@param conn_info - the configuration to use क्रम the
 *				offload.
 *			@वापस 0 on success, otherwise error value.
 * @update_conn:	updates an offloaded connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			@param conn_info - the configuration to use क्रम the
 *				offload.
 *			@वापस 0 on success, otherwise error value.
 * @destroy_conn:	stops an offloaded connection
 *			@param cdev
 *			@param handle - the connection handle.
 *			@वापस 0 on success, otherwise error value.
 * @clear_sq:		clear all task in sq
 *			@param cdev
 *			@param handle - the connection handle.
 *			@वापस 0 on success, otherwise error value.
 * @get_stats:		iSCSI related statistics
 *			@param cdev
 *			@param stats - poपूर्णांकer to struck that would be filled
 *				we stats
 *			@वापस 0 on success, error otherwise.
 * @change_mac		Change MAC of पूर्णांकerface
 *			@param cdev
 *			@param handle - the connection handle.
 *			@param mac - new MAC to configure.
 *			@वापस 0 on success, otherwise error value.
 */
काष्ठा qed_iscsi_ops अणु
	स्थिर काष्ठा qed_common_ops *common;

	स्थिर काष्ठा qed_ll2_ops *ll2;

	पूर्णांक (*fill_dev_info)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_dev_iscsi_info *info);

	व्योम (*रेजिस्टर_ops)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_iscsi_cb_ops *ops, व्योम *cookie);

	पूर्णांक (*start)(काष्ठा qed_dev *cdev,
		     काष्ठा qed_iscsi_tid *tasks,
		     व्योम *event_context, iscsi_event_cb_t async_event_cb);

	पूर्णांक (*stop)(काष्ठा qed_dev *cdev);

	पूर्णांक (*acquire_conn)(काष्ठा qed_dev *cdev,
			    u32 *handle,
			    u32 *fw_cid, व्योम __iomem **p_करोorbell);

	पूर्णांक (*release_conn)(काष्ठा qed_dev *cdev, u32 handle);

	पूर्णांक (*offload_conn)(काष्ठा qed_dev *cdev,
			    u32 handle,
			    काष्ठा qed_iscsi_params_offload *conn_info);

	पूर्णांक (*update_conn)(काष्ठा qed_dev *cdev,
			   u32 handle,
			   काष्ठा qed_iscsi_params_update *conn_info);

	पूर्णांक (*destroy_conn)(काष्ठा qed_dev *cdev, u32 handle, u8 abrt_conn);

	पूर्णांक (*clear_sq)(काष्ठा qed_dev *cdev, u32 handle);

	पूर्णांक (*get_stats)(काष्ठा qed_dev *cdev,
			 काष्ठा qed_iscsi_stats *stats);

	पूर्णांक (*change_mac)(काष्ठा qed_dev *cdev, u32 handle, स्थिर u8 *mac);
पूर्ण;

स्थिर काष्ठा qed_iscsi_ops *qed_get_iscsi_ops(व्योम);
व्योम qed_put_iscsi_ops(व्योम);
#पूर्ण_अगर
