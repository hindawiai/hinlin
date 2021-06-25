<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// AMD ALSA SoC PCM Driver
//
//Copyright 2016 Advanced Micro Devices, Inc.

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "acp3x.h"

#घोषणा DRV_NAME "acp3x_rv_i2s_dma"

अटल स्थिर काष्ठा snd_pcm_hardware acp3x_pcm_hardware_playback = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |  SNDRV_PCM_FMTBIT_S8 |
		   SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 2,
	.channels_max = 8,
	.rates = SNDRV_PCM_RATE_8000_96000,
	.rate_min = 8000,
	.rate_max = 96000,
	.buffer_bytes_max = PLAYBACK_MAX_NUM_PERIODS * PLAYBACK_MAX_PERIOD_SIZE,
	.period_bytes_min = PLAYBACK_MIN_PERIOD_SIZE,
	.period_bytes_max = PLAYBACK_MAX_PERIOD_SIZE,
	.periods_min = PLAYBACK_MIN_NUM_PERIODS,
	.periods_max = PLAYBACK_MAX_NUM_PERIODS,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware acp3x_pcm_hardware_capture = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8 |
		   SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 2,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_8000_48000,
	.rate_min = 8000,
	.rate_max = 48000,
	.buffer_bytes_max = CAPTURE_MAX_NUM_PERIODS * CAPTURE_MAX_PERIOD_SIZE,
	.period_bytes_min = CAPTURE_MIN_PERIOD_SIZE,
	.period_bytes_max = CAPTURE_MAX_PERIOD_SIZE,
	.periods_min = CAPTURE_MIN_NUM_PERIODS,
	.periods_max = CAPTURE_MAX_NUM_PERIODS,
पूर्ण;

अटल irqवापस_t i2s_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2s_dev_data *rv_i2s_data;
	u16 play_flag, cap_flag;
	u32 val;

	rv_i2s_data = dev_id;
	अगर (!rv_i2s_data)
		वापस IRQ_NONE;

	play_flag = 0;
	cap_flag = 0;
	val = rv_पढ़ोl(rv_i2s_data->acp3x_base + mmACP_EXTERNAL_INTR_STAT);
	अगर ((val & BIT(BT_TX_THRESHOLD)) && rv_i2s_data->play_stream) अणु
		rv_ग_लिखोl(BIT(BT_TX_THRESHOLD), rv_i2s_data->acp3x_base +
			  mmACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rv_i2s_data->play_stream);
		play_flag = 1;
	पूर्ण
	अगर ((val & BIT(I2S_TX_THRESHOLD)) &&
				rv_i2s_data->i2ssp_play_stream) अणु
		rv_ग_लिखोl(BIT(I2S_TX_THRESHOLD),
			rv_i2s_data->acp3x_base	+ mmACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rv_i2s_data->i2ssp_play_stream);
		play_flag = 1;
	पूर्ण

	अगर ((val & BIT(BT_RX_THRESHOLD)) && rv_i2s_data->capture_stream) अणु
		rv_ग_लिखोl(BIT(BT_RX_THRESHOLD), rv_i2s_data->acp3x_base +
			  mmACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rv_i2s_data->capture_stream);
		cap_flag = 1;
	पूर्ण
	अगर ((val & BIT(I2S_RX_THRESHOLD)) &&
				rv_i2s_data->i2ssp_capture_stream) अणु
		rv_ग_लिखोl(BIT(I2S_RX_THRESHOLD),
			 rv_i2s_data->acp3x_base + mmACP_EXTERNAL_INTR_STAT);
		snd_pcm_period_elapsed(rv_i2s_data->i2ssp_capture_stream);
		cap_flag = 1;
	पूर्ण

	अगर (play_flag | cap_flag)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम config_acp3x_dma(काष्ठा i2s_stream_instance *rtd, पूर्णांक direction)
अणु
	u16 page_idx;
	u32 low, high, val, acp_fअगरo_addr, reg_fअगरo_addr;
	u32 reg_dma_size, reg_fअगरo_size;
	dma_addr_t addr;

	addr = rtd->dma_addr;

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			val = ACP_SRAM_BT_PB_PTE_OFFSET;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			val = ACP_SRAM_SP_PB_PTE_OFFSET;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			val = ACP_SRAM_BT_CP_PTE_OFFSET;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			val = ACP_SRAM_SP_CP_PTE_OFFSET;
		पूर्ण
	पूर्ण
	/* Group Enable */
	rv_ग_लिखोl(ACP_SRAM_PTE_OFFSET | BIT(31), rtd->acp3x_base +
		  mmACPAXI2AXI_ATU_BASE_ADDR_GRP_1);
	rv_ग_लिखोl(PAGE_SIZE_4K_ENABLE, rtd->acp3x_base +
		  mmACPAXI2AXI_ATU_PAGE_SIZE_GRP_1);

	क्रम (page_idx = 0; page_idx < rtd->num_pages; page_idx++) अणु
		/* Load the low address of page पूर्णांक ACP SRAM through SRBM */
		low = lower_32_bits(addr);
		high = upper_32_bits(addr);

		rv_ग_लिखोl(low, rtd->acp3x_base + mmACP_SCRATCH_REG_0 + val);
		high |= BIT(31);
		rv_ग_लिखोl(high, rtd->acp3x_base + mmACP_SCRATCH_REG_0 + val
				+ 4);
		/* Move to next physically contiguos page */
		val += 8;
		addr += PAGE_SIZE;
	पूर्ण

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			reg_dma_size = mmACP_BT_TX_DMA_SIZE;
			acp_fअगरo_addr = ACP_SRAM_PTE_OFFSET +
						BT_PB_FIFO_ADDR_OFFSET;
			reg_fअगरo_addr = mmACP_BT_TX_FIFOADDR;
			reg_fअगरo_size = mmACP_BT_TX_FIFOSIZE;
			rv_ग_लिखोl(I2S_BT_TX_MEM_WINDOW_START,
				rtd->acp3x_base + mmACP_BT_TX_RINGBUFADDR);
			अवरोध;

		हाल I2S_SP_INSTANCE:
		शेष:
			reg_dma_size = mmACP_I2S_TX_DMA_SIZE;
			acp_fअगरo_addr = ACP_SRAM_PTE_OFFSET +
						SP_PB_FIFO_ADDR_OFFSET;
			reg_fअगरo_addr =	mmACP_I2S_TX_FIFOADDR;
			reg_fअगरo_size = mmACP_I2S_TX_FIFOSIZE;
			rv_ग_लिखोl(I2S_SP_TX_MEM_WINDOW_START,
				rtd->acp3x_base + mmACP_I2S_TX_RINGBUFADDR);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			reg_dma_size = mmACP_BT_RX_DMA_SIZE;
			acp_fअगरo_addr = ACP_SRAM_PTE_OFFSET +
						BT_CAPT_FIFO_ADDR_OFFSET;
			reg_fअगरo_addr = mmACP_BT_RX_FIFOADDR;
			reg_fअगरo_size = mmACP_BT_RX_FIFOSIZE;
			rv_ग_लिखोl(I2S_BT_RX_MEM_WINDOW_START,
				rtd->acp3x_base + mmACP_BT_RX_RINGBUFADDR);
			अवरोध;

		हाल I2S_SP_INSTANCE:
		शेष:
			reg_dma_size = mmACP_I2S_RX_DMA_SIZE;
			acp_fअगरo_addr = ACP_SRAM_PTE_OFFSET +
						SP_CAPT_FIFO_ADDR_OFFSET;
			reg_fअगरo_addr = mmACP_I2S_RX_FIFOADDR;
			reg_fअगरo_size = mmACP_I2S_RX_FIFOSIZE;
			rv_ग_लिखोl(I2S_SP_RX_MEM_WINDOW_START,
				rtd->acp3x_base + mmACP_I2S_RX_RINGBUFADDR);
		पूर्ण
	पूर्ण
	rv_ग_लिखोl(DMA_SIZE, rtd->acp3x_base + reg_dma_size);
	rv_ग_लिखोl(acp_fअगरo_addr, rtd->acp3x_base + reg_fअगरo_addr);
	rv_ग_लिखोl(FIFO_SIZE, rtd->acp3x_base + reg_fअगरo_size);
	rv_ग_लिखोl(BIT(I2S_RX_THRESHOLD) | BIT(BT_RX_THRESHOLD)
		| BIT(I2S_TX_THRESHOLD) | BIT(BT_TX_THRESHOLD),
		rtd->acp3x_base + mmACP_EXTERNAL_INTR_CNTL);
पूर्ण

अटल पूर्णांक acp3x_dma_खोलो(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_soc_pcm_runसमय *prtd;
	काष्ठा i2s_dev_data *adata;
	काष्ठा i2s_stream_instance *i2s_data;
	पूर्णांक ret;

	runसमय = substream->runसमय;
	prtd = asoc_substream_to_rtd(substream);
	component = snd_soc_rtdcom_lookup(prtd, DRV_NAME);
	adata = dev_get_drvdata(component->dev);
	i2s_data = kzalloc(माप(*i2s_data), GFP_KERNEL);
	अगर (!i2s_data)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		runसमय->hw = acp3x_pcm_hardware_playback;
	अन्यथा
		runसमय->hw = acp3x_pcm_hardware_capture;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		dev_err(component->dev, "set integer constraint failed\n");
		kमुक्त(i2s_data);
		वापस ret;
	पूर्ण

	i2s_data->acp3x_base = adata->acp3x_base;
	runसमय->निजी_data = i2s_data;
	वापस ret;
पूर्ण


अटल पूर्णांक acp3x_dma_hw_params(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा i2s_stream_instance *rtd;
	काष्ठा snd_soc_pcm_runसमय *prtd;
	काष्ठा snd_soc_card *card;
	काष्ठा acp3x_platक्रमm_info *pinfo;
	काष्ठा i2s_dev_data *adata;
	u64 size;

	prtd = asoc_substream_to_rtd(substream);
	card = prtd->card;
	pinfo = snd_soc_card_get_drvdata(card);
	adata = dev_get_drvdata(component->dev);
	rtd = substream->runसमय->निजी_data;
	अगर (!rtd)
		वापस -EINVAL;

	अगर (pinfo) अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			rtd->i2s_instance = pinfo->play_i2s_instance;
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				adata->play_stream = substream;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				adata->i2ssp_play_stream = substream;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtd->i2s_instance = pinfo->cap_i2s_instance;
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				adata->capture_stream = substream;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				adata->i2ssp_capture_stream = substream;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("pinfo failed\n");
	पूर्ण
	size = params_buffer_bytes(params);
	rtd->dma_addr = substream->dma_buffer.addr;
	rtd->num_pages = (PAGE_ALIGN(size) >> PAGE_SHIFT);
	config_acp3x_dma(rtd, substream->stream);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t acp3x_dma_poपूर्णांकer(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2s_stream_instance *rtd;
	u32 pos;
	u32 buffersize;
	u64 bytescount;

	rtd = substream->runसमय->निजी_data;

	buffersize = frames_to_bytes(substream->runसमय,
				     substream->runसमय->buffer_size);
	bytescount = acp_get_byte_count(rtd, substream->stream);
	अगर (bytescount > rtd->bytescount)
		bytescount -= rtd->bytescount;
	pos = करो_भाग(bytescount, buffersize);
	वापस bytes_to_frames(substream->runसमय, pos);
पूर्ण

अटल पूर्णांक acp3x_dma_new(काष्ठा snd_soc_component *component,
			 काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा device *parent = component->dev->parent;
	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_DEV,
				       parent, MIN_BUFFER, MAX_BUFFER);
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_dma_mmap(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस snd_pcm_lib_शेष_mmap(substream, vma);
पूर्ण

अटल पूर्णांक acp3x_dma_बंद(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *prtd;
	काष्ठा i2s_dev_data *adata;
	काष्ठा i2s_stream_instance *ins;

	prtd = asoc_substream_to_rtd(substream);
	component = snd_soc_rtdcom_lookup(prtd, DRV_NAME);
	adata = dev_get_drvdata(component->dev);
	ins = substream->runसमय->निजी_data;
	अगर (!ins)
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (ins->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			adata->play_stream = शून्य;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			adata->i2ssp_play_stream = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ins->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			adata->capture_stream = शून्य;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			adata->i2ssp_capture_stream = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver acp3x_i2s_component = अणु
	.name		= DRV_NAME,
	.खोलो		= acp3x_dma_खोलो,
	.बंद		= acp3x_dma_बंद,
	.hw_params	= acp3x_dma_hw_params,
	.poपूर्णांकer	= acp3x_dma_poपूर्णांकer,
	.mmap		= acp3x_dma_mmap,
	.pcm_स्थिरruct	= acp3x_dma_new,
पूर्ण;

अटल पूर्णांक acp3x_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा i2s_dev_data *adata;
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

	adata->acp3x_base = devm_ioremap(&pdev->dev, res->start,
					 resource_size(res));
	अगर (!adata->acp3x_base)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "IORESOURCE_IRQ FAILED\n");
		वापस -ENODEV;
	पूर्ण

	adata->i2s_irq = res->start;

	dev_set_drvdata(&pdev->dev, adata);
	status = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
						 &acp3x_i2s_component,
						 शून्य, 0);
	अगर (status) अणु
		dev_err(&pdev->dev, "Fail to register acp i2s component\n");
		वापस -ENODEV;
	पूर्ण
	status = devm_request_irq(&pdev->dev, adata->i2s_irq, i2s_irq_handler,
				  irqflags, "ACP3x_I2S_IRQ", adata);
	अगर (status) अणु
		dev_err(&pdev->dev, "ACP3x I2S IRQ request failed\n");
		वापस -ENODEV;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 2000);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2s_dev_data *adata;
	u32 val, reg_val, frmt_val;

	reg_val = 0;
	frmt_val = 0;
	adata = dev_get_drvdata(dev);

	अगर (adata->play_stream && adata->play_stream->runसमय) अणु
		काष्ठा i2s_stream_instance *rtd =
			adata->play_stream->runसमय->निजी_data;
		config_acp3x_dma(rtd, SNDRV_PCM_STREAM_PLAYBACK);
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			reg_val = mmACP_BTTDM_ITER;
			frmt_val = mmACP_BTTDM_TXFRMT;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			reg_val = mmACP_I2STDM_ITER;
			frmt_val = mmACP_I2STDM_TXFRMT;
		पूर्ण
		rv_ग_लिखोl((rtd->xfer_resolution  << 3),
			  rtd->acp3x_base + reg_val);
	पूर्ण
	अगर (adata->capture_stream && adata->capture_stream->runसमय) अणु
		काष्ठा i2s_stream_instance *rtd =
			adata->capture_stream->runसमय->निजी_data;
		config_acp3x_dma(rtd, SNDRV_PCM_STREAM_CAPTURE);
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			reg_val = mmACP_BTTDM_IRER;
			frmt_val = mmACP_BTTDM_RXFRMT;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			reg_val = mmACP_I2STDM_IRER;
			frmt_val = mmACP_I2STDM_RXFRMT;
		पूर्ण
		rv_ग_लिखोl((rtd->xfer_resolution  << 3),
			  rtd->acp3x_base + reg_val);
	पूर्ण
	अगर (adata->tdm_mode == TDM_ENABLE) अणु
		rv_ग_लिखोl(adata->tdm_fmt, adata->acp3x_base + frmt_val);
		val = rv_पढ़ोl(adata->acp3x_base + reg_val);
		rv_ग_लिखोl(val | 0x2, adata->acp3x_base + reg_val);
	पूर्ण
	rv_ग_लिखोl(1, adata->acp3x_base + mmACP_EXTERNAL_INTR_ENB);
	वापस 0;
पूर्ण


अटल पूर्णांक acp3x_pcm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2s_dev_data *adata;

	adata = dev_get_drvdata(dev);

	rv_ग_लिखोl(0, adata->acp3x_base + mmACP_EXTERNAL_INTR_ENB);

	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_pcm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2s_dev_data *adata;

	adata = dev_get_drvdata(dev);

	rv_ग_लिखोl(1, adata->acp3x_base + mmACP_EXTERNAL_INTR_ENB);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops acp3x_pm_ops = अणु
	.runसमय_suspend = acp3x_pcm_runसमय_suspend,
	.runसमय_resume = acp3x_pcm_runसमय_resume,
	.resume = acp3x_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver acp3x_dma_driver = अणु
	.probe = acp3x_audio_probe,
	.हटाओ = acp3x_audio_हटाओ,
	.driver = अणु
		.name = "acp3x_rv_i2s_dma",
		.pm = &acp3x_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(acp3x_dma_driver);

MODULE_AUTHOR("Vishnuvardhanrao.Ravulapati@amd.com");
MODULE_AUTHOR("Maruthi.Bayyavarapu@amd.com");
MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_DESCRIPTION("AMD ACP 3.x PCM Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:"DRV_NAME);
