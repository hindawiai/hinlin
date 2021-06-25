<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UIO Hilscher CIF card driver
 *
 * (C) 2007 Hans J. Koch <hjk@hansjkoch.de>
 * Original code (C) 2005 Benedikt Spranger <b.spranger@linutronix.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uio_driver.h>

#समावेश <यंत्र/पन.स>

#घोषणा PLX9030_INTCSR		0x4C
#घोषणा INTSCR_INT1_ENABLE	0x01
#घोषणा INTSCR_INT1_STATUS	0x04
#घोषणा INT1_ENABLED_AND_ACTIVE	(INTSCR_INT1_ENABLE | INTSCR_INT1_STATUS)

#घोषणा PCI_SUBVENDOR_ID_PEP	0x1518
#घोषणा CIF_SUBDEVICE_PROFIBUS	0x430
#घोषणा CIF_SUBDEVICE_DEVICENET	0x432


अटल irqवापस_t hilscher_handler(पूर्णांक irq, काष्ठा uio_info *dev_info)
अणु
	व्योम __iomem *plx_पूर्णांकscr = dev_info->mem[0].पूर्णांकernal_addr
					+ PLX9030_INTCSR;

	अगर ((ioपढ़ो8(plx_पूर्णांकscr) & INT1_ENABLED_AND_ACTIVE)
	    != INT1_ENABLED_AND_ACTIVE)
		वापस IRQ_NONE;

	/* Disable पूर्णांकerrupt */
	ioग_लिखो8(ioपढ़ो8(plx_पूर्णांकscr) & ~INTSCR_INT1_ENABLE, plx_पूर्णांकscr);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hilscher_pci_probe(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uio_info *info;

	info = devm_kzalloc(&dev->dev, माप(काष्ठा uio_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर (pci_enable_device(dev))
		वापस -ENODEV;

	अगर (pci_request_regions(dev, "hilscher"))
		जाओ out_disable;

	info->mem[0].addr = pci_resource_start(dev, 0);
	अगर (!info->mem[0].addr)
		जाओ out_release;
	info->mem[0].पूर्णांकernal_addr = pci_ioremap_bar(dev, 0);
	अगर (!info->mem[0].पूर्णांकernal_addr)
		जाओ out_release;

	info->mem[0].size = pci_resource_len(dev, 0);
	info->mem[0].memtype = UIO_MEM_PHYS;
	info->mem[1].addr = pci_resource_start(dev, 2);
	info->mem[1].size = pci_resource_len(dev, 2);
	info->mem[1].memtype = UIO_MEM_PHYS;
	चयन (id->subdevice) अणु
		हाल CIF_SUBDEVICE_PROFIBUS:
			info->name = "CIF_Profibus";
			अवरोध;
		हाल CIF_SUBDEVICE_DEVICENET:
			info->name = "CIF_Devicenet";
			अवरोध;
		शेष:
			info->name = "CIF_???";
	पूर्ण
	info->version = "0.0.1";
	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = hilscher_handler;

	अगर (uio_रेजिस्टर_device(&dev->dev, info))
		जाओ out_unmap;

	pci_set_drvdata(dev, info);

	वापस 0;
out_unmap:
	iounmap(info->mem[0].पूर्णांकernal_addr);
out_release:
	pci_release_regions(dev);
out_disable:
	pci_disable_device(dev);
	वापस -ENODEV;
पूर्ण

अटल व्योम hilscher_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा uio_info *info = pci_get_drvdata(dev);

	uio_unरेजिस्टर_device(info);
	pci_release_regions(dev);
	pci_disable_device(dev);
	iounmap(info->mem[0].पूर्णांकernal_addr);
पूर्ण

अटल काष्ठा pci_device_id hilscher_pci_ids[] = अणु
	अणु
		.venकरोr =	PCI_VENDOR_ID_PLX,
		.device =	PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =	PCI_SUBVENDOR_ID_PEP,
		.subdevice =	CIF_SUBDEVICE_PROFIBUS,
	पूर्ण,
	अणु
		.venकरोr =	PCI_VENDOR_ID_PLX,
		.device =	PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =	PCI_SUBVENDOR_ID_PEP,
		.subdevice =	CIF_SUBDEVICE_DEVICENET,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver hilscher_pci_driver = अणु
	.name = "hilscher",
	.id_table = hilscher_pci_ids,
	.probe = hilscher_pci_probe,
	.हटाओ = hilscher_pci_हटाओ,
पूर्ण;

module_pci_driver(hilscher_pci_driver);
MODULE_DEVICE_TABLE(pci, hilscher_pci_ids);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Hans J. Koch, Benedikt Spranger");
