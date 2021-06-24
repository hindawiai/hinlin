<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित BRCMFMAC_CFG80211_H
#घोषणा BRCMFMAC_CFG80211_H

/* क्रम brcmu_d11inf */
#समावेश <brcmu_d11.h>

#समावेश "core.h"
#समावेश "fwil_types.h"
#समावेश "p2p.h"

#घोषणा BRCMF_SCAN_IE_LEN_MAX		2048

#घोषणा WL_NUM_SCAN_MAX			10
#घोषणा WL_TLV_INFO_MAX			1024
#घोषणा WL_BSS_INFO_MAX			2048
#घोषणा WL_ASSOC_INFO_MAX		512	/* assoc related fil max buf */
#घोषणा WL_EXTRA_BUF_MAX		2048
#घोषणा WL_ROAM_TRIGGER_LEVEL		-75
#घोषणा WL_ROAM_DELTA			20

/* WME Access Category Indices (ACIs) */
#घोषणा AC_BE			0	/* Best Efक्रमt */
#घोषणा AC_BK			1	/* Background */
#घोषणा AC_VI			2	/* Video */
#घोषणा AC_VO			3	/* Voice */
#घोषणा EDCF_AC_COUNT		4
#घोषणा MAX_8021D_PRIO		8

#घोषणा EDCF_ACI_MASK			0x60
#घोषणा EDCF_ACI_SHIFT			5
#घोषणा EDCF_ACM_MASK                  0x10
#घोषणा EDCF_ECWMIN_MASK		0x0f
#घोषणा EDCF_ECWMAX_SHIFT		4
#घोषणा EDCF_AIFSN_MASK			0x0f
#घोषणा EDCF_AIFSN_MAX			15
#घोषणा EDCF_ECWMAX_MASK		0xf0

/* Keep BRCMF_ESCAN_BUF_SIZE below 64K (65536). Allocing over 64K can be
 * problematic on some प्रणालीs and should be aव्योमed.
 */
#घोषणा BRCMF_ESCAN_BUF_SIZE		65000
#घोषणा BRCMF_ESCAN_TIMER_INTERVAL_MS	10000	/* E-Scan समयout */

#घोषणा WL_ESCAN_ACTION_START		1
#घोषणा WL_ESCAN_ACTION_CONTINUE	2
#घोषणा WL_ESCAN_ACTION_ABORT		3

#घोषणा WL_AUTH_SHARED_KEY		1	/* d11 shared authentication */
#घोषणा IE_MAX_LEN			512

/* IE TLV processing */
#घोषणा TLV_LEN_OFF			1	/* length offset */
#घोषणा TLV_HDR_LEN			2	/* header length */
#घोषणा TLV_BODY_OFF			2	/* body offset */
#घोषणा TLV_OUI_LEN			3	/* oui id length */

/* 802.11 Mgmt Packet flags */
#घोषणा BRCMF_VNDR_IE_BEACON_FLAG	0x1
#घोषणा BRCMF_VNDR_IE_PRBRSP_FLAG	0x2
#घोषणा BRCMF_VNDR_IE_ASSOCRSP_FLAG	0x4
#घोषणा BRCMF_VNDR_IE_AUTHRSP_FLAG	0x8
#घोषणा BRCMF_VNDR_IE_PRBREQ_FLAG	0x10
#घोषणा BRCMF_VNDR_IE_ASSOCREQ_FLAG	0x20
/* venकरोr IE in IW advertisement protocol ID field */
#घोषणा BRCMF_VNDR_IE_IWAPID_FLAG	0x40
/* allow custom IE id */
#घोषणा BRCMF_VNDR_IE_CUSTOM_FLAG	0x100

/* P2P Action Frames flags (spec ordered) */
#घोषणा BRCMF_VNDR_IE_GONREQ_FLAG     0x001000
#घोषणा BRCMF_VNDR_IE_GONRSP_FLAG     0x002000
#घोषणा BRCMF_VNDR_IE_GONCFM_FLAG     0x004000
#घोषणा BRCMF_VNDR_IE_INVREQ_FLAG     0x008000
#घोषणा BRCMF_VNDR_IE_INVRSP_FLAG     0x010000
#घोषणा BRCMF_VNDR_IE_DISREQ_FLAG     0x020000
#घोषणा BRCMF_VNDR_IE_DISRSP_FLAG     0x040000
#घोषणा BRCMF_VNDR_IE_PRDREQ_FLAG     0x080000
#घोषणा BRCMF_VNDR_IE_PRDRSP_FLAG     0x100000

#घोषणा BRCMF_VNDR_IE_P2PAF_SHIFT	12

#घोषणा BRCMF_MAX_DEFAULT_KEYS		6

/* beacon loss समयout शेषs */
#घोषणा BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_ON	2
#घोषणा BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_OFF	4

#घोषणा BRCMF_VIF_EVENT_TIMEOUT		msecs_to_jअगरfies(1500)

/**
 * क्रमागत brcmf_scan_status - scan engine status
 *
 * @BRCMF_SCAN_STATUS_BUSY: scanning in progress on करोngle.
 * @BRCMF_SCAN_STATUS_ABORT: scan being पातed on करोngle.
 * @BRCMF_SCAN_STATUS_SUPPRESS: scanning is suppressed in driver.
 */
क्रमागत brcmf_scan_status अणु
	BRCMF_SCAN_STATUS_BUSY,
	BRCMF_SCAN_STATUS_ABORT,
	BRCMF_SCAN_STATUS_SUPPRESS,
पूर्ण;

/* करोngle configuration */
काष्ठा brcmf_cfg80211_conf अणु
	u32 frag_threshold;
	u32 rts_threshold;
	u32 retry_लघु;
	u32 retry_दीर्घ;
पूर्ण;

/* security inक्रमmation with currently associated ap */
काष्ठा brcmf_cfg80211_security अणु
	u32 wpa_versions;
	u32 auth_type;
	u32 cipher_pairwise;
	u32 cipher_group;
पूर्ण;

क्रमागत brcmf_profile_fwsup अणु
	BRCMF_PROखाता_FWSUP_NONE,
	BRCMF_PROखाता_FWSUP_PSK,
	BRCMF_PROखाता_FWSUP_1X,
	BRCMF_PROखाता_FWSUP_SAE
पूर्ण;

/**
 * क्रमागत brcmf_profile_fwauth - firmware authenticator profile
 *
 * @BRCMF_PROखाता_FWAUTH_NONE: no firmware authenticator
 * @BRCMF_PROखाता_FWAUTH_PSK: authenticator क्रम WPA/WPA2-PSK
 * @BRCMF_PROखाता_FWAUTH_SAE: authenticator क्रम SAE
 */
क्रमागत brcmf_profile_fwauth अणु
	BRCMF_PROखाता_FWAUTH_NONE,
	BRCMF_PROखाता_FWAUTH_PSK,
	BRCMF_PROखाता_FWAUTH_SAE
पूर्ण;

/**
 * काष्ठा brcmf_cfg80211_profile - profile inक्रमmation.
 *
 * @bssid: bssid of joined/joining ibss.
 * @sec: security inक्रमmation.
 * @key: key inक्रमmation
 */
काष्ठा brcmf_cfg80211_profile अणु
	u8 bssid[ETH_ALEN];
	काष्ठा brcmf_cfg80211_security sec;
	काष्ठा brcmf_wsec_key key[BRCMF_MAX_DEFAULT_KEYS];
	क्रमागत brcmf_profile_fwsup use_fwsup;
	u16 use_fwauth;
	bool is_ft;
पूर्ण;

/**
 * क्रमागत brcmf_vअगर_status - bit indices क्रम vअगर status.
 *
 * @BRCMF_VIF_STATUS_READY: पढ़ोy क्रम operation.
 * @BRCMF_VIF_STATUS_CONNECTING: connect/join in progress.
 * @BRCMF_VIF_STATUS_CONNECTED: connected/joined successfully.
 * @BRCMF_VIF_STATUS_DISCONNECTING: disconnect/disable in progress.
 * @BRCMF_VIF_STATUS_AP_CREATED: AP operation started.
 * @BRCMF_VIF_STATUS_EAP_SUCCUSS: EAPOL handshake successful.
 * @BRCMF_VIF_STATUS_ASSOC_SUCCESS: successful SET_SSID received.
 */
क्रमागत brcmf_vअगर_status अणु
	BRCMF_VIF_STATUS_READY,
	BRCMF_VIF_STATUS_CONNECTING,
	BRCMF_VIF_STATUS_CONNECTED,
	BRCMF_VIF_STATUS_DISCONNECTING,
	BRCMF_VIF_STATUS_AP_CREATED,
	BRCMF_VIF_STATUS_EAP_SUCCESS,
	BRCMF_VIF_STATUS_ASSOC_SUCCESS,
पूर्ण;

/**
 * काष्ठा vअगर_saved_ie - holds saved IEs क्रम a भव पूर्णांकerface.
 *
 * @probe_req_ie: IE info क्रम probe request.
 * @probe_res_ie: IE info क्रम probe response.
 * @beacon_ie: IE info क्रम beacon frame.
 * @assoc_res_ie: IE info क्रम association response frame.
 * @probe_req_ie_len: IE info length क्रम probe request.
 * @probe_res_ie_len: IE info length क्रम probe response.
 * @beacon_ie_len: IE info length क्रम beacon frame.
 * @assoc_res_ie_len: IE info length क्रम association response frame.
 */
काष्ठा vअगर_saved_ie अणु
	u8  probe_req_ie[IE_MAX_LEN];
	u8  probe_res_ie[IE_MAX_LEN];
	u8  beacon_ie[IE_MAX_LEN];
	u8  assoc_req_ie[IE_MAX_LEN];
	u8  assoc_res_ie[IE_MAX_LEN];
	u32 probe_req_ie_len;
	u32 probe_res_ie_len;
	u32 beacon_ie_len;
	u32 assoc_req_ie_len;
	u32 assoc_res_ie_len;
पूर्ण;

/**
 * काष्ठा brcmf_cfg80211_vअगर - भव पूर्णांकerface specअगरic inक्रमmation.
 *
 * @अगरp: lower layer पूर्णांकerface poपूर्णांकer
 * @wdev: wireless device.
 * @profile: profile inक्रमmation.
 * @sme_state: SME state using क्रमागत brcmf_vअगर_status bits.
 * @list: linked list.
 * @mgmt_rx_reg: रेजिस्टरed rx mgmt frame types.
 * @mbss: Multiple BSS type, set अगर not first AP (not relevant क्रम P2P).
 * @cqm_rssi_low: Lower RSSI limit क्रम CQM monitoring
 * @cqm_rssi_high: Upper RSSI limit क्रम CQM monitoring
 * @cqm_rssi_last: Last RSSI पढ़ोing क्रम CQM monitoring
 */
काष्ठा brcmf_cfg80211_vअगर अणु
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा wireless_dev wdev;
	काष्ठा brcmf_cfg80211_profile profile;
	अचिन्हित दीर्घ sme_state;
	काष्ठा vअगर_saved_ie saved_ie;
	काष्ठा list_head list;
	u16 mgmt_rx_reg;
	bool mbss;
	पूर्णांक is_11d;
	s32 cqm_rssi_low;
	s32 cqm_rssi_high;
	s32 cqm_rssi_last;
पूर्ण;

/* association inक्रमm */
काष्ठा brcmf_cfg80211_connect_info अणु
	u8 *req_ie;
	s32 req_ie_len;
	u8 *resp_ie;
	s32 resp_ie_len;
पूर्ण;

/* assoc ie length */
काष्ठा brcmf_cfg80211_assoc_ielen_le अणु
	__le32 req_len;
	__le32 resp_len;
पूर्ण;

काष्ठा brcmf_cfg80211_edcf_acparam अणु
	u8 ACI;
	u8 ECW;
	u16 TXOP;        /* stored in network order (ls octet first) */
पूर्ण;

/* करोngle escan state */
क्रमागत wl_escan_state अणु
	WL_ESCAN_STATE_IDLE,
	WL_ESCAN_STATE_SCANNING
पूर्ण;

काष्ठा escan_info अणु
	u32 escan_state;
	u8 *escan_buf;
	काष्ठा wiphy *wiphy;
	काष्ठा brcmf_अगर *अगरp;
	s32 (*run)(काष्ठा brcmf_cfg80211_info *cfg, काष्ठा brcmf_अगर *अगरp,
		   काष्ठा cfg80211_scan_request *request);
पूर्ण;

/**
 * काष्ठा brcmf_cfg80211_vअगर_event - भव पूर्णांकerface event inक्रमmation.
 *
 * @vअगर_wq: रुकोqueue aरुकोing पूर्णांकerface event from firmware.
 * @vअगर_event_lock: protects other members in this काष्ठाure.
 * @vअगर_complete: completion क्रम net attach.
 * @action: either add, change, or delete.
 * @vअगर: भव पूर्णांकerface object related to the event.
 */
काष्ठा brcmf_cfg80211_vअगर_event अणु
	रुको_queue_head_t vअगर_wq;
	spinlock_t vअगर_event_lock;
	u8 action;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
पूर्ण;

/**
 * काष्ठा brcmf_cfg80211_wowl - wowl related inक्रमmation.
 *
 * @active: set on suspend, cleared on resume.
 * @pre_pmmode: firmware PM mode at entering suspend.
 * @nd: net dectect data.
 * @nd_info: helper काष्ठा to pass to cfg80211.
 * @nd_data_रुको: रुको queue to sync net detect data.
 * @nd_data_completed: completion क्रम net detect data.
 * @nd_enabled: net detect enabled.
 */
काष्ठा brcmf_cfg80211_wowl अणु
	bool active;
	u32 pre_pmmode;
	काष्ठा cfg80211_wowlan_nd_match *nd;
	काष्ठा cfg80211_wowlan_nd_info *nd_info;
	रुको_queue_head_t nd_data_रुको;
	bool nd_data_completed;
	bool nd_enabled;
पूर्ण;

/**
 * काष्ठा brcmf_cfg80211_info - करोngle निजी data of cfg80211 पूर्णांकerface
 *
 * @wiphy: wiphy object क्रम cfg80211 पूर्णांकerface.
 * @ops: poपूर्णांकer to copy of ops as रेजिस्टरed with wiphy object.
 * @conf: करोngle configuration.
 * @p2p: peer-to-peer specअगरic inक्रमmation.
 * @btcoex: Bluetooth coexistence inक्रमmation.
 * @scan_request: cfg80211 scan request object.
 * @usr_sync: मुख्यly क्रम करोngle up/करोwn synchronization.
 * @bss_list: bss_list holding scanned ap inक्रमmation.
 * @bss_info: bss inक्रमmation क्रम cfg80211 layer.
 * @conn_info: association info.
 * @pmk_list: wpa2 pmk list.
 * @scan_status: scan activity on the करोngle.
 * @pub: common driver inक्रमmation.
 * @channel: current channel.
 * @पूर्णांक_escan_map: bucket map क्रम which पूर्णांकernal e-scan is करोne.
 * @ibss_starter: indicates this sta is ibss starter.
 * @pwr_save: indicate whether करोngle to support घातer save mode.
 * @करोngle_up: indicate whether करोngle up or not.
 * @roam_on: on/off चयन क्रम करोngle self-roaming.
 * @scan_tried: indicates अगर first scan attempted.
 * @dcmd_buf: dcmd buffer.
 * @extra_buf: मुख्यly to grab assoc inक्रमmation.
 * @debugfsdir: debugfs folder क्रम this device.
 * @escan_info: escan inक्रमmation.
 * @escan_समयout: Timer क्रम catch scan समयout.
 * @escan_समयout_work: scan समयout worker.
 * @vअगर_list: linked list of vअगर instances.
 * @vअगर_cnt: number of vअगर instances.
 * @vअगर_event: vअगर event संकेतling.
 * @wowl: wowl related inक्रमmation.
 * @pno: inक्रमmation of pno module.
 */
काष्ठा brcmf_cfg80211_info अणु
	काष्ठा wiphy *wiphy;
	काष्ठा brcmf_cfg80211_conf *conf;
	काष्ठा brcmf_p2p_info p2p;
	काष्ठा brcmf_btcoex_info *btcoex;
	काष्ठा cfg80211_scan_request *scan_request;
	काष्ठा mutex usr_sync;
	काष्ठा wl_cfg80211_bss_info *bss_info;
	काष्ठा brcmf_cfg80211_connect_info conn_info;
	काष्ठा brcmf_pmk_list_le pmk_list;
	अचिन्हित दीर्घ scan_status;
	काष्ठा brcmf_pub *pub;
	u32 channel;
	u32 पूर्णांक_escan_map;
	bool ibss_starter;
	bool pwr_save;
	bool करोngle_up;
	bool scan_tried;
	u8 *dcmd_buf;
	u8 *extra_buf;
	काष्ठा dentry *debugfsdir;
	काष्ठा escan_info escan_info;
	काष्ठा समयr_list escan_समयout;
	काष्ठा work_काष्ठा escan_समयout_work;
	काष्ठा list_head vअगर_list;
	काष्ठा brcmf_cfg80211_vअगर_event vअगर_event;
	काष्ठा completion vअगर_disabled;
	काष्ठा brcmu_d11inf d11inf;
	काष्ठा brcmf_assoclist_le assoclist;
	काष्ठा brcmf_cfg80211_wowl wowl;
	काष्ठा brcmf_pno_info *pno;
	u8 ac_priority[MAX_8021D_PRIO];
पूर्ण;

/**
 * काष्ठा brcmf_tlv - tag_ID/length/value_buffer tuple.
 *
 * @id: tag identअगरier.
 * @len: number of bytes in value buffer.
 * @data: value buffer.
 */
काष्ठा brcmf_tlv अणु
	u8 id;
	u8 len;
	u8 data[1];
पूर्ण;

अटल अंतरभूत काष्ठा wiphy *cfg_to_wiphy(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	वापस cfg->wiphy;
पूर्ण

अटल अंतरभूत काष्ठा brcmf_cfg80211_info *wiphy_to_cfg(काष्ठा wiphy *w)
अणु
	काष्ठा brcmf_pub *drvr = wiphy_priv(w);
	वापस drvr->config;
पूर्ण

अटल अंतरभूत काष्ठा brcmf_cfg80211_info *wdev_to_cfg(काष्ठा wireless_dev *wd)
अणु
	वापस wiphy_to_cfg(wd->wiphy);
पूर्ण

अटल अंतरभूत काष्ठा brcmf_cfg80211_vअगर *wdev_to_vअगर(काष्ठा wireless_dev *wdev)
अणु
	वापस container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);
पूर्ण

अटल अंतरभूत
काष्ठा net_device *cfg_to_ndev(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	वापस brcmf_get_अगरp(cfg->pub, 0)->ndev;
पूर्ण

अटल अंतरभूत काष्ठा brcmf_cfg80211_info *ndev_to_cfg(काष्ठा net_device *ndev)
अणु
	वापस wdev_to_cfg(ndev->ieee80211_ptr);
पूर्ण

अटल अंतरभूत काष्ठा brcmf_cfg80211_profile *ndev_to_prof(काष्ठा net_device *nd)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(nd);
	वापस &अगरp->vअगर->profile;
पूर्ण

अटल अंतरभूत काष्ठा brcmf_cfg80211_vअगर *ndev_to_vअगर(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	वापस अगरp->vअगर;
पूर्ण

अटल अंतरभूत काष्ठा
brcmf_cfg80211_connect_info *cfg_to_conn(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	वापस &cfg->conn_info;
पूर्ण

काष्ठा brcmf_cfg80211_info *brcmf_cfg80211_attach(काष्ठा brcmf_pub *drvr,
						  काष्ठा cfg80211_ops *ops,
						  bool p2pdev_क्रमced);
व्योम brcmf_cfg80211_detach(काष्ठा brcmf_cfg80211_info *cfg);
s32 brcmf_cfg80211_up(काष्ठा net_device *ndev);
s32 brcmf_cfg80211_करोwn(काष्ठा net_device *ndev);
काष्ठा cfg80211_ops *brcmf_cfg80211_get_ops(काष्ठा brcmf_mp_device *settings);
क्रमागत nl80211_अगरtype brcmf_cfg80211_get_अगरtype(काष्ठा brcmf_अगर *अगरp);

काष्ठा brcmf_cfg80211_vअगर *brcmf_alloc_vअगर(काष्ठा brcmf_cfg80211_info *cfg,
					   क्रमागत nl80211_अगरtype type);
व्योम brcmf_मुक्त_vअगर(काष्ठा brcmf_cfg80211_vअगर *vअगर);

s32 brcmf_vअगर_set_mgmt_ie(काष्ठा brcmf_cfg80211_vअगर *vअगर, s32 pktflag,
			  स्थिर u8 *vndr_ie_buf, u32 vndr_ie_len);
s32 brcmf_vअगर_clear_mgmt_ies(काष्ठा brcmf_cfg80211_vअगर *vअगर);
u16 channel_to_chanspec(काष्ठा brcmu_d11inf *d11inf,
			काष्ठा ieee80211_channel *ch);
bool brcmf_get_vअगर_state_any(काष्ठा brcmf_cfg80211_info *cfg,
			     अचिन्हित दीर्घ state);
व्योम brcmf_cfg80211_arm_vअगर_event(काष्ठा brcmf_cfg80211_info *cfg,
				  काष्ठा brcmf_cfg80211_vअगर *vअगर);
bool brcmf_cfg80211_vअगर_event_armed(काष्ठा brcmf_cfg80211_info *cfg);
पूर्णांक brcmf_cfg80211_रुको_vअगर_event(काष्ठा brcmf_cfg80211_info *cfg,
				  u8 action, uदीर्घ समयout);
s32 brcmf_notअगरy_escan_complete(काष्ठा brcmf_cfg80211_info *cfg,
				काष्ठा brcmf_अगर *अगरp, bool पातed,
				bool fw_पात);
व्योम brcmf_set_mpc(काष्ठा brcmf_अगर *ndev, पूर्णांक mpc);
व्योम brcmf_पात_scanning(काष्ठा brcmf_cfg80211_info *cfg);
व्योम brcmf_cfg80211_मुक्त_netdev(काष्ठा net_device *ndev);

#पूर्ण_अगर /* BRCMFMAC_CFG80211_H */
