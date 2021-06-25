<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 NXP Semiconductors
 *
 * Code portions referenced from the i2x-pxa and i2c-pnx drivers
 *
 * Make SMBus byte and word transactions work on LPC178x/7x
 * Copyright (c) 2012
 * Alexander Potashev, Emcraft Systems, aspotashev@emcraft.com
 * Anton Protopopov, Emcraft Systems, antonp@emcraft.com
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>

/* LPC24xx रेजिस्टर offsets and bits */
#घोषणा LPC24XX_I2CONSET	0x00
#घोषणा LPC24XX_I2STAT		0x04
#घोषणा LPC24XX_I2DAT		0x08
#घोषणा LPC24XX_I2ADDR		0x0c
#घोषणा LPC24XX_I2SCLH		0x10
#घोषणा LPC24XX_I2SCLL		0x14
#घोषणा LPC24XX_I2CONCLR	0x18

#घोषणा LPC24XX_AA		BIT(2)
#घोषणा LPC24XX_SI		BIT(3)
#घोषणा LPC24XX_STO		BIT(4)
#घोषणा LPC24XX_STA		BIT(5)
#घोषणा LPC24XX_I2EN		BIT(6)

#घोषणा LPC24XX_STO_AA		(LPC24XX_STO | LPC24XX_AA)
#घोषणा LPC24XX_CLEAR_ALL	(LPC24XX_AA | LPC24XX_SI | LPC24XX_STO | \
				 LPC24XX_STA | LPC24XX_I2EN)

/* I2C SCL घड़ी has dअगरferent duty cycle depending on mode */
#घोषणा I2C_STD_MODE_DUTY		46
#घोषणा I2C_FAST_MODE_DUTY		36
#घोषणा I2C_FAST_MODE_PLUS_DUTY		38

/*
 * 26 possible I2C status codes, but codes applicable only
 * to master are listed here and used in this driver
 */
क्रमागत अणु
	M_BUS_ERROR		= 0x00,
	M_START			= 0x08,
	M_REPSTART		= 0x10,
	MX_ADDR_W_ACK		= 0x18,
	MX_ADDR_W_NACK		= 0x20,
	MX_DATA_W_ACK		= 0x28,
	MX_DATA_W_NACK		= 0x30,
	M_DATA_ARB_LOST		= 0x38,
	MR_ADDR_R_ACK		= 0x40,
	MR_ADDR_R_NACK		= 0x48,
	MR_DATA_R_ACK		= 0x50,
	MR_DATA_R_NACK		= 0x58,
	M_I2C_IDLE		= 0xf8,
पूर्ण;

काष्ठा lpc2k_i2c अणु
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	पूर्णांक			irq;
	रुको_queue_head_t	रुको;
	काष्ठा i2c_adapter	adap;
	काष्ठा i2c_msg		*msg;
	पूर्णांक			msg_idx;
	पूर्णांक			msg_status;
	पूर्णांक			is_last;
पूर्ण;

अटल व्योम i2c_lpc2k_reset(काष्ठा lpc2k_i2c *i2c)
अणु
	/* Will क्रमce clear all statuses */
	ग_लिखोl(LPC24XX_CLEAR_ALL, i2c->base + LPC24XX_I2CONCLR);
	ग_लिखोl(0, i2c->base + LPC24XX_I2ADDR);
	ग_लिखोl(LPC24XX_I2EN, i2c->base + LPC24XX_I2CONSET);
पूर्ण

अटल पूर्णांक i2c_lpc2k_clear_arb(काष्ठा lpc2k_i2c *i2c)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	/*
	 * If the transfer needs to पात क्रम some reason, we'll try to
	 * क्रमce a stop condition to clear any pending bus conditions
	 */
	ग_लिखोl(LPC24XX_STO, i2c->base + LPC24XX_I2CONSET);

	/* Wait क्रम status change */
	जबतक (पढ़ोl(i2c->base + LPC24XX_I2STAT) != M_I2C_IDLE) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			/* Bus was not idle, try to reset adapter */
			i2c_lpc2k_reset(i2c);
			वापस -EBUSY;
		पूर्ण

		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i2c_lpc2k_pump_msg(काष्ठा lpc2k_i2c *i2c)
अणु
	अचिन्हित अक्षर data;
	u32 status;

	/*
	 * I2C in the LPC2xxx series is basically a state machine.
	 * Just run through the steps based on the current status.
	 */
	status = पढ़ोl(i2c->base + LPC24XX_I2STAT);

	चयन (status) अणु
	हाल M_START:
	हाल M_REPSTART:
		/* Start bit was just sent out, send out addr and dir */
		data = i2c_8bit_addr_from_msg(i2c->msg);

		ग_लिखोl(data, i2c->base + LPC24XX_I2DAT);
		ग_लिखोl(LPC24XX_STA, i2c->base + LPC24XX_I2CONCLR);
		अवरोध;

	हाल MX_ADDR_W_ACK:
	हाल MX_DATA_W_ACK:
		/*
		 * Address or data was sent out with an ACK. If there is more
		 * data to send, send it now
		 */
		अगर (i2c->msg_idx < i2c->msg->len) अणु
			ग_लिखोl(i2c->msg->buf[i2c->msg_idx],
			       i2c->base + LPC24XX_I2DAT);
		पूर्ण अन्यथा अगर (i2c->is_last) अणु
			/* Last message, send stop */
			ग_लिखोl(LPC24XX_STO_AA, i2c->base + LPC24XX_I2CONSET);
			ग_लिखोl(LPC24XX_SI, i2c->base + LPC24XX_I2CONCLR);
			i2c->msg_status = 0;
			disable_irq_nosync(i2c->irq);
		पूर्ण अन्यथा अणु
			i2c->msg_status = 0;
			disable_irq_nosync(i2c->irq);
		पूर्ण

		i2c->msg_idx++;
		अवरोध;

	हाल MR_ADDR_R_ACK:
		/* Receive first byte from slave */
		अगर (i2c->msg->len == 1) अणु
			/* Last byte, वापस NACK */
			ग_लिखोl(LPC24XX_AA, i2c->base + LPC24XX_I2CONCLR);
		पूर्ण अन्यथा अणु
			/* Not last byte, वापस ACK */
			ग_लिखोl(LPC24XX_AA, i2c->base + LPC24XX_I2CONSET);
		पूर्ण

		ग_लिखोl(LPC24XX_STA, i2c->base + LPC24XX_I2CONCLR);
		अवरोध;

	हाल MR_DATA_R_NACK:
		/*
		 * The I2C shows NACK status on पढ़ोs, so we need to accept
		 * the NACK as an ACK here. This should be ok, as the real
		 * BACK would of been caught on the address ग_लिखो.
		 */
	हाल MR_DATA_R_ACK:
		/* Data was received */
		अगर (i2c->msg_idx < i2c->msg->len) अणु
			i2c->msg->buf[i2c->msg_idx] =
					पढ़ोl(i2c->base + LPC24XX_I2DAT);
		पूर्ण

		/* If transfer is करोne, send STOP */
		अगर (i2c->msg_idx >= i2c->msg->len - 1 && i2c->is_last) अणु
			ग_लिखोl(LPC24XX_STO_AA, i2c->base + LPC24XX_I2CONSET);
			ग_लिखोl(LPC24XX_SI, i2c->base + LPC24XX_I2CONCLR);
			i2c->msg_status = 0;
		पूर्ण

		/* Message is करोne */
		अगर (i2c->msg_idx >= i2c->msg->len - 1) अणु
			i2c->msg_status = 0;
			disable_irq_nosync(i2c->irq);
		पूर्ण

		/*
		 * One pre-last data input, send NACK to tell the slave that
		 * this is going to be the last data byte to be transferred.
		 */
		अगर (i2c->msg_idx >= i2c->msg->len - 2) अणु
			/* One byte left to receive - NACK */
			ग_लिखोl(LPC24XX_AA, i2c->base + LPC24XX_I2CONCLR);
		पूर्ण अन्यथा अणु
			/* More than one byte left to receive - ACK */
			ग_लिखोl(LPC24XX_AA, i2c->base + LPC24XX_I2CONSET);
		पूर्ण

		ग_लिखोl(LPC24XX_STA, i2c->base + LPC24XX_I2CONCLR);
		i2c->msg_idx++;
		अवरोध;

	हाल MX_ADDR_W_NACK:
	हाल MX_DATA_W_NACK:
	हाल MR_ADDR_R_NACK:
		/* NACK processing is करोne */
		ग_लिखोl(LPC24XX_STO_AA, i2c->base + LPC24XX_I2CONSET);
		i2c->msg_status = -ENXIO;
		disable_irq_nosync(i2c->irq);
		अवरोध;

	हाल M_DATA_ARB_LOST:
		/* Arbitration lost */
		i2c->msg_status = -EAGAIN;

		/* Release the I2C bus */
		ग_लिखोl(LPC24XX_STA | LPC24XX_STO, i2c->base + LPC24XX_I2CONCLR);
		disable_irq_nosync(i2c->irq);
		अवरोध;

	शेष:
		/* Unexpected statuses */
		i2c->msg_status = -EIO;
		disable_irq_nosync(i2c->irq);
		अवरोध;
	पूर्ण

	/* Exit on failure or all bytes transferred */
	अगर (i2c->msg_status != -EBUSY)
		wake_up(&i2c->रुको);

	/*
	 * If `msg_status` is zero, then `lpc2k_process_msg()`
	 * is responsible क्रम clearing the SI flag.
	 */
	अगर (i2c->msg_status != 0)
		ग_लिखोl(LPC24XX_SI, i2c->base + LPC24XX_I2CONCLR);
पूर्ण

अटल पूर्णांक lpc2k_process_msg(काष्ठा lpc2k_i2c *i2c, पूर्णांक msgidx)
अणु
	/* A new transfer is kicked off by initiating a start condition */
	अगर (!msgidx) अणु
		ग_लिखोl(LPC24XX_STA, i2c->base + LPC24XX_I2CONSET);
	पूर्ण अन्यथा अणु
		/*
		 * A multi-message I2C transfer जारीs where the
		 * previous I2C transfer left off and uses the
		 * current condition of the I2C adapter.
		 */
		अगर (unlikely(i2c->msg->flags & I2C_M_NOSTART)) अणु
			WARN_ON(i2c->msg->len == 0);

			अगर (!(i2c->msg->flags & I2C_M_RD)) अणु
				/* Start transmit of data */
				ग_लिखोl(i2c->msg->buf[0],
				       i2c->base + LPC24XX_I2DAT);
				i2c->msg_idx++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Start or repeated start */
			ग_लिखोl(LPC24XX_STA, i2c->base + LPC24XX_I2CONSET);
		पूर्ण

		ग_लिखोl(LPC24XX_SI, i2c->base + LPC24XX_I2CONCLR);
	पूर्ण

	enable_irq(i2c->irq);

	/* Wait क्रम transfer completion */
	अगर (रुको_event_समयout(i2c->रुको, i2c->msg_status != -EBUSY,
			       msecs_to_jअगरfies(1000)) == 0) अणु
		disable_irq_nosync(i2c->irq);

		वापस -ETIMEDOUT;
	पूर्ण

	वापस i2c->msg_status;
पूर्ण

अटल पूर्णांक i2c_lpc2k_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			  पूर्णांक msg_num)
अणु
	काष्ठा lpc2k_i2c *i2c = i2c_get_adapdata(adap);
	पूर्णांक ret, i;
	u32 stat;

	/* Check क्रम bus idle condition */
	stat = पढ़ोl(i2c->base + LPC24XX_I2STAT);
	अगर (stat != M_I2C_IDLE) अणु
		/* Something is holding the bus, try to clear it */
		वापस i2c_lpc2k_clear_arb(i2c);
	पूर्ण

	/* Process a single message at a समय */
	क्रम (i = 0; i < msg_num; i++) अणु
		/* Save message poपूर्णांकer and current message data index */
		i2c->msg = &msgs[i];
		i2c->msg_idx = 0;
		i2c->msg_status = -EBUSY;
		i2c->is_last = (i == (msg_num - 1));

		ret = lpc2k_process_msg(i2c, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस msg_num;
पूर्ण

अटल irqवापस_t i2c_lpc2k_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpc2k_i2c *i2c = dev_id;

	अगर (पढ़ोl(i2c->base + LPC24XX_I2CONSET) & LPC24XX_SI) अणु
		i2c_lpc2k_pump_msg(i2c);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल u32 i2c_lpc2k_functionality(काष्ठा i2c_adapter *adap)
अणु
	/* Only emulated SMBus क्रम now */
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_lpc2k_algorithm = अणु
	.master_xfer	= i2c_lpc2k_xfer,
	.functionality	= i2c_lpc2k_functionality,
पूर्ण;

अटल पूर्णांक i2c_lpc2k_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc2k_i2c *i2c;
	u32 bus_clk_rate;
	u32 scl_high;
	u32 clkrate;
	पूर्णांक ret;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	i2c->irq = platक्रमm_get_irq(pdev, 0);
	अगर (i2c->irq < 0)
		वापस i2c->irq;

	init_रुकोqueue_head(&i2c->रुको);

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c->clk)) अणु
		dev_err(&pdev->dev, "error getting clock\n");
		वापस PTR_ERR(i2c->clk);
	पूर्ण

	ret = clk_prepare_enable(i2c->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable clock.\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, i2c->irq, i2c_lpc2k_handler, 0,
			       dev_name(&pdev->dev), i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can't request interrupt.\n");
		जाओ fail_clk;
	पूर्ण

	disable_irq_nosync(i2c->irq);

	/* Place controller is a known state */
	i2c_lpc2k_reset(i2c);

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				   &bus_clk_rate);
	अगर (ret)
		bus_clk_rate = I2C_MAX_STANDARD_MODE_FREQ;

	clkrate = clk_get_rate(i2c->clk);
	अगर (clkrate == 0) अणु
		dev_err(&pdev->dev, "can't get I2C base clock\n");
		ret = -EINVAL;
		जाओ fail_clk;
	पूर्ण

	/* Setup I2C भागiders to generate घड़ी with proper duty cycle */
	clkrate = clkrate / bus_clk_rate;
	अगर (bus_clk_rate <= I2C_MAX_STANDARD_MODE_FREQ)
		scl_high = (clkrate * I2C_STD_MODE_DUTY) / 100;
	अन्यथा अगर (bus_clk_rate <= I2C_MAX_FAST_MODE_FREQ)
		scl_high = (clkrate * I2C_FAST_MODE_DUTY) / 100;
	अन्यथा
		scl_high = (clkrate * I2C_FAST_MODE_PLUS_DUTY) / 100;

	ग_लिखोl(scl_high, i2c->base + LPC24XX_I2SCLH);
	ग_लिखोl(clkrate - scl_high, i2c->base + LPC24XX_I2SCLL);

	platक्रमm_set_drvdata(pdev, i2c);

	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.owner = THIS_MODULE;
	strlcpy(i2c->adap.name, "LPC2K I2C adapter", माप(i2c->adap.name));
	i2c->adap.algo = &i2c_lpc2k_algorithm;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret < 0)
		जाओ fail_clk;

	dev_info(&pdev->dev, "LPC2K I2C adapter\n");

	वापस 0;

fail_clk:
	clk_disable_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_lpc2k_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा lpc2k_i2c *i2c = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&i2c->adap);
	clk_disable_unprepare(i2c->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2c_lpc2k_suspend(काष्ठा device *dev)
अणु
	काष्ठा lpc2k_i2c *i2c = dev_get_drvdata(dev);

	clk_disable(i2c->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_lpc2k_resume(काष्ठा device *dev)
अणु
	काष्ठा lpc2k_i2c *i2c = dev_get_drvdata(dev);

	clk_enable(i2c->clk);
	i2c_lpc2k_reset(i2c);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops i2c_lpc2k_dev_pm_ops = अणु
	.suspend_noirq = i2c_lpc2k_suspend,
	.resume_noirq = i2c_lpc2k_resume,
पूर्ण;

#घोषणा I2C_LPC2K_DEV_PM_OPS (&i2c_lpc2k_dev_pm_ops)
#अन्यथा
#घोषणा I2C_LPC2K_DEV_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id lpc2k_i2c_match[] = अणु
	अणु .compatible = "nxp,lpc1788-i2c" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc2k_i2c_match);

अटल काष्ठा platक्रमm_driver i2c_lpc2k_driver = अणु
	.probe	= i2c_lpc2k_probe,
	.हटाओ	= i2c_lpc2k_हटाओ,
	.driver	= अणु
		.name		= "lpc2k-i2c",
		.pm		= I2C_LPC2K_DEV_PM_OPS,
		.of_match_table	= lpc2k_i2c_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(i2c_lpc2k_driver);

MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_DESCRIPTION("I2C driver for LPC2xxx devices");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lpc2k-i2c");
