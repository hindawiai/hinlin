<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH FLCTL nand controller
 *
 * Copyright (c) 2008 Renesas Solutions Corp.
 * Copyright (c) 2008 Atom Create Engineering Co., Ltd.
 *
 * Based on fsl_elbc_nand.c, Copyright (c) 2006-2007 Freescale Semiconductor
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_dma.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/sh_flctl.h>

अटल पूर्णांक flctl_4secc_ooblayout_sp_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 0;
	oobregion->length = chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक flctl_4secc_ooblayout_sp_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					 काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 12;
	oobregion->length = 4;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops flctl_4secc_oob_smallpage_ops = अणु
	.ecc = flctl_4secc_ooblayout_sp_ecc,
	.मुक्त = flctl_4secc_ooblayout_sp_मुक्त,
पूर्ण;

अटल पूर्णांक flctl_4secc_ooblayout_lp_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 6;
	oobregion->length = chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक flctl_4secc_ooblayout_lp_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);

	अगर (section >= chip->ecc.steps)
		वापस -दुस्फल;

	oobregion->offset = section * 16;
	oobregion->length = 6;

	अगर (!section) अणु
		oobregion->offset += 2;
		oobregion->length -= 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops flctl_4secc_oob_largepage_ops = अणु
	.ecc = flctl_4secc_ooblayout_lp_ecc,
	.मुक्त = flctl_4secc_ooblayout_lp_मुक्त,
पूर्ण;

अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr flctl_4secc_smallpage = अणु
	.offs = 11,
	.len = 1,
	.pattern = scan_ff_pattern,
पूर्ण;

अटल काष्ठा nand_bbt_descr flctl_4secc_largepage = अणु
	.offs = 0,
	.len = 2,
	.pattern = scan_ff_pattern,
पूर्ण;

अटल व्योम empty_fअगरo(काष्ठा sh_flctl *flctl)
अणु
	ग_लिखोl(flctl->flपूर्णांकdmacr_base | AC1CLR | AC0CLR, FLINTDMACR(flctl));
	ग_लिखोl(flctl->flपूर्णांकdmacr_base, FLINTDMACR(flctl));
पूर्ण

अटल व्योम start_translation(काष्ठा sh_flctl *flctl)
अणु
	ग_लिखोb(TRSTRT, FLTRCR(flctl));
पूर्ण

अटल व्योम समयout_error(काष्ठा sh_flctl *flctl, स्थिर अक्षर *str)
अणु
	dev_err(&flctl->pdev->dev, "Timeout occurred in %s\n", str);
पूर्ण

अटल व्योम रुको_completion(काष्ठा sh_flctl *flctl)
अणु
	uपूर्णांक32_t समयout = LOOP_TIMEOUT_MAX;

	जबतक (समयout--) अणु
		अगर (पढ़ोb(FLTRCR(flctl)) & TREND) अणु
			ग_लिखोb(0x0, FLTRCR(flctl));
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण

	समयout_error(flctl, __func__);
	ग_लिखोb(0x0, FLTRCR(flctl));
पूर्ण

अटल व्योम flctl_dma_complete(व्योम *param)
अणु
	काष्ठा sh_flctl *flctl = param;

	complete(&flctl->dma_complete);
पूर्ण

अटल व्योम flctl_release_dma(काष्ठा sh_flctl *flctl)
अणु
	अगर (flctl->chan_fअगरo0_rx) अणु
		dma_release_channel(flctl->chan_fअगरo0_rx);
		flctl->chan_fअगरo0_rx = शून्य;
	पूर्ण
	अगर (flctl->chan_fअगरo0_tx) अणु
		dma_release_channel(flctl->chan_fअगरo0_tx);
		flctl->chan_fअगरo0_tx = शून्य;
	पूर्ण
पूर्ण

अटल व्योम flctl_setup_dma(काष्ठा sh_flctl *flctl)
अणु
	dma_cap_mask_t mask;
	काष्ठा dma_slave_config cfg;
	काष्ठा platक्रमm_device *pdev = flctl->pdev;
	काष्ठा sh_flctl_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	अगर (!pdata)
		वापस;

	अगर (pdata->slave_id_fअगरo0_tx <= 0 || pdata->slave_id_fअगरo0_rx <= 0)
		वापस;

	/* We can only either use DMA क्रम both Tx and Rx or not use it at all */
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	flctl->chan_fअगरo0_tx = dma_request_channel(mask, shdma_chan_filter,
				(व्योम *)(uपूर्णांकptr_t)pdata->slave_id_fअगरo0_tx);
	dev_dbg(&pdev->dev, "%s: TX: got channel %p\n", __func__,
		flctl->chan_fअगरo0_tx);

	अगर (!flctl->chan_fअगरo0_tx)
		वापस;

	स_रखो(&cfg, 0, माप(cfg));
	cfg.direction = DMA_MEM_TO_DEV;
	cfg.dst_addr = flctl->fअगरo;
	cfg.src_addr = 0;
	ret = dmaengine_slave_config(flctl->chan_fअगरo0_tx, &cfg);
	अगर (ret < 0)
		जाओ err;

	flctl->chan_fअगरo0_rx = dma_request_channel(mask, shdma_chan_filter,
				(व्योम *)(uपूर्णांकptr_t)pdata->slave_id_fअगरo0_rx);
	dev_dbg(&pdev->dev, "%s: RX: got channel %p\n", __func__,
		flctl->chan_fअगरo0_rx);

	अगर (!flctl->chan_fअगरo0_rx)
		जाओ err;

	cfg.direction = DMA_DEV_TO_MEM;
	cfg.dst_addr = 0;
	cfg.src_addr = flctl->fअगरo;
	ret = dmaengine_slave_config(flctl->chan_fअगरo0_rx, &cfg);
	अगर (ret < 0)
		जाओ err;

	init_completion(&flctl->dma_complete);

	वापस;

err:
	flctl_release_dma(flctl);
पूर्ण

अटल व्योम set_addr(काष्ठा mtd_info *mtd, पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	uपूर्णांक32_t addr = 0;

	अगर (column == -1) अणु
		addr = page_addr;	/* ERASE1 */
	पूर्ण अन्यथा अगर (page_addr != -1) अणु
		/* SEQIN, READ0, etc.. */
		अगर (flctl->chip.options & न_अंकD_BUSWIDTH_16)
			column >>= 1;
		अगर (flctl->page_size) अणु
			addr = column & 0x0FFF;
			addr |= (page_addr & 0xff) << 16;
			addr |= ((page_addr >> 8) & 0xff) << 24;
			/* big than 128MB */
			अगर (flctl->rw_ADRCNT == ADRCNT2_E) अणु
				uपूर्णांक32_t 	addr2;
				addr2 = (page_addr >> 16) & 0xff;
				ग_लिखोl(addr2, FLADR2(flctl));
			पूर्ण
		पूर्ण अन्यथा अणु
			addr = column;
			addr |= (page_addr & 0xff) << 8;
			addr |= ((page_addr >> 8) & 0xff) << 16;
			addr |= ((page_addr >> 16) & 0xff) << 24;
		पूर्ण
	पूर्ण
	ग_लिखोl(addr, FLADR(flctl));
पूर्ण

अटल व्योम रुको_rfअगरo_पढ़ोy(काष्ठा sh_flctl *flctl)
अणु
	uपूर्णांक32_t समयout = LOOP_TIMEOUT_MAX;

	जबतक (समयout--) अणु
		uपूर्णांक32_t val;
		/* check FIFO */
		val = पढ़ोl(FLDTCNTR(flctl)) >> 16;
		अगर (val & 0xFF)
			वापस;
		udelay(1);
	पूर्ण
	समयout_error(flctl, __func__);
पूर्ण

अटल व्योम रुको_wfअगरo_पढ़ोy(काष्ठा sh_flctl *flctl)
अणु
	uपूर्णांक32_t len, समयout = LOOP_TIMEOUT_MAX;

	जबतक (समयout--) अणु
		/* check FIFO */
		len = (पढ़ोl(FLDTCNTR(flctl)) >> 16) & 0xFF;
		अगर (len >= 4)
			वापस;
		udelay(1);
	पूर्ण
	समयout_error(flctl, __func__);
पूर्ण

अटल क्रमागत flctl_ecc_res_t रुको_recfअगरo_पढ़ोy
		(काष्ठा sh_flctl *flctl, पूर्णांक sector_number)
अणु
	uपूर्णांक32_t समयout = LOOP_TIMEOUT_MAX;
	व्योम __iomem *ecc_reg[4];
	पूर्णांक i;
	पूर्णांक state = FL_SUCCESS;
	uपूर्णांक32_t data, size;

	/*
	 * First this loops checks in FLDTCNTR अगर we are पढ़ोy to पढ़ो out the
	 * oob data. This is the हाल अगर either all went fine without errors or
	 * अगर the bottom part of the loop corrected the errors or marked them as
	 * uncorrectable and the controller is given समय to push the data पूर्णांकo
	 * the FIFO.
	 */
	जबतक (समयout--) अणु
		/* check अगर all is ok and we can पढ़ो out the OOB */
		size = पढ़ोl(FLDTCNTR(flctl)) >> 24;
		अगर ((size & 0xFF) == 4)
			वापस state;

		/* check अगर a correction code has been calculated */
		अगर (!(पढ़ोl(FL4ECCCR(flctl)) & _4ECCEND)) अणु
			/*
			 * either we रुको क्रम the fअगरo to be filled or a
			 * correction pattern is being generated
			 */
			udelay(1);
			जारी;
		पूर्ण

		/* check क्रम an uncorrectable error */
		अगर (पढ़ोl(FL4ECCCR(flctl)) & _4ECCFA) अणु
			/* check अगर we face a non-empty page */
			क्रम (i = 0; i < 512; i++) अणु
				अगर (flctl->करोne_buff[i] != 0xff) अणु
					state = FL_ERROR; /* can't correct */
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (state == FL_SUCCESS)
				dev_dbg(&flctl->pdev->dev,
				"reading empty sector %d, ecc error ignored\n",
				sector_number);

			ग_लिखोl(0, FL4ECCCR(flctl));
			जारी;
		पूर्ण

		/* start error correction */
		ecc_reg[0] = FL4ECCRESULT0(flctl);
		ecc_reg[1] = FL4ECCRESULT1(flctl);
		ecc_reg[2] = FL4ECCRESULT2(flctl);
		ecc_reg[3] = FL4ECCRESULT3(flctl);

		क्रम (i = 0; i < 3; i++) अणु
			uपूर्णांक8_t org;
			अचिन्हित पूर्णांक index;

			data = पढ़ोl(ecc_reg[i]);

			अगर (flctl->page_size)
				index = (512 * sector_number) +
					(data >> 16);
			अन्यथा
				index = data >> 16;

			org = flctl->करोne_buff[index];
			flctl->करोne_buff[index] = org ^ (data & 0xFF);
		पूर्ण
		state = FL_REPAIRABLE;
		ग_लिखोl(0, FL4ECCCR(flctl));
	पूर्ण

	समयout_error(flctl, __func__);
	वापस FL_TIMEOUT;	/* समयout */
पूर्ण

अटल व्योम रुको_wecfअगरo_पढ़ोy(काष्ठा sh_flctl *flctl)
अणु
	uपूर्णांक32_t समयout = LOOP_TIMEOUT_MAX;
	uपूर्णांक32_t len;

	जबतक (समयout--) अणु
		/* check FLECFIFO */
		len = (पढ़ोl(FLDTCNTR(flctl)) >> 24) & 0xFF;
		अगर (len >= 4)
			वापस;
		udelay(1);
	पूर्ण
	समयout_error(flctl, __func__);
पूर्ण

अटल पूर्णांक flctl_dma_fअगरo0_transfer(काष्ठा sh_flctl *flctl, अचिन्हित दीर्घ *buf,
					पूर्णांक len, क्रमागत dma_data_direction dir)
अणु
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *chan;
	क्रमागत dma_transfer_direction tr_dir;
	dma_addr_t dma_addr;
	dma_cookie_t cookie;
	uपूर्णांक32_t reg;
	पूर्णांक ret;

	अगर (dir == DMA_FROM_DEVICE) अणु
		chan = flctl->chan_fअगरo0_rx;
		tr_dir = DMA_DEV_TO_MEM;
	पूर्ण अन्यथा अणु
		chan = flctl->chan_fअगरo0_tx;
		tr_dir = DMA_MEM_TO_DEV;
	पूर्ण

	dma_addr = dma_map_single(chan->device->dev, buf, len, dir);

	अगर (!dma_mapping_error(chan->device->dev, dma_addr))
		desc = dmaengine_prep_slave_single(chan, dma_addr, len,
			tr_dir, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (desc) अणु
		reg = पढ़ोl(FLINTDMACR(flctl));
		reg |= DREQ0EN;
		ग_लिखोl(reg, FLINTDMACR(flctl));

		desc->callback = flctl_dma_complete;
		desc->callback_param = flctl;
		cookie = dmaengine_submit(desc);
		अगर (dma_submit_error(cookie)) अणु
			ret = dma_submit_error(cookie);
			dev_warn(&flctl->pdev->dev,
				 "DMA submit failed, falling back to PIO\n");
			जाओ out;
		पूर्ण

		dma_async_issue_pending(chan);
	पूर्ण अन्यथा अणु
		/* DMA failed, fall back to PIO */
		flctl_release_dma(flctl);
		dev_warn(&flctl->pdev->dev,
			 "DMA failed, falling back to PIO\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret =
	रुको_क्रम_completion_समयout(&flctl->dma_complete,
				msecs_to_jअगरfies(3000));

	अगर (ret <= 0) अणु
		dmaengine_terminate_all(chan);
		dev_err(&flctl->pdev->dev, "wait_for_completion_timeout\n");
	पूर्ण

out:
	reg = पढ़ोl(FLINTDMACR(flctl));
	reg &= ~DREQ0EN;
	ग_लिखोl(reg, FLINTDMACR(flctl));

	dma_unmap_single(chan->device->dev, dma_addr, len, dir);

	/* ret > 0 is success */
	वापस ret;
पूर्ण

अटल व्योम पढ़ो_datareg(काष्ठा sh_flctl *flctl, पूर्णांक offset)
अणु
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ *buf = (अचिन्हित दीर्घ *)&flctl->करोne_buff[offset];

	रुको_completion(flctl);

	data = पढ़ोl(FLDATAR(flctl));
	*buf = le32_to_cpu(data);
पूर्ण

अटल व्योम पढ़ो_fअगरoreg(काष्ठा sh_flctl *flctl, पूर्णांक rlen, पूर्णांक offset)
अणु
	पूर्णांक i, len_4align;
	अचिन्हित दीर्घ *buf = (अचिन्हित दीर्घ *)&flctl->करोne_buff[offset];

	len_4align = (rlen + 3) / 4;

	/* initiate DMA transfer */
	अगर (flctl->chan_fअगरo0_rx && rlen >= 32 &&
		flctl_dma_fअगरo0_transfer(flctl, buf, rlen, DMA_FROM_DEVICE) > 0)
			जाओ convert;	/* DMA success */

	/* करो polling transfer */
	क्रम (i = 0; i < len_4align; i++) अणु
		रुको_rfअगरo_पढ़ोy(flctl);
		buf[i] = पढ़ोl(FLDTFIFO(flctl));
	पूर्ण

convert:
	क्रम (i = 0; i < len_4align; i++)
		buf[i] = be32_to_cpu(buf[i]);
पूर्ण

अटल क्रमागत flctl_ecc_res_t पढ़ो_ecfअगरoreg
		(काष्ठा sh_flctl *flctl, uपूर्णांक8_t *buff, पूर्णांक sector)
अणु
	पूर्णांक i;
	क्रमागत flctl_ecc_res_t res;
	अचिन्हित दीर्घ *ecc_buf = (अचिन्हित दीर्घ *)buff;

	res = रुको_recfअगरo_पढ़ोy(flctl , sector);

	अगर (res != FL_ERROR) अणु
		क्रम (i = 0; i < 4; i++) अणु
			ecc_buf[i] = पढ़ोl(FLECFIFO(flctl));
			ecc_buf[i] = be32_to_cpu(ecc_buf[i]);
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम ग_लिखो_fअगरoreg(काष्ठा sh_flctl *flctl, पूर्णांक rlen,
						अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक i, len_4align;
	अचिन्हित दीर्घ *buf = (अचिन्हित दीर्घ *)&flctl->करोne_buff[offset];

	len_4align = (rlen + 3) / 4;
	क्रम (i = 0; i < len_4align; i++) अणु
		रुको_wfअगरo_पढ़ोy(flctl);
		ग_लिखोl(cpu_to_be32(buf[i]), FLDTFIFO(flctl));
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_ec_fअगरoreg(काष्ठा sh_flctl *flctl, पूर्णांक rlen,
						अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक i, len_4align;
	अचिन्हित दीर्घ *buf = (अचिन्हित दीर्घ *)&flctl->करोne_buff[offset];

	len_4align = (rlen + 3) / 4;

	क्रम (i = 0; i < len_4align; i++)
		buf[i] = cpu_to_be32(buf[i]);

	/* initiate DMA transfer */
	अगर (flctl->chan_fअगरo0_tx && rlen >= 32 &&
		flctl_dma_fअगरo0_transfer(flctl, buf, rlen, DMA_TO_DEVICE) > 0)
			वापस;	/* DMA success */

	/* करो polling transfer */
	क्रम (i = 0; i < len_4align; i++) अणु
		रुको_wecfअगरo_पढ़ोy(flctl);
		ग_लिखोl(buf[i], FLECFIFO(flctl));
	पूर्ण
पूर्ण

अटल व्योम set_cmd_regs(काष्ठा mtd_info *mtd, uपूर्णांक32_t cmd, uपूर्णांक32_t flcmcdr_val)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	uपूर्णांक32_t flcmncr_val = flctl->flcmncr_base & ~SEL_16BIT;
	uपूर्णांक32_t flcmdcr_val, addr_len_bytes = 0;

	/* Set Sन_अंकD bit अगर page size is 2048byte */
	अगर (flctl->page_size)
		flcmncr_val |= Sन_अंकD_E;
	अन्यथा
		flcmncr_val &= ~Sन_अंकD_E;

	/* शेष FLCMDCR val */
	flcmdcr_val = DOCMD1_E | DOADR_E;

	/* Set क्रम FLCMDCR */
	चयन (cmd) अणु
	हाल न_अंकD_CMD_ERASE1:
		addr_len_bytes = flctl->erase_ADRCNT;
		flcmdcr_val |= DOCMD2_E;
		अवरोध;
	हाल न_अंकD_CMD_READ0:
	हाल न_अंकD_CMD_READOOB:
	हाल न_अंकD_CMD_RNDOUT:
		addr_len_bytes = flctl->rw_ADRCNT;
		flcmdcr_val |= CDSRC_E;
		अगर (flctl->chip.options & न_अंकD_BUSWIDTH_16)
			flcmncr_val |= SEL_16BIT;
		अवरोध;
	हाल न_अंकD_CMD_SEQIN:
		/* This हाल is that cmd is READ0 or READ1 or READ00 */
		flcmdcr_val &= ~DOADR_E;	/* ONLY execute 1st cmd */
		अवरोध;
	हाल न_अंकD_CMD_PAGEPROG:
		addr_len_bytes = flctl->rw_ADRCNT;
		flcmdcr_val |= DOCMD2_E | CDSRC_E | SELRW;
		अगर (flctl->chip.options & न_अंकD_BUSWIDTH_16)
			flcmncr_val |= SEL_16BIT;
		अवरोध;
	हाल न_अंकD_CMD_READID:
		flcmncr_val &= ~Sन_अंकD_E;
		flcmdcr_val |= CDSRC_E;
		addr_len_bytes = ADRCNT_1;
		अवरोध;
	हाल न_अंकD_CMD_STATUS:
	हाल न_अंकD_CMD_RESET:
		flcmncr_val &= ~Sन_अंकD_E;
		flcmdcr_val &= ~(DOADR_E | DOSR_E);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Set address bytes parameter */
	flcmdcr_val |= addr_len_bytes;

	/* Now actually ग_लिखो */
	ग_लिखोl(flcmncr_val, FLCMNCR(flctl));
	ग_लिखोl(flcmdcr_val, FLCMDCR(flctl));
	ग_लिखोl(flcmcdr_val, FLCMCDR(flctl));
पूर्ण

अटल पूर्णांक flctl_पढ़ो_page_hwecc(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	nand_पढ़ो_page_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	अगर (oob_required)
		chip->legacy.पढ़ो_buf(chip, chip->oob_poi, mtd->oobsize);
	वापस 0;
पूर्ण

अटल पूर्णांक flctl_ग_लिखो_page_hwecc(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	nand_prog_page_begin_op(chip, page, 0, buf, mtd->ग_लिखोsize);
	chip->legacy.ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);
	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल व्योम execmd_पढ़ो_page_sector(काष्ठा mtd_info *mtd, पूर्णांक page_addr)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	पूर्णांक sector, page_sectors;
	क्रमागत flctl_ecc_res_t ecc_result;

	page_sectors = flctl->page_size ? 4 : 1;

	set_cmd_regs(mtd, न_अंकD_CMD_READ0,
		(न_अंकD_CMD_READSTART << 8) | न_अंकD_CMD_READ0);

	ग_लिखोl(पढ़ोl(FLCMNCR(flctl)) | ACM_SACCES_MODE | _4ECCCORRECT,
		 FLCMNCR(flctl));
	ग_लिखोl(पढ़ोl(FLCMDCR(flctl)) | page_sectors, FLCMDCR(flctl));
	ग_लिखोl(page_addr << 2, FLADR(flctl));

	empty_fअगरo(flctl);
	start_translation(flctl);

	क्रम (sector = 0; sector < page_sectors; sector++) अणु
		पढ़ो_fअगरoreg(flctl, 512, 512 * sector);

		ecc_result = पढ़ो_ecfअगरoreg(flctl,
			&flctl->करोne_buff[mtd->ग_लिखोsize + 16 * sector],
			sector);

		चयन (ecc_result) अणु
		हाल FL_REPAIRABLE:
			dev_info(&flctl->pdev->dev,
				"applied ecc on page 0x%x", page_addr);
			mtd->ecc_stats.corrected++;
			अवरोध;
		हाल FL_ERROR:
			dev_warn(&flctl->pdev->dev,
				"page 0x%x contains corrupted data\n",
				page_addr);
			mtd->ecc_stats.failed++;
			अवरोध;
		शेष:
			;
		पूर्ण
	पूर्ण

	रुको_completion(flctl);

	ग_लिखोl(पढ़ोl(FLCMNCR(flctl)) & ~(ACM_SACCES_MODE | _4ECCCORRECT),
			FLCMNCR(flctl));
पूर्ण

अटल व्योम execmd_पढ़ो_oob(काष्ठा mtd_info *mtd, पूर्णांक page_addr)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	पूर्णांक page_sectors = flctl->page_size ? 4 : 1;
	पूर्णांक i;

	set_cmd_regs(mtd, न_अंकD_CMD_READ0,
		(न_अंकD_CMD_READSTART << 8) | न_अंकD_CMD_READ0);

	empty_fअगरo(flctl);

	क्रम (i = 0; i < page_sectors; i++) अणु
		set_addr(mtd, (512 + 16) * i + 512 , page_addr);
		ग_लिखोl(16, FLDTCNTR(flctl));

		start_translation(flctl);
		पढ़ो_fअगरoreg(flctl, 16, 16 * i);
		रुको_completion(flctl);
	पूर्ण
पूर्ण

अटल व्योम execmd_ग_लिखो_page_sector(काष्ठा mtd_info *mtd)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	पूर्णांक page_addr = flctl->seqin_page_addr;
	पूर्णांक sector, page_sectors;

	page_sectors = flctl->page_size ? 4 : 1;

	set_cmd_regs(mtd, न_अंकD_CMD_PAGEPROG,
			(न_अंकD_CMD_PAGEPROG << 8) | न_अंकD_CMD_SEQIN);

	empty_fअगरo(flctl);
	ग_लिखोl(पढ़ोl(FLCMNCR(flctl)) | ACM_SACCES_MODE, FLCMNCR(flctl));
	ग_लिखोl(पढ़ोl(FLCMDCR(flctl)) | page_sectors, FLCMDCR(flctl));
	ग_लिखोl(page_addr << 2, FLADR(flctl));
	start_translation(flctl);

	क्रम (sector = 0; sector < page_sectors; sector++) अणु
		ग_लिखो_fअगरoreg(flctl, 512, 512 * sector);
		ग_लिखो_ec_fअगरoreg(flctl, 16, mtd->ग_लिखोsize + 16 * sector);
	पूर्ण

	रुको_completion(flctl);
	ग_लिखोl(पढ़ोl(FLCMNCR(flctl)) & ~ACM_SACCES_MODE, FLCMNCR(flctl));
पूर्ण

अटल व्योम execmd_ग_लिखो_oob(काष्ठा mtd_info *mtd)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	पूर्णांक page_addr = flctl->seqin_page_addr;
	पूर्णांक sector, page_sectors;

	page_sectors = flctl->page_size ? 4 : 1;

	set_cmd_regs(mtd, न_अंकD_CMD_PAGEPROG,
			(न_अंकD_CMD_PAGEPROG << 8) | न_अंकD_CMD_SEQIN);

	क्रम (sector = 0; sector < page_sectors; sector++) अणु
		empty_fअगरo(flctl);
		set_addr(mtd, sector * 528 + 512, page_addr);
		ग_लिखोl(16, FLDTCNTR(flctl));	/* set पढ़ो size */

		start_translation(flctl);
		ग_लिखो_fअगरoreg(flctl, 16, 16 * sector);
		रुको_completion(flctl);
	पूर्ण
पूर्ण

अटल व्योम flctl_cmdfunc(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक command,
			पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);
	uपूर्णांक32_t पढ़ो_cmd = 0;

	pm_runसमय_get_sync(&flctl->pdev->dev);

	flctl->पढ़ो_bytes = 0;
	अगर (command != न_अंकD_CMD_PAGEPROG)
		flctl->index = 0;

	चयन (command) अणु
	हाल न_अंकD_CMD_READ1:
	हाल न_अंकD_CMD_READ0:
		अगर (flctl->hwecc) अणु
			/* पढ़ो page with hwecc */
			execmd_पढ़ो_page_sector(mtd, page_addr);
			अवरोध;
		पूर्ण
		अगर (flctl->page_size)
			set_cmd_regs(mtd, command, (न_अंकD_CMD_READSTART << 8)
				| command);
		अन्यथा
			set_cmd_regs(mtd, command, command);

		set_addr(mtd, 0, page_addr);

		flctl->पढ़ो_bytes = mtd->ग_लिखोsize + mtd->oobsize;
		अगर (flctl->chip.options & न_अंकD_BUSWIDTH_16)
			column >>= 1;
		flctl->index += column;
		जाओ पढ़ो_normal_निकास;

	हाल न_अंकD_CMD_READOOB:
		अगर (flctl->hwecc) अणु
			/* पढ़ो page with hwecc */
			execmd_पढ़ो_oob(mtd, page_addr);
			अवरोध;
		पूर्ण

		अगर (flctl->page_size) अणु
			set_cmd_regs(mtd, command, (न_अंकD_CMD_READSTART << 8)
				| न_अंकD_CMD_READ0);
			set_addr(mtd, mtd->ग_लिखोsize, page_addr);
		पूर्ण अन्यथा अणु
			set_cmd_regs(mtd, command, command);
			set_addr(mtd, 0, page_addr);
		पूर्ण
		flctl->पढ़ो_bytes = mtd->oobsize;
		जाओ पढ़ो_normal_निकास;

	हाल न_अंकD_CMD_RNDOUT:
		अगर (flctl->hwecc)
			अवरोध;

		अगर (flctl->page_size)
			set_cmd_regs(mtd, command, (न_अंकD_CMD_RNDOUTSTART << 8)
				| command);
		अन्यथा
			set_cmd_regs(mtd, command, command);

		set_addr(mtd, column, 0);

		flctl->पढ़ो_bytes = mtd->ग_लिखोsize + mtd->oobsize - column;
		जाओ पढ़ो_normal_निकास;

	हाल न_अंकD_CMD_READID:
		set_cmd_regs(mtd, command, command);

		/* READID is always perक्रमmed using an 8-bit bus */
		अगर (flctl->chip.options & न_अंकD_BUSWIDTH_16)
			column <<= 1;
		set_addr(mtd, column, 0);

		flctl->पढ़ो_bytes = 8;
		ग_लिखोl(flctl->पढ़ो_bytes, FLDTCNTR(flctl)); /* set पढ़ो size */
		empty_fअगरo(flctl);
		start_translation(flctl);
		पढ़ो_fअगरoreg(flctl, flctl->पढ़ो_bytes, 0);
		रुको_completion(flctl);
		अवरोध;

	हाल न_अंकD_CMD_ERASE1:
		flctl->erase1_page_addr = page_addr;
		अवरोध;

	हाल न_अंकD_CMD_ERASE2:
		set_cmd_regs(mtd, न_अंकD_CMD_ERASE1,
			(command << 8) | न_अंकD_CMD_ERASE1);
		set_addr(mtd, -1, flctl->erase1_page_addr);
		start_translation(flctl);
		रुको_completion(flctl);
		अवरोध;

	हाल न_अंकD_CMD_SEQIN:
		अगर (!flctl->page_size) अणु
			/* output पढ़ो command */
			अगर (column >= mtd->ग_लिखोsize) अणु
				column -= mtd->ग_लिखोsize;
				पढ़ो_cmd = न_अंकD_CMD_READOOB;
			पूर्ण अन्यथा अगर (column < 256) अणु
				पढ़ो_cmd = न_अंकD_CMD_READ0;
			पूर्ण अन्यथा अणु
				column -= 256;
				पढ़ो_cmd = न_अंकD_CMD_READ1;
			पूर्ण
		पूर्ण
		flctl->seqin_column = column;
		flctl->seqin_page_addr = page_addr;
		flctl->seqin_पढ़ो_cmd = पढ़ो_cmd;
		अवरोध;

	हाल न_अंकD_CMD_PAGEPROG:
		empty_fअगरo(flctl);
		अगर (!flctl->page_size) अणु
			set_cmd_regs(mtd, न_अंकD_CMD_SEQIN,
					flctl->seqin_पढ़ो_cmd);
			set_addr(mtd, -1, -1);
			ग_लिखोl(0, FLDTCNTR(flctl));	/* set 0 size */
			start_translation(flctl);
			रुको_completion(flctl);
		पूर्ण
		अगर (flctl->hwecc) अणु
			/* ग_लिखो page with hwecc */
			अगर (flctl->seqin_column == mtd->ग_लिखोsize)
				execmd_ग_लिखो_oob(mtd);
			अन्यथा अगर (!flctl->seqin_column)
				execmd_ग_लिखो_page_sector(mtd);
			अन्यथा
				pr_err("Invalid address !?\n");
			अवरोध;
		पूर्ण
		set_cmd_regs(mtd, command, (command << 8) | न_अंकD_CMD_SEQIN);
		set_addr(mtd, flctl->seqin_column, flctl->seqin_page_addr);
		ग_लिखोl(flctl->index, FLDTCNTR(flctl));	/* set ग_लिखो size */
		start_translation(flctl);
		ग_लिखो_fअगरoreg(flctl, flctl->index, 0);
		रुको_completion(flctl);
		अवरोध;

	हाल न_अंकD_CMD_STATUS:
		set_cmd_regs(mtd, command, command);
		set_addr(mtd, -1, -1);

		flctl->पढ़ो_bytes = 1;
		ग_लिखोl(flctl->पढ़ो_bytes, FLDTCNTR(flctl)); /* set पढ़ो size */
		start_translation(flctl);
		पढ़ो_datareg(flctl, 0); /* पढ़ो and end */
		अवरोध;

	हाल न_अंकD_CMD_RESET:
		set_cmd_regs(mtd, command, command);
		set_addr(mtd, -1, -1);

		ग_लिखोl(0, FLDTCNTR(flctl));	/* set 0 size */
		start_translation(flctl);
		रुको_completion(flctl);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	जाओ runसमय_निकास;

पढ़ो_normal_निकास:
	ग_लिखोl(flctl->पढ़ो_bytes, FLDTCNTR(flctl));	/* set पढ़ो size */
	empty_fअगरo(flctl);
	start_translation(flctl);
	पढ़ो_fअगरoreg(flctl, flctl->पढ़ो_bytes, 0);
	रुको_completion(flctl);
runसमय_निकास:
	pm_runसमय_put_sync(&flctl->pdev->dev);
	वापस;
पूर्ण

अटल व्योम flctl_select_chip(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(nand_to_mtd(chip));
	पूर्णांक ret;

	चयन (chipnr) अणु
	हाल -1:
		flctl->flcmncr_base &= ~CE0_ENABLE;

		pm_runसमय_get_sync(&flctl->pdev->dev);
		ग_लिखोl(flctl->flcmncr_base, FLCMNCR(flctl));

		अगर (flctl->qos_request) अणु
			dev_pm_qos_हटाओ_request(&flctl->pm_qos);
			flctl->qos_request = 0;
		पूर्ण

		pm_runसमय_put_sync(&flctl->pdev->dev);
		अवरोध;
	हाल 0:
		flctl->flcmncr_base |= CE0_ENABLE;

		अगर (!flctl->qos_request) अणु
			ret = dev_pm_qos_add_request(&flctl->pdev->dev,
							&flctl->pm_qos,
							DEV_PM_QOS_RESUME_LATENCY,
							100);
			अगर (ret < 0)
				dev_err(&flctl->pdev->dev,
					"PM QoS request failed: %d\n", ret);
			flctl->qos_request = 1;
		पूर्ण

		अगर (flctl->holden) अणु
			pm_runसमय_get_sync(&flctl->pdev->dev);
			ग_लिखोl(HOLDEN, FLHOLDCR(flctl));
			pm_runसमय_put_sync(&flctl->pdev->dev);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम flctl_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(nand_to_mtd(chip));

	स_नकल(&flctl->करोne_buff[flctl->index], buf, len);
	flctl->index += len;
पूर्ण

अटल uपूर्णांक8_t flctl_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(nand_to_mtd(chip));
	uपूर्णांक8_t data;

	data = flctl->करोne_buff[flctl->index];
	flctl->index++;
	वापस data;
पूर्ण

अटल व्योम flctl_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा sh_flctl *flctl = mtd_to_flctl(nand_to_mtd(chip));

	स_नकल(buf, &flctl->करोne_buff[flctl->index], len);
	flctl->index += len;
पूर्ण

अटल पूर्णांक flctl_chip_attach_chip(काष्ठा nand_chip *chip)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&chip->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा sh_flctl *flctl = mtd_to_flctl(mtd);

	/*
	 * न_अंकD_BUSWIDTH_16 may have been set by nand_scan_ident().
	 * Add the SEL_16BIT flag in flctl->flcmncr_base.
	 */
	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		flctl->flcmncr_base |= SEL_16BIT;

	अगर (mtd->ग_लिखोsize == 512) अणु
		flctl->page_size = 0;
		अगर (tarमाला_लोize > (32 << 20)) अणु
			/* big than 32MB */
			flctl->rw_ADRCNT = ADRCNT_4;
			flctl->erase_ADRCNT = ADRCNT_3;
		पूर्ण अन्यथा अगर (tarमाला_लोize > (2 << 16)) अणु
			/* big than 128KB */
			flctl->rw_ADRCNT = ADRCNT_3;
			flctl->erase_ADRCNT = ADRCNT_2;
		पूर्ण अन्यथा अणु
			flctl->rw_ADRCNT = ADRCNT_2;
			flctl->erase_ADRCNT = ADRCNT_1;
		पूर्ण
	पूर्ण अन्यथा अणु
		flctl->page_size = 1;
		अगर (tarमाला_लोize > (128 << 20)) अणु
			/* big than 128MB */
			flctl->rw_ADRCNT = ADRCNT2_E;
			flctl->erase_ADRCNT = ADRCNT_3;
		पूर्ण अन्यथा अगर (tarमाला_लोize > (8 << 16)) अणु
			/* big than 512KB */
			flctl->rw_ADRCNT = ADRCNT_4;
			flctl->erase_ADRCNT = ADRCNT_2;
		पूर्ण अन्यथा अणु
			flctl->rw_ADRCNT = ADRCNT_3;
			flctl->erase_ADRCNT = ADRCNT_1;
		पूर्ण
	पूर्ण

	अगर (flctl->hwecc) अणु
		अगर (mtd->ग_लिखोsize == 512) अणु
			mtd_set_ooblayout(mtd, &flctl_4secc_oob_smallpage_ops);
			chip->badblock_pattern = &flctl_4secc_smallpage;
		पूर्ण अन्यथा अणु
			mtd_set_ooblayout(mtd, &flctl_4secc_oob_largepage_ops);
			chip->badblock_pattern = &flctl_4secc_largepage;
		पूर्ण

		chip->ecc.size = 512;
		chip->ecc.bytes = 10;
		chip->ecc.strength = 4;
		chip->ecc.पढ़ो_page = flctl_पढ़ो_page_hwecc;
		chip->ecc.ग_लिखो_page = flctl_ग_लिखो_page_hwecc;
		chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

		/* 4 symbols ECC enabled */
		flctl->flcmncr_base |= _4ECCEN;
	पूर्ण अन्यथा अणु
		chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops flctl_nand_controller_ops = अणु
	.attach_chip = flctl_chip_attach_chip,
पूर्ण;

अटल irqवापस_t flctl_handle_flste(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_flctl *flctl = dev_id;

	dev_err(&flctl->pdev->dev, "flste irq: %x\n", पढ़ोl(FLINTDMACR(flctl)));
	ग_लिखोl(flctl->flपूर्णांकdmacr_base, FLINTDMACR(flctl));

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा flctl_soc_config अणु
	अचिन्हित दीर्घ flcmncr_val;
	अचिन्हित has_hwecc:1;
	अचिन्हित use_holden:1;
पूर्ण;

अटल काष्ठा flctl_soc_config flctl_sh7372_config = अणु
	.flcmncr_val = CLK_16B_12L_4H | TYPESEL_SET | SHBUSSEL,
	.has_hwecc = 1,
	.use_holden = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_flctl_match[] = अणु
	अणु .compatible = "renesas,shmobile-flctl-sh7372",
				.data = &flctl_sh7372_config पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_flctl_match);

अटल काष्ठा sh_flctl_platक्रमm_data *flctl_parse_dt(काष्ठा device *dev)
अणु
	स्थिर काष्ठा flctl_soc_config *config;
	काष्ठा sh_flctl_platक्रमm_data *pdata;

	config = of_device_get_match_data(dev);
	अगर (!config) अणु
		dev_err(dev, "%s: no OF configuration attached\n", __func__);
		वापस शून्य;
	पूर्ण

	pdata = devm_kzalloc(dev, माप(काष्ठा sh_flctl_platक्रमm_data),
								GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	/* set SoC specअगरic options */
	pdata->flcmncr_val = config->flcmncr_val;
	pdata->has_hwecc = config->has_hwecc;
	pdata->use_holden = config->use_holden;

	वापस pdata;
पूर्ण

अटल पूर्णांक flctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा sh_flctl *flctl;
	काष्ठा mtd_info *flctl_mtd;
	काष्ठा nand_chip *nand;
	काष्ठा sh_flctl_platक्रमm_data *pdata;
	पूर्णांक ret;
	पूर्णांक irq;

	flctl = devm_kzalloc(&pdev->dev, माप(काष्ठा sh_flctl), GFP_KERNEL);
	अगर (!flctl)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	flctl->reg = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(flctl->reg))
		वापस PTR_ERR(flctl->reg);
	flctl->fअगरo = res->start + 0x24; /* FLDTFIFO */

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, flctl_handle_flste, IRQF_SHARED,
			       "flste", flctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request interrupt failed.\n");
		वापस ret;
	पूर्ण

	अगर (pdev->dev.of_node)
		pdata = flctl_parse_dt(&pdev->dev);
	अन्यथा
		pdata = dev_get_platdata(&pdev->dev);

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no setup data defined\n");
		वापस -EINVAL;
	पूर्ण

	platक्रमm_set_drvdata(pdev, flctl);
	nand = &flctl->chip;
	flctl_mtd = nand_to_mtd(nand);
	nand_set_flash_node(nand, pdev->dev.of_node);
	flctl_mtd->dev.parent = &pdev->dev;
	flctl->pdev = pdev;
	flctl->hwecc = pdata->has_hwecc;
	flctl->holden = pdata->use_holden;
	flctl->flcmncr_base = pdata->flcmncr_val;
	flctl->flपूर्णांकdmacr_base = flctl->hwecc ? (STERINTE | ECERB) : STERINTE;

	/* Set address of hardware control function */
	/* 20 us command delay समय */
	nand->legacy.chip_delay = 20;

	nand->legacy.पढ़ो_byte = flctl_पढ़ो_byte;
	nand->legacy.ग_लिखो_buf = flctl_ग_लिखो_buf;
	nand->legacy.पढ़ो_buf = flctl_पढ़ो_buf;
	nand->legacy.select_chip = flctl_select_chip;
	nand->legacy.cmdfunc = flctl_cmdfunc;
	nand->legacy.set_features = nand_get_set_features_notsupp;
	nand->legacy.get_features = nand_get_set_features_notsupp;

	अगर (pdata->flcmncr_val & SEL_16BIT)
		nand->options |= न_अंकD_BUSWIDTH_16;

	nand->options |= न_अंकD_BBM_FIRSTPAGE | न_अंकD_BBM_SECONDPAGE;

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_resume(&pdev->dev);

	flctl_setup_dma(flctl);

	nand->legacy.dummy_controller.ops = &flctl_nand_controller_ops;
	ret = nand_scan(nand, 1);
	अगर (ret)
		जाओ err_chip;

	ret = mtd_device_रेजिस्टर(flctl_mtd, pdata->parts, pdata->nr_parts);
	अगर (ret)
		जाओ cleanup_nand;

	वापस 0;

cleanup_nand:
	nand_cleanup(nand);
err_chip:
	flctl_release_dma(flctl);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक flctl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_flctl *flctl = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &flctl->chip;
	पूर्णांक ret;

	flctl_release_dma(flctl);
	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver flctl_driver = अणु
	.हटाओ		= flctl_हटाओ,
	.driver = अणु
		.name	= "sh_flctl",
		.of_match_table = of_match_ptr(of_flctl_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(flctl_driver, flctl_probe);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_DESCRIPTION("SuperH FLCTL driver");
MODULE_ALIAS("platform:sh_flctl");
