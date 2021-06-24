<शैली गुरु>
/*
 * P2WI (Push-Pull Two Wire Interface) bus driver.
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * The P2WI controller looks like an SMBus controller which only supports byte
 * data transfers. But, it dअगरfers from standard SMBus protocol on several
 * aspects:
 * - it supports only one slave device, and thus drop the address field
 * - it adds a parity bit every 8bits of data
 * - only one पढ़ो access is required to पढ़ो a byte (instead of a ग_लिखो
 *   followed by a पढ़ो access in standard SMBus protocol)
 * - there's no Ack bit after each byte transfer
 *
 * This means this bus cannot be used to पूर्णांकerface with standard SMBus
 * devices (the only known device to support this पूर्णांकerface is the AXP221
 * PMIC).
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>


/* P2WI रेजिस्टरs */
#घोषणा P2WI_CTRL		0x0
#घोषणा P2WI_CCR		0x4
#घोषणा P2WI_INTE		0x8
#घोषणा P2WI_INTS		0xc
#घोषणा P2WI_DADDR0		0x10
#घोषणा P2WI_DADDR1		0x14
#घोषणा P2WI_DLEN		0x18
#घोषणा P2WI_DATA0		0x1c
#घोषणा P2WI_DATA1		0x20
#घोषणा P2WI_LCR		0x24
#घोषणा P2WI_PMCR		0x28

/* CTRL fields */
#घोषणा P2WI_CTRL_START_TRANS		BIT(7)
#घोषणा P2WI_CTRL_ABORT_TRANS		BIT(6)
#घोषणा P2WI_CTRL_GLOBAL_INT_ENB	BIT(1)
#घोषणा P2WI_CTRL_SOFT_RST		BIT(0)

/* CLK CTRL fields */
#घोषणा P2WI_CCR_SDA_OUT_DELAY(v)	(((v) & 0x7) << 8)
#घोषणा P2WI_CCR_MAX_CLK_DIV		0xff
#घोषणा P2WI_CCR_CLK_DIV(v)		((v) & P2WI_CCR_MAX_CLK_DIV)

/* STATUS fields */
#घोषणा P2WI_INTS_TRANS_ERR_ID(v)	(((v) >> 8) & 0xff)
#घोषणा P2WI_INTS_LOAD_BSY		BIT(2)
#घोषणा P2WI_INTS_TRANS_ERR		BIT(1)
#घोषणा P2WI_INTS_TRANS_OVER		BIT(0)

/* DATA LENGTH fields*/
#घोषणा P2WI_DLEN_READ			BIT(4)
#घोषणा P2WI_DLEN_DATA_LENGTH(v)	((v - 1) & 0x7)

/* LINE CTRL fields*/
#घोषणा P2WI_LCR_SCL_STATE		BIT(5)
#घोषणा P2WI_LCR_SDA_STATE		BIT(4)
#घोषणा P2WI_LCR_SCL_CTL		BIT(3)
#घोषणा P2WI_LCR_SCL_CTL_EN		BIT(2)
#घोषणा P2WI_LCR_SDA_CTL		BIT(1)
#घोषणा P2WI_LCR_SDA_CTL_EN		BIT(0)

/* PMU MODE CTRL fields */
#घोषणा P2WI_PMCR_PMU_INIT_SEND		BIT(31)
#घोषणा P2WI_PMCR_PMU_INIT_DATA(v)	(((v) & 0xff) << 16)
#घोषणा P2WI_PMCR_PMU_MODE_REG(v)	(((v) & 0xff) << 8)
#घोषणा P2WI_PMCR_PMU_DEV_ADDR(v)	((v) & 0xff)

#घोषणा P2WI_MAX_FREQ			6000000

काष्ठा p2wi अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा completion complete;
	अचिन्हित पूर्णांक status;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा reset_control *rstc;
	पूर्णांक slave_addr;
पूर्ण;

अटल irqवापस_t p2wi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा p2wi *p2wi = dev_id;
	अचिन्हित दीर्घ status;

	status = पढ़ोl(p2wi->regs + P2WI_INTS);
	p2wi->status = status;

	/* Clear पूर्णांकerrupts */
	status &= (P2WI_INTS_LOAD_BSY | P2WI_INTS_TRANS_ERR |
		   P2WI_INTS_TRANS_OVER);
	ग_लिखोl(status, p2wi->regs + P2WI_INTS);

	complete(&p2wi->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 p2wi_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_BYTE_DATA;
पूर्ण

अटल पूर्णांक p2wi_smbus_xfer(काष्ठा i2c_adapter *adap, u16 addr,
			   अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			   u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा p2wi *p2wi = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ dlen = P2WI_DLEN_DATA_LENGTH(1);

	अगर (p2wi->slave_addr >= 0 && addr != p2wi->slave_addr) अणु
		dev_err(&adap->dev, "invalid P2WI address\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!data)
		वापस -EINVAL;

	ग_लिखोl(command, p2wi->regs + P2WI_DADDR0);

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		dlen |= P2WI_DLEN_READ;
	अन्यथा
		ग_लिखोl(data->byte, p2wi->regs + P2WI_DATA0);

	ग_लिखोl(dlen, p2wi->regs + P2WI_DLEN);

	अगर (पढ़ोl(p2wi->regs + P2WI_CTRL) & P2WI_CTRL_START_TRANS) अणु
		dev_err(&adap->dev, "P2WI bus busy\n");
		वापस -EBUSY;
	पूर्ण

	reinit_completion(&p2wi->complete);

	ग_लिखोl(P2WI_INTS_LOAD_BSY | P2WI_INTS_TRANS_ERR | P2WI_INTS_TRANS_OVER,
	       p2wi->regs + P2WI_INTE);

	ग_लिखोl(P2WI_CTRL_START_TRANS | P2WI_CTRL_GLOBAL_INT_ENB,
	       p2wi->regs + P2WI_CTRL);

	रुको_क्रम_completion(&p2wi->complete);

	अगर (p2wi->status & P2WI_INTS_LOAD_BSY) अणु
		dev_err(&adap->dev, "P2WI bus busy\n");
		वापस -EBUSY;
	पूर्ण

	अगर (p2wi->status & P2WI_INTS_TRANS_ERR) अणु
		dev_err(&adap->dev, "P2WI bus xfer error\n");
		वापस -ENXIO;
	पूर्ण

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		data->byte = पढ़ोl(p2wi->regs + P2WI_DATA0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm p2wi_algo = अणु
	.smbus_xfer = p2wi_smbus_xfer,
	.functionality = p2wi_functionality,
पूर्ण;

अटल स्थिर काष्ठा of_device_id p2wi_of_match_table[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-p2wi" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, p2wi_of_match_table);

अटल पूर्णांक p2wi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *childnp;
	अचिन्हित दीर्घ parent_clk_freq;
	u32 clk_freq = I2C_MAX_STANDARD_MODE_FREQ;
	काष्ठा p2wi *p2wi;
	u32 slave_addr;
	पूर्णांक clk_भाग;
	पूर्णांक irq;
	पूर्णांक ret;

	of_property_पढ़ो_u32(np, "clock-frequency", &clk_freq);
	अगर (clk_freq > P2WI_MAX_FREQ) अणु
		dev_err(dev,
			"required clock-frequency (%u Hz) is too high (max = 6MHz)",
			clk_freq);
		वापस -EINVAL;
	पूर्ण

	अगर (of_get_child_count(np) > 1) अणु
		dev_err(dev, "P2WI only supports one slave device\n");
		वापस -EINVAL;
	पूर्ण

	p2wi = devm_kzalloc(dev, माप(काष्ठा p2wi), GFP_KERNEL);
	अगर (!p2wi)
		वापस -ENOMEM;

	p2wi->slave_addr = -1;

	/*
	 * Authorize a p2wi node without any children to be able to use an
	 * i2c-dev from userpace.
	 * In this हाल the slave_addr is set to -1 and won't be checked when
	 * launching a P2WI transfer.
	 */
	childnp = of_get_next_available_child(np, शून्य);
	अगर (childnp) अणु
		ret = of_property_पढ़ो_u32(childnp, "reg", &slave_addr);
		अगर (ret) अणु
			dev_err(dev, "invalid slave address on node %pOF\n",
				childnp);
			वापस -EINVAL;
		पूर्ण

		p2wi->slave_addr = slave_addr;
	पूर्ण

	p2wi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p2wi->regs))
		वापस PTR_ERR(p2wi->regs);

	strlcpy(p2wi->adapter.name, pdev->name, माप(p2wi->adapter.name));
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	p2wi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(p2wi->clk)) अणु
		ret = PTR_ERR(p2wi->clk);
		dev_err(dev, "failed to retrieve clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(p2wi->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clk: %d\n", ret);
		वापस ret;
	पूर्ण

	parent_clk_freq = clk_get_rate(p2wi->clk);

	p2wi->rstc = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(p2wi->rstc)) अणु
		ret = PTR_ERR(p2wi->rstc);
		dev_err(dev, "failed to retrieve reset controller: %d\n", ret);
		जाओ err_clk_disable;
	पूर्ण

	ret = reset_control_deनिश्चित(p2wi->rstc);
	अगर (ret) अणु
		dev_err(dev, "failed to deassert reset line: %d\n", ret);
		जाओ err_clk_disable;
	पूर्ण

	init_completion(&p2wi->complete);
	p2wi->adapter.dev.parent = dev;
	p2wi->adapter.algo = &p2wi_algo;
	p2wi->adapter.owner = THIS_MODULE;
	p2wi->adapter.dev.of_node = pdev->dev.of_node;
	platक्रमm_set_drvdata(pdev, p2wi);
	i2c_set_adapdata(&p2wi->adapter, p2wi);

	ret = devm_request_irq(dev, irq, p2wi_पूर्णांकerrupt, 0, pdev->name, p2wi);
	अगर (ret) अणु
		dev_err(dev, "can't register interrupt handler irq%d: %d\n",
			irq, ret);
		जाओ err_reset_निश्चित;
	पूर्ण

	ग_लिखोl(P2WI_CTRL_SOFT_RST, p2wi->regs + P2WI_CTRL);

	clk_भाग = parent_clk_freq / clk_freq;
	अगर (!clk_भाग) अणु
		dev_warn(dev,
			 "clock-frequency is too high, setting it to %lu Hz\n",
			 parent_clk_freq);
		clk_भाग = 1;
	पूर्ण अन्यथा अगर (clk_भाग > P2WI_CCR_MAX_CLK_DIV) अणु
		dev_warn(dev,
			 "clock-frequency is too low, setting it to %lu Hz\n",
			 parent_clk_freq / P2WI_CCR_MAX_CLK_DIV);
		clk_भाग = P2WI_CCR_MAX_CLK_DIV;
	पूर्ण

	ग_लिखोl(P2WI_CCR_SDA_OUT_DELAY(1) | P2WI_CCR_CLK_DIV(clk_भाग),
	       p2wi->regs + P2WI_CCR);

	ret = i2c_add_adapter(&p2wi->adapter);
	अगर (!ret)
		वापस 0;

err_reset_निश्चित:
	reset_control_निश्चित(p2wi->rstc);

err_clk_disable:
	clk_disable_unprepare(p2wi->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक p2wi_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा p2wi *p2wi = platक्रमm_get_drvdata(dev);

	reset_control_निश्चित(p2wi->rstc);
	clk_disable_unprepare(p2wi->clk);
	i2c_del_adapter(&p2wi->adapter);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver p2wi_driver = अणु
	.probe	= p2wi_probe,
	.हटाओ	= p2wi_हटाओ,
	.driver	= अणु
		.name = "i2c-sunxi-p2wi",
		.of_match_table = p2wi_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(p2wi_driver);

MODULE_AUTHOR("Boris BREZILLON <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner P2WI driver");
MODULE_LICENSE("GPL v2");
