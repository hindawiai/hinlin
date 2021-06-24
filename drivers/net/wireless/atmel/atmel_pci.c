<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*** -*- linux-c -*- **********************************************************

     Driver क्रम Aपंचांगel at76c502 at76c504 and at76c506 wireless cards.

         Copyright 2004 Simon Kelley.


******************************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश "atmel.h"

MODULE_AUTHOR("Simon Kelley");
MODULE_DESCRIPTION("Support for Atmel at76c50x 802.11 wireless ethernet cards.");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा pci_device_id card_ids[] = अणु
	अणु 0x1114, 0x0506, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, card_ids);

अटल पूर्णांक aपंचांगel_pci_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम aपंचांगel_pci_हटाओ(काष्ठा pci_dev *);

अटल काष्ठा pci_driver aपंचांगel_driver = अणु
	.name     = "atmel",
	.id_table = card_ids,
	.probe    = aपंचांगel_pci_probe,
	.हटाओ   = aपंचांगel_pci_हटाओ,
पूर्ण;


अटल पूर्णांक aपंचांगel_pci_probe(काष्ठा pci_dev *pdev,
				     स्थिर काष्ठा pci_device_id *pent)
अणु
	काष्ठा net_device *dev;

	अगर (pci_enable_device(pdev))
		वापस -ENODEV;

	pci_set_master(pdev);

	dev = init_aपंचांगel_card(pdev->irq, pdev->resource[1].start,
			      ATMEL_FW_TYPE_506,
			      &pdev->dev, शून्य, शून्य);
	अगर (!dev) अणु
		pci_disable_device(pdev);
		वापस -ENODEV;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	stop_aपंचांगel_card(pci_get_drvdata(pdev));
पूर्ण

module_pci_driver(aपंचांगel_driver);
