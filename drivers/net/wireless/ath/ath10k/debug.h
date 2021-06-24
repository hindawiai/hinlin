<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DEBUG_H_
#घोषणा _DEBUG_H_

#समावेश <linux/types.h>
#समावेश "trace.h"

क्रमागत ath10k_debug_mask अणु
	ATH10K_DBG_PCI		= 0x00000001,
	ATH10K_DBG_WMI		= 0x00000002,
	ATH10K_DBG_HTC		= 0x00000004,
	ATH10K_DBG_HTT		= 0x00000008,
	ATH10K_DBG_MAC		= 0x00000010,
	ATH10K_DBG_BOOT		= 0x00000020,
	ATH10K_DBG_PCI_DUMP	= 0x00000040,
	ATH10K_DBG_HTT_DUMP	= 0x00000080,
	ATH10K_DBG_MGMT		= 0x00000100,
	ATH10K_DBG_DATA		= 0x00000200,
	ATH10K_DBG_BMI		= 0x00000400,
	ATH10K_DBG_REGULATORY	= 0x00000800,
	ATH10K_DBG_TESTMODE	= 0x00001000,
	ATH10K_DBG_WMI_PRINT	= 0x00002000,
	ATH10K_DBG_PCI_PS	= 0x00004000,
	ATH10K_DBG_AHB		= 0x00008000,
	ATH10K_DBG_SDIO		= 0x00010000,
	ATH10K_DBG_SDIO_DUMP	= 0x00020000,
	ATH10K_DBG_USB		= 0x00040000,
	ATH10K_DBG_USB_BULK	= 0x00080000,
	ATH10K_DBG_SNOC		= 0x00100000,
	ATH10K_DBG_QMI		= 0x00200000,
	ATH10K_DBG_STA		= 0x00400000,
	ATH10K_DBG_ANY		= 0xffffffff,
पूर्ण;

क्रमागत ath10k_pktlog_filter अणु
	ATH10K_PKTLOG_RX         = 0x000000001,
	ATH10K_PKTLOG_TX         = 0x000000002,
	ATH10K_PKTLOG_RCFIND     = 0x000000004,
	ATH10K_PKTLOG_RCUPDATE   = 0x000000008,
	ATH10K_PKTLOG_DBG_PRINT  = 0x000000010,
	ATH10K_PKTLOG_PEER_STATS = 0x000000040,
	ATH10K_PKTLOG_ANY        = 0x00000005f,
पूर्ण;

क्रमागत ath10k_dbg_aggr_mode अणु
	ATH10K_DBG_AGGR_MODE_AUTO,
	ATH10K_DBG_AGGR_MODE_MANUAL,
	ATH10K_DBG_AGGR_MODE_MAX,
पूर्ण;

/* Types of packet log events */
क्रमागत ath_pktlog_type अणु
	ATH_PKTLOG_TYPE_TX_CTRL = 1,
	ATH_PKTLOG_TYPE_TX_STAT,
पूर्ण;

काष्ठा ath10k_pktlog_hdr अणु
	__le16 flags;
	__le16 missed_cnt;
	__le16 log_type; /* Type of log inक्रमmation foll this header */
	__le16 size; /* Size of variable length log inक्रमmation in bytes */
	__le32 बारtamp;
	u8 payload[];
पूर्ण __packed;

/* FIXME: How to calculate the buffer size sanely? */
#घोषणा ATH10K_FW_STATS_BUF_SIZE (1024 * 1024)

#घोषणा ATH10K_TX_POWER_MAX_VAL 70
#घोषणा ATH10K_TX_POWER_MIN_VAL 0

बाह्य अचिन्हित पूर्णांक ath10k_debug_mask;

__म_लिखो(2, 3) व्योम ath10k_info(काष्ठा ath10k *ar, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम ath10k_err(काष्ठा ath10k *ar, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम ath10k_warn(काष्ठा ath10k *ar, स्थिर अक्षर *fmt, ...);

व्योम ath10k_debug_prपूर्णांक_hwfw_info(काष्ठा ath10k *ar);
व्योम ath10k_debug_prपूर्णांक_board_info(काष्ठा ath10k *ar);
व्योम ath10k_debug_prपूर्णांक_boot_info(काष्ठा ath10k *ar);
व्योम ath10k_prपूर्णांक_driver_info(काष्ठा ath10k *ar);

#अगर_घोषित CONFIG_ATH10K_DEBUGFS
पूर्णांक ath10k_debug_start(काष्ठा ath10k *ar);
व्योम ath10k_debug_stop(काष्ठा ath10k *ar);
पूर्णांक ath10k_debug_create(काष्ठा ath10k *ar);
व्योम ath10k_debug_destroy(काष्ठा ath10k *ar);
पूर्णांक ath10k_debug_रेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_debug_unरेजिस्टर(काष्ठा ath10k *ar);
व्योम ath10k_debug_fw_stats_process(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
व्योम ath10k_debug_tpc_stats_process(काष्ठा ath10k *ar,
				    काष्ठा ath10k_tpc_stats *tpc_stats);
व्योम
ath10k_debug_tpc_stats_final_process(काष्ठा ath10k *ar,
				     काष्ठा ath10k_tpc_stats_final *tpc_stats);
व्योम ath10k_debug_dbglog_add(काष्ठा ath10k *ar, u8 *buffer, पूर्णांक len);

#घोषणा ATH10K_DFS_STAT_INC(ar, c) (ar->debug.dfs_stats.c++)

व्योम ath10k_debug_get_et_strings(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 u32 sset, u8 *data);
पूर्णांक ath10k_debug_get_et_sset_count(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset);
व्योम ath10k_debug_get_et_stats(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ethtool_stats *stats, u64 *data);

अटल अंतरभूत u64 ath10k_debug_get_fw_dbglog_mask(काष्ठा ath10k *ar)
अणु
	वापस ar->debug.fw_dbglog_mask;
पूर्ण

अटल अंतरभूत u32 ath10k_debug_get_fw_dbglog_level(काष्ठा ath10k *ar)
अणु
	वापस ar->debug.fw_dbglog_level;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_debug_is_extd_tx_stats_enabled(काष्ठा ath10k *ar)
अणु
	वापस ar->debug.enable_extd_tx_stats;
पूर्ण

पूर्णांक ath10k_debug_fw_stats_request(काष्ठा ath10k *ar);

#अन्यथा

अटल अंतरभूत पूर्णांक ath10k_debug_start(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_debug_stop(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_debug_create(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_debug_destroy(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_debug_रेजिस्टर(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_debug_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत व्योम ath10k_debug_fw_stats_process(काष्ठा ath10k *ar,
						 काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम ath10k_debug_tpc_stats_process(काष्ठा ath10k *ar,
						  काष्ठा ath10k_tpc_stats *tpc_stats)
अणु
	kमुक्त(tpc_stats);
पूर्ण

अटल अंतरभूत व्योम
ath10k_debug_tpc_stats_final_process(काष्ठा ath10k *ar,
				     काष्ठा ath10k_tpc_stats_final *tpc_stats)
अणु
	kमुक्त(tpc_stats);
पूर्ण

अटल अंतरभूत व्योम ath10k_debug_dbglog_add(काष्ठा ath10k *ar, u8 *buffer,
					   पूर्णांक len)
अणु
पूर्ण

अटल अंतरभूत u64 ath10k_debug_get_fw_dbglog_mask(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ath10k_debug_get_fw_dbglog_level(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_debug_is_extd_tx_stats_enabled(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_debug_fw_stats_request(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

#घोषणा ATH10K_DFS_STAT_INC(ar, c) करो अणु पूर्ण जबतक (0)

#घोषणा ath10k_debug_get_et_strings शून्य
#घोषणा ath10k_debug_get_et_sset_count शून्य
#घोषणा ath10k_debug_get_et_stats शून्य

#पूर्ण_अगर /* CONFIG_ATH10K_DEBUGFS */
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
व्योम ath10k_sta_add_debugfs(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, काष्ठा dentry *dir);
व्योम ath10k_sta_update_rx_duration(काष्ठा ath10k *ar,
				   काष्ठा ath10k_fw_stats *stats);
व्योम ath10k_sta_update_rx_tid_stats(काष्ठा ath10k *ar, u8 *first_hdr,
				    अचिन्हित दीर्घ num_msdus,
				    क्रमागत ath10k_pkt_rx_err err,
				    अचिन्हित दीर्घ unchain_cnt,
				    अचिन्हित दीर्घ drop_cnt,
				    अचिन्हित दीर्घ drop_cnt_filter,
				    अचिन्हित दीर्घ queued_msdus);
व्योम ath10k_sta_update_rx_tid_stats_ampdu(काष्ठा ath10k *ar,
					  u16 peer_id, u8 tid,
					  काष्ठा htt_rx_indication_mpdu_range *ranges,
					  पूर्णांक num_ranges);
#अन्यथा
अटल अंतरभूत
व्योम ath10k_sta_update_rx_duration(काष्ठा ath10k *ar,
				   काष्ठा ath10k_fw_stats *stats)
अणु
पूर्ण

अटल अंतरभूत
व्योम ath10k_sta_update_rx_tid_stats(काष्ठा ath10k *ar, u8 *first_hdr,
				    अचिन्हित दीर्घ num_msdus,
				    क्रमागत ath10k_pkt_rx_err err,
				    अचिन्हित दीर्घ unchain_cnt,
				    अचिन्हित दीर्घ drop_cnt,
				    अचिन्हित दीर्घ drop_cnt_filter,
				    अचिन्हित दीर्घ queued_msdus)
अणु
पूर्ण

अटल अंतरभूत
व्योम ath10k_sta_update_rx_tid_stats_ampdu(काष्ठा ath10k *ar,
					  u16 peer_id, u8 tid,
					  काष्ठा htt_rx_indication_mpdu_range *ranges,
					  पूर्णांक num_ranges)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MAC80211_DEBUGFS */

#अगर_घोषित CONFIG_ATH10K_DEBUG
__म_लिखो(3, 4) व्योम __ath10k_dbg(काष्ठा ath10k *ar,
				 क्रमागत ath10k_debug_mask mask,
				 स्थिर अक्षर *fmt, ...);
व्योम ath10k_dbg_dump(काष्ठा ath10k *ar,
		     क्रमागत ath10k_debug_mask mask,
		     स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		     स्थिर व्योम *buf, माप_प्रकार len);
#अन्यथा /* CONFIG_ATH10K_DEBUG */

अटल अंतरभूत पूर्णांक __ath10k_dbg(काष्ठा ath10k *ar,
			       क्रमागत ath10k_debug_mask dbg_mask,
			       स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_dbg_dump(काष्ठा ath10k *ar,
				   क्रमागत ath10k_debug_mask mask,
				   स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
				   स्थिर व्योम *buf, माप_प्रकार len)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH10K_DEBUG */

/* Aव्योम calling __ath10k_dbg() अगर debug_mask is not set and tracing
 * disabled.
 */
#घोषणा ath10k_dbg(ar, dbg_mask, fmt, ...)			\
करो अणु								\
	अगर ((ath10k_debug_mask & dbg_mask) ||			\
	    trace_ath10k_log_dbg_enabled())			\
		__ath10k_dbg(ar, dbg_mask, fmt, ##__VA_ARGS__); \
पूर्ण जबतक (0)
#पूर्ण_अगर /* _DEBUG_H_ */
