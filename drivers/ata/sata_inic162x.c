<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sata_inic162x.c - Driver क्रम Initio 162x SATA controllers
 *
 * Copyright 2006  SUSE Linux Products GmbH
 * Copyright 2006  Tejun Heo <teheo@novell.com>
 *
 * **** WARNING ****
 *
 * This driver never worked properly and unक्रमtunately data corruption is
 * relatively common.  There isn't anyone working on the driver and there's
 * no support from the venकरोr.  Do not use this driver in any production
 * environment.
 *
 * http://thपढ़ो.gmane.org/gmane.linux.debian.devel.bugs.rc/378525/focus=54491
 * https://bugzilla.kernel.org/show_bug.cgi?id=60565
 *
 * *****************
 *
 * This controller is eccentric and easily locks up अगर something isn't
 * right.  Documentation is available at initio's website but it only
 * करोcuments रेजिस्टरs (not programming model).
 *
 * This driver has पूर्णांकeresting history.  The first version was written
 * from the करोcumentation and a 2.4 IDE driver posted on a Taiwan
 * company, which didn't use any IDMA features and couldn't handle
 * LBA48.  The resulting driver couldn't handle LBA48 devices either
 * making it pretty useless.
 *
 * After a जबतक, initio picked the driver up, नामd it to
 * sata_initio162x, updated it to use IDMA क्रम ATA DMA commands and
 * posted it on their website.  It only used ATA_PROT_DMA क्रम IDMA and
 * attaching both devices and issuing IDMA and !IDMA commands
 * simultaneously broke it due to PIRQ masking पूर्णांकeraction but it did
 * show how to use the IDMA (ADMA + some initio specअगरic twists)
 * engine.
 *
 * Then, I picked up their changes again and here's the usable driver
 * which uses IDMA क्रम everything.  Everything works now including
 * LBA48, CD/DVD burning, suspend/resume and hotplug.  There are some
 * issues tho.  Result Tf is not resported properly, NCQ isn't
 * supported yet and CD/DVD writing works with DMA assisted PIO
 * protocol (which, क्रम native SATA devices, shouldn't cause any
 * noticeable dअगरference).
 *
 * Anyways, so, here's finally a working driver क्रम inic162x.  Enjoy!
 *
 * initio: If you guys wanna improve the driver regarding result TF
 * access and other stuff, please feel मुक्त to contact me.  I'll be
 * happy to assist.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_device.h>

#घोषणा DRV_NAME	"sata_inic162x"
#घोषणा DRV_VERSION	"0.4"

क्रमागत अणु
	MMIO_BAR_PCI		= 5,
	MMIO_BAR_CARDBUS	= 1,

	NR_PORTS		= 2,

	IDMA_CPB_TBL_SIZE	= 4 * 32,

	INIC_DMA_BOUNDARY	= 0xffffff,

	HOST_ACTRL		= 0x08,
	HOST_CTL		= 0x7c,
	HOST_STAT		= 0x7e,
	HOST_IRQ_STAT		= 0xbc,
	HOST_IRQ_MASK		= 0xbe,

	PORT_SIZE		= 0x40,

	/* रेजिस्टरs क्रम ATA TF operation */
	PORT_TF_DATA		= 0x00,
	PORT_TF_FEATURE		= 0x01,
	PORT_TF_NSECT		= 0x02,
	PORT_TF_LBAL		= 0x03,
	PORT_TF_LBAM		= 0x04,
	PORT_TF_LBAH		= 0x05,
	PORT_TF_DEVICE		= 0x06,
	PORT_TF_COMMAND		= 0x07,
	PORT_TF_ALT_STAT	= 0x08,
	PORT_IRQ_STAT		= 0x09,
	PORT_IRQ_MASK		= 0x0a,
	PORT_PRD_CTL		= 0x0b,
	PORT_PRD_ADDR		= 0x0c,
	PORT_PRD_XFERLEN	= 0x10,
	PORT_CPB_CPBLAR		= 0x18,
	PORT_CPB_PTQFIFO	= 0x1c,

	/* IDMA रेजिस्टर */
	PORT_IDMA_CTL		= 0x14,
	PORT_IDMA_STAT		= 0x16,

	PORT_RPQ_FIFO		= 0x1e,
	PORT_RPQ_CNT		= 0x1f,

	PORT_SCR		= 0x20,

	/* HOST_CTL bits */
	HCTL_LEDEN		= (1 << 3),  /* enable LED operation */
	HCTL_IRQOFF		= (1 << 8),  /* global IRQ off */
	HCTL_FTHD0		= (1 << 10), /* fअगरo threshold 0 */
	HCTL_FTHD1		= (1 << 11), /* fअगरo threshold 1*/
	HCTL_PWRDWN		= (1 << 12), /* घातer करोwn PHYs */
	HCTL_SOFTRST		= (1 << 13), /* global reset (no phy reset) */
	HCTL_RPGSEL		= (1 << 15), /* रेजिस्टर page select */

	HCTL_KNOWN_BITS		= HCTL_IRQOFF | HCTL_PWRDWN | HCTL_SOFTRST |
				  HCTL_RPGSEL,

	/* HOST_IRQ_(STAT|MASK) bits */
	HIRQ_PORT0		= (1 << 0),
	HIRQ_PORT1		= (1 << 1),
	HIRQ_SOFT		= (1 << 14),
	HIRQ_GLOBAL		= (1 << 15), /* STAT only */

	/* PORT_IRQ_(STAT|MASK) bits */
	PIRQ_OFFLINE		= (1 << 0),  /* device unplugged */
	PIRQ_ONLINE		= (1 << 1),  /* device plugged */
	PIRQ_COMPLETE		= (1 << 2),  /* completion पूर्णांकerrupt */
	PIRQ_FATAL		= (1 << 3),  /* fatal error */
	PIRQ_ATA		= (1 << 4),  /* ATA पूर्णांकerrupt */
	PIRQ_REPLY		= (1 << 5),  /* reply FIFO not empty */
	PIRQ_PENDING		= (1 << 7),  /* port IRQ pending (STAT only) */

	PIRQ_ERR		= PIRQ_OFFLINE | PIRQ_ONLINE | PIRQ_FATAL,
	PIRQ_MASK_DEFAULT	= PIRQ_REPLY | PIRQ_ATA,
	PIRQ_MASK_FREEZE	= 0xff,

	/* PORT_PRD_CTL bits */
	PRD_CTL_START		= (1 << 0),
	PRD_CTL_WR		= (1 << 3),
	PRD_CTL_DMAEN		= (1 << 7),  /* DMA enable */

	/* PORT_IDMA_CTL bits */
	IDMA_CTL_RST_ATA	= (1 << 2),  /* hardreset ATA bus */
	IDMA_CTL_RST_IDMA	= (1 << 5),  /* reset IDMA machinery */
	IDMA_CTL_GO		= (1 << 7),  /* IDMA mode go */
	IDMA_CTL_ATA_NIEN	= (1 << 8),  /* ATA IRQ disable */

	/* PORT_IDMA_STAT bits */
	IDMA_STAT_PERR		= (1 << 0),  /* PCI ERROR MODE */
	IDMA_STAT_CPBERR	= (1 << 1),  /* ADMA CPB error */
	IDMA_STAT_LGCY		= (1 << 3),  /* ADMA legacy */
	IDMA_STAT_UIRQ		= (1 << 4),  /* ADMA unsolicited irq */
	IDMA_STAT_STPD		= (1 << 5),  /* ADMA stopped */
	IDMA_STAT_PSD		= (1 << 6),  /* ADMA छोड़ो */
	IDMA_STAT_DONE		= (1 << 7),  /* ADMA करोne */

	IDMA_STAT_ERR		= IDMA_STAT_PERR | IDMA_STAT_CPBERR,

	/* CPB Control Flags*/
	CPB_CTL_VALID		= (1 << 0),  /* CPB valid */
	CPB_CTL_QUEUED		= (1 << 1),  /* queued command */
	CPB_CTL_DATA		= (1 << 2),  /* data, rsvd in datasheet */
	CPB_CTL_IEN		= (1 << 3),  /* PCI पूर्णांकerrupt enable */
	CPB_CTL_DEVसूची		= (1 << 4),  /* device direction control */

	/* CPB Response Flags */
	CPB_RESP_DONE		= (1 << 0),  /* ATA command complete */
	CPB_RESP_REL		= (1 << 1),  /* ATA release */
	CPB_RESP_IGNORED	= (1 << 2),  /* CPB ignored */
	CPB_RESP_ATA_ERR	= (1 << 3),  /* ATA command error */
	CPB_RESP_SPURIOUS	= (1 << 4),  /* ATA spurious पूर्णांकerrupt error */
	CPB_RESP_UNDERFLOW	= (1 << 5),  /* APRD deficiency length error */
	CPB_RESP_OVERFLOW	= (1 << 6),  /* APRD exccess length error */
	CPB_RESP_CPB_ERR	= (1 << 7),  /* CPB error flag */

	/* PRD Control Flags */
	PRD_DRAIN		= (1 << 1),  /* ignore data excess */
	PRD_CDB			= (1 << 2),  /* atapi packet command poपूर्णांकer */
	PRD_सूचीECT_INTR		= (1 << 3),  /* direct पूर्णांकerrupt */
	PRD_DMA			= (1 << 4),  /* data transfer method */
	PRD_WRITE		= (1 << 5),  /* data dir, rsvd in datasheet */
	PRD_IOM			= (1 << 6),  /* io/memory transfer */
	PRD_END			= (1 << 7),  /* APRD chain end */
पूर्ण;

/* Comman Parameter Block */
काष्ठा inic_cpb अणु
	u8		resp_flags;	/* Response Flags */
	u8		error;		/* ATA Error */
	u8		status;		/* ATA Status */
	u8		ctl_flags;	/* Control Flags */
	__le32		len;		/* Total Transfer Length */
	__le32		prd;		/* First PRD poपूर्णांकer */
	u8		rsvd[4];
	/* 16 bytes */
	u8		feature;	/* ATA Feature */
	u8		hob_feature;	/* ATA Ex. Feature */
	u8		device;		/* ATA Device/Head */
	u8		mirctl;		/* Mirror Control */
	u8		nsect;		/* ATA Sector Count */
	u8		hob_nsect;	/* ATA Ex. Sector Count */
	u8		lbal;		/* ATA Sector Number */
	u8		hob_lbal;	/* ATA Ex. Sector Number */
	u8		lbam;		/* ATA Cylinder Low */
	u8		hob_lbam;	/* ATA Ex. Cylinder Low */
	u8		lbah;		/* ATA Cylinder High */
	u8		hob_lbah;	/* ATA Ex. Cylinder High */
	u8		command;	/* ATA Command */
	u8		ctl;		/* ATA Control */
	u8		slave_error;	/* Slave ATA Error */
	u8		slave_status;	/* Slave ATA Status */
	/* 32 bytes */
पूर्ण __packed;

/* Physical Region Descriptor */
काष्ठा inic_prd अणु
	__le32		mad;		/* Physical Memory Address */
	__le16		len;		/* Transfer Length */
	u8		rsvd;
	u8		flags;		/* Control Flags */
पूर्ण __packed;

काष्ठा inic_pkt अणु
	काष्ठा inic_cpb	cpb;
	काष्ठा inic_prd	prd[LIBATA_MAX_PRD + 1];	/* + 1 क्रम cdb */
	u8		cdb[ATAPI_CDB_LEN];
पूर्ण __packed;

काष्ठा inic_host_priv अणु
	व्योम __iomem	*mmio_base;
	u16		cached_hctl;
पूर्ण;

काष्ठा inic_port_priv अणु
	काष्ठा inic_pkt	*pkt;
	dma_addr_t	pkt_dma;
	u32		*cpb_tbl;
	dma_addr_t	cpb_tbl_dma;
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा inic_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= LIBATA_MAX_PRD, /* maybe it can be larger? */

	/*
	 * This controller is braindamaged.  dma_boundary is 0xffff like others
	 * but it will lock up the whole machine HARD अगर 65536 byte PRD entry
	 * is fed.  Reduce maximum segment size.
	 */
	.dma_boundary		= INIC_DMA_BOUNDARY,
	.max_segment_size	= 65536 - 512,
पूर्ण;

अटल स्थिर पूर्णांक scr_map[] = अणु
	[SCR_STATUS]	= 0,
	[SCR_ERROR]	= 1,
	[SCR_CONTROL]	= 2,
पूर्ण;

अटल व्योम __iomem *inic_port_base(काष्ठा ata_port *ap)
अणु
	काष्ठा inic_host_priv *hpriv = ap->host->निजी_data;

	वापस hpriv->mmio_base + ap->port_no * PORT_SIZE;
पूर्ण

अटल व्योम inic_reset_port(व्योम __iomem *port_base)
अणु
	व्योम __iomem *idma_ctl = port_base + PORT_IDMA_CTL;

	/* stop IDMA engine */
	पढ़ोw(idma_ctl); /* flush */
	msleep(1);

	/* mask IRQ and निश्चित reset */
	ग_लिखोw(IDMA_CTL_RST_IDMA, idma_ctl);
	पढ़ोw(idma_ctl); /* flush */
	msleep(1);

	/* release reset */
	ग_लिखोw(0, idma_ctl);

	/* clear irq */
	ग_लिखोb(0xff, port_base + PORT_IRQ_STAT);
पूर्ण

अटल पूर्णांक inic_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित sc_reg, u32 *val)
अणु
	व्योम __iomem *scr_addr = inic_port_base(link->ap) + PORT_SCR;

	अगर (unlikely(sc_reg >= ARRAY_SIZE(scr_map)))
		वापस -EINVAL;

	*val = पढ़ोl(scr_addr + scr_map[sc_reg] * 4);

	/* this controller has stuck DIAG.N, ignore it */
	अगर (sc_reg == SCR_ERROR)
		*val &= ~SERR_PHYRDY_CHG;
	वापस 0;
पूर्ण

अटल पूर्णांक inic_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित sc_reg, u32 val)
अणु
	व्योम __iomem *scr_addr = inic_port_base(link->ap) + PORT_SCR;

	अगर (unlikely(sc_reg >= ARRAY_SIZE(scr_map)))
		वापस -EINVAL;

	ग_लिखोl(val, scr_addr + scr_map[sc_reg] * 4);
	वापस 0;
पूर्ण

अटल व्योम inic_stop_idma(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);

	पढ़ोb(port_base + PORT_RPQ_FIFO);
	पढ़ोb(port_base + PORT_RPQ_CNT);
	ग_लिखोw(0, port_base + PORT_IDMA_CTL);
पूर्ण

अटल व्योम inic_host_err_पूर्णांकr(काष्ठा ata_port *ap, u8 irq_stat, u16 idma_stat)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	काष्ठा inic_port_priv *pp = ap->निजी_data;
	काष्ठा inic_cpb *cpb = &pp->pkt->cpb;
	bool मुक्तze = false;

	ata_ehi_clear_desc(ehi);
	ata_ehi_push_desc(ehi, "irq_stat=0x%x idma_stat=0x%x",
			  irq_stat, idma_stat);

	inic_stop_idma(ap);

	अगर (irq_stat & (PIRQ_OFFLINE | PIRQ_ONLINE)) अणु
		ata_ehi_push_desc(ehi, "hotplug");
		ata_ehi_hotplugged(ehi);
		मुक्तze = true;
	पूर्ण

	अगर (idma_stat & IDMA_STAT_PERR) अणु
		ata_ehi_push_desc(ehi, "PCI error");
		मुक्तze = true;
	पूर्ण

	अगर (idma_stat & IDMA_STAT_CPBERR) अणु
		ata_ehi_push_desc(ehi, "CPB error");

		अगर (cpb->resp_flags & CPB_RESP_IGNORED) अणु
			__ata_ehi_push_desc(ehi, " ignored");
			ehi->err_mask |= AC_ERR_INVALID;
			मुक्तze = true;
		पूर्ण

		अगर (cpb->resp_flags & CPB_RESP_ATA_ERR)
			ehi->err_mask |= AC_ERR_DEV;

		अगर (cpb->resp_flags & CPB_RESP_SPURIOUS) अणु
			__ata_ehi_push_desc(ehi, " spurious-intr");
			ehi->err_mask |= AC_ERR_HSM;
			मुक्तze = true;
		पूर्ण

		अगर (cpb->resp_flags &
		    (CPB_RESP_UNDERFLOW | CPB_RESP_OVERFLOW)) अणु
			__ata_ehi_push_desc(ehi, " data-over/underflow");
			ehi->err_mask |= AC_ERR_HSM;
			मुक्तze = true;
		पूर्ण
	पूर्ण

	अगर (मुक्तze)
		ata_port_मुक्तze(ap);
	अन्यथा
		ata_port_पात(ap);
पूर्ण

अटल व्योम inic_host_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);
	काष्ठा ata_queued_cmd *qc = ata_qc_from_tag(ap, ap->link.active_tag);
	u8 irq_stat;
	u16 idma_stat;

	/* पढ़ो and clear IRQ status */
	irq_stat = पढ़ोb(port_base + PORT_IRQ_STAT);
	ग_लिखोb(irq_stat, port_base + PORT_IRQ_STAT);
	idma_stat = पढ़ोw(port_base + PORT_IDMA_STAT);

	अगर (unlikely((irq_stat & PIRQ_ERR) || (idma_stat & IDMA_STAT_ERR)))
		inic_host_err_पूर्णांकr(ap, irq_stat, idma_stat);

	अगर (unlikely(!qc))
		जाओ spurious;

	अगर (likely(idma_stat & IDMA_STAT_DONE)) अणु
		inic_stop_idma(ap);

		/* Depending on circumstances, device error
		 * isn't reported by IDMA, check it explicitly.
		 */
		अगर (unlikely(पढ़ोb(port_base + PORT_TF_COMMAND) &
			     (ATA_DF | ATA_ERR)))
			qc->err_mask |= AC_ERR_DEV;

		ata_qc_complete(qc);
		वापस;
	पूर्ण

 spurious:
	ata_port_warn(ap, "unhandled interrupt: cmd=0x%x irq_stat=0x%x idma_stat=0x%x\n",
		      qc ? qc->tf.command : 0xff, irq_stat, idma_stat);
पूर्ण

अटल irqवापस_t inic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा inic_host_priv *hpriv = host->निजी_data;
	u16 host_irq_stat;
	पूर्णांक i, handled = 0;

	host_irq_stat = पढ़ोw(hpriv->mmio_base + HOST_IRQ_STAT);

	अगर (unlikely(!(host_irq_stat & HIRQ_GLOBAL)))
		जाओ out;

	spin_lock(&host->lock);

	क्रम (i = 0; i < NR_PORTS; i++)
		अगर (host_irq_stat & (HIRQ_PORT0 << i)) अणु
			inic_host_पूर्णांकr(host->ports[i]);
			handled++;
		पूर्ण

	spin_unlock(&host->lock);

 out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक inic_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	/* For some reason ATAPI_PROT_DMA करोesn't work क्रम some
	 * commands including ग_लिखोs and other misc ops.  Use PIO
	 * protocol instead, which BTW is driven by the DMA engine
	 * anyway, so it shouldn't make much dअगरference क्रम native
	 * SATA devices.
	 */
	अगर (atapi_cmd_type(qc->cdb[0]) == READ)
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम inic_fill_sg(काष्ठा inic_prd *prd, काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si;
	u8 flags = 0;

	अगर (qc->tf.flags & ATA_TFLAG_WRITE)
		flags |= PRD_WRITE;

	अगर (ata_is_dma(qc->tf.protocol))
		flags |= PRD_DMA;

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		prd->mad = cpu_to_le32(sg_dma_address(sg));
		prd->len = cpu_to_le16(sg_dma_len(sg));
		prd->flags = flags;
		prd++;
	पूर्ण

	WARN_ON(!si);
	prd[-1].flags |= PRD_END;
पूर्ण

अटल क्रमागत ata_completion_errors inic_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा inic_port_priv *pp = qc->ap->निजी_data;
	काष्ठा inic_pkt *pkt = pp->pkt;
	काष्ठा inic_cpb *cpb = &pkt->cpb;
	काष्ठा inic_prd *prd = pkt->prd;
	bool is_atapi = ata_is_atapi(qc->tf.protocol);
	bool is_data = ata_is_data(qc->tf.protocol);
	अचिन्हित पूर्णांक cdb_len = 0;

	VPRINTK("ENTER\n");

	अगर (is_atapi)
		cdb_len = qc->dev->cdb_len;

	/* prepare packet, based on initio driver */
	स_रखो(pkt, 0, माप(काष्ठा inic_pkt));

	cpb->ctl_flags = CPB_CTL_VALID | CPB_CTL_IEN;
	अगर (is_atapi || is_data)
		cpb->ctl_flags |= CPB_CTL_DATA;

	cpb->len = cpu_to_le32(qc->nbytes + cdb_len);
	cpb->prd = cpu_to_le32(pp->pkt_dma + दुरत्व(काष्ठा inic_pkt, prd));

	cpb->device = qc->tf.device;
	cpb->feature = qc->tf.feature;
	cpb->nsect = qc->tf.nsect;
	cpb->lbal = qc->tf.lbal;
	cpb->lbam = qc->tf.lbam;
	cpb->lbah = qc->tf.lbah;

	अगर (qc->tf.flags & ATA_TFLAG_LBA48) अणु
		cpb->hob_feature = qc->tf.hob_feature;
		cpb->hob_nsect = qc->tf.hob_nsect;
		cpb->hob_lbal = qc->tf.hob_lbal;
		cpb->hob_lbam = qc->tf.hob_lbam;
		cpb->hob_lbah = qc->tf.hob_lbah;
	पूर्ण

	cpb->command = qc->tf.command;
	/* करोn't load ctl - dunno why.  it's like that in the initio driver */

	/* setup PRD क्रम CDB */
	अगर (is_atapi) अणु
		स_नकल(pkt->cdb, qc->cdb, ATAPI_CDB_LEN);
		prd->mad = cpu_to_le32(pp->pkt_dma +
				       दुरत्व(काष्ठा inic_pkt, cdb));
		prd->len = cpu_to_le16(cdb_len);
		prd->flags = PRD_CDB | PRD_WRITE;
		अगर (!is_data)
			prd->flags |= PRD_END;
		prd++;
	पूर्ण

	/* setup sg table */
	अगर (is_data)
		inic_fill_sg(prd, qc);

	pp->cpb_tbl[0] = pp->pkt_dma;

	वापस AC_ERR_OK;
पूर्ण

अटल अचिन्हित पूर्णांक inic_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *port_base = inic_port_base(ap);

	/* fire up the ADMA engine */
	ग_लिखोw(HCTL_FTHD0 | HCTL_LEDEN, port_base + HOST_CTL);
	ग_लिखोw(IDMA_CTL_GO, port_base + PORT_IDMA_CTL);
	ग_लिखोb(0, port_base + PORT_CPB_PTQFIFO);

	वापस 0;
पूर्ण

अटल व्योम inic_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);

	tf->feature	= पढ़ोb(port_base + PORT_TF_FEATURE);
	tf->nsect	= पढ़ोb(port_base + PORT_TF_NSECT);
	tf->lbal	= पढ़ोb(port_base + PORT_TF_LBAL);
	tf->lbam	= पढ़ोb(port_base + PORT_TF_LBAM);
	tf->lbah	= पढ़ोb(port_base + PORT_TF_LBAH);
	tf->device	= पढ़ोb(port_base + PORT_TF_DEVICE);
	tf->command	= पढ़ोb(port_base + PORT_TF_COMMAND);
पूर्ण

अटल bool inic_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *rtf = &qc->result_tf;
	काष्ठा ata_taskfile tf;

	/* FIXME: Except क्रम status and error, result TF access
	 * करोesn't work.  I tried पढ़ोing from BAR0/2, CPB and BAR5.
	 * None works regardless of which command पूर्णांकerface is used.
	 * For now वापस true अगरf status indicates device error.
	 * This means that we're reporting bogus sector क्रम RW
	 * failures.  Eeekk....
	 */
	inic_tf_पढ़ो(qc->ap, &tf);

	अगर (!(tf.command & ATA_ERR))
		वापस false;

	rtf->command = tf.command;
	rtf->feature = tf.feature;
	वापस true;
पूर्ण

अटल व्योम inic_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);

	ग_लिखोb(PIRQ_MASK_FREEZE, port_base + PORT_IRQ_MASK);
	ग_लिखोb(0xff, port_base + PORT_IRQ_STAT);
पूर्ण

अटल व्योम inic_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);

	ग_लिखोb(0xff, port_base + PORT_IRQ_STAT);
	ग_लिखोb(PIRQ_MASK_DEFAULT, port_base + PORT_IRQ_MASK);
पूर्ण

अटल पूर्णांक inic_check_पढ़ोy(काष्ठा ata_link *link)
अणु
	व्योम __iomem *port_base = inic_port_base(link->ap);

	वापस ata_check_पढ़ोy(पढ़ोb(port_base + PORT_TF_COMMAND));
पूर्ण

/*
 * SRST and SControl hardreset करोn't give valid signature on this
 * controller.  Only controller specअगरic hardreset mechanism works.
 */
अटल पूर्णांक inic_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *port_base = inic_port_base(ap);
	व्योम __iomem *idma_ctl = port_base + PORT_IDMA_CTL;
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(&link->eh_context);
	पूर्णांक rc;

	/* hammer it पूर्णांकo sane state */
	inic_reset_port(port_base);

	ग_लिखोw(IDMA_CTL_RST_ATA, idma_ctl);
	पढ़ोw(idma_ctl);	/* flush */
	ata_msleep(ap, 1);
	ग_लिखोw(0, idma_ctl);

	rc = sata_link_resume(link, timing, deadline);
	अगर (rc) अणु
		ata_link_warn(link,
			      "failed to resume link after reset (errno=%d)\n",
			      rc);
		वापस rc;
	पूर्ण

	*class = ATA_DEV_NONE;
	अगर (ata_link_online(link)) अणु
		काष्ठा ata_taskfile tf;

		/* रुको क्रम link to become पढ़ोy */
		rc = ata_रुको_after_reset(link, deadline, inic_check_पढ़ोy);
		/* link occupied, -ENODEV too is an error */
		अगर (rc) अणु
			ata_link_warn(link,
				      "device not ready after hardreset (errno=%d)\n",
				      rc);
			वापस rc;
		पूर्ण

		inic_tf_पढ़ो(ap, &tf);
		*class = ata_dev_classअगरy(&tf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम inic_error_handler(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);

	inic_reset_port(port_base);
	ata_std_error_handler(ap);
पूर्ण

अटल व्योम inic_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	/* make DMA engine क्रमget about the failed command */
	अगर (qc->flags & ATA_QCFLAG_FAILED)
		inic_reset_port(inic_port_base(qc->ap));
पूर्ण

अटल व्योम init_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_base = inic_port_base(ap);
	काष्ठा inic_port_priv *pp = ap->निजी_data;

	/* clear packet and CPB table */
	स_रखो(pp->pkt, 0, माप(काष्ठा inic_pkt));
	स_रखो(pp->cpb_tbl, 0, IDMA_CPB_TBL_SIZE);

	/* setup CPB lookup table addresses */
	ग_लिखोl(pp->cpb_tbl_dma, port_base + PORT_CPB_CPBLAR);
पूर्ण

अटल पूर्णांक inic_port_resume(काष्ठा ata_port *ap)
अणु
	init_port(ap);
	वापस 0;
पूर्ण

अटल पूर्णांक inic_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा inic_port_priv *pp;

	/* alloc and initialize निजी data */
	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;
	ap->निजी_data = pp;

	/* Alloc resources */
	pp->pkt = dmam_alloc_coherent(dev, माप(काष्ठा inic_pkt),
				      &pp->pkt_dma, GFP_KERNEL);
	अगर (!pp->pkt)
		वापस -ENOMEM;

	pp->cpb_tbl = dmam_alloc_coherent(dev, IDMA_CPB_TBL_SIZE,
					  &pp->cpb_tbl_dma, GFP_KERNEL);
	अगर (!pp->cpb_tbl)
		वापस -ENOMEM;

	init_port(ap);

	वापस 0;
पूर्ण

अटल काष्ठा ata_port_operations inic_port_ops = अणु
	.inherits		= &sata_port_ops,

	.check_atapi_dma	= inic_check_atapi_dma,
	.qc_prep		= inic_qc_prep,
	.qc_issue		= inic_qc_issue,
	.qc_fill_rtf		= inic_qc_fill_rtf,

	.मुक्तze			= inic_मुक्तze,
	.thaw			= inic_thaw,
	.hardreset		= inic_hardreset,
	.error_handler		= inic_error_handler,
	.post_पूर्णांकernal_cmd	= inic_post_पूर्णांकernal_cmd,

	.scr_पढ़ो		= inic_scr_पढ़ो,
	.scr_ग_लिखो		= inic_scr_ग_लिखो,

	.port_resume		= inic_port_resume,
	.port_start		= inic_port_start,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info inic_port_info = अणु
	.flags			= ATA_FLAG_SATA | ATA_FLAG_PIO_DMA,
	.pio_mask		= ATA_PIO4,
	.mwdma_mask		= ATA_MWDMA2,
	.udma_mask		= ATA_UDMA6,
	.port_ops		= &inic_port_ops
पूर्ण;

अटल पूर्णांक init_controller(व्योम __iomem *mmio_base, u16 hctl)
अणु
	पूर्णांक i;
	u16 val;

	hctl &= ~HCTL_KNOWN_BITS;

	/* Soft reset whole controller.  Spec says reset duration is 3
	 * PCI घड़ीs, be generous and give it 10ms.
	 */
	ग_लिखोw(hctl | HCTL_SOFTRST, mmio_base + HOST_CTL);
	पढ़ोw(mmio_base + HOST_CTL); /* flush */

	क्रम (i = 0; i < 10; i++) अणु
		msleep(1);
		val = पढ़ोw(mmio_base + HOST_CTL);
		अगर (!(val & HCTL_SOFTRST))
			अवरोध;
	पूर्ण

	अगर (val & HCTL_SOFTRST)
		वापस -EIO;

	/* mask all पूर्णांकerrupts and reset ports */
	क्रम (i = 0; i < NR_PORTS; i++) अणु
		व्योम __iomem *port_base = mmio_base + i * PORT_SIZE;

		ग_लिखोb(0xff, port_base + PORT_IRQ_MASK);
		inic_reset_port(port_base);
	पूर्ण

	/* port IRQ is masked now, unmask global IRQ */
	ग_लिखोw(hctl & ~HCTL_IRQOFF, mmio_base + HOST_CTL);
	val = पढ़ोw(mmio_base + HOST_IRQ_MASK);
	val &= ~(HIRQ_PORT0 | HIRQ_PORT1);
	ग_लिखोw(val, mmio_base + HOST_IRQ_MASK);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक inic_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा inic_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		rc = init_controller(hpriv->mmio_base, hpriv->cached_hctl);
		अगर (rc)
			वापस rc;
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक inic_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &inic_port_info, शून्य पूर्ण;
	काष्ठा ata_host *host;
	काष्ठा inic_host_priv *hpriv;
	व्योम __iomem * स्थिर *iomap;
	पूर्णांक mmio_bar;
	पूर्णांक i, rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	dev_alert(&pdev->dev, "inic162x support is broken with common data corruption issues and will be disabled by default, contact linux-ide@vger.kernel.org if in production use\n");

	/* alloc host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, NR_PORTS);
	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);
	अगर (!host || !hpriv)
		वापस -ENOMEM;

	host->निजी_data = hpriv;

	/* Acquire resources and fill host.  Note that PCI and cardbus
	 * use dअगरferent BARs.
	 */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (pci_resource_flags(pdev, MMIO_BAR_PCI) & IORESOURCE_MEM)
		mmio_bar = MMIO_BAR_PCI;
	अन्यथा
		mmio_bar = MMIO_BAR_CARDBUS;

	rc = pcim_iomap_regions(pdev, 1 << mmio_bar, DRV_NAME);
	अगर (rc)
		वापस rc;
	host->iomap = iomap = pcim_iomap_table(pdev);
	hpriv->mmio_base = iomap[mmio_bar];
	hpriv->cached_hctl = पढ़ोw(hpriv->mmio_base + HOST_CTL);

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ata_port_pbar_desc(ap, mmio_bar, -1, "mmio");
		ata_port_pbar_desc(ap, mmio_bar, i * PORT_SIZE, "port");
	पूर्ण

	/* Set dma_mask.  This devices करोesn't support 64bit addressing. */
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(&pdev->dev, "32-bit DMA enable failed\n");
		वापस rc;
	पूर्ण

	rc = init_controller(hpriv->mmio_base, hpriv->cached_hctl);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to initialize controller\n");
		वापस rc;
	पूर्ण

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, inic_पूर्णांकerrupt, IRQF_SHARED,
				 &inic_sht);
पूर्ण

अटल स्थिर काष्ठा pci_device_id inic_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INIT, 0x1622), पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver inic_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= inic_pci_tbl,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= inic_pci_device_resume,
#पूर्ण_अगर
	.probe 		= inic_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
पूर्ण;

module_pci_driver(inic_pci_driver);

MODULE_AUTHOR("Tejun Heo");
MODULE_DESCRIPTION("low-level driver for Initio 162x SATA");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, inic_pci_tbl);
MODULE_VERSION(DRV_VERSION);
