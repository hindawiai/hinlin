<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/sound/soc/pxa/mmp-pcm.c
 *
 * Copyright (C) 2011 Marvell International Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_data/dma-mmp_tdma.h>
#समावेश <linux/platक्रमm_data/mmp_audपन.स>

#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#घोषणा DRV_NAME "mmp-pcm"

काष्ठा mmp_dma_data अणु
	पूर्णांक ssp_id;
	काष्ठा resource *dma_res;
पूर्ण;

#घोषणा MMP_PCM_INFO (SNDRV_PCM_INFO_MMAP |	\
		SNDRV_PCM_INFO_MMAP_VALID |	\
		SNDRV_PCM_INFO_INTERLEAVED |	\
		SNDRV_PCM_INFO_PAUSE |		\
		SNDRV_PCM_INFO_RESUME |		\
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP)

अटल काष्ठा snd_pcm_hardware mmp_pcm_hardware[] = अणु
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

अटल पूर्णांक mmp_pcm_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा dma_chan *chan = snd_dmaengine_pcm_get_chan(substream);
	काष्ठा dma_slave_config slave_config;
	पूर्णांक ret;

	ret =
	    snd_dmaengine_pcm_prepare_slave_config(substream, params,
						   &slave_config);
	अगर (ret)
		वापस ret;

	ret = dmaengine_slave_config(chan, &slave_config);
	अगर (ret)
		वापस ret;

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_pcm_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	वापस snd_dmaengine_pcm_trigger(substream, cmd);
पूर्ण

अटल snd_pcm_uframes_t mmp_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_dmaengine_pcm_poपूर्णांकer(substream);
पूर्ण

अटल bool filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा mmp_dma_data *dma_data = param;
	bool found = false;
	अक्षर *devname;

	devname = kaप्र_लिखो(GFP_KERNEL, "%s.%d", dma_data->dma_res->name,
		dma_data->ssp_id);
	अगर ((म_भेद(dev_name(chan->device->dev), devname) == 0) &&
		(chan->chan_id == dma_data->dma_res->start)) अणु
		found = true;
	पूर्ण

	kमुक्त(devname);
	वापस found;
पूर्ण

अटल पूर्णांक mmp_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(component->dev);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा mmp_dma_data dma_data;
	काष्ठा resource *r;

	r = platक्रमm_get_resource(pdev, IORESOURCE_DMA, substream->stream);
	अगर (!r)
		वापस -EBUSY;

	snd_soc_set_runसमय_hwparams(substream,
				&mmp_pcm_hardware[substream->stream]);

	dma_data.dma_res = r;
	dma_data.ssp_id = cpu_dai->id;

	वापस snd_dmaengine_pcm_खोलो_request_chan(substream, filter,
		    &dma_data);
पूर्ण

अटल पूर्णांक mmp_pcm_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_dmaengine_pcm_बंद_release_chan(substream);
पूर्ण

अटल पूर्णांक mmp_pcm_mmap(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ off = vma->vm_pgoff;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	वापस remap_pfn_range(vma, vma->vm_start,
		__phys_to_pfn(runसमय->dma_addr) + off,
		vma->vm_end - vma->vm_start, vma->vm_page_prot);
पूर्ण

अटल व्योम mmp_pcm_मुक्त_dma_buffers(काष्ठा snd_soc_component *component,
				     काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_dma_buffer *buf;
	पूर्णांक stream;
	काष्ठा gen_pool *gpool;

	gpool = sram_get_gpool("asram");
	अगर (!gpool)
		वापस;

	क्रम (stream = 0; stream < 2; stream++) अणु
		माप_प्रकार size = mmp_pcm_hardware[stream].buffer_bytes_max;

		substream = pcm->streams[stream].substream;
		अगर (!substream)
			जारी;

		buf = &substream->dma_buffer;
		अगर (!buf->area)
			जारी;
		gen_pool_मुक्त(gpool, (अचिन्हित दीर्घ)buf->area, size);
		buf->area = शून्य;
	पूर्ण

पूर्ण

अटल पूर्णांक mmp_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm_substream *substream,
								पूर्णांक stream)
अणु
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;
	माप_प्रकार size = mmp_pcm_hardware[stream].buffer_bytes_max;
	काष्ठा gen_pool *gpool;

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = substream->pcm->card->dev;
	buf->निजी_data = शून्य;

	gpool = sram_get_gpool("asram");
	अगर (!gpool)
		वापस -ENOMEM;

	buf->area = gen_pool_dma_alloc(gpool, size, &buf->addr);
	अगर (!buf->area)
		वापस -ENOMEM;
	buf->bytes = size;
	वापस 0;
पूर्ण

अटल पूर्णांक mmp_pcm_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret, stream;

	क्रम (stream = 0; stream < 2; stream++) अणु
		substream = pcm->streams[stream].substream;

		ret = mmp_pcm_pपुनः_स्मृतिate_dma_buffer(substream,	stream);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	mmp_pcm_मुक्त_dma_buffers(component, pcm);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mmp_soc_component = अणु
	.name		= DRV_NAME,
	.खोलो		= mmp_pcm_खोलो,
	.बंद		= mmp_pcm_बंद,
	.hw_params	= mmp_pcm_hw_params,
	.trigger	= mmp_pcm_trigger,
	.poपूर्णांकer	= mmp_pcm_poपूर्णांकer,
	.mmap		= mmp_pcm_mmap,
	.pcm_स्थिरruct	= mmp_pcm_new,
	.pcm_deकाष्ठा	= mmp_pcm_मुक्त_dma_buffers,
पूर्ण;

अटल पूर्णांक mmp_pcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmp_audio_platdata *pdata = pdev->dev.platक्रमm_data;

	अगर (pdata) अणु
		mmp_pcm_hardware[SNDRV_PCM_STREAM_PLAYBACK].buffer_bytes_max =
						pdata->buffer_max_playback;
		mmp_pcm_hardware[SNDRV_PCM_STREAM_PLAYBACK].period_bytes_max =
						pdata->period_max_playback;
		mmp_pcm_hardware[SNDRV_PCM_STREAM_CAPTURE].buffer_bytes_max =
						pdata->buffer_max_capture;
		mmp_pcm_hardware[SNDRV_PCM_STREAM_CAPTURE].period_bytes_max =
						pdata->period_max_capture;
	पूर्ण
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &mmp_soc_component,
					       शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver mmp_pcm_driver = अणु
	.driver = अणु
		.name = "mmp-pcm-audio",
	पूर्ण,

	.probe = mmp_pcm_probe,
पूर्ण;

module_platक्रमm_driver(mmp_pcm_driver);

MODULE_AUTHOR("Leo Yan <leoy@marvell.com>");
MODULE_DESCRIPTION("MMP Soc Audio DMA module");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mmp-pcm-audio");
