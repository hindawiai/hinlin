<शैली गुरु>
/*
 * drivers/watchकरोg/orion_wdt.c
 *
 * Watchकरोg driver क्रम Orion/Kirkwood processors
 *
 * Author: Sylver Bruneau <sylver.bruneau@googlemail.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/* RSTOUT mask रेजिस्टर physical address क्रम Orion5x, Kirkwood and Dove */
#घोषणा ORION_RSTOUT_MASK_OFFSET	0x20108

/* Internal रेजिस्टरs can be configured at any 1 MiB aligned address */
#घोषणा INTERNAL_REGS_MASK		~(SZ_1M - 1)

/*
 * Watchकरोg समयr block रेजिस्टरs.
 */
#घोषणा TIMER_CTRL		0x0000
#घोषणा TIMER1_FIXED_ENABLE_BIT	BIT(12)
#घोषणा WDT_AXP_FIXED_ENABLE_BIT BIT(10)
#घोषणा TIMER1_ENABLE_BIT	BIT(2)

#घोषणा TIMER_A370_STATUS	0x0004
#घोषणा WDT_A370_EXPIRED	BIT(31)
#घोषणा TIMER1_STATUS_BIT	BIT(8)

#घोषणा TIMER1_VAL_OFF		0x001c

#घोषणा WDT_MAX_CYCLE_COUNT	0xffffffff

#घोषणा WDT_A370_RATIO_MASK(v)	((v) << 16)
#घोषणा WDT_A370_RATIO_SHIFT	5
#घोषणा WDT_A370_RATIO		(1 << WDT_A370_RATIO_SHIFT)

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल पूर्णांक heartbeat;		/* module parameter (seconds) */

काष्ठा orion_watchकरोg;

काष्ठा orion_watchकरोg_data अणु
	पूर्णांक wdt_counter_offset;
	पूर्णांक wdt_enable_bit;
	पूर्णांक rstout_enable_bit;
	पूर्णांक rstout_mask_bit;
	पूर्णांक (*घड़ी_init)(काष्ठा platक्रमm_device *,
			  काष्ठा orion_watchकरोg *);
	पूर्णांक (*enabled)(काष्ठा orion_watchकरोg *);
	पूर्णांक (*start)(काष्ठा watchकरोg_device *);
	पूर्णांक (*stop)(काष्ठा watchकरोg_device *);
पूर्ण;

काष्ठा orion_watchकरोg अणु
	काष्ठा watchकरोg_device wdt;
	व्योम __iomem *reg;
	व्योम __iomem *rstout;
	व्योम __iomem *rstout_mask;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा clk *clk;
	स्थिर काष्ठा orion_watchकरोg_data *data;
पूर्ण;

अटल पूर्णांक orion_wdt_घड़ी_init(काष्ठा platक्रमm_device *pdev,
				काष्ठा orion_watchकरोg *dev)
अणु
	पूर्णांक ret;

	dev->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);
	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		clk_put(dev->clk);
		वापस ret;
	पूर्ण

	dev->clk_rate = clk_get_rate(dev->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक armada370_wdt_घड़ी_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा orion_watchकरोg *dev)
अणु
	पूर्णांक ret;

	dev->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);
	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		clk_put(dev->clk);
		वापस ret;
	पूर्ण

	/* Setup watchकरोg input घड़ी */
	atomic_io_modअगरy(dev->reg + TIMER_CTRL,
			WDT_A370_RATIO_MASK(WDT_A370_RATIO_SHIFT),
			WDT_A370_RATIO_MASK(WDT_A370_RATIO_SHIFT));

	dev->clk_rate = clk_get_rate(dev->clk) / WDT_A370_RATIO;
	वापस 0;
पूर्ण

अटल पूर्णांक armada375_wdt_घड़ी_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा orion_watchकरोg *dev)
अणु
	पूर्णांक ret;

	dev->clk = of_clk_get_by_name(pdev->dev.of_node, "fixed");
	अगर (!IS_ERR(dev->clk)) अणु
		ret = clk_prepare_enable(dev->clk);
		अगर (ret) अणु
			clk_put(dev->clk);
			वापस ret;
		पूर्ण

		atomic_io_modअगरy(dev->reg + TIMER_CTRL,
				WDT_AXP_FIXED_ENABLE_BIT,
				WDT_AXP_FIXED_ENABLE_BIT);
		dev->clk_rate = clk_get_rate(dev->clk);

		वापस 0;
	पूर्ण

	/* Mandatory fallback क्रम proper devicetree backward compatibility */
	dev->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);

	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		clk_put(dev->clk);
		वापस ret;
	पूर्ण

	atomic_io_modअगरy(dev->reg + TIMER_CTRL,
			WDT_A370_RATIO_MASK(WDT_A370_RATIO_SHIFT),
			WDT_A370_RATIO_MASK(WDT_A370_RATIO_SHIFT));
	dev->clk_rate = clk_get_rate(dev->clk) / WDT_A370_RATIO;

	वापस 0;
पूर्ण

अटल पूर्णांक armadaxp_wdt_घड़ी_init(काष्ठा platक्रमm_device *pdev,
				   काष्ठा orion_watchकरोg *dev)
अणु
	पूर्णांक ret;
	u32 val;

	dev->clk = of_clk_get_by_name(pdev->dev.of_node, "fixed");
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);
	ret = clk_prepare_enable(dev->clk);
	अगर (ret) अणु
		clk_put(dev->clk);
		वापस ret;
	पूर्ण

	/* Fix the wdt and समयr1 घड़ी freqency to 25MHz */
	val = WDT_AXP_FIXED_ENABLE_BIT | TIMER1_FIXED_ENABLE_BIT;
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, val, val);

	dev->clk_rate = clk_get_rate(dev->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक orion_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);
	/* Reload watchकरोg duration */
	ग_लिखोl(dev->clk_rate * wdt_dev->समयout,
	       dev->reg + dev->data->wdt_counter_offset);
	अगर (dev->wdt.info->options & WDIOF_PRETIMEOUT)
		ग_लिखोl(dev->clk_rate * (wdt_dev->समयout - wdt_dev->preसमयout),
		       dev->reg + TIMER1_VAL_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक armada375_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);
	u32 reg;

	/* Set watchकरोg duration */
	ग_लिखोl(dev->clk_rate * wdt_dev->समयout,
	       dev->reg + dev->data->wdt_counter_offset);
	अगर (dev->wdt.info->options & WDIOF_PRETIMEOUT)
		ग_लिखोl(dev->clk_rate * (wdt_dev->समयout - wdt_dev->preसमयout),
		       dev->reg + TIMER1_VAL_OFF);

	/* Clear the watchकरोg expiration bit */
	atomic_io_modअगरy(dev->reg + TIMER_A370_STATUS, WDT_A370_EXPIRED, 0);

	/* Enable watchकरोg समयr */
	reg = dev->data->wdt_enable_bit;
	अगर (dev->wdt.info->options & WDIOF_PRETIMEOUT)
		reg |= TIMER1_ENABLE_BIT;
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, reg, reg);

	/* Enable reset on watchकरोg */
	reg = पढ़ोl(dev->rstout);
	reg |= dev->data->rstout_enable_bit;
	ग_लिखोl(reg, dev->rstout);

	atomic_io_modअगरy(dev->rstout_mask, dev->data->rstout_mask_bit, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक armada370_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);
	u32 reg;

	/* Set watchकरोg duration */
	ग_लिखोl(dev->clk_rate * wdt_dev->समयout,
	       dev->reg + dev->data->wdt_counter_offset);

	/* Clear the watchकरोg expiration bit */
	atomic_io_modअगरy(dev->reg + TIMER_A370_STATUS, WDT_A370_EXPIRED, 0);

	/* Enable watchकरोg समयr */
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit,
						dev->data->wdt_enable_bit);

	/* Enable reset on watchकरोg */
	reg = पढ़ोl(dev->rstout);
	reg |= dev->data->rstout_enable_bit;
	ग_लिखोl(reg, dev->rstout);
	वापस 0;
पूर्ण

अटल पूर्णांक orion_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);

	/* Set watchकरोg duration */
	ग_लिखोl(dev->clk_rate * wdt_dev->समयout,
	       dev->reg + dev->data->wdt_counter_offset);

	/* Enable watchकरोg समयr */
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit,
						dev->data->wdt_enable_bit);

	/* Enable reset on watchकरोg */
	atomic_io_modअगरy(dev->rstout, dev->data->rstout_enable_bit,
				      dev->data->rstout_enable_bit);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);

	/* There are some per-SoC quirks to handle */
	वापस dev->data->start(wdt_dev);
पूर्ण

अटल पूर्णांक orion_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);

	/* Disable reset on watchकरोg */
	atomic_io_modअगरy(dev->rstout, dev->data->rstout_enable_bit, 0);

	/* Disable watchकरोg समयr */
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक armada375_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);
	u32 reg, mask;

	/* Disable reset on watchकरोg */
	atomic_io_modअगरy(dev->rstout_mask, dev->data->rstout_mask_bit,
					   dev->data->rstout_mask_bit);
	reg = पढ़ोl(dev->rstout);
	reg &= ~dev->data->rstout_enable_bit;
	ग_लिखोl(reg, dev->rstout);

	/* Disable watchकरोg समयr */
	mask = dev->data->wdt_enable_bit;
	अगर (wdt_dev->info->options & WDIOF_PRETIMEOUT)
		mask |= TIMER1_ENABLE_BIT;
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, mask, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक armada370_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);
	u32 reg;

	/* Disable reset on watchकरोg */
	reg = पढ़ोl(dev->rstout);
	reg &= ~dev->data->rstout_enable_bit;
	ग_लिखोl(reg, dev->rstout);

	/* Disable watchकरोg समयr */
	atomic_io_modअगरy(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);

	वापस dev->data->stop(wdt_dev);
पूर्ण

अटल पूर्णांक orion_enabled(काष्ठा orion_watchकरोg *dev)
अणु
	bool enabled, running;

	enabled = पढ़ोl(dev->rstout) & dev->data->rstout_enable_bit;
	running = पढ़ोl(dev->reg + TIMER_CTRL) & dev->data->wdt_enable_bit;

	वापस enabled && running;
पूर्ण

अटल पूर्णांक armada375_enabled(काष्ठा orion_watchकरोg *dev)
अणु
	bool masked, enabled, running;

	masked = पढ़ोl(dev->rstout_mask) & dev->data->rstout_mask_bit;
	enabled = पढ़ोl(dev->rstout) & dev->data->rstout_enable_bit;
	running = पढ़ोl(dev->reg + TIMER_CTRL) & dev->data->wdt_enable_bit;

	वापस !masked && enabled && running;
पूर्ण

अटल पूर्णांक orion_wdt_enabled(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);

	वापस dev->data->enabled(dev);
पूर्ण

अटल अचिन्हित पूर्णांक orion_wdt_get_समयleft(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);
	वापस पढ़ोl(dev->reg + dev->data->wdt_counter_offset) / dev->clk_rate;
पूर्ण

अटल काष्ठा watchकरोg_info orion_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "Orion Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops orion_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = orion_wdt_start,
	.stop = orion_wdt_stop,
	.ping = orion_wdt_ping,
	.get_समयleft = orion_wdt_get_समयleft,
पूर्ण;

अटल irqवापस_t orion_wdt_irq(पूर्णांक irq, व्योम *devid)
अणु
	panic("Watchdog Timeout");
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t orion_wdt_pre_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा orion_watchकरोg *dev = devid;

	atomic_io_modअगरy(dev->reg + TIMER_A370_STATUS,
			 TIMER1_STATUS_BIT, 0);
	watchकरोg_notअगरy_preसमयout(&dev->wdt);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * The original devicetree binding क्रम this driver specअगरied only
 * one memory resource, so in order to keep DT backwards compatibility
 * we try to fallback to a hardcoded रेजिस्टर address, अगर the resource
 * is missing from the devicetree.
 */
अटल व्योम __iomem *orion_wdt_ioremap_rstout(काष्ठा platक्रमm_device *pdev,
					      phys_addr_t पूर्णांकernal_regs)
अणु
	काष्ठा resource *res;
	phys_addr_t rstout;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res)
		वापस devm_ioremap(&pdev->dev, res->start,
				    resource_size(res));

	rstout = पूर्णांकernal_regs + ORION_RSTOUT_MASK_OFFSET;

	WARN(1, FW_BUG "falling back to hardcoded RSTOUT reg %pa\n", &rstout);
	वापस devm_ioremap(&pdev->dev, rstout, 0x4);
पूर्ण

अटल स्थिर काष्ठा orion_watchकरोg_data orion_data = अणु
	.rstout_enable_bit = BIT(1),
	.wdt_enable_bit = BIT(4),
	.wdt_counter_offset = 0x24,
	.घड़ी_init = orion_wdt_घड़ी_init,
	.enabled = orion_enabled,
	.start = orion_start,
	.stop = orion_stop,
पूर्ण;

अटल स्थिर काष्ठा orion_watchकरोg_data armada370_data = अणु
	.rstout_enable_bit = BIT(8),
	.wdt_enable_bit = BIT(8),
	.wdt_counter_offset = 0x34,
	.घड़ी_init = armada370_wdt_घड़ी_init,
	.enabled = orion_enabled,
	.start = armada370_start,
	.stop = armada370_stop,
पूर्ण;

अटल स्थिर काष्ठा orion_watchकरोg_data armadaxp_data = अणु
	.rstout_enable_bit = BIT(8),
	.wdt_enable_bit = BIT(8),
	.wdt_counter_offset = 0x34,
	.घड़ी_init = armadaxp_wdt_घड़ी_init,
	.enabled = orion_enabled,
	.start = armada370_start,
	.stop = armada370_stop,
पूर्ण;

अटल स्थिर काष्ठा orion_watchकरोg_data armada375_data = अणु
	.rstout_enable_bit = BIT(8),
	.rstout_mask_bit = BIT(10),
	.wdt_enable_bit = BIT(8),
	.wdt_counter_offset = 0x34,
	.घड़ी_init = armada375_wdt_घड़ी_init,
	.enabled = armada375_enabled,
	.start = armada375_start,
	.stop = armada375_stop,
पूर्ण;

अटल स्थिर काष्ठा orion_watchकरोg_data armada380_data = अणु
	.rstout_enable_bit = BIT(8),
	.rstout_mask_bit = BIT(10),
	.wdt_enable_bit = BIT(8),
	.wdt_counter_offset = 0x34,
	.घड़ी_init = armadaxp_wdt_घड़ी_init,
	.enabled = armada375_enabled,
	.start = armada375_start,
	.stop = armada375_stop,
पूर्ण;

अटल स्थिर काष्ठा of_device_id orion_wdt_of_match_table[] = अणु
	अणु
		.compatible = "marvell,orion-wdt",
		.data = &orion_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-370-wdt",
		.data = &armada370_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-xp-wdt",
		.data = &armadaxp_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-375-wdt",
		.data = &armada375_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-380-wdt",
		.data = &armada380_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, orion_wdt_of_match_table);

अटल पूर्णांक orion_wdt_get_regs(काष्ठा platक्रमm_device *pdev,
			      काष्ठा orion_watchकरोg *dev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	dev->reg = devm_ioremap(&pdev->dev, res->start,
				resource_size(res));
	अगर (!dev->reg)
		वापस -ENOMEM;

	/* Each supported compatible has some RSTOUT रेजिस्टर quirk */
	अगर (of_device_is_compatible(node, "marvell,orion-wdt")) अणु

		dev->rstout = orion_wdt_ioremap_rstout(pdev, res->start &
						       INTERNAL_REGS_MASK);
		अगर (!dev->rstout)
			वापस -ENODEV;

	पूर्ण अन्यथा अगर (of_device_is_compatible(node, "marvell,armada-370-wdt") ||
		   of_device_is_compatible(node, "marvell,armada-xp-wdt")) अणु

		/* Dedicated RSTOUT रेजिस्टर, can be requested. */
		dev->rstout = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(dev->rstout))
			वापस PTR_ERR(dev->rstout);

	पूर्ण अन्यथा अगर (of_device_is_compatible(node, "marvell,armada-375-wdt") ||
		   of_device_is_compatible(node, "marvell,armada-380-wdt")) अणु

		/* Dedicated RSTOUT रेजिस्टर, can be requested. */
		dev->rstout = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(dev->rstout))
			वापस PTR_ERR(dev->rstout);

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
		अगर (!res)
			वापस -ENODEV;
		dev->rstout_mask = devm_ioremap(&pdev->dev, res->start,
						resource_size(res));
		अगर (!dev->rstout_mask)
			वापस -ENOMEM;

	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक orion_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा orion_watchकरोg *dev;
	स्थिर काष्ठा of_device_id *match;
	अचिन्हित पूर्णांक wdt_max_duration;	/* (seconds) */
	पूर्णांक ret, irq;

	dev = devm_kzalloc(&pdev->dev, माप(काष्ठा orion_watchकरोg),
			   GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	match = of_match_device(orion_wdt_of_match_table, &pdev->dev);
	अगर (!match)
		/* Default legacy match */
		match = &orion_wdt_of_match_table[0];

	dev->wdt.info = &orion_wdt_info;
	dev->wdt.ops = &orion_wdt_ops;
	dev->wdt.min_समयout = 1;
	dev->data = match->data;

	ret = orion_wdt_get_regs(pdev, dev);
	अगर (ret)
		वापस ret;

	ret = dev->data->घड़ी_init(pdev, dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot initialize clock\n");
		वापस ret;
	पूर्ण

	wdt_max_duration = WDT_MAX_CYCLE_COUNT / dev->clk_rate;

	dev->wdt.समयout = wdt_max_duration;
	dev->wdt.max_समयout = wdt_max_duration;
	dev->wdt.parent = &pdev->dev;
	watchकरोg_init_समयout(&dev->wdt, heartbeat, &pdev->dev);

	platक्रमm_set_drvdata(pdev, &dev->wdt);
	watchकरोg_set_drvdata(&dev->wdt, dev);

	/*
	 * Let's make sure the watchdog is fully stopped, unless it's
	 * explicitly enabled. This may be the हाल अगर the module was
	 * हटाओd and re-inserted, or अगर the bootloader explicitly
	 * set a running watchकरोg beक्रमe booting the kernel.
	 */
	अगर (!orion_wdt_enabled(&dev->wdt))
		orion_wdt_stop(&dev->wdt);
	अन्यथा
		set_bit(WDOG_HW_RUNNING, &dev->wdt.status);

	/* Request the IRQ only after the watchकरोg is disabled */
	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq > 0) अणु
		/*
		 * Not all supported platक्रमms specअगरy an पूर्णांकerrupt क्रम the
		 * watchकरोg, so let's make it optional.
		 */
		ret = devm_request_irq(&pdev->dev, irq, orion_wdt_irq, 0,
				       pdev->name, dev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to request IRQ\n");
			जाओ disable_clk;
		पूर्ण
	पूर्ण

	/* Optional 2nd पूर्णांकerrupt क्रम preसमयout */
	irq = platक्रमm_get_irq_optional(pdev, 1);
	अगर (irq > 0) अणु
		orion_wdt_info.options |= WDIOF_PRETIMEOUT;
		ret = devm_request_irq(&pdev->dev, irq, orion_wdt_pre_irq,
				       0, pdev->name, dev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to request IRQ\n");
			जाओ disable_clk;
		पूर्ण
	पूर्ण


	watchकरोg_set_nowayout(&dev->wdt, nowayout);
	ret = watchकरोg_रेजिस्टर_device(&dev->wdt);
	अगर (ret)
		जाओ disable_clk;

	pr_info("Initial timeout %d sec%s\n",
		dev->wdt.समयout, nowayout ? ", nowayout" : "");
	वापस 0;

disable_clk:
	clk_disable_unprepare(dev->clk);
	clk_put(dev->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक orion_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wdt_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा orion_watchकरोg *dev = watchकरोg_get_drvdata(wdt_dev);

	watchकरोg_unरेजिस्टर_device(wdt_dev);
	clk_disable_unprepare(dev->clk);
	clk_put(dev->clk);
	वापस 0;
पूर्ण

अटल व्योम orion_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wdt_dev = platक्रमm_get_drvdata(pdev);
	orion_wdt_stop(wdt_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver orion_wdt_driver = अणु
	.probe		= orion_wdt_probe,
	.हटाओ		= orion_wdt_हटाओ,
	.shutकरोwn	= orion_wdt_shutकरोwn,
	.driver		= अणु
		.name	= "orion_wdt",
		.of_match_table = orion_wdt_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(orion_wdt_driver);

MODULE_AUTHOR("Sylver Bruneau <sylver.bruneau@googlemail.com>");
MODULE_DESCRIPTION("Orion Processor Watchdog");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Initial watchdog heartbeat in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:orion_wdt");
