<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम न_अंकD MLC Controller in LPC32xx
 *
 * Author: Roland Stigge <stigge@antcom.de>
 *
 * Copyright तऊ 2011 WORK Microwave GmbH
 * Copyright तऊ 2011, 2012 Roland Stigge
 *
 * न_अंकD Flash Controller Operation:
 * - Read: Auto Decode
 * - Write: Auto Encode
 * - Tested Page Sizes: 2048, 4096
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mtd/lpc32xx_mlc.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>

#घोषणा DRV_NAME "lpc32xx_mlc"

/**********************************************************************
* MLC न_अंकD controller रेजिस्टर offsets
**********************************************************************/

#घोषणा MLC_BUFF(x)			(x + 0x00000)
#घोषणा MLC_DATA(x)			(x + 0x08000)
#घोषणा MLC_CMD(x)			(x + 0x10000)
#घोषणा MLC_ADDR(x)			(x + 0x10004)
#घोषणा MLC_ECC_ENC_REG(x)		(x + 0x10008)
#घोषणा MLC_ECC_DEC_REG(x)		(x + 0x1000C)
#घोषणा MLC_ECC_AUTO_ENC_REG(x)		(x + 0x10010)
#घोषणा MLC_ECC_AUTO_DEC_REG(x)		(x + 0x10014)
#घोषणा MLC_RPR(x)			(x + 0x10018)
#घोषणा MLC_WPR(x)			(x + 0x1001C)
#घोषणा MLC_RUBP(x)			(x + 0x10020)
#घोषणा MLC_ROBP(x)			(x + 0x10024)
#घोषणा MLC_SW_WP_ADD_LOW(x)		(x + 0x10028)
#घोषणा MLC_SW_WP_ADD_HIG(x)		(x + 0x1002C)
#घोषणा MLC_ICR(x)			(x + 0x10030)
#घोषणा MLC_TIME_REG(x)			(x + 0x10034)
#घोषणा MLC_IRQ_MR(x)			(x + 0x10038)
#घोषणा MLC_IRQ_SR(x)			(x + 0x1003C)
#घोषणा MLC_LOCK_PR(x)			(x + 0x10044)
#घोषणा MLC_ISR(x)			(x + 0x10048)
#घोषणा MLC_CEH(x)			(x + 0x1004C)

/**********************************************************************
* MLC_CMD bit definitions
**********************************************************************/
#घोषणा MLCCMD_RESET			0xFF

/**********************************************************************
* MLC_ICR bit definitions
**********************************************************************/
#घोषणा MLCICR_WPROT			(1 << 3)
#घोषणा MLCICR_LARGEBLOCK		(1 << 2)
#घोषणा MLCICR_LONGADDR			(1 << 1)
#घोषणा MLCICR_16BIT			(1 << 0)  /* unsupported by LPC32x0! */

/**********************************************************************
* MLC_TIME_REG bit definitions
**********************************************************************/
#घोषणा MLCTIMEREG_TCEA_DELAY(n)	(((n) & 0x03) << 24)
#घोषणा MLCTIMEREG_BUSY_DELAY(n)	(((n) & 0x1F) << 19)
#घोषणा MLCTIMEREG_न_अंकD_TA(n)		(((n) & 0x07) << 16)
#घोषणा MLCTIMEREG_RD_HIGH(n)		(((n) & 0x0F) << 12)
#घोषणा MLCTIMEREG_RD_LOW(n)		(((n) & 0x0F) << 8)
#घोषणा MLCTIMEREG_WR_HIGH(n)		(((n) & 0x0F) << 4)
#घोषणा MLCTIMEREG_WR_LOW(n)		(((n) & 0x0F) << 0)

/**********************************************************************
* MLC_IRQ_MR and MLC_IRQ_SR bit definitions
**********************************************************************/
#घोषणा MLCIRQ_न_अंकD_READY		(1 << 5)
#घोषणा MLCIRQ_CONTROLLER_READY		(1 << 4)
#घोषणा MLCIRQ_DECODE_FAILURE		(1 << 3)
#घोषणा MLCIRQ_DECODE_ERROR		(1 << 2)
#घोषणा MLCIRQ_ECC_READY		(1 << 1)
#घोषणा MLCIRQ_WRPROT_FAULT		(1 << 0)

/**********************************************************************
* MLC_LOCK_PR bit definitions
**********************************************************************/
#घोषणा MLCLOCKPR_MAGIC			0xA25E

/**********************************************************************
* MLC_ISR bit definitions
**********************************************************************/
#घोषणा MLCISR_DECODER_FAILURE		(1 << 6)
#घोषणा MLCISR_ERRORS			((1 << 4) | (1 << 5))
#घोषणा MLCISR_ERRORS_DETECTED		(1 << 3)
#घोषणा MLCISR_ECC_READY		(1 << 2)
#घोषणा MLCISR_CONTROLLER_READY		(1 << 1)
#घोषणा MLCISR_न_अंकD_READY		(1 << 0)

/**********************************************************************
* MLC_CEH bit definitions
**********************************************************************/
#घोषणा MLCCEH_NORMAL			(1 << 0)

काष्ठा lpc32xx_nand_cfg_mlc अणु
	uपूर्णांक32_t tcea_delay;
	uपूर्णांक32_t busy_delay;
	uपूर्णांक32_t nand_ta;
	uपूर्णांक32_t rd_high;
	uपूर्णांक32_t rd_low;
	uपूर्णांक32_t wr_high;
	uपूर्णांक32_t wr_low;
	पूर्णांक wp_gpio;
	काष्ठा mtd_partition *parts;
	अचिन्हित num_parts;
पूर्ण;

अटल पूर्णांक lpc32xx_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);

	अगर (section >= nand_chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = ((section + 1) * 16) - nand_chip->ecc.bytes;
	oobregion->length = nand_chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);

	अगर (section >= nand_chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = 16 * section;
	oobregion->length = 16 - nand_chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops lpc32xx_ooblayout_ops = अणु
	.ecc = lpc32xx_ooblayout_ecc,
	.मुक्त = lpc32xx_ooblayout_मुक्त,
पूर्ण;

अटल काष्ठा nand_bbt_descr lpc32xx_nand_bbt = अणु
	.options = न_अंकD_BBT_ABSPAGE | न_अंकD_BBT_2BIT | न_अंकD_BBT_NO_OOB |
		   न_अंकD_BBT_WRITE,
	.pages = अणु 524224, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा nand_bbt_descr lpc32xx_nand_bbt_mirror = अणु
	.options = न_अंकD_BBT_ABSPAGE | न_अंकD_BBT_2BIT | न_अंकD_BBT_NO_OOB |
		   न_अंकD_BBT_WRITE,
	.pages = अणु 524160, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

काष्ठा lpc32xx_nand_host अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा nand_chip	nand_chip;
	काष्ठा lpc32xx_mlc_platक्रमm_data *pdata;
	काष्ठा clk		*clk;
	व्योम __iomem		*io_base;
	पूर्णांक			irq;
	काष्ठा lpc32xx_nand_cfg_mlc	*ncfg;
	काष्ठा completion       comp_nand;
	काष्ठा completion       comp_controller;
	uपूर्णांक32_t llptr;
	/*
	 * Physical addresses of ECC buffer, DMA data buffers, OOB data buffer
	 */
	dma_addr_t		oob_buf_phy;
	/*
	 * Virtual addresses of ECC buffer, DMA data buffers, OOB data buffer
	 */
	uपूर्णांक8_t			*oob_buf;
	/* Physical address of DMA base address */
	dma_addr_t		io_base_phy;

	काष्ठा completion	comp_dma;
	काष्ठा dma_chan		*dma_chan;
	काष्ठा dma_slave_config	dma_slave_config;
	काष्ठा scatterlist	sgl;
	uपूर्णांक8_t			*dma_buf;
	uपूर्णांक8_t			*dummy_buf;
	पूर्णांक			mlcsubpages; /* number of 512bytes-subpages */
पूर्ण;

/*
 * Activate/Deactivate DMA Operation:
 *
 * Using the PL080 DMA Controller क्रम transferring the 512 byte subpages
 * instead of करोing पढ़ोl() / ग_लिखोl() in a loop slows it करोwn signअगरicantly.
 * Measurements via getnsसमयofday() upon 512 byte subpage पढ़ोs reveal:
 *
 * - पढ़ोl() of 128 x 32 bits in a loop: ~20us
 * - DMA पढ़ो of 512 bytes (32 bit, 4...128 words bursts): ~60us
 * - DMA पढ़ो of 512 bytes (32 bit, no bursts): ~100us
 *
 * This applies to the transfer itself. In the DMA हाल: only the
 * रुको_क्रम_completion() (DMA setup _not_ included).
 *
 * Note that the 512 bytes subpage transfer is करोne directly from/to a
 * FIFO/buffer inside the न_अंकD controller. Most of the समय (~400-800us क्रम a
 * 2048 bytes page) is spent रुकोing क्रम the न_अंकD IRQ, anyway. (The न_अंकD
 * controller transferring data between its पूर्णांकernal buffer to/from the न_अंकD
 * chip.)
 *
 * Thereक्रमe, using the PL080 DMA is disabled by शेष, क्रम now.
 *
 */
अटल पूर्णांक use_dma;

अटल व्योम lpc32xx_nand_setup(काष्ठा lpc32xx_nand_host *host)
अणु
	uपूर्णांक32_t clkrate, पंचांगp;

	/* Reset MLC controller */
	ग_लिखोl(MLCCMD_RESET, MLC_CMD(host->io_base));
	udelay(1000);

	/* Get base घड़ी क्रम MLC block */
	clkrate = clk_get_rate(host->clk);
	अगर (clkrate == 0)
		clkrate = 104000000;

	/* Unlock MLC_ICR
	 * (among others, will be locked again स्वतःmatically) */
	ग_लिखोw(MLCLOCKPR_MAGIC, MLC_LOCK_PR(host->io_base));

	/* Configure MLC Controller: Large Block, 5 Byte Address */
	पंचांगp = MLCICR_LARGEBLOCK | MLCICR_LONGADDR;
	ग_लिखोl(पंचांगp, MLC_ICR(host->io_base));

	/* Unlock MLC_TIME_REG
	 * (among others, will be locked again स्वतःmatically) */
	ग_लिखोw(MLCLOCKPR_MAGIC, MLC_LOCK_PR(host->io_base));

	/* Compute घड़ी setup values, see LPC and न_अंकD manual */
	पंचांगp = 0;
	पंचांगp |= MLCTIMEREG_TCEA_DELAY(clkrate / host->ncfg->tcea_delay + 1);
	पंचांगp |= MLCTIMEREG_BUSY_DELAY(clkrate / host->ncfg->busy_delay + 1);
	पंचांगp |= MLCTIMEREG_न_अंकD_TA(clkrate / host->ncfg->nand_ta + 1);
	पंचांगp |= MLCTIMEREG_RD_HIGH(clkrate / host->ncfg->rd_high + 1);
	पंचांगp |= MLCTIMEREG_RD_LOW(clkrate / host->ncfg->rd_low);
	पंचांगp |= MLCTIMEREG_WR_HIGH(clkrate / host->ncfg->wr_high + 1);
	पंचांगp |= MLCTIMEREG_WR_LOW(clkrate / host->ncfg->wr_low);
	ग_लिखोl(पंचांगp, MLC_TIME_REG(host->io_base));

	/* Enable IRQ क्रम CONTROLLER_READY and न_अंकD_READY */
	ग_लिखोb(MLCIRQ_CONTROLLER_READY | MLCIRQ_न_अंकD_READY,
			MLC_IRQ_MR(host->io_base));

	/* Normal nCE operation: nCE controlled by controller */
	ग_लिखोl(MLCCEH_NORMAL, MLC_CEH(host->io_base));
पूर्ण

/*
 * Hardware specअगरic access to control lines
 */
अटल व्योम lpc32xx_nand_cmd_ctrl(काष्ठा nand_chip *nand_chip, पूर्णांक cmd,
				  अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(nand_chip);

	अगर (cmd != न_अंकD_CMD_NONE) अणु
		अगर (ctrl & न_अंकD_CLE)
			ग_लिखोl(cmd, MLC_CMD(host->io_base));
		अन्यथा
			ग_लिखोl(cmd, MLC_ADDR(host->io_base));
	पूर्ण
पूर्ण

/*
 * Read Device Ready (न_अंकD device _and_ controller पढ़ोy)
 */
अटल पूर्णांक lpc32xx_nand_device_पढ़ोy(काष्ठा nand_chip *nand_chip)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(nand_chip);

	अगर ((पढ़ोb(MLC_ISR(host->io_base)) &
	     (MLCISR_CONTROLLER_READY | MLCISR_न_अंकD_READY)) ==
	    (MLCISR_CONTROLLER_READY | MLCISR_न_अंकD_READY))
		वापस  1;

	वापस 0;
पूर्ण

अटल irqवापस_t lpc3xxx_nand_irq(पूर्णांक irq, काष्ठा lpc32xx_nand_host *host)
अणु
	uपूर्णांक8_t sr;

	/* Clear पूर्णांकerrupt flag by पढ़ोing status */
	sr = पढ़ोb(MLC_IRQ_SR(host->io_base));
	अगर (sr & MLCIRQ_न_अंकD_READY)
		complete(&host->comp_nand);
	अगर (sr & MLCIRQ_CONTROLLER_READY)
		complete(&host->comp_controller);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lpc32xx_रुकोfunc_nand(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	अगर (पढ़ोb(MLC_ISR(host->io_base)) & MLCISR_न_अंकD_READY)
		जाओ निकास;

	रुको_क्रम_completion(&host->comp_nand);

	जबतक (!(पढ़ोb(MLC_ISR(host->io_base)) & MLCISR_न_अंकD_READY)) अणु
		/* Seems to be delayed someबार by controller */
		dev_dbg(&mtd->dev, "Warning: NAND not ready.\n");
		cpu_relax();
	पूर्ण

निकास:
	वापस न_अंकD_STATUS_READY;
पूर्ण

अटल पूर्णांक lpc32xx_रुकोfunc_controller(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	अगर (पढ़ोb(MLC_ISR(host->io_base)) & MLCISR_CONTROLLER_READY)
		जाओ निकास;

	रुको_क्रम_completion(&host->comp_controller);

	जबतक (!(पढ़ोb(MLC_ISR(host->io_base)) &
		 MLCISR_CONTROLLER_READY)) अणु
		dev_dbg(&mtd->dev, "Warning: Controller not ready.\n");
		cpu_relax();
	पूर्ण

निकास:
	वापस न_अंकD_STATUS_READY;
पूर्ण

अटल पूर्णांक lpc32xx_रुकोfunc(काष्ठा nand_chip *chip)
अणु
	lpc32xx_रुकोfunc_nand(chip);
	lpc32xx_रुकोfunc_controller(chip);

	वापस न_अंकD_STATUS_READY;
पूर्ण

/*
 * Enable न_अंकD ग_लिखो protect
 */
अटल व्योम lpc32xx_wp_enable(काष्ठा lpc32xx_nand_host *host)
अणु
	अगर (gpio_is_valid(host->ncfg->wp_gpio))
		gpio_set_value(host->ncfg->wp_gpio, 0);
पूर्ण

/*
 * Disable न_अंकD ग_लिखो protect
 */
अटल व्योम lpc32xx_wp_disable(काष्ठा lpc32xx_nand_host *host)
अणु
	अगर (gpio_is_valid(host->ncfg->wp_gpio))
		gpio_set_value(host->ncfg->wp_gpio, 1);
पूर्ण

अटल व्योम lpc32xx_dma_complete_func(व्योम *completion)
अणु
	complete(completion);
पूर्ण

अटल पूर्णांक lpc32xx_xmit_dma(काष्ठा mtd_info *mtd, व्योम *mem, पूर्णांक len,
			    क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	पूर्णांक res;

	sg_init_one(&host->sgl, mem, len);

	res = dma_map_sg(host->dma_chan->device->dev, &host->sgl, 1,
			 DMA_BIसूचीECTIONAL);
	अगर (res != 1) अणु
		dev_err(mtd->dev.parent, "Failed to map sg list\n");
		वापस -ENXIO;
	पूर्ण
	desc = dmaengine_prep_slave_sg(host->dma_chan, &host->sgl, 1, dir,
				       flags);
	अगर (!desc) अणु
		dev_err(mtd->dev.parent, "Failed to prepare slave sg\n");
		जाओ out1;
	पूर्ण

	init_completion(&host->comp_dma);
	desc->callback = lpc32xx_dma_complete_func;
	desc->callback_param = &host->comp_dma;

	dmaengine_submit(desc);
	dma_async_issue_pending(host->dma_chan);

	रुको_क्रम_completion_समयout(&host->comp_dma, msecs_to_jअगरfies(1000));

	dma_unmap_sg(host->dma_chan->device->dev, &host->sgl, 1,
		     DMA_BIसूचीECTIONAL);
	वापस 0;
out1:
	dma_unmap_sg(host->dma_chan->device->dev, &host->sgl, 1,
		     DMA_BIसूचीECTIONAL);
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक lpc32xx_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	पूर्णांक i, j;
	uपूर्णांक8_t *oobbuf = chip->oob_poi;
	uपूर्णांक32_t mlc_isr;
	पूर्णांक res;
	uपूर्णांक8_t *dma_buf;
	bool dma_mapped;

	अगर ((व्योम *)buf <= high_memory) अणु
		dma_buf = buf;
		dma_mapped = true;
	पूर्ण अन्यथा अणु
		dma_buf = host->dma_buf;
		dma_mapped = false;
	पूर्ण

	/* Writing Command and Address */
	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	/* For all sub-pages */
	क्रम (i = 0; i < host->mlcsubpages; i++) अणु
		/* Start Auto Decode Command */
		ग_लिखोb(0x00, MLC_ECC_AUTO_DEC_REG(host->io_base));

		/* Wait क्रम Controller Ready */
		lpc32xx_रुकोfunc_controller(chip);

		/* Check ECC Error status */
		mlc_isr = पढ़ोl(MLC_ISR(host->io_base));
		अगर (mlc_isr & MLCISR_DECODER_FAILURE) अणु
			mtd->ecc_stats.failed++;
			dev_warn(&mtd->dev, "%s: DECODER_FAILURE\n", __func__);
		पूर्ण अन्यथा अगर (mlc_isr & MLCISR_ERRORS_DETECTED) अणु
			mtd->ecc_stats.corrected += ((mlc_isr >> 4) & 0x3) + 1;
		पूर्ण

		/* Read 512 + 16 Bytes */
		अगर (use_dma) अणु
			res = lpc32xx_xmit_dma(mtd, dma_buf + i * 512, 512,
					       DMA_DEV_TO_MEM);
			अगर (res)
				वापस res;
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < (512 >> 2); j++) अणु
				*((uपूर्णांक32_t *)(buf)) =
					पढ़ोl(MLC_BUFF(host->io_base));
				buf += 4;
			पूर्ण
		पूर्ण
		क्रम (j = 0; j < (16 >> 2); j++) अणु
			*((uपूर्णांक32_t *)(oobbuf)) =
				पढ़ोl(MLC_BUFF(host->io_base));
			oobbuf += 4;
		पूर्ण
	पूर्ण

	अगर (use_dma && !dma_mapped)
		स_नकल(buf, dma_buf, mtd->ग_लिखोsize);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_ग_लिखो_page_lowlevel(काष्ठा nand_chip *chip,
				       स्थिर uपूर्णांक8_t *buf, पूर्णांक oob_required,
				       पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	स्थिर uपूर्णांक8_t *oobbuf = chip->oob_poi;
	uपूर्णांक8_t *dma_buf = (uपूर्णांक8_t *)buf;
	पूर्णांक res;
	पूर्णांक i, j;

	अगर (use_dma && (व्योम *)buf >= high_memory) अणु
		dma_buf = host->dma_buf;
		स_नकल(dma_buf, buf, mtd->ग_लिखोsize);
	पूर्ण

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	क्रम (i = 0; i < host->mlcsubpages; i++) अणु
		/* Start Encode */
		ग_लिखोb(0x00, MLC_ECC_ENC_REG(host->io_base));

		/* Write 512 + 6 Bytes to Buffer */
		अगर (use_dma) अणु
			res = lpc32xx_xmit_dma(mtd, dma_buf + i * 512, 512,
					       DMA_MEM_TO_DEV);
			अगर (res)
				वापस res;
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < (512 >> 2); j++) अणु
				ग_लिखोl(*((uपूर्णांक32_t *)(buf)),
				       MLC_BUFF(host->io_base));
				buf += 4;
			पूर्ण
		पूर्ण
		ग_लिखोl(*((uपूर्णांक32_t *)(oobbuf)), MLC_BUFF(host->io_base));
		oobbuf += 4;
		ग_लिखोw(*((uपूर्णांक16_t *)(oobbuf)), MLC_BUFF(host->io_base));
		oobbuf += 12;

		/* Auto Encode w/ Bit 8 = 0 (see LPC MLC Controller manual) */
		ग_लिखोb(0x00, MLC_ECC_AUTO_ENC_REG(host->io_base));

		/* Wait क्रम Controller Ready */
		lpc32xx_रुकोfunc_controller(chip);
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक lpc32xx_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Read whole page - necessary with MLC controller! */
	lpc32xx_पढ़ो_page(chip, host->dummy_buf, 1, page);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	/* None, ग_लिखो_oob conflicts with the स्वतःmatic LPC MLC ECC decoder! */
	वापस 0;
पूर्ण

/* Prepares MLC क्रम transfers with H/W ECC enabled: always enabled anyway */
अटल व्योम lpc32xx_ecc_enable(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	/* Always enabled! */
पूर्ण

अटल पूर्णांक lpc32xx_dma_setup(काष्ठा lpc32xx_nand_host *host)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(&host->nand_chip);
	dma_cap_mask_t mask;

	अगर (!host->pdata || !host->pdata->dma_filter) अणु
		dev_err(mtd->dev.parent, "no DMA platform data\n");
		वापस -ENOENT;
	पूर्ण

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	host->dma_chan = dma_request_channel(mask, host->pdata->dma_filter,
					     "nand-mlc");
	अगर (!host->dma_chan) अणु
		dev_err(mtd->dev.parent, "Failed to request DMA channel\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Set direction to a sensible value even अगर the dmaengine driver
	 * should ignore it. With the शेष (DMA_MEM_TO_MEM), the amba-pl08x
	 * driver criticizes it as "alien transfer direction".
	 */
	host->dma_slave_config.direction = DMA_DEV_TO_MEM;
	host->dma_slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->dma_slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->dma_slave_config.src_maxburst = 128;
	host->dma_slave_config.dst_maxburst = 128;
	/* DMA controller करोes flow control: */
	host->dma_slave_config.device_fc = false;
	host->dma_slave_config.src_addr = MLC_BUFF(host->io_base_phy);
	host->dma_slave_config.dst_addr = MLC_BUFF(host->io_base_phy);
	अगर (dmaengine_slave_config(host->dma_chan, &host->dma_slave_config)) अणु
		dev_err(mtd->dev.parent, "Failed to setup DMA slave\n");
		जाओ out1;
	पूर्ण

	वापस 0;
out1:
	dma_release_channel(host->dma_chan);
	वापस -ENXIO;
पूर्ण

अटल काष्ठा lpc32xx_nand_cfg_mlc *lpc32xx_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_nand_cfg_mlc *ncfg;
	काष्ठा device_node *np = dev->of_node;

	ncfg = devm_kzalloc(dev, माप(*ncfg), GFP_KERNEL);
	अगर (!ncfg)
		वापस शून्य;

	of_property_पढ़ो_u32(np, "nxp,tcea-delay", &ncfg->tcea_delay);
	of_property_पढ़ो_u32(np, "nxp,busy-delay", &ncfg->busy_delay);
	of_property_पढ़ो_u32(np, "nxp,nand-ta", &ncfg->nand_ta);
	of_property_पढ़ो_u32(np, "nxp,rd-high", &ncfg->rd_high);
	of_property_पढ़ो_u32(np, "nxp,rd-low", &ncfg->rd_low);
	of_property_पढ़ो_u32(np, "nxp,wr-high", &ncfg->wr_high);
	of_property_पढ़ो_u32(np, "nxp,wr-low", &ncfg->wr_low);

	अगर (!ncfg->tcea_delay || !ncfg->busy_delay || !ncfg->nand_ta ||
	    !ncfg->rd_high || !ncfg->rd_low || !ncfg->wr_high ||
	    !ncfg->wr_low) अणु
		dev_err(dev, "chip parameters not specified correctly\n");
		वापस शून्य;
	पूर्ण

	ncfg->wp_gpio = of_get_named_gpio(np, "gpios", 0);

	वापस ncfg;
पूर्ण

अटल पूर्णांक lpc32xx_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	काष्ठा device *dev = &host->pdev->dev;

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	host->dma_buf = devm_kzalloc(dev, mtd->ग_लिखोsize, GFP_KERNEL);
	अगर (!host->dma_buf)
		वापस -ENOMEM;

	host->dummy_buf = devm_kzalloc(dev, mtd->ग_लिखोsize, GFP_KERNEL);
	अगर (!host->dummy_buf)
		वापस -ENOMEM;

	chip->ecc.size = 512;
	chip->ecc.hwctl = lpc32xx_ecc_enable;
	chip->ecc.पढ़ो_page_raw = lpc32xx_पढ़ो_page;
	chip->ecc.पढ़ो_page = lpc32xx_पढ़ो_page;
	chip->ecc.ग_लिखो_page_raw = lpc32xx_ग_लिखो_page_lowlevel;
	chip->ecc.ग_लिखो_page = lpc32xx_ग_लिखो_page_lowlevel;
	chip->ecc.ग_लिखो_oob = lpc32xx_ग_लिखो_oob;
	chip->ecc.पढ़ो_oob = lpc32xx_पढ़ो_oob;
	chip->ecc.strength = 4;
	chip->ecc.bytes = 10;

	mtd_set_ooblayout(mtd, &lpc32xx_ooblayout_ops);
	host->mlcsubpages = mtd->ग_लिखोsize / 512;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops lpc32xx_nand_controller_ops = अणु
	.attach_chip = lpc32xx_nand_attach_chip,
पूर्ण;

/*
 * Probe क्रम न_अंकD controller
 */
अटल पूर्णांक lpc32xx_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_nand_host *host;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *nand_chip;
	काष्ठा resource *rc;
	पूर्णांक res;

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->pdev = pdev;

	rc = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->io_base = devm_ioremap_resource(&pdev->dev, rc);
	अगर (IS_ERR(host->io_base))
		वापस PTR_ERR(host->io_base);

	host->io_base_phy = rc->start;

	nand_chip = &host->nand_chip;
	mtd = nand_to_mtd(nand_chip);
	अगर (pdev->dev.of_node)
		host->ncfg = lpc32xx_parse_dt(&pdev->dev);
	अगर (!host->ncfg) अणु
		dev_err(&pdev->dev,
			"Missing or bad NAND config from device tree\n");
		वापस -ENOENT;
	पूर्ण
	अगर (host->ncfg->wp_gpio == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(host->ncfg->wp_gpio) &&
			gpio_request(host->ncfg->wp_gpio, "NAND WP")) अणु
		dev_err(&pdev->dev, "GPIO not available\n");
		वापस -EBUSY;
	पूर्ण
	lpc32xx_wp_disable(host);

	host->pdata = dev_get_platdata(&pdev->dev);

	/* link the निजी data काष्ठाures */
	nand_set_controller_data(nand_chip, host);
	nand_set_flash_node(nand_chip, pdev->dev.of_node);
	mtd->dev.parent = &pdev->dev;

	/* Get न_अंकD घड़ी */
	host->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		dev_err(&pdev->dev, "Clock initialization failure\n");
		res = -ENOENT;
		जाओ मुक्त_gpio;
	पूर्ण
	res = clk_prepare_enable(host->clk);
	अगर (res)
		जाओ put_clk;

	nand_chip->legacy.cmd_ctrl = lpc32xx_nand_cmd_ctrl;
	nand_chip->legacy.dev_पढ़ोy = lpc32xx_nand_device_पढ़ोy;
	nand_chip->legacy.chip_delay = 25; /* us */
	nand_chip->legacy.IO_ADDR_R = MLC_DATA(host->io_base);
	nand_chip->legacy.IO_ADDR_W = MLC_DATA(host->io_base);

	/* Init न_अंकD controller */
	lpc32xx_nand_setup(host);

	platक्रमm_set_drvdata(pdev, host);

	/* Initialize function poपूर्णांकers */
	nand_chip->legacy.रुकोfunc = lpc32xx_रुकोfunc;

	nand_chip->options = न_अंकD_NO_SUBPAGE_WRITE;
	nand_chip->bbt_options = न_अंकD_BBT_USE_FLASH | न_अंकD_BBT_NO_OOB;
	nand_chip->bbt_td = &lpc32xx_nand_bbt;
	nand_chip->bbt_md = &lpc32xx_nand_bbt_mirror;

	अगर (use_dma) अणु
		res = lpc32xx_dma_setup(host);
		अगर (res) अणु
			res = -EIO;
			जाओ unprepare_clk;
		पूर्ण
	पूर्ण

	/* initially clear पूर्णांकerrupt status */
	पढ़ोb(MLC_IRQ_SR(host->io_base));

	init_completion(&host->comp_nand);
	init_completion(&host->comp_controller);

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0) अणु
		res = -EINVAL;
		जाओ release_dma_chan;
	पूर्ण

	अगर (request_irq(host->irq, (irq_handler_t)&lpc3xxx_nand_irq,
			IRQF_TRIGGER_HIGH, DRV_NAME, host)) अणु
		dev_err(&pdev->dev, "Error requesting NAND IRQ\n");
		res = -ENXIO;
		जाओ release_dma_chan;
	पूर्ण

	/*
	 * Scan to find existence of the device and get the type of न_अंकD device:
	 * SMALL block or LARGE block.
	 */
	nand_chip->legacy.dummy_controller.ops = &lpc32xx_nand_controller_ops;
	res = nand_scan(nand_chip, 1);
	अगर (res)
		जाओ मुक्त_irq;

	mtd->name = DRV_NAME;

	res = mtd_device_रेजिस्टर(mtd, host->ncfg->parts,
				  host->ncfg->num_parts);
	अगर (res)
		जाओ cleanup_nand;

	वापस 0;

cleanup_nand:
	nand_cleanup(nand_chip);
मुक्त_irq:
	मुक्त_irq(host->irq, host);
release_dma_chan:
	अगर (use_dma)
		dma_release_channel(host->dma_chan);
unprepare_clk:
	clk_disable_unprepare(host->clk);
put_clk:
	clk_put(host->clk);
मुक्त_gpio:
	lpc32xx_wp_enable(host);
	gpio_मुक्त(host->ncfg->wp_gpio);

	वापस res;
पूर्ण

/*
 * Remove न_अंकD device
 */
अटल पूर्णांक lpc32xx_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_nand_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &host->nand_chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	मुक्त_irq(host->irq, host);
	अगर (use_dma)
		dma_release_channel(host->dma_chan);

	clk_disable_unprepare(host->clk);
	clk_put(host->clk);

	lpc32xx_wp_enable(host);
	gpio_मुक्त(host->ncfg->wp_gpio);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lpc32xx_nand_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_nand_host *host = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	/* Re-enable न_अंकD घड़ी */
	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		वापस ret;

	/* Fresh init of न_अंकD controller */
	lpc32xx_nand_setup(host);

	/* Disable ग_लिखो protect */
	lpc32xx_wp_disable(host);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_nand_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t pm)
अणु
	काष्ठा lpc32xx_nand_host *host = platक्रमm_get_drvdata(pdev);

	/* Enable ग_लिखो protect क्रम safety */
	lpc32xx_wp_enable(host);

	/* Disable घड़ी */
	clk_disable_unprepare(host->clk);
	वापस 0;
पूर्ण

#अन्यथा
#घोषणा lpc32xx_nand_resume शून्य
#घोषणा lpc32xx_nand_suspend शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id lpc32xx_nand_match[] = अणु
	अणु .compatible = "nxp,lpc3220-mlc" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_nand_match);

अटल काष्ठा platक्रमm_driver lpc32xx_nand_driver = अणु
	.probe		= lpc32xx_nand_probe,
	.हटाओ		= lpc32xx_nand_हटाओ,
	.resume		= lpc32xx_nand_resume,
	.suspend	= lpc32xx_nand_suspend,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = lpc32xx_nand_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpc32xx_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("NAND driver for the NXP LPC32XX MLC controller");
