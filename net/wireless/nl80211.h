<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Portions of this file
 * Copyright (C) 2018, 2020 Intel Corporation
 */
#अगर_अघोषित __NET_WIRELESS_NL80211_H
#घोषणा __NET_WIRELESS_NL80211_H

#समावेश "core.h"

पूर्णांक nl80211_init(व्योम);
व्योम nl80211_निकास(व्योम);

व्योम *nl80211hdr_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
		     पूर्णांक flags, u8 cmd);
bool nl80211_put_sta_rate(काष्ठा sk_buff *msg, काष्ठा rate_info *info,
			  पूर्णांक attr);

अटल अंतरभूत u64 wdev_id(काष्ठा wireless_dev *wdev)
अणु
	वापस (u64)wdev->identअगरier |
	       ((u64)wiphy_to_rdev(wdev->wiphy)->wiphy_idx << 32);
पूर्ण

पूर्णांक nl80211_prepare_wdev_dump(काष्ठा netlink_callback *cb,
			      काष्ठा cfg80211_रेजिस्टरed_device **rdev,
			      काष्ठा wireless_dev **wdev);

पूर्णांक nl80211_parse_chandef(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा genl_info *info,
			  काष्ठा cfg80211_chan_def *chandef);
पूर्णांक nl80211_parse_अक्रमom_mac(काष्ठा nlattr **attrs,
			     u8 *mac_addr, u8 *mac_addr_mask);

व्योम nl80211_notअगरy_wiphy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  क्रमागत nl80211_commands cmd);
व्योम nl80211_notअगरy_अगरace(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा wireless_dev *wdev,
			  क्रमागत nl80211_commands cmd);
व्योम nl80211_send_scan_start(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			     काष्ठा wireless_dev *wdev);
काष्ठा sk_buff *nl80211_build_scan_msg(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा wireless_dev *wdev, bool पातed);
व्योम nl80211_send_scan_msg(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा sk_buff *msg);
व्योम nl80211_send_sched_scan(काष्ठा cfg80211_sched_scan_request *req, u32 cmd);
व्योम nl80211_common_reg_change_event(क्रमागत nl80211_commands cmd_id,
				     काष्ठा regulatory_request *request);

अटल अंतरभूत व्योम
nl80211_send_reg_change_event(काष्ठा regulatory_request *request)
अणु
	nl80211_common_reg_change_event(NL80211_CMD_REG_CHANGE, request);
पूर्ण

अटल अंतरभूत व्योम
nl80211_send_wiphy_reg_change_event(काष्ठा regulatory_request *request)
अणु
	nl80211_common_reg_change_event(NL80211_CMD_WIPHY_REG_CHANGE, request);
पूर्ण

व्योम nl80211_send_rx_auth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *netdev,
			  स्थिर u8 *buf, माप_प्रकार len, gfp_t gfp);
व्योम nl80211_send_rx_assoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *netdev,
			   स्थिर u8 *buf, माप_प्रकार len, gfp_t gfp,
			   पूर्णांक uapsd_queues,
			   स्थिर u8 *req_ies, माप_प्रकार req_ies_len);
व्योम nl80211_send_deauth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *netdev,
			 स्थिर u8 *buf, माप_प्रकार len,
			 bool reconnect, gfp_t gfp);
व्योम nl80211_send_disassoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *netdev,
			   स्थिर u8 *buf, माप_प्रकार len,
			   bool reconnect, gfp_t gfp);
व्योम nl80211_send_auth_समयout(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev,
			       स्थिर u8 *addr, gfp_t gfp);
व्योम nl80211_send_assoc_समयout(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *netdev,
				स्थिर u8 *addr, gfp_t gfp);
व्योम nl80211_send_connect_result(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *netdev,
				 काष्ठा cfg80211_connect_resp_params *params,
				 gfp_t gfp);
व्योम nl80211_send_roamed(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *netdev,
			 काष्ठा cfg80211_roam_info *info, gfp_t gfp);
व्योम nl80211_send_port_authorized(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *netdev, स्थिर u8 *bssid);
व्योम nl80211_send_disconnected(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, u16 reason,
			       स्थिर u8 *ie, माप_प्रकार ie_len, bool from_ap);

व्योम
nl80211_michael_mic_failure(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा net_device *netdev, स्थिर u8 *addr,
			    क्रमागत nl80211_key_type key_type,
			    पूर्णांक key_id, स्थिर u8 *tsc, gfp_t gfp);

व्योम
nl80211_send_beacon_hपूर्णांक_event(काष्ठा wiphy *wiphy,
			       काष्ठा ieee80211_channel *channel_beक्रमe,
			       काष्ठा ieee80211_channel *channel_after);

व्योम nl80211_send_ibss_bssid(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			     काष्ठा net_device *netdev, स्थिर u8 *bssid,
			     gfp_t gfp);

पूर्णांक nl80211_send_mgmt(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा wireless_dev *wdev, u32 nlpid,
		      पूर्णांक freq, पूर्णांक sig_dbm,
		      स्थिर u8 *buf, माप_प्रकार len, u32 flags, gfp_t gfp);

व्योम
nl80211_radar_notअगरy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     स्थिर काष्ठा cfg80211_chan_def *chandef,
		     क्रमागत nl80211_radar_event event,
		     काष्ठा net_device *netdev, gfp_t gfp);

व्योम nl80211_send_ap_stopped(काष्ठा wireless_dev *wdev);

व्योम cfg80211_rdev_मुक्त_coalesce(काष्ठा cfg80211_रेजिस्टरed_device *rdev);

/* peer measurement */
पूर्णांक nl80211_pmsr_start(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक nl80211_pmsr_dump_results(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

#पूर्ण_अगर /* __NET_WIRELESS_NL80211_H */
