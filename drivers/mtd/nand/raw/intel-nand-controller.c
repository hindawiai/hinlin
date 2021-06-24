<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2020 Intel Corporation. */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा EBU_CLC			0x000
#घोषणा EBU_CLC_RST		0x00000000u

#घोषणा EBU_ADDR_SEL(n)		(0x020 + (n) * 4)
/* 5 bits 26:22 included क्रम comparison in the ADDR_SELx */
#घोषणा EBU_ADDR_MASK(x)	((x) << 4)
#घोषणा EBU_ADDR_SEL_REGEN	0x1

#घोषणा EBU_BUSCON(n)		(0x060 + (n) * 4)
#घोषणा EBU_BUSCON_CMULT_V4	0x1
#घोषणा EBU_BUSCON_RECOVC(n)	((n) << 2)
#घोषणा EBU_BUSCON_HOLDC(n)	((n) << 4)
#घोषणा EBU_BUSCON_WAITRDC(n)	((n) << 6)
#घोषणा EBU_BUSCON_WAITWRC(n)	((n) << 8)
#घोषणा EBU_BUSCON_BCGEN_CS	0x0
#घोषणा EBU_BUSCON_SETUP_EN	BIT(22)
#घोषणा EBU_BUSCON_ALEC		0xC000

#घोषणा EBU_CON			0x0B0
#घोषणा EBU_CON_न_अंकDM_EN	BIT(0)
#घोषणा EBU_CON_न_अंकDM_DIS	0x0
#घोषणा EBU_CON_CSMUX_E_EN	BIT(1)
#घोषणा EBU_CON_ALE_P_LOW	BIT(2)
#घोषणा EBU_CON_CLE_P_LOW	BIT(3)
#घोषणा EBU_CON_CS_P_LOW	BIT(4)
#घोषणा EBU_CON_SE_P_LOW	BIT(5)
#घोषणा EBU_CON_WP_P_LOW	BIT(6)
#घोषणा EBU_CON_PRE_P_LOW	BIT(7)
#घोषणा EBU_CON_IN_CS_S(n)	((n) << 8)
#घोषणा EBU_CON_OUT_CS_S(n)	((n) << 10)
#घोषणा EBU_CON_LAT_EN_CS_P	((0x3D) << 18)

#घोषणा EBU_WAIT		0x0B4
#घोषणा EBU_WAIT_RDBY		BIT(0)
#घोषणा EBU_WAIT_WR_C		BIT(3)

#घोषणा HSन_अंकD_CTL1		0x110
#घोषणा HSन_अंकD_CTL1_ADDR_SHIFT	24

#घोषणा HSन_अंकD_CTL2		0x114
#घोषणा HSन_अंकD_CTL2_ADDR_SHIFT	8
#घोषणा HSन_अंकD_CTL2_CYC_N_V5	(0x2 << 16)

#घोषणा HSन_अंकD_INT_MSK_CTL	0x124
#घोषणा HSन_अंकD_INT_MSK_CTL_WR_C	BIT(4)

#घोषणा HSन_अंकD_INT_STA		0x128
#घोषणा HSन_अंकD_INT_STA_WR_C	BIT(4)

#घोषणा HSन_अंकD_CTL		0x130
#घोषणा HSन_अंकD_CTL_ENABLE_ECC	BIT(0)
#घोषणा HSन_अंकD_CTL_GO		BIT(2)
#घोषणा HSन_अंकD_CTL_CE_SEL_CS(n)	BIT(3 + (n))
#घोषणा HSन_अंकD_CTL_RW_READ	0x0
#घोषणा HSन_अंकD_CTL_RW_WRITE	BIT(10)
#घोषणा HSन_अंकD_CTL_ECC_OFF_V8TH	BIT(11)
#घोषणा HSन_अंकD_CTL_CKFF_EN	0x0
#घोषणा HSन_अंकD_CTL_MSG_EN	BIT(17)

#घोषणा HSन_अंकD_PARA0		0x13c
#घोषणा HSन_अंकD_PARA0_PAGE_V8192	0x3
#घोषणा HSन_अंकD_PARA0_PIB_V256	(0x3 << 4)
#घोषणा HSन_अंकD_PARA0_BYP_EN_NP	0x0
#घोषणा HSन_अंकD_PARA0_BYP_DEC_NP	0x0
#घोषणा HSन_अंकD_PARA0_TYPE_ONFI	BIT(18)
#घोषणा HSन_अंकD_PARA0_ADEP_EN	BIT(21)

#घोषणा HSन_अंकD_CMSG_0		0x150
#घोषणा HSन_अंकD_CMSG_1		0x154

#घोषणा HSन_अंकD_ALE_OFFS		BIT(2)
#घोषणा HSन_अंकD_CLE_OFFS		BIT(3)
#घोषणा HSन_अंकD_CS_OFFS		BIT(4)

#घोषणा HSन_अंकD_ECC_OFFSET	0x008

#घोषणा न_अंकD_DATA_IFACE_CHECK_ONLY	-1

#घोषणा MAX_CS	2

#घोषणा HZ_PER_MHZ	1000000L
#घोषणा USEC_PER_SEC	1000000L

काष्ठा ebu_nand_cs अणु
	व्योम __iomem *chipaddr;
	dma_addr_t nand_pa;
	u32 addr_sel;
पूर्ण;

काष्ठा ebu_nand_controller अणु
	काष्ठा nand_controller controller;
	काष्ठा nand_chip chip;
	काष्ठा device *dev;
	व्योम __iomem *ebu;
	व्योम __iomem *hsnand;
	काष्ठा dma_chan *dma_tx;
	काष्ठा dma_chan *dma_rx;
	काष्ठा completion dma_access_complete;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा clk *clk;
	u32 nd_para0;
	u8 cs_num;
	काष्ठा ebu_nand_cs cs[MAX_CS];
पूर्ण;

अटल अंतरभूत काष्ठा ebu_nand_controller *nand_to_ebu(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा ebu_nand_controller, chip);
पूर्ण

अटल पूर्णांक ebu_nand_रुकोrdy(काष्ठा nand_chip *chip, पूर्णांक समयout_ms)
अणु
	काष्ठा ebu_nand_controller *ctrl = nand_to_ebu(chip);
	u32 status;

	वापस पढ़ोl_poll_समयout(ctrl->ebu + EBU_WAIT, status,
				  (status & EBU_WAIT_RDBY) ||
				  (status & EBU_WAIT_WR_C), 20, समयout_ms);
पूर्ण

अटल u8 ebu_nand_पढ़ोb(काष्ठा nand_chip *chip)
अणु
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);
	u8 cs_num = ebu_host->cs_num;
	u8 val;

	val = पढ़ोb(ebu_host->cs[cs_num].chipaddr + HSन_अंकD_CS_OFFS);
	ebu_nand_रुकोrdy(chip, 1000);
	वापस val;
पूर्ण

अटल व्योम ebu_nand_ग_लिखोb(काष्ठा nand_chip *chip, u32 offset, u8 value)
अणु
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);
	u8 cs_num = ebu_host->cs_num;

	ग_लिखोb(value, ebu_host->cs[cs_num].chipaddr + offset);
	ebu_nand_रुकोrdy(chip, 1000);
पूर्ण

अटल व्योम ebu_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		buf[i] = ebu_nand_पढ़ोb(chip);
पूर्ण

अटल व्योम ebu_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ebu_nand_ग_लिखोb(chip, HSन_अंकD_CS_OFFS, buf[i]);
पूर्ण

अटल व्योम ebu_nand_disable(काष्ठा nand_chip *chip)
अणु
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);

	ग_लिखोl(0, ebu_host->ebu + EBU_CON);
पूर्ण

अटल व्योम ebu_select_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);
	व्योम __iomem *nand_con = ebu_host->ebu + EBU_CON;
	u32 cs = ebu_host->cs_num;

	ग_लिखोl(EBU_CON_न_अंकDM_EN | EBU_CON_CSMUX_E_EN | EBU_CON_CS_P_LOW |
	       EBU_CON_SE_P_LOW | EBU_CON_WP_P_LOW | EBU_CON_PRE_P_LOW |
	       EBU_CON_IN_CS_S(cs) | EBU_CON_OUT_CS_S(cs) |
	       EBU_CON_LAT_EN_CS_P, nand_con);
पूर्ण

अटल पूर्णांक ebu_nand_set_timings(काष्ठा nand_chip *chip, पूर्णांक csline,
				स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा ebu_nand_controller *ctrl = nand_to_ebu(chip);
	अचिन्हित पूर्णांक rate = clk_get_rate(ctrl->clk) / HZ_PER_MHZ;
	अचिन्हित पूर्णांक period = DIV_ROUND_UP(USEC_PER_SEC, rate);
	स्थिर काष्ठा nand_sdr_timings *timings;
	u32 trecov, thold, twrरुको, trdरुको;
	u32 reg = 0;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस PTR_ERR(timings);

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	trecov = DIV_ROUND_UP(max(timings->tREA_max, timings->tREH_min),
			      period);
	reg |= EBU_BUSCON_RECOVC(trecov);

	thold = DIV_ROUND_UP(max(timings->tDH_min, timings->tDS_min), period);
	reg |= EBU_BUSCON_HOLDC(thold);

	trdरुको = DIV_ROUND_UP(max(timings->tRC_min, timings->tREH_min),
			       period);
	reg |= EBU_BUSCON_WAITRDC(trdरुको);

	twrरुको = DIV_ROUND_UP(max(timings->tWC_min, timings->tWH_min), period);
	reg |= EBU_BUSCON_WAITWRC(twrरुको);

	reg |= EBU_BUSCON_CMULT_V4 | EBU_BUSCON_BCGEN_CS | EBU_BUSCON_ALEC |
		EBU_BUSCON_SETUP_EN;

	ग_लिखोl(reg, ctrl->ebu + EBU_BUSCON(ctrl->cs_num));

	वापस 0;
पूर्ण

अटल पूर्णांक ebu_nand_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = HSन_अंकD_ECC_OFFSET;
	oobregion->length = chip->ecc.total;

	वापस 0;
पूर्ण

अटल पूर्णांक ebu_nand_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = chip->ecc.total + HSन_अंकD_ECC_OFFSET;
	oobregion->length = mtd->oobsize - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops ebu_nand_ooblayout_ops = अणु
	.ecc = ebu_nand_ooblayout_ecc,
	.मुक्त = ebu_nand_ooblayout_मुक्त,
पूर्ण;

अटल व्योम ebu_dma_rx_callback(व्योम *cookie)
अणु
	काष्ठा ebu_nand_controller *ebu_host = cookie;

	dmaengine_terminate_async(ebu_host->dma_rx);

	complete(&ebu_host->dma_access_complete);
पूर्ण

अटल व्योम ebu_dma_tx_callback(व्योम *cookie)
अणु
	काष्ठा ebu_nand_controller *ebu_host = cookie;

	dmaengine_terminate_async(ebu_host->dma_tx);

	complete(&ebu_host->dma_access_complete);
पूर्ण

अटल पूर्णांक ebu_dma_start(काष्ठा ebu_nand_controller *ebu_host, u32 dir,
			 स्थिर u8 *buf, u32 len)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा completion *dma_completion;
	dma_async_tx_callback callback;
	काष्ठा dma_chan *chan;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	dma_addr_t buf_dma;
	पूर्णांक ret;
	u32 समयout;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		chan = ebu_host->dma_rx;
		dma_completion = &ebu_host->dma_access_complete;
		callback = ebu_dma_rx_callback;
	पूर्ण अन्यथा अणु
		chan = ebu_host->dma_tx;
		dma_completion = &ebu_host->dma_access_complete;
		callback = ebu_dma_tx_callback;
	पूर्ण

	buf_dma = dma_map_single(chan->device->dev, (व्योम *)buf, len, dir);
	अगर (dma_mapping_error(chan->device->dev, buf_dma)) अणु
		dev_err(ebu_host->dev, "Failed to map DMA buffer\n");
		ret = -EIO;
		जाओ err_unmap;
	पूर्ण

	tx = dmaengine_prep_slave_single(chan, buf_dma, len, dir, flags);
	अगर (!tx) अणु
		ret = -ENXIO;
		जाओ err_unmap;
	पूर्ण

	tx->callback = callback;
	tx->callback_param = ebu_host;
	cookie = tx->tx_submit(tx);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(ebu_host->dev, "dma_submit_error %d\n", cookie);
		ret = -EIO;
		जाओ err_unmap;
	पूर्ण

	init_completion(dma_completion);
	dma_async_issue_pending(chan);

	/* Wait DMA to finish the data transfer.*/
	समयout = रुको_क्रम_completion_समयout(dma_completion, msecs_to_jअगरfies(1000));
	अगर (!समयout) अणु
		dev_err(ebu_host->dev, "I/O Error in DMA RX (status %d)\n",
			dmaengine_tx_status(chan, cookie, शून्य));
		dmaengine_terminate_sync(chan);
		ret = -ETIMEDOUT;
		जाओ err_unmap;
	पूर्ण

	वापस 0;

err_unmap:
	dma_unmap_single(ebu_host->dev, buf_dma, len, dir);

	वापस ret;
पूर्ण

अटल व्योम ebu_nand_trigger(काष्ठा ebu_nand_controller *ebu_host,
			     पूर्णांक page, u32 cmd)
अणु
	अचिन्हित पूर्णांक val;

	val = cmd | (page & 0xFF) << HSन_अंकD_CTL1_ADDR_SHIFT;
	ग_लिखोl(val, ebu_host->hsnand + HSन_अंकD_CTL1);
	val = (page & 0xFFFF00) >> 8 | HSन_अंकD_CTL2_CYC_N_V5;
	ग_लिखोl(val, ebu_host->hsnand + HSन_अंकD_CTL2);

	ग_लिखोl(ebu_host->nd_para0, ebu_host->hsnand + HSन_अंकD_PARA0);

	/* clear first, will update later */
	ग_लिखोl(0xFFFFFFFF, ebu_host->hsnand + HSन_अंकD_CMSG_0);
	ग_लिखोl(0xFFFFFFFF, ebu_host->hsnand + HSन_अंकD_CMSG_1);

	ग_लिखोl(HSन_अंकD_INT_MSK_CTL_WR_C,
	       ebu_host->hsnand + HSन_अंकD_INT_MSK_CTL);

	अगर (!cmd)
		val = HSन_अंकD_CTL_RW_READ;
	अन्यथा
		val = HSन_अंकD_CTL_RW_WRITE;

	ग_लिखोl(HSन_अंकD_CTL_MSG_EN | HSन_अंकD_CTL_CKFF_EN |
	       HSन_अंकD_CTL_ECC_OFF_V8TH | HSन_अंकD_CTL_CE_SEL_CS(ebu_host->cs_num) |
	       HSन_अंकD_CTL_ENABLE_ECC | HSन_अंकD_CTL_GO | val,
	       ebu_host->hsnand + HSन_अंकD_CTL);
पूर्ण

अटल पूर्णांक ebu_nand_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, u8 *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);
	पूर्णांक ret, reg_data;

	ebu_nand_trigger(ebu_host, page, न_अंकD_CMD_READ0);

	ret = ebu_dma_start(ebu_host, DMA_DEV_TO_MEM, buf, mtd->ग_लिखोsize);
	अगर (ret)
		वापस ret;

	अगर (oob_required)
		chip->ecc.पढ़ो_oob(chip, page);

	reg_data = पढ़ोl(ebu_host->hsnand + HSन_अंकD_CTL);
	reg_data &= ~HSन_अंकD_CTL_GO;
	ग_लिखोl(reg_data, ebu_host->hsnand + HSन_अंकD_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक ebu_nand_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				     पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);
	व्योम __iomem *पूर्णांक_sta = ebu_host->hsnand + HSन_अंकD_INT_STA;
	पूर्णांक reg_data, ret, val;
	u32 reg;

	ebu_nand_trigger(ebu_host, page, न_अंकD_CMD_SEQIN);

	ret = ebu_dma_start(ebu_host, DMA_MEM_TO_DEV, buf, mtd->ग_लिखोsize);
	अगर (ret)
		वापस ret;

	अगर (oob_required) अणु
		reg = get_unaligned_le32(chip->oob_poi);
		ग_लिखोl(reg, ebu_host->hsnand + HSन_अंकD_CMSG_0);

		reg = get_unaligned_le32(chip->oob_poi + 4);
		ग_लिखोl(reg, ebu_host->hsnand + HSन_अंकD_CMSG_1);
	पूर्ण

	ret = पढ़ोl_poll_समयout_atomic(पूर्णांक_sta, val, !(val & HSन_अंकD_INT_STA_WR_C),
					10, 1000);
	अगर (ret)
		वापस ret;

	reg_data = पढ़ोl(ebu_host->hsnand + HSन_अंकD_CTL);
	reg_data &= ~HSन_अंकD_CTL_GO;
	ग_लिखोl(reg_data, ebu_host->hsnand + HSन_अंकD_CTL);

	वापस 0;
पूर्ण

अटल स्थिर u8 ecc_strength[] = अणु 1, 1, 4, 8, 24, 32, 40, 60, पूर्ण;

अटल पूर्णांक ebu_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा ebu_nand_controller *ebu_host = nand_get_controller_data(chip);
	u32 ecc_steps, ecc_bytes, ecc_total, pagesize, pg_per_blk;
	u32 ecc_strength_ds = chip->ecc.strength;
	u32 ecc_size = chip->ecc.size;
	u32 ग_लिखोsize = mtd->ग_लिखोsize;
	u32 blocksize = mtd->erasesize;
	पूर्णांक bch_algo, start, val;

	/* Default to an ECC size of 512 */
	अगर (!chip->ecc.size)
		chip->ecc.size = 512;

	चयन (ecc_size) अणु
	हाल 512:
		start = 1;
		अगर (!ecc_strength_ds)
			ecc_strength_ds = 4;
		अवरोध;
	हाल 1024:
		start = 4;
		अगर (!ecc_strength_ds)
			ecc_strength_ds = 32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* BCH ECC algorithm Settings क्रम number of bits per 512B/1024B */
	bch_algo = round_up(start + 1, 4);
	क्रम (val = start; val < bch_algo; val++) अणु
		अगर (ecc_strength_ds == ecc_strength[val])
			अवरोध;
	पूर्ण
	अगर (val == bch_algo)
		वापस -EINVAL;

	अगर (ecc_strength_ds == 8)
		ecc_bytes = 14;
	अन्यथा
		ecc_bytes = DIV_ROUND_UP(ecc_strength_ds * fls(8 * ecc_size), 8);

	ecc_steps = ग_लिखोsize / ecc_size;
	ecc_total = ecc_steps * ecc_bytes;
	अगर ((ecc_total + 8) > mtd->oobsize)
		वापस -दुस्फल;

	chip->ecc.total = ecc_total;
	pagesize = fls(ग_लिखोsize >> 11);
	अगर (pagesize > HSन_अंकD_PARA0_PAGE_V8192)
		वापस -दुस्फल;

	pg_per_blk = fls((blocksize / ग_लिखोsize) >> 6) / 8;
	अगर (pg_per_blk > HSन_अंकD_PARA0_PIB_V256)
		वापस -दुस्फल;

	ebu_host->nd_para0 = pagesize | pg_per_blk | HSन_अंकD_PARA0_BYP_EN_NP |
			     HSन_अंकD_PARA0_BYP_DEC_NP | HSन_अंकD_PARA0_ADEP_EN |
			     HSन_अंकD_PARA0_TYPE_ONFI | (val << 29);

	mtd_set_ooblayout(mtd, &ebu_nand_ooblayout_ops);
	chip->ecc.पढ़ो_page = ebu_nand_पढ़ो_page_hwecc;
	chip->ecc.ग_लिखो_page = ebu_nand_ग_लिखो_page_hwecc;

	वापस 0;
पूर्ण

अटल पूर्णांक ebu_nand_exec_op(काष्ठा nand_chip *chip,
			    स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	अचिन्हित पूर्णांक op_id;
	पूर्णांक i, समयout_ms, ret = 0;

	अगर (check_only)
		वापस 0;

	ebu_select_chip(chip);
	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			ebu_nand_ग_लिखोb(chip, HSन_अंकD_CLE_OFFS | HSन_अंकD_CS_OFFS,
					instr->ctx.cmd.opcode);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
				ebu_nand_ग_लिखोb(chip,
						HSन_अंकD_ALE_OFFS | HSन_अंकD_CS_OFFS,
						instr->ctx.addr.addrs[i]);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			ebu_पढ़ो_buf(chip, instr->ctx.data.buf.in,
				     instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			ebu_ग_लिखो_buf(chip, instr->ctx.data.buf.out,
				      instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			समयout_ms = instr->ctx.रुकोrdy.समयout_ms * 1000;
			ret = ebu_nand_रुकोrdy(chip, समयout_ms);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops ebu_nand_controller_ops = अणु
	.attach_chip = ebu_nand_attach_chip,
	.setup_पूर्णांकerface = ebu_nand_set_timings,
	.exec_op = ebu_nand_exec_op,
पूर्ण;

अटल व्योम ebu_dma_cleanup(काष्ठा ebu_nand_controller *ebu_host)
अणु
	अगर (ebu_host->dma_rx)
		dma_release_channel(ebu_host->dma_rx);

	अगर (ebu_host->dma_tx)
		dma_release_channel(ebu_host->dma_tx);
पूर्ण

अटल पूर्णांक ebu_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ebu_nand_controller *ebu_host;
	काष्ठा nand_chip *nand;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *res;
	अक्षर *resname;
	पूर्णांक ret;
	u32 cs;

	ebu_host = devm_kzalloc(dev, माप(*ebu_host), GFP_KERNEL);
	अगर (!ebu_host)
		वापस -ENOMEM;

	ebu_host->dev = dev;
	nand_controller_init(&ebu_host->controller);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ebunand");
	ebu_host->ebu = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ebu_host->ebu))
		वापस PTR_ERR(ebu_host->ebu);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hsnand");
	ebu_host->hsnand = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ebu_host->hsnand))
		वापस PTR_ERR(ebu_host->hsnand);

	ret = device_property_पढ़ो_u32(dev, "reg", &cs);
	अगर (ret) अणु
		dev_err(dev, "failed to get chip select: %d\n", ret);
		वापस ret;
	पूर्ण
	ebu_host->cs_num = cs;

	resname = devm_kaप्र_लिखो(dev, GFP_KERNEL, "nand_cs%d", cs);
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, resname);
	ebu_host->cs[cs].chipaddr = devm_ioremap_resource(dev, res);
	ebu_host->cs[cs].nand_pa = res->start;
	अगर (IS_ERR(ebu_host->cs[cs].chipaddr))
		वापस PTR_ERR(ebu_host->cs[cs].chipaddr);

	ebu_host->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ebu_host->clk))
		वापस dev_err_probe(dev, PTR_ERR(ebu_host->clk),
				     "failed to get clock\n");

	ret = clk_prepare_enable(ebu_host->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण
	ebu_host->clk_rate = clk_get_rate(ebu_host->clk);

	ebu_host->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(ebu_host->dma_tx))
		वापस dev_err_probe(dev, PTR_ERR(ebu_host->dma_tx),
				     "failed to request DMA tx chan!.\n");

	ebu_host->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(ebu_host->dma_rx))
		वापस dev_err_probe(dev, PTR_ERR(ebu_host->dma_rx),
				     "failed to request DMA rx chan!.\n");

	resname = devm_kaप्र_लिखो(dev, GFP_KERNEL, "addr_sel%d", cs);
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, resname);
	अगर (!res)
		वापस -EINVAL;
	ebu_host->cs[cs].addr_sel = res->start;
	ग_लिखोl(ebu_host->cs[cs].addr_sel | EBU_ADDR_MASK(5) | EBU_ADDR_SEL_REGEN,
	       ebu_host->ebu + EBU_ADDR_SEL(cs));

	nand_set_flash_node(&ebu_host->chip, dev->of_node);

	mtd = nand_to_mtd(&ebu_host->chip);
	अगर (!mtd->name) अणु
		dev_err(ebu_host->dev, "NAND label property is mandatory\n");
		वापस -EINVAL;
	पूर्ण

	mtd->dev.parent = dev;
	ebu_host->dev = dev;

	platक्रमm_set_drvdata(pdev, ebu_host);
	nand_set_controller_data(&ebu_host->chip, ebu_host);

	nand = &ebu_host->chip;
	nand->controller = &ebu_host->controller;
	nand->controller->ops = &ebu_nand_controller_ops;

	/* Scan to find existence of the device */
	ret = nand_scan(&ebu_host->chip, 1);
	अगर (ret)
		जाओ err_cleanup_dma;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		जाओ err_clean_nand;

	वापस 0;

err_clean_nand:
	nand_cleanup(&ebu_host->chip);
err_cleanup_dma:
	ebu_dma_cleanup(ebu_host);
	clk_disable_unprepare(ebu_host->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ebu_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ebu_nand_controller *ebu_host = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(&ebu_host->chip));
	WARN_ON(ret);
	nand_cleanup(&ebu_host->chip);
	ebu_nand_disable(&ebu_host->chip);
	ebu_dma_cleanup(ebu_host);
	clk_disable_unprepare(ebu_host->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ebu_nand_match[] = अणु
	अणु .compatible = "intel,nand-controller" पूर्ण,
	अणु .compatible = "intel,lgm-ebunand" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ebu_nand_match);

अटल काष्ठा platक्रमm_driver ebu_nand_driver = अणु
	.probe = ebu_nand_probe,
	.हटाओ = ebu_nand_हटाओ,
	.driver = अणु
		.name = "intel-nand-controller",
		.of_match_table = ebu_nand_match,
	पूर्ण,

पूर्ण;
module_platक्रमm_driver(ebu_nand_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Vadivel Murugan R <vadivel.muruganx.ramuthevar@intel.com>");
MODULE_DESCRIPTION("Intel's LGM External Bus NAND Controller driver");
