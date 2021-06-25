<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Allwinner sunXi IR controller
 *
 * Copyright (C) 2014 Alexsey Shestacov <wingrime@linux-sunxi.org>
 * Copyright (C) 2014 Alexander Bersenev <bay@hackerकरोm.ru>
 *
 * Based on sun5i-ir.c:
 * Copyright (C) 2007-2012 Daniel Wang
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset.h>
#समावेश <media/rc-core.h>

#घोषणा SUNXI_IR_DEV "sunxi-ir"

/* Registers */
/* IR Control */
#घोषणा SUNXI_IR_CTL_REG      0x00
/* Global Enable */
#घोषणा REG_CTL_GEN			BIT(0)
/* RX block enable */
#घोषणा REG_CTL_RXEN			BIT(1)
/* CIR mode */
#घोषणा REG_CTL_MD			(BIT(4) | BIT(5))

/* Rx Config */
#घोषणा SUNXI_IR_RXCTL_REG    0x10
/* Pulse Polarity Invert flag */
#घोषणा REG_RXCTL_RPPI			BIT(2)

/* Rx Data */
#घोषणा SUNXI_IR_RXFIFO_REG   0x20

/* Rx Interrupt Enable */
#घोषणा SUNXI_IR_RXINT_REG    0x2C
/* Rx FIFO Overflow Interrupt Enable */
#घोषणा REG_RXINT_ROI_EN		BIT(0)
/* Rx Packet End Interrupt Enable */
#घोषणा REG_RXINT_RPEI_EN		BIT(1)
/* Rx FIFO Data Available Interrupt Enable */
#घोषणा REG_RXINT_RAI_EN		BIT(4)

/* Rx FIFO available byte level */
#घोषणा REG_RXINT_RAL(val)    ((val) << 8)

/* Rx Interrupt Status */
#घोषणा SUNXI_IR_RXSTA_REG    0x30
/* Rx FIFO Overflow */
#घोषणा REG_RXSTA_ROI			REG_RXINT_ROI_EN
/* Rx Packet End */
#घोषणा REG_RXSTA_RPE			REG_RXINT_RPEI_EN
/* Rx FIFO Data Available */
#घोषणा REG_RXSTA_RA			REG_RXINT_RAI_EN
/* RX FIFO Get Available Counter */
#घोषणा REG_RXSTA_GET_AC(val) (((val) >> 8) & (ir->fअगरo_size * 2 - 1))
/* Clear all पूर्णांकerrupt status value */
#घोषणा REG_RXSTA_CLEARALL    0xff

/* IR Sample Config */
#घोषणा SUNXI_IR_CIR_REG      0x34
/* CIR_REG रेजिस्टर noise threshold */
#घोषणा REG_CIR_NTHR(val)    (((val) << 2) & (GENMASK(7, 2)))
/* CIR_REG रेजिस्टर idle threshold */
#घोषणा REG_CIR_ITHR(val)    (((val) << 8) & (GENMASK(15, 8)))

/* Required frequency क्रम IR0 or IR1 घड़ी in CIR mode (शेष) */
#घोषणा SUNXI_IR_BASE_CLK     8000000
/* Noise threshold in samples  */
#घोषणा SUNXI_IR_RXNOISE      1

/**
 * काष्ठा sunxi_ir_quirks - Dअगरferences between SoC variants.
 *
 * @has_reset: SoC needs reset deनिश्चितed.
 * @fअगरo_size: size of the fअगरo.
 */
काष्ठा sunxi_ir_quirks अणु
	bool		has_reset;
	पूर्णांक		fअगरo_size;
पूर्ण;

काष्ठा sunxi_ir अणु
	काष्ठा rc_dev   *rc;
	व्योम __iomem    *base;
	पूर्णांक             irq;
	पूर्णांक		fअगरo_size;
	काष्ठा clk      *clk;
	काष्ठा clk      *apb_clk;
	काष्ठा reset_control *rst;
	स्थिर अक्षर      *map_name;
पूर्ण;

अटल irqवापस_t sunxi_ir_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ status;
	अचिन्हित अक्षर dt;
	अचिन्हित पूर्णांक cnt, rc;
	काष्ठा sunxi_ir *ir = dev_id;
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	status = पढ़ोl(ir->base + SUNXI_IR_RXSTA_REG);

	/* clean all pending statuses */
	ग_लिखोl(status | REG_RXSTA_CLEARALL, ir->base + SUNXI_IR_RXSTA_REG);

	अगर (status & (REG_RXSTA_RA | REG_RXSTA_RPE)) अणु
		/* How many messages in fअगरo */
		rc  = REG_RXSTA_GET_AC(status);
		/* Sanity check */
		rc = rc > ir->fअगरo_size ? ir->fअगरo_size : rc;
		/* If we have data */
		क्रम (cnt = 0; cnt < rc; cnt++) अणु
			/* क्रम each bit in fअगरo */
			dt = पढ़ोb(ir->base + SUNXI_IR_RXFIFO_REG);
			rawir.pulse = (dt & 0x80) != 0;
			rawir.duration = ((dt & 0x7f) + 1) *
					 ir->rc->rx_resolution;
			ir_raw_event_store_with_filter(ir->rc, &rawir);
		पूर्ण
	पूर्ण

	अगर (status & REG_RXSTA_ROI) अणु
		ir_raw_event_reset(ir->rc);
	पूर्ण अन्यथा अगर (status & REG_RXSTA_RPE) अणु
		ir_raw_event_set_idle(ir->rc, true);
		ir_raw_event_handle(ir->rc);
	पूर्ण अन्यथा अणु
		ir_raw_event_handle(ir->rc);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Convert idle threshold to usec */
अटल अचिन्हित पूर्णांक sunxi_ithr_to_usec(अचिन्हित पूर्णांक base_clk, अचिन्हित पूर्णांक ithr)
अणु
	वापस DIV_ROUND_CLOSEST(USEC_PER_SEC * (ithr + 1),
				 base_clk / (128 * 64));
पूर्ण

/* Convert usec to idle threshold */
अटल अचिन्हित पूर्णांक sunxi_usec_to_ithr(अचिन्हित पूर्णांक base_clk, अचिन्हित पूर्णांक usec)
अणु
	/* make sure we करोn't end up with a समयout less than requested */
	वापस DIV_ROUND_UP((base_clk / (128 * 64)) * usec,  USEC_PER_SEC) - 1;
पूर्ण

अटल पूर्णांक sunxi_ir_set_समयout(काष्ठा rc_dev *rc_dev, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sunxi_ir *ir = rc_dev->priv;
	अचिन्हित पूर्णांक base_clk = clk_get_rate(ir->clk);

	अचिन्हित पूर्णांक ithr = sunxi_usec_to_ithr(base_clk, समयout);

	dev_dbg(rc_dev->dev.parent, "setting idle threshold to %u\n", ithr);

	/* Set noise threshold and idle threshold */
	ग_लिखोl(REG_CIR_NTHR(SUNXI_IR_RXNOISE) | REG_CIR_ITHR(ithr),
	       ir->base + SUNXI_IR_CIR_REG);

	rc_dev->समयout = sunxi_ithr_to_usec(base_clk, ithr);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_ir_hw_init(काष्ठा device *dev)
अणु
	काष्ठा sunxi_ir *ir = dev_get_drvdata(dev);
	u32 पंचांगp;
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(ir->rst);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(ir->apb_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable apb clk\n");
		जाओ निकास_निश्चित_reset;
	पूर्ण

	ret = clk_prepare_enable(ir->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ir clk\n");
		जाओ निकास_disable_apb_clk;
	पूर्ण

	/* Enable CIR Mode */
	ग_लिखोl(REG_CTL_MD, ir->base + SUNXI_IR_CTL_REG);

	/* Set noise threshold and idle threshold */
	sunxi_ir_set_समयout(ir->rc, ir->rc->समयout);

	/* Invert Input Signal */
	ग_लिखोl(REG_RXCTL_RPPI, ir->base + SUNXI_IR_RXCTL_REG);

	/* Clear All Rx Interrupt Status */
	ग_लिखोl(REG_RXSTA_CLEARALL, ir->base + SUNXI_IR_RXSTA_REG);

	/*
	 * Enable IRQ on overflow, packet end, FIFO available with trigger
	 * level
	 */
	ग_लिखोl(REG_RXINT_ROI_EN | REG_RXINT_RPEI_EN |
	       REG_RXINT_RAI_EN | REG_RXINT_RAL(ir->fअगरo_size / 2 - 1),
	       ir->base + SUNXI_IR_RXINT_REG);

	/* Enable IR Module */
	पंचांगp = पढ़ोl(ir->base + SUNXI_IR_CTL_REG);
	ग_लिखोl(पंचांगp | REG_CTL_GEN | REG_CTL_RXEN, ir->base + SUNXI_IR_CTL_REG);

	वापस 0;

निकास_disable_apb_clk:
	clk_disable_unprepare(ir->apb_clk);
निकास_निश्चित_reset:
	reset_control_निश्चित(ir->rst);

	वापस ret;
पूर्ण

अटल व्योम sunxi_ir_hw_निकास(काष्ठा device *dev)
अणु
	काष्ठा sunxi_ir *ir = dev_get_drvdata(dev);

	clk_disable_unprepare(ir->clk);
	clk_disable_unprepare(ir->apb_clk);
	reset_control_निश्चित(ir->rst);
पूर्ण

अटल पूर्णांक __maybe_unused sunxi_ir_suspend(काष्ठा device *dev)
अणु
	sunxi_ir_hw_निकास(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sunxi_ir_resume(काष्ठा device *dev)
अणु
	वापस sunxi_ir_hw_init(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sunxi_ir_pm_ops, sunxi_ir_suspend, sunxi_ir_resume);

अटल पूर्णांक sunxi_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;

	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = dev->of_node;
	स्थिर काष्ठा sunxi_ir_quirks *quirks;
	काष्ठा resource *res;
	काष्ठा sunxi_ir *ir;
	u32 b_clk_freq = SUNXI_IR_BASE_CLK;

	ir = devm_kzalloc(dev, माप(काष्ठा sunxi_ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;

	quirks = of_device_get_match_data(&pdev->dev);
	अगर (!quirks) अणु
		dev_err(&pdev->dev, "Failed to determine the quirks to use\n");
		वापस -ENODEV;
	पूर्ण

	ir->fअगरo_size = quirks->fअगरo_size;

	/* Clock */
	ir->apb_clk = devm_clk_get(dev, "apb");
	अगर (IS_ERR(ir->apb_clk)) अणु
		dev_err(dev, "failed to get a apb clock.\n");
		वापस PTR_ERR(ir->apb_clk);
	पूर्ण
	ir->clk = devm_clk_get(dev, "ir");
	अगर (IS_ERR(ir->clk)) अणु
		dev_err(dev, "failed to get a ir clock.\n");
		वापस PTR_ERR(ir->clk);
	पूर्ण

	/* Base घड़ी frequency (optional) */
	of_property_पढ़ो_u32(dn, "clock-frequency", &b_clk_freq);

	/* Reset */
	अगर (quirks->has_reset) अणु
		ir->rst = devm_reset_control_get_exclusive(dev, शून्य);
		अगर (IS_ERR(ir->rst))
			वापस PTR_ERR(ir->rst);
	पूर्ण

	ret = clk_set_rate(ir->clk, b_clk_freq);
	अगर (ret) अणु
		dev_err(dev, "set ir base clock failed!\n");
		वापस ret;
	पूर्ण
	dev_dbg(dev, "set base clock frequency to %d Hz.\n", b_clk_freq);

	/* IO */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ir->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ir->base)) अणु
		वापस PTR_ERR(ir->base);
	पूर्ण

	ir->rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!ir->rc) अणु
		dev_err(dev, "failed to allocate device\n");
		वापस -ENOMEM;
	पूर्ण

	ir->rc->priv = ir;
	ir->rc->device_name = SUNXI_IR_DEV;
	ir->rc->input_phys = "sunxi-ir/input0";
	ir->rc->input_id.bustype = BUS_HOST;
	ir->rc->input_id.venकरोr = 0x0001;
	ir->rc->input_id.product = 0x0001;
	ir->rc->input_id.version = 0x0100;
	ir->map_name = of_get_property(dn, "linux,rc-map-name", शून्य);
	ir->rc->map_name = ir->map_name ?: RC_MAP_EMPTY;
	ir->rc->dev.parent = dev;
	ir->rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	/* Frequency after IR पूर्णांकernal भागider with sample period in us */
	ir->rc->rx_resolution = (USEC_PER_SEC / (b_clk_freq / 64));
	ir->rc->समयout = IR_DEFAULT_TIMEOUT;
	ir->rc->min_समयout = sunxi_ithr_to_usec(b_clk_freq, 0);
	ir->rc->max_समयout = sunxi_ithr_to_usec(b_clk_freq, 255);
	ir->rc->s_समयout = sunxi_ir_set_समयout;
	ir->rc->driver_name = SUNXI_IR_DEV;

	ret = rc_रेजिस्टर_device(ir->rc);
	अगर (ret) अणु
		dev_err(dev, "failed to register rc device\n");
		जाओ निकास_मुक्त_dev;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ir);

	/* IRQ */
	ir->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ir->irq < 0) अणु
		ret = ir->irq;
		जाओ निकास_मुक्त_dev;
	पूर्ण

	ret = devm_request_irq(dev, ir->irq, sunxi_ir_irq, 0, SUNXI_IR_DEV, ir);
	अगर (ret) अणु
		dev_err(dev, "failed request irq\n");
		जाओ निकास_मुक्त_dev;
	पूर्ण

	ret = sunxi_ir_hw_init(dev);
	अगर (ret)
		जाओ निकास_मुक्त_dev;

	dev_info(dev, "initialized sunXi IR driver\n");
	वापस 0;

निकास_मुक्त_dev:
	rc_मुक्त_device(ir->rc);

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_ir_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_ir *ir = platक्रमm_get_drvdata(pdev);

	rc_unरेजिस्टर_device(ir->rc);
	sunxi_ir_hw_निकास(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम sunxi_ir_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	sunxi_ir_hw_निकास(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा sunxi_ir_quirks sun4i_a10_ir_quirks = अणु
	.has_reset = false,
	.fअगरo_size = 16,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ir_quirks sun5i_a13_ir_quirks = अणु
	.has_reset = false,
	.fअगरo_size = 64,
पूर्ण;

अटल स्थिर काष्ठा sunxi_ir_quirks sun6i_a31_ir_quirks = अणु
	.has_reset = true,
	.fअगरo_size = 64,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_ir_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-ir",
		.data = &sun4i_a10_ir_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun5i-a13-ir",
		.data = &sun5i_a13_ir_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun6i-a31-ir",
		.data = &sun6i_a31_ir_quirks,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_ir_match);

अटल काष्ठा platक्रमm_driver sunxi_ir_driver = अणु
	.probe          = sunxi_ir_probe,
	.हटाओ         = sunxi_ir_हटाओ,
	.shutकरोwn       = sunxi_ir_shutकरोwn,
	.driver = अणु
		.name = SUNXI_IR_DEV,
		.of_match_table = sunxi_ir_match,
		.pm = &sunxi_ir_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sunxi_ir_driver);

MODULE_DESCRIPTION("Allwinner sunXi IR controller driver");
MODULE_AUTHOR("Alexsey Shestacov <wingrime@linux-sunxi.org>");
MODULE_LICENSE("GPL");
