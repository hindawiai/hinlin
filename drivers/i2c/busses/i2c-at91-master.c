<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  i2c Support क्रम Aपंचांगel's AT91 Two-Wire Interface (TWI)
 *
 *  Copyright (C) 2011 Weinmann Medical GmbH
 *  Author: Nikolaus Voss <n.voss@weinmann.de>
 *
 *  Evolved from original work by:
 *  Copyright (C) 2004 Rick Bronson
 *  Converted to 2.6 by Andrew Victor <andrew@sanpeople.com>
 *
 *  Borrowed heavily from original work by:
 *  Copyright (C) 2000 Philip Edelbrock <phil@stimpy.netroedge.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "i2c-at91.h"

व्योम at91_init_twi_bus_master(काष्ठा at91_twi_dev *dev)
अणु
	काष्ठा at91_twi_pdata *pdata = dev->pdata;
	u32 filtr = 0;

	/* FIFO should be enabled immediately after the software reset */
	अगर (dev->fअगरo_size)
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_FIFOEN);
	at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_MSEN);
	at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_SVDIS);
	at91_twi_ग_लिखो(dev, AT91_TWI_CWGR, dev->twi_cwgr_reg);

	/* enable digital filter */
	अगर (pdata->has_dig_filtr && dev->enable_dig_filt)
		filtr |= AT91_TWI_FILTR_FILT;

	/* enable advanced digital filter */
	अगर (pdata->has_adv_dig_filtr && dev->enable_dig_filt)
		filtr |= AT91_TWI_FILTR_FILT |
			 (AT91_TWI_FILTR_THRES(dev->filter_width) &
			 AT91_TWI_FILTR_THRES_MASK);

	/* enable analog filter */
	अगर (pdata->has_ana_filtr && dev->enable_ana_filt)
		filtr |= AT91_TWI_FILTR_PADFEN;

	अगर (filtr)
		at91_twi_ग_लिखो(dev, AT91_TWI_FILTR, filtr);
पूर्ण

/*
 * Calculate symmetric घड़ी as stated in datasheet:
 * twi_clk = F_MAIN / (2 * (cभाग * (1 << ckभाग) + offset))
 */
अटल व्योम at91_calc_twi_घड़ी(काष्ठा at91_twi_dev *dev)
अणु
	पूर्णांक ckभाग, cभाग, भाग, hold = 0, filter_width = 0;
	काष्ठा at91_twi_pdata *pdata = dev->pdata;
	पूर्णांक offset = pdata->clk_offset;
	पूर्णांक max_ckभाग = pdata->clk_max_भाग;
	काष्ठा i2c_timings timings, *t = &timings;

	i2c_parse_fw_timings(dev->dev, t, true);

	भाग = max(0, (पूर्णांक)DIV_ROUND_UP(clk_get_rate(dev->clk),
				       2 * t->bus_freq_hz) - offset);
	ckभाग = fls(भाग >> 8);
	cभाग = भाग >> ckभाग;

	अगर (ckभाग > max_ckभाग) अणु
		dev_warn(dev->dev, "%d exceeds ckdiv max value which is %d.\n",
			 ckभाग, max_ckभाग);
		ckभाग = max_ckभाग;
		cभाग = 255;
	पूर्ण

	अगर (pdata->has_hold_field) अणु
		/*
		 * hold समय = HOLD + 3 x T_peripheral_घड़ी
		 * Use clk rate in kHz to prevent overflows when computing
		 * hold.
		 */
		hold = DIV_ROUND_UP(t->sda_hold_ns
				    * (clk_get_rate(dev->clk) / 1000), 1000000);
		hold -= 3;
		अगर (hold < 0)
			hold = 0;
		अगर (hold > AT91_TWI_CWGR_HOLD_MAX) अणु
			dev_warn(dev->dev,
				 "HOLD field set to its maximum value (%d instead of %d)\n",
				 AT91_TWI_CWGR_HOLD_MAX, hold);
			hold = AT91_TWI_CWGR_HOLD_MAX;
		पूर्ण
	पूर्ण

	अगर (pdata->has_adv_dig_filtr) अणु
		/*
		 * filter width = 0 to AT91_TWI_FILTR_THRES_MAX
		 * peripheral घड़ीs
		 */
		filter_width = DIV_ROUND_UP(t->digital_filter_width_ns
				* (clk_get_rate(dev->clk) / 1000), 1000000);
		अगर (filter_width > AT91_TWI_FILTR_THRES_MAX) अणु
			dev_warn(dev->dev,
				"Filter threshold set to its maximum value (%d instead of %d)\n",
				AT91_TWI_FILTR_THRES_MAX, filter_width);
			filter_width = AT91_TWI_FILTR_THRES_MAX;
		पूर्ण
	पूर्ण

	dev->twi_cwgr_reg = (ckभाग << 16) | (cभाग << 8) | cभाग
			    | AT91_TWI_CWGR_HOLD(hold);

	dev->filter_width = filter_width;

	dev_dbg(dev->dev, "cdiv %d ckdiv %d hold %d (%d ns), filter_width %d (%d ns)\n",
		cभाग, ckभाग, hold, t->sda_hold_ns, filter_width,
		t->digital_filter_width_ns);
पूर्ण

अटल व्योम at91_twi_dma_cleanup(काष्ठा at91_twi_dev *dev)
अणु
	काष्ठा at91_twi_dma *dma = &dev->dma;

	at91_twi_irq_save(dev);

	अगर (dma->xfer_in_progress) अणु
		अगर (dma->direction == DMA_FROM_DEVICE)
			dmaengine_terminate_all(dma->chan_rx);
		अन्यथा
			dmaengine_terminate_all(dma->chan_tx);
		dma->xfer_in_progress = false;
	पूर्ण
	अगर (dma->buf_mapped) अणु
		dma_unmap_single(dev->dev, sg_dma_address(&dma->sg[0]),
				 dev->buf_len, dma->direction);
		dma->buf_mapped = false;
	पूर्ण

	at91_twi_irq_restore(dev);
पूर्ण

अटल व्योम at91_twi_ग_लिखो_next_byte(काष्ठा at91_twi_dev *dev)
अणु
	अगर (!dev->buf_len)
		वापस;

	/* 8bit ग_लिखो works with and without FIFO */
	ग_लिखोb_relaxed(*dev->buf, dev->base + AT91_TWI_THR);

	/* send stop when last byte has been written */
	अगर (--dev->buf_len == 0) अणु
		अगर (!dev->use_alt_cmd)
			at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_STOP);
		at91_twi_ग_लिखो(dev, AT91_TWI_IDR, AT91_TWI_TXRDY);
	पूर्ण

	dev_dbg(dev->dev, "wrote 0x%x, to go %zu\n", *dev->buf, dev->buf_len);

	++dev->buf;
पूर्ण

अटल व्योम at91_twi_ग_लिखो_data_dma_callback(व्योम *data)
अणु
	काष्ठा at91_twi_dev *dev = (काष्ठा at91_twi_dev *)data;

	dma_unmap_single(dev->dev, sg_dma_address(&dev->dma.sg[0]),
			 dev->buf_len, DMA_TO_DEVICE);

	/*
	 * When this callback is called, THR/TX FIFO is likely not to be empty
	 * yet. So we have to रुको क्रम TXCOMP or NACK bits to be set पूर्णांकo the
	 * Status Register to be sure that the STOP bit has been sent and the
	 * transfer is completed. The NACK पूर्णांकerrupt has alपढ़ोy been enabled,
	 * we just have to enable TXCOMP one.
	 */
	at91_twi_ग_लिखो(dev, AT91_TWI_IER, AT91_TWI_TXCOMP);
	अगर (!dev->use_alt_cmd)
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_STOP);
पूर्ण

अटल व्योम at91_twi_ग_लिखो_data_dma(काष्ठा at91_twi_dev *dev)
अणु
	dma_addr_t dma_addr;
	काष्ठा dma_async_tx_descriptor *txdesc;
	काष्ठा at91_twi_dma *dma = &dev->dma;
	काष्ठा dma_chan *chan_tx = dma->chan_tx;
	अचिन्हित पूर्णांक sg_len = 1;

	अगर (!dev->buf_len)
		वापस;

	dma->direction = DMA_TO_DEVICE;

	at91_twi_irq_save(dev);
	dma_addr = dma_map_single(dev->dev, dev->buf, dev->buf_len,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev->dev, dma_addr)) अणु
		dev_err(dev->dev, "dma map failed\n");
		वापस;
	पूर्ण
	dma->buf_mapped = true;
	at91_twi_irq_restore(dev);

	अगर (dev->fअगरo_size) अणु
		माप_प्रकार part1_len, part2_len;
		काष्ठा scatterlist *sg;
		अचिन्हित fअगरo_mr;

		sg_len = 0;

		part1_len = dev->buf_len & ~0x3;
		अगर (part1_len) अणु
			sg = &dma->sg[sg_len++];
			sg_dma_len(sg) = part1_len;
			sg_dma_address(sg) = dma_addr;
		पूर्ण

		part2_len = dev->buf_len & 0x3;
		अगर (part2_len) अणु
			sg = &dma->sg[sg_len++];
			sg_dma_len(sg) = part2_len;
			sg_dma_address(sg) = dma_addr + part1_len;
		पूर्ण

		/*
		 * DMA controller is triggered when at least 4 data can be
		 * written पूर्णांकo the TX FIFO
		 */
		fअगरo_mr = at91_twi_पढ़ो(dev, AT91_TWI_FMR);
		fअगरo_mr &= ~AT91_TWI_FMR_TXRDYM_MASK;
		fअगरo_mr |= AT91_TWI_FMR_TXRDYM(AT91_TWI_FOUR_DATA);
		at91_twi_ग_लिखो(dev, AT91_TWI_FMR, fअगरo_mr);
	पूर्ण अन्यथा अणु
		sg_dma_len(&dma->sg[0]) = dev->buf_len;
		sg_dma_address(&dma->sg[0]) = dma_addr;
	पूर्ण

	txdesc = dmaengine_prep_slave_sg(chan_tx, dma->sg, sg_len,
					 DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!txdesc) अणु
		dev_err(dev->dev, "dma prep slave sg failed\n");
		जाओ error;
	पूर्ण

	txdesc->callback = at91_twi_ग_लिखो_data_dma_callback;
	txdesc->callback_param = dev;

	dma->xfer_in_progress = true;
	dmaengine_submit(txdesc);
	dma_async_issue_pending(chan_tx);

	वापस;

error:
	at91_twi_dma_cleanup(dev);
पूर्ण

अटल व्योम at91_twi_पढ़ो_next_byte(काष्ठा at91_twi_dev *dev)
अणु
	/*
	 * If we are in this हाल, it means there is garbage data in RHR, so
	 * delete them.
	 */
	अगर (!dev->buf_len) अणु
		at91_twi_पढ़ो(dev, AT91_TWI_RHR);
		वापस;
	पूर्ण

	/* 8bit पढ़ो works with and without FIFO */
	*dev->buf = पढ़ोb_relaxed(dev->base + AT91_TWI_RHR);
	--dev->buf_len;

	/* वापस अगर पातing, we only needed to पढ़ो RHR to clear RXRDY*/
	अगर (dev->recv_len_पात)
		वापस;

	/* handle I2C_SMBUS_BLOCK_DATA */
	अगर (unlikely(dev->msg->flags & I2C_M_RECV_LEN)) अणु
		/* ensure length byte is a valid value */
		अगर (*dev->buf <= I2C_SMBUS_BLOCK_MAX && *dev->buf > 0) अणु
			dev->msg->flags &= ~I2C_M_RECV_LEN;
			dev->buf_len += *dev->buf;
			dev->msg->len = dev->buf_len + 1;
			dev_dbg(dev->dev, "received block length %zu\n",
					 dev->buf_len);
		पूर्ण अन्यथा अणु
			/* पात and send the stop by पढ़ोing one more byte */
			dev->recv_len_पात = true;
			dev->buf_len = 1;
		पूर्ण
	पूर्ण

	/* send stop अगर second but last byte has been पढ़ो */
	अगर (!dev->use_alt_cmd && dev->buf_len == 1)
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_STOP);

	dev_dbg(dev->dev, "read 0x%x, to go %zu\n", *dev->buf, dev->buf_len);

	++dev->buf;
पूर्ण

अटल व्योम at91_twi_पढ़ो_data_dma_callback(व्योम *data)
अणु
	काष्ठा at91_twi_dev *dev = (काष्ठा at91_twi_dev *)data;
	अचिन्हित ier = AT91_TWI_TXCOMP;

	dma_unmap_single(dev->dev, sg_dma_address(&dev->dma.sg[0]),
			 dev->buf_len, DMA_FROM_DEVICE);

	अगर (!dev->use_alt_cmd) अणु
		/* The last two bytes have to be पढ़ो without using dma */
		dev->buf += dev->buf_len - 2;
		dev->buf_len = 2;
		ier |= AT91_TWI_RXRDY;
	पूर्ण
	at91_twi_ग_लिखो(dev, AT91_TWI_IER, ier);
पूर्ण

अटल व्योम at91_twi_पढ़ो_data_dma(काष्ठा at91_twi_dev *dev)
अणु
	dma_addr_t dma_addr;
	काष्ठा dma_async_tx_descriptor *rxdesc;
	काष्ठा at91_twi_dma *dma = &dev->dma;
	काष्ठा dma_chan *chan_rx = dma->chan_rx;
	माप_प्रकार buf_len;

	buf_len = (dev->use_alt_cmd) ? dev->buf_len : dev->buf_len - 2;
	dma->direction = DMA_FROM_DEVICE;

	/* Keep in mind that we won't use dma to पढ़ो the last two bytes */
	at91_twi_irq_save(dev);
	dma_addr = dma_map_single(dev->dev, dev->buf, buf_len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev->dev, dma_addr)) अणु
		dev_err(dev->dev, "dma map failed\n");
		वापस;
	पूर्ण
	dma->buf_mapped = true;
	at91_twi_irq_restore(dev);

	अगर (dev->fअगरo_size && IS_ALIGNED(buf_len, 4)) अणु
		अचिन्हित fअगरo_mr;

		/*
		 * DMA controller is triggered when at least 4 data can be
		 * पढ़ो from the RX FIFO
		 */
		fअगरo_mr = at91_twi_पढ़ो(dev, AT91_TWI_FMR);
		fअगरo_mr &= ~AT91_TWI_FMR_RXRDYM_MASK;
		fअगरo_mr |= AT91_TWI_FMR_RXRDYM(AT91_TWI_FOUR_DATA);
		at91_twi_ग_लिखो(dev, AT91_TWI_FMR, fअगरo_mr);
	पूर्ण

	sg_dma_len(&dma->sg[0]) = buf_len;
	sg_dma_address(&dma->sg[0]) = dma_addr;

	rxdesc = dmaengine_prep_slave_sg(chan_rx, dma->sg, 1, DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!rxdesc) अणु
		dev_err(dev->dev, "dma prep slave sg failed\n");
		जाओ error;
	पूर्ण

	rxdesc->callback = at91_twi_पढ़ो_data_dma_callback;
	rxdesc->callback_param = dev;

	dma->xfer_in_progress = true;
	dmaengine_submit(rxdesc);
	dma_async_issue_pending(dma->chan_rx);

	वापस;

error:
	at91_twi_dma_cleanup(dev);
पूर्ण

अटल irqवापस_t aपंचांगel_twi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा at91_twi_dev *dev = dev_id;
	स्थिर अचिन्हित status = at91_twi_पढ़ो(dev, AT91_TWI_SR);
	स्थिर अचिन्हित irqstatus = status & at91_twi_पढ़ो(dev, AT91_TWI_IMR);

	अगर (!irqstatus)
		वापस IRQ_NONE;
	/*
	 * In reception, the behavior of the twi device (beक्रमe sama5d2) is
	 * weird. There is some magic about RXRDY flag! When a data has been
	 * almost received, the reception of a new one is anticipated अगर there
	 * is no stop command to send. That is the reason why ask क्रम sending
	 * the stop command not on the last data but on the second last one.
	 *
	 * Unक्रमtunately, we could still have the RXRDY flag set even अगर the
	 * transfer is करोne and we have पढ़ो the last data. It might happen
	 * when the i2c slave device sends too quickly data after receiving the
	 * ack from the master. The data has been almost received beक्रमe having
	 * the order to send stop. In this हाल, sending the stop command could
	 * cause a RXRDY पूर्णांकerrupt with a TXCOMP one. It is better to manage
	 * the RXRDY पूर्णांकerrupt first in order to not keep garbage data in the
	 * Receive Holding Register क्रम the next transfer.
	 */
	अगर (irqstatus & AT91_TWI_RXRDY) अणु
		/*
		 * Read all available bytes at once by polling RXRDY usable w/
		 * and w/o FIFO. With FIFO enabled we could also पढ़ो RXFL and
		 * aव्योम polling RXRDY.
		 */
		करो अणु
			at91_twi_पढ़ो_next_byte(dev);
		पूर्ण जबतक (at91_twi_पढ़ो(dev, AT91_TWI_SR) & AT91_TWI_RXRDY);
	पूर्ण

	/*
	 * When a NACK condition is detected, the I2C controller sets the NACK,
	 * TXCOMP and TXRDY bits all together in the Status Register (SR).
	 *
	 * 1 - Handling NACK errors with CPU ग_लिखो transfer.
	 *
	 * In such हाल, we should not ग_लिखो the next byte पूर्णांकo the Transmit
	 * Holding Register (THR) otherwise the I2C controller would start a new
	 * transfer and the I2C slave is likely to reply by another NACK.
	 *
	 * 2 - Handling NACK errors with DMA ग_लिखो transfer.
	 *
	 * By setting the TXRDY bit in the SR, the I2C controller also triggers
	 * the DMA controller to ग_लिखो the next data पूर्णांकo the THR. Then the
	 * result depends on the hardware version of the I2C controller.
	 *
	 * 2a - Without support of the Alternative Command mode.
	 *
	 * This is the worst हाल: the DMA controller is triggered to ग_लिखो the
	 * next data पूर्णांकo the THR, hence starting a new transfer: the I2C slave
	 * is likely to reply by another NACK.
	 * Concurrently, this पूर्णांकerrupt handler is likely to be called to manage
	 * the first NACK beक्रमe the I2C controller detects the second NACK and
	 * sets once again the NACK bit पूर्णांकo the SR.
	 * When handling the first NACK, this पूर्णांकerrupt handler disables the I2C
	 * controller पूर्णांकerruptions, especially the NACK पूर्णांकerrupt.
	 * Hence, the NACK bit is pending पूर्णांकo the SR. This is why we should
	 * पढ़ो the SR to clear all pending पूर्णांकerrupts at the beginning of
	 * at91_करो_twi_transfer() beक्रमe actually starting a new transfer.
	 *
	 * 2b - With support of the Alternative Command mode.
	 *
	 * When a NACK condition is detected, the I2C controller also locks the
	 * THR (and sets the LOCK bit in the SR): even though the DMA controller
	 * is triggered by the TXRDY bit to ग_लिखो the next data पूर्णांकo the THR,
	 * this data actually won't go on the I2C bus hence a second NACK is not
	 * generated.
	 */
	अगर (irqstatus & (AT91_TWI_TXCOMP | AT91_TWI_NACK)) अणु
		at91_disable_twi_पूर्णांकerrupts(dev);
		complete(&dev->cmd_complete);
	पूर्ण अन्यथा अगर (irqstatus & AT91_TWI_TXRDY) अणु
		at91_twi_ग_लिखो_next_byte(dev);
	पूर्ण

	/* catch error flags */
	dev->transfer_status |= status;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक at91_करो_twi_transfer(काष्ठा at91_twi_dev *dev)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;
	bool has_unre_flag = dev->pdata->has_unre_flag;
	bool has_alt_cmd = dev->pdata->has_alt_cmd;

	/*
	 * WARNING: the TXCOMP bit in the Status Register is NOT a clear on
	 * पढ़ो flag but shows the state of the transmission at the समय the
	 * Status Register is पढ़ो. According to the programmer datasheet,
	 * TXCOMP is set when both holding रेजिस्टर and पूर्णांकernal shअगरter are
	 * empty and STOP condition has been sent.
	 * Consequently, we should enable NACK पूर्णांकerrupt rather than TXCOMP to
	 * detect transmission failure.
	 * Indeed let's take the हाल of an i2c ग_लिखो command using DMA.
	 * Whenever the slave करोesn't acknowledge a byte, the LOCK, NACK and
	 * TXCOMP bits are set together पूर्णांकo the Status Register.
	 * LOCK is a clear on ग_लिखो bit, which is set to prevent the DMA
	 * controller from sending new data on the i2c bus after a NACK
	 * condition has happened. Once locked, this i2c peripheral stops
	 * triggering the DMA controller क्रम new data but it is more than
	 * likely that a new DMA transaction is alपढ़ोy in progress, writing
	 * पूर्णांकo the Transmit Holding Register. Since the peripheral is locked,
	 * these new data won't be sent to the i2c bus but they will reमुख्य
	 * पूर्णांकo the Transmit Holding Register, so TXCOMP bit is cleared.
	 * Then when the पूर्णांकerrupt handler is called, the Status Register is
	 * पढ़ो: the TXCOMP bit is clear but NACK bit is still set. The driver
	 * manage the error properly, without रुकोing क्रम समयout.
	 * This हाल can be reproduced easyly when writing पूर्णांकo an at24 eeprom.
	 *
	 * Besides, the TXCOMP bit is alपढ़ोy set beक्रमe the i2c transaction
	 * has been started. For पढ़ो transactions, this bit is cleared when
	 * writing the START bit पूर्णांकo the Control Register. So the
	 * corresponding पूर्णांकerrupt can safely be enabled just after.
	 * However क्रम ग_लिखो transactions managed by the CPU, we first ग_लिखो
	 * पूर्णांकo THR, so TXCOMP is cleared. Then we can safely enable TXCOMP
	 * पूर्णांकerrupt. If TXCOMP पूर्णांकerrupt were enabled beक्रमe writing पूर्णांकo THR,
	 * the पूर्णांकerrupt handler would be called immediately and the i2c command
	 * would be reported as completed.
	 * Also when a ग_लिखो transaction is managed by the DMA controller,
	 * enabling the TXCOMP पूर्णांकerrupt in this function may lead to a race
	 * condition since we करोn't know whether the TXCOMP पूर्णांकerrupt is enabled
	 * beक्रमe or after the DMA has started to ग_लिखो पूर्णांकo THR. So the TXCOMP
	 * पूर्णांकerrupt is enabled later by at91_twi_ग_लिखो_data_dma_callback().
	 * Immediately after in that DMA callback, अगर the alternative command
	 * mode is not used, we still need to send the STOP condition manually
	 * writing the corresponding bit पूर्णांकo the Control Register.
	 */

	dev_dbg(dev->dev, "transfer: %s %zu bytes.\n",
		(dev->msg->flags & I2C_M_RD) ? "read" : "write", dev->buf_len);

	reinit_completion(&dev->cmd_complete);
	dev->transfer_status = 0;

	/* Clear pending पूर्णांकerrupts, such as NACK. */
	at91_twi_पढ़ो(dev, AT91_TWI_SR);

	अगर (dev->fअगरo_size) अणु
		अचिन्हित fअगरo_mr = at91_twi_पढ़ो(dev, AT91_TWI_FMR);

		/* Reset FIFO mode रेजिस्टर */
		fअगरo_mr &= ~(AT91_TWI_FMR_TXRDYM_MASK |
			     AT91_TWI_FMR_RXRDYM_MASK);
		fअगरo_mr |= AT91_TWI_FMR_TXRDYM(AT91_TWI_ONE_DATA);
		fअगरo_mr |= AT91_TWI_FMR_RXRDYM(AT91_TWI_ONE_DATA);
		at91_twi_ग_लिखो(dev, AT91_TWI_FMR, fअगरo_mr);

		/* Flush FIFOs */
		at91_twi_ग_लिखो(dev, AT91_TWI_CR,
			       AT91_TWI_THRCLR | AT91_TWI_RHRCLR);
	पूर्ण

	अगर (!dev->buf_len) अणु
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_QUICK);
		at91_twi_ग_लिखो(dev, AT91_TWI_IER, AT91_TWI_TXCOMP);
	पूर्ण अन्यथा अगर (dev->msg->flags & I2C_M_RD) अणु
		अचिन्हित start_flags = AT91_TWI_START;

		/* अगर only one byte is to be पढ़ो, immediately stop transfer */
		अगर (!dev->use_alt_cmd && dev->buf_len <= 1 &&
		    !(dev->msg->flags & I2C_M_RECV_LEN))
			start_flags |= AT91_TWI_STOP;
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, start_flags);
		/*
		 * When using dma without alternative command mode, the last
		 * byte has to be पढ़ो manually in order to not send the stop
		 * command too late and then to receive extra data.
		 * In practice, there are some issues अगर you use the dma to
		 * पढ़ो n-1 bytes because of latency.
		 * Reading n-2 bytes with dma and the two last ones manually
		 * seems to be the best solution.
		 */
		अगर (dev->use_dma && (dev->buf_len > AT91_I2C_DMA_THRESHOLD)) अणु
			at91_twi_ग_लिखो(dev, AT91_TWI_IER, AT91_TWI_NACK);
			at91_twi_पढ़ो_data_dma(dev);
		पूर्ण अन्यथा अणु
			at91_twi_ग_लिखो(dev, AT91_TWI_IER,
				       AT91_TWI_TXCOMP |
				       AT91_TWI_NACK |
				       AT91_TWI_RXRDY);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dev->use_dma && (dev->buf_len > AT91_I2C_DMA_THRESHOLD)) अणु
			at91_twi_ग_लिखो(dev, AT91_TWI_IER, AT91_TWI_NACK);
			at91_twi_ग_लिखो_data_dma(dev);
		पूर्ण अन्यथा अणु
			at91_twi_ग_लिखो_next_byte(dev);
			at91_twi_ग_लिखो(dev, AT91_TWI_IER,
				       AT91_TWI_TXCOMP | AT91_TWI_NACK |
				       (dev->buf_len ? AT91_TWI_TXRDY : 0));
		पूर्ण
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&dev->cmd_complete,
					      dev->adapter.समयout);
	अगर (समय_left == 0) अणु
		dev->transfer_status |= at91_twi_पढ़ो(dev, AT91_TWI_SR);
		dev_err(dev->dev, "controller timed out\n");
		at91_init_twi_bus(dev);
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण
	अगर (dev->transfer_status & AT91_TWI_NACK) अणु
		dev_dbg(dev->dev, "received nack\n");
		ret = -EREMOTEIO;
		जाओ error;
	पूर्ण
	अगर (dev->transfer_status & AT91_TWI_OVRE) अणु
		dev_err(dev->dev, "overrun while reading\n");
		ret = -EIO;
		जाओ error;
	पूर्ण
	अगर (has_unre_flag && dev->transfer_status & AT91_TWI_UNRE) अणु
		dev_err(dev->dev, "underrun while writing\n");
		ret = -EIO;
		जाओ error;
	पूर्ण
	अगर ((has_alt_cmd || dev->fअगरo_size) &&
	    (dev->transfer_status & AT91_TWI_LOCK)) अणु
		dev_err(dev->dev, "tx locked\n");
		ret = -EIO;
		जाओ error;
	पूर्ण
	अगर (dev->recv_len_पात) अणु
		dev_err(dev->dev, "invalid smbus block length recvd\n");
		ret = -EPROTO;
		जाओ error;
	पूर्ण

	dev_dbg(dev->dev, "transfer complete\n");

	वापस 0;

error:
	/* first stop DMA transfer अगर still in progress */
	at91_twi_dma_cleanup(dev);
	/* then flush THR/FIFO and unlock TX अगर locked */
	अगर ((has_alt_cmd || dev->fअगरo_size) &&
	    (dev->transfer_status & AT91_TWI_LOCK)) अणु
		dev_dbg(dev->dev, "unlock tx\n");
		at91_twi_ग_लिखो(dev, AT91_TWI_CR,
			       AT91_TWI_THRCLR | AT91_TWI_LOCKCLR);
	पूर्ण

	/*
	 * some faulty I2C slave devices might hold SDA करोwn;
	 * we can send a bus clear command, hoping that the pins will be
	 * released
	 */
	i2c_recover_bus(&dev->adapter);

	वापस ret;
पूर्ण

अटल पूर्णांक at91_twi_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	काष्ठा at91_twi_dev *dev = i2c_get_adapdata(adap);
	पूर्णांक ret;
	अचिन्हित पूर्णांक_addr_flag = 0;
	काष्ठा i2c_msg *m_start = msg;
	bool is_पढ़ो;

	dev_dbg(&adap->dev, "at91_xfer: processing %d messages:\n", num);

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0)
		जाओ out;

	अगर (num == 2) अणु
		पूर्णांक पूर्णांकernal_address = 0;
		पूर्णांक i;

		/* 1st msg is put पूर्णांकo the पूर्णांकernal address, start with 2nd */
		m_start = &msg[1];
		क्रम (i = 0; i < msg->len; ++i) अणु
			स्थिर अचिन्हित addr = msg->buf[msg->len - 1 - i];

			पूर्णांकernal_address |= addr << (8 * i);
			पूर्णांक_addr_flag += AT91_TWI_IADRSZ_1;
		पूर्ण
		at91_twi_ग_लिखो(dev, AT91_TWI_IADR, पूर्णांकernal_address);
	पूर्ण

	dev->use_alt_cmd = false;
	is_पढ़ो = (m_start->flags & I2C_M_RD);
	अगर (dev->pdata->has_alt_cmd) अणु
		अगर (m_start->len > 0 &&
		    m_start->len < AT91_I2C_MAX_ALT_CMD_DATA_SIZE) अणु
			at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_ACMEN);
			at91_twi_ग_लिखो(dev, AT91_TWI_ACR,
				       AT91_TWI_ACR_DATAL(m_start->len) |
				       ((is_पढ़ो) ? AT91_TWI_ACR_सूची : 0));
			dev->use_alt_cmd = true;
		पूर्ण अन्यथा अणु
			at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_ACMDIS);
		पूर्ण
	पूर्ण

	at91_twi_ग_लिखो(dev, AT91_TWI_MMR,
		       (m_start->addr << 16) |
		       पूर्णांक_addr_flag |
		       ((!dev->use_alt_cmd && is_पढ़ो) ? AT91_TWI_MREAD : 0));

	dev->buf_len = m_start->len;
	dev->buf = m_start->buf;
	dev->msg = m_start;
	dev->recv_len_पात = false;

	ret = at91_करो_twi_transfer(dev);

	ret = (ret < 0) ? ret : num;
out:
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस ret;
पूर्ण

/*
 * The hardware can handle at most two messages concatenated by a
 * repeated start via it's पूर्णांकernal address feature.
 */
अटल स्थिर काष्ठा i2c_adapter_quirks at91_twi_quirks = अणु
	.flags = I2C_AQ_COMB | I2C_AQ_COMB_WRITE_FIRST | I2C_AQ_COMB_SAME_ADDR,
	.max_comb_1st_msg_len = 3,
पूर्ण;

अटल u32 at91_twi_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL
		| I2C_FUNC_SMBUS_READ_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm at91_twi_algorithm = अणु
	.master_xfer	= at91_twi_xfer,
	.functionality	= at91_twi_func,
पूर्ण;

अटल पूर्णांक at91_twi_configure_dma(काष्ठा at91_twi_dev *dev, u32 phy_addr)
अणु
	पूर्णांक ret = 0;
	काष्ठा dma_slave_config slave_config;
	काष्ठा at91_twi_dma *dma = &dev->dma;
	क्रमागत dma_slave_buswidth addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;

	/*
	 * The actual width of the access will be chosen in
	 * dmaengine_prep_slave_sg():
	 * क्रम each buffer in the scatter-gather list, अगर its size is aligned
	 * to addr_width then addr_width accesses will be perक्रमmed to transfer
	 * the buffer. On the other hand, अगर the buffer size is not aligned to
	 * addr_width then the buffer is transferred using single byte accesses.
	 * Please refer to the Aपंचांगel eXtended DMA controller driver.
	 * When FIFOs are used, the TXRDYM threshold can always be set to
	 * trigger the XDMAC when at least 4 data can be written पूर्णांकo the TX
	 * FIFO, even अगर single byte accesses are perक्रमmed.
	 * However the RXRDYM threshold must be set to fit the access width,
	 * deduced from buffer length, so the XDMAC is triggered properly to
	 * पढ़ो data from the RX FIFO.
	 */
	अगर (dev->fअगरo_size)
		addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	स_रखो(&slave_config, 0, माप(slave_config));
	slave_config.src_addr = (dma_addr_t)phy_addr + AT91_TWI_RHR;
	slave_config.src_addr_width = addr_width;
	slave_config.src_maxburst = 1;
	slave_config.dst_addr = (dma_addr_t)phy_addr + AT91_TWI_THR;
	slave_config.dst_addr_width = addr_width;
	slave_config.dst_maxburst = 1;
	slave_config.device_fc = false;

	dma->chan_tx = dma_request_chan(dev->dev, "tx");
	अगर (IS_ERR(dma->chan_tx)) अणु
		ret = PTR_ERR(dma->chan_tx);
		dma->chan_tx = शून्य;
		जाओ error;
	पूर्ण

	dma->chan_rx = dma_request_chan(dev->dev, "rx");
	अगर (IS_ERR(dma->chan_rx)) अणु
		ret = PTR_ERR(dma->chan_rx);
		dma->chan_rx = शून्य;
		जाओ error;
	पूर्ण

	slave_config.direction = DMA_MEM_TO_DEV;
	अगर (dmaengine_slave_config(dma->chan_tx, &slave_config)) अणु
		dev_err(dev->dev, "failed to configure tx channel\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	slave_config.direction = DMA_DEV_TO_MEM;
	अगर (dmaengine_slave_config(dma->chan_rx, &slave_config)) अणु
		dev_err(dev->dev, "failed to configure rx channel\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	sg_init_table(dma->sg, 2);
	dma->buf_mapped = false;
	dma->xfer_in_progress = false;
	dev->use_dma = true;

	dev_info(dev->dev, "using %s (tx) and %s (rx) for DMA transfers\n",
		 dma_chan_name(dma->chan_tx), dma_chan_name(dma->chan_rx));

	वापस ret;

error:
	अगर (ret != -EPROBE_DEFER)
		dev_info(dev->dev, "can't get DMA channel, continue without DMA support\n");
	अगर (dma->chan_rx)
		dma_release_channel(dma->chan_rx);
	अगर (dma->chan_tx)
		dma_release_channel(dma->chan_tx);
	वापस ret;
पूर्ण

अटल पूर्णांक at91_init_twi_recovery_gpio(काष्ठा platक्रमm_device *pdev,
				       काष्ठा at91_twi_dev *dev)
अणु
	काष्ठा i2c_bus_recovery_info *rinfo = &dev->rinfo;

	rinfo->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (!rinfo->pinctrl || IS_ERR(rinfo->pinctrl)) अणु
		dev_info(dev->dev, "can't get pinctrl, bus recovery not supported\n");
		वापस PTR_ERR(rinfo->pinctrl);
	पूर्ण
	dev->adapter.bus_recovery_info = rinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक at91_twi_recover_bus_cmd(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा at91_twi_dev *dev = i2c_get_adapdata(adap);

	dev->transfer_status |= at91_twi_पढ़ो(dev, AT91_TWI_SR);
	अगर (!(dev->transfer_status & AT91_TWI_SDA)) अणु
		dev_dbg(dev->dev, "SDA is down; sending bus clear command\n");
		अगर (dev->use_alt_cmd) अणु
			अचिन्हित पूर्णांक acr;

			acr = at91_twi_पढ़ो(dev, AT91_TWI_ACR);
			acr &= ~AT91_TWI_ACR_DATAL_MASK;
			at91_twi_ग_लिखो(dev, AT91_TWI_ACR, acr);
		पूर्ण
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_CLEAR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_init_twi_recovery_info(काष्ठा platक्रमm_device *pdev,
				       काष्ठा at91_twi_dev *dev)
अणु
	काष्ठा i2c_bus_recovery_info *rinfo = &dev->rinfo;
	bool has_clear_cmd = dev->pdata->has_clear_cmd;

	अगर (!has_clear_cmd)
		वापस at91_init_twi_recovery_gpio(pdev, dev);

	rinfo->recover_bus = at91_twi_recover_bus_cmd;
	dev->adapter.bus_recovery_info = rinfo;

	वापस 0;
पूर्ण

पूर्णांक at91_twi_probe_master(काष्ठा platक्रमm_device *pdev,
			  u32 phy_addr, काष्ठा at91_twi_dev *dev)
अणु
	पूर्णांक rc;

	init_completion(&dev->cmd_complete);

	rc = devm_request_irq(&pdev->dev, dev->irq, aपंचांगel_twi_पूर्णांकerrupt, 0,
			      dev_name(dev->dev), dev);
	अगर (rc) अणु
		dev_err(dev->dev, "Cannot get irq %d: %d\n", dev->irq, rc);
		वापस rc;
	पूर्ण

	अगर (dev->dev->of_node) अणु
		rc = at91_twi_configure_dma(dev, phy_addr);
		अगर (rc == -EPROBE_DEFER)
			वापस rc;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "atmel,fifo-size",
				  &dev->fअगरo_size)) अणु
		dev_info(dev->dev, "Using FIFO (%u data)\n", dev->fअगरo_size);
	पूर्ण

	dev->enable_dig_filt = of_property_पढ़ो_bool(pdev->dev.of_node,
						     "i2c-digital-filter");

	dev->enable_ana_filt = of_property_पढ़ो_bool(pdev->dev.of_node,
						     "i2c-analog-filter");
	at91_calc_twi_घड़ी(dev);

	rc = at91_init_twi_recovery_info(pdev, dev);
	अगर (rc == -EPROBE_DEFER)
		वापस rc;

	dev->adapter.algo = &at91_twi_algorithm;
	dev->adapter.quirks = &at91_twi_quirks;

	वापस 0;
पूर्ण
