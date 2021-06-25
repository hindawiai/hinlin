<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 - 2012  Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __LOCAL_PN544_H_
#घोषणा __LOCAL_PN544_H_

#समावेश <net/nfc/hci.h>

#घोषणा DRIVER_DESC "HCI NFC driver for PN544"

#घोषणा PN544_HCI_MODE 0
#घोषणा PN544_FW_MODE 1

प्रकार पूर्णांक (*fw_करोwnload_t)(व्योम *context, स्थिर अक्षर *firmware_name,
				u8 hw_variant);

पूर्णांक pn544_hci_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops, अक्षर *llc_name,
		    पूर्णांक phy_headroom, पूर्णांक phy_tailroom, पूर्णांक phy_payload,
		    fw_करोwnload_t fw_करोwnload, काष्ठा nfc_hci_dev **hdev);
व्योम pn544_hci_हटाओ(काष्ठा nfc_hci_dev *hdev);

#पूर्ण_अगर /* __LOCAL_PN544_H_ */
