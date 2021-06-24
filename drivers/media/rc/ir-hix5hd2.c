<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 HiSilicon Limited.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <media/rc-core.h>

#घोषणा IR_ENABLE		0x00
#घोषणा IR_CONFIG		0x04
#घोषणा CNT_LEADS		0x08
#घोषणा CNT_LEADE		0x0c
#घोषणा CNT_SLEADE		0x10
#घोषणा CNT0_B			0x14
#घोषणा CNT1_B			0x18
#घोषणा IR_BUSY			0x1c
#घोषणा IR_DATAH		0x20
#घोषणा IR_DATAL		0x24
#घोषणा IR_INTM			0x28
#घोषणा IR_INTS			0x2c
#घोषणा IR_INTC			0x30
#घोषणा IR_START		0x34

/* पूर्णांकerrupt mask */
#घोषणा INTMS_SYMBRCV		(BIT(24) | BIT(8))
#घोषणा INTMS_TIMEOUT		(BIT(25) | BIT(9))
#घोषणा INTMS_OVERFLOW		(BIT(26) | BIT(10))
#घोषणा INT_CLR_OVERFLOW	BIT(18)
#घोषणा INT_CLR_TIMEOUT		BIT(17)
#घोषणा INT_CLR_RCV		BIT(16)
#घोषणा INT_CLR_RCVTIMEOUT	(BIT(16) | BIT(17))

#घोषणा IR_CLK_ENABLE		BIT(4)
#घोषणा IR_CLK_RESET		BIT(5)

/* IR_ENABLE रेजिस्टर bits */
#घोषणा IR_ENABLE_EN		BIT(0)
#घोषणा IR_ENABLE_EN_EXTRA	BIT(8)

#घोषणा IR_CFG_WIDTH_MASK	0xffff
#घोषणा IR_CFG_WIDTH_SHIFT	16
#घोषणा IR_CFG_FORMAT_MASK	0x3
#घोषणा IR_CFG_FORMAT_SHIFT	14
#घोषणा IR_CFG_INT_LEVEL_MASK	0x3f
#घोषणा IR_CFG_INT_LEVEL_SHIFT	8
/* only support raw mode */
#घोषणा IR_CFG_MODE_RAW		BIT(7)
#घोषणा IR_CFG_FREQ_MASK	0x7f
#घोषणा IR_CFG_FREQ_SHIFT	0
#घोषणा IR_CFG_INT_THRESHOLD	1
/* symbol start from low to high, symbol stream end at high*/
#घोषणा IR_CFG_SYMBOL_FMT	0
#घोषणा IR_CFG_SYMBOL_MAXWIDTH	0x3e80

#घोषणा IR_HIX5HD2_NAME		"hix5hd2-ir"

/* Need to set extra bit क्रम enabling IR */
#घोषणा HIX5HD2_FLAG_EXTRA_ENABLE	BIT(0)

काष्ठा hix5hd2_soc_data अणु
	u32 clk_reg;
	u32 flags;
पूर्ण;

अटल स्थिर काष्ठा hix5hd2_soc_data hix5hd2_data = अणु
	.clk_reg = 0x48,
पूर्ण;

अटल स्थिर काष्ठा hix5hd2_soc_data hi3796cv300_data = अणु
	.clk_reg = 0x60,
	.flags = HIX5HD2_FLAG_EXTRA_ENABLE,
पूर्ण;

काष्ठा hix5hd2_ir_priv अणु
	पूर्णांक			irq;
	व्योम __iomem		*base;
	काष्ठा device		*dev;
	काष्ठा rc_dev		*rdev;
	काष्ठा regmap		*regmap;
	काष्ठा clk		*घड़ी;
	अचिन्हित दीर्घ		rate;
	स्थिर काष्ठा hix5hd2_soc_data *socdata;
पूर्ण;

अटल पूर्णांक hix5hd2_ir_clk_enable(काष्ठा hix5hd2_ir_priv *dev, bool on)
अणु
	u32 clk_reg = dev->socdata->clk_reg;
	u32 val;
	पूर्णांक ret = 0;

	अगर (dev->regmap) अणु
		regmap_पढ़ो(dev->regmap, clk_reg, &val);
		अगर (on) अणु
			val &= ~IR_CLK_RESET;
			val |= IR_CLK_ENABLE;
		पूर्ण अन्यथा अणु
			val &= ~IR_CLK_ENABLE;
			val |= IR_CLK_RESET;
		पूर्ण
		regmap_ग_लिखो(dev->regmap, clk_reg, val);
	पूर्ण अन्यथा अणु
		अगर (on)
			ret = clk_prepare_enable(dev->घड़ी);
		अन्यथा
			clk_disable_unprepare(dev->घड़ी);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम hix5hd2_ir_enable(काष्ठा hix5hd2_ir_priv *priv)
अणु
	u32 val = IR_ENABLE_EN;

	अगर (priv->socdata->flags & HIX5HD2_FLAG_EXTRA_ENABLE)
		val |= IR_ENABLE_EN_EXTRA;

	ग_लिखोl_relaxed(val, priv->base + IR_ENABLE);
पूर्ण

अटल पूर्णांक hix5hd2_ir_config(काष्ठा hix5hd2_ir_priv *priv)
अणु
	पूर्णांक समयout = 10000;
	u32 val, rate;

	hix5hd2_ir_enable(priv);

	जबतक (पढ़ोl_relaxed(priv->base + IR_BUSY)) अणु
		अगर (समयout--) अणु
			udelay(1);
		पूर्ण अन्यथा अणु
			dev_err(priv->dev, "IR_BUSY timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/* Now only support raw mode, with symbol start from low to high */
	rate = DIV_ROUND_CLOSEST(priv->rate, 1000000);
	val = IR_CFG_SYMBOL_MAXWIDTH & IR_CFG_WIDTH_MASK << IR_CFG_WIDTH_SHIFT;
	val |= IR_CFG_SYMBOL_FMT & IR_CFG_FORMAT_MASK << IR_CFG_FORMAT_SHIFT;
	val |= (IR_CFG_INT_THRESHOLD - 1) & IR_CFG_INT_LEVEL_MASK
	       << IR_CFG_INT_LEVEL_SHIFT;
	val |= IR_CFG_MODE_RAW;
	val |= (rate - 1) & IR_CFG_FREQ_MASK << IR_CFG_FREQ_SHIFT;
	ग_लिखोl_relaxed(val, priv->base + IR_CONFIG);

	ग_लिखोl_relaxed(0x00, priv->base + IR_INTM);
	/* ग_लिखो arbitrary value to start  */
	ग_लिखोl_relaxed(0x01, priv->base + IR_START);
	वापस 0;
पूर्ण

अटल पूर्णांक hix5hd2_ir_खोलो(काष्ठा rc_dev *rdev)
अणु
	काष्ठा hix5hd2_ir_priv *priv = rdev->priv;
	पूर्णांक ret;

	ret = hix5hd2_ir_clk_enable(priv, true);
	अगर (ret)
		वापस ret;

	ret = hix5hd2_ir_config(priv);
	अगर (ret) अणु
		hix5hd2_ir_clk_enable(priv, false);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hix5hd2_ir_बंद(काष्ठा rc_dev *rdev)
अणु
	काष्ठा hix5hd2_ir_priv *priv = rdev->priv;

	hix5hd2_ir_clk_enable(priv, false);
पूर्ण

अटल irqवापस_t hix5hd2_ir_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	u32 symb_num, symb_val, symb_समय;
	u32 data_l, data_h;
	u32 irq_sr, i;
	काष्ठा hix5hd2_ir_priv *priv = data;

	irq_sr = पढ़ोl_relaxed(priv->base + IR_INTS);
	अगर (irq_sr & INTMS_OVERFLOW) अणु
		/*
		 * we must पढ़ो IR_DATAL first, then we can clean up
		 * IR_INTS availably since logic would not clear
		 * fअगरo when overflow, drv करो the job
		 */
		ir_raw_event_reset(priv->rdev);
		symb_num = पढ़ोl_relaxed(priv->base + IR_DATAH);
		क्रम (i = 0; i < symb_num; i++)
			पढ़ोl_relaxed(priv->base + IR_DATAL);

		ग_लिखोl_relaxed(INT_CLR_OVERFLOW, priv->base + IR_INTC);
		dev_info(priv->dev, "overflow, level=%d\n",
			 IR_CFG_INT_THRESHOLD);
	पूर्ण

	अगर ((irq_sr & INTMS_SYMBRCV) || (irq_sr & INTMS_TIMEOUT)) अणु
		काष्ठा ir_raw_event ev = अणुपूर्ण;

		symb_num = पढ़ोl_relaxed(priv->base + IR_DATAH);
		क्रम (i = 0; i < symb_num; i++) अणु
			symb_val = पढ़ोl_relaxed(priv->base + IR_DATAL);
			data_l = ((symb_val & 0xffff) * 10);
			data_h =  ((symb_val >> 16) & 0xffff) * 10;
			symb_समय = (data_l + data_h) / 10;

			ev.duration = data_l;
			ev.pulse = true;
			ir_raw_event_store(priv->rdev, &ev);

			अगर (symb_समय < IR_CFG_SYMBOL_MAXWIDTH) अणु
				ev.duration = data_h;
				ev.pulse = false;
				ir_raw_event_store(priv->rdev, &ev);
			पूर्ण अन्यथा अणु
				ir_raw_event_set_idle(priv->rdev, true);
			पूर्ण
		पूर्ण

		अगर (irq_sr & INTMS_SYMBRCV)
			ग_लिखोl_relaxed(INT_CLR_RCV, priv->base + IR_INTC);
		अगर (irq_sr & INTMS_TIMEOUT)
			ग_लिखोl_relaxed(INT_CLR_TIMEOUT, priv->base + IR_INTC);
	पूर्ण

	/* Empty software fअगरo */
	ir_raw_event_handle(priv->rdev);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id hix5hd2_ir_table[] = अणु
	अणु .compatible = "hisilicon,hix5hd2-ir", &hix5hd2_data, पूर्ण,
	अणु .compatible = "hisilicon,hi3796cv300-ir", &hi3796cv300_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hix5hd2_ir_table);

अटल पूर्णांक hix5hd2_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rc_dev *rdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा hix5hd2_ir_priv *priv;
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर अक्षर *map_name;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	of_id = of_match_device(hix5hd2_ir_table, dev);
	अगर (!of_id) अणु
		dev_err(dev, "Unable to initialize IR data\n");
		वापस -ENODEV;
	पूर्ण
	priv->socdata = of_id->data;

	priv->regmap = syscon_regmap_lookup_by_phandle(node,
						       "hisilicon,power-syscon");
	अगर (IS_ERR(priv->regmap)) अणु
		dev_info(dev, "no power-reg\n");
		priv->regmap = शून्य;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rdev)
		वापस -ENOMEM;

	priv->घड़ी = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->घड़ी)) अणु
		dev_err(dev, "clock not found\n");
		ret = PTR_ERR(priv->घड़ी);
		जाओ err;
	पूर्ण
	ret = clk_prepare_enable(priv->घड़ी);
	अगर (ret)
		जाओ err;
	priv->rate = clk_get_rate(priv->घड़ी);

	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->priv = priv;
	rdev->खोलो = hix5hd2_ir_खोलो;
	rdev->बंद = hix5hd2_ir_बंद;
	rdev->driver_name = IR_HIX5HD2_NAME;
	map_name = of_get_property(node, "linux,rc-map-name", शून्य);
	rdev->map_name = map_name ?: RC_MAP_EMPTY;
	rdev->device_name = IR_HIX5HD2_NAME;
	rdev->input_phys = IR_HIX5HD2_NAME "/input0";
	rdev->input_id.bustype = BUS_HOST;
	rdev->input_id.venकरोr = 0x0001;
	rdev->input_id.product = 0x0001;
	rdev->input_id.version = 0x0100;
	rdev->rx_resolution = 10;
	rdev->समयout = IR_CFG_SYMBOL_MAXWIDTH * 10;

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret < 0)
		जाओ clkerr;

	अगर (devm_request_irq(dev, priv->irq, hix5hd2_ir_rx_पूर्णांकerrupt,
			     0, pdev->name, priv) < 0) अणु
		dev_err(dev, "IRQ %d register failed\n", priv->irq);
		ret = -EINVAL;
		जाओ regerr;
	पूर्ण

	priv->rdev = rdev;
	priv->dev = dev;
	platक्रमm_set_drvdata(pdev, priv);

	वापस ret;

regerr:
	rc_unरेजिस्टर_device(rdev);
	rdev = शून्य;
clkerr:
	clk_disable_unprepare(priv->घड़ी);
err:
	rc_मुक्त_device(rdev);
	dev_err(dev, "Unable to register device (%d)\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hix5hd2_ir_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hix5hd2_ir_priv *priv = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(priv->घड़ी);
	rc_unरेजिस्टर_device(priv->rdev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hix5hd2_ir_suspend(काष्ठा device *dev)
अणु
	काष्ठा hix5hd2_ir_priv *priv = dev_get_drvdata(dev);

	clk_disable_unprepare(priv->घड़ी);
	hix5hd2_ir_clk_enable(priv, false);

	वापस 0;
पूर्ण

अटल पूर्णांक hix5hd2_ir_resume(काष्ठा device *dev)
अणु
	काष्ठा hix5hd2_ir_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = hix5hd2_ir_clk_enable(priv, true);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(priv->घड़ी);
	अगर (ret) अणु
		hix5hd2_ir_clk_enable(priv, false);
		वापस ret;
	पूर्ण

	hix5hd2_ir_enable(priv);

	ग_लिखोl_relaxed(0x00, priv->base + IR_INTM);
	ग_लिखोl_relaxed(0xff, priv->base + IR_INTC);
	ग_लिखोl_relaxed(0x01, priv->base + IR_START);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(hix5hd2_ir_pm_ops, hix5hd2_ir_suspend,
			 hix5hd2_ir_resume);

अटल काष्ठा platक्रमm_driver hix5hd2_ir_driver = अणु
	.driver = अणु
		.name = IR_HIX5HD2_NAME,
		.of_match_table = hix5hd2_ir_table,
		.pm     = &hix5hd2_ir_pm_ops,
	पूर्ण,
	.probe = hix5hd2_ir_probe,
	.हटाओ = hix5hd2_ir_हटाओ,
पूर्ण;

module_platक्रमm_driver(hix5hd2_ir_driver);

MODULE_DESCRIPTION("IR controller driver for hix5hd2 platforms");
MODULE_AUTHOR("Guoxiong Yan <yanguoxiong@huawei.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:hix5hd2-ir");
