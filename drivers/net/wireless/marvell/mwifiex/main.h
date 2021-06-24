<शैली गुरु>
/*
 * NXP Wireless LAN device driver: major data काष्ठाures and prototypes
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित _MWIFIEX_MAIN_H_
#घोषणा _MWIFIEX_MAIN_H_

#समावेश <linux/completion.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/sock.h>
#समावेश <net/lib80211.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/of.h>
#समावेश <linux/idr.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_irq.h>

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "pcie.h"
#समावेश "usb.h"
#समावेश "sdio.h"

बाह्य स्थिर अक्षर driver_version[];
बाह्य bool mfg_mode;
बाह्य bool aggr_ctrl;

काष्ठा mwअगरiex_adapter;
काष्ठा mwअगरiex_निजी;

क्रमागत अणु
	MWIFIEX_ASYNC_CMD,
	MWIFIEX_SYNC_CMD
पूर्ण;

#घोषणा MWIFIEX_DRIVER_MODE_STA			BIT(0)
#घोषणा MWIFIEX_DRIVER_MODE_UAP			BIT(1)
#घोषणा MWIFIEX_DRIVER_MODE_P2P			BIT(2)
#घोषणा MWIFIEX_DRIVER_MODE_BITMASK		(BIT(0) | BIT(1) | BIT(2))

#घोषणा MWIFIEX_MAX_AP				64

#घोषणा MWIFIEX_MAX_PKTS_TXQ			16

#घोषणा MWIFIEX_DEFAULT_WATCHDOG_TIMEOUT	(5 * HZ)

#घोषणा MWIFIEX_TIMER_10S			10000
#घोषणा MWIFIEX_TIMER_1S			1000

#घोषणा MAX_TX_PENDING      400
#घोषणा LOW_TX_PENDING      380

#घोषणा HIGH_RX_PENDING     50
#घोषणा LOW_RX_PENDING      20

#घोषणा MWIFIEX_UPLD_SIZE               (2312)

#घोषणा MAX_EVENT_SIZE                  2048

#घोषणा MWIFIEX_FW_DUMP_SIZE       (2 * 1024 * 1024)

#घोषणा ARP_FILTER_MAX_BUF_SIZE         68

#घोषणा MWIFIEX_KEY_BUFFER_SIZE			16
#घोषणा MWIFIEX_DEFAULT_LISTEN_INTERVAL 10
#घोषणा MWIFIEX_MAX_REGION_CODE         9

#घोषणा DEFAULT_BCN_AVG_FACTOR          8
#घोषणा DEFAULT_DATA_AVG_FACTOR         8

#घोषणा FIRST_VALID_CHANNEL				0xff
#घोषणा DEFAULT_AD_HOC_CHANNEL			6
#घोषणा DEFAULT_AD_HOC_CHANNEL_A		36

#घोषणा DEFAULT_BCN_MISS_TIMEOUT		5

#घोषणा MAX_SCAN_BEACON_BUFFER			8000

#घोषणा SCAN_BEACON_ENTRY_PAD			6

#घोषणा MWIFIEX_PASSIVE_SCAN_CHAN_TIME	110
#घोषणा MWIFIEX_ACTIVE_SCAN_CHAN_TIME	40
#घोषणा MWIFIEX_SPECIFIC_SCAN_CHAN_TIME	40
#घोषणा MWIFIEX_DEF_SCAN_CHAN_GAP_TIME  50

#घोषणा SCAN_RSSI(RSSI)					(0x100 - ((u8)(RSSI)))

#घोषणा MWIFIEX_MAX_TOTAL_SCAN_TIME	(MWIFIEX_TIMER_10S - MWIFIEX_TIMER_1S)

#घोषणा WPA_GTK_OUI_OFFSET				2
#घोषणा RSN_GTK_OUI_OFFSET				2

#घोषणा MWIFIEX_OUI_NOT_PRESENT			0
#घोषणा MWIFIEX_OUI_PRESENT				1

#घोषणा PKT_TYPE_MGMT	0xE5

/*
 * Do not check क्रम data_received क्रम USB, as data_received
 * is handled in mwअगरiex_usb_recv क्रम USB
 */
#घोषणा IS_CARD_RX_RCVD(adapter) (adapter->cmd_resp_received || \
				adapter->event_received || \
				adapter->data_received)

#घोषणा MWIFIEX_TYPE_CMD				1
#घोषणा MWIFIEX_TYPE_DATA				0
#घोषणा MWIFIEX_TYPE_AGGR_DATA				10
#घोषणा MWIFIEX_TYPE_EVENT				3

#घोषणा MAX_BITMAP_RATES_SIZE			18

#घोषणा MAX_CHANNEL_BAND_BG     14
#घोषणा MAX_CHANNEL_BAND_A      165

#घोषणा MAX_FREQUENCY_BAND_BG   2484

#घोषणा MWIFIEX_EVENT_HEADER_LEN           4
#घोषणा MWIFIEX_UAP_EVENT_EXTRA_HEADER	   2

#घोषणा MWIFIEX_TYPE_LEN			4
#घोषणा MWIFIEX_USB_TYPE_CMD			0xF00DFACE
#घोषणा MWIFIEX_USB_TYPE_DATA			0xBEADC0DE
#घोषणा MWIFIEX_USB_TYPE_EVENT			0xBEEFFACE

/* Threshold क्रम tx_समयout_cnt beक्रमe we trigger a card reset */
#घोषणा TX_TIMEOUT_THRESHOLD	6

#घोषणा MWIFIEX_DRV_INFO_SIZE_MAX 0x40000

/* Address alignment */
#घोषणा MWIFIEX_ALIGN_ADDR(p, a) (((दीर्घ)(p) + (a) - 1) & ~((a) - 1))

#घोषणा MWIFIEX_MAC_LOCAL_ADMIN_BIT		41

/**
 *क्रमागत mwअगरiex_debug_level  -  marvell wअगरi debug level
 */
क्रमागत MWIFIEX_DEBUG_LEVEL अणु
	MWIFIEX_DBG_MSG		= 0x00000001,
	MWIFIEX_DBG_FATAL	= 0x00000002,
	MWIFIEX_DBG_ERROR	= 0x00000004,
	MWIFIEX_DBG_DATA	= 0x00000008,
	MWIFIEX_DBG_CMD		= 0x00000010,
	MWIFIEX_DBG_EVENT	= 0x00000020,
	MWIFIEX_DBG_INTR	= 0x00000040,
	MWIFIEX_DBG_IOCTL	= 0x00000080,

	MWIFIEX_DBG_MPA_D	= 0x00008000,
	MWIFIEX_DBG_DAT_D	= 0x00010000,
	MWIFIEX_DBG_CMD_D	= 0x00020000,
	MWIFIEX_DBG_EVT_D	= 0x00040000,
	MWIFIEX_DBG_FW_D	= 0x00080000,
	MWIFIEX_DBG_IF_D	= 0x00100000,

	MWIFIEX_DBG_ENTRY	= 0x10000000,
	MWIFIEX_DBG_WARN	= 0x20000000,
	MWIFIEX_DBG_INFO	= 0x40000000,
	MWIFIEX_DBG_DUMP	= 0x80000000,

	MWIFIEX_DBG_ANY		= 0xffffffff
पूर्ण;

#घोषणा MWIFIEX_DEFAULT_DEBUG_MASK	(MWIFIEX_DBG_MSG | \
					MWIFIEX_DBG_FATAL | \
					MWIFIEX_DBG_ERROR)

__म_लिखो(3, 4)
व्योम _mwअगरiex_dbg(स्थिर काष्ठा mwअगरiex_adapter *adapter, पूर्णांक mask,
		  स्थिर अक्षर *fmt, ...);
#घोषणा mwअगरiex_dbg(adapter, mask, fmt, ...)				\
	_mwअगरiex_dbg(adapter, MWIFIEX_DBG_##mask, fmt, ##__VA_ARGS__)

#घोषणा DEBUG_DUMP_DATA_MAX_LEN		128
#घोषणा mwअगरiex_dbg_dump(adapter, dbg_mask, str, buf, len)	\
करो अणु								\
	अगर ((adapter)->debug_mask & MWIFIEX_DBG_##dbg_mask)	\
		prपूर्णांक_hex_dump(KERN_DEBUG, str,			\
			       DUMP_PREFIX_OFFSET, 16, 1,	\
			       buf, len, false);		\
पूर्ण जबतक (0)

/** Min BGSCAN पूर्णांकerval 15 second */
#घोषणा MWIFIEX_BGSCAN_INTERVAL 15000
/** शेष repeat count */
#घोषणा MWIFIEX_BGSCAN_REPEAT_COUNT 6

काष्ठा mwअगरiex_dbg अणु
	u32 num_cmd_host_to_card_failure;
	u32 num_cmd_sleep_cfm_host_to_card_failure;
	u32 num_tx_host_to_card_failure;
	u32 num_event_deauth;
	u32 num_event_disassoc;
	u32 num_event_link_lost;
	u32 num_cmd_deauth;
	u32 num_cmd_assoc_success;
	u32 num_cmd_assoc_failure;
	u32 num_tx_समयout;
	u16 समयout_cmd_id;
	u16 समयout_cmd_act;
	u16 last_cmd_id[DBG_CMD_NUM];
	u16 last_cmd_act[DBG_CMD_NUM];
	u16 last_cmd_index;
	u16 last_cmd_resp_id[DBG_CMD_NUM];
	u16 last_cmd_resp_index;
	u16 last_event[DBG_CMD_NUM];
	u16 last_event_index;
	u32 last_mp_wr_biपंचांगap[MWIFIEX_DBG_SDIO_MP_NUM];
	u32 last_mp_wr_ports[MWIFIEX_DBG_SDIO_MP_NUM];
	u32 last_mp_wr_len[MWIFIEX_DBG_SDIO_MP_NUM];
	u32 last_mp_curr_wr_port[MWIFIEX_DBG_SDIO_MP_NUM];
	u8 last_sdio_mp_index;
पूर्ण;

क्रमागत MWIFIEX_HARDWARE_STATUS अणु
	MWIFIEX_HW_STATUS_READY,
	MWIFIEX_HW_STATUS_INITIALIZING,
	MWIFIEX_HW_STATUS_INIT_DONE,
	MWIFIEX_HW_STATUS_RESET,
	MWIFIEX_HW_STATUS_NOT_READY
पूर्ण;

क्रमागत MWIFIEX_802_11_POWER_MODE अणु
	MWIFIEX_802_11_POWER_MODE_CAM,
	MWIFIEX_802_11_POWER_MODE_PSP
पूर्ण;

काष्ठा mwअगरiex_tx_param अणु
	u32 next_pkt_len;
पूर्ण;

क्रमागत MWIFIEX_PS_STATE अणु
	PS_STATE_AWAKE,
	PS_STATE_PRE_SLEEP,
	PS_STATE_SLEEP_CFM,
	PS_STATE_SLEEP
पूर्ण;

क्रमागत mwअगरiex_अगरace_type अणु
	MWIFIEX_SDIO,
	MWIFIEX_PCIE,
	MWIFIEX_USB
पूर्ण;

काष्ठा mwअगरiex_add_ba_param अणु
	u32 tx_win_size;
	u32 rx_win_size;
	u32 समयout;
	u8 tx_amsdu;
	u8 rx_amsdu;
पूर्ण;

काष्ठा mwअगरiex_tx_aggr अणु
	u8 ampdu_user;
	u8 ampdu_ap;
	u8 amsdu;
पूर्ण;

क्रमागत mwअगरiex_ba_status अणु
	BA_SETUP_NONE = 0,
	BA_SETUP_INPROGRESS,
	BA_SETUP_COMPLETE
पूर्ण;

काष्ठा mwअगरiex_ra_list_tbl अणु
	काष्ठा list_head list;
	काष्ठा sk_buff_head skb_head;
	u8 ra[ETH_ALEN];
	u32 is_11n_enabled;
	u16 max_amsdu;
	u16 ba_pkt_count;
	u8 ba_packet_thr;
	क्रमागत mwअगरiex_ba_status ba_status;
	u8 amsdu_in_ampdu;
	u16 total_pkt_count;
	bool tdls_link;
	bool tx_छोड़ोd;
पूर्ण;

काष्ठा mwअगरiex_tid_tbl अणु
	काष्ठा list_head ra_list;
पूर्ण;

#घोषणा WMM_HIGHEST_PRIORITY		7
#घोषणा HIGH_PRIO_TID				7
#घोषणा LOW_PRIO_TID				0
#घोषणा NO_PKT_PRIO_TID				-1
#घोषणा MWIFIEX_WMM_DRV_DELAY_MAX 510

काष्ठा mwअगरiex_wmm_desc अणु
	काष्ठा mwअगरiex_tid_tbl tid_tbl_ptr[MAX_NUM_TID];
	u32 packets_out[MAX_NUM_TID];
	u32 pkts_छोड़ोd[MAX_NUM_TID];
	/* spin lock to protect ra_list */
	spinlock_t ra_list_spinlock;
	काष्ठा mwअगरiex_wmm_ac_status ac_status[IEEE80211_NUM_ACS];
	क्रमागत mwअगरiex_wmm_ac_e ac_करोwn_graded_vals[IEEE80211_NUM_ACS];
	u32 drv_pkt_delay_max;
	u8 queue_priority[IEEE80211_NUM_ACS];
	u32 user_pri_pkt_tx_ctrl[WMM_HIGHEST_PRIORITY + 1];	/* UP: 0 to 7 */
	/* Number of transmit packets queued */
	atomic_t tx_pkts_queued;
	/* Tracks highest priority with a packet queued */
	atomic_t highest_queued_prio;
पूर्ण;

काष्ठा mwअगरiex_802_11_security अणु
	u8 wpa_enabled;
	u8 wpa2_enabled;
	u8 wapi_enabled;
	u8 wapi_key_on;
	u8 wep_enabled;
	u32 authentication_mode;
	u8 is_authtype_स्वतः;
	u32 encryption_mode;
पूर्ण;

काष्ठा ieee_types_header अणु
	u8 element_id;
	u8 len;
पूर्ण __packed;

काष्ठा ieee_types_venकरोr_specअगरic अणु
	काष्ठा ieee_types_venकरोr_header vend_hdr;
	u8 data[IEEE_MAX_IE_SIZE - माप(काष्ठा ieee_types_venकरोr_header)];
पूर्ण __packed;

काष्ठा ieee_types_generic अणु
	काष्ठा ieee_types_header ieee_hdr;
	u8 data[IEEE_MAX_IE_SIZE - माप(काष्ठा ieee_types_header)];
पूर्ण __packed;

काष्ठा ieee_types_bss_co_2040 अणु
	काष्ठा ieee_types_header ieee_hdr;
	u8 bss_2040co;
पूर्ण __packed;

काष्ठा ieee_types_extcap अणु
	काष्ठा ieee_types_header ieee_hdr;
	u8 ext_capab[8];
पूर्ण __packed;

काष्ठा ieee_types_vht_cap अणु
	काष्ठा ieee_types_header ieee_hdr;
	काष्ठा ieee80211_vht_cap vhtcap;
पूर्ण __packed;

काष्ठा ieee_types_vht_oper अणु
	काष्ठा ieee_types_header ieee_hdr;
	काष्ठा ieee80211_vht_operation vhtoper;
पूर्ण __packed;

काष्ठा ieee_types_aid अणु
	काष्ठा ieee_types_header ieee_hdr;
	u16 aid;
पूर्ण __packed;

काष्ठा mwअगरiex_bssdescriptor अणु
	u8 mac_address[ETH_ALEN];
	काष्ठा cfg80211_ssid ssid;
	u32 privacy;
	s32 rssi;
	u32 channel;
	u32 freq;
	u16 beacon_period;
	u8 erp_flags;
	u32 bss_mode;
	u8 supported_rates[MWIFIEX_SUPPORTED_RATES];
	u8 data_rates[MWIFIEX_SUPPORTED_RATES];
	/* Network band.
	 * BAND_B(0x01): 'b' band
	 * BAND_G(0x02): 'g' band
	 * BAND_A(0X04): 'a' band
	 */
	u16 bss_band;
	u64 fw_tsf;
	u64 बारtamp;
	जोड़ ieee_types_phy_param_set phy_param_set;
	जोड़ ieee_types_ss_param_set ss_param_set;
	u16 cap_info_biपंचांगap;
	काष्ठा ieee_types_wmm_parameter wmm_ie;
	u8  disable_11n;
	काष्ठा ieee80211_ht_cap *bcn_ht_cap;
	u16 ht_cap_offset;
	काष्ठा ieee80211_ht_operation *bcn_ht_oper;
	u16 ht_info_offset;
	u8 *bcn_bss_co_2040;
	u16 bss_co_2040_offset;
	u8 *bcn_ext_cap;
	u16 ext_cap_offset;
	काष्ठा ieee80211_vht_cap *bcn_vht_cap;
	u16 vht_cap_offset;
	काष्ठा ieee80211_vht_operation *bcn_vht_oper;
	u16 vht_info_offset;
	काष्ठा ieee_types_oper_mode_ntf *oper_mode;
	u16 oper_mode_offset;
	u8 disable_11ac;
	काष्ठा ieee_types_venकरोr_specअगरic *bcn_wpa_ie;
	u16 wpa_offset;
	काष्ठा ieee_types_generic *bcn_rsn_ie;
	u16 rsn_offset;
	काष्ठा ieee_types_generic *bcn_wapi_ie;
	u16 wapi_offset;
	u8 *beacon_buf;
	u32 beacon_buf_size;
	u8 sensed_11h;
	u8 local_स्थिरraपूर्णांक;
	u8 chan_sw_ie_present;
पूर्ण;

काष्ठा mwअगरiex_current_bss_params अणु
	काष्ठा mwअगरiex_bssdescriptor bss_descriptor;
	u8 wmm_enabled;
	u8 wmm_uapsd_enabled;
	u8 band;
	u32 num_of_rates;
	u8 data_rates[MWIFIEX_SUPPORTED_RATES];
पूर्ण;

काष्ठा mwअगरiex_sleep_params अणु
	u16 sp_error;
	u16 sp_offset;
	u16 sp_stable_समय;
	u8 sp_cal_control;
	u8 sp_ext_sleep_clk;
	u16 sp_reserved;
पूर्ण;

काष्ठा mwअगरiex_sleep_period अणु
	u16 period;
	u16 reserved;
पूर्ण;

काष्ठा mwअगरiex_wep_key अणु
	u32 length;
	u32 key_index;
	u32 key_length;
	u8 key_material[MWIFIEX_KEY_BUFFER_SIZE];
पूर्ण;

#घोषणा MAX_REGION_CHANNEL_NUM  2

काष्ठा mwअगरiex_chan_freq_घातer अणु
	u16 channel;
	u32 freq;
	u16 max_tx_घातer;
	u8 unsupported;
पूर्ण;

क्रमागत state_11d_t अणु
	DISABLE_11D = 0,
	ENABLE_11D = 1,
पूर्ण;

#घोषणा MWIFIEX_MAX_TRIPLET_802_11D		83

काष्ठा mwअगरiex_802_11d_करोमुख्य_reg अणु
	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	u8 no_of_triplet;
	काष्ठा ieee80211_country_ie_triplet
		triplet[MWIFIEX_MAX_TRIPLET_802_11D];
पूर्ण;

काष्ठा mwअगरiex_venकरोr_spec_cfg_ie अणु
	u16 mask;
	u16 flag;
	u8 ie[MWIFIEX_MAX_VSIE_LEN];
पूर्ण;

काष्ठा wps अणु
	u8 session_enable;
पूर्ण;

काष्ठा mwअगरiex_roc_cfg अणु
	u64 cookie;
	काष्ठा ieee80211_channel chan;
पूर्ण;

क्रमागत mwअगरiex_अगरace_work_flags अणु
	MWIFIEX_IFACE_WORK_DEVICE_DUMP,
	MWIFIEX_IFACE_WORK_CARD_RESET,
पूर्ण;

क्रमागत mwअगरiex_adapter_work_flags अणु
	MWIFIEX_SURPRISE_REMOVED,
	MWIFIEX_IS_CMD_TIMEDOUT,
	MWIFIEX_IS_SUSPENDED,
	MWIFIEX_IS_HS_CONFIGURED,
	MWIFIEX_IS_HS_ENABLING,
पूर्ण;

काष्ठा mwअगरiex_band_config अणु
	u8 chan_band:2;
	u8 chan_width:2;
	u8 chan2_offset:2;
	u8 scan_mode:2;
पूर्ण __packed;

काष्ठा mwअगरiex_channel_band अणु
	काष्ठा mwअगरiex_band_config band_config;
	u8 channel;
पूर्ण;

काष्ठा mwअगरiex_निजी अणु
	काष्ठा mwअगरiex_adapter *adapter;
	u8 bss_type;
	u8 bss_role;
	u8 bss_priority;
	u8 bss_num;
	u8 bss_started;
	u8 frame_type;
	u8 curr_addr[ETH_ALEN];
	u8 media_connected;
	u8 port_खोलो;
	u8 usb_port;
	u32 num_tx_समयout;
	/* track consecutive समयout */
	u8 tx_समयout_cnt;
	काष्ठा net_device *netdev;
	काष्ठा net_device_stats stats;
	u32 curr_pkt_filter;
	u32 bss_mode;
	u32 pkt_tx_ctrl;
	u16 tx_घातer_level;
	u8 max_tx_घातer_level;
	u8 min_tx_घातer_level;
	u32 tx_ant;
	u32 rx_ant;
	u8 tx_rate;
	u8 tx_htinfo;
	u8 rxpd_htinfo;
	u8 rxpd_rate;
	u16 rate_biपंचांगap;
	u16 biपंचांगap_rates[MAX_BITMAP_RATES_SIZE];
	u32 data_rate;
	u8 is_data_rate_स्वतः;
	u16 bcn_avg_factor;
	u16 data_avg_factor;
	s16 data_rssi_last;
	s16 data_nf_last;
	s16 data_rssi_avg;
	s16 data_nf_avg;
	s16 bcn_rssi_last;
	s16 bcn_nf_last;
	s16 bcn_rssi_avg;
	s16 bcn_nf_avg;
	काष्ठा mwअगरiex_bssdescriptor *attempted_bss_desc;
	काष्ठा cfg80211_ssid prev_ssid;
	u8 prev_bssid[ETH_ALEN];
	काष्ठा mwअगरiex_current_bss_params curr_bss_params;
	u16 beacon_period;
	u8 dtim_period;
	u16 listen_पूर्णांकerval;
	u16 atim_winकरोw;
	u8 adhoc_channel;
	u8 adhoc_is_link_sensed;
	u8 adhoc_state;
	काष्ठा mwअगरiex_802_11_security sec_info;
	काष्ठा mwअगरiex_wep_key wep_key[NUM_WEP_KEYS];
	u16 wep_key_curr_index;
	u8 wpa_ie[256];
	u16 wpa_ie_len;
	u8 wpa_is_gtk_set;
	काष्ठा host_cmd_ds_802_11_key_material aes_key;
	काष्ठा host_cmd_ds_802_11_key_material_v2 aes_key_v2;
	u8 wapi_ie[256];
	u16 wapi_ie_len;
	u8 *wps_ie;
	u16 wps_ie_len;
	u8 wmm_required;
	u8 wmm_enabled;
	u8 wmm_qosinfo;
	काष्ठा mwअगरiex_wmm_desc wmm;
	atomic_t wmm_tx_pending[IEEE80211_NUM_ACS];
	काष्ठा list_head sta_list;
	/* spin lock क्रम associated station/TDLS peers list */
	spinlock_t sta_list_spinlock;
	काष्ठा list_head स्वतः_tdls_list;
	/* spin lock क्रम स्वतः TDLS peer list */
	spinlock_t स्वतः_tdls_lock;
	काष्ठा list_head tx_ba_stream_tbl_ptr;
	/* spin lock क्रम tx_ba_stream_tbl_ptr queue */
	spinlock_t tx_ba_stream_tbl_lock;
	काष्ठा mwअगरiex_tx_aggr aggr_prio_tbl[MAX_NUM_TID];
	काष्ठा mwअगरiex_add_ba_param add_ba_param;
	u16 rx_seq[MAX_NUM_TID];
	u8 tos_to_tid_inv[MAX_NUM_TID];
	काष्ठा list_head rx_reorder_tbl_ptr;
	/* spin lock क्रम rx_reorder_tbl_ptr queue */
	spinlock_t rx_reorder_tbl_lock;
#घोषणा MWIFIEX_ASSOC_RSP_BUF_SIZE  500
	u8 assoc_rsp_buf[MWIFIEX_ASSOC_RSP_BUF_SIZE];
	u32 assoc_rsp_size;

#घोषणा MWIFIEX_GENIE_BUF_SIZE      256
	u8 gen_ie_buf[MWIFIEX_GENIE_BUF_SIZE];
	u8 gen_ie_buf_len;

	काष्ठा mwअगरiex_venकरोr_spec_cfg_ie vs_ie[MWIFIEX_MAX_VSIE_NUM];

#घोषणा MWIFIEX_ASSOC_TLV_BUF_SIZE  256
	u8 assoc_tlv_buf[MWIFIEX_ASSOC_TLV_BUF_SIZE];
	u8 assoc_tlv_buf_len;

	u8 *curr_bcn_buf;
	u32 curr_bcn_size;
	/* spin lock क्रम beacon buffer */
	spinlock_t curr_bcn_buf_lock;
	काष्ठा wireless_dev wdev;
	काष्ठा mwअगरiex_chan_freq_घातer cfp;
	u32 versionstrsel;
	अक्षर version_str[128];
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dfs_dev_dir;
#पूर्ण_अगर
	u16 current_key_index;
	काष्ठा mutex async_mutex;
	काष्ठा cfg80211_scan_request *scan_request;
	u8 cfg_bssid[6];
	काष्ठा wps wps;
	u8 scan_block;
	s32 cqm_rssi_thold;
	u32 cqm_rssi_hyst;
	u8 subsc_evt_rssi_state;
	काष्ठा mwअगरiex_ds_misc_subsc_evt async_subsc_evt_storage;
	काष्ठा mwअगरiex_ie mgmt_ie[MAX_MGMT_IE_INDEX];
	u16 beacon_idx;
	u16 proberesp_idx;
	u16 assocresp_idx;
	u16 gen_idx;
	u8 ap_11n_enabled;
	u8 ap_11ac_enabled;
	u32 mgmt_frame_mask;
	काष्ठा mwअगरiex_roc_cfg roc_cfg;
	bool scan_पातing;
	u8 sched_scanning;
	u8 csa_chan;
	अचिन्हित दीर्घ csa_expire_समय;
	u8 del_list_idx;
	bool hs2_enabled;
	काष्ठा mwअगरiex_uap_bss_param bss_cfg;
	काष्ठा cfg80211_chan_def bss_chandef;
	काष्ठा station_parameters *sta_params;
	काष्ठा sk_buff_head tdls_txq;
	u8 check_tdls_tx;
	काष्ठा समयr_list स्वतः_tdls_समयr;
	bool स्वतः_tdls_समयr_active;
	काष्ठा idr ack_status_frames;
	/* spin lock क्रम ack status */
	spinlock_t ack_status_lock;
	/** rx histogram data */
	काष्ठा mwअगरiex_histogram_data *hist_data;
	काष्ठा cfg80211_chan_def dfs_chandef;
	काष्ठा workqueue_काष्ठा *dfs_cac_workqueue;
	काष्ठा delayed_work dfs_cac_work;
	काष्ठा समयr_list dfs_chan_चयन_समयr;
	काष्ठा workqueue_काष्ठा *dfs_chan_sw_workqueue;
	काष्ठा delayed_work dfs_chan_sw_work;
	काष्ठा cfg80211_beacon_data beacon_after;
	काष्ठा mwअगरiex_11h_पूर्णांकf_state state_11h;
	काष्ठा mwअगरiex_ds_mem_rw mem_rw;
	काष्ठा sk_buff_head bypass_txq;
	काष्ठा mwअगरiex_user_scan_chan hidden_chan[MWIFIEX_USER_SCAN_CHAN_MAX];
	u8 assoc_resp_ht_param;
	bool ht_param_present;
पूर्ण;


काष्ठा mwअगरiex_tx_ba_stream_tbl अणु
	काष्ठा list_head list;
	पूर्णांक tid;
	u8 ra[ETH_ALEN];
	क्रमागत mwअगरiex_ba_status ba_status;
	u8 amsdu;
पूर्ण;

काष्ठा mwअगरiex_rx_reorder_tbl;

काष्ठा reorder_पंचांगr_cnxt अणु
	काष्ठा समयr_list समयr;
	काष्ठा mwअगरiex_rx_reorder_tbl *ptr;
	काष्ठा mwअगरiex_निजी *priv;
	u8 समयr_is_set;
पूर्ण;

काष्ठा mwअगरiex_rx_reorder_tbl अणु
	काष्ठा list_head list;
	पूर्णांक tid;
	u8 ta[ETH_ALEN];
	पूर्णांक init_win;
	पूर्णांक start_win;
	पूर्णांक win_size;
	व्योम **rx_reorder_ptr;
	काष्ठा reorder_पंचांगr_cnxt समयr_context;
	u8 amsdu;
	u8 flags;
पूर्ण;

काष्ठा mwअगरiex_bss_prio_node अणु
	काष्ठा list_head list;
	काष्ठा mwअगरiex_निजी *priv;
पूर्ण;

काष्ठा mwअगरiex_bss_prio_tbl अणु
	काष्ठा list_head bss_prio_head;
	/* spin lock क्रम bss priority  */
	spinlock_t bss_prio_lock;
	काष्ठा mwअगरiex_bss_prio_node *bss_prio_cur;
पूर्ण;

काष्ठा cmd_ctrl_node अणु
	काष्ठा list_head list;
	काष्ठा mwअगरiex_निजी *priv;
	u32 cmd_no;
	u32 cmd_flag;
	काष्ठा sk_buff *cmd_skb;
	काष्ठा sk_buff *resp_skb;
	व्योम *data_buf;
	u32 रुको_q_enabled;
	काष्ठा sk_buff *skb;
	u8 *condition;
	u8 cmd_रुको_q_woken;
पूर्ण;

काष्ठा mwअगरiex_bss_priv अणु
	u8 band;
	u64 fw_tsf;
पूर्ण;

काष्ठा mwअगरiex_tdls_capab अणु
	__le16 capab;
	u8 rates[32];
	u8 rates_len;
	u8 qos_info;
	u8 coex_2040;
	u16 aid;
	काष्ठा ieee80211_ht_cap ht_capb;
	काष्ठा ieee80211_ht_operation ht_oper;
	काष्ठा ieee_types_extcap extcap;
	काष्ठा ieee_types_generic rsn_ie;
	काष्ठा ieee80211_vht_cap vhtcap;
	काष्ठा ieee80211_vht_operation vhtoper;
पूर्ण;

काष्ठा mwअगरiex_station_stats अणु
	u64 last_rx;
	s8 rssi;
	u64 rx_bytes;
	u64 tx_bytes;
	u32 rx_packets;
	u32 tx_packets;
	u32 tx_failed;
	u8 last_tx_rate;
	u8 last_tx_htinfo;
पूर्ण;

/* This is AP/TDLS specअगरic काष्ठाure which stores inक्रमmation
 * about associated/peer STA
 */
काष्ठा mwअगरiex_sta_node अणु
	काष्ठा list_head list;
	u8 mac_addr[ETH_ALEN];
	u8 is_wmm_enabled;
	u8 is_11n_enabled;
	u8 is_11ac_enabled;
	u8 ampdu_sta[MAX_NUM_TID];
	u16 rx_seq[MAX_NUM_TID];
	u16 max_amsdu;
	u8 tdls_status;
	काष्ठा mwअगरiex_tdls_capab tdls_cap;
	काष्ठा mwअगरiex_station_stats stats;
	u8 tx_छोड़ो;
पूर्ण;

काष्ठा mwअगरiex_स्वतः_tdls_peer अणु
	काष्ठा list_head list;
	u8 mac_addr[ETH_ALEN];
	u8 tdls_status;
	पूर्णांक rssi;
	दीर्घ rssi_jअगरfies;
	u8 failure_count;
	u8 करो_discover;
	u8 करो_setup;
पूर्ण;

#घोषणा MWIFIEX_TYPE_AGGR_DATA_V2 11
#घोषणा MWIFIEX_BUS_AGGR_MODE_LEN_V2 (2)
#घोषणा MWIFIEX_BUS_AGGR_MAX_LEN 16000
#घोषणा MWIFIEX_BUS_AGGR_MAX_NUM 10
काष्ठा bus_aggr_params अणु
	u16 enable;
	u16 mode;
	u16 tx_aggr_max_size;
	u16 tx_aggr_max_num;
	u16 tx_aggr_align;
पूर्ण;

काष्ठा mwअगरiex_अगर_ops अणु
	पूर्णांक (*init_अगर) (काष्ठा mwअगरiex_adapter *);
	व्योम (*cleanup_अगर) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*check_fw_status) (काष्ठा mwअगरiex_adapter *, u32);
	पूर्णांक (*check_winner_status)(काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*prog_fw) (काष्ठा mwअगरiex_adapter *, काष्ठा mwअगरiex_fw_image *);
	पूर्णांक (*रेजिस्टर_dev) (काष्ठा mwअगरiex_adapter *);
	व्योम (*unरेजिस्टर_dev) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*enable_पूर्णांक) (काष्ठा mwअगरiex_adapter *);
	व्योम (*disable_पूर्णांक) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*process_पूर्णांक_status) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*host_to_card) (काष्ठा mwअगरiex_adapter *, u8, काष्ठा sk_buff *,
			     काष्ठा mwअगरiex_tx_param *);
	पूर्णांक (*wakeup) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*wakeup_complete) (काष्ठा mwअगरiex_adapter *);

	/* Interface specअगरic functions */
	व्योम (*update_mp_end_port) (काष्ठा mwअगरiex_adapter *, u16);
	व्योम (*cleanup_mpa_buf) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*cmdrsp_complete) (काष्ठा mwअगरiex_adapter *, काष्ठा sk_buff *);
	पूर्णांक (*event_complete) (काष्ठा mwअगरiex_adapter *, काष्ठा sk_buff *);
	पूर्णांक (*init_fw_port) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*dnld_fw) (काष्ठा mwअगरiex_adapter *, काष्ठा mwअगरiex_fw_image *);
	व्योम (*card_reset) (काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*reg_dump)(काष्ठा mwअगरiex_adapter *, अक्षर *);
	व्योम (*device_dump)(काष्ठा mwअगरiex_adapter *);
	पूर्णांक (*clean_pcie_ring) (काष्ठा mwअगरiex_adapter *adapter);
	व्योम (*अगरace_work)(काष्ठा work_काष्ठा *work);
	व्योम (*submit_rem_rx_urbs)(काष्ठा mwअगरiex_adapter *adapter);
	व्योम (*deaggr_pkt)(काष्ठा mwअगरiex_adapter *, काष्ठा sk_buff *);
	व्योम (*multi_port_resync)(काष्ठा mwअगरiex_adapter *);
	bool (*is_port_पढ़ोy)(काष्ठा mwअगरiex_निजी *);
	व्योम (*करोwn_dev)(काष्ठा mwअगरiex_adapter *);
	व्योम (*up_dev)(काष्ठा mwअगरiex_adapter *);
पूर्ण;

काष्ठा mwअगरiex_adapter अणु
	u8 अगरace_type;
	अचिन्हित पूर्णांक debug_mask;
	काष्ठा mwअगरiex_अगरace_comb अगरace_limit;
	काष्ठा mwअगरiex_अगरace_comb curr_अगरace_comb;
	काष्ठा mwअगरiex_निजी *priv[MWIFIEX_MAX_BSS_NUM];
	u8 priv_num;
	स्थिर काष्ठा firmware *firmware;
	अक्षर fw_name[32];
	पूर्णांक winner;
	काष्ठा device *dev;
	काष्ठा wiphy *wiphy;
	u8 perm_addr[ETH_ALEN];
	अचिन्हित दीर्घ work_flags;
	u32 fw_release_number;
	u8 पूर्णांकf_hdr_len;
	u16 init_रुको_q_woken;
	रुको_queue_head_t init_रुको_q;
	व्योम *card;
	काष्ठा mwअगरiex_अगर_ops अगर_ops;
	atomic_t bypass_tx_pending;
	atomic_t rx_pending;
	atomic_t tx_pending;
	atomic_t cmd_pending;
	atomic_t tx_hw_pending;
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा मुख्य_work;
	काष्ठा workqueue_काष्ठा *rx_workqueue;
	काष्ठा work_काष्ठा rx_work;
	काष्ठा workqueue_काष्ठा *dfs_workqueue;
	काष्ठा work_काष्ठा dfs_work;
	bool rx_work_enabled;
	bool rx_processing;
	bool delay_मुख्य_work;
	bool rx_locked;
	bool मुख्य_locked;
	काष्ठा mwअगरiex_bss_prio_tbl bss_prio_tbl[MWIFIEX_MAX_BSS_NUM];
	/* spin lock क्रम मुख्य process */
	spinlock_t मुख्य_proc_lock;
	u32 mwअगरiex_processing;
	u8 more_task_flag;
	u16 tx_buf_size;
	u16 curr_tx_buf_size;
	/* sdio single port rx aggregation capability */
	bool host_disable_sdio_rx_aggr;
	bool sdio_rx_aggr_enable;
	u16 sdio_rx_block_size;
	u32 ioport;
	क्रमागत MWIFIEX_HARDWARE_STATUS hw_status;
	u16 number_of_antenna;
	u32 fw_cap_info;
	/* spin lock क्रम पूर्णांकerrupt handling */
	spinlock_t पूर्णांक_lock;
	u8 पूर्णांक_status;
	u32 event_cause;
	काष्ठा sk_buff *event_skb;
	u8 upld_buf[MWIFIEX_UPLD_SIZE];
	u8 data_sent;
	u8 cmd_sent;
	u8 cmd_resp_received;
	u8 event_received;
	u8 data_received;
	u16 seq_num;
	काष्ठा cmd_ctrl_node *cmd_pool;
	काष्ठा cmd_ctrl_node *curr_cmd;
	/* spin lock क्रम command */
	spinlock_t mwअगरiex_cmd_lock;
	u16 last_init_cmd;
	काष्ठा समयr_list cmd_समयr;
	काष्ठा list_head cmd_मुक्त_q;
	/* spin lock क्रम cmd_मुक्त_q */
	spinlock_t cmd_मुक्त_q_lock;
	काष्ठा list_head cmd_pending_q;
	/* spin lock क्रम cmd_pending_q */
	spinlock_t cmd_pending_q_lock;
	काष्ठा list_head scan_pending_q;
	/* spin lock क्रम scan_pending_q */
	spinlock_t scan_pending_q_lock;
	/* spin lock क्रम RX processing routine */
	spinlock_t rx_proc_lock;
	काष्ठा sk_buff_head tx_data_q;
	atomic_t tx_queued;
	u32 scan_processing;
	u16 region_code;
	काष्ठा mwअगरiex_802_11d_करोमुख्य_reg करोमुख्य_reg;
	u16 scan_probes;
	u32 scan_mode;
	u16 specअगरic_scan_समय;
	u16 active_scan_समय;
	u16 passive_scan_समय;
	u16 scan_chan_gap_समय;
	u8 fw_bands;
	u8 adhoc_start_band;
	u8 config_bands;
	काष्ठा mwअगरiex_chan_scan_param_set *scan_channels;
	u8 tx_lock_flag;
	काष्ठा mwअगरiex_sleep_params sleep_params;
	काष्ठा mwअगरiex_sleep_period sleep_period;
	u16 ps_mode;
	u32 ps_state;
	u8 need_to_wakeup;
	u16 multiple_dtim;
	u16 local_listen_पूर्णांकerval;
	u16 null_pkt_पूर्णांकerval;
	काष्ठा sk_buff *sleep_cfm;
	u16 bcn_miss_समय_out;
	u16 adhoc_awake_period;
	u8 is_deep_sleep;
	u8 delay_null_pkt;
	u16 delay_to_ps;
	u16 enhanced_ps_mode;
	u8 pm_wakeup_card_req;
	u16 gen_null_pkt;
	u16 pps_uapsd_mode;
	u32 pm_wakeup_fw_try;
	काष्ठा समयr_list wakeup_समयr;
	काष्ठा mwअगरiex_hs_config_param hs_cfg;
	u8 hs_activated;
	u16 hs_activate_रुको_q_woken;
	रुको_queue_head_t hs_activate_रुको_q;
	u8 event_body[MAX_EVENT_SIZE];
	u32 hw_करोt_11n_dev_cap;
	u8 hw_dev_mcs_support;
	u8 user_dev_mcs_support;
	u8 adhoc_11n_enabled;
	u8 sec_chan_offset;
	काष्ठा mwअगरiex_dbg dbg;
	u8 arp_filter[ARP_FILTER_MAX_BUF_SIZE];
	u32 arp_filter_size;
	काष्ठा mwअगरiex_रुको_queue cmd_रुको_q;
	u8 scan_रुको_q_woken;
	spinlock_t queue_lock;		/* lock क्रम tx queues */
	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	u16 max_mgmt_ie_index;
	स्थिर काष्ठा firmware *cal_data;
	काष्ठा device_node *dt_node;

	/* 11AC */
	u32 is_hw_11ac_capable;
	u32 hw_करोt_11ac_dev_cap;
	u32 hw_करोt_11ac_mcs_support;
	u32 usr_करोt_11ac_dev_cap_bg;
	u32 usr_करोt_11ac_dev_cap_a;
	u32 usr_करोt_11ac_mcs_support;

	atomic_t pending_bridged_pkts;

	/* For synchronizing FW initialization with device lअगरecycle. */
	काष्ठा completion *fw_करोne;
	bool is_up;

	bool ext_scan;
	u8 fw_api_ver;
	u8 key_api_major_ver, key_api_minor_ver;
	u8 max_p2p_conn, max_sta_conn;
	काष्ठा memory_type_mapping *mem_type_mapping_tbl;
	u8 num_mem_types;
	bool scan_chan_gap_enabled;
	काष्ठा sk_buff_head rx_data_q;
	bool mfg_mode;
	काष्ठा mwअगरiex_chan_stats *chan_stats;
	u32 num_in_chan_stats;
	पूर्णांक survey_idx;
	bool स्वतः_tdls;
	u8 coex_scan;
	u8 coex_min_scan_समय;
	u8 coex_max_scan_समय;
	u8 coex_win_size;
	u8 coex_tx_win_size;
	u8 coex_rx_win_size;
	bool drcs_enabled;
	u8 active_scan_triggered;
	bool usb_mc_status;
	bool usb_mc_setup;
	काष्ठा cfg80211_wowlan_nd_info *nd_info;
	काष्ठा ieee80211_regकरोमुख्य *regd;

	/* Wake-on-WLAN (WoWLAN) */
	पूर्णांक irq_wakeup;
	bool wake_by_wअगरi;
	/* Aggregation parameters*/
	काष्ठा bus_aggr_params bus_aggr;
	/* Device dump data/length */
	व्योम *devdump_data;
	पूर्णांक devdump_len;
	काष्ठा समयr_list devdump_समयr;
पूर्ण;

व्योम mwअगरiex_process_tx_queue(काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_init_lock_list(काष्ठा mwअगरiex_adapter *adapter);

व्योम mwअगरiex_set_trans_start(काष्ठा net_device *dev);

व्योम mwअगरiex_stop_net_dev_queue(काष्ठा net_device *netdev,
		काष्ठा mwअगरiex_adapter *adapter);

व्योम mwअगरiex_wake_up_net_dev_queue(काष्ठा net_device *netdev,
		काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_init_priv(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_मुक्त_priv(काष्ठा mwअगरiex_निजी *priv);

पूर्णांक mwअगरiex_init_fw(काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_init_fw_complete(काष्ठा mwअगरiex_adapter *adapter);

व्योम mwअगरiex_shutकरोwn_drv(काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_dnld_fw(काष्ठा mwअगरiex_adapter *, काष्ठा mwअगरiex_fw_image *);

पूर्णांक mwअगरiex_recv_packet(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_uap_recv_packet(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा sk_buff *skb);

पूर्णांक mwअगरiex_process_mgmt_packet(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा sk_buff *skb);

पूर्णांक mwअगरiex_process_event(काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_complete_cmd(काष्ठा mwअगरiex_adapter *adapter,
			 काष्ठा cmd_ctrl_node *cmd_node);

पूर्णांक mwअगरiex_send_cmd(काष्ठा mwअगरiex_निजी *priv, u16 cmd_no,
		     u16 cmd_action, u32 cmd_oid, व्योम *data_buf, bool sync);

व्योम mwअगरiex_cmd_समयout_func(काष्ठा समयr_list *t);

पूर्णांक mwअगरiex_get_debug_info(काष्ठा mwअगरiex_निजी *,
			   काष्ठा mwअगरiex_debug_info *);

पूर्णांक mwअगरiex_alloc_cmd_buffer(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_मुक्त_cmd_buffer(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_मुक्त_cmd_buffers(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_cancel_all_pending_cmd(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_cancel_pending_scan_cmd(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_cancel_scan(काष्ठा mwअगरiex_adapter *adapter);

व्योम mwअगरiex_recycle_cmd_node(काष्ठा mwअगरiex_adapter *adapter,
			      काष्ठा cmd_ctrl_node *cmd_node);

व्योम mwअगरiex_insert_cmd_to_pending_q(काष्ठा mwअगरiex_adapter *adapter,
				     काष्ठा cmd_ctrl_node *cmd_node);

पूर्णांक mwअगरiex_exec_next_cmd(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_process_cmdresp(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_handle_rx_packet(काष्ठा mwअगरiex_adapter *adapter,
			     काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_process_tx(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb,
		       काष्ठा mwअगरiex_tx_param *tx_param);
पूर्णांक mwअगरiex_send_null_packet(काष्ठा mwअगरiex_निजी *priv, u8 flags);
पूर्णांक mwअगरiex_ग_लिखो_data_complete(काष्ठा mwअगरiex_adapter *adapter,
				काष्ठा sk_buff *skb, पूर्णांक aggr, पूर्णांक status);
व्योम mwअगरiex_clean_txrx(काष्ठा mwअगरiex_निजी *priv);
u8 mwअगरiex_check_last_packet_indication(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_check_ps_cond(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_process_sleep_confirm_resp(काष्ठा mwअगरiex_adapter *, u8 *,
					u32);
पूर्णांक mwअगरiex_cmd_enh_घातer_mode(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *cmd,
			       u16 cmd_action, uपूर्णांक16_t ps_biपंचांगap,
			       काष्ठा mwअगरiex_ds_स्वतः_ds *स्वतः_ds);
पूर्णांक mwअगरiex_ret_enh_घातer_mode(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *resp,
			       काष्ठा mwअगरiex_ds_pm_cfg *pm_cfg);
व्योम mwअगरiex_process_hs_config(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_hs_activated_event(काष्ठा mwअगरiex_निजी *priv,
					u8 activated);
पूर्णांक mwअगरiex_set_hs_params(काष्ठा mwअगरiex_निजी *priv, u16 action,
			  पूर्णांक cmd_type, काष्ठा mwअगरiex_ds_hs_cfg *hs_cfg);
पूर्णांक mwअगरiex_ret_802_11_hs_cfg(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp);
पूर्णांक mwअगरiex_process_rx_packet(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_sta_prepare_cmd(काष्ठा mwअगरiex_निजी *, uपूर्णांक16_t cmd_no,
			    u16 cmd_action, u32 cmd_oid,
			    व्योम *data_buf, व्योम *cmd_buf);
पूर्णांक mwअगरiex_uap_prepare_cmd(काष्ठा mwअगरiex_निजी *priv, uपूर्णांक16_t cmd_no,
			    u16 cmd_action, u32 cmd_oid,
			    व्योम *data_buf, व्योम *cmd_buf);
पूर्णांक mwअगरiex_process_sta_cmdresp(काष्ठा mwअगरiex_निजी *, u16 cmdresp_no,
				काष्ठा host_cmd_ds_command *resp);
पूर्णांक mwअगरiex_process_sta_rx_packet(काष्ठा mwअगरiex_निजी *,
				  काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_process_uap_rx_packet(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_handle_uap_rx_क्रमward(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_process_sta_event(काष्ठा mwअगरiex_निजी *);
पूर्णांक mwअगरiex_process_uap_event(काष्ठा mwअगरiex_निजी *);
व्योम mwअगरiex_delete_all_station_list(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_wmm_del_peer_ra_list(काष्ठा mwअगरiex_निजी *priv,
				  स्थिर u8 *ra_addr);
व्योम *mwअगरiex_process_sta_txpd(काष्ठा mwअगरiex_निजी *, काष्ठा sk_buff *skb);
व्योम *mwअगरiex_process_uap_txpd(काष्ठा mwअगरiex_निजी *, काष्ठा sk_buff *skb);
पूर्णांक mwअगरiex_sta_init_cmd(काष्ठा mwअगरiex_निजी *, u8 first_sta, bool init);
पूर्णांक mwअगरiex_cmd_802_11_scan(काष्ठा host_cmd_ds_command *cmd,
			    काष्ठा mwअगरiex_scan_cmd_config *scan_cfg);
व्योम mwअगरiex_queue_scan_cmd(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा cmd_ctrl_node *cmd_node);
पूर्णांक mwअगरiex_ret_802_11_scan(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा host_cmd_ds_command *resp);
s32 mwअगरiex_ssid_cmp(काष्ठा cfg80211_ssid *ssid1, काष्ठा cfg80211_ssid *ssid2);
पूर्णांक mwअगरiex_associate(काष्ठा mwअगरiex_निजी *priv,
		      काष्ठा mwअगरiex_bssdescriptor *bss_desc);
पूर्णांक mwअगरiex_cmd_802_11_associate(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा host_cmd_ds_command *cmd,
				 काष्ठा mwअगरiex_bssdescriptor *bss_desc);
पूर्णांक mwअगरiex_ret_802_11_associate(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा host_cmd_ds_command *resp);
व्योम mwअगरiex_reset_connect_state(काष्ठा mwअगरiex_निजी *priv, u16 reason,
				 bool from_ap);
u8 mwअगरiex_band_to_radio_type(u8 band);
पूर्णांक mwअगरiex_deauthenticate(काष्ठा mwअगरiex_निजी *priv, u8 *mac);
व्योम mwअगरiex_deauthenticate_all(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_adhoc_start(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा cfg80211_ssid *adhoc_ssid);
पूर्णांक mwअगरiex_adhoc_join(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा mwअगरiex_bssdescriptor *bss_desc);
पूर्णांक mwअगरiex_cmd_802_11_ad_hoc_start(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा host_cmd_ds_command *cmd,
				    काष्ठा cfg80211_ssid *req_ssid);
पूर्णांक mwअगरiex_cmd_802_11_ad_hoc_join(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   काष्ठा mwअगरiex_bssdescriptor *bss_desc);
पूर्णांक mwअगरiex_ret_802_11_ad_hoc(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp);
पूर्णांक mwअगरiex_cmd_802_11_bg_scan_query(काष्ठा host_cmd_ds_command *cmd);
काष्ठा mwअगरiex_chan_freq_घातer *mwअगरiex_get_cfp(काष्ठा mwअगरiex_निजी *priv,
						u8 band, u16 channel, u32 freq);
u32 mwअगरiex_index_to_data_rate(काष्ठा mwअगरiex_निजी *priv,
			       u8 index, u8 ht_info);
u32 mwअगरiex_index_to_acs_data_rate(काष्ठा mwअगरiex_निजी *priv,
				   u8 index, u8 ht_info);
u32 mwअगरiex_find_freq_from_band_chan(u8, u8);
पूर्णांक mwअगरiex_cmd_append_vsie_tlv(काष्ठा mwअगरiex_निजी *priv, u16 vsie_mask,
				u8 **buffer);
u32 mwअगरiex_get_active_data_rates(काष्ठा mwअगरiex_निजी *priv,
				    u8 *rates);
u32 mwअगरiex_get_supported_rates(काष्ठा mwअगरiex_निजी *priv, u8 *rates);
u32 mwअगरiex_get_rates_from_cfg80211(काष्ठा mwअगरiex_निजी *priv,
				    u8 *rates, u8 radio_type);
u8 mwअगरiex_is_rate_स्वतः(काष्ठा mwअगरiex_निजी *priv);
बाह्य u16 region_code_index[MWIFIEX_MAX_REGION_CODE];
व्योम mwअगरiex_save_curr_bcn(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_मुक्त_curr_bcn(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_cmd_get_hw_spec(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा host_cmd_ds_command *cmd);
पूर्णांक mwअगरiex_ret_get_hw_spec(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा host_cmd_ds_command *resp);
पूर्णांक is_command_pending(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_init_priv_params(काष्ठा mwअगरiex_निजी *priv,
						काष्ठा net_device *dev);
पूर्णांक mwअगरiex_set_secure_params(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_uap_bss_param *bss_config,
			      काष्ठा cfg80211_ap_settings *params);
व्योम mwअगरiex_set_ht_params(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			   काष्ठा cfg80211_ap_settings *params);
व्योम mwअगरiex_set_vht_params(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			    काष्ठा cfg80211_ap_settings *params);
व्योम mwअगरiex_set_tpc_params(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			    काष्ठा cfg80211_ap_settings *params);
व्योम mwअगरiex_set_uap_rates(काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			   काष्ठा cfg80211_ap_settings *params);
व्योम mwअगरiex_set_vht_width(काष्ठा mwअगरiex_निजी *priv,
			   क्रमागत nl80211_chan_width width,
			   bool ap_11ac_disable);
व्योम
mwअगरiex_set_wmm_params(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
		       काष्ठा cfg80211_ap_settings *params);
व्योम mwअगरiex_set_ba_params(काष्ठा mwअगरiex_निजी *priv);

व्योम mwअगरiex_update_ampdu_txwinsize(काष्ठा mwअगरiex_adapter *pmadapter);
व्योम mwअगरiex_bt_coex_wlan_param_update_event(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा sk_buff *event_skb);

व्योम mwअगरiex_set_11ac_ba_params(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_cmd_802_11_scan_ext(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *cmd,
				व्योम *data_buf);
पूर्णांक mwअगरiex_ret_802_11_scan_ext(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *resp);
पूर्णांक mwअगरiex_handle_event_ext_scan_report(काष्ठा mwअगरiex_निजी *priv,
					 व्योम *buf);
पूर्णांक mwअगरiex_cmd_802_11_bg_scan_config(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा host_cmd_ds_command *cmd,
				      व्योम *data_buf);
पूर्णांक mwअगरiex_stop_bg_scan(काष्ठा mwअगरiex_निजी *priv);

/*
 * This function checks अगर the queuing is RA based or not.
 */
अटल अंतरभूत u8
mwअगरiex_queuing_ra_based(काष्ठा mwअगरiex_निजी *priv)
अणु
	/*
	 * Currently we assume अगर we are in Infra, then DA=RA. This might not be
	 * true in the future
	 */
	अगर ((priv->bss_mode == NL80211_IFTYPE_STATION ||
	     priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT) &&
	    (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA))
		वापस false;

	वापस true;
पूर्ण

/*
 * This function copies rates.
 */
अटल अंतरभूत u32
mwअगरiex_copy_rates(u8 *dest, u32 pos, u8 *src, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len && src[i]; i++, pos++) अणु
		अगर (pos >= MWIFIEX_SUPPORTED_RATES)
			अवरोध;
		dest[pos] = src[i];
	पूर्ण

	वापस pos;
पूर्ण

/*
 * This function वापसs the correct निजी काष्ठाure poपूर्णांकer based
 * upon the BSS type and BSS number.
 */
अटल अंतरभूत काष्ठा mwअगरiex_निजी *
mwअगरiex_get_priv_by_id(काष्ठा mwअगरiex_adapter *adapter,
		       u8 bss_num, u8 bss_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			अगर ((adapter->priv[i]->bss_num == bss_num) &&
			    (adapter->priv[i]->bss_type == bss_type))
				अवरोध;
		पूर्ण
	पूर्ण
	वापस ((i < adapter->priv_num) ? adapter->priv[i] : शून्य);
पूर्ण

/*
 * This function वापसs the first available निजी काष्ठाure poपूर्णांकer
 * based upon the BSS role.
 */
अटल अंतरभूत काष्ठा mwअगरiex_निजी *
mwअगरiex_get_priv(काष्ठा mwअगरiex_adapter *adapter,
		 क्रमागत mwअगरiex_bss_role bss_role)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			अगर (bss_role == MWIFIEX_BSS_ROLE_ANY ||
			    GET_BSS_ROLE(adapter->priv[i]) == bss_role)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ((i < adapter->priv_num) ? adapter->priv[i] : शून्य);
पूर्ण

/*
 * This function checks available bss_num when adding new पूर्णांकerface or
 * changing पूर्णांकerface type.
 */
अटल अंतरभूत u8
mwअगरiex_get_unused_bss_num(काष्ठा mwअगरiex_adapter *adapter, u8 bss_type)
अणु
	u8 i, j;
	पूर्णांक index[MWIFIEX_MAX_BSS_NUM];

	स_रखो(index, 0, माप(index));
	क्रम (i = 0; i < adapter->priv_num; i++)
		अगर (adapter->priv[i]) अणु
			अगर (adapter->priv[i]->bss_type == bss_type &&
			    !(adapter->priv[i]->bss_mode ==
			      NL80211_IFTYPE_UNSPECIFIED)) अणु
				index[adapter->priv[i]->bss_num] = 1;
			पूर्ण
		पूर्ण
	क्रम (j = 0; j < MWIFIEX_MAX_BSS_NUM; j++)
		अगर (!index[j])
			वापस j;
	वापस -1;
पूर्ण

/*
 * This function वापसs the first available unused निजी काष्ठाure poपूर्णांकer.
 */
अटल अंतरभूत काष्ठा mwअगरiex_निजी *
mwअगरiex_get_unused_priv_by_bss_type(काष्ठा mwअगरiex_adapter *adapter,
				    u8 bss_type)
अणु
	u8 i;

	क्रम (i = 0; i < adapter->priv_num; i++)
		अगर (adapter->priv[i]->bss_mode ==
		   NL80211_IFTYPE_UNSPECIFIED) अणु
			adapter->priv[i]->bss_num =
			mwअगरiex_get_unused_bss_num(adapter, bss_type);
			अवरोध;
		पूर्ण

	वापस ((i < adapter->priv_num) ? adapter->priv[i] : शून्य);
पूर्ण

/*
 * This function वापसs the driver निजी काष्ठाure of a network device.
 */
अटल अंतरभूत काष्ठा mwअगरiex_निजी *
mwअगरiex_netdev_get_priv(काष्ठा net_device *dev)
अणु
	वापस (काष्ठा mwअगरiex_निजी *) (*(अचिन्हित दीर्घ *) netdev_priv(dev));
पूर्ण

/*
 * This function checks अगर a skb holds a management frame.
 */
अटल अंतरभूत bool mwअगरiex_is_skb_mgmt_frame(काष्ठा sk_buff *skb)
अणु
	वापस (get_unaligned_le32(skb->data) == PKT_TYPE_MGMT);
पूर्ण

/* This function retrieves channel बंदd क्रम operation by Channel
 * Switch Announcement.
 */
अटल अंतरभूत u8
mwअगरiex_11h_get_csa_बंदd_channel(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (!priv->csa_chan)
		वापस 0;

	/* Clear csa channel, अगर DFS channel move समय has passed */
	अगर (समय_after(jअगरfies, priv->csa_expire_समय)) अणु
		priv->csa_chan = 0;
		priv->csa_expire_समय = 0;
	पूर्ण

	वापस priv->csa_chan;
पूर्ण

अटल अंतरभूत u8 mwअगरiex_is_any_पूर्णांकf_active(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_निजी *priv_num;
	पूर्णांक i;

	क्रम (i = 0; i < priv->adapter->priv_num; i++) अणु
		priv_num = priv->adapter->priv[i];
		अगर (priv_num) अणु
			अगर ((GET_BSS_ROLE(priv_num) == MWIFIEX_BSS_ROLE_UAP &&
			     priv_num->bss_started) ||
			    (GET_BSS_ROLE(priv_num) == MWIFIEX_BSS_ROLE_STA &&
			     priv_num->media_connected))
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u8 mwअगरiex_is_tdls_link_setup(u8 status)
अणु
	चयन (status) अणु
	हाल TDLS_SETUP_COMPLETE:
	हाल TDLS_CHAN_SWITCHING:
	हाल TDLS_IN_BASE_CHAN:
	हाल TDLS_IN_OFF_CHAN:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/* Disable platक्रमm specअगरic wakeup पूर्णांकerrupt */
अटल अंतरभूत व्योम mwअगरiex_disable_wake(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (adapter->irq_wakeup >= 0) अणु
		disable_irq_wake(adapter->irq_wakeup);
		disable_irq(adapter->irq_wakeup);
		अगर (adapter->wake_by_wअगरi)
			/* Unकरो our disable, since पूर्णांकerrupt handler alपढ़ोy
			 * did this.
			 */
			enable_irq(adapter->irq_wakeup);

	पूर्ण
पूर्ण

/* Enable platक्रमm specअगरic wakeup पूर्णांकerrupt */
अटल अंतरभूत व्योम mwअगरiex_enable_wake(काष्ठा mwअगरiex_adapter *adapter)
अणु
	/* Enable platक्रमm specअगरic wakeup पूर्णांकerrupt */
	अगर (adapter->irq_wakeup >= 0) अणु
		adapter->wake_by_wअगरi = false;
		enable_irq(adapter->irq_wakeup);
		enable_irq_wake(adapter->irq_wakeup);
	पूर्ण
पूर्ण

पूर्णांक mwअगरiex_init_shutकरोwn_fw(काष्ठा mwअगरiex_निजी *priv,
			     u32 func_init_shutकरोwn);

पूर्णांक mwअगरiex_add_card(व्योम *card, काष्ठा completion *fw_करोne,
		     काष्ठा mwअगरiex_अगर_ops *अगर_ops, u8 अगरace_type,
		     काष्ठा device *dev);
पूर्णांक mwअगरiex_हटाओ_card(काष्ठा mwअगरiex_adapter *adapter);

व्योम mwअगरiex_get_version(काष्ठा mwअगरiex_adapter *adapter, अक्षर *version,
			 पूर्णांक maxlen);
पूर्णांक mwअगरiex_request_set_multicast_list(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा mwअगरiex_multicast_list *mcast_list);
पूर्णांक mwअगरiex_copy_mcast_addr(काष्ठा mwअगरiex_multicast_list *mlist,
			    काष्ठा net_device *dev);
पूर्णांक mwअगरiex_रुको_queue_complete(काष्ठा mwअगरiex_adapter *adapter,
				काष्ठा cmd_ctrl_node *cmd_queued);
पूर्णांक mwअगरiex_bss_start(काष्ठा mwअगरiex_निजी *priv, काष्ठा cfg80211_bss *bss,
		      काष्ठा cfg80211_ssid *req_ssid);
पूर्णांक mwअगरiex_cancel_hs(काष्ठा mwअगरiex_निजी *priv, पूर्णांक cmd_type);
पूर्णांक mwअगरiex_enable_hs(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_disable_स्वतः_ds(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_drv_get_data_rate(काष्ठा mwअगरiex_निजी *priv, u32 *rate);
पूर्णांक mwअगरiex_request_scan(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा cfg80211_ssid *req_ssid);
पूर्णांक mwअगरiex_scan_networks(काष्ठा mwअगरiex_निजी *priv,
			  स्थिर काष्ठा mwअगरiex_user_scan_cfg *user_scan_in);
पूर्णांक mwअगरiex_set_radio(काष्ठा mwअगरiex_निजी *priv, u8 option);

पूर्णांक mwअगरiex_set_encode(काष्ठा mwअगरiex_निजी *priv, काष्ठा key_params *kp,
		       स्थिर u8 *key, पूर्णांक key_len, u8 key_index,
		       स्थिर u8 *mac_addr, पूर्णांक disable);

पूर्णांक mwअगरiex_set_gen_ie(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ie, पूर्णांक ie_len);

पूर्णांक mwअगरiex_get_ver_ext(काष्ठा mwअगरiex_निजी *priv, u32 version_str_sel);

पूर्णांक mwअगरiex_reमुख्य_on_chan_cfg(काष्ठा mwअगरiex_निजी *priv, u16 action,
			       काष्ठा ieee80211_channel *chan,
			       अचिन्हित पूर्णांक duration);

पूर्णांक mwअगरiex_get_stats_info(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा mwअगरiex_ds_get_stats *log);

पूर्णांक mwअगरiex_reg_ग_लिखो(काष्ठा mwअगरiex_निजी *priv, u32 reg_type,
		      u32 reg_offset, u32 reg_value);

पूर्णांक mwअगरiex_reg_पढ़ो(काष्ठा mwअगरiex_निजी *priv, u32 reg_type,
		     u32 reg_offset, u32 *value);

पूर्णांक mwअगरiex_eeprom_पढ़ो(काष्ठा mwअगरiex_निजी *priv, u16 offset, u16 bytes,
			u8 *value);

पूर्णांक mwअगरiex_set_11n_httx_cfg(काष्ठा mwअगरiex_निजी *priv, पूर्णांक data);

पूर्णांक mwअगरiex_get_11n_httx_cfg(काष्ठा mwअगरiex_निजी *priv, पूर्णांक *data);

पूर्णांक mwअगरiex_set_tx_rate_cfg(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tx_rate_index);

पूर्णांक mwअगरiex_get_tx_rate_cfg(काष्ठा mwअगरiex_निजी *priv, पूर्णांक *tx_rate_index);

पूर्णांक mwअगरiex_drv_set_घातer(काष्ठा mwअगरiex_निजी *priv, u32 *ps_mode);

पूर्णांक mwअगरiex_drv_get_driver_version(काष्ठा mwअगरiex_adapter *adapter,
				   अक्षर *version, पूर्णांक max_len);

पूर्णांक mwअगरiex_set_tx_घातer(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा mwअगरiex_घातer_cfg *घातer_cfg);

पूर्णांक mwअगरiex_मुख्य_process(काष्ठा mwअगरiex_adapter *);

पूर्णांक mwअगरiex_queue_tx_pkt(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb);

पूर्णांक mwअगरiex_get_bss_info(काष्ठा mwअगरiex_निजी *,
			 काष्ठा mwअगरiex_bss_info *);
पूर्णांक mwअगरiex_fill_new_bss_desc(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा cfg80211_bss *bss,
			      काष्ठा mwअगरiex_bssdescriptor *bss_desc);
पूर्णांक mwअगरiex_update_bss_desc_with_ie(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा mwअगरiex_bssdescriptor *bss_entry);
पूर्णांक mwअगरiex_check_network_compatibility(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा mwअगरiex_bssdescriptor *bss_desc);

u8 mwअगरiex_chan_type_to_sec_chan_offset(क्रमागत nl80211_channel_type chan_type);
u8 mwअगरiex_get_chan_type(काष्ठा mwअगरiex_निजी *priv);

काष्ठा wireless_dev *mwअगरiex_add_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
					      स्थिर अक्षर *name,
					      अचिन्हित अक्षर name_assign_type,
					      क्रमागत nl80211_अगरtype type,
					      काष्ठा vअगर_params *params);
पूर्णांक mwअगरiex_del_भव_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);

व्योम mwअगरiex_set_sys_config_invalid_data(काष्ठा mwअगरiex_uap_bss_param *config);

पूर्णांक mwअगरiex_add_wowlan_magic_pkt_filter(काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_set_mgmt_ies(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा cfg80211_beacon_data *data);
पूर्णांक mwअगरiex_del_mgmt_ies(काष्ठा mwअगरiex_निजी *priv);
u8 *mwअगरiex_11d_code_2_region(u8 code);
व्योम mwअगरiex_uap_set_channel(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			     काष्ठा cfg80211_chan_def chandef);
पूर्णांक mwअगरiex_config_start_uap(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_uap_bss_param *bss_cfg);
व्योम mwअगरiex_uap_del_sta_data(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_sta_node *node);

व्योम mwअगरiex_config_uap_11d(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा cfg80211_beacon_data *beacon_data);

व्योम mwअगरiex_init_11h_params(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_is_11h_active(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_11h_activate(काष्ठा mwअगरiex_निजी *priv, bool flag);

व्योम mwअगरiex_11h_process_join(काष्ठा mwअगरiex_निजी *priv, u8 **buffer,
			      काष्ठा mwअगरiex_bssdescriptor *bss_desc);
पूर्णांक mwअगरiex_11h_handle_event_chanswann(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_dnld_dt_cfgdata(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा device_node *node, स्थिर अक्षर *prefix);
व्योम mwअगरiex_dnld_txpwr_table(काष्ठा mwअगरiex_निजी *priv);

बाह्य स्थिर काष्ठा ethtool_ops mwअगरiex_ethtool_ops;

व्योम mwअगरiex_del_all_sta_list(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_del_sta_entry(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac);
व्योम
mwअगरiex_set_sta_ht_cap(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ies,
		       पूर्णांक ies_len, काष्ठा mwअगरiex_sta_node *node);
काष्ठा mwअगरiex_sta_node *
mwअगरiex_add_sta_entry(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac);
काष्ठा mwअगरiex_sta_node *
mwअगरiex_get_sta_entry(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac);
u8 mwअगरiex_is_tdls_chan_चयनing(काष्ठा mwअगरiex_निजी *priv);
u8 mwअगरiex_is_tdls_off_chan(काष्ठा mwअगरiex_निजी *priv);
u8 mwअगरiex_is_send_cmd_allowed(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_send_tdls_data_frame(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer,
				 u8 action_code, u8 dialog_token,
				 u16 status_code, स्थिर u8 *extra_ies,
				 माप_प्रकार extra_ies_len);
पूर्णांक mwअगरiex_send_tdls_action_frame(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer,
				   u8 action_code, u8 dialog_token,
				   u16 status_code, स्थिर u8 *extra_ies,
				   माप_प्रकार extra_ies_len);
व्योम mwअगरiex_process_tdls_action_frame(काष्ठा mwअगरiex_निजी *priv,
				       u8 *buf, पूर्णांक len);
पूर्णांक mwअगरiex_tdls_oper(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer, u8 action);
पूर्णांक mwअगरiex_get_tdls_link_status(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac);
पूर्णांक mwअगरiex_get_tdls_list(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा tdls_peer_info *buf);
व्योम mwअगरiex_disable_all_tdls_links(काष्ठा mwअगरiex_निजी *priv);
bool mwअगरiex_is_bss_in_11ac_mode(काष्ठा mwअगरiex_निजी *priv);
u8 mwअगरiex_get_center_freq_index(काष्ठा mwअगरiex_निजी *priv, u8 band,
				 u32 pri_chan, u8 chan_bw);
पूर्णांक mwअगरiex_init_channel_scan_gap(काष्ठा mwअगरiex_adapter *adapter);

पूर्णांक mwअगरiex_tdls_check_tx(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb);
व्योम mwअगरiex_flush_स्वतः_tdls_list(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_स्वतः_tdls_update_peer_status(काष्ठा mwअगरiex_निजी *priv,
					  स्थिर u8 *mac, u8 link_status);
व्योम mwअगरiex_स्वतः_tdls_update_peer_संकेत(काष्ठा mwअगरiex_निजी *priv,
					  u8 *mac, s8 snr, s8 nflr);
व्योम mwअगरiex_check_स्वतः_tdls(काष्ठा समयr_list *t);
व्योम mwअगरiex_add_स्वतः_tdls_peer(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac);
व्योम mwअगरiex_setup_स्वतः_tdls_समयr(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_clean_स्वतः_tdls(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_config_tdls_enable(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_config_tdls_disable(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_config_tdls_cs_params(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_stop_tdls_cs(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer_mac);
पूर्णांक mwअगरiex_start_tdls_cs(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer_mac,
			  u8 primary_chan, u8 second_chan_offset, u8 band);

पूर्णांक mwअगरiex_cmd_issue_chan_report_request(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा host_cmd_ds_command *cmd,
					  व्योम *data_buf);
पूर्णांक mwअगरiex_11h_handle_chanrpt_पढ़ोy(काष्ठा mwअगरiex_निजी *priv,
				     काष्ठा sk_buff *skb);

व्योम mwअगरiex_parse_tx_status_event(काष्ठा mwअगरiex_निजी *priv,
				   व्योम *event_body);

काष्ठा sk_buff *
mwअगरiex_clone_skb_क्रम_tx_status(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा sk_buff *skb, u8 flag, u64 *cookie);
व्योम mwअगरiex_dfs_cac_work_queue(काष्ठा work_काष्ठा *work);
व्योम mwअगरiex_dfs_chan_sw_work_queue(काष्ठा work_काष्ठा *work);
व्योम mwअगरiex_पात_cac(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_stop_radar_detection(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा cfg80211_chan_def *chandef);
पूर्णांक mwअगरiex_11h_handle_radar_detected(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा sk_buff *skb);

व्योम mwअगरiex_hist_data_set(काष्ठा mwअगरiex_निजी *priv, u8 rx_rate, s8 snr,
			   s8 nflr);
व्योम mwअगरiex_hist_data_reset(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_hist_data_add(काष्ठा mwअगरiex_निजी *priv,
			   u8 rx_rate, s8 snr, s8 nflr);
u8 mwअगरiex_adjust_data_rate(काष्ठा mwअगरiex_निजी *priv,
			    u8 rx_rate, u8 ht_info);

व्योम mwअगरiex_drv_info_dump(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_prepare_fw_dump_info(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_upload_device_dump(काष्ठा mwअगरiex_adapter *adapter);
व्योम *mwअगरiex_alloc_dma_align_buf(पूर्णांक rx_len, gfp_t flags);
व्योम mwअगरiex_fw_dump_event(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_queue_मुख्य_work(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_get_wakeup_reason(काष्ठा mwअगरiex_निजी *priv, u16 action,
			      पूर्णांक cmd_type,
			      काष्ठा mwअगरiex_ds_wakeup_reason *wakeup_reason);
पूर्णांक mwअगरiex_get_chan_info(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा mwअगरiex_channel_band *channel_band);
पूर्णांक mwअगरiex_ret_wakeup_reason(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp,
			      काष्ठा host_cmd_ds_wakeup_reason *wakeup_reason);
व्योम mwअगरiex_coex_ampdu_rxwinsize(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_11n_delba(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid);
पूर्णांक mwअगरiex_send_करोमुख्य_info_cmd_fw(काष्ठा wiphy *wiphy);
व्योम mwअगरiex_process_tx_छोड़ो_event(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा sk_buff *event);
व्योम mwअगरiex_process_multi_chan_event(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा sk_buff *event_skb);
व्योम mwअगरiex_multi_chan_resync(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_set_mac_address(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा net_device *dev,
			    bool बाह्यal, u8 *new_mac);
व्योम mwअगरiex_devdump_पंचांगo_func(अचिन्हित दीर्घ function_context);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम mwअगरiex_debugfs_init(व्योम);
व्योम mwअगरiex_debugfs_हटाओ(व्योम);

व्योम mwअगरiex_dev_debugfs_init(काष्ठा mwअगरiex_निजी *priv);
व्योम mwअगरiex_dev_debugfs_हटाओ(काष्ठा mwअगरiex_निजी *priv);
#पूर्ण_अगर
पूर्णांक mwअगरiex_reinit_sw(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_shutकरोwn_sw(काष्ठा mwअगरiex_adapter *adapter);
#पूर्ण_अगर /* !_MWIFIEX_MAIN_H_ */
