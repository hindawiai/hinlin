<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013  Intel Corporation. All rights reserved.
 *
 * HCI based Driver क्रम NXP pn544 NFC Chip
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "../mei_phy.h"
#समावेश "pn544.h"

#घोषणा PN544_DRIVER_NAME "pn544"

अटल पूर्णांक pn544_mei_probe(काष्ठा mei_cl_device *cldev,
			       स्थिर काष्ठा mei_cl_device_id *id)
अणु
	काष्ठा nfc_mei_phy *phy;
	पूर्णांक r;

	pr_info("Probing NFC pn544\n");

	phy = nfc_mei_phy_alloc(cldev);
	अगर (!phy) अणु
		pr_err("Cannot allocate memory for pn544 mei phy.\n");
		वापस -ENOMEM;
	पूर्ण

	r = pn544_hci_probe(phy, &mei_phy_ops, LLC_NOP_NAME,
			    MEI_NFC_HEADER_SIZE, 0, MEI_NFC_MAX_HCI_PAYLOAD,
			    शून्य, &phy->hdev);
	अगर (r < 0) अणु
		nfc_mei_phy_मुक्त(phy);

		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pn544_mei_हटाओ(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा nfc_mei_phy *phy = mei_cldev_get_drvdata(cldev);

	pr_info("Removing pn544\n");

	pn544_hci_हटाओ(phy->hdev);

	nfc_mei_phy_मुक्त(phy);
पूर्ण

अटल काष्ठा mei_cl_device_id pn544_mei_tbl[] = अणु
	अणु PN544_DRIVER_NAME, MEI_NFC_UUID, MEI_CL_VERSION_ANYपूर्ण,

	/* required last entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mei, pn544_mei_tbl);

अटल काष्ठा mei_cl_driver pn544_driver = अणु
	.id_table = pn544_mei_tbl,
	.name = PN544_DRIVER_NAME,

	.probe = pn544_mei_probe,
	.हटाओ = pn544_mei_हटाओ,
पूर्ण;

module_mei_cl_driver(pn544_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
