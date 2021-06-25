<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2020 NXP

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/pm_qos.h>
#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/dma-mapping.h>

#समावेश "fsl_aud2htx.h"
#समावेश "imx-pcm.h"

अटल पूर्णांक fsl_aud2htx_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_aud2htx *aud2htx = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL,
				   AUD2HTX_CTRL_EN, AUD2HTX_CTRL_EN);
		regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL_EXT,
				   AUD2HTX_CTRE_DE, AUD2HTX_CTRE_DE);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL_EXT,
				   AUD2HTX_CTRE_DE, 0);
		regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL,
				   AUD2HTX_CTRL_EN, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_aud2htx_dai_ops = अणु
	.trigger	= fsl_aud2htx_trigger,
पूर्ण;

अटल पूर्णांक fsl_aud2htx_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_aud2htx *aud2htx = dev_get_drvdata(cpu_dai->dev);

	/* DMA request when number of entries < WTMK_LOW */
	regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL_EXT,
			   AUD2HTX_CTRE_DT_MASK, 0);

	/* Disable पूर्णांकerrupts*/
	regmap_update_bits(aud2htx->regmap, AUD2HTX_IRQ_MASK,
			   AUD2HTX_WM_HIGH_IRQ_MASK |
			   AUD2HTX_WM_LOW_IRQ_MASK |
			   AUD2HTX_OVF_MASK,
			   AUD2HTX_WM_HIGH_IRQ_MASK |
			   AUD2HTX_WM_LOW_IRQ_MASK |
			   AUD2HTX_OVF_MASK);

	/* Configure watermark */
	regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL_EXT,
			   AUD2HTX_CTRE_WL_MASK,
			   AUD2HTX_WTMK_LOW << AUD2HTX_CTRE_WL_SHIFT);
	regmap_update_bits(aud2htx->regmap, AUD2HTX_CTRL_EXT,
			   AUD2HTX_CTRE_WH_MASK,
			   AUD2HTX_WTMK_HIGH << AUD2HTX_CTRE_WH_SHIFT);

	snd_soc_dai_init_dma_data(cpu_dai, &aud2htx->dma_params_tx,
				  &aud2htx->dma_params_rx);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_aud2htx_dai = अणु
	.probe = fsl_aud2htx_dai_probe,
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000 |
			 SNDRV_PCM_RATE_88200 |
			 SNDRV_PCM_RATE_96000 |
			 SNDRV_PCM_RATE_176400 |
			 SNDRV_PCM_RATE_192000,
		.क्रमmats = FSL_AUD2HTX_FORMATS,
	पूर्ण,
	.ops = &fsl_aud2htx_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_aud2htx_component = अणु
	.name	= "fsl-aud2htx",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष fsl_aud2htx_reg_शेषs[] = अणु
	अणुAUD2HTX_CTRL,		0x00000000पूर्ण,
	अणुAUD2HTX_CTRL_EXT,	0x00000000पूर्ण,
	अणुAUD2HTX_WR,		0x00000000पूर्ण,
	अणुAUD2HTX_STATUS,	0x00000000पूर्ण,
	अणुAUD2HTX_IRQ_NOMASK,	0x00000000पूर्ण,
	अणुAUD2HTX_IRQ_MASKED,	0x00000000पूर्ण,
	अणुAUD2HTX_IRQ_MASK,	0x00000000पूर्ण,
पूर्ण;

अटल bool fsl_aud2htx_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AUD2HTX_CTRL:
	हाल AUD2HTX_CTRL_EXT:
	हाल AUD2HTX_STATUS:
	हाल AUD2HTX_IRQ_NOMASK:
	हाल AUD2HTX_IRQ_MASKED:
	हाल AUD2HTX_IRQ_MASK:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_aud2htx_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AUD2HTX_CTRL:
	हाल AUD2HTX_CTRL_EXT:
	हाल AUD2HTX_WR:
	हाल AUD2HTX_IRQ_NOMASK:
	हाल AUD2HTX_IRQ_MASKED:
	हाल AUD2HTX_IRQ_MASK:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_aud2htx_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AUD2HTX_STATUS:
	हाल AUD2HTX_IRQ_NOMASK:
	हाल AUD2HTX_IRQ_MASKED:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_aud2htx_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = AUD2HTX_IRQ_MASK,
	.reg_शेषs = fsl_aud2htx_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(fsl_aud2htx_reg_शेषs),
	.पढ़ोable_reg = fsl_aud2htx_पढ़ोable_reg,
	.अस्थिर_reg = fsl_aud2htx_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_aud2htx_ग_लिखोable_reg,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_aud2htx_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8mp-aud2htx",पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_aud2htx_dt_ids);

अटल irqवापस_t fsl_aud2htx_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_aud2htx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_aud2htx *aud2htx;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret, irq;

	aud2htx = devm_kzalloc(&pdev->dev, माप(*aud2htx), GFP_KERNEL);
	अगर (!aud2htx)
		वापस -ENOMEM;

	aud2htx->pdev = pdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	aud2htx->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
						&fsl_aud2htx_regmap_config);
	अगर (IS_ERR(aud2htx->regmap)) अणु
		dev_err(&pdev->dev, "failed to init regmap");
		वापस PTR_ERR(aud2htx->regmap);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, fsl_aud2htx_isr, 0,
			       dev_name(&pdev->dev), aud2htx);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim irq %u: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	aud2htx->bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(aud2htx->bus_clk)) अणु
		dev_err(&pdev->dev, "failed to get mem clock\n");
		वापस PTR_ERR(aud2htx->bus_clk);
	पूर्ण

	aud2htx->dma_params_tx.chan_name = "tx";
	aud2htx->dma_params_tx.maxburst = AUD2HTX_MAXBURST;
	aud2htx->dma_params_tx.addr = res->start + AUD2HTX_WR;

	platक्रमm_set_drvdata(pdev, aud2htx);
	pm_runसमय_enable(&pdev->dev);

	regcache_cache_only(aud2htx->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &fsl_aud2htx_component,
					      &fsl_aud2htx_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register ASoC DAI\n");
		वापस ret;
	पूर्ण

	ret = imx_pcm_dma_init(pdev, IMX_DEFAULT_DMABUF_SIZE);
	अगर (ret)
		dev_err(&pdev->dev, "failed to init imx pcm dma: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_aud2htx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_aud2htx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_aud2htx *aud2htx = dev_get_drvdata(dev);

	regcache_cache_only(aud2htx->regmap, true);
	clk_disable_unprepare(aud2htx->bus_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fsl_aud2htx_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_aud2htx *aud2htx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(aud2htx->bus_clk);
	अगर (ret)
		वापस ret;

	regcache_cache_only(aud2htx->regmap, false);
	regcache_mark_dirty(aud2htx->regmap);
	regcache_sync(aud2htx->regmap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_aud2htx_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_aud2htx_runसमय_suspend,
			   fsl_aud2htx_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_aud2htx_driver = अणु
	.probe = fsl_aud2htx_probe,
	.हटाओ = fsl_aud2htx_हटाओ,
	.driver = अणु
		.name = "fsl-aud2htx",
		.pm = &fsl_aud2htx_pm_ops,
		.of_match_table = fsl_aud2htx_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_aud2htx_driver);

MODULE_AUTHOR("Shengjiu Wang <Shengjiu.Wang@nxp.com>");
MODULE_DESCRIPTION("NXP AUD2HTX driver");
MODULE_LICENSE("GPL v2");
