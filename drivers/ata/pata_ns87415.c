<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_ns87415.c - NS87415 (and PARISC SUPERIO 87560) PATA
 *
 *	(C) 2005 Red Hat <alan@lxorguk.ukuu.org.uk>
 *
 *    This is a fairly generic MWDMA controller. It has some limitations
 *    as it requires timing reloads on PIO/DMA transitions but it is otherwise
 *    fairly well deचिन्हित.
 *
 *    This driver assumes the firmware has left the chip in a valid ST506
 *    compliant state, either legacy IRQ 14/15 or native INTA shared. You
 *    may need to add platक्रमm code अगर your प्रणाली fails to करो this.
 *
 *    The same cell appears in the 87560 controller used by some PARISC
 *    प्रणालीs. This has its own special mountain of errata.
 *
 *    TODO:
 *	Get someone to test on SPARC
 *	Implement lazy pio/dma चयनing क्रम better perक्रमmance
 *	8bit shared timing.
 *	See अगर we need to समाप्त the FIFO क्रम ATAPI
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

#घोषणा DRV_NAME	"pata_ns87415"
#घोषणा DRV_VERSION	"0.0.1"

/**
 *	ns87415_set_mode - Initialize host controller mode timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device whose timings we are configuring
 *	@mode: Mode to set
 *
 *	Program the mode रेजिस्टरs क्रम this controller, channel and
 *	device. Because the chip is quite an old design we have to करो this
 *	क्रम PIO/DMA चयनes.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम ns87415_set_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev, u8 mode)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	पूर्णांक unit		= 2 * ap->port_no + adev->devno;
	पूर्णांक timing		= 0x44 + 2 * unit;
	अचिन्हित दीर्घ T		= 1000000000 / 33333;	/* PCI घड़ीs */
	काष्ठा ata_timing t;
	u16 घड़ीing;
	u8 iordy;
	u8 status;

	/* Timing रेजिस्टर क्रमmat is 17 - low nybble पढ़ो timing with
	   the high nybble being 16 - x क्रम recovery समय in PCI घड़ीs */

	ata_timing_compute(adev, adev->pio_mode, &t, T, 0);

	घड़ीing = 17 - clamp_val(t.active, 2, 17);
	घड़ीing |= (16 - clamp_val(t.recover, 1, 16)) << 4;
 	/* Use the same timing क्रम पढ़ो and ग_लिखो bytes */
	घड़ीing |= (घड़ीing << 8);
	pci_ग_लिखो_config_word(dev, timing, घड़ीing);

	/* Set the IORDY enable versus DMA enable on or off properly */
	pci_पढ़ो_config_byte(dev, 0x42, &iordy);
	iordy &= ~(1 << (4 + unit));
	अगर (mode >= XFER_MW_DMA_0 || !ata_pio_need_iordy(adev))
		iordy |= (1 << (4 + unit));

	/* Paranoia: We shouldn't ever get here with busy ग_लिखो buffers
	   but अगर so रुको */

	pci_पढ़ो_config_byte(dev, 0x43, &status);
	जबतक (status & 0x03) अणु
		udelay(1);
		pci_पढ़ो_config_byte(dev, 0x43, &status);
	पूर्ण
	/* Flip the IORDY/DMA bits now we are sure the ग_लिखो buffers are
	   clear */
	pci_ग_लिखो_config_byte(dev, 0x42, iordy);

	/* TODO: Set byte 54 command timing to the best 8bit
	   mode shared by all four devices */
पूर्ण

/**
 *	ns87415_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम ns87415_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	ns87415_set_mode(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	ns87415_bmdma_setup		-	Set up DMA
 *	@qc: Command block
 *
 *	Set up क्रम bus mastering DMA. We have to करो this ourselves
 *	rather than use the helper due to a chip erratum
 */

अटल व्योम ns87415_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	u8 dmactl;

	/* load PRD table addr. */
	mb();	/* make sure PRD table ग_लिखोs are visible to controller */
	ioग_लिखो32(ap->bmdma_prd_dma, ap->ioaddr.bmdma_addr + ATA_DMA_TABLE_OFS);

	/* specअगरy data direction, triple-check start bit is clear */
	dmactl = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	dmactl &= ~(ATA_DMA_WR | ATA_DMA_START);
	/* Due to an erratum we need to ग_लिखो these bits to the wrong
	   place - which करोes save us an I/O bizarrely */
	dmactl |= ATA_DMA_INTR | ATA_DMA_ERR;
	अगर (!rw)
		dmactl |= ATA_DMA_WR;
	ioग_लिखो8(dmactl, ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

/**
 *	ns87415_bmdma_start		-	Begin DMA transfer
 *	@qc: Command block
 *
 *	Switch the timings क्रम the chip and set up क्रम a DMA transfer
 *	beक्रमe the DMA burst begins.
 *
 *	FIXME: We should करो lazy चयनing on bmdma_start versus
 *	ata_pio_data_xfer क्रम better perक्रमmance.
 */

अटल व्योम ns87415_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	ns87415_set_mode(qc->ap, qc->dev, qc->dev->dma_mode);
	ata_bmdma_start(qc);
पूर्ण

/**
 *	ns87415_bmdma_stop		-	End DMA transfer
 *	@qc: Command block
 *
 *	End DMA mode and चयन the controller back पूर्णांकo PIO mode
 */

अटल व्योम ns87415_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	ata_bmdma_stop(qc);
	ns87415_set_mode(qc->ap, qc->dev, qc->dev->pio_mode);
पूर्ण

/**
 *	ns87415_irq_clear		-	Clear पूर्णांकerrupt
 *	@ap: Channel to clear
 *
 *	Erratum: Due to a chip bug रेजिस्टरs 02 and 0A bit 1 and 2 (the
 *	error bits) are reset by writing to रेजिस्टर 00 or 08.
 */

अटल व्योम ns87415_irq_clear(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->ioaddr.bmdma_addr;

	अगर (!mmio)
		वापस;
	ioग_लिखो8((ioपढ़ो8(mmio + ATA_DMA_CMD) | ATA_DMA_INTR | ATA_DMA_ERR),
			mmio + ATA_DMA_CMD);
पूर्ण

/**
 *	ns87415_check_atapi_dma		-	ATAPI DMA filter
 *	@qc: Command block
 *
 *	Disable ATAPI DMA (क्रम now). We may be able to करो DMA अगर we
 *	समाप्त the prefetching. This isn't clear.
 */

अटल पूर्णांक ns87415_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#अगर defined(CONFIG_SUPERIO)

/* SUPERIO 87560 is a PoS chip that NatSem denies exists.
 * Unक्रमtunately, it's built-in on all Astro-based PA-RISC workstations
 * which use the पूर्णांकegrated NS87514 cell क्रम CD-ROM support.
 * i.e we have to support क्रम CD-ROM installs.
 * See drivers/parisc/superio.c क्रम more gory details.
 *
 * Workarounds taken from drivers/ide/pci/ns87415.c
 */

#समावेश <यंत्र/superपन.स>

#घोषणा SUPERIO_IDE_MAX_RETRIES 25

/**
 *	ns87560_पढ़ो_buggy	-	workaround buggy Super I/O chip
 *	@port: Port to पढ़ो
 *
 *	Work around chipset problems in the 87560 SuperIO chip
 */

अटल u8 ns87560_पढ़ो_buggy(व्योम __iomem *port)
अणु
	u8 पंचांगp;
	पूर्णांक retries = SUPERIO_IDE_MAX_RETRIES;
	करो अणु
		पंचांगp = ioपढ़ो8(port);
		अगर (पंचांगp != 0)
			वापस पंचांगp;
		udelay(50);
	पूर्ण जबतक(retries-- > 0);
	वापस पंचांगp;
पूर्ण

/**
 *	ns87560_check_status
 *	@ap: channel to check
 *
 *	Return the status of the channel working around the
 *	87560 flaws.
 */

अटल u8 ns87560_check_status(काष्ठा ata_port *ap)
अणु
	वापस ns87560_पढ़ो_buggy(ap->ioaddr.status_addr);
पूर्ण

/**
 *	ns87560_tf_पढ़ो - input device's ATA taskfile shaकरोw रेजिस्टरs
 *	@ap: Port from which input is पढ़ो
 *	@tf: ATA taskfile रेजिस्टर set क्रम storing input
 *
 *	Reads ATA taskfile रेजिस्टरs क्रम currently-selected device
 *	पूर्णांकo @tf. Work around the 87560 bugs.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ns87560_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	tf->command = ns87560_check_status(ap);
	tf->feature = ioपढ़ो8(ioaddr->error_addr);
	tf->nsect = ioपढ़ो8(ioaddr->nsect_addr);
	tf->lbal = ioपढ़ो8(ioaddr->lbal_addr);
	tf->lbam = ioपढ़ो8(ioaddr->lbam_addr);
	tf->lbah = ioपढ़ो8(ioaddr->lbah_addr);
	tf->device = ns87560_पढ़ो_buggy(ioaddr->device_addr);

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		ioग_लिखो8(tf->ctl | ATA_HOB, ioaddr->ctl_addr);
		tf->hob_feature = ioपढ़ो8(ioaddr->error_addr);
		tf->hob_nsect = ioपढ़ो8(ioaddr->nsect_addr);
		tf->hob_lbal = ioपढ़ो8(ioaddr->lbal_addr);
		tf->hob_lbam = ioपढ़ो8(ioaddr->lbam_addr);
		tf->hob_lbah = ioपढ़ो8(ioaddr->lbah_addr);
		ioग_लिखो8(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
	पूर्ण
पूर्ण

/**
 *	ns87560_bmdma_status
 *	@ap: channel to check
 *
 *	Return the DMA status of the channel working around the
 *	87560 flaws.
 */

अटल u8 ns87560_bmdma_status(काष्ठा ata_port *ap)
अणु
	वापस ns87560_पढ़ो_buggy(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
पूर्ण
#पूर्ण_अगर		/* 87560 SuperIO Support */

अटल काष्ठा ata_port_operations ns87415_pata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.check_atapi_dma	= ns87415_check_atapi_dma,
	.bmdma_setup		= ns87415_bmdma_setup,
	.bmdma_start		= ns87415_bmdma_start,
	.bmdma_stop		= ns87415_bmdma_stop,
	.sff_irq_clear		= ns87415_irq_clear,

	.cable_detect		= ata_cable_40wire,
	.set_piomode		= ns87415_set_piomode,
पूर्ण;

#अगर defined(CONFIG_SUPERIO)
अटल काष्ठा ata_port_operations ns87560_pata_ops = अणु
	.inherits		= &ns87415_pata_ops,
	.sff_tf_पढ़ो		= ns87560_tf_पढ़ो,
	.sff_check_status	= ns87560_check_status,
	.bmdma_status		= ns87560_bmdma_status,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा ns87415_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल व्योम ns87415_fixup(काष्ठा pci_dev *pdev)
अणु
	/* Select 512 byte sectors */
	pci_ग_लिखो_config_byte(pdev, 0x55, 0xEE);
	/* Select PIO0 8bit घड़ीing */
	pci_ग_लिखो_config_byte(pdev, 0x54, 0xB7);
पूर्ण

/**
 *	ns87415_init_one - Register 87415 ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in ns87415_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.  We probe क्रम combined mode (sigh),
 *	and then hand over control to libata, क्रम it to करो the rest.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक ns87415_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.port_ops	= &ns87415_pata_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	पूर्णांक rc;
#अगर defined(CONFIG_SUPERIO)
	अटल स्थिर काष्ठा ata_port_info info87560 = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.port_ops	= &ns87560_pata_ops,
	पूर्ण;

	अगर (PCI_SLOT(pdev->devfn) == 0x0E)
		ppi[0] = &info87560;
#पूर्ण_अगर
	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	ns87415_fixup(pdev);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &ns87415_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ns87415_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_87415), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ns87415_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	ns87415_fixup(pdev);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pci_driver ns87415_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= ns87415_pci_tbl,
	.probe			= ns87415_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ns87415_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(ns87415_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("ATA low-level driver for NS87415 controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ns87415_pci_tbl);
MODULE_VERSION(DRV_VERSION);
