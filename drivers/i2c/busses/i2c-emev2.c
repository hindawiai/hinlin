<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I2C driver क्रम the Renesas EMEV2 SoC
 *
 * Copyright (C) 2015 Wolfram Sang <wsa@sang-engineering.com>
 * Copyright 2013 Codethink Ltd.
 * Copyright 2010-2015 Renesas Electronics Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>

/* I2C Registers */
#घोषणा I2C_OFS_IICACT0		0x00	/* start */
#घोषणा I2C_OFS_IIC0		0x04	/* shअगरt */
#घोषणा I2C_OFS_IICC0		0x08	/* control */
#घोषणा I2C_OFS_SVA0		0x0c	/* slave address */
#घोषणा I2C_OFS_IICCL0		0x10	/* घड़ी select */
#घोषणा I2C_OFS_IICX0		0x14	/* extension */
#घोषणा I2C_OFS_IICS0		0x18	/* status */
#घोषणा I2C_OFS_IICSE0		0x1c	/* status For emulation */
#घोषणा I2C_OFS_IICF0		0x20	/* IIC flag */

/* I2C IICACT0 Masks */
#घोषणा I2C_BIT_IICE0		0x0001

/* I2C IICC0 Masks */
#घोषणा I2C_BIT_LREL0		0x0040
#घोषणा I2C_BIT_WREL0		0x0020
#घोषणा I2C_BIT_SPIE0		0x0010
#घोषणा I2C_BIT_WTIM0		0x0008
#घोषणा I2C_BIT_ACKE0		0x0004
#घोषणा I2C_BIT_STT0		0x0002
#घोषणा I2C_BIT_SPT0		0x0001

/* I2C IICCL0 Masks */
#घोषणा I2C_BIT_SMC0		0x0008
#घोषणा I2C_BIT_DFC0		0x0004

/* I2C IICSE0 Masks */
#घोषणा I2C_BIT_MSTS0		0x0080
#घोषणा I2C_BIT_ALD0		0x0040
#घोषणा I2C_BIT_EXC0		0x0020
#घोषणा I2C_BIT_COI0		0x0010
#घोषणा I2C_BIT_TRC0		0x0008
#घोषणा I2C_BIT_ACKD0		0x0004
#घोषणा I2C_BIT_STD0		0x0002
#घोषणा I2C_BIT_SPD0		0x0001

/* I2C IICF0 Masks */
#घोषणा I2C_BIT_STCF		0x0080
#घोषणा I2C_BIT_IICBSY		0x0040
#घोषणा I2C_BIT_STCEN		0x0002
#घोषणा I2C_BIT_IICRSV		0x0001

काष्ठा em_i2c_device अणु
	व्योम __iomem *base;
	काष्ठा i2c_adapter adap;
	काष्ठा completion msg_करोne;
	काष्ठा clk *sclk;
	काष्ठा i2c_client *slave;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत व्योम em_clear_set_bit(काष्ठा em_i2c_device *priv, u8 clear, u8 set, u8 reg)
अणु
	ग_लिखोb((पढ़ोb(priv->base + reg) & ~clear) | set, priv->base + reg);
पूर्ण

अटल पूर्णांक em_i2c_रुको_क्रम_event(काष्ठा em_i2c_device *priv)
अणु
	अचिन्हित दीर्घ समय_left;
	पूर्णांक status;

	reinit_completion(&priv->msg_करोne);

	समय_left = रुको_क्रम_completion_समयout(&priv->msg_करोne, priv->adap.समयout);

	अगर (!समय_left)
		वापस -ETIMEDOUT;

	status = पढ़ोb(priv->base + I2C_OFS_IICSE0);
	वापस status & I2C_BIT_ALD0 ? -EAGAIN : status;
पूर्ण

अटल व्योम em_i2c_stop(काष्ठा em_i2c_device *priv)
अणु
	/* Send Stop condition */
	em_clear_set_bit(priv, 0, I2C_BIT_SPT0 | I2C_BIT_SPIE0, I2C_OFS_IICC0);

	/* Wait क्रम stop condition */
	em_i2c_रुको_क्रम_event(priv);
पूर्ण

अटल व्योम em_i2c_reset(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा em_i2c_device *priv = i2c_get_adapdata(adap);
	पूर्णांक retr;

	/* If I2C active */
	अगर (पढ़ोb(priv->base + I2C_OFS_IICACT0) & I2C_BIT_IICE0) अणु
		/* Disable I2C operation */
		ग_लिखोb(0, priv->base + I2C_OFS_IICACT0);

		retr = 1000;
		जबतक (पढ़ोb(priv->base + I2C_OFS_IICACT0) == 1 && retr)
			retr--;
		WARN_ON(retr == 0);
	पूर्ण

	/* Transfer mode set */
	ग_लिखोb(I2C_BIT_DFC0, priv->base + I2C_OFS_IICCL0);

	/* Can Issue start without detecting a stop, Reservation disabled. */
	ग_लिखोb(I2C_BIT_STCEN | I2C_BIT_IICRSV, priv->base + I2C_OFS_IICF0);

	/* I2C enable, 9 bit पूर्णांकerrupt mode */
	ग_लिखोb(I2C_BIT_WTIM0, priv->base + I2C_OFS_IICC0);

	/* Enable I2C operation */
	ग_लिखोb(I2C_BIT_IICE0, priv->base + I2C_OFS_IICACT0);

	retr = 1000;
	जबतक (पढ़ोb(priv->base + I2C_OFS_IICACT0) == 0 && retr)
		retr--;
	WARN_ON(retr == 0);
पूर्ण

अटल पूर्णांक __em_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
				पूर्णांक stop)
अणु
	काष्ठा em_i2c_device *priv = i2c_get_adapdata(adap);
	पूर्णांक count, status, पढ़ो = !!(msg->flags & I2C_M_RD);

	/* Send start condition */
	em_clear_set_bit(priv, 0, I2C_BIT_ACKE0 | I2C_BIT_WTIM0, I2C_OFS_IICC0);
	em_clear_set_bit(priv, 0, I2C_BIT_STT0, I2C_OFS_IICC0);

	/* Send slave address and R/W type */
	ग_लिखोb(i2c_8bit_addr_from_msg(msg), priv->base + I2C_OFS_IIC0);

	/* Wait क्रम transaction */
	status = em_i2c_रुको_क्रम_event(priv);
	अगर (status < 0)
		जाओ out_reset;

	/* Received NACK (result of setting slave address and R/W) */
	अगर (!(status & I2C_BIT_ACKD0)) अणु
		em_i2c_stop(priv);
		जाओ out;
	पूर्ण

	/* Extra setup क्रम पढ़ो transactions */
	अगर (पढ़ो) अणु
		/* 8 bit पूर्णांकerrupt mode */
		em_clear_set_bit(priv, I2C_BIT_WTIM0, I2C_BIT_ACKE0, I2C_OFS_IICC0);
		em_clear_set_bit(priv, I2C_BIT_WTIM0, I2C_BIT_WREL0, I2C_OFS_IICC0);

		/* Wait क्रम transaction */
		status = em_i2c_रुको_क्रम_event(priv);
		अगर (status < 0)
			जाओ out_reset;
	पूर्ण

	/* Send / receive data */
	क्रम (count = 0; count < msg->len; count++) अणु
		अगर (पढ़ो) अणु /* Read transaction */
			msg->buf[count] = पढ़ोb(priv->base + I2C_OFS_IIC0);
			em_clear_set_bit(priv, 0, I2C_BIT_WREL0, I2C_OFS_IICC0);

		पूर्ण अन्यथा अणु /* Write transaction */
			/* Received NACK */
			अगर (!(status & I2C_BIT_ACKD0)) अणु
				em_i2c_stop(priv);
				जाओ out;
			पूर्ण

			/* Write data */
			ग_लिखोb(msg->buf[count], priv->base + I2C_OFS_IIC0);
		पूर्ण

		/* Wait क्रम R/W transaction */
		status = em_i2c_रुको_क्रम_event(priv);
		अगर (status < 0)
			जाओ out_reset;
	पूर्ण

	अगर (stop)
		em_i2c_stop(priv);

	वापस count;

out_reset:
	em_i2c_reset(adap);
out:
	वापस status < 0 ? status : -ENXIO;
पूर्ण

अटल पूर्णांक em_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
	पूर्णांक num)
अणु
	काष्ठा em_i2c_device *priv = i2c_get_adapdata(adap);
	पूर्णांक ret, i;

	अगर (पढ़ोb(priv->base + I2C_OFS_IICF0) & I2C_BIT_IICBSY)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		ret = __em_i2c_xfer(adap, &msgs[i], (i == (num - 1)));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* I2C transfer completed */
	वापस num;
पूर्ण

अटल bool em_i2c_slave_irq(काष्ठा em_i2c_device *priv)
अणु
	u8 status, value;
	क्रमागत i2c_slave_event event;
	पूर्णांक ret;

	अगर (!priv->slave)
		वापस false;

	status = पढ़ोb(priv->base + I2C_OFS_IICSE0);

	/* Extension code, करो not participate */
	अगर (status & I2C_BIT_EXC0) अणु
		em_clear_set_bit(priv, 0, I2C_BIT_LREL0, I2C_OFS_IICC0);
		वापस true;
	पूर्ण

	/* Stop detected, we करोn't know if it's क्रम slave or master */
	अगर (status & I2C_BIT_SPD0) अणु
		/* Notअगरy slave device */
		i2c_slave_event(priv->slave, I2C_SLAVE_STOP, &value);
		/* Pretend we did not handle the पूर्णांकerrupt */
		वापस false;
	पूर्ण

	/* Only handle पूर्णांकerrupts addressed to us */
	अगर (!(status & I2C_BIT_COI0))
		वापस false;

	/* Enable stop पूर्णांकerrupts */
	em_clear_set_bit(priv, 0, I2C_BIT_SPIE0, I2C_OFS_IICC0);

	/* Transmission or Reception */
	अगर (status & I2C_BIT_TRC0) अणु
		अगर (status & I2C_BIT_ACKD0) अणु
			/* 9 bit पूर्णांकerrupt mode */
			em_clear_set_bit(priv, 0, I2C_BIT_WTIM0, I2C_OFS_IICC0);

			/* Send data */
			event = status & I2C_BIT_STD0 ?
				I2C_SLAVE_READ_REQUESTED :
				I2C_SLAVE_READ_PROCESSED;
			i2c_slave_event(priv->slave, event, &value);
			ग_लिखोb(value, priv->base + I2C_OFS_IIC0);
		पूर्ण अन्यथा अणु
			/* NACK, stop transmitting */
			em_clear_set_bit(priv, 0, I2C_BIT_LREL0, I2C_OFS_IICC0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 8 bit पूर्णांकerrupt mode */
		em_clear_set_bit(priv, I2C_BIT_WTIM0, I2C_BIT_ACKE0,
				I2C_OFS_IICC0);
		em_clear_set_bit(priv, I2C_BIT_WTIM0, I2C_BIT_WREL0,
				I2C_OFS_IICC0);

		अगर (status & I2C_BIT_STD0) अणु
			i2c_slave_event(priv->slave, I2C_SLAVE_WRITE_REQUESTED,
					&value);
		पूर्ण अन्यथा अणु
			/* Recv data */
			value = पढ़ोb(priv->base + I2C_OFS_IIC0);
			ret = i2c_slave_event(priv->slave,
					I2C_SLAVE_WRITE_RECEIVED, &value);
			अगर (ret < 0)
				em_clear_set_bit(priv, I2C_BIT_ACKE0, 0,
						I2C_OFS_IICC0);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल irqवापस_t em_i2c_irq_handler(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा em_i2c_device *priv = dev_id;

	अगर (em_i2c_slave_irq(priv))
		वापस IRQ_HANDLED;

	complete(&priv->msg_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 em_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_SLAVE;
पूर्ण

अटल पूर्णांक em_i2c_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा em_i2c_device *priv = i2c_get_adapdata(slave->adapter);

	अगर (priv->slave)
		वापस -EBUSY;

	अगर (slave->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;

	priv->slave = slave;

	/* Set slave address */
	ग_लिखोb(slave->addr << 1, priv->base + I2C_OFS_SVA0);

	वापस 0;
पूर्ण

अटल पूर्णांक em_i2c_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा em_i2c_device *priv = i2c_get_adapdata(slave->adapter);

	WARN_ON(!priv->slave);

	ग_लिखोb(0, priv->base + I2C_OFS_SVA0);

	/*
	 * Wait क्रम पूर्णांकerrupt to finish. New slave irqs cannot happen because we
	 * cleared the slave address and, thus, only extension codes will be
	 * detected which करो not use the slave ptr.
	 */
	synchronize_irq(priv->irq);
	priv->slave = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm em_i2c_algo = अणु
	.master_xfer = em_i2c_xfer,
	.functionality = em_i2c_func,
	.reg_slave      = em_i2c_reg_slave,
	.unreg_slave    = em_i2c_unreg_slave,
पूर्ण;

अटल पूर्णांक em_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा em_i2c_device *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	strlcpy(priv->adap.name, "EMEV2 I2C", माप(priv->adap.name));

	priv->sclk = devm_clk_get(&pdev->dev, "sclk");
	अगर (IS_ERR(priv->sclk))
		वापस PTR_ERR(priv->sclk);

	ret = clk_prepare_enable(priv->sclk);
	अगर (ret)
		वापस ret;

	priv->adap.समयout = msecs_to_jअगरfies(100);
	priv->adap.retries = 5;
	priv->adap.dev.parent = &pdev->dev;
	priv->adap.algo = &em_i2c_algo;
	priv->adap.owner = THIS_MODULE;
	priv->adap.dev.of_node = pdev->dev.of_node;

	init_completion(&priv->msg_करोne);

	platक्रमm_set_drvdata(pdev, priv);
	i2c_set_adapdata(&priv->adap, priv);

	em_i2c_reset(&priv->adap);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_clk;
	priv->irq = ret;
	ret = devm_request_irq(&pdev->dev, priv->irq, em_i2c_irq_handler, 0,
				"em_i2c", priv);
	अगर (ret)
		जाओ err_clk;

	ret = i2c_add_adapter(&priv->adap);

	अगर (ret)
		जाओ err_clk;

	dev_info(&pdev->dev, "Added i2c controller %d, irq %d\n", priv->adap.nr,
		 priv->irq);

	वापस 0;

err_clk:
	clk_disable_unprepare(priv->sclk);
	वापस ret;
पूर्ण

अटल पूर्णांक em_i2c_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा em_i2c_device *priv = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&priv->adap);
	clk_disable_unprepare(priv->sclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id em_i2c_ids[] = अणु
	अणु .compatible = "renesas,iic-emev2", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver em_i2c_driver = अणु
	.probe = em_i2c_probe,
	.हटाओ = em_i2c_हटाओ,
	.driver = अणु
		.name = "em-i2c",
		.of_match_table = em_i2c_ids,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(em_i2c_driver);

MODULE_DESCRIPTION("EMEV2 I2C bus driver");
MODULE_AUTHOR("Ian Molton");
MODULE_AUTHOR("Wolfram Sang <wsa@sang-engineering.com>");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, em_i2c_ids);
