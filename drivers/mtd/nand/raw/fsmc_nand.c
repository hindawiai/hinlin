<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ST Microelectronics
 * Flexible Static Memory Controller (FSMC)
 * Driver क्रम न_अंकD portions
 *
 * Copyright तऊ 2010 ST Microelectronics
 * Vipin Kumar <vipin.kumar@st.com>
 * Ashish Priyadarshi
 *
 * Based on drivers/mtd/nand/nomadik_nand.c (हटाओd in v3.8)
 *  Copyright तऊ 2007 STMicroelectronics Pvt. Ltd.
 *  Copyright तऊ 2009 Alessandro Rubini
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/resource.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/amba/bus.h>
#समावेश <mtd/mtd-abi.h>

/* fsmc controller रेजिस्टरs क्रम NOR flash */
#घोषणा CTRL			0x0
	/* ctrl रेजिस्टर definitions */
	#घोषणा BANK_ENABLE		BIT(0)
	#घोषणा MUXED			BIT(1)
	#घोषणा NOR_DEV			(2 << 2)
	#घोषणा WIDTH_16		BIT(4)
	#घोषणा RSTPWRDWN		BIT(6)
	#घोषणा WPROT			BIT(7)
	#घोषणा WRT_ENABLE		BIT(12)
	#घोषणा WAIT_ENB		BIT(13)

#घोषणा CTRL_TIM		0x4
	/* ctrl_tim रेजिस्टर definitions */

#घोषणा FSMC_NOR_BANK_SZ	0x8
#घोषणा FSMC_NOR_REG_SIZE	0x40

#घोषणा FSMC_NOR_REG(base, bank, reg)	((base) +			\
					 (FSMC_NOR_BANK_SZ * (bank)) +	\
					 (reg))

/* fsmc controller रेजिस्टरs क्रम न_अंकD flash */
#घोषणा FSMC_PC			0x00
	/* pc रेजिस्टर definitions */
	#घोषणा FSMC_RESET		BIT(0)
	#घोषणा FSMC_WAITON		BIT(1)
	#घोषणा FSMC_ENABLE		BIT(2)
	#घोषणा FSMC_DEVTYPE_न_अंकD	BIT(3)
	#घोषणा FSMC_DEVWID_16		BIT(4)
	#घोषणा FSMC_ECCEN		BIT(6)
	#घोषणा FSMC_ECCPLEN_256	BIT(7)
	#घोषणा FSMC_TCLR_SHIFT		(9)
	#घोषणा FSMC_TCLR_MASK		(0xF)
	#घोषणा FSMC_TAR_SHIFT		(13)
	#घोषणा FSMC_TAR_MASK		(0xF)
#घोषणा STS			0x04
	/* sts रेजिस्टर definitions */
	#घोषणा FSMC_CODE_RDY		BIT(15)
#घोषणा COMM			0x08
	/* comm रेजिस्टर definitions */
	#घोषणा FSMC_TSET_SHIFT		0
	#घोषणा FSMC_TSET_MASK		0xFF
	#घोषणा FSMC_TWAIT_SHIFT	8
	#घोषणा FSMC_TWAIT_MASK		0xFF
	#घोषणा FSMC_THOLD_SHIFT	16
	#घोषणा FSMC_THOLD_MASK		0xFF
	#घोषणा FSMC_THIZ_SHIFT		24
	#घोषणा FSMC_THIZ_MASK		0xFF
#घोषणा ATTRIB			0x0C
#घोषणा IOATA			0x10
#घोषणा ECC1			0x14
#घोषणा ECC2			0x18
#घोषणा ECC3			0x1C
#घोषणा FSMC_न_अंकD_BANK_SZ	0x20

#घोषणा FSMC_BUSY_WAIT_TIMEOUT	(1 * HZ)

काष्ठा fsmc_nand_timings अणु
	u8 tclr;
	u8 tar;
	u8 thiz;
	u8 thold;
	u8 tरुको;
	u8 tset;
पूर्ण;

क्रमागत access_mode अणु
	USE_DMA_ACCESS = 1,
	USE_WORD_ACCESS,
पूर्ण;

/**
 * काष्ठा fsmc_nand_data - काष्ठाure क्रम FSMC न_अंकD device state
 *
 * @base:		Inherit from the nand_controller काष्ठा
 * @pid:		Part ID on the AMBA PrimeCell क्रमmat
 * @nand:		Chip related info क्रम a न_अंकD flash.
 *
 * @bank:		Bank number क्रम probed device.
 * @dev:		Parent device
 * @mode:		Access mode
 * @clk:		Clock काष्ठाure क्रम FSMC.
 *
 * @पढ़ो_dma_chan:	DMA channel क्रम पढ़ो access
 * @ग_लिखो_dma_chan:	DMA channel क्रम ग_लिखो access to न_अंकD
 * @dma_access_complete: Completion काष्ठाure
 *
 * @dev_timings:	न_अंकD timings
 *
 * @data_pa:		न_अंकD Physical port क्रम Data.
 * @data_va:		न_अंकD port क्रम Data.
 * @cmd_va:		न_अंकD port क्रम Command.
 * @addr_va:		न_अंकD port क्रम Address.
 * @regs_va:		Registers base address क्रम a given bank.
 */
काष्ठा fsmc_nand_data अणु
	काष्ठा nand_controller	base;
	u32			pid;
	काष्ठा nand_chip	nand;

	अचिन्हित पूर्णांक		bank;
	काष्ठा device		*dev;
	क्रमागत access_mode	mode;
	काष्ठा clk		*clk;

	/* DMA related objects */
	काष्ठा dma_chan		*पढ़ो_dma_chan;
	काष्ठा dma_chan		*ग_लिखो_dma_chan;
	काष्ठा completion	dma_access_complete;

	काष्ठा fsmc_nand_timings *dev_timings;

	dma_addr_t		data_pa;
	व्योम __iomem		*data_va;
	व्योम __iomem		*cmd_va;
	व्योम __iomem		*addr_va;
	व्योम __iomem		*regs_va;
पूर्ण;

अटल पूर्णांक fsmc_ecc1_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 2;
	oobregion->length = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक fsmc_ecc1_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				    काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 8;

	अगर (section < chip->ecc.steps - 1)
		oobregion->length = 8;
	अन्यथा
		oobregion->length = mtd->oobsize - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops fsmc_ecc1_ooblayout_ops = अणु
	.ecc = fsmc_ecc1_ooblayout_ecc,
	.मुक्त = fsmc_ecc1_ooblayout_मुक्त,
पूर्ण;

/*
 * ECC placement definitions in oobमुक्त type क्रमmat.
 * There are 13 bytes of ecc क्रम every 512 byte block and it has to be पढ़ो
 * consecutively and immediately after the 512 byte data block क्रम hardware to
 * generate the error bit offsets in 512 byte data.
 */
अटल पूर्णांक fsmc_ecc4_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->length = chip->ecc.bytes;

	अगर (!section && mtd->ग_लिखोsize <= 512)
		oobregion->offset = 0;
	अन्यथा
		oobregion->offset = (section * 16) + 2;

	वापस 0;
पूर्ण

अटल पूर्णांक fsmc_ecc4_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				    काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 15;

	अगर (section < chip->ecc.steps - 1)
		oobregion->length = 3;
	अन्यथा
		oobregion->length = mtd->oobsize - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops fsmc_ecc4_ooblayout_ops = अणु
	.ecc = fsmc_ecc4_ooblayout_ecc,
	.मुक्त = fsmc_ecc4_ooblayout_मुक्त,
पूर्ण;

अटल अंतरभूत काष्ठा fsmc_nand_data *nand_to_fsmc(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा fsmc_nand_data, nand);
पूर्ण

/*
 * fsmc_nand_setup - FSMC (Flexible Static Memory Controller) init routine
 *
 * This routine initializes timing parameters related to न_अंकD memory access in
 * FSMC रेजिस्टरs
 */
अटल व्योम fsmc_nand_setup(काष्ठा fsmc_nand_data *host,
			    काष्ठा fsmc_nand_timings *tims)
अणु
	u32 value = FSMC_DEVTYPE_न_अंकD | FSMC_ENABLE | FSMC_WAITON;
	u32 tclr, tar, thiz, thold, tरुको, tset;

	tclr = (tims->tclr & FSMC_TCLR_MASK) << FSMC_TCLR_SHIFT;
	tar = (tims->tar & FSMC_TAR_MASK) << FSMC_TAR_SHIFT;
	thiz = (tims->thiz & FSMC_THIZ_MASK) << FSMC_THIZ_SHIFT;
	thold = (tims->thold & FSMC_THOLD_MASK) << FSMC_THOLD_SHIFT;
	tरुको = (tims->tरुको & FSMC_TWAIT_MASK) << FSMC_TWAIT_SHIFT;
	tset = (tims->tset & FSMC_TSET_MASK) << FSMC_TSET_SHIFT;

	अगर (host->nand.options & न_अंकD_BUSWIDTH_16)
		value |= FSMC_DEVWID_16;

	ग_लिखोl_relaxed(value | tclr | tar, host->regs_va + FSMC_PC);
	ग_लिखोl_relaxed(thiz | thold | tरुको | tset, host->regs_va + COMM);
	ग_लिखोl_relaxed(thiz | thold | tरुको | tset, host->regs_va + ATTRIB);
पूर्ण

अटल पूर्णांक fsmc_calc_timings(काष्ठा fsmc_nand_data *host,
			     स्थिर काष्ठा nand_sdr_timings *sdrt,
			     काष्ठा fsmc_nand_timings *tims)
अणु
	अचिन्हित दीर्घ hclk = clk_get_rate(host->clk);
	अचिन्हित दीर्घ hclkn = NSEC_PER_SEC / hclk;
	u32 thiz, thold, tरुको, tset;

	अगर (sdrt->tRC_min < 30000)
		वापस -EOPNOTSUPP;

	tims->tar = DIV_ROUND_UP(sdrt->tAR_min / 1000, hclkn) - 1;
	अगर (tims->tar > FSMC_TAR_MASK)
		tims->tar = FSMC_TAR_MASK;
	tims->tclr = DIV_ROUND_UP(sdrt->tCLR_min / 1000, hclkn) - 1;
	अगर (tims->tclr > FSMC_TCLR_MASK)
		tims->tclr = FSMC_TCLR_MASK;

	thiz = sdrt->tCS_min - sdrt->tWP_min;
	tims->thiz = DIV_ROUND_UP(thiz / 1000, hclkn);

	thold = sdrt->tDH_min;
	अगर (thold < sdrt->tCH_min)
		thold = sdrt->tCH_min;
	अगर (thold < sdrt->tCLH_min)
		thold = sdrt->tCLH_min;
	अगर (thold < sdrt->tWH_min)
		thold = sdrt->tWH_min;
	अगर (thold < sdrt->tALH_min)
		thold = sdrt->tALH_min;
	अगर (thold < sdrt->tREH_min)
		thold = sdrt->tREH_min;
	tims->thold = DIV_ROUND_UP(thold / 1000, hclkn);
	अगर (tims->thold == 0)
		tims->thold = 1;
	अन्यथा अगर (tims->thold > FSMC_THOLD_MASK)
		tims->thold = FSMC_THOLD_MASK;

	tरुको = max(sdrt->tRP_min, sdrt->tWP_min);
	tims->tरुको = DIV_ROUND_UP(tरुको / 1000, hclkn) - 1;
	अगर (tims->tरुको == 0)
		tims->tरुको = 1;
	अन्यथा अगर (tims->tरुको > FSMC_TWAIT_MASK)
		tims->tरुको = FSMC_TWAIT_MASK;

	tset = max(sdrt->tCS_min - sdrt->tWP_min,
		   sdrt->tCEA_max - sdrt->tREA_max);
	tims->tset = DIV_ROUND_UP(tset / 1000, hclkn) - 1;
	अगर (tims->tset == 0)
		tims->tset = 1;
	अन्यथा अगर (tims->tset > FSMC_TSET_MASK)
		tims->tset = FSMC_TSET_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक fsmc_setup_पूर्णांकerface(काष्ठा nand_chip *nand, पूर्णांक csline,
				स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(nand);
	काष्ठा fsmc_nand_timings tims;
	स्थिर काष्ठा nand_sdr_timings *sdrt;
	पूर्णांक ret;

	sdrt = nand_get_sdr_timings(conf);
	अगर (IS_ERR(sdrt))
		वापस PTR_ERR(sdrt);

	ret = fsmc_calc_timings(host, sdrt, &tims);
	अगर (ret)
		वापस ret;

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	fsmc_nand_setup(host, &tims);

	वापस 0;
पूर्ण

/*
 * fsmc_enable_hwecc - Enables Hardware ECC through FSMC रेजिस्टरs
 */
अटल व्योम fsmc_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(chip);

	ग_लिखोl_relaxed(पढ़ोl(host->regs_va + FSMC_PC) & ~FSMC_ECCPLEN_256,
		       host->regs_va + FSMC_PC);
	ग_लिखोl_relaxed(पढ़ोl(host->regs_va + FSMC_PC) & ~FSMC_ECCEN,
		       host->regs_va + FSMC_PC);
	ग_लिखोl_relaxed(पढ़ोl(host->regs_va + FSMC_PC) | FSMC_ECCEN,
		       host->regs_va + FSMC_PC);
पूर्ण

/*
 * fsmc_पढ़ो_hwecc_ecc4 - Hardware ECC calculator क्रम ecc4 option supported by
 * FSMC. ECC is 13 bytes क्रम 512 bytes of data (supports error correction up to
 * max of 8-bits)
 */
अटल पूर्णांक fsmc_पढ़ो_hwecc_ecc4(काष्ठा nand_chip *chip, स्थिर u8 *data,
				u8 *ecc)
अणु
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 ecc_पंचांगp;
	अचिन्हित दीर्घ deadline = jअगरfies + FSMC_BUSY_WAIT_TIMEOUT;

	करो अणु
		अगर (पढ़ोl_relaxed(host->regs_va + STS) & FSMC_CODE_RDY)
			अवरोध;

		cond_resched();
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	अगर (समय_after_eq(jअगरfies, deadline)) अणु
		dev_err(host->dev, "calculate ecc timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ecc_पंचांगp = पढ़ोl_relaxed(host->regs_va + ECC1);
	ecc[0] = ecc_पंचांगp;
	ecc[1] = ecc_पंचांगp >> 8;
	ecc[2] = ecc_पंचांगp >> 16;
	ecc[3] = ecc_पंचांगp >> 24;

	ecc_पंचांगp = पढ़ोl_relaxed(host->regs_va + ECC2);
	ecc[4] = ecc_पंचांगp;
	ecc[5] = ecc_पंचांगp >> 8;
	ecc[6] = ecc_पंचांगp >> 16;
	ecc[7] = ecc_पंचांगp >> 24;

	ecc_पंचांगp = पढ़ोl_relaxed(host->regs_va + ECC3);
	ecc[8] = ecc_पंचांगp;
	ecc[9] = ecc_पंचांगp >> 8;
	ecc[10] = ecc_पंचांगp >> 16;
	ecc[11] = ecc_पंचांगp >> 24;

	ecc_पंचांगp = पढ़ोl_relaxed(host->regs_va + STS);
	ecc[12] = ecc_पंचांगp >> 16;

	वापस 0;
पूर्ण

/*
 * fsmc_पढ़ो_hwecc_ecc1 - Hardware ECC calculator क्रम ecc1 option supported by
 * FSMC. ECC is 3 bytes क्रम 512 bytes of data (supports error correction up to
 * max of 1-bit)
 */
अटल पूर्णांक fsmc_पढ़ो_hwecc_ecc1(काष्ठा nand_chip *chip, स्थिर u8 *data,
				u8 *ecc)
अणु
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 ecc_पंचांगp;

	ecc_पंचांगp = पढ़ोl_relaxed(host->regs_va + ECC1);
	ecc[0] = ecc_पंचांगp;
	ecc[1] = ecc_पंचांगp >> 8;
	ecc[2] = ecc_पंचांगp >> 16;

	वापस 0;
पूर्ण

अटल पूर्णांक fsmc_correct_ecc1(काष्ठा nand_chip *chip,
			     अचिन्हित अक्षर *buf,
			     अचिन्हित अक्षर *पढ़ो_ecc,
			     अचिन्हित अक्षर *calc_ecc)
अणु
	वापस ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
				      chip->ecc.size, false);
पूर्ण

/* Count the number of 0's in buff upto a max of max_bits */
अटल पूर्णांक count_written_bits(u8 *buff, पूर्णांक size, पूर्णांक max_bits)
अणु
	पूर्णांक k, written_bits = 0;

	क्रम (k = 0; k < size; k++) अणु
		written_bits += hweight8(~buff[k]);
		अगर (written_bits > max_bits)
			अवरोध;
	पूर्ण

	वापस written_bits;
पूर्ण

अटल व्योम dma_complete(व्योम *param)
अणु
	काष्ठा fsmc_nand_data *host = param;

	complete(&host->dma_access_complete);
पूर्ण

अटल पूर्णांक dma_xfer(काष्ठा fsmc_nand_data *host, व्योम *buffer, पूर्णांक len,
		    क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_device *dma_dev;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_addr_t dma_dst, dma_src, dma_addr;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	अगर (direction == DMA_TO_DEVICE)
		chan = host->ग_लिखो_dma_chan;
	अन्यथा अगर (direction == DMA_FROM_DEVICE)
		chan = host->पढ़ो_dma_chan;
	अन्यथा
		वापस -EINVAL;

	dma_dev = chan->device;
	dma_addr = dma_map_single(dma_dev->dev, buffer, len, direction);

	अगर (direction == DMA_TO_DEVICE) अणु
		dma_src = dma_addr;
		dma_dst = host->data_pa;
	पूर्ण अन्यथा अणु
		dma_src = host->data_pa;
		dma_dst = dma_addr;
	पूर्ण

	tx = dma_dev->device_prep_dma_स_नकल(chan, dma_dst, dma_src,
			len, flags);
	अगर (!tx) अणु
		dev_err(host->dev, "device_prep_dma_memcpy error\n");
		ret = -EIO;
		जाओ unmap_dma;
	पूर्ण

	tx->callback = dma_complete;
	tx->callback_param = host;
	cookie = tx->tx_submit(tx);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(host->dev, "dma_submit_error %d\n", cookie);
		जाओ unmap_dma;
	पूर्ण

	dma_async_issue_pending(chan);

	समय_left =
	रुको_क्रम_completion_समयout(&host->dma_access_complete,
				    msecs_to_jअगरfies(3000));
	अगर (समय_left == 0) अणु
		dmaengine_terminate_all(chan);
		dev_err(host->dev, "wait_for_completion_timeout\n");
		ret = -ETIMEDOUT;
		जाओ unmap_dma;
	पूर्ण

	ret = 0;

unmap_dma:
	dma_unmap_single(dma_dev->dev, dma_addr, len, direction);

	वापस ret;
पूर्ण

/*
 * fsmc_ग_लिखो_buf - ग_लिखो buffer to chip
 * @host:	FSMC न_अंकD controller
 * @buf:	data buffer
 * @len:	number of bytes to ग_लिखो
 */
अटल व्योम fsmc_ग_लिखो_buf(काष्ठा fsmc_nand_data *host, स्थिर u8 *buf,
			   पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u32)) &&
	    IS_ALIGNED(len, माप(u32))) अणु
		u32 *p = (u32 *)buf;

		len = len >> 2;
		क्रम (i = 0; i < len; i++)
			ग_लिखोl_relaxed(p[i], host->data_va);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len; i++)
			ग_लिखोb_relaxed(buf[i], host->data_va);
	पूर्ण
पूर्ण

/*
 * fsmc_पढ़ो_buf - पढ़ो chip data पूर्णांकo buffer
 * @host:	FSMC न_अंकD controller
 * @buf:	buffer to store date
 * @len:	number of bytes to पढ़ो
 */
अटल व्योम fsmc_पढ़ो_buf(काष्ठा fsmc_nand_data *host, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u32)) &&
	    IS_ALIGNED(len, माप(u32))) अणु
		u32 *p = (u32 *)buf;

		len = len >> 2;
		क्रम (i = 0; i < len; i++)
			p[i] = पढ़ोl_relaxed(host->data_va);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len; i++)
			buf[i] = पढ़ोb_relaxed(host->data_va);
	पूर्ण
पूर्ण

/*
 * fsmc_पढ़ो_buf_dma - पढ़ो chip data पूर्णांकo buffer
 * @host:	FSMC न_अंकD controller
 * @buf:	buffer to store date
 * @len:	number of bytes to पढ़ो
 */
अटल व्योम fsmc_पढ़ो_buf_dma(काष्ठा fsmc_nand_data *host, u8 *buf,
			      पूर्णांक len)
अणु
	dma_xfer(host, buf, len, DMA_FROM_DEVICE);
पूर्ण

/*
 * fsmc_ग_लिखो_buf_dma - ग_लिखो buffer to chip
 * @host:	FSMC न_अंकD controller
 * @buf:	data buffer
 * @len:	number of bytes to ग_लिखो
 */
अटल व्योम fsmc_ग_लिखो_buf_dma(काष्ठा fsmc_nand_data *host, स्थिर u8 *buf,
			       पूर्णांक len)
अणु
	dma_xfer(host, (व्योम *)buf, len, DMA_TO_DEVICE);
पूर्ण

/*
 * fsmc_exec_op - hook called by the core to execute न_अंकD operations
 *
 * This controller is simple enough and thus करोes not need to use the parser
 * provided by the core, instead, handle every situation here.
 */
अटल पूर्णांक fsmc_exec_op(काष्ठा nand_chip *chip, स्थिर काष्ठा nand_operation *op,
			bool check_only)
अणु
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(chip);
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक op_id;
	पूर्णांक i;

	अगर (check_only)
		वापस 0;

	pr_debug("Executing operation [%d instructions]:\n", op->ninstrs);

	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];

		nand_op_trace("  ", instr);

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			ग_लिखोb_relaxed(instr->ctx.cmd.opcode, host->cmd_va);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
				ग_लिखोb_relaxed(instr->ctx.addr.addrs[i],
					       host->addr_va);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			अगर (host->mode == USE_DMA_ACCESS)
				fsmc_पढ़ो_buf_dma(host, instr->ctx.data.buf.in,
						  instr->ctx.data.len);
			अन्यथा
				fsmc_पढ़ो_buf(host, instr->ctx.data.buf.in,
					      instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			अगर (host->mode == USE_DMA_ACCESS)
				fsmc_ग_लिखो_buf_dma(host,
						   instr->ctx.data.buf.out,
						   instr->ctx.data.len);
			अन्यथा
				fsmc_ग_लिखो_buf(host, instr->ctx.data.buf.out,
					       instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			ret = nand_soft_रुकोrdy(chip,
						instr->ctx.रुकोrdy.समयout_ms);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * fsmc_पढ़ो_page_hwecc
 * @chip:	nand chip info काष्ठाure
 * @buf:	buffer to store पढ़ो data
 * @oob_required:	caller expects OOB data पढ़ो to chip->oob_poi
 * @page:	page number to पढ़ो
 *
 * This routine is needed क्रम fsmc version 8 as पढ़ोing from न_अंकD chip has to be
 * perक्रमmed in a strict sequence as follows:
 * data(512 byte) -> ecc(13 byte)
 * After this पढ़ो, fsmc hardware generates and reports error data bits(up to a
 * max of 8 bits)
 */
अटल पूर्णांक fsmc_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, u8 *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक i, j, s, stat, eccsize = chip->ecc.size;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	u8 *p = buf;
	u8 *ecc_calc = chip->ecc.calc_buf;
	u8 *ecc_code = chip->ecc.code_buf;
	पूर्णांक off, len, ret, group = 0;
	/*
	 * ecc_oob is पूर्णांकentionally taken as u16. In 16bit devices, we
	 * end up पढ़ोing 14 bytes (7 words) from oob. The local array is
	 * to मुख्यtain word alignment
	 */
	u16 ecc_oob[7];
	u8 *oob = (u8 *)&ecc_oob[0];
	अचिन्हित पूर्णांक max_bitflips = 0;

	क्रम (i = 0, s = 0; s < eccsteps; s++, i += eccbytes, p += eccsize) अणु
		nand_पढ़ो_page_op(chip, page, s * eccsize, शून्य, 0);
		chip->ecc.hwctl(chip, न_अंकD_ECC_READ);
		ret = nand_पढ़ो_data_op(chip, p, eccsize, false, false);
		अगर (ret)
			वापस ret;

		क्रम (j = 0; j < eccbytes;) अणु
			काष्ठा mtd_oob_region oobregion;

			ret = mtd_ooblayout_ecc(mtd, group++, &oobregion);
			अगर (ret)
				वापस ret;

			off = oobregion.offset;
			len = oobregion.length;

			/*
			 * length is पूर्णांकentionally kept a higher multiple of 2
			 * to पढ़ो at least 13 bytes even in हाल of 16 bit न_अंकD
			 * devices
			 */
			अगर (chip->options & न_अंकD_BUSWIDTH_16)
				len = roundup(len, 2);

			nand_पढ़ो_oob_op(chip, page, off, oob + j, len);
			j += len;
		पूर्ण

		स_नकल(&ecc_code[i], oob, chip->ecc.bytes);
		chip->ecc.calculate(chip, p, &ecc_calc[i]);

		stat = chip->ecc.correct(chip, p, &ecc_code[i], &ecc_calc[i]);
		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण

	वापस max_bitflips;
पूर्ण

/*
 * fsmc_bch8_correct_data
 * @mtd:	mtd info काष्ठाure
 * @dat:	buffer of पढ़ो data
 * @पढ़ो_ecc:	ecc पढ़ो from device spare area
 * @calc_ecc:	ecc calculated from पढ़ो data
 *
 * calc_ecc is a 104 bit inक्रमmation containing maximum of 8 error
 * offset inक्रमmation of 13 bits each in 512 bytes of पढ़ो data.
 */
अटल पूर्णांक fsmc_bch8_correct_data(काष्ठा nand_chip *chip, u8 *dat,
				  u8 *पढ़ो_ecc, u8 *calc_ecc)
अणु
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 err_idx[8];
	u32 num_err, i;
	u32 ecc1, ecc2, ecc3, ecc4;

	num_err = (पढ़ोl_relaxed(host->regs_va + STS) >> 10) & 0xF;

	/* no bit flipping */
	अगर (likely(num_err == 0))
		वापस 0;

	/* too many errors */
	अगर (unlikely(num_err > 8)) अणु
		/*
		 * This is a temporary erase check. A newly erased page पढ़ो
		 * would result in an ecc error because the oob data is also
		 * erased to FF and the calculated ecc क्रम an FF data is not
		 * FF..FF.
		 * This is a workaround to skip perक्रमming correction in हाल
		 * data is FF..FF
		 *
		 * Logic:
		 * For every page, each bit written as 0 is counted until these
		 * number of bits are greater than 8 (the maximum correction
		 * capability of FSMC क्रम each 512 + 13 bytes)
		 */

		पूर्णांक bits_ecc = count_written_bits(पढ़ो_ecc, chip->ecc.bytes, 8);
		पूर्णांक bits_data = count_written_bits(dat, chip->ecc.size, 8);

		अगर ((bits_ecc + bits_data) <= 8) अणु
			अगर (bits_data)
				स_रखो(dat, 0xff, chip->ecc.size);
			वापस bits_data;
		पूर्ण

		वापस -EBADMSG;
	पूर्ण

	/*
	 * ------------------- calc_ecc[] bit wise -----------|--13 bits--|
	 * |---idx[7]--|--.....-----|---idx[2]--||---idx[1]--||---idx[0]--|
	 *
	 * calc_ecc is a 104 bit inक्रमmation containing maximum of 8 error
	 * offset inक्रमmation of 13 bits each. calc_ecc is copied पूर्णांकo a
	 * u64 array and error offset indexes are populated in err_idx
	 * array
	 */
	ecc1 = पढ़ोl_relaxed(host->regs_va + ECC1);
	ecc2 = पढ़ोl_relaxed(host->regs_va + ECC2);
	ecc3 = पढ़ोl_relaxed(host->regs_va + ECC3);
	ecc4 = पढ़ोl_relaxed(host->regs_va + STS);

	err_idx[0] = (ecc1 >> 0) & 0x1FFF;
	err_idx[1] = (ecc1 >> 13) & 0x1FFF;
	err_idx[2] = (((ecc2 >> 0) & 0x7F) << 6) | ((ecc1 >> 26) & 0x3F);
	err_idx[3] = (ecc2 >> 7) & 0x1FFF;
	err_idx[4] = (((ecc3 >> 0) & 0x1) << 12) | ((ecc2 >> 20) & 0xFFF);
	err_idx[5] = (ecc3 >> 1) & 0x1FFF;
	err_idx[6] = (ecc3 >> 14) & 0x1FFF;
	err_idx[7] = (((ecc4 >> 16) & 0xFF) << 5) | ((ecc3 >> 27) & 0x1F);

	i = 0;
	जबतक (num_err--) अणु
		err_idx[i] ^= 3;

		अगर (err_idx[i] < chip->ecc.size * 8) अणु
			पूर्णांक err = err_idx[i];

			dat[err >> 3] ^= BIT(err & 7);
			i++;
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण

अटल bool filter(काष्ठा dma_chan *chan, व्योम *slave)
अणु
	chan->निजी = slave;
	वापस true;
पूर्ण

अटल पूर्णांक fsmc_nand_probe_config_dt(काष्ठा platक्रमm_device *pdev,
				     काष्ठा fsmc_nand_data *host,
				     काष्ठा nand_chip *nand)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 val;
	पूर्णांक ret;

	nand->options = 0;

	अगर (!of_property_पढ़ो_u32(np, "bank-width", &val)) अणु
		अगर (val == 2) अणु
			nand->options |= न_अंकD_BUSWIDTH_16;
		पूर्ण अन्यथा अगर (val != 1) अणु
			dev_err(&pdev->dev, "invalid bank-width %u\n", val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_get_property(np, "nand-skip-bbtscan", शून्य))
		nand->options |= न_अंकD_SKIP_BBTSCAN;

	host->dev_timings = devm_kzalloc(&pdev->dev,
					 माप(*host->dev_timings),
					 GFP_KERNEL);
	अगर (!host->dev_timings)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u8_array(np, "timings", (u8 *)host->dev_timings,
					माप(*host->dev_timings));
	अगर (ret)
		host->dev_timings = शून्य;

	/* Set शेष न_अंकD bank to 0 */
	host->bank = 0;
	अगर (!of_property_पढ़ो_u32(np, "bank", &val)) अणु
		अगर (val > 3) अणु
			dev_err(&pdev->dev, "invalid bank %u\n", val);
			वापस -EINVAL;
		पूर्ण
		host->bank = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fsmc_nand_attach_chip(काष्ठा nand_chip *nand)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा fsmc_nand_data *host = nand_to_fsmc(nand);

	अगर (nand->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_INVALID)
		nand->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	अगर (!nand->ecc.size)
		nand->ecc.size = 512;

	अगर (AMBA_REV_BITS(host->pid) >= 8) अणु
		nand->ecc.पढ़ो_page = fsmc_पढ़ो_page_hwecc;
		nand->ecc.calculate = fsmc_पढ़ो_hwecc_ecc4;
		nand->ecc.correct = fsmc_bch8_correct_data;
		nand->ecc.bytes = 13;
		nand->ecc.strength = 8;
	पूर्ण

	अगर (AMBA_REV_BITS(host->pid) >= 8) अणु
		चयन (mtd->oobsize) अणु
		हाल 16:
		हाल 64:
		हाल 128:
		हाल 224:
		हाल 256:
			अवरोध;
		शेष:
			dev_warn(host->dev,
				 "No oob scheme defined for oobsize %d\n",
				 mtd->oobsize);
			वापस -EINVAL;
		पूर्ण

		mtd_set_ooblayout(mtd, &fsmc_ecc4_ooblayout_ops);

		वापस 0;
	पूर्ण

	चयन (nand->ecc.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		dev_info(host->dev, "Using 1-bit HW ECC scheme\n");
		nand->ecc.calculate = fsmc_पढ़ो_hwecc_ecc1;
		nand->ecc.correct = fsmc_correct_ecc1;
		nand->ecc.hwctl = fsmc_enable_hwecc;
		nand->ecc.bytes = 3;
		nand->ecc.strength = 1;
		nand->ecc.options |= न_अंकD_ECC_SOFT_HAMMING_SM_ORDER;
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		अगर (nand->ecc.algo == न_अंकD_ECC_ALGO_BCH) अणु
			dev_info(host->dev,
				 "Using 4-bit SW BCH ECC scheme\n");
			अवरोध;
		पूर्ण
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_ON_DIE:
		अवरोध;

	शेष:
		dev_err(host->dev, "Unsupported ECC mode!\n");
		वापस -ENOTSUPP;
	पूर्ण

	/*
	 * Don't set layout क्रम BCH4 SW ECC. This will be
	 * generated later during BCH initialization.
	 */
	अगर (nand->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		चयन (mtd->oobsize) अणु
		हाल 16:
		हाल 64:
		हाल 128:
			mtd_set_ooblayout(mtd,
					  &fsmc_ecc1_ooblayout_ops);
			अवरोध;
		शेष:
			dev_warn(host->dev,
				 "No oob scheme defined for oobsize %d\n",
				 mtd->oobsize);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops fsmc_nand_controller_ops = अणु
	.attach_chip = fsmc_nand_attach_chip,
	.exec_op = fsmc_exec_op,
	.setup_पूर्णांकerface = fsmc_setup_पूर्णांकerface,
पूर्ण;

/**
 * fsmc_nand_disable() - Disables the न_अंकD bank
 * @host: The instance to disable
 */
अटल व्योम fsmc_nand_disable(काष्ठा fsmc_nand_data *host)
अणु
	u32 val;

	val = पढ़ोl(host->regs_va + FSMC_PC);
	val &= ~FSMC_ENABLE;
	ग_लिखोl(val, host->regs_va + FSMC_PC);
पूर्ण

/*
 * fsmc_nand_probe - Probe function
 * @pdev:       platक्रमm device काष्ठाure
 */
अटल पूर्णांक __init fsmc_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsmc_nand_data *host;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *nand;
	काष्ठा resource *res;
	व्योम __iomem *base;
	dma_cap_mask_t mask;
	पूर्णांक ret = 0;
	u32 pid;
	पूर्णांक i;

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	nand = &host->nand;

	ret = fsmc_nand_probe_config_dt(pdev, host, nand);
	अगर (ret)
		वापस ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nand_data");
	host->data_va = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->data_va))
		वापस PTR_ERR(host->data_va);

	host->data_pa = (dma_addr_t)res->start;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nand_addr");
	host->addr_va = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->addr_va))
		वापस PTR_ERR(host->addr_va);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nand_cmd");
	host->cmd_va = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->cmd_va))
		वापस PTR_ERR(host->cmd_va);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "fsmc_regs");
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	host->regs_va = base + FSMC_NOR_REG_SIZE +
		(host->bank * FSMC_न_अंकD_BANK_SZ);

	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		dev_err(&pdev->dev, "failed to fetch block clock\n");
		वापस PTR_ERR(host->clk);
	पूर्ण

	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		वापस ret;

	/*
	 * This device ID is actually a common AMBA ID as used on the
	 * AMBA PrimeCell bus. However it is not a PrimeCell.
	 */
	क्रम (pid = 0, i = 0; i < 4; i++)
		pid |= (पढ़ोl(base + resource_size(res) - 0x20 + 4 * i) &
			255) << (i * 8);

	host->pid = pid;

	dev_info(&pdev->dev,
		 "FSMC device partno %03x, manufacturer %02x, revision %02x, config %02x\n",
		 AMBA_PART_BITS(pid), AMBA_MANF_BITS(pid),
		 AMBA_REV_BITS(pid), AMBA_CONFIG_BITS(pid));

	host->dev = &pdev->dev;

	अगर (host->mode == USE_DMA_ACCESS)
		init_completion(&host->dma_access_complete);

	/* Link all निजी poपूर्णांकers */
	mtd = nand_to_mtd(&host->nand);
	nand_set_flash_node(nand, pdev->dev.of_node);

	mtd->dev.parent = &pdev->dev;

	nand->badblockbits = 7;

	अगर (host->mode == USE_DMA_ACCESS) अणु
		dma_cap_zero(mask);
		dma_cap_set(DMA_MEMCPY, mask);
		host->पढ़ो_dma_chan = dma_request_channel(mask, filter, शून्य);
		अगर (!host->पढ़ो_dma_chan) अणु
			dev_err(&pdev->dev, "Unable to get read dma channel\n");
			ret = -ENODEV;
			जाओ disable_clk;
		पूर्ण
		host->ग_लिखो_dma_chan = dma_request_channel(mask, filter, शून्य);
		अगर (!host->ग_लिखो_dma_chan) अणु
			dev_err(&pdev->dev, "Unable to get write dma channel\n");
			ret = -ENODEV;
			जाओ release_dma_पढ़ो_chan;
		पूर्ण
	पूर्ण

	अगर (host->dev_timings) अणु
		fsmc_nand_setup(host, host->dev_timings);
		nand->options |= न_अंकD_KEEP_TIMINGS;
	पूर्ण

	nand_controller_init(&host->base);
	host->base.ops = &fsmc_nand_controller_ops;
	nand->controller = &host->base;

	/*
	 * Scan to find existence of the device
	 */
	ret = nand_scan(nand, 1);
	अगर (ret)
		जाओ release_dma_ग_लिखो_chan;

	mtd->name = "nand";
	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		जाओ cleanup_nand;

	platक्रमm_set_drvdata(pdev, host);
	dev_info(&pdev->dev, "FSMC NAND driver registration successful\n");

	वापस 0;

cleanup_nand:
	nand_cleanup(nand);
release_dma_ग_लिखो_chan:
	अगर (host->mode == USE_DMA_ACCESS)
		dma_release_channel(host->ग_लिखो_dma_chan);
release_dma_पढ़ो_chan:
	अगर (host->mode == USE_DMA_ACCESS)
		dma_release_channel(host->पढ़ो_dma_chan);
disable_clk:
	fsmc_nand_disable(host);
	clk_disable_unprepare(host->clk);

	वापस ret;
पूर्ण

/*
 * Clean up routine
 */
अटल पूर्णांक fsmc_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsmc_nand_data *host = platक्रमm_get_drvdata(pdev);

	अगर (host) अणु
		काष्ठा nand_chip *chip = &host->nand;
		पूर्णांक ret;

		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		fsmc_nand_disable(host);

		अगर (host->mode == USE_DMA_ACCESS) अणु
			dma_release_channel(host->ग_लिखो_dma_chan);
			dma_release_channel(host->पढ़ो_dma_chan);
		पूर्ण
		clk_disable_unprepare(host->clk);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fsmc_nand_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsmc_nand_data *host = dev_get_drvdata(dev);

	अगर (host)
		clk_disable_unprepare(host->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक fsmc_nand_resume(काष्ठा device *dev)
अणु
	काष्ठा fsmc_nand_data *host = dev_get_drvdata(dev);

	अगर (host) अणु
		clk_prepare_enable(host->clk);
		अगर (host->dev_timings)
			fsmc_nand_setup(host, host->dev_timings);
		nand_reset(&host->nand, 0);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(fsmc_nand_pm_ops, fsmc_nand_suspend, fsmc_nand_resume);

अटल स्थिर काष्ठा of_device_id fsmc_nand_id_table[] = अणु
	अणु .compatible = "st,spear600-fsmc-nand" पूर्ण,
	अणु .compatible = "stericsson,fsmc-nand" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsmc_nand_id_table);

अटल काष्ठा platक्रमm_driver fsmc_nand_driver = अणु
	.हटाओ = fsmc_nand_हटाओ,
	.driver = अणु
		.name = "fsmc-nand",
		.of_match_table = fsmc_nand_id_table,
		.pm = &fsmc_nand_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(fsmc_nand_driver, fsmc_nand_probe);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Vipin Kumar <vipin.kumar@st.com>, Ashish Priyadarshi");
MODULE_DESCRIPTION("NAND driver for SPEAr Platforms");
