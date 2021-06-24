<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा UNIPHIER_FI2C_CR	0x00	/* control रेजिस्टर */
#घोषणा     UNIPHIER_FI2C_CR_MST	BIT(3)	/* master mode */
#घोषणा     UNIPHIER_FI2C_CR_STA	BIT(2)	/* start condition */
#घोषणा     UNIPHIER_FI2C_CR_STO	BIT(1)	/* stop condition */
#घोषणा     UNIPHIER_FI2C_CR_NACK	BIT(0)	/* करो not वापस ACK */
#घोषणा UNIPHIER_FI2C_DTTX	0x04	/* TX FIFO */
#घोषणा     UNIPHIER_FI2C_DTTX_CMD	BIT(8)	/* send command (slave addr) */
#घोषणा     UNIPHIER_FI2C_DTTX_RD	BIT(0)	/* पढ़ो transaction */
#घोषणा UNIPHIER_FI2C_DTRX	0x04	/* RX FIFO */
#घोषणा UNIPHIER_FI2C_SLAD	0x0c	/* slave address */
#घोषणा UNIPHIER_FI2C_CYC	0x10	/* घड़ी cycle control */
#घोषणा UNIPHIER_FI2C_LCTL	0x14	/* घड़ी low period control */
#घोषणा UNIPHIER_FI2C_SSUT	0x18	/* restart/stop setup समय control */
#घोषणा UNIPHIER_FI2C_DSUT	0x1c	/* data setup समय control */
#घोषणा UNIPHIER_FI2C_INT	0x20	/* पूर्णांकerrupt status */
#घोषणा UNIPHIER_FI2C_IE	0x24	/* पूर्णांकerrupt enable */
#घोषणा UNIPHIER_FI2C_IC	0x28	/* पूर्णांकerrupt clear */
#घोषणा     UNIPHIER_FI2C_INT_TE	BIT(9)	/* TX FIFO empty */
#घोषणा     UNIPHIER_FI2C_INT_RF	BIT(8)	/* RX FIFO full */
#घोषणा     UNIPHIER_FI2C_INT_TC	BIT(7)	/* send complete (STOP) */
#घोषणा     UNIPHIER_FI2C_INT_RC	BIT(6)	/* receive complete (STOP) */
#घोषणा     UNIPHIER_FI2C_INT_TB	BIT(5)	/* sent specअगरied bytes */
#घोषणा     UNIPHIER_FI2C_INT_RB	BIT(4)	/* received specअगरied bytes */
#घोषणा     UNIPHIER_FI2C_INT_NA	BIT(2)	/* no ACK */
#घोषणा     UNIPHIER_FI2C_INT_AL	BIT(1)	/* arbitration lost */
#घोषणा UNIPHIER_FI2C_SR	0x2c	/* status रेजिस्टर */
#घोषणा     UNIPHIER_FI2C_SR_DB		BIT(12)	/* device busy */
#घोषणा     UNIPHIER_FI2C_SR_STS	BIT(11)	/* stop condition detected */
#घोषणा     UNIPHIER_FI2C_SR_BB		BIT(8)	/* bus busy */
#घोषणा     UNIPHIER_FI2C_SR_RFF	BIT(3)	/* RX FIFO full */
#घोषणा     UNIPHIER_FI2C_SR_RNE	BIT(2)	/* RX FIFO not empty */
#घोषणा     UNIPHIER_FI2C_SR_TNF	BIT(1)	/* TX FIFO not full */
#घोषणा     UNIPHIER_FI2C_SR_TFE	BIT(0)	/* TX FIFO empty */
#घोषणा UNIPHIER_FI2C_RST	0x34	/* reset control */
#घोषणा     UNIPHIER_FI2C_RST_TBRST	BIT(2)	/* clear TX FIFO */
#घोषणा     UNIPHIER_FI2C_RST_RBRST	BIT(1)	/* clear RX FIFO */
#घोषणा     UNIPHIER_FI2C_RST_RST	BIT(0)	/* क्रमcible bus reset */
#घोषणा UNIPHIER_FI2C_BM	0x38	/* bus monitor */
#घोषणा     UNIPHIER_FI2C_BM_SDAO	BIT(3)	/* output क्रम SDA line */
#घोषणा     UNIPHIER_FI2C_BM_SDAS	BIT(2)	/* पढ़ोback of SDA line */
#घोषणा     UNIPHIER_FI2C_BM_SCLO	BIT(1)	/* output क्रम SCL line */
#घोषणा     UNIPHIER_FI2C_BM_SCLS	BIT(0)	/* पढ़ोback of SCL line */
#घोषणा UNIPHIER_FI2C_NOISE	0x3c	/* noise filter control */
#घोषणा UNIPHIER_FI2C_TBC	0x40	/* TX byte count setting */
#घोषणा UNIPHIER_FI2C_RBC	0x44	/* RX byte count setting */
#घोषणा UNIPHIER_FI2C_TBCM	0x48	/* TX byte count monitor */
#घोषणा UNIPHIER_FI2C_RBCM	0x4c	/* RX byte count monitor */
#घोषणा UNIPHIER_FI2C_BRST	0x50	/* bus reset */
#घोषणा     UNIPHIER_FI2C_BRST_FOEN	BIT(1)	/* normal operation */
#घोषणा     UNIPHIER_FI2C_BRST_RSCL	BIT(0)	/* release SCL */

#घोषणा UNIPHIER_FI2C_INT_FAULTS	\
				(UNIPHIER_FI2C_INT_NA | UNIPHIER_FI2C_INT_AL)
#घोषणा UNIPHIER_FI2C_INT_STOP		\
				(UNIPHIER_FI2C_INT_TC | UNIPHIER_FI2C_INT_RC)

#घोषणा UNIPHIER_FI2C_RD		BIT(0)
#घोषणा UNIPHIER_FI2C_STOP		BIT(1)
#घोषणा UNIPHIER_FI2C_MANUAL_NACK	BIT(2)
#घोषणा UNIPHIER_FI2C_BYTE_WISE		BIT(3)
#घोषणा UNIPHIER_FI2C_DEFER_STOP_COMP	BIT(4)

#घोषणा UNIPHIER_FI2C_FIFO_SIZE		8

काष्ठा uniphier_fi2c_priv अणु
	काष्ठा completion comp;
	काष्ठा i2c_adapter adap;
	व्योम __iomem *membase;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक len;
	u8 *buf;
	u32 enabled_irqs;
	पूर्णांक error;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक busy_cnt;
	अचिन्हित पूर्णांक clk_cycle;
	spinlock_t lock;	/* IRQ synchronization */
पूर्ण;

अटल व्योम uniphier_fi2c_fill_txfअगरo(काष्ठा uniphier_fi2c_priv *priv,
				      bool first)
अणु
	पूर्णांक fअगरo_space = UNIPHIER_FI2C_FIFO_SIZE;

	/*
	 * TX-FIFO stores slave address in it क्रम the first access.
	 * Decrement the counter.
	 */
	अगर (first)
		fअगरo_space--;

	जबतक (priv->len) अणु
		अगर (fअगरo_space-- <= 0)
			अवरोध;

		ग_लिखोl(*priv->buf++, priv->membase + UNIPHIER_FI2C_DTTX);
		priv->len--;
	पूर्ण
पूर्ण

अटल व्योम uniphier_fi2c_drain_rxfअगरo(काष्ठा uniphier_fi2c_priv *priv)
अणु
	पूर्णांक fअगरo_left = priv->flags & UNIPHIER_FI2C_BYTE_WISE ?
						1 : UNIPHIER_FI2C_FIFO_SIZE;

	जबतक (priv->len) अणु
		अगर (fअगरo_left-- <= 0)
			अवरोध;

		*priv->buf++ = पढ़ोl(priv->membase + UNIPHIER_FI2C_DTRX);
		priv->len--;
	पूर्ण
पूर्ण

अटल व्योम uniphier_fi2c_set_irqs(काष्ठा uniphier_fi2c_priv *priv)
अणु
	ग_लिखोl(priv->enabled_irqs, priv->membase + UNIPHIER_FI2C_IE);
पूर्ण

अटल व्योम uniphier_fi2c_clear_irqs(काष्ठा uniphier_fi2c_priv *priv,
				     u32 mask)
अणु
	ग_लिखोl(mask, priv->membase + UNIPHIER_FI2C_IC);
पूर्ण

अटल व्योम uniphier_fi2c_stop(काष्ठा uniphier_fi2c_priv *priv)
अणु
	priv->enabled_irqs |= UNIPHIER_FI2C_INT_STOP;
	uniphier_fi2c_set_irqs(priv);
	ग_लिखोl(UNIPHIER_FI2C_CR_MST | UNIPHIER_FI2C_CR_STO,
	       priv->membase + UNIPHIER_FI2C_CR);
पूर्ण

अटल irqवापस_t uniphier_fi2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uniphier_fi2c_priv *priv = dev_id;
	u32 irq_status;

	spin_lock(&priv->lock);

	irq_status = पढ़ोl(priv->membase + UNIPHIER_FI2C_INT);
	irq_status &= priv->enabled_irqs;

	अगर (irq_status & UNIPHIER_FI2C_INT_STOP)
		जाओ complete;

	अगर (unlikely(irq_status & UNIPHIER_FI2C_INT_AL)) अणु
		priv->error = -EAGAIN;
		जाओ complete;
	पूर्ण

	अगर (unlikely(irq_status & UNIPHIER_FI2C_INT_NA)) अणु
		priv->error = -ENXIO;
		अगर (priv->flags & UNIPHIER_FI2C_RD) अणु
			/*
			 * work around a hardware bug:
			 * The receive-completed पूर्णांकerrupt is never set even अगर
			 * STOP condition is detected after the address phase
			 * of पढ़ो transaction fails to get ACK.
			 * To aव्योम समय-out error, we issue STOP here,
			 * but करो not रुको क्रम its completion.
			 * It should be checked after निकासing this handler.
			 */
			uniphier_fi2c_stop(priv);
			priv->flags |= UNIPHIER_FI2C_DEFER_STOP_COMP;
			जाओ complete;
		पूर्ण
		जाओ stop;
	पूर्ण

	अगर (irq_status & UNIPHIER_FI2C_INT_TE) अणु
		अगर (!priv->len)
			जाओ data_करोne;

		uniphier_fi2c_fill_txfअगरo(priv, false);
		जाओ handled;
	पूर्ण

	अगर (irq_status & (UNIPHIER_FI2C_INT_RF | UNIPHIER_FI2C_INT_RB)) अणु
		uniphier_fi2c_drain_rxfअगरo(priv);
		/*
		 * If the number of bytes to पढ़ो is multiple of the FIFO size
		 * (msg->len == 8, 16, 24, ...), the INT_RF bit is set a little
		 * earlier than INT_RB. We रुको क्रम INT_RB to confirm the
		 * completion of the current message.
		 */
		अगर (!priv->len && (irq_status & UNIPHIER_FI2C_INT_RB))
			जाओ data_करोne;

		अगर (unlikely(priv->flags & UNIPHIER_FI2C_MANUAL_NACK)) अणु
			अगर (priv->len <= UNIPHIER_FI2C_FIFO_SIZE &&
			    !(priv->flags & UNIPHIER_FI2C_BYTE_WISE)) अणु
				priv->enabled_irqs |= UNIPHIER_FI2C_INT_RB;
				uniphier_fi2c_set_irqs(priv);
				priv->flags |= UNIPHIER_FI2C_BYTE_WISE;
			पूर्ण
			अगर (priv->len <= 1)
				ग_लिखोl(UNIPHIER_FI2C_CR_MST |
				       UNIPHIER_FI2C_CR_NACK,
				       priv->membase + UNIPHIER_FI2C_CR);
		पूर्ण

		जाओ handled;
	पूर्ण

	spin_unlock(&priv->lock);

	वापस IRQ_NONE;

data_करोne:
	अगर (priv->flags & UNIPHIER_FI2C_STOP) अणु
stop:
		uniphier_fi2c_stop(priv);
	पूर्ण अन्यथा अणु
complete:
		priv->enabled_irqs = 0;
		uniphier_fi2c_set_irqs(priv);
		complete(&priv->comp);
	पूर्ण

handled:
	/*
	 * This controller makes a छोड़ो जबतक any bit of the IRQ status is
	 * निश्चितed. Clear the निश्चितed bit to kick the controller just beक्रमe
	 * निकासing the handler.
	 */
	uniphier_fi2c_clear_irqs(priv, irq_status);

	spin_unlock(&priv->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम uniphier_fi2c_tx_init(काष्ठा uniphier_fi2c_priv *priv, u16 addr,
				  bool repeat)
अणु
	priv->enabled_irqs |= UNIPHIER_FI2C_INT_TE;
	uniphier_fi2c_set_irqs(priv);

	/* करो not use TX byte counter */
	ग_लिखोl(0, priv->membase + UNIPHIER_FI2C_TBC);
	/* set slave address */
	ग_लिखोl(UNIPHIER_FI2C_DTTX_CMD | addr << 1,
	       priv->membase + UNIPHIER_FI2C_DTTX);
	/*
	 * First chunk of data. For a repeated START condition, करो not ग_लिखो
	 * data to the TX fअगरo here to aव्योम the timing issue.
	 */
	अगर (!repeat)
		uniphier_fi2c_fill_txfअगरo(priv, true);
पूर्ण

अटल व्योम uniphier_fi2c_rx_init(काष्ठा uniphier_fi2c_priv *priv, u16 addr)
अणु
	priv->flags |= UNIPHIER_FI2C_RD;

	अगर (likely(priv->len < 256)) अणु
		/*
		 * If possible, use RX byte counter.
		 * It can स्वतःmatically handle NACK क्रम the last byte.
		 */
		ग_लिखोl(priv->len, priv->membase + UNIPHIER_FI2C_RBC);
		priv->enabled_irqs |= UNIPHIER_FI2C_INT_RF |
				      UNIPHIER_FI2C_INT_RB;
	पूर्ण अन्यथा अणु
		/*
		 * The byte counter can not count over 256.  In this हाल,
		 * करो not use it at all.  Drain data when FIFO माला_लो full,
		 * but treat the last portion as a special हाल.
		 */
		ग_लिखोl(0, priv->membase + UNIPHIER_FI2C_RBC);
		priv->flags |= UNIPHIER_FI2C_MANUAL_NACK;
		priv->enabled_irqs |= UNIPHIER_FI2C_INT_RF;
	पूर्ण

	uniphier_fi2c_set_irqs(priv);

	/* set slave address with RD bit */
	ग_लिखोl(UNIPHIER_FI2C_DTTX_CMD | UNIPHIER_FI2C_DTTX_RD | addr << 1,
	       priv->membase + UNIPHIER_FI2C_DTTX);
पूर्ण

अटल व्योम uniphier_fi2c_reset(काष्ठा uniphier_fi2c_priv *priv)
अणु
	ग_लिखोl(UNIPHIER_FI2C_RST_RST, priv->membase + UNIPHIER_FI2C_RST);
पूर्ण

अटल व्योम uniphier_fi2c_prepare_operation(काष्ठा uniphier_fi2c_priv *priv)
अणु
	ग_लिखोl(UNIPHIER_FI2C_BRST_FOEN | UNIPHIER_FI2C_BRST_RSCL,
	       priv->membase + UNIPHIER_FI2C_BRST);
पूर्ण

अटल व्योम uniphier_fi2c_recover(काष्ठा uniphier_fi2c_priv *priv)
अणु
	uniphier_fi2c_reset(priv);
	i2c_recover_bus(&priv->adap);
पूर्ण

अटल पूर्णांक uniphier_fi2c_master_xfer_one(काष्ठा i2c_adapter *adap,
					 काष्ठा i2c_msg *msg, bool repeat,
					 bool stop)
अणु
	काष्ठा uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);
	bool is_पढ़ो = msg->flags & I2C_M_RD;
	अचिन्हित दीर्घ समय_left, flags;

	priv->len = msg->len;
	priv->buf = msg->buf;
	priv->enabled_irqs = UNIPHIER_FI2C_INT_FAULTS;
	priv->error = 0;
	priv->flags = 0;

	अगर (stop)
		priv->flags |= UNIPHIER_FI2C_STOP;

	reinit_completion(&priv->comp);
	uniphier_fi2c_clear_irqs(priv, U32_MAX);
	ग_लिखोl(UNIPHIER_FI2C_RST_TBRST | UNIPHIER_FI2C_RST_RBRST,
	       priv->membase + UNIPHIER_FI2C_RST);	/* reset TX/RX FIFO */

	spin_lock_irqsave(&priv->lock, flags);

	अगर (is_पढ़ो)
		uniphier_fi2c_rx_init(priv, msg->addr);
	अन्यथा
		uniphier_fi2c_tx_init(priv, msg->addr, repeat);

	/*
	 * For a repeated START condition, writing a slave address to the FIFO
	 * kicks the controller. So, the UNIPHIER_FI2C_CR रेजिस्टर should be
	 * written only क्रम a non-repeated START condition.
	 */
	अगर (!repeat)
		ग_लिखोl(UNIPHIER_FI2C_CR_MST | UNIPHIER_FI2C_CR_STA,
		       priv->membase + UNIPHIER_FI2C_CR);

	spin_unlock_irqrestore(&priv->lock, flags);

	समय_left = रुको_क्रम_completion_समयout(&priv->comp, adap->समयout);

	spin_lock_irqsave(&priv->lock, flags);
	priv->enabled_irqs = 0;
	uniphier_fi2c_set_irqs(priv);
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (!समय_left) अणु
		dev_err(&adap->dev, "transaction timeout.\n");
		uniphier_fi2c_recover(priv);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (unlikely(priv->flags & UNIPHIER_FI2C_DEFER_STOP_COMP)) अणु
		u32 status;
		पूर्णांक ret;

		ret = पढ़ोl_poll_समयout(priv->membase + UNIPHIER_FI2C_SR,
					 status,
					 (status & UNIPHIER_FI2C_SR_STS) &&
					 !(status & UNIPHIER_FI2C_SR_BB),
					 1, 20);
		अगर (ret) अणु
			dev_err(&adap->dev,
				"stop condition was not completed.\n");
			uniphier_fi2c_recover(priv);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस priv->error;
पूर्ण

अटल पूर्णांक uniphier_fi2c_check_bus_busy(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);

	अगर (पढ़ोl(priv->membase + UNIPHIER_FI2C_SR) & UNIPHIER_FI2C_SR_DB) अणु
		अगर (priv->busy_cnt++ > 3) अणु
			/*
			 * If bus busy जारीs too दीर्घ, it is probably
			 * in a wrong state.  Try bus recovery.
			 */
			uniphier_fi2c_recover(priv);
			priv->busy_cnt = 0;
		पूर्ण

		वापस -EAGAIN;
	पूर्ण

	priv->busy_cnt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_fi2c_master_xfer(काष्ठा i2c_adapter *adap,
				     काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_msg *msg, *emsg = msgs + num;
	bool repeat = false;
	पूर्णांक ret;

	ret = uniphier_fi2c_check_bus_busy(adap);
	अगर (ret)
		वापस ret;

	क्रम (msg = msgs; msg < emsg; msg++) अणु
		/* Emit STOP अगर it is the last message or I2C_M_STOP is set. */
		bool stop = (msg + 1 == emsg) || (msg->flags & I2C_M_STOP);

		ret = uniphier_fi2c_master_xfer_one(adap, msg, repeat, stop);
		अगर (ret)
			वापस ret;

		repeat = !stop;
	पूर्ण

	वापस num;
पूर्ण

अटल u32 uniphier_fi2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm uniphier_fi2c_algo = अणु
	.master_xfer = uniphier_fi2c_master_xfer,
	.functionality = uniphier_fi2c_functionality,
पूर्ण;

अटल पूर्णांक uniphier_fi2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);

	वापस !!(पढ़ोl(priv->membase + UNIPHIER_FI2C_BM) &
							UNIPHIER_FI2C_BM_SCLS);
पूर्ण

अटल व्योम uniphier_fi2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);

	ग_लिखोl(val ? UNIPHIER_FI2C_BRST_RSCL : 0,
	       priv->membase + UNIPHIER_FI2C_BRST);
पूर्ण

अटल पूर्णांक uniphier_fi2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);

	वापस !!(पढ़ोl(priv->membase + UNIPHIER_FI2C_BM) &
							UNIPHIER_FI2C_BM_SDAS);
पूर्ण

अटल व्योम uniphier_fi2c_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	uniphier_fi2c_prepare_operation(i2c_get_adapdata(adap));
पूर्ण

अटल काष्ठा i2c_bus_recovery_info uniphier_fi2c_bus_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.get_scl = uniphier_fi2c_get_scl,
	.set_scl = uniphier_fi2c_set_scl,
	.get_sda = uniphier_fi2c_get_sda,
	.unprepare_recovery = uniphier_fi2c_unprepare_recovery,
पूर्ण;

अटल व्योम uniphier_fi2c_hw_init(काष्ठा uniphier_fi2c_priv *priv)
अणु
	अचिन्हित पूर्णांक cyc = priv->clk_cycle;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(priv->membase + UNIPHIER_FI2C_CR);
	पंचांगp |= UNIPHIER_FI2C_CR_MST;
	ग_लिखोl(पंचांगp, priv->membase + UNIPHIER_FI2C_CR);

	uniphier_fi2c_reset(priv);

	/*
	 *  Standard-mode: tLOW + tHIGH = 10 us
	 *  Fast-mode:     tLOW + tHIGH = 2.5 us
	 */
	ग_लिखोl(cyc, priv->membase + UNIPHIER_FI2C_CYC);
	/*
	 *  Standard-mode: tLOW = 4.7 us, tHIGH = 4.0 us, tBUF = 4.7 us
	 *  Fast-mode:     tLOW = 1.3 us, tHIGH = 0.6 us, tBUF = 1.3 us
	 * "tLow/tHIGH = 5/4" meets both.
	 */
	ग_लिखोl(cyc * 5 / 9, priv->membase + UNIPHIER_FI2C_LCTL);
	/*
	 *  Standard-mode: tHD;STA = 4.0 us, tSU;STA = 4.7 us, tSU;STO = 4.0 us
	 *  Fast-mode:     tHD;STA = 0.6 us, tSU;STA = 0.6 us, tSU;STO = 0.6 us
	 */
	ग_लिखोl(cyc / 2, priv->membase + UNIPHIER_FI2C_SSUT);
	/*
	 *  Standard-mode: tSU;DAT = 250 ns
	 *  Fast-mode:     tSU;DAT = 100 ns
	 */
	ग_लिखोl(cyc / 16, priv->membase + UNIPHIER_FI2C_DSUT);

	uniphier_fi2c_prepare_operation(priv);
पूर्ण

अटल पूर्णांक uniphier_fi2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_fi2c_priv *priv;
	u32 bus_speed;
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक irq, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->membase))
		वापस PTR_ERR(priv->membase);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (of_property_पढ़ो_u32(dev->of_node, "clock-frequency", &bus_speed))
		bus_speed = I2C_MAX_STANDARD_MODE_FREQ;

	अगर (!bus_speed || bus_speed > I2C_MAX_FAST_MODE_FREQ) अणु
		dev_err(dev, "invalid clock-frequency %d\n", bus_speed);
		वापस -EINVAL;
	पूर्ण

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	clk_rate = clk_get_rate(priv->clk);
	अगर (!clk_rate) अणु
		dev_err(dev, "input clock rate should not be zero\n");
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	priv->clk_cycle = clk_rate / bus_speed;
	init_completion(&priv->comp);
	spin_lock_init(&priv->lock);
	priv->adap.owner = THIS_MODULE;
	priv->adap.algo = &uniphier_fi2c_algo;
	priv->adap.dev.parent = dev;
	priv->adap.dev.of_node = dev->of_node;
	strlcpy(priv->adap.name, "UniPhier FI2C", माप(priv->adap.name));
	priv->adap.bus_recovery_info = &uniphier_fi2c_bus_recovery_info;
	i2c_set_adapdata(&priv->adap, priv);
	platक्रमm_set_drvdata(pdev, priv);

	uniphier_fi2c_hw_init(priv);

	ret = devm_request_irq(dev, irq, uniphier_fi2c_पूर्णांकerrupt, 0,
			       pdev->name, priv);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq %d\n", irq);
		जाओ disable_clk;
	पूर्ण

	ret = i2c_add_adapter(&priv->adap);
disable_clk:
	अगर (ret)
		clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_fi2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_fi2c_priv *priv = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_fi2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा uniphier_fi2c_priv *priv = dev_get_drvdata(dev);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_fi2c_resume(काष्ठा device *dev)
अणु
	काष्ठा uniphier_fi2c_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	uniphier_fi2c_hw_init(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uniphier_fi2c_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(uniphier_fi2c_suspend, uniphier_fi2c_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_fi2c_match[] = अणु
	अणु .compatible = "socionext,uniphier-fi2c" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_fi2c_match);

अटल काष्ठा platक्रमm_driver uniphier_fi2c_drv = अणु
	.probe  = uniphier_fi2c_probe,
	.हटाओ = uniphier_fi2c_हटाओ,
	.driver = अणु
		.name  = "uniphier-fi2c",
		.of_match_table = uniphier_fi2c_match,
		.pm = &uniphier_fi2c_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_fi2c_drv);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier FIFO-builtin I2C bus driver");
MODULE_LICENSE("GPL");
