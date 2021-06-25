<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_promise.c - Promise SATA
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *		    Mikael Pettersson
 *  		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2003-2004 Red Hat, Inc.
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware inक्रमmation only available under NDA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>
#समावेश "sata_promise.h"

#घोषणा DRV_NAME	"sata_promise"
#घोषणा DRV_VERSION	"2.12"

क्रमागत अणु
	PDC_MAX_PORTS		= 4,
	PDC_MMIO_BAR		= 3,
	PDC_MAX_PRD		= LIBATA_MAX_PRD - 1, /* -1 क्रम ASIC PRD bug workaround */

	/* host रेजिस्टर offsets (from host->iomap[PDC_MMIO_BAR]) */
	PDC_INT_SEQMASK		= 0x40,	/* Mask of निश्चितed SEQ INTs */
	PDC_FLASH_CTL		= 0x44, /* Flash control रेजिस्टर */
	PDC_PCI_CTL		= 0x48, /* PCI control/status reg */
	PDC_SATA_PLUG_CSR	= 0x6C, /* SATA Plug control/status reg */
	PDC2_SATA_PLUG_CSR	= 0x60, /* SATAII Plug control/status reg */
	PDC_TBG_MODE		= 0x41C, /* TBG mode (not SATAII) */
	PDC_SLEW_CTL		= 0x470, /* slew rate control reg (not SATAII) */

	/* per-port ATA रेजिस्टर offsets (from ap->ioaddr.cmd_addr) */
	PDC_FEATURE		= 0x04, /* Feature/Error reg (per port) */
	PDC_SECTOR_COUNT	= 0x08, /* Sector count reg (per port) */
	PDC_SECTOR_NUMBER	= 0x0C, /* Sector number reg (per port) */
	PDC_CYLINDER_LOW	= 0x10, /* Cylinder low reg (per port) */
	PDC_CYLINDER_HIGH	= 0x14, /* Cylinder high reg (per port) */
	PDC_DEVICE		= 0x18, /* Device/Head reg (per port) */
	PDC_COMMAND		= 0x1C, /* Command/status reg (per port) */
	PDC_ALTSTATUS		= 0x38, /* Alternate-status/device-control reg (per port) */
	PDC_PKT_SUBMIT		= 0x40, /* Command packet poपूर्णांकer addr */
	PDC_GLOBAL_CTL		= 0x48, /* Global control/status (per port) */
	PDC_CTLSTAT		= 0x60,	/* IDE control and status (per port) */

	/* per-port SATA रेजिस्टर offsets (from ap->ioaddr.scr_addr) */
	PDC_SATA_ERROR		= 0x04,
	PDC_PHYMODE4		= 0x14,
	PDC_LINK_LAYER_ERRORS	= 0x6C,
	PDC_FPDMA_CTLSTAT	= 0xD8,
	PDC_INTERNAL_DEBUG_1	= 0xF8,	/* also used क्रम PATA */
	PDC_INTERNAL_DEBUG_2	= 0xFC,	/* also used क्रम PATA */

	/* PDC_FPDMA_CTLSTAT bit definitions */
	PDC_FPDMA_CTLSTAT_RESET			= 1 << 3,
	PDC_FPDMA_CTLSTAT_DMASETUP_INT_FLAG	= 1 << 10,
	PDC_FPDMA_CTLSTAT_SETDB_INT_FLAG	= 1 << 11,

	/* PDC_GLOBAL_CTL bit definitions */
	PDC_PH_ERR		= (1 <<  8), /* PCI error जबतक loading packet */
	PDC_SH_ERR		= (1 <<  9), /* PCI error जबतक loading S/G table */
	PDC_DH_ERR		= (1 << 10), /* PCI error जबतक loading data */
	PDC2_HTO_ERR		= (1 << 12), /* host bus समयout */
	PDC2_ATA_HBA_ERR	= (1 << 13), /* error during SATA DATA FIS transmission */
	PDC2_ATA_DMA_CNT_ERR	= (1 << 14), /* DMA DATA FIS size dअगरfers from S/G count */
	PDC_OVERRUN_ERR		= (1 << 19), /* S/G byte count larger than HD requires */
	PDC_UNDERRUN_ERR	= (1 << 20), /* S/G byte count less than HD requires */
	PDC_DRIVE_ERR		= (1 << 21), /* drive error */
	PDC_PCI_SYS_ERR		= (1 << 22), /* PCI प्रणाली error */
	PDC1_PCI_PARITY_ERR	= (1 << 23), /* PCI parity error (from SATA150 driver) */
	PDC1_ERR_MASK		= PDC1_PCI_PARITY_ERR,
	PDC2_ERR_MASK		= PDC2_HTO_ERR | PDC2_ATA_HBA_ERR |
				  PDC2_ATA_DMA_CNT_ERR,
	PDC_ERR_MASK		= PDC_PH_ERR | PDC_SH_ERR | PDC_DH_ERR |
				  PDC_OVERRUN_ERR | PDC_UNDERRUN_ERR |
				  PDC_DRIVE_ERR | PDC_PCI_SYS_ERR |
				  PDC1_ERR_MASK | PDC2_ERR_MASK,

	board_2037x		= 0,	/* FastTrak S150 TX2plus */
	board_2037x_pata	= 1,	/* FastTrak S150 TX2plus PATA port */
	board_20319		= 2,	/* FastTrak S150 TX4 */
	board_20619		= 3,	/* FastTrak TX4000 */
	board_2057x		= 4,	/* SATAII150 Tx2plus */
	board_2057x_pata	= 5,	/* SATAII150 Tx2plus PATA port */
	board_40518		= 6,	/* SATAII150 Tx4 */

	PDC_HAS_PATA		= (1 << 1), /* PDC20375/20575 has PATA */

	/* Sequence counter control रेजिस्टरs bit definitions */
	PDC_SEQCNTRL_INT_MASK	= (1 << 5), /* Sequence Interrupt Mask */

	/* Feature रेजिस्टर values */
	PDC_FEATURE_ATAPI_PIO	= 0x00, /* ATAPI data xfer by PIO */
	PDC_FEATURE_ATAPI_DMA	= 0x01, /* ATAPI data xfer by DMA */

	/* Device/Head रेजिस्टर values */
	PDC_DEVICE_SATA		= 0xE0, /* Device/Head value क्रम SATA devices */

	/* PDC_CTLSTAT bit definitions */
	PDC_DMA_ENABLE		= (1 << 7),
	PDC_IRQ_DISABLE		= (1 << 10),
	PDC_RESET		= (1 << 11), /* HDMA reset */

	PDC_COMMON_FLAGS	= ATA_FLAG_PIO_POLLING,

	/* ap->flags bits */
	PDC_FLAG_GEN_II		= (1 << 24),
	PDC_FLAG_SATA_PATA	= (1 << 25), /* supports SATA + PATA */
	PDC_FLAG_4_PORTS	= (1 << 26), /* 4 ports */
पूर्ण;

काष्ठा pdc_port_priv अणु
	u8			*pkt;
	dma_addr_t		pkt_dma;
पूर्ण;

काष्ठा pdc_host_priv अणु
	spinlock_t hard_reset_lock;
पूर्ण;

अटल पूर्णांक pdc_sata_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक pdc_sata_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);
अटल पूर्णांक pdc_ata_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल पूर्णांक pdc_common_port_start(काष्ठा ata_port *ap);
अटल पूर्णांक pdc_sata_port_start(काष्ठा ata_port *ap);
अटल क्रमागत ata_completion_errors pdc_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल व्योम pdc_tf_load_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
अटल व्योम pdc_exec_command_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
अटल पूर्णांक pdc_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक pdc_old_sata_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल व्योम pdc_irq_clear(काष्ठा ata_port *ap);
अटल अचिन्हित पूर्णांक pdc_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल व्योम pdc_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम pdc_sata_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम pdc_thaw(काष्ठा ata_port *ap);
अटल व्योम pdc_sata_thaw(काष्ठा ata_port *ap);
अटल पूर्णांक pdc_pata_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline);
अटल पूर्णांक pdc_sata_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline);
अटल व्योम pdc_error_handler(काष्ठा ata_port *ap);
अटल व्योम pdc_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक pdc_pata_cable_detect(काष्ठा ata_port *ap);

अटल काष्ठा scsi_host_ढाँचा pdc_ata_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= PDC_MAX_PRD,
	.dma_boundary		= ATA_DMA_BOUNDARY,
पूर्ण;

अटल स्थिर काष्ठा ata_port_operations pdc_common_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.sff_tf_load		= pdc_tf_load_mmio,
	.sff_exec_command	= pdc_exec_command_mmio,
	.check_atapi_dma	= pdc_check_atapi_dma,
	.qc_prep		= pdc_qc_prep,
	.qc_issue		= pdc_qc_issue,

	.sff_irq_clear		= pdc_irq_clear,
	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,

	.post_पूर्णांकernal_cmd	= pdc_post_पूर्णांकernal_cmd,
	.error_handler		= pdc_error_handler,
पूर्ण;

अटल काष्ठा ata_port_operations pdc_sata_ops = अणु
	.inherits		= &pdc_common_ops,
	.cable_detect		= ata_cable_sata,
	.मुक्तze			= pdc_sata_मुक्तze,
	.thaw			= pdc_sata_thaw,
	.scr_पढ़ो		= pdc_sata_scr_पढ़ो,
	.scr_ग_लिखो		= pdc_sata_scr_ग_लिखो,
	.port_start		= pdc_sata_port_start,
	.hardreset		= pdc_sata_hardreset,
पूर्ण;

/* First-generation chips need a more restrictive ->check_atapi_dma op,
   and ->मुक्तze/thaw that ignore the hotplug controls. */
अटल काष्ठा ata_port_operations pdc_old_sata_ops = अणु
	.inherits		= &pdc_sata_ops,
	.मुक्तze			= pdc_मुक्तze,
	.thaw			= pdc_thaw,
	.check_atapi_dma	= pdc_old_sata_check_atapi_dma,
पूर्ण;

अटल काष्ठा ata_port_operations pdc_pata_ops = अणु
	.inherits		= &pdc_common_ops,
	.cable_detect		= pdc_pata_cable_detect,
	.मुक्तze			= pdc_मुक्तze,
	.thaw			= pdc_thaw,
	.port_start		= pdc_common_port_start,
	.softreset		= pdc_pata_softreset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info pdc_port_info[] = अणु
	[board_2037x] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SATA |
				  PDC_FLAG_SATA_PATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_old_sata_ops,
	पूर्ण,

	[board_2037x_pata] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_pata_ops,
	पूर्ण,

	[board_20319] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SATA |
				  PDC_FLAG_4_PORTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_old_sata_ops,
	पूर्ण,

	[board_20619] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SLAVE_POSS |
				  PDC_FLAG_4_PORTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_pata_ops,
	पूर्ण,

	[board_2057x] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SATA |
				  PDC_FLAG_GEN_II | PDC_FLAG_SATA_PATA,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_sata_ops,
	पूर्ण,

	[board_2057x_pata] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SLAVE_POSS |
				  PDC_FLAG_GEN_II,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_pata_ops,
	पूर्ण,

	[board_40518] =
	अणु
		.flags		= PDC_COMMON_FLAGS | ATA_FLAG_SATA |
				  PDC_FLAG_GEN_II | PDC_FLAG_4_PORTS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_sata_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pdc_ata_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PROMISE, 0x3371), board_2037x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3373), board_2037x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3375), board_2037x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3376), board_2037x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3570), board_2057x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3571), board_2057x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3574), board_2057x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3577), board_2057x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3d73), board_2057x पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3d75), board_2057x पूर्ण,

	अणु PCI_VDEVICE(PROMISE, 0x3318), board_20319 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3319), board_20319 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3515), board_40518 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3519), board_40518 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3d17), board_40518 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, 0x3d18), board_40518 पूर्ण,

	अणु PCI_VDEVICE(PROMISE, 0x6629), board_20619 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver pdc_ata_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= pdc_ata_pci_tbl,
	.probe			= pdc_ata_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

अटल पूर्णांक pdc_common_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा pdc_port_priv *pp;
	पूर्णांक rc;

	/* we use the same prd table as bmdma, allocate it */
	rc = ata_bmdma_port_start(ap);
	अगर (rc)
		वापस rc;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	pp->pkt = dmam_alloc_coherent(dev, 128, &pp->pkt_dma, GFP_KERNEL);
	अगर (!pp->pkt)
		वापस -ENOMEM;

	ap->निजी_data = pp;

	वापस 0;
पूर्ण

अटल पूर्णांक pdc_sata_port_start(काष्ठा ata_port *ap)
अणु
	पूर्णांक rc;

	rc = pdc_common_port_start(ap);
	अगर (rc)
		वापस rc;

	/* fix up PHYMODE4 align timing */
	अगर (ap->flags & PDC_FLAG_GEN_II) अणु
		व्योम __iomem *sata_mmio = ap->ioaddr.scr_addr;
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp = पढ़ोl(sata_mmio + PDC_PHYMODE4);
		पंचांगp = (पंचांगp & ~3) | 1;	/* set bits 1:0 = 0:1 */
		ग_लिखोl(पंचांगp, sata_mmio + PDC_PHYMODE4);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pdc_fpdma_clear_पूर्णांकerrupt_flag(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *sata_mmio = ap->ioaddr.scr_addr;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(sata_mmio + PDC_FPDMA_CTLSTAT);
	पंचांगp |= PDC_FPDMA_CTLSTAT_DMASETUP_INT_FLAG;
	पंचांगp |= PDC_FPDMA_CTLSTAT_SETDB_INT_FLAG;

	/* It's not allowed to ग_लिखो to the entire FPDMA_CTLSTAT रेजिस्टर
	   when NCQ is running. So करो a byte-sized ग_लिखो to bits 10 and 11. */
	ग_लिखोb(पंचांगp >> 8, sata_mmio + PDC_FPDMA_CTLSTAT + 1);
	पढ़ोb(sata_mmio + PDC_FPDMA_CTLSTAT + 1); /* flush */
पूर्ण

अटल व्योम pdc_fpdma_reset(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *sata_mmio = ap->ioaddr.scr_addr;
	u8 पंचांगp;

	पंचांगp = (u8)पढ़ोl(sata_mmio + PDC_FPDMA_CTLSTAT);
	पंचांगp &= 0x7F;
	पंचांगp |= PDC_FPDMA_CTLSTAT_RESET;
	ग_लिखोb(पंचांगp, sata_mmio + PDC_FPDMA_CTLSTAT);
	पढ़ोl(sata_mmio + PDC_FPDMA_CTLSTAT); /* flush */
	udelay(100);
	पंचांगp &= ~PDC_FPDMA_CTLSTAT_RESET;
	ग_लिखोb(पंचांगp, sata_mmio + PDC_FPDMA_CTLSTAT);
	पढ़ोl(sata_mmio + PDC_FPDMA_CTLSTAT); /* flush */

	pdc_fpdma_clear_पूर्णांकerrupt_flag(ap);
पूर्ण

अटल व्योम pdc_not_at_command_packet_phase(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *sata_mmio = ap->ioaddr.scr_addr;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;

	/* check not at ASIC packet command phase */
	क्रम (i = 0; i < 100; ++i) अणु
		ग_लिखोl(0, sata_mmio + PDC_INTERNAL_DEBUG_1);
		पंचांगp = पढ़ोl(sata_mmio + PDC_INTERNAL_DEBUG_2);
		अगर ((पंचांगp & 0xF) != 1)
			अवरोध;
		udelay(100);
	पूर्ण
पूर्ण

अटल व्योम pdc_clear_पूर्णांकernal_debug_record_error_रेजिस्टर(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *sata_mmio = ap->ioaddr.scr_addr;

	ग_लिखोl(0xffffffff, sata_mmio + PDC_SATA_ERROR);
	ग_लिखोl(0xffff0000, sata_mmio + PDC_LINK_LAYER_ERRORS);
पूर्ण

अटल व्योम pdc_reset_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *ata_ctlstat_mmio = ap->ioaddr.cmd_addr + PDC_CTLSTAT;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;

	अगर (ap->flags & PDC_FLAG_GEN_II)
		pdc_not_at_command_packet_phase(ap);

	पंचांगp = पढ़ोl(ata_ctlstat_mmio);
	पंचांगp |= PDC_RESET;
	ग_लिखोl(पंचांगp, ata_ctlstat_mmio);

	क्रम (i = 11; i > 0; i--) अणु
		पंचांगp = पढ़ोl(ata_ctlstat_mmio);
		अगर (पंचांगp & PDC_RESET)
			अवरोध;

		udelay(100);

		पंचांगp |= PDC_RESET;
		ग_लिखोl(पंचांगp, ata_ctlstat_mmio);
	पूर्ण

	पंचांगp &= ~PDC_RESET;
	ग_लिखोl(पंचांगp, ata_ctlstat_mmio);
	पढ़ोl(ata_ctlstat_mmio);	/* flush */

	अगर (sata_scr_valid(&ap->link) && (ap->flags & PDC_FLAG_GEN_II)) अणु
		pdc_fpdma_reset(ap);
		pdc_clear_पूर्णांकernal_debug_record_error_रेजिस्टर(ap);
	पूर्ण
पूर्ण

अटल पूर्णांक pdc_pata_cable_detect(काष्ठा ata_port *ap)
अणु
	u8 पंचांगp;
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;

	पंचांगp = पढ़ोb(ata_mmio + PDC_CTLSTAT + 3);
	अगर (पंचांगp & 0x01)
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

अटल पूर्णांक pdc_sata_scr_पढ़ो(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	*val = पढ़ोl(link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक pdc_sata_scr_ग_लिखो(काष्ठा ata_link *link,
			      अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	ग_लिखोl(val, link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल व्योम pdc_atapi_pkt(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	dma_addr_t sg_table = ap->bmdma_prd_dma;
	अचिन्हित पूर्णांक cdb_len = qc->dev->cdb_len;
	u8 *cdb = qc->cdb;
	काष्ठा pdc_port_priv *pp = ap->निजी_data;
	u8 *buf = pp->pkt;
	__le32 *buf32 = (__le32 *) buf;
	अचिन्हित पूर्णांक dev_sel, feature;

	/* set control bits (byte 0), zero delay seq id (byte 3),
	 * and seq id (byte 2)
	 */
	चयन (qc->tf.protocol) अणु
	हाल ATAPI_PROT_DMA:
		अगर (!(qc->tf.flags & ATA_TFLAG_WRITE))
			buf32[0] = cpu_to_le32(PDC_PKT_READ);
		अन्यथा
			buf32[0] = 0;
		अवरोध;
	हाल ATAPI_PROT_NODATA:
		buf32[0] = cpu_to_le32(PDC_PKT_NODATA);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
	buf32[1] = cpu_to_le32(sg_table);	/* S/G table addr */
	buf32[2] = 0;				/* no next-packet */

	/* select drive */
	अगर (sata_scr_valid(&ap->link))
		dev_sel = PDC_DEVICE_SATA;
	अन्यथा
		dev_sel = qc->tf.device;

	buf[12] = (1 << 5) | ATA_REG_DEVICE;
	buf[13] = dev_sel;
	buf[14] = (1 << 5) | ATA_REG_DEVICE | PDC_PKT_CLEAR_BSY;
	buf[15] = dev_sel; /* once more, रुकोing क्रम BSY to clear */

	buf[16] = (1 << 5) | ATA_REG_NSECT;
	buf[17] = qc->tf.nsect;
	buf[18] = (1 << 5) | ATA_REG_LBAL;
	buf[19] = qc->tf.lbal;

	/* set feature and byte counter रेजिस्टरs */
	अगर (qc->tf.protocol != ATAPI_PROT_DMA)
		feature = PDC_FEATURE_ATAPI_PIO;
	अन्यथा
		feature = PDC_FEATURE_ATAPI_DMA;

	buf[20] = (1 << 5) | ATA_REG_FEATURE;
	buf[21] = feature;
	buf[22] = (1 << 5) | ATA_REG_BYTEL;
	buf[23] = qc->tf.lbam;
	buf[24] = (1 << 5) | ATA_REG_BYTEH;
	buf[25] = qc->tf.lbah;

	/* send ATAPI packet command 0xA0 */
	buf[26] = (1 << 5) | ATA_REG_CMD;
	buf[27] = qc->tf.command;

	/* select drive and check DRQ */
	buf[28] = (1 << 5) | ATA_REG_DEVICE | PDC_PKT_WAIT_DRDY;
	buf[29] = dev_sel;

	/* we can represent cdb lengths 2/4/6/8/10/12/14/16 */
	BUG_ON(cdb_len & ~0x1E);

	/* append the CDB as the final part */
	buf[30] = (((cdb_len >> 1) & 7) << 5) | ATA_REG_DATA | PDC_LAST_REG;
	स_नकल(buf+31, cdb, cdb_len);
पूर्ण

/**
 *	pdc_fill_sg - Fill PCI IDE PRD table
 *	@qc: Metadata associated with taskfile to be transferred
 *
 *	Fill PCI IDE PRD (scatter-gather) table with segments
 *	associated with the current disk command.
 *	Make sure hardware करोes not choke on it.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 */
अटल व्योम pdc_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_bmdma_prd *prd = ap->bmdma_prd;
	काष्ठा scatterlist *sg;
	स्थिर u32 SG_COUNT_ASIC_BUG = 41*4;
	अचिन्हित पूर्णांक si, idx;
	u32 len;

	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस;

	idx = 0;
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr, offset;
		u32 sg_len;

		/* determine अगर physical DMA addr spans 64K boundary.
		 * Note h/w करोesn't support 64-bit, so we unconditionally
		 * truncate dma_addr_t to u32.
		 */
		addr = (u32) sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		जबतक (sg_len) अणु
			offset = addr & 0xffff;
			len = sg_len;
			अगर ((offset + sg_len) > 0x10000)
				len = 0x10000 - offset;

			prd[idx].addr = cpu_to_le32(addr);
			prd[idx].flags_len = cpu_to_le32(len & 0xffff);
			VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", idx, addr, len);

			idx++;
			sg_len -= len;
			addr += len;
		पूर्ण
	पूर्ण

	len = le32_to_cpu(prd[idx - 1].flags_len);

	अगर (len > SG_COUNT_ASIC_BUG) अणु
		u32 addr;

		VPRINTK("Splitting last PRD.\n");

		addr = le32_to_cpu(prd[idx - 1].addr);
		prd[idx - 1].flags_len = cpu_to_le32(len - SG_COUNT_ASIC_BUG);
		VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", idx - 1, addr, SG_COUNT_ASIC_BUG);

		addr = addr + len - SG_COUNT_ASIC_BUG;
		len = SG_COUNT_ASIC_BUG;
		prd[idx].addr = cpu_to_le32(addr);
		prd[idx].flags_len = cpu_to_le32(len);
		VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", idx, addr, len);

		idx++;
	पूर्ण

	prd[idx - 1].flags_len |= cpu_to_le32(ATA_PRD_EOT);
पूर्ण

अटल क्रमागत ata_completion_errors pdc_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा pdc_port_priv *pp = qc->ap->निजी_data;
	अचिन्हित पूर्णांक i;

	VPRINTK("ENTER\n");

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		pdc_fill_sg(qc);
		fallthrough;
	हाल ATA_PROT_NODATA:
		i = pdc_pkt_header(&qc->tf, qc->ap->bmdma_prd_dma,
				   qc->dev->devno, pp->pkt);
		अगर (qc->tf.flags & ATA_TFLAG_LBA48)
			i = pdc_prep_lba48(&qc->tf, pp->pkt, i);
		अन्यथा
			i = pdc_prep_lba28(&qc->tf, pp->pkt, i);
		pdc_pkt_footer(&qc->tf, pp->pkt, i);
		अवरोध;
	हाल ATAPI_PROT_PIO:
		pdc_fill_sg(qc);
		अवरोध;
	हाल ATAPI_PROT_DMA:
		pdc_fill_sg(qc);
		fallthrough;
	हाल ATAPI_PROT_NODATA:
		pdc_atapi_pkt(qc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस AC_ERR_OK;
पूर्ण

अटल पूर्णांक pdc_is_sataii_tx4(अचिन्हित दीर्घ flags)
अणु
	स्थिर अचिन्हित दीर्घ mask = PDC_FLAG_GEN_II | PDC_FLAG_4_PORTS;
	वापस (flags & mask) == mask;
पूर्ण

अटल अचिन्हित पूर्णांक pdc_port_no_to_ata_no(अचिन्हित पूर्णांक port_no,
					  पूर्णांक is_sataii_tx4)
अणु
	अटल स्थिर अचिन्हित अक्षर sataii_tx4_port_remap[4] = अणु 3, 1, 0, 2पूर्ण;
	वापस is_sataii_tx4 ? sataii_tx4_port_remap[port_no] : port_no;
पूर्ण

अटल अचिन्हित पूर्णांक pdc_sata_nr_ports(स्थिर काष्ठा ata_port *ap)
अणु
	वापस (ap->flags & PDC_FLAG_4_PORTS) ? 4 : 2;
पूर्ण

अटल अचिन्हित पूर्णांक pdc_sata_ata_port_to_ata_no(स्थिर काष्ठा ata_port *ap)
अणु
	स्थिर काष्ठा ata_host *host = ap->host;
	अचिन्हित पूर्णांक nr_ports = pdc_sata_nr_ports(ap);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr_ports && host->ports[i] != ap; ++i)
		;
	BUG_ON(i >= nr_ports);
	वापस pdc_port_no_to_ata_no(i, pdc_is_sataii_tx4(ap->flags));
पूर्ण

अटल व्योम pdc_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(ata_mmio + PDC_CTLSTAT);
	पंचांगp |= PDC_IRQ_DISABLE;
	पंचांगp &= ~PDC_DMA_ENABLE;
	ग_लिखोl(पंचांगp, ata_mmio + PDC_CTLSTAT);
	पढ़ोl(ata_mmio + PDC_CTLSTAT); /* flush */
पूर्ण

अटल व्योम pdc_sata_मुक्तze(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_host *host = ap->host;
	व्योम __iomem *host_mmio = host->iomap[PDC_MMIO_BAR];
	अचिन्हित पूर्णांक hotplug_offset = PDC2_SATA_PLUG_CSR;
	अचिन्हित पूर्णांक ata_no = pdc_sata_ata_port_to_ata_no(ap);
	u32 hotplug_status;

	/* Disable hotplug events on this port.
	 *
	 * Locking:
	 * 1) hotplug रेजिस्टर accesses must be serialised via host->lock
	 * 2) ap->lock == &ap->host->lock
	 * 3) ->मुक्तze() and ->thaw() are called with ap->lock held
	 */
	hotplug_status = पढ़ोl(host_mmio + hotplug_offset);
	hotplug_status |= 0x11 << (ata_no + 16);
	ग_लिखोl(hotplug_status, host_mmio + hotplug_offset);
	पढ़ोl(host_mmio + hotplug_offset); /* flush */

	pdc_मुक्तze(ap);
पूर्ण

अटल व्योम pdc_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;
	u32 पंचांगp;

	/* clear IRQ */
	पढ़ोl(ata_mmio + PDC_COMMAND);

	/* turn IRQ back on */
	पंचांगp = पढ़ोl(ata_mmio + PDC_CTLSTAT);
	पंचांगp &= ~PDC_IRQ_DISABLE;
	ग_लिखोl(पंचांगp, ata_mmio + PDC_CTLSTAT);
	पढ़ोl(ata_mmio + PDC_CTLSTAT); /* flush */
पूर्ण

अटल व्योम pdc_sata_thaw(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_host *host = ap->host;
	व्योम __iomem *host_mmio = host->iomap[PDC_MMIO_BAR];
	अचिन्हित पूर्णांक hotplug_offset = PDC2_SATA_PLUG_CSR;
	अचिन्हित पूर्णांक ata_no = pdc_sata_ata_port_to_ata_no(ap);
	u32 hotplug_status;

	pdc_thaw(ap);

	/* Enable hotplug events on this port.
	 * Locking: see pdc_sata_मुक्तze().
	 */
	hotplug_status = पढ़ोl(host_mmio + hotplug_offset);
	hotplug_status |= 0x11 << ata_no;
	hotplug_status &= ~(0x11 << (ata_no + 16));
	ग_लिखोl(hotplug_status, host_mmio + hotplug_offset);
	पढ़ोl(host_mmio + hotplug_offset); /* flush */
पूर्ण

अटल पूर्णांक pdc_pata_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline)
अणु
	pdc_reset_port(link->ap);
	वापस ata_sff_softreset(link, class, deadline);
पूर्ण

अटल अचिन्हित पूर्णांक pdc_ata_port_to_ata_no(स्थिर काष्ठा ata_port *ap)
अणु
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;
	व्योम __iomem *host_mmio = ap->host->iomap[PDC_MMIO_BAR];

	/* ata_mmio == host_mmio + 0x200 + ata_no * 0x80 */
	वापस (ata_mmio - host_mmio - 0x200) / 0x80;
पूर्ण

अटल व्योम pdc_hard_reset_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *host_mmio = ap->host->iomap[PDC_MMIO_BAR];
	व्योम __iomem *pcictl_b1_mmio = host_mmio + PDC_PCI_CTL + 1;
	अचिन्हित पूर्णांक ata_no = pdc_ata_port_to_ata_no(ap);
	काष्ठा pdc_host_priv *hpriv = ap->host->निजी_data;
	u8 पंचांगp;

	spin_lock(&hpriv->hard_reset_lock);

	पंचांगp = पढ़ोb(pcictl_b1_mmio);
	पंचांगp &= ~(0x10 << ata_no);
	ग_लिखोb(पंचांगp, pcictl_b1_mmio);
	पढ़ोb(pcictl_b1_mmio); /* flush */
	udelay(100);
	पंचांगp |= (0x10 << ata_no);
	ग_लिखोb(पंचांगp, pcictl_b1_mmio);
	पढ़ोb(pcictl_b1_mmio); /* flush */

	spin_unlock(&hpriv->hard_reset_lock);
पूर्ण

अटल पूर्णांक pdc_sata_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline)
अणु
	अगर (link->ap->flags & PDC_FLAG_GEN_II)
		pdc_not_at_command_packet_phase(link->ap);
	/* hotplug IRQs should have been masked by pdc_sata_मुक्तze() */
	pdc_hard_reset_port(link->ap);
	pdc_reset_port(link->ap);

	/* sata_promise can't reliably acquire the first D2H Reg FIS
	 * after hardreset.  Do non-रुकोing hardreset and request
	 * follow-up SRST.
	 */
	वापस sata_std_hardreset(link, class, deadline);
पूर्ण

अटल व्योम pdc_error_handler(काष्ठा ata_port *ap)
अणु
	अगर (!(ap->pflags & ATA_PFLAG_FROZEN))
		pdc_reset_port(ap);

	ata_sff_error_handler(ap);
पूर्ण

अटल व्योम pdc_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	/* make DMA engine क्रमget about the failed command */
	अगर (qc->flags & ATA_QCFLAG_FAILED)
		pdc_reset_port(ap);
पूर्ण

अटल व्योम pdc_error_पूर्णांकr(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc,
			   u32 port_status, u32 err_mask)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	अचिन्हित पूर्णांक ac_err_mask = 0;

	ata_ehi_clear_desc(ehi);
	ata_ehi_push_desc(ehi, "port_status 0x%08x", port_status);
	port_status &= err_mask;

	अगर (port_status & PDC_DRIVE_ERR)
		ac_err_mask |= AC_ERR_DEV;
	अगर (port_status & (PDC_OVERRUN_ERR | PDC_UNDERRUN_ERR))
		ac_err_mask |= AC_ERR_OTHER;
	अगर (port_status & (PDC2_ATA_HBA_ERR | PDC2_ATA_DMA_CNT_ERR))
		ac_err_mask |= AC_ERR_ATA_BUS;
	अगर (port_status & (PDC_PH_ERR | PDC_SH_ERR | PDC_DH_ERR | PDC2_HTO_ERR
			   | PDC_PCI_SYS_ERR | PDC1_PCI_PARITY_ERR))
		ac_err_mask |= AC_ERR_HOST_BUS;

	अगर (sata_scr_valid(&ap->link)) अणु
		u32 serror;

		pdc_sata_scr_पढ़ो(&ap->link, SCR_ERROR, &serror);
		ehi->serror |= serror;
	पूर्ण

	qc->err_mask |= ac_err_mask;

	pdc_reset_port(ap);

	ata_port_पात(ap);
पूर्ण

अटल अचिन्हित पूर्णांक pdc_host_पूर्णांकr(काष्ठा ata_port *ap,
				  काष्ठा ata_queued_cmd *qc)
अणु
	अचिन्हित पूर्णांक handled = 0;
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;
	u32 port_status, err_mask;

	err_mask = PDC_ERR_MASK;
	अगर (ap->flags & PDC_FLAG_GEN_II)
		err_mask &= ~PDC1_ERR_MASK;
	अन्यथा
		err_mask &= ~PDC2_ERR_MASK;
	port_status = पढ़ोl(ata_mmio + PDC_GLOBAL_CTL);
	अगर (unlikely(port_status & err_mask)) अणु
		pdc_error_पूर्णांकr(ap, qc, port_status, err_mask);
		वापस 1;
	पूर्ण

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
	हाल ATA_PROT_NODATA:
	हाल ATAPI_PROT_DMA:
	हाल ATAPI_PROT_NODATA:
		qc->err_mask |= ac_err_mask(ata_रुको_idle(ap));
		ata_qc_complete(qc);
		handled = 1;
		अवरोध;
	शेष:
		ap->stats.idle_irq++;
		अवरोध;
	पूर्ण

	वापस handled;
पूर्ण

अटल व्योम pdc_irq_clear(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;

	पढ़ोl(ata_mmio + PDC_COMMAND);
पूर्ण

अटल irqवापस_t pdc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा ata_port *ap;
	u32 mask = 0;
	अचिन्हित पूर्णांक i, पंचांगp;
	अचिन्हित पूर्णांक handled = 0;
	व्योम __iomem *host_mmio;
	अचिन्हित पूर्णांक hotplug_offset, ata_no;
	u32 hotplug_status;
	पूर्णांक is_sataii_tx4;

	VPRINTK("ENTER\n");

	अगर (!host || !host->iomap[PDC_MMIO_BAR]) अणु
		VPRINTK("QUICK EXIT\n");
		वापस IRQ_NONE;
	पूर्ण

	host_mmio = host->iomap[PDC_MMIO_BAR];

	spin_lock(&host->lock);

	/* पढ़ो and clear hotplug flags क्रम all ports */
	अगर (host->ports[0]->flags & PDC_FLAG_GEN_II) अणु
		hotplug_offset = PDC2_SATA_PLUG_CSR;
		hotplug_status = पढ़ोl(host_mmio + hotplug_offset);
		अगर (hotplug_status & 0xff)
			ग_लिखोl(hotplug_status | 0xff, host_mmio + hotplug_offset);
		hotplug_status &= 0xff;	/* clear unपूर्णांकeresting bits */
	पूर्ण अन्यथा
		hotplug_status = 0;

	/* पढ़ोing should also clear पूर्णांकerrupts */
	mask = पढ़ोl(host_mmio + PDC_INT_SEQMASK);

	अगर (mask == 0xffffffff && hotplug_status == 0) अणु
		VPRINTK("QUICK EXIT 2\n");
		जाओ करोne_irq;
	पूर्ण

	mask &= 0xffff;		/* only 16 SEQIDs possible */
	अगर (mask == 0 && hotplug_status == 0) अणु
		VPRINTK("QUICK EXIT 3\n");
		जाओ करोne_irq;
	पूर्ण

	ग_लिखोl(mask, host_mmio + PDC_INT_SEQMASK);

	is_sataii_tx4 = pdc_is_sataii_tx4(host->ports[0]->flags);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		VPRINTK("port %u\n", i);
		ap = host->ports[i];

		/* check क्रम a plug or unplug event */
		ata_no = pdc_port_no_to_ata_no(i, is_sataii_tx4);
		पंचांगp = hotplug_status & (0x11 << ata_no);
		अगर (पंचांगp) अणु
			काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
			ata_ehi_clear_desc(ehi);
			ata_ehi_hotplugged(ehi);
			ata_ehi_push_desc(ehi, "hotplug_status %#x", पंचांगp);
			ata_port_मुक्तze(ap);
			++handled;
			जारी;
		पूर्ण

		/* check क्रम a packet पूर्णांकerrupt */
		पंचांगp = mask & (1 << (i + 1));
		अगर (पंचांगp) अणु
			काष्ठा ata_queued_cmd *qc;

			qc = ata_qc_from_tag(ap, ap->link.active_tag);
			अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING)))
				handled += pdc_host_पूर्णांकr(ap, qc);
		पूर्ण
	पूर्ण

	VPRINTK("EXIT\n");

करोne_irq:
	spin_unlock(&host->lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम pdc_packet_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pdc_port_priv *pp = ap->निजी_data;
	व्योम __iomem *host_mmio = ap->host->iomap[PDC_MMIO_BAR];
	व्योम __iomem *ata_mmio = ap->ioaddr.cmd_addr;
	अचिन्हित पूर्णांक port_no = ap->port_no;
	u8 seq = (u8) (port_no + 1);

	VPRINTK("ENTER, ap %p\n", ap);

	ग_लिखोl(0x00000001, host_mmio + (seq * 4));
	पढ़ोl(host_mmio + (seq * 4));	/* flush */

	pp->pkt[2] = seq;
	wmb();			/* flush PRD, pkt ग_लिखोs */
	ग_लिखोl(pp->pkt_dma, ata_mmio + PDC_PKT_SUBMIT);
	पढ़ोl(ata_mmio + PDC_PKT_SUBMIT); /* flush */
पूर्ण

अटल अचिन्हित पूर्णांक pdc_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	चयन (qc->tf.protocol) अणु
	हाल ATAPI_PROT_NODATA:
		अगर (qc->dev->flags & ATA_DFLAG_CDB_INTR)
			अवरोध;
		fallthrough;
	हाल ATA_PROT_NODATA:
		अगर (qc->tf.flags & ATA_TFLAG_POLLING)
			अवरोध;
		fallthrough;
	हाल ATAPI_PROT_DMA:
	हाल ATA_PROT_DMA:
		pdc_packet_start(qc);
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल व्योम pdc_tf_load_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	WARN_ON(tf->protocol == ATA_PROT_DMA || tf->protocol == ATAPI_PROT_DMA);
	ata_sff_tf_load(ap, tf);
पूर्ण

अटल व्योम pdc_exec_command_mmio(काष्ठा ata_port *ap,
				  स्थिर काष्ठा ata_taskfile *tf)
अणु
	WARN_ON(tf->protocol == ATA_PROT_DMA || tf->protocol == ATAPI_PROT_DMA);
	ata_sff_exec_command(ap, tf);
पूर्ण

अटल पूर्णांक pdc_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	u8 *scsicmd = qc->scsicmd->cmnd;
	पूर्णांक pio = 1; /* atapi dma off by शेष */

	/* Whitelist commands that may use DMA. */
	चयन (scsicmd[0]) अणु
	हाल WRITE_12:
	हाल WRITE_10:
	हाल WRITE_6:
	हाल READ_12:
	हाल READ_10:
	हाल READ_6:
	हाल 0xad: /* READ_DVD_STRUCTURE */
	हाल 0xbe: /* READ_CD */
		pio = 0;
	पूर्ण
	/* -45150 (FFFF4FA2) to -1 (FFFFFFFF) shall use PIO mode */
	अगर (scsicmd[0] == WRITE_10) अणु
		अचिन्हित पूर्णांक lba =
			(scsicmd[2] << 24) |
			(scsicmd[3] << 16) |
			(scsicmd[4] << 8) |
			scsicmd[5];
		अगर (lba >= 0xFFFF4FA2)
			pio = 1;
	पूर्ण
	वापस pio;
पूर्ण

अटल पूर्णांक pdc_old_sata_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	/* First generation chips cannot use ATAPI DMA on SATA ports */
	वापस 1;
पूर्ण

अटल व्योम pdc_ata_setup_port(काष्ठा ata_port *ap,
			       व्योम __iomem *base, व्योम __iomem *scr_addr)
अणु
	ap->ioaddr.cmd_addr		= base;
	ap->ioaddr.data_addr		= base;
	ap->ioaddr.feature_addr		=
	ap->ioaddr.error_addr		= base + 0x4;
	ap->ioaddr.nsect_addr		= base + 0x8;
	ap->ioaddr.lbal_addr		= base + 0xc;
	ap->ioaddr.lbam_addr		= base + 0x10;
	ap->ioaddr.lbah_addr		= base + 0x14;
	ap->ioaddr.device_addr		= base + 0x18;
	ap->ioaddr.command_addr		=
	ap->ioaddr.status_addr		= base + 0x1c;
	ap->ioaddr.altstatus_addr	=
	ap->ioaddr.ctl_addr		= base + 0x38;
	ap->ioaddr.scr_addr		= scr_addr;
पूर्ण

अटल व्योम pdc_host_init(काष्ठा ata_host *host)
अणु
	व्योम __iomem *host_mmio = host->iomap[PDC_MMIO_BAR];
	पूर्णांक is_gen2 = host->ports[0]->flags & PDC_FLAG_GEN_II;
	पूर्णांक hotplug_offset;
	u32 पंचांगp;

	अगर (is_gen2)
		hotplug_offset = PDC2_SATA_PLUG_CSR;
	अन्यथा
		hotplug_offset = PDC_SATA_PLUG_CSR;

	/*
	 * Except क्रम the hotplug stuff, this is vooकरोo from the
	 * Promise driver.  Label this entire section
	 * "TODO: figure out why we do this"
	 */

	/* enable BMR_BURST, maybe change FIFO_SHD to 8 dwords */
	पंचांगp = पढ़ोl(host_mmio + PDC_FLASH_CTL);
	पंचांगp |= 0x02000;	/* bit 13 (enable bmr burst) */
	अगर (!is_gen2)
		पंचांगp |= 0x10000;	/* bit 16 (fअगरo threshold at 8 dw) */
	ग_लिखोl(पंचांगp, host_mmio + PDC_FLASH_CTL);

	/* clear plug/unplug flags क्रम all ports */
	पंचांगp = पढ़ोl(host_mmio + hotplug_offset);
	ग_लिखोl(पंचांगp | 0xff, host_mmio + hotplug_offset);

	पंचांगp = पढ़ोl(host_mmio + hotplug_offset);
	अगर (is_gen2)	/* unmask plug/unplug पूर्णांकs */
		ग_लिखोl(पंचांगp & ~0xff0000, host_mmio + hotplug_offset);
	अन्यथा		/* mask plug/unplug पूर्णांकs */
		ग_लिखोl(पंचांगp | 0xff0000, host_mmio + hotplug_offset);

	/* करोn't initialise TBG or SLEW on 2nd generation chips */
	अगर (is_gen2)
		वापस;

	/* reduce TBG घड़ी to 133 Mhz. */
	पंचांगp = पढ़ोl(host_mmio + PDC_TBG_MODE);
	पंचांगp &= ~0x30000; /* clear bit 17, 16*/
	पंचांगp |= 0x10000;  /* set bit 17:16 = 0:1 */
	ग_लिखोl(पंचांगp, host_mmio + PDC_TBG_MODE);

	पढ़ोl(host_mmio + PDC_TBG_MODE);	/* flush */
	msleep(10);

	/* adjust slew rate control रेजिस्टर. */
	पंचांगp = पढ़ोl(host_mmio + PDC_SLEW_CTL);
	पंचांगp &= 0xFFFFF03F; /* clear bit 11 ~ 6 */
	पंचांगp  |= 0x00000900; /* set bit 11-9 = 100b , bit 8-6 = 100 */
	ग_लिखोl(पंचांगp, host_mmio + PDC_SLEW_CTL);
पूर्ण

अटल पूर्णांक pdc_ata_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *pi = &pdc_port_info[ent->driver_data];
	स्थिर काष्ठा ata_port_info *ppi[PDC_MAX_PORTS];
	काष्ठा ata_host *host;
	काष्ठा pdc_host_priv *hpriv;
	व्योम __iomem *host_mmio;
	पूर्णांक n_ports, i, rc;
	पूर्णांक is_sataii_tx4;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* enable and acquire resources */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, 1 << PDC_MMIO_BAR, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host_mmio = pcim_iomap_table(pdev)[PDC_MMIO_BAR];

	/* determine port configuration and setup host */
	n_ports = 2;
	अगर (pi->flags & PDC_FLAG_4_PORTS)
		n_ports = 4;
	क्रम (i = 0; i < n_ports; i++)
		ppi[i] = pi;

	अगर (pi->flags & PDC_FLAG_SATA_PATA) अणु
		u8 पंचांगp = पढ़ोb(host_mmio + PDC_FLASH_CTL + 1);
		अगर (!(पंचांगp & 0x80))
			ppi[n_ports++] = pi + 1;
	पूर्ण

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	अगर (!host) अणु
		dev_err(&pdev->dev, "failed to allocate host\n");
		वापस -ENOMEM;
	पूर्ण
	hpriv = devm_kzalloc(&pdev->dev, माप *hpriv, GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;
	spin_lock_init(&hpriv->hard_reset_lock);
	host->निजी_data = hpriv;
	host->iomap = pcim_iomap_table(pdev);

	is_sataii_tx4 = pdc_is_sataii_tx4(pi->flags);
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		अचिन्हित पूर्णांक ata_no = pdc_port_no_to_ata_no(i, is_sataii_tx4);
		अचिन्हित पूर्णांक ata_offset = 0x200 + ata_no * 0x80;
		अचिन्हित पूर्णांक scr_offset = 0x400 + ata_no * 0x100;

		pdc_ata_setup_port(ap, host_mmio + ata_offset, host_mmio + scr_offset);

		ata_port_pbar_desc(ap, PDC_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, PDC_MMIO_BAR, ata_offset, "ata");
	पूर्ण

	/* initialize adapter */
	pdc_host_init(host);

	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;

	/* start host, request IRQ and attach */
	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, pdc_पूर्णांकerrupt, IRQF_SHARED,
				 &pdc_ata_sht);
पूर्ण

module_pci_driver(pdc_ata_pci_driver);

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("Promise ATA TX2/TX4/TX4000 low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pdc_ata_pci_tbl);
MODULE_VERSION(DRV_VERSION);
