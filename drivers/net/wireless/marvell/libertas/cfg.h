<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LBS_CFG80211_H__
#घोषणा __LBS_CFG80211_H__

काष्ठा device;
काष्ठा lbs_निजी;
काष्ठा regulatory_request;
काष्ठा wiphy;

काष्ठा wireless_dev *lbs_cfg_alloc(काष्ठा device *dev);
पूर्णांक lbs_cfg_रेजिस्टर(काष्ठा lbs_निजी *priv);
व्योम lbs_cfg_मुक्त(काष्ठा lbs_निजी *priv);

व्योम lbs_send_disconnect_notअगरication(काष्ठा lbs_निजी *priv,
				      bool locally_generated);
व्योम lbs_send_mic_failureevent(काष्ठा lbs_निजी *priv, u32 event);

व्योम lbs_scan_करोne(काष्ठा lbs_निजी *priv);
व्योम lbs_scan_deinit(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_disconnect(काष्ठा lbs_निजी *priv, u16 reason);

#पूर्ण_अगर
