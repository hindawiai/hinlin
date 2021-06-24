<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pdc_adma.c - Pacअगरic Digital Corporation ADMA
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *
 *  Copyright 2005 Mark Lord
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Supports ATA disks in single-packet ADMA mode.
 *  Uses PIO क्रम everything अन्यथा.
 *
 *  TODO:  Use ADMA transfers क्रम ATAPI devices, when possible.
 *  This requires careful attention to a number of quirks of the chip.
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

#घोषणा DRV_NAME	"pdc_adma"
#घोषणा DRV_VERSION	"1.0"

/* macro to calculate base address क्रम ATA regs */
#घोषणा ADMA_ATA_REGS(base, port_no)	((base) + ((port_no) * 0x40))

/* macro to calculate base address क्रम ADMA regs */
#घोषणा ADMA_REGS(base, port_no)	((base) + 0x80 + ((port_no) * 0x20))

/* macro to obtain addresses from ata_port */
#घोषणा ADMA_PORT_REGS(ap) \
	ADMA_REGS((ap)->host->iomap[ADMA_MMIO_BAR], ap->port_no)

क्रमागत अणु
	ADMA_MMIO_BAR		= 4,

	ADMA_PORTS		= 2,
	ADMA_CPB_BYTES		= 40,
	ADMA_PRD_BYTES		= LIBATA_MAX_PRD * 16,
	ADMA_PKT_BYTES		= ADMA_CPB_BYTES + ADMA_PRD_BYTES,

	ADMA_DMA_BOUNDARY	= 0xffffffff,

	/* global रेजिस्टर offsets */
	ADMA_MODE_LOCK		= 0x00c7,

	/* per-channel रेजिस्टर offsets */
	ADMA_CONTROL		= 0x0000, /* ADMA control */
	ADMA_STATUS		= 0x0002, /* ADMA status */
	ADMA_CPB_COUNT		= 0x0004, /* CPB count */
	ADMA_CPB_CURRENT	= 0x000c, /* current CPB address */
	ADMA_CPB_NEXT		= 0x000c, /* next CPB address */
	ADMA_CPB_LOOKUP		= 0x0010, /* CPB lookup table */
	ADMA_FIFO_IN		= 0x0014, /* input FIFO threshold */
	ADMA_FIFO_OUT		= 0x0016, /* output FIFO threshold */

	/* ADMA_CONTROL रेजिस्टर bits */
	aNIEN			= (1 << 8), /* irq mask: 1==masked */
	aGO			= (1 << 7), /* packet trigger ("Go!") */
	aRSTADM			= (1 << 5), /* ADMA logic reset */
	aPIOMD4			= 0x0003,   /* PIO mode 4 */

	/* ADMA_STATUS रेजिस्टर bits */
	aPSD			= (1 << 6),
	aUIRQ			= (1 << 4),
	aPERR			= (1 << 0),

	/* CPB bits */
	cDONE			= (1 << 0),
	cATERR			= (1 << 3),

	cVLD			= (1 << 0),
	cDAT			= (1 << 2),
	cIEN			= (1 << 3),

	/* PRD bits */
	pORD			= (1 << 4),
	pसूचीO			= (1 << 5),
	pEND			= (1 << 7),

	/* ATA रेजिस्टर flags */
	rIGN			= (1 << 5),
	rEND			= (1 << 7),

	/* ATA रेजिस्टर addresses */
	ADMA_REGS_CONTROL	= 0x0e,
	ADMA_REGS_SECTOR_COUNT	= 0x12,
	ADMA_REGS_LBA_LOW	= 0x13,
	ADMA_REGS_LBA_MID	= 0x14,
	ADMA_REGS_LBA_HIGH	= 0x15,
	ADMA_REGS_DEVICE	= 0x16,
	ADMA_REGS_COMMAND	= 0x17,

	/* PCI device IDs */
	board_1841_idx		= 0,	/* ADMA 2-port controller */
पूर्ण;

प्रकार क्रमागत अणु adma_state_idle, adma_state_pkt, adma_state_mmio पूर्ण adma_state_t;

काष्ठा adma_port_priv अणु
	u8			*pkt;
	dma_addr_t		pkt_dma;
	adma_state_t		state;
पूर्ण;

अटल पूर्णांक adma_ata_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent);
अटल पूर्णांक adma_port_start(काष्ठा ata_port *ap);
अटल व्योम adma_port_stop(काष्ठा ata_port *ap);
अटल क्रमागत ata_completion_errors adma_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित पूर्णांक adma_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक adma_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल व्योम adma_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम adma_thaw(काष्ठा ata_port *ap);
अटल पूर्णांक adma_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);

अटल काष्ठा scsi_host_ढाँचा adma_ata_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= LIBATA_MAX_PRD,
	.dma_boundary		= ADMA_DMA_BOUNDARY,
पूर्ण;

अटल काष्ठा ata_port_operations adma_ata_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,

	.check_atapi_dma	= adma_check_atapi_dma,
	.qc_prep		= adma_qc_prep,
	.qc_issue		= adma_qc_issue,

	.मुक्तze			= adma_मुक्तze,
	.thaw			= adma_thaw,
	.prereset		= adma_prereset,

	.port_start		= adma_port_start,
	.port_stop		= adma_port_stop,
पूर्ण;

अटल काष्ठा ata_port_info adma_port_info[] = अणु
	/* board_1841_idx */
	अणु
		.flags		= ATA_FLAG_SLAVE_POSS | ATA_FLAG_PIO_POLLING,
		.pio_mask	= ATA_PIO4_ONLY,
		.udma_mask	= ATA_UDMA4,
		.port_ops	= &adma_ata_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id adma_ata_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PDC, 0x1841), board_1841_idx पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver adma_ata_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= adma_ata_pci_tbl,
	.probe			= adma_ata_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

अटल पूर्णांक adma_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस 1;	/* ATAPI DMA not yet supported */
पूर्ण

अटल व्योम adma_reset_engine(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *chan = ADMA_PORT_REGS(ap);

	/* reset ADMA to idle state */
	ग_लिखोw(aPIOMD4 | aNIEN | aRSTADM, chan + ADMA_CONTROL);
	udelay(2);
	ग_लिखोw(aPIOMD4, chan + ADMA_CONTROL);
	udelay(2);
पूर्ण

अटल व्योम adma_reinit_engine(काष्ठा ata_port *ap)
अणु
	काष्ठा adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *chan = ADMA_PORT_REGS(ap);

	/* mask/clear ATA पूर्णांकerrupts */
	ग_लिखोb(ATA_NIEN, ap->ioaddr.ctl_addr);
	ata_sff_check_status(ap);

	/* reset the ADMA engine */
	adma_reset_engine(ap);

	/* set in-FIFO threshold to 0x100 */
	ग_लिखोw(0x100, chan + ADMA_FIFO_IN);

	/* set CPB poपूर्णांकer */
	ग_लिखोl((u32)pp->pkt_dma, chan + ADMA_CPB_NEXT);

	/* set out-FIFO threshold to 0x100 */
	ग_लिखोw(0x100, chan + ADMA_FIFO_OUT);

	/* set CPB count */
	ग_लिखोw(1, chan + ADMA_CPB_COUNT);

	/* पढ़ो/discard ADMA status */
	पढ़ोb(chan + ADMA_STATUS);
पूर्ण

अटल अंतरभूत व्योम adma_enter_reg_mode(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *chan = ADMA_PORT_REGS(ap);

	ग_लिखोw(aPIOMD4, chan + ADMA_CONTROL);
	पढ़ोb(chan + ADMA_STATUS);	/* flush */
पूर्ण

अटल व्योम adma_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *chan = ADMA_PORT_REGS(ap);

	/* mask/clear ATA पूर्णांकerrupts */
	ग_लिखोb(ATA_NIEN, ap->ioaddr.ctl_addr);
	ata_sff_check_status(ap);

	/* reset ADMA to idle state */
	ग_लिखोw(aPIOMD4 | aNIEN | aRSTADM, chan + ADMA_CONTROL);
	udelay(2);
	ग_लिखोw(aPIOMD4 | aNIEN, chan + ADMA_CONTROL);
	udelay(2);
पूर्ण

अटल व्योम adma_thaw(काष्ठा ata_port *ap)
अणु
	adma_reinit_engine(ap);
पूर्ण

अटल पूर्णांक adma_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा adma_port_priv *pp = ap->निजी_data;

	अगर (pp->state != adma_state_idle) /* healthy paranoia */
		pp->state = adma_state_mmio;
	adma_reinit_engine(ap);

	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल पूर्णांक adma_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा adma_port_priv *pp = ap->निजी_data;
	u8  *buf = pp->pkt, *last_buf = शून्य;
	पूर्णांक i = (2 + buf[3]) * 8;
	u8 pFLAGS = pORD | ((qc->tf.flags & ATA_TFLAG_WRITE) ? pसूचीO : 0);
	अचिन्हित पूर्णांक si;

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr;
		u32 len;

		addr = (u32)sg_dma_address(sg);
		*(__le32 *)(buf + i) = cpu_to_le32(addr);
		i += 4;

		len = sg_dma_len(sg) >> 3;
		*(__le32 *)(buf + i) = cpu_to_le32(len);
		i += 4;

		last_buf = &buf[i];
		buf[i++] = pFLAGS;
		buf[i++] = qc->dev->dma_mode & 0xf;
		buf[i++] = 0;	/* pPKLW */
		buf[i++] = 0;	/* reserved */

		*(__le32 *)(buf + i) =
			(pFLAGS & pEND) ? 0 : cpu_to_le32(pp->pkt_dma + i + 4);
		i += 4;

		VPRINTK("PRD[%u] = (0x%lX, 0x%X)\n", i/4,
					(अचिन्हित दीर्घ)addr, len);
	पूर्ण

	अगर (likely(last_buf))
		*last_buf |= pEND;

	वापस i;
पूर्ण

अटल क्रमागत ata_completion_errors adma_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा adma_port_priv *pp = qc->ap->निजी_data;
	u8  *buf = pp->pkt;
	u32 pkt_dma = (u32)pp->pkt_dma;
	पूर्णांक i = 0;

	VPRINTK("ENTER\n");

	adma_enter_reg_mode(qc->ap);
	अगर (qc->tf.protocol != ATA_PROT_DMA)
		वापस AC_ERR_OK;

	buf[i++] = 0;	/* Response flags */
	buf[i++] = 0;	/* reserved */
	buf[i++] = cVLD | cDAT | cIEN;
	i++;		/* cLEN, माला_लो filled in below */

	*(__le32 *)(buf+i) = cpu_to_le32(pkt_dma);	/* cNCPB */
	i += 4;		/* cNCPB */
	i += 4;		/* cPRD, माला_लो filled in below */

	buf[i++] = 0;	/* reserved */
	buf[i++] = 0;	/* reserved */
	buf[i++] = 0;	/* reserved */
	buf[i++] = 0;	/* reserved */

	/* ATA रेजिस्टरs; must be a multiple of 4 */
	buf[i++] = qc->tf.device;
	buf[i++] = ADMA_REGS_DEVICE;
	अगर ((qc->tf.flags & ATA_TFLAG_LBA48)) अणु
		buf[i++] = qc->tf.hob_nsect;
		buf[i++] = ADMA_REGS_SECTOR_COUNT;
		buf[i++] = qc->tf.hob_lbal;
		buf[i++] = ADMA_REGS_LBA_LOW;
		buf[i++] = qc->tf.hob_lbam;
		buf[i++] = ADMA_REGS_LBA_MID;
		buf[i++] = qc->tf.hob_lbah;
		buf[i++] = ADMA_REGS_LBA_HIGH;
	पूर्ण
	buf[i++] = qc->tf.nsect;
	buf[i++] = ADMA_REGS_SECTOR_COUNT;
	buf[i++] = qc->tf.lbal;
	buf[i++] = ADMA_REGS_LBA_LOW;
	buf[i++] = qc->tf.lbam;
	buf[i++] = ADMA_REGS_LBA_MID;
	buf[i++] = qc->tf.lbah;
	buf[i++] = ADMA_REGS_LBA_HIGH;
	buf[i++] = 0;
	buf[i++] = ADMA_REGS_CONTROL;
	buf[i++] = rIGN;
	buf[i++] = 0;
	buf[i++] = qc->tf.command;
	buf[i++] = ADMA_REGS_COMMAND | rEND;

	buf[3] = (i >> 3) - 2;				/* cLEN */
	*(__le32 *)(buf+8) = cpu_to_le32(pkt_dma + i);	/* cPRD */

	i = adma_fill_sg(qc);
	wmb();	/* flush PRDs and pkt to memory */
#अगर 0
	/* dump out CPB + PRDs क्रम debug */
	अणु
		पूर्णांक j, len = 0;
		अटल अक्षर obuf[2048];
		क्रम (j = 0; j < i; ++j) अणु
			len += प्र_लिखो(obuf+len, "%02x ", buf[j]);
			अगर ((j & 7) == 7) अणु
				prपूर्णांकk("%s\n", obuf);
				len = 0;
			पूर्ण
		पूर्ण
		अगर (len)
			prपूर्णांकk("%s\n", obuf);
	पूर्ण
#पूर्ण_अगर
	वापस AC_ERR_OK;
पूर्ण

अटल अंतरभूत व्योम adma_packet_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *chan = ADMA_PORT_REGS(ap);

	VPRINTK("ENTER, ap %p\n", ap);

	/* fire up the ADMA engine */
	ग_लिखोw(aPIOMD4 | aGO, chan + ADMA_CONTROL);
पूर्ण

अटल अचिन्हित पूर्णांक adma_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा adma_port_priv *pp = qc->ap->निजी_data;

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		pp->state = adma_state_pkt;
		adma_packet_start(qc);
		वापस 0;

	हाल ATAPI_PROT_DMA:
		BUG();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	pp->state = adma_state_mmio;
	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक adma_पूर्णांकr_pkt(काष्ठा ata_host *host)
अणु
	अचिन्हित पूर्णांक handled = 0, port_no;

	क्रम (port_no = 0; port_no < host->n_ports; ++port_no) अणु
		काष्ठा ata_port *ap = host->ports[port_no];
		काष्ठा adma_port_priv *pp;
		काष्ठा ata_queued_cmd *qc;
		व्योम __iomem *chan = ADMA_PORT_REGS(ap);
		u8 status = पढ़ोb(chan + ADMA_STATUS);

		अगर (status == 0)
			जारी;
		handled = 1;
		adma_enter_reg_mode(ap);
		pp = ap->निजी_data;
		अगर (!pp || pp->state != adma_state_pkt)
			जारी;
		qc = ata_qc_from_tag(ap, ap->link.active_tag);
		अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING))) अणु
			अगर (status & aPERR)
				qc->err_mask |= AC_ERR_HOST_BUS;
			अन्यथा अगर ((status & (aPSD | aUIRQ)))
				qc->err_mask |= AC_ERR_OTHER;

			अगर (pp->pkt[0] & cATERR)
				qc->err_mask |= AC_ERR_DEV;
			अन्यथा अगर (pp->pkt[0] != cDONE)
				qc->err_mask |= AC_ERR_OTHER;

			अगर (!qc->err_mask)
				ata_qc_complete(qc);
			अन्यथा अणु
				काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
				ata_ehi_clear_desc(ehi);
				ata_ehi_push_desc(ehi,
					"ADMA-status 0x%02X", status);
				ata_ehi_push_desc(ehi,
					"pkt[0] 0x%02X", pp->pkt[0]);

				अगर (qc->err_mask == AC_ERR_DEV)
					ata_port_पात(ap);
				अन्यथा
					ata_port_मुक्तze(ap);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस handled;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक adma_पूर्णांकr_mmio(काष्ठा ata_host *host)
अणु
	अचिन्हित पूर्णांक handled = 0, port_no;

	क्रम (port_no = 0; port_no < host->n_ports; ++port_no) अणु
		काष्ठा ata_port *ap = host->ports[port_no];
		काष्ठा adma_port_priv *pp = ap->निजी_data;
		काष्ठा ata_queued_cmd *qc;

		अगर (!pp || pp->state != adma_state_mmio)
			जारी;
		qc = ata_qc_from_tag(ap, ap->link.active_tag);
		अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING))) अणु

			/* check मुख्य status, clearing INTRQ */
			u8 status = ata_sff_check_status(ap);
			अगर ((status & ATA_BUSY))
				जारी;
			DPRINTK("ata%u: protocol %d (dev_stat 0x%X)\n",
				ap->prपूर्णांक_id, qc->tf.protocol, status);

			/* complete taskfile transaction */
			pp->state = adma_state_idle;
			qc->err_mask |= ac_err_mask(status);
			अगर (!qc->err_mask)
				ata_qc_complete(qc);
			अन्यथा अणु
				काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
				ata_ehi_clear_desc(ehi);
				ata_ehi_push_desc(ehi, "status 0x%02X", status);

				अगर (qc->err_mask == AC_ERR_DEV)
					ata_port_पात(ap);
				अन्यथा
					ata_port_मुक्तze(ap);
			पूर्ण
			handled = 1;
		पूर्ण
	पूर्ण
	वापस handled;
पूर्ण

अटल irqवापस_t adma_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	अचिन्हित पूर्णांक handled = 0;

	VPRINTK("ENTER\n");

	spin_lock(&host->lock);
	handled  = adma_पूर्णांकr_pkt(host) | adma_पूर्णांकr_mmio(host);
	spin_unlock(&host->lock);

	VPRINTK("EXIT\n");

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम adma_ata_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		=
	port->data_addr		= base + 0x000;
	port->error_addr	=
	port->feature_addr	= base + 0x004;
	port->nsect_addr	= base + 0x008;
	port->lbal_addr		= base + 0x00c;
	port->lbam_addr		= base + 0x010;
	port->lbah_addr		= base + 0x014;
	port->device_addr	= base + 0x018;
	port->status_addr	=
	port->command_addr	= base + 0x01c;
	port->altstatus_addr	=
	port->ctl_addr		= base + 0x038;
पूर्ण

अटल पूर्णांक adma_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा adma_port_priv *pp;

	adma_enter_reg_mode(ap);
	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;
	pp->pkt = dmam_alloc_coherent(dev, ADMA_PKT_BYTES, &pp->pkt_dma,
				      GFP_KERNEL);
	अगर (!pp->pkt)
		वापस -ENOMEM;
	/* paranoia? */
	अगर ((pp->pkt_dma & 7) != 0) अणु
		prपूर्णांकk(KERN_ERR "bad alignment for pp->pkt_dma: %08x\n",
						(u32)pp->pkt_dma);
		वापस -ENOMEM;
	पूर्ण
	ap->निजी_data = pp;
	adma_reinit_engine(ap);
	वापस 0;
पूर्ण

अटल व्योम adma_port_stop(काष्ठा ata_port *ap)
अणु
	adma_reset_engine(ap);
पूर्ण

अटल व्योम adma_host_init(काष्ठा ata_host *host, अचिन्हित पूर्णांक chip_id)
अणु
	अचिन्हित पूर्णांक port_no;

	/* enable/lock aGO operation */
	ग_लिखोb(7, host->iomap[ADMA_MMIO_BAR] + ADMA_MODE_LOCK);

	/* reset the ADMA logic */
	क्रम (port_no = 0; port_no < ADMA_PORTS; ++port_no)
		adma_reset_engine(host->ports[port_no]);
पूर्ण

अटल पूर्णांक adma_ata_init_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक board_idx = (अचिन्हित पूर्णांक) ent->driver_data;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &adma_port_info[board_idx], शून्य पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *mmio_base;
	पूर्णांक rc, port_no;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* alloc host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, ADMA_PORTS);
	अगर (!host)
		वापस -ENOMEM;

	/* acquire resources and fill host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर ((pci_resource_flags(pdev, 4) & IORESOURCE_MEM) == 0)
		वापस -ENODEV;

	rc = pcim_iomap_regions(pdev, 1 << ADMA_MMIO_BAR, DRV_NAME);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);
	mmio_base = host->iomap[ADMA_MMIO_BAR];

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(&pdev->dev, "32-bit DMA enable failed\n");
		वापस rc;
	पूर्ण

	क्रम (port_no = 0; port_no < ADMA_PORTS; ++port_no) अणु
		काष्ठा ata_port *ap = host->ports[port_no];
		व्योम __iomem *port_base = ADMA_ATA_REGS(mmio_base, port_no);
		अचिन्हित पूर्णांक offset = port_base - mmio_base;

		adma_ata_setup_port(&ap->ioaddr, port_base);

		ata_port_pbar_desc(ap, ADMA_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, ADMA_MMIO_BAR, offset, "port");
	पूर्ण

	/* initialize adapter */
	adma_host_init(host, board_idx);

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, adma_पूर्णांकr, IRQF_SHARED,
				 &adma_ata_sht);
पूर्ण

module_pci_driver(adma_ata_pci_driver);

MODULE_AUTHOR("Mark Lord");
MODULE_DESCRIPTION("Pacific Digital Corporation ADMA low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, adma_ata_pci_tbl);
MODULE_VERSION(DRV_VERSION);
