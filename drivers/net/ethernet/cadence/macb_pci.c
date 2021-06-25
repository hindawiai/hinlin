<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * DOC: Cadence GEM PCI wrapper.
 *
 * Copyright (C) 2016 Cadence Design Systems - https://www.cadence.com
 *
 * Authors: Rafal Ozieblo <rafalo@cadence.com>
 *	    Bartosz Folta <bfolta@cadence.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "macb.h"

#घोषणा PCI_DRIVER_NAME "macb_pci"
#घोषणा PLAT_DRIVER_NAME "macb"

#घोषणा CDNS_VENDOR_ID 0x17cd
#घोषणा CDNS_DEVICE_ID 0xe007

#घोषणा GEM_PCLK_RATE 50000000
#घोषणा GEM_HCLK_RATE 50000000

अटल पूर्णांक macb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा platक्रमm_device *plat_dev;
	काष्ठा platक्रमm_device_info plat_info;
	काष्ठा macb_platक्रमm_data plat_data;
	काष्ठा resource res[2];

	/* enable pci device */
	err = pcim_enable_device(pdev);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Enabling PCI device has failed: %d", err);
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	/* set up resources */
	स_रखो(res, 0x00, माप(काष्ठा resource) * ARRAY_SIZE(res));
	res[0].start = pci_resource_start(pdev, 0);
	res[0].end = pci_resource_end(pdev, 0);
	res[0].name = PCI_DRIVER_NAME;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = pci_irq_vector(pdev, 0);
	res[1].name = PCI_DRIVER_NAME;
	res[1].flags = IORESOURCE_IRQ;

	dev_info(&pdev->dev, "EMAC physical base addr: %pa\n",
		 &res[0].start);

	/* set up macb platक्रमm data */
	स_रखो(&plat_data, 0, माप(plat_data));

	/* initialize घड़ीs */
	plat_data.pclk = clk_रेजिस्टर_fixed_rate(&pdev->dev, "pclk", शून्य, 0,
						 GEM_PCLK_RATE);
	अगर (IS_ERR(plat_data.pclk)) अणु
		err = PTR_ERR(plat_data.pclk);
		जाओ err_pclk_रेजिस्टर;
	पूर्ण

	plat_data.hclk = clk_रेजिस्टर_fixed_rate(&pdev->dev, "hclk", शून्य, 0,
						 GEM_HCLK_RATE);
	अगर (IS_ERR(plat_data.hclk)) अणु
		err = PTR_ERR(plat_data.hclk);
		जाओ err_hclk_रेजिस्टर;
	पूर्ण

	/* set up platक्रमm device info */
	स_रखो(&plat_info, 0, माप(plat_info));
	plat_info.parent = &pdev->dev;
	plat_info.fwnode = pdev->dev.fwnode;
	plat_info.name = PLAT_DRIVER_NAME;
	plat_info.id = pdev->devfn;
	plat_info.res = res;
	plat_info.num_res = ARRAY_SIZE(res);
	plat_info.data = &plat_data;
	plat_info.size_data = माप(plat_data);
	plat_info.dma_mask = pdev->dma_mask;

	/* रेजिस्टर platक्रमm device */
	plat_dev = platक्रमm_device_रेजिस्टर_full(&plat_info);
	अगर (IS_ERR(plat_dev)) अणु
		err = PTR_ERR(plat_dev);
		जाओ err_plat_dev_रेजिस्टर;
	पूर्ण

	pci_set_drvdata(pdev, plat_dev);

	वापस 0;

err_plat_dev_रेजिस्टर:
	clk_unरेजिस्टर(plat_data.hclk);

err_hclk_रेजिस्टर:
	clk_unरेजिस्टर(plat_data.pclk);

err_pclk_रेजिस्टर:
	वापस err;
पूर्ण

अटल व्योम macb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा platक्रमm_device *plat_dev = pci_get_drvdata(pdev);
	काष्ठा macb_platक्रमm_data *plat_data = dev_get_platdata(&plat_dev->dev);

	platक्रमm_device_unरेजिस्टर(plat_dev);
	clk_unरेजिस्टर(plat_data->pclk);
	clk_unरेजिस्टर(plat_data->hclk);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dev_id_table[] = अणु
	अणु PCI_DEVICE(CDNS_VENDOR_ID, CDNS_DEVICE_ID), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver macb_pci_driver = अणु
	.name     = PCI_DRIVER_NAME,
	.id_table = dev_id_table,
	.probe    = macb_probe,
	.हटाओ	  = macb_हटाओ,
पूर्ण;

module_pci_driver(macb_pci_driver);
MODULE_DEVICE_TABLE(pci, dev_id_table);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cadence NIC PCI wrapper");
