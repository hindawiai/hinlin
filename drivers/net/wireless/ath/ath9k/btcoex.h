<शैली गुरु>
/*
 * Copyright (c) 2009-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित BTCOEX_H
#घोषणा BTCOEX_H

#समावेश "hw.h"

#घोषणा ATH_WLANACTIVE_GPIO_9280     5
#घोषणा ATH_BTACTIVE_GPIO_9280       6
#घोषणा ATH_BTPRIORITY_GPIO_9285     7

#घोषणा ATH_WLANACTIVE_GPIO_9300     5
#घोषणा ATH_BTACTIVE_GPIO_9300       4
#घोषणा ATH_BTPRIORITY_GPIO_9300     8

#घोषणा ATH_BTCOEX_DEF_BT_PERIOD  45
#घोषणा ATH_BTCOEX_DEF_DUTY_CYCLE 55
#घोषणा ATH_BTCOEX_BTSCAN_DUTY_CYCLE 90
#घोषणा ATH_BTCOEX_BMISS_THRESH   50

#घोषणा ATH_BT_PRIORITY_TIME_THRESHOLD 1000 /* ms */
#घोषणा ATH_BT_CNT_THRESHOLD	       3
#घोषणा ATH_BT_CNT_SCAN_THRESHOLD      15

#घोषणा ATH_BTCOEX_RX_WAIT_TIME       100
#घोषणा ATH_BTCOEX_STOMP_FTP_THRESH   5

#घोषणा ATH_BTCOEX_HT20_MAX_TXPOWER   0x14
#घोषणा ATH_BTCOEX_HT40_MAX_TXPOWER   0x10

#घोषणा AR9300_NUM_BT_WEIGHTS   4
#घोषणा AR9300_NUM_WLAN_WEIGHTS 4

#घोषणा ATH_AIC_MAX_BT_CHANNEL  79

/* Defines the BT AR_BT_COEX_WGHT used */
क्रमागत ath_stomp_type अणु
	ATH_BTCOEX_STOMP_ALL,
	ATH_BTCOEX_STOMP_LOW,
	ATH_BTCOEX_STOMP_NONE,
	ATH_BTCOEX_STOMP_LOW_FTP,
	ATH_BTCOEX_STOMP_AUDIO,
	ATH_BTCOEX_STOMP_MAX
पूर्ण;

क्रमागत ath_btcoex_scheme अणु
	ATH_BTCOEX_CFG_NONE,
	ATH_BTCOEX_CFG_2WIRE,
	ATH_BTCOEX_CFG_3WIRE,
	ATH_BTCOEX_CFG_MCI,
पूर्ण;

काष्ठा ath9k_hw_mci अणु
	u32 raw_पूर्णांकr;
	u32 rx_msg_पूर्णांकr;
	u32 cont_status;
	u32 gpm_addr;
	u32 gpm_len;
	u32 gpm_idx;
	u32 sched_addr;
	u32 wlan_channels[4];
	u32 wlan_cal_seq;
	u32 wlan_cal_करोne;
	u32 config;
	u8 *gpm_buf;
	bool पढ़ोy;
	bool update_2g5g;
	bool is_2g;
	bool query_bt;
	bool unhalt_bt_gpm; /* need send UNHALT */
	bool halted_bt_gpm; /* HALT sent */
	bool need_flush_btinfo;
	bool bt_version_known;
	bool wlan_channels_update;
	u8 wlan_ver_major;
	u8 wlan_ver_minor;
	u8 bt_ver_major;
	u8 bt_ver_minor;
	u8 bt_state;
	u8 stomp_ftp;
	bool concur_tx;
	u32 last_recovery;
पूर्ण;

काष्ठा ath9k_hw_aic अणु
	bool aic_enabled;
	u8 aic_cal_state;
	u8 aic_caled_chan;
	u32 aic_sram[ATH_AIC_MAX_BT_CHANNEL];
	u32 aic_cal_start_समय;
पूर्ण;

काष्ठा ath_btcoex_hw अणु
	क्रमागत ath_btcoex_scheme scheme;
	काष्ठा ath9k_hw_mci mci;
	काष्ठा ath9k_hw_aic aic;
	bool enabled;
	u8 wlanactive_gpio;
	u8 btactive_gpio;
	u8 btpriority_gpio;
	u32 bt_coex_mode; 	/* Register setting क्रम AR_BT_COEX_MODE */
	u32 bt_coex_weights; 	/* Register setting क्रम AR_BT_COEX_WEIGHT */
	u32 bt_coex_mode2; 	/* Register setting क्रम AR_BT_COEX_MODE2 */
	u32 bt_coex_mode3;	/* Register setting क्रम AR_BT_COEX_MODE3 */
	u32 bt_weight[AR9300_NUM_BT_WEIGHTS];
	u32 wlan_weight[AR9300_NUM_WLAN_WEIGHTS];
	u8 tx_prio[ATH_BTCOEX_STOMP_MAX];
पूर्ण;

व्योम ath9k_hw_btcoex_init_scheme(काष्ठा ath_hw *ah);
व्योम ath9k_hw_btcoex_init_2wire(काष्ठा ath_hw *ah);
व्योम ath9k_hw_btcoex_init_3wire(काष्ठा ath_hw *ah);
व्योम ath9k_hw_btcoex_deinit(काष्ठा ath_hw *ah);
व्योम ath9k_hw_btcoex_init_mci(काष्ठा ath_hw *ah);
व्योम ath9k_hw_init_btcoex_hw(काष्ठा ath_hw *ah, पूर्णांक qnum);
व्योम ath9k_hw_btcoex_set_weight(काष्ठा ath_hw *ah,
				u32 bt_weight,
				u32 wlan_weight,
				क्रमागत ath_stomp_type stomp_type);
व्योम ath9k_hw_btcoex_disable(काष्ठा ath_hw *ah);
व्योम ath9k_hw_btcoex_bt_stomp(काष्ठा ath_hw *ah,
			      क्रमागत ath_stomp_type stomp_type);
व्योम ath9k_hw_btcoex_set_concur_txprio(काष्ठा ath_hw *ah, u8 *stomp_txprio);

#पूर्ण_अगर
