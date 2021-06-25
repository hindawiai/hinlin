<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2015 Pengutronix, Markus Pargmann <mpa@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/imx25-tsadc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

अटल काष्ठा regmap_config mx25_tsadc_regmap_config = अणु
	.fast_io = true,
	.max_रेजिस्टर = 8,
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल व्योम mx25_tsadc_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा mx25_tsadc *tsadc = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 status;

	chained_irq_enter(chip, desc);

	regmap_पढ़ो(tsadc->regs, MX25_TSC_TGSR, &status);

	अगर (status & MX25_TGSR_GCQ_INT)
		generic_handle_irq(irq_find_mapping(tsadc->करोमुख्य, 1));

	अगर (status & MX25_TGSR_TCQ_INT)
		generic_handle_irq(irq_find_mapping(tsadc->करोमुख्य, 0));

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक mx25_tsadc_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hwirq)
अणु
	काष्ठा mx25_tsadc *tsadc = d->host_data;

	irq_set_chip_data(irq, tsadc);
	irq_set_chip_and_handler(irq, &dummy_irq_chip,
				 handle_level_irq);
	irq_modअगरy_status(irq, IRQ_NOREQUEST, IRQ_NOPROBE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mx25_tsadc_करोमुख्य_ops = अणु
	.map = mx25_tsadc_करोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक mx25_tsadc_setup_irq(काष्ठा platक्रमm_device *pdev,
				काष्ठा mx25_tsadc *tsadc)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	tsadc->करोमुख्य = irq_करोमुख्य_add_simple(np, 2, 0, &mx25_tsadc_करोमुख्य_ops,
					      tsadc);
	अगर (!tsadc->करोमुख्य) अणु
		dev_err(dev, "Failed to add irq domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_set_chained_handler_and_data(irq, mx25_tsadc_irq_handler, tsadc);

	वापस 0;
पूर्ण

अटल व्योम mx25_tsadc_setup_clk(काष्ठा platक्रमm_device *pdev,
				 काष्ठा mx25_tsadc *tsadc)
अणु
	अचिन्हित clk_भाग;

	/*
	 * According to the datasheet the ADC घड़ी should never
	 * exceed 1,75 MHz. Base घड़ी is the IPG and the ADC unit uses
	 * a funny घड़ी भागider. To keep the ADC conversion समय स्थिरant
	 * adapt the ADC पूर्णांकernal घड़ी भागider to the IPG घड़ी rate.
	 */

	dev_dbg(&pdev->dev, "Found master clock at %lu Hz\n",
		clk_get_rate(tsadc->clk));

	clk_भाग = DIV_ROUND_UP(clk_get_rate(tsadc->clk), 1750000);
	dev_dbg(&pdev->dev, "Setting up ADC clock divider to %u\n", clk_भाग);

	/* adc घड़ी = IPG घड़ी / (2 * भाग + 2) */
	clk_भाग -= 2;
	clk_भाग /= 2;

	/*
	 * the ADC घड़ी भागider changes its behaviour when values below 4
	 * are used: it is fixed to "/ 10" in this हाल
	 */
	clk_भाग = max_t(अचिन्हित, 4, clk_भाग);

	dev_dbg(&pdev->dev, "Resulting ADC conversion clock at %lu Hz\n",
		clk_get_rate(tsadc->clk) / (2 * clk_भाग + 2));

	regmap_update_bits(tsadc->regs, MX25_TSC_TGCR,
			   MX25_TGCR_ADCCLKCFG(0x1f),
			   MX25_TGCR_ADCCLKCFG(clk_भाग));
पूर्ण

अटल पूर्णांक mx25_tsadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mx25_tsadc *tsadc;
	काष्ठा resource *res;
	पूर्णांक ret;
	व्योम __iomem *iomem;

	tsadc = devm_kzalloc(dev, माप(*tsadc), GFP_KERNEL);
	अगर (!tsadc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	iomem = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(iomem))
		वापस PTR_ERR(iomem);

	tsadc->regs = devm_regmap_init_mmio(dev, iomem,
					    &mx25_tsadc_regmap_config);
	अगर (IS_ERR(tsadc->regs)) अणु
		dev_err(dev, "Failed to initialize regmap\n");
		वापस PTR_ERR(tsadc->regs);
	पूर्ण

	tsadc->clk = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(tsadc->clk)) अणु
		dev_err(dev, "Failed to get ipg clock\n");
		वापस PTR_ERR(tsadc->clk);
	पूर्ण

	/* setup घड़ी according to the datasheet */
	mx25_tsadc_setup_clk(pdev, tsadc);

	/* Enable घड़ी and reset the component */
	regmap_update_bits(tsadc->regs, MX25_TSC_TGCR, MX25_TGCR_CLK_EN,
			   MX25_TGCR_CLK_EN);
	regmap_update_bits(tsadc->regs, MX25_TSC_TGCR, MX25_TGCR_TSC_RST,
			   MX25_TGCR_TSC_RST);

	/* Setup घातersaving mode, but enable पूर्णांकernal reference voltage */
	regmap_update_bits(tsadc->regs, MX25_TSC_TGCR, MX25_TGCR_POWERMODE_MASK,
			   MX25_TGCR_POWERMODE_SAVE);
	regmap_update_bits(tsadc->regs, MX25_TSC_TGCR, MX25_TGCR_INTREFEN,
			   MX25_TGCR_INTREFEN);

	ret = mx25_tsadc_setup_irq(pdev, tsadc);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, tsadc);

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

अटल पूर्णांक mx25_tsadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mx25_tsadc *tsadc = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (irq) अणु
		irq_set_chained_handler_and_data(irq, शून्य, शून्य);
		irq_करोमुख्य_हटाओ(tsadc->करोमुख्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mx25_tsadc_ids[] = अणु
	अणु .compatible = "fsl,imx25-tsadc" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mx25_tsadc_ids);

अटल काष्ठा platक्रमm_driver mx25_tsadc_driver = अणु
	.driver = अणु
		.name = "mx25-tsadc",
		.of_match_table = mx25_tsadc_ids,
	पूर्ण,
	.probe = mx25_tsadc_probe,
	.हटाओ = mx25_tsadc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mx25_tsadc_driver);

MODULE_DESCRIPTION("MFD for ADC/TSC for Freescale mx25");
MODULE_AUTHOR("Markus Pargmann <mpa@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mx25-tsadc");
