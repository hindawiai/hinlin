<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au12x0/Au1550 PSC ALSA ASoC audio support.
 *
 * (c) 2007-2008 MSC Vertriebsges.m.b.H.,
 *	Manuel Lauss <manuel.lauss@gmail.com>
 *
 * DMA glue क्रम Au1x-PSC audio.
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
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>

#समावेश "psc.h"

/*#घोषणा PCM_DEBUG*/

#घोषणा DRV_NAME "dbdma2"

#घोषणा MSG(x...)	prपूर्णांकk(KERN_INFO "au1xpsc_pcm: " x)
#अगर_घोषित PCM_DEBUG
#घोषणा DBG		MSG
#अन्यथा
#घोषणा DBG(x...)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा au1xpsc_audio_dmadata अणु
	/* DDMA control data */
	अचिन्हित पूर्णांक ddma_id;		/* DDMA direction ID क्रम this PSC */
	u32 ddma_chan;			/* DDMA context */

	/* PCM context (क्रम irq handlers) */
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित दीर्घ curr_period;	/* current segment DDMA is working on */
	अचिन्हित दीर्घ q_period;		/* queue period(s) */
	dma_addr_t dma_area;		/* address of queued DMA area */
	dma_addr_t dma_area_s;		/* start address of DMA area */
	अचिन्हित दीर्घ pos;		/* current byte position being played */
	अचिन्हित दीर्घ periods;		/* number of SG segments in total */
	अचिन्हित दीर्घ period_bytes;	/* size in bytes of one SG segment */

	/* runसमय data */
	पूर्णांक msbits;
पूर्ण;

/*
 * These settings are somewhat okay, at least on my machine audio plays
 * almost skip-मुक्त. Especially the 64kB buffer seems to help a LOT.
 */
#घोषणा AU1XPSC_PERIOD_MIN_BYTES	1024
#घोषणा AU1XPSC_BUFFER_MIN_BYTES	65536

/* PCM hardware DMA capabilities - platक्रमm specअगरic */
अटल स्थिर काष्ठा snd_pcm_hardware au1xpsc_pcm_hardware = अणु
	.info		  = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
			    SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BATCH,
	.period_bytes_min = AU1XPSC_PERIOD_MIN_BYTES,
	.period_bytes_max = 4096 * 1024 - 1,
	.periods_min	  = 2,
	.periods_max	  = 4096,	/* 2 to as-much-as-you-like */
	.buffer_bytes_max = 4096 * 1024 - 1,
	.fअगरo_size	  = 16,		/* fअगरo entries of AC97/I2S PSC */
पूर्ण;

अटल व्योम au1x_pcm_queue_tx(काष्ठा au1xpsc_audio_dmadata *cd)
अणु
	au1xxx_dbdma_put_source(cd->ddma_chan, cd->dma_area,
				cd->period_bytes, DDMA_FLAGS_IE);

	/* update next-to-queue period */
	++cd->q_period;
	cd->dma_area += cd->period_bytes;
	अगर (cd->q_period >= cd->periods) अणु
		cd->q_period = 0;
		cd->dma_area = cd->dma_area_s;
	पूर्ण
पूर्ण

अटल व्योम au1x_pcm_queue_rx(काष्ठा au1xpsc_audio_dmadata *cd)
अणु
	au1xxx_dbdma_put_dest(cd->ddma_chan, cd->dma_area,
			      cd->period_bytes, DDMA_FLAGS_IE);

	/* update next-to-queue period */
	++cd->q_period;
	cd->dma_area += cd->period_bytes;
	अगर (cd->q_period >= cd->periods) अणु
		cd->q_period = 0;
		cd->dma_area = cd->dma_area_s;
	पूर्ण
पूर्ण

अटल व्योम au1x_pcm_dmatx_cb(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा au1xpsc_audio_dmadata *cd = dev_id;

	cd->pos += cd->period_bytes;
	अगर (++cd->curr_period >= cd->periods) अणु
		cd->pos = 0;
		cd->curr_period = 0;
	पूर्ण
	snd_pcm_period_elapsed(cd->substream);
	au1x_pcm_queue_tx(cd);
पूर्ण

अटल व्योम au1x_pcm_dmarx_cb(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा au1xpsc_audio_dmadata *cd = dev_id;

	cd->pos += cd->period_bytes;
	अगर (++cd->curr_period >= cd->periods) अणु
		cd->pos = 0;
		cd->curr_period = 0;
	पूर्ण
	snd_pcm_period_elapsed(cd->substream);
	au1x_pcm_queue_rx(cd);
पूर्ण

अटल व्योम au1x_pcm_dbdma_मुक्त(काष्ठा au1xpsc_audio_dmadata *pcd)
अणु
	अगर (pcd->ddma_chan) अणु
		au1xxx_dbdma_stop(pcd->ddma_chan);
		au1xxx_dbdma_reset(pcd->ddma_chan);
		au1xxx_dbdma_chan_मुक्त(pcd->ddma_chan);
		pcd->ddma_chan = 0;
		pcd->msbits = 0;
	पूर्ण
पूर्ण

/* in हाल of missing DMA ring or changed TX-source / RX-dest bit widths,
 * allocate (or पुनः_स्मृतिate) a 2-descriptor DMA ring with bit depth according
 * to ALSA-supplied sample depth.  This is due to limitations in the dbdma api
 * (cannot adjust source/dest widths of alपढ़ोy allocated descriptor ring).
 */
अटल पूर्णांक au1x_pcm_dbdma_पुनः_स्मृति(काष्ठा au1xpsc_audio_dmadata *pcd,
				 पूर्णांक stype, पूर्णांक msbits)
अणु
	/* DMA only in 8/16/32 bit widths */
	अगर (msbits == 24)
		msbits = 32;

	/* check current config: correct bits and descriptors allocated? */
	अगर ((pcd->ddma_chan) && (msbits == pcd->msbits))
		जाओ out;	/* all ok! */

	au1x_pcm_dbdma_मुक्त(pcd);

	अगर (stype == SNDRV_PCM_STREAM_CAPTURE)
		pcd->ddma_chan = au1xxx_dbdma_chan_alloc(pcd->ddma_id,
					DSCR_CMD0_ALWAYS,
					au1x_pcm_dmarx_cb, (व्योम *)pcd);
	अन्यथा
		pcd->ddma_chan = au1xxx_dbdma_chan_alloc(DSCR_CMD0_ALWAYS,
					pcd->ddma_id,
					au1x_pcm_dmatx_cb, (व्योम *)pcd);

	अगर (!pcd->ddma_chan)
		वापस -ENOMEM;

	au1xxx_dbdma_set_devwidth(pcd->ddma_chan, msbits);
	au1xxx_dbdma_ring_alloc(pcd->ddma_chan, 2);

	pcd->msbits = msbits;

	au1xxx_dbdma_stop(pcd->ddma_chan);
	au1xxx_dbdma_reset(pcd->ddma_chan);

out:
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा au1xpsc_audio_dmadata *to_dmadata(काष्ठा snd_pcm_substream *ss,
						       काष्ठा snd_soc_component *component)
अणु
	काष्ठा au1xpsc_audio_dmadata *pcd = snd_soc_component_get_drvdata(component);
	वापस &pcd[ss->stream];
पूर्ण

अटल पूर्णांक au1xpsc_pcm_hw_params(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा au1xpsc_audio_dmadata *pcd;
	पूर्णांक stype, ret;

	stype = substream->stream;
	pcd = to_dmadata(substream, component);

	DBG("runtime->dma_area = 0x%08lx dma_addr_t = 0x%08lx dma_size = %zu "
	    "runtime->min_align %lu\n",
		(अचिन्हित दीर्घ)runसमय->dma_area,
		(अचिन्हित दीर्घ)runसमय->dma_addr, runसमय->dma_bytes,
		runसमय->min_align);

	DBG("bits %d  frags %d  frag_bytes %d  is_rx %d\n", params->msbits,
		params_periods(params), params_period_bytes(params), stype);

	ret = au1x_pcm_dbdma_पुनः_स्मृति(pcd, stype, params->msbits);
	अगर (ret) अणु
		MSG("DDMA channel (re)alloc failed!\n");
		जाओ out;
	पूर्ण

	pcd->substream = substream;
	pcd->period_bytes = params_period_bytes(params);
	pcd->periods = params_periods(params);
	pcd->dma_area_s = pcd->dma_area = runसमय->dma_addr;
	pcd->q_period = 0;
	pcd->curr_period = 0;
	pcd->pos = 0;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक au1xpsc_pcm_prepare(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा au1xpsc_audio_dmadata *pcd = to_dmadata(substream, component);

	au1xxx_dbdma_reset(pcd->ddma_chan);

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		au1x_pcm_queue_rx(pcd);
		au1x_pcm_queue_rx(pcd);
	पूर्ण अन्यथा अणु
		au1x_pcm_queue_tx(pcd);
		au1x_pcm_queue_tx(pcd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_pcm_trigger(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	u32 c = to_dmadata(substream, component)->ddma_chan;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		au1xxx_dbdma_start(c);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		au1xxx_dbdma_stop(c);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
au1xpsc_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *substream)
अणु
	वापस bytes_to_frames(substream->runसमय,
			       to_dmadata(substream, component)->pos);
पूर्ण

अटल पूर्णांक au1xpsc_pcm_खोलो(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा au1xpsc_audio_dmadata *pcd = to_dmadata(substream, component);
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक stype = substream->stream, *dmaids;

	dmaids = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	अगर (!dmaids)
		वापस -ENODEV;	/* whoa, has ordering changed? */

	pcd->ddma_id = dmaids[stype];

	snd_soc_set_runसमय_hwparams(substream, &au1xpsc_pcm_hardware);
	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_pcm_बंद(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	au1x_pcm_dbdma_मुक्त(to_dmadata(substream, component));
	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_pcm_new(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
		card->dev, AU1XPSC_BUFFER_MIN_BYTES, (4096 * 1024) - 1);

	वापस 0;
पूर्ण

/* au1xpsc audio platक्रमm */
अटल काष्ठा snd_soc_component_driver au1xpsc_soc_component = अणु
	.name		= DRV_NAME,
	.खोलो		= au1xpsc_pcm_खोलो,
	.बंद		= au1xpsc_pcm_बंद,
	.hw_params	= au1xpsc_pcm_hw_params,
	.prepare	= au1xpsc_pcm_prepare,
	.trigger	= au1xpsc_pcm_trigger,
	.poपूर्णांकer	= au1xpsc_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= au1xpsc_pcm_new,
पूर्ण;

अटल पूर्णांक au1xpsc_pcm_drvprobe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xpsc_audio_dmadata *dmadata;

	dmadata = devm_kसुस्मृति(&pdev->dev,
			       2, माप(काष्ठा au1xpsc_audio_dmadata),
			       GFP_KERNEL);
	अगर (!dmadata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dmadata);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					&au1xpsc_soc_component, शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver au1xpsc_pcm_driver = अणु
	.driver	= अणु
		.name	= "au1xpsc-pcm",
	पूर्ण,
	.probe		= au1xpsc_pcm_drvprobe,
पूर्ण;

module_platक्रमm_driver(au1xpsc_pcm_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Au12x0/Au1550 PSC Audio DMA driver");
MODULE_AUTHOR("Manuel Lauss");
