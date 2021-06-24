<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_MODEM_H_
#घोषणा _IPA_MODEM_H_

काष्ठा ipa;
काष्ठा ipa_endpoपूर्णांक;
काष्ठा net_device;
काष्ठा sk_buff;

पूर्णांक ipa_modem_start(काष्ठा ipa *ipa);
पूर्णांक ipa_modem_stop(काष्ठा ipa *ipa);

व्योम ipa_modem_skb_rx(काष्ठा net_device *netdev, काष्ठा sk_buff *skb);

व्योम ipa_modem_suspend(काष्ठा net_device *netdev);
व्योम ipa_modem_resume(काष्ठा net_device *netdev);

पूर्णांक ipa_modem_init(काष्ठा ipa *ipa, bool modem_init);
व्योम ipa_modem_निकास(काष्ठा ipa *ipa);

पूर्णांक ipa_modem_config(काष्ठा ipa *ipa);
व्योम ipa_modem_deconfig(काष्ठा ipa *ipa);

पूर्णांक ipa_modem_setup(काष्ठा ipa *ipa);
व्योम ipa_modem_tearकरोwn(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_MODEM_H_ */
