<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/ni_labpc_pci.c
 * Driver क्रम National Instruments Lab-PC PCI-1200
 * Copyright (C) 2001, 2002, 2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

/*
 * Driver: ni_labpc_pci
 * Description: National Instruments Lab-PC PCI-1200
 * Devices: [National Instruments] PCI-1200 (ni_pci-1200)
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Status: works
 *
 * This is the PCI-specअगरic support split off from the ni_labpc driver.
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 *
 * NI manuals:
 * 340914a (pci-1200)
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "ni_labpc.h"

क्रमागत labpc_pci_boardid अणु
	BOARD_NI_PCI1200,
पूर्ण;

अटल स्थिर काष्ठा labpc_boardinfo labpc_pci_boards[] = अणु
	[BOARD_NI_PCI1200] = अणु
		.name			= "ni_pci-1200",
		.ai_speed		= 10000,
		.ai_scan_up		= 1,
		.has_ao			= 1,
		.is_labpc1200		= 1,
	पूर्ण,
पूर्ण;

/* ripped from mite.h and mite_setup2() to aव्योम mite dependency */
#घोषणा MITE_IODWBSR	0xc0	/* IO Device Winकरोw Base Size Register */
#घोषणा WENAB		BIT(7)	/* winकरोw enable */

अटल पूर्णांक labpc_pci_mite_init(काष्ठा pci_dev *pcidev)
अणु
	व्योम __iomem *mite_base;
	u32 मुख्य_phys_addr;

	/* ioremap the MITE रेजिस्टरs (BAR 0) temporarily */
	mite_base = pci_ioremap_bar(pcidev, 0);
	अगर (!mite_base)
		वापस -ENOMEM;

	/* set data winकरोw to मुख्य रेजिस्टरs (BAR 1) */
	मुख्य_phys_addr = pci_resource_start(pcidev, 1);
	ग_लिखोl(मुख्य_phys_addr | WENAB, mite_base + MITE_IODWBSR);

	/* finished with MITE रेजिस्टरs */
	iounmap(mite_base);
	वापस 0;
पूर्ण

अटल पूर्णांक labpc_pci_स्वतः_attach(काष्ठा comedi_device *dev,
				 अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा labpc_boardinfo *board = शून्य;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(labpc_pci_boards))
		board = &labpc_pci_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	ret = labpc_pci_mite_init(pcidev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 1);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	वापस labpc_common_attach(dev, pcidev->irq, IRQF_SHARED);
पूर्ण

अटल व्योम labpc_pci_detach(काष्ठा comedi_device *dev)
अणु
	labpc_common_detach(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver labpc_pci_comedi_driver = अणु
	.driver_name	= "labpc_pci",
	.module		= THIS_MODULE,
	.स्वतः_attach	= labpc_pci_स्वतः_attach,
	.detach		= labpc_pci_detach,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id labpc_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x161), BOARD_NI_PCI1200 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, labpc_pci_table);

अटल पूर्णांक labpc_pci_probe(काष्ठा pci_dev *dev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &labpc_pci_comedi_driver,
				      id->driver_data);
पूर्ण

अटल काष्ठा pci_driver labpc_pci_driver = अणु
	.name		= "labpc_pci",
	.id_table	= labpc_pci_table,
	.probe		= labpc_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(labpc_pci_comedi_driver, labpc_pci_driver);

MODULE_DESCRIPTION("Comedi: National Instruments Lab-PC PCI-1200 driver");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
