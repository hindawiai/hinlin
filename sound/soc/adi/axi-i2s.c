<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2013, Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#घोषणा AXI_I2S_REG_RESET	0x00
#घोषणा AXI_I2S_REG_CTRL	0x04
#घोषणा AXI_I2S_REG_CLK_CTRL	0x08
#घोषणा AXI_I2S_REG_STATUS	0x10

#घोषणा AXI_I2S_REG_RX_FIFO	0x28
#घोषणा AXI_I2S_REG_TX_FIFO	0x2C

#घोषणा AXI_I2S_RESET_GLOBAL	BIT(0)
#घोषणा AXI_I2S_RESET_TX_FIFO	BIT(1)
#घोषणा AXI_I2S_RESET_RX_FIFO	BIT(2)

#घोषणा AXI_I2S_CTRL_TX_EN	BIT(0)
#घोषणा AXI_I2S_CTRL_RX_EN	BIT(1)

/* The frame size is configurable, but क्रम now we always set it 64 bit */
#घोषणा AXI_I2S_BITS_PER_FRAME 64

काष्ठा axi_i2s अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	काष्ठा clk *clk_ref;

	bool   has_capture;
	bool   has_playback;

	काष्ठा snd_soc_dai_driver dai_driver;

	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;

	काष्ठा snd_ratnum ratnum;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums rate_स्थिरraपूर्णांकs;
पूर्ण;

अटल पूर्णांक axi_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask, val;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mask = AXI_I2S_CTRL_RX_EN;
	अन्यथा
		mask = AXI_I2S_CTRL_TX_EN;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = mask;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, AXI_I2S_REG_CTRL, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक bclk_भाग, word_size;
	अचिन्हित पूर्णांक bclk_rate;

	bclk_rate = params_rate(params) * AXI_I2S_BITS_PER_FRAME;

	word_size = AXI_I2S_BITS_PER_FRAME / 2 - 1;
	bclk_भाग = DIV_ROUND_UP(clk_get_rate(i2s->clk_ref), bclk_rate) / 2 - 1;

	regmap_ग_लिखो(i2s->regmap, AXI_I2S_REG_CLK_CTRL, (word_size << 16) |
		bclk_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_i2s_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t mask;
	पूर्णांक ret;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mask = AXI_I2S_RESET_RX_FIFO;
	अन्यथा
		mask = AXI_I2S_RESET_TX_FIFO;

	regmap_ग_लिखो(i2s->regmap, AXI_I2S_REG_RESET, mask);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_ratnums(substream->runसमय, 0,
			   SNDRV_PCM_HW_PARAM_RATE,
			   &i2s->rate_स्थिरraपूर्णांकs);
	अगर (ret)
		वापस ret;

	वापस clk_prepare_enable(i2s->clk_ref);
पूर्ण

अटल व्योम axi_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(i2s->clk_ref);
पूर्ण

अटल पूर्णांक axi_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(
		dai,
		i2s->has_playback ? &i2s->playback_dma_data : शून्य,
		i2s->has_capture  ? &i2s->capture_dma_data  : शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axi_i2s_dai_ops = अणु
	.startup = axi_i2s_startup,
	.shutकरोwn = axi_i2s_shutकरोwn,
	.trigger = axi_i2s_trigger,
	.hw_params = axi_i2s_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver axi_i2s_dai = अणु
	.probe = axi_i2s_dai_probe,
	.ops = &axi_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axi_i2s_component = अणु
	.name = "axi-i2s",
पूर्ण;

अटल स्थिर काष्ठा regmap_config axi_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = AXI_I2S_REG_STATUS,
पूर्ण;

अटल व्योम axi_i2s_parse_of(काष्ठा axi_i2s *i2s, स्थिर काष्ठा device_node *np)
अणु
	काष्ठा property *dma_names;
	स्थिर अक्षर *dma_name;

	of_property_क्रम_each_string(np, "dma-names", dma_names, dma_name) अणु
		अगर (म_भेद(dma_name, "rx") == 0)
			i2s->has_capture = true;
		अगर (म_भेद(dma_name, "tx") == 0)
			i2s->has_playback = true;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा axi_i2s *i2s;
	व्योम __iomem *base;
	पूर्णांक ret;

	i2s = devm_kzalloc(&pdev->dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, i2s);

	axi_i2s_parse_of(i2s, pdev->dev.of_node);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, base,
		&axi_i2s_regmap_config);
	अगर (IS_ERR(i2s->regmap))
		वापस PTR_ERR(i2s->regmap);

	i2s->clk = devm_clk_get(&pdev->dev, "axi");
	अगर (IS_ERR(i2s->clk))
		वापस PTR_ERR(i2s->clk);

	i2s->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(i2s->clk_ref))
		वापस PTR_ERR(i2s->clk_ref);

	ret = clk_prepare_enable(i2s->clk);
	अगर (ret)
		वापस ret;

	अगर (i2s->has_playback) अणु
		axi_i2s_dai.playback.channels_min = 2;
		axi_i2s_dai.playback.channels_max = 2;
		axi_i2s_dai.playback.rates = SNDRV_PCM_RATE_KNOT;
		axi_i2s_dai.playback.क्रमmats =
			SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_U32_LE;

		i2s->playback_dma_data.addr = res->start + AXI_I2S_REG_TX_FIFO;
		i2s->playback_dma_data.addr_width = 4;
		i2s->playback_dma_data.maxburst = 1;
	पूर्ण

	अगर (i2s->has_capture) अणु
		axi_i2s_dai.capture.channels_min = 2;
		axi_i2s_dai.capture.channels_max = 2;
		axi_i2s_dai.capture.rates = SNDRV_PCM_RATE_KNOT;
		axi_i2s_dai.capture.क्रमmats =
			SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_U32_LE;

		i2s->capture_dma_data.addr = res->start + AXI_I2S_REG_RX_FIFO;
		i2s->capture_dma_data.addr_width = 4;
		i2s->capture_dma_data.maxburst = 1;
	पूर्ण

	i2s->ratnum.num = clk_get_rate(i2s->clk_ref) / 2 / AXI_I2S_BITS_PER_FRAME;
	i2s->ratnum.den_step = 1;
	i2s->ratnum.den_min = 1;
	i2s->ratnum.den_max = 64;

	i2s->rate_स्थिरraपूर्णांकs.rats = &i2s->ratnum;
	i2s->rate_स्थिरraपूर्णांकs.nrats = 1;

	regmap_ग_लिखो(i2s->regmap, AXI_I2S_REG_RESET, AXI_I2S_RESET_GLOBAL);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &axi_i2s_component,
					 &axi_i2s_dai, 1);
	अगर (ret)
		जाओ err_clk_disable;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		जाओ err_clk_disable;

	dev_info(&pdev->dev, "probed, capture %s, playback %s\n",
		 i2s->has_capture ? "enabled" : "disabled",
		 i2s->has_playback ? "enabled" : "disabled");

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(i2s->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक axi_i2s_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axi_i2s *i2s = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(i2s->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axi_i2s_of_match[] = अणु
	अणु .compatible = "adi,axi-i2s-1.00.a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axi_i2s_of_match);

अटल काष्ठा platक्रमm_driver axi_i2s_driver = अणु
	.driver = अणु
		.name = "axi-i2s",
		.of_match_table = axi_i2s_of_match,
	पूर्ण,
	.probe = axi_i2s_probe,
	.हटाओ = axi_i2s_dev_हटाओ,
पूर्ण;
module_platक्रमm_driver(axi_i2s_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("AXI I2S driver");
MODULE_LICENSE("GPL");
