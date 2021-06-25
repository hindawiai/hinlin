<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Promise PATA TX2/TX4/TX2000/133 IDE driver क्रम pdc20268 to pdc20277.
 *
 *  Ported to libata by:
 *  Albert Lee <albertcc@tw.ibm.com> IBM Corporation
 *
 *  Copyright (C) 1998-2002		Andre Hedrick <andre@linux-ide.org>
 *  Portions Copyright (C) 1999 Promise Technology, Inc.
 *
 *  Author: Frank Tiernan (frankt@promise.com)
 *  Released under terms of General Public License
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware inक्रमmation only available under NDA.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kसमय.स>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_pdc2027x"
#घोषणा DRV_VERSION	"1.0"
#अघोषित PDC_DEBUG

#अगर_घोषित PDC_DEBUG
#घोषणा PDPRINTK(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा PDPRINTK(fmt, args...)
#पूर्ण_अगर

क्रमागत अणु
	PDC_MMIO_BAR		= 5,

	PDC_UDMA_100		= 0,
	PDC_UDMA_133		= 1,

	PDC_100_MHZ		= 100000000,
	PDC_133_MHZ		= 133333333,

	PDC_SYS_CTL		= 0x1100,
	PDC_ATA_CTL		= 0x1104,
	PDC_GLOBAL_CTL		= 0x1108,
	PDC_CTCR0		= 0x110C,
	PDC_CTCR1		= 0x1110,
	PDC_BYTE_COUNT		= 0x1120,
	PDC_PLL_CTL		= 0x1202,
पूर्ण;

अटल पूर्णांक pdc2027x_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pdc2027x_reinit_one(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
अटल पूर्णांक pdc2027x_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
अटल व्योम pdc2027x_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev);
अटल व्योम pdc2027x_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev);
अटल पूर्णांक pdc2027x_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित दीर्घ pdc2027x_mode_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask);
अटल पूर्णांक pdc2027x_cable_detect(काष्ठा ata_port *ap);
अटल पूर्णांक pdc2027x_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed);

/*
 * ATA Timing Tables based on 133MHz controller घड़ी.
 * These tables are only used when the controller is in 133MHz घड़ी.
 * If the controller is in 100MHz घड़ी, the ASIC hardware will
 * set the timing रेजिस्टरs स्वतःmatically when "set feature" command
 * is issued to the device. However, अगर the controller घड़ी is 133MHz,
 * the following tables must be used.
 */
अटल स्थिर काष्ठा pdc2027x_pio_timing अणु
	u8 value0, value1, value2;
पूर्ण pdc2027x_pio_timing_tbl[] = अणु
	अणु 0xfb, 0x2b, 0xac पूर्ण, /* PIO mode 0 */
	अणु 0x46, 0x29, 0xa4 पूर्ण, /* PIO mode 1 */
	अणु 0x23, 0x26, 0x64 पूर्ण, /* PIO mode 2 */
	अणु 0x27, 0x0d, 0x35 पूर्ण, /* PIO mode 3, IORDY on, Prefetch off */
	अणु 0x23, 0x09, 0x25 पूर्ण, /* PIO mode 4, IORDY on, Prefetch off */
पूर्ण;

अटल स्थिर काष्ठा pdc2027x_mdma_timing अणु
	u8 value0, value1;
पूर्ण pdc2027x_mdma_timing_tbl[] = अणु
	अणु 0xdf, 0x5f पूर्ण, /* MDMA mode 0 */
	अणु 0x6b, 0x27 पूर्ण, /* MDMA mode 1 */
	अणु 0x69, 0x25 पूर्ण, /* MDMA mode 2 */
पूर्ण;

अटल स्थिर काष्ठा pdc2027x_udma_timing अणु
	u8 value0, value1, value2;
पूर्ण pdc2027x_udma_timing_tbl[] = अणु
	अणु 0x4a, 0x0f, 0xd5 पूर्ण, /* UDMA mode 0 */
	अणु 0x3a, 0x0a, 0xd0 पूर्ण, /* UDMA mode 1 */
	अणु 0x2a, 0x07, 0xcd पूर्ण, /* UDMA mode 2 */
	अणु 0x1a, 0x05, 0xcd पूर्ण, /* UDMA mode 3 */
	अणु 0x1a, 0x03, 0xcd पूर्ण, /* UDMA mode 4 */
	अणु 0x1a, 0x02, 0xcb पूर्ण, /* UDMA mode 5 */
	अणु 0x1a, 0x01, 0xcb पूर्ण, /* UDMA mode 6 */
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pdc2027x_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20268), PDC_UDMA_100 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20269), PDC_UDMA_133 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20270), PDC_UDMA_100 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20271), PDC_UDMA_133 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20275), PDC_UDMA_133 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20276), PDC_UDMA_133 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20277), PDC_UDMA_133 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver pdc2027x_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= pdc2027x_pci_tbl,
	.probe			= pdc2027x_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= pdc2027x_reinit_one,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा pdc2027x_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pdc2027x_pata100_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.check_atapi_dma	= pdc2027x_check_atapi_dma,
	.cable_detect		= pdc2027x_cable_detect,
	.prereset		= pdc2027x_prereset,
पूर्ण;

अटल काष्ठा ata_port_operations pdc2027x_pata133_ops = अणु
	.inherits		= &pdc2027x_pata100_ops,
	.mode_filter		= pdc2027x_mode_filter,
	.set_piomode		= pdc2027x_set_piomode,
	.set_dmamode		= pdc2027x_set_dmamode,
	.set_mode		= pdc2027x_set_mode,
पूर्ण;

अटल काष्ठा ata_port_info pdc2027x_port_info[] = अणु
	/* PDC_UDMA_100 */
	अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &pdc2027x_pata100_ops,
	पूर्ण,
	/* PDC_UDMA_133 */
	अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc2027x_pata133_ops,
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("Andre Hedrick, Frank Tiernan, Albert Lee");
MODULE_DESCRIPTION("libata driver module for Promise PDC20268 to PDC20277");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, pdc2027x_pci_tbl);

/**
 *	port_mmio - Get the MMIO address of PDC2027x extended रेजिस्टरs
 *	@ap: Port
 *	@offset: offset from mmio base
 */
अटल अंतरभूत व्योम __iomem *port_mmio(काष्ठा ata_port *ap, अचिन्हित पूर्णांक offset)
अणु
	वापस ap->host->iomap[PDC_MMIO_BAR] + ap->port_no * 0x100 + offset;
पूर्ण

/**
 *	dev_mmio - Get the MMIO address of PDC2027x extended रेजिस्टरs
 *	@ap: Port
 *	@adev: device
 *	@offset: offset from mmio base
 */
अटल अंतरभूत व्योम __iomem *dev_mmio(काष्ठा ata_port *ap, काष्ठा ata_device *adev, अचिन्हित पूर्णांक offset)
अणु
	u8 adj = (adev->devno) ? 0x08 : 0x00;
	वापस port_mmio(ap, offset) + adj;
पूर्ण

/**
 *	pdc2027x_cable_detect - Probe host controller cable detect info
 *	@ap: Port क्रम which cable detect info is desired
 *
 *	Read 80c cable indicator from Promise extended रेजिस्टर.
 *      This रेजिस्टर is latched when the प्रणाली is reset.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */
अटल पूर्णांक pdc2027x_cable_detect(काष्ठा ata_port *ap)
अणु
	u32 cgcr;

	/* check cable detect results */
	cgcr = ioपढ़ो32(port_mmio(ap, PDC_GLOBAL_CTL));
	अगर (cgcr & (1 << 26))
		जाओ cbl40;

	PDPRINTK("No cable or 80-conductor cable on port %d\n", ap->port_no);

	वापस ATA_CBL_PATA80;
cbl40:
	prपूर्णांकk(KERN_INFO DRV_NAME ": 40-conductor cable detected on port %d\n", ap->port_no);
	वापस ATA_CBL_PATA40;
पूर्ण

/**
 * pdc2027x_port_enabled - Check PDC ATA control रेजिस्टर to see whether the port is enabled.
 * @ap: Port to check
 */
अटल अंतरभूत पूर्णांक pdc2027x_port_enabled(काष्ठा ata_port *ap)
अणु
	वापस ioपढ़ो8(port_mmio(ap, PDC_ATA_CTL)) & 0x02;
पूर्ण

/**
 *	pdc2027x_prereset - prereset क्रम PATA host controller
 *	@link: Target link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Probeinit including cable detection.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल पूर्णांक pdc2027x_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	/* Check whether port enabled */
	अगर (!pdc2027x_port_enabled(link->ap))
		वापस -ENOENT;
	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	pdc2027x_mode_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: list of modes proposed
 *
 *	Block UDMA on devices that cause trouble with this controller.
 */

अटल अचिन्हित दीर्घ pdc2027x_mode_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];
	काष्ठा ata_device *pair = ata_dev_pair(adev);

	अगर (adev->class != ATA_DEV_ATA || adev->devno == 0 || pair == शून्य)
		वापस mask;

	/* Check क्रम slave of a Maxtor at UDMA6 */
	ata_id_c_string(pair->id, model_num, ATA_ID_PROD,
			  ATA_ID_PROD_LEN + 1);
	/* If the master is a maxtor in UDMA6 then the slave should not use UDMA 6 */
	अगर (म_माला(model_num, "Maxtor") == शून्य && pair->dma_mode == XFER_UDMA_6)
		mask &= ~ (1 << (6 + ATA_SHIFT_UDMA));

	वापस mask;
पूर्ण

/**
 *	pdc2027x_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port to configure
 *	@adev: um
 *
 *	Set PIO mode क्रम device.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम pdc2027x_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio = adev->pio_mode - XFER_PIO_0;
	u32 ctcr0, ctcr1;

	PDPRINTK("adev->pio_mode[%X]\n", adev->pio_mode);

	/* Sanity check */
	अगर (pio > 4) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": Unknown pio mode [%d] ignored\n", pio);
		वापस;

	पूर्ण

	/* Set the PIO timing रेजिस्टरs using value table क्रम 133MHz */
	PDPRINTK("Set pio regs... \n");

	ctcr0 = ioपढ़ो32(dev_mmio(ap, adev, PDC_CTCR0));
	ctcr0 &= 0xffff0000;
	ctcr0 |= pdc2027x_pio_timing_tbl[pio].value0 |
		(pdc2027x_pio_timing_tbl[pio].value1 << 8);
	ioग_लिखो32(ctcr0, dev_mmio(ap, adev, PDC_CTCR0));

	ctcr1 = ioपढ़ो32(dev_mmio(ap, adev, PDC_CTCR1));
	ctcr1 &= 0x00ffffff;
	ctcr1 |= (pdc2027x_pio_timing_tbl[pio].value2 << 24);
	ioग_लिखो32(ctcr1, dev_mmio(ap, adev, PDC_CTCR1));

	PDPRINTK("Set pio regs done\n");

	PDPRINTK("Set to pio mode[%u] \n", pio);
पूर्ण

/**
 *	pdc2027x_set_dmamode - Initialize host controller PATA UDMA timings
 *	@ap: Port to configure
 *	@adev: um
 *
 *	Set UDMA mode क्रम device.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */
अटल व्योम pdc2027x_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक dma_mode = adev->dma_mode;
	u32 ctcr0, ctcr1;

	अगर ((dma_mode >= XFER_UDMA_0) &&
	   (dma_mode <= XFER_UDMA_6)) अणु
		/* Set the UDMA timing रेजिस्टरs with value table क्रम 133MHz */
		अचिन्हित पूर्णांक udma_mode = dma_mode & 0x07;

		अगर (dma_mode == XFER_UDMA_2) अणु
			/*
			 * Turn off tHOLD.
			 * If tHOLD is '1', the hardware will add half घड़ी क्रम data hold समय.
			 * This code segment seems to be no effect. tHOLD will be overwritten below.
			 */
			ctcr1 = ioपढ़ो32(dev_mmio(ap, adev, PDC_CTCR1));
			ioग_लिखो32(ctcr1 & ~(1 << 7), dev_mmio(ap, adev, PDC_CTCR1));
		पूर्ण

		PDPRINTK("Set udma regs... \n");

		ctcr1 = ioपढ़ो32(dev_mmio(ap, adev, PDC_CTCR1));
		ctcr1 &= 0xff000000;
		ctcr1 |= pdc2027x_udma_timing_tbl[udma_mode].value0 |
			(pdc2027x_udma_timing_tbl[udma_mode].value1 << 8) |
			(pdc2027x_udma_timing_tbl[udma_mode].value2 << 16);
		ioग_लिखो32(ctcr1, dev_mmio(ap, adev, PDC_CTCR1));

		PDPRINTK("Set udma regs done\n");

		PDPRINTK("Set to udma mode[%u] \n", udma_mode);

	पूर्ण अन्यथा  अगर ((dma_mode >= XFER_MW_DMA_0) &&
		   (dma_mode <= XFER_MW_DMA_2)) अणु
		/* Set the MDMA timing रेजिस्टरs with value table क्रम 133MHz */
		अचिन्हित पूर्णांक mdma_mode = dma_mode & 0x07;

		PDPRINTK("Set mdma regs... \n");
		ctcr0 = ioपढ़ो32(dev_mmio(ap, adev, PDC_CTCR0));

		ctcr0 &= 0x0000ffff;
		ctcr0 |= (pdc2027x_mdma_timing_tbl[mdma_mode].value0 << 16) |
			(pdc2027x_mdma_timing_tbl[mdma_mode].value1 << 24);

		ioग_लिखो32(ctcr0, dev_mmio(ap, adev, PDC_CTCR0));
		PDPRINTK("Set mdma regs done\n");

		PDPRINTK("Set to mdma mode[%u] \n", mdma_mode);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": Unknown dma mode [%u] ignored\n", dma_mode);
	पूर्ण
पूर्ण

/**
 *	pdc2027x_set_mode - Set the timing रेजिस्टरs back to correct values.
 *	@link: link to configure
 *	@r_failed: Returned device क्रम failure
 *
 *	The pdc2027x hardware will look at "SET FEATURES" and change the timing रेजिस्टरs
 *	स्वतःmatically. The values set by the hardware might be incorrect, under 133Mhz PLL.
 *	This function overग_लिखोs the possibly incorrect values set by the hardware to be correct.
 */
अटल पूर्णांक pdc2027x_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *dev;
	पूर्णांक rc;

	rc = ata_करो_set_mode(link, r_failed);
	अगर (rc < 0)
		वापस rc;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		pdc2027x_set_piomode(ap, dev);

		/*
		 * Enable prefetch अगर the device support PIO only.
		 */
		अगर (dev->xfer_shअगरt == ATA_SHIFT_PIO) अणु
			u32 ctcr1 = ioपढ़ो32(dev_mmio(ap, dev, PDC_CTCR1));
			ctcr1 |= (1 << 25);
			ioग_लिखो32(ctcr1, dev_mmio(ap, dev, PDC_CTCR1));

			PDPRINTK("Turn on prefetch\n");
		पूर्ण अन्यथा अणु
			pdc2027x_set_dmamode(ap, dev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	pdc2027x_check_atapi_dma - Check whether ATAPI DMA can be supported क्रम this command
 *	@qc: Metadata associated with taskfile to check
 *
 *	LOCKING:
 *	None (inherited from caller).
 *
 *	RETURNS: 0 when ATAPI DMA can be used
 *		 1 otherwise
 */
अटल पूर्णांक pdc2027x_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	u8 *scsicmd = cmd->cmnd;
	पूर्णांक rc = 1; /* atapi dma off by शेष */

	/*
	 * This workaround is from Promise's GPL driver.
	 * If ATAPI DMA is used क्रम commands not in the
	 * following white list, say MODE_SENSE and REQUEST_SENSE,
	 * pdc2027x might hit the irq lost problem.
	 */
	चयन (scsicmd[0]) अणु
	हाल READ_10:
	हाल WRITE_10:
	हाल READ_12:
	हाल WRITE_12:
	हाल READ_6:
	हाल WRITE_6:
	हाल 0xad: /* READ_DVD_STRUCTURE */
	हाल 0xbe: /* READ_CD */
		/* ATAPI DMA is ok */
		rc = 0;
		अवरोध;
	शेष:
		;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * pdc_पढ़ो_counter - Read the ctr counter
 * @host: target ATA host
 */

अटल दीर्घ pdc_पढ़ो_counter(काष्ठा ata_host *host)
अणु
	व्योम __iomem *mmio_base = host->iomap[PDC_MMIO_BAR];
	दीर्घ counter;
	पूर्णांक retry = 1;
	u32 bccrl, bccrh, bccrlv, bccrhv;

retry:
	bccrl = ioपढ़ो32(mmio_base + PDC_BYTE_COUNT) & 0x7fff;
	bccrh = ioपढ़ो32(mmio_base + PDC_BYTE_COUNT + 0x100) & 0x7fff;

	/* Read the counter values again क्रम verअगरication */
	bccrlv = ioपढ़ो32(mmio_base + PDC_BYTE_COUNT) & 0x7fff;
	bccrhv = ioपढ़ो32(mmio_base + PDC_BYTE_COUNT + 0x100) & 0x7fff;

	counter = (bccrh << 15) | bccrl;

	PDPRINTK("bccrh [%X] bccrl [%X]\n", bccrh,  bccrl);
	PDPRINTK("bccrhv[%X] bccrlv[%X]\n", bccrhv, bccrlv);

	/*
	 * The 30-bit decreasing counter are पढ़ो by 2 pieces.
	 * Incorrect value may be पढ़ो when both bccrh and bccrl are changing.
	 * Ex. When 7900 decrease to 78FF, wrong value 7800 might be पढ़ो.
	 */
	अगर (retry && !(bccrh == bccrhv && bccrl >= bccrlv)) अणु
		retry--;
		PDPRINTK("rereading counter\n");
		जाओ retry;
	पूर्ण

	वापस counter;
पूर्ण

/**
 * pdc_adjust_pll - Adjust the PLL input घड़ी in Hz.
 *
 * @host: target ATA host
 * @pll_घड़ी: The input of PLL in HZ
 * @board_idx: board identअगरier
 */
अटल व्योम pdc_adjust_pll(काष्ठा ata_host *host, दीर्घ pll_घड़ी, अचिन्हित पूर्णांक board_idx)
अणु
	व्योम __iomem *mmio_base = host->iomap[PDC_MMIO_BAR];
	u16 pll_ctl;
	दीर्घ pll_घड़ी_khz = pll_घड़ी / 1000;
	दीर्घ pout_required = board_idx? PDC_133_MHZ:PDC_100_MHZ;
	दीर्घ ratio = pout_required / pll_घड़ी_khz;
	पूर्णांक F, R;

	/* Sanity check */
	अगर (unlikely(pll_घड़ी_khz < 5000L || pll_घड़ी_khz > 70000L)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": Invalid PLL input clock %ldkHz, give up!\n", pll_घड़ी_khz);
		वापस;
	पूर्ण

#अगर_घोषित PDC_DEBUG
	PDPRINTK("pout_required is %ld\n", pout_required);

	/* Show the current घड़ी value of PLL control रेजिस्टर
	 * (maybe alपढ़ोy configured by the firmware)
	 */
	pll_ctl = ioपढ़ो16(mmio_base + PDC_PLL_CTL);

	PDPRINTK("pll_ctl[%X]\n", pll_ctl);
#पूर्ण_अगर

	/*
	 * Calculate the ratio of F, R and OD
	 * POUT = (F + 2) / (( R + 2) * NO)
	 */
	अगर (ratio < 8600L) अणु /* 8.6x */
		/* Using NO = 0x01, R = 0x0D */
		R = 0x0d;
	पूर्ण अन्यथा अगर (ratio < 12900L) अणु /* 12.9x */
		/* Using NO = 0x01, R = 0x08 */
		R = 0x08;
	पूर्ण अन्यथा अगर (ratio < 16100L) अणु /* 16.1x */
		/* Using NO = 0x01, R = 0x06 */
		R = 0x06;
	पूर्ण अन्यथा अगर (ratio < 64000L) अणु /* 64x */
		R = 0x00;
	पूर्ण अन्यथा अणु
		/* Invalid ratio */
		prपूर्णांकk(KERN_ERR DRV_NAME ": Invalid ratio %ld, give up!\n", ratio);
		वापस;
	पूर्ण

	F = (ratio * (R+2)) / 1000 - 2;

	अगर (unlikely(F < 0 || F > 127)) अणु
		/* Invalid F */
		prपूर्णांकk(KERN_ERR DRV_NAME ": F[%d] invalid!\n", F);
		वापस;
	पूर्ण

	PDPRINTK("F[%d] R[%d] ratio*1000[%ld]\n", F, R, ratio);

	pll_ctl = (R << 8) | F;

	PDPRINTK("Writing pll_ctl[%X]\n", pll_ctl);

	ioग_लिखो16(pll_ctl, mmio_base + PDC_PLL_CTL);
	ioपढ़ो16(mmio_base + PDC_PLL_CTL); /* flush */

	/* Wait the PLL circuit to be stable */
	msleep(30);

#अगर_घोषित PDC_DEBUG
	/*
	 *  Show the current घड़ी value of PLL control रेजिस्टर
	 * (maybe configured by the firmware)
	 */
	pll_ctl = ioपढ़ो16(mmio_base + PDC_PLL_CTL);

	PDPRINTK("pll_ctl[%X]\n", pll_ctl);
#पूर्ण_अगर

	वापस;
पूर्ण

/**
 * pdc_detect_pll_input_घड़ी - Detect the PLL input घड़ी in Hz.
 * @host: target ATA host
 * Ex. 16949000 on 33MHz PCI bus क्रम pdc20275.
 *     Half of the PCI घड़ी.
 */
अटल दीर्घ pdc_detect_pll_input_घड़ी(काष्ठा ata_host *host)
अणु
	व्योम __iomem *mmio_base = host->iomap[PDC_MMIO_BAR];
	u32 scr;
	दीर्घ start_count, end_count;
	kसमय_प्रकार start_समय, end_समय;
	दीर्घ pll_घड़ी, usec_elapsed;

	/* Start the test mode */
	scr = ioपढ़ो32(mmio_base + PDC_SYS_CTL);
	PDPRINTK("scr[%X]\n", scr);
	ioग_लिखो32(scr | (0x01 << 14), mmio_base + PDC_SYS_CTL);
	ioपढ़ो32(mmio_base + PDC_SYS_CTL); /* flush */

	/* Read current counter value */
	start_count = pdc_पढ़ो_counter(host);
	start_समय = kसमय_get();

	/* Let the counter run क्रम 100 ms. */
	msleep(100);

	/* Read the counter values again */
	end_count = pdc_पढ़ो_counter(host);
	end_समय = kसमय_get();

	/* Stop the test mode */
	scr = ioपढ़ो32(mmio_base + PDC_SYS_CTL);
	PDPRINTK("scr[%X]\n", scr);
	ioग_लिखो32(scr & ~(0x01 << 14), mmio_base + PDC_SYS_CTL);
	ioपढ़ो32(mmio_base + PDC_SYS_CTL); /* flush */

	/* calculate the input घड़ी in Hz */
	usec_elapsed = (दीर्घ) kसमय_us_delta(end_समय, start_समय);

	pll_घड़ी = ((start_count - end_count) & 0x3fffffff) / 100 *
		(100000000 / usec_elapsed);

	PDPRINTK("start[%ld] end[%ld] \n", start_count, end_count);
	PDPRINTK("PLL input clock[%ld]Hz\n", pll_घड़ी);

	वापस pll_घड़ी;
पूर्ण

/**
 * pdc_hardware_init - Initialize the hardware.
 * @host: target ATA host
 * @board_idx: board identअगरier
 */
अटल व्योम pdc_hardware_init(काष्ठा ata_host *host, अचिन्हित पूर्णांक board_idx)
अणु
	दीर्घ pll_घड़ी;

	/*
	 * Detect PLL input घड़ी rate.
	 * On some प्रणाली, where PCI bus is running at non-standard घड़ी rate.
	 * Ex. 25MHz or 40MHz, we have to adjust the cycle_समय.
	 * The pdc20275 controller employs PLL circuit to help correct timing रेजिस्टरs setting.
	 */
	pll_घड़ी = pdc_detect_pll_input_घड़ी(host);

	dev_info(host->dev, "PLL input clock %ld kHz\n", pll_घड़ी/1000);

	/* Adjust PLL control रेजिस्टर */
	pdc_adjust_pll(host, pll_घड़ी, board_idx);
पूर्ण

/**
 * pdc_ata_setup_port - setup the mmio address
 * @port: ata ioports to setup
 * @base: base address
 */
अटल व्योम pdc_ata_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		=
	port->data_addr		= base;
	port->feature_addr	=
	port->error_addr	= base + 0x05;
	port->nsect_addr	= base + 0x0a;
	port->lbal_addr		= base + 0x0f;
	port->lbam_addr		= base + 0x10;
	port->lbah_addr		= base + 0x15;
	port->device_addr	= base + 0x1a;
	port->command_addr	=
	port->status_addr	= base + 0x1f;
	port->altstatus_addr	=
	port->ctl_addr		= base + 0x81a;
पूर्ण

/**
 * pdc2027x_init_one - PCI probe function
 * Called when an instance of PCI adapter is inserted.
 * This function checks whether the hardware is supported,
 * initialize hardware and रेजिस्टर an instance of ata_host to
 * libata.  (implements काष्ठा pci_driver.probe() )
 *
 * @pdev: instance of pci_dev found
 * @ent:  matching entry in the id_tbl[]
 */
अटल पूर्णांक pdc2027x_init_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर अचिन्हित दीर्घ cmd_offset[] = अणु 0x17c0, 0x15c0 पूर्ण;
	अटल स्थिर अचिन्हित दीर्घ bmdma_offset[] = अणु 0x1000, 0x1008 पूर्ण;
	अचिन्हित पूर्णांक board_idx = (अचिन्हित पूर्णांक) ent->driver_data;
	स्थिर काष्ठा ata_port_info *ppi[] =
		अणु &pdc2027x_port_info[board_idx], शून्य पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *mmio_base;
	पूर्णांक i, rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* alloc host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 2);
	अगर (!host)
		वापस -ENOMEM;

	/* acquire resources and fill host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, 1 << PDC_MMIO_BAR, DRV_NAME);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);

	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;

	mmio_base = host->iomap[PDC_MMIO_BAR];

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		pdc_ata_setup_port(&ap->ioaddr, mmio_base + cmd_offset[i]);
		ap->ioaddr.bmdma_addr = mmio_base + bmdma_offset[i];

		ata_port_pbar_desc(ap, PDC_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, PDC_MMIO_BAR, cmd_offset[i], "cmd");
	पूर्ण

	//pci_enable_पूर्णांकx(pdev);

	/* initialize adapter */
	pdc_hardware_init(host, board_idx);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &pdc2027x_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pdc2027x_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	अचिन्हित पूर्णांक board_idx;
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->device == PCI_DEVICE_ID_PROMISE_20268 ||
	    pdev->device == PCI_DEVICE_ID_PROMISE_20270)
		board_idx = PDC_UDMA_100;
	अन्यथा
		board_idx = PDC_UDMA_133;

	pdc_hardware_init(host, board_idx);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

module_pci_driver(pdc2027x_pci_driver);
