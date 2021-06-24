<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा UNIPHIER_I2C_DTRM	0x00	/* TX रेजिस्टर */
#घोषणा     UNIPHIER_I2C_DTRM_IRQEN	BIT(11)	/* enable पूर्णांकerrupt */
#घोषणा     UNIPHIER_I2C_DTRM_STA	BIT(10)	/* start condition */
#घोषणा     UNIPHIER_I2C_DTRM_STO	BIT(9)	/* stop condition */
#घोषणा     UNIPHIER_I2C_DTRM_NACK	BIT(8)	/* करो not वापस ACK */
#घोषणा     UNIPHIER_I2C_DTRM_RD	BIT(0)	/* पढ़ो transaction */
#घोषणा UNIPHIER_I2C_DREC	0x04	/* RX रेजिस्टर */
#घोषणा     UNIPHIER_I2C_DREC_MST	BIT(14)	/* 1 = master, 0 = slave */
#घोषणा     UNIPHIER_I2C_DREC_TX	BIT(13)	/* 1 = transmit, 0 = receive */
#घोषणा     UNIPHIER_I2C_DREC_STS	BIT(12)	/* stop condition detected */
#घोषणा     UNIPHIER_I2C_DREC_LRB	BIT(11)	/* no ACK */
#घोषणा     UNIPHIER_I2C_DREC_LAB	BIT(9)	/* arbitration lost */
#घोषणा     UNIPHIER_I2C_DREC_BBN	BIT(8)	/* bus not busy */
#घोषणा UNIPHIER_I2C_MYAD	0x08	/* slave address */
#घोषणा UNIPHIER_I2C_CLK	0x0c	/* घड़ी frequency control */
#घोषणा UNIPHIER_I2C_BRST	0x10	/* bus reset */
#घोषणा     UNIPHIER_I2C_BRST_FOEN	BIT(1)	/* normal operation */
#घोषणा     UNIPHIER_I2C_BRST_RSCL	BIT(0)	/* release SCL */
#घोषणा UNIPHIER_I2C_HOLD	0x14	/* hold समय control */
#घोषणा UNIPHIER_I2C_BSTS	0x18	/* bus status monitor */
#घोषणा     UNIPHIER_I2C_BSTS_SDA	BIT(1)	/* पढ़ोback of SDA line */
#घोषणा     UNIPHIER_I2C_BSTS_SCL	BIT(0)	/* पढ़ोback of SCL line */
#घोषणा UNIPHIER_I2C_NOISE	0x1c	/* noise filter control */
#घोषणा UNIPHIER_I2C_SETUP	0x20	/* setup समय control */

काष्ठा uniphier_i2c_priv अणु
	काष्ठा completion comp;
	काष्ठा i2c_adapter adap;
	व्योम __iomem *membase;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक busy_cnt;
	अचिन्हित पूर्णांक clk_cycle;
पूर्ण;

अटल irqवापस_t uniphier_i2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uniphier_i2c_priv *priv = dev_id;

	/*
	 * This hardware uses edge triggered पूर्णांकerrupt.  Do not touch the
	 * hardware रेजिस्टरs in this handler to make sure to catch the next
	 * पूर्णांकerrupt edge.  Just send a complete संकेत and वापस.
	 */
	complete(&priv->comp);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uniphier_i2c_xfer_byte(काष्ठा i2c_adapter *adap, u32 txdata,
				  u32 *rxdatap)
अणु
	काष्ठा uniphier_i2c_priv *priv = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ समय_left;
	u32 rxdata;

	reinit_completion(&priv->comp);

	txdata |= UNIPHIER_I2C_DTRM_IRQEN;
	ग_लिखोl(txdata, priv->membase + UNIPHIER_I2C_DTRM);

	समय_left = रुको_क्रम_completion_समयout(&priv->comp, adap->समयout);
	अगर (unlikely(!समय_left)) अणु
		dev_err(&adap->dev, "transaction timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	rxdata = पढ़ोl(priv->membase + UNIPHIER_I2C_DREC);
	अगर (rxdatap)
		*rxdatap = rxdata;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_i2c_send_byte(काष्ठा i2c_adapter *adap, u32 txdata)
अणु
	u32 rxdata;
	पूर्णांक ret;

	ret = uniphier_i2c_xfer_byte(adap, txdata, &rxdata);
	अगर (ret)
		वापस ret;

	अगर (unlikely(rxdata & UNIPHIER_I2C_DREC_LAB))
		वापस -EAGAIN;

	अगर (unlikely(rxdata & UNIPHIER_I2C_DREC_LRB))
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_i2c_tx(काष्ठा i2c_adapter *adap, u16 addr, u16 len,
			   स्थिर u8 *buf)
अणु
	पूर्णांक ret;

	ret = uniphier_i2c_send_byte(adap, addr << 1 |
				     UNIPHIER_I2C_DTRM_STA |
				     UNIPHIER_I2C_DTRM_NACK);
	अगर (ret)
		वापस ret;

	जबतक (len--) अणु
		ret = uniphier_i2c_send_byte(adap,
					     UNIPHIER_I2C_DTRM_NACK | *buf++);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_i2c_rx(काष्ठा i2c_adapter *adap, u16 addr, u16 len,
			   u8 *buf)
अणु
	पूर्णांक ret;

	ret = uniphier_i2c_send_byte(adap, addr << 1 |
				     UNIPHIER_I2C_DTRM_STA |
				     UNIPHIER_I2C_DTRM_NACK |
				     UNIPHIER_I2C_DTRM_RD);
	अगर (ret)
		वापस ret;

	जबतक (len--) अणु
		u32 rxdata;

		ret = uniphier_i2c_xfer_byte(adap,
					     len ? 0 : UNIPHIER_I2C_DTRM_NACK,
					     &rxdata);
		अगर (ret)
			वापस ret;
		*buf++ = rxdata;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_i2c_stop(काष्ठा i2c_adapter *adap)
अणु
	वापस uniphier_i2c_send_byte(adap, UNIPHIER_I2C_DTRM_STO |
				      UNIPHIER_I2C_DTRM_NACK);
पूर्ण

अटल पूर्णांक uniphier_i2c_master_xfer_one(काष्ठा i2c_adapter *adap,
					काष्ठा i2c_msg *msg, bool stop)
अणु
	bool is_पढ़ो = msg->flags & I2C_M_RD;
	bool recovery = false;
	पूर्णांक ret;

	अगर (is_पढ़ो)
		ret = uniphier_i2c_rx(adap, msg->addr, msg->len, msg->buf);
	अन्यथा
		ret = uniphier_i2c_tx(adap, msg->addr, msg->len, msg->buf);

	अगर (ret == -EAGAIN) /* could not acquire bus. bail out without STOP */
		वापस ret;

	अगर (ret == -ETIMEDOUT) अणु
		/* This error is fatal.  Needs recovery. */
		stop = false;
		recovery = true;
	पूर्ण

	अगर (stop) अणु
		पूर्णांक ret2 = uniphier_i2c_stop(adap);

		अगर (ret2) अणु
			/* Failed to issue STOP.  The bus needs recovery. */
			recovery = true;
			ret = ret ?: ret2;
		पूर्ण
	पूर्ण

	अगर (recovery)
		i2c_recover_bus(adap);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_i2c_check_bus_busy(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा uniphier_i2c_priv *priv = i2c_get_adapdata(adap);

	अगर (!(पढ़ोl(priv->membase + UNIPHIER_I2C_DREC) &
						UNIPHIER_I2C_DREC_BBN)) अणु
		अगर (priv->busy_cnt++ > 3) अणु
			/*
			 * If bus busy जारीs too दीर्घ, it is probably
			 * in a wrong state.  Try bus recovery.
			 */
			i2c_recover_bus(adap);
			priv->busy_cnt = 0;
		पूर्ण

		वापस -EAGAIN;
	पूर्ण

	priv->busy_cnt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_i2c_master_xfer(काष्ठा i2c_adapter *adap,
				    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_msg *msg, *emsg = msgs + num;
	पूर्णांक ret;

	ret = uniphier_i2c_check_bus_busy(adap);
	अगर (ret)
		वापस ret;

	क्रम (msg = msgs; msg < emsg; msg++) अणु
		/* Emit STOP अगर it is the last message or I2C_M_STOP is set. */
		bool stop = (msg + 1 == emsg) || (msg->flags & I2C_M_STOP);

		ret = uniphier_i2c_master_xfer_one(adap, msg, stop);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस num;
पूर्ण

अटल u32 uniphier_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm uniphier_i2c_algo = अणु
	.master_xfer = uniphier_i2c_master_xfer,
	.functionality = uniphier_i2c_functionality,
पूर्ण;

अटल व्योम uniphier_i2c_reset(काष्ठा uniphier_i2c_priv *priv, bool reset_on)
अणु
	u32 val = UNIPHIER_I2C_BRST_RSCL;

	val |= reset_on ? 0 : UNIPHIER_I2C_BRST_FOEN;
	ग_लिखोl(val, priv->membase + UNIPHIER_I2C_BRST);
पूर्ण

अटल पूर्णांक uniphier_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा uniphier_i2c_priv *priv = i2c_get_adapdata(adap);

	वापस !!(पढ़ोl(priv->membase + UNIPHIER_I2C_BSTS) &
							UNIPHIER_I2C_BSTS_SCL);
पूर्ण

अटल व्योम uniphier_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा uniphier_i2c_priv *priv = i2c_get_adapdata(adap);

	ग_लिखोl(val ? UNIPHIER_I2C_BRST_RSCL : 0,
	       priv->membase + UNIPHIER_I2C_BRST);
पूर्ण

अटल पूर्णांक uniphier_i2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा uniphier_i2c_priv *priv = i2c_get_adapdata(adap);

	वापस !!(पढ़ोl(priv->membase + UNIPHIER_I2C_BSTS) &
							UNIPHIER_I2C_BSTS_SDA);
पूर्ण

अटल व्योम uniphier_i2c_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	uniphier_i2c_reset(i2c_get_adapdata(adap), false);
पूर्ण

अटल काष्ठा i2c_bus_recovery_info uniphier_i2c_bus_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.get_scl = uniphier_i2c_get_scl,
	.set_scl = uniphier_i2c_set_scl,
	.get_sda = uniphier_i2c_get_sda,
	.unprepare_recovery = uniphier_i2c_unprepare_recovery,
पूर्ण;

अटल व्योम uniphier_i2c_hw_init(काष्ठा uniphier_i2c_priv *priv)
अणु
	अचिन्हित पूर्णांक cyc = priv->clk_cycle;

	uniphier_i2c_reset(priv, true);

	/*
	 * Bit30-16: घड़ी cycles of tLOW.
	 *  Standard-mode: tLOW = 4.7 us, tHIGH = 4.0 us
	 *  Fast-mode:     tLOW = 1.3 us, tHIGH = 0.6 us
	 * "tLow/tHIGH = 5/4" meets both.
	 */
	ग_लिखोl((cyc * 5 / 9 << 16) | cyc, priv->membase + UNIPHIER_I2C_CLK);

	uniphier_i2c_reset(priv, false);
पूर्ण

अटल पूर्णांक uniphier_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_i2c_priv *priv;
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
	priv->adap.owner = THIS_MODULE;
	priv->adap.algo = &uniphier_i2c_algo;
	priv->adap.dev.parent = dev;
	priv->adap.dev.of_node = dev->of_node;
	strlcpy(priv->adap.name, "UniPhier I2C", माप(priv->adap.name));
	priv->adap.bus_recovery_info = &uniphier_i2c_bus_recovery_info;
	i2c_set_adapdata(&priv->adap, priv);
	platक्रमm_set_drvdata(pdev, priv);

	uniphier_i2c_hw_init(priv);

	ret = devm_request_irq(dev, irq, uniphier_i2c_पूर्णांकerrupt, 0, pdev->name,
			       priv);
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

अटल पूर्णांक uniphier_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_i2c_priv *priv = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा uniphier_i2c_priv *priv = dev_get_drvdata(dev);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused uniphier_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा uniphier_i2c_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	uniphier_i2c_hw_init(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uniphier_i2c_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(uniphier_i2c_suspend, uniphier_i2c_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_i2c_match[] = अणु
	अणु .compatible = "socionext,uniphier-i2c" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_i2c_match);

अटल काष्ठा platक्रमm_driver uniphier_i2c_drv = अणु
	.probe  = uniphier_i2c_probe,
	.हटाओ = uniphier_i2c_हटाओ,
	.driver = अणु
		.name  = "uniphier-i2c",
		.of_match_table = uniphier_i2c_match,
		.pm = &uniphier_i2c_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_i2c_drv);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier I2C bus driver");
MODULE_LICENSE("GPL");
