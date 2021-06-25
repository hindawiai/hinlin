<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_vsc.c - Vitesse VSC7174 4 port DPA SATA
 *
 *  Maपूर्णांकained by:  Jeremy Higकरोn @ SGI
 * 		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2004 SGI
 *
 *  Bits from Jeff Garzik, Copyright RedHat, Inc.
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Vitesse hardware करोcumentation presumably available under NDA.
 *  Intel 31244 (same hardware पूर्णांकerface) करोcumentation presumably
 *  available from http://developer.पूर्णांकel.com/
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"sata_vsc"
#घोषणा DRV_VERSION	"2.3"

क्रमागत अणु
	VSC_MMIO_BAR			= 0,

	/* Interrupt रेजिस्टर offsets (from chip base address) */
	VSC_SATA_INT_STAT_OFFSET	= 0x00,
	VSC_SATA_INT_MASK_OFFSET	= 0x04,

	/* Taskfile रेजिस्टरs offsets */
	VSC_SATA_TF_CMD_OFFSET		= 0x00,
	VSC_SATA_TF_DATA_OFFSET		= 0x00,
	VSC_SATA_TF_ERROR_OFFSET	= 0x04,
	VSC_SATA_TF_FEATURE_OFFSET	= 0x06,
	VSC_SATA_TF_NSECT_OFFSET	= 0x08,
	VSC_SATA_TF_LBAL_OFFSET		= 0x0c,
	VSC_SATA_TF_LBAM_OFFSET		= 0x10,
	VSC_SATA_TF_LBAH_OFFSET		= 0x14,
	VSC_SATA_TF_DEVICE_OFFSET	= 0x18,
	VSC_SATA_TF_STATUS_OFFSET	= 0x1c,
	VSC_SATA_TF_COMMAND_OFFSET	= 0x1d,
	VSC_SATA_TF_ALTSTATUS_OFFSET	= 0x28,
	VSC_SATA_TF_CTL_OFFSET		= 0x29,

	/* DMA base */
	VSC_SATA_UP_DESCRIPTOR_OFFSET	= 0x64,
	VSC_SATA_UP_DATA_BUFFER_OFFSET	= 0x6C,
	VSC_SATA_DMA_CMD_OFFSET		= 0x70,

	/* SCRs base */
	VSC_SATA_SCR_STATUS_OFFSET	= 0x100,
	VSC_SATA_SCR_ERROR_OFFSET	= 0x104,
	VSC_SATA_SCR_CONTROL_OFFSET	= 0x108,

	/* Port stride */
	VSC_SATA_PORT_OFFSET		= 0x200,

	/* Error पूर्णांकerrupt status bit offsets */
	VSC_SATA_INT_ERROR_CRC		= 0x40,
	VSC_SATA_INT_ERROR_T		= 0x20,
	VSC_SATA_INT_ERROR_P		= 0x10,
	VSC_SATA_INT_ERROR_R		= 0x8,
	VSC_SATA_INT_ERROR_E		= 0x4,
	VSC_SATA_INT_ERROR_M		= 0x2,
	VSC_SATA_INT_PHY_CHANGE		= 0x1,
	VSC_SATA_INT_ERROR = (VSC_SATA_INT_ERROR_CRC  | VSC_SATA_INT_ERROR_T | \
			      VSC_SATA_INT_ERROR_P    | VSC_SATA_INT_ERROR_R | \
			      VSC_SATA_INT_ERROR_E    | VSC_SATA_INT_ERROR_M | \
			      VSC_SATA_INT_PHY_CHANGE),
पूर्ण;

अटल पूर्णांक vsc_sata_scr_पढ़ो(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	*val = पढ़ोl(link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण


अटल पूर्णांक vsc_sata_scr_ग_लिखो(काष्ठा ata_link *link,
			      अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	ग_लिखोl(val, link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण


अटल व्योम vsc_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mask_addr;

	mask_addr = ap->host->iomap[VSC_MMIO_BAR] +
		VSC_SATA_INT_MASK_OFFSET + ap->port_no;

	ग_लिखोb(0, mask_addr);
पूर्ण


अटल व्योम vsc_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mask_addr;

	mask_addr = ap->host->iomap[VSC_MMIO_BAR] +
		VSC_SATA_INT_MASK_OFFSET + ap->port_no;

	ग_लिखोb(0xff, mask_addr);
पूर्ण


अटल व्योम vsc_पूर्णांकr_mask_update(काष्ठा ata_port *ap, u8 ctl)
अणु
	व्योम __iomem *mask_addr;
	u8 mask;

	mask_addr = ap->host->iomap[VSC_MMIO_BAR] +
		VSC_SATA_INT_MASK_OFFSET + ap->port_no;
	mask = पढ़ोb(mask_addr);
	अगर (ctl & ATA_NIEN)
		mask |= 0x80;
	अन्यथा
		mask &= 0x7F;
	ग_लिखोb(mask, mask_addr);
पूर्ण


अटल व्योम vsc_sata_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;

	/*
	 * The only thing the ctl रेजिस्टर is used क्रम is SRST.
	 * That is not enabled or disabled via tf_load.
	 * However, अगर ATA_NIEN is changed, then we need to change
	 * the पूर्णांकerrupt रेजिस्टर.
	 */
	अगर ((tf->ctl & ATA_NIEN) != (ap->last_ctl & ATA_NIEN)) अणु
		ap->last_ctl = tf->ctl;
		vsc_पूर्णांकr_mask_update(ap, tf->ctl & ATA_NIEN);
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


अटल व्योम vsc_sata_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	u16 nsect, lbal, lbam, lbah, feature;

	tf->command = ata_sff_check_status(ap);
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

अटल अंतरभूत व्योम vsc_error_पूर्णांकr(u8 port_status, काष्ठा ata_port *ap)
अणु
	अगर (port_status & (VSC_SATA_INT_PHY_CHANGE | VSC_SATA_INT_ERROR_M))
		ata_port_मुक्तze(ap);
	अन्यथा
		ata_port_पात(ap);
पूर्ण

अटल व्योम vsc_port_पूर्णांकr(u8 port_status, काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	पूर्णांक handled = 0;

	अगर (unlikely(port_status & VSC_SATA_INT_ERROR)) अणु
		vsc_error_पूर्णांकr(port_status, ap);
		वापस;
	पूर्ण

	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	अगर (qc && likely(!(qc->tf.flags & ATA_TFLAG_POLLING)))
		handled = ata_bmdma_port_पूर्णांकr(ap, qc);

	/* We received an पूर्णांकerrupt during a polled command,
	 * or some other spurious condition.  Interrupt reporting
	 * with this hardware is fairly reliable so it is safe to
	 * simply clear the पूर्णांकerrupt
	 */
	अगर (unlikely(!handled))
		ap->ops->sff_check_status(ap);
पूर्ण

/*
 * vsc_sata_पूर्णांकerrupt
 *
 * Read the पूर्णांकerrupt रेजिस्टर and process क्रम the devices that have
 * them pending.
 */
अटल irqवापस_t vsc_sata_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक handled = 0;
	u32 status;

	status = पढ़ोl(host->iomap[VSC_MMIO_BAR] + VSC_SATA_INT_STAT_OFFSET);

	अगर (unlikely(status == 0xffffffff || status == 0)) अणु
		अगर (status)
			dev_err(host->dev,
				": IRQ status == 0xffffffff, PCI fault or device removal?\n");
		जाओ out;
	पूर्ण

	spin_lock(&host->lock);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		u8 port_status = (status >> (8 * i)) & 0xff;
		अगर (port_status) अणु
			vsc_port_पूर्णांकr(port_status, host->ports[i]);
			handled++;
		पूर्ण
	पूर्ण

	spin_unlock(&host->lock);
out:
	वापस IRQ_RETVAL(handled);
पूर्ण


अटल काष्ठा scsi_host_ढाँचा vsc_sata_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;


अटल काष्ठा ata_port_operations vsc_sata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	/* The IRQ handling is not quite standard SFF behaviour so we
	   cannot use the शेष lost पूर्णांकerrupt handler */
	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,
	.sff_tf_load		= vsc_sata_tf_load,
	.sff_tf_पढ़ो		= vsc_sata_tf_पढ़ो,
	.मुक्तze			= vsc_मुक्तze,
	.thaw			= vsc_thaw,
	.scr_पढ़ो		= vsc_sata_scr_पढ़ो,
	.scr_ग_लिखो		= vsc_sata_scr_ग_लिखो,
पूर्ण;

अटल व्योम vsc_sata_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		= base + VSC_SATA_TF_CMD_OFFSET;
	port->data_addr		= base + VSC_SATA_TF_DATA_OFFSET;
	port->error_addr	= base + VSC_SATA_TF_ERROR_OFFSET;
	port->feature_addr	= base + VSC_SATA_TF_FEATURE_OFFSET;
	port->nsect_addr	= base + VSC_SATA_TF_NSECT_OFFSET;
	port->lbal_addr		= base + VSC_SATA_TF_LBAL_OFFSET;
	port->lbam_addr		= base + VSC_SATA_TF_LBAM_OFFSET;
	port->lbah_addr		= base + VSC_SATA_TF_LBAH_OFFSET;
	port->device_addr	= base + VSC_SATA_TF_DEVICE_OFFSET;
	port->status_addr	= base + VSC_SATA_TF_STATUS_OFFSET;
	port->command_addr	= base + VSC_SATA_TF_COMMAND_OFFSET;
	port->altstatus_addr	= base + VSC_SATA_TF_ALTSTATUS_OFFSET;
	port->ctl_addr		= base + VSC_SATA_TF_CTL_OFFSET;
	port->bmdma_addr	= base + VSC_SATA_DMA_CMD_OFFSET;
	port->scr_addr		= base + VSC_SATA_SCR_STATUS_OFFSET;
	ग_लिखोl(0, base + VSC_SATA_UP_DESCRIPTOR_OFFSET);
	ग_लिखोl(0, base + VSC_SATA_UP_DATA_BUFFER_OFFSET);
पूर्ण


अटल पूर्णांक vsc_sata_init_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info pi = अणु
		.flags		= ATA_FLAG_SATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &vsc_sata_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *mmio_base;
	पूर्णांक i, rc;
	u8 cls;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* allocate host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 4);
	अगर (!host)
		वापस -ENOMEM;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* check अगर we have needed resource mapped */
	अगर (pci_resource_len(pdev, 0) == 0)
		वापस -ENODEV;

	/* map IO regions and initialize host accordingly */
	rc = pcim_iomap_regions(pdev, 1 << VSC_MMIO_BAR, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);

	mmio_base = host->iomap[VSC_MMIO_BAR];

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		अचिन्हित पूर्णांक offset = (i + 1) * VSC_SATA_PORT_OFFSET;

		vsc_sata_setup_port(&ap->ioaddr, mmio_base + offset);

		ata_port_pbar_desc(ap, VSC_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, VSC_MMIO_BAR, offset, "port");
	पूर्ण

	/*
	 * Use 32 bit DMA mask, because 64 bit address support is poor.
	 */
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	/*
	 * Due to a bug in the chip, the शेष cache line size can't be
	 * used (unless the शेष is non-zero).
	 */
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE, &cls);
	अगर (cls == 0x00)
		pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE, 0x80);

	अगर (pci_enable_msi(pdev) == 0)
		pci_पूर्णांकx(pdev, 0);

	/*
	 * Config offset 0x98 is "Extended Control and Status Register 0"
	 * Default value is (1 << 28).  All bits except bit 28 are reserved in
	 * DPA mode.  If bit 28 is set, LED 0 reflects all ports' activity.
	 * If bit 28 is clear, each port has its own LED.
	 */
	pci_ग_लिखो_config_dword(pdev, 0x98, 0);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, vsc_sata_पूर्णांकerrupt,
				 IRQF_SHARED, &vsc_sata_sht);
पूर्ण

अटल स्थिर काष्ठा pci_device_id vsc_sata_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_VITESSE, 0x7174,
	  PCI_ANY_ID, PCI_ANY_ID, 0x10600, 0xFFFFFF, 0 पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x3200,
	  PCI_ANY_ID, PCI_ANY_ID, 0x10600, 0xFFFFFF, 0 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver vsc_sata_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= vsc_sata_pci_tbl,
	.probe			= vsc_sata_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

module_pci_driver(vsc_sata_pci_driver);

MODULE_AUTHOR("Jeremy Higdon");
MODULE_DESCRIPTION("low-level driver for Vitesse VSC7174 SATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, vsc_sata_pci_tbl);
MODULE_VERSION(DRV_VERSION);
