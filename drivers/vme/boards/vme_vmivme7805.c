<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the VMIVME-7805 board access to the Universe II bridge.
 *
 * Author: Arthur Benilov <arthur.benilov@iba-group.com>
 * Copyright 2010 Ion Beam Application, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>

#समावेश "vme_vmivme7805.h"

अटल पूर्णांक vmic_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम vmic_हटाओ(काष्ठा pci_dev *);

/** Base address to access FPGA रेजिस्टर */
अटल व्योम __iomem *vmic_base;

अटल स्थिर अक्षर driver_name[] = "vmivme_7805";

अटल स्थिर काष्ठा pci_device_id vmic_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VMIC, PCI_DEVICE_ID_VTIMR) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver vmic_driver = अणु
	.name = driver_name,
	.id_table = vmic_ids,
	.probe = vmic_probe,
	.हटाओ = vmic_हटाओ,
पूर्ण;

अटल पूर्णांक vmic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक retval;
	u32 data;

	/* Enable the device */
	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "Unable to enable device\n");
		जाओ err;
	पूर्ण

	/* Map Registers */
	retval = pci_request_regions(pdev, driver_name);
	अगर (retval) अणु
		dev_err(&pdev->dev, "Unable to reserve resources\n");
		जाओ err_resource;
	पूर्ण

	/* Map रेजिस्टरs in BAR 0 */
	vmic_base = ioremap(pci_resource_start(pdev, 0), 16);
	अगर (!vmic_base) अणु
		dev_err(&pdev->dev, "Unable to remap CRG region\n");
		retval = -EIO;
		जाओ err_remap;
	पूर्ण

	/* Clear the FPGA VME IF contents */
	ioग_लिखो32(0, vmic_base + VME_CONTROL);

	/* Clear any initial BERR  */
	data = ioपढ़ो32(vmic_base + VME_CONTROL) & 0x00000FFF;
	data |= BM_VME_CONTROL_BERRST;
	ioग_लिखो32(data, vmic_base + VME_CONTROL);

	/* Enable the vme पूर्णांकerface and byte swapping */
	data = ioपढ़ो32(vmic_base + VME_CONTROL) & 0x00000FFF;
	data = data | BM_VME_CONTROL_MASTER_ENDIAN |
			BM_VME_CONTROL_SLAVE_ENDIAN |
			BM_VME_CONTROL_ABLE |
			BM_VME_CONTROL_BERRI |
			BM_VME_CONTROL_BPENA |
			BM_VME_CONTROL_VBENA;
	ioग_लिखो32(data, vmic_base + VME_CONTROL);

	वापस 0;

err_remap:
	pci_release_regions(pdev);
err_resource:
	pci_disable_device(pdev);
err:
	वापस retval;
पूर्ण

अटल व्योम vmic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	iounmap(vmic_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

पूर्ण

module_pci_driver(vmic_driver);

MODULE_DESCRIPTION("VMIVME-7805 board support driver");
MODULE_AUTHOR("Arthur Benilov <arthur.benilov@iba-group.com>");
MODULE_LICENSE("GPL");

