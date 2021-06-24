<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wlcore
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#अगर_अघोषित __WLCORE_H__
#घोषणा __WLCORE_H__

#समावेश <linux/platक्रमm_device.h>

#समावेश "wlcore_i.h"
#समावेश "event.h"
#समावेश "boot.h"

/* The maximum number of Tx descriptors in all chip families */
#घोषणा WLCORE_MAX_TX_DESCRIPTORS 32

/*
 * We always allocate this number of mac addresses. If we करोn't
 * have enough allocated addresses, the LAA bit is used
 */
#घोषणा WLCORE_NUM_MAC_ADDRESSES 3

/* wl12xx/wl18xx maximum transmission घातer (in dBm) */
#घोषणा WLCORE_MAX_TXPWR        25

/* Texas Instruments pre asचिन्हित OUI */
#घोषणा WLCORE_TI_OUI_ADDRESS 0x080028

/* क्रमward declaration */
काष्ठा wl1271_tx_hw_descr;
क्रमागत wl_rx_buf_align;
काष्ठा wl1271_rx_descriptor;

काष्ठा wlcore_ops अणु
	पूर्णांक (*setup)(काष्ठा wl1271 *wl);
	पूर्णांक (*identअगरy_chip)(काष्ठा wl1271 *wl);
	पूर्णांक (*identअगरy_fw)(काष्ठा wl1271 *wl);
	पूर्णांक (*boot)(काष्ठा wl1271 *wl);
	पूर्णांक (*plt_init)(काष्ठा wl1271 *wl);
	पूर्णांक (*trigger_cmd)(काष्ठा wl1271 *wl, पूर्णांक cmd_box_addr,
			   व्योम *buf, माप_प्रकार len);
	पूर्णांक (*ack_event)(काष्ठा wl1271 *wl);
	पूर्णांक (*रुको_क्रम_event)(काष्ठा wl1271 *wl, क्रमागत wlcore_रुको_event event,
			      bool *समयout);
	पूर्णांक (*process_mailbox_events)(काष्ठा wl1271 *wl);
	u32 (*calc_tx_blocks)(काष्ठा wl1271 *wl, u32 len, u32 spare_blks);
	व्योम (*set_tx_desc_blocks)(काष्ठा wl1271 *wl,
				   काष्ठा wl1271_tx_hw_descr *desc,
				   u32 blks, u32 spare_blks);
	व्योम (*set_tx_desc_data_len)(काष्ठा wl1271 *wl,
				     काष्ठा wl1271_tx_hw_descr *desc,
				     काष्ठा sk_buff *skb);
	क्रमागत wl_rx_buf_align (*get_rx_buf_align)(काष्ठा wl1271 *wl,
						 u32 rx_desc);
	पूर्णांक (*prepare_पढ़ो)(काष्ठा wl1271 *wl, u32 rx_desc, u32 len);
	u32 (*get_rx_packet_len)(काष्ठा wl1271 *wl, व्योम *rx_data,
				 u32 data_len);
	पूर्णांक (*tx_delayed_compl)(काष्ठा wl1271 *wl);
	व्योम (*tx_immediate_compl)(काष्ठा wl1271 *wl);
	पूर्णांक (*hw_init)(काष्ठा wl1271 *wl);
	पूर्णांक (*init_vअगर)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
	व्योम (*convert_fw_status)(काष्ठा wl1271 *wl, व्योम *raw_fw_status,
				  काष्ठा wl_fw_status *fw_status);
	u32 (*sta_get_ap_rate_mask)(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर);
	पूर्णांक (*get_pg_ver)(काष्ठा wl1271 *wl, s8 *ver);
	पूर्णांक (*get_mac)(काष्ठा wl1271 *wl);
	व्योम (*set_tx_desc_csum)(काष्ठा wl1271 *wl,
				 काष्ठा wl1271_tx_hw_descr *desc,
				 काष्ठा sk_buff *skb);
	व्योम (*set_rx_csum)(काष्ठा wl1271 *wl,
			    काष्ठा wl1271_rx_descriptor *desc,
			    काष्ठा sk_buff *skb);
	u32 (*ap_get_mimo_wide_rate_mask)(काष्ठा wl1271 *wl,
					  काष्ठा wl12xx_vअगर *wlvअगर);
	पूर्णांक (*debugfs_init)(काष्ठा wl1271 *wl, काष्ठा dentry *rootdir);
	पूर्णांक (*handle_अटल_data)(काष्ठा wl1271 *wl,
				  काष्ठा wl1271_अटल_data *अटल_data);
	पूर्णांक (*scan_start)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  काष्ठा cfg80211_scan_request *req);
	पूर्णांक (*scan_stop)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
	पूर्णांक (*sched_scan_start)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				काष्ठा cfg80211_sched_scan_request *req,
				काष्ठा ieee80211_scan_ies *ies);
	व्योम (*sched_scan_stop)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
	पूर्णांक (*get_spare_blocks)(काष्ठा wl1271 *wl, bool is_gem);
	पूर्णांक (*set_key)(काष्ठा wl1271 *wl, क्रमागत set_key_cmd cmd,
		       काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key_conf);
	पूर्णांक (*channel_चयन)(काष्ठा wl1271 *wl,
			      काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा ieee80211_channel_चयन *ch_चयन);
	u32 (*pre_pkt_send)(काष्ठा wl1271 *wl, u32 buf_offset, u32 last_len);
	व्योम (*sta_rc_update)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
	पूर्णांक (*set_peer_cap)(काष्ठा wl1271 *wl,
			    काष्ठा ieee80211_sta_ht_cap *ht_cap,
			    bool allow_ht_operation,
			    u32 rate_set, u8 hlid);
	u32 (*convert_hwaddr)(काष्ठा wl1271 *wl, u32 hwaddr);
	bool (*lnk_high_prio)(काष्ठा wl1271 *wl, u8 hlid,
			      काष्ठा wl1271_link *lnk);
	bool (*lnk_low_prio)(काष्ठा wl1271 *wl, u8 hlid,
			     काष्ठा wl1271_link *lnk);
	पूर्णांक (*पूर्णांकerrupt_notअगरy)(काष्ठा wl1271 *wl, bool action);
	पूर्णांक (*rx_ba_filter)(काष्ठा wl1271 *wl, bool action);
	पूर्णांक (*ap_sleep)(काष्ठा wl1271 *wl);
	पूर्णांक (*smart_config_start)(काष्ठा wl1271 *wl, u32 group_biपंचांगap);
	पूर्णांक (*smart_config_stop)(काष्ठा wl1271 *wl);
	पूर्णांक (*smart_config_set_group_key)(काष्ठा wl1271 *wl, u16 group_id,
					  u8 key_len, u8 *key);
	पूर्णांक (*set_cac)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       bool start);
	पूर्णांक (*dfs_master_restart)(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
पूर्ण;

क्रमागत wlcore_partitions अणु
	PART_DOWN,
	PART_WORK,
	PART_BOOT,
	PART_DRPW,
	PART_TOP_PRCM_ELP_SOC,
	PART_PHY_INIT,

	PART_TABLE_LEN,
पूर्ण;

काष्ठा wlcore_partition अणु
	u32 size;
	u32 start;
पूर्ण;

काष्ठा wlcore_partition_set अणु
	काष्ठा wlcore_partition mem;
	काष्ठा wlcore_partition reg;
	काष्ठा wlcore_partition mem2;
	काष्ठा wlcore_partition mem3;
पूर्ण;

क्रमागत wlcore_रेजिस्टरs अणु
	/* रेजिस्टर addresses, used with partition translation */
	REG_ECPU_CONTROL,
	REG_INTERRUPT_NO_CLEAR,
	REG_INTERRUPT_ACK,
	REG_COMMAND_MAILBOX_PTR,
	REG_EVENT_MAILBOX_PTR,
	REG_INTERRUPT_TRIG,
	REG_INTERRUPT_MASK,
	REG_PC_ON_RECOVERY,
	REG_CHIP_ID_B,
	REG_CMD_MBOX_ADDRESS,

	/* data access memory addresses, used with partition translation */
	REG_SLV_MEM_DATA,
	REG_SLV_REG_DATA,

	/* raw data access memory addresses */
	REG_RAW_FW_STATUS_ADDR,

	REG_TABLE_LEN,
पूर्ण;

काष्ठा wl1271_stats अणु
	व्योम *fw_stats;
	अचिन्हित दीर्घ fw_stats_update;
	माप_प्रकार fw_stats_len;

	अचिन्हित पूर्णांक retry_count;
	अचिन्हित पूर्णांक excessive_retries;
पूर्ण;

काष्ठा wl1271 अणु
	bool initialized;
	काष्ठा ieee80211_hw *hw;
	bool mac80211_रेजिस्टरed;

	काष्ठा device *dev;
	काष्ठा platक्रमm_device *pdev;

	व्योम *अगर_priv;

	काष्ठा wl1271_अगर_operations *अगर_ops;

	पूर्णांक irq;
	पूर्णांक wakeirq;

	पूर्णांक irq_flags;
	पूर्णांक wakeirq_flags;

	spinlock_t wl_lock;

	क्रमागत wlcore_state state;
	क्रमागत wl12xx_fw_type fw_type;
	bool plt;
	क्रमागत plt_mode plt_mode;
	u8 fem_manuf;
	u8 last_vअगर_count;
	काष्ठा mutex mutex;

	अचिन्हित दीर्घ flags;

	काष्ठा wlcore_partition_set curr_part;

	काष्ठा wl1271_chip chip;

	पूर्णांक cmd_box_addr;

	u8 *fw;
	माप_प्रकार fw_len;
	व्योम *nvs;
	माप_प्रकार nvs_len;

	s8 hw_pg_ver;

	/* address पढ़ो from the fuse ROM */
	u32 fuse_oui_addr;
	u32 fuse_nic_addr;

	/* we have up to 2 MAC addresses */
	काष्ठा mac_address addresses[WLCORE_NUM_MAC_ADDRESSES];
	पूर्णांक channel;
	u8 प्रणाली_hlid;

	अचिन्हित दीर्घ links_map[BITS_TO_LONGS(WLCORE_MAX_LINKS)];
	अचिन्हित दीर्घ roles_map[BITS_TO_LONGS(WL12XX_MAX_ROLES)];
	अचिन्हित दीर्घ roc_map[BITS_TO_LONGS(WL12XX_MAX_ROLES)];
	अचिन्हित दीर्घ rate_policies_map[
			BITS_TO_LONGS(WL12XX_MAX_RATE_POLICIES)];
	अचिन्हित दीर्घ klv_ढाँचाs_map[
			BITS_TO_LONGS(WLCORE_MAX_KLV_TEMPLATES)];

	u8 session_ids[WLCORE_MAX_LINKS];

	काष्ठा list_head wlvअगर_list;

	u8 sta_count;
	u8 ap_count;

	काष्ठा wl1271_acx_mem_map *target_mem_map;

	/* Accounting क्रम allocated / available TX blocks on HW */
	u32 tx_blocks_मुक्तd;
	u32 tx_blocks_available;
	u32 tx_allocated_blocks;
	u32 tx_results_count;

	/* Accounting क्रम allocated / available Tx packets in HW */
	u32 tx_pkts_मुक्तd[NUM_TX_QUEUES];
	u32 tx_allocated_pkts[NUM_TX_QUEUES];

	/* Transmitted TX packets counter क्रम chipset पूर्णांकerface */
	u32 tx_packets_count;

	/* Time-offset between host and chipset घड़ीs */
	s64 समय_offset;

	/* Frames scheduled क्रम transmission, not handled yet */
	पूर्णांक tx_queue_count[NUM_TX_QUEUES];
	अचिन्हित दीर्घ queue_stop_reasons[
				NUM_TX_QUEUES * WLCORE_NUM_MAC_ADDRESSES];

	/* Frames received, not handled yet by mac80211 */
	काष्ठा sk_buff_head deferred_rx_queue;

	/* Frames sent, not वापसed yet to mac80211 */
	काष्ठा sk_buff_head deferred_tx_queue;

	काष्ठा work_काष्ठा tx_work;
	काष्ठा workqueue_काष्ठा *मुक्तzable_wq;

	/* Pending TX frames */
	अचिन्हित दीर्घ tx_frames_map[BITS_TO_LONGS(WLCORE_MAX_TX_DESCRIPTORS)];
	काष्ठा sk_buff *tx_frames[WLCORE_MAX_TX_DESCRIPTORS];
	पूर्णांक tx_frames_cnt;

	/* FW Rx counter */
	u32 rx_counter;

	/* Intermediate buffer, used क्रम packet aggregation */
	u8 *aggr_buf;
	u32 aggr_buf_size;

	/* Reusable dummy packet ढाँचा */
	काष्ठा sk_buff *dummy_packet;

	/* Network stack work  */
	काष्ठा work_काष्ठा netstack_work;

	/* FW log buffer */
	u8 *fwlog;

	/* Number of valid bytes in the FW log buffer */
	sमाप_प्रकार fwlog_size;

	/* FW log end marker */
	u32 fwlog_end;

	/* FW memory block size */
	u32 fw_mem_block_size;

	/* Hardware recovery work */
	काष्ठा work_काष्ठा recovery_work;
	bool watchकरोg_recovery;

	/* Reg करोमुख्य last configuration */
	DECLARE_BITMAP(reg_ch_conf_last, 64);
	/* Reg करोमुख्य pending configuration */
	DECLARE_BITMAP(reg_ch_conf_pending, 64);

	/* Poपूर्णांकer that holds DMA-मित्रly block क्रम the mailbox */
	व्योम *mbox;

	/* The mbox event mask */
	u32 event_mask;
	/* events to unmask only when ap पूर्णांकerface is up */
	u32 ap_event_mask;

	/* Mailbox poपूर्णांकers */
	u32 mbox_size;
	u32 mbox_ptr[2];

	/* Are we currently scanning */
	काष्ठा wl12xx_vअगर *scan_wlvअगर;
	काष्ठा wl1271_scan scan;
	काष्ठा delayed_work scan_complete_work;

	काष्ठा ieee80211_vअगर *roc_vअगर;
	काष्ठा delayed_work roc_complete_work;

	काष्ठा wl12xx_vअगर *sched_vअगर;

	/* The current band */
	क्रमागत nl80211_band band;

	काष्ठा completion *elp_compl;

	/* in dBm */
	पूर्णांक घातer_level;

	काष्ठा wl1271_stats stats;

	__le32 *buffer_32;
	u32 buffer_cmd;
	u32 buffer_busyword[WL1271_BUSY_WORD_CNT];

	व्योम *raw_fw_status;
	काष्ठा wl_fw_status *fw_status;
	काष्ठा wl1271_tx_hw_res_अगर *tx_res_अगर;

	/* Current chipset configuration */
	काष्ठा wlcore_conf conf;

	bool sg_enabled;

	bool enable_11a;

	पूर्णांक recovery_count;

	/* Most recently reported noise in dBm */
	s8 noise;

	/* bands supported by this instance of wl12xx */
	काष्ठा ieee80211_supported_band bands[WLCORE_NUM_BANDS];

	/*
	 * wowlan trigger was configured during suspend.
	 * (currently, only "ANY" trigger is supported)
	 */
	bool wow_enabled;
	bool irq_wake_enabled;

	/*
	 * AP-mode - links indexed by HLID. The global and broadcast links
	 * are always active.
	 */
	काष्ठा wl1271_link links[WLCORE_MAX_LINKS];

	/* number of currently active links */
	पूर्णांक active_link_count;

	/* Fast/slow links biपंचांगap according to FW */
	अचिन्हित दीर्घ fw_fast_lnk_map;

	/* AP-mode - a biपंचांगap of links currently in PS mode according to FW */
	अचिन्हित दीर्घ ap_fw_ps_map;

	/* AP-mode - a biपंचांगap of links currently in PS mode in mac80211 */
	अचिन्हित दीर्घ ap_ps_map;

	/* Quirks of specअगरic hardware revisions */
	अचिन्हित पूर्णांक quirks;

	/* number of currently active RX BA sessions */
	पूर्णांक ba_rx_session_count;

	/* Maximum number of supported RX BA sessions */
	पूर्णांक ba_rx_session_count_max;

	/* AP-mode - number of currently connected stations */
	पूर्णांक active_sta_count;

	/* Flag determining whether AP should broadcast OFDM-only rates */
	bool ofdm_only_ap;

	/* last wlvअगर we transmitted from */
	काष्ठा wl12xx_vअगर *last_wlvअगर;

	/* work to fire when Tx is stuck */
	काष्ठा delayed_work tx_watchकरोg_work;

	काष्ठा wlcore_ops *ops;
	/* poपूर्णांकer to the lower driver partition table */
	स्थिर काष्ठा wlcore_partition_set *ptable;
	/* poपूर्णांकer to the lower driver रेजिस्टर table */
	स्थिर पूर्णांक *rtable;
	/* name of the firmwares to load - क्रम PLT, single role, multi-role */
	स्थिर अक्षर *plt_fw_name;
	स्थिर अक्षर *sr_fw_name;
	स्थिर अक्षर *mr_fw_name;

	u8 scan_templ_id_2_4;
	u8 scan_templ_id_5;
	u8 sched_scan_templ_id_2_4;
	u8 sched_scan_templ_id_5;
	u8 max_channels_5;

	/* per-chip-family निजी काष्ठाure */
	व्योम *priv;

	/* number of TX descriptors the HW supports. */
	u32 num_tx_desc;
	/* number of RX descriptors the HW supports. */
	u32 num_rx_desc;
	/* number of links the HW supports */
	u8 num_links;
	/* max stations a single AP can support */
	u8 max_ap_stations;

	/* translate HW Tx rates to standard rate-indices */
	स्थिर u8 **band_rate_to_idx;

	/* size of table क्रम HW rates that can be received from chip */
	u8 hw_tx_rate_tbl_size;

	/* this HW rate and below are considered HT rates क्रम this chip */
	u8 hw_min_ht_rate;

	/* HW HT (11n) capabilities */
	काष्ठा ieee80211_sta_ht_cap ht_cap[WLCORE_NUM_BANDS];

	/* the current dfs region */
	क्रमागत nl80211_dfs_regions dfs_region;
	bool radar_debug_mode;

	/* size of the निजी FW status data */
	माप_प्रकार fw_status_len;
	माप_प्रकार fw_status_priv_len;

	/* RX Data filter rule state - enabled/disabled */
	अचिन्हित दीर्घ rx_filter_enabled[BITS_TO_LONGS(WL1271_MAX_RX_FILTERS)];

	/* size of the निजी अटल data */
	माप_प्रकार अटल_data_priv_len;

	/* the current channel type */
	क्रमागत nl80211_channel_type channel_type;

	/* mutex क्रम protecting the tx_flush function */
	काष्ठा mutex flush_mutex;

	/* sleep auth value currently configured to FW */
	पूर्णांक sleep_auth;

	/* the number of allocated MAC addresses in this chip */
	पूर्णांक num_mac_addr;

	/* minimum FW version required क्रम the driver to work in single-role */
	अचिन्हित पूर्णांक min_sr_fw_ver[NUM_FW_VER];

	/* minimum FW version required क्रम the driver to work in multi-role */
	अचिन्हित पूर्णांक min_mr_fw_ver[NUM_FW_VER];

	काष्ठा completion nvs_loading_complete;

	/* पूर्णांकerface combinations supported by the hw */
	स्थिर काष्ठा ieee80211_अगरace_combination *अगरace_combinations;
	u8 n_अगरace_combinations;

	/* dynamic fw traces */
	u32 dynamic_fw_traces;

	/* समय sync zone master */
	u8 zone_master_mac_addr[ETH_ALEN];
पूर्ण;

पूर्णांक wlcore_probe(काष्ठा wl1271 *wl, काष्ठा platक्रमm_device *pdev);
पूर्णांक wlcore_हटाओ(काष्ठा platक्रमm_device *pdev);
काष्ठा ieee80211_hw *wlcore_alloc_hw(माप_प्रकार priv_size, u32 aggr_buf_size,
				     u32 mbox_size);
पूर्णांक wlcore_मुक्त_hw(काष्ठा wl1271 *wl);
पूर्णांक wlcore_set_key(काष्ठा wl1271 *wl, क्रमागत set_key_cmd cmd,
		   काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta,
		   काष्ठा ieee80211_key_conf *key_conf);
व्योम wlcore_regकरोमुख्य_config(काष्ठा wl1271 *wl);
व्योम wlcore_update_inconn_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा wl1271_station *wl_sta, bool in_conn);

अटल अंतरभूत व्योम
wlcore_set_ht_cap(काष्ठा wl1271 *wl, क्रमागत nl80211_band band,
		  काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	स_नकल(&wl->ht_cap[band], ht_cap, माप(*ht_cap));
पूर्ण

/* Tell wlcore not to care about this element when checking the version */
#घोषणा WLCORE_FW_VER_IGNORE	-1

अटल अंतरभूत व्योम
wlcore_set_min_fw_ver(काष्ठा wl1271 *wl, अचिन्हित पूर्णांक chip,
		      अचिन्हित पूर्णांक अगरtype_sr, अचिन्हित पूर्णांक major_sr,
		      अचिन्हित पूर्णांक subtype_sr, अचिन्हित पूर्णांक minor_sr,
		      अचिन्हित पूर्णांक अगरtype_mr, अचिन्हित पूर्णांक major_mr,
		      अचिन्हित पूर्णांक subtype_mr, अचिन्हित पूर्णांक minor_mr)
अणु
	wl->min_sr_fw_ver[FW_VER_CHIP] = chip;
	wl->min_sr_fw_ver[FW_VER_IF_TYPE] = अगरtype_sr;
	wl->min_sr_fw_ver[FW_VER_MAJOR] = major_sr;
	wl->min_sr_fw_ver[FW_VER_SUBTYPE] = subtype_sr;
	wl->min_sr_fw_ver[FW_VER_MINOR] = minor_sr;

	wl->min_mr_fw_ver[FW_VER_CHIP] = chip;
	wl->min_mr_fw_ver[FW_VER_IF_TYPE] = अगरtype_mr;
	wl->min_mr_fw_ver[FW_VER_MAJOR] = major_mr;
	wl->min_mr_fw_ver[FW_VER_SUBTYPE] = subtype_mr;
	wl->min_mr_fw_ver[FW_VER_MINOR] = minor_mr;
पूर्ण

/* Firmware image load chunk size */
#घोषणा CHUNK_SIZE	16384

/* Quirks */

/* Each RX/TX transaction requires an end-of-transaction transfer */
#घोषणा WLCORE_QUIRK_END_OF_TRANSACTION		BIT(0)

/* wl127x and SPI करोn't support SDIO block size alignment */
#घोषणा WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN		BIT(2)

/* means aggregated Rx packets are aligned to a SDIO block */
#घोषणा WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN		BIT(3)

/* Older firmwares did not implement the FW logger over bus feature */
#घोषणा WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED	BIT(4)

/* Older firmwares use an old NVS क्रमmat */
#घोषणा WLCORE_QUIRK_LEGACY_NVS			BIT(5)

/* pad only the last frame in the aggregate buffer */
#घोषणा WLCORE_QUIRK_TX_PAD_LAST_FRAME		BIT(7)

/* extra header space is required क्रम TKIP */
#घोषणा WLCORE_QUIRK_TKIP_HEADER_SPACE		BIT(8)

/* Some firmwares not support sched scans जबतक connected */
#घोषणा WLCORE_QUIRK_NO_SCHED_SCAN_WHILE_CONN	BIT(9)

/* separate probe response ढाँचाs क्रम one-shot and sched scans */
#घोषणा WLCORE_QUIRK_DUAL_PROBE_TMPL		BIT(10)

/* Firmware requires reg करोमुख्य configuration क्रम active calibration */
#घोषणा WLCORE_QUIRK_REGDOMAIN_CONF		BIT(11)

/* The FW only support a zero session id क्रम AP */
#घोषणा WLCORE_QUIRK_AP_ZERO_SESSION_ID		BIT(12)

/* TODO: move all these common रेजिस्टरs and values अन्यथाwhere */
#घोषणा HW_ACCESS_ELP_CTRL_REG		0x1FFFC

/* ELP रेजिस्टर commands */
#घोषणा ELPCTRL_WAKE_UP             0x1
#घोषणा ELPCTRL_WAKE_UP_WLAN_READY  0x5
#घोषणा ELPCTRL_SLEEP               0x0
/* ELP WLAN_READY bit */
#घोषणा ELPCTRL_WLAN_READY          0x2

/*************************************************************************

    Interrupt Trigger Register (Host -> WiLink)

**************************************************************************/

/* Hardware to Embedded CPU Interrupts - first 32-bit रेजिस्टर set */

/*
 * The host sets this bit to inक्रमm the Wlan
 * FW that a TX packet is in the XFER
 * Buffer #0.
 */
#घोषणा INTR_TRIG_TX_PROC0 BIT(2)

/*
 * The host sets this bit to inक्रमm the FW
 * that it पढ़ो a packet from RX XFER
 * Buffer #0.
 */
#घोषणा INTR_TRIG_RX_PROC0 BIT(3)

#घोषणा INTR_TRIG_DEBUG_ACK BIT(4)

#घोषणा INTR_TRIG_STATE_CHANGED BIT(5)

/* Hardware to Embedded CPU Interrupts - second 32-bit रेजिस्टर set */

/*
 * The host sets this bit to inक्रमm the FW
 * that it पढ़ो a packet from RX XFER
 * Buffer #1.
 */
#घोषणा INTR_TRIG_RX_PROC1 BIT(17)

/*
 * The host sets this bit to inक्रमm the Wlan
 * hardware that a TX packet is in the XFER
 * Buffer #1.
 */
#घोषणा INTR_TRIG_TX_PROC1 BIT(18)

#घोषणा ACX_SLV_SOFT_RESET_BIT	BIT(1)
#घोषणा SOFT_RESET_MAX_TIME	1000000
#घोषणा SOFT_RESET_STALL_TIME	1000

#घोषणा ECPU_CONTROL_HALT	0x00000101

#घोषणा WELP_ARM_COMMAND_VAL	0x4

#पूर्ण_अगर /* __WLCORE_H__ */
