<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1998-2000 Michel Aubry
 * Copyright (C) 1998-2000 Andrzej Krzysztofowicz
 * Copyright (C) 1998-2000 Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2007-2010 Bartlomiej Zolnierkiewicz
 * Portions copyright (c) 2001 Sun Microप्रणालीs
 *
 *
 * RCC/ServerWorks IDE driver क्रम Linux
 *
 *   OSB4: `Open South Bridge' IDE Interface (fn 1)
 *         supports UDMA mode 2 (33 MB/s)
 *
 *   CSB5: `Champion South Bridge' IDE Interface (fn 1)
 *         all revisions support UDMA mode 4 (66 MB/s)
 *         revision A2.0 and up support UDMA mode 5 (100 MB/s)
 *
 *         *** The CSB5 करोes not provide ANY रेजिस्टर ***
 *         *** to detect 80-conductor cable presence. ***
 *
 *   CSB6: `Champion South Bridge' IDE Interface (optional: third channel)
 *
 *   HT1000: AKA BCM5785 - Hypertransport Southbridge क्रम Opteron प्रणालीs. IDE
 *   controller same as the CSB6. Single channel ATA100 only.
 *
 * Documentation:
 *	Available under NDA only. Errata info very hard to get.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "serverworks"

#घोषणा SVWKS_CSB5_REVISION_NEW	0x92 /* min PCI_REVISION_ID क्रम UDMA5 (A2.0) */
#घोषणा SVWKS_CSB6_REVISION	0xa0 /* min PCI_REVISION_ID क्रम UDMA4 (A1.0) */

/* Seagate Barracuda ATA IV Family drives in UDMA mode 5
 * can overrun their FIFOs when used with the CSB5 */
अटल स्थिर अक्षर *svwks_bad_ata100[] = अणु
	"ST320011A",
	"ST340016A",
	"ST360021A",
	"ST380021A",
	शून्य
पूर्ण;

अटल पूर्णांक check_in_drive_lists (ide_drive_t *drive, स्थिर अक्षर **list)
अणु
	अक्षर *m = (अक्षर *)&drive->id[ATA_ID_PROD];

	जबतक (*list)
		अगर (!म_भेद(*list++, m))
			वापस 1;
	वापस 0;
पूर्ण

अटल u8 svwks_udma_filter(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);

	अगर (dev->device == PCI_DEVICE_ID_SERVERWORKS_HT1000IDE) अणु
		वापस 0x1f;
	पूर्ण अन्यथा अगर (dev->revision < SVWKS_CSB5_REVISION_NEW) अणु
		वापस 0x07;
	पूर्ण अन्यथा अणु
		u8 btr = 0, mode, mask;

		pci_पढ़ो_config_byte(dev, 0x5A, &btr);
		mode = btr & 0x3;

		/* If someone decides to करो UDMA133 on CSB5 the same
		   issue will bite so be inclusive */
		अगर (mode > 2 && check_in_drive_lists(drive, svwks_bad_ata100))
			mode = 2;

		चयन(mode) अणु
		हाल 3:	 mask = 0x3f; अवरोध;
		हाल 2:	 mask = 0x1f; अवरोध;
		हाल 1:	 mask = 0x07; अवरोध;
		शेष: mask = 0x00; अवरोध;
		पूर्ण

		वापस mask;
	पूर्ण
पूर्ण

अटल u8 svwks_csb_check (काष्ठा pci_dev *dev)
अणु
	चयन (dev->device) अणु
		हाल PCI_DEVICE_ID_SERVERWORKS_CSB5IDE:
		हाल PCI_DEVICE_ID_SERVERWORKS_CSB6IDE:
		हाल PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2:
		हाल PCI_DEVICE_ID_SERVERWORKS_HT1000IDE:
			वापस 1;
		शेष:
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम svwks_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल स्थिर u8 pio_modes[] = अणु 0x5d, 0x47, 0x34, 0x22, 0x20 पूर्ण;
	अटल स्थिर u8 drive_pci[] = अणु 0x41, 0x40, 0x43, 0x42 पूर्ण;

	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	अगर (drive->dn >= ARRAY_SIZE(drive_pci))
		वापस;

	pci_ग_लिखो_config_byte(dev, drive_pci[drive->dn], pio_modes[pio]);

	अगर (svwks_csb_check(dev)) अणु
		u16 csb_pio = 0;

		pci_पढ़ो_config_word(dev, 0x4a, &csb_pio);

		csb_pio &= ~(0x0f << (4 * drive->dn));
		csb_pio |= (pio << (4 * drive->dn));

		pci_ग_लिखो_config_word(dev, 0x4a, csb_pio);
	पूर्ण
पूर्ण

अटल व्योम svwks_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल स्थिर u8 udma_modes[]		= अणु 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 पूर्ण;
	अटल स्थिर u8 dma_modes[]		= अणु 0x77, 0x21, 0x20 पूर्ण;
	अटल स्थिर u8 drive_pci2[]		= अणु 0x45, 0x44, 0x47, 0x46 पूर्ण;

	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	स्थिर u8 speed		= drive->dma_mode;
	u8 unit			= drive->dn & 1;

	u8 ultra_enable	 = 0, ultra_timing = 0, dma_timing = 0;

	अगर (drive->dn >= ARRAY_SIZE(drive_pci2))
		वापस;

	pci_पढ़ो_config_byte(dev, (0x56|hwअगर->channel), &ultra_timing);
	pci_पढ़ो_config_byte(dev, 0x54, &ultra_enable);

	ultra_timing	&= ~(0x0F << (4*unit));
	ultra_enable	&= ~(0x01 << drive->dn);

	अगर (speed >= XFER_UDMA_0) अणु
		dma_timing   |= dma_modes[2];
		ultra_timing |= (udma_modes[speed - XFER_UDMA_0] << (4 * unit));
		ultra_enable |= (0x01 << drive->dn);
	पूर्ण अन्यथा अगर (speed >= XFER_MW_DMA_0)
		dma_timing   |= dma_modes[speed - XFER_MW_DMA_0];

	pci_ग_लिखो_config_byte(dev, drive_pci2[drive->dn], dma_timing);
	pci_ग_लिखो_config_byte(dev, (0x56|hwअगर->channel), ultra_timing);
	pci_ग_लिखो_config_byte(dev, 0x54, ultra_enable);
पूर्ण

अटल पूर्णांक init_chipset_svwks(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक reg;
	u8 btr;

	/* क्रमce Master Latency Timer value to 64 PCICLKs */
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x40);

	/* OSB4 : South Bridge and IDE */
	अगर (dev->device == PCI_DEVICE_ID_SERVERWORKS_OSB4IDE) अणु
		काष्ठा pci_dev *isa_dev =
			pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
					PCI_DEVICE_ID_SERVERWORKS_OSB4, शून्य);
		अगर (isa_dev) अणु
			pci_पढ़ो_config_dword(isa_dev, 0x64, &reg);
			reg &= ~0x00002000; /* disable 600ns पूर्णांकerrupt mask */
			अगर(!(reg & 0x00004000))
				prपूर्णांकk(KERN_DEBUG DRV_NAME " %s: UDMA not BIOS "
					"enabled.\n", pci_name(dev));
			reg |=  0x00004000; /* enable UDMA/33 support */
			pci_ग_लिखो_config_dword(isa_dev, 0x64, reg);
			pci_dev_put(isa_dev);
		पूर्ण
	पूर्ण

	/* setup CSB5/CSB6 : South Bridge and IDE option RAID */
	अन्यथा अगर ((dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5IDE) ||
		 (dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE) ||
		 (dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2)) अणु

		/* Third Channel Test */
		अगर (!(PCI_FUNC(dev->devfn) & 1)) अणु
			काष्ठा pci_dev * findev = शून्य;
			u32 reg4c = 0;
			findev = pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
				PCI_DEVICE_ID_SERVERWORKS_CSB5, शून्य);
			अगर (findev) अणु
				pci_पढ़ो_config_dword(findev, 0x4C, &reg4c);
				reg4c &= ~0x000007FF;
				reg4c |=  0x00000040;
				reg4c |=  0x00000020;
				pci_ग_लिखो_config_dword(findev, 0x4C, reg4c);
				pci_dev_put(findev);
			पूर्ण
			outb_p(0x06, 0x0c00);
			dev->irq = inb_p(0x0c01);
		पूर्ण अन्यथा अणु
			काष्ठा pci_dev * findev = शून्य;
			u8 reg41 = 0;

			findev = pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
					PCI_DEVICE_ID_SERVERWORKS_CSB6, शून्य);
			अगर (findev) अणु
				pci_पढ़ो_config_byte(findev, 0x41, &reg41);
				reg41 &= ~0x40;
				pci_ग_लिखो_config_byte(findev, 0x41, reg41);
				pci_dev_put(findev);
			पूर्ण
			/*
			 * This is a device pin issue on CSB6.
			 * Since there will be a future raid mode,
			 * early versions of the chipset require the
			 * पूर्णांकerrupt pin to be set, and it is a compatibility
			 * mode issue.
			 */
			अगर ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE)
				dev->irq = 0;
		पूर्ण
//		pci_पढ़ो_config_dword(dev, 0x40, &pioreg)
//		pci_ग_लिखो_config_dword(dev, 0x40, 0x99999999);
//		pci_पढ़ो_config_dword(dev, 0x44, &dmareg);
//		pci_ग_लिखो_config_dword(dev, 0x44, 0xFFFFFFFF);
		/* setup the UDMA Control रेजिस्टर
		 *
		 * 1. clear bit 6 to enable DMA
		 * 2. enable DMA modes with bits 0-1
		 * 	00 : legacy
		 * 	01 : udma2
		 * 	10 : udma2/udma4
		 * 	11 : udma2/udma4/udma5
		 */
		pci_पढ़ो_config_byte(dev, 0x5A, &btr);
		btr &= ~0x40;
		अगर (!(PCI_FUNC(dev->devfn) & 1))
			btr |= 0x2;
		अन्यथा
			btr |= (dev->revision >= SVWKS_CSB5_REVISION_NEW) ? 0x3 : 0x2;
		pci_ग_लिखो_config_byte(dev, 0x5A, btr);
	पूर्ण
	/* Setup HT1000 SouthBridge Controller - Single Channel Only */
	अन्यथा अगर (dev->device == PCI_DEVICE_ID_SERVERWORKS_HT1000IDE) अणु
		pci_पढ़ो_config_byte(dev, 0x5A, &btr);
		btr &= ~0x40;
		btr |= 0x3;
		pci_ग_लिखो_config_byte(dev, 0x5A, btr);
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 ata66_svwks_svwks(ide_hwअगर_t *hwअगर)
अणु
	वापस ATA_CBL_PATA80;
पूर्ण

/* On Dell PowerEdge servers with a CSB5/CSB6, the top two bits
 * of the subप्रणाली device ID indicate presence of an 80-pin cable.
 * Bit 15 clear = secondary IDE channel करोes not have 80-pin cable.
 * Bit 15 set   = secondary IDE channel has 80-pin cable.
 * Bit 14 clear = primary IDE channel करोes not have 80-pin cable.
 * Bit 14 set   = primary IDE channel has 80-pin cable.
 */
अटल u8 ata66_svwks_dell(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL &&
	    dev->venकरोr	== PCI_VENDOR_ID_SERVERWORKS &&
	    (dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5IDE ||
	     dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE))
		वापस ((1 << (hwअगर->channel + 14)) &
			dev->subप्रणाली_device) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
	वापस ATA_CBL_PATA40;
पूर्ण

/* Sun Cobalt Alpine hardware aव्योमs the 80-pin cable
 * detect issue by attaching the drives directly to the board.
 * This check follows the Dell precedent (how scary is that?!)
 *
 * WARNING: this only works on Alpine hardware!
 */
अटल u8 ata66_svwks_cobalt(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SUN &&
	    dev->venकरोr	== PCI_VENDOR_ID_SERVERWORKS &&
	    dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5IDE)
		वापस ((1 << (hwअगर->channel + 14)) &
			dev->subप्रणाली_device) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
	वापस ATA_CBL_PATA40;
पूर्ण

अटल u8 svwks_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	/* Server Works */
	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SERVERWORKS)
		वापस ata66_svwks_svwks (hwअगर);
	
	/* Dell PowerEdge */
	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL)
		वापस ata66_svwks_dell (hwअगर);

	/* Cobalt Alpine */
	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SUN)
		वापस ata66_svwks_cobalt (hwअगर);

	/* Per Specअगरied Design by OEM, and ASIC Architect */
	अगर ((dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE) ||
	    (dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2))
		वापस ATA_CBL_PATA80;

	वापस ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops osb4_port_ops = अणु
	.set_pio_mode		= svwks_set_pio_mode,
	.set_dma_mode		= svwks_set_dma_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops svwks_port_ops = अणु
	.set_pio_mode		= svwks_set_pio_mode,
	.set_dma_mode		= svwks_set_dma_mode,
	.udma_filter		= svwks_udma_filter,
	.cable_detect		= svwks_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info serverworks_chipsets[] = अणु
	अणु	/* 0: OSB4 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_svwks,
		.port_ops	= &osb4_port_ops,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= 0x00, /* UDMA is problematic on OSB4 */
	पूर्ण,
	अणु	/* 1: CSB5 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_svwks,
		.port_ops	= &svwks_port_ops,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण,
	अणु	/* 2: CSB6 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_svwks,
		.port_ops	= &svwks_port_ops,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण,
	अणु	/* 3: CSB6-2 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_svwks,
		.port_ops	= &svwks_port_ops,
		.host_flags	= IDE_HFLAG_SINGLE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण,
	अणु	/* 4: HT1000 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_svwks,
		.port_ops	= &svwks_port_ops,
		.host_flags	= IDE_HFLAG_SINGLE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण
पूर्ण;

/**
 *	svwks_init_one	-	called when a OSB/CSB is found
 *	@dev: the svwks device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */
 
अटल पूर्णांक svwks_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d;
	u8 idx = id->driver_data;

	d = serverworks_chipsets[idx];

	अगर (idx == 1)
		d.host_flags |= IDE_HFLAG_CLEAR_SIMPLEX;
	अन्यथा अगर (idx == 2 || idx == 3) अणु
		अगर ((PCI_FUNC(dev->devfn) & 1) == 0) अणु
			अगर (pci_resource_start(dev, 0) != 0x01f1)
				d.host_flags |= IDE_HFLAG_NON_BOOTABLE;
			d.host_flags |= IDE_HFLAG_SINGLE;
		पूर्ण अन्यथा
			d.host_flags &= ~IDE_HFLAG_SINGLE;
	पूर्ण

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id svwks_pci_tbl[] = अणु
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_OSB4IDE),   0 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB5IDE),   1 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB6IDE),   2 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2),  3 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_HT1000IDE), 4 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, svwks_pci_tbl);

अटल काष्ठा pci_driver svwks_pci_driver = अणु
	.name		= "Serverworks_IDE",
	.id_table	= svwks_pci_tbl,
	.probe		= svwks_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init svwks_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&svwks_pci_driver);
पूर्ण

अटल व्योम __निकास svwks_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&svwks_pci_driver);
पूर्ण

module_init(svwks_ide_init);
module_निकास(svwks_ide_निकास);

MODULE_AUTHOR("Michael Aubry. Andrzej Krzysztofowicz, Andre Hedrick, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("PCI driver module for Serverworks OSB4/CSB5/CSB6 IDE");
MODULE_LICENSE("GPL");
