<शैली गुरु>
/*
 * Broadcom 43xx PCI-SSB bridge module
 *
 * This technically is a separate PCI driver module, but
 * because of its small size we include it in the SSB core
 * instead of creating a standalone module.
 *
 * Copyright 2007  Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/ssb/ssb.h>


अटल स्थिर काष्ठा pci_device_id b43_pci_bridge_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4301) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4306) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4307) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4311) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4312) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4315) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4318) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BCM_GVC,  0x4318) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4319) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4320) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4321) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4322) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 43222) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4324) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4325) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4328) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4329) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x432b) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x432c) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4350) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROADCOM, 0x4351) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, b43_pci_bridge_tbl);

अटल काष्ठा pci_driver b43_pci_bridge_driver = अणु
	.name = "b43-pci-bridge",
	.id_table = b43_pci_bridge_tbl,
पूर्ण;


पूर्णांक __init b43_pci_ssb_bridge_init(व्योम)
अणु
	वापस ssb_pcihost_रेजिस्टर(&b43_pci_bridge_driver);
पूर्ण

व्योम __निकास b43_pci_ssb_bridge_निकास(व्योम)
अणु
	ssb_pcihost_unरेजिस्टर(&b43_pci_bridge_driver);
पूर्ण
