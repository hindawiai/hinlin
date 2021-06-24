<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Freescale MPC5200 Audio DMA driver
 */

#अगर_अघोषित __SOUND_SOC_FSL_MPC5200_DMA_H__
#घोषणा __SOUND_SOC_FSL_MPC5200_DMA_H__

#घोषणा PSC_STREAM_NAME_LEN 32

/**
 * psc_ac97_stream - Data specअगरic to a single stream (playback or capture)
 * @active:		flag indicating अगर the stream is active
 * @psc_dma:		poपूर्णांकer back to parent psc_dma data काष्ठाure
 * @bcom_task:		bestcomm task काष्ठाure
 * @irq:		irq number क्रम bestcomm task
 * @period_end:		physical address of end of DMA region
 * @period_next_pt:	physical address of next DMA buffer to enqueue
 * @period_bytes:	size of DMA period in bytes
 * @ac97_slot_bits:	Enable bits क्रम turning on the correct AC97 slot
 */
काष्ठा psc_dma_stream अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक active;
	काष्ठा psc_dma *psc_dma;
	काष्ठा bcom_task *bcom_task;
	पूर्णांक irq;
	काष्ठा snd_pcm_substream *stream;
	पूर्णांक period_next;
	पूर्णांक period_current;
	पूर्णांक period_bytes;
	पूर्णांक period_count;

	/* AC97 state */
	u32 ac97_slot_bits;
पूर्ण;

/**
 * psc_dma - Private driver data
 * @name: लघु name क्रम this device ("PSC0", "PSC1", etc)
 * @psc_regs: poपूर्णांकer to the PSC's रेजिस्टरs
 * @fअगरo_regs: poपूर्णांकer to the PSC's FIFO रेजिस्टरs
 * @irq: IRQ of this PSC
 * @dev: काष्ठा device poपूर्णांकer
 * @dai: the CPU DAI क्रम this device
 * @sicr: Base value used in serial पूर्णांकerface control रेजिस्टर; mode is ORed
 *        with this value.
 * @playback: Playback stream context data
 * @capture: Capture stream context data
 */
काष्ठा psc_dma अणु
	अक्षर name[32];
	काष्ठा mpc52xx_psc __iomem *psc_regs;
	काष्ठा mpc52xx_psc_fअगरo __iomem *fअगरo_regs;
	अचिन्हित पूर्णांक irq;
	काष्ठा device *dev;
	spinlock_t lock;
	काष्ठा mutex mutex;
	u32 sicr;
	uपूर्णांक sysclk;
	पूर्णांक imr;
	पूर्णांक id;
	अचिन्हित पूर्णांक slots;

	/* per-stream data */
	काष्ठा psc_dma_stream playback;
	काष्ठा psc_dma_stream capture;

	/* Statistics */
	काष्ठा अणु
		अचिन्हित दीर्घ overrun_count;
		अचिन्हित दीर्घ underrun_count;
	पूर्ण stats;
पूर्ण;

/* Utility क्रम retrieving psc_dma_stream काष्ठाure from a substream */
अटल अंतरभूत काष्ठा psc_dma_stream *
to_psc_dma_stream(काष्ठा snd_pcm_substream *substream, काष्ठा psc_dma *psc_dma)
अणु
	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस &psc_dma->capture;
	वापस &psc_dma->playback;
पूर्ण

पूर्णांक mpc5200_audio_dma_create(काष्ठा platक्रमm_device *op);
पूर्णांक mpc5200_audio_dma_destroy(काष्ठा platक्रमm_device *op);

#पूर्ण_अगर /* __SOUND_SOC_FSL_MPC5200_DMA_H__ */
