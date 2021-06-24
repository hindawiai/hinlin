<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BCM2835 master mode driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा BCM2835_I2C_C		0x0
#घोषणा BCM2835_I2C_S		0x4
#घोषणा BCM2835_I2C_DLEN	0x8
#घोषणा BCM2835_I2C_A		0xc
#घोषणा BCM2835_I2C_FIFO	0x10
#घोषणा BCM2835_I2C_DIV		0x14
#घोषणा BCM2835_I2C_DEL		0x18
#घोषणा BCM2835_I2C_CLKT	0x1c

#घोषणा BCM2835_I2C_C_READ	BIT(0)
#घोषणा BCM2835_I2C_C_CLEAR	BIT(4) /* bits 4 and 5 both clear */
#घोषणा BCM2835_I2C_C_ST	BIT(7)
#घोषणा BCM2835_I2C_C_INTD	BIT(8)
#घोषणा BCM2835_I2C_C_INTT	BIT(9)
#घोषणा BCM2835_I2C_C_INTR	BIT(10)
#घोषणा BCM2835_I2C_C_I2CEN	BIT(15)

#घोषणा BCM2835_I2C_S_TA	BIT(0)
#घोषणा BCM2835_I2C_S_DONE	BIT(1)
#घोषणा BCM2835_I2C_S_TXW	BIT(2)
#घोषणा BCM2835_I2C_S_RXR	BIT(3)
#घोषणा BCM2835_I2C_S_TXD	BIT(4)
#घोषणा BCM2835_I2C_S_RXD	BIT(5)
#घोषणा BCM2835_I2C_S_TXE	BIT(6)
#घोषणा BCM2835_I2C_S_RXF	BIT(7)
#घोषणा BCM2835_I2C_S_ERR	BIT(8)
#घोषणा BCM2835_I2C_S_CLKT	BIT(9)
#घोषणा BCM2835_I2C_S_LEN	BIT(10) /* Fake bit क्रम SW error reporting */

#घोषणा BCM2835_I2C_FEDL_SHIFT	16
#घोषणा BCM2835_I2C_REDL_SHIFT	0

#घोषणा BCM2835_I2C_CDIV_MIN	0x0002
#घोषणा BCM2835_I2C_CDIV_MAX	0xFFFE

काष्ठा bcm2835_i2c_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	पूर्णांक irq;
	काष्ठा i2c_adapter adapter;
	काष्ठा completion completion;
	काष्ठा i2c_msg *curr_msg;
	काष्ठा clk *bus_clk;
	पूर्णांक num_msgs;
	u32 msg_err;
	u8 *msg_buf;
	माप_प्रकार msg_buf_reमुख्यing;
पूर्ण;

अटल अंतरभूत व्योम bcm2835_i2c_ग_लिखोl(काष्ठा bcm2835_i2c_dev *i2c_dev,
				      u32 reg, u32 val)
अणु
	ग_लिखोl(val, i2c_dev->regs + reg);
पूर्ण

अटल अंतरभूत u32 bcm2835_i2c_पढ़ोl(काष्ठा bcm2835_i2c_dev *i2c_dev, u32 reg)
अणु
	वापस पढ़ोl(i2c_dev->regs + reg);
पूर्ण

#घोषणा to_clk_bcm2835_i2c(_hw) container_of(_hw, काष्ठा clk_bcm2835_i2c, hw)
काष्ठा clk_bcm2835_i2c अणु
	काष्ठा clk_hw hw;
	काष्ठा bcm2835_i2c_dev *i2c_dev;
पूर्ण;

अटल पूर्णांक clk_bcm2835_i2c_calc_भागider(अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	u32 भागider = DIV_ROUND_UP(parent_rate, rate);

	/*
	 * Per the datasheet, the रेजिस्टर is always पूर्णांकerpreted as an even
	 * number, by rounding करोwn. In other words, the LSB is ignored. So,
	 * अगर the LSB is set, increment the भागider to aव्योम any issue.
	 */
	अगर (भागider & 1)
		भागider++;
	अगर ((भागider < BCM2835_I2C_CDIV_MIN) ||
	    (भागider > BCM2835_I2C_CDIV_MAX))
		वापस -EINVAL;

	वापस भागider;
पूर्ण

अटल पूर्णांक clk_bcm2835_i2c_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_bcm2835_i2c *भाग = to_clk_bcm2835_i2c(hw);
	u32 redl, fedl;
	u32 भागider = clk_bcm2835_i2c_calc_भागider(rate, parent_rate);

	अगर (भागider == -EINVAL)
		वापस -EINVAL;

	bcm2835_i2c_ग_लिखोl(भाग->i2c_dev, BCM2835_I2C_DIV, भागider);

	/*
	 * Number of core घड़ीs to रुको after falling edge beक्रमe
	 * outputting the next data bit.  Note that both FEDL and REDL
	 * can't be greater than CDIV/2.
	 */
	fedl = max(भागider / 16, 1u);

	/*
	 * Number of core घड़ीs to रुको after rising edge beक्रमe
	 * sampling the next incoming data bit.
	 */
	redl = max(भागider / 4, 1u);

	bcm2835_i2c_ग_लिखोl(भाग->i2c_dev, BCM2835_I2C_DEL,
			   (fedl << BCM2835_I2C_FEDL_SHIFT) |
			   (redl << BCM2835_I2C_REDL_SHIFT));
	वापस 0;
पूर्ण

अटल दीर्घ clk_bcm2835_i2c_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	u32 भागider = clk_bcm2835_i2c_calc_भागider(rate, *parent_rate);

	वापस DIV_ROUND_UP(*parent_rate, भागider);
पूर्ण

अटल अचिन्हित दीर्घ clk_bcm2835_i2c_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_bcm2835_i2c *भाग = to_clk_bcm2835_i2c(hw);
	u32 भागider = bcm2835_i2c_पढ़ोl(भाग->i2c_dev, BCM2835_I2C_DIV);

	वापस DIV_ROUND_UP(parent_rate, भागider);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_bcm2835_i2c_ops = अणु
	.set_rate = clk_bcm2835_i2c_set_rate,
	.round_rate = clk_bcm2835_i2c_round_rate,
	.recalc_rate = clk_bcm2835_i2c_recalc_rate,
पूर्ण;

अटल काष्ठा clk *bcm2835_i2c_रेजिस्टर_भाग(काष्ठा device *dev,
					काष्ठा clk *mclk,
					काष्ठा bcm2835_i2c_dev *i2c_dev)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_bcm2835_i2c *priv;
	अक्षर name[32];
	स्थिर अक्षर *mclk_name;

	snम_लिखो(name, माप(name), "%s_div", dev_name(dev));

	mclk_name = __clk_get_name(mclk);

	init.ops = &clk_bcm2835_i2c_ops;
	init.name = name;
	init.parent_names = (स्थिर अक्षर* []) अणु mclk_name पूर्ण;
	init.num_parents = 1;
	init.flags = 0;

	priv = devm_kzalloc(dev, माप(काष्ठा clk_bcm2835_i2c), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस ERR_PTR(-ENOMEM);

	priv->hw.init = &init;
	priv->i2c_dev = i2c_dev;

	clk_hw_रेजिस्टर_clkdev(&priv->hw, "div", dev_name(dev));
	वापस devm_clk_रेजिस्टर(dev, &priv->hw);
पूर्ण

अटल व्योम bcm2835_fill_txfअगरo(काष्ठा bcm2835_i2c_dev *i2c_dev)
अणु
	u32 val;

	जबतक (i2c_dev->msg_buf_reमुख्यing) अणु
		val = bcm2835_i2c_पढ़ोl(i2c_dev, BCM2835_I2C_S);
		अगर (!(val & BCM2835_I2C_S_TXD))
			अवरोध;
		bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_FIFO,
				   *i2c_dev->msg_buf);
		i2c_dev->msg_buf++;
		i2c_dev->msg_buf_reमुख्यing--;
	पूर्ण
पूर्ण

अटल व्योम bcm2835_drain_rxfअगरo(काष्ठा bcm2835_i2c_dev *i2c_dev)
अणु
	u32 val;

	जबतक (i2c_dev->msg_buf_reमुख्यing) अणु
		val = bcm2835_i2c_पढ़ोl(i2c_dev, BCM2835_I2C_S);
		अगर (!(val & BCM2835_I2C_S_RXD))
			अवरोध;
		*i2c_dev->msg_buf = bcm2835_i2c_पढ़ोl(i2c_dev,
						      BCM2835_I2C_FIFO);
		i2c_dev->msg_buf++;
		i2c_dev->msg_buf_reमुख्यing--;
	पूर्ण
पूर्ण

/*
 * Repeated Start Condition (Sr)
 * The BCM2835 ARM Peripherals datasheet mentions a way to trigger a Sr when it
 * talks about पढ़ोing from a slave with 10 bit address. This is achieved by
 * issuing a ग_लिखो, poll the I2CS.TA flag and रुको क्रम it to be set, and then
 * issue a पढ़ो.
 * A comment in https://github.com/raspberrypi/linux/issues/254 shows how the
 * firmware actually करोes it using polling and says that it's a workaround क्रम
 * a problem in the state machine.
 * It turns out that it is possible to use the TXW पूर्णांकerrupt to know when the
 * transfer is active, provided the FIFO has not been prefilled.
 */

अटल व्योम bcm2835_i2c_start_transfer(काष्ठा bcm2835_i2c_dev *i2c_dev)
अणु
	u32 c = BCM2835_I2C_C_ST | BCM2835_I2C_C_I2CEN;
	काष्ठा i2c_msg *msg = i2c_dev->curr_msg;
	bool last_msg = (i2c_dev->num_msgs == 1);

	अगर (!i2c_dev->num_msgs)
		वापस;

	i2c_dev->num_msgs--;
	i2c_dev->msg_buf = msg->buf;
	i2c_dev->msg_buf_reमुख्यing = msg->len;

	अगर (msg->flags & I2C_M_RD)
		c |= BCM2835_I2C_C_READ | BCM2835_I2C_C_INTR;
	अन्यथा
		c |= BCM2835_I2C_C_INTT;

	अगर (last_msg)
		c |= BCM2835_I2C_C_INTD;

	bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_A, msg->addr);
	bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_DLEN, msg->len);
	bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_C, c);
पूर्ण

अटल व्योम bcm2835_i2c_finish_transfer(काष्ठा bcm2835_i2c_dev *i2c_dev)
अणु
	i2c_dev->curr_msg = शून्य;
	i2c_dev->num_msgs = 0;

	i2c_dev->msg_buf = शून्य;
	i2c_dev->msg_buf_reमुख्यing = 0;
पूर्ण

/*
 * Note about I2C_C_CLEAR on error:
 * The I2C_C_CLEAR on errors will take some समय to resolve -- अगर you were in
 * non-idle state and I2C_C_READ, it sets an पात_rx flag and runs through
 * the state machine to send a NACK and a STOP. Since we're setting CLEAR
 * without I2CEN, that NACK will be hanging around queued up क्रम next समय
 * we start the engine.
 */

अटल irqवापस_t bcm2835_i2c_isr(पूर्णांक this_irq, व्योम *data)
अणु
	काष्ठा bcm2835_i2c_dev *i2c_dev = data;
	u32 val, err;

	val = bcm2835_i2c_पढ़ोl(i2c_dev, BCM2835_I2C_S);

	err = val & (BCM2835_I2C_S_CLKT | BCM2835_I2C_S_ERR);
	अगर (err) अणु
		i2c_dev->msg_err = err;
		जाओ complete;
	पूर्ण

	अगर (val & BCM2835_I2C_S_DONE) अणु
		अगर (!i2c_dev->curr_msg) अणु
			dev_err(i2c_dev->dev, "Got unexpected interrupt (from firmware?)\n");
		पूर्ण अन्यथा अगर (i2c_dev->curr_msg->flags & I2C_M_RD) अणु
			bcm2835_drain_rxfअगरo(i2c_dev);
			val = bcm2835_i2c_पढ़ोl(i2c_dev, BCM2835_I2C_S);
		पूर्ण

		अगर ((val & BCM2835_I2C_S_RXD) || i2c_dev->msg_buf_reमुख्यing)
			i2c_dev->msg_err = BCM2835_I2C_S_LEN;
		अन्यथा
			i2c_dev->msg_err = 0;
		जाओ complete;
	पूर्ण

	अगर (val & BCM2835_I2C_S_TXW) अणु
		अगर (!i2c_dev->msg_buf_reमुख्यing) अणु
			i2c_dev->msg_err = val | BCM2835_I2C_S_LEN;
			जाओ complete;
		पूर्ण

		bcm2835_fill_txfअगरo(i2c_dev);

		अगर (i2c_dev->num_msgs && !i2c_dev->msg_buf_reमुख्यing) अणु
			i2c_dev->curr_msg++;
			bcm2835_i2c_start_transfer(i2c_dev);
		पूर्ण

		वापस IRQ_HANDLED;
	पूर्ण

	अगर (val & BCM2835_I2C_S_RXR) अणु
		अगर (!i2c_dev->msg_buf_reमुख्यing) अणु
			i2c_dev->msg_err = val | BCM2835_I2C_S_LEN;
			जाओ complete;
		पूर्ण

		bcm2835_drain_rxfअगरo(i2c_dev);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;

complete:
	bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_C, BCM2835_I2C_C_CLEAR);
	bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_S, BCM2835_I2C_S_CLKT |
			   BCM2835_I2C_S_ERR | BCM2835_I2C_S_DONE);
	complete(&i2c_dev->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm2835_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[],
			    पूर्णांक num)
अणु
	काष्ठा bcm2835_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ समय_left;
	पूर्णांक i;

	क्रम (i = 0; i < (num - 1); i++)
		अगर (msgs[i].flags & I2C_M_RD) अणु
			dev_warn_once(i2c_dev->dev,
				      "only one read message supported, has to be last\n");
			वापस -EOPNOTSUPP;
		पूर्ण

	i2c_dev->curr_msg = msgs;
	i2c_dev->num_msgs = num;
	reinit_completion(&i2c_dev->completion);

	bcm2835_i2c_start_transfer(i2c_dev);

	समय_left = रुको_क्रम_completion_समयout(&i2c_dev->completion,
						adap->समयout);

	bcm2835_i2c_finish_transfer(i2c_dev);

	अगर (!समय_left) अणु
		bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_C,
				   BCM2835_I2C_C_CLEAR);
		dev_err(i2c_dev->dev, "i2c transfer timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (!i2c_dev->msg_err)
		वापस num;

	dev_dbg(i2c_dev->dev, "i2c transfer failed: %x\n", i2c_dev->msg_err);

	अगर (i2c_dev->msg_err & BCM2835_I2C_S_ERR)
		वापस -EREMOTEIO;

	वापस -EIO;
पूर्ण

अटल u32 bcm2835_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm bcm2835_i2c_algo = अणु
	.master_xfer	= bcm2835_i2c_xfer,
	.functionality	= bcm2835_i2c_func,
पूर्ण;

/*
 * The BCM2835 was reported to have problems with घड़ी stretching:
 * https://www.advamation.com/knowhow/raspberrypi/rpi-i2c-bug.hपंचांगl
 * https://www.raspberrypi.org/क्रमums/viewtopic.php?p=146272
 */
अटल स्थिर काष्ठा i2c_adapter_quirks bcm2835_i2c_quirks = अणु
	.flags = I2C_AQ_NO_CLK_STRETCH,
पूर्ण;

अटल पूर्णांक bcm2835_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_i2c_dev *i2c_dev;
	काष्ठा resource *mem, *irq;
	पूर्णांक ret;
	काष्ठा i2c_adapter *adap;
	काष्ठा clk *mclk;
	u32 bus_clk_rate;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, i2c_dev);
	i2c_dev->dev = &pdev->dev;
	init_completion(&i2c_dev->completion);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(i2c_dev->regs))
		वापस PTR_ERR(i2c_dev->regs);

	mclk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mclk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(mclk),
				     "Could not get clock\n");

	i2c_dev->bus_clk = bcm2835_i2c_रेजिस्टर_भाग(&pdev->dev, mclk, i2c_dev);

	अगर (IS_ERR(i2c_dev->bus_clk)) अणु
		dev_err(&pdev->dev, "Could not register clock\n");
		वापस PTR_ERR(i2c_dev->bus_clk);
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				   &bus_clk_rate);
	अगर (ret < 0) अणु
		dev_warn(&pdev->dev,
			 "Could not read clock-frequency property\n");
		bus_clk_rate = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण

	ret = clk_set_rate_exclusive(i2c_dev->bus_clk, bus_clk_rate);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not set clock frequency\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(i2c_dev->bus_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't prepare clock");
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "No IRQ resource\n");
		वापस -ENODEV;
	पूर्ण
	i2c_dev->irq = irq->start;

	ret = request_irq(i2c_dev->irq, bcm2835_i2c_isr, IRQF_SHARED,
			  dev_name(&pdev->dev), i2c_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request IRQ\n");
		वापस -ENODEV;
	पूर्ण

	adap = &i2c_dev->adapter;
	i2c_set_adapdata(adap, i2c_dev);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	snम_लिखो(adap->name, माप(adap->name), "bcm2835 (%s)",
		 of_node_full_name(pdev->dev.of_node));
	adap->algo = &bcm2835_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->quirks = of_device_get_match_data(&pdev->dev);

	bcm2835_i2c_ग_लिखोl(i2c_dev, BCM2835_I2C_C, 0);

	ret = i2c_add_adapter(adap);
	अगर (ret)
		मुक्त_irq(i2c_dev->irq, i2c_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);

	clk_rate_exclusive_put(i2c_dev->bus_clk);
	clk_disable_unprepare(i2c_dev->bus_clk);

	मुक्त_irq(i2c_dev->irq, i2c_dev);
	i2c_del_adapter(&i2c_dev->adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_i2c_of_match[] = अणु
	अणु .compatible = "brcm,bcm2711-i2c" पूर्ण,
	अणु .compatible = "brcm,bcm2835-i2c", .data = &bcm2835_i2c_quirks पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_i2c_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_i2c_driver = अणु
	.probe		= bcm2835_i2c_probe,
	.हटाओ		= bcm2835_i2c_हटाओ,
	.driver		= अणु
		.name	= "i2c-bcm2835",
		.of_match_table = bcm2835_i2c_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_i2c_driver);

MODULE_AUTHOR("Stephen Warren <swarren@wwwdotorg.org>");
MODULE_DESCRIPTION("BCM2835 I2C bus adapter");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c-bcm2835");
