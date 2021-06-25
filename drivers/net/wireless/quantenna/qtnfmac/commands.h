<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित QLINK_COMMANDS_H_
#घोषणा QLINK_COMMANDS_H_

#समावेश <linux/nl80211.h>

#समावेश "core.h"
#समावेश "bus.h"

पूर्णांक qtnf_cmd_send_init_fw(काष्ठा qtnf_bus *bus);
व्योम qtnf_cmd_send_deinit_fw(काष्ठा qtnf_bus *bus);
पूर्णांक qtnf_cmd_get_hw_info(काष्ठा qtnf_bus *bus);
पूर्णांक qtnf_cmd_get_mac_info(काष्ठा qtnf_wmac *mac);
पूर्णांक qtnf_cmd_send_add_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर, क्रमागत nl80211_अगरtype अगरtype,
			   पूर्णांक use4addr, u8 *mac_addr);
पूर्णांक qtnf_cmd_send_change_पूर्णांकf_type(काष्ठा qtnf_vअगर *vअगर,
				   क्रमागत nl80211_अगरtype अगरtype,
				   पूर्णांक use4addr,
				   u8 *mac_addr);
पूर्णांक qtnf_cmd_send_del_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर);
पूर्णांक qtnf_cmd_band_info_get(काष्ठा qtnf_wmac *mac,
			   काष्ठा ieee80211_supported_band *band);
पूर्णांक qtnf_cmd_send_regulatory_config(काष्ठा qtnf_wmac *mac, स्थिर अक्षर *alpha2);
पूर्णांक qtnf_cmd_send_start_ap(काष्ठा qtnf_vअगर *vअगर,
			   स्थिर काष्ठा cfg80211_ap_settings *s);
पूर्णांक qtnf_cmd_send_stop_ap(काष्ठा qtnf_vअगर *vअगर);
पूर्णांक qtnf_cmd_send_रेजिस्टर_mgmt(काष्ठा qtnf_vअगर *vअगर, u16 frame_type, bool reg);
पूर्णांक qtnf_cmd_send_frame(काष्ठा qtnf_vअगर *vअगर, u32 cookie, u16 flags,
			u16 freq, स्थिर u8 *buf, माप_प्रकार len);
पूर्णांक qtnf_cmd_send_mgmt_set_appie(काष्ठा qtnf_vअगर *vअगर, u8 frame_type,
				 स्थिर u8 *buf, माप_प्रकार len);
पूर्णांक qtnf_cmd_get_sta_info(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *sta_mac,
			  काष्ठा station_info *sinfo);
पूर्णांक qtnf_cmd_send_phy_params(काष्ठा qtnf_wmac *mac, u16 cmd_action,
			     व्योम *data_buf);
पूर्णांक qtnf_cmd_send_add_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index, bool pairwise,
			  स्थिर u8 *mac_addr, काष्ठा key_params *params);
पूर्णांक qtnf_cmd_send_del_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index, bool pairwise,
			  स्थिर u8 *mac_addr);
पूर्णांक qtnf_cmd_send_set_शेष_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index,
				  bool unicast, bool multicast);
पूर्णांक qtnf_cmd_send_set_शेष_mgmt_key(काष्ठा qtnf_vअगर *vअगर, u8 key_index);
पूर्णांक qtnf_cmd_send_add_sta(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *mac,
			  काष्ठा station_parameters *params);
पूर्णांक qtnf_cmd_send_change_sta(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *mac,
			     काष्ठा station_parameters *params);
पूर्णांक qtnf_cmd_send_del_sta(काष्ठा qtnf_vअगर *vअगर,
			  काष्ठा station_del_parameters *params);
पूर्णांक qtnf_cmd_send_scan(काष्ठा qtnf_wmac *mac);
पूर्णांक qtnf_cmd_send_connect(काष्ठा qtnf_vअगर *vअगर,
			  काष्ठा cfg80211_connect_params *sme);
पूर्णांक qtnf_cmd_send_बाह्यal_auth(काष्ठा qtnf_vअगर *vअगर,
				काष्ठा cfg80211_बाह्यal_auth_params *auth);
पूर्णांक qtnf_cmd_send_disconnect(काष्ठा qtnf_vअगर *vअगर,
			     u16 reason_code);
पूर्णांक qtnf_cmd_send_upकरोwn_पूर्णांकf(काष्ठा qtnf_vअगर *vअगर,
			      bool up);
पूर्णांक qtnf_cmd_reg_notअगरy(काष्ठा qtnf_wmac *mac, काष्ठा regulatory_request *req,
			bool slave_radar, bool dfs_offload);
पूर्णांक qtnf_cmd_get_chan_stats(काष्ठा qtnf_wmac *mac, u32 chan_freq,
			    काष्ठा survey_info *survey);
पूर्णांक qtnf_cmd_send_chan_चयन(काष्ठा qtnf_vअगर *vअगर,
			      काष्ठा cfg80211_csa_settings *params);
पूर्णांक qtnf_cmd_get_channel(काष्ठा qtnf_vअगर *vअगर, काष्ठा cfg80211_chan_def *chdef);
पूर्णांक qtnf_cmd_start_cac(स्थिर काष्ठा qtnf_vअगर *vअगर,
		       स्थिर काष्ठा cfg80211_chan_def *chdef,
		       u32 cac_समय_ms);
पूर्णांक qtnf_cmd_set_mac_acl(स्थिर काष्ठा qtnf_vअगर *vअगर,
			 स्थिर काष्ठा cfg80211_acl_data *params);
पूर्णांक qtnf_cmd_send_pm_set(स्थिर काष्ठा qtnf_vअगर *vअगर, u8 pm_mode, पूर्णांक समयout);
पूर्णांक qtnf_cmd_get_tx_घातer(स्थिर काष्ठा qtnf_vअगर *vअगर, पूर्णांक *dbm);
पूर्णांक qtnf_cmd_set_tx_घातer(स्थिर काष्ठा qtnf_vअगर *vअगर,
			  क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm);
पूर्णांक qtnf_cmd_send_wowlan_set(स्थिर काष्ठा qtnf_vअगर *vअगर,
			     स्थिर काष्ठा cfg80211_wowlan *wowl);
पूर्णांक qtnf_cmd_netdev_changeupper(स्थिर काष्ठा qtnf_vअगर *vअगर, पूर्णांक br_करोमुख्य);
पूर्णांक qtnf_cmd_send_update_owe(काष्ठा qtnf_vअगर *vअगर,
			     काष्ठा cfg80211_update_owe_info *owe);

#पूर्ण_अगर /* QLINK_COMMANDS_H_ */
