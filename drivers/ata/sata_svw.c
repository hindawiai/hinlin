<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_svw.c - ServerWorks / Apple K2 SATA
 *
 *  Maपूर्णांकained by: Benjamin Herrenschmidt <benh@kernel.crashing.org> and
 *		   Jeff Garzik <jgarzik@pobox.com>
 *  		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2003 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *
 *  Bits from Jeff Garzik, Copyright RedHat, Inc.
 *
 *  This driver probably works with non-Apple versions of the
 *  Broadcom chipset...
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available under NDA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi.h>
#समावेश <linux/libata.h>
#समावेश <linux/of.h>

#घोषणा DRV_NAME	"sata_svw"
#घोषणा DRV_VERSION	"2.3"

क्रमागत अणु
	/* ap->flags bits */
	K2_FLAG_SATA_8_PORTS		= (1 << 24),
	K2_FLAG_NO_ATAPI_DMA		= (1 << 25),
	K2_FLAG_BAR_POS_3			= (1 << 26),

	/* Taskfile रेजिस्टरs offsets */
	K2_SATA_TF_CMD_OFFSET		= 0x00,
	K2_SATA_TF_DATA_OFFSET		= 0x00,
	K2_SATA_TF_ERROR_OFFSET		= 0x04,
	K2_SATA_TF_NSECT_OFFSET		= 0x08,
	K2_SATA_TF_LBAL_OFFSET		= 0x0c,
	K2_SATA_TF_LBAM_OFFSET		= 0x10,
	K2_SATA_TF_LBAH_OFFSET		= 0x14,
	K2_SATA_TF_DEVICE_OFFSET	= 0x18,
	K2_SATA_TF_CMDSTAT_OFFSET      	= 0x1c,
	K2_SATA_TF_CTL_OFFSET		= 0x20,

	/* DMA base */
	K2_SATA_DMA_CMD_OFFSET		= 0x30,

	/* SCRs base */
	K2_SATA_SCR_STATUS_OFFSET	= 0x40,
	K2_SATA_SCR_ERROR_OFFSET	= 0x44,
	K2_SATA_SCR_CONTROL_OFFSET	= 0x48,

	/* Others */
	K2_SATA_SICR1_OFFSET		= 0x80,
	K2_SATA_SICR2_OFFSET		= 0x84,
	K2_SATA_SIM_OFFSET		= 0x88,

	/* Port stride */
	K2_SATA_PORT_OFFSET		= 0x100,

	chip_svw4			= 0,
	chip_svw8			= 1,
	chip_svw42			= 2,	/* bar 3 */
	chip_svw43			= 3,	/* bar 5 */
पूर्ण;

अटल u8 k2_stat_check_status(काष्ठा ata_port *ap);


अटल पूर्णांक k2_sata_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	u8 cmnd = qc->scsicmd->cmnd[0];

	अगर (qc->ap->flags & K2_FLAG_NO_ATAPI_DMA)
		वापस -1;	/* ATAPI DMA not supported */
	अन्यथा अणु
		चयन (cmnd) अणु
		हाल READ_10:
		हाल READ_12:
		हाल READ_16:
		हाल WRITE_10:
		हाल WRITE_12:
		हाल WRITE_16:
			वापस 0;

		शेष:
			वापस -1;
		पूर्ण

	पूर्ण
पूर्ण

अटल पूर्णांक k2_sata_scr_पढ़ो(काष्ठा ata_link *link,
			    अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	*val = पढ़ोl(link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण


अटल पूर्णांक k2_sata_scr_ग_लिखो(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	ग_लिखोl(val, link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक k2_sata_softreset(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक *class, अचिन्हित दीर्घ deadline)
अणु
	u8 dmactl;
	व्योम __iomem *mmio = link->ap->ioaddr.bmdma_addr;

	dmactl = पढ़ोb(mmio + ATA_DMA_CMD);

	/* Clear the start bit */
	अगर (dmactl & ATA_DMA_START) अणु
		dmactl &= ~ATA_DMA_START;
		ग_लिखोb(dmactl, mmio + ATA_DMA_CMD);
	पूर्ण

	वापस ata_sff_softreset(link, class, deadline);
पूर्ण

अटल पूर्णांक k2_sata_hardreset(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक *class, अचिन्हित दीर्घ deadline)
अणु
	u8 dmactl;
	व्योम __iomem *mmio = link->ap->ioaddr.bmdma_addr;

	dmactl = पढ़ोb(mmio + ATA_DMA_CMD);

	/* Clear the start bit */
	अगर (dmactl & ATA_DMA_START) अणु
		dmactl &= ~ATA_DMA_START;
		ग_लिखोb(dmactl, mmio + ATA_DMA_CMD);
	पूर्ण

	वापस sata_sff_hardreset(link, class, deadline);
पूर्ण

अटल व्योम k2_sata_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;

	अगर (tf->ctl != ap->last_ctl) अणु
		ग_लिखोb(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
	पूर्ण
	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		ग_लिखोw(tf->feature | (((u16)tf->hob_feature) << 8),
		       ioaddr->feature_addr);
		ग_लिखोw(tf->nsect | (((u16)tf->hob_nsect) << 8),
		       ioaddr->nsect_addr);
		ग_लिखोw(tf->lbal | (((u16)tf->hob_lbal) << 8),
		       ioaddr->lbal_addr);
		ग_लिखोw(tf->lbam | (((u16)tf->hob_lbam) << 8),
		       ioaddr->lbam_addr);
		ग_लिखोw(tf->lbah | (((u16)tf->hob_lbah) << 8),
		       ioaddr->lbah_addr);
	पूर्ण अन्यथा अगर (is_addr) अणु
		ग_लिखोw(tf->feature, ioaddr->feature_addr);
		ग_लिखोw(tf->nsect, ioaddr->nsect_addr);
		ग_लिखोw(tf->lbal, ioaddr->lbal_addr);
		ग_लिखोw(tf->lbam, ioaddr->lbam_addr);
		ग_लिखोw(tf->lbah, ioaddr->lbah_addr);
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE)
		ग_लिखोb(tf->device, ioaddr->device_addr);

	ata_रुको_idle(ap);
पूर्ण


अटल व्योम k2_sata_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	u16 nsect, lbal, lbam, lbah, feature;

	tf->command = k2_stat_check_status(ap);
	tf->device = पढ़ोw(ioaddr->device_addr);
	feature = पढ़ोw(ioaddr->error_addr);
	nsect = पढ़ोw(ioaddr->nsect_addr);
	lbal = पढ़ोw(ioaddr->lbal_addr);
	lbam = पढ़ोw(ioaddr->lbam_addr);
	lbah = पढ़ोw(ioaddr->lbah_addr);

	tf->feature = feature;
	tf->nsect = nsect;
	tf->lbal = lbal;
	tf->lbam = lbam;
	tf->lbah = lbah;

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		tf->hob_feature = feature >> 8;
		tf->hob_nsect = nsect >> 8;
		tf->hob_lbal = lbal >> 8;
		tf->hob_lbam = lbam >> 8;
		tf->hob_lbah = lbah >> 8;
	पूर्ण
पूर्ण

/**
 *	k2_bmdma_setup_mmio - Set up PCI IDE BMDMA transaction (MMIO)
 *	@qc: Info associated with this ATA transaction.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */

अटल व्योम k2_bmdma_setup_mmio(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	u8 dmactl;
	व्योम __iomem *mmio = ap->ioaddr.bmdma_addr;

	/* load PRD table addr. */
	mb();	/* make sure PRD table ग_लिखोs are visible to controller */
	ग_लिखोl(ap->bmdma_prd_dma, mmio + ATA_DMA_TABLE_OFS);

	/* specअगरy data direction, triple-check start bit is clear */
	dmactl = पढ़ोb(mmio + ATA_DMA_CMD);
	dmactl &= ~(ATA_DMA_WR | ATA_DMA_START);
	अगर (!rw)
		dmactl |= ATA_DMA_WR;
	ग_लिखोb(dmactl, mmio + ATA_DMA_CMD);

	/* issue r/w command अगर this is not a ATA DMA command*/
	अगर (qc->tf.protocol != ATA_PROT_DMA)
		ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

/**
 *	k2_bmdma_start_mmio - Start a PCI IDE BMDMA transaction (MMIO)
 *	@qc: Info associated with this ATA transaction.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */

अटल व्योम k2_bmdma_start_mmio(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *mmio = ap->ioaddr.bmdma_addr;
	u8 dmactl;

	/* start host DMA transaction */
	dmactl = पढ़ोb(mmio + ATA_DMA_CMD);
	ग_लिखोb(dmactl | ATA_DMA_START, mmio + ATA_DMA_CMD);
	/* This works around possible data corruption.

	   On certain SATA controllers that can be seen when the r/w
	   command is given to the controller beक्रमe the host DMA is
	   started.

	   On a Read command, the controller would initiate the
	   command to the drive even beक्रमe it sees the DMA
	   start. When there are very fast drives connected to the
	   controller, or when the data request hits in the drive
	   cache, there is the possibility that the drive वापसs a
	   part or all of the requested data to the controller beक्रमe
	   the DMA start is issued.  In this हाल, the controller
	   would become confused as to what to करो with the data.  In
	   the worst हाल when all the data is वापसed back to the
	   controller, the controller could hang. In other हालs it
	   could वापस partial data वापसing in data
	   corruption. This problem has been seen in PPC प्रणालीs and
	   can also appear on an प्रणाली with very fast disks, where
	   the SATA controller is sitting behind a number of bridges,
	   and hence there is signअगरicant latency between the r/w
	   command and the start command. */
	/* issue r/w command अगर the access is to ATA */
	अगर (qc->tf.protocol == ATA_PROT_DMA)
		ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण


अटल u8 k2_stat_check_status(काष्ठा ata_port *ap)
अणु
	वापस पढ़ोl(ap->ioaddr.status_addr);
पूर्ण

अटल पूर्णांक k2_sata_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ata_port *ap;
	काष्ठा device_node *np;
	पूर्णांक index;

	/* Find  the ata_port */
	ap = ata_shost_to_port(shost);
	अगर (ap == शून्य)
		वापस 0;

	/* Find the OF node क्रम the PCI device proper */
	np = pci_device_to_OF_node(to_pci_dev(ap->host->dev));
	अगर (np == शून्य)
		वापस 0;

	/* Match it to a port node */
	index = (ap == ap->host->ports[0]) ? 0 : 1;
	क्रम (np = np->child; np != शून्य; np = np->sibling) अणु
		स्थिर u32 *reg = of_get_property(np, "reg", शून्य);
		अगर (!reg)
			जारी;
		अगर (index == *reg) अणु
			seq_म_लिखो(m, "devspec: %pOF\n", np);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा k2_sata_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.show_info		= k2_sata_show_info,
पूर्ण;


अटल काष्ठा ata_port_operations k2_sata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.softreset              = k2_sata_softreset,
	.hardreset              = k2_sata_hardreset,
	.sff_tf_load		= k2_sata_tf_load,
	.sff_tf_पढ़ो		= k2_sata_tf_पढ़ो,
	.sff_check_status	= k2_stat_check_status,
	.check_atapi_dma	= k2_sata_check_atapi_dma,
	.bmdma_setup		= k2_bmdma_setup_mmio,
	.bmdma_start		= k2_bmdma_start_mmio,
	.scr_पढ़ो		= k2_sata_scr_पढ़ो,
	.scr_ग_लिखो		= k2_sata_scr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info k2_port_info[] = अणु
	/* chip_svw4 */
	अणु
		.flags		= ATA_FLAG_SATA | K2_FLAG_NO_ATAPI_DMA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &k2_sata_ops,
	पूर्ण,
	/* chip_svw8 */
	अणु
		.flags		= ATA_FLAG_SATA | K2_FLAG_NO_ATAPI_DMA |
				  K2_FLAG_SATA_8_PORTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &k2_sata_ops,
	पूर्ण,
	/* chip_svw42 */
	अणु
		.flags		= ATA_FLAG_SATA | K2_FLAG_BAR_POS_3,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &k2_sata_ops,
	पूर्ण,
	/* chip_svw43 */
	अणु
		.flags		= ATA_FLAG_SATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &k2_sata_ops,
	पूर्ण,
पूर्ण;

अटल व्योम k2_sata_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		= base + K2_SATA_TF_CMD_OFFSET;
	port->data_addr		= base + K2_SATA_TF_DATA_OFFSET;
	port->feature_addr	=
	port->error_addr	= base + K2_SATA_TF_ERROR_OFFSET;
	port->nsect_addr	= base + K2_SATA_TF_NSECT_OFFSET;
	port->lbal_addr		= base + K2_SATA_TF_LBAL_OFFSET;
	port->lbam_addr		= base + K2_SATA_TF_LBAM_OFFSET;
	port->lbah_addr		= base + K2_SATA_TF_LBAH_OFFSET;
	port->device_addr	= base + K2_SATA_TF_DEVICE_OFFSET;
	port->command_addr	=
	port->status_addr	= base + K2_SATA_TF_CMDSTAT_OFFSET;
	port->altstatus_addr	=
	port->ctl_addr		= base + K2_SATA_TF_CTL_OFFSET;
	port->bmdma_addr	= base + K2_SATA_DMA_CMD_OFFSET;
	port->scr_addr		= base + K2_SATA_SCR_STATUS_OFFSET;
पूर्ण


अटल पूर्णांक k2_sata_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] =
		अणु &k2_port_info[ent->driver_data], शून्य पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *mmio_base;
	पूर्णांक n_ports, i, rc, bar_pos;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* allocate host */
	n_ports = 4;
	अगर (ppi[0]->flags & K2_FLAG_SATA_8_PORTS)
		n_ports = 8;

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	अगर (!host)
		वापस -ENOMEM;

	bar_pos = 5;
	अगर (ppi[0]->flags & K2_FLAG_BAR_POS_3)
		bar_pos = 3;
	/*
	 * If this driver happens to only be useful on Apple's K2, then
	 * we should check that here as it has a normal Serverworks ID
	 */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/*
	 * Check अगर we have resources mapped at all (second function may
	 * have been disabled by firmware)
	 */
	अगर (pci_resource_len(pdev, bar_pos) == 0) अणु
		/* In IDE mode we need to pin the device to ensure that
			pcim_release करोes not clear the busmaster bit in config
			space, clearing causes busmaster DMA to fail on
			ports 3 & 4 */
		pcim_pin_device(pdev);
		वापस -ENODEV;
	पूर्ण

	/* Request and iomap PCI regions */
	rc = pcim_iomap_regions(pdev, 1 << bar_pos, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);
	mmio_base = host->iomap[bar_pos];

	/* dअगरferent controllers have dअगरferent number of ports - currently 4 or 8 */
	/* All ports are on the same function. Multi-function device is no
	 * दीर्घer available. This should not be seen in any प्रणाली. */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		अचिन्हित पूर्णांक offset = i * K2_SATA_PORT_OFFSET;

		k2_sata_setup_port(&ap->ioaddr, mmio_base + offset);

		ata_port_pbar_desc(ap, 5, -1, "mmio");
		ata_port_pbar_desc(ap, 5, offset, "port");
	पूर्ण

	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;

	/* Clear a magic bit in SCR1 according to Darwin, those help
	 * some funky seagate drives (though so far, those were alपढ़ोy
	 * set by the firmware on the machines I had access to)
	 */
	ग_लिखोl(पढ़ोl(mmio_base + K2_SATA_SICR1_OFFSET) & ~0x00040000,
	       mmio_base + K2_SATA_SICR1_OFFSET);

	/* Clear SATA error & पूर्णांकerrupts we करोn't use */
	ग_लिखोl(0xffffffff, mmio_base + K2_SATA_SCR_ERROR_OFFSET);
	ग_लिखोl(0x0, mmio_base + K2_SATA_SIM_OFFSET);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &k2_sata_sht);
पूर्ण

/* 0x240 is device ID क्रम Apple K2 device
 * 0x241 is device ID क्रम Serverworks Froकरो4
 * 0x242 is device ID क्रम Serverworks Froकरो8
 * 0x24a is device ID क्रम BCM5785 (aka HT1000) HT southbridge पूर्णांकegrated SATA
 * controller
 * */
अटल स्थिर काष्ठा pci_device_id k2_sata_pci_tbl[] = अणु
	अणु PCI_VDEVICE(SERVERWORKS, 0x0240), chip_svw4 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, 0x0241), chip_svw8 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, 0x0242), chip_svw4 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, 0x024a), chip_svw4 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, 0x024b), chip_svw4 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, 0x0410), chip_svw42 पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, 0x0411), chip_svw43 पूर्ण,

	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver k2_sata_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= k2_sata_pci_tbl,
	.probe			= k2_sata_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

module_pci_driver(k2_sata_pci_driver);

MODULE_AUTHOR("Benjamin Herrenschmidt");
MODULE_DESCRIPTION("low-level driver for K2 SATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, k2_sata_pci_tbl);
MODULE_VERSION(DRV_VERSION);
