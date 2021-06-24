<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Xilinx ASoC SPDIF audio support
//
// Copyright (C) 2018 Xilinx, Inc.
//
// Author: Maruthi Srinivas Bayyavarapu <maruthis@xilinx.com>
//

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा XLNX_SPDIF_RATES \
	(SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 | \
	SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 | \
	SNDRV_PCM_RATE_192000)

#घोषणा XLNX_SPDIF_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा XSPDIF_IRQ_STS_REG		0x20
#घोषणा XSPDIF_IRQ_ENABLE_REG		0x28
#घोषणा XSPDIF_SOFT_RESET_REG		0x40
#घोषणा XSPDIF_CONTROL_REG		0x44
#घोषणा XSPDIF_CHAN_0_STS_REG		0x4C
#घोषणा XSPDIF_GLOBAL_IRQ_ENABLE_REG	0x1C
#घोषणा XSPDIF_CH_A_USER_DATA_REG_0	0x64

#घोषणा XSPDIF_CORE_ENABLE_MASK		BIT(0)
#घोषणा XSPDIF_FIFO_FLUSH_MASK		BIT(1)
#घोषणा XSPDIF_CH_STS_MASK		BIT(5)
#घोषणा XSPDIF_GLOBAL_IRQ_ENABLE	BIT(31)
#घोषणा XSPDIF_CLOCK_CONFIG_BITS_MASK	GENMASK(5, 2)
#घोषणा XSPDIF_CLOCK_CONFIG_BITS_SHIFT	2
#घोषणा XSPDIF_SOFT_RESET_VALUE		0xA

#घोषणा MAX_CHANNELS			2
#घोषणा AES_SAMPLE_WIDTH		32
#घोषणा CH_STATUS_UPDATE_TIMEOUT	40

काष्ठा spdअगर_dev_data अणु
	u32 mode;
	u32 aclk;
	bool rx_chsts_updated;
	व्योम __iomem *base;
	काष्ठा clk *axi_clk;
	रुको_queue_head_t chsts_q;
पूर्ण;

अटल irqवापस_t xlnx_spdअगरrx_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	u32 val;
	काष्ठा spdअगर_dev_data *ctx = arg;

	val = पढ़ोl(ctx->base + XSPDIF_IRQ_STS_REG);
	अगर (val & XSPDIF_CH_STS_MASK) अणु
		ग_लिखोl(val & XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IRQ_STS_REG);
		val = पढ़ोl(ctx->base +
			    XSPDIF_IRQ_ENABLE_REG);
		ग_लिखोl(val & ~XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IRQ_ENABLE_REG);

		ctx->rx_chsts_updated = true;
		wake_up_पूर्णांकerruptible(&ctx->chsts_q);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक xlnx_spdअगर_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	u32 val;
	काष्ठा spdअगर_dev_data *ctx = dev_get_drvdata(dai->dev);

	val = पढ़ोl(ctx->base + XSPDIF_CONTROL_REG);
	val |= XSPDIF_FIFO_FLUSH_MASK;
	ग_लिखोl(val, ctx->base + XSPDIF_CONTROL_REG);

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		ग_लिखोl(XSPDIF_CH_STS_MASK,
		       ctx->base + XSPDIF_IRQ_ENABLE_REG);
		ग_लिखोl(XSPDIF_GLOBAL_IRQ_ENABLE,
		       ctx->base + XSPDIF_GLOBAL_IRQ_ENABLE_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xlnx_spdअगर_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_dev_data *ctx = dev_get_drvdata(dai->dev);

	ग_लिखोl(XSPDIF_SOFT_RESET_VALUE, ctx->base + XSPDIF_SOFT_RESET_REG);
पूर्ण

अटल पूर्णांक xlnx_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	u32 val, clk_भाग, clk_cfg;
	काष्ठा spdअगर_dev_data *ctx = dev_get_drvdata(dai->dev);

	clk_भाग = DIV_ROUND_CLOSEST(ctx->aclk, MAX_CHANNELS * AES_SAMPLE_WIDTH *
				    params_rate(params));

	चयन (clk_भाग) अणु
	हाल 4:
		clk_cfg = 0;
		अवरोध;
	हाल 8:
		clk_cfg = 1;
		अवरोध;
	हाल 16:
		clk_cfg = 2;
		अवरोध;
	हाल 24:
		clk_cfg = 3;
		अवरोध;
	हाल 32:
		clk_cfg = 4;
		अवरोध;
	हाल 48:
		clk_cfg = 5;
		अवरोध;
	हाल 64:
		clk_cfg = 6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = पढ़ोl(ctx->base + XSPDIF_CONTROL_REG);
	val &= ~XSPDIF_CLOCK_CONFIG_BITS_MASK;
	val |= clk_cfg << XSPDIF_CLOCK_CONFIG_BITS_SHIFT;
	ग_लिखोl(val, ctx->base + XSPDIF_CONTROL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक rx_stream_detect(काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक err;
	काष्ठा spdअगर_dev_data *ctx = dev_get_drvdata(dai->dev);
	अचिन्हित दीर्घ jअगरfies = msecs_to_jअगरfies(CH_STATUS_UPDATE_TIMEOUT);

	/* start capture only अगर stream is detected within 40ms समयout */
	err = रुको_event_पूर्णांकerruptible_समयout(ctx->chsts_q,
					       ctx->rx_chsts_updated,
					       jअगरfies);
	अगर (!err) अणु
		dev_err(dai->dev, "No streaming audio detected!\n");
		वापस -EINVAL;
	पूर्ण
	ctx->rx_chsts_updated = false;

	वापस 0;
पूर्ण

अटल पूर्णांक xlnx_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			      काष्ठा snd_soc_dai *dai)
अणु
	u32 val;
	पूर्णांक ret = 0;
	काष्ठा spdअगर_dev_data *ctx = dev_get_drvdata(dai->dev);

	val = पढ़ोl(ctx->base + XSPDIF_CONTROL_REG);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val |= XSPDIF_CORE_ENABLE_MASK;
		ग_लिखोl(val, ctx->base + XSPDIF_CONTROL_REG);
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			ret = rx_stream_detect(dai);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val &= ~XSPDIF_CORE_ENABLE_MASK;
		ग_लिखोl(val, ctx->base + XSPDIF_CONTROL_REG);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops xlnx_spdअगर_dai_ops = अणु
	.startup = xlnx_spdअगर_startup,
	.shutकरोwn = xlnx_spdअगर_shutकरोwn,
	.trigger = xlnx_spdअगर_trigger,
	.hw_params = xlnx_spdअगर_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver xlnx_spdअगर_tx_dai = अणु
	.name = "xlnx_spdif_tx",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = XLNX_SPDIF_RATES,
		.क्रमmats = XLNX_SPDIF_FORMATS,
	पूर्ण,
	.ops = &xlnx_spdअगर_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver xlnx_spdअगर_rx_dai = अणु
	.name = "xlnx_spdif_rx",
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = XLNX_SPDIF_RATES,
		.क्रमmats = XLNX_SPDIF_FORMATS,
	पूर्ण,
	.ops = &xlnx_spdअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver xlnx_spdअगर_component = अणु
	.name = "xlnx-spdif",
पूर्ण;

अटल स्थिर काष्ठा of_device_id xlnx_spdअगर_of_match[] = अणु
	अणु .compatible = "xlnx,spdif-2.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlnx_spdअगर_of_match);

अटल पूर्णांक xlnx_spdअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *res;
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा spdअगर_dev_data *ctx;

	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->axi_clk = devm_clk_get(dev, "s_axi_aclk");
	अगर (IS_ERR(ctx->axi_clk)) अणु
		ret = PTR_ERR(ctx->axi_clk);
		dev_err(dev, "failed to get s_axi_aclk(%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(ctx->axi_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable s_axi_aclk(%d)\n", ret);
		वापस ret;
	पूर्ण

	ctx->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctx->base)) अणु
		ret = PTR_ERR(ctx->base);
		जाओ clk_err;
	पूर्ण
	ret = of_property_पढ़ो_u32(node, "xlnx,spdif-mode", &ctx->mode);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get SPDIF mode\n");
		जाओ clk_err;
	पूर्ण
	अगर (ctx->mode) अणु
		dai_drv = &xlnx_spdअगर_tx_dai;
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
		अगर (!res) अणु
			dev_err(dev, "No IRQ resource found\n");
			ret = -ENODEV;
			जाओ clk_err;
		पूर्ण
		ret = devm_request_irq(dev, res->start,
				       xlnx_spdअगरrx_irq_handler,
				       0, "XLNX_SPDIF_RX", ctx);
		अगर (ret) अणु
			dev_err(dev, "spdif rx irq request failed\n");
			ret = -ENODEV;
			जाओ clk_err;
		पूर्ण

		init_रुकोqueue_head(&ctx->chsts_q);
		dai_drv = &xlnx_spdअगर_rx_dai;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "xlnx,aud_clk_i", &ctx->aclk);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get aud_clk_i value\n");
		जाओ clk_err;
	पूर्ण

	dev_set_drvdata(dev, ctx);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &xlnx_spdअगर_component,
					      dai_drv, 1);
	अगर (ret) अणु
		dev_err(dev, "SPDIF component registration failed\n");
		जाओ clk_err;
	पूर्ण

	ग_लिखोl(XSPDIF_SOFT_RESET_VALUE, ctx->base + XSPDIF_SOFT_RESET_REG);
	dev_info(dev, "%s DAI registered\n", dai_drv->name);

clk_err:
	clk_disable_unprepare(ctx->axi_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक xlnx_spdअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spdअगर_dev_data *ctx = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(ctx->axi_clk);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xlnx_spdअगर_driver = अणु
	.driver = अणु
		.name = "xlnx-spdif",
		.of_match_table = xlnx_spdअगर_of_match,
	पूर्ण,
	.probe = xlnx_spdअगर_probe,
	.हटाओ = xlnx_spdअगर_हटाओ,
पूर्ण;
module_platक्रमm_driver(xlnx_spdअगर_driver);

MODULE_AUTHOR("Maruthi Srinivas Bayyavarapu <maruthis@xilinx.com>");
MODULE_DESCRIPTION("XILINX SPDIF driver");
MODULE_LICENSE("GPL v2");
