<शैली गुरु>
/*
 * pata_it821x.c 	- IT821x PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  Alan Cox <alan@lxorguk.ukuu.org.uk>
 *			  (C) 2007 Bartlomiej Zolnierkiewicz
 *
 * based upon
 *
 * it821x.c
 *
 * linux/drivers/ide/pci/it821x.c		Version 0.09	December 2004
 *
 * Copyright (C) 2004		Red Hat
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *  Based in part on the ITE venकरोr provided SCSI driver.
 *
 *  Documentation available from IT8212F_V04.pdf
 * 	http://www.ite.com.tw/EN/products_more.aspx?CategoryID=3&ID=5,91
 *  Some other करोcuments are NDA.
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
 *	-	ATAPI and other speed filtering
 *	-	RAID configuration ioctls
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>


#घोषणा DRV_NAME "pata_it821x"
#घोषणा DRV_VERSION "0.4.2"

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
	u16	last_device;		/* Master or slave loaded ? */
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
 *	@ap: ATA port
 *	@adev: Device to program
 *	@timing: Timing value (66Mhz in top 8bits, 50 in the low 8)
 *
 *	Program the PIO/MWDMA timing क्रम this channel according to the
 *	current घड़ी. These share the same रेजिस्टर so are managed by
 *	the DMA start/stop sequence as with the old driver.
 */

अटल व्योम it821x_program(काष्ठा ata_port *ap, काष्ठा ata_device *adev, u16 timing)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	पूर्णांक channel = ap->port_no;
	u8 conf;

	/* Program PIO/MWDMA timing bits */
	अगर (itdev->घड़ी_mode == ATA_66)
		conf = timing >> 8;
	अन्यथा
		conf = timing & 0xFF;
	pci_ग_लिखो_config_byte(pdev, 0x54 + 4 * channel, conf);
पूर्ण


/**
 *	it821x_program_udma	-	program the UDMA रेजिस्टरs
 *	@ap: ATA port
 *	@adev: ATA device to update
 *	@timing: Timing bits. Top 8 are क्रम 66Mhz bottom क्रम 50Mhz
 *
 *	Program the UDMA timing क्रम this drive according to the
 *	current घड़ी. Handles the dual घड़ीs and also knows about
 *	the errata on the 0x10 revision. The UDMA errata is partly handled
 *	here and partly in start_dma.
 */

अटल व्योम it821x_program_udma(काष्ठा ata_port *ap, काष्ठा ata_device *adev, u16 timing)
अणु
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक channel = ap->port_no;
	पूर्णांक unit = adev->devno;
	u8 conf;

	/* Program UDMA timing bits */
	अगर (itdev->घड़ी_mode == ATA_66)
		conf = timing >> 8;
	अन्यथा
		conf = timing & 0xFF;
	अगर (itdev->timing10 == 0)
		pci_ग_लिखो_config_byte(pdev, 0x56 + 4 * channel + unit, conf);
	अन्यथा अणु
		/* Early revision must be programmed क्रम both together */
		pci_ग_लिखो_config_byte(pdev, 0x56 + 4 * channel, conf);
		pci_ग_लिखो_config_byte(pdev, 0x56 + 4 * channel + 1, conf);
	पूर्ण
पूर्ण

/**
 *	it821x_घड़ी_strategy
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device being updated
 *
 *	Select between the 50 and 66Mhz base घड़ीs to get the best
 *	results क्रम this पूर्णांकerface.
 */

अटल व्योम it821x_घड़ी_strategy(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	u8 unit = adev->devno;
	काष्ठा ata_device *pair = ata_dev_pair(adev);

	पूर्णांक घड़ी, altघड़ी;
	u8 v;
	पूर्णांक sel = 0;

	/* Look क्रम the most wanted घड़ीing */
	अगर (itdev->want[0][0] > itdev->want[1][0]) अणु
		घड़ी = itdev->want[0][1];
		altघड़ी = itdev->want[1][1];
	पूर्ण अन्यथा अणु
		घड़ी = itdev->want[1][1];
		altघड़ी = itdev->want[0][1];
	पूर्ण

	/* Master करोesn't care करोes the slave ? */
	अगर (घड़ी == ATA_ANY)
		घड़ी = altघड़ी;

	/* Nobody cares - keep the same घड़ी */
	अगर (घड़ी == ATA_ANY)
		वापस;
	/* No change */
	अगर (घड़ी == itdev->घड़ी_mode)
		वापस;

	/* Load this पूर्णांकo the controller */
	अगर (घड़ी == ATA_66)
		itdev->घड़ी_mode = ATA_66;
	अन्यथा अणु
		itdev->घड़ी_mode = ATA_50;
		sel = 1;
	पूर्ण
	pci_पढ़ो_config_byte(pdev, 0x50, &v);
	v &= ~(1 << (1 + ap->port_no));
	v |= sel << (1 + ap->port_no);
	pci_ग_लिखो_config_byte(pdev, 0x50, v);

	/*
	 *	Reprogram the UDMA/PIO of the pair drive क्रम the चयन
	 *	MWDMA will be dealt with by the dma चयनer
	 */
	अगर (pair && itdev->udma[1-unit] != UDMA_OFF) अणु
		it821x_program_udma(ap, pair, itdev->udma[1-unit]);
		it821x_program(ap, pair, itdev->pio[1-unit]);
	पूर्ण
	/*
	 *	Reprogram the UDMA/PIO of our drive क्रम the चयन.
	 *	MWDMA will be dealt with by the dma चयनer
	 */
	अगर (itdev->udma[unit] != UDMA_OFF) अणु
		it821x_program_udma(ap, adev, itdev->udma[unit]);
		it821x_program(ap, adev, itdev->pio[unit]);
	पूर्ण
पूर्ण

/**
 *	it821x_passthru_set_piomode	-	set PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Configure क्रम PIO mode. This is complicated as the रेजिस्टर is
 *	shared by PIO and MWDMA and क्रम both channels.
 */

अटल व्योम it821x_passthru_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	/* Spec says 89 ref driver uses 88 */
	अटल स्थिर u16 pio[]	= अणु 0xAA88, 0xA382, 0xA181, 0x3332, 0x3121 पूर्ण;
	अटल स्थिर u8 pio_want[]    = अणु ATA_66, ATA_66, ATA_66, ATA_66, ATA_ANY पूर्ण;

	काष्ठा it821x_dev *itdev = ap->निजी_data;
	पूर्णांक unit = adev->devno;
	पूर्णांक mode_wanted = adev->pio_mode - XFER_PIO_0;

	/* We prefer 66Mhz घड़ी क्रम PIO 0-3, करोn't care क्रम PIO4 */
	itdev->want[unit][1] = pio_want[mode_wanted];
	itdev->want[unit][0] = 1;	/* PIO is lowest priority */
	itdev->pio[unit] = pio[mode_wanted];
	it821x_घड़ी_strategy(ap, adev);
	it821x_program(ap, adev, itdev->pio[unit]);
पूर्ण

/**
 *	it821x_passthru_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Set up the DMA modes. The actions taken depend heavily on the mode
 *	to use. If UDMA is used as is hopefully the usual हाल then the
 *	timing रेजिस्टर is निजी and we need only consider the घड़ी. If
 *	we are using MWDMA then we have to manage the setting ourself as
 *	we चयन devices and mode.
 */

अटल व्योम it821x_passthru_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u16 dma[]	= 	अणु 0x8866, 0x3222, 0x3121 पूर्ण;
	अटल स्थिर u8 mwdma_want[] =  अणु ATA_ANY, ATA_66, ATA_ANY पूर्ण;
	अटल स्थिर u16 udma[]	= 	अणु 0x4433, 0x4231, 0x3121, 0x2121, 0x1111, 0x2211, 0x1111 पूर्ण;
	अटल स्थिर u8 udma_want[] =   अणु ATA_ANY, ATA_50, ATA_ANY, ATA_66, ATA_66, ATA_50, ATA_66 पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	पूर्णांक channel = ap->port_no;
	पूर्णांक unit = adev->devno;
	u8 conf;

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		पूर्णांक mode_wanted = adev->dma_mode - XFER_UDMA_0;

		itdev->want[unit][1] = udma_want[mode_wanted];
		itdev->want[unit][0] = 3;	/* UDMA is high priority */
		itdev->mwdma[unit] = MWDMA_OFF;
		itdev->udma[unit] = udma[mode_wanted];
		अगर (mode_wanted >= 5)
			itdev->udma[unit] |= 0x8080;	/* UDMA 5/6 select on */

		/* UDMA on. Again revision 0x10 must करो the pair */
		pci_पढ़ो_config_byte(pdev, 0x50, &conf);
		अगर (itdev->timing10)
			conf &= channel ? 0x9F: 0xE7;
		अन्यथा
			conf &= ~ (1 << (3 + 2 * channel + unit));
		pci_ग_लिखो_config_byte(pdev, 0x50, conf);
		it821x_घड़ी_strategy(ap, adev);
		it821x_program_udma(ap, adev, itdev->udma[unit]);
	पूर्ण अन्यथा अणु
		पूर्णांक mode_wanted = adev->dma_mode - XFER_MW_DMA_0;

		itdev->want[unit][1] = mwdma_want[mode_wanted];
		itdev->want[unit][0] = 2;	/* MWDMA is low priority */
		itdev->mwdma[unit] = dma[mode_wanted];
		itdev->udma[unit] = UDMA_OFF;

		/* UDMA bits off - Revision 0x10 करो them in pairs */
		pci_पढ़ो_config_byte(pdev, 0x50, &conf);
		अगर (itdev->timing10)
			conf |= channel ? 0x60: 0x18;
		अन्यथा
			conf |= 1 << (3 + 2 * channel + unit);
		pci_ग_लिखो_config_byte(pdev, 0x50, conf);
		it821x_घड़ी_strategy(ap, adev);
	पूर्ण
पूर्ण

/**
 *	it821x_passthru_bmdma_start	-	DMA start callback
 *	@qc: Command in progress
 *
 *	Usually drivers set the DMA timing at the poपूर्णांक the set_dmamode call
 *	is made. IT821x however requires we load new timings on the
 *	transitions in some हालs.
 */

अटल व्योम it821x_passthru_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	पूर्णांक unit = adev->devno;

	अगर (itdev->mwdma[unit] != MWDMA_OFF)
		it821x_program(ap, adev, itdev->mwdma[unit]);
	अन्यथा अगर (itdev->udma[unit] != UDMA_OFF && itdev->timing10)
		it821x_program_udma(ap, adev, itdev->udma[unit]);
	ata_bmdma_start(qc);
पूर्ण

/**
 *	it821x_passthru_bmdma_stop	-	DMA stop callback
 *	@qc: ATA command
 *
 *	We loaded new timings in dma_start, as a result we need to restore
 *	the PIO timings in dma_stop so that the next command issue माला_लो the
 *	right घड़ी values.
 */

अटल व्योम it821x_passthru_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	पूर्णांक unit = adev->devno;

	ata_bmdma_stop(qc);
	अगर (itdev->mwdma[unit] != MWDMA_OFF)
		it821x_program(ap, adev, itdev->pio[unit]);
पूर्ण


/**
 *	it821x_passthru_dev_select	-	Select master/slave
 *	@ap: ATA port
 *	@device: Device number (not poपूर्णांकer)
 *
 *	Device selection hook. If necessary perक्रमm घड़ी चयनing
 */

अटल व्योम it821x_passthru_dev_select(काष्ठा ata_port *ap,
				       अचिन्हित पूर्णांक device)
अणु
	काष्ठा it821x_dev *itdev = ap->निजी_data;
	अगर (itdev && device != itdev->last_device) अणु
		काष्ठा ata_device *adev = &ap->link.device[device];
		it821x_program(ap, adev, itdev->pio[adev->devno]);
		itdev->last_device = device;
	पूर्ण
	ata_sff_dev_select(ap, device);
पूर्ण

/**
 *	it821x_smart_qc_issue		-	wrap qc issue prot
 *	@qc: command
 *
 *	Wrap the command issue sequence क्रम the IT821x. We need to
 *	perक्रमm out own device selection timing loads beक्रमe the
 *	usual happenings kick off
 */

अटल अचिन्हित पूर्णांक it821x_smart_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	चयन(qc->tf.command)
	अणु
		/* Commands the firmware supports */
		हाल ATA_CMD_READ:
		हाल ATA_CMD_READ_EXT:
		हाल ATA_CMD_WRITE:
		हाल ATA_CMD_WRITE_EXT:
		हाल ATA_CMD_PIO_READ:
		हाल ATA_CMD_PIO_READ_EXT:
		हाल ATA_CMD_PIO_WRITE:
		हाल ATA_CMD_PIO_WRITE_EXT:
		हाल ATA_CMD_READ_MULTI:
		हाल ATA_CMD_READ_MULTI_EXT:
		हाल ATA_CMD_WRITE_MULTI:
		हाल ATA_CMD_WRITE_MULTI_EXT:
		हाल ATA_CMD_ID_ATA:
		हाल ATA_CMD_INIT_DEV_PARAMS:
		हाल 0xFC:	/* Internal 'report rebuild state' */
		/* Arguably should just no-op this one */
		हाल ATA_CMD_SET_FEATURES:
			वापस ata_bmdma_qc_issue(qc);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "it821x: can't process command 0x%02X\n", qc->tf.command);
	वापस AC_ERR_DEV;
पूर्ण

/**
 *	it821x_passthru_qc_issue	-	wrap qc issue prot
 *	@qc: command
 *
 *	Wrap the command issue sequence क्रम the IT821x. We need to
 *	perक्रमm out own device selection timing loads beक्रमe the
 *	usual happenings kick off
 */

अटल अचिन्हित पूर्णांक it821x_passthru_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	it821x_passthru_dev_select(qc->ap, qc->dev->devno);
	वापस ata_bmdma_qc_issue(qc);
पूर्ण

/**
 *	it821x_smart_set_mode	-	mode setting
 *	@link: पूर्णांकerface to set up
 *	@unused: device that failed (error only)
 *
 *	Use a non standard set_mode function. We करोn't want to be tuned.
 *	The BIOS configured everything. Our job is not to fiddle. We
 *	पढ़ो the dma enabled bits from the PCI configuration of the device
 *	and respect them.
 */

अटल पूर्णांक it821x_smart_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **unused)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		/* We करोn't really care */
		dev->pio_mode = XFER_PIO_0;
		dev->dma_mode = XFER_MW_DMA_0;
		/* We करो need the right mode inक्रमmation क्रम DMA or PIO
		   and this comes from the current configuration flags */
		अगर (ata_id_has_dma(dev->id)) अणु
			ata_dev_info(dev, "configured for DMA\n");
			dev->xfer_mode = XFER_MW_DMA_0;
			dev->xfer_shअगरt = ATA_SHIFT_MWDMA;
			dev->flags &= ~ATA_DFLAG_PIO;
		पूर्ण अन्यथा अणु
			ata_dev_info(dev, "configured for PIO\n");
			dev->xfer_mode = XFER_PIO_0;
			dev->xfer_shअगरt = ATA_SHIFT_PIO;
			dev->flags |= ATA_DFLAG_PIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	it821x_dev_config	-	Called each device identअगरy
 *	@adev: Device that has just been identअगरied
 *
 *	Perक्रमm the initial setup needed क्रम each device that is chip
 *	special. In our हाल we need to lock the sector count to aव्योम
 *	blowing the brains out of the firmware with large LBA48 requests
 *
 */

अटल व्योम it821x_dev_config(काष्ठा ata_device *adev)
अणु
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];

	ata_id_c_string(adev->id, model_num, ATA_ID_PROD, माप(model_num));

	अगर (adev->max_sectors > 255)
		adev->max_sectors = 255;

	अगर (म_माला(model_num, "Integrated Technology Express")) अणु
		/* RAID mode */
		ata_dev_info(adev, "%sRAID%d volume",
			     adev->id[147] ? "Bootable " : "",
			     adev->id[129]);
		अगर (adev->id[129] != 1)
			pr_cont("(%dK stripe)", adev->id[146]);
		pr_cont("\n");
	पूर्ण
	/* This is a controller firmware triggered funny, करोn't
	   report the drive faulty! */
	adev->horkage &= ~ATA_HORKAGE_DIAGNOSTIC;
	/* No HPA in 'smart' mode */
	adev->horkage |= ATA_HORKAGE_BROKEN_HPA;
पूर्ण

/**
 *	it821x_पढ़ो_id	-	Hack identअगरy data up
 *	@adev: device to पढ़ो
 *	@tf: proposed taskfile
 *	@id: buffer क्रम वापसed ident data
 *
 *	Query the devices on this firmware driven port and slightly
 *	mash the identअगरy data to stop us and common tools trying to
 *	use features not firmware supported. The firmware itself करोes
 *	some masking (eg SMART) but not enough.
 */

अटल अचिन्हित पूर्णांक it821x_पढ़ो_id(काष्ठा ata_device *adev,
					काष्ठा ata_taskfile *tf, u16 *id)
अणु
	अचिन्हित पूर्णांक err_mask;
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];

	err_mask = ata_करो_dev_पढ़ो_id(adev, tf, id);
	अगर (err_mask)
		वापस err_mask;
	ata_id_c_string(id, model_num, ATA_ID_PROD, माप(model_num));

	id[83] &= ~(1 << 12);	/* Cache flush is firmware handled */
	id[83] &= ~(1 << 13);	/* Ditto क्रम LBA48 flushes */
	id[84] &= ~(1 << 6);	/* No FUA */
	id[85] &= ~(1 << 10);	/* No HPA */
	id[76] = 0;		/* No NCQ/AN etc */

	अगर (म_माला(model_num, "Integrated Technology Express")) अणु
		/* Set feature bits the firmware neglects */
		id[49] |= 0x0300;	/* LBA, DMA */
		id[83] &= 0x7FFF;
		id[83] |= 0x4400;	/* Word 83 is valid and LBA48 */
		id[86] |= 0x0400;	/* LBA48 on */
		id[ATA_ID_MAJOR_VER] |= 0x1F;
		/* Clear the serial number because it's dअगरferent each boot
		   which अवरोधs validation on resume */
		स_रखो(&id[ATA_ID_SERNO], 0x20, ATA_ID_SERNO_LEN);
	पूर्ण
	वापस err_mask;
पूर्ण

/**
 *	it821x_check_atapi_dma	-	ATAPI DMA handler
 *	@qc: Command we are about to issue
 *
 *	Decide अगर this ATAPI command can be issued by DMA on this
 *	controller. Return 0 अगर it can be.
 */

अटल पूर्णांक it821x_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा it821x_dev *itdev = ap->निजी_data;

	/* Only use dma क्रम transfers to/from the media. */
	अगर (ata_qc_raw_nbytes(qc) < 2048)
		वापस -EOPNOTSUPP;

	/* No ATAPI DMA in smart mode */
	अगर (itdev->smart)
		वापस -EOPNOTSUPP;
	/* No ATAPI DMA on rev 10 */
	अगर (itdev->timing10)
		वापस -EOPNOTSUPP;
	/* Cool */
	वापस 0;
पूर्ण

/**
 *	it821x_display_disk	-	display disk setup
 *	@n: Device number
 *	@buf: Buffer block from firmware
 *
 *	Produce a nice inक्रमmative display of the device setup as provided
 *	by the firmware.
 */

अटल व्योम it821x_display_disk(पूर्णांक n, u8 *buf)
अणु
	अचिन्हित अक्षर id[41];
	पूर्णांक mode = 0;
	स्थिर अक्षर *mtype = "";
	अक्षर mbuf[8];
	स्थिर अक्षर *cbl = "(40 wire cable)";

	अटल स्थिर अक्षर *types[5] = अणु
		"RAID0", "RAID1", "RAID 0+1", "JBOD", "DISK"
	पूर्ण;

	अगर (buf[52] > 4)	/* No Disk */
		वापस;

	ata_id_c_string((u16 *)buf, id, 0, 41);

	अगर (buf[51]) अणु
		mode = ffs(buf[51]);
		mtype = "UDMA";
	पूर्ण अन्यथा अगर (buf[49]) अणु
		mode = ffs(buf[49]);
		mtype = "MWDMA";
	पूर्ण

	अगर (buf[76])
		cbl = "";

	अगर (mode)
		snम_लिखो(mbuf, 8, "%5s%d", mtype, mode - 1);
	अन्यथा
		म_नकल(mbuf, "PIO");
	अगर (buf[52] == 4)
		prपूर्णांकk(KERN_INFO "%d: %-6s %-8s          %s %s\n",
				n, mbuf, types[buf[52]], id, cbl);
	अन्यथा
		prपूर्णांकk(KERN_INFO "%d: %-6s %-8s Volume: %1d %s %s\n",
				n, mbuf, types[buf[52]], buf[53], id, cbl);
	अगर (buf[125] < 100)
		prपूर्णांकk(KERN_INFO "%d: Rebuilding: %d%%\n", n, buf[125]);
पूर्ण

/**
 *	it821x_firmware_command		-	issue firmware command
 *	@ap: IT821x port to पूर्णांकerrogate
 *	@cmd: command
 *	@len: length
 *
 *	Issue firmware commands expecting data back from the controller. We
 *	use this to issue commands that करो not go via the normal paths. Other
 *	commands such as 0xFC can be issued normally.
 */

अटल u8 *it821x_firmware_command(काष्ठा ata_port *ap, u8 cmd, पूर्णांक len)
अणु
	u8 status;
	पूर्णांक n = 0;
	u16 *buf = kदो_स्मृति(len, GFP_KERNEL);

	अगर (!buf)
		वापस शून्य;

	/* This isn't quite a normal ATA command as we are talking to the
	   firmware not the drives */
	ap->ctl |= ATA_NIEN;
	ioग_लिखो8(ap->ctl, ap->ioaddr.ctl_addr);
	ata_रुको_idle(ap);
	ioग_लिखो8(ATA_DEVICE_OBS, ap->ioaddr.device_addr);
	ioग_लिखो8(cmd, ap->ioaddr.command_addr);
	udelay(1);
	/* This should be almost immediate but a little paranoia goes a दीर्घ
	   way. */
	जबतक(n++ < 10) अणु
		status = ioपढ़ो8(ap->ioaddr.status_addr);
		अगर (status & ATA_ERR) अणु
			kमुक्त(buf);
			prपूर्णांकk(KERN_ERR "it821x_firmware_command: rejected\n");
			वापस शून्य;
		पूर्ण
		अगर (status & ATA_DRQ) अणु
			ioपढ़ो16_rep(ap->ioaddr.data_addr, buf, len/2);
			वापस (u8 *)buf;
		पूर्ण
		usleep_range(500, 1000);
	पूर्ण
	kमुक्त(buf);
	prपूर्णांकk(KERN_ERR "it821x_firmware_command: timeout\n");
	वापस शून्य;
पूर्ण

/**
 *	it821x_probe_firmware	-	firmware reporting/setup
 *	@ap: IT821x port being probed
 *
 *	Probe the firmware of the controller by issuing firmware command
 *	0xFA and analysing the वापसed data.
 */

अटल व्योम it821x_probe_firmware(काष्ठा ata_port *ap)
अणु
	u8 *buf;
	पूर्णांक i;

	/* This is a bit ugly as we can't just issue a task file to a device
	   as this is controller magic */

	buf = it821x_firmware_command(ap, 0xFA, 512);

	अगर (buf != शून्य) अणु
		prपूर्णांकk(KERN_INFO "pata_it821x: Firmware %02X/%02X/%02X%02X\n",
				buf[505],
				buf[506],
				buf[507],
				buf[508]);
		क्रम (i = 0; i < 4; i++)
 			it821x_display_disk(i, buf + 128 * i);
		kमुक्त(buf);
	पूर्ण
पूर्ण



/**
 *	it821x_port_start	-	port setup
 *	@ap: ATA port being set up
 *
 *	The it821x needs to मुख्यtain निजी data काष्ठाures and also to
 *	use the standard PCI पूर्णांकerface which lacks support क्रम this
 *	functionality. We instead set up the निजी data on the port
 *	start hook, and tear it करोwn on port stop
 */

अटल पूर्णांक it821x_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा it821x_dev *itdev;
	u8 conf;

	पूर्णांक ret = ata_bmdma_port_start(ap);
	अगर (ret < 0)
		वापस ret;

	itdev = devm_kzalloc(&pdev->dev, माप(काष्ठा it821x_dev), GFP_KERNEL);
	अगर (itdev == शून्य)
		वापस -ENOMEM;
	ap->निजी_data = itdev;

	pci_पढ़ो_config_byte(pdev, 0x50, &conf);

	अगर (conf & 1) अणु
		itdev->smart = 1;
		/* Long I/O's although allowed in LBA48 space cause the
		   onboard firmware to enter the twighlight zone */
		/* No ATAPI DMA in this mode either */
		अगर (ap->port_no == 0)
			it821x_probe_firmware(ap);
	पूर्ण
	/* Pull the current घड़ीs from 0x50 */
	अगर (conf & (1 << (1 + ap->port_no)))
		itdev->घड़ी_mode = ATA_50;
	अन्यथा
		itdev->घड़ी_mode = ATA_66;

	itdev->want[0][1] = ATA_ANY;
	itdev->want[1][1] = ATA_ANY;
	itdev->last_device = -1;

	अगर (pdev->revision == 0x10) अणु
		itdev->timing10 = 1;
		/* Need to disable ATAPI DMA क्रम this हाल */
		अगर (!itdev->smart)
			prपूर्णांकk(KERN_WARNING DRV_NAME": Revision 0x10, workarounds activated.\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	it821x_rdc_cable	-	Cable detect क्रम RDC1010
 *	@ap: port we are checking
 *
 *	Return the RDC1010 cable type. Unlike the IT821x we know how to करो
 *	this and can करो host side cable detect
 */

अटल पूर्णांक it821x_rdc_cable(काष्ठा ata_port *ap)
अणु
	u16 r40;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	pci_पढ़ो_config_word(pdev, 0x40, &r40);
	अगर (r40 & (1 << (2 + ap->port_no)))
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा it821x_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations it821x_smart_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.check_atapi_dma= it821x_check_atapi_dma,
	.qc_issue	= it821x_smart_qc_issue,

	.cable_detect	= ata_cable_80wire,
	.set_mode	= it821x_smart_set_mode,
	.dev_config	= it821x_dev_config,
	.पढ़ो_id	= it821x_पढ़ो_id,

	.port_start	= it821x_port_start,
पूर्ण;

अटल काष्ठा ata_port_operations it821x_passthru_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.check_atapi_dma= it821x_check_atapi_dma,
	.sff_dev_select	= it821x_passthru_dev_select,
	.bmdma_start 	= it821x_passthru_bmdma_start,
	.bmdma_stop	= it821x_passthru_bmdma_stop,
	.qc_issue	= it821x_passthru_qc_issue,

	.cable_detect	= ata_cable_unknown,
	.set_piomode	= it821x_passthru_set_piomode,
	.set_dmamode	= it821x_passthru_set_dmamode,

	.port_start	= it821x_port_start,
पूर्ण;

अटल काष्ठा ata_port_operations it821x_rdc_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.check_atapi_dma= it821x_check_atapi_dma,
	.sff_dev_select	= it821x_passthru_dev_select,
	.bmdma_start 	= it821x_passthru_bmdma_start,
	.bmdma_stop	= it821x_passthru_bmdma_stop,
	.qc_issue	= it821x_passthru_qc_issue,

	.cable_detect	= it821x_rdc_cable,
	.set_piomode	= it821x_passthru_set_piomode,
	.set_dmamode	= it821x_passthru_set_dmamode,

	.port_start	= it821x_port_start,
पूर्ण;

अटल व्योम it821x_disable_raid(काष्ठा pci_dev *pdev)
अणु
	/* Neither the RDC nor the IT8211 */
	अगर (pdev->venकरोr != PCI_VENDOR_ID_ITE ||
			pdev->device != PCI_DEVICE_ID_ITE_8212)
			वापस;

	/* Reset local CPU, and set BIOS not पढ़ोy */
	pci_ग_लिखो_config_byte(pdev, 0x5E, 0x01);

	/* Set to bypass mode, and reset PCI bus */
	pci_ग_लिखो_config_byte(pdev, 0x50, 0x00);
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND,
			      PCI_COMMAND_PARITY | PCI_COMMAND_IO |
			      PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	pci_ग_लिखो_config_word(pdev, 0x40, 0xA0F3);

	pci_ग_लिखो_config_dword(pdev,0x4C, 0x02040204);
	pci_ग_लिखो_config_byte(pdev, 0x42, 0x36);
	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x20);
पूर्ण


अटल पूर्णांक it821x_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	u8 conf;

	अटल स्थिर काष्ठा ata_port_info info_smart = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &it821x_smart_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_passthru = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &it821x_passthru_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_rdc = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &it821x_rdc_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_rdc_11 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		/* No UDMA */
		.port_ops = &it821x_rdc_port_ops
	पूर्ण;

	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	अटल स्थिर अक्षर *mode[2] = अणु "pass through", "smart" पूर्ण;
	पूर्णांक rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_RDC) अणु
		/* Deal with Vortex86SX */
		अगर (pdev->revision == 0x11)
			ppi[0] = &info_rdc_11;
		अन्यथा
			ppi[0] = &info_rdc;
	पूर्ण अन्यथा अणु
		/* Force the card पूर्णांकo bypass mode अगर so requested */
		अगर (it8212_noraid) अणु
			prपूर्णांकk(KERN_INFO DRV_NAME ": forcing bypass mode.\n");
			it821x_disable_raid(pdev);
		पूर्ण
		pci_पढ़ो_config_byte(pdev, 0x50, &conf);
		conf &= 1;

		prपूर्णांकk(KERN_INFO DRV_NAME": controller in %s mode.\n",
								mode[conf]);
		अगर (conf == 0)
			ppi[0] = &info_passthru;
		अन्यथा
			ppi[0] = &info_smart;
	पूर्ण
	वापस ata_pci_bmdma_init_one(pdev, ppi, &it821x_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक it821x_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;
	/* Resume - turn raid back off अगर need be */
	अगर (it8212_noraid)
		it821x_disable_raid(pdev);
	ata_host_resume(host);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id it821x[] = अणु
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8211), पूर्ण,
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8212), पूर्ण,
	अणु PCI_VDEVICE(RDC, PCI_DEVICE_ID_RDC_D1010), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver it821x_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= it821x,
	.probe 		= it821x_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= it821x_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(it821x_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the IT8211/IT8212 IDE RAID controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, it821x);
MODULE_VERSION(DRV_VERSION);

module_param_named(noraid, it8212_noraid, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(noraid, "Force card into bypass mode");
