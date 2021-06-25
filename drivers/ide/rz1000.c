<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1995-1998  Linus Torvalds & author (see below)
 */

/*
 *  Principal Author:  mlord@pobox.com (Mark Lord)
 *
 *  See linux/MAINTAINERS क्रम address of current मुख्यtainer.
 *
 *  This file provides support क्रम disabling the buggy पढ़ो-ahead
 *  mode of the RZ1000 IDE chipset, commonly used on Intel motherboards.
 *
 *  Dunno अगर this fixes both ports, or only the primary port (?).
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "rz1000"

अटल पूर्णांक rz1000_disable_पढ़ोahead(काष्ठा pci_dev *dev)
अणु
	u16 reg;

	अगर (!pci_पढ़ो_config_word (dev, 0x40, &reg) &&
	    !pci_ग_लिखो_config_word(dev, 0x40, reg & 0xdfff)) अणु
		prपूर्णांकk(KERN_INFO "%s: disabled chipset read-ahead "
			"(buggy RZ1000/RZ1001)\n", pci_name(dev));
		वापस 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: serialized, disabled unmasking "
			"(buggy RZ1000/RZ1001)\n", pci_name(dev));
		वापस 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ide_port_info rz1000_chipset = अणु
	.name		= DRV_NAME,
	.host_flags	= IDE_HFLAG_NO_DMA,
पूर्ण;

अटल पूर्णांक rz1000_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d = rz1000_chipset;
	पूर्णांक rc;

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	अगर (rz1000_disable_पढ़ोahead(dev)) अणु
		d.host_flags |= IDE_HFLAG_SERIALIZE;
		d.host_flags |= IDE_HFLAG_NO_UNMASK_IRQS;
	पूर्ण

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल व्योम rz1000_हटाओ(काष्ठा pci_dev *dev)
अणु
	ide_pci_हटाओ(dev);
	pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id rz1000_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_RZ1000), 0 पूर्ण,
	अणु PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_RZ1001), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, rz1000_pci_tbl);

अटल काष्ठा pci_driver rz1000_pci_driver = अणु
	.name		= "RZ1000_IDE",
	.id_table	= rz1000_pci_tbl,
	.probe		= rz1000_init_one,
	.हटाओ		= rz1000_हटाओ,
पूर्ण;

अटल पूर्णांक __init rz1000_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&rz1000_pci_driver);
पूर्ण

अटल व्योम __निकास rz1000_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&rz1000_pci_driver);
पूर्ण

module_init(rz1000_ide_init);
module_निकास(rz1000_ide_निकास);

MODULE_AUTHOR("Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for RZ1000 IDE");
MODULE_LICENSE("GPL");

