<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Link Layer Control manager खुला पूर्णांकerface
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __NFC_LLC_H_
#घोषणा __NFC_LLC_H_

#समावेश <net/nfc/hci.h>
#समावेश <linux/skbuff.h>

#घोषणा LLC_NOP_NAME "nop"
#घोषणा LLC_SHDLC_NAME "shdlc"

प्रकार व्योम (*rcv_to_hci_t) (काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);
प्रकार पूर्णांक (*xmit_to_drv_t) (काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);
प्रकार व्योम (*llc_failure_t) (काष्ठा nfc_hci_dev *hdev, पूर्णांक err);

काष्ठा nfc_llc;

काष्ठा nfc_llc *nfc_llc_allocate(स्थिर अक्षर *name, काष्ठा nfc_hci_dev *hdev,
				 xmit_to_drv_t xmit_to_drv,
				 rcv_to_hci_t rcv_to_hci, पूर्णांक tx_headroom,
				 पूर्णांक tx_tailroom, llc_failure_t llc_failure);
व्योम nfc_llc_मुक्त(काष्ठा nfc_llc *llc);

पूर्णांक nfc_llc_start(काष्ठा nfc_llc *llc);
पूर्णांक nfc_llc_stop(काष्ठा nfc_llc *llc);
व्योम nfc_llc_rcv_from_drv(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb);
पूर्णांक nfc_llc_xmit_from_hci(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb);

पूर्णांक nfc_llc_init(व्योम);
व्योम nfc_llc_निकास(व्योम);

#पूर्ण_अगर /* __NFC_LLC_H_ */
