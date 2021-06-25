<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/i2c/busses/i2c-mt7621.c
 *
 * Copyright (C) 2013 Steven Liu <steven_liu@mediatek.com>
 * Copyright (C) 2016 Michael Lee <igvtee@gmail.com>
 * Copyright (C) 2018 Jan Breuer <jan.breuer@jaybee.cz>
 *
 * Improve driver क्रम i2cdetect from i2c-tools to detect i2c devices on the bus.
 * (C) 2014 Sittisak <sittisaks@hoपंचांगail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset.h>

#घोषणा REG_SM0CFG2_REG		0x28
#घोषणा REG_SM0CTL0_REG		0x40
#घोषणा REG_SM0CTL1_REG		0x44
#घोषणा REG_SM0D0_REG		0x50
#घोषणा REG_SM0D1_REG		0x54
#घोषणा REG_PINTEN_REG		0x5c
#घोषणा REG_PINTST_REG		0x60
#घोषणा REG_PINTCL_REG		0x64

/* REG_SM0CFG2_REG */
#घोषणा SM0CFG2_IS_AUTOMODE	BIT(0)

/* REG_SM0CTL0_REG */
#घोषणा SM0CTL0_ODRAIN		BIT(31)
#घोषणा SM0CTL0_CLK_DIV_MASK	(0x7ff << 16)
#घोषणा SM0CTL0_CLK_DIV_MAX	0x7ff
#घोषणा SM0CTL0_CS_STATUS       BIT(4)
#घोषणा SM0CTL0_SCL_STATE       BIT(3)
#घोषणा SM0CTL0_SDA_STATE       BIT(2)
#घोषणा SM0CTL0_EN              BIT(1)
#घोषणा SM0CTL0_SCL_STRETCH     BIT(0)

/* REG_SM0CTL1_REG */
#घोषणा SM0CTL1_ACK_MASK	(0xff << 16)
#घोषणा SM0CTL1_PGLEN_MASK	(0x7 << 8)
#घोषणा SM0CTL1_PGLEN(x)	((((x) - 1) << 8) & SM0CTL1_PGLEN_MASK)
#घोषणा SM0CTL1_READ		(5 << 4)
#घोषणा SM0CTL1_READ_LAST	(4 << 4)
#घोषणा SM0CTL1_STOP		(3 << 4)
#घोषणा SM0CTL1_WRITE		(2 << 4)
#घोषणा SM0CTL1_START		(1 << 4)
#घोषणा SM0CTL1_MODE_MASK	(0x7 << 4)
#घोषणा SM0CTL1_TRI		BIT(0)

/* समयout रुकोing क्रम I2C devices to respond */
#घोषणा TIMEOUT_MS		1000

काष्ठा mtk_i2c अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा i2c_adapter adap;
	u32 bus_freq;
	u32 clk_भाग;
	u32 flags;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक mtk_i2c_रुको_idle(काष्ठा mtk_i2c *i2c)
अणु
	पूर्णांक ret;
	u32 val;

	ret = पढ़ोl_relaxed_poll_समयout(i2c->base + REG_SM0CTL1_REG,
					 val, !(val & SM0CTL1_TRI),
					 10, TIMEOUT_MS * 1000);
	अगर (ret)
		dev_dbg(i2c->dev, "idle err(%d)\n", ret);

	वापस ret;
पूर्ण

अटल व्योम mtk_i2c_reset(काष्ठा mtk_i2c *i2c)
अणु
	पूर्णांक ret;

	ret = device_reset(i2c->adap.dev.parent);
	अगर (ret)
		dev_err(i2c->dev, "I2C reset failed!\n");

	/*
	 * Don't set SM0CTL0_ODRAIN as its bit meaning is inverted. To
	 * configure खोलो-drain mode, this bit needs to be cleared.
	 */
	ioग_लिखो32(((i2c->clk_भाग << 16) & SM0CTL0_CLK_DIV_MASK) | SM0CTL0_EN |
		  SM0CTL0_SCL_STRETCH, i2c->base + REG_SM0CTL0_REG);
	ioग_लिखो32(0, i2c->base + REG_SM0CFG2_REG);
पूर्ण

अटल व्योम mtk_i2c_dump_reg(काष्ठा mtk_i2c *i2c)
अणु
	dev_dbg(i2c->dev,
		"SM0CFG2 %08x, SM0CTL0 %08x, SM0CTL1 %08x, SM0D0 %08x, SM0D1 %08x\n",
		ioपढ़ो32(i2c->base + REG_SM0CFG2_REG),
		ioपढ़ो32(i2c->base + REG_SM0CTL0_REG),
		ioपढ़ो32(i2c->base + REG_SM0CTL1_REG),
		ioपढ़ो32(i2c->base + REG_SM0D0_REG),
		ioपढ़ो32(i2c->base + REG_SM0D1_REG));
पूर्ण

अटल पूर्णांक mtk_i2c_check_ack(काष्ठा mtk_i2c *i2c, u32 expected)
अणु
	u32 ack = पढ़ोl_relaxed(i2c->base + REG_SM0CTL1_REG);
	u32 ack_expected = (expected << 16) & SM0CTL1_ACK_MASK;

	वापस ((ack & ack_expected) == ack_expected) ? 0 : -ENXIO;
पूर्ण

अटल पूर्णांक mtk_i2c_master_start(काष्ठा mtk_i2c *i2c)
अणु
	ioग_लिखो32(SM0CTL1_START | SM0CTL1_TRI, i2c->base + REG_SM0CTL1_REG);
	वापस mtk_i2c_रुको_idle(i2c);
पूर्ण

अटल पूर्णांक mtk_i2c_master_stop(काष्ठा mtk_i2c *i2c)
अणु
	ioग_लिखो32(SM0CTL1_STOP | SM0CTL1_TRI, i2c->base + REG_SM0CTL1_REG);
	वापस mtk_i2c_रुको_idle(i2c);
पूर्ण

अटल पूर्णांक mtk_i2c_master_cmd(काष्ठा mtk_i2c *i2c, u32 cmd, पूर्णांक page_len)
अणु
	ioग_लिखो32(cmd | SM0CTL1_TRI | SM0CTL1_PGLEN(page_len),
		  i2c->base + REG_SM0CTL1_REG);
	वापस mtk_i2c_रुको_idle(i2c);
पूर्ण

अटल पूर्णांक mtk_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			       पूर्णांक num)
अणु
	काष्ठा mtk_i2c *i2c;
	काष्ठा i2c_msg *pmsg;
	u16 addr;
	पूर्णांक i, j, ret, len, page_len;
	u32 cmd;
	u32 data[2];

	i2c = i2c_get_adapdata(adap);

	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];

		/* रुको hardware idle */
		ret = mtk_i2c_रुको_idle(i2c);
		अगर (ret)
			जाओ err_समयout;

		/* start sequence */
		ret = mtk_i2c_master_start(i2c);
		अगर (ret)
			जाओ err_समयout;

		/* ग_लिखो address */
		अगर (pmsg->flags & I2C_M_TEN) अणु
			/* 10 bits address */
			addr = 0xf0 | ((pmsg->addr >> 7) & 0x06);
			addr |= (pmsg->addr & 0xff) << 8;
			अगर (pmsg->flags & I2C_M_RD)
				addr |= 1;
			ioग_लिखो32(addr, i2c->base + REG_SM0D0_REG);
			ret = mtk_i2c_master_cmd(i2c, SM0CTL1_WRITE, 2);
			अगर (ret)
				जाओ err_समयout;
		पूर्ण अन्यथा अणु
			/* 7 bits address */
			addr = i2c_8bit_addr_from_msg(pmsg);
			ioग_लिखो32(addr, i2c->base + REG_SM0D0_REG);
			ret = mtk_i2c_master_cmd(i2c, SM0CTL1_WRITE, 1);
			अगर (ret)
				जाओ err_समयout;
		पूर्ण

		/* check address ACK */
		अगर (!(pmsg->flags & I2C_M_IGNORE_NAK)) अणु
			ret = mtk_i2c_check_ack(i2c, BIT(0));
			अगर (ret)
				जाओ err_ack;
		पूर्ण

		/* transfer data */
		क्रम (len = pmsg->len, j = 0; len > 0; len -= 8, j += 8) अणु
			page_len = (len >= 8) ? 8 : len;

			अगर (pmsg->flags & I2C_M_RD) अणु
				cmd = (len > 8) ?
					SM0CTL1_READ : SM0CTL1_READ_LAST;
			पूर्ण अन्यथा अणु
				स_नकल(data, &pmsg->buf[j], page_len);
				ioग_लिखो32(data[0], i2c->base + REG_SM0D0_REG);
				ioग_लिखो32(data[1], i2c->base + REG_SM0D1_REG);
				cmd = SM0CTL1_WRITE;
			पूर्ण

			ret = mtk_i2c_master_cmd(i2c, cmd, page_len);
			अगर (ret)
				जाओ err_समयout;

			अगर (pmsg->flags & I2C_M_RD) अणु
				data[0] = ioपढ़ो32(i2c->base + REG_SM0D0_REG);
				data[1] = ioपढ़ो32(i2c->base + REG_SM0D1_REG);
				स_नकल(&pmsg->buf[j], data, page_len);
			पूर्ण अन्यथा अणु
				अगर (!(pmsg->flags & I2C_M_IGNORE_NAK)) अणु
					ret = mtk_i2c_check_ack(i2c,
								(1 << page_len)
								- 1);
					अगर (ret)
						जाओ err_ack;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ret = mtk_i2c_master_stop(i2c);
	अगर (ret)
		जाओ err_समयout;

	/* the वापस value is number of executed messages */
	वापस i;

err_ack:
	ret = mtk_i2c_master_stop(i2c);
	अगर (ret)
		जाओ err_समयout;
	वापस -ENXIO;

err_समयout:
	mtk_i2c_dump_reg(i2c);
	mtk_i2c_reset(i2c);
	वापस ret;
पूर्ण

अटल u32 mtk_i2c_func(काष्ठा i2c_adapter *a)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mtk_i2c_algo = अणु
	.master_xfer	= mtk_i2c_master_xfer,
	.functionality	= mtk_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा of_device_id i2c_mtk_dt_ids[] = अणु
	अणु .compatible = "mediatek,mt7621-i2c" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, i2c_mtk_dt_ids);

अटल व्योम mtk_i2c_init(काष्ठा mtk_i2c *i2c)
अणु
	i2c->clk_भाग = clk_get_rate(i2c->clk) / i2c->bus_freq - 1;
	अगर (i2c->clk_भाग < 99)
		i2c->clk_भाग = 99;
	अगर (i2c->clk_भाग > SM0CTL0_CLK_DIV_MAX)
		i2c->clk_भाग = SM0CTL0_CLK_DIV_MAX;

	mtk_i2c_reset(i2c);
पूर्ण

अटल पूर्णांक mtk_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा mtk_i2c *i2c;
	काष्ठा i2c_adapter *adap;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा mtk_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c->clk)) अणु
		dev_err(&pdev->dev, "no clock defined\n");
		वापस PTR_ERR(i2c->clk);
	पूर्ण
	ret = clk_prepare_enable(i2c->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable clock\n");
		वापस ret;
	पूर्ण

	i2c->dev = &pdev->dev;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				 &i2c->bus_freq))
		i2c->bus_freq = I2C_MAX_STANDARD_MODE_FREQ;

	अगर (i2c->bus_freq == 0) अणु
		dev_warn(i2c->dev, "clock-frequency 0 not supported\n");
		वापस -EINVAL;
	पूर्ण

	adap = &i2c->adap;
	adap->owner = THIS_MODULE;
	adap->algo = &mtk_i2c_algo;
	adap->retries = 3;
	adap->dev.parent = &pdev->dev;
	i2c_set_adapdata(adap, i2c);
	adap->dev.of_node = pdev->dev.of_node;
	strlcpy(adap->name, dev_name(&pdev->dev), माप(adap->name));

	platक्रमm_set_drvdata(pdev, i2c);

	mtk_i2c_init(i2c);

	ret = i2c_add_adapter(adap);
	अगर (ret < 0)
		वापस ret;

	dev_info(&pdev->dev, "clock %u kHz\n", i2c->bus_freq / 1000);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_i2c *i2c = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(i2c->clk);
	i2c_del_adapter(&i2c->adap);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_i2c_driver = अणु
	.probe		= mtk_i2c_probe,
	.हटाओ		= mtk_i2c_हटाओ,
	.driver		= अणु
		.name	= "i2c-mt7621",
		.of_match_table = i2c_mtk_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_i2c_driver);

MODULE_AUTHOR("Steven Liu");
MODULE_DESCRIPTION("MT7621 I2C host driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:MT7621-I2C");
