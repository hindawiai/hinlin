<शैली गुरु>
/*
 *  Copyright (C) 2001-2002	Andre Hedrick <andre@linux-ide.org>
 *  Portions (C) Copyright 2002  Red Hat Inc
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * For the aव्योमance of करोubt the "preferred form" of this code is one which
 * is in an खोलो non patent encumbered क्रमmat. Where cryptographic key signing
 * क्रमms part of the process of creating an executable the inक्रमmation
 * including keys needed to generate an equivalently functional executable
 * are deemed to be part of the source code.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "ide_pci_generic"

अटल bool ide_generic_all;		/* Set to claim all devices */

module_param_named(all_generic_ide, ide_generic_all, bool, 0444);
MODULE_PARM_DESC(all_generic_ide, "IDE generic will claim all unknown PCI IDE storage controllers.");

अटल व्योम netcell_quirkproc(ide_drive_t *drive)
अणु
	/* mark words 85-87 as valid */
	drive->id[ATA_ID_CSF_DEFAULT] |= 0x4000;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops netcell_port_ops = अणु
	.quirkproc		= netcell_quirkproc,
पूर्ण;

#घोषणा DECLARE_GENERIC_PCI_DEV(extra_flags) \
	अणु \
		.name		= DRV_NAME, \
		.host_flags	= IDE_HFLAG_TRUST_BIOS_FOR_DMA | \
				  extra_flags, \
		.swdma_mask	= ATA_SWDMA2, \
		.mwdma_mask	= ATA_MWDMA2, \
		.udma_mask	= ATA_UDMA6, \
	पूर्ण

अटल स्थिर काष्ठा ide_port_info generic_chipsets[] = अणु
	/*  0: Unknown */
	DECLARE_GENERIC_PCI_DEV(0),

	अणु	/* 1: NS87410 */
		.name		= DRV_NAME,
		.enablebits	= अणु अणु0x43, 0x08, 0x08पूर्ण, अणु0x47, 0x08, 0x08पूर्ण पूर्ण,
		.host_flags	= IDE_HFLAG_TRUST_BIOS_FOR_DMA,
		.swdma_mask	= ATA_SWDMA2,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
	पूर्ण,

	/*  2: SAMURAI / HT6565 / HINT_IDE */
	DECLARE_GENERIC_PCI_DEV(0),
	/*  3: UM8673F / UM8886A / UM8886BF */
	DECLARE_GENERIC_PCI_DEV(IDE_HFLAG_NO_DMA),
	/*  4: VIA_IDE / OPTI621V / Piccolo010अणु2,3,5पूर्ण */
	DECLARE_GENERIC_PCI_DEV(IDE_HFLAG_NO_AUTODMA),

	अणु	/* 5: VIA8237SATA */
		.name		= DRV_NAME,
		.host_flags	= IDE_HFLAG_TRUST_BIOS_FOR_DMA |
				  IDE_HFLAG_OFF_BOARD,
		.swdma_mask	= ATA_SWDMA2,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
	पूर्ण,

	अणु	/* 6: Revolution */
		.name		= DRV_NAME,
		.port_ops	= &netcell_port_ops,
		.host_flags	= IDE_HFLAG_CLEAR_SIMPLEX |
				  IDE_HFLAG_TRUST_BIOS_FOR_DMA |
				  IDE_HFLAG_OFF_BOARD,
		.swdma_mask	= ATA_SWDMA2,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
	पूर्ण
पूर्ण;

/**
 *	generic_init_one	-	called when a PIIX is found
 *	@dev: the generic device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */

अटल पूर्णांक generic_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा ide_port_info *d = &generic_chipsets[id->driver_data];
	पूर्णांक ret = -ENODEV;

	/* Don't use the generic entry unless inकाष्ठाed to करो so */
	अगर (id->driver_data == 0 && ide_generic_all == 0)
			जाओ out;

	चयन (dev->venकरोr) अणु
	हाल PCI_VENDOR_ID_UMC:
		अगर (dev->device == PCI_DEVICE_ID_UMC_UM8886A &&
				!(PCI_FUNC(dev->devfn) & 1))
			जाओ out; /* UM8886A/BF pair */
		अवरोध;
	हाल PCI_VENDOR_ID_OPTI:
		अगर (dev->device == PCI_DEVICE_ID_OPTI_82C558 &&
				!(PCI_FUNC(dev->devfn) & 1))
			जाओ out;
		अवरोध;
	हाल PCI_VENDOR_ID_JMICRON:
		अगर (dev->device != PCI_DEVICE_ID_JMICRON_JMB368 &&
				PCI_FUNC(dev->devfn) != 1)
			जाओ out;
		अवरोध;
	हाल PCI_VENDOR_ID_NS:
		अगर (dev->device == PCI_DEVICE_ID_NS_87410 &&
				(dev->class >> 8) != PCI_CLASS_STORAGE_IDE)
			जाओ out;
		अवरोध;
	पूर्ण

	अगर (dev->venकरोr != PCI_VENDOR_ID_JMICRON) अणु
		u16 command;
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
		अगर (!(command & PCI_COMMAND_IO)) अणु
			prपूर्णांकk(KERN_INFO "%s %s: skipping disabled "
				"controller\n", d->name, pci_name(dev));
			जाओ out;
		पूर्ण
	पूर्ण
	ret = ide_pci_init_one(dev, d, शून्य);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id generic_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NS,	PCI_DEVICE_ID_NS_87410),		 1 पूर्ण,
	अणु PCI_VDEVICE(PCTECH,	PCI_DEVICE_ID_PCTECH_SAMURAI_IDE),	 2 पूर्ण,
	अणु PCI_VDEVICE(HOLTEK,	PCI_DEVICE_ID_HOLTEK_6565),		 2 पूर्ण,
	अणु PCI_VDEVICE(UMC,	PCI_DEVICE_ID_UMC_UM8673F),		 3 पूर्ण,
	अणु PCI_VDEVICE(UMC,	PCI_DEVICE_ID_UMC_UM8886A),		 3 पूर्ण,
	अणु PCI_VDEVICE(UMC,	PCI_DEVICE_ID_UMC_UM8886BF),		 3 पूर्ण,
	अणु PCI_VDEVICE(HINT,	PCI_DEVICE_ID_HINT_VXPROII_IDE),	 2 पूर्ण,
	अणु PCI_VDEVICE(VIA,	PCI_DEVICE_ID_VIA_82C561),		 4 पूर्ण,
	अणु PCI_VDEVICE(OPTI,	PCI_DEVICE_ID_OPTI_82C558),		 4 पूर्ण,
#अगर_घोषित CONFIG_BLK_DEV_IDE_SATA
	अणु PCI_VDEVICE(VIA,	PCI_DEVICE_ID_VIA_8237_SATA),		 5 पूर्ण,
#पूर्ण_अगर
	अणु PCI_VDEVICE(TOSHIBA,	PCI_DEVICE_ID_TOSHIBA_PICCOLO_1),	 4 पूर्ण,
	अणु PCI_VDEVICE(TOSHIBA,	PCI_DEVICE_ID_TOSHIBA_PICCOLO_2),	 4 पूर्ण,
	अणु PCI_VDEVICE(TOSHIBA,	PCI_DEVICE_ID_TOSHIBA_PICCOLO_3),	 4 पूर्ण,
	अणु PCI_VDEVICE(TOSHIBA,	PCI_DEVICE_ID_TOSHIBA_PICCOLO_5),	 4 पूर्ण,
	अणु PCI_VDEVICE(NETCELL,	PCI_DEVICE_ID_REVOLUTION),		 6 पूर्ण,
	/*
	 * Must come last.  If you add entries adjust
	 * this table and generic_chipsets[] appropriately.
	 */
	अणु PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_STORAGE_IDE << 8, 0xFFFFFF00UL, 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, generic_pci_tbl);

अटल काष्ठा pci_driver generic_pci_driver = अणु
	.name		= "PCI_IDE",
	.id_table	= generic_pci_tbl,
	.probe		= generic_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init generic_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&generic_pci_driver);
पूर्ण

अटल व्योम __निकास generic_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&generic_pci_driver);
पूर्ण

module_init(generic_ide_init);
module_निकास(generic_ide_निकास);

MODULE_AUTHOR("Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for generic PCI IDE");
MODULE_LICENSE("GPL");
