<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext UniPhier AIO DMA driver.
//
// Copyright (c) 2016-2018 Socionext Inc.

#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश "aio.h"

अटल काष्ठा snd_pcm_hardware uniphier_aiodma_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED,
	.period_bytes_min = 256,
	.period_bytes_max = 4096,
	.periods_min      = 4,
	.periods_max      = 1024,
	.buffer_bytes_max = 128 * 1024,
पूर्ण;

अटल व्योम aiodma_pcm_irq(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = sub->substream->runसमय;
	पूर्णांक bytes = runसमय->period_size *
		runसमय->channels * samples_to_bytes(runसमय, 1);
	पूर्णांक ret;

	spin_lock(&sub->lock);
	ret = aiodma_rb_set_threshold(sub, runसमय->dma_bytes,
				      sub->threshold + bytes);
	अगर (!ret)
		sub->threshold += bytes;

	aiodma_rb_sync(sub, runसमय->dma_addr, runसमय->dma_bytes, bytes);
	aiodma_rb_clear_irq(sub);
	spin_unlock(&sub->lock);

	snd_pcm_period_elapsed(sub->substream);
पूर्ण

अटल व्योम aiodma_compr_irq(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा snd_compr_runसमय *runसमय = sub->cstream->runसमय;
	पूर्णांक bytes = runसमय->fragment_size;
	पूर्णांक ret;

	spin_lock(&sub->lock);
	ret = aiodma_rb_set_threshold(sub, sub->compr_bytes,
				      sub->threshold + bytes);
	अगर (!ret)
		sub->threshold += bytes;

	aiodma_rb_sync(sub, sub->compr_addr, sub->compr_bytes, bytes);
	aiodma_rb_clear_irq(sub);
	spin_unlock(&sub->lock);

	snd_compr_fragment_elapsed(sub->cstream);
पूर्ण

अटल irqवापस_t aiodma_irq(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा platक्रमm_device *pdev = p;
	काष्ठा uniphier_aio_chip *chip = platक्रमm_get_drvdata(pdev);
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक i, j;

	क्रम (i = 0; i < chip->num_aios; i++) अणु
		काष्ठा uniphier_aio *aio = &chip->aios[i];

		क्रम (j = 0; j < ARRAY_SIZE(aio->sub); j++) अणु
			काष्ठा uniphier_aio_sub *sub = &aio->sub[j];

			/* Skip channel that करोes not trigger */
			अगर (!sub->running || !aiodma_rb_is_irq(sub))
				जारी;

			अगर (sub->substream)
				aiodma_pcm_irq(sub);
			अगर (sub->cstream)
				aiodma_compr_irq(sub);

			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_aiodma_खोलो(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_soc_set_runसमय_hwparams(substream, &uniphier_aiodma_hw);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 256);
पूर्ण

अटल पूर्णांक uniphier_aiodma_prepare(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];
	पूर्णांक bytes = runसमय->period_size *
		runसमय->channels * samples_to_bytes(runसमय, 1);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = aiodma_ch_set_param(sub);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&sub->lock, flags);
	ret = aiodma_rb_set_buffer(sub, runसमय->dma_addr,
				   runसमय->dma_addr + runसमय->dma_bytes,
				   bytes);
	spin_unlock_irqrestore(&sub->lock, flags);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aiodma_trigger(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];
	काष्ठा device *dev = &aio->chip->pdev->dev;
	पूर्णांक bytes = runसमय->period_size *
		runसमय->channels * samples_to_bytes(runसमय, 1);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sub->lock, flags);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		aiodma_rb_sync(sub, runसमय->dma_addr, runसमय->dma_bytes,
			       bytes);
		aiodma_ch_set_enable(sub, 1);
		sub->running = 1;

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		sub->running = 0;
		aiodma_ch_set_enable(sub, 0);

		अवरोध;
	शेष:
		dev_warn(dev, "Unknown trigger(%d) ignored\n", cmd);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&sub->lock, flags);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t uniphier_aiodma_poपूर्णांकer(
					काष्ठा snd_soc_component *component,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[substream->stream];
	पूर्णांक bytes = runसमय->period_size *
		runसमय->channels * samples_to_bytes(runसमय, 1);
	अचिन्हित दीर्घ flags;
	snd_pcm_uframes_t pos;

	spin_lock_irqsave(&sub->lock, flags);
	aiodma_rb_sync(sub, runसमय->dma_addr, runसमय->dma_bytes, bytes);

	अगर (sub->swm->dir == PORT_सूची_OUTPUT)
		pos = bytes_to_frames(runसमय, sub->rd_offs);
	अन्यथा
		pos = bytes_to_frames(runसमय, sub->wr_offs);
	spin_unlock_irqrestore(&sub->lock, flags);

	वापस pos;
पूर्ण

अटल पूर्णांक uniphier_aiodma_mmap(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);

	वापस remap_pfn_range(vma, vma->vm_start,
			       substream->dma_buffer.addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start, vma->vm_page_prot);
पूर्ण

अटल पूर्णांक uniphier_aiodma_new(काष्ठा snd_soc_component *component,
			       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा device *dev = rtd->card->snd_card->dev;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(33));
	अगर (ret)
		वापस ret;

	snd_pcm_set_managed_buffer_all(pcm,
		SNDRV_DMA_TYPE_DEV, dev,
		uniphier_aiodma_hw.buffer_bytes_max,
		uniphier_aiodma_hw.buffer_bytes_max);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver uniphier_soc_platक्रमm = अणु
	.खोलो		= uniphier_aiodma_खोलो,
	.prepare	= uniphier_aiodma_prepare,
	.trigger	= uniphier_aiodma_trigger,
	.poपूर्णांकer	= uniphier_aiodma_poपूर्णांकer,
	.mmap		= uniphier_aiodma_mmap,
	.pcm_स्थिरruct	= uniphier_aiodma_new,
	.compress_ops	= &uniphier_aio_compress_ops,
पूर्ण;

अटल स्थिर काष्ठा regmap_config aiodma_regmap_config = अणु
	.reg_bits      = 32,
	.reg_stride    = 4,
	.val_bits      = 32,
	.max_रेजिस्टर  = 0x7fffc,
	.cache_type    = REGCACHE_NONE,
पूर्ण;

/**
 * uniphier_aiodma_soc_रेजिस्टर_platक्रमm - रेजिस्टर the AIO DMA
 * @pdev: the platक्रमm device
 *
 * Register and setup the DMA of AIO to transfer the sound data to device.
 * This function need to call once at driver startup and need NOT to call
 * unरेजिस्टर function.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक uniphier_aiodma_soc_रेजिस्टर_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_aio_chip *chip = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *preg;
	पूर्णांक irq, ret;

	preg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(preg))
		वापस PTR_ERR(preg);

	chip->regmap = devm_regmap_init_mmio(dev, preg,
					     &aiodma_regmap_config);
	अगर (IS_ERR(chip->regmap))
		वापस PTR_ERR(chip->regmap);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, aiodma_irq,
			       IRQF_SHARED, dev_name(dev), pdev);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &uniphier_soc_platक्रमm,
					       शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(uniphier_aiodma_soc_रेजिस्टर_platक्रमm);
