<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 *
 * Authors:
 *    Lauro Ramos Venancio <lauro.venancio@खोलोbossa.org>
 *    Aloisio Almeida Jr <aloisio.almeida@खोलोbossa.org>
 */

#अगर_अघोषित __LOCAL_NFC_H
#घोषणा __LOCAL_NFC_H

#समावेश <net/nfc/nfc.h>
#समावेश <net/sock.h>

#घोषणा NFC_TARGET_MODE_IDLE 0
#घोषणा NFC_TARGET_MODE_SLEEP 1

काष्ठा nfc_protocol अणु
	पूर्णांक id;
	काष्ठा proto *proto;
	काष्ठा module *owner;
	पूर्णांक (*create)(काष्ठा net *net, काष्ठा socket *sock,
		      स्थिर काष्ठा nfc_protocol *nfc_proto, पूर्णांक kern);
पूर्ण;

काष्ठा nfc_rawsock अणु
	काष्ठा sock sk;
	काष्ठा nfc_dev *dev;
	u32 target_idx;
	काष्ठा work_काष्ठा tx_work;
	bool tx_work_scheduled;
पूर्ण;

काष्ठा nfc_sock_list अणु
	काष्ठा hlist_head head;
	rwlock_t          lock;
पूर्ण;

#घोषणा nfc_rawsock(sk) ((काष्ठा nfc_rawsock *) sk)
#घोषणा to_rawsock_sk(_tx_work) \
	((काष्ठा sock *) container_of(_tx_work, काष्ठा nfc_rawsock, tx_work))

काष्ठा nfc_llcp_sdp_tlv;

व्योम nfc_llcp_mac_is_करोwn(काष्ठा nfc_dev *dev);
व्योम nfc_llcp_mac_is_up(काष्ठा nfc_dev *dev, u32 target_idx,
			u8 comm_mode, u8 rf_mode);
पूर्णांक nfc_llcp_रेजिस्टर_device(काष्ठा nfc_dev *dev);
व्योम nfc_llcp_unरेजिस्टर_device(काष्ठा nfc_dev *dev);
पूर्णांक nfc_llcp_set_remote_gb(काष्ठा nfc_dev *dev, u8 *gb, u8 gb_len);
u8 *nfc_llcp_general_bytes(काष्ठा nfc_dev *dev, माप_प्रकार *general_bytes_len);
पूर्णांक nfc_llcp_data_received(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb);
काष्ठा nfc_llcp_local *nfc_llcp_find_local(काष्ठा nfc_dev *dev);
पूर्णांक __init nfc_llcp_init(व्योम);
व्योम nfc_llcp_निकास(व्योम);
व्योम nfc_llcp_मुक्त_sdp_tlv(काष्ठा nfc_llcp_sdp_tlv *sdp);
व्योम nfc_llcp_मुक्त_sdp_tlv_list(काष्ठा hlist_head *head);

पूर्णांक __init rawsock_init(व्योम);
व्योम rawsock_निकास(व्योम);

पूर्णांक __init af_nfc_init(व्योम);
व्योम af_nfc_निकास(व्योम);
पूर्णांक nfc_proto_रेजिस्टर(स्थिर काष्ठा nfc_protocol *nfc_proto);
व्योम nfc_proto_unरेजिस्टर(स्थिर काष्ठा nfc_protocol *nfc_proto);

बाह्य पूर्णांक nfc_devlist_generation;
बाह्य काष्ठा mutex nfc_devlist_mutex;

पूर्णांक __init nfc_genl_init(व्योम);
व्योम nfc_genl_निकास(व्योम);

व्योम nfc_genl_data_init(काष्ठा nfc_genl_data *genl_data);
व्योम nfc_genl_data_निकास(काष्ठा nfc_genl_data *genl_data);

पूर्णांक nfc_genl_tarमाला_लो_found(काष्ठा nfc_dev *dev);
पूर्णांक nfc_genl_target_lost(काष्ठा nfc_dev *dev, u32 target_idx);

पूर्णांक nfc_genl_device_added(काष्ठा nfc_dev *dev);
पूर्णांक nfc_genl_device_हटाओd(काष्ठा nfc_dev *dev);

पूर्णांक nfc_genl_dep_link_up_event(काष्ठा nfc_dev *dev, u32 target_idx,
			       u8 comm_mode, u8 rf_mode);
पूर्णांक nfc_genl_dep_link_करोwn_event(काष्ठा nfc_dev *dev);

पूर्णांक nfc_genl_पंचांग_activated(काष्ठा nfc_dev *dev, u32 protocol);
पूर्णांक nfc_genl_पंचांग_deactivated(काष्ठा nfc_dev *dev);

पूर्णांक nfc_genl_llc_send_sdres(काष्ठा nfc_dev *dev, काष्ठा hlist_head *sdres_list);

पूर्णांक nfc_genl_se_added(काष्ठा nfc_dev *dev, u32 se_idx, u16 type);
पूर्णांक nfc_genl_se_हटाओd(काष्ठा nfc_dev *dev, u32 se_idx);
पूर्णांक nfc_genl_se_transaction(काष्ठा nfc_dev *dev, u8 se_idx,
			    काष्ठा nfc_evt_transaction *evt_transaction);
पूर्णांक nfc_genl_se_connectivity(काष्ठा nfc_dev *dev, u8 se_idx);

काष्ठा nfc_dev *nfc_get_device(अचिन्हित पूर्णांक idx);

अटल अंतरभूत व्योम nfc_put_device(काष्ठा nfc_dev *dev)
अणु
	put_device(&dev->dev);
पूर्ण

अटल अंतरभूत व्योम nfc_device_iter_init(काष्ठा class_dev_iter *iter)
अणु
	class_dev_iter_init(iter, &nfc_class, शून्य, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा nfc_dev *nfc_device_iter_next(काष्ठा class_dev_iter *iter)
अणु
	काष्ठा device *d = class_dev_iter_next(iter);
	अगर (!d)
		वापस शून्य;

	वापस to_nfc_dev(d);
पूर्ण

अटल अंतरभूत व्योम nfc_device_iter_निकास(काष्ठा class_dev_iter *iter)
अणु
	class_dev_iter_निकास(iter);
पूर्ण

पूर्णांक nfc_fw_करोwnload(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name);
पूर्णांक nfc_genl_fw_करोwnload_करोne(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name,
			      u32 result);

पूर्णांक nfc_dev_up(काष्ठा nfc_dev *dev);

पूर्णांक nfc_dev_करोwn(काष्ठा nfc_dev *dev);

पूर्णांक nfc_start_poll(काष्ठा nfc_dev *dev, u32 im_protocols, u32 पंचांग_protocols);

पूर्णांक nfc_stop_poll(काष्ठा nfc_dev *dev);

पूर्णांक nfc_dep_link_up(काष्ठा nfc_dev *dev, पूर्णांक target_idx, u8 comm_mode);

पूर्णांक nfc_dep_link_करोwn(काष्ठा nfc_dev *dev);

पूर्णांक nfc_activate_target(काष्ठा nfc_dev *dev, u32 target_idx, u32 protocol);

पूर्णांक nfc_deactivate_target(काष्ठा nfc_dev *dev, u32 target_idx, u8 mode);

पूर्णांक nfc_data_exchange(काष्ठा nfc_dev *dev, u32 target_idx, काष्ठा sk_buff *skb,
		      data_exchange_cb_t cb, व्योम *cb_context);

पूर्णांक nfc_enable_se(काष्ठा nfc_dev *dev, u32 se_idx);
पूर्णांक nfc_disable_se(काष्ठा nfc_dev *dev, u32 se_idx);

#पूर्ण_अगर /* __LOCAL_NFC_H */
