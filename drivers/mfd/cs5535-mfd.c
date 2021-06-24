<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs5535-mfd.c - core MFD driver क्रम CS5535/CS5536 southbridges
 *
 * The CS5535 and CS5536 has an ISA bridge on the PCI bus that is
 * used क्रम accessing GPIOs, MFGPTs, ACPI, etc.  Each subdevice has
 * an IO range that's specअगरied in a single BAR.  The BAR order is
 * hardcoded in the CS553x specअगरications.
 *
 * Copyright (c) 2010  Andres Salomon <dilinger@queued.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/olpc.h>

#घोषणा DRV_NAME "cs5535-mfd"

क्रमागत cs5535_mfd_bars अणु
	SMB_BAR = 0,
	GPIO_BAR = 1,
	MFGPT_BAR = 2,
	PMS_BAR = 4,
	ACPI_BAR = 5,
	NR_BARS,
पूर्ण;

अटल काष्ठा resource cs5535_mfd_resources[NR_BARS];

अटल काष्ठा mfd_cell cs5535_mfd_cells[] = अणु
	अणु
		.name = "cs5535-smb",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[SMB_BAR],
	पूर्ण,
	अणु
		.name = "cs5535-gpio",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[GPIO_BAR],
	पूर्ण,
	अणु
		.name = "cs5535-mfgpt",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[MFGPT_BAR],
	पूर्ण,
	अणु
		.name = "cs5535-pms",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[PMS_BAR],
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell cs5535_olpc_mfd_cells[] = अणु
	अणु
		.name = "olpc-xo1-pm-acpi",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[ACPI_BAR],
	पूर्ण,
	अणु
		.name = "olpc-xo1-sci-acpi",
		.num_resources = 1,
		.resources = &cs5535_mfd_resources[ACPI_BAR],
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs5535_mfd_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err, bar;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	क्रम (bar = 0; bar < NR_BARS; bar++) अणु
		काष्ठा resource *r = &cs5535_mfd_resources[bar];

		r->flags = IORESOURCE_IO;
		r->start = pci_resource_start(pdev, bar);
		r->end = pci_resource_end(pdev, bar);
	पूर्ण

	err = pci_request_region(pdev, PMS_BAR, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request PMS_BAR's IO region\n");
		जाओ err_disable;
	पूर्ण

	err = mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE, cs5535_mfd_cells,
			      ARRAY_SIZE(cs5535_mfd_cells), शून्य, 0, शून्य);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to add CS5535 sub-devices: %d\n", err);
		जाओ err_release_pms;
	पूर्ण

	अगर (machine_is_olpc()) अणु
		err = pci_request_region(pdev, ACPI_BAR, DRV_NAME);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to request ACPI_BAR's IO region\n");
			जाओ err_हटाओ_devices;
		पूर्ण

		err = mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				      cs5535_olpc_mfd_cells,
				      ARRAY_SIZE(cs5535_olpc_mfd_cells),
				      शून्य, 0, शून्य);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to add CS5535 OLPC sub-devices: %d\n",
				err);
			जाओ err_release_acpi;
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "%zu devices registered.\n",
			ARRAY_SIZE(cs5535_mfd_cells));

	वापस 0;

err_release_acpi:
	pci_release_region(pdev, ACPI_BAR);
err_हटाओ_devices:
	mfd_हटाओ_devices(&pdev->dev);
err_release_pms:
	pci_release_region(pdev, PMS_BAR);
err_disable:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम cs5535_mfd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	mfd_हटाओ_devices(&pdev->dev);

	अगर (machine_is_olpc())
		pci_release_region(pdev, ACPI_BAR);

	pci_release_region(pdev, PMS_BAR);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5535_mfd_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_CS5535_ISA) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cs5535_mfd_pci_tbl);

अटल काष्ठा pci_driver cs5535_mfd_driver = अणु
	.name = DRV_NAME,
	.id_table = cs5535_mfd_pci_tbl,
	.probe = cs5535_mfd_probe,
	.हटाओ = cs5535_mfd_हटाओ,
पूर्ण;

module_pci_driver(cs5535_mfd_driver);

MODULE_AUTHOR("Andres Salomon <dilinger@queued.net>");
MODULE_DESCRIPTION("MFD driver for CS5535/CS5536 southbridge's ISA PCI device");
MODULE_LICENSE("GPL");
