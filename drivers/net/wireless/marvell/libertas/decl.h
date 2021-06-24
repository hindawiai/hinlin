<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 *  This file contains declaration referring to
 *  functions defined in other source files
 */

#अगर_अघोषित _LBS_DECL_H_
#घोषणा _LBS_DECL_H_

#समावेश <linux/netdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/nl80211.h>

/* Should be terminated by a शून्य entry */
काष्ठा lbs_fw_table अणु
	पूर्णांक model;
	स्थिर अक्षर *helper;
	स्थिर अक्षर *fwname;
पूर्ण;

काष्ठा lbs_निजी;
प्रकार व्योम (*lbs_fw_cb)(काष्ठा lbs_निजी *priv, पूर्णांक ret,
		स्थिर काष्ठा firmware *helper, स्थिर काष्ठा firmware *मुख्यfw);

काष्ठा sk_buff;
काष्ठा net_device;
काष्ठा cmd_ds_command;


/* ethtool.c */
बाह्य स्थिर काष्ठा ethtool_ops lbs_ethtool_ops;


/* tx.c */
व्योम lbs_send_tx_feedback(काष्ठा lbs_निजी *priv, u32 try_count);
netdev_tx_t lbs_hard_start_xmit(काष्ठा sk_buff *skb,
				काष्ठा net_device *dev);

/* rx.c */
पूर्णांक lbs_process_rxed_packet(काष्ठा lbs_निजी *priv, काष्ठा sk_buff *);


/* मुख्य.c */
काष्ठा lbs_निजी *lbs_add_card(व्योम *card, काष्ठा device *dmdev);
व्योम lbs_हटाओ_card(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_start_card(काष्ठा lbs_निजी *priv);
व्योम lbs_stop_card(काष्ठा lbs_निजी *priv);
व्योम lbs_host_to_card_करोne(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_start_अगरace(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_stop_अगरace(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_set_अगरace_type(काष्ठा lbs_निजी *priv, क्रमागत nl80211_अगरtype type);

पूर्णांक lbs_rtap_supported(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_set_mac_address(काष्ठा net_device *dev, व्योम *addr);
व्योम lbs_set_multicast_list(काष्ठा net_device *dev);
व्योम lbs_update_mcast(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_suspend(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_resume(काष्ठा lbs_निजी *priv);

व्योम lbs_queue_event(काष्ठा lbs_निजी *priv, u32 event);
व्योम lbs_notअगरy_command_response(काष्ठा lbs_निजी *priv, u8 resp_idx);

पूर्णांक lbs_enter_स्वतः_deep_sleep(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_निकास_स्वतः_deep_sleep(काष्ठा lbs_निजी *priv);

u32 lbs_fw_index_to_data_rate(u8 index);
u8 lbs_data_rate_to_fw_index(u32 rate);

पूर्णांक lbs_get_firmware(काष्ठा device *dev, u32 card_model,
			स्थिर काष्ठा lbs_fw_table *fw_table,
			स्थिर काष्ठा firmware **helper,
			स्थिर काष्ठा firmware **मुख्यfw);
पूर्णांक lbs_get_firmware_async(काष्ठा lbs_निजी *priv, काष्ठा device *device,
			   u32 card_model, स्थिर काष्ठा lbs_fw_table *fw_table,
			   lbs_fw_cb callback);
व्योम lbs_रुको_क्रम_firmware_load(काष्ठा lbs_निजी *priv);

#पूर्ण_अगर
