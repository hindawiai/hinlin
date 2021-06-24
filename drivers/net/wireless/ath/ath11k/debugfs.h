<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ATH11K_DEBUGFS_H_
#घोषणा _ATH11K_DEBUGFS_H_

#समावेश "hal_tx.h"

#घोषणा ATH11K_TX_POWER_MAX_VAL	70
#घोषणा ATH11K_TX_POWER_MIN_VAL	0

/* htt_dbg_ext_stats_type */
क्रमागत ath11k_dbg_htt_ext_stats_type अणु
	ATH11K_DBG_HTT_EXT_STATS_RESET                      =  0,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX                    =  1,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_RX                    =  2,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_HWQ                =  3,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_SCHED              =  4,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_ERROR                 =  5,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TQM                   =  6,
	ATH11K_DBG_HTT_EXT_STATS_TQM_CMDQ                   =  7,
	ATH11K_DBG_HTT_EXT_STATS_TX_DE_INFO                 =  8,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_RATE               =  9,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_RX_RATE               =  10,
	ATH11K_DBG_HTT_EXT_STATS_PEER_INFO                  =  11,
	ATH11K_DBG_HTT_EXT_STATS_TX_SELFGEN_INFO            =  12,
	ATH11K_DBG_HTT_EXT_STATS_TX_MU_HWQ                  =  13,
	ATH11K_DBG_HTT_EXT_STATS_RING_IF_INFO               =  14,
	ATH11K_DBG_HTT_EXT_STATS_SRNG_INFO                  =  15,
	ATH11K_DBG_HTT_EXT_STATS_SFM_INFO                   =  16,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_MU                 =  17,
	ATH11K_DBG_HTT_EXT_STATS_ACTIVE_PEERS_LIST          =  18,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_CCA_STATS             =  19,
	ATH11K_DBG_HTT_EXT_STATS_TWT_SESSIONS               =  20,
	ATH11K_DBG_HTT_EXT_STATS_REO_RESOURCE_STATS         =  21,
	ATH11K_DBG_HTT_EXT_STATS_TX_SOUNDING_INFO           =  22,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_OBSS_PD_STATS	    =  23,
	ATH11K_DBG_HTT_EXT_STATS_RING_BACKPRESSURE_STATS    =  24,

	/* keep this last */
	ATH11K_DBG_HTT_NUM_EXT_STATS,
पूर्ण;

काष्ठा debug_htt_stats_req अणु
	bool करोne;
	u8 pdev_id;
	u8 type;
	u8 peer_addr[ETH_ALEN];
	काष्ठा completion cmpln;
	u32 buf_len;
	u8 buf[];
पूर्ण;

काष्ठा ath_pktlog_hdr अणु
	u16 flags;
	u16 missed_cnt;
	u16 log_type;
	u16 size;
	u32 बारtamp;
	u32 type_specअगरic_data;
	u8 payload[];
पूर्ण;

#घोषणा ATH11K_HTT_PEER_STATS_RESET BIT(16)

#घोषणा ATH11K_HTT_STATS_BUF_SIZE (1024 * 512)
#घोषणा ATH11K_FW_STATS_BUF_SIZE (1024 * 1024)

क्रमागत ath11k_pktlog_filter अणु
	ATH11K_PKTLOG_RX		= 0x000000001,
	ATH11K_PKTLOG_TX		= 0x000000002,
	ATH11K_PKTLOG_RCFIND		= 0x000000004,
	ATH11K_PKTLOG_RCUPDATE		= 0x000000008,
	ATH11K_PKTLOG_EVENT_SMART_ANT	= 0x000000020,
	ATH11K_PKTLOG_EVENT_SW		= 0x000000040,
	ATH11K_PKTLOG_ANY		= 0x00000006f,
पूर्ण;

क्रमागत ath11k_pktlog_mode अणु
	ATH11K_PKTLOG_MODE_LITE = 1,
	ATH11K_PKTLOG_MODE_FULL = 2,
पूर्ण;

क्रमागत ath11k_pktlog_क्रमागत अणु
	ATH11K_PKTLOG_TYPE_TX_CTRL      = 1,
	ATH11K_PKTLOG_TYPE_TX_STAT      = 2,
	ATH11K_PKTLOG_TYPE_TX_MSDU_ID   = 3,
	ATH11K_PKTLOG_TYPE_RX_STAT      = 5,
	ATH11K_PKTLOG_TYPE_RC_FIND      = 6,
	ATH11K_PKTLOG_TYPE_RC_UPDATE    = 7,
	ATH11K_PKTLOG_TYPE_TX_VIRT_ADDR = 8,
	ATH11K_PKTLOG_TYPE_RX_CBF       = 10,
	ATH11K_PKTLOG_TYPE_RX_STATBUF   = 22,
	ATH11K_PKTLOG_TYPE_PPDU_STATS   = 23,
	ATH11K_PKTLOG_TYPE_LITE_RX      = 24,
पूर्ण;

क्रमागत ath11k_dbg_aggr_mode अणु
	ATH11K_DBG_AGGR_MODE_AUTO,
	ATH11K_DBG_AGGR_MODE_MANUAL,
	ATH11K_DBG_AGGR_MODE_MAX,
पूर्ण;

#अगर_घोषित CONFIG_ATH11K_DEBUGFS
पूर्णांक ath11k_debugfs_soc_create(काष्ठा ath11k_base *ab);
व्योम ath11k_debugfs_soc_destroy(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_debugfs_pdev_create(काष्ठा ath11k_base *ab);
व्योम ath11k_debugfs_pdev_destroy(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_debugfs_रेजिस्टर(काष्ठा ath11k *ar);
व्योम ath11k_debugfs_unरेजिस्टर(काष्ठा ath11k *ar);
व्योम ath11k_debugfs_fw_stats_process(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb);

व्योम ath11k_debugfs_fw_stats_init(काष्ठा ath11k *ar);

अटल अंतरभूत bool ath11k_debugfs_is_pktlog_lite_mode_enabled(काष्ठा ath11k *ar)
अणु
	वापस (ar->debug.pktlog_mode == ATH11K_PKTLOG_MODE_LITE);
पूर्ण

अटल अंतरभूत bool ath11k_debugfs_is_pktlog_rx_stats_enabled(काष्ठा ath11k *ar)
अणु
	वापस (!ar->debug.pktlog_peer_valid && ar->debug.pktlog_mode);
पूर्ण

अटल अंतरभूत bool ath11k_debugfs_is_pktlog_peer_valid(काष्ठा ath11k *ar, u8 *addr)
अणु
	वापस (ar->debug.pktlog_peer_valid && ar->debug.pktlog_mode &&
		ether_addr_equal(addr, ar->debug.pktlog_peer_addr));
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_is_extd_tx_stats_enabled(काष्ठा ath11k *ar)
अणु
	वापस ar->debug.extd_tx_stats;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_is_extd_rx_stats_enabled(काष्ठा ath11k *ar)
अणु
	वापस ar->debug.extd_rx_stats;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_rx_filter(काष्ठा ath11k *ar)
अणु
	वापस ar->debug.rx_filter;
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक ath11k_debugfs_soc_create(काष्ठा ath11k_base *ab)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_soc_destroy(काष्ठा ath11k_base *ab)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_pdev_create(काष्ठा ath11k_base *ab)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_pdev_destroy(काष्ठा ath11k_base *ab)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_रेजिस्टर(काष्ठा ath11k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_unरेजिस्टर(काष्ठा ath11k *ar)
अणु
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_fw_stats_process(काष्ठा ath11k_base *ab,
						   काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_fw_stats_init(काष्ठा ath11k *ar)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_is_extd_tx_stats_enabled(काष्ठा ath11k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_is_extd_rx_stats_enabled(काष्ठा ath11k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool ath11k_debugfs_is_pktlog_lite_mode_enabled(काष्ठा ath11k *ar)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool ath11k_debugfs_is_pktlog_rx_stats_enabled(काष्ठा ath11k *ar)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool ath11k_debugfs_is_pktlog_peer_valid(काष्ठा ath11k *ar, u8 *addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_rx_filter(काष्ठा ath11k *ar)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MAC80211_DEBUGFS*/

#पूर्ण_अगर /* _ATH11K_DEBUGFS_H_ */
