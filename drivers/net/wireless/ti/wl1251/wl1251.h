<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008-2009 Nokia Corporation
 */

#अगर_अघोषित __WL1251_H__
#घोषणा __WL1251_H__

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <net/mac80211.h>

#घोषणा DRIVER_NAME "wl1251"
#घोषणा DRIVER_PREFIX DRIVER_NAME ": "

क्रमागत अणु
	DEBUG_NONE	= 0,
	DEBUG_IRQ	= BIT(0),
	DEBUG_SPI	= BIT(1),
	DEBUG_BOOT	= BIT(2),
	DEBUG_MAILBOX	= BIT(3),
	DEBUG_NETLINK	= BIT(4),
	DEBUG_EVENT	= BIT(5),
	DEBUG_TX	= BIT(6),
	DEBUG_RX	= BIT(7),
	DEBUG_SCAN	= BIT(8),
	DEBUG_CRYPT	= BIT(9),
	DEBUG_PSM	= BIT(10),
	DEBUG_MAC80211	= BIT(11),
	DEBUG_CMD	= BIT(12),
	DEBUG_ACX	= BIT(13),
	DEBUG_ALL	= ~0,
पूर्ण;

#घोषणा DEBUG_LEVEL (DEBUG_NONE)

#घोषणा DEBUG_DUMP_LIMIT 1024

#घोषणा wl1251_error(fmt, arg...) \
	prपूर्णांकk(KERN_ERR DRIVER_PREFIX "ERROR " fmt "\n", ##arg)

#घोषणा wl1251_warning(fmt, arg...) \
	prपूर्णांकk(KERN_WARNING DRIVER_PREFIX "WARNING " fmt "\n", ##arg)

#घोषणा wl1251_notice(fmt, arg...) \
	prपूर्णांकk(KERN_INFO DRIVER_PREFIX fmt "\n", ##arg)

#घोषणा wl1251_info(fmt, arg...) \
	prपूर्णांकk(KERN_DEBUG DRIVER_PREFIX fmt "\n", ##arg)

#घोषणा wl1251_debug(level, fmt, arg...) \
	करो अणु \
		अगर (level & DEBUG_LEVEL) \
			prपूर्णांकk(KERN_DEBUG DRIVER_PREFIX fmt "\n", ##arg); \
	पूर्ण जबतक (0)

#घोषणा wl1251_dump(level, prefix, buf, len)	\
	करो अणु \
		अगर (level & DEBUG_LEVEL) \
			prपूर्णांक_hex_dump(KERN_DEBUG, DRIVER_PREFIX prefix, \
				       DUMP_PREFIX_OFFSET, 16, 1,	\
				       buf,				\
				       min_t(माप_प्रकार, len, DEBUG_DUMP_LIMIT), \
				       0);				\
	पूर्ण जबतक (0)

#घोषणा wl1251_dump_ascii(level, prefix, buf, len)	\
	करो अणु \
		अगर (level & DEBUG_LEVEL) \
			prपूर्णांक_hex_dump(KERN_DEBUG, DRIVER_PREFIX prefix, \
				       DUMP_PREFIX_OFFSET, 16, 1,	\
				       buf,				\
				       min_t(माप_प्रकार, len, DEBUG_DUMP_LIMIT), \
				       true);				\
	पूर्ण जबतक (0)

#घोषणा WL1251_DEFAULT_RX_CONFIG (CFG_UNI_FILTER_EN |	\
				  CFG_MC_FILTER_EN |	\
				  CFG_BSSID_FILTER_EN)

#घोषणा WL1251_DEFAULT_RX_FILTER (CFG_RX_PRSP_EN |  \
				  CFG_RX_MGMT_EN |  \
				  CFG_RX_DATA_EN |  \
				  CFG_RX_CTL_EN |   \
				  CFG_RX_BCN_EN |   \
				  CFG_RX_AUTH_EN |  \
				  CFG_RX_ASSOC_EN)

#घोषणा WL1251_BUSY_WORD_LEN 8

काष्ठा boot_attr अणु
	u32 radio_type;
	u8 mac_घड़ी;
	u8 arm_घड़ी;
	पूर्णांक firmware_debug;
	u32 minor;
	u32 major;
	u32 bugfix;
पूर्ण;

क्रमागत wl1251_state अणु
	WL1251_STATE_OFF,
	WL1251_STATE_ON,
	WL1251_STATE_PLT,
पूर्ण;

क्रमागत wl1251_partition_type अणु
	PART_DOWN,
	PART_WORK,
	PART_DRPW,

	PART_TABLE_LEN
पूर्ण;

क्रमागत wl1251_station_mode अणु
	STATION_ACTIVE_MODE,
	STATION_POWER_SAVE_MODE,
	STATION_IDLE,
पूर्ण;

काष्ठा wl1251_partition अणु
	u32 size;
	u32 start;
पूर्ण;

काष्ठा wl1251_partition_set अणु
	काष्ठा wl1251_partition mem;
	काष्ठा wl1251_partition reg;
पूर्ण;

काष्ठा wl1251;

काष्ठा wl1251_stats अणु
	काष्ठा acx_statistics *fw_stats;
	अचिन्हित दीर्घ fw_stats_update;

	अचिन्हित पूर्णांक retry_count;
	अचिन्हित पूर्णांक excessive_retries;
पूर्ण;

काष्ठा wl1251_debugfs अणु
	काष्ठा dentry *rootdir;
	काष्ठा dentry *fw_statistics;

	काष्ठा dentry *tx_पूर्णांकernal_desc_overflow;

	काष्ठा dentry *rx_out_of_mem;
	काष्ठा dentry *rx_hdr_overflow;
	काष्ठा dentry *rx_hw_stuck;
	काष्ठा dentry *rx_dropped;
	काष्ठा dentry *rx_fcs_err;
	काष्ठा dentry *rx_xfr_hपूर्णांक_trig;
	काष्ठा dentry *rx_path_reset;
	काष्ठा dentry *rx_reset_counter;

	काष्ठा dentry *dma_rx_requested;
	काष्ठा dentry *dma_rx_errors;
	काष्ठा dentry *dma_tx_requested;
	काष्ठा dentry *dma_tx_errors;

	काष्ठा dentry *isr_cmd_cmplt;
	काष्ठा dentry *isr_fiqs;
	काष्ठा dentry *isr_rx_headers;
	काष्ठा dentry *isr_rx_mem_overflow;
	काष्ठा dentry *isr_rx_rdys;
	काष्ठा dentry *isr_irqs;
	काष्ठा dentry *isr_tx_procs;
	काष्ठा dentry *isr_decrypt_करोne;
	काष्ठा dentry *isr_dma0_करोne;
	काष्ठा dentry *isr_dma1_करोne;
	काष्ठा dentry *isr_tx_exch_complete;
	काष्ठा dentry *isr_commands;
	काष्ठा dentry *isr_rx_procs;
	काष्ठा dentry *isr_hw_pm_mode_changes;
	काष्ठा dentry *isr_host_acknowledges;
	काष्ठा dentry *isr_pci_pm;
	काष्ठा dentry *isr_wakeups;
	काष्ठा dentry *isr_low_rssi;

	काष्ठा dentry *wep_addr_key_count;
	काष्ठा dentry *wep_शेष_key_count;
	/* skipping wep.reserved */
	काष्ठा dentry *wep_key_not_found;
	काष्ठा dentry *wep_decrypt_fail;
	काष्ठा dentry *wep_packets;
	काष्ठा dentry *wep_पूर्णांकerrupt;

	काष्ठा dentry *pwr_ps_enter;
	काष्ठा dentry *pwr_elp_enter;
	काष्ठा dentry *pwr_missing_bcns;
	काष्ठा dentry *pwr_wake_on_host;
	काष्ठा dentry *pwr_wake_on_समयr_exp;
	काष्ठा dentry *pwr_tx_with_ps;
	काष्ठा dentry *pwr_tx_without_ps;
	काष्ठा dentry *pwr_rcvd_beacons;
	काष्ठा dentry *pwr_घातer_save_off;
	काष्ठा dentry *pwr_enable_ps;
	काष्ठा dentry *pwr_disable_ps;
	काष्ठा dentry *pwr_fix_tsf_ps;
	/* skipping cont_miss_bcns_spपढ़ो क्रम now */
	काष्ठा dentry *pwr_rcvd_awake_beacons;

	काष्ठा dentry *mic_rx_pkts;
	काष्ठा dentry *mic_calc_failure;

	काष्ठा dentry *aes_encrypt_fail;
	काष्ठा dentry *aes_decrypt_fail;
	काष्ठा dentry *aes_encrypt_packets;
	काष्ठा dentry *aes_decrypt_packets;
	काष्ठा dentry *aes_encrypt_पूर्णांकerrupt;
	काष्ठा dentry *aes_decrypt_पूर्णांकerrupt;

	काष्ठा dentry *event_heart_beat;
	काष्ठा dentry *event_calibration;
	काष्ठा dentry *event_rx_mismatch;
	काष्ठा dentry *event_rx_mem_empty;
	काष्ठा dentry *event_rx_pool;
	काष्ठा dentry *event_oom_late;
	काष्ठा dentry *event_phy_transmit_error;
	काष्ठा dentry *event_tx_stuck;

	काष्ठा dentry *ps_pspoll_समयouts;
	काष्ठा dentry *ps_upsd_समयouts;
	काष्ठा dentry *ps_upsd_max_spसमय;
	काष्ठा dentry *ps_upsd_max_apturn;
	काष्ठा dentry *ps_pspoll_max_apturn;
	काष्ठा dentry *ps_pspoll_utilization;
	काष्ठा dentry *ps_upsd_utilization;

	काष्ठा dentry *rxpipe_rx_prep_beacon_drop;
	काष्ठा dentry *rxpipe_descr_host_पूर्णांक_trig_rx_data;
	काष्ठा dentry *rxpipe_beacon_buffer_thres_host_पूर्णांक_trig_rx_data;
	काष्ठा dentry *rxpipe_missed_beacon_host_पूर्णांक_trig_rx_data;
	काष्ठा dentry *rxpipe_tx_xfr_host_पूर्णांक_trig_rx_data;

	काष्ठा dentry *tx_queue_len;
	काष्ठा dentry *tx_queue_status;

	काष्ठा dentry *retry_count;
	काष्ठा dentry *excessive_retries;
पूर्ण;

काष्ठा wl1251_अगर_operations अणु
	व्योम (*पढ़ो)(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf, माप_प्रकार len);
	व्योम (*ग_लिखो)(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf, माप_प्रकार len);
	व्योम (*पढ़ो_elp)(काष्ठा wl1251 *wl, पूर्णांक addr, u32 *val);
	व्योम (*ग_लिखो_elp)(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val);
	पूर्णांक  (*घातer)(काष्ठा wl1251 *wl, bool enable);
	व्योम (*reset)(काष्ठा wl1251 *wl);
	व्योम (*enable_irq)(काष्ठा wl1251 *wl);
	व्योम (*disable_irq)(काष्ठा wl1251 *wl);
पूर्ण;

काष्ठा wl1251 अणु
	काष्ठा ieee80211_hw *hw;
	bool mac80211_रेजिस्टरed;

	व्योम *अगर_priv;
	स्थिर काष्ठा wl1251_अगर_operations *अगर_ops;

	पूर्णांक घातer_gpio;
	पूर्णांक irq;
	bool use_eeprom;

	काष्ठा regulator *vio;

	spinlock_t wl_lock;

	क्रमागत wl1251_state state;
	काष्ठा mutex mutex;

	पूर्णांक physical_mem_addr;
	पूर्णांक physical_reg_addr;
	पूर्णांक भव_mem_addr;
	पूर्णांक भव_reg_addr;

	पूर्णांक cmd_box_addr;
	पूर्णांक event_box_addr;
	काष्ठा boot_attr boot_attr;

	u8 *fw;
	माप_प्रकार fw_len;
	u8 *nvs;
	माप_प्रकार nvs_len;

	u8 bssid[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];
	u8 bss_type;
	u8 listen_पूर्णांक;
	पूर्णांक channel;
	bool monitor_present;
	bool joined;

	व्योम *target_mem_map;
	काष्ठा acx_data_path_params_resp *data_path;

	/* Number of TX packets transferred to the FW, modulo 16 */
	u32 data_in_count;

	/* Frames scheduled क्रम transmission, not handled yet */
	काष्ठा sk_buff_head tx_queue;
	bool tx_queue_stopped;

	काष्ठा work_काष्ठा tx_work;

	/* Pending TX frames */
	काष्ठा sk_buff *tx_frames[16];

	/*
	 * Index poपूर्णांकing to the next TX complete entry
	 * in the cyclic XT complete array we get from
	 * the FW.
	 */
	u32 next_tx_complete;

	/* FW Rx counter */
	u32 rx_counter;

	/* Rx frames handled */
	u32 rx_handled;

	/* Current द्विगुन buffer */
	u32 rx_current_buffer;
	u32 rx_last_id;

	/* The target पूर्णांकerrupt mask */
	u32 पूर्णांकr_mask;
	काष्ठा work_काष्ठा irq_work;

	/* The mbox event mask */
	u32 event_mask;

	/* Mailbox poपूर्णांकers */
	u32 mbox_ptr[2];

	/* Are we currently scanning */
	bool scanning;

	/* Default key (क्रम WEP) */
	u32 शेष_key;

	अचिन्हित पूर्णांक tx_mgmt_frm_rate;
	अचिन्हित पूर्णांक tx_mgmt_frm_mod;

	अचिन्हित पूर्णांक rx_config;
	अचिन्हित पूर्णांक rx_filter;

	/* is firmware in elp mode */
	bool elp;

	काष्ठा delayed_work elp_work;

	क्रमागत wl1251_station_mode station_mode;

	/* PSM mode requested */
	bool psm_requested;

	/* retry counter क्रम PSM entries */
	u8 psm_entry_retry;

	u16 beacon_पूर्णांक;
	u8 dtim_period;

	/* in dBm */
	पूर्णांक घातer_level;

	पूर्णांक rssi_thold;

	काष्ठा wl1251_stats stats;
	काष्ठा wl1251_debugfs debugfs;

	__le32 buffer_32;
	u32 buffer_cmd;
	u8 buffer_busyword[WL1251_BUSY_WORD_LEN];
	काष्ठा wl1251_rx_descriptor *rx_descriptor;

	काष्ठा ieee80211_vअगर *vअगर;

	u32 chip_id;
	अक्षर fw_ver[21];

	/* Most recently reported noise in dBm */
	s8 noise;
पूर्ण;

पूर्णांक wl1251_plt_start(काष्ठा wl1251 *wl);
पूर्णांक wl1251_plt_stop(काष्ठा wl1251 *wl);

काष्ठा ieee80211_hw *wl1251_alloc_hw(व्योम);
पूर्णांक wl1251_मुक्त_hw(काष्ठा wl1251 *wl);
पूर्णांक wl1251_init_ieee80211(काष्ठा wl1251 *wl);
व्योम wl1251_enable_पूर्णांकerrupts(काष्ठा wl1251 *wl);
व्योम wl1251_disable_पूर्णांकerrupts(काष्ठा wl1251 *wl);

#घोषणा DEFAULT_HW_GEN_MODULATION_TYPE    CCK_LONG /* Long Preamble */
#घोषणा DEFAULT_HW_GEN_TX_RATE          RATE_2MBPS
#घोषणा JOIN_TIMEOUT 5000 /* 5000 milliseconds to join */

#घोषणा WL1251_DEFAULT_POWER_LEVEL 20

#घोषणा WL1251_TX_QUEUE_LOW_WATERMARK  10
#घोषणा WL1251_TX_QUEUE_HIGH_WATERMARK 25

#घोषणा WL1251_DEFAULT_BEACON_INT 100
#घोषणा WL1251_DEFAULT_DTIM_PERIOD 1

#घोषणा WL1251_DEFAULT_CHANNEL 0

#घोषणा WL1251_DEFAULT_BET_CONSECUTIVE 10

#घोषणा CHIP_ID_1251_PG10	           (0x7010101)
#घोषणा CHIP_ID_1251_PG11	           (0x7020101)
#घोषणा CHIP_ID_1251_PG12	           (0x7030101)
#घोषणा CHIP_ID_1271_PG10	           (0x4030101)
#घोषणा CHIP_ID_1271_PG20	           (0x4030111)

#घोषणा WL1251_FW_NAME "ti-connectivity/wl1251-fw.bin"
#घोषणा WL1251_NVS_NAME "ti-connectivity/wl1251-nvs.bin"

#घोषणा WL1251_POWER_ON_SLEEP 10 /* in milliseconds */

#घोषणा WL1251_PART_DOWN_MEM_START	0x0
#घोषणा WL1251_PART_DOWN_MEM_SIZE	0x16800
#घोषणा WL1251_PART_DOWN_REG_START	REGISTERS_BASE
#घोषणा WL1251_PART_DOWN_REG_SIZE	REGISTERS_DOWN_SIZE

#घोषणा WL1251_PART_WORK_MEM_START	0x28000
#घोषणा WL1251_PART_WORK_MEM_SIZE	0x14000
#घोषणा WL1251_PART_WORK_REG_START	REGISTERS_BASE
#घोषणा WL1251_PART_WORK_REG_SIZE	REGISTERS_WORK_SIZE

#घोषणा WL1251_DEFAULT_LOW_RSSI_WEIGHT          10
#घोषणा WL1251_DEFAULT_LOW_RSSI_DEPTH           10

#पूर्ण_अगर
