<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   Driver क्रम KeyStream IEEE802.11 b/g wireless LAN cards.
 *
 *   Copyright (C) 2006-2008 KeyStream Corp.
 *   Copyright (C) 2009 Renesas Technology Corp.
 */

#अगर_अघोषित _KS_WLAN_H
#घोषणा _KS_WLAN_H

#समावेश <linux/atomic.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/completion.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/wireless.h>

काष्ठा ks_wlan_parameter अणु
	u8 operation_mode;
	u8 channel;
	u8 tx_rate;
	काष्ठा अणु
		u8 size;
		u8 body[16];
	पूर्ण rate_set;
	u8 bssid[ETH_ALEN];
	काष्ठा अणु
		u8 size;
		u8 body[32 + 1];
	पूर्ण ssid;
	u8 preamble;
	u8 घातer_mgmt;
	u32 scan_type;
#घोषणा BEACON_LOST_COUNT_MAX 65535
	u32 beacon_lost_count;
	u32 rts;
	u32 fragment;
	u32 privacy_invoked;
	u32 wep_index;
	काष्ठा अणु
		u8 size;
		u8 val[13 * 2 + 1];
	पूर्ण wep_key[4];
	u16 authenticate_type;
	u16 phy_type;
	u16 cts_mode;
	u16 phy_info_समयr;
पूर्ण;

क्रमागत अणु
	DEVICE_STATE_OFF = 0,	/* this means hw_unavailable is != 0 */
	DEVICE_STATE_PREBOOT,	/* we are in a pre-boot state (empty RAM) */
	DEVICE_STATE_BOOT,	/* boot state (fw upload, run fw) */
	DEVICE_STATE_PREINIT,	/* pre-init state */
	DEVICE_STATE_INIT,	/* init state (restore MIB backup to device) */
	DEVICE_STATE_READY,	/* driver&device are in operational state */
	DEVICE_STATE_SLEEP	/* device in sleep mode */
पूर्ण;

/* SME flag */
#घोषणा SME_MODE_SET	    BIT(0)
#घोषणा SME_RTS             BIT(1)
#घोषणा SME_FRAG            BIT(2)
#घोषणा SME_WEP_FLAG        BIT(3)
#घोषणा SME_WEP_INDEX       BIT(4)
#घोषणा SME_WEP_VAL1        BIT(5)
#घोषणा SME_WEP_VAL2        BIT(6)
#घोषणा SME_WEP_VAL3        BIT(7)
#घोषणा SME_WEP_VAL4        BIT(8)
#घोषणा SME_WEP_VAL_MASK    GENMASK(8, 5)
#घोषणा SME_RSN             BIT(9)
#घोषणा SME_RSN_MULTICAST   BIT(10)
#घोषणा SME_RSN_UNICAST	    BIT(11)
#घोषणा SME_RSN_AUTH	    BIT(12)

#घोषणा SME_AP_SCAN         BIT(13)
#घोषणा SME_MULTICAST       BIT(14)

/* SME Event */
क्रमागत अणु
	SME_START,

	SME_MULTICAST_REQUEST,
	SME_MACADDRESS_SET_REQUEST,
	SME_BSS_SCAN_REQUEST,
	SME_SET_FLAG,
	SME_SET_TXKEY,
	SME_SET_KEY1,
	SME_SET_KEY2,
	SME_SET_KEY3,
	SME_SET_KEY4,
	SME_SET_PMK_TSC,
	SME_SET_GMK1_TSC,
	SME_SET_GMK2_TSC,
	SME_SET_GMK3_TSC,
	SME_SET_PMKSA,
	SME_POW_MNGMT_REQUEST,
	SME_PHY_INFO_REQUEST,
	SME_MIC_FAILURE_REQUEST,
	SME_GET_MAC_ADDRESS,
	SME_GET_PRODUCT_VERSION,
	SME_STOP_REQUEST,
	SME_RTS_THRESHOLD_REQUEST,
	SME_FRAGMENTATION_THRESHOLD_REQUEST,
	SME_WEP_INDEX_REQUEST,
	SME_WEP_KEY1_REQUEST,
	SME_WEP_KEY2_REQUEST,
	SME_WEP_KEY3_REQUEST,
	SME_WEP_KEY4_REQUEST,
	SME_WEP_FLAG_REQUEST,
	SME_RSN_UCAST_REQUEST,
	SME_RSN_MCAST_REQUEST,
	SME_RSN_AUTH_REQUEST,
	SME_RSN_ENABLED_REQUEST,
	SME_RSN_MODE_REQUEST,
	SME_WPS_ENABLE_REQUEST,
	SME_WPS_PROBE_REQUEST,
	SME_SET_GAIN,
	SME_GET_GAIN,
	SME_SLEEP_REQUEST,
	SME_SET_REGION,
	SME_MODE_SET_REQUEST,
	SME_START_REQUEST,
	SME_GET_EEPROM_CKSUM,

	SME_MIC_FAILURE_CONFIRM,
	SME_START_CONFIRM,

	SME_MULTICAST_CONFIRM,
	SME_BSS_SCAN_CONFIRM,
	SME_GET_CURRENT_AP,
	SME_POW_MNGMT_CONFIRM,
	SME_PHY_INFO_CONFIRM,
	SME_STOP_CONFIRM,
	SME_RTS_THRESHOLD_CONFIRM,
	SME_FRAGMENTATION_THRESHOLD_CONFIRM,
	SME_WEP_INDEX_CONFIRM,
	SME_WEP_KEY1_CONFIRM,
	SME_WEP_KEY2_CONFIRM,
	SME_WEP_KEY3_CONFIRM,
	SME_WEP_KEY4_CONFIRM,
	SME_WEP_FLAG_CONFIRM,
	SME_RSN_UCAST_CONFIRM,
	SME_RSN_MCAST_CONFIRM,
	SME_RSN_AUTH_CONFIRM,
	SME_RSN_ENABLED_CONFIRM,
	SME_RSN_MODE_CONFIRM,
	SME_MODE_SET_CONFIRM,
	SME_SLEEP_CONFIRM,

	SME_RSN_SET_CONFIRM,
	SME_WEP_SET_CONFIRM,
	SME_TERMINATE,

	SME_EVENT_SIZE
पूर्ण;

/* SME Status */
क्रमागत अणु
	SME_IDLE,
	SME_SETUP,
	SME_DISCONNECT,
	SME_CONNECT
पूर्ण;

#घोषणा	SME_EVENT_BUFF_SIZE	128

काष्ठा sme_info अणु
	पूर्णांक sme_status;
	पूर्णांक event_buff[SME_EVENT_BUFF_SIZE];
	अचिन्हित पूर्णांक qhead;
	अचिन्हित पूर्णांक qtail;
	spinlock_t sme_spin;
	अचिन्हित दीर्घ sme_flag;
पूर्ण;

काष्ठा hostt अणु
	पूर्णांक buff[SME_EVENT_BUFF_SIZE];
	अचिन्हित पूर्णांक qhead;
	अचिन्हित पूर्णांक qtail;
पूर्ण;

#घोषणा RSN_IE_BODY_MAX 64
काष्ठा rsn_ie अणु
	u8 id;	/* 0xdd = WPA or 0x30 = RSN */
	u8 size;	/* max ? 255 ? */
	u8 body[RSN_IE_BODY_MAX];
पूर्ण __packed;

#घोषणा WPA_INFO_ELEM_ID 0xdd
#घोषणा RSN_INFO_ELEM_ID 0x30

#घोषणा WPS_IE_BODY_MAX 255
काष्ठा wps_ie अणु
	u8 id;	/* 221 'dd <len> 00 50 F2 04' */
	u8 size;	/* max ? 255 ? */
	u8 body[WPS_IE_BODY_MAX];
पूर्ण __packed;

काष्ठा local_ap अणु
	u8 bssid[6];
	u8 rssi;
	u8 sq;
	काष्ठा अणु
		u8 size;
		u8 body[32];
		u8 ssid_pad;
	पूर्ण ssid;
	काष्ठा अणु
		u8 size;
		u8 body[16];
		u8 rate_pad;
	पूर्ण rate_set;
	u16 capability;
	u8 channel;
	u8 noise;
	काष्ठा rsn_ie wpa_ie;
	काष्ठा rsn_ie rsn_ie;
	काष्ठा wps_ie wps_ie;
पूर्ण;

#घोषणा LOCAL_APLIST_MAX 31
#घोषणा LOCAL_CURRENT_AP LOCAL_APLIST_MAX
काष्ठा local_aplist अणु
	पूर्णांक size;
	काष्ठा local_ap ap[LOCAL_APLIST_MAX + 1];
पूर्ण;

काष्ठा local_gain अणु
	u8 tx_mode;
	u8 rx_mode;
	u8 tx_gain;
	u8 rx_gain;
पूर्ण;

काष्ठा local_eeprom_sum अणु
	u8 type;
	u8 result;
पूर्ण;

क्रमागत अणु
	EEPROM_OK,
	EEPROM_CHECKSUM_NONE,
	EEPROM_FW_NOT_SUPPORT,
	EEPROM_NG,
पूर्ण;

/* Power Save Status */
क्रमागत अणु
	PS_NONE,
	PS_ACTIVE_SET,
	PS_SAVE_SET,
	PS_CONF_WAIT,
	PS_SNOOZE,
	PS_WAKEUP
पूर्ण;

काष्ठा घातer_save_status अणु
	atomic_t status;	/* initialvalue 0 */
	काष्ठा completion wakeup_रुको;
	atomic_t confirm_रुको;
	atomic_t snooze_guard;
पूर्ण;

काष्ठा sleep_status अणु
	atomic_t status;	/* initialvalue 0 */
	atomic_t करोze_request;
	atomic_t wakeup_request;
पूर्ण;

/* WPA */
काष्ठा scan_ext अणु
	अचिन्हित पूर्णांक flag;
	अक्षर ssid[IW_ESSID_MAX_SIZE + 1];
पूर्ण;

#घोषणा CIPHER_ID_WPA_NONE    "\x00\x50\xf2\x00"
#घोषणा CIPHER_ID_WPA_WEP40   "\x00\x50\xf2\x01"
#घोषणा CIPHER_ID_WPA_TKIP    "\x00\x50\xf2\x02"
#घोषणा CIPHER_ID_WPA_CCMP    "\x00\x50\xf2\x04"
#घोषणा CIPHER_ID_WPA_WEP104  "\x00\x50\xf2\x05"

#घोषणा CIPHER_ID_WPA2_NONE   "\x00\x0f\xac\x00"
#घोषणा CIPHER_ID_WPA2_WEP40  "\x00\x0f\xac\x01"
#घोषणा CIPHER_ID_WPA2_TKIP   "\x00\x0f\xac\x02"
#घोषणा CIPHER_ID_WPA2_CCMP   "\x00\x0f\xac\x04"
#घोषणा CIPHER_ID_WPA2_WEP104 "\x00\x0f\xac\x05"

#घोषणा CIPHER_ID_LEN    4

क्रमागत अणु
	KEY_MGMT_802_1X,
	KEY_MGMT_PSK,
	KEY_MGMT_WPANONE,
पूर्ण;

#घोषणा KEY_MGMT_ID_WPA_NONE     "\x00\x50\xf2\x00"
#घोषणा KEY_MGMT_ID_WPA_1X       "\x00\x50\xf2\x01"
#घोषणा KEY_MGMT_ID_WPA_PSK      "\x00\x50\xf2\x02"
#घोषणा KEY_MGMT_ID_WPA_WPANONE  "\x00\x50\xf2\xff"

#घोषणा KEY_MGMT_ID_WPA2_NONE    "\x00\x0f\xac\x00"
#घोषणा KEY_MGMT_ID_WPA2_1X      "\x00\x0f\xac\x01"
#घोषणा KEY_MGMT_ID_WPA2_PSK     "\x00\x0f\xac\x02"
#घोषणा KEY_MGMT_ID_WPA2_WPANONE "\x00\x0f\xac\xff"

#घोषणा KEY_MGMT_ID_LEN  4

#घोषणा MIC_KEY_SIZE 8

काष्ठा wpa_key अणु
	u32 ext_flags;	/* IW_ENCODE_EXT_xxx */
	u8 tx_seq[IW_ENCODE_SEQ_MAX_SIZE];	/* LSB first */
	u8 rx_seq[IW_ENCODE_SEQ_MAX_SIZE];	/* LSB first */
	काष्ठा sockaddr addr;	/* ff:ff:ff:ff:ff:ff क्रम broadcast/multicast
				 * (group) keys or unicast address क्रम
				 * inभागidual keys
				 */
	u16 alg;
	u16 key_len;	/* WEP: 5 or 13, TKIP: 32, CCMP: 16 */
	u8 key_val[IW_ENCODING_TOKEN_MAX];
	u8 tx_mic_key[MIC_KEY_SIZE];
	u8 rx_mic_key[MIC_KEY_SIZE];
पूर्ण;

#घोषणा WPA_KEY_INDEX_MAX 4
#घोषणा WPA_RX_SEQ_LEN 6

काष्ठा mic_failure अणु
	u16 failure;	/* MIC Failure counter 0 or 1 or 2 */
	u16 counter;	/* 1sec counter 0-60 */
	u32 last_failure_समय;
	पूर्णांक stop;
पूर्ण;

काष्ठा wpa_status अणु
	पूर्णांक wpa_enabled;
	bool rsn_enabled;
	पूर्णांक version;
	पूर्णांक pairwise_suite;	/* unicast cipher */
	पूर्णांक group_suite;	/* multicast cipher */
	पूर्णांक key_mgmt_suite;
	पूर्णांक auth_alg;
	पूर्णांक txkey;
	काष्ठा wpa_key key[WPA_KEY_INDEX_MAX];
	काष्ठा scan_ext scan_ext;
	काष्ठा mic_failure mic_failure;
पूर्ण;

#समावेश <linux/list.h>
#घोषणा PMK_LIST_MAX 8
काष्ठा pmk_list अणु
	u16 size;
	काष्ठा list_head head;
	काष्ठा pmk अणु
		काष्ठा list_head list;
		u8 bssid[ETH_ALEN];
		u8 pmkid[IW_PMKID_LEN];
	पूर्ण pmk[PMK_LIST_MAX];
पूर्ण;

काष्ठा wps_status अणु
	पूर्णांक wps_enabled;
	पूर्णांक ielen;
	u8 ie[255];
पूर्ण;

/* Tx Device काष्ठा */
#घोषणा	TX_DEVICE_BUFF_SIZE	1024

काष्ठा ks_wlan_निजी;

/**
 * काष्ठा tx_device_buffer - Queue item क्रम the tx queue.
 * @sendp: Poपूर्णांकer to the send request data.
 * @size: Size of @sendp data.
 * @complete_handler: Function called once data ग_लिखो to device is complete.
 * @arg1: First argument to @complete_handler.
 * @arg2: Second argument to @complete_handler.
 */
काष्ठा tx_device_buffer अणु
	अचिन्हित अक्षर *sendp;
	अचिन्हित पूर्णांक size;
	व्योम (*complete_handler)(काष्ठा ks_wlan_निजी *priv,
				 काष्ठा sk_buff *skb);
	काष्ठा sk_buff *skb;
पूर्ण;

/**
 * काष्ठा tx_device - Tx buffer queue.
 * @tx_device_buffer: Queue buffer.
 * @qhead: Head of tx queue.
 * @qtail: Tail of tx queue.
 * @tx_dev_lock: Queue lock.
 */
काष्ठा tx_device अणु
	काष्ठा tx_device_buffer tx_dev_buff[TX_DEVICE_BUFF_SIZE];
	अचिन्हित पूर्णांक qhead;
	अचिन्हित पूर्णांक qtail;
	spinlock_t tx_dev_lock;	/* protect access to the queue */
पूर्ण;

/* Rx Device काष्ठा */
#घोषणा	RX_DATA_SIZE	(2 + 2 + 2347 + 1)
#घोषणा	RX_DEVICE_BUFF_SIZE	32

/**
 * काष्ठा rx_device_buffer - Queue item क्रम the rx queue.
 * @data: rx data.
 * @size: Size of @data.
 */
काष्ठा rx_device_buffer अणु
	अचिन्हित अक्षर data[RX_DATA_SIZE];
	अचिन्हित पूर्णांक size;
पूर्ण;

/**
 * काष्ठा rx_device - Rx buffer queue.
 * @rx_device_buffer: Queue buffer.
 * @qhead: Head of rx queue.
 * @qtail: Tail of rx queue.
 * @rx_dev_lock: Queue lock.
 */
काष्ठा rx_device अणु
	काष्ठा rx_device_buffer rx_dev_buff[RX_DEVICE_BUFF_SIZE];
	अचिन्हित पूर्णांक qhead;
	अचिन्हित पूर्णांक qtail;
	spinlock_t rx_dev_lock;	/* protect access to the queue */
पूर्ण;

काष्ठा ks_wlan_निजी अणु
	/* hardware inक्रमmation */
	व्योम *अगर_hw;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work rw_dwork;
	काष्ठा tasklet_काष्ठा rx_bh_task;

	काष्ठा net_device *net_dev;
	काष्ठा net_device_stats nstats;
	काष्ठा iw_statistics wstats;

	काष्ठा completion confirm_रुको;

	/* trx device & sme */
	काष्ठा tx_device tx_dev;
	काष्ठा rx_device rx_dev;
	काष्ठा sme_info sme_i;
	u8 *rxp;
	अचिन्हित पूर्णांक rx_size;
	काष्ठा tasklet_काष्ठा sme_task;
	काष्ठा work_काष्ठा wakeup_work;
	पूर्णांक scan_ind_count;

	अचिन्हित अक्षर eth_addr[ETH_ALEN];

	काष्ठा local_aplist aplist;
	काष्ठा local_ap current_ap;
	काष्ठा घातer_save_status psstatus;
	काष्ठा sleep_status sleepstatus;
	काष्ठा wpa_status wpa;
	काष्ठा pmk_list pmklist;
	/* wireless parameter */
	काष्ठा ks_wlan_parameter reg;
	u8 current_rate;

	अक्षर nick[IW_ESSID_MAX_SIZE + 1];

	spinlock_t multicast_spin;

	spinlock_t dev_पढ़ो_lock;
	रुको_queue_head_t devपढ़ो_रुको;

	अचिन्हित पूर्णांक need_commit;	/* क्रम ioctl */

	/* DeviceIoControl */
	bool is_device_खोलो;
	atomic_t event_count;
	atomic_t rec_count;
	पूर्णांक dev_count;
#घोषणा DEVICE_STOCK_COUNT 20
	अचिन्हित अक्षर *dev_data[DEVICE_STOCK_COUNT];
	पूर्णांक dev_size[DEVICE_STOCK_COUNT];

	/* ioctl : IOCTL_FIRMWARE_VERSION */
	अचिन्हित अक्षर firmware_version[128 + 1];
	पूर्णांक version_size;

	bool mac_address_valid;

	पूर्णांक dev_state;

	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक cur_rx;	/* Index पूर्णांकo the Rx buffer of next Rx pkt. */
#घोषणा FORCE_DISCONNECT    0x80000000
#घोषणा CONNECT_STATUS_MASK 0x7FFFFFFF
	u32 connect_status;
	पूर्णांक infra_status;
	u8 scan_ssid_len;
	u8 scan_ssid[IW_ESSID_MAX_SIZE + 1];
	काष्ठा local_gain gain;
	काष्ठा wps_status wps;
	u8 sleep_mode;

	u8 region;
	काष्ठा local_eeprom_sum eeprom_sum;
	u8 eeprom_checksum;

	काष्ठा hostt hostt;

	अचिन्हित दीर्घ last_करोze;
	अचिन्हित दीर्घ last_wakeup;

	अचिन्हित पूर्णांक wakeup_count;	/* क्रम detect wakeup loop */
पूर्ण;

अटल अंतरभूत व्योम inc_txqhead(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->tx_dev.qhead = (priv->tx_dev.qhead + 1) % TX_DEVICE_BUFF_SIZE;
पूर्ण

अटल अंतरभूत व्योम inc_txqtail(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->tx_dev.qtail = (priv->tx_dev.qtail + 1) % TX_DEVICE_BUFF_SIZE;
पूर्ण

अटल अंतरभूत bool txq_has_space(काष्ठा ks_wlan_निजी *priv)
अणु
	वापस (CIRC_SPACE(priv->tx_dev.qhead, priv->tx_dev.qtail,
			   TX_DEVICE_BUFF_SIZE) > 0);
पूर्ण

अटल अंतरभूत व्योम inc_rxqhead(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->rx_dev.qhead = (priv->rx_dev.qhead + 1) % RX_DEVICE_BUFF_SIZE;
पूर्ण

अटल अंतरभूत व्योम inc_rxqtail(काष्ठा ks_wlan_निजी *priv)
अणु
	priv->rx_dev.qtail = (priv->rx_dev.qtail + 1) % RX_DEVICE_BUFF_SIZE;
पूर्ण

अटल अंतरभूत bool rxq_has_space(काष्ठा ks_wlan_निजी *priv)
अणु
	वापस (CIRC_SPACE(priv->rx_dev.qhead, priv->rx_dev.qtail,
			   RX_DEVICE_BUFF_SIZE) > 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक txq_count(काष्ठा ks_wlan_निजी *priv)
अणु
	वापस CIRC_CNT_TO_END(priv->tx_dev.qhead, priv->tx_dev.qtail,
			       TX_DEVICE_BUFF_SIZE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rxq_count(काष्ठा ks_wlan_निजी *priv)
अणु
	वापस CIRC_CNT_TO_END(priv->rx_dev.qhead, priv->rx_dev.qtail,
			       RX_DEVICE_BUFF_SIZE);
पूर्ण

पूर्णांक ks_wlan_net_start(काष्ठा net_device *dev);
पूर्णांक ks_wlan_net_stop(काष्ठा net_device *dev);
bool is_connect_status(u32 status);
bool is_disconnect_status(u32 status);

#पूर्ण_अगर /* _KS_WLAN_H */
