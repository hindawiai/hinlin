<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap-dmic.c  --  OMAP ASoC DMIC DAI driver
 *
 * Copyright (C) 2010 - 2011 Texas Instruments
 *
 * Author: David Lambert <dlambert@ti.com>
 *	   Misael Lopez Cruz <misael.lopez@ti.com>
 *	   Liam Girdwood <lrg@ti.com>
 *	   Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "omap-dmic.h"
#समावेश "sdma-pcm.h"

काष्ठा omap_dmic अणु
	काष्ठा device *dev;
	व्योम __iomem *io_base;
	काष्ठा clk *fclk;
	काष्ठा pm_qos_request pm_qos_req;
	पूर्णांक latency;
	पूर्णांक fclk_freq;
	पूर्णांक out_freq;
	पूर्णांक clk_भाग;
	पूर्णांक sysclk;
	पूर्णांक threshold;
	u32 ch_enabled;
	bool active;
	काष्ठा mutex mutex;

	काष्ठा snd_dmaengine_dai_dma_data dma_data;
पूर्ण;

अटल अंतरभूत व्योम omap_dmic_ग_लिखो(काष्ठा omap_dmic *dmic, u16 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, dmic->io_base + reg);
पूर्ण

अटल अंतरभूत पूर्णांक omap_dmic_पढ़ो(काष्ठा omap_dmic *dmic, u16 reg)
अणु
	वापस पढ़ोl_relaxed(dmic->io_base + reg);
पूर्ण

अटल अंतरभूत व्योम omap_dmic_start(काष्ठा omap_dmic *dmic)
अणु
	u32 ctrl = omap_dmic_पढ़ो(dmic, OMAP_DMIC_CTRL_REG);

	/* Configure DMA controller */
	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_DMAENABLE_SET_REG,
			OMAP_DMIC_DMA_ENABLE);

	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_CTRL_REG, ctrl | dmic->ch_enabled);
पूर्ण

अटल अंतरभूत व्योम omap_dmic_stop(काष्ठा omap_dmic *dmic)
अणु
	u32 ctrl = omap_dmic_पढ़ो(dmic, OMAP_DMIC_CTRL_REG);
	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_CTRL_REG,
			ctrl & ~OMAP_DMIC_UP_ENABLE_MASK);

	/* Disable DMA request generation */
	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_DMAENABLE_CLR_REG,
			OMAP_DMIC_DMA_ENABLE);

पूर्ण

अटल अंतरभूत पूर्णांक dmic_is_enabled(काष्ठा omap_dmic *dmic)
अणु
	वापस omap_dmic_पढ़ो(dmic, OMAP_DMIC_CTRL_REG) &
						OMAP_DMIC_UP_ENABLE_MASK;
पूर्ण

अटल पूर्णांक omap_dmic_dai_startup(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret = 0;

	mutex_lock(&dmic->mutex);

	अगर (!snd_soc_dai_active(dai))
		dmic->active = 1;
	अन्यथा
		ret = -EBUSY;

	mutex_unlock(&dmic->mutex);

	वापस ret;
पूर्ण

अटल व्योम omap_dmic_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	mutex_lock(&dmic->mutex);

	cpu_latency_qos_हटाओ_request(&dmic->pm_qos_req);

	अगर (!snd_soc_dai_active(dai))
		dmic->active = 0;

	mutex_unlock(&dmic->mutex);
पूर्ण

अटल पूर्णांक omap_dmic_select_भागider(काष्ठा omap_dmic *dmic, पूर्णांक sample_rate)
अणु
	पूर्णांक भागider = -EINVAL;

	/*
	 * 192KHz rate is only supported with 19.2MHz/3.84MHz घड़ी
	 * configuration.
	 */
	अगर (sample_rate == 192000) अणु
		अगर (dmic->fclk_freq == 19200000 && dmic->out_freq == 3840000)
			भागider = 0x6; /* Divider: 5 (192KHz sampling rate) */
		अन्यथा
			dev_err(dmic->dev,
				"invalid clock configuration for 192KHz\n");

		वापस भागider;
	पूर्ण

	चयन (dmic->out_freq) अणु
	हाल 1536000:
		अगर (dmic->fclk_freq != 24576000)
			जाओ भाग_err;
		भागider = 0x4; /* Divider: 16 */
		अवरोध;
	हाल 2400000:
		चयन (dmic->fclk_freq) अणु
		हाल 12000000:
			भागider = 0x5; /* Divider: 5 */
			अवरोध;
		हाल 19200000:
			भागider = 0x0; /* Divider: 8 */
			अवरोध;
		हाल 24000000:
			भागider = 0x2; /* Divider: 10 */
			अवरोध;
		शेष:
			जाओ भाग_err;
		पूर्ण
		अवरोध;
	हाल 3072000:
		अगर (dmic->fclk_freq != 24576000)
			जाओ भाग_err;
		भागider = 0x3; /* Divider: 8 */
		अवरोध;
	हाल 3840000:
		अगर (dmic->fclk_freq != 19200000)
			जाओ भाग_err;
		भागider = 0x1; /* Divider: 5 (96KHz sampling rate) */
		अवरोध;
	शेष:
		dev_err(dmic->dev, "invalid out frequency: %dHz\n",
			dmic->out_freq);
		अवरोध;
	पूर्ण

	वापस भागider;

भाग_err:
	dev_err(dmic->dev, "invalid out frequency %dHz for %dHz input\n",
		dmic->out_freq, dmic->fclk_freq);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक omap_dmic_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	पूर्णांक channels;

	dmic->clk_भाग = omap_dmic_select_भागider(dmic, params_rate(params));
	अगर (dmic->clk_भाग < 0) अणु
		dev_err(dmic->dev, "no valid divider for %dHz from %dHz\n",
			dmic->out_freq, dmic->fclk_freq);
		वापस -EINVAL;
	पूर्ण

	dmic->ch_enabled = 0;
	channels = params_channels(params);
	चयन (channels) अणु
	हाल 6:
		dmic->ch_enabled |= OMAP_DMIC_UP3_ENABLE;
		fallthrough;
	हाल 4:
		dmic->ch_enabled |= OMAP_DMIC_UP2_ENABLE;
		fallthrough;
	हाल 2:
		dmic->ch_enabled |= OMAP_DMIC_UP1_ENABLE;
		अवरोध;
	शेष:
		dev_err(dmic->dev, "invalid number of legacy channels\n");
		वापस -EINVAL;
	पूर्ण

	/* packet size is threshold * channels */
	dma_data = snd_soc_dai_get_dma_data(dai, substream);
	dma_data->maxburst = dmic->threshold * channels;
	dmic->latency = (OMAP_DMIC_THRES_MAX - dmic->threshold) * USEC_PER_SEC /
			params_rate(params);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dmic_dai_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);
	u32 ctrl;

	अगर (cpu_latency_qos_request_active(&dmic->pm_qos_req))
		cpu_latency_qos_update_request(&dmic->pm_qos_req,
					       dmic->latency);

	/* Configure uplink threshold */
	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_FIFO_CTRL_REG, dmic->threshold);

	ctrl = omap_dmic_पढ़ो(dmic, OMAP_DMIC_CTRL_REG);

	/* Set dmic out क्रमmat */
	ctrl &= ~(OMAP_DMIC_FORMAT | OMAP_DMIC_POLAR_MASK);
	ctrl |= (OMAP_DMICOUTFORMAT_LJUST | OMAP_DMIC_POLAR1 |
		 OMAP_DMIC_POLAR2 | OMAP_DMIC_POLAR3);

	/* Configure dmic घड़ी भागider */
	ctrl &= ~OMAP_DMIC_CLK_DIV_MASK;
	ctrl |= OMAP_DMIC_CLK_DIV(dmic->clk_भाग);

	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_CTRL_REG, ctrl);

	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_CTRL_REG,
			ctrl | OMAP_DMICOUTFORMAT_LJUST | OMAP_DMIC_POLAR1 |
			OMAP_DMIC_POLAR2 | OMAP_DMIC_POLAR3);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dmic_dai_trigger(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		omap_dmic_start(dmic);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		omap_dmic_stop(dmic);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dmic_select_fclk(काष्ठा omap_dmic *dmic, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq)
अणु
	काष्ठा clk *parent_clk, *mux;
	अक्षर *parent_clk_name;
	पूर्णांक ret = 0;

	चयन (freq) अणु
	हाल 12000000:
	हाल 19200000:
	हाल 24000000:
	हाल 24576000:
		अवरोध;
	शेष:
		dev_err(dmic->dev, "invalid input frequency: %dHz\n", freq);
		dmic->fclk_freq = 0;
		वापस -EINVAL;
	पूर्ण

	अगर (dmic->sysclk == clk_id) अणु
		dmic->fclk_freq = freq;
		वापस 0;
	पूर्ण

	/* re-parent not allowed अगर a stream is ongoing */
	अगर (dmic->active && dmic_is_enabled(dmic)) अणु
		dev_err(dmic->dev, "can't re-parent when DMIC active\n");
		वापस -EBUSY;
	पूर्ण

	चयन (clk_id) अणु
	हाल OMAP_DMIC_SYSCLK_PAD_CLKS:
		parent_clk_name = "pad_clks_ck";
		अवरोध;
	हाल OMAP_DMIC_SYSCLK_SLIMBLUS_CLKS:
		parent_clk_name = "slimbus_clk";
		अवरोध;
	हाल OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS:
		parent_clk_name = "dmic_sync_mux_ck";
		अवरोध;
	शेष:
		dev_err(dmic->dev, "fclk clk_id (%d) not supported\n", clk_id);
		वापस -EINVAL;
	पूर्ण

	parent_clk = clk_get(dmic->dev, parent_clk_name);
	अगर (IS_ERR(parent_clk)) अणु
		dev_err(dmic->dev, "can't get %s\n", parent_clk_name);
		वापस -ENODEV;
	पूर्ण

	mux = clk_get_parent(dmic->fclk);
	अगर (IS_ERR(mux)) अणु
		dev_err(dmic->dev, "can't get fck mux parent\n");
		clk_put(parent_clk);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&dmic->mutex);
	अगर (dmic->active) अणु
		/* disable घड़ी जबतक reparenting */
		pm_runसमय_put_sync(dmic->dev);
		ret = clk_set_parent(mux, parent_clk);
		pm_runसमय_get_sync(dmic->dev);
	पूर्ण अन्यथा अणु
		ret = clk_set_parent(mux, parent_clk);
	पूर्ण
	mutex_unlock(&dmic->mutex);

	अगर (ret < 0) अणु
		dev_err(dmic->dev, "re-parent failed\n");
		जाओ err_busy;
	पूर्ण

	dmic->sysclk = clk_id;
	dmic->fclk_freq = freq;

err_busy:
	clk_put(mux);
	clk_put(parent_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_dmic_select_outclk(काष्ठा omap_dmic *dmic, पूर्णांक clk_id,
				    अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक ret = 0;

	अगर (clk_id != OMAP_DMIC_ABE_DMIC_CLK) अणु
		dev_err(dmic->dev, "output clk_id (%d) not supported\n",
			clk_id);
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 1536000:
	हाल 2400000:
	हाल 3072000:
	हाल 3840000:
		dmic->out_freq = freq;
		अवरोध;
	शेष:
		dev_err(dmic->dev, "invalid out frequency: %dHz\n", freq);
		dmic->out_freq = 0;
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक omap_dmic_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				    अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	अगर (dir == SND_SOC_CLOCK_IN)
		वापस omap_dmic_select_fclk(dmic, clk_id, freq);
	अन्यथा अगर (dir == SND_SOC_CLOCK_OUT)
		वापस omap_dmic_select_outclk(dmic, clk_id, freq);

	dev_err(dmic->dev, "invalid clock direction (%d)\n", dir);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops omap_dmic_dai_ops = अणु
	.startup	= omap_dmic_dai_startup,
	.shutकरोwn	= omap_dmic_dai_shutकरोwn,
	.hw_params	= omap_dmic_dai_hw_params,
	.prepare	= omap_dmic_dai_prepare,
	.trigger	= omap_dmic_dai_trigger,
	.set_sysclk	= omap_dmic_set_dai_sysclk,
पूर्ण;

अटल पूर्णांक omap_dmic_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	pm_runसमय_enable(dmic->dev);

	/* Disable lines जबतक request is ongoing */
	pm_runसमय_get_sync(dmic->dev);
	omap_dmic_ग_लिखो(dmic, OMAP_DMIC_CTRL_REG, 0x00);
	pm_runसमय_put_sync(dmic->dev);

	/* Configure DMIC threshold value */
	dmic->threshold = OMAP_DMIC_THRES_MAX - 3;

	snd_soc_dai_init_dma_data(dai, शून्य, &dmic->dma_data);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dmic_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	pm_runसमय_disable(dmic->dev);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver omap_dmic_dai = अणु
	.name = "omap-dmic",
	.probe = omap_dmic_probe,
	.हटाओ = omap_dmic_हटाओ,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 6,
		.rates = SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 24,
	पूर्ण,
	.ops = &omap_dmic_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver omap_dmic_component = अणु
	.name		= "omap-dmic",
पूर्ण;

अटल पूर्णांक asoc_dmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dmic *dmic;
	काष्ठा resource *res;
	पूर्णांक ret;

	dmic = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_dmic), GFP_KERNEL);
	अगर (!dmic)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dmic);
	dmic->dev = &pdev->dev;
	dmic->sysclk = OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS;

	mutex_init(&dmic->mutex);

	dmic->fclk = devm_clk_get(dmic->dev, "fck");
	अगर (IS_ERR(dmic->fclk)) अणु
		dev_err(dmic->dev, "cant get fck\n");
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dma");
	अगर (!res) अणु
		dev_err(dmic->dev, "invalid dma memory resource\n");
		वापस -ENODEV;
	पूर्ण
	dmic->dma_data.addr = res->start + OMAP_DMIC_DATA_REG;

	dmic->dma_data.filter_data = "up_link";

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mpu");
	dmic->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dmic->io_base))
		वापस PTR_ERR(dmic->io_base);


	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &omap_dmic_component,
					      &omap_dmic_dai, 1);
	अगर (ret)
		वापस ret;

	ret = sdma_pcm_platक्रमm_रेजिस्टर(&pdev->dev, शून्य, "up_link");
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_dmic_of_match[] = अणु
	अणु .compatible = "ti,omap4-dmic", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_dmic_of_match);

अटल काष्ठा platक्रमm_driver asoc_dmic_driver = अणु
	.driver = अणु
		.name = "omap-dmic",
		.of_match_table = omap_dmic_of_match,
	पूर्ण,
	.probe = asoc_dmic_probe,
पूर्ण;

module_platक्रमm_driver(asoc_dmic_driver);

MODULE_ALIAS("platform:omap-dmic");
MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("OMAP DMIC ASoC Interface");
MODULE_LICENSE("GPL");
