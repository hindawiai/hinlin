<शैली गुरु>
/*
 * drivers/ata/pata_arasan_cf.c
 *
 * Arasan Compact Flash host controller source file
 *
 * Copyright (C) 2011 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/*
 * The Arasan CompactFlash Device Controller IP core has three basic modes of
 * operation: PC card ATA using I/O mode, PC card ATA using memory mode, PC card
 * ATA using true IDE modes. This driver supports only True IDE mode currently.
 *
 * Arasan CF Controller shares global irq रेजिस्टर with Arasan XD Controller.
 *
 * Tested on arch/arm/mach-spear13xx
 */

#समावेश <linux/ata.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pata_arasan_cf_data.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#घोषणा DRIVER_NAME	"arasan_cf"
#घोषणा TIMEOUT		msecs_to_jअगरfies(3000)

/* Registers */
/* CompactFlash Interface Status */
#घोषणा CFI_STS			0x000
	#घोषणा STS_CHG				(1)
	#घोषणा BIN_AUDIO_OUT			(1 << 1)
	#घोषणा CARD_DETECT1			(1 << 2)
	#घोषणा CARD_DETECT2			(1 << 3)
	#घोषणा INP_ACK				(1 << 4)
	#घोषणा CARD_READY			(1 << 5)
	#घोषणा IO_READY			(1 << 6)
	#घोषणा B16_IO_PORT_SEL			(1 << 7)
/* IRQ */
#घोषणा IRQ_STS			0x004
/* Interrupt Enable */
#घोषणा IRQ_EN			0x008
	#घोषणा CARD_DETECT_IRQ			(1)
	#घोषणा STATUS_CHNG_IRQ			(1 << 1)
	#घोषणा MEM_MODE_IRQ			(1 << 2)
	#घोषणा IO_MODE_IRQ			(1 << 3)
	#घोषणा TRUE_IDE_MODE_IRQ		(1 << 8)
	#घोषणा PIO_XFER_ERR_IRQ		(1 << 9)
	#घोषणा BUF_AVAIL_IRQ			(1 << 10)
	#घोषणा XFER_DONE_IRQ			(1 << 11)
	#घोषणा IGNORED_IRQS	(STATUS_CHNG_IRQ | MEM_MODE_IRQ | IO_MODE_IRQ |\
					TRUE_IDE_MODE_IRQ)
	#घोषणा TRUE_IDE_IRQS	(CARD_DETECT_IRQ | PIO_XFER_ERR_IRQ |\
					BUF_AVAIL_IRQ | XFER_DONE_IRQ)
/* Operation Mode */
#घोषणा OP_MODE			0x00C
	#घोषणा CARD_MODE_MASK			(0x3)
	#घोषणा MEM_MODE			(0x0)
	#घोषणा IO_MODE				(0x1)
	#घोषणा TRUE_IDE_MODE			(0x2)

	#घोषणा CARD_TYPE_MASK			(1 << 2)
	#घोषणा CF_CARD				(0)
	#घोषणा CF_PLUS_CARD			(1 << 2)

	#घोषणा CARD_RESET			(1 << 3)
	#घोषणा CFHOST_ENB			(1 << 4)
	#घोषणा OUTPUTS_TRISTATE		(1 << 5)
	#घोषणा ULTRA_DMA_ENB			(1 << 8)
	#घोषणा MULTI_WORD_DMA_ENB		(1 << 9)
	#घोषणा DRQ_BLOCK_SIZE_MASK		(0x3 << 11)
	#घोषणा DRQ_BLOCK_SIZE_512		(0)
	#घोषणा DRQ_BLOCK_SIZE_1024		(1 << 11)
	#घोषणा DRQ_BLOCK_SIZE_2048		(2 << 11)
	#घोषणा DRQ_BLOCK_SIZE_4096		(3 << 11)
/* CF Interface Clock Configuration */
#घोषणा CLK_CFG			0x010
	#घोषणा CF_IF_CLK_MASK			(0XF)
/* CF Timing Mode Configuration */
#घोषणा TM_CFG			0x014
	#घोषणा MEM_MODE_TIMING_MASK		(0x3)
	#घोषणा MEM_MODE_TIMING_250NS		(0x0)
	#घोषणा MEM_MODE_TIMING_120NS		(0x1)
	#घोषणा MEM_MODE_TIMING_100NS		(0x2)
	#घोषणा MEM_MODE_TIMING_80NS		(0x3)

	#घोषणा IO_MODE_TIMING_MASK		(0x3 << 2)
	#घोषणा IO_MODE_TIMING_250NS		(0x0 << 2)
	#घोषणा IO_MODE_TIMING_120NS		(0x1 << 2)
	#घोषणा IO_MODE_TIMING_100NS		(0x2 << 2)
	#घोषणा IO_MODE_TIMING_80NS		(0x3 << 2)

	#घोषणा TRUEIDE_PIO_TIMING_MASK		(0x7 << 4)
	#घोषणा TRUEIDE_PIO_TIMING_SHIFT	4

	#घोषणा TRUEIDE_MWORD_DMA_TIMING_MASK	(0x7 << 7)
	#घोषणा TRUEIDE_MWORD_DMA_TIMING_SHIFT	7

	#घोषणा ULTRA_DMA_TIMING_MASK		(0x7 << 10)
	#घोषणा ULTRA_DMA_TIMING_SHIFT		10
/* CF Transfer Address */
#घोषणा XFER_ADDR		0x014
	#घोषणा XFER_ADDR_MASK			(0x7FF)
	#घोषणा MAX_XFER_COUNT			0x20000u
/* Transfer Control */
#घोषणा XFER_CTR		0x01C
	#घोषणा XFER_COUNT_MASK			(0x3FFFF)
	#घोषणा ADDR_INC_DISABLE		(1 << 24)
	#घोषणा XFER_WIDTH_MASK			(1 << 25)
	#घोषणा XFER_WIDTH_8B			(0)
	#घोषणा XFER_WIDTH_16B			(1 << 25)

	#घोषणा MEM_TYPE_MASK			(1 << 26)
	#घोषणा MEM_TYPE_COMMON			(0)
	#घोषणा MEM_TYPE_ATTRIBUTE		(1 << 26)

	#घोषणा MEM_IO_XFER_MASK		(1 << 27)
	#घोषणा MEM_XFER			(0)
	#घोषणा IO_XFER				(1 << 27)

	#घोषणा DMA_XFER_MODE			(1 << 28)

	#घोषणा AHB_BUS_NORMAL_PIO_OPRTN	(~(1 << 29))
	#घोषणा XFER_सूची_MASK			(1 << 30)
	#घोषणा XFER_READ			(0)
	#घोषणा XFER_WRITE			(1 << 30)

	#घोषणा XFER_START			(1 << 31)
/* Write Data Port */
#घोषणा WRITE_PORT		0x024
/* Read Data Port */
#घोषणा READ_PORT		0x028
/* ATA Data Port */
#घोषणा ATA_DATA_PORT		0x030
	#घोषणा ATA_DATA_PORT_MASK		(0xFFFF)
/* ATA Error/Features */
#घोषणा ATA_ERR_FTR		0x034
/* ATA Sector Count */
#घोषणा ATA_SC			0x038
/* ATA Sector Number */
#घोषणा ATA_SN			0x03C
/* ATA Cylinder Low */
#घोषणा ATA_CL			0x040
/* ATA Cylinder High */
#घोषणा ATA_CH			0x044
/* ATA Select Card/Head */
#घोषणा ATA_SH			0x048
/* ATA Status-Command */
#घोषणा ATA_STS_CMD		0x04C
/* ATA Alternate Status/Device Control */
#घोषणा ATA_ASTS_DCTR		0x050
/* Extended Write Data Port 0x200-0x3FC */
#घोषणा EXT_WRITE_PORT		0x200
/* Extended Read Data Port 0x400-0x5FC */
#घोषणा EXT_READ_PORT		0x400
	#घोषणा FIFO_SIZE	0x200u
/* Global Interrupt Status */
#घोषणा GIRQ_STS		0x800
/* Global Interrupt Status enable */
#घोषणा GIRQ_STS_EN		0x804
/* Global Interrupt Signal enable */
#घोषणा GIRQ_SGN_EN		0x808
	#घोषणा GIRQ_CF		(1)
	#घोषणा GIRQ_XD		(1 << 1)

/* Compact Flash Controller Dev Structure */
काष्ठा arasan_cf_dev अणु
	/* poपूर्णांकer to ata_host काष्ठाure */
	काष्ठा ata_host *host;
	/* clk काष्ठाure */
	काष्ठा clk *clk;

	/* physical base address of controller */
	dma_addr_t pbase;
	/* भव base address of controller */
	व्योम __iomem *vbase;
	/* irq number*/
	पूर्णांक irq;

	/* status to be updated to framework regarding DMA transfer */
	u8 dma_status;
	/* Card is present or Not */
	u8 card_present;

	/* dma specअगरic */
	/* Completion क्रम transfer complete पूर्णांकerrupt from controller */
	काष्ठा completion cf_completion;
	/* Completion क्रम DMA transfer complete. */
	काष्ठा completion dma_completion;
	/* Dma channel allocated */
	काष्ठा dma_chan *dma_chan;
	/* Mask क्रम DMA transfers */
	dma_cap_mask_t mask;
	/* DMA transfer work */
	काष्ठा work_काष्ठा work;
	/* DMA delayed finish work */
	काष्ठा delayed_work dwork;
	/* qc to be transferred using DMA */
	काष्ठा ata_queued_cmd *qc;
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा arasan_cf_sht = अणु
	ATA_BASE_SHT(DRIVER_NAME),
	.dma_boundary = 0xFFFFFFFFUL,
पूर्ण;

अटल व्योम cf_dumpregs(काष्ठा arasan_cf_dev *acdev)
अणु
	काष्ठा device *dev = acdev->host->dev;

	dev_dbg(dev, ": =========== REGISTER DUMP ===========");
	dev_dbg(dev, ": CFI_STS: %x", पढ़ोl(acdev->vbase + CFI_STS));
	dev_dbg(dev, ": IRQ_STS: %x", पढ़ोl(acdev->vbase + IRQ_STS));
	dev_dbg(dev, ": IRQ_EN: %x", पढ़ोl(acdev->vbase + IRQ_EN));
	dev_dbg(dev, ": OP_MODE: %x", पढ़ोl(acdev->vbase + OP_MODE));
	dev_dbg(dev, ": CLK_CFG: %x", पढ़ोl(acdev->vbase + CLK_CFG));
	dev_dbg(dev, ": TM_CFG: %x", पढ़ोl(acdev->vbase + TM_CFG));
	dev_dbg(dev, ": XFER_CTR: %x", पढ़ोl(acdev->vbase + XFER_CTR));
	dev_dbg(dev, ": GIRQ_STS: %x", पढ़ोl(acdev->vbase + GIRQ_STS));
	dev_dbg(dev, ": GIRQ_STS_EN: %x", पढ़ोl(acdev->vbase + GIRQ_STS_EN));
	dev_dbg(dev, ": GIRQ_SGN_EN: %x", पढ़ोl(acdev->vbase + GIRQ_SGN_EN));
	dev_dbg(dev, ": =====================================");
पूर्ण

/* Enable/Disable global पूर्णांकerrupts shared between CF and XD ctrlr. */
अटल व्योम cf_gपूर्णांकerrupt_enable(काष्ठा arasan_cf_dev *acdev, bool enable)
अणु
	/* enable should be 0 or 1 */
	ग_लिखोl(enable, acdev->vbase + GIRQ_STS_EN);
	ग_लिखोl(enable, acdev->vbase + GIRQ_SGN_EN);
पूर्ण

/* Enable/Disable CF पूर्णांकerrupts */
अटल अंतरभूत व्योम
cf_पूर्णांकerrupt_enable(काष्ठा arasan_cf_dev *acdev, u32 mask, bool enable)
अणु
	u32 val = पढ़ोl(acdev->vbase + IRQ_EN);
	/* clear & enable/disable irqs */
	अगर (enable) अणु
		ग_लिखोl(mask, acdev->vbase + IRQ_STS);
		ग_लिखोl(val | mask, acdev->vbase + IRQ_EN);
	पूर्ण अन्यथा
		ग_लिखोl(val & ~mask, acdev->vbase + IRQ_EN);
पूर्ण

अटल अंतरभूत व्योम cf_card_reset(काष्ठा arasan_cf_dev *acdev)
अणु
	u32 val = पढ़ोl(acdev->vbase + OP_MODE);

	ग_लिखोl(val | CARD_RESET, acdev->vbase + OP_MODE);
	udelay(200);
	ग_लिखोl(val & ~CARD_RESET, acdev->vbase + OP_MODE);
पूर्ण

अटल अंतरभूत व्योम cf_ctrl_reset(काष्ठा arasan_cf_dev *acdev)
अणु
	ग_लिखोl(पढ़ोl(acdev->vbase + OP_MODE) & ~CFHOST_ENB,
			acdev->vbase + OP_MODE);
	ग_लिखोl(पढ़ोl(acdev->vbase + OP_MODE) | CFHOST_ENB,
			acdev->vbase + OP_MODE);
पूर्ण

अटल व्योम cf_card_detect(काष्ठा arasan_cf_dev *acdev, bool hotplugged)
अणु
	काष्ठा ata_port *ap = acdev->host->ports[0];
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	u32 val = पढ़ोl(acdev->vbase + CFI_STS);

	/* Both CD1 & CD2 should be low अगर card inserted completely */
	अगर (!(val & (CARD_DETECT1 | CARD_DETECT2))) अणु
		अगर (acdev->card_present)
			वापस;
		acdev->card_present = 1;
		cf_card_reset(acdev);
	पूर्ण अन्यथा अणु
		अगर (!acdev->card_present)
			वापस;
		acdev->card_present = 0;
	पूर्ण

	अगर (hotplugged) अणु
		ata_ehi_hotplugged(ehi);
		ata_port_मुक्तze(ap);
	पूर्ण
पूर्ण

अटल पूर्णांक cf_init(काष्ठा arasan_cf_dev *acdev)
अणु
	काष्ठा arasan_cf_pdata *pdata = dev_get_platdata(acdev->host->dev);
	अचिन्हित पूर्णांक अगर_clk;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(acdev->clk);
	अगर (ret) अणु
		dev_dbg(acdev->host->dev, "clock enable failed");
		वापस ret;
	पूर्ण

	ret = clk_set_rate(acdev->clk, 166000000);
	अगर (ret) अणु
		dev_warn(acdev->host->dev, "clock set rate failed");
		clk_disable_unprepare(acdev->clk);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&acdev->host->lock, flags);
	/* configure CF पूर्णांकerface घड़ी */
	/* TODO: पढ़ो from device tree */
	अगर_clk = CF_IF_CLK_166M;
	अगर (pdata && pdata->cf_अगर_clk <= CF_IF_CLK_200M)
		अगर_clk = pdata->cf_अगर_clk;

	ग_लिखोl(अगर_clk, acdev->vbase + CLK_CFG);

	ग_लिखोl(TRUE_IDE_MODE | CFHOST_ENB, acdev->vbase + OP_MODE);
	cf_पूर्णांकerrupt_enable(acdev, CARD_DETECT_IRQ, 1);
	cf_gपूर्णांकerrupt_enable(acdev, 1);
	spin_unlock_irqrestore(&acdev->host->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम cf_निकास(काष्ठा arasan_cf_dev *acdev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&acdev->host->lock, flags);
	cf_gपूर्णांकerrupt_enable(acdev, 0);
	cf_पूर्णांकerrupt_enable(acdev, TRUE_IDE_IRQS, 0);
	cf_card_reset(acdev);
	ग_लिखोl(पढ़ोl(acdev->vbase + OP_MODE) & ~CFHOST_ENB,
			acdev->vbase + OP_MODE);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
	clk_disable_unprepare(acdev->clk);
पूर्ण

अटल व्योम dma_callback(व्योम *dev)
अणु
	काष्ठा arasan_cf_dev *acdev = dev;

	complete(&acdev->dma_completion);
पूर्ण

अटल अंतरभूत व्योम dma_complete(काष्ठा arasan_cf_dev *acdev)
अणु
	काष्ठा ata_queued_cmd *qc = acdev->qc;
	अचिन्हित दीर्घ flags;

	acdev->qc = शून्य;
	ata_sff_पूर्णांकerrupt(acdev->irq, acdev->host);

	spin_lock_irqsave(&acdev->host->lock, flags);
	अगर (unlikely(qc->err_mask) && ata_is_dma(qc->tf.protocol))
		ata_ehi_push_desc(&qc->ap->link.eh_info, "DMA Failed: Timeout");
	spin_unlock_irqrestore(&acdev->host->lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक रुको4buf(काष्ठा arasan_cf_dev *acdev)
अणु
	अगर (!रुको_क्रम_completion_समयout(&acdev->cf_completion, TIMEOUT)) अणु
		u32 rw = acdev->qc->tf.flags & ATA_TFLAG_WRITE;

		dev_err(acdev->host->dev, "%s TimeOut", rw ? "write" : "read");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Check अगर PIO Error पूर्णांकerrupt has occurred */
	अगर (acdev->dma_status & ATA_DMA_ERR)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक
dma_xfer(काष्ठा arasan_cf_dev *acdev, dma_addr_t src, dma_addr_t dest, u32 len)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_chan *chan = acdev->dma_chan;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags = DMA_PREP_INTERRUPT;
	पूर्णांक ret = 0;

	tx = chan->device->device_prep_dma_स_नकल(chan, dest, src, len, flags);
	अगर (!tx) अणु
		dev_err(acdev->host->dev, "device_prep_dma_memcpy failed\n");
		वापस -EAGAIN;
	पूर्ण

	tx->callback = dma_callback;
	tx->callback_param = acdev;
	cookie = tx->tx_submit(tx);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(acdev->host->dev, "dma_submit_error\n");
		वापस ret;
	पूर्ण

	chan->device->device_issue_pending(chan);

	/* Wait क्रम DMA to complete */
	अगर (!रुको_क्रम_completion_समयout(&acdev->dma_completion, TIMEOUT)) अणु
		dmaengine_terminate_all(chan);
		dev_err(acdev->host->dev, "wait_for_completion_timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sg_xfer(काष्ठा arasan_cf_dev *acdev, काष्ठा scatterlist *sg)
अणु
	dma_addr_t dest = 0, src = 0;
	u32 xfer_cnt, sglen, dma_len, xfer_ctr;
	u32 ग_लिखो = acdev->qc->tf.flags & ATA_TFLAG_WRITE;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	sglen = sg_dma_len(sg);
	अगर (ग_लिखो) अणु
		src = sg_dma_address(sg);
		dest = acdev->pbase + EXT_WRITE_PORT;
	पूर्ण अन्यथा अणु
		dest = sg_dma_address(sg);
		src = acdev->pbase + EXT_READ_PORT;
	पूर्ण

	/*
	 * For each sg:
	 * MAX_XFER_COUNT data will be transferred beक्रमe we get transfer
	 * complete पूर्णांकerrupt. Between after FIFO_SIZE data
	 * buffer available पूर्णांकerrupt will be generated. At this समय we will
	 * fill FIFO again: max FIFO_SIZE data.
	 */
	जबतक (sglen) अणु
		xfer_cnt = min(sglen, MAX_XFER_COUNT);
		spin_lock_irqsave(&acdev->host->lock, flags);
		xfer_ctr = पढ़ोl(acdev->vbase + XFER_CTR) &
			~XFER_COUNT_MASK;
		ग_लिखोl(xfer_ctr | xfer_cnt | XFER_START,
				acdev->vbase + XFER_CTR);
		spin_unlock_irqrestore(&acdev->host->lock, flags);

		/* जारी dma xfers until current sg is completed */
		जबतक (xfer_cnt) अणु
			/* रुको क्रम पढ़ो to complete */
			अगर (!ग_लिखो) अणु
				ret = रुको4buf(acdev);
				अगर (ret)
					जाओ fail;
			पूर्ण

			/* पढ़ो/ग_लिखो FIFO in chunk of FIFO_SIZE */
			dma_len = min(xfer_cnt, FIFO_SIZE);
			ret = dma_xfer(acdev, src, dest, dma_len);
			अगर (ret) अणु
				dev_err(acdev->host->dev, "dma failed");
				जाओ fail;
			पूर्ण

			अगर (ग_लिखो)
				src += dma_len;
			अन्यथा
				dest += dma_len;

			sglen -= dma_len;
			xfer_cnt -= dma_len;

			/* रुको क्रम ग_लिखो to complete */
			अगर (ग_लिखो) अणु
				ret = रुको4buf(acdev);
				अगर (ret)
					जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

fail:
	spin_lock_irqsave(&acdev->host->lock, flags);
	ग_लिखोl(पढ़ोl(acdev->vbase + XFER_CTR) & ~XFER_START,
			acdev->vbase + XFER_CTR);
	spin_unlock_irqrestore(&acdev->host->lock, flags);

	वापस ret;
पूर्ण

/*
 * This routine uses External DMA controller to पढ़ो/ग_लिखो data to FIFO of CF
 * controller. There are two xfer related पूर्णांकerrupt supported by CF controller:
 * - buf_avail: This पूर्णांकerrupt is generated as soon as we have buffer of 512
 *	bytes available क्रम पढ़ोing or empty buffer available क्रम writing.
 * - xfer_करोne: This पूर्णांकerrupt is generated on transfer of "xfer_size" amount of
 *	data to/from FIFO. xfer_size is programmed in XFER_CTR रेजिस्टर.
 *
 * Max buffer size = FIFO_SIZE = 512 Bytes.
 * Max xfer_size = MAX_XFER_COUNT = 256 KB.
 */
अटल व्योम data_xfer(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arasan_cf_dev *acdev = container_of(work, काष्ठा arasan_cf_dev,
			work);
	काष्ठा ata_queued_cmd *qc = acdev->qc;
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ flags;
	u32 temp;
	पूर्णांक ret = 0;

	/* request dma channels */
	/* dma_request_channel may sleep, so calling from process context */
	acdev->dma_chan = dma_request_chan(acdev->host->dev, "data");
	अगर (IS_ERR(acdev->dma_chan)) अणु
		dev_err(acdev->host->dev, "Unable to get dma_chan\n");
		acdev->dma_chan = शून्य;
		जाओ chan_request_fail;
	पूर्ण

	क्रम_each_sg(qc->sg, sg, qc->n_elem, temp) अणु
		ret = sg_xfer(acdev, sg);
		अगर (ret)
			अवरोध;
	पूर्ण

	dma_release_channel(acdev->dma_chan);
	acdev->dma_chan = शून्य;

	/* data xferred successfully */
	अगर (!ret) अणु
		u32 status;

		spin_lock_irqsave(&acdev->host->lock, flags);
		status = ioपढ़ो8(qc->ap->ioaddr.altstatus_addr);
		spin_unlock_irqrestore(&acdev->host->lock, flags);
		अगर (status & (ATA_BUSY | ATA_DRQ)) अणु
			ata_sff_queue_delayed_work(&acdev->dwork, 1);
			वापस;
		पूर्ण

		जाओ sff_पूर्णांकr;
	पूर्ण

	cf_dumpregs(acdev);

chan_request_fail:
	spin_lock_irqsave(&acdev->host->lock, flags);
	/* error when transferring data to/from memory */
	qc->err_mask |= AC_ERR_HOST_BUS;
	qc->ap->hsm_task_state = HSM_ST_ERR;

	cf_ctrl_reset(acdev);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
sff_पूर्णांकr:
	dma_complete(acdev);
पूर्ण

अटल व्योम delayed_finish(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arasan_cf_dev *acdev = container_of(work, काष्ठा arasan_cf_dev,
			dwork.work);
	काष्ठा ata_queued_cmd *qc = acdev->qc;
	अचिन्हित दीर्घ flags;
	u8 status;

	spin_lock_irqsave(&acdev->host->lock, flags);
	status = ioपढ़ो8(qc->ap->ioaddr.altstatus_addr);
	spin_unlock_irqrestore(&acdev->host->lock, flags);

	अगर (status & (ATA_BUSY | ATA_DRQ))
		ata_sff_queue_delayed_work(&acdev->dwork, 1);
	अन्यथा
		dma_complete(acdev);
पूर्ण

अटल irqवापस_t arasan_cf_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा arasan_cf_dev *acdev = ((काष्ठा ata_host *)dev)->निजी_data;
	अचिन्हित दीर्घ flags;
	u32 irqsts;

	irqsts = पढ़ोl(acdev->vbase + GIRQ_STS);
	अगर (!(irqsts & GIRQ_CF))
		वापस IRQ_NONE;

	spin_lock_irqsave(&acdev->host->lock, flags);
	irqsts = पढ़ोl(acdev->vbase + IRQ_STS);
	ग_लिखोl(irqsts, acdev->vbase + IRQ_STS);		/* clear irqs */
	ग_लिखोl(GIRQ_CF, acdev->vbase + GIRQ_STS);	/* clear girqs */

	/* handle only relevant पूर्णांकerrupts */
	irqsts &= ~IGNORED_IRQS;

	अगर (irqsts & CARD_DETECT_IRQ) अणु
		cf_card_detect(acdev, 1);
		spin_unlock_irqrestore(&acdev->host->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (irqsts & PIO_XFER_ERR_IRQ) अणु
		acdev->dma_status = ATA_DMA_ERR;
		ग_लिखोl(पढ़ोl(acdev->vbase + XFER_CTR) & ~XFER_START,
				acdev->vbase + XFER_CTR);
		spin_unlock_irqrestore(&acdev->host->lock, flags);
		complete(&acdev->cf_completion);
		dev_err(acdev->host->dev, "pio xfer err irq\n");
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&acdev->host->lock, flags);

	अगर (irqsts & BUF_AVAIL_IRQ) अणु
		complete(&acdev->cf_completion);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (irqsts & XFER_DONE_IRQ) अणु
		काष्ठा ata_queued_cmd *qc = acdev->qc;

		/* Send Complete only क्रम ग_लिखो */
		अगर (qc->tf.flags & ATA_TFLAG_WRITE)
			complete(&acdev->cf_completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम arasan_cf_मुक्तze(काष्ठा ata_port *ap)
अणु
	काष्ठा arasan_cf_dev *acdev = ap->host->निजी_data;

	/* stop transfer and reset controller */
	ग_लिखोl(पढ़ोl(acdev->vbase + XFER_CTR) & ~XFER_START,
			acdev->vbase + XFER_CTR);
	cf_ctrl_reset(acdev);
	acdev->dma_status = ATA_DMA_ERR;

	ata_sff_dma_छोड़ो(ap);
	ata_sff_मुक्तze(ap);
पूर्ण

अटल व्योम arasan_cf_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा arasan_cf_dev *acdev = ap->host->निजी_data;

	/*
	 * DMA transfers using an बाह्यal DMA controller may be scheduled.
	 * Abort them beक्रमe handling error. Refer data_xfer() क्रम further
	 * details.
	 */
	cancel_work_sync(&acdev->work);
	cancel_delayed_work_sync(&acdev->dwork);
	वापस ata_sff_error_handler(ap);
पूर्ण

अटल व्योम arasan_cf_dma_start(काष्ठा arasan_cf_dev *acdev)
अणु
	काष्ठा ata_queued_cmd *qc = acdev->qc;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_taskfile *tf = &qc->tf;
	u32 xfer_ctr = पढ़ोl(acdev->vbase + XFER_CTR) & ~XFER_सूची_MASK;
	u32 ग_लिखो = tf->flags & ATA_TFLAG_WRITE;

	xfer_ctr |= ग_लिखो ? XFER_WRITE : XFER_READ;
	ग_लिखोl(xfer_ctr, acdev->vbase + XFER_CTR);

	ap->ops->sff_exec_command(ap, tf);
	ata_sff_queue_work(&acdev->work);
पूर्ण

अटल अचिन्हित पूर्णांक arasan_cf_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा arasan_cf_dev *acdev = ap->host->निजी_data;

	/* defer PIO handling to sff_qc_issue */
	अगर (!ata_is_dma(qc->tf.protocol))
		वापस ata_sff_qc_issue(qc);

	/* select the device */
	ata_रुको_idle(ap);
	ata_sff_dev_select(ap, qc->dev->devno);
	ata_रुको_idle(ap);

	/* start the command */
	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		WARN_ON_ONCE(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);
		acdev->dma_status = 0;
		acdev->qc = qc;
		arasan_cf_dma_start(acdev);
		ap->hsm_task_state = HSM_ST_LAST;
		अवरोध;

	शेष:
		WARN_ON(1);
		वापस AC_ERR_SYSTEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम arasan_cf_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा arasan_cf_dev *acdev = ap->host->निजी_data;
	u8 pio = adev->pio_mode - XFER_PIO_0;
	अचिन्हित दीर्घ flags;
	u32 val;

	/* Arasan ctrl supports Mode0 -> Mode6 */
	अगर (pio > 6) अणु
		dev_err(ap->dev, "Unknown PIO mode\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&acdev->host->lock, flags);
	val = पढ़ोl(acdev->vbase + OP_MODE) &
		~(ULTRA_DMA_ENB | MULTI_WORD_DMA_ENB | DRQ_BLOCK_SIZE_MASK);
	ग_लिखोl(val, acdev->vbase + OP_MODE);
	val = पढ़ोl(acdev->vbase + TM_CFG) & ~TRUEIDE_PIO_TIMING_MASK;
	val |= pio << TRUEIDE_PIO_TIMING_SHIFT;
	ग_लिखोl(val, acdev->vbase + TM_CFG);

	cf_पूर्णांकerrupt_enable(acdev, BUF_AVAIL_IRQ | XFER_DONE_IRQ, 0);
	cf_पूर्णांकerrupt_enable(acdev, PIO_XFER_ERR_IRQ, 1);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
पूर्ण

अटल व्योम arasan_cf_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा arasan_cf_dev *acdev = ap->host->निजी_data;
	u32 opmode, पंचांगcfg, dma_mode = adev->dma_mode;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&acdev->host->lock, flags);
	opmode = पढ़ोl(acdev->vbase + OP_MODE) &
		~(MULTI_WORD_DMA_ENB | ULTRA_DMA_ENB);
	पंचांगcfg = पढ़ोl(acdev->vbase + TM_CFG);

	अगर ((dma_mode >= XFER_UDMA_0) && (dma_mode <= XFER_UDMA_6)) अणु
		opmode |= ULTRA_DMA_ENB;
		पंचांगcfg &= ~ULTRA_DMA_TIMING_MASK;
		पंचांगcfg |= (dma_mode - XFER_UDMA_0) << ULTRA_DMA_TIMING_SHIFT;
	पूर्ण अन्यथा अगर ((dma_mode >= XFER_MW_DMA_0) && (dma_mode <= XFER_MW_DMA_4)) अणु
		opmode |= MULTI_WORD_DMA_ENB;
		पंचांगcfg &= ~TRUEIDE_MWORD_DMA_TIMING_MASK;
		पंचांगcfg |= (dma_mode - XFER_MW_DMA_0) <<
			TRUEIDE_MWORD_DMA_TIMING_SHIFT;
	पूर्ण अन्यथा अणु
		dev_err(ap->dev, "Unknown DMA mode\n");
		spin_unlock_irqrestore(&acdev->host->lock, flags);
		वापस;
	पूर्ण

	ग_लिखोl(opmode, acdev->vbase + OP_MODE);
	ग_लिखोl(पंचांगcfg, acdev->vbase + TM_CFG);
	ग_लिखोl(DMA_XFER_MODE, acdev->vbase + XFER_CTR);

	cf_पूर्णांकerrupt_enable(acdev, PIO_XFER_ERR_IRQ, 0);
	cf_पूर्णांकerrupt_enable(acdev, BUF_AVAIL_IRQ | XFER_DONE_IRQ, 1);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
पूर्ण

अटल काष्ठा ata_port_operations arasan_cf_ops = अणु
	.inherits = &ata_sff_port_ops,
	.मुक्तze = arasan_cf_मुक्तze,
	.error_handler = arasan_cf_error_handler,
	.qc_issue = arasan_cf_qc_issue,
	.set_piomode = arasan_cf_set_piomode,
	.set_dmamode = arasan_cf_set_dmamode,
पूर्ण;

अटल पूर्णांक arasan_cf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arasan_cf_dev *acdev;
	काष्ठा arasan_cf_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	काष्ठा resource *res;
	u32 quirk;
	irq_handler_t irq_handler = शून्य;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	अगर (!devm_request_mem_region(&pdev->dev, res->start, resource_size(res),
				DRIVER_NAME)) अणु
		dev_warn(&pdev->dev, "Failed to get memory region resource\n");
		वापस -ENOENT;
	पूर्ण

	acdev = devm_kzalloc(&pdev->dev, माप(*acdev), GFP_KERNEL);
	अगर (!acdev)
		वापस -ENOMEM;

	अगर (pdata)
		quirk = pdata->quirk;
	अन्यथा
		quirk = CF_BROKEN_UDMA; /* as it is on spear1340 */

	/*
	 * If there's an error getting IRQ (or we करो get IRQ0),
	 * support only PIO
	 */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret > 0) अणु
		acdev->irq = ret;
		irq_handler = arasan_cf_पूर्णांकerrupt;
	पूर्ण अन्यथा	अगर (ret == -EPROBE_DEFER) अणु
		वापस ret;
	पूर्ण अन्यथा	अणु
		quirk |= CF_BROKEN_MWDMA | CF_BROKEN_UDMA;
	पूर्ण

	acdev->pbase = res->start;
	acdev->vbase = devm_ioremap(&pdev->dev, res->start,
			resource_size(res));
	अगर (!acdev->vbase) अणु
		dev_warn(&pdev->dev, "ioremap fail\n");
		वापस -ENOMEM;
	पूर्ण

	acdev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(acdev->clk)) अणु
		dev_warn(&pdev->dev, "Clock not found\n");
		वापस PTR_ERR(acdev->clk);
	पूर्ण

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host) अणु
		dev_warn(&pdev->dev, "alloc host fail\n");
		वापस -ENOMEM;
	पूर्ण

	ap = host->ports[0];
	host->निजी_data = acdev;
	acdev->host = host;
	ap->ops = &arasan_cf_ops;
	ap->pio_mask = ATA_PIO6;
	ap->mwdma_mask = ATA_MWDMA4;
	ap->udma_mask = ATA_UDMA6;

	init_completion(&acdev->cf_completion);
	init_completion(&acdev->dma_completion);
	INIT_WORK(&acdev->work, data_xfer);
	INIT_DELAYED_WORK(&acdev->dwork, delayed_finish);
	dma_cap_set(DMA_MEMCPY, acdev->mask);

	/* Handle platक्रमm specअगरic quirks */
	अगर (quirk) अणु
		अगर (quirk & CF_BROKEN_PIO) अणु
			ap->ops->set_piomode = शून्य;
			ap->pio_mask = 0;
		पूर्ण
		अगर (quirk & CF_BROKEN_MWDMA)
			ap->mwdma_mask = 0;
		अगर (quirk & CF_BROKEN_UDMA)
			ap->udma_mask = 0;
	पूर्ण
	ap->flags |= ATA_FLAG_PIO_POLLING | ATA_FLAG_NO_ATAPI;

	ap->ioaddr.cmd_addr = acdev->vbase + ATA_DATA_PORT;
	ap->ioaddr.data_addr = acdev->vbase + ATA_DATA_PORT;
	ap->ioaddr.error_addr = acdev->vbase + ATA_ERR_FTR;
	ap->ioaddr.feature_addr = acdev->vbase + ATA_ERR_FTR;
	ap->ioaddr.nsect_addr = acdev->vbase + ATA_SC;
	ap->ioaddr.lbal_addr = acdev->vbase + ATA_SN;
	ap->ioaddr.lbam_addr = acdev->vbase + ATA_CL;
	ap->ioaddr.lbah_addr = acdev->vbase + ATA_CH;
	ap->ioaddr.device_addr = acdev->vbase + ATA_SH;
	ap->ioaddr.status_addr = acdev->vbase + ATA_STS_CMD;
	ap->ioaddr.command_addr = acdev->vbase + ATA_STS_CMD;
	ap->ioaddr.altstatus_addr = acdev->vbase + ATA_ASTS_DCTR;
	ap->ioaddr.ctl_addr = acdev->vbase + ATA_ASTS_DCTR;

	ata_port_desc(ap, "phy_addr %llx virt_addr %p",
		      (अचिन्हित दीर्घ दीर्घ) res->start, acdev->vbase);

	ret = cf_init(acdev);
	अगर (ret)
		वापस ret;

	cf_card_detect(acdev, 0);

	ret = ata_host_activate(host, acdev->irq, irq_handler, 0,
				&arasan_cf_sht);
	अगर (!ret)
		वापस 0;

	cf_निकास(acdev);

	वापस ret;
पूर्ण

अटल पूर्णांक arasan_cf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा arasan_cf_dev *acdev = host->ports[0]->निजी_data;

	ata_host_detach(host);
	cf_निकास(acdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक arasan_cf_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा arasan_cf_dev *acdev = host->ports[0]->निजी_data;

	अगर (acdev->dma_chan)
		dmaengine_terminate_all(acdev->dma_chan);

	cf_निकास(acdev);
	वापस ata_host_suspend(host, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक arasan_cf_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा arasan_cf_dev *acdev = host->ports[0]->निजी_data;

	cf_init(acdev);
	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(arasan_cf_pm_ops, arasan_cf_suspend, arasan_cf_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id arasan_cf_id_table[] = अणु
	अणु .compatible = "arasan,cf-spear1340" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, arasan_cf_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver arasan_cf_driver = अणु
	.probe		= arasan_cf_probe,
	.हटाओ		= arasan_cf_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm	= &arasan_cf_pm_ops,
		.of_match_table = of_match_ptr(arasan_cf_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(arasan_cf_driver);

MODULE_AUTHOR("Viresh Kumar <vireshk@kernel.org>");
MODULE_DESCRIPTION("Arasan ATA Compact Flash driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
