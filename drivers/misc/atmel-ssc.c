<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel SSC driver
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/aपंचांगel-ssc.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/of.h>

#समावेश "../../sound/soc/atmel/atmel_ssc_dai.h"

/* Serialize access to ssc_list and user count */
अटल DEFINE_MUTEX(user_lock);
अटल LIST_HEAD(ssc_list);

काष्ठा ssc_device *ssc_request(अचिन्हित पूर्णांक ssc_num)
अणु
	पूर्णांक ssc_valid = 0;
	काष्ठा ssc_device *ssc;

	mutex_lock(&user_lock);
	list_क्रम_each_entry(ssc, &ssc_list, list) अणु
		अगर (ssc->pdev->dev.of_node) अणु
			अगर (of_alias_get_id(ssc->pdev->dev.of_node, "ssc")
				== ssc_num) अणु
				ssc->pdev->id = ssc_num;
				ssc_valid = 1;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ssc->pdev->id == ssc_num) अणु
			ssc_valid = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ssc_valid) अणु
		mutex_unlock(&user_lock);
		pr_err("ssc: ssc%d platform device is missing\n", ssc_num);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (ssc->user) अणु
		mutex_unlock(&user_lock);
		dev_dbg(&ssc->pdev->dev, "module busy\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	ssc->user++;
	mutex_unlock(&user_lock);

	clk_prepare(ssc->clk);

	वापस ssc;
पूर्ण
EXPORT_SYMBOL(ssc_request);

व्योम ssc_मुक्त(काष्ठा ssc_device *ssc)
अणु
	bool disable_clk = true;

	mutex_lock(&user_lock);
	अगर (ssc->user)
		ssc->user--;
	अन्यथा अणु
		disable_clk = false;
		dev_dbg(&ssc->pdev->dev, "device already free\n");
	पूर्ण
	mutex_unlock(&user_lock);

	अगर (disable_clk)
		clk_unprepare(ssc->clk);
पूर्ण
EXPORT_SYMBOL(ssc_मुक्त);

अटल काष्ठा aपंचांगel_ssc_platक्रमm_data at91rm9200_config = अणु
	.use_dma = 0,
	.has_fslen_ext = 0,
पूर्ण;

अटल काष्ठा aपंचांगel_ssc_platक्रमm_data at91sam9rl_config = अणु
	.use_dma = 0,
	.has_fslen_ext = 1,
पूर्ण;

अटल काष्ठा aपंचांगel_ssc_platक्रमm_data at91sam9g45_config = अणु
	.use_dma = 1,
	.has_fslen_ext = 1,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id aपंचांगel_ssc_devtypes[] = अणु
	अणु
		.name = "at91rm9200_ssc",
		.driver_data = (अचिन्हित दीर्घ) &at91rm9200_config,
	पूर्ण, अणु
		.name = "at91sam9rl_ssc",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9rl_config,
	पूर्ण, अणु
		.name = "at91sam9g45_ssc",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9g45_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id aपंचांगel_ssc_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91rm9200-ssc",
		.data = &at91rm9200_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9rl-ssc",
		.data = &at91sam9rl_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9g45-ssc",
		.data = &at91sam9g45_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_ssc_dt_ids);
#पूर्ण_अगर

अटल अंतरभूत स्थिर काष्ठा aपंचांगel_ssc_platक्रमm_data *
	aपंचांगel_ssc_get_driver_data(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_node(aपंचांगel_ssc_dt_ids, pdev->dev.of_node);
		अगर (match == शून्य)
			वापस शून्य;
		वापस match->data;
	पूर्ण

	वापस (काष्ठा aपंचांगel_ssc_platक्रमm_data *)
		platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

#अगर_घोषित CONFIG_SND_ATMEL_SOC_SSC
अटल पूर्णांक ssc_sound_dai_probe(काष्ठा ssc_device *ssc)
अणु
	काष्ठा device_node *np = ssc->pdev->dev.of_node;
	पूर्णांक ret;
	पूर्णांक id;

	ssc->sound_dai = false;

	अगर (!of_property_पढ़ो_bool(np, "#sound-dai-cells"))
		वापस 0;

	id = of_alias_get_id(np, "ssc");
	अगर (id < 0)
		वापस id;

	ret = aपंचांगel_ssc_set_audio(id);
	ssc->sound_dai = !ret;

	वापस ret;
पूर्ण

अटल व्योम ssc_sound_dai_हटाओ(काष्ठा ssc_device *ssc)
अणु
	अगर (!ssc->sound_dai)
		वापस;

	aपंचांगel_ssc_put_audio(of_alias_get_id(ssc->pdev->dev.of_node, "ssc"));
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ssc_sound_dai_probe(काष्ठा ssc_device *ssc)
अणु
	अगर (of_property_पढ़ो_bool(ssc->pdev->dev.of_node, "#sound-dai-cells"))
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ssc_sound_dai_हटाओ(काष्ठा ssc_device *ssc)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ssc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *regs;
	काष्ठा ssc_device *ssc;
	स्थिर काष्ठा aपंचांगel_ssc_platक्रमm_data *plat_dat;

	ssc = devm_kzalloc(&pdev->dev, माप(काष्ठा ssc_device), GFP_KERNEL);
	अगर (!ssc) अणु
		dev_dbg(&pdev->dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	ssc->pdev = pdev;

	plat_dat = aपंचांगel_ssc_get_driver_data(pdev);
	अगर (!plat_dat)
		वापस -ENODEV;
	ssc->pdata = (काष्ठा aपंचांगel_ssc_platक्रमm_data *)plat_dat;

	अगर (pdev->dev.of_node) अणु
		काष्ठा device_node *np = pdev->dev.of_node;
		ssc->clk_from_rk_pin =
			of_property_पढ़ो_bool(np, "atmel,clk-from-rk-pin");
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ssc->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(ssc->regs))
		वापस PTR_ERR(ssc->regs);

	ssc->phybase = regs->start;

	ssc->clk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(ssc->clk)) अणु
		dev_dbg(&pdev->dev, "no pclk clock defined\n");
		वापस -ENXIO;
	पूर्ण

	/* disable all पूर्णांकerrupts */
	clk_prepare_enable(ssc->clk);
	ssc_ग_लिखोl(ssc->regs, IDR, -1);
	ssc_पढ़ोl(ssc->regs, SR);
	clk_disable_unprepare(ssc->clk);

	ssc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (!ssc->irq) अणु
		dev_dbg(&pdev->dev, "could not get irq\n");
		वापस -ENXIO;
	पूर्ण

	mutex_lock(&user_lock);
	list_add_tail(&ssc->list, &ssc_list);
	mutex_unlock(&user_lock);

	platक्रमm_set_drvdata(pdev, ssc);

	dev_info(&pdev->dev, "Atmel SSC device at 0x%p (irq %d)\n",
			ssc->regs, ssc->irq);

	अगर (ssc_sound_dai_probe(ssc))
		dev_err(&pdev->dev, "failed to auto-setup ssc for audio\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ssc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssc_device *ssc = platक्रमm_get_drvdata(pdev);

	ssc_sound_dai_हटाओ(ssc);

	mutex_lock(&user_lock);
	list_del(&ssc->list);
	mutex_unlock(&user_lock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ssc_driver = अणु
	.driver		= अणु
		.name		= "ssc",
		.of_match_table	= of_match_ptr(aपंचांगel_ssc_dt_ids),
	पूर्ण,
	.id_table	= aपंचांगel_ssc_devtypes,
	.probe		= ssc_probe,
	.हटाओ		= ssc_हटाओ,
पूर्ण;
module_platक्रमm_driver(ssc_driver);

MODULE_AUTHOR("Hans-Christian Egtvedt <hcegtvedt@atmel.com>");
MODULE_DESCRIPTION("SSC driver for Atmel AVR32 and AT91");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ssc");
