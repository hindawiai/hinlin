<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_qstor.c - Pacअगरic Digital Corporation QStor SATA
 *
 *  Maपूर्णांकained by:  Mark Lord <mlord@pobox.com>
 *
 *  Copyright 2005 Pacअगरic Digital Corporation.
 *  (OSL/GPL code release authorized by Jalil Fadavi).
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"sata_qstor"
#घोषणा DRV_VERSION	"0.09"

क्रमागत अणु
	QS_MMIO_BAR		= 4,

	QS_PORTS		= 4,
	QS_MAX_PRD		= LIBATA_MAX_PRD,
	QS_CPB_ORDER		= 6,
	QS_CPB_BYTES		= (1 << QS_CPB_ORDER),
	QS_PRD_BYTES		= QS_MAX_PRD * 16,
	QS_PKT_BYTES		= QS_CPB_BYTES + QS_PRD_BYTES,

	/* global रेजिस्टर offsets */
	QS_HCF_CNFG3		= 0x0003, /* host configuration offset */
	QS_HID_HPHY		= 0x0004, /* host physical पूर्णांकerface info */
	QS_HCT_CTRL		= 0x00e4, /* global पूर्णांकerrupt mask offset */
	QS_HST_SFF		= 0x0100, /* host status fअगरo offset */
	QS_HVS_SERD3		= 0x0393, /* PHY enable offset */

	/* global control bits */
	QS_HPHY_64BIT		= (1 << 1), /* 64-bit bus detected */
	QS_CNFG3_GSRST		= 0x01,     /* global chip reset */
	QS_SERD3_PHY_ENA	= 0xf0,     /* PHY detection ENAble*/

	/* per-channel रेजिस्टर offsets */
	QS_CCF_CPBA		= 0x0710, /* chan CPB base address */
	QS_CCF_CSEP		= 0x0718, /* chan CPB separation factor */
	QS_CFC_HUFT		= 0x0800, /* host upstream fअगरo threshold */
	QS_CFC_HDFT		= 0x0804, /* host करोwnstream fअगरo threshold */
	QS_CFC_DUFT		= 0x0808, /* dev upstream fअगरo threshold */
	QS_CFC_DDFT		= 0x080c, /* dev करोwnstream fअगरo threshold */
	QS_CCT_CTR0		= 0x0900, /* chan control-0 offset */
	QS_CCT_CTR1		= 0x0901, /* chan control-1 offset */
	QS_CCT_CFF		= 0x0a00, /* chan command fअगरo offset */

	/* channel control bits */
	QS_CTR0_REG		= (1 << 1),   /* रेजिस्टर mode (vs. pkt mode) */
	QS_CTR0_CLER		= (1 << 2),   /* clear channel errors */
	QS_CTR1_RDEV		= (1 << 1),   /* sata phy/comms reset */
	QS_CTR1_RCHN		= (1 << 4),   /* reset channel logic */
	QS_CCF_RUN_PKT		= 0x107,      /* RUN a new dma PKT */

	/* pkt sub-field headers */
	QS_HCB_HDR		= 0x01,   /* Host Control Block header */
	QS_DCB_HDR		= 0x02,   /* Device Control Block header */

	/* pkt HCB flag bits */
	QS_HF_सूचीO		= (1 << 0),   /* data सूचीection Out */
	QS_HF_DAT		= (1 << 3),   /* DATa pkt */
	QS_HF_IEN		= (1 << 4),   /* Interrupt ENable */
	QS_HF_VLD		= (1 << 5),   /* VaLiD pkt */

	/* pkt DCB flag bits */
	QS_DF_PORD		= (1 << 2),   /* Pio OR Dma */
	QS_DF_ELBA		= (1 << 3),   /* Extended LBA (lba48) */

	/* PCI device IDs */
	board_2068_idx		= 0,	/* QStor 4-port SATA/RAID */
पूर्ण;

क्रमागत अणु
	QS_DMA_BOUNDARY		= ~0UL
पूर्ण;

प्रकार क्रमागत अणु qs_state_mmio, qs_state_pkt पूर्ण qs_state_t;

काष्ठा qs_port_priv अणु
	u8			*pkt;
	dma_addr_t		pkt_dma;
	qs_state_t		state;
पूर्ण;

अटल पूर्णांक qs_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक qs_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);
अटल पूर्णांक qs_ata_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल पूर्णांक qs_port_start(काष्ठा ata_port *ap);
अटल व्योम qs_host_stop(काष्ठा ata_host *host);
अटल क्रमागत ata_completion_errors qs_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित पूर्णांक qs_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक qs_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल व्योम qs_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम qs_thaw(काष्ठा ata_port *ap);
अटल पूर्णांक qs_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
अटल व्योम qs_error_handler(काष्ठा ata_port *ap);

अटल काष्ठा scsi_host_ढाँचा qs_ata_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= QS_MAX_PRD,
	.dma_boundary		= QS_DMA_BOUNDARY,
पूर्ण;

अटल काष्ठा ata_port_operations qs_ata_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.check_atapi_dma	= qs_check_atapi_dma,
	.qc_prep		= qs_qc_prep,
	.qc_issue		= qs_qc_issue,

	.मुक्तze			= qs_मुक्तze,
	.thaw			= qs_thaw,
	.prereset		= qs_prereset,
	.softreset		= ATA_OP_शून्य,
	.error_handler		= qs_error_handler,
	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,

	.scr_पढ़ो		= qs_scr_पढ़ो,
	.scr_ग_लिखो		= qs_scr_ग_लिखो,

	.port_start		= qs_port_start,
	.host_stop		= qs_host_stop,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info qs_port_info[] = अणु
	/* board_2068_idx */
	अणु
		.flags		= ATA_FLAG_SATA | ATA_FLAG_PIO_POLLING,
		.pio_mask	= ATA_PIO4_ONLY,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &qs_ata_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id qs_ata_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PDC, 0x2068), board_2068_idx पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver qs_ata_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= qs_ata_pci_tbl,
	.probe			= qs_ata_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

अटल व्योम __iomem *qs_mmio_base(काष्ठा ata_host *host)
अणु
	वापस host->iomap[QS_MMIO_BAR];
पूर्ण

अटल पूर्णांक qs_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस 1;	/* ATAPI DMA not supported */
पूर्ण

अटल अंतरभूत व्योम qs_enter_reg_mode(काष्ठा ata_port *ap)
अणु
	u8 __iomem *chan = qs_mmio_base(ap->host) + (ap->port_no * 0x4000);
	काष्ठा qs_port_priv *pp = ap->निजी_data;

	pp->state = qs_state_mmio;
	ग_लिखोb(QS_CTR0_REG, chan + QS_CCT_CTR0);
	पढ़ोb(chan + QS_CCT_CTR0);        /* flush */
पूर्ण

अटल अंतरभूत व्योम qs_reset_channel_logic(काष्ठा ata_port *ap)
अणु
	u8 __iomem *chan = qs_mmio_base(ap->host) + (ap->port_no * 0x4000);

	ग_लिखोb(QS_CTR1_RCHN, chan + QS_CCT_CTR1);
	पढ़ोb(chan + QS_CCT_CTR0);        /* flush */
	qs_enter_reg_mode(ap);
पूर्ण

अटल व्योम qs_मुक्तze(काष्ठा ata_port *ap)
अणु
	u8 __iomem *mmio_base = qs_mmio_base(ap->host);

	ग_लिखोb(0, mmio_base + QS_HCT_CTRL); /* disable host पूर्णांकerrupts */
	qs_enter_reg_mode(ap);
पूर्ण

अटल व्योम qs_thaw(काष्ठा ata_port *ap)
अणु
	u8 __iomem *mmio_base = qs_mmio_base(ap->host);

	qs_enter_reg_mode(ap);
	ग_लिखोb(1, mmio_base + QS_HCT_CTRL); /* enable host पूर्णांकerrupts */
पूर्ण

अटल पूर्णांक qs_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;

	qs_reset_channel_logic(ap);
	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल पूर्णांक qs_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	*val = पढ़ोl(link->ap->ioaddr.scr_addr + (sc_reg * 8));
	वापस 0;
पूर्ण

अटल व्योम qs_error_handler(काष्ठा ata_port *ap)
अणु
	qs_enter_reg_mode(ap);
	ata_sff_error_handler(ap);
पूर्ण

अटल पूर्णांक qs_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;
	ग_लिखोl(val, link->ap->ioaddr.scr_addr + (sc_reg * 8));
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक qs_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा qs_port_priv *pp = ap->निजी_data;
	u8 *prd = pp->pkt + QS_CPB_BYTES;
	अचिन्हित पूर्णांक si;

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u64 addr;
		u32 len;

		addr = sg_dma_address(sg);
		*(__le64 *)prd = cpu_to_le64(addr);
		prd += माप(u64);

		len = sg_dma_len(sg);
		*(__le32 *)prd = cpu_to_le32(len);
		prd += माप(u64);

		VPRINTK("PRD[%u] = (0x%llX, 0x%X)\n", si,
					(अचिन्हित दीर्घ दीर्घ)addr, len);
	पूर्ण

	वापस si;
पूर्ण

अटल क्रमागत ata_completion_errors qs_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा qs_port_priv *pp = qc->ap->निजी_data;
	u8 dflags = QS_DF_PORD, *buf = pp->pkt;
	u8 hflags = QS_HF_DAT | QS_HF_IEN | QS_HF_VLD;
	u64 addr;
	अचिन्हित पूर्णांक nelem;

	VPRINTK("ENTER\n");

	qs_enter_reg_mode(qc->ap);
	अगर (qc->tf.protocol != ATA_PROT_DMA)
		वापस AC_ERR_OK;

	nelem = qs_fill_sg(qc);

	अगर ((qc->tf.flags & ATA_TFLAG_WRITE))
		hflags |= QS_HF_सूचीO;
	अगर ((qc->tf.flags & ATA_TFLAG_LBA48))
		dflags |= QS_DF_ELBA;

	/* host control block (HCB) */
	buf[ 0] = QS_HCB_HDR;
	buf[ 1] = hflags;
	*(__le32 *)(&buf[ 4]) = cpu_to_le32(qc->nbytes);
	*(__le32 *)(&buf[ 8]) = cpu_to_le32(nelem);
	addr = ((u64)pp->pkt_dma) + QS_CPB_BYTES;
	*(__le64 *)(&buf[16]) = cpu_to_le64(addr);

	/* device control block (DCB) */
	buf[24] = QS_DCB_HDR;
	buf[28] = dflags;

	/* frame inक्रमmation काष्ठाure (FIS) */
	ata_tf_to_fis(&qc->tf, 0, 1, &buf[32]);

	वापस AC_ERR_OK;
पूर्ण

अटल अंतरभूत व्योम qs_packet_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	u8 __iomem *chan = qs_mmio_base(ap->host) + (ap->port_no * 0x4000);

	VPRINTK("ENTER, ap %p\n", ap);

	ग_लिखोb(QS_CTR0_CLER, chan + QS_CCT_CTR0);
	wmb();                             /* flush PRDs and pkt to memory */
	ग_लिखोl(QS_CCF_RUN_PKT, chan + QS_CCT_CFF);
	पढ़ोl(chan + QS_CCT_CFF);          /* flush */
पूर्ण

अटल अचिन्हित पूर्णांक qs_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा qs_port_priv *pp = qc->ap->निजी_data;

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		pp->state = qs_state_pkt;
		qs_packet_start(qc);
		वापस 0;

	हाल ATAPI_PROT_DMA:
		BUG();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	pp->state = qs_state_mmio;
	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल व्योम qs_करो_or_die(काष्ठा ata_queued_cmd *qc, u8 status)
अणु
	qc->err_mask |= ac_err_mask(status);

	अगर (!qc->err_mask) अणु
		ata_qc_complete(qc);
	पूर्ण अन्यथा अणु
		काष्ठा ata_port    *ap  = qc->ap;
		काष्ठा ata_eh_info *ehi = &ap->link.eh_info;

		ata_ehi_clear_desc(ehi);
		ata_ehi_push_desc(ehi, "status 0x%02X", status);

		अगर (qc->err_mask == AC_ERR_DEV)
			ata_port_पात(ap);
		अन्यथा
			ata_port_मुक्तze(ap);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक qs_पूर्णांकr_pkt(काष्ठा ata_host *host)
अणु
	अचिन्हित पूर्णांक handled = 0;
	u8 sFFE;
	u8 __iomem *mmio_base = qs_mmio_base(host);

	करो अणु
		u32 sff0 = पढ़ोl(mmio_base + QS_HST_SFF);
		u32 sff1 = पढ़ोl(mmio_base + QS_HST_SFF + 4);
		u8 sEVLD = (sff1 >> 30) & 0x01;	/* valid flag */
		sFFE  = sff1 >> 31;		/* empty flag */

		अगर (sEVLD) अणु
			u8 sDST = sff0 >> 16;	/* dev status */
			u8 sHST = sff1 & 0x3f;	/* host status */
			अचिन्हित पूर्णांक port_no = (sff1 >> 8) & 0x03;
			काष्ठा ata_port *ap = host->ports[port_no];
			काष्ठा qs_port_priv *pp = ap->निजी_data;
			काष्ठा ata_queued_cmd *qc;

			DPRINTK("SFF=%08x%08x: sCHAN=%u sHST=%d sDST=%02x\n",
					sff1, sff0, port_no, sHST, sDST);
			handled = 1;
			अगर (!pp || pp->state != qs_state_pkt)
				जारी;
			qc = ata_qc_from_tag(ap, ap->link.active_tag);
			अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING))) अणु
				चयन (sHST) अणु
				हाल 0: /* successful CPB */
				हाल 3: /* device error */
					qs_enter_reg_mode(qc->ap);
					qs_करो_or_die(qc, sDST);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!sFFE);
	वापस handled;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक qs_पूर्णांकr_mmio(काष्ठा ata_host *host)
अणु
	अचिन्हित पूर्णांक handled = 0, port_no;

	क्रम (port_no = 0; port_no < host->n_ports; ++port_no) अणु
		काष्ठा ata_port *ap = host->ports[port_no];
		काष्ठा qs_port_priv *pp = ap->निजी_data;
		काष्ठा ata_queued_cmd *qc;

		qc = ata_qc_from_tag(ap, ap->link.active_tag);
		अगर (!qc) अणु
			/*
			 * The qstor hardware generates spurious
			 * पूर्णांकerrupts from समय to समय when चयनing
			 * in and out of packet mode.  There's no
			 * obvious way to know अगर we're here now due
			 * to that, so just ack the irq and pretend we
			 * knew it was ours.. (ugh).  This करोes not
			 * affect packet mode.
			 */
			ata_sff_check_status(ap);
			handled = 1;
			जारी;
		पूर्ण

		अगर (!pp || pp->state != qs_state_mmio)
			जारी;
		अगर (!(qc->tf.flags & ATA_TFLAG_POLLING))
			handled |= ata_sff_port_पूर्णांकr(ap, qc);
	पूर्ण
	वापस handled;
पूर्ण

अटल irqवापस_t qs_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	अचिन्हित पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;

	VPRINTK("ENTER\n");

	spin_lock_irqsave(&host->lock, flags);
	handled  = qs_पूर्णांकr_pkt(host) | qs_पूर्णांकr_mmio(host);
	spin_unlock_irqrestore(&host->lock, flags);

	VPRINTK("EXIT\n");

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम qs_ata_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		=
	port->data_addr		= base + 0x400;
	port->error_addr	=
	port->feature_addr	= base + 0x408; /* hob_feature = 0x409 */
	port->nsect_addr	= base + 0x410; /* hob_nsect   = 0x411 */
	port->lbal_addr		= base + 0x418; /* hob_lbal    = 0x419 */
	port->lbam_addr		= base + 0x420; /* hob_lbam    = 0x421 */
	port->lbah_addr		= base + 0x428; /* hob_lbah    = 0x429 */
	port->device_addr	= base + 0x430;
	port->status_addr	=
	port->command_addr	= base + 0x438;
	port->altstatus_addr	=
	port->ctl_addr		= base + 0x440;
	port->scr_addr		= base + 0xc00;
पूर्ण

अटल पूर्णांक qs_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा qs_port_priv *pp;
	व्योम __iomem *mmio_base = qs_mmio_base(ap->host);
	व्योम __iomem *chan = mmio_base + (ap->port_no * 0x4000);
	u64 addr;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;
	pp->pkt = dmam_alloc_coherent(dev, QS_PKT_BYTES, &pp->pkt_dma,
				      GFP_KERNEL);
	अगर (!pp->pkt)
		वापस -ENOMEM;
	ap->निजी_data = pp;

	qs_enter_reg_mode(ap);
	addr = (u64)pp->pkt_dma;
	ग_लिखोl((u32) addr,        chan + QS_CCF_CPBA);
	ग_लिखोl((u32)(addr >> 32), chan + QS_CCF_CPBA + 4);
	वापस 0;
पूर्ण

अटल व्योम qs_host_stop(काष्ठा ata_host *host)
अणु
	व्योम __iomem *mmio_base = qs_mmio_base(host);

	ग_लिखोb(0, mmio_base + QS_HCT_CTRL); /* disable host पूर्णांकerrupts */
	ग_लिखोb(QS_CNFG3_GSRST, mmio_base + QS_HCF_CNFG3); /* global reset */
पूर्ण

अटल व्योम qs_host_init(काष्ठा ata_host *host, अचिन्हित पूर्णांक chip_id)
अणु
	व्योम __iomem *mmio_base = host->iomap[QS_MMIO_BAR];
	अचिन्हित पूर्णांक port_no;

	ग_लिखोb(0, mmio_base + QS_HCT_CTRL); /* disable host पूर्णांकerrupts */
	ग_लिखोb(QS_CNFG3_GSRST, mmio_base + QS_HCF_CNFG3); /* global reset */

	/* reset each channel in turn */
	क्रम (port_no = 0; port_no < host->n_ports; ++port_no) अणु
		u8 __iomem *chan = mmio_base + (port_no * 0x4000);
		ग_लिखोb(QS_CTR1_RDEV|QS_CTR1_RCHN, chan + QS_CCT_CTR1);
		ग_लिखोb(QS_CTR0_REG, chan + QS_CCT_CTR0);
		पढ़ोb(chan + QS_CCT_CTR0);        /* flush */
	पूर्ण
	ग_लिखोb(QS_SERD3_PHY_ENA, mmio_base + QS_HVS_SERD3); /* enable phy */

	क्रम (port_no = 0; port_no < host->n_ports; ++port_no) अणु
		u8 __iomem *chan = mmio_base + (port_no * 0x4000);
		/* set FIFO depths to same settings as Winकरोws driver */
		ग_लिखोw(32, chan + QS_CFC_HUFT);
		ग_लिखोw(32, chan + QS_CFC_HDFT);
		ग_लिखोw(10, chan + QS_CFC_DUFT);
		ग_लिखोw( 8, chan + QS_CFC_DDFT);
		/* set CPB size in bytes, as a घातer of two */
		ग_लिखोb(QS_CPB_ORDER,    chan + QS_CCF_CSEP);
	पूर्ण
	ग_लिखोb(1, mmio_base + QS_HCT_CTRL); /* enable host पूर्णांकerrupts */
पूर्ण

/*
 * The QStor understands 64-bit buses, and uses 64-bit fields
 * क्रम DMA poपूर्णांकers regardless of bus width.  We just have to
 * make sure our DMA masks are set appropriately क्रम whatever
 * bridge lies between us and the QStor, and then the DMA mapping
 * code will ensure we only ever "see" appropriate buffer addresses.
 * If we're 32-bit limited somewhere, then our 64-bit fields will
 * just end up with zeros in the upper 32-bits, without any special
 * logic required outside of this routine (below).
 */
अटल पूर्णांक qs_set_dma_masks(काष्ठा pci_dev *pdev, व्योम __iomem *mmio_base)
अणु
	u32 bus_info = पढ़ोl(mmio_base + QS_HID_HPHY);
	पूर्णांक dma_bits = (bus_info & QS_HPHY_64BIT) ? 64 : 32;
	पूर्णांक rc;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(dma_bits));
	अगर (rc)
		dev_err(&pdev->dev, "%d-bit DMA enable failed\n", dma_bits);
	वापस rc;
पूर्ण

अटल पूर्णांक qs_ata_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक board_idx = (अचिन्हित पूर्णांक) ent->driver_data;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &qs_port_info[board_idx], शून्य पूर्ण;
	काष्ठा ata_host *host;
	पूर्णांक rc, port_no;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* alloc host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, QS_PORTS);
	अगर (!host)
		वापस -ENOMEM;

	/* acquire resources and fill host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर ((pci_resource_flags(pdev, QS_MMIO_BAR) & IORESOURCE_MEM) == 0)
		वापस -ENODEV;

	rc = pcim_iomap_regions(pdev, 1 << QS_MMIO_BAR, DRV_NAME);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);

	rc = qs_set_dma_masks(pdev, host->iomap[QS_MMIO_BAR]);
	अगर (rc)
		वापस rc;

	क्रम (port_no = 0; port_no < host->n_ports; ++port_no) अणु
		काष्ठा ata_port *ap = host->ports[port_no];
		अचिन्हित पूर्णांक offset = port_no * 0x4000;
		व्योम __iomem *chan = host->iomap[QS_MMIO_BAR] + offset;

		qs_ata_setup_port(&ap->ioaddr, chan);

		ata_port_pbar_desc(ap, QS_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, QS_MMIO_BAR, offset, "port");
	पूर्ण

	/* initialize adapter */
	qs_host_init(host, board_idx);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, qs_पूर्णांकr, IRQF_SHARED,
				 &qs_ata_sht);
पूर्ण

module_pci_driver(qs_ata_pci_driver);

MODULE_AUTHOR("Mark Lord");
MODULE_DESCRIPTION("Pacific Digital Corporation QStor SATA low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, qs_ata_pci_tbl);
MODULE_VERSION(DRV_VERSION);
