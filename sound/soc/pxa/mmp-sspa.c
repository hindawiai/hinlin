<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/sound/soc/pxa/mmp-sspa.c
 * Base on pxa2xx-ssp.c
 *
 * Copyright (C) 2011 Marvell International Ltd.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश "mmp-sspa.h"

/*
 * SSPA audio निजी data
 */
काष्ठा sspa_priv अणु
	व्योम __iomem *tx_base;
	व्योम __iomem *rx_base;

	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;
	काष्ठा clk *clk;
	काष्ठा clk *audio_clk;
	काष्ठा clk *sysclk;

	पूर्णांक running_cnt;
	u32 sp;
	u32 ctrl;
पूर्ण;

अटल व्योम mmp_sspa_tx_enable(काष्ठा sspa_priv *sspa)
अणु
	अचिन्हित पूर्णांक sspa_sp = sspa->sp;

	sspa_sp &= ~SSPA_SP_MSL;
	sspa_sp |= SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__raw_ग_लिखोl(sspa_sp, sspa->tx_base + SSPA_SP);
पूर्ण

अटल व्योम mmp_sspa_tx_disable(काष्ठा sspa_priv *sspa)
अणु
	अचिन्हित पूर्णांक sspa_sp = sspa->sp;

	sspa_sp &= ~SSPA_SP_MSL;
	sspa_sp &= ~SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__raw_ग_लिखोl(sspa_sp, sspa->tx_base + SSPA_SP);
पूर्ण

अटल व्योम mmp_sspa_rx_enable(काष्ठा sspa_priv *sspa)
अणु
	अचिन्हित पूर्णांक sspa_sp = sspa->sp;

	sspa_sp |= SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__raw_ग_लिखोl(sspa_sp, sspa->rx_base + SSPA_SP);
पूर्ण

अटल व्योम mmp_sspa_rx_disable(काष्ठा sspa_priv *sspa)
अणु
	अचिन्हित पूर्णांक sspa_sp = sspa->sp;

	sspa_sp &= ~SSPA_SP_S_EN;
	sspa_sp |= SSPA_SP_WEN;
	__raw_ग_लिखोl(sspa_sp, sspa->rx_base + SSPA_SP);
पूर्ण

अटल पूर्णांक mmp_sspa_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(dai);

	clk_prepare_enable(sspa->sysclk);
	clk_prepare_enable(sspa->clk);

	वापस 0;
पूर्ण

अटल व्योम mmp_sspa_shutकरोwn(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(sspa->clk);
	clk_disable_unprepare(sspa->sysclk);
पूर्ण

/*
 * Set the SSP ports SYSCLK.
 */
अटल पूर्णांक mmp_sspa_set_dai_sysclk(काष्ठा snd_soc_dai *cpu_dai,
				    पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा device *dev = cpu_dai->component->dev;
	पूर्णांक ret = 0;

	अगर (dev->of_node)
		वापस -ENOTSUPP;

	चयन (clk_id) अणु
	हाल MMP_SSPA_CLK_AUDIO:
		ret = clk_set_rate(sspa->audio_clk, freq);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल MMP_SSPA_CLK_PLL:
	हाल MMP_SSPA_CLK_VCXO:
		/* not support yet */
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_sspa_set_dai_pll(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक pll_id,
				 पूर्णांक source, अचिन्हित पूर्णांक freq_in,
				 अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा device *dev = cpu_dai->component->dev;
	पूर्णांक ret = 0;

	अगर (dev->of_node)
		वापस -ENOTSUPP;

	चयन (pll_id) अणु
	हाल MMP_SYSCLK:
		ret = clk_set_rate(sspa->sysclk, freq_out);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल MMP_SSPA_CLK:
		ret = clk_set_rate(sspa->clk, freq_out);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set up the sspa dai क्रमmat.
 */
अटल पूर्णांक mmp_sspa_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(cpu_dai);

	/* reset port settings */
	sspa->sp   = SSPA_SP_WEN | SSPA_SP_S_RST | SSPA_SP_FFLUSH;
	sspa->ctrl = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		sspa->sp |= SSPA_SP_MSL;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		sspa->sp |= SSPA_SP_FSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		sspa->ctrl |= SSPA_CTL_XDATDLY(1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Since we are configuring the timings क्रम the क्रमmat by hand
	 * we have to defer some things until hw_params() where we
	 * know parameters like the sample size.
	 */
	वापस 0;
पूर्ण

/*
 * Set the SSPA audio DMA parameters and sample size.
 * Can be called multiple बार by oss emulation.
 */
अटल पूर्णांक mmp_sspa_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(dai);
	काष्ठा device *dev = dai->component->dev;
	u32 sspa_ctrl = sspa->ctrl;
	पूर्णांक bits;
	पूर्णांक bitval;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		bits = 8;
		bitval = SSPA_CTL_8_BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		bits = 16;
		bitval = SSPA_CTL_16_BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		bits = 24;
		bitval = SSPA_CTL_24_BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		bits = 32;
		bitval = SSPA_CTL_32_BITS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sspa_ctrl &= ~SSPA_CTL_XPH;
	अगर (dev->of_node || params_channels(params) == 2)
		sspa_ctrl |= SSPA_CTL_XPH;

	sspa_ctrl &= ~SSPA_CTL_XWDLEN1_MASK;
	sspa_ctrl |= SSPA_CTL_XWDLEN1(bitval);

	sspa_ctrl &= ~SSPA_CTL_XWDLEN2_MASK;
	sspa_ctrl |= SSPA_CTL_XWDLEN2(bitval);

	sspa_ctrl &= ~SSPA_CTL_XSSZ1_MASK;
	sspa_ctrl |= SSPA_CTL_XSSZ1(bitval);

	sspa_ctrl &= ~SSPA_CTL_XSSZ2_MASK;
	sspa_ctrl |= SSPA_CTL_XSSZ2(bitval);

	sspa->sp &= ~SSPA_SP_FWID_MASK;
	sspa->sp |= SSPA_SP_FWID(bits - 1);

	sspa->sp &= ~SSPA_TXSP_FPER_MASK;
	sspa->sp |= SSPA_TXSP_FPER(bits * 2 - 1);

	अगर (dev->of_node) अणु
		clk_set_rate(sspa->clk, params_rate(params) *
					params_channels(params) * bits);
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		__raw_ग_लिखोl(sspa_ctrl, sspa->tx_base + SSPA_CTL);
		__raw_ग_लिखोl(0x1, sspa->tx_base + SSPA_FIFO_UL);
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोl(sspa_ctrl, sspa->rx_base + SSPA_CTL);
		__raw_ग_लिखोl(0x0, sspa->rx_base + SSPA_FIFO_UL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_sspa_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/*
		 * whatever playback or capture, must enable rx.
		 * this is a hw issue, so need check अगर rx has been
		 * enabled or not; अगर has been enabled by another
		 * stream, करो not enable again.
		 */
		अगर (!sspa->running_cnt)
			mmp_sspa_rx_enable(sspa);

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			mmp_sspa_tx_enable(sspa);

		sspa->running_cnt++;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		sspa->running_cnt--;

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			mmp_sspa_tx_disable(sspa);

		/* have no capture stream, disable rx port */
		अगर (!sspa->running_cnt)
			mmp_sspa_rx_disable(sspa);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mmp_sspa_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sspa_priv *sspa = dev_get_drvdata(dai->dev);

	snd_soc_dai_init_dma_data(dai,
				&sspa->playback_dma_data,
				&sspa->capture_dma_data);

	वापस 0;
पूर्ण

#घोषणा MMP_SSPA_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा MMP_SSPA_FORMATS (SNDRV_PCM_FMTBIT_S8 | \
		SNDRV_PCM_FMTBIT_S16_LE | \
		SNDRV_PCM_FMTBIT_S24_3LE | \
		SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops mmp_sspa_dai_ops = अणु
	.startup	= mmp_sspa_startup,
	.shutकरोwn	= mmp_sspa_shutकरोwn,
	.trigger	= mmp_sspa_trigger,
	.hw_params	= mmp_sspa_hw_params,
	.set_sysclk	= mmp_sspa_set_dai_sysclk,
	.set_pll	= mmp_sspa_set_dai_pll,
	.set_fmt	= mmp_sspa_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver mmp_sspa_dai = अणु
	.probe = mmp_sspa_probe,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 128,
		.rates = MMP_SSPA_RATES,
		.क्रमmats = MMP_SSPA_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = MMP_SSPA_RATES,
		.क्रमmats = MMP_SSPA_FORMATS,
	पूर्ण,
	.ops = &mmp_sspa_dai_ops,
पूर्ण;

#घोषणा MMP_PCM_INFO (SNDRV_PCM_INFO_MMAP |	\
		SNDRV_PCM_INFO_MMAP_VALID |	\
		SNDRV_PCM_INFO_INTERLEAVED |	\
		SNDRV_PCM_INFO_PAUSE |		\
		SNDRV_PCM_INFO_RESUME |		\
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP)

अटल स्थिर काष्ठा snd_pcm_hardware mmp_pcm_hardware[] = अणु
	अणु
		.info			= MMP_PCM_INFO,
		.period_bytes_min	= 1024,
		.period_bytes_max	= 2048,
		.periods_min		= 2,
		.periods_max		= 32,
		.buffer_bytes_max	= 4096,
		.fअगरo_size		= 32,
	पूर्ण,
	अणु
		.info			= MMP_PCM_INFO,
		.period_bytes_min	= 1024,
		.period_bytes_max	= 2048,
		.periods_min		= 2,
		.periods_max		= 32,
		.buffer_bytes_max	= 4096,
		.fअगरo_size		= 32,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config mmp_pcm_config = अणु
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.pcm_hardware = mmp_pcm_hardware,
	.pपुनः_स्मृति_buffer_size = 4096,
पूर्ण;

अटल पूर्णांक mmp_pcm_mmap(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	वापस remap_pfn_range(vma, vma->vm_start,
		substream->dma_buffer.addr >> PAGE_SHIFT,
		vma->vm_end - vma->vm_start, vma->vm_page_prot);
पूर्ण

अटल पूर्णांक mmp_sspa_खोलो(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sspa_priv *sspa = snd_soc_component_get_drvdata(component);

	pm_runसमय_get_sync(component->dev);

	/* we can only change the settings अगर the port is not in use */
	अगर ((__raw_पढ़ोl(sspa->tx_base + SSPA_SP) & SSPA_SP_S_EN) ||
	    (__raw_पढ़ोl(sspa->rx_base + SSPA_SP) & SSPA_SP_S_EN)) अणु
		dev_err(component->dev,
			"can't change hardware dai format: stream is in use\n");
		वापस -EBUSY;
	पूर्ण

	__raw_ग_लिखोl(sspa->sp, sspa->tx_base + SSPA_SP);
	__raw_ग_लिखोl(sspa->sp, sspa->rx_base + SSPA_SP);

	sspa->sp &= ~(SSPA_SP_S_RST | SSPA_SP_FFLUSH);
	__raw_ग_लिखोl(sspa->sp, sspa->tx_base + SSPA_SP);
	__raw_ग_लिखोl(sspa->sp, sspa->rx_base + SSPA_SP);

	/*
	 * FIXME: hw issue, क्रम the tx serial port,
	 * can not config the master/slave mode;
	 * so must clean this bit.
	 * The master/slave mode has been set in the
	 * rx port.
	 */
	__raw_ग_लिखोl(sspa->sp & ~SSPA_SP_MSL, sspa->tx_base + SSPA_SP);

	__raw_ग_लिखोl(sspa->ctrl, sspa->tx_base + SSPA_CTL);
	__raw_ग_लिखोl(sspa->ctrl, sspa->rx_base + SSPA_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_sspa_बंद(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream)
अणु
	pm_runसमय_put_sync(component->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mmp_sspa_component = अणु
	.name		= "mmp-sspa",
	.mmap		= mmp_pcm_mmap,
	.खोलो		= mmp_sspa_खोलो,
	.बंद		= mmp_sspa_बंद,
पूर्ण;

अटल पूर्णांक asoc_mmp_sspa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sspa_priv *sspa;
	पूर्णांक ret;

	sspa = devm_kzalloc(&pdev->dev,
				माप(काष्ठा sspa_priv), GFP_KERNEL);
	अगर (!sspa)
		वापस -ENOMEM;

	अगर (pdev->dev.of_node) अणु
		sspa->rx_base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(sspa->rx_base))
			वापस PTR_ERR(sspa->rx_base);

		sspa->tx_base = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(sspa->tx_base))
			वापस PTR_ERR(sspa->tx_base);

		sspa->clk = devm_clk_get(&pdev->dev, "bitclk");
		अगर (IS_ERR(sspa->clk))
			वापस PTR_ERR(sspa->clk);

		sspa->audio_clk = devm_clk_get(&pdev->dev, "audio");
		अगर (IS_ERR(sspa->audio_clk))
			वापस PTR_ERR(sspa->audio_clk);
	पूर्ण अन्यथा अणु
		काष्ठा resource *res;

		res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
		अगर (res == शून्य)
			वापस -ENODEV;

		sspa->rx_base = devm_ioremap(&pdev->dev, res->start, 0x30);
		अगर (!sspa->rx_base)
			वापस -ENOMEM;

		sspa->tx_base = devm_ioremap(&pdev->dev,
					     res->start + 0x80, 0x30);
		अगर (!sspa->tx_base)
			वापस -ENOMEM;

		sspa->clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(sspa->clk))
			वापस PTR_ERR(sspa->clk);

		sspa->audio_clk = clk_get(शून्य, "mmp-audio");
		अगर (IS_ERR(sspa->audio_clk))
			वापस PTR_ERR(sspa->audio_clk);

		sspa->sysclk = clk_get(शून्य, "mmp-sysclk");
		अगर (IS_ERR(sspa->sysclk)) अणु
			clk_put(sspa->audio_clk);
			वापस PTR_ERR(sspa->sysclk);
		पूर्ण
	पूर्ण
	platक्रमm_set_drvdata(pdev, sspa);

	sspa->playback_dma_data.maxburst = 4;
	sspa->capture_dma_data.maxburst = 4;
	/* You know, these addresses are actually ignored. */
	sspa->capture_dma_data.addr = SSPA_D;
	sspa->playback_dma_data.addr = 0x80 + SSPA_D;

	अगर (pdev->dev.of_node) अणु
		ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev,
						      &mmp_pcm_config, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &mmp_sspa_component,
					      &mmp_sspa_dai, 1);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&pdev->dev);
	clk_prepare_enable(sspa->audio_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक asoc_mmp_sspa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sspa_priv *sspa = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(sspa->audio_clk);
	pm_runसमय_disable(&pdev->dev);

	अगर (pdev->dev.of_node)
		वापस 0;

	clk_put(sspa->audio_clk);
	clk_put(sspa->sysclk);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mmp_sspa_of_match[] = अणु
	अणु .compatible = "marvell,mmp-sspa" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mmp_sspa_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver asoc_mmp_sspa_driver = अणु
	.driver = अणु
		.name = "mmp-sspa-dai",
		.of_match_table = of_match_ptr(mmp_sspa_of_match),
	पूर्ण,
	.probe = asoc_mmp_sspa_probe,
	.हटाओ = asoc_mmp_sspa_हटाओ,
पूर्ण;

module_platक्रमm_driver(asoc_mmp_sspa_driver);

MODULE_AUTHOR("Leo Yan <leoy@marvell.com>");
MODULE_DESCRIPTION("MMP SSPA SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mmp-sspa-dai");
