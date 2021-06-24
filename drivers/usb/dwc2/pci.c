<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * pci.c - DesignWare HS OTG Controller PCI driver
 *
 * Copyright (C) 2004-2013 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Provides the initialization and cleanup entry poपूर्णांकs क्रम the DWC_otg PCI
 * driver
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>

#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ch11.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/usb_phy_generic.h>

#घोषणा PCI_PRODUCT_ID_HAPS_HSOTG	0xabc0

अटल स्थिर अक्षर dwc2_driver_name[] = "dwc2-pci";

काष्ठा dwc2_pci_glue अणु
	काष्ठा platक्रमm_device *dwc2;
	काष्ठा platक्रमm_device *phy;
पूर्ण;

/**
 * dwc2_pci_probe() - Provides the cleanup entry poपूर्णांकs क्रम the DWC_otg PCI
 * driver
 *
 * @pci: The programming view of DWC_otg PCI
 */
अटल व्योम dwc2_pci_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा dwc2_pci_glue *glue = pci_get_drvdata(pci);

	platक्रमm_device_unरेजिस्टर(glue->dwc2);
	usb_phy_generic_unरेजिस्टर(glue->phy);
	pci_set_drvdata(pci, शून्य);
पूर्ण

अटल पूर्णांक dwc2_pci_probe(काष्ठा pci_dev *pci,
			  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा resource		res[2];
	काष्ठा platक्रमm_device	*dwc2;
	काष्ठा platक्रमm_device	*phy;
	पूर्णांक			ret;
	काष्ठा device		*dev = &pci->dev;
	काष्ठा dwc2_pci_glue	*glue;

	ret = pcim_enable_device(pci);
	अगर (ret) अणु
		dev_err(dev, "failed to enable pci device\n");
		वापस -ENODEV;
	पूर्ण

	pci_set_master(pci);

	phy = usb_phy_generic_रेजिस्टर();
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "error registering generic PHY (%ld)\n",
			PTR_ERR(phy));
		वापस PTR_ERR(phy);
	पूर्ण

	dwc2 = platक्रमm_device_alloc("dwc2", PLATFORM_DEVID_AUTO);
	अगर (!dwc2) अणु
		dev_err(dev, "couldn't allocate dwc2 device\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	स_रखो(res, 0x00, माप(काष्ठा resource) * ARRAY_SIZE(res));

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= "dwc2";
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= "dwc2";
	res[1].flags	= IORESOURCE_IRQ;

	ret = platक्रमm_device_add_resources(dwc2, res, ARRAY_SIZE(res));
	अगर (ret) अणु
		dev_err(dev, "couldn't add resources to dwc2 device\n");
		जाओ err;
	पूर्ण

	dwc2->dev.parent = dev;

	glue = devm_kzalloc(dev, माप(*glue), GFP_KERNEL);
	अगर (!glue) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = platक्रमm_device_add(dwc2);
	अगर (ret) अणु
		dev_err(dev, "failed to register dwc2 device\n");
		जाओ err;
	पूर्ण

	glue->phy = phy;
	glue->dwc2 = dwc2;
	pci_set_drvdata(pci, glue);

	वापस 0;
err:
	usb_phy_generic_unरेजिस्टर(phy);
	platक्रमm_device_put(dwc2);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id dwc2_pci_ids[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_SYNOPSYS, PCI_PRODUCT_ID_HAPS_HSOTG),
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_STMICRO,
			   PCI_DEVICE_ID_STMICRO_USB_OTG),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dwc2_pci_ids);

अटल काष्ठा pci_driver dwc2_pci_driver = अणु
	.name = dwc2_driver_name,
	.id_table = dwc2_pci_ids,
	.probe = dwc2_pci_probe,
	.हटाओ = dwc2_pci_हटाओ,
पूर्ण;

module_pci_driver(dwc2_pci_driver);

MODULE_DESCRIPTION("DESIGNWARE HS OTG PCI Bus Glue");
MODULE_AUTHOR("Synopsys, Inc.");
MODULE_LICENSE("Dual BSD/GPL");
