<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UIO driver क्रम Hilscher NetX based fieldbus cards (cअगरX, comX).
 * See http://www.hilscher.com क्रम details.
 *
 * (C) 2007 Hans J. Koch <hjk@hansjkoch.de>
 * (C) 2008 Manuel Traut <manut@linutronix.de>
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uio_driver.h>

#घोषणा PCI_VENDOR_ID_HILSCHER		0x15CF
#घोषणा PCI_DEVICE_ID_HILSCHER_NETX	0x0000
#घोषणा PCI_DEVICE_ID_HILSCHER_NETPLC	0x0010
#घोषणा PCI_SUBDEVICE_ID_NETPLC_RAM	0x0000
#घोषणा PCI_SUBDEVICE_ID_NETPLC_FLASH	0x0001
#घोषणा PCI_SUBDEVICE_ID_NXSB_PCA	0x3235
#घोषणा PCI_SUBDEVICE_ID_NXPCA		0x3335

#घोषणा DPM_HOST_INT_EN0	0xfff0
#घोषणा DPM_HOST_INT_STAT0	0xffe0

#घोषणा DPM_HOST_INT_MASK	0xe600ffff
#घोषणा DPM_HOST_INT_GLOBAL_EN	0x80000000

अटल irqवापस_t netx_handler(पूर्णांक irq, काष्ठा uio_info *dev_info)
अणु
	व्योम __iomem *पूर्णांक_enable_reg = dev_info->mem[0].पूर्णांकernal_addr
					+ DPM_HOST_INT_EN0;
	व्योम __iomem *पूर्णांक_status_reg = dev_info->mem[0].पूर्णांकernal_addr
					+ DPM_HOST_INT_STAT0;

	/* Is one of our पूर्णांकerrupts enabled and active ? */
	अगर (!(ioपढ़ो32(पूर्णांक_enable_reg) & ioपढ़ो32(पूर्णांक_status_reg)
		& DPM_HOST_INT_MASK))
		वापस IRQ_NONE;

	/* Disable पूर्णांकerrupt */
	ioग_लिखो32(ioपढ़ो32(पूर्णांक_enable_reg) & ~DPM_HOST_INT_GLOBAL_EN,
		पूर्णांक_enable_reg);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक netx_pci_probe(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uio_info *info;
	पूर्णांक bar;

	info = devm_kzalloc(&dev->dev, माप(काष्ठा uio_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर (pci_enable_device(dev))
		वापस -ENODEV;

	अगर (pci_request_regions(dev, "netx"))
		जाओ out_disable;

	चयन (id->device) अणु
	हाल PCI_DEVICE_ID_HILSCHER_NETX:
		bar = 0;
		info->name = "netx";
		अवरोध;
	हाल PCI_DEVICE_ID_HILSCHER_NETPLC:
		bar = 0;
		info->name = "netplc";
		अवरोध;
	शेष:
		bar = 2;
		info->name = "netx_plx";
	पूर्ण

	/* BAR0 or 2 poपूर्णांकs to the card's dual port memory */
	info->mem[0].addr = pci_resource_start(dev, bar);
	अगर (!info->mem[0].addr)
		जाओ out_release;
	info->mem[0].पूर्णांकernal_addr = ioremap(pci_resource_start(dev, bar),
						pci_resource_len(dev, bar));

	अगर (!info->mem[0].पूर्णांकernal_addr)
			जाओ out_release;

	info->mem[0].size = pci_resource_len(dev, bar);
	info->mem[0].memtype = UIO_MEM_PHYS;
	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = netx_handler;
	info->version = "0.0.1";

	/* Make sure all पूर्णांकerrupts are disabled */
	ioग_लिखो32(0, info->mem[0].पूर्णांकernal_addr + DPM_HOST_INT_EN0);

	अगर (uio_रेजिस्टर_device(&dev->dev, info))
		जाओ out_unmap;

	pci_set_drvdata(dev, info);
	dev_info(&dev->dev, "Found %s card, registered UIO device.\n",
				info->name);

	वापस 0;

out_unmap:
	iounmap(info->mem[0].पूर्णांकernal_addr);
out_release:
	pci_release_regions(dev);
out_disable:
	pci_disable_device(dev);
	वापस -ENODEV;
पूर्ण

अटल व्योम netx_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा uio_info *info = pci_get_drvdata(dev);

	/* Disable all पूर्णांकerrupts */
	ioग_लिखो32(0, info->mem[0].पूर्णांकernal_addr + DPM_HOST_INT_EN0);
	uio_unरेजिस्टर_device(info);
	pci_release_regions(dev);
	pci_disable_device(dev);
	iounmap(info->mem[0].पूर्णांकernal_addr);
पूर्ण

अटल काष्ठा pci_device_id netx_pci_ids[] = अणु
	अणु
		.venकरोr =	PCI_VENDOR_ID_HILSCHER,
		.device =	PCI_DEVICE_ID_HILSCHER_NETX,
		.subvenकरोr =	0,
		.subdevice =	0,
	पूर्ण,
	अणु
		.venकरोr =       PCI_VENDOR_ID_HILSCHER,
		.device =       PCI_DEVICE_ID_HILSCHER_NETPLC,
		.subvenकरोr =    PCI_VENDOR_ID_HILSCHER,
		.subdevice =    PCI_SUBDEVICE_ID_NETPLC_RAM,
	पूर्ण,
	अणु
		.venकरोr =       PCI_VENDOR_ID_HILSCHER,
		.device =       PCI_DEVICE_ID_HILSCHER_NETPLC,
		.subvenकरोr =    PCI_VENDOR_ID_HILSCHER,
		.subdevice =    PCI_SUBDEVICE_ID_NETPLC_FLASH,
	पूर्ण,
	अणु
		.venकरोr =	PCI_VENDOR_ID_PLX,
		.device =	PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =	PCI_VENDOR_ID_PLX,
		.subdevice =	PCI_SUBDEVICE_ID_NXSB_PCA,
	पूर्ण,
	अणु
		.venकरोr =	PCI_VENDOR_ID_PLX,
		.device =	PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =	PCI_VENDOR_ID_PLX,
		.subdevice =	PCI_SUBDEVICE_ID_NXPCA,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver netx_pci_driver = अणु
	.name = "netx",
	.id_table = netx_pci_ids,
	.probe = netx_pci_probe,
	.हटाओ = netx_pci_हटाओ,
पूर्ण;

module_pci_driver(netx_pci_driver);
MODULE_DEVICE_TABLE(pci, netx_pci_ids);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Hans J. Koch, Manuel Traut");
