<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Link Layer Control manager
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __LOCAL_LLC_H_
#घोषणा __LOCAL_LLC_H_

#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>
#समावेश <linux/skbuff.h>

काष्ठा nfc_llc_ops अणु
	व्योम *(*init) (काष्ठा nfc_hci_dev *hdev, xmit_to_drv_t xmit_to_drv,
		       rcv_to_hci_t rcv_to_hci, पूर्णांक tx_headroom,
		       पूर्णांक tx_tailroom, पूर्णांक *rx_headroom, पूर्णांक *rx_tailroom,
		       llc_failure_t llc_failure);
	व्योम (*deinit) (काष्ठा nfc_llc *llc);
	पूर्णांक (*start) (काष्ठा nfc_llc *llc);
	पूर्णांक (*stop) (काष्ठा nfc_llc *llc);
	व्योम (*rcv_from_drv) (काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb);
	पूर्णांक (*xmit_from_hci) (काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा nfc_llc_engine अणु
	स्थिर अक्षर *name;
	काष्ठा nfc_llc_ops *ops;
	काष्ठा list_head entry;
पूर्ण;

काष्ठा nfc_llc अणु
	व्योम *data;
	काष्ठा nfc_llc_ops *ops;
	पूर्णांक rx_headroom;
	पूर्णांक rx_tailroom;
पूर्ण;

व्योम *nfc_llc_get_data(काष्ठा nfc_llc *llc);

पूर्णांक nfc_llc_रेजिस्टर(स्थिर अक्षर *name, काष्ठा nfc_llc_ops *ops);
व्योम nfc_llc_unरेजिस्टर(स्थिर अक्षर *name);

पूर्णांक nfc_llc_nop_रेजिस्टर(व्योम);

#अगर defined(CONFIG_NFC_SHDLC)
पूर्णांक nfc_llc_shdlc_रेजिस्टर(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक nfc_llc_shdlc_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LOCAL_LLC_H_ */
