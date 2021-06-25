<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2017 NXP

/*                     INTMUX Block Diagram
 *
 *                               ________________
 * पूर्णांकerrupt source #  0  +---->|                |
 *                        |     |                |
 * पूर्णांकerrupt source #  1  +++-->|                |
 *            ...         | |   |   channel # 0  |--------->पूर्णांकerrupt out # 0
 *            ...         | |   |                |
 *            ...         | |   |                |
 * पूर्णांकerrupt source # X-1 +++-->|________________|
 *                        | | |
 *                        | | |
 *                        | | |  ________________
 *                        +---->|                |
 *                        | | | |                |
 *                        | +-->|                |
 *                        | | | |   channel # 1  |--------->पूर्णांकerrupt out # 1
 *                        | | +>|                |
 *                        | | | |                |
 *                        | | | |________________|
 *                        | | |
 *                        | | |
 *                        | | |       ...
 *                        | | |       ...
 *                        | | |
 *                        | | |  ________________
 *                        +---->|                |
 *                          | | |                |
 *                          +-->|                |
 *                            | |   channel # N  |--------->पूर्णांकerrupt out # N
 *                            +>|                |
 *                              |                |
 *                              |________________|
 *
 *
 * N: Interrupt Channel Instance Number (N=7)
 * X: Interrupt Source Number क्रम each channel (X=32)
 *
 * The INTMUX पूर्णांकerrupt multiplexer has 8 channels, each channel receives 32
 * पूर्णांकerrupt sources and generates 1 पूर्णांकerrupt output.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा CHANIER(n)	(0x10 + (0x40 * n))
#घोषणा CHANIPR(n)	(0x20 + (0x40 * n))

#घोषणा CHAN_MAX_NUM		0x8

काष्ठा पूर्णांकmux_irqchip_data अणु
	काष्ठा irq_chip		chip;
	u32			saved_reg;
	पूर्णांक			chanidx;
	पूर्णांक			irq;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
पूर्ण;

काष्ठा पूर्णांकmux_data अणु
	raw_spinlock_t			lock;
	व्योम __iomem			*regs;
	काष्ठा clk			*ipg_clk;
	पूर्णांक				channum;
	काष्ठा पूर्णांकmux_irqchip_data	irqchip_data[];
पूर्ण;

अटल व्योम imx_पूर्णांकmux_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data = d->chip_data;
	पूर्णांक idx = irqchip_data->chanidx;
	काष्ठा पूर्णांकmux_data *data = container_of(irqchip_data, काष्ठा पूर्णांकmux_data,
						irqchip_data[idx]);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u32 val;

	raw_spin_lock_irqsave(&data->lock, flags);
	reg = data->regs + CHANIER(idx);
	val = पढ़ोl_relaxed(reg);
	/* disable the पूर्णांकerrupt source of this channel */
	val &= ~BIT(d->hwirq);
	ग_लिखोl_relaxed(val, reg);
	raw_spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल व्योम imx_पूर्णांकmux_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data = d->chip_data;
	पूर्णांक idx = irqchip_data->chanidx;
	काष्ठा पूर्णांकmux_data *data = container_of(irqchip_data, काष्ठा पूर्णांकmux_data,
						irqchip_data[idx]);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u32 val;

	raw_spin_lock_irqsave(&data->lock, flags);
	reg = data->regs + CHANIER(idx);
	val = पढ़ोl_relaxed(reg);
	/* enable the पूर्णांकerrupt source of this channel */
	val |= BIT(d->hwirq);
	ग_लिखोl_relaxed(val, reg);
	raw_spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल काष्ठा irq_chip imx_पूर्णांकmux_irq_chip = अणु
	.name		= "intmux",
	.irq_mask	= imx_पूर्णांकmux_irq_mask,
	.irq_unmask	= imx_पूर्णांकmux_irq_unmask,
पूर्ण;

अटल पूर्णांक imx_पूर्णांकmux_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hwirq)
अणु
	काष्ठा पूर्णांकmux_irqchip_data *data = h->host_data;

	irq_set_chip_data(irq, data);
	irq_set_chip_and_handler(irq, &data->chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_पूर्णांकmux_irq_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
				स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data = d->host_data;
	पूर्णांक idx = irqchip_data->chanidx;
	काष्ठा पूर्णांकmux_data *data = container_of(irqchip_data, काष्ठा पूर्णांकmux_data,
						irqchip_data[idx]);

	/*
	 * two cells needed in पूर्णांकerrupt specअगरier:
	 * the 1st cell: hw पूर्णांकerrupt number
	 * the 2nd cell: channel index
	 */
	अगर (WARN_ON(पूर्णांकsize != 2))
		वापस -EINVAL;

	अगर (WARN_ON(पूर्णांकspec[1] >= data->channum))
		वापस -EINVAL;

	*out_hwirq = पूर्णांकspec[0];
	*out_type = IRQ_TYPE_LEVEL_HIGH;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_पूर्णांकmux_irq_select(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
				 क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data = d->host_data;

	/* Not क्रम us */
	अगर (fwspec->fwnode != d->fwnode)
		वापस false;

	वापस irqchip_data->chanidx == fwspec->param[1];
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops imx_पूर्णांकmux_करोमुख्य_ops = अणु
	.map		= imx_पूर्णांकmux_irq_map,
	.xlate		= imx_पूर्णांकmux_irq_xlate,
	.select		= imx_पूर्णांकmux_irq_select,
पूर्ण;

अटल व्योम imx_पूर्णांकmux_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data = irq_desc_get_handler_data(desc);
	पूर्णांक idx = irqchip_data->chanidx;
	काष्ठा पूर्णांकmux_data *data = container_of(irqchip_data, काष्ठा पूर्णांकmux_data,
						irqchip_data[idx]);
	अचिन्हित दीर्घ irqstat;
	पूर्णांक pos, virq;

	chained_irq_enter(irq_desc_get_chip(desc), desc);

	/* पढ़ो the पूर्णांकerrupt source pending status of this channel */
	irqstat = पढ़ोl_relaxed(data->regs + CHANIPR(idx));

	क्रम_each_set_bit(pos, &irqstat, 32) अणु
		virq = irq_find_mapping(irqchip_data->करोमुख्य, pos);
		अगर (virq)
			generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(irq_desc_get_chip(desc), desc);
पूर्ण

अटल पूर्णांक imx_पूर्णांकmux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा पूर्णांकmux_data *data;
	पूर्णांक channum;
	पूर्णांक i, ret;

	channum = platक्रमm_irq_count(pdev);
	अगर (channum == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (channum > CHAN_MAX_NUM) अणु
		dev_err(&pdev->dev, "supports up to %d multiplex channels\n",
			CHAN_MAX_NUM);
		वापस -EINVAL;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, काष्ठा_size(data, irqchip_data, channum), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->regs)) अणु
		dev_err(&pdev->dev, "failed to initialize reg\n");
		वापस PTR_ERR(data->regs);
	पूर्ण

	data->ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(data->ipg_clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(data->ipg_clk),
				     "failed to get ipg clk\n");

	data->channum = channum;
	raw_spin_lock_init(&data->lock);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = clk_prepare_enable(data->ipg_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable ipg clk: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < channum; i++) अणु
		data->irqchip_data[i].chip = imx_पूर्णांकmux_irq_chip;
		data->irqchip_data[i].chip.parent_device = &pdev->dev;
		data->irqchip_data[i].chanidx = i;

		data->irqchip_data[i].irq = irq_of_parse_and_map(np, i);
		अगर (data->irqchip_data[i].irq <= 0) अणु
			ret = -EINVAL;
			dev_err(&pdev->dev, "failed to get irq\n");
			जाओ out;
		पूर्ण

		करोमुख्य = irq_करोमुख्य_add_linear(np, 32, &imx_पूर्णांकmux_करोमुख्य_ops,
					       &data->irqchip_data[i]);
		अगर (!करोमुख्य) अणु
			ret = -ENOMEM;
			dev_err(&pdev->dev, "failed to create IRQ domain\n");
			जाओ out;
		पूर्ण
		data->irqchip_data[i].करोमुख्य = करोमुख्य;

		/* disable all पूर्णांकerrupt sources of this channel firstly */
		ग_लिखोl_relaxed(0, data->regs + CHANIER(i));

		irq_set_chained_handler_and_data(data->irqchip_data[i].irq,
						 imx_पूर्णांकmux_irq_handler,
						 &data->irqchip_data[i]);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	/*
	 * Let pm_runसमय_put() disable घड़ी.
	 * If CONFIG_PM is not enabled, the घड़ी will stay घातered.
	 */
	pm_runसमय_put(&pdev->dev);

	वापस 0;
out:
	clk_disable_unprepare(data->ipg_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_पूर्णांकmux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकmux_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < data->channum; i++) अणु
		/* disable all पूर्णांकerrupt sources of this channel */
		ग_लिखोl_relaxed(0, data->regs + CHANIER(i));

		irq_set_chained_handler_and_data(data->irqchip_data[i].irq,
						 शून्य, शून्य);

		irq_करोमुख्य_हटाओ(data->irqchip_data[i].करोमुख्य);
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक imx_पूर्णांकmux_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकmux_data *data = dev_get_drvdata(dev);
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data;
	पूर्णांक i;

	क्रम (i = 0; i < data->channum; i++) अणु
		irqchip_data = &data->irqchip_data[i];
		irqchip_data->saved_reg = पढ़ोl_relaxed(data->regs + CHANIER(i));
	पूर्ण

	clk_disable_unprepare(data->ipg_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_पूर्णांकmux_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकmux_data *data = dev_get_drvdata(dev);
	काष्ठा पूर्णांकmux_irqchip_data *irqchip_data;
	पूर्णांक ret, i;

	ret = clk_prepare_enable(data->ipg_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ipg clk: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < data->channum; i++) अणु
		irqchip_data = &data->irqchip_data[i];
		ग_लिखोl_relaxed(irqchip_data->saved_reg, data->regs + CHANIER(i));
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops imx_पूर्णांकmux_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(imx_पूर्णांकmux_runसमय_suspend,
			   imx_पूर्णांकmux_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_पूर्णांकmux_id[] = अणु
	अणु .compatible = "fsl,imx-intmux", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_पूर्णांकmux_driver = अणु
	.driver = अणु
		.name = "imx-intmux",
		.of_match_table = imx_पूर्णांकmux_id,
		.pm = &imx_पूर्णांकmux_pm_ops,
	पूर्ण,
	.probe = imx_पूर्णांकmux_probe,
	.हटाओ = imx_पूर्णांकmux_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(imx_पूर्णांकmux_driver);
