<शैली गुरु>
/*
 *  Copyright (C) 1998-2000 Michel Aubry, Maपूर्णांकainer
 *  Copyright (C) 1998-2000 Andrzej Krzysztofowicz, Maपूर्णांकainer
 *  Copyright (C) 1999-2000 CJ, cjtsai@ali.com.tw, Maपूर्णांकainer
 *
 *  Copyright (C) 1998-2000 Andre Hedrick (andre@linux-ide.org)
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *  Copyright (C) 2002 Alan Cox
 *  ALi (now ULi M5228) support by Clear Zhang <Clear.Zhang@ali.com.tw>
 *  Copyright (C) 2007 MontaVista Software, Inc. <source@mvista.com>
 *  Copyright (C) 2007-2010 Bartlomiej Zolnierkiewicz
 *
 *  (U)DMA capable version of ali 1533/1543(C), 1535(D)
 *
 **********************************************************************
 *  9/7/99 --Parts from the above author are included and need to be
 *  converted पूर्णांकo standard पूर्णांकerface, once I finish the thought.
 *
 *  Recent changes
 *	Don't use LBA48 mode on ALi <= 0xC4
 *	Don't poke 0x79 with a non ALi northbridge
 *	Don't flip undefined bits on newer chipsets (fix Fujitsu laptop hang)
 *	Allow UDMA6 on revisions > 0xC4
 *
 *  Documentation
 *	Chipset करोcumentation available under NDA only
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "alim15x3"

/*
 *	ALi devices are not plug in. Otherwise these अटल values would
 *	need to go. They ought to go away anyway
 */
 
अटल u8 m5229_revision;
अटल u8 chip_is_1543c_e;
अटल काष्ठा pci_dev *isa_dev;

अटल व्योम ali_fअगरo_control(ide_hwअगर_t *hwअगर, ide_drive_t *drive, पूर्णांक on)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	पूर्णांक pio_fअगरo = 0x54 + hwअगर->channel;
	u8 fअगरo;
	पूर्णांक shअगरt = 4 * (drive->dn & 1);

	pci_पढ़ो_config_byte(pdev, pio_fअगरo, &fअगरo);
	fअगरo &= ~(0x0F << shअगरt);
	fअगरo |= (on << shअगरt);
	pci_ग_लिखो_config_byte(pdev, pio_fअगरo, fअगरo);
पूर्ण

अटल व्योम ali_program_timings(ide_hwअगर_t *hwअगर, ide_drive_t *drive,
				काष्ठा ide_timing *t, u8 ultra)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	पूर्णांक port = hwअगर->channel ? 0x5c : 0x58;
	पूर्णांक udmat = 0x56 + hwअगर->channel;
	u8 unit = drive->dn & 1, udma;
	पूर्णांक shअगरt = 4 * unit;

	/* Set up the UDMA */
	pci_पढ़ो_config_byte(dev, udmat, &udma);
	udma &= ~(0x0F << shअगरt);
	udma |= ultra << shअगरt;
	pci_ग_लिखो_config_byte(dev, udmat, udma);

	अगर (t == शून्य)
		वापस;

	t->setup = clamp_val(t->setup, 1, 8) & 7;
	t->act8b = clamp_val(t->act8b, 1, 8) & 7;
	t->rec8b = clamp_val(t->rec8b, 1, 16) & 15;
	t->active = clamp_val(t->active, 1, 8) & 7;
	t->recover = clamp_val(t->recover, 1, 16) & 15;

	pci_ग_लिखो_config_byte(dev, port, t->setup);
	pci_ग_लिखो_config_byte(dev, port + 1, (t->act8b << 4) | t->rec8b);
	pci_ग_लिखो_config_byte(dev, port + unit + 2,
			      (t->active << 4) | t->recover);
पूर्ण

/**
 *	ali_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Program the controller क्रम the given PIO mode.
 */

अटल व्योम ali_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	ide_drive_t *pair = ide_get_pair_dev(drive);
	पूर्णांक bus_speed = ide_pci_clk ? ide_pci_clk : 33;
	अचिन्हित दीर्घ T =  1000000 / bus_speed; /* PCI घड़ी based */
	काष्ठा ide_timing t;

	ide_timing_compute(drive, drive->pio_mode, &t, T, 1);
	अगर (pair) अणु
		काष्ठा ide_timing p;

		ide_timing_compute(pair, pair->pio_mode, &p, T, 1);
		ide_timing_merge(&p, &t, &t,
			IDE_TIMING_SETUP | IDE_TIMING_8BIT);
		अगर (pair->dma_mode) अणु
			ide_timing_compute(pair, pair->dma_mode, &p, T, 1);
			ide_timing_merge(&p, &t, &t,
				IDE_TIMING_SETUP | IDE_TIMING_8BIT);
		पूर्ण
	पूर्ण

	/* 
	 * PIO mode => ATA FIFO on, ATAPI FIFO off
	 */
	ali_fअगरo_control(hwअगर, drive, (drive->media == ide_disk) ? 0x05 : 0x00);

	ali_program_timings(hwअगर, drive, &t, 0);
पूर्ण

/**
 *	ali_udma_filter		-	compute UDMA mask
 *	@drive: IDE device
 *
 *	Return available UDMA modes.
 *
 *	The actual rules क्रम the ALi are:
 *		No UDMA on revisions <= 0x20
 *		Disk only क्रम revisions < 0xC2
 *		Not WDC drives on M1543C-E (?)
 */

अटल u8 ali_udma_filter(ide_drive_t *drive)
अणु
	अगर (m5229_revision > 0x20 && m5229_revision < 0xC2) अणु
		अगर (drive->media != ide_disk)
			वापस 0;
		अगर (chip_is_1543c_e &&
		    म_माला((अक्षर *)&drive->id[ATA_ID_PROD], "WDC "))
			वापस 0;
	पूर्ण

	वापस drive->hwअगर->ultra_mask;
पूर्ण

/**
 *	ali_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Configure the hardware क्रम the desired IDE transfer mode.
 */

अटल व्योम ali_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल u8 udma_timing[7] = अणु 0xC, 0xB, 0xA, 0x9, 0x8, 0xF, 0xD पूर्ण;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	ide_drive_t *pair	= ide_get_pair_dev(drive);
	पूर्णांक bus_speed		= ide_pci_clk ? ide_pci_clk : 33;
	अचिन्हित दीर्घ T		=  1000000 / bus_speed; /* PCI घड़ी based */
	स्थिर u8 speed		= drive->dma_mode;
	u8 पंचांगpbyte		= 0x00;
	काष्ठा ide_timing t;

	अगर (speed < XFER_UDMA_0) अणु
		ide_timing_compute(drive, drive->dma_mode, &t, T, 1);
		अगर (pair) अणु
			काष्ठा ide_timing p;

			ide_timing_compute(pair, pair->pio_mode, &p, T, 1);
			ide_timing_merge(&p, &t, &t,
				IDE_TIMING_SETUP | IDE_TIMING_8BIT);
			अगर (pair->dma_mode) अणु
				ide_timing_compute(pair, pair->dma_mode,
						&p, T, 1);
				ide_timing_merge(&p, &t, &t,
					IDE_TIMING_SETUP | IDE_TIMING_8BIT);
			पूर्ण
		पूर्ण
		ali_program_timings(hwअगर, drive, &t, 0);
	पूर्ण अन्यथा अणु
		ali_program_timings(hwअगर, drive, शून्य,
				udma_timing[speed - XFER_UDMA_0]);
		अगर (speed >= XFER_UDMA_3) अणु
			pci_पढ़ो_config_byte(dev, 0x4b, &पंचांगpbyte);
			पंचांगpbyte |= 1;
			pci_ग_लिखो_config_byte(dev, 0x4b, पंचांगpbyte);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	ali_dma_check	-	DMA check
 *	@drive:	target device
 *	@cmd: command
 *
 *	Returns 1 अगर the DMA cannot be perक्रमmed, zero on success.
 */

अटल पूर्णांक ali_dma_check(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	अगर (m5229_revision < 0xC2 && drive->media != ide_disk) अणु
		अगर (cmd->tf_flags & IDE_TFLAG_WRITE)
			वापस 1;	/* try PIO instead of DMA */
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	init_chipset_ali15x3	-	Initialise an ALi IDE controller
 *	@dev: PCI device
 *
 *	This function initializes the ALI IDE controller and where 
 *	appropriate also sets up the 1533 southbridge.
 */

अटल पूर्णांक init_chipset_ali15x3(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	u8 पंचांगpbyte;
	काष्ठा pci_dev *north = pci_get_slot(dev->bus, PCI_DEVFN(0,0));

	m5229_revision = dev->revision;

	isa_dev = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1533, शून्य);

	local_irq_save(flags);

	अगर (m5229_revision < 0xC2) अणु
		/*
		 * revision 0x20 (1543-E, 1543-F)
		 * revision 0xC0, 0xC1 (1543C-C, 1543C-D, 1543C-E)
		 * clear CD-ROM DMA ग_लिखो bit, m5229, 0x4b, bit 7
		 */
		pci_पढ़ो_config_byte(dev, 0x4b, &पंचांगpbyte);
		/*
		 * clear bit 7
		 */
		pci_ग_लिखो_config_byte(dev, 0x4b, पंचांगpbyte & 0x7F);
		/*
		 * check m1533, 0x5e, bit 1~4 == 1001 => & 00011110 = 00010010
		 */
		अगर (m5229_revision >= 0x20 && isa_dev) अणु
			pci_पढ़ो_config_byte(isa_dev, 0x5e, &पंचांगpbyte);
			chip_is_1543c_e = ((पंचांगpbyte & 0x1e) == 0x12) ? 1: 0;
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * 1543C-B?, 1535, 1535D, 1553
	 * Note 1: not all "motherboard" support this detection
	 * Note 2: अगर no udma 66 device, the detection may "error".
	 *         but in this हाल, we will not set the device to
	 *         ultra 66, the detection result is not important
	 */

	/*
	 * enable "Cable Detection", m5229, 0x4b, bit3
	 */
	pci_पढ़ो_config_byte(dev, 0x4b, &पंचांगpbyte);
	pci_ग_लिखो_config_byte(dev, 0x4b, पंचांगpbyte | 0x08);

	/*
	 * We should only tune the 1533 enable अगर we are using an ALi
	 * North bridge. We might have no north found on some zany
	 * box without a device at 0:0.0. The ALi bridge will be at
	 * 0:0.0 so अगर we didn't find one we know what is cooking.
	 */
	अगर (north && north->venकरोr != PCI_VENDOR_ID_AL)
		जाओ out;

	अगर (m5229_revision < 0xC5 && isa_dev)
	अणु	
		/*
		 * set south-bridge's enable bit, m1533, 0x79
		 */

		pci_पढ़ो_config_byte(isa_dev, 0x79, &पंचांगpbyte);
		अगर (m5229_revision == 0xC2) अणु
			/*
			 * 1543C-B0 (m1533, 0x79, bit 2)
			 */
			pci_ग_लिखो_config_byte(isa_dev, 0x79, पंचांगpbyte | 0x04);
		पूर्ण अन्यथा अगर (m5229_revision >= 0xC3) अणु
			/*
			 * 1553/1535 (m1533, 0x79, bit 1)
			 */
			pci_ग_लिखो_config_byte(isa_dev, 0x79, पंचांगpbyte | 0x02);
		पूर्ण
	पूर्ण

out:
	/*
	 * CD_ROM DMA on (m5229, 0x53, bit0)
	 *      Enable this bit even अगर we want to use PIO.
	 * PIO FIFO off (m5229, 0x53, bit1)
	 *      The hardware will use 0x54h and 0x55h to control PIO FIFO.
	 *	(Not on later devices it seems)
	 *
	 *	0x53 changes meaning on later revs - we must no touch
	 *	bit 1 on them.  Need to check अगर 0x20 is the right अवरोध.
	 */
	अगर (m5229_revision >= 0x20) अणु
		pci_पढ़ो_config_byte(dev, 0x53, &पंचांगpbyte);

		अगर (m5229_revision <= 0x20)
			पंचांगpbyte = (पंचांगpbyte & (~0x02)) | 0x01;
		अन्यथा अगर (m5229_revision == 0xc7 || m5229_revision == 0xc8)
			पंचांगpbyte |= 0x03;
		अन्यथा
			पंचांगpbyte |= 0x01;

		pci_ग_लिखो_config_byte(dev, 0x53, पंचांगpbyte);
	पूर्ण
	local_irq_restore(flags);
	pci_dev_put(north);
	pci_dev_put(isa_dev);
	वापस 0;
पूर्ण

/*
 *	Cable special हालs
 */

अटल स्थिर काष्ठा dmi_प्रणाली_id cable_dmi_table[] = अणु
	अणु
		.ident = "HP Pavilion N5430",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_BOARD_VERSION, "OmniBook N32N-736"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Toshiba Satellite S1800-814",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "S1800-814"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक ali_cable_override(काष्ठा pci_dev *pdev)
अणु
	/* Fujitsu P2000 */
	अगर (pdev->subप्रणाली_venकरोr == 0x10CF &&
	    pdev->subप्रणाली_device == 0x10AF)
		वापस 1;

	/* Mitac 8317 (Winbook-A) and relatives */
	अगर (pdev->subप्रणाली_venकरोr == 0x1071 &&
	    pdev->subप्रणाली_device == 0x8317)
		वापस 1;

	/* Systems by DMI */
	अगर (dmi_check_प्रणाली(cable_dmi_table))
		वापस 1;

	वापस 0;
पूर्ण

/**
 *	ali_cable_detect	-	cable detection
 *	@hwअगर: IDE पूर्णांकerface
 *
 *	This checks अगर the controller and the cable are capable
 *	of UDMA66 transfers. It करोesn't check the drives.
 */

अटल u8 ali_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 cbl = ATA_CBL_PATA40, पंचांगpbyte;

	अगर (m5229_revision >= 0xC2) अणु
		/*
		 * m5229 80-pin cable detection (from Host View)
		 *
		 * 0x4a bit0 is 0 => primary channel has 80-pin
		 * 0x4a bit1 is 0 => secondary channel has 80-pin
		 *
		 * Certain laptops use लघु but suitable cables
		 * and करोn't implement the detect logic.
		 */
		अगर (ali_cable_override(dev))
			cbl = ATA_CBL_PATA40_SHORT;
		अन्यथा अणु
			pci_पढ़ो_config_byte(dev, 0x4a, &पंचांगpbyte);
			अगर ((पंचांगpbyte & (1 << hwअगर->channel)) == 0)
				cbl = ATA_CBL_PATA80;
		पूर्ण
	पूर्ण

	वापस cbl;
पूर्ण

#अगर_अघोषित CONFIG_SPARC64
/**
 *	init_hwअगर_ali15x3	-	Initialize the ALI IDE x86 stuff
 *	@hwअगर: पूर्णांकerface to configure
 *
 *	Obtain the IRQ tables क्रम an ALi based IDE solution on the PC
 *	class platक्रमms. This part of the code isn't applicable to the
 *	Sparc प्रणालीs.
 */

अटल व्योम init_hwअगर_ali15x3(ide_hwअगर_t *hwअगर)
अणु
	u8 ideic, inmir;
	s8 irq_routing_table[] = अणु -1,  9, 3, 10, 4,  5, 7,  6,
				      1, 11, 0, 12, 0, 14, 0, 15 पूर्ण;
	पूर्णांक irq = -1;

	अगर (isa_dev) अणु
		/*
		 * पढ़ो IDE पूर्णांकerface control
		 */
		pci_पढ़ो_config_byte(isa_dev, 0x58, &ideic);

		/* bit0, bit1 */
		ideic = ideic & 0x03;

		/* get IRQ क्रम IDE Controller */
		अगर ((hwअगर->channel && ideic == 0x03) ||
		    (!hwअगर->channel && !ideic)) अणु
			/*
			 * get SIRQ1 routing table
			 */
			pci_पढ़ो_config_byte(isa_dev, 0x44, &inmir);
			inmir = inmir & 0x0f;
			irq = irq_routing_table[inmir];
		पूर्ण अन्यथा अगर (hwअगर->channel && !(ideic & 0x01)) अणु
			/*
			 * get SIRQ2 routing table
			 */
			pci_पढ़ो_config_byte(isa_dev, 0x75, &inmir);
			inmir = inmir & 0x0f;
			irq = irq_routing_table[inmir];
		पूर्ण
		अगर(irq >= 0)
			hwअगर->irq = irq;
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा init_hwअगर_ali15x3 शून्य
#पूर्ण_अगर /* CONFIG_SPARC64 */

/**
 *	init_dma_ali15x3	-	set up DMA on ALi15x3
 *	@hwअगर: IDE पूर्णांकerface
 *	@d: IDE port info
 *
 *	Set up the DMA functionality on the ALi 15x3.
 */

अटल पूर्णांक init_dma_ali15x3(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ base = ide_pci_dma_base(hwअगर, d);

	अगर (base == 0)
		वापस -1;

	hwअगर->dma_base = base;

	अगर (ide_pci_check_simplex(hwअगर, d) < 0)
		वापस -1;

	अगर (ide_pci_set_master(dev, d->name) < 0)
		वापस -1;

	अगर (!hwअगर->channel)
		outb(inb(base + 2) & 0x60, base + 2);

	prपूर्णांकk(KERN_INFO "    %s: BM-DMA at 0x%04lx-0x%04lx\n",
			 hwअगर->name, base, base + 7);

	अगर (ide_allocate_dma_engine(hwअगर))
		वापस -1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops ali_port_ops = अणु
	.set_pio_mode		= ali_set_pio_mode,
	.set_dma_mode		= ali_set_dma_mode,
	.udma_filter		= ali_udma_filter,
	.cable_detect		= ali_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops ali_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= ide_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_check		= ali_dma_check,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info ali15x3_chipset = अणु
	.name		= DRV_NAME,
	.init_chipset	= init_chipset_ali15x3,
	.init_hwअगर	= init_hwअगर_ali15x3,
	.init_dma	= init_dma_ali15x3,
	.port_ops	= &ali_port_ops,
	.dma_ops	= &sff_dma_ops,
	.pio_mask	= ATA_PIO5,
	.swdma_mask	= ATA_SWDMA2,
	.mwdma_mask	= ATA_MWDMA2,
पूर्ण;

/**
 *	alim15x3_init_one	-	set up an ALi15x3 IDE controller
 *	@dev: PCI device to set up
 *
 *	Perक्रमm the actual set up क्रम an ALi15x3 that has been found by the
 *	hot plug layer.
 */
 
अटल पूर्णांक alim15x3_init_one(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d = ali15x3_chipset;
	u8 rev = dev->revision, idx = id->driver_data;

	/* करोn't use LBA48 DMA on ALi devices beक्रमe rev 0xC5 */
	अगर (rev <= 0xC4)
		d.host_flags |= IDE_HFLAG_NO_LBA48_DMA;

	अगर (rev >= 0x20) अणु
		अगर (rev == 0x20)
			d.host_flags |= IDE_HFLAG_NO_ATAPI_DMA;

		अगर (rev < 0xC2)
			d.udma_mask = ATA_UDMA2;
		अन्यथा अगर (rev == 0xC2 || rev == 0xC3)
			d.udma_mask = ATA_UDMA4;
		अन्यथा अगर (rev == 0xC4)
			d.udma_mask = ATA_UDMA5;
		अन्यथा
			d.udma_mask = ATA_UDMA6;

		d.dma_ops = &ali_dma_ops;
	पूर्ण अन्यथा अणु
		d.host_flags |= IDE_HFLAG_NO_DMA;

		d.mwdma_mask = d.swdma_mask = 0;
	पूर्ण

	अगर (idx == 0)
		d.host_flags |= IDE_HFLAG_CLEAR_SIMPLEX;

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण


अटल स्थिर काष्ठा pci_device_id alim15x3_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AL, PCI_DEVICE_ID_AL_M5229), 0 पूर्ण,
	अणु PCI_VDEVICE(AL, PCI_DEVICE_ID_AL_M5228), 1 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, alim15x3_pci_tbl);

अटल काष्ठा pci_driver alim15x3_pci_driver = अणु
	.name		= "ALI15x3_IDE",
	.id_table	= alim15x3_pci_tbl,
	.probe		= alim15x3_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init ali15x3_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&alim15x3_pci_driver);
पूर्ण

अटल व्योम __निकास ali15x3_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&alim15x3_pci_driver);
पूर्ण

module_init(ali15x3_ide_init);
module_निकास(ali15x3_ide_निकास);

MODULE_AUTHOR("Michael Aubry, Andrzej Krzysztofowicz, CJ, Andre Hedrick, Alan Cox, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("PCI driver module for ALi 15x3 IDE");
MODULE_LICENSE("GPL");
