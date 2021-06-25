<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_optidma.c 	- Opti DMA PATA क्रम new ATA layer
 *			  (C) 2006 Red Hat Inc
 *
 *	The Opti DMA controllers are related to the older PIO PCI controllers
 *	and indeed the VLB ones. The मुख्य dअगरferences are that the timing
 *	numbers are now based off PCI घड़ीs not VLB and dअगरfer, and that
 *	MWDMA is supported.
 *
 *	This driver should support Viper-N+, FireStar, FireStar Plus.
 *
 *	These devices support भव DMA क्रम पढ़ो (aka the CS5520). Later
 *	chips support UDMA33, but only अगर the rest of the board logic करोes,
 *	so you have to get this right. We करोn't support the भव DMA
 *	but we करो handle UDMA.
 *
 *	Bits that are worth knowing
 *		Most control रेजिस्टरs are shaकरोwed पूर्णांकo I/O रेजिस्टरs
 *		0x1F5 bit 0 tells you अगर the PCI/VLB घड़ी is 33 or 25Mhz
 *		Virtual DMA रेजिस्टरs *move* between rev 0x02 and rev 0x10
 *		UDMA requires a 66MHz FSB
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_optidma"
#घोषणा DRV_VERSION "0.3.2"

क्रमागत अणु
	READ_REG	= 0,	/* index of Read cycle timing रेजिस्टर */
	WRITE_REG 	= 1,	/* index of Write cycle timing रेजिस्टर */
	CNTRL_REG 	= 3,	/* index of Control रेजिस्टर */
	STRAP_REG 	= 5,	/* index of Strap रेजिस्टर */
	MISC_REG 	= 6	/* index of Miscellaneous रेजिस्टर */
पूर्ण;

अटल पूर्णांक pci_घड़ी;	/* 0 = 33 1 = 25 */

/**
 *	optidma_pre_reset		-	probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Set up cable type and use generic probe init
 */

अटल पूर्णांक optidma_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर काष्ठा pci_bits optidma_enable_bits = अणु
		0x40, 1, 0x08, 0x00
	पूर्ण;

	अगर (ap->port_no && !pci_test_config_bits(pdev, &optidma_enable_bits))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	optidma_unlock		-	unlock control रेजिस्टरs
 *	@ap: ATA port
 *
 *	Unlock the control रेजिस्टर block क्रम this adapter. Registers must not
 *	be unlocked in a situation where libata might look at them.
 */

अटल व्योम optidma_unlock(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *regio = ap->ioaddr.cmd_addr;

	/* These 3 unlock the control रेजिस्टर access */
	ioपढ़ो16(regio + 1);
	ioपढ़ो16(regio + 1);
	ioग_लिखो8(3, regio + 2);
पूर्ण

/**
 *	optidma_lock		-	issue temporary relock
 *	@ap: ATA port
 *
 *	Re-lock the configuration रेजिस्टर settings.
 */

अटल व्योम optidma_lock(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *regio = ap->ioaddr.cmd_addr;

	/* Relock */
	ioग_लिखो8(0x83, regio + 2);
पूर्ण

/**
 *	optidma_mode_setup	-	set mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@mode: Mode to set
 *
 *	Called to करो the DMA or PIO mode setup. Timing numbers are all
 *	pre computed to keep the code clean. There are two tables depending
 *	on the hardware घड़ी speed.
 *
 *	WARNING: While we करो this the IDE रेजिस्टरs vanish. If we take an
 *	IRQ here we depend on the host set locking to aव्योम catastrophe.
 */

अटल व्योम optidma_mode_setup(काष्ठा ata_port *ap, काष्ठा ata_device *adev, u8 mode)
अणु
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	पूर्णांक pio = adev->pio_mode - XFER_PIO_0;
	पूर्णांक dma = adev->dma_mode - XFER_MW_DMA_0;
	व्योम __iomem *regio = ap->ioaddr.cmd_addr;
	u8 addr;

	/* Address table precomputed with a DCLK of 2 */
	अटल स्थिर u8 addr_timing[2][5] = अणु
		अणु 0x30, 0x20, 0x20, 0x10, 0x10 पूर्ण,
		अणु 0x20, 0x20, 0x10, 0x10, 0x10 पूर्ण
	पूर्ण;
	अटल स्थिर u8 data_rec_timing[2][5] = अणु
		अणु 0x59, 0x46, 0x30, 0x20, 0x20 पूर्ण,
		अणु 0x46, 0x32, 0x20, 0x20, 0x10 पूर्ण
	पूर्ण;
	अटल स्थिर u8 dma_data_rec_timing[2][3] = अणु
		अणु 0x76, 0x20, 0x20 पूर्ण,
		अणु 0x54, 0x20, 0x10 पूर्ण
	पूर्ण;

	/* Switch from IDE to control mode */
	optidma_unlock(ap);


	/*
 	 *	As with many controllers the address setup समय is shared
 	 *	and must suit both devices अगर present. FIXME: Check अगर we
 	 *	need to look at slowest of PIO/DMA mode of either device
	 */

	अगर (mode >= XFER_MW_DMA_0)
		addr = 0;
	अन्यथा
		addr = addr_timing[pci_घड़ी][pio];

	अगर (pair) अणु
		u8 pair_addr;
		/* Hardware स्थिरraपूर्णांक */
		अगर (pair->dma_mode)
			pair_addr = 0;
		अन्यथा
			pair_addr = addr_timing[pci_घड़ी][pair->pio_mode - XFER_PIO_0];
		अगर (pair_addr > addr)
			addr = pair_addr;
	पूर्ण

	/* Commence primary programming sequence */
	/* First we load the device number पूर्णांकo the timing select */
	ioग_लिखो8(adev->devno, regio + MISC_REG);
	/* Now we load the data timings पूर्णांकo पढ़ो data/ग_लिखो data */
	अगर (mode < XFER_MW_DMA_0) अणु
		ioग_लिखो8(data_rec_timing[pci_घड़ी][pio], regio + READ_REG);
		ioग_लिखो8(data_rec_timing[pci_घड़ी][pio], regio + WRITE_REG);
	पूर्ण अन्यथा अगर (mode < XFER_UDMA_0) अणु
		ioग_लिखो8(dma_data_rec_timing[pci_घड़ी][dma], regio + READ_REG);
		ioग_लिखो8(dma_data_rec_timing[pci_घड़ी][dma], regio + WRITE_REG);
	पूर्ण
	/* Finally we load the address setup पूर्णांकo the misc रेजिस्टर */
	ioग_लिखो8(addr | adev->devno, regio + MISC_REG);

	/* Programming sequence complete, timing 0 dev 0, timing 1 dev 1 */
	ioग_लिखो8(0x85, regio + CNTRL_REG);

	/* Switch back to IDE mode */
	optidma_lock(ap);

	/* Note: at this poपूर्णांक our programming is incomplete. We are
	   not supposed to program PCI 0x43 "things we hacked onto the chip"
	   until we've करोne both sets of PIO/DMA timings */
पूर्ण

/**
 *	optiplus_mode_setup	-	DMA setup क्रम Firestar Plus
 *	@ap: ATA port
 *	@adev: device
 *	@mode: desired mode
 *
 *	The Firestar plus has additional UDMA functionality क्रम UDMA0-2 and
 *	requires we करो some additional work. Because the base work we must करो
 *	is mostly shared we wrap the Firestar setup functionality in this
 *	one
 */

अटल व्योम optiplus_mode_setup(काष्ठा ata_port *ap, काष्ठा ata_device *adev, u8 mode)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 udcfg;
	u8 udslave;
	पूर्णांक dev2 = 2 * adev->devno;
	पूर्णांक unit = 2 * ap->port_no + adev->devno;
	पूर्णांक udma = mode - XFER_UDMA_0;

	pci_पढ़ो_config_byte(pdev, 0x44, &udcfg);
	अगर (mode <= XFER_UDMA_0) अणु
		udcfg &= ~(1 << unit);
		optidma_mode_setup(ap, adev, adev->dma_mode);
	पूर्ण अन्यथा अणु
		udcfg |=  (1 << unit);
		अगर (ap->port_no) अणु
			pci_पढ़ो_config_byte(pdev, 0x45, &udslave);
			udslave &= ~(0x03 << dev2);
			udslave |= (udma << dev2);
			pci_ग_लिखो_config_byte(pdev, 0x45, udslave);
		पूर्ण अन्यथा अणु
			udcfg &= ~(0x30 << dev2);
			udcfg |= (udma << dev2);
		पूर्ण
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, 0x44, udcfg);
पूर्ण

/**
 *	optidma_set_pio_mode	-	PIO setup callback
 *	@ap: ATA port
 *	@adev: Device
 *
 *	The libata core provides separate functions क्रम handling PIO and
 *	DMA programming. The architecture of the Firestar makes it easier
 *	क्रम us to have a common function so we provide wrappers
 */

अटल व्योम optidma_set_pio_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	optidma_mode_setup(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	optidma_set_dma_mode	-	DMA setup callback
 *	@ap: ATA port
 *	@adev: Device
 *
 *	The libata core provides separate functions क्रम handling PIO and
 *	DMA programming. The architecture of the Firestar makes it easier
 *	क्रम us to have a common function so we provide wrappers
 */

अटल व्योम optidma_set_dma_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	optidma_mode_setup(ap, adev, adev->dma_mode);
पूर्ण

/**
 *	optiplus_set_pio_mode	-	PIO setup callback
 *	@ap: ATA port
 *	@adev: Device
 *
 *	The libata core provides separate functions क्रम handling PIO and
 *	DMA programming. The architecture of the Firestar makes it easier
 *	क्रम us to have a common function so we provide wrappers
 */

अटल व्योम optiplus_set_pio_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	optiplus_mode_setup(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	optiplus_set_dma_mode	-	DMA setup callback
 *	@ap: ATA port
 *	@adev: Device
 *
 *	The libata core provides separate functions क्रम handling PIO and
 *	DMA programming. The architecture of the Firestar makes it easier
 *	क्रम us to have a common function so we provide wrappers
 */

अटल व्योम optiplus_set_dma_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	optiplus_mode_setup(ap, adev, adev->dma_mode);
पूर्ण

/**
 *	optidma_make_bits43	-	PCI setup helper
 *	@adev: ATA device
 *
 *	Turn the ATA device setup पूर्णांकo PCI configuration bits
 *	क्रम रेजिस्टर 0x43 and वापस the two bits needed.
 */

अटल u8 optidma_make_bits43(काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 bits43[5] = अणु
		0, 0, 0, 1, 2
	पूर्ण;
	अगर (!ata_dev_enabled(adev))
		वापस 0;
	अगर (adev->dma_mode)
		वापस adev->dma_mode - XFER_MW_DMA_0;
	वापस bits43[adev->pio_mode - XFER_PIO_0];
पूर्ण

/**
 *	optidma_set_mode	-	mode setup
 *	@link: link to set up
 *	@r_failed: out parameter क्रम failed device
 *
 *	Use the standard setup to tune the chipset and then finalise the
 *	configuration by writing the nibble of extra bits of data पूर्णांकo
 *	the chip.
 */

अटल पूर्णांक optidma_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed)
अणु
	काष्ठा ata_port *ap = link->ap;
	u8 r;
	पूर्णांक nybble = 4 * ap->port_no;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक rc  = ata_करो_set_mode(link, r_failed);
	अगर (rc == 0) अणु
		pci_पढ़ो_config_byte(pdev, 0x43, &r);

		r &= (0x0F << nybble);
		r |= (optidma_make_bits43(&link->device[0]) +
		     (optidma_make_bits43(&link->device[0]) << 2)) << nybble;
		pci_ग_लिखो_config_byte(pdev, 0x43, r);
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा optidma_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations optidma_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= optidma_set_pio_mode,
	.set_dmamode	= optidma_set_dma_mode,
	.set_mode	= optidma_set_mode,
	.prereset	= optidma_pre_reset,
पूर्ण;

अटल काष्ठा ata_port_operations optiplus_port_ops = अणु
	.inherits	= &optidma_port_ops,
	.set_piomode	= optiplus_set_pio_mode,
	.set_dmamode	= optiplus_set_dma_mode,
पूर्ण;

/**
 *	optiplus_with_udma	-	Look क्रम UDMA capable setup
 *	@pdev: ATA controller
 */

अटल पूर्णांक optiplus_with_udma(काष्ठा pci_dev *pdev)
अणु
	u8 r;
	पूर्णांक ret = 0;
	पूर्णांक ioport = 0x22;
	काष्ठा pci_dev *dev1;

	/* Find function 1 */
	dev1 = pci_get_device(0x1045, 0xC701, शून्य);
	अगर (dev1 == शून्य)
		वापस 0;

	/* Rev must be >= 0x10 */
	pci_पढ़ो_config_byte(dev1, 0x08, &r);
	अगर (r < 0x10)
		जाओ करोne_nomsg;
	/* Read the chipset प्रणाली configuration to check our mode */
	pci_पढ़ो_config_byte(dev1, 0x5F, &r);
	ioport |= (r << 8);
	outb(0x10, ioport);
	/* Must be 66Mhz sync */
	अगर ((inb(ioport + 2) & 1) == 0)
		जाओ करोne;

	/* Check the ATA arbitration/timing is suitable */
	pci_पढ़ो_config_byte(pdev, 0x42, &r);
	अगर ((r & 0x36) != 0x36)
		जाओ करोne;
	pci_पढ़ो_config_byte(dev1, 0x52, &r);
	अगर (r & 0x80)	/* IDEसूची disabled */
		ret = 1;
करोne:
	prपूर्णांकk(KERN_WARNING "UDMA not supported in this configuration.\n");
करोne_nomsg:		/* Wrong chip revision */
	pci_dev_put(dev1);
	वापस ret;
पूर्ण

अटल पूर्णांक optidma_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info_82c700 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &optidma_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_82c700_udma = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.port_ops = &optiplus_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info_82c700, शून्य पूर्ण;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&dev->dev, DRV_VERSION);

	rc = pcim_enable_device(dev);
	अगर (rc)
		वापस rc;

	/* Fixed location chipset magic */
	inw(0x1F1);
	inw(0x1F1);
	pci_घड़ी = inb(0x1F5) & 1;		/* 0 = 33Mhz, 1 = 25Mhz */

	अगर (optiplus_with_udma(dev))
		ppi[0] = &info_82c700_udma;

	वापस ata_pci_bmdma_init_one(dev, ppi, &optidma_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id optidma[] = अणु
	अणु PCI_VDEVICE(OPTI, 0xD568), पूर्ण,		/* Opti 82C700 */

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver optidma_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= optidma,
	.probe 		= optidma_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(optidma_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Opti Firestar/Firestar Plus");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, optidma);
MODULE_VERSION(DRV_VERSION);
