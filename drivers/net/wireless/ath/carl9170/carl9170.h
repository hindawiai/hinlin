<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * Driver specअगरic definitions
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009, 2010, Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित __CARL9170_H
#घोषणा __CARL9170_H

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश <linux/usb.h>
#अगर_घोषित CONFIG_CARL9170_LEDS
#समावेश <linux/leds.h>
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */
#अगर_घोषित CONFIG_CARL9170_WPC
#समावेश <linux/input.h>
#पूर्ण_अगर /* CONFIG_CARL9170_WPC */
#समावेश "eeprom.h"
#समावेश "wlan.h"
#समावेश "hw.h"
#समावेश "fwdesc.h"
#समावेश "fwcmd.h"
#समावेश "../regd.h"

#अगर_घोषित CONFIG_CARL9170_DEBUGFS
#समावेश "debug.h"
#पूर्ण_अगर /* CONFIG_CARL9170_DEBUGFS */

#घोषणा CARL9170FW_NAME	"carl9170-1.fw"

#घोषणा PAYLOAD_MAX	(CARL9170_MAX_CMD_LEN / 4 - 1)

अटल अंतरभूत u8 ar9170_qmap(u8 idx)
अणु
	वापस 3 - idx; /* अणु 3, 2, 1, 0 पूर्ण */
पूर्ण

#घोषणा CARL9170_MAX_RX_BUFFER_SIZE		8192

क्रमागत carl9170_device_state अणु
	CARL9170_UNKNOWN_STATE,
	CARL9170_STOPPED,
	CARL9170_IDLE,
	CARL9170_STARTED,
पूर्ण;

#घोषणा WME_BA_BMP_SIZE			64
#घोषणा CARL9170_TX_USER_RATE_TRIES	3

#घोषणा TID_TO_WME_AC(_tid)				\
	((((_tid) == 0) || ((_tid) == 3)) ? IEEE80211_AC_BE :	\
	 (((_tid) == 1) || ((_tid) == 2)) ? IEEE80211_AC_BK :	\
	 (((_tid) == 4) || ((_tid) == 5)) ? IEEE80211_AC_VI :	\
	 IEEE80211_AC_VO)

#घोषणा SEQ_DIFF(_start, _seq) \
	(((_start) - (_seq)) & 0x0fff)
#घोषणा SEQ_PREV(_seq) \
	(((_seq) - 1) & 0x0fff)
#घोषणा SEQ_NEXT(_seq) \
	(((_seq) + 1) & 0x0fff)
#घोषणा BAW_WITHIN(_start, _bawsz, _seqno) \
	((((_seqno) - (_start)) & 0xfff) < (_bawsz))

क्रमागत carl9170_tid_state अणु
	CARL9170_TID_STATE_INVALID,
	CARL9170_TID_STATE_KILLED,
	CARL9170_TID_STATE_SHUTDOWN,
	CARL9170_TID_STATE_SUSPEND,
	CARL9170_TID_STATE_PROGRESS,
	CARL9170_TID_STATE_IDLE,
	CARL9170_TID_STATE_XMIT,
पूर्ण;

#घोषणा CARL9170_BAW_BITS (2 * WME_BA_BMP_SIZE)
#घोषणा CARL9170_BAW_SIZE (BITS_TO_LONGS(CARL9170_BAW_BITS))
#घोषणा CARL9170_BAW_LEN (DIV_ROUND_UP(CARL9170_BAW_BITS, BITS_PER_BYTE))

काष्ठा carl9170_sta_tid अणु
	/* must be the first entry! */
	काष्ठा list_head list;

	/* temporary list क्रम RCU unlink procedure */
	काष्ठा list_head पंचांगp_list;

	/* lock क्रम the following data काष्ठाures */
	spinlock_t lock;

	अचिन्हित पूर्णांक counter;
	क्रमागत carl9170_tid_state state;
	u8 tid;		/* TID number ( 0 - 15 ) */
	u16 max;	/* max. AMPDU size */

	u16 snx;	/* aरुकोing _next_ frame */
	u16 hsn;	/* highest _queued_ sequence */
	u16 bsn;	/* base of the tx/agg biपंचांगap */
	अचिन्हित दीर्घ biपंचांगap[CARL9170_BAW_SIZE];

	/* Preaggregation reorder queue */
	काष्ठा sk_buff_head queue;

	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_vअगर *vअगर;
पूर्ण;

#घोषणा CARL9170_QUEUE_TIMEOUT		256
#घोषणा CARL9170_BUMP_QUEUE		1000
#घोषणा CARL9170_TX_TIMEOUT		2500
#घोषणा CARL9170_JANITOR_DELAY		128
#घोषणा CARL9170_QUEUE_STUCK_TIMEOUT	5500
#घोषणा CARL9170_STAT_WORK		30000

#घोषणा CARL9170_NUM_TX_AGG_MAX		30

/*
 * Tradeoff between stability/latency and speed.
 *
 * AR9170_TXQ_DEPTH is devised by भागiding the amount of available
 * tx buffers with the size of a full ethernet frame + overhead.
 *
 * Naturally: The higher the limit, the faster the device CAN send.
 * However, even a slight over-commiपंचांगent at the wrong समय and the
 * hardware is करोomed to send all alपढ़ोy-queued frames at suboptimal
 * rates. This in turn leads to an enormous amount of unsuccessful
 * retries => Latency goes up, whereas the throughput goes करोwn. CRASH!
 */
#घोषणा CARL9170_NUM_TX_LIMIT_HARD	((AR9170_TXQ_DEPTH * 3) / 2)
#घोषणा CARL9170_NUM_TX_LIMIT_SOFT	(AR9170_TXQ_DEPTH)

काष्ठा carl9170_tx_queue_stats अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक len;
पूर्ण;

काष्ठा carl9170_vअगर अणु
	अचिन्हित पूर्णांक id;
	काष्ठा ieee80211_vअगर __rcu *vअगर;
पूर्ण;

काष्ठा carl9170_vअगर_info अणु
	काष्ठा list_head list;
	bool active;
	अचिन्हित पूर्णांक id;
	काष्ठा sk_buff *beacon;
	bool enable_beacon;
पूर्ण;

#घोषणा AR9170_NUM_RX_URBS	16
#घोषणा AR9170_NUM_RX_URBS_MUL	2
#घोषणा AR9170_NUM_TX_URBS	8
#घोषणा AR9170_NUM_RX_URBS_POOL (AR9170_NUM_RX_URBS_MUL * AR9170_NUM_RX_URBS)

क्रमागत carl9170_device_features अणु
	CARL9170_WPS_BUTTON		= BIT(0),
	CARL9170_ONE_LED		= BIT(1),
पूर्ण;

#अगर_घोषित CONFIG_CARL9170_LEDS
काष्ठा ar9170;

काष्ठा carl9170_led अणु
	काष्ठा ar9170 *ar;
	काष्ठा led_classdev l;
	अक्षर name[32];
	अचिन्हित पूर्णांक toggled;
	bool last_state;
	bool रेजिस्टरed;
पूर्ण;
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */

क्रमागत carl9170_restart_reasons अणु
	CARL9170_RR_NO_REASON = 0,
	CARL9170_RR_FATAL_FIRMWARE_ERROR,
	CARL9170_RR_TOO_MANY_FIRMWARE_ERRORS,
	CARL9170_RR_WATCHDOG,
	CARL9170_RR_STUCK_TX,
	CARL9170_RR_UNRESPONSIVE_DEVICE,
	CARL9170_RR_COMMAND_TIMEOUT,
	CARL9170_RR_TOO_MANY_PHY_ERRORS,
	CARL9170_RR_LOST_RSP,
	CARL9170_RR_INVALID_RSP,
	CARL9170_RR_USER_REQUEST,

	__CARL9170_RR_LAST,
पूर्ण;

क्रमागत carl9170_erp_modes अणु
	CARL9170_ERP_INVALID,
	CARL9170_ERP_AUTO,
	CARL9170_ERP_MAC80211,
	CARL9170_ERP_OFF,
	CARL9170_ERP_CTS,
	CARL9170_ERP_RTS,
	__CARL9170_ERP_NUM,
पूर्ण;

काष्ठा ar9170 अणु
	काष्ठा ath_common common;
	काष्ठा ieee80211_hw *hw;
	काष्ठा mutex mutex;
	क्रमागत carl9170_device_state state;
	spinlock_t state_lock;
	क्रमागत carl9170_restart_reasons last_reason;
	bool रेजिस्टरed;

	/* USB */
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_anchor rx_anch;
	काष्ठा usb_anchor rx_work;
	काष्ठा usb_anchor rx_pool;
	काष्ठा usb_anchor tx_रुको;
	काष्ठा usb_anchor tx_anch;
	काष्ठा usb_anchor tx_cmd;
	काष्ठा usb_anchor tx_err;
	काष्ठा tasklet_काष्ठा usb_tasklet;
	atomic_t tx_cmd_urbs;
	atomic_t tx_anch_urbs;
	atomic_t rx_anch_urbs;
	atomic_t rx_work_urbs;
	atomic_t rx_pool_urbs;
	kernel_uदीर्घ_t features;
	bool usb_ep_cmd_is_bulk;

	/* firmware settings */
	काष्ठा completion fw_load_रुको;
	काष्ठा completion fw_boot_रुको;
	काष्ठा अणु
		स्थिर काष्ठा carl9170fw_desc_head *desc;
		स्थिर काष्ठा firmware *fw;
		अचिन्हित पूर्णांक offset;
		अचिन्हित पूर्णांक address;
		अचिन्हित पूर्णांक cmd_bufs;
		अचिन्हित पूर्णांक api_version;
		अचिन्हित पूर्णांक vअगर_num;
		अचिन्हित पूर्णांक err_counter;
		अचिन्हित पूर्णांक bug_counter;
		u32 beacon_addr;
		अचिन्हित पूर्णांक beacon_max_len;
		bool rx_stream;
		bool tx_stream;
		bool rx_filter;
		bool hw_counters;
		अचिन्हित पूर्णांक mem_blocks;
		अचिन्हित पूर्णांक mem_block_size;
		अचिन्हित पूर्णांक rx_size;
		अचिन्हित पूर्णांक tx_seq_table;
		bool ba_filter;
		bool disable_offload_fw;
	पूर्ण fw;

	/* पूर्णांकerface configuration combinations */
	काष्ठा ieee80211_अगरace_limit अगर_comb_limits[1];
	काष्ठा ieee80211_अगरace_combination अगर_combs[1];

	/* reset / stuck frames/queue detection */
	काष्ठा work_काष्ठा restart_work;
	काष्ठा work_काष्ठा ping_work;
	अचिन्हित पूर्णांक restart_counter;
	अचिन्हित दीर्घ queue_stop_समयout[__AR9170_NUM_TXQ];
	अचिन्हित दीर्घ max_queue_stop_समयout[__AR9170_NUM_TXQ];
	bool needs_full_reset;
	bool क्रमce_usb_reset;
	atomic_t pending_restarts;

	/* पूर्णांकerface mode settings */
	काष्ठा list_head vअगर_list;
	अचिन्हित दीर्घ vअगर_biपंचांगap;
	अचिन्हित पूर्णांक vअगरs;
	काष्ठा carl9170_vअगर vअगर_priv[AR9170_MAX_VIRTUAL_MAC];

	/* beaconing */
	spinlock_t beacon_lock;
	अचिन्हित पूर्णांक global_pretbtt;
	अचिन्हित पूर्णांक global_beacon_पूर्णांक;
	काष्ठा carl9170_vअगर_info __rcu *beacon_iter;
	अचिन्हित पूर्णांक beacon_enabled;

	/* cryptographic engine */
	u64 usedkeys;
	bool rx_software_decryption;
	bool disable_offload;

	/* filter settings */
	u64 cur_mc_hash;
	u32 cur_filter;
	अचिन्हित पूर्णांक filter_state;
	अचिन्हित पूर्णांक rx_filter_caps;
	bool snअगरfer_enabled;

	/* MAC */
	क्रमागत carl9170_erp_modes erp_mode;

	/* PHY */
	काष्ठा ieee80211_channel *channel;
	अचिन्हित पूर्णांक num_channels;
	पूर्णांक noise[4];
	अचिन्हित पूर्णांक chan_fail;
	अचिन्हित पूर्णांक total_chan_fail;
	u8 heavy_clip;
	u8 ht_settings;
	काष्ठा अणु
		u64 active;	/* usec */
		u64 cca;	/* usec */
		u64 tx_समय;	/* usec */
		u64 rx_total;
		u64 rx_overrun;
	पूर्ण tally;
	काष्ठा delayed_work stat_work;
	काष्ठा survey_info *survey;

	/* घातer calibration data */
	u8 घातer_5G_leg[4];
	u8 घातer_2G_cck[4];
	u8 घातer_2G_ofdm[4];
	u8 घातer_5G_ht20[8];
	u8 घातer_5G_ht40[8];
	u8 घातer_2G_ht20[8];
	u8 घातer_2G_ht40[8];

#अगर_घोषित CONFIG_CARL9170_LEDS
	/* LED */
	काष्ठा delayed_work led_work;
	काष्ठा carl9170_led leds[AR9170_NUM_LEDS];
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */

	/* qos queue settings */
	spinlock_t tx_stats_lock;
	काष्ठा carl9170_tx_queue_stats tx_stats[__AR9170_NUM_TXQ];
	काष्ठा ieee80211_tx_queue_params edcf[5];
	काष्ठा completion tx_flush;

	/* CMD */
	पूर्णांक cmd_seq;
	पूर्णांक पढ़ोlen;
	u8 *पढ़ोbuf;
	spinlock_t cmd_lock;
	काष्ठा completion cmd_रुको;
	जोड़ अणु
		__le32 cmd_buf[PAYLOAD_MAX + 1];
		काष्ठा carl9170_cmd cmd;
		काष्ठा carl9170_rsp rsp;
	पूर्ण;

	/* statistics */
	अचिन्हित पूर्णांक tx_dropped;
	अचिन्हित पूर्णांक tx_ack_failures;
	अचिन्हित पूर्णांक tx_fcs_errors;
	अचिन्हित पूर्णांक rx_dropped;

	/* EEPROM */
	काष्ठा ar9170_eeprom eeprom;

	/* tx queuing */
	काष्ठा sk_buff_head tx_pending[__AR9170_NUM_TXQ];
	काष्ठा sk_buff_head tx_status[__AR9170_NUM_TXQ];
	काष्ठा delayed_work tx_janitor;
	अचिन्हित दीर्घ tx_janitor_last_run;
	bool tx_schedule;

	/* tx ampdu */
	काष्ठा work_काष्ठा ampdu_work;
	spinlock_t tx_ampdu_list_lock;
	काष्ठा carl9170_sta_tid __rcu *tx_ampdu_iter;
	काष्ठा list_head tx_ampdu_list;
	atomic_t tx_ampdu_upload;
	atomic_t tx_ampdu_scheduler;
	atomic_t tx_total_pending;
	atomic_t tx_total_queued;
	अचिन्हित पूर्णांक tx_ampdu_list_len;
	पूर्णांक current_density;
	पूर्णांक current_factor;
	bool tx_ampdu_schedule;

	/* पूर्णांकernal memory management */
	spinlock_t mem_lock;
	अचिन्हित दीर्घ *mem_biपंचांगap;
	atomic_t mem_मुक्त_blocks;
	atomic_t mem_allocs;

	/* rxstream mpdu merge */
	काष्ठा ar9170_rx_head rx_plcp;
	bool rx_has_plcp;
	काष्ठा sk_buff *rx_failover;
	पूर्णांक rx_failover_missing;
	u32 ampdu_ref;

	/* FIFO क्रम collecting outstanding BlockAckRequest */
	काष्ठा list_head bar_list[__AR9170_NUM_TXQ];
	spinlock_t bar_list_lock[__AR9170_NUM_TXQ];

#अगर_घोषित CONFIG_CARL9170_WPC
	काष्ठा अणु
		bool pbc_state;
		काष्ठा input_dev *pbc;
		अक्षर name[32];
		अक्षर phys[32];
	पूर्ण wps;
#पूर्ण_अगर /* CONFIG_CARL9170_WPC */

#अगर_घोषित CONFIG_CARL9170_DEBUGFS
	काष्ठा carl9170_debug debug;
	काष्ठा dentry *debug_dir;
#पूर्ण_अगर /* CONFIG_CARL9170_DEBUGFS */

	/* PSM */
	काष्ठा work_काष्ठा ps_work;
	काष्ठा अणु
		अचिन्हित पूर्णांक dtim_counter;
		अचिन्हित दीर्घ last_beacon;
		अचिन्हित दीर्घ last_action;
		अचिन्हित दीर्घ last_slept;
		अचिन्हित पूर्णांक sleep_ms;
		अचिन्हित पूर्णांक off_override;
		bool state;
	पूर्ण ps;

#अगर_घोषित CONFIG_CARL9170_HWRNG
# define CARL9170_HWRNG_CACHE_SIZE	CARL9170_MAX_CMD_PAYLOAD_LEN
	काष्ठा अणु
		काष्ठा hwrng rng;
		bool initialized;
		अक्षर name[30 + 1];
		u16 cache[CARL9170_HWRNG_CACHE_SIZE / माप(u16)];
		अचिन्हित पूर्णांक cache_idx;
	पूर्ण rng;
#पूर्ण_अगर /* CONFIG_CARL9170_HWRNG */
पूर्ण;

क्रमागत carl9170_ps_off_override_reasons अणु
	PS_OFF_VIF	= BIT(0),
	PS_OFF_BCN	= BIT(1),
पूर्ण;

काष्ठा carl9170_bar_list_entry अणु
	काष्ठा list_head list;
	काष्ठा rcu_head head;
	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा carl9170_ba_stats अणु
	u8 ampdu_len;
	u8 ampdu_ack_len;
	bool clear;
	bool req;
पूर्ण;

काष्ठा carl9170_sta_info अणु
	bool ht_sta;
	bool sleeping;
	atomic_t pending_frames;
	अचिन्हित पूर्णांक ampdu_max_len;
	काष्ठा carl9170_sta_tid __rcu *agg[IEEE80211_NUM_TIDS];
	काष्ठा carl9170_ba_stats stats[IEEE80211_NUM_TIDS];
पूर्ण;

काष्ठा carl9170_tx_info अणु
	अचिन्हित दीर्घ समयout;
	काष्ठा ar9170 *ar;
	काष्ठा kref ref;
पूर्ण;

#घोषणा CHK_DEV_STATE(a, s)	(((काष्ठा ar9170 *)a)->state >= (s))
#घोषणा IS_INITIALIZED(a)	(CHK_DEV_STATE(a, CARL9170_STOPPED))
#घोषणा IS_ACCEPTING_CMD(a)	(CHK_DEV_STATE(a, CARL9170_IDLE))
#घोषणा IS_STARTED(a)		(CHK_DEV_STATE(a, CARL9170_STARTED))

अटल अंतरभूत व्योम __carl9170_set_state(काष्ठा ar9170 *ar,
	क्रमागत carl9170_device_state newstate)
अणु
	ar->state = newstate;
पूर्ण

अटल अंतरभूत व्योम carl9170_set_state(काष्ठा ar9170 *ar,
	क्रमागत carl9170_device_state newstate)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ar->state_lock, flags);
	__carl9170_set_state(ar, newstate);
	spin_unlock_irqrestore(&ar->state_lock, flags);
पूर्ण

अटल अंतरभूत व्योम carl9170_set_state_when(काष्ठा ar9170 *ar,
	क्रमागत carl9170_device_state min, क्रमागत carl9170_device_state newstate)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ar->state_lock, flags);
	अगर (CHK_DEV_STATE(ar, min))
		__carl9170_set_state(ar, newstate);
	spin_unlock_irqrestore(&ar->state_lock, flags);
पूर्ण

/* exported पूर्णांकerface */
व्योम *carl9170_alloc(माप_प्रकार priv_size);
पूर्णांक carl9170_रेजिस्टर(काष्ठा ar9170 *ar);
व्योम carl9170_unरेजिस्टर(काष्ठा ar9170 *ar);
व्योम carl9170_मुक्त(काष्ठा ar9170 *ar);
व्योम carl9170_restart(काष्ठा ar9170 *ar, स्थिर क्रमागत carl9170_restart_reasons r);
व्योम carl9170_ps_check(काष्ठा ar9170 *ar);

/* USB back-end */
पूर्णांक carl9170_usb_खोलो(काष्ठा ar9170 *ar);
व्योम carl9170_usb_stop(काष्ठा ar9170 *ar);
व्योम carl9170_usb_tx(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb);
व्योम carl9170_usb_handle_tx_err(काष्ठा ar9170 *ar);
पूर्णांक carl9170_exec_cmd(काष्ठा ar9170 *ar, स्थिर क्रमागत carl9170_cmd_oids,
		      u32 plen, व्योम *payload, u32 rlen, व्योम *resp);
पूर्णांक __carl9170_exec_cmd(काष्ठा ar9170 *ar, काष्ठा carl9170_cmd *cmd,
			स्थिर bool मुक्त_buf);
पूर्णांक carl9170_usb_restart(काष्ठा ar9170 *ar);
व्योम carl9170_usb_reset(काष्ठा ar9170 *ar);

/* MAC */
पूर्णांक carl9170_init_mac(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_qos(काष्ठा ar9170 *ar);
पूर्णांक carl9170_update_multicast(काष्ठा ar9170 *ar, स्थिर u64 mc_hast);
पूर्णांक carl9170_mod_भव_mac(काष्ठा ar9170 *ar, स्थिर अचिन्हित पूर्णांक id,
			     स्थिर u8 *mac);
पूर्णांक carl9170_set_operating_mode(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_beacon_समयrs(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_dyn_sअगरs_ack(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_rts_cts_rate(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_ampdu_settings(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_slot_समय(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_mac_rates(काष्ठा ar9170 *ar);
पूर्णांक carl9170_set_hwretry_limit(काष्ठा ar9170 *ar, स्थिर u32 max_retry);
पूर्णांक carl9170_upload_key(काष्ठा ar9170 *ar, स्थिर u8 id, स्थिर u8 *mac,
	स्थिर u8 ktype, स्थिर u8 keyidx, स्थिर u8 *keydata, स्थिर पूर्णांक keylen);
पूर्णांक carl9170_disable_key(काष्ठा ar9170 *ar, स्थिर u8 id);
पूर्णांक carl9170_set_mac_tpc(काष्ठा ar9170 *ar, काष्ठा ieee80211_channel *channel);

/* RX */
व्योम carl9170_rx(काष्ठा ar9170 *ar, व्योम *buf, अचिन्हित पूर्णांक len);
व्योम carl9170_handle_command_response(काष्ठा ar9170 *ar, व्योम *buf, u32 len);

/* TX */
व्योम carl9170_op_tx(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_tx_control *control,
		    काष्ठा sk_buff *skb);
व्योम carl9170_tx_janitor(काष्ठा work_काष्ठा *work);
व्योम carl9170_tx_process_status(काष्ठा ar9170 *ar,
				स्थिर काष्ठा carl9170_rsp *cmd);
व्योम carl9170_tx_status(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb,
			स्थिर bool success);
व्योम carl9170_tx_callback(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb);
व्योम carl9170_tx_drop(काष्ठा ar9170 *ar, काष्ठा sk_buff *skb);
व्योम carl9170_tx_scheduler(काष्ठा ar9170 *ar);
व्योम carl9170_tx_get_skb(काष्ठा sk_buff *skb);
पूर्णांक carl9170_tx_put_skb(काष्ठा sk_buff *skb);
पूर्णांक carl9170_update_beacon(काष्ठा ar9170 *ar, स्थिर bool submit);

/* LEDs */
#अगर_घोषित CONFIG_CARL9170_LEDS
पूर्णांक carl9170_led_रेजिस्टर(काष्ठा ar9170 *ar);
व्योम carl9170_led_unरेजिस्टर(काष्ठा ar9170 *ar);
#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */
पूर्णांक carl9170_led_init(काष्ठा ar9170 *ar);
पूर्णांक carl9170_led_set_state(काष्ठा ar9170 *ar, स्थिर u32 led_state);

/* PHY / RF */
पूर्णांक carl9170_set_channel(काष्ठा ar9170 *ar, काष्ठा ieee80211_channel *channel,
			 क्रमागत nl80211_channel_type bw);
पूर्णांक carl9170_get_noiseन्यूनमान(काष्ठा ar9170 *ar);

/* FW */
पूर्णांक carl9170_parse_firmware(काष्ठा ar9170 *ar);

बाह्य काष्ठा ieee80211_rate __carl9170_ratetable[];
बाह्य पूर्णांक modparam_noht;

अटल अंतरभूत काष्ठा ar9170 *carl9170_get_priv(काष्ठा carl9170_vअगर *carl_vअगर)
अणु
	वापस container_of(carl_vअगर, काष्ठा ar9170,
			    vअगर_priv[carl_vअगर->id]);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_hdr *carl9170_get_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (व्योम *)((काष्ठा _carl9170_tx_superframe *)
		skb->data)->frame_data;
पूर्ण

अटल अंतरभूत u16 get_seq_h(काष्ठा ieee80211_hdr *hdr)
अणु
	वापस le16_to_cpu(hdr->seq_ctrl) >> 4;
पूर्ण

अटल अंतरभूत u16 carl9170_get_seq(काष्ठा sk_buff *skb)
अणु
	वापस get_seq_h(carl9170_get_hdr(skb));
पूर्ण

अटल अंतरभूत u16 carl9170_get_tid(काष्ठा sk_buff *skb)
अणु
	वापस ieee80211_get_tid(carl9170_get_hdr(skb));
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_vअगर *
carl9170_get_vअगर(काष्ठा carl9170_vअगर_info *priv)
अणु
	वापस container_of((व्योम *)priv, काष्ठा ieee80211_vअगर, drv_priv);
पूर्ण

/* Protected by ar->mutex or RCU */
अटल अंतरभूत काष्ठा ieee80211_vअगर *carl9170_get_मुख्य_vअगर(काष्ठा ar9170 *ar)
अणु
	काष्ठा carl9170_vअगर_info *cvअगर;

	list_क्रम_each_entry_rcu(cvअगर, &ar->vअगर_list, list) अणु
		अगर (cvअगर->active)
			वापस carl9170_get_vअगर(cvअगर);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool is_मुख्य_vअगर(काष्ठा ar9170 *ar, काष्ठा ieee80211_vअगर *vअगर)
अणु
	bool ret;

	rcu_पढ़ो_lock();
	ret = (carl9170_get_मुख्य_vअगर(ar) == vअगर);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __CARL9170_H */
