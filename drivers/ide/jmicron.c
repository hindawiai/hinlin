<शैली गुरु>

/*
 * Copyright (C) 2006		Red Hat
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "jmicron"

प्रकार क्रमागत अणु
	PORT_PATA0 = 0,
	PORT_PATA1 = 1,
	PORT_SATA = 2,
पूर्ण port_type;

/**
 *	jmicron_cable_detect	-	cable detection
 *	@hwअगर: IDE port
 *
 *	Returns the cable type.
 */

अटल u8 jmicron_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);

	u32 control;
	u32 control5;

	पूर्णांक port = hwअगर->channel;
	port_type port_map[2];

	pci_पढ़ो_config_dword(pdev, 0x40, &control);

	/* There are two basic mappings. One has the two SATA ports merged
	   as master/slave and the secondary as PATA, the other has only the
	   SATA port mapped */
	अगर (control & (1 << 23)) अणु
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_PATA0;
	पूर्ण अन्यथा अणु
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_SATA;
	पूर्ण

	/* The 365/366 may have this bit set to map the second PATA port
	   as the पूर्णांकernal primary channel */
	pci_पढ़ो_config_dword(pdev, 0x80, &control5);
	अगर (control5 & (1<<24))
		port_map[0] = PORT_PATA1;

	/* The two ports may then be logically swapped by the firmware */
	अगर (control & (1 << 22))
		port = port ^ 1;

	/*
	 *	Now we know which physical port we are talking about we can
	 *	actually करो our cable checking etc. Thankfully we करोn't need
	 *	to करो the plumbing क्रम other हालs.
	 */
	चयन (port_map[port]) अणु
	हाल PORT_PATA0:
		अगर (control & (1 << 3))	/* 40/80 pin primary */
			वापस ATA_CBL_PATA40;
		वापस ATA_CBL_PATA80;
	हाल PORT_PATA1:
		अगर (control5 & (1 << 19))	/* 40/80 pin secondary */
			वापस ATA_CBL_PATA40;
		वापस ATA_CBL_PATA80;
	हाल PORT_SATA:
		अवरोध;
	पूर्ण
	/* Aव्योम bogus "control reaches end of non-void function" */
	वापस ATA_CBL_PATA80;
पूर्ण

अटल व्योम jmicron_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
पूर्ण

/**
 *	jmicron_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	As the JMicron snoops क्रम timings we करोn't need to करो anything here.
 */

अटल व्योम jmicron_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
पूर्ण

अटल स्थिर काष्ठा ide_port_ops jmicron_port_ops = अणु
	.set_pio_mode		= jmicron_set_pio_mode,
	.set_dma_mode		= jmicron_set_dma_mode,
	.cable_detect		= jmicron_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info jmicron_chipset = अणु
	.name		= DRV_NAME,
	.enablebits	= अणु अणु 0x40, 0x01, 0x01 पूर्ण, अणु 0x40, 0x10, 0x10 पूर्ण पूर्ण,
	.port_ops	= &jmicron_port_ops,
	.pio_mask	= ATA_PIO5,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
पूर्ण;

/**
 *	jmicron_init_one	-	pci layer discovery entry
 *	@dev: PCI device
 *	@id: ident table entry
 *
 *	Called by the PCI code when it finds a Jmicron controller.
 *	We then use the IDE PCI generic helper to करो most of the work.
 */

अटल पूर्णांक jmicron_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &jmicron_chipset, शून्य);
पूर्ण

/* All JMB PATA controllers have and will जारी to have the same
 * पूर्णांकerface.  Matching venकरोr and device class is enough क्रम all
 * current and future controllers अगर the controller is programmed
 * properly.
 *
 * If libata is configured, jmicron PCI quirk programs the controller
 * पूर्णांकo the correct mode.  If libata isn't configured, match known
 * device IDs too to मुख्यtain backward compatibility.
 */
अटल काष्ठा pci_device_id jmicron_pci_tbl[] = अणु
#अगर !defined(CONFIG_ATA) && !defined(CONFIG_ATA_MODULE)
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB361) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB363) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB365) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB366) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMB368) पूर्ण,
#पूर्ण_अगर
	अणु PCI_VENDOR_ID_JMICRON, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_IDE << 8, 0xffff00, 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, jmicron_pci_tbl);

अटल काष्ठा pci_driver jmicron_pci_driver = अणु
	.name		= "JMicron IDE",
	.id_table	= jmicron_pci_tbl,
	.probe		= jmicron_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init jmicron_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&jmicron_pci_driver);
पूर्ण

अटल व्योम __निकास jmicron_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&jmicron_pci_driver);
पूर्ण

module_init(jmicron_ide_init);
module_निकास(jmicron_ide_निकास);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("PCI driver module for the JMicron in legacy modes");
MODULE_LICENSE("GPL");
