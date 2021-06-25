<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC Audio Layer - Samsung S/PDIF Controller driver
//
// Copyright (c) 2010 Samsung Electronics Co. Ltd
//		http://www.samsung.com/

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश <linux/platक्रमm_data/asoc-s3c.h>

#समावेश "dma.h"
#समावेश "spdif.h"

/* Registers */
#घोषणा CLKCON				0x00
#घोषणा CON				0x04
#घोषणा BSTAS				0x08
#घोषणा CSTAS				0x0C
#घोषणा DATA_OUTBUF			0x10
#घोषणा DCNT				0x14
#घोषणा BSTAS_S				0x18
#घोषणा DCNT_S				0x1C

#घोषणा CLKCTL_MASK			0x7
#घोषणा CLKCTL_MCLK_EXT			(0x1 << 2)
#घोषणा CLKCTL_PWR_ON			(0x1 << 0)

#घोषणा CON_MASK			0x3ffffff
#घोषणा CON_FIFO_TH_SHIFT		19
#घोषणा CON_FIFO_TH_MASK		(0x7 << 19)
#घोषणा CON_USERDATA_23RDBIT		(0x1 << 12)

#घोषणा CON_SW_RESET			(0x1 << 5)

#घोषणा CON_MCLKDIV_MASK		(0x3 << 3)
#घोषणा CON_MCLKDIV_256FS		(0x0 << 3)
#घोषणा CON_MCLKDIV_384FS		(0x1 << 3)
#घोषणा CON_MCLKDIV_512FS		(0x2 << 3)

#घोषणा CON_PCM_MASK			(0x3 << 1)
#घोषणा CON_PCM_16BIT			(0x0 << 1)
#घोषणा CON_PCM_20BIT			(0x1 << 1)
#घोषणा CON_PCM_24BIT			(0x2 << 1)

#घोषणा CON_PCM_DATA			(0x1 << 0)

#घोषणा CSTAS_MASK			0x3fffffff
#घोषणा CSTAS_SAMP_FREQ_MASK		(0xF << 24)
#घोषणा CSTAS_SAMP_FREQ_44		(0x0 << 24)
#घोषणा CSTAS_SAMP_FREQ_48		(0x2 << 24)
#घोषणा CSTAS_SAMP_FREQ_32		(0x3 << 24)
#घोषणा CSTAS_SAMP_FREQ_96		(0xA << 24)

#घोषणा CSTAS_CATEGORY_MASK		(0xFF << 8)
#घोषणा CSTAS_CATEGORY_CODE_CDP		(0x01 << 8)

#घोषणा CSTAS_NO_COPYRIGHT		(0x1 << 2)

/**
 * काष्ठा samsung_spdअगर_info - Samsung S/PDIF Controller inक्रमmation
 * @lock: Spin lock क्रम S/PDIF.
 * @dev: The parent device passed to use from the probe.
 * @regs: The poपूर्णांकer to the device रेजिस्टर block.
 * @clk_rate: Current घड़ी rate क्रम calcurate ratio.
 * @pclk: The peri-घड़ी poपूर्णांकer क्रम spdअगर master operation.
 * @sclk: The source घड़ी poपूर्णांकer क्रम making sync संकेतs.
 * @saved_clkcon: Backup clkcon reg. in suspend.
 * @saved_con: Backup con reg. in suspend.
 * @saved_cstas: Backup cstas reg. in suspend.
 * @dma_playback: DMA inक्रमmation क्रम playback channel.
 */
काष्ठा samsung_spdअगर_info अणु
	spinlock_t	lock;
	काष्ठा device	*dev;
	व्योम __iomem	*regs;
	अचिन्हित दीर्घ	clk_rate;
	काष्ठा clk	*pclk;
	काष्ठा clk	*sclk;
	u32		saved_clkcon;
	u32		saved_con;
	u32		saved_cstas;
	काष्ठा snd_dmaengine_dai_dma_data *dma_playback;
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data spdअगर_stereo_out;
अटल काष्ठा samsung_spdअगर_info spdअगर_info;

अटल अंतरभूत काष्ठा samsung_spdअगर_info
*component_to_info(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_get_drvdata(component);
पूर्ण

अटल अंतरभूत काष्ठा samsung_spdअगर_info *to_info(काष्ठा snd_soc_dai *cpu_dai)
अणु
	वापस snd_soc_dai_get_drvdata(cpu_dai);
पूर्ण

अटल व्योम spdअगर_snd_txctrl(काष्ठा samsung_spdअगर_info *spdअगर, पूर्णांक on)
अणु
	व्योम __iomem *regs = spdअगर->regs;
	u32 clkcon;

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	clkcon = पढ़ोl(regs + CLKCON) & CLKCTL_MASK;
	अगर (on)
		ग_लिखोl(clkcon | CLKCTL_PWR_ON, regs + CLKCON);
	अन्यथा
		ग_लिखोl(clkcon & ~CLKCTL_PWR_ON, regs + CLKCON);
पूर्ण

अटल पूर्णांक spdअगर_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा samsung_spdअगर_info *spdअगर = to_info(cpu_dai);
	u32 clkcon;

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	clkcon = पढ़ोl(spdअगर->regs + CLKCON);

	अगर (clk_id == SND_SOC_SPDIF_INT_MCLK)
		clkcon &= ~CLKCTL_MCLK_EXT;
	अन्यथा
		clkcon |= CLKCTL_MCLK_EXT;

	ग_लिखोl(clkcon, spdअगर->regs + CLKCON);

	spdअगर->clk_rate = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा samsung_spdअगर_info *spdअगर = to_info(asoc_rtd_to_cpu(rtd, 0));
	अचिन्हित दीर्घ flags;

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irqsave(&spdअगर->lock, flags);
		spdअगर_snd_txctrl(spdअगर, 1);
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&spdअगर->lock, flags);
		spdअगर_snd_txctrl(spdअगर, 0);
		spin_unlock_irqrestore(&spdअगर->lock, flags);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_sysclk_ratios[] = अणु
	512, 384, 256,
पूर्ण;

अटल पूर्णांक spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *socdai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा samsung_spdअगर_info *spdअगर = to_info(asoc_rtd_to_cpu(rtd, 0));
	व्योम __iomem *regs = spdअगर->regs;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	u32 con, clkcon, cstas;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ratio;

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = spdअगर->dma_playback;
	अन्यथा अणु
		dev_err(spdअगर->dev, "Capture is not supported\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_dai_set_dma_data(asoc_rtd_to_cpu(rtd, 0), substream, dma_data);

	spin_lock_irqsave(&spdअगर->lock, flags);

	con = पढ़ोl(regs + CON) & CON_MASK;
	cstas = पढ़ोl(regs + CSTAS) & CSTAS_MASK;
	clkcon = पढ़ोl(regs + CLKCON) & CLKCTL_MASK;

	con &= ~CON_FIFO_TH_MASK;
	con |= (0x7 << CON_FIFO_TH_SHIFT);
	con |= CON_USERDATA_23RDBIT;
	con |= CON_PCM_DATA;

	con &= ~CON_PCM_MASK;
	चयन (params_width(params)) अणु
	हाल 16:
		con |= CON_PCM_16BIT;
		अवरोध;
	शेष:
		dev_err(spdअगर->dev, "Unsupported data size.\n");
		जाओ err;
	पूर्ण

	ratio = spdअगर->clk_rate / params_rate(params);
	क्रम (i = 0; i < ARRAY_SIZE(spdअगर_sysclk_ratios); i++)
		अगर (ratio == spdअगर_sysclk_ratios[i])
			अवरोध;
	अगर (i == ARRAY_SIZE(spdअगर_sysclk_ratios)) अणु
		dev_err(spdअगर->dev, "Invalid clock ratio %ld/%d\n",
				spdअगर->clk_rate, params_rate(params));
		जाओ err;
	पूर्ण

	con &= ~CON_MCLKDIV_MASK;
	चयन (ratio) अणु
	हाल 256:
		con |= CON_MCLKDIV_256FS;
		अवरोध;
	हाल 384:
		con |= CON_MCLKDIV_384FS;
		अवरोध;
	हाल 512:
		con |= CON_MCLKDIV_512FS;
		अवरोध;
	पूर्ण

	cstas &= ~CSTAS_SAMP_FREQ_MASK;
	चयन (params_rate(params)) अणु
	हाल 44100:
		cstas |= CSTAS_SAMP_FREQ_44;
		अवरोध;
	हाल 48000:
		cstas |= CSTAS_SAMP_FREQ_48;
		अवरोध;
	हाल 32000:
		cstas |= CSTAS_SAMP_FREQ_32;
		अवरोध;
	हाल 96000:
		cstas |= CSTAS_SAMP_FREQ_96;
		अवरोध;
	शेष:
		dev_err(spdअगर->dev, "Invalid sampling rate %d\n",
				params_rate(params));
		जाओ err;
	पूर्ण

	cstas &= ~CSTAS_CATEGORY_MASK;
	cstas |= CSTAS_CATEGORY_CODE_CDP;
	cstas |= CSTAS_NO_COPYRIGHT;

	ग_लिखोl(con, regs + CON);
	ग_लिखोl(cstas, regs + CSTAS);
	ग_लिखोl(clkcon, regs + CLKCON);

	spin_unlock_irqrestore(&spdअगर->lock, flags);

	वापस 0;
err:
	spin_unlock_irqrestore(&spdअगर->lock, flags);
	वापस -EINVAL;
पूर्ण

अटल व्योम spdअगर_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा samsung_spdअगर_info *spdअगर = to_info(asoc_rtd_to_cpu(rtd, 0));
	व्योम __iomem *regs = spdअगर->regs;
	u32 con, clkcon;

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	con = पढ़ोl(regs + CON) & CON_MASK;
	clkcon = पढ़ोl(regs + CLKCON) & CLKCTL_MASK;

	ग_लिखोl(con | CON_SW_RESET, regs + CON);
	cpu_relax();

	ग_लिखोl(clkcon & ~CLKCTL_PWR_ON, regs + CLKCON);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक spdअगर_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा samsung_spdअगर_info *spdअगर = component_to_info(component);
	u32 con = spdअगर->saved_con;

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	spdअगर->saved_clkcon = पढ़ोl(spdअगर->regs	+ CLKCON) & CLKCTL_MASK;
	spdअगर->saved_con = पढ़ोl(spdअगर->regs + CON) & CON_MASK;
	spdअगर->saved_cstas = पढ़ोl(spdअगर->regs + CSTAS) & CSTAS_MASK;

	ग_लिखोl(con | CON_SW_RESET, spdअगर->regs + CON);
	cpu_relax();

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा samsung_spdअगर_info *spdअगर = component_to_info(component);

	dev_dbg(spdअगर->dev, "Entered %s\n", __func__);

	ग_लिखोl(spdअगर->saved_clkcon, spdअगर->regs	+ CLKCON);
	ग_लिखोl(spdअगर->saved_con, spdअगर->regs + CON);
	ग_लिखोl(spdअगर->saved_cstas, spdअगर->regs + CSTAS);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा spdअगर_suspend शून्य
#घोषणा spdअगर_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_dai_ops spdअगर_dai_ops = अणु
	.set_sysclk	= spdअगर_set_sysclk,
	.trigger	= spdअगर_trigger,
	.hw_params	= spdअगर_hw_params,
	.shutकरोwn	= spdअगर_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver samsung_spdअगर_dai = अणु
	.name = "samsung-spdif",
	.playback = अणु
		.stream_name = "S/PDIF Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_32000 |
				SNDRV_PCM_RATE_44100 |
				SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_96000),
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE, पूर्ण,
	.ops = &spdअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver samsung_spdअगर_component = अणु
	.name		= "samsung-spdif",
	.suspend	= spdअगर_suspend,
	.resume		= spdअगर_resume,
पूर्ण;

अटल पूर्णांक spdअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_audio_pdata *spdअगर_pdata;
	काष्ठा resource *mem_res;
	काष्ठा samsung_spdअगर_info *spdअगर;
	dma_filter_fn filter;
	पूर्णांक ret;

	spdअगर_pdata = pdev->dev.platक्रमm_data;

	dev_dbg(&pdev->dev, "Entered %s\n", __func__);

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem_res) अणु
		dev_err(&pdev->dev, "Unable to get register resource.\n");
		वापस -ENXIO;
	पूर्ण

	अगर (spdअगर_pdata && spdअगर_pdata->cfg_gpio
			&& spdअगर_pdata->cfg_gpio(pdev)) अणु
		dev_err(&pdev->dev, "Unable to configure GPIO pins\n");
		वापस -EINVAL;
	पूर्ण

	spdअगर = &spdअगर_info;
	spdअगर->dev = &pdev->dev;

	spin_lock_init(&spdअगर->lock);

	spdअगर->pclk = devm_clk_get(&pdev->dev, "spdif");
	अगर (IS_ERR(spdअगर->pclk)) अणु
		dev_err(&pdev->dev, "failed to get peri-clock\n");
		ret = -ENOENT;
		जाओ err0;
	पूर्ण
	ret = clk_prepare_enable(spdअगर->pclk);
	अगर (ret)
		जाओ err0;

	spdअगर->sclk = devm_clk_get(&pdev->dev, "sclk_spdif");
	अगर (IS_ERR(spdअगर->sclk)) अणु
		dev_err(&pdev->dev, "failed to get internal source clock\n");
		ret = -ENOENT;
		जाओ err1;
	पूर्ण
	ret = clk_prepare_enable(spdअगर->sclk);
	अगर (ret)
		जाओ err1;

	/* Request S/PDIF Register's memory region */
	अगर (!request_mem_region(mem_res->start,
				resource_size(mem_res), "samsung-spdif")) अणु
		dev_err(&pdev->dev, "Unable to request register region\n");
		ret = -EBUSY;
		जाओ err2;
	पूर्ण

	spdअगर->regs = ioremap(mem_res->start, 0x100);
	अगर (spdअगर->regs == शून्य) अणु
		dev_err(&pdev->dev, "Cannot ioremap registers\n");
		ret = -ENXIO;
		जाओ err3;
	पूर्ण

	spdअगर_stereo_out.addr_width = 2;
	spdअगर_stereo_out.addr = mem_res->start + DATA_OUTBUF;
	filter = शून्य;
	अगर (spdअगर_pdata) अणु
		spdअगर_stereo_out.filter_data = spdअगर_pdata->dma_playback;
		filter = spdअगर_pdata->dma_filter;
	पूर्ण
	spdअगर->dma_playback = &spdअगर_stereo_out;

	ret = samsung_asoc_dma_platक्रमm_रेजिस्टर(&pdev->dev, filter,
						 शून्य, शून्य, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register DMA: %d\n", ret);
		जाओ err4;
	पूर्ण

	dev_set_drvdata(&pdev->dev, spdअगर);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&samsung_spdअगर_component, &samsung_spdअगर_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "fail to register dai\n");
		जाओ err4;
	पूर्ण

	वापस 0;
err4:
	iounmap(spdअगर->regs);
err3:
	release_mem_region(mem_res->start, resource_size(mem_res));
err2:
	clk_disable_unprepare(spdअगर->sclk);
err1:
	clk_disable_unprepare(spdअगर->pclk);
err0:
	वापस ret;
पूर्ण

अटल पूर्णांक spdअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा samsung_spdअगर_info *spdअगर = &spdअगर_info;
	काष्ठा resource *mem_res;

	iounmap(spdअगर->regs);

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (mem_res)
		release_mem_region(mem_res->start, resource_size(mem_res));

	clk_disable_unprepare(spdअगर->sclk);
	clk_disable_unprepare(spdअगर->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver samsung_spdअगर_driver = अणु
	.probe	= spdअगर_probe,
	.हटाओ	= spdअगर_हटाओ,
	.driver	= अणु
		.name	= "samsung-spdif",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(samsung_spdअगर_driver);

MODULE_AUTHOR("Seungwhan Youn, <sw.youn@samsung.com>");
MODULE_DESCRIPTION("Samsung S/PDIF Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:samsung-spdif");
