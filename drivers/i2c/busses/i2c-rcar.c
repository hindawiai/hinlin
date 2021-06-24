<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Renesas R-Car I2C unit
 *
 * Copyright (C) 2014-19 Wolfram Sang <wsa@sang-engineering.com>
 * Copyright (C) 2011-2019 Renesas Electronics Corporation
 *
 * Copyright (C) 2012-14 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This file is based on the drivers/i2c/busses/i2c-sh7760.c
 * (c) 2005-2008 MSC Vertriebsges.m.b.H, Manuel Lauss <mlau@msc-ge.com>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

/* रेजिस्टर offsets */
#घोषणा ICSCR	0x00	/* slave ctrl */
#घोषणा ICMCR	0x04	/* master ctrl */
#घोषणा ICSSR	0x08	/* slave status */
#घोषणा ICMSR	0x0C	/* master status */
#घोषणा ICSIER	0x10	/* slave irq enable */
#घोषणा ICMIER	0x14	/* master irq enable */
#घोषणा ICCCR	0x18	/* घड़ी भागiders */
#घोषणा ICSAR	0x1C	/* slave address */
#घोषणा ICMAR	0x20	/* master address */
#घोषणा ICRXTX	0x24	/* data port */
#घोषणा ICFBSCR	0x38	/* first bit setup cycle (Gen3) */
#घोषणा ICDMAER	0x3c	/* DMA enable (Gen3) */

/* ICSCR */
#घोषणा SDBS	(1 << 3)	/* slave data buffer select */
#घोषणा SIE	(1 << 2)	/* slave पूर्णांकerface enable */
#घोषणा GCAE	(1 << 1)	/* general call address enable */
#घोषणा FNA	(1 << 0)	/* क्रमced non acknowledgment */

/* ICMCR */
#घोषणा MDBS	(1 << 7)	/* non-fअगरo mode चयन */
#घोषणा FSCL	(1 << 6)	/* override SCL pin */
#घोषणा FSDA	(1 << 5)	/* override SDA pin */
#घोषणा OBPC	(1 << 4)	/* override pins */
#घोषणा MIE	(1 << 3)	/* master अगर enable */
#घोषणा TSBE	(1 << 2)
#घोषणा FSB	(1 << 1)	/* क्रमce stop bit */
#घोषणा ESG	(1 << 0)	/* enable start bit gen */

/* ICSSR (also क्रम ICSIER) */
#घोषणा GCAR	(1 << 6)	/* general call received */
#घोषणा STM	(1 << 5)	/* slave transmit mode */
#घोषणा SSR	(1 << 4)	/* stop received */
#घोषणा SDE	(1 << 3)	/* slave data empty */
#घोषणा SDT	(1 << 2)	/* slave data transmitted */
#घोषणा SDR	(1 << 1)	/* slave data received */
#घोषणा SAR	(1 << 0)	/* slave addr received */

/* ICMSR (also क्रम ICMIE) */
#घोषणा MNR	(1 << 6)	/* nack received */
#घोषणा MAL	(1 << 5)	/* arbitration lost */
#घोषणा MST	(1 << 4)	/* sent a stop */
#घोषणा MDE	(1 << 3)
#घोषणा MDT	(1 << 2)
#घोषणा MDR	(1 << 1)
#घोषणा MAT	(1 << 0)	/* slave addr xfer करोne */

/* ICDMAER */
#घोषणा RSDMAE	(1 << 3)	/* DMA Slave Received Enable */
#घोषणा TSDMAE	(1 << 2)	/* DMA Slave Transmitted Enable */
#घोषणा RMDMAE	(1 << 1)	/* DMA Master Received Enable */
#घोषणा TMDMAE	(1 << 0)	/* DMA Master Transmitted Enable */

/* ICFBSCR */
#घोषणा TCYC17	0x0f		/* 17*Tcyc delay 1st bit between SDA and SCL */

#घोषणा RCAR_MIN_DMA_LEN	8

#घोषणा RCAR_BUS_PHASE_START	(MDBS | MIE | ESG)
#घोषणा RCAR_BUS_PHASE_DATA	(MDBS | MIE)
#घोषणा RCAR_BUS_PHASE_STOP	(MDBS | MIE | FSB)

#घोषणा RCAR_IRQ_SEND	(MNR | MAL | MST | MAT | MDE)
#घोषणा RCAR_IRQ_RECV	(MNR | MAL | MST | MAT | MDR)
#घोषणा RCAR_IRQ_STOP	(MST)

#घोषणा RCAR_IRQ_ACK_SEND	(~(MAT | MDE) & 0x7F)
#घोषणा RCAR_IRQ_ACK_RECV	(~(MAT | MDR) & 0x7F)

#घोषणा ID_LAST_MSG	(1 << 0)
#घोषणा ID_FIRST_MSG	(1 << 1)
#घोषणा ID_DONE		(1 << 2)
#घोषणा ID_ARBLOST	(1 << 3)
#घोषणा ID_NACK		(1 << 4)
/* persistent flags */
#घोषणा ID_P_HOST_NOTIFY	BIT(28)
#घोषणा ID_P_REP_AFTER_RD	BIT(29)
#घोषणा ID_P_NO_RXDMA		BIT(30) /* HW क्रमbids RXDMA someबार */
#घोषणा ID_P_PM_BLOCKED		BIT(31)
#घोषणा ID_P_MASK		GENMASK(31, 28)

क्रमागत rcar_i2c_type अणु
	I2C_RCAR_GEN1,
	I2C_RCAR_GEN2,
	I2C_RCAR_GEN3,
पूर्ण;

काष्ठा rcar_i2c_priv अणु
	u32 flags;
	व्योम __iomem *io;
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_msg *msg;
	पूर्णांक msgs_left;
	काष्ठा clk *clk;

	रुको_queue_head_t रुको;

	पूर्णांक pos;
	u32 icccr;
	u8 recovery_icmcr;	/* रक्षित by adapter lock */
	क्रमागत rcar_i2c_type devtype;
	काष्ठा i2c_client *slave;

	काष्ठा resource *res;
	काष्ठा dma_chan *dma_tx;
	काष्ठा dma_chan *dma_rx;
	काष्ठा scatterlist sg;
	क्रमागत dma_data_direction dma_direction;

	काष्ठा reset_control *rstc;
	bool atomic_xfer;
	पूर्णांक irq;

	काष्ठा i2c_client *host_notअगरy_client;
पूर्ण;

#घोषणा rcar_i2c_priv_to_dev(p)		((p)->adap.dev.parent)
#घोषणा rcar_i2c_is_recv(p)		((p)->msg->flags & I2C_M_RD)

अटल व्योम rcar_i2c_ग_लिखो(काष्ठा rcar_i2c_priv *priv, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, priv->io + reg);
पूर्ण

अटल u32 rcar_i2c_पढ़ो(काष्ठा rcar_i2c_priv *priv, पूर्णांक reg)
अणु
	वापस पढ़ोl(priv->io + reg);
पूर्ण

अटल पूर्णांक rcar_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);

	वापस !!(rcar_i2c_पढ़ो(priv, ICMCR) & FSCL);

पूर्ण;

अटल व्योम rcar_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);

	अगर (val)
		priv->recovery_icmcr |= FSCL;
	अन्यथा
		priv->recovery_icmcr &= ~FSCL;

	rcar_i2c_ग_लिखो(priv, ICMCR, priv->recovery_icmcr);
पूर्ण;

अटल व्योम rcar_i2c_set_sda(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);

	अगर (val)
		priv->recovery_icmcr |= FSDA;
	अन्यथा
		priv->recovery_icmcr &= ~FSDA;

	rcar_i2c_ग_लिखो(priv, ICMCR, priv->recovery_icmcr);
पूर्ण;

अटल पूर्णांक rcar_i2c_get_bus_मुक्त(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);

	वापस !(rcar_i2c_पढ़ो(priv, ICMCR) & FSDA);

पूर्ण;

अटल काष्ठा i2c_bus_recovery_info rcar_i2c_bri = अणु
	.get_scl = rcar_i2c_get_scl,
	.set_scl = rcar_i2c_set_scl,
	.set_sda = rcar_i2c_set_sda,
	.get_bus_मुक्त = rcar_i2c_get_bus_मुक्त,
	.recover_bus = i2c_generic_scl_recovery,
पूर्ण;
अटल व्योम rcar_i2c_init(काष्ठा rcar_i2c_priv *priv)
अणु
	/* reset master mode */
	rcar_i2c_ग_लिखो(priv, ICMIER, 0);
	rcar_i2c_ग_लिखो(priv, ICMCR, MDBS);
	rcar_i2c_ग_लिखो(priv, ICMSR, 0);
	/* start घड़ी */
	rcar_i2c_ग_लिखो(priv, ICCCR, priv->icccr);

	अगर (priv->devtype == I2C_RCAR_GEN3)
		rcar_i2c_ग_लिखो(priv, ICFBSCR, TCYC17);

पूर्ण

अटल पूर्णांक rcar_i2c_bus_barrier(काष्ठा rcar_i2c_priv *priv)
अणु
	पूर्णांक ret;
	u32 val;

	ret = पढ़ोl_poll_समयout(priv->io + ICMCR, val, !(val & FSDA), 10,
				 priv->adap.समयout);
	अगर (ret) अणु
		/* Waiting did not help, try to recover */
		priv->recovery_icmcr = MDBS | OBPC | FSDA | FSCL;
		ret = i2c_recover_bus(&priv->adap);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_i2c_घड़ी_calculate(काष्ठा rcar_i2c_priv *priv)
अणु
	u32 scgd, cdf, round, ick, sum, scl, cdf_width;
	अचिन्हित दीर्घ rate;
	काष्ठा device *dev = rcar_i2c_priv_to_dev(priv);
	काष्ठा i2c_timings t = अणु
		.bus_freq_hz		= I2C_MAX_STANDARD_MODE_FREQ,
		.scl_fall_ns		= 35,
		.scl_rise_ns		= 200,
		.scl_पूर्णांक_delay_ns	= 50,
	पूर्ण;

	/* Fall back to previously used values अगर not supplied */
	i2c_parse_fw_timings(dev, &t, false);

	चयन (priv->devtype) अणु
	हाल I2C_RCAR_GEN1:
		cdf_width = 2;
		अवरोध;
	हाल I2C_RCAR_GEN2:
	हाल I2C_RCAR_GEN3:
		cdf_width = 3;
		अवरोध;
	शेष:
		dev_err(dev, "device type error\n");
		वापस -EIO;
	पूर्ण

	/*
	 * calculate SCL घड़ी
	 * see
	 *	ICCCR
	 *
	 * ick	= clkp / (1 + CDF)
	 * SCL	= ick / (20 + SCGD * 8 + F[(ticf + tr + पूर्णांकd) * ick])
	 *
	 * ick  : I2C पूर्णांकernal घड़ी < 20 MHz
	 * ticf : I2C SCL falling समय
	 * tr   : I2C SCL rising  समय
	 * पूर्णांकd : LSI पूर्णांकernal delay
	 * clkp : peripheral_clk
	 * F[]  : पूर्णांकeger up-valuation
	 */
	rate = clk_get_rate(priv->clk);
	cdf = rate / 20000000;
	अगर (cdf >= 1U << cdf_width) अणु
		dev_err(dev, "Input clock %lu too high\n", rate);
		वापस -EIO;
	पूर्ण
	ick = rate / (cdf + 1);

	/*
	 * it is impossible to calculate large scale
	 * number on u32. separate it
	 *
	 * F[(ticf + tr + पूर्णांकd) * ick] with sum = (ticf + tr + पूर्णांकd)
	 *  = F[sum * ick / 1000000000]
	 *  = F[(ick / 1000000) * sum / 1000]
	 */
	sum = t.scl_fall_ns + t.scl_rise_ns + t.scl_पूर्णांक_delay_ns;
	round = (ick + 500000) / 1000000 * sum;
	round = (round + 500) / 1000;

	/*
	 * SCL	= ick / (20 + SCGD * 8 + F[(ticf + tr + पूर्णांकd) * ick])
	 *
	 * Calculation result (= SCL) should be less than
	 * bus_speed क्रम hardware safety
	 *
	 * We could use something aदीर्घ the lines of
	 *	भाग = ick / (bus_speed + 1) + 1;
	 *	scgd = (भाग - 20 - round + 7) / 8;
	 *	scl = ick / (20 + (scgd * 8) + round);
	 * (not fully verअगरied) but that would get pretty involved
	 */
	क्रम (scgd = 0; scgd < 0x40; scgd++) अणु
		scl = ick / (20 + (scgd * 8) + round);
		अगर (scl <= t.bus_freq_hz)
			जाओ scgd_find;
	पूर्ण
	dev_err(dev, "it is impossible to calculate best SCL\n");
	वापस -EIO;

scgd_find:
	dev_dbg(dev, "clk %d/%d(%lu), round %u, CDF:0x%x, SCGD: 0x%x\n",
		scl, t.bus_freq_hz, rate, round, cdf, scgd);

	/* keep icccr value */
	priv->icccr = scgd << cdf_width | cdf;

	वापस 0;
पूर्ण

अटल व्योम rcar_i2c_prepare_msg(काष्ठा rcar_i2c_priv *priv)
अणु
	पूर्णांक पढ़ो = !!rcar_i2c_is_recv(priv);

	priv->pos = 0;
	अगर (priv->msgs_left == 1)
		priv->flags |= ID_LAST_MSG;

	rcar_i2c_ग_लिखो(priv, ICMAR, i2c_8bit_addr_from_msg(priv->msg));
	/*
	 * We करोn't have a test हाल but the HW engineers say that the ग_लिखो order
	 * of ICMSR and ICMCR depends on whether we issue START or REP_START. Since
	 * it didn't cause a drawback for me, let's rather be safe than sorry.
	 */
	अगर (priv->flags & ID_FIRST_MSG) अणु
		rcar_i2c_ग_लिखो(priv, ICMSR, 0);
		rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_START);
	पूर्ण अन्यथा अणु
		अगर (priv->flags & ID_P_REP_AFTER_RD)
			priv->flags &= ~ID_P_REP_AFTER_RD;
		अन्यथा
			rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_START);
		rcar_i2c_ग_लिखो(priv, ICMSR, 0);
	पूर्ण

	अगर (!priv->atomic_xfer)
		rcar_i2c_ग_लिखो(priv, ICMIER, पढ़ो ? RCAR_IRQ_RECV : RCAR_IRQ_SEND);
पूर्ण

अटल व्योम rcar_i2c_next_msg(काष्ठा rcar_i2c_priv *priv)
अणु
	priv->msg++;
	priv->msgs_left--;
	priv->flags &= ID_P_MASK;
	rcar_i2c_prepare_msg(priv);
पूर्ण

अटल व्योम rcar_i2c_dma_unmap(काष्ठा rcar_i2c_priv *priv)
अणु
	काष्ठा dma_chan *chan = priv->dma_direction == DMA_FROM_DEVICE
		? priv->dma_rx : priv->dma_tx;

	dma_unmap_single(chan->device->dev, sg_dma_address(&priv->sg),
			 sg_dma_len(&priv->sg), priv->dma_direction);

	/* Gen3 can only करो one RXDMA per transfer and we just completed it */
	अगर (priv->devtype == I2C_RCAR_GEN3 &&
	    priv->dma_direction == DMA_FROM_DEVICE)
		priv->flags |= ID_P_NO_RXDMA;

	priv->dma_direction = DMA_NONE;

	/* Disable DMA Master Received/Transmitted, must be last! */
	rcar_i2c_ग_लिखो(priv, ICDMAER, 0);
पूर्ण

अटल व्योम rcar_i2c_cleanup_dma(काष्ठा rcar_i2c_priv *priv)
अणु
	अगर (priv->dma_direction == DMA_NONE)
		वापस;
	अन्यथा अगर (priv->dma_direction == DMA_FROM_DEVICE)
		dmaengine_terminate_all(priv->dma_rx);
	अन्यथा अगर (priv->dma_direction == DMA_TO_DEVICE)
		dmaengine_terminate_all(priv->dma_tx);

	rcar_i2c_dma_unmap(priv);
पूर्ण

अटल व्योम rcar_i2c_dma_callback(व्योम *data)
अणु
	काष्ठा rcar_i2c_priv *priv = data;

	priv->pos += sg_dma_len(&priv->sg);

	rcar_i2c_dma_unmap(priv);
पूर्ण

अटल bool rcar_i2c_dma(काष्ठा rcar_i2c_priv *priv)
अणु
	काष्ठा device *dev = rcar_i2c_priv_to_dev(priv);
	काष्ठा i2c_msg *msg = priv->msg;
	bool पढ़ो = msg->flags & I2C_M_RD;
	क्रमागत dma_data_direction dir = पढ़ो ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	काष्ठा dma_chan *chan = पढ़ो ? priv->dma_rx : priv->dma_tx;
	काष्ठा dma_async_tx_descriptor *txdesc;
	dma_addr_t dma_addr;
	dma_cookie_t cookie;
	अचिन्हित अक्षर *buf;
	पूर्णांक len;

	/* Do various checks to see अगर DMA is feasible at all */
	अगर (priv->atomic_xfer || IS_ERR(chan) || msg->len < RCAR_MIN_DMA_LEN ||
	    !(msg->flags & I2C_M_DMA_SAFE) || (पढ़ो && priv->flags & ID_P_NO_RXDMA))
		वापस false;

	अगर (पढ़ो) अणु
		/*
		 * The last two bytes needs to be fetched using PIO in
		 * order क्रम the STOP phase to work.
		 */
		buf = priv->msg->buf;
		len = priv->msg->len - 2;
	पूर्ण अन्यथा अणु
		/*
		 * First byte in message was sent using PIO.
		 */
		buf = priv->msg->buf + 1;
		len = priv->msg->len - 1;
	पूर्ण

	dma_addr = dma_map_single(chan->device->dev, buf, len, dir);
	अगर (dma_mapping_error(chan->device->dev, dma_addr)) अणु
		dev_dbg(dev, "dma map failed, using PIO\n");
		वापस false;
	पूर्ण

	sg_dma_len(&priv->sg) = len;
	sg_dma_address(&priv->sg) = dma_addr;

	priv->dma_direction = dir;

	txdesc = dmaengine_prep_slave_sg(chan, &priv->sg, 1,
					 पढ़ो ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!txdesc) अणु
		dev_dbg(dev, "dma prep slave sg failed, using PIO\n");
		rcar_i2c_cleanup_dma(priv);
		वापस false;
	पूर्ण

	txdesc->callback = rcar_i2c_dma_callback;
	txdesc->callback_param = priv;

	cookie = dmaengine_submit(txdesc);
	अगर (dma_submit_error(cookie)) अणु
		dev_dbg(dev, "submitting dma failed, using PIO\n");
		rcar_i2c_cleanup_dma(priv);
		वापस false;
	पूर्ण

	/* Enable DMA Master Received/Transmitted */
	अगर (पढ़ो)
		rcar_i2c_ग_लिखो(priv, ICDMAER, RMDMAE);
	अन्यथा
		rcar_i2c_ग_लिखो(priv, ICDMAER, TMDMAE);

	dma_async_issue_pending(chan);
	वापस true;
पूर्ण

अटल व्योम rcar_i2c_irq_send(काष्ठा rcar_i2c_priv *priv, u32 msr)
अणु
	काष्ठा i2c_msg *msg = priv->msg;

	/* FIXME: someबार, unknown पूर्णांकerrupt happened. Do nothing */
	अगर (!(msr & MDE))
		वापस;

	/* Check अगर DMA can be enabled and take over */
	अगर (priv->pos == 1 && rcar_i2c_dma(priv))
		वापस;

	अगर (priv->pos < msg->len) अणु
		/*
		 * Prepare next data to ICRXTX रेजिस्टर.
		 * This data will go to _SHIFT_ रेजिस्टर.
		 *
		 *    *
		 * [ICRXTX] -> [SHIFT] -> [I2C bus]
		 */
		rcar_i2c_ग_लिखो(priv, ICRXTX, msg->buf[priv->pos]);
		priv->pos++;
	पूर्ण अन्यथा अणु
		/*
		 * The last data was pushed to ICRXTX on _PREV_ empty irq.
		 * It is on _SHIFT_ रेजिस्टर, and will sent to I2C bus.
		 *
		 *		  *
		 * [ICRXTX] -> [SHIFT] -> [I2C bus]
		 */

		अगर (priv->flags & ID_LAST_MSG) अणु
			/*
			 * If current msg is the _LAST_ msg,
			 * prepare stop condition here.
			 * ID_DONE will be set on STOP irq.
			 */
			rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_STOP);
		पूर्ण अन्यथा अणु
			rcar_i2c_next_msg(priv);
			वापस;
		पूर्ण
	पूर्ण

	rcar_i2c_ग_लिखो(priv, ICMSR, RCAR_IRQ_ACK_SEND);
पूर्ण

अटल व्योम rcar_i2c_irq_recv(काष्ठा rcar_i2c_priv *priv, u32 msr)
अणु
	काष्ठा i2c_msg *msg = priv->msg;

	/* FIXME: someबार, unknown पूर्णांकerrupt happened. Do nothing */
	अगर (!(msr & MDR))
		वापस;

	अगर (msr & MAT) अणु
		/*
		 * Address transfer phase finished, but no data at this poपूर्णांक.
		 * Try to use DMA to receive data.
		 */
		rcar_i2c_dma(priv);
	पूर्ण अन्यथा अगर (priv->pos < msg->len) अणु
		/* get received data */
		msg->buf[priv->pos] = rcar_i2c_पढ़ो(priv, ICRXTX);
		priv->pos++;
	पूर्ण

	/* If next received data is the _LAST_, go to new phase. */
	अगर (priv->pos + 1 == msg->len) अणु
		अगर (priv->flags & ID_LAST_MSG) अणु
			rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_STOP);
		पूर्ण अन्यथा अणु
			rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_START);
			priv->flags |= ID_P_REP_AFTER_RD;
		पूर्ण
	पूर्ण

	अगर (priv->pos == msg->len && !(priv->flags & ID_LAST_MSG))
		rcar_i2c_next_msg(priv);
	अन्यथा
		rcar_i2c_ग_लिखो(priv, ICMSR, RCAR_IRQ_ACK_RECV);
पूर्ण

अटल bool rcar_i2c_slave_irq(काष्ठा rcar_i2c_priv *priv)
अणु
	u32 ssr_raw, ssr_filtered;
	u8 value;

	ssr_raw = rcar_i2c_पढ़ो(priv, ICSSR) & 0xff;
	ssr_filtered = ssr_raw & rcar_i2c_पढ़ो(priv, ICSIER);

	अगर (!ssr_filtered)
		वापस false;

	/* address detected */
	अगर (ssr_filtered & SAR) अणु
		/* पढ़ो or ग_लिखो request */
		अगर (ssr_raw & STM) अणु
			i2c_slave_event(priv->slave, I2C_SLAVE_READ_REQUESTED, &value);
			rcar_i2c_ग_लिखो(priv, ICRXTX, value);
			rcar_i2c_ग_लिखो(priv, ICSIER, SDE | SSR | SAR);
		पूर्ण अन्यथा अणु
			i2c_slave_event(priv->slave, I2C_SLAVE_WRITE_REQUESTED, &value);
			rcar_i2c_पढ़ो(priv, ICRXTX);	/* dummy पढ़ो */
			rcar_i2c_ग_लिखो(priv, ICSIER, SDR | SSR | SAR);
		पूर्ण

		/* Clear SSR, too, because of old STOPs to other clients than us */
		rcar_i2c_ग_लिखो(priv, ICSSR, ~(SAR | SSR) & 0xff);
	पूर्ण

	/* master sent stop */
	अगर (ssr_filtered & SSR) अणु
		i2c_slave_event(priv->slave, I2C_SLAVE_STOP, &value);
		rcar_i2c_ग_लिखो(priv, ICSCR, SIE | SDBS); /* clear our NACK */
		rcar_i2c_ग_लिखो(priv, ICSIER, SAR);
		rcar_i2c_ग_लिखो(priv, ICSSR, ~SSR & 0xff);
	पूर्ण

	/* master wants to ग_लिखो to us */
	अगर (ssr_filtered & SDR) अणु
		पूर्णांक ret;

		value = rcar_i2c_पढ़ो(priv, ICRXTX);
		ret = i2c_slave_event(priv->slave, I2C_SLAVE_WRITE_RECEIVED, &value);
		/* Send NACK in हाल of error */
		rcar_i2c_ग_लिखो(priv, ICSCR, SIE | SDBS | (ret < 0 ? FNA : 0));
		rcar_i2c_ग_लिखो(priv, ICSSR, ~SDR & 0xff);
	पूर्ण

	/* master wants to पढ़ो from us */
	अगर (ssr_filtered & SDE) अणु
		i2c_slave_event(priv->slave, I2C_SLAVE_READ_PROCESSED, &value);
		rcar_i2c_ग_लिखो(priv, ICRXTX, value);
		rcar_i2c_ग_लिखो(priv, ICSSR, ~SDE & 0xff);
	पूर्ण

	वापस true;
पूर्ण

/*
 * This driver has a lock-मुक्त design because there are IP cores (at least
 * R-Car Gen2) which have an inherent race condition in their hardware design.
 * There, we need to चयन to RCAR_BUS_PHASE_DATA as soon as possible after
 * the पूर्णांकerrupt was generated, otherwise an unwanted repeated message माला_लो
 * generated. It turned out that taking a spinlock at the beginning of the ISR
 * was alपढ़ोy causing repeated messages. Thus, this driver was converted to
 * the now lockless behaviour. Please keep this in mind when hacking the driver.
 * R-Car Gen3 seems to have this fixed but earlier versions than R-Car Gen2 are
 * likely affected. Thereक्रमe, we have dअगरferent पूर्णांकerrupt handler entries.
 */
अटल irqवापस_t rcar_i2c_irq(पूर्णांक irq, काष्ठा rcar_i2c_priv *priv, u32 msr)
अणु
	अगर (!msr) अणु
		अगर (rcar_i2c_slave_irq(priv))
			वापस IRQ_HANDLED;

		वापस IRQ_NONE;
	पूर्ण

	/* Arbitration lost */
	अगर (msr & MAL) अणु
		priv->flags |= ID_DONE | ID_ARBLOST;
		जाओ out;
	पूर्ण

	/* Nack */
	अगर (msr & MNR) अणु
		/* HW स्वतःmatically sends STOP after received NACK */
		अगर (!priv->atomic_xfer)
			rcar_i2c_ग_लिखो(priv, ICMIER, RCAR_IRQ_STOP);
		priv->flags |= ID_NACK;
		जाओ out;
	पूर्ण

	/* Stop */
	अगर (msr & MST) अणु
		priv->msgs_left--; /* The last message also made it */
		priv->flags |= ID_DONE;
		जाओ out;
	पूर्ण

	अगर (rcar_i2c_is_recv(priv))
		rcar_i2c_irq_recv(priv, msr);
	अन्यथा
		rcar_i2c_irq_send(priv, msr);

out:
	अगर (priv->flags & ID_DONE) अणु
		rcar_i2c_ग_लिखो(priv, ICMIER, 0);
		rcar_i2c_ग_लिखो(priv, ICMSR, 0);
		अगर (!priv->atomic_xfer)
			wake_up(&priv->रुको);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rcar_i2c_gen2_irq(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा rcar_i2c_priv *priv = ptr;
	u32 msr;

	/* Clear START or STOP immediately, except क्रम REPSTART after पढ़ो */
	अगर (likely(!(priv->flags & ID_P_REP_AFTER_RD)))
		rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_DATA);

	/* Only handle पूर्णांकerrupts that are currently enabled */
	msr = rcar_i2c_पढ़ो(priv, ICMSR);
	अगर (!priv->atomic_xfer)
		msr &= rcar_i2c_पढ़ो(priv, ICMIER);

	वापस rcar_i2c_irq(irq, priv, msr);
पूर्ण

अटल irqवापस_t rcar_i2c_gen3_irq(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा rcar_i2c_priv *priv = ptr;
	u32 msr;

	/* Only handle पूर्णांकerrupts that are currently enabled */
	msr = rcar_i2c_पढ़ो(priv, ICMSR);
	अगर (!priv->atomic_xfer)
		msr &= rcar_i2c_पढ़ो(priv, ICMIER);

	/*
	 * Clear START or STOP immediately, except क्रम REPSTART after पढ़ो or
	 * अगर a spurious पूर्णांकerrupt was detected.
	 */
	अगर (likely(!(priv->flags & ID_P_REP_AFTER_RD) && msr))
		rcar_i2c_ग_लिखो(priv, ICMCR, RCAR_BUS_PHASE_DATA);

	वापस rcar_i2c_irq(irq, priv, msr);
पूर्ण

अटल काष्ठा dma_chan *rcar_i2c_request_dma_chan(काष्ठा device *dev,
					क्रमागत dma_transfer_direction dir,
					dma_addr_t port_addr)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_slave_config cfg;
	अक्षर *chan_name = dir == DMA_MEM_TO_DEV ? "tx" : "rx";
	पूर्णांक ret;

	chan = dma_request_chan(dev, chan_name);
	अगर (IS_ERR(chan)) अणु
		dev_dbg(dev, "request_channel failed for %s (%ld)\n",
			chan_name, PTR_ERR(chan));
		वापस chan;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));
	cfg.direction = dir;
	अगर (dir == DMA_MEM_TO_DEV) अणु
		cfg.dst_addr = port_addr;
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण अन्यथा अणु
		cfg.src_addr = port_addr;
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret) अणु
		dev_dbg(dev, "slave_config failed for %s (%d)\n",
			chan_name, ret);
		dma_release_channel(chan);
		वापस ERR_PTR(ret);
	पूर्ण

	dev_dbg(dev, "got DMA channel for %s\n", chan_name);
	वापस chan;
पूर्ण

अटल व्योम rcar_i2c_request_dma(काष्ठा rcar_i2c_priv *priv,
				 काष्ठा i2c_msg *msg)
अणु
	काष्ठा device *dev = rcar_i2c_priv_to_dev(priv);
	bool पढ़ो;
	काष्ठा dma_chan *chan;
	क्रमागत dma_transfer_direction dir;

	पढ़ो = msg->flags & I2C_M_RD;

	chan = पढ़ो ? priv->dma_rx : priv->dma_tx;
	अगर (PTR_ERR(chan) != -EPROBE_DEFER)
		वापस;

	dir = पढ़ो ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;
	chan = rcar_i2c_request_dma_chan(dev, dir, priv->res->start + ICRXTX);

	अगर (पढ़ो)
		priv->dma_rx = chan;
	अन्यथा
		priv->dma_tx = chan;
पूर्ण

अटल व्योम rcar_i2c_release_dma(काष्ठा rcar_i2c_priv *priv)
अणु
	अगर (!IS_ERR(priv->dma_tx)) अणु
		dma_release_channel(priv->dma_tx);
		priv->dma_tx = ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	अगर (!IS_ERR(priv->dma_rx)) अणु
		dma_release_channel(priv->dma_rx);
		priv->dma_rx = ERR_PTR(-EPROBE_DEFER);
	पूर्ण
पूर्ण

/* I2C is a special हाल, we need to poll the status of a reset */
अटल पूर्णांक rcar_i2c_करो_reset(काष्ठा rcar_i2c_priv *priv)
अणु
	पूर्णांक ret;

	ret = reset_control_reset(priv->rstc);
	अगर (ret)
		वापस ret;

	वापस पढ़ो_poll_समयout_atomic(reset_control_status, ret, ret == 0, 1,
					100, false, priv->rstc);
पूर्ण

अटल पूर्णांक rcar_i2c_master_xfer(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);
	काष्ठा device *dev = rcar_i2c_priv_to_dev(priv);
	पूर्णांक i, ret;
	दीर्घ समय_left;

	priv->atomic_xfer = false;

	pm_runसमय_get_sync(dev);

	/* Check bus state beक्रमe init otherwise bus busy info will be lost */
	ret = rcar_i2c_bus_barrier(priv);
	अगर (ret < 0)
		जाओ out;

	/* Gen3 needs a reset beक्रमe allowing RXDMA once */
	अगर (priv->devtype == I2C_RCAR_GEN3) अणु
		priv->flags |= ID_P_NO_RXDMA;
		अगर (!IS_ERR(priv->rstc)) अणु
			ret = rcar_i2c_करो_reset(priv);
			अगर (ret == 0)
				priv->flags &= ~ID_P_NO_RXDMA;
		पूर्ण
	पूर्ण

	rcar_i2c_init(priv);

	क्रम (i = 0; i < num; i++)
		rcar_i2c_request_dma(priv, msgs + i);

	/* init first message */
	priv->msg = msgs;
	priv->msgs_left = num;
	priv->flags = (priv->flags & ID_P_MASK) | ID_FIRST_MSG;
	rcar_i2c_prepare_msg(priv);

	समय_left = रुको_event_समयout(priv->रुको, priv->flags & ID_DONE,
				     num * adap->समयout);

	/* cleanup DMA अगर it couldn't complete properly due to an error */
	अगर (priv->dma_direction != DMA_NONE)
		rcar_i2c_cleanup_dma(priv);

	अगर (!समय_left) अणु
		rcar_i2c_init(priv);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (priv->flags & ID_NACK) अणु
		ret = -ENXIO;
	पूर्ण अन्यथा अगर (priv->flags & ID_ARBLOST) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		ret = num - priv->msgs_left; /* The number of transfer */
	पूर्ण
out:
	pm_runसमय_put(dev);

	अगर (ret < 0 && ret != -ENXIO)
		dev_err(dev, "error %d : %x\n", ret, priv->flags);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_i2c_master_xfer_atomic(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);
	काष्ठा device *dev = rcar_i2c_priv_to_dev(priv);
	अचिन्हित दीर्घ j;
	bool समय_left;
	पूर्णांक ret;

	priv->atomic_xfer = true;

	pm_runसमय_get_sync(dev);

	/* Check bus state beक्रमe init otherwise bus busy info will be lost */
	ret = rcar_i2c_bus_barrier(priv);
	अगर (ret < 0)
		जाओ out;

	rcar_i2c_init(priv);

	/* init first message */
	priv->msg = msgs;
	priv->msgs_left = num;
	priv->flags = (priv->flags & ID_P_MASK) | ID_FIRST_MSG;
	rcar_i2c_prepare_msg(priv);

	j = jअगरfies + num * adap->समयout;
	करो अणु
		u32 msr = rcar_i2c_पढ़ो(priv, ICMSR);

		msr &= (rcar_i2c_is_recv(priv) ? RCAR_IRQ_RECV : RCAR_IRQ_SEND) | RCAR_IRQ_STOP;

		अगर (msr) अणु
			अगर (priv->devtype < I2C_RCAR_GEN3)
				rcar_i2c_gen2_irq(0, priv);
			अन्यथा
				rcar_i2c_gen3_irq(0, priv);
		पूर्ण

		समय_left = समय_beक्रमe_eq(jअगरfies, j);
	पूर्ण जबतक (!(priv->flags & ID_DONE) && समय_left);

	अगर (!समय_left) अणु
		rcar_i2c_init(priv);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (priv->flags & ID_NACK) अणु
		ret = -ENXIO;
	पूर्ण अन्यथा अगर (priv->flags & ID_ARBLOST) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		ret = num - priv->msgs_left; /* The number of transfer */
	पूर्ण
out:
	pm_runसमय_put(dev);

	अगर (ret < 0 && ret != -ENXIO)
		dev_err(dev, "error %d : %x\n", ret, priv->flags);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(slave->adapter);

	अगर (priv->slave)
		वापस -EBUSY;

	अगर (slave->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;

	/* Keep device active क्रम slave address detection logic */
	pm_runसमय_get_sync(rcar_i2c_priv_to_dev(priv));

	priv->slave = slave;
	rcar_i2c_ग_लिखो(priv, ICSAR, slave->addr);
	rcar_i2c_ग_लिखो(priv, ICSSR, 0);
	rcar_i2c_ग_लिखो(priv, ICSIER, SAR);
	rcar_i2c_ग_लिखो(priv, ICSCR, SIE | SDBS);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(slave->adapter);

	WARN_ON(!priv->slave);

	/* ensure no irq is running beक्रमe clearing ptr */
	disable_irq(priv->irq);
	rcar_i2c_ग_लिखो(priv, ICSIER, 0);
	rcar_i2c_ग_लिखो(priv, ICSSR, 0);
	enable_irq(priv->irq);
	rcar_i2c_ग_लिखो(priv, ICSCR, SDBS);
	rcar_i2c_ग_लिखो(priv, ICSAR, 0); /* Gen2: must be 0 अगर not using slave */

	priv->slave = शून्य;

	pm_runसमय_put(rcar_i2c_priv_to_dev(priv));

	वापस 0;
पूर्ण

अटल u32 rcar_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा rcar_i2c_priv *priv = i2c_get_adapdata(adap);

	/*
	 * This HW can't करो:
	 * I2C_SMBUS_QUICK (setting FSB during START didn't work)
	 * I2C_M_NOSTART (स्वतःmatically sends address after START)
	 * I2C_M_IGNORE_NAK (स्वतःmatically sends STOP after NAK)
	 */
	u32 func = I2C_FUNC_I2C | I2C_FUNC_SLAVE |
		   (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);

	अगर (priv->flags & ID_P_HOST_NOTIFY)
		func |= I2C_FUNC_SMBUS_HOST_NOTIFY;

	वापस func;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm rcar_i2c_algo = अणु
	.master_xfer	= rcar_i2c_master_xfer,
	.master_xfer_atomic = rcar_i2c_master_xfer_atomic,
	.functionality	= rcar_i2c_func,
	.reg_slave	= rcar_reg_slave,
	.unreg_slave	= rcar_unreg_slave,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks rcar_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_i2c_dt_ids[] = अणु
	अणु .compatible = "renesas,i2c-r8a7778", .data = (व्योम *)I2C_RCAR_GEN1 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7779", .data = (व्योम *)I2C_RCAR_GEN1 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7790", .data = (व्योम *)I2C_RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7791", .data = (व्योम *)I2C_RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7792", .data = (व्योम *)I2C_RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7793", .data = (व्योम *)I2C_RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7794", .data = (व्योम *)I2C_RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7795", .data = (व्योम *)I2C_RCAR_GEN3 पूर्ण,
	अणु .compatible = "renesas,i2c-r8a7796", .data = (व्योम *)I2C_RCAR_GEN3 पूर्ण,
	अणु .compatible = "renesas,i2c-rcar", .data = (व्योम *)I2C_RCAR_GEN1 पूर्ण,	/* Deprecated */
	अणु .compatible = "renesas,rcar-gen1-i2c", .data = (व्योम *)I2C_RCAR_GEN1 पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-i2c", .data = (व्योम *)I2C_RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-i2c", .data = (व्योम *)I2C_RCAR_GEN3 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_i2c_dt_ids);

अटल पूर्णांक rcar_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_i2c_priv *priv;
	काष्ठा i2c_adapter *adap;
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित दीर्घ irqflags = 0;
	irqवापस_t (*irqhandler)(पूर्णांक irq, व्योम *ptr) = rcar_i2c_gen3_irq;
	पूर्णांक ret;

	/* Otherwise logic will अवरोध because some bytes must always use PIO */
	BUILD_BUG_ON_MSG(RCAR_MIN_DMA_LEN < 3, "Invalid min DMA length");

	priv = devm_kzalloc(dev, माप(काष्ठा rcar_i2c_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "cannot get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	priv->io = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &priv->res);
	अगर (IS_ERR(priv->io))
		वापस PTR_ERR(priv->io);

	priv->devtype = (क्रमागत rcar_i2c_type)of_device_get_match_data(dev);
	init_रुकोqueue_head(&priv->रुको);

	adap = &priv->adap;
	adap->nr = pdev->id;
	adap->algo = &rcar_i2c_algo;
	adap->class = I2C_CLASS_DEPRECATED;
	adap->retries = 3;
	adap->dev.parent = dev;
	adap->dev.of_node = dev->of_node;
	adap->bus_recovery_info = &rcar_i2c_bri;
	adap->quirks = &rcar_i2c_quirks;
	i2c_set_adapdata(adap, priv);
	strlcpy(adap->name, pdev->name, माप(adap->name));

	/* Init DMA */
	sg_init_table(&priv->sg, 1);
	priv->dma_direction = DMA_NONE;
	priv->dma_rx = priv->dma_tx = ERR_PTR(-EPROBE_DEFER);

	/* Activate device क्रम घड़ी calculation */
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);
	ret = rcar_i2c_घड़ी_calculate(priv);
	अगर (ret < 0)
		जाओ out_pm_put;

	rcar_i2c_ग_लिखो(priv, ICSAR, 0); /* Gen2: must be 0 अगर not using slave */

	अगर (priv->devtype < I2C_RCAR_GEN3) अणु
		irqflags |= IRQF_NO_THREAD;
		irqhandler = rcar_i2c_gen2_irq;
	पूर्ण

	अगर (priv->devtype == I2C_RCAR_GEN3) अणु
		priv->rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
		अगर (!IS_ERR(priv->rstc)) अणु
			ret = reset_control_status(priv->rstc);
			अगर (ret < 0)
				priv->rstc = ERR_PTR(-ENOTSUPP);
		पूर्ण
	पूर्ण

	/* Stay always active when multi-master to keep arbitration working */
	अगर (of_property_पढ़ो_bool(dev->of_node, "multi-master"))
		priv->flags |= ID_P_PM_BLOCKED;
	अन्यथा
		pm_runसमय_put(dev);

	अगर (of_property_पढ़ो_bool(dev->of_node, "smbus"))
		priv->flags |= ID_P_HOST_NOTIFY;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ out_pm_disable;
	priv->irq = ret;
	ret = devm_request_irq(dev, priv->irq, irqhandler, irqflags, dev_name(dev), priv);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get irq %d\n", priv->irq);
		जाओ out_pm_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	ret = i2c_add_numbered_adapter(adap);
	अगर (ret < 0)
		जाओ out_pm_disable;

	अगर (priv->flags & ID_P_HOST_NOTIFY) अणु
		priv->host_notअगरy_client = i2c_new_slave_host_notअगरy_device(adap);
		अगर (IS_ERR(priv->host_notअगरy_client)) अणु
			ret = PTR_ERR(priv->host_notअगरy_client);
			जाओ out_del_device;
		पूर्ण
	पूर्ण

	dev_info(dev, "probed\n");

	वापस 0;

 out_del_device:
	i2c_del_adapter(&priv->adap);
 out_pm_put:
	pm_runसमय_put(dev);
 out_pm_disable:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक rcar_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_i2c_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	अगर (priv->host_notअगरy_client)
		i2c_मुक्त_slave_host_notअगरy_device(priv->host_notअगरy_client);
	i2c_del_adapter(&priv->adap);
	rcar_i2c_release_dma(priv);
	अगर (priv->flags & ID_P_PM_BLOCKED)
		pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rcar_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा rcar_i2c_priv *priv = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&priv->adap);
	वापस 0;
पूर्ण

अटल पूर्णांक rcar_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा rcar_i2c_priv *priv = dev_get_drvdata(dev);

	i2c_mark_adapter_resumed(&priv->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rcar_i2c_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(rcar_i2c_suspend, rcar_i2c_resume)
पूर्ण;

#घोषणा DEV_PM_OPS (&rcar_i2c_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver rcar_i2c_driver = अणु
	.driver	= अणु
		.name	= "i2c-rcar",
		.of_match_table = rcar_i2c_dt_ids,
		.pm	= DEV_PM_OPS,
	पूर्ण,
	.probe		= rcar_i2c_probe,
	.हटाओ		= rcar_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(rcar_i2c_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renesas R-Car I2C bus driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
