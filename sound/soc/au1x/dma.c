<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au1000/Au1500/Au1100 Audio DMA support.
 *
 * (c) 2011 Manuel Lauss <manuel.lauss@googlemail.com>
 *
 * copied almost verbatim from the old ALSA driver, written by
 *			Charles Eidsness <अक्षरles@cooper-street.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1000_dma.h>

#समावेश "psc.h"

#घोषणा DRV_NAME "au1x_dma"

काष्ठा pcm_period अणु
	u32 start;
	u32 relative_end;	/* relative to start of buffer */
	काष्ठा pcm_period *next;
पूर्ण;

काष्ठा audio_stream अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक dma;
	काष्ठा pcm_period *buffer;
	अचिन्हित पूर्णांक period_size;
	अचिन्हित पूर्णांक periods;
पूर्ण;

काष्ठा alchemy_pcm_ctx अणु
	काष्ठा audio_stream stream[2];	/* playback & capture */
पूर्ण;

अटल व्योम au1000_release_dma_link(काष्ठा audio_stream *stream)
अणु
	काष्ठा pcm_period *poपूर्णांकer;
	काष्ठा pcm_period *poपूर्णांकer_next;

	stream->period_size = 0;
	stream->periods = 0;
	poपूर्णांकer = stream->buffer;
	अगर (!poपूर्णांकer)
		वापस;
	करो अणु
		poपूर्णांकer_next = poपूर्णांकer->next;
		kमुक्त(poपूर्णांकer);
		poपूर्णांकer = poपूर्णांकer_next;
	पूर्ण जबतक (poपूर्णांकer != stream->buffer);
	stream->buffer = शून्य;
पूर्ण

अटल पूर्णांक au1000_setup_dma_link(काष्ठा audio_stream *stream,
				 अचिन्हित पूर्णांक period_bytes,
				 अचिन्हित पूर्णांक periods)
अणु
	काष्ठा snd_pcm_substream *substream = stream->substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा pcm_period *poपूर्णांकer;
	अचिन्हित दीर्घ dma_start;
	पूर्णांक i;

	dma_start = virt_to_phys(runसमय->dma_area);

	अगर (stream->period_size == period_bytes &&
	    stream->periods == periods)
		वापस 0; /* not changed */

	au1000_release_dma_link(stream);

	stream->period_size = period_bytes;
	stream->periods = periods;

	stream->buffer = kदो_स्मृति(माप(काष्ठा pcm_period), GFP_KERNEL);
	अगर (!stream->buffer)
		वापस -ENOMEM;
	poपूर्णांकer = stream->buffer;
	क्रम (i = 0; i < periods; i++) अणु
		poपूर्णांकer->start = (u32)(dma_start + (i * period_bytes));
		poपूर्णांकer->relative_end = (u32) (((i+1) * period_bytes) - 0x1);
		अगर (i < periods - 1) अणु
			poपूर्णांकer->next = kदो_स्मृति(माप(काष्ठा pcm_period),
						GFP_KERNEL);
			अगर (!poपूर्णांकer->next) अणु
				au1000_release_dma_link(stream);
				वापस -ENOMEM;
			पूर्ण
			poपूर्णांकer = poपूर्णांकer->next;
		पूर्ण
	पूर्ण
	poपूर्णांकer->next = stream->buffer;
	वापस 0;
पूर्ण

अटल व्योम au1000_dma_stop(काष्ठा audio_stream *stream)
अणु
	अगर (stream->buffer)
		disable_dma(stream->dma);
पूर्ण

अटल व्योम au1000_dma_start(काष्ठा audio_stream *stream)
अणु
	अगर (!stream->buffer)
		वापस;

	init_dma(stream->dma);
	अगर (get_dma_active_buffer(stream->dma) == 0) अणु
		clear_dma_करोne0(stream->dma);
		set_dma_addr0(stream->dma, stream->buffer->start);
		set_dma_count0(stream->dma, stream->period_size >> 1);
		set_dma_addr1(stream->dma, stream->buffer->next->start);
		set_dma_count1(stream->dma, stream->period_size >> 1);
	पूर्ण अन्यथा अणु
		clear_dma_करोne1(stream->dma);
		set_dma_addr1(stream->dma, stream->buffer->start);
		set_dma_count1(stream->dma, stream->period_size >> 1);
		set_dma_addr0(stream->dma, stream->buffer->next->start);
		set_dma_count0(stream->dma, stream->period_size >> 1);
	पूर्ण
	enable_dma_buffers(stream->dma);
	start_dma(stream->dma);
पूर्ण

अटल irqवापस_t au1000_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा audio_stream *stream = (काष्ठा audio_stream *)ptr;
	काष्ठा snd_pcm_substream *substream = stream->substream;

	चयन (get_dma_buffer_करोne(stream->dma)) अणु
	हाल DMA_D0:
		stream->buffer = stream->buffer->next;
		clear_dma_करोne0(stream->dma);
		set_dma_addr0(stream->dma, stream->buffer->next->start);
		set_dma_count0(stream->dma, stream->period_size >> 1);
		enable_dma_buffer0(stream->dma);
		अवरोध;
	हाल DMA_D1:
		stream->buffer = stream->buffer->next;
		clear_dma_करोne1(stream->dma);
		set_dma_addr1(stream->dma, stream->buffer->next->start);
		set_dma_count1(stream->dma, stream->period_size >> 1);
		enable_dma_buffer1(stream->dma);
		अवरोध;
	हाल (DMA_D0 | DMA_D1):
		pr_debug("DMA %d missed interrupt.\n", stream->dma);
		au1000_dma_stop(stream);
		au1000_dma_start(stream);
		अवरोध;
	हाल (~DMA_D0 & ~DMA_D1):
		pr_debug("DMA %d empty irq.\n", stream->dma);
	पूर्ण
	snd_pcm_period_elapsed(substream);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware alchemy_pcm_hardware = अणु
	.info		  = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
			    SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BATCH,
	.period_bytes_min = 1024,
	.period_bytes_max = 16 * 1024 - 1,
	.periods_min	  = 4,
	.periods_max	  = 255,
	.buffer_bytes_max = 128 * 1024,
	.fअगरo_size	  = 16,
पूर्ण;

अटल अंतरभूत काष्ठा alchemy_pcm_ctx *ss_to_ctx(काष्ठा snd_pcm_substream *ss,
						काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_get_drvdata(component);
पूर्ण

अटल अंतरभूत काष्ठा audio_stream *ss_to_as(काष्ठा snd_pcm_substream *ss,
					    काष्ठा snd_soc_component *component)
अणु
	काष्ठा alchemy_pcm_ctx *ctx = ss_to_ctx(ss, component);
	वापस &(ctx->stream[ss->stream]);
पूर्ण

अटल पूर्णांक alchemy_pcm_खोलो(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा alchemy_pcm_ctx *ctx = ss_to_ctx(substream, component);
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक *dmaids, s = substream->stream;
	अक्षर *name;

	dmaids = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	अगर (!dmaids)
		वापस -ENODEV;	/* whoa, has ordering changed? */

	/* DMA setup */
	name = (s == SNDRV_PCM_STREAM_PLAYBACK) ? "audio-tx" : "audio-rx";
	ctx->stream[s].dma = request_au1000_dma(dmaids[s], name,
					au1000_dma_पूर्णांकerrupt, 0,
					&ctx->stream[s]);
	set_dma_mode(ctx->stream[s].dma,
		     get_dma_mode(ctx->stream[s].dma) & ~DMA_NC);

	ctx->stream[s].substream = substream;
	ctx->stream[s].buffer = शून्य;
	snd_soc_set_runसमय_hwparams(substream, &alchemy_pcm_hardware);

	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_pcm_बंद(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा alchemy_pcm_ctx *ctx = ss_to_ctx(substream, component);
	पूर्णांक stype = substream->stream;

	ctx->stream[stype].substream = शून्य;
	मुक्त_au1000_dma(ctx->stream[stype].dma);

	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_pcm_hw_params(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा audio_stream *stream = ss_to_as(substream, component);

	वापस au1000_setup_dma_link(stream,
				     params_period_bytes(hw_params),
				     params_periods(hw_params));
पूर्ण

अटल पूर्णांक alchemy_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा audio_stream *stream = ss_to_as(substream, component);
	au1000_release_dma_link(stream);
	वापस 0;
पूर्ण

अटल पूर्णांक alchemy_pcm_trigger(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा audio_stream *stream = ss_to_as(substream, component);
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		au1000_dma_start(stream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		au1000_dma_stop(stream);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल snd_pcm_uframes_t alchemy_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					     काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा audio_stream *stream = ss_to_as(ss, component);
	दीर्घ location;

	location = get_dma_residue(stream->dma);
	location = stream->buffer->relative_end - location;
	अगर (location == -1)
		location = 0;
	वापस bytes_to_frames(ss->runसमय, location);
पूर्ण

अटल पूर्णांक alchemy_pcm_new(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm *pcm = rtd->pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 65536, (4096 * 1024) - 1);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_component_driver alchemy_pcm_soc_component = अणु
	.name		= DRV_NAME,
	.खोलो		= alchemy_pcm_खोलो,
	.बंद		= alchemy_pcm_बंद,
	.hw_params	= alchemy_pcm_hw_params,
	.hw_मुक्त	= alchemy_pcm_hw_मुक्त,
	.trigger	= alchemy_pcm_trigger,
	.poपूर्णांकer	= alchemy_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= alchemy_pcm_new,
पूर्ण;

अटल पूर्णांक alchemy_pcm_drvprobe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा alchemy_pcm_ctx *ctx;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ctx);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					&alchemy_pcm_soc_component, शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver alchemy_pcmdma_driver = अणु
	.driver	= अणु
		.name	= "alchemy-pcm-dma",
	पूर्ण,
	.probe		= alchemy_pcm_drvprobe,
पूर्ण;

module_platक्रमm_driver(alchemy_pcmdma_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Au1000/Au1500/Au1100 Audio DMA driver");
MODULE_AUTHOR("Manuel Lauss");
