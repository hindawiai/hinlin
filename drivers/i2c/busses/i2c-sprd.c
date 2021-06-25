<शैली गुरु>
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 *
 * SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा I2C_CTL			0x00
#घोषणा I2C_ADDR_CFG		0x04
#घोषणा I2C_COUNT		0x08
#घोषणा I2C_RX			0x0c
#घोषणा I2C_TX			0x10
#घोषणा I2C_STATUS		0x14
#घोषणा I2C_HSMODE_CFG		0x18
#घोषणा I2C_VERSION		0x1c
#घोषणा ADDR_DVD0		0x20
#घोषणा ADDR_DVD1		0x24
#घोषणा ADDR_STA0_DVD		0x28
#घोषणा ADDR_RST		0x2c

/* I2C_CTL */
#घोषणा STP_EN			BIT(20)
#घोषणा FIFO_AF_LVL_MASK	GENMASK(19, 16)
#घोषणा FIFO_AF_LVL		16
#घोषणा FIFO_AE_LVL_MASK	GENMASK(15, 12)
#घोषणा FIFO_AE_LVL		12
#घोषणा I2C_DMA_EN		BIT(11)
#घोषणा FULL_INTEN		BIT(10)
#घोषणा EMPTY_INTEN		BIT(9)
#घोषणा I2C_DVD_OPT		BIT(8)
#घोषणा I2C_OUT_OPT		BIT(7)
#घोषणा I2C_TRIM_OPT		BIT(6)
#घोषणा I2C_HS_MODE		BIT(4)
#घोषणा I2C_MODE		BIT(3)
#घोषणा I2C_EN			BIT(2)
#घोषणा I2C_INT_EN		BIT(1)
#घोषणा I2C_START		BIT(0)

/* I2C_STATUS */
#घोषणा SDA_IN			BIT(21)
#घोषणा SCL_IN			BIT(20)
#घोषणा FIFO_FULL		BIT(4)
#घोषणा FIFO_EMPTY		BIT(3)
#घोषणा I2C_INT			BIT(2)
#घोषणा I2C_RX_ACK		BIT(1)
#घोषणा I2C_BUSY		BIT(0)

/* ADDR_RST */
#घोषणा I2C_RST			BIT(0)

#घोषणा I2C_FIFO_DEEP		12
#घोषणा I2C_FIFO_FULL_THLD	15
#घोषणा I2C_FIFO_EMPTY_THLD	4
#घोषणा I2C_DATA_STEP		8
#घोषणा I2C_ADDR_DVD0_CALC(high, low)	\
	((((high) & GENMASK(15, 0)) << 16) | ((low) & GENMASK(15, 0)))
#घोषणा I2C_ADDR_DVD1_CALC(high, low)	\
	(((high) & GENMASK(31, 16)) | (((low) & GENMASK(31, 16)) >> 16))

/* समयout (ms) क्रम pm runसमय स्वतःsuspend */
#घोषणा SPRD_I2C_PM_TIMEOUT	1000
/* समयout (ms) क्रम transfer message */
#घोषणा I2C_XFER_TIMEOUT	1000

/* SPRD i2c data काष्ठाure */
काष्ठा sprd_i2c अणु
	काष्ठा i2c_adapter adap;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा i2c_msg *msg;
	काष्ठा clk *clk;
	u32 src_clk;
	u32 bus_freq;
	काष्ठा completion complete;
	u8 *buf;
	u32 count;
	पूर्णांक irq;
	पूर्णांक err;
पूर्ण;

अटल व्योम sprd_i2c_set_count(काष्ठा sprd_i2c *i2c_dev, u32 count)
अणु
	ग_लिखोl(count, i2c_dev->base + I2C_COUNT);
पूर्ण

अटल व्योम sprd_i2c_send_stop(काष्ठा sprd_i2c *i2c_dev, पूर्णांक stop)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	अगर (stop)
		ग_लिखोl(पंचांगp & ~STP_EN, i2c_dev->base + I2C_CTL);
	अन्यथा
		ग_लिखोl(पंचांगp | STP_EN, i2c_dev->base + I2C_CTL);
पूर्ण

अटल व्योम sprd_i2c_clear_start(काष्ठा sprd_i2c *i2c_dev)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	ग_लिखोl(पंचांगp & ~I2C_START, i2c_dev->base + I2C_CTL);
पूर्ण

अटल व्योम sprd_i2c_clear_ack(काष्ठा sprd_i2c *i2c_dev)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_STATUS);

	ग_लिखोl(पंचांगp & ~I2C_RX_ACK, i2c_dev->base + I2C_STATUS);
पूर्ण

अटल व्योम sprd_i2c_clear_irq(काष्ठा sprd_i2c *i2c_dev)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_STATUS);

	ग_लिखोl(पंचांगp & ~I2C_INT, i2c_dev->base + I2C_STATUS);
पूर्ण

अटल व्योम sprd_i2c_reset_fअगरo(काष्ठा sprd_i2c *i2c_dev)
अणु
	ग_लिखोl(I2C_RST, i2c_dev->base + ADDR_RST);
पूर्ण

अटल व्योम sprd_i2c_set_devaddr(काष्ठा sprd_i2c *i2c_dev, काष्ठा i2c_msg *m)
अणु
	ग_लिखोl(m->addr << 1, i2c_dev->base + I2C_ADDR_CFG);
पूर्ण

अटल व्योम sprd_i2c_ग_लिखो_bytes(काष्ठा sprd_i2c *i2c_dev, u8 *buf, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोb(buf[i], i2c_dev->base + I2C_TX);
पूर्ण

अटल व्योम sprd_i2c_पढ़ो_bytes(काष्ठा sprd_i2c *i2c_dev, u8 *buf, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++)
		buf[i] = पढ़ोb(i2c_dev->base + I2C_RX);
पूर्ण

अटल व्योम sprd_i2c_set_full_thld(काष्ठा sprd_i2c *i2c_dev, u32 full_thld)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	पंचांगp &= ~FIFO_AF_LVL_MASK;
	पंचांगp |= full_thld << FIFO_AF_LVL;
	ग_लिखोl(पंचांगp, i2c_dev->base + I2C_CTL);
पूर्ण;

अटल व्योम sprd_i2c_set_empty_thld(काष्ठा sprd_i2c *i2c_dev, u32 empty_thld)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	पंचांगp &= ~FIFO_AE_LVL_MASK;
	पंचांगp |= empty_thld << FIFO_AE_LVL;
	ग_लिखोl(पंचांगp, i2c_dev->base + I2C_CTL);
पूर्ण;

अटल व्योम sprd_i2c_set_fअगरo_full_पूर्णांक(काष्ठा sprd_i2c *i2c_dev, पूर्णांक enable)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	अगर (enable)
		पंचांगp |= FULL_INTEN;
	अन्यथा
		पंचांगp &= ~FULL_INTEN;

	ग_लिखोl(पंचांगp, i2c_dev->base + I2C_CTL);
पूर्ण;

अटल व्योम sprd_i2c_set_fअगरo_empty_पूर्णांक(काष्ठा sprd_i2c *i2c_dev, पूर्णांक enable)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	अगर (enable)
		पंचांगp |= EMPTY_INTEN;
	अन्यथा
		पंचांगp &= ~EMPTY_INTEN;

	ग_लिखोl(पंचांगp, i2c_dev->base + I2C_CTL);
पूर्ण;

अटल व्योम sprd_i2c_opt_start(काष्ठा sprd_i2c *i2c_dev)
अणु
	u32 पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);

	ग_लिखोl(पंचांगp | I2C_START, i2c_dev->base + I2C_CTL);
पूर्ण

अटल व्योम sprd_i2c_opt_mode(काष्ठा sprd_i2c *i2c_dev, पूर्णांक rw)
अणु
	u32 cmd = पढ़ोl(i2c_dev->base + I2C_CTL) & ~I2C_MODE;

	ग_लिखोl(cmd | rw << 3, i2c_dev->base + I2C_CTL);
पूर्ण

अटल व्योम sprd_i2c_data_transfer(काष्ठा sprd_i2c *i2c_dev)
अणु
	u32 i2c_count = i2c_dev->count;
	u32 need_tran = i2c_count <= I2C_FIFO_DEEP ? i2c_count : I2C_FIFO_DEEP;
	काष्ठा i2c_msg *msg = i2c_dev->msg;

	अगर (msg->flags & I2C_M_RD) अणु
		sprd_i2c_पढ़ो_bytes(i2c_dev, i2c_dev->buf, I2C_FIFO_FULL_THLD);
		i2c_dev->count -= I2C_FIFO_FULL_THLD;
		i2c_dev->buf += I2C_FIFO_FULL_THLD;

		/*
		 * If the पढ़ो data count is larger than rx fअगरo full threshold,
		 * we should enable the rx fअगरo full पूर्णांकerrupt to पढ़ो data
		 * again.
		 */
		अगर (i2c_dev->count >= I2C_FIFO_FULL_THLD)
			sprd_i2c_set_fअगरo_full_पूर्णांक(i2c_dev, 1);
	पूर्ण अन्यथा अणु
		sprd_i2c_ग_लिखो_bytes(i2c_dev, i2c_dev->buf, need_tran);
		i2c_dev->buf += need_tran;
		i2c_dev->count -= need_tran;

		/*
		 * If the ग_लिखो data count is arger than tx fअगरo depth which
		 * means we can not ग_लिखो all data in one समय, then we should
		 * enable the tx fअगरo empty पूर्णांकerrupt to ग_लिखो again.
		 */
		अगर (i2c_count > I2C_FIFO_DEEP)
			sprd_i2c_set_fअगरo_empty_पूर्णांक(i2c_dev, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_i2c_handle_msg(काष्ठा i2c_adapter *i2c_adap,
			       काष्ठा i2c_msg *msg, bool is_last_msg)
अणु
	काष्ठा sprd_i2c *i2c_dev = i2c_adap->algo_data;
	अचिन्हित दीर्घ समय_left;

	i2c_dev->msg = msg;
	i2c_dev->buf = msg->buf;
	i2c_dev->count = msg->len;

	reinit_completion(&i2c_dev->complete);
	sprd_i2c_reset_fअगरo(i2c_dev);
	sprd_i2c_set_devaddr(i2c_dev, msg);
	sprd_i2c_set_count(i2c_dev, msg->len);

	अगर (msg->flags & I2C_M_RD) अणु
		sprd_i2c_opt_mode(i2c_dev, 1);
		sprd_i2c_send_stop(i2c_dev, 1);
	पूर्ण अन्यथा अणु
		sprd_i2c_opt_mode(i2c_dev, 0);
		sprd_i2c_send_stop(i2c_dev, !!is_last_msg);
	पूर्ण

	/*
	 * We should enable rx fअगरo full पूर्णांकerrupt to get data when receiving
	 * full data.
	 */
	अगर (msg->flags & I2C_M_RD)
		sprd_i2c_set_fअगरo_full_पूर्णांक(i2c_dev, 1);
	अन्यथा
		sprd_i2c_data_transfer(i2c_dev);

	sprd_i2c_opt_start(i2c_dev);

	समय_left = रुको_क्रम_completion_समयout(&i2c_dev->complete,
				msecs_to_jअगरfies(I2C_XFER_TIMEOUT));
	अगर (!समय_left)
		वापस -ETIMEDOUT;

	वापस i2c_dev->err;
पूर्ण

अटल पूर्णांक sprd_i2c_master_xfer(काष्ठा i2c_adapter *i2c_adap,
				काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा sprd_i2c *i2c_dev = i2c_adap->algo_data;
	पूर्णांक im, ret;

	ret = pm_runसमय_resume_and_get(i2c_dev->dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (im = 0; im < num - 1; im++) अणु
		ret = sprd_i2c_handle_msg(i2c_adap, &msgs[im], 0);
		अगर (ret)
			जाओ err_msg;
	पूर्ण

	ret = sprd_i2c_handle_msg(i2c_adap, &msgs[im++], 1);

err_msg:
	pm_runसमय_mark_last_busy(i2c_dev->dev);
	pm_runसमय_put_स्वतःsuspend(i2c_dev->dev);

	वापस ret < 0 ? ret : im;
पूर्ण

अटल u32 sprd_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm sprd_i2c_algo = अणु
	.master_xfer = sprd_i2c_master_xfer,
	.functionality = sprd_i2c_func,
पूर्ण;

अटल व्योम sprd_i2c_set_clk(काष्ठा sprd_i2c *i2c_dev, u32 freq)
अणु
	u32 apb_clk = i2c_dev->src_clk;
	/*
	 * From I2C databook, the prescale calculation क्रमmula:
	 * prescale = freq_i2c / (4 * freq_scl) - 1;
	 */
	u32 i2c_dvd = apb_clk / (4 * freq) - 1;
	/*
	 * From I2C databook, the high period of SCL घड़ी is recommended as
	 * 40% (2/5), and the low period of SCL घड़ी is recommended as 60%
	 * (3/5), then the क्रमmula should be:
	 * high = (prescale * 2 * 2) / 5
	 * low = (prescale * 2 * 3) / 5
	 */
	u32 high = ((i2c_dvd << 1) * 2) / 5;
	u32 low = ((i2c_dvd << 1) * 3) / 5;
	u32 भाग0 = I2C_ADDR_DVD0_CALC(high, low);
	u32 भाग1 = I2C_ADDR_DVD1_CALC(high, low);

	ग_लिखोl(भाग0, i2c_dev->base + ADDR_DVD0);
	ग_लिखोl(भाग1, i2c_dev->base + ADDR_DVD1);

	/* Start hold timing = hold समय(us) * source घड़ी */
	अगर (freq == I2C_MAX_FAST_MODE_FREQ)
		ग_लिखोl((6 * apb_clk) / 10000000, i2c_dev->base + ADDR_STA0_DVD);
	अन्यथा अगर (freq == I2C_MAX_STANDARD_MODE_FREQ)
		ग_लिखोl((4 * apb_clk) / 1000000, i2c_dev->base + ADDR_STA0_DVD);
पूर्ण

अटल व्योम sprd_i2c_enable(काष्ठा sprd_i2c *i2c_dev)
अणु
	u32 पंचांगp = I2C_DVD_OPT;

	ग_लिखोl(पंचांगp, i2c_dev->base + I2C_CTL);

	sprd_i2c_set_full_thld(i2c_dev, I2C_FIFO_FULL_THLD);
	sprd_i2c_set_empty_thld(i2c_dev, I2C_FIFO_EMPTY_THLD);

	sprd_i2c_set_clk(i2c_dev, i2c_dev->bus_freq);
	sprd_i2c_reset_fअगरo(i2c_dev);
	sprd_i2c_clear_irq(i2c_dev);

	पंचांगp = पढ़ोl(i2c_dev->base + I2C_CTL);
	ग_लिखोl(पंचांगp | I2C_EN | I2C_INT_EN, i2c_dev->base + I2C_CTL);
पूर्ण

अटल irqवापस_t sprd_i2c_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sprd_i2c *i2c_dev = dev_id;
	काष्ठा i2c_msg *msg = i2c_dev->msg;
	bool ack = !(पढ़ोl(i2c_dev->base + I2C_STATUS) & I2C_RX_ACK);
	u32 i2c_tran;

	अगर (msg->flags & I2C_M_RD)
		i2c_tran = i2c_dev->count >= I2C_FIFO_FULL_THLD;
	अन्यथा
		i2c_tran = i2c_dev->count;

	/*
	 * If we got one ACK from slave when writing data, and we did not
	 * finish this transmission (i2c_tran is not zero), then we should
	 * जारी to ग_लिखो data.
	 *
	 * For पढ़ोing data, ack is always true, अगर i2c_tran is not 0 which
	 * means we still need to contine to पढ़ो data from slave.
	 */
	अगर (i2c_tran && ack) अणु
		sprd_i2c_data_transfer(i2c_dev);
		वापस IRQ_HANDLED;
	पूर्ण

	i2c_dev->err = 0;

	/*
	 * If we did not get one ACK from slave when writing data, we should
	 * वापस -EIO to notअगरy users.
	 */
	अगर (!ack)
		i2c_dev->err = -EIO;
	अन्यथा अगर (msg->flags & I2C_M_RD && i2c_dev->count)
		sprd_i2c_पढ़ो_bytes(i2c_dev, i2c_dev->buf, i2c_dev->count);

	/* Transmission is करोne and clear ack and start operation */
	sprd_i2c_clear_ack(i2c_dev);
	sprd_i2c_clear_start(i2c_dev);
	complete(&i2c_dev->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sprd_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sprd_i2c *i2c_dev = dev_id;
	काष्ठा i2c_msg *msg = i2c_dev->msg;
	bool ack = !(पढ़ोl(i2c_dev->base + I2C_STATUS) & I2C_RX_ACK);
	u32 i2c_tran;

	अगर (msg->flags & I2C_M_RD)
		i2c_tran = i2c_dev->count >= I2C_FIFO_FULL_THLD;
	अन्यथा
		i2c_tran = i2c_dev->count;

	/*
	 * If we did not get one ACK from slave when writing data, then we
	 * should finish this transmission since we got some errors.
	 *
	 * When writing data, अगर i2c_tran == 0 which means we have ग_लिखोn
	 * करोne all data, then we can finish this transmission.
	 *
	 * When पढ़ोing data, अगर conut < rx fअगरo full threshold, which
	 * means we can पढ़ो all data in one समय, then we can finish this
	 * transmission too.
	 */
	अगर (!i2c_tran || !ack) अणु
		sprd_i2c_clear_start(i2c_dev);
		sprd_i2c_clear_irq(i2c_dev);
	पूर्ण

	sprd_i2c_set_fअगरo_empty_पूर्णांक(i2c_dev, 0);
	sprd_i2c_set_fअगरo_full_पूर्णांक(i2c_dev, 0);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक sprd_i2c_clk_init(काष्ठा sprd_i2c *i2c_dev)
अणु
	काष्ठा clk *clk_i2c, *clk_parent;

	clk_i2c = devm_clk_get(i2c_dev->dev, "i2c");
	अगर (IS_ERR(clk_i2c)) अणु
		dev_warn(i2c_dev->dev, "i2c%d can't get the i2c clock\n",
			 i2c_dev->adap.nr);
		clk_i2c = शून्य;
	पूर्ण

	clk_parent = devm_clk_get(i2c_dev->dev, "source");
	अगर (IS_ERR(clk_parent)) अणु
		dev_warn(i2c_dev->dev, "i2c%d can't get the source clock\n",
			 i2c_dev->adap.nr);
		clk_parent = शून्य;
	पूर्ण

	अगर (clk_set_parent(clk_i2c, clk_parent))
		i2c_dev->src_clk = clk_get_rate(clk_i2c);
	अन्यथा
		i2c_dev->src_clk = 26000000;

	dev_dbg(i2c_dev->dev, "i2c%d set source clock is %d\n",
		i2c_dev->adap.nr, i2c_dev->src_clk);

	i2c_dev->clk = devm_clk_get(i2c_dev->dev, "enable");
	अगर (IS_ERR(i2c_dev->clk)) अणु
		dev_err(i2c_dev->dev, "i2c%d can't get the enable clock\n",
			i2c_dev->adap.nr);
		वापस PTR_ERR(i2c_dev->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sprd_i2c *i2c_dev;
	u32 prop;
	पूर्णांक ret;

	pdev->id = of_alias_get_id(dev->of_node, "i2c");

	i2c_dev = devm_kzalloc(dev, माप(काष्ठा sprd_i2c), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	i2c_dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);

	i2c_dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (i2c_dev->irq < 0)
		वापस i2c_dev->irq;

	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);
	init_completion(&i2c_dev->complete);
	snम_लिखो(i2c_dev->adap.name, माप(i2c_dev->adap.name),
		 "%s", "sprd-i2c");

	i2c_dev->bus_freq = I2C_MAX_STANDARD_MODE_FREQ;
	i2c_dev->adap.owner = THIS_MODULE;
	i2c_dev->dev = dev;
	i2c_dev->adap.retries = 3;
	i2c_dev->adap.algo = &sprd_i2c_algo;
	i2c_dev->adap.algo_data = i2c_dev;
	i2c_dev->adap.dev.parent = dev;
	i2c_dev->adap.nr = pdev->id;
	i2c_dev->adap.dev.of_node = dev->of_node;

	अगर (!of_property_पढ़ो_u32(dev->of_node, "clock-frequency", &prop))
		i2c_dev->bus_freq = prop;

	/* We only support 100k and 400k now, otherwise will वापस error. */
	अगर (i2c_dev->bus_freq != I2C_MAX_STANDARD_MODE_FREQ &&
	    i2c_dev->bus_freq != I2C_MAX_FAST_MODE_FREQ)
		वापस -EINVAL;

	ret = sprd_i2c_clk_init(i2c_dev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, i2c_dev);

	ret = clk_prepare_enable(i2c_dev->clk);
	अगर (ret)
		वापस ret;

	sprd_i2c_enable(i2c_dev);

	pm_runसमय_set_स्वतःsuspend_delay(i2c_dev->dev, SPRD_I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(i2c_dev->dev);
	pm_runसमय_set_active(i2c_dev->dev);
	pm_runसमय_enable(i2c_dev->dev);

	ret = pm_runसमय_get_sync(i2c_dev->dev);
	अगर (ret < 0)
		जाओ err_rpm_put;

	ret = devm_request_thपढ़ोed_irq(dev, i2c_dev->irq,
		sprd_i2c_isr, sprd_i2c_isr_thपढ़ो,
		IRQF_NO_SUSPEND | IRQF_ONESHOT,
		pdev->name, i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request irq %d\n", i2c_dev->irq);
		जाओ err_rpm_put;
	पूर्ण

	ret = i2c_add_numbered_adapter(&i2c_dev->adap);
	अगर (ret) अणु
		dev_err(&pdev->dev, "add adapter failed\n");
		जाओ err_rpm_put;
	पूर्ण

	pm_runसमय_mark_last_busy(i2c_dev->dev);
	pm_runसमय_put_स्वतःsuspend(i2c_dev->dev);
	वापस 0;

err_rpm_put:
	pm_runसमय_put_noidle(i2c_dev->dev);
	pm_runसमय_disable(i2c_dev->dev);
	clk_disable_unprepare(i2c_dev->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_i2c *i2c_dev = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(i2c_dev->dev);
	अगर (ret < 0)
		वापस ret;

	i2c_del_adapter(&i2c_dev->adap);
	clk_disable_unprepare(i2c_dev->clk);

	pm_runसमय_put_noidle(i2c_dev->dev);
	pm_runसमय_disable(i2c_dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_i2c_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा sprd_i2c *i2c_dev = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&i2c_dev->adap);
	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sprd_i2c_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा sprd_i2c *i2c_dev = dev_get_drvdata(dev);

	i2c_mark_adapter_resumed(&i2c_dev->adap);
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sprd_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sprd_i2c *i2c_dev = dev_get_drvdata(dev);

	clk_disable_unprepare(i2c_dev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sprd_i2c *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2c_dev->clk);
	अगर (ret)
		वापस ret;

	sprd_i2c_enable(i2c_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sprd_i2c_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sprd_i2c_runसमय_suspend,
			   sprd_i2c_runसमय_resume, शून्य)

	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sprd_i2c_suspend_noirq,
				      sprd_i2c_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sprd_i2c_of_match[] = अणु
	अणु .compatible = "sprd,sc9860-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_i2c_of_match);

अटल काष्ठा platक्रमm_driver sprd_i2c_driver = अणु
	.probe = sprd_i2c_probe,
	.हटाओ = sprd_i2c_हटाओ,
	.driver = अणु
		   .name = "sprd-i2c",
		   .of_match_table = sprd_i2c_of_match,
		   .pm = &sprd_i2c_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_i2c_driver);

MODULE_DESCRIPTION("Spreadtrum I2C master controller driver");
MODULE_LICENSE("GPL v2");
