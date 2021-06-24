<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Shared defines क्रम all mac80211 Prism54 code
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 *
 * Based on the islsm (sofपंचांगac prism54) driver, which is:
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */

#अगर_अघोषित P54_H
#घोषणा P54_H

#अगर_घोषित CONFIG_P54_LEDS
#समावेश <linux/leds.h>
#पूर्ण_अगर /* CONFIG_P54_LEDS */

#घोषणा ISL38XX_DEV_FIRMWARE_ADDR 0x20000

#घोषणा BR_CODE_MIN			0x80000000
#घोषणा BR_CODE_COMPONENT_ID		0x80000001
#घोषणा BR_CODE_COMPONENT_VERSION	0x80000002
#घोषणा BR_CODE_DEPENDENT_IF		0x80000003
#घोषणा BR_CODE_EXPOSED_IF		0x80000004
#घोषणा BR_CODE_DESCR			0x80000101
#घोषणा BR_CODE_MAX			0x8FFFFFFF
#घोषणा BR_CODE_END_OF_BRA		0xFF0000FF
#घोषणा LEGACY_BR_CODE_END_OF_BRA	0xFFFFFFFF

काष्ठा bootrec अणु
	__le32 code;
	__le32 len;
	u32 data[10];
पूर्ण __packed;

/* Interface role definitions */
#घोषणा BR_INTERFACE_ROLE_SERVER	0x0000
#घोषणा BR_INTERFACE_ROLE_CLIENT	0x8000

#घोषणा BR_DESC_PRIV_CAP_WEP		BIT(0)
#घोषणा BR_DESC_PRIV_CAP_TKIP		BIT(1)
#घोषणा BR_DESC_PRIV_CAP_MICHAEL	BIT(2)
#घोषणा BR_DESC_PRIV_CAP_CCX_CP		BIT(3)
#घोषणा BR_DESC_PRIV_CAP_CCX_MIC	BIT(4)
#घोषणा BR_DESC_PRIV_CAP_AESCCMP	BIT(5)

काष्ठा bootrec_desc अणु
	__le16 modes;
	__le16 flags;
	__le32 rx_start;
	__le32 rx_end;
	u8 headroom;
	u8 tailroom;
	u8 tx_queues;
	u8 tx_depth;
	u8 privacy_caps;
	u8 rx_keycache_size;
	u8 समय_size;
	u8 padding;
	u8 rates[16];
	u8 padding2[4];
	__le16 rx_mtu;
पूर्ण __packed;

#घोषणा FW_FMAC 0x464d4143
#घोषणा FW_LM86 0x4c4d3836
#घोषणा FW_LM87 0x4c4d3837
#घोषणा FW_LM20 0x4c4d3230

काष्ठा bootrec_comp_id अणु
	__le32 fw_variant;
पूर्ण __packed;

काष्ठा bootrec_comp_ver अणु
	अक्षर fw_version[24];
पूर्ण __packed;

काष्ठा bootrec_end अणु
	__le16 crc;
	u8 padding[2];
	u8 md5[16];
पूर्ण __packed;

/* provide 16 bytes क्रम the transport back-end */
#घोषणा P54_TX_INFO_DATA_SIZE		16

/* stored in ieee80211_tx_info's rate_driver_data */
काष्ठा p54_tx_info अणु
	u32 start_addr;
	u32 end_addr;
	जोड़ अणु
		व्योम *data[P54_TX_INFO_DATA_SIZE / माप(व्योम *)];
		काष्ठा अणु
			u32 extra_len;
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा P54_MAX_CTRL_FRAME_LEN		0x1000

#घोषणा P54_SET_QUEUE(queue, ai_fs, cw_min, cw_max, _txop)	\
करो अणु								\
	queue.aअगरs = cpu_to_le16(ai_fs);			\
	queue.cwmin = cpu_to_le16(cw_min);			\
	queue.cwmax = cpu_to_le16(cw_max);			\
	queue.txop = cpu_to_le16(_txop);			\
पूर्ण जबतक (0)

काष्ठा p54_edcf_queue_param अणु
	__le16 aअगरs;
	__le16 cwmin;
	__le16 cwmax;
	__le16 txop;
पूर्ण __packed;

काष्ठा p54_rssi_db_entry अणु
	u16 freq;
	s16 mul;
	s16 add;
	s16 दीर्घbow_unkn;
	s16 दीर्घbow_unk2;
पूर्ण;

काष्ठा p54_cal_database अणु
	माप_प्रकार entries;
	माप_प्रकार entry_size;
	माप_प्रकार offset;
	माप_प्रकार len;
	u8 data[];
पूर्ण;

#घोषणा EEPROM_READBACK_LEN 0x3fc

क्रमागत fw_state अणु
	FW_STATE_OFF,
	FW_STATE_BOOTING,
	FW_STATE_READY,
	FW_STATE_RESET,
	FW_STATE_RESETTING,
पूर्ण;

#अगर_घोषित CONFIG_P54_LEDS

#घोषणा P54_LED_MAX_NAME_LEN 31

काष्ठा p54_led_dev अणु
	काष्ठा ieee80211_hw *hw_dev;
	काष्ठा led_classdev led_dev;
	अक्षर name[P54_LED_MAX_NAME_LEN + 1];

	अचिन्हित पूर्णांक toggled;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक रेजिस्टरed;
पूर्ण;

#पूर्ण_अगर /* CONFIG_P54_LEDS */

काष्ठा p54_tx_queue_stats अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा p54_common अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_vअगर *vअगर;
	व्योम (*tx)(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb);
	पूर्णांक (*खोलो)(काष्ठा ieee80211_hw *dev);
	व्योम (*stop)(काष्ठा ieee80211_hw *dev);
	काष्ठा sk_buff_head tx_pending;
	काष्ठा sk_buff_head tx_queue;
	काष्ठा mutex conf_mutex;
	bool रेजिस्टरed;

	/* memory management (as seen by the firmware) */
	u32 rx_start;
	u32 rx_end;
	u16 rx_mtu;
	u8 headroom;
	u8 tailroom;

	/* firmware/hardware info */
	अचिन्हित पूर्णांक tx_hdr_len;
	अचिन्हित पूर्णांक fw_var;
	अचिन्हित पूर्णांक fw_पूर्णांकerface;
	u8 version;

	/* (e)DCF / QOS state */
	bool use_लघु_slot;
	spinlock_t tx_stats_lock;
	काष्ठा p54_tx_queue_stats tx_stats[8];
	काष्ठा p54_edcf_queue_param qos_params[8];

	/* Radio data */
	u16 rxhw;
	u8 rx_भागersity_mask;
	u8 tx_भागersity_mask;
	अचिन्हित पूर्णांक output_घातer;
	काष्ठा p54_rssi_db_entry *cur_rssi;
	काष्ठा ieee80211_channel *curchan;
	काष्ठा survey_info *survey;
	अचिन्हित पूर्णांक chan_num;
	काष्ठा completion stat_comp;
	bool update_stats;
	काष्ठा अणु
		अचिन्हित पूर्णांक बारtamp;
		अचिन्हित पूर्णांक cached_cca;
		अचिन्हित पूर्णांक cached_tx;
		अचिन्हित पूर्णांक cached_rssi;
		u64 active;
		u64 cca;
		u64 tx;
		u64 rssi;
	पूर्ण survey_raw;

	पूर्णांक noise;
	/* calibration, output घातer limit and rssi<->dBm conversation data */
	काष्ठा pda_iq_स्वतःcal_entry *iq_स्वतःcal;
	अचिन्हित पूर्णांक iq_स्वतःcal_len;
	काष्ठा p54_cal_database *curve_data;
	काष्ठा p54_cal_database *output_limit;
	काष्ठा p54_cal_database *rssi_db;
	काष्ठा ieee80211_supported_band *band_table[NUM_NL80211_BANDS];

	/* BBP/MAC state */
	u8 mac_addr[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	u8 mc_maclist[4][ETH_ALEN];
	u16 wakeup_समयr;
	अचिन्हित पूर्णांक filter_flags;
	पूर्णांक mc_maclist_num;
	पूर्णांक mode;
	u32 tsf_low32, tsf_high32;
	u32 basic_rate_mask;
	u16 aid;
	u8 coverage_class;
	bool phy_idle;
	bool phy_ps;
	bool घातersave_override;
	__le32 beacon_req_id;
	काष्ठा completion beacon_comp;

	/* cryptographic engine inक्रमmation */
	u8 privacy_caps;
	u8 rx_keycache_size;
	अचिन्हित दीर्घ *used_rxkeys;

	/* LED management */
#अगर_घोषित CONFIG_P54_LEDS
	काष्ठा p54_led_dev leds[4];
	काष्ठा delayed_work led_work;
#पूर्ण_अगर /* CONFIG_P54_LEDS */
	u16 softled_state;		/* bit field of glowing LEDs */

	/* statistics */
	काष्ठा ieee80211_low_level_stats stats;
	काष्ठा delayed_work work;

	/* eeprom handling */
	व्योम *eeprom;
	काष्ठा completion eeprom_comp;
	काष्ठा mutex eeprom_mutex;
पूर्ण;

/* पूर्णांकerfaces क्रम the drivers */
पूर्णांक p54_rx(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb);
व्योम p54_मुक्त_skb(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb);
पूर्णांक p54_parse_firmware(काष्ठा ieee80211_hw *dev, स्थिर काष्ठा firmware *fw);
पूर्णांक p54_parse_eeprom(काष्ठा ieee80211_hw *dev, व्योम *eeprom, पूर्णांक len);
पूर्णांक p54_पढ़ो_eeprom(काष्ठा ieee80211_hw *dev);

काष्ठा ieee80211_hw *p54_init_common(माप_प्रकार priv_data_len);
पूर्णांक p54_रेजिस्टर_common(काष्ठा ieee80211_hw *dev, काष्ठा device *pdev);
व्योम p54_मुक्त_common(काष्ठा ieee80211_hw *dev);

व्योम p54_unरेजिस्टर_common(काष्ठा ieee80211_hw *dev);

#पूर्ण_अगर /* P54_H */
