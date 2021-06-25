<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_sx4.c - Promise SATA
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *  		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2003-2004 Red Hat, Inc.
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available under NDA.
 */

/*
	Theory of operation
	-------------------

	The SX4 (PDC20621) chip features a single Host DMA (HDMA) copy
	engine, DIMM memory, and four ATA engines (one per SATA port).
	Data is copied to/from DIMM memory by the HDMA engine, beक्रमe
	handing off to one (or more) of the ATA engines.  The ATA
	engines operate solely on DIMM memory.

	The SX4 behaves like a PATA chip, with no SATA controls or
	knowledge whatsoever, leading to the presumption that
	PATA<->SATA bridges exist on SX4 boards, बाह्यal to the
	PDC20621 chip itself.

	The chip is quite capable, supporting an XOR engine and linked
	hardware commands (permits a string to transactions to be
	submitted and रुकोed-on as a single unit), and an optional
	microprocessor.

	The limiting factor is largely software.  This Linux driver was
	written to multiplex the single HDMA engine to copy disk
	transactions पूर्णांकo a fixed DIMM memory space, from where an ATA
	engine takes over.  As a result, each WRITE looks like this:

		submit HDMA packet to hardware
		hardware copies data from प्रणाली memory to DIMM
		hardware उठाओs पूर्णांकerrupt

		submit ATA packet to hardware
		hardware executes ATA WRITE command, w/ data in DIMM
		hardware उठाओs पूर्णांकerrupt

	and each READ looks like this:

		submit ATA packet to hardware
		hardware executes ATA READ command, w/ data in DIMM
		hardware उठाओs पूर्णांकerrupt

		submit HDMA packet to hardware
		hardware copies data from DIMM to प्रणाली memory
		hardware उठाओs पूर्णांकerrupt

	This is a very slow, lock-step way of करोing things that can
	certainly be improved by motivated kernel hackers.

 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>
#समावेश "sata_promise.h"

#घोषणा DRV_NAME	"sata_sx4"
#घोषणा DRV_VERSION	"0.12"


क्रमागत अणु
	PDC_MMIO_BAR		= 3,
	PDC_DIMM_BAR		= 4,

	PDC_PRD_TBL		= 0x44,	/* Direct command DMA table addr */

	PDC_PKT_SUBMIT		= 0x40, /* Command packet poपूर्णांकer addr */
	PDC_HDMA_PKT_SUBMIT	= 0x100, /* Host DMA packet poपूर्णांकer addr */
	PDC_INT_SEQMASK		= 0x40,	/* Mask of निश्चितed SEQ INTs */
	PDC_HDMA_CTLSTAT	= 0x12C, /* Host DMA control / status */

	PDC_CTLSTAT		= 0x60,	/* IDEn control / status */

	PDC_20621_SEQCTL	= 0x400,
	PDC_20621_SEQMASK	= 0x480,
	PDC_20621_GENERAL_CTL	= 0x484,
	PDC_20621_PAGE_SIZE	= (32 * 1024),

	/* chosen, not स्थिरant, values; we design our own DIMM mem map */
	PDC_20621_DIMM_WINDOW	= 0x0C,	/* page# क्रम 32K DIMM winकरोw */
	PDC_20621_DIMM_BASE	= 0x00200000,
	PDC_20621_DIMM_DATA	= (64 * 1024),
	PDC_DIMM_DATA_STEP	= (256 * 1024),
	PDC_DIMM_WINDOW_STEP	= (8 * 1024),
	PDC_DIMM_HOST_PRD	= (6 * 1024),
	PDC_DIMM_HOST_PKT	= (128 * 0),
	PDC_DIMM_HPKT_PRD	= (128 * 1),
	PDC_DIMM_ATA_PKT	= (128 * 2),
	PDC_DIMM_APKT_PRD	= (128 * 3),
	PDC_DIMM_HEADER_SZ	= PDC_DIMM_APKT_PRD + 128,
	PDC_PAGE_WINDOW		= 0x40,
	PDC_PAGE_DATA		= PDC_PAGE_WINDOW +
				  (PDC_20621_DIMM_DATA / PDC_20621_PAGE_SIZE),
	PDC_PAGE_SET		= PDC_DIMM_DATA_STEP / PDC_20621_PAGE_SIZE,

	PDC_CHIP0_OFS		= 0xC0000, /* offset of chip #0 */

	PDC_20621_ERR_MASK	= (1<<19) | (1<<20) | (1<<21) | (1<<22) |
				  (1<<23),

	board_20621		= 0,	/* FastTrak S150 SX4 */

	PDC_MASK_INT		= (1 << 10), /* HDMA/ATA mask पूर्णांक */
	PDC_RESET		= (1 << 11), /* HDMA/ATA reset */
	PDC_DMA_ENABLE		= (1 << 7),  /* DMA start/stop */

	PDC_MAX_HDMA		= 32,
	PDC_HDMA_Q_MASK		= (PDC_MAX_HDMA - 1),

	PDC_DIMM0_SPD_DEV_ADDRESS	= 0x50,
	PDC_DIMM1_SPD_DEV_ADDRESS	= 0x51,
	PDC_I2C_CONTROL			= 0x48,
	PDC_I2C_ADDR_DATA		= 0x4C,
	PDC_DIMM0_CONTROL		= 0x80,
	PDC_DIMM1_CONTROL		= 0x84,
	PDC_SDRAM_CONTROL		= 0x88,
	PDC_I2C_WRITE			= 0,		/* master -> slave */
	PDC_I2C_READ			= (1 << 6),	/* master <- slave */
	PDC_I2C_START			= (1 << 7),	/* start I2C proto */
	PDC_I2C_MASK_INT		= (1 << 5),	/* mask I2C पूर्णांकerrupt */
	PDC_I2C_COMPLETE		= (1 << 16),	/* I2C normal compl. */
	PDC_I2C_NO_ACK			= (1 << 20),	/* slave no-ack addr */
	PDC_DIMM_SPD_SUBADDRESS_START	= 0x00,
	PDC_DIMM_SPD_SUBADDRESS_END	= 0x7F,
	PDC_DIMM_SPD_ROW_NUM		= 3,
	PDC_DIMM_SPD_COLUMN_NUM		= 4,
	PDC_DIMM_SPD_MODULE_ROW		= 5,
	PDC_DIMM_SPD_TYPE		= 11,
	PDC_DIMM_SPD_FRESH_RATE		= 12,
	PDC_DIMM_SPD_BANK_NUM		= 17,
	PDC_DIMM_SPD_CAS_LATENCY	= 18,
	PDC_DIMM_SPD_ATTRIBUTE		= 21,
	PDC_DIMM_SPD_ROW_PRE_CHARGE	= 27,
	PDC_DIMM_SPD_ROW_ACTIVE_DELAY	= 28,
	PDC_DIMM_SPD_RAS_CAS_DELAY	= 29,
	PDC_DIMM_SPD_ACTIVE_PRECHARGE	= 30,
	PDC_DIMM_SPD_SYSTEM_FREQ	= 126,
	PDC_CTL_STATUS			= 0x08,
	PDC_DIMM_WINDOW_CTLR		= 0x0C,
	PDC_TIME_CONTROL		= 0x3C,
	PDC_TIME_PERIOD			= 0x40,
	PDC_TIME_COUNTER		= 0x44,
	PDC_GENERAL_CTLR		= 0x484,
	PCI_PLL_INIT			= 0x8A531824,
	PCI_X_TCOUNT			= 0xEE1E5CFF,

	/* PDC_TIME_CONTROL bits */
	PDC_TIMER_BUZZER		= (1 << 10),
	PDC_TIMER_MODE_PERIODIC		= 0,		/* bits 9:8 == 00 */
	PDC_TIMER_MODE_ONCE		= (1 << 8),	/* bits 9:8 == 01 */
	PDC_TIMER_ENABLE		= (1 << 7),
	PDC_TIMER_MASK_INT		= (1 << 5),
	PDC_TIMER_SEQ_MASK		= 0x1f,		/* SEQ ID क्रम समयr */
	PDC_TIMER_DEFAULT		= PDC_TIMER_MODE_ONCE |
					  PDC_TIMER_ENABLE |
					  PDC_TIMER_MASK_INT,
पूर्ण;

#घोषणा ECC_ERASE_BUF_SZ (128 * 1024)

काष्ठा pdc_port_priv अणु
	u8			dimm_buf[(ATA_PRD_SZ * ATA_MAX_PRD) + 512];
	u8			*pkt;
	dma_addr_t		pkt_dma;
पूर्ण;

काष्ठा pdc_host_priv अणु
	अचिन्हित पूर्णांक		करोing_hdma;
	अचिन्हित पूर्णांक		hdma_prod;
	अचिन्हित पूर्णांक		hdma_cons;
	काष्ठा अणु
		काष्ठा ata_queued_cmd *qc;
		अचिन्हित पूर्णांक	seq;
		अचिन्हित दीर्घ	pkt_ofs;
	पूर्ण hdma[32];
पूर्ण;


अटल पूर्णांक pdc_sata_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम pdc_error_handler(काष्ठा ata_port *ap);
अटल व्योम pdc_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम pdc_thaw(काष्ठा ata_port *ap);
अटल पूर्णांक pdc_port_start(काष्ठा ata_port *ap);
अटल क्रमागत ata_completion_errors pdc20621_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल व्योम pdc_tf_load_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
अटल व्योम pdc_exec_command_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
अटल अचिन्हित पूर्णांक pdc20621_dimm_init(काष्ठा ata_host *host);
अटल पूर्णांक pdc20621_detect_dimm(काष्ठा ata_host *host);
अटल अचिन्हित पूर्णांक pdc20621_i2c_पढ़ो(काष्ठा ata_host *host,
				      u32 device, u32 subaddr, u32 *pdata);
अटल पूर्णांक pdc20621_prog_dimm0(काष्ठा ata_host *host);
अटल अचिन्हित पूर्णांक pdc20621_prog_dimm_global(काष्ठा ata_host *host);
#अगर_घोषित ATA_VERBOSE_DEBUG
अटल व्योम pdc20621_get_from_dimm(काष्ठा ata_host *host,
				   व्योम *psource, u32 offset, u32 size);
#पूर्ण_अगर
अटल व्योम pdc20621_put_to_dimm(काष्ठा ata_host *host,
				 व्योम *psource, u32 offset, u32 size);
अटल व्योम pdc20621_irq_clear(काष्ठा ata_port *ap);
अटल अचिन्हित पूर्णांक pdc20621_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक pdc_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			 अचिन्हित दीर्घ deadline);
अटल व्योम pdc_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक pdc_check_atapi_dma(काष्ठा ata_queued_cmd *qc);


अटल काष्ठा scsi_host_ढाँचा pdc_sata_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= LIBATA_MAX_PRD,
	.dma_boundary		= ATA_DMA_BOUNDARY,
पूर्ण;

/* TODO: inherit from base port_ops after converting to new EH */
अटल काष्ठा ata_port_operations pdc_20621_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.check_atapi_dma	= pdc_check_atapi_dma,
	.qc_prep		= pdc20621_qc_prep,
	.qc_issue		= pdc20621_qc_issue,

	.मुक्तze			= pdc_मुक्तze,
	.thaw			= pdc_thaw,
	.softreset		= pdc_softreset,
	.error_handler		= pdc_error_handler,
	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,
	.post_पूर्णांकernal_cmd	= pdc_post_पूर्णांकernal_cmd,

	.port_start		= pdc_port_start,

	.sff_tf_load		= pdc_tf_load_mmio,
	.sff_exec_command	= pdc_exec_command_mmio,
	.sff_irq_clear		= pdc20621_irq_clear,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info pdc_port_info[] = अणु
	/* board_20621 */
	अणु
		.flags		= ATA_FLAG_SATA | ATA_FLAG_NO_ATAPI |
				  ATA_FLAG_PIO_POLLING,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &pdc_20621_ops,
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा pci_device_id pdc_sata_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PROMISE, 0x6622), board_20621 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver pdc_sata_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= pdc_sata_pci_tbl,
	.probe			= pdc_sata_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;


अटल पूर्णांक pdc_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा pdc_port_priv *pp;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	pp->pkt = dmam_alloc_coherent(dev, 128, &pp->pkt_dma, GFP_KERNEL);
	अगर (!pp->pkt)
		वापस -ENOMEM;

	ap->निजी_data = pp;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pdc20621_ata_sg(u8 *buf, अचिन्हित पूर्णांक portno,
				   अचिन्हित पूर्णांक total_len)
अणु
	u32 addr;
	अचिन्हित पूर्णांक dw = PDC_DIMM_APKT_PRD >> 2;
	__le32 *buf32 = (__le32 *) buf;

	/* output ATA packet S/G table */
	addr = PDC_20621_DIMM_BASE + PDC_20621_DIMM_DATA +
	       (PDC_DIMM_DATA_STEP * portno);
	VPRINTK("ATA sg addr 0x%x, %d\n", addr, addr);
	buf32[dw] = cpu_to_le32(addr);
	buf32[dw + 1] = cpu_to_le32(total_len | ATA_PRD_EOT);

	VPRINTK("ATA PSG @ %x == (0x%x, 0x%x)\n",
		PDC_20621_DIMM_BASE +
		       (PDC_DIMM_WINDOW_STEP * portno) +
		       PDC_DIMM_APKT_PRD,
		buf32[dw], buf32[dw + 1]);
पूर्ण

अटल अंतरभूत व्योम pdc20621_host_sg(u8 *buf, अचिन्हित पूर्णांक portno,
				    अचिन्हित पूर्णांक total_len)
अणु
	u32 addr;
	अचिन्हित पूर्णांक dw = PDC_DIMM_HPKT_PRD >> 2;
	__le32 *buf32 = (__le32 *) buf;

	/* output Host DMA packet S/G table */
	addr = PDC_20621_DIMM_BASE + PDC_20621_DIMM_DATA +
	       (PDC_DIMM_DATA_STEP * portno);

	buf32[dw] = cpu_to_le32(addr);
	buf32[dw + 1] = cpu_to_le32(total_len | ATA_PRD_EOT);

	VPRINTK("HOST PSG @ %x == (0x%x, 0x%x)\n",
		PDC_20621_DIMM_BASE +
		       (PDC_DIMM_WINDOW_STEP * portno) +
		       PDC_DIMM_HPKT_PRD,
		buf32[dw], buf32[dw + 1]);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pdc20621_ata_pkt(काष्ठा ata_taskfile *tf,
					    अचिन्हित पूर्णांक devno, u8 *buf,
					    अचिन्हित पूर्णांक portno)
अणु
	अचिन्हित पूर्णांक i, dw;
	__le32 *buf32 = (__le32 *) buf;
	u8 dev_reg;

	अचिन्हित पूर्णांक dimm_sg = PDC_20621_DIMM_BASE +
			       (PDC_DIMM_WINDOW_STEP * portno) +
			       PDC_DIMM_APKT_PRD;
	VPRINTK("ENTER, dimm_sg == 0x%x, %d\n", dimm_sg, dimm_sg);

	i = PDC_DIMM_ATA_PKT;

	/*
	 * Set up ATA packet
	 */
	अगर ((tf->protocol == ATA_PROT_DMA) && (!(tf->flags & ATA_TFLAG_WRITE)))
		buf[i++] = PDC_PKT_READ;
	अन्यथा अगर (tf->protocol == ATA_PROT_NODATA)
		buf[i++] = PDC_PKT_NODATA;
	अन्यथा
		buf[i++] = 0;
	buf[i++] = 0;			/* reserved */
	buf[i++] = portno + 1;		/* seq. id */
	buf[i++] = 0xff;		/* delay seq. id */

	/* dimm dma S/G, and next-pkt */
	dw = i >> 2;
	अगर (tf->protocol == ATA_PROT_NODATA)
		buf32[dw] = 0;
	अन्यथा
		buf32[dw] = cpu_to_le32(dimm_sg);
	buf32[dw + 1] = 0;
	i += 8;

	अगर (devno == 0)
		dev_reg = ATA_DEVICE_OBS;
	अन्यथा
		dev_reg = ATA_DEVICE_OBS | ATA_DEV1;

	/* select device */
	buf[i++] = (1 << 5) | PDC_PKT_CLEAR_BSY | ATA_REG_DEVICE;
	buf[i++] = dev_reg;

	/* device control रेजिस्टर */
	buf[i++] = (1 << 5) | PDC_REG_DEVCTL;
	buf[i++] = tf->ctl;

	वापस i;
पूर्ण

अटल अंतरभूत व्योम pdc20621_host_pkt(काष्ठा ata_taskfile *tf, u8 *buf,
				     अचिन्हित पूर्णांक portno)
अणु
	अचिन्हित पूर्णांक dw;
	u32 पंचांगp;
	__le32 *buf32 = (__le32 *) buf;

	अचिन्हित पूर्णांक host_sg = PDC_20621_DIMM_BASE +
			       (PDC_DIMM_WINDOW_STEP * portno) +
			       PDC_DIMM_HOST_PRD;
	अचिन्हित पूर्णांक dimm_sg = PDC_20621_DIMM_BASE +
			       (PDC_DIMM_WINDOW_STEP * portno) +
			       PDC_DIMM_HPKT_PRD;
	VPRINTK("ENTER, dimm_sg == 0x%x, %d\n", dimm_sg, dimm_sg);
	VPRINTK("host_sg == 0x%x, %d\n", host_sg, host_sg);

	dw = PDC_DIMM_HOST_PKT >> 2;

	/*
	 * Set up Host DMA packet
	 */
	अगर ((tf->protocol == ATA_PROT_DMA) && (!(tf->flags & ATA_TFLAG_WRITE)))
		पंचांगp = PDC_PKT_READ;
	अन्यथा
		पंचांगp = 0;
	पंचांगp |= ((portno + 1 + 4) << 16);	/* seq. id */
	पंचांगp |= (0xff << 24);			/* delay seq. id */
	buf32[dw + 0] = cpu_to_le32(पंचांगp);
	buf32[dw + 1] = cpu_to_le32(host_sg);
	buf32[dw + 2] = cpu_to_le32(dimm_sg);
	buf32[dw + 3] = 0;

	VPRINTK("HOST PKT @ %x == (0x%x 0x%x 0x%x 0x%x)\n",
		PDC_20621_DIMM_BASE + (PDC_DIMM_WINDOW_STEP * portno) +
			PDC_DIMM_HOST_PKT,
		buf32[dw + 0],
		buf32[dw + 1],
		buf32[dw + 2],
		buf32[dw + 3]);
पूर्ण

अटल व्योम pdc20621_dma_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pdc_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = ap->host->iomap[PDC_MMIO_BAR];
	व्योम __iomem *dimm_mmio = ap->host->iomap[PDC_DIMM_BAR];
	अचिन्हित पूर्णांक portno = ap->port_no;
	अचिन्हित पूर्णांक i, si, idx, total_len = 0, sgt_len;
	__le32 *buf = (__le32 *) &pp->dimm_buf[PDC_DIMM_HEADER_SZ];

	WARN_ON(!(qc->flags & ATA_QCFLAG_DMAMAP));

	VPRINTK("ata%u: ENTER\n", ap->prपूर्णांक_id);

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	/*
	 * Build S/G table
	 */
	idx = 0;
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		buf[idx++] = cpu_to_le32(sg_dma_address(sg));
		buf[idx++] = cpu_to_le32(sg_dma_len(sg));
		total_len += sg_dma_len(sg);
	पूर्ण
	buf[idx - 1] |= cpu_to_le32(ATA_PRD_EOT);
	sgt_len = idx * 4;

	/*
	 * Build ATA, host DMA packets
	 */
	pdc20621_host_sg(&pp->dimm_buf[0], portno, total_len);
	pdc20621_host_pkt(&qc->tf, &pp->dimm_buf[0], portno);

	pdc20621_ata_sg(&pp->dimm_buf[0], portno, total_len);
	i = pdc20621_ata_pkt(&qc->tf, qc->dev->devno, &pp->dimm_buf[0], portno);

	अगर (qc->tf.flags & ATA_TFLAG_LBA48)
		i = pdc_prep_lba48(&qc->tf, &pp->dimm_buf[0], i);
	अन्यथा
		i = pdc_prep_lba28(&qc->tf, &pp->dimm_buf[0], i);

	pdc_pkt_footer(&qc->tf, &pp->dimm_buf[0], i);

	/* copy three S/G tables and two packets to DIMM MMIO winकरोw */
	स_नकल_toio(dimm_mmio + (portno * PDC_DIMM_WINDOW_STEP),
		    &pp->dimm_buf, PDC_DIMM_HEADER_SZ);
	स_नकल_toio(dimm_mmio + (portno * PDC_DIMM_WINDOW_STEP) +
		    PDC_DIMM_HOST_PRD,
		    &pp->dimm_buf[PDC_DIMM_HEADER_SZ], sgt_len);

	/* क्रमce host FIFO dump */
	ग_लिखोl(0x00000001, mmio + PDC_20621_GENERAL_CTL);

	पढ़ोl(dimm_mmio);	/* MMIO PCI posting flush */

	VPRINTK("ata pkt buf ofs %u, prd size %u, mmio copied\n", i, sgt_len);
पूर्ण

अटल व्योम pdc20621_nodata_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pdc_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = ap->host->iomap[PDC_MMIO_BAR];
	व्योम __iomem *dimm_mmio = ap->host->iomap[PDC_DIMM_BAR];
	अचिन्हित पूर्णांक portno = ap->port_no;
	अचिन्हित पूर्णांक i;

	VPRINTK("ata%u: ENTER\n", ap->prपूर्णांक_id);

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	i = pdc20621_ata_pkt(&qc->tf, qc->dev->devno, &pp->dimm_buf[0], portno);

	अगर (qc->tf.flags & ATA_TFLAG_LBA48)
		i = pdc_prep_lba48(&qc->tf, &pp->dimm_buf[0], i);
	अन्यथा
		i = pdc_prep_lba28(&qc->tf, &pp->dimm_buf[0], i);

	pdc_pkt_footer(&qc->tf, &pp->dimm_buf[0], i);

	/* copy three S/G tables and two packets to DIMM MMIO winकरोw */
	स_नकल_toio(dimm_mmio + (portno * PDC_DIMM_WINDOW_STEP),
		    &pp->dimm_buf, PDC_DIMM_HEADER_SZ);

	/* क्रमce host FIFO dump */
	ग_लिखोl(0x00000001, mmio + PDC_20621_GENERAL_CTL);

	पढ़ोl(dimm_mmio);	/* MMIO PCI posting flush */

	VPRINTK("ata pkt buf ofs %u, mmio copied\n", i);
पूर्ण

अटल क्रमागत ata_completion_errors pdc20621_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		pdc20621_dma_prep(qc);
		अवरोध;
	हाल ATA_PROT_NODATA:
		pdc20621_nodata_prep(qc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस AC_ERR_OK;
पूर्ण

अटल व्योम __pdc20621_push_hdma(काष्ठा ata_queued_cmd *qc,
				 अचिन्हित पूर्णांक seq,
				 u32 pkt_ofs)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_host *host = ap->host;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	ग_लिखोl(0x00000001, mmio + PDC_20621_SEQCTL + (seq * 4));
	पढ़ोl(mmio + PDC_20621_SEQCTL + (seq * 4));	/* flush */

	ग_लिखोl(pkt_ofs, mmio + PDC_HDMA_PKT_SUBMIT);
	पढ़ोl(mmio + PDC_HDMA_PKT_SUBMIT);	/* flush */
पूर्ण

अटल व्योम pdc20621_push_hdma(काष्ठा ata_queued_cmd *qc,
				अचिन्हित पूर्णांक seq,
				u32 pkt_ofs)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pdc_host_priv *pp = ap->host->निजी_data;
	अचिन्हित पूर्णांक idx = pp->hdma_prod & PDC_HDMA_Q_MASK;

	अगर (!pp->करोing_hdma) अणु
		__pdc20621_push_hdma(qc, seq, pkt_ofs);
		pp->करोing_hdma = 1;
		वापस;
	पूर्ण

	pp->hdma[idx].qc = qc;
	pp->hdma[idx].seq = seq;
	pp->hdma[idx].pkt_ofs = pkt_ofs;
	pp->hdma_prod++;
पूर्ण

अटल व्योम pdc20621_pop_hdma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pdc_host_priv *pp = ap->host->निजी_data;
	अचिन्हित पूर्णांक idx = pp->hdma_cons & PDC_HDMA_Q_MASK;

	/* अगर nothing on queue, we're करोne */
	अगर (pp->hdma_prod == pp->hdma_cons) अणु
		pp->करोing_hdma = 0;
		वापस;
	पूर्ण

	__pdc20621_push_hdma(pp->hdma[idx].qc, pp->hdma[idx].seq,
			     pp->hdma[idx].pkt_ofs);
	pp->hdma_cons++;
पूर्ण

#अगर_घोषित ATA_VERBOSE_DEBUG
अटल व्योम pdc20621_dump_hdma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित पूर्णांक port_no = ap->port_no;
	व्योम __iomem *dimm_mmio = ap->host->iomap[PDC_DIMM_BAR];

	dimm_mmio += (port_no * PDC_DIMM_WINDOW_STEP);
	dimm_mmio += PDC_DIMM_HOST_PKT;

	prपूर्णांकk(KERN_ERR "HDMA[0] == 0x%08X\n", पढ़ोl(dimm_mmio));
	prपूर्णांकk(KERN_ERR "HDMA[1] == 0x%08X\n", पढ़ोl(dimm_mmio + 4));
	prपूर्णांकk(KERN_ERR "HDMA[2] == 0x%08X\n", पढ़ोl(dimm_mmio + 8));
	prपूर्णांकk(KERN_ERR "HDMA[3] == 0x%08X\n", पढ़ोl(dimm_mmio + 12));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pdc20621_dump_hdma(काष्ठा ata_queued_cmd *qc) अणु पूर्ण
#पूर्ण_अगर /* ATA_VERBOSE_DEBUG */

अटल व्योम pdc20621_packet_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_host *host = ap->host;
	अचिन्हित पूर्णांक port_no = ap->port_no;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];
	अचिन्हित पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	u8 seq = (u8) (port_no + 1);
	अचिन्हित पूर्णांक port_ofs;

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	VPRINTK("ata%u: ENTER\n", ap->prपूर्णांक_id);

	wmb();			/* flush PRD, pkt ग_लिखोs */

	port_ofs = PDC_20621_DIMM_BASE + (PDC_DIMM_WINDOW_STEP * port_no);

	/* अगर writing, we (1) DMA to DIMM, then (2) करो ATA command */
	अगर (rw && qc->tf.protocol == ATA_PROT_DMA) अणु
		seq += 4;

		pdc20621_dump_hdma(qc);
		pdc20621_push_hdma(qc, seq, port_ofs + PDC_DIMM_HOST_PKT);
		VPRINTK("queued ofs 0x%x (%u), seq %u\n",
			port_ofs + PDC_DIMM_HOST_PKT,
			port_ofs + PDC_DIMM_HOST_PKT,
			seq);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x00000001, mmio + PDC_20621_SEQCTL + (seq * 4));
		पढ़ोl(mmio + PDC_20621_SEQCTL + (seq * 4));	/* flush */

		ग_लिखोl(port_ofs + PDC_DIMM_ATA_PKT,
		       ap->ioaddr.cmd_addr + PDC_PKT_SUBMIT);
		पढ़ोl(ap->ioaddr.cmd_addr + PDC_PKT_SUBMIT);
		VPRINTK("submitted ofs 0x%x (%u), seq %u\n",
			port_ofs + PDC_DIMM_ATA_PKT,
			port_ofs + PDC_DIMM_ATA_PKT,
			seq);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक pdc20621_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_NODATA:
		अगर (qc->tf.flags & ATA_TFLAG_POLLING)
			अवरोध;
		fallthrough;
	हाल ATA_PROT_DMA:
		pdc20621_packet_start(qc);
		वापस 0;

	हाल ATAPI_PROT_DMA:
		BUG();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pdc20621_host_पूर्णांकr(काष्ठा ata_port *ap,
					  काष्ठा ata_queued_cmd *qc,
					  अचिन्हित पूर्णांक करोing_hdma,
					  व्योम __iomem *mmio)
अणु
	अचिन्हित पूर्णांक port_no = ap->port_no;
	अचिन्हित पूर्णांक port_ofs =
		PDC_20621_DIMM_BASE + (PDC_DIMM_WINDOW_STEP * port_no);
	u8 status;
	अचिन्हित पूर्णांक handled = 0;

	VPRINTK("ENTER\n");

	अगर ((qc->tf.protocol == ATA_PROT_DMA) &&	/* पढ़ो */
	    (!(qc->tf.flags & ATA_TFLAG_WRITE))) अणु

		/* step two - DMA from DIMM to host */
		अगर (करोing_hdma) अणु
			VPRINTK("ata%u: read hdma, 0x%x 0x%x\n", ap->prपूर्णांक_id,
				पढ़ोl(mmio + 0x104), पढ़ोl(mmio + PDC_HDMA_CTLSTAT));
			/* get drive status; clear पूर्णांकr; complete txn */
			qc->err_mask |= ac_err_mask(ata_रुको_idle(ap));
			ata_qc_complete(qc);
			pdc20621_pop_hdma(qc);
		पूर्ण

		/* step one - exec ATA command */
		अन्यथा अणु
			u8 seq = (u8) (port_no + 1 + 4);
			VPRINTK("ata%u: read ata, 0x%x 0x%x\n", ap->prपूर्णांक_id,
				पढ़ोl(mmio + 0x104), पढ़ोl(mmio + PDC_HDMA_CTLSTAT));

			/* submit hdma pkt */
			pdc20621_dump_hdma(qc);
			pdc20621_push_hdma(qc, seq,
					   port_ofs + PDC_DIMM_HOST_PKT);
		पूर्ण
		handled = 1;

	पूर्ण अन्यथा अगर (qc->tf.protocol == ATA_PROT_DMA) अणु	/* ग_लिखो */

		/* step one - DMA from host to DIMM */
		अगर (करोing_hdma) अणु
			u8 seq = (u8) (port_no + 1);
			VPRINTK("ata%u: write hdma, 0x%x 0x%x\n", ap->prपूर्णांक_id,
				पढ़ोl(mmio + 0x104), पढ़ोl(mmio + PDC_HDMA_CTLSTAT));

			/* submit ata pkt */
			ग_लिखोl(0x00000001, mmio + PDC_20621_SEQCTL + (seq * 4));
			पढ़ोl(mmio + PDC_20621_SEQCTL + (seq * 4));
			ग_लिखोl(port_ofs + PDC_DIMM_ATA_PKT,
			       ap->ioaddr.cmd_addr + PDC_PKT_SUBMIT);
			पढ़ोl(ap->ioaddr.cmd_addr + PDC_PKT_SUBMIT);
		पूर्ण

		/* step two - execute ATA command */
		अन्यथा अणु
			VPRINTK("ata%u: write ata, 0x%x 0x%x\n", ap->prपूर्णांक_id,
				पढ़ोl(mmio + 0x104), पढ़ोl(mmio + PDC_HDMA_CTLSTAT));
			/* get drive status; clear पूर्णांकr; complete txn */
			qc->err_mask |= ac_err_mask(ata_रुको_idle(ap));
			ata_qc_complete(qc);
			pdc20621_pop_hdma(qc);
		पूर्ण
		handled = 1;

	/* command completion, but no data xfer */
	पूर्ण अन्यथा अगर (qc->tf.protocol == ATA_PROT_NODATA) अणु

		status = ata_sff_busy_रुको(ap, ATA_BUSY | ATA_DRQ, 1000);
		DPRINTK("BUS_NODATA (drv_stat 0x%X)\n", status);
		qc->err_mask |= ac_err_mask(status);
		ata_qc_complete(qc);
		handled = 1;

	पूर्ण अन्यथा अणु
		ap->stats.idle_irq++;
	पूर्ण

	वापस handled;
पूर्ण

अटल व्योम pdc20621_irq_clear(काष्ठा ata_port *ap)
अणु
	ioपढ़ो8(ap->ioaddr.status_addr);
पूर्ण

अटल irqवापस_t pdc20621_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा ata_port *ap;
	u32 mask = 0;
	अचिन्हित पूर्णांक i, पंचांगp, port_no;
	अचिन्हित पूर्णांक handled = 0;
	व्योम __iomem *mmio_base;

	VPRINTK("ENTER\n");

	अगर (!host || !host->iomap[PDC_MMIO_BAR]) अणु
		VPRINTK("QUICK EXIT\n");
		वापस IRQ_NONE;
	पूर्ण

	mmio_base = host->iomap[PDC_MMIO_BAR];

	/* पढ़ोing should also clear पूर्णांकerrupts */
	mmio_base += PDC_CHIP0_OFS;
	mask = पढ़ोl(mmio_base + PDC_20621_SEQMASK);
	VPRINTK("mask == 0x%x\n", mask);

	अगर (mask == 0xffffffff) अणु
		VPRINTK("QUICK EXIT 2\n");
		वापस IRQ_NONE;
	पूर्ण
	mask &= 0xffff;		/* only 16 tags possible */
	अगर (!mask) अणु
		VPRINTK("QUICK EXIT 3\n");
		वापस IRQ_NONE;
	पूर्ण

	spin_lock(&host->lock);

	क्रम (i = 1; i < 9; i++) अणु
		port_no = i - 1;
		अगर (port_no > 3)
			port_no -= 4;
		अगर (port_no >= host->n_ports)
			ap = शून्य;
		अन्यथा
			ap = host->ports[port_no];
		पंचांगp = mask & (1 << i);
		VPRINTK("seq %u, port_no %u, ap %p, tmp %x\n", i, port_no, ap, पंचांगp);
		अगर (पंचांगp && ap) अणु
			काष्ठा ata_queued_cmd *qc;

			qc = ata_qc_from_tag(ap, ap->link.active_tag);
			अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING)))
				handled += pdc20621_host_पूर्णांकr(ap, qc, (i > 4),
							      mmio_base);
		पूर्ण
	पूर्ण

	spin_unlock(&host->lock);

	VPRINTK("mask == 0x%x\n", mask);

	VPRINTK("EXIT\n");

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम pdc_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->ioaddr.cmd_addr;
	u32 पंचांगp;

	/* FIXME: अगर all 4 ATA engines are stopped, also stop HDMA engine */

	पंचांगp = पढ़ोl(mmio + PDC_CTLSTAT);
	पंचांगp |= PDC_MASK_INT;
	पंचांगp &= ~PDC_DMA_ENABLE;
	ग_लिखोl(पंचांगp, mmio + PDC_CTLSTAT);
	पढ़ोl(mmio + PDC_CTLSTAT); /* flush */
पूर्ण

अटल व्योम pdc_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->ioaddr.cmd_addr;
	u32 पंचांगp;

	/* FIXME: start HDMA engine, अगर zero ATA engines running */

	/* clear IRQ */
	ioपढ़ो8(ap->ioaddr.status_addr);

	/* turn IRQ back on */
	पंचांगp = पढ़ोl(mmio + PDC_CTLSTAT);
	पंचांगp &= ~PDC_MASK_INT;
	ग_लिखोl(पंचांगp, mmio + PDC_CTLSTAT);
	पढ़ोl(mmio + PDC_CTLSTAT); /* flush */
पूर्ण

अटल व्योम pdc_reset_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->ioaddr.cmd_addr + PDC_CTLSTAT;
	अचिन्हित पूर्णांक i;
	u32 पंचांगp;

	/* FIXME: handle HDMA copy engine */

	क्रम (i = 11; i > 0; i--) अणु
		पंचांगp = पढ़ोl(mmio);
		अगर (पंचांगp & PDC_RESET)
			अवरोध;

		udelay(100);

		पंचांगp |= PDC_RESET;
		ग_लिखोl(पंचांगp, mmio);
	पूर्ण

	पंचांगp &= ~PDC_RESET;
	ग_लिखोl(पंचांगp, mmio);
	पढ़ोl(mmio);	/* flush */
पूर्ण

अटल पूर्णांक pdc_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			 अचिन्हित दीर्घ deadline)
अणु
	pdc_reset_port(link->ap);
	वापस ata_sff_softreset(link, class, deadline);
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

अटल व्योम pdc_tf_load_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	WARN_ON(tf->protocol == ATA_PROT_DMA ||
		tf->protocol == ATAPI_PROT_DMA);
	ata_sff_tf_load(ap, tf);
पूर्ण


अटल व्योम pdc_exec_command_mmio(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	WARN_ON(tf->protocol == ATA_PROT_DMA ||
		tf->protocol == ATAPI_PROT_DMA);
	ata_sff_exec_command(ap, tf);
पूर्ण


अटल व्योम pdc_sata_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		= base;
	port->data_addr		= base;
	port->feature_addr	=
	port->error_addr	= base + 0x4;
	port->nsect_addr	= base + 0x8;
	port->lbal_addr		= base + 0xc;
	port->lbam_addr		= base + 0x10;
	port->lbah_addr		= base + 0x14;
	port->device_addr	= base + 0x18;
	port->command_addr	=
	port->status_addr	= base + 0x1c;
	port->altstatus_addr	=
	port->ctl_addr		= base + 0x38;
पूर्ण


#अगर_घोषित ATA_VERBOSE_DEBUG
अटल व्योम pdc20621_get_from_dimm(काष्ठा ata_host *host, व्योम *psource,
				   u32 offset, u32 size)
अणु
	u32 winकरोw_size;
	u16 idx;
	u8 page_mask;
	दीर्घ dist;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];
	व्योम __iomem *dimm_mmio = host->iomap[PDC_DIMM_BAR];

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	page_mask = 0x00;
	winकरोw_size = 0x2000 * 4; /* 32K byte uअक्षर size */
	idx = (u16) (offset / winकरोw_size);

	ग_लिखोl(0x01, mmio + PDC_GENERAL_CTLR);
	पढ़ोl(mmio + PDC_GENERAL_CTLR);
	ग_लिखोl(((idx) << page_mask), mmio + PDC_DIMM_WINDOW_CTLR);
	पढ़ोl(mmio + PDC_DIMM_WINDOW_CTLR);

	offset -= (idx * winकरोw_size);
	idx++;
	dist = ((दीर्घ) (winकरोw_size - (offset + size))) >= 0 ? size :
		(दीर्घ) (winकरोw_size - offset);
	स_नकल_fromio(psource, dimm_mmio + offset / 4, dist);

	psource += dist;
	size -= dist;
	क्रम (; (दीर्घ) size >= (दीर्घ) winकरोw_size ;) अणु
		ग_लिखोl(0x01, mmio + PDC_GENERAL_CTLR);
		पढ़ोl(mmio + PDC_GENERAL_CTLR);
		ग_लिखोl(((idx) << page_mask), mmio + PDC_DIMM_WINDOW_CTLR);
		पढ़ोl(mmio + PDC_DIMM_WINDOW_CTLR);
		स_नकल_fromio(psource, dimm_mmio, winकरोw_size / 4);
		psource += winकरोw_size;
		size -= winकरोw_size;
		idx++;
	पूर्ण

	अगर (size) अणु
		ग_लिखोl(0x01, mmio + PDC_GENERAL_CTLR);
		पढ़ोl(mmio + PDC_GENERAL_CTLR);
		ग_लिखोl(((idx) << page_mask), mmio + PDC_DIMM_WINDOW_CTLR);
		पढ़ोl(mmio + PDC_DIMM_WINDOW_CTLR);
		स_नकल_fromio(psource, dimm_mmio, size / 4);
	पूर्ण
पूर्ण
#पूर्ण_अगर


अटल व्योम pdc20621_put_to_dimm(काष्ठा ata_host *host, व्योम *psource,
				 u32 offset, u32 size)
अणु
	u32 winकरोw_size;
	u16 idx;
	u8 page_mask;
	दीर्घ dist;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];
	व्योम __iomem *dimm_mmio = host->iomap[PDC_DIMM_BAR];

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	page_mask = 0x00;
	winकरोw_size = 0x2000 * 4;       /* 32K byte uअक्षर size */
	idx = (u16) (offset / winकरोw_size);

	ग_लिखोl(((idx) << page_mask), mmio + PDC_DIMM_WINDOW_CTLR);
	पढ़ोl(mmio + PDC_DIMM_WINDOW_CTLR);
	offset -= (idx * winकरोw_size);
	idx++;
	dist = ((दीर्घ)(s32)(winकरोw_size - (offset + size))) >= 0 ? size :
		(दीर्घ) (winकरोw_size - offset);
	स_नकल_toio(dimm_mmio + offset / 4, psource, dist);
	ग_लिखोl(0x01, mmio + PDC_GENERAL_CTLR);
	पढ़ोl(mmio + PDC_GENERAL_CTLR);

	psource += dist;
	size -= dist;
	क्रम (; (दीर्घ) size >= (दीर्घ) winकरोw_size ;) अणु
		ग_लिखोl(((idx) << page_mask), mmio + PDC_DIMM_WINDOW_CTLR);
		पढ़ोl(mmio + PDC_DIMM_WINDOW_CTLR);
		स_नकल_toio(dimm_mmio, psource, winकरोw_size / 4);
		ग_लिखोl(0x01, mmio + PDC_GENERAL_CTLR);
		पढ़ोl(mmio + PDC_GENERAL_CTLR);
		psource += winकरोw_size;
		size -= winकरोw_size;
		idx++;
	पूर्ण

	अगर (size) अणु
		ग_लिखोl(((idx) << page_mask), mmio + PDC_DIMM_WINDOW_CTLR);
		पढ़ोl(mmio + PDC_DIMM_WINDOW_CTLR);
		स_नकल_toio(dimm_mmio, psource, size / 4);
		ग_लिखोl(0x01, mmio + PDC_GENERAL_CTLR);
		पढ़ोl(mmio + PDC_GENERAL_CTLR);
	पूर्ण
पूर्ण


अटल अचिन्हित पूर्णांक pdc20621_i2c_पढ़ो(काष्ठा ata_host *host, u32 device,
				      u32 subaddr, u32 *pdata)
अणु
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];
	u32 i2creg  = 0;
	u32 status;
	u32 count = 0;

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	i2creg |= device << 24;
	i2creg |= subaddr << 16;

	/* Set the device and subaddress */
	ग_लिखोl(i2creg, mmio + PDC_I2C_ADDR_DATA);
	पढ़ोl(mmio + PDC_I2C_ADDR_DATA);

	/* Write Control to perक्रमm पढ़ो operation, mask पूर्णांक */
	ग_लिखोl(PDC_I2C_READ | PDC_I2C_START | PDC_I2C_MASK_INT,
	       mmio + PDC_I2C_CONTROL);

	क्रम (count = 0; count <= 1000; count ++) अणु
		status = पढ़ोl(mmio + PDC_I2C_CONTROL);
		अगर (status & PDC_I2C_COMPLETE) अणु
			status = पढ़ोl(mmio + PDC_I2C_ADDR_DATA);
			अवरोध;
		पूर्ण अन्यथा अगर (count == 1000)
			वापस 0;
	पूर्ण

	*pdata = (status >> 8) & 0x000000ff;
	वापस 1;
पूर्ण


अटल पूर्णांक pdc20621_detect_dimm(काष्ठा ata_host *host)
अणु
	u32 data = 0;
	अगर (pdc20621_i2c_पढ़ो(host, PDC_DIMM0_SPD_DEV_ADDRESS,
			     PDC_DIMM_SPD_SYSTEM_FREQ, &data)) अणु
		अगर (data == 100)
			वापस 100;
	पूर्ण अन्यथा
		वापस 0;

	अगर (pdc20621_i2c_पढ़ो(host, PDC_DIMM0_SPD_DEV_ADDRESS, 9, &data)) अणु
		अगर (data <= 0x75)
			वापस 133;
	पूर्ण अन्यथा
		वापस 0;

	वापस 0;
पूर्ण


अटल पूर्णांक pdc20621_prog_dimm0(काष्ठा ata_host *host)
अणु
	u32 spd0[50];
	u32 data = 0;
	पूर्णांक size, i;
	u8 bdimmsize;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक reg;
		अचिन्हित पूर्णांक ofs;
	पूर्ण pdc_i2c_पढ़ो_data [] = अणु
		अणु PDC_DIMM_SPD_TYPE, 11 पूर्ण,
		अणु PDC_DIMM_SPD_FRESH_RATE, 12 पूर्ण,
		अणु PDC_DIMM_SPD_COLUMN_NUM, 4 पूर्ण,
		अणु PDC_DIMM_SPD_ATTRIBUTE, 21 पूर्ण,
		अणु PDC_DIMM_SPD_ROW_NUM, 3 पूर्ण,
		अणु PDC_DIMM_SPD_BANK_NUM, 17 पूर्ण,
		अणु PDC_DIMM_SPD_MODULE_ROW, 5 पूर्ण,
		अणु PDC_DIMM_SPD_ROW_PRE_CHARGE, 27 पूर्ण,
		अणु PDC_DIMM_SPD_ROW_ACTIVE_DELAY, 28 पूर्ण,
		अणु PDC_DIMM_SPD_RAS_CAS_DELAY, 29 पूर्ण,
		अणु PDC_DIMM_SPD_ACTIVE_PRECHARGE, 30 पूर्ण,
		अणु PDC_DIMM_SPD_CAS_LATENCY, 18 पूर्ण,
	पूर्ण;

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	क्रम (i = 0; i < ARRAY_SIZE(pdc_i2c_पढ़ो_data); i++)
		pdc20621_i2c_पढ़ो(host, PDC_DIMM0_SPD_DEV_ADDRESS,
				  pdc_i2c_पढ़ो_data[i].reg,
				  &spd0[pdc_i2c_पढ़ो_data[i].ofs]);

	data |= (spd0[4] - 8) | ((spd0[21] != 0) << 3) | ((spd0[3]-11) << 4);
	data |= ((spd0[17] / 4) << 6) | ((spd0[5] / 2) << 7) |
		((((spd0[27] + 9) / 10) - 1) << 8) ;
	data |= (((((spd0[29] > spd0[28])
		    ? spd0[29] : spd0[28]) + 9) / 10) - 1) << 10;
	data |= ((spd0[30] - spd0[29] + 9) / 10 - 2) << 12;

	अगर (spd0[18] & 0x08)
		data |= ((0x03) << 14);
	अन्यथा अगर (spd0[18] & 0x04)
		data |= ((0x02) << 14);
	अन्यथा अगर (spd0[18] & 0x01)
		data |= ((0x01) << 14);
	अन्यथा
		data |= (0 << 14);

	/*
	   Calculate the size of bDIMMSize (घातer of 2) and
	   merge the DIMM size by program start/end address.
	*/

	bdimmsize = spd0[4] + (spd0[5] / 2) + spd0[3] + (spd0[17] / 2) + 3;
	size = (1 << bdimmsize) >> 20;	/* size = xxx(MB) */
	data |= (((size / 16) - 1) << 16);
	data |= (0 << 23);
	data |= 8;
	ग_लिखोl(data, mmio + PDC_DIMM0_CONTROL);
	पढ़ोl(mmio + PDC_DIMM0_CONTROL);
	वापस size;
पूर्ण


अटल अचिन्हित पूर्णांक pdc20621_prog_dimm_global(काष्ठा ata_host *host)
अणु
	u32 data, spd0;
	पूर्णांक error, i;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	/*
	  Set To Default : DIMM Module Global Control Register (0x022259F1)
	  DIMM Arbitration Disable (bit 20)
	  DIMM Data/Control Output Driving Selection (bit12 - bit15)
	  Refresh Enable (bit 17)
	*/

	data = 0x022259F1;
	ग_लिखोl(data, mmio + PDC_SDRAM_CONTROL);
	पढ़ोl(mmio + PDC_SDRAM_CONTROL);

	/* Turn on क्रम ECC */
	अगर (!pdc20621_i2c_पढ़ो(host, PDC_DIMM0_SPD_DEV_ADDRESS,
			       PDC_DIMM_SPD_TYPE, &spd0)) अणु
		pr_err("Failed in i2c read: device=%#x, subaddr=%#x\n",
		       PDC_DIMM0_SPD_DEV_ADDRESS, PDC_DIMM_SPD_TYPE);
		वापस 1;
	पूर्ण
	अगर (spd0 == 0x02) अणु
		data |= (0x01 << 16);
		ग_लिखोl(data, mmio + PDC_SDRAM_CONTROL);
		पढ़ोl(mmio + PDC_SDRAM_CONTROL);
		prपूर्णांकk(KERN_ERR "Local DIMM ECC Enabled\n");
	पूर्ण

	/* DIMM Initialization Select/Enable (bit 18/19) */
	data &= (~(1<<18));
	data |= (1<<19);
	ग_लिखोl(data, mmio + PDC_SDRAM_CONTROL);

	error = 1;
	क्रम (i = 1; i <= 10; i++) अणु   /* polling ~5 secs */
		data = पढ़ोl(mmio + PDC_SDRAM_CONTROL);
		अगर (!(data & (1<<19))) अणु
			error = 0;
			अवरोध;
		पूर्ण
		msleep(i*100);
	पूर्ण
	वापस error;
पूर्ण


अटल अचिन्हित पूर्णांक pdc20621_dimm_init(काष्ठा ata_host *host)
अणु
	पूर्णांक speed, size, length;
	u32 addr, spd0, pci_status;
	u32 समय_period = 0;
	u32 tcount = 0;
	u32 ticks = 0;
	u32 घड़ी = 0;
	u32 fparam = 0;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	/* Initialize PLL based upon PCI Bus Frequency */

	/* Initialize Time Period Register */
	ग_लिखोl(0xffffffff, mmio + PDC_TIME_PERIOD);
	समय_period = पढ़ोl(mmio + PDC_TIME_PERIOD);
	VPRINTK("Time Period Register (0x40): 0x%x\n", समय_period);

	/* Enable समयr */
	ग_लिखोl(PDC_TIMER_DEFAULT, mmio + PDC_TIME_CONTROL);
	पढ़ोl(mmio + PDC_TIME_CONTROL);

	/* Wait 3 seconds */
	msleep(3000);

	/*
	   When समयr is enabled, counter is decreased every पूर्णांकernal
	   घड़ी cycle.
	*/

	tcount = पढ़ोl(mmio + PDC_TIME_COUNTER);
	VPRINTK("Time Counter Register (0x44): 0x%x\n", tcount);

	/*
	   If SX4 is on PCI-X bus, after 3 seconds, the समयr counter
	   रेजिस्टर should be >= (0xffffffff - 3x10^8).
	*/
	अगर (tcount >= PCI_X_TCOUNT) अणु
		ticks = (समय_period - tcount);
		VPRINTK("Num counters 0x%x (%d)\n", ticks, ticks);

		घड़ी = (ticks / 300000);
		VPRINTK("10 * Internal clk = 0x%x (%d)\n", घड़ी, घड़ी);

		घड़ी = (घड़ी * 33);
		VPRINTK("10 * Internal clk * 33 = 0x%x (%d)\n", घड़ी, घड़ी);

		/* PLL F Param (bit 22:16) */
		fparam = (1400000 / घड़ी) - 2;
		VPRINTK("PLL F Param: 0x%x (%d)\n", fparam, fparam);

		/* OD param = 0x2 (bit 31:30), R param = 0x5 (bit 29:25) */
		pci_status = (0x8a001824 | (fparam << 16));
	पूर्ण अन्यथा
		pci_status = PCI_PLL_INIT;

	/* Initialize PLL. */
	VPRINTK("pci_status: 0x%x\n", pci_status);
	ग_लिखोl(pci_status, mmio + PDC_CTL_STATUS);
	पढ़ोl(mmio + PDC_CTL_STATUS);

	/*
	   Read SPD of DIMM by I2C पूर्णांकerface,
	   and program the DIMM Module Controller.
	*/
	अगर (!(speed = pdc20621_detect_dimm(host))) अणु
		prपूर्णांकk(KERN_ERR "Detect Local DIMM Fail\n");
		वापस 1;	/* DIMM error */
	पूर्ण
	VPRINTK("Local DIMM Speed = %d\n", speed);

	/* Programming DIMM0 Module Control Register (index_CID0:80h) */
	size = pdc20621_prog_dimm0(host);
	VPRINTK("Local DIMM Size = %dMB\n", size);

	/* Programming DIMM Module Global Control Register (index_CID0:88h) */
	अगर (pdc20621_prog_dimm_global(host)) अणु
		prपूर्णांकk(KERN_ERR "Programming DIMM Module Global Control Register Fail\n");
		वापस 1;
	पूर्ण

#अगर_घोषित ATA_VERBOSE_DEBUG
	अणु
		u8 test_parttern1[40] =
			अणु0x55,0xAA,'P','r','o','m','i','s','e',' ',
			'N','o','t',' ','Y','e','t',' ',
			'D','e','f','i','n','e','d',' ',
			'1','.','1','0',
			'9','8','0','3','1','6','1','2',0,0पूर्ण;
		u8 test_parttern2[40] = अणु0पूर्ण;

		pdc20621_put_to_dimm(host, test_parttern2, 0x10040, 40);
		pdc20621_put_to_dimm(host, test_parttern2, 0x40, 40);

		pdc20621_put_to_dimm(host, test_parttern1, 0x10040, 40);
		pdc20621_get_from_dimm(host, test_parttern2, 0x40, 40);
		prपूर्णांकk(KERN_ERR "%x, %x, %s\n", test_parttern2[0],
		       test_parttern2[1], &(test_parttern2[2]));
		pdc20621_get_from_dimm(host, test_parttern2, 0x10040,
				       40);
		prपूर्णांकk(KERN_ERR "%x, %x, %s\n", test_parttern2[0],
		       test_parttern2[1], &(test_parttern2[2]));

		pdc20621_put_to_dimm(host, test_parttern1, 0x40, 40);
		pdc20621_get_from_dimm(host, test_parttern2, 0x40, 40);
		prपूर्णांकk(KERN_ERR "%x, %x, %s\n", test_parttern2[0],
		       test_parttern2[1], &(test_parttern2[2]));
	पूर्ण
#पूर्ण_अगर

	/* ECC initiliazation. */

	अगर (!pdc20621_i2c_पढ़ो(host, PDC_DIMM0_SPD_DEV_ADDRESS,
			       PDC_DIMM_SPD_TYPE, &spd0)) अणु
		pr_err("Failed in i2c read: device=%#x, subaddr=%#x\n",
		       PDC_DIMM0_SPD_DEV_ADDRESS, PDC_DIMM_SPD_TYPE);
		वापस 1;
	पूर्ण
	अगर (spd0 == 0x02) अणु
		व्योम *buf;
		VPRINTK("Start ECC initialization\n");
		addr = 0;
		length = size * 1024 * 1024;
		buf = kzalloc(ECC_ERASE_BUF_SZ, GFP_KERNEL);
		अगर (!buf)
			वापस 1;
		जबतक (addr < length) अणु
			pdc20621_put_to_dimm(host, buf, addr,
					     ECC_ERASE_BUF_SZ);
			addr += ECC_ERASE_BUF_SZ;
		पूर्ण
		kमुक्त(buf);
		VPRINTK("Finish ECC initialization\n");
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम pdc_20621_init(काष्ठा ata_host *host)
अणु
	u32 पंचांगp;
	व्योम __iomem *mmio = host->iomap[PDC_MMIO_BAR];

	/* hard-code chip #0 */
	mmio += PDC_CHIP0_OFS;

	/*
	 * Select page 0x40 क्रम our 32k DIMM winकरोw
	 */
	पंचांगp = पढ़ोl(mmio + PDC_20621_DIMM_WINDOW) & 0xffff0000;
	पंचांगp |= PDC_PAGE_WINDOW;	/* page 40h; arbitrarily selected */
	ग_लिखोl(पंचांगp, mmio + PDC_20621_DIMM_WINDOW);

	/*
	 * Reset Host DMA
	 */
	पंचांगp = पढ़ोl(mmio + PDC_HDMA_CTLSTAT);
	पंचांगp |= PDC_RESET;
	ग_लिखोl(पंचांगp, mmio + PDC_HDMA_CTLSTAT);
	पढ़ोl(mmio + PDC_HDMA_CTLSTAT);		/* flush */

	udelay(10);

	पंचांगp = पढ़ोl(mmio + PDC_HDMA_CTLSTAT);
	पंचांगp &= ~PDC_RESET;
	ग_लिखोl(पंचांगp, mmio + PDC_HDMA_CTLSTAT);
	पढ़ोl(mmio + PDC_HDMA_CTLSTAT);		/* flush */
पूर्ण

अटल पूर्णांक pdc_sata_init_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] =
		अणु &pdc_port_info[ent->driver_data], शून्य पूर्ण;
	काष्ठा ata_host *host;
	काष्ठा pdc_host_priv *hpriv;
	पूर्णांक i, rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* allocate host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 4);
	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);
	अगर (!host || !hpriv)
		वापस -ENOMEM;

	host->निजी_data = hpriv;

	/* acquire resources and fill host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, (1 << PDC_MMIO_BAR) | (1 << PDC_DIMM_BAR),
				DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		व्योम __iomem *base = host->iomap[PDC_MMIO_BAR] + PDC_CHIP0_OFS;
		अचिन्हित पूर्णांक offset = 0x200 + i * 0x80;

		pdc_sata_setup_port(&ap->ioaddr, base + offset);

		ata_port_pbar_desc(ap, PDC_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, PDC_DIMM_BAR, -1, "dimm");
		ata_port_pbar_desc(ap, PDC_MMIO_BAR, offset, "port");
	पूर्ण

	/* configure and activate */
	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;

	अगर (pdc20621_dimm_init(host))
		वापस -ENOMEM;
	pdc_20621_init(host);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, pdc20621_पूर्णांकerrupt,
				 IRQF_SHARED, &pdc_sata_sht);
पूर्ण

module_pci_driver(pdc_sata_pci_driver);

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("Promise SATA low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pdc_sata_pci_tbl);
MODULE_VERSION(DRV_VERSION);
