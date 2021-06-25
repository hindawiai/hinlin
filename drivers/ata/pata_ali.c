<शैली गुरु>
/*
 * pata_ali.c 	- ALI 15x3 PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *
 * based in part upon
 * linux/drivers/ide/pci/alim15x3.c		Version 0.17	2003/01/02
 *
 *  Copyright (C) 1998-2000 Michel Aubry, Maपूर्णांकainer
 *  Copyright (C) 1998-2000 Andrzej Krzysztofowicz, Maपूर्णांकainer
 *  Copyright (C) 1999-2000 CJ, cjtsai@ali.com.tw, Maपूर्णांकainer
 *
 *  Copyright (C) 1998-2000 Andre Hedrick (andre@linux-ide.org)
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *  Copyright (C) 2002 Alan Cox <alan@redhat.com>
 *  ALi (now ULi M5228) support by Clear Zhang <Clear.Zhang@ali.com.tw>
 *
 *  Documentation
 *	Chipset करोcumentation available under NDA only
 *
 *  TODO/CHECK
 *	Cannot have ATAPI on both master & slave क्रम rev < c2 (???) but
 *	otherwise should करो atapi DMA (For now क्रम old we करो PIO only क्रम
 *	ATAPI)
 *	Review Sunblade workaround.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME "pata_ali"
#घोषणा DRV_VERSION "0.7.8"

अटल पूर्णांक ali_atapi_dma = 0;
module_param_named(atapi_dma, ali_atapi_dma, पूर्णांक, 0644);
MODULE_PARM_DESC(atapi_dma, "Enable ATAPI DMA (0=disable, 1=enable)");

अटल काष्ठा pci_dev *ali_isa_bridge;

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
	अगर (pdev->subप्रणाली_venकरोr == 0x10CF && pdev->subप्रणाली_device == 0x10AF)
	   	वापस 1;
	/* Mitac 8317 (Winbook-A) and relatives */
	अगर (pdev->subप्रणाली_venकरोr == 0x1071 && pdev->subप्रणाली_device == 0x8317)
		वापस 1;
	/* Systems by DMI */
	अगर (dmi_check_प्रणाली(cable_dmi_table))
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	ali_c2_cable_detect	-	cable detection
 *	@ap: ATA port
 *
 *	Perक्रमm cable detection क्रम C2 and later revisions
 */

अटल पूर्णांक ali_c2_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	/* Certain laptops use लघु but suitable cables and करोn't
	   implement the detect logic */

	अगर (ali_cable_override(pdev))
		वापस ATA_CBL_PATA40_SHORT;

	/* Host view cable detect 0x4A bit 0 primary bit 1 secondary
	   Bit set क्रम 40 pin */
	pci_पढ़ो_config_byte(pdev, 0x4A, &ata66);
	अगर (ata66 & (1 << ap->port_no))
		वापस ATA_CBL_PATA40;
	अन्यथा
		वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	ali_20_filter		-	filter क्रम earlier ALI DMA
 *	@adev: ATA device
 *	@mask: received mask to manipulate and pass back
 *
 *	Ensure that we करो not करो DMA on CD devices. We may be able to
 *	fix that later on. Also ensure we करो not करो UDMA on WDC drives
 */

अटल अचिन्हित दीर्घ ali_20_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अक्षर model_num[ATA_ID_PROD_LEN + 1];
	/* No DMA on anything but a disk क्रम now */
	अगर (adev->class != ATA_DEV_ATA)
		mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
	ata_id_c_string(adev->id, model_num, ATA_ID_PROD, माप(model_num));
	अगर (म_माला(model_num, "WDC"))
		वापस mask &= ~ATA_MASK_UDMA;
	वापस mask;
पूर्ण

/**
 *	ali_fअगरo_control	-	FIFO manager
 *	@ap: ALi channel to control
 *	@adev: device क्रम FIFO control
 *	@on: 0 क्रम off 1 क्रम on
 *
 *	Enable or disable the FIFO on a given device. Because of the way the
 *	ALi FIFO works it provides a boost on ATA disk but can be confused by
 *	ATAPI and we must thereक्रमe manage it.
 */

अटल व्योम ali_fअगरo_control(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक on)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक pio_fअगरo = 0x54 + ap->port_no;
	u8 fअगरo;
	पूर्णांक shअगरt = 4 * adev->devno;

	/* ATA - FIFO on set nibble to 0x05, ATAPI - FIFO off, set nibble to
	   0x00. Not all the करोcs agree but the behaviour we now use is the
	   one stated in the BIOS Programming Guide */

	pci_पढ़ो_config_byte(pdev, pio_fअगरo, &fअगरo);
	fअगरo &= ~(0x0F << shअगरt);
	fअगरo |= (on << shअगरt);
	pci_ग_लिखो_config_byte(pdev, pio_fअगरo, fअगरo);
पूर्ण

/**
 *	ali_program_modes	-	load mode रेजिस्टरs
 *	@ap: ALi channel to load
 *	@adev: Device the timing is क्रम
 *	@t: timing data
 *	@ultra: UDMA timing or zero क्रम off
 *
 *	Loads the timing रेजिस्टरs क्रम cmd/data and disable UDMA अगर
 *	ultra is zero. If ultra is set then load and enable the UDMA
 *	timing but करो not touch the command/data timing.
 */

अटल व्योम ali_program_modes(काष्ठा ata_port *ap, काष्ठा ata_device *adev, काष्ठा ata_timing *t, u8 ultra)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक cas = 0x58 + 4 * ap->port_no;	/* Command timing */
	पूर्णांक cbt = 0x59 + 4 * ap->port_no;	/* Command timing */
	पूर्णांक drwt = 0x5A + 4 * ap->port_no + adev->devno; /* R/W timing */
	पूर्णांक udmat = 0x56 + ap->port_no;	/* UDMA timing */
	पूर्णांक shअगरt = 4 * adev->devno;
	u8 udma;

	अगर (t != शून्य) अणु
		t->setup = clamp_val(t->setup, 1, 8) & 7;
		t->act8b = clamp_val(t->act8b, 1, 8) & 7;
		t->rec8b = clamp_val(t->rec8b, 1, 16) & 15;
		t->active = clamp_val(t->active, 1, 8) & 7;
		t->recover = clamp_val(t->recover, 1, 16) & 15;

		pci_ग_लिखो_config_byte(pdev, cas, t->setup);
		pci_ग_लिखो_config_byte(pdev, cbt, (t->act8b << 4) | t->rec8b);
		pci_ग_लिखो_config_byte(pdev, drwt, (t->active << 4) | t->recover);
	पूर्ण

	/* Set up the UDMA enable */
	pci_पढ़ो_config_byte(pdev, udmat, &udma);
	udma &= ~(0x0F << shअगरt);
	udma |= ultra << shअगरt;
	pci_ग_लिखो_config_byte(pdev, udmat, udma);
पूर्ण

/**
 *	ali_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the ALi रेजिस्टरs क्रम PIO mode.
 */

अटल व्योम ali_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	काष्ठा ata_timing t;
	अचिन्हित दीर्घ T =  1000000000 / 33333;	/* PCI घड़ी based */

	ata_timing_compute(adev, adev->pio_mode, &t, T, 1);
	अगर (pair) अणु
		काष्ठा ata_timing p;
		ata_timing_compute(pair, pair->pio_mode, &p, T, 1);
		ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
		अगर (pair->dma_mode) अणु
			ata_timing_compute(pair, pair->dma_mode, &p, T, 1);
			ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
		पूर्ण
	पूर्ण

	/* PIO FIFO is only permitted on ATA disk */
	अगर (adev->class != ATA_DEV_ATA)
		ali_fअगरo_control(ap, adev, 0x00);
	ali_program_modes(ap, adev, &t, 0);
	अगर (adev->class == ATA_DEV_ATA)
		ali_fअगरo_control(ap, adev, 0x05);

पूर्ण

/**
 *	ali_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the ALi रेजिस्टरs क्रम DMA mode.
 */

अटल व्योम ali_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल u8 udma_timing[7] = अणु 0xC, 0xB, 0xA, 0x9, 0x8, 0xF, 0xD पूर्ण;
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	काष्ठा ata_timing t;
	अचिन्हित दीर्घ T =  1000000000 / 33333;	/* PCI घड़ी based */
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);


	अगर (adev->class == ATA_DEV_ATA)
		ali_fअगरo_control(ap, adev, 0x08);

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		ali_program_modes(ap, adev, शून्य, udma_timing[adev->dma_mode - XFER_UDMA_0]);
		अगर (adev->dma_mode >= XFER_UDMA_3) अणु
			u8 reg4b;
			pci_पढ़ो_config_byte(pdev, 0x4B, &reg4b);
			reg4b |= 1;
			pci_ग_लिखो_config_byte(pdev, 0x4B, reg4b);
		पूर्ण
	पूर्ण अन्यथा अणु
		ata_timing_compute(adev, adev->dma_mode, &t, T, 1);
		अगर (pair) अणु
			काष्ठा ata_timing p;
			ata_timing_compute(pair, pair->pio_mode, &p, T, 1);
			ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
			अगर (pair->dma_mode) अणु
				ata_timing_compute(pair, pair->dma_mode, &p, T, 1);
				ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
			पूर्ण
		पूर्ण
		ali_program_modes(ap, adev, &t, 0);
	पूर्ण
पूर्ण

/**
 *	ali_warn_atapi_dma	-	Warn about ATAPI DMA disablement
 *	@adev: Device
 *
 *	Whine about ATAPI DMA disablement अगर @adev is an ATAPI device.
 *	Can be used as ->dev_config.
 */

अटल व्योम ali_warn_atapi_dma(काष्ठा ata_device *adev)
अणु
	काष्ठा ata_eh_context *ehc = &adev->link->eh_context;
	पूर्णांक prपूर्णांक_info = ehc->i.flags & ATA_EHI_PRINTINFO;

	अगर (prपूर्णांक_info && adev->class == ATA_DEV_ATAPI && !ali_atapi_dma) अणु
		ata_dev_warn(adev,
			     "WARNING: ATAPI DMA disabled for reliability issues.  It can be enabled\n");
		ata_dev_warn(adev,
			     "WARNING: via pata_ali.atapi_dma modparam or corresponding sysfs node.\n");
	पूर्ण
पूर्ण

/**
 *	ali_lock_sectors	-	Keep older devices to 255 sector mode
 *	@adev: Device
 *
 *	Called during the bus probe क्रम each device that is found. We use
 *	this call to lock the sector count of the device to 255 or less on
 *	older ALi controllers. If we didn't do this then large I/O's would
 *	require LBA48 commands which the older ALi requires are issued by
 *	slower PIO methods
 */

अटल व्योम ali_lock_sectors(काष्ठा ata_device *adev)
अणु
	adev->max_sectors = 255;
	ali_warn_atapi_dma(adev);
पूर्ण

/**
 *	ali_check_atapi_dma	-	DMA check क्रम most ALi controllers
 *	@qc: Command to complete
 *
 *	Called to decide whether commands should be sent by DMA or PIO
 */

अटल पूर्णांक ali_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (!ali_atapi_dma) अणु
		/* FIXME: pata_ali can't करो ATAPI DMA reliably but the
		 * IDE alim15x3 driver can.  I tried lots of things
		 * but couldn't find what the actual dअगरference was.
		 * If you got an idea, please ग_लिखो it to
		 * linux-ide@vger.kernel.org and cc htejun@gmail.com.
		 *
		 * Disable ATAPI DMA क्रम now.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If its not a media command, its not worth it */
	अगर (atapi_cmd_type(qc->cdb[0]) == ATAPI_MISC)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल व्योम ali_c2_c3_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes)
अणु
	u8 r;
	पूर्णांक port_bit = 4 << link->ap->port_no;

	/* If our bridge is an ALI 1533 then करो the extra work */
	अगर (ali_isa_bridge) अणु
		/* Tristate and re-enable the bus संकेतs */
		pci_पढ़ो_config_byte(ali_isa_bridge, 0x58, &r);
		r &= ~port_bit;
		pci_ग_लिखो_config_byte(ali_isa_bridge, 0x58, r);
		r |= port_bit;
		pci_ग_लिखो_config_byte(ali_isa_bridge, 0x58, r);
	पूर्ण
	ata_sff_postreset(link, classes);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ali_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

/*
 *	Port operations क्रम PIO only ALi
 */

अटल काष्ठा ata_port_operations ali_early_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= ali_set_piomode,
	.sff_data_xfer  = ata_sff_data_xfer32,
पूर्ण;

अटल स्थिर काष्ठा ata_port_operations ali_dma_base_ops = अणु
	.inherits	= &ata_bmdma32_port_ops,
	.set_piomode	= ali_set_piomode,
	.set_dmamode	= ali_set_dmamode,
पूर्ण;

/*
 *	Port operations क्रम DMA capable ALi without cable
 *	detect
 */
अटल काष्ठा ata_port_operations ali_20_port_ops = अणु
	.inherits	= &ali_dma_base_ops,
	.cable_detect	= ata_cable_40wire,
	.mode_filter	= ali_20_filter,
	.check_atapi_dma = ali_check_atapi_dma,
	.dev_config	= ali_lock_sectors,
पूर्ण;

/*
 *	Port operations क्रम DMA capable ALi with cable detect
 */
अटल काष्ठा ata_port_operations ali_c2_port_ops = अणु
	.inherits	= &ali_dma_base_ops,
	.check_atapi_dma = ali_check_atapi_dma,
	.cable_detect	= ali_c2_cable_detect,
	.dev_config	= ali_lock_sectors,
	.postreset	= ali_c2_c3_postreset,
पूर्ण;

/*
 *	Port operations क्रम DMA capable ALi with cable detect
 */
अटल काष्ठा ata_port_operations ali_c4_port_ops = अणु
	.inherits	= &ali_dma_base_ops,
	.check_atapi_dma = ali_check_atapi_dma,
	.cable_detect	= ali_c2_cable_detect,
	.dev_config	= ali_lock_sectors,
पूर्ण;

/*
 *	Port operations क्रम DMA capable ALi with cable detect and LBA48
 */
अटल काष्ठा ata_port_operations ali_c5_port_ops = अणु
	.inherits	= &ali_dma_base_ops,
	.check_atapi_dma = ali_check_atapi_dma,
	.dev_config	= ali_warn_atapi_dma,
	.cable_detect	= ali_c2_cable_detect,
पूर्ण;


/**
 *	ali_init_chipset	-	chip setup function
 *	@pdev: PCI device of ATA controller
 *
 *	Perक्रमm the setup on the device that must be करोne both at boot
 *	and at resume समय.
 */

अटल व्योम ali_init_chipset(काष्ठा pci_dev *pdev)
अणु
	u8 पंचांगp;
	काष्ठा pci_dev *north;

	/*
	 * The chipset revision selects the driver operations and
	 * mode data.
	 */

	अगर (pdev->revision <= 0x20) अणु
		pci_पढ़ो_config_byte(pdev, 0x53, &पंचांगp);
		पंचांगp |= 0x03;
		pci_ग_लिखो_config_byte(pdev, 0x53, पंचांगp);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_byte(pdev, 0x4a, &पंचांगp);
		pci_ग_लिखो_config_byte(pdev, 0x4a, पंचांगp | 0x20);
		pci_पढ़ो_config_byte(pdev, 0x4B, &पंचांगp);
		अगर (pdev->revision < 0xC2)
			/* 1543-E/F, 1543C-C, 1543C-D, 1543C-E */
			/* Clear CD-ROM DMA ग_लिखो bit */
			पंचांगp &= 0x7F;
		/* Cable and UDMA */
		अगर (pdev->revision >= 0xc2)
			पंचांगp |= 0x01;
		pci_ग_लिखो_config_byte(pdev, 0x4B, पंचांगp | 0x08);
		/*
		 * CD_ROM DMA on (0x53 bit 0). Enable this even अगर we want
		 * to use PIO. 0x53 bit 1 (rev 20 only) - enable FIFO control
		 * via 0x54/55.
		 */
		pci_पढ़ो_config_byte(pdev, 0x53, &पंचांगp);
		अगर (pdev->revision >= 0xc7)
			पंचांगp |= 0x03;
		अन्यथा
			पंचांगp |= 0x01;	/* CD_ROM enable क्रम DMA */
		pci_ग_लिखो_config_byte(pdev, 0x53, पंचांगp);
	पूर्ण
	north = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus), 0,
					    PCI_DEVFN(0, 0));
	अगर (north && north->venकरोr == PCI_VENDOR_ID_AL && ali_isa_bridge) अणु
		/* Configure the ALi bridge logic. For non ALi rely on BIOS.
		   Set the south bridge enable bit */
		pci_पढ़ो_config_byte(ali_isa_bridge, 0x79, &पंचांगp);
		अगर (pdev->revision == 0xC2)
			pci_ग_लिखो_config_byte(ali_isa_bridge, 0x79, पंचांगp | 0x04);
		अन्यथा अगर (pdev->revision > 0xC2 && pdev->revision < 0xC5)
			pci_ग_लिखो_config_byte(ali_isa_bridge, 0x79, पंचांगp | 0x02);
	पूर्ण
	pci_dev_put(north);
	ata_pci_bmdma_clear_simplex(pdev);
पूर्ण
/**
 *	ali_init_one		-	discovery callback
 *	@pdev: PCI device ID
 *	@id: PCI table info
 *
 *	An ALi IDE पूर्णांकerface has been discovered. Figure out what revision
 *	and perक्रमm configuration work beक्रमe handing it to the ATA layer
 */

अटल पूर्णांक ali_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info_early = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &ali_early_port_ops
	पूर्ण;
	/* Revision 0x20 added DMA */
	अटल स्थिर काष्ठा ata_port_info info_20 = अणु
		.flags = ATA_FLAG_SLAVE_POSS | ATA_FLAG_PIO_LBA48 |
							ATA_FLAG_IGN_SIMPLEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &ali_20_port_ops
	पूर्ण;
	/* Revision 0x20 with support logic added UDMA */
	अटल स्थिर काष्ठा ata_port_info info_20_udma = अणु
		.flags = ATA_FLAG_SLAVE_POSS | ATA_FLAG_PIO_LBA48 |
							ATA_FLAG_IGN_SIMPLEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.port_ops = &ali_20_port_ops
	पूर्ण;
	/* Revision 0xC2 adds UDMA66 */
	अटल स्थिर काष्ठा ata_port_info info_c2 = अणु
		.flags = ATA_FLAG_SLAVE_POSS | ATA_FLAG_PIO_LBA48 |
							ATA_FLAG_IGN_SIMPLEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &ali_c2_port_ops
	पूर्ण;
	/* Revision 0xC3 is UDMA66 क्रम now */
	अटल स्थिर काष्ठा ata_port_info info_c3 = अणु
		.flags = ATA_FLAG_SLAVE_POSS | ATA_FLAG_PIO_LBA48 |
							ATA_FLAG_IGN_SIMPLEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &ali_c2_port_ops
	पूर्ण;
	/* Revision 0xC4 is UDMA100 */
	अटल स्थिर काष्ठा ata_port_info info_c4 = अणु
		.flags = ATA_FLAG_SLAVE_POSS | ATA_FLAG_PIO_LBA48 |
							ATA_FLAG_IGN_SIMPLEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &ali_c4_port_ops
	पूर्ण;
	/* Revision 0xC5 is UDMA133 with LBA48 DMA */
	अटल स्थिर काष्ठा ata_port_info info_c5 = अणु
		.flags = ATA_FLAG_SLAVE_POSS | 	ATA_FLAG_IGN_SIMPLEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &ali_c5_port_ops
	पूर्ण;

	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	u8 पंचांगp;
	पूर्णांक rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/*
	 * The chipset revision selects the driver operations and
	 * mode data.
	 */

	अगर (pdev->revision < 0x20) अणु
		ppi[0] = &info_early;
	पूर्ण अन्यथा अगर (pdev->revision < 0xC2) अणु
        	ppi[0] = &info_20;
	पूर्ण अन्यथा अगर (pdev->revision == 0xC2) अणु
        	ppi[0] = &info_c2;
	पूर्ण अन्यथा अगर (pdev->revision == 0xC3) अणु
        	ppi[0] = &info_c3;
	पूर्ण अन्यथा अगर (pdev->revision == 0xC4) अणु
        	ppi[0] = &info_c4;
	पूर्ण अन्यथा
        	ppi[0] = &info_c5;

	ali_init_chipset(pdev);

	अगर (ali_isa_bridge && pdev->revision >= 0x20 && pdev->revision < 0xC2) अणु
		/* Are we paired with a UDMA capable chip */
		pci_पढ़ो_config_byte(ali_isa_bridge, 0x5E, &पंचांगp);
		अगर ((पंचांगp & 0x1E) == 0x12)
	        	ppi[0] = &info_20_udma;
	पूर्ण

	अगर (!ppi[0]->mwdma_mask && !ppi[0]->udma_mask)
		वापस ata_pci_sff_init_one(pdev, ppi, &ali_sht, शून्य, 0);
	अन्यथा
		वापस ata_pci_bmdma_init_one(pdev, ppi, &ali_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ali_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;
	ali_init_chipset(pdev);
	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id ali[] = अणु
	अणु PCI_VDEVICE(AL, PCI_DEVICE_ID_AL_M5228), पूर्ण,
	अणु PCI_VDEVICE(AL, PCI_DEVICE_ID_AL_M5229), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ali_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= ali,
	.probe 		= ali_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ali_reinit_one,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init ali_init(व्योम)
अणु
	पूर्णांक ret;
	ali_isa_bridge = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1533, शून्य);

	ret = pci_रेजिस्टर_driver(&ali_pci_driver);
	अगर (ret < 0)
		pci_dev_put(ali_isa_bridge);
	वापस ret;
पूर्ण


अटल व्योम __निकास ali_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ali_pci_driver);
	pci_dev_put(ali_isa_bridge);
पूर्ण


MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for ALi PATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ali);
MODULE_VERSION(DRV_VERSION);

module_init(ali_init);
module_निकास(ali_निकास);
