<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file contains definitions and data काष्ठाures specअगरic
 * to Marvell 802.11 NIC. It contains the Device Inक्रमmation
 * काष्ठाure काष्ठा lbs_निजी..
 */
#अगर_अघोषित _LBS_DEV_H_
#घोषणा _LBS_DEV_H_

#समावेश "defs.h"
#समावेश "decl.h"
#समावेश "host.h"

#समावेश <linux/kfअगरo.h>

/* sleep_params */
काष्ठा sleep_params अणु
	uपूर्णांक16_t sp_error;
	uपूर्णांक16_t sp_offset;
	uपूर्णांक16_t sp_stableसमय;
	uपूर्णांक8_t  sp_calcontrol;
	uपूर्णांक8_t  sp_extsleepclk;
	uपूर्णांक16_t sp_reserved;
पूर्ण;

/* Mesh statistics */
काष्ठा lbs_mesh_stats अणु
	u32	fwd_bcast_cnt;		/* Fwd: Broadcast counter */
	u32	fwd_unicast_cnt;	/* Fwd: Unicast counter */
	u32	fwd_drop_ttl;		/* Fwd: TTL zero */
	u32	fwd_drop_rbt;		/* Fwd: Recently Broadcasted */
	u32	fwd_drop_noroute; 	/* Fwd: No route to Destination */
	u32	fwd_drop_nobuf;		/* Fwd: Run out of पूर्णांकernal buffers */
	u32	drop_blind;		/* Rx:  Dropped by blinding table */
	u32	tx_failed_cnt;		/* Tx:  Failed transmissions */
पूर्ण;

/* Private काष्ठाure क्रम the MV device */
काष्ठा lbs_निजी अणु

	/* Basic networking */
	काष्ठा net_device *dev;
	u32 connect_status;
	काष्ठा work_काष्ठा mcast_work;
	u32 nr_of_multicasपंचांगacaddr;
	u8 multicastlist[MRVDRV_MAX_MULTICAST_LIST_SIZE][ETH_ALEN];

	/* CFG80211 */
	काष्ठा wireless_dev *wdev;
	bool wiphy_रेजिस्टरed;
	काष्ठा cfg80211_scan_request *scan_req;
	u8 assoc_bss[ETH_ALEN];
	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	u8 disassoc_reason;

	/* Mesh */
	काष्ठा net_device *mesh_dev; /* Virtual device */
#अगर_घोषित CONFIG_LIBERTAS_MESH
	काष्ठा lbs_mesh_stats mstats;
	uपूर्णांक16_t mesh_tlv;
	u8 mesh_channel;
#पूर्ण_अगर

	/* Debugfs */
	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_debug;
	काष्ठा dentry *debugfs_files[6];
	काष्ठा dentry *events_dir;
	काष्ठा dentry *debugfs_events_files[6];
	काष्ठा dentry *regs_dir;
	काष्ठा dentry *debugfs_regs_files[6];

	/* Hardware debugging */
	u32 mac_offset;
	u32 bbp_offset;
	u32 rf_offset;

	/* Power management */
	u16 psmode;
	u32 psstate;
	u8 needtowakeup;

	/* Deep sleep */
	पूर्णांक is_deep_sleep;
	पूर्णांक deep_sleep_required;
	पूर्णांक is_स्वतः_deep_sleep_enabled;
	पूर्णांक wakeup_dev_required;
	पूर्णांक is_activity_detected;
	पूर्णांक स्वतः_deep_sleep_समयout; /* in ms */
	रुको_queue_head_t ds_awake_q;
	काष्ठा समयr_list स्वतः_deepsleep_समयr;

	/* Host sleep*/
	पूर्णांक is_host_sleep_configured;
	पूर्णांक is_host_sleep_activated;
	रुको_queue_head_t host_sleep_q;

	/* Hardware access */
	व्योम *card;
	bool अगरace_running;
	u8 is_polling; /* host has to poll the card irq */
	u8 fw_पढ़ोy;
	u8 surpriseहटाओd;
	u8 setup_fw_on_resume;
	u8 घातer_up_on_resume;
	पूर्णांक (*hw_host_to_card) (काष्ठा lbs_निजी *priv, u8 type, u8 *payload, u16 nb);
	व्योम (*reset_card) (काष्ठा lbs_निजी *priv);
	पूर्णांक (*घातer_save) (काष्ठा lbs_निजी *priv);
	पूर्णांक (*घातer_restore) (काष्ठा lbs_निजी *priv);
	पूर्णांक (*enter_deep_sleep) (काष्ठा lbs_निजी *priv);
	पूर्णांक (*निकास_deep_sleep) (काष्ठा lbs_निजी *priv);
	पूर्णांक (*reset_deep_sleep_wakeup) (काष्ठा lbs_निजी *priv);

	/* Adapter info (from EEPROM) */
	u32 fwrelease;
	u32 fwcapinfo;
	u16 regioncode;
	u8 current_addr[ETH_ALEN];
	u8 copied_hwaddr;

	/* Command करोwnload */
	u8 dnld_sent;
	/* bit0 1/0=data_sent/data_tx_करोne,
	   bit1 1/0=cmd_sent/cmd_tx_करोne,
	   all other bits reserved 0 */
	u16 seqnum;
	काष्ठा cmd_ctrl_node *cmd_array;
	काष्ठा cmd_ctrl_node *cur_cmd;
	काष्ठा list_head cmdमुक्तq;    /* मुक्त command buffers */
	काष्ठा list_head cmdpendingq; /* pending command buffers */
	काष्ठा समयr_list command_समयr;
	पूर्णांक cmd_समयd_out;

	/* Command responses sent from the hardware to the driver */
	u8 resp_idx;
	u8 resp_buf[2][LBS_UPLD_SIZE];
	u32 resp_len[2];

	/* Events sent from hardware to driver */
	काष्ठा kfअगरo event_fअगरo;

	/* thपढ़ो to service पूर्णांकerrupts */
	काष्ठा task_काष्ठा *मुख्य_thपढ़ो;
	रुको_queue_head_t रुकोq;
	काष्ठा workqueue_काष्ठा *work_thपढ़ो;

	/* Encryption stuff */
	u8 authtype_स्वतः;
	u8 wep_tx_key;
	u8 wep_key[4][WLAN_KEY_LEN_WEP104];
	u8 wep_key_len[4];

	/* Wake On LAN */
	uपूर्णांक32_t wol_criteria;
	uपूर्णांक8_t wol_gpio;
	uपूर्णांक8_t wol_gap;
	bool ehs_हटाओ_supported;

	/* Transmitting */
	पूर्णांक tx_pending_len;		/* -1 जबतक building packet */
	u8 tx_pending_buf[LBS_UPLD_SIZE];
	/* रक्षित by hard_start_xmit serialization */
	u8 txretrycount;
	काष्ठा sk_buff *currenttxskb;
	काष्ठा समयr_list tx_lockup_समयr;

	/* Locks */
	काष्ठा mutex lock;
	spinlock_t driver_lock;

	/* NIC/link operation अक्षरacteristics */
	u16 mac_control;
	u8 radio_on;
	u8 cur_rate;
	u8 channel;
	s16 txघातer_cur;
	s16 txघातer_min;
	s16 txघातer_max;

	/* Scanning */
	काष्ठा delayed_work scan_work;
	पूर्णांक scan_channel;
	/* Queue of things रुकोing क्रम scan completion */
	रुको_queue_head_t scan_q;
	/* Whether the scan was initiated पूर्णांकernally and not by cfg80211 */
	bool पूर्णांकernal_scan;

	/* Firmware load */
	u32 fw_model;
	रुको_queue_head_t fw_रुकोq;
	काष्ठा device *fw_device;
	स्थिर काष्ठा firmware *helper_fw;
	स्थिर काष्ठा lbs_fw_table *fw_table;
	स्थिर काष्ठा lbs_fw_table *fw_iter;
	lbs_fw_cb fw_callback;
पूर्ण;

बाह्य काष्ठा cmd_confirm_sleep confirm_sleep;

/* Check अगर there is an पूर्णांकerface active. */
अटल अंतरभूत पूर्णांक lbs_अगरace_active(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक r;

	r = netअगर_running(priv->dev);
	अगर (priv->mesh_dev)
		r |= netअगर_running(priv->mesh_dev);

	वापस r;
पूर्ण

#पूर्ण_अगर
