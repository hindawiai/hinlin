<शैली गुरु>
/*
 *  Copyright (C) 1998-1999 Andrzej Krzysztofowicz, Author and Maपूर्णांकainer
 *  Copyright (C) 1998-2000 Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2003 Red Hat
 *  Copyright (C) 2006-2007 MontaVista Software, Inc. <source@mvista.com>
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 * Documentation:
 *
 *	Publicly available from Intel web site. Errata करोcumentation
 * is also खुलाly available. As an aide to anyone hacking on this
 * driver the list of errata that are relevant is below.going back to
 * PIIX4. Older device करोcumentation is now a bit tricky to find.
 *
 * Errata of note:
 *
 * Unfixable
 *	PIIX4    errata #9	- Only on ultra obscure hw
 *	ICH3	 errata #13     - Not observed to affect real hw
 *				  by Intel
 *
 * Things we must deal with
 *	PIIX4	errata #10	- BM IDE hang with non UDMA
 *				  (must stop/start dma to recover)
 *	440MX   errata #15	- As PIIX4 errata #10
 *	PIIX4	errata #15	- Must not पढ़ो control रेजिस्टरs
 * 				  during a PIO transfer
 *	440MX   errata #13	- As PIIX4 errata #15
 *	ICH2	errata #21	- DMA mode 0 करोesn't work right
 *	ICH0/1  errata #55	- As ICH2 errata #21
 *	ICH2	spec c #9	- Extra operations needed to handle
 *				  drive hotswap [NOT YET SUPPORTED]
 *	ICH2    spec c #20	- IDE PRD must not cross a 64K boundary
 *				  and must be dword aligned
 *	ICH2    spec c #24	- UDMA mode 4,5 t85/86 should be 6ns not 3.3
 *
 * Should have been BIOS fixed:
 *	450NX:	errata #19	- DMA hangs on old 450NX
 *	450NX:  errata #20	- DMA hangs on old 450NX
 *	450NX:  errata #25	- Corruption with DMA on old 450NX
 *	ICH3    errata #15      - IDE deadlock under high load
 *				  (BIOS must set dev 31 fn 0 bit 23)
 *	ICH3	errata #18	- Don't use native mode
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "piix"

अटल पूर्णांक no_piix_dma;

/**
 *	piix_set_pio_mode	-	set host controller क्रम PIO mode
 *	@port: port
 *	@drive: drive
 *
 *	Set the पूर्णांकerface PIO mode based upon the settings करोne by AMI BIOS.
 */

अटल व्योम piix_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक is_slave		= drive->dn & 1;
	पूर्णांक master_port		= hwअगर->channel ? 0x42 : 0x40;
	पूर्णांक slave_port		= 0x44;
	अचिन्हित दीर्घ flags;
	u16 master_data;
	u8 slave_data;
	अटल DEFINE_SPINLOCK(tune_lock);
	पूर्णांक control = 0;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

				     /* ISP  RTC */
	अटल स्थिर u8 timings[][2]= अणु
					अणु 0, 0 पूर्ण,
					अणु 0, 0 पूर्ण,
					अणु 1, 0 पूर्ण,
					अणु 2, 1 पूर्ण,
					अणु 2, 3 पूर्ण, पूर्ण;

	/*
	 * Master vs slave is synchronized above us but the slave रेजिस्टर is
	 * shared by the two hwअगरs so the corner हाल of two slave समयouts in
	 * parallel must be locked.
	 */
	spin_lock_irqsave(&tune_lock, flags);
	pci_पढ़ो_config_word(dev, master_port, &master_data);

	अगर (pio > 1)
		control |= 1;	/* Programmable timing on */
	अगर (drive->media == ide_disk)
		control |= 4;	/* Prefetch, post ग_लिखो */
	अगर (ide_pio_need_iordy(drive, pio))
		control |= 2;	/* IORDY */
	अगर (is_slave) अणु
		master_data |=  0x4000;
		master_data &= ~0x0070;
		अगर (pio > 1) अणु
			/* Set PPE, IE and TIME */
			master_data |= control << 4;
		पूर्ण
		pci_पढ़ो_config_byte(dev, slave_port, &slave_data);
		slave_data &= hwअगर->channel ? 0x0f : 0xf0;
		slave_data |= ((timings[pio][0] << 2) | timings[pio][1]) <<
			       (hwअगर->channel ? 4 : 0);
	पूर्ण अन्यथा अणु
		master_data &= ~0x3307;
		अगर (pio > 1) अणु
			/* enable PPE, IE and TIME */
			master_data |= control;
		पूर्ण
		master_data |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	पूर्ण
	pci_ग_लिखो_config_word(dev, master_port, master_data);
	अगर (is_slave)
		pci_ग_लिखो_config_byte(dev, slave_port, slave_data);
	spin_unlock_irqrestore(&tune_lock, flags);
पूर्ण

/**
 *	piix_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Set a PIIX host controller to the desired DMA mode.  This involves
 *	programming the right timing data पूर्णांकo the PCI configuration space.
 */

अटल व्योम piix_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 maslave		= hwअगर->channel ? 0x42 : 0x40;
	पूर्णांक a_speed		= 3 << (drive->dn * 4);
	पूर्णांक u_flag		= 1 << drive->dn;
	पूर्णांक v_flag		= 0x01 << drive->dn;
	पूर्णांक w_flag		= 0x10 << drive->dn;
	पूर्णांक u_speed		= 0;
	पूर्णांक			sitre;
	u16			reg4042, reg4a;
	u8			reg48, reg54, reg55;
	स्थिर u8 speed		= drive->dma_mode;

	pci_पढ़ो_config_word(dev, maslave, &reg4042);
	sitre = (reg4042 & 0x4000) ? 1 : 0;
	pci_पढ़ो_config_byte(dev, 0x48, &reg48);
	pci_पढ़ो_config_word(dev, 0x4a, &reg4a);
	pci_पढ़ो_config_byte(dev, 0x54, &reg54);
	pci_पढ़ो_config_byte(dev, 0x55, &reg55);

	अगर (speed >= XFER_UDMA_0) अणु
		u8 udma = speed - XFER_UDMA_0;

		u_speed = min_t(u8, 2 - (udma & 1), udma) << (drive->dn * 4);

		अगर (!(reg48 & u_flag))
			pci_ग_लिखो_config_byte(dev, 0x48, reg48 | u_flag);
		अगर (speed == XFER_UDMA_5) अणु
			pci_ग_लिखो_config_byte(dev, 0x55, (u8) reg55|w_flag);
		पूर्ण अन्यथा अणु
			pci_ग_लिखो_config_byte(dev, 0x55, (u8) reg55 & ~w_flag);
		पूर्ण
		अगर ((reg4a & a_speed) != u_speed)
			pci_ग_लिखो_config_word(dev, 0x4a, (reg4a & ~a_speed) | u_speed);
		अगर (speed > XFER_UDMA_2) अणु
			अगर (!(reg54 & v_flag))
				pci_ग_लिखो_config_byte(dev, 0x54, reg54 | v_flag);
		पूर्ण अन्यथा
			pci_ग_लिखो_config_byte(dev, 0x54, reg54 & ~v_flag);
	पूर्ण अन्यथा अणु
		स्थिर u8 mwdma_to_pio[] = अणु 0, 3, 4 पूर्ण;

		अगर (reg48 & u_flag)
			pci_ग_लिखो_config_byte(dev, 0x48, reg48 & ~u_flag);
		अगर (reg4a & a_speed)
			pci_ग_लिखो_config_word(dev, 0x4a, reg4a & ~a_speed);
		अगर (reg54 & v_flag)
			pci_ग_लिखो_config_byte(dev, 0x54, reg54 & ~v_flag);
		अगर (reg55 & w_flag)
			pci_ग_लिखो_config_byte(dev, 0x55, (u8) reg55 & ~w_flag);

		अगर (speed >= XFER_MW_DMA_0)
			drive->pio_mode =
				mwdma_to_pio[speed - XFER_MW_DMA_0] + XFER_PIO_0;
		अन्यथा
			drive->pio_mode = XFER_PIO_2; /* क्रम SWDMA2 */

		piix_set_pio_mode(hwअगर, drive);
	पूर्ण
पूर्ण

/**
 *	init_chipset_ich	-	set up the ICH chipset
 *	@dev: PCI device to set up
 *
 *	Initialize the PCI device as required.  For the ICH this turns
 *	out to be nice and simple.
 */

अटल पूर्णांक init_chipset_ich(काष्ठा pci_dev *dev)
अणु
	u32 extra = 0;

	pci_पढ़ो_config_dword(dev, 0x54, &extra);
	pci_ग_लिखो_config_dword(dev, 0x54, extra | 0x400);

	वापस 0;
पूर्ण

/**
 *	ich_clear_irq	-	clear BMDMA status
 *	@drive: IDE drive
 *
 *	ICHx contollers set DMA INTR no matter DMA or PIO.
 *	BMDMA status might need to be cleared even क्रम
 *	PIO पूर्णांकerrupts to prevent spurious/lost IRQ.
 */
अटल व्योम ich_clear_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat;

	/*
	 * ide_dma_end() needs BMDMA status क्रम error checking.
	 * So, skip clearing BMDMA status here and leave it
	 * to ide_dma_end() अगर this is DMA पूर्णांकerrupt.
	 */
	अगर (drive->रुकोing_क्रम_dma || hwअगर->dma_base == 0)
		वापस;

	/* clear the INTR & ERROR bits */
	dma_stat = inb(hwअगर->dma_base + ATA_DMA_STATUS);
	/* Should we क्रमce the bit as well ? */
	outb(dma_stat, hwअगर->dma_base + ATA_DMA_STATUS);
पूर्ण

काष्ठा ich_laptop अणु
	u16 device;
	u16 subvenकरोr;
	u16 subdevice;
पूर्ण;

/*
 *	List of laptops that use लघु cables rather than 80 wire
 */

अटल स्थिर काष्ठा ich_laptop ich_laptop[] = अणु
	/* devid, subvenकरोr, subdev */
	अणु 0x27DF, 0x1025, 0x0102 पूर्ण,	/* ICH7 on Acer 5602aWLMi */
	अणु 0x27DF, 0x0005, 0x0280 पूर्ण,	/* ICH7 on Acer 5602WLMi */
	अणु 0x27DF, 0x1025, 0x0110 पूर्ण,	/* ICH7 on Acer 3682WLMi */
	अणु 0x27DF, 0x1043, 0x1267 पूर्ण,	/* ICH7 on Asus W5F */
	अणु 0x27DF, 0x103C, 0x30A1 पूर्ण,	/* ICH7 on HP Compaq nc2400 */
	अणु 0x27DF, 0x1071, 0xD221 पूर्ण,	/* ICH7 on Hercules EC-900 */
	अणु 0x24CA, 0x1025, 0x0061 पूर्ण,	/* ICH4 on Acer Aspire 2023WLMi */
	अणु 0x24CA, 0x1025, 0x003d पूर्ण,	/* ICH4 on ACER TM290 */
	अणु 0x266F, 0x1025, 0x0066 पूर्ण,	/* ICH6 on ACER Aspire 1694WLMi */
	अणु 0x2653, 0x1043, 0x82D8 पूर्ण,	/* ICH6M on Asus Eee 701 */
	अणु 0x27df, 0x104d, 0x900e पूर्ण,	/* ICH7 on Sony TZ-90 */
	/* end marker */
	अणु 0, पूर्ण
पूर्ण;

अटल u8 piix_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	स्थिर काष्ठा ich_laptop *lap = &ich_laptop[0];
	u8 reg54h = 0, mask = hwअगर->channel ? 0xc0 : 0x30;

	/* check क्रम specials */
	जबतक (lap->device) अणु
		अगर (lap->device == pdev->device &&
		    lap->subvenकरोr == pdev->subप्रणाली_venकरोr &&
		    lap->subdevice == pdev->subप्रणाली_device) अणु
			वापस ATA_CBL_PATA40_SHORT;
		पूर्ण
		lap++;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, 0x54, &reg54h);

	वापस (reg54h & mask) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
पूर्ण

/**
 *	init_hwअगर_piix		-	fill in the hwअगर क्रम the PIIX
 *	@hwअगर: IDE पूर्णांकerface
 *
 *	Set up the ide_hwअगर_t क्रम the PIIX पूर्णांकerface according to the
 *	capabilities of the hardware.
 */

अटल व्योम init_hwअगर_piix(ide_hwअगर_t *hwअगर)
अणु
	अगर (!hwअगर->dma_base)
		वापस;

	अगर (no_piix_dma)
		hwअगर->ultra_mask = hwअगर->mwdma_mask = hwअगर->swdma_mask = 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops piix_port_ops = अणु
	.set_pio_mode		= piix_set_pio_mode,
	.set_dma_mode		= piix_set_dma_mode,
	.cable_detect		= piix_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops ich_port_ops = अणु
	.set_pio_mode		= piix_set_pio_mode,
	.set_dma_mode		= piix_set_dma_mode,
	.clear_irq		= ich_clear_irq,
	.cable_detect		= piix_cable_detect,
पूर्ण;

#घोषणा DECLARE_PIIX_DEV(udma) \
	अणु						\
		.name		= DRV_NAME,		\
		.init_hwअगर	= init_hwअगर_piix,	\
		.enablebits	= अणुअणु0x41,0x80,0x80पूर्ण, अणु0x43,0x80,0x80पूर्णपूर्ण, \
		.port_ops	= &piix_port_ops,	\
		.pio_mask	= ATA_PIO4,		\
		.swdma_mask	= ATA_SWDMA2_ONLY,	\
		.mwdma_mask	= ATA_MWDMA12_ONLY,	\
		.udma_mask	= udma,			\
	पूर्ण

#घोषणा DECLARE_ICH_DEV(mwdma, udma) \
	अणु \
		.name		= DRV_NAME, \
		.init_chipset	= init_chipset_ich, \
		.init_hwअगर	= init_hwअगर_piix, \
		.enablebits	= अणुअणु0x41,0x80,0x80पूर्ण, अणु0x43,0x80,0x80पूर्णपूर्ण, \
		.port_ops	= &ich_port_ops, \
		.pio_mask	= ATA_PIO4, \
		.swdma_mask	= ATA_SWDMA2_ONLY, \
		.mwdma_mask	= mwdma, \
		.udma_mask	= udma, \
	पूर्ण

अटल स्थिर काष्ठा ide_port_info piix_pci_info[] = अणु
	/* 0: MPIIX */
	अणु	/*
		 * MPIIX actually has only a single IDE channel mapped to
		 * the primary or secondary ports depending on the value
		 * of the bit 14 of the IDETIM रेजिस्टर at offset 0x6c
		 */
		.name		= DRV_NAME,
		.enablebits	= अणुअणु0x6d,0xc0,0x80पूर्ण, अणु0x6d,0xc0,0xc0पूर्णपूर्ण,
		.host_flags	= IDE_HFLAG_ISA_PORTS | IDE_HFLAG_NO_DMA,
		.pio_mask	= ATA_PIO4,
		/* This is a painful प्रणाली best to let it self tune क्रम now */
	पूर्ण,
	/* 1: PIIXa/PIIXb/PIIX3 */
	DECLARE_PIIX_DEV(0x00), /* no udma */
	/* 2: PIIX4 */
	DECLARE_PIIX_DEV(ATA_UDMA2),
	/* 3: ICH0 */
	DECLARE_ICH_DEV(ATA_MWDMA12_ONLY, ATA_UDMA2),
	/* 4: ICH */
	DECLARE_ICH_DEV(ATA_MWDMA12_ONLY, ATA_UDMA4),
	/* 5: PIIX4 */
	DECLARE_PIIX_DEV(ATA_UDMA4),
	/* 6: ICH[2-6]/ICH[2-3]M/C-ICH/ICH5-SATA/ESB2/ICH8M */
	DECLARE_ICH_DEV(ATA_MWDMA12_ONLY, ATA_UDMA5),
	/* 7: ICH7/7-R, no MWDMA1 */
	DECLARE_ICH_DEV(ATA_MWDMA2_ONLY, ATA_UDMA5),
पूर्ण;

/**
 *	piix_init_one	-	called when a PIIX is found
 *	@dev: the piix device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */
 
अटल पूर्णांक piix_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &piix_pci_info[id->driver_data], शून्य);
पूर्ण

/**
 *	piix_check_450nx	-	Check क्रम problem 450NX setup
 *	
 *	Check क्रम the present of 450NX errata #19 and errata #25. If
 *	they are found, disable use of DMA IDE
 */

अटल व्योम piix_check_450nx(व्योम)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	u16 cfg;
	जबतक((pdev=pci_get_device(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82454NX, pdev))!=शून्य)
	अणु
		/* Look क्रम 450NX PXB. Check क्रम problem configurations
		   A PCI quirk checks bit 6 alपढ़ोy */
		pci_पढ़ो_config_word(pdev, 0x41, &cfg);
		/* Only on the original revision: IDE DMA can hang */
		अगर (pdev->revision == 0x00)
			no_piix_dma = 1;
		/* On all revisions below 5 PXB bus lock must be disabled क्रम IDE */
		अन्यथा अगर (cfg & (1<<14) && pdev->revision < 5)
			no_piix_dma = 2;
	पूर्ण
	अगर(no_piix_dma)
		prपूर्णांकk(KERN_WARNING DRV_NAME ": 450NX errata present, disabling IDE DMA.\n");
	अगर(no_piix_dma == 2)
		prपूर्णांकk(KERN_WARNING DRV_NAME ": A BIOS update may resolve this.\n");
पूर्ण		

अटल स्थिर काष्ठा pci_device_id piix_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82371FB_0),  1 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82371FB_1),  1 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82371MX),    0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82371SB_1),  1 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82371AB),    2 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801AB_1),  3 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82443MX_1),  2 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801AA_1),  4 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82372FB_1),  5 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82451NX),    2 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801BA_9),  6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801BA_8),  6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801CA_10), 6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801CA_11), 6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801DB_11), 6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801EB_11), 6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801E_11),  6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801DB_10), 6 पूर्ण,
#अगर_घोषित CONFIG_BLK_DEV_IDE_SATA
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801EB_1),  6 पूर्ण,
#पूर्ण_अगर
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ESB_2),      6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ICH6_19),    6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ICH7_21),    7 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82801DB_1),  6 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ESB2_18),    7 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ICH8_6),     6 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, piix_pci_tbl);

अटल काष्ठा pci_driver piix_pci_driver = अणु
	.name		= "PIIX_IDE",
	.id_table	= piix_pci_tbl,
	.probe		= piix_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init piix_ide_init(व्योम)
अणु
	piix_check_450nx();
	वापस ide_pci_रेजिस्टर_driver(&piix_pci_driver);
पूर्ण

अटल व्योम __निकास piix_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&piix_pci_driver);
पूर्ण

module_init(piix_ide_init);
module_निकास(piix_ide_निकास);

MODULE_AUTHOR("Andre Hedrick, Andrzej Krzysztofowicz");
MODULE_DESCRIPTION("PCI driver module for Intel PIIX IDE");
MODULE_LICENSE("GPL");
