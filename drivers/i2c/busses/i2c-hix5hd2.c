<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 HiSilicon Limited.
 *
 * Now only support 7 bit address.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

/* Register Map */
#घोषणा HIX5I2C_CTRL		0x00
#घोषणा HIX5I2C_COM		0x04
#घोषणा HIX5I2C_ICR		0x08
#घोषणा HIX5I2C_SR		0x0c
#घोषणा HIX5I2C_SCL_H		0x10
#घोषणा HIX5I2C_SCL_L		0x14
#घोषणा HIX5I2C_TXR		0x18
#घोषणा HIX5I2C_RXR		0x1c

/* I2C_CTRL_REG */
#घोषणा I2C_ENABLE		BIT(8)
#घोषणा I2C_UNMASK_TOTAL	BIT(7)
#घोषणा I2C_UNMASK_START	BIT(6)
#घोषणा I2C_UNMASK_END		BIT(5)
#घोषणा I2C_UNMASK_SEND		BIT(4)
#घोषणा I2C_UNMASK_RECEIVE	BIT(3)
#घोषणा I2C_UNMASK_ACK		BIT(2)
#घोषणा I2C_UNMASK_ARBITRATE	BIT(1)
#घोषणा I2C_UNMASK_OVER		BIT(0)
#घोषणा I2C_UNMASK_ALL		(I2C_UNMASK_ACK | I2C_UNMASK_OVER)

/* I2C_COM_REG */
#घोषणा I2C_NO_ACK		BIT(4)
#घोषणा I2C_START		BIT(3)
#घोषणा I2C_READ		BIT(2)
#घोषणा I2C_WRITE		BIT(1)
#घोषणा I2C_STOP		BIT(0)

/* I2C_ICR_REG */
#घोषणा I2C_CLEAR_START		BIT(6)
#घोषणा I2C_CLEAR_END		BIT(5)
#घोषणा I2C_CLEAR_SEND		BIT(4)
#घोषणा I2C_CLEAR_RECEIVE	BIT(3)
#घोषणा I2C_CLEAR_ACK		BIT(2)
#घोषणा I2C_CLEAR_ARBITRATE	BIT(1)
#घोषणा I2C_CLEAR_OVER		BIT(0)
#घोषणा I2C_CLEAR_ALL		(I2C_CLEAR_START | I2C_CLEAR_END | \
				I2C_CLEAR_SEND | I2C_CLEAR_RECEIVE | \
				I2C_CLEAR_ACK | I2C_CLEAR_ARBITRATE | \
				I2C_CLEAR_OVER)

/* I2C_SR_REG */
#घोषणा I2C_BUSY		BIT(7)
#घोषणा I2C_START_INTR		BIT(6)
#घोषणा I2C_END_INTR		BIT(5)
#घोषणा I2C_SEND_INTR		BIT(4)
#घोषणा I2C_RECEIVE_INTR	BIT(3)
#घोषणा I2C_ACK_INTR		BIT(2)
#घोषणा I2C_ARBITRATE_INTR	BIT(1)
#घोषणा I2C_OVER_INTR		BIT(0)

क्रमागत hix5hd2_i2c_state अणु
	HIX5I2C_STAT_RW_ERR = -1,
	HIX5I2C_STAT_INIT,
	HIX5I2C_STAT_RW,
	HIX5I2C_STAT_SND_STOP,
	HIX5I2C_STAT_RW_SUCCESS,
पूर्ण;

काष्ठा hix5hd2_i2c_priv अणु
	काष्ठा i2c_adapter adap;
	काष्ठा i2c_msg *msg;
	काष्ठा completion msg_complete;
	अचिन्हित पूर्णांक msg_idx;
	अचिन्हित पूर्णांक msg_len;
	पूर्णांक stop;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा device *dev;
	spinlock_t lock;	/* IRQ synchronization */
	पूर्णांक err;
	अचिन्हित पूर्णांक freq;
	क्रमागत hix5hd2_i2c_state state;
पूर्ण;

अटल u32 hix5hd2_i2c_clr_pend_irq(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	u32 val = पढ़ोl_relaxed(priv->regs + HIX5I2C_SR);

	ग_लिखोl_relaxed(val, priv->regs + HIX5I2C_ICR);

	वापस val;
पूर्ण

अटल व्योम hix5hd2_i2c_clr_all_irq(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	ग_लिखोl_relaxed(I2C_CLEAR_ALL, priv->regs + HIX5I2C_ICR);
पूर्ण

अटल व्योम hix5hd2_i2c_disable_irq(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	ग_लिखोl_relaxed(0, priv->regs + HIX5I2C_CTRL);
पूर्ण

अटल व्योम hix5hd2_i2c_enable_irq(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	ग_लिखोl_relaxed(I2C_ENABLE | I2C_UNMASK_TOTAL | I2C_UNMASK_ALL,
		       priv->regs + HIX5I2C_CTRL);
पूर्ण

अटल व्योम hix5hd2_i2c_drv_setrate(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	u32 rate, val;
	u32 scl, sysघड़ी;

	/* बंद all i2c पूर्णांकerrupt */
	val = पढ़ोl_relaxed(priv->regs + HIX5I2C_CTRL);
	ग_लिखोl_relaxed(val & (~I2C_UNMASK_TOTAL), priv->regs + HIX5I2C_CTRL);

	rate = priv->freq;
	sysघड़ी = clk_get_rate(priv->clk);
	scl = (sysघड़ी / (rate * 2)) / 2 - 1;
	ग_लिखोl_relaxed(scl, priv->regs + HIX5I2C_SCL_H);
	ग_लिखोl_relaxed(scl, priv->regs + HIX5I2C_SCL_L);

	/* restore original पूर्णांकerrupt*/
	ग_लिखोl_relaxed(val, priv->regs + HIX5I2C_CTRL);

	dev_dbg(priv->dev, "%s: sysclock=%d, rate=%d, scl=%d\n",
		__func__, sysघड़ी, rate, scl);
पूर्ण

अटल व्योम hix5hd2_i2c_init(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	hix5hd2_i2c_disable_irq(priv);
	hix5hd2_i2c_drv_setrate(priv);
	hix5hd2_i2c_clr_all_irq(priv);
	hix5hd2_i2c_enable_irq(priv);
पूर्ण

अटल व्योम hix5hd2_i2c_reset(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	clk_disable_unprepare(priv->clk);
	msleep(20);
	clk_prepare_enable(priv->clk);
	hix5hd2_i2c_init(priv);
पूर्ण

अटल पूर्णांक hix5hd2_i2c_रुको_bus_idle(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	अचिन्हित दीर्घ stop_समय;
	u32 पूर्णांक_status;

	/* रुको क्रम 100 milli seconds क्रम the bus to be idle */
	stop_समय = jअगरfies + msecs_to_jअगरfies(100);
	करो अणु
		पूर्णांक_status = hix5hd2_i2c_clr_pend_irq(priv);
		अगर (!(पूर्णांक_status & I2C_BUSY))
			वापस 0;

		usleep_range(50, 200);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop_समय));

	वापस -EBUSY;
पूर्ण

अटल व्योम hix5hd2_rw_over(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	अगर (priv->state == HIX5I2C_STAT_SND_STOP)
		dev_dbg(priv->dev, "%s: rw and send stop over\n", __func__);
	अन्यथा
		dev_dbg(priv->dev, "%s: have not data to send\n", __func__);

	priv->state = HIX5I2C_STAT_RW_SUCCESS;
	priv->err = 0;
पूर्ण

अटल व्योम hix5hd2_rw_handle_stop(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	अगर (priv->stop) अणु
		priv->state = HIX5I2C_STAT_SND_STOP;
		ग_लिखोl_relaxed(I2C_STOP, priv->regs + HIX5I2C_COM);
	पूर्ण अन्यथा अणु
		hix5hd2_rw_over(priv);
	पूर्ण
पूर्ण

अटल व्योम hix5hd2_पढ़ो_handle(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	अगर (priv->msg_len == 1) अणु
		/* the last byte करोn't need send ACK */
		ग_लिखोl_relaxed(I2C_READ | I2C_NO_ACK, priv->regs + HIX5I2C_COM);
	पूर्ण अन्यथा अगर (priv->msg_len > 1) अणु
		/* अगर i2c master receive data will send ACK */
		ग_लिखोl_relaxed(I2C_READ, priv->regs + HIX5I2C_COM);
	पूर्ण अन्यथा अणु
		hix5hd2_rw_handle_stop(priv);
	पूर्ण
पूर्ण

अटल व्योम hix5hd2_ग_लिखो_handle(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	u8 data;

	अगर (priv->msg_len > 0) अणु
		data = priv->msg->buf[priv->msg_idx++];
		ग_लिखोl_relaxed(data, priv->regs + HIX5I2C_TXR);
		ग_लिखोl_relaxed(I2C_WRITE, priv->regs + HIX5I2C_COM);
	पूर्ण अन्यथा अणु
		hix5hd2_rw_handle_stop(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक hix5hd2_rw_preprocess(काष्ठा hix5hd2_i2c_priv *priv)
अणु
	u8 data;

	अगर (priv->state == HIX5I2C_STAT_INIT) अणु
		priv->state = HIX5I2C_STAT_RW;
	पूर्ण अन्यथा अगर (priv->state == HIX5I2C_STAT_RW) अणु
		अगर (priv->msg->flags & I2C_M_RD) अणु
			data = पढ़ोl_relaxed(priv->regs + HIX5I2C_RXR);
			priv->msg->buf[priv->msg_idx++] = data;
		पूर्ण
		priv->msg_len--;
	पूर्ण अन्यथा अणु
		dev_dbg(priv->dev, "%s: error: priv->state = %d, msg_len = %d\n",
			__func__, priv->state, priv->msg_len);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t hix5hd2_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा hix5hd2_i2c_priv *priv = dev_id;
	u32 पूर्णांक_status;
	पूर्णांक ret;

	spin_lock(&priv->lock);

	पूर्णांक_status = hix5hd2_i2c_clr_pend_irq(priv);

	/* handle error */
	अगर (पूर्णांक_status & I2C_ARBITRATE_INTR) अणु
		/* bus error */
		dev_dbg(priv->dev, "ARB bus loss\n");
		priv->err = -EAGAIN;
		priv->state = HIX5I2C_STAT_RW_ERR;
		जाओ stop;
	पूर्ण अन्यथा अगर (पूर्णांक_status & I2C_ACK_INTR) अणु
		/* ack error */
		dev_dbg(priv->dev, "No ACK from device\n");
		priv->err = -ENXIO;
		priv->state = HIX5I2C_STAT_RW_ERR;
		जाओ stop;
	पूर्ण

	अगर (पूर्णांक_status & I2C_OVER_INTR) अणु
		अगर (priv->msg_len > 0) अणु
			ret = hix5hd2_rw_preprocess(priv);
			अगर (ret) अणु
				priv->err = ret;
				priv->state = HIX5I2C_STAT_RW_ERR;
				जाओ stop;
			पूर्ण
			अगर (priv->msg->flags & I2C_M_RD)
				hix5hd2_पढ़ो_handle(priv);
			अन्यथा
				hix5hd2_ग_लिखो_handle(priv);
		पूर्ण अन्यथा अणु
			hix5hd2_rw_over(priv);
		पूर्ण
	पूर्ण

stop:
	अगर ((priv->state == HIX5I2C_STAT_RW_SUCCESS &&
	     priv->msg->len == priv->msg_idx) ||
	    (priv->state == HIX5I2C_STAT_RW_ERR)) अणु
		hix5hd2_i2c_disable_irq(priv);
		hix5hd2_i2c_clr_pend_irq(priv);
		complete(&priv->msg_complete);
	पूर्ण

	spin_unlock(&priv->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hix5hd2_i2c_message_start(काष्ठा hix5hd2_i2c_priv *priv, पूर्णांक stop)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	hix5hd2_i2c_clr_all_irq(priv);
	hix5hd2_i2c_enable_irq(priv);

	ग_लिखोl_relaxed(i2c_8bit_addr_from_msg(priv->msg),
		       priv->regs + HIX5I2C_TXR);

	ग_लिखोl_relaxed(I2C_WRITE | I2C_START, priv->regs + HIX5I2C_COM);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक hix5hd2_i2c_xfer_msg(काष्ठा hix5hd2_i2c_priv *priv,
				काष्ठा i2c_msg *msgs, पूर्णांक stop)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	priv->msg = msgs;
	priv->msg_idx = 0;
	priv->msg_len = priv->msg->len;
	priv->stop = stop;
	priv->err = 0;
	priv->state = HIX5I2C_STAT_INIT;

	reinit_completion(&priv->msg_complete);
	hix5hd2_i2c_message_start(priv, stop);

	समयout = रुको_क्रम_completion_समयout(&priv->msg_complete,
					      priv->adap.समयout);
	अगर (समयout == 0) अणु
		priv->state = HIX5I2C_STAT_RW_ERR;
		priv->err = -ETIMEDOUT;
		dev_warn(priv->dev, "%s timeout=%d\n",
			 msgs->flags & I2C_M_RD ? "rx" : "tx",
			 priv->adap.समयout);
	पूर्ण
	ret = priv->state;

	/*
	 * If this is the last message to be transfered (stop == 1)
	 * Then check अगर the bus can be brought back to idle.
	 */
	अगर (priv->state == HIX5I2C_STAT_RW_SUCCESS && stop)
		ret = hix5hd2_i2c_रुको_bus_idle(priv);

	अगर (ret < 0)
		hix5hd2_i2c_reset(priv);

	वापस priv->err;
पूर्ण

अटल पूर्णांक hix5hd2_i2c_xfer(काष्ठा i2c_adapter *adap,
			    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा hix5hd2_i2c_priv *priv = i2c_get_adapdata(adap);
	पूर्णांक i, ret, stop;

	pm_runसमय_get_sync(priv->dev);

	क्रम (i = 0; i < num; i++, msgs++) अणु
		stop = (i == num - 1);
		ret = hix5hd2_i2c_xfer_msg(priv, msgs, stop);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = num;

out:
	pm_runसमय_mark_last_busy(priv->dev);
	pm_runसमय_put_स्वतःsuspend(priv->dev);
	वापस ret;
पूर्ण

अटल u32 hix5hd2_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm hix5hd2_i2c_algorithm = अणु
	.master_xfer		= hix5hd2_i2c_xfer,
	.functionality		= hix5hd2_i2c_func,
पूर्ण;

अटल पूर्णांक hix5hd2_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा hix5hd2_i2c_priv *priv;
	अचिन्हित पूर्णांक freq;
	पूर्णांक irq, ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &freq)) अणु
		/* use 100k as शेष value */
		priv->freq = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण अन्यथा अणु
		अगर (freq > I2C_MAX_FAST_MODE_FREQ) अणु
			priv->freq = I2C_MAX_FAST_MODE_FREQ;
			dev_warn(priv->dev, "use max freq %d instead\n",
				 I2C_MAX_FAST_MODE_FREQ);
		पूर्ण अन्यथा अणु
			priv->freq = freq;
		पूर्ण
	पूर्ण

	priv->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण
	clk_prepare_enable(priv->clk);

	strlcpy(priv->adap.name, "hix5hd2-i2c", माप(priv->adap.name));
	priv->dev = &pdev->dev;
	priv->adap.owner = THIS_MODULE;
	priv->adap.algo = &hix5hd2_i2c_algorithm;
	priv->adap.retries = 3;
	priv->adap.dev.of_node = np;
	priv->adap.algo_data = priv;
	priv->adap.dev.parent = &pdev->dev;
	i2c_set_adapdata(&priv->adap, priv);
	platक्रमm_set_drvdata(pdev, priv);
	spin_lock_init(&priv->lock);
	init_completion(&priv->msg_complete);

	hix5hd2_i2c_init(priv);

	ret = devm_request_irq(&pdev->dev, irq, hix5hd2_i2c_irq,
			       IRQF_NO_SUSPEND, dev_name(&pdev->dev), priv);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "cannot request HS-I2C IRQ %d\n", irq);
		जाओ err_clk;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(priv->dev, MSEC_PER_SEC);
	pm_runसमय_use_स्वतःsuspend(priv->dev);
	pm_runसमय_set_active(priv->dev);
	pm_runसमय_enable(priv->dev);

	ret = i2c_add_adapter(&priv->adap);
	अगर (ret < 0)
		जाओ err_runसमय;

	वापस ret;

err_runसमय:
	pm_runसमय_disable(priv->dev);
	pm_runसमय_set_suspended(priv->dev);
err_clk:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक hix5hd2_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hix5hd2_i2c_priv *priv = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	pm_runसमय_disable(priv->dev);
	pm_runसमय_set_suspended(priv->dev);
	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक hix5hd2_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hix5hd2_i2c_priv *priv = dev_get_drvdata(dev);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक hix5hd2_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hix5hd2_i2c_priv *priv = dev_get_drvdata(dev);

	clk_prepare_enable(priv->clk);
	hix5hd2_i2c_init(priv);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops hix5hd2_i2c_pm_ops = अणु
	SET_RUNTIME_PM_OPS(hix5hd2_i2c_runसमय_suspend,
			      hix5hd2_i2c_runसमय_resume,
			      शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id hix5hd2_i2c_match[] = अणु
	अणु .compatible = "hisilicon,hix5hd2-i2c" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hix5hd2_i2c_match);

अटल काष्ठा platक्रमm_driver hix5hd2_i2c_driver = अणु
	.probe		= hix5hd2_i2c_probe,
	.हटाओ		= hix5hd2_i2c_हटाओ,
	.driver		= अणु
		.name	= "hix5hd2-i2c",
		.pm	= &hix5hd2_i2c_pm_ops,
		.of_match_table = hix5hd2_i2c_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hix5hd2_i2c_driver);

MODULE_DESCRIPTION("Hix5hd2 I2C Bus driver");
MODULE_AUTHOR("Wei Yan <sledge.yanwei@huawei.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hix5hd2-i2c");
