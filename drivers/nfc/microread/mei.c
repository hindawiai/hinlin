<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
 *
 * HCI based Driver क्रम Inside Secure microपढ़ो NFC Chip
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "../mei_phy.h"
#समावेश "microread.h"

#घोषणा MICROREAD_DRIVER_NAME "microread"

अटल पूर्णांक microपढ़ो_mei_probe(काष्ठा mei_cl_device *cldev,
			       स्थिर काष्ठा mei_cl_device_id *id)
अणु
	काष्ठा nfc_mei_phy *phy;
	पूर्णांक r;

	pr_info("Probing NFC microread\n");

	phy = nfc_mei_phy_alloc(cldev);
	अगर (!phy) अणु
		pr_err("Cannot allocate memory for microread mei phy.\n");
		वापस -ENOMEM;
	पूर्ण

	r = microपढ़ो_probe(phy, &mei_phy_ops, LLC_NOP_NAME,
			    MEI_NFC_HEADER_SIZE, 0, MEI_NFC_MAX_HCI_PAYLOAD,
			    &phy->hdev);
	अगर (r < 0) अणु
		nfc_mei_phy_मुक्त(phy);

		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम microपढ़ो_mei_हटाओ(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा nfc_mei_phy *phy = mei_cldev_get_drvdata(cldev);

	microपढ़ो_हटाओ(phy->hdev);

	nfc_mei_phy_मुक्त(phy);
पूर्ण

अटल काष्ठा mei_cl_device_id microपढ़ो_mei_tbl[] = अणु
	अणु MICROREAD_DRIVER_NAME, MEI_NFC_UUID, MEI_CL_VERSION_ANYपूर्ण,

	/* required last entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mei, microपढ़ो_mei_tbl);

अटल काष्ठा mei_cl_driver microपढ़ो_driver = अणु
	.id_table = microपढ़ो_mei_tbl,
	.name = MICROREAD_DRIVER_NAME,

	.probe = microपढ़ो_mei_probe,
	.हटाओ = microपढ़ो_mei_हटाओ,
पूर्ण;

module_mei_cl_driver(microपढ़ो_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
