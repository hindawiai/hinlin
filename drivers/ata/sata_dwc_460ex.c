<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/ata/sata_dwc_460ex.c
 *
 * Synopsys DesignWare Cores (DWC) SATA host driver
 *
 * Author: Mark Miesfeld <mmiesfeld@amcc.com>
 *
 * Ported from 2.6.19.2 to 2.6.25/26 by Stefan Roese <sr@denx.de>
 * Copyright 2008 DENX Software Engineering
 *
 * Based on versions provided by AMCC and Synopsys which are:
 *          Copyright 2006 Applied Micro Circuits Corporation
 *          COPYRIGHT (C) 2005  SYNOPSYS, INC.  ALL RIGHTS RESERVED
 */

#अगर_घोषित CONFIG_SATA_DWC_DEBUG
#घोषणा DEBUG
#पूर्ण_अगर

#अगर_घोषित CONFIG_SATA_DWC_VDEBUG
#घोषणा VERBOSE_DEBUG
#घोषणा DEBUG_NCQ
#पूर्ण_अगर

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/libata.h>
#समावेश <linux/slab.h>

#समावेश "libata.h"

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>

/* These two are defined in "libata.h" */
#अघोषित	DRV_NAME
#अघोषित	DRV_VERSION

#घोषणा DRV_NAME        "sata-dwc"
#घोषणा DRV_VERSION     "1.3"

#घोषणा sata_dwc_ग_लिखोl(a, v)	ग_लिखोl_relaxed(v, a)
#घोषणा sata_dwc_पढ़ोl(a)	पढ़ोl_relaxed(a)

#अगर_अघोषित NO_IRQ
#घोषणा NO_IRQ		0
#पूर्ण_अगर

#घोषणा AHB_DMA_BRST_DFLT	64	/* 16 data items burst length */

क्रमागत अणु
	SATA_DWC_MAX_PORTS = 1,

	SATA_DWC_SCR_OFFSET = 0x24,
	SATA_DWC_REG_OFFSET = 0x64,
पूर्ण;

/* DWC SATA Registers */
काष्ठा sata_dwc_regs अणु
	u32 fptagr;		/* 1st party DMA tag */
	u32 fpbor;		/* 1st party DMA buffer offset */
	u32 fptcr;		/* 1st party DMA Xfr count */
	u32 dmacr;		/* DMA Control */
	u32 dbtsr;		/* DMA Burst Transac size */
	u32 पूर्णांकpr;		/* Interrupt Pending */
	u32 पूर्णांकmr;		/* Interrupt Mask */
	u32 errmr;		/* Error Mask */
	u32 llcr;		/* Link Layer Control */
	u32 phycr;		/* PHY Control */
	u32 physr;		/* PHY Status */
	u32 rxbistpd;		/* Recvd BIST pattern def रेजिस्टर */
	u32 rxbistpd1;		/* Recvd BIST data dword1 */
	u32 rxbistpd2;		/* Recvd BIST pattern data dword2 */
	u32 txbistpd;		/* Trans BIST pattern def रेजिस्टर */
	u32 txbistpd1;		/* Trans BIST data dword1 */
	u32 txbistpd2;		/* Trans BIST data dword2 */
	u32 bistcr;		/* BIST Control Register */
	u32 bistfctr;		/* BIST FIS Count Register */
	u32 bistsr;		/* BIST Status Register */
	u32 bistdecr;		/* BIST Dword Error count रेजिस्टर */
	u32 res[15];		/* Reserved locations */
	u32 testr;		/* Test Register */
	u32 versionr;		/* Version Register */
	u32 idr;		/* ID Register */
	u32 unimpl[192];	/* Unimplemented */
	u32 dmadr[256];		/* FIFO Locations in DMA Mode */
पूर्ण;

क्रमागत अणु
	SCR_SCONTROL_DET_ENABLE	=	0x00000001,
	SCR_SSTATUS_DET_PRESENT	=	0x00000001,
	SCR_SERROR_DIAG_X	=	0x04000000,
/* DWC SATA Register Operations */
	SATA_DWC_TXFIFO_DEPTH	=	0x01FF,
	SATA_DWC_RXFIFO_DEPTH	=	0x01FF,
	SATA_DWC_DMACR_TMOD_TXCHEN =	0x00000004,
	SATA_DWC_DMACR_TXCHEN	= (0x00000001 | SATA_DWC_DMACR_TMOD_TXCHEN),
	SATA_DWC_DMACR_RXCHEN	= (0x00000002 | SATA_DWC_DMACR_TMOD_TXCHEN),
	SATA_DWC_DMACR_TXRXCH_CLEAR =	SATA_DWC_DMACR_TMOD_TXCHEN,
	SATA_DWC_INTPR_DMAT	=	0x00000001,
	SATA_DWC_INTPR_NEWFP	=	0x00000002,
	SATA_DWC_INTPR_PMABRT	=	0x00000004,
	SATA_DWC_INTPR_ERR	=	0x00000008,
	SATA_DWC_INTPR_NEWBIST	=	0x00000010,
	SATA_DWC_INTPR_IPF	=	0x10000000,
	SATA_DWC_INTMR_DMATM	=	0x00000001,
	SATA_DWC_INTMR_NEWFPM	=	0x00000002,
	SATA_DWC_INTMR_PMABRTM	=	0x00000004,
	SATA_DWC_INTMR_ERRM	=	0x00000008,
	SATA_DWC_INTMR_NEWBISTM	=	0x00000010,
	SATA_DWC_LLCR_SCRAMEN	=	0x00000001,
	SATA_DWC_LLCR_DESCRAMEN	=	0x00000002,
	SATA_DWC_LLCR_RPDEN	=	0x00000004,
/* This is all error bits, zero's are reserved fields. */
	SATA_DWC_SERROR_ERR_BITS =	0x0FFF0F03
पूर्ण;

#घोषणा SATA_DWC_SCR0_SPD_GET(v)	(((v) >> 4) & 0x0000000F)
#घोषणा SATA_DWC_DMACR_TX_CLEAR(v)	(((v) & ~SATA_DWC_DMACR_TXCHEN) |\
						 SATA_DWC_DMACR_TMOD_TXCHEN)
#घोषणा SATA_DWC_DMACR_RX_CLEAR(v)	(((v) & ~SATA_DWC_DMACR_RXCHEN) |\
						 SATA_DWC_DMACR_TMOD_TXCHEN)
#घोषणा SATA_DWC_DBTSR_MWR(size)	(((size)/4) & SATA_DWC_TXFIFO_DEPTH)
#घोषणा SATA_DWC_DBTSR_MRD(size)	((((size)/4) & SATA_DWC_RXFIFO_DEPTH)\
						 << 16)
काष्ठा sata_dwc_device अणु
	काष्ठा device		*dev;		/* generic device काष्ठा */
	काष्ठा ata_probe_ent	*pe;		/* ptr to probe-ent */
	काष्ठा ata_host		*host;
	काष्ठा sata_dwc_regs __iomem *sata_dwc_regs;	/* DW SATA specअगरic */
	u32			sactive_issued;
	u32			sactive_queued;
	काष्ठा phy		*phy;
	phys_addr_t		dmadr;
#अगर_घोषित CONFIG_SATA_DWC_OLD_DMA
	काष्ठा dw_dma_chip	*dma;
#पूर्ण_अगर
पूर्ण;

#घोषणा SATA_DWC_QCMD_MAX	32

काष्ठा sata_dwc_device_port अणु
	काष्ठा sata_dwc_device	*hsdev;
	पूर्णांक			cmd_issued[SATA_DWC_QCMD_MAX];
	पूर्णांक			dma_pending[SATA_DWC_QCMD_MAX];

	/* DMA info */
	काष्ठा dma_chan			*chan;
	काष्ठा dma_async_tx_descriptor	*desc[SATA_DWC_QCMD_MAX];
	u32				dma_पूर्णांकerrupt_count;
पूर्ण;

/*
 * Commonly used DWC SATA driver macros
 */
#घोषणा HSDEV_FROM_HOST(host)	((काष्ठा sata_dwc_device *)(host)->निजी_data)
#घोषणा HSDEV_FROM_AP(ap)	((काष्ठा sata_dwc_device *)(ap)->host->निजी_data)
#घोषणा HSDEVP_FROM_AP(ap)	((काष्ठा sata_dwc_device_port *)(ap)->निजी_data)
#घोषणा HSDEV_FROM_QC(qc)	((काष्ठा sata_dwc_device *)(qc)->ap->host->निजी_data)
#घोषणा HSDEV_FROM_HSDEVP(p)	((काष्ठा sata_dwc_device *)(p)->hsdev)

क्रमागत अणु
	SATA_DWC_CMD_ISSUED_NOT		= 0,
	SATA_DWC_CMD_ISSUED_PEND	= 1,
	SATA_DWC_CMD_ISSUED_EXEC	= 2,
	SATA_DWC_CMD_ISSUED_NODATA	= 3,

	SATA_DWC_DMA_PENDING_NONE	= 0,
	SATA_DWC_DMA_PENDING_TX		= 1,
	SATA_DWC_DMA_PENDING_RX		= 2,
पूर्ण;

/*
 * Prototypes
 */
अटल व्योम sata_dwc_bmdma_start_by_tag(काष्ठा ata_queued_cmd *qc, u8 tag);
अटल पूर्णांक sata_dwc_qc_complete(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc,
				u32 check_status);
अटल व्योम sata_dwc_dma_xfer_complete(काष्ठा ata_port *ap, u32 check_status);
अटल व्योम sata_dwc_port_stop(काष्ठा ata_port *ap);
अटल व्योम sata_dwc_clear_dmacr(काष्ठा sata_dwc_device_port *hsdevp, u8 tag);

#अगर_घोषित CONFIG_SATA_DWC_OLD_DMA

#समावेश <linux/platक्रमm_data/dma-dw.h>
#समावेश <linux/dma/dw.h>

अटल काष्ठा dw_dma_slave sata_dwc_dma_dws = अणु
	.src_id = 0,
	.dst_id = 0,
	.m_master = 1,
	.p_master = 0,
पूर्ण;

अटल bool sata_dwc_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा dw_dma_slave *dws = &sata_dwc_dma_dws;

	अगर (dws->dma_dev != chan->device->dev)
		वापस false;

	chan->निजी = dws;
	वापस true;
पूर्ण

अटल पूर्णांक sata_dwc_dma_get_channel_old(काष्ठा sata_dwc_device_port *hsdevp)
अणु
	काष्ठा sata_dwc_device *hsdev = hsdevp->hsdev;
	काष्ठा dw_dma_slave *dws = &sata_dwc_dma_dws;
	dma_cap_mask_t mask;

	dws->dma_dev = hsdev->dev;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Acquire DMA channel */
	hsdevp->chan = dma_request_channel(mask, sata_dwc_dma_filter, hsdevp);
	अगर (!hsdevp->chan) अणु
		dev_err(hsdev->dev, "%s: dma channel unavailable\n",
			 __func__);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sata_dwc_dma_init_old(काष्ठा platक्रमm_device *pdev,
				 काष्ठा sata_dwc_device *hsdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;

	hsdev->dma = devm_kzalloc(&pdev->dev, माप(*hsdev->dma), GFP_KERNEL);
	अगर (!hsdev->dma)
		वापस -ENOMEM;

	hsdev->dma->dev = &pdev->dev;
	hsdev->dma->id = pdev->id;

	/* Get SATA DMA पूर्णांकerrupt number */
	hsdev->dma->irq = irq_of_parse_and_map(np, 1);
	अगर (hsdev->dma->irq == NO_IRQ) अणु
		dev_err(&pdev->dev, "no SATA DMA irq\n");
		वापस -ENODEV;
	पूर्ण

	/* Get physical SATA DMA रेजिस्टर base address */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	hsdev->dma->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hsdev->dma->regs))
		वापस PTR_ERR(hsdev->dma->regs);

	/* Initialize AHB DMAC */
	वापस dw_dma_probe(hsdev->dma);
पूर्ण

अटल व्योम sata_dwc_dma_निकास_old(काष्ठा sata_dwc_device *hsdev)
अणु
	अगर (!hsdev->dma)
		वापस;

	dw_dma_हटाओ(hsdev->dma);
पूर्ण

#पूर्ण_अगर

अटल स्थिर अक्षर *get_prot_descript(u8 protocol)
अणु
	चयन (protocol) अणु
	हाल ATA_PROT_NODATA:
		वापस "ATA no data";
	हाल ATA_PROT_PIO:
		वापस "ATA PIO";
	हाल ATA_PROT_DMA:
		वापस "ATA DMA";
	हाल ATA_PROT_NCQ:
		वापस "ATA NCQ";
	हाल ATA_PROT_NCQ_NODATA:
		वापस "ATA NCQ no data";
	हाल ATAPI_PROT_NODATA:
		वापस "ATAPI no data";
	हाल ATAPI_PROT_PIO:
		वापस "ATAPI PIO";
	हाल ATAPI_PROT_DMA:
		वापस "ATAPI DMA";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *get_dma_dir_descript(पूर्णांक dma_dir)
अणु
	चयन ((क्रमागत dma_data_direction)dma_dir) अणु
	हाल DMA_BIसूचीECTIONAL:
		वापस "bidirectional";
	हाल DMA_TO_DEVICE:
		वापस "to device";
	हाल DMA_FROM_DEVICE:
		वापस "from device";
	शेष:
		वापस "none";
	पूर्ण
पूर्ण

अटल व्योम sata_dwc_tf_dump(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	dev_vdbg(ap->dev,
		"taskfile cmd: 0x%02x protocol: %s flags: 0x%lx device: %x\n",
		tf->command, get_prot_descript(tf->protocol), tf->flags,
		tf->device);
	dev_vdbg(ap->dev,
		"feature: 0x%02x nsect: 0x%x lbal: 0x%x lbam: 0x%x lbah: 0x%x\n",
		tf->feature, tf->nsect, tf->lbal, tf->lbam, tf->lbah);
	dev_vdbg(ap->dev,
		"hob_feature: 0x%02x hob_nsect: 0x%x hob_lbal: 0x%x hob_lbam: 0x%x hob_lbah: 0x%x\n",
		tf->hob_feature, tf->hob_nsect, tf->hob_lbal, tf->hob_lbam,
		tf->hob_lbah);
पूर्ण

अटल व्योम dma_dwc_xfer_करोne(व्योम *hsdev_instance)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sata_dwc_device *hsdev = hsdev_instance;
	काष्ठा ata_host *host = (काष्ठा ata_host *)hsdev->host;
	काष्ठा ata_port *ap;
	काष्ठा sata_dwc_device_port *hsdevp;
	u8 tag = 0;
	अचिन्हित पूर्णांक port = 0;

	spin_lock_irqsave(&host->lock, flags);
	ap = host->ports[port];
	hsdevp = HSDEVP_FROM_AP(ap);
	tag = ap->link.active_tag;

	/*
	 * Each DMA command produces 2 पूर्णांकerrupts.  Only
	 * complete the command after both पूर्णांकerrupts have been
	 * seen. (See sata_dwc_isr())
	 */
	hsdevp->dma_पूर्णांकerrupt_count++;
	sata_dwc_clear_dmacr(hsdevp, tag);

	अगर (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_NONE) अणु
		dev_err(ap->dev, "DMA not pending tag=0x%02x pending=%d\n",
			tag, hsdevp->dma_pending[tag]);
	पूर्ण

	अगर ((hsdevp->dma_पूर्णांकerrupt_count % 2) == 0)
		sata_dwc_dma_xfer_complete(ap, 1);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *dma_dwc_xfer_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_AP(ap);
	काष्ठा dma_slave_config sconf;
	काष्ठा dma_async_tx_descriptor *desc;

	अगर (qc->dma_dir == DMA_DEV_TO_MEM) अणु
		sconf.src_addr = hsdev->dmadr;
		sconf.device_fc = false;
	पूर्ण अन्यथा अणु	/* DMA_MEM_TO_DEV */
		sconf.dst_addr = hsdev->dmadr;
		sconf.device_fc = false;
	पूर्ण

	sconf.direction = qc->dma_dir;
	sconf.src_maxburst = AHB_DMA_BRST_DFLT / 4;	/* in items */
	sconf.dst_maxburst = AHB_DMA_BRST_DFLT / 4;	/* in items */
	sconf.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	sconf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	dmaengine_slave_config(hsdevp->chan, &sconf);

	/* Convert SG list to linked list of items (LLIs) क्रम AHB DMA */
	desc = dmaengine_prep_slave_sg(hsdevp->chan, qc->sg, qc->n_elem,
				       qc->dma_dir,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!desc)
		वापस शून्य;

	desc->callback = dma_dwc_xfer_करोne;
	desc->callback_param = hsdev;

	dev_dbg(hsdev->dev, "%s sg: 0x%p, count: %d addr: %pa\n", __func__,
		qc->sg, qc->n_elem, &hsdev->dmadr);

	वापस desc;
पूर्ण

अटल पूर्णांक sata_dwc_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 *val)
अणु
	अगर (scr > SCR_NOTIFICATION) अणु
		dev_err(link->ap->dev, "%s: Incorrect SCR offset 0x%02x\n",
			__func__, scr);
		वापस -EINVAL;
	पूर्ण

	*val = sata_dwc_पढ़ोl(link->ap->ioaddr.scr_addr + (scr * 4));
	dev_dbg(link->ap->dev, "%s: id=%d reg=%d val=0x%08x\n", __func__,
		link->ap->prपूर्णांक_id, scr, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक sata_dwc_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 val)
अणु
	dev_dbg(link->ap->dev, "%s: id=%d reg=%d val=0x%08x\n", __func__,
		link->ap->prपूर्णांक_id, scr, val);
	अगर (scr > SCR_NOTIFICATION) अणु
		dev_err(link->ap->dev, "%s: Incorrect SCR offset 0x%02x\n",
			 __func__, scr);
		वापस -EINVAL;
	पूर्ण
	sata_dwc_ग_लिखोl(link->ap->ioaddr.scr_addr + (scr * 4), val);

	वापस 0;
पूर्ण

अटल व्योम clear_serror(काष्ठा ata_port *ap)
अणु
	u32 val;
	sata_dwc_scr_पढ़ो(&ap->link, SCR_ERROR, &val);
	sata_dwc_scr_ग_लिखो(&ap->link, SCR_ERROR, val);
पूर्ण

अटल व्योम clear_पूर्णांकerrupt_bit(काष्ठा sata_dwc_device *hsdev, u32 bit)
अणु
	sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->पूर्णांकpr,
			sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->पूर्णांकpr));
पूर्ण

अटल u32 qcmd_tag_to_mask(u8 tag)
अणु
	वापस 0x00000001 << (tag & 0x1f);
पूर्ण

/* See ahci.c */
अटल व्योम sata_dwc_error_पूर्णांकr(काष्ठा ata_port *ap,
				काष्ठा sata_dwc_device *hsdev, uपूर्णांक पूर्णांकpr)
अणु
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	अचिन्हित पूर्णांक err_mask = 0, action = 0;
	काष्ठा ata_queued_cmd *qc;
	u32 serror;
	u8 status, tag;

	ata_ehi_clear_desc(ehi);

	sata_dwc_scr_पढ़ो(&ap->link, SCR_ERROR, &serror);
	status = ap->ops->sff_check_status(ap);

	tag = ap->link.active_tag;

	dev_err(ap->dev,
		"%s SCR_ERROR=0x%08x intpr=0x%08x status=0x%08x dma_intp=%d pending=%d issued=%d",
		__func__, serror, पूर्णांकpr, status, hsdevp->dma_पूर्णांकerrupt_count,
		hsdevp->dma_pending[tag], hsdevp->cmd_issued[tag]);

	/* Clear error रेजिस्टर and पूर्णांकerrupt bit */
	clear_serror(ap);
	clear_पूर्णांकerrupt_bit(hsdev, SATA_DWC_INTPR_ERR);

	/* This is the only error happening now.  TODO check क्रम exact error */

	err_mask |= AC_ERR_HOST_BUS;
	action |= ATA_EH_RESET;

	/* Pass this on to EH */
	ehi->serror |= serror;
	ehi->action |= action;

	qc = ata_qc_from_tag(ap, tag);
	अगर (qc)
		qc->err_mask |= err_mask;
	अन्यथा
		ehi->err_mask |= err_mask;

	ata_port_पात(ap);
पूर्ण

/*
 * Function : sata_dwc_isr
 * arguments : irq, व्योम *dev_instance, काष्ठा pt_regs *regs
 * Return value : irqवापस_t - status of IRQ
 * This Interrupt handler called via port ops रेजिस्टरed function.
 * .irq_handler = sata_dwc_isr
 */
अटल irqवापस_t sata_dwc_isr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = (काष्ठा ata_host *)dev_instance;
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_HOST(host);
	काष्ठा ata_port *ap;
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित दीर्घ flags;
	u8 status, tag;
	पूर्णांक handled, num_processed, port = 0;
	uपूर्णांक पूर्णांकpr, sactive, sactive2, tag_mask;
	काष्ठा sata_dwc_device_port *hsdevp;
	hsdev->sactive_issued = 0;

	spin_lock_irqsave(&host->lock, flags);

	/* Read the पूर्णांकerrupt रेजिस्टर */
	पूर्णांकpr = sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->पूर्णांकpr);

	ap = host->ports[port];
	hsdevp = HSDEVP_FROM_AP(ap);

	dev_dbg(ap->dev, "%s intpr=0x%08x active_tag=%d\n", __func__, पूर्णांकpr,
		ap->link.active_tag);

	/* Check क्रम error पूर्णांकerrupt */
	अगर (पूर्णांकpr & SATA_DWC_INTPR_ERR) अणु
		sata_dwc_error_पूर्णांकr(ap, hsdev, पूर्णांकpr);
		handled = 1;
		जाओ DONE;
	पूर्ण

	/* Check क्रम DMA SETUP FIS (FP DMA) पूर्णांकerrupt */
	अगर (पूर्णांकpr & SATA_DWC_INTPR_NEWFP) अणु
		clear_पूर्णांकerrupt_bit(hsdev, SATA_DWC_INTPR_NEWFP);

		tag = (u8)(sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->fptagr));
		dev_dbg(ap->dev, "%s: NEWFP tag=%d\n", __func__, tag);
		अगर (hsdevp->cmd_issued[tag] != SATA_DWC_CMD_ISSUED_PEND)
			dev_warn(ap->dev, "CMD tag=%d not pending?\n", tag);

		hsdev->sactive_issued |= qcmd_tag_to_mask(tag);

		qc = ata_qc_from_tag(ap, tag);
		अगर (unlikely(!qc)) अणु
			dev_err(ap->dev, "failed to get qc");
			handled = 1;
			जाओ DONE;
		पूर्ण
		/*
		 * Start FP DMA क्रम NCQ command.  At this poपूर्णांक the tag is the
		 * active tag.  It is the tag that matches the command about to
		 * be completed.
		 */
		qc->ap->link.active_tag = tag;
		sata_dwc_bmdma_start_by_tag(qc, tag);

		handled = 1;
		जाओ DONE;
	पूर्ण
	sata_dwc_scr_पढ़ो(&ap->link, SCR_ACTIVE, &sactive);
	tag_mask = (hsdev->sactive_issued | sactive) ^ sactive;

	/* If no sactive issued and tag_mask is zero then this is not NCQ */
	अगर (hsdev->sactive_issued == 0 && tag_mask == 0) अणु
		अगर (ap->link.active_tag == ATA_TAG_POISON)
			tag = 0;
		अन्यथा
			tag = ap->link.active_tag;
		qc = ata_qc_from_tag(ap, tag);

		/* DEV पूर्णांकerrupt w/ no active qc? */
		अगर (unlikely(!qc || (qc->tf.flags & ATA_TFLAG_POLLING))) अणु
			dev_err(ap->dev,
				"%s interrupt with no active qc qc=%p\n",
				__func__, qc);
			ap->ops->sff_check_status(ap);
			handled = 1;
			जाओ DONE;
		पूर्ण
		status = ap->ops->sff_check_status(ap);

		qc->ap->link.active_tag = tag;
		hsdevp->cmd_issued[tag] = SATA_DWC_CMD_ISSUED_NOT;

		अगर (status & ATA_ERR) अणु
			dev_dbg(ap->dev, "interrupt ATA_ERR (0x%x)\n", status);
			sata_dwc_qc_complete(ap, qc, 1);
			handled = 1;
			जाओ DONE;
		पूर्ण

		dev_dbg(ap->dev, "%s non-NCQ cmd interrupt, protocol: %s\n",
			__func__, get_prot_descript(qc->tf.protocol));
DRVSTILLBUSY:
		अगर (ata_is_dma(qc->tf.protocol)) अणु
			/*
			 * Each DMA transaction produces 2 पूर्णांकerrupts. The DMAC
			 * transfer complete पूर्णांकerrupt and the SATA controller
			 * operation करोne पूर्णांकerrupt. The command should be
			 * completed only after both पूर्णांकerrupts are seen.
			 */
			hsdevp->dma_पूर्णांकerrupt_count++;
			अगर (hsdevp->dma_pending[tag] == \
					SATA_DWC_DMA_PENDING_NONE) अणु
				dev_err(ap->dev,
					"%s: DMA not pending intpr=0x%08x status=0x%08x pending=%d\n",
					__func__, पूर्णांकpr, status,
					hsdevp->dma_pending[tag]);
			पूर्ण

			अगर ((hsdevp->dma_पूर्णांकerrupt_count % 2) == 0)
				sata_dwc_dma_xfer_complete(ap, 1);
		पूर्ण अन्यथा अगर (ata_is_pio(qc->tf.protocol)) अणु
			ata_sff_hsm_move(ap, qc, status, 0);
			handled = 1;
			जाओ DONE;
		पूर्ण अन्यथा अणु
			अगर (unlikely(sata_dwc_qc_complete(ap, qc, 1)))
				जाओ DRVSTILLBUSY;
		पूर्ण

		handled = 1;
		जाओ DONE;
	पूर्ण

	/*
	 * This is a NCQ command. At this poपूर्णांक we need to figure out क्रम which
	 * tags we have gotten a completion पूर्णांकerrupt.  One पूर्णांकerrupt may serve
	 * as completion क्रम more than one operation when commands are queued
	 * (NCQ).  We need to process each completed command.
	 */

	 /* process completed commands */
	sata_dwc_scr_पढ़ो(&ap->link, SCR_ACTIVE, &sactive);
	tag_mask = (hsdev->sactive_issued | sactive) ^ sactive;

	अगर (sactive != 0 || hsdev->sactive_issued > 1 || tag_mask > 1) अणु
		dev_dbg(ap->dev,
			"%s NCQ:sactive=0x%08x  sactive_issued=0x%08x tag_mask=0x%08x\n",
			__func__, sactive, hsdev->sactive_issued, tag_mask);
	पूर्ण

	अगर ((tag_mask | hsdev->sactive_issued) != hsdev->sactive_issued) अणु
		dev_warn(ap->dev,
			 "Bad tag mask?  sactive=0x%08x sactive_issued=0x%08x  tag_mask=0x%08x\n",
			 sactive, hsdev->sactive_issued, tag_mask);
	पूर्ण

	/* पढ़ो just to clear ... not bad अगर currently still busy */
	status = ap->ops->sff_check_status(ap);
	dev_dbg(ap->dev, "%s ATA status register=0x%x\n", __func__, status);

	tag = 0;
	num_processed = 0;
	जबतक (tag_mask) अणु
		num_processed++;
		जबतक (!(tag_mask & 0x00000001)) अणु
			tag++;
			tag_mask <<= 1;
		पूर्ण

		tag_mask &= (~0x00000001);
		qc = ata_qc_from_tag(ap, tag);
		अगर (unlikely(!qc)) अणु
			dev_err(ap->dev, "failed to get qc");
			handled = 1;
			जाओ DONE;
		पूर्ण

		/* To be picked up by completion functions */
		qc->ap->link.active_tag = tag;
		hsdevp->cmd_issued[tag] = SATA_DWC_CMD_ISSUED_NOT;

		/* Let libata/scsi layers handle error */
		अगर (status & ATA_ERR) अणु
			dev_dbg(ap->dev, "%s ATA_ERR (0x%x)\n", __func__,
				status);
			sata_dwc_qc_complete(ap, qc, 1);
			handled = 1;
			जाओ DONE;
		पूर्ण

		/* Process completed command */
		dev_dbg(ap->dev, "%s NCQ command, protocol: %s\n", __func__,
			get_prot_descript(qc->tf.protocol));
		अगर (ata_is_dma(qc->tf.protocol)) अणु
			hsdevp->dma_पूर्णांकerrupt_count++;
			अगर (hsdevp->dma_pending[tag] == \
					SATA_DWC_DMA_PENDING_NONE)
				dev_warn(ap->dev, "%s: DMA not pending?\n",
					__func__);
			अगर ((hsdevp->dma_पूर्णांकerrupt_count % 2) == 0)
				sata_dwc_dma_xfer_complete(ap, 1);
		पूर्ण अन्यथा अणु
			अगर (unlikely(sata_dwc_qc_complete(ap, qc, 1)))
				जाओ STILLBUSY;
		पूर्ण
		जारी;

STILLBUSY:
		ap->stats.idle_irq++;
		dev_warn(ap->dev, "STILL BUSY IRQ ata%d: irq trap\n",
			ap->prपूर्णांक_id);
	पूर्ण /* जबतक tag_mask */

	/*
	 * Check to see अगर any commands completed जबतक we were processing our
	 * initial set of completed commands (पढ़ो status clears पूर्णांकerrupts,
	 * so we might miss a completed command पूर्णांकerrupt अगर one came in जबतक
	 * we were processing --we पढ़ो status as part of processing a completed
	 * command).
	 */
	sata_dwc_scr_पढ़ो(&ap->link, SCR_ACTIVE, &sactive2);
	अगर (sactive2 != sactive) अणु
		dev_dbg(ap->dev,
			"More completed - sactive=0x%x sactive2=0x%x\n",
			sactive, sactive2);
	पूर्ण
	handled = 1;

DONE:
	spin_unlock_irqrestore(&host->lock, flags);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम sata_dwc_clear_dmacr(काष्ठा sata_dwc_device_port *hsdevp, u8 tag)
अणु
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_HSDEVP(hsdevp);
	u32 dmacr = sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->dmacr);

	अगर (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_RX) अणु
		dmacr = SATA_DWC_DMACR_RX_CLEAR(dmacr);
		sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr, dmacr);
	पूर्ण अन्यथा अगर (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_TX) अणु
		dmacr = SATA_DWC_DMACR_TX_CLEAR(dmacr);
		sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr, dmacr);
	पूर्ण अन्यथा अणु
		/*
		 * This should not happen, it indicates the driver is out of
		 * sync.  If it करोes happen, clear dmacr anyway.
		 */
		dev_err(hsdev->dev,
			"%s DMA protocol RX and TX DMA not pending tag=0x%02x pending=%d dmacr: 0x%08x\n",
			__func__, tag, hsdevp->dma_pending[tag], dmacr);
		sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr,
				SATA_DWC_DMACR_TXRXCH_CLEAR);
	पूर्ण
पूर्ण

अटल व्योम sata_dwc_dma_xfer_complete(काष्ठा ata_port *ap, u32 check_status)
अणु
	काष्ठा ata_queued_cmd *qc;
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_AP(ap);
	u8 tag = 0;

	tag = ap->link.active_tag;
	qc = ata_qc_from_tag(ap, tag);
	अगर (!qc) अणु
		dev_err(ap->dev, "failed to get qc");
		वापस;
	पूर्ण

#अगर_घोषित DEBUG_NCQ
	अगर (tag > 0) अणु
		dev_info(ap->dev,
			 "%s tag=%u cmd=0x%02x dma dir=%s proto=%s dmacr=0x%08x\n",
			 __func__, qc->hw_tag, qc->tf.command,
			 get_dma_dir_descript(qc->dma_dir),
			 get_prot_descript(qc->tf.protocol),
			 sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->dmacr));
	पूर्ण
#पूर्ण_अगर

	अगर (ata_is_dma(qc->tf.protocol)) अणु
		अगर (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_NONE) अणु
			dev_err(ap->dev,
				"%s DMA protocol RX and TX DMA not pending dmacr: 0x%08x\n",
				__func__,
				sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->dmacr));
		पूर्ण

		hsdevp->dma_pending[tag] = SATA_DWC_DMA_PENDING_NONE;
		sata_dwc_qc_complete(ap, qc, check_status);
		ap->link.active_tag = ATA_TAG_POISON;
	पूर्ण अन्यथा अणु
		sata_dwc_qc_complete(ap, qc, check_status);
	पूर्ण
पूर्ण

अटल पूर्णांक sata_dwc_qc_complete(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc,
				u32 check_status)
अणु
	u8 status = 0;
	u32 mask = 0x0;
	u8 tag = qc->hw_tag;
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_AP(ap);
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);
	hsdev->sactive_queued = 0;
	dev_dbg(ap->dev, "%s checkstatus? %x\n", __func__, check_status);

	अगर (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_TX)
		dev_err(ap->dev, "TX DMA PENDING\n");
	अन्यथा अगर (hsdevp->dma_pending[tag] == SATA_DWC_DMA_PENDING_RX)
		dev_err(ap->dev, "RX DMA PENDING\n");
	dev_dbg(ap->dev,
		"QC complete cmd=0x%02x status=0x%02x ata%u: protocol=%d\n",
		qc->tf.command, status, ap->prपूर्णांक_id, qc->tf.protocol);

	/* clear active bit */
	mask = (~(qcmd_tag_to_mask(tag)));
	hsdev->sactive_queued = hsdev->sactive_queued & mask;
	hsdev->sactive_issued = hsdev->sactive_issued & mask;
	ata_qc_complete(qc);
	वापस 0;
पूर्ण

अटल व्योम sata_dwc_enable_पूर्णांकerrupts(काष्ठा sata_dwc_device *hsdev)
अणु
	/* Enable selective पूर्णांकerrupts by setting the पूर्णांकerrupt maskरेजिस्टर*/
	sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->पूर्णांकmr,
			SATA_DWC_INTMR_ERRM |
			SATA_DWC_INTMR_NEWFPM |
			SATA_DWC_INTMR_PMABRTM |
			SATA_DWC_INTMR_DMATM);
	/*
	 * Unmask the error bits that should trigger an error पूर्णांकerrupt by
	 * setting the error mask रेजिस्टर.
	 */
	sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->errmr, SATA_DWC_SERROR_ERR_BITS);

	dev_dbg(hsdev->dev, "%s: INTMR = 0x%08x, ERRMR = 0x%08x\n",
		 __func__, sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->पूर्णांकmr),
		sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->errmr));
पूर्ण

अटल व्योम sata_dwc_setup_port(काष्ठा ata_ioports *port, व्योम __iomem *base)
अणु
	port->cmd_addr		= base + 0x00;
	port->data_addr		= base + 0x00;

	port->error_addr	= base + 0x04;
	port->feature_addr	= base + 0x04;

	port->nsect_addr	= base + 0x08;

	port->lbal_addr		= base + 0x0c;
	port->lbam_addr		= base + 0x10;
	port->lbah_addr		= base + 0x14;

	port->device_addr	= base + 0x18;
	port->command_addr	= base + 0x1c;
	port->status_addr	= base + 0x1c;

	port->altstatus_addr	= base + 0x20;
	port->ctl_addr		= base + 0x20;
पूर्ण

अटल पूर्णांक sata_dwc_dma_get_channel(काष्ठा sata_dwc_device_port *hsdevp)
अणु
	काष्ठा sata_dwc_device *hsdev = hsdevp->hsdev;
	काष्ठा device *dev = hsdev->dev;

#अगर_घोषित CONFIG_SATA_DWC_OLD_DMA
	अगर (!of_find_property(dev->of_node, "dmas", शून्य))
		वापस sata_dwc_dma_get_channel_old(hsdevp);
#पूर्ण_अगर

	hsdevp->chan = dma_request_chan(dev, "sata-dma");
	अगर (IS_ERR(hsdevp->chan)) अणु
		dev_err(dev, "failed to allocate dma channel: %ld\n",
			PTR_ERR(hsdevp->chan));
		वापस PTR_ERR(hsdevp->chan);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function : sata_dwc_port_start
 * arguments : काष्ठा ata_ioports *port
 * Return value : वापसs 0 अगर success, error code otherwise
 * This function allocates the scatter gather LLI table क्रम AHB DMA
 */
अटल पूर्णांक sata_dwc_port_start(काष्ठा ata_port *ap)
अणु
	पूर्णांक err = 0;
	काष्ठा sata_dwc_device *hsdev;
	काष्ठा sata_dwc_device_port *hsdevp = शून्य;
	काष्ठा device *pdev;
	पूर्णांक i;

	hsdev = HSDEV_FROM_AP(ap);

	dev_dbg(ap->dev, "%s: port_no=%d\n", __func__, ap->port_no);

	hsdev->host = ap->host;
	pdev = ap->host->dev;
	अगर (!pdev) अणु
		dev_err(ap->dev, "%s: no ap->host->dev\n", __func__);
		err = -ENODEV;
		जाओ CLEANUP;
	पूर्ण

	/* Allocate Port Struct */
	hsdevp = kzalloc(माप(*hsdevp), GFP_KERNEL);
	अगर (!hsdevp) अणु
		err = -ENOMEM;
		जाओ CLEANUP;
	पूर्ण
	hsdevp->hsdev = hsdev;

	err = sata_dwc_dma_get_channel(hsdevp);
	अगर (err)
		जाओ CLEANUP_ALLOC;

	err = phy_घातer_on(hsdev->phy);
	अगर (err)
		जाओ CLEANUP_ALLOC;

	क्रम (i = 0; i < SATA_DWC_QCMD_MAX; i++)
		hsdevp->cmd_issued[i] = SATA_DWC_CMD_ISSUED_NOT;

	ap->bmdma_prd = शून्य;	/* set these so libata करोesn't use them */
	ap->bmdma_prd_dma = 0;

	अगर (ap->port_no == 0)  अणु
		dev_dbg(ap->dev, "%s: clearing TXCHEN, RXCHEN in DMAC\n",
			__func__);
		sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr,
				SATA_DWC_DMACR_TXRXCH_CLEAR);

		dev_dbg(ap->dev, "%s: setting burst size in DBTSR\n",
			 __func__);
		sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dbtsr,
				(SATA_DWC_DBTSR_MWR(AHB_DMA_BRST_DFLT) |
				 SATA_DWC_DBTSR_MRD(AHB_DMA_BRST_DFLT)));
	पूर्ण

	/* Clear any error bits beक्रमe libata starts issuing commands */
	clear_serror(ap);
	ap->निजी_data = hsdevp;
	dev_dbg(ap->dev, "%s: done\n", __func__);
	वापस 0;

CLEANUP_ALLOC:
	kमुक्त(hsdevp);
CLEANUP:
	dev_dbg(ap->dev, "%s: fail. ap->id = %d\n", __func__, ap->prपूर्णांक_id);
	वापस err;
पूर्ण

अटल व्योम sata_dwc_port_stop(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_AP(ap);

	dev_dbg(ap->dev, "%s: ap->id = %d\n", __func__, ap->prपूर्णांक_id);

	dmaengine_terminate_sync(hsdevp->chan);
	dma_release_channel(hsdevp->chan);
	phy_घातer_off(hsdev->phy);

	kमुक्त(hsdevp);
	ap->निजी_data = शून्य;
पूर्ण

/*
 * Function : sata_dwc_exec_command_by_tag
 * arguments : ata_port *ap, ata_taskfile *tf, u8 tag, u32 cmd_issued
 * Return value : None
 * This function keeps track of inभागidual command tag ids and calls
 * ata_exec_command in libata
 */
अटल व्योम sata_dwc_exec_command_by_tag(काष्ठा ata_port *ap,
					 काष्ठा ata_taskfile *tf,
					 u8 tag, u32 cmd_issued)
अणु
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);

	dev_dbg(ap->dev, "%s cmd(0x%02x): %s tag=%d\n", __func__, tf->command,
		ata_get_cmd_descript(tf->command), tag);

	hsdevp->cmd_issued[tag] = cmd_issued;

	/*
	 * Clear SError beक्रमe executing a new command.
	 * sata_dwc_scr_ग_लिखो and पढ़ो can not be used here. Clearing the PM
	 * managed SError रेजिस्टर क्रम the disk needs to be करोne beक्रमe the
	 * task file is loaded.
	 */
	clear_serror(ap);
	ata_sff_exec_command(ap, tf);
पूर्ण

अटल व्योम sata_dwc_bmdma_setup_by_tag(काष्ठा ata_queued_cmd *qc, u8 tag)
अणु
	sata_dwc_exec_command_by_tag(qc->ap, &qc->tf, tag,
				     SATA_DWC_CMD_ISSUED_PEND);
पूर्ण

अटल व्योम sata_dwc_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	u8 tag = qc->hw_tag;

	अगर (ata_is_ncq(qc->tf.protocol)) अणु
		dev_dbg(qc->ap->dev, "%s: ap->link.sactive=0x%08x tag=%d\n",
			__func__, qc->ap->link.sactive, tag);
	पूर्ण अन्यथा अणु
		tag = 0;
	पूर्ण
	sata_dwc_bmdma_setup_by_tag(qc, tag);
पूर्ण

अटल व्योम sata_dwc_bmdma_start_by_tag(काष्ठा ata_queued_cmd *qc, u8 tag)
अणु
	पूर्णांक start_dma;
	u32 reg;
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_QC(qc);
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);
	काष्ठा dma_async_tx_descriptor *desc = hsdevp->desc[tag];
	पूर्णांक dir = qc->dma_dir;

	अगर (hsdevp->cmd_issued[tag] != SATA_DWC_CMD_ISSUED_NOT) अणु
		start_dma = 1;
		अगर (dir == DMA_TO_DEVICE)
			hsdevp->dma_pending[tag] = SATA_DWC_DMA_PENDING_TX;
		अन्यथा
			hsdevp->dma_pending[tag] = SATA_DWC_DMA_PENDING_RX;
	पूर्ण अन्यथा अणु
		dev_err(ap->dev,
			"%s: Command not pending cmd_issued=%d (tag=%d) DMA NOT started\n",
			__func__, hsdevp->cmd_issued[tag], tag);
		start_dma = 0;
	पूर्ण

	dev_dbg(ap->dev,
		"%s qc=%p tag: %x cmd: 0x%02x dma_dir: %s start_dma? %x\n",
		__func__, qc, tag, qc->tf.command,
		get_dma_dir_descript(qc->dma_dir), start_dma);
	sata_dwc_tf_dump(ap, &qc->tf);

	अगर (start_dma) अणु
		sata_dwc_scr_पढ़ो(&ap->link, SCR_ERROR, &reg);
		अगर (reg & SATA_DWC_SERROR_ERR_BITS) अणु
			dev_err(ap->dev, "%s: ****** SError=0x%08x ******\n",
				__func__, reg);
		पूर्ण

		अगर (dir == DMA_TO_DEVICE)
			sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr,
					SATA_DWC_DMACR_TXCHEN);
		अन्यथा
			sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr,
					SATA_DWC_DMACR_RXCHEN);

		/* Enable AHB DMA transfer on the specअगरied channel */
		dmaengine_submit(desc);
		dma_async_issue_pending(hsdevp->chan);
	पूर्ण
पूर्ण

अटल व्योम sata_dwc_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	u8 tag = qc->hw_tag;

	अगर (ata_is_ncq(qc->tf.protocol)) अणु
		dev_dbg(qc->ap->dev, "%s: ap->link.sactive=0x%08x tag=%d\n",
			__func__, qc->ap->link.sactive, tag);
	पूर्ण अन्यथा अणु
		tag = 0;
	पूर्ण
	dev_dbg(qc->ap->dev, "%s\n", __func__);
	sata_dwc_bmdma_start_by_tag(qc, tag);
पूर्ण

अटल अचिन्हित पूर्णांक sata_dwc_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	u32 sactive;
	u8 tag = qc->hw_tag;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_dwc_device_port *hsdevp = HSDEVP_FROM_AP(ap);

#अगर_घोषित DEBUG_NCQ
	अगर (qc->hw_tag > 0 || ap->link.sactive > 1)
		dev_info(ap->dev,
			 "%s ap id=%d cmd(0x%02x)=%s qc tag=%d prot=%s ap active_tag=0x%08x ap sactive=0x%08x\n",
			 __func__, ap->prपूर्णांक_id, qc->tf.command,
			 ata_get_cmd_descript(qc->tf.command),
			 qc->hw_tag, get_prot_descript(qc->tf.protocol),
			 ap->link.active_tag, ap->link.sactive);
#पूर्ण_अगर

	अगर (!ata_is_ncq(qc->tf.protocol))
		tag = 0;

	अगर (ata_is_dma(qc->tf.protocol)) अणु
		hsdevp->desc[tag] = dma_dwc_xfer_setup(qc);
		अगर (!hsdevp->desc[tag])
			वापस AC_ERR_SYSTEM;
	पूर्ण अन्यथा अणु
		hsdevp->desc[tag] = शून्य;
	पूर्ण

	अगर (ata_is_ncq(qc->tf.protocol)) अणु
		sata_dwc_scr_पढ़ो(&ap->link, SCR_ACTIVE, &sactive);
		sactive |= (0x00000001 << tag);
		sata_dwc_scr_ग_लिखो(&ap->link, SCR_ACTIVE, sactive);

		dev_dbg(qc->ap->dev,
			"%s: tag=%d ap->link.sactive = 0x%08x sactive=0x%08x\n",
			__func__, tag, qc->ap->link.sactive, sactive);

		ap->ops->sff_tf_load(ap, &qc->tf);
		sata_dwc_exec_command_by_tag(ap, &qc->tf, tag,
					     SATA_DWC_CMD_ISSUED_PEND);
	पूर्ण अन्यथा अणु
		वापस ata_bmdma_qc_issue(qc);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sata_dwc_error_handler(काष्ठा ata_port *ap)
अणु
	ata_sff_error_handler(ap);
पूर्ण

अटल पूर्णांक sata_dwc_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline)
अणु
	काष्ठा sata_dwc_device *hsdev = HSDEV_FROM_AP(link->ap);
	पूर्णांक ret;

	ret = sata_sff_hardreset(link, class, deadline);

	sata_dwc_enable_पूर्णांकerrupts(hsdev);

	/* Reconfigure the DMA control रेजिस्टर */
	sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dmacr,
			SATA_DWC_DMACR_TXRXCH_CLEAR);

	/* Reconfigure the DMA Burst Transaction Size रेजिस्टर */
	sata_dwc_ग_लिखोl(&hsdev->sata_dwc_regs->dbtsr,
			SATA_DWC_DBTSR_MWR(AHB_DMA_BRST_DFLT) |
			SATA_DWC_DBTSR_MRD(AHB_DMA_BRST_DFLT));

	वापस ret;
पूर्ण

अटल व्योम sata_dwc_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	/* SATA DWC is master only */
पूर्ण

/*
 * scsi mid-layer and libata पूर्णांकerface काष्ठाures
 */
अटल काष्ठा scsi_host_ढाँचा sata_dwc_sht = अणु
	ATA_NCQ_SHT(DRV_NAME),
	/*
	 * test-only: Currently this driver करोesn't handle NCQ
	 * correctly. We enable NCQ but set the queue depth to a
	 * max of 1. This will get fixed in in a future release.
	 */
	.sg_tablesize		= LIBATA_MAX_PRD,
	/* .can_queue		= ATA_MAX_QUEUE, */
	/*
	 * Make sure a LLI block is not created that will span 8K max FIS
	 * boundary. If the block spans such a FIS boundary, there is a chance
	 * that a DMA burst will cross that boundary -- this results in an
	 * error in the host controller.
	 */
	.dma_boundary		= 0x1fff /* ATA_DMA_BOUNDARY */,
पूर्ण;

अटल काष्ठा ata_port_operations sata_dwc_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.error_handler		= sata_dwc_error_handler,
	.hardreset		= sata_dwc_hardreset,

	.qc_issue		= sata_dwc_qc_issue,

	.scr_पढ़ो		= sata_dwc_scr_पढ़ो,
	.scr_ग_लिखो		= sata_dwc_scr_ग_लिखो,

	.port_start		= sata_dwc_port_start,
	.port_stop		= sata_dwc_port_stop,

	.sff_dev_select		= sata_dwc_dev_select,

	.bmdma_setup		= sata_dwc_bmdma_setup,
	.bmdma_start		= sata_dwc_bmdma_start,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info sata_dwc_port_info[] = अणु
	अणु
		.flags		= ATA_FLAG_SATA | ATA_FLAG_NCQ,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &sata_dwc_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sata_dwc_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा sata_dwc_device *hsdev;
	u32 idr, versionr;
	अक्षर *ver = (अक्षर *)&versionr;
	व्योम __iomem *base;
	पूर्णांक err = 0;
	पूर्णांक irq;
	काष्ठा ata_host *host;
	काष्ठा ata_port_info pi = sata_dwc_port_info[0];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा resource *res;

	/* Allocate DWC SATA device */
	host = ata_host_alloc_pinfo(&ofdev->dev, ppi, SATA_DWC_MAX_PORTS);
	hsdev = devm_kzalloc(&ofdev->dev, माप(*hsdev), GFP_KERNEL);
	अगर (!host || !hsdev)
		वापस -ENOMEM;

	host->निजी_data = hsdev;

	/* Ioremap SATA रेजिस्टरs */
	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&ofdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	dev_dbg(&ofdev->dev, "ioremap done for SATA register address\n");

	/* Synopsys DWC SATA specअगरic Registers */
	hsdev->sata_dwc_regs = base + SATA_DWC_REG_OFFSET;
	hsdev->dmadr = res->start + SATA_DWC_REG_OFFSET + दुरत्व(काष्ठा sata_dwc_regs, dmadr);

	/* Setup port */
	host->ports[0]->ioaddr.cmd_addr = base;
	host->ports[0]->ioaddr.scr_addr = base + SATA_DWC_SCR_OFFSET;
	sata_dwc_setup_port(&host->ports[0]->ioaddr, base);

	/* Read the ID and Version Registers */
	idr = sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->idr);
	versionr = sata_dwc_पढ़ोl(&hsdev->sata_dwc_regs->versionr);
	dev_notice(&ofdev->dev, "id %d, controller version %c.%c%c\n",
		   idr, ver[0], ver[1], ver[2]);

	/* Save dev क्रम later use in dev_xxx() routines */
	hsdev->dev = &ofdev->dev;

	/* Enable SATA Interrupts */
	sata_dwc_enable_पूर्णांकerrupts(hsdev);

	/* Get SATA पूर्णांकerrupt number */
	irq = irq_of_parse_and_map(np, 0);
	अगर (irq == NO_IRQ) अणु
		dev_err(&ofdev->dev, "no SATA DMA irq\n");
		err = -ENODEV;
		जाओ error_out;
	पूर्ण

#अगर_घोषित CONFIG_SATA_DWC_OLD_DMA
	अगर (!of_find_property(np, "dmas", शून्य)) अणु
		err = sata_dwc_dma_init_old(ofdev, hsdev);
		अगर (err)
			जाओ error_out;
	पूर्ण
#पूर्ण_अगर

	hsdev->phy = devm_phy_optional_get(hsdev->dev, "sata-phy");
	अगर (IS_ERR(hsdev->phy)) अणु
		err = PTR_ERR(hsdev->phy);
		hsdev->phy = शून्य;
		जाओ error_out;
	पूर्ण

	err = phy_init(hsdev->phy);
	अगर (err)
		जाओ error_out;

	/*
	 * Now, रेजिस्टर with libATA core, this will also initiate the
	 * device discovery process, invoking our port_start() handler &
	 * error_handler() to execute a dummy Softreset EH session
	 */
	err = ata_host_activate(host, irq, sata_dwc_isr, 0, &sata_dwc_sht);
	अगर (err)
		dev_err(&ofdev->dev, "failed to activate host");

	वापस 0;

error_out:
	phy_निकास(hsdev->phy);
	वापस err;
पूर्ण

अटल पूर्णांक sata_dwc_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा sata_dwc_device *hsdev = host->निजी_data;

	ata_host_detach(host);

	phy_निकास(hsdev->phy);

#अगर_घोषित CONFIG_SATA_DWC_OLD_DMA
	/* Free SATA DMA resources */
	sata_dwc_dma_निकास_old(hsdev);
#पूर्ण_अगर

	dev_dbg(&ofdev->dev, "done\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sata_dwc_match[] = अणु
	अणु .compatible = "amcc,sata-460ex", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sata_dwc_match);

अटल काष्ठा platक्रमm_driver sata_dwc_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = sata_dwc_match,
	पूर्ण,
	.probe = sata_dwc_probe,
	.हटाओ = sata_dwc_हटाओ,
पूर्ण;

module_platक्रमm_driver(sata_dwc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Miesfeld <mmiesfeld@amcc.com>");
MODULE_DESCRIPTION("DesignWare Cores SATA controller low level driver");
MODULE_VERSION(DRV_VERSION);
