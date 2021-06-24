<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_sis.c - SiS ATA driver
 *
 *	(C) 2005 Red Hat
 *	(C) 2007,2009 Bartlomiej Zolnierkiewicz
 *
 *    Based upon linux/drivers/ide/pci/sis5513.c
 * Copyright (C) 1999-2000	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2002		Lionel Bouton <Lionel.Bouton@inet6.fr>, Maपूर्णांकainer
 * Copyright (C) 2003		Vojtech Pavlik <vojtech@suse.cz>
 * SiS Taiwan		: क्रम direct support and hardware.
 * Daniela Engert	: क्रम initial ATA100 advices and numerous others.
 * John Fremlin, Manfred Spraul, Dave Morgan, Peter Kjellerstedt	:
 *			  क्रम checking code correctness, providing patches.
 * Original tests and design on the SiS620 chipset.
 * ATA100 tests and design on the SiS735 chipset.
 * ATA16/33 support from specs
 * ATA133 support क्रम SiS961/962 by L.C. Chang <lcchang@sis.com.tw>
 *
 *
 *	TODO
 *	Check MWDMA on drives that करोn't support MWDMA speed pio cycles ?
 *	More Testing
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/ata.h>
#समावेश "sis.h"

#घोषणा DRV_NAME	"pata_sis"
#घोषणा DRV_VERSION	"0.5.2"

काष्ठा sis_chipset अणु
	u16 device;				/* PCI host ID */
	स्थिर काष्ठा ata_port_info *info;	/* Info block */
	/* Probably add family, cable detect type etc here to clean
	   up code later */
पूर्ण;

काष्ठा sis_laptop अणु
	u16 device;
	u16 subvenकरोr;
	u16 subdevice;
पूर्ण;

अटल स्थिर काष्ठा sis_laptop sis_laptop[] = अणु
	/* devid, subvenकरोr, subdev */
	अणु 0x5513, 0x1043, 0x1107 पूर्ण,	/* ASUS A6K */
	अणु 0x5513, 0x1734, 0x105F पूर्ण,	/* FSC Amilo A1630 */
	अणु 0x5513, 0x1071, 0x8640 पूर्ण,	/* EasyNote K5305 */
	/* end marker */
	अणु 0, पूर्ण
पूर्ण;

अटल पूर्णांक sis_लघु_ata40(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा sis_laptop *lap = &sis_laptop[0];

	जबतक (lap->device) अणु
		अगर (lap->device == dev->device &&
		    lap->subvenकरोr == dev->subप्रणाली_venकरोr &&
		    lap->subdevice == dev->subप्रणाली_device)
			वापस 1;
		lap++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	sis_old_port_base - वापस PCI configuration base क्रम dev
 *	@adev: device
 *
 *	Returns the base of the PCI configuration रेजिस्टरs क्रम this port
 *	number.
 */

अटल पूर्णांक sis_old_port_base(काष्ठा ata_device *adev)
अणु
	वापस 0x40 + (4 * adev->link->ap->port_no) + (2 * adev->devno);
पूर्ण

/**
 *	sis_port_base - वापस PCI configuration base क्रम dev
 *	@adev: device
 *
 *	Returns the base of the PCI configuration रेजिस्टरs क्रम this port
 *	number.
 */

अटल पूर्णांक sis_port_base(काष्ठा ata_device *adev)
अणु
	काष्ठा ata_port *ap = adev->link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = 0x40;
	u32 reg54;

	/* If bit 30 is set then the रेजिस्टरs are mapped at 0x70 not 0x40 */
	pci_पढ़ो_config_dword(pdev, 0x54, &reg54);
	अगर (reg54 & 0x40000000)
		port = 0x70;

	वापस port + (8 * ap->port_no) + (4 * adev->devno);
पूर्ण

/**
 *	sis_133_cable_detect - check क्रम 40/80 pin
 *	@ap: Port
 *
 *	Perक्रमm cable detection क्रम the later UDMA133 capable
 *	SiS chipset.
 */

अटल पूर्णांक sis_133_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 पंचांगp;

	/* The top bit of this रेजिस्टर is the cable detect bit */
	pci_पढ़ो_config_word(pdev, 0x50 + 2 * ap->port_no, &पंचांगp);
	अगर ((पंचांगp & 0x8000) && !sis_लघु_ata40(pdev))
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	sis_66_cable_detect - check क्रम 40/80 pin
 *	@ap: Port
 *
 *	Perक्रमm cable detection on the UDMA66, UDMA100 and early UDMA133
 *	SiS IDE controllers.
 */

अटल पूर्णांक sis_66_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 पंचांगp;

	/* Older chips keep cable detect in bits 4/5 of reg 0x48 */
	pci_पढ़ो_config_byte(pdev, 0x48, &पंचांगp);
	पंचांगp >>= ap->port_no;
	अगर ((पंचांगp & 0x10) && !sis_लघु_ata40(pdev))
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण


/**
 *	sis_pre_reset - probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Set up cable type and use generic probe init
 */

अटल पूर्णांक sis_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits sis_enable_bits[] = अणु
		अणु 0x4aU, 1U, 0x02UL, 0x02UL पूर्ण,	/* port 0 */
		अणु 0x4aU, 1U, 0x04UL, 0x04UL पूर्ण,	/* port 1 */
	पूर्ण;

	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &sis_enable_bits[ap->port_no]))
		वापस -ENOENT;

	/* Clear the FIFO settings. We can't enable the FIFO until
	   we know we are poking at a disk */
	pci_ग_लिखो_config_byte(pdev, 0x4B, 0);
	वापस ata_sff_prereset(link, deadline);
पूर्ण


/**
 *	sis_set_fअगरo - Set RWP fअगरo bits क्रम this device
 *	@ap: Port
 *	@adev: Device
 *
 *	SIS chipsets implement prefetch/postग_लिखो bits क्रम each device
 *	on both channels. This functionality is not ATAPI compatible and
 *	must be configured according to the class of device present
 */

अटल व्योम sis_set_fअगरo(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 fअगरoctrl;
	u8 mask = 0x11;

	mask <<= (2 * ap->port_no);
	mask <<= adev->devno;

	/* This holds various bits including the FIFO control */
	pci_पढ़ो_config_byte(pdev, 0x4B, &fअगरoctrl);
	fअगरoctrl &= ~mask;

	/* Enable क्रम ATA (disk) only */
	अगर (adev->class == ATA_DEV_ATA)
		fअगरoctrl |= mask;
	pci_ग_लिखो_config_byte(pdev, 0x4B, fअगरoctrl);
पूर्ण

/**
 *	sis_old_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring क्रम.
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. This
 *	function handles PIO set up क्रम all chips that are pre ATA100 and
 *	also early ATA100 devices.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_old_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = sis_old_port_base(adev);
	u8 t1, t2;
	पूर्णांक speed = adev->pio_mode - XFER_PIO_0;

	अटल स्थिर u8 active[]   = अणु 0x00, 0x07, 0x04, 0x03, 0x01 पूर्ण;
	अटल स्थिर u8 recovery[] = अणु 0x00, 0x06, 0x04, 0x03, 0x03 पूर्ण;

	sis_set_fअगरo(ap, adev);

	pci_पढ़ो_config_byte(pdev, port, &t1);
	pci_पढ़ो_config_byte(pdev, port + 1, &t2);

	t1 &= ~0x0F;	/* Clear active/recovery timings */
	t2 &= ~0x07;

	t1 |= active[speed];
	t2 |= recovery[speed];

	pci_ग_लिखो_config_byte(pdev, port, t1);
	pci_ग_लिखो_config_byte(pdev, port + 1, t2);
पूर्ण

/**
 *	sis_100_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring क्रम.
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. This
 *	function handles PIO set up क्रम ATA100 devices and early ATA133.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_100_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = sis_old_port_base(adev);
	पूर्णांक speed = adev->pio_mode - XFER_PIO_0;

	अटल स्थिर u8 actrec[] = अणु 0x00, 0x67, 0x44, 0x33, 0x31 पूर्ण;

	sis_set_fअगरo(ap, adev);

	pci_ग_लिखो_config_byte(pdev, port, actrec[speed]);
पूर्ण

/**
 *	sis_133_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring क्रम.
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. This
 *	function handles PIO set up क्रम the later ATA133 devices.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_133_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port;
	u32 t1;
	पूर्णांक speed = adev->pio_mode - XFER_PIO_0;

	अटल स्थिर u32 timing133[] = अणु
		0x28269000,	/* Recovery << 24 | Act << 16 | Ini << 12 */
		0x0C266000,
		0x04263000,
		0x0C0A3000,
		0x05093000
	पूर्ण;
	अटल स्थिर u32 timing100[] = अणु
		0x1E1C6000,	/* Recovery << 24 | Act << 16 | Ini << 12 */
		0x091C4000,
		0x031C2000,
		0x09072000,
		0x04062000
	पूर्ण;

	sis_set_fअगरo(ap, adev);

	port = sis_port_base(adev);
	pci_पढ़ो_config_dword(pdev, port, &t1);
	t1 &= 0xC0C00FFF;	/* Mask out timing */

	अगर (t1 & 0x08)		/* 100 or 133 ? */
		t1 |= timing133[speed];
	अन्यथा
		t1 |= timing100[speed];
	pci_ग_लिखो_config_byte(pdev, port, t1);
पूर्ण

/**
 *	sis_old_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *	Handles pre UDMA and UDMA33 devices. Supports MWDMA as well unlike
 *	the old ide/pci driver.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_old_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक speed = adev->dma_mode - XFER_MW_DMA_0;
	पूर्णांक drive_pci = sis_old_port_base(adev);
	u16 timing;

	अटल स्थिर u16 mwdma_bits[] = अणु 0x008, 0x302, 0x301 पूर्ण;
	अटल स्थिर u16 udma_bits[]  = अणु 0xE000, 0xC000, 0xA000 पूर्ण;

	pci_पढ़ो_config_word(pdev, drive_pci, &timing);

	अगर (adev->dma_mode < XFER_UDMA_0) अणु
		/* bits 3-0 hold recovery timing bits 8-10 active timing and
		   the higher bits are dependent on the device */
		timing &= ~0x870F;
		timing |= mwdma_bits[speed];
	पूर्ण अन्यथा अणु
		/* Bit 15 is UDMA on/off, bit 13-14 are cycle समय */
		speed = adev->dma_mode - XFER_UDMA_0;
		timing &= ~0x6000;
		timing |= udma_bits[speed];
	पूर्ण
	pci_ग_लिखो_config_word(pdev, drive_pci, timing);
पूर्ण

/**
 *	sis_66_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *	Handles UDMA66 and early UDMA100 devices. Supports MWDMA as well unlike
 *	the old ide/pci driver.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_66_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक speed = adev->dma_mode - XFER_MW_DMA_0;
	पूर्णांक drive_pci = sis_old_port_base(adev);
	u16 timing;

	/* MWDMA 0-2 and UDMA 0-5 */
	अटल स्थिर u16 mwdma_bits[] = अणु 0x008, 0x302, 0x301 पूर्ण;
	अटल स्थिर u16 udma_bits[]  = अणु 0xF000, 0xD000, 0xB000, 0xA000, 0x9000, 0x8000 पूर्ण;

	pci_पढ़ो_config_word(pdev, drive_pci, &timing);

	अगर (adev->dma_mode < XFER_UDMA_0) अणु
		/* bits 3-0 hold recovery timing bits 8-10 active timing and
		   the higher bits are dependent on the device, bit 15 udma */
		timing &= ~0x870F;
		timing |= mwdma_bits[speed];
	पूर्ण अन्यथा अणु
		/* Bit 15 is UDMA on/off, bit 12-14 are cycle समय */
		speed = adev->dma_mode - XFER_UDMA_0;
		timing &= ~0xF000;
		timing |= udma_bits[speed];
	पूर्ण
	pci_ग_लिखो_config_word(pdev, drive_pci, timing);
पूर्ण

/**
 *	sis_100_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *	Handles UDMA66 and early UDMA100 devices.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_100_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक speed = adev->dma_mode - XFER_MW_DMA_0;
	पूर्णांक drive_pci = sis_old_port_base(adev);
	u8 timing;

	अटल स्थिर u8 udma_bits[]  = अणु 0x8B, 0x87, 0x85, 0x83, 0x82, 0x81पूर्ण;

	pci_पढ़ो_config_byte(pdev, drive_pci + 1, &timing);

	अगर (adev->dma_mode < XFER_UDMA_0) अणु
		/* NOT SUPPORTED YET: NEED DATA SHEET. DITTO IN OLD DRIVER */
	पूर्ण अन्यथा अणु
		/* Bit 7 is UDMA on/off, bit 0-3 are cycle समय */
		speed = adev->dma_mode - XFER_UDMA_0;
		timing &= ~0x8F;
		timing |= udma_bits[speed];
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, drive_pci + 1, timing);
पूर्ण

/**
 *	sis_133_early_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *	Handles early SiS 961 bridges.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_133_early_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक speed = adev->dma_mode - XFER_MW_DMA_0;
	पूर्णांक drive_pci = sis_old_port_base(adev);
	u8 timing;
	/* Low 4 bits are timing */
	अटल स्थिर u8 udma_bits[]  = अणु 0x8F, 0x8A, 0x87, 0x85, 0x83, 0x82, 0x81पूर्ण;

	pci_पढ़ो_config_byte(pdev, drive_pci + 1, &timing);

	अगर (adev->dma_mode < XFER_UDMA_0) अणु
		/* NOT SUPPORTED YET: NEED DATA SHEET. DITTO IN OLD DRIVER */
	पूर्ण अन्यथा अणु
		/* Bit 7 is UDMA on/off, bit 0-3 are cycle समय */
		speed = adev->dma_mode - XFER_UDMA_0;
		timing &= ~0x8F;
		timing |= udma_bits[speed];
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, drive_pci + 1, timing);
पूर्ण

/**
 *	sis_133_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sis_133_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port;
	u32 t1;

	port = sis_port_base(adev);
	pci_पढ़ो_config_dword(pdev, port, &t1);

	अगर (adev->dma_mode < XFER_UDMA_0) अणु
		/* Recovery << 24 | Act << 16 | Ini << 12, like PIO modes */
		अटल स्थिर u32 timing_u100[] = अणु 0x19154000, 0x06072000, 0x04062000 पूर्ण;
		अटल स्थिर u32 timing_u133[] = अणु 0x221C6000, 0x0C0A3000, 0x05093000 पूर्ण;
		पूर्णांक speed = adev->dma_mode - XFER_MW_DMA_0;

		t1 &= 0xC0C00FFF;
		/* disable UDMA */
		t1 &= ~0x00000004;
		अगर (t1 & 0x08)
			t1 |= timing_u133[speed];
		अन्यथा
			t1 |= timing_u100[speed];
	पूर्ण अन्यथा अणु
		/* bits 4- cycle समय 8 - cvs समय */
		अटल स्थिर u32 timing_u100[] = अणु 0x6B0, 0x470, 0x350, 0x140, 0x120, 0x110, 0x000 पूर्ण;
		अटल स्थिर u32 timing_u133[] = अणु 0x9F0, 0x6A0, 0x470, 0x250, 0x230, 0x220, 0x210 पूर्ण;
		पूर्णांक speed = adev->dma_mode - XFER_UDMA_0;

		t1 &= ~0x00000FF0;
		/* enable UDMA */
		t1 |= 0x00000004;
		अगर (t1 & 0x08)
			t1 |= timing_u133[speed];
		अन्यथा
			t1 |= timing_u100[speed];
	पूर्ण
	pci_ग_लिखो_config_dword(pdev, port, t1);
पूर्ण

/**
 *	sis_133_mode_filter - mode selection filter
 *	@adev: ATA device
 *	@mask: received mask to manipulate and pass back
 *
 *	Block UDMA6 on devices that करो not support it.
 */

अटल अचिन्हित दीर्घ sis_133_mode_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	काष्ठा ata_port *ap = adev->link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = sis_port_base(adev);
	u32 t1;

	pci_पढ़ो_config_dword(pdev, port, &t1);
	/* अगर ATA133 is disabled, mask it out */
	अगर (!(t1 & 0x08))
		mask &= ~(0xC0 << ATA_SHIFT_UDMA);
	वापस mask;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sis_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations sis_133_क्रम_sata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.set_piomode		= sis_133_set_piomode,
	.set_dmamode		= sis_133_set_dmamode,
	.cable_detect		= sis_133_cable_detect,
पूर्ण;

अटल काष्ठा ata_port_operations sis_base_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.prereset		= sis_pre_reset,
पूर्ण;

अटल काष्ठा ata_port_operations sis_133_ops = अणु
	.inherits		= &sis_base_ops,
	.set_piomode		= sis_133_set_piomode,
	.set_dmamode		= sis_133_set_dmamode,
	.cable_detect		= sis_133_cable_detect,
	.mode_filter		= sis_133_mode_filter,
पूर्ण;

अटल काष्ठा ata_port_operations sis_133_early_ops = अणु
	.inherits		= &sis_base_ops,
	.set_piomode		= sis_100_set_piomode,
	.set_dmamode		= sis_133_early_set_dmamode,
	.cable_detect		= sis_66_cable_detect,
पूर्ण;

अटल काष्ठा ata_port_operations sis_100_ops = अणु
	.inherits		= &sis_base_ops,
	.set_piomode		= sis_100_set_piomode,
	.set_dmamode		= sis_100_set_dmamode,
	.cable_detect		= sis_66_cable_detect,
पूर्ण;

अटल काष्ठा ata_port_operations sis_66_ops = अणु
	.inherits		= &sis_base_ops,
	.set_piomode		= sis_old_set_piomode,
	.set_dmamode		= sis_66_set_dmamode,
	.cable_detect		= sis_66_cable_detect,
पूर्ण;

अटल काष्ठा ata_port_operations sis_old_ops = अणु
	.inherits		= &sis_base_ops,
	.set_piomode		= sis_old_set_piomode,
	.set_dmamode		= sis_old_set_dmamode,
	.cable_detect		= ata_cable_40wire,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info sis_info = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	/* No UDMA */
	.port_ops	= &sis_old_ops,
पूर्ण;
अटल स्थिर काष्ठा ata_port_info sis_info33 = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA2,
	.port_ops	= &sis_old_ops,
पूर्ण;
अटल स्थिर काष्ठा ata_port_info sis_info66 = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA4,
	.port_ops	= &sis_66_ops,
पूर्ण;
अटल स्थिर काष्ठा ata_port_info sis_info100 = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA5,
	.port_ops	= &sis_100_ops,
पूर्ण;
अटल स्थिर काष्ठा ata_port_info sis_info100_early = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA5,
	.port_ops	= &sis_66_ops,
पूर्ण;
अटल स्थिर काष्ठा ata_port_info sis_info133 = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &sis_133_ops,
पूर्ण;
स्थिर काष्ठा ata_port_info sis_info133_क्रम_sata = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &sis_133_क्रम_sata_ops,
पूर्ण;
अटल स्थिर काष्ठा ata_port_info sis_info133_early = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &sis_133_early_ops,
पूर्ण;

/* Privately shared with the SiS180 SATA driver, not क्रम use अन्यथाwhere */
EXPORT_SYMBOL_GPL(sis_info133_क्रम_sata);

अटल व्योम sis_fixup(काष्ठा pci_dev *pdev, काष्ठा sis_chipset *sis)
अणु
	u16 regw;
	u8 reg;

	अगर (sis->info == &sis_info133) अणु
		pci_पढ़ो_config_word(pdev, 0x50, &regw);
		अगर (regw & 0x08)
			pci_ग_लिखो_config_word(pdev, 0x50, regw & ~0x08);
		pci_पढ़ो_config_word(pdev, 0x52, &regw);
		अगर (regw & 0x08)
			pci_ग_लिखो_config_word(pdev, 0x52, regw & ~0x08);
		वापस;
	पूर्ण

	अगर (sis->info == &sis_info133_early || sis->info == &sis_info100) अणु
		/* Fix up latency */
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x80);
		/* Set compatibility bit */
		pci_पढ़ो_config_byte(pdev, 0x49, &reg);
		अगर (!(reg & 0x01))
			pci_ग_लिखो_config_byte(pdev, 0x49, reg | 0x01);
		वापस;
	पूर्ण

	अगर (sis->info == &sis_info66 || sis->info == &sis_info100_early) अणु
		/* Fix up latency */
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x80);
		/* Set compatibility bit */
		pci_पढ़ो_config_byte(pdev, 0x52, &reg);
		अगर (!(reg & 0x04))
			pci_ग_लिखो_config_byte(pdev, 0x52, reg | 0x04);
		वापस;
	पूर्ण

	अगर (sis->info == &sis_info33) अणु
		pci_पढ़ो_config_byte(pdev, PCI_CLASS_PROG, &reg);
		अगर (( reg & 0x0F ) != 0x00)
			pci_ग_लिखो_config_byte(pdev, PCI_CLASS_PROG, reg & 0xF0);
		/* Fall through to ATA16 fixup below */
	पूर्ण

	अगर (sis->info == &sis_info || sis->info == &sis_info33) अणु
		/* क्रमce per drive recovery and active timings
		   needed on ATA_33 and below chips */
		pci_पढ़ो_config_byte(pdev, 0x52, &reg);
		अगर (!(reg & 0x08))
			pci_ग_लिखो_config_byte(pdev, 0x52, reg|0x08);
		वापस;
	पूर्ण

	BUG();
पूर्ण

/**
 *	sis_init_one - Register SiS ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in sis_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer. We probe क्रम combined mode (sigh),
 *	and then hand over control to libata, क्रम it to करो the rest.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक sis_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	काष्ठा pci_dev *host = शून्य;
	काष्ठा sis_chipset *chipset = शून्य;
	काष्ठा sis_chipset *sets;
	पूर्णांक rc;

	अटल काष्ठा sis_chipset sis_chipsets[] = अणु

		अणु 0x0968, &sis_info133 पूर्ण,
		अणु 0x0966, &sis_info133 पूर्ण,
		अणु 0x0965, &sis_info133 पूर्ण,
		अणु 0x0745, &sis_info100 पूर्ण,
		अणु 0x0735, &sis_info100 पूर्ण,
		अणु 0x0733, &sis_info100 पूर्ण,
		अणु 0x0635, &sis_info100 पूर्ण,
		अणु 0x0633, &sis_info100 पूर्ण,

		अणु 0x0730, &sis_info100_early पूर्ण,	/* 100 with ATA 66 layout */
		अणु 0x0550, &sis_info100_early पूर्ण,	/* 100 with ATA 66 layout */

		अणु 0x0640, &sis_info66 पूर्ण,
		अणु 0x0630, &sis_info66 पूर्ण,
		अणु 0x0620, &sis_info66 पूर्ण,
		अणु 0x0540, &sis_info66 पूर्ण,
		अणु 0x0530, &sis_info66 पूर्ण,

		अणु 0x5600, &sis_info33 पूर्ण,
		अणु 0x5598, &sis_info33 पूर्ण,
		अणु 0x5597, &sis_info33 पूर्ण,
		अणु 0x5591, &sis_info33 पूर्ण,
		अणु 0x5582, &sis_info33 पूर्ण,
		अणु 0x5581, &sis_info33 पूर्ण,

		अणु 0x5596, &sis_info पूर्ण,
		अणु 0x5571, &sis_info पूर्ण,
		अणु 0x5517, &sis_info पूर्ण,
		अणु 0x5511, &sis_info पूर्ण,

		अणु0पूर्ण
	पूर्ण;
	अटल काष्ठा sis_chipset sis133_early = अणु
		0x0, &sis_info133_early
	पूर्ण;
	अटल काष्ठा sis_chipset sis133 = अणु
		0x0, &sis_info133
	पूर्ण;
	अटल काष्ठा sis_chipset sis100_early = अणु
		0x0, &sis_info100_early
	पूर्ण;
	अटल काष्ठा sis_chipset sis100 = अणु
		0x0, &sis_info100
	पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* We have to find the bridge first */
	क्रम (sets = &sis_chipsets[0]; sets->device; sets++) अणु
		host = pci_get_device(PCI_VENDOR_ID_SI, sets->device, शून्य);
		अगर (host != शून्य) अणु
			chipset = sets;			/* Match found */
			अगर (sets->device == 0x630) अणु	/* SIS630 */
				अगर (host->revision >= 0x30)	/* 630 ET */
					chipset = &sis100_early;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* Look क्रम concealed bridges */
	अगर (chipset == शून्य) अणु
		/* Second check */
		u32 idemisc;
		u16 trueid;

		/* Disable ID masking and रेजिस्टर remapping then
		   see what the real ID is */

		pci_पढ़ो_config_dword(pdev, 0x54, &idemisc);
		pci_ग_लिखो_config_dword(pdev, 0x54, idemisc & 0x7fffffff);
		pci_पढ़ो_config_word(pdev, PCI_DEVICE_ID, &trueid);
		pci_ग_लिखो_config_dword(pdev, 0x54, idemisc);

		चयन(trueid) अणु
		हाल 0x5518:	/* SIS 962/963 */
			dev_info(&pdev->dev,
				 "SiS 962/963 MuTIOL IDE UDMA133 controller\n");
			chipset = &sis133;
			अगर ((idemisc & 0x40000000) == 0) अणु
				pci_ग_लिखो_config_dword(pdev, 0x54, idemisc | 0x40000000);
				dev_info(&pdev->dev,
					 "Switching to 5513 register mapping\n");
			पूर्ण
			अवरोध;
		हाल 0x0180:	/* SIS 965/965L */
			chipset = &sis133;
			अवरोध;
		हाल 0x1180:	/* SIS 966/966L */
			chipset = &sis133;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Further check */
	अगर (chipset == शून्य) अणु
		काष्ठा pci_dev *lpc_bridge;
		u16 trueid;
		u8 prefctl;
		u8 idecfg;

		/* Try the second unmasking technique */
		pci_पढ़ो_config_byte(pdev, 0x4a, &idecfg);
		pci_ग_लिखो_config_byte(pdev, 0x4a, idecfg | 0x10);
		pci_पढ़ो_config_word(pdev, PCI_DEVICE_ID, &trueid);
		pci_ग_लिखो_config_byte(pdev, 0x4a, idecfg);

		चयन(trueid) अणु
		हाल 0x5517:
			lpc_bridge = pci_get_slot(pdev->bus, 0x10); /* Bus 0 Dev 2 Fn 0 */
			अगर (lpc_bridge == शून्य)
				अवरोध;
			pci_पढ़ो_config_byte(pdev, 0x49, &prefctl);
			pci_dev_put(lpc_bridge);

			अगर (lpc_bridge->revision == 0x10 && (prefctl & 0x80)) अणु
				chipset = &sis133_early;
				अवरोध;
			पूर्ण
			chipset = &sis100;
			अवरोध;
		पूर्ण
	पूर्ण
	pci_dev_put(host);

	/* No chipset info, no support */
	अगर (chipset == शून्य)
		वापस -ENODEV;

	ppi[0] = chipset->info;

	sis_fixup(pdev, chipset);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &sis_sht, chipset, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sis_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	sis_fixup(pdev, host->निजी_data);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id sis_pci_tbl[] = अणु
	अणु PCI_VDEVICE(SI, 0x5513), पूर्ण,	/* SiS 5513 */
	अणु PCI_VDEVICE(SI, 0x5518), पूर्ण,	/* SiS 5518 */
	अणु PCI_VDEVICE(SI, 0x1180), पूर्ण,	/* SiS 1180 */

	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver sis_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= sis_pci_tbl,
	.probe			= sis_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= sis_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(sis_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for SiS ATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sis_pci_tbl);
MODULE_VERSION(DRV_VERSION);
