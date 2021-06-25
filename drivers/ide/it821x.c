<शैली गुरु>
/*
 * Copyright (C) 2004		Red Hat
 * Copyright (C) 2007		Bartlomiej Zolnierkiewicz
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *  Based in part on the ITE venकरोr provided SCSI driver.
 *
 *  Documentation:
 *	Datasheet is मुक्तly available, some other करोcuments under NDA.
 *
 *  The ITE8212 isn't exactly a standard IDE controller. It has two
 *  modes. In pass through mode then it is an IDE controller. In its smart
 *  mode its actually quite a capable hardware raid controller disguised
 *  as an IDE controller. Smart mode only understands DMA पढ़ो/ग_लिखो and
 *  identअगरy, none of the fancier commands apply. The IT8211 is identical
 *  in other respects but lacks the raid mode.
 *
 *  Errata:
 *  o	Rev 0x10 also requires master/slave hold the same DMA timings and
 *	cannot करो ATAPI MWDMA.
 *  o	The identअगरy data क्रम raid volumes lacks CHS info (technically ok)
 *	but also fails to set the LBA28 and other bits. We fix these in
 *	the IDE probe quirk code.
 *  o	If you ग_लिखो LBA48 sized I/O's (ie > 256 sector) in smart mode
 *	raid then the controller firmware dies
 *  o	Smart mode without RAID करोesn't clear all the necessary identअगरy
 *	bits to reduce the command set to the one used
 *
 *  This has a few impacts on the driver
 *  - In pass through mode we करो all the work you would expect
 *  - In smart mode the घड़ीing set up is करोne by the controller generally
 *    but we must watch the other limits and filter.
 *  - There are a few extra venकरोr commands that actually talk to the
 *    controller but only work PIO with no IRQ.
 *
 *  Venकरोr areas of the identअगरy block in smart mode are used क्रम the
 *  timing and policy set up. Each HDD in raid mode also has a serial
 *  block on the disk. The hardware extra commands are get/set chip status,
 *  rebuild, get rebuild status.
 *
 *  In Linux the driver supports pass through mode as अगर the device was
 *  just another IDE controller. If the smart mode is running then
 *  volumes are managed by the controller firmware and each IDE "disk"
 *  is a raid volume. Even more cute - the controller can करो स्वतःmated
 *  hotplug and rebuild.
 *
 *  The pass through controller itself is a little demented. It has a
 *  flaw that it has a single set of PIO/MWDMA timings per channel so
 *  non UDMA devices restrict each others perक्रमmance. It also has a
 *  single घड़ी source per channel so mixed UDMA100/133 perक्रमmance
 *  isn't perfect and we have to pick a घड़ी. Thankfully none of this
 *  matters in smart mode. ATAPI DMA is not currently supported.
 *
 *  It seems the smart mode is a win क्रम RAID1/RAID10 but otherwise not.
 *
 *  TODO
 *	-	ATAPI UDMA is ok but not MWDMA it seems
 *	-	RAID configuration ioctls
 *	-	Move to libata once it grows up
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "it821x"

#घोषणा QUIRK_VORTEX86 1

काष्ठा it821x_dev
अणु
	अचिन्हित पूर्णांक smart:1,		/* Are we in smart raid mode */
		timing10:1;		/* Rev 0x10 */
	u8	घड़ी_mode;		/* 0, ATA_50 or ATA_66 */
	u8	want[2][2];		/* Mode/Pri log क्रम master slave */
	/* We need these क्रम चयनing the घड़ी when DMA goes on/off
	   The high byte is the 66Mhz timing */
	u16	pio[2];			/* Cached PIO values */
	u16	mwdma[2];		/* Cached MWDMA values */
	u16	udma[2];		/* Cached UDMA values (per drive) */
	u16	quirks;
पूर्ण;

#घोषणा ATA_66		0
#घोषणा ATA_50		1
#घोषणा ATA_ANY		2

#घोषणा UDMA_OFF	0
#घोषणा MWDMA_OFF	0

/*
 *	We allow users to क्रमce the card पूर्णांकo non raid mode without
 *	flashing the alternative BIOS. This is also necessary right now
 *	क्रम embedded platक्रमms that cannot run a PC BIOS but are using this
 *	device.
 */

अटल पूर्णांक it8212_noraid;

/**
 *	it821x_program	-	program the PIO/MWDMA रेजिस्टरs
 *	@drive: drive to tune
 *	@timing: timing info
 *
 *	Program the PIO/MWDMA timing क्रम this channel according to the
 *	current घड़ी.
 */

अटल व्योम it821x_program(ide_drive_t *drive, u16 timing)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	पूर्णांक channel = hwअगर->channel;
	u8 conf;

	/* Program PIO/MWDMA timing bits */
	अगर(itdev->घड़ी_mode == ATA_66)
		conf = timing >> 8;
	अन्यथा
		conf = timing & 0xFF;

	pci_ग_लिखो_config_byte(dev, 0x54 + 4 * channel, conf);
पूर्ण

/**
 *	it821x_program_udma	-	program the UDMA रेजिस्टरs
 *	@drive: drive to tune
 *	@timing: timing info
 *
 *	Program the UDMA timing क्रम this drive according to the
 *	current घड़ी.
 */

अटल व्योम it821x_program_udma(ide_drive_t *drive, u16 timing)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	पूर्णांक channel = hwअगर->channel;
	u8 unit = drive->dn & 1, conf;

	/* Program UDMA timing bits */
	अगर(itdev->घड़ी_mode == ATA_66)
		conf = timing >> 8;
	अन्यथा
		conf = timing & 0xFF;

	अगर (itdev->timing10 == 0)
		pci_ग_लिखो_config_byte(dev, 0x56 + 4 * channel + unit, conf);
	अन्यथा अणु
		pci_ग_लिखो_config_byte(dev, 0x56 + 4 * channel, conf);
		pci_ग_लिखो_config_byte(dev, 0x56 + 4 * channel + 1, conf);
	पूर्ण
पूर्ण

/**
 *	it821x_घड़ी_strategy
 *	@drive: drive to set up
 *
 *	Select between the 50 and 66Mhz base घड़ीs to get the best
 *	results क्रम this पूर्णांकerface.
 */

अटल व्योम it821x_घड़ी_strategy(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	पूर्णांक घड़ी, altघड़ी, sel = 0;
	u8 unit = drive->dn & 1, v;

	अगर(itdev->want[0][0] > itdev->want[1][0]) अणु
		घड़ी = itdev->want[0][1];
		altघड़ी = itdev->want[1][1];
	पूर्ण अन्यथा अणु
		घड़ी = itdev->want[1][1];
		altघड़ी = itdev->want[0][1];
	पूर्ण

	/*
	 * अगर both घड़ीs can be used क्रम the mode with the higher priority
	 * use the घड़ी needed by the mode with the lower priority
	 */
	अगर (घड़ी == ATA_ANY)
		घड़ी = altघड़ी;

	/* Nobody cares - keep the same घड़ी */
	अगर(घड़ी == ATA_ANY)
		वापस;
	/* No change */
	अगर(घड़ी == itdev->घड़ी_mode)
		वापस;

	/* Load this पूर्णांकo the controller ? */
	अगर(घड़ी == ATA_66)
		itdev->घड़ी_mode = ATA_66;
	अन्यथा अणु
		itdev->घड़ी_mode = ATA_50;
		sel = 1;
	पूर्ण

	pci_पढ़ो_config_byte(dev, 0x50, &v);
	v &= ~(1 << (1 + hwअगर->channel));
	v |= sel << (1 + hwअगर->channel);
	pci_ग_लिखो_config_byte(dev, 0x50, v);

	/*
	 *	Reprogram the UDMA/PIO of the pair drive क्रम the चयन
	 *	MWDMA will be dealt with by the dma चयनer
	 */
	अगर(pair && itdev->udma[1-unit] != UDMA_OFF) अणु
		it821x_program_udma(pair, itdev->udma[1-unit]);
		it821x_program(pair, itdev->pio[1-unit]);
	पूर्ण
	/*
	 *	Reprogram the UDMA/PIO of our drive क्रम the चयन.
	 *	MWDMA will be dealt with by the dma चयनer
	 */
	अगर(itdev->udma[unit] != UDMA_OFF) अणु
		it821x_program_udma(drive, itdev->udma[unit]);
		it821x_program(drive, itdev->pio[unit]);
	पूर्ण
पूर्ण

/**
 *	it821x_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Tune the host to the desired PIO mode taking पूर्णांकo the consideration
 *	the maximum PIO mode supported by the other device on the cable.
 */

अटल व्योम it821x_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	u8 unit = drive->dn & 1, set_pio = pio;

	/* Spec says 89 ref driver uses 88 */
	अटल u16 pio_timings[]= अणु 0xAA88, 0xA382, 0xA181, 0x3332, 0x3121 पूर्ण;
	अटल u8 pio_want[]    = अणु ATA_66, ATA_66, ATA_66, ATA_66, ATA_ANY पूर्ण;

	/*
	 * Compute the best PIO mode we can क्रम a given device. We must
	 * pick a speed that करोes not cause problems with the other device
	 * on the cable.
	 */
	अगर (pair) अणु
		u8 pair_pio = pair->pio_mode - XFER_PIO_0;
		/* trim PIO to the slowest of the master/slave */
		अगर (pair_pio < set_pio)
			set_pio = pair_pio;
	पूर्ण

	/* We prefer 66Mhz घड़ी क्रम PIO 0-3, करोn't care क्रम PIO4 */
	itdev->want[unit][1] = pio_want[set_pio];
	itdev->want[unit][0] = 1;	/* PIO is lowest priority */
	itdev->pio[unit] = pio_timings[set_pio];
	it821x_घड़ी_strategy(drive);
	it821x_program(drive, itdev->pio[unit]);
पूर्ण

/**
 *	it821x_tune_mwdma	-	tune a channel क्रम MWDMA
 *	@drive: drive to set up
 *	@mode_wanted: the target operating mode
 *
 *	Load the timing settings क्रम this device mode पूर्णांकo the
 *	controller when करोing MWDMA in pass through mode. The caller
 *	must manage the whole lack of per device MWDMA/PIO timings and
 *	the shared MWDMA/PIO timing रेजिस्टर.
 */

अटल व्योम it821x_tune_mwdma(ide_drive_t *drive, u8 mode_wanted)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा it821x_dev *itdev = (व्योम *)ide_get_hwअगरdata(hwअगर);
	u8 unit = drive->dn & 1, channel = hwअगर->channel, conf;

	अटल u16 dma[]	= अणु 0x8866, 0x3222, 0x3121 पूर्ण;
	अटल u8 mwdma_want[]	= अणु ATA_ANY, ATA_66, ATA_ANY पूर्ण;

	itdev->want[unit][1] = mwdma_want[mode_wanted];
	itdev->want[unit][0] = 2;	/* MWDMA is low priority */
	itdev->mwdma[unit] = dma[mode_wanted];
	itdev->udma[unit] = UDMA_OFF;

	/* UDMA bits off - Revision 0x10 करो them in pairs */
	pci_पढ़ो_config_byte(dev, 0x50, &conf);
	अगर (itdev->timing10)
		conf |= channel ? 0x60: 0x18;
	अन्यथा
		conf |= 1 << (3 + 2 * channel + unit);
	pci_ग_लिखो_config_byte(dev, 0x50, conf);

	it821x_घड़ी_strategy(drive);
	/* FIXME: करो we need to program this ? */
	/* it821x_program(drive, itdev->mwdma[unit]); */
पूर्ण

/**
 *	it821x_tune_udma	-	tune a channel क्रम UDMA
 *	@drive: drive to set up
 *	@mode_wanted: the target operating mode
 *
 *	Load the timing settings क्रम this device mode पूर्णांकo the
 *	controller when करोing UDMA modes in pass through.
 */

अटल व्योम it821x_tune_udma(ide_drive_t *drive, u8 mode_wanted)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	u8 unit = drive->dn & 1, channel = hwअगर->channel, conf;

	अटल u16 udma[]	= अणु 0x4433, 0x4231, 0x3121, 0x2121, 0x1111, 0x2211, 0x1111 पूर्ण;
	अटल u8 udma_want[]	= अणु ATA_ANY, ATA_50, ATA_ANY, ATA_66, ATA_66, ATA_50, ATA_66 पूर्ण;

	itdev->want[unit][1] = udma_want[mode_wanted];
	itdev->want[unit][0] = 3;	/* UDMA is high priority */
	itdev->mwdma[unit] = MWDMA_OFF;
	itdev->udma[unit] = udma[mode_wanted];
	अगर(mode_wanted >= 5)
		itdev->udma[unit] |= 0x8080;	/* UDMA 5/6 select on */

	/* UDMA on. Again revision 0x10 must करो the pair */
	pci_पढ़ो_config_byte(dev, 0x50, &conf);
	अगर (itdev->timing10)
		conf &= channel ? 0x9F: 0xE7;
	अन्यथा
		conf &= ~ (1 << (3 + 2 * channel + unit));
	pci_ग_लिखो_config_byte(dev, 0x50, conf);

	it821x_घड़ी_strategy(drive);
	it821x_program_udma(drive, itdev->udma[unit]);

पूर्ण

/**
 *	it821x_dma_पढ़ो	-	DMA hook
 *	@drive: drive क्रम DMA
 *
 *	The IT821x has a single timing रेजिस्टर क्रम MWDMA and क्रम PIO
 *	operations. As we flip back and क्रमth we have to reload the
 *	घड़ी. In addition the rev 0x10 device only works अगर the same
 *	timing value is loaded पूर्णांकo the master and slave UDMA घड़ी
 * 	so we must also reload that.
 *
 *	FIXME: we could figure out in advance अगर we need to करो reloads
 */

अटल व्योम it821x_dma_start(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	u8 unit = drive->dn & 1;

	अगर(itdev->mwdma[unit] != MWDMA_OFF)
		it821x_program(drive, itdev->mwdma[unit]);
	अन्यथा अगर(itdev->udma[unit] != UDMA_OFF && itdev->timing10)
		it821x_program_udma(drive, itdev->udma[unit]);
	ide_dma_start(drive);
पूर्ण

/**
 *	it821x_dma_ग_लिखो	-	DMA hook
 *	@drive: drive क्रम DMA stop
 *
 *	The IT821x has a single timing रेजिस्टर क्रम MWDMA and क्रम PIO
 *	operations. As we flip back and क्रमth we have to reload the
 *	घड़ी.
 */

अटल पूर्णांक it821x_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(hwअगर);
	पूर्णांक ret = ide_dma_end(drive);
	u8 unit = drive->dn & 1;

	अगर(itdev->mwdma[unit] != MWDMA_OFF)
		it821x_program(drive, itdev->pio[unit]);
	वापस ret;
पूर्ण

/**
 *	it821x_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Tune the ITE chipset क्रम the desired DMA mode.
 */

अटल व्योम it821x_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	स्थिर u8 speed = drive->dma_mode;

	/*
	 * MWDMA tuning is really hard because our MWDMA and PIO
	 * timings are kept in the same place.  We can चयन in the
	 * host dma on/off callbacks.
	 */
	अगर (speed >= XFER_UDMA_0 && speed <= XFER_UDMA_6)
		it821x_tune_udma(drive, speed - XFER_UDMA_0);
	अन्यथा अगर (speed >= XFER_MW_DMA_0 && speed <= XFER_MW_DMA_2)
		it821x_tune_mwdma(drive, speed - XFER_MW_DMA_0);
पूर्ण

/**
 *	it821x_cable_detect	-	cable detection
 *	@hwअगर: पूर्णांकerface to check
 *
 *	Check क्रम the presence of an ATA66 capable cable on the
 *	पूर्णांकerface. Problematic as it seems some cards करोn't have
 *	the needed logic onboard.
 */

अटल u8 it821x_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	/* The reference driver also only करोes disk side */
	वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	it821x_quirkproc	-	post init callback
 *	@drive: drive
 *
 *	This callback is run after the drive has been probed but
 *	beक्रमe anything माला_लो attached. It allows drivers to करो any
 *	final tuning that is needed, or fixups to work around bugs.
 */

अटल व्योम it821x_quirkproc(ide_drive_t *drive)
अणु
	काष्ठा it821x_dev *itdev = ide_get_hwअगरdata(drive->hwअगर);
	u16 *id = drive->id;

	अगर (!itdev->smart) अणु
		/*
		 *	If we are in pass through mode then not much
		 *	needs to be करोne, but we करो bother to clear the
		 *	IRQ mask as we may well be in PIO (eg rev 0x10)
		 *	क्रम now and we know unmasking is safe on this chipset.
		 */
		drive->dev_flags |= IDE_DFLAG_UNMASK;
	पूर्ण अन्यथा अणु
	/*
	 *	Perक्रमm fixups on smart mode. We need to "lose" some
	 *	capabilities the firmware lacks but करोes not filter, and
	 *	also patch up some capability bits that it क्रममाला_लो to set
	 *	in RAID mode.
	 */

		/* Check क्रम RAID v native */
		अगर (म_माला((अक्षर *)&id[ATA_ID_PROD],
			   "Integrated Technology Express")) अणु
			/* In raid mode the ident block is slightly buggy
			   We need to set the bits so that the IDE layer knows
			   LBA28. LBA48 and DMA ar valid */
			id[ATA_ID_CAPABILITY]    |= (3 << 8); /* LBA28, DMA */
			id[ATA_ID_COMMAND_SET_2] |= 0x0400;   /* LBA48 valid */
			id[ATA_ID_CFS_ENABLE_2]  |= 0x0400;   /* LBA48 on */
			/* Reporting logic */
			prपूर्णांकk(KERN_INFO "%s: IT8212 %sRAID %d volume",
				drive->name, id[147] ? "Bootable " : "",
				id[ATA_ID_CSFO]);
			अगर (id[ATA_ID_CSFO] != 1)
				prपूर्णांकk(KERN_CONT "(%dK stripe)", id[146]);
			prपूर्णांकk(KERN_CONT ".\n");
		पूर्ण अन्यथा अणु
			/* Non RAID volume. Fixups to stop the core code
			   करोing unsupported things */
			id[ATA_ID_FIELD_VALID]	 &= 3;
			id[ATA_ID_QUEUE_DEPTH]	  = 0;
			id[ATA_ID_COMMAND_SET_1]  = 0;
			id[ATA_ID_COMMAND_SET_2] &= 0xC400;
			id[ATA_ID_CFSSE]	 &= 0xC000;
			id[ATA_ID_CFS_ENABLE_1]	  = 0;
			id[ATA_ID_CFS_ENABLE_2]	 &= 0xC400;
			id[ATA_ID_CSF_DEFAULT]	 &= 0xC000;
			id[127]			  = 0;
			id[ATA_ID_DLF]		  = 0;
			id[ATA_ID_CSFO]		  = 0;
			id[ATA_ID_CFA_POWER]	  = 0;
			prपूर्णांकk(KERN_INFO "%s: Performing identify fixups.\n",
				drive->name);
		पूर्ण

		/*
		 * Set MWDMA0 mode as enabled/support - just to tell
		 * IDE core that DMA is supported (it821x hardware
		 * takes care of DMA mode programming).
		 */
		अगर (ata_id_has_dma(id)) अणु
			id[ATA_ID_MWDMA_MODES] |= 0x0101;
			drive->current_speed = XFER_MW_DMA_0;
		पूर्ण
	पूर्ण

पूर्ण

अटल स्थिर काष्ठा ide_dma_ops it821x_pass_through_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= it821x_dma_start,
	.dma_end		= it821x_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

/**
 *	init_hwअगर_it821x	-	set up hwअगर काष्ठाs
 *	@hwअगर: पूर्णांकerface to set up
 *
 *	We करो the basic set up of the पूर्णांकerface काष्ठाure. The IT8212
 *	requires several custom handlers so we override the शेष
 *	ide DMA handlers appropriately
 */

अटल व्योम init_hwअगर_it821x(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा it821x_dev *itdevs = host->host_priv;
	काष्ठा it821x_dev *idev = itdevs + hwअगर->channel;
	u8 conf;

	ide_set_hwअगरdata(hwअगर, idev);

	pci_पढ़ो_config_byte(dev, 0x50, &conf);
	अगर (conf & 1) अणु
		idev->smart = 1;
		hwअगर->host_flags |= IDE_HFLAG_NO_ATAPI_DMA;
		/* Long I/O's although allowed in LBA48 space cause the
		   onboard firmware to enter the twighlight zone */
		hwअगर->rqsize = 256;
	पूर्ण

	/* Pull the current घड़ीs from 0x50 also */
	अगर (conf & (1 << (1 + hwअगर->channel)))
		idev->घड़ी_mode = ATA_50;
	अन्यथा
		idev->घड़ी_mode = ATA_66;

	idev->want[0][1] = ATA_ANY;
	idev->want[1][1] = ATA_ANY;

	/*
	 *	Not in the करोcs but according to the reference driver
	 *	this is necessary.
	 */

	अगर (dev->revision == 0x10) अणु
		idev->timing10 = 1;
		hwअगर->host_flags |= IDE_HFLAG_NO_ATAPI_DMA;
		अगर (idev->smart == 0)
			prपूर्णांकk(KERN_WARNING DRV_NAME " %s: revision 0x10, "
				"workarounds activated\n", pci_name(dev));
	पूर्ण

	अगर (idev->smart == 0) अणु
		/* MWDMA/PIO घड़ी चयनing क्रम pass through mode */
		hwअगर->dma_ops = &it821x_pass_through_dma_ops;
	पूर्ण अन्यथा
		hwअगर->host_flags |= IDE_HFLAG_NO_SET_MODE;

	अगर (hwअगर->dma_base == 0)
		वापस;

	hwअगर->ultra_mask = ATA_UDMA6;
	hwअगर->mwdma_mask = ATA_MWDMA2;

	/* Vortex86SX quirk: prevent Ultra-DMA mode to fix BadCRC issue */
	अगर (idev->quirks & QUIRK_VORTEX86) अणु
		अगर (dev->revision == 0x11)
			hwअगर->ultra_mask = 0;
	पूर्ण
पूर्ण

अटल व्योम it8212_disable_raid(काष्ठा pci_dev *dev)
अणु
	/* Reset local CPU, and set BIOS not पढ़ोy */
	pci_ग_लिखो_config_byte(dev, 0x5E, 0x01);

	/* Set to bypass mode, and reset PCI bus */
	pci_ग_लिखो_config_byte(dev, 0x50, 0x00);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND,
			      PCI_COMMAND_PARITY | PCI_COMMAND_IO |
			      PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	pci_ग_लिखो_config_word(dev, 0x40, 0xA0F3);

	pci_ग_लिखो_config_dword(dev,0x4C, 0x02040204);
	pci_ग_लिखो_config_byte(dev, 0x42, 0x36);
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x20);
पूर्ण

अटल पूर्णांक init_chipset_it821x(काष्ठा pci_dev *dev)
अणु
	u8 conf;
	अटल अक्षर *mode[2] = अणु "pass through", "smart" पूर्ण;

	/* Force the card पूर्णांकo bypass mode अगर so requested */
	अगर (it8212_noraid) अणु
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: forcing bypass mode\n",
			pci_name(dev));
		it8212_disable_raid(dev);
	पूर्ण
	pci_पढ़ो_config_byte(dev, 0x50, &conf);
	prपूर्णांकk(KERN_INFO DRV_NAME " %s: controller in %s mode\n",
		pci_name(dev), mode[conf & 1]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops it821x_port_ops = अणु
	/* it821x_set_अणुpio,dmaपूर्ण_mode() are only used in pass-through mode */
	.set_pio_mode		= it821x_set_pio_mode,
	.set_dma_mode		= it821x_set_dma_mode,
	.quirkproc		= it821x_quirkproc,
	.cable_detect		= it821x_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info it821x_chipset = अणु
	.name		= DRV_NAME,
	.init_chipset	= init_chipset_it821x,
	.init_hwअगर	= init_hwअगर_it821x,
	.port_ops	= &it821x_port_ops,
	.pio_mask	= ATA_PIO4,
पूर्ण;

/**
 *	it821x_init_one	-	pci layer discovery entry
 *	@dev: PCI device
 *	@id: ident table entry
 *
 *	Called by the PCI code when it finds an ITE821x controller.
 *	We then use the IDE PCI generic helper to करो most of the work.
 */

अटल पूर्णांक it821x_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा it821x_dev *itdevs;
	पूर्णांक rc;

	itdevs = kसुस्मृति(2, माप(*itdevs), GFP_KERNEL);
	अगर (itdevs == शून्य) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME " %s: out of memory\n", pci_name(dev));
		वापस -ENOMEM;
	पूर्ण

	itdevs->quirks = id->driver_data;

	rc = ide_pci_init_one(dev, &it821x_chipset, itdevs);
	अगर (rc)
		kमुक्त(itdevs);

	वापस rc;
पूर्ण

अटल व्योम it821x_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा it821x_dev *itdevs = host->host_priv;

	ide_pci_हटाओ(dev);
	kमुक्त(itdevs);
पूर्ण

अटल स्थिर काष्ठा pci_device_id it821x_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8211), 0 पूर्ण,
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8212), 0 पूर्ण,
	अणु PCI_VDEVICE(RDC, PCI_DEVICE_ID_RDC_D1010), QUIRK_VORTEX86 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, it821x_pci_tbl);

अटल काष्ठा pci_driver it821x_pci_driver = अणु
	.name		= "ITE821x IDE",
	.id_table	= it821x_pci_tbl,
	.probe		= it821x_init_one,
	.हटाओ		= it821x_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init it821x_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&it821x_pci_driver);
पूर्ण

अटल व्योम __निकास it821x_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&it821x_pci_driver);
पूर्ण

module_init(it821x_ide_init);
module_निकास(it821x_ide_निकास);

module_param_named(noraid, it8212_noraid, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(noraid, "Force card into bypass mode");

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("PCI driver module for the ITE 821x");
MODULE_LICENSE("GPL");
