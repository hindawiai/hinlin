<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// SH7760 ("camelot") DMABRG audio DMA unit support
//
// Copyright (C) 2007 Manuel Lauss <mano@roarinelk.homelinux.net>
//
// The SH7760 DMABRG provides 4 dma channels (2x rec, 2x play), which
// trigger an पूर्णांकerrupt when one half of the programmed transfer size
// has been xmitted.
//
// FIXME: little-endian only क्रम now

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/dmabrg.h>


/* रेजिस्टरs and bits */
#घोषणा BRGATXSAR	0x00
#घोषणा BRGARXDAR	0x04
#घोषणा BRGATXTCR	0x08
#घोषणा BRGARXTCR	0x0C
#घोषणा BRGACR		0x10
#घोषणा BRGATXTCNT	0x14
#घोषणा BRGARXTCNT	0x18

#घोषणा ACR_RAR		(1 << 18)
#घोषणा ACR_RDS		(1 << 17)
#घोषणा ACR_RDE		(1 << 16)
#घोषणा ACR_TAR		(1 << 2)
#घोषणा ACR_TDS		(1 << 1)
#घोषणा ACR_TDE		(1 << 0)

/* receiver/transmitter data alignment */
#घोषणा ACR_RAM_NONE	(0 << 24)
#घोषणा ACR_RAM_4BYTE	(1 << 24)
#घोषणा ACR_RAM_2WORD	(2 << 24)
#घोषणा ACR_TAM_NONE	(0 << 8)
#घोषणा ACR_TAM_4BYTE	(1 << 8)
#घोषणा ACR_TAM_2WORD	(2 << 8)


काष्ठा camelot_pcm अणु
	अचिन्हित दीर्घ mmio;  /* DMABRG audio channel control reg MMIO */
	अचिन्हित पूर्णांक txid;    /* ID of first DMABRG IRQ क्रम this unit */

	काष्ठा snd_pcm_substream *tx_ss;
	अचिन्हित दीर्घ tx_period_size;
	अचिन्हित पूर्णांक  tx_period;

	काष्ठा snd_pcm_substream *rx_ss;
	अचिन्हित दीर्घ rx_period_size;
	अचिन्हित पूर्णांक  rx_period;

पूर्ण cam_pcm_data[2] = अणु
	अणु
		.mmio	=	0xFE3C0040,
		.txid	=	DMABRGIRQ_A0TXF,
	पूर्ण,
	अणु
		.mmio	=	0xFE3C0060,
		.txid	=	DMABRGIRQ_A1TXF,
	पूर्ण,
पूर्ण;

#घोषणा BRGREG(x)	(*(अचिन्हित दीर्घ *)(cam->mmio + (x)))

/*
 * set a minimum of 16kb per period, to aव्योम पूर्णांकerrupt-"storm" and
 * resulting skipping. In general, the bigger the minimum size, the
 * better क्रम overall प्रणाली perक्रमmance. (The SH7760 is a puny CPU
 * with a slow SDRAM पूर्णांकerface and poor पूर्णांकernal bus bandwidth,
 * *especially* when the LCDC is active).  The minimum क्रम the DMAC
 * is 8 bytes; 16kbytes are enough to get skip-मुक्त playback of a
 * 44kHz/16bit/stereo MP3 on a lightly loaded प्रणाली, and मुख्यtain
 * reasonable responsiveness in MPlayer.
 */
#घोषणा DMABRG_PERIOD_MIN		16 * 1024
#घोषणा DMABRG_PERIOD_MAX		0x03fffffc
#घोषणा DMABRG_PREALLOC_BUFFER		32 * 1024
#घोषणा DMABRG_PREALLOC_BUFFER_MAX	32 * 1024

अटल स्थिर काष्ठा snd_pcm_hardware camelot_pcm_hardware = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH),
	.buffer_bytes_max =	DMABRG_PERIOD_MAX,
	.period_bytes_min =	DMABRG_PERIOD_MIN,
	.period_bytes_max =	DMABRG_PERIOD_MAX / 2,
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		128,
पूर्ण;

अटल व्योम camelot_txdma(व्योम *data)
अणु
	काष्ठा camelot_pcm *cam = data;
	cam->tx_period ^= 1;
	snd_pcm_period_elapsed(cam->tx_ss);
पूर्ण

अटल व्योम camelot_rxdma(व्योम *data)
अणु
	काष्ठा camelot_pcm *cam = data;
	cam->rx_period ^= 1;
	snd_pcm_period_elapsed(cam->rx_ss);
पूर्ण

अटल पूर्णांक camelot_pcm_खोलो(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा camelot_pcm *cam = &cam_pcm_data[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक recv = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? 0:1;
	पूर्णांक ret, dmairq;

	snd_soc_set_runसमय_hwparams(substream, &camelot_pcm_hardware);

	/* DMABRG buffer half/full events */
	dmairq = (recv) ? cam->txid + 2 : cam->txid;
	अगर (recv) अणु
		cam->rx_ss = substream;
		ret = dmabrg_request_irq(dmairq, camelot_rxdma, cam);
		अगर (unlikely(ret)) अणु
			pr_debug("audio unit %d irqs already taken!\n",
			     asoc_rtd_to_cpu(rtd, 0)->id);
			वापस -EBUSY;
		पूर्ण
		(व्योम)dmabrg_request_irq(dmairq + 1,camelot_rxdma, cam);
	पूर्ण अन्यथा अणु
		cam->tx_ss = substream;
		ret = dmabrg_request_irq(dmairq, camelot_txdma, cam);
		अगर (unlikely(ret)) अणु
			pr_debug("audio unit %d irqs already taken!\n",
			     asoc_rtd_to_cpu(rtd, 0)->id);
			वापस -EBUSY;
		पूर्ण
		(व्योम)dmabrg_request_irq(dmairq + 1, camelot_txdma, cam);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक camelot_pcm_बंद(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा camelot_pcm *cam = &cam_pcm_data[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक recv = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? 0:1;
	पूर्णांक dmairq;

	dmairq = (recv) ? cam->txid + 2 : cam->txid;

	अगर (recv)
		cam->rx_ss = शून्य;
	अन्यथा
		cam->tx_ss = शून्य;

	dmabrg_मुक्त_irq(dmairq + 1);
	dmabrg_मुक्त_irq(dmairq);

	वापस 0;
पूर्ण

अटल पूर्णांक camelot_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा camelot_pcm *cam = &cam_pcm_data[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक recv = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? 0:1;

	अगर (recv) अणु
		cam->rx_period_size = params_period_bytes(hw_params);
		cam->rx_period = 0;
	पूर्ण अन्यथा अणु
		cam->tx_period_size = params_period_bytes(hw_params);
		cam->tx_period = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक camelot_prepare(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा camelot_pcm *cam = &cam_pcm_data[asoc_rtd_to_cpu(rtd, 0)->id];

	pr_debug("PCM data: addr 0x%08lx len %d\n",
		 (u32)runसमय->dma_addr, runसमय->dma_bytes);
 
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		BRGREG(BRGATXSAR) = (अचिन्हित दीर्घ)runसमय->dma_area;
		BRGREG(BRGATXTCR) = runसमय->dma_bytes;
	पूर्ण अन्यथा अणु
		BRGREG(BRGARXDAR) = (अचिन्हित दीर्घ)runसमय->dma_area;
		BRGREG(BRGARXTCR) = runसमय->dma_bytes;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dmabrg_play_dma_start(काष्ठा camelot_pcm *cam)
अणु
	अचिन्हित दीर्घ acr = BRGREG(BRGACR) & ~(ACR_TDS | ACR_RDS);
	/* start DMABRG engine: XFER start, स्वतः-addr-reload */
	BRGREG(BRGACR) = acr | ACR_TDE | ACR_TAR | ACR_TAM_2WORD;
पूर्ण

अटल अंतरभूत व्योम dmabrg_play_dma_stop(काष्ठा camelot_pcm *cam)
अणु
	अचिन्हित दीर्घ acr = BRGREG(BRGACR) & ~(ACR_TDS | ACR_RDS);
	/* क्रमcibly terminate data transmission */
	BRGREG(BRGACR) = acr | ACR_TDS;
पूर्ण

अटल अंतरभूत व्योम dmabrg_rec_dma_start(काष्ठा camelot_pcm *cam)
अणु
	अचिन्हित दीर्घ acr = BRGREG(BRGACR) & ~(ACR_TDS | ACR_RDS);
	/* start DMABRG engine: recv start, स्वतः-reload */
	BRGREG(BRGACR) = acr | ACR_RDE | ACR_RAR | ACR_RAM_2WORD;
पूर्ण

अटल अंतरभूत व्योम dmabrg_rec_dma_stop(काष्ठा camelot_pcm *cam)
अणु
	अचिन्हित दीर्घ acr = BRGREG(BRGACR) & ~(ACR_TDS | ACR_RDS);
	/* क्रमcibly terminate data receiver */
	BRGREG(BRGACR) = acr | ACR_RDS;
पूर्ण

अटल पूर्णांक camelot_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा camelot_pcm *cam = &cam_pcm_data[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक recv = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? 0:1;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (recv)
			dmabrg_rec_dma_start(cam);
		अन्यथा
			dmabrg_play_dma_start(cam);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (recv)
			dmabrg_rec_dma_stop(cam);
		अन्यथा
			dmabrg_play_dma_stop(cam);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t camelot_pos(काष्ठा snd_soc_component *component,
				     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा camelot_pcm *cam = &cam_pcm_data[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक recv = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? 0:1;
	अचिन्हित दीर्घ pos;

	/* cannot use the DMABRG poपूर्णांकer रेजिस्टर: under load, by the
	 * समय ALSA comes around to पढ़ो the रेजिस्टर, it is alपढ़ोy
	 * far ahead (or worse, alपढ़ोy करोne with the fragment) of the
	 * position at the समय the IRQ was triggered, which results in
	 * fast-playback sound in my test application (ScummVM)
	 */
	अगर (recv)
		pos = cam->rx_period ? cam->rx_period_size : 0;
	अन्यथा
		pos = cam->tx_period ? cam->tx_period_size : 0;

	वापस bytes_to_frames(runसमय, pos);
पूर्ण

अटल पूर्णांक camelot_pcm_new(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm *pcm = rtd->pcm;

	/* करोnt use SNDRV_DMA_TYPE_DEV, since it will oops the SH kernel
	 * in MMAP mode (i.e. aplay -M)
	 */
	snd_pcm_set_managed_buffer_all(pcm,
		SNDRV_DMA_TYPE_CONTINUOUS,
		शून्य,
		DMABRG_PREALLOC_BUFFER,	DMABRG_PREALLOC_BUFFER_MAX);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sh7760_soc_component = अणु
	.खोलो		= camelot_pcm_खोलो,
	.बंद		= camelot_pcm_बंद,
	.hw_params	= camelot_hw_params,
	.prepare	= camelot_prepare,
	.trigger	= camelot_trigger,
	.poपूर्णांकer	= camelot_pos,
	.pcm_स्थिरruct	= camelot_pcm_new,
पूर्ण;

अटल पूर्णांक sh7760_soc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sh7760_soc_component,
					       शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver sh7760_pcm_driver = अणु
	.driver = अणु
			.name = "sh7760-pcm-audio",
	पूर्ण,

	.probe = sh7760_soc_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(sh7760_pcm_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SH7760 Audio DMA (DMABRG) driver");
MODULE_AUTHOR("Manuel Lauss <mano@roarinelk.homelinux.net>");
