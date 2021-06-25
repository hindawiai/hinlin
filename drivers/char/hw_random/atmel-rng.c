<शैली गुरु>
/*
 * Copyright (c) 2011 Peter Korsgaard <jacmet@sunsite.dk>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा TRNG_CR		0x00
#घोषणा TRNG_MR		0x04
#घोषणा TRNG_ISR	0x1c
#घोषणा TRNG_ODATA	0x50

#घोषणा TRNG_KEY	0x524e4700 /* RNG */

#घोषणा TRNG_HALFR	BIT(0) /* generate RN every 168 cycles */

काष्ठा aपंचांगel_trng_data अणु
	bool has_half_rate;
पूर्ण;

काष्ठा aपंचांगel_trng अणु
	काष्ठा clk *clk;
	व्योम __iomem *base;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक aपंचांगel_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max,
			   bool रुको)
अणु
	काष्ठा aपंचांगel_trng *trng = container_of(rng, काष्ठा aपंचांगel_trng, rng);
	u32 *data = buf;

	/* data पढ़ोy? */
	अगर (पढ़ोl(trng->base + TRNG_ISR) & 1) अणु
		*data = पढ़ोl(trng->base + TRNG_ODATA);
		/*
		  ensure data पढ़ोy is only set again AFTER the next data
		  word is पढ़ोy in हाल it got set between checking ISR
		  and पढ़ोing ODATA, so we करोn't risk re-पढ़ोing the
		  same word
		*/
		पढ़ोl(trng->base + TRNG_ISR);
		वापस 4;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल व्योम aपंचांगel_trng_enable(काष्ठा aपंचांगel_trng *trng)
अणु
	ग_लिखोl(TRNG_KEY | 1, trng->base + TRNG_CR);
पूर्ण

अटल व्योम aपंचांगel_trng_disable(काष्ठा aपंचांगel_trng *trng)
अणु
	ग_लिखोl(TRNG_KEY, trng->base + TRNG_CR);
पूर्ण

अटल पूर्णांक aपंचांगel_trng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_trng *trng;
	स्थिर काष्ठा aपंचांगel_trng_data *data;
	पूर्णांक ret;

	trng = devm_kzalloc(&pdev->dev, माप(*trng), GFP_KERNEL);
	अगर (!trng)
		वापस -ENOMEM;

	trng->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(trng->base))
		वापस PTR_ERR(trng->base);

	trng->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(trng->clk))
		वापस PTR_ERR(trng->clk);
	data = of_device_get_match_data(&pdev->dev);
	अगर (!data)
		वापस -ENODEV;

	अगर (data->has_half_rate) अणु
		अचिन्हित दीर्घ rate = clk_get_rate(trng->clk);

		/* अगर peripheral clk is above 100MHz, set HALFR */
		अगर (rate > 100000000)
			ग_लिखोl(TRNG_HALFR, trng->base + TRNG_MR);
	पूर्ण

	ret = clk_prepare_enable(trng->clk);
	अगर (ret)
		वापस ret;

	aपंचांगel_trng_enable(trng);
	trng->rng.name = pdev->name;
	trng->rng.पढ़ो = aपंचांगel_trng_पढ़ो;

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &trng->rng);
	अगर (ret)
		जाओ err_रेजिस्टर;

	platक्रमm_set_drvdata(pdev, trng);

	वापस 0;

err_रेजिस्टर:
	clk_disable_unprepare(trng->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_trng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_trng *trng = platक्रमm_get_drvdata(pdev);


	aपंचांगel_trng_disable(trng);
	clk_disable_unprepare(trng->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक aपंचांगel_trng_suspend(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_trng *trng = dev_get_drvdata(dev);

	aपंचांगel_trng_disable(trng);
	clk_disable_unprepare(trng->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_trng_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_trng *trng = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(trng->clk);
	अगर (ret)
		वापस ret;

	aपंचांगel_trng_enable(trng);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops aपंचांगel_trng_pm_ops = अणु
	.suspend	= aपंचांगel_trng_suspend,
	.resume		= aपंचांगel_trng_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा aपंचांगel_trng_data at91sam9g45_config = अणु
	.has_half_rate = false,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_trng_data sam9x60_config = अणु
	.has_half_rate = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_trng_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91sam9g45-trng",
		.data = &at91sam9g45_config,
	पूर्ण, अणु
		.compatible = "microchip,sam9x60-trng",
		.data = &sam9x60_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_trng_dt_ids);

अटल काष्ठा platक्रमm_driver aपंचांगel_trng_driver = अणु
	.probe		= aपंचांगel_trng_probe,
	.हटाओ		= aपंचांगel_trng_हटाओ,
	.driver		= अणु
		.name	= "atmel-trng",
#अगर_घोषित CONFIG_PM
		.pm	= &aपंचांगel_trng_pm_ops,
#पूर्ण_अगर /* CONFIG_PM */
		.of_match_table = aपंचांगel_trng_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_trng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Korsgaard <jacmet@sunsite.dk>");
MODULE_DESCRIPTION("Atmel true random number generator driver");
