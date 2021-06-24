<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_IF_H
#घोषणा _QED_IF_H

#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पन.स>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/common_hsi.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <net/devlink.h>

क्रमागत dcbx_protocol_type अणु
	DCBX_PROTOCOL_ISCSI,
	DCBX_PROTOCOL_FCOE,
	DCBX_PROTOCOL_ROCE,
	DCBX_PROTOCOL_ROCE_V2,
	DCBX_PROTOCOL_ETH,
	DCBX_MAX_PROTOCOL_TYPE
पूर्ण;

#घोषणा QED_ROCE_PROTOCOL_INDEX (3)

#घोषणा QED_LLDP_CHASSIS_ID_STAT_LEN 4
#घोषणा QED_LLDP_PORT_ID_STAT_LEN 4
#घोषणा QED_DCBX_MAX_APP_PROTOCOL 32
#घोषणा QED_MAX_PFC_PRIORITIES 8
#घोषणा QED_DCBX_DSCP_SIZE 64

काष्ठा qed_dcbx_lldp_remote अणु
	u32 peer_chassis_id[QED_LLDP_CHASSIS_ID_STAT_LEN];
	u32 peer_port_id[QED_LLDP_PORT_ID_STAT_LEN];
	bool enable_rx;
	bool enable_tx;
	u32 tx_पूर्णांकerval;
	u32 max_credit;
पूर्ण;

काष्ठा qed_dcbx_lldp_local अणु
	u32 local_chassis_id[QED_LLDP_CHASSIS_ID_STAT_LEN];
	u32 local_port_id[QED_LLDP_PORT_ID_STAT_LEN];
पूर्ण;

काष्ठा qed_dcbx_app_prio अणु
	u8 roce;
	u8 roce_v2;
	u8 fcoe;
	u8 iscsi;
	u8 eth;
पूर्ण;

काष्ठा qed_dbcx_pfc_params अणु
	bool willing;
	bool enabled;
	u8 prio[QED_MAX_PFC_PRIORITIES];
	u8 max_tc;
पूर्ण;

क्रमागत qed_dcbx_sf_ieee_type अणु
	QED_DCBX_SF_IEEE_ETHTYPE,
	QED_DCBX_SF_IEEE_TCP_PORT,
	QED_DCBX_SF_IEEE_UDP_PORT,
	QED_DCBX_SF_IEEE_TCP_UDP_PORT
पूर्ण;

काष्ठा qed_app_entry अणु
	bool ethtype;
	क्रमागत qed_dcbx_sf_ieee_type sf_ieee;
	bool enabled;
	u8 prio;
	u16 proto_id;
	क्रमागत dcbx_protocol_type proto_type;
पूर्ण;

काष्ठा qed_dcbx_params अणु
	काष्ठा qed_app_entry app_entry[QED_DCBX_MAX_APP_PROTOCOL];
	u16 num_app_entries;
	bool app_willing;
	bool app_valid;
	bool app_error;
	bool ets_willing;
	bool ets_enabled;
	bool ets_cbs;
	bool valid;
	u8 ets_pri_tc_tbl[QED_MAX_PFC_PRIORITIES];
	u8 ets_tc_bw_tbl[QED_MAX_PFC_PRIORITIES];
	u8 ets_tc_tsa_tbl[QED_MAX_PFC_PRIORITIES];
	काष्ठा qed_dbcx_pfc_params pfc;
	u8 max_ets_tc;
पूर्ण;

काष्ठा qed_dcbx_admin_params अणु
	काष्ठा qed_dcbx_params params;
	bool valid;
पूर्ण;

काष्ठा qed_dcbx_remote_params अणु
	काष्ठा qed_dcbx_params params;
	bool valid;
पूर्ण;

काष्ठा qed_dcbx_operational_params अणु
	काष्ठा qed_dcbx_app_prio app_prio;
	काष्ठा qed_dcbx_params params;
	bool valid;
	bool enabled;
	bool ieee;
	bool cee;
	bool local;
	u32 err;
पूर्ण;

काष्ठा qed_dcbx_get अणु
	काष्ठा qed_dcbx_operational_params operational;
	काष्ठा qed_dcbx_lldp_remote lldp_remote;
	काष्ठा qed_dcbx_lldp_local lldp_local;
	काष्ठा qed_dcbx_remote_params remote;
	काष्ठा qed_dcbx_admin_params local;
पूर्ण;

क्रमागत qed_nvm_images अणु
	QED_NVM_IMAGE_ISCSI_CFG,
	QED_NVM_IMAGE_FCOE_CFG,
	QED_NVM_IMAGE_MDUMP,
	QED_NVM_IMAGE_NVM_CFG1,
	QED_NVM_IMAGE_DEFAULT_CFG,
	QED_NVM_IMAGE_NVM_META,
पूर्ण;

काष्ठा qed_link_eee_params अणु
	u32 tx_lpi_समयr;
#घोषणा QED_EEE_1G_ADV		BIT(0)
#घोषणा QED_EEE_10G_ADV		BIT(1)

	/* Capabilities are represented using QED_EEE_*_ADV values */
	u8 adv_caps;
	u8 lp_adv_caps;
	bool enable;
	bool tx_lpi_enable;
पूर्ण;

क्रमागत qed_led_mode अणु
	QED_LED_MODE_OFF,
	QED_LED_MODE_ON,
	QED_LED_MODE_RESTORE
पूर्ण;

काष्ठा qed_mfw_tlv_eth अणु
	u16 lso_maxoff_size;
	bool lso_maxoff_size_set;
	u16 lso_minseg_size;
	bool lso_minseg_size_set;
	u8 prom_mode;
	bool prom_mode_set;
	u16 tx_descr_size;
	bool tx_descr_size_set;
	u16 rx_descr_size;
	bool rx_descr_size_set;
	u16 netq_count;
	bool netq_count_set;
	u32 tcp4_offloads;
	bool tcp4_offloads_set;
	u32 tcp6_offloads;
	bool tcp6_offloads_set;
	u16 tx_descr_qdepth;
	bool tx_descr_qdepth_set;
	u16 rx_descr_qdepth;
	bool rx_descr_qdepth_set;
	u8 iov_offload;
#घोषणा QED_MFW_TLV_IOV_OFFLOAD_NONE            (0)
#घोषणा QED_MFW_TLV_IOV_OFFLOAD_MULTIQUEUE      (1)
#घोषणा QED_MFW_TLV_IOV_OFFLOAD_VEB             (2)
#घोषणा QED_MFW_TLV_IOV_OFFLOAD_VEPA            (3)
	bool iov_offload_set;
	u8 txqs_empty;
	bool txqs_empty_set;
	u8 rxqs_empty;
	bool rxqs_empty_set;
	u8 num_txqs_full;
	bool num_txqs_full_set;
	u8 num_rxqs_full;
	bool num_rxqs_full_set;
पूर्ण;

#घोषणा QED_MFW_TLV_TIME_SIZE	14
काष्ठा qed_mfw_tlv_समय अणु
	bool b_set;
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	u16 msec;
	u16 usec;
पूर्ण;

काष्ठा qed_mfw_tlv_fcoe अणु
	u8 scsi_समयout;
	bool scsi_समयout_set;
	u32 rt_tov;
	bool rt_tov_set;
	u32 ra_tov;
	bool ra_tov_set;
	u32 ed_tov;
	bool ed_tov_set;
	u32 cr_tov;
	bool cr_tov_set;
	u8 boot_type;
	bool boot_type_set;
	u8 npiv_state;
	bool npiv_state_set;
	u32 num_npiv_ids;
	bool num_npiv_ids_set;
	u8 चयन_name[8];
	bool चयन_name_set;
	u16 चयन_portnum;
	bool चयन_portnum_set;
	u8 चयन_portid[3];
	bool चयन_portid_set;
	u8 venकरोr_name[8];
	bool venकरोr_name_set;
	u8 चयन_model[8];
	bool चयन_model_set;
	u8 चयन_fw_version[8];
	bool चयन_fw_version_set;
	u8 qos_pri;
	bool qos_pri_set;
	u8 port_alias[3];
	bool port_alias_set;
	u8 port_state;
#घोषणा QED_MFW_TLV_PORT_STATE_OFFLINE  (0)
#घोषणा QED_MFW_TLV_PORT_STATE_LOOP             (1)
#घोषणा QED_MFW_TLV_PORT_STATE_P2P              (2)
#घोषणा QED_MFW_TLV_PORT_STATE_FABRIC           (3)
	bool port_state_set;
	u16 fip_tx_descr_size;
	bool fip_tx_descr_size_set;
	u16 fip_rx_descr_size;
	bool fip_rx_descr_size_set;
	u16 link_failures;
	bool link_failures_set;
	u8 fcoe_boot_progress;
	bool fcoe_boot_progress_set;
	u64 rx_bcast;
	bool rx_bcast_set;
	u64 tx_bcast;
	bool tx_bcast_set;
	u16 fcoe_txq_depth;
	bool fcoe_txq_depth_set;
	u16 fcoe_rxq_depth;
	bool fcoe_rxq_depth_set;
	u64 fcoe_rx_frames;
	bool fcoe_rx_frames_set;
	u64 fcoe_rx_bytes;
	bool fcoe_rx_bytes_set;
	u64 fcoe_tx_frames;
	bool fcoe_tx_frames_set;
	u64 fcoe_tx_bytes;
	bool fcoe_tx_bytes_set;
	u16 crc_count;
	bool crc_count_set;
	u32 crc_err_src_fcid[5];
	bool crc_err_src_fcid_set[5];
	काष्ठा qed_mfw_tlv_समय crc_err[5];
	u16 losync_err;
	bool losync_err_set;
	u16 losig_err;
	bool losig_err_set;
	u16 primtive_err;
	bool primtive_err_set;
	u16 disparity_err;
	bool disparity_err_set;
	u16 code_violation_err;
	bool code_violation_err_set;
	u32 flogi_param[4];
	bool flogi_param_set[4];
	काष्ठा qed_mfw_tlv_समय flogi_tstamp;
	u32 flogi_acc_param[4];
	bool flogi_acc_param_set[4];
	काष्ठा qed_mfw_tlv_समय flogi_acc_tstamp;
	u32 flogi_rjt;
	bool flogi_rjt_set;
	काष्ठा qed_mfw_tlv_समय flogi_rjt_tstamp;
	u32 fdiscs;
	bool fdiscs_set;
	u8 fdisc_acc;
	bool fdisc_acc_set;
	u8 fdisc_rjt;
	bool fdisc_rjt_set;
	u8 plogi;
	bool plogi_set;
	u8 plogi_acc;
	bool plogi_acc_set;
	u8 plogi_rjt;
	bool plogi_rjt_set;
	u32 plogi_dst_fcid[5];
	bool plogi_dst_fcid_set[5];
	काष्ठा qed_mfw_tlv_समय plogi_tstamp[5];
	u32 plogi_acc_src_fcid[5];
	bool plogi_acc_src_fcid_set[5];
	काष्ठा qed_mfw_tlv_समय plogi_acc_tstamp[5];
	u8 tx_plogos;
	bool tx_plogos_set;
	u8 plogo_acc;
	bool plogo_acc_set;
	u8 plogo_rjt;
	bool plogo_rjt_set;
	u32 plogo_src_fcid[5];
	bool plogo_src_fcid_set[5];
	काष्ठा qed_mfw_tlv_समय plogo_tstamp[5];
	u8 rx_logos;
	bool rx_logos_set;
	u8 tx_accs;
	bool tx_accs_set;
	u8 tx_prlis;
	bool tx_prlis_set;
	u8 rx_accs;
	bool rx_accs_set;
	u8 tx_abts;
	bool tx_abts_set;
	u8 rx_abts_acc;
	bool rx_abts_acc_set;
	u8 rx_abts_rjt;
	bool rx_abts_rjt_set;
	u32 abts_dst_fcid[5];
	bool abts_dst_fcid_set[5];
	काष्ठा qed_mfw_tlv_समय abts_tstamp[5];
	u8 rx_rscn;
	bool rx_rscn_set;
	u32 rx_rscn_nport[4];
	bool rx_rscn_nport_set[4];
	u8 tx_lun_rst;
	bool tx_lun_rst_set;
	u8 पात_task_sets;
	bool पात_task_sets_set;
	u8 tx_tprlos;
	bool tx_tprlos_set;
	u8 tx_nos;
	bool tx_nos_set;
	u8 rx_nos;
	bool rx_nos_set;
	u8 ols;
	bool ols_set;
	u8 lr;
	bool lr_set;
	u8 lrr;
	bool lrr_set;
	u8 tx_lip;
	bool tx_lip_set;
	u8 rx_lip;
	bool rx_lip_set;
	u8 eofa;
	bool eofa_set;
	u8 eofni;
	bool eofni_set;
	u8 scsi_chks;
	bool scsi_chks_set;
	u8 scsi_cond_met;
	bool scsi_cond_met_set;
	u8 scsi_busy;
	bool scsi_busy_set;
	u8 scsi_पूर्णांकer;
	bool scsi_पूर्णांकer_set;
	u8 scsi_पूर्णांकer_cond_met;
	bool scsi_पूर्णांकer_cond_met_set;
	u8 scsi_rsv_conflicts;
	bool scsi_rsv_conflicts_set;
	u8 scsi_tsk_full;
	bool scsi_tsk_full_set;
	u8 scsi_aca_active;
	bool scsi_aca_active_set;
	u8 scsi_tsk_पात;
	bool scsi_tsk_पात_set;
	u32 scsi_rx_chk[5];
	bool scsi_rx_chk_set[5];
	काष्ठा qed_mfw_tlv_समय scsi_chk_tstamp[5];
पूर्ण;

काष्ठा qed_mfw_tlv_iscsi अणु
	u8 target_llmnr;
	bool target_llmnr_set;
	u8 header_digest;
	bool header_digest_set;
	u8 data_digest;
	bool data_digest_set;
	u8 auth_method;
#घोषणा QED_MFW_TLV_AUTH_METHOD_NONE            (1)
#घोषणा QED_MFW_TLV_AUTH_METHOD_CHAP            (2)
#घोषणा QED_MFW_TLV_AUTH_METHOD_MUTUAL_CHAP     (3)
	bool auth_method_set;
	u16 boot_taget_portal;
	bool boot_taget_portal_set;
	u16 frame_size;
	bool frame_size_set;
	u16 tx_desc_size;
	bool tx_desc_size_set;
	u16 rx_desc_size;
	bool rx_desc_size_set;
	u8 boot_progress;
	bool boot_progress_set;
	u16 tx_desc_qdepth;
	bool tx_desc_qdepth_set;
	u16 rx_desc_qdepth;
	bool rx_desc_qdepth_set;
	u64 rx_frames;
	bool rx_frames_set;
	u64 rx_bytes;
	bool rx_bytes_set;
	u64 tx_frames;
	bool tx_frames_set;
	u64 tx_bytes;
	bool tx_bytes_set;
पूर्ण;

क्रमागत qed_db_rec_width अणु
	DB_REC_WIDTH_32B,
	DB_REC_WIDTH_64B,
पूर्ण;

क्रमागत qed_db_rec_space अणु
	DB_REC_KERNEL,
	DB_REC_USER,
पूर्ण;

#घोषणा सूचीECT_REG_WR(reg_addr, val) ग_लिखोl((u32)val, \
					    (व्योम __iomem *)(reg_addr))

#घोषणा सूचीECT_REG_RD(reg_addr) पढ़ोl((व्योम __iomem *)(reg_addr))

#घोषणा सूचीECT_REG_WR64(reg_addr, val) ग_लिखोq((u64)val,	\
					      (व्योम __iomem *)(reg_addr))

#घोषणा QED_COALESCE_MAX 0x1FF
#घोषणा QED_DEFAULT_RX_USECS 12
#घोषणा QED_DEFAULT_TX_USECS 48

/* क्रमward */
काष्ठा qed_dev;

काष्ठा qed_eth_pf_params अणु
	/* The following parameters are used during HW-init
	 * and these parameters need to be passed as arguments
	 * to update_pf_params routine invoked beक्रमe slowpath start
	 */
	u16 num_cons;

	/* per-VF number of CIDs */
	u8 num_vf_cons;
#घोषणा ETH_PF_PARAMS_VF_CONS_DEFAULT	(32)

	/* To enable arfs, previous to HW-init a positive number needs to be
	 * set [as filters require allocated searcher ILT memory].
	 * This will set the maximal number of configured steering-filters.
	 */
	u32 num_arfs_filters;
पूर्ण;

काष्ठा qed_fcoe_pf_params अणु
	/* The following parameters are used during protocol-init */
	u64 glbl_q_params_addr;
	u64 bdq_pbl_base_addr[2];

	/* The following parameters are used during HW-init
	 * and these parameters need to be passed as arguments
	 * to update_pf_params routine invoked beक्रमe slowpath start
	 */
	u16 num_cons;
	u16 num_tasks;

	/* The following parameters are used during protocol-init */
	u16 sq_num_pbl_pages;

	u16 cq_num_entries;
	u16 cmdq_num_entries;
	u16 rq_buffer_log_size;
	u16 mtu;
	u16 dummy_icid;
	u16 bdq_xoff_threshold[2];
	u16 bdq_xon_threshold[2];
	u16 rq_buffer_size;
	u8 num_cqs;		/* num of global CQs */
	u8 log_page_size;
	u8 gl_rq_pi;
	u8 gl_cmd_pi;
	u8 debug_mode;
	u8 is_target;
	u8 bdq_pbl_num_entries[2];
पूर्ण;

/* Most of the parameters below are described in the FW iSCSI / TCP HSI */
काष्ठा qed_iscsi_pf_params अणु
	u64 glbl_q_params_addr;
	u64 bdq_pbl_base_addr[3];
	u16 cq_num_entries;
	u16 cmdq_num_entries;
	u32 two_msl_समयr;
	u16 tx_sws_समयr;

	/* The following parameters are used during HW-init
	 * and these parameters need to be passed as arguments
	 * to update_pf_params routine invoked beक्रमe slowpath start
	 */
	u16 num_cons;
	u16 num_tasks;

	/* The following parameters are used during protocol-init */
	u16 half_way_बंद_समयout;
	u16 bdq_xoff_threshold[3];
	u16 bdq_xon_threshold[3];
	u16 cmdq_xoff_threshold;
	u16 cmdq_xon_threshold;
	u16 rq_buffer_size;

	u8 num_sq_pages_in_ring;
	u8 num_r2tq_pages_in_ring;
	u8 num_uhq_pages_in_ring;
	u8 num_queues;
	u8 log_page_size;
	u8 rqe_log_size;
	u8 max_fin_rt;
	u8 gl_rq_pi;
	u8 gl_cmd_pi;
	u8 debug_mode;
	u8 ll2_ooo_queue_id;

	u8 is_target;
	u8 is_soc_en;
	u8 soc_num_of_blocks_log;
	u8 bdq_pbl_num_entries[3];
पूर्ण;

काष्ठा qed_rdma_pf_params अणु
	/* Supplied to QED during resource allocation (may affect the ILT and
	 * the करोorbell BAR).
	 */
	u32 min_dpis;		/* number of requested DPIs */
	u32 num_qps;		/* number of requested Queue Pairs */
	u32 num_srqs;		/* number of requested SRQ */
	u8 roce_edpm_mode;	/* see QED_ROCE_EDPM_MODE_ENABLE */
	u8 gl_pi;		/* protocol index */

	/* Will allocate rate limiters to be used with QPs */
	u8 enable_dcqcn;
पूर्ण;

काष्ठा qed_pf_params अणु
	काष्ठा qed_eth_pf_params eth_pf_params;
	काष्ठा qed_fcoe_pf_params fcoe_pf_params;
	काष्ठा qed_iscsi_pf_params iscsi_pf_params;
	काष्ठा qed_rdma_pf_params rdma_pf_params;
पूर्ण;

क्रमागत qed_पूर्णांक_mode अणु
	QED_INT_MODE_INTA,
	QED_INT_MODE_MSIX,
	QED_INT_MODE_MSI,
	QED_INT_MODE_POLL,
पूर्ण;

काष्ठा qed_sb_info अणु
	काष्ठा status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	u32 sb_ack; /* Last given ack */
	u16 igu_sb_id;
	व्योम __iomem *igu_addr;
	u8 flags;
#घोषणा QED_SB_INFO_INIT	0x1
#घोषणा QED_SB_INFO_SETUP	0x2

	काष्ठा qed_dev *cdev;
पूर्ण;

क्रमागत qed_hw_err_type अणु
	QED_HW_ERR_FAN_FAIL,
	QED_HW_ERR_MFW_RESP_FAIL,
	QED_HW_ERR_HW_ATTN,
	QED_HW_ERR_DMAE_FAIL,
	QED_HW_ERR_RAMROD_FAIL,
	QED_HW_ERR_FW_ASSERT,
	QED_HW_ERR_LAST,
पूर्ण;

क्रमागत qed_dev_type अणु
	QED_DEV_TYPE_BB,
	QED_DEV_TYPE_AH,
	QED_DEV_TYPE_E5,
पूर्ण;

काष्ठा qed_dev_info अणु
	अचिन्हित दीर्घ	pci_mem_start;
	अचिन्हित दीर्घ	pci_mem_end;
	अचिन्हित पूर्णांक	pci_irq;
	u8		num_hwfns;

	u8		hw_mac[ETH_ALEN];

	/* FW version */
	u16		fw_major;
	u16		fw_minor;
	u16		fw_rev;
	u16		fw_eng;

	/* MFW version */
	u32		mfw_rev;
#घोषणा QED_MFW_VERSION_0_MASK		0x000000FF
#घोषणा QED_MFW_VERSION_0_OFFSET	0
#घोषणा QED_MFW_VERSION_1_MASK		0x0000FF00
#घोषणा QED_MFW_VERSION_1_OFFSET	8
#घोषणा QED_MFW_VERSION_2_MASK		0x00FF0000
#घोषणा QED_MFW_VERSION_2_OFFSET	16
#घोषणा QED_MFW_VERSION_3_MASK		0xFF000000
#घोषणा QED_MFW_VERSION_3_OFFSET	24

	u32		flash_size;
	bool		b_arfs_capable;
	bool		b_पूर्णांकer_pf_चयन;
	bool		tx_चयनing;
	bool		rdma_supported;
	u16		mtu;

	bool wol_support;
	bool smart_an;

	/* MBI version */
	u32 mbi_version;
#घोषणा QED_MBI_VERSION_0_MASK		0x000000FF
#घोषणा QED_MBI_VERSION_0_OFFSET	0
#घोषणा QED_MBI_VERSION_1_MASK		0x0000FF00
#घोषणा QED_MBI_VERSION_1_OFFSET	8
#घोषणा QED_MBI_VERSION_2_MASK		0x00FF0000
#घोषणा QED_MBI_VERSION_2_OFFSET	16

	क्रमागत qed_dev_type dev_type;

	/* Output parameters क्रम qede */
	bool		vxlan_enable;
	bool		gre_enable;
	bool		geneve_enable;

	u8		असल_pf_id;
पूर्ण;

क्रमागत qed_sb_type अणु
	QED_SB_TYPE_L2_QUEUE,
	QED_SB_TYPE_CNQ,
	QED_SB_TYPE_STORAGE,
पूर्ण;

क्रमागत qed_protocol अणु
	QED_PROTOCOL_ETH,
	QED_PROTOCOL_ISCSI,
	QED_PROTOCOL_FCOE,
पूर्ण;

क्रमागत qed_fec_mode अणु
	QED_FEC_MODE_NONE			= BIT(0),
	QED_FEC_MODE_FIRECODE			= BIT(1),
	QED_FEC_MODE_RS				= BIT(2),
	QED_FEC_MODE_AUTO			= BIT(3),
	QED_FEC_MODE_UNSUPPORTED		= BIT(4),
पूर्ण;

काष्ठा qed_link_params अणु
	bool					link_up;

	u32					override_flags;
#घोषणा QED_LINK_OVERRIDE_SPEED_AUTONEG		BIT(0)
#घोषणा QED_LINK_OVERRIDE_SPEED_ADV_SPEEDS	BIT(1)
#घोषणा QED_LINK_OVERRIDE_SPEED_FORCED_SPEED	BIT(2)
#घोषणा QED_LINK_OVERRIDE_PAUSE_CONFIG		BIT(3)
#घोषणा QED_LINK_OVERRIDE_LOOPBACK_MODE		BIT(4)
#घोषणा QED_LINK_OVERRIDE_EEE_CONFIG		BIT(5)
#घोषणा QED_LINK_OVERRIDE_FEC_CONFIG		BIT(6)

	bool					स्वतःneg;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(adv_speeds);
	u32					क्रमced_speed;

	u32					छोड़ो_config;
#घोषणा QED_LINK_PAUSE_AUTONEG_ENABLE		BIT(0)
#घोषणा QED_LINK_PAUSE_RX_ENABLE		BIT(1)
#घोषणा QED_LINK_PAUSE_TX_ENABLE		BIT(2)

	u32					loopback_mode;
#घोषणा QED_LINK_LOOPBACK_NONE			BIT(0)
#घोषणा QED_LINK_LOOPBACK_INT_PHY		BIT(1)
#घोषणा QED_LINK_LOOPBACK_EXT_PHY		BIT(2)
#घोषणा QED_LINK_LOOPBACK_EXT			BIT(3)
#घोषणा QED_LINK_LOOPBACK_MAC			BIT(4)
#घोषणा QED_LINK_LOOPBACK_CNIG_AH_ONLY_0123	BIT(5)
#घोषणा QED_LINK_LOOPBACK_CNIG_AH_ONLY_2301	BIT(6)
#घोषणा QED_LINK_LOOPBACK_PCS_AH_ONLY		BIT(7)
#घोषणा QED_LINK_LOOPBACK_REVERSE_MAC_AH_ONLY	BIT(8)
#घोषणा QED_LINK_LOOPBACK_INT_PHY_FEA_AH_ONLY	BIT(9)

	काष्ठा qed_link_eee_params		eee;
	u32					fec;
पूर्ण;

काष्ठा qed_link_output अणु
	bool					link_up;

	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported_caps);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertised_caps);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(lp_caps);

	u32					speed;	   /* In Mb/s */
	u8					duplex;	   /* In DUPLEX defs */
	u8					port;	   /* In PORT defs */
	bool					स्वतःneg;
	u32					छोड़ो_config;

	/* EEE - capability & param */
	bool					eee_supported;
	bool					eee_active;
	u8					sup_caps;
	काष्ठा qed_link_eee_params		eee;

	u32					sup_fec;
	u32					active_fec;
पूर्ण;

काष्ठा qed_probe_params अणु
	क्रमागत qed_protocol protocol;
	u32 dp_module;
	u8 dp_level;
	bool is_vf;
	bool recov_in_prog;
पूर्ण;

#घोषणा QED_DRV_VER_STR_SIZE 12
काष्ठा qed_slowpath_params अणु
	u32	पूर्णांक_mode;
	u8	drv_major;
	u8	drv_minor;
	u8	drv_rev;
	u8	drv_eng;
	u8	name[QED_DRV_VER_STR_SIZE];
पूर्ण;

#घोषणा ILT_PAGE_SIZE_TCFC 0x8000 /* 32KB */

काष्ठा qed_पूर्णांक_info अणु
	काष्ठा msix_entry	*msix;
	u8			msix_cnt;

	/* This should be updated by the protocol driver */
	u8			used_cnt;
पूर्ण;

काष्ठा qed_generic_tlvs अणु
#घोषणा QED_TLV_IP_CSUM         BIT(0)
#घोषणा QED_TLV_LSO             BIT(1)
	u16 feat_flags;
#घोषणा QED_TLV_MAC_COUNT	3
	u8 mac[QED_TLV_MAC_COUNT][ETH_ALEN];
पूर्ण;

#घोषणा QED_I2C_DEV_ADDR_A0 0xA0
#घोषणा QED_I2C_DEV_ADDR_A2 0xA2

#घोषणा QED_NVM_SIGNATURE 0x12435687

क्रमागत qed_nvm_flash_cmd अणु
	QED_NVM_FLASH_CMD_खाता_DATA = 0x2,
	QED_NVM_FLASH_CMD_खाता_START = 0x3,
	QED_NVM_FLASH_CMD_NVM_CHANGE = 0x4,
	QED_NVM_FLASH_CMD_NVM_CFG_ID = 0x5,
	QED_NVM_FLASH_CMD_NVM_MAX,
पूर्ण;

काष्ठा qed_devlink अणु
	काष्ठा qed_dev *cdev;
	काष्ठा devlink_health_reporter *fw_reporter;
पूर्ण;

काष्ठा qed_common_cb_ops अणु
	व्योम (*arfs_filter_op)(व्योम *dev, व्योम *fltr, u8 fw_rc);
	व्योम (*link_update)(व्योम *dev, काष्ठा qed_link_output *link);
	व्योम (*schedule_recovery_handler)(व्योम *dev);
	व्योम (*schedule_hw_err_handler)(व्योम *dev,
					क्रमागत qed_hw_err_type err_type);
	व्योम (*dcbx_aen)(व्योम *dev, काष्ठा qed_dcbx_get *get, u32 mib_type);
	व्योम (*get_generic_tlv_data)(व्योम *dev, काष्ठा qed_generic_tlvs *data);
	व्योम (*get_protocol_tlv_data)(व्योम *dev, व्योम *data);
	व्योम (*bw_update)(व्योम *dev);
पूर्ण;

काष्ठा qed_selftest_ops अणु
/**
 * @brief selftest_पूर्णांकerrupt - Perक्रमm पूर्णांकerrupt test
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*selftest_पूर्णांकerrupt)(काष्ठा qed_dev *cdev);

/**
 * @brief selftest_memory - Perक्रमm memory test
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*selftest_memory)(काष्ठा qed_dev *cdev);

/**
 * @brief selftest_रेजिस्टर - Perक्रमm रेजिस्टर test
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*selftest_रेजिस्टर)(काष्ठा qed_dev *cdev);

/**
 * @brief selftest_घड़ी - Perक्रमm घड़ी test
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*selftest_घड़ी)(काष्ठा qed_dev *cdev);

/**
 * @brief selftest_nvram - Perक्रमm nvram test
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*selftest_nvram) (काष्ठा qed_dev *cdev);
पूर्ण;

काष्ठा qed_common_ops अणु
	काष्ठा qed_selftest_ops *selftest;

	काष्ठा qed_dev*	(*probe)(काष्ठा pci_dev *dev,
				 काष्ठा qed_probe_params *params);

	व्योम (*हटाओ)(काष्ठा qed_dev *cdev);

	पूर्णांक (*set_घातer_state)(काष्ठा qed_dev *cdev, pci_घातer_t state);

	व्योम (*set_name) (काष्ठा qed_dev *cdev, अक्षर name[]);

	/* Client drivers need to make this call beक्रमe slowpath_start.
	 * PF params required क्रम the call beक्रमe slowpath_start is
	 * करोcumented within the qed_pf_params काष्ठाure definition.
	 */
	व्योम (*update_pf_params)(काष्ठा qed_dev *cdev,
				 काष्ठा qed_pf_params *params);

	पूर्णांक (*slowpath_start)(काष्ठा qed_dev *cdev,
			      काष्ठा qed_slowpath_params *params);

	पूर्णांक (*slowpath_stop)(काष्ठा qed_dev *cdev);

	/* Requests to use `cnt' पूर्णांकerrupts क्रम fastpath.
	 * upon success, वापसs number of पूर्णांकerrupts allocated क्रम fastpath.
	 */
	पूर्णांक (*set_fp_पूर्णांक)(काष्ठा qed_dev *cdev, u16 cnt);

	/* Fills `info' with poपूर्णांकers required क्रम utilizing पूर्णांकerrupts */
	पूर्णांक (*get_fp_पूर्णांक)(काष्ठा qed_dev *cdev, काष्ठा qed_पूर्णांक_info *info);

	u32 (*sb_init)(काष्ठा qed_dev *cdev,
		       काष्ठा qed_sb_info *sb_info,
		       व्योम *sb_virt_addr,
		       dma_addr_t sb_phy_addr,
		       u16 sb_id,
		       क्रमागत qed_sb_type type);

	u32 (*sb_release)(काष्ठा qed_dev *cdev,
			  काष्ठा qed_sb_info *sb_info,
			  u16 sb_id,
			  क्रमागत qed_sb_type type);

	व्योम (*simd_handler_config)(काष्ठा qed_dev *cdev,
				    व्योम *token,
				    पूर्णांक index,
				    व्योम (*handler)(व्योम *));

	व्योम (*simd_handler_clean)(काष्ठा qed_dev *cdev, पूर्णांक index);

	पूर्णांक (*dbg_grc)(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes);

	पूर्णांक (*dbg_grc_size)(काष्ठा qed_dev *cdev);

	पूर्णांक (*dbg_all_data)(काष्ठा qed_dev *cdev, व्योम *buffer);

	पूर्णांक (*dbg_all_data_size)(काष्ठा qed_dev *cdev);

	पूर्णांक (*report_fatal_error)(काष्ठा devlink *devlink,
				  क्रमागत qed_hw_err_type err_type);

/**
 * @brief can_link_change - can the instance change the link or not
 *
 * @param cdev
 *
 * @वापस true अगर link-change is allowed, false otherwise.
 */
	bool (*can_link_change)(काष्ठा qed_dev *cdev);

/**
 * @brief set_link - set links according to params
 *
 * @param cdev
 * @param params - values used to override the शेष link configuration
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक		(*set_link)(काष्ठा qed_dev *cdev,
				    काष्ठा qed_link_params *params);

/**
 * @brief get_link - वापसs the current link state.
 *
 * @param cdev
 * @param अगर_link - काष्ठाure to be filled with current link configuration.
 */
	व्योम		(*get_link)(काष्ठा qed_dev *cdev,
				    काष्ठा qed_link_output *अगर_link);

/**
 * @brief - drains chip in हाल Tx completions fail to arrive due to छोड़ो.
 *
 * @param cdev
 */
	पूर्णांक		(*drain)(काष्ठा qed_dev *cdev);

/**
 * @brief update_msglvl - update module debug level
 *
 * @param cdev
 * @param dp_module
 * @param dp_level
 */
	व्योम		(*update_msglvl)(काष्ठा qed_dev *cdev,
					 u32 dp_module,
					 u8 dp_level);

	पूर्णांक		(*chain_alloc)(काष्ठा qed_dev *cdev,
				       काष्ठा qed_chain *chain,
				       काष्ठा qed_chain_init_params *params);

	व्योम		(*chain_मुक्त)(काष्ठा qed_dev *cdev,
				      काष्ठा qed_chain *p_chain);

/**
 * @brief nvm_flash - Flash nvm data.
 *
 * @param cdev
 * @param name - file containing the data
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*nvm_flash)(काष्ठा qed_dev *cdev, स्थिर अक्षर *name);

/**
 * @brief nvm_get_image - पढ़ोs an entire image from nvram
 *
 * @param cdev
 * @param type - type of the request nvram image
 * @param buf - pपुनः_स्मृतिated buffer to fill with the image
 * @param len - length of the allocated buffer
 *
 * @वापस 0 on success, error otherwise
 */
	पूर्णांक (*nvm_get_image)(काष्ठा qed_dev *cdev,
			     क्रमागत qed_nvm_images type, u8 *buf, u16 len);

/**
 * @brief set_coalesce - Configure Rx coalesce value in usec
 *
 * @param cdev
 * @param rx_coal - Rx coalesce value in usec
 * @param tx_coal - Tx coalesce value in usec
 * @param qid - Queue index
 * @param sb_id - Status Block Id
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*set_coalesce)(काष्ठा qed_dev *cdev,
			    u16 rx_coal, u16 tx_coal, व्योम *handle);

/**
 * @brief set_led - Configure LED mode
 *
 * @param cdev
 * @param mode - LED mode
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*set_led)(काष्ठा qed_dev *cdev,
		       क्रमागत qed_led_mode mode);

/**
 * @brief attn_clr_enable - Prevent attentions from being reनिश्चितed
 *
 * @param cdev
 * @param clr_enable
 */
	व्योम (*attn_clr_enable)(काष्ठा qed_dev *cdev, bool clr_enable);

/**
 * @brief db_recovery_add - add करोorbell inक्रमmation to the करोorbell
 * recovery mechanism.
 *
 * @param cdev
 * @param db_addr - करोorbell address
 * @param db_data - address of where db_data is stored
 * @param db_is_32b - करोorbell is 32b pr 64b
 * @param db_is_user - करोorbell recovery addresses are user or kernel space
 */
	पूर्णांक (*db_recovery_add)(काष्ठा qed_dev *cdev,
			       व्योम __iomem *db_addr,
			       व्योम *db_data,
			       क्रमागत qed_db_rec_width db_width,
			       क्रमागत qed_db_rec_space db_space);

/**
 * @brief db_recovery_del - हटाओ करोorbell inक्रमmation from the करोorbell
 * recovery mechanism. db_data serves as key (db_addr is not unique).
 *
 * @param cdev
 * @param db_addr - करोorbell address
 * @param db_data - address where db_data is stored. Serves as key क्रम the
 *		    entry to delete.
 */
	पूर्णांक (*db_recovery_del)(काष्ठा qed_dev *cdev,
			       व्योम __iomem *db_addr, व्योम *db_data);

/**
 * @brief recovery_process - Trigger a recovery process
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*recovery_process)(काष्ठा qed_dev *cdev);

/**
 * @brief recovery_prolog - Execute the prolog operations of a recovery process
 *
 * @param cdev
 *
 * @वापस 0 on success, error otherwise.
 */
	पूर्णांक (*recovery_prolog)(काष्ठा qed_dev *cdev);

/**
 * @brief update_drv_state - API to inक्रमm the change in the driver state.
 *
 * @param cdev
 * @param active
 *
 */
	पूर्णांक (*update_drv_state)(काष्ठा qed_dev *cdev, bool active);

/**
 * @brief update_mac - API to inक्रमm the change in the mac address
 *
 * @param cdev
 * @param mac
 *
 */
	पूर्णांक (*update_mac)(काष्ठा qed_dev *cdev, u8 *mac);

/**
 * @brief update_mtu - API to inक्रमm the change in the mtu
 *
 * @param cdev
 * @param mtu
 *
 */
	पूर्णांक (*update_mtu)(काष्ठा qed_dev *cdev, u16 mtu);

/**
 * @brief update_wol - update of changes in the WoL configuration
 *
 * @param cdev
 * @param enabled - true अगरf WoL should be enabled.
 */
	पूर्णांक (*update_wol) (काष्ठा qed_dev *cdev, bool enabled);

/**
 * @brief पढ़ो_module_eeprom
 *
 * @param cdev
 * @param buf - buffer
 * @param dev_addr - PHY device memory region
 * @param offset - offset पूर्णांकo eeprom contents to be पढ़ो
 * @param len - buffer length, i.e., max bytes to be पढ़ो
 */
	पूर्णांक (*पढ़ो_module_eeprom)(काष्ठा qed_dev *cdev,
				  अक्षर *buf, u8 dev_addr, u32 offset, u32 len);

/**
 * @brief get_affin_hwfn_idx
 *
 * @param cdev
 */
	u8 (*get_affin_hwfn_idx)(काष्ठा qed_dev *cdev);

/**
 * @brief पढ़ो_nvm_cfg - Read NVM config attribute value.
 * @param cdev
 * @param buf - buffer
 * @param cmd - NVM CFG command id
 * @param entity_id - Entity id
 *
 */
	पूर्णांक (*पढ़ो_nvm_cfg)(काष्ठा qed_dev *cdev, u8 **buf, u32 cmd,
			    u32 entity_id);
/**
 * @brief पढ़ो_nvm_cfg - Read NVM config attribute value.
 * @param cdev
 * @param cmd - NVM CFG command id
 *
 * @वापस config id length, 0 on error.
 */
	पूर्णांक (*पढ़ो_nvm_cfg_len)(काष्ठा qed_dev *cdev, u32 cmd);

/**
 * @brief set_grc_config - Configure value क्रम grc config id.
 * @param cdev
 * @param cfg_id - grc config id
 * @param val - grc config value
 *
 */
	पूर्णांक (*set_grc_config)(काष्ठा qed_dev *cdev, u32 cfg_id, u32 val);

	काष्ठा devlink* (*devlink_रेजिस्टर)(काष्ठा qed_dev *cdev);

	व्योम (*devlink_unरेजिस्टर)(काष्ठा devlink *devlink);
पूर्ण;

#घोषणा MASK_FIELD(_name, _value) \
	((_value) &= (_name ## _MASK))

#घोषणा FIELD_VALUE(_name, _value) \
	((_value & _name ## _MASK) << _name ## _SHIFT)

#घोषणा SET_FIELD(value, name, flag)			       \
	करो अणु						       \
		(value) &= ~(name ## _MASK << name ## _SHIFT); \
		(value) |= (((u64)flag) << (name ## _SHIFT));  \
	पूर्ण जबतक (0)

#घोषणा GET_FIELD(value, name) \
	(((value) >> (name ## _SHIFT)) & name ## _MASK)

#घोषणा GET_MFW_FIELD(name, field) \
	(((name) & (field ## _MASK)) >> (field ## _OFFSET))

#घोषणा SET_MFW_FIELD(name, field, value)				 \
	करो अणु								 \
		(name) &= ~(field ## _MASK);				 \
		(name) |= (((value) << (field ## _OFFSET)) & (field ## _MASK));\
	पूर्ण जबतक (0)

#घोषणा DB_ADDR_SHIFT(addr) ((addr) << DB_PWM_ADDR_OFFSET_SHIFT)

/* Debug prपूर्णांक definitions */
#घोषणा DP_ERR(cdev, fmt, ...)					\
	करो अणु							\
		pr_err("[%s:%d(%s)]" fmt,			\
		       __func__, __LINE__,			\
		       DP_NAME(cdev) ? DP_NAME(cdev) : "",	\
		       ## __VA_ARGS__);				\
	पूर्ण जबतक (0)

#घोषणा DP_NOTICE(cdev, fmt, ...)				      \
	करो अणु							      \
		अगर (unlikely((cdev)->dp_level <= QED_LEVEL_NOTICE)) अणु \
			pr_notice("[%s:%d(%s)]" fmt,		      \
				  __func__, __LINE__,		      \
				  DP_NAME(cdev) ? DP_NAME(cdev) : "", \
				  ## __VA_ARGS__);		      \
								      \
		पूर्ण						      \
	पूर्ण जबतक (0)

#घोषणा DP_INFO(cdev, fmt, ...)					      \
	करो अणु							      \
		अगर (unlikely((cdev)->dp_level <= QED_LEVEL_INFO)) अणु   \
			pr_notice("[%s:%d(%s)]" fmt,		      \
				  __func__, __LINE__,		      \
				  DP_NAME(cdev) ? DP_NAME(cdev) : "", \
				  ## __VA_ARGS__);		      \
		पूर्ण						      \
	पूर्ण जबतक (0)

#घोषणा DP_VERBOSE(cdev, module, fmt, ...)				\
	करो अणु								\
		अगर (unlikely(((cdev)->dp_level <= QED_LEVEL_VERBOSE) &&	\
			     ((cdev)->dp_module & module))) अणु		\
			pr_notice("[%s:%d(%s)]" fmt,			\
				  __func__, __LINE__,			\
				  DP_NAME(cdev) ? DP_NAME(cdev) : "",	\
				  ## __VA_ARGS__);			\
		पूर्ण							\
	पूर्ण जबतक (0)

क्रमागत DP_LEVEL अणु
	QED_LEVEL_VERBOSE	= 0x0,
	QED_LEVEL_INFO		= 0x1,
	QED_LEVEL_NOTICE	= 0x2,
	QED_LEVEL_ERR		= 0x3,
पूर्ण;

#घोषणा QED_LOG_LEVEL_SHIFT     (30)
#घोषणा QED_LOG_VERBOSE_MASK    (0x3fffffff)
#घोषणा QED_LOG_INFO_MASK       (0x40000000)
#घोषणा QED_LOG_NOTICE_MASK     (0x80000000)

क्रमागत DP_MODULE अणु
	QED_MSG_SPQ	= 0x10000,
	QED_MSG_STATS	= 0x20000,
	QED_MSG_DCB	= 0x40000,
	QED_MSG_IOV	= 0x80000,
	QED_MSG_SP	= 0x100000,
	QED_MSG_STORAGE = 0x200000,
	QED_MSG_CXT	= 0x800000,
	QED_MSG_LL2	= 0x1000000,
	QED_MSG_ILT	= 0x2000000,
	QED_MSG_RDMA	= 0x4000000,
	QED_MSG_DEBUG	= 0x8000000,
	/* to be added...up to 0x8000000 */
पूर्ण;

क्रमागत qed_mf_mode अणु
	QED_MF_DEFAULT,
	QED_MF_OVLAN,
	QED_MF_NPAR,
पूर्ण;

काष्ठा qed_eth_stats_common अणु
	u64	no_buff_discards;
	u64	packet_too_big_discard;
	u64	ttl0_discard;
	u64	rx_ucast_bytes;
	u64	rx_mcast_bytes;
	u64	rx_bcast_bytes;
	u64	rx_ucast_pkts;
	u64	rx_mcast_pkts;
	u64	rx_bcast_pkts;
	u64	mftag_filter_discards;
	u64	mac_filter_discards;
	u64	gft_filter_drop;
	u64	tx_ucast_bytes;
	u64	tx_mcast_bytes;
	u64	tx_bcast_bytes;
	u64	tx_ucast_pkts;
	u64	tx_mcast_pkts;
	u64	tx_bcast_pkts;
	u64	tx_err_drop_pkts;
	u64	tpa_coalesced_pkts;
	u64	tpa_coalesced_events;
	u64	tpa_पातs_num;
	u64	tpa_not_coalesced_pkts;
	u64	tpa_coalesced_bytes;

	/* port */
	u64	rx_64_byte_packets;
	u64	rx_65_to_127_byte_packets;
	u64	rx_128_to_255_byte_packets;
	u64	rx_256_to_511_byte_packets;
	u64	rx_512_to_1023_byte_packets;
	u64	rx_1024_to_1518_byte_packets;
	u64	rx_crc_errors;
	u64	rx_mac_crtl_frames;
	u64	rx_छोड़ो_frames;
	u64	rx_pfc_frames;
	u64	rx_align_errors;
	u64	rx_carrier_errors;
	u64	rx_oversize_packets;
	u64	rx_jabbers;
	u64	rx_undersize_packets;
	u64	rx_fragments;
	u64	tx_64_byte_packets;
	u64	tx_65_to_127_byte_packets;
	u64	tx_128_to_255_byte_packets;
	u64	tx_256_to_511_byte_packets;
	u64	tx_512_to_1023_byte_packets;
	u64	tx_1024_to_1518_byte_packets;
	u64	tx_छोड़ो_frames;
	u64	tx_pfc_frames;
	u64	brb_truncates;
	u64	brb_discards;
	u64	rx_mac_bytes;
	u64	rx_mac_uc_packets;
	u64	rx_mac_mc_packets;
	u64	rx_mac_bc_packets;
	u64	rx_mac_frames_ok;
	u64	tx_mac_bytes;
	u64	tx_mac_uc_packets;
	u64	tx_mac_mc_packets;
	u64	tx_mac_bc_packets;
	u64	tx_mac_ctrl_frames;
	u64	link_change_count;
पूर्ण;

काष्ठा qed_eth_stats_bb अणु
	u64 rx_1519_to_1522_byte_packets;
	u64 rx_1519_to_2047_byte_packets;
	u64 rx_2048_to_4095_byte_packets;
	u64 rx_4096_to_9216_byte_packets;
	u64 rx_9217_to_16383_byte_packets;
	u64 tx_1519_to_2047_byte_packets;
	u64 tx_2048_to_4095_byte_packets;
	u64 tx_4096_to_9216_byte_packets;
	u64 tx_9217_to_16383_byte_packets;
	u64 tx_lpi_entry_count;
	u64 tx_total_collisions;
पूर्ण;

काष्ठा qed_eth_stats_ah अणु
	u64 rx_1519_to_max_byte_packets;
	u64 tx_1519_to_max_byte_packets;
पूर्ण;

काष्ठा qed_eth_stats अणु
	काष्ठा qed_eth_stats_common common;

	जोड़ अणु
		काष्ठा qed_eth_stats_bb bb;
		काष्ठा qed_eth_stats_ah ah;
	पूर्ण;
पूर्ण;

#घोषणा QED_SB_IDX              0x0002

#घोषणा RX_PI           0
#घोषणा TX_PI(tc)       (RX_PI + 1 + tc)

काष्ठा qed_sb_cnt_info अणु
	/* Original, current, and मुक्त SBs क्रम PF */
	पूर्णांक orig;
	पूर्णांक cnt;
	पूर्णांक मुक्त_cnt;

	/* Original, current and मुक्त SBS क्रम child VFs */
	पूर्णांक iov_orig;
	पूर्णांक iov_cnt;
	पूर्णांक मुक्त_cnt_iov;
पूर्ण;

अटल अंतरभूत u16 qed_sb_update_sb_idx(काष्ठा qed_sb_info *sb_info)
अणु
	u32 prod = 0;
	u16 rc = 0;

	prod = le32_to_cpu(sb_info->sb_virt->prod_index) &
	       STATUS_BLOCK_E4_PROD_INDEX_MASK;
	अगर (sb_info->sb_ack != prod) अणु
		sb_info->sb_ack = prod;
		rc |= QED_SB_IDX;
	पूर्ण

	/* Let SB update */
	वापस rc;
पूर्ण

/**
 *
 * @brief This function creates an update command क्रम पूर्णांकerrupts that is
 *        written to the IGU.
 *
 * @param sb_info       - This is the काष्ठाure allocated and
 *                 initialized per status block. Assumption is
 *                 that it was initialized using qed_sb_init
 * @param पूर्णांक_cmd       - Enable/Disable/Nop
 * @param upd_flg       - whether igu consumer should be
 *                 updated.
 *
 * @वापस अंतरभूत व्योम
 */
अटल अंतरभूत व्योम qed_sb_ack(काष्ठा qed_sb_info *sb_info,
			      क्रमागत igu_पूर्णांक_cmd पूर्णांक_cmd,
			      u8 upd_flg)
अणु
	u32 igu_ack;

	igu_ack = ((sb_info->sb_ack << IGU_PROD_CONS_UPDATE_SB_INDEX_SHIFT) |
		   (upd_flg << IGU_PROD_CONS_UPDATE_UPDATE_FLAG_SHIFT) |
		   (पूर्णांक_cmd << IGU_PROD_CONS_UPDATE_ENABLE_INT_SHIFT) |
		   (IGU_SEG_ACCESS_REG <<
		    IGU_PROD_CONS_UPDATE_SEGMENT_ACCESS_SHIFT));

	सूचीECT_REG_WR(sb_info->igu_addr, igu_ack);

	/* Both segments (पूर्णांकerrupts & acks) are written to same place address;
	 * Need to guarantee all commands will be received (in-order) by HW.
	 */
	barrier();
पूर्ण

अटल अंतरभूत व्योम __पूर्णांकernal_ram_wr(व्योम *p_hwfn,
				     व्योम __iomem *addr,
				     पूर्णांक size,
				     u32 *data)

अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size / माप(*data); i++)
		सूचीECT_REG_WR(&((u32 __iomem *)addr)[i], data[i]);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकernal_ram_wr(व्योम __iomem *addr,
				   पूर्णांक size,
				   u32 *data)
अणु
	__पूर्णांकernal_ram_wr(शून्य, addr, size, data);
पूर्ण

क्रमागत qed_rss_caps अणु
	QED_RSS_IPV4		= 0x1,
	QED_RSS_IPV6		= 0x2,
	QED_RSS_IPV4_TCP	= 0x4,
	QED_RSS_IPV6_TCP	= 0x8,
	QED_RSS_IPV4_UDP	= 0x10,
	QED_RSS_IPV6_UDP	= 0x20,
पूर्ण;

#घोषणा QED_RSS_IND_TABLE_SIZE 128
#घोषणा QED_RSS_KEY_SIZE 10 /* size in 32b chunks */
#पूर्ण_अगर
