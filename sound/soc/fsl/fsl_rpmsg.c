<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2018-2021 NXP

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rpmsg.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "fsl_rpmsg.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_RPMSG_RATES        (SNDRV_PCM_RATE_8000 | \
				SNDRV_PCM_RATE_16000 | \
				SNDRV_PCM_RATE_48000)
#घोषणा FSL_RPMSG_FORMATS	SNDRV_PCM_FMTBIT_S16_LE

/* 192kHz/32bit/2ch/60s size is 0x574e00 */
#घोषणा LPA_LARGE_BUFFER_SIZE  (0x6000000)

अटल स्थिर अचिन्हित पूर्णांक fsl_rpmsg_rates[] = अणु
	8000, 11025, 16000, 22050, 44100,
	32000, 48000, 96000, 88200, 176400, 192000,
	352800, 384000, 705600, 768000, 1411200, 2822400,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list fsl_rpmsg_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(fsl_rpmsg_rates),
	.list = fsl_rpmsg_rates,
पूर्ण;

अटल पूर्णांक fsl_rpmsg_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_rpmsg *rpmsg = snd_soc_dai_get_drvdata(dai);
	काष्ठा clk *p = rpmsg->mclk, *pll = शून्य, *npll = शून्य;
	u64 rate = params_rate(params);
	पूर्णांक ret = 0;

	/* Get current pll parent */
	जबतक (p && rpmsg->pll8k && rpmsg->pll11k) अणु
		काष्ठा clk *pp = clk_get_parent(p);

		अगर (clk_is_match(pp, rpmsg->pll8k) ||
		    clk_is_match(pp, rpmsg->pll11k)) अणु
			pll = pp;
			अवरोध;
		पूर्ण
		p = pp;
	पूर्ण

	/* Switch to another pll parent अगर needed. */
	अगर (pll) अणु
		npll = (करो_भाग(rate, 8000) ? rpmsg->pll11k : rpmsg->pll8k);
		अगर (!clk_is_match(pll, npll)) अणु
			ret = clk_set_parent(p, npll);
			अगर (ret < 0)
				dev_warn(dai->dev, "failed to set parent %s: %d\n",
					 __clk_get_name(npll), ret);
		पूर्ण
	पूर्ण

	अगर (!(rpmsg->mclk_streams & BIT(substream->stream))) अणु
		ret = clk_prepare_enable(rpmsg->mclk);
		अगर (ret) अणु
			dev_err(dai->dev, "failed to enable mclk: %d\n", ret);
			वापस ret;
		पूर्ण

		rpmsg->mclk_streams |= BIT(substream->stream);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_rpmsg_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_rpmsg *rpmsg = snd_soc_dai_get_drvdata(dai);

	अगर (rpmsg->mclk_streams & BIT(substream->stream)) अणु
		clk_disable_unprepare(rpmsg->mclk);
		rpmsg->mclk_streams &= ~BIT(substream->stream);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_rpmsg_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *cpu_dai)
अणु
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &fsl_rpmsg_rate_स्थिरraपूर्णांकs);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_rpmsg_dai_ops = अणु
	.startup	= fsl_rpmsg_startup,
	.hw_params      = fsl_rpmsg_hw_params,
	.hw_मुक्त        = fsl_rpmsg_hw_मुक्त,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver fsl_rpmsg_dai = अणु
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_RPMSG_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_RPMSG_FORMATS,
	पूर्ण,
	.symmetric_rate        = 1,
	.symmetric_channels    = 1,
	.symmetric_sample_bits = 1,
	.ops = &fsl_rpmsg_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_component = अणु
	.name           = "fsl-rpmsg",
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_rpmsg_ids[] = अणु
	अणु .compatible = "fsl,imx7ulp-rpmsg-audio"पूर्ण,
	अणु .compatible = "fsl,imx8mm-rpmsg-audio"पूर्ण,
	अणु .compatible = "fsl,imx8mn-rpmsg-audio"पूर्ण,
	अणु .compatible = "fsl,imx8mp-rpmsg-audio"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_rpmsg_ids);

अटल पूर्णांक fsl_rpmsg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_rpmsg *rpmsg;
	पूर्णांक ret;

	rpmsg = devm_kzalloc(&pdev->dev, माप(काष्ठा fsl_rpmsg), GFP_KERNEL);
	अगर (!rpmsg)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_bool(np, "fsl,enable-lpa")) अणु
		rpmsg->enable_lpa = 1;
		rpmsg->buffer_size = LPA_LARGE_BUFFER_SIZE;
	पूर्ण अन्यथा अणु
		rpmsg->buffer_size = IMX_DEFAULT_DMABUF_SIZE;
	पूर्ण

	/* Get the optional घड़ीs */
	rpmsg->ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(rpmsg->ipg))
		rpmsg->ipg = शून्य;

	rpmsg->mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(rpmsg->mclk))
		rpmsg->mclk = शून्य;

	rpmsg->dma = devm_clk_get(&pdev->dev, "dma");
	अगर (IS_ERR(rpmsg->dma))
		rpmsg->dma = शून्य;

	rpmsg->pll8k = devm_clk_get(&pdev->dev, "pll8k");
	अगर (IS_ERR(rpmsg->pll8k))
		rpmsg->pll8k = शून्य;

	rpmsg->pll11k = devm_clk_get(&pdev->dev, "pll11k");
	अगर (IS_ERR(rpmsg->pll11k))
		rpmsg->pll11k = शून्य;

	platक्रमm_set_drvdata(pdev, rpmsg);
	pm_runसमय_enable(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsl_component,
					      &fsl_rpmsg_dai, 1);
	अगर (ret)
		वापस ret;

	rpmsg->card_pdev = platक्रमm_device_रेजिस्टर_data(&pdev->dev,
							 "imx-audio-rpmsg",
							 PLATFORM_DEVID_NONE,
							 शून्य,
							 0);
	अगर (IS_ERR(rpmsg->card_pdev)) अणु
		dev_err(&pdev->dev, "failed to register rpmsg card\n");
		ret = PTR_ERR(rpmsg->card_pdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_rpmsg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_rpmsg *rpmsg = platक्रमm_get_drvdata(pdev);

	अगर (rpmsg->card_pdev)
		platक्रमm_device_unरेजिस्टर(rpmsg->card_pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsl_rpmsg_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_rpmsg *rpmsg = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(rpmsg->ipg);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ipg clock: %d\n", ret);
		जाओ ipg_err;
	पूर्ण

	ret = clk_prepare_enable(rpmsg->dma);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable dma clock %d\n", ret);
		जाओ dma_err;
	पूर्ण

	वापस 0;

dma_err:
	clk_disable_unprepare(rpmsg->ipg);
ipg_err:
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_rpmsg_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_rpmsg *rpmsg = dev_get_drvdata(dev);

	clk_disable_unprepare(rpmsg->dma);
	clk_disable_unprepare(rpmsg->ipg);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fsl_rpmsg_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_rpmsg_runसमय_suspend,
			   fsl_rpmsg_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_rpmsg_driver = अणु
	.probe  = fsl_rpmsg_probe,
	.हटाओ = fsl_rpmsg_हटाओ,
	.driver = अणु
		.name = "fsl_rpmsg",
		.pm = &fsl_rpmsg_pm_ops,
		.of_match_table = fsl_rpmsg_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_rpmsg_driver);

MODULE_DESCRIPTION("Freescale SoC Audio PRMSG CPU Interface");
MODULE_AUTHOR("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODULE_ALIAS("platform:fsl_rpmsg");
MODULE_LICENSE("GPL");
