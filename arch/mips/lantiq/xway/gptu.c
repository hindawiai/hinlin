<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 *  Copyright (C) 2012 Lantiq GmbH
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>

#समावेश <lantiq_soc.h>
#समावेश "../clk.h"

/* the magic ID byte of the core */
#घोषणा GPTU_MAGIC	0x59
/* घड़ी control रेजिस्टर */
#घोषणा GPTU_CLC	0x00
/* id रेजिस्टर */
#घोषणा GPTU_ID		0x08
/* पूर्णांकerrupt node enable */
#घोषणा GPTU_IRNEN	0xf4
/* पूर्णांकerrupt control रेजिस्टर */
#घोषणा GPTU_IRCR	0xf8
/* पूर्णांकerrupt capture रेजिस्टर */
#घोषणा GPTU_IRNCR	0xfc
/* there are 3 identical blocks of 2 समयrs. calculate रेजिस्टर offsets */
#घोषणा GPTU_SHIFT(x)	(x % 2 ? 4 : 0)
#घोषणा GPTU_BASE(x)	(((x >> 1) * 0x20) + 0x10)
/* समयr control रेजिस्टर */
#घोषणा GPTU_CON(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x00)
/* समयr स्वतः reload रेजिस्टर */
#घोषणा GPTU_RUN(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x08)
/* समयr manual reload रेजिस्टर */
#घोषणा GPTU_RLD(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x10)
/* समयr count रेजिस्टर */
#घोषणा GPTU_CNT(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x18)

/* GPTU_CON(x) */
#घोषणा CON_CNT		BIT(2)
#घोषणा CON_EDGE_ANY	(BIT(7) | BIT(6))
#घोषणा CON_SYNC	BIT(8)
#घोषणा CON_CLK_INT	BIT(10)

/* GPTU_RUN(x) */
#घोषणा RUN_SEN		BIT(0)
#घोषणा RUN_RL		BIT(2)

/* set घड़ी to runmode */
#घोषणा CLC_RMC		BIT(8)
/* bring core out of suspend */
#घोषणा CLC_SUSPEND	BIT(4)
/* the disable bit */
#घोषणा CLC_DISABLE	BIT(0)

#घोषणा gptu_w32(x, y)	ltq_w32((x), gptu_membase + (y))
#घोषणा gptu_r32(x)	ltq_r32(gptu_membase + (x))

क्रमागत gptu_समयr अणु
	TIMER1A = 0,
	TIMER1B,
	TIMER2A,
	TIMER2B,
	TIMER3A,
	TIMER3B
पूर्ण;

अटल व्योम __iomem *gptu_membase;
अटल काष्ठा resource irqres[6];

अटल irqवापस_t समयr_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	पूर्णांक समयr = irq - irqres[0].start;
	gptu_w32(1 << समयr, GPTU_IRNCR);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम gptu_hwinit(व्योम)
अणु
	gptu_w32(0x00, GPTU_IRNEN);
	gptu_w32(0xff, GPTU_IRNCR);
	gptu_w32(CLC_RMC | CLC_SUSPEND, GPTU_CLC);
पूर्ण

अटल व्योम gptu_hwनिकास(व्योम)
अणु
	gptu_w32(0x00, GPTU_IRNEN);
	gptu_w32(0xff, GPTU_IRNCR);
	gptu_w32(CLC_DISABLE, GPTU_CLC);
पूर्ण

अटल पूर्णांक gptu_enable(काष्ठा clk *clk)
अणु
	पूर्णांक ret = request_irq(irqres[clk->bits].start, समयr_irq_handler,
		IRQF_TIMER, "gtpu", शून्य);
	अगर (ret) अणु
		pr_err("gptu: failed to request irq\n");
		वापस ret;
	पूर्ण

	gptu_w32(CON_CNT | CON_EDGE_ANY | CON_SYNC | CON_CLK_INT,
		GPTU_CON(clk->bits));
	gptu_w32(1, GPTU_RLD(clk->bits));
	gptu_w32(gptu_r32(GPTU_IRNEN) | BIT(clk->bits), GPTU_IRNEN);
	gptu_w32(RUN_SEN | RUN_RL, GPTU_RUN(clk->bits));
	वापस 0;
पूर्ण

अटल व्योम gptu_disable(काष्ठा clk *clk)
अणु
	gptu_w32(0, GPTU_RUN(clk->bits));
	gptu_w32(0, GPTU_CON(clk->bits));
	gptu_w32(0, GPTU_RLD(clk->bits));
	gptu_w32(gptu_r32(GPTU_IRNEN) & ~BIT(clk->bits), GPTU_IRNEN);
	मुक्त_irq(irqres[clk->bits].start, शून्य);
पूर्ण

अटल अंतरभूत व्योम clkdev_add_gptu(काष्ठा device *dev, स्थिर अक्षर *con,
							अचिन्हित पूर्णांक समयr)
अणु
	काष्ठा clk *clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);

	clk->cl.dev_id = dev_name(dev);
	clk->cl.con_id = con;
	clk->cl.clk = clk;
	clk->enable = gptu_enable;
	clk->disable = gptu_disable;
	clk->bits = समयr;
	clkdev_add(&clk->cl);
पूर्ण

अटल पूर्णांक gptu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *clk;
	काष्ठा resource *res;

	अगर (of_irq_to_resource_table(pdev->dev.of_node, irqres, 6) != 6) अणु
		dev_err(&pdev->dev, "Failed to get IRQ list\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	/* remap gptu रेजिस्टर range */
	gptu_membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(gptu_membase))
		वापस PTR_ERR(gptu_membase);

	/* enable our घड़ी */
	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Failed to get clock\n");
		वापस -ENOENT;
	पूर्ण
	clk_enable(clk);

	/* घातer up the core */
	gptu_hwinit();

	/* the gptu has a ID रेजिस्टर */
	अगर (((gptu_r32(GPTU_ID) >> 8) & 0xff) != GPTU_MAGIC) अणु
		dev_err(&pdev->dev, "Failed to find magic\n");
		gptu_hwनिकास();
		clk_disable(clk);
		clk_put(clk);
		वापस -ENAVAIL;
	पूर्ण

	/* रेजिस्टर the घड़ीs */
	clkdev_add_gptu(&pdev->dev, "timer1a", TIMER1A);
	clkdev_add_gptu(&pdev->dev, "timer1b", TIMER1B);
	clkdev_add_gptu(&pdev->dev, "timer2a", TIMER2A);
	clkdev_add_gptu(&pdev->dev, "timer2b", TIMER2B);
	clkdev_add_gptu(&pdev->dev, "timer3a", TIMER3A);
	clkdev_add_gptu(&pdev->dev, "timer3b", TIMER3B);

	dev_info(&pdev->dev, "gptu: 6 timers loaded\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gptu_match[] = अणु
	अणु .compatible = "lantiq,gptu-xway" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver dma_driver = अणु
	.probe = gptu_probe,
	.driver = अणु
		.name = "gptu-xway",
		.of_match_table = gptu_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init gptu_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&dma_driver);

	अगर (ret)
		pr_info("gptu: Error registering platform driver\n");
	वापस ret;
पूर्ण

arch_initcall(gptu_init);
