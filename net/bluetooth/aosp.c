<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021 Intel Corporation
 */

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "aosp.h"

व्योम aosp_करो_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	अगर (!hdev->aosp_capable)
		वापस;

	bt_dev_dbg(hdev, "Initialize AOSP extension");

	/* LE Get Venकरोr Capabilities Command */
	skb = __hci_cmd_sync(hdev, hci_opcode_pack(0x3f, 0x153), 0, शून्य,
			     HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस;

	kमुक्त_skb(skb);
पूर्ण

व्योम aosp_करो_बंद(काष्ठा hci_dev *hdev)
अणु
	अगर (!hdev->aosp_capable)
		वापस;

	bt_dev_dbg(hdev, "Cleanup of AOSP extension");
पूर्ण
