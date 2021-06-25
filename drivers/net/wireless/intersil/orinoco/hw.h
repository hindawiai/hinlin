<शैली गुरु>
/* Encapsulate basic setting changes on Hermes hardware
 *
 * See copyright notice in मुख्य.c
 */
#अगर_अघोषित _ORINOCO_HW_H_
#घोषणा _ORINOCO_HW_H_

#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <net/cfg80211.h>

/* Hardware BAPs */
#घोषणा USER_BAP 0
#घोषणा IRQ_BAP  1

/* WEP key sizes */
#घोषणा SMALL_KEY_SIZE 5
#घोषणा LARGE_KEY_SIZE 13

/* Number of supported channels */
#घोषणा NUM_CHANNELS 14

/* Forward declarations */
काष्ठा orinoco_निजी;

पूर्णांक determine_fw_capabilities(काष्ठा orinoco_निजी *priv, अक्षर *fw_name,
			      माप_प्रकार fw_name_len, u32 *hw_ver);
पूर्णांक orinoco_hw_पढ़ो_card_settings(काष्ठा orinoco_निजी *priv, u8 *dev_addr);
पूर्णांक orinoco_hw_allocate_fid(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_get_bitratemode(पूर्णांक bitrate, पूर्णांक स्वतःmatic);
व्योम orinoco_get_ratemode_cfg(पूर्णांक ratemode, पूर्णांक *bitrate, पूर्णांक *स्वतःmatic);

पूर्णांक orinoco_hw_program_rids(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_hw_get_tkip_iv(काष्ठा orinoco_निजी *priv, पूर्णांक key, u8 *tsc);
पूर्णांक __orinoco_hw_set_bitrate(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_hw_get_act_bitrate(काष्ठा orinoco_निजी *priv, पूर्णांक *bitrate);
पूर्णांक __orinoco_hw_set_wap(काष्ठा orinoco_निजी *priv);
पूर्णांक __orinoco_hw_setup_wepkeys(काष्ठा orinoco_निजी *priv);
पूर्णांक __orinoco_hw_setup_enc(काष्ठा orinoco_निजी *priv);
पूर्णांक __orinoco_hw_set_tkip_key(काष्ठा orinoco_निजी *priv, पूर्णांक key_idx,
			      पूर्णांक set_tx, स्थिर u8 *key, स्थिर u8 *rsc,
			      माप_प्रकार rsc_len, स्थिर u8 *tsc, माप_प्रकार tsc_len);
पूर्णांक orinoco_clear_tkip_key(काष्ठा orinoco_निजी *priv, पूर्णांक key_idx);
पूर्णांक __orinoco_hw_set_multicast_list(काष्ठा orinoco_निजी *priv,
				    काष्ठा net_device *dev,
				    पूर्णांक mc_count, पूर्णांक promisc);
पूर्णांक orinoco_hw_get_essid(काष्ठा orinoco_निजी *priv, पूर्णांक *active,
			 अक्षर buf[IW_ESSID_MAX_SIZE + 1]);
पूर्णांक orinoco_hw_get_freq(काष्ठा orinoco_निजी *priv);
पूर्णांक orinoco_hw_get_bitratelist(काष्ठा orinoco_निजी *priv,
			       पूर्णांक *numrates, s32 *rates, पूर्णांक max);
पूर्णांक orinoco_hw_trigger_scan(काष्ठा orinoco_निजी *priv,
			    स्थिर काष्ठा cfg80211_ssid *ssid);
पूर्णांक orinoco_hw_disassociate(काष्ठा orinoco_निजी *priv,
			    u8 *addr, u16 reason_code);
पूर्णांक orinoco_hw_get_current_bssid(काष्ठा orinoco_निजी *priv,
				 u8 *addr);

#पूर्ण_अगर /* _ORINOCO_HW_H_ */
