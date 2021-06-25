<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित HOSTAP_AP_H
#घोषणा HOSTAP_AP_H

#समावेश "hostap_80211.h"

/* AP data काष्ठाures क्रम STAs */

/* maximum number of frames to buffer per STA */
#घोषणा STA_MAX_TX_BUFFER 32

/* STA flags */
#घोषणा WLAN_STA_AUTH BIT(0)
#घोषणा WLAN_STA_ASSOC BIT(1)
#घोषणा WLAN_STA_PS BIT(2)
#घोषणा WLAN_STA_TIM BIT(3) /* TIM bit is on क्रम PS stations */
#घोषणा WLAN_STA_PERM BIT(4) /* permanent; करो not हटाओ entry on expiration */
#घोषणा WLAN_STA_AUTHORIZED BIT(5) /* If 802.1X is used, this flag is
				    * controlling whether STA is authorized to
				    * send and receive non-IEEE 802.1X frames
				    */
#घोषणा WLAN_STA_PENDING_POLL BIT(6) /* pending activity poll not ACKed */

#घोषणा WLAN_RATE_1M BIT(0)
#घोषणा WLAN_RATE_2M BIT(1)
#घोषणा WLAN_RATE_5M5 BIT(2)
#घोषणा WLAN_RATE_11M BIT(3)
#घोषणा WLAN_RATE_COUNT 4

/* Maximum size of Supported Rates info element. IEEE 802.11 has a limit of 8,
 * but some pre-standard IEEE 802.11g products use दीर्घer elements. */
#घोषणा WLAN_SUPP_RATES_MAX 32

/* Try to increase TX rate after # successfully sent consecutive packets */
#घोषणा WLAN_RATE_UPDATE_COUNT 50

/* Decrease TX rate after # consecutive dropped packets */
#घोषणा WLAN_RATE_DECREASE_THRESHOLD 2

काष्ठा sta_info अणु
	काष्ठा list_head list;
	काष्ठा sta_info *hnext; /* next entry in hash table list */
	atomic_t users; /* number of users (करो not हटाओ अगर > 0) */
	काष्ठा proc_dir_entry *proc;

	u8 addr[6];
	u16 aid; /* STA's unique AID (1 .. 2007) or 0 अगर not yet asचिन्हित */
	u32 flags;
	u16 capability;
	u16 listen_पूर्णांकerval; /* or beacon_पूर्णांक क्रम APs */
	u8 supported_rates[WLAN_SUPP_RATES_MAX];

	अचिन्हित दीर्घ last_auth;
	अचिन्हित दीर्घ last_assoc;
	अचिन्हित दीर्घ last_rx;
	अचिन्हित दीर्घ last_tx;
	अचिन्हित दीर्घ rx_packets, tx_packets;
	अचिन्हित दीर्घ rx_bytes, tx_bytes;
	काष्ठा sk_buff_head tx_buf;
	/* FIX: समयout buffers with an expiry समय somehow derived from
	 * listen_पूर्णांकerval */

	s8 last_rx_silence; /* Noise in dBm */
	s8 last_rx_संकेत; /* Signal strength in dBm */
	u8 last_rx_rate; /* TX rate in 0.1 Mbps */
	u8 last_rx_updated; /* IWSPY's काष्ठा iw_quality::updated */

	u8 tx_supp_rates; /* bit field of supported TX rates */
	u8 tx_rate; /* current TX rate (in 0.1 Mbps) */
	u8 tx_rate_idx; /* current TX rate (WLAN_RATE_*) */
	u8 tx_max_rate; /* max TX rate (WLAN_RATE_*) */
	u32 tx_count[WLAN_RATE_COUNT]; /* number of frames sent (per rate) */
	u32 rx_count[WLAN_RATE_COUNT]; /* number of frames received (per rate)
					*/
	u32 tx_since_last_failure;
	u32 tx_consecutive_exc;

	काष्ठा lib80211_crypt_data *crypt;

	पूर्णांक ap; /* whether this station is an AP */

	local_info_t *local;

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	जोड़ अणु
		काष्ठा अणु
			अक्षर *challenge; /* shared key authentication
					  * challenge */
		पूर्ण sta;
		काष्ठा अणु
			पूर्णांक ssid_len;
			अचिन्हित अक्षर ssid[MAX_SSID_LEN + 1]; /* AP's ssid */
			पूर्णांक channel;
			अचिन्हित दीर्घ last_beacon; /* last RX beacon समय */
		पूर्ण ap;
	पूर्ण u;

	काष्ठा समयr_list समयr;
	क्रमागत अणु STA_शून्यFUNC = 0, STA_DISASSOC, STA_DEAUTH पूर्ण समयout_next;
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
पूर्ण;


#घोषणा MAX_STA_COUNT 1024

/* Maximum number of AIDs to use क्रम STAs; must be 2007 or lower
 * (8802.11 limitation) */
#घोषणा MAX_AID_TABLE_SIZE 128

#घोषणा STA_HASH_SIZE 256
#घोषणा STA_HASH(sta) (sta[5])


/* Default value क्रम maximum station inactivity. After AP_MAX_INACTIVITY_SEC
 * has passed since last received frame from the station, a nullfunc data
 * frame is sent to the station. If this frame is not acknowledged and no other
 * frames have been received, the station will be disassociated after
 * AP_DISASSOC_DELAY. Similarly, a the station will be deauthenticated after
 * AP_DEAUTH_DELAY. AP_TIMEOUT_RESOLUTION is the resolution that is used with
 * max inactivity समयr. */
#घोषणा AP_MAX_INACTIVITY_SEC (5 * 60)
#घोषणा AP_DISASSOC_DELAY (HZ)
#घोषणा AP_DEAUTH_DELAY (HZ)

/* ap_policy: whether to accept frames to/from other APs/IBSS */
प्रकार क्रमागत अणु
	AP_OTHER_AP_SKIP_ALL = 0,
	AP_OTHER_AP_SAME_SSID = 1,
	AP_OTHER_AP_ALL = 2,
	AP_OTHER_AP_EVEN_IBSS = 3
पूर्ण ap_policy_क्रमागत;

#घोषणा PRISM2_AUTH_OPEN BIT(0)
#घोषणा PRISM2_AUTH_SHARED_KEY BIT(1)


/* MAC address-based restrictions */
काष्ठा mac_entry अणु
	काष्ठा list_head list;
	u8 addr[6];
पूर्ण;

काष्ठा mac_restrictions अणु
	क्रमागत अणु MAC_POLICY_OPEN = 0, MAC_POLICY_ALLOW, MAC_POLICY_DENY पूर्ण policy;
	अचिन्हित पूर्णांक entries;
	काष्ठा list_head mac_list;
	spinlock_t lock;
पूर्ण;


काष्ठा add_sta_proc_data अणु
	u8 addr[ETH_ALEN];
	काष्ठा add_sta_proc_data *next;
पूर्ण;


प्रकार क्रमागत अणु WDS_ADD, WDS_DEL पूर्ण wds_oper_type;
काष्ठा wds_oper_data अणु
	wds_oper_type type;
	u8 addr[ETH_ALEN];
	काष्ठा wds_oper_data *next;
पूर्ण;


काष्ठा ap_data अणु
	पूर्णांक initialized; /* whether ap_data has been initialized */
	local_info_t *local;
	पूर्णांक bridge_packets; /* send packet to associated STAs directly to the
			     * wireless media instead of higher layers in the
			     * kernel */
	अचिन्हित पूर्णांक bridged_unicast; /* number of unicast frames bridged on
				       * wireless media */
	अचिन्हित पूर्णांक bridged_multicast; /* number of non-unicast frames
					 * bridged on wireless media */
	अचिन्हित पूर्णांक tx_drop_nonassoc; /* number of unicast TX packets dropped
					* because they were to an address that
					* was not associated */
	पूर्णांक nullfunc_ack; /* use workaround क्रम nullfunc frame ACKs */

	spinlock_t sta_table_lock;
	पूर्णांक num_sta; /* number of entries in sta_list */
	काष्ठा list_head sta_list; /* STA info list head */
	काष्ठा sta_info *sta_hash[STA_HASH_SIZE];

	काष्ठा proc_dir_entry *proc;

	ap_policy_क्रमागत ap_policy;
	अचिन्हित पूर्णांक max_inactivity;
	पूर्णांक स्वतःm_ap_wds;

	काष्ठा mac_restrictions mac_restrictions; /* MAC-based auth */
	पूर्णांक last_tx_rate;

	काष्ठा work_काष्ठा add_sta_proc_queue;
	काष्ठा add_sta_proc_data *add_sta_proc_entries;

	काष्ठा work_काष्ठा wds_oper_queue;
	काष्ठा wds_oper_data *wds_oper_entries;

	u16 tx_callback_idx;

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	/* poपूर्णांकers to STA info; based on allocated AID or शून्य अगर AID मुक्त
	 * AID is in the range 1-2007, so sta_aid[0] corresponders to AID 1
	 * and so on
	 */
	काष्ठा sta_info *sta_aid[MAX_AID_TABLE_SIZE];

	u16 tx_callback_auth, tx_callback_assoc, tx_callback_poll;

	/* WEP operations क्रम generating challenges to be used with shared key
	 * authentication */
	काष्ठा lib80211_crypto_ops *crypt;
	व्योम *crypt_priv;
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */
पूर्ण;


व्योम hostap_rx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
	       काष्ठा hostap_80211_rx_status *rx_stats);
व्योम hostap_init_data(local_info_t *local);
व्योम hostap_init_ap_proc(local_info_t *local);
व्योम hostap_मुक्त_data(काष्ठा ap_data *ap);
व्योम hostap_check_sta_fw_version(काष्ठा ap_data *ap, पूर्णांक sta_fw_ver);

प्रकार क्रमागत अणु
	AP_TX_CONTINUE, AP_TX_DROP, AP_TX_RETRY, AP_TX_BUFFERED,
	AP_TX_CONTINUE_NOT_AUTHORIZED
पूर्ण ap_tx_ret;
काष्ठा hostap_tx_data अणु
	काष्ठा sk_buff *skb;
	पूर्णांक host_encrypt;
	काष्ठा lib80211_crypt_data *crypt;
	व्योम *sta_ptr;
पूर्ण;
ap_tx_ret hostap_handle_sta_tx(local_info_t *local, काष्ठा hostap_tx_data *tx);
व्योम hostap_handle_sta_release(व्योम *ptr);
व्योम hostap_handle_sta_tx_exc(local_info_t *local, काष्ठा sk_buff *skb);
पूर्णांक hostap_update_sta_ps(local_info_t *local, काष्ठा ieee80211_hdr *hdr);
प्रकार क्रमागत अणु
	AP_RX_CONTINUE, AP_RX_DROP, AP_RX_EXIT, AP_RX_CONTINUE_NOT_AUTHORIZED
पूर्ण ap_rx_ret;
ap_rx_ret hostap_handle_sta_rx(local_info_t *local, काष्ठा net_device *dev,
			       काष्ठा sk_buff *skb,
			       काष्ठा hostap_80211_rx_status *rx_stats,
			       पूर्णांक wds);
पूर्णांक hostap_handle_sta_crypto(local_info_t *local, काष्ठा ieee80211_hdr *hdr,
			     काष्ठा lib80211_crypt_data **crypt,
			     व्योम **sta_ptr);
पूर्णांक hostap_is_sta_assoc(काष्ठा ap_data *ap, u8 *sta_addr);
पूर्णांक hostap_is_sta_authorized(काष्ठा ap_data *ap, u8 *sta_addr);
पूर्णांक hostap_add_sta(काष्ठा ap_data *ap, u8 *sta_addr);
पूर्णांक hostap_update_rx_stats(काष्ठा ap_data *ap, काष्ठा ieee80211_hdr *hdr,
			   काष्ठा hostap_80211_rx_status *rx_stats);
व्योम hostap_update_rates(local_info_t *local);
व्योम hostap_add_wds_links(local_info_t *local);
व्योम hostap_wds_link_oper(local_info_t *local, u8 *addr, wds_oper_type type);

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
व्योम hostap_deauth_all_stas(काष्ठा net_device *dev, काष्ठा ap_data *ap,
			    पूर्णांक resend);
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

#पूर्ण_अगर /* HOSTAP_AP_H */
