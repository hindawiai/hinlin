<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ci_hdrc_pci.c - MIPS USB IP core family device controller
 *
 * Copyright (C) 2008 Chipidea - MIPS Technologies, Inc. All rights reserved.
 *
 * Author: David Lopo
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/usb/usb_phy_generic.h>

/* driver name */
#घोषणा UDC_DRIVER_NAME   "ci_hdrc_pci"

काष्ठा ci_hdrc_pci अणु
	काष्ठा platक्रमm_device	*ci;
	काष्ठा platक्रमm_device	*phy;
पूर्ण;

/******************************************************************************
 * PCI block
 *****************************************************************************/
अटल काष्ठा ci_hdrc_platक्रमm_data pci_platdata = अणु
	.name		= UDC_DRIVER_NAME,
	.capoffset	= DEF_CAPOFFSET,
पूर्ण;

अटल काष्ठा ci_hdrc_platक्रमm_data langwell_pci_platdata = अणु
	.name		= UDC_DRIVER_NAME,
	.capoffset	= 0,
पूर्ण;

अटल काष्ठा ci_hdrc_platक्रमm_data penwell_pci_platdata = अणु
	.name		= UDC_DRIVER_NAME,
	.capoffset	= 0,
	.घातer_budget	= 200,
पूर्ण;

/**
 * ci_hdrc_pci_probe: PCI probe
 * @pdev: USB device controller being probed
 * @id:   PCI hotplug ID connecting controller to UDC framework
 *
 * This function वापसs an error code
 * Allocates basic PCI resources क्रम this USB device controller, and then
 * invokes the udc_probe() method to start the UDC associated with it
 */
अटल पूर्णांक ci_hdrc_pci_probe(काष्ठा pci_dev *pdev,
				       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ci_hdrc_platक्रमm_data *platdata = (व्योम *)id->driver_data;
	काष्ठा ci_hdrc_pci *ci;
	काष्ठा resource res[3];
	पूर्णांक retval = 0, nres = 2;

	अगर (!platdata) अणु
		dev_err(&pdev->dev, "device doesn't provide driver data\n");
		वापस -ENODEV;
	पूर्ण

	ci = devm_kzalloc(&pdev->dev, माप(*ci), GFP_KERNEL);
	अगर (!ci)
		वापस -ENOMEM;

	retval = pcim_enable_device(pdev);
	अगर (retval)
		वापस retval;

	अगर (!pdev->irq) अणु
		dev_err(&pdev->dev, "No IRQ, check BIOS/PCI setup!");
		वापस -ENODEV;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	/* रेजिस्टर a nop PHY */
	ci->phy = usb_phy_generic_रेजिस्टर();
	अगर (IS_ERR(ci->phy))
		वापस PTR_ERR(ci->phy);

	स_रखो(res, 0, माप(res));
	res[0].start	= pci_resource_start(pdev, 0);
	res[0].end	= pci_resource_end(pdev, 0);
	res[0].flags	= IORESOURCE_MEM;
	res[1].start	= pdev->irq;
	res[1].flags	= IORESOURCE_IRQ;

	ci->ci = ci_hdrc_add_device(&pdev->dev, res, nres, platdata);
	अगर (IS_ERR(ci->ci)) अणु
		dev_err(&pdev->dev, "ci_hdrc_add_device failed!\n");
		usb_phy_generic_unरेजिस्टर(ci->phy);
		वापस PTR_ERR(ci->ci);
	पूर्ण

	pci_set_drvdata(pdev, ci);

	वापस 0;
पूर्ण

/**
 * ci_hdrc_pci_हटाओ: PCI हटाओ
 * @pdev: USB Device Controller being हटाओd
 *
 * Reverses the effect of ci_hdrc_pci_probe(),
 * first invoking the udc_हटाओ() and then releases
 * all PCI resources allocated क्रम this USB device controller
 */
अटल व्योम ci_hdrc_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ci_hdrc_pci *ci = pci_get_drvdata(pdev);

	ci_hdrc_हटाओ_device(ci->ci);
	usb_phy_generic_unरेजिस्टर(ci->phy);
पूर्ण

/*
 * PCI device table
 * PCI device काष्ठाure
 *
 * Check "pci.h" क्रम details
 *
 * Note: ehci-pci driver may try to probe the device first. You have to add an
 * ID to the bypass_pci_id_table in ehci-pci driver to prevent this.
 */
अटल स्थिर काष्ठा pci_device_id ci_hdrc_pci_id_table[] = अणु
	अणु
		PCI_DEVICE(0x153F, 0x1004),
		.driver_data = (kernel_uदीर्घ_t)&pci_platdata,
	पूर्ण,
	अणु
		PCI_DEVICE(0x153F, 0x1006),
		.driver_data = (kernel_uदीर्घ_t)&pci_platdata,
	पूर्ण,
	अणु
		PCI_VDEVICE(INTEL, 0x0811),
		.driver_data = (kernel_uदीर्घ_t)&langwell_pci_platdata,
	पूर्ण,
	अणु
		PCI_VDEVICE(INTEL, 0x0829),
		.driver_data = (kernel_uदीर्घ_t)&penwell_pci_platdata,
	पूर्ण,
	अणु
		/* Intel Clovertrail */
		PCI_VDEVICE(INTEL, 0xe006),
		.driver_data = (kernel_uदीर्घ_t)&penwell_pci_platdata,
	पूर्ण,
	अणु 0 पूर्ण /* end: all zeroes */
पूर्ण;
MODULE_DEVICE_TABLE(pci, ci_hdrc_pci_id_table);

अटल काष्ठा pci_driver ci_hdrc_pci_driver = अणु
	.name         =	UDC_DRIVER_NAME,
	.id_table     =	ci_hdrc_pci_id_table,
	.probe        =	ci_hdrc_pci_probe,
	.हटाओ       =	ci_hdrc_pci_हटाओ,
पूर्ण;

module_pci_driver(ci_hdrc_pci_driver);

MODULE_AUTHOR("MIPS - David Lopo <dlopo@chipidea.mips.com>");
MODULE_DESCRIPTION("MIPS CI13XXX USB Peripheral Controller");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ci13xxx_pci");
