<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STM32 ALSA SoC Digital Audio Interface (SAI) driver.
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author(s): Olivier Moysan <olivier.moysan@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/reset.h>

#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/core.h>

#समावेश "stm32_sai.h"

अटल स्थिर काष्ठा sपंचांग32_sai_conf sपंचांग32_sai_conf_f4 = अणु
	.version = STM_SAI_STM32F4,
	.fअगरo_size = 8,
	.has_spdअगर_pdm = false,
पूर्ण;

/*
 * Default settings क्रम sपंचांग32 H7 socs and next.
 * These शेष settings will be overridden अगर the soc provides
 * support of hardware configuration रेजिस्टरs.
 */
अटल स्थिर काष्ठा sपंचांग32_sai_conf sपंचांग32_sai_conf_h7 = अणु
	.version = STM_SAI_STM32H7,
	.fअगरo_size = 8,
	.has_spdअगर_pdm = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_sai_ids[] = अणु
	अणु .compatible = "st,stm32f4-sai", .data = (व्योम *)&sपंचांग32_sai_conf_f4 पूर्ण,
	अणु .compatible = "st,stm32h7-sai", .data = (व्योम *)&sपंचांग32_sai_conf_h7 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sपंचांग32_sai_pclk_disable(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_sai_data *sai = dev_get_drvdata(dev);

	clk_disable_unprepare(sai->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_pclk_enable(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_sai_data *sai = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(sai->pclk);
	अगर (ret) अणु
		dev_err(&sai->pdev->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sync_conf_client(काष्ठा sपंचांग32_sai_data *sai, पूर्णांक synci)
अणु
	पूर्णांक ret;

	/* Enable peripheral घड़ी to allow GCR रेजिस्टर access */
	ret = sपंचांग32_sai_pclk_enable(&sai->pdev->dev);
	अगर (ret)
		वापस ret;

	ग_लिखोl_relaxed(FIELD_PREP(SAI_GCR_SYNCIN_MASK, (synci - 1)), sai->base);

	sपंचांग32_sai_pclk_disable(&sai->pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_sync_conf_provider(काष्ठा sपंचांग32_sai_data *sai, पूर्णांक synco)
अणु
	u32 prev_synco;
	पूर्णांक ret;

	/* Enable peripheral घड़ी to allow GCR रेजिस्टर access */
	ret = sपंचांग32_sai_pclk_enable(&sai->pdev->dev);
	अगर (ret)
		वापस ret;

	dev_dbg(&sai->pdev->dev, "Set %pOFn%s as synchro provider\n",
		sai->pdev->dev.of_node,
		synco == STM_SAI_SYNC_OUT_A ? "A" : "B");

	prev_synco = FIELD_GET(SAI_GCR_SYNCOUT_MASK, पढ़ोl_relaxed(sai->base));
	अगर (prev_synco != STM_SAI_SYNC_OUT_NONE && synco != prev_synco) अणु
		dev_err(&sai->pdev->dev, "%pOFn%s already set as sync provider\n",
			sai->pdev->dev.of_node,
			prev_synco == STM_SAI_SYNC_OUT_A ? "A" : "B");
		sपंचांग32_sai_pclk_disable(&sai->pdev->dev);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(FIELD_PREP(SAI_GCR_SYNCOUT_MASK, synco), sai->base);

	sपंचांग32_sai_pclk_disable(&sai->pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_set_sync(काष्ठा sपंचांग32_sai_data *sai_client,
			      काष्ठा device_node *np_provider,
			      पूर्णांक synco, पूर्णांक synci)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(np_provider);
	काष्ठा sपंचांग32_sai_data *sai_provider;
	पूर्णांक ret;

	अगर (!pdev) अणु
		dev_err(&sai_client->pdev->dev,
			"Device not found for node %pOFn\n", np_provider);
		of_node_put(np_provider);
		वापस -ENODEV;
	पूर्ण

	sai_provider = platक्रमm_get_drvdata(pdev);
	अगर (!sai_provider) अणु
		dev_err(&sai_client->pdev->dev,
			"SAI sync provider data not found\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* Configure sync client */
	ret = sपंचांग32_sai_sync_conf_client(sai_client, synci);
	अगर (ret < 0)
		जाओ error;

	/* Configure sync provider */
	ret = sपंचांग32_sai_sync_conf_provider(sai_provider, synco);

error:
	put_device(&pdev->dev);
	of_node_put(np_provider);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_sai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_sai_data *sai;
	काष्ठा reset_control *rst;
	स्थिर काष्ठा of_device_id *of_id;
	u32 val;
	पूर्णांक ret;

	sai = devm_kzalloc(&pdev->dev, माप(*sai), GFP_KERNEL);
	अगर (!sai)
		वापस -ENOMEM;

	sai->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sai->base))
		वापस PTR_ERR(sai->base);

	of_id = of_match_device(sपंचांग32_sai_ids, &pdev->dev);
	अगर (of_id)
		स_नकल(&sai->conf, (स्थिर काष्ठा sपंचांग32_sai_conf *)of_id->data,
		       माप(काष्ठा sपंचांग32_sai_conf));
	अन्यथा
		वापस -EINVAL;

	अगर (!STM_SAI_IS_F4(sai)) अणु
		sai->pclk = devm_clk_get(&pdev->dev, "pclk");
		अगर (IS_ERR(sai->pclk)) अणु
			अगर (PTR_ERR(sai->pclk) != -EPROBE_DEFER)
				dev_err(&pdev->dev, "missing bus clock pclk: %ld\n",
					PTR_ERR(sai->pclk));
			वापस PTR_ERR(sai->pclk);
		पूर्ण
	पूर्ण

	sai->clk_x8k = devm_clk_get(&pdev->dev, "x8k");
	अगर (IS_ERR(sai->clk_x8k)) अणु
		अगर (PTR_ERR(sai->clk_x8k) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "missing x8k parent clock: %ld\n",
				PTR_ERR(sai->clk_x8k));
		वापस PTR_ERR(sai->clk_x8k);
	पूर्ण

	sai->clk_x11k = devm_clk_get(&pdev->dev, "x11k");
	अगर (IS_ERR(sai->clk_x11k)) अणु
		अगर (PTR_ERR(sai->clk_x11k) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "missing x11k parent clock: %ld\n",
				PTR_ERR(sai->clk_x11k));
		वापस PTR_ERR(sai->clk_x11k);
	पूर्ण

	/* init irqs */
	sai->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sai->irq < 0)
		वापस sai->irq;

	/* reset */
	rst = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		अगर (PTR_ERR(rst) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Reset controller error %ld\n",
				PTR_ERR(rst));
		वापस PTR_ERR(rst);
	पूर्ण
	reset_control_निश्चित(rst);
	udelay(2);
	reset_control_deनिश्चित(rst);

	/* Enable peripheral घड़ी to allow रेजिस्टर access */
	ret = clk_prepare_enable(sai->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	val = FIELD_GET(SAI_IDR_ID_MASK,
			पढ़ोl_relaxed(sai->base + STM_SAI_IDR));
	अगर (val == SAI_IPIDR_NUMBER) अणु
		val = पढ़ोl_relaxed(sai->base + STM_SAI_HWCFGR);
		sai->conf.fअगरo_size = FIELD_GET(SAI_HWCFGR_FIFO_SIZE, val);
		sai->conf.has_spdअगर_pdm = !!FIELD_GET(SAI_HWCFGR_SPDIF_PDM,
						      val);

		val = पढ़ोl_relaxed(sai->base + STM_SAI_VERR);
		sai->conf.version = val;

		dev_dbg(&pdev->dev, "SAI version: %lu.%lu registered\n",
			FIELD_GET(SAI_VERR_MAJ_MASK, val),
			FIELD_GET(SAI_VERR_MIN_MASK, val));
	पूर्ण
	clk_disable_unprepare(sai->pclk);

	sai->pdev = pdev;
	sai->set_sync = &sपंचांग32_sai_set_sync;
	platक्रमm_set_drvdata(pdev, sai);

	वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * When pins are shared by two sai sub instances, pins have to be defined
 * in sai parent node. In this हाल, pins state is not managed by alsa fw.
 * These pins are managed in suspend/resume callbacks.
 */
अटल पूर्णांक sपंचांग32_sai_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_sai_data *sai = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sपंचांग32_sai_pclk_enable(dev);
	अगर (ret)
		वापस ret;

	sai->gcr = पढ़ोl_relaxed(sai->base);
	sपंचांग32_sai_pclk_disable(dev);

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक sपंचांग32_sai_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_sai_data *sai = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sपंचांग32_sai_pclk_enable(dev);
	अगर (ret)
		वापस ret;

	ग_लिखोl_relaxed(sai->gcr, sai->base);
	sपंचांग32_sai_pclk_disable(dev);

	वापस pinctrl_pm_select_शेष_state(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_sai_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_sai_suspend, sपंचांग32_sai_resume)
पूर्ण;

MODULE_DEVICE_TABLE(of, sपंचांग32_sai_ids);

अटल काष्ठा platक्रमm_driver sपंचांग32_sai_driver = अणु
	.driver = अणु
		.name = "st,stm32-sai",
		.of_match_table = sपंचांग32_sai_ids,
		.pm = &sपंचांग32_sai_pm_ops,
	पूर्ण,
	.probe = sपंचांग32_sai_probe,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_sai_driver);

MODULE_DESCRIPTION("STM32 Soc SAI Interface");
MODULE_AUTHOR("Olivier Moysan <olivier.moysan@st.com>");
MODULE_ALIAS("platform:st,stm32-sai");
MODULE_LICENSE("GPL v2");
