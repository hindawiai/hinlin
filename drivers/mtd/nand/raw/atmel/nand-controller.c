<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 ATMEL
 * Copyright 2017 Free Electrons
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *
 * Derived from the aपंचांगel_nand.c driver which contained the following
 * copyrights:
 *
 *   Copyright 2003 Rick Bronson
 *
 *   Derived from drivers/mtd/nand/autcpu12.c (हटाओd in v3.8)
 *	Copyright 2001 Thomas Gleixner (gleixner@autronix.de)
 *
 *   Derived from drivers/mtd/spia.c (हटाओd in v3.8)
 *	Copyright 2000 Steven J. Hill (sjhill@cotw.com)
 *
 *
 *   Add Hardware ECC support क्रम AT91SAM9260 / AT91SAM9263
 *	Riअक्षरd Genoud (riअक्षरd.genoud@gmail.com), Adeneo Copyright 2007
 *
 *   Derived from Das U-Boot source code
 *	(u-boot-1.1.5/board/aपंचांगel/at91sam9263ek/nand.c)
 *	Copyright 2006 ATMEL Rousset, Lacressonniere Nicolas
 *
 *   Add Programmable Multibit ECC support क्रम various AT91 SoC
 *	Copyright 2012 ATMEL, Hong Xu
 *
 *   Add Nand Flash Controller support क्रम SAMA5 SoC
 *	Copyright 2013 ATMEL, Josh Wu (josh.wu@aपंचांगel.com)
 *
 * A few words about the naming convention in this file. This convention
 * applies to काष्ठाure and function names.
 *
 * Prefixes:
 *
 * - aपंचांगel_nand_: all generic काष्ठाures/functions
 * - aपंचांगel_smc_nand_: all काष्ठाures/functions specअगरic to the SMC पूर्णांकerface
 *		      (at91sam9 and avr32 SoCs)
 * - aपंचांगel_hsmc_nand_: all काष्ठाures/functions specअगरic to the HSMC पूर्णांकerface
 *		       (sama5 SoCs and later)
 * - aपंचांगel_nfc_: all काष्ठाures/functions used to manipulate the NFC sub-block
 *		 that is available in the HSMC block
 * - <soc>_nand_: all SoC specअगरic काष्ठाures/functions
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/aपंचांगel-matrix.h>
#समावेश <linux/mfd/syscon/aपंचांगel-smc.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <soc/at91/aपंचांगel-sfr.h>

#समावेश "pmecc.h"

#घोषणा ATMEL_HSMC_NFC_CFG			0x0
#घोषणा ATMEL_HSMC_NFC_CFG_SPARESIZE(x)		(((x) / 4) << 24)
#घोषणा ATMEL_HSMC_NFC_CFG_SPARESIZE_MASK	GENMASK(30, 24)
#घोषणा ATMEL_HSMC_NFC_CFG_DTO(cyc, mul)	(((cyc) << 16) | ((mul) << 20))
#घोषणा ATMEL_HSMC_NFC_CFG_DTO_MAX		GENMASK(22, 16)
#घोषणा ATMEL_HSMC_NFC_CFG_RBEDGE		BIT(13)
#घोषणा ATMEL_HSMC_NFC_CFG_FALLING_EDGE		BIT(12)
#घोषणा ATMEL_HSMC_NFC_CFG_RSPARE		BIT(9)
#घोषणा ATMEL_HSMC_NFC_CFG_WSPARE		BIT(8)
#घोषणा ATMEL_HSMC_NFC_CFG_PAGESIZE_MASK	GENMASK(2, 0)
#घोषणा ATMEL_HSMC_NFC_CFG_PAGESIZE(x)		(fls((x) / 512) - 1)

#घोषणा ATMEL_HSMC_NFC_CTRL			0x4
#घोषणा ATMEL_HSMC_NFC_CTRL_EN			BIT(0)
#घोषणा ATMEL_HSMC_NFC_CTRL_DIS			BIT(1)

#घोषणा ATMEL_HSMC_NFC_SR			0x8
#घोषणा ATMEL_HSMC_NFC_IER			0xc
#घोषणा ATMEL_HSMC_NFC_IDR			0x10
#घोषणा ATMEL_HSMC_NFC_IMR			0x14
#घोषणा ATMEL_HSMC_NFC_SR_ENABLED		BIT(1)
#घोषणा ATMEL_HSMC_NFC_SR_RB_RISE		BIT(4)
#घोषणा ATMEL_HSMC_NFC_SR_RB_FALL		BIT(5)
#घोषणा ATMEL_HSMC_NFC_SR_BUSY			BIT(8)
#घोषणा ATMEL_HSMC_NFC_SR_WR			BIT(11)
#घोषणा ATMEL_HSMC_NFC_SR_CSID			GENMASK(14, 12)
#घोषणा ATMEL_HSMC_NFC_SR_XFRDONE		BIT(16)
#घोषणा ATMEL_HSMC_NFC_SR_CMDDONE		BIT(17)
#घोषणा ATMEL_HSMC_NFC_SR_DTOE			BIT(20)
#घोषणा ATMEL_HSMC_NFC_SR_UNDEF			BIT(21)
#घोषणा ATMEL_HSMC_NFC_SR_AWB			BIT(22)
#घोषणा ATMEL_HSMC_NFC_SR_NFCASE		BIT(23)
#घोषणा ATMEL_HSMC_NFC_SR_ERRORS		(ATMEL_HSMC_NFC_SR_DTOE | \
						 ATMEL_HSMC_NFC_SR_UNDEF | \
						 ATMEL_HSMC_NFC_SR_AWB | \
						 ATMEL_HSMC_NFC_SR_NFCASE)
#घोषणा ATMEL_HSMC_NFC_SR_RBEDGE(x)		BIT((x) + 24)

#घोषणा ATMEL_HSMC_NFC_ADDR			0x18
#घोषणा ATMEL_HSMC_NFC_BANK			0x1c

#घोषणा ATMEL_NFC_MAX_RB_ID			7

#घोषणा ATMEL_NFC_SRAM_SIZE			0x2400

#घोषणा ATMEL_NFC_CMD(pos, cmd)			((cmd) << (((pos) * 8) + 2))
#घोषणा ATMEL_NFC_VCMD2				BIT(18)
#घोषणा ATMEL_NFC_ACYCLE(naddrs)		((naddrs) << 19)
#घोषणा ATMEL_NFC_CSID(cs)			((cs) << 22)
#घोषणा ATMEL_NFC_DATAEN			BIT(25)
#घोषणा ATMEL_NFC_NFCWR				BIT(26)

#घोषणा ATMEL_NFC_MAX_ADDR_CYCLES		5

#घोषणा ATMEL_न_अंकD_ALE_OFFSET			BIT(21)
#घोषणा ATMEL_न_अंकD_CLE_OFFSET			BIT(22)

#घोषणा DEFAULT_TIMEOUT_MS			1000
#घोषणा MIN_DMA_LEN				128

अटल bool aपंचांगel_nand_aव्योम_dma __पढ़ो_mostly;

MODULE_PARM_DESC(aव्योमdma, "Avoid using DMA");
module_param_named(aव्योमdma, aपंचांगel_nand_aव्योम_dma, bool, 0400);

क्रमागत aपंचांगel_nand_rb_type अणु
	ATMEL_न_अंकD_NO_RB,
	ATMEL_न_अंकD_NATIVE_RB,
	ATMEL_न_अंकD_GPIO_RB,
पूर्ण;

काष्ठा aपंचांगel_nand_rb अणु
	क्रमागत aपंचांगel_nand_rb_type type;
	जोड़ अणु
		काष्ठा gpio_desc *gpio;
		पूर्णांक id;
	पूर्ण;
पूर्ण;

काष्ठा aपंचांगel_nand_cs अणु
	पूर्णांक id;
	काष्ठा aपंचांगel_nand_rb rb;
	काष्ठा gpio_desc *csgpio;
	काष्ठा अणु
		व्योम __iomem *virt;
		dma_addr_t dma;
	पूर्ण io;

	काष्ठा aपंचांगel_smc_cs_conf smcconf;
पूर्ण;

काष्ठा aपंचांगel_nand अणु
	काष्ठा list_head node;
	काष्ठा device *dev;
	काष्ठा nand_chip base;
	काष्ठा aपंचांगel_nand_cs *activecs;
	काष्ठा aपंचांगel_pmecc_user *pmecc;
	काष्ठा gpio_desc *cdgpio;
	पूर्णांक numcs;
	काष्ठा aपंचांगel_nand_cs cs[];
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_nand *to_aपंचांगel_nand(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा aपंचांगel_nand, base);
पूर्ण

क्रमागत aपंचांगel_nfc_data_xfer अणु
	ATMEL_NFC_NO_DATA,
	ATMEL_NFC_READ_DATA,
	ATMEL_NFC_WRITE_DATA,
पूर्ण;

काष्ठा aपंचांगel_nfc_op अणु
	u8 cs;
	u8 ncmds;
	u8 cmds[2];
	u8 naddrs;
	u8 addrs[5];
	क्रमागत aपंचांगel_nfc_data_xfer data;
	u32 रुको;
	u32 errors;
पूर्ण;

काष्ठा aपंचांगel_nand_controller;
काष्ठा aपंचांगel_nand_controller_caps;

काष्ठा aपंचांगel_nand_controller_ops अणु
	पूर्णांक (*probe)(काष्ठा platक्रमm_device *pdev,
		     स्थिर काष्ठा aपंचांगel_nand_controller_caps *caps);
	पूर्णांक (*हटाओ)(काष्ठा aपंचांगel_nand_controller *nc);
	व्योम (*nand_init)(काष्ठा aपंचांगel_nand_controller *nc,
			  काष्ठा aपंचांगel_nand *nand);
	पूर्णांक (*ecc_init)(काष्ठा nand_chip *chip);
	पूर्णांक (*setup_पूर्णांकerface)(काष्ठा aपंचांगel_nand *nand, पूर्णांक csline,
			       स्थिर काष्ठा nand_पूर्णांकerface_config *conf);
	पूर्णांक (*exec_op)(काष्ठा aपंचांगel_nand *nand,
		       स्थिर काष्ठा nand_operation *op, bool check_only);
पूर्ण;

काष्ठा aपंचांगel_nand_controller_caps अणु
	bool has_dma;
	bool legacy_of_bindings;
	u32 ale_offs;
	u32 cle_offs;
	स्थिर अक्षर *ebi_csa_regmap_name;
	स्थिर काष्ठा aपंचांगel_nand_controller_ops *ops;
पूर्ण;

काष्ठा aपंचांगel_nand_controller अणु
	काष्ठा nand_controller base;
	स्थिर काष्ठा aपंचांगel_nand_controller_caps *caps;
	काष्ठा device *dev;
	काष्ठा regmap *smc;
	काष्ठा dma_chan *dmac;
	काष्ठा aपंचांगel_pmecc *pmecc;
	काष्ठा list_head chips;
	काष्ठा clk *mck;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_nand_controller *
to_nand_controller(काष्ठा nand_controller *ctl)
अणु
	वापस container_of(ctl, काष्ठा aपंचांगel_nand_controller, base);
पूर्ण

काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg अणु
	u32 offs;
	u32 nfd0_on_d16;
पूर्ण;

काष्ठा aपंचांगel_smc_nand_controller अणु
	काष्ठा aपंचांगel_nand_controller base;
	काष्ठा regmap *ebi_csa_regmap;
	काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg *ebi_csa;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_smc_nand_controller *
to_smc_nand_controller(काष्ठा nand_controller *ctl)
अणु
	वापस container_of(to_nand_controller(ctl),
			    काष्ठा aपंचांगel_smc_nand_controller, base);
पूर्ण

काष्ठा aपंचांगel_hsmc_nand_controller अणु
	काष्ठा aपंचांगel_nand_controller base;
	काष्ठा अणु
		काष्ठा gen_pool *pool;
		व्योम __iomem *virt;
		dma_addr_t dma;
	पूर्ण sram;
	स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *hsmc_layout;
	काष्ठा regmap *io;
	काष्ठा aपंचांगel_nfc_op op;
	काष्ठा completion complete;
	u32 cfg;
	पूर्णांक irq;

	/* Only used when instantiating from legacy DT bindings. */
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_hsmc_nand_controller *
to_hsmc_nand_controller(काष्ठा nand_controller *ctl)
अणु
	वापस container_of(to_nand_controller(ctl),
			    काष्ठा aपंचांगel_hsmc_nand_controller, base);
पूर्ण

अटल bool aपंचांगel_nfc_op_करोne(काष्ठा aपंचांगel_nfc_op *op, u32 status)
अणु
	op->errors |= status & ATMEL_HSMC_NFC_SR_ERRORS;
	op->रुको ^= status & op->रुको;

	वापस !op->रुको || op->errors;
पूर्ण

अटल irqवापस_t aपंचांगel_nfc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा aपंचांगel_hsmc_nand_controller *nc = data;
	u32 sr, rcvd;
	bool करोne;

	regmap_पढ़ो(nc->base.smc, ATMEL_HSMC_NFC_SR, &sr);

	rcvd = sr & (nc->op.रुको | ATMEL_HSMC_NFC_SR_ERRORS);
	करोne = aपंचांगel_nfc_op_करोne(&nc->op, sr);

	अगर (rcvd)
		regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_IDR, rcvd);

	अगर (करोne)
		complete(&nc->complete);

	वापस rcvd ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक aपंचांगel_nfc_रुको(काष्ठा aपंचांगel_hsmc_nand_controller *nc, bool poll,
			  अचिन्हित पूर्णांक समयout_ms)
अणु
	पूर्णांक ret;

	अगर (!समयout_ms)
		समयout_ms = DEFAULT_TIMEOUT_MS;

	अगर (poll) अणु
		u32 status;

		ret = regmap_पढ़ो_poll_समयout(nc->base.smc,
					       ATMEL_HSMC_NFC_SR, status,
					       aपंचांगel_nfc_op_करोne(&nc->op,
								 status),
					       0, समयout_ms * 1000);
	पूर्ण अन्यथा अणु
		init_completion(&nc->complete);
		regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_IER,
			     nc->op.रुको | ATMEL_HSMC_NFC_SR_ERRORS);
		ret = रुको_क्रम_completion_समयout(&nc->complete,
						msecs_to_jअगरfies(समयout_ms));
		अगर (!ret)
			ret = -ETIMEDOUT;
		अन्यथा
			ret = 0;

		regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_IDR, 0xffffffff);
	पूर्ण

	अगर (nc->op.errors & ATMEL_HSMC_NFC_SR_DTOE) अणु
		dev_err(nc->base.dev, "Waiting NAND R/B Timeout\n");
		ret = -ETIMEDOUT;
	पूर्ण

	अगर (nc->op.errors & ATMEL_HSMC_NFC_SR_UNDEF) अणु
		dev_err(nc->base.dev, "Access to an undefined area\n");
		ret = -EIO;
	पूर्ण

	अगर (nc->op.errors & ATMEL_HSMC_NFC_SR_AWB) अणु
		dev_err(nc->base.dev, "Access while busy\n");
		ret = -EIO;
	पूर्ण

	अगर (nc->op.errors & ATMEL_HSMC_NFC_SR_NFCASE) अणु
		dev_err(nc->base.dev, "Wrong access size\n");
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_nand_dma_transfer_finished(व्योम *data)
अणु
	काष्ठा completion *finished = data;

	complete(finished);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_dma_transfer(काष्ठा aपंचांगel_nand_controller *nc,
				   व्योम *buf, dma_addr_t dev_dma, माप_प्रकार len,
				   क्रमागत dma_data_direction dir)
अणु
	DECLARE_COMPLETION_ONSTACK(finished);
	dma_addr_t src_dma, dst_dma, buf_dma;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;

	buf_dma = dma_map_single(nc->dev, buf, len, dir);
	अगर (dma_mapping_error(nc->dev, dev_dma)) अणु
		dev_err(nc->dev,
			"Failed to prepare a buffer for DMA access\n");
		जाओ err;
	पूर्ण

	अगर (dir == DMA_FROM_DEVICE) अणु
		src_dma = dev_dma;
		dst_dma = buf_dma;
	पूर्ण अन्यथा अणु
		src_dma = buf_dma;
		dst_dma = dev_dma;
	पूर्ण

	tx = dmaengine_prep_dma_स_नकल(nc->dmac, dst_dma, src_dma, len,
				       DMA_CTRL_ACK | DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(nc->dev, "Failed to prepare DMA memcpy\n");
		जाओ err_unmap;
	पूर्ण

	tx->callback = aपंचांगel_nand_dma_transfer_finished;
	tx->callback_param = &finished;

	cookie = dmaengine_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_err(nc->dev, "Failed to do DMA tx_submit\n");
		जाओ err_unmap;
	पूर्ण

	dma_async_issue_pending(nc->dmac);
	रुको_क्रम_completion(&finished);

	वापस 0;

err_unmap:
	dma_unmap_single(nc->dev, buf_dma, len, dir);

err:
	dev_dbg(nc->dev, "Fall back to CPU I/O\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक aपंचांगel_nfc_exec_op(काष्ठा aपंचांगel_hsmc_nand_controller *nc, bool poll)
अणु
	u8 *addrs = nc->op.addrs;
	अचिन्हित पूर्णांक op = 0;
	u32 addr, val;
	पूर्णांक i, ret;

	nc->op.रुको = ATMEL_HSMC_NFC_SR_CMDDONE;

	क्रम (i = 0; i < nc->op.ncmds; i++)
		op |= ATMEL_NFC_CMD(i, nc->op.cmds[i]);

	अगर (nc->op.naddrs == ATMEL_NFC_MAX_ADDR_CYCLES)
		regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_ADDR, *addrs++);

	op |= ATMEL_NFC_CSID(nc->op.cs) |
	      ATMEL_NFC_ACYCLE(nc->op.naddrs);

	अगर (nc->op.ncmds > 1)
		op |= ATMEL_NFC_VCMD2;

	addr = addrs[0] | (addrs[1] << 8) | (addrs[2] << 16) |
	       (addrs[3] << 24);

	अगर (nc->op.data != ATMEL_NFC_NO_DATA) अणु
		op |= ATMEL_NFC_DATAEN;
		nc->op.रुको |= ATMEL_HSMC_NFC_SR_XFRDONE;

		अगर (nc->op.data == ATMEL_NFC_WRITE_DATA)
			op |= ATMEL_NFC_NFCWR;
	पूर्ण

	/* Clear all flags. */
	regmap_पढ़ो(nc->base.smc, ATMEL_HSMC_NFC_SR, &val);

	/* Send the command. */
	regmap_ग_लिखो(nc->io, op, addr);

	ret = aपंचांगel_nfc_रुको(nc, poll, 0);
	अगर (ret)
		dev_err(nc->base.dev,
			"Failed to send NAND command (err = %d)!",
			ret);

	/* Reset the op state. */
	स_रखो(&nc->op, 0, माप(nc->op));

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_nand_data_in(काष्ठा aपंचांगel_nand *nand, व्योम *buf,
			       अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	काष्ठा aपंचांगel_nand_controller *nc;

	nc = to_nand_controller(nand->base.controller);

	/*
	 * If the controller supports DMA, the buffer address is DMA-able and
	 * len is दीर्घ enough to make DMA transfers profitable, let's trigger
	 * a DMA transfer. If it fails, fallback to PIO mode.
	 */
	अगर (nc->dmac && virt_addr_valid(buf) &&
	    len >= MIN_DMA_LEN && !क्रमce_8bit &&
	    !aपंचांगel_nand_dma_transfer(nc, buf, nand->activecs->io.dma, len,
				     DMA_FROM_DEVICE))
		वापस;

	अगर ((nand->base.options & न_अंकD_BUSWIDTH_16) && !क्रमce_8bit)
		ioपढ़ो16_rep(nand->activecs->io.virt, buf, len / 2);
	अन्यथा
		ioपढ़ो8_rep(nand->activecs->io.virt, buf, len);
पूर्ण

अटल व्योम aपंचांगel_nand_data_out(काष्ठा aपंचांगel_nand *nand, स्थिर व्योम *buf,
				अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	काष्ठा aपंचांगel_nand_controller *nc;

	nc = to_nand_controller(nand->base.controller);

	/*
	 * If the controller supports DMA, the buffer address is DMA-able and
	 * len is दीर्घ enough to make DMA transfers profitable, let's trigger
	 * a DMA transfer. If it fails, fallback to PIO mode.
	 */
	अगर (nc->dmac && virt_addr_valid(buf) &&
	    len >= MIN_DMA_LEN && !क्रमce_8bit &&
	    !aपंचांगel_nand_dma_transfer(nc, (व्योम *)buf, nand->activecs->io.dma,
				     len, DMA_TO_DEVICE))
		वापस;

	अगर ((nand->base.options & न_अंकD_BUSWIDTH_16) && !क्रमce_8bit)
		ioग_लिखो16_rep(nand->activecs->io.virt, buf, len / 2);
	अन्यथा
		ioग_लिखो8_rep(nand->activecs->io.virt, buf, len);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_रुकोrdy(काष्ठा aपंचांगel_nand *nand, अचिन्हित पूर्णांक समयout_ms)
अणु
	अगर (nand->activecs->rb.type == ATMEL_न_अंकD_NO_RB)
		वापस nand_soft_रुकोrdy(&nand->base, समयout_ms);

	वापस nand_gpio_रुकोrdy(&nand->base, nand->activecs->rb.gpio,
				 समयout_ms);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_रुकोrdy(काष्ठा aपंचांगel_nand *nand,
				   अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	u32 status, mask;

	अगर (nand->activecs->rb.type != ATMEL_न_अंकD_NATIVE_RB)
		वापस aपंचांगel_nand_रुकोrdy(nand, समयout_ms);

	nc = to_hsmc_nand_controller(nand->base.controller);
	mask = ATMEL_HSMC_NFC_SR_RBEDGE(nand->activecs->rb.id);
	वापस regmap_पढ़ो_poll_समयout_atomic(nc->base.smc, ATMEL_HSMC_NFC_SR,
					       status, status & mask,
					       10, समयout_ms * 1000);
पूर्ण

अटल व्योम aपंचांगel_nand_select_target(काष्ठा aपंचांगel_nand *nand,
				     अचिन्हित पूर्णांक cs)
अणु
	nand->activecs = &nand->cs[cs];
पूर्ण

अटल व्योम aपंचांगel_hsmc_nand_select_target(काष्ठा aपंचांगel_nand *nand,
					  अचिन्हित पूर्णांक cs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(&nand->base);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	u32 cfg = ATMEL_HSMC_NFC_CFG_PAGESIZE(mtd->ग_लिखोsize) |
		  ATMEL_HSMC_NFC_CFG_SPARESIZE(mtd->oobsize) |
		  ATMEL_HSMC_NFC_CFG_RSPARE;

	nand->activecs = &nand->cs[cs];
	nc = to_hsmc_nand_controller(nand->base.controller);
	अगर (nc->cfg == cfg)
		वापस;

	regmap_update_bits(nc->base.smc, ATMEL_HSMC_NFC_CFG,
			   ATMEL_HSMC_NFC_CFG_PAGESIZE_MASK |
			   ATMEL_HSMC_NFC_CFG_SPARESIZE_MASK |
			   ATMEL_HSMC_NFC_CFG_RSPARE |
			   ATMEL_HSMC_NFC_CFG_WSPARE,
			   cfg);
	nc->cfg = cfg;
पूर्ण

अटल पूर्णांक aपंचांगel_smc_nand_exec_instr(काष्ठा aपंचांगel_nand *nand,
				     स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा aपंचांगel_nand_controller *nc;
	अचिन्हित पूर्णांक i;

	nc = to_nand_controller(nand->base.controller);
	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		ग_लिखोb(instr->ctx.cmd.opcode,
		       nand->activecs->io.virt + nc->caps->cle_offs);
		वापस 0;
	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
			ग_लिखोb(instr->ctx.addr.addrs[i],
			       nand->activecs->io.virt + nc->caps->ale_offs);
		वापस 0;
	हाल न_अंकD_OP_DATA_IN_INSTR:
		aपंचांगel_nand_data_in(nand, instr->ctx.data.buf.in,
				   instr->ctx.data.len,
				   instr->ctx.data.क्रमce_8bit);
		वापस 0;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		aपंचांगel_nand_data_out(nand, instr->ctx.data.buf.out,
				    instr->ctx.data.len,
				    instr->ctx.data.क्रमce_8bit);
		वापस 0;
	हाल न_अंकD_OP_WAITRDY_INSTR:
		वापस aपंचांगel_nand_रुकोrdy(nand,
					  instr->ctx.रुकोrdy.समयout_ms);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aपंचांगel_smc_nand_exec_op(काष्ठा aपंचांगel_nand *nand,
				  स्थिर काष्ठा nand_operation *op,
				  bool check_only)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (check_only)
		वापस 0;

	aपंचांगel_nand_select_target(nand, op->cs);
	gpiod_set_value(nand->activecs->csgpio, 0);
	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = aपंचांगel_smc_nand_exec_instr(nand, &op->instrs[i]);
		अगर (ret)
			अवरोध;
	पूर्ण
	gpiod_set_value(nand->activecs->csgpio, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_exec_cmd_addr(काष्ठा nand_chip *chip,
				    स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	अचिन्हित पूर्णांक i, j;

	nc = to_hsmc_nand_controller(chip->controller);

	nc->op.cs = nand->activecs->id;
	क्रम (i = 0; i < subop->ninstrs; i++) अणु
		स्थिर काष्ठा nand_op_instr *instr = &subop->instrs[i];

		अगर (instr->type == न_अंकD_OP_CMD_INSTR) अणु
			nc->op.cmds[nc->op.ncmds++] = instr->ctx.cmd.opcode;
			जारी;
		पूर्ण

		क्रम (j = nand_subop_get_addr_start_off(subop, i);
		     j < nand_subop_get_num_addr_cyc(subop, i); j++) अणु
			nc->op.addrs[nc->op.naddrs] = instr->ctx.addr.addrs[j];
			nc->op.naddrs++;
		पूर्ण
	पूर्ण

	वापस aपंचांगel_nfc_exec_op(nc, true);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_exec_rw(काष्ठा nand_chip *chip,
			      स्थिर काष्ठा nand_subop *subop)
अणु
	स्थिर काष्ठा nand_op_instr *instr = subop->instrs;
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);

	अगर (instr->type == न_अंकD_OP_DATA_IN_INSTR)
		aपंचांगel_nand_data_in(nand, instr->ctx.data.buf.in,
				   instr->ctx.data.len,
				   instr->ctx.data.क्रमce_8bit);
	अन्यथा
		aपंचांगel_nand_data_out(nand, instr->ctx.data.buf.out,
				    instr->ctx.data.len,
				    instr->ctx.data.क्रमce_8bit);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_exec_रुकोrdy(काष्ठा nand_chip *chip,
				   स्थिर काष्ठा nand_subop *subop)
अणु
	स्थिर काष्ठा nand_op_instr *instr = subop->instrs;
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);

	वापस aपंचांगel_hsmc_nand_रुकोrdy(nand, instr->ctx.रुकोrdy.समयout_ms);
पूर्ण

अटल स्थिर काष्ठा nand_op_parser aपंचांगel_hsmc_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(aपंचांगel_hsmc_exec_cmd_addr,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 5),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true)),
	न_अंकD_OP_PARSER_PATTERN(aपंचांगel_hsmc_exec_rw,
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, 0)),
	न_अंकD_OP_PARSER_PATTERN(aपंचांगel_hsmc_exec_rw,
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, 0)),
	न_अंकD_OP_PARSER_PATTERN(aपंचांगel_hsmc_exec_रुकोrdy,
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
);

अटल पूर्णांक aपंचांगel_hsmc_nand_exec_op(काष्ठा aपंचांगel_nand *nand,
				   स्थिर काष्ठा nand_operation *op,
				   bool check_only)
अणु
	पूर्णांक ret;

	अगर (check_only)
		वापस nand_op_parser_exec_op(&nand->base,
					      &aपंचांगel_hsmc_op_parser, op, true);

	aपंचांगel_hsmc_nand_select_target(nand, op->cs);
	ret = nand_op_parser_exec_op(&nand->base, &aपंचांगel_hsmc_op_parser, op,
				     false);

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_nfc_copy_to_sram(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				   bool oob_required)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	पूर्णांक ret = -EIO;

	nc = to_hsmc_nand_controller(chip->controller);

	अगर (nc->base.dmac)
		ret = aपंचांगel_nand_dma_transfer(&nc->base, (व्योम *)buf,
					      nc->sram.dma, mtd->ग_लिखोsize,
					      DMA_TO_DEVICE);

	/* Falling back to CPU copy. */
	अगर (ret)
		स_नकल_toio(nc->sram.virt, buf, mtd->ग_लिखोsize);

	अगर (oob_required)
		स_नकल_toio(nc->sram.virt + mtd->ग_लिखोsize, chip->oob_poi,
			    mtd->oobsize);
पूर्ण

अटल व्योम aपंचांगel_nfc_copy_from_sram(काष्ठा nand_chip *chip, u8 *buf,
				     bool oob_required)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	पूर्णांक ret = -EIO;

	nc = to_hsmc_nand_controller(chip->controller);

	अगर (nc->base.dmac)
		ret = aपंचांगel_nand_dma_transfer(&nc->base, buf, nc->sram.dma,
					      mtd->ग_लिखोsize, DMA_FROM_DEVICE);

	/* Falling back to CPU copy. */
	अगर (ret)
		स_नकल_fromio(buf, nc->sram.virt, mtd->ग_लिखोsize);

	अगर (oob_required)
		स_नकल_fromio(chip->oob_poi, nc->sram.virt + mtd->ग_लिखोsize,
			      mtd->oobsize);
पूर्ण

अटल व्योम aपंचांगel_nfc_set_op_addr(काष्ठा nand_chip *chip, पूर्णांक page, पूर्णांक column)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;

	nc = to_hsmc_nand_controller(chip->controller);

	अगर (column >= 0) अणु
		nc->op.addrs[nc->op.naddrs++] = column;

		/*
		 * 2 address cycles क्रम the column offset on large page न_अंकDs.
		 */
		अगर (mtd->ग_लिखोsize > 512)
			nc->op.addrs[nc->op.naddrs++] = column >> 8;
	पूर्ण

	अगर (page >= 0) अणु
		nc->op.addrs[nc->op.naddrs++] = page;
		nc->op.addrs[nc->op.naddrs++] = page >> 8;

		अगर (chip->options & न_अंकD_ROW_ADDR_3)
			nc->op.addrs[nc->op.naddrs++] = page >> 16;
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_enable(काष्ठा nand_chip *chip, पूर्णांक op, bool raw)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_nand_controller *nc;
	पूर्णांक ret;

	nc = to_nand_controller(chip->controller);

	अगर (raw)
		वापस 0;

	ret = aपंचांगel_pmecc_enable(nand->pmecc, op);
	अगर (ret)
		dev_err(nc->dev,
			"Failed to enable ECC engine (err = %d)\n", ret);

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_nand_pmecc_disable(काष्ठा nand_chip *chip, bool raw)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);

	अगर (!raw)
		aपंचांगel_pmecc_disable(nand->pmecc);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_generate_eccbytes(काष्ठा nand_chip *chip, bool raw)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_nand_controller *nc;
	काष्ठा mtd_oob_region oobregion;
	व्योम *eccbuf;
	पूर्णांक ret, i;

	nc = to_nand_controller(chip->controller);

	अगर (raw)
		वापस 0;

	ret = aपंचांगel_pmecc_रुको_rdy(nand->pmecc);
	अगर (ret) अणु
		dev_err(nc->dev,
			"Failed to transfer NAND page data (err = %d)\n",
			ret);
		वापस ret;
	पूर्ण

	mtd_ooblayout_ecc(mtd, 0, &oobregion);
	eccbuf = chip->oob_poi + oobregion.offset;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		aपंचांगel_pmecc_get_generated_eccbytes(nand->pmecc, i,
						   eccbuf);
		eccbuf += chip->ecc.bytes;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_correct_data(काष्ठा nand_chip *chip, व्योम *buf,
					 bool raw)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_nand_controller *nc;
	काष्ठा mtd_oob_region oobregion;
	पूर्णांक ret, i, max_bitflips = 0;
	व्योम *databuf, *eccbuf;

	nc = to_nand_controller(chip->controller);

	अगर (raw)
		वापस 0;

	ret = aपंचांगel_pmecc_रुको_rdy(nand->pmecc);
	अगर (ret) अणु
		dev_err(nc->dev,
			"Failed to read NAND page data (err = %d)\n",
			ret);
		वापस ret;
	पूर्ण

	mtd_ooblayout_ecc(mtd, 0, &oobregion);
	eccbuf = chip->oob_poi + oobregion.offset;
	databuf = buf;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		ret = aपंचांगel_pmecc_correct_sector(nand->pmecc, i, databuf,
						 eccbuf);
		अगर (ret < 0 && !aपंचांगel_pmecc_correct_erased_chunks(nand->pmecc))
			ret = nand_check_erased_ecc_chunk(databuf,
							  chip->ecc.size,
							  eccbuf,
							  chip->ecc.bytes,
							  शून्य, 0,
							  chip->ecc.strength);

		अगर (ret >= 0) अणु
			mtd->ecc_stats.corrected += ret;
			max_bitflips = max(ret, max_bitflips);
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.failed++;
		पूर्ण

		databuf += chip->ecc.size;
		eccbuf += chip->ecc.bytes;
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_ग_लिखो_pg(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				     bool oob_required, पूर्णांक page, bool raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	पूर्णांक ret;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	ret = aपंचांगel_nand_pmecc_enable(chip, न_अंकD_ECC_WRITE, raw);
	अगर (ret)
		वापस ret;

	nand_ग_लिखो_data_op(chip, buf, mtd->ग_लिखोsize, false);

	ret = aपंचांगel_nand_pmecc_generate_eccbytes(chip, raw);
	अगर (ret) अणु
		aपंचांगel_pmecc_disable(nand->pmecc);
		वापस ret;
	पूर्ण

	aपंचांगel_nand_pmecc_disable(chip, raw);

	nand_ग_लिखो_data_op(chip, chip->oob_poi, mtd->oobsize, false);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				       पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस aपंचांगel_nand_pmecc_ग_लिखो_pg(chip, buf, oob_required, page, false);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
					   स्थिर u8 *buf, पूर्णांक oob_required,
					   पूर्णांक page)
अणु
	वापस aपंचांगel_nand_pmecc_ग_लिखो_pg(chip, buf, oob_required, page, true);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_पढ़ो_pg(काष्ठा nand_chip *chip, u8 *buf,
				    bool oob_required, पूर्णांक page, bool raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	ret = aपंचांगel_nand_pmecc_enable(chip, न_अंकD_ECC_READ, raw);
	अगर (ret)
		वापस ret;

	ret = nand_पढ़ो_data_op(chip, buf, mtd->ग_लिखोsize, false, false);
	अगर (ret)
		जाओ out_disable;

	ret = nand_पढ़ो_data_op(chip, chip->oob_poi, mtd->oobsize, false, false);
	अगर (ret)
		जाओ out_disable;

	ret = aपंचांगel_nand_pmecc_correct_data(chip, buf, raw);

out_disable:
	aपंचांगel_nand_pmecc_disable(chip, raw);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_पढ़ो_page(काष्ठा nand_chip *chip, u8 *buf,
				      पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस aपंचांगel_nand_pmecc_पढ़ो_pg(chip, buf, oob_required, page, false);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
					  पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस aपंचांगel_nand_pmecc_पढ़ो_pg(chip, buf, oob_required, page, true);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_pmecc_ग_लिखो_pg(काष्ठा nand_chip *chip,
					  स्थिर u8 *buf, bool oob_required,
					  पूर्णांक page, bool raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	पूर्णांक ret;

	aपंचांगel_hsmc_nand_select_target(nand, chip->cur_cs);
	nc = to_hsmc_nand_controller(chip->controller);

	aपंचांगel_nfc_copy_to_sram(chip, buf, false);

	nc->op.cmds[0] = न_अंकD_CMD_SEQIN;
	nc->op.ncmds = 1;
	aपंचांगel_nfc_set_op_addr(chip, page, 0x0);
	nc->op.cs = nand->activecs->id;
	nc->op.data = ATMEL_NFC_WRITE_DATA;

	ret = aपंचांगel_nand_pmecc_enable(chip, न_अंकD_ECC_WRITE, raw);
	अगर (ret)
		वापस ret;

	ret = aपंचांगel_nfc_exec_op(nc, false);
	अगर (ret) अणु
		aपंचांगel_nand_pmecc_disable(chip, raw);
		dev_err(nc->base.dev,
			"Failed to transfer NAND page data (err = %d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = aपंचांगel_nand_pmecc_generate_eccbytes(chip, raw);

	aपंचांगel_nand_pmecc_disable(chip, raw);

	अगर (ret)
		वापस ret;

	nand_ग_लिखो_data_op(chip, chip->oob_poi, mtd->oobsize, false);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_pmecc_ग_लिखो_page(काष्ठा nand_chip *chip,
					    स्थिर u8 *buf, पूर्णांक oob_required,
					    पूर्णांक page)
अणु
	वापस aपंचांगel_hsmc_nand_pmecc_ग_लिखो_pg(chip, buf, oob_required, page,
					      false);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_pmecc_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
						स्थिर u8 *buf,
						पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस aपंचांगel_hsmc_nand_pmecc_ग_लिखो_pg(chip, buf, oob_required, page,
					      true);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_pmecc_पढ़ो_pg(काष्ठा nand_chip *chip, u8 *buf,
					 bool oob_required, पूर्णांक page,
					 bool raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	पूर्णांक ret;

	aपंचांगel_hsmc_nand_select_target(nand, chip->cur_cs);
	nc = to_hsmc_nand_controller(chip->controller);

	/*
	 * Optimized पढ़ो page accessors only work when the न_अंकD R/B pin is
	 * connected to a native SoC R/B pin. If that's not the हाल, fallback
	 * to the non-optimized one.
	 */
	अगर (nand->activecs->rb.type != ATMEL_न_अंकD_NATIVE_RB)
		वापस aपंचांगel_nand_pmecc_पढ़ो_pg(chip, buf, oob_required, page,
						raw);

	nc->op.cmds[nc->op.ncmds++] = न_अंकD_CMD_READ0;

	अगर (mtd->ग_लिखोsize > 512)
		nc->op.cmds[nc->op.ncmds++] = न_अंकD_CMD_READSTART;

	aपंचांगel_nfc_set_op_addr(chip, page, 0x0);
	nc->op.cs = nand->activecs->id;
	nc->op.data = ATMEL_NFC_READ_DATA;

	ret = aपंचांगel_nand_pmecc_enable(chip, न_अंकD_ECC_READ, raw);
	अगर (ret)
		वापस ret;

	ret = aपंचांगel_nfc_exec_op(nc, false);
	अगर (ret) अणु
		aपंचांगel_nand_pmecc_disable(chip, raw);
		dev_err(nc->base.dev,
			"Failed to load NAND page data (err = %d)\n",
			ret);
		वापस ret;
	पूर्ण

	aपंचांगel_nfc_copy_from_sram(chip, buf, true);

	ret = aपंचांगel_nand_pmecc_correct_data(chip, buf, raw);

	aपंचांगel_nand_pmecc_disable(chip, raw);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_pmecc_पढ़ो_page(काष्ठा nand_chip *chip, u8 *buf,
					   पूर्णांक oob_required, पूर्णांक page)
अणु
	वापस aपंचांगel_hsmc_nand_pmecc_पढ़ो_pg(chip, buf, oob_required, page,
					     false);
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_pmecc_पढ़ो_page_raw(काष्ठा nand_chip *chip,
					       u8 *buf, पूर्णांक oob_required,
					       पूर्णांक page)
अणु
	वापस aपंचांगel_hsmc_nand_pmecc_पढ़ो_pg(chip, buf, oob_required, page,
					     true);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_pmecc_init(काष्ठा nand_chip *chip)
अणु
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_device *nanddev = mtd_to_nanddev(mtd);
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_nand_controller *nc;
	काष्ठा aपंचांगel_pmecc_user_req req;

	nc = to_nand_controller(chip->controller);

	अगर (!nc->pmecc) अणु
		dev_err(nc->dev, "HW ECC not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (nc->caps->legacy_of_bindings) अणु
		u32 val;

		अगर (!of_property_पढ़ो_u32(nc->dev->of_node, "atmel,pmecc-cap",
					  &val))
			chip->ecc.strength = val;

		अगर (!of_property_पढ़ो_u32(nc->dev->of_node,
					  "atmel,pmecc-sector-size",
					  &val))
			chip->ecc.size = val;
	पूर्ण

	अगर (nanddev->ecc.user_conf.flags & न_अंकD_ECC_MAXIMIZE_STRENGTH)
		req.ecc.strength = ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH;
	अन्यथा अगर (chip->ecc.strength)
		req.ecc.strength = chip->ecc.strength;
	अन्यथा अगर (requirements->strength)
		req.ecc.strength = requirements->strength;
	अन्यथा
		req.ecc.strength = ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH;

	अगर (chip->ecc.size)
		req.ecc.sectorsize = chip->ecc.size;
	अन्यथा अगर (requirements->step_size)
		req.ecc.sectorsize = requirements->step_size;
	अन्यथा
		req.ecc.sectorsize = ATMEL_PMECC_SECTOR_SIZE_AUTO;

	req.pagesize = mtd->ग_लिखोsize;
	req.oobsize = mtd->oobsize;

	अगर (mtd->ग_लिखोsize <= 512) अणु
		req.ecc.bytes = 4;
		req.ecc.ooboffset = 0;
	पूर्ण अन्यथा अणु
		req.ecc.bytes = mtd->oobsize - 2;
		req.ecc.ooboffset = ATMEL_PMECC_OOBOFFSET_AUTO;
	पूर्ण

	nand->pmecc = aपंचांगel_pmecc_create_user(nc->pmecc, &req);
	अगर (IS_ERR(nand->pmecc))
		वापस PTR_ERR(nand->pmecc);

	chip->ecc.algo = न_अंकD_ECC_ALGO_BCH;
	chip->ecc.size = req.ecc.sectorsize;
	chip->ecc.bytes = req.ecc.bytes / req.ecc.nsectors;
	chip->ecc.strength = req.ecc.strength;

	chip->options |= न_अंकD_NO_SUBPAGE_WRITE;

	mtd_set_ooblayout(mtd, nand_get_large_page_ooblayout());

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_nand_ecc_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा aपंचांगel_nand_controller *nc;
	पूर्णांक ret;

	nc = to_nand_controller(chip->controller);

	चयन (chip->ecc.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		/*
		 * Nothing to करो, the core will initialize everything क्रम us.
		 */
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		ret = aपंचांगel_nand_pmecc_init(chip);
		अगर (ret)
			वापस ret;

		chip->ecc.पढ़ो_page = aपंचांगel_nand_pmecc_पढ़ो_page;
		chip->ecc.ग_लिखो_page = aपंचांगel_nand_pmecc_ग_लिखो_page;
		chip->ecc.पढ़ो_page_raw = aपंचांगel_nand_pmecc_पढ़ो_page_raw;
		chip->ecc.ग_लिखो_page_raw = aपंचांगel_nand_pmecc_ग_लिखो_page_raw;
		अवरोध;

	शेष:
		/* Other modes are not supported. */
		dev_err(nc->dev, "Unsupported ECC mode: %d\n",
			chip->ecc.engine_type);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_ecc_init(काष्ठा nand_chip *chip)
अणु
	पूर्णांक ret;

	ret = aपंचांगel_nand_ecc_init(chip);
	अगर (ret)
		वापस ret;

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	/* Adjust the ECC operations क्रम the HSMC IP. */
	chip->ecc.पढ़ो_page = aपंचांगel_hsmc_nand_pmecc_पढ़ो_page;
	chip->ecc.ग_लिखो_page = aपंचांगel_hsmc_nand_pmecc_ग_लिखो_page;
	chip->ecc.पढ़ो_page_raw = aपंचांगel_hsmc_nand_pmecc_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page_raw = aपंचांगel_hsmc_nand_pmecc_ग_लिखो_page_raw;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_smc_nand_prepare_smcconf(काष्ठा aपंचांगel_nand *nand,
					स्थिर काष्ठा nand_पूर्णांकerface_config *conf,
					काष्ठा aपंचांगel_smc_cs_conf *smcconf)
अणु
	u32 ncycles, totalcycles, समयps, mckperiodps;
	काष्ठा aपंचांगel_nand_controller *nc;
	पूर्णांक ret;

	nc = to_nand_controller(nand->base.controller);

	/* DDR पूर्णांकerface not supported. */
	अगर (conf->type != न_अंकD_SDR_IFACE)
		वापस -ENOTSUPP;

	/*
	 * tRC < 30ns implies EDO mode. This controller करोes not support this
	 * mode.
	 */
	अगर (conf->timings.sdr.tRC_min < 30000)
		वापस -ENOTSUPP;

	aपंचांगel_smc_cs_conf_init(smcconf);

	mckperiodps = NSEC_PER_SEC / clk_get_rate(nc->mck);
	mckperiodps *= 1000;

	/*
	 * Set ग_लिखो pulse timing. This one is easy to extract:
	 *
	 * NWE_PULSE = tWP
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tWP_min, mckperiodps);
	totalcycles = ncycles;
	ret = aपंचांगel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NWE_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/*
	 * The ग_लिखो setup timing depends on the operation करोne on the न_अंकD.
	 * All operations goes through the same data bus, but the operation
	 * type depends on the address we are writing to (ALE/CLE address
	 * lines).
	 * Since we have no way to dअगरferentiate the dअगरferent operations at
	 * the SMC level, we must consider the worst हाल (the biggest setup
	 * समय among all operation types):
	 *
	 * NWE_SETUP = max(tCLS, tCS, tALS, tDS) - NWE_PULSE
	 */
	समयps = max3(conf->timings.sdr.tCLS_min, conf->timings.sdr.tCS_min,
		      conf->timings.sdr.tALS_min);
	समयps = max(समयps, conf->timings.sdr.tDS_min);
	ncycles = DIV_ROUND_UP(समयps, mckperiodps);
	ncycles = ncycles > totalcycles ? ncycles - totalcycles : 0;
	totalcycles += ncycles;
	ret = aपंचांगel_smc_cs_conf_set_setup(smcconf, ATMEL_SMC_NWE_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/*
	 * As क्रम the ग_लिखो setup timing, the ग_लिखो hold timing depends on the
	 * operation करोne on the न_अंकD:
	 *
	 * NWE_HOLD = max(tCLH, tCH, tALH, tDH, tWH)
	 */
	समयps = max3(conf->timings.sdr.tCLH_min, conf->timings.sdr.tCH_min,
		      conf->timings.sdr.tALH_min);
	समयps = max3(समयps, conf->timings.sdr.tDH_min,
		      conf->timings.sdr.tWH_min);
	ncycles = DIV_ROUND_UP(समयps, mckperiodps);
	totalcycles += ncycles;

	/*
	 * The ग_लिखो cycle timing is directly matching tWC, but is also
	 * dependent on the other timings on the setup and hold timings we
	 * calculated earlier, which gives:
	 *
	 * NWE_CYCLE = max(tWC, NWE_SETUP + NWE_PULSE + NWE_HOLD)
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tWC_min, mckperiodps);
	ncycles = max(totalcycles, ncycles);
	ret = aपंचांगel_smc_cs_conf_set_cycle(smcconf, ATMEL_SMC_NWE_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/*
	 * We करोn't want the CS line to be toggled between each byte/word
	 * transfer to the न_अंकD. The only way to guarantee that is to have the
	 * NCS_अणुWR,RDपूर्ण_अणुSETUP,HOLDपूर्ण timings set to 0, which in turn means:
	 *
	 * NCS_WR_PULSE = NWE_CYCLE
	 */
	ret = aपंचांगel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NCS_WR_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/*
	 * As क्रम the ग_लिखो setup timing, the पढ़ो hold timing depends on the
	 * operation करोne on the न_अंकD:
	 *
	 * NRD_HOLD = max(tREH, tRHOH)
	 */
	समयps = max(conf->timings.sdr.tREH_min, conf->timings.sdr.tRHOH_min);
	ncycles = DIV_ROUND_UP(समयps, mckperiodps);
	totalcycles = ncycles;

	/*
	 * TDF = tRHZ - NRD_HOLD
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRHZ_max, mckperiodps);
	ncycles -= totalcycles;

	/*
	 * In ONFI 4.0 specs, tRHZ has been increased to support EDO न_अंकDs and
	 * we might end up with a config that करोes not fit in the TDF field.
	 * Just take the max value in this हाल and hope that the न_अंकD is more
	 * tolerant than advertised.
	 */
	अगर (ncycles > ATMEL_SMC_MODE_TDF_MAX)
		ncycles = ATMEL_SMC_MODE_TDF_MAX;
	अन्यथा अगर (ncycles < ATMEL_SMC_MODE_TDF_MIN)
		ncycles = ATMEL_SMC_MODE_TDF_MIN;

	smcconf->mode |= ATMEL_SMC_MODE_TDF(ncycles) |
			 ATMEL_SMC_MODE_TDFMODE_OPTIMIZED;

	/*
	 * Read pulse timing directly matches tRP:
	 *
	 * NRD_PULSE = tRP
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRP_min, mckperiodps);
	totalcycles += ncycles;
	ret = aपंचांगel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NRD_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/*
	 * The ग_लिखो cycle timing is directly matching tWC, but is also
	 * dependent on the setup and hold timings we calculated earlier,
	 * which gives:
	 *
	 * NRD_CYCLE = max(tRC, NRD_PULSE + NRD_HOLD)
	 *
	 * NRD_SETUP is always 0.
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRC_min, mckperiodps);
	ncycles = max(totalcycles, ncycles);
	ret = aपंचांगel_smc_cs_conf_set_cycle(smcconf, ATMEL_SMC_NRD_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/*
	 * We करोn't want the CS line to be toggled between each byte/word
	 * transfer from the न_अंकD. The only way to guarantee that is to have
	 * the NCS_अणुWR,RDपूर्ण_अणुSETUP,HOLDपूर्ण timings set to 0, which in turn means:
	 *
	 * NCS_RD_PULSE = NRD_CYCLE
	 */
	ret = aपंचांगel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NCS_RD_SHIFT,
					  ncycles);
	अगर (ret)
		वापस ret;

	/* Txxx timings are directly matching tXXX ones. */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tCLR_min, mckperiodps);
	ret = aपंचांगel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TCLR_SHIFT,
					   ncycles);
	अगर (ret)
		वापस ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tADL_min, mckperiodps);
	ret = aपंचांगel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TADL_SHIFT,
					   ncycles);
	/*
	 * Version 4 of the ONFI spec mandates that tADL be at least 400
	 * nanoseconds, but, depending on the master घड़ी rate, 400 ns may not
	 * fit in the tADL field of the SMC reg. We need to relax the check and
	 * accept the -दुस्फल वापस code.
	 *
	 * Note that previous versions of the ONFI spec had a lower tADL_min
	 * (100 or 200 ns). It's not clear why this timing स्थिरraपूर्णांक got
	 * increased but it seems most न_अंकDs are fine with values lower than
	 * 400ns, so we should be safe.
	 */
	अगर (ret && ret != -दुस्फल)
		वापस ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tAR_min, mckperiodps);
	ret = aपंचांगel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TAR_SHIFT,
					   ncycles);
	अगर (ret)
		वापस ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRR_min, mckperiodps);
	ret = aपंचांगel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TRR_SHIFT,
					   ncycles);
	अगर (ret)
		वापस ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tWB_max, mckperiodps);
	ret = aपंचांगel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TWB_SHIFT,
					   ncycles);
	अगर (ret)
		वापस ret;

	/* Attach the CS line to the NFC logic. */
	smcconf->timings |= ATMEL_HSMC_TIMINGS_NFSEL;

	/* Set the appropriate data bus width. */
	अगर (nand->base.options & न_अंकD_BUSWIDTH_16)
		smcconf->mode |= ATMEL_SMC_MODE_DBW_16;

	/* Operate in NRD/NWE READ/WRITEMODE. */
	smcconf->mode |= ATMEL_SMC_MODE_READMODE_NRD |
			 ATMEL_SMC_MODE_WRITEMODE_NWE;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_smc_nand_setup_पूर्णांकerface(काष्ठा aपंचांगel_nand *nand,
					पूर्णांक csline,
					स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा aपंचांगel_nand_controller *nc;
	काष्ठा aपंचांगel_smc_cs_conf smcconf;
	काष्ठा aपंचांगel_nand_cs *cs;
	पूर्णांक ret;

	nc = to_nand_controller(nand->base.controller);

	ret = aपंचांगel_smc_nand_prepare_smcconf(nand, conf, &smcconf);
	अगर (ret)
		वापस ret;

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	cs = &nand->cs[csline];
	cs->smcconf = smcconf;
	aपंचांगel_smc_cs_conf_apply(nc->smc, cs->id, &cs->smcconf);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_setup_पूर्णांकerface(काष्ठा aपंचांगel_nand *nand,
					पूर्णांक csline,
					स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	काष्ठा aपंचांगel_smc_cs_conf smcconf;
	काष्ठा aपंचांगel_nand_cs *cs;
	पूर्णांक ret;

	nc = to_hsmc_nand_controller(nand->base.controller);

	ret = aपंचांगel_smc_nand_prepare_smcconf(nand, conf, &smcconf);
	अगर (ret)
		वापस ret;

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	cs = &nand->cs[csline];
	cs->smcconf = smcconf;

	अगर (cs->rb.type == ATMEL_न_अंकD_NATIVE_RB)
		cs->smcconf.timings |= ATMEL_HSMC_TIMINGS_RBNSEL(cs->rb.id);

	aपंचांगel_hsmc_cs_conf_apply(nc->base.smc, nc->hsmc_layout, cs->id,
				 &cs->smcconf);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_nand_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक csline,
				      स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_nand_controller *nc;

	nc = to_nand_controller(nand->base.controller);

	अगर (csline >= nand->numcs ||
	    (csline < 0 && csline != न_अंकD_DATA_IFACE_CHECK_ONLY))
		वापस -EINVAL;

	वापस nc->caps->ops->setup_पूर्णांकerface(nand, csline, conf);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_exec_op(काष्ठा nand_chip *chip,
			      स्थिर काष्ठा nand_operation *op,
			      bool check_only)
अणु
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा aपंचांगel_nand_controller *nc;

	nc = to_nand_controller(nand->base.controller);

	वापस nc->caps->ops->exec_op(nand, op, check_only);
पूर्ण

अटल व्योम aपंचांगel_nand_init(काष्ठा aपंचांगel_nand_controller *nc,
			    काष्ठा aपंचांगel_nand *nand)
अणु
	काष्ठा nand_chip *chip = &nand->base;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	mtd->dev.parent = nc->dev;
	nand->base.controller = &nc->base;

	अगर (!nc->mck || !nc->caps->ops->setup_पूर्णांकerface)
		chip->options |= न_अंकD_KEEP_TIMINGS;

	/*
	 * Use a bounce buffer when the buffer passed by the MTD user is not
	 * suitable क्रम DMA.
	 */
	अगर (nc->dmac)
		chip->options |= न_अंकD_USES_DMA;

	/* Default to HW ECC अगर pmecc is available. */
	अगर (nc->pmecc)
		chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
पूर्ण

अटल व्योम aपंचांगel_smc_nand_init(काष्ठा aपंचांगel_nand_controller *nc,
				काष्ठा aपंचांगel_nand *nand)
अणु
	काष्ठा nand_chip *chip = &nand->base;
	काष्ठा aपंचांगel_smc_nand_controller *smc_nc;
	पूर्णांक i;

	aपंचांगel_nand_init(nc, nand);

	smc_nc = to_smc_nand_controller(chip->controller);
	अगर (!smc_nc->ebi_csa_regmap)
		वापस;

	/* Attach the CS to the न_अंकD Flash logic. */
	क्रम (i = 0; i < nand->numcs; i++)
		regmap_update_bits(smc_nc->ebi_csa_regmap,
				   smc_nc->ebi_csa->offs,
				   BIT(nand->cs[i].id), BIT(nand->cs[i].id));

	अगर (smc_nc->ebi_csa->nfd0_on_d16)
		regmap_update_bits(smc_nc->ebi_csa_regmap,
				   smc_nc->ebi_csa->offs,
				   smc_nc->ebi_csa->nfd0_on_d16,
				   smc_nc->ebi_csa->nfd0_on_d16);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_controller_हटाओ_nand(काष्ठा aपंचांगel_nand *nand)
अणु
	काष्ठा nand_chip *chip = &nand->base;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(mtd);
	अगर (ret)
		वापस ret;

	nand_cleanup(chip);
	list_del(&nand->node);

	वापस 0;
पूर्ण

अटल काष्ठा aपंचांगel_nand *aपंचांगel_nand_create(काष्ठा aपंचांगel_nand_controller *nc,
					    काष्ठा device_node *np,
					    पूर्णांक reg_cells)
अणु
	काष्ठा aपंचांगel_nand *nand;
	काष्ठा gpio_desc *gpio;
	पूर्णांक numcs, ret, i;

	numcs = of_property_count_elems_of_size(np, "reg",
						reg_cells * माप(u32));
	अगर (numcs < 1) अणु
		dev_err(nc->dev, "Missing or invalid reg property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	nand = devm_kzalloc(nc->dev, काष्ठा_size(nand, cs, numcs), GFP_KERNEL);
	अगर (!nand) अणु
		dev_err(nc->dev, "Failed to allocate NAND object\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	nand->numcs = numcs;

	gpio = devm_fwnode_gpiod_get(nc->dev, of_fwnode_handle(np),
				     "det", GPIOD_IN, "nand-det");
	अगर (IS_ERR(gpio) && PTR_ERR(gpio) != -ENOENT) अणु
		dev_err(nc->dev,
			"Failed to get detect gpio (err = %ld)\n",
			PTR_ERR(gpio));
		वापस ERR_CAST(gpio);
	पूर्ण

	अगर (!IS_ERR(gpio))
		nand->cdgpio = gpio;

	क्रम (i = 0; i < numcs; i++) अणु
		काष्ठा resource res;
		u32 val;

		ret = of_address_to_resource(np, 0, &res);
		अगर (ret) अणु
			dev_err(nc->dev, "Invalid reg property (err = %d)\n",
				ret);
			वापस ERR_PTR(ret);
		पूर्ण

		ret = of_property_पढ़ो_u32_index(np, "reg", i * reg_cells,
						 &val);
		अगर (ret) अणु
			dev_err(nc->dev, "Invalid reg property (err = %d)\n",
				ret);
			वापस ERR_PTR(ret);
		पूर्ण

		nand->cs[i].id = val;

		nand->cs[i].io.dma = res.start;
		nand->cs[i].io.virt = devm_ioremap_resource(nc->dev, &res);
		अगर (IS_ERR(nand->cs[i].io.virt))
			वापस ERR_CAST(nand->cs[i].io.virt);

		अगर (!of_property_पढ़ो_u32(np, "atmel,rb", &val)) अणु
			अगर (val > ATMEL_NFC_MAX_RB_ID)
				वापस ERR_PTR(-EINVAL);

			nand->cs[i].rb.type = ATMEL_न_अंकD_NATIVE_RB;
			nand->cs[i].rb.id = val;
		पूर्ण अन्यथा अणु
			gpio = devm_fwnode_gpiod_get_index(nc->dev,
							   of_fwnode_handle(np),
							   "rb", i, GPIOD_IN,
							   "nand-rb");
			अगर (IS_ERR(gpio) && PTR_ERR(gpio) != -ENOENT) अणु
				dev_err(nc->dev,
					"Failed to get R/B gpio (err = %ld)\n",
					PTR_ERR(gpio));
				वापस ERR_CAST(gpio);
			पूर्ण

			अगर (!IS_ERR(gpio)) अणु
				nand->cs[i].rb.type = ATMEL_न_अंकD_GPIO_RB;
				nand->cs[i].rb.gpio = gpio;
			पूर्ण
		पूर्ण

		gpio = devm_fwnode_gpiod_get_index(nc->dev,
						   of_fwnode_handle(np),
						   "cs", i, GPIOD_OUT_HIGH,
						   "nand-cs");
		अगर (IS_ERR(gpio) && PTR_ERR(gpio) != -ENOENT) अणु
			dev_err(nc->dev,
				"Failed to get CS gpio (err = %ld)\n",
				PTR_ERR(gpio));
			वापस ERR_CAST(gpio);
		पूर्ण

		अगर (!IS_ERR(gpio))
			nand->cs[i].csgpio = gpio;
	पूर्ण

	nand_set_flash_node(&nand->base, np);

	वापस nand;
पूर्ण

अटल पूर्णांक
aपंचांगel_nand_controller_add_nand(काष्ठा aपंचांगel_nand_controller *nc,
			       काष्ठा aपंचांगel_nand *nand)
अणु
	काष्ठा nand_chip *chip = &nand->base;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	/* No card inserted, skip this न_अंकD. */
	अगर (nand->cdgpio && gpiod_get_value(nand->cdgpio)) अणु
		dev_info(nc->dev, "No SmartMedia card inserted.\n");
		वापस 0;
	पूर्ण

	nc->caps->ops->nand_init(nc, nand);

	ret = nand_scan(chip, nand->numcs);
	अगर (ret) अणु
		dev_err(nc->dev, "NAND scan failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(nc->dev, "Failed to register mtd device: %d\n", ret);
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	list_add_tail(&nand->node, &nc->chips);

	वापस 0;
पूर्ण

अटल पूर्णांक
aपंचांगel_nand_controller_हटाओ_nands(काष्ठा aपंचांगel_nand_controller *nc)
अणु
	काष्ठा aपंचांगel_nand *nand, *पंचांगp;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(nand, पंचांगp, &nc->chips, node) अणु
		ret = aपंचांगel_nand_controller_हटाओ_nand(nand);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
aपंचांगel_nand_controller_legacy_add_nands(काष्ठा aपंचांगel_nand_controller *nc)
अणु
	काष्ठा device *dev = nc->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा aपंचांगel_nand *nand;
	काष्ठा gpio_desc *gpio;
	काष्ठा resource *res;

	/*
	 * Legacy bindings only allow connecting a single न_अंकD with a unique CS
	 * line to the controller.
	 */
	nand = devm_kzalloc(nc->dev, माप(*nand) + माप(*nand->cs),
			    GFP_KERNEL);
	अगर (!nand)
		वापस -ENOMEM;

	nand->numcs = 1;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nand->cs[0].io.virt = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(nand->cs[0].io.virt))
		वापस PTR_ERR(nand->cs[0].io.virt);

	nand->cs[0].io.dma = res->start;

	/*
	 * The old driver was hardcoding the CS id to 3 क्रम all sama5
	 * controllers. Since this id is only meaningful क्रम the sama5
	 * controller we can safely assign this id to 3 no matter the
	 * controller.
	 * If one wants to connect a न_अंकD to a dअगरferent CS line, he will
	 * have to use the new bindings.
	 */
	nand->cs[0].id = 3;

	/* R/B GPIO. */
	gpio = devm_gpiod_get_index_optional(dev, शून्य, 0,  GPIOD_IN);
	अगर (IS_ERR(gpio)) अणु
		dev_err(dev, "Failed to get R/B gpio (err = %ld)\n",
			PTR_ERR(gpio));
		वापस PTR_ERR(gpio);
	पूर्ण

	अगर (gpio) अणु
		nand->cs[0].rb.type = ATMEL_न_अंकD_GPIO_RB;
		nand->cs[0].rb.gpio = gpio;
	पूर्ण

	/* CS GPIO. */
	gpio = devm_gpiod_get_index_optional(dev, शून्य, 1, GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpio)) अणु
		dev_err(dev, "Failed to get CS gpio (err = %ld)\n",
			PTR_ERR(gpio));
		वापस PTR_ERR(gpio);
	पूर्ण

	nand->cs[0].csgpio = gpio;

	/* Card detect GPIO. */
	gpio = devm_gpiod_get_index_optional(nc->dev, शून्य, 2, GPIOD_IN);
	अगर (IS_ERR(gpio)) अणु
		dev_err(dev,
			"Failed to get detect gpio (err = %ld)\n",
			PTR_ERR(gpio));
		वापस PTR_ERR(gpio);
	पूर्ण

	nand->cdgpio = gpio;

	nand_set_flash_node(&nand->base, nc->dev->of_node);

	वापस aपंचांगel_nand_controller_add_nand(nc, nand);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_controller_add_nands(काष्ठा aपंचांगel_nand_controller *nc)
अणु
	काष्ठा device_node *np, *nand_np;
	काष्ठा device *dev = nc->dev;
	पूर्णांक ret, reg_cells;
	u32 val;

	/* We करो not retrieve the SMC syscon when parsing old DTs. */
	अगर (nc->caps->legacy_of_bindings)
		वापस aपंचांगel_nand_controller_legacy_add_nands(nc);

	np = dev->of_node;

	ret = of_property_पढ़ो_u32(np, "#address-cells", &val);
	अगर (ret) अणु
		dev_err(dev, "missing #address-cells property\n");
		वापस ret;
	पूर्ण

	reg_cells = val;

	ret = of_property_पढ़ो_u32(np, "#size-cells", &val);
	अगर (ret) अणु
		dev_err(dev, "missing #size-cells property\n");
		वापस ret;
	पूर्ण

	reg_cells += val;

	क्रम_each_child_of_node(np, nand_np) अणु
		काष्ठा aपंचांगel_nand *nand;

		nand = aपंचांगel_nand_create(nc, nand_np, reg_cells);
		अगर (IS_ERR(nand)) अणु
			ret = PTR_ERR(nand);
			जाओ err;
		पूर्ण

		ret = aपंचांगel_nand_controller_add_nand(nc, nand);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	aपंचांगel_nand_controller_हटाओ_nands(nc);

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_nand_controller_cleanup(काष्ठा aपंचांगel_nand_controller *nc)
अणु
	अगर (nc->dmac)
		dma_release_channel(nc->dmac);

	clk_put(nc->mck);
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9260_ebi_csa = अणु
	.offs = AT91SAM9260_MATRIX_EBICSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9261_ebi_csa = अणु
	.offs = AT91SAM9261_MATRIX_EBICSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9263_ebi_csa = अणु
	.offs = AT91SAM9263_MATRIX_EBI0CSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9rl_ebi_csa = अणु
	.offs = AT91SAM9RL_MATRIX_EBICSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9g45_ebi_csa = अणु
	.offs = AT91SAM9G45_MATRIX_EBICSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9n12_ebi_csa = अणु
	.offs = AT91SAM9N12_MATRIX_EBICSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg at91sam9x5_ebi_csa = अणु
	.offs = AT91SAM9X5_MATRIX_EBICSA,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg sam9x60_ebi_csa = अणु
	.offs = AT91_SFR_CCFG_EBICSA,
	.nfd0_on_d16 = AT91_SFR_CCFG_NFD0_ON_D16,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_ebi_csa_regmap_of_ids[] = अणु
	अणु
		.compatible = "atmel,at91sam9260-matrix",
		.data = &at91sam9260_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9261-matrix",
		.data = &at91sam9261_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9263-matrix",
		.data = &at91sam9263_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9rl-matrix",
		.data = &at91sam9rl_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9g45-matrix",
		.data = &at91sam9g45_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9n12-matrix",
		.data = &at91sam9n12_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9x5-matrix",
		.data = &at91sam9x5_ebi_csa,
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-sfr",
		.data = &sam9x60_ebi_csa,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक aपंचांगel_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा aपंचांगel_nand_controller *nc = to_nand_controller(chip->controller);
	काष्ठा aपंचांगel_nand *nand = to_aपंचांगel_nand(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = nc->caps->ops->ecc_init(chip);
	अगर (ret)
		वापस ret;

	अगर (nc->caps->legacy_of_bindings || !nc->dev->of_node) अणु
		/*
		 * We keep the MTD name unchanged to aव्योम अवरोधing platक्रमms
		 * where the MTD cmdline parser is used and the bootloader
		 * has not been updated to use the new naming scheme.
		 */
		mtd->name = "atmel_nand";
	पूर्ण अन्यथा अगर (!mtd->name) अणु
		/*
		 * If the new bindings are used and the bootloader has not been
		 * updated to pass a new mtdparts parameter on the cmdline, you
		 * should define the following property in your nand node:
		 *
		 *	label = "atmel_nand";
		 *
		 * This way, mtd->name will be set by the core when
		 * nand_set_flash_node() is called.
		 */
		mtd->name = devm_kaप्र_लिखो(nc->dev, GFP_KERNEL,
					   "%s:nand.%d", dev_name(nc->dev),
					   nand->cs[0].id);
		अगर (!mtd->name) अणु
			dev_err(nc->dev, "Failed to allocate mtd->name\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops aपंचांगel_nand_controller_ops = अणु
	.attach_chip = aपंचांगel_nand_attach_chip,
	.setup_पूर्णांकerface = aपंचांगel_nand_setup_पूर्णांकerface,
	.exec_op = aपंचांगel_nand_exec_op,
पूर्ण;

अटल पूर्णांक aपंचांगel_nand_controller_init(काष्ठा aपंचांगel_nand_controller *nc,
				काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा aपंचांगel_nand_controller_caps *caps)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	nand_controller_init(&nc->base);
	nc->base.ops = &aपंचांगel_nand_controller_ops;
	INIT_LIST_HEAD(&nc->chips);
	nc->dev = dev;
	nc->caps = caps;

	platक्रमm_set_drvdata(pdev, nc);

	nc->pmecc = devm_aपंचांगel_pmecc_get(dev);
	अगर (IS_ERR(nc->pmecc))
		वापस dev_err_probe(dev, PTR_ERR(nc->pmecc),
				     "Could not get PMECC object\n");

	अगर (nc->caps->has_dma && !aपंचांगel_nand_aव्योम_dma) अणु
		dma_cap_mask_t mask;

		dma_cap_zero(mask);
		dma_cap_set(DMA_MEMCPY, mask);

		nc->dmac = dma_request_channel(mask, शून्य, शून्य);
		अगर (!nc->dmac)
			dev_err(nc->dev, "Failed to request DMA channel\n");
	पूर्ण

	/* We करो not retrieve the SMC syscon when parsing old DTs. */
	अगर (nc->caps->legacy_of_bindings)
		वापस 0;

	nc->mck = of_clk_get(dev->parent->of_node, 0);
	अगर (IS_ERR(nc->mck)) अणु
		dev_err(dev, "Failed to retrieve MCK clk\n");
		वापस PTR_ERR(nc->mck);
	पूर्ण

	np = of_parse_phandle(dev->parent->of_node, "atmel,smc", 0);
	अगर (!np) अणु
		dev_err(dev, "Missing or invalid atmel,smc property\n");
		वापस -EINVAL;
	पूर्ण

	nc->smc = syscon_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(nc->smc)) अणु
		ret = PTR_ERR(nc->smc);
		dev_err(dev, "Could not get SMC regmap (err = %d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
aपंचांगel_smc_nand_controller_init(काष्ठा aपंचांगel_smc_nand_controller *nc)
अणु
	काष्ठा device *dev = nc->base.dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	पूर्णांक ret;

	/* We करो not retrieve the EBICSA regmap when parsing old DTs. */
	अगर (nc->base.caps->legacy_of_bindings)
		वापस 0;

	np = of_parse_phandle(dev->parent->of_node,
			      nc->base.caps->ebi_csa_regmap_name, 0);
	अगर (!np)
		वापस 0;

	match = of_match_node(aपंचांगel_ebi_csa_regmap_of_ids, np);
	अगर (!match) अणु
		of_node_put(np);
		वापस 0;
	पूर्ण

	nc->ebi_csa_regmap = syscon_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(nc->ebi_csa_regmap)) अणु
		ret = PTR_ERR(nc->ebi_csa_regmap);
		dev_err(dev, "Could not get EBICSA regmap (err = %d)\n", ret);
		वापस ret;
	पूर्ण

	nc->ebi_csa = (काष्ठा aपंचांगel_smc_nand_ebi_csa_cfg *)match->data;

	/*
	 * The at91sam9263 has 2 EBIs, अगर the न_अंकD controller is under EBI1
	 * add 4 to ->ebi_csa->offs.
	 */
	अगर (of_device_is_compatible(dev->parent->of_node,
				    "atmel,at91sam9263-ebi1"))
		nc->ebi_csa->offs += 4;

	वापस 0;
पूर्ण

अटल पूर्णांक
aपंचांगel_hsmc_nand_controller_legacy_init(काष्ठा aपंचांगel_hsmc_nand_controller *nc)
अणु
	काष्ठा regmap_config regmap_conf = अणु
		.reg_bits = 32,
		.val_bits = 32,
		.reg_stride = 4,
	पूर्ण;

	काष्ठा device *dev = nc->base.dev;
	काष्ठा device_node *nand_np, *nfc_np;
	व्योम __iomem *iomem;
	काष्ठा resource res;
	पूर्णांक ret;

	nand_np = dev->of_node;
	nfc_np = of_get_compatible_child(dev->of_node, "atmel,sama5d3-nfc");
	अगर (!nfc_np) अणु
		dev_err(dev, "Could not find device node for sama5d3-nfc\n");
		वापस -ENODEV;
	पूर्ण

	nc->clk = of_clk_get(nfc_np, 0);
	अगर (IS_ERR(nc->clk)) अणु
		ret = PTR_ERR(nc->clk);
		dev_err(dev, "Failed to retrieve HSMC clock (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(nc->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable the HSMC clock (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	nc->irq = of_irq_get(nand_np, 0);
	अगर (nc->irq <= 0) अणु
		ret = nc->irq ?: -ENXIO;
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get IRQ number (err = %d)\n",
				ret);
		जाओ out;
	पूर्ण

	ret = of_address_to_resource(nfc_np, 0, &res);
	अगर (ret) अणु
		dev_err(dev, "Invalid or missing NFC IO resource (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	iomem = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(iomem)) अणु
		ret = PTR_ERR(iomem);
		जाओ out;
	पूर्ण

	regmap_conf.name = "nfc-io";
	regmap_conf.max_रेजिस्टर = resource_size(&res) - 4;
	nc->io = devm_regmap_init_mmio(dev, iomem, &regmap_conf);
	अगर (IS_ERR(nc->io)) अणु
		ret = PTR_ERR(nc->io);
		dev_err(dev, "Could not create NFC IO regmap (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	ret = of_address_to_resource(nfc_np, 1, &res);
	अगर (ret) अणु
		dev_err(dev, "Invalid or missing HSMC resource (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	iomem = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(iomem)) अणु
		ret = PTR_ERR(iomem);
		जाओ out;
	पूर्ण

	regmap_conf.name = "smc";
	regmap_conf.max_रेजिस्टर = resource_size(&res) - 4;
	nc->base.smc = devm_regmap_init_mmio(dev, iomem, &regmap_conf);
	अगर (IS_ERR(nc->base.smc)) अणु
		ret = PTR_ERR(nc->base.smc);
		dev_err(dev, "Could not create NFC IO regmap (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	ret = of_address_to_resource(nfc_np, 2, &res);
	अगर (ret) अणु
		dev_err(dev, "Invalid or missing SRAM resource (err = %d)\n",
			ret);
		जाओ out;
	पूर्ण

	nc->sram.virt = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(nc->sram.virt)) अणु
		ret = PTR_ERR(nc->sram.virt);
		जाओ out;
	पूर्ण

	nc->sram.dma = res.start;

out:
	of_node_put(nfc_np);

	वापस ret;
पूर्ण

अटल पूर्णांक
aपंचांगel_hsmc_nand_controller_init(काष्ठा aपंचांगel_hsmc_nand_controller *nc)
अणु
	काष्ठा device *dev = nc->base.dev;
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_parse_phandle(dev->parent->of_node, "atmel,smc", 0);
	अगर (!np) अणु
		dev_err(dev, "Missing or invalid atmel,smc property\n");
		वापस -EINVAL;
	पूर्ण

	nc->hsmc_layout = aपंचांगel_hsmc_get_reg_layout(np);

	nc->irq = of_irq_get(np, 0);
	of_node_put(np);
	अगर (nc->irq <= 0) अणु
		ret = nc->irq ?: -ENXIO;
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get IRQ number (err = %d)\n",
				ret);
		वापस ret;
	पूर्ण

	np = of_parse_phandle(dev->of_node, "atmel,nfc-io", 0);
	अगर (!np) अणु
		dev_err(dev, "Missing or invalid atmel,nfc-io property\n");
		वापस -EINVAL;
	पूर्ण

	nc->io = syscon_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(nc->io)) अणु
		ret = PTR_ERR(nc->io);
		dev_err(dev, "Could not get NFC IO regmap (err = %d)\n", ret);
		वापस ret;
	पूर्ण

	nc->sram.pool = of_gen_pool_get(nc->base.dev->of_node,
					 "atmel,nfc-sram", 0);
	अगर (!nc->sram.pool) अणु
		dev_err(nc->base.dev, "Missing SRAM\n");
		वापस -ENOMEM;
	पूर्ण

	nc->sram.virt = (व्योम __iomem *)gen_pool_dma_alloc(nc->sram.pool,
							   ATMEL_NFC_SRAM_SIZE,
							   &nc->sram.dma);
	अगर (!nc->sram.virt) अणु
		dev_err(nc->base.dev,
			"Could not allocate memory from the NFC SRAM pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
aपंचांगel_hsmc_nand_controller_हटाओ(काष्ठा aपंचांगel_nand_controller *nc)
अणु
	काष्ठा aपंचांगel_hsmc_nand_controller *hsmc_nc;
	पूर्णांक ret;

	ret = aपंचांगel_nand_controller_हटाओ_nands(nc);
	अगर (ret)
		वापस ret;

	hsmc_nc = container_of(nc, काष्ठा aपंचांगel_hsmc_nand_controller, base);
	regmap_ग_लिखो(hsmc_nc->base.smc, ATMEL_HSMC_NFC_CTRL,
		     ATMEL_HSMC_NFC_CTRL_DIS);

	अगर (hsmc_nc->sram.pool)
		gen_pool_मुक्त(hsmc_nc->sram.pool,
			      (अचिन्हित दीर्घ)hsmc_nc->sram.virt,
			      ATMEL_NFC_SRAM_SIZE);

	अगर (hsmc_nc->clk) अणु
		clk_disable_unprepare(hsmc_nc->clk);
		clk_put(hsmc_nc->clk);
	पूर्ण

	aपंचांगel_nand_controller_cleanup(nc);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hsmc_nand_controller_probe(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा aपंचांगel_nand_controller_caps *caps)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_hsmc_nand_controller *nc;
	पूर्णांक ret;

	nc = devm_kzalloc(dev, माप(*nc), GFP_KERNEL);
	अगर (!nc)
		वापस -ENOMEM;

	ret = aपंचांगel_nand_controller_init(&nc->base, pdev, caps);
	अगर (ret)
		वापस ret;

	अगर (caps->legacy_of_bindings)
		ret = aपंचांगel_hsmc_nand_controller_legacy_init(nc);
	अन्यथा
		ret = aपंचांगel_hsmc_nand_controller_init(nc);

	अगर (ret)
		वापस ret;

	/* Make sure all irqs are masked beक्रमe रेजिस्टरing our IRQ handler. */
	regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_IDR, 0xffffffff);
	ret = devm_request_irq(dev, nc->irq, aपंचांगel_nfc_पूर्णांकerrupt,
			       IRQF_SHARED, "nfc", nc);
	अगर (ret) अणु
		dev_err(dev,
			"Could not get register NFC interrupt handler (err = %d)\n",
			ret);
		जाओ err;
	पूर्ण

	/* Initial NFC configuration. */
	regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_CFG,
		     ATMEL_HSMC_NFC_CFG_DTO_MAX);
	regmap_ग_लिखो(nc->base.smc, ATMEL_HSMC_NFC_CTRL,
		     ATMEL_HSMC_NFC_CTRL_EN);

	ret = aपंचांगel_nand_controller_add_nands(&nc->base);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	aपंचांगel_hsmc_nand_controller_हटाओ(&nc->base);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_nand_controller_ops aपंचांगel_hsmc_nc_ops = अणु
	.probe = aपंचांगel_hsmc_nand_controller_probe,
	.हटाओ = aपंचांगel_hsmc_nand_controller_हटाओ,
	.ecc_init = aपंचांगel_hsmc_nand_ecc_init,
	.nand_init = aपंचांगel_nand_init,
	.setup_पूर्णांकerface = aपंचांगel_hsmc_nand_setup_पूर्णांकerface,
	.exec_op = aपंचांगel_hsmc_nand_exec_op,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sama5_nc_caps = अणु
	.has_dma = true,
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ops = &aपंचांगel_hsmc_nc_ops,
पूर्ण;

/* Only used to parse old bindings. */
अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sama5_nand_caps = अणु
	.has_dma = true,
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ops = &aपंचांगel_hsmc_nc_ops,
	.legacy_of_bindings = true,
पूर्ण;

अटल पूर्णांक aपंचांगel_smc_nand_controller_probe(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा aपंचांगel_nand_controller_caps *caps)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_smc_nand_controller *nc;
	पूर्णांक ret;

	nc = devm_kzalloc(dev, माप(*nc), GFP_KERNEL);
	अगर (!nc)
		वापस -ENOMEM;

	ret = aपंचांगel_nand_controller_init(&nc->base, pdev, caps);
	अगर (ret)
		वापस ret;

	ret = aपंचांगel_smc_nand_controller_init(nc);
	अगर (ret)
		वापस ret;

	वापस aपंचांगel_nand_controller_add_nands(&nc->base);
पूर्ण

अटल पूर्णांक
aपंचांगel_smc_nand_controller_हटाओ(काष्ठा aपंचांगel_nand_controller *nc)
अणु
	पूर्णांक ret;

	ret = aपंचांगel_nand_controller_हटाओ_nands(nc);
	अगर (ret)
		वापस ret;

	aपंचांगel_nand_controller_cleanup(nc);

	वापस 0;
पूर्ण

/*
 * The SMC reg layout of at91rm9200 is completely dअगरferent which prevents us
 * from re-using aपंचांगel_smc_nand_setup_पूर्णांकerface() क्रम the
 * ->setup_पूर्णांकerface() hook.
 * At this poपूर्णांक, there's no support क्रम the at91rm9200 SMC IP, so we leave
 * ->setup_पूर्णांकerface() unasचिन्हित.
 */
अटल स्थिर काष्ठा aपंचांगel_nand_controller_ops at91rm9200_nc_ops = अणु
	.probe = aपंचांगel_smc_nand_controller_probe,
	.हटाओ = aपंचांगel_smc_nand_controller_हटाओ,
	.ecc_init = aपंचांगel_nand_ecc_init,
	.nand_init = aपंचांगel_smc_nand_init,
	.exec_op = aपंचांगel_smc_nand_exec_op,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_rm9200_nc_caps = अणु
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ebi_csa_regmap_name = "atmel,matrix",
	.ops = &at91rm9200_nc_ops,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_ops aपंचांगel_smc_nc_ops = अणु
	.probe = aपंचांगel_smc_nand_controller_probe,
	.हटाओ = aपंचांगel_smc_nand_controller_हटाओ,
	.ecc_init = aपंचांगel_nand_ecc_init,
	.nand_init = aपंचांगel_smc_nand_init,
	.setup_पूर्णांकerface = aपंचांगel_smc_nand_setup_पूर्णांकerface,
	.exec_op = aपंचांगel_smc_nand_exec_op,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sam9260_nc_caps = अणु
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ebi_csa_regmap_name = "atmel,matrix",
	.ops = &aपंचांगel_smc_nc_ops,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sam9261_nc_caps = अणु
	.ale_offs = BIT(22),
	.cle_offs = BIT(21),
	.ebi_csa_regmap_name = "atmel,matrix",
	.ops = &aपंचांगel_smc_nc_ops,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sam9g45_nc_caps = अणु
	.has_dma = true,
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ebi_csa_regmap_name = "atmel,matrix",
	.ops = &aपंचांगel_smc_nc_ops,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps microchip_sam9x60_nc_caps = अणु
	.has_dma = true,
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ebi_csa_regmap_name = "microchip,sfr",
	.ops = &aपंचांगel_smc_nc_ops,
पूर्ण;

/* Only used to parse old bindings. */
अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_rm9200_nand_caps = अणु
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ops = &aपंचांगel_smc_nc_ops,
	.legacy_of_bindings = true,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sam9261_nand_caps = अणु
	.ale_offs = BIT(22),
	.cle_offs = BIT(21),
	.ops = &aपंचांगel_smc_nc_ops,
	.legacy_of_bindings = true,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_nand_controller_caps aपंचांगel_sam9g45_nand_caps = अणु
	.has_dma = true,
	.ale_offs = BIT(21),
	.cle_offs = BIT(22),
	.ops = &aपंचांगel_smc_nc_ops,
	.legacy_of_bindings = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_nand_controller_of_ids[] = अणु
	अणु
		.compatible = "atmel,at91rm9200-nand-controller",
		.data = &aपंचांगel_rm9200_nc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9260-nand-controller",
		.data = &aपंचांगel_sam9260_nc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9261-nand-controller",
		.data = &aपंचांगel_sam9261_nc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9g45-nand-controller",
		.data = &aपंचांगel_sam9g45_nc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d3-nand-controller",
		.data = &aपंचांगel_sama5_nc_caps,
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-nand-controller",
		.data = &microchip_sam9x60_nc_caps,
	पूर्ण,
	/* Support क्रम old/deprecated bindings: */
	अणु
		.compatible = "atmel,at91rm9200-nand",
		.data = &aपंचांगel_rm9200_nand_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d4-nand",
		.data = &aपंचांगel_rm9200_nand_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d2-nand",
		.data = &aपंचांगel_rm9200_nand_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_nand_controller_of_ids);

अटल पूर्णांक aपंचांगel_nand_controller_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा aपंचांगel_nand_controller_caps *caps;

	अगर (pdev->id_entry)
		caps = (व्योम *)pdev->id_entry->driver_data;
	अन्यथा
		caps = of_device_get_match_data(&pdev->dev);

	अगर (!caps) अणु
		dev_err(&pdev->dev, "Could not retrieve NFC caps\n");
		वापस -EINVAL;
	पूर्ण

	अगर (caps->legacy_of_bindings) अणु
		काष्ठा device_node *nfc_node;
		u32 ale_offs = 21;

		/*
		 * If we are parsing legacy DT props and the DT contains a
		 * valid NFC node, क्रमward the request to the sama5 logic.
		 */
		nfc_node = of_get_compatible_child(pdev->dev.of_node,
						   "atmel,sama5d3-nfc");
		अगर (nfc_node) अणु
			caps = &aपंचांगel_sama5_nand_caps;
			of_node_put(nfc_node);
		पूर्ण

		/*
		 * Even अगर the compatible says we are dealing with an
		 * at91rm9200 controller, the aपंचांगel,nand-has-dma specअगरy that
		 * this controller supports DMA, which means we are in fact
		 * dealing with an at91sam9g45+ controller.
		 */
		अगर (!caps->has_dma &&
		    of_property_पढ़ो_bool(pdev->dev.of_node,
					  "atmel,nand-has-dma"))
			caps = &aपंचांगel_sam9g45_nand_caps;

		/*
		 * All SoCs except the at91sam9261 are assigning ALE to A21 and
		 * CLE to A22. If aपंचांगel,nand-addr-offset != 21 this means we're
		 * actually dealing with an at91sam9261 controller.
		 */
		of_property_पढ़ो_u32(pdev->dev.of_node,
				     "atmel,nand-addr-offset", &ale_offs);
		अगर (ale_offs != 21)
			caps = &aपंचांगel_sam9261_nand_caps;
	पूर्ण

	वापस caps->ops->probe(pdev, caps);
पूर्ण

अटल पूर्णांक aपंचांगel_nand_controller_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_nand_controller *nc = platक्रमm_get_drvdata(pdev);

	वापस nc->caps->ops->हटाओ(nc);
पूर्ण

अटल __maybe_unused पूर्णांक aपंचांगel_nand_controller_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_nand_controller *nc = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_nand *nand;

	अगर (nc->pmecc)
		aपंचांगel_pmecc_reset(nc->pmecc);

	list_क्रम_each_entry(nand, &nc->chips, node) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nand->numcs; i++)
			nand_reset(&nand->base, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_nand_controller_pm_ops, शून्य,
			 aपंचांगel_nand_controller_resume);

अटल काष्ठा platक्रमm_driver aपंचांगel_nand_controller_driver = अणु
	.driver = अणु
		.name = "atmel-nand-controller",
		.of_match_table = of_match_ptr(aपंचांगel_nand_controller_of_ids),
		.pm = &aपंचांगel_nand_controller_pm_ops,
	पूर्ण,
	.probe = aपंचांगel_nand_controller_probe,
	.हटाओ = aपंचांगel_nand_controller_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_nand_controller_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("NAND Flash Controller driver for Atmel SoCs");
MODULE_ALIAS("platform:atmel-nand-controller");
