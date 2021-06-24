<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * This is i.MX low घातer i2c controller driver.
 *
 * Copyright 2016 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#घोषणा DRIVER_NAME "imx-lpi2c"

#घोषणा LPI2C_PARAM	0x04	/* i2c RX/TX FIFO size */
#घोषणा LPI2C_MCR	0x10	/* i2c contrl रेजिस्टर */
#घोषणा LPI2C_MSR	0x14	/* i2c status रेजिस्टर */
#घोषणा LPI2C_MIER	0x18	/* i2c पूर्णांकerrupt enable */
#घोषणा LPI2C_MCFGR0	0x20	/* i2c master configuration */
#घोषणा LPI2C_MCFGR1	0x24	/* i2c master configuration */
#घोषणा LPI2C_MCFGR2	0x28	/* i2c master configuration */
#घोषणा LPI2C_MCFGR3	0x2C	/* i2c master configuration */
#घोषणा LPI2C_MCCR0	0x48	/* i2c master clk configuration */
#घोषणा LPI2C_MCCR1	0x50	/* i2c master clk configuration */
#घोषणा LPI2C_MFCR	0x58	/* i2c master FIFO control */
#घोषणा LPI2C_MFSR	0x5C	/* i2c master FIFO status */
#घोषणा LPI2C_MTDR	0x60	/* i2c master TX data रेजिस्टर */
#घोषणा LPI2C_MRDR	0x70	/* i2c master RX data रेजिस्टर */

/* i2c command */
#घोषणा TRAN_DATA	0X00
#घोषणा RECV_DATA	0X01
#घोषणा GEN_STOP	0X02
#घोषणा RECV_DISCARD	0X03
#घोषणा GEN_START	0X04
#घोषणा START_NACK	0X05
#घोषणा START_HIGH	0X06
#घोषणा START_HIGH_NACK	0X07

#घोषणा MCR_MEN		BIT(0)
#घोषणा MCR_RST		BIT(1)
#घोषणा MCR_DOZEN	BIT(2)
#घोषणा MCR_DBGEN	BIT(3)
#घोषणा MCR_RTF		BIT(8)
#घोषणा MCR_RRF		BIT(9)
#घोषणा MSR_TDF		BIT(0)
#घोषणा MSR_RDF		BIT(1)
#घोषणा MSR_SDF		BIT(9)
#घोषणा MSR_NDF		BIT(10)
#घोषणा MSR_ALF		BIT(11)
#घोषणा MSR_MBF		BIT(24)
#घोषणा MSR_BBF		BIT(25)
#घोषणा MIER_TDIE	BIT(0)
#घोषणा MIER_RDIE	BIT(1)
#घोषणा MIER_SDIE	BIT(9)
#घोषणा MIER_NDIE	BIT(10)
#घोषणा MCFGR1_AUTOSTOP	BIT(8)
#घोषणा MCFGR1_IGNACK	BIT(9)
#घोषणा MRDR_RXEMPTY	BIT(14)

#घोषणा I2C_CLK_RATIO	2
#घोषणा CHUNK_DATA	256

#घोषणा I2C_PM_TIMEOUT		10 /* ms */

क्रमागत lpi2c_imx_mode अणु
	STANDARD,	/* 100+Kbps */
	FAST,		/* 400+Kbps */
	FAST_PLUS,	/* 1.0+Mbps */
	HS,		/* 3.4+Mbps */
	ULTRA_FAST,	/* 5.0+Mbps */
पूर्ण;

क्रमागत lpi2c_imx_pincfg अणु
	TWO_PIN_OD,
	TWO_PIN_OO,
	TWO_PIN_PP,
	FOUR_PIN_PP,
पूर्ण;

काष्ठा lpi2c_imx_काष्ठा अणु
	काष्ठा i2c_adapter	adapter;
	काष्ठा clk		*clk;
	व्योम __iomem		*base;
	__u8			*rx_buf;
	__u8			*tx_buf;
	काष्ठा completion	complete;
	अचिन्हित पूर्णांक		msglen;
	अचिन्हित पूर्णांक		delivered;
	अचिन्हित पूर्णांक		block_data;
	अचिन्हित पूर्णांक		bitrate;
	अचिन्हित पूर्णांक		txfअगरosize;
	अचिन्हित पूर्णांक		rxfअगरosize;
	क्रमागत lpi2c_imx_mode	mode;
पूर्ण;

अटल व्योम lpi2c_imx_पूर्णांकctrl(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx,
			      अचिन्हित पूर्णांक enable)
अणु
	ग_लिखोl(enable, lpi2c_imx->base + LPI2C_MIER);
पूर्ण

अटल पूर्णांक lpi2c_imx_bus_busy(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित दीर्घ orig_jअगरfies = jअगरfies;
	अचिन्हित पूर्णांक temp;

	जबतक (1) अणु
		temp = पढ़ोl(lpi2c_imx->base + LPI2C_MSR);

		/* check क्रम arbitration lost, clear अगर set */
		अगर (temp & MSR_ALF) अणु
			ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MSR);
			वापस -EAGAIN;
		पूर्ण

		अगर (temp & (MSR_BBF | MSR_MBF))
			अवरोध;

		अगर (समय_after(jअगरfies, orig_jअगरfies + msecs_to_jअगरfies(500))) अणु
			dev_dbg(&lpi2c_imx->adapter.dev, "bus not work\n");
			वापस -ETIMEDOUT;
		पूर्ण
		schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lpi2c_imx_set_mode(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित पूर्णांक bitrate = lpi2c_imx->bitrate;
	क्रमागत lpi2c_imx_mode mode;

	अगर (bitrate < I2C_MAX_FAST_MODE_FREQ)
		mode = STANDARD;
	अन्यथा अगर (bitrate < I2C_MAX_FAST_MODE_PLUS_FREQ)
		mode = FAST;
	अन्यथा अगर (bitrate < I2C_MAX_HIGH_SPEED_MODE_FREQ)
		mode = FAST_PLUS;
	अन्यथा अगर (bitrate < I2C_MAX_ULTRA_FAST_MODE_FREQ)
		mode = HS;
	अन्यथा
		mode = ULTRA_FAST;

	lpi2c_imx->mode = mode;
पूर्ण

अटल पूर्णांक lpi2c_imx_start(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx,
			   काष्ठा i2c_msg *msgs)
अणु
	अचिन्हित पूर्णांक temp;

	temp = पढ़ोl(lpi2c_imx->base + LPI2C_MCR);
	temp |= MCR_RRF | MCR_RTF;
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCR);
	ग_लिखोl(0x7f00, lpi2c_imx->base + LPI2C_MSR);

	temp = i2c_8bit_addr_from_msg(msgs) | (GEN_START << 8);
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MTDR);

	वापस lpi2c_imx_bus_busy(lpi2c_imx);
पूर्ण

अटल व्योम lpi2c_imx_stop(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित दीर्घ orig_jअगरfies = jअगरfies;
	अचिन्हित पूर्णांक temp;

	ग_लिखोl(GEN_STOP << 8, lpi2c_imx->base + LPI2C_MTDR);

	करो अणु
		temp = पढ़ोl(lpi2c_imx->base + LPI2C_MSR);
		अगर (temp & MSR_SDF)
			अवरोध;

		अगर (समय_after(jअगरfies, orig_jअगरfies + msecs_to_jअगरfies(500))) अणु
			dev_dbg(&lpi2c_imx->adapter.dev, "stop timeout\n");
			अवरोध;
		पूर्ण
		schedule();

	पूर्ण जबतक (1);
पूर्ण

/* CLKLO = I2C_CLK_RATIO * CLKHI, SETHOLD = CLKHI, DATAVD = CLKHI/2 */
अटल पूर्णांक lpi2c_imx_config(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	u8 prescale, filt, sethold, clkhi, clklo, datavd;
	अचिन्हित पूर्णांक clk_rate, clk_cycle;
	क्रमागत lpi2c_imx_pincfg pincfg;
	अचिन्हित पूर्णांक temp;

	lpi2c_imx_set_mode(lpi2c_imx);

	clk_rate = clk_get_rate(lpi2c_imx->clk);
	अगर (lpi2c_imx->mode == HS || lpi2c_imx->mode == ULTRA_FAST)
		filt = 0;
	अन्यथा
		filt = 2;

	क्रम (prescale = 0; prescale <= 7; prescale++) अणु
		clk_cycle = clk_rate / ((1 << prescale) * lpi2c_imx->bitrate)
			    - 3 - (filt >> 1);
		clkhi = (clk_cycle + I2C_CLK_RATIO) / (I2C_CLK_RATIO + 1);
		clklo = clk_cycle - clkhi;
		अगर (clklo < 64)
			अवरोध;
	पूर्ण

	अगर (prescale > 7)
		वापस -EINVAL;

	/* set MCFGR1: PINCFG, PRESCALE, IGNACK */
	अगर (lpi2c_imx->mode == ULTRA_FAST)
		pincfg = TWO_PIN_OO;
	अन्यथा
		pincfg = TWO_PIN_OD;
	temp = prescale | pincfg << 24;

	अगर (lpi2c_imx->mode == ULTRA_FAST)
		temp |= MCFGR1_IGNACK;

	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCFGR1);

	/* set MCFGR2: FILTSDA, FILTSCL */
	temp = (filt << 16) | (filt << 24);
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCFGR2);

	/* set MCCR: DATAVD, SETHOLD, CLKHI, CLKLO */
	sethold = clkhi;
	datavd = clkhi >> 1;
	temp = datavd << 24 | sethold << 16 | clkhi << 8 | clklo;

	अगर (lpi2c_imx->mode == HS)
		ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCCR1);
	अन्यथा
		ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCCR0);

	वापस 0;
पूर्ण

अटल पूर्णांक lpi2c_imx_master_enable(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(lpi2c_imx->adapter.dev.parent);
	अगर (ret < 0)
		वापस ret;

	temp = MCR_RST;
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCR);
	ग_लिखोl(0, lpi2c_imx->base + LPI2C_MCR);

	ret = lpi2c_imx_config(lpi2c_imx);
	अगर (ret)
		जाओ rpm_put;

	temp = पढ़ोl(lpi2c_imx->base + LPI2C_MCR);
	temp |= MCR_MEN;
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCR);

	वापस 0;

rpm_put:
	pm_runसमय_mark_last_busy(lpi2c_imx->adapter.dev.parent);
	pm_runसमय_put_स्वतःsuspend(lpi2c_imx->adapter.dev.parent);

	वापस ret;
पूर्ण

अटल पूर्णांक lpi2c_imx_master_disable(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	u32 temp;

	temp = पढ़ोl(lpi2c_imx->base + LPI2C_MCR);
	temp &= ~MCR_MEN;
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MCR);

	pm_runसमय_mark_last_busy(lpi2c_imx->adapter.dev.parent);
	pm_runसमय_put_स्वतःsuspend(lpi2c_imx->adapter.dev.parent);

	वापस 0;
पूर्ण

अटल पूर्णांक lpi2c_imx_msg_complete(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = रुको_क्रम_completion_समयout(&lpi2c_imx->complete, HZ);

	वापस समयout ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक lpi2c_imx_txfअगरo_empty(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित दीर्घ orig_jअगरfies = jअगरfies;
	u32 txcnt;

	करो अणु
		txcnt = पढ़ोl(lpi2c_imx->base + LPI2C_MFSR) & 0xff;

		अगर (पढ़ोl(lpi2c_imx->base + LPI2C_MSR) & MSR_NDF) अणु
			dev_dbg(&lpi2c_imx->adapter.dev, "NDF detected\n");
			वापस -EIO;
		पूर्ण

		अगर (समय_after(jअगरfies, orig_jअगरfies + msecs_to_jअगरfies(500))) अणु
			dev_dbg(&lpi2c_imx->adapter.dev, "txfifo empty timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
		schedule();

	पूर्ण जबतक (txcnt);

	वापस 0;
पूर्ण

अटल व्योम lpi2c_imx_set_tx_watermark(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	ग_लिखोl(lpi2c_imx->txfअगरosize >> 1, lpi2c_imx->base + LPI2C_MFCR);
पूर्ण

अटल व्योम lpi2c_imx_set_rx_watermark(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित पूर्णांक temp, reमुख्यing;

	reमुख्यing = lpi2c_imx->msglen - lpi2c_imx->delivered;

	अगर (reमुख्यing > (lpi2c_imx->rxfअगरosize >> 1))
		temp = lpi2c_imx->rxfअगरosize >> 1;
	अन्यथा
		temp = 0;

	ग_लिखोl(temp << 16, lpi2c_imx->base + LPI2C_MFCR);
पूर्ण

अटल व्योम lpi2c_imx_ग_लिखो_txfअगरo(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित पूर्णांक data, txcnt;

	txcnt = पढ़ोl(lpi2c_imx->base + LPI2C_MFSR) & 0xff;

	जबतक (txcnt < lpi2c_imx->txfअगरosize) अणु
		अगर (lpi2c_imx->delivered == lpi2c_imx->msglen)
			अवरोध;

		data = lpi2c_imx->tx_buf[lpi2c_imx->delivered++];
		ग_लिखोl(data, lpi2c_imx->base + LPI2C_MTDR);
		txcnt++;
	पूर्ण

	अगर (lpi2c_imx->delivered < lpi2c_imx->msglen)
		lpi2c_imx_पूर्णांकctrl(lpi2c_imx, MIER_TDIE | MIER_NDIE);
	अन्यथा
		complete(&lpi2c_imx->complete);
पूर्ण

अटल व्योम lpi2c_imx_पढ़ो_rxfअगरo(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx)
अणु
	अचिन्हित पूर्णांक blocklen, reमुख्यing;
	अचिन्हित पूर्णांक temp, data;

	करो अणु
		data = पढ़ोl(lpi2c_imx->base + LPI2C_MRDR);
		अगर (data & MRDR_RXEMPTY)
			अवरोध;

		lpi2c_imx->rx_buf[lpi2c_imx->delivered++] = data & 0xff;
	पूर्ण जबतक (1);

	/*
	 * First byte is the length of reमुख्यing packet in the SMBus block
	 * data पढ़ो. Add it to msgs->len.
	 */
	अगर (lpi2c_imx->block_data) अणु
		blocklen = lpi2c_imx->rx_buf[0];
		lpi2c_imx->msglen += blocklen;
	पूर्ण

	reमुख्यing = lpi2c_imx->msglen - lpi2c_imx->delivered;

	अगर (!reमुख्यing) अणु
		complete(&lpi2c_imx->complete);
		वापस;
	पूर्ण

	/* not finished, still रुकोing क्रम rx data */
	lpi2c_imx_set_rx_watermark(lpi2c_imx);

	/* multiple receive commands */
	अगर (lpi2c_imx->block_data) अणु
		lpi2c_imx->block_data = 0;
		temp = reमुख्यing;
		temp |= (RECV_DATA << 8);
		ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MTDR);
	पूर्ण अन्यथा अगर (!(lpi2c_imx->delivered & 0xff)) अणु
		temp = (reमुख्यing > CHUNK_DATA ? CHUNK_DATA : reमुख्यing) - 1;
		temp |= (RECV_DATA << 8);
		ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MTDR);
	पूर्ण

	lpi2c_imx_पूर्णांकctrl(lpi2c_imx, MIER_RDIE);
पूर्ण

अटल व्योम lpi2c_imx_ग_लिखो(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx,
			    काष्ठा i2c_msg *msgs)
अणु
	lpi2c_imx->tx_buf = msgs->buf;
	lpi2c_imx_set_tx_watermark(lpi2c_imx);
	lpi2c_imx_ग_लिखो_txfअगरo(lpi2c_imx);
पूर्ण

अटल व्योम lpi2c_imx_पढ़ो(काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx,
			   काष्ठा i2c_msg *msgs)
अणु
	अचिन्हित पूर्णांक temp;

	lpi2c_imx->rx_buf = msgs->buf;
	lpi2c_imx->block_data = msgs->flags & I2C_M_RECV_LEN;

	lpi2c_imx_set_rx_watermark(lpi2c_imx);
	temp = msgs->len > CHUNK_DATA ? CHUNK_DATA - 1 : msgs->len - 1;
	temp |= (RECV_DATA << 8);
	ग_लिखोl(temp, lpi2c_imx->base + LPI2C_MTDR);

	lpi2c_imx_पूर्णांकctrl(lpi2c_imx, MIER_RDIE | MIER_NDIE);
पूर्ण

अटल पूर्णांक lpi2c_imx_xfer(काष्ठा i2c_adapter *adapter,
			  काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx = i2c_get_adapdata(adapter);
	अचिन्हित पूर्णांक temp;
	पूर्णांक i, result;

	result = lpi2c_imx_master_enable(lpi2c_imx);
	अगर (result)
		वापस result;

	क्रम (i = 0; i < num; i++) अणु
		result = lpi2c_imx_start(lpi2c_imx, &msgs[i]);
		अगर (result)
			जाओ disable;

		/* quick smbus */
		अगर (num == 1 && msgs[0].len == 0)
			जाओ stop;

		lpi2c_imx->delivered = 0;
		lpi2c_imx->msglen = msgs[i].len;
		init_completion(&lpi2c_imx->complete);

		अगर (msgs[i].flags & I2C_M_RD)
			lpi2c_imx_पढ़ो(lpi2c_imx, &msgs[i]);
		अन्यथा
			lpi2c_imx_ग_लिखो(lpi2c_imx, &msgs[i]);

		result = lpi2c_imx_msg_complete(lpi2c_imx);
		अगर (result)
			जाओ stop;

		अगर (!(msgs[i].flags & I2C_M_RD)) अणु
			result = lpi2c_imx_txfअगरo_empty(lpi2c_imx);
			अगर (result)
				जाओ stop;
		पूर्ण
	पूर्ण

stop:
	lpi2c_imx_stop(lpi2c_imx);

	temp = पढ़ोl(lpi2c_imx->base + LPI2C_MSR);
	अगर ((temp & MSR_NDF) && !result)
		result = -EIO;

disable:
	lpi2c_imx_master_disable(lpi2c_imx);

	dev_dbg(&lpi2c_imx->adapter.dev, "<%s> exit with: %s: %d\n", __func__,
		(result < 0) ? "error" : "success msg",
		(result < 0) ? result : num);

	वापस (result < 0) ? result : num;
पूर्ण

अटल irqवापस_t lpi2c_imx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx = dev_id;
	अचिन्हित पूर्णांक temp;

	lpi2c_imx_पूर्णांकctrl(lpi2c_imx, 0);
	temp = पढ़ोl(lpi2c_imx->base + LPI2C_MSR);

	अगर (temp & MSR_RDF)
		lpi2c_imx_पढ़ो_rxfअगरo(lpi2c_imx);

	अगर (temp & MSR_TDF)
		lpi2c_imx_ग_लिखो_txfअगरo(lpi2c_imx);

	अगर (temp & MSR_NDF)
		complete(&lpi2c_imx->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 lpi2c_imx_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		I2C_FUNC_SMBUS_READ_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm lpi2c_imx_algo = अणु
	.master_xfer	= lpi2c_imx_xfer,
	.functionality	= lpi2c_imx_func,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lpi2c_imx_of_match[] = अणु
	अणु .compatible = "fsl,imx7ulp-lpi2c" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpi2c_imx_of_match);

अटल पूर्णांक lpi2c_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx;
	अचिन्हित पूर्णांक temp;
	पूर्णांक irq, ret;

	lpi2c_imx = devm_kzalloc(&pdev->dev, माप(*lpi2c_imx), GFP_KERNEL);
	अगर (!lpi2c_imx)
		वापस -ENOMEM;

	lpi2c_imx->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(lpi2c_imx->base))
		वापस PTR_ERR(lpi2c_imx->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	lpi2c_imx->adapter.owner	= THIS_MODULE;
	lpi2c_imx->adapter.algo		= &lpi2c_imx_algo;
	lpi2c_imx->adapter.dev.parent	= &pdev->dev;
	lpi2c_imx->adapter.dev.of_node	= pdev->dev.of_node;
	strlcpy(lpi2c_imx->adapter.name, pdev->name,
		माप(lpi2c_imx->adapter.name));

	lpi2c_imx->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(lpi2c_imx->clk)) अणु
		dev_err(&pdev->dev, "can't get I2C peripheral clock\n");
		वापस PTR_ERR(lpi2c_imx->clk);
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "clock-frequency", &lpi2c_imx->bitrate);
	अगर (ret)
		lpi2c_imx->bitrate = I2C_MAX_STANDARD_MODE_FREQ;

	ret = devm_request_irq(&pdev->dev, irq, lpi2c_imx_isr, 0,
			       pdev->name, lpi2c_imx);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't claim irq %d\n", irq);
		वापस ret;
	पूर्ण

	i2c_set_adapdata(&lpi2c_imx->adapter, lpi2c_imx);
	platक्रमm_set_drvdata(pdev, lpi2c_imx);

	ret = clk_prepare_enable(lpi2c_imx->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clk enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	temp = पढ़ोl(lpi2c_imx->base + LPI2C_PARAM);
	lpi2c_imx->txfअगरosize = 1 << (temp & 0x0f);
	lpi2c_imx->rxfअगरosize = 1 << ((temp >> 8) & 0x0f);

	ret = i2c_add_adapter(&lpi2c_imx->adapter);
	अगर (ret)
		जाओ rpm_disable;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	dev_info(&lpi2c_imx->adapter.dev, "LPI2C adapter registered\n");

	वापस 0;

rpm_disable:
	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक lpi2c_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&lpi2c_imx->adapter);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused lpi2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx = dev_get_drvdata(dev);

	clk_disable_unprepare(lpi2c_imx->clk);
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused lpi2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा lpi2c_imx_काष्ठा *lpi2c_imx = dev_get_drvdata(dev);
	पूर्णांक ret;

	pinctrl_pm_select_शेष_state(dev);
	ret = clk_prepare_enable(lpi2c_imx->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable I2C clock, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lpi2c_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(lpi2c_runसमय_suspend,
			   lpi2c_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver lpi2c_imx_driver = अणु
	.probe = lpi2c_imx_probe,
	.हटाओ = lpi2c_imx_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = lpi2c_imx_of_match,
		.pm = &lpi2c_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpi2c_imx_driver);

MODULE_AUTHOR("Gao Pan <pandy.gao@nxp.com>");
MODULE_DESCRIPTION("I2C adapter driver for LPI2C bus");
MODULE_LICENSE("GPL");
