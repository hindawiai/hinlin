<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/ata/sata_fsl.c
 *
 * Freescale 3.0Gbps SATA device driver
 *
 * Author: Ashish Kalra <ashish.kalra@मुक्तscale.com>
 * Li Yang <leoli@मुक्तscale.com>
 *
 * Copyright (c) 2006-2007, 2011-2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

अटल अचिन्हित पूर्णांक पूर्णांकr_coalescing_count;
module_param(पूर्णांकr_coalescing_count, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(पूर्णांकr_coalescing_count,
				 "INT coalescing count threshold (1..31)");

अटल अचिन्हित पूर्णांक पूर्णांकr_coalescing_ticks;
module_param(पूर्णांकr_coalescing_ticks, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(पूर्णांकr_coalescing_ticks,
				 "INT coalescing timer threshold in AHB ticks");
/* Controller inक्रमmation */
क्रमागत अणु
	SATA_FSL_QUEUE_DEPTH	= 16,
	SATA_FSL_MAX_PRD	= 63,
	SATA_FSL_MAX_PRD_USABLE	= SATA_FSL_MAX_PRD - 1,
	SATA_FSL_MAX_PRD_सूचीECT	= 16,	/* Direct PRDT entries */

	SATA_FSL_HOST_FLAGS	= (ATA_FLAG_SATA | ATA_FLAG_PIO_DMA |
				   ATA_FLAG_PMP | ATA_FLAG_NCQ |
				   ATA_FLAG_AN | ATA_FLAG_NO_LOG_PAGE),

	SATA_FSL_MAX_CMDS	= SATA_FSL_QUEUE_DEPTH,
	SATA_FSL_CMD_HDR_SIZE	= 16,	/* 4 DWORDS */
	SATA_FSL_CMD_SLOT_SIZE  = (SATA_FSL_MAX_CMDS * SATA_FSL_CMD_HDR_SIZE),

	/*
	 * SATA-FSL host controller supports a max. of (15+1) direct PRDEs, and
	 * chained indirect PRDEs up to a max count of 63.
	 * We are allocating an array of 63 PRDEs contiguously, but PRDE#15 will
	 * be setup as an indirect descriptor, poपूर्णांकing to it's next
	 * (contiguous) PRDE. Though chained indirect PRDE arrays are
	 * supported,it will be more efficient to use a direct PRDT and
	 * a single chain/link to indirect PRDE array/PRDT.
	 */

	SATA_FSL_CMD_DESC_CFIS_SZ	= 32,
	SATA_FSL_CMD_DESC_SFIS_SZ	= 32,
	SATA_FSL_CMD_DESC_ACMD_SZ	= 16,
	SATA_FSL_CMD_DESC_RSRVD		= 16,

	SATA_FSL_CMD_DESC_SIZE	= (SATA_FSL_CMD_DESC_CFIS_SZ +
				 SATA_FSL_CMD_DESC_SFIS_SZ +
				 SATA_FSL_CMD_DESC_ACMD_SZ +
				 SATA_FSL_CMD_DESC_RSRVD +
				 SATA_FSL_MAX_PRD * 16),

	SATA_FSL_CMD_DESC_OFFSET_TO_PRDT	=
				(SATA_FSL_CMD_DESC_CFIS_SZ +
				 SATA_FSL_CMD_DESC_SFIS_SZ +
				 SATA_FSL_CMD_DESC_ACMD_SZ +
				 SATA_FSL_CMD_DESC_RSRVD),

	SATA_FSL_CMD_DESC_AR_SZ	= (SATA_FSL_CMD_DESC_SIZE * SATA_FSL_MAX_CMDS),
	SATA_FSL_PORT_PRIV_DMA_SZ = (SATA_FSL_CMD_SLOT_SIZE +
					SATA_FSL_CMD_DESC_AR_SZ),

	/*
	 * MPC8315 has two SATA controllers, SATA1 & SATA2
	 * (one port per controller)
	 * MPC837x has 2/4 controllers, one port per controller
	 */

	SATA_FSL_MAX_PORTS	= 1,

	SATA_FSL_IRQ_FLAG	= IRQF_SHARED,
पूर्ण;

/*
 * Interrupt Coalescing Control Register bitdefs  */
क्रमागत अणु
	ICC_MIN_INT_COUNT_THRESHOLD	= 1,
	ICC_MAX_INT_COUNT_THRESHOLD	= ((1 << 5) - 1),
	ICC_MIN_INT_TICKS_THRESHOLD	= 0,
	ICC_MAX_INT_TICKS_THRESHOLD	= ((1 << 19) - 1),
	ICC_SAFE_INT_TICKS		= 1,
पूर्ण;

/*
* Host Controller command रेजिस्टर set - per port
*/
क्रमागत अणु
	CQ = 0,
	CA = 8,
	CC = 0x10,
	CE = 0x18,
	DE = 0x20,
	CHBA = 0x24,
	HSTATUS = 0x28,
	HCONTROL = 0x2C,
	CQPMP = 0x30,
	SIGNATURE = 0x34,
	ICC = 0x38,

	/*
	 * Host Status Register (HStatus) bitdefs
	 */
	ONLINE = (1 << 31),
	GOING_OFFLINE = (1 << 30),
	BIST_ERR = (1 << 29),
	CLEAR_ERROR = (1 << 27),

	FATAL_ERR_HC_MASTER_ERR = (1 << 18),
	FATAL_ERR_PARITY_ERR_TX = (1 << 17),
	FATAL_ERR_PARITY_ERR_RX = (1 << 16),
	FATAL_ERR_DATA_UNDERRUN = (1 << 13),
	FATAL_ERR_DATA_OVERRUN = (1 << 12),
	FATAL_ERR_CRC_ERR_TX = (1 << 11),
	FATAL_ERR_CRC_ERR_RX = (1 << 10),
	FATAL_ERR_FIFO_OVRFL_TX = (1 << 9),
	FATAL_ERR_FIFO_OVRFL_RX = (1 << 8),

	FATAL_ERROR_DECODE = FATAL_ERR_HC_MASTER_ERR |
	    FATAL_ERR_PARITY_ERR_TX |
	    FATAL_ERR_PARITY_ERR_RX |
	    FATAL_ERR_DATA_UNDERRUN |
	    FATAL_ERR_DATA_OVERRUN |
	    FATAL_ERR_CRC_ERR_TX |
	    FATAL_ERR_CRC_ERR_RX |
	    FATAL_ERR_FIFO_OVRFL_TX | FATAL_ERR_FIFO_OVRFL_RX,

	INT_ON_DATA_LENGTH_MISMATCH = (1 << 12),
	INT_ON_FATAL_ERR = (1 << 5),
	INT_ON_PHYRDY_CHG = (1 << 4),

	INT_ON_SIGNATURE_UPDATE = (1 << 3),
	INT_ON_SNOTIFY_UPDATE = (1 << 2),
	INT_ON_SINGL_DEVICE_ERR = (1 << 1),
	INT_ON_CMD_COMPLETE = 1,

	INT_ON_ERROR = INT_ON_FATAL_ERR | INT_ON_SNOTIFY_UPDATE |
	    INT_ON_PHYRDY_CHG | INT_ON_SINGL_DEVICE_ERR,

	/*
	 * Host Control Register (HControl) bitdefs
	 */
	HCONTROL_ONLINE_PHY_RST = (1 << 31),
	HCONTROL_FORCE_OFFLINE = (1 << 30),
	HCONTROL_LEGACY = (1 << 28),
	HCONTROL_PARITY_PROT_MOD = (1 << 14),
	HCONTROL_DPATH_PARITY = (1 << 12),
	HCONTROL_SNOOP_ENABLE = (1 << 10),
	HCONTROL_PMP_ATTACHED = (1 << 9),
	HCONTROL_COPYOUT_STATFIS = (1 << 8),
	IE_ON_FATAL_ERR = (1 << 5),
	IE_ON_PHYRDY_CHG = (1 << 4),
	IE_ON_SIGNATURE_UPDATE = (1 << 3),
	IE_ON_SNOTIFY_UPDATE = (1 << 2),
	IE_ON_SINGL_DEVICE_ERR = (1 << 1),
	IE_ON_CMD_COMPLETE = 1,

	DEFAULT_PORT_IRQ_ENABLE_MASK = IE_ON_FATAL_ERR | IE_ON_PHYRDY_CHG |
	    IE_ON_SIGNATURE_UPDATE | IE_ON_SNOTIFY_UPDATE |
	    IE_ON_SINGL_DEVICE_ERR | IE_ON_CMD_COMPLETE,

	EXT_INसूचीECT_SEG_PRD_FLAG = (1 << 31),
	DATA_SNOOP_ENABLE_V1 = (1 << 22),
	DATA_SNOOP_ENABLE_V2 = (1 << 28),
पूर्ण;

/*
 * SATA Superset Registers
 */
क्रमागत अणु
	SSTATUS = 0,
	SERROR = 4,
	SCONTROL = 8,
	SNOTIFY = 0xC,
पूर्ण;

/*
 * Control Status Register Set
 */
क्रमागत अणु
	TRANSCFG = 0,
	TRANSSTATUS = 4,
	LINKCFG = 8,
	LINKCFG1 = 0xC,
	LINKCFG2 = 0x10,
	LINKSTATUS = 0x14,
	LINKSTATUS1 = 0x18,
	PHYCTRLCFG = 0x1C,
	COMMANDSTAT = 0x20,
पूर्ण;

/* TRANSCFG (transport-layer) configuration control */
क्रमागत अणु
	TRANSCFG_RX_WATER_MARK = (1 << 4),
पूर्ण;

/* PHY (link-layer) configuration control */
क्रमागत अणु
	PHY_BIST_ENABLE = 0x01,
पूर्ण;

/*
 * Command Header Table entry, i.e, command slot
 * 4 Dwords per command slot, command header size ==  64 Dwords.
 */
काष्ठा cmdhdr_tbl_entry अणु
	u32 cda;
	u32 prde_fis_len;
	u32 ttl;
	u32 desc_info;
पूर्ण;

/*
 * Description inक्रमmation bitdefs
 */
क्रमागत अणु
	CMD_DESC_RES = (1 << 11),
	VENDOR_SPECIFIC_BIST = (1 << 10),
	CMD_DESC_SNOOP_ENABLE = (1 << 9),
	FPDMA_QUEUED_CMD = (1 << 8),
	SRST_CMD = (1 << 7),
	BIST = (1 << 6),
	ATAPI_CMD = (1 << 5),
पूर्ण;

/*
 * Command Descriptor
 */
काष्ठा command_desc अणु
	u8 cfis[8 * 4];
	u8 sfis[8 * 4];
	u8 acmd[4 * 4];
	u8 fill[4 * 4];
	u32 prdt[SATA_FSL_MAX_PRD_सूचीECT * 4];
	u32 prdt_indirect[(SATA_FSL_MAX_PRD - SATA_FSL_MAX_PRD_सूचीECT) * 4];
पूर्ण;

/*
 * Physical region table descriptor(PRD)
 */

काष्ठा prde अणु
	u32 dba;
	u8 fill[2 * 4];
	u32 ddc_and_ext;
पूर्ण;

/*
 * ata_port निजी data
 * This is our per-port instance data.
 */
काष्ठा sata_fsl_port_priv अणु
	काष्ठा cmdhdr_tbl_entry *cmdslot;
	dma_addr_t cmdslot_paddr;
	काष्ठा command_desc *cmdentry;
	dma_addr_t cmdentry_paddr;
पूर्ण;

/*
 * ata_port->host_set निजी data
 */
काष्ठा sata_fsl_host_priv अणु
	व्योम __iomem *hcr_base;
	व्योम __iomem *ssr_base;
	व्योम __iomem *csr_base;
	पूर्णांक irq;
	पूर्णांक data_snoop;
	काष्ठा device_attribute पूर्णांकr_coalescing;
	काष्ठा device_attribute rx_watermark;
पूर्ण;

अटल व्योम fsl_sata_set_irq_coalescing(काष्ठा ata_host *host,
		अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक ticks)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	अचिन्हित दीर्घ flags;

	अगर (count > ICC_MAX_INT_COUNT_THRESHOLD)
		count = ICC_MAX_INT_COUNT_THRESHOLD;
	अन्यथा अगर (count < ICC_MIN_INT_COUNT_THRESHOLD)
		count = ICC_MIN_INT_COUNT_THRESHOLD;

	अगर (ticks > ICC_MAX_INT_TICKS_THRESHOLD)
		ticks = ICC_MAX_INT_TICKS_THRESHOLD;
	अन्यथा अगर ((ICC_MIN_INT_TICKS_THRESHOLD == ticks) &&
			(count > ICC_MIN_INT_COUNT_THRESHOLD))
		ticks = ICC_SAFE_INT_TICKS;

	spin_lock_irqsave(&host->lock, flags);
	ioग_लिखो32((count << 24 | ticks), hcr_base + ICC);

	पूर्णांकr_coalescing_count = count;
	पूर्णांकr_coalescing_ticks = ticks;
	spin_unlock_irqrestore(&host->lock, flags);

	DPRINTK("interrupt coalescing, count = 0x%x, ticks = %x\n",
			पूर्णांकr_coalescing_count, पूर्णांकr_coalescing_ticks);
	DPRINTK("ICC register status: (hcr base: 0x%x) = 0x%x\n",
			hcr_base, ioपढ़ो32(hcr_base + ICC));
पूर्ण

अटल sमाप_प्रकार fsl_sata_पूर्णांकr_coalescing_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d	%d\n",
			पूर्णांकr_coalescing_count, पूर्णांकr_coalescing_ticks);
पूर्ण

अटल sमाप_प्रकार fsl_sata_पूर्णांकr_coalescing_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक coalescing_count,	coalescing_ticks;

	अगर (माला_पूछो(buf, "%d%d",
				&coalescing_count,
				&coalescing_ticks) != 2) अणु
		prपूर्णांकk(KERN_ERR "fsl-sata: wrong parameter format.\n");
		वापस -EINVAL;
	पूर्ण

	fsl_sata_set_irq_coalescing(dev_get_drvdata(dev),
			coalescing_count, coalescing_ticks);

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार fsl_sata_rx_watermark_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक rx_watermark;
	अचिन्हित दीर्घ flags;
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;
	व्योम __iomem *csr_base = host_priv->csr_base;

	spin_lock_irqsave(&host->lock, flags);
	rx_watermark = ioपढ़ो32(csr_base + TRANSCFG);
	rx_watermark &= 0x1f;

	spin_unlock_irqrestore(&host->lock, flags);
	वापस प्र_लिखो(buf, "%d\n", rx_watermark);
पूर्ण

अटल sमाप_प्रकार fsl_sata_rx_watermark_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक rx_watermark;
	अचिन्हित दीर्घ flags;
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;
	व्योम __iomem *csr_base = host_priv->csr_base;
	u32 temp;

	अगर (माला_पूछो(buf, "%d", &rx_watermark) != 1) अणु
		prपूर्णांकk(KERN_ERR "fsl-sata: wrong parameter format.\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);
	temp = ioपढ़ो32(csr_base + TRANSCFG);
	temp &= 0xffffffe0;
	ioग_लिखो32(temp | rx_watermark, csr_base + TRANSCFG);

	spin_unlock_irqrestore(&host->lock, flags);
	वापस म_माप(buf);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sata_fsl_tag(अचिन्हित पूर्णांक tag,
					व्योम __iomem *hcr_base)
अणु
	/* We let libATA core करो actual (queue) tag allocation */

	अगर (unlikely(tag >= SATA_FSL_QUEUE_DEPTH)) अणु
		DPRINTK("tag %d invalid : out of range\n", tag);
		वापस 0;
	पूर्ण

	अगर (unlikely((ioपढ़ो32(hcr_base + CQ)) & (1 << tag))) अणु
		DPRINTK("tag %d invalid : in use!!\n", tag);
		वापस 0;
	पूर्ण

	वापस tag;
पूर्ण

अटल व्योम sata_fsl_setup_cmd_hdr_entry(काष्ठा sata_fsl_port_priv *pp,
					 अचिन्हित पूर्णांक tag, u32 desc_info,
					 u32 data_xfer_len, u8 num_prde,
					 u8 fis_len)
अणु
	dma_addr_t cmd_descriptor_address;

	cmd_descriptor_address = pp->cmdentry_paddr +
	    tag * SATA_FSL_CMD_DESC_SIZE;

	/* NOTE: both data_xfer_len & fis_len are Dword counts */

	pp->cmdslot[tag].cda = cpu_to_le32(cmd_descriptor_address);
	pp->cmdslot[tag].prde_fis_len =
	    cpu_to_le32((num_prde << 16) | (fis_len << 2));
	pp->cmdslot[tag].ttl = cpu_to_le32(data_xfer_len & ~0x03);
	pp->cmdslot[tag].desc_info = cpu_to_le32(desc_info | (tag & 0x1F));

	VPRINTK("cda=0x%x, prde_fis_len=0x%x, ttl=0x%x, di=0x%x\n",
		pp->cmdslot[tag].cda,
		pp->cmdslot[tag].prde_fis_len,
		pp->cmdslot[tag].ttl, pp->cmdslot[tag].desc_info);

पूर्ण

अटल अचिन्हित पूर्णांक sata_fsl_fill_sg(काष्ठा ata_queued_cmd *qc, व्योम *cmd_desc,
				     u32 *ttl, dma_addr_t cmd_desc_paddr,
				     पूर्णांक data_snoop)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक num_prde = 0;
	u32 ttl_dwords = 0;

	/*
	 * NOTE : direct & indirect prdt's are contiguously allocated
	 */
	काष्ठा prde *prd = (काष्ठा prde *)&((काष्ठा command_desc *)
					    cmd_desc)->prdt;

	काष्ठा prde *prd_ptr_to_indirect_ext = शून्य;
	अचिन्हित indirect_ext_segment_sz = 0;
	dma_addr_t indirect_ext_segment_paddr;
	अचिन्हित पूर्णांक si;

	VPRINTK("SATA FSL : cd = 0x%p, prd = 0x%p\n", cmd_desc, prd);

	indirect_ext_segment_paddr = cmd_desc_paddr +
	    SATA_FSL_CMD_DESC_OFFSET_TO_PRDT + SATA_FSL_MAX_PRD_सूचीECT * 16;

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		dma_addr_t sg_addr = sg_dma_address(sg);
		u32 sg_len = sg_dma_len(sg);

		VPRINTK("SATA FSL : fill_sg, sg_addr = 0x%llx, sg_len = %d\n",
			(अचिन्हित दीर्घ दीर्घ)sg_addr, sg_len);

		/* warn अगर each s/g element is not dword aligned */
		अगर (unlikely(sg_addr & 0x03))
			ata_port_err(qc->ap, "s/g addr unaligned : 0x%llx\n",
				     (अचिन्हित दीर्घ दीर्घ)sg_addr);
		अगर (unlikely(sg_len & 0x03))
			ata_port_err(qc->ap, "s/g len unaligned : 0x%x\n",
				     sg_len);

		अगर (num_prde == (SATA_FSL_MAX_PRD_सूचीECT - 1) &&
		    sg_next(sg) != शून्य) अणु
			VPRINTK("setting indirect prde\n");
			prd_ptr_to_indirect_ext = prd;
			prd->dba = cpu_to_le32(indirect_ext_segment_paddr);
			indirect_ext_segment_sz = 0;
			++prd;
			++num_prde;
		पूर्ण

		ttl_dwords += sg_len;
		prd->dba = cpu_to_le32(sg_addr);
		prd->ddc_and_ext = cpu_to_le32(data_snoop | (sg_len & ~0x03));

		VPRINTK("sg_fill, ttl=%d, dba=0x%x, ddc=0x%x\n",
			ttl_dwords, prd->dba, prd->ddc_and_ext);

		++num_prde;
		++prd;
		अगर (prd_ptr_to_indirect_ext)
			indirect_ext_segment_sz += sg_len;
	पूर्ण

	अगर (prd_ptr_to_indirect_ext) अणु
		/* set indirect extension flag aदीर्घ with indirect ext. size */
		prd_ptr_to_indirect_ext->ddc_and_ext =
		    cpu_to_le32((EXT_INसूचीECT_SEG_PRD_FLAG |
				 data_snoop |
				 (indirect_ext_segment_sz & ~0x03)));
	पूर्ण

	*ttl = ttl_dwords;
	वापस num_prde;
पूर्ण

अटल क्रमागत ata_completion_errors sata_fsl_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_fsl_port_priv *pp = ap->निजी_data;
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	अचिन्हित पूर्णांक tag = sata_fsl_tag(qc->hw_tag, hcr_base);
	काष्ठा command_desc *cd;
	u32 desc_info = CMD_DESC_RES | CMD_DESC_SNOOP_ENABLE;
	u32 num_prde = 0;
	u32 ttl_dwords = 0;
	dma_addr_t cd_paddr;

	cd = (काष्ठा command_desc *)pp->cmdentry + tag;
	cd_paddr = pp->cmdentry_paddr + tag * SATA_FSL_CMD_DESC_SIZE;

	ata_tf_to_fis(&qc->tf, qc->dev->link->pmp, 1, (u8 *) &cd->cfis);

	VPRINTK("Dumping cfis : 0x%x, 0x%x, 0x%x\n",
		cd->cfis[0], cd->cfis[1], cd->cfis[2]);

	अगर (qc->tf.protocol == ATA_PROT_NCQ) अणु
		VPRINTK("FPDMA xfer,Sctor cnt[0:7],[8:15] = %d,%d\n",
			cd->cfis[3], cd->cfis[11]);
	पूर्ण

	/* setup "ACMD - atapi command" in cmd. desc. अगर this is ATAPI cmd */
	अगर (ata_is_atapi(qc->tf.protocol)) अणु
		desc_info |= ATAPI_CMD;
		स_रखो((व्योम *)&cd->acmd, 0, 32);
		स_नकल((व्योम *)&cd->acmd, qc->cdb, qc->dev->cdb_len);
	पूर्ण

	अगर (qc->flags & ATA_QCFLAG_DMAMAP)
		num_prde = sata_fsl_fill_sg(qc, (व्योम *)cd,
					    &ttl_dwords, cd_paddr,
					    host_priv->data_snoop);

	अगर (qc->tf.protocol == ATA_PROT_NCQ)
		desc_info |= FPDMA_QUEUED_CMD;

	sata_fsl_setup_cmd_hdr_entry(pp, tag, desc_info, ttl_dwords,
				     num_prde, 5);

	VPRINTK("SATA FSL : xx_qc_prep, di = 0x%x, ttl = %d, num_prde = %d\n",
		desc_info, ttl_dwords, num_prde);

	वापस AC_ERR_OK;
पूर्ण

अटल अचिन्हित पूर्णांक sata_fsl_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	अचिन्हित पूर्णांक tag = sata_fsl_tag(qc->hw_tag, hcr_base);

	VPRINTK("xx_qc_issue called,CQ=0x%x,CA=0x%x,CE=0x%x,CC=0x%x\n",
		ioपढ़ो32(CQ + hcr_base),
		ioपढ़ो32(CA + hcr_base),
		ioपढ़ो32(CE + hcr_base), ioपढ़ो32(CC + hcr_base));

	ioग_लिखो32(qc->dev->link->pmp, CQPMP + hcr_base);

	/* Simply queue command to the controller/device */
	ioग_लिखो32(1 << tag, CQ + hcr_base);

	VPRINTK("xx_qc_issue called, tag=%d, CQ=0x%x, CA=0x%x\n",
		tag, ioपढ़ो32(CQ + hcr_base), ioपढ़ो32(CA + hcr_base));

	VPRINTK("CE=0x%x, DE=0x%x, CC=0x%x, CmdStat = 0x%x\n",
		ioपढ़ो32(CE + hcr_base),
		ioपढ़ो32(DE + hcr_base),
		ioपढ़ो32(CC + hcr_base),
		ioपढ़ो32(COMMANDSTAT + host_priv->csr_base));

	वापस 0;
पूर्ण

अटल bool sata_fsl_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा sata_fsl_port_priv *pp = qc->ap->निजी_data;
	काष्ठा sata_fsl_host_priv *host_priv = qc->ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	अचिन्हित पूर्णांक tag = sata_fsl_tag(qc->hw_tag, hcr_base);
	काष्ठा command_desc *cd;

	cd = pp->cmdentry + tag;

	ata_tf_from_fis(cd->sfis, &qc->result_tf);
	वापस true;
पूर्ण

अटल पूर्णांक sata_fsl_scr_ग_लिखो(काष्ठा ata_link *link,
			      अचिन्हित पूर्णांक sc_reg_in, u32 val)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = link->ap->host->निजी_data;
	व्योम __iomem *ssr_base = host_priv->ssr_base;
	अचिन्हित पूर्णांक sc_reg;

	चयन (sc_reg_in) अणु
	हाल SCR_STATUS:
	हाल SCR_ERROR:
	हाल SCR_CONTROL:
	हाल SCR_ACTIVE:
		sc_reg = sc_reg_in;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	VPRINTK("xx_scr_write, reg_in = %d\n", sc_reg);

	ioग_लिखो32(val, ssr_base + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक sata_fsl_scr_पढ़ो(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक sc_reg_in, u32 *val)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = link->ap->host->निजी_data;
	व्योम __iomem *ssr_base = host_priv->ssr_base;
	अचिन्हित पूर्णांक sc_reg;

	चयन (sc_reg_in) अणु
	हाल SCR_STATUS:
	हाल SCR_ERROR:
	हाल SCR_CONTROL:
	हाल SCR_ACTIVE:
		sc_reg = sc_reg_in;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	VPRINTK("xx_scr_read, reg_in = %d\n", sc_reg);

	*val = ioपढ़ो32(ssr_base + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल व्योम sata_fsl_मुक्तze(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	VPRINTK("xx_freeze, CQ=0x%x, CA=0x%x, CE=0x%x, DE=0x%x\n",
		ioपढ़ो32(CQ + hcr_base),
		ioपढ़ो32(CA + hcr_base),
		ioपढ़ो32(CE + hcr_base), ioपढ़ो32(DE + hcr_base));
	VPRINTK("CmdStat = 0x%x\n",
		ioपढ़ो32(host_priv->csr_base + COMMANDSTAT));

	/* disable पूर्णांकerrupts on the controller/port */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32((temp & ~0x3F), hcr_base + HCONTROL);

	VPRINTK("in xx_freeze : HControl = 0x%x, HStatus = 0x%x\n",
		ioपढ़ो32(hcr_base + HCONTROL), ioपढ़ो32(hcr_base + HSTATUS));
पूर्ण

अटल व्योम sata_fsl_thaw(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	/* ack. any pending IRQs क्रम this controller/port */
	temp = ioपढ़ो32(hcr_base + HSTATUS);

	VPRINTK("xx_thaw, pending IRQs = 0x%x\n", (temp & 0x3F));

	अगर (temp & 0x3F)
		ioग_लिखो32((temp & 0x3F), hcr_base + HSTATUS);

	/* enable पूर्णांकerrupts on the controller/port */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32((temp | DEFAULT_PORT_IRQ_ENABLE_MASK), hcr_base + HCONTROL);

	VPRINTK("xx_thaw : HControl = 0x%x, HStatus = 0x%x\n",
		ioपढ़ो32(hcr_base + HCONTROL), ioपढ़ो32(hcr_base + HSTATUS));
पूर्ण

अटल व्योम sata_fsl_pmp_attach(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32((temp | HCONTROL_PMP_ATTACHED), hcr_base + HCONTROL);
पूर्ण

अटल व्योम sata_fsl_pmp_detach(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	temp = ioपढ़ो32(hcr_base + HCONTROL);
	temp &= ~HCONTROL_PMP_ATTACHED;
	ioग_लिखो32(temp, hcr_base + HCONTROL);

	/* enable पूर्णांकerrupts on the controller/port */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32((temp | DEFAULT_PORT_IRQ_ENABLE_MASK), hcr_base + HCONTROL);

पूर्ण

अटल पूर्णांक sata_fsl_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा sata_fsl_port_priv *pp;
	व्योम *mem;
	dma_addr_t mem_dma;
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	pp = kzalloc(माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	mem = dma_alloc_coherent(dev, SATA_FSL_PORT_PRIV_DMA_SZ, &mem_dma,
				 GFP_KERNEL);
	अगर (!mem) अणु
		kमुक्त(pp);
		वापस -ENOMEM;
	पूर्ण

	pp->cmdslot = mem;
	pp->cmdslot_paddr = mem_dma;

	mem += SATA_FSL_CMD_SLOT_SIZE;
	mem_dma += SATA_FSL_CMD_SLOT_SIZE;

	pp->cmdentry = mem;
	pp->cmdentry_paddr = mem_dma;

	ap->निजी_data = pp;

	VPRINTK("CHBA = 0x%x, cmdentry_phys = 0x%x\n",
		pp->cmdslot_paddr, pp->cmdentry_paddr);

	/* Now, update the CHBA रेजिस्टर in host controller cmd रेजिस्टर set */
	ioग_लिखो32(pp->cmdslot_paddr & 0xffffffff, hcr_base + CHBA);

	/*
	 * Now, we can bring the controller on-line & also initiate
	 * the COMINIT sequence, we simply वापस here and the boot-probing
	 * & device discovery process is re-initiated by libATA using a
	 * Softreset EH (dummy) session. Hence, boot probing and device
	 * discovey will be part of sata_fsl_softreset() callback.
	 */

	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32((temp | HCONTROL_ONLINE_PHY_RST), hcr_base + HCONTROL);

	VPRINTK("HStatus = 0x%x\n", ioपढ़ो32(hcr_base + HSTATUS));
	VPRINTK("HControl = 0x%x\n", ioपढ़ो32(hcr_base + HCONTROL));
	VPRINTK("CHBA  = 0x%x\n", ioपढ़ो32(hcr_base + CHBA));

	वापस 0;
पूर्ण

अटल व्योम sata_fsl_port_stop(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा sata_fsl_port_priv *pp = ap->निजी_data;
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	/*
	 * Force host controller to go off-line, पातing current operations
	 */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	temp &= ~HCONTROL_ONLINE_PHY_RST;
	temp |= HCONTROL_FORCE_OFFLINE;
	ioग_लिखो32(temp, hcr_base + HCONTROL);

	/* Poll क्रम controller to go offline - should happen immediately */
	ata_रुको_रेजिस्टर(ap, hcr_base + HSTATUS, ONLINE, ONLINE, 1, 1);

	ap->निजी_data = शून्य;
	dma_मुक्त_coherent(dev, SATA_FSL_PORT_PRIV_DMA_SZ,
			  pp->cmdslot, pp->cmdslot_paddr);

	kमुक्त(pp);
पूर्ण

अटल अचिन्हित पूर्णांक sata_fsl_dev_classअगरy(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	काष्ठा ata_taskfile tf;
	u32 temp;

	temp = ioपढ़ो32(hcr_base + SIGNATURE);

	VPRINTK("raw sig = 0x%x\n", temp);
	VPRINTK("HStatus = 0x%x\n", ioपढ़ो32(hcr_base + HSTATUS));
	VPRINTK("HControl = 0x%x\n", ioपढ़ो32(hcr_base + HCONTROL));

	tf.lbah = (temp >> 24) & 0xff;
	tf.lbam = (temp >> 16) & 0xff;
	tf.lbal = (temp >> 8) & 0xff;
	tf.nsect = temp & 0xff;

	वापस ata_dev_classअगरy(&tf);
पूर्ण

अटल पूर्णांक sata_fsl_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
					अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ start_jअगरfies;

	DPRINTK("in xx_hardreset\n");

try_offline_again:
	/*
	 * Force host controller to go off-line, पातing current operations
	 */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	temp &= ~HCONTROL_ONLINE_PHY_RST;
	ioग_लिखो32(temp, hcr_base + HCONTROL);

	/* Poll क्रम controller to go offline */
	temp = ata_रुको_रेजिस्टर(ap, hcr_base + HSTATUS, ONLINE, ONLINE,
				 1, 500);

	अगर (temp & ONLINE) अणु
		ata_port_err(ap, "Hardreset failed, not off-lined %d\n", i);

		/*
		 * Try to offline controller atleast twice
		 */
		i++;
		अगर (i == 2)
			जाओ err;
		अन्यथा
			जाओ try_offline_again;
	पूर्ण

	DPRINTK("hardreset, controller off-lined\n");
	VPRINTK("HStatus = 0x%x\n", ioपढ़ो32(hcr_base + HSTATUS));
	VPRINTK("HControl = 0x%x\n", ioपढ़ो32(hcr_base + HCONTROL));

	/*
	 * PHY reset should reमुख्य निश्चितed क्रम atleast 1ms
	 */
	ata_msleep(ap, 1);

	sata_set_spd(link);

	/*
	 * Now, bring the host controller online again, this can take समय
	 * as PHY reset and communication establishment, 1st D2H FIS and
	 * device signature update is करोne, on safe side assume 500ms
	 * NOTE : Host online status may be indicated immediately!!
	 */

	temp = ioपढ़ो32(hcr_base + HCONTROL);
	temp |= (HCONTROL_ONLINE_PHY_RST | HCONTROL_SNOOP_ENABLE);
	temp |= HCONTROL_PMP_ATTACHED;
	ioग_लिखो32(temp, hcr_base + HCONTROL);

	temp = ata_रुको_रेजिस्टर(ap, hcr_base + HSTATUS, ONLINE, 0, 1, 500);

	अगर (!(temp & ONLINE)) अणु
		ata_port_err(ap, "Hardreset failed, not on-lined\n");
		जाओ err;
	पूर्ण

	DPRINTK("hardreset, controller off-lined & on-lined\n");
	VPRINTK("HStatus = 0x%x\n", ioपढ़ो32(hcr_base + HSTATUS));
	VPRINTK("HControl = 0x%x\n", ioपढ़ो32(hcr_base + HCONTROL));

	/*
	 * First, रुको क्रम the PHYRDY change to occur beक्रमe रुकोing क्रम
	 * the signature, and also verअगरy अगर SStatus indicates device
	 * presence
	 */

	temp = ata_रुको_रेजिस्टर(ap, hcr_base + HSTATUS, 0xFF, 0, 1, 500);
	अगर ((!(temp & 0x10)) || ata_link_offline(link)) अणु
		ata_port_warn(ap, "No Device OR PHYRDY change,Hstatus = 0x%x\n",
			      ioपढ़ो32(hcr_base + HSTATUS));
		*class = ATA_DEV_NONE;
		वापस 0;
	पूर्ण

	/*
	 * Wait क्रम the first D2H from device,i.e,signature update notअगरication
	 */
	start_jअगरfies = jअगरfies;
	temp = ata_रुको_रेजिस्टर(ap, hcr_base + HSTATUS, 0xFF, 0x10,
			500, jअगरfies_to_msecs(deadline - start_jअगरfies));

	अगर ((temp & 0xFF) != 0x18) अणु
		ata_port_warn(ap, "No Signature Update\n");
		*class = ATA_DEV_NONE;
		जाओ करो_followup_srst;
	पूर्ण अन्यथा अणु
		ata_port_info(ap, "Signature Update detected @ %d msecs\n",
			      jअगरfies_to_msecs(jअगरfies - start_jअगरfies));
		*class = sata_fsl_dev_classअगरy(ap);
		वापस 0;
	पूर्ण

करो_followup_srst:
	/*
	 * request libATA to perक्रमm follow-up softreset
	 */
	वापस -EAGAIN;

err:
	वापस -EIO;
पूर्ण

अटल पूर्णांक sata_fsl_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
					अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा sata_fsl_port_priv *pp = ap->निजी_data;
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	पूर्णांक pmp = sata_srst_pmp(link);
	u32 temp;
	काष्ठा ata_taskfile tf;
	u8 *cfis;
	u32 Serror;

	DPRINTK("in xx_softreset\n");

	अगर (ata_link_offline(link)) अणु
		DPRINTK("PHY reports no device\n");
		*class = ATA_DEV_NONE;
		वापस 0;
	पूर्ण

	/*
	 * Send a device reset (SRST) explicitly on command slot #0
	 * Check : will the command queue (reg) be cleared during offlining ??
	 * Also we will be online only अगर Phy commn. has been established
	 * and device presence has been detected, thereक्रमe अगर we have
	 * reached here, we can send a command to the target device
	 */

	DPRINTK("Sending SRST/device reset\n");

	ata_tf_init(link->device, &tf);
	cfis = (u8 *) &pp->cmdentry->cfis;

	/* device reset/SRST is a control रेजिस्टर update FIS, uses tag0 */
	sata_fsl_setup_cmd_hdr_entry(pp, 0,
		SRST_CMD | CMD_DESC_RES | CMD_DESC_SNOOP_ENABLE, 0, 0, 5);

	tf.ctl |= ATA_SRST;	/* setup SRST bit in taskfile control reg */
	ata_tf_to_fis(&tf, pmp, 0, cfis);

	DPRINTK("Dumping cfis : 0x%x, 0x%x, 0x%x, 0x%x\n",
		cfis[0], cfis[1], cfis[2], cfis[3]);

	/*
	 * Queue SRST command to the controller/device, ensure that no
	 * other commands are active on the controller/device
	 */

	DPRINTK("@Softreset, CQ = 0x%x, CA = 0x%x, CC = 0x%x\n",
		ioपढ़ो32(CQ + hcr_base),
		ioपढ़ो32(CA + hcr_base), ioपढ़ो32(CC + hcr_base));

	ioग_लिखो32(0xFFFF, CC + hcr_base);
	अगर (pmp != SATA_PMP_CTRL_PORT)
		ioग_लिखो32(pmp, CQPMP + hcr_base);
	ioग_लिखो32(1, CQ + hcr_base);

	temp = ata_रुको_रेजिस्टर(ap, CQ + hcr_base, 0x1, 0x1, 1, 5000);
	अगर (temp & 0x1) अणु
		ata_port_warn(ap, "ATA_SRST issue failed\n");

		DPRINTK("Softreset@5000,CQ=0x%x,CA=0x%x,CC=0x%x\n",
			ioपढ़ो32(CQ + hcr_base),
			ioपढ़ो32(CA + hcr_base), ioपढ़ो32(CC + hcr_base));

		sata_fsl_scr_पढ़ो(&ap->link, SCR_ERROR, &Serror);

		DPRINTK("HStatus = 0x%x\n", ioपढ़ो32(hcr_base + HSTATUS));
		DPRINTK("HControl = 0x%x\n", ioपढ़ो32(hcr_base + HCONTROL));
		DPRINTK("Serror = 0x%x\n", Serror);
		जाओ err;
	पूर्ण

	ata_msleep(ap, 1);

	/*
	 * SATA device enters reset state after receiving a Control रेजिस्टर
	 * FIS with SRST bit निश्चितed and it aरुकोs another H2D Control reg.
	 * FIS with SRST bit cleared, then the device करोes पूर्णांकernal diags &
	 * initialization, followed by indicating it's initialization status
	 * using ATA signature D2H रेजिस्टर FIS to the host controller.
	 */

	sata_fsl_setup_cmd_hdr_entry(pp, 0, CMD_DESC_RES | CMD_DESC_SNOOP_ENABLE,
				      0, 0, 5);

	tf.ctl &= ~ATA_SRST;	/* 2nd H2D Ctl. रेजिस्टर FIS */
	ata_tf_to_fis(&tf, pmp, 0, cfis);

	अगर (pmp != SATA_PMP_CTRL_PORT)
		ioग_लिखो32(pmp, CQPMP + hcr_base);
	ioग_लिखो32(1, CQ + hcr_base);
	ata_msleep(ap, 150);		/* ?? */

	/*
	 * The above command would have संकेतled an पूर्णांकerrupt on command
	 * complete, which needs special handling, by clearing the Nth
	 * command bit of the CCreg
	 */
	ioग_लिखो32(0x01, CC + hcr_base);	/* We know it will be cmd#0 always */

	DPRINTK("SATA FSL : Now checking device signature\n");

	*class = ATA_DEV_NONE;

	/* Verअगरy अगर SStatus indicates device presence */
	अगर (ata_link_online(link)) अणु
		/*
		 * अगर we are here, device presence has been detected,
		 * 1st D2H FIS would have been received, but sfis in
		 * command desc. is not updated, but signature रेजिस्टर
		 * would have been updated
		 */

		*class = sata_fsl_dev_classअगरy(ap);

		DPRINTK("class = %d\n", *class);
		VPRINTK("ccreg = 0x%x\n", ioपढ़ो32(hcr_base + CC));
		VPRINTK("cereg = 0x%x\n", ioपढ़ो32(hcr_base + CE));
	पूर्ण

	वापस 0;

err:
	वापस -EIO;
पूर्ण

अटल व्योम sata_fsl_error_handler(काष्ठा ata_port *ap)
अणु

	DPRINTK("in xx_error_handler\n");
	sata_pmp_error_handler(ap);

पूर्ण

अटल व्योम sata_fsl_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->flags & ATA_QCFLAG_FAILED)
		qc->err_mask |= AC_ERR_OTHER;

	अगर (qc->err_mask) अणु
		/* make DMA engine क्रमget about the failed command */

	पूर्ण
पूर्ण

अटल व्योम sata_fsl_error_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 hstatus, dereg=0, cereg = 0, SError = 0;
	अचिन्हित पूर्णांक err_mask = 0, action = 0;
	पूर्णांक मुक्तze = 0, पात=0;
	काष्ठा ata_link *link = शून्य;
	काष्ठा ata_queued_cmd *qc = शून्य;
	काष्ठा ata_eh_info *ehi;

	hstatus = ioपढ़ो32(hcr_base + HSTATUS);
	cereg = ioपढ़ो32(hcr_base + CE);

	/* first, analyze and record host port events */
	link = &ap->link;
	ehi = &link->eh_info;
	ata_ehi_clear_desc(ehi);

	/*
	 * Handle & Clear SError
	 */

	sata_fsl_scr_पढ़ो(&ap->link, SCR_ERROR, &SError);
	अगर (unlikely(SError & 0xFFFF0000))
		sata_fsl_scr_ग_लिखो(&ap->link, SCR_ERROR, SError);

	DPRINTK("error_intr,hStat=0x%x,CE=0x%x,DE =0x%x,SErr=0x%x\n",
		hstatus, cereg, ioपढ़ो32(hcr_base + DE), SError);

	/* handle fatal errors */
	अगर (hstatus & FATAL_ERROR_DECODE) अणु
		ehi->err_mask |= AC_ERR_ATA_BUS;
		ehi->action |= ATA_EH_SOFTRESET;

		मुक्तze = 1;
	पूर्ण

	/* Handle SDB FIS receive & notअगरy update */
	अगर (hstatus & INT_ON_SNOTIFY_UPDATE)
		sata_async_notअगरication(ap);

	/* Handle PHYRDY change notअगरication */
	अगर (hstatus & INT_ON_PHYRDY_CHG) अणु
		DPRINTK("SATA FSL: PHYRDY change indication\n");

		/* Setup a soft-reset EH action */
		ata_ehi_hotplugged(ehi);
		ata_ehi_push_desc(ehi, "%s", "PHY RDY changed");
		मुक्तze = 1;
	पूर्ण

	/* handle single device errors */
	अगर (cereg) अणु
		/*
		 * clear the command error, also clears queue to the device
		 * in error, and we can (re)issue commands to this device.
		 * When a device is in error all commands queued पूर्णांकo the
		 * host controller and at the device are considered पातed
		 * and the queue क्रम that device is stopped. Now, after
		 * clearing the device error, we can issue commands to the
		 * device to पूर्णांकerrogate it to find the source of the error.
		 */
		पात = 1;

		DPRINTK("single device error, CE=0x%x, DE=0x%x\n",
			ioपढ़ो32(hcr_base + CE), ioपढ़ो32(hcr_base + DE));

		/* find out the offending link and qc */
		अगर (ap->nr_pmp_links) अणु
			अचिन्हित पूर्णांक dev_num;

			dereg = ioपढ़ो32(hcr_base + DE);
			ioग_लिखो32(dereg, hcr_base + DE);
			ioग_लिखो32(cereg, hcr_base + CE);

			dev_num = ffs(dereg) - 1;
			अगर (dev_num < ap->nr_pmp_links && dereg != 0) अणु
				link = &ap->pmp_link[dev_num];
				ehi = &link->eh_info;
				qc = ata_qc_from_tag(ap, link->active_tag);
				/*
				 * We should consider this as non fatal error,
                                 * and TF must be updated as करोne below.
		                 */

				err_mask |= AC_ERR_DEV;

			पूर्ण अन्यथा अणु
				err_mask |= AC_ERR_HSM;
				action |= ATA_EH_HARDRESET;
				मुक्तze = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			dereg = ioपढ़ो32(hcr_base + DE);
			ioग_लिखो32(dereg, hcr_base + DE);
			ioग_लिखो32(cereg, hcr_base + CE);

			qc = ata_qc_from_tag(ap, link->active_tag);
			/*
			 * We should consider this as non fatal error,
                         * and TF must be updated as करोne below.
	                */
			err_mask |= AC_ERR_DEV;
		पूर्ण
	पूर्ण

	/* record error info */
	अगर (qc)
		qc->err_mask |= err_mask;
	अन्यथा
		ehi->err_mask |= err_mask;

	ehi->action |= action;

	/* मुक्तze or पात */
	अगर (मुक्तze)
		ata_port_मुक्तze(ap);
	अन्यथा अगर (पात) अणु
		अगर (qc)
			ata_link_पात(qc->dev->link);
		अन्यथा
			ata_port_पात(ap);
	पूर्ण
पूर्ण

अटल व्योम sata_fsl_host_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = ap->host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 hstatus, करोne_mask = 0;
	काष्ठा ata_queued_cmd *qc;
	u32 SError;
	u32 tag;
	u32 status_mask = INT_ON_ERROR;

	hstatus = ioपढ़ो32(hcr_base + HSTATUS);

	sata_fsl_scr_पढ़ो(&ap->link, SCR_ERROR, &SError);

	/* Read command completed रेजिस्टर */
	करोne_mask = ioपढ़ो32(hcr_base + CC);

	/* Workaround क्रम data length mismatch errata */
	अगर (unlikely(hstatus & INT_ON_DATA_LENGTH_MISMATCH)) अणु
		ata_qc_क्रम_each_with_पूर्णांकernal(ap, qc, tag) अणु
			अगर (qc && ata_is_atapi(qc->tf.protocol)) अणु
				u32 hcontrol;
				/* Set HControl[27] to clear error रेजिस्टरs */
				hcontrol = ioपढ़ो32(hcr_base + HCONTROL);
				ioग_लिखो32(hcontrol | CLEAR_ERROR,
						hcr_base + HCONTROL);

				/* Clear HControl[27] */
				ioग_लिखो32(hcontrol & ~CLEAR_ERROR,
						hcr_base + HCONTROL);

				/* Clear SError[E] bit */
				sata_fsl_scr_ग_लिखो(&ap->link, SCR_ERROR,
						SError);

				/* Ignore fatal error and device error */
				status_mask &= ~(INT_ON_SINGL_DEVICE_ERR
						| INT_ON_FATAL_ERR);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(SError & 0xFFFF0000)) अणु
		DPRINTK("serror @host_intr : 0x%x\n", SError);
		sata_fsl_error_पूर्णांकr(ap);
	पूर्ण

	अगर (unlikely(hstatus & status_mask)) अणु
		DPRINTK("error interrupt!!\n");
		sata_fsl_error_पूर्णांकr(ap);
		वापस;
	पूर्ण

	VPRINTK("Status of all queues :\n");
	VPRINTK("done_mask/CC = 0x%x, CA = 0x%x, CE=0x%x,CQ=0x%x,apqa=0x%llx\n",
		करोne_mask,
		ioपढ़ो32(hcr_base + CA),
		ioपढ़ो32(hcr_base + CE),
		ioपढ़ो32(hcr_base + CQ),
		ap->qc_active);

	अगर (करोne_mask & ap->qc_active) अणु
		पूर्णांक i;
		/* clear CC bit, this will also complete the पूर्णांकerrupt */
		ioग_लिखो32(करोne_mask, hcr_base + CC);

		DPRINTK("Status of all queues :\n");
		DPRINTK("done_mask/CC = 0x%x, CA = 0x%x, CE=0x%x\n",
			करोne_mask, ioपढ़ो32(hcr_base + CA),
			ioपढ़ो32(hcr_base + CE));

		क्रम (i = 0; i < SATA_FSL_QUEUE_DEPTH; i++) अणु
			अगर (करोne_mask & (1 << i))
				DPRINTK
				    ("completing ncq cmd,tag=%d,CC=0x%x,CA=0x%x\n",
				     i, ioपढ़ो32(hcr_base + CC),
				     ioपढ़ो32(hcr_base + CA));
		पूर्ण
		ata_qc_complete_multiple(ap, ata_qc_get_active(ap) ^ करोne_mask);
		वापस;

	पूर्ण अन्यथा अगर ((ap->qc_active & (1ULL << ATA_TAG_INTERNAL))) अणु
		ioग_लिखो32(1, hcr_base + CC);
		qc = ata_qc_from_tag(ap, ATA_TAG_INTERNAL);

		DPRINTK("completing non-ncq cmd, CC=0x%x\n",
			 ioपढ़ो32(hcr_base + CC));

		अगर (qc) अणु
			ata_qc_complete(qc);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Spurious Interrupt!! */
		DPRINTK("spurious interrupt!!, CC = 0x%x\n",
			ioपढ़ो32(hcr_base + CC));
		ioग_लिखो32(करोne_mask, hcr_base + CC);
		वापस;
	पूर्ण
पूर्ण

अटल irqवापस_t sata_fsl_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 पूर्णांकerrupt_enables;
	अचिन्हित handled = 0;
	काष्ठा ata_port *ap;

	/* ack. any pending IRQs क्रम this controller/port */
	पूर्णांकerrupt_enables = ioपढ़ो32(hcr_base + HSTATUS);
	पूर्णांकerrupt_enables &= 0x3F;

	DPRINTK("interrupt status 0x%x\n", पूर्णांकerrupt_enables);

	अगर (!पूर्णांकerrupt_enables)
		वापस IRQ_NONE;

	spin_lock(&host->lock);

	/* Assuming one port per host controller */

	ap = host->ports[0];
	अगर (ap) अणु
		sata_fsl_host_पूर्णांकr(ap);
	पूर्ण अन्यथा अणु
		dev_warn(host->dev, "interrupt on disabled port 0\n");
	पूर्ण

	ioग_लिखो32(पूर्णांकerrupt_enables, hcr_base + HSTATUS);
	handled = 1;

	spin_unlock(&host->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 * Multiple ports are represented by multiple SATA controllers with
 * one port per controller
 */
अटल पूर्णांक sata_fsl_init_controller(काष्ठा ata_host *host)
अणु
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	u32 temp;

	/*
	 * NOTE : We cannot bring the controller online beक्रमe setting
	 * the CHBA, hence मुख्य controller initialization is करोne as
	 * part of the port_start() callback
	 */

	/* sata controller to operate in enterprise mode */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32(temp & ~HCONTROL_LEGACY, hcr_base + HCONTROL);

	/* ack. any pending IRQs क्रम this controller/port */
	temp = ioपढ़ो32(hcr_base + HSTATUS);
	अगर (temp & 0x3F)
		ioग_लिखो32((temp & 0x3F), hcr_base + HSTATUS);

	/* Keep पूर्णांकerrupts disabled on the controller */
	temp = ioपढ़ो32(hcr_base + HCONTROL);
	ioग_लिखो32((temp & ~0x3F), hcr_base + HCONTROL);

	/* Disable पूर्णांकerrupt coalescing control(icc), क्रम the moment */
	DPRINTK("icc = 0x%x\n", ioपढ़ो32(hcr_base + ICC));
	ioग_लिखो32(0x01000000, hcr_base + ICC);

	/* clear error रेजिस्टरs, SError is cleared by libATA  */
	ioग_लिखो32(0x00000FFFF, hcr_base + CE);
	ioग_लिखो32(0x00000FFFF, hcr_base + DE);

 	/*
	 * reset the number of command complete bits which will cause the
	 * पूर्णांकerrupt to be संकेतed
	 */
	fsl_sata_set_irq_coalescing(host, पूर्णांकr_coalescing_count,
			पूर्णांकr_coalescing_ticks);

	/*
	 * host controller will be brought on-line, during xx_port_start()
	 * callback, that should also initiate the OOB, COMINIT sequence
	 */

	DPRINTK("HStatus = 0x%x\n", ioपढ़ो32(hcr_base + HSTATUS));
	DPRINTK("HControl = 0x%x\n", ioपढ़ो32(hcr_base + HCONTROL));

	वापस 0;
पूर्ण

/*
 * scsi mid-layer and libata पूर्णांकerface काष्ठाures
 */
अटल काष्ठा scsi_host_ढाँचा sata_fsl_sht = अणु
	ATA_NCQ_SHT("sata_fsl"),
	.can_queue = SATA_FSL_QUEUE_DEPTH,
	.sg_tablesize = SATA_FSL_MAX_PRD_USABLE,
	.dma_boundary = ATA_DMA_BOUNDARY,
पूर्ण;

अटल काष्ठा ata_port_operations sata_fsl_ops = अणु
	.inherits		= &sata_pmp_port_ops,

	.qc_defer = ata_std_qc_defer,
	.qc_prep = sata_fsl_qc_prep,
	.qc_issue = sata_fsl_qc_issue,
	.qc_fill_rtf = sata_fsl_qc_fill_rtf,

	.scr_पढ़ो = sata_fsl_scr_पढ़ो,
	.scr_ग_लिखो = sata_fsl_scr_ग_लिखो,

	.मुक्तze = sata_fsl_मुक्तze,
	.thaw = sata_fsl_thaw,
	.softreset = sata_fsl_softreset,
	.hardreset = sata_fsl_hardreset,
	.pmp_softreset = sata_fsl_softreset,
	.error_handler = sata_fsl_error_handler,
	.post_पूर्णांकernal_cmd = sata_fsl_post_पूर्णांकernal_cmd,

	.port_start = sata_fsl_port_start,
	.port_stop = sata_fsl_port_stop,

	.pmp_attach = sata_fsl_pmp_attach,
	.pmp_detach = sata_fsl_pmp_detach,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info sata_fsl_port_info[] = अणु
	अणु
	 .flags = SATA_FSL_HOST_FLAGS,
	 .pio_mask = ATA_PIO4,
	 .udma_mask = ATA_UDMA6,
	 .port_ops = &sata_fsl_ops,
	 पूर्ण,
पूर्ण;

अटल पूर्णांक sata_fsl_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	पूर्णांक retval = -ENXIO;
	व्योम __iomem *hcr_base = शून्य;
	व्योम __iomem *ssr_base = शून्य;
	व्योम __iomem *csr_base = शून्य;
	काष्ठा sata_fsl_host_priv *host_priv = शून्य;
	पूर्णांक irq;
	काष्ठा ata_host *host = शून्य;
	u32 temp;

	काष्ठा ata_port_info pi = sata_fsl_port_info[0];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;

	dev_info(&ofdev->dev, "Sata FSL Platform/CSB Driver init\n");

	hcr_base = of_iomap(ofdev->dev.of_node, 0);
	अगर (!hcr_base)
		जाओ error_निकास_with_cleanup;

	ssr_base = hcr_base + 0x100;
	csr_base = hcr_base + 0x140;

	अगर (!of_device_is_compatible(ofdev->dev.of_node, "fsl,mpc8315-sata")) अणु
		temp = ioपढ़ो32(csr_base + TRANSCFG);
		temp = temp & 0xffffffe0;
		ioग_लिखो32(temp | TRANSCFG_RX_WATER_MARK, csr_base + TRANSCFG);
	पूर्ण

	DPRINTK("@reset i/o = 0x%x\n", ioपढ़ो32(csr_base + TRANSCFG));
	DPRINTK("sizeof(cmd_desc) = %d\n", माप(काष्ठा command_desc));
	DPRINTK("sizeof(#define cmd_desc) = %d\n", SATA_FSL_CMD_DESC_SIZE);

	host_priv = kzalloc(माप(काष्ठा sata_fsl_host_priv), GFP_KERNEL);
	अगर (!host_priv)
		जाओ error_निकास_with_cleanup;

	host_priv->hcr_base = hcr_base;
	host_priv->ssr_base = ssr_base;
	host_priv->csr_base = csr_base;

	irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	अगर (!irq) अणु
		dev_err(&ofdev->dev, "invalid irq from platform\n");
		जाओ error_निकास_with_cleanup;
	पूर्ण
	host_priv->irq = irq;

	अगर (of_device_is_compatible(ofdev->dev.of_node, "fsl,pq-sata-v2"))
		host_priv->data_snoop = DATA_SNOOP_ENABLE_V2;
	अन्यथा
		host_priv->data_snoop = DATA_SNOOP_ENABLE_V1;

	/* allocate host काष्ठाure */
	host = ata_host_alloc_pinfo(&ofdev->dev, ppi, SATA_FSL_MAX_PORTS);
	अगर (!host) अणु
		retval = -ENOMEM;
		जाओ error_निकास_with_cleanup;
	पूर्ण

	/* host->iomap is not used currently */
	host->निजी_data = host_priv;

	/* initialize host controller */
	sata_fsl_init_controller(host);

	/*
	 * Now, रेजिस्टर with libATA core, this will also initiate the
	 * device discovery process, invoking our port_start() handler &
	 * error_handler() to execute a dummy Softreset EH session
	 */
	ata_host_activate(host, irq, sata_fsl_पूर्णांकerrupt, SATA_FSL_IRQ_FLAG,
			  &sata_fsl_sht);

	host_priv->पूर्णांकr_coalescing.show = fsl_sata_पूर्णांकr_coalescing_show;
	host_priv->पूर्णांकr_coalescing.store = fsl_sata_पूर्णांकr_coalescing_store;
	sysfs_attr_init(&host_priv->पूर्णांकr_coalescing.attr);
	host_priv->पूर्णांकr_coalescing.attr.name = "intr_coalescing";
	host_priv->पूर्णांकr_coalescing.attr.mode = S_IRUGO | S_IWUSR;
	retval = device_create_file(host->dev, &host_priv->पूर्णांकr_coalescing);
	अगर (retval)
		जाओ error_निकास_with_cleanup;

	host_priv->rx_watermark.show = fsl_sata_rx_watermark_show;
	host_priv->rx_watermark.store = fsl_sata_rx_watermark_store;
	sysfs_attr_init(&host_priv->rx_watermark.attr);
	host_priv->rx_watermark.attr.name = "rx_watermark";
	host_priv->rx_watermark.attr.mode = S_IRUGO | S_IWUSR;
	retval = device_create_file(host->dev, &host_priv->rx_watermark);
	अगर (retval) अणु
		device_हटाओ_file(&ofdev->dev, &host_priv->पूर्णांकr_coalescing);
		जाओ error_निकास_with_cleanup;
	पूर्ण

	वापस 0;

error_निकास_with_cleanup:

	अगर (host)
		ata_host_detach(host);

	अगर (hcr_base)
		iounmap(hcr_base);
	kमुक्त(host_priv);

	वापस retval;
पूर्ण

अटल पूर्णांक sata_fsl_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(ofdev);
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;

	device_हटाओ_file(&ofdev->dev, &host_priv->पूर्णांकr_coalescing);
	device_हटाओ_file(&ofdev->dev, &host_priv->rx_watermark);

	ata_host_detach(host);

	irq_dispose_mapping(host_priv->irq);
	iounmap(host_priv->hcr_base);
	kमुक्त(host_priv);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sata_fsl_suspend(काष्ठा platक्रमm_device *op, pm_message_t state)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(op);
	वापस ata_host_suspend(host, state);
पूर्ण

अटल पूर्णांक sata_fsl_resume(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(op);
	काष्ठा sata_fsl_host_priv *host_priv = host->निजी_data;
	पूर्णांक ret;
	व्योम __iomem *hcr_base = host_priv->hcr_base;
	काष्ठा ata_port *ap = host->ports[0];
	काष्ठा sata_fsl_port_priv *pp = ap->निजी_data;

	ret = sata_fsl_init_controller(host);
	अगर (ret) अणु
		dev_err(&op->dev, "Error initializing hardware\n");
		वापस ret;
	पूर्ण

	/* Recovery the CHBA रेजिस्टर in host controller cmd रेजिस्टर set */
	ioग_लिखो32(pp->cmdslot_paddr & 0xffffffff, hcr_base + CHBA);

	ioग_लिखो32((ioपढ़ो32(hcr_base + HCONTROL)
				| HCONTROL_ONLINE_PHY_RST
				| HCONTROL_SNOOP_ENABLE
				| HCONTROL_PMP_ATTACHED),
			hcr_base + HCONTROL);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id fsl_sata_match[] = अणु
	अणु
		.compatible = "fsl,pq-sata",
	पूर्ण,
	अणु
		.compatible = "fsl,pq-sata-v2",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, fsl_sata_match);

अटल काष्ठा platक्रमm_driver fsl_sata_driver = अणु
	.driver = अणु
		.name = "fsl-sata",
		.of_match_table = fsl_sata_match,
	पूर्ण,
	.probe		= sata_fsl_probe,
	.हटाओ		= sata_fsl_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= sata_fsl_suspend,
	.resume		= sata_fsl_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(fsl_sata_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashish Kalra, Freescale Semiconductor");
MODULE_DESCRIPTION("Freescale 3.0Gbps SATA controller low level driver");
MODULE_VERSION("1.10");
