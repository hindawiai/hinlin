<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम RNDIS based wireless USB devices.
 *
 * Copyright (C) 2007 by Bjorge Dijkstra <bjd@jooz.net>
 * Copyright (C) 2008-2009 by Jussi Kivilinna <jussi.kivilinna@iki.fi>
 *
 *  Portions of this file are based on NDISwrapper project,
 *  Copyright (C) 2003-2005 Pontus Fuchs, Giridhar Pemmasani
 *  http://ndiswrapper.sourceक्रमge.net/
 */

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <net/cfg80211.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/rndis_host.h>


/* NOTE: All these are settings क्रम Broadcom chipset */
अटल अक्षर modparam_country[4] = "EU";
module_param_string(country, modparam_country, 4, 0444);
MODULE_PARM_DESC(country, "Country code (ISO 3166-1 alpha-2), default: EU");

अटल पूर्णांक modparam_frameburst = 1;
module_param_named(frameburst, modparam_frameburst, पूर्णांक, 0444);
MODULE_PARM_DESC(frameburst, "enable frame bursting (default: on)");

अटल पूर्णांक modparam_afterburner = 0;
module_param_named(afterburner, modparam_afterburner, पूर्णांक, 0444);
MODULE_PARM_DESC(afterburner,
	"enable afterburner aka '125 High Speed Mode' (default: off)");

अटल पूर्णांक modparam_घातer_save = 0;
module_param_named(घातer_save, modparam_घातer_save, पूर्णांक, 0444);
MODULE_PARM_DESC(घातer_save,
	"set power save mode: 0=off, 1=on, 2=fast (default: off)");

अटल पूर्णांक modparam_घातer_output = 3;
module_param_named(घातer_output, modparam_घातer_output, पूर्णांक, 0444);
MODULE_PARM_DESC(घातer_output,
	"set power output: 0=25%, 1=50%, 2=75%, 3=100% (default: 100%)");

अटल पूर्णांक modparam_roamtrigger = -70;
module_param_named(roamtrigger, modparam_roamtrigger, पूर्णांक, 0444);
MODULE_PARM_DESC(roamtrigger,
	"set roaming dBm trigger: -80=optimize for distance, "
				"-60=bandwidth (default: -70)");

अटल पूर्णांक modparam_roamdelta = 1;
module_param_named(roamdelta, modparam_roamdelta, पूर्णांक, 0444);
MODULE_PARM_DESC(roamdelta,
	"set roaming tendency: 0=aggressive, 1=moderate, "
				"2=conservative (default: moderate)");

अटल पूर्णांक modparam_workaround_पूर्णांकerval;
module_param_named(workaround_पूर्णांकerval, modparam_workaround_पूर्णांकerval,
							पूर्णांक, 0444);
MODULE_PARM_DESC(workaround_पूर्णांकerval,
	"set stall workaround interval in msecs (0=disabled) (default: 0)");

/* Typical noise/maximum संकेत level values taken from ndiswrapper iw_ndis.h */
#घोषणा	WL_NOISE	-96	/* typical noise level in dBm */
#घोषणा	WL_SIGMAX	-32	/* typical maximum संकेत level in dBm */


/* Assume that Broadcom 4320 (only chipset at समय of writing known to be
 * based on wireless rndis) has शेष txघातer of 13dBm.
 * This value is from Linksys WUSB54GSC User Guide, Appendix F: Specअगरications.
 *  100% : 20 mW ~ 13dBm
 *   75% : 15 mW ~ 12dBm
 *   50% : 10 mW ~ 10dBm
 *   25% :  5 mW ~  7dBm
 */
#घोषणा BCM4320_DEFAULT_TXPOWER_DBM_100 13
#घोषणा BCM4320_DEFAULT_TXPOWER_DBM_75  12
#घोषणा BCM4320_DEFAULT_TXPOWER_DBM_50  10
#घोषणा BCM4320_DEFAULT_TXPOWER_DBM_25  7

/* Known device types */
#घोषणा RNDIS_UNKNOWN	0
#घोषणा RNDIS_BCM4320A	1
#घोषणा RNDIS_BCM4320B	2


/* NDIS data काष्ठाures. Taken from wpa_supplicant driver_ndis.c
 * slightly modअगरied क्रम datatype endianess, etc
 */
#घोषणा NDIS_802_11_LENGTH_SSID 32
#घोषणा NDIS_802_11_LENGTH_RATES 8
#घोषणा NDIS_802_11_LENGTH_RATES_EX 16

क्रमागत ndis_80211_net_type अणु
	NDIS_80211_TYPE_FREQ_HOP,
	NDIS_80211_TYPE_सूचीECT_SEQ,
	NDIS_80211_TYPE_OFDM_A,
	NDIS_80211_TYPE_OFDM_G
पूर्ण;

क्रमागत ndis_80211_net_infra अणु
	NDIS_80211_INFRA_ADHOC,
	NDIS_80211_INFRA_INFRA,
	NDIS_80211_INFRA_AUTO_UNKNOWN
पूर्ण;

क्रमागत ndis_80211_auth_mode अणु
	NDIS_80211_AUTH_OPEN,
	NDIS_80211_AUTH_SHARED,
	NDIS_80211_AUTH_AUTO_SWITCH,
	NDIS_80211_AUTH_WPA,
	NDIS_80211_AUTH_WPA_PSK,
	NDIS_80211_AUTH_WPA_NONE,
	NDIS_80211_AUTH_WPA2,
	NDIS_80211_AUTH_WPA2_PSK
पूर्ण;

क्रमागत ndis_80211_encr_status अणु
	NDIS_80211_ENCR_WEP_ENABLED,
	NDIS_80211_ENCR_DISABLED,
	NDIS_80211_ENCR_WEP_KEY_ABSENT,
	NDIS_80211_ENCR_NOT_SUPPORTED,
	NDIS_80211_ENCR_TKIP_ENABLED,
	NDIS_80211_ENCR_TKIP_KEY_ABSENT,
	NDIS_80211_ENCR_CCMP_ENABLED,
	NDIS_80211_ENCR_CCMP_KEY_ABSENT
पूर्ण;

क्रमागत ndis_80211_priv_filter अणु
	NDIS_80211_PRIV_ACCEPT_ALL,
	NDIS_80211_PRIV_8021X_WEP
पूर्ण;

क्रमागत ndis_80211_status_type अणु
	NDIS_80211_STATUSTYPE_AUTHENTICATION,
	NDIS_80211_STATUSTYPE_MEDIASTREAMMODE,
	NDIS_80211_STATUSTYPE_PMKID_CANDIDATELIST,
	NDIS_80211_STATUSTYPE_RADIOSTATE,
पूर्ण;

क्रमागत ndis_80211_media_stream_mode अणु
	NDIS_80211_MEDIA_STREAM_OFF,
	NDIS_80211_MEDIA_STREAM_ON
पूर्ण;

क्रमागत ndis_80211_radio_status अणु
	NDIS_80211_RADIO_STATUS_ON,
	NDIS_80211_RADIO_STATUS_HARDWARE_OFF,
	NDIS_80211_RADIO_STATUS_SOFTWARE_OFF,
पूर्ण;

क्रमागत ndis_80211_addkey_bits अणु
	NDIS_80211_ADDKEY_8021X_AUTH = cpu_to_le32(1 << 28),
	NDIS_80211_ADDKEY_SET_INIT_RECV_SEQ = cpu_to_le32(1 << 29),
	NDIS_80211_ADDKEY_PAIRWISE_KEY = cpu_to_le32(1 << 30),
	NDIS_80211_ADDKEY_TRANSMIT_KEY = cpu_to_le32(1 << 31)
पूर्ण;

क्रमागत ndis_80211_addwep_bits अणु
	NDIS_80211_ADDWEP_PERCLIENT_KEY = cpu_to_le32(1 << 30),
	NDIS_80211_ADDWEP_TRANSMIT_KEY = cpu_to_le32(1 << 31)
पूर्ण;

क्रमागत ndis_80211_घातer_mode अणु
	NDIS_80211_POWER_MODE_CAM,
	NDIS_80211_POWER_MODE_MAX_PSP,
	NDIS_80211_POWER_MODE_FAST_PSP,
पूर्ण;

क्रमागत ndis_80211_pmkid_cand_list_flag_bits अणु
	NDIS_80211_PMKID_CAND_PREAUTH = cpu_to_le32(1 << 0)
पूर्ण;

काष्ठा ndis_80211_auth_request अणु
	__le32 length;
	u8 bssid[ETH_ALEN];
	u8 padding[2];
	__le32 flags;
पूर्ण __packed;

काष्ठा ndis_80211_pmkid_candidate अणु
	u8 bssid[ETH_ALEN];
	u8 padding[2];
	__le32 flags;
पूर्ण __packed;

काष्ठा ndis_80211_pmkid_cand_list अणु
	__le32 version;
	__le32 num_candidates;
	काष्ठा ndis_80211_pmkid_candidate candidate_list[];
पूर्ण __packed;

काष्ठा ndis_80211_status_indication अणु
	__le32 status_type;
	जोड़ अणु
		__le32					media_stream_mode;
		__le32					radio_status;
		काष्ठा ndis_80211_auth_request		auth_request[0];
		काष्ठा ndis_80211_pmkid_cand_list	cand_list;
	पूर्ण u;
पूर्ण __packed;

काष्ठा ndis_80211_ssid अणु
	__le32 length;
	u8 essid[NDIS_802_11_LENGTH_SSID];
पूर्ण __packed;

काष्ठा ndis_80211_conf_freq_hop अणु
	__le32 length;
	__le32 hop_pattern;
	__le32 hop_set;
	__le32 dwell_समय;
पूर्ण __packed;

काष्ठा ndis_80211_conf अणु
	__le32 length;
	__le32 beacon_period;
	__le32 atim_winकरोw;
	__le32 ds_config;
	काष्ठा ndis_80211_conf_freq_hop fh_config;
पूर्ण __packed;

काष्ठा ndis_80211_bssid_ex अणु
	__le32 length;
	u8 mac[ETH_ALEN];
	u8 padding[2];
	काष्ठा ndis_80211_ssid ssid;
	__le32 privacy;
	__le32 rssi;
	__le32 net_type;
	काष्ठा ndis_80211_conf config;
	__le32 net_infra;
	u8 rates[NDIS_802_11_LENGTH_RATES_EX];
	__le32 ie_length;
	u8 ies[];
पूर्ण __packed;

काष्ठा ndis_80211_bssid_list_ex अणु
	__le32 num_items;
	काष्ठा ndis_80211_bssid_ex bssid[];
पूर्ण __packed;

काष्ठा ndis_80211_fixed_ies अणु
	u8 बारtamp[8];
	__le16 beacon_पूर्णांकerval;
	__le16 capabilities;
पूर्ण __packed;

काष्ठा ndis_80211_wep_key अणु
	__le32 size;
	__le32 index;
	__le32 length;
	u8 material[32];
पूर्ण __packed;

काष्ठा ndis_80211_key अणु
	__le32 size;
	__le32 index;
	__le32 length;
	u8 bssid[ETH_ALEN];
	u8 padding[6];
	u8 rsc[8];
	u8 material[32];
पूर्ण __packed;

काष्ठा ndis_80211_हटाओ_key अणु
	__le32 size;
	__le32 index;
	u8 bssid[ETH_ALEN];
	u8 padding[2];
पूर्ण __packed;

काष्ठा ndis_config_param अणु
	__le32 name_offs;
	__le32 name_length;
	__le32 type;
	__le32 value_offs;
	__le32 value_length;
पूर्ण __packed;

काष्ठा ndis_80211_assoc_info अणु
	__le32 length;
	__le16 req_ies;
	काष्ठा req_ie अणु
		__le16 capa;
		__le16 listen_पूर्णांकerval;
		u8 cur_ap_address[ETH_ALEN];
	पूर्ण req_ie;
	__le32 req_ie_length;
	__le32 offset_req_ies;
	__le16 resp_ies;
	काष्ठा resp_ie अणु
		__le16 capa;
		__le16 status_code;
		__le16 assoc_id;
	पूर्ण resp_ie;
	__le32 resp_ie_length;
	__le32 offset_resp_ies;
पूर्ण __packed;

काष्ठा ndis_80211_capability अणु
	__le32 length;
	__le32 version;
	__le32 num_pmkids;
	__le32 num_auth_encr_pair;
पूर्ण __packed;

काष्ठा ndis_80211_bssid_info अणु
	u8 bssid[ETH_ALEN];
	u8 pmkid[16];
पूर्ण __packed;

काष्ठा ndis_80211_pmkid अणु
	__le32 length;
	__le32 bssid_info_count;
	काष्ठा ndis_80211_bssid_info bssid_info[];
पूर्ण __packed;

/*
 *  निजी data
 */
#घोषणा CAP_MODE_80211A		1
#घोषणा CAP_MODE_80211B		2
#घोषणा CAP_MODE_80211G		4
#घोषणा CAP_MODE_MASK		7

#घोषणा WORK_LINK_UP		0
#घोषणा WORK_LINK_DOWN		1
#घोषणा WORK_SET_MULTICAST_LIST	2

#घोषणा RNDIS_WLAN_ALG_NONE	0
#घोषणा RNDIS_WLAN_ALG_WEP	(1<<0)
#घोषणा RNDIS_WLAN_ALG_TKIP	(1<<1)
#घोषणा RNDIS_WLAN_ALG_CCMP	(1<<2)

#घोषणा RNDIS_WLAN_NUM_KEYS		4
#घोषणा RNDIS_WLAN_KEY_MGMT_NONE	0
#घोषणा RNDIS_WLAN_KEY_MGMT_802_1X	(1<<0)
#घोषणा RNDIS_WLAN_KEY_MGMT_PSK		(1<<1)

#घोषणा COMMAND_BUFFER_SIZE	(CONTROL_BUFFER_SIZE + माप(काष्ठा rndis_set))

अटल स्थिर काष्ठा ieee80211_channel rndis_channels[] = अणु
	अणु .center_freq = 2412 पूर्ण,
	अणु .center_freq = 2417 पूर्ण,
	अणु .center_freq = 2422 पूर्ण,
	अणु .center_freq = 2427 पूर्ण,
	अणु .center_freq = 2432 पूर्ण,
	अणु .center_freq = 2437 पूर्ण,
	अणु .center_freq = 2442 पूर्ण,
	अणु .center_freq = 2447 पूर्ण,
	अणु .center_freq = 2452 पूर्ण,
	अणु .center_freq = 2457 पूर्ण,
	अणु .center_freq = 2462 पूर्ण,
	अणु .center_freq = 2467 पूर्ण,
	अणु .center_freq = 2472 पूर्ण,
	अणु .center_freq = 2484 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_rate rndis_rates[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60 पूर्ण,
	अणु .bitrate = 90 पूर्ण,
	अणु .bitrate = 120 पूर्ण,
	अणु .bitrate = 180 पूर्ण,
	अणु .bitrate = 240 पूर्ण,
	अणु .bitrate = 360 पूर्ण,
	अणु .bitrate = 480 पूर्ण,
	अणु .bitrate = 540 पूर्ण
पूर्ण;

अटल स्थिर u32 rndis_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
पूर्ण;

काष्ठा rndis_wlan_encr_key अणु
	पूर्णांक len;
	u32 cipher;
	u8 material[32];
	u8 bssid[ETH_ALEN];
	bool pairwise;
	bool tx_key;
पूर्ण;

/* RNDIS device निजी data */
काष्ठा rndis_wlan_निजी अणु
	काष्ठा usbnet *usbdev;

	काष्ठा wireless_dev wdev;

	काष्ठा cfg80211_scan_request *scan_request;

	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा delayed_work dev_poller_work;
	काष्ठा delayed_work scan_work;
	काष्ठा work_काष्ठा work;
	काष्ठा mutex command_lock;
	अचिन्हित दीर्घ work_pending;
	पूर्णांक last_qual;
	s32 cqm_rssi_thold;
	u32 cqm_rssi_hyst;
	पूर्णांक last_cqm_event_rssi;

	काष्ठा ieee80211_supported_band band;
	काष्ठा ieee80211_channel channels[ARRAY_SIZE(rndis_channels)];
	काष्ठा ieee80211_rate rates[ARRAY_SIZE(rndis_rates)];
	u32 cipher_suites[ARRAY_SIZE(rndis_cipher_suites)];

	पूर्णांक device_type;
	पूर्णांक caps;
	पूर्णांक multicast_size;

	/* module parameters */
	अक्षर param_country[4];
	पूर्णांक  param_frameburst;
	पूर्णांक  param_afterburner;
	पूर्णांक  param_घातer_save;
	पूर्णांक  param_घातer_output;
	पूर्णांक  param_roamtrigger;
	पूर्णांक  param_roamdelta;
	u32  param_workaround_पूर्णांकerval;

	/* hardware state */
	bool radio_on;
	पूर्णांक घातer_mode;
	पूर्णांक infra_mode;
	bool connected;
	u8 bssid[ETH_ALEN];
	u32 current_command_oid;

	/* encryption stuff */
	u8 encr_tx_key_index;
	काष्ठा rndis_wlan_encr_key encr_keys[RNDIS_WLAN_NUM_KEYS];
	पूर्णांक  wpa_version;

	u8 command_buffer[COMMAND_BUFFER_SIZE];
पूर्ण;

/*
 * cfg80211 ops
 */
अटल पूर्णांक rndis_change_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
					काष्ठा net_device *dev,
					क्रमागत nl80211_अगरtype type,
					काष्ठा vअगर_params *params);

अटल पूर्णांक rndis_scan(काष्ठा wiphy *wiphy,
			काष्ठा cfg80211_scan_request *request);

अटल पूर्णांक rndis_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed);

अटल पूर्णांक rndis_set_tx_घातer(काष्ठा wiphy *wiphy,
			      काष्ठा wireless_dev *wdev,
			      क्रमागत nl80211_tx_घातer_setting type,
			      पूर्णांक mbm);
अटल पूर्णांक rndis_get_tx_घातer(काष्ठा wiphy *wiphy,
			      काष्ठा wireless_dev *wdev,
			      पूर्णांक *dbm);

अटल पूर्णांक rndis_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				काष्ठा cfg80211_connect_params *sme);

अटल पूर्णांक rndis_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				u16 reason_code);

अटल पूर्णांक rndis_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
					काष्ठा cfg80211_ibss_params *params);

अटल पूर्णांक rndis_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev);

अटल पूर्णांक rndis_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			 u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			 काष्ठा key_params *params);

अटल पूर्णांक rndis_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			 u8 key_index, bool pairwise, स्थिर u8 *mac_addr);

अटल पूर्णांक rndis_set_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				 u8 key_index, bool unicast, bool multicast);

अटल पूर्णांक rndis_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *mac, काष्ठा station_info *sinfo);

अटल पूर्णांक rndis_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo);

अटल पूर्णांक rndis_set_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				काष्ठा cfg80211_pmksa *pmksa);

अटल पूर्णांक rndis_del_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				काष्ठा cfg80211_pmksa *pmksa);

अटल पूर्णांक rndis_flush_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev);

अटल पूर्णांक rndis_set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				bool enabled, पूर्णांक समयout);

अटल पूर्णांक rndis_set_cqm_rssi_config(काष्ठा wiphy *wiphy,
					काष्ठा net_device *dev,
					s32 rssi_thold, u32 rssi_hyst);

अटल स्थिर काष्ठा cfg80211_ops rndis_config_ops = अणु
	.change_भव_पूर्णांकf = rndis_change_भव_पूर्णांकf,
	.scan = rndis_scan,
	.set_wiphy_params = rndis_set_wiphy_params,
	.set_tx_घातer = rndis_set_tx_घातer,
	.get_tx_घातer = rndis_get_tx_घातer,
	.connect = rndis_connect,
	.disconnect = rndis_disconnect,
	.join_ibss = rndis_join_ibss,
	.leave_ibss = rndis_leave_ibss,
	.add_key = rndis_add_key,
	.del_key = rndis_del_key,
	.set_शेष_key = rndis_set_शेष_key,
	.get_station = rndis_get_station,
	.dump_station = rndis_dump_station,
	.set_pmksa = rndis_set_pmksa,
	.del_pmksa = rndis_del_pmksa,
	.flush_pmksa = rndis_flush_pmksa,
	.set_घातer_mgmt = rndis_set_घातer_mgmt,
	.set_cqm_rssi_config = rndis_set_cqm_rssi_config,
पूर्ण;

अटल व्योम *rndis_wiphy_privid = &rndis_wiphy_privid;


अटल काष्ठा rndis_wlan_निजी *get_rndis_wlan_priv(काष्ठा usbnet *dev)
अणु
	वापस (काष्ठा rndis_wlan_निजी *)dev->driver_priv;
पूर्ण

अटल u32 get_bcm4320_घातer_dbm(काष्ठा rndis_wlan_निजी *priv)
अणु
	चयन (priv->param_घातer_output) अणु
	शेष:
	हाल 3:
		वापस BCM4320_DEFAULT_TXPOWER_DBM_100;
	हाल 2:
		वापस BCM4320_DEFAULT_TXPOWER_DBM_75;
	हाल 1:
		वापस BCM4320_DEFAULT_TXPOWER_DBM_50;
	हाल 0:
		वापस BCM4320_DEFAULT_TXPOWER_DBM_25;
	पूर्ण
पूर्ण

अटल bool is_wpa_key(काष्ठा rndis_wlan_निजी *priv, u8 idx)
अणु
	पूर्णांक cipher = priv->encr_keys[idx].cipher;

	वापस (cipher == WLAN_CIPHER_SUITE_CCMP ||
		cipher == WLAN_CIPHER_SUITE_TKIP);
पूर्ण

अटल पूर्णांक rndis_cipher_to_alg(u32 cipher)
अणु
	चयन (cipher) अणु
	शेष:
		वापस RNDIS_WLAN_ALG_NONE;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस RNDIS_WLAN_ALG_WEP;
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस RNDIS_WLAN_ALG_TKIP;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस RNDIS_WLAN_ALG_CCMP;
	पूर्ण
पूर्ण

अटल पूर्णांक rndis_akm_suite_to_key_mgmt(u32 akm_suite)
अणु
	चयन (akm_suite) अणु
	शेष:
		वापस RNDIS_WLAN_KEY_MGMT_NONE;
	हाल WLAN_AKM_SUITE_8021X:
		वापस RNDIS_WLAN_KEY_MGMT_802_1X;
	हाल WLAN_AKM_SUITE_PSK:
		वापस RNDIS_WLAN_KEY_MGMT_PSK;
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG
अटल स्थिर अक्षर *oid_to_string(u32 oid)
अणु
	चयन (oid) अणु
#घोषणा OID_STR(oid) हाल oid: वापस(#oid)
		/* from rndis_host.h */
		OID_STR(RNDIS_OID_802_3_PERMANENT_ADDRESS);
		OID_STR(RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE);
		OID_STR(RNDIS_OID_GEN_CURRENT_PACKET_FILTER);
		OID_STR(RNDIS_OID_GEN_PHYSICAL_MEDIUM);

		/* from rndis_wlan.c */
		OID_STR(RNDIS_OID_GEN_LINK_SPEED);
		OID_STR(RNDIS_OID_GEN_RNDIS_CONFIG_PARAMETER);

		OID_STR(RNDIS_OID_GEN_XMIT_OK);
		OID_STR(RNDIS_OID_GEN_RCV_OK);
		OID_STR(RNDIS_OID_GEN_XMIT_ERROR);
		OID_STR(RNDIS_OID_GEN_RCV_ERROR);
		OID_STR(RNDIS_OID_GEN_RCV_NO_BUFFER);

		OID_STR(RNDIS_OID_802_3_CURRENT_ADDRESS);
		OID_STR(RNDIS_OID_802_3_MULTICAST_LIST);
		OID_STR(RNDIS_OID_802_3_MAXIMUM_LIST_SIZE);

		OID_STR(RNDIS_OID_802_11_BSSID);
		OID_STR(RNDIS_OID_802_11_SSID);
		OID_STR(RNDIS_OID_802_11_INFRASTRUCTURE_MODE);
		OID_STR(RNDIS_OID_802_11_ADD_WEP);
		OID_STR(RNDIS_OID_802_11_REMOVE_WEP);
		OID_STR(RNDIS_OID_802_11_DISASSOCIATE);
		OID_STR(RNDIS_OID_802_11_AUTHENTICATION_MODE);
		OID_STR(RNDIS_OID_802_11_PRIVACY_FILTER);
		OID_STR(RNDIS_OID_802_11_BSSID_LIST_SCAN);
		OID_STR(RNDIS_OID_802_11_ENCRYPTION_STATUS);
		OID_STR(RNDIS_OID_802_11_ADD_KEY);
		OID_STR(RNDIS_OID_802_11_REMOVE_KEY);
		OID_STR(RNDIS_OID_802_11_ASSOCIATION_INFORMATION);
		OID_STR(RNDIS_OID_802_11_CAPABILITY);
		OID_STR(RNDIS_OID_802_11_PMKID);
		OID_STR(RNDIS_OID_802_11_NETWORK_TYPES_SUPPORTED);
		OID_STR(RNDIS_OID_802_11_NETWORK_TYPE_IN_USE);
		OID_STR(RNDIS_OID_802_11_TX_POWER_LEVEL);
		OID_STR(RNDIS_OID_802_11_RSSI);
		OID_STR(RNDIS_OID_802_11_RSSI_TRIGGER);
		OID_STR(RNDIS_OID_802_11_FRAGMENTATION_THRESHOLD);
		OID_STR(RNDIS_OID_802_11_RTS_THRESHOLD);
		OID_STR(RNDIS_OID_802_11_SUPPORTED_RATES);
		OID_STR(RNDIS_OID_802_11_CONFIGURATION);
		OID_STR(RNDIS_OID_802_11_POWER_MODE);
		OID_STR(RNDIS_OID_802_11_BSSID_LIST);
#अघोषित OID_STR
	पूर्ण

	वापस "?";
पूर्ण
#अन्यथा
अटल स्थिर अक्षर *oid_to_string(u32 oid)
अणु
	वापस "?";
पूर्ण
#पूर्ण_अगर

/* translate error code */
अटल पूर्णांक rndis_error_status(__le32 rndis_status)
अणु
	पूर्णांक ret = -EINVAL;
	चयन (le32_to_cpu(rndis_status)) अणु
	हाल RNDIS_STATUS_SUCCESS:
		ret = 0;
		अवरोध;
	हाल RNDIS_STATUS_FAILURE:
	हाल RNDIS_STATUS_INVALID_DATA:
		ret = -EINVAL;
		अवरोध;
	हाल RNDIS_STATUS_NOT_SUPPORTED:
		ret = -EOPNOTSUPP;
		अवरोध;
	हाल RNDIS_STATUS_ADAPTER_NOT_READY:
	हाल RNDIS_STATUS_ADAPTER_NOT_OPEN:
		ret = -EBUSY;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rndis_query_oid(काष्ठा usbnet *dev, u32 oid, व्योम *data, पूर्णांक *len)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(dev);
	जोड़ अणु
		व्योम			*buf;
		काष्ठा rndis_msg_hdr	*header;
		काष्ठा rndis_query	*get;
		काष्ठा rndis_query_c	*get_c;
	पूर्ण u;
	पूर्णांक ret, buflen;
	पूर्णांक resplen, respoffs, copylen;

	buflen = *len + माप(*u.get);
	अगर (buflen < CONTROL_BUFFER_SIZE)
		buflen = CONTROL_BUFFER_SIZE;

	अगर (buflen > COMMAND_BUFFER_SIZE) अणु
		u.buf = kदो_स्मृति(buflen, GFP_KERNEL);
		अगर (!u.buf)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		u.buf = priv->command_buffer;
	पूर्ण

	mutex_lock(&priv->command_lock);

	स_रखो(u.get, 0, माप *u.get);
	u.get->msg_type = cpu_to_le32(RNDIS_MSG_QUERY);
	u.get->msg_len = cpu_to_le32(माप *u.get);
	u.get->oid = cpu_to_le32(oid);

	priv->current_command_oid = oid;
	ret = rndis_command(dev, u.header, buflen);
	priv->current_command_oid = 0;
	अगर (ret < 0)
		netdev_dbg(dev->net, "%s(%s): rndis_command() failed, %d (%08x)\n",
			   __func__, oid_to_string(oid), ret,
			   le32_to_cpu(u.get_c->status));

	अगर (ret == 0) अणु
		resplen = le32_to_cpu(u.get_c->len);
		respoffs = le32_to_cpu(u.get_c->offset) + 8;

		अगर (respoffs > buflen) अणु
			/* Device वापसed data offset outside buffer, error. */
			netdev_dbg(dev->net, "%s(%s): received invalid "
				"data offset: %d > %d\n", __func__,
				oid_to_string(oid), respoffs, buflen);

			ret = -EINVAL;
			जाओ निकास_unlock;
		पूर्ण

		अगर ((resplen + respoffs) > buflen) अणु
			/* Device would have वापसed more data अगर buffer would
			 * have been big enough. Copy just the bits that we got.
			 */
			copylen = buflen - respoffs;
		पूर्ण अन्यथा अणु
			copylen = resplen;
		पूर्ण

		अगर (copylen > *len)
			copylen = *len;

		स_नकल(data, u.buf + respoffs, copylen);

		*len = resplen;

		ret = rndis_error_status(u.get_c->status);
		अगर (ret < 0)
			netdev_dbg(dev->net, "%s(%s): device returned error,  0x%08x (%d)\n",
				   __func__, oid_to_string(oid),
				   le32_to_cpu(u.get_c->status), ret);
	पूर्ण

निकास_unlock:
	mutex_unlock(&priv->command_lock);

	अगर (u.buf != priv->command_buffer)
		kमुक्त(u.buf);
	वापस ret;
पूर्ण

अटल पूर्णांक rndis_set_oid(काष्ठा usbnet *dev, u32 oid, स्थिर व्योम *data,
			 पूर्णांक len)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(dev);
	जोड़ अणु
		व्योम			*buf;
		काष्ठा rndis_msg_hdr	*header;
		काष्ठा rndis_set	*set;
		काष्ठा rndis_set_c	*set_c;
	पूर्ण u;
	पूर्णांक ret, buflen;

	buflen = len + माप(*u.set);
	अगर (buflen < CONTROL_BUFFER_SIZE)
		buflen = CONTROL_BUFFER_SIZE;

	अगर (buflen > COMMAND_BUFFER_SIZE) अणु
		u.buf = kदो_स्मृति(buflen, GFP_KERNEL);
		अगर (!u.buf)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		u.buf = priv->command_buffer;
	पूर्ण

	mutex_lock(&priv->command_lock);

	स_रखो(u.set, 0, माप *u.set);
	u.set->msg_type = cpu_to_le32(RNDIS_MSG_SET);
	u.set->msg_len = cpu_to_le32(माप(*u.set) + len);
	u.set->oid = cpu_to_le32(oid);
	u.set->len = cpu_to_le32(len);
	u.set->offset = cpu_to_le32(माप(*u.set) - 8);
	u.set->handle = cpu_to_le32(0);
	स_नकल(u.buf + माप(*u.set), data, len);

	priv->current_command_oid = oid;
	ret = rndis_command(dev, u.header, buflen);
	priv->current_command_oid = 0;
	अगर (ret < 0)
		netdev_dbg(dev->net, "%s(%s): rndis_command() failed, %d (%08x)\n",
			   __func__, oid_to_string(oid), ret,
			   le32_to_cpu(u.set_c->status));

	अगर (ret == 0) अणु
		ret = rndis_error_status(u.set_c->status);

		अगर (ret < 0)
			netdev_dbg(dev->net, "%s(%s): device returned error, 0x%08x (%d)\n",
				   __func__, oid_to_string(oid),
				   le32_to_cpu(u.set_c->status), ret);
	पूर्ण

	mutex_unlock(&priv->command_lock);

	अगर (u.buf != priv->command_buffer)
		kमुक्त(u.buf);
	वापस ret;
पूर्ण

अटल पूर्णांक rndis_reset(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा rndis_reset *reset;
	पूर्णांक ret;

	mutex_lock(&priv->command_lock);

	reset = (व्योम *)priv->command_buffer;
	स_रखो(reset, 0, माप(*reset));
	reset->msg_type = cpu_to_le32(RNDIS_MSG_RESET);
	reset->msg_len = cpu_to_le32(माप(*reset));
	priv->current_command_oid = 0;
	ret = rndis_command(usbdev, (व्योम *)reset, CONTROL_BUFFER_SIZE);

	mutex_unlock(&priv->command_lock);

	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

/*
 * Specs say that we can only set config parameters only soon after device
 * initialization.
 *   value_type: 0 = u32, 2 = unicode string
 */
अटल पूर्णांक rndis_set_config_parameter(काष्ठा usbnet *dev, अक्षर *param,
						पूर्णांक value_type, व्योम *value)
अणु
	काष्ठा ndis_config_param *infobuf;
	पूर्णांक value_len, info_len, param_len, ret, i;
	__le16 *unibuf;
	__le32 *dst_value;

	अगर (value_type == 0)
		value_len = माप(__le32);
	अन्यथा अगर (value_type == 2)
		value_len = म_माप(value) * माप(__le16);
	अन्यथा
		वापस -EINVAL;

	param_len = म_माप(param) * माप(__le16);
	info_len = माप(*infobuf) + param_len + value_len;

#अगर_घोषित DEBUG
	info_len += 12;
#पूर्ण_अगर
	infobuf = kदो_स्मृति(info_len, GFP_KERNEL);
	अगर (!infobuf)
		वापस -ENOMEM;

#अगर_घोषित DEBUG
	info_len -= 12;
	/* extra 12 bytes are क्रम padding (debug output) */
	स_रखो(infobuf, 0xCC, info_len + 12);
#पूर्ण_अगर

	अगर (value_type == 2)
		netdev_dbg(dev->net, "setting config parameter: %s, value: %s\n",
			   param, (u8 *)value);
	अन्यथा
		netdev_dbg(dev->net, "setting config parameter: %s, value: %d\n",
			   param, *(u32 *)value);

	infobuf->name_offs = cpu_to_le32(माप(*infobuf));
	infobuf->name_length = cpu_to_le32(param_len);
	infobuf->type = cpu_to_le32(value_type);
	infobuf->value_offs = cpu_to_le32(माप(*infobuf) + param_len);
	infobuf->value_length = cpu_to_le32(value_len);

	/* simple string to unicode string conversion */
	unibuf = (व्योम *)infobuf + माप(*infobuf);
	क्रम (i = 0; i < param_len / माप(__le16); i++)
		unibuf[i] = cpu_to_le16(param[i]);

	अगर (value_type == 2) अणु
		unibuf = (व्योम *)infobuf + माप(*infobuf) + param_len;
		क्रम (i = 0; i < value_len / माप(__le16); i++)
			unibuf[i] = cpu_to_le16(((u8 *)value)[i]);
	पूर्ण अन्यथा अणु
		dst_value = (व्योम *)infobuf + माप(*infobuf) + param_len;
		*dst_value = cpu_to_le32(*(u32 *)value);
	पूर्ण

#अगर_घोषित DEBUG
	netdev_dbg(dev->net, "info buffer (len: %d)\n", info_len);
	क्रम (i = 0; i < info_len; i += 12) अणु
		u32 *पंचांगp = (u32 *)((u8 *)infobuf + i);
		netdev_dbg(dev->net, "%08X:%08X:%08X\n",
			   cpu_to_be32(पंचांगp[0]),
			   cpu_to_be32(पंचांगp[1]),
			   cpu_to_be32(पंचांगp[2]));
	पूर्ण
#पूर्ण_अगर

	ret = rndis_set_oid(dev, RNDIS_OID_GEN_RNDIS_CONFIG_PARAMETER,
							infobuf, info_len);
	अगर (ret != 0)
		netdev_dbg(dev->net, "setting rndis config parameter failed, %d\n",
			   ret);

	kमुक्त(infobuf);
	वापस ret;
पूर्ण

अटल पूर्णांक rndis_set_config_parameter_str(काष्ठा usbnet *dev,
						अक्षर *param, अक्षर *value)
अणु
	वापस rndis_set_config_parameter(dev, param, 2, value);
पूर्ण

/*
 * data conversion functions
 */
अटल पूर्णांक level_to_qual(पूर्णांक level)
अणु
	पूर्णांक qual = 100 * (level - WL_NOISE) / (WL_SIGMAX - WL_NOISE);
	वापस qual >= 0 ? (qual <= 100 ? qual : 100) : 0;
पूर्ण

/*
 * common functions
 */
अटल पूर्णांक set_infra_mode(काष्ठा usbnet *usbdev, पूर्णांक mode);
अटल व्योम restore_keys(काष्ठा usbnet *usbdev);
अटल पूर्णांक rndis_check_bssid_list(काष्ठा usbnet *usbdev, u8 *match_bssid,
					bool *matched);

अटल पूर्णांक rndis_start_bssid_list_scan(काष्ठा usbnet *usbdev)
अणु
	__le32 पंचांगp;

	/* Note: RNDIS_OID_802_11_BSSID_LIST_SCAN clears पूर्णांकernal BSS list. */
	पंचांगp = cpu_to_le32(1);
	वापस rndis_set_oid(usbdev, RNDIS_OID_802_11_BSSID_LIST_SCAN, &पंचांगp,
							माप(पंचांगp));
पूर्ण

अटल पूर्णांक set_essid(काष्ठा usbnet *usbdev, काष्ठा ndis_80211_ssid *ssid)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	पूर्णांक ret;

	ret = rndis_set_oid(usbdev, RNDIS_OID_802_11_SSID,
			    ssid, माप(*ssid));
	अगर (ret < 0) अणु
		netdev_warn(usbdev->net, "setting SSID failed (%08X)\n", ret);
		वापस ret;
	पूर्ण
	अगर (ret == 0) अणु
		priv->radio_on = true;
		netdev_dbg(usbdev->net, "%s(): radio_on = true\n", __func__);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_bssid(काष्ठा usbnet *usbdev, स्थिर u8 *bssid)
अणु
	पूर्णांक ret;

	ret = rndis_set_oid(usbdev, RNDIS_OID_802_11_BSSID,
			    bssid, ETH_ALEN);
	अगर (ret < 0) अणु
		netdev_warn(usbdev->net, "setting BSSID[%pM] failed (%08X)\n",
			    bssid, ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक clear_bssid(काष्ठा usbnet *usbdev)
अणु
	अटल स्थिर u8 broadcast_mac[ETH_ALEN] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;

	वापस set_bssid(usbdev, broadcast_mac);
पूर्ण

अटल पूर्णांक get_bssid(काष्ठा usbnet *usbdev, u8 bssid[ETH_ALEN])
अणु
	पूर्णांक ret, len;

	len = ETH_ALEN;
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_BSSID,
			      bssid, &len);

	अगर (ret != 0)
		eth_zero_addr(bssid);

	वापस ret;
पूर्ण

अटल पूर्णांक get_association_info(काष्ठा usbnet *usbdev,
			काष्ठा ndis_80211_assoc_info *info, पूर्णांक len)
अणु
	वापस rndis_query_oid(usbdev,
			RNDIS_OID_802_11_ASSOCIATION_INFORMATION,
			info, &len);
पूर्ण

अटल bool is_associated(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	u8 bssid[ETH_ALEN];
	पूर्णांक ret;

	अगर (!priv->radio_on)
		वापस false;

	ret = get_bssid(usbdev, bssid);

	वापस (ret == 0 && !is_zero_ether_addr(bssid));
पूर्ण

अटल पूर्णांक disassociate(काष्ठा usbnet *usbdev, bool reset_ssid)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ndis_80211_ssid ssid;
	पूर्णांक i, ret = 0;

	अगर (priv->radio_on) अणु
		ret = rndis_set_oid(usbdev,
				RNDIS_OID_802_11_DISASSOCIATE,
				शून्य, 0);
		अगर (ret == 0) अणु
			priv->radio_on = false;
			netdev_dbg(usbdev->net, "%s(): radio_on = false\n",
				   __func__);

			अगर (reset_ssid)
				msleep(100);
		पूर्ण
	पूर्ण

	/* disassociate causes radio to be turned off; अगर reset_ssid
	 * is given, set अक्रमom ssid to enable radio */
	अगर (reset_ssid) अणु
		/* Set device to infraकाष्ठाure mode so we करोn't get ad-hoc
		 * 'media connect' indications with the अक्रमom ssid.
		 */
		set_infra_mode(usbdev, NDIS_80211_INFRA_INFRA);

		ssid.length = cpu_to_le32(माप(ssid.essid));
		get_अक्रमom_bytes(&ssid.essid[2], माप(ssid.essid)-2);
		ssid.essid[0] = 0x1;
		ssid.essid[1] = 0xff;
		क्रम (i = 2; i < माप(ssid.essid); i++)
			ssid.essid[i] = 0x1 + (ssid.essid[i] * 0xfe / 0xff);
		ret = set_essid(usbdev, &ssid);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक set_auth_mode(काष्ठा usbnet *usbdev, u32 wpa_version,
				क्रमागत nl80211_auth_type auth_type, पूर्णांक keymgmt)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	__le32 पंचांगp;
	पूर्णांक auth_mode, ret;

	netdev_dbg(usbdev->net, "%s(): wpa_version=0x%x authalg=0x%x keymgmt=0x%x\n",
		   __func__, wpa_version, auth_type, keymgmt);

	अगर (wpa_version & NL80211_WPA_VERSION_2) अणु
		अगर (keymgmt & RNDIS_WLAN_KEY_MGMT_802_1X)
			auth_mode = NDIS_80211_AUTH_WPA2;
		अन्यथा
			auth_mode = NDIS_80211_AUTH_WPA2_PSK;
	पूर्ण अन्यथा अगर (wpa_version & NL80211_WPA_VERSION_1) अणु
		अगर (keymgmt & RNDIS_WLAN_KEY_MGMT_802_1X)
			auth_mode = NDIS_80211_AUTH_WPA;
		अन्यथा अगर (keymgmt & RNDIS_WLAN_KEY_MGMT_PSK)
			auth_mode = NDIS_80211_AUTH_WPA_PSK;
		अन्यथा
			auth_mode = NDIS_80211_AUTH_WPA_NONE;
	पूर्ण अन्यथा अगर (auth_type == NL80211_AUTHTYPE_SHARED_KEY)
		auth_mode = NDIS_80211_AUTH_SHARED;
	अन्यथा अगर (auth_type == NL80211_AUTHTYPE_OPEN_SYSTEM)
		auth_mode = NDIS_80211_AUTH_OPEN;
	अन्यथा अगर (auth_type == NL80211_AUTHTYPE_AUTOMATIC)
		auth_mode = NDIS_80211_AUTH_AUTO_SWITCH;
	अन्यथा
		वापस -ENOTSUPP;

	पंचांगp = cpu_to_le32(auth_mode);
	ret = rndis_set_oid(usbdev,
			    RNDIS_OID_802_11_AUTHENTICATION_MODE,
			    &पंचांगp, माप(पंचांगp));
	अगर (ret != 0) अणु
		netdev_warn(usbdev->net, "setting auth mode failed (%08X)\n",
			    ret);
		वापस ret;
	पूर्ण

	priv->wpa_version = wpa_version;

	वापस 0;
पूर्ण

अटल पूर्णांक set_priv_filter(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	__le32 पंचांगp;

	netdev_dbg(usbdev->net, "%s(): wpa_version=0x%x\n",
		   __func__, priv->wpa_version);

	अगर (priv->wpa_version & NL80211_WPA_VERSION_2 ||
	    priv->wpa_version & NL80211_WPA_VERSION_1)
		पंचांगp = cpu_to_le32(NDIS_80211_PRIV_8021X_WEP);
	अन्यथा
		पंचांगp = cpu_to_le32(NDIS_80211_PRIV_ACCEPT_ALL);

	वापस rndis_set_oid(usbdev,
			     RNDIS_OID_802_11_PRIVACY_FILTER, &पंचांगp,
			     माप(पंचांगp));
पूर्ण

अटल पूर्णांक set_encr_mode(काष्ठा usbnet *usbdev, पूर्णांक pairwise, पूर्णांक groupwise)
अणु
	__le32 पंचांगp;
	पूर्णांक encr_mode, ret;

	netdev_dbg(usbdev->net, "%s(): cipher_pair=0x%x cipher_group=0x%x\n",
		   __func__, pairwise, groupwise);

	अगर (pairwise & RNDIS_WLAN_ALG_CCMP)
		encr_mode = NDIS_80211_ENCR_CCMP_ENABLED;
	अन्यथा अगर (pairwise & RNDIS_WLAN_ALG_TKIP)
		encr_mode = NDIS_80211_ENCR_TKIP_ENABLED;
	अन्यथा अगर (pairwise & RNDIS_WLAN_ALG_WEP)
		encr_mode = NDIS_80211_ENCR_WEP_ENABLED;
	अन्यथा अगर (groupwise & RNDIS_WLAN_ALG_CCMP)
		encr_mode = NDIS_80211_ENCR_CCMP_ENABLED;
	अन्यथा अगर (groupwise & RNDIS_WLAN_ALG_TKIP)
		encr_mode = NDIS_80211_ENCR_TKIP_ENABLED;
	अन्यथा
		encr_mode = NDIS_80211_ENCR_DISABLED;

	पंचांगp = cpu_to_le32(encr_mode);
	ret = rndis_set_oid(usbdev,
			RNDIS_OID_802_11_ENCRYPTION_STATUS, &पंचांगp,
			माप(पंचांगp));
	अगर (ret != 0) अणु
		netdev_warn(usbdev->net, "setting encr mode failed (%08X)\n",
			    ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_infra_mode(काष्ठा usbnet *usbdev, पूर्णांक mode)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	__le32 पंचांगp;
	पूर्णांक ret;

	netdev_dbg(usbdev->net, "%s(): infra_mode=0x%x\n",
		   __func__, priv->infra_mode);

	पंचांगp = cpu_to_le32(mode);
	ret = rndis_set_oid(usbdev,
			    RNDIS_OID_802_11_INFRASTRUCTURE_MODE,
			    &पंचांगp, माप(पंचांगp));
	अगर (ret != 0) अणु
		netdev_warn(usbdev->net, "setting infra mode failed (%08X)\n",
			    ret);
		वापस ret;
	पूर्ण

	/* NDIS drivers clear keys when infraकाष्ठाure mode is
	 * changed. But Linux tools assume otherwise. So set the
	 * keys */
	restore_keys(usbdev);

	priv->infra_mode = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक set_rts_threshold(काष्ठा usbnet *usbdev, u32 rts_threshold)
अणु
	__le32 पंचांगp;

	netdev_dbg(usbdev->net, "%s(): %i\n", __func__, rts_threshold);

	अगर (rts_threshold == -1 || rts_threshold > 2347)
		rts_threshold = 2347;

	पंचांगp = cpu_to_le32(rts_threshold);
	वापस rndis_set_oid(usbdev,
			     RNDIS_OID_802_11_RTS_THRESHOLD,
			     &पंचांगp, माप(पंचांगp));
पूर्ण

अटल पूर्णांक set_frag_threshold(काष्ठा usbnet *usbdev, u32 frag_threshold)
अणु
	__le32 पंचांगp;

	netdev_dbg(usbdev->net, "%s(): %i\n", __func__, frag_threshold);

	अगर (frag_threshold < 256 || frag_threshold > 2346)
		frag_threshold = 2346;

	पंचांगp = cpu_to_le32(frag_threshold);
	वापस rndis_set_oid(usbdev,
			RNDIS_OID_802_11_FRAGMENTATION_THRESHOLD,
			&पंचांगp, माप(पंचांगp));
पूर्ण

अटल व्योम set_शेष_iw_params(काष्ठा usbnet *usbdev)
अणु
	set_infra_mode(usbdev, NDIS_80211_INFRA_INFRA);
	set_auth_mode(usbdev, 0, NL80211_AUTHTYPE_OPEN_SYSTEM,
						RNDIS_WLAN_KEY_MGMT_NONE);
	set_priv_filter(usbdev);
	set_encr_mode(usbdev, RNDIS_WLAN_ALG_NONE, RNDIS_WLAN_ALG_NONE);
पूर्ण

अटल पूर्णांक deauthenticate(काष्ठा usbnet *usbdev)
अणु
	पूर्णांक ret;

	ret = disassociate(usbdev, true);
	set_शेष_iw_params(usbdev);
	वापस ret;
पूर्ण

अटल पूर्णांक set_channel(काष्ठा usbnet *usbdev, पूर्णांक channel)
अणु
	काष्ठा ndis_80211_conf config;
	अचिन्हित पूर्णांक dsconfig;
	पूर्णांक len, ret;

	netdev_dbg(usbdev->net, "%s(%d)\n", __func__, channel);

	/* this OID is valid only when not associated */
	अगर (is_associated(usbdev))
		वापस 0;

	dsconfig = 1000 *
		ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);

	len = माप(config);
	ret = rndis_query_oid(usbdev,
			RNDIS_OID_802_11_CONFIGURATION,
			&config, &len);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "%s(): querying configuration failed\n",
			   __func__);
		वापस ret;
	पूर्ण

	config.ds_config = cpu_to_le32(dsconfig);
	ret = rndis_set_oid(usbdev,
			RNDIS_OID_802_11_CONFIGURATION,
			&config, माप(config));

	netdev_dbg(usbdev->net, "%s(): %d -> %d\n", __func__, channel, ret);

	वापस ret;
पूर्ण

अटल काष्ठा ieee80211_channel *get_current_channel(काष्ठा usbnet *usbdev,
						     u32 *beacon_period)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ieee80211_channel *channel;
	काष्ठा ndis_80211_conf config;
	पूर्णांक len, ret;

	/* Get channel and beacon पूर्णांकerval */
	len = माप(config);
	ret = rndis_query_oid(usbdev,
			RNDIS_OID_802_11_CONFIGURATION,
			&config, &len);
	netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_CONFIGURATION -> %d\n",
				__func__, ret);
	अगर (ret < 0)
		वापस शून्य;

	channel = ieee80211_get_channel(priv->wdev.wiphy,
				KHZ_TO_MHZ(le32_to_cpu(config.ds_config)));
	अगर (!channel)
		वापस शून्य;

	अगर (beacon_period)
		*beacon_period = le32_to_cpu(config.beacon_period);
	वापस channel;
पूर्ण

/* index must be 0 - N, as per NDIS  */
अटल पूर्णांक add_wep_key(काष्ठा usbnet *usbdev, स्थिर u8 *key, पूर्णांक key_len,
								u8 index)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ndis_80211_wep_key ndis_key;
	u32 cipher;
	पूर्णांक ret;

	netdev_dbg(usbdev->net, "%s(idx: %d, len: %d)\n",
		   __func__, index, key_len);

	अगर (index >= RNDIS_WLAN_NUM_KEYS)
		वापस -EINVAL;

	अगर (key_len == 5)
		cipher = WLAN_CIPHER_SUITE_WEP40;
	अन्यथा अगर (key_len == 13)
		cipher = WLAN_CIPHER_SUITE_WEP104;
	अन्यथा
		वापस -EINVAL;

	स_रखो(&ndis_key, 0, माप(ndis_key));

	ndis_key.size = cpu_to_le32(माप(ndis_key));
	ndis_key.length = cpu_to_le32(key_len);
	ndis_key.index = cpu_to_le32(index);
	स_नकल(&ndis_key.material, key, key_len);

	अगर (index == priv->encr_tx_key_index) अणु
		ndis_key.index |= NDIS_80211_ADDWEP_TRANSMIT_KEY;
		ret = set_encr_mode(usbdev, RNDIS_WLAN_ALG_WEP,
							RNDIS_WLAN_ALG_NONE);
		अगर (ret)
			netdev_warn(usbdev->net, "encryption couldn't be enabled (%08X)\n",
				    ret);
	पूर्ण

	ret = rndis_set_oid(usbdev,
			RNDIS_OID_802_11_ADD_WEP, &ndis_key,
			माप(ndis_key));
	अगर (ret != 0) अणु
		netdev_warn(usbdev->net, "adding encryption key %d failed (%08X)\n",
			    index + 1, ret);
		वापस ret;
	पूर्ण

	priv->encr_keys[index].len = key_len;
	priv->encr_keys[index].cipher = cipher;
	स_नकल(&priv->encr_keys[index].material, key, key_len);
	eth_broadcast_addr(priv->encr_keys[index].bssid);

	वापस 0;
पूर्ण

अटल पूर्णांक add_wpa_key(काष्ठा usbnet *usbdev, स्थिर u8 *key, पूर्णांक key_len,
			u8 index, स्थिर u8 *addr, स्थिर u8 *rx_seq,
			पूर्णांक seq_len, u32 cipher, __le32 flags)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ndis_80211_key ndis_key;
	bool is_addr_ok;
	पूर्णांक ret;

	अगर (index >= RNDIS_WLAN_NUM_KEYS) अणु
		netdev_dbg(usbdev->net, "%s(): index out of range (%i)\n",
			   __func__, index);
		वापस -EINVAL;
	पूर्ण
	अगर (key_len > माप(ndis_key.material) || key_len < 0) अणु
		netdev_dbg(usbdev->net, "%s(): key length out of range (%i)\n",
			   __func__, key_len);
		वापस -EINVAL;
	पूर्ण
	अगर (flags & NDIS_80211_ADDKEY_SET_INIT_RECV_SEQ) अणु
		अगर (!rx_seq || seq_len <= 0) अणु
			netdev_dbg(usbdev->net, "%s(): recv seq flag without buffer\n",
				   __func__);
			वापस -EINVAL;
		पूर्ण
		अगर (rx_seq && seq_len > माप(ndis_key.rsc)) अणु
			netdev_dbg(usbdev->net, "%s(): too big recv seq buffer\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	is_addr_ok = addr && !is_zero_ether_addr(addr) &&
					!is_broadcast_ether_addr(addr);
	अगर ((flags & NDIS_80211_ADDKEY_PAIRWISE_KEY) && !is_addr_ok) अणु
		netdev_dbg(usbdev->net, "%s(): pairwise but bssid invalid (%pM)\n",
			   __func__, addr);
		वापस -EINVAL;
	पूर्ण

	netdev_dbg(usbdev->net, "%s(%i): flags:%i%i%i\n",
		   __func__, index,
		   !!(flags & NDIS_80211_ADDKEY_TRANSMIT_KEY),
		   !!(flags & NDIS_80211_ADDKEY_PAIRWISE_KEY),
		   !!(flags & NDIS_80211_ADDKEY_SET_INIT_RECV_SEQ));

	स_रखो(&ndis_key, 0, माप(ndis_key));

	ndis_key.size = cpu_to_le32(माप(ndis_key) -
				माप(ndis_key.material) + key_len);
	ndis_key.length = cpu_to_le32(key_len);
	ndis_key.index = cpu_to_le32(index) | flags;

	अगर (cipher == WLAN_CIPHER_SUITE_TKIP && key_len == 32) अणु
		/* wpa_supplicant gives us the Michael MIC RX/TX keys in
		 * dअगरferent order than NDIS spec, so swap the order here. */
		स_नकल(ndis_key.material, key, 16);
		स_नकल(ndis_key.material + 16, key + 24, 8);
		स_नकल(ndis_key.material + 24, key + 16, 8);
	पूर्ण अन्यथा
		स_नकल(ndis_key.material, key, key_len);

	अगर (flags & NDIS_80211_ADDKEY_SET_INIT_RECV_SEQ)
		स_नकल(ndis_key.rsc, rx_seq, seq_len);

	अगर (flags & NDIS_80211_ADDKEY_PAIRWISE_KEY) अणु
		/* pairwise key */
		स_नकल(ndis_key.bssid, addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* group key */
		अगर (priv->infra_mode == NDIS_80211_INFRA_ADHOC)
			eth_broadcast_addr(ndis_key.bssid);
		अन्यथा
			get_bssid(usbdev, ndis_key.bssid);
	पूर्ण

	ret = rndis_set_oid(usbdev,
			RNDIS_OID_802_11_ADD_KEY, &ndis_key,
			le32_to_cpu(ndis_key.size));
	netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_ADD_KEY -> %08X\n",
		   __func__, ret);
	अगर (ret != 0)
		वापस ret;

	स_रखो(&priv->encr_keys[index], 0, माप(priv->encr_keys[index]));
	priv->encr_keys[index].len = key_len;
	priv->encr_keys[index].cipher = cipher;
	स_नकल(&priv->encr_keys[index].material, key, key_len);
	अगर (flags & NDIS_80211_ADDKEY_PAIRWISE_KEY)
		स_नकल(&priv->encr_keys[index].bssid, ndis_key.bssid, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(priv->encr_keys[index].bssid);

	अगर (flags & NDIS_80211_ADDKEY_TRANSMIT_KEY)
		priv->encr_tx_key_index = index;

	वापस 0;
पूर्ण

अटल पूर्णांक restore_key(काष्ठा usbnet *usbdev, u8 key_idx)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा rndis_wlan_encr_key key;

	अगर (is_wpa_key(priv, key_idx))
		वापस 0;

	key = priv->encr_keys[key_idx];

	netdev_dbg(usbdev->net, "%s(): %i:%i\n", __func__, key_idx, key.len);

	अगर (key.len == 0)
		वापस 0;

	वापस add_wep_key(usbdev, key.material, key.len, key_idx);
पूर्ण

अटल व्योम restore_keys(काष्ठा usbnet *usbdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		restore_key(usbdev, i);
पूर्ण

अटल व्योम clear_key(काष्ठा rndis_wlan_निजी *priv, u8 idx)
अणु
	स_रखो(&priv->encr_keys[idx], 0, माप(priv->encr_keys[idx]));
पूर्ण

/* हटाओ_key is क्रम both wep and wpa */
अटल पूर्णांक हटाओ_key(काष्ठा usbnet *usbdev, u8 index, स्थिर u8 *bssid)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ndis_80211_हटाओ_key हटाओ_key;
	__le32 keyindex;
	bool is_wpa;
	पूर्णांक ret;

	अगर (index >= RNDIS_WLAN_NUM_KEYS)
		वापस -ENOENT;

	अगर (priv->encr_keys[index].len == 0)
		वापस 0;

	is_wpa = is_wpa_key(priv, index);

	netdev_dbg(usbdev->net, "%s(): %i:%s:%i\n",
		   __func__, index, is_wpa ? "wpa" : "wep",
		   priv->encr_keys[index].len);

	clear_key(priv, index);

	अगर (is_wpa) अणु
		हटाओ_key.size = cpu_to_le32(माप(हटाओ_key));
		हटाओ_key.index = cpu_to_le32(index);
		अगर (bssid) अणु
			/* pairwise key */
			अगर (!is_broadcast_ether_addr(bssid))
				हटाओ_key.index |=
					NDIS_80211_ADDKEY_PAIRWISE_KEY;
			स_नकल(हटाओ_key.bssid, bssid,
					माप(हटाओ_key.bssid));
		पूर्ण अन्यथा
			स_रखो(हटाओ_key.bssid, 0xff,
						माप(हटाओ_key.bssid));

		ret = rndis_set_oid(usbdev,
				RNDIS_OID_802_11_REMOVE_KEY,
				&हटाओ_key, माप(हटाओ_key));
		अगर (ret != 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		keyindex = cpu_to_le32(index);
		ret = rndis_set_oid(usbdev,
				RNDIS_OID_802_11_REMOVE_WEP,
				&keyindex, माप(keyindex));
		अगर (ret != 0) अणु
			netdev_warn(usbdev->net,
				    "removing encryption key %d failed (%08X)\n",
				    index, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* अगर it is transmit key, disable encryption */
	अगर (index == priv->encr_tx_key_index)
		set_encr_mode(usbdev, RNDIS_WLAN_ALG_NONE, RNDIS_WLAN_ALG_NONE);

	वापस 0;
पूर्ण

अटल व्योम set_multicast_list(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा netdev_hw_addr *ha;
	__le32 filter, basefilter;
	पूर्णांक ret;
	अक्षर *mc_addrs = शून्य;
	पूर्णांक mc_count;

	basefilter = filter = cpu_to_le32(RNDIS_PACKET_TYPE_सूचीECTED |
					  RNDIS_PACKET_TYPE_BROADCAST);

	अगर (usbdev->net->flags & IFF_PROMISC) अणु
		filter |= cpu_to_le32(RNDIS_PACKET_TYPE_PROMISCUOUS |
				      RNDIS_PACKET_TYPE_ALL_LOCAL);
	पूर्ण अन्यथा अगर (usbdev->net->flags & IFF_ALLMULTI) अणु
		filter |= cpu_to_le32(RNDIS_PACKET_TYPE_ALL_MULTICAST);
	पूर्ण

	अगर (filter != basefilter)
		जाओ set_filter;

	/*
	 * mc_list should be accessed holding the lock, so copy addresses to
	 * local buffer first.
	 */
	netअगर_addr_lock_bh(usbdev->net);
	mc_count = netdev_mc_count(usbdev->net);
	अगर (mc_count > priv->multicast_size) अणु
		filter |= cpu_to_le32(RNDIS_PACKET_TYPE_ALL_MULTICAST);
	पूर्ण अन्यथा अगर (mc_count) अणु
		पूर्णांक i = 0;

		mc_addrs = kदो_स्मृति_array(mc_count, ETH_ALEN, GFP_ATOMIC);
		अगर (!mc_addrs) अणु
			netअगर_addr_unlock_bh(usbdev->net);
			वापस;
		पूर्ण

		netdev_क्रम_each_mc_addr(ha, usbdev->net)
			स_नकल(mc_addrs + i++ * ETH_ALEN,
			       ha->addr, ETH_ALEN);
	पूर्ण
	netअगर_addr_unlock_bh(usbdev->net);

	अगर (filter != basefilter)
		जाओ set_filter;

	अगर (mc_count) अणु
		ret = rndis_set_oid(usbdev,
				RNDIS_OID_802_3_MULTICAST_LIST,
				mc_addrs, mc_count * ETH_ALEN);
		kमुक्त(mc_addrs);
		अगर (ret == 0)
			filter |= cpu_to_le32(RNDIS_PACKET_TYPE_MULTICAST);
		अन्यथा
			filter |= cpu_to_le32(RNDIS_PACKET_TYPE_ALL_MULTICAST);

		netdev_dbg(usbdev->net, "RNDIS_OID_802_3_MULTICAST_LIST(%d, max: %d) -> %d\n",
			   mc_count, priv->multicast_size, ret);
	पूर्ण

set_filter:
	ret = rndis_set_oid(usbdev, RNDIS_OID_GEN_CURRENT_PACKET_FILTER, &filter,
							माप(filter));
	अगर (ret < 0) अणु
		netdev_warn(usbdev->net, "couldn't set packet filter: %08x\n",
			    le32_to_cpu(filter));
	पूर्ण

	netdev_dbg(usbdev->net, "RNDIS_OID_GEN_CURRENT_PACKET_FILTER(%08x) -> %d\n",
		   le32_to_cpu(filter), ret);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम debug_prपूर्णांक_pmkids(काष्ठा usbnet *usbdev,
				काष्ठा ndis_80211_pmkid *pmkids,
				स्थिर अक्षर *func_str)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	पूर्णांक i, len, count, max_pmkids, entry_len;

	max_pmkids = priv->wdev.wiphy->max_num_pmkids;
	len = le32_to_cpu(pmkids->length);
	count = le32_to_cpu(pmkids->bssid_info_count);

	entry_len = (count > 0) ? (len - माप(*pmkids)) / count : -1;

	netdev_dbg(usbdev->net, "%s(): %d PMKIDs (data len: %d, entry len: "
				"%d)\n", func_str, count, len, entry_len);

	अगर (count > max_pmkids)
		count = max_pmkids;

	क्रम (i = 0; i < count; i++) अणु
		u32 *पंचांगp = (u32 *)pmkids->bssid_info[i].pmkid;

		netdev_dbg(usbdev->net, "%s():  bssid: %pM, "
				"pmkid: %08X:%08X:%08X:%08X\n",
				func_str, pmkids->bssid_info[i].bssid,
				cpu_to_be32(पंचांगp[0]), cpu_to_be32(पंचांगp[1]),
				cpu_to_be32(पंचांगp[2]), cpu_to_be32(पंचांगp[3]));
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम debug_prपूर्णांक_pmkids(काष्ठा usbnet *usbdev,
				काष्ठा ndis_80211_pmkid *pmkids,
				स्थिर अक्षर *func_str)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा ndis_80211_pmkid *get_device_pmkids(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ndis_80211_pmkid *pmkids;
	पूर्णांक len, ret, max_pmkids;

	max_pmkids = priv->wdev.wiphy->max_num_pmkids;
	len = काष्ठा_size(pmkids, bssid_info, max_pmkids);

	pmkids = kzalloc(len, GFP_KERNEL);
	अगर (!pmkids)
		वापस ERR_PTR(-ENOMEM);

	pmkids->length = cpu_to_le32(len);
	pmkids->bssid_info_count = cpu_to_le32(max_pmkids);

	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_PMKID,
			pmkids, &len);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_PMKID(%d, %d)"
				" -> %d\n", __func__, len, max_pmkids, ret);

		kमुक्त(pmkids);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (le32_to_cpu(pmkids->bssid_info_count) > max_pmkids)
		pmkids->bssid_info_count = cpu_to_le32(max_pmkids);

	debug_prपूर्णांक_pmkids(usbdev, pmkids, __func__);

	वापस pmkids;
पूर्ण

अटल पूर्णांक set_device_pmkids(काष्ठा usbnet *usbdev,
				काष्ठा ndis_80211_pmkid *pmkids)
अणु
	पूर्णांक ret, len, num_pmkids;

	num_pmkids = le32_to_cpu(pmkids->bssid_info_count);
	len = काष्ठा_size(pmkids, bssid_info, num_pmkids);
	pmkids->length = cpu_to_le32(len);

	debug_prपूर्णांक_pmkids(usbdev, pmkids, __func__);

	ret = rndis_set_oid(usbdev, RNDIS_OID_802_11_PMKID, pmkids,
			    le32_to_cpu(pmkids->length));
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_PMKID(%d, %d) -> %d"
				"\n", __func__, len, num_pmkids, ret);
	पूर्ण

	kमुक्त(pmkids);
	वापस ret;
पूर्ण

अटल काष्ठा ndis_80211_pmkid *हटाओ_pmkid(काष्ठा usbnet *usbdev,
						काष्ठा ndis_80211_pmkid *pmkids,
						काष्ठा cfg80211_pmksa *pmksa,
						पूर्णांक max_pmkids)
अणु
	पूर्णांक i, err;
	अचिन्हित पूर्णांक count;

	count = le32_to_cpu(pmkids->bssid_info_count);

	अगर (count > max_pmkids)
		count = max_pmkids;

	क्रम (i = 0; i < count; i++)
		अगर (ether_addr_equal(pmkids->bssid_info[i].bssid,
				     pmksa->bssid))
			अवरोध;

	/* pmkid not found */
	अगर (i == count) अणु
		netdev_dbg(usbdev->net, "%s(): bssid not found (%pM)\n",
					__func__, pmksa->bssid);
		err = -ENOENT;
		जाओ error;
	पूर्ण

	क्रम (; i + 1 < count; i++)
		pmkids->bssid_info[i] = pmkids->bssid_info[i + 1];

	count--;
	pmkids->length = cpu_to_le32(काष्ठा_size(pmkids, bssid_info, count));
	pmkids->bssid_info_count = cpu_to_le32(count);

	वापस pmkids;
error:
	kमुक्त(pmkids);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा ndis_80211_pmkid *update_pmkid(काष्ठा usbnet *usbdev,
						काष्ठा ndis_80211_pmkid *pmkids,
						काष्ठा cfg80211_pmksa *pmksa,
						पूर्णांक max_pmkids)
अणु
	काष्ठा ndis_80211_pmkid *new_pmkids;
	पूर्णांक i, err, newlen;
	अचिन्हित पूर्णांक count;

	count = le32_to_cpu(pmkids->bssid_info_count);

	अगर (count > max_pmkids)
		count = max_pmkids;

	/* update with new pmkid */
	क्रम (i = 0; i < count; i++) अणु
		अगर (!ether_addr_equal(pmkids->bssid_info[i].bssid,
				      pmksa->bssid))
			जारी;

		स_नकल(pmkids->bssid_info[i].pmkid, pmksa->pmkid,
								WLAN_PMKID_LEN);

		वापस pmkids;
	पूर्ण

	/* out of space, वापस error */
	अगर (i == max_pmkids) अणु
		netdev_dbg(usbdev->net, "%s(): out of space\n", __func__);
		err = -ENOSPC;
		जाओ error;
	पूर्ण

	/* add new pmkid */
	newlen = काष्ठा_size(pmkids, bssid_info, count + 1);

	new_pmkids = kपुनः_स्मृति(pmkids, newlen, GFP_KERNEL);
	अगर (!new_pmkids) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	pmkids = new_pmkids;

	pmkids->length = cpu_to_le32(newlen);
	pmkids->bssid_info_count = cpu_to_le32(count + 1);

	स_नकल(pmkids->bssid_info[count].bssid, pmksa->bssid, ETH_ALEN);
	स_नकल(pmkids->bssid_info[count].pmkid, pmksa->pmkid, WLAN_PMKID_LEN);

	वापस pmkids;
error:
	kमुक्त(pmkids);
	वापस ERR_PTR(err);
पूर्ण

/*
 * cfg80211 ops
 */
अटल पूर्णांक rndis_change_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
					काष्ठा net_device *dev,
					क्रमागत nl80211_अगरtype type,
					काष्ठा vअगर_params *params)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	पूर्णांक mode;

	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		mode = NDIS_80211_INFRA_ADHOC;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		mode = NDIS_80211_INFRA_INFRA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	priv->wdev.अगरtype = type;

	वापस set_infra_mode(usbdev, mode);
पूर्ण

अटल पूर्णांक rndis_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	पूर्णांक err;

	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD) अणु
		err = set_frag_threshold(usbdev, wiphy->frag_threshold);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
		err = set_rts_threshold(usbdev, wiphy->rts_threshold);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rndis_set_tx_घातer(काष्ठा wiphy *wiphy,
			      काष्ठा wireless_dev *wdev,
			      क्रमागत nl80211_tx_घातer_setting type,
			      पूर्णांक mbm)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	netdev_dbg(usbdev->net, "%s(): type:0x%x mbm:%i\n",
		   __func__, type, mbm);

	अगर (mbm < 0 || (mbm % 100))
		वापस -ENOTSUPP;

	/* Device करोesn't support changing txघातer after initialization, only
	 * turn off/on radio. Support 'auto' mode and setting same dBm that is
	 * currently used.
	 */
	अगर (type == NL80211_TX_POWER_AUTOMATIC ||
	    MBM_TO_DBM(mbm) == get_bcm4320_घातer_dbm(priv)) अणु
		अगर (!priv->radio_on)
			disassociate(usbdev, true); /* turn on radio */

		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक rndis_get_tx_घातer(काष्ठा wiphy *wiphy,
			      काष्ठा wireless_dev *wdev,
			      पूर्णांक *dbm)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	*dbm = get_bcm4320_घातer_dbm(priv);

	netdev_dbg(usbdev->net, "%s(): dbm:%i\n", __func__, *dbm);

	वापस 0;
पूर्ण

#घोषणा SCAN_DELAY_JIFFIES (6 * HZ)
अटल पूर्णांक rndis_scan(काष्ठा wiphy *wiphy,
			काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा net_device *dev = request->wdev->netdev;
	काष्ठा usbnet *usbdev = netdev_priv(dev);
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	पूर्णांक ret;
	पूर्णांक delay = SCAN_DELAY_JIFFIES;

	netdev_dbg(usbdev->net, "cfg80211.scan\n");

	/* Get current bssid list from device beक्रमe new scan, as new scan
	 * clears पूर्णांकernal bssid list.
	 */
	rndis_check_bssid_list(usbdev, शून्य, शून्य);

	अगर (priv->scan_request && priv->scan_request != request)
		वापस -EBUSY;

	priv->scan_request = request;

	ret = rndis_start_bssid_list_scan(usbdev);
	अगर (ret == 0) अणु
		अगर (priv->device_type == RNDIS_BCM4320A)
			delay = HZ;

		/* Wait beक्रमe retrieving scan results from device */
		queue_delayed_work(priv->workqueue, &priv->scan_work, delay);
	पूर्ण

	वापस ret;
पूर्ण

अटल bool rndis_bss_info_update(काष्ठा usbnet *usbdev,
				  काष्ठा ndis_80211_bssid_ex *bssid)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ieee80211_channel *channel;
	काष्ठा cfg80211_bss *bss;
	s32 संकेत;
	u64 बारtamp;
	u16 capability;
	u16 beacon_पूर्णांकerval;
	काष्ठा ndis_80211_fixed_ies *fixed;
	पूर्णांक ie_len, bssid_len;
	u8 *ie;

	netdev_dbg(usbdev->net, " found bssid: '%.32s' [%pM], len: %d\n",
		   bssid->ssid.essid, bssid->mac, le32_to_cpu(bssid->length));

	/* parse bssid काष्ठाure */
	bssid_len = le32_to_cpu(bssid->length);

	अगर (bssid_len < माप(काष्ठा ndis_80211_bssid_ex) +
			माप(काष्ठा ndis_80211_fixed_ies))
		वापस शून्य;

	fixed = (काष्ठा ndis_80211_fixed_ies *)bssid->ies;

	ie = (व्योम *)(bssid->ies + माप(काष्ठा ndis_80211_fixed_ies));
	ie_len = min(bssid_len - (पूर्णांक)माप(*bssid),
					(पूर्णांक)le32_to_cpu(bssid->ie_length));
	ie_len -= माप(काष्ठा ndis_80211_fixed_ies);
	अगर (ie_len < 0)
		वापस शून्य;

	/* extract data क्रम cfg80211_inक्रमm_bss */
	channel = ieee80211_get_channel(priv->wdev.wiphy,
			KHZ_TO_MHZ(le32_to_cpu(bssid->config.ds_config)));
	अगर (!channel)
		वापस शून्य;

	संकेत = level_to_qual(le32_to_cpu(bssid->rssi));
	बारtamp = le64_to_cpu(*(__le64 *)fixed->बारtamp);
	capability = le16_to_cpu(fixed->capabilities);
	beacon_पूर्णांकerval = le16_to_cpu(fixed->beacon_पूर्णांकerval);

	bss = cfg80211_inक्रमm_bss(priv->wdev.wiphy, channel,
				  CFG80211_BSS_FTYPE_UNKNOWN, bssid->mac,
				  बारtamp, capability, beacon_पूर्णांकerval,
				  ie, ie_len, संकेत, GFP_KERNEL);
	cfg80211_put_bss(priv->wdev.wiphy, bss);

	वापस (bss != शून्य);
पूर्ण

अटल काष्ठा ndis_80211_bssid_ex *next_bssid_list_item(
					काष्ठा ndis_80211_bssid_ex *bssid,
					पूर्णांक *bssid_len, व्योम *buf, पूर्णांक len)
अणु
	व्योम *buf_end, *bssid_end;

	buf_end = (अक्षर *)buf + len;
	bssid_end = (अक्षर *)bssid + *bssid_len;

	अगर ((पूर्णांक)(buf_end - bssid_end) < माप(bssid->length)) अणु
		*bssid_len = 0;
		वापस शून्य;
	पूर्ण अन्यथा अणु
		bssid = (व्योम *)((अक्षर *)bssid + *bssid_len);
		*bssid_len = le32_to_cpu(bssid->length);
		वापस bssid;
	पूर्ण
पूर्ण

अटल bool check_bssid_list_item(काष्ठा ndis_80211_bssid_ex *bssid,
				  पूर्णांक bssid_len, व्योम *buf, पूर्णांक len)
अणु
	व्योम *buf_end, *bssid_end;

	अगर (!bssid || bssid_len <= 0 || bssid_len > len)
		वापस false;

	buf_end = (अक्षर *)buf + len;
	bssid_end = (अक्षर *)bssid + bssid_len;

	वापस (पूर्णांक)(buf_end - bssid_end) >= 0 && (पूर्णांक)(bssid_end - buf) >= 0;
पूर्ण

अटल पूर्णांक rndis_check_bssid_list(काष्ठा usbnet *usbdev, u8 *match_bssid,
					bool *matched)
अणु
	व्योम *buf = शून्य;
	काष्ठा ndis_80211_bssid_list_ex *bssid_list;
	काष्ठा ndis_80211_bssid_ex *bssid;
	पूर्णांक ret = -EINVAL, len, count, bssid_len, real_count, new_len;

	netdev_dbg(usbdev->net, "%s()\n", __func__);

	len = CONTROL_BUFFER_SIZE;
resize_buf:
	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* BSSID-list might have got bigger last समय we checked, keep
	 * resizing until it won't get any bigger.
	 */
	new_len = len;
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_BSSID_LIST,
			      buf, &new_len);
	अगर (ret != 0 || new_len < माप(काष्ठा ndis_80211_bssid_list_ex))
		जाओ out;

	अगर (new_len > len) अणु
		len = new_len;
		kमुक्त(buf);
		जाओ resize_buf;
	पूर्ण

	len = new_len;

	bssid_list = buf;
	count = le32_to_cpu(bssid_list->num_items);
	real_count = 0;
	netdev_dbg(usbdev->net, "%s(): buflen: %d\n", __func__, len);

	bssid_len = 0;
	bssid = next_bssid_list_item(bssid_list->bssid, &bssid_len, buf, len);

	/* Device वापसs incorrect 'num_items'. Workaround by ignoring the
	 * received 'num_items' and walking through full bssid buffer instead.
	 */
	जबतक (check_bssid_list_item(bssid, bssid_len, buf, len)) अणु
		अगर (rndis_bss_info_update(usbdev, bssid) && match_bssid &&
		    matched) अणु
			अगर (ether_addr_equal(bssid->mac, match_bssid))
				*matched = true;
		पूर्ण

		real_count++;
		bssid = next_bssid_list_item(bssid, &bssid_len, buf, len);
	पूर्ण

	netdev_dbg(usbdev->net, "%s(): num_items from device: %d, really found:"
				" %d\n", __func__, count, real_count);

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम rndis_get_scan_results(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rndis_wlan_निजी *priv =
		container_of(work, काष्ठा rndis_wlan_निजी, scan_work.work);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा cfg80211_scan_info info = अणुपूर्ण;
	पूर्णांक ret;

	netdev_dbg(usbdev->net, "get_scan_results\n");

	अगर (!priv->scan_request)
		वापस;

	ret = rndis_check_bssid_list(usbdev, शून्य, शून्य);

	info.पातed = ret < 0;
	cfg80211_scan_करोne(priv->scan_request, &info);

	priv->scan_request = शून्य;
पूर्ण

अटल पूर्णांक rndis_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
					काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा ieee80211_channel *channel = sme->channel;
	काष्ठा ndis_80211_ssid ssid;
	पूर्णांक pairwise = RNDIS_WLAN_ALG_NONE;
	पूर्णांक groupwise = RNDIS_WLAN_ALG_NONE;
	पूर्णांक keymgmt = RNDIS_WLAN_KEY_MGMT_NONE;
	पूर्णांक length, i, ret, chan = -1;

	अगर (channel)
		chan = ieee80211_frequency_to_channel(channel->center_freq);

	groupwise = rndis_cipher_to_alg(sme->crypto.cipher_group);
	क्रम (i = 0; i < sme->crypto.n_ciphers_pairwise; i++)
		pairwise |=
			rndis_cipher_to_alg(sme->crypto.ciphers_pairwise[i]);

	अगर (sme->crypto.n_ciphers_pairwise > 0 &&
			pairwise == RNDIS_WLAN_ALG_NONE) अणु
		netdev_err(usbdev->net, "Unsupported pairwise cipher\n");
		वापस -ENOTSUPP;
	पूर्ण

	क्रम (i = 0; i < sme->crypto.n_akm_suites; i++)
		keymgmt |=
			rndis_akm_suite_to_key_mgmt(sme->crypto.akm_suites[i]);

	अगर (sme->crypto.n_akm_suites > 0 &&
			keymgmt == RNDIS_WLAN_KEY_MGMT_NONE) अणु
		netdev_err(usbdev->net, "Invalid keymgmt\n");
		वापस -ENOTSUPP;
	पूर्ण

	netdev_dbg(usbdev->net, "cfg80211.connect('%.32s':[%pM]:%d:[%d,0x%x:0x%x]:[0x%x:0x%x]:0x%x)\n",
		   sme->ssid, sme->bssid, chan,
		   sme->privacy, sme->crypto.wpa_versions, sme->auth_type,
		   groupwise, pairwise, keymgmt);

	अगर (is_associated(usbdev))
		disassociate(usbdev, false);

	ret = set_infra_mode(usbdev, NDIS_80211_INFRA_INFRA);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "connect: set_infra_mode failed, %d\n",
			   ret);
		जाओ err_turn_radio_on;
	पूर्ण

	ret = set_auth_mode(usbdev, sme->crypto.wpa_versions, sme->auth_type,
								keymgmt);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "connect: set_auth_mode failed, %d\n",
			   ret);
		जाओ err_turn_radio_on;
	पूर्ण

	set_priv_filter(usbdev);

	ret = set_encr_mode(usbdev, pairwise, groupwise);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "connect: set_encr_mode failed, %d\n",
			   ret);
		जाओ err_turn_radio_on;
	पूर्ण

	अगर (channel) अणु
		ret = set_channel(usbdev, chan);
		अगर (ret < 0) अणु
			netdev_dbg(usbdev->net, "connect: set_channel failed, %d\n",
				   ret);
			जाओ err_turn_radio_on;
		पूर्ण
	पूर्ण

	अगर (sme->key && ((groupwise | pairwise) & RNDIS_WLAN_ALG_WEP)) अणु
		priv->encr_tx_key_index = sme->key_idx;
		ret = add_wep_key(usbdev, sme->key, sme->key_len, sme->key_idx);
		अगर (ret < 0) अणु
			netdev_dbg(usbdev->net, "connect: add_wep_key failed, %d (%d, %d)\n",
				   ret, sme->key_len, sme->key_idx);
			जाओ err_turn_radio_on;
		पूर्ण
	पूर्ण

	अगर (sme->bssid && !is_zero_ether_addr(sme->bssid) &&
				!is_broadcast_ether_addr(sme->bssid)) अणु
		ret = set_bssid(usbdev, sme->bssid);
		अगर (ret < 0) अणु
			netdev_dbg(usbdev->net, "connect: set_bssid failed, %d\n",
				   ret);
			जाओ err_turn_radio_on;
		पूर्ण
	पूर्ण अन्यथा
		clear_bssid(usbdev);

	length = sme->ssid_len;
	अगर (length > NDIS_802_11_LENGTH_SSID)
		length = NDIS_802_11_LENGTH_SSID;

	स_रखो(&ssid, 0, माप(ssid));
	ssid.length = cpu_to_le32(length);
	स_नकल(ssid.essid, sme->ssid, length);

	/* Pause and purge rx queue, so we करोn't pass packets beक्रमe
	 * 'media connect'-indication.
	 */
	usbnet_छोड़ो_rx(usbdev);
	usbnet_purge_छोड़ोd_rxq(usbdev);

	ret = set_essid(usbdev, &ssid);
	अगर (ret < 0)
		netdev_dbg(usbdev->net, "connect: set_essid failed, %d\n", ret);
	वापस ret;

err_turn_radio_on:
	disassociate(usbdev, true);

	वापस ret;
पूर्ण

अटल पूर्णांक rndis_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
								u16 reason_code)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	netdev_dbg(usbdev->net, "cfg80211.disconnect(%d)\n", reason_code);

	priv->connected = false;
	eth_zero_addr(priv->bssid);

	वापस deauthenticate(usbdev);
पूर्ण

अटल पूर्णांक rndis_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
					काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा ieee80211_channel *channel = params->chandef.chan;
	काष्ठा ndis_80211_ssid ssid;
	क्रमागत nl80211_auth_type auth_type;
	पूर्णांक ret, alg, length, chan = -1;

	अगर (channel)
		chan = ieee80211_frequency_to_channel(channel->center_freq);

	/* TODO: How to handle ad-hoc encryption?
	 * connect() has *key, join_ibss() करोesn't. RNDIS requires key to be
	 * pre-shared क्रम encryption (खोलो/shared/wpa), is key set beक्रमe
	 * join_ibss? Which auth_type to use (not in params)? What about WPA?
	 */
	अगर (params->privacy) अणु
		auth_type = NL80211_AUTHTYPE_SHARED_KEY;
		alg = RNDIS_WLAN_ALG_WEP;
	पूर्ण अन्यथा अणु
		auth_type = NL80211_AUTHTYPE_OPEN_SYSTEM;
		alg = RNDIS_WLAN_ALG_NONE;
	पूर्ण

	netdev_dbg(usbdev->net, "cfg80211.join_ibss('%.32s':[%pM]:%d:%d)\n",
		   params->ssid, params->bssid, chan, params->privacy);

	अगर (is_associated(usbdev))
		disassociate(usbdev, false);

	ret = set_infra_mode(usbdev, NDIS_80211_INFRA_ADHOC);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "join_ibss: set_infra_mode failed, %d\n",
			   ret);
		जाओ err_turn_radio_on;
	पूर्ण

	ret = set_auth_mode(usbdev, 0, auth_type, RNDIS_WLAN_KEY_MGMT_NONE);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "join_ibss: set_auth_mode failed, %d\n",
			   ret);
		जाओ err_turn_radio_on;
	पूर्ण

	set_priv_filter(usbdev);

	ret = set_encr_mode(usbdev, alg, RNDIS_WLAN_ALG_NONE);
	अगर (ret < 0) अणु
		netdev_dbg(usbdev->net, "join_ibss: set_encr_mode failed, %d\n",
			   ret);
		जाओ err_turn_radio_on;
	पूर्ण

	अगर (channel) अणु
		ret = set_channel(usbdev, chan);
		अगर (ret < 0) अणु
			netdev_dbg(usbdev->net, "join_ibss: set_channel failed, %d\n",
				   ret);
			जाओ err_turn_radio_on;
		पूर्ण
	पूर्ण

	अगर (params->bssid && !is_zero_ether_addr(params->bssid) &&
				!is_broadcast_ether_addr(params->bssid)) अणु
		ret = set_bssid(usbdev, params->bssid);
		अगर (ret < 0) अणु
			netdev_dbg(usbdev->net, "join_ibss: set_bssid failed, %d\n",
				   ret);
			जाओ err_turn_radio_on;
		पूर्ण
	पूर्ण अन्यथा
		clear_bssid(usbdev);

	length = params->ssid_len;
	अगर (length > NDIS_802_11_LENGTH_SSID)
		length = NDIS_802_11_LENGTH_SSID;

	स_रखो(&ssid, 0, माप(ssid));
	ssid.length = cpu_to_le32(length);
	स_नकल(ssid.essid, params->ssid, length);

	/* Don't need to छोड़ो rx queue क्रम ad-hoc. */
	usbnet_purge_छोड़ोd_rxq(usbdev);
	usbnet_resume_rx(usbdev);

	ret = set_essid(usbdev, &ssid);
	अगर (ret < 0)
		netdev_dbg(usbdev->net, "join_ibss: set_essid failed, %d\n",
			   ret);
	वापस ret;

err_turn_radio_on:
	disassociate(usbdev, true);

	वापस ret;
पूर्ण

अटल पूर्णांक rndis_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	netdev_dbg(usbdev->net, "cfg80211.leave_ibss()\n");

	priv->connected = false;
	eth_zero_addr(priv->bssid);

	वापस deauthenticate(usbdev);
पूर्ण

अटल पूर्णांक rndis_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			 u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			 काष्ठा key_params *params)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	__le32 flags;

	netdev_dbg(usbdev->net, "%s(%i, %pM, %08x)\n",
		   __func__, key_index, mac_addr, params->cipher);

	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस add_wep_key(usbdev, params->key, params->key_len,
								key_index);
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
		flags = 0;

		अगर (params->seq && params->seq_len > 0)
			flags |= NDIS_80211_ADDKEY_SET_INIT_RECV_SEQ;
		अगर (mac_addr)
			flags |= NDIS_80211_ADDKEY_PAIRWISE_KEY |
					NDIS_80211_ADDKEY_TRANSMIT_KEY;

		वापस add_wpa_key(usbdev, params->key, params->key_len,
				key_index, mac_addr, params->seq,
				params->seq_len, params->cipher, flags);
	शेष:
		netdev_dbg(usbdev->net, "%s(): unsupported cipher %08x\n",
			   __func__, params->cipher);
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक rndis_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			 u8 key_index, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	netdev_dbg(usbdev->net, "%s(%i, %pM)\n", __func__, key_index, mac_addr);

	वापस हटाओ_key(usbdev, key_index, mac_addr);
पूर्ण

अटल पूर्णांक rndis_set_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				 u8 key_index, bool unicast, bool multicast)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा rndis_wlan_encr_key key;

	netdev_dbg(usbdev->net, "%s(%i)\n", __func__, key_index);

	अगर (key_index >= RNDIS_WLAN_NUM_KEYS)
		वापस -ENOENT;

	priv->encr_tx_key_index = key_index;

	अगर (is_wpa_key(priv, key_index))
		वापस 0;

	key = priv->encr_keys[key_index];

	वापस add_wep_key(usbdev, key.material, key.len, key_index);
पूर्ण

अटल व्योम rndis_fill_station_info(काष्ठा usbnet *usbdev,
						काष्ठा station_info *sinfo)
अणु
	__le32 linkspeed, rssi;
	पूर्णांक ret, len;

	स_रखो(sinfo, 0, माप(*sinfo));

	len = माप(linkspeed);
	ret = rndis_query_oid(usbdev, RNDIS_OID_GEN_LINK_SPEED, &linkspeed, &len);
	अगर (ret == 0) अणु
		sinfo->txrate.legacy = le32_to_cpu(linkspeed) / 1000;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	पूर्ण

	len = माप(rssi);
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_RSSI,
			      &rssi, &len);
	अगर (ret == 0) अणु
		sinfo->संकेत = level_to_qual(le32_to_cpu(rssi));
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	पूर्ण
पूर्ण

अटल पूर्णांक rndis_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	अगर (!ether_addr_equal(priv->bssid, mac))
		वापस -ENOENT;

	rndis_fill_station_info(usbdev, sinfo);

	वापस 0;
पूर्ण

अटल पूर्णांक rndis_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;

	अगर (idx != 0)
		वापस -ENOENT;

	स_नकल(mac, priv->bssid, ETH_ALEN);

	rndis_fill_station_info(usbdev, sinfo);

	वापस 0;
पूर्ण

अटल पूर्णांक rndis_set_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा ndis_80211_pmkid *pmkids;
	u32 *पंचांगp = (u32 *)pmksa->pmkid;

	netdev_dbg(usbdev->net, "%s(%pM, %08X:%08X:%08X:%08X)\n", __func__,
			pmksa->bssid,
			cpu_to_be32(पंचांगp[0]), cpu_to_be32(पंचांगp[1]),
			cpu_to_be32(पंचांगp[2]), cpu_to_be32(पंचांगp[3]));

	pmkids = get_device_pmkids(usbdev);
	अगर (IS_ERR(pmkids)) अणु
		/* couldn't पढ़ो PMKID cache from device */
		वापस PTR_ERR(pmkids);
	पूर्ण

	pmkids = update_pmkid(usbdev, pmkids, pmksa, wiphy->max_num_pmkids);
	अगर (IS_ERR(pmkids)) अणु
		/* not found, list full, etc */
		वापस PTR_ERR(pmkids);
	पूर्ण

	वापस set_device_pmkids(usbdev, pmkids);
पूर्ण

अटल पूर्णांक rndis_del_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा ndis_80211_pmkid *pmkids;
	u32 *पंचांगp = (u32 *)pmksa->pmkid;

	netdev_dbg(usbdev->net, "%s(%pM, %08X:%08X:%08X:%08X)\n", __func__,
			pmksa->bssid,
			cpu_to_be32(पंचांगp[0]), cpu_to_be32(पंचांगp[1]),
			cpu_to_be32(पंचांगp[2]), cpu_to_be32(पंचांगp[3]));

	pmkids = get_device_pmkids(usbdev);
	अगर (IS_ERR(pmkids)) अणु
		/* Couldn't पढ़ो PMKID cache from device */
		वापस PTR_ERR(pmkids);
	पूर्ण

	pmkids = हटाओ_pmkid(usbdev, pmkids, pmksa, wiphy->max_num_pmkids);
	अगर (IS_ERR(pmkids)) अणु
		/* not found, etc */
		वापस PTR_ERR(pmkids);
	पूर्ण

	वापस set_device_pmkids(usbdev, pmkids);
पूर्ण

अटल पूर्णांक rndis_flush_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	काष्ठा ndis_80211_pmkid pmkid;

	netdev_dbg(usbdev->net, "%s()\n", __func__);

	स_रखो(&pmkid, 0, माप(pmkid));

	pmkid.length = cpu_to_le32(माप(pmkid));
	pmkid.bssid_info_count = cpu_to_le32(0);

	वापस rndis_set_oid(usbdev, RNDIS_OID_802_11_PMKID,
			     &pmkid, माप(pmkid));
पूर्ण

अटल पूर्णांक rndis_set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				bool enabled, पूर्णांक समयout)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);
	काष्ठा usbnet *usbdev = priv->usbdev;
	पूर्णांक घातer_mode;
	__le32 mode;
	पूर्णांक ret;

	अगर (priv->device_type != RNDIS_BCM4320B)
		वापस -ENOTSUPP;

	netdev_dbg(usbdev->net, "%s(): %s, %d\n", __func__,
				enabled ? "enabled" : "disabled",
				समयout);

	अगर (enabled)
		घातer_mode = NDIS_80211_POWER_MODE_FAST_PSP;
	अन्यथा
		घातer_mode = NDIS_80211_POWER_MODE_CAM;

	अगर (घातer_mode == priv->घातer_mode)
		वापस 0;

	priv->घातer_mode = घातer_mode;

	mode = cpu_to_le32(घातer_mode);
	ret = rndis_set_oid(usbdev, RNDIS_OID_802_11_POWER_MODE,
			    &mode, माप(mode));

	netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_POWER_MODE -> %d\n",
				__func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rndis_set_cqm_rssi_config(काष्ठा wiphy *wiphy,
					काष्ठा net_device *dev,
					s32 rssi_thold, u32 rssi_hyst)
अणु
	काष्ठा rndis_wlan_निजी *priv = wiphy_priv(wiphy);

	priv->cqm_rssi_thold = rssi_thold;
	priv->cqm_rssi_hyst = rssi_hyst;
	priv->last_cqm_event_rssi = 0;

	वापस 0;
पूर्ण

अटल व्योम rndis_wlan_craft_connected_bss(काष्ठा usbnet *usbdev, u8 *bssid,
					   काष्ठा ndis_80211_assoc_info *info)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ieee80211_channel *channel;
	काष्ठा ndis_80211_ssid ssid;
	काष्ठा cfg80211_bss *bss;
	s32 संकेत;
	u64 बारtamp;
	u16 capability;
	u32 beacon_period = 0;
	__le32 rssi;
	u8 ie_buf[34];
	पूर्णांक len, ret, ie_len;

	/* Get संकेत quality, in हाल of error use rssi=0 and ignore error. */
	len = माप(rssi);
	rssi = 0;
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_RSSI,
			      &rssi, &len);
	संकेत = level_to_qual(le32_to_cpu(rssi));

	netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_RSSI -> %d, "
		   "rssi:%d, qual: %d\n", __func__, ret, le32_to_cpu(rssi),
		   level_to_qual(le32_to_cpu(rssi)));

	/* Get AP capabilities */
	अगर (info) अणु
		capability = le16_to_cpu(info->resp_ie.capa);
	पूर्ण अन्यथा अणु
		/* Set atleast ESS/IBSS capability */
		capability = (priv->infra_mode == NDIS_80211_INFRA_INFRA) ?
				WLAN_CAPABILITY_ESS : WLAN_CAPABILITY_IBSS;
	पूर्ण

	/* Get channel and beacon पूर्णांकerval */
	channel = get_current_channel(usbdev, &beacon_period);
	अगर (!channel) अणु
		netdev_warn(usbdev->net, "%s(): could not get channel.\n",
					__func__);
		वापस;
	पूर्ण

	/* Get SSID, in हाल of error, use zero length SSID and ignore error. */
	len = माप(ssid);
	स_रखो(&ssid, 0, माप(ssid));
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_SSID,
			      &ssid, &len);
	netdev_dbg(usbdev->net, "%s(): RNDIS_OID_802_11_SSID -> %d, len: %d, ssid: "
				"'%.32s'\n", __func__, ret,
				le32_to_cpu(ssid.length), ssid.essid);

	अगर (le32_to_cpu(ssid.length) > 32)
		ssid.length = cpu_to_le32(32);

	ie_buf[0] = WLAN_EID_SSID;
	ie_buf[1] = le32_to_cpu(ssid.length);
	स_नकल(&ie_buf[2], ssid.essid, le32_to_cpu(ssid.length));

	ie_len = le32_to_cpu(ssid.length) + 2;

	/* no tsf */
	बारtamp = 0;

	netdev_dbg(usbdev->net, "%s(): channel:%d(freq), bssid:[%pM], tsf:%d, "
		"capa:%x, beacon int:%d, resp_ie(len:%d, essid:'%.32s'), "
		"signal:%d\n", __func__, (channel ? channel->center_freq : -1),
		bssid, (u32)बारtamp, capability, beacon_period, ie_len,
		ssid.essid, संकेत);

	bss = cfg80211_inक्रमm_bss(priv->wdev.wiphy, channel,
				  CFG80211_BSS_FTYPE_UNKNOWN, bssid,
				  बारtamp, capability, beacon_period,
				  ie_buf, ie_len, संकेत, GFP_KERNEL);
	cfg80211_put_bss(priv->wdev.wiphy, bss);
पूर्ण

/*
 * workers, indication handlers, device poller
 */
अटल व्योम rndis_wlan_करो_link_up_work(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा ndis_80211_assoc_info *info = शून्य;
	u8 bssid[ETH_ALEN];
	अचिन्हित पूर्णांक resp_ie_len, req_ie_len;
	अचिन्हित पूर्णांक offset;
	u8 *req_ie, *resp_ie;
	पूर्णांक ret;
	bool roamed = false;
	bool match_bss;

	अगर (priv->infra_mode == NDIS_80211_INFRA_INFRA && priv->connected) अणु
		/* received media connect indication जबतक connected, either
		 * device reassociated with same AP or roamed to new. */
		roamed = true;
	पूर्ण

	req_ie_len = 0;
	resp_ie_len = 0;
	req_ie = शून्य;
	resp_ie = शून्य;

	अगर (priv->infra_mode == NDIS_80211_INFRA_INFRA) अणु
		info = kzalloc(CONTROL_BUFFER_SIZE, GFP_KERNEL);
		अगर (!info) अणु
			/* No memory? Try resume work later */
			set_bit(WORK_LINK_UP, &priv->work_pending);
			queue_work(priv->workqueue, &priv->work);
			वापस;
		पूर्ण

		/* Get association info IEs from device. */
		ret = get_association_info(usbdev, info, CONTROL_BUFFER_SIZE);
		अगर (!ret) अणु
			req_ie_len = le32_to_cpu(info->req_ie_length);
			अगर (req_ie_len > CONTROL_BUFFER_SIZE)
				req_ie_len = CONTROL_BUFFER_SIZE;
			अगर (req_ie_len != 0) अणु
				offset = le32_to_cpu(info->offset_req_ies);

				अगर (offset > CONTROL_BUFFER_SIZE)
					offset = CONTROL_BUFFER_SIZE;

				req_ie = (u8 *)info + offset;

				अगर (offset + req_ie_len > CONTROL_BUFFER_SIZE)
					req_ie_len =
						CONTROL_BUFFER_SIZE - offset;
			पूर्ण

			resp_ie_len = le32_to_cpu(info->resp_ie_length);
			अगर (resp_ie_len > CONTROL_BUFFER_SIZE)
				resp_ie_len = CONTROL_BUFFER_SIZE;
			अगर (resp_ie_len != 0) अणु
				offset = le32_to_cpu(info->offset_resp_ies);

				अगर (offset > CONTROL_BUFFER_SIZE)
					offset = CONTROL_BUFFER_SIZE;

				resp_ie = (u8 *)info + offset;

				अगर (offset + resp_ie_len > CONTROL_BUFFER_SIZE)
					resp_ie_len =
						CONTROL_BUFFER_SIZE - offset;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Since rndis_wlan_craft_connected_bss() might use info
			 * later and expects info to contain valid data अगर
			 * non-null, मुक्त info and set शून्य here.
			 */
			kमुक्त(info);
			info = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (WARN_ON(priv->infra_mode != NDIS_80211_INFRA_ADHOC))
		वापस;

	ret = get_bssid(usbdev, bssid);
	अगर (ret < 0)
		स_रखो(bssid, 0, माप(bssid));

	netdev_dbg(usbdev->net, "link up work: [%pM]%s\n",
		   bssid, roamed ? " roamed" : "");

	/* Internal bss list in device should contain at least the currently
	 * connected bss and we can get it to cfg80211 with
	 * rndis_check_bssid_list().
	 *
	 * NDIS spec says: "If the device is associated, but the associated
	 *  BSSID is not in its BSSID scan list, then the driver must add an
	 *  entry क्रम the BSSID at the end of the data that it वापसs in
	 *  response to query of RNDIS_OID_802_11_BSSID_LIST."
	 *
	 * NOTE: Seems to be true क्रम BCM4320b variant, but not BCM4320a.
	 */
	match_bss = false;
	rndis_check_bssid_list(usbdev, bssid, &match_bss);

	अगर (!is_zero_ether_addr(bssid) && !match_bss) अणु
		/* Couldn't get bss from device, we need to manually craft bss
		 * क्रम cfg80211.
		 */
		rndis_wlan_craft_connected_bss(usbdev, bssid, info);
	पूर्ण

	अगर (priv->infra_mode == NDIS_80211_INFRA_INFRA) अणु
		अगर (!roamed) अणु
			cfg80211_connect_result(usbdev->net, bssid, req_ie,
						req_ie_len, resp_ie,
						resp_ie_len, 0, GFP_KERNEL);
		पूर्ण अन्यथा अणु
			काष्ठा cfg80211_roam_info roam_info = अणु
				.channel = get_current_channel(usbdev, शून्य),
				.bssid = bssid,
				.req_ie = req_ie,
				.req_ie_len = req_ie_len,
				.resp_ie = resp_ie,
				.resp_ie_len = resp_ie_len,
			पूर्ण;

			cfg80211_roamed(usbdev->net, &roam_info, GFP_KERNEL);
		पूर्ण
	पूर्ण अन्यथा अगर (priv->infra_mode == NDIS_80211_INFRA_ADHOC)
		cfg80211_ibss_joined(usbdev->net, bssid,
				     get_current_channel(usbdev, शून्य),
				     GFP_KERNEL);

	kमुक्त(info);

	priv->connected = true;
	स_नकल(priv->bssid, bssid, ETH_ALEN);

	usbnet_resume_rx(usbdev);
	netअगर_carrier_on(usbdev->net);
पूर्ण

अटल व्योम rndis_wlan_करो_link_करोwn_work(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);

	अगर (priv->connected) अणु
		priv->connected = false;
		eth_zero_addr(priv->bssid);

		deauthenticate(usbdev);

		cfg80211_disconnected(usbdev->net, 0, शून्य, 0, true, GFP_KERNEL);
	पूर्ण

	netअगर_carrier_off(usbdev->net);
पूर्ण

अटल व्योम rndis_wlan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rndis_wlan_निजी *priv =
		container_of(work, काष्ठा rndis_wlan_निजी, work);
	काष्ठा usbnet *usbdev = priv->usbdev;

	अगर (test_and_clear_bit(WORK_LINK_UP, &priv->work_pending))
		rndis_wlan_करो_link_up_work(usbdev);

	अगर (test_and_clear_bit(WORK_LINK_DOWN, &priv->work_pending))
		rndis_wlan_करो_link_करोwn_work(usbdev);

	अगर (test_and_clear_bit(WORK_SET_MULTICAST_LIST, &priv->work_pending))
		set_multicast_list(usbdev);
पूर्ण

अटल व्योम rndis_wlan_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा usbnet *usbdev = netdev_priv(dev);
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);

	अगर (test_bit(WORK_SET_MULTICAST_LIST, &priv->work_pending))
		वापस;

	set_bit(WORK_SET_MULTICAST_LIST, &priv->work_pending);
	queue_work(priv->workqueue, &priv->work);
पूर्ण

अटल व्योम rndis_wlan_auth_indication(काष्ठा usbnet *usbdev,
				काष्ठा ndis_80211_status_indication *indication,
				पूर्णांक len)
अणु
	u8 *buf;
	स्थिर अक्षर *type;
	पूर्णांक flags, buflen, key_id;
	bool pairwise_error, group_error;
	काष्ठा ndis_80211_auth_request *auth_req;
	क्रमागत nl80211_key_type key_type;

	/* must have at least one array entry */
	अगर (len < दुरत्व(काष्ठा ndis_80211_status_indication, u) +
				माप(काष्ठा ndis_80211_auth_request)) अणु
		netdev_info(usbdev->net, "authentication indication: too short message (%i)\n",
			    len);
		वापस;
	पूर्ण

	buf = (व्योम *)&indication->u.auth_request[0];
	buflen = len - दुरत्व(काष्ठा ndis_80211_status_indication, u);

	जबतक (buflen >= माप(*auth_req)) अणु
		auth_req = (व्योम *)buf;
		अगर (buflen < le32_to_cpu(auth_req->length))
			वापस;
		type = "unknown";
		flags = le32_to_cpu(auth_req->flags);
		pairwise_error = false;
		group_error = false;

		अगर (flags & 0x1)
			type = "reauth request";
		अगर (flags & 0x2)
			type = "key update request";
		अगर (flags & 0x6) अणु
			pairwise_error = true;
			type = "pairwise_error";
		पूर्ण
		अगर (flags & 0xe) अणु
			group_error = true;
			type = "group_error";
		पूर्ण

		netdev_info(usbdev->net, "authentication indication: %s (0x%08x)\n",
			    type, le32_to_cpu(auth_req->flags));

		अगर (pairwise_error) अणु
			key_type = NL80211_KEYTYPE_PAIRWISE;
			key_id = -1;

			cfg80211_michael_mic_failure(usbdev->net,
							auth_req->bssid,
							key_type, key_id, शून्य,
							GFP_KERNEL);
		पूर्ण

		अगर (group_error) अणु
			key_type = NL80211_KEYTYPE_GROUP;
			key_id = -1;

			cfg80211_michael_mic_failure(usbdev->net,
							auth_req->bssid,
							key_type, key_id, शून्य,
							GFP_KERNEL);
		पूर्ण

		buflen -= le32_to_cpu(auth_req->length);
		buf += le32_to_cpu(auth_req->length);
	पूर्ण
पूर्ण

अटल व्योम rndis_wlan_pmkid_cand_list_indication(काष्ठा usbnet *usbdev,
				काष्ठा ndis_80211_status_indication *indication,
				पूर्णांक len)
अणु
	काष्ठा ndis_80211_pmkid_cand_list *cand_list;
	पूर्णांक list_len, expected_len, i;

	अगर (len < दुरत्व(काष्ठा ndis_80211_status_indication, u) +
				माप(काष्ठा ndis_80211_pmkid_cand_list)) अणु
		netdev_info(usbdev->net, "pmkid candidate list indication: too short message (%i)\n",
			    len);
		वापस;
	पूर्ण

	list_len = le32_to_cpu(indication->u.cand_list.num_candidates) *
			माप(काष्ठा ndis_80211_pmkid_candidate);
	expected_len = माप(काष्ठा ndis_80211_pmkid_cand_list) + list_len +
			दुरत्व(काष्ठा ndis_80211_status_indication, u);

	अगर (len < expected_len) अणु
		netdev_info(usbdev->net, "pmkid candidate list indication: list larger than buffer (%i < %i)\n",
			    len, expected_len);
		वापस;
	पूर्ण

	cand_list = &indication->u.cand_list;

	netdev_info(usbdev->net, "pmkid candidate list indication: version %i, candidates %i\n",
		    le32_to_cpu(cand_list->version),
		    le32_to_cpu(cand_list->num_candidates));

	अगर (le32_to_cpu(cand_list->version) != 1)
		वापस;

	क्रम (i = 0; i < le32_to_cpu(cand_list->num_candidates); i++) अणु
		काष्ठा ndis_80211_pmkid_candidate *cand =
						&cand_list->candidate_list[i];
		bool preauth = !!(cand->flags & NDIS_80211_PMKID_CAND_PREAUTH);

		netdev_dbg(usbdev->net, "cand[%i]: flags: 0x%08x, preauth: %d, bssid: %pM\n",
			   i, le32_to_cpu(cand->flags), preauth, cand->bssid);

		cfg80211_pmksa_candidate_notअगरy(usbdev->net, i, cand->bssid,
						preauth, GFP_ATOMIC);
	पूर्ण
पूर्ण

अटल व्योम rndis_wlan_media_specअगरic_indication(काष्ठा usbnet *usbdev,
			काष्ठा rndis_indicate *msg, पूर्णांक buflen)
अणु
	काष्ठा ndis_80211_status_indication *indication;
	अचिन्हित पूर्णांक len, offset;

	offset = दुरत्व(काष्ठा rndis_indicate, status) +
			le32_to_cpu(msg->offset);
	len = le32_to_cpu(msg->length);

	अगर (len < 8) अणु
		netdev_info(usbdev->net, "media specific indication, ignore too short message (%i < 8)\n",
			    len);
		वापस;
	पूर्ण

	अगर (len > buflen || offset > buflen || offset + len > buflen) अणु
		netdev_info(usbdev->net, "media specific indication, too large to fit to buffer (%i > %i)\n",
			    offset + len, buflen);
		वापस;
	पूर्ण

	indication = (व्योम *)((u8 *)msg + offset);

	चयन (le32_to_cpu(indication->status_type)) अणु
	हाल NDIS_80211_STATUSTYPE_RADIOSTATE:
		netdev_info(usbdev->net, "radio state indication: %i\n",
			    le32_to_cpu(indication->u.radio_status));
		वापस;

	हाल NDIS_80211_STATUSTYPE_MEDIASTREAMMODE:
		netdev_info(usbdev->net, "media stream mode indication: %i\n",
			    le32_to_cpu(indication->u.media_stream_mode));
		वापस;

	हाल NDIS_80211_STATUSTYPE_AUTHENTICATION:
		rndis_wlan_auth_indication(usbdev, indication, len);
		वापस;

	हाल NDIS_80211_STATUSTYPE_PMKID_CANDIDATELIST:
		rndis_wlan_pmkid_cand_list_indication(usbdev, indication, len);
		वापस;

	शेष:
		netdev_info(usbdev->net, "media specific indication: unknown status type 0x%08x\n",
			    le32_to_cpu(indication->status_type));
	पूर्ण
पूर्ण

अटल व्योम rndis_wlan_indication(काष्ठा usbnet *usbdev, व्योम *ind, पूर्णांक buflen)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	काष्ठा rndis_indicate *msg = ind;

	चयन (le32_to_cpu(msg->status)) अणु
	हाल RNDIS_STATUS_MEDIA_CONNECT:
		अगर (priv->current_command_oid == RNDIS_OID_802_11_ADD_KEY) अणु
			/* RNDIS_OID_802_11_ADD_KEY causes someबार extra
			 * "media connect" indications which confuses driver
			 * and userspace to think that device is
			 * roaming/reassociating when it isn't.
			 */
			netdev_dbg(usbdev->net, "ignored RNDIS_OID_802_11_ADD_KEY triggered 'media connect'\n");
			वापस;
		पूर्ण

		usbnet_छोड़ो_rx(usbdev);

		netdev_info(usbdev->net, "media connect\n");

		/* queue work to aव्योम recursive calls पूर्णांकo rndis_command */
		set_bit(WORK_LINK_UP, &priv->work_pending);
		queue_work(priv->workqueue, &priv->work);
		अवरोध;

	हाल RNDIS_STATUS_MEDIA_DISCONNECT:
		netdev_info(usbdev->net, "media disconnect\n");

		/* queue work to aव्योम recursive calls पूर्णांकo rndis_command */
		set_bit(WORK_LINK_DOWN, &priv->work_pending);
		queue_work(priv->workqueue, &priv->work);
		अवरोध;

	हाल RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION:
		rndis_wlan_media_specअगरic_indication(usbdev, msg, buflen);
		अवरोध;

	शेष:
		netdev_info(usbdev->net, "indication: 0x%08x\n",
			    le32_to_cpu(msg->status));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rndis_wlan_get_caps(काष्ठा usbnet *usbdev, काष्ठा wiphy *wiphy)
अणु
	काष्ठा अणु
		__le32	num_items;
		__le32	items[8];
	पूर्ण networks_supported;
	काष्ठा ndis_80211_capability caps;
	पूर्णांक len, retval, i, n;
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);

	/* determine supported modes */
	len = माप(networks_supported);
	retval = rndis_query_oid(usbdev,
				 RNDIS_OID_802_11_NETWORK_TYPES_SUPPORTED,
				 &networks_supported, &len);
	अगर (!retval) अणु
		n = le32_to_cpu(networks_supported.num_items);
		अगर (n > 8)
			n = 8;
		क्रम (i = 0; i < n; i++) अणु
			चयन (le32_to_cpu(networks_supported.items[i])) अणु
			हाल NDIS_80211_TYPE_FREQ_HOP:
			हाल NDIS_80211_TYPE_सूचीECT_SEQ:
				priv->caps |= CAP_MODE_80211B;
				अवरोध;
			हाल NDIS_80211_TYPE_OFDM_A:
				priv->caps |= CAP_MODE_80211A;
				अवरोध;
			हाल NDIS_80211_TYPE_OFDM_G:
				priv->caps |= CAP_MODE_80211G;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* get device 802.11 capabilities, number of PMKIDs */
	len = माप(caps);
	retval = rndis_query_oid(usbdev,
				 RNDIS_OID_802_11_CAPABILITY,
				 &caps, &len);
	अगर (!retval) अणु
		netdev_dbg(usbdev->net, "RNDIS_OID_802_11_CAPABILITY -> len %d, "
				"ver %d, pmkids %d, auth-encr-pairs %d\n",
				le32_to_cpu(caps.length),
				le32_to_cpu(caps.version),
				le32_to_cpu(caps.num_pmkids),
				le32_to_cpu(caps.num_auth_encr_pair));
		wiphy->max_num_pmkids = le32_to_cpu(caps.num_pmkids);
	पूर्ण अन्यथा
		wiphy->max_num_pmkids = 0;

	वापस retval;
पूर्ण

अटल व्योम rndis_करो_cqm(काष्ठा usbnet *usbdev, s32 rssi)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	क्रमागत nl80211_cqm_rssi_threshold_event event;
	पूर्णांक thold, hyst, last_event;

	अगर (priv->cqm_rssi_thold >= 0 || rssi >= 0)
		वापस;
	अगर (priv->infra_mode != NDIS_80211_INFRA_INFRA)
		वापस;

	last_event = priv->last_cqm_event_rssi;
	thold = priv->cqm_rssi_thold;
	hyst = priv->cqm_rssi_hyst;

	अगर (rssi < thold && (last_event == 0 || rssi < last_event - hyst))
		event = NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW;
	अन्यथा अगर (rssi > thold && (last_event == 0 || rssi > last_event + hyst))
		event = NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH;
	अन्यथा
		वापस;

	priv->last_cqm_event_rssi = rssi;
	cfg80211_cqm_rssi_notअगरy(usbdev->net, event, rssi, GFP_KERNEL);
पूर्ण

#घोषणा DEVICE_POLLER_JIFFIES (HZ)
अटल व्योम rndis_device_poller(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rndis_wlan_निजी *priv =
		container_of(work, काष्ठा rndis_wlan_निजी,
							dev_poller_work.work);
	काष्ठा usbnet *usbdev = priv->usbdev;
	__le32 rssi, पंचांगp;
	पूर्णांक len, ret, j;
	पूर्णांक update_jअगरfies = DEVICE_POLLER_JIFFIES;
	व्योम *buf;

	/* Only check/करो workaround when connected. Calling is_associated()
	 * also polls device with rndis_command() and catches क्रम media link
	 * indications.
	 */
	अगर (!is_associated(usbdev)) अणु
		/* Workaround bad scanning in BCM4320a devices with active
		 * background scanning when not associated.
		 */
		अगर (priv->device_type == RNDIS_BCM4320A && priv->radio_on &&
		    !priv->scan_request) अणु
			/* Get previous scan results */
			rndis_check_bssid_list(usbdev, शून्य, शून्य);

			/* Initiate new scan */
			rndis_start_bssid_list_scan(usbdev);
		पूर्ण

		जाओ end;
	पूर्ण

	len = माप(rssi);
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_RSSI,
			      &rssi, &len);
	अगर (ret == 0) अणु
		priv->last_qual = level_to_qual(le32_to_cpu(rssi));
		rndis_करो_cqm(usbdev, le32_to_cpu(rssi));
	पूर्ण

	netdev_dbg(usbdev->net, "dev-poller: RNDIS_OID_802_11_RSSI -> %d, rssi:%d, qual: %d\n",
		   ret, le32_to_cpu(rssi), level_to_qual(le32_to_cpu(rssi)));

	/* Workaround transfer stalls on poor quality links.
	 * TODO: find right way to fix these stalls (as stalls करो not happen
	 * with ndiswrapper/winकरोws driver). */
	अगर (priv->param_workaround_पूर्णांकerval > 0 && priv->last_qual <= 25) अणु
		/* Decrease stats worker पूर्णांकerval to catch stalls.
		 * faster. Faster than 400-500ms causes packet loss,
		 * Slower करोesn't catch stalls fast enough.
		 */
		j = msecs_to_jअगरfies(priv->param_workaround_पूर्णांकerval);
		अगर (j > DEVICE_POLLER_JIFFIES)
			j = DEVICE_POLLER_JIFFIES;
		अन्यथा अगर (j <= 0)
			j = 1;
		update_jअगरfies = j;

		/* Send scan OID. Use of both OIDs is required to get device
		 * working.
		 */
		पंचांगp = cpu_to_le32(1);
		rndis_set_oid(usbdev,
			      RNDIS_OID_802_11_BSSID_LIST_SCAN,
			      &पंचांगp, माप(पंचांगp));

		len = CONTROL_BUFFER_SIZE;
		buf = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!buf)
			जाओ end;

		rndis_query_oid(usbdev,
				RNDIS_OID_802_11_BSSID_LIST,
				buf, &len);
		kमुक्त(buf);
	पूर्ण

end:
	अगर (update_jअगरfies >= HZ)
		update_jअगरfies = round_jअगरfies_relative(update_jअगरfies);
	अन्यथा अणु
		j = round_jअगरfies_relative(update_jअगरfies);
		अगर (असल(j - update_jअगरfies) <= 10)
			update_jअगरfies = j;
	पूर्ण

	queue_delayed_work(priv->workqueue, &priv->dev_poller_work,
								update_jअगरfies);
पूर्ण

/*
 * driver/device initialization
 */
अटल व्योम rndis_copy_module_params(काष्ठा usbnet *usbdev, पूर्णांक device_type)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);

	priv->device_type = device_type;

	priv->param_country[0] = modparam_country[0];
	priv->param_country[1] = modparam_country[1];
	priv->param_country[2] = 0;
	priv->param_frameburst   = modparam_frameburst;
	priv->param_afterburner  = modparam_afterburner;
	priv->param_घातer_save   = modparam_घातer_save;
	priv->param_घातer_output = modparam_घातer_output;
	priv->param_roamtrigger  = modparam_roamtrigger;
	priv->param_roamdelta    = modparam_roamdelta;

	priv->param_country[0] = बड़े(priv->param_country[0]);
	priv->param_country[1] = बड़े(priv->param_country[1]);
	/* करोesn't support EU as country code, use FI instead */
	अगर (!म_भेद(priv->param_country, "EU"))
		म_नकल(priv->param_country, "FI");

	अगर (priv->param_घातer_save < 0)
		priv->param_घातer_save = 0;
	अन्यथा अगर (priv->param_घातer_save > 2)
		priv->param_घातer_save = 2;

	अगर (priv->param_घातer_output < 0)
		priv->param_घातer_output = 0;
	अन्यथा अगर (priv->param_घातer_output > 3)
		priv->param_घातer_output = 3;

	अगर (priv->param_roamtrigger < -80)
		priv->param_roamtrigger = -80;
	अन्यथा अगर (priv->param_roamtrigger > -60)
		priv->param_roamtrigger = -60;

	अगर (priv->param_roamdelta < 0)
		priv->param_roamdelta = 0;
	अन्यथा अगर (priv->param_roamdelta > 2)
		priv->param_roamdelta = 2;

	अगर (modparam_workaround_पूर्णांकerval < 0)
		priv->param_workaround_पूर्णांकerval = 500;
	अन्यथा
		priv->param_workaround_पूर्णांकerval = modparam_workaround_पूर्णांकerval;
पूर्ण

अटल पूर्णांक unknown_early_init(काष्ठा usbnet *usbdev)
अणु
	/* copy module parameters क्रम unknown so that iwconfig reports txघातer
	 * and workaround parameter is copied to निजी काष्ठाure correctly.
	 */
	rndis_copy_module_params(usbdev, RNDIS_UNKNOWN);

	/* This is unknown device, so करो not try set configuration parameters.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक bcm4320a_early_init(काष्ठा usbnet *usbdev)
अणु
	/* copy module parameters क्रम bcm4320a so that iwconfig reports txघातer
	 * and workaround parameter is copied to निजी काष्ठाure correctly.
	 */
	rndis_copy_module_params(usbdev, RNDIS_BCM4320A);

	/* bcm4320a करोesn't handle configuration parameters well. Try
	 * set any and you get partially zeroed mac and broken device.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक bcm4320b_early_init(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	अक्षर buf[8];

	rndis_copy_module_params(usbdev, RNDIS_BCM4320B);

	/* Early initialization settings, setting these won't have effect
	 * अगर called after generic_rndis_bind().
	 */

	rndis_set_config_parameter_str(usbdev, "Country", priv->param_country);
	rndis_set_config_parameter_str(usbdev, "FrameBursting",
					priv->param_frameburst ? "1" : "0");
	rndis_set_config_parameter_str(usbdev, "Afterburner",
					priv->param_afterburner ? "1" : "0");
	प्र_लिखो(buf, "%d", priv->param_घातer_save);
	rndis_set_config_parameter_str(usbdev, "PowerSaveMode", buf);
	प्र_लिखो(buf, "%d", priv->param_घातer_output);
	rndis_set_config_parameter_str(usbdev, "PwrOut", buf);
	प्र_लिखो(buf, "%d", priv->param_roamtrigger);
	rndis_set_config_parameter_str(usbdev, "RoamTrigger", buf);
	प्र_लिखो(buf, "%d", priv->param_roamdelta);
	rndis_set_config_parameter_str(usbdev, "RoamDelta", buf);

	वापस 0;
पूर्ण

/* same as rndis_netdev_ops but with local multicast handler */
अटल स्थिर काष्ठा net_device_ops rndis_wlan_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= rndis_wlan_set_multicast_list,
पूर्ण;

अटल पूर्णांक rndis_wlan_bind(काष्ठा usbnet *usbdev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा wiphy *wiphy;
	काष्ठा rndis_wlan_निजी *priv;
	पूर्णांक retval, len;
	__le32 पंचांगp;

	/* allocate wiphy and rndis निजी data
	 * NOTE: We only support a single भव पूर्णांकerface, so wiphy
	 * and wireless_dev are somewhat synonymous क्रम this device.
	 */
	wiphy = wiphy_new(&rndis_config_ops, माप(काष्ठा rndis_wlan_निजी));
	अगर (!wiphy)
		वापस -ENOMEM;

	priv = wiphy_priv(wiphy);
	usbdev->net->ieee80211_ptr = &priv->wdev;
	priv->wdev.wiphy = wiphy;
	priv->wdev.अगरtype = NL80211_IFTYPE_STATION;

	/* These have to be initialized beक्रमe calling generic_rndis_bind().
	 * Otherwise we'll be in big trouble in rndis_wlan_early_init().
	 */
	usbdev->driver_priv = priv;
	priv->usbdev = usbdev;

	mutex_init(&priv->command_lock);

	/* because rndis_command() sleeps we need to use workqueue */
	priv->workqueue = create_singlethपढ़ो_workqueue("rndis_wlan");
	अगर (!priv->workqueue) अणु
		wiphy_मुक्त(wiphy);
		वापस -ENOMEM;
	पूर्ण
	INIT_WORK(&priv->work, rndis_wlan_worker);
	INIT_DELAYED_WORK(&priv->dev_poller_work, rndis_device_poller);
	INIT_DELAYED_WORK(&priv->scan_work, rndis_get_scan_results);

	/* try bind rndis_host */
	retval = generic_rndis_bind(usbdev, पूर्णांकf, FLAG_RNDIS_PHYM_WIRELESS);
	अगर (retval < 0)
		जाओ fail;

	/* generic_rndis_bind set packet filter to multicast_all+
	 * promisc mode which करोesn't work well क्रम our devices (device
	 * picks up rssi to बंदst station instead of to access poपूर्णांक).
	 *
	 * rndis_host wants to aव्योम all OID as much as possible
	 * so करो promisc/multicast handling in rndis_wlan.
	 */
	usbdev->net->netdev_ops = &rndis_wlan_netdev_ops;

	पंचांगp = cpu_to_le32(RNDIS_PACKET_TYPE_सूचीECTED | RNDIS_PACKET_TYPE_BROADCAST);
	retval = rndis_set_oid(usbdev,
			       RNDIS_OID_GEN_CURRENT_PACKET_FILTER,
			       &पंचांगp, माप(पंचांगp));

	len = माप(पंचांगp);
	retval = rndis_query_oid(usbdev,
				 RNDIS_OID_802_3_MAXIMUM_LIST_SIZE,
				 &पंचांगp, &len);
	priv->multicast_size = le32_to_cpu(पंचांगp);
	अगर (retval < 0 || priv->multicast_size < 0)
		priv->multicast_size = 0;
	अगर (priv->multicast_size > 0)
		usbdev->net->flags |= IFF_MULTICAST;
	अन्यथा
		usbdev->net->flags &= ~IFF_MULTICAST;

	/* fill-out wiphy काष्ठाure and रेजिस्टर w/ cfg80211 */
	स_नकल(wiphy->perm_addr, usbdev->net->dev_addr, ETH_ALEN);
	wiphy->privid = rndis_wiphy_privid;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION)
					| BIT(NL80211_IFTYPE_ADHOC);
	wiphy->max_scan_ssids = 1;

	/* TODO: fill-out band/encr inक्रमmation based on priv->caps */
	rndis_wlan_get_caps(usbdev, wiphy);

	स_नकल(priv->channels, rndis_channels, माप(rndis_channels));
	स_नकल(priv->rates, rndis_rates, माप(rndis_rates));
	priv->band.channels = priv->channels;
	priv->band.n_channels = ARRAY_SIZE(rndis_channels);
	priv->band.bitrates = priv->rates;
	priv->band.n_bitrates = ARRAY_SIZE(rndis_rates);
	wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_UNSPEC;

	स_नकल(priv->cipher_suites, rndis_cipher_suites,
						माप(rndis_cipher_suites));
	wiphy->cipher_suites = priv->cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(rndis_cipher_suites);

	set_wiphy_dev(wiphy, &usbdev->udev->dev);

	अगर (wiphy_रेजिस्टर(wiphy)) अणु
		retval = -ENODEV;
		जाओ fail;
	पूर्ण

	set_शेष_iw_params(usbdev);

	priv->घातer_mode = -1;

	/* set शेष rts/frag */
	rndis_set_wiphy_params(wiphy,
			WIPHY_PARAM_FRAG_THRESHOLD | WIPHY_PARAM_RTS_THRESHOLD);

	/* turn radio off on init */
	priv->radio_on = false;
	disassociate(usbdev, false);
	netअगर_carrier_off(usbdev->net);

	वापस 0;

fail:
	cancel_delayed_work_sync(&priv->dev_poller_work);
	cancel_delayed_work_sync(&priv->scan_work);
	cancel_work_sync(&priv->work);
	flush_workqueue(priv->workqueue);
	destroy_workqueue(priv->workqueue);

	wiphy_मुक्त(wiphy);
	वापस retval;
पूर्ण

अटल व्योम rndis_wlan_unbind(काष्ठा usbnet *usbdev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);

	/* turn radio off */
	disassociate(usbdev, false);

	cancel_delayed_work_sync(&priv->dev_poller_work);
	cancel_delayed_work_sync(&priv->scan_work);
	cancel_work_sync(&priv->work);
	flush_workqueue(priv->workqueue);
	destroy_workqueue(priv->workqueue);

	rndis_unbind(usbdev, पूर्णांकf);

	wiphy_unरेजिस्टर(priv->wdev.wiphy);
	wiphy_मुक्त(priv->wdev.wiphy);
पूर्ण

अटल पूर्णांक rndis_wlan_reset(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	पूर्णांक retval;

	netdev_dbg(usbdev->net, "%s()\n", __func__);

	retval = rndis_reset(usbdev);
	अगर (retval)
		netdev_warn(usbdev->net, "rndis_reset failed: %d\n", retval);

	/* rndis_reset cleared multicast list, so restore here.
	   (set_multicast_list() also turns on current packet filter) */
	set_multicast_list(usbdev);

	queue_delayed_work(priv->workqueue, &priv->dev_poller_work,
		round_jअगरfies_relative(DEVICE_POLLER_JIFFIES));

	वापस deauthenticate(usbdev);
पूर्ण

अटल पूर्णांक rndis_wlan_stop(काष्ठा usbnet *usbdev)
अणु
	काष्ठा rndis_wlan_निजी *priv = get_rndis_wlan_priv(usbdev);
	पूर्णांक retval;
	__le32 filter;

	netdev_dbg(usbdev->net, "%s()\n", __func__);

	retval = disassociate(usbdev, false);

	priv->work_pending = 0;
	cancel_delayed_work_sync(&priv->dev_poller_work);
	cancel_delayed_work_sync(&priv->scan_work);
	cancel_work_sync(&priv->work);
	flush_workqueue(priv->workqueue);

	अगर (priv->scan_request) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		cfg80211_scan_करोne(priv->scan_request, &info);
		priv->scan_request = शून्य;
	पूर्ण

	/* Set current packet filter zero to block receiving data packets from
	   device. */
	filter = 0;
	rndis_set_oid(usbdev, RNDIS_OID_GEN_CURRENT_PACKET_FILTER, &filter,
								माप(filter));

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा driver_info	bcm4320b_info = अणु
	.description =	"Wireless RNDIS device, BCM4320b based",
	.flags =	FLAG_WLAN | FLAG_FRAMING_RN | FLAG_NO_SETINT |
				FLAG_AVOID_UNLINK_URBS,
	.bind =		rndis_wlan_bind,
	.unbind =	rndis_wlan_unbind,
	.status =	rndis_status,
	.rx_fixup =	rndis_rx_fixup,
	.tx_fixup =	rndis_tx_fixup,
	.reset =	rndis_wlan_reset,
	.stop =		rndis_wlan_stop,
	.early_init =	bcm4320b_early_init,
	.indication =	rndis_wlan_indication,
पूर्ण;

अटल स्थिर काष्ठा driver_info	bcm4320a_info = अणु
	.description =	"Wireless RNDIS device, BCM4320a based",
	.flags =	FLAG_WLAN | FLAG_FRAMING_RN | FLAG_NO_SETINT |
				FLAG_AVOID_UNLINK_URBS,
	.bind =		rndis_wlan_bind,
	.unbind =	rndis_wlan_unbind,
	.status =	rndis_status,
	.rx_fixup =	rndis_rx_fixup,
	.tx_fixup =	rndis_tx_fixup,
	.reset =	rndis_wlan_reset,
	.stop =		rndis_wlan_stop,
	.early_init =	bcm4320a_early_init,
	.indication =	rndis_wlan_indication,
पूर्ण;

अटल स्थिर काष्ठा driver_info rndis_wlan_info = अणु
	.description =	"Wireless RNDIS device",
	.flags =	FLAG_WLAN | FLAG_FRAMING_RN | FLAG_NO_SETINT |
				FLAG_AVOID_UNLINK_URBS,
	.bind =		rndis_wlan_bind,
	.unbind =	rndis_wlan_unbind,
	.status =	rndis_status,
	.rx_fixup =	rndis_rx_fixup,
	.tx_fixup =	rndis_tx_fixup,
	.reset =	rndis_wlan_reset,
	.stop =		rndis_wlan_stop,
	.early_init =	unknown_early_init,
	.indication =	rndis_wlan_indication,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा usb_device_id products [] = अणु
#घोषणा	RNDIS_MASTER_INTERFACE \
	.bInterfaceClass	= USB_CLASS_COMM, \
	.bInterfaceSubClass	= 2 /* ACM */, \
	.bInterfaceProtocol	= 0x0ff

/* INF driver क्रम these devices have DriverVer >= 4.xx.xx.xx and many custom
 * parameters available. Chipset marked as 'BCM4320SKFBG' in NDISwrapper-wiki.
 */
अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x0411,
	.idProduct		= 0x00bc,	/* Buffalo WLI-U2-KG125S */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x0baf,
	.idProduct		= 0x011b,	/* U.S. Robotics USR5421 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x050d,
	.idProduct		= 0x011b,	/* Belkin F5D7051 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x1799,	/* Belkin has two venकरोr ids */
	.idProduct		= 0x011b,	/* Belkin F5D7051 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x13b1,
	.idProduct		= 0x0014,	/* Linksys WUSB54GSv2 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x13b1,
	.idProduct		= 0x0026,	/* Linksys WUSB54GSC */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x0b05,
	.idProduct		= 0x1717,	/* Asus WL169gE */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x0a5c,
	.idProduct		= 0xd11b,	/* Eminent EM4045 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x1690,
	.idProduct		= 0x0715,	/* BT Voyager 1055 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320b_info,
पूर्ण,
/* These devices have DriverVer < 4.xx.xx.xx and करो not have any custom
 * parameters available, hardware probably contain older firmware version with
 * no way of updating. Chipset marked as 'BCM4320????' in NDISwrapper-wiki.
 */
अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x13b1,
	.idProduct		= 0x000e,	/* Linksys WUSB54GSv1 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320a_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x0baf,
	.idProduct		= 0x0111,	/* U.S. Robotics USR5420 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320a_info,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x0411,
	.idProduct		= 0x004b,	/* BUFFALO WLI-USB-G54 */
	RNDIS_MASTER_INTERFACE,
	.driver_info		= (अचिन्हित दीर्घ) &bcm4320a_info,
पूर्ण,
/* Generic Wireless RNDIS devices that we करोn't have exact
 * idVenकरोr/idProduct/chip yet.
 */
अणु
	/* RNDIS is MSFT's un-official variant of CDC ACM */
	USB_INTERFACE_INFO(USB_CLASS_COMM, 2 /* ACM */, 0x0ff),
	.driver_info = (अचिन्हित दीर्घ) &rndis_wlan_info,
पूर्ण, अणु
	/* "ActiveSync" is an unकरोcumented variant of RNDIS, used in WM5 */
	USB_INTERFACE_INFO(USB_CLASS_MISC, 1, 1),
	.driver_info = (अचिन्हित दीर्घ) &rndis_wlan_info,
पूर्ण,
	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver rndis_wlan_driver = अणु
	.name =		"rndis_wlan",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rndis_wlan_driver);

MODULE_AUTHOR("Bjorge Dijkstra");
MODULE_AUTHOR("Jussi Kivilinna");
MODULE_DESCRIPTION("Driver for RNDIS based USB Wireless adapters");
MODULE_LICENSE("GPL");

