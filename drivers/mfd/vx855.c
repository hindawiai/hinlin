<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux multi-function-device driver (MFD) क्रम the पूर्णांकegrated peripherals
 * of the VIA VX855 chipset
 *
 * Copyright (C) 2009 VIA Technologies, Inc.
 * Copyright (C) 2010 One Laptop per Child
 * Author: Harald Welte <HaraldWelte@viatech.com>
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/mfd/core.h>

/* offset पूर्णांकo pci config space indicating the 16bit रेजिस्टर containing
 * the घातer management IO space base */
#घोषणा VX855_CFG_PMIO_OFFSET	0x88

/* ACPI I/O Space रेजिस्टरs */
#घोषणा VX855_PMIO_ACPI		0x00
#घोषणा VX855_PMIO_ACPI_LEN	0x0b

/* Processor Power Management */
#घोषणा VX855_PMIO_PPM		0x10
#घोषणा VX855_PMIO_PPM_LEN	0x08

/* General Purpose Power Management */
#घोषणा VX855_PMIO_GPPM		0x20
#घोषणा VX855_PMIO_R_GPI	0x48
#घोषणा VX855_PMIO_R_GPO	0x4c
#घोषणा VX855_PMIO_GPPM_LEN	0x33

#घोषणा VSPIC_MMIO_SIZE	0x1000

अटल काष्ठा resource vx855_gpio_resources[] = अणु
	अणु
		.flags = IORESOURCE_IO,
	पूर्ण,
	अणु
		.flags = IORESOURCE_IO,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell vx855_cells[] = अणु
	अणु
		.name = "vx855_gpio",
		.num_resources = ARRAY_SIZE(vx855_gpio_resources),
		.resources = vx855_gpio_resources,

		/* we must ignore resource conflicts, क्रम reasons outlined in
		 * the vx855_gpio driver */
		.ignore_resource_conflicts = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक vx855_probe(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	u16 gpio_io_offset;

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस -ENODEV;

	pci_पढ़ो_config_word(pdev, VX855_CFG_PMIO_OFFSET, &gpio_io_offset);
	अगर (!gpio_io_offset) अणु
		dev_warn(&pdev->dev,
			"BIOS did not assign PMIO base offset?!?\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* mask out the lowest seven bits, as they are always zero, but
	 * hardware वापसs them as 0x01 */
	gpio_io_offset &= 0xff80;

	/* As the region identअगरied here includes many non-GPIO things, we
	 * only work with the specअगरic रेजिस्टरs that concern us. */
	vx855_gpio_resources[0].start = gpio_io_offset + VX855_PMIO_R_GPI;
	vx855_gpio_resources[0].end = vx855_gpio_resources[0].start + 3;
	vx855_gpio_resources[1].start = gpio_io_offset + VX855_PMIO_R_GPO;
	vx855_gpio_resources[1].end = vx855_gpio_resources[1].start + 3;

	ret = mfd_add_devices(&pdev->dev, -1, vx855_cells, ARRAY_SIZE(vx855_cells),
			शून्य, 0, शून्य);

	/* we always वापस -ENODEV here in order to enable other
	 * drivers like old, not-yet-platक्रमm_device ported i2c-viapro */
	वापस -ENODEV;
out:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम vx855_हटाओ(काष्ठा pci_dev *pdev)
अणु
	mfd_हटाओ_devices(&pdev->dev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id vx855_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VX855) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, vx855_pci_tbl);

अटल काष्ठा pci_driver vx855_pci_driver = अणु
	.name		= "vx855",
	.id_table	= vx855_pci_tbl,
	.probe		= vx855_probe,
	.हटाओ		= vx855_हटाओ,
पूर्ण;

module_pci_driver(vx855_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <HaraldWelte@viatech.com>");
MODULE_DESCRIPTION("Driver for the VIA VX855 chipset");
