<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2017 NXP
 * Copyright (C) 2018 Pengutronix, Lucas Stach <kernel@pengutronix.de>
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

#घोषणा CTRL_STRIDE_OFF(_t, _r)	(_t * 4 * _r)
#घोषणा CHANCTRL		0x0
#घोषणा CHANMASK(n, t)		(CTRL_STRIDE_OFF(t, 0) + 0x4 * (n) + 0x4)
#घोषणा CHANSET(n, t)		(CTRL_STRIDE_OFF(t, 1) + 0x4 * (n) + 0x4)
#घोषणा CHANSTATUS(n, t)	(CTRL_STRIDE_OFF(t, 2) + 0x4 * (n) + 0x4)
#घोषणा CHAN_MINTDIS(t)		(CTRL_STRIDE_OFF(t, 3) + 0x4)
#घोषणा CHAN_MASTRSTAT(t)	(CTRL_STRIDE_OFF(t, 3) + 0x8)

#घोषणा CHAN_MAX_OUTPUT_INT	0x8

काष्ठा irqsteer_data अणु
	व्योम __iomem		*regs;
	काष्ठा clk		*ipg_clk;
	पूर्णांक			irq[CHAN_MAX_OUTPUT_INT];
	पूर्णांक			irq_count;
	raw_spinlock_t		lock;
	पूर्णांक			reg_num;
	पूर्णांक			channel;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	u32			*saved_reg;
पूर्ण;

अटल पूर्णांक imx_irqsteer_get_reg_index(काष्ठा irqsteer_data *data,
				      अचिन्हित दीर्घ irqnum)
अणु
	वापस (data->reg_num - irqnum / 32 - 1);
पूर्ण

अटल व्योम imx_irqsteer_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irqsteer_data *data = d->chip_data;
	पूर्णांक idx = imx_irqsteer_get_reg_index(data, d->hwirq);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&data->lock, flags);
	val = पढ़ोl_relaxed(data->regs + CHANMASK(idx, data->reg_num));
	val |= BIT(d->hwirq % 32);
	ग_लिखोl_relaxed(val, data->regs + CHANMASK(idx, data->reg_num));
	raw_spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल व्योम imx_irqsteer_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irqsteer_data *data = d->chip_data;
	पूर्णांक idx = imx_irqsteer_get_reg_index(data, d->hwirq);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&data->lock, flags);
	val = पढ़ोl_relaxed(data->regs + CHANMASK(idx, data->reg_num));
	val &= ~BIT(d->hwirq % 32);
	ग_लिखोl_relaxed(val, data->regs + CHANMASK(idx, data->reg_num));
	raw_spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल काष्ठा irq_chip imx_irqsteer_irq_chip = अणु
	.name		= "irqsteer",
	.irq_mask	= imx_irqsteer_irq_mask,
	.irq_unmask	= imx_irqsteer_irq_unmask,
पूर्ण;

अटल पूर्णांक imx_irqsteer_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	irq_set_status_flags(irq, IRQ_LEVEL);
	irq_set_chip_data(irq, h->host_data);
	irq_set_chip_and_handler(irq, &imx_irqsteer_irq_chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops imx_irqsteer_करोमुख्य_ops = अणु
	.map		= imx_irqsteer_irq_map,
	.xlate		= irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक imx_irqsteer_get_hwirq_base(काष्ठा irqsteer_data *data, u32 irq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->irq_count; i++) अणु
		अगर (data->irq[i] == irq)
			वापस i * 64;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम imx_irqsteer_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irqsteer_data *data = irq_desc_get_handler_data(desc);
	पूर्णांक hwirq;
	पूर्णांक irq, i;

	chained_irq_enter(irq_desc_get_chip(desc), desc);

	irq = irq_desc_get_irq(desc);
	hwirq = imx_irqsteer_get_hwirq_base(data, irq);
	अगर (hwirq < 0) अणु
		pr_warn("%s: unable to get hwirq base for irq %d\n",
			__func__, irq);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 2; i++, hwirq += 32) अणु
		पूर्णांक idx = imx_irqsteer_get_reg_index(data, hwirq);
		अचिन्हित दीर्घ irqmap;
		पूर्णांक pos, virq;

		अगर (hwirq >= data->reg_num * 32)
			अवरोध;

		irqmap = पढ़ोl_relaxed(data->regs +
				       CHANSTATUS(idx, data->reg_num));

		क्रम_each_set_bit(pos, &irqmap, 32) अणु
			virq = irq_find_mapping(data->करोमुख्य, pos + hwirq);
			अगर (virq)
				generic_handle_irq(virq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(irq_desc_get_chip(desc), desc);
पूर्ण

अटल पूर्णांक imx_irqsteer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा irqsteer_data *data;
	u32 irqs_num;
	पूर्णांक i, ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
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

	raw_spin_lock_init(&data->lock);

	ret = of_property_पढ़ो_u32(np, "fsl,num-irqs", &irqs_num);
	अगर (ret)
		वापस ret;
	ret = of_property_पढ़ो_u32(np, "fsl,channel", &data->channel);
	अगर (ret)
		वापस ret;

	/*
	 * There is one output irq क्रम each group of 64 inमाला_दो.
	 * One रेजिस्टर bit map can represent 32 input पूर्णांकerrupts.
	 */
	data->irq_count = DIV_ROUND_UP(irqs_num, 64);
	data->reg_num = irqs_num / 32;

	अगर (IS_ENABLED(CONFIG_PM_SLEEP)) अणु
		data->saved_reg = devm_kzalloc(&pdev->dev,
					माप(u32) * data->reg_num,
					GFP_KERNEL);
		अगर (!data->saved_reg)
			वापस -ENOMEM;
	पूर्ण

	ret = clk_prepare_enable(data->ipg_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable ipg clk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* steer all IRQs पूर्णांकo configured channel */
	ग_लिखोl_relaxed(BIT(data->channel), data->regs + CHANCTRL);

	data->करोमुख्य = irq_करोमुख्य_add_linear(np, data->reg_num * 32,
					     &imx_irqsteer_करोमुख्य_ops, data);
	अगर (!data->करोमुख्य) अणु
		dev_err(&pdev->dev, "failed to create IRQ domain\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!data->irq_count || data->irq_count > CHAN_MAX_OUTPUT_INT) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < data->irq_count; i++) अणु
		data->irq[i] = irq_of_parse_and_map(np, i);
		अगर (!data->irq[i]) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		irq_set_chained_handler_and_data(data->irq[i],
						 imx_irqsteer_irq_handler,
						 data);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
out:
	clk_disable_unprepare(data->ipg_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_irqsteer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irqsteer_data *irqsteer_data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < irqsteer_data->irq_count; i++)
		irq_set_chained_handler_and_data(irqsteer_data->irq[i],
						 शून्य, शून्य);

	irq_करोमुख्य_हटाओ(irqsteer_data->करोमुख्य);

	clk_disable_unprepare(irqsteer_data->ipg_clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम imx_irqsteer_save_regs(काष्ठा irqsteer_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->reg_num; i++)
		data->saved_reg[i] = पढ़ोl_relaxed(data->regs +
						CHANMASK(i, data->reg_num));
पूर्ण

अटल व्योम imx_irqsteer_restore_regs(काष्ठा irqsteer_data *data)
अणु
	पूर्णांक i;

	ग_लिखोl_relaxed(BIT(data->channel), data->regs + CHANCTRL);
	क्रम (i = 0; i < data->reg_num; i++)
		ग_लिखोl_relaxed(data->saved_reg[i],
			       data->regs + CHANMASK(i, data->reg_num));
पूर्ण

अटल पूर्णांक imx_irqsteer_suspend(काष्ठा device *dev)
अणु
	काष्ठा irqsteer_data *irqsteer_data = dev_get_drvdata(dev);

	imx_irqsteer_save_regs(irqsteer_data);
	clk_disable_unprepare(irqsteer_data->ipg_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_irqsteer_resume(काष्ठा device *dev)
अणु
	काष्ठा irqsteer_data *irqsteer_data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(irqsteer_data->ipg_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ipg clk: %d\n", ret);
		वापस ret;
	पूर्ण
	imx_irqsteer_restore_regs(irqsteer_data);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops imx_irqsteer_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(imx_irqsteer_suspend, imx_irqsteer_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_irqsteer_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-irqsteer", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_irqsteer_driver = अणु
	.driver = अणु
		.name = "imx-irqsteer",
		.of_match_table = imx_irqsteer_dt_ids,
		.pm = &imx_irqsteer_pm_ops,
	पूर्ण,
	.probe = imx_irqsteer_probe,
	.हटाओ = imx_irqsteer_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(imx_irqsteer_driver);
