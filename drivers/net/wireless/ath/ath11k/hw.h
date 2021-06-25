<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_HW_H
#घोषणा ATH11K_HW_H

#समावेश "wmi.h"

/* Target configuration defines */

/* Num VDEVS per radio */
#घोषणा TARGET_NUM_VDEVS	(16 + 1)

#घोषणा TARGET_NUM_PEERS_PDEV	(512 + TARGET_NUM_VDEVS)

/* Num of peers क्रम Single Radio mode */
#घोषणा TARGET_NUM_PEERS_SINGLE		(TARGET_NUM_PEERS_PDEV)

/* Num of peers क्रम DBS */
#घोषणा TARGET_NUM_PEERS_DBS		(2 * TARGET_NUM_PEERS_PDEV)

/* Num of peers क्रम DBS_SBS */
#घोषणा TARGET_NUM_PEERS_DBS_SBS	(3 * TARGET_NUM_PEERS_PDEV)

/* Max num of stations (per radio) */
#घोषणा TARGET_NUM_STATIONS	512

#घोषणा TARGET_NUM_PEERS(x)	TARGET_NUM_PEERS_##x
#घोषणा TARGET_NUM_PEER_KEYS	2
#घोषणा TARGET_NUM_TIDS(x)	(2 * TARGET_NUM_PEERS(x) + \
				 4 * TARGET_NUM_VDEVS + 8)

#घोषणा TARGET_AST_SKID_LIMIT	16
#घोषणा TARGET_NUM_OFFLD_PEERS	4
#घोषणा TARGET_NUM_OFFLD_REORDER_BUFFS 4

#घोषणा TARGET_TX_CHAIN_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#घोषणा TARGET_RX_CHAIN_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#घोषणा TARGET_RX_TIMEOUT_LO_PRI	100
#घोषणा TARGET_RX_TIMEOUT_HI_PRI	40

#घोषणा TARGET_DECAP_MODE_RAW		0
#घोषणा TARGET_DECAP_MODE_NATIVE_WIFI	1
#घोषणा TARGET_DECAP_MODE_ETH		2

#घोषणा TARGET_SCAN_MAX_PENDING_REQS	4
#घोषणा TARGET_BMISS_OFFLOAD_MAX_VDEV	3
#घोषणा TARGET_ROAM_OFFLOAD_MAX_VDEV	3
#घोषणा TARGET_ROAM_OFFLOAD_MAX_AP_PROखाताS	8
#घोषणा TARGET_GTK_OFFLOAD_MAX_VDEV	3
#घोषणा TARGET_NUM_MCAST_GROUPS		12
#घोषणा TARGET_NUM_MCAST_TABLE_ELEMS	64
#घोषणा TARGET_MCAST2UCAST_MODE		2
#घोषणा TARGET_TX_DBG_LOG_SIZE		1024
#घोषणा TARGET_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK 1
#घोषणा TARGET_VOW_CONFIG		0
#घोषणा TARGET_NUM_MSDU_DESC		(2500)
#घोषणा TARGET_MAX_FRAG_ENTRIES		6
#घोषणा TARGET_MAX_BCN_OFFLD		16
#घोषणा TARGET_NUM_WDS_ENTRIES		32
#घोषणा TARGET_DMA_BURST_SIZE		1
#घोषणा TARGET_RX_BATCHMODE		1

#घोषणा ATH11K_HW_MAX_QUEUES		4
#घोषणा ATH11K_QUEUE_LEN		4096

#घोषणा ATH11k_HW_RATECODE_CCK_SHORT_PREAM_MASK  0x4

#घोषणा ATH11K_FW_सूची			"ath11k"

#घोषणा ATH11K_BOARD_MAGIC		"QCA-ATH11K-BOARD"
#घोषणा ATH11K_BOARD_API2_खाता		"board-2.bin"
#घोषणा ATH11K_DEFAULT_BOARD_खाता	"board.bin"
#घोषणा ATH11K_DEFAULT_CAL_खाता		"caldata.bin"
#घोषणा ATH11K_AMSS_खाता		"amss.bin"
#घोषणा ATH11K_M3_खाता			"m3.bin"

क्रमागत ath11k_hw_rate_cck अणु
	ATH11K_HW_RATE_CCK_LP_11M = 0,
	ATH11K_HW_RATE_CCK_LP_5_5M,
	ATH11K_HW_RATE_CCK_LP_2M,
	ATH11K_HW_RATE_CCK_LP_1M,
	ATH11K_HW_RATE_CCK_SP_11M,
	ATH11K_HW_RATE_CCK_SP_5_5M,
	ATH11K_HW_RATE_CCK_SP_2M,
पूर्ण;

क्रमागत ath11k_hw_rate_ofdm अणु
	ATH11K_HW_RATE_OFDM_48M = 0,
	ATH11K_HW_RATE_OFDM_24M,
	ATH11K_HW_RATE_OFDM_12M,
	ATH11K_HW_RATE_OFDM_6M,
	ATH11K_HW_RATE_OFDM_54M,
	ATH11K_HW_RATE_OFDM_36M,
	ATH11K_HW_RATE_OFDM_18M,
	ATH11K_HW_RATE_OFDM_9M,
पूर्ण;

क्रमागत ath11k_bus अणु
	ATH11K_BUS_AHB,
	ATH11K_BUS_PCI,
पूर्ण;

#घोषणा ATH11K_EXT_IRQ_GRP_NUM_MAX 11

काष्ठा hal_rx_desc;
काष्ठा hal_tcl_data_cmd;

काष्ठा ath11k_hw_ring_mask अणु
	u8 tx[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 rx_mon_status[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 rx[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 rx_err[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 rx_wbm_rel[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 reo_status[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 rxdma2host[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	u8 host2rxdma[ATH11K_EXT_IRQ_GRP_NUM_MAX];
पूर्ण;

काष्ठा ath11k_hw_params अणु
	स्थिर अक्षर *name;
	u16 hw_rev;
	u8 max_radios;
	u32 bdf_addr;

	काष्ठा अणु
		स्थिर अक्षर *dir;
		माप_प्रकार board_size;
		माप_प्रकार cal_size;
	पूर्ण fw;

	स्थिर काष्ठा ath11k_hw_ops *hw_ops;
	स्थिर काष्ठा ath11k_hw_ring_mask *ring_mask;

	bool पूर्णांकernal_sleep_घड़ी;

	स्थिर काष्ठा ath11k_hw_regs *regs;
	u32 qmi_service_ins_id;
	स्थिर काष्ठा ce_attr *host_ce_config;
	u32 ce_count;
	स्थिर काष्ठा ce_pipe_config *target_ce_config;
	u32 target_ce_count;
	स्थिर काष्ठा service_to_pipe *svc_to_ce_map;
	u32 svc_to_ce_map_len;

	bool single_pdev_only;

	bool rxdma1_enable;
	पूर्णांक num_rxmda_per_pdev;
	bool rx_mac_buf_ring;
	bool vdev_start_delay;
	bool htt_peer_map_v2;
	bool tcl_0_only;
	u8 spectral_fft_sz;

	u16 पूर्णांकerface_modes;
	bool supports_monitor;
	bool supports_shaकरोw_regs;
	bool idle_ps;
	bool cold_boot_calib;
	bool supports_suspend;
	u32 hal_desc_sz;
पूर्ण;

काष्ठा ath11k_hw_ops अणु
	u8 (*get_hw_mac_from_pdev_id)(पूर्णांक pdev_id);
	व्योम (*wmi_init_config)(काष्ठा ath11k_base *ab,
				काष्ठा target_resource_config *config);
	पूर्णांक (*mac_id_to_pdev_id)(काष्ठा ath11k_hw_params *hw, पूर्णांक mac_id);
	पूर्णांक (*mac_id_to_srng_id)(काष्ठा ath11k_hw_params *hw, पूर्णांक mac_id);
	व्योम (*tx_mesh_enable)(काष्ठा ath11k_base *ab,
			       काष्ठा hal_tcl_data_cmd *tcl_cmd);
	bool (*rx_desc_get_first_msdu)(काष्ठा hal_rx_desc *desc);
	bool (*rx_desc_get_last_msdu)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_l3_pad_bytes)(काष्ठा hal_rx_desc *desc);
	u8 *(*rx_desc_get_hdr_status)(काष्ठा hal_rx_desc *desc);
	bool (*rx_desc_encrypt_valid)(काष्ठा hal_rx_desc *desc);
	u32 (*rx_desc_get_encrypt_type)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_decap_type)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_mesh_ctl)(काष्ठा hal_rx_desc *desc);
	bool (*rx_desc_get_mpdu_seq_ctl_vld)(काष्ठा hal_rx_desc *desc);
	bool (*rx_desc_get_mpdu_fc_valid)(काष्ठा hal_rx_desc *desc);
	u16 (*rx_desc_get_mpdu_start_seq_no)(काष्ठा hal_rx_desc *desc);
	u16 (*rx_desc_get_msdu_len)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_msdu_sgi)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_msdu_rate_mcs)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_msdu_rx_bw)(काष्ठा hal_rx_desc *desc);
	u32 (*rx_desc_get_msdu_freq)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_msdu_pkt_type)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_msdu_nss)(काष्ठा hal_rx_desc *desc);
	u8 (*rx_desc_get_mpdu_tid)(काष्ठा hal_rx_desc *desc);
	u16 (*rx_desc_get_mpdu_peer_id)(काष्ठा hal_rx_desc *desc);
	व्योम (*rx_desc_copy_attn_end_tlv)(काष्ठा hal_rx_desc *fdesc,
					  काष्ठा hal_rx_desc *ldesc);
	u32 (*rx_desc_get_mpdu_start_tag)(काष्ठा hal_rx_desc *desc);
	u32 (*rx_desc_get_mpdu_ppdu_id)(काष्ठा hal_rx_desc *desc);
	व्योम (*rx_desc_set_msdu_len)(काष्ठा hal_rx_desc *desc, u16 len);
	काष्ठा rx_attention *(*rx_desc_get_attention)(काष्ठा hal_rx_desc *desc);
	u8 *(*rx_desc_get_msdu_payload)(काष्ठा hal_rx_desc *desc);
पूर्ण;

बाह्य स्थिर काष्ठा ath11k_hw_ops ipq8074_ops;
बाह्य स्थिर काष्ठा ath11k_hw_ops ipq6018_ops;
बाह्य स्थिर काष्ठा ath11k_hw_ops qca6390_ops;
बाह्य स्थिर काष्ठा ath11k_hw_ops qcn9074_ops;

बाह्य स्थिर काष्ठा ath11k_hw_ring_mask ath11k_hw_ring_mask_ipq8074;
बाह्य स्थिर काष्ठा ath11k_hw_ring_mask ath11k_hw_ring_mask_qca6390;
बाह्य स्थिर काष्ठा ath11k_hw_ring_mask ath11k_hw_ring_mask_qcn9074;

अटल अंतरभूत
पूर्णांक ath11k_hw_get_mac_from_pdev_id(काष्ठा ath11k_hw_params *hw,
				   पूर्णांक pdev_idx)
अणु
	अगर (hw->hw_ops->get_hw_mac_from_pdev_id)
		वापस hw->hw_ops->get_hw_mac_from_pdev_id(pdev_idx);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hw_mac_id_to_pdev_id(काष्ठा ath11k_hw_params *hw,
					      पूर्णांक mac_id)
अणु
	अगर (hw->hw_ops->mac_id_to_pdev_id)
		वापस hw->hw_ops->mac_id_to_pdev_id(hw, mac_id);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_hw_mac_id_to_srng_id(काष्ठा ath11k_hw_params *hw,
					      पूर्णांक mac_id)
अणु
	अगर (hw->hw_ops->mac_id_to_srng_id)
		वापस hw->hw_ops->mac_id_to_srng_id(hw, mac_id);

	वापस 0;
पूर्ण

काष्ठा ath11k_fw_ie अणु
	__le32 id;
	__le32 len;
	u8 data[];
पूर्ण;

क्रमागत ath11k_bd_ie_board_type अणु
	ATH11K_BD_IE_BOARD_NAME = 0,
	ATH11K_BD_IE_BOARD_DATA = 1,
पूर्ण;

क्रमागत ath11k_bd_ie_type अणु
	/* contains sub IEs of क्रमागत ath11k_bd_ie_board_type */
	ATH11K_BD_IE_BOARD = 0,
	ATH11K_BD_IE_BOARD_EXT = 1,
पूर्ण;

काष्ठा ath11k_hw_regs अणु
	u32 hal_tcl1_ring_base_lsb;
	u32 hal_tcl1_ring_base_msb;
	u32 hal_tcl1_ring_id;
	u32 hal_tcl1_ring_misc;
	u32 hal_tcl1_ring_tp_addr_lsb;
	u32 hal_tcl1_ring_tp_addr_msb;
	u32 hal_tcl1_ring_consumer_पूर्णांक_setup_ix0;
	u32 hal_tcl1_ring_consumer_पूर्णांक_setup_ix1;
	u32 hal_tcl1_ring_msi1_base_lsb;
	u32 hal_tcl1_ring_msi1_base_msb;
	u32 hal_tcl1_ring_msi1_data;
	u32 hal_tcl2_ring_base_lsb;
	u32 hal_tcl_ring_base_lsb;

	u32 hal_tcl_status_ring_base_lsb;

	u32 hal_reo1_ring_base_lsb;
	u32 hal_reo1_ring_base_msb;
	u32 hal_reo1_ring_id;
	u32 hal_reo1_ring_misc;
	u32 hal_reo1_ring_hp_addr_lsb;
	u32 hal_reo1_ring_hp_addr_msb;
	u32 hal_reo1_ring_producer_पूर्णांक_setup;
	u32 hal_reo1_ring_msi1_base_lsb;
	u32 hal_reo1_ring_msi1_base_msb;
	u32 hal_reo1_ring_msi1_data;
	u32 hal_reo2_ring_base_lsb;
	u32 hal_reo1_aging_thresh_ix_0;
	u32 hal_reo1_aging_thresh_ix_1;
	u32 hal_reo1_aging_thresh_ix_2;
	u32 hal_reo1_aging_thresh_ix_3;

	u32 hal_reo1_ring_hp;
	u32 hal_reo1_ring_tp;
	u32 hal_reo2_ring_hp;

	u32 hal_reo_tcl_ring_base_lsb;
	u32 hal_reo_tcl_ring_hp;

	u32 hal_reo_status_ring_base_lsb;
	u32 hal_reo_status_hp;

	u32 hal_seq_wcss_umac_ce0_src_reg;
	u32 hal_seq_wcss_umac_ce0_dst_reg;
	u32 hal_seq_wcss_umac_ce1_src_reg;
	u32 hal_seq_wcss_umac_ce1_dst_reg;

	u32 hal_wbm_idle_link_ring_base_lsb;
	u32 hal_wbm_idle_link_ring_misc;

	u32 hal_wbm_release_ring_base_lsb;

	u32 hal_wbm0_release_ring_base_lsb;
	u32 hal_wbm1_release_ring_base_lsb;

	u32 pcie_qserdes_sysclk_en_sel;
	u32 pcie_pcs_osc_dtct_config_base;
पूर्ण;

बाह्य स्थिर काष्ठा ath11k_hw_regs ipq8074_regs;
बाह्य स्थिर काष्ठा ath11k_hw_regs qca6390_regs;
बाह्य स्थिर काष्ठा ath11k_hw_regs qcn9074_regs;

#पूर्ण_अगर
