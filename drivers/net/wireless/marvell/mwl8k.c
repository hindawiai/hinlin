<शैली गुरु>
/*
 * drivers/net/wireless/mwl8k.c
 * Driver क्रम Marvell TOPDOG 802.11 Wireless cards
 *
 * Copyright (C) 2008, 2009, 2010 Marvell Semiconductor Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/firmware.h>
#समावेश <linux/workqueue.h>

#घोषणा MWL8K_DESC	"Marvell TOPDOG(R) 802.11 Wireless Network Driver"
#घोषणा MWL8K_NAME	KBUILD_MODNAME
#घोषणा MWL8K_VERSION	"0.13"

/* Module parameters */
अटल bool ap_mode_शेष;
module_param(ap_mode_शेष, bool, 0);
MODULE_PARM_DESC(ap_mode_शेष,
		 "Set to 1 to make ap mode the default instead of sta mode");

/* Register definitions */
#घोषणा MWL8K_HIU_GEN_PTR			0x00000c10
#घोषणा  MWL8K_MODE_STA				 0x0000005a
#घोषणा  MWL8K_MODE_AP				 0x000000a5
#घोषणा MWL8K_HIU_INT_CODE			0x00000c14
#घोषणा  MWL8K_FWSTA_READY			 0xf0f1f2f4
#घोषणा  MWL8K_FWAP_READY			 0xf1f2f4a5
#घोषणा  MWL8K_INT_CODE_CMD_FINISHED		 0x00000005
#घोषणा MWL8K_HIU_SCRATCH			0x00000c40

/* Host->device communications */
#घोषणा MWL8K_HIU_H2A_INTERRUPT_EVENTS		0x00000c18
#घोषणा MWL8K_HIU_H2A_INTERRUPT_STATUS		0x00000c1c
#घोषणा MWL8K_HIU_H2A_INTERRUPT_MASK		0x00000c20
#घोषणा MWL8K_HIU_H2A_INTERRUPT_CLEAR_SEL	0x00000c24
#घोषणा MWL8K_HIU_H2A_INTERRUPT_STATUS_MASK	0x00000c28
#घोषणा  MWL8K_H2A_INT_DUMMY			 (1 << 20)
#घोषणा  MWL8K_H2A_INT_RESET			 (1 << 15)
#घोषणा  MWL8K_H2A_INT_DOORBELL			 (1 << 1)
#घोषणा  MWL8K_H2A_INT_PPA_READY		 (1 << 0)

/* Device->host communications */
#घोषणा MWL8K_HIU_A2H_INTERRUPT_EVENTS		0x00000c2c
#घोषणा MWL8K_HIU_A2H_INTERRUPT_STATUS		0x00000c30
#घोषणा MWL8K_HIU_A2H_INTERRUPT_MASK		0x00000c34
#घोषणा MWL8K_HIU_A2H_INTERRUPT_CLEAR_SEL	0x00000c38
#घोषणा MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK	0x00000c3c
#घोषणा  MWL8K_A2H_INT_DUMMY			 (1 << 20)
#घोषणा  MWL8K_A2H_INT_BA_WATCHDOG		 (1 << 14)
#घोषणा  MWL8K_A2H_INT_CHNL_SWITCHED		 (1 << 11)
#घोषणा  MWL8K_A2H_INT_QUEUE_EMPTY		 (1 << 10)
#घोषणा  MWL8K_A2H_INT_RADAR_DETECT		 (1 << 7)
#घोषणा  MWL8K_A2H_INT_RADIO_ON			 (1 << 6)
#घोषणा  MWL8K_A2H_INT_RADIO_OFF		 (1 << 5)
#घोषणा  MWL8K_A2H_INT_MAC_EVENT		 (1 << 3)
#घोषणा  MWL8K_A2H_INT_OPC_DONE			 (1 << 2)
#घोषणा  MWL8K_A2H_INT_RX_READY			 (1 << 1)
#घोषणा  MWL8K_A2H_INT_TX_DONE			 (1 << 0)

/* HW micro second समयr रेजिस्टर
 * located at offset 0xA600. This
 * will be used to बारtamp tx
 * packets.
 */

#घोषणा	MWL8K_HW_TIMER_REGISTER			0x0000a600
#घोषणा BBU_RXRDY_CNT_REG			0x0000a860
#घोषणा NOK_CCA_CNT_REG				0x0000a6a0
#घोषणा BBU_AVG_NOISE_VAL			0x67

#घोषणा MWL8K_A2H_EVENTS	(MWL8K_A2H_INT_DUMMY | \
				 MWL8K_A2H_INT_CHNL_SWITCHED | \
				 MWL8K_A2H_INT_QUEUE_EMPTY | \
				 MWL8K_A2H_INT_RADAR_DETECT | \
				 MWL8K_A2H_INT_RADIO_ON | \
				 MWL8K_A2H_INT_RADIO_OFF | \
				 MWL8K_A2H_INT_MAC_EVENT | \
				 MWL8K_A2H_INT_OPC_DONE | \
				 MWL8K_A2H_INT_RX_READY | \
				 MWL8K_A2H_INT_TX_DONE | \
				 MWL8K_A2H_INT_BA_WATCHDOG)

#घोषणा MWL8K_RX_QUEUES		1
#घोषणा MWL8K_TX_WMM_QUEUES	4
#घोषणा MWL8K_MAX_AMPDU_QUEUES	8
#घोषणा MWL8K_MAX_TX_QUEUES	(MWL8K_TX_WMM_QUEUES + MWL8K_MAX_AMPDU_QUEUES)
#घोषणा mwl8k_tx_queues(priv)	(MWL8K_TX_WMM_QUEUES + (priv)->num_ampdu_queues)

/* txpriorities are mapped with hw queues.
 * Each hw queue has a txpriority.
 */
#घोषणा TOTAL_HW_TX_QUEUES	8

/* Each HW queue can have one AMPDU stream.
 * But, because one of the hw queue is reserved,
 * maximum AMPDU queues that can be created are
 * one लघु of total tx queues.
 */
#घोषणा MWL8K_NUM_AMPDU_STREAMS	(TOTAL_HW_TX_QUEUES - 1)

#घोषणा MWL8K_NUM_CHANS 18

काष्ठा rxd_ops अणु
	पूर्णांक rxd_size;
	व्योम (*rxd_init)(व्योम *rxd, dma_addr_t next_dma_addr);
	व्योम (*rxd_refill)(व्योम *rxd, dma_addr_t addr, पूर्णांक len);
	पूर्णांक (*rxd_process)(व्योम *rxd, काष्ठा ieee80211_rx_status *status,
			   __le16 *qos, s8 *noise);
पूर्ण;

काष्ठा mwl8k_device_info अणु
	अक्षर *part_name;
	अक्षर *helper_image;
	अक्षर *fw_image_sta;
	अक्षर *fw_image_ap;
	काष्ठा rxd_ops *ap_rxd_ops;
	u32 fw_api_ap;
पूर्ण;

काष्ठा mwl8k_rx_queue अणु
	पूर्णांक rxd_count;

	/* hw receives here */
	पूर्णांक head;

	/* refill descs here */
	पूर्णांक tail;

	व्योम *rxd;
	dma_addr_t rxd_dma;
	काष्ठा अणु
		काष्ठा sk_buff *skb;
		DEFINE_DMA_UNMAP_ADDR(dma);
	पूर्ण *buf;
पूर्ण;

काष्ठा mwl8k_tx_queue अणु
	/* hw transmits here */
	पूर्णांक head;

	/* sw appends here */
	पूर्णांक tail;

	अचिन्हित पूर्णांक len;
	काष्ठा mwl8k_tx_desc *txd;
	dma_addr_t txd_dma;
	काष्ठा sk_buff **skb;
पूर्ण;

क्रमागत अणु
	AMPDU_NO_STREAM,
	AMPDU_STREAM_NEW,
	AMPDU_STREAM_IN_PROGRESS,
	AMPDU_STREAM_ACTIVE,
पूर्ण;

काष्ठा mwl8k_ampdu_stream अणु
	काष्ठा ieee80211_sta *sta;
	u8 tid;
	u8 state;
	u8 idx;
पूर्ण;

काष्ठा mwl8k_priv अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा pci_dev *pdev;
	पूर्णांक irq;

	काष्ठा mwl8k_device_info *device_info;

	व्योम __iomem *sram;
	व्योम __iomem *regs;

	/* firmware */
	स्थिर काष्ठा firmware *fw_helper;
	स्थिर काष्ठा firmware *fw_ucode;

	/* hardware/firmware parameters */
	bool ap_fw;
	काष्ठा rxd_ops *rxd_ops;
	काष्ठा ieee80211_supported_band band_24;
	काष्ठा ieee80211_channel channels_24[14];
	काष्ठा ieee80211_rate rates_24[13];
	काष्ठा ieee80211_supported_band band_50;
	काष्ठा ieee80211_channel channels_50[9];
	काष्ठा ieee80211_rate rates_50[8];
	u32 ap_macids_supported;
	u32 sta_macids_supported;

	/* Ampdu stream inक्रमmation */
	u8 num_ampdu_queues;
	spinlock_t stream_lock;
	काष्ठा mwl8k_ampdu_stream ampdu[MWL8K_MAX_AMPDU_QUEUES];
	काष्ठा work_काष्ठा watchकरोg_ba_handle;

	/* firmware access */
	काष्ठा mutex fw_mutex;
	काष्ठा task_काष्ठा *fw_mutex_owner;
	काष्ठा task_काष्ठा *hw_restart_owner;
	पूर्णांक fw_mutex_depth;
	काष्ठा completion *hostcmd_रुको;

	atomic_t watchकरोg_event_pending;

	/* lock held over TX and TX reap */
	spinlock_t tx_lock;

	/* TX quiesce completion, रक्षित by fw_mutex and tx_lock */
	काष्ठा completion *tx_रुको;

	/* List of पूर्णांकerfaces.  */
	u32 macids_used;
	काष्ठा list_head vअगर_list;

	/* घातer management status cookie from firmware */
	u32 *cookie;
	dma_addr_t cookie_dma;

	u16 num_mcaddrs;
	u8 hw_rev;
	u32 fw_rev;
	u32 caps;

	/*
	 * Running count of TX packets in flight, to aव्योम
	 * iterating over the transmit rings each समय.
	 */
	पूर्णांक pending_tx_pkts;

	काष्ठा mwl8k_rx_queue rxq[MWL8K_RX_QUEUES];
	काष्ठा mwl8k_tx_queue txq[MWL8K_MAX_TX_QUEUES];
	u32 txq_offset[MWL8K_MAX_TX_QUEUES];

	bool radio_on;
	bool radio_लघु_preamble;
	bool snअगरfer_enabled;
	bool wmm_enabled;

	/* XXX need to convert this to handle multiple पूर्णांकerfaces */
	bool capture_beacon;
	u8 capture_bssid[ETH_ALEN];
	काष्ठा sk_buff *beacon_skb;

	/*
	 * This FJ worker has to be global as it is scheduled from the
	 * RX handler.  At this poपूर्णांक we करोn't know which पूर्णांकerface it
	 * beदीर्घs to until the list of bssids रुकोing to complete join
	 * is checked.
	 */
	काष्ठा work_काष्ठा finalize_join_worker;

	/* Tasklet to perक्रमm TX reclaim.  */
	काष्ठा tasklet_काष्ठा poll_tx_task;

	/* Tasklet to perक्रमm RX.  */
	काष्ठा tasklet_काष्ठा poll_rx_task;

	/* Most recently reported noise in dBm */
	s8 noise;

	/*
	 * preserve the queue configurations so they can be restored अगर/when
	 * the firmware image is swapped.
	 */
	काष्ठा ieee80211_tx_queue_params wmm_params[MWL8K_TX_WMM_QUEUES];

	/* To perक्रमm the task of reloading the firmware */
	काष्ठा work_काष्ठा fw_reload;
	bool hw_restart_in_progress;

	/* async firmware loading state */
	अचिन्हित fw_state;
	अक्षर *fw_pref;
	अक्षर *fw_alt;
	bool is_8764;
	काष्ठा completion firmware_loading_complete;

	/* biपंचांगap of running BSSes */
	u32 running_bsses;

	/* ACS related */
	bool sw_scan_start;
	काष्ठा ieee80211_channel *acs_chan;
	अचिन्हित दीर्घ channel_समय;
	काष्ठा survey_info survey[MWL8K_NUM_CHANS];
पूर्ण;

#घोषणा MAX_WEP_KEY_LEN         13
#घोषणा NUM_WEP_KEYS            4

/* Per पूर्णांकerface specअगरic निजी data */
काष्ठा mwl8k_vअगर अणु
	काष्ठा list_head list;
	काष्ठा ieee80211_vअगर *vअगर;

	/* Firmware macid क्रम this vअगर.  */
	पूर्णांक macid;

	/* Non AMPDU sequence number asचिन्हित by driver.  */
	u16 seqno;

	/* Saved WEP keys */
	काष्ठा अणु
		u8 enabled;
		u8 key[माप(काष्ठा ieee80211_key_conf) + MAX_WEP_KEY_LEN];
	पूर्ण wep_key_conf[NUM_WEP_KEYS];

	/* BSSID */
	u8 bssid[ETH_ALEN];

	/* A flag to indicate is HW crypto is enabled क्रम this bssid */
	bool is_hw_crypto_enabled;
पूर्ण;
#घोषणा MWL8K_VIF(_vअगर) ((काष्ठा mwl8k_vअगर *)&((_vअगर)->drv_priv))
#घोषणा IEEE80211_KEY_CONF(_u8) ((काष्ठा ieee80211_key_conf *)(_u8))

काष्ठा tx_traffic_info अणु
	u32 start_समय;
	u32 pkts;
पूर्ण;

#घोषणा MWL8K_MAX_TID 8
काष्ठा mwl8k_sta अणु
	/* Index पूर्णांकo station database. Returned by UPDATE_STADB.  */
	u8 peer_id;
	u8 is_ampdu_allowed;
	काष्ठा tx_traffic_info tx_stats[MWL8K_MAX_TID];
पूर्ण;
#घोषणा MWL8K_STA(_sta) ((काष्ठा mwl8k_sta *)&((_sta)->drv_priv))

अटल स्थिर काष्ठा ieee80211_channel mwl8k_channels_24[] = अणु
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2412, .hw_value = 1, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2417, .hw_value = 2, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2422, .hw_value = 3, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2427, .hw_value = 4, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2432, .hw_value = 5, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2437, .hw_value = 6, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2442, .hw_value = 7, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2447, .hw_value = 8, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2452, .hw_value = 9, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2457, .hw_value = 10, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2462, .hw_value = 11, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2467, .hw_value = 12, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2472, .hw_value = 13, पूर्ण,
	अणु .band = NL80211_BAND_2GHZ, .center_freq = 2484, .hw_value = 14, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_rate mwl8k_rates_24[] = अणु
	अणु .bitrate = 10, .hw_value = 2, पूर्ण,
	अणु .bitrate = 20, .hw_value = 4, पूर्ण,
	अणु .bitrate = 55, .hw_value = 11, पूर्ण,
	अणु .bitrate = 110, .hw_value = 22, पूर्ण,
	अणु .bitrate = 220, .hw_value = 44, पूर्ण,
	अणु .bitrate = 60, .hw_value = 12, पूर्ण,
	अणु .bitrate = 90, .hw_value = 18, पूर्ण,
	अणु .bitrate = 120, .hw_value = 24, पूर्ण,
	अणु .bitrate = 180, .hw_value = 36, पूर्ण,
	अणु .bitrate = 240, .hw_value = 48, पूर्ण,
	अणु .bitrate = 360, .hw_value = 72, पूर्ण,
	अणु .bitrate = 480, .hw_value = 96, पूर्ण,
	अणु .bitrate = 540, .hw_value = 108, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel mwl8k_channels_50[] = अणु
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5180, .hw_value = 36, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5200, .hw_value = 40, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5220, .hw_value = 44, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5240, .hw_value = 48, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5745, .hw_value = 149, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5765, .hw_value = 153, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5785, .hw_value = 157, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5805, .hw_value = 161, पूर्ण,
	अणु .band = NL80211_BAND_5GHZ, .center_freq = 5825, .hw_value = 165, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_rate mwl8k_rates_50[] = अणु
	अणु .bitrate = 60, .hw_value = 12, पूर्ण,
	अणु .bitrate = 90, .hw_value = 18, पूर्ण,
	अणु .bitrate = 120, .hw_value = 24, पूर्ण,
	अणु .bitrate = 180, .hw_value = 36, पूर्ण,
	अणु .bitrate = 240, .hw_value = 48, पूर्ण,
	अणु .bitrate = 360, .hw_value = 72, पूर्ण,
	अणु .bitrate = 480, .hw_value = 96, पूर्ण,
	अणु .bitrate = 540, .hw_value = 108, पूर्ण,
पूर्ण;

/* Set or get info from Firmware */
#घोषणा MWL8K_CMD_GET			0x0000
#घोषणा MWL8K_CMD_SET			0x0001
#घोषणा MWL8K_CMD_SET_LIST		0x0002

/* Firmware command codes */
#घोषणा MWL8K_CMD_CODE_DNLD		0x0001
#घोषणा MWL8K_CMD_GET_HW_SPEC		0x0003
#घोषणा MWL8K_CMD_SET_HW_SPEC		0x0004
#घोषणा MWL8K_CMD_MAC_MULTICAST_ADR	0x0010
#घोषणा MWL8K_CMD_GET_STAT		0x0014
#घोषणा MWL8K_CMD_BBP_REG_ACCESS	0x001a
#घोषणा MWL8K_CMD_RADIO_CONTROL		0x001c
#घोषणा MWL8K_CMD_RF_TX_POWER		0x001e
#घोषणा MWL8K_CMD_TX_POWER		0x001f
#घोषणा MWL8K_CMD_RF_ANTENNA		0x0020
#घोषणा MWL8K_CMD_SET_BEACON		0x0100		/* per-vअगर */
#घोषणा MWL8K_CMD_SET_PRE_SCAN		0x0107
#घोषणा MWL8K_CMD_SET_POST_SCAN		0x0108
#घोषणा MWL8K_CMD_SET_RF_CHANNEL	0x010a
#घोषणा MWL8K_CMD_SET_AID		0x010d
#घोषणा MWL8K_CMD_SET_RATE		0x0110
#घोषणा MWL8K_CMD_SET_FINALIZE_JOIN	0x0111
#घोषणा MWL8K_CMD_RTS_THRESHOLD		0x0113
#घोषणा MWL8K_CMD_SET_SLOT		0x0114
#घोषणा MWL8K_CMD_SET_EDCA_PARAMS	0x0115
#घोषणा MWL8K_CMD_SET_WMM_MODE		0x0123
#घोषणा MWL8K_CMD_MIMO_CONFIG		0x0125
#घोषणा MWL8K_CMD_USE_FIXED_RATE	0x0126
#घोषणा MWL8K_CMD_ENABLE_SNIFFER	0x0150
#घोषणा MWL8K_CMD_SET_MAC_ADDR		0x0202		/* per-vअगर */
#घोषणा MWL8K_CMD_SET_RATEADAPT_MODE	0x0203
#घोषणा MWL8K_CMD_GET_WATCHDOG_BITMAP	0x0205
#घोषणा MWL8K_CMD_DEL_MAC_ADDR		0x0206		/* per-vअगर */
#घोषणा MWL8K_CMD_BSS_START		0x1100		/* per-vअगर */
#घोषणा MWL8K_CMD_SET_NEW_STN		0x1111		/* per-vअगर */
#घोषणा MWL8K_CMD_UPDATE_ENCRYPTION	0x1122		/* per-vअगर */
#घोषणा MWL8K_CMD_UPDATE_STADB		0x1123
#घोषणा MWL8K_CMD_BASTREAM		0x1125

#घोषणा MWL8K_LEGACY_5G_RATE_OFFSET \
	(ARRAY_SIZE(mwl8k_rates_24) - ARRAY_SIZE(mwl8k_rates_50))

अटल स्थिर अक्षर *mwl8k_cmd_name(__le16 cmd, अक्षर *buf, पूर्णांक bufsize)
अणु
	u16 command = le16_to_cpu(cmd);

#घोषणा MWL8K_CMDNAME(x)	हाल MWL8K_CMD_##x: करो अणु\
					snम_लिखो(buf, bufsize, "%s", #x);\
					वापस buf;\
					पूर्ण जबतक (0)
	चयन (command & ~0x8000) अणु
		MWL8K_CMDNAME(CODE_DNLD);
		MWL8K_CMDNAME(GET_HW_SPEC);
		MWL8K_CMDNAME(SET_HW_SPEC);
		MWL8K_CMDNAME(MAC_MULTICAST_ADR);
		MWL8K_CMDNAME(GET_STAT);
		MWL8K_CMDNAME(RADIO_CONTROL);
		MWL8K_CMDNAME(RF_TX_POWER);
		MWL8K_CMDNAME(TX_POWER);
		MWL8K_CMDNAME(RF_ANTENNA);
		MWL8K_CMDNAME(SET_BEACON);
		MWL8K_CMDNAME(SET_PRE_SCAN);
		MWL8K_CMDNAME(SET_POST_SCAN);
		MWL8K_CMDNAME(SET_RF_CHANNEL);
		MWL8K_CMDNAME(SET_AID);
		MWL8K_CMDNAME(SET_RATE);
		MWL8K_CMDNAME(SET_FINALIZE_JOIN);
		MWL8K_CMDNAME(RTS_THRESHOLD);
		MWL8K_CMDNAME(SET_SLOT);
		MWL8K_CMDNAME(SET_EDCA_PARAMS);
		MWL8K_CMDNAME(SET_WMM_MODE);
		MWL8K_CMDNAME(MIMO_CONFIG);
		MWL8K_CMDNAME(USE_FIXED_RATE);
		MWL8K_CMDNAME(ENABLE_SNIFFER);
		MWL8K_CMDNAME(SET_MAC_ADDR);
		MWL8K_CMDNAME(SET_RATEADAPT_MODE);
		MWL8K_CMDNAME(BSS_START);
		MWL8K_CMDNAME(SET_NEW_STN);
		MWL8K_CMDNAME(UPDATE_ENCRYPTION);
		MWL8K_CMDNAME(UPDATE_STADB);
		MWL8K_CMDNAME(BASTREAM);
		MWL8K_CMDNAME(GET_WATCHDOG_BITMAP);
	शेष:
		snम_लिखो(buf, bufsize, "0x%x", cmd);
	पूर्ण
#अघोषित MWL8K_CMDNAME

	वापस buf;
पूर्ण

/* Hardware and firmware reset */
अटल व्योम mwl8k_hw_reset(काष्ठा mwl8k_priv *priv)
अणु
	ioग_लिखो32(MWL8K_H2A_INT_RESET,
		priv->regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	ioग_लिखो32(MWL8K_H2A_INT_RESET,
		priv->regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	msleep(20);
पूर्ण

/* Release fw image */
अटल व्योम mwl8k_release_fw(स्थिर काष्ठा firmware **fw)
अणु
	अगर (*fw == शून्य)
		वापस;
	release_firmware(*fw);
	*fw = शून्य;
पूर्ण

अटल व्योम mwl8k_release_firmware(काष्ठा mwl8k_priv *priv)
अणु
	mwl8k_release_fw(&priv->fw_ucode);
	mwl8k_release_fw(&priv->fw_helper);
पूर्ण

/* states क्रम asynchronous f/w loading */
अटल व्योम mwl8k_fw_state_machine(स्थिर काष्ठा firmware *fw, व्योम *context);
क्रमागत अणु
	FW_STATE_INIT = 0,
	FW_STATE_LOADING_PREF,
	FW_STATE_LOADING_ALT,
	FW_STATE_ERROR,
पूर्ण;

/* Request fw image */
अटल पूर्णांक mwl8k_request_fw(काष्ठा mwl8k_priv *priv,
			    स्थिर अक्षर *fname, स्थिर काष्ठा firmware **fw,
			    bool noरुको)
अणु
	/* release current image */
	अगर (*fw != शून्य)
		mwl8k_release_fw(fw);

	अगर (noरुको)
		वापस request_firmware_noरुको(THIS_MODULE, 1, fname,
					       &priv->pdev->dev, GFP_KERNEL,
					       priv, mwl8k_fw_state_machine);
	अन्यथा
		वापस request_firmware(fw, fname, &priv->pdev->dev);
पूर्ण

अटल पूर्णांक mwl8k_request_firmware(काष्ठा mwl8k_priv *priv, अक्षर *fw_image,
				  bool noरुको)
अणु
	काष्ठा mwl8k_device_info *di = priv->device_info;
	पूर्णांक rc;

	अगर (di->helper_image != शून्य) अणु
		अगर (noरुको)
			rc = mwl8k_request_fw(priv, di->helper_image,
					      &priv->fw_helper, true);
		अन्यथा
			rc = mwl8k_request_fw(priv, di->helper_image,
					      &priv->fw_helper, false);
		अगर (rc)
			prपूर्णांकk(KERN_ERR "%s: Error requesting helper fw %s\n",
			       pci_name(priv->pdev), di->helper_image);

		अगर (rc || noरुको)
			वापस rc;
	पूर्ण

	अगर (noरुको) अणु
		/*
		 * अगर we get here, no helper image is needed.  Skip the
		 * FW_STATE_INIT state.
		 */
		priv->fw_state = FW_STATE_LOADING_PREF;
		rc = mwl8k_request_fw(priv, fw_image,
				      &priv->fw_ucode,
				      true);
	पूर्ण अन्यथा
		rc = mwl8k_request_fw(priv, fw_image,
				      &priv->fw_ucode, false);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error requesting firmware file %s\n",
		       pci_name(priv->pdev), fw_image);
		mwl8k_release_fw(&priv->fw_helper);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा mwl8k_cmd_pkt अणु
	__le16	code;
	__le16	length;
	__u8	seq_num;
	__u8	macid;
	__le16	result;
	अक्षर	payload[];
पूर्ण __packed;

/*
 * Firmware loading.
 */
अटल पूर्णांक
mwl8k_send_fw_load_cmd(काष्ठा mwl8k_priv *priv, व्योम *data, पूर्णांक length)
अणु
	व्योम __iomem *regs = priv->regs;
	dma_addr_t dma_addr;
	पूर्णांक loops;

	dma_addr = dma_map_single(&priv->pdev->dev, data, length,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->pdev->dev, dma_addr))
		वापस -ENOMEM;

	ioग_लिखो32(dma_addr, regs + MWL8K_HIU_GEN_PTR);
	ioग_लिखो32(0, regs + MWL8K_HIU_INT_CODE);
	ioग_लिखो32(MWL8K_H2A_INT_DOORBELL,
		regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	ioग_लिखो32(MWL8K_H2A_INT_DUMMY,
		regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);

	loops = 1000;
	करो अणु
		u32 पूर्णांक_code;
		अगर (priv->is_8764) अणु
			पूर्णांक_code = ioपढ़ो32(regs +
					    MWL8K_HIU_H2A_INTERRUPT_STATUS);
			अगर (पूर्णांक_code == 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			पूर्णांक_code = ioपढ़ो32(regs + MWL8K_HIU_INT_CODE);
			अगर (पूर्णांक_code == MWL8K_INT_CODE_CMD_FINISHED) अणु
				ioग_लिखो32(0, regs + MWL8K_HIU_INT_CODE);
				अवरोध;
			पूर्ण
		पूर्ण
		cond_resched();
		udelay(1);
	पूर्ण जबतक (--loops);

	dma_unmap_single(&priv->pdev->dev, dma_addr, length, DMA_TO_DEVICE);

	वापस loops ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक mwl8k_load_fw_image(काष्ठा mwl8k_priv *priv,
				स्थिर u8 *data, माप_प्रकार length)
अणु
	काष्ठा mwl8k_cmd_pkt *cmd;
	पूर्णांक करोne;
	पूर्णांक rc = 0;

	cmd = kदो_स्मृति(माप(*cmd) + 256, GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->code = cpu_to_le16(MWL8K_CMD_CODE_DNLD);
	cmd->seq_num = 0;
	cmd->macid = 0;
	cmd->result = 0;

	करोne = 0;
	जबतक (length) अणु
		पूर्णांक block_size = length > 256 ? 256 : length;

		स_नकल(cmd->payload, data + करोne, block_size);
		cmd->length = cpu_to_le16(block_size);

		rc = mwl8k_send_fw_load_cmd(priv, cmd,
						माप(*cmd) + block_size);
		अगर (rc)
			अवरोध;

		करोne += block_size;
		length -= block_size;
	पूर्ण

	अगर (!rc) अणु
		cmd->length = 0;
		rc = mwl8k_send_fw_load_cmd(priv, cmd, माप(*cmd));
	पूर्ण

	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_feed_fw_image(काष्ठा mwl8k_priv *priv,
				स्थिर u8 *data, माप_प्रकार length)
अणु
	अचिन्हित अक्षर *buffer;
	पूर्णांक may_जारी, rc = 0;
	u32 करोne, prev_block_size;

	buffer = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (buffer == शून्य)
		वापस -ENOMEM;

	करोne = 0;
	prev_block_size = 0;
	may_जारी = 1000;
	जबतक (may_जारी > 0) अणु
		u32 block_size;

		block_size = ioपढ़ो32(priv->regs + MWL8K_HIU_SCRATCH);
		अगर (block_size & 1) अणु
			block_size &= ~1;
			may_जारी--;
		पूर्ण अन्यथा अणु
			करोne += prev_block_size;
			length -= prev_block_size;
		पूर्ण

		अगर (block_size > 1024 || block_size > length) अणु
			rc = -EOVERFLOW;
			अवरोध;
		पूर्ण

		अगर (length == 0) अणु
			rc = 0;
			अवरोध;
		पूर्ण

		अगर (block_size == 0) अणु
			rc = -EPROTO;
			may_जारी--;
			udelay(1);
			जारी;
		पूर्ण

		prev_block_size = block_size;
		स_नकल(buffer, data + करोne, block_size);

		rc = mwl8k_send_fw_load_cmd(priv, buffer, block_size);
		अगर (rc)
			अवरोध;
	पूर्ण

	अगर (!rc && length != 0)
		rc = -EREMOTEIO;

	kमुक्त(buffer);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_load_firmware(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	स्थिर काष्ठा firmware *fw = priv->fw_ucode;
	पूर्णांक rc;
	पूर्णांक loops;

	अगर (!स_भेद(fw->data, "\x01\x00\x00\x00", 4) && !priv->is_8764) अणु
		स्थिर काष्ठा firmware *helper = priv->fw_helper;

		अगर (helper == शून्य) अणु
			prपूर्णांकk(KERN_ERR "%s: helper image needed but none "
			       "given\n", pci_name(priv->pdev));
			वापस -EINVAL;
		पूर्ण

		rc = mwl8k_load_fw_image(priv, helper->data, helper->size);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: unable to load firmware "
			       "helper image\n", pci_name(priv->pdev));
			वापस rc;
		पूर्ण
		msleep(20);

		rc = mwl8k_feed_fw_image(priv, fw->data, fw->size);
	पूर्ण अन्यथा अणु
		अगर (priv->is_8764)
			rc = mwl8k_feed_fw_image(priv, fw->data, fw->size);
		अन्यथा
			rc = mwl8k_load_fw_image(priv, fw->data, fw->size);
	पूर्ण

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to load firmware image\n",
		       pci_name(priv->pdev));
		वापस rc;
	पूर्ण

	ioग_लिखो32(MWL8K_MODE_STA, priv->regs + MWL8K_HIU_GEN_PTR);

	loops = 500000;
	करो अणु
		u32 पढ़ोy_code;

		पढ़ोy_code = ioपढ़ो32(priv->regs + MWL8K_HIU_INT_CODE);
		अगर (पढ़ोy_code == MWL8K_FWAP_READY) अणु
			priv->ap_fw = true;
			अवरोध;
		पूर्ण अन्यथा अगर (पढ़ोy_code == MWL8K_FWSTA_READY) अणु
			priv->ap_fw = false;
			अवरोध;
		पूर्ण

		cond_resched();
		udelay(1);
	पूर्ण जबतक (--loops);

	वापस loops ? 0 : -ETIMEDOUT;
पूर्ण


/* DMA header used by firmware and hardware.  */
काष्ठा mwl8k_dma_data अणु
	__le16 fwlen;
	काष्ठा ieee80211_hdr wh;
	अक्षर data[];
पूर्ण __packed __aligned(2);

/* Routines to add/हटाओ DMA header from skb.  */
अटल अंतरभूत व्योम mwl8k_हटाओ_dma_header(काष्ठा sk_buff *skb, __le16 qos)
अणु
	काष्ठा mwl8k_dma_data *tr;
	पूर्णांक hdrlen;

	tr = (काष्ठा mwl8k_dma_data *)skb->data;
	hdrlen = ieee80211_hdrlen(tr->wh.frame_control);

	अगर (hdrlen != माप(tr->wh)) अणु
		अगर (ieee80211_is_data_qos(tr->wh.frame_control)) अणु
			स_हटाओ(tr->data - hdrlen, &tr->wh, hdrlen - 2);
			*((__le16 *)(tr->data - 2)) = qos;
		पूर्ण अन्यथा अणु
			स_हटाओ(tr->data - hdrlen, &tr->wh, hdrlen);
		पूर्ण
	पूर्ण

	अगर (hdrlen != माप(*tr))
		skb_pull(skb, माप(*tr) - hdrlen);
पूर्ण

#घोषणा REDUCED_TX_HEADROOM	8

अटल व्योम
mwl8k_add_dma_header(काष्ठा mwl8k_priv *priv, काष्ठा sk_buff *skb,
						पूर्णांक head_pad, पूर्णांक tail_pad)
अणु
	काष्ठा ieee80211_hdr *wh;
	पूर्णांक hdrlen;
	पूर्णांक reqd_hdrlen;
	काष्ठा mwl8k_dma_data *tr;

	/*
	 * Add a firmware DMA header; the firmware requires that we
	 * present a 2-byte payload length followed by a 4-address
	 * header (without QoS field), followed (optionally) by any
	 * WEP/ExtIV header (but only filled in क्रम CCMP).
	 */
	wh = (काष्ठा ieee80211_hdr *)skb->data;

	hdrlen = ieee80211_hdrlen(wh->frame_control);

	/*
	 * Check अगर skb_resize is required because of
	 * tx_headroom adjusपंचांगent.
	 */
	अगर (priv->ap_fw && (hdrlen < (माप(काष्ठा ieee80211_cts)
						+ REDUCED_TX_HEADROOM))) अणु
		अगर (pskb_expand_head(skb, REDUCED_TX_HEADROOM, 0, GFP_ATOMIC)) अणु

			wiphy_err(priv->hw->wiphy,
					"Failed to reallocate TX buffer\n");
			वापस;
		पूर्ण
		skb->truesize += REDUCED_TX_HEADROOM;
	पूर्ण

	reqd_hdrlen = माप(*tr) + head_pad;

	अगर (hdrlen != reqd_hdrlen)
		skb_push(skb, reqd_hdrlen - hdrlen);

	अगर (ieee80211_is_data_qos(wh->frame_control))
		hdrlen -= IEEE80211_QOS_CTL_LEN;

	tr = (काष्ठा mwl8k_dma_data *)skb->data;
	अगर (wh != &tr->wh)
		स_हटाओ(&tr->wh, wh, hdrlen);
	अगर (hdrlen != माप(tr->wh))
		स_रखो(((व्योम *)&tr->wh) + hdrlen, 0, माप(tr->wh) - hdrlen);

	/*
	 * Firmware length is the length of the fully क्रमmed "802.11
	 * payload".  That is, everything except क्रम the 802.11 header.
	 * This includes all crypto material including the MIC.
	 */
	tr->fwlen = cpu_to_le16(skb->len - माप(*tr) + tail_pad);
पूर्ण

अटल व्योम mwl8k_encapsulate_tx_frame(काष्ठा mwl8k_priv *priv,
		काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *wh;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा ieee80211_key_conf *key_conf;
	पूर्णांक data_pad;
	पूर्णांक head_pad = 0;

	wh = (काष्ठा ieee80211_hdr *)skb->data;

	tx_info = IEEE80211_SKB_CB(skb);

	key_conf = शून्य;
	अगर (ieee80211_is_data(wh->frame_control))
		key_conf = tx_info->control.hw_key;

	/*
	 * Make sure the packet header is in the DMA header क्रमmat (4-address
	 * without QoS), and add head & tail padding when HW crypto is enabled.
	 *
	 * We have the following trailer padding requirements:
	 * - WEP: 4 trailer bytes (ICV)
	 * - TKIP: 12 trailer bytes (8 MIC + 4 ICV)
	 * - CCMP: 8 trailer bytes (MIC)
	 */
	data_pad = 0;
	अगर (key_conf != शून्य) अणु
		head_pad = key_conf->iv_len;
		चयन (key_conf->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			data_pad = 4;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			data_pad = 12;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			data_pad = 8;
			अवरोध;
		पूर्ण
	पूर्ण
	mwl8k_add_dma_header(priv, skb, head_pad, data_pad);
पूर्ण

/*
 * Packet reception क्रम 88w8366/88w8764 AP firmware.
 */
काष्ठा mwl8k_rxd_ap अणु
	__le16 pkt_len;
	__u8 sq2;
	__u8 rate;
	__le32 pkt_phys_addr;
	__le32 next_rxd_phys_addr;
	__le16 qos_control;
	__le16 htsig2;
	__le32 hw_rssi_info;
	__le32 hw_noise_न्यूनमान_info;
	__u8 noise_न्यूनमान;
	__u8 pad0[3];
	__u8 rssi;
	__u8 rx_status;
	__u8 channel;
	__u8 rx_ctrl;
पूर्ण __packed;

#घोषणा MWL8K_AP_RATE_INFO_MCS_FORMAT		0x80
#घोषणा MWL8K_AP_RATE_INFO_40MHZ		0x40
#घोषणा MWL8K_AP_RATE_INFO_RATEID(x)		((x) & 0x3f)

#घोषणा MWL8K_AP_RX_CTRL_OWNED_BY_HOST		0x80

/* 8366/8764 AP rx_status bits */
#घोषणा MWL8K_AP_RXSTAT_DECRYPT_ERR_MASK		0x80
#घोषणा MWL8K_AP_RXSTAT_GENERAL_DECRYPT_ERR		0xFF
#घोषणा MWL8K_AP_RXSTAT_TKIP_DECRYPT_MIC_ERR		0x02
#घोषणा MWL8K_AP_RXSTAT_WEP_DECRYPT_ICV_ERR		0x04
#घोषणा MWL8K_AP_RXSTAT_TKIP_DECRYPT_ICV_ERR		0x08

अटल व्योम mwl8k_rxd_ap_init(व्योम *_rxd, dma_addr_t next_dma_addr)
अणु
	काष्ठा mwl8k_rxd_ap *rxd = _rxd;

	rxd->next_rxd_phys_addr = cpu_to_le32(next_dma_addr);
	rxd->rx_ctrl = MWL8K_AP_RX_CTRL_OWNED_BY_HOST;
पूर्ण

अटल व्योम mwl8k_rxd_ap_refill(व्योम *_rxd, dma_addr_t addr, पूर्णांक len)
अणु
	काष्ठा mwl8k_rxd_ap *rxd = _rxd;

	rxd->pkt_len = cpu_to_le16(len);
	rxd->pkt_phys_addr = cpu_to_le32(addr);
	wmb();
	rxd->rx_ctrl = 0;
पूर्ण

अटल पूर्णांक
mwl8k_rxd_ap_process(व्योम *_rxd, काष्ठा ieee80211_rx_status *status,
		     __le16 *qos, s8 *noise)
अणु
	काष्ठा mwl8k_rxd_ap *rxd = _rxd;

	अगर (!(rxd->rx_ctrl & MWL8K_AP_RX_CTRL_OWNED_BY_HOST))
		वापस -1;
	rmb();

	स_रखो(status, 0, माप(*status));

	status->संकेत = -rxd->rssi;
	*noise = -rxd->noise_न्यूनमान;

	अगर (rxd->rate & MWL8K_AP_RATE_INFO_MCS_FORMAT) अणु
		status->encoding = RX_ENC_HT;
		अगर (rxd->rate & MWL8K_AP_RATE_INFO_40MHZ)
			status->bw = RATE_INFO_BW_40;
		status->rate_idx = MWL8K_AP_RATE_INFO_RATEID(rxd->rate);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(mwl8k_rates_24); i++) अणु
			अगर (mwl8k_rates_24[i].hw_value == rxd->rate) अणु
				status->rate_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rxd->channel > 14) अणु
		status->band = NL80211_BAND_5GHZ;
		अगर (!(status->encoding == RX_ENC_HT) &&
		    status->rate_idx >= MWL8K_LEGACY_5G_RATE_OFFSET)
			status->rate_idx -= MWL8K_LEGACY_5G_RATE_OFFSET;
	पूर्ण अन्यथा अणु
		status->band = NL80211_BAND_2GHZ;
	पूर्ण
	status->freq = ieee80211_channel_to_frequency(rxd->channel,
						      status->band);

	*qos = rxd->qos_control;

	अगर ((rxd->rx_status != MWL8K_AP_RXSTAT_GENERAL_DECRYPT_ERR) &&
	    (rxd->rx_status & MWL8K_AP_RXSTAT_DECRYPT_ERR_MASK) &&
	    (rxd->rx_status & MWL8K_AP_RXSTAT_TKIP_DECRYPT_MIC_ERR))
		status->flag |= RX_FLAG_MMIC_ERROR;

	वापस le16_to_cpu(rxd->pkt_len);
पूर्ण

अटल काष्ठा rxd_ops rxd_ap_ops = अणु
	.rxd_size	= माप(काष्ठा mwl8k_rxd_ap),
	.rxd_init	= mwl8k_rxd_ap_init,
	.rxd_refill	= mwl8k_rxd_ap_refill,
	.rxd_process	= mwl8k_rxd_ap_process,
पूर्ण;

/*
 * Packet reception क्रम STA firmware.
 */
काष्ठा mwl8k_rxd_sta अणु
	__le16 pkt_len;
	__u8 link_quality;
	__u8 noise_level;
	__le32 pkt_phys_addr;
	__le32 next_rxd_phys_addr;
	__le16 qos_control;
	__le16 rate_info;
	__le32 pad0[4];
	__u8 rssi;
	__u8 channel;
	__le16 pad1;
	__u8 rx_ctrl;
	__u8 rx_status;
	__u8 pad2[2];
पूर्ण __packed;

#घोषणा MWL8K_STA_RATE_INFO_SHORTPRE		0x8000
#घोषणा MWL8K_STA_RATE_INFO_ANTSELECT(x)	(((x) >> 11) & 0x3)
#घोषणा MWL8K_STA_RATE_INFO_RATEID(x)		(((x) >> 3) & 0x3f)
#घोषणा MWL8K_STA_RATE_INFO_40MHZ		0x0004
#घोषणा MWL8K_STA_RATE_INFO_SHORTGI		0x0002
#घोषणा MWL8K_STA_RATE_INFO_MCS_FORMAT		0x0001

#घोषणा MWL8K_STA_RX_CTRL_OWNED_BY_HOST		0x02
#घोषणा MWL8K_STA_RX_CTRL_DECRYPT_ERROR		0x04
/* ICV=0 or MIC=1 */
#घोषणा MWL8K_STA_RX_CTRL_DEC_ERR_TYPE		0x08
/* Key is uploaded only in failure हाल */
#घोषणा MWL8K_STA_RX_CTRL_KEY_INDEX			0x30

अटल व्योम mwl8k_rxd_sta_init(व्योम *_rxd, dma_addr_t next_dma_addr)
अणु
	काष्ठा mwl8k_rxd_sta *rxd = _rxd;

	rxd->next_rxd_phys_addr = cpu_to_le32(next_dma_addr);
	rxd->rx_ctrl = MWL8K_STA_RX_CTRL_OWNED_BY_HOST;
पूर्ण

अटल व्योम mwl8k_rxd_sta_refill(व्योम *_rxd, dma_addr_t addr, पूर्णांक len)
अणु
	काष्ठा mwl8k_rxd_sta *rxd = _rxd;

	rxd->pkt_len = cpu_to_le16(len);
	rxd->pkt_phys_addr = cpu_to_le32(addr);
	wmb();
	rxd->rx_ctrl = 0;
पूर्ण

अटल पूर्णांक
mwl8k_rxd_sta_process(व्योम *_rxd, काष्ठा ieee80211_rx_status *status,
		       __le16 *qos, s8 *noise)
अणु
	काष्ठा mwl8k_rxd_sta *rxd = _rxd;
	u16 rate_info;

	अगर (!(rxd->rx_ctrl & MWL8K_STA_RX_CTRL_OWNED_BY_HOST))
		वापस -1;
	rmb();

	rate_info = le16_to_cpu(rxd->rate_info);

	स_रखो(status, 0, माप(*status));

	status->संकेत = -rxd->rssi;
	*noise = -rxd->noise_level;
	status->antenna = MWL8K_STA_RATE_INFO_ANTSELECT(rate_info);
	status->rate_idx = MWL8K_STA_RATE_INFO_RATEID(rate_info);

	अगर (rate_info & MWL8K_STA_RATE_INFO_SHORTPRE)
		status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
	अगर (rate_info & MWL8K_STA_RATE_INFO_40MHZ)
		status->bw = RATE_INFO_BW_40;
	अगर (rate_info & MWL8K_STA_RATE_INFO_SHORTGI)
		status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
	अगर (rate_info & MWL8K_STA_RATE_INFO_MCS_FORMAT)
		status->encoding = RX_ENC_HT;

	अगर (rxd->channel > 14) अणु
		status->band = NL80211_BAND_5GHZ;
		अगर (!(status->encoding == RX_ENC_HT) &&
		    status->rate_idx >= MWL8K_LEGACY_5G_RATE_OFFSET)
			status->rate_idx -= MWL8K_LEGACY_5G_RATE_OFFSET;
	पूर्ण अन्यथा अणु
		status->band = NL80211_BAND_2GHZ;
	पूर्ण
	status->freq = ieee80211_channel_to_frequency(rxd->channel,
						      status->band);

	*qos = rxd->qos_control;
	अगर ((rxd->rx_ctrl & MWL8K_STA_RX_CTRL_DECRYPT_ERROR) &&
	    (rxd->rx_ctrl & MWL8K_STA_RX_CTRL_DEC_ERR_TYPE))
		status->flag |= RX_FLAG_MMIC_ERROR;

	वापस le16_to_cpu(rxd->pkt_len);
पूर्ण

अटल काष्ठा rxd_ops rxd_sta_ops = अणु
	.rxd_size	= माप(काष्ठा mwl8k_rxd_sta),
	.rxd_init	= mwl8k_rxd_sta_init,
	.rxd_refill	= mwl8k_rxd_sta_refill,
	.rxd_process	= mwl8k_rxd_sta_process,
पूर्ण;


#घोषणा MWL8K_RX_DESCS		256
#घोषणा MWL8K_RX_MAXSZ		3800

अटल पूर्णांक mwl8k_rxq_init(काष्ठा ieee80211_hw *hw, पूर्णांक index)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_rx_queue *rxq = priv->rxq + index;
	पूर्णांक size;
	पूर्णांक i;

	rxq->rxd_count = 0;
	rxq->head = 0;
	rxq->tail = 0;

	size = MWL8K_RX_DESCS * priv->rxd_ops->rxd_size;

	rxq->rxd = dma_alloc_coherent(&priv->pdev->dev, size, &rxq->rxd_dma,
				      GFP_KERNEL);
	अगर (rxq->rxd == शून्य) अणु
		wiphy_err(hw->wiphy, "failed to alloc RX descriptors\n");
		वापस -ENOMEM;
	पूर्ण

	rxq->buf = kसुस्मृति(MWL8K_RX_DESCS, माप(*rxq->buf), GFP_KERNEL);
	अगर (rxq->buf == शून्य) अणु
		dma_मुक्त_coherent(&priv->pdev->dev, size, rxq->rxd,
				  rxq->rxd_dma);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < MWL8K_RX_DESCS; i++) अणु
		पूर्णांक desc_size;
		व्योम *rxd;
		पूर्णांक nexti;
		dma_addr_t next_dma_addr;

		desc_size = priv->rxd_ops->rxd_size;
		rxd = rxq->rxd + (i * priv->rxd_ops->rxd_size);

		nexti = i + 1;
		अगर (nexti == MWL8K_RX_DESCS)
			nexti = 0;
		next_dma_addr = rxq->rxd_dma + (nexti * desc_size);

		priv->rxd_ops->rxd_init(rxd, next_dma_addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rxq_refill(काष्ठा ieee80211_hw *hw, पूर्णांक index, पूर्णांक limit)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_rx_queue *rxq = priv->rxq + index;
	पूर्णांक refilled = 0;

	जबतक (rxq->rxd_count < MWL8K_RX_DESCS && limit--) अणु
		काष्ठा sk_buff *skb;
		dma_addr_t addr;
		पूर्णांक rx;
		व्योम *rxd;

		skb = dev_alloc_skb(MWL8K_RX_MAXSZ);
		अगर (skb == शून्य)
			अवरोध;

		addr = dma_map_single(&priv->pdev->dev, skb->data,
				      MWL8K_RX_MAXSZ, DMA_FROM_DEVICE);

		rxq->rxd_count++;
		rx = rxq->tail++;
		अगर (rxq->tail == MWL8K_RX_DESCS)
			rxq->tail = 0;
		rxq->buf[rx].skb = skb;
		dma_unmap_addr_set(&rxq->buf[rx], dma, addr);

		rxd = rxq->rxd + (rx * priv->rxd_ops->rxd_size);
		priv->rxd_ops->rxd_refill(rxd, addr, MWL8K_RX_MAXSZ);

		refilled++;
	पूर्ण

	वापस refilled;
पूर्ण

/* Must be called only when the card's reception is completely halted */
अटल व्योम mwl8k_rxq_deinit(काष्ठा ieee80211_hw *hw, पूर्णांक index)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_rx_queue *rxq = priv->rxq + index;
	पूर्णांक i;

	अगर (rxq->rxd == शून्य)
		वापस;

	क्रम (i = 0; i < MWL8K_RX_DESCS; i++) अणु
		अगर (rxq->buf[i].skb != शून्य) अणु
			dma_unmap_single(&priv->pdev->dev,
					 dma_unmap_addr(&rxq->buf[i], dma),
					 MWL8K_RX_MAXSZ, DMA_FROM_DEVICE);
			dma_unmap_addr_set(&rxq->buf[i], dma, 0);

			kमुक्त_skb(rxq->buf[i].skb);
			rxq->buf[i].skb = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(rxq->buf);
	rxq->buf = शून्य;

	dma_मुक्त_coherent(&priv->pdev->dev,
			  MWL8K_RX_DESCS * priv->rxd_ops->rxd_size, rxq->rxd,
			  rxq->rxd_dma);
	rxq->rxd = शून्य;
पूर्ण


/*
 * Scan a list of BSSIDs to process क्रम finalize join.
 * Allows क्रम extension to process multiple BSSIDs.
 */
अटल अंतरभूत पूर्णांक
mwl8k_capture_bssid(काष्ठा mwl8k_priv *priv, काष्ठा ieee80211_hdr *wh)
अणु
	वापस priv->capture_beacon &&
		ieee80211_is_beacon(wh->frame_control) &&
		ether_addr_equal_64bits(wh->addr3, priv->capture_bssid);
पूर्ण

अटल अंतरभूत व्योम mwl8k_save_beacon(काष्ठा ieee80211_hw *hw,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	priv->capture_beacon = false;
	eth_zero_addr(priv->capture_bssid);

	/*
	 * Use GFP_ATOMIC as rxq_process is called from
	 * the primary पूर्णांकerrupt handler, memory allocation call
	 * must not sleep.
	 */
	priv->beacon_skb = skb_copy(skb, GFP_ATOMIC);
	अगर (priv->beacon_skb != शून्य)
		ieee80211_queue_work(hw, &priv->finalize_join_worker);
पूर्ण

अटल अंतरभूत काष्ठा mwl8k_vअगर *mwl8k_find_vअगर_bss(काष्ठा list_head *vअगर_list,
						   u8 *bssid)
अणु
	काष्ठा mwl8k_vअगर *mwl8k_vअगर;

	list_क्रम_each_entry(mwl8k_vअगर,
			    vअगर_list, list) अणु
		अगर (स_भेद(bssid, mwl8k_vअगर->bssid,
			   ETH_ALEN) == 0)
			वापस mwl8k_vअगर;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक rxq_process(काष्ठा ieee80211_hw *hw, पूर्णांक index, पूर्णांक limit)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = शून्य;
	काष्ठा mwl8k_rx_queue *rxq = priv->rxq + index;
	पूर्णांक processed;

	processed = 0;
	जबतक (rxq->rxd_count && limit--) अणु
		काष्ठा sk_buff *skb;
		व्योम *rxd;
		पूर्णांक pkt_len;
		काष्ठा ieee80211_rx_status status;
		काष्ठा ieee80211_hdr *wh;
		__le16 qos;

		skb = rxq->buf[rxq->head].skb;
		अगर (skb == शून्य)
			अवरोध;

		rxd = rxq->rxd + (rxq->head * priv->rxd_ops->rxd_size);

		pkt_len = priv->rxd_ops->rxd_process(rxd, &status, &qos,
							&priv->noise);
		अगर (pkt_len < 0)
			अवरोध;

		rxq->buf[rxq->head].skb = शून्य;

		dma_unmap_single(&priv->pdev->dev,
				 dma_unmap_addr(&rxq->buf[rxq->head], dma),
				 MWL8K_RX_MAXSZ, DMA_FROM_DEVICE);
		dma_unmap_addr_set(&rxq->buf[rxq->head], dma, 0);

		rxq->head++;
		अगर (rxq->head == MWL8K_RX_DESCS)
			rxq->head = 0;

		rxq->rxd_count--;

		wh = &((काष्ठा mwl8k_dma_data *)skb->data)->wh;

		/*
		 * Check क्रम a pending join operation.  Save a
		 * copy of the beacon and schedule a tasklet to
		 * send a FINALIZE_JOIN command to the firmware.
		 */
		अगर (mwl8k_capture_bssid(priv, (व्योम *)skb->data))
			mwl8k_save_beacon(hw, skb);

		अगर (ieee80211_has_रक्षित(wh->frame_control)) अणु

			/* Check अगर hw crypto has been enabled क्रम
			 * this bss. If yes, set the status flags
			 * accordingly
			 */
			mwl8k_vअगर = mwl8k_find_vअगर_bss(&priv->vअगर_list,
								wh->addr1);

			अगर (mwl8k_vअगर != शून्य &&
			    mwl8k_vअगर->is_hw_crypto_enabled) अणु
				/*
				 * When MMIC ERROR is encountered
				 * by the firmware, payload is
				 * dropped and only 32 bytes of
				 * mwl8k Firmware header is sent
				 * to the host.
				 *
				 * We need to add four bytes of
				 * key inक्रमmation.  In it
				 * MAC80211 expects keyidx set to
				 * 0 क्रम triggering Counter
				 * Measure of MMIC failure.
				 */
				अगर (status.flag & RX_FLAG_MMIC_ERROR) अणु
					काष्ठा mwl8k_dma_data *tr;
					tr = (काष्ठा mwl8k_dma_data *)skb->data;
					स_रखो((व्योम *)&(tr->data), 0, 4);
					pkt_len += 4;
				पूर्ण

				अगर (!ieee80211_is_auth(wh->frame_control))
					status.flag |= RX_FLAG_IV_STRIPPED |
						       RX_FLAG_DECRYPTED |
						       RX_FLAG_MMIC_STRIPPED;
			पूर्ण
		पूर्ण

		skb_put(skb, pkt_len);
		mwl8k_हटाओ_dma_header(skb, qos);
		स_नकल(IEEE80211_SKB_RXCB(skb), &status, माप(status));
		ieee80211_rx_irqsafe(hw, skb);

		processed++;
	पूर्ण

	वापस processed;
पूर्ण


/*
 * Packet transmission.
 */

#घोषणा MWL8K_TXD_STATUS_OK			0x00000001
#घोषणा MWL8K_TXD_STATUS_OK_RETRY		0x00000002
#घोषणा MWL8K_TXD_STATUS_OK_MORE_RETRY		0x00000004
#घोषणा MWL8K_TXD_STATUS_MULTICAST_TX		0x00000008
#घोषणा MWL8K_TXD_STATUS_FW_OWNED		0x80000000

#घोषणा MWL8K_QOS_QLEN_UNSPEC			0xff00
#घोषणा MWL8K_QOS_ACK_POLICY_MASK		0x0060
#घोषणा MWL8K_QOS_ACK_POLICY_NORMAL		0x0000
#घोषणा MWL8K_QOS_ACK_POLICY_BLOCKACK		0x0060
#घोषणा MWL8K_QOS_EOSP				0x0010

काष्ठा mwl8k_tx_desc अणु
	__le32 status;
	__u8 data_rate;
	__u8 tx_priority;
	__le16 qos_control;
	__le32 pkt_phys_addr;
	__le16 pkt_len;
	__u8 dest_MAC_addr[ETH_ALEN];
	__le32 next_txd_phys_addr;
	__le32 बारtamp;
	__le16 rate_info;
	__u8 peer_id;
	__u8 tx_frag_cnt;
पूर्ण __packed;

#घोषणा MWL8K_TX_DESCS		128

अटल पूर्णांक mwl8k_txq_init(काष्ठा ieee80211_hw *hw, पूर्णांक index)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_tx_queue *txq = priv->txq + index;
	पूर्णांक size;
	पूर्णांक i;

	txq->len = 0;
	txq->head = 0;
	txq->tail = 0;

	size = MWL8K_TX_DESCS * माप(काष्ठा mwl8k_tx_desc);

	txq->txd = dma_alloc_coherent(&priv->pdev->dev, size, &txq->txd_dma,
				      GFP_KERNEL);
	अगर (txq->txd == शून्य) अणु
		wiphy_err(hw->wiphy, "failed to alloc TX descriptors\n");
		वापस -ENOMEM;
	पूर्ण

	txq->skb = kसुस्मृति(MWL8K_TX_DESCS, माप(*txq->skb), GFP_KERNEL);
	अगर (txq->skb == शून्य) अणु
		dma_मुक्त_coherent(&priv->pdev->dev, size, txq->txd,
				  txq->txd_dma);
		txq->txd = शून्य;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < MWL8K_TX_DESCS; i++) अणु
		काष्ठा mwl8k_tx_desc *tx_desc;
		पूर्णांक nexti;

		tx_desc = txq->txd + i;
		nexti = (i + 1) % MWL8K_TX_DESCS;

		tx_desc->status = 0;
		tx_desc->next_txd_phys_addr =
			cpu_to_le32(txq->txd_dma + nexti * माप(*tx_desc));
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mwl8k_tx_start(काष्ठा mwl8k_priv *priv)
अणु
	ioग_लिखो32(MWL8K_H2A_INT_PPA_READY,
		priv->regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	ioग_लिखो32(MWL8K_H2A_INT_DUMMY,
		priv->regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	ioपढ़ो32(priv->regs + MWL8K_HIU_INT_CODE);
पूर्ण

अटल व्योम mwl8k_dump_tx_rings(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक i;

	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++) अणु
		काष्ठा mwl8k_tx_queue *txq = priv->txq + i;
		पूर्णांक fw_owned = 0;
		पूर्णांक drv_owned = 0;
		पूर्णांक unused = 0;
		पूर्णांक desc;

		क्रम (desc = 0; desc < MWL8K_TX_DESCS; desc++) अणु
			काष्ठा mwl8k_tx_desc *tx_desc = txq->txd + desc;
			u32 status;

			status = le32_to_cpu(tx_desc->status);
			अगर (status & MWL8K_TXD_STATUS_FW_OWNED)
				fw_owned++;
			अन्यथा
				drv_owned++;

			अगर (tx_desc->pkt_len == 0)
				unused++;
		पूर्ण

		wiphy_err(hw->wiphy,
			  "txq[%d] len=%d head=%d tail=%d "
			  "fw_owned=%d drv_owned=%d unused=%d\n",
			  i,
			  txq->len, txq->head, txq->tail,
			  fw_owned, drv_owned, unused);
	पूर्ण
पूर्ण

/*
 * Must be called with priv->fw_mutex held and tx queues stopped.
 */
#घोषणा MWL8K_TX_WAIT_TIMEOUT_MS	5000

अटल पूर्णांक mwl8k_tx_रुको_empty(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	DECLARE_COMPLETION_ONSTACK(tx_रुको);
	पूर्णांक retry;
	पूर्णांक rc;

	might_sleep();

	/* Since fw restart is in progress, allow only the firmware
	 * commands from the restart code and block the other
	 * commands since they are going to fail in any हाल since
	 * the firmware has crashed
	 */
	अगर (priv->hw_restart_in_progress) अणु
		अगर (priv->hw_restart_owner == current)
			वापस 0;
		अन्यथा
			वापस -EBUSY;
	पूर्ण

	अगर (atomic_पढ़ो(&priv->watchकरोg_event_pending))
		वापस 0;

	/*
	 * The TX queues are stopped at this poपूर्णांक, so this test
	 * करोesn't need to take ->tx_lock.
	 */
	अगर (!priv->pending_tx_pkts)
		वापस 0;

	retry = 1;
	rc = 0;

	spin_lock_bh(&priv->tx_lock);
	priv->tx_रुको = &tx_रुको;
	जबतक (!rc) अणु
		पूर्णांक oldcount;
		अचिन्हित दीर्घ समयout;

		oldcount = priv->pending_tx_pkts;

		spin_unlock_bh(&priv->tx_lock);
		समयout = रुको_क्रम_completion_समयout(&tx_रुको,
			    msecs_to_jअगरfies(MWL8K_TX_WAIT_TIMEOUT_MS));

		अगर (atomic_पढ़ो(&priv->watchकरोg_event_pending)) अणु
			spin_lock_bh(&priv->tx_lock);
			priv->tx_रुको = शून्य;
			spin_unlock_bh(&priv->tx_lock);
			वापस 0;
		पूर्ण

		spin_lock_bh(&priv->tx_lock);

		अगर (समयout || !priv->pending_tx_pkts) अणु
			WARN_ON(priv->pending_tx_pkts);
			अगर (retry)
				wiphy_notice(hw->wiphy, "tx rings drained\n");
			अवरोध;
		पूर्ण

		अगर (retry) अणु
			mwl8k_tx_start(priv);
			retry = 0;
			जारी;
		पूर्ण

		अगर (priv->pending_tx_pkts < oldcount) अणु
			wiphy_notice(hw->wiphy,
				     "waiting for tx rings to drain (%d -> %d pkts)\n",
				     oldcount, priv->pending_tx_pkts);
			retry = 1;
			जारी;
		पूर्ण

		priv->tx_रुको = शून्य;

		wiphy_err(hw->wiphy, "tx rings stuck for %d ms\n",
			  MWL8K_TX_WAIT_TIMEOUT_MS);
		mwl8k_dump_tx_rings(hw);
		priv->hw_restart_in_progress = true;
		ieee80211_queue_work(hw, &priv->fw_reload);

		rc = -ETIMEDOUT;
	पूर्ण
	priv->tx_रुको = शून्य;
	spin_unlock_bh(&priv->tx_lock);

	वापस rc;
पूर्ण

#घोषणा MWL8K_TXD_SUCCESS(status)				\
	((status) & (MWL8K_TXD_STATUS_OK |			\
		     MWL8K_TXD_STATUS_OK_RETRY |		\
		     MWL8K_TXD_STATUS_OK_MORE_RETRY))

अटल पूर्णांक mwl8k_tid_queue_mapping(u8 tid)
अणु
	BUG_ON(tid > 7);

	चयन (tid) अणु
	हाल 0:
	हाल 3:
		वापस IEEE80211_AC_BE;
	हाल 1:
	हाल 2:
		वापस IEEE80211_AC_BK;
	हाल 4:
	हाल 5:
		वापस IEEE80211_AC_VI;
	हाल 6:
	हाल 7:
		वापस IEEE80211_AC_VO;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/* The firmware will fill in the rate inक्रमmation
 * क्रम each packet that माला_लो queued in the hardware
 * and these macros will पूर्णांकerpret that info.
 */

#घोषणा RI_FORMAT(a)		  (a & 0x0001)
#घोषणा RI_RATE_ID_MCS(a)	 ((a & 0x01f8) >> 3)

अटल पूर्णांक
mwl8k_txq_reclaim(काष्ठा ieee80211_hw *hw, पूर्णांक index, पूर्णांक limit, पूर्णांक क्रमce)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_tx_queue *txq = priv->txq + index;
	पूर्णांक processed;

	processed = 0;
	जबतक (txq->len > 0 && limit--) अणु
		पूर्णांक tx;
		काष्ठा mwl8k_tx_desc *tx_desc;
		अचिन्हित दीर्घ addr;
		पूर्णांक size;
		काष्ठा sk_buff *skb;
		काष्ठा ieee80211_tx_info *info;
		u32 status;
		काष्ठा ieee80211_sta *sta;
		काष्ठा mwl8k_sta *sta_info = शून्य;
		u16 rate_info;
		काष्ठा ieee80211_hdr *wh;

		tx = txq->head;
		tx_desc = txq->txd + tx;

		status = le32_to_cpu(tx_desc->status);

		अगर (status & MWL8K_TXD_STATUS_FW_OWNED) अणु
			अगर (!क्रमce)
				अवरोध;
			tx_desc->status &=
				~cpu_to_le32(MWL8K_TXD_STATUS_FW_OWNED);
		पूर्ण

		txq->head = (tx + 1) % MWL8K_TX_DESCS;
		BUG_ON(txq->len == 0);
		txq->len--;
		priv->pending_tx_pkts--;

		addr = le32_to_cpu(tx_desc->pkt_phys_addr);
		size = le16_to_cpu(tx_desc->pkt_len);
		skb = txq->skb[tx];
		txq->skb[tx] = शून्य;

		BUG_ON(skb == शून्य);
		dma_unmap_single(&priv->pdev->dev, addr, size, DMA_TO_DEVICE);

		mwl8k_हटाओ_dma_header(skb, tx_desc->qos_control);

		wh = (काष्ठा ieee80211_hdr *) skb->data;

		/* Mark descriptor as unused */
		tx_desc->pkt_phys_addr = 0;
		tx_desc->pkt_len = 0;

		info = IEEE80211_SKB_CB(skb);
		अगर (ieee80211_is_data(wh->frame_control)) अणु
			rcu_पढ़ो_lock();
			sta = ieee80211_find_sta_by_अगरaddr(hw, wh->addr1,
							   wh->addr2);
			अगर (sta) अणु
				sta_info = MWL8K_STA(sta);
				BUG_ON(sta_info == शून्य);
				rate_info = le16_to_cpu(tx_desc->rate_info);
				/* If rate is < 6.5 Mpbs क्रम an ht station
				 * करो not क्रमm an ampdu. If the station is a
				 * legacy station (क्रमmat = 0), करो not क्रमm an
				 * ampdu
				 */
				अगर (RI_RATE_ID_MCS(rate_info) < 1 ||
				    RI_FORMAT(rate_info) == 0) अणु
					sta_info->is_ampdu_allowed = false;
				पूर्ण अन्यथा अणु
					sta_info->is_ampdu_allowed = true;
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण

		ieee80211_tx_info_clear_status(info);

		/* Rate control is happening in the firmware.
		 * Ensure no tx rate is being reported.
		 */
		info->status.rates[0].idx = -1;
		info->status.rates[0].count = 1;

		अगर (MWL8K_TXD_SUCCESS(status))
			info->flags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_status_irqsafe(hw, skb);

		processed++;
	पूर्ण

	वापस processed;
पूर्ण

/* must be called only when the card's transmit is completely halted */
अटल व्योम mwl8k_txq_deinit(काष्ठा ieee80211_hw *hw, पूर्णांक index)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_tx_queue *txq = priv->txq + index;

	अगर (txq->txd == शून्य)
		वापस;

	mwl8k_txq_reclaim(hw, index, पूर्णांक_उच्च, 1);

	kमुक्त(txq->skb);
	txq->skb = शून्य;

	dma_मुक्त_coherent(&priv->pdev->dev,
			  MWL8K_TX_DESCS * माप(काष्ठा mwl8k_tx_desc),
			  txq->txd, txq->txd_dma);
	txq->txd = शून्य;
पूर्ण

/* caller must hold priv->stream_lock when calling the stream functions */
अटल काष्ठा mwl8k_ampdu_stream *
mwl8k_add_stream(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta, u8 tid)
अणु
	काष्ठा mwl8k_ampdu_stream *stream;
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक i;

	क्रम (i = 0; i < MWL8K_NUM_AMPDU_STREAMS; i++) अणु
		stream = &priv->ampdu[i];
		अगर (stream->state == AMPDU_NO_STREAM) अणु
			stream->sta = sta;
			stream->state = AMPDU_STREAM_NEW;
			stream->tid = tid;
			stream->idx = i;
			wiphy_debug(hw->wiphy, "Added a new stream for %pM %d",
				    sta->addr, tid);
			वापस stream;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
mwl8k_start_stream(काष्ठा ieee80211_hw *hw, काष्ठा mwl8k_ampdu_stream *stream)
अणु
	पूर्णांक ret;

	/* अगर the stream has alपढ़ोy been started, करोn't start it again */
	अगर (stream->state != AMPDU_STREAM_NEW)
		वापस 0;
	ret = ieee80211_start_tx_ba_session(stream->sta, stream->tid, 0);
	अगर (ret)
		wiphy_debug(hw->wiphy, "Failed to start stream for %pM %d: "
			    "%d\n", stream->sta->addr, stream->tid, ret);
	अन्यथा
		wiphy_debug(hw->wiphy, "Started stream for %pM %d\n",
			    stream->sta->addr, stream->tid);
	वापस ret;
पूर्ण

अटल व्योम
mwl8k_हटाओ_stream(काष्ठा ieee80211_hw *hw, काष्ठा mwl8k_ampdu_stream *stream)
अणु
	wiphy_debug(hw->wiphy, "Remove stream for %pM %d\n", stream->sta->addr,
		    stream->tid);
	स_रखो(stream, 0, माप(*stream));
पूर्ण

अटल काष्ठा mwl8k_ampdu_stream *
mwl8k_lookup_stream(काष्ठा ieee80211_hw *hw, u8 *addr, u8 tid)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक i;

	क्रम (i = 0; i < MWL8K_NUM_AMPDU_STREAMS; i++) अणु
		काष्ठा mwl8k_ampdu_stream *stream;
		stream = &priv->ampdu[i];
		अगर (stream->state == AMPDU_NO_STREAM)
			जारी;
		अगर (!स_भेद(stream->sta->addr, addr, ETH_ALEN) &&
		    stream->tid == tid)
			वापस stream;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा MWL8K_AMPDU_PACKET_THRESHOLD 64
अटल अंतरभूत bool mwl8k_ampdu_allowed(काष्ठा ieee80211_sta *sta, u8 tid)
अणु
	काष्ठा mwl8k_sta *sta_info = MWL8K_STA(sta);
	काष्ठा tx_traffic_info *tx_stats;

	BUG_ON(tid >= MWL8K_MAX_TID);
	tx_stats = &sta_info->tx_stats[tid];

	वापस sta_info->is_ampdu_allowed &&
		tx_stats->pkts > MWL8K_AMPDU_PACKET_THRESHOLD;
पूर्ण

अटल अंतरभूत व्योम mwl8k_tx_count_packet(काष्ठा ieee80211_sta *sta, u8 tid)
अणु
	काष्ठा mwl8k_sta *sta_info = MWL8K_STA(sta);
	काष्ठा tx_traffic_info *tx_stats;

	BUG_ON(tid >= MWL8K_MAX_TID);
	tx_stats = &sta_info->tx_stats[tid];

	अगर (tx_stats->start_समय == 0)
		tx_stats->start_समय = jअगरfies;

	/* reset the packet count after each second elapses.  If the number of
	 * packets ever exceeds the ampdu_min_traffic threshold, we will allow
	 * an ampdu stream to be started.
	 */
	अगर (jअगरfies - tx_stats->start_समय > HZ) अणु
		tx_stats->pkts = 0;
		tx_stats->start_समय = 0;
	पूर्ण अन्यथा
		tx_stats->pkts++;
पूर्ण

/* The hardware ampdu queues start from 5.
 * txpriorities क्रम ampdu queues are
 * 5 6 7 0 1 2 3 4 ie., queue 5 is highest
 * and queue 3 is lowest (queue 4 is reserved)
 */
#घोषणा BA_QUEUE		5

अटल व्योम
mwl8k_txq_xmit(काष्ठा ieee80211_hw *hw,
	       पूर्णांक index,
	       काष्ठा ieee80211_sta *sta,
	       काष्ठा sk_buff *skb)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर;
	काष्ठा ieee80211_hdr *wh;
	काष्ठा mwl8k_tx_queue *txq;
	काष्ठा mwl8k_tx_desc *tx;
	dma_addr_t dma;
	u32 txstatus;
	u8 txdatarate;
	u16 qos;
	पूर्णांक txpriority;
	u8 tid = 0;
	काष्ठा mwl8k_ampdu_stream *stream = शून्य;
	bool start_ba_session = false;
	bool mgmtframe = false;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	bool eapol_frame = false;

	wh = (काष्ठा ieee80211_hdr *)skb->data;
	अगर (ieee80211_is_data_qos(wh->frame_control))
		qos = le16_to_cpu(*((__le16 *)ieee80211_get_qos_ctl(wh)));
	अन्यथा
		qos = 0;

	अगर (skb->protocol == cpu_to_be16(ETH_P_PAE))
		eapol_frame = true;

	अगर (ieee80211_is_mgmt(wh->frame_control))
		mgmtframe = true;

	अगर (priv->ap_fw)
		mwl8k_encapsulate_tx_frame(priv, skb);
	अन्यथा
		mwl8k_add_dma_header(priv, skb, 0, 0);

	wh = &((काष्ठा mwl8k_dma_data *)skb->data)->wh;

	tx_info = IEEE80211_SKB_CB(skb);
	mwl8k_vअगर = MWL8K_VIF(tx_info->control.vअगर);

	अगर (tx_info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		wh->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		wh->seq_ctrl |= cpu_to_le16(mwl8k_vअगर->seqno);
		mwl8k_vअगर->seqno += 0x10;
	पूर्ण

	/* Setup firmware control bit fields क्रम each frame type.  */
	txstatus = 0;
	txdatarate = 0;
	अगर (ieee80211_is_mgmt(wh->frame_control) ||
	    ieee80211_is_ctl(wh->frame_control)) अणु
		txdatarate = 0;
		qos |= MWL8K_QOS_QLEN_UNSPEC | MWL8K_QOS_EOSP;
	पूर्ण अन्यथा अगर (ieee80211_is_data(wh->frame_control)) अणु
		txdatarate = 1;
		अगर (is_multicast_ether_addr(wh->addr1))
			txstatus |= MWL8K_TXD_STATUS_MULTICAST_TX;

		qos &= ~MWL8K_QOS_ACK_POLICY_MASK;
		अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU)
			qos |= MWL8K_QOS_ACK_POLICY_BLOCKACK;
		अन्यथा
			qos |= MWL8K_QOS_ACK_POLICY_NORMAL;
	पूर्ण

	/* Queue ADDBA request in the respective data queue.  While setting up
	 * the ampdu stream, mac80211 queues further packets क्रम that
	 * particular ra/tid pair.  However, packets piled up in the hardware
	 * क्रम that ra/tid pair will still go out. ADDBA request and the
	 * related data packets going out from dअगरferent queues asynchronously
	 * will cause a shअगरt in the receiver winकरोw which might result in
	 * ampdu packets getting dropped at the receiver after the stream has
	 * been setup.
	 */
	अगर (unlikely(ieee80211_is_action(wh->frame_control) &&
	    mgmt->u.action.category == WLAN_CATEGORY_BACK &&
	    mgmt->u.action.u.addba_req.action_code == WLAN_ACTION_ADDBA_REQ &&
	    priv->ap_fw)) अणु
		u16 capab = le16_to_cpu(mgmt->u.action.u.addba_req.capab);
		tid = (capab & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
		index = mwl8k_tid_queue_mapping(tid);
	पूर्ण

	txpriority = index;

	अगर (priv->ap_fw && sta && sta->ht_cap.ht_supported && !eapol_frame &&
	    ieee80211_is_data_qos(wh->frame_control)) अणु
		tid = qos & 0xf;
		mwl8k_tx_count_packet(sta, tid);
		spin_lock(&priv->stream_lock);
		stream = mwl8k_lookup_stream(hw, sta->addr, tid);
		अगर (stream != शून्य) अणु
			अगर (stream->state == AMPDU_STREAM_ACTIVE) अणु
				WARN_ON(!(qos & MWL8K_QOS_ACK_POLICY_BLOCKACK));
				txpriority = (BA_QUEUE + stream->idx) %
					     TOTAL_HW_TX_QUEUES;
				अगर (stream->idx <= 1)
					index = stream->idx +
						MWL8K_TX_WMM_QUEUES;

			पूर्ण अन्यथा अगर (stream->state == AMPDU_STREAM_NEW) अणु
				/* We get here अगर the driver sends us packets
				 * after we've initiated a stream, but beक्रमe
				 * our ampdu_action routine has been called
				 * with IEEE80211_AMPDU_TX_START to get the SSN
				 * क्रम the ADDBA request.  So this packet can
				 * go out with no risk of sequence number
				 * mismatch.  No special handling is required.
				 */
			पूर्ण अन्यथा अणु
				/* Drop packets that would go out after the
				 * ADDBA request was sent but beक्रमe the ADDBA
				 * response is received.  If we करोn't करो this,
				 * the recipient would probably receive it
				 * after the ADDBA request with SSN 0.  This
				 * will cause the recipient's BA receive winकरोw
				 * to shअगरt, which would cause the subsequent
				 * packets in the BA stream to be discarded.
				 * mac80211 queues our packets क्रम us in this
				 * हाल, so this is really just a safety check.
				 */
				wiphy_warn(hw->wiphy,
					   "Cannot send packet while ADDBA "
					   "dialog is underway.\n");
				spin_unlock(&priv->stream_lock);
				dev_kमुक्त_skb(skb);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Defer calling mwl8k_start_stream so that the current
			 * skb can go out beक्रमe the ADDBA request.  This
			 * prevents sequence number mismatch at the recepient
			 * as described above.
			 */
			अगर (mwl8k_ampdu_allowed(sta, tid)) अणु
				stream = mwl8k_add_stream(hw, sta, tid);
				अगर (stream != शून्य)
					start_ba_session = true;
			पूर्ण
		पूर्ण
		spin_unlock(&priv->stream_lock);
	पूर्ण अन्यथा अणु
		qos &= ~MWL8K_QOS_ACK_POLICY_MASK;
		qos |= MWL8K_QOS_ACK_POLICY_NORMAL;
	पूर्ण

	dma = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
			     DMA_TO_DEVICE);

	अगर (dma_mapping_error(&priv->pdev->dev, dma)) अणु
		wiphy_debug(hw->wiphy,
			    "failed to dma map skb, dropping TX frame.\n");
		अगर (start_ba_session) अणु
			spin_lock(&priv->stream_lock);
			mwl8k_हटाओ_stream(hw, stream);
			spin_unlock(&priv->stream_lock);
		पूर्ण
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	spin_lock_bh(&priv->tx_lock);

	txq = priv->txq + index;

	/* Mgmt frames that go out frequently are probe
	 * responses. Other mgmt frames got out relatively
	 * infrequently. Hence reserve 2 buffers so that
	 * other mgmt frames करो not get dropped due to an
	 * alपढ़ोy queued probe response in one of the
	 * reserved buffers.
	 */

	अगर (txq->len >= MWL8K_TX_DESCS - 2) अणु
		अगर (!mgmtframe || txq->len == MWL8K_TX_DESCS) अणु
			अगर (start_ba_session) अणु
				spin_lock(&priv->stream_lock);
				mwl8k_हटाओ_stream(hw, stream);
				spin_unlock(&priv->stream_lock);
			पूर्ण
			mwl8k_tx_start(priv);
			spin_unlock_bh(&priv->tx_lock);
			dma_unmap_single(&priv->pdev->dev, dma, skb->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	BUG_ON(txq->skb[txq->tail] != शून्य);
	txq->skb[txq->tail] = skb;

	tx = txq->txd + txq->tail;
	tx->data_rate = txdatarate;
	tx->tx_priority = txpriority;
	tx->qos_control = cpu_to_le16(qos);
	tx->pkt_phys_addr = cpu_to_le32(dma);
	tx->pkt_len = cpu_to_le16(skb->len);
	tx->rate_info = 0;
	अगर (!priv->ap_fw && sta != शून्य)
		tx->peer_id = MWL8K_STA(sta)->peer_id;
	अन्यथा
		tx->peer_id = 0;

	अगर (priv->ap_fw && ieee80211_is_data(wh->frame_control) && !eapol_frame)
		tx->बारtamp = cpu_to_le32(ioपढ़ो32(priv->regs +
						MWL8K_HW_TIMER_REGISTER));
	अन्यथा
		tx->बारtamp = 0;

	wmb();
	tx->status = cpu_to_le32(MWL8K_TXD_STATUS_FW_OWNED | txstatus);

	txq->len++;
	priv->pending_tx_pkts++;

	txq->tail++;
	अगर (txq->tail == MWL8K_TX_DESCS)
		txq->tail = 0;

	mwl8k_tx_start(priv);

	spin_unlock_bh(&priv->tx_lock);

	/* Initiate the ampdu session here */
	अगर (start_ba_session) अणु
		spin_lock(&priv->stream_lock);
		अगर (mwl8k_start_stream(hw, stream))
			mwl8k_हटाओ_stream(hw, stream);
		spin_unlock(&priv->stream_lock);
	पूर्ण
पूर्ण


/*
 * Firmware access.
 *
 * We have the following requirements क्रम issuing firmware commands:
 * - Some commands require that the packet transmit path is idle when
 *   the command is issued.  (For simplicity, we'll just quiesce the
 *   transmit path क्रम every command.)
 * - There are certain sequences of commands that need to be issued to
 *   the hardware sequentially, with no other पूर्णांकervening commands.
 *
 * This leads to an implementation of a "firmware lock" as a mutex that
 * can be taken recursively, and which is taken by both the low-level
 * command submission function (mwl8k_post_cmd) as well as any users of
 * that function that require issuing of an atomic sequence of commands,
 * and quiesces the transmit path whenever it's taken.
 */
अटल पूर्णांक mwl8k_fw_lock(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	अगर (priv->fw_mutex_owner != current) अणु
		पूर्णांक rc;

		mutex_lock(&priv->fw_mutex);
		ieee80211_stop_queues(hw);

		rc = mwl8k_tx_रुको_empty(hw);
		अगर (rc) अणु
			अगर (!priv->hw_restart_in_progress)
				ieee80211_wake_queues(hw);

			mutex_unlock(&priv->fw_mutex);

			वापस rc;
		पूर्ण

		priv->fw_mutex_owner = current;
	पूर्ण

	priv->fw_mutex_depth++;

	वापस 0;
पूर्ण

अटल व्योम mwl8k_fw_unlock(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	अगर (!--priv->fw_mutex_depth) अणु
		अगर (!priv->hw_restart_in_progress)
			ieee80211_wake_queues(hw);

		priv->fw_mutex_owner = शून्य;
		mutex_unlock(&priv->fw_mutex);
	पूर्ण
पूर्ण

अटल व्योम mwl8k_enable_bsses(काष्ठा ieee80211_hw *hw, bool enable,
			       u32 biपंचांगap);

/*
 * Command processing.
 */

/* Timeout firmware commands after 10s */
#घोषणा MWL8K_CMD_TIMEOUT_MS	10000

अटल पूर्णांक mwl8k_post_cmd(काष्ठा ieee80211_hw *hw, काष्ठा mwl8k_cmd_pkt *cmd)
अणु
	DECLARE_COMPLETION_ONSTACK(cmd_रुको);
	काष्ठा mwl8k_priv *priv = hw->priv;
	व्योम __iomem *regs = priv->regs;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक dma_size;
	पूर्णांक rc;
	अचिन्हित दीर्घ समयout = 0;
	u8 buf[32];
	u32 biपंचांगap = 0;

	wiphy_dbg(hw->wiphy, "Posting %s [%d]\n",
		  mwl8k_cmd_name(cmd->code, buf, माप(buf)), cmd->macid);

	/* Beक्रमe posting firmware commands that could change the hardware
	 * अक्षरacteristics, make sure that all BSSes are stopped temporary.
	 * Enable these stopped BSSes after completion of the commands
	 */

	rc = mwl8k_fw_lock(hw);
	अगर (rc)
		वापस rc;

	अगर (priv->ap_fw && priv->running_bsses) अणु
		चयन (le16_to_cpu(cmd->code)) अणु
		हाल MWL8K_CMD_SET_RF_CHANNEL:
		हाल MWL8K_CMD_RADIO_CONTROL:
		हाल MWL8K_CMD_RF_TX_POWER:
		हाल MWL8K_CMD_TX_POWER:
		हाल MWL8K_CMD_RF_ANTENNA:
		हाल MWL8K_CMD_RTS_THRESHOLD:
		हाल MWL8K_CMD_MIMO_CONFIG:
			biपंचांगap = priv->running_bsses;
			mwl8k_enable_bsses(hw, false, biपंचांगap);
			अवरोध;
		पूर्ण
	पूर्ण

	cmd->result = (__क्रमce __le16) 0xffff;
	dma_size = le16_to_cpu(cmd->length);
	dma_addr = dma_map_single(&priv->pdev->dev, cmd, dma_size,
				  DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&priv->pdev->dev, dma_addr)) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	priv->hostcmd_रुको = &cmd_रुको;
	ioग_लिखो32(dma_addr, regs + MWL8K_HIU_GEN_PTR);
	ioग_लिखो32(MWL8K_H2A_INT_DOORBELL,
		regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);
	ioग_लिखो32(MWL8K_H2A_INT_DUMMY,
		regs + MWL8K_HIU_H2A_INTERRUPT_EVENTS);

	समयout = रुको_क्रम_completion_समयout(&cmd_रुको,
				msecs_to_jअगरfies(MWL8K_CMD_TIMEOUT_MS));

	priv->hostcmd_रुको = शून्य;


	dma_unmap_single(&priv->pdev->dev, dma_addr, dma_size,
			 DMA_BIसूचीECTIONAL);

	अगर (!समयout) अणु
		wiphy_err(hw->wiphy, "Command %s timeout after %u ms\n",
			  mwl8k_cmd_name(cmd->code, buf, माप(buf)),
			  MWL8K_CMD_TIMEOUT_MS);
		rc = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		पूर्णांक ms;

		ms = MWL8K_CMD_TIMEOUT_MS - jअगरfies_to_msecs(समयout);

		rc = cmd->result ? -EINVAL : 0;
		अगर (rc)
			wiphy_err(hw->wiphy, "Command %s error 0x%x\n",
				  mwl8k_cmd_name(cmd->code, buf, माप(buf)),
				  le16_to_cpu(cmd->result));
		अन्यथा अगर (ms > 2000)
			wiphy_notice(hw->wiphy, "Command %s took %d ms\n",
				     mwl8k_cmd_name(cmd->code,
						    buf, माप(buf)),
				     ms);
	पूर्ण

निकास:
	अगर (biपंचांगap)
		mwl8k_enable_bsses(hw, true, biपंचांगap);

	mwl8k_fw_unlock(hw);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_post_pervअगर_cmd(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा mwl8k_cmd_pkt *cmd)
अणु
	अगर (vअगर != शून्य)
		cmd->macid = MWL8K_VIF(vअगर)->macid;
	वापस mwl8k_post_cmd(hw, cmd);
पूर्ण

/*
 * Setup code shared between STA and AP firmware images.
 */
अटल व्योम mwl8k_setup_2ghz_band(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	BUILD_BUG_ON(माप(priv->channels_24) != माप(mwl8k_channels_24));
	स_नकल(priv->channels_24, mwl8k_channels_24, माप(mwl8k_channels_24));

	BUILD_BUG_ON(माप(priv->rates_24) != माप(mwl8k_rates_24));
	स_नकल(priv->rates_24, mwl8k_rates_24, माप(mwl8k_rates_24));

	priv->band_24.band = NL80211_BAND_2GHZ;
	priv->band_24.channels = priv->channels_24;
	priv->band_24.n_channels = ARRAY_SIZE(mwl8k_channels_24);
	priv->band_24.bitrates = priv->rates_24;
	priv->band_24.n_bitrates = ARRAY_SIZE(mwl8k_rates_24);

	hw->wiphy->bands[NL80211_BAND_2GHZ] = &priv->band_24;
पूर्ण

अटल व्योम mwl8k_setup_5ghz_band(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	BUILD_BUG_ON(माप(priv->channels_50) != माप(mwl8k_channels_50));
	स_नकल(priv->channels_50, mwl8k_channels_50, माप(mwl8k_channels_50));

	BUILD_BUG_ON(माप(priv->rates_50) != माप(mwl8k_rates_50));
	स_नकल(priv->rates_50, mwl8k_rates_50, माप(mwl8k_rates_50));

	priv->band_50.band = NL80211_BAND_5GHZ;
	priv->band_50.channels = priv->channels_50;
	priv->band_50.n_channels = ARRAY_SIZE(mwl8k_channels_50);
	priv->band_50.bitrates = priv->rates_50;
	priv->band_50.n_bitrates = ARRAY_SIZE(mwl8k_rates_50);

	hw->wiphy->bands[NL80211_BAND_5GHZ] = &priv->band_50;
पूर्ण

/*
 * CMD_GET_HW_SPEC (STA version).
 */
काष्ठा mwl8k_cmd_get_hw_spec_sta अणु
	काष्ठा mwl8k_cmd_pkt header;
	__u8 hw_rev;
	__u8 host_पूर्णांकerface;
	__le16 num_mcaddrs;
	__u8 perm_addr[ETH_ALEN];
	__le16 region_code;
	__le32 fw_rev;
	__le32 ps_cookie;
	__le32 caps;
	__u8 mcs_biपंचांगap[16];
	__le32 rx_queue_ptr;
	__le32 num_tx_queues;
	__le32 tx_queue_ptrs[MWL8K_TX_WMM_QUEUES];
	__le32 caps2;
	__le32 num_tx_desc_per_queue;
	__le32 total_rxd;
पूर्ण __packed;

#घोषणा MWL8K_CAP_MAX_AMSDU		0x20000000
#घोषणा MWL8K_CAP_GREENFIELD		0x08000000
#घोषणा MWL8K_CAP_AMPDU			0x04000000
#घोषणा MWL8K_CAP_RX_STBC		0x01000000
#घोषणा MWL8K_CAP_TX_STBC		0x00800000
#घोषणा MWL8K_CAP_SHORTGI_40MHZ		0x00400000
#घोषणा MWL8K_CAP_SHORTGI_20MHZ		0x00200000
#घोषणा MWL8K_CAP_RX_ANTENNA_MASK	0x000e0000
#घोषणा MWL8K_CAP_TX_ANTENNA_MASK	0x0001c000
#घोषणा MWL8K_CAP_DELAY_BA		0x00003000
#घोषणा MWL8K_CAP_MIMO			0x00000200
#घोषणा MWL8K_CAP_40MHZ			0x00000100
#घोषणा MWL8K_CAP_BAND_MASK		0x00000007
#घोषणा MWL8K_CAP_5GHZ			0x00000004
#घोषणा MWL8K_CAP_2GHZ4			0x00000001

अटल व्योम
mwl8k_set_ht_caps(काष्ठा ieee80211_hw *hw,
		  काष्ठा ieee80211_supported_band *band, u32 cap)
अणु
	पूर्णांक rx_streams;
	पूर्णांक tx_streams;

	band->ht_cap.ht_supported = 1;

	अगर (cap & MWL8K_CAP_MAX_AMSDU)
		band->ht_cap.cap |= IEEE80211_HT_CAP_MAX_AMSDU;
	अगर (cap & MWL8K_CAP_GREENFIELD)
		band->ht_cap.cap |= IEEE80211_HT_CAP_GRN_FLD;
	अगर (cap & MWL8K_CAP_AMPDU) अणु
		ieee80211_hw_set(hw, AMPDU_AGGREGATION);
		band->ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
		band->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;
	पूर्ण
	अगर (cap & MWL8K_CAP_RX_STBC)
		band->ht_cap.cap |= IEEE80211_HT_CAP_RX_STBC;
	अगर (cap & MWL8K_CAP_TX_STBC)
		band->ht_cap.cap |= IEEE80211_HT_CAP_TX_STBC;
	अगर (cap & MWL8K_CAP_SHORTGI_40MHZ)
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
	अगर (cap & MWL8K_CAP_SHORTGI_20MHZ)
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;
	अगर (cap & MWL8K_CAP_DELAY_BA)
		band->ht_cap.cap |= IEEE80211_HT_CAP_DELAY_BA;
	अगर (cap & MWL8K_CAP_40MHZ)
		band->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	rx_streams = hweight32(cap & MWL8K_CAP_RX_ANTENNA_MASK);
	tx_streams = hweight32(cap & MWL8K_CAP_TX_ANTENNA_MASK);

	band->ht_cap.mcs.rx_mask[0] = 0xff;
	अगर (rx_streams >= 2)
		band->ht_cap.mcs.rx_mask[1] = 0xff;
	अगर (rx_streams >= 3)
		band->ht_cap.mcs.rx_mask[2] = 0xff;
	band->ht_cap.mcs.rx_mask[4] = 0x01;
	band->ht_cap.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;

	अगर (rx_streams != tx_streams) अणु
		band->ht_cap.mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		band->ht_cap.mcs.tx_params |= (tx_streams - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;
	पूर्ण
पूर्ण

अटल व्योम
mwl8k_set_caps(काष्ठा ieee80211_hw *hw, u32 caps)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	अगर (priv->caps)
		वापस;

	अगर ((caps & MWL8K_CAP_2GHZ4) || !(caps & MWL8K_CAP_BAND_MASK)) अणु
		mwl8k_setup_2ghz_band(hw);
		अगर (caps & MWL8K_CAP_MIMO)
			mwl8k_set_ht_caps(hw, &priv->band_24, caps);
	पूर्ण

	अगर (caps & MWL8K_CAP_5GHZ) अणु
		mwl8k_setup_5ghz_band(hw);
		अगर (caps & MWL8K_CAP_MIMO)
			mwl8k_set_ht_caps(hw, &priv->band_50, caps);
	पूर्ण

	priv->caps = caps;
पूर्ण

अटल पूर्णांक mwl8k_cmd_get_hw_spec_sta(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_get_hw_spec_sta *cmd;
	पूर्णांक rc;
	पूर्णांक i;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_HW_SPEC);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	स_रखो(cmd->perm_addr, 0xff, माप(cmd->perm_addr));
	cmd->ps_cookie = cpu_to_le32(priv->cookie_dma);
	cmd->rx_queue_ptr = cpu_to_le32(priv->rxq[0].rxd_dma);
	cmd->num_tx_queues = cpu_to_le32(mwl8k_tx_queues(priv));
	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		cmd->tx_queue_ptrs[i] = cpu_to_le32(priv->txq[i].txd_dma);
	cmd->num_tx_desc_per_queue = cpu_to_le32(MWL8K_TX_DESCS);
	cmd->total_rxd = cpu_to_le32(MWL8K_RX_DESCS);

	rc = mwl8k_post_cmd(hw, &cmd->header);

	अगर (!rc) अणु
		SET_IEEE80211_PERM_ADDR(hw, cmd->perm_addr);
		priv->num_mcaddrs = le16_to_cpu(cmd->num_mcaddrs);
		priv->fw_rev = le32_to_cpu(cmd->fw_rev);
		priv->hw_rev = cmd->hw_rev;
		mwl8k_set_caps(hw, le32_to_cpu(cmd->caps));
		priv->ap_macids_supported = 0x00000000;
		priv->sta_macids_supported = 0x00000001;
	पूर्ण

	kमुक्त(cmd);
	वापस rc;
पूर्ण

/*
 * CMD_GET_HW_SPEC (AP version).
 */
काष्ठा mwl8k_cmd_get_hw_spec_ap अणु
	काष्ठा mwl8k_cmd_pkt header;
	__u8 hw_rev;
	__u8 host_पूर्णांकerface;
	__le16 num_wcb;
	__le16 num_mcaddrs;
	__u8 perm_addr[ETH_ALEN];
	__le16 region_code;
	__le16 num_antenna;
	__le32 fw_rev;
	__le32 wcbbase0;
	__le32 rxwrptr;
	__le32 rxrdptr;
	__le32 ps_cookie;
	__le32 wcbbase1;
	__le32 wcbbase2;
	__le32 wcbbase3;
	__le32 fw_api_version;
	__le32 caps;
	__le32 num_of_ampdu_queues;
	__le32 wcbbase_ampdu[MWL8K_MAX_AMPDU_QUEUES];
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_get_hw_spec_ap(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_get_hw_spec_ap *cmd;
	पूर्णांक rc, i;
	u32 api_version;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_HW_SPEC);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	स_रखो(cmd->perm_addr, 0xff, माप(cmd->perm_addr));
	cmd->ps_cookie = cpu_to_le32(priv->cookie_dma);

	rc = mwl8k_post_cmd(hw, &cmd->header);

	अगर (!rc) अणु
		पूर्णांक off;

		api_version = le32_to_cpu(cmd->fw_api_version);
		अगर (priv->device_info->fw_api_ap != api_version) अणु
			prपूर्णांकk(KERN_ERR "%s: Unsupported fw API version for %s."
			       "  Expected %d got %d.\n", MWL8K_NAME,
			       priv->device_info->part_name,
			       priv->device_info->fw_api_ap,
			       api_version);
			rc = -EINVAL;
			जाओ करोne;
		पूर्ण
		SET_IEEE80211_PERM_ADDR(hw, cmd->perm_addr);
		priv->num_mcaddrs = le16_to_cpu(cmd->num_mcaddrs);
		priv->fw_rev = le32_to_cpu(cmd->fw_rev);
		priv->hw_rev = cmd->hw_rev;
		mwl8k_set_caps(hw, le32_to_cpu(cmd->caps));
		priv->ap_macids_supported = 0x000000ff;
		priv->sta_macids_supported = 0x00000100;
		priv->num_ampdu_queues = le32_to_cpu(cmd->num_of_ampdu_queues);
		अगर (priv->num_ampdu_queues > MWL8K_MAX_AMPDU_QUEUES) अणु
			wiphy_warn(hw->wiphy, "fw reported %d ampdu queues"
				   " but we only support %d.\n",
				   priv->num_ampdu_queues,
				   MWL8K_MAX_AMPDU_QUEUES);
			priv->num_ampdu_queues = MWL8K_MAX_AMPDU_QUEUES;
		पूर्ण
		off = le32_to_cpu(cmd->rxwrptr) & 0xffff;
		ioग_लिखो32(priv->rxq[0].rxd_dma, priv->sram + off);

		off = le32_to_cpu(cmd->rxrdptr) & 0xffff;
		ioग_लिखो32(priv->rxq[0].rxd_dma, priv->sram + off);

		priv->txq_offset[0] = le32_to_cpu(cmd->wcbbase0) & 0xffff;
		priv->txq_offset[1] = le32_to_cpu(cmd->wcbbase1) & 0xffff;
		priv->txq_offset[2] = le32_to_cpu(cmd->wcbbase2) & 0xffff;
		priv->txq_offset[3] = le32_to_cpu(cmd->wcbbase3) & 0xffff;

		क्रम (i = 0; i < priv->num_ampdu_queues; i++)
			priv->txq_offset[i + MWL8K_TX_WMM_QUEUES] =
				le32_to_cpu(cmd->wcbbase_ampdu[i]) & 0xffff;
	पूर्ण

करोne:
	kमुक्त(cmd);
	वापस rc;
पूर्ण

/*
 * CMD_SET_HW_SPEC.
 */
काष्ठा mwl8k_cmd_set_hw_spec अणु
	काष्ठा mwl8k_cmd_pkt header;
	__u8 hw_rev;
	__u8 host_पूर्णांकerface;
	__le16 num_mcaddrs;
	__u8 perm_addr[ETH_ALEN];
	__le16 region_code;
	__le32 fw_rev;
	__le32 ps_cookie;
	__le32 caps;
	__le32 rx_queue_ptr;
	__le32 num_tx_queues;
	__le32 tx_queue_ptrs[MWL8K_MAX_TX_QUEUES];
	__le32 flags;
	__le32 num_tx_desc_per_queue;
	__le32 total_rxd;
पूर्ण __packed;

/* If enabled, MWL8K_SET_HW_SPEC_FLAG_ENABLE_LIFE_TIME_EXPIRY will cause
 * packets to expire 500 ms after the बारtamp in the tx descriptor.  That is,
 * the packets that are queued क्रम more than 500ms, will be dropped in the
 * hardware. This helps minimizing the issues caused due to head-of-line
 * blocking where a slow client can hog the bandwidth and affect traffic to a
 * faster client.
 */
#घोषणा MWL8K_SET_HW_SPEC_FLAG_ENABLE_LIFE_TIME_EXPIRY	0x00000400
#घोषणा MWL8K_SET_HW_SPEC_FLAG_GENERATE_CCMP_HDR	0x00000200
#घोषणा MWL8K_SET_HW_SPEC_FLAG_HOST_DECR_MGMT		0x00000080
#घोषणा MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_PROBERESP	0x00000020
#घोषणा MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_BEACON		0x00000010

अटल पूर्णांक mwl8k_cmd_set_hw_spec(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_set_hw_spec *cmd;
	पूर्णांक rc;
	पूर्णांक i;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_HW_SPEC);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	cmd->ps_cookie = cpu_to_le32(priv->cookie_dma);
	cmd->rx_queue_ptr = cpu_to_le32(priv->rxq[0].rxd_dma);
	cmd->num_tx_queues = cpu_to_le32(mwl8k_tx_queues(priv));

	/*
	 * Mac80211 stack has Q0 as highest priority and Q3 as lowest in
	 * that order. Firmware has Q3 as highest priority and Q0 as lowest
	 * in that order. Map Q3 of mac80211 to Q0 of firmware so that the
	 * priority is पूर्णांकerpreted the right way in firmware.
	 */
	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++) अणु
		पूर्णांक j = mwl8k_tx_queues(priv) - 1 - i;
		cmd->tx_queue_ptrs[i] = cpu_to_le32(priv->txq[j].txd_dma);
	पूर्ण

	cmd->flags = cpu_to_le32(MWL8K_SET_HW_SPEC_FLAG_HOST_DECR_MGMT |
				 MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_PROBERESP |
				 MWL8K_SET_HW_SPEC_FLAG_HOSTFORM_BEACON |
				 MWL8K_SET_HW_SPEC_FLAG_ENABLE_LIFE_TIME_EXPIRY |
				 MWL8K_SET_HW_SPEC_FLAG_GENERATE_CCMP_HDR);
	cmd->num_tx_desc_per_queue = cpu_to_le32(MWL8K_TX_DESCS);
	cmd->total_rxd = cpu_to_le32(MWL8K_RX_DESCS);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_MAC_MULTICAST_ADR.
 */
काष्ठा mwl8k_cmd_mac_multicast_adr अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 numaddr;
	__u8 addr[][ETH_ALEN];
पूर्ण;

#घोषणा MWL8K_ENABLE_RX_सूचीECTED	0x0001
#घोषणा MWL8K_ENABLE_RX_MULTICAST	0x0002
#घोषणा MWL8K_ENABLE_RX_ALL_MULTICAST	0x0004
#घोषणा MWL8K_ENABLE_RX_BROADCAST	0x0008

अटल काष्ठा mwl8k_cmd_pkt *
__mwl8k_cmd_mac_multicast_adr(काष्ठा ieee80211_hw *hw, पूर्णांक allmulti,
			      काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_mac_multicast_adr *cmd;
	पूर्णांक size;
	पूर्णांक mc_count = 0;

	अगर (mc_list)
		mc_count = netdev_hw_addr_list_count(mc_list);

	अगर (allmulti || mc_count > priv->num_mcaddrs) अणु
		allmulti = 1;
		mc_count = 0;
	पूर्ण

	size = माप(*cmd) + mc_count * ETH_ALEN;

	cmd = kzalloc(size, GFP_ATOMIC);
	अगर (cmd == शून्य)
		वापस शून्य;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_MAC_MULTICAST_ADR);
	cmd->header.length = cpu_to_le16(size);
	cmd->action = cpu_to_le16(MWL8K_ENABLE_RX_सूचीECTED |
				  MWL8K_ENABLE_RX_BROADCAST);

	अगर (allmulti) अणु
		cmd->action |= cpu_to_le16(MWL8K_ENABLE_RX_ALL_MULTICAST);
	पूर्ण अन्यथा अगर (mc_count) अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i = 0;

		cmd->action |= cpu_to_le16(MWL8K_ENABLE_RX_MULTICAST);
		cmd->numaddr = cpu_to_le16(mc_count);
		netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
			स_नकल(cmd->addr[i], ha->addr, ETH_ALEN);
		पूर्ण
	पूर्ण

	वापस &cmd->header;
पूर्ण

/*
 * CMD_GET_STAT.
 */
काष्ठा mwl8k_cmd_get_stat अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 stats[64];
पूर्ण __packed;

#घोषणा MWL8K_STAT_ACK_FAILURE	9
#घोषणा MWL8K_STAT_RTS_FAILURE	12
#घोषणा MWL8K_STAT_FCS_ERROR	24
#घोषणा MWL8K_STAT_RTS_SUCCESS	11

अटल पूर्णांक mwl8k_cmd_get_stat(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा mwl8k_cmd_get_stat *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_STAT);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	rc = mwl8k_post_cmd(hw, &cmd->header);
	अगर (!rc) अणु
		stats->करोt11ACKFailureCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_ACK_FAILURE]);
		stats->करोt11RTSFailureCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_RTS_FAILURE]);
		stats->करोt11FCSErrorCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_FCS_ERROR]);
		stats->करोt11RTSSuccessCount =
			le32_to_cpu(cmd->stats[MWL8K_STAT_RTS_SUCCESS]);
	पूर्ण
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_RADIO_CONTROL.
 */
काष्ठा mwl8k_cmd_radio_control अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 control;
	__le16 radio_on;
पूर्ण __packed;

अटल पूर्णांक
mwl8k_cmd_radio_control(काष्ठा ieee80211_hw *hw, bool enable, bool क्रमce)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_radio_control *cmd;
	पूर्णांक rc;

	अगर (enable == priv->radio_on && !क्रमce)
		वापस 0;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_RADIO_CONTROL);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->control = cpu_to_le16(priv->radio_लघु_preamble ? 3 : 1);
	cmd->radio_on = cpu_to_le16(enable ? 0x0001 : 0x0000);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	अगर (!rc)
		priv->radio_on = enable;

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_cmd_radio_disable(काष्ठा ieee80211_hw *hw)
अणु
	वापस mwl8k_cmd_radio_control(hw, 0, 0);
पूर्ण

अटल पूर्णांक mwl8k_cmd_radio_enable(काष्ठा ieee80211_hw *hw)
अणु
	वापस mwl8k_cmd_radio_control(hw, 1, 0);
पूर्ण

अटल पूर्णांक
mwl8k_set_radio_preamble(काष्ठा ieee80211_hw *hw, bool लघु_preamble)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	priv->radio_लघु_preamble = लघु_preamble;

	वापस mwl8k_cmd_radio_control(hw, 1, 1);
पूर्ण

/*
 * CMD_RF_TX_POWER.
 */
#घोषणा MWL8K_RF_TX_POWER_LEVEL_TOTAL	8

काष्ठा mwl8k_cmd_rf_tx_घातer अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 support_level;
	__le16 current_level;
	__le16 reserved;
	__le16 घातer_level_list[MWL8K_RF_TX_POWER_LEVEL_TOTAL];
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_rf_tx_घातer(काष्ठा ieee80211_hw *hw, पूर्णांक dBm)
अणु
	काष्ठा mwl8k_cmd_rf_tx_घातer *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_RF_TX_POWER);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->support_level = cpu_to_le16(dBm);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_TX_POWER.
 */
#घोषणा MWL8K_TX_POWER_LEVEL_TOTAL      12

काष्ठा mwl8k_cmd_tx_घातer अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 band;
	__le16 channel;
	__le16 bw;
	__le16 sub_ch;
	__le16 घातer_level_list[MWL8K_TX_POWER_LEVEL_TOTAL];
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_tx_घातer(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_conf *conf,
				     अचिन्हित लघु pwr)
अणु
	काष्ठा ieee80211_channel *channel = conf->chandef.chan;
	क्रमागत nl80211_channel_type channel_type =
		cfg80211_get_chandef_type(&conf->chandef);
	काष्ठा mwl8k_cmd_tx_घातer *cmd;
	पूर्णांक rc;
	पूर्णांक i;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_TX_POWER);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET_LIST);

	अगर (channel->band == NL80211_BAND_2GHZ)
		cmd->band = cpu_to_le16(0x1);
	अन्यथा अगर (channel->band == NL80211_BAND_5GHZ)
		cmd->band = cpu_to_le16(0x4);

	cmd->channel = cpu_to_le16(channel->hw_value);

	अगर (channel_type == NL80211_CHAN_NO_HT ||
	    channel_type == NL80211_CHAN_HT20) अणु
		cmd->bw = cpu_to_le16(0x2);
	पूर्ण अन्यथा अणु
		cmd->bw = cpu_to_le16(0x4);
		अगर (channel_type == NL80211_CHAN_HT40MINUS)
			cmd->sub_ch = cpu_to_le16(0x3);
		अन्यथा अगर (channel_type == NL80211_CHAN_HT40PLUS)
			cmd->sub_ch = cpu_to_le16(0x1);
	पूर्ण

	क्रम (i = 0; i < MWL8K_TX_POWER_LEVEL_TOTAL; i++)
		cmd->घातer_level_list[i] = cpu_to_le16(pwr);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_RF_ANTENNA.
 */
काष्ठा mwl8k_cmd_rf_antenna अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 antenna;
	__le16 mode;
पूर्ण __packed;

#घोषणा MWL8K_RF_ANTENNA_RX		1
#घोषणा MWL8K_RF_ANTENNA_TX		2

अटल पूर्णांक
mwl8k_cmd_rf_antenna(काष्ठा ieee80211_hw *hw, पूर्णांक antenna, पूर्णांक mask)
अणु
	काष्ठा mwl8k_cmd_rf_antenna *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_RF_ANTENNA);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->antenna = cpu_to_le16(antenna);
	cmd->mode = cpu_to_le16(mask);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_BEACON.
 */
काष्ठा mwl8k_cmd_set_beacon अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 beacon_len;
	__u8 beacon[];
पूर्ण;

अटल पूर्णांक mwl8k_cmd_set_beacon(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर, u8 *beacon, पूर्णांक len)
अणु
	काष्ठा mwl8k_cmd_set_beacon *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd) + len, GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_BEACON);
	cmd->header.length = cpu_to_le16(माप(*cmd) + len);
	cmd->beacon_len = cpu_to_le16(len);
	स_नकल(cmd->beacon, beacon, len);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_PRE_SCAN.
 */
काष्ठा mwl8k_cmd_set_pre_scan अणु
	काष्ठा mwl8k_cmd_pkt header;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_set_pre_scan(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_cmd_set_pre_scan *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_PRE_SCAN);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_BBP_REG_ACCESS.
 */
काष्ठा mwl8k_cmd_bbp_reg_access अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 offset;
	u8 value;
	u8 rsrv[3];
पूर्ण __packed;

अटल पूर्णांक
mwl8k_cmd_bbp_reg_access(काष्ठा ieee80211_hw *hw,
			 u16 action,
			 u16 offset,
			 u8 *value)
अणु
	काष्ठा mwl8k_cmd_bbp_reg_access *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BBP_REG_ACCESS);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(action);
	cmd->offset = cpu_to_le16(offset);

	rc = mwl8k_post_cmd(hw, &cmd->header);

	अगर (!rc)
		*value = cmd->value;
	अन्यथा
		*value = 0;

	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_POST_SCAN.
 */
काष्ठा mwl8k_cmd_set_post_scan अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 isibss;
	__u8 bssid[ETH_ALEN];
पूर्ण __packed;

अटल पूर्णांक
mwl8k_cmd_set_post_scan(काष्ठा ieee80211_hw *hw, स्थिर __u8 *mac)
अणु
	काष्ठा mwl8k_cmd_set_post_scan *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_POST_SCAN);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->isibss = 0;
	स_नकल(cmd->bssid, mac, ETH_ALEN);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक freq_to_idx(काष्ठा mwl8k_priv *priv, पूर्णांक freq)
अणु
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक band, ch, idx = 0;

	क्रम (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; band++) अणु
		sband = priv->hw->wiphy->bands[band];
		अगर (!sband)
			जारी;

		क्रम (ch = 0; ch < sband->n_channels; ch++, idx++)
			अगर (sband->channels[ch].center_freq == freq)
				जाओ निकास;
	पूर्ण

निकास:
	वापस idx;
पूर्ण

अटल व्योम mwl8k_update_survey(काष्ठा mwl8k_priv *priv,
				काष्ठा ieee80211_channel *channel)
अणु
	u32 cca_cnt, rx_rdy;
	s8 nf = 0, idx;
	काष्ठा survey_info *survey;

	idx = freq_to_idx(priv, priv->acs_chan->center_freq);
	अगर (idx >= MWL8K_NUM_CHANS) अणु
		wiphy_err(priv->hw->wiphy, "Failed to update survey\n");
		वापस;
	पूर्ण

	survey = &priv->survey[idx];

	cca_cnt = ioपढ़ो32(priv->regs + NOK_CCA_CNT_REG);
	cca_cnt /= 1000; /* uSecs to mSecs */
	survey->समय_busy = (u64) cca_cnt;

	rx_rdy = ioपढ़ो32(priv->regs + BBU_RXRDY_CNT_REG);
	rx_rdy /= 1000; /* uSecs to mSecs */
	survey->समय_rx = (u64) rx_rdy;

	priv->channel_समय = jअगरfies - priv->channel_समय;
	survey->समय = jअगरfies_to_msecs(priv->channel_समय);

	survey->channel = channel;

	mwl8k_cmd_bbp_reg_access(priv->hw, 0, BBU_AVG_NOISE_VAL, &nf);

	/* Make sure sign is negative अन्यथा ACS  at hostapd fails */
	survey->noise = nf * -1;

	survey->filled = SURVEY_INFO_NOISE_DBM |
			 SURVEY_INFO_TIME |
			 SURVEY_INFO_TIME_BUSY |
			 SURVEY_INFO_TIME_RX;
पूर्ण

/*
 * CMD_SET_RF_CHANNEL.
 */
काष्ठा mwl8k_cmd_set_rf_channel अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__u8 current_channel;
	__le32 channel_flags;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_set_rf_channel(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_conf *conf)
अणु
	काष्ठा ieee80211_channel *channel = conf->chandef.chan;
	क्रमागत nl80211_channel_type channel_type =
		cfg80211_get_chandef_type(&conf->chandef);
	काष्ठा mwl8k_cmd_set_rf_channel *cmd;
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_RF_CHANNEL);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->current_channel = channel->hw_value;

	अगर (channel->band == NL80211_BAND_2GHZ)
		cmd->channel_flags |= cpu_to_le32(0x00000001);
	अन्यथा अगर (channel->band == NL80211_BAND_5GHZ)
		cmd->channel_flags |= cpu_to_le32(0x00000004);

	अगर (!priv->sw_scan_start) अणु
		अगर (channel_type == NL80211_CHAN_NO_HT ||
		    channel_type == NL80211_CHAN_HT20)
			cmd->channel_flags |= cpu_to_le32(0x00000080);
		अन्यथा अगर (channel_type == NL80211_CHAN_HT40MINUS)
			cmd->channel_flags |= cpu_to_le32(0x000001900);
		अन्यथा अगर (channel_type == NL80211_CHAN_HT40PLUS)
			cmd->channel_flags |= cpu_to_le32(0x000000900);
	पूर्ण अन्यथा अणु
		cmd->channel_flags |= cpu_to_le32(0x00000080);
	पूर्ण

	अगर (priv->sw_scan_start) अणु
		/* Store current channel stats
		 * beक्रमe चयनing to newer one.
		 * This will be processed only क्रम AP fw.
		 */
		अगर (priv->channel_समय != 0)
			mwl8k_update_survey(priv, priv->acs_chan);

		priv->channel_समय = jअगरfies;
		priv->acs_chan =  channel;
	पूर्ण

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_AID.
 */
#घोषणा MWL8K_FRAME_PROT_DISABLED			0x00
#घोषणा MWL8K_FRAME_PROT_11G				0x07
#घोषणा MWL8K_FRAME_PROT_11N_HT_40MHZ_ONLY		0x02
#घोषणा MWL8K_FRAME_PROT_11N_HT_ALL			0x06

काष्ठा mwl8k_cmd_update_set_aid अणु
	काष्ठा	mwl8k_cmd_pkt header;
	__le16	aid;

	 /* AP's MAC address (BSSID) */
	__u8	bssid[ETH_ALEN];
	__le16	protection_mode;
	__u8	supp_rates[14];
पूर्ण __packed;

अटल व्योम legacy_rate_mask_to_array(u8 *rates, u32 mask)
अणु
	पूर्णांक i;
	पूर्णांक j;

	/*
	 * Clear nonstandard rate 4.
	 */
	mask &= 0x1fef;

	क्रम (i = 0, j = 0; i < 13; i++) अणु
		अगर (mask & (1 << i))
			rates[j++] = mwl8k_rates_24[i].hw_value;
	पूर्ण
पूर्ण

अटल पूर्णांक
mwl8k_cmd_set_aid(काष्ठा ieee80211_hw *hw,
		  काष्ठा ieee80211_vअगर *vअगर, u32 legacy_rate_mask)
अणु
	काष्ठा mwl8k_cmd_update_set_aid *cmd;
	u16 prot_mode;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_AID);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->aid = cpu_to_le16(vअगर->bss_conf.aid);
	स_नकल(cmd->bssid, vअगर->bss_conf.bssid, ETH_ALEN);

	अगर (vअगर->bss_conf.use_cts_prot) अणु
		prot_mode = MWL8K_FRAME_PROT_11G;
	पूर्ण अन्यथा अणु
		चयन (vअगर->bss_conf.ht_operation_mode &
			IEEE80211_HT_OP_MODE_PROTECTION) अणु
		हाल IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
			prot_mode = MWL8K_FRAME_PROT_11N_HT_40MHZ_ONLY;
			अवरोध;
		हाल IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
			prot_mode = MWL8K_FRAME_PROT_11N_HT_ALL;
			अवरोध;
		शेष:
			prot_mode = MWL8K_FRAME_PROT_DISABLED;
			अवरोध;
		पूर्ण
	पूर्ण
	cmd->protection_mode = cpu_to_le16(prot_mode);

	legacy_rate_mask_to_array(cmd->supp_rates, legacy_rate_mask);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_RATE.
 */
काष्ठा mwl8k_cmd_set_rate अणु
	काष्ठा	mwl8k_cmd_pkt header;
	__u8	legacy_rates[14];

	/* Biपंचांगap क्रम supported MCS codes.  */
	__u8	mcs_set[16];
	__u8	reserved[16];
पूर्ण __packed;

अटल पूर्णांक
mwl8k_cmd_set_rate(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   u32 legacy_rate_mask, u8 *mcs_rates)
अणु
	काष्ठा mwl8k_cmd_set_rate *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_RATE);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	legacy_rate_mask_to_array(cmd->legacy_rates, legacy_rate_mask);
	स_नकल(cmd->mcs_set, mcs_rates, 16);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_FINALIZE_JOIN.
 */
#घोषणा MWL8K_FJ_BEACON_MAXLEN	128

काष्ठा mwl8k_cmd_finalize_join अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 sleep_पूर्णांकerval;	/* Number of beacon periods to sleep */
	__u8 beacon_data[MWL8K_FJ_BEACON_MAXLEN];
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_finalize_join(काष्ठा ieee80211_hw *hw, व्योम *frame,
				   पूर्णांक framelen, पूर्णांक dtim)
अणु
	काष्ठा mwl8k_cmd_finalize_join *cmd;
	काष्ठा ieee80211_mgmt *payload = frame;
	पूर्णांक payload_len;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_FINALIZE_JOIN);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->sleep_पूर्णांकerval = cpu_to_le32(dtim ? dtim : 1);

	payload_len = framelen - ieee80211_hdrlen(payload->frame_control);
	अगर (payload_len < 0)
		payload_len = 0;
	अन्यथा अगर (payload_len > MWL8K_FJ_BEACON_MAXLEN)
		payload_len = MWL8K_FJ_BEACON_MAXLEN;

	स_नकल(cmd->beacon_data, &payload->u.beacon, payload_len);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_RTS_THRESHOLD.
 */
काष्ठा mwl8k_cmd_set_rts_threshold अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 threshold;
पूर्ण __packed;

अटल पूर्णांक
mwl8k_cmd_set_rts_threshold(काष्ठा ieee80211_hw *hw, पूर्णांक rts_thresh)
अणु
	काष्ठा mwl8k_cmd_set_rts_threshold *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_RTS_THRESHOLD);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->threshold = cpu_to_le16(rts_thresh);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_SLOT.
 */
काष्ठा mwl8k_cmd_set_slot अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__u8 लघु_slot;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_set_slot(काष्ठा ieee80211_hw *hw, bool लघु_slot_समय)
अणु
	काष्ठा mwl8k_cmd_set_slot *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_SLOT);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->लघु_slot = लघु_slot_समय;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_EDCA_PARAMS.
 */
काष्ठा mwl8k_cmd_set_edca_params अणु
	काष्ठा mwl8k_cmd_pkt header;

	/* See MWL8K_SET_EDCA_XXX below */
	__le16 action;

	/* TX opportunity in units of 32 us */
	__le16 txop;

	जोड़ अणु
		काष्ठा अणु
			/* Log exponent of max contention period: 0...15 */
			__le32 log_cw_max;

			/* Log exponent of min contention period: 0...15 */
			__le32 log_cw_min;

			/* Adaptive पूर्णांकerframe spacing in units of 32us */
			__u8 aअगरs;

			/* TX queue to configure */
			__u8 txq;
		पूर्ण ap;
		काष्ठा अणु
			/* Log exponent of max contention period: 0...15 */
			__u8 log_cw_max;

			/* Log exponent of min contention period: 0...15 */
			__u8 log_cw_min;

			/* Adaptive पूर्णांकerframe spacing in units of 32us */
			__u8 aअगरs;

			/* TX queue to configure */
			__u8 txq;
		पूर्ण sta;
	पूर्ण;
पूर्ण __packed;

#घोषणा MWL8K_SET_EDCA_CW	0x01
#घोषणा MWL8K_SET_EDCA_TXOP	0x02
#घोषणा MWL8K_SET_EDCA_AIFS	0x04

#घोषणा MWL8K_SET_EDCA_ALL	(MWL8K_SET_EDCA_CW | \
				 MWL8K_SET_EDCA_TXOP | \
				 MWL8K_SET_EDCA_AIFS)

अटल पूर्णांक
mwl8k_cmd_set_edca_params(काष्ठा ieee80211_hw *hw, __u8 qnum,
			  __u16 cw_min, __u16 cw_max,
			  __u8 aअगरs, __u16 txop)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_set_edca_params *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_EDCA_PARAMS);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_SET_EDCA_ALL);
	cmd->txop = cpu_to_le16(txop);
	अगर (priv->ap_fw) अणु
		cmd->ap.log_cw_max = cpu_to_le32(ilog2(cw_max + 1));
		cmd->ap.log_cw_min = cpu_to_le32(ilog2(cw_min + 1));
		cmd->ap.aअगरs = aअगरs;
		cmd->ap.txq = qnum;
	पूर्ण अन्यथा अणु
		cmd->sta.log_cw_max = (u8)ilog2(cw_max + 1);
		cmd->sta.log_cw_min = (u8)ilog2(cw_min + 1);
		cmd->sta.aअगरs = aअगरs;
		cmd->sta.txq = qnum;
	पूर्ण

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_SET_WMM_MODE.
 */
काष्ठा mwl8k_cmd_set_wmm_mode अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_set_wmm_mode(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_set_wmm_mode *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_WMM_MODE);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(!!enable);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	अगर (!rc)
		priv->wmm_enabled = enable;

	वापस rc;
पूर्ण

/*
 * CMD_MIMO_CONFIG.
 */
काष्ठा mwl8k_cmd_mimo_config अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 action;
	__u8 rx_antenna_map;
	__u8 tx_antenna_map;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_mimo_config(काष्ठा ieee80211_hw *hw, __u8 rx, __u8 tx)
अणु
	काष्ठा mwl8k_cmd_mimo_config *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_MIMO_CONFIG);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32((u32)MWL8K_CMD_SET);
	cmd->rx_antenna_map = rx;
	cmd->tx_antenna_map = tx;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_USE_FIXED_RATE (STA version).
 */
काष्ठा mwl8k_cmd_use_fixed_rate_sta अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 action;
	__le32 allow_rate_drop;
	__le32 num_rates;
	काष्ठा अणु
		__le32 is_ht_rate;
		__le32 enable_retry;
		__le32 rate;
		__le32 retry_count;
	पूर्ण rate_entry[8];
	__le32 rate_type;
	__le32 reserved1;
	__le32 reserved2;
पूर्ण __packed;

#घोषणा MWL8K_USE_AUTO_RATE	0x0002
#घोषणा MWL8K_UCAST_RATE	0

अटल पूर्णांक mwl8k_cmd_use_fixed_rate_sta(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_cmd_use_fixed_rate_sta *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_USE_FIXED_RATE);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(MWL8K_USE_AUTO_RATE);
	cmd->rate_type = cpu_to_le32(MWL8K_UCAST_RATE);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_USE_FIXED_RATE (AP version).
 */
काष्ठा mwl8k_cmd_use_fixed_rate_ap अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 action;
	__le32 allow_rate_drop;
	__le32 num_rates;
	काष्ठा mwl8k_rate_entry_ap अणु
		__le32 is_ht_rate;
		__le32 enable_retry;
		__le32 rate;
		__le32 retry_count;
	पूर्ण rate_entry[4];
	u8 multicast_rate;
	u8 multicast_rate_type;
	u8 management_rate;
पूर्ण __packed;

अटल पूर्णांक
mwl8k_cmd_use_fixed_rate_ap(काष्ठा ieee80211_hw *hw, पूर्णांक mcast, पूर्णांक mgmt)
अणु
	काष्ठा mwl8k_cmd_use_fixed_rate_ap *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_USE_FIXED_RATE);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(MWL8K_USE_AUTO_RATE);
	cmd->multicast_rate = mcast;
	cmd->management_rate = mgmt;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_ENABLE_SNIFFER.
 */
काष्ठा mwl8k_cmd_enable_snअगरfer अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 action;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_enable_snअगरfer(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा mwl8k_cmd_enable_snअगरfer *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_ENABLE_SNIFFER);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(!!enable);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

काष्ठा mwl8k_cmd_update_mac_addr अणु
	काष्ठा mwl8k_cmd_pkt header;
	जोड़ अणु
		काष्ठा अणु
			__le16 mac_type;
			__u8 mac_addr[ETH_ALEN];
		पूर्ण mbss;
		__u8 mac_addr[ETH_ALEN];
	पूर्ण;
पूर्ण __packed;

#घोषणा MWL8K_MAC_TYPE_PRIMARY_CLIENT		0
#घोषणा MWL8K_MAC_TYPE_SECONDARY_CLIENT		1
#घोषणा MWL8K_MAC_TYPE_PRIMARY_AP		2
#घोषणा MWL8K_MAC_TYPE_SECONDARY_AP		3

अटल पूर्णांक mwl8k_cmd_update_mac_addr(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर, u8 *mac, bool set)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);
	काष्ठा mwl8k_cmd_update_mac_addr *cmd;
	पूर्णांक mac_type;
	पूर्णांक rc;

	mac_type = MWL8K_MAC_TYPE_PRIMARY_AP;
	अगर (vअगर != शून्य && vअगर->type == NL80211_IFTYPE_STATION) अणु
		अगर (mwl8k_vअगर->macid + 1 == ffs(priv->sta_macids_supported))
			अगर (priv->ap_fw)
				mac_type = MWL8K_MAC_TYPE_SECONDARY_CLIENT;
			अन्यथा
				mac_type = MWL8K_MAC_TYPE_PRIMARY_CLIENT;
		अन्यथा
			mac_type = MWL8K_MAC_TYPE_SECONDARY_CLIENT;
	पूर्ण अन्यथा अगर (vअगर != शून्य && vअगर->type == NL80211_IFTYPE_AP) अणु
		अगर (mwl8k_vअगर->macid + 1 == ffs(priv->ap_macids_supported))
			mac_type = MWL8K_MAC_TYPE_PRIMARY_AP;
		अन्यथा
			mac_type = MWL8K_MAC_TYPE_SECONDARY_AP;
	पूर्ण

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	अगर (set)
		cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_MAC_ADDR);
	अन्यथा
		cmd->header.code = cpu_to_le16(MWL8K_CMD_DEL_MAC_ADDR);

	cmd->header.length = cpu_to_le16(माप(*cmd));
	अगर (priv->ap_fw) अणु
		cmd->mbss.mac_type = cpu_to_le16(mac_type);
		स_नकल(cmd->mbss.mac_addr, mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		स_नकल(cmd->mac_addr, mac, ETH_ALEN);
	पूर्ण

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * MWL8K_CMD_SET_MAC_ADDR.
 */
अटल अंतरभूत पूर्णांक mwl8k_cmd_set_mac_addr(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर, u8 *mac)
अणु
	वापस mwl8k_cmd_update_mac_addr(hw, vअगर, mac, true);
पूर्ण

/*
 * MWL8K_CMD_DEL_MAC_ADDR.
 */
अटल अंतरभूत पूर्णांक mwl8k_cmd_del_mac_addr(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर, u8 *mac)
अणु
	वापस mwl8k_cmd_update_mac_addr(hw, vअगर, mac, false);
पूर्ण

/*
 * CMD_SET_RATEADAPT_MODE.
 */
काष्ठा mwl8k_cmd_set_rate_adapt_mode अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 action;
	__le16 mode;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_set_rateadapt_mode(काष्ठा ieee80211_hw *hw, __u16 mode)
अणु
	काष्ठा mwl8k_cmd_set_rate_adapt_mode *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_RATEADAPT_MODE);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->mode = cpu_to_le16(mode);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_GET_WATCHDOG_BITMAP.
 */
काष्ठा mwl8k_cmd_get_watchकरोg_biपंचांगap अणु
	काष्ठा mwl8k_cmd_pkt header;
	u8	biपंचांगap;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_get_watchकरोg_biपंचांगap(काष्ठा ieee80211_hw *hw, u8 *biपंचांगap)
अणु
	काष्ठा mwl8k_cmd_get_watchकरोg_biपंचांगap *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_GET_WATCHDOG_BITMAP);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	rc = mwl8k_post_cmd(hw, &cmd->header);
	अगर (!rc)
		*biपंचांगap = cmd->biपंचांगap;

	kमुक्त(cmd);

	वापस rc;
पूर्ण

#घोषणा MWL8K_WMM_QUEUE_NUMBER	3

अटल व्योम mwl8k_destroy_ba(काष्ठा ieee80211_hw *hw,
			     u8 idx);

अटल व्योम mwl8k_watchकरोg_ba_events(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	u8 biपंचांगap = 0, stream_index;
	काष्ठा mwl8k_ampdu_stream *streams;
	काष्ठा mwl8k_priv *priv =
		container_of(work, काष्ठा mwl8k_priv, watchकरोg_ba_handle);
	काष्ठा ieee80211_hw *hw = priv->hw;
	पूर्णांक i;
	u32 status = 0;

	mwl8k_fw_lock(hw);

	rc = mwl8k_cmd_get_watchकरोg_biपंचांगap(priv->hw, &biपंचांगap);
	अगर (rc)
		जाओ करोne;

	spin_lock(&priv->stream_lock);

	/* the biपंचांगap is the hw queue number.  Map it to the ampdu queue. */
	क्रम (i = 0; i < TOTAL_HW_TX_QUEUES; i++) अणु
		अगर (biपंचांगap & (1 << i)) अणु
			stream_index = (i + MWL8K_WMM_QUEUE_NUMBER) %
				       TOTAL_HW_TX_QUEUES;
			streams = &priv->ampdu[stream_index];
			अगर (streams->state == AMPDU_STREAM_ACTIVE) अणु
				ieee80211_stop_tx_ba_session(streams->sta,
							     streams->tid);
				spin_unlock(&priv->stream_lock);
				mwl8k_destroy_ba(hw, stream_index);
				spin_lock(&priv->stream_lock);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(&priv->stream_lock);
करोne:
	atomic_dec(&priv->watchकरोg_event_pending);
	status = ioपढ़ो32(priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);
	ioग_लिखो32((status | MWL8K_A2H_INT_BA_WATCHDOG),
		  priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);
	mwl8k_fw_unlock(hw);
	वापस;
पूर्ण


/*
 * CMD_BSS_START.
 */
काष्ठा mwl8k_cmd_bss_start अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le32 enable;
पूर्ण __packed;

अटल पूर्णांक mwl8k_cmd_bss_start(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर, पूर्णांक enable)
अणु
	काष्ठा mwl8k_cmd_bss_start *cmd;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc;

	अगर (enable && (priv->running_bsses & (1 << mwl8k_vअगर->macid)))
		वापस 0;

	अगर (!enable && !(priv->running_bsses & (1 << mwl8k_vअगर->macid)))
		वापस 0;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BSS_START);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->enable = cpu_to_le32(enable);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	अगर (!rc) अणु
		अगर (enable)
			priv->running_bsses |= (1 << mwl8k_vअगर->macid);
		अन्यथा
			priv->running_bsses &= ~(1 << mwl8k_vअगर->macid);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम mwl8k_enable_bsses(काष्ठा ieee80211_hw *hw, bool enable, u32 biपंचांगap)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर, *पंचांगp_vअगर;
	काष्ठा ieee80211_vअगर *vअगर;

	list_क्रम_each_entry_safe(mwl8k_vअगर, पंचांगp_vअगर, &priv->vअगर_list, list) अणु
		vअगर = mwl8k_vअगर->vअगर;

		अगर (!(biपंचांगap & (1 << mwl8k_vअगर->macid)))
			जारी;

		अगर (vअगर->type == NL80211_IFTYPE_AP)
			mwl8k_cmd_bss_start(hw, vअगर, enable);
	पूर्ण
पूर्ण
/*
 * CMD_BASTREAM.
 */

/*
 * UPSTREAM is tx direction
 */
#घोषणा BASTREAM_FLAG_सूचीECTION_UPSTREAM	0x00
#घोषणा BASTREAM_FLAG_IMMEDIATE_TYPE		0x01

क्रमागत ba_stream_action_type अणु
	MWL8K_BA_CREATE,
	MWL8K_BA_UPDATE,
	MWL8K_BA_DESTROY,
	MWL8K_BA_FLUSH,
	MWL8K_BA_CHECK,
पूर्ण;


काष्ठा mwl8k_create_ba_stream अणु
	__le32	flags;
	__le32	idle_thrs;
	__le32	bar_thrs;
	__le32	winकरोw_size;
	u8	peer_mac_addr[6];
	u8	dialog_token;
	u8	tid;
	u8	queue_id;
	u8	param_info;
	__le32	ba_context;
	u8	reset_seq_no_flag;
	__le16	curr_seq_no;
	u8	sta_src_mac_addr[6];
पूर्ण __packed;

काष्ठा mwl8k_destroy_ba_stream अणु
	__le32	flags;
	__le32	ba_context;
पूर्ण __packed;

काष्ठा mwl8k_cmd_bastream अणु
	काष्ठा mwl8k_cmd_pkt	header;
	__le32	action;
	जोड़ अणु
		काष्ठा mwl8k_create_ba_stream	create_params;
		काष्ठा mwl8k_destroy_ba_stream	destroy_params;
	पूर्ण;
पूर्ण __packed;

अटल पूर्णांक
mwl8k_check_ba(काष्ठा ieee80211_hw *hw, काष्ठा mwl8k_ampdu_stream *stream,
	       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mwl8k_cmd_bastream *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BASTREAM);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	cmd->action = cpu_to_le32(MWL8K_BA_CHECK);

	cmd->create_params.queue_id = stream->idx;
	स_नकल(&cmd->create_params.peer_mac_addr[0], stream->sta->addr,
	       ETH_ALEN);
	cmd->create_params.tid = stream->tid;

	cmd->create_params.flags =
		cpu_to_le32(BASTREAM_FLAG_IMMEDIATE_TYPE) |
		cpu_to_le32(BASTREAM_FLAG_सूचीECTION_UPSTREAM);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);

	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक
mwl8k_create_ba(काष्ठा ieee80211_hw *hw, काष्ठा mwl8k_ampdu_stream *stream,
		u8 buf_size, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mwl8k_cmd_bastream *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;


	cmd->header.code = cpu_to_le16(MWL8K_CMD_BASTREAM);
	cmd->header.length = cpu_to_le16(माप(*cmd));

	cmd->action = cpu_to_le32(MWL8K_BA_CREATE);

	cmd->create_params.bar_thrs = cpu_to_le32((u32)buf_size);
	cmd->create_params.winकरोw_size = cpu_to_le32((u32)buf_size);
	cmd->create_params.queue_id = stream->idx;

	स_नकल(cmd->create_params.peer_mac_addr, stream->sta->addr, ETH_ALEN);
	cmd->create_params.tid = stream->tid;
	cmd->create_params.curr_seq_no = cpu_to_le16(0);
	cmd->create_params.reset_seq_no_flag = 1;

	cmd->create_params.param_info =
		(stream->sta->ht_cap.ampdu_factor &
		 IEEE80211_HT_AMPDU_PARM_FACTOR) |
		((stream->sta->ht_cap.ampdu_density << 2) &
		 IEEE80211_HT_AMPDU_PARM_DENSITY);

	cmd->create_params.flags =
		cpu_to_le32(BASTREAM_FLAG_IMMEDIATE_TYPE |
					BASTREAM_FLAG_सूचीECTION_UPSTREAM);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);

	wiphy_debug(hw->wiphy, "Created a BA stream for %pM : tid %d\n",
		stream->sta->addr, stream->tid);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल व्योम mwl8k_destroy_ba(काष्ठा ieee80211_hw *hw,
			     u8 idx)
अणु
	काष्ठा mwl8k_cmd_bastream *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_BASTREAM);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(MWL8K_BA_DESTROY);

	cmd->destroy_params.ba_context = cpu_to_le32(idx);
	mwl8k_post_cmd(hw, &cmd->header);

	wiphy_debug(hw->wiphy, "Deleted BA stream index %d\n", idx);

	kमुक्त(cmd);
पूर्ण

/*
 * CMD_SET_NEW_STN.
 */
काष्ठा mwl8k_cmd_set_new_stn अणु
	काष्ठा mwl8k_cmd_pkt header;
	__le16 aid;
	__u8 mac_addr[6];
	__le16 stn_id;
	__le16 action;
	__le16 rsvd;
	__le32 legacy_rates;
	__u8 ht_rates[4];
	__le16 cap_info;
	__le16 ht_capabilities_info;
	__u8 mac_ht_param_info;
	__u8 rev;
	__u8 control_channel;
	__u8 add_channel;
	__le16 op_mode;
	__le16 stbc;
	__u8 add_qos_info;
	__u8 is_qos_sta;
	__le32 fw_sta_ptr;
पूर्ण __packed;

#घोषणा MWL8K_STA_ACTION_ADD		0
#घोषणा MWL8K_STA_ACTION_REMOVE		2

अटल पूर्णांक mwl8k_cmd_set_new_stn_add(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mwl8k_cmd_set_new_stn *cmd;
	u32 rates;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_NEW_STN);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->aid = cpu_to_le16(sta->aid);
	स_नकल(cmd->mac_addr, sta->addr, ETH_ALEN);
	cmd->stn_id = cpu_to_le16(sta->aid);
	cmd->action = cpu_to_le16(MWL8K_STA_ACTION_ADD);
	अगर (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ)
		rates = sta->supp_rates[NL80211_BAND_2GHZ];
	अन्यथा
		rates = sta->supp_rates[NL80211_BAND_5GHZ] << 5;
	cmd->legacy_rates = cpu_to_le32(rates);
	अगर (sta->ht_cap.ht_supported) अणु
		cmd->ht_rates[0] = sta->ht_cap.mcs.rx_mask[0];
		cmd->ht_rates[1] = sta->ht_cap.mcs.rx_mask[1];
		cmd->ht_rates[2] = sta->ht_cap.mcs.rx_mask[2];
		cmd->ht_rates[3] = sta->ht_cap.mcs.rx_mask[3];
		cmd->ht_capabilities_info = cpu_to_le16(sta->ht_cap.cap);
		cmd->mac_ht_param_info = (sta->ht_cap.ampdu_factor & 3) |
			((sta->ht_cap.ampdu_density & 7) << 2);
		cmd->is_qos_sta = 1;
	पूर्ण

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_cmd_set_new_stn_add_self(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mwl8k_cmd_set_new_stn *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_NEW_STN);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	स_नकल(cmd->mac_addr, vअगर->addr, ETH_ALEN);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_cmd_set_new_stn_del(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर, u8 *addr)
अणु
	काष्ठा mwl8k_cmd_set_new_stn *cmd;
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc, i;
	u8 idx;

	spin_lock(&priv->stream_lock);
	/* Destroy any active ampdu streams क्रम this sta */
	क्रम (i = 0; i < MWL8K_NUM_AMPDU_STREAMS; i++) अणु
		काष्ठा mwl8k_ampdu_stream *s;
		s = &priv->ampdu[i];
		अगर (s->state != AMPDU_NO_STREAM) अणु
			अगर (स_भेद(s->sta->addr, addr, ETH_ALEN) == 0) अणु
				अगर (s->state == AMPDU_STREAM_ACTIVE) अणु
					idx = s->idx;
					spin_unlock(&priv->stream_lock);
					mwl8k_destroy_ba(hw, idx);
					spin_lock(&priv->stream_lock);
				पूर्ण अन्यथा अगर (s->state == AMPDU_STREAM_NEW) अणु
					mwl8k_हटाओ_stream(hw, s);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(&priv->stream_lock);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_NEW_STN);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	स_नकल(cmd->mac_addr, addr, ETH_ALEN);
	cmd->action = cpu_to_le16(MWL8K_STA_ACTION_REMOVE);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

/*
 * CMD_UPDATE_ENCRYPTION.
 */

#घोषणा MAX_ENCR_KEY_LENGTH	16
#घोषणा MIC_KEY_LENGTH		8

काष्ठा mwl8k_cmd_update_encryption अणु
	काष्ठा mwl8k_cmd_pkt header;

	__le32 action;
	__le32 reserved;
	__u8 mac_addr[6];
	__u8 encr_type;

पूर्ण __packed;

काष्ठा mwl8k_cmd_set_key अणु
	काष्ठा mwl8k_cmd_pkt header;

	__le32 action;
	__le32 reserved;
	__le16 length;
	__le16 key_type_id;
	__le32 key_info;
	__le32 key_id;
	__le16 key_len;
	__u8 key_material[MAX_ENCR_KEY_LENGTH];
	__u8 tkip_tx_mic_key[MIC_KEY_LENGTH];
	__u8 tkip_rx_mic_key[MIC_KEY_LENGTH];
	__le16 tkip_rsc_low;
	__le32 tkip_rsc_high;
	__le16 tkip_tsc_low;
	__le32 tkip_tsc_high;
	__u8 mac_addr[6];
पूर्ण __packed;

क्रमागत अणु
	MWL8K_ENCR_ENABLE,
	MWL8K_ENCR_SET_KEY,
	MWL8K_ENCR_REMOVE_KEY,
	MWL8K_ENCR_SET_GROUP_KEY,
पूर्ण;

#घोषणा MWL8K_UPDATE_ENCRYPTION_TYPE_WEP	0
#घोषणा MWL8K_UPDATE_ENCRYPTION_TYPE_DISABLE	1
#घोषणा MWL8K_UPDATE_ENCRYPTION_TYPE_TKIP	4
#घोषणा MWL8K_UPDATE_ENCRYPTION_TYPE_MIXED	7
#घोषणा MWL8K_UPDATE_ENCRYPTION_TYPE_AES	8

क्रमागत अणु
	MWL8K_ALG_WEP,
	MWL8K_ALG_TKIP,
	MWL8K_ALG_CCMP,
पूर्ण;

#घोषणा MWL8K_KEY_FLAG_TXGROUPKEY	0x00000004
#घोषणा MWL8K_KEY_FLAG_PAIRWISE		0x00000008
#घोषणा MWL8K_KEY_FLAG_TSC_VALID	0x00000040
#घोषणा MWL8K_KEY_FLAG_WEP_TXKEY	0x01000000
#घोषणा MWL8K_KEY_FLAG_MICKEY_VALID	0x02000000

अटल पूर्णांक mwl8k_cmd_update_encryption_enable(काष्ठा ieee80211_hw *hw,
					      काष्ठा ieee80211_vअगर *vअगर,
					      u8 *addr,
					      u8 encr_type)
अणु
	काष्ठा mwl8k_cmd_update_encryption *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_ENCRYPTION);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(MWL8K_ENCR_ENABLE);
	स_नकल(cmd->mac_addr, addr, ETH_ALEN);
	cmd->encr_type = encr_type;

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_encryption_set_cmd_info(काष्ठा mwl8k_cmd_set_key *cmd,
						u8 *addr,
						काष्ठा ieee80211_key_conf *key)
अणु
	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_ENCRYPTION);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->length = cpu_to_le16(माप(*cmd) -
				दुरत्व(काष्ठा mwl8k_cmd_set_key, length));
	cmd->key_id = cpu_to_le32(key->keyidx);
	cmd->key_len = cpu_to_le16(key->keylen);
	स_नकल(cmd->mac_addr, addr, ETH_ALEN);

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		cmd->key_type_id = cpu_to_le16(MWL8K_ALG_WEP);
		अगर (key->keyidx == 0)
			cmd->key_info =	cpu_to_le32(MWL8K_KEY_FLAG_WEP_TXKEY);

		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		cmd->key_type_id = cpu_to_le16(MWL8K_ALG_TKIP);
		cmd->key_info =	(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
			? cpu_to_le32(MWL8K_KEY_FLAG_PAIRWISE)
			: cpu_to_le32(MWL8K_KEY_FLAG_TXGROUPKEY);
		cmd->key_info |= cpu_to_le32(MWL8K_KEY_FLAG_MICKEY_VALID
						| MWL8K_KEY_FLAG_TSC_VALID);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		cmd->key_type_id = cpu_to_le16(MWL8K_ALG_CCMP);
		cmd->key_info =	(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
			? cpu_to_le32(MWL8K_KEY_FLAG_PAIRWISE)
			: cpu_to_le32(MWL8K_KEY_FLAG_TXGROUPKEY);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mwl8k_cmd_encryption_set_key(काष्ठा ieee80211_hw *hw,
						काष्ठा ieee80211_vअगर *vअगर,
						u8 *addr,
						काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mwl8k_cmd_set_key *cmd;
	पूर्णांक rc;
	पूर्णांक keymlen;
	u32 action;
	u8 idx;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	rc = mwl8k_encryption_set_cmd_info(cmd, addr, key);
	अगर (rc < 0)
		जाओ करोne;

	idx = key->keyidx;

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		action = MWL8K_ENCR_SET_KEY;
	अन्यथा
		action = MWL8K_ENCR_SET_GROUP_KEY;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (!mwl8k_vअगर->wep_key_conf[idx].enabled) अणु
			स_नकल(mwl8k_vअगर->wep_key_conf[idx].key, key,
						माप(*key) + key->keylen);
			mwl8k_vअगर->wep_key_conf[idx].enabled = 1;
		पूर्ण

		keymlen = key->keylen;
		action = MWL8K_ENCR_SET_KEY;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		keymlen = MAX_ENCR_KEY_LENGTH + 2 * MIC_KEY_LENGTH;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		keymlen = key->keylen;
		अवरोध;
	शेष:
		rc = -ENOTSUPP;
		जाओ करोne;
	पूर्ण

	स_नकल(cmd->key_material, key->key, keymlen);
	cmd->action = cpu_to_le32(action);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
करोne:
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_cmd_encryption_हटाओ_key(काष्ठा ieee80211_hw *hw,
						काष्ठा ieee80211_vअगर *vअगर,
						u8 *addr,
						काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mwl8k_cmd_set_key *cmd;
	पूर्णांक rc;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	rc = mwl8k_encryption_set_cmd_info(cmd, addr, key);
	अगर (rc < 0)
		जाओ करोne;

	अगर (key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
			key->cipher == WLAN_CIPHER_SUITE_WEP104)
		mwl8k_vअगर->wep_key_conf[key->keyidx].enabled = 0;

	cmd->action = cpu_to_le32(MWL8K_ENCR_REMOVE_KEY);

	rc = mwl8k_post_pervअगर_cmd(hw, vअगर, &cmd->header);
करोne:
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_set_key(काष्ठा ieee80211_hw *hw,
			 क्रमागत set_key_cmd cmd_param,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta,
			 काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक rc = 0;
	u8 encr_type;
	u8 *addr;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);
	काष्ठा mwl8k_priv *priv = hw->priv;

	अगर (vअगर->type == NL80211_IFTYPE_STATION && !priv->ap_fw)
		वापस -EOPNOTSUPP;

	अगर (sta == शून्य)
		addr = vअगर->addr;
	अन्यथा
		addr = sta->addr;

	अगर (cmd_param == SET_KEY) अणु
		rc = mwl8k_cmd_encryption_set_key(hw, vअगर, addr, key);
		अगर (rc)
			जाओ out;

		अगर ((key->cipher == WLAN_CIPHER_SUITE_WEP40)
				|| (key->cipher == WLAN_CIPHER_SUITE_WEP104))
			encr_type = MWL8K_UPDATE_ENCRYPTION_TYPE_WEP;
		अन्यथा
			encr_type = MWL8K_UPDATE_ENCRYPTION_TYPE_MIXED;

		rc = mwl8k_cmd_update_encryption_enable(hw, vअगर, addr,
								encr_type);
		अगर (rc)
			जाओ out;

		mwl8k_vअगर->is_hw_crypto_enabled = true;

	पूर्ण अन्यथा अणु
		rc = mwl8k_cmd_encryption_हटाओ_key(hw, vअगर, addr, key);

		अगर (rc)
			जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/*
 * CMD_UPDATE_STADB.
 */
काष्ठा ewc_ht_info अणु
	__le16	control1;
	__le16	control2;
	__le16	control3;
पूर्ण __packed;

काष्ठा peer_capability_info अणु
	/* Peer type - AP vs. STA.  */
	__u8	peer_type;

	/* Basic 802.11 capabilities from assoc resp.  */
	__le16	basic_caps;

	/* Set अगर peer supports 802.11n high throughput (HT).  */
	__u8	ht_support;

	/* Valid अगर HT is supported.  */
	__le16	ht_caps;
	__u8	extended_ht_caps;
	काष्ठा ewc_ht_info	ewc_info;

	/* Legacy rate table. Intersection of our rates and peer rates.  */
	__u8	legacy_rates[12];

	/* HT rate table. Intersection of our rates and peer rates.  */
	__u8	ht_rates[16];
	__u8	pad[16];

	/* If set, पूर्णांकeroperability mode, no proprietary extensions.  */
	__u8	पूर्णांकerop;
	__u8	pad2;
	__u8	station_id;
	__le16	amsdu_enabled;
पूर्ण __packed;

काष्ठा mwl8k_cmd_update_stadb अणु
	काष्ठा mwl8k_cmd_pkt header;

	/* See STADB_ACTION_TYPE */
	__le32	action;

	/* Peer MAC address */
	__u8	peer_addr[ETH_ALEN];

	__le32	reserved;

	/* Peer info - valid during add/update.  */
	काष्ठा peer_capability_info	peer_info;
पूर्ण __packed;

#घोषणा MWL8K_STA_DB_MODIFY_ENTRY	1
#घोषणा MWL8K_STA_DB_DEL_ENTRY		2

/* Peer Entry flags - used to define the type of the peer node */
#घोषणा MWL8K_PEER_TYPE_ACCESSPOINT	2

अटल पूर्णांक mwl8k_cmd_update_stadb_add(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mwl8k_cmd_update_stadb *cmd;
	काष्ठा peer_capability_info *p;
	u32 rates;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_STADB);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(MWL8K_STA_DB_MODIFY_ENTRY);
	स_नकल(cmd->peer_addr, sta->addr, ETH_ALEN);

	p = &cmd->peer_info;
	p->peer_type = MWL8K_PEER_TYPE_ACCESSPOINT;
	p->basic_caps = cpu_to_le16(vअगर->bss_conf.assoc_capability);
	p->ht_support = sta->ht_cap.ht_supported;
	p->ht_caps = cpu_to_le16(sta->ht_cap.cap);
	p->extended_ht_caps = (sta->ht_cap.ampdu_factor & 3) |
		((sta->ht_cap.ampdu_density & 7) << 2);
	अगर (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ)
		rates = sta->supp_rates[NL80211_BAND_2GHZ];
	अन्यथा
		rates = sta->supp_rates[NL80211_BAND_5GHZ] << 5;
	legacy_rate_mask_to_array(p->legacy_rates, rates);
	स_नकल(p->ht_rates, sta->ht_cap.mcs.rx_mask, 16);
	p->पूर्णांकerop = 1;
	p->amsdu_enabled = 0;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	अगर (!rc)
		rc = p->station_id;
	kमुक्त(cmd);

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_cmd_update_stadb_del(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर, u8 *addr)
अणु
	काष्ठा mwl8k_cmd_update_stadb *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_UPDATE_STADB);
	cmd->header.length = cpu_to_le16(माप(*cmd));
	cmd->action = cpu_to_le32(MWL8K_STA_DB_DEL_ENTRY);
	स_नकल(cmd->peer_addr, addr, ETH_ALEN);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kमुक्त(cmd);

	वापस rc;
पूर्ण


/*
 * Interrupt handling.
 */
अटल irqवापस_t mwl8k_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ieee80211_hw *hw = dev_id;
	काष्ठा mwl8k_priv *priv = hw->priv;
	u32 status;

	status = ioपढ़ो32(priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & MWL8K_A2H_INT_TX_DONE) अणु
		status &= ~MWL8K_A2H_INT_TX_DONE;
		tasklet_schedule(&priv->poll_tx_task);
	पूर्ण

	अगर (status & MWL8K_A2H_INT_RX_READY) अणु
		status &= ~MWL8K_A2H_INT_RX_READY;
		tasklet_schedule(&priv->poll_rx_task);
	पूर्ण

	अगर (status & MWL8K_A2H_INT_BA_WATCHDOG) अणु
		ioग_लिखो32(~MWL8K_A2H_INT_BA_WATCHDOG,
			  priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);

		atomic_inc(&priv->watchकरोg_event_pending);
		status &= ~MWL8K_A2H_INT_BA_WATCHDOG;
		ieee80211_queue_work(hw, &priv->watchकरोg_ba_handle);
	पूर्ण

	अगर (status)
		ioग_लिखो32(~status, priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);

	अगर (status & MWL8K_A2H_INT_OPC_DONE) अणु
		अगर (priv->hostcmd_रुको != शून्य)
			complete(priv->hostcmd_रुको);
	पूर्ण

	अगर (status & MWL8K_A2H_INT_QUEUE_EMPTY) अणु
		अगर (!mutex_is_locked(&priv->fw_mutex) &&
		    priv->radio_on && priv->pending_tx_pkts)
			mwl8k_tx_start(priv);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mwl8k_tx_poll(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mwl8k_priv *priv = from_tasklet(priv, t, poll_tx_task);
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(priv->pdev);
	पूर्णांक limit;
	पूर्णांक i;

	limit = 32;

	spin_lock(&priv->tx_lock);

	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		limit -= mwl8k_txq_reclaim(hw, i, limit, 0);

	अगर (!priv->pending_tx_pkts && priv->tx_रुको != शून्य) अणु
		complete(priv->tx_रुको);
		priv->tx_रुको = शून्य;
	पूर्ण

	spin_unlock(&priv->tx_lock);

	अगर (limit) अणु
		ग_लिखोl(~MWL8K_A2H_INT_TX_DONE,
		       priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	पूर्ण अन्यथा अणु
		tasklet_schedule(&priv->poll_tx_task);
	पूर्ण
पूर्ण

अटल व्योम mwl8k_rx_poll(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mwl8k_priv *priv = from_tasklet(priv, t, poll_rx_task);
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(priv->pdev);
	पूर्णांक limit;

	limit = 32;
	limit -= rxq_process(hw, 0, limit);
	limit -= rxq_refill(hw, 0, limit);

	अगर (limit) अणु
		ग_लिखोl(~MWL8K_A2H_INT_RX_READY,
		       priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	पूर्ण अन्यथा अणु
		tasklet_schedule(&priv->poll_rx_task);
	पूर्ण
पूर्ण


/*
 * Core driver operations.
 */
अटल व्योम mwl8k_tx(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_tx_control *control,
		     काष्ठा sk_buff *skb)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक index = skb_get_queue_mapping(skb);

	अगर (!priv->radio_on) अणु
		wiphy_debug(hw->wiphy,
			    "dropped TX frame since radio disabled\n");
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	mwl8k_txq_xmit(hw, index, control->sta, skb);
पूर्ण

अटल पूर्णांक mwl8k_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc;

	rc = request_irq(priv->pdev->irq, mwl8k_पूर्णांकerrupt,
			 IRQF_SHARED, MWL8K_NAME, hw);
	अगर (rc) अणु
		priv->irq = -1;
		wiphy_err(hw->wiphy, "failed to register IRQ handler\n");
		वापस -EIO;
	पूर्ण
	priv->irq = priv->pdev->irq;

	/* Enable TX reclaim and RX tasklets.  */
	tasklet_enable(&priv->poll_tx_task);
	tasklet_enable(&priv->poll_rx_task);

	/* Enable पूर्णांकerrupts */
	ioग_लिखो32(MWL8K_A2H_EVENTS, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	ioग_लिखो32(MWL8K_A2H_EVENTS,
		  priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);

	rc = mwl8k_fw_lock(hw);
	अगर (!rc) अणु
		rc = mwl8k_cmd_radio_enable(hw);

		अगर (!priv->ap_fw) अणु
			अगर (!rc)
				rc = mwl8k_cmd_enable_snअगरfer(hw, 0);

			अगर (!rc)
				rc = mwl8k_cmd_set_pre_scan(hw);

			अगर (!rc)
				rc = mwl8k_cmd_set_post_scan(hw,
						"\x00\x00\x00\x00\x00\x00");
		पूर्ण

		अगर (!rc)
			rc = mwl8k_cmd_set_rateadapt_mode(hw, 0);

		अगर (!rc)
			rc = mwl8k_cmd_set_wmm_mode(hw, 0);

		mwl8k_fw_unlock(hw);
	पूर्ण

	अगर (rc) अणु
		ioग_लिखो32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
		मुक्त_irq(priv->pdev->irq, hw);
		priv->irq = -1;
		tasklet_disable(&priv->poll_tx_task);
		tasklet_disable(&priv->poll_rx_task);
	पूर्ण अन्यथा अणु
		ieee80211_wake_queues(hw);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम mwl8k_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक i;

	अगर (!priv->hw_restart_in_progress)
		mwl8k_cmd_radio_disable(hw);

	ieee80211_stop_queues(hw);

	/* Disable पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	अगर (priv->irq != -1) अणु
		मुक्त_irq(priv->pdev->irq, hw);
		priv->irq = -1;
	पूर्ण

	/* Stop finalize join worker */
	cancel_work_sync(&priv->finalize_join_worker);
	cancel_work_sync(&priv->watchकरोg_ba_handle);
	अगर (priv->beacon_skb != शून्य)
		dev_kमुक्त_skb(priv->beacon_skb);

	/* Stop TX reclaim and RX tasklets.  */
	tasklet_disable(&priv->poll_tx_task);
	tasklet_disable(&priv->poll_rx_task);

	/* Return all skbs to mac80211 */
	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_reclaim(hw, i, पूर्णांक_उच्च, 1);
पूर्ण

अटल पूर्णांक mwl8k_reload_firmware(काष्ठा ieee80211_hw *hw, अक्षर *fw_image);

अटल पूर्णांक mwl8k_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर;
	u32 macids_supported;
	पूर्णांक macid, rc;
	काष्ठा mwl8k_device_info *di;

	/*
	 * Reject पूर्णांकerface creation अगर snअगरfer mode is active, as
	 * STA operation is mutually exclusive with hardware snअगरfer
	 * mode.  (Snअगरfer mode is only used on STA firmware.)
	 */
	अगर (priv->snअगरfer_enabled) अणु
		wiphy_info(hw->wiphy,
			   "unable to create STA interface because sniffer mode is enabled\n");
		वापस -EINVAL;
	पूर्ण

	di = priv->device_info;
	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		अगर (!priv->ap_fw && di->fw_image_ap) अणु
			/* we must load the ap fw to meet this request */
			अगर (!list_empty(&priv->vअगर_list))
				वापस -EBUSY;
			rc = mwl8k_reload_firmware(hw, di->fw_image_ap);
			अगर (rc)
				वापस rc;
		पूर्ण
		macids_supported = priv->ap_macids_supported;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (priv->ap_fw && di->fw_image_sta) अणु
			अगर (!list_empty(&priv->vअगर_list)) अणु
				wiphy_warn(hw->wiphy, "AP interface is running.\n"
					   "Adding STA interface for WDS");
			पूर्ण अन्यथा अणु
				/* we must load the sta fw to
				 * meet this request.
				 */
				rc = mwl8k_reload_firmware(hw,
							   di->fw_image_sta);
				अगर (rc)
					वापस rc;
			पूर्ण
		पूर्ण
		macids_supported = priv->sta_macids_supported;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	macid = ffs(macids_supported & ~priv->macids_used);
	अगर (!macid--)
		वापस -EBUSY;

	/* Setup driver निजी area. */
	mwl8k_vअगर = MWL8K_VIF(vअगर);
	स_रखो(mwl8k_vअगर, 0, माप(*mwl8k_vअगर));
	mwl8k_vअगर->vअगर = vअगर;
	mwl8k_vअगर->macid = macid;
	mwl8k_vअगर->seqno = 0;
	स_नकल(mwl8k_vअगर->bssid, vअगर->addr, ETH_ALEN);
	mwl8k_vअगर->is_hw_crypto_enabled = false;

	/* Set the mac address.  */
	mwl8k_cmd_set_mac_addr(hw, vअगर, vअगर->addr);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		mwl8k_cmd_set_new_stn_add_self(hw, vअगर);

	priv->macids_used |= 1 << mwl8k_vअगर->macid;
	list_add_tail(&mwl8k_vअगर->list, &priv->vअगर_list);

	वापस 0;
पूर्ण

अटल व्योम mwl8k_हटाओ_vअगर(काष्ठा mwl8k_priv *priv, काष्ठा mwl8k_vअगर *vअगर)
अणु
	/* Has ieee80211_restart_hw re-added the हटाओd पूर्णांकerfaces? */
	अगर (!priv->macids_used)
		वापस;

	priv->macids_used &= ~(1 << vअगर->macid);
	list_del(&vअगर->list);
पूर्ण

अटल व्योम mwl8k_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		mwl8k_cmd_set_new_stn_del(hw, vअगर, vअगर->addr);

	mwl8k_cmd_del_mac_addr(hw, vअगर, vअगर->addr);

	mwl8k_हटाओ_vअगर(priv, mwl8k_vअगर);
पूर्ण

अटल व्योम mwl8k_hw_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mwl8k_priv *priv =
		container_of(work, काष्ठा mwl8k_priv, fw_reload);
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा mwl8k_device_info *di;
	पूर्णांक rc;

	/* If some command is रुकोing क्रम a response, clear it */
	अगर (priv->hostcmd_रुको != शून्य) अणु
		complete(priv->hostcmd_रुको);
		priv->hostcmd_रुको = शून्य;
	पूर्ण

	priv->hw_restart_owner = current;
	di = priv->device_info;
	mwl8k_fw_lock(hw);

	अगर (priv->ap_fw)
		rc = mwl8k_reload_firmware(hw, di->fw_image_ap);
	अन्यथा
		rc = mwl8k_reload_firmware(hw, di->fw_image_sta);

	अगर (rc)
		जाओ fail;

	priv->hw_restart_owner = शून्य;
	priv->hw_restart_in_progress = false;

	/*
	 * This unlock will wake up the queues and
	 * also खोलोs the command path क्रम other
	 * commands
	 */
	mwl8k_fw_unlock(hw);

	ieee80211_restart_hw(hw);

	wiphy_err(hw->wiphy, "Firmware restarted successfully\n");

	वापस;
fail:
	mwl8k_fw_unlock(hw);

	wiphy_err(hw->wiphy, "Firmware restart failed\n");
पूर्ण

अटल पूर्णांक mwl8k_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc;

	rc = mwl8k_fw_lock(hw);
	अगर (rc)
		वापस rc;

	अगर (conf->flags & IEEE80211_CONF_IDLE)
		rc = mwl8k_cmd_radio_disable(hw);
	अन्यथा
		rc = mwl8k_cmd_radio_enable(hw);
	अगर (rc)
		जाओ out;

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		rc = mwl8k_cmd_set_rf_channel(hw, conf);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (conf->घातer_level > 18)
		conf->घातer_level = 18;

	अगर (priv->ap_fw) अणु

		अगर (conf->flags & IEEE80211_CONF_CHANGE_POWER) अणु
			rc = mwl8k_cmd_tx_घातer(hw, conf, conf->घातer_level);
			अगर (rc)
				जाओ out;
		पूर्ण


	पूर्ण अन्यथा अणु
		rc = mwl8k_cmd_rf_tx_घातer(hw, conf->घातer_level);
		अगर (rc)
			जाओ out;
		rc = mwl8k_cmd_mimo_config(hw, 0x7, 0x7);
	पूर्ण

out:
	mwl8k_fw_unlock(hw);

	वापस rc;
पूर्ण

अटल व्योम
mwl8k_bss_info_changed_sta(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	u32 ap_legacy_rates = 0;
	u8 ap_mcs_rates[16];
	पूर्णांक rc;

	अगर (mwl8k_fw_lock(hw))
		वापस;

	/*
	 * No need to capture a beacon अगर we're no दीर्घer associated.
	 */
	अगर ((changed & BSS_CHANGED_ASSOC) && !vअगर->bss_conf.assoc)
		priv->capture_beacon = false;

	/*
	 * Get the AP's legacy and MCS rates.
	 */
	अगर (vअगर->bss_conf.assoc) अणु
		काष्ठा ieee80211_sta *ap;

		rcu_पढ़ो_lock();

		ap = ieee80211_find_sta(vअगर, vअगर->bss_conf.bssid);
		अगर (ap == शून्य) अणु
			rcu_पढ़ो_unlock();
			जाओ out;
		पूर्ण

		अगर (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ) अणु
			ap_legacy_rates = ap->supp_rates[NL80211_BAND_2GHZ];
		पूर्ण अन्यथा अणु
			ap_legacy_rates =
				ap->supp_rates[NL80211_BAND_5GHZ] << 5;
		पूर्ण
		स_नकल(ap_mcs_rates, ap->ht_cap.mcs.rx_mask, 16);

		rcu_पढ़ो_unlock();

		अगर (changed & BSS_CHANGED_ASSOC) अणु
			अगर (!priv->ap_fw) अणु
				rc = mwl8k_cmd_set_rate(hw, vअगर,
							ap_legacy_rates,
							ap_mcs_rates);
				अगर (rc)
					जाओ out;

				rc = mwl8k_cmd_use_fixed_rate_sta(hw);
				अगर (rc)
					जाओ out;
			पूर्ण अन्यथा अणु
				पूर्णांक idx;
				पूर्णांक rate;

				/* Use AP firmware specअगरic rate command.
				 */
				idx = ffs(vअगर->bss_conf.basic_rates);
				अगर (idx)
					idx--;

				अगर (hw->conf.chandef.chan->band ==
				    NL80211_BAND_2GHZ)
					rate = mwl8k_rates_24[idx].hw_value;
				अन्यथा
					rate = mwl8k_rates_50[idx].hw_value;

				mwl8k_cmd_use_fixed_rate_ap(hw, rate, rate);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		rc = mwl8k_set_radio_preamble(hw,
				vअगर->bss_conf.use_लघु_preamble);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर ((changed & BSS_CHANGED_ERP_SLOT) && !priv->ap_fw)  अणु
		rc = mwl8k_cmd_set_slot(hw, vअगर->bss_conf.use_लघु_slot);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (vअगर->bss_conf.assoc && !priv->ap_fw &&
	    (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_ERP_CTS_PROT |
			BSS_CHANGED_HT))) अणु
		rc = mwl8k_cmd_set_aid(hw, vअगर, ap_legacy_rates);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (vअगर->bss_conf.assoc &&
	    (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BEACON_INT))) अणु
		/*
		 * Finalize the join.  Tell rx handler to process
		 * next beacon from our BSSID.
		 */
		स_नकल(priv->capture_bssid, vअगर->bss_conf.bssid, ETH_ALEN);
		priv->capture_beacon = true;
	पूर्ण

out:
	mwl8k_fw_unlock(hw);
पूर्ण

अटल व्योम
mwl8k_bss_info_changed_ap(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	पूर्णांक rc;

	अगर (mwl8k_fw_lock(hw))
		वापस;

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		rc = mwl8k_set_radio_preamble(hw,
				vअगर->bss_conf.use_लघु_preamble);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		पूर्णांक idx;
		पूर्णांक rate;

		/*
		 * Use lowest supported basic rate क्रम multicasts
		 * and management frames (such as probe responses --
		 * beacons will always go out at 1 Mb/s).
		 */
		idx = ffs(vअगर->bss_conf.basic_rates);
		अगर (idx)
			idx--;

		अगर (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ)
			rate = mwl8k_rates_24[idx].hw_value;
		अन्यथा
			rate = mwl8k_rates_50[idx].hw_value;

		mwl8k_cmd_use_fixed_rate_ap(hw, rate, rate);
	पूर्ण

	अगर (changed & (BSS_CHANGED_BEACON_INT | BSS_CHANGED_BEACON)) अणु
		काष्ठा sk_buff *skb;

		skb = ieee80211_beacon_get(hw, vअगर);
		अगर (skb != शून्य) अणु
			mwl8k_cmd_set_beacon(hw, vअगर, skb->data, skb->len);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED)
		mwl8k_cmd_bss_start(hw, vअगर, info->enable_beacon);

out:
	mwl8k_fw_unlock(hw);
पूर्ण

अटल व्योम
mwl8k_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		mwl8k_bss_info_changed_sta(hw, vअगर, info, changed);
	अगर (vअगर->type == NL80211_IFTYPE_AP)
		mwl8k_bss_info_changed_ap(hw, vअगर, info, changed);
पूर्ण

अटल u64 mwl8k_prepare_multicast(काष्ठा ieee80211_hw *hw,
				   काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा mwl8k_cmd_pkt *cmd;

	/*
	 * Synthesize and वापस a command packet that programs the
	 * hardware multicast address filter.  At this poपूर्णांक we करोn't
	 * know whether FIF_ALLMULTI is being requested, but अगर it is,
	 * we'll end up throwing this packet away and creating a new
	 * one in mwl8k_configure_filter().
	 */
	cmd = __mwl8k_cmd_mac_multicast_adr(hw, 0, mc_list);

	वापस (अचिन्हित दीर्घ)cmd;
पूर्ण

अटल पूर्णांक
mwl8k_configure_filter_snअगरfer(काष्ठा ieee80211_hw *hw,
			       अचिन्हित पूर्णांक changed_flags,
			       अचिन्हित पूर्णांक *total_flags)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	/*
	 * Hardware snअगरfer mode is mutually exclusive with STA
	 * operation, so refuse to enable snअगरfer mode अगर a STA
	 * पूर्णांकerface is active.
	 */
	अगर (!list_empty(&priv->vअगर_list)) अणु
		अगर (net_ratelimit())
			wiphy_info(hw->wiphy,
				   "not enabling sniffer mode because STA interface is active\n");
		वापस 0;
	पूर्ण

	अगर (!priv->snअगरfer_enabled) अणु
		अगर (mwl8k_cmd_enable_snअगरfer(hw, 1))
			वापस 0;
		priv->snअगरfer_enabled = true;
	पूर्ण

	*total_flags &=	FIF_ALLMULTI |
			FIF_BCN_PRBRESP_PROMISC | FIF_CONTROL |
			FIF_OTHER_BSS;

	वापस 1;
पूर्ण

अटल काष्ठा mwl8k_vअगर *mwl8k_first_vअगर(काष्ठा mwl8k_priv *priv)
अणु
	अगर (!list_empty(&priv->vअगर_list))
		वापस list_entry(priv->vअगर_list.next, काष्ठा mwl8k_vअगर, list);

	वापस शून्य;
पूर्ण

अटल व्योम mwl8k_configure_filter(काष्ठा ieee80211_hw *hw,
				   अचिन्हित पूर्णांक changed_flags,
				   अचिन्हित पूर्णांक *total_flags,
				   u64 multicast)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_cmd_pkt *cmd = (व्योम *)(अचिन्हित दीर्घ)multicast;

	/*
	 * AP firmware करोesn't allow fine-grained control over
	 * the receive filter.
	 */
	अगर (priv->ap_fw) अणु
		*total_flags &= FIF_ALLMULTI | FIF_BCN_PRBRESP_PROMISC;
		kमुक्त(cmd);
		वापस;
	पूर्ण

	/*
	 * Enable hardware snअगरfer mode अगर FIF_CONTROL or
	 * FIF_OTHER_BSS is requested.
	 */
	अगर (*total_flags & (FIF_CONTROL | FIF_OTHER_BSS) &&
	    mwl8k_configure_filter_snअगरfer(hw, changed_flags, total_flags)) अणु
		kमुक्त(cmd);
		वापस;
	पूर्ण

	/* Clear unsupported feature flags */
	*total_flags &= FIF_ALLMULTI | FIF_BCN_PRBRESP_PROMISC;

	अगर (mwl8k_fw_lock(hw)) अणु
		kमुक्त(cmd);
		वापस;
	पूर्ण

	अगर (priv->snअगरfer_enabled) अणु
		mwl8k_cmd_enable_snअगरfer(hw, 0);
		priv->snअगरfer_enabled = false;
	पूर्ण

	अगर (changed_flags & FIF_BCN_PRBRESP_PROMISC) अणु
		अगर (*total_flags & FIF_BCN_PRBRESP_PROMISC) अणु
			/*
			 * Disable the BSS filter.
			 */
			mwl8k_cmd_set_pre_scan(hw);
		पूर्ण अन्यथा अणु
			काष्ठा mwl8k_vअगर *mwl8k_vअगर;
			स्थिर u8 *bssid;

			/*
			 * Enable the BSS filter.
			 *
			 * If there is an active STA पूर्णांकerface, use that
			 * पूर्णांकerface's BSSID, otherwise use a dummy one
			 * (where the OUI part needs to be nonzero क्रम
			 * the BSSID to be accepted by POST_SCAN).
			 */
			mwl8k_vअगर = mwl8k_first_vअगर(priv);
			अगर (mwl8k_vअगर != शून्य)
				bssid = mwl8k_vअगर->vअगर->bss_conf.bssid;
			अन्यथा
				bssid = "\x01\x00\x00\x00\x00\x00";

			mwl8k_cmd_set_post_scan(hw, bssid);
		पूर्ण
	पूर्ण

	/*
	 * If FIF_ALLMULTI is being requested, throw away the command
	 * packet that ->prepare_multicast() built and replace it with
	 * a command packet that enables reception of all multicast
	 * packets.
	 */
	अगर (*total_flags & FIF_ALLMULTI) अणु
		kमुक्त(cmd);
		cmd = __mwl8k_cmd_mac_multicast_adr(hw, 1, शून्य);
	पूर्ण

	अगर (cmd != शून्य) अणु
		mwl8k_post_cmd(hw, cmd);
		kमुक्त(cmd);
	पूर्ण

	mwl8k_fw_unlock(hw);
पूर्ण

अटल पूर्णांक mwl8k_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	वापस mwl8k_cmd_set_rts_threshold(hw, value);
पूर्ण

अटल पूर्णांक mwl8k_sta_हटाओ(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;

	अगर (priv->ap_fw)
		वापस mwl8k_cmd_set_new_stn_del(hw, vअगर, sta->addr);
	अन्यथा
		वापस mwl8k_cmd_update_stadb_del(hw, vअगर, sta->addr);
पूर्ण

अटल पूर्णांक mwl8k_sta_add(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा mwl8k_vअगर *mwl8k_vअगर = MWL8K_VIF(vअगर);
	काष्ठा ieee80211_key_conf *key;

	अगर (!priv->ap_fw) अणु
		ret = mwl8k_cmd_update_stadb_add(hw, vअगर, sta);
		अगर (ret >= 0) अणु
			MWL8K_STA(sta)->peer_id = ret;
			अगर (sta->ht_cap.ht_supported)
				MWL8K_STA(sta)->is_ampdu_allowed = true;
			ret = 0;
		पूर्ण

	पूर्ण अन्यथा अणु
		ret = mwl8k_cmd_set_new_stn_add(hw, vअगर, sta);
	पूर्ण

	क्रम (i = 0; i < NUM_WEP_KEYS; i++) अणु
		key = IEEE80211_KEY_CONF(mwl8k_vअगर->wep_key_conf[i].key);
		अगर (mwl8k_vअगर->wep_key_conf[i].enabled)
			mwl8k_set_key(hw, SET_KEY, vअगर, sta, key);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mwl8k_conf_tx(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			 स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc;

	rc = mwl8k_fw_lock(hw);
	अगर (!rc) अणु
		BUG_ON(queue > MWL8K_TX_WMM_QUEUES - 1);
		स_नकल(&priv->wmm_params[queue], params, माप(*params));

		अगर (!priv->wmm_enabled)
			rc = mwl8k_cmd_set_wmm_mode(hw, 1);

		अगर (!rc) अणु
			पूर्णांक q = MWL8K_TX_WMM_QUEUES - 1 - queue;
			rc = mwl8k_cmd_set_edca_params(hw, q,
						       params->cw_min,
						       params->cw_max,
						       params->aअगरs,
						       params->txop);
		पूर्ण

		mwl8k_fw_unlock(hw);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_get_stats(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_low_level_stats *stats)
अणु
	वापस mwl8k_cmd_get_stat(hw, stats);
पूर्ण

अटल पूर्णांक mwl8k_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_supported_band *sband;

	अगर (priv->ap_fw) अणु
		sband = hw->wiphy->bands[NL80211_BAND_2GHZ];

		अगर (sband && idx >= sband->n_channels) अणु
			idx -= sband->n_channels;
			sband = शून्य;
		पूर्ण

		अगर (!sband)
			sband = hw->wiphy->bands[NL80211_BAND_5GHZ];

		अगर (!sband || idx >= sband->n_channels)
			वापस -ENOENT;

		स_नकल(survey, &priv->survey[idx], माप(*survey));
		survey->channel = &sband->channels[idx];

		वापस 0;
	पूर्ण

	अगर (idx != 0)
		वापस -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = priv->noise;

	वापस 0;
पूर्ण

#घोषणा MAX_AMPDU_ATTEMPTS 5

अटल पूर्णांक
mwl8k_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	u8 buf_size = params->buf_size;
	पूर्णांक i, rc = 0;
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_ampdu_stream *stream;
	u8 *addr = sta->addr, idx;
	काष्ठा mwl8k_sta *sta_info = MWL8K_STA(sta);

	अगर (!ieee80211_hw_check(hw, AMPDU_AGGREGATION))
		वापस -ENOTSUPP;

	spin_lock(&priv->stream_lock);
	stream = mwl8k_lookup_stream(hw, addr, tid);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		/* By the समय we get here the hw queues may contain outgoing
		 * packets क्रम this RA/TID that are not part of this BA
		 * session.  The hw will assign sequence numbers to these
		 * packets as they go out.  So अगर we query the hw क्रम its next
		 * sequence number and use that क्रम the SSN here, it may end up
		 * being wrong, which will lead to sequence number mismatch at
		 * the recipient.  To aव्योम this, we reset the sequence number
		 * to O क्रम the first MPDU in this BA stream.
		 */
		*ssn = 0;
		अगर (stream == शून्य) अणु
			/* This means that somebody outside this driver called
			 * ieee80211_start_tx_ba_session.  This is unexpected
			 * because we करो our own rate control.  Just warn and
			 * move on.
			 */
			wiphy_warn(hw->wiphy, "Unexpected call to %s.  "
				   "Proceeding anyway.\n", __func__);
			stream = mwl8k_add_stream(hw, sta, tid);
		पूर्ण
		अगर (stream == शून्य) अणु
			wiphy_debug(hw->wiphy, "no free AMPDU streams\n");
			rc = -EBUSY;
			अवरोध;
		पूर्ण
		stream->state = AMPDU_STREAM_IN_PROGRESS;

		/* Release the lock beक्रमe we करो the समय consuming stuff */
		spin_unlock(&priv->stream_lock);
		क्रम (i = 0; i < MAX_AMPDU_ATTEMPTS; i++) अणु

			/* Check अगर link is still valid */
			अगर (!sta_info->is_ampdu_allowed) अणु
				spin_lock(&priv->stream_lock);
				mwl8k_हटाओ_stream(hw, stream);
				spin_unlock(&priv->stream_lock);
				वापस -EBUSY;
			पूर्ण

			rc = mwl8k_check_ba(hw, stream, vअगर);

			/* If HW restart is in progress mwl8k_post_cmd will
			 * वापस -EBUSY. Aव्योम retrying mwl8k_check_ba in
			 * such हालs
			 */
			अगर (!rc || rc == -EBUSY)
				अवरोध;
			/*
			 * HW queues take समय to be flushed, give them
			 * sufficient समय
			 */

			msleep(1000);
		पूर्ण
		spin_lock(&priv->stream_lock);
		अगर (rc) अणु
			wiphy_err(hw->wiphy, "Stream for tid %d busy after %d"
				" attempts\n", tid, MAX_AMPDU_ATTEMPTS);
			mwl8k_हटाओ_stream(hw, stream);
			rc = -EBUSY;
			अवरोध;
		पूर्ण
		rc = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		अगर (stream) अणु
			अगर (stream->state == AMPDU_STREAM_ACTIVE) अणु
				idx = stream->idx;
				spin_unlock(&priv->stream_lock);
				mwl8k_destroy_ba(hw, idx);
				spin_lock(&priv->stream_lock);
			पूर्ण
			mwl8k_हटाओ_stream(hw, stream);
		पूर्ण
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		BUG_ON(stream == शून्य);
		BUG_ON(stream->state != AMPDU_STREAM_IN_PROGRESS);
		spin_unlock(&priv->stream_lock);
		rc = mwl8k_create_ba(hw, stream, buf_size, vअगर);
		spin_lock(&priv->stream_lock);
		अगर (!rc)
			stream->state = AMPDU_STREAM_ACTIVE;
		अन्यथा अणु
			idx = stream->idx;
			spin_unlock(&priv->stream_lock);
			mwl8k_destroy_ba(hw, idx);
			spin_lock(&priv->stream_lock);
			wiphy_debug(hw->wiphy,
				"Failed adding stream for sta %pM tid %d\n",
				addr, tid);
			mwl8k_हटाओ_stream(hw, stream);
		पूर्ण
		अवरोध;

	शेष:
		rc = -ENOTSUPP;
	पूर्ण

	spin_unlock(&priv->stream_lock);
	वापस rc;
पूर्ण

अटल व्योम mwl8k_sw_scan_start(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				स्थिर u8 *mac_addr)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	u8 पंचांगp;

	अगर (!priv->ap_fw)
		वापस;

	/* clear all stats */
	priv->channel_समय = 0;
	ioपढ़ो32(priv->regs + BBU_RXRDY_CNT_REG);
	ioपढ़ो32(priv->regs + NOK_CCA_CNT_REG);
	mwl8k_cmd_bbp_reg_access(priv->hw, 0, BBU_AVG_NOISE_VAL, &पंचांगp);

	priv->sw_scan_start = true;
पूर्ण

अटल व्योम mwl8k_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	u8 पंचांगp;

	अगर (!priv->ap_fw)
		वापस;

	priv->sw_scan_start = false;

	/* clear all stats */
	priv->channel_समय = 0;
	ioपढ़ो32(priv->regs + BBU_RXRDY_CNT_REG);
	ioपढ़ो32(priv->regs + NOK_CCA_CNT_REG);
	mwl8k_cmd_bbp_reg_access(priv->hw, 0, BBU_AVG_NOISE_VAL, &पंचांगp);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops mwl8k_ops = अणु
	.tx			= mwl8k_tx,
	.start			= mwl8k_start,
	.stop			= mwl8k_stop,
	.add_पूर्णांकerface		= mwl8k_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= mwl8k_हटाओ_पूर्णांकerface,
	.config			= mwl8k_config,
	.bss_info_changed	= mwl8k_bss_info_changed,
	.prepare_multicast	= mwl8k_prepare_multicast,
	.configure_filter	= mwl8k_configure_filter,
	.set_key                = mwl8k_set_key,
	.set_rts_threshold	= mwl8k_set_rts_threshold,
	.sta_add		= mwl8k_sta_add,
	.sta_हटाओ		= mwl8k_sta_हटाओ,
	.conf_tx		= mwl8k_conf_tx,
	.get_stats		= mwl8k_get_stats,
	.get_survey		= mwl8k_get_survey,
	.ampdu_action		= mwl8k_ampdu_action,
	.sw_scan_start		= mwl8k_sw_scan_start,
	.sw_scan_complete	= mwl8k_sw_scan_complete,
पूर्ण;

अटल व्योम mwl8k_finalize_join_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mwl8k_priv *priv =
		container_of(work, काष्ठा mwl8k_priv, finalize_join_worker);
	काष्ठा sk_buff *skb = priv->beacon_skb;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	पूर्णांक len = skb->len - दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	स्थिर u8 *tim = cfg80211_find_ie(WLAN_EID_TIM,
					 mgmt->u.beacon.variable, len);
	पूर्णांक dtim_period = 1;

	अगर (tim && tim[1] >= 2)
		dtim_period = tim[3];

	mwl8k_cmd_finalize_join(priv->hw, skb->data, skb->len, dtim_period);

	dev_kमुक्त_skb(skb);
	priv->beacon_skb = शून्य;
पूर्ण

क्रमागत अणु
	MWL8363 = 0,
	MWL8687,
	MWL8366,
	MWL8764,
पूर्ण;

#घोषणा MWL8K_8366_AP_FW_API 3
#घोषणा _MWL8K_8366_AP_FW(api) "mwl8k/fmimage_8366_ap-" #api ".fw"
#घोषणा MWL8K_8366_AP_FW(api) _MWL8K_8366_AP_FW(api)

#घोषणा MWL8K_8764_AP_FW_API 1
#घोषणा _MWL8K_8764_AP_FW(api) "mwl8k/fmimage_8764_ap-" #api ".fw"
#घोषणा MWL8K_8764_AP_FW(api) _MWL8K_8764_AP_FW(api)

अटल काष्ठा mwl8k_device_info mwl8k_info_tbl[] = अणु
	[MWL8363] = अणु
		.part_name	= "88w8363",
		.helper_image	= "mwl8k/helper_8363.fw",
		.fw_image_sta	= "mwl8k/fmimage_8363.fw",
	पूर्ण,
	[MWL8687] = अणु
		.part_name	= "88w8687",
		.helper_image	= "mwl8k/helper_8687.fw",
		.fw_image_sta	= "mwl8k/fmimage_8687.fw",
	पूर्ण,
	[MWL8366] = अणु
		.part_name	= "88w8366",
		.helper_image	= "mwl8k/helper_8366.fw",
		.fw_image_sta	= "mwl8k/fmimage_8366.fw",
		.fw_image_ap	= MWL8K_8366_AP_FW(MWL8K_8366_AP_FW_API),
		.fw_api_ap	= MWL8K_8366_AP_FW_API,
		.ap_rxd_ops	= &rxd_ap_ops,
	पूर्ण,
	[MWL8764] = अणु
		.part_name	= "88w8764",
		.fw_image_ap	= MWL8K_8764_AP_FW(MWL8K_8764_AP_FW_API),
		.fw_api_ap	= MWL8K_8764_AP_FW_API,
		.ap_rxd_ops	= &rxd_ap_ops,
	पूर्ण,
पूर्ण;

MODULE_FIRMWARE("mwl8k/helper_8363.fw");
MODULE_FIRMWARE("mwl8k/fmimage_8363.fw");
MODULE_FIRMWARE("mwl8k/helper_8687.fw");
MODULE_FIRMWARE("mwl8k/fmimage_8687.fw");
MODULE_FIRMWARE("mwl8k/helper_8366.fw");
MODULE_FIRMWARE("mwl8k/fmimage_8366.fw");
MODULE_FIRMWARE(MWL8K_8366_AP_FW(MWL8K_8366_AP_FW_API));

अटल स्थिर काष्ठा pci_device_id mwl8k_pci_id_table[] = अणु
	अणु PCI_VDEVICE(MARVELL, 0x2a0a), .driver_data = MWL8363, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a0c), .driver_data = MWL8363, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a24), .driver_data = MWL8363, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a2b), .driver_data = MWL8687, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a30), .driver_data = MWL8687, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a40), .driver_data = MWL8366, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a41), .driver_data = MWL8366, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a42), .driver_data = MWL8366, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2a43), .driver_data = MWL8366, पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x2b36), .driver_data = MWL8764, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, mwl8k_pci_id_table);

अटल पूर्णांक mwl8k_request_alt_fw(काष्ठा mwl8k_priv *priv)
अणु
	पूर्णांक rc;
	prपूर्णांकk(KERN_ERR "%s: Error requesting preferred fw %s.\n"
	       "Trying alternative firmware %s\n", pci_name(priv->pdev),
	       priv->fw_pref, priv->fw_alt);
	rc = mwl8k_request_fw(priv, priv->fw_alt, &priv->fw_ucode, true);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Error requesting alt fw %s\n",
		       pci_name(priv->pdev), priv->fw_alt);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mwl8k_firmware_load_success(काष्ठा mwl8k_priv *priv);
अटल व्योम mwl8k_fw_state_machine(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा mwl8k_priv *priv = context;
	काष्ठा mwl8k_device_info *di = priv->device_info;
	पूर्णांक rc;

	चयन (priv->fw_state) अणु
	हाल FW_STATE_INIT:
		अगर (!fw) अणु
			prपूर्णांकk(KERN_ERR "%s: Error requesting helper fw %s\n",
			       pci_name(priv->pdev), di->helper_image);
			जाओ fail;
		पूर्ण
		priv->fw_helper = fw;
		rc = mwl8k_request_fw(priv, priv->fw_pref, &priv->fw_ucode,
				      true);
		अगर (rc && priv->fw_alt) अणु
			rc = mwl8k_request_alt_fw(priv);
			अगर (rc)
				जाओ fail;
			priv->fw_state = FW_STATE_LOADING_ALT;
		पूर्ण अन्यथा अगर (rc)
			जाओ fail;
		अन्यथा
			priv->fw_state = FW_STATE_LOADING_PREF;
		अवरोध;

	हाल FW_STATE_LOADING_PREF:
		अगर (!fw) अणु
			अगर (priv->fw_alt) अणु
				rc = mwl8k_request_alt_fw(priv);
				अगर (rc)
					जाओ fail;
				priv->fw_state = FW_STATE_LOADING_ALT;
			पूर्ण अन्यथा
				जाओ fail;
		पूर्ण अन्यथा अणु
			priv->fw_ucode = fw;
			rc = mwl8k_firmware_load_success(priv);
			अगर (rc)
				जाओ fail;
			अन्यथा
				complete(&priv->firmware_loading_complete);
		पूर्ण
		अवरोध;

	हाल FW_STATE_LOADING_ALT:
		अगर (!fw) अणु
			prपूर्णांकk(KERN_ERR "%s: Error requesting alt fw %s\n",
			       pci_name(priv->pdev), di->helper_image);
			जाओ fail;
		पूर्ण
		priv->fw_ucode = fw;
		rc = mwl8k_firmware_load_success(priv);
		अगर (rc)
			जाओ fail;
		अन्यथा
			complete(&priv->firmware_loading_complete);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "%s: Unexpected firmware loading state: %d\n",
		       MWL8K_NAME, priv->fw_state);
		BUG_ON(1);
	पूर्ण

	वापस;

fail:
	priv->fw_state = FW_STATE_ERROR;
	complete(&priv->firmware_loading_complete);
	device_release_driver(&priv->pdev->dev);
	mwl8k_release_firmware(priv);
पूर्ण

#घोषणा MAX_RESTART_ATTEMPTS 1
अटल पूर्णांक mwl8k_init_firmware(काष्ठा ieee80211_hw *hw, अक्षर *fw_image,
			       bool noरुको)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc;
	पूर्णांक count = MAX_RESTART_ATTEMPTS;

retry:
	/* Reset firmware and hardware */
	mwl8k_hw_reset(priv);

	/* Ask userland hotplug daemon क्रम the device firmware */
	rc = mwl8k_request_firmware(priv, fw_image, noरुको);
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "Firmware files not found\n");
		वापस rc;
	पूर्ण

	अगर (noरुको)
		वापस rc;

	/* Load firmware पूर्णांकo hardware */
	rc = mwl8k_load_firmware(hw);
	अगर (rc)
		wiphy_err(hw->wiphy, "Cannot start firmware\n");

	/* Reclaim memory once firmware is successfully loaded */
	mwl8k_release_firmware(priv);

	अगर (rc && count) अणु
		/* FW did not start successfully;
		 * lets try one more समय
		 */
		count--;
		wiphy_err(hw->wiphy, "Trying to reload the firmware again\n");
		msleep(20);
		जाओ retry;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक mwl8k_init_txqs(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++) अणु
		rc = mwl8k_txq_init(hw, i);
		अगर (rc)
			अवरोध;
		अगर (priv->ap_fw)
			ioग_लिखो32(priv->txq[i].txd_dma,
				  priv->sram + priv->txq_offset[i]);
	पूर्ण
	वापस rc;
पूर्ण

/* initialize hw after successfully loading a firmware image */
अटल पूर्णांक mwl8k_probe_hw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mwl8k_priv *priv = hw->priv;
	पूर्णांक rc = 0;
	पूर्णांक i;

	अगर (priv->ap_fw) अणु
		priv->rxd_ops = priv->device_info->ap_rxd_ops;
		अगर (priv->rxd_ops == शून्य) अणु
			wiphy_err(hw->wiphy,
				  "Driver does not have AP firmware image support for this hardware\n");
			rc = -ENOENT;
			जाओ err_stop_firmware;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->rxd_ops = &rxd_sta_ops;
	पूर्ण

	priv->snअगरfer_enabled = false;
	priv->wmm_enabled = false;
	priv->pending_tx_pkts = 0;
	atomic_set(&priv->watchकरोg_event_pending, 0);

	rc = mwl8k_rxq_init(hw, 0);
	अगर (rc)
		जाओ err_stop_firmware;
	rxq_refill(hw, 0, पूर्णांक_उच्च);

	/* For the sta firmware, we need to know the dma addresses of tx queues
	 * beक्रमe sending MWL8K_CMD_GET_HW_SPEC.  So we must initialize them
	 * prior to issuing this command.  But क्रम the AP हाल, we learn the
	 * total number of queues from the result CMD_GET_HW_SPEC, so क्रम this
	 * हाल we must initialize the tx queues after.
	 */
	priv->num_ampdu_queues = 0;
	अगर (!priv->ap_fw) अणु
		rc = mwl8k_init_txqs(hw);
		अगर (rc)
			जाओ err_मुक्त_queues;
	पूर्ण

	ioग_लिखो32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	ioग_लिखो32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	ioग_लिखो32(MWL8K_A2H_INT_TX_DONE|MWL8K_A2H_INT_RX_READY|
		  MWL8K_A2H_INT_BA_WATCHDOG,
		  priv->regs + MWL8K_HIU_A2H_INTERRUPT_CLEAR_SEL);
	ioग_लिखो32(MWL8K_A2H_INT_OPC_DONE,
		  priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS_MASK);

	rc = request_irq(priv->pdev->irq, mwl8k_पूर्णांकerrupt,
			 IRQF_SHARED, MWL8K_NAME, hw);
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "failed to register IRQ handler\n");
		जाओ err_मुक्त_queues;
	पूर्ण

	/*
	 * When hw restart is requested,
	 * mac80211 will take care of clearing
	 * the ampdu streams, so करो not clear
	 * the ampdu state here
	 */
	अगर (!priv->hw_restart_in_progress)
		स_रखो(priv->ampdu, 0, माप(priv->ampdu));

	/*
	 * Temporarily enable पूर्णांकerrupts.  Initial firmware host
	 * commands use पूर्णांकerrupts and aव्योम polling.  Disable
	 * पूर्णांकerrupts when करोne.
	 */
	ioग_लिखो32(MWL8K_A2H_EVENTS, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);

	/* Get config data, mac addrs etc */
	अगर (priv->ap_fw) अणु
		rc = mwl8k_cmd_get_hw_spec_ap(hw);
		अगर (!rc)
			rc = mwl8k_init_txqs(hw);
		अगर (!rc)
			rc = mwl8k_cmd_set_hw_spec(hw);
	पूर्ण अन्यथा अणु
		rc = mwl8k_cmd_get_hw_spec_sta(hw);
	पूर्ण
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "Cannot initialise firmware\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Turn radio off */
	rc = mwl8k_cmd_radio_disable(hw);
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "Cannot disable\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Clear MAC address */
	rc = mwl8k_cmd_set_mac_addr(hw, शून्य, "\x00\x00\x00\x00\x00\x00");
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "Cannot clear MAC address\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Configure Antennas */
	rc = mwl8k_cmd_rf_antenna(hw, MWL8K_RF_ANTENNA_RX, 0x3);
	अगर (rc)
		wiphy_warn(hw->wiphy, "failed to set # of RX antennas");
	rc = mwl8k_cmd_rf_antenna(hw, MWL8K_RF_ANTENNA_TX, 0x7);
	अगर (rc)
		wiphy_warn(hw->wiphy, "failed to set # of TX antennas");


	/* Disable पूर्णांकerrupts */
	ioग_लिखो32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	मुक्त_irq(priv->pdev->irq, hw);

	wiphy_info(hw->wiphy, "%s v%d, %pm, %s firmware %u.%u.%u.%u\n",
		   priv->device_info->part_name,
		   priv->hw_rev, hw->wiphy->perm_addr,
		   priv->ap_fw ? "AP" : "STA",
		   (priv->fw_rev >> 24) & 0xff, (priv->fw_rev >> 16) & 0xff,
		   (priv->fw_rev >> 8) & 0xff, priv->fw_rev & 0xff);

	वापस 0;

err_मुक्त_irq:
	ioग_लिखो32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	मुक्त_irq(priv->pdev->irq, hw);

err_मुक्त_queues:
	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_deinit(hw, i);
	mwl8k_rxq_deinit(hw, 0);

err_stop_firmware:
	mwl8k_hw_reset(priv);

	वापस rc;
पूर्ण

/*
 * invoke mwl8k_reload_firmware to change the firmware image after the device
 * has alपढ़ोy been रेजिस्टरed
 */
अटल पूर्णांक mwl8k_reload_firmware(काष्ठा ieee80211_hw *hw, अक्षर *fw_image)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा mwl8k_priv *priv = hw->priv;
	काष्ठा mwl8k_vअगर *vअगर, *पंचांगp_vअगर;

	mwl8k_stop(hw);
	mwl8k_rxq_deinit(hw, 0);

	/*
	 * All the existing पूर्णांकerfaces are re-added by the ieee80211_reconfig;
	 * which means driver should हटाओ existing पूर्णांकerfaces beक्रमe calling
	 * ieee80211_restart_hw
	 */
	अगर (priv->hw_restart_in_progress)
		list_क्रम_each_entry_safe(vअगर, पंचांगp_vअगर, &priv->vअगर_list, list)
			mwl8k_हटाओ_vअगर(priv, vअगर);

	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_deinit(hw, i);

	rc = mwl8k_init_firmware(hw, fw_image, false);
	अगर (rc)
		जाओ fail;

	rc = mwl8k_probe_hw(hw);
	अगर (rc)
		जाओ fail;

	अगर (priv->hw_restart_in_progress)
		वापस rc;

	rc = mwl8k_start(hw);
	अगर (rc)
		जाओ fail;

	rc = mwl8k_config(hw, ~0);
	अगर (rc)
		जाओ fail;

	क्रम (i = 0; i < MWL8K_TX_WMM_QUEUES; i++) अणु
		rc = mwl8k_conf_tx(hw, शून्य, i, &priv->wmm_params[i]);
		अगर (rc)
			जाओ fail;
	पूर्ण

	वापस rc;

fail:
	prपूर्णांकk(KERN_WARNING "mwl8k: Failed to reload firmware image.\n");
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ieee80211_अगरace_limit ap_अगर_limits[] = अणु
	अणु .max = 8,	.types = BIT(NL80211_IFTYPE_AP) पूर्ण,
	अणु .max = 1,	.types = BIT(NL80211_IFTYPE_STATION) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination ap_अगर_comb = अणु
	.limits = ap_अगर_limits,
	.n_limits = ARRAY_SIZE(ap_अगर_limits),
	.max_पूर्णांकerfaces = 8,
	.num_dअगरferent_channels = 1,
पूर्ण;


अटल पूर्णांक mwl8k_firmware_load_success(काष्ठा mwl8k_priv *priv)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	पूर्णांक i, rc;

	rc = mwl8k_load_firmware(hw);
	mwl8k_release_firmware(priv);
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "Cannot start firmware\n");
		वापस rc;
	पूर्ण

	/*
	 * Extra headroom is the size of the required DMA header
	 * minus the size of the smallest 802.11 frame (CTS frame).
	 */
	hw->extra_tx_headroom =
		माप(काष्ठा mwl8k_dma_data) - माप(काष्ठा ieee80211_cts);

	hw->extra_tx_headroom -= priv->ap_fw ? REDUCED_TX_HEADROOM : 0;

	hw->queues = MWL8K_TX_WMM_QUEUES;

	/* Set rssi values to dBm */
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);

	/*
	 * Ask mac80211 to not to trigger PS mode
	 * based on PM bit of incoming frames.
	 */
	अगर (priv->ap_fw)
		ieee80211_hw_set(hw, AP_LINK_PS);

	hw->vअगर_data_size = माप(काष्ठा mwl8k_vअगर);
	hw->sta_data_size = माप(काष्ठा mwl8k_sta);

	priv->macids_used = 0;
	INIT_LIST_HEAD(&priv->vअगर_list);

	/* Set शेष radio state and preamble */
	priv->radio_on = false;
	priv->radio_लघु_preamble = false;

	/* Finalize join worker */
	INIT_WORK(&priv->finalize_join_worker, mwl8k_finalize_join_worker);
	/* Handle watchकरोg ba events */
	INIT_WORK(&priv->watchकरोg_ba_handle, mwl8k_watchकरोg_ba_events);
	/* To reload the firmware अगर it crashes */
	INIT_WORK(&priv->fw_reload, mwl8k_hw_restart_work);

	/* TX reclaim and RX tasklets.  */
	tasklet_setup(&priv->poll_tx_task, mwl8k_tx_poll);
	tasklet_disable(&priv->poll_tx_task);
	tasklet_setup(&priv->poll_rx_task, mwl8k_rx_poll);
	tasklet_disable(&priv->poll_rx_task);

	/* Power management cookie */
	priv->cookie = dma_alloc_coherent(&priv->pdev->dev, 4,
					  &priv->cookie_dma, GFP_KERNEL);
	अगर (priv->cookie == शून्य)
		वापस -ENOMEM;

	mutex_init(&priv->fw_mutex);
	priv->fw_mutex_owner = शून्य;
	priv->fw_mutex_depth = 0;
	priv->hostcmd_रुको = शून्य;

	spin_lock_init(&priv->tx_lock);

	spin_lock_init(&priv->stream_lock);

	priv->tx_रुको = शून्य;

	rc = mwl8k_probe_hw(hw);
	अगर (rc)
		जाओ err_मुक्त_cookie;

	hw->wiphy->पूर्णांकerface_modes = 0;

	अगर (priv->ap_macids_supported || priv->device_info->fw_image_ap) अणु
		hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_AP);
		hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_STATION);
		hw->wiphy->अगरace_combinations = &ap_अगर_comb;
		hw->wiphy->n_अगरace_combinations = 1;
	पूर्ण

	अगर (priv->sta_macids_supported || priv->device_info->fw_image_sta)
		hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_STATION);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	rc = ieee80211_रेजिस्टर_hw(hw);
	अगर (rc) अणु
		wiphy_err(hw->wiphy, "Cannot register device\n");
		जाओ err_unprobe_hw;
	पूर्ण

	वापस 0;

err_unprobe_hw:
	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_deinit(hw, i);
	mwl8k_rxq_deinit(hw, 0);

err_मुक्त_cookie:
	अगर (priv->cookie != शून्य)
		dma_मुक्त_coherent(&priv->pdev->dev, 4, priv->cookie,
				  priv->cookie_dma);

	वापस rc;
पूर्ण
अटल पूर्णांक mwl8k_probe(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	अटल पूर्णांक prपूर्णांकed_version;
	काष्ठा ieee80211_hw *hw;
	काष्ठा mwl8k_priv *priv;
	काष्ठा mwl8k_device_info *di;
	पूर्णांक rc;

	अगर (!prपूर्णांकed_version) अणु
		prपूर्णांकk(KERN_INFO "%s version %s\n", MWL8K_DESC, MWL8K_VERSION);
		prपूर्णांकed_version = 1;
	पूर्ण


	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot enable new PCI device\n",
		       MWL8K_NAME);
		वापस rc;
	पूर्ण

	rc = pci_request_regions(pdev, MWL8K_NAME);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot obtain PCI resources\n",
		       MWL8K_NAME);
		जाओ err_disable_device;
	पूर्ण

	pci_set_master(pdev);


	hw = ieee80211_alloc_hw(माप(*priv), &mwl8k_ops);
	अगर (hw == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: ieee80211 alloc failed\n", MWL8K_NAME);
		rc = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण

	SET_IEEE80211_DEV(hw, &pdev->dev);
	pci_set_drvdata(pdev, hw);

	priv = hw->priv;
	priv->hw = hw;
	priv->pdev = pdev;
	priv->device_info = &mwl8k_info_tbl[id->driver_data];

	अगर (id->driver_data == MWL8764)
		priv->is_8764 = true;

	priv->sram = pci_iomap(pdev, 0, 0x10000);
	अगर (priv->sram == शून्य) अणु
		wiphy_err(hw->wiphy, "Cannot map device SRAM\n");
		rc = -EIO;
		जाओ err_iounmap;
	पूर्ण

	/*
	 * If BAR0 is a 32 bit BAR, the रेजिस्टर BAR will be BAR1.
	 * If BAR0 is a 64 bit BAR, the रेजिस्टर BAR will be BAR2.
	 */
	priv->regs = pci_iomap(pdev, 1, 0x10000);
	अगर (priv->regs == शून्य) अणु
		priv->regs = pci_iomap(pdev, 2, 0x10000);
		अगर (priv->regs == शून्य) अणु
			wiphy_err(hw->wiphy, "Cannot map device registers\n");
			rc = -EIO;
			जाओ err_iounmap;
		पूर्ण
	पूर्ण

	/*
	 * Choose the initial fw image depending on user input.  If a second
	 * image is available, make it the alternative image that will be
	 * loaded अगर the first one fails.
	 */
	init_completion(&priv->firmware_loading_complete);
	di = priv->device_info;
	अगर (ap_mode_शेष && di->fw_image_ap) अणु
		priv->fw_pref = di->fw_image_ap;
		priv->fw_alt = di->fw_image_sta;
	पूर्ण अन्यथा अगर (!ap_mode_शेष && di->fw_image_sta) अणु
		priv->fw_pref = di->fw_image_sta;
		priv->fw_alt = di->fw_image_ap;
	पूर्ण अन्यथा अगर (ap_mode_शेष && !di->fw_image_ap && di->fw_image_sta) अणु
		prपूर्णांकk(KERN_WARNING "AP fw is unavailable.  Using STA fw.");
		priv->fw_pref = di->fw_image_sta;
	पूर्ण अन्यथा अगर (!ap_mode_शेष && !di->fw_image_sta && di->fw_image_ap) अणु
		prपूर्णांकk(KERN_WARNING "STA fw is unavailable.  Using AP fw.");
		priv->fw_pref = di->fw_image_ap;
	पूर्ण
	rc = mwl8k_init_firmware(hw, priv->fw_pref, true);
	अगर (rc)
		जाओ err_stop_firmware;

	priv->hw_restart_in_progress = false;

	priv->running_bsses = 0;

	वापस rc;

err_stop_firmware:
	mwl8k_hw_reset(priv);

err_iounmap:
	अगर (priv->regs != शून्य)
		pci_iounmap(pdev, priv->regs);

	अगर (priv->sram != शून्य)
		pci_iounmap(pdev, priv->sram);

	ieee80211_मुक्त_hw(hw);

err_मुक्त_reg:
	pci_release_regions(pdev);

err_disable_device:
	pci_disable_device(pdev);

	वापस rc;
पूर्ण

अटल व्योम mwl8k_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा mwl8k_priv *priv;
	पूर्णांक i;

	अगर (hw == शून्य)
		वापस;
	priv = hw->priv;

	रुको_क्रम_completion(&priv->firmware_loading_complete);

	अगर (priv->fw_state == FW_STATE_ERROR) अणु
		mwl8k_hw_reset(priv);
		जाओ unmap;
	पूर्ण

	ieee80211_stop_queues(hw);

	ieee80211_unरेजिस्टर_hw(hw);

	/* Remove TX reclaim and RX tasklets.  */
	tasklet_समाप्त(&priv->poll_tx_task);
	tasklet_समाप्त(&priv->poll_rx_task);

	/* Stop hardware */
	mwl8k_hw_reset(priv);

	/* Return all skbs to mac80211 */
	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_reclaim(hw, i, पूर्णांक_उच्च, 1);

	क्रम (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_deinit(hw, i);

	mwl8k_rxq_deinit(hw, 0);

	dma_मुक्त_coherent(&priv->pdev->dev, 4, priv->cookie, priv->cookie_dma);

unmap:
	pci_iounmap(pdev, priv->regs);
	pci_iounmap(pdev, priv->sram);
	ieee80211_मुक्त_hw(hw);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver mwl8k_driver = अणु
	.name		= MWL8K_NAME,
	.id_table	= mwl8k_pci_id_table,
	.probe		= mwl8k_probe,
	.हटाओ		= mwl8k_हटाओ,
पूर्ण;

module_pci_driver(mwl8k_driver);

MODULE_DESCRIPTION(MWL8K_DESC);
MODULE_VERSION(MWL8K_VERSION);
MODULE_AUTHOR("Lennert Buytenhek <buytenh@marvell.com>");
MODULE_LICENSE("GPL");
