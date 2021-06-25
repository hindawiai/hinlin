<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_via.c - VIA Serial ATA controllers
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 * 		   Please ALWAYS copy linux-ide@vger.kernel.org
 *		   on emails.
 *
 *  Copyright 2003-2004 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2004 Jeff Garzik
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
#समावेश <linux/device.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"sata_via"
#घोषणा DRV_VERSION	"2.6"

/*
 * vt8251 is dअगरferent from other sata controllers of VIA.  It has two
 * channels, each channel has both Master and Slave slot.
 */
क्रमागत board_ids_क्रमागत अणु
	vt6420,
	vt6421,
	vt8251,
पूर्ण;

क्रमागत अणु
	SATA_CHAN_ENAB		= 0x40, /* SATA channel enable */
	SATA_INT_GATE		= 0x41, /* SATA पूर्णांकerrupt gating */
	SATA_NATIVE_MODE	= 0x42, /* Native mode enable */
	SVIA_MISC_3		= 0x46,	/* Miscellaneous Control III */
	PATA_UDMA_TIMING	= 0xB3, /* PATA timing क्रम DMA/ cable detect */
	PATA_PIO_TIMING		= 0xAB, /* PATA timing रेजिस्टर */

	PORT0			= (1 << 1),
	PORT1			= (1 << 0),
	ALL_PORTS		= PORT0 | PORT1,

	NATIVE_MODE_ALL		= (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4),

	SATA_EXT_PHY		= (1 << 6), /* 0==use PATA, 1==ext phy */

	SATA_HOTPLUG		= (1 << 5), /* enable IRQ on hotplug */
पूर्ण;

काष्ठा svia_priv अणु
	bool			wd_workaround;
पूर्ण;

अटल पूर्णांक vt6420_hotplug;
module_param_named(vt6420_hotplug, vt6420_hotplug, पूर्णांक, 0644);
MODULE_PARM_DESC(vt6420_hotplug, "Enable hot-plug support for VT6420 (0=Don't support, 1=support)");

अटल पूर्णांक svia_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक svia_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
अटल पूर्णांक svia_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक svia_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);
अटल पूर्णांक vt8251_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 *val);
अटल पूर्णांक vt8251_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 val);
अटल व्योम svia_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
अटल व्योम svia_noop_मुक्तze(काष्ठा ata_port *ap);
अटल पूर्णांक vt6420_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
अटल व्योम vt6420_bmdma_start(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक vt6421_pata_cable_detect(काष्ठा ata_port *ap);
अटल व्योम vt6421_set_pio_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev);
अटल व्योम vt6421_set_dma_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev);
अटल व्योम vt6421_error_handler(काष्ठा ata_port *ap);

अटल स्थिर काष्ठा pci_device_id svia_pci_tbl[] = अणु
	अणु PCI_VDEVICE(VIA, 0x5337), vt6420 पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x0591), vt6420 पूर्ण, /* 2 sata chnls (Master) */
	अणु PCI_VDEVICE(VIA, 0x3149), vt6420 पूर्ण, /* 2 sata chnls (Master) */
	अणु PCI_VDEVICE(VIA, 0x3249), vt6421 पूर्ण, /* 2 sata chnls, 1 pata chnl */
	अणु PCI_VDEVICE(VIA, 0x5372), vt6420 पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x7372), vt6420 पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x5287), vt8251 पूर्ण, /* 2 sata chnls (Master/Slave) */
	अणु PCI_VDEVICE(VIA, 0x9000), vt8251 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver svia_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= svia_pci_tbl,
	.probe			= svia_init_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= svia_pci_device_resume,
#पूर्ण_अगर
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा svia_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations svia_base_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.sff_tf_load		= svia_tf_load,
पूर्ण;

अटल काष्ठा ata_port_operations vt6420_sata_ops = अणु
	.inherits		= &svia_base_ops,
	.मुक्तze			= svia_noop_मुक्तze,
	.prereset		= vt6420_prereset,
	.bmdma_start		= vt6420_bmdma_start,
पूर्ण;

अटल काष्ठा ata_port_operations vt6421_pata_ops = अणु
	.inherits		= &svia_base_ops,
	.cable_detect		= vt6421_pata_cable_detect,
	.set_piomode		= vt6421_set_pio_mode,
	.set_dmamode		= vt6421_set_dma_mode,
पूर्ण;

अटल काष्ठा ata_port_operations vt6421_sata_ops = अणु
	.inherits		= &svia_base_ops,
	.scr_पढ़ो		= svia_scr_पढ़ो,
	.scr_ग_लिखो		= svia_scr_ग_लिखो,
	.error_handler		= vt6421_error_handler,
पूर्ण;

अटल काष्ठा ata_port_operations vt8251_ops = अणु
	.inherits		= &svia_base_ops,
	.hardreset		= sata_std_hardreset,
	.scr_पढ़ो		= vt8251_scr_पढ़ो,
	.scr_ग_लिखो		= vt8251_scr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info vt6420_port_info = अणु
	.flags		= ATA_FLAG_SATA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &vt6420_sata_ops,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info vt6421_sport_info = अणु
	.flags		= ATA_FLAG_SATA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &vt6421_sata_ops,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info vt6421_pport_info = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &vt6421_pata_ops,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info vt8251_port_info = अणु
	.flags		= ATA_FLAG_SATA | ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &vt8251_ops,
पूर्ण;

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("SCSI low-level driver for VIA SATA controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, svia_pci_tbl);
MODULE_VERSION(DRV_VERSION);

अटल पूर्णांक svia_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	*val = ioपढ़ो32(link->ap->ioaddr.scr_addr + (4 * sc_reg));
	वापस 0;
पूर्ण

अटल पूर्णांक svia_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	ioग_लिखो32(val, link->ap->ioaddr.scr_addr + (4 * sc_reg));
	वापस 0;
पूर्ण

अटल पूर्णांक vt8251_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 *val)
अणु
	अटल स्थिर u8 ipm_tbl[] = अणु 1, 2, 6, 0 पूर्ण;
	काष्ठा pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	पूर्णांक slot = 2 * link->ap->port_no + link->pmp;
	u32 v = 0;
	u8 raw;

	चयन (scr) अणु
	हाल SCR_STATUS:
		pci_पढ़ो_config_byte(pdev, 0xA0 + slot, &raw);

		/* पढ़ो the DET field, bit0 and 1 of the config byte */
		v |= raw & 0x03;

		/* पढ़ो the SPD field, bit4 of the configure byte */
		अगर (raw & (1 << 4))
			v |= 0x02 << 4;
		अन्यथा
			v |= 0x01 << 4;

		/* पढ़ो the IPM field, bit2 and 3 of the config byte */
		v |= ipm_tbl[(raw >> 2) & 0x3];
		अवरोध;

	हाल SCR_ERROR:
		/* devices other than 5287 uses 0xA8 as base */
		WARN_ON(pdev->device != 0x5287);
		pci_पढ़ो_config_dword(pdev, 0xB0 + slot * 4, &v);
		अवरोध;

	हाल SCR_CONTROL:
		pci_पढ़ो_config_byte(pdev, 0xA4 + slot, &raw);

		/* पढ़ो the DET field, bit0 and bit1 */
		v |= ((raw & 0x02) << 1) | (raw & 0x01);

		/* पढ़ो the IPM field, bit2 and bit3 */
		v |= ((raw >> 2) & 0x03) << 8;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*val = v;
	वापस 0;
पूर्ण

अटल पूर्णांक vt8251_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 val)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	पूर्णांक slot = 2 * link->ap->port_no + link->pmp;
	u32 v = 0;

	चयन (scr) अणु
	हाल SCR_ERROR:
		/* devices other than 5287 uses 0xA8 as base */
		WARN_ON(pdev->device != 0x5287);
		pci_ग_लिखो_config_dword(pdev, 0xB0 + slot * 4, val);
		वापस 0;

	हाल SCR_CONTROL:
		/* set the DET field */
		v |= ((val & 0x4) >> 1) | (val & 0x1);

		/* set the IPM field */
		v |= ((val >> 8) & 0x3) << 2;

		pci_ग_लिखो_config_byte(pdev, 0xA4 + slot, v);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 *	svia_tf_load - send taskfile रेजिस्टरs to host controller
 *	@ap: Port to which output is sent
 *	@tf: ATA taskfile रेजिस्टर set
 *
 *	Outमाला_दो ATA taskfile to standard ATA host controller.
 *
 *	This is to fix the पूर्णांकernal bug of via chipsets, which will
 *	reset the device रेजिस्टर after changing the IEN bit on ctl
 *	रेजिस्टर.
 */
अटल व्योम svia_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_taskfile ttf;

	अगर (tf->ctl != ap->last_ctl)  अणु
		ttf = *tf;
		ttf.flags |= ATA_TFLAG_DEVICE;
		tf = &ttf;
	पूर्ण
	ata_sff_tf_load(ap, tf);
पूर्ण

अटल व्योम svia_noop_मुक्तze(काष्ठा ata_port *ap)
अणु
	/* Some VIA controllers choke अगर ATA_NIEN is manipulated in
	 * certain way.  Leave it alone and just clear pending IRQ.
	 */
	ap->ops->sff_check_status(ap);
	ata_bmdma_irq_clear(ap);
पूर्ण

/**
 *	vt6420_prereset - prereset क्रम vt6420
 *	@link: target ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	SCR रेजिस्टरs on vt6420 are pieces of shit and may hang the
 *	whole machine completely अगर accessed with the wrong timing.
 *	To aव्योम such catastrophe, vt6420 करोesn't provide generic SCR
 *	access operations, but uses SStatus and SControl only during
 *	boot probing in controlled way.
 *
 *	As the old (pre EH update) probing code is proven to work, we
 *	strictly follow the access pattern.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक vt6420_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &ap->link.eh_context;
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * 5);
	u32 sstatus, scontrol;
	पूर्णांक online;

	/* करोn't do any SCR stuff if we're not loading */
	अगर (!(ap->pflags & ATA_PFLAG_LOADING))
		जाओ skip_scr;

	/* Resume phy.  This is the old SATA resume sequence */
	svia_scr_ग_लिखो(link, SCR_CONTROL, 0x300);
	svia_scr_पढ़ो(link, SCR_CONTROL, &scontrol); /* flush */

	/* रुको क्रम phy to become पढ़ोy, अगर necessary */
	करो अणु
		ata_msleep(link->ap, 200);
		svia_scr_पढ़ो(link, SCR_STATUS, &sstatus);
		अगर ((sstatus & 0xf) != 1)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	/* खोलो code sata_prपूर्णांक_link_status() */
	svia_scr_पढ़ो(link, SCR_STATUS, &sstatus);
	svia_scr_पढ़ो(link, SCR_CONTROL, &scontrol);

	online = (sstatus & 0xf) == 0x3;

	ata_port_info(ap,
		      "SATA link %s 1.5 Gbps (SStatus %X SControl %X)\n",
		      online ? "up" : "down", sstatus, scontrol);

	/* SStatus is पढ़ो one more समय */
	svia_scr_पढ़ो(link, SCR_STATUS, &sstatus);

	अगर (!online) अणु
		/* tell EH to bail */
		ehc->i.action &= ~ATA_EH_RESET;
		वापस 0;
	पूर्ण

 skip_scr:
	/* रुको क्रम !BSY */
	ata_sff_रुको_पढ़ोy(link, deadline);

	वापस 0;
पूर्ण

अटल व्योम vt6420_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अगर ((qc->tf.command == ATA_CMD_PACKET) &&
	    (qc->scsicmd->sc_data_direction == DMA_TO_DEVICE)) अणु
		/* Prevents corruption on some ATAPI burners */
		ata_sff_छोड़ो(ap);
	पूर्ण
	ata_bmdma_start(qc);
पूर्ण

अटल पूर्णांक vt6421_pata_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 पंचांगp;

	pci_पढ़ो_config_byte(pdev, PATA_UDMA_TIMING, &पंचांगp);
	अगर (पंचांगp & 0x10)
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

अटल व्योम vt6421_set_pio_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर u8 pio_bits[] = अणु 0xA8, 0x65, 0x65, 0x31, 0x20 पूर्ण;
	pci_ग_लिखो_config_byte(pdev, PATA_PIO_TIMING - adev->devno,
			      pio_bits[adev->pio_mode - XFER_PIO_0]);
पूर्ण

अटल व्योम vt6421_set_dma_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर u8 udma_bits[] = अणु 0xEE, 0xE8, 0xE6, 0xE4, 0xE2, 0xE1, 0xE0, 0xE0 पूर्ण;
	pci_ग_लिखो_config_byte(pdev, PATA_UDMA_TIMING - adev->devno,
			      udma_bits[adev->dma_mode - XFER_UDMA_0]);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक svia_bar_sizes[] = अणु
	8, 4, 8, 4, 16, 256
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक vt6421_bar_sizes[] = अणु
	16, 16, 16, 16, 32, 128
पूर्ण;

अटल व्योम __iomem *svia_scr_addr(व्योम __iomem *addr, अचिन्हित पूर्णांक port)
अणु
	वापस addr + (port * 128);
पूर्ण

अटल व्योम __iomem *vt6421_scr_addr(व्योम __iomem *addr, अचिन्हित पूर्णांक port)
अणु
	वापस addr + (port * 64);
पूर्ण

अटल व्योम vt6421_init_addrs(काष्ठा ata_port *ap)
अणु
	व्योम __iomem * स्थिर * iomap = ap->host->iomap;
	व्योम __iomem *reg_addr = iomap[ap->port_no];
	व्योम __iomem *bmdma_addr = iomap[4] + (ap->port_no * 8);
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	ioaddr->cmd_addr = reg_addr;
	ioaddr->altstatus_addr =
	ioaddr->ctl_addr = (व्योम __iomem *)
		((अचिन्हित दीर्घ)(reg_addr + 8) | ATA_PCI_CTL_OFS);
	ioaddr->bmdma_addr = bmdma_addr;
	ioaddr->scr_addr = vt6421_scr_addr(iomap[5], ap->port_no);

	ata_sff_std_ports(ioaddr);

	ata_port_pbar_desc(ap, ap->port_no, -1, "port");
	ata_port_pbar_desc(ap, 4, ap->port_no * 8, "bmdma");
पूर्ण

अटल पूर्णांक vt6420_prepare_host(काष्ठा pci_dev *pdev, काष्ठा ata_host **r_host)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &vt6420_port_info, शून्य पूर्ण;
	काष्ठा ata_host *host;
	पूर्णांक rc;

	अगर (vt6420_hotplug) अणु
		ppi[0]->port_ops->scr_पढ़ो = svia_scr_पढ़ो;
		ppi[0]->port_ops->scr_ग_लिखो = svia_scr_ग_लिखो;
	पूर्ण

	rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अगर (rc)
		वापस rc;
	*r_host = host;

	rc = pcim_iomap_regions(pdev, 1 << 5, DRV_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to iomap PCI BAR 5\n");
		वापस rc;
	पूर्ण

	host->ports[0]->ioaddr.scr_addr = svia_scr_addr(host->iomap[5], 0);
	host->ports[1]->ioaddr.scr_addr = svia_scr_addr(host->iomap[5], 1);

	वापस 0;
पूर्ण

अटल पूर्णांक vt6421_prepare_host(काष्ठा pci_dev *pdev, काष्ठा ata_host **r_host)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] =
		अणु &vt6421_sport_info, &vt6421_sport_info, &vt6421_pport_info पूर्ण;
	काष्ठा ata_host *host;
	पूर्णांक i, rc;

	*r_host = host = ata_host_alloc_pinfo(&pdev->dev, ppi, ARRAY_SIZE(ppi));
	अगर (!host) अणु
		dev_err(&pdev->dev, "failed to allocate host\n");
		वापस -ENOMEM;
	पूर्ण

	rc = pcim_iomap_regions(pdev, 0x3f, DRV_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to request/iomap PCI BARs (errno=%d)\n",
			rc);
		वापस rc;
	पूर्ण
	host->iomap = pcim_iomap_table(pdev);

	क्रम (i = 0; i < host->n_ports; i++)
		vt6421_init_addrs(host->ports[i]);

	वापस dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
पूर्ण

अटल पूर्णांक vt8251_prepare_host(काष्ठा pci_dev *pdev, काष्ठा ata_host **r_host)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &vt8251_port_info, शून्य पूर्ण;
	काष्ठा ata_host *host;
	पूर्णांक i, rc;

	rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अगर (rc)
		वापस rc;
	*r_host = host;

	rc = pcim_iomap_regions(pdev, 1 << 5, DRV_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to iomap PCI BAR 5\n");
		वापस rc;
	पूर्ण

	/* 8251 hosts four sata ports as M/S of the two channels */
	क्रम (i = 0; i < host->n_ports; i++)
		ata_slave_link_init(host->ports[i]);

	वापस 0;
पूर्ण

अटल व्योम svia_wd_fix(काष्ठा pci_dev *pdev)
अणु
	u8 पंचांगp8;

	pci_पढ़ो_config_byte(pdev, 0x52, &पंचांगp8);
	pci_ग_लिखो_config_byte(pdev, 0x52, पंचांगp8 | BIT(2));
पूर्ण

अटल irqवापस_t vt642x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	irqवापस_t rc = ata_bmdma_पूर्णांकerrupt(irq, dev_instance);

	/* अगर the IRQ was not handled, it might be a hotplug IRQ */
	अगर (rc != IRQ_HANDLED) अणु
		u32 serror;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&host->lock, flags);
		/* check क्रम hotplug on port 0 */
		svia_scr_पढ़ो(&host->ports[0]->link, SCR_ERROR, &serror);
		अगर (serror & SERR_PHYRDY_CHG) अणु
			ata_ehi_hotplugged(&host->ports[0]->link.eh_info);
			ata_port_मुक्तze(host->ports[0]);
			rc = IRQ_HANDLED;
		पूर्ण
		/* check क्रम hotplug on port 1 */
		svia_scr_पढ़ो(&host->ports[1]->link, SCR_ERROR, &serror);
		अगर (serror & SERR_PHYRDY_CHG) अणु
			ata_ehi_hotplugged(&host->ports[1]->link.eh_info);
			ata_port_मुक्तze(host->ports[1]);
			rc = IRQ_HANDLED;
		पूर्ण
		spin_unlock_irqrestore(&host->lock, flags);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम vt6421_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा svia_priv *hpriv = ap->host->निजी_data;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 serror;

	/* see svia_configure() क्रम description */
	अगर (!hpriv->wd_workaround) अणु
		svia_scr_पढ़ो(&ap->link, SCR_ERROR, &serror);
		अगर (serror == 0x1000500) अणु
			ata_port_warn(ap, "Incompatible drive: enabling workaround. This slows down transfer rate to ~60 MB/s");
			svia_wd_fix(pdev);
			hpriv->wd_workaround = true;
			ap->link.eh_context.i.flags |= ATA_EHI_QUIET;
		पूर्ण
	पूर्ण

	ata_sff_error_handler(ap);
पूर्ण

अटल व्योम svia_configure(काष्ठा pci_dev *pdev, पूर्णांक board_id,
			   काष्ठा svia_priv *hpriv)
अणु
	u8 पंचांगp8;

	pci_पढ़ो_config_byte(pdev, PCI_INTERRUPT_LINE, &पंचांगp8);
	dev_info(&pdev->dev, "routed to hard irq line %d\n",
		 (पूर्णांक) (पंचांगp8 & 0xf0) == 0xf0 ? 0 : पंचांगp8 & 0x0f);

	/* make sure SATA channels are enabled */
	pci_पढ़ो_config_byte(pdev, SATA_CHAN_ENAB, &पंचांगp8);
	अगर ((पंचांगp8 & ALL_PORTS) != ALL_PORTS) अणु
		dev_dbg(&pdev->dev, "enabling SATA channels (0x%x)\n",
			(पूर्णांक)पंचांगp8);
		पंचांगp8 |= ALL_PORTS;
		pci_ग_लिखो_config_byte(pdev, SATA_CHAN_ENAB, पंचांगp8);
	पूर्ण

	/* make sure पूर्णांकerrupts क्रम each channel sent to us */
	pci_पढ़ो_config_byte(pdev, SATA_INT_GATE, &पंचांगp8);
	अगर ((पंचांगp8 & ALL_PORTS) != ALL_PORTS) अणु
		dev_dbg(&pdev->dev, "enabling SATA channel interrupts (0x%x)\n",
			(पूर्णांक) पंचांगp8);
		पंचांगp8 |= ALL_PORTS;
		pci_ग_लिखो_config_byte(pdev, SATA_INT_GATE, पंचांगp8);
	पूर्ण

	/* make sure native mode is enabled */
	pci_पढ़ो_config_byte(pdev, SATA_NATIVE_MODE, &पंचांगp8);
	अगर ((पंचांगp8 & NATIVE_MODE_ALL) != NATIVE_MODE_ALL) अणु
		dev_dbg(&pdev->dev,
			"enabling SATA channel native mode (0x%x)\n",
			(पूर्णांक) पंचांगp8);
		पंचांगp8 |= NATIVE_MODE_ALL;
		pci_ग_लिखो_config_byte(pdev, SATA_NATIVE_MODE, पंचांगp8);
	पूर्ण

	अगर ((board_id == vt6420 && vt6420_hotplug) || board_id == vt6421) अणु
		/* enable IRQ on hotplug */
		pci_पढ़ो_config_byte(pdev, SVIA_MISC_3, &पंचांगp8);
		अगर ((पंचांगp8 & SATA_HOTPLUG) != SATA_HOTPLUG) अणु
			dev_dbg(&pdev->dev,
				"enabling SATA hotplug (0x%x)\n",
				(पूर्णांक) पंचांगp8);
			पंचांगp8 |= SATA_HOTPLUG;
			pci_ग_लिखो_config_byte(pdev, SVIA_MISC_3, पंचांगp8);
		पूर्ण
	पूर्ण

	/*
	 * vt6420/1 has problems talking to some drives.  The following
	 * is the fix from Joseph Chan <JosephChan@via.com.tw>.
	 *
	 * When host issues HOLD, device may send up to 20DW of data
	 * beक्रमe acknowledging it with HOLDA and the host should be
	 * able to buffer them in FIFO.  Unक्रमtunately, some WD drives
	 * send up to 40DW beक्रमe acknowledging HOLD and, in the
	 * शेष configuration, this ends up overflowing vt6421's
	 * FIFO, making the controller पात the transaction with
	 * R_ERR.
	 *
	 * Rx52[2] is the पूर्णांकernal 128DW FIFO Flow control watermark
	 * adjusting mechanism enable bit and the शेष value 0
	 * means host will issue HOLD to device when the left FIFO
	 * size goes below 32DW.  Setting it to 1 makes the watermark
	 * 64DW.
	 *
	 * https://bugzilla.kernel.org/show_bug.cgi?id=15173
	 * http://article.gmane.org/gmane.linux.ide/46352
	 * http://thपढ़ो.gmane.org/gmane.linux.kernel/1062139
	 *
	 * As the fix slows करोwn data transfer, apply it only अगर the error
	 * actually appears - see vt6421_error_handler()
	 * Apply the fix always on vt6420 as we करोn't know अगर SCR_ERROR can be
	 * पढ़ो safely.
	 */
	अगर (board_id == vt6420) अणु
		svia_wd_fix(pdev);
		hpriv->wd_workaround = true;
	पूर्ण
पूर्ण

अटल पूर्णांक svia_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;
	काष्ठा ata_host *host = शून्य;
	पूर्णांक board_id = (पूर्णांक) ent->driver_data;
	स्थिर अचिन्हित *bar_sizes;
	काष्ठा svia_priv *hpriv;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (board_id == vt6421)
		bar_sizes = &vt6421_bar_sizes[0];
	अन्यथा
		bar_sizes = &svia_bar_sizes[0];

	क्रम (i = 0; i < ARRAY_SIZE(svia_bar_sizes); i++)
		अगर ((pci_resource_start(pdev, i) == 0) ||
		    (pci_resource_len(pdev, i) < bar_sizes[i])) अणु
			dev_err(&pdev->dev,
				"invalid PCI BAR %u (sz 0x%llx, val 0x%llx)\n",
				i,
				(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, i),
				(अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, i));
			वापस -ENODEV;
		पूर्ण

	चयन (board_id) अणु
	हाल vt6420:
		rc = vt6420_prepare_host(pdev, &host);
		अवरोध;
	हाल vt6421:
		rc = vt6421_prepare_host(pdev, &host);
		अवरोध;
	हाल vt8251:
		rc = vt8251_prepare_host(pdev, &host);
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण
	अगर (rc)
		वापस rc;

	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;
	host->निजी_data = hpriv;

	svia_configure(pdev, board_id, hpriv);

	pci_set_master(pdev);
	अगर ((board_id == vt6420 && vt6420_hotplug) || board_id == vt6421)
		वापस ata_host_activate(host, pdev->irq, vt642x_पूर्णांकerrupt,
					 IRQF_SHARED, &svia_sht);
	अन्यथा
		वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
					 IRQF_SHARED, &svia_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक svia_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा svia_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (hpriv->wd_workaround)
		svia_wd_fix(pdev);
	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

module_pci_driver(svia_pci_driver);
