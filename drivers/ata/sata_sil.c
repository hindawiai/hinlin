<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_sil.c - Silicon Image SATA
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *  		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2003-2005 Red Hat, Inc.
 *  Copyright 2003 Benjamin Herrenschmidt
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Documentation क्रम SiI 3112:
 *  http://gkernel.sourceक्रमge.net/specs/sii/3112A_SiI-DS-0095-B2.pdf.bz2
 *
 *  Other errata and करोcumentation available under NDA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME	"sata_sil"
#घोषणा DRV_VERSION	"2.4"

#घोषणा SIL_DMA_BOUNDARY	0x7fffffffUL

क्रमागत अणु
	SIL_MMIO_BAR		= 5,

	/*
	 * host flags
	 */
	SIL_FLAG_NO_SATA_IRQ	= (1 << 28),
	SIL_FLAG_RERR_ON_DMA_ACT = (1 << 29),
	SIL_FLAG_MOD15WRITE	= (1 << 30),

	SIL_DFL_PORT_FLAGS	= ATA_FLAG_SATA,

	/*
	 * Controller IDs
	 */
	sil_3112		= 0,
	sil_3112_no_sata_irq	= 1,
	sil_3512		= 2,
	sil_3114		= 3,

	/*
	 * Register offsets
	 */
	SIL_SYSCFG		= 0x48,

	/*
	 * Register bits
	 */
	/* SYSCFG */
	SIL_MASK_IDE0_INT	= (1 << 22),
	SIL_MASK_IDE1_INT	= (1 << 23),
	SIL_MASK_IDE2_INT	= (1 << 24),
	SIL_MASK_IDE3_INT	= (1 << 25),
	SIL_MASK_2PORT		= SIL_MASK_IDE0_INT | SIL_MASK_IDE1_INT,
	SIL_MASK_4PORT		= SIL_MASK_2PORT |
				  SIL_MASK_IDE2_INT | SIL_MASK_IDE3_INT,

	/* BMDMA/BMDMA2 */
	SIL_INTR_STEERING	= (1 << 1),

	SIL_DMA_ENABLE		= (1 << 0),  /* DMA run चयन */
	SIL_DMA_RDWR		= (1 << 3),  /* DMA Rd-Wr */
	SIL_DMA_SATA_IRQ	= (1 << 4),  /* OR of all SATA IRQs */
	SIL_DMA_ACTIVE		= (1 << 16), /* DMA running */
	SIL_DMA_ERROR		= (1 << 17), /* PCI bus error */
	SIL_DMA_COMPLETE	= (1 << 18), /* cmd complete / IRQ pending */
	SIL_DMA_N_SATA_IRQ	= (1 << 6),  /* SATA_IRQ क्रम the next channel */
	SIL_DMA_N_ACTIVE	= (1 << 24), /* ACTIVE क्रम the next channel */
	SIL_DMA_N_ERROR		= (1 << 25), /* ERROR क्रम the next channel */
	SIL_DMA_N_COMPLETE	= (1 << 26), /* COMPLETE क्रम the next channel */

	/* SIEN */
	SIL_SIEN_N		= (1 << 16), /* triggered by SError.N */

	/*
	 * Others
	 */
	SIL_QUIRK_MOD15WRITE	= (1 << 0),
	SIL_QUIRK_UDMA5MAX	= (1 << 1),
पूर्ण;

अटल पूर्णांक sil_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sil_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
अटल व्योम sil_dev_config(काष्ठा ata_device *dev);
अटल पूर्णांक sil_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक sil_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);
अटल पूर्णांक sil_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed);
अटल क्रमागत ata_completion_errors sil_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल व्योम sil_bmdma_setup(काष्ठा ata_queued_cmd *qc);
अटल व्योम sil_bmdma_start(काष्ठा ata_queued_cmd *qc);
अटल व्योम sil_bmdma_stop(काष्ठा ata_queued_cmd *qc);
अटल व्योम sil_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम sil_thaw(काष्ठा ata_port *ap);


अटल स्थिर काष्ठा pci_device_id sil_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CMD, 0x3112), sil_3112 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x0240), sil_3112 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x3512), sil_3512 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x3114), sil_3114 पूर्ण,
	अणु PCI_VDEVICE(ATI, 0x436e), sil_3112 पूर्ण,
	अणु PCI_VDEVICE(ATI, 0x4379), sil_3112_no_sata_irq पूर्ण,
	अणु PCI_VDEVICE(ATI, 0x437a), sil_3112_no_sata_irq पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;


/* TODO firmware versions should be added - eric */
अटल स्थिर काष्ठा sil_drivelist अणु
	स्थिर अक्षर *product;
	अचिन्हित पूर्णांक quirk;
पूर्ण sil_blacklist [] = अणु
	अणु "ST320012AS",		SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST330013AS",		SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST340017AS",		SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST360015AS",		SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST380023AS",		SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST3120023AS",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST340014ASL",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST360014ASL",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST380011ASL",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST3120022ASL",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "ST3160021ASL",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "TOSHIBA MK2561GSYN",	SIL_QUIRK_MOD15WRITE पूर्ण,
	अणु "Maxtor 4D060H3",	SIL_QUIRK_UDMA5MAX पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver sil_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= sil_pci_tbl,
	.probe			= sil_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= sil_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा sil_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	/** These controllers support Large Block Transfer which allows
	    transfer chunks up to 2GB and which cross 64KB boundaries,
	    thereक्रमe the DMA limits are more relaxed than standard ATA SFF. */
	.dma_boundary		= SIL_DMA_BOUNDARY,
	.sg_tablesize		= ATA_MAX_PRD
पूर्ण;

अटल काष्ठा ata_port_operations sil_ops = अणु
	.inherits		= &ata_bmdma32_port_ops,
	.dev_config		= sil_dev_config,
	.set_mode		= sil_set_mode,
	.bmdma_setup            = sil_bmdma_setup,
	.bmdma_start            = sil_bmdma_start,
	.bmdma_stop		= sil_bmdma_stop,
	.qc_prep		= sil_qc_prep,
	.मुक्तze			= sil_मुक्तze,
	.thaw			= sil_thaw,
	.scr_पढ़ो		= sil_scr_पढ़ो,
	.scr_ग_लिखो		= sil_scr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info sil_port_info[] = अणु
	/* sil_3112 */
	अणु
		.flags		= SIL_DFL_PORT_FLAGS | SIL_FLAG_MOD15WRITE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil_ops,
	पूर्ण,
	/* sil_3112_no_sata_irq */
	अणु
		.flags		= SIL_DFL_PORT_FLAGS | SIL_FLAG_MOD15WRITE |
				  SIL_FLAG_NO_SATA_IRQ,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil_ops,
	पूर्ण,
	/* sil_3512 */
	अणु
		.flags		= SIL_DFL_PORT_FLAGS | SIL_FLAG_RERR_ON_DMA_ACT,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil_ops,
	पूर्ण,
	/* sil_3114 */
	अणु
		.flags		= SIL_DFL_PORT_FLAGS | SIL_FLAG_RERR_ON_DMA_ACT,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil_ops,
	पूर्ण,
पूर्ण;

/* per-port रेजिस्टर offsets */
/* TODO: we can probably calculate rather than use a table */
अटल स्थिर काष्ठा अणु
	अचिन्हित दीर्घ tf;	/* ATA taskfile रेजिस्टर block */
	अचिन्हित दीर्घ ctl;	/* ATA control/altstatus रेजिस्टर block */
	अचिन्हित दीर्घ bmdma;	/* DMA रेजिस्टर block */
	अचिन्हित दीर्घ bmdma2;	/* DMA रेजिस्टर block #2 */
	अचिन्हित दीर्घ fअगरo_cfg;	/* FIFO Valid Byte Count and Control */
	अचिन्हित दीर्घ scr;	/* SATA control रेजिस्टर block */
	अचिन्हित दीर्घ sien;	/* SATA Interrupt Enable रेजिस्टर */
	अचिन्हित दीर्घ xfer_mode;/* data transfer mode रेजिस्टर */
	अचिन्हित दीर्घ sfis_cfg;	/* SATA FIS reception config रेजिस्टर */
पूर्ण sil_port[] = अणु
	/* port 0 ... */
	/*   tf    ctl  bmdma  bmdma2  fअगरo    scr   sien   mode   sfis */
	अणु  0x80,  0x8A,   0x0,  0x10,  0x40, 0x100, 0x148,  0xb4, 0x14c पूर्ण,
	अणु  0xC0,  0xCA,   0x8,  0x18,  0x44, 0x180, 0x1c8,  0xf4, 0x1cc पूर्ण,
	अणु 0x280, 0x28A, 0x200, 0x210, 0x240, 0x300, 0x348, 0x2b4, 0x34c पूर्ण,
	अणु 0x2C0, 0x2CA, 0x208, 0x218, 0x244, 0x380, 0x3c8, 0x2f4, 0x3cc पूर्ण,
	/* ... port 3 */
पूर्ण;

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("low-level driver for Silicon Image SATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sil_pci_tbl);
MODULE_VERSION(DRV_VERSION);

अटल पूर्णांक slow_करोwn;
module_param(slow_करोwn, पूर्णांक, 0444);
MODULE_PARM_DESC(slow_करोwn, "Sledgehammer used to work around random problems, by limiting commands to 15 sectors (0=off, 1=on)");


अटल व्योम sil_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *mmio_base = ap->host->iomap[SIL_MMIO_BAR];
	व्योम __iomem *bmdma2 = mmio_base + sil_port[ap->port_no].bmdma2;

	/* clear start/stop bit - can safely always ग_लिखो 0 */
	ioग_लिखो8(0, bmdma2);

	/* one-PIO-cycle guaranteed रुको, per spec, क्रम HDMA1:0 transition */
	ata_sff_dma_छोड़ो(ap);
पूर्ण

अटल व्योम sil_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *bmdma = ap->ioaddr.bmdma_addr;

	/* load PRD table addr. */
	ioग_लिखो32(ap->bmdma_prd_dma, bmdma + ATA_DMA_TABLE_OFS);

	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

अटल व्योम sil_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	अचिन्हित पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *mmio_base = ap->host->iomap[SIL_MMIO_BAR];
	व्योम __iomem *bmdma2 = mmio_base + sil_port[ap->port_no].bmdma2;
	u8 dmactl = ATA_DMA_START;

	/* set transfer direction, start host DMA transaction
	   Note: For Large Block Transfer to work, the DMA must be started
	   using the bmdma2 रेजिस्टर. */
	अगर (!rw)
		dmactl |= ATA_DMA_WR;
	ioग_लिखो8(dmactl, bmdma2);
पूर्ण

/* The way God पूर्णांकended PCI IDE scatter/gather lists to look and behave... */
अटल व्योम sil_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_bmdma_prd *prd, *last_prd = शून्य;
	अचिन्हित पूर्णांक si;

	prd = &ap->bmdma_prd[0];
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		/* Note h/w करोesn't support 64-bit, so we unconditionally
		 * truncate dma_addr_t to u32.
		 */
		u32 addr = (u32) sg_dma_address(sg);
		u32 sg_len = sg_dma_len(sg);

		prd->addr = cpu_to_le32(addr);
		prd->flags_len = cpu_to_le32(sg_len);
		VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", si, addr, sg_len);

		last_prd = prd;
		prd++;
	पूर्ण

	अगर (likely(last_prd))
		last_prd->flags_len |= cpu_to_le32(ATA_PRD_EOT);
पूर्ण

अटल क्रमागत ata_completion_errors sil_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	sil_fill_sg(qc);

	वापस AC_ERR_OK;
पूर्ण

अटल अचिन्हित अक्षर sil_get_device_cache_line(काष्ठा pci_dev *pdev)
अणु
	u8 cache_line = 0;
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE, &cache_line);
	वापस cache_line;
पूर्ण

/**
 *	sil_set_mode		-	wrap set_mode functions
 *	@link: link to set up
 *	@r_failed: वापसed device when we fail
 *
 *	Wrap the libata method क्रम device setup as after the setup we need
 *	to inspect the results and करो some configuration work
 */

अटल पूर्णांक sil_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *mmio_base = ap->host->iomap[SIL_MMIO_BAR];
	व्योम __iomem *addr = mmio_base + sil_port[ap->port_no].xfer_mode;
	काष्ठा ata_device *dev;
	u32 पंचांगp, dev_mode[2] = अणु पूर्ण;
	पूर्णांक rc;

	rc = ata_करो_set_mode(link, r_failed);
	अगर (rc)
		वापस rc;

	ata_क्रम_each_dev(dev, link, ALL) अणु
		अगर (!ata_dev_enabled(dev))
			dev_mode[dev->devno] = 0;	/* PIO0/1/2 */
		अन्यथा अगर (dev->flags & ATA_DFLAG_PIO)
			dev_mode[dev->devno] = 1;	/* PIO3/4 */
		अन्यथा
			dev_mode[dev->devno] = 3;	/* UDMA */
		/* value 2 indicates MDMA */
	पूर्ण

	पंचांगp = पढ़ोl(addr);
	पंचांगp &= ~((1<<5) | (1<<4) | (1<<1) | (1<<0));
	पंचांगp |= dev_mode[0];
	पंचांगp |= (dev_mode[1] << 4);
	ग_लिखोl(पंचांगp, addr);
	पढ़ोl(addr);	/* flush */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __iomem *sil_scr_addr(काष्ठा ata_port *ap,
					 अचिन्हित पूर्णांक sc_reg)
अणु
	व्योम __iomem *offset = ap->ioaddr.scr_addr;

	चयन (sc_reg) अणु
	हाल SCR_STATUS:
		वापस offset + 4;
	हाल SCR_ERROR:
		वापस offset + 8;
	हाल SCR_CONTROL:
		वापस offset;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sil_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	व्योम __iomem *mmio = sil_scr_addr(link->ap, sc_reg);

	अगर (mmio) अणु
		*val = पढ़ोl(mmio);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sil_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	व्योम __iomem *mmio = sil_scr_addr(link->ap, sc_reg);

	अगर (mmio) अणु
		ग_लिखोl(val, mmio);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम sil_host_पूर्णांकr(काष्ठा ata_port *ap, u32 bmdma2)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	काष्ठा ata_queued_cmd *qc = ata_qc_from_tag(ap, ap->link.active_tag);
	u8 status;

	अगर (unlikely(bmdma2 & SIL_DMA_SATA_IRQ)) अणु
		u32 serror = 0xffffffff;

		/* SIEN करोesn't mask SATA IRQs on some 3112s.  Those
		 * controllers जारी to निश्चित IRQ as दीर्घ as
		 * SError bits are pending.  Clear SError immediately.
		 */
		sil_scr_पढ़ो(&ap->link, SCR_ERROR, &serror);
		sil_scr_ग_लिखो(&ap->link, SCR_ERROR, serror);

		/* Someबार spurious पूर्णांकerrupts occur, द्विगुन check
		 * it's PHYRDY CHG.
		 */
		अगर (serror & SERR_PHYRDY_CHG) अणु
			ap->link.eh_info.serror |= serror;
			जाओ मुक्तze;
		पूर्ण

		अगर (!(bmdma2 & SIL_DMA_COMPLETE))
			वापस;
	पूर्ण

	अगर (unlikely(!qc || (qc->tf.flags & ATA_TFLAG_POLLING))) अणु
		/* this someबार happens, just clear IRQ */
		ap->ops->sff_check_status(ap);
		वापस;
	पूर्ण

	/* Check whether we are expecting पूर्णांकerrupt in this state */
	चयन (ap->hsm_task_state) अणु
	हाल HSM_ST_FIRST:
		/* Some pre-ATAPI-4 devices निश्चित INTRQ
		 * at this state when पढ़ोy to receive CDB.
		 */

		/* Check the ATA_DFLAG_CDB_INTR flag is enough here.
		 * The flag was turned on only क्रम atapi devices.  No
		 * need to check ata_is_atapi(qc->tf.protocol) again.
		 */
		अगर (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			जाओ err_hsm;
		अवरोध;
	हाल HSM_ST_LAST:
		अगर (ata_is_dma(qc->tf.protocol)) अणु
			/* clear DMA-Start bit */
			ap->ops->bmdma_stop(qc);

			अगर (bmdma2 & SIL_DMA_ERROR) अणु
				qc->err_mask |= AC_ERR_HOST_BUS;
				ap->hsm_task_state = HSM_ST_ERR;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HSM_ST:
		अवरोध;
	शेष:
		जाओ err_hsm;
	पूर्ण

	/* check मुख्य status, clearing INTRQ */
	status = ap->ops->sff_check_status(ap);
	अगर (unlikely(status & ATA_BUSY))
		जाओ err_hsm;

	/* ack bmdma irq events */
	ata_bmdma_irq_clear(ap);

	/* kick HSM in the ass */
	ata_sff_hsm_move(ap, qc, status, 0);

	अगर (unlikely(qc->err_mask) && ata_is_dma(qc->tf.protocol))
		ata_ehi_push_desc(ehi, "BMDMA2 stat 0x%x", bmdma2);

	वापस;

 err_hsm:
	qc->err_mask |= AC_ERR_HSM;
 मुक्तze:
	ata_port_मुक्तze(ap);
पूर्ण

अटल irqवापस_t sil_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	व्योम __iomem *mmio_base = host->iomap[SIL_MMIO_BAR];
	पूर्णांक handled = 0;
	पूर्णांक i;

	spin_lock(&host->lock);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		u32 bmdma2 = पढ़ोl(mmio_base + sil_port[ap->port_no].bmdma2);

		/* turn off SATA_IRQ अगर not supported */
		अगर (ap->flags & SIL_FLAG_NO_SATA_IRQ)
			bmdma2 &= ~SIL_DMA_SATA_IRQ;

		अगर (bmdma2 == 0xffffffff ||
		    !(bmdma2 & (SIL_DMA_COMPLETE | SIL_DMA_SATA_IRQ)))
			जारी;

		sil_host_पूर्णांकr(ap, bmdma2);
		handled = 1;
	पूर्ण

	spin_unlock(&host->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम sil_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio_base = ap->host->iomap[SIL_MMIO_BAR];
	u32 पंचांगp;

	/* global IRQ mask करोesn't block SATA IRQ, turn off explicitly */
	ग_लिखोl(0, mmio_base + sil_port[ap->port_no].sien);

	/* plug IRQ */
	पंचांगp = पढ़ोl(mmio_base + SIL_SYSCFG);
	पंचांगp |= SIL_MASK_IDE0_INT << ap->port_no;
	ग_लिखोl(पंचांगp, mmio_base + SIL_SYSCFG);
	पढ़ोl(mmio_base + SIL_SYSCFG);	/* flush */

	/* Ensure DMA_ENABLE is off.
	 *
	 * This is because the controller will not give us access to the
	 * taskfile रेजिस्टरs जबतक a DMA is in progress
	 */
	ioग_लिखो8(ioपढ़ो8(ap->ioaddr.bmdma_addr) & ~SIL_DMA_ENABLE,
		 ap->ioaddr.bmdma_addr);

	/* According to ata_bmdma_stop, an HDMA transition requires
	 * on PIO cycle. But we can't पढ़ो a taskfile रेजिस्टर.
	 */
	ioपढ़ो8(ap->ioaddr.bmdma_addr);
पूर्ण

अटल व्योम sil_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio_base = ap->host->iomap[SIL_MMIO_BAR];
	u32 पंचांगp;

	/* clear IRQ */
	ap->ops->sff_check_status(ap);
	ata_bmdma_irq_clear(ap);

	/* turn on SATA IRQ अगर supported */
	अगर (!(ap->flags & SIL_FLAG_NO_SATA_IRQ))
		ग_लिखोl(SIL_SIEN_N, mmio_base + sil_port[ap->port_no].sien);

	/* turn on IRQ */
	पंचांगp = पढ़ोl(mmio_base + SIL_SYSCFG);
	पंचांगp &= ~(SIL_MASK_IDE0_INT << ap->port_no);
	ग_लिखोl(पंचांगp, mmio_base + SIL_SYSCFG);
पूर्ण

/**
 *	sil_dev_config - Apply device/host-specअगरic errata fixups
 *	@dev: Device to be examined
 *
 *	After the IDENTIFY [PACKET] DEVICE step is complete, and a
 *	device is known to be present, this function is called.
 *	We apply two errata fixups which are specअगरic to Silicon Image,
 *	a Seagate and a Maxtor fixup.
 *
 *	For certain Seagate devices, we must limit the maximum sectors
 *	to under 8K.
 *
 *	For certain Maxtor devices, we must not program the drive
 *	beyond udma5.
 *
 *	Both fixups are unfairly pessimistic.  As soon as I get more
 *	inक्रमmation on these errata, I will create a more exhaustive
 *	list, and apply the fixups to only the specअगरic
 *	devices/hosts/firmwares that need it.
 *
 *	20040111 - Seagate drives affected by the Mod15Write bug are blacklisted
 *	The Maxtor quirk is in the blacklist, but I'm keeping the original
 *	pessimistic fix क्रम the following reasons...
 *	- There seems to be less info on it, only one device gleaned off the
 *	Winकरोws	driver, maybe only one is affected.  More info would be greatly
 *	appreciated.
 *	- But then again UDMA5 is hardly anything to complain about
 */
अटल व्योम sil_dev_config(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	पूर्णांक prपूर्णांक_info = ap->link.eh_context.i.flags & ATA_EHI_PRINTINFO;
	अचिन्हित पूर्णांक n, quirks = 0;
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];

	/* This controller करोesn't support trim */
	dev->horkage |= ATA_HORKAGE_NOTRIM;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, माप(model_num));

	क्रम (n = 0; sil_blacklist[n].product; n++)
		अगर (!म_भेद(sil_blacklist[n].product, model_num)) अणु
			quirks = sil_blacklist[n].quirk;
			अवरोध;
		पूर्ण

	/* limit requests to 15 sectors */
	अगर (slow_करोwn ||
	    ((ap->flags & SIL_FLAG_MOD15WRITE) &&
	     (quirks & SIL_QUIRK_MOD15WRITE))) अणु
		अगर (prपूर्णांक_info)
			ata_dev_info(dev,
		"applying Seagate errata fix (mod15write workaround)\n");
		dev->max_sectors = 15;
		वापस;
	पूर्ण

	/* limit to udma5 */
	अगर (quirks & SIL_QUIRK_UDMA5MAX) अणु
		अगर (prपूर्णांक_info)
			ata_dev_info(dev, "applying Maxtor errata fix %s\n",
				     model_num);
		dev->udma_mask &= ATA_UDMA5;
		वापस;
	पूर्ण
पूर्ण

अटल व्योम sil_init_controller(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	व्योम __iomem *mmio_base = host->iomap[SIL_MMIO_BAR];
	u8 cls;
	u32 पंचांगp;
	पूर्णांक i;

	/* Initialize FIFO PCI bus arbitration */
	cls = sil_get_device_cache_line(pdev);
	अगर (cls) अणु
		cls >>= 3;
		cls++;  /* cls = (line_size/8)+1 */
		क्रम (i = 0; i < host->n_ports; i++)
			ग_लिखोw(cls << 8 | cls,
			       mmio_base + sil_port[i].fअगरo_cfg);
	पूर्ण अन्यथा
		dev_warn(&pdev->dev,
			 "cache line size not set.  Driver may not function\n");

	/* Apply R_ERR on DMA activate FIS errata workaround */
	अगर (host->ports[0]->flags & SIL_FLAG_RERR_ON_DMA_ACT) अणु
		पूर्णांक cnt;

		क्रम (i = 0, cnt = 0; i < host->n_ports; i++) अणु
			पंचांगp = पढ़ोl(mmio_base + sil_port[i].sfis_cfg);
			अगर ((पंचांगp & 0x3) != 0x01)
				जारी;
			अगर (!cnt)
				dev_info(&pdev->dev,
					 "Applying R_ERR on DMA activate FIS errata fix\n");
			ग_लिखोl(पंचांगp & ~0x3, mmio_base + sil_port[i].sfis_cfg);
			cnt++;
		पूर्ण
	पूर्ण

	अगर (host->n_ports == 4) अणु
		/* flip the magic "make 4 ports work" bit */
		पंचांगp = पढ़ोl(mmio_base + sil_port[2].bmdma);
		अगर ((पंचांगp & SIL_INTR_STEERING) == 0)
			ग_लिखोl(पंचांगp | SIL_INTR_STEERING,
			       mmio_base + sil_port[2].bmdma);
	पूर्ण
पूर्ण

अटल bool sil_broken_प्रणाली_घातeroff(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id broken_प्रणालीs[] = अणु
		अणु
			.ident = "HP Compaq nx6325",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nx6325"),
			पूर्ण,
			/* PCI slot number of the controller */
			.driver_data = (व्योम *)0x12UL,
		पूर्ण,

		अणु पूर्ण	/* terminate list */
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi = dmi_first_match(broken_प्रणालीs);

	अगर (dmi) अणु
		अचिन्हित दीर्घ slot = (अचिन्हित दीर्घ)dmi->driver_data;
		/* apply the quirk only to on-board controllers */
		वापस slot == PCI_SLOT(pdev->devfn);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक sil_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक board_id = ent->driver_data;
	काष्ठा ata_port_info pi = sil_port_info[board_id];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *mmio_base;
	पूर्णांक n_ports, rc;
	अचिन्हित पूर्णांक i;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* allocate host */
	n_ports = 2;
	अगर (board_id == sil_3114)
		n_ports = 4;

	अगर (sil_broken_प्रणाली_घातeroff(pdev)) अणु
		pi.flags |= ATA_FLAG_NO_POWEROFF_SPINDOWN |
					ATA_FLAG_NO_HIBERNATE_SPINDOWN;
		dev_info(&pdev->dev, "quirky BIOS, skipping spindown "
				"on poweroff and hibernation\n");
	पूर्ण

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	अगर (!host)
		वापस -ENOMEM;

	/* acquire resources and fill host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, 1 << SIL_MMIO_BAR, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);

	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;

	mmio_base = host->iomap[SIL_MMIO_BAR];

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

		ioaddr->cmd_addr = mmio_base + sil_port[i].tf;
		ioaddr->altstatus_addr =
		ioaddr->ctl_addr = mmio_base + sil_port[i].ctl;
		ioaddr->bmdma_addr = mmio_base + sil_port[i].bmdma;
		ioaddr->scr_addr = mmio_base + sil_port[i].scr;
		ata_sff_std_ports(ioaddr);

		ata_port_pbar_desc(ap, SIL_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, SIL_MMIO_BAR, sil_port[i].tf, "tf");
	पूर्ण

	/* initialize and activate */
	sil_init_controller(host);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, sil_पूर्णांकerrupt, IRQF_SHARED,
				 &sil_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sil_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	sil_init_controller(host);
	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

module_pci_driver(sil_pci_driver);
