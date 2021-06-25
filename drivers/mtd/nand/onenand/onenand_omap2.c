<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Oneन_अंकD driver क्रम OMAP2 / OMAP3
 *
 *  Copyright तऊ 2005-2006 Nokia Corporation
 *
 *  Author: Jarkko Lavinen <jarkko.lavinen@nokia.com> and Juha Yrjथघlथअ
 *  IRQ and DMA support written by Timo Teras
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of_device.h>
#समावेश <linux/omap-gpmc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <यंत्र/mach/flash.h>

#घोषणा DRIVER_NAME "omap2-onenand"

#घोषणा ONEन_अंकD_BUFRAM_SIZE	(1024 * 5)

काष्ठा omap2_onenand अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक gpmc_cs;
	अचिन्हित दीर्घ phys_base;
	काष्ठा gpio_desc *पूर्णांक_gpiod;
	काष्ठा mtd_info mtd;
	काष्ठा onenand_chip onenand;
	काष्ठा completion irq_करोne;
	काष्ठा completion dma_करोne;
	काष्ठा dma_chan *dma_chan;
पूर्ण;

अटल व्योम omap2_onenand_dma_complete_func(व्योम *completion)
अणु
	complete(completion);
पूर्ण

अटल irqवापस_t omap2_onenand_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap2_onenand *c = dev_id;

	complete(&c->irq_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत अचिन्हित लघु पढ़ो_reg(काष्ठा omap2_onenand *c, पूर्णांक reg)
अणु
	वापस पढ़ोw(c->onenand.base + reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg(काष्ठा omap2_onenand *c, अचिन्हित लघु value,
			     पूर्णांक reg)
अणु
	ग_लिखोw(value, c->onenand.base + reg);
पूर्ण

अटल पूर्णांक omap2_onenand_set_cfg(काष्ठा omap2_onenand *c,
				 bool sr, bool sw,
				 पूर्णांक latency, पूर्णांक burst_len)
अणु
	अचिन्हित लघु reg = ONEन_अंकD_SYS_CFG1_RDY | ONEन_अंकD_SYS_CFG1_INT;

	reg |= latency << ONEन_अंकD_SYS_CFG1_BRL_SHIFT;

	चयन (burst_len) अणु
	हाल 0:		/* continuous */
		अवरोध;
	हाल 4:
		reg |= ONEन_अंकD_SYS_CFG1_BL_4;
		अवरोध;
	हाल 8:
		reg |= ONEन_अंकD_SYS_CFG1_BL_8;
		अवरोध;
	हाल 16:
		reg |= ONEन_अंकD_SYS_CFG1_BL_16;
		अवरोध;
	हाल 32:
		reg |= ONEन_अंकD_SYS_CFG1_BL_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (latency > 5)
		reg |= ONEन_अंकD_SYS_CFG1_HF;
	अगर (latency > 7)
		reg |= ONEन_अंकD_SYS_CFG1_VHF;
	अगर (sr)
		reg |= ONEन_अंकD_SYS_CFG1_SYNC_READ;
	अगर (sw)
		reg |= ONEन_अंकD_SYS_CFG1_SYNC_WRITE;

	ग_लिखो_reg(c, reg, ONEन_अंकD_REG_SYS_CFG1);

	वापस 0;
पूर्ण

अटल पूर्णांक omap2_onenand_get_freq(पूर्णांक ver)
अणु
	चयन ((ver >> 4) & 0xf) अणु
	हाल 0:
		वापस 40;
	हाल 1:
		वापस 54;
	हाल 2:
		वापस 66;
	हाल 3:
		वापस 83;
	हाल 4:
		वापस 104;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम रुको_err(अक्षर *msg, पूर्णांक state, अचिन्हित पूर्णांक ctrl, अचिन्हित पूर्णांक पूर्णांकr)
अणु
	prपूर्णांकk(KERN_ERR "onenand_wait: %s! state %d ctrl 0x%04x intr 0x%04x\n",
	       msg, state, ctrl, पूर्णांकr);
पूर्ण

अटल व्योम रुको_warn(अक्षर *msg, पूर्णांक state, अचिन्हित पूर्णांक ctrl,
		      अचिन्हित पूर्णांक पूर्णांकr)
अणु
	prपूर्णांकk(KERN_WARNING "onenand_wait: %s! state %d ctrl 0x%04x "
	       "intr 0x%04x\n", msg, state, ctrl, पूर्णांकr);
पूर्ण

अटल पूर्णांक omap2_onenand_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	काष्ठा omap2_onenand *c = container_of(mtd, काष्ठा omap2_onenand, mtd);
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित पूर्णांक पूर्णांकr = 0;
	अचिन्हित पूर्णांक ctrl, ctrl_mask;
	अचिन्हित दीर्घ समयout;
	u32 syscfg;

	अगर (state == FL_RESETTING || state == FL_PREPARING_ERASE ||
	    state == FL_VERIFYING_ERASE) अणु
		पूर्णांक i = 21;
		अचिन्हित पूर्णांक पूर्णांकr_flags = ONEन_अंकD_INT_MASTER;

		चयन (state) अणु
		हाल FL_RESETTING:
			पूर्णांकr_flags |= ONEन_अंकD_INT_RESET;
			अवरोध;
		हाल FL_PREPARING_ERASE:
			पूर्णांकr_flags |= ONEन_अंकD_INT_ERASE;
			अवरोध;
		हाल FL_VERIFYING_ERASE:
			i = 101;
			अवरोध;
		पूर्ण

		जबतक (--i) अणु
			udelay(1);
			पूर्णांकr = पढ़ो_reg(c, ONEन_अंकD_REG_INTERRUPT);
			अगर (पूर्णांकr & ONEन_अंकD_INT_MASTER)
				अवरोध;
		पूर्ण
		ctrl = पढ़ो_reg(c, ONEन_अंकD_REG_CTRL_STATUS);
		अगर (ctrl & ONEन_अंकD_CTRL_ERROR) अणु
			रुको_err("controller error", state, ctrl, पूर्णांकr);
			वापस -EIO;
		पूर्ण
		अगर ((पूर्णांकr & पूर्णांकr_flags) == पूर्णांकr_flags)
			वापस 0;
		/* Continue in रुको क्रम पूर्णांकerrupt branch */
	पूर्ण

	अगर (state != FL_READING) अणु
		पूर्णांक result;

		/* Turn पूर्णांकerrupts on */
		syscfg = पढ़ो_reg(c, ONEन_अंकD_REG_SYS_CFG1);
		अगर (!(syscfg & ONEन_अंकD_SYS_CFG1_IOBE)) अणु
			syscfg |= ONEन_अंकD_SYS_CFG1_IOBE;
			ग_लिखो_reg(c, syscfg, ONEन_अंकD_REG_SYS_CFG1);
			/* Add a delay to let GPIO settle */
			syscfg = पढ़ो_reg(c, ONEन_अंकD_REG_SYS_CFG1);
		पूर्ण

		reinit_completion(&c->irq_करोne);
		result = gpiod_get_value(c->पूर्णांक_gpiod);
		अगर (result < 0) अणु
			ctrl = पढ़ो_reg(c, ONEन_अंकD_REG_CTRL_STATUS);
			पूर्णांकr = पढ़ो_reg(c, ONEन_अंकD_REG_INTERRUPT);
			रुको_err("gpio error", state, ctrl, पूर्णांकr);
			वापस result;
		पूर्ण अन्यथा अगर (result == 0) अणु
			पूर्णांक retry_cnt = 0;
retry:
			अगर (!रुको_क्रम_completion_io_समयout(&c->irq_करोne,
						msecs_to_jअगरfies(20))) अणु
				/* Timeout after 20ms */
				ctrl = पढ़ो_reg(c, ONEन_अंकD_REG_CTRL_STATUS);
				अगर (ctrl & ONEन_अंकD_CTRL_ONGO &&
				    !this->ongoing) अणु
					/*
					 * The operation seems to be still going
					 * so give it some more समय.
					 */
					retry_cnt += 1;
					अगर (retry_cnt < 3)
						जाओ retry;
					पूर्णांकr = पढ़ो_reg(c,
							ONEन_अंकD_REG_INTERRUPT);
					रुको_err("timeout", state, ctrl, पूर्णांकr);
					वापस -EIO;
				पूर्ण
				पूर्णांकr = पढ़ो_reg(c, ONEन_अंकD_REG_INTERRUPT);
				अगर ((पूर्णांकr & ONEन_अंकD_INT_MASTER) == 0)
					रुको_warn("timeout", state, ctrl, पूर्णांकr);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक retry_cnt = 0;

		/* Turn पूर्णांकerrupts off */
		syscfg = पढ़ो_reg(c, ONEन_अंकD_REG_SYS_CFG1);
		syscfg &= ~ONEन_अंकD_SYS_CFG1_IOBE;
		ग_लिखो_reg(c, syscfg, ONEन_अंकD_REG_SYS_CFG1);

		समयout = jअगरfies + msecs_to_jअगरfies(20);
		जबतक (1) अणु
			अगर (समय_beक्रमe(jअगरfies, समयout)) अणु
				पूर्णांकr = पढ़ो_reg(c, ONEन_अंकD_REG_INTERRUPT);
				अगर (पूर्णांकr & ONEन_अंकD_INT_MASTER)
					अवरोध;
			पूर्ण अन्यथा अणु
				/* Timeout after 20ms */
				ctrl = पढ़ो_reg(c, ONEन_अंकD_REG_CTRL_STATUS);
				अगर (ctrl & ONEन_अंकD_CTRL_ONGO) अणु
					/*
					 * The operation seems to be still going
					 * so give it some more समय.
					 */
					retry_cnt += 1;
					अगर (retry_cnt < 3) अणु
						समयout = jअगरfies +
							  msecs_to_jअगरfies(20);
						जारी;
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	पूर्णांकr = पढ़ो_reg(c, ONEन_अंकD_REG_INTERRUPT);
	ctrl = पढ़ो_reg(c, ONEन_अंकD_REG_CTRL_STATUS);

	अगर (पूर्णांकr & ONEन_अंकD_INT_READ) अणु
		पूर्णांक ecc = पढ़ो_reg(c, ONEन_अंकD_REG_ECC_STATUS);

		अगर (ecc) अणु
			अचिन्हित पूर्णांक addr1, addr8;

			addr1 = पढ़ो_reg(c, ONEन_अंकD_REG_START_ADDRESS1);
			addr8 = पढ़ो_reg(c, ONEन_अंकD_REG_START_ADDRESS8);
			अगर (ecc & ONEन_अंकD_ECC_2BIT_ALL) अणु
				prपूर्णांकk(KERN_ERR "onenand_wait: ECC error = "
				       "0x%04x, addr1 %#x, addr8 %#x\n",
				       ecc, addr1, addr8);
				mtd->ecc_stats.failed++;
				वापस -EBADMSG;
			पूर्ण अन्यथा अगर (ecc & ONEन_अंकD_ECC_1BIT_ALL) अणु
				prपूर्णांकk(KERN_NOTICE "onenand_wait: correctable "
				       "ECC error = 0x%04x, addr1 %#x, "
				       "addr8 %#x\n", ecc, addr1, addr8);
				mtd->ecc_stats.corrected++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (state == FL_READING) अणु
		रुको_err("timeout", state, ctrl, पूर्णांकr);
		वापस -EIO;
	पूर्ण

	अगर (ctrl & ONEन_अंकD_CTRL_ERROR) अणु
		रुको_err("controller error", state, ctrl, पूर्णांकr);
		अगर (ctrl & ONEन_अंकD_CTRL_LOCK)
			prपूर्णांकk(KERN_ERR "onenand_wait: "
					"Device is write protected!!!\n");
		वापस -EIO;
	पूर्ण

	ctrl_mask = 0xFE9F;
	अगर (this->ongoing)
		ctrl_mask &= ~0x8000;

	अगर (ctrl & ctrl_mask)
		रुको_warn("unexpected controller status", state, ctrl, पूर्णांकr);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap2_onenand_bufferram_offset(काष्ठा mtd_info *mtd, पूर्णांक area)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	अगर (ONEन_अंकD_CURRENT_BUFFERRAM(this)) अणु
		अगर (area == ONEन_अंकD_DATARAM)
			वापस this->ग_लिखोsize;
		अगर (area == ONEन_अंकD_SPARERAM)
			वापस mtd->oobsize;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap2_onenand_dma_transfer(काष्ठा omap2_onenand *c,
					     dma_addr_t src, dma_addr_t dst,
					     माप_प्रकार count)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;

	tx = dmaengine_prep_dma_स_नकल(c->dma_chan, dst, src, count,
				       DMA_CTRL_ACK | DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(&c->pdev->dev, "Failed to prepare DMA memcpy\n");
		वापस -EIO;
	पूर्ण

	reinit_completion(&c->dma_करोne);

	tx->callback = omap2_onenand_dma_complete_func;
	tx->callback_param = &c->dma_करोne;

	cookie = tx->tx_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_err(&c->pdev->dev, "Failed to do DMA tx_submit\n");
		वापस -EIO;
	पूर्ण

	dma_async_issue_pending(c->dma_chan);

	अगर (!रुको_क्रम_completion_io_समयout(&c->dma_करोne,
					    msecs_to_jअगरfies(20))) अणु
		dmaengine_terminate_sync(c->dma_chan);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap2_onenand_पढ़ो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
					अचिन्हित अक्षर *buffer, पूर्णांक offset,
					माप_प्रकार count)
अणु
	काष्ठा omap2_onenand *c = container_of(mtd, काष्ठा omap2_onenand, mtd);
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा device *dev = &c->pdev->dev;
	व्योम *buf = (व्योम *)buffer;
	dma_addr_t dma_src, dma_dst;
	पूर्णांक bram_offset, err;
	माप_प्रकार xtra;

	bram_offset = omap2_onenand_bufferram_offset(mtd, area) + area + offset;
	/*
	 * If the buffer address is not DMA-able, len is not दीर्घ enough to
	 * make DMA transfers profitable or अगर invoked from panic_ग_लिखो()
	 * fallback to PIO mode.
	 */
	अगर (!virt_addr_valid(buf) || bram_offset & 3 || (माप_प्रकार)buf & 3 ||
	    count < 384 || mtd->oops_panic_ग_लिखो)
		जाओ out_copy;

	xtra = count & 3;
	अगर (xtra) अणु
		count -= xtra;
		स_नकल(buf + count, this->base + bram_offset + count, xtra);
	पूर्ण

	dma_dst = dma_map_single(dev, buf, count, DMA_FROM_DEVICE);
	dma_src = c->phys_base + bram_offset;

	अगर (dma_mapping_error(dev, dma_dst)) अणु
		dev_err(dev, "Couldn't DMA map a %d byte buffer\n", count);
		जाओ out_copy;
	पूर्ण

	err = omap2_onenand_dma_transfer(c, dma_src, dma_dst, count);
	dma_unmap_single(dev, dma_dst, count, DMA_FROM_DEVICE);
	अगर (!err)
		वापस 0;

	dev_err(dev, "timeout waiting for DMA\n");

out_copy:
	स_नकल(buf, this->base + bram_offset, count);
	वापस 0;
पूर्ण

अटल पूर्णांक omap2_onenand_ग_लिखो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
					 स्थिर अचिन्हित अक्षर *buffer,
					 पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा omap2_onenand *c = container_of(mtd, काष्ठा omap2_onenand, mtd);
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा device *dev = &c->pdev->dev;
	व्योम *buf = (व्योम *)buffer;
	dma_addr_t dma_src, dma_dst;
	पूर्णांक bram_offset, err;

	bram_offset = omap2_onenand_bufferram_offset(mtd, area) + area + offset;
	/*
	 * If the buffer address is not DMA-able, len is not दीर्घ enough to
	 * make DMA transfers profitable or अगर invoked from panic_ग_लिखो()
	 * fallback to PIO mode.
	 */
	अगर (!virt_addr_valid(buf) || bram_offset & 3 || (माप_प्रकार)buf & 3 ||
	    count < 384 || mtd->oops_panic_ग_लिखो)
		जाओ out_copy;

	dma_src = dma_map_single(dev, buf, count, DMA_TO_DEVICE);
	dma_dst = c->phys_base + bram_offset;
	अगर (dma_mapping_error(dev, dma_src)) अणु
		dev_err(dev, "Couldn't DMA map a %d byte buffer\n", count);
		जाओ out_copy;
	पूर्ण

	err = omap2_onenand_dma_transfer(c, dma_src, dma_dst, count);
	dma_unmap_page(dev, dma_src, count, DMA_TO_DEVICE);
	अगर (!err)
		वापस 0;

	dev_err(dev, "timeout waiting for DMA\n");

out_copy:
	स_नकल(this->base + bram_offset, buf, count);
	वापस 0;
पूर्ण

अटल व्योम omap2_onenand_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap2_onenand *c = dev_get_drvdata(&pdev->dev);

	/* With certain content in the buffer RAM, the OMAP boot ROM code
	 * can recognize the flash chip incorrectly. Zero it out beक्रमe
	 * soft reset.
	 */
	स_रखो((__क्रमce व्योम *)c->onenand.base, 0, ONEन_अंकD_BUFRAM_SIZE);
पूर्ण

अटल पूर्णांक omap2_onenand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 val;
	dma_cap_mask_t mask;
	पूर्णांक freq, latency, r;
	काष्ठा resource *res;
	काष्ठा omap2_onenand *c;
	काष्ठा gpmc_onenand_info info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "error getting memory resource\n");
		वापस -EINVAL;
	पूर्ण

	r = of_property_पढ़ो_u32(np, "reg", &val);
	अगर (r) अणु
		dev_err(dev, "reg not found in DT\n");
		वापस r;
	पूर्ण

	c = devm_kzalloc(dev, माप(काष्ठा omap2_onenand), GFP_KERNEL);
	अगर (!c)
		वापस -ENOMEM;

	init_completion(&c->irq_करोne);
	init_completion(&c->dma_करोne);
	c->gpmc_cs = val;
	c->phys_base = res->start;

	c->onenand.base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(c->onenand.base))
		वापस PTR_ERR(c->onenand.base);

	c->पूर्णांक_gpiod = devm_gpiod_get_optional(dev, "int", GPIOD_IN);
	अगर (IS_ERR(c->पूर्णांक_gpiod)) अणु
		/* Just try again अगर this happens */
		वापस dev_err_probe(dev, PTR_ERR(c->पूर्णांक_gpiod), "error getting gpio\n");
	पूर्ण

	अगर (c->पूर्णांक_gpiod) अणु
		r = devm_request_irq(dev, gpiod_to_irq(c->पूर्णांक_gpiod),
				     omap2_onenand_पूर्णांकerrupt,
				     IRQF_TRIGGER_RISING, "onenand", c);
		अगर (r)
			वापस r;

		c->onenand.रुको = omap2_onenand_रुको;
	पूर्ण

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	c->dma_chan = dma_request_channel(mask, शून्य, शून्य);
	अगर (c->dma_chan) अणु
		c->onenand.पढ़ो_bufferram = omap2_onenand_पढ़ो_bufferram;
		c->onenand.ग_लिखो_bufferram = omap2_onenand_ग_लिखो_bufferram;
	पूर्ण

	c->pdev = pdev;
	c->mtd.priv = &c->onenand;
	c->mtd.dev.parent = dev;
	mtd_set_of_node(&c->mtd, dev->of_node);

	dev_info(dev, "initializing on CS%d (0x%08lx), va %p, %s mode\n",
		 c->gpmc_cs, c->phys_base, c->onenand.base,
		 c->dma_chan ? "DMA" : "PIO");

	r = onenand_scan(&c->mtd, 1);
	अगर (r < 0)
		जाओ err_release_dma;

	freq = omap2_onenand_get_freq(c->onenand.version_id);
	अगर (freq > 0) अणु
		चयन (freq) अणु
		हाल 104:
			latency = 7;
			अवरोध;
		हाल 83:
			latency = 6;
			अवरोध;
		हाल 66:
			latency = 5;
			अवरोध;
		हाल 56:
			latency = 4;
			अवरोध;
		शेष:	/* 40 MHz or lower */
			latency = 3;
			अवरोध;
		पूर्ण

		r = gpmc_omap_onenand_set_timings(dev, c->gpmc_cs,
						  freq, latency, &info);
		अगर (r)
			जाओ err_release_onenand;

		r = omap2_onenand_set_cfg(c, info.sync_पढ़ो, info.sync_ग_लिखो,
					  latency, info.burst_len);
		अगर (r)
			जाओ err_release_onenand;

		अगर (info.sync_पढ़ो || info.sync_ग_लिखो)
			dev_info(dev, "optimized timings for %d MHz\n", freq);
	पूर्ण

	r = mtd_device_रेजिस्टर(&c->mtd, शून्य, 0);
	अगर (r)
		जाओ err_release_onenand;

	platक्रमm_set_drvdata(pdev, c);

	वापस 0;

err_release_onenand:
	onenand_release(&c->mtd);
err_release_dma:
	अगर (c->dma_chan)
		dma_release_channel(c->dma_chan);

	वापस r;
पूर्ण

अटल पूर्णांक omap2_onenand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap2_onenand *c = dev_get_drvdata(&pdev->dev);

	onenand_release(&c->mtd);
	अगर (c->dma_chan)
		dma_release_channel(c->dma_chan);
	omap2_onenand_shutकरोwn(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap2_onenand_id_table[] = अणु
	अणु .compatible = "ti,omap2-onenand", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap2_onenand_id_table);

अटल काष्ठा platक्रमm_driver omap2_onenand_driver = अणु
	.probe		= omap2_onenand_probe,
	.हटाओ		= omap2_onenand_हटाओ,
	.shutकरोwn	= omap2_onenand_shutकरोwn,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = omap2_onenand_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap2_onenand_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarkko Lavinen <jarkko.lavinen@nokia.com>");
MODULE_DESCRIPTION("Glue layer for OneNAND flash on OMAP2 / OMAP3");
