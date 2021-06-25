<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// AMD ALSA SoC PDM Driver
//
//Copyright 2020 Advanced Micro Devices, Inc.

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "rn_acp3x.h"

#घोषणा DRV_NAME "acp_rn_pdm_dma"

अटल स्थिर काष्ठा snd_pcm_hardware acp_pdm_hardware_capture = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 2,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 48000,
	.rate_max = 48000,
	.buffer_bytes_max = CAPTURE_MAX_NUM_PERIODS * CAPTURE_MAX_PERIOD_SIZE,
	.period_bytes_min = CAPTURE_MIN_PERIOD_SIZE,
	.period_bytes_max = CAPTURE_MAX_PERIOD_SIZE,
	.periods_min = CAPTURE_MIN_NUM_PERIODS,
	.periods_max = CAPTURE_MAX_NUM_PERIODS,
पूर्ण;

अटल irqवापस_t pdm_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pdm_dev_data *rn_pdm_data;
	u16 cap_flag;
	u32 val;

	rn_pdm_data = dev_id;
	अगर (!rn_pdm_data)
		वापस IRQ_NONE;

	cap_flag = 0;
	val = rn_पढ़ोl(rn_pdm_data->acp_base + ACP_EXTERNAL_INTR_STAT);
	अगर ((val & BIT(PDM_DMA_STAT)) && rn_pdm_data->capture_stream) अणु
		rn_ग_लिखोl(BIT(PDM_DMA_STAT), rn_pdm_data->acp_base +
			  ACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rn_pdm_data->capture_stream);
		cap_flag = 1;
	पूर्ण

	अगर (cap_flag)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम init_pdm_ring_buffer(u32 physical_addr,
				 u32 buffer_size,
				 u32 watermark_size,
				 व्योम __iomem *acp_base)
अणु
	rn_ग_लिखोl(physical_addr, acp_base + ACP_WOV_RX_RINGBUFADDR);
	rn_ग_लिखोl(buffer_size, acp_base + ACP_WOV_RX_RINGबफ_मानE);
	rn_ग_लिखोl(watermark_size, acp_base + ACP_WOV_RX_INTR_WATERMARK_SIZE);
	rn_ग_लिखोl(0x01, acp_base + ACPAXI2AXI_ATU_CTRL);
पूर्ण

अटल व्योम enable_pdm_घड़ी(व्योम __iomem *acp_base)
अणु
	u32 pdm_clk_enable, pdm_ctrl;

	pdm_clk_enable = ACP_PDM_CLK_FREQ_MASK;
	pdm_ctrl = 0x00;

	rn_ग_लिखोl(pdm_clk_enable, acp_base + ACP_WOV_CLK_CTRL);
	pdm_ctrl = rn_पढ़ोl(acp_base + ACP_WOV_MISC_CTRL);
	pdm_ctrl |= ACP_WOV_MISC_CTRL_MASK;
	rn_ग_लिखोl(pdm_ctrl, acp_base + ACP_WOV_MISC_CTRL);
पूर्ण

अटल व्योम enable_pdm_पूर्णांकerrupts(व्योम __iomem *acp_base)
अणु
	u32 ext_पूर्णांक_ctrl;

	ext_पूर्णांक_ctrl = rn_पढ़ोl(acp_base + ACP_EXTERNAL_INTR_CNTL);
	ext_पूर्णांक_ctrl |= PDM_DMA_INTR_MASK;
	rn_ग_लिखोl(ext_पूर्णांक_ctrl, acp_base + ACP_EXTERNAL_INTR_CNTL);
पूर्ण

अटल व्योम disable_pdm_पूर्णांकerrupts(व्योम __iomem *acp_base)
अणु
	u32 ext_पूर्णांक_ctrl;

	ext_पूर्णांक_ctrl = rn_पढ़ोl(acp_base + ACP_EXTERNAL_INTR_CNTL);
	ext_पूर्णांक_ctrl |= ~PDM_DMA_INTR_MASK;
	rn_ग_लिखोl(ext_पूर्णांक_ctrl, acp_base + ACP_EXTERNAL_INTR_CNTL);
पूर्ण

अटल bool check_pdm_dma_status(व्योम __iomem *acp_base)
अणु
	bool pdm_dma_status;
	u32 pdm_enable, pdm_dma_enable;

	pdm_dma_status = false;
	pdm_enable = rn_पढ़ोl(acp_base + ACP_WOV_PDM_ENABLE);
	pdm_dma_enable = rn_पढ़ोl(acp_base + ACP_WOV_PDM_DMA_ENABLE);
	अगर ((pdm_enable & ACP_PDM_ENABLE) && (pdm_dma_enable &
	     ACP_PDM_DMA_EN_STATUS))
		pdm_dma_status = true;
	वापस pdm_dma_status;
पूर्ण

अटल पूर्णांक start_pdm_dma(व्योम __iomem *acp_base)
अणु
	u32 pdm_enable;
	u32 pdm_dma_enable;
	पूर्णांक समयout;

	pdm_enable = 0x01;
	pdm_dma_enable  = 0x01;

	enable_pdm_घड़ी(acp_base);
	rn_ग_लिखोl(pdm_enable, acp_base + ACP_WOV_PDM_ENABLE);
	rn_ग_लिखोl(pdm_dma_enable, acp_base + ACP_WOV_PDM_DMA_ENABLE);
	समयout = 0;
	जबतक (++समयout < ACP_COUNTER) अणु
		pdm_dma_enable = rn_पढ़ोl(acp_base + ACP_WOV_PDM_DMA_ENABLE);
		अगर ((pdm_dma_enable & 0x02) == ACP_PDM_DMA_EN_STATUS)
			वापस 0;
		udelay(DELAY_US);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक stop_pdm_dma(व्योम __iomem *acp_base)
अणु
	u32 pdm_enable, pdm_dma_enable;
	पूर्णांक समयout;

	pdm_enable = 0x00;
	pdm_dma_enable  = 0x00;

	pdm_enable = rn_पढ़ोl(acp_base + ACP_WOV_PDM_ENABLE);
	pdm_dma_enable = rn_पढ़ोl(acp_base + ACP_WOV_PDM_DMA_ENABLE);
	अगर (pdm_dma_enable & 0x01) अणु
		pdm_dma_enable = 0x02;
		rn_ग_लिखोl(pdm_dma_enable, acp_base + ACP_WOV_PDM_DMA_ENABLE);
		समयout = 0;
		जबतक (++समयout < ACP_COUNTER) अणु
			pdm_dma_enable = rn_पढ़ोl(acp_base +
						  ACP_WOV_PDM_DMA_ENABLE);
			अगर ((pdm_dma_enable & 0x02) == 0x00)
				अवरोध;
			udelay(DELAY_US);
		पूर्ण
		अगर (समयout == ACP_COUNTER)
			वापस -ETIMEDOUT;
	पूर्ण
	अगर (pdm_enable == ACP_PDM_ENABLE) अणु
		pdm_enable = ACP_PDM_DISABLE;
		rn_ग_लिखोl(pdm_enable, acp_base + ACP_WOV_PDM_ENABLE);
	पूर्ण
	rn_ग_लिखोl(0x01, acp_base + ACP_WOV_PDM_FIFO_FLUSH);
	वापस 0;
पूर्ण

अटल व्योम config_acp_dma(काष्ठा pdm_stream_instance *rtd, पूर्णांक direction)
अणु
	u16 page_idx;
	u32 low, high, val;
	dma_addr_t addr;

	addr = rtd->dma_addr;
	val = 0;

	/* Group Enable */
	rn_ग_लिखोl(ACP_SRAM_PTE_OFFSET | BIT(31), rtd->acp_base +
		  ACPAXI2AXI_ATU_BASE_ADDR_GRP_1);
	rn_ग_लिखोl(PAGE_SIZE_4K_ENABLE, rtd->acp_base +
		  ACPAXI2AXI_ATU_PAGE_SIZE_GRP_1);

	क्रम (page_idx = 0; page_idx < rtd->num_pages; page_idx++) अणु
		/* Load the low address of page पूर्णांक ACP SRAM through SRBM */
		low = lower_32_bits(addr);
		high = upper_32_bits(addr);

		rn_ग_लिखोl(low, rtd->acp_base + ACP_SCRATCH_REG_0 + val);
		high |= BIT(31);
		rn_ग_लिखोl(high, rtd->acp_base + ACP_SCRATCH_REG_0 + val + 4);
		val += 8;
		addr += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक acp_pdm_dma_खोलो(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा pdm_dev_data *adata;
	काष्ठा pdm_stream_instance *pdm_data;
	पूर्णांक ret;

	runसमय = substream->runसमय;
	adata = dev_get_drvdata(component->dev);
	pdm_data = kzalloc(माप(*pdm_data), GFP_KERNEL);
	अगर (!pdm_data)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		runसमय->hw = acp_pdm_hardware_capture;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		dev_err(component->dev, "set integer constraint failed\n");
		kमुक्त(pdm_data);
		वापस ret;
	पूर्ण

	enable_pdm_पूर्णांकerrupts(adata->acp_base);

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		adata->capture_stream = substream;

	pdm_data->acp_base = adata->acp_base;
	runसमय->निजी_data = pdm_data;
	वापस ret;
पूर्ण

अटल पूर्णांक acp_pdm_dma_hw_params(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा pdm_stream_instance *rtd;
	माप_प्रकार size, period_bytes;

	rtd = substream->runसमय->निजी_data;
	अगर (!rtd)
		वापस -EINVAL;
	size = params_buffer_bytes(params);
	period_bytes = params_period_bytes(params);
	rtd->dma_addr = substream->dma_buffer.addr;
	rtd->num_pages = (PAGE_ALIGN(size) >> PAGE_SHIFT);
	config_acp_dma(rtd, substream->stream);
	init_pdm_ring_buffer(MEM_WINDOW_START, size, period_bytes,
			     rtd->acp_base);
	वापस 0;
पूर्ण

अटल u64 acp_pdm_get_byte_count(काष्ठा pdm_stream_instance *rtd,
				  पूर्णांक direction)
अणु
	जोड़ acp_pdm_dma_count byte_count;

	byte_count.bcount.high =
			rn_पढ़ोl(rtd->acp_base +
				 ACP_WOV_RX_LINEARPOSITIONCNTR_HIGH);
	byte_count.bcount.low =
			rn_पढ़ोl(rtd->acp_base +
				 ACP_WOV_RX_LINEARPOSITIONCNTR_LOW);
	वापस byte_count.bytescount;
पूर्ण

अटल snd_pcm_uframes_t acp_pdm_dma_poपूर्णांकer(काष्ठा snd_soc_component *comp,
					     काष्ठा snd_pcm_substream *stream)
अणु
	काष्ठा pdm_stream_instance *rtd;
	u32 pos, buffersize;
	u64 bytescount;

	rtd = stream->runसमय->निजी_data;
	buffersize = frames_to_bytes(stream->runसमय,
				     stream->runसमय->buffer_size);
	bytescount = acp_pdm_get_byte_count(rtd, stream->stream);
	अगर (bytescount > rtd->bytescount)
		bytescount -= rtd->bytescount;
	pos = करो_भाग(bytescount, buffersize);
	वापस bytes_to_frames(stream->runसमय, pos);
पूर्ण

अटल पूर्णांक acp_pdm_dma_new(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा device *parent = component->dev->parent;

	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_DEV,
				       parent, MIN_BUFFER, MAX_BUFFER);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pdm_dma_mmap(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream,
			    काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस snd_pcm_lib_शेष_mmap(substream, vma);
पूर्ण

अटल पूर्णांक acp_pdm_dma_बंद(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा pdm_dev_data *adata = dev_get_drvdata(component->dev);

	disable_pdm_पूर्णांकerrupts(adata->acp_base);
	adata->capture_stream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pdm_dai_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा pdm_stream_instance *rtd;
	पूर्णांक ret;
	bool pdm_status;
	अचिन्हित पूर्णांक ch_mask;

	rtd = substream->runसमय->निजी_data;
	ret = 0;
	चयन (substream->runसमय->channels) अणु
	हाल TWO_CH:
		ch_mask = 0x00;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		rn_ग_लिखोl(ch_mask, rtd->acp_base + ACP_WOV_PDM_NO_OF_CHANNELS);
		rn_ग_लिखोl(PDM_DECIMATION_FACTOR, rtd->acp_base +
			  ACP_WOV_PDM_DECIMATION_FACTOR);
		rtd->bytescount = acp_pdm_get_byte_count(rtd,
							 substream->stream);
		pdm_status = check_pdm_dma_status(rtd->acp_base);
		अगर (!pdm_status)
			ret = start_pdm_dma(rtd->acp_base);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		pdm_status = check_pdm_dma_status(rtd->acp_base);
		अगर (pdm_status)
			ret = stop_pdm_dma(rtd->acp_base);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops acp_pdm_dai_ops = अणु
	.trigger   = acp_pdm_dai_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver acp_pdm_dai_driver = अणु
	.capture = अणु
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE,
		.channels_min = 2,
		.channels_max = 2,
		.rate_min = 48000,
		.rate_max = 48000,
	पूर्ण,
	.ops = &acp_pdm_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver acp_pdm_component = अणु
	.name		= DRV_NAME,
	.खोलो		= acp_pdm_dma_खोलो,
	.बंद		= acp_pdm_dma_बंद,
	.hw_params	= acp_pdm_dma_hw_params,
	.poपूर्णांकer	= acp_pdm_dma_poपूर्णांकer,
	.mmap		= acp_pdm_dma_mmap,
	.pcm_स्थिरruct	= acp_pdm_dma_new,
पूर्ण;

अटल पूर्णांक acp_pdm_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा pdm_dev_data *adata;
	अचिन्हित पूर्णांक irqflags;
	पूर्णांक status;

	अगर (!pdev->dev.platक्रमm_data) अणु
		dev_err(&pdev->dev, "platform_data not retrieved\n");
		वापस -ENODEV;
	पूर्ण
	irqflags = *((अचिन्हित पूर्णांक *)(pdev->dev.platक्रमm_data));

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "IORESOURCE_MEM FAILED\n");
		वापस -ENODEV;
	पूर्ण

	adata = devm_kzalloc(&pdev->dev, माप(*adata), GFP_KERNEL);
	अगर (!adata)
		वापस -ENOMEM;

	adata->acp_base = devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	अगर (!adata->acp_base)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "IORESOURCE_IRQ FAILED\n");
		वापस -ENODEV;
	पूर्ण

	adata->pdm_irq = res->start;
	adata->capture_stream = शून्य;

	dev_set_drvdata(&pdev->dev, adata);
	status = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
						 &acp_pdm_component,
						 &acp_pdm_dai_driver, 1);
	अगर (status) अणु
		dev_err(&pdev->dev, "Fail to register acp pdm dai\n");

		वापस -ENODEV;
	पूर्ण
	status = devm_request_irq(&pdev->dev, adata->pdm_irq, pdm_irq_handler,
				  irqflags, "ACP_PDM_IRQ", adata);
	अगर (status) अणु
		dev_err(&pdev->dev, "ACP PDM IRQ request failed\n");
		वापस -ENODEV;
	पूर्ण
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, ACP_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pdm_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pdm_resume(काष्ठा device *dev)
अणु
	काष्ठा pdm_dev_data *adata;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा pdm_stream_instance *rtd;
	u32 period_bytes, buffer_len;

	adata = dev_get_drvdata(dev);
	अगर (adata->capture_stream && adata->capture_stream->runसमय) अणु
		runसमय = adata->capture_stream->runसमय;
		rtd = runसमय->निजी_data;
		period_bytes = frames_to_bytes(runसमय, runसमय->period_size);
		buffer_len = frames_to_bytes(runसमय, runसमय->buffer_size);
		config_acp_dma(rtd, SNDRV_PCM_STREAM_CAPTURE);
		init_pdm_ring_buffer(MEM_WINDOW_START, buffer_len, period_bytes,
				     adata->acp_base);
	पूर्ण
	enable_pdm_पूर्णांकerrupts(adata->acp_base);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_pdm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pdm_dev_data *adata;

	adata = dev_get_drvdata(dev);
	disable_pdm_पूर्णांकerrupts(adata->acp_base);

	वापस 0;
पूर्ण

अटल पूर्णांक acp_pdm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pdm_dev_data *adata;

	adata = dev_get_drvdata(dev);
	enable_pdm_पूर्णांकerrupts(adata->acp_base);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops acp_pdm_pm_ops = अणु
	.runसमय_suspend = acp_pdm_runसमय_suspend,
	.runसमय_resume = acp_pdm_runसमय_resume,
	.resume = acp_pdm_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver acp_pdm_dma_driver = अणु
	.probe = acp_pdm_audio_probe,
	.हटाओ = acp_pdm_audio_हटाओ,
	.driver = अणु
		.name = "acp_rn_pdm_dma",
		.pm = &acp_pdm_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(acp_pdm_dma_driver);

MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_DESCRIPTION("AMD ACP3x Renior PDM Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
