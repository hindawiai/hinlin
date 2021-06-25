<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP LPC32XX न_अंकD SLC driver
 *
 * Authors:
 *    Kevin Wells <kevin.wells@nxp.com>
 *    Roland Stigge <stigge@antcom.de>
 *
 * Copyright तऊ 2011 NXP Semiconductors
 * Copyright तऊ 2012 Roland Stigge
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
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mtd/lpc32xx_slc.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>

#घोषणा LPC32XX_MODNAME		"lpc32xx-nand"

/**********************************************************************
* SLC न_अंकD controller रेजिस्टर offsets
**********************************************************************/

#घोषणा SLC_DATA(x)		(x + 0x000)
#घोषणा SLC_ADDR(x)		(x + 0x004)
#घोषणा SLC_CMD(x)		(x + 0x008)
#घोषणा SLC_STOP(x)		(x + 0x00C)
#घोषणा SLC_CTRL(x)		(x + 0x010)
#घोषणा SLC_CFG(x)		(x + 0x014)
#घोषणा SLC_STAT(x)		(x + 0x018)
#घोषणा SLC_INT_STAT(x)		(x + 0x01C)
#घोषणा SLC_IEN(x)		(x + 0x020)
#घोषणा SLC_ISR(x)		(x + 0x024)
#घोषणा SLC_ICR(x)		(x + 0x028)
#घोषणा SLC_TAC(x)		(x + 0x02C)
#घोषणा SLC_TC(x)		(x + 0x030)
#घोषणा SLC_ECC(x)		(x + 0x034)
#घोषणा SLC_DMA_DATA(x)		(x + 0x038)

/**********************************************************************
* slc_ctrl रेजिस्टर definitions
**********************************************************************/
#घोषणा SLCCTRL_SW_RESET	(1 << 2) /* Reset the न_अंकD controller bit */
#घोषणा SLCCTRL_ECC_CLEAR	(1 << 1) /* Reset ECC bit */
#घोषणा SLCCTRL_DMA_START	(1 << 0) /* Start DMA channel bit */

/**********************************************************************
* slc_cfg रेजिस्टर definitions
**********************************************************************/
#घोषणा SLCCFG_CE_LOW		(1 << 5) /* Force CE low bit */
#घोषणा SLCCFG_DMA_ECC		(1 << 4) /* Enable DMA ECC bit */
#घोषणा SLCCFG_ECC_EN		(1 << 3) /* ECC enable bit */
#घोषणा SLCCFG_DMA_BURST	(1 << 2) /* DMA burst bit */
#घोषणा SLCCFG_DMA_सूची		(1 << 1) /* DMA ग_लिखो(0)/पढ़ो(1) bit */
#घोषणा SLCCFG_WIDTH		(1 << 0) /* External device width, 0=8bit */

/**********************************************************************
* slc_stat रेजिस्टर definitions
**********************************************************************/
#घोषणा SLCSTAT_DMA_FIFO	(1 << 2) /* DMA FIFO has data bit */
#घोषणा SLCSTAT_SLC_FIFO	(1 << 1) /* SLC FIFO has data bit */
#घोषणा SLCSTAT_न_अंकD_READY	(1 << 0) /* न_अंकD device is पढ़ोy bit */

/**********************************************************************
* slc_पूर्णांक_stat, slc_ien, slc_isr, and slc_icr रेजिस्टर definitions
**********************************************************************/
#घोषणा SLCSTAT_INT_TC		(1 << 1) /* Transfer count bit */
#घोषणा SLCSTAT_INT_RDY_EN	(1 << 0) /* Ready पूर्णांकerrupt bit */

/**********************************************************************
* slc_tac रेजिस्टर definitions
**********************************************************************/
/* Computation of घड़ी cycles on basis of controller and device घड़ी rates */
#घोषणा SLCTAC_CLOCKS(c, n, s)	(min_t(u32, DIV_ROUND_UP(c, n) - 1, 0xF) << s)

/* Clock setting क्रम RDY ग_लिखो sample रुको समय in 2*n घड़ीs */
#घोषणा SLCTAC_WDR(n)		(((n) & 0xF) << 28)
/* Write pulse width in घड़ी cycles, 1 to 16 घड़ीs */
#घोषणा SLCTAC_WWIDTH(c, n)	(SLCTAC_CLOCKS(c, n, 24))
/* Write hold समय of control and data संकेतs, 1 to 16 घड़ीs */
#घोषणा SLCTAC_WHOLD(c, n)	(SLCTAC_CLOCKS(c, n, 20))
/* Write setup समय of control and data संकेतs, 1 to 16 घड़ीs */
#घोषणा SLCTAC_WSETUP(c, n)	(SLCTAC_CLOCKS(c, n, 16))
/* Clock setting क्रम RDY पढ़ो sample रुको समय in 2*n घड़ीs */
#घोषणा SLCTAC_RDR(n)		(((n) & 0xF) << 12)
/* Read pulse width in घड़ी cycles, 1 to 16 घड़ीs */
#घोषणा SLCTAC_RWIDTH(c, n)	(SLCTAC_CLOCKS(c, n, 8))
/* Read hold समय of control and data संकेतs, 1 to 16 घड़ीs */
#घोषणा SLCTAC_RHOLD(c, n)	(SLCTAC_CLOCKS(c, n, 4))
/* Read setup समय of control and data संकेतs, 1 to 16 घड़ीs */
#घोषणा SLCTAC_RSETUP(c, n)	(SLCTAC_CLOCKS(c, n, 0))

/**********************************************************************
* slc_ecc रेजिस्टर definitions
**********************************************************************/
/* ECC line party fetch macro */
#घोषणा SLCECC_TO_LINEPAR(n)	(((n) >> 6) & 0x7FFF)
#घोषणा SLCECC_TO_COLPAR(n)	((n) & 0x3F)

/*
 * DMA requires storage space क्रम the DMA local buffer and the hardware ECC
 * storage area. The DMA local buffer is only used अगर DMA mapping fails
 * during runसमय.
 */
#घोषणा LPC32XX_DMA_DATA_SIZE		4096
#घोषणा LPC32XX_ECC_SAVE_SIZE		((4096 / 256) * 4)

/* Number of bytes used क्रम ECC stored in न_अंकD per 256 bytes */
#घोषणा LPC32XX_SLC_DEV_ECC_BYTES	3

/*
 * If the न_अंकD base घड़ी frequency can't be fetched, this frequency will be
 * used instead as the base. This rate is used to setup the timing रेजिस्टरs
 * used क्रम न_अंकD accesses.
 */
#घोषणा LPC32XX_DEF_BUS_RATE		133250000

/* Milliseconds क्रम DMA FIFO समयout (unlikely anyway) */
#घोषणा LPC32XX_DMA_TIMEOUT		100

/*
 * न_अंकD ECC Layout क्रम small page न_अंकD devices
 * Note: For large and huge page devices, the शेष layouts are used
 */
अटल पूर्णांक lpc32xx_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->length = 6;
	oobregion->offset = 10;

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 1)
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->offset = 0;
		oobregion->length = 4;
	पूर्ण अन्यथा अणु
		oobregion->offset = 6;
		oobregion->length = 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops lpc32xx_ooblayout_ops = अणु
	.ecc = lpc32xx_ooblayout_ecc,
	.मुक्त = lpc32xx_ooblayout_मुक्त,
पूर्ण;

अटल u8 bbt_pattern[] = अणु'B', 'b', 't', '0' पूर्ण;
अटल u8 mirror_pattern[] = अणु'1', 't', 'b', 'B' पूर्ण;

/*
 * Small page FLASH BBT descriptors, marker at offset 0, version at offset 6
 * Note: Large page devices used the शेष layout
 */
अटल काष्ठा nand_bbt_descr bbt_smallpage_मुख्य_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
		| न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs =	0,
	.len = 4,
	.veroffs = 6,
	.maxblocks = 4,
	.pattern = bbt_pattern
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_smallpage_mirror_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
		| न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs =	0,
	.len = 4,
	.veroffs = 6,
	.maxblocks = 4,
	.pattern = mirror_pattern
पूर्ण;

/*
 * न_अंकD platक्रमm configuration काष्ठाure
 */
काष्ठा lpc32xx_nand_cfg_slc अणु
	uपूर्णांक32_t wdr_clks;
	uपूर्णांक32_t wwidth;
	uपूर्णांक32_t whold;
	uपूर्णांक32_t wsetup;
	uपूर्णांक32_t rdr_clks;
	uपूर्णांक32_t rwidth;
	uपूर्णांक32_t rhold;
	uपूर्णांक32_t rsetup;
	पूर्णांक wp_gpio;
	काष्ठा mtd_partition *parts;
	अचिन्हित num_parts;
पूर्ण;

काष्ठा lpc32xx_nand_host अणु
	काष्ठा nand_chip	nand_chip;
	काष्ठा lpc32xx_slc_platक्रमm_data *pdata;
	काष्ठा clk		*clk;
	व्योम __iomem		*io_base;
	काष्ठा lpc32xx_nand_cfg_slc *ncfg;

	काष्ठा completion	comp;
	काष्ठा dma_chan		*dma_chan;
	uपूर्णांक32_t		dma_buf_len;
	काष्ठा dma_slave_config	dma_slave_config;
	काष्ठा scatterlist	sgl;

	/*
	 * DMA and CPU addresses of ECC work area and data buffer
	 */
	uपूर्णांक32_t		*ecc_buf;
	uपूर्णांक8_t			*data_buf;
	dma_addr_t		io_base_dma;
पूर्ण;

अटल व्योम lpc32xx_nand_setup(काष्ठा lpc32xx_nand_host *host)
अणु
	uपूर्णांक32_t clkrate, पंचांगp;

	/* Reset SLC controller */
	ग_लिखोl(SLCCTRL_SW_RESET, SLC_CTRL(host->io_base));
	udelay(1000);

	/* Basic setup */
	ग_लिखोl(0, SLC_CFG(host->io_base));
	ग_लिखोl(0, SLC_IEN(host->io_base));
	ग_लिखोl((SLCSTAT_INT_TC | SLCSTAT_INT_RDY_EN),
		SLC_ICR(host->io_base));

	/* Get base घड़ी क्रम SLC block */
	clkrate = clk_get_rate(host->clk);
	अगर (clkrate == 0)
		clkrate = LPC32XX_DEF_BUS_RATE;

	/* Compute घड़ी setup values */
	पंचांगp = SLCTAC_WDR(host->ncfg->wdr_clks) |
		SLCTAC_WWIDTH(clkrate, host->ncfg->wwidth) |
		SLCTAC_WHOLD(clkrate, host->ncfg->whold) |
		SLCTAC_WSETUP(clkrate, host->ncfg->wsetup) |
		SLCTAC_RDR(host->ncfg->rdr_clks) |
		SLCTAC_RWIDTH(clkrate, host->ncfg->rwidth) |
		SLCTAC_RHOLD(clkrate, host->ncfg->rhold) |
		SLCTAC_RSETUP(clkrate, host->ncfg->rsetup);
	ग_लिखोl(पंचांगp, SLC_TAC(host->io_base));
पूर्ण

/*
 * Hardware specअगरic access to control lines
 */
अटल व्योम lpc32xx_nand_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd,
				  अचिन्हित पूर्णांक ctrl)
अणु
	uपूर्णांक32_t पंचांगp;
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Does CE state need to be changed? */
	पंचांगp = पढ़ोl(SLC_CFG(host->io_base));
	अगर (ctrl & न_अंकD_NCE)
		पंचांगp |= SLCCFG_CE_LOW;
	अन्यथा
		पंचांगp &= ~SLCCFG_CE_LOW;
	ग_लिखोl(पंचांगp, SLC_CFG(host->io_base));

	अगर (cmd != न_अंकD_CMD_NONE) अणु
		अगर (ctrl & न_अंकD_CLE)
			ग_लिखोl(cmd, SLC_CMD(host->io_base));
		अन्यथा
			ग_लिखोl(cmd, SLC_ADDR(host->io_base));
	पूर्ण
पूर्ण

/*
 * Read the Device Ready pin
 */
अटल पूर्णांक lpc32xx_nand_device_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	पूर्णांक rdy = 0;

	अगर ((पढ़ोl(SLC_STAT(host->io_base)) & SLCSTAT_न_अंकD_READY) != 0)
		rdy = 1;

	वापस rdy;
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

/*
 * Prepares SLC क्रम transfers with H/W ECC enabled
 */
अटल व्योम lpc32xx_nand_ecc_enable(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	/* Hardware ECC is enabled स्वतःmatically in hardware as needed */
पूर्ण

/*
 * Calculates the ECC क्रम the data
 */
अटल पूर्णांक lpc32xx_nand_ecc_calculate(काष्ठा nand_chip *chip,
				      स्थिर अचिन्हित अक्षर *buf,
				      अचिन्हित अक्षर *code)
अणु
	/*
	 * ECC is calculated स्वतःmatically in hardware during syndrome पढ़ो
	 * and ग_लिखो operations, so it करोesn't need to be calculated here.
	 */
	वापस 0;
पूर्ण

/*
 * Corrects the data
 */
अटल पूर्णांक lpc32xx_nand_ecc_correct(काष्ठा nand_chip *chip,
				    अचिन्हित अक्षर *buf,
				    अचिन्हित अक्षर *पढ़ो_ecc,
				    अचिन्हित अक्षर *calc_ecc)
अणु
	वापस ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
				      chip->ecc.size, false);
पूर्ण

/*
 * Read a single byte from न_अंकD device
 */
अटल uपूर्णांक8_t lpc32xx_nand_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	वापस (uपूर्णांक8_t)पढ़ोl(SLC_DATA(host->io_base));
पूर्ण

/*
 * Simple device पढ़ो without ECC
 */
अटल व्योम lpc32xx_nand_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Direct device पढ़ो with no ECC */
	जबतक (len-- > 0)
		*buf++ = (uपूर्णांक8_t)पढ़ोl(SLC_DATA(host->io_base));
पूर्ण

/*
 * Simple device ग_लिखो without ECC
 */
अटल व्योम lpc32xx_nand_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				   पूर्णांक len)
अणु
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);

	/* Direct device ग_लिखो with no ECC */
	जबतक (len-- > 0)
		ग_लिखोl((uपूर्णांक32_t)*buf++, SLC_DATA(host->io_base));
पूर्ण

/*
 * Read the OOB data from the device without ECC using FIFO method
 */
अटल पूर्णांक lpc32xx_nand_पढ़ो_oob_syndrome(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस nand_पढ़ो_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
पूर्ण

/*
 * Write the OOB data to the device without ECC using FIFO method
 */
अटल पूर्णांक lpc32xx_nand_ग_लिखो_oob_syndrome(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस nand_prog_page_op(chip, page, mtd->ग_लिखोsize, chip->oob_poi,
				 mtd->oobsize);
पूर्ण

/*
 * Fills in the ECC fields in the OOB buffer with the hardware generated ECC
 */
अटल व्योम lpc32xx_slc_ecc_copy(uपूर्णांक8_t *spare, स्थिर uपूर्णांक32_t *ecc, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (count * 3); i += 3) अणु
		uपूर्णांक32_t ce = ecc[i / 3];
		ce = ~(ce << 2) & 0xFFFFFF;
		spare[i + 2] = (uपूर्णांक8_t)(ce & 0xFF);
		ce >>= 8;
		spare[i + 1] = (uपूर्णांक8_t)(ce & 0xFF);
		ce >>= 8;
		spare[i] = (uपूर्णांक8_t)(ce & 0xFF);
	पूर्ण
पूर्ण

अटल व्योम lpc32xx_dma_complete_func(व्योम *completion)
अणु
	complete(completion);
पूर्ण

अटल पूर्णांक lpc32xx_xmit_dma(काष्ठा mtd_info *mtd, dma_addr_t dma,
			    व्योम *mem, पूर्णांक len, क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	पूर्णांक res;

	host->dma_slave_config.direction = dir;
	host->dma_slave_config.src_addr = dma;
	host->dma_slave_config.dst_addr = dma;
	host->dma_slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->dma_slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->dma_slave_config.src_maxburst = 4;
	host->dma_slave_config.dst_maxburst = 4;
	/* DMA controller करोes flow control: */
	host->dma_slave_config.device_fc = false;
	अगर (dmaengine_slave_config(host->dma_chan, &host->dma_slave_config)) अणु
		dev_err(mtd->dev.parent, "Failed to setup DMA slave\n");
		वापस -ENXIO;
	पूर्ण

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

	init_completion(&host->comp);
	desc->callback = lpc32xx_dma_complete_func;
	desc->callback_param = &host->comp;

	dmaengine_submit(desc);
	dma_async_issue_pending(host->dma_chan);

	रुको_क्रम_completion_समयout(&host->comp, msecs_to_jअगरfies(1000));

	dma_unmap_sg(host->dma_chan->device->dev, &host->sgl, 1,
		     DMA_BIसूचीECTIONAL);

	वापस 0;
out1:
	dma_unmap_sg(host->dma_chan->device->dev, &host->sgl, 1,
		     DMA_BIसूचीECTIONAL);
	वापस -ENXIO;
पूर्ण

/*
 * DMA पढ़ो/ग_लिखो transfers with ECC support
 */
अटल पूर्णांक lpc32xx_xfer(काष्ठा mtd_info *mtd, uपूर्णांक8_t *buf, पूर्णांक eccsubpages,
			पूर्णांक पढ़ो)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	पूर्णांक i, status = 0;
	अचिन्हित दीर्घ समयout;
	पूर्णांक res;
	क्रमागत dma_transfer_direction dir =
		पढ़ो ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;
	uपूर्णांक8_t *dma_buf;
	bool dma_mapped;

	अगर ((व्योम *)buf <= high_memory) अणु
		dma_buf = buf;
		dma_mapped = true;
	पूर्ण अन्यथा अणु
		dma_buf = host->data_buf;
		dma_mapped = false;
		अगर (!पढ़ो)
			स_नकल(host->data_buf, buf, mtd->ग_लिखोsize);
	पूर्ण

	अगर (पढ़ो) अणु
		ग_लिखोl(पढ़ोl(SLC_CFG(host->io_base)) |
		       SLCCFG_DMA_सूची | SLCCFG_ECC_EN | SLCCFG_DMA_ECC |
		       SLCCFG_DMA_BURST, SLC_CFG(host->io_base));
	पूर्ण अन्यथा अणु
		ग_लिखोl((पढ़ोl(SLC_CFG(host->io_base)) |
			SLCCFG_ECC_EN | SLCCFG_DMA_ECC | SLCCFG_DMA_BURST) &
		       ~SLCCFG_DMA_सूची,
			SLC_CFG(host->io_base));
	पूर्ण

	/* Clear initial ECC */
	ग_लिखोl(SLCCTRL_ECC_CLEAR, SLC_CTRL(host->io_base));

	/* Transfer size is data area only */
	ग_लिखोl(mtd->ग_लिखोsize, SLC_TC(host->io_base));

	/* Start transfer in the न_अंकD controller */
	ग_लिखोl(पढ़ोl(SLC_CTRL(host->io_base)) | SLCCTRL_DMA_START,
	       SLC_CTRL(host->io_base));

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		/* Data */
		res = lpc32xx_xmit_dma(mtd, SLC_DMA_DATA(host->io_base_dma),
				       dma_buf + i * chip->ecc.size,
				       mtd->ग_लिखोsize / chip->ecc.steps, dir);
		अगर (res)
			वापस res;

		/* Always _पढ़ो_ ECC */
		अगर (i == chip->ecc.steps - 1)
			अवरोध;
		अगर (!पढ़ो) /* ECC availability delayed on ग_लिखो */
			udelay(10);
		res = lpc32xx_xmit_dma(mtd, SLC_ECC(host->io_base_dma),
				       &host->ecc_buf[i], 4, DMA_DEV_TO_MEM);
		अगर (res)
			वापस res;
	पूर्ण

	/*
	 * According to NXP, the DMA can be finished here, but the न_अंकD
	 * controller may still have buffered data. After porting to using the
	 * dmaengine DMA driver (amba-pl080), the condition (DMA_FIFO empty)
	 * appears to be always true, according to tests. Keeping the check क्रम
	 * safety reasons क्रम now.
	 */
	अगर (पढ़ोl(SLC_STAT(host->io_base)) & SLCSTAT_DMA_FIFO) अणु
		dev_warn(mtd->dev.parent, "FIFO not empty!\n");
		समयout = jअगरfies + msecs_to_jअगरfies(LPC32XX_DMA_TIMEOUT);
		जबतक ((पढ़ोl(SLC_STAT(host->io_base)) & SLCSTAT_DMA_FIFO) &&
		       समय_beक्रमe(jअगरfies, समयout))
			cpu_relax();
		अगर (!समय_beक्रमe(jअगरfies, समयout)) अणु
			dev_err(mtd->dev.parent, "FIFO held data too long\n");
			status = -EIO;
		पूर्ण
	पूर्ण

	/* Read last calculated ECC value */
	अगर (!पढ़ो)
		udelay(10);
	host->ecc_buf[chip->ecc.steps - 1] =
		पढ़ोl(SLC_ECC(host->io_base));

	/* Flush DMA */
	dmaengine_terminate_all(host->dma_chan);

	अगर (पढ़ोl(SLC_STAT(host->io_base)) & SLCSTAT_DMA_FIFO ||
	    पढ़ोl(SLC_TC(host->io_base))) अणु
		/* Something is left in the FIFO, something is wrong */
		dev_err(mtd->dev.parent, "DMA FIFO failure\n");
		status = -EIO;
	पूर्ण

	/* Stop DMA & HW ECC */
	ग_लिखोl(पढ़ोl(SLC_CTRL(host->io_base)) & ~SLCCTRL_DMA_START,
	       SLC_CTRL(host->io_base));
	ग_लिखोl(पढ़ोl(SLC_CFG(host->io_base)) &
	       ~(SLCCFG_DMA_सूची | SLCCFG_ECC_EN | SLCCFG_DMA_ECC |
		 SLCCFG_DMA_BURST), SLC_CFG(host->io_base));

	अगर (!dma_mapped && पढ़ो)
		स_नकल(buf, host->data_buf, mtd->ग_लिखोsize);

	वापस status;
पूर्ण

/*
 * Read the data and OOB data from the device, use ECC correction with the
 * data, disable ECC क्रम the OOB data
 */
अटल पूर्णांक lpc32xx_nand_पढ़ो_page_syndrome(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
					   पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	काष्ठा mtd_oob_region oobregion = अणु पूर्ण;
	पूर्णांक stat, i, status, error;
	uपूर्णांक8_t *oobecc, पंचांगpecc[LPC32XX_ECC_SAVE_SIZE];

	/* Issue पढ़ो command */
	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	/* Read data and oob, calculate ECC */
	status = lpc32xx_xfer(mtd, buf, chip->ecc.steps, 1);

	/* Get OOB data */
	chip->legacy.पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);

	/* Convert to stored ECC क्रमmat */
	lpc32xx_slc_ecc_copy(पंचांगpecc, (uपूर्णांक32_t *) host->ecc_buf, chip->ecc.steps);

	/* Poपूर्णांकer to ECC data retrieved from न_अंकD spare area */
	error = mtd_ooblayout_ecc(mtd, 0, &oobregion);
	अगर (error)
		वापस error;

	oobecc = chip->oob_poi + oobregion.offset;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		stat = chip->ecc.correct(chip, buf, oobecc,
					 &पंचांगpecc[i * chip->ecc.bytes]);
		अगर (stat < 0)
			mtd->ecc_stats.failed++;
		अन्यथा
			mtd->ecc_stats.corrected += stat;

		buf += chip->ecc.size;
		oobecc += chip->ecc.bytes;
	पूर्ण

	वापस status;
पूर्ण

/*
 * Read the data and OOB data from the device, no ECC correction with the
 * data or OOB data
 */
अटल पूर्णांक lpc32xx_nand_पढ़ो_page_raw_syndrome(काष्ठा nand_chip *chip,
					       uपूर्णांक8_t *buf, पूर्णांक oob_required,
					       पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Issue पढ़ो command */
	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	/* Raw पढ़ोs can just use the FIFO पूर्णांकerface */
	chip->legacy.पढ़ो_buf(chip, buf, chip->ecc.size * chip->ecc.steps);
	chip->legacy.पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस 0;
पूर्ण

/*
 * Write the data and OOB data to the device, use ECC with the data,
 * disable ECC क्रम the OOB data
 */
अटल पूर्णांक lpc32xx_nand_ग_लिखो_page_syndrome(काष्ठा nand_chip *chip,
					    स्थिर uपूर्णांक8_t *buf,
					    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा lpc32xx_nand_host *host = nand_get_controller_data(chip);
	काष्ठा mtd_oob_region oobregion = अणु पूर्ण;
	uपूर्णांक8_t *pb;
	पूर्णांक error;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	/* Write data, calculate ECC on outbound data */
	error = lpc32xx_xfer(mtd, (uपूर्णांक8_t *)buf, chip->ecc.steps, 0);
	अगर (error)
		वापस error;

	/*
	 * The calculated ECC needs some manual work करोne to it beक्रमe
	 * committing it to न_अंकD. Process the calculated ECC and place
	 * the resultant values directly पूर्णांकo the OOB buffer. */
	error = mtd_ooblayout_ecc(mtd, 0, &oobregion);
	अगर (error)
		वापस error;

	pb = chip->oob_poi + oobregion.offset;
	lpc32xx_slc_ecc_copy(pb, (uपूर्णांक32_t *)host->ecc_buf, chip->ecc.steps);

	/* Write ECC data to device */
	chip->legacy.ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

/*
 * Write the data and OOB data to the device, no ECC correction with the
 * data or OOB data
 */
अटल पूर्णांक lpc32xx_nand_ग_लिखो_page_raw_syndrome(काष्ठा nand_chip *chip,
						स्थिर uपूर्णांक8_t *buf,
						पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Raw ग_लिखोs can just use the FIFO पूर्णांकerface */
	nand_prog_page_begin_op(chip, page, 0, buf,
				chip->ecc.size * chip->ecc.steps);
	chip->legacy.ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक lpc32xx_nand_dma_setup(काष्ठा lpc32xx_nand_host *host)
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
					     "nand-slc");
	अगर (!host->dma_chan) अणु
		dev_err(mtd->dev.parent, "Failed to request DMA channel\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lpc32xx_nand_cfg_slc *lpc32xx_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_nand_cfg_slc *ncfg;
	काष्ठा device_node *np = dev->of_node;

	ncfg = devm_kzalloc(dev, माप(*ncfg), GFP_KERNEL);
	अगर (!ncfg)
		वापस शून्य;

	of_property_पढ़ो_u32(np, "nxp,wdr-clks", &ncfg->wdr_clks);
	of_property_पढ़ो_u32(np, "nxp,wwidth", &ncfg->wwidth);
	of_property_पढ़ो_u32(np, "nxp,whold", &ncfg->whold);
	of_property_पढ़ो_u32(np, "nxp,wsetup", &ncfg->wsetup);
	of_property_पढ़ो_u32(np, "nxp,rdr-clks", &ncfg->rdr_clks);
	of_property_पढ़ो_u32(np, "nxp,rwidth", &ncfg->rwidth);
	of_property_पढ़ो_u32(np, "nxp,rhold", &ncfg->rhold);
	of_property_पढ़ो_u32(np, "nxp,rsetup", &ncfg->rsetup);

	अगर (!ncfg->wdr_clks || !ncfg->wwidth || !ncfg->whold ||
	    !ncfg->wsetup || !ncfg->rdr_clks || !ncfg->rwidth ||
	    !ncfg->rhold || !ncfg->rsetup) अणु
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

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	/* OOB and ECC CPU and DMA work areas */
	host->ecc_buf = (uपूर्णांक32_t *)(host->data_buf + LPC32XX_DMA_DATA_SIZE);

	/*
	 * Small page FLASH has a unique OOB layout, but large and huge
	 * page FLASH use the standard layout. Small page FLASH uses a
	 * custom BBT marker layout.
	 */
	अगर (mtd->ग_लिखोsize <= 512)
		mtd_set_ooblayout(mtd, &lpc32xx_ooblayout_ops);

	chip->ecc.placement = न_अंकD_ECC_PLACEMENT_INTERLEAVED;
	/* These sizes reमुख्य the same regardless of page size */
	chip->ecc.size = 256;
	chip->ecc.strength = 1;
	chip->ecc.bytes = LPC32XX_SLC_DEV_ECC_BYTES;
	chip->ecc.prepad = 0;
	chip->ecc.postpad = 0;
	chip->ecc.पढ़ो_page_raw = lpc32xx_nand_पढ़ो_page_raw_syndrome;
	chip->ecc.पढ़ो_page = lpc32xx_nand_पढ़ो_page_syndrome;
	chip->ecc.ग_लिखो_page_raw = lpc32xx_nand_ग_लिखो_page_raw_syndrome;
	chip->ecc.ग_लिखो_page = lpc32xx_nand_ग_लिखो_page_syndrome;
	chip->ecc.ग_लिखो_oob = lpc32xx_nand_ग_लिखो_oob_syndrome;
	chip->ecc.पढ़ो_oob = lpc32xx_nand_पढ़ो_oob_syndrome;
	chip->ecc.calculate = lpc32xx_nand_ecc_calculate;
	chip->ecc.correct = lpc32xx_nand_ecc_correct;
	chip->ecc.hwctl = lpc32xx_nand_ecc_enable;

	/*
	 * Use a custom BBT marker setup क्रम small page FLASH that
	 * won't पूर्णांकerfere with the ECC layout. Large and huge page
	 * FLASH use the standard layout.
	 */
	अगर ((chip->bbt_options & न_अंकD_BBT_USE_FLASH) &&
	    mtd->ग_लिखोsize <= 512) अणु
		chip->bbt_td = &bbt_smallpage_मुख्य_descr;
		chip->bbt_md = &bbt_smallpage_mirror_descr;
	पूर्ण

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
	काष्ठा nand_chip *chip;
	काष्ठा resource *rc;
	पूर्णांक res;

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	rc = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->io_base = devm_ioremap_resource(&pdev->dev, rc);
	अगर (IS_ERR(host->io_base))
		वापस PTR_ERR(host->io_base);

	host->io_base_dma = rc->start;
	अगर (pdev->dev.of_node)
		host->ncfg = lpc32xx_parse_dt(&pdev->dev);
	अगर (!host->ncfg) अणु
		dev_err(&pdev->dev,
			"Missing or bad NAND config from device tree\n");
		वापस -ENOENT;
	पूर्ण
	अगर (host->ncfg->wp_gpio == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(host->ncfg->wp_gpio) && devm_gpio_request(&pdev->dev,
			host->ncfg->wp_gpio, "NAND WP")) अणु
		dev_err(&pdev->dev, "GPIO not available\n");
		वापस -EBUSY;
	पूर्ण
	lpc32xx_wp_disable(host);

	host->pdata = dev_get_platdata(&pdev->dev);

	chip = &host->nand_chip;
	mtd = nand_to_mtd(chip);
	nand_set_controller_data(chip, host);
	nand_set_flash_node(chip, pdev->dev.of_node);
	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &pdev->dev;

	/* Get न_अंकD घड़ी */
	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		dev_err(&pdev->dev, "Clock failure\n");
		res = -ENOENT;
		जाओ enable_wp;
	पूर्ण
	res = clk_prepare_enable(host->clk);
	अगर (res)
		जाओ enable_wp;

	/* Set न_अंकD IO addresses and command/पढ़ोy functions */
	chip->legacy.IO_ADDR_R = SLC_DATA(host->io_base);
	chip->legacy.IO_ADDR_W = SLC_DATA(host->io_base);
	chip->legacy.cmd_ctrl = lpc32xx_nand_cmd_ctrl;
	chip->legacy.dev_पढ़ोy = lpc32xx_nand_device_पढ़ोy;
	chip->legacy.chip_delay = 20; /* 20us command delay समय */

	/* Init न_अंकD controller */
	lpc32xx_nand_setup(host);

	platक्रमm_set_drvdata(pdev, host);

	/* न_अंकD callbacks क्रम LPC32xx SLC hardware */
	chip->legacy.पढ़ो_byte = lpc32xx_nand_पढ़ो_byte;
	chip->legacy.पढ़ो_buf = lpc32xx_nand_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf = lpc32xx_nand_ग_लिखो_buf;

	/*
	 * Allocate a large enough buffer क्रम a single huge page plus
	 * extra space क्रम the spare area and ECC storage area
	 */
	host->dma_buf_len = LPC32XX_DMA_DATA_SIZE + LPC32XX_ECC_SAVE_SIZE;
	host->data_buf = devm_kzalloc(&pdev->dev, host->dma_buf_len,
				      GFP_KERNEL);
	अगर (host->data_buf == शून्य) अणु
		res = -ENOMEM;
		जाओ unprepare_clk;
	पूर्ण

	res = lpc32xx_nand_dma_setup(host);
	अगर (res) अणु
		res = -EIO;
		जाओ unprepare_clk;
	पूर्ण

	/* Find न_अंकD device */
	chip->legacy.dummy_controller.ops = &lpc32xx_nand_controller_ops;
	res = nand_scan(chip, 1);
	अगर (res)
		जाओ release_dma;

	mtd->name = "nxp_lpc3220_slc";
	res = mtd_device_रेजिस्टर(mtd, host->ncfg->parts,
				  host->ncfg->num_parts);
	अगर (res)
		जाओ cleanup_nand;

	वापस 0;

cleanup_nand:
	nand_cleanup(chip);
release_dma:
	dma_release_channel(host->dma_chan);
unprepare_clk:
	clk_disable_unprepare(host->clk);
enable_wp:
	lpc32xx_wp_enable(host);

	वापस res;
पूर्ण

/*
 * Remove न_अंकD device.
 */
अटल पूर्णांक lpc32xx_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	uपूर्णांक32_t पंचांगp;
	काष्ठा lpc32xx_nand_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &host->nand_chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	dma_release_channel(host->dma_chan);

	/* Force CE high */
	पंचांगp = पढ़ोl(SLC_CTRL(host->io_base));
	पंचांगp &= ~SLCCFG_CE_LOW;
	ग_लिखोl(पंचांगp, SLC_CTRL(host->io_base));

	clk_disable_unprepare(host->clk);
	lpc32xx_wp_enable(host);

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
	uपूर्णांक32_t पंचांगp;
	काष्ठा lpc32xx_nand_host *host = platक्रमm_get_drvdata(pdev);

	/* Force CE high */
	पंचांगp = पढ़ोl(SLC_CTRL(host->io_base));
	पंचांगp &= ~SLCCFG_CE_LOW;
	ग_लिखोl(पंचांगp, SLC_CTRL(host->io_base));

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
	अणु .compatible = "nxp,lpc3220-slc" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_nand_match);

अटल काष्ठा platक्रमm_driver lpc32xx_nand_driver = अणु
	.probe		= lpc32xx_nand_probe,
	.हटाओ		= lpc32xx_nand_हटाओ,
	.resume		= lpc32xx_nand_resume,
	.suspend	= lpc32xx_nand_suspend,
	.driver		= अणु
		.name	= LPC32XX_MODNAME,
		.of_match_table = lpc32xx_nand_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpc32xx_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("NAND driver for the NXP LPC32XX SLC controller");
