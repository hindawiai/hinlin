<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2013 Boris BREZILLON <b.brezillon.dev@gmail.com>
 *
 * Derived from:
 *	https://github.com/yuq/sunxi-nfc-mtd
 *	Copyright (C) 2013 Qiang Yu <yuq825@gmail.com>
 *
 *	https://github.com/hno/Allwinner-Info
 *	Copyright (C) 2013 Henrik Nordstrथघm <Henrik Nordstrथघm>
 *
 *	Copyright (C) 2013 Dmitriy B. <rzk333@gmail.com>
 *	Copyright (C) 2013 Sergey Lapin <slapin@ossfans.org>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/reset.h>

#घोषणा NFC_REG_CTL		0x0000
#घोषणा NFC_REG_ST		0x0004
#घोषणा NFC_REG_INT		0x0008
#घोषणा NFC_REG_TIMING_CTL	0x000C
#घोषणा NFC_REG_TIMING_CFG	0x0010
#घोषणा NFC_REG_ADDR_LOW	0x0014
#घोषणा NFC_REG_ADDR_HIGH	0x0018
#घोषणा NFC_REG_SECTOR_NUM	0x001C
#घोषणा NFC_REG_CNT		0x0020
#घोषणा NFC_REG_CMD		0x0024
#घोषणा NFC_REG_RCMD_SET	0x0028
#घोषणा NFC_REG_WCMD_SET	0x002C
#घोषणा NFC_REG_A10_IO_DATA	0x0030
#घोषणा NFC_REG_A23_IO_DATA	0x0300
#घोषणा NFC_REG_ECC_CTL		0x0034
#घोषणा NFC_REG_ECC_ST		0x0038
#घोषणा NFC_REG_DEBUG		0x003C
#घोषणा NFC_REG_ECC_ERR_CNT(x)	((0x0040 + (x)) & ~0x3)
#घोषणा NFC_REG_USER_DATA(x)	(0x0050 + ((x) * 4))
#घोषणा NFC_REG_SPARE_AREA	0x00A0
#घोषणा NFC_REG_PAT_ID		0x00A4
#घोषणा NFC_REG_MDMA_ADDR	0x00C0
#घोषणा NFC_REG_MDMA_CNT	0x00C4
#घोषणा NFC_RAM0_BASE		0x0400
#घोषणा NFC_RAM1_BASE		0x0800

/* define bit use in NFC_CTL */
#घोषणा NFC_EN			BIT(0)
#घोषणा NFC_RESET		BIT(1)
#घोषणा NFC_BUS_WIDTH_MSK	BIT(2)
#घोषणा NFC_BUS_WIDTH_8		(0 << 2)
#घोषणा NFC_BUS_WIDTH_16	(1 << 2)
#घोषणा NFC_RB_SEL_MSK		BIT(3)
#घोषणा NFC_RB_SEL(x)		((x) << 3)
#घोषणा NFC_CE_SEL_MSK		GENMASK(26, 24)
#घोषणा NFC_CE_SEL(x)		((x) << 24)
#घोषणा NFC_CE_CTL		BIT(6)
#घोषणा NFC_PAGE_SHIFT_MSK	GENMASK(11, 8)
#घोषणा NFC_PAGE_SHIFT(x)	(((x) < 10 ? 0 : (x) - 10) << 8)
#घोषणा NFC_SAM			BIT(12)
#घोषणा NFC_RAM_METHOD		BIT(14)
#घोषणा NFC_DMA_TYPE_NORMAL	BIT(15)
#घोषणा NFC_DEBUG_CTL		BIT(31)

/* define bit use in NFC_ST */
#घोषणा NFC_RB_B2R		BIT(0)
#घोषणा NFC_CMD_INT_FLAG	BIT(1)
#घोषणा NFC_DMA_INT_FLAG	BIT(2)
#घोषणा NFC_CMD_FIFO_STATUS	BIT(3)
#घोषणा NFC_STA			BIT(4)
#घोषणा NFC_NATCH_INT_FLAG	BIT(5)
#घोषणा NFC_RB_STATE(x)		BIT(x + 8)

/* define bit use in NFC_INT */
#घोषणा NFC_B2R_INT_ENABLE	BIT(0)
#घोषणा NFC_CMD_INT_ENABLE	BIT(1)
#घोषणा NFC_DMA_INT_ENABLE	BIT(2)
#घोषणा NFC_INT_MASK		(NFC_B2R_INT_ENABLE | \
				 NFC_CMD_INT_ENABLE | \
				 NFC_DMA_INT_ENABLE)

/* define bit use in NFC_TIMING_CTL */
#घोषणा NFC_TIMING_CTL_EDO	BIT(8)

/* define NFC_TIMING_CFG रेजिस्टर layout */
#घोषणा NFC_TIMING_CFG(tWB, tADL, tWHR, tRHW, tCAD)		\
	(((tWB) & 0x3) | (((tADL) & 0x3) << 2) |		\
	(((tWHR) & 0x3) << 4) | (((tRHW) & 0x3) << 6) |		\
	(((tCAD) & 0x7) << 8))

/* define bit use in NFC_CMD */
#घोषणा NFC_CMD_LOW_BYTE_MSK	GENMASK(7, 0)
#घोषणा NFC_CMD_HIGH_BYTE_MSK	GENMASK(15, 8)
#घोषणा NFC_CMD(x)		(x)
#घोषणा NFC_ADR_NUM_MSK		GENMASK(18, 16)
#घोषणा NFC_ADR_NUM(x)		(((x) - 1) << 16)
#घोषणा NFC_SEND_ADR		BIT(19)
#घोषणा NFC_ACCESS_सूची		BIT(20)
#घोषणा NFC_DATA_TRANS		BIT(21)
#घोषणा NFC_SEND_CMD1		BIT(22)
#घोषणा NFC_WAIT_FLAG		BIT(23)
#घोषणा NFC_SEND_CMD2		BIT(24)
#घोषणा NFC_SEQ			BIT(25)
#घोषणा NFC_DATA_SWAP_METHOD	BIT(26)
#घोषणा NFC_ROW_AUTO_INC	BIT(27)
#घोषणा NFC_SEND_CMD3		BIT(28)
#घोषणा NFC_SEND_CMD4		BIT(29)
#घोषणा NFC_CMD_TYPE_MSK	GENMASK(31, 30)
#घोषणा NFC_NORMAL_OP		(0 << 30)
#घोषणा NFC_ECC_OP		(1 << 30)
#घोषणा NFC_PAGE_OP		(2U << 30)

/* define bit use in NFC_RCMD_SET */
#घोषणा NFC_READ_CMD_MSK	GENMASK(7, 0)
#घोषणा NFC_RND_READ_CMD0_MSK	GENMASK(15, 8)
#घोषणा NFC_RND_READ_CMD1_MSK	GENMASK(23, 16)

/* define bit use in NFC_WCMD_SET */
#घोषणा NFC_PROGRAM_CMD_MSK	GENMASK(7, 0)
#घोषणा NFC_RND_WRITE_CMD_MSK	GENMASK(15, 8)
#घोषणा NFC_READ_CMD0_MSK	GENMASK(23, 16)
#घोषणा NFC_READ_CMD1_MSK	GENMASK(31, 24)

/* define bit use in NFC_ECC_CTL */
#घोषणा NFC_ECC_EN		BIT(0)
#घोषणा NFC_ECC_PIPELINE	BIT(3)
#घोषणा NFC_ECC_EXCEPTION	BIT(4)
#घोषणा NFC_ECC_BLOCK_SIZE_MSK	BIT(5)
#घोषणा NFC_ECC_BLOCK_512	BIT(5)
#घोषणा NFC_RANDOM_EN		BIT(9)
#घोषणा NFC_RANDOM_सूचीECTION	BIT(10)
#घोषणा NFC_ECC_MODE_MSK	GENMASK(15, 12)
#घोषणा NFC_ECC_MODE(x)		((x) << 12)
#घोषणा NFC_RANDOM_SEED_MSK	GENMASK(30, 16)
#घोषणा NFC_RANDOM_SEED(x)	((x) << 16)

/* define bit use in NFC_ECC_ST */
#घोषणा NFC_ECC_ERR(x)		BIT(x)
#घोषणा NFC_ECC_ERR_MSK		GENMASK(15, 0)
#घोषणा NFC_ECC_PAT_FOUND(x)	BIT(x + 16)
#घोषणा NFC_ECC_ERR_CNT(b, x)	(((x) >> (((b) % 4) * 8)) & 0xff)

#घोषणा NFC_DEFAULT_TIMEOUT_MS	1000

#घोषणा NFC_SRAM_SIZE		1024

#घोषणा NFC_MAX_CS		7

/**
 * काष्ठा sunxi_nand_chip_sel - stores inक्रमmation related to न_अंकD Chip Select
 *
 * @cs: the न_अंकD CS id used to communicate with a न_अंकD Chip
 * @rb: the Ready/Busy pin ID. -1 means no R/B pin connected to the NFC
 */
काष्ठा sunxi_nand_chip_sel अणु
	u8 cs;
	s8 rb;
पूर्ण;

/**
 * काष्ठा sunxi_nand_hw_ecc - stores inक्रमmation related to HW ECC support
 *
 * @mode: the sunxi ECC mode field deduced from ECC requirements
 */
काष्ठा sunxi_nand_hw_ecc अणु
	पूर्णांक mode;
पूर्ण;

/**
 * काष्ठा sunxi_nand_chip - stores न_अंकD chip device related inक्रमmation
 *
 * @node: used to store न_अंकD chips पूर्णांकo a list
 * @nand: base न_अंकD chip काष्ठाure
 * @ecc: ECC controller काष्ठाure
 * @clk_rate: clk_rate required क्रम this न_अंकD chip
 * @timing_cfg: TIMING_CFG रेजिस्टर value क्रम this न_अंकD chip
 * @timing_ctl: TIMING_CTL रेजिस्टर value क्रम this न_अंकD chip
 * @nsels: number of CS lines required by the न_अंकD chip
 * @sels: array of CS lines descriptions
 */
काष्ठा sunxi_nand_chip अणु
	काष्ठा list_head node;
	काष्ठा nand_chip nand;
	काष्ठा sunxi_nand_hw_ecc *ecc;
	अचिन्हित दीर्घ clk_rate;
	u32 timing_cfg;
	u32 timing_ctl;
	पूर्णांक nsels;
	काष्ठा sunxi_nand_chip_sel sels[];
पूर्ण;

अटल अंतरभूत काष्ठा sunxi_nand_chip *to_sunxi_nand(काष्ठा nand_chip *nand)
अणु
	वापस container_of(nand, काष्ठा sunxi_nand_chip, nand);
पूर्ण

/*
 * न_अंकD Controller capabilities काष्ठाure: stores न_अंकD controller capabilities
 * क्रम distinction between compatible strings.
 *
 * @has_mdma:		Use mbus dma mode, otherwise general dma
 *			through MBUS on A23/A33 needs extra configuration.
 * @reg_io_data:	I/O data रेजिस्टर
 * @dma_maxburst:	DMA maxburst
 */
काष्ठा sunxi_nfc_caps अणु
	bool has_mdma;
	अचिन्हित पूर्णांक reg_io_data;
	अचिन्हित पूर्णांक dma_maxburst;
पूर्ण;

/**
 * काष्ठा sunxi_nfc - stores sunxi न_अंकD controller inक्रमmation
 *
 * @controller: base controller काष्ठाure
 * @dev: parent device (used to prपूर्णांक error messages)
 * @regs: न_अंकD controller रेजिस्टरs
 * @ahb_clk: न_अंकD controller AHB घड़ी
 * @mod_clk: न_अंकD controller mod घड़ी
 * @reset: न_अंकD controller reset line
 * @asचिन्हित_cs: biपंचांगask describing alपढ़ोy asचिन्हित CS lines
 * @clk_rate: न_अंकD controller current घड़ी rate
 * @chips: a list containing all the न_अंकD chips attached to this न_अंकD
 *	   controller
 * @complete: a completion object used to रुको क्रम न_अंकD controller events
 * @dmac: the DMA channel attached to the न_अंकD controller
 * @caps: न_अंकD Controller capabilities
 */
काष्ठा sunxi_nfc अणु
	काष्ठा nand_controller controller;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *ahb_clk;
	काष्ठा clk *mod_clk;
	काष्ठा reset_control *reset;
	अचिन्हित दीर्घ asचिन्हित_cs;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा list_head chips;
	काष्ठा completion complete;
	काष्ठा dma_chan *dmac;
	स्थिर काष्ठा sunxi_nfc_caps *caps;
पूर्ण;

अटल अंतरभूत काष्ठा sunxi_nfc *to_sunxi_nfc(काष्ठा nand_controller *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा sunxi_nfc, controller);
पूर्ण

अटल irqवापस_t sunxi_nfc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sunxi_nfc *nfc = dev_id;
	u32 st = पढ़ोl(nfc->regs + NFC_REG_ST);
	u32 ien = पढ़ोl(nfc->regs + NFC_REG_INT);

	अगर (!(ien & st))
		वापस IRQ_NONE;

	अगर ((ien & st) == ien)
		complete(&nfc->complete);

	ग_लिखोl(st & NFC_INT_MASK, nfc->regs + NFC_REG_ST);
	ग_लिखोl(~st & ien & NFC_INT_MASK, nfc->regs + NFC_REG_INT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sunxi_nfc_रुको_events(काष्ठा sunxi_nfc *nfc, u32 events,
				 bool use_polling, अचिन्हित पूर्णांक समयout_ms)
अणु
	पूर्णांक ret;

	अगर (events & ~NFC_INT_MASK)
		वापस -EINVAL;

	अगर (!समयout_ms)
		समयout_ms = NFC_DEFAULT_TIMEOUT_MS;

	अगर (!use_polling) अणु
		init_completion(&nfc->complete);

		ग_लिखोl(events, nfc->regs + NFC_REG_INT);

		ret = रुको_क्रम_completion_समयout(&nfc->complete,
						msecs_to_jअगरfies(समयout_ms));
		अगर (!ret)
			ret = -ETIMEDOUT;
		अन्यथा
			ret = 0;

		ग_लिखोl(0, nfc->regs + NFC_REG_INT);
	पूर्ण अन्यथा अणु
		u32 status;

		ret = पढ़ोl_poll_समयout(nfc->regs + NFC_REG_ST, status,
					 (status & events) == events, 1,
					 समयout_ms * 1000);
	पूर्ण

	ग_लिखोl(events & NFC_INT_MASK, nfc->regs + NFC_REG_ST);

	अगर (ret)
		dev_err(nfc->dev, "wait interrupt timedout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_nfc_रुको_cmd_fअगरo_empty(काष्ठा sunxi_nfc *nfc)
अणु
	u32 status;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(nfc->regs + NFC_REG_ST, status,
				 !(status & NFC_CMD_FIFO_STATUS), 1,
				 NFC_DEFAULT_TIMEOUT_MS * 1000);
	अगर (ret)
		dev_err(nfc->dev, "wait for empty cmd FIFO timedout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_nfc_rst(काष्ठा sunxi_nfc *nfc)
अणु
	u32 ctl;
	पूर्णांक ret;

	ग_लिखोl(0, nfc->regs + NFC_REG_ECC_CTL);
	ग_लिखोl(NFC_RESET, nfc->regs + NFC_REG_CTL);

	ret = पढ़ोl_poll_समयout(nfc->regs + NFC_REG_CTL, ctl,
				 !(ctl & NFC_RESET), 1,
				 NFC_DEFAULT_TIMEOUT_MS * 1000);
	अगर (ret)
		dev_err(nfc->dev, "wait for NAND controller reset timedout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_nfc_dma_op_prepare(काष्ठा sunxi_nfc *nfc, स्थिर व्योम *buf,
				    पूर्णांक chunksize, पूर्णांक nchunks,
				    क्रमागत dma_data_direction ddir,
				    काष्ठा scatterlist *sg)
अणु
	काष्ठा dma_async_tx_descriptor *dmad;
	क्रमागत dma_transfer_direction tdir;
	dma_cookie_t dmat;
	पूर्णांक ret;

	अगर (ddir == DMA_FROM_DEVICE)
		tdir = DMA_DEV_TO_MEM;
	अन्यथा
		tdir = DMA_MEM_TO_DEV;

	sg_init_one(sg, buf, nchunks * chunksize);
	ret = dma_map_sg(nfc->dev, sg, 1, ddir);
	अगर (!ret)
		वापस -ENOMEM;

	अगर (!nfc->caps->has_mdma) अणु
		dmad = dmaengine_prep_slave_sg(nfc->dmac, sg, 1, tdir, DMA_CTRL_ACK);
		अगर (!dmad) अणु
			ret = -EINVAL;
			जाओ err_unmap_buf;
		पूर्ण
	पूर्ण

	ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_CTL) | NFC_RAM_METHOD,
	       nfc->regs + NFC_REG_CTL);
	ग_लिखोl(nchunks, nfc->regs + NFC_REG_SECTOR_NUM);
	ग_लिखोl(chunksize, nfc->regs + NFC_REG_CNT);

	अगर (nfc->caps->has_mdma) अणु
		ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_CTL) & ~NFC_DMA_TYPE_NORMAL,
		       nfc->regs + NFC_REG_CTL);
		ग_लिखोl(chunksize * nchunks, nfc->regs + NFC_REG_MDMA_CNT);
		ग_लिखोl(sg_dma_address(sg), nfc->regs + NFC_REG_MDMA_ADDR);
	पूर्ण अन्यथा अणु
		dmat = dmaengine_submit(dmad);

		ret = dma_submit_error(dmat);
		अगर (ret)
			जाओ err_clr_dma_flag;
	पूर्ण

	वापस 0;

err_clr_dma_flag:
	ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_CTL) & ~NFC_RAM_METHOD,
	       nfc->regs + NFC_REG_CTL);

err_unmap_buf:
	dma_unmap_sg(nfc->dev, sg, 1, ddir);
	वापस ret;
पूर्ण

अटल व्योम sunxi_nfc_dma_op_cleanup(काष्ठा sunxi_nfc *nfc,
				     क्रमागत dma_data_direction ddir,
				     काष्ठा scatterlist *sg)
अणु
	dma_unmap_sg(nfc->dev, sg, 1, ddir);
	ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_CTL) & ~NFC_RAM_METHOD,
	       nfc->regs + NFC_REG_CTL);
पूर्ण

अटल व्योम sunxi_nfc_select_chip(काष्ठा nand_chip *nand, अचिन्हित पूर्णांक cs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	काष्ठा sunxi_nand_chip_sel *sel;
	u32 ctl;

	अगर (cs > 0 && cs >= sunxi_nand->nsels)
		वापस;

	ctl = पढ़ोl(nfc->regs + NFC_REG_CTL) &
	      ~(NFC_PAGE_SHIFT_MSK | NFC_CE_SEL_MSK | NFC_RB_SEL_MSK | NFC_EN);

	sel = &sunxi_nand->sels[cs];
	ctl |= NFC_CE_SEL(sel->cs) | NFC_EN | NFC_PAGE_SHIFT(nand->page_shअगरt);
	अगर (sel->rb >= 0)
		ctl |= NFC_RB_SEL(sel->rb);

	ग_लिखोl(mtd->ग_लिखोsize, nfc->regs + NFC_REG_SPARE_AREA);

	अगर (nfc->clk_rate != sunxi_nand->clk_rate) अणु
		clk_set_rate(nfc->mod_clk, sunxi_nand->clk_rate);
		nfc->clk_rate = sunxi_nand->clk_rate;
	पूर्ण

	ग_लिखोl(sunxi_nand->timing_ctl, nfc->regs + NFC_REG_TIMING_CTL);
	ग_लिखोl(sunxi_nand->timing_cfg, nfc->regs + NFC_REG_TIMING_CFG);
	ग_लिखोl(ctl, nfc->regs + NFC_REG_CTL);
पूर्ण

अटल व्योम sunxi_nfc_पढ़ो_buf(काष्ठा nand_chip *nand, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	पूर्णांक ret;
	पूर्णांक cnt;
	पूर्णांक offs = 0;
	u32 पंचांगp;

	जबतक (len > offs) अणु
		bool poll = false;

		cnt = min(len - offs, NFC_SRAM_SIZE);

		ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
		अगर (ret)
			अवरोध;

		ग_लिखोl(cnt, nfc->regs + NFC_REG_CNT);
		पंचांगp = NFC_DATA_TRANS | NFC_DATA_SWAP_METHOD;
		ग_लिखोl(पंचांगp, nfc->regs + NFC_REG_CMD);

		/* Arbitrary limit क्रम polling mode */
		अगर (cnt < 64)
			poll = true;

		ret = sunxi_nfc_रुको_events(nfc, NFC_CMD_INT_FLAG, poll, 0);
		अगर (ret)
			अवरोध;

		अगर (buf)
			स_नकल_fromio(buf + offs, nfc->regs + NFC_RAM0_BASE,
				      cnt);
		offs += cnt;
	पूर्ण
पूर्ण

अटल व्योम sunxi_nfc_ग_लिखो_buf(काष्ठा nand_chip *nand, स्थिर uपूर्णांक8_t *buf,
				पूर्णांक len)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	पूर्णांक ret;
	पूर्णांक cnt;
	पूर्णांक offs = 0;
	u32 पंचांगp;

	जबतक (len > offs) अणु
		bool poll = false;

		cnt = min(len - offs, NFC_SRAM_SIZE);

		ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
		अगर (ret)
			अवरोध;

		ग_लिखोl(cnt, nfc->regs + NFC_REG_CNT);
		स_नकल_toio(nfc->regs + NFC_RAM0_BASE, buf + offs, cnt);
		पंचांगp = NFC_DATA_TRANS | NFC_DATA_SWAP_METHOD |
		      NFC_ACCESS_सूची;
		ग_लिखोl(पंचांगp, nfc->regs + NFC_REG_CMD);

		/* Arbitrary limit क्रम polling mode */
		अगर (cnt < 64)
			poll = true;

		ret = sunxi_nfc_रुको_events(nfc, NFC_CMD_INT_FLAG, poll, 0);
		अगर (ret)
			अवरोध;

		offs += cnt;
	पूर्ण
पूर्ण

/* These seed values have been extracted from Allwinner's BSP */
अटल स्थिर u16 sunxi_nfc_अक्रमomizer_page_seeds[] = अणु
	0x2b75, 0x0bd0, 0x5ca3, 0x62d1, 0x1c93, 0x07e9, 0x2162, 0x3a72,
	0x0d67, 0x67f9, 0x1be7, 0x077d, 0x032f, 0x0dac, 0x2716, 0x2436,
	0x7922, 0x1510, 0x3860, 0x5287, 0x480f, 0x4252, 0x1789, 0x5a2d,
	0x2a49, 0x5e10, 0x437f, 0x4b4e, 0x2f45, 0x216e, 0x5cb7, 0x7130,
	0x2a3f, 0x60e4, 0x4dc9, 0x0ef0, 0x0f52, 0x1bb9, 0x6211, 0x7a56,
	0x226d, 0x4ea7, 0x6f36, 0x3692, 0x38bf, 0x0c62, 0x05eb, 0x4c55,
	0x60f4, 0x728c, 0x3b6f, 0x2037, 0x7f69, 0x0936, 0x651a, 0x4ceb,
	0x6218, 0x79f3, 0x383f, 0x18d9, 0x4f05, 0x5c82, 0x2912, 0x6f17,
	0x6856, 0x5938, 0x1007, 0x61ab, 0x3e7f, 0x57c2, 0x542f, 0x4f62,
	0x7454, 0x2eac, 0x7739, 0x42d4, 0x2f90, 0x435a, 0x2e52, 0x2064,
	0x637c, 0x66ad, 0x2c90, 0x0bad, 0x759c, 0x0029, 0x0986, 0x7126,
	0x1ca7, 0x1605, 0x386a, 0x27f5, 0x1380, 0x6d75, 0x24c3, 0x0f8e,
	0x2b7a, 0x1418, 0x1fd1, 0x7dc1, 0x2d8e, 0x43af, 0x2267, 0x7da3,
	0x4e3d, 0x1338, 0x50db, 0x454d, 0x764d, 0x40a3, 0x42e6, 0x262b,
	0x2d2e, 0x1aea, 0x2e17, 0x173d, 0x3a6e, 0x71bf, 0x25f9, 0x0a5d,
	0x7c57, 0x0fbe, 0x46ce, 0x4939, 0x6b17, 0x37bb, 0x3e91, 0x76db,
पूर्ण;

/*
 * sunxi_nfc_अक्रमomizer_ecc512_seeds and sunxi_nfc_अक्रमomizer_ecc1024_seeds
 * have been generated using
 * sunxi_nfc_अक्रमomizer_step(seed, (step_size * 8) + 15), which is what
 * the अक्रमomizer engine करोes पूर्णांकernally beक्रमe de/scrambling OOB data.
 *
 * Those tables are अटलally defined to aव्योम calculating अक्रमomizer state
 * at runसमय.
 */
अटल स्थिर u16 sunxi_nfc_अक्रमomizer_ecc512_seeds[] = अणु
	0x3346, 0x367f, 0x1f18, 0x769a, 0x4f64, 0x068c, 0x2ef1, 0x6b64,
	0x28a9, 0x15d7, 0x30f8, 0x3659, 0x53db, 0x7c5f, 0x71d4, 0x4409,
	0x26eb, 0x03cc, 0x655d, 0x47d4, 0x4daa, 0x0877, 0x712d, 0x3617,
	0x3264, 0x49aa, 0x7f9e, 0x588e, 0x4fbc, 0x7176, 0x7f91, 0x6c6d,
	0x4b95, 0x5fb7, 0x3844, 0x4037, 0x0184, 0x081b, 0x0ee8, 0x5b91,
	0x293d, 0x1f71, 0x0e6f, 0x402b, 0x5122, 0x1e52, 0x22be, 0x3d2d,
	0x75bc, 0x7c60, 0x6291, 0x1a2f, 0x61d4, 0x74aa, 0x4140, 0x29ab,
	0x472d, 0x2852, 0x017e, 0x15e8, 0x5ec2, 0x17cf, 0x7d0f, 0x06b8,
	0x117a, 0x6b94, 0x789b, 0x3126, 0x6ac5, 0x5be7, 0x150f, 0x51f8,
	0x7889, 0x0aa5, 0x663d, 0x77e8, 0x0b87, 0x3dcb, 0x360d, 0x218b,
	0x512f, 0x7dc9, 0x6a4d, 0x630a, 0x3547, 0x1dd2, 0x5aea, 0x69a5,
	0x7bfa, 0x5e4f, 0x1519, 0x6430, 0x3a0e, 0x5eb3, 0x5425, 0x0c7a,
	0x5540, 0x3670, 0x63c1, 0x31e9, 0x5a39, 0x2de7, 0x5979, 0x2891,
	0x1562, 0x014b, 0x5b05, 0x2756, 0x5a34, 0x13aa, 0x6cb5, 0x2c36,
	0x5e72, 0x1306, 0x0861, 0x15ef, 0x1ee8, 0x5a37, 0x7ac4, 0x45dd,
	0x44c4, 0x7266, 0x2f41, 0x3ccc, 0x045e, 0x7d40, 0x7c66, 0x0fa0,
पूर्ण;

अटल स्थिर u16 sunxi_nfc_अक्रमomizer_ecc1024_seeds[] = अणु
	0x2cf5, 0x35f1, 0x63a4, 0x5274, 0x2bd2, 0x778b, 0x7285, 0x32b6,
	0x6a5c, 0x70d6, 0x757d, 0x6769, 0x5375, 0x1e81, 0x0cf3, 0x3982,
	0x6787, 0x042a, 0x6c49, 0x1925, 0x56a8, 0x40a9, 0x063e, 0x7bd9,
	0x4dbf, 0x55ec, 0x672e, 0x7334, 0x5185, 0x4d00, 0x232a, 0x7e07,
	0x445d, 0x6b92, 0x528f, 0x4255, 0x53ba, 0x7d82, 0x2a2e, 0x3a4e,
	0x75eb, 0x450c, 0x6844, 0x1b5d, 0x581a, 0x4cc6, 0x0379, 0x37b2,
	0x419f, 0x0e92, 0x6b27, 0x5624, 0x01e3, 0x07c1, 0x44a5, 0x130c,
	0x13e8, 0x5910, 0x0876, 0x60c5, 0x54e3, 0x5b7f, 0x2269, 0x509f,
	0x7665, 0x36fd, 0x3e9a, 0x0579, 0x6295, 0x14ef, 0x0a81, 0x1bcc,
	0x4b16, 0x64db, 0x0514, 0x4f07, 0x0591, 0x3576, 0x6853, 0x0d9e,
	0x259f, 0x38b7, 0x64fb, 0x3094, 0x4693, 0x6ddd, 0x29bb, 0x0bc8,
	0x3f47, 0x490e, 0x0c0e, 0x7933, 0x3c9e, 0x5840, 0x398d, 0x3e68,
	0x4af1, 0x71f5, 0x57cf, 0x1121, 0x64eb, 0x3579, 0x15ac, 0x584d,
	0x5f2a, 0x47e2, 0x6528, 0x6eac, 0x196e, 0x6b96, 0x0450, 0x0179,
	0x609c, 0x06e1, 0x4626, 0x42c7, 0x273e, 0x486f, 0x0705, 0x1601,
	0x145b, 0x407e, 0x062b, 0x57a5, 0x53f9, 0x5659, 0x4410, 0x3ccd,
पूर्ण;

अटल u16 sunxi_nfc_अक्रमomizer_step(u16 state, पूर्णांक count)
अणु
	state &= 0x7fff;

	/*
	 * This loop is just a simple implementation of a Fibonacci LFSR using
	 * the x16 + x15 + 1 polynomial.
	 */
	जबतक (count--)
		state = ((state >> 1) |
			 (((state ^ (state >> 1)) & 1) << 14)) & 0x7fff;

	वापस state;
पूर्ण

अटल u16 sunxi_nfc_अक्रमomizer_state(काष्ठा nand_chip *nand, पूर्णांक page,
				      bool ecc)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	स्थिर u16 *seeds = sunxi_nfc_अक्रमomizer_page_seeds;
	पूर्णांक mod = mtd_भाग_by_ws(mtd->erasesize, mtd);

	अगर (mod > ARRAY_SIZE(sunxi_nfc_अक्रमomizer_page_seeds))
		mod = ARRAY_SIZE(sunxi_nfc_अक्रमomizer_page_seeds);

	अगर (ecc) अणु
		अगर (mtd->ecc_step_size == 512)
			seeds = sunxi_nfc_अक्रमomizer_ecc512_seeds;
		अन्यथा
			seeds = sunxi_nfc_अक्रमomizer_ecc1024_seeds;
	पूर्ण

	वापस seeds[page % mod];
पूर्ण

अटल व्योम sunxi_nfc_अक्रमomizer_config(काष्ठा nand_chip *nand, पूर्णांक page,
					bool ecc)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	u32 ecc_ctl = पढ़ोl(nfc->regs + NFC_REG_ECC_CTL);
	u16 state;

	अगर (!(nand->options & न_अंकD_NEED_SCRAMBLING))
		वापस;

	ecc_ctl = पढ़ोl(nfc->regs + NFC_REG_ECC_CTL);
	state = sunxi_nfc_अक्रमomizer_state(nand, page, ecc);
	ecc_ctl = पढ़ोl(nfc->regs + NFC_REG_ECC_CTL) & ~NFC_RANDOM_SEED_MSK;
	ग_लिखोl(ecc_ctl | NFC_RANDOM_SEED(state), nfc->regs + NFC_REG_ECC_CTL);
पूर्ण

अटल व्योम sunxi_nfc_अक्रमomizer_enable(काष्ठा nand_chip *nand)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);

	अगर (!(nand->options & न_अंकD_NEED_SCRAMBLING))
		वापस;

	ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_ECC_CTL) | NFC_RANDOM_EN,
	       nfc->regs + NFC_REG_ECC_CTL);
पूर्ण

अटल व्योम sunxi_nfc_अक्रमomizer_disable(काष्ठा nand_chip *nand)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);

	अगर (!(nand->options & न_अंकD_NEED_SCRAMBLING))
		वापस;

	ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_ECC_CTL) & ~NFC_RANDOM_EN,
	       nfc->regs + NFC_REG_ECC_CTL);
पूर्ण

अटल व्योम sunxi_nfc_अक्रमomize_bbm(काष्ठा nand_chip *nand, पूर्णांक page, u8 *bbm)
अणु
	u16 state = sunxi_nfc_अक्रमomizer_state(nand, page, true);

	bbm[0] ^= state;
	bbm[1] ^= sunxi_nfc_अक्रमomizer_step(state, 8);
पूर्ण

अटल व्योम sunxi_nfc_अक्रमomizer_ग_लिखो_buf(काष्ठा nand_chip *nand,
					   स्थिर uपूर्णांक8_t *buf, पूर्णांक len,
					   bool ecc, पूर्णांक page)
अणु
	sunxi_nfc_अक्रमomizer_config(nand, page, ecc);
	sunxi_nfc_अक्रमomizer_enable(nand);
	sunxi_nfc_ग_लिखो_buf(nand, buf, len);
	sunxi_nfc_अक्रमomizer_disable(nand);
पूर्ण

अटल व्योम sunxi_nfc_अक्रमomizer_पढ़ो_buf(काष्ठा nand_chip *nand, uपूर्णांक8_t *buf,
					  पूर्णांक len, bool ecc, पूर्णांक page)
अणु
	sunxi_nfc_अक्रमomizer_config(nand, page, ecc);
	sunxi_nfc_अक्रमomizer_enable(nand);
	sunxi_nfc_पढ़ो_buf(nand, buf, len);
	sunxi_nfc_अक्रमomizer_disable(nand);
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_enable(काष्ठा nand_chip *nand)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	u32 ecc_ctl;

	ecc_ctl = पढ़ोl(nfc->regs + NFC_REG_ECC_CTL);
	ecc_ctl &= ~(NFC_ECC_MODE_MSK | NFC_ECC_PIPELINE |
		     NFC_ECC_BLOCK_SIZE_MSK);
	ecc_ctl |= NFC_ECC_EN | NFC_ECC_MODE(sunxi_nand->ecc->mode) |
		   NFC_ECC_EXCEPTION | NFC_ECC_PIPELINE;

	अगर (nand->ecc.size == 512)
		ecc_ctl |= NFC_ECC_BLOCK_512;

	ग_लिखोl(ecc_ctl, nfc->regs + NFC_REG_ECC_CTL);
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_disable(काष्ठा nand_chip *nand)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);

	ग_लिखोl(पढ़ोl(nfc->regs + NFC_REG_ECC_CTL) & ~NFC_ECC_EN,
	       nfc->regs + NFC_REG_ECC_CTL);
पूर्ण

अटल अंतरभूत व्योम sunxi_nfc_user_data_to_buf(u32 user_data, u8 *buf)
अणु
	buf[0] = user_data;
	buf[1] = user_data >> 8;
	buf[2] = user_data >> 16;
	buf[3] = user_data >> 24;
पूर्ण

अटल अंतरभूत u32 sunxi_nfc_buf_to_user_data(स्थिर u8 *buf)
अणु
	वापस buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_get_prot_oob_bytes(काष्ठा nand_chip *nand, u8 *oob,
						पूर्णांक step, bool bbm, पूर्णांक page)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);

	sunxi_nfc_user_data_to_buf(पढ़ोl(nfc->regs + NFC_REG_USER_DATA(step)),
				   oob);

	/* De-अक्रमomize the Bad Block Marker. */
	अगर (bbm && (nand->options & न_अंकD_NEED_SCRAMBLING))
		sunxi_nfc_अक्रमomize_bbm(nand, page, oob);
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_set_prot_oob_bytes(काष्ठा nand_chip *nand,
						स्थिर u8 *oob, पूर्णांक step,
						bool bbm, पूर्णांक page)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	u8 user_data[4];

	/* Ranकरोmize the Bad Block Marker. */
	अगर (bbm && (nand->options & न_अंकD_NEED_SCRAMBLING)) अणु
		स_नकल(user_data, oob, माप(user_data));
		sunxi_nfc_अक्रमomize_bbm(nand, page, user_data);
		oob = user_data;
	पूर्ण

	ग_लिखोl(sunxi_nfc_buf_to_user_data(oob),
	       nfc->regs + NFC_REG_USER_DATA(step));
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_update_stats(काष्ठा nand_chip *nand,
					  अचिन्हित पूर्णांक *max_bitflips, पूर्णांक ret)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);

	अगर (ret < 0) अणु
		mtd->ecc_stats.failed++;
	पूर्ण अन्यथा अणु
		mtd->ecc_stats.corrected += ret;
		*max_bitflips = max_t(अचिन्हित पूर्णांक, *max_bitflips, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_correct(काष्ठा nand_chip *nand, u8 *data, u8 *oob,
				    पूर्णांक step, u32 status, bool *erased)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	u32 पंचांगp;

	*erased = false;

	अगर (status & NFC_ECC_ERR(step))
		वापस -EBADMSG;

	अगर (status & NFC_ECC_PAT_FOUND(step)) अणु
		u8 pattern;

		अगर (unlikely(!(पढ़ोl(nfc->regs + NFC_REG_PAT_ID) & 0x1))) अणु
			pattern = 0x0;
		पूर्ण अन्यथा अणु
			pattern = 0xff;
			*erased = true;
		पूर्ण

		अगर (data)
			स_रखो(data, pattern, ecc->size);

		अगर (oob)
			स_रखो(oob, pattern, ecc->bytes + 4);

		वापस 0;
	पूर्ण

	पंचांगp = पढ़ोl(nfc->regs + NFC_REG_ECC_ERR_CNT(step));

	वापस NFC_ECC_ERR_CNT(step, पंचांगp);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_chunk(काष्ठा nand_chip *nand,
				       u8 *data, पूर्णांक data_off,
				       u8 *oob, पूर्णांक oob_off,
				       पूर्णांक *cur_off,
				       अचिन्हित पूर्णांक *max_bitflips,
				       bool bbm, bool oob_required, पूर्णांक page)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक raw_mode = 0;
	bool erased;
	पूर्णांक ret;

	अगर (*cur_off != data_off)
		nand_change_पढ़ो_column_op(nand, data_off, शून्य, 0, false);

	sunxi_nfc_अक्रमomizer_पढ़ो_buf(nand, शून्य, ecc->size, false, page);

	अगर (data_off + ecc->size != oob_off)
		nand_change_पढ़ो_column_op(nand, oob_off, शून्य, 0, false);

	ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
	अगर (ret)
		वापस ret;

	sunxi_nfc_अक्रमomizer_enable(nand);
	ग_लिखोl(NFC_DATA_TRANS | NFC_DATA_SWAP_METHOD | NFC_ECC_OP,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_रुको_events(nfc, NFC_CMD_INT_FLAG, false, 0);
	sunxi_nfc_अक्रमomizer_disable(nand);
	अगर (ret)
		वापस ret;

	*cur_off = oob_off + ecc->bytes + 4;

	ret = sunxi_nfc_hw_ecc_correct(nand, data, oob_required ? oob : शून्य, 0,
				       पढ़ोl(nfc->regs + NFC_REG_ECC_ST),
				       &erased);
	अगर (erased)
		वापस 1;

	अगर (ret < 0) अणु
		/*
		 * Re-पढ़ो the data with the अक्रमomizer disabled to identअगरy
		 * bitflips in erased pages.
		 */
		अगर (nand->options & न_अंकD_NEED_SCRAMBLING)
			nand_change_पढ़ो_column_op(nand, data_off, data,
						   ecc->size, false);
		अन्यथा
			स_नकल_fromio(data, nfc->regs + NFC_RAM0_BASE,
				      ecc->size);

		nand_change_पढ़ो_column_op(nand, oob_off, oob, ecc->bytes + 4,
					   false);

		ret = nand_check_erased_ecc_chunk(data,	ecc->size,
						  oob, ecc->bytes + 4,
						  शून्य, 0, ecc->strength);
		अगर (ret >= 0)
			raw_mode = 1;
	पूर्ण अन्यथा अणु
		स_नकल_fromio(data, nfc->regs + NFC_RAM0_BASE, ecc->size);

		अगर (oob_required) अणु
			nand_change_पढ़ो_column_op(nand, oob_off, शून्य, 0,
						   false);
			sunxi_nfc_अक्रमomizer_पढ़ो_buf(nand, oob, ecc->bytes + 4,
						      true, page);

			sunxi_nfc_hw_ecc_get_prot_oob_bytes(nand, oob, 0,
							    bbm, page);
		पूर्ण
	पूर्ण

	sunxi_nfc_hw_ecc_update_stats(nand, max_bitflips, ret);

	वापस raw_mode;
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_पढ़ो_extra_oob(काष्ठा nand_chip *nand,
					    u8 *oob, पूर्णांक *cur_off,
					    bool अक्रमomize, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक offset = ((ecc->bytes + 4) * ecc->steps);
	पूर्णांक len = mtd->oobsize - offset;

	अगर (len <= 0)
		वापस;

	अगर (!cur_off || *cur_off != offset)
		nand_change_पढ़ो_column_op(nand, mtd->ग_लिखोsize, शून्य, 0,
					   false);

	अगर (!अक्रमomize)
		sunxi_nfc_पढ़ो_buf(nand, oob + offset, len);
	अन्यथा
		sunxi_nfc_अक्रमomizer_पढ़ो_buf(nand, oob + offset, len,
					      false, page);

	अगर (cur_off)
		*cur_off = mtd->oobsize + mtd->ग_लिखोsize;
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_chunks_dma(काष्ठा nand_chip *nand, uपूर्णांक8_t *buf,
					    पूर्णांक oob_required, पूर्णांक page,
					    पूर्णांक nchunks)
अणु
	bool अक्रमomized = nand->options & न_अंकD_NEED_SCRAMBLING;
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	अचिन्हित पूर्णांक max_bitflips = 0;
	पूर्णांक ret, i, raw_mode = 0;
	काष्ठा scatterlist sg;
	u32 status, रुको;

	ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
	अगर (ret)
		वापस ret;

	ret = sunxi_nfc_dma_op_prepare(nfc, buf, ecc->size, nchunks,
				       DMA_FROM_DEVICE, &sg);
	अगर (ret)
		वापस ret;

	sunxi_nfc_hw_ecc_enable(nand);
	sunxi_nfc_अक्रमomizer_config(nand, page, false);
	sunxi_nfc_अक्रमomizer_enable(nand);

	ग_लिखोl((न_अंकD_CMD_RNDOUTSTART << 16) | (न_अंकD_CMD_RNDOUT << 8) |
	       न_अंकD_CMD_READSTART, nfc->regs + NFC_REG_RCMD_SET);

	रुको = NFC_CMD_INT_FLAG;

	अगर (nfc->caps->has_mdma)
		रुको |= NFC_DMA_INT_FLAG;
	अन्यथा
		dma_async_issue_pending(nfc->dmac);

	ग_लिखोl(NFC_PAGE_OP | NFC_DATA_SWAP_METHOD | NFC_DATA_TRANS,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_रुको_events(nfc, रुको, false, 0);
	अगर (ret && !nfc->caps->has_mdma)
		dmaengine_terminate_all(nfc->dmac);

	sunxi_nfc_अक्रमomizer_disable(nand);
	sunxi_nfc_hw_ecc_disable(nand);

	sunxi_nfc_dma_op_cleanup(nfc, DMA_FROM_DEVICE, &sg);

	अगर (ret)
		वापस ret;

	status = पढ़ोl(nfc->regs + NFC_REG_ECC_ST);

	क्रम (i = 0; i < nchunks; i++) अणु
		पूर्णांक data_off = i * ecc->size;
		पूर्णांक oob_off = i * (ecc->bytes + 4);
		u8 *data = buf + data_off;
		u8 *oob = nand->oob_poi + oob_off;
		bool erased;

		ret = sunxi_nfc_hw_ecc_correct(nand, अक्रमomized ? data : शून्य,
					       oob_required ? oob : शून्य,
					       i, status, &erased);

		/* ECC errors are handled in the second loop. */
		अगर (ret < 0)
			जारी;

		अगर (oob_required && !erased) अणु
			/* TODO: use DMA to retrieve OOB */
			nand_change_पढ़ो_column_op(nand,
						   mtd->ग_लिखोsize + oob_off,
						   oob, ecc->bytes + 4, false);

			sunxi_nfc_hw_ecc_get_prot_oob_bytes(nand, oob, i,
							    !i, page);
		पूर्ण

		अगर (erased)
			raw_mode = 1;

		sunxi_nfc_hw_ecc_update_stats(nand, &max_bitflips, ret);
	पूर्ण

	अगर (status & NFC_ECC_ERR_MSK) अणु
		क्रम (i = 0; i < nchunks; i++) अणु
			पूर्णांक data_off = i * ecc->size;
			पूर्णांक oob_off = i * (ecc->bytes + 4);
			u8 *data = buf + data_off;
			u8 *oob = nand->oob_poi + oob_off;

			अगर (!(status & NFC_ECC_ERR(i)))
				जारी;

			/*
			 * Re-पढ़ो the data with the अक्रमomizer disabled to
			 * identअगरy bitflips in erased pages.
			 * TODO: use DMA to पढ़ो page in raw mode
			 */
			अगर (अक्रमomized)
				nand_change_पढ़ो_column_op(nand, data_off,
							   data, ecc->size,
							   false);

			/* TODO: use DMA to retrieve OOB */
			nand_change_पढ़ो_column_op(nand,
						   mtd->ग_लिखोsize + oob_off,
						   oob, ecc->bytes + 4, false);

			ret = nand_check_erased_ecc_chunk(data,	ecc->size,
							  oob, ecc->bytes + 4,
							  शून्य, 0,
							  ecc->strength);
			अगर (ret >= 0)
				raw_mode = 1;

			sunxi_nfc_hw_ecc_update_stats(nand, &max_bitflips, ret);
		पूर्ण
	पूर्ण

	अगर (oob_required)
		sunxi_nfc_hw_ecc_पढ़ो_extra_oob(nand, nand->oob_poi,
						शून्य, !raw_mode,
						page);

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_ग_लिखो_chunk(काष्ठा nand_chip *nand,
					स्थिर u8 *data, पूर्णांक data_off,
					स्थिर u8 *oob, पूर्णांक oob_off,
					पूर्णांक *cur_off, bool bbm,
					पूर्णांक page)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक ret;

	अगर (data_off != *cur_off)
		nand_change_ग_लिखो_column_op(nand, data_off, शून्य, 0, false);

	sunxi_nfc_अक्रमomizer_ग_लिखो_buf(nand, data, ecc->size, false, page);

	अगर (data_off + ecc->size != oob_off)
		nand_change_ग_लिखो_column_op(nand, oob_off, शून्य, 0, false);

	ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
	अगर (ret)
		वापस ret;

	sunxi_nfc_अक्रमomizer_enable(nand);
	sunxi_nfc_hw_ecc_set_prot_oob_bytes(nand, oob, 0, bbm, page);

	ग_लिखोl(NFC_DATA_TRANS | NFC_DATA_SWAP_METHOD |
	       NFC_ACCESS_सूची | NFC_ECC_OP,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_रुको_events(nfc, NFC_CMD_INT_FLAG, false, 0);
	sunxi_nfc_अक्रमomizer_disable(nand);
	अगर (ret)
		वापस ret;

	*cur_off = oob_off + ecc->bytes + 4;

	वापस 0;
पूर्ण

अटल व्योम sunxi_nfc_hw_ecc_ग_लिखो_extra_oob(काष्ठा nand_chip *nand,
					     u8 *oob, पूर्णांक *cur_off,
					     पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक offset = ((ecc->bytes + 4) * ecc->steps);
	पूर्णांक len = mtd->oobsize - offset;

	अगर (len <= 0)
		वापस;

	अगर (!cur_off || *cur_off != offset)
		nand_change_ग_लिखो_column_op(nand, offset + mtd->ग_लिखोsize,
					    शून्य, 0, false);

	sunxi_nfc_अक्रमomizer_ग_लिखो_buf(nand, oob + offset, len, false, page);

	अगर (cur_off)
		*cur_off = mtd->oobsize + mtd->ग_लिखोsize;
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_page(काष्ठा nand_chip *nand, uपूर्णांक8_t *buf,
				      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	अचिन्हित पूर्णांक max_bitflips = 0;
	पूर्णांक ret, i, cur_off = 0;
	bool raw_mode = false;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_पढ़ो_page_op(nand, page, 0, शून्य, 0);

	sunxi_nfc_hw_ecc_enable(nand);

	क्रम (i = 0; i < ecc->steps; i++) अणु
		पूर्णांक data_off = i * ecc->size;
		पूर्णांक oob_off = i * (ecc->bytes + 4);
		u8 *data = buf + data_off;
		u8 *oob = nand->oob_poi + oob_off;

		ret = sunxi_nfc_hw_ecc_पढ़ो_chunk(nand, data, data_off, oob,
						  oob_off + mtd->ग_लिखोsize,
						  &cur_off, &max_bitflips,
						  !i, oob_required, page);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret)
			raw_mode = true;
	पूर्ण

	अगर (oob_required)
		sunxi_nfc_hw_ecc_पढ़ो_extra_oob(nand, nand->oob_poi, &cur_off,
						!raw_mode, page);

	sunxi_nfc_hw_ecc_disable(nand);

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_page_dma(काष्ठा nand_chip *nand, u8 *buf,
					  पूर्णांक oob_required, पूर्णांक page)
अणु
	पूर्णांक ret;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_पढ़ो_page_op(nand, page, 0, शून्य, 0);

	ret = sunxi_nfc_hw_ecc_पढ़ो_chunks_dma(nand, buf, oob_required, page,
					       nand->ecc.steps);
	अगर (ret >= 0)
		वापस ret;

	/* Fallback to PIO mode */
	वापस sunxi_nfc_hw_ecc_पढ़ो_page(nand, buf, oob_required, page);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_subpage(काष्ठा nand_chip *nand,
					 u32 data_offs, u32 पढ़ोlen,
					 u8 *bufpoi, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक ret, i, cur_off = 0;
	अचिन्हित पूर्णांक max_bitflips = 0;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_पढ़ो_page_op(nand, page, 0, शून्य, 0);

	sunxi_nfc_hw_ecc_enable(nand);

	क्रम (i = data_offs / ecc->size;
	     i < DIV_ROUND_UP(data_offs + पढ़ोlen, ecc->size); i++) अणु
		पूर्णांक data_off = i * ecc->size;
		पूर्णांक oob_off = i * (ecc->bytes + 4);
		u8 *data = bufpoi + data_off;
		u8 *oob = nand->oob_poi + oob_off;

		ret = sunxi_nfc_hw_ecc_पढ़ो_chunk(nand, data, data_off,
						  oob,
						  oob_off + mtd->ग_लिखोsize,
						  &cur_off, &max_bitflips, !i,
						  false, page);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	sunxi_nfc_hw_ecc_disable(nand);

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_subpage_dma(काष्ठा nand_chip *nand,
					     u32 data_offs, u32 पढ़ोlen,
					     u8 *buf, पूर्णांक page)
अणु
	पूर्णांक nchunks = DIV_ROUND_UP(data_offs + पढ़ोlen, nand->ecc.size);
	पूर्णांक ret;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_पढ़ो_page_op(nand, page, 0, शून्य, 0);

	ret = sunxi_nfc_hw_ecc_पढ़ो_chunks_dma(nand, buf, false, page, nchunks);
	अगर (ret >= 0)
		वापस ret;

	/* Fallback to PIO mode */
	वापस sunxi_nfc_hw_ecc_पढ़ो_subpage(nand, data_offs, पढ़ोlen,
					     buf, page);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_ग_लिखो_page(काष्ठा nand_chip *nand,
				       स्थिर uपूर्णांक8_t *buf, पूर्णांक oob_required,
				       पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक ret, i, cur_off = 0;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_prog_page_begin_op(nand, page, 0, शून्य, 0);

	sunxi_nfc_hw_ecc_enable(nand);

	क्रम (i = 0; i < ecc->steps; i++) अणु
		पूर्णांक data_off = i * ecc->size;
		पूर्णांक oob_off = i * (ecc->bytes + 4);
		स्थिर u8 *data = buf + data_off;
		स्थिर u8 *oob = nand->oob_poi + oob_off;

		ret = sunxi_nfc_hw_ecc_ग_लिखो_chunk(nand, data, data_off, oob,
						   oob_off + mtd->ग_लिखोsize,
						   &cur_off, !i, page);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (oob_required || (nand->options & न_अंकD_NEED_SCRAMBLING))
		sunxi_nfc_hw_ecc_ग_लिखो_extra_oob(nand, nand->oob_poi,
						 &cur_off, page);

	sunxi_nfc_hw_ecc_disable(nand);

	वापस nand_prog_page_end_op(nand);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_ग_लिखो_subpage(काष्ठा nand_chip *nand,
					  u32 data_offs, u32 data_len,
					  स्थिर u8 *buf, पूर्णांक oob_required,
					  पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	पूर्णांक ret, i, cur_off = 0;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_prog_page_begin_op(nand, page, 0, शून्य, 0);

	sunxi_nfc_hw_ecc_enable(nand);

	क्रम (i = data_offs / ecc->size;
	     i < DIV_ROUND_UP(data_offs + data_len, ecc->size); i++) अणु
		पूर्णांक data_off = i * ecc->size;
		पूर्णांक oob_off = i * (ecc->bytes + 4);
		स्थिर u8 *data = buf + data_off;
		स्थिर u8 *oob = nand->oob_poi + oob_off;

		ret = sunxi_nfc_hw_ecc_ग_लिखो_chunk(nand, data, data_off, oob,
						   oob_off + mtd->ग_लिखोsize,
						   &cur_off, !i, page);
		अगर (ret)
			वापस ret;
	पूर्ण

	sunxi_nfc_hw_ecc_disable(nand);

	वापस nand_prog_page_end_op(nand);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_ग_लिखो_page_dma(काष्ठा nand_chip *nand,
					   स्थिर u8 *buf,
					   पूर्णांक oob_required,
					   पूर्णांक page)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	काष्ठा scatterlist sg;
	u32 रुको;
	पूर्णांक ret, i;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
	अगर (ret)
		वापस ret;

	ret = sunxi_nfc_dma_op_prepare(nfc, buf, ecc->size, ecc->steps,
				       DMA_TO_DEVICE, &sg);
	अगर (ret)
		जाओ pio_fallback;

	क्रम (i = 0; i < ecc->steps; i++) अणु
		स्थिर u8 *oob = nand->oob_poi + (i * (ecc->bytes + 4));

		sunxi_nfc_hw_ecc_set_prot_oob_bytes(nand, oob, i, !i, page);
	पूर्ण

	nand_prog_page_begin_op(nand, page, 0, शून्य, 0);

	sunxi_nfc_hw_ecc_enable(nand);
	sunxi_nfc_अक्रमomizer_config(nand, page, false);
	sunxi_nfc_अक्रमomizer_enable(nand);

	ग_लिखोl((न_अंकD_CMD_RNDIN << 8) | न_अंकD_CMD_PAGEPROG,
	       nfc->regs + NFC_REG_WCMD_SET);

	रुको = NFC_CMD_INT_FLAG;

	अगर (nfc->caps->has_mdma)
		रुको |= NFC_DMA_INT_FLAG;
	अन्यथा
		dma_async_issue_pending(nfc->dmac);

	ग_लिखोl(NFC_PAGE_OP | NFC_DATA_SWAP_METHOD |
	       NFC_DATA_TRANS | NFC_ACCESS_सूची,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_रुको_events(nfc, रुको, false, 0);
	अगर (ret && !nfc->caps->has_mdma)
		dmaengine_terminate_all(nfc->dmac);

	sunxi_nfc_अक्रमomizer_disable(nand);
	sunxi_nfc_hw_ecc_disable(nand);

	sunxi_nfc_dma_op_cleanup(nfc, DMA_TO_DEVICE, &sg);

	अगर (ret)
		वापस ret;

	अगर (oob_required || (nand->options & न_अंकD_NEED_SCRAMBLING))
		/* TODO: use DMA to transfer extra OOB bytes ? */
		sunxi_nfc_hw_ecc_ग_लिखो_extra_oob(nand, nand->oob_poi,
						 शून्य, page);

	वापस nand_prog_page_end_op(nand);

pio_fallback:
	वापस sunxi_nfc_hw_ecc_ग_लिखो_page(nand, buf, oob_required, page);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_पढ़ो_oob(काष्ठा nand_chip *nand, पूर्णांक page)
अणु
	u8 *buf = nand_get_data_buf(nand);

	वापस nand->ecc.पढ़ो_page(nand, buf, 1, page);
पूर्ण

अटल पूर्णांक sunxi_nfc_hw_ecc_ग_लिखो_oob(काष्ठा nand_chip *nand, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	u8 *buf = nand_get_data_buf(nand);
	पूर्णांक ret;

	स_रखो(buf, 0xff, mtd->ग_लिखोsize);
	ret = nand->ecc.ग_लिखो_page(nand, buf, 1, page);
	अगर (ret)
		वापस ret;

	/* Send command to program the OOB data */
	वापस nand_prog_page_end_op(nand);
पूर्ण

अटल स्थिर s32 tWB_lut[] = अणु6, 12, 16, 20पूर्ण;
अटल स्थिर s32 tRHW_lut[] = अणु4, 8, 12, 20पूर्ण;

अटल पूर्णांक _sunxi_nand_lookup_timing(स्थिर s32 *lut, पूर्णांक lut_size, u32 duration,
		u32 clk_period)
अणु
	u32 clk_cycles = DIV_ROUND_UP(duration, clk_period);
	पूर्णांक i;

	क्रम (i = 0; i < lut_size; i++) अणु
		अगर (clk_cycles <= lut[i])
			वापस i;
	पूर्ण

	/* Doesn't fit */
	वापस -EINVAL;
पूर्ण

#घोषणा sunxi_nand_lookup_timing(l, p, c) \
			_sunxi_nand_lookup_timing(l, ARRAY_SIZE(l), p, c)

अटल पूर्णांक sunxi_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *nand, पूर्णांक csline,
				     स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(sunxi_nand->nand.controller);
	स्थिर काष्ठा nand_sdr_timings *timings;
	u32 min_clk_period = 0;
	s32 tWB, tADL, tWHR, tRHW, tCAD;
	दीर्घ real_clk_rate;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस -ENOTSUPP;

	/* T1 <=> tCLS */
	अगर (timings->tCLS_min > min_clk_period)
		min_clk_period = timings->tCLS_min;

	/* T2 <=> tCLH */
	अगर (timings->tCLH_min > min_clk_period)
		min_clk_period = timings->tCLH_min;

	/* T3 <=> tCS */
	अगर (timings->tCS_min > min_clk_period)
		min_clk_period = timings->tCS_min;

	/* T4 <=> tCH */
	अगर (timings->tCH_min > min_clk_period)
		min_clk_period = timings->tCH_min;

	/* T5 <=> tWP */
	अगर (timings->tWP_min > min_clk_period)
		min_clk_period = timings->tWP_min;

	/* T6 <=> tWH */
	अगर (timings->tWH_min > min_clk_period)
		min_clk_period = timings->tWH_min;

	/* T7 <=> tALS */
	अगर (timings->tALS_min > min_clk_period)
		min_clk_period = timings->tALS_min;

	/* T8 <=> tDS */
	अगर (timings->tDS_min > min_clk_period)
		min_clk_period = timings->tDS_min;

	/* T9 <=> tDH */
	अगर (timings->tDH_min > min_clk_period)
		min_clk_period = timings->tDH_min;

	/* T10 <=> tRR */
	अगर (timings->tRR_min > (min_clk_period * 3))
		min_clk_period = DIV_ROUND_UP(timings->tRR_min, 3);

	/* T11 <=> tALH */
	अगर (timings->tALH_min > min_clk_period)
		min_clk_period = timings->tALH_min;

	/* T12 <=> tRP */
	अगर (timings->tRP_min > min_clk_period)
		min_clk_period = timings->tRP_min;

	/* T13 <=> tREH */
	अगर (timings->tREH_min > min_clk_period)
		min_clk_period = timings->tREH_min;

	/* T14 <=> tRC */
	अगर (timings->tRC_min > (min_clk_period * 2))
		min_clk_period = DIV_ROUND_UP(timings->tRC_min, 2);

	/* T15 <=> tWC */
	अगर (timings->tWC_min > (min_clk_period * 2))
		min_clk_period = DIV_ROUND_UP(timings->tWC_min, 2);

	/* T16 - T19 + tCAD */
	अगर (timings->tWB_max > (min_clk_period * 20))
		min_clk_period = DIV_ROUND_UP(timings->tWB_max, 20);

	अगर (timings->tADL_min > (min_clk_period * 32))
		min_clk_period = DIV_ROUND_UP(timings->tADL_min, 32);

	अगर (timings->tWHR_min > (min_clk_period * 32))
		min_clk_period = DIV_ROUND_UP(timings->tWHR_min, 32);

	अगर (timings->tRHW_min > (min_clk_period * 20))
		min_clk_period = DIV_ROUND_UP(timings->tRHW_min, 20);

	/*
	 * In non-EDO, tREA should be less than tRP to guarantee that the
	 * controller करोes not sample the IO lines too early. Unक्रमtunately,
	 * the sunxi न_अंकD controller करोes not allow us to have dअगरferent
	 * values क्रम tRP and tREH (tRP = tREH = tRW / 2).
	 *
	 * We have 2 options to overcome this limitation:
	 *
	 * 1/ Extend tRC to fulfil the tREA <= tRC / 2 स्थिरraपूर्णांक
	 * 2/ Use EDO mode (only works अगर timings->tRLOH > 0)
	 */
	अगर (timings->tREA_max > min_clk_period && !timings->tRLOH_min)
		min_clk_period = timings->tREA_max;

	tWB  = sunxi_nand_lookup_timing(tWB_lut, timings->tWB_max,
					min_clk_period);
	अगर (tWB < 0) अणु
		dev_err(nfc->dev, "unsupported tWB\n");
		वापस tWB;
	पूर्ण

	tADL = DIV_ROUND_UP(timings->tADL_min, min_clk_period) >> 3;
	अगर (tADL > 3) अणु
		dev_err(nfc->dev, "unsupported tADL\n");
		वापस -EINVAL;
	पूर्ण

	tWHR = DIV_ROUND_UP(timings->tWHR_min, min_clk_period) >> 3;
	अगर (tWHR > 3) अणु
		dev_err(nfc->dev, "unsupported tWHR\n");
		वापस -EINVAL;
	पूर्ण

	tRHW = sunxi_nand_lookup_timing(tRHW_lut, timings->tRHW_min,
					min_clk_period);
	अगर (tRHW < 0) अणु
		dev_err(nfc->dev, "unsupported tRHW\n");
		वापस tRHW;
	पूर्ण

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	/*
	 * TODO: according to ONFI specs this value only applies क्रम DDR न_अंकD,
	 * but Allwinner seems to set this to 0x7. Mimic them क्रम now.
	 */
	tCAD = 0x7;

	/* TODO: A83 has some more bits क्रम CDQSS, CS, CLHZ, CCS, WC */
	sunxi_nand->timing_cfg = NFC_TIMING_CFG(tWB, tADL, tWHR, tRHW, tCAD);

	/* Convert min_clk_period from picoseconds to nanoseconds */
	min_clk_period = DIV_ROUND_UP(min_clk_period, 1000);

	/*
	 * Unlike what is stated in Allwinner datasheet, the clk_rate should
	 * be set to (1 / min_clk_period), and not (2 / min_clk_period).
	 * This new क्रमmula was verअगरied with a scope and validated by
	 * Allwinner engineers.
	 */
	sunxi_nand->clk_rate = NSEC_PER_SEC / min_clk_period;
	real_clk_rate = clk_round_rate(nfc->mod_clk, sunxi_nand->clk_rate);
	अगर (real_clk_rate <= 0) अणु
		dev_err(nfc->dev, "Unable to round clk %lu\n",
			sunxi_nand->clk_rate);
		वापस -EINVAL;
	पूर्ण

	sunxi_nand->timing_ctl = 0;

	/*
	 * ONFI specअगरication 3.1, paragraph 4.15.2 dictates that EDO data
	 * output cycle timings shall be used अगर the host drives tRC less than
	 * 30 ns. We should also use EDO mode अगर tREA is bigger than tRP.
	 */
	min_clk_period = NSEC_PER_SEC / real_clk_rate;
	अगर (min_clk_period * 2 < 30 || min_clk_period * 1000 < timings->tREA_max)
		sunxi_nand->timing_ctl = NFC_TIMING_CTL_EDO;

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_nand_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				    काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;

	अगर (section >= ecc->steps)
		वापस -दुस्फल;

	oobregion->offset = section * (ecc->bytes + 4) + 4;
	oobregion->length = ecc->bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_nand_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				     काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;

	अगर (section > ecc->steps)
		वापस -दुस्फल;

	/*
	 * The first 2 bytes are used क्रम BB markers, hence we
	 * only have 2 bytes available in the first user data
	 * section.
	 */
	अगर (!section && ecc->engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		oobregion->offset = 2;
		oobregion->length = 2;

		वापस 0;
	पूर्ण

	oobregion->offset = section * (ecc->bytes + 4);

	अगर (section < ecc->steps)
		oobregion->length = 4;
	अन्यथा
		oobregion->offset = mtd->oobsize - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops sunxi_nand_ooblayout_ops = अणु
	.ecc = sunxi_nand_ooblayout_ecc,
	.मुक्त = sunxi_nand_ooblayout_मुक्त,
पूर्ण;

अटल व्योम sunxi_nand_hw_ecc_ctrl_cleanup(काष्ठा sunxi_nand_chip *sunxi_nand)
अणु
	kमुक्त(sunxi_nand->ecc);
पूर्ण

अटल पूर्णांक sunxi_nand_hw_ecc_ctrl_init(काष्ठा nand_chip *nand,
				       काष्ठा nand_ecc_ctrl *ecc,
				       काष्ठा device_node *np)
अणु
	अटल स्थिर u8 strengths[] = अणु 16, 24, 28, 32, 40, 48, 56, 60, 64 पूर्ण;
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा nand_device *nanddev = mtd_to_nanddev(mtd);
	पूर्णांक nsectors;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (nanddev->ecc.user_conf.flags & न_अंकD_ECC_MAXIMIZE_STRENGTH) अणु
		पूर्णांक bytes;

		ecc->size = 1024;
		nsectors = mtd->ग_लिखोsize / ecc->size;

		/* Reserve 2 bytes क्रम the BBM */
		bytes = (mtd->oobsize - 2) / nsectors;

		/* 4 non-ECC bytes are added beक्रमe each ECC bytes section */
		bytes -= 4;

		/* and bytes has to be even. */
		अगर (bytes % 2)
			bytes--;

		ecc->strength = bytes * 8 / fls(8 * ecc->size);

		क्रम (i = 0; i < ARRAY_SIZE(strengths); i++) अणु
			अगर (strengths[i] > ecc->strength)
				अवरोध;
		पूर्ण

		अगर (!i)
			ecc->strength = 0;
		अन्यथा
			ecc->strength = strengths[i - 1];
	पूर्ण

	अगर (ecc->size != 512 && ecc->size != 1024)
		वापस -EINVAL;

	sunxi_nand->ecc = kzalloc(माप(*sunxi_nand->ecc), GFP_KERNEL);
	अगर (!sunxi_nand->ecc)
		वापस -ENOMEM;

	/* Prefer 1k ECC chunk over 512 ones */
	अगर (ecc->size == 512 && mtd->ग_लिखोsize > 512) अणु
		ecc->size = 1024;
		ecc->strength *= 2;
	पूर्ण

	/* Add ECC info retrieval from DT */
	क्रम (i = 0; i < ARRAY_SIZE(strengths); i++) अणु
		अगर (ecc->strength <= strengths[i]) अणु
			/*
			 * Update ecc->strength value with the actual strength
			 * that will be used by the ECC engine.
			 */
			ecc->strength = strengths[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(strengths)) अणु
		dev_err(nfc->dev, "unsupported strength\n");
		ret = -ENOTSUPP;
		जाओ err;
	पूर्ण

	sunxi_nand->ecc->mode = i;

	/* HW ECC always request ECC bytes क्रम 1024 bytes blocks */
	ecc->bytes = DIV_ROUND_UP(ecc->strength * fls(8 * 1024), 8);

	/* HW ECC always work with even numbers of ECC bytes */
	ecc->bytes = ALIGN(ecc->bytes, 2);

	nsectors = mtd->ग_लिखोsize / ecc->size;

	अगर (mtd->oobsize < ((ecc->bytes + 4) * nsectors)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ecc->पढ़ो_oob = sunxi_nfc_hw_ecc_पढ़ो_oob;
	ecc->ग_लिखो_oob = sunxi_nfc_hw_ecc_ग_लिखो_oob;
	mtd_set_ooblayout(mtd, &sunxi_nand_ooblayout_ops);

	अगर (nfc->dmac || nfc->caps->has_mdma) अणु
		ecc->पढ़ो_page = sunxi_nfc_hw_ecc_पढ़ो_page_dma;
		ecc->पढ़ो_subpage = sunxi_nfc_hw_ecc_पढ़ो_subpage_dma;
		ecc->ग_लिखो_page = sunxi_nfc_hw_ecc_ग_लिखो_page_dma;
		nand->options |= न_अंकD_USES_DMA;
	पूर्ण अन्यथा अणु
		ecc->पढ़ो_page = sunxi_nfc_hw_ecc_पढ़ो_page;
		ecc->पढ़ो_subpage = sunxi_nfc_hw_ecc_पढ़ो_subpage;
		ecc->ग_लिखो_page = sunxi_nfc_hw_ecc_ग_लिखो_page;
	पूर्ण

	/* TODO: support DMA क्रम raw accesses and subpage ग_लिखो */
	ecc->ग_लिखो_subpage = sunxi_nfc_hw_ecc_ग_लिखो_subpage;
	ecc->पढ़ो_oob_raw = nand_पढ़ो_oob_std;
	ecc->ग_लिखो_oob_raw = nand_ग_लिखो_oob_std;

	वापस 0;

err:
	kमुक्त(sunxi_nand->ecc);

	वापस ret;
पूर्ण

अटल व्योम sunxi_nand_ecc_cleanup(काष्ठा sunxi_nand_chip *sunxi_nand)
अणु
	काष्ठा nand_ecc_ctrl *ecc = &sunxi_nand->nand.ecc;

	चयन (ecc->engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		sunxi_nand_hw_ecc_ctrl_cleanup(sunxi_nand);
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sunxi_nand_attach_chip(काष्ठा nand_chip *nand)
अणु
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&nand->base);
	काष्ठा nand_ecc_ctrl *ecc = &nand->ecc;
	काष्ठा device_node *np = nand_get_flash_node(nand);
	पूर्णांक ret;

	अगर (nand->bbt_options & न_अंकD_BBT_USE_FLASH)
		nand->bbt_options |= न_अंकD_BBT_NO_OOB;

	अगर (nand->options & न_अंकD_NEED_SCRAMBLING)
		nand->options |= न_अंकD_NO_SUBPAGE_WRITE;

	nand->options |= न_अंकD_SUBPAGE_READ;

	अगर (!ecc->size) अणु
		ecc->size = requirements->step_size;
		ecc->strength = requirements->strength;
	पूर्ण

	अगर (!ecc->size || !ecc->strength)
		वापस -EINVAL;

	चयन (ecc->engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		ret = sunxi_nand_hw_ecc_ctrl_init(nand, ecc, np);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_nfc_exec_subop(काष्ठा nand_chip *nand,
				स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	u32 cmd = 0, extcmd = 0, cnt = 0, addrs[2] = अणु पूर्ण;
	अचिन्हित पूर्णांक i, j, reमुख्यing, start;
	व्योम *inbuf = शून्य;
	पूर्णांक ret;

	क्रम (i = 0; i < subop->ninstrs; i++) अणु
		स्थिर काष्ठा nand_op_instr *instr = &subop->instrs[i];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			अगर (cmd & NFC_SEND_CMD1) अणु
				अगर (WARN_ON(cmd & NFC_SEND_CMD2))
					वापस -EINVAL;

				cmd |= NFC_SEND_CMD2;
				extcmd |= instr->ctx.cmd.opcode;
			पूर्ण अन्यथा अणु
				cmd |= NFC_SEND_CMD1 |
				       NFC_CMD(instr->ctx.cmd.opcode);
			पूर्ण
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			reमुख्यing = nand_subop_get_num_addr_cyc(subop, i);
			start = nand_subop_get_addr_start_off(subop, i);
			क्रम (j = 0; j < 8 && j + start < reमुख्यing; j++) अणु
				u32 addr = instr->ctx.addr.addrs[j + start];

				addrs[j / 4] |= addr << (j % 4) * 8;
			पूर्ण

			अगर (j)
				cmd |= NFC_SEND_ADR | NFC_ADR_NUM(j);

			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
		हाल न_अंकD_OP_DATA_OUT_INSTR:
			start = nand_subop_get_data_start_off(subop, i);
			reमुख्यing = nand_subop_get_data_len(subop, i);
			cnt = min_t(u32, reमुख्यing, NFC_SRAM_SIZE);
			cmd |= NFC_DATA_TRANS | NFC_DATA_SWAP_METHOD;

			अगर (instr->type == न_अंकD_OP_DATA_OUT_INSTR) अणु
				cmd |= NFC_ACCESS_सूची;
				स_नकल_toio(nfc->regs + NFC_RAM0_BASE,
					    instr->ctx.data.buf.out + start,
					    cnt);
			पूर्ण अन्यथा अणु
				inbuf = instr->ctx.data.buf.in + start;
			पूर्ण

			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			cmd |= NFC_WAIT_FLAG;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = sunxi_nfc_रुको_cmd_fअगरo_empty(nfc);
	अगर (ret)
		वापस ret;

	अगर (cmd & NFC_SEND_ADR) अणु
		ग_लिखोl(addrs[0], nfc->regs + NFC_REG_ADDR_LOW);
		ग_लिखोl(addrs[1], nfc->regs + NFC_REG_ADDR_HIGH);
	पूर्ण

	अगर (cmd & NFC_SEND_CMD2)
		ग_लिखोl(extcmd,
		       nfc->regs +
		       (cmd & NFC_ACCESS_सूची ?
			NFC_REG_WCMD_SET : NFC_REG_RCMD_SET));

	अगर (cmd & NFC_DATA_TRANS)
		ग_लिखोl(cnt, nfc->regs + NFC_REG_CNT);

	ग_लिखोl(cmd, nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_रुको_events(nfc, NFC_CMD_INT_FLAG,
				    !(cmd & NFC_WAIT_FLAG) && cnt < 64,
				    0);
	अगर (ret)
		वापस ret;

	अगर (inbuf)
		स_नकल_fromio(inbuf, nfc->regs + NFC_RAM0_BASE, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_nfc_soft_रुकोrdy(काष्ठा nand_chip *nand,
				  स्थिर काष्ठा nand_subop *subop)
अणु
	वापस nand_soft_रुकोrdy(nand,
				 subop->instrs[0].ctx.रुकोrdy.समयout_ms);
पूर्ण

अटल स्थिर काष्ठा nand_op_parser sunxi_nfc_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(sunxi_nfc_exec_subop,
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 8),
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(true, 1024)),
	न_अंकD_OP_PARSER_PATTERN(sunxi_nfc_exec_subop,
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 8),
			       न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(true, 1024),
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true)),
);

अटल स्थिर काष्ठा nand_op_parser sunxi_nfc_norb_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(sunxi_nfc_exec_subop,
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 8),
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(true, 1024)),
	न_अंकD_OP_PARSER_PATTERN(sunxi_nfc_exec_subop,
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
			       न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, 8),
			       न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(true, 1024),
			       न_अंकD_OP_PARSER_PAT_CMD_ELEM(true)),
	न_अंकD_OP_PARSER_PATTERN(sunxi_nfc_soft_रुकोrdy,
			       न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
);

अटल पूर्णांक sunxi_nfc_exec_op(काष्ठा nand_chip *nand,
			     स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand = to_sunxi_nand(nand);
	स्थिर काष्ठा nand_op_parser *parser;

	अगर (!check_only)
		sunxi_nfc_select_chip(nand, op->cs);

	अगर (sunxi_nand->sels[op->cs].rb >= 0)
		parser = &sunxi_nfc_op_parser;
	अन्यथा
		parser = &sunxi_nfc_norb_op_parser;

	वापस nand_op_parser_exec_op(nand, parser, op, check_only);
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops sunxi_nand_controller_ops = अणु
	.attach_chip = sunxi_nand_attach_chip,
	.setup_पूर्णांकerface = sunxi_nfc_setup_पूर्णांकerface,
	.exec_op = sunxi_nfc_exec_op,
पूर्ण;

अटल पूर्णांक sunxi_nand_chip_init(काष्ठा device *dev, काष्ठा sunxi_nfc *nfc,
				काष्ठा device_node *np)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *nand;
	पूर्णांक nsels;
	पूर्णांक ret;
	पूर्णांक i;
	u32 पंचांगp;

	अगर (!of_get_property(np, "reg", &nsels))
		वापस -EINVAL;

	nsels /= माप(u32);
	अगर (!nsels) अणु
		dev_err(dev, "invalid reg property size\n");
		वापस -EINVAL;
	पूर्ण

	sunxi_nand = devm_kzalloc(dev, काष्ठा_size(sunxi_nand, sels, nsels),
				  GFP_KERNEL);
	अगर (!sunxi_nand) अणु
		dev_err(dev, "could not allocate chip\n");
		वापस -ENOMEM;
	पूर्ण

	sunxi_nand->nsels = nsels;

	क्रम (i = 0; i < nsels; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "reg", i, &पंचांगp);
		अगर (ret) अणु
			dev_err(dev, "could not retrieve reg property: %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (पंचांगp > NFC_MAX_CS) अणु
			dev_err(dev,
				"invalid reg value: %u (max CS = 7)\n",
				पंचांगp);
			वापस -EINVAL;
		पूर्ण

		अगर (test_and_set_bit(पंचांगp, &nfc->asचिन्हित_cs)) अणु
			dev_err(dev, "CS %d already assigned\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण

		sunxi_nand->sels[i].cs = पंचांगp;

		अगर (!of_property_पढ़ो_u32_index(np, "allwinner,rb", i, &पंचांगp) &&
		    पंचांगp < 2)
			sunxi_nand->sels[i].rb = पंचांगp;
		अन्यथा
			sunxi_nand->sels[i].rb = -1;
	पूर्ण

	nand = &sunxi_nand->nand;
	/* Default tR value specअगरied in the ONFI spec (chapter 4.15.1) */
	nand->controller = &nfc->controller;
	nand->controller->ops = &sunxi_nand_controller_ops;

	/*
	 * Set the ECC mode to the शेष value in हाल nothing is specअगरied
	 * in the DT.
	 */
	nand->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	nand_set_flash_node(nand, np);

	mtd = nand_to_mtd(nand);
	mtd->dev.parent = dev;

	ret = nand_scan(nand, nsels);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to register mtd device: %d\n", ret);
		nand_cleanup(nand);
		वापस ret;
	पूर्ण

	list_add_tail(&sunxi_nand->node, &nfc->chips);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_nand_chips_init(काष्ठा device *dev, काष्ठा sunxi_nfc *nfc)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *nand_np;
	पूर्णांक nchips = of_get_child_count(np);
	पूर्णांक ret;

	अगर (nchips > 8) अणु
		dev_err(dev, "too many NAND chips: %d (max = 8)\n", nchips);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = sunxi_nand_chip_init(dev, nfc, nand_np);
		अगर (ret) अणु
			of_node_put(nand_np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sunxi_nand_chips_cleanup(काष्ठा sunxi_nfc *nfc)
अणु
	काष्ठा sunxi_nand_chip *sunxi_nand;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	जबतक (!list_empty(&nfc->chips)) अणु
		sunxi_nand = list_first_entry(&nfc->chips,
					      काष्ठा sunxi_nand_chip,
					      node);
		chip = &sunxi_nand->nand;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		sunxi_nand_ecc_cleanup(sunxi_nand);
		list_del(&sunxi_nand->node);
	पूर्ण
पूर्ण

अटल पूर्णांक sunxi_nfc_dma_init(काष्ठा sunxi_nfc *nfc, काष्ठा resource *r)
अणु
	पूर्णांक ret;

	अगर (nfc->caps->has_mdma)
		वापस 0;

	nfc->dmac = dma_request_chan(nfc->dev, "rxtx");
	अगर (IS_ERR(nfc->dmac)) अणु
		ret = PTR_ERR(nfc->dmac);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		/* Ignore errors to fall back to PIO mode */
		dev_warn(nfc->dev, "failed to request rxtx DMA channel: %d\n", ret);
		nfc->dmac = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा dma_slave_config dmac_cfg = अणु पूर्ण;

		dmac_cfg.src_addr = r->start + nfc->caps->reg_io_data;
		dmac_cfg.dst_addr = dmac_cfg.src_addr;
		dmac_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dmac_cfg.dst_addr_width = dmac_cfg.src_addr_width;
		dmac_cfg.src_maxburst = nfc->caps->dma_maxburst;
		dmac_cfg.dst_maxburst = nfc->caps->dma_maxburst;
		dmaengine_slave_config(nfc->dmac, &dmac_cfg);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *r;
	काष्ठा sunxi_nfc *nfc;
	पूर्णांक irq;
	पूर्णांक ret;

	nfc = devm_kzalloc(dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->dev = dev;
	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nfc->regs = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(nfc->regs))
		वापस PTR_ERR(nfc->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	nfc->ahb_clk = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(nfc->ahb_clk)) अणु
		dev_err(dev, "failed to retrieve ahb clk\n");
		वापस PTR_ERR(nfc->ahb_clk);
	पूर्ण

	ret = clk_prepare_enable(nfc->ahb_clk);
	अगर (ret)
		वापस ret;

	nfc->mod_clk = devm_clk_get(dev, "mod");
	अगर (IS_ERR(nfc->mod_clk)) अणु
		dev_err(dev, "failed to retrieve mod clk\n");
		ret = PTR_ERR(nfc->mod_clk);
		जाओ out_ahb_clk_unprepare;
	पूर्ण

	ret = clk_prepare_enable(nfc->mod_clk);
	अगर (ret)
		जाओ out_ahb_clk_unprepare;

	nfc->reset = devm_reset_control_get_optional_exclusive(dev, "ahb");
	अगर (IS_ERR(nfc->reset)) अणु
		ret = PTR_ERR(nfc->reset);
		जाओ out_mod_clk_unprepare;
	पूर्ण

	ret = reset_control_deनिश्चित(nfc->reset);
	अगर (ret) अणु
		dev_err(dev, "reset err %d\n", ret);
		जाओ out_mod_clk_unprepare;
	पूर्ण

	nfc->caps = of_device_get_match_data(&pdev->dev);
	अगर (!nfc->caps) अणु
		ret = -EINVAL;
		जाओ out_ahb_reset_reनिश्चित;
	पूर्ण

	ret = sunxi_nfc_rst(nfc);
	अगर (ret)
		जाओ out_ahb_reset_reनिश्चित;

	ग_लिखोl(0, nfc->regs + NFC_REG_INT);
	ret = devm_request_irq(dev, irq, sunxi_nfc_पूर्णांकerrupt,
			       0, "sunxi-nand", nfc);
	अगर (ret)
		जाओ out_ahb_reset_reनिश्चित;

	ret = sunxi_nfc_dma_init(nfc, r);

	अगर (ret)
		जाओ out_ahb_reset_reनिश्चित;

	platक्रमm_set_drvdata(pdev, nfc);

	ret = sunxi_nand_chips_init(dev, nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to init nand chips\n");
		जाओ out_release_dmac;
	पूर्ण

	वापस 0;

out_release_dmac:
	अगर (nfc->dmac)
		dma_release_channel(nfc->dmac);
out_ahb_reset_reनिश्चित:
	reset_control_निश्चित(nfc->reset);
out_mod_clk_unprepare:
	clk_disable_unprepare(nfc->mod_clk);
out_ahb_clk_unprepare:
	clk_disable_unprepare(nfc->ahb_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_nfc *nfc = platक्रमm_get_drvdata(pdev);

	sunxi_nand_chips_cleanup(nfc);

	reset_control_निश्चित(nfc->reset);

	अगर (nfc->dmac)
		dma_release_channel(nfc->dmac);
	clk_disable_unprepare(nfc->mod_clk);
	clk_disable_unprepare(nfc->ahb_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sunxi_nfc_caps sunxi_nfc_a10_caps = अणु
	.reg_io_data = NFC_REG_A10_IO_DATA,
	.dma_maxburst = 4,
पूर्ण;

अटल स्थिर काष्ठा sunxi_nfc_caps sunxi_nfc_a23_caps = अणु
	.has_mdma = true,
	.reg_io_data = NFC_REG_A23_IO_DATA,
	.dma_maxburst = 8,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_nfc_ids[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-nand",
		.data = &sunxi_nfc_a10_caps,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a23-nand-controller",
		.data = &sunxi_nfc_a23_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_nfc_ids);

अटल काष्ठा platक्रमm_driver sunxi_nfc_driver = अणु
	.driver = अणु
		.name = "sunxi_nand",
		.of_match_table = sunxi_nfc_ids,
	पूर्ण,
	.probe = sunxi_nfc_probe,
	.हटाओ = sunxi_nfc_हटाओ,
पूर्ण;
module_platक्रमm_driver(sunxi_nfc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Boris BREZILLON");
MODULE_DESCRIPTION("Allwinner NAND Flash Controller driver");
MODULE_ALIAS("platform:sunxi_nand");
