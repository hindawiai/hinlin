<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2013, Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/dmaengine_pcm.h>

#घोषणा AXI_SPDIF_REG_CTRL	0x0
#घोषणा AXI_SPDIF_REG_STAT	0x4
#घोषणा AXI_SPDIF_REG_TX_FIFO	0xc

#घोषणा AXI_SPDIF_CTRL_TXDATA BIT(1)
#घोषणा AXI_SPDIF_CTRL_TXEN BIT(0)
#घोषणा AXI_SPDIF_CTRL_CLKDIV_OFFSET 8
#घोषणा AXI_SPDIF_CTRL_CLKDIV_MASK (0xff << 8)

#घोषणा AXI_SPDIF_FREQ_44100	(0x0 << 6)
#घोषणा AXI_SPDIF_FREQ_48000	(0x1 << 6)
#घोषणा AXI_SPDIF_FREQ_32000	(0x2 << 6)
#घोषणा AXI_SPDIF_FREQ_NA	(0x3 << 6)

काष्ठा axi_spdअगर अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	काष्ठा clk *clk_ref;

	काष्ठा snd_dmaengine_dai_dma_data dma_data;

	काष्ठा snd_ratnum ratnum;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums rate_स्थिरraपूर्णांकs;
पूर्ण;

अटल पूर्णांक axi_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक val;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = AXI_SPDIF_CTRL_TXDATA;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(spdअगर->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_TXDATA, val);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक clkभाग, stat;

	चयन (params_rate(params)) अणु
	हाल 32000:
		stat = AXI_SPDIF_FREQ_32000;
		अवरोध;
	हाल 44100:
		stat = AXI_SPDIF_FREQ_44100;
		अवरोध;
	हाल 48000:
		stat = AXI_SPDIF_FREQ_48000;
		अवरोध;
	शेष:
		stat = AXI_SPDIF_FREQ_NA;
		अवरोध;
	पूर्ण

	clkभाग = DIV_ROUND_CLOSEST(clk_get_rate(spdअगर->clk_ref),
			rate * 64 * 2) - 1;
	clkभाग <<= AXI_SPDIF_CTRL_CLKDIV_OFFSET;

	regmap_ग_लिखो(spdअगर->regmap, AXI_SPDIF_REG_STAT, stat);
	regmap_update_bits(spdअगर->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_CLKDIV_MASK, clkभाग);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_spdअगर_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdअगर->dma_data, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_spdअगर_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_ratnums(substream->runसमय, 0,
			   SNDRV_PCM_HW_PARAM_RATE,
			   &spdअगर->rate_स्थिरraपूर्णांकs);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(spdअगर->clk_ref);
	अगर (ret)
		वापस ret;

	regmap_update_bits(spdअगर->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_TXEN, AXI_SPDIF_CTRL_TXEN);

	वापस 0;
पूर्ण

अटल व्योम axi_spdअगर_shutकरोwn(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);

	regmap_update_bits(spdअगर->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_TXEN, 0);

	clk_disable_unprepare(spdअगर->clk_ref);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axi_spdअगर_dai_ops = अणु
	.startup = axi_spdअगर_startup,
	.shutकरोwn = axi_spdअगर_shutकरोwn,
	.trigger = axi_spdअगर_trigger,
	.hw_params = axi_spdअगर_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver axi_spdअगर_dai = अणु
	.probe = axi_spdअगर_dai_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &axi_spdअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axi_spdअगर_component = अणु
	.name = "axi-spdif",
पूर्ण;

अटल स्थिर काष्ठा regmap_config axi_spdअगर_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = AXI_SPDIF_REG_STAT,
पूर्ण;

अटल पूर्णांक axi_spdअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axi_spdअगर *spdअगर;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;

	spdअगर = devm_kzalloc(&pdev->dev, माप(*spdअगर), GFP_KERNEL);
	अगर (!spdअगर)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, spdअगर);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	spdअगर->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					    &axi_spdअगर_regmap_config);
	अगर (IS_ERR(spdअगर->regmap))
		वापस PTR_ERR(spdअगर->regmap);

	spdअगर->clk = devm_clk_get(&pdev->dev, "axi");
	अगर (IS_ERR(spdअगर->clk))
		वापस PTR_ERR(spdअगर->clk);

	spdअगर->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(spdअगर->clk_ref))
		वापस PTR_ERR(spdअगर->clk_ref);

	ret = clk_prepare_enable(spdअगर->clk);
	अगर (ret)
		वापस ret;

	spdअगर->dma_data.addr = res->start + AXI_SPDIF_REG_TX_FIFO;
	spdअगर->dma_data.addr_width = 4;
	spdअगर->dma_data.maxburst = 1;

	spdअगर->ratnum.num = clk_get_rate(spdअगर->clk_ref) / 128;
	spdअगर->ratnum.den_step = 1;
	spdअगर->ratnum.den_min = 1;
	spdअगर->ratnum.den_max = 64;

	spdअगर->rate_स्थिरraपूर्णांकs.rats = &spdअगर->ratnum;
	spdअगर->rate_स्थिरraपूर्णांकs.nrats = 1;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &axi_spdअगर_component,
					 &axi_spdअगर_dai, 1);
	अगर (ret)
		जाओ err_clk_disable;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		जाओ err_clk_disable;

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(spdअगर->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक axi_spdअगर_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axi_spdअगर *spdअगर = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(spdअगर->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axi_spdअगर_of_match[] = अणु
	अणु .compatible = "adi,axi-spdif-tx-1.00.a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axi_spdअगर_of_match);

अटल काष्ठा platक्रमm_driver axi_spdअगर_driver = अणु
	.driver = अणु
		.name = "axi-spdif",
		.of_match_table = axi_spdअगर_of_match,
	पूर्ण,
	.probe = axi_spdअगर_probe,
	.हटाओ = axi_spdअगर_dev_हटाओ,
पूर्ण;
module_platक्रमm_driver(axi_spdअगर_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("AXI SPDIF driver");
MODULE_LICENSE("GPL");
