<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Actions Semiconductor Owl SoC's I2C driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Copyright (c) 2018 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

/* I2C रेजिस्टरs */
#घोषणा OWL_I2C_REG_CTL		0x0000
#घोषणा OWL_I2C_REG_CLKDIV	0x0004
#घोषणा OWL_I2C_REG_STAT	0x0008
#घोषणा OWL_I2C_REG_ADDR	0x000C
#घोषणा OWL_I2C_REG_TXDAT	0x0010
#घोषणा OWL_I2C_REG_RXDAT	0x0014
#घोषणा OWL_I2C_REG_CMD		0x0018
#घोषणा OWL_I2C_REG_FIFOCTL	0x001C
#घोषणा OWL_I2C_REG_FIFOSTAT	0x0020
#घोषणा OWL_I2C_REG_DATCNT	0x0024
#घोषणा OWL_I2C_REG_RCNT	0x0028

/* I2Cx_CTL Bit Mask */
#घोषणा OWL_I2C_CTL_RB		BIT(1)
#घोषणा OWL_I2C_CTL_GBCC(x)	(((x) & 0x3) << 2)
#घोषणा	OWL_I2C_CTL_GBCC_NONE	OWL_I2C_CTL_GBCC(0)
#घोषणा	OWL_I2C_CTL_GBCC_START	OWL_I2C_CTL_GBCC(1)
#घोषणा	OWL_I2C_CTL_GBCC_STOP	OWL_I2C_CTL_GBCC(2)
#घोषणा	OWL_I2C_CTL_GBCC_RSTART	OWL_I2C_CTL_GBCC(3)
#घोषणा OWL_I2C_CTL_IRQE	BIT(5)
#घोषणा OWL_I2C_CTL_EN		BIT(7)
#घोषणा OWL_I2C_CTL_AE		BIT(8)
#घोषणा OWL_I2C_CTL_SHSM	BIT(10)

#घोषणा OWL_I2C_DIV_FACTOR(x)	((x) & 0xff)

/* I2Cx_STAT Bit Mask */
#घोषणा OWL_I2C_STAT_RACK	BIT(0)
#घोषणा OWL_I2C_STAT_BEB	BIT(1)
#घोषणा OWL_I2C_STAT_IRQP	BIT(2)
#घोषणा OWL_I2C_STAT_LAB	BIT(3)
#घोषणा OWL_I2C_STAT_STPD	BIT(4)
#घोषणा OWL_I2C_STAT_STAD	BIT(5)
#घोषणा OWL_I2C_STAT_BBB	BIT(6)
#घोषणा OWL_I2C_STAT_TCB	BIT(7)
#घोषणा OWL_I2C_STAT_LBST	BIT(8)
#घोषणा OWL_I2C_STAT_SAMB	BIT(9)
#घोषणा OWL_I2C_STAT_SRGC	BIT(10)

/* I2Cx_CMD Bit Mask */
#घोषणा OWL_I2C_CMD_SBE		BIT(0)
#घोषणा OWL_I2C_CMD_RBE		BIT(4)
#घोषणा OWL_I2C_CMD_DE		BIT(8)
#घोषणा OWL_I2C_CMD_NS		BIT(9)
#घोषणा OWL_I2C_CMD_SE		BIT(10)
#घोषणा OWL_I2C_CMD_MSS		BIT(11)
#घोषणा OWL_I2C_CMD_WRS		BIT(12)
#घोषणा OWL_I2C_CMD_SECL	BIT(15)

#घोषणा OWL_I2C_CMD_AS(x)	(((x) & 0x7) << 1)
#घोषणा OWL_I2C_CMD_SAS(x)	(((x) & 0x7) << 5)

/* I2Cx_FIFOCTL Bit Mask */
#घोषणा OWL_I2C_FIFOCTL_NIB	BIT(0)
#घोषणा OWL_I2C_FIFOCTL_RFR	BIT(1)
#घोषणा OWL_I2C_FIFOCTL_TFR	BIT(2)

/* I2Cc_FIFOSTAT Bit Mask */
#घोषणा OWL_I2C_FIFOSTAT_CECB	BIT(0)
#घोषणा OWL_I2C_FIFOSTAT_RNB	BIT(1)
#घोषणा OWL_I2C_FIFOSTAT_RFE	BIT(2)
#घोषणा OWL_I2C_FIFOSTAT_TFF	BIT(5)
#घोषणा OWL_I2C_FIFOSTAT_TFD	GENMASK(23, 16)
#घोषणा OWL_I2C_FIFOSTAT_RFD	GENMASK(15, 8)

/* I2C bus समयout */
#घोषणा OWL_I2C_TIMEOUT_MS	(4 * 1000)
#घोषणा OWL_I2C_TIMEOUT		msecs_to_jअगरfies(OWL_I2C_TIMEOUT_MS)

#घोषणा OWL_I2C_MAX_RETRIES	50

काष्ठा owl_i2c_dev अणु
	काष्ठा i2c_adapter	adap;
	काष्ठा i2c_msg		*msg;
	काष्ठा completion	msg_complete;
	काष्ठा clk		*clk;
	spinlock_t		lock;
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		clk_rate;
	u32			bus_freq;
	u32			msg_ptr;
	पूर्णांक			err;
पूर्ण;

अटल व्योम owl_i2c_update_reg(व्योम __iomem *reg, अचिन्हित पूर्णांक val, bool state)
अणु
	अचिन्हित पूर्णांक regval;

	regval = पढ़ोl(reg);

	अगर (state)
		regval |= val;
	अन्यथा
		regval &= ~val;

	ग_लिखोl(regval, reg);
पूर्ण

अटल व्योम owl_i2c_reset(काष्ठा owl_i2c_dev *i2c_dev)
अणु
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_EN, false);
	mdelay(1);
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_EN, true);

	/* Clear status रेजिस्टरs */
	ग_लिखोl(0, i2c_dev->base + OWL_I2C_REG_STAT);
पूर्ण

अटल पूर्णांक owl_i2c_reset_fअगरo(काष्ठा owl_i2c_dev *i2c_dev)
अणु
	अचिन्हित पूर्णांक val, समयout = 0;

	/* Reset FIFO */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOCTL,
			   OWL_I2C_FIFOCTL_RFR | OWL_I2C_FIFOCTL_TFR,
			   true);

	/* Wait 50ms क्रम FIFO reset complete */
	करो अणु
		val = पढ़ोl(i2c_dev->base + OWL_I2C_REG_FIFOCTL);
		अगर (!(val & (OWL_I2C_FIFOCTL_RFR | OWL_I2C_FIFOCTL_TFR)))
			अवरोध;
		usleep_range(500, 1000);
	पूर्ण जबतक (समयout++ < OWL_I2C_MAX_RETRIES);

	अगर (समयout > OWL_I2C_MAX_RETRIES) अणु
		dev_err(&i2c_dev->adap.dev, "FIFO reset timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम owl_i2c_set_freq(काष्ठा owl_i2c_dev *i2c_dev)
अणु
	अचिन्हित पूर्णांक val;

	val = DIV_ROUND_UP(i2c_dev->clk_rate, i2c_dev->bus_freq * 16);

	/* Set घड़ी भागider factor */
	ग_लिखोl(OWL_I2C_DIV_FACTOR(val), i2c_dev->base + OWL_I2C_REG_CLKDIV);
पूर्ण

अटल व्योम owl_i2c_xfer_data(काष्ठा owl_i2c_dev *i2c_dev)
अणु
	काष्ठा i2c_msg *msg = i2c_dev->msg;
	अचिन्हित पूर्णांक stat, fअगरostat;

	i2c_dev->err = 0;

	/* Handle NACK from slave */
	fअगरostat = पढ़ोl(i2c_dev->base + OWL_I2C_REG_FIFOSTAT);
	अगर (fअगरostat & OWL_I2C_FIFOSTAT_RNB) अणु
		i2c_dev->err = -ENXIO;
		/* Clear NACK error bit by writing "1" */
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOSTAT,
				   OWL_I2C_FIFOSTAT_RNB, true);
		वापस;
	पूर्ण

	/* Handle bus error */
	stat = पढ़ोl(i2c_dev->base + OWL_I2C_REG_STAT);
	अगर (stat & OWL_I2C_STAT_BEB) अणु
		i2c_dev->err = -EIO;
		/* Clear BUS error bit by writing "1" */
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_STAT,
				   OWL_I2C_STAT_BEB, true);
		वापस;
	पूर्ण

	/* Handle FIFO पढ़ो */
	अगर (msg->flags & I2C_M_RD) अणु
		जबतक ((पढ़ोl(i2c_dev->base + OWL_I2C_REG_FIFOSTAT) &
			OWL_I2C_FIFOSTAT_RFE) && i2c_dev->msg_ptr < msg->len) अणु
			msg->buf[i2c_dev->msg_ptr++] = पढ़ोl(i2c_dev->base +
							     OWL_I2C_REG_RXDAT);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Handle the reमुख्यing bytes which were not sent */
		जबतक (!(पढ़ोl(i2c_dev->base + OWL_I2C_REG_FIFOSTAT) &
			 OWL_I2C_FIFOSTAT_TFF) && i2c_dev->msg_ptr < msg->len) अणु
			ग_लिखोl(msg->buf[i2c_dev->msg_ptr++],
			       i2c_dev->base + OWL_I2C_REG_TXDAT);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t owl_i2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा owl_i2c_dev *i2c_dev = _dev;

	spin_lock(&i2c_dev->lock);

	owl_i2c_xfer_data(i2c_dev);

	/* Clear pending पूर्णांकerrupts */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_STAT,
			   OWL_I2C_STAT_IRQP, true);

	complete_all(&i2c_dev->msg_complete);
	spin_unlock(&i2c_dev->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 owl_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल पूर्णांक owl_i2c_check_bus_busy(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा owl_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ समयout;

	/* Check क्रम Bus busy */
	समयout = jअगरfies + OWL_I2C_TIMEOUT;
	जबतक (पढ़ोl(i2c_dev->base + OWL_I2C_REG_STAT) & OWL_I2C_STAT_BBB) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&adap->dev, "Bus busy timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक owl_i2c_xfer_common(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			       पूर्णांक num, bool atomic)
अणु
	काष्ठा owl_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	काष्ठा i2c_msg *msg;
	अचिन्हित दीर्घ समय_left, flags;
	अचिन्हित पूर्णांक i2c_cmd, val;
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret, idx;

	spin_lock_irqsave(&i2c_dev->lock, flags);

	/* Reset I2C controller */
	owl_i2c_reset(i2c_dev);

	/* Set bus frequency */
	owl_i2c_set_freq(i2c_dev);

	/*
	 * Spinlock should be released beक्रमe calling reset FIFO and
	 * bus busy check since those functions may sleep
	 */
	spin_unlock_irqrestore(&i2c_dev->lock, flags);

	/* Reset FIFO */
	ret = owl_i2c_reset_fअगरo(i2c_dev);
	अगर (ret)
		जाओ unlocked_err_निकास;

	/* Check क्रम bus busy */
	ret = owl_i2c_check_bus_busy(adap);
	अगर (ret)
		जाओ unlocked_err_निकास;

	spin_lock_irqsave(&i2c_dev->lock, flags);

	/* Check क्रम Arbitration lost */
	val = पढ़ोl(i2c_dev->base + OWL_I2C_REG_STAT);
	अगर (val & OWL_I2C_STAT_LAB) अणु
		val &= ~OWL_I2C_STAT_LAB;
		ग_लिखोl(val, i2c_dev->base + OWL_I2C_REG_STAT);
		ret = -EAGAIN;
		जाओ err_निकास;
	पूर्ण

	अगर (!atomic)
		reinit_completion(&i2c_dev->msg_complete);

	/* Enable/disable I2C controller पूर्णांकerrupt */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_IRQE, !atomic);

	/*
	 * Select: FIFO enable, Master mode, Stop enable, Data count enable,
	 * Send start bit
	 */
	i2c_cmd = OWL_I2C_CMD_SECL | OWL_I2C_CMD_MSS | OWL_I2C_CMD_SE |
		  OWL_I2C_CMD_NS | OWL_I2C_CMD_DE | OWL_I2C_CMD_SBE;

	/* Handle repeated start condition */
	अगर (num > 1) अणु
		/* Set पूर्णांकernal address length and enable repeated start */
		i2c_cmd |= OWL_I2C_CMD_AS(msgs[0].len + 1) |
			   OWL_I2C_CMD_SAS(1) | OWL_I2C_CMD_RBE;

		/* Write slave address */
		addr = i2c_8bit_addr_from_msg(&msgs[0]);
		ग_लिखोl(addr, i2c_dev->base + OWL_I2C_REG_TXDAT);

		/* Write पूर्णांकernal रेजिस्टर address */
		क्रम (idx = 0; idx < msgs[0].len; idx++)
			ग_लिखोl(msgs[0].buf[idx],
			       i2c_dev->base + OWL_I2C_REG_TXDAT);

		msg = &msgs[1];
	पूर्ण अन्यथा अणु
		/* Set address length */
		i2c_cmd |= OWL_I2C_CMD_AS(1);
		msg = &msgs[0];
	पूर्ण

	i2c_dev->msg = msg;
	i2c_dev->msg_ptr = 0;

	/* Set data count क्रम the message */
	ग_लिखोl(msg->len, i2c_dev->base + OWL_I2C_REG_DATCNT);

	addr = i2c_8bit_addr_from_msg(msg);
	ग_लिखोl(addr, i2c_dev->base + OWL_I2C_REG_TXDAT);

	अगर (!(msg->flags & I2C_M_RD)) अणु
		/* Write data to FIFO */
		क्रम (idx = 0; idx < msg->len; idx++) अणु
			/* Check क्रम FIFO full */
			अगर (पढ़ोl(i2c_dev->base + OWL_I2C_REG_FIFOSTAT) &
			    OWL_I2C_FIFOSTAT_TFF)
				अवरोध;

			ग_लिखोl(msg->buf[idx],
			       i2c_dev->base + OWL_I2C_REG_TXDAT);
		पूर्ण

		i2c_dev->msg_ptr = idx;
	पूर्ण

	/* Ignore the NACK अगर needed */
	अगर (msg->flags & I2C_M_IGNORE_NAK)
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOCTL,
				   OWL_I2C_FIFOCTL_NIB, true);
	अन्यथा
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOCTL,
				   OWL_I2C_FIFOCTL_NIB, false);

	/* Start the transfer */
	ग_लिखोl(i2c_cmd, i2c_dev->base + OWL_I2C_REG_CMD);

	spin_unlock_irqrestore(&i2c_dev->lock, flags);

	अगर (atomic) अणु
		/* Wait क्रम Command Execute Completed or NACK Error bits */
		ret = पढ़ोl_poll_समयout_atomic(i2c_dev->base + OWL_I2C_REG_FIFOSTAT,
						val, val & (OWL_I2C_FIFOSTAT_CECB |
							    OWL_I2C_FIFOSTAT_RNB),
						10, OWL_I2C_TIMEOUT_MS * 1000);
	पूर्ण अन्यथा अणु
		समय_left = रुको_क्रम_completion_समयout(&i2c_dev->msg_complete,
							adap->समयout);
		अगर (!समय_left)
			ret = -ETIMEDOUT;
	पूर्ण

	spin_lock_irqsave(&i2c_dev->lock, flags);

	अगर (ret) अणु
		dev_err(&adap->dev, "Transaction timed out\n");
		/* Send stop condition and release the bus */
		owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
				   OWL_I2C_CTL_GBCC_STOP | OWL_I2C_CTL_RB,
				   true);
		जाओ err_निकास;
	पूर्ण

	अगर (atomic)
		owl_i2c_xfer_data(i2c_dev);

	ret = i2c_dev->err < 0 ? i2c_dev->err : num;

err_निकास:
	spin_unlock_irqrestore(&i2c_dev->lock, flags);

unlocked_err_निकास:
	/* Disable I2C controller */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_EN, false);

	वापस ret;
पूर्ण

अटल पूर्णांक owl_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			पूर्णांक num)
अणु
	वापस owl_i2c_xfer_common(adap, msgs, num, false);
पूर्ण

अटल पूर्णांक owl_i2c_xfer_atomic(काष्ठा i2c_adapter *adap,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस owl_i2c_xfer_common(adap, msgs, num, true);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm owl_i2c_algorithm = अणु
	.master_xfer	     = owl_i2c_xfer,
	.master_xfer_atomic  = owl_i2c_xfer_atomic,
	.functionality	     = owl_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks owl_i2c_quirks = अणु
	.flags		= I2C_AQ_COMB | I2C_AQ_COMB_WRITE_FIRST,
	.max_पढ़ो_len   = 240,
	.max_ग_लिखो_len  = 240,
	.max_comb_1st_msg_len = 6,
	.max_comb_2nd_msg_len = 240,
पूर्ण;

अटल पूर्णांक owl_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा owl_i2c_dev *i2c_dev;
	पूर्णांक ret, irq;

	i2c_dev = devm_kzalloc(dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	i2c_dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	अगर (of_property_पढ़ो_u32(dev->of_node, "clock-frequency",
				 &i2c_dev->bus_freq))
		i2c_dev->bus_freq = I2C_MAX_STANDARD_MODE_FREQ;

	/* We support only frequencies of 100k and 400k क्रम now */
	अगर (i2c_dev->bus_freq != I2C_MAX_STANDARD_MODE_FREQ &&
	    i2c_dev->bus_freq != I2C_MAX_FAST_MODE_FREQ) अणु
		dev_err(dev, "invalid clock-frequency %d\n", i2c_dev->bus_freq);
		वापस -EINVAL;
	पूर्ण

	i2c_dev->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(i2c_dev->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(i2c_dev->clk);
	पूर्ण

	ret = clk_prepare_enable(i2c_dev->clk);
	अगर (ret)
		वापस ret;

	i2c_dev->clk_rate = clk_get_rate(i2c_dev->clk);
	अगर (!i2c_dev->clk_rate) अणु
		dev_err(dev, "input clock rate should not be zero\n");
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	init_completion(&i2c_dev->msg_complete);
	spin_lock_init(&i2c_dev->lock);
	i2c_dev->adap.owner = THIS_MODULE;
	i2c_dev->adap.algo = &owl_i2c_algorithm;
	i2c_dev->adap.समयout = OWL_I2C_TIMEOUT;
	i2c_dev->adap.quirks = &owl_i2c_quirks;
	i2c_dev->adap.dev.parent = dev;
	i2c_dev->adap.dev.of_node = dev->of_node;
	snम_लिखो(i2c_dev->adap.name, माप(i2c_dev->adap.name),
		 "%s", "OWL I2C adapter");
	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);

	platक्रमm_set_drvdata(pdev, i2c_dev);

	ret = devm_request_irq(dev, irq, owl_i2c_पूर्णांकerrupt, 0, pdev->name,
			       i2c_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq %d\n", irq);
		जाओ disable_clk;
	पूर्ण

	वापस i2c_add_adapter(&i2c_dev->adap);

disable_clk:
	clk_disable_unprepare(i2c_dev->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id owl_i2c_of_match[] = अणु
	अणु .compatible = "actions,s500-i2c" पूर्ण,
	अणु .compatible = "actions,s700-i2c" पूर्ण,
	अणु .compatible = "actions,s900-i2c" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, owl_i2c_of_match);

अटल काष्ठा platक्रमm_driver owl_i2c_driver = अणु
	.probe		= owl_i2c_probe,
	.driver		= अणु
		.name	= "owl-i2c",
		.of_match_table = of_match_ptr(owl_i2c_of_match),
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(owl_i2c_driver);

MODULE_AUTHOR("David Liu <liuwei@actions-semi.com>");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Actions Semiconductor Owl SoC's I2C driver");
MODULE_LICENSE("GPL");
