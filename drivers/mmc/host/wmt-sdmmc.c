<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  WM8505/WM8650 SD/MMC Host Controller
 *
 *  Copyright (C) 2010 Tony Prisk
 *  Copyright (C) 2008 WonderMedia Technologies, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>

#समावेश <यंत्र/byteorder.h>


#घोषणा DRIVER_NAME "wmt-sdhc"


/* MMC/SD controller रेजिस्टरs */
#घोषणा SDMMC_CTLR			0x00
#घोषणा SDMMC_CMD			0x01
#घोषणा SDMMC_RSPTYPE			0x02
#घोषणा SDMMC_ARG			0x04
#घोषणा SDMMC_BUSMODE			0x08
#घोषणा SDMMC_BLKLEN			0x0C
#घोषणा SDMMC_BLKCNT			0x0E
#घोषणा SDMMC_RSP			0x10
#घोषणा SDMMC_CBCR			0x20
#घोषणा SDMMC_INTMASK0			0x24
#घोषणा SDMMC_INTMASK1			0x25
#घोषणा SDMMC_STS0			0x28
#घोषणा SDMMC_STS1			0x29
#घोषणा SDMMC_STS2			0x2A
#घोषणा SDMMC_STS3			0x2B
#घोषणा SDMMC_RSPTIMEOUT		0x2C
#घोषणा SDMMC_CLK			0x30	/* VT8500 only */
#घोषणा SDMMC_EXTCTRL			0x34
#घोषणा SDMMC_SBLKLEN			0x38
#घोषणा SDMMC_DMATIMEOUT		0x3C


/* SDMMC_CTLR bit fields */
#घोषणा CTLR_CMD_START			0x01
#घोषणा CTLR_CMD_WRITE			0x04
#घोषणा CTLR_FIFO_RESET			0x08

/* SDMMC_BUSMODE bit fields */
#घोषणा BM_SPI_MODE			0x01
#घोषणा BM_FOURBIT_MODE			0x02
#घोषणा BM_EIGHTBIT_MODE		0x04
#घोषणा BM_SD_OFF			0x10
#घोषणा BM_SPI_CS			0x20
#घोषणा BM_SD_POWER			0x40
#घोषणा BM_SOFT_RESET			0x80

/* SDMMC_BLKLEN bit fields */
#घोषणा BLKL_CRCERR_ABORT		0x0800
#घोषणा BLKL_CD_POL_HIGH		0x1000
#घोषणा BLKL_GPI_CD			0x2000
#घोषणा BLKL_DATA3_CD			0x4000
#घोषणा BLKL_INT_ENABLE			0x8000

/* SDMMC_INTMASK0 bit fields */
#घोषणा INT0_MBLK_TRAN_DONE_INT_EN	0x10
#घोषणा INT0_BLK_TRAN_DONE_INT_EN	0x20
#घोषणा INT0_CD_INT_EN			0x40
#घोषणा INT0_DI_INT_EN			0x80

/* SDMMC_INTMASK1 bit fields */
#घोषणा INT1_CMD_RES_TRAN_DONE_INT_EN	0x02
#घोषणा INT1_CMD_RES_TOUT_INT_EN	0x04
#घोषणा INT1_MBLK_AUTO_STOP_INT_EN	0x08
#घोषणा INT1_DATA_TOUT_INT_EN		0x10
#घोषणा INT1_RESCRC_ERR_INT_EN		0x20
#घोषणा INT1_RCRC_ERR_INT_EN		0x40
#घोषणा INT1_WCRC_ERR_INT_EN		0x80

/* SDMMC_STS0 bit fields */
#घोषणा STS0_WRITE_PROTECT		0x02
#घोषणा STS0_CD_DATA3			0x04
#घोषणा STS0_CD_GPI			0x08
#घोषणा STS0_MBLK_DONE			0x10
#घोषणा STS0_BLK_DONE			0x20
#घोषणा STS0_CARD_DETECT		0x40
#घोषणा STS0_DEVICE_INS			0x80

/* SDMMC_STS1 bit fields */
#घोषणा STS1_SDIO_INT			0x01
#घोषणा STS1_CMDRSP_DONE		0x02
#घोषणा STS1_RSP_TIMEOUT		0x04
#घोषणा STS1_AUTOSTOP_DONE		0x08
#घोषणा STS1_DATA_TIMEOUT		0x10
#घोषणा STS1_RSP_CRC_ERR		0x20
#घोषणा STS1_RCRC_ERR			0x40
#घोषणा STS1_WCRC_ERR			0x80

/* SDMMC_STS2 bit fields */
#घोषणा STS2_CMD_RES_BUSY		0x10
#घोषणा STS2_DATARSP_BUSY		0x20
#घोषणा STS2_DIS_FORCECLK		0x80

/* SDMMC_EXTCTRL bit fields */
#घोषणा EXT_EIGHTBIT			0x04

/* MMC/SD DMA Controller Registers */
#घोषणा SDDMA_GCR			0x100
#घोषणा SDDMA_IER			0x104
#घोषणा SDDMA_ISR			0x108
#घोषणा SDDMA_DESPR			0x10C
#घोषणा SDDMA_RBR			0x110
#घोषणा SDDMA_DAR			0x114
#घोषणा SDDMA_BAR			0x118
#घोषणा SDDMA_CPR			0x11C
#घोषणा SDDMA_CCR			0x120


/* SDDMA_GCR bit fields */
#घोषणा DMA_GCR_DMA_EN			0x00000001
#घोषणा DMA_GCR_SOFT_RESET		0x00000100

/* SDDMA_IER bit fields */
#घोषणा DMA_IER_INT_EN			0x00000001

/* SDDMA_ISR bit fields */
#घोषणा DMA_ISR_INT_STS			0x00000001

/* SDDMA_RBR bit fields */
#घोषणा DMA_RBR_FORMAT			0x40000000
#घोषणा DMA_RBR_END			0x80000000

/* SDDMA_CCR bit fields */
#घोषणा DMA_CCR_RUN			0x00000080
#घोषणा DMA_CCR_IF_TO_PERIPHERAL	0x00000000
#घोषणा DMA_CCR_PERIPHERAL_TO_IF	0x00400000

/* SDDMA_CCR event status */
#घोषणा DMA_CCR_EVT_NO_STATUS		0x00000000
#घोषणा DMA_CCR_EVT_UNDERRUN		0x00000001
#घोषणा DMA_CCR_EVT_OVERRUN		0x00000002
#घोषणा DMA_CCR_EVT_DESP_READ		0x00000003
#घोषणा DMA_CCR_EVT_DATA_RW		0x00000004
#घोषणा DMA_CCR_EVT_EARLY_END		0x00000005
#घोषणा DMA_CCR_EVT_SUCCESS		0x0000000F

#घोषणा PDMA_READ			0x00
#घोषणा PDMA_WRITE			0x01

#घोषणा WMT_SD_POWER_OFF		0
#घोषणा WMT_SD_POWER_ON			1

काष्ठा wmt_dma_descriptor अणु
	u32 flags;
	u32 data_buffer_addr;
	u32 branch_addr;
	u32 reserved1;
पूर्ण;

काष्ठा wmt_mci_caps अणु
	अचिन्हित पूर्णांक	f_min;
	अचिन्हित पूर्णांक	f_max;
	u32		ocr_avail;
	u32		caps;
	u32		max_seg_size;
	u32		max_segs;
	u32		max_blk_size;
पूर्ण;

काष्ठा wmt_mci_priv अणु
	काष्ठा mmc_host *mmc;
	व्योम __iomem *sdmmc_base;

	पूर्णांक irq_regular;
	पूर्णांक irq_dma;

	व्योम *dma_desc_buffer;
	dma_addr_t dma_desc_device_addr;

	काष्ठा completion cmdcomp;
	काष्ठा completion datacomp;

	काष्ठा completion *comp_cmd;
	काष्ठा completion *comp_dma;

	काष्ठा mmc_request *req;
	काष्ठा mmc_command *cmd;

	काष्ठा clk *clk_sdmmc;
	काष्ठा device *dev;

	u8 घातer_inverted;
	u8 cd_inverted;
पूर्ण;

अटल व्योम wmt_set_sd_घातer(काष्ठा wmt_mci_priv *priv, पूर्णांक enable)
अणु
	u32 reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_BUSMODE);

	अगर (enable ^ priv->घातer_inverted)
		reg_पंचांगp &= ~BM_SD_OFF;
	अन्यथा
		reg_पंचांगp |= BM_SD_OFF;

	ग_लिखोb(reg_पंचांगp, priv->sdmmc_base + SDMMC_BUSMODE);
पूर्ण

अटल व्योम wmt_mci_पढ़ो_response(काष्ठा mmc_host *mmc)
अणु
	काष्ठा wmt_mci_priv *priv;
	पूर्णांक idx1, idx2;
	u8 पंचांगp_resp;
	u32 response;

	priv = mmc_priv(mmc);

	क्रम (idx1 = 0; idx1 < 4; idx1++) अणु
		response = 0;
		क्रम (idx2 = 0; idx2 < 4; idx2++) अणु
			अगर ((idx1 == 3) && (idx2 == 3))
				पंचांगp_resp = पढ़ोb(priv->sdmmc_base + SDMMC_RSP);
			अन्यथा
				पंचांगp_resp = पढ़ोb(priv->sdmmc_base + SDMMC_RSP +
						 (idx1*4) + idx2 + 1);
			response |= (पंचांगp_resp << (idx2 * 8));
		पूर्ण
		priv->cmd->resp[idx1] = cpu_to_be32(response);
	पूर्ण
पूर्ण

अटल व्योम wmt_mci_start_command(काष्ठा wmt_mci_priv *priv)
अणु
	u32 reg_पंचांगp;

	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_CTLR);
	ग_लिखोb(reg_पंचांगp | CTLR_CMD_START, priv->sdmmc_base + SDMMC_CTLR);
पूर्ण

अटल पूर्णांक wmt_mci_send_command(काष्ठा mmc_host *mmc, u8 command, u8 cmdtype,
				u32 arg, u8 rsptype)
अणु
	काष्ठा wmt_mci_priv *priv;
	u32 reg_पंचांगp;

	priv = mmc_priv(mmc);

	/* ग_लिखो command, arg, resptype रेजिस्टरs */
	ग_लिखोb(command, priv->sdmmc_base + SDMMC_CMD);
	ग_लिखोl(arg, priv->sdmmc_base + SDMMC_ARG);
	ग_लिखोb(rsptype, priv->sdmmc_base + SDMMC_RSPTYPE);

	/* reset response FIFO */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_CTLR);
	ग_लिखोb(reg_पंचांगp | CTLR_FIFO_RESET, priv->sdmmc_base + SDMMC_CTLR);

	/* ensure घड़ी enabled - VT3465 */
	wmt_set_sd_घातer(priv, WMT_SD_POWER_ON);

	/* clear status bits */
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS0);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS1);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS2);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS3);

	/* set command type */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_CTLR);
	ग_लिखोb((reg_पंचांगp & 0x0F) | (cmdtype << 4),
	       priv->sdmmc_base + SDMMC_CTLR);

	वापस 0;
पूर्ण

अटल व्योम wmt_mci_disable_dma(काष्ठा wmt_mci_priv *priv)
अणु
	ग_लिखोl(DMA_ISR_INT_STS, priv->sdmmc_base + SDDMA_ISR);
	ग_लिखोl(0, priv->sdmmc_base + SDDMA_IER);
पूर्ण

अटल व्योम wmt_complete_data_request(काष्ठा wmt_mci_priv *priv)
अणु
	काष्ठा mmc_request *req;
	req = priv->req;

	req->data->bytes_xfered = req->data->blksz * req->data->blocks;

	/* unmap the DMA pages used क्रम ग_लिखो data */
	अगर (req->data->flags & MMC_DATA_WRITE)
		dma_unmap_sg(mmc_dev(priv->mmc), req->data->sg,
			     req->data->sg_len, DMA_TO_DEVICE);
	अन्यथा
		dma_unmap_sg(mmc_dev(priv->mmc), req->data->sg,
			     req->data->sg_len, DMA_FROM_DEVICE);

	/* Check अगर the DMA ISR वापसed a data error */
	अगर ((req->cmd->error) || (req->data->error))
		mmc_request_करोne(priv->mmc, req);
	अन्यथा अणु
		wmt_mci_पढ़ो_response(priv->mmc);
		अगर (!req->data->stop) अणु
			/* single-block पढ़ो/ग_लिखो requests end here */
			mmc_request_करोne(priv->mmc, req);
		पूर्ण अन्यथा अणु
			/*
			 * we change the priv->cmd variable so the response is
			 * stored in the stop काष्ठा rather than the original
			 * calling command काष्ठा
			 */
			priv->comp_cmd = &priv->cmdcomp;
			init_completion(priv->comp_cmd);
			priv->cmd = req->data->stop;
			wmt_mci_send_command(priv->mmc, req->data->stop->opcode,
					     7, req->data->stop->arg, 9);
			wmt_mci_start_command(priv);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t wmt_mci_dma_isr(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा wmt_mci_priv *priv;

	पूर्णांक status;

	priv = (काष्ठा wmt_mci_priv *)data;

	status = पढ़ोl(priv->sdmmc_base + SDDMA_CCR) & 0x0F;

	अगर (status != DMA_CCR_EVT_SUCCESS) अणु
		dev_err(priv->dev, "DMA Error: Status = %d\n", status);
		priv->req->data->error = -ETIMEDOUT;
		complete(priv->comp_dma);
		वापस IRQ_HANDLED;
	पूर्ण

	priv->req->data->error = 0;

	wmt_mci_disable_dma(priv);

	complete(priv->comp_dma);

	अगर (priv->comp_cmd) अणु
		अगर (completion_करोne(priv->comp_cmd)) अणु
			/*
			 * अगर the command (regular) पूर्णांकerrupt has alपढ़ोy
			 * completed, finish off the request otherwise we रुको
			 * क्रम the command पूर्णांकerrupt and finish from there.
			 */
			wmt_complete_data_request(priv);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wmt_mci_regular_isr(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा wmt_mci_priv *priv;
	u32 status0;
	u32 status1;
	u32 status2;
	u32 reg_पंचांगp;
	पूर्णांक cmd_करोne;

	priv = (काष्ठा wmt_mci_priv *)data;
	cmd_करोne = 0;
	status0 = पढ़ोb(priv->sdmmc_base + SDMMC_STS0);
	status1 = पढ़ोb(priv->sdmmc_base + SDMMC_STS1);
	status2 = पढ़ोb(priv->sdmmc_base + SDMMC_STS2);

	/* Check क्रम card insertion */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_INTMASK0);
	अगर ((reg_पंचांगp & INT0_DI_INT_EN) && (status0 & STS0_DEVICE_INS)) अणु
		mmc_detect_change(priv->mmc, 0);
		अगर (priv->cmd)
			priv->cmd->error = -ETIMEDOUT;
		अगर (priv->comp_cmd)
			complete(priv->comp_cmd);
		अगर (priv->comp_dma) अणु
			wmt_mci_disable_dma(priv);
			complete(priv->comp_dma);
		पूर्ण
		ग_लिखोb(STS0_DEVICE_INS, priv->sdmmc_base + SDMMC_STS0);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर ((!priv->req->data) ||
	    ((priv->req->data->stop) && (priv->cmd == priv->req->data->stop))) अणु
		/* handle non-data & stop_transmission requests */
		अगर (status1 & STS1_CMDRSP_DONE) अणु
			priv->cmd->error = 0;
			cmd_करोne = 1;
		पूर्ण अन्यथा अगर ((status1 & STS1_RSP_TIMEOUT) ||
			   (status1 & STS1_DATA_TIMEOUT)) अणु
			priv->cmd->error = -ETIMEDOUT;
			cmd_करोne = 1;
		पूर्ण

		अगर (cmd_करोne) अणु
			priv->comp_cmd = शून्य;

			अगर (!priv->cmd->error)
				wmt_mci_पढ़ो_response(priv->mmc);

			priv->cmd = शून्य;

			mmc_request_करोne(priv->mmc, priv->req);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* handle data requests */
		अगर (status1 & STS1_CMDRSP_DONE) अणु
			अगर (priv->cmd)
				priv->cmd->error = 0;
			अगर (priv->comp_cmd)
				complete(priv->comp_cmd);
		पूर्ण

		अगर ((status1 & STS1_RSP_TIMEOUT) ||
		    (status1 & STS1_DATA_TIMEOUT)) अणु
			अगर (priv->cmd)
				priv->cmd->error = -ETIMEDOUT;
			अगर (priv->comp_cmd)
				complete(priv->comp_cmd);
			अगर (priv->comp_dma) अणु
				wmt_mci_disable_dma(priv);
				complete(priv->comp_dma);
			पूर्ण
		पूर्ण

		अगर (priv->comp_dma) अणु
			/*
			 * If the dma पूर्णांकerrupt has alपढ़ोy completed, finish
			 * off the request; otherwise we रुको क्रम the DMA
			 * पूर्णांकerrupt and finish from there.
			 */
			अगर (completion_करोne(priv->comp_dma))
				wmt_complete_data_request(priv);
		पूर्ण
	पूर्ण

	ग_लिखोb(status0, priv->sdmmc_base + SDMMC_STS0);
	ग_लिखोb(status1, priv->sdmmc_base + SDMMC_STS1);
	ग_लिखोb(status2, priv->sdmmc_base + SDMMC_STS2);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wmt_reset_hardware(काष्ठा mmc_host *mmc)
अणु
	काष्ठा wmt_mci_priv *priv;
	u32 reg_पंचांगp;

	priv = mmc_priv(mmc);

	/* reset controller */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_BUSMODE);
	ग_लिखोb(reg_पंचांगp | BM_SOFT_RESET, priv->sdmmc_base + SDMMC_BUSMODE);

	/* reset response FIFO */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_CTLR);
	ग_लिखोb(reg_पंचांगp | CTLR_FIFO_RESET, priv->sdmmc_base + SDMMC_CTLR);

	/* enable GPI pin to detect card */
	ग_लिखोw(BLKL_INT_ENABLE | BLKL_GPI_CD, priv->sdmmc_base + SDMMC_BLKLEN);

	/* clear पूर्णांकerrupt status */
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS0);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS1);

	/* setup पूर्णांकerrupts */
	ग_लिखोb(INT0_CD_INT_EN | INT0_DI_INT_EN, priv->sdmmc_base +
	       SDMMC_INTMASK0);
	ग_लिखोb(INT1_DATA_TOUT_INT_EN | INT1_CMD_RES_TRAN_DONE_INT_EN |
	       INT1_CMD_RES_TOUT_INT_EN, priv->sdmmc_base + SDMMC_INTMASK1);

	/* set the DMA समयout */
	ग_लिखोw(8191, priv->sdmmc_base + SDMMC_DMATIMEOUT);

	/* स्वतः घड़ी मुक्तzing enable */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_STS2);
	ग_लिखोb(reg_पंचांगp | STS2_DIS_FORCECLK, priv->sdmmc_base + SDMMC_STS2);

	/* set a शेष घड़ी speed of 400Khz */
	clk_set_rate(priv->clk_sdmmc, 400000);
पूर्ण

अटल पूर्णांक wmt_dma_init(काष्ठा mmc_host *mmc)
अणु
	काष्ठा wmt_mci_priv *priv;

	priv = mmc_priv(mmc);

	ग_लिखोl(DMA_GCR_SOFT_RESET, priv->sdmmc_base + SDDMA_GCR);
	ग_लिखोl(DMA_GCR_DMA_EN, priv->sdmmc_base + SDDMA_GCR);
	अगर ((पढ़ोl(priv->sdmmc_base + SDDMA_GCR) & DMA_GCR_DMA_EN) != 0)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल व्योम wmt_dma_init_descriptor(काष्ठा wmt_dma_descriptor *desc,
		u16 req_count, u32 buffer_addr, u32 branch_addr, पूर्णांक end)
अणु
	desc->flags = 0x40000000 | req_count;
	अगर (end)
		desc->flags |= 0x80000000;
	desc->data_buffer_addr = buffer_addr;
	desc->branch_addr = branch_addr;
पूर्ण

अटल व्योम wmt_dma_config(काष्ठा mmc_host *mmc, u32 descaddr, u8 dir)
अणु
	काष्ठा wmt_mci_priv *priv;
	u32 reg_पंचांगp;

	priv = mmc_priv(mmc);

	/* Enable DMA Interrupts */
	ग_लिखोl(DMA_IER_INT_EN, priv->sdmmc_base + SDDMA_IER);

	/* Write DMA Descriptor Poपूर्णांकer Register */
	ग_लिखोl(descaddr, priv->sdmmc_base + SDDMA_DESPR);

	ग_लिखोl(0x00, priv->sdmmc_base + SDDMA_CCR);

	अगर (dir == PDMA_WRITE) अणु
		reg_पंचांगp = पढ़ोl(priv->sdmmc_base + SDDMA_CCR);
		ग_लिखोl(reg_पंचांगp & DMA_CCR_IF_TO_PERIPHERAL, priv->sdmmc_base +
		       SDDMA_CCR);
	पूर्ण अन्यथा अणु
		reg_पंचांगp = पढ़ोl(priv->sdmmc_base + SDDMA_CCR);
		ग_लिखोl(reg_पंचांगp | DMA_CCR_PERIPHERAL_TO_IF, priv->sdmmc_base +
		       SDDMA_CCR);
	पूर्ण
पूर्ण

अटल व्योम wmt_dma_start(काष्ठा wmt_mci_priv *priv)
अणु
	u32 reg_पंचांगp;

	reg_पंचांगp = पढ़ोl(priv->sdmmc_base + SDDMA_CCR);
	ग_लिखोl(reg_पंचांगp | DMA_CCR_RUN, priv->sdmmc_base + SDDMA_CCR);
पूर्ण

अटल व्योम wmt_mci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा wmt_mci_priv *priv;
	काष्ठा wmt_dma_descriptor *desc;
	u8 command;
	u8 cmdtype;
	u32 arg;
	u8 rsptype;
	u32 reg_पंचांगp;

	काष्ठा scatterlist *sg;
	पूर्णांक i;
	पूर्णांक sg_cnt;
	पूर्णांक offset;
	u32 dma_address;
	पूर्णांक desc_cnt;

	priv = mmc_priv(mmc);
	priv->req = req;

	/*
	 * Use the cmd variable to pass a poपूर्णांकer to the resp[] काष्ठाure
	 * This is required on multi-block requests to pass the poपूर्णांकer to the
	 * stop command
	 */
	priv->cmd = req->cmd;

	command = req->cmd->opcode;
	arg = req->cmd->arg;
	rsptype = mmc_resp_type(req->cmd);
	cmdtype = 0;

	/* rsptype=7 only valid क्रम SPI commands - should be =2 क्रम SD */
	अगर (rsptype == 7)
		rsptype = 2;
	/* rsptype=21 is R1B, convert क्रम controller */
	अगर (rsptype == 21)
		rsptype = 9;

	अगर (!req->data) अणु
		wmt_mci_send_command(mmc, command, cmdtype, arg, rsptype);
		wmt_mci_start_command(priv);
		/* completion is now handled in the regular_isr() */
	पूर्ण
	अगर (req->data) अणु
		priv->comp_cmd = &priv->cmdcomp;
		init_completion(priv->comp_cmd);

		wmt_dma_init(mmc);

		/* set controller data length */
		reg_पंचांगp = पढ़ोw(priv->sdmmc_base + SDMMC_BLKLEN);
		ग_लिखोw((reg_पंचांगp & 0xF800) | (req->data->blksz - 1),
		       priv->sdmmc_base + SDMMC_BLKLEN);

		/* set controller block count */
		ग_लिखोw(req->data->blocks, priv->sdmmc_base + SDMMC_BLKCNT);

		desc = (काष्ठा wmt_dma_descriptor *)priv->dma_desc_buffer;

		अगर (req->data->flags & MMC_DATA_WRITE) अणु
			sg_cnt = dma_map_sg(mmc_dev(mmc), req->data->sg,
					    req->data->sg_len, DMA_TO_DEVICE);
			cmdtype = 1;
			अगर (req->data->blocks > 1)
				cmdtype = 3;
		पूर्ण अन्यथा अणु
			sg_cnt = dma_map_sg(mmc_dev(mmc), req->data->sg,
					    req->data->sg_len, DMA_FROM_DEVICE);
			cmdtype = 2;
			अगर (req->data->blocks > 1)
				cmdtype = 4;
		पूर्ण

		dma_address = priv->dma_desc_device_addr + 16;
		desc_cnt = 0;

		क्रम_each_sg(req->data->sg, sg, sg_cnt, i) अणु
			offset = 0;
			जबतक (offset < sg_dma_len(sg)) अणु
				wmt_dma_init_descriptor(desc, req->data->blksz,
						sg_dma_address(sg)+offset,
						dma_address, 0);
				desc++;
				desc_cnt++;
				offset += req->data->blksz;
				dma_address += 16;
				अगर (desc_cnt == req->data->blocks)
					अवरोध;
			पूर्ण
		पूर्ण
		desc--;
		desc->flags |= 0x80000000;

		अगर (req->data->flags & MMC_DATA_WRITE)
			wmt_dma_config(mmc, priv->dma_desc_device_addr,
				       PDMA_WRITE);
		अन्यथा
			wmt_dma_config(mmc, priv->dma_desc_device_addr,
				       PDMA_READ);

		wmt_mci_send_command(mmc, command, cmdtype, arg, rsptype);

		priv->comp_dma = &priv->datacomp;
		init_completion(priv->comp_dma);

		wmt_dma_start(priv);
		wmt_mci_start_command(priv);
	पूर्ण
पूर्ण

अटल व्योम wmt_mci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा wmt_mci_priv *priv;
	u32 busmode, extctrl;

	priv = mmc_priv(mmc);

	अगर (ios->घातer_mode == MMC_POWER_UP) अणु
		wmt_reset_hardware(mmc);

		wmt_set_sd_घातer(priv, WMT_SD_POWER_ON);
	पूर्ण
	अगर (ios->घातer_mode == MMC_POWER_OFF)
		wmt_set_sd_घातer(priv, WMT_SD_POWER_OFF);

	अगर (ios->घड़ी != 0)
		clk_set_rate(priv->clk_sdmmc, ios->घड़ी);

	busmode = पढ़ोb(priv->sdmmc_base + SDMMC_BUSMODE);
	extctrl = पढ़ोb(priv->sdmmc_base + SDMMC_EXTCTRL);

	busmode &= ~(BM_EIGHTBIT_MODE | BM_FOURBIT_MODE);
	extctrl &= ~EXT_EIGHTBIT;

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_8:
		busmode |= BM_EIGHTBIT_MODE;
		extctrl |= EXT_EIGHTBIT;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		busmode |= BM_FOURBIT_MODE;
		अवरोध;
	हाल MMC_BUS_WIDTH_1:
		अवरोध;
	पूर्ण

	ग_लिखोb(busmode, priv->sdmmc_base + SDMMC_BUSMODE);
	ग_लिखोb(extctrl, priv->sdmmc_base + SDMMC_EXTCTRL);
पूर्ण

अटल पूर्णांक wmt_mci_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा wmt_mci_priv *priv = mmc_priv(mmc);

	वापस !(पढ़ोb(priv->sdmmc_base + SDMMC_STS0) & STS0_WRITE_PROTECT);
पूर्ण

अटल पूर्णांक wmt_mci_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा wmt_mci_priv *priv = mmc_priv(mmc);
	u32 cd = (पढ़ोb(priv->sdmmc_base + SDMMC_STS0) & STS0_CD_GPI) >> 3;

	वापस !(cd ^ priv->cd_inverted);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops wmt_mci_ops = अणु
	.request = wmt_mci_request,
	.set_ios = wmt_mci_set_ios,
	.get_ro = wmt_mci_get_ro,
	.get_cd = wmt_mci_get_cd,
पूर्ण;

/* Controller capabilities */
अटल काष्ठा wmt_mci_caps wm8505_caps = अणु
	.f_min = 390425,
	.f_max = 50000000,
	.ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34,
	.caps = MMC_CAP_4_BIT_DATA | MMC_CAP_MMC_HIGHSPEED |
		MMC_CAP_SD_HIGHSPEED,
	.max_seg_size = 65024,
	.max_segs = 128,
	.max_blk_size = 2048,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wmt_mci_dt_ids[] = अणु
	अणु .compatible = "wm,wm8505-sdhc", .data = &wm8505_caps पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक wmt_mci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा wmt_mci_priv *priv;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(wmt_mci_dt_ids, &pdev->dev);
	स्थिर काष्ठा wmt_mci_caps *wmt_caps;
	पूर्णांक ret;
	पूर्णांक regular_irq, dma_irq;

	अगर (!of_id || !of_id->data) अणु
		dev_err(&pdev->dev, "Controller capabilities data missing\n");
		वापस -EFAULT;
	पूर्ण

	wmt_caps = of_id->data;

	अगर (!np) अणु
		dev_err(&pdev->dev, "Missing SDMMC description in devicetree\n");
		वापस -EFAULT;
	पूर्ण

	regular_irq = irq_of_parse_and_map(np, 0);
	dma_irq = irq_of_parse_and_map(np, 1);

	अगर (!regular_irq || !dma_irq) अणु
		dev_err(&pdev->dev, "Getting IRQs failed!\n");
		ret = -ENXIO;
		जाओ fail1;
	पूर्ण

	mmc = mmc_alloc_host(माप(काष्ठा wmt_mci_priv), &pdev->dev);
	अगर (!mmc) अणु
		dev_err(&pdev->dev, "Failed to allocate mmc_host\n");
		ret = -ENOMEM;
		जाओ fail1;
	पूर्ण

	mmc->ops = &wmt_mci_ops;
	mmc->f_min = wmt_caps->f_min;
	mmc->f_max = wmt_caps->f_max;
	mmc->ocr_avail = wmt_caps->ocr_avail;
	mmc->caps = wmt_caps->caps;

	mmc->max_seg_size = wmt_caps->max_seg_size;
	mmc->max_segs = wmt_caps->max_segs;
	mmc->max_blk_size = wmt_caps->max_blk_size;

	mmc->max_req_size = (16*512*mmc->max_segs);
	mmc->max_blk_count = mmc->max_req_size / 512;

	priv = mmc_priv(mmc);
	priv->mmc = mmc;
	priv->dev = &pdev->dev;

	priv->घातer_inverted = 0;
	priv->cd_inverted = 0;

	अगर (of_get_property(np, "sdon-inverted", शून्य))
		priv->घातer_inverted = 1;
	अगर (of_get_property(np, "cd-inverted", शून्य))
		priv->cd_inverted = 1;

	priv->sdmmc_base = of_iomap(np, 0);
	अगर (!priv->sdmmc_base) अणु
		dev_err(&pdev->dev, "Failed to map IO space\n");
		ret = -ENOMEM;
		जाओ fail2;
	पूर्ण

	priv->irq_regular = regular_irq;
	priv->irq_dma = dma_irq;

	ret = request_irq(regular_irq, wmt_mci_regular_isr, 0, "sdmmc", priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Register regular IRQ fail\n");
		जाओ fail3;
	पूर्ण

	ret = request_irq(dma_irq, wmt_mci_dma_isr, 0, "sdmmc", priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Register DMA IRQ fail\n");
		जाओ fail4;
	पूर्ण

	/* alloc some DMA buffers क्रम descriptors/transfers */
	priv->dma_desc_buffer = dma_alloc_coherent(&pdev->dev,
						   mmc->max_blk_count * 16,
						   &priv->dma_desc_device_addr,
						   GFP_KERNEL);
	अगर (!priv->dma_desc_buffer) अणु
		dev_err(&pdev->dev, "DMA alloc fail\n");
		ret = -EPERM;
		जाओ fail5;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mmc);

	priv->clk_sdmmc = of_clk_get(np, 0);
	अगर (IS_ERR(priv->clk_sdmmc)) अणु
		dev_err(&pdev->dev, "Error getting clock\n");
		ret = PTR_ERR(priv->clk_sdmmc);
		जाओ fail5;
	पूर्ण

	ret = clk_prepare_enable(priv->clk_sdmmc);
	अगर (ret)
		जाओ fail6;

	/* configure the controller to a known 'ready' state */
	wmt_reset_hardware(mmc);

	mmc_add_host(mmc);

	dev_info(&pdev->dev, "WMT SDHC Controller initialized\n");

	वापस 0;
fail6:
	clk_put(priv->clk_sdmmc);
fail5:
	मुक्त_irq(dma_irq, priv);
fail4:
	मुक्त_irq(regular_irq, priv);
fail3:
	iounmap(priv->sdmmc_base);
fail2:
	mmc_मुक्त_host(mmc);
fail1:
	वापस ret;
पूर्ण

अटल पूर्णांक wmt_mci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा wmt_mci_priv *priv;
	काष्ठा resource *res;
	u32 reg_पंचांगp;

	mmc = platक्रमm_get_drvdata(pdev);
	priv = mmc_priv(mmc);

	/* reset SD controller */
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_BUSMODE);
	ग_लिखोl(reg_पंचांगp | BM_SOFT_RESET, priv->sdmmc_base + SDMMC_BUSMODE);
	reg_पंचांगp = पढ़ोw(priv->sdmmc_base + SDMMC_BLKLEN);
	ग_लिखोw(reg_पंचांगp & ~(0xA000), priv->sdmmc_base + SDMMC_BLKLEN);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS0);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS1);

	/* release the dma buffers */
	dma_मुक्त_coherent(&pdev->dev, priv->mmc->max_blk_count * 16,
			  priv->dma_desc_buffer, priv->dma_desc_device_addr);

	mmc_हटाओ_host(mmc);

	मुक्त_irq(priv->irq_regular, priv);
	मुक्त_irq(priv->irq_dma, priv);

	iounmap(priv->sdmmc_base);

	clk_disable_unprepare(priv->clk_sdmmc);
	clk_put(priv->clk_sdmmc);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	mmc_मुक्त_host(mmc);

	dev_info(&pdev->dev, "WMT MCI device removed\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wmt_mci_suspend(काष्ठा device *dev)
अणु
	u32 reg_पंचांगp;
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा wmt_mci_priv *priv;

	अगर (!mmc)
		वापस 0;

	priv = mmc_priv(mmc);
	reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_BUSMODE);
	ग_लिखोb(reg_पंचांगp | BM_SOFT_RESET, priv->sdmmc_base +
	       SDMMC_BUSMODE);

	reg_पंचांगp = पढ़ोw(priv->sdmmc_base + SDMMC_BLKLEN);
	ग_लिखोw(reg_पंचांगp & 0x5FFF, priv->sdmmc_base + SDMMC_BLKLEN);

	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS0);
	ग_लिखोb(0xFF, priv->sdmmc_base + SDMMC_STS1);

	clk_disable(priv->clk_sdmmc);
	वापस 0;
पूर्ण

अटल पूर्णांक wmt_mci_resume(काष्ठा device *dev)
अणु
	u32 reg_पंचांगp;
	काष्ठा mmc_host *mmc = dev_get_drvdata(dev);
	काष्ठा wmt_mci_priv *priv;

	अगर (mmc) अणु
		priv = mmc_priv(mmc);
		clk_enable(priv->clk_sdmmc);

		reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_BUSMODE);
		ग_लिखोb(reg_पंचांगp | BM_SOFT_RESET, priv->sdmmc_base +
		       SDMMC_BUSMODE);

		reg_पंचांगp = पढ़ोw(priv->sdmmc_base + SDMMC_BLKLEN);
		ग_लिखोw(reg_पंचांगp | (BLKL_GPI_CD | BLKL_INT_ENABLE),
		       priv->sdmmc_base + SDMMC_BLKLEN);

		reg_पंचांगp = पढ़ोb(priv->sdmmc_base + SDMMC_INTMASK0);
		ग_लिखोb(reg_पंचांगp | INT0_DI_INT_EN, priv->sdmmc_base +
		       SDMMC_INTMASK0);

	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wmt_mci_pm = अणु
	.suspend        = wmt_mci_suspend,
	.resume         = wmt_mci_resume,
पूर्ण;

#घोषणा wmt_mci_pm_ops (&wmt_mci_pm)

#अन्यथा	/* !CONFIG_PM */

#घोषणा wmt_mci_pm_ops शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver wmt_mci_driver = अणु
	.probe = wmt_mci_probe,
	.हटाओ = wmt_mci_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm = wmt_mci_pm_ops,
		.of_match_table = wmt_mci_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wmt_mci_driver);

MODULE_DESCRIPTION("Wondermedia MMC/SD Driver");
MODULE_AUTHOR("Tony Prisk");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, wmt_mci_dt_ids);
