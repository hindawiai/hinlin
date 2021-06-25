<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * uio_aec.c -- simple driver क्रम Adrienne Electronics Corp समय code PCI device
 *
 * Copyright (C) 2008 Bअक्रमon Philips <bअक्रमon@अगरup.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/slab.h>

#घोषणा PCI_VENDOR_ID_AEC 0xaecb
#घोषणा PCI_DEVICE_ID_AEC_VITCLTC 0x6250

#घोषणा INT_ENABLE_ADDR		0xFC
#घोषणा INT_ENABLE		0x10
#घोषणा INT_DISABLE		0x0

#घोषणा INT_MASK_ADDR		0x2E
#घोषणा INT_MASK_ALL		0x3F

#घोषणा INTA_DRVR_ADDR		0xFE
#घोषणा INTA_ENABLED_FLAG	0x08
#घोषणा INTA_FLAG		0x01

#घोषणा MAILBOX			0x0F

अटल काष्ठा pci_device_id ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AEC, PCI_DEVICE_ID_AEC_VITCLTC), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ids);

अटल irqवापस_t aectc_irq(पूर्णांक irq, काष्ठा uio_info *dev_info)
अणु
	व्योम __iomem *पूर्णांक_flag = dev_info->priv + INTA_DRVR_ADDR;
	अचिन्हित अक्षर status = ioपढ़ो8(पूर्णांक_flag);


	अगर ((status & INTA_ENABLED_FLAG) && (status & INTA_FLAG)) अणु
		/* application ग_लिखोs 0x00 to 0x2F to get next पूर्णांकerrupt */
		status = ioपढ़ो8(dev_info->priv + MAILBOX);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम prपूर्णांक_board_data(काष्ठा pci_dev *pdev, काष्ठा uio_info *i)
अणु
	dev_info(&pdev->dev, "PCI-TC board vendor: %x%x number: %x%x"
		" revision: %c%c\n",
		ioपढ़ो8(i->priv + 0x01),
		ioपढ़ो8(i->priv + 0x00),
		ioपढ़ो8(i->priv + 0x03),
		ioपढ़ो8(i->priv + 0x02),
		ioपढ़ो8(i->priv + 0x06),
		ioपढ़ो8(i->priv + 0x07));
पूर्ण

अटल पूर्णांक probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uio_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा uio_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर (pci_enable_device(pdev))
		वापस -ENODEV;

	अगर (pci_request_regions(pdev, "aectc"))
		जाओ out_disable;

	info->name = "aectc";
	info->port[0].start = pci_resource_start(pdev, 0);
	अगर (!info->port[0].start)
		जाओ out_release;
	info->priv = pci_iomap(pdev, 0, 0);
	अगर (!info->priv)
		जाओ out_release;
	info->port[0].size = pci_resource_len(pdev, 0);
	info->port[0].porttype = UIO_PORT_GPIO;

	info->version = "0.0.1";
	info->irq = pdev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = aectc_irq;

	prपूर्णांक_board_data(pdev, info);
	ret = uio_रेजिस्टर_device(&pdev->dev, info);
	अगर (ret)
		जाओ out_unmap;

	ioग_लिखो32(INT_ENABLE, info->priv + INT_ENABLE_ADDR);
	ioग_लिखो8(INT_MASK_ALL, info->priv + INT_MASK_ADDR);
	अगर (!(ioपढ़ो8(info->priv + INTA_DRVR_ADDR)
			& INTA_ENABLED_FLAG))
		dev_err(&pdev->dev, "aectc: interrupts not enabled\n");

	pci_set_drvdata(pdev, info);

	वापस 0;

out_unmap:
	pci_iounmap(pdev, info->priv);
out_release:
	pci_release_regions(pdev);
out_disable:
	pci_disable_device(pdev);
	वापस -ENODEV;
पूर्ण

अटल व्योम हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा uio_info *info = pci_get_drvdata(pdev);

	/* disable पूर्णांकerrupts */
	ioग_लिखो8(INT_DISABLE, info->priv + INT_MASK_ADDR);
	ioग_लिखो32(INT_DISABLE, info->priv + INT_ENABLE_ADDR);
	/* पढ़ो mailbox to ensure board drops irq */
	ioपढ़ो8(info->priv + MAILBOX);

	uio_unरेजिस्टर_device(info);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	iounmap(info->priv);
पूर्ण

अटल काष्ठा pci_driver pci_driver = अणु
	.name = "aectc",
	.id_table = ids,
	.probe = probe,
	.हटाओ = हटाओ,
पूर्ण;

module_pci_driver(pci_driver);
MODULE_LICENSE("GPL");
