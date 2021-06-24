<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 - 2012  Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __LOCAL_MICROREAD_H_
#घोषणा __LOCAL_MICROREAD_H_

#समावेश <net/nfc/hci.h>

#घोषणा DRIVER_DESC "NFC driver for microread"

पूर्णांक microपढ़ो_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops, अक्षर *llc_name,
		    पूर्णांक phy_headroom, पूर्णांक phy_tailroom, पूर्णांक phy_payload,
		    काष्ठा nfc_hci_dev **hdev);

व्योम microपढ़ो_हटाओ(काष्ठा nfc_hci_dev *hdev);

#पूर्ण_अगर /* __LOCAL_MICROREAD_H_ */
